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
char /*thiscall*/ sub_5D0070(int this)  // 函数定义: 逐帧门控（攻击态收招 + 守卫站立二次判定）
{
  int pThis_348; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);  // this+1332 装备/动画定义对象
  sub_5CF180((uint32_t *)this);  // 环绕音管理
  LOBYTE(pThis_348) = 1;  // 调 取 16 位值低 8 位
  if ( *(uint8_t *)(this + 8669) == 1 && *(uint8_t *)(this + 8603) == 0 && *(uint8_t *)(this + 8601) == 1 )  // 判定 “+8669 守卫激活位”
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 虚函数调用 槽+840：大状态 getter（this+6556）
    if ( pThis_348 == 0 )
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);  // 虚函数调用 槽+1344
  }
  return pThis_348;
}



// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5D00D0 sub_5D00D0 —— 守卫状态分派透传（激活门）
// this+8669==1（守卫激活）时把状态事件原样转发 ·sub_4E33D0 状态收尾族；
// 未激活直接返回（result 未赋值，Hex-Rays 忠实输出保留）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D00D0(uint8_t *this, char pszArg2, float fArg3, int nArg4, int nArg5)  // 函数定义: 守卫状态分派透传（激活门）
{
  int result; // eax

  if ( *(this + 8669) == 1 )  // 判定 “+8669 守卫激活位”
    return sub_4E33D0(pszArg2, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  return result;
}



// AI 字段访问（this+8601/8812/8816）
// ------------------------------------------------------------
// 0x5D00F0 sub_5D00F0 —— 守卫相位三槽清零（站立位 + 两计时空槽）
// this+8601 = 0、this+8812 = 0、this+8816 = 0 后返回 0（this+8816 为相位计时器）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D00F0(int this)  // 函数定义: 守卫相位三槽清零（站立位 + 两计时空槽）
{
  *(uint8_t *)(this + 8601) = 0;  // this+8601 站立位
  *(uint32_t *)(this + 8816) = 0;  // this+8816 蓄力计时戳
  *(uint32_t *)(this + 8812) = 0;  // this+8812 蓄力门
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
char /*thiscall*/ sub_5D0110(uint32_t *this, int nArg2)  // 函数定义: 碰撞对象过滤与目标投递（守卫交互判定）
{
  char result; // al
  int pObj; // edi
  int fld_e2203; // eax  | +0x226C → 蓄力门（5D00F0 清零）（证据 va=005D00F0）（CNAxeExpeller；va=005D00F0）

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
  if ( result == 1 )
  {
    pObj = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);  // 虚函数调用 槽+700：读 +6296 槽
    if ( (uint8_t)sub_53F660(*(this + 2203)) == 1 )  // this+8812〔uCharge8812(推断)〕
    {
      fld_e2203 = *(this + 2203) + 8;  // this+8812〔uCharge8812(推断)〕
      *(uint8_t *)(fld_e2203 + 13) = 0;
      *(uint8_t *)(fld_e2203 + 14) = 0;
      return sub_698F90(*(this + 2203) + 8, 20000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2203) + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
               *(this + 2203),  // this+8812〔uCharge8812(推断)〕
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
int /*thiscall*/ sub_5D01B0(void *this, int nArg2, int nArg3, int nArg4)  // 函数定义: 架招反击挂钩（攻击态 + 段号 2）
{
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0((unsigned int)this + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1360))(this, nArg2);  // 虚函数调用 槽+1360
  return sub_4DB480(nArg2, nArg3, nArg4);  // 调 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D0200 sub_5D0200 —— 双子对象析构释放（this+2203/2204 槽）
// 对 this+2204、this+2203 两个指针槽各自判空后经其虚表首槽（+0）以参数 1 调用
// （·0x5AF1C0 式释放约定），随后两槽置 0 返回最后结果。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0200(uint32_t *this)  // 函数定义: 双子对象析构释放（this+2203/2204 槽）
{
  int (/*thiscall*/ ***fld_e2204)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e2203)(uint32_t, int); // ecx

  fld_e2204 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2204);  // this+8816〔uCharge8816(推断)〕
  if ( fld_e2204 != nullptr )  // 若 fld_e2204 有效（非空）
    result = (**fld_e2204)(fld_e2204, 1);  // 调 fld_e2204 的虚函数（vt+0）
  fld_e2203 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2203);  // this+8812〔uCharge8812(推断)〕
  *(this + 2204) = 0;  // this+8816〔uCharge8816(推断)〕
  if ( fld_e2203 != nullptr )  // 若 fld_e2203 有效（非空）
    result = (**fld_e2203)(fld_e2203, 1);  // 调 fld_e2203 的虚函数（vt+0）
  *(this + 2203) = 0;  // this+8812〔uCharge8812(推断)〕
  return result;
}



// 时钟门 AI（sub_699000; this+8600/8812..8837 守卫相位）
// ------------------------------------------------------------
// 0x5D0240 sub_5D0240 —— 相位场复位 + 计时器重挂（30 帧窗口）
// 先清 this+8600/8829/8832/8812 与 this+8824（计数器）、this+8837（标志），
// 再经 ·sub_699000(clock_now, this+36) 取当前时刻写入 this+8816 作起点，
// 并把窗口长度 this+8820 置 30 帧。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0240(int this)  // 函数定义: 相位场复位 + 计时器重挂（30 帧窗口）
{
  int result; // eax

  *(uint8_t *)(this + 8600) = 0;  // 写 this+8600 = 0（子类AI区）
  *(uint8_t *)(this + 8829) = 0;  // this+8829 蓄雷复位字节
  *(uint32_t *)(this + 8832) = 0;  // this+8832 蓄雷参数槽
  *(uint8_t *)(this + 8812) = 0;  // this+8812 蓄雷门
  result = sub_699000(this + 36);  // 【clock_now(clk)】
  *(uint32_t *)(this + 8824) = 0;  // this+8824 蓄雷次数
  *(uint8_t *)(this + 8837) = 0;  // this+8837 编队召唤单次门
  *(uint32_t *)(this + 8816) = result;  // this+8816 蓄雷计时戳
  *(uint32_t *)(this + 8820) = 30;  // this+8820 蓄雷窗口长度
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D0290 sub_5D0290 —— 三武器槽扫描赋默认值（先转 ·sub_4D4CE0 基类）
// 转调 ·sub_4D4CE0(this, nArg2) 后从 this+1648 起以 uint32_t 步长扫描最多 3 槽，
// 遇值 17（玩家型 id）即停；对命中槽写三字段：+412/+436 槽 = 6、+436/+... = 8、
// +424 槽 = 1097859072（浮点 110.0 的位模式）。【推断】按武器序号索引的默认参数面
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0290(char *this, int nArg2)  // 实现：三武器槽扫描赋默认值（先转 ·sub_4D4CE0 基类）
{
  int result; // eax
  uint32_t *i; // ecx

  sub_4D4CE0(this, nArg2);
  result = 0;
  for ( i = this + 412; *i != 17; ++i )  // this+412 【推断】攻击盒肢体槽 B
  {
    if ( ++result >= 3 )
      return result;
  }
  *((uint32_t *)this + result + 103) = 6;
  *((uint32_t *)this + result + 109) = 8;
  *((uint32_t *)this + result + 106) = 1097859072;  // 常量 15.0f
  return result;
}



// AI 字段访问（this+8812/8824）
// ------------------------------------------------------------
// 0x5D02E0 sub_5D02E0 —— 攻击段计数器累加（段号为 1 的帧）
// 以 this+7028 段槽经 ·sub_41A5E0 读段号，把「当前段号 == 1」写入 this+8812，
// 该帧命中段槽时 this+8824 计数器自增 1，最后统一转 ·sub_4DB480 反击判定。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D02E0(int this, int nArg2, int nArg3, int nArg4)  // 函数定义: 攻击段计数器累加（段号为 1 的帧）
{
  unsigned int pThis_1B74; // edi

  pThis_1B74 = this + 7028;  // this+7028 攻击段号槽
  *(uint8_t *)(this + 8812) = sub_41A5E0(this + 7028) == 1;  // crypt4byte 解密校验（·0x41A590 逆运算）
  if ( sub_41A5E0(pThis_1B74) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    ++*(uint32_t *)(this + 8824);  // this+8824 蓄雷次数
  return sub_4DB480(nArg2, nArg3, nArg4);  // 调 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 蓄雷 AI：BEFORE_THUNDER 播报（175L；雷守卫蓄雷循环 —— 与 0x5A1BF0 基诺尔同族）
// ------------------------------------------------------------
// 0x5D0330 sub_5D0330 —— 蓄雷循环：BEFORE_THUNDER 播报 + 雷柱预判布点（175L）
// 【推断】雷守卫蓄雷相位机：按动画序号 pDwArg1[2208] 查表 nFrameSeqTbl=0..11 帧序、
// nFrameOffTbl=0/150..1150 偏移、nHalfSpanTbl=10..120 半径档；
// 与 vt+200 帧号 +148 比对且 this+8829==0 时经 vt+212 播报 BEFORE_THUNDER（雷预警语音），
// 再取 vt+120/124 以 0.5 系数算落点 nBoltX/nBoltY，依目标 pDwArg1[1813] 的 vt+124 做上下侧判定 nSide（±1 翻向）；
// 多次 vt+584（位置写入）以 30070 号攻击、段 10、侧距（pDwArg1[1908] ? 100 : 130）在落点与 ±nHalfSpanTbl 偏移布雷柱
// （半血以下 this+8836 门内追加第三根），
// 收尾 this+8829=1 标记本帧已施放，待帧号推进至 nFrameSeqTbl[段号]+1 时复位并 ++段号，进入下一格。
// ------------------------------------------------------------
int /*usercall*/ sub_5D0330@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：蓄雷循环：BEFORE_THUNDER 播报 + 雷柱预判布点（175L）
{
  int result; // eax
  int nVt; // edx
  int nSelfX; // eax
  int nSegIdx; // ecx
  int nBoltX; // edi
  int pTarget; // ecx
  int nBoltY; // ebx
  int nTgtY; // ebx
  int nSelfY; // eax
  bool bEq; // zf
  bool bLt; // sf
  bool bOv; // of
  int nVt2; // eax
  int nSegIdx2; // ecx
  int nBoltY3; // [esp-38h] [ebp-108h]
  int nPadding; // [esp+4h] [ebp-CCh]
  uint32_t nFrameOffTbl[23]; // [esp+8h] [ebp-C8h]
  uint32_t nHalfSpanTbl[12]; // [esp+64h] [ebp-6Ch]
  uint32_t nFrameSeqTbl[12]; // [esp+94h] [ebp-3Ch]
  float fHalfHp; // [esp+C4h] [ebp-Ch]
  int nSide; // [esp+C8h] [ebp-8h]
  int nScratch; // [esp+CCh] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);  // 结果 = 虚调用 vt+308
  if ( (uint8_t)result != 0 )
  {
    nVt = *pDwArg1;
    nFrameSeqTbl[10] = 10;
    nHalfSpanTbl[0] = 10;
    nFrameSeqTbl[0] = 0;
    nFrameSeqTbl[1] = 1;
    nFrameSeqTbl[2] = 2;
    nFrameSeqTbl[3] = 3;
    nFrameSeqTbl[4] = 4;
    nFrameSeqTbl[5] = 5;
    nFrameSeqTbl[6] = 6;
    nFrameSeqTbl[7] = 7;
    nFrameSeqTbl[8] = 8;
    nFrameSeqTbl[9] = 9;
    nFrameSeqTbl[11] = 11;
    nPadding = 50;
    nFrameOffTbl[0] = 0;
    nFrameOffTbl[1] = 150;
    nFrameOffTbl[2] = 0;
    nFrameOffTbl[3] = 250;
    nFrameOffTbl[4] = 0;
    nFrameOffTbl[5] = 350;
    nFrameOffTbl[6] = 0;
    nFrameOffTbl[7] = 450;
    nFrameOffTbl[8] = 0;
    nFrameOffTbl[9] = 550;
    nFrameOffTbl[10] = 0;
    nFrameOffTbl[11] = 650;
    nFrameOffTbl[12] = 0;
    nFrameOffTbl[13] = 750;
    nFrameOffTbl[14] = 0;
    nFrameOffTbl[15] = 850;
    nFrameOffTbl[16] = 0;
    nFrameOffTbl[17] = 950;
    nFrameOffTbl[18] = 0;
    nFrameOffTbl[19] = 1050;
    nFrameOffTbl[20] = 0;
    nFrameOffTbl[21] = 1150;
    nFrameOffTbl[22] = 0;
    nHalfSpanTbl[1] = 20;
    nHalfSpanTbl[2] = 30;
    nHalfSpanTbl[3] = 40;
    nHalfSpanTbl[4] = 50;
    nHalfSpanTbl[5] = 60;
    nHalfSpanTbl[6] = 70;
    nHalfSpanTbl[7] = 80;
    nHalfSpanTbl[8] = 90;
    nHalfSpanTbl[9] = 100;
    nHalfSpanTbl[10] = 110;
    nHalfSpanTbl[11] = 120;
    nScratch = (*(int (/*thiscall*/ **)(int *))(nVt + 152))(pDwArg1) != 1 ? -1 : 1;  // 虚函数调用 槽+152：效果通道 3
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) + 148) == nFrameSeqTbl[pDwArg1[2208]]  // 虚调用 vt+200
      && *((uint8_t *)pDwArg1 + 8829) == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "BEFORE_THUNDER", -1, 0, 0);  // 字符串 “BEFORE_THUNDER”
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 && pDwArg1[2208] > 0 )  // 虚调用 vt+308
      {
        nSelfX = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 120))(pDwArg1, nArg2, nArg3);  // 结果 = 虚调用 vt+120
        nSegIdx = pDwArg1[2208];
        nSide = nSelfX;
        nBoltX = (uint64_t)((double)nSelfX + (double)nFrameOffTbl[2 * nSegIdx - 1] * 0.5 * (double)nScratch);
        nScratch = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);  // 结果 = 虚调用 vt+124
        pTarget = pDwArg1[1813];
        nBoltY = (uint64_t)((double)nScratch + (double)(int)nFrameOffTbl[2 * pDwArg1[2208]] * 0.5);
        nScratch = nBoltY;
        nSide = 1;
        if ( pTarget != 0 )
        {
          nTgtY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget + 124))(pTarget);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
          nSelfY = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);  // 结果 = 虚调用 vt+124
          bOv = __OFSUB__(nTgtY, nSelfY);  // bOv = 调 __OFSUB__
          bEq = nTgtY == nSelfY;
          bLt = nTgtY - nSelfY < 0;
          nBoltY = nScratch;
          nSide = 2 * !(bLt ^ bOv | bEq) - 1;
        }
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int))(*pDwArg1 + 584))(  // 虚调用 vt+584
          pDwArg1,
          nBoltX,
          nBoltY,
          0,
          nBoltX,
          nBoltY,
          30070,
          10,
          0,
          4,
          pDwArg1[1908] != 0 ? 100 : 130,
          1);
        nScratch = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1);  // 结果 = 虚调用 vt+740
        nVt2 = *pDwArg1;
        fHalfHp = (double)nScratch * 0.5;
        nScratch = (*(int (/*thiscall*/ **)(int *))(nVt2 + 736))(pDwArg1);  // 虚函数调用 槽+736：属性块首值（GetHP 族，此处索引）
        if ( (double)nScratch < fHalfHp )
        {
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*pDwArg1 + 584))(  // 虚调用 vt+584
            pDwArg1,
            nBoltX,
            nSide * nHalfSpanTbl[pDwArg1[2208]] + nBoltY,
            0,
            nBoltX,
            nSide * nHalfSpanTbl[pDwArg1[2208]] + nBoltY,
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
            nBoltY3 = nBoltY - nSide * nHalfSpanTbl[pDwArg1[2208]];
            (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*pDwArg1 + 584))(  // 虚调用 vt+584
              pDwArg1,
              nBoltX,
              nBoltY3,
              0,
              nBoltX,
              nBoltY3,
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
    result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 结果 = 虚调用 vt+200
    nSegIdx2 = pDwArg1[2208];
    if ( *(uint32_t *)(result + 148) == nFrameSeqTbl[nSegIdx2] + 1 )
    {
      *((uint8_t *)pDwArg1 + 8829) = 0;
      pDwArg1[2208] = nSegIdx2 + 1;
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
int /*thiscall*/ sub_5D06E0(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数定义: 架招反击挂钩（架招态 14 + 盾空闲）
{
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 14 && (uint8_t)nArg4 == 0 && *(this + 8603) == 0 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
    (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)this + 1336))(this, nArg2, nArg3, 0);  // 虚函数调用 槽+1336
  return sub_5CEFF0(this, nArg2, nArg3, nArg4);  // 法杖命中
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D0730 sub_5D0730 —— 大状态进入副作用（22 号 → 进架招 14）
// 先经 ·sub_4DBA80 执行大状态进入的增益侧副作用；若事件号 nArg2==22，
// 追加经 vt+560 setState 切到状态 14（架招）四参清零调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0730(void *this, int nArg2)  // 函数定义: 大状态进入副作用（22 号 → 进架招 14）
{
  int result; // eax

  result = sub_4DBA80(nArg2);  // 结果 = 大状态进入副作用处理器（增益侧）
  if ( nArg2 == 22 )
    return (*(int (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 14, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D0760 sub_5D0760 —— 大状态退出副作用（22 号 → 回状态 0）
// ·sub_4DBC20（0x4DBA80 的还原对偶）执行退出副作用后，若事件号 nArg2==22
// 追加 vt+560 setState 回退到状态 0 全零参数调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0760(void *this, int nArg2)  // 函数定义: 大状态退出副作用（22 号 → 回状态 0）
{
  int result; // eax

  result = sub_4DBC20(nArg2);  // 结果 = 大状态退出副作用处理器（0x4DBA80 的还原对偶）
  if ( nArg2 == 22 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D0790 sub_5D0790 —— 单槽析构释放（this+2213）
// 对 this+2213 指针槽判空后经虚表首槽以参数 1 调用（·0x5AF1C0 式释放约定），
// 随后置 0。同 ·sub_5D0200 是同一析构族的单槽变体（此处挂的是 TSM 破碎粒子对象）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0790(uint32_t *this)  // 函数定义: 单槽析构释放（this+2213）
{
  int (/*thiscall*/ ***fld_e2213)(uint32_t, int); // ecx
  int result; // eax

  fld_e2213 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2213);
  if ( fld_e2213 != nullptr )  // 若 fld_e2213 有效（非空）
    result = (**fld_e2213)(fld_e2213, 1);  // 调 fld_e2213 的虚函数（vt+0）
  *(this + 2213) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D07B0 sub_5D07B0 —— 单槽析构释放（this+2207）
// 对 this+2207 指针槽判空后经虚表首槽以参数 1 调用（·0x5AF1C0 式释放约定）
// 并置 0；槽位语义与 this+2203/2204（·sub_5D0200）、this+2213（·sub_5D0790）同族。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D07B0(uint32_t *this)  // 函数定义: 单槽析构释放（this+2207）
{
  int (/*thiscall*/ ***fld_e2207)(uint32_t, int); // ecx
  int result; // eax

  fld_e2207 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2207);
  if ( fld_e2207 != nullptr )  // 若 fld_e2207 有效（非空）
    result = (**fld_e2207)(fld_e2207, 1);  // 调 fld_e2207 的虚函数（vt+0）
  *(this + 2207) = 0;
  return result;
}



// AI 相位字段（this+8600/8812..8820）
// ------------------------------------------------------------
// 0x5D07D0 sub_5D07D0 —— 相位四槽清零（计时起点 + 窗口长 + 站立位）
// this+8812 = 0、this+8816 = 0、this+8820 = 0（窗口长清零）、this+8600 = 0 后返回 0；
// 与 ·sub_5D0240（重挂 30 帧窗口）配对使用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D07D0(int this)  // 函数定义: 相位四槽清零（计时起点 + 窗口长 + 站立位）
{
  *(uint8_t *)(this + 8812) = 0;  // this+8812 相位窗口门
  *(uint32_t *)(this + 8816) = 0;  // this+8816 相位窗口起点时刻
  *(uint8_t *)(this + 8820) = 0;  // this+8820 相位窗口长度
  *(uint8_t *)(this + 8600) = 0;  // 写 this+8600 = 0（子类AI区）
  return 0;
}



// AI 字段访问（this+8722）
// ------------------------------------------------------------
// 0x5D07F0 sub_5D07F0 —— 消亡/解除绑定处理（this+7260 主属 + this+8722 播报位）
// 若 uArg2 即自身主属体 this+7260 且 vt+316 判定有效，先经 vt+312(this, 0) 解绑；
// 再统一转 ·sub_4D9170 消亡通知；若 uArg2 == this（自身消亡）且 this+8722==1
// 则经 vt+216(this, 10) 播报 10 号表现/音效（与 ·sub_5D0950 播报族同槽）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D07F0(uint8_t *this, uint8_t *uArg2)  // 函数定义: 消亡/解除绑定处理（this+7260 主属 + this+8722 播报位）
{
  int result; // eax

  if ( uArg2 == *((uint8_t **)this + 1815) && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 316))(this) != 0 )  // 虚函数调用 槽+316
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);  // 虚函数调用 槽+312：濒死/一击表现（LAST STRIKE；死亡链上游）【新发现(会话 3)】
  result = sub_4D9170(uArg2);  // 调 消亡通知
  if ( uArg2 == this && *(this + 8722) == 1 )  // this+8722〔播报位〕
    return (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 10);  // this+216 【推断】子链标志字节
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
uint32_t */*thiscall*/ sub_5D0850(uint32_t *this, int nArg2, int nArg3)  // CNRDParticleCreater 构造（破碎粒子对象，0xEC 字节）
{
  *this = &CNRDParticleCreater::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_423A20(this + 1);  // 小结构初始化（0-100 刻度）
  *(this + 26) = 0;  // this+104〔nTimerEnd(推断)〕
  *(this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *(this + 28) = 0;  // this+28 【推断】逐帧驱动对象
  *(this + 29) = 0;  // this+116〔会话上下文〕
  *(this + 30) = 0;  // this+120〔pAnimObj〕
  *(this + 31) = 0;  // this+124〔pAuraAnim(推断)〕
  *(this + 32) = 0;  // this+32 格子像素尺寸
  *(this + 33) = 0;  // this+33 【推断】职业数据脏位
  *(this + 34) = 0;  // this+136〔nCtx136(推断)〕
  *(this + 35) = 0;  // this+140〔nAdd140(推断)〕
  *(this + 36) = 0;  // 写 this+36 = 0（状态字）
  *(this + 37) = 0;  // this+37 【推断】淡入收尾标志 A
  *(this + 38) = 0;  // this+38 【推断】淡入收尾标志 B
  *((uint8_t *)this + 156) = 0;  // this+156 第 4 组·+858/+1292 增量
  *(this + 40) = 100;  // 写 this+40 = 100（状态子标志）
  *(this + 41) = 100;  // this+164〔fAdd164(推断)〕
  *(this + 42) = 100;  // this+168〔pAppendVec(推断)〕
  *((uint8_t *)this + 172) = 1;  // this+172 附属对象向量 end
  *((uint8_t *)this + 180) = 0;  // this+180 半径/计数
  *(this + 44) = &off_6C2B88;  // this+44 剩余时间 ms
  *(this + 46) = 0;  // this+184〔bSingleTarget(推断)〕
  *((uint8_t *)this + 188) = 1;  // this+188 状态槽索引
  *((uint8_t *)this + 190) = 0;  // this+190 【推断】复位字节 B
  *((uint8_t *)this + 189) = 0;  // this+189 【推断】复位字节 A
  *(this + 50) = 0;  // this+50 M_CHARACTER_SELECT 一次性发送标志
  *(this + 49) = 0;  // this+49 UDP 已上报标志
  *(this + 48) = 0;  // this+48 UDP 上报使能位
  sub_4902C0(this);  // 动画状态复位（+204..232 清零、+216=1、+232=-1）
  sub_490D40(nArg2, nArg3);  // 重置包装：先 vt+4(nArg2,nArg3) 配置，再 ·0x490BD0 复位
  return this;  // 返回自身指针
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
void /*thiscall*/ sub_5D0950(uint32_t *this)  // 函数定义: 行为字相位机 + 语音播报门（this+1787 / this+8722）
{
  char *pThis_895; // eax
  uint32_t *pThis; // ecx

  if ( *((uint8_t *)this + 8669) == 1 )  // this+8669 守卫激活位
  {
    sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
    if ( *(this + 1787) == 5 )  // 判定 “+7148 大状态镜像槽”
      goto LABEL_6;
    if ( *((uint8_t *)this + 8722) == 1 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10);  // 虚调用 vt+216
      *((uint8_t *)this + 8722) = 0;
    }
    if ( *(this + 1787) == 5 )  // 判定 “+7148 大状态镜像槽”
    {
LABEL_6:
      if ( *((uint8_t *)this + 8722) == 0 )
      {
        if ( *(this + 2202) < 0x10u )
          pThis_895 = (char *)(this + 2197);  // this+2197 语音名 SSO 缓冲
        else
          pThis_895 = (char *)*(this + 2197);  // this+2197 语音名 SSO 缓冲
        (*(void (/*thiscall*/ **)(uint32_t *, char *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_895, 10, 0, 0);  // 虚调用 vt+212
        *((uint8_t *)this + 8722) = 1;
      }
    }
    switch ( *(this + 1787) )  // this+1787 行为字槽
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);  // 虚调用 vt+1284
        break;
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        pThis = this;
        if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
          goto LABEL_19;
        goto LABEL_14;
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
LABEL_14:
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 虚调用 vt+1104
        break;
      case 0xD:
      case 0xE:
      case 0xF:
        if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
        {
          pThis = this;
LABEL_19:
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(pThis, 5);  // 虚调用 vt+1104
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
char /*thiscall*/ sub_5D0A60(uint32_t *this)  // 函数定义: 冷却门反击概率机（写行为字 22）
{
  int fld_e2187; // ebx
  int pThis_885; // edi
  int pThis_8853; // eax
  int fld_e1813; // eax  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int fld_e18132; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int fld_e18133; // ebx  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  BOOL v9; // [esp+Ch] [ebp-8h]
  uint32_t *pThis_8852; // [esp+10h] [ebp-4h]

  fld_e2187 = *(this + 2187);  // this+8748〔bTail8748〕
  pThis_885 = (int)(this + 2181);  // this+8724〔nSegThrEnd8724(推断)〕
  pThis_8852 = this + 2181;
  pThis_8853 = sub_699000((int)(this + 2181));  // 【clock_now(clk)】
  if ( pThis_8853 >= fld_e2187 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 虚调用 vt+308
      && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0  // 虚调用 vt+840
      && *(this + 1787) != 22 )  // this+1787 行为字槽
    {
      fld_e1813 = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( fld_e1813 != 0 && (*(uint8_t (/*stdcall*/ **)(int))(*(uint32_t *)fld_e1813 + 40))(17) != 0 )  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      {
        fld_e18132 = *(this + 1813);  // this+7252〔pTarget7252〕
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 840))(fld_e18132) == 8  // 虚函数调用 槽+840：大状态 getter（this+6556）
          || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 840))(fld_e18132) == 7  // 虚函数调用 槽+840：大状态 getter（this+6556）
          || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e18132 + 40))(fld_e18132, 273) != 0  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 840))(fld_e18132) == 12;  // 虚函数调用 槽+840：大状态 getter（this+6556）
        fld_e18133 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 152))(*(this + 1813));  // 虚函数调用 槽+152：效果通道 3
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != fld_e18133  // 虚调用 vt+152
          && v9
          && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, fld_e18132, 0) < 150  // 虚调用 vt+8
          && rand() % 100 < *(this + 2179) )  // 调 取伪随机数
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 22);  // 虚调用 vt+1104
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
void /*thiscall*/ sub_5D0BA0(int this)  // 函数定义: 守卫相位主门（架招释放概率 10%）
{
  int fld_1C54; // eax  | +0x1C54 → 当前目标/技能对象（0x5D0BA0 可架招窗口判定；0x5AD610 取坐标）（证据 va=005D0BA0）（CNKingGuard；va=005D0BA0）
  int v3; // edi
  int fld_1C542; // edi

  if ( *(uint8_t *)(this + 8669) == 1 )  // 判定 “+8669 守卫激活位”
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
    {
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) == 1 )  // this+200 主状态
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
    }
    else
    {
      sub_5D0950((uint32_t *)this);  // 行为字相位机 + 语音播报门（this+1787 / this+8722）
      if ( *(uint32_t *)(this + 7148) == 22 )  // 判定 “+7148 大状态镜像槽”
      {
        if ( *(uint32_t *)(this + 7252) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )  // this+7252 当前目标/技能对象
        {
          fld_1C54 = *(uint32_t *)(this + 7252);  // this+7252 当前目标/技能对象
          if ( fld_1C54 != 0 )
          {
            v3 = (*(int (**)(void))(*(uint32_t *)fld_1C54 + 120))();  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
            if ( ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) >= v3  // this+120 基类动画对象指针
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0)  // this+152 第 4 组·+886 增量
              && ((fld_1C542 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252)),  // this+7252 当前目标/技能对象
                   (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) < fld_1C542)  // this+120 基类动画对象指针
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 1) )  // this+152 第 4 组·+886 增量
            {
              if ( rand() % 100 < 10 )  // 调 取伪随机数
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 4);  // this+1104 时钟槽 B
                (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1340))(this);  // 虚函数调用 槽+1340
              }
            }
            else
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 5);  // this+1104 时钟槽 B
            }
          }
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 13);  // this+1104 时钟槽 B
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
int /*thiscall*/ sub_5D0CC0(float *this, int pArg2)  // 函数定义: 多段投射物扇形布点（nArg2 ≤ 5 段）
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

  result = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 308))(this);  // 虚函数调用 槽+308
  if ( (uint8_t)result != 0 && pArg2 <= 5 )
  {
    pThis_1D = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)this + 29) + 132) + 44);  // this+116〔会话上下文〕
    v5 = *(uint32_t *)(pThis_1D + 364);  // this+364 动画件名缓冲 SSO 内联首址
    if ( v5 != 0 )
      v6 = (*(uint32_t *)(pThis_1D + 368) - v5) >> 5;  // this+368 绑定坐标记录 Y
    else
      v6 = 0;
    v7 = 224 * v6 / (pArg2 + 1);
    v12 = v7;
    result = 120 * (sub_424FF0() + 3) / 2;  // 结果 = 列数换算
    v14 = result;
    if ( pArg2 > 0 )
    {
      do
      {
        fld_e2233 = (uint64_t)((double)*(int *)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 672))(  // this+672 【推断】拾取/交互目标有效标志
                                                  this,
                                                  0)
                              * *(this + 2233));  // this+8932〔nComboSeg8932〕
        v9 = *this;
        fld_e22332 = fld_e2233;
        pThis_98 = (*(int (/*fastcall*/ **)(float *, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(  // this+152 第 4 组·+886 增量
                this,
                HIDWORD(fld_e2233),  // 调 取 64 位值高 32 位
                2,
                0,
                0,
                0xFFFF,
                0,
                0,
                0,
                0);
        pThis_178 = (*(int (/*thiscall*/ **)(float *, int, int, int, uint32_t, int))(*(uint32_t *)this + 376))(  // this+376 绑定参考值 B
                this,
                fld_e22332,
                v7,
                v14,
                0,
                pThis_98);
        (*(void (/*thiscall*/ **)(float *, int, int))(LODWORD(v9) + 592))(this, 50068, pThis_178);  // 虚函数调用 槽+592：位置/状态同步包发布（短版 48024 / 长版 type 22）
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
int /*thiscall*/ sub_5D0DB0(void *this)  // 函数定义: 守卫相位主门包装 + 姿态回读
{
  int result; // eax

  sub_5D0BA0((int)this);  // 守卫相位主门（架招释放概率 10%）
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);  // 虚函数调用 槽+308
  if ( (uint8_t)result == 1 )
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);  // 虚函数调用 槽+840：大状态 getter（this+6556）
  return result;
}



// 天界驱逐者破碎：引用 Particle/HeavenExpellerBrokenParts.ptl（23L）
// ------------------------------------------------------------
// 0x5D0DE0 sub_5D0DE0 —— 天界驱逐者破碎：装载 HeavenExpellerBrokenParts.ptl
// 三槽 this+8704/8708/8712 置 -1（破碎段序号无效化），vt+1308 先行走清理，
// 再经 vt+1352 装载粒子字符串 Particle/HeavenExpellerBrokenParts.ptl
// （资源名 this+364 起 SSO，≥16 取堆指针）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0DE0(uint32_t *this)  // 函数定义: 天界驱逐者破碎：装载 HeavenExpellerBrokenParts.ptl
{
  *(this + 2176) = -1;  // this+8704〔pSegNameTbl8704(推断)〕
  *(this + 2177) = -1;  // this+8708〔pCandTbl8708(推断)〕
  *(this + 2178) = -1;  // this+8712〔nCandTblEnd8712(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 虚调用 vt+1308
  if ( *(this + 96) < 0x10u )  // 判定 “+384 SSO容量”
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(  // 虚调用 vt+1352
             this,
             this + 91,
             "Particle/HeavenExpellerBrokenParts.ptl");  // 字符串 “Particle/HeavenExpellerBrokenParts.ptl”
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, const char *))(*this + 1352))(  // 虚调用 vt+1352
             this,
             *(this + 91),  // this+364〔pAnimNameStr(推断)〕
             "Particle/HeavenExpellerBrokenParts.ptl");  // 字符串 “Particle/HeavenExpellerBrokenParts.ptl”
}



// 主状态门（this+200/8669）
// ------------------------------------------------------------
// 0x5D0E40 sub_5D0E40 —— 守卫相位主门（架招释放概率 20% + 收招后置门）
// 与 ·sub_5D0BA0 同构：姿态非 14 时转 ·sub_5D0950，攻击段槽 this+7148==22 且
// this+7252 非空、目标可架招窗口判定通过时 rand()%100 < 20（概率翻倍）写行为字 4
// 并 vt+1340 触发，否则写 5；差异在于收招门（姿态 14 且状态块 +170==1 时
// vt+560 setState 全零）在本函数中位于尾部无条件执行。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D0E40(int this)  // 函数定义: 守卫相位主门（架招释放概率 20% + 收招后置门）
{
  int fld_1C54; // eax  | +0x1C54 → 当前目标/技能对象（各证据行判非 0 后走架招窗口与坐标链）（证据: va=005D0E40）（CNHeavenExpeller；va=005D0E40）
  int v3; // edi
  int fld_1C542; // edi

  if ( *(uint8_t *)(this + 8669) == 1 )  // 判定 “+8669 守卫激活位”
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) != 14 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
    {
      sub_5D0950((uint32_t *)this);  // 行为字相位机 + 语音播报门（this+1787 / this+8722）
      if ( *(uint32_t *)(this + 7148) == 22 )  // 判定 “+7148 大状态镜像槽”
      {
        if ( *(uint32_t *)(this + 7252) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )  // this+7252 当前目标/技能对象
        {
          fld_1C54 = *(uint32_t *)(this + 7252);  // this+7252 当前目标/技能对象
          if ( fld_1C54 != 0 )
          {
            v3 = (*(int (**)(void))(*(uint32_t *)fld_1C54 + 120))();  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
            if ( ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) >= v3  // this+120 基类动画对象指针
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0)  // this+152 第 4 组·+886 增量
              && ((fld_1C542 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252)),  // this+7252 当前目标/技能对象
                   (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) < fld_1C542)  // this+120 基类动画对象指针
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 1) )  // this+152 第 4 组·+886 增量
            {
              if ( rand() % 100 < 20 )  // 调 取伪随机数
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 4);  // this+1104 时钟槽 B
                (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1340))(this);  // 虚函数调用 槽+1340
              }
            }
            else
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 5);  // this+1104 时钟槽 B
            }
          }
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 13);  // this+1104 时钟槽 B
        }
      }
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14  // 虚函数调用 槽+840：大状态 getter（this+6556）
      && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) == 1 )  // this+200 主状态
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
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
void /*thiscall*/ sub_5D0F80(int this)  // 函数定义: 守卫相位主门（低频架招释放 1%）
{
  int fld_1C54; // edi  | +0x1C54 → 当前目标/技能对象（各证据行判非 0 后走架招窗口与坐标链）（证据: va=005D0E40）（CNTinSwordManExpeller；va=005D0E40）
  int fld_1C542; // edi
  int v4; // [esp+4h] [ebp-4h]

  if ( *(uint8_t *)(this + 8669) == 1 )  // 判定 “+8669 守卫激活位”
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) != 14 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
    {
      sub_5D0950((uint32_t *)this);  // 行为字相位机 + 语音播报门（this+1787 / this+8722）
      if ( *(uint32_t *)(this + 7148) == 22 )  // 判定 “+7148 大状态镜像槽”
      {
        if ( *(uint32_t *)(this + 7252) != 0 )  // this+7252 当前目标/技能对象
        {
          fld_1C54 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252));  // this+7252 当前目标/技能对象
          if ( ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) >= fld_1C54  // this+120 基类动画对象指针
             || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0)  // this+152 第 4 组·+886 增量
            && ((fld_1C542 = *(uint32_t *)(this + 7252),  // this+7252 当前目标/技能对象
                 (v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this)) < (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_1C542 + 120))(fld_1C542))  // this+120 基类动画对象指针
             || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 1) )  // this+152 第 4 组·+886 增量
          {
            if ( rand() % 100 < 1 )  // 调 取伪随机数
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 4);  // this+1104 时钟槽 B
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1340))(this);  // 虚函数调用 槽+1340
            }
          }
          else
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 5);  // this+1104 时钟槽 B
          }
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 13);  // this+1104 时钟槽 B
        }
      }
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14  // 虚函数调用 槽+840：大状态 getter（this+6556）
      && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) == 1 )  // this+200 主状态
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
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
uint32_t */*thiscall*/ sub_5D10A0(int *this)  // 驱逐者破碎 + TSM 碎屑双装载（TSM 型专用）
{
  int *pThis_5B; // eax
  uint32_t *pMem; // eax
  uint32_t *result; // eax

  *(this + 2176) = -1;  // this+8704〔pSegNameTbl8704(推断)〕
  *(this + 2177) = -1;  // this+8708〔pCandTbl8708(推断)〕
  *(this + 2178) = -1;  // this+8712〔nCandTblEnd8712(推断)〕
  if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 插值终点 X / 落点偏移
    pThis_5B = this + 91;
  else
    pThis_5B = (int *)*(this + 91);  // this+364〔pAnimNameStr(推断)〕
  (*(void (/*thiscall*/ **)(int *, int *, const char *))(*this + 1352))(this, pThis_5B, "Particle/ExpellerBrokenParts.ptl");  // 字符串 “Particle/ExpellerBrokenParts.ptl”
  pMem = operator new(0xECu);  // 堆分配 236 字节对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
  {
    if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 插值终点 X / 落点偏移
      result = sub_5D0850(pMem, (int)(this + 91), (int)"Particle/TSMShattered.ptl");  // 字符串 “Particle/TSMShattered.ptl”
    else
      result = sub_5D0850(pMem, *(this + 91), (int)"Particle/TSMShattered.ptl");  // 字符串 “Particle/TSMShattered.ptl”
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
int /*thiscall*/ sub_5D1160(uint32_t *this)  // 函数定义: 斧驱逐者破碎：装载 AxeExpellerBrokenParts.ptl
{
  *(this + 2176) = -1;  // this+8704〔pSegNameTbl8704(推断)〕
  *(this + 2177) = -1;  // this+8708〔pCandTbl8708(推断)〕
  *(this + 2178) = -1;  // this+8712〔nCandTblEnd8712(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 虚调用 vt+1308
  if ( *(this + 96) < 0x10u )  // 判定 “+384 SSO容量”
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(  // 虚调用 vt+1352
             this,
             this + 91,
             "Particle/AxeExpellerBrokenParts.ptl");  // 字符串 “Particle/AxeExpellerBrokenParts.ptl”
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, const char *))(*this + 1352))(  // 虚调用 vt+1352
             this,
             *(this + 91),  // this+364〔pAnimNameStr(推断)〕
             "Particle/AxeExpellerBrokenParts.ptl");  // 字符串 “Particle/AxeExpellerBrokenParts.ptl”
}



// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5D11C0 sub_5D11C0 —— 帧处理包装（激活门）
// this+8669==1 时转 ·sub_5D0950 行为字相位机，否则空返回（守卫未激活跳过）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D11C0(uint32_t *this)  // 函数定义: 帧处理包装（激活门）
{
  if ( *((uint8_t *)this + 8669) == 1 )  // this+8669 守卫激活位
    sub_5D0950(this);  // 行为字相位机 + 语音播报门（this+1787 / this+8722）
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
int /*thiscall*/ sub_5D11D0(uint32_t *this, int nArg2, float *pArg3, int nArg4)  // 函数定义: 防御守卫嘲讽：R_DEFEN_GUARD_LAUGH + CNChangeHp 伤害包（168L）
{
  int nArg22; // ebx
  int pObj; // esi
  int nAtkOwner; // eax
  int fld_e2210; // ecx  | +0x2288 → 相位/档位槽（0x5CFB50：!=2 才加绘，并按 +4*本槽 取色档）（CNGuardBlock）
  int nVt1; // edx
  int nDmgRet; // eax
  float fSelfX; // edx
  float fSelfY; // eax
  float fSelfZ; // edx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int nObjX; // ebx
  int nRand; // edx
  int v20; // eax
  int nObjY; // ebx
  int nRand2; // edx
  int v23; // eax
  int nObjZ; // ebx
  uint8_t *pMem; // eax
  uint8_t *pDmgObj; // eax
  int nDmgObjVt; // edx
  int nSelfX2; // eax
  uint32_t *pThis_69C; // eax
  int nHitZ; // [esp+10h] [ebp-60h]
  int nHitY; // [esp+14h] [ebp-5Ch]
  int nHitX; // [esp+18h] [ebp-58h]
  int nHitRatio; // [esp+20h] [ebp-50h]
  int nHitFlag; // [esp+24h] [ebp-4Ch]
  float fPtX; // [esp+34h] [ebp-3Ch] BYREF
  float fPtY; // [esp+38h] [ebp-38h]
  float fPtZ; // [esp+3Ch] [ebp-34h]
  int nBoxA; // [esp+40h] [ebp-30h]
  int nBoxB; // [esp+44h] [ebp-2Ch]
  int nBoxC; // [esp+48h] [ebp-28h]
  uint8_t v42[4]; // [esp+4Ch] [ebp-24h] BYREF
  void *Block; // [esp+50h] [ebp-20h]
  int nEffId; // [esp+54h] [ebp-1Ch]
  int nDmgVal; // [esp+58h] [ebp-18h]
  int nHitIdx; // [esp+5Ch] [ebp-14h] BYREF
  char v47; // [esp+63h] [ebp-Dh] BYREF
  int nFreeState; // [esp+6Ch] [ebp-4h]

  nArg22 = nArg2;
  if ( nArg2 != 0 )
    pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // vt+576 受击体
  else
    pObj = 0;
  if ( *(this + 2175) == -1  // 相位空闲
    && *(this + 2210) != 2  // this+8840〔uPhase8840(推断)〕
    && pObj != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) == 1 )  // 存活
  {
    nAtkOwner = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // 攻击方档位
    if ( nAtkOwner != 0 )
    {
      fld_e2210 = *(this + 2210);  // this+8840〔uPhase8840(推断)〕
      LODWORD(fPtY) = 42004;  // 效果号表 起
      LODWORD(fPtZ) = 42003;  // 调 取 64 位值低 32 位
      nBoxA = 42005;
      nBoxB = 42006;
      nBoxC = 48011;  // 效果号表 止
      if ( fld_e2210 == 0 && *(uint32_t *)(nAtkOwner + 12) == 0 )
      {
        nEffId = 48011;  // 相位0 → 48011
        goto LABEL_15;
      }
      if ( fld_e2210 == 1 && *(uint32_t *)(nAtkOwner + 12) == 1 )
      {
        nEffId = *((uint32_t *)&fPtY + *(uint32_t *)(nAtkOwner + 20));  // 相位1：按攻击方 +20 档位索引取
        if ( nEffId != 0 )
        {
LABEL_15:
          nVt1 = *this;
          nHitIdx = 0;
          nDmgRet = (*(int (/*thiscall*/ **)(uint32_t *, char *, uint8_t *, int, int, float *, uint32_t))(nVt1 + 628))(  // 虚函数调用 槽+628：伤害流水线 / vt+628（研究 P14 九步公式全文定案）
                  this,
                  &v47,
                  v42,
                  100,
                  nArg2,
                  pArg3,
                  0);  // vt+628 伤害公式
          fSelfX = *pArg3;
          nDmgVal = nDmgRet;
          fSelfY = pArg3[1];
          fPtX = fSelfX;
          fSelfZ = pArg3[2];
          fPtY = fSelfY;
          v14 = *((uint32_t *)pArg3 + 3);
          fPtZ = fSelfZ;
          v15 = *((uint32_t *)pArg3 + 4);
          nBoxA = v14;
          v16 = *((uint32_t *)pArg3 + 5);
          nBoxB = v15;
          v17 = *(uint32_t *)pObj;
          nBoxC = v16;
          nObjX = (*(int (/*thiscall*/ **)(int))(v17 + 120))(pObj);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
          nRand = rand() % 60;  // 调 取伪随机数
          v20 = *(uint32_t *)pObj;
          Block = (void *)(nObjX + nRand - 30);  // 落点 X ±30 抖动
          fPtX = (float)(int)Block;
          nObjY = (*(int (/*thiscall*/ **)(int))(v20 + 124))(pObj);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
          nRand2 = rand() % 60;  // 调 取伪随机数
          v23 = *(uint32_t *)pObj;
          Block = (void *)(nObjY + nRand2 - 30);  // 落点 Y ±30
          fPtY = (float)(int)Block;
          nObjZ = (*(int (/*thiscall*/ **)(int))(v23 + 128))(pObj);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
          Block = (void *)(nObjZ + rand() % 60 - 30);  // 落点 Z ±30
          fPtZ = (float)(int)Block;
          pMem = operator new(0x80u);  // 堆分配 128 字节对象
          Block = pMem;
          nFreeState = 0;
          if ( pMem != nullptr )  // 若 pMem 有效（非空）
          {
            *(float *)&nHitX = (float)nDmgVal;
            pDmgObj = sub_4D6810(pMem, nHitX, 500, 1, 1);  // CNChangeHp 伤害包（500/1/1）
          }
          else
          {
            pDmgObj = nullptr;
          }
          nDmgObjVt = *(uint32_t *)pDmgObj;
          nFreeState = -1;
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(nDmgObjVt + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
            pDmgObj,
            this,
            this,
            0,
            0,
            0,
            -1);
          nHitFlag = sub_605840(&nHitIdx, pObj, &fPtX, 1);  // 体积/命中
          nHitRatio = nHitIdx;
          nHitY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
          nHitX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
          nSelfX2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
          sub_4E4A50(this, nEffId, nDmgVal, nSelfX2, nHitX, nHitY, 1, 0, nHitRatio, nHitFlag);  // 效果请求
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212
            this,
            "R_DEFEN_GUARD_LAUGH",  // 字符串 “R_DEFEN_GUARD_LAUGH”
            -1,
            0,
            0);
          nArg22 = nArg2;
          goto LABEL_23;
        }
      }
    }
    if ( *(this + 1697) < 0x10u )  // 效果表未命中：退化播报文案槽（this+1692，SSO 短串判别）
      pThis_69C = this + 1692;  // this+1692 播报提示串缓冲
    else
      pThis_69C = (uint32_t *)*(this + 1692);  // this+1692 播报提示串缓冲
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_69C, -1, 0, 0);  // 虚调用 vt+212
  }
LABEL_23:
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14 && (uint8_t)nArg4 == 0 )  // 姿态14：收招
    (*(void (/*thiscall*/ **)(uint32_t *, int, float *, uint32_t))(*this + 1336))(this, nArg22, pArg3, 0);  // 虚调用 vt+1336
  return sub_5CEFF0(nArg22, pArg3, nArg4);  // 法杖命中
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5D1490 sub_5D1490 —— 五元组记录构造（20 字节堆分配）
// operator new(0x14) 后写 (nArg1, nArg2, pArg3[0..2]) 五个 32 位字段，返回首址；
// 供上层把「攻击方/受击方 + 三轴坐标」快照存入列表。【推断】坐标/帧快照结构
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_5D1490(int nArg1, int nArg2, uint32_t *pArg3)  // 五元组记录构造（20 字节堆分配）
{
  uint32_t *result; // eax

  result = operator new(0x14u);  // 堆分配 20 字节对象
  if ( result != nullptr )  // 若 result 有效（非空）
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
char /*usercall*/ sub_5D14D0@<al>(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 实现：变身/变身解除三相位机（this+2175: -1→0→1→2）
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
    (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 144))(pDwArg1);  // 虚调用 vt+144
    v3 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 200))(pDwArg1, 0);  // 结果 = 虚调用 vt+200
    sub_493400(v3, 1);  // 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
    v4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 结果 = 虚调用 vt+200
    sub_4939E0(v4, 1);  // 播放/暂停级联（递归子链 +204）
    v5 = sub_4E7F30(pDwArg1, 200, 200, 0) == 0;  // 结果 = 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
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
      v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 200))(pDwArg1);  // 虚函数调用 槽+200：取动画对象
      sub_4926A0(v9);  // 帧游标复位（+44 帧数组；递归子链 +204）
      v10 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 结果 = 虚调用 vt+200
      LOBYTE(v6) = sub_4939E0(v10, 0);  // 播放/暂停级联（递归子链 +204）
    }
  }
  else if ( v6 == 2 )
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 结果 = 虚调用 vt+200
    if ( *(uint8_t *)(v6 + 170) == 1 )
    {
      v11 = pDwArg1 + 2156;
      for ( i = 8; i != 0; --i )  // 循环：i 从 8 递减到 0
      {
        if ( *v11 != 0 )
        {
          pObj = (*(int (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 784))(pDwArg1, *v11);  // 结果 = 虚调用 vt+784
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 虚函数调用 槽+4：复位/锁定（64F690 + 64A790 +…
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
      (*(void (/*thiscall*/ **)(int *, int *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(pDwArg1, v14, -1, 0, 0, nArg2);  // 虚调用 vt+212
      if ( *((uint8_t *)pDwArg1 + 7801) != 0 && *((uint8_t *)pDwArg1 + 8723) == 1 )
        sub_4DB130(24, 0);  // 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      if ( pDwArg1[2188] != 1065353216 )  // 常量 1.0f
      {
        v19 = *((float *)pDwArg1 + 2188);
        (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 688))(pDwArg1);  // 虚调用 vt+688
        sub_4EB2C0(v19);  // 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
        v15 = pDwArg1 + 2156;
        for ( j = 8; j != 0; --j )  // 循环：j 从 8 递减到 0
        {
          if ( *v15 != 0 )
            sub_4EB6A0(*((float *)pDwArg1 + 2188));  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
          ++v15;
        }
        pDwArg1[40] = (uint64_t)((double)pDwArg1[40] * *((float *)pDwArg1 + 2188));
      }
      LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 820))(pDwArg1, 1);  // 虚调用 vt+820
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
int /*thiscall*/ sub_5D16D0(uint32_t *this)  // 函数定义: 挂载点全表遍历销毁（装备/子件批量清理）
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

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *(this + 1540));  // 虚调用 vt+1328
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *(this + 1541));  // 虚调用 vt+1328
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *(this + 1542));  // 虚调用 vt+1328
  pThis_607 = this + 1543;
  for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *pThis_607++);  // 虚调用 vt+1328
  for ( j = (uint32_t *)*(this + 1550); j != (uint32_t *)*(this + 1551); ++j )  // this+6200〔pTbl6200〕
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *j);  // 虚调用 vt+1328
  for ( k = (uint32_t *)*(this + 1554); k != (uint32_t *)*(this + 1555); ++k )  // this+6216〔pTbl6216(推断)〕等 2 字段
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *k);  // 虚调用 vt+1328
  pThis_651 = this + 1617;
  pThis_6512 = this + 1617;
  v15 = 18;
  do
  {
    if ( *pThis_651 != 0 )
    {
      v7 = (*(int (**)(void))(*(uint32_t *)*pThis_651 + 248))();  // 结果 = 虚调用 vt+248
      v8 = *(uint32_t **)(v7 + 4);
      v14 = v7;
      if ( v8 != *(uint32_t **)(v7 + 8) )
      {
        do
        {
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, v8[1]);  // 虚调用 vt+1328
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, v8[2]);  // 虚调用 vt+1328
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, v8[3]);  // 虚调用 vt+1328
          v9 = v8 + 4;
          for ( m = 2; m != 0; --m )  // 循环：m 从 2 递减到 0
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *v9++);  // 虚调用 vt+1328
          for ( n = (uint32_t *)v8[11]; n != (uint32_t *)v8[12]; ++n )
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *n);  // 虚调用 vt+1328
          for ( ii = (uint32_t *)v8[15]; ii != (uint32_t *)v8[16]; ++ii )
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *ii);  // 虚调用 vt+1328
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
int /*stdcall*/ sub_5D1880(int pArg1)  // 函数定义: 时间轴批量前移 40（帧表烫平）
{
  int result; // eax
  int v2; // ecx

  result = pArg1;
  if ( pArg1 != 0 && pArg1 != -40 )  // 若 pArg1 != 0 与/或 pArg1 != -40
  {
    v2 = *(uint32_t *)(pArg1 + 44);  // pArg1+44〔nExpireMs(推断)〕
    if ( v2 != *(uint32_t *)(pArg1 + 48) )  // pArg1+48〔pCmdVecBegin48(推断)〕
    {
      do
      {
        *(uint32_t *)(v2 + 16) += 40;
        result = *(uint32_t *)(pArg1 + 48);  // pArg1+48〔pCmdVecBegin48(推断)〕
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
uint32_t */*thiscall*/ sub_5D18E0(uint8_t *this)  // 破碎初始化（粒子 + 双轴尺寸 + 变速因子）
{
  char *pThis_16C; // eax
  int pObj; // eax
  uint32_t *result; // eax

  *(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
  *((uint32_t *)this + 1802) = 150;
  *((uint32_t *)this + 2176) = -1;  // this+8704〔pSegNameTbl8704(推断)〕
  *((uint32_t *)this + 2177) = -1;  // this+8708〔pCandTbl8708(推断)〕
  *((uint32_t *)this + 2178) = -1;  // this+8712〔nCandTblEnd8712(推断)〕
  if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 插值终点 X / 落点偏移
    pThis_16C = this + 364;  // this+364 动画件名缓冲 SSO 内联首址
  else
    pThis_16C = *((char **)this + 91);
  (*(void (/*thiscall*/ **)(uint8_t *, char *, const char *))(*(uint32_t *)this + 1352))(  // 虚函数调用 槽+1352
    this,
    pThis_16C,
    "Particle/ExpellerBrokenParts.ptl");  // 字符串 “Particle/ExpellerBrokenParts.ptl”
  if ( operator new(0x84u) != nullptr )  // 堆分配 132 字节对象
    pObj = sub_5FE2C0(1120403456);  // 常量 100.0f
  else
    pObj = 0;
  (*(void (/*thiscall*/ **)(int, uint8_t *, uint8_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
    pObj,
    this,
    this,
    0,
    0,
    0,
    -1);
  result = *((uint32_t **)this + 2153);
  *((uint32_t *)this + 2188) = 1066192077;  // 浮点常量 1.1f
  *result = 900;
  *(uint32_t *)(*((uint32_t *)this + 2153) + 4) = 1400;  // this+8612〔uAI8612(推断)〕
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
int /*thiscall*/ sub_5D19C0(int **this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数定义: 状态事件总透传（架招退出 + 反击效果 30022）
{
  int result; // eax
  int v7; // eax
  int v8; // [esp-18h] [ebp-20h]
  int v9; // [esp-10h] [ebp-18h]

  result = ((int (/*thiscall*/ *)(int **))(*this)[184])(this);
  if ( result <= 0 || (result = ((int (/*thiscall*/ *)(int **))(*this)[210])(this)) != 14 || ArgList == 0 )  // 若 result <= 0 与/或 ArgList == 0
  {
    if ( ArgList == 14 && *((uint8_t *)this + 8669) == 1 )  // this+8669 守卫激活位
    {
      sub_4926A0(**(this + 1554));  // 帧游标复位（+44 帧数组；递归子链 +204）
      ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[49])(this, **(this + 1554));  // this+6216〔pTbl6216(推断)〕
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
    if ( *(this + 1639) == (int *)4 && ArgList == 0 )  // 判定 “+6556 大状态ID”
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
          result = sub_4E4A50(this, 30022, 0, v7, v8, 0, v9, 0, 0, 0);  // 结果 = 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
        }
      }
    }
    if ( *((uint8_t *)this + 8669) == 1 )  // this+8669 守卫激活位
      return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
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
int /*userpurge*/ sub_5D1AD0@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)  // 实现：光守卫闪耀：LIGHT_GUARD_SHINE + 光刃投射（61L）
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
    if ( *(int *)(pArg1 + 8840) < 3 )  // pArg1+8840〔uPhase8840(推断)〕
    {
      sub_4DB130(24, 1);  // 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      result = *(uint32_t *)(pArg1 + 8840) + 1;  // pArg1+8840〔uPhase8840(推断)〕
      *(uint32_t *)(pArg1 + 8840) = result;  // pArg1+8840〔uPhase8840(推断)〕
      *(uint32_t *)(pArg1 + 8844) = result;  // pArg1+8844〔uPhaseClock8844(推断)〕
    }
  }
  else
  {
    sub_5D19C0((int **)pArg1, ArgList, fArg4, nArg5, nArg6);  // 状态事件总透传（架招退出 + 反击效果 30022）
    if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 840))(pArg1, nArg2) == 8  // 虚函数调用 槽+840：大状态 getter（this+6556）
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 908))(pArg1) == 2 )  // 虚函数调用 槽+908：[RTTI: IRDActiveObject__vmt38C…
    {
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(  // 全局 dword_8F7C04 = 本机角色对象
        dword_8F7C04,  // 全局 dword_8F7C04 = 本机角色对象
        "LIGHT_GUARD_SHINE",  // 字符串 “LIGHT_GUARD_SHINE”
        -1,
        0);
      sub_4DB200(24, 2);  // 15% 概率随机文案触发（0x4DB130 的门包装）
      *(uint8_t *)(pArg1 + 8848) = 0;  // pArg1+8848〔bPhase8848(推断)〕
      sub_698F90(pArg1 + 8852, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pArg1 + 888))(pArg1, 4, 4, 1000, 1000);  // 虚函数调用 槽+888：速率设置链: a2/a3 经 vt+976 换算 →…
      v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 672))(pArg1, 3);  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
      v9 = (uint64_t)((double)*(int *)(pArg1 + 8916) / (double)sub_41A5E0(v8 + 872) * 1000.0);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v10 = *(int **)pArg1;
      v11 = *(uint32_t *)(pArg1 + 6216);  // pArg1+6216〔pTbl6216(推断)〕
      *(uint32_t *)(pArg1 + 8880) = v9;  // pArg1+8880〔uPhase8880(推断)〕
      v12 = ((int (/*fastcall*/ *)(int, uint32_t, uint32_t, uint32_t))v10[48])(pArg1, HIDWORD(v9), 0, 0);  // 调 取 64 位值高 32 位
      ((void (/*thiscall*/ *)(int, int, uint32_t, uint32_t, int))v10[51])(pArg1, 1, *(uint32_t *)(v11 + 20), 0, -v12);
      return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 820))(pArg1, 0);  // 虚函数调用 槽+820：写 +6740 字节
    }
    else
    {
      *(uint8_t *)(pArg1 + 8865) = 0;  // pArg1+8865〔bPhase8865(推断)〕
      *(uint8_t *)(pArg1 + 8866) = 0;  // pArg1+8866〔bPhase8866(推断)〕
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20));  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
      *((uint32_t *)dword_8F8528 + 623) = 0;  // 全局 dword_8F8528 = 消息/弹窗管理器
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 820))(pArg1, 1);  // 虚函数调用 槽+820：写 +6740 字节
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
int /*thiscall*/ sub_5D1C50(int *this, int nArg2, int nArg3, int nArg4, float fArg5)  // 函数定义: 透明度正弦淡出（sin 曲线，250 上限，0.5 秒窗口）
{
  uint64_t v6; // rax
  unsigned int pThis_8A5; // edi
  int fld_e2220; // eax  | +0x22B0 → 相位区槽（0x5CF740 清零；0x5D7100/0x5D7360 构造置 1）【推断】（CNGuardLight）
  uint8_t v9; // bl
  unsigned int v10; // edi
  int dword_79C0B02; // [esp-24h] [ebp-30h]

  LODWORD(v6) = sub_5CF520(this, nArg2, nArg3, nArg4, fArg5);  // 法术层绘制（通道 1 附着 / 通道 0 闪烁）
  if ( (uint8_t)nArg2 != 0 )
  {
    pThis_8A5 = sub_699000((int)(this + 2213));  // 【clock_now(clk)】
    LODWORD(v6) = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 虚调用 vt+840
    if ( (uint32_t)v6 == 8 )
    {
      LODWORD(v6) = (*(int (/*thiscall*/ **)(int *))(*this + 908))(this);  // 虚调用 vt+908
      if ( (uint32_t)v6 == 2 && pThis_8A5 != 0 )
      {
        LODWORD(v6) = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 虚调用 vt+200
        if ( (uint32_t)v6 != 0 )
        {
          fld_e2220 = *(this + 2220);  // this+8880〔uPhase8880〕
          if ( pThis_8A5 >= fld_e2220 )
          {
            v10 = pThis_8A5 - fld_e2220;
            if ( v10 >= 0x1F4 )
              v9 = 0;
            else
              v9 = (uint64_t)((1.0 - sin((double)v10 * 0.003141592)) * 250.0);  // 调 正弦
            LODWORD(v6) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));  // 虚调用 vt+208
          }
          else
          {
            v6 = (uint64_t)((double)pThis_8A5 * 250.0 / (double)fld_e2220);
            v9 = v6;
          }
          if ( v9 != 0 )
          {
            dword_79C0B02 = dword_79C0B0;  // 读 dword_79C0B0（文本/图像绘制对象）
            (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);  // 虚调用 vt+200
            LODWORD(v6) = sub_491DE0(dword_79C0B02, nArg3, nArg4, fArg5, 2, 1, -1, (v9 << 24) | 0xFFFFFF);  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
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
char /*thiscall*/ sub_5D1D90(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数定义: 事件 26/27/28 专用 + 总透传
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
    *(uint32_t *)(this + 8972) = v7;  // this+8972 事件档位
    *(uint32_t *)(this + 8976) = v7;  // this+8976 事件档位
    return sub_5CF880((int *)this);  // 加速状态施加（CONDITION_HASTE + 三参数放速）
  }
  if ( ArgList != 28 )
    return sub_5D19C0((int **)this, ArgList, fArg3, nArg4, nArg5);  // 状态事件总透传（架招退出 + 反击效果 30022）
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 944))(this, 1, 100000);  // this+944 名字已播出标志
  *(uint8_t *)(this + 8857) = 0;  // this+8857 相位标志
  *(uint8_t *)(this + 8858) = 0;  // this+8858 相位标志
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
void /*thiscall*/ sub_5D1E30(int *this, int nArg2, int nArg3, int nArg4, float fArg5)  // 函数定义: 光效链淡出驱动（子对象 ring 遍历，此帧比率映射）
{
  int fld_e2243; // eax  | +0x230C → 事件档位（事件 26→1、27→2；0x5D1D90）（CNGuardWind）
  int v8; // eax
  int fld_e1777; // eax  | +0x1BC4 → 出生复位槽（-1 哨兵；0x4D6970）（证据 va=004D6970）（IRDActiveObject·基类；va=004D6970）
  uint32_t *fld_e2227; // eax
  uint32_t *v11; // edi
  uint64_t fld_e22542; // rax  | +0x2338 → 阿莫尔相位第三段（0x5CF7F0 复位区 9012..9048）【推断】（CNGuardWind）
  int v13; // eax
  int v14; // eax
  int v15; // eax
  uint8_t fld_e225422; // [esp+1Bh] [ebp+Bh]
  float v17; // [esp+1Ch] [ebp+Ch]
  int v18; // [esp+20h] [ebp+10h]
  int fld_e2254; // [esp+24h] [ebp+14h]  | +0x2338 → 阿莫尔相位第三段（0x5CF7F0 复位区 9012..9048）【推断】（CNGuardWind）

  sub_5CF520(this, nArg2, nArg3, nArg4, fArg5);  // 法术层绘制（通道 1 附着 / 通道 0 闪烁）
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != 0 )  // 虚调用 vt+200
  {
    fld_e2243 = *(this + 2243);  // this+8972〔uEvtState8972〕
    if ( (uint8_t)nArg2 == 1 )
    {
      if ( fld_e2243 != 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 0 )  // 虚调用 vt+940
      {
        sub_4938F0(*(this + 2245));  // 调 调 sub_4938F0
        v8 = nArg4 + (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
        sub_491D00(dword_79C0B0, nArg3 + (LOBYTE(fArg5) != 0 ? 3 : -3), v8, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      }
    }
    else if ( fld_e2243 == 2 )
    {
      fld_e2254 = *(this + 2254);  // this+9016〔uPhaseC9016〕
      v17 = 1.0;
      (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);  // 虚调用 vt+200
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) != 1  // 虚调用 vt+940
        || (fld_e1777 = sub_699000((int)(this + 9)) - *(this + 1777)) <= 1000  // 【clock_now(clk)】
        && (v17 = (double)(int)sub_423A80(255, 0, fld_e1777, 1000) * 0.0039215689) != 0.0 )  // 同上 int 版（FTOL 截断）
      {
        fld_e2227 = (uint32_t *)*(this + 2227);  // this+8908〔uPhase8908〕
        v11 = (uint32_t *)*fld_e2227;
        if ( (uint32_t *)*fld_e2227 != fld_e2227 )
        {
          do
          {
            fld_e22542 = (uint64_t)((double)fld_e2254 * 150.0 / (double)*(this + 2254) * v17);  // this+9016〔uPhaseC9016〕
            fld_e225422 = fld_e22542;
            --fld_e2254;
            if ( (uint8_t)fld_e22542 == 0 )
              break;
            v13 = (*(int (/*thiscall*/ **)(int *))(*this + 36))(this);  // 结果 = 虚调用 vt+36
            v18 = sub_45E490(v11[2], *(uint32_t *)(v13 + 8));  // 结果 = 屏幕 y → 演出层坐标（减基线）
            v14 = (*(int (/*thiscall*/ **)(int *))(*this + 36))(this);  // 结果 = 虚调用 vt+36
            v15 = sub_45E4D0(v11[3], v11[4], *(uint32_t *)(v14 + 8), 1.0);  // 结果 = 带比例的回换算（nArg2 - nArg3*f + 120）
            sub_491DE0(dword_79C0B0, v18, v15, fArg5, 0, 0, 0, (fld_e225422 << 24) | 0xFFFFFF);  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
            v11 = (uint32_t *)*v11;
          }
          while ( v11 != (uint32_t *)*(this + 2227) );  // this+8908〔uPhase8908〕
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
int /*fastcall*/ sub_5D2020(uint8_t *pArg1, int nArg2, int ArgList, float fArg4, int nArg5, int nArg6)  // 函数定义: 状态播报分派（HASTE/SLOW 增速减速 + FIRE_GUARD_LAUGH）
{
  char v7; // bl
  void *v8; // ecx
  int result; // eax

  switch ( ArgList )  // 按 ArgList 分派
  {
    case 21:  // case 21 = ENUM_CMDPACKET_SORT_ITEM
    case 23:  // case 23 = ENUM_CMDPACKET_RENT_AVATAR
      if ( ArgList == 21 )
      {
        v7 = pArg1[8840] + 1;
        if ( (unsigned int)(uint8_t)pArg1[8840] + 1 >= 2 )
          v7 = 2;
        sub_4DB200(24, 1);  // 15% 概率随机文案触发（0x4DB130 的门包装）
        (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
          pArg1,
          "CONDITION_HASTE",  // 字符串 “CONDITION_HASTE”
          -1,
          0,
          0);
      }
      else
      {
        v7 = (pArg1[8840] - 1) & (((uint8_t)pArg1[8840] <= 1u) - 1);
        (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
          pArg1,
          "CONDITION_SLOW",  // 字符串 “CONDITION_SLOW”
          -1,
          0,
          0);
      }
      if ( v7 != pArg1[8840] )
      {
        LOBYTE(v8) = ArgList == 21;  // 调 取 16 位值低 8 位
        pArg1[8840] = v7;
        sub_5CFD80(pArg1, v8);  // 变速应用（档位倍率 + 位移 ±20 + 火焰特效）
      }
      goto LABEL_9;
    case 22:  // case 22 = ENUM_CMDPACKET_BUY_ITEM
LABEL_9:
      sub_41A590((unsigned int)(pArg1 + 8841), nArg2, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      result = sub_699000((int)(pArg1 + 36));  // 【clock_now(clk)】
      *((uint32_t *)pArg1 + 2217) = result;
      break;
    case 31:  // case 31 = ENUM_CMDPACKET_CHANGE_SKILLSLOT
      sub_4DB130(24, 2);  // 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      result = (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
                 pArg1,
                 "FIRE_GUARD_LAUGH",  // 字符串 “FIRE_GUARD_LAUGH”
                 -1,
                 0,
                 0);
      break;
    default:
      result = sub_5D19C0((int **)pArg1, ArgList, fArg4, nArg5, nArg5);  // 结果 = 状态事件总透传（架招退出 + 反击效果 30022）
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
int /*thiscall*/ sub_5D2140(void *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数定义: 事件 14 架招退出 + 事件 8 攻击起始随机化
{
  int result; // eax
  int nRand; // eax
  int v8; // et2

  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this) <= 0  // 虚函数调用 槽+736：属性块首值（GetHP 族，此处索引）
    || (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) != 14  // 虚函数调用 槽+840：大状态 getter（this+6556）
    || (result = ArgList, ArgList == 0)
    || ArgList == 9 )
  {
    result = ArgList;
    if ( ArgList == 14 )
    {
      if ( *((uint8_t *)this + 8669) != 1 )  // this+8669 守卫激活位
        return result;
      sub_4926A0(**((uint32_t **)this + 1554));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, **((uint32_t **)this + 1554));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      result = (*(int (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
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
      *((uint8_t *)this + 8836) = rand() % 100 < 30;  // 调 取伪随机数
      if ( sub_41A5E0((unsigned int)this + 7028) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        result = sub_41A5E0((unsigned int)this + 7028);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        if ( result == 1 )
        {
          *((uint32_t *)this + 2206) = 0;  // this+8824〔uCharge8824〕
        }
        else
        {
          result = sub_41A5E0((unsigned int)this + 7028);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          if ( result == 3 )
          {
            *((uint8_t *)this + 8829) = 0;  // this+8829 蓄雷复位字节
            *((uint32_t *)this + 2208) = 0;  // this+8832〔uCharge8832〕
          }
        }
      }
      else
      {
        nRand = rand();  // 调 取伪随机数
        v8 = nRand % 100;
        result = nRand / 100;
        if ( v8 < 10 )
          *((uint8_t *)this + 8828) = 1;
      }
    }
    if ( *((uint8_t *)this + 8669) == 1 )  // this+8669 守卫激活位
      return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
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
int /*thiscall*/ sub_5D2270(void *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：与 ·sub_5D2140 同构（差异：无事件 8 分支）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this);  // 虚函数调用 槽+736：属性块首值（GetHP 族，此处索引）
  if ( result <= 0
    || (result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this)) != 14  // 虚函数调用 槽+840：大状态 getter（this+6556）
    || ArgList == 0
    || ArgList == 9 )
  {
    if ( ArgList == 14 )
    {
      if ( *((uint8_t *)this + 8669) != 1 )  // this+8669 守卫激活位
        return result;
      sub_4926A0(**((uint32_t **)this + 1554));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, **((uint32_t **)this + 1554));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      result = (*(int (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
                 this,
                 1,
                 0,
                 0,
                 0,
                 0,
                 0);
    }
    if ( *((uint8_t *)this + 8669) == 1 )  // this+8669 守卫激活位
      return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
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
int /*thiscall*/ sub_5D2320(uint32_t *this)  // 函数定义: 斧驱逐者破碎 2：装载 + 应用目标帧
{
  uint32_t *pThis_5B; // eax

  *(this + 2176) = -1;  // this+8704〔pSegNameTbl8704(推断)〕
  *(this + 2177) = -1;  // this+8708〔pCandTbl8708(推断)〕
  *(this + 2178) = -1;  // this+8712〔nCandTblEnd8712(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 虚调用 vt+1308
  if ( *(this + 96) < 0x10u )  // 判定 “+384 SSO容量”
    pThis_5B = this + 91;
  else
    pThis_5B = (uint32_t *)*(this + 91);  // this+364〔pAnimNameStr(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(  // 虚调用 vt+1352
    this,
    pThis_5B,
    "Particle/AxeExpellerBrokenParts.ptl");  // 字符串 “Particle/AxeExpellerBrokenParts.ptl”
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 16));  // 虚调用 vt+196
}



// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x5D2380 sub_5D2380 —— 破碎尺寸插值（0..30 帧间 ·sub_4049C0 线性插值）
// 取 vt+1172（插值 t）与 vt+384 双参（无参 + 9 号参数 = 起止），经 ·sub_4049C0
// 插值后 /100 得缩放 v8（0.01 量化）；vt+688 先置 1.0 复位、·sub_4EB4B0(10.0)
// 再置回、·sub_4EB2C0(v8) 提交主速率，最后遍历 this+8624 起 6 个子槽
// （·sub_4EB6E0(1.0) + ·sub_4EB6A0(v8)）逐子对象同步破碎缩放。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2380(uint32_t *this)  // 实现：破碎尺寸插值（0..30 帧间 ·sub_4049C0 线性插值）
{
  int v2; // edi
  int result; // eax
  uint32_t *pThis_86C; // esi
  int i; // ebx
  float v6; // [esp+4h] [ebp-28h]
  float v7; // [esp+8h] [ebp-24h]
  float v8; // [esp+24h] [ebp-8h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1172))(this);  // 结果 = 虚调用 vt+1172
  v7 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);  // 结果 = 虚调用 vt+384
  v6 = (float)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 9);  // 结果 = 虚调用 vt+384
  v8 = (double)(int)(uint64_t)sub_4049C0(v6, v7, v2, 30) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 688))(this, 1065353216);  // 虚调用 vt+688
  sub_4EB4B0(COERCE_FLOAT(10));  // 与 ·0x4EB2C0 同构（差异：·sub_4923F0 按倒数缩放）
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);  // 虚调用 vt+688
  result = sub_4EB2C0(v8);  // 结果 = 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  pThis_86C = this + 2156;
  for ( i = 6; i != 0; --i )  // 循环：i 从 6 递减到 0
  {
    if ( *pThis_86C != 0 )
    {
      sub_4EB6E0(1.0);  // 与 ·0x4EB6A0 同构（差异：调 ·0x4EB4B0）
      result = sub_4EB6A0(v8);  // 结果 = this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
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
uint32_t **/*thiscall*/ sub_5D2440(uint32_t *this)  // 相位记录环摘除（this+2226 槽）
{
  int fld_e1; // ecx
  uint32_t **result; // eax

  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  result = *(uint32_t ***)(fld_e1 + 4);
  if ( result != (uint32_t **)fld_e1 )
  {
    *result[1] = *result;
    (*result)[1] = result[1];
    j__free(result);  // 调 堆释放
    result = (uint32_t **)(*(this + 2) - 1);  // this+8〔nSkillRec8(推断)〕
    *(this + 2) = result;  // 写 this+8 = result（技能槽记录首字）
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
char /*thiscall*/ sub_5D2470(int this)  // 函数定义: 受击挂件清理 + 守卫帧收尾（本区多个 AI 的公共尾段）
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

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 2) != 0 )  // 虚函数调用 槽+776：异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
  {
    pThis_304 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 772))(this, 2);  // this+772 参数槽
    (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pThis_304 + 4))(pThis_304, 0, this);  // this+4 宿主对象
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 11) != 0 )  // 虚函数调用 槽+776：异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
  {
    pThis_3042 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 772))(this, 11);  // this+772 参数槽
    (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pThis_3042 + 4))(pThis_3042, 0, this);  // this+4 宿主对象
  }
  for ( i = 0; ; ++i )
  {
    pThis_2BC = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);  // this+700 表现/名字快照[20] 字节槽
    v6 = *(uint32_t *)(pThis_2BC + 4);  // this+4 宿主对象
    v7 = v6 != 0 ? (*(uint32_t *)(pThis_2BC + 8) - v6) >> 2 : 0;  // this+8 物品 id
    if ( (int)i >= v7 )
      break;
    pThis_2BC2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);  // this+700 表现/名字快照[20] 字节槽
    v9 = *(uint32_t *)(pThis_2BC2 + 4);  // this+4 宿主对象
    if ( v9 != 0 && i < (*(uint32_t *)(pThis_2BC2 + 8) - v9) >> 2 )  // this+8 物品 id
      v10 = *(uint32_t *)(v9 + 4 * i);
    else
      v10 = 0;
    if ( *(uint32_t *)(v10 + 4) == this )
    {
      pThis_2BC3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);  // this+700 表现/名字快照[20] 字节槽
      v12 = *(uint32_t *)(pThis_2BC3 + 4);  // this+4 宿主对象
      if ( v12 != 0 && i < (*(uint32_t *)(pThis_2BC3 + 8) - v12) >> 2 )  // this+8 物品 id
        v13 = *(uint32_t *)(v12 + 4 * i);
      else
        v13 = 0;
      v14 = __RTDynamicCast(v13, 0, &IRDAppendage `RTTI Type Descriptor', &CNChangeHp `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      if ( v14 != 0 && *(float *)(v14 + 80) < 0.0 )
      {
        v17 = v14;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);  // this+700 表现/名字快照[20] 字节槽
        sub_53FE50(v17);
      }
    }
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);  // this+1332 装备/动画定义对象
  sub_5CF180((uint32_t *)this);  // 环绕音管理
  LOBYTE(pThis_348) = 1;  // 调 取 16 位值低 8 位
  if ( *(uint8_t *)(this + 8669) == 1 && *(uint8_t *)(this + 8603) == 0 && *(uint8_t *)(this + 8601) == 1 )  // 判定 “+8669 守卫激活位”
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 虚函数调用 槽+840：大状态 getter（this+6556）
    if ( pThis_348 == 0 )
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);  // 虚函数调用 槽+1344
  }
  return pThis_348;
}



// AI 字段访问（this+8723）
// ------------------------------------------------------------
// 0x5D25D0 sub_5D25D0 —— 自动守卫参数装载（vt+384 出场参数面 0..10 号）
// vt+1308 复位后按索引 0..10 读 vt+384，写入 8968..9008 参数面（8968/8988 两处 ×0.01 缩放）。
// 8612 双元槽写 1000/1600，清 8723 与 +1905 对象 +96 位，8840 时钟按 1000ms 起计时。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D25D0(float *this)  // 函数定义: 自动守卫参数装载（vt+384 出场参数面 0..10 号）
{
  double fRate0; // st7
  int nVt1; // eax
  double fRate5; // st7
  int nParam1; // eax
  float fVtBase1; // edx
  int nParam3; // eax
  float fVtBase2; // edx
  int nParam5; // eax
  float fVtBase3; // edx
  int nParam7; // eax
  float fVtBase4; // edx
  int nParam9; // eax
  float fVtBase5; // edx
  uint8_t *pFlag96; // eax

  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 1308))(this);  // 相位复位
  fRate0 = (double)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);  // 参数0
  nVt1 = *(uint32_t *)this;
  fRate5 = fRate0 * 0.0099999998;  // ×0.01（百分数→系数）
  *(this + 2242) = fRate5;  // 8968：虚弱血量比阈值【推断】
  *(this + 2188) = fRate5;  // 8752：同值备份（震地半径系数，·0x5D5F10 消费）
  nParam1 = (*(int (/*thiscall*/ **)(float *, int))(nVt1 + 384))(this, 1);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  fVtBase1 = *this;
  *((uint32_t *)this + 2243) = nParam1;  // 8972：冷却时长
  *((uint32_t *)this + 2244) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(fVtBase1) + 384))(this, 2);  // 8976：技能 id
  nParam3 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);  // this+384 【推断】动画件名 SSO 容量判据
  fVtBase2 = *this;
  *((uint32_t *)this + 2245) = nParam3;  // 8980：随从数量上限
  *((uint32_t *)this + 2246) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(fVtBase2) + 384))(this, 4);  // 8984：恢复时长
  nParam5 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 5);  // this+384 【推断】动画件名 SSO 容量判据
  fVtBase3 = *this;
  *(this + 2247) = (double)nParam5 * 0.0099999998;  // 8988：血量比阈值（×0.01）
  *((uint32_t *)this + 2248) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(fVtBase3) + 384))(this, 6);  // 8992：段时长
  nParam7 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 7);  // this+384 【推断】动画件名 SSO 容量判据
  fVtBase4 = *this;
  *((uint32_t *)this + 2249) = nParam7;  // 8996：范围打击参数A
  *((uint32_t *)this + 2250) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(fVtBase4) + 384))(this, 8);  // 9000：范围打击参数B
  nParam9 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 9);  // this+384 【推断】动画件名 SSO 容量判据
  fVtBase5 = *this;
  *((uint32_t *)this + 2251) = nParam9;  // 9004：身高限制
  *((uint32_t *)this + 2252) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(fVtBase5) + 384))(this, 10);  // 9008：帧游标分档参数
  **((uint32_t **)this + 2153) = 1000;  // 8612 双元槽 0=1000
  *(uint32_t *)(*((uint32_t *)this + 2153) + 4) = 1600;  // 8612 双元槽 1=1600
  pFlag96 = (uint8_t *)(*((uint32_t *)this + 1905) + 96);  // 子对象标志位
  *((uint8_t *)this + 8723) = 0;
  *pFlag96 = 0;
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
int /*userpurge*/ sub_5D2710@<eax>(int pArg1@<ecx>, int nArg2@<edi>, int ArgList, float fArg4, int nArg5, int nArg6)  // 实现：锤王三连段播报（HAMMER_KING_01/02/03）
{
  int nSegIdx; // eax
  const char *pszTag; // eax
  bool bIsSeg1; // zf
  uint32_t *pStkObj; // edi
  int nBaseOffset; // eax
  int nSpanRaw; // eax
  uint64_t nSpanMs; // rax
  int nSegNext; // ecx
  int pPanel; // eax
  int *pVt; // [esp+18h] [ebp+14h]

  sub_5D19C0((int **)pArg1, ArgList, fArg4, nArg5, nArg6);  // 状态事件总透传（架招退出 + 反击效果 30022）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 8  // 姿态 8=崩地
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 908))(pArg1) == 3 )  // 相位 3=落地帧
  {
    sub_4DB130(24, *(uint32_t *)(pArg1 + 8932) + 2);  // 喊话音（24 组，段号+2）
    nSegIdx = *(uint32_t *)(pArg1 + 8932);  // pArg1+8932〔nComboSeg8932(推断)〕
    if ( nSegIdx != 0 )
    {
      bIsSeg1 = nSegIdx == 1;
      pszTag = "HAMMER_KING_02";  // 段1
      if ( !bIsSeg1 )
        pszTag = "HAMMER_KING_03";  // 段2 及以上
    }
    else
    {
      pszTag = "HAMMER_KING_01";  // 段0 起手
    }
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 212))(  // 全局 dword_8F7C04 = 本机角色对象
      dword_8F7C04,  // 全局 dword_8F7C04 = 本机角色对象
      pszTag,
      -1,
      0,
      0,
      nArg2);
    *(uint8_t *)(pArg1 + 8924) = 0;  // 本轮震地门复位
    *(uint8_t *)(pArg1 + 8881) = 0;  // pArg1+8881〔bFlag8881(推断)〕
    *(uint8_t *)(pArg1 + 8882) = 0;  // pArg1+8882〔bFlag8882(推断)〕
    sub_698F90(pArg1 + 8868, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pArg1 + 888))(pArg1, 4, 4, 1000, 1000);  // vt+888 参数(4,4,1000,1000)
    sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));  // 帧游标复位（+44 帧数组；递归子链 +204）
    pStkObj = (uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4);  // 动作子对象
    pVt = *(int **)pArg1;
    nBaseOffset = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 192))(pArg1, 0, 0);  // 虚函数调用 槽+192
    ((void (/*thiscall*/ *)(int, int, uint32_t, uint32_t, int))pVt[51])(pArg1, 1, *pStkObj, 0, -nBaseOffset);  // vt+204 设动作（含 -基线偏移）
    nSpanRaw = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 672))(pArg1, 3);  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
    nSpanMs = (uint64_t)((double)*(int *)(pArg1 + 8992) / (double)sub_41A5E0(nSpanRaw + 872) * 1000.0);  // 段时长 = 9008 表值 / 帧长 ×1000ms
    nSegNext = *(uint32_t *)(pArg1 + 8932) + 1;  // pArg1+8932〔nComboSeg8932(推断)〕
    *(uint32_t *)(pArg1 + 8928) = nSpanMs;  // 本节拍
    *(uint32_t *)(pArg1 + 8932) = nSegNext;  // 段号自增
    if ( nSegNext == 3 )  // 满三段：回段0，清相位与子标志，重排 9008 冷却
    {
      pPanel = *(uint32_t *)(pArg1 + 7620);  // pArg1+7620〔pStatusPanel(推断)〕
      *(uint32_t *)(pArg1 + 8932) = 0;  // pArg1+8932〔nComboSeg8932(推断)〕
      *(uint8_t *)(pPanel + 96) = 0;
      *(uint8_t *)(pArg1 + 8953) = 0;  // pArg1+8953〔bPhase8953(推断)〕
      *(uint8_t *)(pArg1 + 8954) = 0;  // pArg1+8954〔bPhase8954(推断)〕
      sub_698F90(pArg1 + 8940, *(uint32_t *)(pArg1 + 9008), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 820))(pArg1, 0);  // 虚函数调用 槽+820：写 +6740 字节
  }
  else  // 非崩地落地帧：清表现并令 vt+820(1) 收尾
  {
    *(uint8_t *)(pArg1 + 8881) = 0;  // pArg1+8881〔bFlag8881(推断)〕
    *(uint8_t *)(pArg1 + 8882) = 0;  // pArg1+8882〔bFlag8882(推断)〕
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 820))(pArg1, 1);  // 虚函数调用 槽+820：写 +6740 字节
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
char /*usercall*/ sub_5D28D0@<al>(int pArg1@<ecx>, int nArg2@<edi>)  // 实现：多段扇形散射门（血量比阈值 + 时钟）
{
  uint64_t nRet; // rax
  int nMaxHp; // eax
  int nPhaseIdx; // ecx
  int nPhaseIdx2; // eax
  int nNow; // eax
  unsigned int nBreathPeriod; // ecx
  unsigned int nElapsed; // eax
  int nMapX; // edi
  int nMapX2; // edi
  float nSelfVt; // edi
  int nAtkReq; // eax
  int nCoord1; // eax
  int nCoord2; // eax
  int nDestX; // eax
  float fCurHp; // [esp+4h] [ebp-8h]
  float fHpRatio; // [esp+8h] [ebp-4h]

  sub_5D2470(pArg1);  // 受击挂件清理 + 守卫帧收尾（本区多个 AI 的公共尾段）
  LOBYTE(nRet) = *(uint8_t *)(pArg1 + 7801);  // 调 取 16 位值低 8 位
  if ( (uint8_t)nRet == 0 )
    *(uint32_t *)(pArg1 + 8752) = 1065353216;  // 常量 1.0f
  if ( *(uint32_t *)(pArg1 + 8700) == -1 )  // pArg1+8700〔uPhase8700(推断)〕
  {
    fCurHp = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 736))(pArg1);  // 虚函数调用 槽+736：属性块首值（GetHP 族，此处索引）
    nMaxHp = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 740))(pArg1);  // 虚函数调用 槽+740：属性块 +4 浮点壳（GetHP 族）
    nPhaseIdx = *(uint32_t *)(pArg1 + 8840);  // pArg1+8840〔uPhase8840(推断)〕
    fHpRatio = fCurHp / (double)nMaxHp;
    if ( fHpRatio < (double)*(float *)(pArg1 + 4 * nPhaseIdx + 8884)
      && nPhaseIdx == *(uint32_t *)(pArg1 + 8844)  // pArg1+8844〔uPhaseClock8844(推断)〕
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) == 1  // 虚函数调用 槽+308
      && *(uint8_t *)(pArg1 + 7801) == 1  // pArg1+7801〔bActiveRender(推断)〕
      && *(int *)(pArg1 + 8840) < 3  // pArg1+8840〔uPhase8840(推断)〕
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) != 5 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
    {
      nPhaseIdx2 = *(uint32_t *)(pArg1 + 8840);  // pArg1+8840〔uPhase8840(推断)〕
      ++*(uint32_t *)(pArg1 + 8844);  // pArg1+8844〔uPhaseClock8844(推断)〕
      sub_5D0CC0((float *)pArg1, *(uint32_t *)(pArg1 + 4 * nPhaseIdx2 + 8900));  // 多段投射物扇形布点（nArg2 ≤ 5 段）
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 32, 0, 2, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 564))(pArg1);  // 虚函数调用 槽+564：位移同步包 vt+234（会话 3 定案：UDP type=5）
    }
    *(uint8_t *)(*(uint32_t *)(pArg1 + 7620) + 64) = (double)*(int *)(pArg1 + 8924) >= fHpRatio;  // pArg1+7620〔pStatusPanel(推断)〕
    LODWORD(nRet) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);  // 虚函数调用 槽+840：大状态 getter（this+6556）
    if ( (uint32_t)nRet == 8 )
    {
      LODWORD(nRet) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 908))(pArg1);  // 虚函数调用 槽+908：[RTTI: IRDActiveObject__vmt38C…
      if ( (uint32_t)nRet == 2 )
      {
        if ( sub_699000(pArg1 + 8852) <= *(uint32_t *)(pArg1 + 8880) )  // 【clock_now(clk)】
        {
          LOBYTE(nRet) = (uint8_t)dword_8F8528;  // 全局 dword_8F8528 = 消息/弹窗管理器
          *((uint32_t *)dword_8F8528 + 623) = 0;  // 全局 dword_8F8528 = 消息/弹窗管理器
        }
        else
        {
          nNow = sub_699000(pArg1 + 8852);  // 【clock_now(clk)】
          nBreathPeriod = *(uint32_t *)(pArg1 + 8920);  // pArg1+8920〔uPhase8920(推断)〕
          nElapsed = nNow - *(uint32_t *)(pArg1 + 8880);  // pArg1+8880〔uPhase8880(推断)〕
          if ( nElapsed >= nBreathPeriod )
            LOBYTE(nRet) = 0;  // 调 取 16 位值低 8 位
          else
            nRet = (uint64_t)(sin((double)(nBreathPeriod + nElapsed) * 6.2831841 / (double)(int)(4 * nBreathPeriod)) * 250.0);  // 调 正弦
          *((uint32_t *)dword_8F8528 + 623) = (uint8_t)nRet;  // 全局 dword_8F8528 = 消息/弹窗管理器
          LOBYTE(nRet) = *(uint8_t *)(pArg1 + 8848);  // 调 取 16 位值低 8 位
          if ( (uint8_t)nRet == 0 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 608))(dword_8F7C04, nArg2) == 1 )  // 全局 dword_8F7C04 = 本机角色对象
            {
              if ( (nMapX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04),  // 全局 dword_8F7C04 = 本机角色对象
                    (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) >= nMapX)  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 152))(dword_8F7C04) == 1  // 全局 dword_8F7C04 = 本机角色对象
                || (nMapX2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04),  // 全局 dword_8F7C04 = 本机角色对象
                    (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) < nMapX2)  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 152))(dword_8F7C04) == 0 )  // 全局 dword_8F7C04 = 本机角色对象
              {
                (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)dword_8F7C04 + 764))(  // 全局 dword_8F7C04 = 本机角色对象
                  dword_8F7C04,  // 全局 dword_8F7C04 = 本机角色对象
                  3,
                  *(uint32_t *)(pArg1 + 8928),
                  pArg1,
                  0);
              }
            }
            (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 764))(  // 全局 dword_8F7C04 = 本机角色对象
              dword_8F7C04,  // 全局 dword_8F7C04 = 本机角色对象
              6,
              *(uint32_t *)(pArg1 + 8928),
              pArg1);
            nSelfVt = *(float *)pArg1;
            nAtkReq = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04  // 全局 dword_8F7C04 = 本机角色对象
                                                                                                 + 124))(  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
                    dword_8F7C04,  // 全局 dword_8F7C04 = 本机角色对象
                    30311,
                    0,
                    0,
                    4,
                    100,
                    2,
                    0,
                    0);
            nCoord1 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04, nAtkReq);  // 全局 dword_8F7C04 = 本机角色对象
            nCoord2 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 124))(dword_8F7C04, 0, nCoord1);  // 全局 dword_8F7C04 = 本机角色对象
            nDestX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04, nCoord2);  // 全局 dword_8F7C04 = 本机角色对象
            (*(void (/*thiscall*/ **)(int, int))(LODWORD(nSelfVt) + 584))(pArg1, nDestX);  // 虚函数调用 槽+584：动作数据包发布（会话 3 定案：类型 48012 + 0x6E 字节
            LOBYTE(nRet) = sub_424120(*(uint32_t **)(*(uint32_t *)(pArg1 + 116) + 132), 3, *(uint32_t *)(pArg1 + 8920));  // [shake screen] 标签入口（解析器 sub_502F00 调用，全库 36 调用
            *(uint8_t *)(pArg1 + 8848) = 1;  // pArg1+8848〔bPhase8848(推断)〕
          }
        }
      }
    }
  }
  return nRet;
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
int /*thiscall*/ sub_5D2BB0(int this)  // 函数定义: 冰守卫交互事件响应（R_ICE_GUARD）
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

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v13 = -1;
  result = sub_4DC630();  // 结果 = 关卡/交互事件包处理（关联对象 this+7260 校验）
  if ( result != -1 )
  {
    if ( result == 15 )
    {
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v12);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v14);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      v3 = sub_45EBE0(v12, v14);  // 调 存 id 对 → 对象查找
      if ( __RTDynamicCast(v3, 0, &CNRDObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0) != 0 )  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      {
        v4 = 16;
        while ( 1 )  // 无限循环
        {
          v5 = *(uint32_t **)(v4 + dword_8F850C);  // 全局 dword_8F850C = 房间/席位表
          if ( v5 != nullptr )  // 若 v5 有效（非空）
          {
            pObj = v5[49];
            if ( pObj != 0 )
            {
              v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);  // 虚函数调用 槽+48：更新槽（64A5A0 + 41C5E0/52E4D0）
              if ( v7 == v12 )
              {
                v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v5[49] + 52))(v5[49]);  // 虚函数调用 槽+52：播 AURA_SHIELD_LOOP（第二挂点，15 行）
                if ( v8 == v14 )
                  break;
              }
            }
          }
          v4 += 4;
          if ( v4 >= 32 )
            goto LABEL_18;
        }
        if ( *(uint8_t *)(this + 8868) == 0 )  // this+8868 冰守卫交互门
        {
          if ( v5[10] < 0x10u )
            v9 = v5 + 5;
          else
            v9 = (uint32_t *)v5[5];
          v11 = v9;
          fld_2014 = (const char *)sub_41ACF0(*(uint32_t *)(this + 8212) + 4);  // 结果 = 驻留串句柄 → 字符串指针
          sprintf(Buffer, fld_2014, v11);  // 调 格式化到缓冲
          sub_4D9F00(Buffer);  // 调 写提示、·sub_4D84F0 头顶气泡
        }
        sub_4D84F0(0, 0);  // 头顶气泡 ”CommandReceive.ani”（同 0x4D82D0 结构）
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v5[49] + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
          v5[49],
          "R_ICE_GUARD",  // 字符串 “R_ICE_GUARD”
          -1,
          0,
          0);
      }
LABEL_18:
      *(uint8_t *)(this + 8868) = 0;  // this+8868 冰守卫交互门
      *(uint8_t *)(this + 8853) = 0;  // this+8853 相位标志
      *(uint8_t *)(this + 8854) = 0;  // this+8854 相位标志
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
int /*thiscall*/ sub_5D2D50(uint32_t *this, int nArg2, int pArg3, int nArg4)  // 函数定义: 暗黑火命中装配（CNFireBomb 挂件 + 42004 效果）
{
  int nArg22; // ebx
  int pAtkObj; // eax
  int pAtkObj2; // esi
  void *pDmgRet; // eax
  double fld_e2231; // st7
  double fDmgScaled; // st7
  float v11; // eax
  float v12; // edx
  int v13; // eax
  int v14; // edx
  int v15; // eax
  int nSelfX; // eax
  unsigned int i; // ebx
  int nAppend; // eax
  int nBegin1; // ecx
  int nCount1; // eax
  int nAppend2; // eax
  int nBegin2; // ecx
  int pNode; // ecx
  int nAppend3; // eax
  int nBegin3; // ecx
  int pNode2; // ecx
  void *pBomb; // eax
  int *pFireBomb; // eax
  int nVt1; // edx
  int nHitX; // [esp-1Ch] [ebp-58h]
  int nHitZ; // [esp-18h] [ebp-54h]
  int nHitY; // [esp-Ch] [ebp-48h]
  int nHitFlag; // [esp-8h] [ebp-44h]
  float fPtX; // [esp+8h] [ebp-34h] BYREF
  float fPtY; // [esp+Ch] [ebp-30h]
  float fPtZ; // [esp+10h] [ebp-2Ch]
  int nPadA; // [esp+14h] [ebp-28h]
  int nPadB; // [esp+18h] [ebp-24h]
  int nPadC; // [esp+1Ch] [ebp-20h]
  uint8_t v41[4]; // [esp+20h] [ebp-1Ch] BYREF
  void *pSearch; // [esp+24h] [ebp-18h]
  int nHitRatio; // [esp+28h] [ebp-14h] BYREF
  char v44; // [esp+2Fh] [ebp-Dh] BYREF
  int nFreeState; // [esp+38h] [ebp-4h]

  nArg22 = nArg2;
  if ( nArg2 != 0 )
  {
    pAtkObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // vt+576 取攻击归属对象
    pAtkObj2 = pAtkObj;
    if ( pAtkObj != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pAtkObj + 40))(pAtkObj, 17) != 0 )  // 玩家门
    {
      if ( *((uint8_t *)this + 8840) == 2 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 1 )  // 相位2 且存活
      {
        pDmgRet = (void *)(*(int (/*thiscall*/ **)(uint32_t *, char *, uint8_t *, int, int, int, uint32_t))(*this + 628))(  // 结果 = 虚调用 vt+628
                       this,
                       &v44,
                       v41,
                       100,
                       nArg2,
                       pArg3,
                       0);  // vt+628 伤害公式
        fld_e2231 = (double)(int)*(this + 2231);  // 2231 号比率槽
        pSearch = pDmgRet;
        fDmgScaled = fld_e2231 * 0.0099999998 * (double)(int)pDmgRet;  // ×0.01×伤害
        if ( fDmgScaled < 1.0 )
          fDmgScaled = 1.0;  // 伤害下限 1
        v11 = *(float *)(pArg3 + 4);  // pArg3+4〔宿主对象〕
        fPtX = *(float *)pArg3;
        v12 = *(float *)(pArg3 + 8);  // pArg3+8〔nSkillRec8(推断)〕
        fPtY = v11;
        v13 = *(uint32_t *)(pArg3 + 12);  // pArg3+12〔nSkillRec12(推断)〕
        fPtZ = v12;
        v14 = *(uint32_t *)(pArg3 + 16);  // pArg3+16〔nChannelTypeSel(推断)〕
        nPadA = v13;
        v15 = *(uint32_t *)(pArg3 + 20);  // pArg3+20〔nPage(推断)〕
        nHitRatio = 0;
        nPadB = v14;
        nPadC = v15;
        pSearch = (void *)(rand() % 60 - 30);  // ±30 抖动
        fPtX = (double)(int)pSearch + fPtX;
        pSearch = (void *)(rand() % 60 - 30);  // 调 取伪随机数
        fPtY = (double)(int)pSearch + fPtY;
        pSearch = (void *)(rand() % 60 - 30);  // 调 取伪随机数
        fPtZ = (double)(int)pSearch + fPtZ;
        nHitFlag = sub_605840(&nHitRatio, pAtkObj2, &fPtX, 0);  // 命中判定
        nHitY = nHitRatio;
        nHitZ = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAtkObj2 + 128))(pAtkObj2);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
        nHitX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAtkObj2 + 124))(pAtkObj2);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        nSelfX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAtkObj2 + 120))(pAtkObj2);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        sub_4E4A50((int)this, (int)this, 42004, (uint64_t)fDmgScaled, nSelfX, nHitX, nHitZ, 1, 0, nHitY, nHitFlag);  // 42004 号效果
        nArg22 = nArg2;
      }
      if ( *(this + 2175) == -1 )  // 暗黑火挂件槽空闲
      {
        i = 0;
        pSearch = nullptr;
        while ( 1 )  // 遍历 vt+700 挂件表找 CNFireBomb
        {
          nAppend = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAtkObj2 + 700))(pAtkObj2);  // 虚函数调用 槽+700：读 +6296 槽
          nBegin1 = *(uint32_t *)(nAppend + 4);
          nCount1 = nBegin1 != 0 ? (*(uint32_t *)(nAppend + 8) - nBegin1) >> 2 : 0;  // 向量元素数 = (end−begin)/4
          if ( (int)i >= nCount1 )
            break;
          nAppend2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAtkObj2 + 700))(pAtkObj2);  // 虚函数调用 槽+700：读 +6296 槽
          nBegin2 = *(uint32_t *)(nAppend2 + 4);
          if ( nBegin2 != 0 && i < (*(uint32_t *)(nAppend2 + 8) - nBegin2) >> 2 )  // 向量元素数 = (end−begin)/4
            pNode = *(uint32_t *)(nBegin2 + 4 * i);
          else
            pNode = 0;
          if ( *(uint32_t *)(pNode + 4) == pAtkObj2 )  // 回指校验
          {
            nAppend3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAtkObj2 + 700))(pAtkObj2);  // 虚函数调用 槽+700：读 +6296 槽
            nBegin3 = *(uint32_t *)(nAppend3 + 4);
            if ( nBegin3 != 0 && i < (*(uint32_t *)(nAppend3 + 8) - nBegin3) >> 2 )  // 向量元素数 = (end−begin)/4
              pNode2 = *(uint32_t *)(nBegin3 + 4 * i);
            else
              pNode2 = 0;
            pBomb = (void *)__RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                            pNode2,
                            0,
                            &IRDAppendage `RTTI Type Descriptor',
                            &CNFireBomb `RTTI Type Descriptor',
                            0);
            pSearch = pBomb;
            if ( pBomb != nullptr )  // 若 pBomb 有效（非空）
            {
              if ( (uint8_t)sub_64D310(pBomb) == 1  // 暗黑火就绪
                && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pAtkObj2 + 308))(pAtkObj2) == 1 )  // 虚函数调用 槽+308
              {
                (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t))(*this + 560))(this, 31, 0, 2, 0);  // 反应态 31
                (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);  // 虚调用 vt+564
              }
              break;
            }
          }
          ++i;
        }
        if ( pSearch == nullptr )  // 未找到：新建暗黑火
        {
          pSearch = operator new(0x1C0u);  // 堆分配 448 字节对象
          nFreeState = 0;
          if ( pSearch != nullptr )  // 若 pSearch 有效（非空）
            pFireBomb = (int *)sub_64D6A0(*(this + 2232), *(this + 2233), *(this + 2234));  // 装配（三参数面）
          else
            pFireBomb = nullptr;
          nVt1 = *pFireBomb;
          nFreeState = -1;
          (*(void (/*thiscall*/ **)(int *, int, uint32_t *, uint32_t, uint32_t, int, int))(nVt1 + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
            pFireBomb,
            pAtkObj2,
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
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14 && (uint8_t)nArg4 == 0 )  // 姿态14：反击收手
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 1336))(this, nArg22, pArg3, 0);  // 虚调用 vt+1336
  return sub_5CEFF0(nArg22, pArg3, nArg4);  // 法杖命中
}


// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D3060 sub_5D3060 —— 军团驱逐者号令复位（this+29 子表扫描）
// 遍历 this+29 容器，vt+40(obj,529) 过滤后 RTTI 到 IRDMonster 再定到 CNSoldier，
// 非自身的 CNSoldier 逐个交 ·sub_5CF0F0（军团兄弟单位联动收尾）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3060(int *this)  // 函数定义: 军团驱逐者号令复位（this+29 子表扫描）
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

  result = *(this + 29);  // 读 result = this+116（观察者容器）
  if ( result != 0 )  // 若结果非 0（成功）
  {
    for ( i = 0; ; ++i )
    {
      fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
      v5 = *(uint32_t *)(fld_e29 + 8);
      result = v5 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)i >= result )
        break;
      v6 = *(uint32_t *)(fld_e29 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj = *(uint32_t *)(v6 + 4 * i);
      else
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      {
        fld_e292 = *(this + 29);  // 读 fld_e292 = this+116（观察者容器）
        v9 = *(uint32_t *)(fld_e292 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        v11 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
        if ( v11 != 0 )
        {
          v12 = __RTDynamicCast(v11, 0, &IRDMonster `RTTI Type Descriptor', &CNSoldier `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
          if ( v12 != 0 && (int *)v12 != this )
            sub_5CF0F0(v12);  // 闸门复位
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
int /*thiscall*/ sub_5D3130(uint32_t *this)  // 函数定义: 军团编队槽位清空（CNTinSwordManExpeller）
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
    fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
    v4 = *(uint32_t *)(fld_e29 + 8);
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj = *(uint32_t *)(v6 + 4 * i);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    {
      fld_e292 = *(this + 29);  // 读 fld_e292 = this+116（观察者容器）
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      v11 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
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
int /*thiscall*/ sub_5D31D0(uint32_t *this)  // 函数定义: 最近编队驱逐者选取（按 vt+120 坐标取最小）
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
  while ( 1 )  // 无限循环
  {
    fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
    v4 = *(uint32_t *)(fld_e29 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)v1 >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && v1 < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj3 = *(uint32_t *)(v6 + 4 * v1);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 529) != 0 )  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    {
      fld_e292 = *(this + 29);  // 读 fld_e292 = this+116（观察者容器）
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && v1 < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        v10 = *(uint32_t *)(v9 + 4 * v1);
      else
        v10 = 0;
      pObj2 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
              v10,
              0,
              &CNRDObject `RTTI Type Descriptor',
              &CNTinSwordManExpeller `RTTI Type Descriptor',
              0);
      pObj = pObj2;
      if ( pObj2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2) < v15 )  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      {
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
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
uint32_t */*userpurge*/ sub_5D32A0@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)  // 实现：军团呐喊状态切换（LEGION_SHOUT）
{
  uint32_t *result; // eax
  char v8; // di
  int *v9; // eax
  int pObj; // eax
  int pObj2; // edi
  int v12; // edi

  result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);  // 虚函数调用 槽+840：大状态 getter（this+6556）
  v8 = ArgList;
  if ( result != (uint32_t *)20 || ArgList != 20 )
  {
    if ( ArgList == 8 )
    {
      result = *(uint32_t **)(LODWORD(fArg4) + 4);  // 调 取 64 位值低 32 位
      if ( *result == 0 )
        result = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
                             pArg1,
                             "LEGION_SHOUT",  // 字符串 “LEGION_SHOUT”
                             -1,
                             0,
                             0);
    }
    else if ( ArgList == 20 )
    {
      if ( *(uint8_t *)(pArg1 + 8669) != 1 )  // pArg1+8669〔bGuardActive8669(推断)〕
        return result;
      v9 = (int *)(*(uint32_t *)(pArg1 + 6216) + 20);  // pArg1+6216〔pTbl6216(推断)〕
      *(uint8_t *)(pArg1 + 8832) = 1;  // pArg1+8832〔uCharge8832(推断)〕
      sub_4926A0(*v9);  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20), nArg2);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 344))(pArg1, *(uint32_t *)(pArg1 + 556));  // 虚函数调用 槽+344：交互槽（45E490/45E4D0/525CE0）
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        pArg1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        pArg1,
        1,
        0,
        0,
        0,
        0,
        0);
      *(uint8_t *)(pArg1 + 8812) = 1;  // pArg1+8812〔uCharge8812(推断)〕
      *(uint32_t *)(pArg1 + 8816) = 4;  // pArg1+8816〔uCharge8816(推断)〕
      pObj = sub_45EBE0(**(uint32_t **)(LODWORD(fArg4) + 4), *(uint32_t *)(*(uint32_t *)(LODWORD(fArg4) + 4) + 4));  // 调 存 id 对 → 对象查找
      pObj2 = pObj;
      if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      {
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        *(uint32_t *)(pArg1 + 8816) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) < v12;  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      }
      result = (uint32_t *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 144))(pArg1, *(uint32_t *)(pArg1 + 8816));  // 虚函数调用 槽+144：槽（13 行）
      v8 = 20;
    }
    if ( *(uint8_t *)(pArg1 + 8669) == 1 )  // pArg1+8669〔bGuardActive8669(推断)〕
      return (uint32_t *)sub_4E33D0(v8, fArg4, nArg5, nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
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
int /*thiscall*/ sub_5D3400(uint32_t *this)  // 函数定义: 最近军团驱逐者选取（CNLegionExpeller, 类型 704）
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
  while ( 1 )  // 无限循环
  {
    fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
    v4 = *(uint32_t *)(fld_e29 + 120);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)v1 >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 120);
    if ( v6 != 0 && v1 < (*(uint32_t *)(fld_e29 + 124) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      v7 = *(uint32_t *)(v6 + 4 * v1);
    else
      v7 = 0;
    pObj = __RTDynamicCast(v7, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNLegionExpeller `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    pObj2 = pObj;
    if ( (uint32_t *)pObj != this
      && pObj != 0
      && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 704  // 虚函数调用 槽+340：三元组基址（+284，vt+340）
      && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj2, 0) < v12 )  // 虚调用 vt+8
    {
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj2, 0);  // 结果 = 虚调用 vt+8
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
char /*thiscall*/ sub_5D34C0(uint32_t *this, int nArg2, int nArg3)  // 函数定义: 编队格占用检测（nArg2/nArg3 坐标）
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
    fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
    v6 = *(uint32_t *)(fld_e29 + 8);
    v7 = v6 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= v7 )
      break;
    v8 = *(uint32_t *)(fld_e29 + 8);
    if ( v8 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v8) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj = *(uint32_t *)(v8 + 4 * i);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    {
      fld_e292 = *(this + 29);  // 读 fld_e292 = this+116（观察者容器）
      v11 = *(uint32_t *)(fld_e292 + 8);
      if ( v11 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v11) >> 2 )  // 向量元素数 = (end−begin)/4
        v12 = *(uint32_t *)(v11 + 4 * i);
      else
        v12 = 0;
      v13 = __RTDynamicCast(v12, 0, &CNRDObject `RTTI Type Descriptor', &CNLegionExpeller `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      if ( v13 != 0 && *(uint32_t *)(v13 + 8820) == nArg2 && *(uint32_t *)(v13 + 8824) == nArg3 )
        return 0;
    }
  }
  return 1;  // 返回 1(成功)
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D3590 sub_5D3590 —— 场上军团驱逐者计数（类型 704）
// 遍历 this+29 子表，vt+40(obj,529) 过滤后 RTTI 到 IRDMonster，统计 vt+340 == 704 者数量；
// ·0x5D42A0 以计数 > 1 作为编队移动门。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3590(uint32_t *this)  // 函数定义: 场上军团驱逐者计数（类型 704）
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
    fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
    v5 = *(uint32_t *)(fld_e29 + 8);
    v6 = v5 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= v6 )
      break;
    v7 = *(uint32_t *)(fld_e29 + 8);
    if ( v7 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v7) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj2 = *(uint32_t *)(v7 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0 )  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    {
      fld_e292 = *(this + 29);  // 读 fld_e292 = this+116（观察者容器）
      v10 = *(uint32_t *)(fld_e292 + 8);
      if ( v10 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v10) >> 2 )  // 向量元素数 = (end−begin)/4
        v11 = *(uint32_t *)(v10 + 4 * i);
      else
        v11 = 0;
      pObj = __RTDynamicCast(v11, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 704 )  // 虚函数调用 槽+340：三元组基址（+284，vt+340）
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
int /*thiscall*/ sub_5D3640(int *this)  // 函数定义: 编队档位清位（vt+1172 档位 → 子对象 +32..+160 五槽）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 1172))(this);  // 结果 = 虚调用 vt+1172
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
        *(uint8_t *)(*(this + 1905) + 128) = 0;  // this+7620〔pStatusPanel(推断)〕
LABEL_6:
        result = *(this + 1905);  // 读 result = this+7620（速度/属性参数对象）
        *(uint8_t *)(result + 160) = 0;
        return result;
      }
    }
    else
    {
      *(uint8_t *)(*(this + 1905) + 32) = 0;  // this+7620〔pStatusPanel(推断)〕
    }
    *(uint8_t *)(*(this + 1905) + 64) = 0;  // this+7620〔pStatusPanel(推断)〕
    *(uint8_t *)(*(this + 1905) + 96) = 0;  // this+7620〔pStatusPanel(推断)〕
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
void /*thiscall*/ sub_5D36C0(uint8_t *this, int nArg2)  // 函数定义: 编队挂件装配（8602/8603/8604 三相门）
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
    if ( *(this + 8603) != 0 )  // this+8603 盾空闲门
      goto LABEL_10;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 788))(this, 16);  // 虚函数调用 槽+788
    fld_e8602 = *(this + 8602);  // this+8602 【推断】三段演出相位门3
    *(this + 8603) = 1;  // this+8603 盾空闲门
    v3 = 1;
    if ( fld_e8602 != 0 )
      goto LABEL_11;
LABEL_8:
    if ( *(this + 8602) == 0 )  // this+8602 【推断】三段演出相位门3
    {
      (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 788))(this, 0);  // 虚函数调用 槽+788
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 788))(this, 1);  // 虚函数调用 槽+788
      *(this + 8602) = 1;  // this+8602 【推断】三段演出相位门3
LABEL_11:
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 2166) + 12))(*((uint32_t *)this + 2166), 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      pThis_876 = **((uint32_t **)this + 2166);
      pThis_80 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);  // this+128 第 2 组·+1208 增量子倍率
      pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, pThis_80 + 65);  // this+124 第 2 组·+858/+1292 增量
      pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, pThis_7C);  // this+120 动画对象指针
      (*(void (/*thiscall*/ **)(uint32_t, int))(pThis_876 + 40))(*((uint32_t *)this + 2166), pThis_78);  // this+40 物品状态附属标志
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**((uint32_t **)this + 2166) + 92))(*((uint32_t *)this + 2166), v11);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
      pThis_1D = *((void **)this + 29);
      v13 = 0;
      sub_4600B0(pThis_1D, 2, 0, (int)v11);  // 调 演播层注册(槽号)
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
      return;
    }
LABEL_10:
    if ( v3 != 1 )
      return;
    goto LABEL_11;
  }
  if ( nArg2 == 2 && *(this + 8604) == 0 )  // 判定 “+8604 子类 AI 状态字节”
  {
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 788))(this, 13);  // 虚函数调用 槽+788
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1324))(this);  // this+1324 动画图集对象
    fld_e8603 = *(this + 8603);  // this+8603 盾空闲门
    *(this + 8604) = 1;  // 写 this+8604 = 1（子类 AI 状态字节）
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
void /*thiscall*/ sub_5D3810(uint8_t *this)  // 函数定义: 军团呐喊表现铺设（vt+200 状态对象 +148 == 1 分支）
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

  pThis_94 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148);  // this+200 主状态
  if ( pThis_94 != 0 )
  {
    if ( pThis_94 == 1 )
    {
      if ( sub_41A5E0((unsigned int)(this + 7028)) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        if ( sub_41A5E0((unsigned int)(this + 7028)) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
            this,
            0,
            *(uint32_t *)(*((uint32_t *)this + 2153) + 4),  // this+8612〔uAI8612(推断)〕
            *(uint32_t *)(*((uint32_t *)this + 2153) + 4),  // this+8612〔uAI8612(推断)〕
            0,
            -3000,
            1);
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          this,
          0,
          **((uint32_t **)this + 2153),
          **((uint32_t **)this + 2153),
          0,
          -2000,
          1);
      }
      if ( *(this + 8604) == 0 )  // 判定 “+8604 子类 AI 状态字节”
      {
        (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int))(*(uint32_t *)this + 888))(this, 2, 2, 1000, 1000);  // 虚函数调用 槽+888：速率设置链: a2/a3 经 vt+976 换算 →…
        v3 = *(uint32_t *)this;
        pThis_98 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 152))(this, 4);  // this+152 第 4 组·+886 增量
        (*(void (/*thiscall*/ **)(uint8_t *, int))(v3 + 896))(this, pThis_98);  // 虚函数调用 槽+896：默认虚槽桩（11 行 return）
      }
      if ( *(this + 8660) == 1 )  // this+8660 【推断】事件配对/相位槽
      {
        pThis_39C = (uint32_t *)dword_8F8270[(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 924))(this, 2)];  // 虚函数调用 槽+924
        v6 = *(uint32_t *)this;
        pThis_39C2 = pThis_39C;
        v7 = (*(int (/*thiscall*/ **)(uint8_t *))(v6 + 152))(this);  // 虚函数调用 槽+152：效果通道 3
        v8 = *(uint32_t *)this;
        v9 = *pThis_39C;
        v20 = v7 == 0;
        v10 = (*(int (/*thiscall*/ **)(uint8_t *))(v8 + 128))(this);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
        pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, v10);  // this+124 第 2 组·+858/+1292 增量
        pThis_982 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 152))(this, pThis_7C + 1) != 0 ? -20 : 20;  // this+152 第 4 组·+886 增量
        pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) + pThis_982;  // this+120 动画对象指针
        pThis_39C22 = pThis_39C2;
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 40))(pThis_39C2, pThis_78);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
        *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pThis_39C2 + 28))(pThis_39C2) + 84) = v20;  // 虚调用 vt+28
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pThis_39C22 + 12))(pThis_39C22, 0);  // 虚调用 vt+12
        (*(void (/*thiscall*/ **)(uint32_t *, char *))(*pThis_39C22 + 92))(pThis_39C22, v17);  // 虚调用 vt+92
        pThis_1D = *((void **)this + 29);
        v21 = 0;
        sub_4600B0(pThis_1D, 2, 0, (int)v17);  // 调 演播层注册(槽号)
        Block2 = Block;
        *(this + 8660) = 0;  // this+8660 【推断】事件配对/相位槽
        if ( Block2 != nullptr )  // 若 Block2 有效（非空）
          j__free(Block2);  // 调 堆释放
      }
    }
  }
  else
  {
    *(this + 8660) = 1;  // this+8660 【推断】事件配对/相位槽
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
unsigned int /*thiscall*/ sub_5D39D0(int *this)  // 函数定义: 军团驱逐者编队主循环（出生点重定位 + 编队态切换）
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

  result = sub_5D2470();  // 结果 = 受击挂件清理 + 守卫帧收尾（本区多个 AI 的公共尾段）
  if ( *(this + 2175) != -1 )  // this+8700〔uPhase8700(推断)〕
    return result;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2214) + 68))(*(this + 2214)) != 0 )  // 虚函数调用 槽+68：槽（484880 + 5441B0 + 4850B0）
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2214) + 12))(*(this + 2214), 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) == 0 )  // 虚调用 vt+128
  {
    fld_e2226 = *(this + 2226) * *((uint8_t *)this + 8840) / 100 + 1;  // this+8840〔uPhase8840(推断)〕等 2 字段
    fld_e2218 = fld_e2226 * *(this + 2218);  // this+8872〔uDur8872(推断)〕
    fld_e2219 = fld_e2226 * *(this + 2219);  // this+8876〔uPhase8876〕
    nRand = rand();  // 调 取伪随机数
    v7 = *this;
    i = nRand % fld_e2218 - fld_e2218 / 2;
    i += (*(int (/*thiscall*/ **)(int *))(v7 + 120))(this);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    nRand2 = rand() % fld_e2219 - fld_e2219 / 2;  // 调 取伪随机数
    v21 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) + nRand2;  // 结果 = 虚调用 vt+124
    v20 = i;
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2214) + 40))(*(this + 2214));  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(uint32_t, char *))(*(uint32_t *)*(this + 2214) + 92))(*(this + 2214), v23);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    v9 = *this;
    v28 = 0;
    v10 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, char *))(v9 + 80))(this, 2, 0, v23);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    sub_4600B0(v10, v20, v21, 0);  // 调 演播层注册(槽号)
    v28 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
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
    (*(void (/*thiscall*/ **)(int *))(*this + 688))(this);  // 虚调用 vt+688
    sub_4EB4B0(v16);  // 与 ·0x4EB2C0 同构（差异：·sub_4923F0 按倒数缩放）
    pThis_8A82 = *((float *)this + 2216);
    (*(void (/*thiscall*/ **)(int *))(*this + 688))(this);  // 虚调用 vt+688
    sub_4EB2C0(pThis_8A82);  // 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
    pThis_651 = this + 1617;
    for ( i = 18; i != 0; --i )  // 循环：i 从 18 递减到 0
    {
      if ( *pThis_651 != 0 )
      {
        sub_4EB6E0(v16);  // 与 ·0x4EB6A0 同构（差异：调 ·0x4EB4B0）
        sub_4EB6A0(*((float *)this + 2216));  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
      }
      ++pThis_651;
    }
  }
  fld_e2217 = *(this + 2217);  // this+8868〔bGate8868〕
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  if ( fld_e2217 + *(this + 2220) < result || fld_e2217 == 0 )  // this+8880〔uPhase8880〕
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )  // 虚调用 vt+308
    {
      v19 = 22;
      if ( sub_41A5E0((char *)this + 8841) >= *(this + 2221) )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        if ( sub_41A5E0((char *)this + 8841) >= *(this + 2221) && *((uint8_t *)this + 8840) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
          v19 = 23;
      }
      else if ( *((uint8_t *)this + 8840) != 2 )  // this+8840 相位/档位槽
      {
        v19 = 21;
      }
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, v19, 0, 2, 0);  // 虚调用 vt+560
      result = (*(int (/*thiscall*/ **)(int *))(*this + 564))(this);  // 结果 = 虚调用 vt+564
      *(this + 2217) = -1;  // this+8868〔bGate8868〕
    }
    else
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      *(this + 2217) = result;  // this+8868〔bGate8868〕
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
char /*thiscall*/ sub_5D3CB0(int this)  // 函数定义: 雷守卫主帧（蓄雷循环 + 编队召唤收尾）
{
  int pThis_348; // eax
  int v3; // edi
  int pThis_30; // eax
  int v5; // edi
  int pThis_34; // eax
  int v7; // edi
  int v8; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
  {
    if ( sub_41A5E0(this + 7028) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);  // this+1332 装备/动画定义对象
    }
    else if ( sub_41A5E0(this + 7028) == 0 || sub_41A5E0(this + 7028) == 2 || sub_41A5E0(this + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( sub_41A5E0(this + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        sub_5D0330((int *)this, 1, this + 7028);  // 蓄雷循环：BEFORE_THUNDER 播报 + 雷柱预判布点（175L）
      sub_4D9360(this);
    }
  }
  if ( *(uint8_t *)(this + 8812) == 1  // this+8812 蓄雷门
    && sub_41A5E0(this + 7028) == 1  // crypt4byte 解密校验（·0x41A590 逆运算）
    && *(int *)(this + 8824) < 3  // this+8824 蓄雷次数
    && *(uint32_t *)(this + 8816) + *(uint32_t *)(this + 8820) < (unsigned int)sub_699000(this + 36) )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);  // this+352 【推断】命中/关系上下文槽
    *(uint32_t *)(this + 8816) = sub_699000(this + 36);  // clock_now(clk)
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) != 8 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
    sub_4D93D0(this);
  LOBYTE(pThis_348) = sub_5CF180((uint32_t *)this);  // 环绕音管理
  if ( *(uint8_t *)(this + 8669) == 1 )  // 判定 “+8669 守卫激活位”
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8603);  // this+8603 盾空闲门
    if ( (uint8_t)pThis_348 == 0 && *(uint8_t *)(this + 8601) == 1 )  // this+8601 站立位
    {
      pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 虚函数调用 槽+840：大状态 getter（this+6556）
      if ( pThis_348 == 0 )
        LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);  // 虚函数调用 槽+1344
    }
    if ( *(uint8_t *)(this + 8669) == 1 )  // 判定 “+8669 守卫激活位”
    {
      LOBYTE(pThis_348) = *(uint8_t *)(this + 8837);  // this+8837 编队召唤单次门
      if ( (uint8_t)pThis_348 == 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);  // 虚函数调用 槽+8：Update（166 行：CLICK_BUTTON2/DISSOLVE
        v3 = *(uint32_t *)dword_8F8520;  // 读 dword_8F8520（会话/UDP 管理器）
        pThis_30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 48))(this);  // this+48 UDP 上报使能位
        (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, pThis_30);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
        v5 = *(uint32_t *)dword_8F8520;  // 读 dword_8F8520（会话/UDP 管理器）
        pThis_34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 52))(this);  // this+52 光环状态字节
        (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_34);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
        v7 = *(uint32_t *)dword_8F8520;  // 读 dword_8F8520（会话/UDP 管理器）
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 全局 dword_8F7C04 = 本机角色对象
        (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 14);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
        LOBYTE(pThis_348) = sub_5D3060((int *)this);  // 军团驱逐者号令复位（this+29 子表扫描）
        *(uint8_t *)(this + 8837) = 1;  // this+8837 编队召唤单次门
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
int /*thiscall*/ sub_5D3E70(int this)  // 函数定义: 事件门号令复位（8837 一次性门）
{
  int result; // eax
  int v3; // edi

  result = sub_4DC630();  // 结果 = 关卡/交互事件包处理（关联对象 this+7260 校验）
  v3 = result;
  if ( result != -1 )
  {
    if ( result == 14 && *(uint8_t *)(this + 8837) == 0 )  // this+8837 编队召唤单次门
    {
      sub_5D3060((int *)this);  // 军团驱逐者号令复位（this+29 子表扫描）
      *(uint8_t *)(this + 8837) = 1;  // this+8837 编队召唤单次门
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
int /*thiscall*/ sub_5D3EB0(int this, int nArg2, int nArg3, int nArg4)  // 函数定义: 军团驱逐者播报转发（8664 子对象定位）
{
  int fld_21D8; // edi  | +0x21D8 → 附属子对象槽（CNTinSwordManExpeller；va=005D3EB0）
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  void *fld_74; // ecx
  uint8_t v11[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v13; // [esp+Ch] [ebp-14h]
  int v14; // [esp+10h] [ebp-10h]
  int v15; // [esp+1Ch] [ebp-4h]

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
  {
    if ( (uint8_t)nArg4 != 0 )
      return sub_5CEFF0((uint8_t *)this, nArg2, nArg3, nArg4);  // 法杖命中
    if ( *(uint8_t *)(this + 8603) == 0 )  // this+8603 盾空闲门
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)this + 1336))(this, nArg2, nArg3, 0);  // 虚函数调用 槽+1336
  }
  else if ( (uint8_t)nArg4 != 0 )
  {
    return sub_5CEFF0((uint8_t *)this, nArg2, nArg3, nArg4);  // 法杖命中
  }
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8664) + 12))(*(uint32_t *)(this + 8664), 0);  // this+8664 附属子对象槽
  fld_21D8 = **(uint32_t **)(this + 8664);  // this+8664 附属子对象槽
  pThis_80 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // this+128 第 2 组·+1208 增量子倍率
  pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_80 + 65);  // this+124 第 2 组·+858/+1292 增量
  pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C);  // this+120 基类动画对象指针
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_21D8 + 40))(*(uint32_t *)(this + 8664), pThis_78);  // this+8664 附属子对象槽
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 8664) + 92))(*(uint32_t *)(this + 8664), v11);  // this+8664 附属子对象槽
  fld_74 = *(void **)(this + 116);  // this+116 观察者 vector 尾针
  v15 = 0;
  sub_4600B0(fld_74, 2, 0, (int)v11);  // 调 演播层注册(槽号)
  v15 = -1;
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 堆释放
  Block = nullptr;
  v13 = 0;
  v14 = 0;
  return sub_5CEFF0((uint8_t *)this, nArg2, nArg3, nArg4);  // 法杖命中
}



// 时钟门+RTTI AI（122L）
// ------------------------------------------------------------
// 0x5D3FD0 sub_5D3FD0 —— 编队格位搜索（48x480 网格扫描 + 时间门）
// 2211 时钟未到返回 0；到点后 ·0x5D3130 清位、2218/2219 归零、698F90(10000) 起长时门。
// ·0x5D31D0 取自身时，以 this+29 子链 vt+672(3) 尺寸算网格上界，48 步长双层循环扫
// ·0x5D34C0 空位与 vt+136 地形可用性，命中则写 8812/8816 并 vt+1144 落位；否则 8848 置位。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D3FD0(int *this)  // 函数定义: 编队格位搜索（48x480 网格扫描 + 时间门）
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

  pThis_89D = (int)(this + 2205);  // this+8820〔uCharge8820(推断)〕
  fld_e2211 = *(this + 2211);  // this+8844〔uPhaseClock8844〕
  if ( sub_699000((int)(this + 2205)) < fld_e2211 )  // 【clock_now(clk)】
    return 0;
  sub_5D3130(this);  // 军团编队槽位清空（CNTinSwordManExpeller）
  *(uint8_t *)(pThis_89D + 13) = 0;
  *(uint8_t *)(pThis_89D + 14) = 0;
  sub_698F90(pThis_89D, 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  v5 = sub_5D31D0(this);  // 结果 = 最近编队驱逐者选取（按 vt+120 坐标取最小）
  pObj2 = v5;
  v24 = v5;
  if ( v5 != 0 && (int *)v5 == this )
  {
    fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);  // this+116〔会话上下文〕
    v8 = *(uint32_t *)(fld_e29 + 364);
    v9 = fld_e29 + 360;
    v10 = v8 != 0 ? (*(uint32_t *)(v9 + 8) - v8) >> 5 : 0;
    v11 = 224 * v10;
    v23 = 224 * v10;
    v25 = 48 * ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2) / 48);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    if ( v25 < v11 )
    {
LABEL_9:
      v26 = 0;
      while ( 1 )  // 无限循环
      {
        v12 = 0;
        while ( 1 )  // 无限循环
        {
          fld_e292 = *(this + 29);  // 读 fld_e292 = this+116（观察者容器）
          v14 = *(uint32_t *)(fld_e292 + 8);
          v15 = v14 != 0 ? (*(uint32_t *)(fld_e292 + 12) - v14) >> 2 : 0;  // 向量元素数 = (end−begin)/4
          if ( (int)v12 >= v15 )
            break;
          v16 = *(uint32_t *)(fld_e292 + 8);
          if ( v16 != 0 && v12 < (*(uint32_t *)(fld_e292 + 12) - v16) >> 2 )  // 向量元素数 = (end−begin)/4
            pObj = *(uint32_t *)(v16 + 4 * v12);
          else
            pObj = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) == 0 )  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
            goto LABEL_31;
          fld_e293 = *(this + 29);  // 读 fld_e293 = this+116（观察者容器）
          v19 = *(uint32_t *)(fld_e293 + 8);
          if ( v19 != 0 && v12 < (*(uint32_t *)(fld_e293 + 12) - v19) >> 2 )  // 向量元素数 = (end−begin)/4
            v20 = *(uint32_t *)(v19 + 4 * v12);
          else
            v20 = 0;
          v21 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                  v20,
                  0,
                  &CNRDObject `RTTI Type Descriptor',
                  &CNTinSwordManExpeller `RTTI Type Descriptor',
                  0);
          if ( v24 == v21 )
          {
            (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);  // 虚调用 vt+1104
            ++v12;
          }
          else
          {
            if ( v21 != 0
              && *(uint8_t *)(v21 + 8848) == 0
              && *(uint32_t *)(v21 + 8812) != v25
              && *(uint32_t *)(v21 + 8816) != v26
              && (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(*this + 136))(this, v25, v26, 0) != 0 )  // 虚调用 vt+136
            {
              v22 = *(uint32_t *)v21;
              *(uint32_t *)(v21 + 8816) = v26;
              *(uint32_t *)(v21 + 8812) = v25;
              *(uint8_t *)(v21 + 8848) = 1;
              (*(void (/*thiscall*/ **)(int, int, int))(v22 + 1144))(v21, v25, v26);  // 虚函数调用 槽+1144：默认虚槽桩（10 行 return）
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
            return 1;  // 返回 1(成功)
          goto LABEL_9;
        }
      }
    }
  }
  return 1;  // 返回 1(成功)
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5D41E0 sub_5D41E0 —— 环绕八点布位（±48 步长）
// ·0x5D3400 取最近军团驱逐者作锚点，按 -48/0/48 组合枚举 8 个环绕格位，逐点叠加锚点
// vt+120/vt+124 作绝对坐标，·0x5D34C0 判空位与 vt+136 判可用，命中即 break 并回传出参。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D41E0(uint32_t *this, int *pDwArg2, int *pDwArg3)  // 函数定义: 环绕八点布位（±48 步长）
{
  int pObj; // esi
  int i; // ebx
  int v6; // eax
  int v8; // [esp+Ch] [ebp-40h]
  uint32_t v9[15]; // [esp+10h] [ebp-3Ch]

  pObj = sub_5D3400(this);  // 结果 = 最近军团驱逐者选取（CNLegionExpeller, 类型 704）
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
  for ( i = 0; i < 8; ++i )  // 循环：i 从 0 递增到 8
  {
    if ( pObj != 0 )
    {
      *pDwArg2 = v9[2 * i - 1] + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      v6 = v9[2 * i] + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      *pDwArg3 = v6;
      if ( sub_5D34C0(this, *pDwArg2, v6) != 0  // 编队格占用检测（nArg2/nArg3 坐标）
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 136))(this, *pDwArg2, *pDwArg3, 0) != 0 )  // 虚调用 vt+136
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
int /*thiscall*/ sub_5D42A0(uint32_t *this)  // 函数定义: 编队落位判定（count>1 且后仰非 25 号）
{
  int result; // eax
  int v3; // eax
  int v4; // edx
  int v5; // [esp+4h] [ebp-8h] BYREF
  int v6; // [esp+8h] [ebp-4h] BYREF

  result = sub_5D3590(this);  // 结果 = 场上军团驱逐者计数（类型 704）
  if ( *(this + 1813) == 0 && result > 1 )  // this+7252〔pTarget7252〕
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
    v4 = *this;
    v5 = v3;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 124))(this);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    result = sub_5D41E0(this, &v5, &v6);  // 结果 = 环绕八点布位（±48 步长）
    if ( result != 0 )  // 若结果非 0（成功）
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, result, 0);  // 结果 = 虚调用 vt+8
      if ( result > 100 || result < 64 )  // 若 result > 100 与/或 result < 64
      {
        if ( *(this + 1787) != 25 )  // 判定 “+7148 大状态镜像槽”
          return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1144))(this, v5, v6);  // 虚调用 vt+1144
      }
      else if ( *(this + 1787) == 25 )  // 判定 “+7148 大状态镜像槽”
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);  // 虚调用 vt+1104
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
int /*thiscall*/ sub_5D4340(uint8_t *this)  // 函数定义: 阿莫尔战损第一段（AMOR_HIT + 爆碎粒子）
{
  *(this + 8600) = 0;  // 写 this+8600 = 0（子类AI区）
  sub_4015C0("AMOR_HIT", 8u);  // 【std::string构造赋值】
  *((uint32_t *)this + 2176) = -1;  // this+8704〔pSegNameTbl8704(推断)〕
  *((uint32_t *)this + 2177) = -1;  // this+8708〔pCandTbl8708(推断)〕
  *((uint32_t *)this + 2178) = -1;  // this+8712〔nCandTblEnd8712(推断)〕
  if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 插值终点 X / 落点偏移
    return (*(int (/*thiscall*/ **)(uint8_t *, uint8_t *, const char *))(*(uint32_t *)this + 1352))(  // 虚函数调用 槽+1352
             this,
             this + 364,  // this+364 动画件名缓冲 SSO 内联首址
             "Particle/ExpellerBrokenParts.ptl");  // 字符串 “Particle/ExpellerBrokenParts.ptl”
  else
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, const char *))(*(uint32_t *)this + 1352))(  // 虚函数调用 槽+1352
             this,
             *((uint32_t *)this + 91),  // this+91〔字符串〕
             "Particle/ExpellerBrokenParts.ptl");  // 字符串 “Particle/ExpellerBrokenParts.ptl”
}



// AI 相位字段（this+8601/8603/8669）
// ------------------------------------------------------------
// 0x5D43B0 sub_5D43B0 —— 编队搜索帧（主帧包装）
// 攻击态先 vt+1332 收招；8669 门为 1 时调 ·0x5D3FD0 编队格位搜索，再 ·sub_5CF180 基类帧，
// 尾段 8603/8601 + 姿态 0 走 vt+1344 二次判定（与 ·0x5D0070 同构收尾）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D43B0(int this)  // 函数定义: 编队搜索帧（主帧包装）
{
  int pThis_348; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);  // this+1332 装备/动画定义对象
  if ( *(uint8_t *)(this + 8669) == 1 )  // 判定 “+8669 守卫激活位”
    sub_5D3FD0((int *)this);  // 编队格位搜索（48x480 网格扫描 + 时间门）
  LOBYTE(pThis_348) = sub_5CF180((uint32_t *)this);  // 环绕音管理
  if ( *(uint8_t *)(this + 8669) == 1 )  // 判定 “+8669 守卫激活位”
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8603);  // this+8603 盾空闲门
    if ( (uint8_t)pThis_348 == 0 && *(uint8_t *)(this + 8601) == 1 )  // this+8601 站立位
    {
      pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 虚函数调用 槽+840：大状态 getter（this+6556）
      if ( pThis_348 == 0 )
        LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);  // 虚函数调用 槽+1344
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
int /*thiscall*/ sub_5D4420(uint8_t *this)  // 函数定义: 阿莫尔战损第二段（位置双槽重置）
{
  int v2; // eax
  int v3; // eax

  v2 = *(uint32_t *)this;
  *(this + 8600) = 0;  // 写 this+8600 = 0（子类AI区）
  v3 = (*(int (**)(void))(v2 + 52))();  // 虚函数调用 槽+52：播 AURA_SHIELD_LOOP（第二挂点，15 行）
  *((uint32_t *)this + 2204) = v3;  // this+8816〔uCharge8816(推断)〕
  *((uint32_t *)this + 2203) = v3;  // this+8812〔uCharge8812(推断)〕
  *(this + 8833) = 0;
  *(this + 8834) = 0;
  sub_698F90((int)(this + 8820), 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(this + 8848) = 0;  // this+8848 【推断】相位标志字节
  *((uint32_t *)this + 2213) = 0;
  return sub_4015C0("AMOR_HIT", 8u);  // 【std::string构造赋值】
}



// 阿莫尔命中 3：AMOR_HIT 播报（this+8601/8812/8832 相位）
// ------------------------------------------------------------
// 0x5D4480 sub_5D4480 —— 阿莫尔战损第三段（编队门清位）
// 清 8601/8812/8600 三门，vt+52 取坐标写 2205/2206 双槽、2207 归零，清 8832 门，
// 最后 ·sub_4015C0 写 AMOR_HIT 语音槽。与 ·0x5D4420 同构（差异：清 8601/8812/8832 组）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4480(uint8_t *this)  // 函数定义: 阿莫尔战损第三段（编队门清位）
{
  int v2; // eax
  int v3; // eax

  v2 = *(uint32_t *)this;
  *(this + 8601) = 0;  // this+8601 子类 AI 状态字节 2
  *(this + 8812) = 0;  // this+8812 蓄力门
  *(this + 8600) = 0;  // 写 this+8600 = 0（子类AI区）
  v3 = (*(int (**)(void))(v2 + 52))();  // 虚函数调用 槽+52：播 AURA_SHIELD_LOOP（第二挂点，15 行）
  *((uint32_t *)this + 2206) = v3;  // this+8824〔uCharge8824〕
  *((uint32_t *)this + 2205) = v3;  // this+8820〔uCharge8820(推断)〕
  *((uint32_t *)this + 2207) = 0;
  *(this + 8832) = 0;  // this+8832 蓄雷参数槽
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
char /*thiscall*/ sub_5D44D0(uint32_t *this)  // 函数定义: 阿莫尔主帧（姿态 8/20 分支 + 受击联动）
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

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 结果 = 虚调用 vt+840
  if ( v2 == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 0 || sub_41A5E0((unsigned int)(this + 1757)) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1332))(this);  // 虚调用 vt+1332
    else
      sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
  }
  else if ( v2 == 20 )
  {
    if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) <= 1 )  // 虚调用 vt+200
    {
      if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) >= 1  // 虚调用 vt+200
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308
      {
        if ( *((uint8_t *)this + 8812) == 1 )  // this+8812 蓄力门
        {
          v3 = *this;
          fld_e2204 = *(this + 2204);  // this+8816〔uCharge8816(推断)〕
          *((uint8_t *)this + 8812) = 0;  // this+8812 蓄力门
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v3 + 896))(this, fld_e2204, 4);  // 虚函数调用 槽+896：默认虚槽桩（11 行 return）
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(  // 虚调用 vt+876
            this,
            0,
            1400,
            1400,
            0,
            -2000,
            1);
        }
        pObj = dword_8F8270[(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 924))(this, 2)];  // 结果 = 虚调用 vt+924
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0;  // 结果 = 虚调用 vt+152
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj) + 84) = v5;  // 虚函数调用 槽+28：生成装配：Character/Mage/Effect/Animation/Fol…
        v6 = *(uint32_t *)pObj;
        v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
        v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v7);  // 结果 = 虚调用 vt+124
        v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v8);  // 结果 = 虚调用 vt+120
        (*(void (/*thiscall*/ **)(int, int))(v6 + 40))(pObj, v9);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
        (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj + 92))(pObj, v13);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
        fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
        v14 = 0;
        sub_4600B0(fld_e29, 2, 0, (int)v13);  // 调 演播层注册(槽号)
        v14 = -1;
        sub_5E5260(v13);  // 调 动画子对象清理临时缓冲
      }
    }
    else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 虚调用 vt+308
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 568))(this) != 0 )  // 虚调用 vt+568
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 虚调用 vt+560
    }
  }
  if ( *((uint8_t *)this + 8669) == 1 )  // this+8669 守卫激活位
    sub_5D42A0(this);  // 编队落位判定（count>1 且后仰非 25 号）
  if ( *((uint8_t *)this + 8832) != 0 )  // this+8832 蓄雷参数槽
  {
    sub_4D83E0(0, 0);  // 头顶气泡 ”Exclamation.ani”（惊叹；同 0x4D82D0 结构）
    *((uint8_t *)this + 8832) = 0;  // this+8832 蓄雷参数槽
  }
  return sub_5CF180(this);  // 环绕音管理
}



// 语音注册（sub_4015C0; 容器越界串为 STL 断言文本, 非游戏资源）
// ------------------------------------------------------------
// 0x5D46D0 sub_5D46D0 —— STL vector 下标越界抛掷（编译器内联展开的异常路径）
// 构造 std::out_of_range 对象（_TI3_AVout_of_range_std__）并 _CxxThrowException；
// 源码侧即 v[i] 越界检查失败的 noreturn 桩，非业务逻辑。
// ------------------------------------------------------------
void /*noreturn*/ sub_5D46D0()  // STL vector 下标越界抛掷（编译器内联展开的异常路径）
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
  sub_401740(v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject = &std::out_of_range::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// 语音注册（sub_4015C0）
// ------------------------------------------------------------
// 0x5D4740 sub_5D4740 —— STL list 结点计数累加（超限抛 length_error）
// 以 357913941（0x15555555 上限）校验 this+2 计数，溢出则抛 std::length_error；
// 否则 this+2 += uArg2 并回传新计数。·0x5D48D0 中以 1 递增相位记录环长度。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4740(uint32_t *this, unsigned int uArg2)  // 函数定义: STL list 结点计数累加（超限抛 length_error）
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // 读 fld_e2 = this+8（技能槽记录首字）
  if ( 357913941 - fld_e2 < uArg2 )
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
    v8 = 0;
    sub_401740(v5);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
    pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // 写 this+8 = result（技能槽记录首字）
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
int /*userpurge*/ sub_5D47D0@<eax>(int pArg1@<ecx>, int nArg2@<edi>, int ArgList, float fArg4, int nArg5, int nArg6)  // 实现：霸体状态事件（SUPERARMOR 播报, 24/25 号）
{
  uint64_t v7; // rax
  uint32_t *v8; // edi
  int *v9; // edx
  float v11; // [esp+1Ch] [ebp+14h]

  if ( ArgList < 24 || ArgList > 25 )  // 若 ArgList < 24 与/或 ArgList > 25
    return sub_5D19C0((int **)pArg1, ArgList, fArg4, nArg5, nArg6);  // 状态事件总透传（架招退出 + 反击效果 30022）
  v11 = (float)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 736))(pArg1, nArg2);  // 虚函数调用 槽+736：属性块首值（GetHP 族，此处索引）
  v7 = (uint64_t)((1.0 - v11 / (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 740))(pArg1))  // 虚函数调用 槽+740：属性块 +4 浮点壳（GetHP 族）
                        * (double)*(int *)(pArg1 + 8864));
  v8 = *(uint32_t **)(LODWORD(fArg4) + 4);  // 调 取 64 位值低 32 位
  if ( v8 == nullptr || (*(uint32_t *)(LODWORD(fArg4) + 8) - (int)v8) >> 2 == 0 )  // 调 取 64 位值低 32 位
    sub_454B50();  // vector 越界抛异常
  *(uint32_t *)(pArg1 + 8844) = *(uint32_t *)(pArg1 + 4 * *v8 + 8852) - v7;  // pArg1+8844〔uPhaseClock8844(推断)〕
  *(uint32_t *)(pArg1 + 8848) = sub_699000(pArg1 + 36);  // clock_now(clk)
  if ( *(uint32_t *)(pArg1 + 8700) == -1 )  // pArg1+8700〔uPhase8700(推断)〕
  {
    sub_4DB200(24, (ArgList != 24) + 1);  // 15% 概率随机文案触发（0x4DB130 的门包装）
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, "SUPERARMOR", -1, 0, 0);  // 字符串 “SUPERARMOR”
  }
  v9 = *(int **)pArg1;
  *(uint32_t *)(pArg1 + 8840) = ArgList != 24;  // pArg1+8840〔uPhase8840(推断)〕
  return ((int (/*thiscall*/ *)(int, uint32_t))v9[248])(pArg1, *(uint32_t *)(pArg1 + 8844));  // pArg1+8844〔uPhaseClock8844(推断)〕
}



// 大型 AI（183L；sub_699000 + this+8840..8998 守卫相位字段）
// ------------------------------------------------------------
// 0x5D48D0 sub_5D48D0 —— 军团驱逐者计时器总调度（2211..2262 多时钟）
// ·sub_5D2470 尾段后于 2175 空闲门内依次巡检: 2211 时钟（8840 相位与 940 门下 28 号状态）、
// 2243/2244 血量比阈值→26/27 号状态、2236 逾 1000 时 8F8520 事件 + ±随机坐标 vt+136 探测、
// 2235/2229 记录环（·sub_5D2440 摘除 + ·0x5D1490 造记录 + ·0x5D4740 计数）、
// 2246 逾 2252 时 8F8270 池对象定位 + 2261/2262 随机重排。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D48D0(int *this)  // 函数定义: 军团驱逐者计时器总调度（2211..2262 多时钟）
{
  int nThunderCd; // ebx
  int fld_e2243; // edi  | +0x230C → 事件档位（事件 26→1、27→2；0x5D1D90）（CNGuardWind）
  int nVtHp; // eax
  int nHpPhase; // eax  | +0x230C → 事件档位（事件 26→1、27→2；0x5D1D90）（CNGuardWind）
  int nPktVt1; // edx
  int nPktVt2; // edi
  int nSelfKeyA; // eax
  int nPktVt3; // edi
  int nSelfKeyB; // eax
  int nPktVt4; // edi
  int nMapId; // eax
  int fld_pLink44; // edi
  int nSpanY; // edi
  int nProbeX; // ebx
  int nProbeY; // edx
  int nSelfVt; // eax
  int nRingCd; // edi
  int nSelfX; // eax
  int nSelfVt2; // edx
  uint32_t *pRingHead; // eax
  int nRingVt; // ebx
  int pNewNode; // eax
  int nShotCd; // edi
  int pShotObj; // edi
  int nFacing; // eax
  int nShotVt; // ebx
  int nSelfZ; // eax
  int nSelfY; // eax
  int nSelfX2; // eax
  int pFlagField; // eax
  void *pSceneObj; // ecx
  int nRandJitter; // eax
  char v35[4]; // [esp+4h] [ebp-38h] BYREF
  void *Block; // [esp+8h] [ebp-34h]
  uint32_t v37[3]; // [esp+14h] [ebp-28h] BYREF
  int nProbeYSave; // [esp+20h] [ebp-1Ch]
  float fHpRatio; // [esp+24h] [ebp-18h]
  int nHpVal; // [esp+28h] [ebp-14h]
  bool bFacingZero; // [esp+2Fh] [ebp-Dh]
  int nFreeState; // [esp+38h] [ebp-4h]

  sub_5D2470();  // 受击挂件清理 + 守卫帧收尾（本区多个 AI 的公共尾段）
  if ( *(this + 2175) == -1 )  // this+8700〔uPhase8700(推断)〕
  {
    nThunderCd = *(this + 2217);  // this+8868〔bGate8868〕
    if ( sub_699000((int)(this + 2211)) >= nThunderCd && (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 0 )  // 【clock_now(clk)】
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1  // 虚调用 vt+308
        && *((uint8_t *)this + 8840) == 0  // this+8840 相位/档位槽
        && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 0 )  // 虚调用 vt+940
      {
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 28, 0, 2, 0);  // 虚调用 vt+560
        (*(void (/*thiscall*/ **)(int *))(*this + 564))(this);  // 虚调用 vt+564
      }
      *((uint8_t *)this + 8840) = 0;  // this+8840 相位/档位槽
      *((uint8_t *)this + 8857) = 0;  // this+8857 相位标志
      *((uint8_t *)this + 8858) = 0;  // this+8858 相位标志
      sub_698F90((int)(this + 2211), *(this + 2253), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    fld_e2243 = *(this + 2243);  // this+8972〔uEvtState8972〕
    nHpVal = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);  // 结果 = 虚调用 vt+736
    nVtHp = *this;
    fHpRatio = (float)nHpVal;
    nHpVal = (*(int (/*thiscall*/ **)(int *))(nVtHp + 740))(this);  // 虚函数调用 槽+740：属性块 +4 浮点壳（GetHP 族）
    if ( fHpRatio / (double)nHpVal < *((float *)this + fld_e2243 + 2256)
      && fld_e2243 == *(this + 2244)  // this+8976〔uEvtState8976〕
      && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )  // 虚调用 vt+308
    {
      nHpPhase = *(this + 2243);  // this+8972〔uEvtState8972〕
      if ( nHpPhase != 2 )
      {
        if ( nHpPhase != 0 )
        {
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 27, 0, 2, 0);  // 虚调用 vt+560
          *(this + 2244) = 2;  // this+8976〔uEvtState8976〕
        }
        else
        {
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 26, 0, 2, 0);  // 虚调用 vt+560
          *(this + 2244) = 1;  // this+8976〔uEvtState8976〕
        }
        (*(void (/*thiscall*/ **)(int *))(*this + 564))(this);  // 虚调用 vt+564
      }
    }
    if ( sub_699000((int)(this + 2236)) > 1000 )  // 【clock_now(clk)】
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 1  // 虚调用 vt+940
        && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )  // 虚调用 vt+308
      {
        nPktVt1 = *(uint32_t *)dword_8F8520;  // 读 dword_8F8520（会话/UDP 管理器）
        nHpVal = 100;
        (*(void (/*thiscall*/ **)(int, int, int))(nPktVt1 + 8))(dword_8F8520, 29, 2);  // 虚函数调用 槽+8：Update（166 行：CLICK_BUTTON2/DISSOLVE
        nPktVt2 = *(uint32_t *)dword_8F8520;  // 读 dword_8F8520（会话/UDP 管理器）
        nSelfKeyA = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);  // 结果 = 虚调用 vt+48
        (*(void (/*thiscall*/ **)(int, int))(nPktVt2 + 36))(dword_8F8520, nSelfKeyA);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
        nPktVt3 = *(uint32_t *)dword_8F8520;  // 读 dword_8F8520（会话/UDP 管理器）
        nSelfKeyB = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);  // 结果 = 虚调用 vt+52
        (*(void (/*thiscall*/ **)(int, int))(nPktVt3 + 36))(dword_8F8520, nSelfKeyB);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
        nPktVt4 = *(uint32_t *)dword_8F8520;  // 读 dword_8F8520（会话/UDP 管理器）
        nMapId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 全局 dword_8F7C04 = 本机角色对象
        (*(void (/*thiscall*/ **)(int, int))(nPktVt4 + 36))(dword_8F8520, nMapId);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
        fld_pLink44 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);  // this+116〔会话上下文〕
        fHpRatio = COERCE_FLOAT(sub_425050(fld_pLink44));  // 结果 = 总宽换算
        nSpanY = 120 * (sub_424FF0(fld_pLink44) + 3);  // 结果 = 列数换算
        do
        {
          nProbeX = rand() % SLODWORD(fHpRatio);  // 调 取伪随机数
          nProbeY = rand() % nSpanY;  // 调 取伪随机数
          nSelfVt = *this;
          nProbeYSave = nProbeY;
          if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(nSelfVt + 136))(this, nProbeX, nProbeY, 0) == 1 )  // 虚函数调用 槽+136：槽（10 行）
            break;
        }
        while ( nHpVal-- != 0 );
        if ( nHpVal != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 17);  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nProbeX);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nProbeYSave);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
        }
      }
      *((uint8_t *)this + 8957) = 0;  // this+8957 相位字节
      *((uint8_t *)this + 8958) = 0;  // this+8958 相位字节
    }
    nRingCd = *(this + 2235);
    if ( sub_699000((int)(this + 2229)) >= nRingCd )  // 【clock_now(clk)】
    {
      if ( *(this + 2228) == *(this + 2254) )  // this+8912〔uPhase8912〕
        sub_5D2440(this + 2226);  // 相位记录环摘除（this+2226 槽）
      nSelfX = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
      nSelfVt2 = *this;
      v37[0] = nSelfX;
      v37[1] = (*(int (/*thiscall*/ **)(int *))(nSelfVt2 + 124))(this);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      v37[2] = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
      pRingHead = (uint32_t *)*(this + 2227);  // this+8908〔uPhase8908〕
      nRingVt = *pRingHead;
      nProbeYSave = sub_5D1490(*pRingHead, *(uint32_t *)(*pRingHead + 4), v37);  // 结果 = 五元组记录构造（20 字节堆分配）
      sub_5D4740(1);  // STL list 结点计数累加（超限抛 length_error）
      pNewNode = nProbeYSave;
      *(uint32_t *)(nRingVt + 4) = nProbeYSave;
      **(uint32_t **)(pNewNode + 4) = pNewNode;
      *((uint8_t *)this + 8929) = 0;  // this+8929 相位字节
      *((uint8_t *)this + 8930) = 0;  // this+8930 相位字节
      sub_698F90((int)(this + 2229), *(this + 2255), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 1 )  // 虚调用 vt+940
    {
      nShotCd = *(this + 2252);  // this+9008〔uPhase9008〕
      if ( sub_699000((int)(this + 2246)) >= nShotCd )  // 【clock_now(clk)】
      {
        pShotObj = dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 2)];  // 结果 = 虚调用 vt+924
        nFacing = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 结果 = 虚调用 vt+152
        nShotVt = *(uint32_t *)pShotObj;
        bFacingZero = nFacing == 0;
        nSelfZ = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
        nSelfY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nSelfZ);  // 结果 = 虚调用 vt+124
        nSelfX2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nSelfY);  // 结果 = 虚调用 vt+120
        (*(void (/*thiscall*/ **)(int, int))(nShotVt + 40))(pShotObj, nSelfX2);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
        pFlagField = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pShotObj + 28))(pShotObj);  // 虚函数调用 槽+28：生成装配：Character/Mage/Effect/Animation/Fol…
        *(uint8_t *)(pFlagField + 84) = bFacingZero;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pShotObj + 12))(pShotObj, 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pShotObj + 92))(pShotObj, v35);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
        pSceneObj = (void *)*(this + 29);  // this+116〔会话上下文〕
        nFreeState = 0;
        sub_4600B0(pSceneObj, 2, 0, (int)v35);  // 调 演播层注册(槽号)
        *((uint8_t *)this + 8997) = 0;
        *((uint8_t *)this + 8998) = 0;
        nRandJitter = rand();  // 调 取伪随机数
        sub_698F90((int)(this + 2246), *(this + 2261) + nRandJitter % *(this + 2262), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        if ( Block != nullptr )  // 若 Block 有效（非空）
          j__free(Block);  // 调 堆释放
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
char /*thiscall*/ sub_5D4D00(uint32_t *this)  // 函数定义: 霸体 PO 挂装（vt+1757 帧位 2 分支）
{
  void *pMem; // eax
  int pObj; // eax
  int fld_e2204; // ecx  | +0x2270 → 蓄力计时戳（5D00F0 清零）（证据 va=005D00F0）（CNAxeExpeller；va=005D00F0）

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8 )  // 虚调用 vt+840
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 0 || sub_41A5E0((unsigned int)(this + 1757)) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1332))(this);  // 虚调用 vt+1332
    }
    else if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( *(this + 2204) == 0 )  // this+8816〔uCharge8816(推断)〕
      {
        pMem = operator new(0x64u);  // 堆分配 100 字节对象
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
          pObj = sub_51A7D0(pMem);  // 调 构造后把时长写入虚 64 结果 +40
        else
          pObj = 0;
        *(this + 2204) = pObj;  // this+8816〔uCharge8816(推断)〕
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
      }
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2204) + 80))(*(this + 2204)) == 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2204) + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
          *(this + 2204),  // this+8816〔uCharge8816(推断)〕
          this,
          this,
          0,
          0,
          0,
          -1);
    }
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 8 || sub_41A5E0((unsigned int)(this + 1757)) != 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    fld_e2204 = *(this + 2204);  // this+8816〔uCharge8816(推断)〕
    if ( fld_e2204 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2204 + 80))(fld_e2204) == 1 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2204) + 76))(*(this + 2204), 0);  // 虚函数调用 槽+76：槽（542940 + 485020）
  }
  return sub_5CF180(this);  // 环绕音管理
}



// 斧驱逐者破碎 3：Particle/AxeExpellerBrokenParts.ptl（32L）
// ------------------------------------------------------------
// 0x5D4E30 sub_5D4E30 —— 斧驱逐者战损（AxeExpellerBrokenParts.ptl）
// 清 2176/2177/2178 三槽、vt+1308 复位；new 0x7C + ·sub_4B3DF0(5,1,-10.0,20000,0) 构造爆碎
// 颗粒对象写 2203 槽并清派生 +36 位；按 96 槽长短路取 364 或 +91 字符串，
// vt+1352 装载 Particle/AxeExpellerBrokenParts.ptl。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4E30(uint32_t *this)  // 函数定义: 斧驱逐者战损（AxeExpellerBrokenParts.ptl）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pThis_5B; // eax

  *(this + 2176) = -1;  // this+8704〔pSegNameTbl8704(推断)〕
  *(this + 2177) = -1;  // this+8708〔pCandTbl8708(推断)〕
  *(this + 2178) = -1;  // this+8712〔nCandTblEnd8712(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 虚调用 vt+1308
  pMem = operator new(0x7Cu);  // 堆分配 124 字节对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4B3DF0(pMem, 5, 1, -1035468800, 20000, 0);  // 结果 = CNChangeStatus 构造（六参）
  else
    v3 = nullptr;
  *(this + 2203) = v3;  // this+8812〔uCharge8812(推断)〕
  *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 64))(v3) + 36) = 0;  // 虚调用 vt+64
  if ( *(this + 96) < 0x10u )  // 判定 “+384 SSO容量”
    pThis_5B = this + 91;
  else
    pThis_5B = (uint32_t *)*(this + 91);  // this+364〔pAnimNameStr(推断)〕
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(  // 虚调用 vt+1352
           this,
           pThis_5B,
           "Particle/AxeExpellerBrokenParts.ptl");  // 字符串 “Particle/AxeExpellerBrokenParts.ptl”
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
char /*usercall*/ sub_5D4EF0@<al>(uint8_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：火属性守卫表现分派（7028 帧位 2/3/5 三分支）
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
    (*(void (**)(void))(v4 + 1360))();  // 虚函数调用 槽+1360
  }
  v5 = *(uint32_t *)(*((uint32_t *)pArg1 + 30) + 148);
  if ( *((uint32_t *)pArg1 + 1639) == 8 )
  {
    switch ( sub_41A5E0((unsigned int)(pArg1 + 7028)) )  // 调 crypt4byte 解密校验
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 1332))(pArg1);  // 虚函数调用 槽+1332：默认虚槽桩
        break;
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        if ( v5 >= 4 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && pArg1[8812] != 0 )  // 虚函数调用 槽+308
        {
          v6 = (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 11, nArg3);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
          v26 = v6;
          pArg1[8812] = 0;
          v25 = (double)v6 * 0.0099999998;  // ×0.01f（百分数转比例）
          pMem = operator new(0x80u);  // 堆分配 128 字节对象
          Block = pMem;
          v27 = 0;
          if ( pMem == nullptr )  // 若 pMem 为空
            goto LABEL_18;
          v26 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 740))(pArg1);  // 虚函数调用 槽+740：属性块 +4 浮点壳（GetHP 族）
          *(float *)&v18 = (double)v26 * v25;
          v8 = (int *)sub_4D6810(pMem, v18, 500, 1, 1);  // 调 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
          goto LABEL_19;
        }
        break;
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        if ( v5 >= 4 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && pArg1[8812] != 0 )  // 虚函数调用 槽+308
        {
          v25 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 2, nArg3));  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
          v9 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 3);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
          pArg1[8812] = 0;
          pMem2 = operator new(0x7Cu);  // 堆分配 124 字节对象
          Block = pMem2;
          v27 = 1;
          if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
          {
            *(float *)&v19 = (float)SLODWORD(v25);  // 调 取 64 位值低 32 位(带符号)
            v8 = sub_4B3DF0(pMem2, 21, 1, v19, v9, 0);  // 结果 = CNChangeStatus 构造（六参）
          }
          else
          {
LABEL_18:
            v8 = nullptr;
          }
LABEL_19:
          v11 = *v8;
          v27 = -1;
          (*(void (/*thiscall*/ **)(int *, uint8_t *, uint8_t *, uint32_t, uint32_t, uint32_t))(v11 + 56))(v8, pArg1, pArg1, 0, 0, 0);  // 虚函数调用 槽+56：确认动作：+84 标志时 4
        }
        break;
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        if ( v5 >= 4 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && pArg1[8812] != 0 )  // 虚函数调用 槽+308
        {
          v25 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint8_t *, int, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 6, nArg2, nArg3));  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
          v12 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 7);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
          v13 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 8);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
          v23 = (float)SLODWORD(v25);  // 调 取 64 位值低 32 位(带符号)
          pArg1[8812] = 0;
          v21 = 5;
          v22 = 1;
          Block = operator new(0x1D0u);  // 堆分配 464 字节对象
          v27 = 2;
          if ( Block != nullptr )  // 若 Block 有效（非空）
            v14 = (int *)sub_64B6C0(v12, &v21, 1, v13, 1, 0);  // 结果 = 火焰动画查询（5910D0）
          else
            v14 = nullptr;
          v15 = *v14;
          v27 = -1;
          (*(void (/*thiscall*/ **)(int *, uint8_t *, uint8_t *, uint32_t, uint32_t))(v15 + 56))(v14, pArg1, pArg1, 0, 0);  // 虚函数调用 槽+56：确认动作：+84 标志时 4
        }
        break;
      default:
        break;
    }
  }
  LOBYTE(v16) = sub_5CF180(pArg1);  // 环绕音管理
  if ( pArg1[8669] == 1 )
  {
    LOBYTE(v16) = pArg1[8603];  // 调 取 16 位值低 8 位
    if ( (uint8_t)v16 == 0 && pArg1[8601] == 1 )
    {
      v16 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 840))(pArg1);  // 虚函数调用 槽+840：大状态 getter（this+6556）
      if ( v16 == 0 )
        LOBYTE(v16) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 1344))(pArg1);  // 虚函数调用 槽+1344
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
char /*thiscall*/ sub_5D51D0(char *this)  // 函数定义: 守卫字段大复位（8600..8738 全区 + 参数面向量重建）
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

  *((uint32_t *)this + 1639) = 19;  // 写 this+6556 = 19（大状态ID）
  *(this + 8668) = 1;  // this+8668 【推断】人偶行为模式
  *(this + 8669) = 0;  // 写 this+8669 = 0（守卫激活位）
  *(this + 8660) = 0;  // this+8660 【推断】事件配对/相位槽
  *(this + 8600) = 1;  // 写 this+8600 = 1（子类AI区）
  *(this + 8601) = 1;  // this+8601 子类 AI 状态字节 2
  *((uint16_t *)this + 4301) = 0;  // this+8602〔bAI8602(推断)〕
  *(this + 8604) = 0;  // 写 this+8604 = 0（子类 AI 状态字节）
  *((uint32_t *)this + 2156) = 0;  // this+8624〔uAI8624(推断)〕
  *((uint32_t *)this + 2157) = 0;  // this+8628〔nPoolTime(推断)〕
  *((uint32_t *)this + 2158) = 0;  // this+8632〔bDevourFlag(推断)〕
  *((uint32_t *)this + 2159) = 0;  // this+8636〔pDollTarget(推断)〕
  *((uint32_t *)this + 2160) = 0;  // this+8640〔uCastSlot8640(推断)〕
  *((uint32_t *)this + 2161) = 0;  // 写 this+8644 = 0（相位槽）
  *((uint32_t *)this + 2162) = 0;  // 写 this+8648 = 0（相位/缓存槽）
  *((uint32_t *)this + 2163) = 0;  // 写 this+8652 = 0（相位槽）
  pThis_21A0 = this + 8608;  // this+8608 骑乘/骑手槽
  *((uint32_t *)this + 1698) = 0;  // this+6792〔nVoiceParam0(推断)〕
  *((uint32_t *)this + 1699) = 1;  // this+6796〔nVoiceParam1(推断)〕
  *((uint32_t *)this + 1700) = 1;  // this+6800〔nVoiceParam2(推断)〕
  *((uint32_t *)this + 1701) = 2;  // this+6804〔nVoiceParam3(推断)〕
  *((uint32_t *)this + 1702) = 3;  // this+6808〔nVoiceParam4(推断)〕
  pThis_869 = *((uint32_t *)this + 2153);  // this+8612〔uAI8612(推断)〕
  v11 = 700;
  if ( pThis_869 != 0 )
    pThis_86A = (*((uint32_t *)this + 2154) - pThis_869) >> 2;  // this+8616〔uAI8616(推断)〕
  else
    pThis_86A = 0;
  if ( pThis_869 != 0 && pThis_86A < (*((uint32_t *)this + 2155) - pThis_869) >> 2 )  // this+8620〔uAI8620(推断)〕
  {
    pThis_86A2 = *((uint32_t **)this + 2154);
    *pThis_86A2 = 700;
    *((uint32_t *)this + 2154) = pThis_86A2 + 1;  // this+8616〔uAI8616(推断)〕
  }
  else
  {
    sub_430C80(*((void **)this + 2154), 1, (int)&v11);  // uint32 vector 区间插入（同值填充）
  }
  v6 = *((uint32_t *)pThis_21A0 + 1);
  v11 = 1000;
  if ( v6 != 0 )
    v7 = (*((uint32_t *)pThis_21A0 + 2) - v6) >> 2;  // 向量元素数 = (end−begin)/4
  else
    v7 = 0;
  if ( v6 != 0 && v7 < (*((uint32_t *)pThis_21A0 + 3) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
  {
    v8 = *((uint32_t **)pThis_21A0 + 2);
    *v8 = 1000;
    *((uint32_t *)pThis_21A0 + 2) = v8 + 1;  // pThis_21A0[2] = v8 + 1
  }
  else
  {
    sub_430C80(*((void **)pThis_21A0 + 2), 1, (int)&v11);  // uint32 vector 区间插入（同值填充）
  }
  *(this + 8685) = 0;  // this+8685 【推断】挥击/散射语音锁存
  *(this + 8686) = 0;
  v9 = *(uint32_t *)this;
  *((uint32_t *)this + 2175) = 0;  // this+8700〔uPhase8700(推断)〕
  *(this + 8721) = 0;
  *(this + 8722) = 0;
  (*(void (/*thiscall*/ **)(char *, uint32_t))(v9 + 820))(this, 0);  // 虚函数调用 槽+820：写 +6740 字节
  *(this + 8737) = 0;
  *(this + 8738) = 0;
  result = sub_698F90((int)(this + 8724), 100, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint32_t *)this + 2179) = 3;  // this+8716〔uArr8716〕
  *((uint32_t *)this + 2188) = 1065353216;  // this+8752 = 1.0f
  *(this + 8723) = 1;
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5D5370 sub_5D5370 —— 近身随机起手（50% 门 + 150 距离）
// 50% 随机命中、1813 槽对象 vt+40(17) 为玩家、vt+8 距离 < 150 三条件齐备时，
// ·sub_431230 打包参数 {1} 后 vt+560(8, ...) 转 8 号状态（近身攻击起手）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D5370(uint32_t *this)  // 函数定义: 近身随机起手（50% 门 + 150 距离）
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  if ( rand() % 100 < 50  // 调 取伪随机数
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1813) + 40))(*(this + 1813), 17) != 0  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 8))(this, *(this + 1813), 0) < 150 )  // 虚调用 vt+8
  {
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 1;
    sub_431230((int)v2, v6);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);  // 虚调用 vt+560
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
  }
}



// 时钟门 AI（sub_699000; this+8853/8854）
// ------------------------------------------------------------
// 0x5D5420 sub_5D5420 —— 冰守卫光环收束（2210 时钟 + 8F850C 对象表 16..31）
// ·sub_5D2470 尾段后 2175 空闲门内，2216 时钟到点且 vt+308 为 1 时扫描 8F850C 表 16..31 槽，
// 对 +196 槽对象 vt+724 == 0 者 ·sub_487F60 收束；随后清 8853/8854，2210 时钟按 2218 重排。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D5420(int *this)  // 函数定义: 冰守卫光环收束（2210 时钟 + 8F850C 对象表 16..31）
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

  LOBYTE(pThis_8A2) = sub_5D2470((int)this);  // 受击挂件清理 + 守卫帧收尾（本区多个 AI 的公共尾段）
  if ( *(this + 2175) == -1 )  // this+8700〔uPhase8700(推断)〕
  {
    fld_e2216 = *(this + 2216);
    pThis_8A2 = sub_699000((int)(this + 2210));  // 【clock_now(clk)】
    if ( pThis_8A2 >= fld_e2216 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )  // 虚调用 vt+308
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
          v5 = *(uint32_t *)(i + dword_8F850C);  // 全局 dword_8F850C = 房间/席位表
          if ( v5 != 0 )
          {
            pObj = *(uint32_t *)(v5 + 196);
            if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 724))(pObj) == 0 )  // 虚函数调用 槽+724：读 +6552 霸体字节
            {
              v18 = *(uint32_t *)(v5 + 196);
              sub_487F60(&v18);  // 4 字节元素尾插
            }
          }
        }
        v19 = -1;
      }
      *((uint8_t *)this + 8853) = 0;  // this+8853 相位标志
      *((uint8_t *)this + 8854) = 0;  // this+8854 相位标志
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
unsigned int /*thiscall*/ sub_5D56A0(uint32_t *this)  // 函数定义: 随机段状态选择（24/25 号, 时钟门）
{
  int fld_e2212; // edi
  unsigned int result; // eax
  int fld_e2210; // eax  | +0x2288 → 相位/档位槽（0x5CFB50：!=2 才加绘，并按 +4*本槽 取色档）（CNGuardBlock）
  uint8_t v5[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-18h]
  int v8; // [esp+18h] [ebp-14h]
  int nRand; // [esp+1Ch] [ebp-10h] BYREF
  int v10; // [esp+28h] [ebp-4h]

  sub_5D2470((int)this);  // 受击挂件清理 + 守卫帧收尾（本区多个 AI 的公共尾段）
  fld_e2212 = *(this + 2212);  // this+8848〔bPhase8848〕
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  if ( fld_e2212 + *(this + 2211) < result || fld_e2212 == 0 )  // this+8844〔uPhaseClock8844〕
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 1 )  // 虚调用 vt+308
    {
      Block = nullptr;
      v7 = 0;
      v8 = 0;
      v10 = 0;
      nRand = rand() % 3;  // 调 取伪随机数
      sub_431230((int)v5, &nRand);  // uint32 vector push_back
      fld_e2210 = *(this + 2210);  // this+8840〔uPhase8840(推断)〕
      if ( fld_e2210 == 2 || fld_e2210 == 1 )  // 若 fld_e2210 == 2 与/或 fld_e2210 == 1
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 24, v5, 2, 0);  // 虚调用 vt+560
      else
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 25, v5, 2, 0);  // 虚调用 vt+560
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);  // 虚调用 vt+564
      v10 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
      Block = nullptr;
      v7 = 0;
      v8 = 0;
    }
    *(this + 2211) = *(this + 2213);  // this+8844〔uPhaseClock8844〕
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    *(this + 2212) = result;  // this+8848〔bPhase8848〕
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
int /*thiscall*/ sub_5D57B0(uint32_t *this)  // 函数定义: 军团同袍点名（20 号状态 + 坐标双参）
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

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 结果 = 虚调用 vt+308
  if ( (uint8_t)result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
      v5 = *(uint32_t *)(fld_e29 + 8);
      result = v5 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)i >= result )
        break;
      v6 = *(uint32_t *)(fld_e29 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj2 = *(uint32_t *)(v6 + 4 * i);
      else
        pObj2 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0 )  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      {
        fld_e292 = *(this + 29);  // 读 fld_e292 = this+116（观察者容器）
        v9 = *(uint32_t *)(fld_e292 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        pObj = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
        if ( pObj != 0
          && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 704  // 虚函数调用 槽+340：三元组基址（+284，vt+340）
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 568))(pObj) != 20  // 虚函数调用 槽+568
          && *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
        {
          memset(&pBuf[1], 0, 12);  // 清零 12 字节块
          fld_e1813 = *(this + 1813);  // this+7252〔pTarget7252〕
          v15 = 0;
          fld_e18132 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 48))(fld_e1813);  // 虚函数调用 槽+48：更新槽（64A5A0 + 41C5E0/52E4D0）
          sub_431230((int)pBuf, &fld_e18132);  // uint32 vector push_back
          fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 52))(*(this + 1813));  // 虚函数调用 槽+52：播 AURA_SHIELD_LOOP（第二挂点，15 行）
          sub_431230((int)pBuf, &fld_e18132);  // uint32 vector push_back
          (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)pObj + 560))(pObj, 20, pBuf, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
          v15 = -1;
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
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
int /*thiscall*/ sub_5D5920(uint32_t *this, int nArg2, int nArg3)  // 函数定义: 破碎颗粒对象构造（ExpellerBrokenParts.ptl）
{
  int result; // eax

  if ( operator new(0x12Cu) != nullptr )  // 堆分配 300 字节对象
  {
    if ( *(this + 96) < 0x10u )  // 判定 “+384 SSO容量”
      result = sub_4C3640(this + 91, "Particle/ExpellerBrokenParts.ptl", this);  // 字符串 “Particle/ExpellerBrokenParts.ptl”
    else
      result = sub_4C3640(*(this + 91), "Particle/ExpellerBrokenParts.ptl", this);  // 字符串 “Particle/ExpellerBrokenParts.ptl”
  }
  else
  {
    result = 0;
  }
  *(this + 2166) = result;  // this+8664〔uAI8664(推断)〕
  return result;
}



// 复合门（this+200/568/8601/8603/8669 —— 最后受击时刻联动）
// ------------------------------------------------------------
// 0x5D59B0 sub_5D59B0 —— 军团同袍联动帧（主帧包装）
// 姿态 8 时按 7028 帧位 0/1 走 vt+1332 收招；==2 且 vt+200 状态 +148>=4、vt+568 != 20 时
// 调 ·0x5D57B0 同袍点名。尾段 ·sub_5CF180 + 8669/8603/8601 三条件走 vt+1344（与 ·0x5D0070 同构）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D59B0(int this)  // 函数定义: 军团同袍联动帧（主帧包装）
{
  int pThis_348; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
  {
    if ( sub_41A5E0(this + 7028) == 0 || sub_41A5E0(this + 7028) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);  // this+1332 装备/动画定义对象
    }
    else if ( sub_41A5E0(this + 7028) == 2  // crypt4byte 解密校验（·0x41A590 逆运算）
           && *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 4  // this+200 主状态
           && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 568))(this) != 20 )  // this+568 提醒数值
    {
      sub_5D57B0((uint32_t *)this);  // 军团同袍点名（20 号状态 + 坐标双参）
    }
  }
  LOBYTE(pThis_348) = sub_5CF180((uint32_t *)this);  // 环绕音管理
  if ( *(uint8_t *)(this + 8669) == 1 )  // 判定 “+8669 守卫激活位”
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8603);  // this+8603 盾空闲门
    if ( (uint8_t)pThis_348 == 0 && *(uint8_t *)(this + 8601) == 1 )  // this+8601 站立位
    {
      pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 虚函数调用 槽+840：大状态 getter（this+6556）
      if ( pThis_348 == 0 )
        LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);  // 虚函数调用 槽+1344
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
int /*userpurge*/ sub_5D5A60@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int ArgList, float fArg5, int nArg6, int nArg7)  // 实现：军团编队召唤（20 号状态, 挑衅人偶出场）
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

  result = *(uint32_t *)(pArg1 + 8816);  // pArg1+8816〔uCharge8816(推断)〕
  if ( result == 0 )
  {
    sub_5D3640((int *)pArg1);  // 编队档位清位（vt+1172 档位 → 子对象 +32..+160 五槽）
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1172))(pArg1);  // 虚函数调用 槽+1172
    *(uint32_t *)(pArg1 + 8816) = v9;  // pArg1+8816〔uCharge8816(推断)〕
    if ( v9 > 5 )
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 1);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
    else
      result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 384))(pArg1, 0);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
    *(uint32_t *)(pArg1 + 8716) = result;  // pArg1+8716〔uArr8716(推断)〕
  }
  if ( ArgList == 8 )
  {
    result = **(uint32_t **)(LODWORD(fArg5) + 4) - 2;  // 调 取 64 位值低 32 位
    switch ( **(uint32_t **)(LODWORD(fArg5) + 4) )  // 调 取 64 位值低 32 位
    {
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        *(uint8_t *)(pArg1 + 8812) = 1;  // pArg1+8812〔uCharge8812(推断)〕
        break;
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        nArg22 = nArg2;
        nArg32 = nArg3;
        for ( i = 0; ; ++i )
        {
          v11 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 700))(pArg1, nArg32, nArg22);  // 虚函数调用 槽+700：读 +6296 槽
          v12 = *(uint32_t *)(v11 + 4);
          v13 = v12 != 0 ? (*(uint32_t *)(v11 + 8) - v12) >> 2 : 0;  // 向量元素数 = (end−begin)/4
          if ( (int)i >= v13 )
            break;
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 700))(pArg1);  // 虚函数调用 槽+700：读 +6296 槽
          v15 = *(uint32_t *)(v14 + 4);
          if ( v15 != 0 && i < (*(uint32_t *)(v14 + 8) - v15) >> 2 )  // 向量元素数 = (end−begin)/4
            v16 = *(uint32_t *)(v15 + 4 * i);
          else
            v16 = 0;
          if ( *(uint32_t *)(v16 + 4) == pArg1 )
          {
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 700))(pArg1);  // 虚函数调用 槽+700：读 +6296 槽
            v17 = sub_517740(i);
            pObj = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                    v17,
                    0,
                    &IRDAppendage `RTTI Type Descriptor',
                    &CNProvocationDollAura `RTTI Type Descriptor',
                    0);
            if ( pObj != 0 )
            {
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 虚函数调用 槽+76：槽（542940 + 485020）
              break;
            }
          }
        }
        v19 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 4, nArg32, nArg22);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
        v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 5);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
        pMem = operator new(0x98u);  // 堆分配 152 字节对象
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
          v22 = sub_591260(pMem, v19, 0);  // 结果 = CNProvocationDollAura 挑衅人偶光环构造
        else
          v22 = nullptr;
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t))(*v22 + 56))(v22, pArg1, pArg1, 0, 0);  // 虚调用 vt+56
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*v22 + 64))(v22);  // 结果 = 虚调用 vt+64
        *(uint32_t *)(result + 40) = v20;
        break;
      default:
        break;
    }
  }
  if ( *(uint8_t *)(pArg1 + 8669) == 1 )  // pArg1+8669〔bGuardActive8669(推断)〕
    return sub_4E33D0(ArgList, fArg5, nArg6, nArg7);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
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
uint8_t /*userpurge*/ sub_5D5C30@<al>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3, float *pArg4, int nArg5)  // 实现：守卫格挡特效（GuardSpark.ani + GuardCircle.ani 双层）
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
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v7 = pDwArg1[161];
    goto LABEL_7;
  }
  v8 = pDwArg1[30];
  if ( v8 != 0 )
  {
    if ( *(uint32_t *)(v8 + 148) == -1 )
      result = (uint8_t)sub_4938F0(pDwArg1[30]);  // 调 调 sub_4938F0
    v7 = *(uint32_t *)(v8 + 112);
LABEL_7:
    if ( v7 > 1 )
      return result;
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 348))(nArg3, nArg2) + 12) != 0  // 虚函数调用 槽+348
    || (v9 = *pDwArg1,
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3),  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        (*(uint8_t (/*thiscall*/ **)(int *, int))(v9 + 180))(pDwArg1, v10) != 0) )  // 虚函数调用 槽+180：目标是否在前方/后方（按 walkDir 朝向 +152）
  {
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1104))(pDwArg1, 13);  // 虚调用 vt+1104
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*pDwArg1 + 876))(pDwArg1, 0, 300, 300, 0, -3000, 1);  // 虚调用 vt+876
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 虚调用 vt+876
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*pDwArg1 + 888))(pDwArg1, 0, 0, 1000, 1000);  // 虚调用 vt+888
  v11 = *pDwArg1;
  v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);  // 结果 = 虚调用 vt+152
  v13 = sub_432E50(v12);  // 结果 = 关系码对调映射
  (*(void (/*thiscall*/ **)(int *, int))(v11 + 896))(pDwArg1, v13);  // 虚函数调用 槽+896：默认虚槽桩（11 行 return）
  v23 = (uint64_t)(pArg4[3] * 0.5 + *pArg4);
  v22 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*pDwArg1 + 124))(pDwArg1, (uint64_t)(pArg4[3] * 0.5 + *pArg4) >> 32);  // 结果 = 虚调用 vt+124
  v26 = (uint64_t)(pArg4[5] * 0.5 + pArg4[2]);
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    v14 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardSpark.ani", 1);  // 字符串 “Character/Swordman/Effect/Animation/GuardSpa”
  else
    v14 = 0;
  v15 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  pObj = (int)v15;
  if ( v15 != nullptr )  // 若 v15 有效（非空）
  {
    sub_44E0D0(v15, v14, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pObj = &CNRDPooledObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  }
  else
  {
    v16 = 0;
  }
  sub_45FE80(a1[29], v16, 2, 0, v16, (int)a1, 0);  // 调 对象注册
  v17 = *(uint32_t *)v16;
  v18 = (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1);  // 结果 = 虚调用 vt+152
  (*(void (/*thiscall*/ **)(int, int))(v17 + 148))(v16, v18);  // 虚函数调用 槽+148：槽（12 行）
  v19 = v23;
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v16 + 112))(v16, v23, v22, v26);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    v24 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardCircle.ani", 1);  // 字符串 “Character/Swordman/Effect/Animation/GuardCir”
  else
    v24 = 0;
  v20 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  if ( v20 != nullptr )  // 若 v20 有效（非空）
  {
    sub_44E0D0(v20, v24, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)v20 = &CNRDPooledObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  }
  else
  {
    pObj2 = nullptr;
  }
  sub_45FE80(pDwArg1[29], (int)pObj2, 2, 0, (int)pObj2, (int)pDwArg1, 0);  // 调 对象注册
  v25 = *(uint32_t *)pObj2;
  v21 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 结果 = 虚调用 vt+152
  (*(void (/*thiscall*/ **)(char *, int))(v25 + 148))(pObj2, v21);  // 虚函数调用 槽+148：槽（12 行）
  return (*(int (/*thiscall*/ **)(char *, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, v19, v22, v26);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D5ED0 sub_5D5ED0 —— 特效动画槽释放（idx2209）
// 释放特效槽 idx2209（·0x5D6590 处装载 ksguard_light.ani 的落点）：·sub_42AF90 解引用 +
// ·sub_657740(句柄, 228) 按 228 池标签归还资源，随后槽置空。
// 【推断】疑属光守卫或四属性守卫析构路径（与 ·0x5D6860 的 Haste 槽释放同构）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D5ED0(void ***this)  // 函数定义: 特效动画槽释放（idx2209）
{
  int fld_e2209; // esi
  int result; // eax

  fld_e2209 = (int)*(this + 2209);
  if ( fld_e2209 != 0 )
  {
    sub_42AF90(*(this + 2209));  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e2209, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
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
void /*thiscall*/ sub_5D5F10(int *this)  // 函数定义: 锤王大地崩三相位主处理（R_HAMMER_KING 语音 + 双 PassiveObject 震地）
{
  int nCurHp; // eax
  int nVtHp; // edx
  int fld_e2241; // edi
  int fld_e2216; // edi
  unsigned int nIdx1; // edi
  int nFollowerCnt; // ebx
  int fld_e29; // ecx
  int nBegin1; // edx
  int nCount1; // eax
  int nBegin2; // edx
  int pScanObj; // eax
  int fld_e292; // ecx
  int nSkillListBegin; // edx
  int nSkillListCnt; // eax
  int nSkillIdxSeed; // eax
  int nVt2; // ebx
  int nSpawnSpan; // edi
  int nAtkReq; // eax
  int fld_e2244; // eax  | +0x2310 → 事件档位（同 8972 成对；0x5D1D90）（CNHammerKing）
  int fld_e2230; // ebx
  int pAnim; // eax
  int *pQuake; // edi
  int nQuakeVt; // edx
  int nQuakeVt2; // ebx
  int nSelfZ; // eax
  int nSelfY; // eax
  int nSelfX; // eax
  int pRingAnim; // eax
  int *pRing; // edi
  int nRingVt; // edx
  int nRingVt2; // ebx
  int nSelfZ2; // eax
  int nSelfY2; // eax
  int nSelfX2; // eax
  unsigned int i; // ebx
  int fld_e293; // ecx
  int nBegin3; // edx
  int nCount3; // eax
  int nBegin4; // edx
  int pScanObj2; // eax
  int pCandRaw; // eax
  int pCand; // edi
  int nCandVt; // edx
  int nCandX; // ebx
  int nRand; // edx
  int nCandVt2; // eax
  int nCandY; // eax
  int nCandVt3; // edx
  int nCandX2; // eax
  int nCandY2; // eax
  int nCandZ2; // eax
  BOOL nRand2; // [esp-10h] [ebp-5Ch]
  float v54; // [esp-8h] [ebp-54h]
  int nHitFlag; // [esp-4h] [ebp-50h]
  float fHitX; // [esp+Ch] [ebp-40h] BYREF
  float fHitY; // [esp+10h] [ebp-3Ch]
  int nVal10f; // [esp+14h] [ebp-38h]
  int nVal30fa; // [esp+18h] [ebp-34h]
  int nVal30fb; // [esp+1Ch] [ebp-30h]
  int nVal5f; // [esp+20h] [ebp-2Ch]
  void *pBuf[4]; // [esp+24h] [ebp-28h] BYREF
  int nTmp; // [esp+34h] [ebp-18h] BYREF
  int v64; // [esp+38h] [ebp-14h]
  float v65; // [esp+3Ch] [ebp-10h] BYREF
  int v66; // [esp+48h] [ebp-4h]

  sub_5D2470((int)this);  // 受击挂件清理 + 守卫帧收尾（本区多个 AI 的公共尾段）
  nCurHp = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);  // vt+736: 当前HP
  nVtHp = *this;
  v64 = nCurHp;
  v65 = (float)nCurHp;
  v64 = (*(int (/*thiscall*/ **)(int *))(nVtHp + 740))(this);  // vt+740: 最大HP
  if ( v65 / (double)v64 <= *((float *)this + 2247) )  // 血量比 ≤ this+2247 阈值（虚弱态门）
  {
    fld_e2241 = *(this + 2241);  // this+8964〔nDmgCap〕
    if ( sub_699000((int)(this + 2235)) >= fld_e2241 )  // 【clock_now(clk)】
      *(uint8_t *)(*(this + 1905) + 96) = 1;  // 子对象 +96 阶段旗标（虚弱表现）
  }
  fld_e2216 = *(this + 2216);
  if ( sub_699000((int)(this + 2210)) >= fld_e2216 && (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 5 )  // 【clock_now(clk)】
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )  // 存活
    {
      nIdx1 = 0;
      nFollowerCnt = 0;
      while ( 1 )  // 统计场上 CNTinSwordManExpeller 数量
      {
        fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
        nBegin1 = *(uint32_t *)(fld_e29 + 8);
        nCount1 = nBegin1 != 0 ? (*(uint32_t *)(fld_e29 + 12) - nBegin1) >> 2 : 0;  // 向量元素数 = (end−begin)/4
        if ( (int)nIdx1 >= nCount1 )
          break;
        nBegin2 = *(uint32_t *)(fld_e29 + 8);
        if ( nBegin2 != 0 && nIdx1 < (*(uint32_t *)(fld_e29 + 12) - nBegin2) >> 2 )  // 向量元素数 = (end−begin)/4
          pScanObj = *(uint32_t *)(nBegin2 + 4 * nIdx1);
        else
          pScanObj = 0;
        if ( __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
               pScanObj,
               0,
               &CNRDObject `RTTI Type Descriptor',
               &CNTinSwordManExpeller `RTTI Type Descriptor',
               0) != 0 )
          ++nFollowerCnt;  // 随从计数
        ++nIdx1;
      }
      if ( nFollowerCnt < *(this + 2245) )  // 随从数 < this+2245 上限 → 召唤
      {
        fld_e292 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);  // this+116〔会话上下文〕
        nSkillListBegin = *(uint32_t *)(fld_e292 + 364);
        if ( nSkillListBegin != 0 )
          nSkillListCnt = (*(uint32_t *)(fld_e292 + 368) - nSkillListBegin) >> 5;
        else
          nSkillListCnt = 0;
        v64 = 224 * nSkillListCnt;  // 技能表占位长度（0xE0 字节/项）
        nSkillIdxSeed = sub_424FF0(fld_e292);  // 结果 = 列数换算
        nVt2 = *this;
        nSpawnSpan = 120 * (nSkillIdxSeed + 3);  // 散布半径
        nAtkReq = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 152))(  // 结果 = 虚调用 vt+152
                this,
                2,
                0,
                0,
                0xFFFF,
                0,
                0,
                0,
                0);
        fld_e2244 = (*(int (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int))(*this + 376))(  // 结果 = 虚调用 vt+376
                this,
                *(this + 2244),  // this+8976〔uEvtState8976〕
                v64 / 2,
                nSpawnSpan / 2,
                0,
                nAtkReq);
        (*(void (/*thiscall*/ **)(int *, int, int))(nVt2 + 592))(this, 705, fld_e2244);  // 生成 705 号随从
      }
    }
    if ( *((uint8_t *)this + 8936) == 0 )  // 一次性播报门
    {
      sub_4DB130(24, 0);  // 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_HAMMER_KING", -1, 0, 0);  // 字符串 “R_HAMMER_KING”
      *((uint8_t *)this + 8936) = 1;  // this+8936 相位字节
    }
    *((uint8_t *)this + 8853) = 0;  // this+8853 相位标志
    *((uint8_t *)this + 8854) = 0;  // this+8854 相位标志
    sub_698F90((int)(this + 2210), *(this + 2243), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  fld_e2230 = *(this + 2230);  // this+8920〔uPhase8920〕
  if ( sub_699000((int)(this + 2224)) >= fld_e2230 )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 308))(this);  // 虚调用 vt+308
    *((uint8_t *)this + 8909) = 0;  // this+8909 相位字节
    *((uint8_t *)this + 8910) = 0;  // this+8910 相位字节
    sub_698F90((int)(this + 2224), *(this + 2246), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8  // 姿态8=震地
    && (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 3  // 相位3=落地帧
    && sub_699000((int)(this + 2217)) > *(this + 2232)  // 【clock_now(clk)】
    && *((uint8_t *)this + 8924) == 0 )  // 一次性门
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 虚调用 vt+888
    v64 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 ? 1 : -1;  // 朝向 ±1
    LODWORD(v65) = (uint64_t)((double)v64 * *((float *)this + 2188) * 125.0);  // 朝向 × 半径系数 ×125
    nTmp = sub_44B6C0(284);  // CNRDPooledObject 池取
    v66 = 0;
    if ( nTmp != 0 )
    {
      v64 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
      LOBYTE(v66) = 1;  // 调 取 16 位值低 8 位
      if ( v64 != 0 )
        pAnim = sub_431860((char)"PassiveObject/Common/Animation/EarthQuake.ani", 1);  // 主震波纹动画
      else
        pAnim = 0;
      LOBYTE(v66) = 0;  // 调 取 16 位值低 8 位
      pQuake = (int *)sub_44E1F0(pAnim, 1);  // 结果 = CNRDPooledObject 构造（虚表覆盖壳）
    }
    else
    {
      pQuake = nullptr;
    }
    nQuakeVt = *pQuake;
    v66 = -1;
    (*(void (/*thiscall*/ **)(int *, int))(nQuakeVt + 72))(pQuake, 2);  // 虚函数调用 槽+72：槽（4BE520/4F2D40 + 4848
    sub_45FE80(*(this + 29), (int)pQuake, 2, 0, (int)pQuake, (int)this, 0);  // 调 对象注册
    nQuakeVt2 = *pQuake;
    nSelfZ = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
    nSelfY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nSelfZ);  // 结果 = 虚调用 vt+124
    nSelfX = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nSelfY - 1);  // 自身 X 偏 -1
    (*(void (/*thiscall*/ **)(int *, int))(nQuakeVt2 + 112))(pQuake, LODWORD(v65) + nSelfX);  // 落点=自身X+朝向偏移
    nTmp = sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
    v66 = 2;
    if ( nTmp != 0 )
    {
      v64 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
      LOBYTE(v66) = 3;  // 调 取 16 位值低 8 位
      if ( v64 != 0 )
      {
        pRingAnim = sub_431860((char)"PassiveObject/Common/Animation/EarthQuakeRing.ani", 1);  // 外环波动画
        LOBYTE(v66) = 2;  // 调 取 16 位值低 8 位
        pRing = (int *)sub_44E1F0(pRingAnim, 1);  // 结果 = CNRDPooledObject 构造（虚表覆盖壳）
      }
      else
      {
        LOBYTE(v66) = 2;  // 调 取 16 位值低 8 位
        pRing = (int *)sub_44E1F0(0, 1);  // 结果 = CNRDPooledObject 构造（虚表覆盖壳）
      }
    }
    else
    {
      pRing = nullptr;
    }
    nRingVt = *pRing;
    v66 = -1;
    (*(void (/*thiscall*/ **)(int *, int))(nRingVt + 72))(pRing, 2);  // 虚函数调用 槽+72：槽（4BE520/4F2D40 + 4848
    sub_45FE80(*(this + 29), (int)pRing, 2, 0, (int)pRing, (int)this, 0);  // 调 对象注册
    nRingVt2 = *pRing;
    nSelfZ2 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
    nSelfY2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nSelfZ2);  // 结果 = 虚调用 vt+124
    nSelfX2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nSelfY2 - 2);  // 自身 X 偏 -2（内环错位）
    (*(void (/*thiscall*/ **)(int *, int))(nRingVt2 + 112))(pRing, LODWORD(v65) + nSelfX2);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
    for ( i = 0; ; ++i )  // 遍历场上对象做范围打击
    {
      fld_e293 = *(this + 29);  // 读 fld_e293 = this+116（观察者容器）
      nBegin3 = *(uint32_t *)(fld_e293 + 8);
      v64 = i;
      nCount3 = nBegin3 != 0 ? (*(uint32_t *)(fld_e293 + 12) - nBegin3) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)i >= nCount3 )
        break;
      nBegin4 = *(uint32_t *)(fld_e293 + 8);
      if ( nBegin4 != 0 && i < (*(uint32_t *)(fld_e293 + 12) - nBegin4) >> 2 )  // 向量元素数 = (end−begin)/4
        pScanObj2 = *(uint32_t *)(nBegin4 + 4 * i);
      else
        pScanObj2 = 0;
      pCandRaw = __RTDynamicCast(pScanObj2, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      pCand = pCandRaw;
      if ( (int *)pCandRaw != this  // 排除自己
        && pCandRaw != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pCandRaw + 308))(pCandRaw) == 1  // 存活
        && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCand + 128))(pCand) <= *(this + 2251) )  // Z ≤ this+2251
      {
        nCandVt = *(uint32_t *)pCand;
        v65 = 0.0;
        fHitX = 0.0;
        fHitY = 0.0;
        nVal10f = 0;
        nVal30fa = 0;
        nVal30fb = 0;
        nVal5f = 0;
        nCandX = (*(int (/*thiscall*/ **)(int))(nCandVt + 120))(pCand);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        nRand = rand() % 60;  // 调 取伪随机数
        nCandVt2 = *(uint32_t *)pCand;
        nTmp = nCandX + nRand - 30;  // 命中点X = 目标X ±30 随机抖动
        fHitX = (float)nTmp;
        nCandY = (*(int (/*thiscall*/ **)(int))(nCandVt2 + 124))(pCand);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        nCandVt3 = *(uint32_t *)pCand;
        nTmp = nCandY;
        nVal10f = 1092616192;  // 位型 10.0f
        fHitY = (float)nCandY;
        nVal30fa = 1106247680;  // 位型 30.0f
        nVal30fb = 1106247680;  // 位型 30.0f
        nVal5f = 1084227584;  // 位型 5.0f
        (*(void (/*thiscall*/ **)(int))(nCandVt3 + 44))(pCand);  // 虚函数调用 槽+44：定位槽（43C330/69C4C0/69C420 + 69A5F0/69A8
        nHitFlag = sub_605840(&v65, pCand, &fHitX, 1);  // 命中判定（返回命中位）
        v54 = v65;  // 命中系数
        nRand2 = rand() % 2 == 0;  // 随机朝向位
        nCandZ2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCand + 128))(pCand);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
        nCandY2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCand + 124))(pCand);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        nCandX2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCand + 120))(pCand);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
        sub_4E4A50(this, 30312, 0, nCandX2, nCandY2, nCandZ2, nRand2, 0, LODWORD(v54), nHitFlag);  // 30312 散射伤害
        i = v64;
      }
    }
    sub_424120(*(uint32_t **)(*(this + 29) + 132), *(this + 2249), *(this + 2250));  // 范围打击(半径=this+2249/2250)
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(  // 全局 dword_8F7C04 = 本机角色对象
      dword_8F7C04,  // 全局 dword_8F7C04 = 本机角色对象
      "HAMMER_KING_CRASH",  // 字符串 “HAMMER_KING_CRASH”
      -1,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 4));  // 虚调用 vt+208
    *((uint8_t *)this + 8924) = 1;  // 关门：每轮仅一次
  }
  if ( *(this + 2233) != 0  // 目标态==1 且存活 → vt+560 反应态 8
    && (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != 0  // 虚调用 vt+200
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) == 1  // 虚调用 vt+200
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )  // 虚调用 vt+308
  {
    memset(&pBuf[1], 0, 12);  // 清零 12 字节块
    v66 = 4;
    nTmp = 3;
    sub_431230((int)pBuf, &nTmp);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(int *, int, void **, int, uint32_t))(*this + 560))(this, 8, pBuf, 2, 0);  // setState 8
    (*(void (/*thiscall*/ **)(int *))(*this + 564))(this);  // 虚调用 vt+564
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
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
int /*thiscall*/ sub_5D6590(float *this)  // 函数定义: 光守卫参数装载（ksguard_light.ani + vt+384 十一连读）
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

  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 1308))(this);  // this+1308 动画行向量 begin
  *(uint8_t *)(*((uint32_t *)this + 1905) + 64) = 0;  // this+7620〔pStatusPanel(推断)〕
  pThis_180 = (double)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);  // this+384 【推断】动画件名 SSO 容量判据
  v3 = *(uint32_t *)this;
  *(this + 2221) = pThis_180 * 0.0099999998;  // this+8884〔uPhase8884〕
  v4 = (*(int (/*thiscall*/ **)(float *, int))(v3 + 384))(this, 1);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v5 = *this;
  *(this + 2222) = (double)v4 * 0.0099999998;  // this+8888〔uPhase8888〕
  v6 = (double)(*(int (/*thiscall*/ **)(float *, int))(LODWORD(v5) + 384))(this, 2);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v7 = *this;
  *(this + 2223) = v6 * 0.0099999998;  // this+8892〔nGlowCenter8892(推断)〕
  v8 = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v7) + 384))(this, 3);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v9 = *this;
  *((uint32_t *)this + 2225) = v8;  // this+8900〔uGlowPeriod8900(推断)〕
  *((uint32_t *)this + 2226) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v9) + 384))(this, 4);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 5);  // this+384 【推断】动画件名 SSO 容量判据
  v11 = *this;
  *((uint32_t *)this + 2227) = pThis_1802;  // this+8908〔uPhase8908〕
  *((uint32_t *)this + 2229) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v11) + 384))(this, 6);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  pThis_1803 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 7);  // this+384 【推断】动画件名 SSO 容量判据
  v13 = *this;
  *((uint32_t *)this + 2230) = pThis_1803;  // this+8920〔uPhase8920〕
  *((uint32_t *)this + 2231) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v13) + 384))(this, 8);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  pThis_1804 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 9);  // this+384 【推断】动画件名 SSO 容量判据
  v15 = *this;
  *((uint32_t *)this + 2232) = pThis_1804;  // this+8928〔uPhase8928〕
  *(this + 2233) = (double)(*(int (/*thiscall*/ **)(float *, int))(LODWORD(v15) + 384))(this, 10) * 0.0099999998;  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_light.ani", 1);  // 字符串 “equipment/character/common/title/titleanimat”
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
int /*thiscall*/ sub_5D6700(float *this)  // 函数定义: 风守卫参数装载（Haste.ani + ksguard_wind.ani 双载）
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

  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 1308))(this);  // this+1308 动画行向量 begin
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    v2 = sub_431860((char)"Common/ActiveStatus/Animation/Haste.ani", 1);  // 字符串 “Common/ActiveStatus/Animation/Haste.ani”
  else
    v2 = 0;
  v3 = *(uint32_t *)this;
  *((uint32_t *)this + 2245) = v2;  // this+8980〔uEffect8980〕
  *((uint32_t *)this + 2253) = (*(int (/*thiscall*/ **)(float *, uint32_t))(v3 + 384))(this, 0);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  pThis_180 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);  // this+384 【推断】动画件名 SSO 容量判据
  v5 = *(uint32_t *)this;
  *((uint32_t *)this + 2254) = pThis_180;  // this+9016〔uPhaseC9016〕
  *((uint32_t *)this + 2255) = (*(int (/*thiscall*/ **)(float *, int))(v5 + 384))(this, 2);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);  // this+384 【推断】动画件名 SSO 容量判据
  v7 = *(uint32_t *)this;
  *(this + 2256) = (double)pThis_1802 * 0.0099999998;  // this+9024〔uPhaseC9024〕
  v8 = (double)(*(int (/*thiscall*/ **)(float *, int))(v7 + 384))(this, 4);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v9 = *this;
  *(this + 2257) = v8 * 0.0099999998;  // this+9028〔uPhaseC9028〕
  v10 = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v9) + 384))(this, 5);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v11 = *this;
  *((uint32_t *)this + 2259) = v10;  // this+9036〔uPhaseC9036〕
  *((uint32_t *)this + 2260) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v11) + 384))(this, 6);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  pThis_1803 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 7);  // this+384 【推断】动画件名 SSO 容量判据
  v13 = *this;
  *((uint32_t *)this + 2261) = pThis_1803;  // this+9044〔uPhaseC9044〕
  *((uint32_t *)this + 2262) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v13) + 384))(this, 8);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_wind.ani", 1);  // 字符串 “equipment/character/common/title/titleanimat”
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
int /*thiscall*/ sub_5D6860(void ***this)  // 函数定义: 加速表现槽释放（idx2245）
{
  int fld_e2245; // esi  | +0x2314 → 特效/资源槽（0x5D7500 析构释放并清零）（CNGuardWind）
  int result; // eax

  fld_e2245 = (int)*(this + 2245);  // this+8980〔uEffect8980〕
  if ( fld_e2245 != 0 )
  {
    sub_42AF90(*(this + 2245));  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e2245, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  *(this + 2245) = nullptr;  // this+8980〔uEffect8980〕
  return result;
}



// 冰守卫特效：ksguard_ice.ani（31L）
// ------------------------------------------------------------
// 0x5D68A0 sub_5D68A0 —— 冰守卫参数装载（ksguard_ice.ani + vt+384 五连读）
// vt+1308 清相位后经 vt+384(0..4) 导入 this+2218..2222 档，末装载 ksguard_ice.ani 到特效槽 idx2209。
// 与 ·0x5D6590 同面（差异：档位仅 5 个、无 *0.01 浮点转写 —— 冰守卫参数面较短）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D68A0(uint32_t *this)  // 函数定义: 冰守卫参数装载（ksguard_ice.ani + vt+384 五连读）
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 虚调用 vt+1308
  *(this + 2218) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 虚调用 vt+384
  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 结果 = 虚调用 vt+384
  v3 = *this;
  *(this + 2219) = v2;  // this+8876〔uPhase8876〕
  *(this + 2220) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 384))(this, 2);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);  // 结果 = 虚调用 vt+384
  v5 = *this;
  *(this + 2221) = v4;  // this+8884〔uPhase8884〕
  *(this + 2222) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 4);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_ice.ani", 1);  // 字符串 “equipment/character/common/title/titleanimat”
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
int /*thiscall*/ sub_5D6960(uint32_t *this)  // 函数定义: 防御守卫参数装载（ksguard_protection.ani + R_DEFEN_GUARD 语音四件套）
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

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 虚调用 vt+1308
  v2 = 0;
  pThis_8A5 = this + 2213;
  do
    *pThis_8A5++ = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v2++);  // 虚调用 vt+384
  while ( v2 < 3 );
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);  // 结果 = 虚调用 vt+384
  v5 = *this;
  *(this + 2216) = v4;
  *(this + 2225) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 4);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);  // 结果 = 虚调用 vt+384
  v7 = *this;
  *(this + 2226) = v6;  // this+8904〔bGlowAlpha8904(推断)〕
  *(this + 2179) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v7 + 384))(this, 6);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v8 = 8;
  pThis_8AB = this + 2219;
  do
  {
    *(pThis_8AB - 2) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v8 - 1);  // 虚调用 vt+384
    *pThis_8AB = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v8);  // 结果 = 虚调用 vt+384
    v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v8 + 1);  // 结果 = 虚调用 vt+384
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
  *(this + 2208) = 0;  // this+8832〔uCharge8832〕
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_protection.ani", 1);  // 字符串 “equipment/character/common/title/titleanimat”
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
int /*thiscall*/ sub_5D6AF0(uint32_t *this)  // 函数定义: 火守卫参数装载（Particle/TrackingFire.ptl 追踪火 + ksguard_flame.ani）
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

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 虚调用 vt+1308
  if ( operator new(0x12Cu) != nullptr )  // 堆分配 300 字节对象
  {
    if ( *(this + 96) < 0x10u )  // 判定 “+384 SSO容量”
      pThis_5B = sub_4C3640(this + 91, "Particle/TrackingFire.ptl", this);  // 字符串 “Particle/TrackingFire.ptl”
    else
      pThis_5B = sub_4C3640(*(this + 91), "Particle/TrackingFire.ptl", this);  // 字符串 “Particle/TrackingFire.ptl”
  }
  else
  {
    pThis_5B = 0;
  }
  v3 = *this;
  *(this + 2214) = pThis_5B;
  *(this + 2218) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 384))(this, 0);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 结果 = 虚调用 vt+384
  v5 = *this;
  *(this + 2219) = v4;  // this+8876〔uPhase8876〕
  *(this + 2220) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 2);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);  // 结果 = 虚调用 vt+384
  v7 = *this;
  *(this + 2221) = v6;  // this+8884〔uPhase8884〕
  *(this + 2223) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v7 + 384))(this, 4);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);  // 结果 = 虚调用 vt+384
  v9 = *this;
  *(this + 2224) = v8;  // this+8896〔uGlowAmp8896〕
  *(this + 2225) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v9 + 384))(this, 6);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 7);  // 结果 = 虚调用 vt+384
  v11 = *this;
  *(this + 2226) = v10;  // this+8904〔bGlowAlpha8904(推断)〕
  *(this + 2227) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v11 + 384))(this, 8);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 9);  // 结果 = 虚调用 vt+384
  v13 = *this;
  *(this + 2228) = v12;  // this+8912〔uPhase8912〕
  *(this + 2229) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v13 + 384))(this, 10);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 11);  // 结果 = 虚调用 vt+384
  v15 = *this;
  *(this + 2230) = v14;  // this+8920〔uPhase8920〕
  *(this + 2231) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v15 + 384))(this, 12);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 13);  // 结果 = 虚调用 vt+384
  v17 = *this;
  *(this + 2232) = v16;  // this+8928〔uPhase8928〕
  *(this + 2233) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v17 + 384))(this, 14);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  *(this + 2234) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 15);  // 虚调用 vt+384
  *(this + 2188) = 1065353216;  // this+8752 = 1.0f
  *(this + 2207) = 0;
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_flame.ani", 1);  // 字符串 “equipment/character/common/title/titleanimat”
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
int /*thiscall*/ sub_5D6CF0(int this, char ArgList, int nArg3)  // 函数定义: CNSoldier 基类构造 + 守卫字段区清零 + 三语音槽（AMOR_HIT/R_EXPELLER_*）
{
  sub_4A4EA0(ArgList, nArg3);  // 调 IRDMonster 基类构造
  *(uint32_t *)this = &CNSoldier::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(uint32_t *)(this + 8612) = 0;  // this+8612 锁定/相位字节 A
  *(uint32_t *)(this + 8616) = 0;  // this+8616 【推断】钻地相位字节1
  *(uint32_t *)(this + 8620) = 0;  // this+8620 相位双字节门
  *(uint8_t *)(this + 8676) = 0;  // this+8676 【推断】子类 AI 相位槽
  *(uint32_t *)(this + 8672) = &off_6C2B88;  // this+8672 【推断】子类 AI 相位槽
  *(uint32_t *)(this + 8680) = 0;  // this+8680 【推断】子类 AI 门字节
  *(uint8_t *)(this + 8684) = 1;  // this+8684 【推断】子类 AI 门字节
  *(uint8_t *)(this + 8686) = 0;
  *(uint8_t *)(this + 8685) = 0;  // this+8685 【推断】挥击/散射语音锁存
  *(uint32_t *)(this + 8696) = 0;  // this+8696 【推断】子类 AI 向量槽
  *(uint32_t *)(this + 8692) = 0;  // this+8692 【推断】子类 AI 向量槽
  *(uint32_t *)(this + 8688) = 0;  // this+8688 【推断】子类 AI 向量/防护槽
  *(uint8_t *)(this + 8728) = 0;  // this+8728 【推断】段阈值表容量端
  *(uint32_t *)(this + 8724) = &off_6C2B88;  // this+8724 【推断】段阈值表尾针
  *(uint32_t *)(this + 8732) = 0;  // this+8732 【推断】段名一次性门
  *(uint8_t *)(this + 8736) = 1;
  *(uint8_t *)(this + 8738) = 0;
  *(uint8_t *)(this + 8737) = 0;
  *(uint32_t *)(this + 8748) = 0;  // this+8748 【推断】子类 AI 尾部槽
  *(uint32_t *)(this + 8744) = 0;  // this+8744 【推断】主倒计时截止
  *(uint32_t *)(this + 8740) = 0;
  *(uint32_t *)(this + 8780) = 15;
  *(uint32_t *)(this + 8776) = 0;
  *(uint8_t *)(this + 8760) = 0;
  *(uint32_t *)(this + 8808) = 15;
  *(uint32_t *)(this + 8804) = 0;
  *(uint8_t *)(this + 8788) = 0;
  sub_5D51D0((char *)this);  // 守卫字段大复位（8600..8738 全区 + 参数面向量重建）
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, 0);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
  sub_4015C0("AMOR_HIT", 8u);  // 【std::string构造赋值】
  sub_4015C0("R_EXPELLER_ALIVE", 0x10u);  // 【std::string构造赋值】
  sub_4015C0("R_EXPELLER_AMB_LOOP", 0x13u);  // 【std::string构造赋值】
  return this;  // 返回自身指针
}



// 相位字段（this+8676/8728/8760/8788）
// ------------------------------------------------------------
// 0x5D6E40 sub_5D6E40 —— 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
// 写 CNSoldier vftable 后按内嵌序逆序析构：idx2166 接口指针经虚表 +0 自毁、idx2202/2195 两处
// 容量 >=16 的堆串 j__free 并重置 15/0/旗标 0（this+8788/8760），idx2181/2168 换 IObject vftable
// 并清 this+8728/8676，末释放 idx2153 帧/参数表三元组。收尾走 ·sub_4A50F0 基类析构。
// 守卫族与驱逐者族共用（各型析构后缀本函数）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6E40(void *this)  // 函数定义: 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
{
  void (/*thiscall*/ ***pThis_876)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNSoldier::`vftable';  // 写 vftable 指针（对象重定位/复位）
  v2 = *((void (/*thiscall*/ ****)(uint32_t, int))this + 2166);
  if ( v2 != nullptr )  // 若 v2 有效（非空）
    (**v2)(v2, 1);  // 调 v2 的虚函数（vt+0）
  *((uint32_t *)this + 2166) = 0;  // this+8664〔uAI8664(推断)〕
  if ( *((uint32_t *)this + 2202) >= 0x10u )
    j__free(*((void **)this + 2197));  // this+2197 【推断】相位播报字符串槽 SSO 首字节
  *((uint32_t *)this + 2202) = 15;
  *((uint32_t *)this + 2201) = 0;
  *((uint8_t *)this + 8788) = 0;
  if ( *((uint32_t *)this + 2195) >= 0x10u )
    j__free(*((void **)this + 2190));  // 调 堆释放
  *((uint32_t *)this + 2195) = 15;
  *((uint32_t *)this + 2194) = 0;
  *((uint8_t *)this + 8760) = 0;
  *((uint32_t *)this + 2181) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8728) = 0;  // this+8728 【推断】段阈值表容量端
  *((uint32_t *)this + 2168) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8676) = 0;  // this+8676 【推断】子类 AI 相位槽
  if ( *((uint32_t *)this + 2153) != 0 )  // this+8612〔uAI8612(推断)〕
    j__free(*((void **)this + 2153));  // 调 堆释放
  *((uint32_t *)this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
  *((uint32_t *)this + 2154) = 0;  // this+8616〔uAI8616(推断)〕
  *((uint32_t *)this + 2155) = 0;  // this+8620〔uAI8620(推断)〕
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D6F50 sub_5D6F50 —— 守卫族标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7000 / ·sub_5D7CE0 / ·sub_5D7D10 / ·sub_5D7D40 / ·sub_5D7D70 同构
//    （差异：仅转调 ·sub_5D6E40 —— this-1 无 vftable 重写的最简变体；pszArg2&1 时 j__free）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D6F50(void *Block, char pszArg2)  // 守卫族标量删除器（析构 + 可选 free）
{
  sub_5D6E40(Block);  // 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D6F80 sub_5D6F80 —— 守卫王族析构（CNKingGuard vftable + 特效槽释放 + 基析构）
// 写 CNKingGuard vftable 后经 ·sub_42AF90 + ·sub_657740(228) 释放 idx2209 特效槽（ksguard_*.ani
// 落点）并置空，收尾走 ·sub_5D6E40 基析构。守卫王/锤王/四属性守卫/驱逐者各型析构的共同尾段
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6F80(void ***this)  // 函数定义: 守卫王族析构（CNKingGuard vftable + 特效槽释放 + 基析构）
{
  void **fld_e2209; // edi

  *this = &CNKingGuard::`vftable';  // 写 vftable 指针（对象重定位/复位）
  fld_e2209 = *(this + 2209);
  if ( fld_e2209 != nullptr )  // 若 fld_e2209 有效（非空）
  {
    sub_42AF90(fld_e2209);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_e2209, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  *(this + 2209) = nullptr;
  return sub_5D6E40(this);  // 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7000 sub_5D7000 —— 守卫王族标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D6F50 同构（差异：转调 ·sub_5D6F80 —— 带 CNKingGuard vftable 重写的守卫王族版本）
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7000(void ***Block, char pszArg2)  // 守卫王族标量删除器（析构 + 可选 free）
{
  sub_5D6F80(Block);  // 守卫王族析构（CNKingGuard vftable + 特效槽释放 + 基析构）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
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
uint32_t */*thiscall*/ sub_5D7030(uint32_t *this, char ArgList, int nArg3, char pszArg4)  // CNKingGuard 二段构造（六处置 1 武装 + 破碎初始化 + 外观装载分支）
{
  sub_5D6CF0(ArgList, nArg3);  // CNSoldier 基类构造 + 守卫字段区清零 + 三语音槽（AMOR_HIT/R_EXP
  *this = &CNKingGuard::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(this + 2203) = 1;  // this+8812〔uCharge8812(推断)〕
  *(this + 2204) = 1;  // this+8816〔uCharge8816(推断)〕
  *(this + 2205) = 1;  // this+8820〔uCharge8820(推断)〕
  *(this + 2206) = 1;  // this+8824〔uCharge8824〕
  *(this + 2207) = 1;
  *(this + 2208) = 1;  // this+8832〔uCharge8832〕
  *(this + 2209) = 0;
  sub_5D18E0(this);  // 破碎初始化（粒子 + 双轴尺寸 + 变速因子）
  if ( pszArg4 == 1 )
  {
    sub_4D50A0(*(uint32_t *)(*(this + 1554) + 16));  // 调 触发初次刷新
  }
  else
  {
    sub_4D50A0(*(this + 1540));  // 调 触发初次刷新
    sub_5CF120(this);  // 法杖态关闭
  }
  return this;  // 返回自身指针
}



// 驱逐者相位字段 A（this+8840..8881）
// ------------------------------------------------------------
// 0x5D7100 sub_5D7100 —— CNHammerKing 构造（四组内嵌子对象清零 + 基构造 + 参数装载）
// 转调 ·sub_5D7030 基构造后写 CNHammerKing vftable；this+8840..8964 按 28 字节步长铺五组内嵌
// 结构（每组：off_6C2B88 vftable + 12 字节零 + 1/0/0 三旗标，即五条串/列表槽），this+8840 组
// 即守卫王族相位字段 A 面；末调 ·sub_5CF690 参数复位与 ·sub_5D25D0 自动守卫参数装载——注意此处
// v4 未初始化【原样保留】。锤王（R_HAMMER_KING）专属构造
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7100(int this, char ArgList, int nArg3)  // 函数定义: CNHammerKing 构造，结果存 result
{
  float *v4; // ecx

  sub_5D7030((uint32_t *)this, ArgList, nArg3, 0);  // CNKingGuard 二段构造（六处置 1 武装 + 破碎初始化 + 外观装载分支）
  *(uint32_t *)this = &CNHammerKing::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(uint8_t *)(this + 8844) = 0;  // this+8844 【推断】相位时钟槽
  *(uint32_t *)(this + 8840) = &off_6C2B88;  // this+8840 相位/档位槽
  *(uint32_t *)(this + 8848) = 0;  // this+8848 【推断】相位标志字节
  *(uint8_t *)(this + 8852) = 1;
  *(uint8_t *)(this + 8854) = 0;  // this+8854 【推断】相位标志
  *(uint8_t *)(this + 8853) = 0;  // this+8853 【推断】相位标志
  *(uint32_t *)(this + 8864) = 0;
  *(uint32_t *)(this + 8860) = 0;
  *(uint32_t *)(this + 8856) = 0;
  *(uint8_t *)(this + 8872) = 0;  // this+8872 【推断】相位时长槽
  *(uint32_t *)(this + 8868) = &off_6C2B88;  // this+8868 【推断】冰守卫交互门
  *(uint32_t *)(this + 8876) = 0;  // this+8876 【推断】相位区槽
  *(uint8_t *)(this + 8880) = 1;  // this+8880 【推断】相位区槽
  *(uint8_t *)(this + 8882) = 0;  // this+8882 【推断】相位/连段门
  *(uint8_t *)(this + 8881) = 0;  // this+8881 【推断】相位/连段门
  *(uint32_t *)(this + 8892) = 0;  // this+8892 呼吸发光中心值
  *(uint32_t *)(this + 8888) = 0;  // this+8888 【推断】相位区槽
  *(uint32_t *)(this + 8884) = 0;  // this+8884 【推断】相位区槽
  *(uint8_t *)(this + 8900) = 0;  // this+8900 抖动振幅
  *(uint32_t *)(this + 8896) = &off_6C2B88;  // this+8896 呼吸发光振幅
  *(uint32_t *)(this + 8904) = 0;  // this+8904 渲染透明度源
  *(uint8_t *)(this + 8908) = 1;  // this+8908 【推断】相位区槽
  *(uint8_t *)(this + 8910) = 0;  // this+8910 【推断】相位字节
  *(uint8_t *)(this + 8909) = 0;  // this+8909 【推断】相位字节
  *(uint32_t *)(this + 8920) = 0;  // this+8920 【推断】相位区槽
  *(uint32_t *)(this + 8916) = 0;  // this+8916 【推断】相位区槽
  *(uint32_t *)(this + 8912) = 0;  // this+8912 【推断】相位区槽
  *(uint8_t *)(this + 8944) = 0;
  *(uint32_t *)(this + 8940) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8948) = 0;
  *(uint8_t *)(this + 8952) = 1;
  *(uint8_t *)(this + 8954) = 0;  // this+8954 【推断】相位字节
  *(uint8_t *)(this + 8953) = 0;  // this+8953 【推断】相位字节
  *(uint32_t *)(this + 8964) = 0;  // this+8964 伤害上限值
  *(uint32_t *)(this + 8960) = 0;  // this+8960 伤害上限开关字节
  *(uint32_t *)(this + 8956) = 0;
  sub_5CF690(this);  // 相位字段复位 A（8853..9008）
  sub_5D25D0(v4);  // 自动守卫参数装载（vt+384 出场参数面 0..10 号）
  return this;  // 返回自身指针
}



// 驱逐者相位字段 B（this+8844/8872/8900/8944）
// ------------------------------------------------------------
// 0x5D7240 sub_5D7240 —— CNHammerKing 析构（四组相位子对象换 IObject vftable + 旗标清 0）
// 写 CNHammerKing vftable 后按 idx2235/2224/2217/2210 四组（对应 this+8944/8900/8872/8844）
// 换 nengine::IObject vftable 并清各自 +24 字节旗标，收尾 ·sub_5D6F80 守卫王族析构。
// 与 ·0x5D7100 构造的相位字段 A 面严格对偶
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7240(void ***this)  // 函数定义: CNHammerKing 析构（四组相位子对象换 IObject vftable + 旗标清 0）
{
  *this = &CNHammerKing::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(this + 2235) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8944) = 0;
  *(this + 2224) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8900) = 0;  // this+8900 抖动振幅
  *(this + 2217) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8872) = 0;  // this+8872 【推断】相位时长槽
  *(this + 2210) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8844) = 0;  // this+8844 【推断】相位时钟槽
  return sub_5D6F80(this);  // 守卫王族析构（CNKingGuard vftable + 特效槽释放 + 基析构）
}



// 驱逐者相位字段 C（this+8852..8876）
// ------------------------------------------------------------
// 0x5D7290 sub_5D7290 —— CNGuardLight 构造（光守卫）
// 转调 ·sub_5D7030（pszArg4=1 军团形态）后写 CNGuardLight vftable；this+8852..8876 铺一组内嵌
// 结构（off_6C2B88 vftable + 零 + 1/0/0 旗标），末调 ·sub_5CF740 参数复位与 ·0x5D6590 光守卫
// 参数装载（ksguard_light.ani + vt+384 十一连读）。守卫格挡族——光属性
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7290(int this, char ArgList, int nArg3)  // 函数定义: CNGuardLight 构造并把指针直接返回
{
  float *v4; // ecx

  sub_5D7030((uint32_t *)this, ArgList, nArg3, 1);  // CNKingGuard 二段构造（六处置 1 武装 + 破碎初始化 + 外观装载分支）
  *(uint32_t *)this = &CNGuardLight::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(uint8_t *)(this + 8856) = 0;
  *(uint32_t *)(this + 8852) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8860) = 0;
  *(uint8_t *)(this + 8864) = 1;
  *(uint8_t *)(this + 8866) = 0;  // this+8866 【推断】相位标志字节
  *(uint8_t *)(this + 8865) = 0;  // this+8865 【推断】相位标志字节
  *(uint32_t *)(this + 8876) = 0;  // this+8876 【推断】相位区槽
  *(uint32_t *)(this + 8872) = 0;  // this+8872 【推断】相位时长槽
  *(uint32_t *)(this + 8868) = 0;  // this+8868 【推断】冰守卫交互门
  sub_5CF740(this);  // 相位字段复位 B（8840..8932）
  sub_5D6590(v4);  // 光守卫参数装载（ksguard_light.ani + vt+384 十一连读）
  return this;  // 返回自身指针
}



// AI 字段访问（this+8856）
// ------------------------------------------------------------
// 0x5D7330 sub_5D7330 —— CNGuardLight 析构（全局光守卫计数减一 + 特效槽清）
// 写 CNGuardLight vftable 后把全局 dword_8F8528 +623 处计数置 0（【推断】光守卫在场/链数清位），
// idx2213 换 IObject vftable 并清 this+8856 旗标，收尾 ·sub_5D6F80。与 ·0x5D7290 构造对偶
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7330(void ***this)  // 函数定义: CNGuardLight 析构（全局光守卫计数减一 + 特效槽清）
{
  *this = &CNGuardLight::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint32_t *)dword_8F8528 + 623) = 0;  // 全局 dword_8F8528 = 消息/弹窗管理器
  *(this + 2213) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8856) = 0;  // this+8856〔旗标〕
  return sub_5D6F80(this);  // 守卫王族析构（CNKingGuard vftable + 特效槽释放 + 基析构）
}



// 驱逐者相位字段 D（this+8844..8889）
// ------------------------------------------------------------
// 0x5D7360 sub_5D7360 —— CNGuardWind 构造（风守卫）
// 转调 ·sub_5D7030（pszArg4=1 军团形态）后写 CNGuardWind vftable；this+8844..9008 铺七组内嵌结构
// （含 this+8908 = ·sub_4A2D10(this+8904) 的链式切面），相位数与参数面在守卫族中最宽 —— 疑含
// 多段风刃/场地表现槽；末调 ·sub_5CF7F0 参数复位与 ·0x5D6700 风守卫装载（Haste.ani + ksguard_wind）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7360(int this, char ArgList, int nArg3)  // 函数定义: CNGuardWind 构造，结果存 result
{
  float *v4; // ecx

  sub_5D7030((uint32_t *)this, ArgList, nArg3, 1);  // CNKingGuard 二段构造（六处置 1 武装 + 破碎初始化 + 外观装载分支）
  *(uint32_t *)this = &CNGuardWind::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(uint8_t *)(this + 8848) = 0;  // this+8848 【推断】相位标志字节
  *(uint32_t *)(this + 8844) = &off_6C2B88;  // this+8844 【推断】相位时钟槽
  *(uint32_t *)(this + 8852) = 0;
  *(uint8_t *)(this + 8856) = 1;
  *(uint8_t *)(this + 8858) = 0;  // this+8858 【推断】相位标志
  *(uint8_t *)(this + 8857) = 0;  // this+8857 【推断】相位标志
  *(uint32_t *)(this + 8868) = 0;  // this+8868 【推断】冰守卫交互门
  *(uint32_t *)(this + 8864) = 0;
  *(uint32_t *)(this + 8860) = 0;
  *(uint8_t *)(this + 8880) = 0;  // this+8880 【推断】相位区槽
  *(uint32_t *)(this + 8876) = &off_6C2B88;  // this+8876 【推断】相位区槽
  *(uint32_t *)(this + 8884) = 0;  // this+8884 【推断】相位区槽
  *(uint8_t *)(this + 8888) = 1;  // this+8888 【推断】相位区槽
  *(uint8_t *)(this + 8890) = 0;  // this+8890 【推断】相位字节
  *(uint8_t *)(this + 8889) = 0;  // this+8889 【推断】相位字节
  *(uint32_t *)(this + 8900) = 0;  // this+8900 抖动振幅
  *(uint32_t *)(this + 8896) = 0;  // this+8896 呼吸发光振幅
  *(uint32_t *)(this + 8892) = 0;  // this+8892 呼吸发光中心值
  *(uint32_t *)(this + 8908) = sub_4A2D10(this + 8904);  // this+8908 【推断】相位区槽
  *(uint32_t *)(this + 8912) = 0;  // this+8912 【推断】相位区槽
  *(uint8_t *)(this + 8920) = 0;  // this+8920 【推断】相位区槽
  *(uint32_t *)(this + 8916) = &off_6C2B88;  // this+8916 【推断】相位区槽
  *(uint32_t *)(this + 8924) = 0;  // this+8924 【推断】相位门
  *(uint8_t *)(this + 8928) = 1;  // this+8928 【推断】相位区槽
  *(uint8_t *)(this + 8930) = 0;  // this+8930 【推断】相位字节
  *(uint8_t *)(this + 8929) = 0;  // this+8929 【推断】相位字节
  *(uint32_t *)(this + 8940) = 0;
  *(uint32_t *)(this + 8936) = 0;  // this+8936 【推断】相位字节
  *(uint32_t *)(this + 8932) = 0;  // this+8932 【推断】相位槽/三连段段号
  *(uint8_t *)(this + 8948) = 0;
  *(uint32_t *)(this + 8944) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8952) = 0;
  *(uint8_t *)(this + 8956) = 1;
  *(uint8_t *)(this + 8958) = 0;  // this+8958 【推断】相位字节
  *(uint8_t *)(this + 8957) = 0;  // this+8957 【推断】相位字节
  *(uint32_t *)(this + 8968) = 0;  // this+8968 上限上下文
  *(uint32_t *)(this + 8964) = 0;  // this+8964 伤害上限值
  *(uint32_t *)(this + 8960) = 0;  // this+8960 伤害上限开关字节
  *(uint8_t *)(this + 8988) = 0;  // this+8988 【推断】内嵌子对象旗标
  *(uint32_t *)(this + 8984) = &off_6C2B88;  // this+8984 【推断】内嵌子对象 vftable 槽
  *(uint32_t *)(this + 8992) = 0;  // this+8992 【推断】段时长换算槽
  *(uint8_t *)(this + 8996) = 1;  // this+8996 【推断】相位字节
  *(uint8_t *)(this + 8998) = 0;
  *(uint8_t *)(this + 8997) = 0;
  *(uint32_t *)(this + 9008) = 0;  // this+9008 【推断】段时长重排源
  *(uint32_t *)(this + 9004) = 0;  // this+9004 【推断】相位槽
  *(uint32_t *)(this + 9000) = 0;  // this+9000 【推断】相位槽
  sub_5CF7F0(this);  // 相位字段复位 C（8840..9048）
  sub_5D6700(v4);  // 风守卫参数装载（Haste.ani + ksguard_wind.ani 双载）
  return this;  // 返回自身指针
}



// 驱逐者相位字段 E（this+8844..8988）
// ------------------------------------------------------------
// 0x5D7500 sub_5D7500 —— CNGuardWind 析构（风守卫，含 list 释放 + 基析构）
// 写 CNGuardWind vftable 后经 ·sub_42AF90 + ·sub_657740(228) 释放 this+8980 特效槽；随后
// this+8984/8944/8916/8876/8844 五组换 IObject vftable 并清旗标，this+8904 槽经 ·sub_6569D0
// 释放其节点后 j__free(this+8908) 并置 0，收尾 ·sub_5D6F80。守卫族析构中清理面最宽的一支
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7500(int this)  // 函数定义: CNGuardWind 析构（风守卫，含 list 释放 + 基析构）
{
  void **fld_2314; // edi

  *(uint32_t *)this = &CNGuardWind::`vftable';  // 写 vftable 指针（对象重定位/复位）
  v2 = *(void ***)(this + 8980);  // this+8980 特效/资源槽
  if ( v2 != nullptr )  // 若 v2 有效（非空）
  {
    sub_42AF90(v2);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(v2, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  *(uint32_t *)(this + 8980) = 0;  // this+8980 特效/资源槽
  *(uint32_t *)(this + 8984) = &nengine::IObject::`vftable';  // this+8984 【推断】内嵌子对象 vftable 槽
  *(uint8_t *)(this + 8988) = 0;  // this+8988 【推断】内嵌子对象旗标
  *(uint32_t *)(this + 8944) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(uint8_t *)(this + 8948) = 0;
  *(uint32_t *)(this + 8916) = &nengine::IObject::`vftable';  // this+8916 【推断】相位区槽
  *(uint8_t *)(this + 8920) = 0;  // this+8920 【推断】相位区槽
  sub_6569D0(this + 8904);  // 调 (this+4)
  j__free(*(void **)(this + 8908));  // this+8908 【推断】相位区槽
  *(uint32_t *)(this + 8908) = 0;  // this+8908 【推断】相位区槽
  *(uint32_t *)(this + 8876) = &nengine::IObject::`vftable';  // this+8876 【推断】相位区槽
  *(uint8_t *)(this + 8880) = 0;  // this+8880 【推断】相位区槽
  *(uint32_t *)(this + 8844) = &nengine::IObject::`vftable';  // this+8844 【推断】相位时钟槽
  *(uint8_t *)(this + 8848) = 0;  // this+8848 【推断】相位标志字节
  return sub_5D6F80((void ***)this);  // 守卫王族析构（CNKingGuard vftable + 特效槽释放 + 基析构）
}



// 驱逐者相位字段 F（this+8840..8884）
// ------------------------------------------------------------
// 0x5D75E0 sub_5D75E0 —— CNGuardIce 构造（冰守卫）
// 转调 ·sub_5D7030（pszArg4=1 军团形态）后写 CNGuardIce vftable；this+8840..8888 铺一组内嵌结构
// （off_6C2B88 vftable + 零 + 1/0/0 旗标），末调 ·0x5D68A0 冰守卫装载（ksguard_ice.ani + vt+384
// 五连读）。守卫格挡族——冰属性
// ------------------------------------------------------------
int /*thiscall*/ sub_5D75E0(int this, char ArgList, int nArg3)  // 函数定义: CNGuardIce 构造，结果存 result
{
  sub_5D7030((uint32_t *)this, ArgList, nArg3, 1);  // CNKingGuard 二段构造（六处置 1 武装 + 破碎初始化 + 外观装载分支）
  *(uint32_t *)this = &CNGuardIce::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(uint8_t *)(this + 8844) = 0;  // this+8844 【推断】相位时钟槽
  *(uint32_t *)(this + 8840) = &off_6C2B88;  // this+8840 相位/档位槽
  *(uint32_t *)(this + 8848) = 0;  // this+8848 【推断】相位标志字节
  *(uint8_t *)(this + 8852) = 1;
  *(uint8_t *)(this + 8854) = 0;  // this+8854 【推断】相位标志
  *(uint8_t *)(this + 8853) = 0;  // this+8853 【推断】相位标志
  *(uint32_t *)(this + 8864) = 0;
  *(uint32_t *)(this + 8860) = 0;
  *(uint32_t *)(this + 8856) = 0;
  *(uint8_t *)(this + 8853) = 0;  // this+8853 【推断】相位标志
  *(uint8_t *)(this + 8854) = 0;  // this+8854 【推断】相位标志
  *(uint8_t *)(this + 8868) = 1;  // this+8868 【推断】冰守卫交互门
  *(uint32_t *)(this + 8872) = 0;  // this+8872 【推断】相位时长槽
  *(uint32_t *)(this + 8876) = 0;  // this+8876 【推断】相位区槽
  *(uint32_t *)(this + 8880) = 0;  // this+8880 【推断】相位区槽
  *(uint32_t *)(this + 8884) = 0;  // this+8884 【推断】相位区槽
  *(uint32_t *)(this + 8888) = 0;  // this+8888 【推断】相位区槽
  sub_5D68A0((uint32_t *)this);  // 冰守卫参数装载（ksguard_ice.ani + vt+384 五连读）
  return this;  // 返回自身指针
}



// AI 字段访问（this+8844）
// ------------------------------------------------------------
// 0x5D76B0 sub_5D76B0 —— CNGuardIce 析构
// 写 CNGuardIce vftable 后 idx2210 换 IObject vftable、清 this+8844 旗标，收尾 ·sub_5D6F80。
// 与 ·0x5D75E0 构造对偶（冰守卫清理面最简）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D76B0(void ***this)  // 函数定义: CNGuardIce 析构
{
  *this = &CNGuardIce::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(this + 2210) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8844) = 0;  // this+8844 【推断】相位时钟槽
  return sub_5D6F80(this);  // 守卫王族析构（CNKingGuard vftable + 特效槽释放 + 基析构）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D76D0 sub_5D76D0 —— CNGuardBlock 构造（重装/格挡守卫）
// 转调 ·sub_5D7030 基构造后写 CNGuardBlock vftable，经 ·sub_5CFAE0 参数复位与 ·0x5D6960 装载 ——
// 即 R_DEFEN_GUARD_DIE/DMG/ALIVE/AMB 语音四件套 + ksguard_protection.ani 防御守卫特效。
// 【推断】CNGuardBlock = 守卫格挡/盾卫分支，语音组取自防御守卫
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D76D0(uint32_t *this, char ArgList, int nArg3)  // CNGuardBlock 构造（重装/格挡守卫）
{
  uint32_t *v4; // ecx

  sub_5D7030(this, ArgList, nArg3, 1);  // CNKingGuard 二段构造（六处置 1 武装 + 破碎初始化 + 外观装载分支）
  *this = &CNGuardBlock::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_5CFAE0(this);  // 节拍区复位（2210 置 2 + 2211..2226 清零）
  sub_5D6960(v4);  // 防御守卫参数装载（ksguard_protection.ani + R_DEFEN_GUAR
  return this;  // 返回自身指针
}



// AI 字段访问（this+8841）
// ------------------------------------------------------------
// 0x5D7740 sub_5D7740 —— CNGuardFire 构造（火守卫）
// 转调 ·sub_5D7030 基构造后写 CNGuardFire vftable；this+8841 处经 ·sub_41A630 构造 clong 并从
// 该处写回 clong::vftable（this+8841 未按指针对齐 —— 疑为字节内嵌计数/引用对象【推断】），
// 末经 ·sub_5CFCC0 参数复位与 ·0x5D6AF0 火守卫装载（TrackingFire.ptl + ksguard_flame.ani）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D7740(uint32_t *this, char ArgList, int nArg3)  // CNGuardFire 构造（火守卫）
{
  int v4; // edx

  sub_5D7030(this, ArgList, nArg3, 1);  // CNKingGuard 二段构造（六处置 1 武装 + 破碎初始化 + 外观装载分支）
  *this = &CNGuardFire::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_41A630((unsigned int)this + 8841);  // 调 调 sub_41A630
  *(uint32_t *)((char *)this + 8841) = &clong::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_5CFCC0((int)this, v4);  // 相位参数块重置（8841 校验字 + 8860/8864=1.0f）
  sub_5D6AF0(this);  // 火守卫参数装载（Particle/TrackingFire.ptl 追踪火 + ksguar
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D77C0 sub_5D77C0 —— CNGuardFire 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D6F50 同构（差异：转调 ·sub_5D77F0 —— 火守卫析构；原样保留的零参调用形式）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D77C0(void *Block, char pszArg2)  // CNGuardFire 标量删除器（析构 + 可选 free）
{
  sub_5D77F0();  // CNGuardFire 析构（clong 子对象析构 + 基析构）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问（this+8841/8856）
// ------------------------------------------------------------
// 0x5D77F0 sub_5D77F0 —— CNGuardFire 析构（clong 子对象析构 + 基析构）
// 写 CNGuardFire vftable 后 this+8856 接口指针经虚表 +0 自毁并置 0，经 ·sub_41A580 析构 this+8841
// 处 clong 子对象，收尾 ·sub_5D6F80。与 ·0x5D7740 构造对偶
// ------------------------------------------------------------
int /*thiscall*/ sub_5D77F0(int this)  // 函数定义: CNGuardFire 析构（clong 子对象析构 + 基析构）
{
  void (/*thiscall*/ ***pThis_2298)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNGuardFire::`vftable';  // 写 vftable 指针（对象重定位/复位）
  pThis_2298 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8856);
  if ( pThis_2298 != nullptr )  // 若 pThis_2298 有效（非空）
    (**pThis_2298)(pThis_2298, 1);  // 调 pThis_2298 的虚函数（vt+0）
  *(uint32_t *)(this + 8856) = 0;
  sub_41A580(this + 8841);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  return sub_5D6F80((void ***)this);  // 守卫王族析构（CNKingGuard vftable + 特效槽释放 + 基析构）
}



// AI 字段访问（this+8601）
// ------------------------------------------------------------
// 0x5D7870 sub_5D7870 —— CNAxeExpeller 构造（斧驱逐者）
// 转调 ·sub_5D6CF0 基构造后写 CNAxeExpeller vftable；清 this+8601 与 idx2203/2204 两槽，
// 经 ·sub_5D4E30 装载 AxeExpellerBroken 破碎外观，末取 this+1554 外层 +16 槽外观资源。
// 斧驱逐者（AxeExpeller）专属构造——破碎件表现族
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D7870(uint8_t *this, char ArgList, int nArg3)  // CNAxeExpeller 构造（斧驱逐者）
{
  sub_5D6CF0(ArgList, nArg3);  // CNSoldier 基类构造 + 守卫字段区清零 + 三语音槽（AMOR_HIT/R_EXP
  *(uint32_t *)this = &CNAxeExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(this + 8601) = 0;  // this+8601 子类 AI 状态字节 2
  *((uint32_t *)this + 2204) = 0;  // this+8816〔uCharge8816(推断)〕
  *((uint32_t *)this + 2203) = 0;  // this+8812〔uCharge8812(推断)〕
  sub_5D4E30(this);  // 斧驱逐者战损（AxeExpellerBrokenParts.ptl）
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));  // 调 触发初次刷新
  return this;  // 返回自身指针
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D78F0 sub_5D78F0 —— CNAxeExpeller 析构（idx2204/2203 双槽逆序释放 + 基析构）
// 写 CNAxeExpeller vftable 后按 idx2204 → idx2203 逆序经虚表 +0 自毁两接口槽并置 0
// （对应 ·0x5D7870 的清零点），收尾 ·sub_5D6E40。与斧驱逐者构造严格对偶
// ------------------------------------------------------------
int /*thiscall*/ sub_5D78F0(uint32_t *this)  // 函数定义: CNAxeExpeller 析构（idx2204/2203 双槽逆序释放 + 基析构）
{
  void (/*thiscall*/ ***fld_e2204)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e2203)(uint32_t, int); // ecx

  *this = &CNAxeExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  fld_e2204 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2204);  // this+8816〔uCharge8816(推断)〕
  if ( fld_e2204 != nullptr )  // 若 fld_e2204 有效（非空）
    (**fld_e2204)(fld_e2204, 1);  // 调 fld_e2204 的虚函数（vt+0）
  fld_e2203 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2203);  // this+8812〔uCharge8812(推断)〕
  *(this + 2204) = 0;  // this+8816〔uCharge8816(推断)〕
  if ( fld_e2203 != nullptr )  // 若 fld_e2203 有效（非空）
    (**fld_e2203)(fld_e2203, 1);  // 调 fld_e2203 的虚函数（vt+0）
  *(this + 2203) = 0;  // this+8812〔uCharge8812(推断)〕
  return sub_5D6E40(this);  // 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
}



// 时钟门 AI（sub_699000; this+8600/8812/8829/8837）
// ------------------------------------------------------------
// 0x5D7970 sub_5D7970 —— CNHeavenExpeller 构造（天界驱逐者）
// 转调 ·sub_5D6CF0 基构造后写 CNHeavenExpeller vftable；清 this+8600/8812/8829/8837 相位字节，
// idx2204 = ·sub_699000(this+36) 取时钟基线、idx2205/2206 = 30/0 冷却初值；经 ·sub_5D0DE0 装载
// HeavenExpellerBroken 破碎外观与 this+1554 外层外观，释放 idx2153 三元组后经 ·sub_430C80
// 向该表按序压入 1000/2000 两项（int 容器 push_back 的内联展开）。天界驱逐者专属构造
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7970(void *this, char ArgList, int nArg3)  // CNHeavenExpeller 构造（天界驱逐者）
{
  int pThis_869; // edx
  unsigned int pThis_86A; // ecx
  uint32_t *pThis_86A2; // eax

  sub_5D6CF0(ArgList, nArg3);  // CNSoldier 基类构造 + 守卫字段区清零 + 三语音槽（AMOR_HIT/R_EXP
  *(uint32_t *)this = &CNHeavenExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8600) = 0;  // 写 this+8600 = 0（子类AI区）
  *((uint8_t *)this + 8829) = 0;  // this+8829 蓄雷复位字节
  *((uint32_t *)this + 2208) = 0;  // this+8832〔uCharge8832〕
  *((uint8_t *)this + 8812) = 0;  // this+8812 蓄力门
  *((uint32_t *)this + 2204) = sub_699000((int)this + 36);  // clock_now(clk)
  *((uint32_t *)this + 2206) = 0;  // this+8824〔uCharge8824〕
  *((uint32_t *)this + 2205) = 30;  // this+8820〔uCharge8820(推断)〕
  *((uint8_t *)this + 8837) = 0;  // this+8837 编队召唤单次门
  sub_5D0DE0(this);  // 天界驱逐者破碎：装载 HeavenExpellerBrokenParts.ptl
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));  // 调 触发初次刷新
  if ( *((uint32_t *)this + 2153) != 0 )  // this+8612〔uAI8612(推断)〕
    j__free(*((void **)this + 2153));  // 调 堆释放
  *((uint32_t *)this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
  *((uint32_t *)this + 2154) = 0;  // this+8616〔uAI8616(推断)〕
  *((uint32_t *)this + 2155) = 0;  // this+8620〔uAI8620(推断)〕
  nArg3 = 1000;
  sub_430C80(*((void **)this + 2154), 1, (int)&nArg3);  // uint32 vector 区间插入（同值填充）
  pThis_869 = *((uint32_t *)this + 2153);  // this+8612〔uAI8612(推断)〕
  nArg3 = 2000;
  if ( pThis_869 != 0 )
    pThis_86A = (*((uint32_t *)this + 2154) - pThis_869) >> 2;  // this+8616〔uAI8616(推断)〕
  else
    pThis_86A = 0;
  if ( pThis_869 != 0 && pThis_86A < (*((uint32_t *)this + 2155) - pThis_869) >> 2 )  // this+8620〔uAI8620(推断)〕
  {
    pThis_86A2 = *((uint32_t **)this + 2154);
    *pThis_86A2 = 2000;
    *((uint32_t *)this + 2154) = pThis_86A2 + 1;  // this+8616〔uAI8616(推断)〕
  }
  else
  {
    sub_430C80(*((void **)this + 2154), 1, (int)&nArg3);  // uint32 vector 区间插入（同值填充）
  }
  return this;  // 返回自身指针
}



// 阿莫尔命中 4：AMOR_HIT 播报（this+8601/8812/8832 相位）
// ------------------------------------------------------------
// 0x5D7AE0 sub_5D7AE0 —— CNLegionExpeller 构造（军团驱逐者）
// 转调 ·sub_5D6CF0 基构造后写 CNLegionExpeller vftable；清 this+8601/8812/8600 与 idx2207/8832；
// ·sub_42A560 取参数存 idx2205/2206（同值双槽，疑为 帧/时长 或 距离/半径 对偶【推断】）；
// 再经 ·sub_4015C0 写 AMOR_HIT 命中 TAG，末 ·sub_5D1160 装载 AxeExpellerBroken 破碎外观与
// this+1554 外层外观，pszArg4==1 时另走 ·sub_5CF120。军团驱逐者专属（vt+40 类型校验 704 = 本型）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D7AE0(uint8_t *this, char ArgList, int nArg3, char pszArg4)  // CNLegionExpeller 构造（军团驱逐者）
{
  int v5; // eax

  sub_5D6CF0(ArgList, nArg3);  // CNSoldier 基类构造 + 守卫字段区清零 + 三语音槽（AMOR_HIT/R_EXP
  *(uint32_t *)this = &CNLegionExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(this + 8601) = 0;  // this+8601 子类 AI 状态字节 2
  *(this + 8812) = 0;  // this+8812 蓄力门
  *(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
  v5 = sub_42A560(this);
  *((uint32_t *)this + 2206) = v5;  // this+8824〔uCharge8824〕
  *((uint32_t *)this + 2205) = v5;  // this+8820〔uCharge8820(推断)〕
  *((uint32_t *)this + 2207) = 0;
  *(this + 8832) = 0;  // this+8832 蓄雷参数槽
  sub_4015C0("AMOR_HIT", 8u);  // 【std::string构造赋值】
  sub_5D1160(this);  // 斧驱逐者破碎：装载 AxeExpellerBrokenParts.ptl
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));  // 调 触发初次刷新
  if ( pszArg4 == 1 )
    sub_5CF120(this);  // 法杖态关闭
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7BA0 sub_5D7BA0 —— CNLegionExpeller 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7E00 同构（差异：转调 ·sub_5D7BD0 —— 军团驱逐者析构）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7BA0(void *Block, char pszArg2)  // CNLegionExpeller 标量删除器（析构 + 可选 free）
{
  sub_5D7BD0();  // CNLegionExpeller 析构（idx2207 槽释放 + 基析构）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7BD0 sub_5D7BD0 —— CNLegionExpeller 析构（idx2207 槽释放 + 基析构）
// 写 CNLegionExpeller vftable 后 idx2207 接口指针经虚表 +0 自毁并置 0（·0x5D7AE0 置 0 的落点），
// 收尾 ·sub_5D6E40 基析构
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7BD0(uint32_t *this)  // 函数定义: CNLegionExpeller 析构（idx2207 槽释放 + 基析构）
{
  void (/*thiscall*/ ***fld_e2207)(uint32_t, int); // ecx

  *this = &CNLegionExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  fld_e2207 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2207);
  if ( fld_e2207 != nullptr )  // 若 fld_e2207 有效（非空）
    (**fld_e2207)(fld_e2207, 1);  // 调 fld_e2207 的虚函数（vt+0）
  *(this + 2207) = 0;
  return sub_5D6E40(this);  // 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
}



// AI 相位字段（this+8600/8812/8820）
// ------------------------------------------------------------
// 0x5D7C40 sub_5D7C40 —— CNSandorExpeller 构造（沙多/桑多驱逐者）
// 转调 ·sub_5D6CF0 基构造后写 CNSandorExpeller vftable；清 this+8812/8820/8600 与 idx2204，
// 经 ·sub_5D2320 装载 AxeExpellerBroken 2 破碎外观并应用目标帧；pszArg4==1 时走 this+1540 与
// ·sub_5CF120 军团分支，末 ·sub_5D3640 编队档位清位（vt+1172 档位 → 子对象 +3x 字段）。
// 沙多驱逐者专属构造
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D7C40(uint8_t *this, char ArgList, int nArg3, char pszArg4)  // CNSandorExpeller 构造（沙多/桑多驱逐者）
{
  sub_5D6CF0(ArgList, nArg3);  // CNSoldier 基类构造 + 守卫字段区清零 + 三语音槽（AMOR_HIT/R_EXP
  *(uint32_t *)this = &CNSandorExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(this + 8812) = 0;  // this+8812 蓄力门
  *((uint32_t *)this + 2204) = 0;  // this+8816〔uCharge8816(推断)〕
  *(this + 8820) = 0;  // this+8820 蓄雷窗口长度
  *(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
  sub_5D2320(this);  // 斧驱逐者破碎 2：装载 + 应用目标帧
  if ( pszArg4 == 1 )
  {
    sub_4D50A0(*((uint32_t *)this + 1540));  // 调 触发初次刷新
    sub_5CF120(this);  // 法杖态关闭
  }
  sub_5D3640(this);  // 编队档位清位（vt+1172 档位 → 子对象 +32..+160 五槽）
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7CE0 sub_5D7CE0 —— CNHammerKing 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7D10 同构（差异：转调 ·sub_5D7240 —— 锤王析构）
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7CE0(void ***Block, char pszArg2)  // CNHammerKing 标量删除器（析构 + 可选 free）
{
  sub_5D7240(Block);  // CNHammerKing 析构（四组相位子对象换 IObject vftable + 旗标清
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7D10 sub_5D7D10 —— CNGuardLight 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7D70 同构（差异：转调 ·sub_5D7330 —— 光守卫析构）
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7D10(void ***Block, char pszArg2)  // CNGuardLight 标量删除器（析构 + 可选 free）
{
  sub_5D7330(Block);  // CNGuardLight 析构（全局光守卫计数减一 + 特效槽清）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7D40 sub_5D7D40 —— CNGuardWind 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7D70 同构（差异：转调 ·sub_5D7500 —— 风守卫析构）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7D40(void *Block, char pszArg2)  // CNGuardWind 标量删除器（析构 + 可选 free）
{
  sub_5D7500((int)Block);  // CNGuardWind 析构（风守卫，含 list 释放 + 基析构）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7D70 sub_5D7D70 —— CNGuardIce 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7DD0 同构（差异：转调 ·sub_5D76B0 —— 冰守卫析构）
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7D70(void ***Block, char pszArg2)  // CNGuardIce 标量删除器（析构 + 可选 free）
{
  sub_5D76B0(Block);  // CNGuardIce 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7DA0 sub_5D7DA0 —— 守卫格挡族标量删除器（析构 + 可选 free）
// 转调 ·sub_5D7730 后按 pszArg2&1 释放。与 ·sub_5D7D70 同构（差异：被调析构为 ·sub_5D7730）。
// 【推断】·sub_5D7730 紧邻 ·0x5D76D0 CNGuardBlock 构造之后，当为该型析构 —— 本条属重装/格挡守卫
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7DA0(void *Block, char pszArg2)  // 守卫格挡族标量删除器（析构 + 可选 free）
{
  sub_5D7730();  // 调 后按 pszArg2&1 释放
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7DD0 sub_5D7DD0 —— CNAxeExpeller 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7E30 同构（差异：转调 ·sub_5D78F0 —— 斧驱逐者析构）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D7DD0(uint32_t *Block, char pszArg2)  // CNAxeExpeller 标量删除器（析构 + 可选 free）
{
  sub_5D78F0(Block);  // CNAxeExpeller 析构（idx2204/2203 双槽逆序释放 + 基析构）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7E00 sub_5D7E00 —— 军团驱逐者族标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7BA0 同构（差异：转调 ·sub_5D7AD0 —— 本条为该型析构的近邻定义；
//    【推断】疑为 ·sub_5D7AE0 CNLegionExpeller 析构别名）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7E00(void *Block, char pszArg2)  // 军团驱逐者族标量删除器（析构 + 可选 free）
{
  sub_5D7AD0();  // 调 本条为该型析构的近邻定义
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7E30 sub_5D7E30 —— CNSandorExpeller 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7DD0 同构（差异：转调 ·sub_5D7CD0 —— 本条为沙多驱逐者析构的近邻定义；
//    【推断】疑为 ·sub_5D7C40 CNSandorExpeller 析构别名）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7E30(void *Block, char pszArg2)  // CNSandorExpeller 标量删除器（析构 + 可选 free）
{
  sub_5D7CD0();  // 调 本条为沙多驱逐者析构的近邻定义
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
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
char */*thiscall*/ sub_5D7E60(char *this, void *Block, int nArg3, int nArg4, int nArg5)  // 驱逐者八型外观装载的公共工厂
{
  sub_485CC0();  // IRDItem 核心构造（+132 转 clong 子对象）
  *(uint32_t *)this = &CNRDEquipment::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_4B3BE0(this + 148);  // clong 组合初始化
  sub_437E70(this + 212);  // 配置对象构造（clong/cfloat）
  sub_4E9A50(this + 1160);  // 四内联 clong 构造 + 初值（0/0/-1/0）
  *(this + 1224) = 0;  // this+1224 0x469170 读取槽
  *((uint32_t *)this + 305) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *((uint32_t *)this + 307) = 0;  // this+1228〔bLvTagInited〕
  *(this + 1232) = 1;  // this+1232 角色名标签控件
  *(this + 1234) = 0;
  *(this + 1233) = 0;
  *((uint32_t *)this + 311) = 0;  // this+1244〔nTagTimer〕
  *((uint32_t *)this + 310) = 0;
  *((uint32_t *)this + 309) = 0;  // this+1236〔field_04D4〕
  *((uint32_t *)this + 314) = 0;  // 写 this+1256 = 0（条件组表 begin）
  *((uint32_t *)this + 315) = 0;  // 写 this+1260 = 0（条件组表 end）
  *((uint32_t *)this + 316) = 0;
  *((uint32_t *)this + 318) = 0;
  sub_41BFE0((void **)this + 318, szPassword);  // 调 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 323) = 0;  // 写 this+1292 = 0（动画行表基址）
  *((uint32_t *)this + 324) = 0;  // this+324
  *((uint32_t *)this + 325) = 0;
  *((uint32_t *)this + 327) = 0;  // 写 this+1308 = 0（动画行向量 begin）
  *((uint32_t *)this + 328) = 0;  // 写 this+1312 = 0（动画行向量 end）
  *((uint32_t *)this + 329) = 0;  // 写 this+1316 = 0（动画行向量 cap）
  sub_4E9D70(this);  // 对象字段复位（属性/名字/标志组）
  sub_4EE580(Block, nArg3, nArg4, nArg5);  // 调 物品实例生成（按文件名）
  return this;  // 返回自身指针
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
void /*thiscall*/ sub_5D7F80(char **this)  // 函数定义: 锤王七件外观装载（Monster/Soldier/HammerKing 七件 .equ 查表循环）
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/HammerKing/Cloak1.equ";  // 字符串 “Monster/Soldier/HammerKing/Cloak1.equ”
  v6[1] = "Monster/Soldier/HammerKing/Cloak2.equ";  // 字符串 “Monster/Soldier/HammerKing/Cloak2.equ”
  v6[2] = "Monster/Soldier/HammerKing/Leg.equ";  // 字符串 “Monster/Soldier/HammerKing/Leg.equ”
  v6[3] = "Monster/Soldier/HammerKing/Head1.equ";  // 字符串 “Monster/Soldier/HammerKing/Head1.equ”
  v6[4] = "Monster/Soldier/HammerKing/Head2.equ";  // 字符串 “Monster/Soldier/HammerKing/Head2.equ”
  v6[5] = "Monster/Soldier/HammerKing/Shield.equ";  // 字符串 “Monster/Soldier/HammerKing/Shield.equ”
  v6[6] = "Monster/Soldier/HammerKing/Weapon.equ";  // 字符串 “Monster/Soldier/HammerKing/Weapon.equ”
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )  // 若 v3 有效（非空）
    {
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v5 = sub_4BA9E0(pMem, v3, 0);  // 结果 = CNRDEquipment 构造（.equ 外观对象公共工厂）
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
char */*thiscall*/ sub_5D8040(char **this)  // 守卫外观装载（off_795608 路径表 + GuardHandle.equ 单件）
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
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v4 = sub_5D7E60(pMem, *v1, 0, 0, 3);  // 结果 = 驱逐者八型外观装载的公共工厂
      else
        v4 = nullptr;
      *pThis_86C = v4;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
  pMem2 = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
  {
    result = sub_5D7E60(pMem2, "Monster/Soldier/Guard/GuardHandle.equ", 0, 0, 0);  // 字符串 “Monster/Soldier/Guard/GuardHandle.equ”
    *(this + 2162) = result;  // 写 this+8648 = result（相位/缓存槽）
  }
  else
  {
    *(this + 2162) = nullptr;  // 写 this+8648 = nullptr（相位/缓存槽）
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
char */*thiscall*/ sub_5D8120(char **this)  // 守卫外观装载 2（off_795608 路径表 + GuardHandle.equ 双件）
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
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v4 = sub_5D7E60(pMem, *v1, 0, 0, 4);  // 结果 = 驱逐者八型外观装载的公共工厂
      else
        v4 = nullptr;
      *pThis_86C = v4;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
  pMem2 = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_5D7E60(pMem2, "Monster/Soldier/Guard/GuardHandle.equ", 0, 0, 0);  // 字符串 “Monster/Soldier/Guard/GuardHandle.equ”
  else
    v6 = nullptr;
  *(this + 2162) = v6;  // 写 this+8648 = v6（相位/缓存槽）
  pMem3 = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    result = sub_5D7E60(pMem3, "Monster/Soldier/Guard/GuardHandle.equ", 0, 0, 0);  // 字符串 “Monster/Soldier/Guard/GuardHandle.equ”
  else
    result = nullptr;
  *(this + 2163) = result;  // 写 this+8652 = result（相位槽）
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D8230 sub_5D8230 —— 外观装载表 e1 型（off_795608 路径表 + 变体号 1）
// 与 ·sub_5D8040 同构（差异：off_795608 逐项经 ·sub_5D7E60 变体号 1 成件，无后续单件补装）
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8230(char **this)  // 函数定义: 外观装载表 e1 型（off_795608 路径表 + 变体号 1）
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
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v4 = sub_5D7E60(pMem, *v1, 0, 0, 1);  // 结果 = 驱逐者八型外观装载的公共工厂
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
void /*thiscall*/ sub_5D82C0(char **this)  // 函数定义: 外观装载表 e2 型（off_795608 路径表 + 变体号 2）
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
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v4 = sub_5D7E60(pMem, *v1, 0, 0, 2);  // 结果 = 驱逐者八型外观装载的公共工厂
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
void /*thiscall*/ sub_5D8350(char **this)  // 函数定义: 外观装载表 e0 型（off_795608 路径表 + 变体号 0）
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
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v4 = sub_5D7E60(pMem, *v1, 0, 0, 0);  // 结果 = 驱逐者八型外观装载的公共工厂
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
void /*thiscall*/ sub_5D83E0(char **this)  // 函数定义: 驱逐者外观装载：Expeller 六件套（Leg/Head/RArm/LArm/HeadEnd/Glow）
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/Expeller/ExpellerLeg.equ";  // 字符串 “Monster/Soldier/Expeller/ExpellerLeg.equ”
  v6[1] = "Monster/Soldier/Expeller/ExpellerHead.equ";  // 字符串 “Monster/Soldier/Expeller/ExpellerHead.equ”
  v6[2] = "Monster/Soldier/Expeller/ExpellerRightArm.equ";  // 字符串 “Monster/Soldier/Expeller/ExpellerRightArm.eq”
  v6[3] = "Monster/Soldier/Expeller/ExpellerLeftArm.equ";  // 字符串 “Monster/Soldier/Expeller/ExpellerLeftArm.equ”
  v6[4] = "Monster/Soldier/Expeller/ExpellerHeadEnd.equ";  // 字符串 “Monster/Soldier/Expeller/ExpellerHeadEnd.equ”
  v6[5] = "Monster/Soldier/Expeller/ExpellerGlow.equ";  // 字符串 “Monster/Soldier/Expeller/ExpellerGlow.equ”
  v6[6] = 0;
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )  // 若 v3 有效（非空）
    {
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v5 = sub_4BA9E0(pMem, v3, 0);  // 结果 = CNRDEquipment 构造（.equ 外观对象公共工厂）
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
void /*thiscall*/ sub_5D8490(char **this)  // 函数定义: AxeExpeller 外观装载：Monster/Soldier/AxeExpeller 六件套
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/AxeExpeller/AxeExpellerLeg.equ";  // 字符串 “Monster/Soldier/AxeExpeller/AxeExpellerLeg.e”
  v6[1] = "Monster/Soldier/AxeExpeller/AxeExpellerHead.equ";  // 字符串 “Monster/Soldier/AxeExpeller/AxeExpellerHead.”
  v6[2] = "Monster/Soldier/AxeExpeller/AxeExpellerRightArm.equ";  // 字符串 “Monster/Soldier/AxeExpeller/AxeExpellerRight”
  v6[3] = "Monster/Soldier/AxeExpeller/AxeExpellerLeftArm.equ";  // 字符串 “Monster/Soldier/AxeExpeller/AxeExpellerLeftA”
  v6[4] = "Monster/Soldier/AxeExpeller/AxeExpellerHeadEnd.equ";  // 字符串 “Monster/Soldier/AxeExpeller/AxeExpellerHeadE”
  v6[5] = "Monster/Soldier/AxeExpeller/AxeExpellerGlow.equ";  // 字符串 “Monster/Soldier/AxeExpeller/AxeExpellerGlow.”
  v6[6] = 0;
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )  // 若 v3 有效（非空）
    {
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v5 = sub_4BA9E0(pMem, v3, 0);  // 结果 = CNRDEquipment 构造（.equ 外观对象公共工厂）
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
void /*thiscall*/ sub_5D8540(char **this)  // 函数定义: HeavenExpeller 外观装载：天界驱逐者七件套（Leg/Head/双边臂/LeftArmHandle/He…
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/HeavenExpeller/HeavenExpellerLeg.equ";  // 字符串 “Monster/Soldier/HeavenExpeller/HeavenExpelle”
  v6[1] = "Monster/Soldier/HeavenExpeller/HeavenExpellerHead.equ";  // 字符串 “Monster/Soldier/HeavenExpeller/HeavenExpelle”
  v6[2] = "Monster/Soldier/HeavenExpeller/HeavenExpellerRightArm.equ";  // 字符串 “Monster/Soldier/HeavenExpeller/HeavenExpelle”
  v6[3] = "Monster/Soldier/HeavenExpeller/HeavenExpellerLeftArm.equ";  // 字符串 “Monster/Soldier/HeavenExpeller/HeavenExpelle”
  v6[4] = "Monster/Soldier/HeavenExpeller/HeavenExpellerLeftArmHandle.equ";  // 字符串 “Monster/Soldier/HeavenExpeller/HeavenExpelle”
  v6[5] = "Monster/Soldier/HeavenExpeller/HeavenExpellerHeadEnd.equ";  // 字符串 “Monster/Soldier/HeavenExpeller/HeavenExpelle”
  v6[6] = "Monster/Soldier/HeavenExpeller/HeavenExpellerGlow.equ";  // 字符串 “Monster/Soldier/HeavenExpeller/HeavenExpelle”
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )  // 若 v3 有效（非空）
    {
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v5 = sub_4BA9E0(pMem, v3, 0);  // 结果 = CNRDEquipment 构造（.equ 外观对象公共工厂）
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
void /*thiscall*/ sub_5D8600(char **this)  // 函数定义: AxionExpeller 外观装载：冲击驱逐者七件套（含 LeftArmHandle 挂件）
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/AxionExpeller/AxionExpellerLeg.equ";  // 字符串 “Monster/Soldier/AxionExpeller/AxionExpellerL”
  v6[1] = "Monster/Soldier/AxionExpeller/AxionExpellerHead.equ";  // 字符串 “Monster/Soldier/AxionExpeller/AxionExpellerH”
  v6[2] = "Monster/Soldier/AxionExpeller/AxionExpellerRightArm.equ";  // 字符串 “Monster/Soldier/AxionExpeller/AxionExpellerR”
  v6[3] = "Monster/Soldier/AxionExpeller/AxionExpellerLeftArm.equ";  // 字符串 “Monster/Soldier/AxionExpeller/AxionExpellerL”
  v6[4] = "Monster/Soldier/AxionExpeller/AxionExpellerLeftArmHandle.equ";  // 字符串 “Monster/Soldier/AxionExpeller/AxionExpellerL”
  v6[5] = "Monster/Soldier/AxionExpeller/AxionExpellerHeadEnd.equ";  // 字符串 “Monster/Soldier/AxionExpeller/AxionExpellerH”
  v6[6] = "Monster/Soldier/AxionExpeller/AxionExpellerGlow.equ";  // 字符串 “Monster/Soldier/AxionExpeller/AxionExpellerG”
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )  // 若 v3 有效（非空）
    {
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v5 = sub_4BA9E0(pMem, v3, 0);  // 结果 = CNRDEquipment 构造（.equ 外观对象公共工厂）
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
void /*thiscall*/ sub_5D86C0(char **this)  // 函数定义: TSMExpeller 外观装载：Monster/Soldier/TSMExpeller 六件套
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/TSMExpeller/TSMExpellerLeg.equ";  // 字符串 “Monster/Soldier/TSMExpeller/TSMExpellerLeg.e”
  v6[1] = "Monster/Soldier/TSMExpeller/TSMExpellerHead.equ";  // 字符串 “Monster/Soldier/TSMExpeller/TSMExpellerHead.”
  v6[2] = "Monster/Soldier/TSMExpeller/TSMExpellerRightArm.equ";  // 字符串 “Monster/Soldier/TSMExpeller/TSMExpellerRight”
  v6[3] = "Monster/Soldier/TSMExpeller/TSMExpellerLeftArm.equ";  // 字符串 “Monster/Soldier/TSMExpeller/TSMExpellerLeftA”
  v6[4] = "Monster/Soldier/TSMExpeller/TSMExpellerHeadEnd.equ";  // 字符串 “Monster/Soldier/TSMExpeller/TSMExpellerHeadE”
  v6[5] = "Monster/Soldier/TSMExpeller/TSMExpellerGlow.equ";  // 字符串 “Monster/Soldier/TSMExpeller/TSMExpellerGlow.”
  v6[6] = 0;
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )  // 若 v3 有效（非空）
    {
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v5 = sub_4BA9E0(pMem, v3, 0);  // 结果 = CNRDEquipment 构造（.equ 外观对象公共工厂）
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
void /*thiscall*/ sub_5D8770(char **this)  // 函数定义: LegionExpeller 外观装载：军团驱逐者六件套
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/LegionExpeller/LegionExpellerLeg.equ";  // 字符串 “Monster/Soldier/LegionExpeller/LegionExpelle”
  v6[1] = "Monster/Soldier/LegionExpeller/LegionExpellerHead.equ";  // 字符串 “Monster/Soldier/LegionExpeller/LegionExpelle”
  v6[2] = "Monster/Soldier/LegionExpeller/LegionExpellerRightArm.equ";  // 字符串 “Monster/Soldier/LegionExpeller/LegionExpelle”
  v6[3] = "Monster/Soldier/LegionExpeller/LegionExpellerLeftArm.equ";  // 字符串 “Monster/Soldier/LegionExpeller/LegionExpelle”
  v6[4] = "Monster/Soldier/LegionExpeller/LegionExpellerHeadEnd.equ";  // 字符串 “Monster/Soldier/LegionExpeller/LegionExpelle”
  v6[5] = "Monster/Soldier/LegionExpeller/LegionExpellerGlow.equ";  // 字符串 “Monster/Soldier/LegionExpeller/LegionExpelle”
  v6[6] = 0;
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )  // 若 v3 有效（非空）
    {
      pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v5 = sub_4BA9E0(pMem, v3, 0);  // 结果 = CNRDEquipment 构造（.equ 外观对象公共工厂）
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
char */*thiscall*/ sub_5D8820(char **this)  // SandorExpeller 外观装载：桑德尔驱逐者六件套（直接表循环 6 项）
{
  int v1; // esi
  char **pThis_86C; // edi
  char *pMem; // eax
  char *result; // eax
  uint32_t v5[7]; // [esp+8h] [ebp-28h]
  int v6; // [esp+2Ch] [ebp-4h]

  v5[0] = "Monster/Soldier/SandorExpeller/SandorExpellerLeg.equ";  // 字符串 “Monster/Soldier/SandorExpeller/SandorExpelle”
  v5[1] = "Monster/Soldier/SandorExpeller/SandorExpellerHead.equ";  // 字符串 “Monster/Soldier/SandorExpeller/SandorExpelle”
  v5[2] = "Monster/Soldier/SandorExpeller/SandorExpellerRightArm.equ";  // 字符串 “Monster/Soldier/SandorExpeller/SandorExpelle”
  v5[3] = "Monster/Soldier/SandorExpeller/SandorExpellerLeftArm.equ";  // 字符串 “Monster/Soldier/SandorExpeller/SandorExpelle”
  v5[4] = "Monster/Soldier/SandorExpeller/SandorExpellerHeadEnd.equ";  // 字符串 “Monster/Soldier/SandorExpeller/SandorExpelle”
  v5[5] = "Monster/Soldier/SandorExpeller/SandorExpellerGlow.equ";  // 字符串 “Monster/Soldier/SandorExpeller/SandorExpelle”
  v1 = 0;
  pThis_86C = this + 2156;
  do
  {
    pMem = (char *)operator new(0x544u);  // 堆分配 1348 字节对象
    v5[6] = pMem;
    v6 = 0;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      result = sub_4BA9E0(pMem, (void *)v5[v1], 0);  // 结果 = CNRDEquipment 构造（.equ 外观对象公共工厂）
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
uint32_t */*thiscall*/ sub_5D88C0(uint32_t *this, char ArgList, int nArg3)  // CNExpeller 主构造（Expeller 破碎原型）
{
  uint32_t *pThis_5B; // eax

  sub_5D6CF0(ArgList, nArg3);  // CNSoldier 基类构造 + 守卫字段区清零 + 三语音槽（AMOR_HIT/R_EXP
  *this = &CNExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(this + 2176) = -1;  // this+8704〔pSegNameTbl8704(推断)〕
  *(this + 2177) = -1;  // this+8708〔pCandTbl8708(推断)〕
  *(this + 2178) = -1;  // this+8712〔nCandTblEnd8712(推断)〕
  if ( *(this + 96) < 0x10u )  // 判定 “+384 SSO容量”
    pThis_5B = this + 91;
  else
    pThis_5B = (uint32_t *)*(this + 91);  // this+364〔pAnimNameStr(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(  // 虚调用 vt+1352
    this,
    pThis_5B,
    "Particle/ExpellerBrokenParts.ptl");  // 字符串 “Particle/ExpellerBrokenParts.ptl”
  sub_5D83E0(this);  // 驱逐者外观装载：Expeller 六件套（Leg/Head/RArm/LArm/HeadEn
  sub_4D50A0(*(uint32_t *)(*(this + 1554) + 16));  // 调 触发初次刷新
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8970 sub_5D8970 —— 标量删除器（转调 ·sub_5D89A0 析构，pszArg2&1 时 free）
// 标准 ICD 删除器形态：尾调析构后按掩码最低位判定是否 j__free 释放本块
// ------------------------------------------------------------
void */*thiscall*/ sub_5D8970(void *Block, char pszArg2)  // 标量删除器（转调 ·sub_5D89A0 析构，pszArg2&1 时 free）
{
  sub_5D89A0();  // CNExpeller 析构（重挂 vftable 后转调 ·sub_5D6E40 守卫族基析
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
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
int /*thiscall*/ sub_5D89A0(void *this)  // 实现：CNExpeller 析构（重挂 vftable 后转调 ·sub_5D6E40 守卫族基析构）
{
  *(uint32_t *)this = &CNExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  return sub_5D6E40(this);  // 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D89B0 sub_5D89B0 —— CNAxionExpeller 主构造（冲击驱逐者）
// 基类 ·sub_5D6CF0 后挂 CNAxionExpeller vftable；·sub_5D4340 战损一段（AMOR_HIT + 爆碎粒子）、
// ·sub_5D8600 七件套装载、·sub_4D50A0 刷新，pszArg4==1 时 ·sub_5CF120 补挂默认件【推断】
// 与 ·sub_5D88C0 同族（差异：无破碎粒子 ptl 挂装；装载七件套型）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D89B0(uint32_t *this, char ArgList, int nArg3, char pszArg4)  // CNAxionExpeller 主构造（冲击驱逐者）
{
  sub_5D6CF0(ArgList, nArg3);  // CNSoldier 基类构造 + 守卫字段区清零 + 三语音槽（AMOR_HIT/R_EXP
  *this = &CNAxionExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_5D4340(this);  // 阿莫尔战损第一段（AMOR_HIT + 爆碎粒子）
  sub_5D8600(this);  // AxionExpeller 外观装载：冲击驱逐者七件套（含 LeftArmHandle 挂件
  sub_4D50A0(*(uint32_t *)(*(this + 1554) + 16));  // 调 触发初次刷新
  if ( pszArg4 == 1 )
    sub_5CF120(this);  // 法杖态关闭
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8A30 sub_5D8A30 —— 标量删除器（转调 ·sub_5D8A60 析构，pszArg2&1 时 free）
// 标准 ICD 删除器形态：尾调析构后按掩码最低位判定是否 j__free 释放本块
// ------------------------------------------------------------
void */*thiscall*/ sub_5D8A30(void *Block, char pszArg2)  // 标量删除器（转调 ·sub_5D8A60 析构，pszArg2&1 时 free）
{
  sub_5D8A60();  // CNAxionExpeller 析构（重挂 vftable 后转调 ·sub_5D6E40
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8A60 sub_5D8A60 —— CNAxionExpeller 析构（重挂 vftable 后转调 ·sub_5D6E40 基析构）
// 本函数无字段清理动作 —— 七件套外观件释放交由基析构链完成
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8A60(void *this)  // 实现：CNAxionExpeller 析构（重挂 vftable 后转调 ·sub_5D6E40 基析构）
{
  *(uint32_t *)this = &CNAxionExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  return sub_5D6E40(this);  // 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
}



// 相位字段（this+8824/8832/8833/8834）
// ------------------------------------------------------------
// 0x5D8A70 sub_5D8A70 —— CNTinSwordManExpeller 主构造（TSM 驱逐者）
// 基类 ·sub_5D6CF0 后挂 CNTinSwordManExpeller vftable；+8824 相位字节与 +2205/2207/2209..2211
// 计时槽区清零、+8832 置 1（this+2205 挂 ·off_6C2B88 IObject 空 vftable）；·sub_5D4420 战损二段、
// ·sub_5D10A0 驱逐者破碎 + TSM 碎屑双装载、·sub_5D86C0 六件套；pszArg4==1 时 ·sub_5CF120
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D8A70(uint8_t *this, char ArgList, int nArg3, char pszArg4)  // CNTinSwordManExpeller 主构造（TSM 驱逐者）
{
  sub_5D6CF0(ArgList, nArg3);  // CNSoldier 基类构造 + 守卫字段区清零 + 三语音槽（AMOR_HIT/R_EXP
  *(uint32_t *)this = &CNTinSwordManExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(this + 8824) = 0;  // this+8824 蓄雷次数
  *((uint32_t *)this + 2205) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *((uint32_t *)this + 2207) = 0;
  *(this + 8832) = 1;  // this+8832 蓄雷参数槽
  *(this + 8834) = 0;
  *(this + 8833) = 0;
  *((uint32_t *)this + 2211) = 0;  // this+8844〔uPhaseClock8844〕
  *((uint32_t *)this + 2210) = 0;  // this+8840〔uPhase8840(推断)〕
  *((uint32_t *)this + 2209) = 0;
  sub_5D4420(this);  // 阿莫尔战损第二段（位置双槽重置）
  sub_5D10A0(this);  // 驱逐者破碎 + TSM 碎屑双装载（TSM 型专用）
  sub_5D86C0(this);  // TSMExpeller 外观装载：Monster/Soldier/TSMExpeller 六
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));  // 调 触发初次刷新
  if ( pszArg4 == 1 )
    sub_5CF120(this);  // 法杖态关闭
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8B40 sub_5D8B40 —— 标量删除器（转调 ·sub_5D8B70 析构，pszArg2&1 时 free）
// 标准 ICD 删除器形态：尾调析构后按掩码最低位判定是否 j__free 释放本块
// ------------------------------------------------------------
void */*thiscall*/ sub_5D8B40(void *Block, char pszArg2)  // 标量删除器（转调 ·sub_5D8B70 析构，pszArg2&1 时 free）
{
  sub_5D8B70();  // CNTinSwordManExpeller 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问（this+8824）
// ------------------------------------------------------------
// 0x5D8B70 sub_5D8B70 —— CNTinSwordManExpeller 析构
// 重挂 vftable；this+2213 子对象经其 vftable[0](v, 1) 释放后槽清零，this+2205 回写
// nengine::IObject 空 vftable、+8824 相位字节清零，最后转调 ·sub_5D6E40 基析构
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8B70(uint32_t *this)  // 函数定义: CNTinSwordManExpeller 析构
{
  void (/*thiscall*/ ***fld_e2213)(uint32_t, int); // ecx

  *this = &CNTinSwordManExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2213);
  if ( v2 != nullptr )  // 若 v2 有效（非空）
    (**v2)(v2, 1);  // 调 v2 的虚函数（vt+0）
  *(this + 2213) = 0;
  *(this + 2205) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8824) = 0;  // this+8824 蓄雷次数
  return sub_5D6E40(this);  // 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
}



// AI 字段访问（this+8600/8604）
// ------------------------------------------------------------
// 0x5D8BF0 sub_5D8BF0 —— 相位槽二次清零（this+8600 字节 + this+8604 双字；恒返回 0）
// 与 ·0x5D8DA0 同片清零区 —— 本函数仅覆盖 8600/8604 两槽（窄幅复位变体）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8BF0(int this)  // 函数定义: 相位槽二次清零（this+8600 字节 + this+8604 双字；恒返回 0）
{
  *(uint8_t *)(this + 8600) = 0;  // 写 this+8600 = 0（子类AI区）
  *(uint32_t *)(this + 8604) = 0;  // 写 this+8604 = 0（子类 AI 状态字节）
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8C00 sub_5D8C00 —— 架招相位门（·sub_4E7F30(this,300) 非零 → vt+560 setState(14 蓄力架招)）
// 尾调 ·sub_4E1780（激活码轮询），其返回值透传
// ------------------------------------------------------------
char /*thiscall*/ sub_5D8C00(uint32_t *this)  // 实现：架招相位门（·sub_4E7F30(this,300) 非零 → vt+560 setState(14 蓄力架招)）
{
  if ( sub_4E7F30(this, 300, 0, 0) != 0 )  // 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 虚调用 vt+560
  return sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D8C30 sub_5D8C30 —— 状态 14 联动：帧写入（vt+196 ← *(*(this+1554)+4)）后取 this+28 关联对象
// 归零其 +5 速率槽为 1.0f 并置其 +196 激活位（对象 vt+308 存活判定）【推断】
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8C30(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 函数定义: 状态 14 联动：帧写入（vt+196 ← *(*(this+1554)+4)）后取 this+28 关联对象
{
  uint32_t *fld_e28; // esi

  if ( nArg2 == 14 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // 虚调用 vt+196
    fld_e28 = (uint32_t *)*(this + 28);  // this+28 【推断】逐帧驱动对象
    if ( *fld_e28 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0 && fld_e28[5] != 1065353216 )  // 虚调用 vt+308
    {
      fld_e28[5] = 1065353216;  // 常量 1.0f
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
uint32_t */*thiscall*/ sub_5D8C80(uint32_t *this, char ArgList, int nArg3, char pszArg4)  // CNBat 主构造（蝙蝠族）
{
  sub_4A4EA0(ArgList, nArg3);  // 调 IRDMonster 基类构造
  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *this = &CNBat::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8600) = 0;  // 写 this+8600 = 0（子类AI区）
  *(this + 2151) = 0;  // 写 this+8604 = 0（子类 AI 状态字节）
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  *((uint8_t *)this + 8624) = 0;  // this+8624 【推断】子类AI槽
  if ( pszArg4 == 1 )
  {
    *(this + 1639) = 0;  // 写 this+6556 = 0（大状态ID）
    *(this + 2151) = -1;  // 写 this+8604 = -1（子类 AI 状态字节）
    *((uint8_t *)this + 8600) = 1;  // 写 this+8600 = 1（子类AI区）
  }
  sub_4D50A0(*(uint32_t *)*(this + 1554));  // 调 触发初次刷新
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8D40 sub_5D8D40 —— CNBat 析构（重挂 vftable 后转调 ·sub_4A50F0 基析构）
// 本函数无字段清理动作（蝙蝠族字段由基析构链回收）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8D40(uint32_t *this)  // 实现：CNBat 析构（重挂 vftable 后转调 ·sub_4A50F0 基析构）
{
  *this = &CNBat::`vftable';  // 写 vftable 指针（对象重定位/复位）
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8D50 sub_5D8D50 —— 标量删除器（转调 ·sub_5D8D40 析构，pszArg2&1 时 free）
// 标准 ICD 删除器形态：尾调析构后按掩码最低位判定是否 j__free 释放本块
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D8D50(uint32_t *Block, char pszArg2)  // 标量删除器（转调 ·sub_5D8D40 析构，pszArg2&1 时 free）
{
  sub_5D8D40(Block);  // CNBat 析构（重挂 vftable 后转调 ·sub_4A50F0 基析构）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8D80 sub_5D8D80 —— 子对象释放（this+2159 经其 vftable[0](v,1) 析构，槽随后清零）
// 与 ·0x5DA0E0 析构中的同型子对象释放段一致（2159 槽复用形态）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8D80(uint32_t *this)  // 函数定义: 子对象释放（this+2159 经其 vftable[0](v,1) 析构，槽随后清零）
{
  int (/*thiscall*/ ***fld_e2159)(uint32_t, int); // ecx
  int result; // eax

  fld_e2159 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2159);  // this+8636〔pDollTarget(推断)〕
  if ( fld_e2159 != nullptr )  // 若 fld_e2159 有效（非空）
    result = (**fld_e2159)(fld_e2159, 1);  // 调 fld_e2159 的虚函数（vt+0）
  *(this + 2159) = 0;  // this+8636〔pDollTarget(推断)〕
  return result;
}



// AI 相位字段（this+8600/8604/8628）
// ------------------------------------------------------------
// 0x5D8DA0 sub_5D8DA0 —— 邪眼族相位大区清零（+6792..6808 五槽、+8600/+8604、+7144）
// 并把 +8628 置 5（帧索引/相位初值，与 ·0x5DA220 同片字段区呼应）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8DA0(int this)  // 函数定义: 邪眼族相位大区清零（+6792..6808 五槽、+8600/+8604、+7144）
{
  *(uint32_t *)(this + 6792) = 0;  // this+6792 邪眼圈参数槽 1
  *(uint32_t *)(this + 6796) = 0;  // this+6796 邪眼圈参数槽 2
  *(uint32_t *)(this + 6800) = 0;  // this+6800 邪眼圈参数槽 3
  *(uint32_t *)(this + 6804) = 0;  // this+6804 邪眼圈参数槽 4
  *(uint32_t *)(this + 6808) = 0;  // this+6808 邪眼圈参数槽 5
  *(uint8_t *)(this + 8600) = 0;  // 写 this+8600 = 0（子类AI区）
  *(uint32_t *)(this + 8604) = 0;  // 写 this+8604 = 0（子类 AI 状态字节）
  *(uint32_t *)(this + 8628) = 5;  // this+8628 帧索引/相位初值
  *(uint8_t *)(this + 7144) = 0;  // this+7144 相位字节
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D8DE0 sub_5D8DE0 —— 行为字相位推进（·sub_4E0120 预处理后按 this+1787 行为字分派）
// 0 → vt+1284 相位解除；4/5 → 关联对象 this+1813 非空时 10% 概率经 vt+1104 写入 5/4 进阶；
// 13/14/15 有对象则回写行为字 4；无对象则 vt+1104 写 13（随机进阶档位）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8DE0(int *this)  // 实现：行为字相位推进（·sub_4E0120 预处理后按 this+1787 行为字分派）
{
  int result; // eax
  int nRand; // eax
  int v4; // et2
  int nRand2; // eax
  int v6; // et2

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // 读 result = this+7148（大状态镜像槽）
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 结果 = 虚调用 vt+1284
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_4;
      nRand = rand();  // 调 取伪随机数
      v4 = nRand % 100;
      result = nRand / 100;
      if ( v4 < 10 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);  // 结果 = 虚调用 vt+1104
      break;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
      {
        nRand2 = rand();  // 调 取伪随机数
        v6 = nRand2 % 100;
        result = nRand2 / 100;
        if ( v6 < 10 )
          goto LABEL_11;
      }
      else
      {
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 结果 = 虚调用 vt+1104
      }
      break;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_11:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 结果 = 虚调用 vt+1104
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
int /*thiscall*/ sub_5D8EC0(void *this, int nArg2)  // 函数定义: 对称随机偏移发生器（对象存活经 vt+308 门；rand%100>=50 取 +rand%n 否则…
{
  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) == 0 )  // 虚函数调用 槽+308
    return 0;
  if ( rand() % 100 >= 50 )  // 调 取伪随机数
    return rand() % nArg2;  // 调 取伪随机数
  return -(rand() % nArg2);  // 调 取伪随机数
}



// 时钟门 AI（sub_699000, 79L）
// ------------------------------------------------------------
// 0x5D8F10 sub_5D8F10 —— 行为字相位机（站姿门 vt+840 + clock_now 超时重掷）
// 行为字 this+1787-4 分派：4 → 80% 闸 + ·sub_4DA6B0 命中包；5/9 → ·sub_4DBDB0 空间栅格重叠检测；
// 13 → 40% 闸 + rand 重掷（命中 nRand==4&&nRand2==4 时超时 300ms，否则 1000ms 写入 this+1818）；
// 关联对象 this+1813 非空双向 vt+124 激活，按 iskill 表 SHIWORD(this+行为字+2092) 概率复位挡位，
// 经 vt+896 写入速率、·sub_5FDFE0 粒子与 vt+1080 收手
// ------------------------------------------------------------
int /*usercall*/ sub_5D8F10@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：行为字相位机（站姿门 vt+840 + clock_now 超时重掷）
{
  int result; // eax
  int v4; // eax
  int nRand2; // eax
  int v6; // eax
  int pObj; // ecx
  int v8; // edi
  int nRand; // [esp+4h] [ebp-8h] BYREF
  int nRand22; // [esp+8h] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 结果 = 虚调用 vt+308
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);  // 结果 = 虚调用 vt+840
    if ( result == 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 184))(pArg1, nArg2);  // 虚调用 vt+184
      (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 188))(pArg1);  // 虚调用 vt+188
      v4 = pArg1[1787] - 4;
      nRand = 4;
      nRand22 = 4;
      switch ( v4 )  // 按 v4 分派
      {
        case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
          if ( rand() % 100 >= 80 || (uint8_t)sub_4DA6B0(&nRand) != 0 )  // 调 滚动格判定
            goto LABEL_7;
          goto LABEL_6;
        case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
LABEL_6:
          sub_4DBDB0(&nRand, &nRand22);  // 调 空间栅格重叠检测（碰撞/挤压分离轴；研究第 24/25 轮族）
          goto LABEL_7;
        case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
          if ( rand() % 100 >= 40 )  // 调 取伪随机数
          {
LABEL_7:
            nRand2 = nRand22;
          }
          else
          {
            if ( (uint8_t)sub_4DA6B0(&nRand) == 0 )  // 调 滚动格判定
              nRand = rand() % 2;  // 调 取伪随机数
            nRand2 = rand() % 2 + 2;  // 调 取伪随机数
            nRand22 = nRand2;
          }
          if ( nRand == 4 && nRand2 == 4 )  // 若 nRand == 4 与/或 nRand2 == 4
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
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);  // 虚调用 vt+124
      }
      v8 = pArg1[1787];
      if ( rand() % 100 < SHIWORD(pArg1[v8 + 2092]) )  // 调 取伪随机数
        nRand22 = 4;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 896))(pArg1, nRand);  // 虚调用 vt+896
      sub_5FDFE0(pArg1[1932]);  // 调 粒子与 vt+1080 收手
      return (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1080))(pArg1);  // 虚调用 vt+1080
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
int /*userpurge*/ sub_5D90F0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4, int nArg5, int nArg6, void *Block, int nArg8)  // 实现：困难级伤害定位摆动（this+1943==3）
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
    return sub_4E22E0(nArg3, nArg4, nArg5, nArg6, Block, nArg8);  // 掉落物生成（角度均分 + 定位 + 文本倒计时）
  v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 152))(pArg1, nArg2);  // 结果 = 虚调用 vt+152
  v10 = *pArg1;
  if ( v9 != 0 )
  {
    v19 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 128))(pArg1);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v20 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v19);  // 结果 = 虚调用 vt+124
    v21 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v20);  // 结果 = 虚调用 vt+120
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v10 + 112))(pArg1, v21 + 115);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
    sub_4E22E0(nArg3, nArg4, nArg5, nArg6, Block, nArg8);  // 掉落物生成（角度均分 + 定位 + 文本倒计时）
    v22 = *pArg1;
    v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);  // 结果 = 虚调用 vt+128
    v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v23);  // 结果 = 虚调用 vt+124
    v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v24);  // 结果 = 虚调用 vt+120
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v22 + 112))(pArg1, v25 - 115);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  }
  else
  {
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 128))(pArg1);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v11);  // 结果 = 虚调用 vt+124
    v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v12);  // 结果 = 虚调用 vt+120
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v10 + 112))(pArg1, v13 - 115);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
    sub_4E22E0(nArg3, nArg4, nArg5, nArg6, Block, nArg8);  // 掉落物生成（角度均分 + 定位 + 文本倒计时）
    v14 = *pArg1;
    v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);  // 结果 = 虚调用 vt+128
    v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v15);  // 结果 = 虚调用 vt+124
    v17 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v16);  // 结果 = 虚调用 vt+120
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v14 + 112))(pArg1, v17 + 115);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  }
}



// 邪眼现身：EYE_APPEAR 播报（79L；this+204/208/8685/8686 相位）
// ------------------------------------------------------------
// 0x5D9210 sub_5D9210 —— 邪眼现身相位机（EYE_APPEAR）
// this+2175 相位 0→1：vt+204 帧写入 + 倒计时 5000ms 起、子链 8685/8686 清零、this+2176 计零；
// 相位 1：每 500ms 经 vt+584 发射 30303 弹（伤害 10/4/100）并播报 EYE_APPEAR，clock 达
// this+2174 后切相 2；相位 2：vt+208 帧复位 + vt+560 setState(0) 回待机并置 3
// ------------------------------------------------------------
char /*thiscall*/ sub_5D9210(int *this)  // 函数定义: 邪眼现身相位机（EYE_APPEAR）
{
  int fld_e2175; // eax
  int fld_e1813; // ecx
  int v4; // edi
  int fld_e18132; // ebx
  int fld_e2174; // edi

  fld_e2175 = *(this + 2175);  // this+8700〔uPhase8700(推断)〕
  if ( fld_e2175 != 0 )
  {
    if ( fld_e2175 == 1 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0  // 虚调用 vt+308
        && (unsigned int)(sub_699000((int)(this + 2168)) - *(this + 2176)) > 0x1F4 )  // 【clock_now(clk)】
      {
        fld_e1813 = *(this + 1813);  // this+7252〔pTarget7252〕
        if ( fld_e1813 != 0 )
        {
          v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
          fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 128))(*(this + 1813));  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 584))(  // 虚调用 vt+584
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
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "EYE_APPEAR", -1, 0, 0);  // 字符串 “EYE_APPEAR”
        }
        *(this + 2176) = sub_699000((int)(this + 2168));  // clock_now(clk)
      }
      fld_e2174 = *(this + 2174);  // this+8696〔uVec8696(推断)〕
      fld_e2175 = sub_699000((int)(this + 2168));  // 【clock_now(clk)】
      if ( fld_e2175 >= fld_e2174 )
        *(this + 2175) = 2;  // this+8700〔uPhase8700(推断)〕
    }
    else if ( fld_e2175 == 2 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));  // 虚调用 vt+208
      LOBYTE(fld_e2175) = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 虚调用 vt+560
      *(this + 2175) = 3;  // this+8700〔uPhase8700(推断)〕
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204
      this,
      1,
      *(uint32_t *)(*(this + 1554) + 12),  // this+6216〔pTbl6216(推断)〕
      0,
      0,
      0,
      0);
    *(this + 2175) = 1;  // this+8700〔uPhase8700(推断)〕
    sub_49C620(3, 1, 5000);  // 命令下发包装（组 id = this+4，值重复两遍）
    sub_49C5F0(3, 0, 0, 5000);  // 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
    *((uint8_t *)this + 8685) = 0;  // this+8685 【推断】挥击/散射语音锁存
    *((uint8_t *)this + 8686) = 0;
    LOBYTE(fld_e2175) = sub_698F90((int)(this + 2168), 5000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(this + 2176) = 0;  // this+8704〔pSegNameTbl8704(推断)〕
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
char /*usercall*/ sub_5D93A0@<al>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：邪眼主技能状态机（大状态 8/14/17/9 分派）
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

  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);  // 结果 = 虚调用 vt+840
  v5 = *pArg1;
  if ( v4 == 8 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 840))(pArg1) == 17 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
      goto LABEL_6;
    v6 = (uint32_t *)(pArg1[1554] + 12);
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v5 + 208))(pArg1, *(uint32_t *)(pArg1[1554] + 4));  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
    v6 = (uint32_t *)(pArg1[1554] + 20);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, *v6);  // 虚调用 vt+208
LABEL_6:
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 8 )  // 虚调用 vt+840
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 908))(pArg1);  // 结果 = 虚调用 vt+908
    v8 = *pArg1;
    if ( v7 == 1 )
    {
      if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(v8 + 200))(pArg1) + 148) >= 3 && *((uint8_t *)pArg1 + 8600) == 1 )  // 虚函数调用 槽+200：取动画对象
      {
        v9 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 152))(pArg1, nArg3, nArg2);  // 结果 = 虚调用 vt+152
        if ( v9 != 0 )
        {
          v11 = sub_425050(*(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 44));  // 结果 = 总宽换算
          v10 = 1374389535LL * (v11 - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));  // 结果 = 虚调用 vt+120
        }
        else
        {
          v10 = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);  // 结果 = 虚调用 vt+120
        }
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580
          pArg1,
          48029,
          (SHIDWORD(v10) >> 5) + (HIDWORD(v10) >> 31),  // 调 取 64 位值高 32 位(带符号)
          0,
          0,
          85,
          0,
          107,
          v9,
          0);
        *((uint8_t *)pArg1 + 8600) = 0;
        sub_432EA0("STONE_LASER_READY", -1, 0, 0);  // 字符串 “STONE_LASER_READY”
      }
      else if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 148) >= 8  // 虚调用 vt+200
             && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 568))(pArg1) != 14 )  // 虚调用 vt+568
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 14, 0, 0, 0);  // 虚调用 vt+560
      }
    }
    else
    {
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 908))(pArg1) == 2;  // 虚函数调用 槽+908：[RTTI: IRDActiveObject__vmt38C…
      v13 = *pArg1;
      if ( v12 )
      {
        if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(v13 + 200))(pArg1) + 148) >= 5 && *((uint8_t *)pArg1 + 8600) == 1 )  // 虚函数调用 槽+200：取动画对象
        {
          v14 = *pArg1;
          v25 = pArg1[2177];
          *((uint8_t *)pArg1 + 8600) = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v14 + 580))(  // 虚函数调用 槽+580：位置化动作发布（会话 3 定案：位置化动作）
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
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580
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
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580
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
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580
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
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580
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
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "EYE_SHOT", -1, 0, 0);  // 字符串 “EYE_SHOT”
        }
      }
      else if ( (*(int (/*thiscall*/ **)(uint32_t *))(v13 + 908))(pArg1) == 3 )  // 虚函数调用 槽+908：[RTTI: IRDActiveObject__vmt38C…
      {
        if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 148) >= 5 && *((uint8_t *)pArg1 + 8600) == 1 )  // 虚调用 vt+200
        {
          pObj = pArg1[1813];
          *((uint8_t *)pArg1 + 8600) = 0;
          if ( pObj != 0 )
          {
            v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
            v17 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813]);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 128))(pArg1[1813]);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*pArg1 + 584))(  // 虚调用 vt+584
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
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(  // 虚调用 vt+212
              pArg1,
              "EYE_APPEAR",  // 字符串 “EYE_APPEAR”
              -1,
              0,
              0);
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(  // 虚调用 vt+212
              pArg1,
              "BEFORE_THUNDER",  // 字符串 “BEFORE_THUNDER”
              -1,
              0,
              0);
          }
        }
      }
      else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 908))(pArg1) == 0  // 虚调用 vt+908
             && *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 148) >= 5  // 虚调用 vt+200
             && *((uint8_t *)pArg1 + 8600) == 1 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580
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
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 14;  // 结果 = 虚调用 vt+840
    v18 = *pArg1;
    if ( v12 )
    {
      if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(v18 + 200))(pArg1) + 148) >= 0 && *((uint8_t *)pArg1 + 8600) == 1 )  // 虚函数调用 槽+200：取动画对象
      {
        v19 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 152))(pArg1, nArg3, nArg2);  // 结果 = 虚调用 vt+152
        if ( v19 != 0 )
        {
          v21 = sub_425050(*(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 44));  // 结果 = 总宽换算
          v20 = 1374389535LL * (v21 - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));  // 结果 = 虚调用 vt+120
        }
        else
        {
          v20 = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);  // 结果 = 虚调用 vt+120
        }
        v22 = (SHIDWORD(v20) >> 5) + (HIDWORD(v20) >> 31);  // 调 取 64 位值高 32 位(带符号)
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int))(*pArg1 + 212))(pArg1, "STONE_LASER_FIRE", -1);  // 字符串 “STONE_LASER_FIRE”
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580
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
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0  // 虚调用 vt+200
        && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 568))(pArg1) != 0 )  // 虚调用 vt+568
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
      }
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *))(v18 + 840))(pArg1) == 17 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
    {
      sub_5D9210(pArg1);  // 邪眼现身相位机（EYE_APPEAR）
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 9 && pArg1[2151] == 1 )  // 虚调用 vt+840
    {
      v23 = (uint32_t *)(pArg1[1554] + 8);
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) != *v23 )  // 虚调用 vt+200
      {
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 8));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 8));  // 虚调用 vt+196
      }
      if ( (unsigned int)(sub_699000((int)(pArg1 + 9)) - pArg1[2156]) > 0xFA0  // 【clock_now(clk)】
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )  // 虚调用 vt+308
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t *, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 5, pArg1 + 2152, 0, 0);  // 虚调用 vt+560
        pArg1[2151] = 2;
      }
    }
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 8 || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) >= 14 )  // 虚调用 vt+840
  {
    sub_4D9360(pArg1);
    return sub_4E1780(pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  }
  else
  {
    sub_4D93D0(pArg1);
    return sub_4E1780(pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  }
}


// 时钟门+插值 AI（sub_699000+sub_4049C0; this+200）
// ------------------------------------------------------------
// 0x5D9950 sub_5D9950 —— 状态 9 消散演出（时钟插值渐隐 + 抖动位移）
// clock_now-this+2156 经 ·sub_4049C0(255..0,1000ms) 换算 alpha 后 ·sub_491690 通道写入（1/5/1）；
// this+2157 计数 >0 时每 300ms 经 ·sub_5D8EC0 三轴抖动 + ·sub_605840 打包 + ·sub_4E4A50 请求
// 42005 效果并递减；计数耗尽后 ·sub_4600B0 双轴写入 + 子链帧游标 ·sub_4924C0 复位（3000ms 槽）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D9950(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 函数定义: 状态 9 消散演出（时钟插值渐隐 + 抖动位移）
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
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 9 )  // 虚调用 vt+840
    {
      fld_e2156 = sub_699000((int)(this + 9)) - *(this + 2156);  // 【clock_now(clk)】
      if ( fld_e2156 >= 0x3E8 )  // 比较常量 0x3E8（= 1000（毫秒））
        LOBYTE(v7) = 0;  // 调 取 16 位值低 8 位
      else
        v7 = (uint64_t)sub_4049C0(255.0, 0.0, fld_e2156, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v19 = ((uint8_t)v7 << 24) | 0xFFFFFF;
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 虚调用 vt+200
      sub_491690(1, 5, 1, -1, v19, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
      if ( (int)*(this + 2157) <= 0 )  // this+8628〔nPoolTime(推断)〕
      {
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 1 ? -50 : 50;  // 结果 = 虚调用 vt+152
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + v13;  // 结果 = 虚调用 vt+120
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2159) + 40))(*(this + 2159), v14, v15, 60);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
        (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2159) + 92))(*(this + 2159), v28);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
        fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
        v34 = 0;
        sub_4600B0(fld_e29, 2, 0, (int)v28);  // 调 演播层注册(槽号)
        Block2 = Block;
        if ( Block != v30 )
        {
          do
          {
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 200))(*Block2);  // 虚调用 vt+200
            *(uint32_t *)(sub_4924C0(0) + 48) = *(this + 2160);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
            ++Block2;
          }
          while ( Block2 != v30 );
          Block2 = Block;
        }
        v34 = -1;
        if ( Block2 != nullptr )  // 若 Block2 有效（非空）
          j__free(Block2);  // 调 堆释放
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
        v8 = sub_5D8EC0(this, 100);  // 结果 = 对称随机偏移发生器（对象存活经 vt+308 门；rand%100>=50 取 +rand%
        v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
        v10 = *this;
        v32 = v9 + v8;
        v22 = (float)(v9 + v8);
        v32 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 124))(this);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
        v23 = (float)v32;
        v11 = sub_5D8EC0(this, 50);  // 结果 = 对称随机偏移发生器（对象存活经 vt+308 门；rand%100>=50 取 +rand%
        v32 = v11 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) + 50;  // 结果 = 虚调用 vt+128
        v24 = (float)v32;
        v21 = sub_605840(&v33, this, &v22, 1);  // 结果 = 30 字节全局包
        v20 = v33;
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 结果 = 虚调用 vt+152
        sub_4E4A50(this, 42005, 1, 0, 0, 0, v12, 0, v20, v21);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
        *(this + 2158) = sub_699000((int)(this + 9));  // clock_now(clk)
        --*(this + 2157);  // this+8628〔nPoolTime(推断)〕
      }
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 9  // 虚调用 vt+840
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) <= 0 )  // 虚调用 vt+736
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 虚调用 vt+200
      sub_491690(1, 5, 1, -1, -1, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
    }
  }
  return sub_4D8F90(nArg2, nArg3, nArg4, nArg5);  // vmt144 转发垫片（IRDActiveObject__vmt144 族）
}



// 复合门（114L；this+612/616 反应态 + 8600/8657/8658 —— 反应态空闲门样本, 研究 15）
// ------------------------------------------------------------
// 0x5D9BF0 sub_5D9BF0 —— 复合状态门（ArgList 5/8/14/17 分派 + 超时回环）
// 5 → 存活则 this+2151=2；相位 0 时置 1、setState 9 候选、this+2152 槽写入 + 2156/2158 计零；
// 8 → 攻击入场（+8600=1 相位激活，vt+204 帧写入取 1554 双槽择一）；14 → vt+196 帧写 + vt+612(1,1)；
// 17 → 2175/8657/8658 清零 + this+2161 倒计时 30000ms 重挂；状态 0 且 this+2167 到点 → setState(17)
// 循环重挂；状态 14 → vt+612(0,0) 收架；尾调 ·sub_4E33D0 状态收尾
// ------------------------------------------------------------
int /*thiscall*/ sub_5D9BF0(uint32_t *this, int ArgList, int pArg3, int nArg4, int nArg5)  // 函数定义: 复合状态门（ArgList 5/8/14/17 分派 + 超时回环）
{
  char v5; // di
  int v7; // edx
  int fld_e1554; // eax
  uint32_t *fld_e15542; // eax
  int v10; // edx
  int v11; // eax
  int fld_e2167; // ebx

  v5 = ArgList;
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308
        *(this + 2151) = 2;  // 写 this+8604 = 2（子类 AI 状态字节）
      if ( *(this + 2151) == 0 )  // 判定 “+8604 子类 AI 状态字节”
      {
        *(this + 2151) = 1;  // 写 this+8604 = 1（子类 AI 状态字节）
        LOBYTE(ArgList) = 9;  // 调 取 16 位值低 8 位
        sub_4ED3F0((int)(this + 2152), pArg3);  // int 向量拷贝赋值（全容量路径）
        *(this + 2156) = sub_699000((int)(this + 9));  // clock_now(clk)
        v5 = 9;
        *(this + 2158) = sub_699000((int)(this + 9));  // clock_now(clk)
      }
      break;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      *((uint8_t *)this + 8600) = 1;  // 写 this+8600 = 1（子类AI区）
      v7 = *this;
      fld_e1554 = *(this + 1554);  // 读 fld_e1554 = this+6216（资源/帧游标表）
      if ( **(uint32_t **)(pArg3 + 4) != 0 )  // pArg3+4〔宿主对象〕
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v7 + 204))(  // 虚函数调用 槽+204：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
          this,
          1,
          *(uint32_t *)(fld_e1554 + 4),
          0,
          0,
          0,
          0);
      else
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v7 + 204))(  // 虚函数调用 槽+204：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
          this,
          1,
          *(uint32_t *)(fld_e1554 + 20),
          0,
          0,
          0,
          0);
      break;
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      fld_e15542 = (uint32_t *)*(this + 1554);  // this+6216〔pTbl6216(推断)〕
      v10 = *this;
      *((uint8_t *)this + 8600) = 1;  // 写 this+8600 = 1（子类AI区）
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v10 + 196))(this, *fld_e15542);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 612))(this, 1, 1);  // 虚调用 vt+612
      break;
    case 17:  // case 17 = ENUM_CMDPACKET_SELECT_DUNGEON
      *(this + 2175) = 0;  // this+8700〔uPhase8700(推断)〕
      *((uint8_t *)this + 8657) = 0;  // this+8657 【推断】子类AI标记字节
      *((uint8_t *)this + 8658) = 0;  // this+8658 【推断】子类AI标记字节
      sub_698F90((int)(this + 2161), 30000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      break;
    default:
      break;
  }
  v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 结果 = 虚调用 vt+840
  if ( v11 != 0 )
  {
    if ( v11 == 14 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);  // 虚调用 vt+612
  }
  else
  {
    fld_e2167 = *(this + 2167);  // this+8668〔nCool8668(推断)〕
    if ( sub_699000((int)(this + 2161)) >= fld_e2167 )  // 【clock_now(clk)】
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 17, 0, 0, 0);  // 虚调用 vt+560
      *(this + 2175) = 0;  // this+8700〔uPhase8700(推断)〕
      *((uint8_t *)this + 8657) = 0;  // this+8657 【推断】子类AI标记字节
      *((uint8_t *)this + 8658) = 0;  // this+8658 【推断】子类AI标记字节
      sub_698F90((int)(this + 2161), 30000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    v5 = ArgList;
  }
  return sub_4E33D0(v5, *(float *)&pArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
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
int /*thiscall*/ sub_5D9DA0(uint32_t *this)  // 函数定义: 邪眼死亡演出资源预载
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

  pMem = operator new(0x12Cu);  // 堆分配 300 字节对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_428F30(pMem, (int)"Monster/Common/Particle/MonsterDieSmoke.ptl", 0);  // 字符串 “Monster/Common/Particle/MonsterDieSmoke.ptl”
  else
    v3 = nullptr;
  *(this + 2159) = v3;  // this+8636〔pDollTarget(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *))(*v3 + 28))(v3);  // 虚调用 vt+28
  fld_e2159 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2159) + 36))(*(this + 2159));  // 虚函数调用 槽+36：目标锁定（102 行：4AED00/47EFD0/605840/64F340/5…
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
  v12 = sub_41A5E0(v5 + 984);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v6 = (uint64_t)((double)v12 * COERCE_FLOAT(sub_41A5E0(v5 + 998)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)fld_e2159 = sub_4049C0(20.0, 60.0, (int)v6 - 30000, 140000);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
  Block = (void *)sub_41A5E0(v7 + 984);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v8 = (uint64_t)((double)(int)Block * COERCE_FLOAT(sub_41A5E0(v7 + 998)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v9 = (uint64_t)sub_4049C0(50.0, 150.0, (int)v8 - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(uint32_t *)(fld_e2159 + 12) = v9;
  *(uint32_t *)(fld_e2159 + 16) = 2 * v9;
  *(uint32_t *)(fld_e2159 + 20) = v9;
  *(this + 2160) = 3000;  // this+8640〔uCastSlot8640(推断)〕
  *(this + 2177) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // 虚函数调用 槽+4：复位/锁定（64F690 + 64A790 +…
                     dword_8F84E4,  // 全局 对象工厂/生成管理器
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroCenter.ptl");  // 字符串 “PassiveObject/Monster/EvilEye/Particle/Missi”
  *(this + 2178) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // 虚函数调用 槽+4：复位/锁定（64F690 + 64A790 +…
                     dword_8F84E4,  // 全局 对象工厂/生成管理器
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroCenterLeft.ptl");  // 字符串 “PassiveObject/Monster/EvilEye/Particle/Missi”
  *(this + 2179) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // 虚函数调用 槽+4：复位/锁定（64F690 + 64A790 +…
                     dword_8F84E4,  // 全局 对象工厂/生成管理器
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroCenterRight.ptl");  // 字符串 “PassiveObject/Monster/EvilEye/Particle/Missi”
  *(this + 2180) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // 虚函数调用 槽+4：复位/锁定（64F690 + 64A790 +…
                     dword_8F84E4,  // 全局 对象工厂/生成管理器
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroLeft.ptl");  // 字符串 “PassiveObject/Monster/EvilEye/Particle/Missi”
  result = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // 虚函数调用 槽+4：复位/锁定（64F690 + 64A790 +…
             dword_8F84E4,  // 全局 对象工厂/生成管理器
             "PassiveObject/Monster/EvilEye/Particle/MissileGeroRight.ptl");  // 字符串 “PassiveObject/Monster/EvilEye/Particle/Missi”
  *(this + 2181) = result;  // this+8724〔nSegThrEnd8724〕
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
int /*thiscall*/ sub_5D9F50(int this, char ArgList, int nArg3)  // 函数定义: CNEvilEye 构造，结果存 result
{
  char v5; // [esp-24h] [ebp-3Ch]
  void *v6; // [esp-20h] [ebp-38h]
  int v7; // [esp-1Ch] [ebp-34h]
  int v8; // [esp-18h] [ebp-30h]
  int v9; // [esp-14h] [ebp-2Ch]

  sub_4A4EA0(ArgList, nArg3);  // 调 IRDMonster 基类构造
  *(uint32_t *)this = &CNEvilEye::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *(uint32_t *)(this + 8612) = 0;  // this+8612 锁定/相位字节 A
  *(uint32_t *)(this + 8616) = 0;  // this+8616 【推断】钻地相位字节1
  *(uint32_t *)(this + 8620) = 0;  // this+8620 相位双字节门
  *(uint8_t *)(this + 8648) = 0;  // 写 this+8648 = 0（相位/缓存槽）
  *(uint32_t *)(this + 8644) = &off_6C2B88;  // 写 this+8644 = &off_6C2B88（相位槽）
  *(uint32_t *)(this + 8652) = 0;  // 写 this+8652 = 0（相位槽）
  *(uint8_t *)(this + 8656) = 1;  // 写 this+8656 = 1（事件 16/17 配对槽）
  *(uint8_t *)(this + 8658) = 0;  // this+8658 【推断】子类AI标记字节
  *(uint8_t *)(this + 8657) = 0;  // this+8657 【推断】子类AI标记字节
  *(uint32_t *)(this + 8668) = 0;  // this+8668 【推断】人偶行为模式
  *(uint32_t *)(this + 8664) = 0;  // this+8664 【推断】子类AI相位槽
  *(uint32_t *)(this + 8660) = 0;  // this+8660 【推断】事件配对/相位槽
  *(uint8_t *)(this + 8676) = 0;  // this+8676 【推断】子类 AI 相位槽
  *(uint32_t *)(this + 8672) = &off_6C2B88;  // this+8672 【推断】子类 AI 相位槽
  *(uint32_t *)(this + 8680) = 0;  // this+8680 【推断】子类 AI 门字节
  *(uint8_t *)(this + 8684) = 1;  // this+8684 【推断】子类 AI 门字节
  *(uint8_t *)(this + 8686) = 0;
  *(uint8_t *)(this + 8685) = 0;  // this+8685 【推断】挥击/散射语音锁存
  *(uint32_t *)(this + 8696) = 0;  // this+8696 【推断】子类 AI 向量槽
  *(uint32_t *)(this + 8692) = 0;  // this+8692 【推断】子类 AI 向量槽
  *(uint32_t *)(this + 8688) = 0;  // this+8688 【推断】子类 AI 向量/防护槽
  *(uint32_t *)(this + 6792) = 0;  // this+6792 【推断】炮车/子类参数面槽 1
  *(uint32_t *)(this + 6796) = 0;  // this+6796 【推断】炮车/子类参数面槽 2
  *(uint32_t *)(this + 6800) = 0;  // this+6800 【推断】炮车/子类参数面槽 3
  *(uint32_t *)(this + 6804) = 0;  // this+6804 【推断】炮车/子类参数面槽 4
  *(uint32_t *)(this + 6808) = 0;  // this+6808 【推断】炮车/子类参数面槽 5
  *(uint8_t *)(this + 8600) = 0;  // 写 this+8600 = 0（子类AI区）
  *(uint32_t *)(this + 8604) = 0;  // 写 this+8604 = 0（子类 AI 状态字节）
  *(uint32_t *)(this + 8628) = 5;  // this+8628 【推断】指挥计时戳
  *(uint8_t *)(this + 7144) = 0;  // this+7144 【推断】相位字节
  sub_5D9DA0((uint32_t *)this);  // 邪眼死亡演出资源预载
  *(uint8_t *)(this + 8657) = 0;  // this+8657 【推断】子类AI标记字节
  *(uint8_t *)(this + 8658) = 0;  // this+8658 【推断】子类AI标记字节
  sub_4015C0("EVIL_SHOUT", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("EVIL_SHOUT", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("EVIL_DMG", 8u);  // 【std::string构造赋值】
  LOBYTE(v6) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("EYE_WRIGGLE", 0xBu);  // 【std::string构造赋值】
  sub_4DE5E0(v5, v6, v7, v8, v9, 0, 15, 5000, 10000);  // 文案条目装载 + 随机倒计时（0x4DE410 的配套件）
  return this;  // 返回自身指针
}



// AI 字段访问（this+8648/8676）
// ------------------------------------------------------------
// 0x5DA0E0 sub_5DA0E0 —— CNEvilEye 析构
// 重挂 vftable；this+2159 粒子子对象经 vftable[0](v,1) 释放清零；+2168/+2161 回写
// nengine::IObject 空 vftable（+8676/+8648 相位字节清零）；+2153 堆数组 free 后 2153/2154/2155 清零；
// 尾调 ·sub_4A50F0 基析构
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA0E0(void *this)  // 函数定义: CNEvilEye 析构
{
  void (/*thiscall*/ ***pThis_86F)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNEvilEye::`vftable';  // 写 vftable 指针（对象重定位/复位）
  v2 = *((void (/*thiscall*/ ****)(uint32_t, int))this + 2159);
  if ( v2 != nullptr )  // 若 v2 有效（非空）
    (**v2)(v2, 1);  // 调 v2 的虚函数（vt+0）
  *((uint32_t *)this + 2159) = 0;  // this+8636〔pDollTarget(推断)〕
  *((uint32_t *)this + 2168) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 8676) = 0;  // this+8676 【推断】子类 AI 相位槽
  *((uint32_t *)this + 2161) = &nengine::IObject::`vftable';  // 写 this+8644 = &nengine::IObject::`vftable’（相位槽）
  *((uint8_t *)this + 8648) = 0;  // 写 this+8648 = 0（相位/缓存槽）
  if ( *((uint32_t *)this + 2153) != 0 )  // this+8612〔uAI8612(推断)〕
    j__free(*((void **)this + 2153));  // 调 堆释放
  *((uint32_t *)this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
  *((uint32_t *)this + 2154) = 0;  // this+8616〔uAI8616(推断)〕
  *((uint32_t *)this + 2155) = 0;  // this+8620〔uAI8620(推断)〕
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA190 sub_5DA190 —— 标量删除器（转调 ·sub_5DA0E0 析构，pszArg2&1 时 free）
// 标准 ICD 删除器形态：尾调析构后按掩码最低位判定是否 j__free 释放本块
// ------------------------------------------------------------
void */*thiscall*/ sub_5DA190(void *Block, char pszArg2)  // 标量删除器（转调 ·sub_5DA0E0 析构，pszArg2&1 时 free）
{
  sub_5DA0E0(Block);  // CNEvilEye 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA1C0 sub_5DA1C0 —— 存活查询（this+2093 对象非空且其 vt+80 判定为真）
// 供 ·0x5DA550/·0x5DA750 族受击/伤害流程的存活门复用
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_5DA1C0(uint32_t *this)  // 函数定义: 存活查询（this+2093 对象非空且其 vt+80 判定为真）
{
  int fld_e2093; // eax

  fld_e2093 = *(this + 2093);  // this+8372〔nDiffVal(推断)〕
  return fld_e2093 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2093 + 80))() != 0;  // 虚函数调用 槽+80：槽（参数写入 3 转发）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA1E0 sub_5DA1E0 —— 索引→组号映射（nArg1>=55 归 4，否则查表 dword_738048；与 ·0x5DACE0 同表）
// 供 4 组帧区（本轮序 4 组上限）取组号，超界统一折叠到组 4
// ------------------------------------------------------------
int /*cdecl*/ sub_5DA1E0(int nArg1)  // 函数定义: 存 索引→组号映射
{
  if ( nArg1 >= 55 )
    return 4;
  else
    return dword_738048[nArg1];  // 返回 取 dword_738048[nArg1]
}



// 邪眼相位字段大区（this+8216..8308, 112L —— 邪眼专用 82xx 字段块）
// ------------------------------------------------------------
// 0x5DA220 sub_5DA220 —— 邪眼相位大区复位（this+8216..8628，57 槽批量置初值）
// 默认 -1 的索引槽（8216/8400/8444/8496/8516/8536/8568/8592/8596）、组 5（8244）、
// 组 4（8252/8512/8528）、容量 100（8392）、倍率 1.0f（8388/8488）；
// 4 轮循环清 8260 起 4 个 -1 索引与 8276 起 4×2 计时对；8308..8364 十二槽与其余位清零；
// 8628 归 0（与 ·0x5D8DA0 的置 5 对照 —— 复位态）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA220(int this)  // 函数定义: 邪眼相位大区复位（this+8216..8628，57 槽批量置初值）
{
  int result; // eax
  uint32_t *pThis_2054; // esi
  uint32_t *pThis_2044; // edx
  int i; // [esp+Ch] [ebp-4h]

  result = 0;
  *(uint32_t *)(this + 8216) = -1;  // this+8216 【推断】攻击动作类型
  *(uint8_t *)(this + 8220) = 0;  // this+8220 抓取目标选择
  *(uint32_t *)(this + 8224) = 0;  // this+8224 仅见复位
  *(uint8_t *)(this + 8228) = 0;  // this+8228 0x5EA970 清零字节槽
  *(uint32_t *)(this + 8232) = 0;  // this+8232 【推断】抓取数据表读数
  *(uint32_t *)(this + 8236) = 0;  // this+8236 反射/连击计数
  *(uint32_t *)(this + 8240) = 0;  // this+8240 抓取参数个数
  *(uint32_t *)(this + 8244) = 5;  // this+8244 变体选择
  *(uint32_t *)(this + 8248) = 0;  // this+8248 变体值
  *(uint32_t *)(this + 8252) = 4;  // this+8252 抓取参数元组 [1]
  *(uint32_t *)(this + 8256) = 0;  // this+8256 抓取参数元组 [2]
  pThis_2054 = (uint32_t *)(this + 8276);  // this+8276 仅见复位
  pThis_2044 = (uint32_t *)(this + 8260);  // this+8260 相位值 A
  for ( i = 4; i != 0; --i )  // 循环：i 从 4 递减到 0
  {
    *pThis_2044 = -1;
    *pThis_2054 = 0;
    pThis_2054[1] = 0;
    ++pThis_2044;
    pThis_2054 += 2;
  }
  *(uint32_t *)(this + 8308) = 0;  // this+8308 抱人坐标 Y
  *(uint32_t *)(this + 8328) = 0;  // this+8328 仅见复位
  *(uint32_t *)(this + 8348) = 0;  // this+8348 相位奇偶
  *(uint32_t *)(this + 8312) = 0;  // this+8312 抱人坐标 Z
  *(uint32_t *)(this + 8332) = 0;  // this+8332 仅见复位
  *(uint32_t *)(this + 8352) = 0;  // 写 this+8352 = 0（骑乘/宿主槽）
  *(uint32_t *)(this + 8316) = 0;  // this+8316 抱人朝向/源对象
  *(uint32_t *)(this + 8336) = 0;  // this+8336 0x5EA970: pThis_2090=
  *(uint32_t *)(this + 8356) = 0;  // 写 this+8356 = 0（拾取信息槽 B）
  *(uint32_t *)(this + 8320) = 0;  // this+8320 【推断】抱人宿主/锚
  *(uint32_t *)(this + 8340) = 0;  // this+8340 【推断】动画对象 A
  *(uint32_t *)(this + 8360) = 0;  // 写 this+8360 = 0（拾取信息 7 字节对象指针）
  *(uint32_t *)(this + 8324) = 0;  // this+8324 抱人模式字节
  *(uint32_t *)(this + 8344) = 0;  // this+8344 【推断】骑乘模式
  *(uint32_t *)(this + 8364) = 0;  // this+8364 【推断】帧对象指针
  *(uint8_t *)(this + 8368) = 0;  // this+8368 同三元组第 2 项
  *(uint32_t *)(this + 8372) = 0;  // this+8372 0x5EA970: *
  *(uint8_t *)(this + 8376) = 0;  // this+8376 【推断】特效/技能对象B
  *(uint32_t *)(this + 8380) = 0;  // this+8380 【推断】动画对象 C
  *(uint32_t *)(this + 8384) = 0;  // this+8384 仅见复位
  *(uint32_t *)(this + 8392) = 100;  // this+8392 仅见复位
  *(uint32_t *)(this + 8396) = 0;  // this+8396 0x5EA970 经 vt+1172
  *(uint8_t *)(this + 8404) = 0;  // this+8404 【推断】特效/技能对象D
  *(uint32_t *)(this + 8400) = -1;  // this+8400 附属物/状态组件指针
  *(uint32_t *)(this + 8388) = 1065353216;  // this+8388 【推断】动画对象 D
  *(uint32_t *)(this + 8408) = 0;  // this+8408 【推断】抓取挂接对象
  *(uint32_t *)(this + 8416) = 0;
  *(uint32_t *)(this + 8424) = 0;  // this+8424 【推断】对象数组 end
  *(uint32_t *)(this + 8432) = 0;  // this+8432 【推断】Buff 挂件A
  *(uint32_t *)(this + 8412) = 0;  // this+8412 【推断】动画对象 E
  *(uint32_t *)(this + 8420) = 0;  // this+8420 【推断】对象数组 begin
  *(uint32_t *)(this + 8428) = 0;  // this+8428 【推断】对象数组 cap
  *(uint32_t *)(this + 8436) = 0;  // this+8436 【推断】Buff 挂件B
  *(uint32_t *)(this + 8440) = 0;  // this+8440 0x5DE690: *
  *(uint32_t *)(this + 8444) = -1;  // this+8444 0x5EA970: nArg2!=21 && nArg2!=6 && *
  *(uint32_t *)(this + 8448) = 0;  // this+8448 【推断】收招数据值
  *(uint32_t *)(this + 8452) = 0;
  *(uint32_t *)(this + 8456) = 0;  // this+8456 攻击倍率组件
  *(uint32_t *)(this + 8460) = 0;  // this+8460 攻击倍率浮点
  *(uint32_t *)(this + 8464) = 0;
  *(uint32_t *)(this + 8468) = 0;  // this+8468 【推断】技能对象指针
  *(uint32_t *)(this + 8472) = 0;  // this+8472 【推断】收束标志
  *(uint32_t *)(this + 8476) = 0;  // this+8476 【推断】收束门字节
  *(uint32_t *)(this + 8480) = 0;  // this+8480 【推断】攻击挂接对象
  *(uint32_t *)(this + 8484) = 0;
  *(uint32_t *)(this + 8488) = 1065353216;  // this+8488 = 1.0f
  *(uint32_t *)(this + 8492) = 0;
  *(uint32_t *)(this + 8496) = -1;  // this+8496 【推断】魔能充能态
  *(uint32_t *)(this + 8500) = 0;  // this+8500 【推断】充能计时
  *(uint8_t *)(this + 8504) = 0;  // this+8504 仅见写
  *(uint32_t *)(this + 8508) = 0;  // this+8508 仅见复位
  *(uint32_t *)(this + 8512) = 4;  // this+8512 【推断】动画对象 F
  *(uint32_t *)(this + 8516) = -1;  // this+8516 仅见复位
  *(uint8_t *)(this + 8520) = 0;  // this+8520 0x5DE690: ==0 且 *
  *(uint32_t *)(this + 8524) = 0;  // this+8524 复位批标志字节
  *(uint32_t *)(this + 8528) = 4;  // this+8528 std::string 文案串起点
  *(uint32_t *)(this + 8532) = 0;  // this+8532 0x5DE690 相位值 B
  *(uint32_t *)(this + 8536) = -1;
  *(uint32_t *)(this + 8540) = 0;  // this+8540 相位时间戳
  *(uint32_t *)(this + 8544) = 0;  // this+8544 0x5DE690 经 sub_4939E0
  *(uint32_t *)(this + 8548) = 0;  // this+8548 相位段 B 结束时刻
  *(uint32_t *)(this + 8552) = 0;
  *(uint32_t *)(this + 8556) = 0;
  *(uint32_t *)(this + 8560) = 0;
  *(uint32_t *)(this + 8564) = 0;
  *(uint32_t *)(this + 8568) = -1;  // this+8568 相位组索引
  *(uint32_t *)(this + 8572) = 0;  // this+8572 相位已历时
  *(uint32_t *)(this + 8576) = 0;  // this+8576 渐变 alpha
  *(uint32_t *)(this + 8580) = 0;  // this+8580 相位阶段号
  *(uint8_t *)(this + 8584) = 0;  // this+8584 0x5DE690: !=0 判据字节
  *(uint8_t *)(this + 8585) = 0;
  *(uint32_t *)(this + 8588) = 0;  // this+8588 仅见复位
  *(uint32_t *)(this + 8592) = -1;
  *(uint32_t *)(this + 8596) = -1;  // this+8596 命中者状态快照
  *(uint8_t *)(this + 8628) = 0;  // this+8628 【推断】指挥计时戳
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA490 sub_5DA490 —— avatar 子对象复位（·sub_4B32E0 后 +2148/2149 置 -1，返回 -1）
// 与 ·0x5DADE0（置 dword_79D100 时钟快照）配对使用 —— 复位态用 -1 表示无锚点
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA490(uint32_t *this)  // 实现：avatar 子对象复位（·sub_4B32E0 后 +2148/2149 置 -1，返回 -1）
{
  sub_4B32E0();  // 角色状态复位（含本地全局清理）
  *(this + 2148) = -1;
  *(this + 2149) = -1;  // this+8596〔bTargetState〕
  return -1;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA4B0 sub_5DA4B0 —— avatar 集合初始化（·sub_4B1670 后 +2061 槽置 5）
// +2061 与 ·0x5DAC20 的 this+2064 倒计时计数缓存同片字段区【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA4B0(uint32_t *this)  // 实现：avatar 集合初始化（·sub_4B1670 后 +2061 槽置 5）
{
  int result; // eax

  result = sub_4B1670();  // 结果 = avatar 集合初始化（+252；sub_4F3460/47E8C0/6569D0）
  *(this + 2061) = 5;  // this+8244〔nVariantSel〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DA4D0 sub_5DA4D0 —— 收招复位（this+2056 非零 → 经 vt+672(3)+1026 槽回写差值并由
// ·sub_41A590 写回速率），尾调 ·sub_4D4A20 观察者通知（受击包五号回调）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA4D0(float *this, int nArg2, int nArg3, int nArg4)  // 函数定义: 收招复位（this+2056 非零 → 经 vt+672(3)+1026 槽回写差值并由
{
  unsigned int pThis_2A0; // edi
  int v6; // edx
  float fld_e2056; // [esp+4h] [ebp-8h]
  int v9; // [esp+4h] [ebp-8h]

  if ( *(this + 2056) != 0.0 )  // this+8224〔f_2020〕
  {
    fld_e2056 = *(this + 2056);  // this+8224〔f_2020〕
    pThis_2A0 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3) + 1026;  // this+672 【推断】拾取/交互目标有效标志
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) - fld_e2056;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, v6, v9);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    *(this + 2056) = 0.0;  // this+8224〔f_2020〕
  }
  return sub_4D4A20(this, nArg2, nArg3, nArg4);  // 18 观察者通知（flag=0 轻量版；受击包五号回调）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DA550 sub_5DA550 —— 伤害计算覆写（受击方档位 vt+348 + 帧写入 vt+736）
// this+2095 对象存活且 nArg4==0 且 ·sub_4AED20 计数<=1 时：vt+648 伤害类型（100）→ vt+628
// 伤害结算（·sub_432F40 定点转换）→ 与 vt+752 上限比较钳位 → 百分比写入 this+2098；
// 命中则 vt+744 扣血 + this+2095 vt+120 反馈；返回 ·sub_4AFB80（受击流程收尾）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA550(float *this, int nArg2, int nArg3, int nArg4)  // 函数定义: 伤害计算覆写（受击方档位 vt+348 + 帧写入 vt+736）
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
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // 虚函数调用 槽+348
  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 736))(this);  // 虚函数调用 槽+736：属性块首值（GetHP 族，此处索引）
  pThis_82F = *((uint32_t *)this + 2095);  // this+8380〔pAnimC〕
  if ( pThis_82F != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pThis_82F + 80))(pThis_82F) != 0  // this+80 关联角色对象
    && (uint8_t)nArg4 == 0
    && (unsigned int)sub_4AED20((int)this) <= 1 )
  {
    v7 = *(uint32_t *)this;
    v19 = 100;
    (*(void (/*thiscall*/ **)(float *, int *, int))(v7 + 648))(this, &v19, nArg22);  // 虚函数调用 槽+648：写入 100（格挡/减伤基础值槽）
    v8 = *(uint32_t *)this;
    HIBYTE(nArg2) = 0;  // 调 取 16 位值高 8 位
    v17 = 0;
    v18 = (float)(*(int (/*thiscall*/ **)(float *, char *, int *, int, int, int, uint32_t))(v8 + 628))(  // 虚函数调用 槽+628：伤害流水线 / vt+628（研究 P14 九步公式全文定案）
                   this,
                   (char *)&nArg2 + 3,
                   &v17,
                   v19,
                   nArg22,
                   nArg3,
                   0);
    pThis_830 = (double)*((int *)this + 2096) * v18 * 0.0099999998;  // this+8384〔f_20C0〕
    pThis_2F02 = sub_432F40(pThis_830);  // 结果 = 舍入取整（float → int）
    fld_e2097 = (double)pThis_2F02 * *(this + 2097);  // this+8388〔pAnimD〕
    pThis_2F0 = sub_432F40(fld_e2097);  // 结果 = 舍入取整（float → int）
    if ( pThis_2F0 > (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 752))(this) )  // 虚函数调用 槽+752：音效地板适配判定 vmt2F0
    {
      pThis_2F0 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 752))(this);  // 虚函数调用 槽+752：音效地板适配判定 vmt2F0
      pThis_2F02 = pThis_2F0;
      fld_e20972 = (double)pThis_2F0 / *(this + 2097);  // this+8388〔pAnimD〕
      pThis_2F02 = sub_432F40(fld_e20972);  // 结果 = 舍入取整（float → int）
      v16 = 100.0 - (double)pThis_2F02 * 100.0 / v18;
      pThis_8302 = sub_432F40(v16);  // 结果 = 舍入取整（float → int）
    }
    else
    {
      pThis_8302 = 100 - *((uint32_t *)this + 2096);  // this+8384〔f_20C0〕
    }
    *((uint32_t *)this + 2098) = pThis_8302;  // this+8392〔f_20C8〕
    if ( pThis_2F0 != 0 )
    {
      v18 = *this;
      v11 = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v18) + 752))(this, 1);  // 虚函数调用 槽+752：音效地板适配判定 vmt2F0
      (*(void (/*thiscall*/ **)(float *, int))(LODWORD(v18) + 744))(this, v11 - pThis_2F0);  // 虚函数调用 槽+744：物件破坏三连（表现/掉落/广播）
      (*(void (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 2095) + 120))(*((uint32_t *)this + 2095));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    }
  }
  return sub_4AFB80(nArg22, nArg3, nArg4);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA6D0 sub_5DA6D0 —— 伤害百分比复位（+2098=100）后转调 ·sub_4AFC30 受击流程
// 与 ·0x5DA550 的 +2098 上限写入配对 —— 本函数为其满值复位路径
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA6D0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：伤害百分比复位（+2098=100）后转调 ·sub_4AFC30 受击流程
{
  *(this + 2098) = 100;  // this+8392〔f_20C8〕
  return sub_4AFC30(nArg2, nArg3, nArg4);  // 调 受击流程
}



// AI 字段访问（this+8584）
// ------------------------------------------------------------
// 0x5DA6F0 sub_5DA6F0 —— 受击联动（·sub_4D54E0 受击包后：+1639==10 主状态镜像 且 +1953==0/+1954==15
// 子相位 且 +8584 标志位时，以 dword_9B9344 弧度常量经 vt+272 触发转向/击退【推断】）
// ------------------------------------------------------------
char /*thiscall*/ sub_5DA6F0(uint32_t *this)  // 实现：受击联动（·sub_4D54E0 受击包后：+1639==10 主状态镜像 且 +1953==0/+1954==15
{
  int fld_e1953; // eax  | +0x1E84 → ★ 子状态 A（0x5DE690: +7812==0 分支）（CNMage；va=005DE690）
  float v4; // [esp+0h] [ebp-8h]

  LOBYTE(fld_e1953) = sub_4D54E0(this);  // 调 受击包后：+1639==10 主状态镜像 且 +1953==0/+1954==15
  if ( *(this + 1639) == 10 )  // 判定 “+6556 大状态ID”
  {
    fld_e1953 = *(this + 1953);  // this+7812〔nSubStateA(推断)〕
    if ( fld_e1953 == 0 && *(this + 1954) == 15 )  // this+7816〔nSubStateB(推断)〕
    {
      LOBYTE(fld_e1953) = *((uint8_t *)this + 8584);  // this+8584 0x5DE690: !=0 判据字节
      if ( (uint8_t)fld_e1953 != 0 )
      {
        v4 = (double)dword_9B9344 * 0.017444445;  // ×0.01744f（角度转弧度，π/180）
        LOBYTE(fld_e1953) = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 272))(this, 1, LODWORD(v4));  // 虚调用 vt+272
      }
    }
  }
  return fld_e1953;  // | +0x1E84 → ★ 子状态 A（0x5DE690: +7812==0 分支）（CNMage；va=005DE690）
}



// 数据表读数（sub_47EF20, 41L）
// ------------------------------------------------------------
// 0x5DA740 sub_5DA740 —— 伤害数值闸（·sub_4AFBF0 受击过滤；结果!=3 时）
// this+2095 存活 → 伤害钳位到 this+2098 百分比上限；this+2142!=-1 且主状态镜像 +1639 为 0/11 时
// 经 vt+1140 取表 38 参数、vt+1160 恢复、·sub_47EF20 查表加权（+1000 基准）后改写伤害
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA740(int *this, int *pDwArg2, int nArg3)  // 实现：伤害数值闸（·sub_4AFBF0 受击过滤；结果!=3 时）
{
  int result; // eax
  int v5; // ebx
  int fld_e2095; // eax
  int fld_e2098; // eax
  int fld_e1639; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  int v9; // [esp-Ch] [ebp-18h]

  result = sub_4AFBF0(pDwArg2, nArg3);  // 调 受击过滤
  v5 = result;
  if ( result != 3 )
  {
    fld_e2095 = *(this + 2095);  // this+8380〔pAnimC〕
    if ( fld_e2095 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2095 + 80))() != 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    {
      fld_e2098 = *pDwArg2;
      if ( *pDwArg2 >= *(this + 2098) )  // this+8392〔f_20C8〕
        fld_e2098 = *(this + 2098);  // this+8392〔f_20C8〕
      *pDwArg2 = fld_e2098;
    }
    if ( *(this + 2142) != -1 )  // this+8568〔nPhaseGroupIdx〕
    {
      fld_e1639 = *(this + 1639);  // 读 fld_e1639 = this+6556（大状态ID）
      if ( fld_e1639 == 0 || fld_e1639 == 11 )  // 若 fld_e1639 == 0 与/或 fld_e1639 == 11
      {
        v9 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 38, -1);  // 结果 = 虚调用 vt+1140
        (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);  // 虚调用 vt+1160
        *pDwArg2 = (sub_47EF20(38, 1, v9, -1, 11) + 1000) * *pDwArg2 / 1000;  // 调 读攻击数据表
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
int /*userpurge*/ sub_5DA7F0@<eax>(uint8_t *pArg1@<ecx>, char pszArg2@<bl>, char pszArg3)  // 实现：受击事件链（vt+308 存活门；+7730 标志决定 pszArg3 是否生效）
{
  int result; // eax
  char pszArg32; // bl
  int v6; // eax
  bool v7; // al
  char v9; // [esp-4h] [ebp-8h]

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1);  // 虚函数调用 槽+308
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
    v6 = sub_4AFD50(pszArg3);  // 调 过滤 → vt+1140 查 32 号表项 >0 判定 → vt+1160 写 1
    LOBYTE(v6) = pszArg32 != 0 && (v6 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 32)) > 0;  // 虚函数调用 槽+1140
    (*(void (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 11, v6);  // 虚函数调用 槽+1160
    sub_47E440(pszArg2);
    if ( pszArg32 != 0 )
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 33);  // 虚函数调用 槽+1140
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 1160))(pArg1);  // 虚函数调用 槽+1160
    sub_47E440(14);
    v7 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 34) > 0;  // 虚函数调用 槽+1140
    v9 = v7;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 12);  // 虚函数调用 槽+1160
    return sub_47E440(v9);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA8D0 sub_5DA8D0 —— 存活查询透传（vt+308）
// 供受击包族（·0x5DA7F0/·0x5DA9E0 等）统一走 vftable 存活门，避免直接判对象指针
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA8D0(void *this)  // 函数定义: 存活查询透传（vt+308）
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);  // 虚函数调用 槽+308
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA8E0 sub_5DA8E0 —— 集合移除回调（·sub_4B0530 后：uArg2==this+2110 槽则清槽；
// uArg2==this 自身移除时经 vt+216 自毁通知 11）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA8E0(uint32_t *this, uint32_t *uArg2)  // 实现：集合移除回调（·sub_4B0530 后：uArg2==this+2110 槽则清槽；
{
  int result; // eax

  result = sub_4B0530(uArg2);  // 结果 = 目标引用解除（清 +7888 缓存）
  if ( uArg2 == (uint32_t *)*(this + 2110) )
    *(this + 2110) = 0;
  if ( uArg2 == this )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);  // 虚调用 vt+216
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DA920 sub_5DA920 —— 主状态→组号映射（6/7/8/9 → 0/1/2/3，其余归 4）
// 与 ·0x5DA1E0 的 dword_738048 表映射互为印证（两条索引→组号路径）
// ------------------------------------------------------------
int /*stdcall*/ sub_5DA920(int nArg1)  // 函数定义: 存 主状态→组号映射
{
  int result; // eax

  switch ( nArg1 )  // 按 nArg1 分派
  {
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      result = 0;
      break;
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      result = 1;
      break;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      result = 2;
      break;
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
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
int /*cdecl*/ sub_5DA980(int nArg1)  // 函数定义: 索引→表值查表（在 dword_738020 前 4 项中定位，命中返回 dword_738030 同位项…
{
  int v1; // eax

  v1 = 0;
  while ( nArg1 != dword_738020[v1] )  // 当 nArg1 != dword_738020[v1] 循环
  {
    if ( ++v1 >= 4 )
      return -1;
  }
  return dword_738030[v1];  // 返回 取 dword_738030[v1]
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA9B0 sub_5DA9B0 —— 表包含查询（nArg1 在 unk_737FFC..dword_738020 区间表内返回 1）
// 与 ·0x5DA980 同表区（737FFC..738020，四项）—— 本函数只判包含不取值
// ------------------------------------------------------------
char /*stdcall*/ sub_5DA9B0(int nArg1)  // 函数定义: 表包含查询（nArg1 在 unk_737FFC..dword_738020 区间表内返回 1）
{
  uint32_t *v1; // eax

  v1 = &unk_737FFC;
  while ( nArg1 != *v1 )  // 当 nArg1 != *v1 循环
  {
    if ( (int)++v1 >= (int)dword_738020 )
      return 0;
  }
  return 1;  // 返回 1(成功)
}



// 时钟门+数据表 AI（sub_699000+sub_47EF20, 46L）
// ------------------------------------------------------------
// 0x5DA9E0 sub_5DA9E0 —— 相位组切换（pArg2 目标组；this+2062 对象存活门）
// 组变更且新组!=4 时：vt+1140 查 29 号表项 + vt+1160 恢复 → ·sub_47EF20 表 29 加权时延写
// this+2065+pArg2 到点槽；·sub_4926A0 帧游标复位选帧（2087/2082 组、组 2 时补 2091/2086）；
// this+2063 记组号；this+2*pArg2+2069 起 2 项帧游标复位
// ------------------------------------------------------------
void /*thiscall*/ sub_5DA9E0(int *this, int pArg2)  // 函数定义: 相位组切换（pArg2 目标组；this+2062 对象存活门）
{
  int fld_e2062; // ecx
  int fld_e2063; // eax
  int v5; // ebx
  int pThis_9; // eax
  int v7; // ecx
  int *pThis_2; // esi
  int i; // edi
  int v10; // [esp-14h] [ebp-18h]

  fld_e2062 = *(this + 2062);  // this+8248〔nVariantVal〕
  if ( fld_e2062 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2062 + 80))(fld_e2062) != 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
  {
    fld_e2063 = *(this + 2063);  // this+8252〔nParam2〕
    if ( fld_e2063 != pArg2 )
    {
      if ( fld_e2063 != 4 )
      {
        v10 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 29, -1);  // 结果 = 虚调用 vt+1140
        (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);  // 虚调用 vt+1160
        v5 = sub_47EF20(29, 1, v10, -1, 11);  // 调 读攻击数据表
        pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
        v7 = *(this + pArg2 + 2087);
        *(this + pArg2 + 2065) = v5 + pThis_9;
        sub_4926A0(v7);  // 帧游标复位（+44 帧数组；递归子链 +204）
        sub_4926A0(*(this + pArg2 + 2082));  // 帧游标复位（+44 帧数组；递归子链 +204）
        if ( pArg2 == 2 )
        {
          sub_4926A0(*(this + 2091));  // 帧游标复位（+44 帧数组；递归子链 +204）
          sub_4926A0(*(this + 2086));  // 帧游标复位（+44 帧数组；递归子链 +204）
        }
      }
      *(this + 2063) = pArg2;  // this+8252〔nParam2〕
      pThis_2 = this + 2 * pArg2 + 2069;
      for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
        sub_4926A0(*pThis_2++);  // 帧游标复位（+44 帧数组；递归子链 +204）
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
int /*thiscall*/ sub_5DAAC0(int *this, char pszArg2, int nArg3, int nArg4, int nArg5)  // 函数定义: 播放驱动（帧数组批播 + 表偏移定位）
{
  int result; // eax
  int i; // edi
  int j; // ebx
  int v9; // edi
  int v10; // edi
  int v11; // eax
  int v12; // [esp+4h] [ebp-4h]

  result = *(this + 2062);  // this+8248〔nVariantVal〕
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = (*(int (**)(void))(*(uint32_t *)result + 80))();  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    if ( (uint8_t)result != 0 )
    {
      if ( pszArg2 != 0 && *(this + 2063) != 4 )  // this+8252〔nParam2〕
      {
        for ( i = 0; i < 2; ++i )  // 循环：i 从 0 递增到 2
        {
          sub_4938F0(*(this + 2 * *(this + 2063) + i + 2069));  // 调 调 sub_4938F0
          sub_491D00(dword_79C0B0, nArg3, nArg4 - *(this + 40), 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        }
      }
      for ( j = 0; j < 5; ++j )  // 循环：j 从 0 递增到 5
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
                v11 = sub_491C70(v10, 3);  // 调 帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
                sub_493A60(v10, v11);  // 时间推进包装（累计 +32；+212 同步源优先）
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
        sub_4938F0(v10);  // 调 调 sub_4938F0
        result = sub_491D00(dword_79C0B0, nArg3 + dword_737FD4[v12], nArg4 + dword_737FE4[v12], 0.0);  // 结果 = 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
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
void /*usercall*/ sub_5DAC20(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 函数定义: 倒计时槽计数广播（this+2062 存活门）
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
  if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 80))(pObj) != 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
  {
    v5 = 0;
    v6 = pDwArg1 + 2065;
    for ( i = 4; i != 0; --i )  // 循环：i 从 4 递减到 0
    {
      if ( *v6 != -1 && sub_699000((int)(pDwArg1 + 9)) < *v6 )  // 【clock_now(clk)】
        ++v5;
      ++v6;
    }
    if ( v5 != pDwArg1[2064] )
    {
      pObj2 = pDwArg1[2062];
      pDwArg1[2064] = v5;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 124))(pObj2);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      if ( v5 != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 1140))(pDwArg1, 29, -1);  // 结果 = 虚调用 vt+1140
        (*(void (/*thiscall*/ **)(int *, int, int, int))(*pDwArg1 + 1160))(pDwArg1, 29, v5 + 1, v8);  // 虚调用 vt+1160
        v9 = sub_47EF20(-1, 11, nArg3, nArg2, v12);  // 调 读攻击数据表
        v13 = (float)v9;
        (*(void (/*cdecl*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pDwArg1[2062] + 120))(1, 0, LODWORD(v13), v9);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
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
void /*usercall*/ sub_5DACE0(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 函数定义: 换锚重定
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
    if ( v3 == 0 || v3 == 11 )  // 若 v3 == 0 与/或 v3 == 11
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1140))(pArg1);  // 结果 = 虚调用 vt+1140
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*pArg1 + 1160))(pArg1, 38, 0, v4);  // 虚调用 vt+1160
      v5 = sub_47EF20(38, -1, -1, 11, nArg2);  // 调 读攻击数据表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*pArg1 + 888))(pArg1, 0, 0, v5 * pArg1[1663] / 1000);  // 虚调用 vt+888
      v6 = pArg1[2142];
      if ( v6 >= 55 )
        v7 = 4;
      else
        v7 = dword_738048[v6];
      v8 = &pArg1[2 * v7 + 2043];
      for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
      {
        sub_493D00(*(v8 - 10), 100.0);  // 调 变速
        sub_493D00(*v8++, 100.0);  // 调 变速
      }
    }
  }
}



// AI 字段访问（this+8628）
// ------------------------------------------------------------
// 0x5DADE0 sub_5DADE0 —— 死亡/移除锚定（vt+216 事件 11 + +8628 帧索引清零 + vt+212 播报 nArg2；
// +2148 时刻槽取 dword_79D100 时钟快照 —— 与 ·0x5DA490 的 -1 复位及后续到点比较配对）【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DADE0(uint8_t *this, int nArg2)  // 函数定义: 死亡/移除锚定
{
  int v3; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 11);  // this+216 【推断】子链标志字节
  v3 = *(uint32_t *)this;
  *(this + 8628) = 0;  // this+8628 【推断】指挥计时戳
  result = (*(int (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t))(v3 + 212))(this, nArg2, 11, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
  *((uint32_t *)this + 2148) = dword_79D100[0];  // 16 条时间域累计 tick
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DAE20 sub_5DAE20 —— 内联尾插（this[0]=容量上限、this[1]=基址、this[2]=游标；越界转·off_77F3FC 断言）
// ·被 0x5E1000 / aura_create / passive_object 直接喂 dword_9B9344 等 AI 相位槽值【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DAE20(int *this, int nArg2)  // 函数定义: 内联尾插
{
  int fld_e2; // esi
  int v3; // ecx
  int result; // eax

  *(uint32_t *)(*(this + 1) + *(this + 2)) = nArg2;  // this+4〔宿主对象〕等 2 字段
  fld_e2 = *(this + 2) + 4;  // this+8〔nSkillRec8(推断)〕
  *(this + 2) = fld_e2;  // 写 this+8 = fld_e2（技能槽记录首字）
  v3 = *this;
  result = fld_e2;
  if ( fld_e2 > v3 )
    return off_77F3FC(aCriticalError_40, v3);  // 读 off_77F3FC（引擎日志输出函数）
  return result;
}



// 追击弹发射：CHASER_LAUNCH 播报（14L）
// ------------------------------------------------------------
// 0x5DAE60 sub_5DAE60 —— 追击弹发射相位同步：·sub_4AFDB0 基类发射后，索引 <55 且组号非 4 时·sub_5DA9E0 切相位组
// ·弹种 39 追加 vt+212 播报 CHASER_LAUNCH（dword_738048 为索引→组号表，55 为表长门）
// ------------------------------------------------------------
void /*thiscall*/ sub_5DAE60(int *this, int nArg2, int nArg3)  // 实现：追击弹发射相位同步：·sub_4AFDB0 基类发射后，索引 <55 且组号非 4 时·sub_5DA9E0 切相位组
{
  sub_4AFDB0((uint8_t **)this, nArg2, nArg3);  // 调 基类发射后
  if ( nArg2 < 55 && dword_738048[nArg2] != 4 )
    sub_5DA9E0(this, dword_738048[nArg2]);  // 相位组切换（pArg2 目标组；this+2062 对象存活门）
  if ( nArg2 == 39 )
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "CHASER_LAUNCH", -1, 0, 0);  // 字符串 “CHASER_LAUNCH”
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DAEB0 sub_5DAEB0 —— 双驱动择序派发：nArg2 非 0 先·sub_4B1E50 外观渲染主驱动再·sub_5DAAC0 帧数组批播
// ·nArg2 为 0 时反序（先批播后渲染）【推断：两套表现管线的顺序门】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DAEB0(int *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：双驱动择序派发：nArg2 非 0 先·sub_4B1E50 外观渲染主驱动再·sub_5DAAC0 帧数组批播
{
  if ( (uint8_t)nArg2 != 0 )
  {
    sub_4B1E50(nArg2, nArg3, nArg4, nArg5);  // 调 外观渲染主驱动（帧推进 sub_4938F0、+52/+56 槽、sub_424760 提交、sub_42FDA0…
    return sub_5DAAC0(this, nArg2, nArg3, nArg4, nArg5);  // 播放驱动（帧数组批播 + 表偏移定位）
  }
  else
  {
    sub_5DAAC0(this, 0, nArg3, nArg4, nArg5);  // 播放驱动（帧数组批播 + 表偏移定位）
    return sub_4B1E50(0, nArg3, nArg4, nArg5);  // 调 外观渲染主驱动（帧推进 sub_4938F0、+52/+56 槽、sub_424760 提交、sub_42FDA0…
  }
}



// AI 字段访问（this+8628）
// ------------------------------------------------------------
// 0x5DAF10 sub_5DAF10 —— 延时播报到点触发：this+8596 时刻槽非 -1 且 dword_79D100 时钟已到，先判 this+8628 忙位 vt+216(this,11) 解忙
// ·再以 this+8624<0x10 判 SSO 取 +8604 文案串交 vt+212 播报，末尾时刻槽复位 -1（与·0x5DADE0/·0x5DBBD0 三点配对）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DAF10(int *this)  // 函数定义: 延时播报到点触发：this+8596 时刻槽非 -1 且 dword_79D100 时钟已到…
{
  int result; // eax
  uint32_t *pThis_867; // eax

  result = *(this + 2149);  // this+8596〔bTargetState〕
  if ( result != -1 && dword_79D100[0] >= result )  // 16 条时间域累计 tick
  {
    if ( *((uint8_t *)this + 8628) != 0 )  // this+8628 【推断】指挥计时戳
      (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 11);  // 虚调用 vt+216
    if ( (unsigned int)*(this + 2156) < 0x10 )  // this+8624〔uAI8624(推断)〕
      pThis_867 = this + 2151;
    else
      pThis_867 = (uint32_t *)*(this + 2151);  // this+8604〔bAI8604(推断)〕
    result = (*(int (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_867, -1, 0, 0);  // 结果 = 虚调用 vt+212
    *(this + 2149) = -1;  // this+8596〔bTargetState〕
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DAF70 sub_5DAF70 —— 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推得，尾段整体后移一格
// ·仅被·0x5DBCD0/·0x5DBEB0 的插入分支调用【推断：MSVC vector 插入内联残留】
// ------------------------------------------------------------
void */*cdecl*/ sub_5DAF70(void *Src, int nArg2, int nArg3)  // 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推
{
  return memcpy_0((void *)(nArg3 - 4 * ((nArg2 - (int)Src) >> 2)), Src, 4 * ((nArg2 - (int)Src) >> 2));  // 返回 调 memcpy_0
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DAFA0 sub_5DAFA0 —— CNWhipped 构造（鞭挞效果）：基类·sub_4B1030 → 置 CNWhipped vftable → ·sub_64D880 装资源
// ··sub_64DC00 注入鞭挞参数；被·0x5DE100 以 new(0x70)+弹种 20 实例化
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DAFA0(uint32_t *this, char pszArg2, int nArg3)  // CNWhipped 构造（鞭挞效果）：基类·sub_4B1030 → 置 CNWhipped
{
  sub_4B1030();  // IRDAppendage 基类构造
  *this = &CNWhipped::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_64D880(this);  // 鞭挞数据
  sub_64DC00((int)this, pszArg2, nArg3);  // 鞭挞数据 4（47E720/47EF20/47E9D0）
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB000 sub_5DB000 —— CNWhipped 标量删除器（转调·sub_5DB030 析构，bit0 置位才 j__free）
// ·调用点由 vtable 槽 0 承担；本文件·0x5DAFA0 构造的 0x70 字节块配套释放【推断：vftable 未知】
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB000(void *Block, char pszArg2)  // CNWhipped 标量删除器（转调·sub_5DB030 析构，bit0 置位才 j__f
{
  sub_5DB030();  // CNWhipped 析构：先回置 CNWhipped vftable → ·sub_6509
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB030 sub_5DB030 —— CNWhipped 析构：先回置 CNWhipped vftable → ·sub_6509F0 释放资源 → 降为 IRDAppendage vftable
// ··sub_5F6640 基类析构，this+8 再置 nengine::IObject vftable、this+12 清零（三态析构链）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DB030(uint32_t *this)  // 实现：CNWhipped 析构：先回置 CNWhipped vftable → ·sub_6509F0 释放资源 → 降为 IRDAppendag…
{
  int result; // eax

  *this = &CNWhipped::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_6509F0();  // 释放 +108 挂接件（虚表首槽删除）
  *this = &IRDAppendage::`vftable';  // 写 vftable 指针（对象重定位/复位）
  result = sub_5F6640(this);  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // 写 this+8 = &nengine::IObject::`vftable’（技能槽记录首字）
  *((uint8_t *)this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB090 sub_5DB090 —— CNFollowMe 构造（召集跟随标）：基类·sub_4B1030 → 置 CNFollowMe vftable → ·sub_64D910 装资源
// ··sub_64D940 注入 nArg2；被·0x5DB260 以 new(0x7C)+vt+1140(this,30) 取参实例化
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DB090(uint32_t *this, int nArg2)  // CNFollowMe 构造（召集跟随标）：基类·sub_4B1030 → 置 CNFollo
{
  sub_4B1030();  // IRDAppendage 基类构造
  *this = &CNFollowMe::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_64D910(this);  // 鞭挞数据 2
  sub_64D940((int)this, nArg2);  // 鞭挞数据 3（47E720/47EF20）
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB0F0 sub_5DB0F0 —— CNFollowMe 标量删除器（转调·sub_5DB120 析构，bit0 置位才 j__free）
// ·与·0x5DB000/·0x5DB1D0 三者除析构目标不同外指令序列一致（同构删除器族）
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB0F0(void *Block, char pszArg2)  // CNFollowMe 标量删除器（转调·sub_5DB120 析构，bit0 置位才 j__
{
  sub_5DB120();  // CNFollowMe 析构：·sub_64E920 跟随受击收尾 → 回置 IRDAppen
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB120 sub_5DB120 —— CNFollowMe 析构：·sub_64E920 跟随受击收尾 → 回置 IRDAppendage vftable → ·sub_5F6640 基类析构
// ·this+8 置 nengine::IObject vftable、this+12 清零（与·0x5DB030 同构析构链）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DB120(uint32_t *this)  // 实现：CNFollowMe 析构：·sub_64E920 跟随受击收尾 → 回置 IRDAppendage vftable → ·sub_5F66…
{
  int result; // eax

  *this = &CNFollowMe::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_64E920();  // 跟随受击（42AF90/657740）
  *this = &IRDAppendage::`vftable';  // 写 vftable 指针（对象重定位/复位）
  result = sub_5F6640(this);  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // 写 this+8 = &nengine::IObject::`vftable’（技能槽记录首字）
  *((uint8_t *)this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB180 sub_5DB180 —— CNAuraShield 构造（光环护盾）：基类·sub_4B1030 → 置 CNAuraShield vftable
// ··sub_6509D0 基类装配 → ·sub_64ED00 装载 AuraShieldStart/Loop/End 三段光环资源
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DB180(uint32_t *this)  // CNAuraShield 构造（光环护盾）：基类·sub_4B1030 → 置 CNAura
{
  sub_4B1030();  // IRDAppendage 基类构造
  *this = &CNAuraShield::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_6509D0(this);  // 与 ·sub_6500E0 同构（差异：+80..+108 八字段全清）
  sub_64ED00(this);  // 装载 AuraShieldStart/Loop/End/Hit1/Hit2.ani（42FC
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB1D0 sub_5DB1D0 —— CNAuraShield 标量删除器（转调·sub_5DB200 析构，bit0 置位才 j__free）
// ·与·0x5DB000/·0x5DB0F0 同构（本组三挂件析构统一尾调·sub_5F6640）
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB1D0(void *Block, char pszArg2)  // CNAuraShield 标量删除器（转调·sub_5DB200 析构，bit0 置位才 j
{
  sub_5DB200();  // CNAuraShield 析构：·sub_64EE40 护盾受击收尾 → 回置 IRDApp
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB200 sub_5DB200 —— CNAuraShield 析构：·sub_64EE40 护盾受击收尾 → 回置 IRDAppendage vftable → ·sub_5F6640 基类析构
// ·this+8 置 nengine::IObject vftable、this+12 清零（与·0x5DB030/·0x5DB120 同构，仅末段收尾函数不同）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DB200(uint32_t *this)  // 实现：CNAuraShield 析构：·sub_64EE40 护盾受击收尾 → 回置 IRDAppendage vftable → ·sub_5F…
{
  int result; // eax

  *this = &CNAuraShield::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_64EE40();  // 护盾受击（42AF90/657740）
  *this = &IRDAppendage::`vftable';  // 写 vftable 指针（对象重定位/复位）
  result = sub_5F6640(this);  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // 写 this+8 = &nengine::IObject::`vftable’（技能槽记录首字）
  *((uint8_t *)this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB260 sub_5DB260 —— 召集标实例化：new(0x7C) 后取 vt+1140(this,30) 参数交·sub_5DB090 构造 CNFollowMe
// ·再 vt+56(v4, Block, this, 0, 0, 12, -1) 挂装到 Block 上（12 为挂点/类型参数）；仅由·0x5DB2E0 的三重门放行
// ------------------------------------------------------------
void /*thiscall*/ sub_5DB260(void *this, void *Block)  // 实现：召集标实例化：new(0x7C) 后取 vt+1140(this,30) 参数交·sub_5DB090 构造 CNFollowMe
{
  uint32_t *pMem; // edi
  uint32_t *v4; // eax
  int pThis_474; // eax

  if ( Block != nullptr )  // 若 Block 有效（非空）
  {
    pMem = operator new(0x7Cu);  // 堆分配 124 字节对象
    v4 = nullptr;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
    {
      pThis_474 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1140))(this, 30);  // 虚函数调用 槽+1140
      v4 = sub_5DB090(pMem, pThis_474);  // 结果 = CNFollowMe 构造（召集跟随标）：基类·sub_4B1030 → 置 CNFollo
    }
    (*(void (/*thiscall*/ **)(uint32_t *, void *, void *, uint32_t, uint32_t, int, int))(*v4 + 56))(  // 虚调用 vt+56
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
void /*thiscall*/ sub_5DB2E0(uint32_t *this, void *Block)  // 函数定义: 召集标挂装门：this+8372 挂件存活（vt+80）且 Block 经 vt+40 类型校验 ==529 且…
{
  int fld_e2093; // eax  | +0x20B4 → 0x5DE690 累加值（fld_20B4，写入前读取）（CNMage；va=005DE690）

  nullsub_1(Block);
  fld_e2093 = *(this + 2093);  // this+8372〔nDiffVal(推断)〕
  if ( fld_e2093 != 0
    && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2093 + 80))() != 0  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    && (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)Block + 40))(Block, 529) != 0  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    && *((uint32_t **)Block + 2088) == this )
  {
    sub_5DB260(this, Block);  // 召集标实例化：new(0x7C) 后取 vt+1140(this,30) 参数交·sub_5
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB330 sub_5DB330 —— 关联容器结点深拷贝（红黑树克隆）：先·sub_5648C0 分配并装配本结点
// ·再以 +21 哨兵色位判分支，递归拷贝 (*pDwArg2) 与 pDwArg2[2] 左右子树；v7[3] 存 this 供回填【推断：vftable 未知的泛型容器】
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB330(void **this, int *pDwArg2, int nArg3)  // 关联容器结点深拷贝（红黑树克隆）：先·sub_5648C0 分配并装配本结点
{
  char v3; // al
  uint32_t *fld_e1; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);  // 读 Block = this+4（宿主对象指针）
  v3 = *((uint8_t *)pDwArg2 + 21);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    fld_e1 = (uint32_t *)sub_5648C0(*(this + 1), nArg3, *(this + 1), pDwArg2 + 3, *((uint8_t *)pDwArg2 + 20));  // 结果 = 商店文本
    if ( *((uint8_t *)Block + 21) != 0 )
      Block = fld_e1;
    v6 = *pDwArg2;
    v10 = 0;
    *fld_e1 = sub_5DB330(v6, fld_e1);  // 结果 = 关联容器结点深拷贝（红黑树克隆）：先·sub_5648C0 分配并装配本结点
    fld_e1[2] = sub_5DB330(pDwArg2[2], fld_e1);  // 结果 = 关联容器结点深拷贝（红黑树克隆）：先·sub_5648C0 分配并装配本结点
  }
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB3E0 sub_5DB3E0 —— 全局偏位/相位常量表装载（无 this）：·sub_47E720/·sub_47E9D0 建 5 组表句柄
// ·dword_795850 与 dword_795854(=其*dword_7930D4[0]/100) 为攻方 X/Y 偏位（·0x5DCA10 作插值端点），
// ·dword_9B9338..9B9344 四槽供·0x5DE690/·0x5DE100 的距离与计时门；被 equ_buff 侧调用
// ------------------------------------------------------------
int sub_5DB3E0()  // 全局偏位/相位常量表装载（无 this）：·sub_47E720/·sub_47E9D0 建
{
  uint32_t *v0; // eax
  uint32_t *v1; // eax
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int result; // eax

  v0 = (uint32_t *)sub_47E720(3, 3);  // 调 调 sub_47E720
  dword_795850 = sub_47E9D0(v0, 1u);  // 调 收招/结束例程
  dword_795854 = dword_795850 * dword_7930D4[0] / 100;
  v1 = (uint32_t *)sub_47E720(3, 14);  // 调 调 sub_47E720
  dword_9B9338 = sub_47E9D0(v1, 0);  // 调 收招/结束例程
  v2 = (uint32_t *)sub_47E720(3, 14);  // 调 调 sub_47E720
  dword_9B933C = sub_47E9D0(v2, 1u);  // 调 收招/结束例程
  v3 = (uint32_t *)sub_47E720(3, 14);  // 调 调 sub_47E720
  dword_9B9340 = sub_47E9D0(v3, 2u);  // 调 收招/结束例程
  v4 = (uint32_t *)sub_47E720(3, 42);  // 调 调 sub_47E720
  result = sub_47E9D0(v4, 3u);  // 调 收招/结束例程
  dword_9B9344 = result;
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5DB490 sub_5DB490 —— 本体追击弹存在性查询：遍历 this[29] 碰撞对象表 RTTI cast 到 CNChaser
// ·命中条件 vt+688(obj)==2（弹种态）且 vt+684(obj)==this（回指本体）；被·0x5DB810/·0x5DE100/·0x5DE690 作三处前置门
// ------------------------------------------------------------
char /*thiscall*/ sub_5DB490(uint32_t *this)  // 函数定义: 追击弹在（DASH 弹存在）
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
  fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
  if ( fld_e29 == 0 )
    return 0;
  v4 = *(uint32_t *)(fld_e29 + 120);
  if ( v4 != 0 )
    v5 = (*(uint32_t *)(fld_e29 + 124) - v4) >> 2;  // 向量元素数 = (end−begin)/4
  else
    v5 = 0;
  v6 = 0;
  if ( v5 <= 0 )
    return 0;
  while ( 1 )  // 无限循环
  {
    v7 = pThis[29];
    v8 = *(uint32_t *)(v7 + 120);
    if ( v8 != 0 && v6 < (*(uint32_t *)(v7 + 124) - v8) >> 2 )  // 向量元素数 = (end−begin)/4
      v9 = *(uint32_t *)(v8 + 4 * v6);
    else
      v9 = 0;
    pObj2 = __RTDynamicCast(v9, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNChaser `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    pObj = pObj2;
    if ( pObj2 != 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 688))(pObj2) == 2  // 虚函数调用 槽+688：附加块基址 this+6160
      && (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 684))(pObj) == this )  // 虚函数调用 槽+684：属性块基址（this+6132，HP 读处）
    {
      break;
    }
    if ( (int)++v6 >= v5 )
      return 0;
    pThis = this;
  }
  return 1;  // 返回 1(成功)
}



// AI 相位辅助（65L）
// ------------------------------------------------------------
// 0x5DB550 sub_5DB550 —— 双锚位姿同步（v4=0/1 两挂点 this+8416 起步长 4）：vt+120/124/128 取本体坐标
// ·按 vt+152 朝向决定 X 加/减 nArg2，第二锚再补 ±30 错位；逐锚 vt+40(x,y,z) 写位置、vt+28 结点 +84 写朝向布尔、
// vt+92 取包交·sub_4600B0(fld,2,0,pkt) 广播（44/60 为·0x5DE690 case 0xA 传入的界面偏移量）
// ------------------------------------------------------------
void /*thiscall*/ sub_5DB550(uint32_t *this, int nArg2, int nArg3)  // 函数定义: 双锚位姿同步（v4=0/1 两挂点 this+8416 起步长 4）：vt+120/124/128 取本体坐标
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
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )  // 虚调用 vt+152
      v5 = nArg2 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
    else
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - nArg2;  // 结果 = 虚调用 vt+120
    v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
    v6 = nArg3 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
    v17 = v6;
    if ( v4 == 1 )
    {
      v5 += (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 ? -30 : 30;  // 虚调用 vt+152
      v6 = v17;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + v4 + 2104) + 40))(  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      *(this + v4 + 2104),
      v5,
      v16,
      v6);
    v7 = (int *)*(this + v4 + 2104);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 结果 = 虚调用 vt+152
    v9 = *v7;
    v18 = v8 == 0;
    v10 = (*(int (/*thiscall*/ **)(int *))(v9 + 28))(v7);  // 虚函数调用 槽+28：生成装配：Character/Mage/Effect/Animation/Fol…
    *(uint8_t *)(v10 + 84) = v18;
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + v4 + 2104) + 92))(*(this + v4 + 2104), v12);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
    v19 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v12);  // 调 演播层注册(槽号)
    v19 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
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
int /*thiscall*/ sub_5DB670(uint32_t *this, int nArg2, int nArg3)  // 函数定义: 攻击段号驱动的伤害系数改写：vt+308 存活 + this+8232 挂件门，vt+1160…
{
  int result; // eax
  int fld_e2058; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int pObj; // eax
  int v11; // [esp+4h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 结果 = 虚调用 vt+308
  if ( (uint8_t)result != 0 )
  {
    fld_e2058 = *(this + 2058);  // this+8232〔nGrabTable〕
    if ( fld_e2058 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2058 + 80))() != 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1160))(this);  // 结果 = 虚调用 vt+1160
      v11 = sub_41A5E0(14 * nArg3 + *(uint32_t *)(v6 + 348) - 14);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1140))(this);  // 结果 = 虚调用 vt+1140
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 1160))(this, 2, 1, v7);  // 虚调用 vt+1160
      v8 = sub_47EF20(2, -1, -1, 11, nArg2);  // 调 读攻击数据表
      sub_41A590(  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        14 * nArg3 + *(uint32_t *)(v6 + 348) - 14,
        (int)((uint64_t)(274877907LL * v11 * (1000 - v8)) >> 32) >> 6,
        v11 * (1000 - v8) / 1000);
      sub_579650(nArg2, nArg3);  // 【IRDCharacter__vmt510】
      return sub_41A590(14 * nArg3 + *(uint32_t *)(v6 + 348) - 14, v9, v11);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 结果 = 虚调用 vt+308
      if ( (uint8_t)result != 0 )
      {
        pObj = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, nArg2);  // 结果 = 虚调用 vt+1160
        return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, nArg3);  // 虚函数调用 槽+4：复位/锁定（64F690 + 64A790 +…
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
int */*thiscall*/ sub_5DB780(int this, int pArg2)  // 关联容器整体重建（红黑树复制）：先·sub_5DB330 克隆源树到 this+4 结点、t
{
  int fld_4; // edi
  int **fld_42; // edx
  int *result; // eax
  int *v6; // ecx
  int fld_43; // esi
  int **v8; // ecx

  fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
  *(uint32_t *)(fld_4 + 4) = sub_5DB330((void **)this, *(int **)(*(uint32_t *)(pArg2 + 4) + 4), fld_4);  // 关联容器结点深拷贝（红黑树克隆）：先·sub_5648C0 分配并装配本结点
  *(uint32_t *)(this + 8) = *(uint32_t *)(pArg2 + 8);  // 写 this+8 = *(uint32_t *)(pArg2 + 8)（技能槽记录首字）
  fld_42 = *(int ***)(this + 4);  // this+4 宿主对象
  result = fld_42[1];
  if ( *((uint8_t *)result + 21) != 0 )
  {
    *fld_42 = (int *)fld_42;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);  // 涉及字段 “+4 宿主对象指针”
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
    fld_43 = *(uint32_t *)(this + 4);  // 读 fld_43 = this+4（宿主对象指针）
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
char /*thiscall*/ sub_5DB810(uint32_t *this)  // 函数定义: 三层状态门总调度（vt+308 存活 + this+7730 字节 + switch…
{
  int fld_e1639; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  int *v3; // edi

  LOBYTE(fld_e1639) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 虚调用 vt+308
  if ( (uint8_t)fld_e1639 != 0 )
  {
    sub_4AFEC0(this);
    if ( *(this + 2111) != -1  // this+8444〔nSkillGate(推断)〕
      && *(this + 2110) != 0
      && sub_699000((int)(this + 9)) < *(this + 2111)  // 【clock_now(clk)】
      && (uint8_t)sub_5DB490(this) != 0 )  // 本体追击弹存在性查询：遍历 this[29] 碰撞对象表 RTTI cast 到 CNCha
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 39);  // 虚调用 vt+1160
      sub_47E440(1);
    }
    LOBYTE(fld_e1639) = *((uint8_t *)this + 7730);  // this+7730 子类使能字节
    if ( (uint8_t)fld_e1639 != 0 )
    {
      fld_e1639 = *(this + 1639);  // 读 fld_e1639 = this+6556（大状态ID）
      switch ( fld_e1639 )  // 按 fld_e1639 分派
      {
        case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
          if ( *(this + 2142) == -1 )  // this+8568〔nPhaseGroupIdx〕
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 2);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 4);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 5);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 6);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 7);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 9);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 8);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 10);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 11);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 12);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 13);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 14);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 15);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 16);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 17);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 18);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 20);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 26);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 27);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 28);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 29);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 30);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 31);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 37);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 40);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 41);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 43);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 49);  // 虚调用 vt+1160
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 50);  // 虚调用 vt+1160
            sub_47E440(1);
            v3 = (int *)&unk_737FFC;
            do
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, *v3);  // 虚调用 vt+1160
              LOBYTE(fld_e1639) = sub_47E440(1);  // 调 取 16 位值低 8 位
              ++v3;
            }
            while ( (int)v3 < (int)&dword_738020 );
          }
          else
          {
            byte_9A0358 = 0;
            byte_9A0384 = 0;
            LOBYTE(fld_e1639) = sub_483DF0(0);  // 遍历技能槽对非空项调用 ·sub_47E440
          }
          break;
        case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        case 4:  // case 4 = ENUM_CMDPACKET_EXIT
          LOBYTE(fld_e1639) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 8);  // 虚调用 vt+776
          if ( (uint8_t)fld_e1639 == 0 )
          {
            LOBYTE(fld_e1639) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 16);  // 虚调用 vt+776
            if ( (uint8_t)fld_e1639 == 0 )
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 3);  // 虚调用 vt+1160
              LOBYTE(fld_e1639) = sub_47E440(1);  // 调 取 16 位值低 8 位
            }
          }
          break;
        case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
          fld_e1639 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 42);  // 结果 = 虚调用 vt+1140
          if ( fld_e1639 > 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 15);  // 虚调用 vt+1160
            LOBYTE(fld_e1639) = sub_47E440(1);  // 调 取 16 位值低 8 位
          }
          break;
        default:
          return fld_e1639;  // | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
      }
    }
  }
  return fld_e1639;  // | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
}


// 语音注册（sub_4015C0; this+8628）
// ------------------------------------------------------------
// 0x5DBBD0 sub_5DBBD0 —— 延时播报登记（this+8592 时刻槽非 -1 时生效）：dword_79D100 时钟未到 nArg3+起点则挂起
// ·this+8596 存到期时刻、sub_4015C0 拷贝 Src 文案、this+8628 置忙位 1；已到则立即 vt+216(this,11)+vt+212 播报；
// ·无论何种分支末尾 this+8592 复位 -1（与·0x5DADE0 清零、·0x5DAF10 到点触发构成三件套）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DBBD0(uint32_t *this, void *Src, int nArg3)  // 函数定义: 延时播报登记
{
  int result; // eax
  int v5; // eax

  result = *(this + 2148);  // this+8592〔复位〕
  if ( result != -1 )
  {
    v5 = nArg3 + result;
    if ( dword_79D100[0] < v5 )  // 16 条时间域累计 tick
    {
      *(this + 2149) = v5;  // this+8596〔bTargetState〕
      result = sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
      *((uint8_t *)this + 8628) = 1;  // this+8628 【推断】指挥计时戳
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);  // 虚调用 vt+216
      result = (*(int (/*thiscall*/ **)(uint32_t *, void *, int, uint32_t, uint32_t))(*this + 212))(this, Src, -1, 0, 0);  // 结果 = 虚调用 vt+212
    }
    *(this + 2148) = -1;  // this+8592〔复位〕
  }
  return result;
}



// 语音注册（sub_4015C0; STL 断言串为符号文本非资源）
// ------------------------------------------------------------
// 0x5DBC60 sub_5DBC60 —— std::vector 超长断言（noreturn）：构造 length_error 异常对象并 _CxxThrowException
// ·「vector<T> too long」仅 STL 诊断符号文本、非业务资源；由·0x5DBCD0 容量溢出分支转调【推断：MSVC 模板内联外提】
// ------------------------------------------------------------
void /*noreturn*/ sub_5DBC60()  // std::vector 超长断言（noreturn）：构造 length_error 异常对
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
  sub_401740(v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// AI 相位辅助（112L）
// ------------------------------------------------------------
// 0x5DBCD0 sub_5DBCD0 —— 指针表 insert_n（三分支自研实现，本工程 vector<T*> 语义）：尾插空间足则
// ··sub_55E7F0 尾段搬移 + ·sub_5DAF70 前段回填 + ·sub_49A9D0 收尾；空隙不足则·sub_523700 就地扩容；
// ·容量不足则 operator new(4*v10) 整块重建后搬移旧块并 j__free；异常路径转·0x5DBC60；被·0x5DC170 逐目标调用
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5DBCD0(int this, int Src, unsigned int uArg3, int *pDwArg4)  // 函数定义: 指针表 insert_n（三分支自研实现，本工程 vector<T*> 语义）：尾插空间足则
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

  fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;  // 涉及字段 “+12 技能槽记录次字”
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // 涉及字段 “+8 技能槽记录首字”
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_5DBC60(this);  // std::vector 超长断言（noreturn）：构造 length_error 异常对
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // 涉及字段 “+8 技能槽记录首字”
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(uint8_t **)(this + 8);  // this+8 物品 id
      v21 = (int)&fld_83[-Src] >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // 商城状态
        sub_5DAF70((void *)Src, v24, v29);  // 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // 商城状态
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // 调 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];  // 涉及字段 “+8 技能槽记录首字”
        *(uint32_t *)(this + 8) = fld_84;  // 写 this+8 = fld_84（技能槽记录首字）
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // 涉及字段 “+8 技能槽记录首字”
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( fld_4 != 0 )
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // 涉及字段 “+8 技能槽记录首字”
        else
          fld_86 = 0;
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);  // 涉及字段 “+4 宿主对象指针”
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+4 宿主对象
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // 调 填充补足尾段
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));  // 涉及字段 “+8 技能槽记录首字”
      fld_43 = *(uint32_t *)(this + 4);  // 读 fld_43 = this+4（宿主对象指针）
      if ( fld_43 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // 涉及字段 “+8 技能槽记录首字”
      else
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));  // this+4 宿主对象
      *(uint32_t *)(this + 12) = &pMem[v28];  // 写 this+12 = &pMem[v28]（技能槽记录次字）
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // 写 this+8 = &pMem[4 * v18]（技能槽记录首字）
      *(uint32_t *)(this + 4) = pMem;  // 写 this+4 = pMem（宿主对象指针）
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
unsigned int /*thiscall*/ sub_5DBEB0(int this, int Src, unsigned int uArg3, int *pDwArg4)  // 实现：与·0x5DBCD0 同构（指针表 insert_n 尾部单元素快路径）：唯一差异为容量溢出时转·sub_4DE680
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

  fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;  // 涉及字段 “+12 技能槽记录次字”
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // 涉及字段 “+8 技能槽记录首字”
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_4DE680(this);  // noreturn 异常抛出（”vector<T> too long”）
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // 涉及字段 “+8 技能槽记录首字”
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(uint8_t **)(this + 8);  // this+8 物品 id
      v21 = (int)&fld_83[-Src] >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // 商城状态
        sub_5DAF70((void *)Src, v24, v29);  // 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // 商城状态
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // 调 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];  // 涉及字段 “+8 技能槽记录首字”
        *(uint32_t *)(this + 8) = fld_84;  // 写 this+8 = fld_84（技能槽记录首字）
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // 涉及字段 “+8 技能槽记录首字”
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( fld_4 != 0 )
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // 涉及字段 “+8 技能槽记录首字”
        else
          fld_86 = 0;
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);  // 涉及字段 “+4 宿主对象指针”
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+4 宿主对象
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // 调 填充补足尾段
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));  // 涉及字段 “+8 技能槽记录首字”
      fld_43 = *(uint32_t *)(this + 4);  // 读 fld_43 = this+4（宿主对象指针）
      if ( fld_43 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // 涉及字段 “+8 技能槽记录首字”
      else
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));  // this+4 宿主对象
      *(uint32_t *)(this + 12) = &pMem[v28];  // 写 this+12 = &pMem[v28]（技能槽记录次字）
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // 写 this+8 = &pMem[4 * v18]（技能槽记录首字）
      *(uint32_t *)(this + 4) = pMem;  // 写 this+4 = pMem（宿主对象指针）
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
uint32_t */*thiscall*/ sub_5DC090(uint32_t *this, int nArg2)  // 关联容器初始化（红黑树头结点）：·sub_433AC0 分配哨兵结点头，+21 置 1（黑/
{
  int v3; // eax
  uint32_t v5[8]; // [esp+0h] [ebp-20h] BYREF

  v5[4] = v5;
  v5[3] = this;
  v3 = sub_433AC0(this);  // 结果 = map 节点分配（0x18）
  *(this + 1) = v3;  // this+4〔宿主对象〕
  *(uint8_t *)(v3 + 21) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);  // this+4〔宿主对象〕
  *(uint32_t *)*(this + 1) = *(this + 1);  // this+4〔宿主对象〕
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  v5[7] = 0;
  sub_5DB780((int)this, nArg2);  // 关联容器整体重建（红黑树复制）：先·sub_5DB330 克隆源树到 this+4 结点、t
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DC120 sub_5DC120 —— 与·0x5DC090 同构的转发封装（仅多一层返回 this），供·0x5DC780 目标切换时调用
// ·差异：·0x5DC090 直接构造，本函数经 vt+344 相位切换后被复用以重灌目标树【推断】
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DC120(uint32_t *this, int nArg2)  // 与·0x5DC090 同构的转发封装（仅多一层返回 this），供·0x5DC780 目标切
{
  sub_5DC090(this, nArg2);  // 关联容器初始化（红黑树头结点）：·sub_433AC0 分配哨兵结点头，+21 置 1（黑/
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DC140 sub_5DC140 —— 关联容器拷贝赋值：this 与 uArg2 不同则·sub_4A3610 释放旧树后·sub_5DB780 依源重建
// ·返回 this 支持链式；被·0x5DC780 在三处状态切换后刷新（this+540 处的相位树）
// ------------------------------------------------------------
uint32_t **/*thiscall*/ sub_5DC140(uint32_t **this, uint32_t **uArg2)  // 关联容器拷贝赋值：this 与 uArg2 不同则·sub_4A3610 释放旧树后·sub
{
  int v2; // edi

  v2 = (int)uArg2;
  if ( this != uArg2 )
  {
    sub_4A3610(&uArg2, **(this + 1), *(this + 1));  // 调 释放旧树后·sub
    sub_5DB780((int)this, v2);  // 关联容器整体重建（红黑树复制）：先·sub_5DB330 克隆源树到 this+4 结点、t
  }
  return this;  // 返回自身指针
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
int /*thiscall*/ sub_5DC170(uint32_t *this, int pArg2)  // 实现：本体所属追击弹收集器（唯一调用者链·0x5DC290/·0x5DC480/·0x5DCE00/·0x5DCF20）：
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
    if ( *(uint32_t *)(pArg2 + 4) != 0 )  // pArg2+4〔宿主对象〕
      j__free(*(void **)(pArg2 + 4));  // 调 堆释放
    *(uint32_t *)(pArg2 + 4) = 0;  // pArg2+4〔宿主对象〕
    *(uint32_t *)(pArg2 + 8) = 0;  // pArg2+8〔nSkillRec8(推断)〕
    *(uint32_t *)(pArg2 + 12) = 0;  // pArg2+12〔nSkillRec12(推断)〕
  }
  v5 = pThis[29];
  if ( v5 == 0 )
    return 0;
  v7 = *(uint32_t *)(v5 + 120);
  if ( v7 != 0 )
    v19 = (*(uint32_t *)(v5 + 124) - v7) >> 2;  // 向量元素数 = (end−begin)/4
  else
    v19 = 0;
  if ( v19 > 0 )
  {
    while ( 1 )  // 无限循环
    {
      v8 = pThis[29];
      v9 = *(uint32_t *)(v8 + 120);
      if ( v9 != 0 && v3 < (*(uint32_t *)(v8 + 124) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        v10 = *(uint32_t *)(v9 + 4 * v3);
      else
        v10 = 0;
      pObj = __RTDynamicCast(v10, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNChaser `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      v12 = (uint32_t *)pObj;
      pObj3 = pObj;
      if ( pObj != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 688))(pObj) == 2 )  // 虚函数调用 槽+688：附加块基址 this+6160
      {
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*v12 + 684))(v12);  // 结果 = 虚调用 vt+684
        if ( (uint32_t *)v13 == pThis2 )
        {
          if ( pArg2 != 0 )
          {
            pObj2 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
            if ( pObj2 != *(uint32_t *)(pArg2 + 8) )  // pArg2+8〔nSkillRec8(推断)〕
            {
              v15 = v12[251];
              do
              {
                if ( *(uint32_t *)(*(uint32_t *)pObj2 + 1004) >= v15 )
                  break;
                pObj2 += 4;
              }
              while ( pObj2 != *(uint32_t *)(pArg2 + 8) );  // pArg2+8〔nSkillRec8(推断)〕
            }
            sub_5DBCD0(pArg2, pObj2, 1u, &pObj3);  // 指针表 insert_n（三分支自研实现，本工程 vector<T*> 语义）：尾插空间足则
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
void /*thiscall*/ sub_5DC290(uint32_t *this)  // 实现：追击弹序号重排：·sub_5DC170 收集后按数组序回写 obj+1004（序号槽）
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
  sub_5DC170(this, (int)v6);  // 本体所属追击弹收集器（唯一调用者链·0x5DC290/·0x5DC480/·0x5DCE00
  v2 = v8;
  Block2 = Block;
  while ( Block2 != nullptr )  // 当 Block2 != nullptr 循环
  {
    if ( v1 >= (v2 - (int)Block2) >> 2 )
    {
      j__free(Block2);  // 调 堆释放
      return;
    }
    v4 = *((uint32_t *)Block2 + v1);
    v5 = *(uint32_t *)(v4 + 960) == 3;
    *(uint32_t *)(v4 + 1004) = v1;
    if ( !v5 )
      sub_617720(v4 + 984, v4 + 988, v4 + 992, v1);  // 追击珠环形轨迹参数（三输出）
    ++v1;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC330 sub_5DC330 —— 目标筛选与登记（this[29] 碰撞表遍历）：按 vt+40(obj,33) 类型门 + vt+348(obj) 档位 +20 == nArg4 匹配
// ·命中者交 vt+8(this,pObj,0) 求距离，<= nArg3/2 则记入 pObj2 并经·sub_45F8A0 登记；返回 nArg2 原样
// ·被 fighter_skills 的追加打击链调用【推断：nArg4 为攻击方档位、nArg3 为距离上界】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DC330(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数定义: 目标筛选与登记（this[29] 碰撞表遍历）：按 vt+40(obj,33) 类型门 + vt+348…
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
  fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
  v19 = 0;
  if ( fld_e29 != 0 )
  {
    v7 = *(uint32_t *)(fld_e29 + 120);
    v18 = v7 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v7) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    v17 = 0;
    if ( v18 > 0 )
    {
      do
      {
        fld_e292 = *(this + 29);  // 读 fld_e292 = this+116（观察者容器）
        v9 = *(uint32_t *)(fld_e292 + 120);
        if ( v9 != 0 && v4 < (*(uint32_t *)(fld_e292 + 124) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
          pObj = *(uint32_t *)(v9 + 4 * v4);
        else
          pObj = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 33) != 0  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
          && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj) + 20) == nArg4 )  // 虚函数调用 槽+348
        {
          pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj, 0);  // 结果 = 虚调用 vt+8
          if ( pObj2 <= nArg3 / 2 )
          {
            pObj2 = pObj;
            sub_45F8A0(Src, 1, (int)&pObj2);  // 对象指针表插入（内联 vector insert_n：搬移/填值/扩容三路）
            v4 = v17;
          }
        }
        v17 = ++v4;
      }
      while ( (int)v4 < v18 );
    }
  }
  sub_4982B0(v12);  // uint32 元素 vector 拷贝赋值（复用首指针）
  return nArg2;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC480 sub_5DC480 —— 追击弹发射（vt+308 存活门）：·sub_5DC170 收集现存弹，数量 < vt+1160(this,5) 表值·sub_47E9D0(vt,1) 才发射
// ·序号取末弹 +1004+1（pszArg3 非 0 再加 10000 偏置），经 vt+580(this, dword_737FB0[nArg2], 序号, ...) 发射调用；
// ·满额则经 dword_8F8528[7] + ·sub_422E70(1205) + ·sub_43BEE0 挂提示；nArg2 为 dword_737FB0 弹种表索引
// ------------------------------------------------------------
void /*thiscall*/ sub_5DC480(uint32_t *this, int nArg2, char pszArg3)  // 函数定义: 追击弹发射
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

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308
  {
    v4 = 0;
    Block = nullptr;
    v12 = 0;
    v13 = 0;
    v14 = 0;
    sub_5DC170(this, (int)v10);  // 本体所属追击弹收集器（唯一调用者链·0x5DC290/·0x5DC480/·0x5DCE00
    Block2 = Block;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      v4 = (v12 - (int)Block) >> 2;
    v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 5);  // 结果 = 虚调用 vt+1160
    if ( v4 < sub_47E9D0(v6, 1u) )  // 调 收招/结束例程
    {
      v9 = 0;
      if ( Block2 != nullptr && (v12 - (int)Block2) >> 2 != 0 )
        v9 = *(uint32_t *)(*(uint32_t *)(v12 - 4) + 1004) + 1;
      if ( pszArg3 != 0 )
        v9 += 10000;
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 虚调用 vt+580
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
      v7 = *((uint32_t **)dword_8F8528 + 7);  // 全局 dword_8F8528 = 消息/弹窗管理器
      v8 = sub_422E70(1205);  // 调 存 CStringManager::getStr 取本地化串
      sub_43BEE0(v7, v8, -6567706, 0, -1);  // 调 【播报上屏】
    }
    if ( Block2 != nullptr )  // 若 Block2 有效（非空）
      j__free(Block2);  // 调 堆释放
  }
}



// 数据表读数（sub_47EF20, 49L）
// ------------------------------------------------------------
// 0x5DC590 sub_5DC590 —— 追击弹发射概率门：vt+1160(this, this+8244) 取上限表、vt+1140 取当前并发数（<=1 归 1）
// ··sub_5DC170 计数 < ·sub_47E9D0(表,1) 时再判 vt+752(this) >= ·sub_47EA80(并发) 且 rand()%1000 < nArg2（千分概率）；
// ·通过则 vt+744 扣减差值、vt+1160(this,40,1,vt+1140) 登记、sub_47EF20(40,...) 取参后·sub_5DC480 发射（nRand 再判一次千分）
// ------------------------------------------------------------
void /*thiscall*/ sub_5DC590(int *this, int nArg2)  // 函数定义: 发射概率门
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

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308
  {
    sub_432FA0();  // srand 播种
    fld_e2061 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1160))(this, *(this + 2061));  // 结果 = 虚调用 vt+1160
    if ( (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 2061)) <= 1 )  // 虚调用 vt+1140
      fld_e20612 = 1;
    else
      fld_e20612 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 2061));  // 结果 = 虚调用 vt+1140
    v4 = sub_5DC170(this, 0);  // 结果 = 本体所属追击弹收集器（唯一调用者链·0x5DC290/·0x5DC480/·0x5DCE00
    if ( v4 < sub_47E9D0(fld_e2061, 1u) )  // 调 收招/结束例程
    {
      v5 = sub_47EA80(fld_e20612);
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 752))(this) >= v5 && rand() % 1000 < nArg2 )  // 虚调用 vt+752
      {
        v6 = *this;
        v7 = sub_47EA80(fld_e20612);
        v8 = (*(int (/*thiscall*/ **)(int *))(*this + 752))(this);  // 结果 = 虚调用 vt+752
        (*(void (/*thiscall*/ **)(int *, int))(v6 + 744))(this, v8 - v7);  // 虚函数调用 槽+744：物件破坏三连（表现/掉落/广播）
        v9 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);  // 结果 = 虚调用 vt+1140
        (*(void (/*thiscall*/ **)(int *, int, int, int))(*this + 1160))(this, 40, 1, v9);  // 虚调用 vt+1160
        v10 = sub_47EF20(40, -1, -1, 11, 1);  // 调 读攻击数据表
        nRand = rand() % 1000 < v10;  // 调 取伪随机数
        fld_e20613 = sub_5DA920(*(this + 2061));  // 结果 = 主状态→组号映射（6/7/8/9 → 0/1/2/3，其余归 4）
        sub_5DC480(v12, fld_e20613, nRand);  // 追击弹发射（vt+308 存活门）：·sub_5DC170 收集现存弹，数量 < vt+11
      }
    }
  }
}



// 数据表读数（sub_47EF20, 21L）
// ------------------------------------------------------------
// 0x5DC6D0 sub_5DC6D0 —— 发射概率外部入口：this+8240 挂件存活 + nArg3>0 + nArg2<=5 时
// ·vt+1140(this,40,-1) 取参交 sub_47EF20(40,4,参数,-1,11) 折算后转·sub_5DC590(this, v5) 走概率门
// ------------------------------------------------------------
void /*thiscall*/ sub_5DC6D0(int *this, int nArg2, int nArg3)  // 函数定义: 发射概率外部入口：this+8240 挂件存活 + nArg3>0 + nArg2<=5 时
{
  int fld_e2060; // eax
  int v5; // eax
  int v6; // [esp-Ch] [ebp-10h]

  fld_e2060 = *(this + 2060);  // this+8240〔nParamCnt〕
  if ( fld_e2060 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2060 + 80))() != 0 && nArg3 > 0 && nArg2 <= 5 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
  {
    v6 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 40, -1);  // 结果 = 虚调用 vt+1140
    (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);  // 虚调用 vt+1160
    v5 = sub_47EF20(40, 4, v6, -1, 11);  // 调 读攻击数据表
    sub_5DC590(this, v5);  // 追击弹发射概率门：vt+1160(this, this+8244) 取上限表、vt+1140
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC730 sub_5DC730 —— 指针表尾插快路径封装（this[1] 基址、this[2] 游标、this[3] 容量）：this[1]==0
// ·或游标已达容量时转·sub_5DBEB0 走扩容；否则就地写入 *pDwArg2 并游标 +1；被·0x5DD040 在收集结果后调用
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5DC730(int *this, int *pDwArg2)  // 函数定义: 登记到出口表
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 2;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 2 )  // 判定 “+12 技能槽记录次字”
    return sub_5DBEB0((int)this, *(this + 2), 1u, pDwArg2);  // 与·0x5DBCD0 同构（指针表 insert_n 尾部单元素快路径）：唯一差异为容量溢出
  fld_e22 = (int *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
  *fld_e22 = *pDwArg2;
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = result;  // 写 this+8 = result（技能槽记录首字）
  return result;
}



// AI 相位辅助（104L）
// ------------------------------------------------------------
// 0x5DC780 sub_5DC780 —— 敌方挂件相位切换（三段）：this+6556==8 攻击态且·sub_41A5E0(this+7028)==0 且 this+8216==-1 时
// ·以·sub_445870(37712398,10000)<100 的万分比触发，this+8224 置 9.0、vt+672(this,3) 与·sub_4AED60(9.0) 起效果；
// ·this+6556==20 军团态且 this+8516==20 时按·sub_4E4630 敌我关系在盟/敌分支置 this+8528 为 6/4/5 并·sub_5DC090/·sub_5DC120 切树，
// ·再 vt+344 定相位、th+139+152*相位 取偏移、sub_47EFD0 与·sub_4A3790 结算并写 this+388/396/397 三字段
// ------------------------------------------------------------
int /*thiscall*/ sub_5DC780(float *this, int nArg2, int nArg3, int nArg4)  // 实现：敌方挂件相位切换（三段）：this+6556==8 攻击态且·sub_41A5E0(this+7028)==0 且 this+8216==-…
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

  if ( *((uint32_t *)this + 1639) == 8 && sub_41A5E0(this + 1757) == 0 && *((uint32_t *)this + 2054) == -1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v25 = sub_445870(37712398, 10000);  // 结果 = 槽表随机数
    if ( (double)v25 < 100.0 )
    {
      v5 = *(uint32_t *)this;
      *(this + 2056) = 9.0;  // this+8224〔f_2020〕
      (*(void (/*thiscall*/ **)(float *, int))(v5 + 672))(this, 3);  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
      sub_4AED60(9.0);
    }
  }
  if ( *((uint32_t *)this + 1639) == 20 && *((uint32_t *)this + 2129) == 20 )  // this+1639 主状态镜像 2
  {
    if ( (uint8_t)sub_4E4630(nArg2) != 0 )  // 调 （上一表达式的参数/条件续行）
    {
      if ( *((uint32_t *)this + 2132) != 6 )
      {
        *((uint32_t *)this + 2132) = 6;
        sub_5DC090(this + 135);  // 关联容器初始化（红黑树头结点）：·sub_433AC0 分配哨兵结点头，+21 置 1（黑/
        v6 = *(uint32_t *)this;
        pThis_8B = *((uint32_t *)this + 139) + 152 * *((uint32_t *)this + 2132);  // this+556〔nGrabAnimBase〕
        v26 = 0;
        (*(void (/*thiscall*/ **)(float *, int))(v6 + 344))(this, pThis_8B);  // 虚函数调用 槽+344：交互槽（45E490/45E4D0/525CE0）
        sub_5DC140(v24);  // 关联容器拷贝赋值：this 与 uArg2 不同则·sub_4A3610 释放旧树后·sub
        pThis_488 = (char *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 1160))(this, 20);  // 虚函数调用 槽+1160
        pThis_474 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 1140))(this, 20);  // 虚函数调用 槽+1140
        pThis_184 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 388))(this);  // this+388 【推断】攻击上下文浮点值
        pThis_63 = sub_47EFD0(pThis_488, COERCE_FLOAT(8), pThis_474, pThis_184, pThis_184, 11) - 100 + *((uint32_t *)this + 99);  // this+396〔uReflectCtx(推断)〕
        v11 = *(uint32_t *)this;
        *((uint32_t *)this + 99) = pThis_63;  // 写 this+396 = pThis_63（技能参数索引）
        v12 = (*(int (/*thiscall*/ **)(float *))(v11 + 388))(this);  // 虚函数调用 槽+388：属性块（vt+672(3)）首 DWORD
        pThis_632 = 100 * sub_47EFD0(pThis_488, COERCE_FLOAT(9), pThis_474, v12, v12, 0) / (*((uint32_t *)this + 99) + 100);
        v14 = v24;
        *(this + 97) = (double)pThis_632 + *(this + 97);  // this+97 【推断】附加门字节
LABEL_16:
        v26 = -1;
        sub_4A3790(v14);
      }
    }
    else
    {
      v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      pThis_854 = *((uint32_t *)this + 2132);
      if ( v15 != 0 )
      {
        if ( pThis_854 != 4 )
        {
          *((uint32_t *)this + 2132) = 4;
          sub_5DC120(this + 135);  // 与·0x5DC090 同构的转发封装（仅多一层返回 this），供·0x5DC780 目标切
          v17 = *this;
          pThis_8B2 = *((uint32_t *)this + 139) + 152 * *((uint32_t *)this + 2132);  // this+556〔nGrabAnimBase〕
          v26 = 1;
          (*(void (/*thiscall*/ **)(float *, int))(LODWORD(v17) + 344))(this, pThis_8B2);  // 虚函数调用 槽+344：交互槽（45E490/45E4D0/525CE0）
          sub_5DC140(v24);  // 关联容器拷贝赋值：this 与 uArg2 不同则·sub_4A3610 释放旧树后·sub
          v14 = v24;
          goto LABEL_16;
        }
      }
      else if ( pThis_854 != 5 )
      {
        *((uint32_t *)this + 2132) = 5;
        sub_5DC120(this + 135);  // 与·0x5DC090 同构的转发封装（仅多一层返回 this），供·0x5DC780 目标切
        v18 = *this;
        pThis_8B3 = *((uint32_t *)this + 139) + 152 * *((uint32_t *)this + 2132);  // this+556〔nGrabAnimBase〕
        v26 = 2;
        (*(void (/*thiscall*/ **)(float *, int))(LODWORD(v18) + 344))(this, pThis_8B3);  // 虚函数调用 槽+344：交互槽（45E490/45E4D0/525CE0）
        sub_5DC140(v23);  // 关联容器拷贝赋值：this 与 uArg2 不同则·sub_4A3610 释放旧树后·sub
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
void /*userpurge*/ sub_5DCA10(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)  // 函数定义: 位移插值推进（this+6556 为 4/3 且 vt+724 静止门）：vt+776…
{
  int nPhaseState; // eax
  int nMissing; // eax
  int nDirCodeX; // ebx
  int nParam0; // eax
  int nFacing; // eax
  int nSelfX; // eax
  int nVt1; // edx
  int nSelfX2; // edi
  float fStartX; // eax
  float fEndX; // edi
  float fTmpY; // eax
  int nSelfX3; // eax
  int nVt2; // edx
  int nStartX; // edi
  int nSelfX4; // eax
  int nVt3; // edx
  int nDirCodeY; // ebx
  int nStep; // edi
  uint64_t nLerp; // rax
  int nSpan; // ebx
  uint64_t nLerp2; // rax
  int nYPos; // edi
  bool bStepOk; // cc
  uint32_t *pEntry3; // eax
  int nArg42; // [esp-10h] [ebp-50h]
  char v30; // [esp+0h] [ebp-40h]
  uint8_t v31[4]; // [esp+4h] [ebp-3Ch] BYREF
  void *Block; // [esp+8h] [ebp-38h]
  void *Src; // [esp+Ch] [ebp-34h]
  int nVecCap; // [esp+10h] [ebp-30h]
  int nTmpVar; // [esp+14h] [ebp-2Ch] BYREF
  float fYFrom; // [esp+18h] [ebp-28h]
  int nYFrom; // [esp+1Ch] [ebp-24h] BYREF
  int nXTo; // [esp+20h] [ebp-20h]
  float fYTo; // [esp+24h] [ebp-1Ch]
  int nYTo; // [esp+28h] [ebp-18h] BYREF
  float fXTo; // [esp+2Ch] [ebp-14h]
  float fYAdj; // [esp+30h] [ebp-10h]
  int nFreeState; // [esp+3Ch] [ebp-4h]

  nPhaseState = pArg1[1639];
  if ( nPhaseState != 4 && nPhaseState != 3 || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 724))(pArg1) != 0 )  // 主状态 4/3 且非静止
    return;
  nMissing = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 776))(pArg1, 8);  // 结果 = 虚调用 vt+776
  LOBYTE(nMissing) = (uint8_t)nMissing == 0 && (uint8_t)(nMissing = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 776))(pArg1, 16)) == 0;  // 8 与 16 段都缺则为1
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 1160))(pArg1, 3, nMissing);  // 虚调用 vt+1160
  sub_47E440(v30);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1312))(pArg1, 3) == 0 )  // 3 号反击门
    return;
  nDirCodeX = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, int))(*pArg1 + 1132))(pArg1, 0, nArg3, nArg2);  // 方向码X
  nParam0 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1132))(pArg1, 1);  // 方向码Y
  nYFrom = nParam0;
  if ( nDirCodeX == 4 && nParam0 == 4 )  // 双向码 4=朝目标：以朝向归一
  {
    nFacing = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 结果 = 虚调用 vt+152
    nDirCodeX = sub_432E50(nFacing);  // 结果 = 关系码对调映射
  }
  *(float *)&nSelfX = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));  // 虚调用 vt+120
  nVt1 = *pArg1;
  nSelfX2 = nSelfX;
  fXTo = *(float *)&nSelfX;
  fTmpY = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(nVt1 + 124))(pArg1));  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  fYAdj = fTmpY;
  if ( nDirCodeX != 0 )
  {
    if ( nDirCodeX != 1 )
      goto LABEL_17;
    LODWORD(fEndX) = dword_795850 + nSelfX2;  // 码1：X += 偏位
  }
  else
  {
    LODWORD(fEndX) = nSelfX2 - dword_795850;  // 码0：X -= 偏位
  }
  fXTo = fEndX;
LABEL_17:
  if ( nYFrom == 2 )
  {
    LODWORD(fTmpY) = LODWORD(fTmpY) - dword_795854;  // 码2：Y -= 偏位
LABEL_21:
    fYAdj = fTmpY;
    goto LABEL_22;
  }
  if ( nYFrom == 3 )
  {
    LODWORD(fTmpY) = dword_795854 + LODWORD(fTmpY);  // 码3：Y += 偏位
    goto LABEL_21;
  }
LABEL_22:
  nSelfX3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);  // 结果 = 虚调用 vt+120
  nVt2 = *pArg1;
  nStartX = nSelfX3;
  nXTo = nSelfX3;
  fYTo = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(nVt2 + 124))(pArg1));  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  nSelfX4 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);  // 结果 = 虚调用 vt+120
  nVt3 = *pArg1;
  nYFrom = nSelfX4;
  nYTo = (*(int (/*thiscall*/ **)(uint32_t *))(nVt3 + 124))(pArg1);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  if ( nDirCodeX == 4 )  // 码4：只沿 Y 插值（纯横向位移）
  {
    nSpan = abs32(LODWORD(fYTo) - LODWORD(fYAdj));  // 调 取 64 位值低 32 位
    nXTo = 0;
    if ( nSpan >= 0 )
    {
      fYAdj = (float)SLODWORD(fYAdj);  // 调 取 64 位值低 32 位(带符号)
      fYTo = (float)SLODWORD(fYTo);  // 调 取 64 位值低 32 位(带符号)
      do
      {
        nLerp = (uint64_t)sub_4049C0(fYTo, fYAdj, nXTo, nSpan);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        nYPos = nLerp;
        if ( (*(uint8_t (/*fastcall*/ **)(uint32_t *, uint32_t, float, uint32_t, uint32_t))(*pArg1 + 136))(  // 虚调用 vt+136
               pArg1,
               HIDWORD(nLerp),  // 调 取 64 位值高 32 位
               COERCE_FLOAT(LODWORD(fXTo)),  // 调 取 64 位值低 32 位
               nLerp,
               0) == 0 )  // 逐格碰撞试探
          break;
        bStepOk = nXTo + 1 <= nSpan;
        nYTo = nYPos;
        ++nXTo;
      }
      while ( bStepOk );
    }
  }
  else  // 其余码：XY 双轴同时插值
  {
    nStep = 0;
    nDirCodeY = abs32(nStartX - LODWORD(fXTo));  // 调 取 64 位值低 32 位
    if ( nDirCodeY >= 0 )
    {
      fXTo = (float)SLODWORD(fXTo);  // 调 取 64 位值低 32 位(带符号)
      fYFrom = (float)nXTo;
      fYAdj = (float)SLODWORD(fYAdj);  // 调 取 64 位值低 32 位(带符号)
      fYTo = (float)SLODWORD(fYTo);  // 调 取 64 位值低 32 位(带符号)
      do
      {
        nXTo = (uint64_t)sub_4049C0(fYFrom, fXTo, nStep, nDirCodeY);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        nLerp2 = (uint64_t)sub_4049C0(fYTo, fYAdj, nStep, nDirCodeY);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        HIDWORD(nLerp2) = *pArg1;  // 调 取 64 位值高 32 位
        nTmpVar = nLerp2;
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(HIDWORD(nLerp2) + 136))(pArg1, nXTo, nLerp2, 0) == 0 )  // 虚函数调用 槽+136：槽（10 行）
          break;
        ++nStep;
        nYFrom = nXTo;
        nYTo = nTmpVar;
      }
      while ( nStep <= nDirCodeY );
    }
  }
  Block = nullptr;
  Src = nullptr;
  nVecCap = 0;
  nFreeState = 0;
  nTmpVar = 3;  // 相位包参数头：3
  sub_430C80(nullptr, 1, (int)&nTmpVar);  // uint32 vector 区间插入（同值填充）
  sub_430C80(nullptr, 1, (int)&nYFrom);  // 起点
  sub_430C80(nullptr, 1, (int)&nYTo);  // 终点
  pEntry3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1160))(pArg1, 3);  // 3 号数据表
  nTmpVar = sub_47E9D0(pEntry3, 0);  // 调 收招/结束例程
  sub_430C80(nullptr, 1, (int)&nTmpVar);  // uint32 vector 区间插入（同值填充）
  nArg42 = nArg4;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1160))(pArg1, 3);  // 虚调用 vt+1160
  nTmpVar = sub_47EF20(0, nArg42, -1, -1, 11);  // 调 读攻击数据表
  sub_430C80(nullptr, 1, (int)&nTmpVar);  // uint32 vector 区间插入（同值填充）
  sub_430C80(nullptr, 1, (int)&nArg4);  // uint32 vector 区间插入（同值填充）
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *))(*pArg1 + 560))(pArg1, 17, v31);  // 提交相位 17
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 堆释放
}


// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5DCE00 sub_5DCE00 —— 追击弹命中播报：nArg2 非 0 时·sub_5DC170 收集现存弹，取首弹 obj+980（弹种索引）查 off_79583C 文案表
// ·交 vt+212 播报，再判该弹 vt+308 存活后以 sub_431230 三次打包（vt+48/vt+52 坐标 + 常量 400）经 vt+560(弹,3,包,0,0) 下发相位
// ------------------------------------------------------------
void /*thiscall*/ sub_5DCE00(uint32_t *this, int nArg2)  // 实现：追击弹命中播报：nArg2 非 0 时·sub_5DC170 收集现存弹，取首弹 obj+980（弹种索引）查 off_79583C 文案表
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
    sub_5DC170(this, (int)v5);  // 本体所属追击弹收集器（唯一调用者链·0x5DC290/·0x5DC480/·0x5DCE00
    pObj22 = pObj2;
    if ( pObj2 != nullptr )  // 若 pObj2 有效（非空）
    {
      if ( (v7 - (int)pObj2) >> 2 != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, char *, int, uint32_t, uint32_t))(*pThis + 212))(  // 虚调用 vt+212
          pThis,
          off_79583C[*(uint32_t *)(*(uint32_t *)pObj2 + 980)],
          -1,
          0,
          0);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pObj22 + 308))(*pObj22) != 0 )  // 虚调用 vt+308
        {
          Block = nullptr;
          v11 = 0;
          v12 = 0;
          v4 = *(uint32_t *)pObj;
          LOBYTE(v14) = 1;  // 调 取 16 位值低 8 位
          nArg2 = (*(int (/*thiscall*/ **)(int))(v4 + 48))(pObj);  // 虚函数调用 槽+48：更新槽（64A5A0 + 41C5E0/52E4D0）
          sub_431230((int)v9, &nArg2);  // uint32 vector push_back
          nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 虚函数调用 槽+52：播 AURA_SHIELD_LOOP（第二挂点，15 行）
          sub_431230((int)v9, &nArg2);  // uint32 vector push_back
          nArg2 = 400;
          sub_431230((int)v9, &nArg2);  // uint32 vector push_back
          (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)*pObj22 + 560))(*pObj22, 3, v9, 0, 0);  // 虚调用 vt+560
          if ( Block != nullptr )  // 若 Block 有效（非空）
            j__free(Block);  // 调 堆释放
          Block = nullptr;
          v11 = 0;
          v12 = 0;
        }
      }
      j__free(pObj22);  // 调 堆释放
    }
  }
}



// 追击弹爆炸：CHASER_EXPLOSION 播报（81L）
// ------------------------------------------------------------
// 0x5DCF20 sub_5DCF20 —— 追击弹爆炸总清理：·sub_5DC170 收集后逐弹（vt+308 存活者）以 sub_430C80 登记 v4 偏移
// ·（步长 +80）再 vt+560(弹,4,包,0,0) 触发第 4 相位；全部处理完 vt+212 播报 CHASER_EXPLOSION 并统一 j__free 释放收集块
// ------------------------------------------------------------
void /*thiscall*/ sub_5DCF20(uint32_t *this)  // 函数定义: 追击弹爆炸总清理：
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
  sub_5DC170(this, (int)v6);  // 本体所属追击弹收集器（唯一调用者链·0x5DC290/·0x5DC480/·0x5DCE00
  Block2 = Block;
  if ( Block != nullptr )  // 若 Block 有效（非空）
  {
    v2 = (v8 - (int)Block) >> 2;
    v15 = v2;
    if ( v2 != 0 )
    {
      v3 = 0;
      v17 = 0;
      v4 = 0;
      while ( v3 < v2 )  // 当 v3 < v2 循环
      {
        pObj = Block2[v3];
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )  // 虚函数调用 槽+308
        {
          v11 = nullptr;
          v12 = 0;
          v13 = 0;
          LOBYTE(v18) = 1;  // 调 取 16 位值低 8 位
          v16 = v4;
          sub_430C80(nullptr, 1, (int)&v16);  // uint32 vector 区间插入（同值填充）
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pObj + 560))(pObj, 4, v10, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
          LOBYTE(v18) = 0;  // 调 取 16 位值低 8 位
          if ( v11 != nullptr )  // 若 v11 有效（非空）
            j__free(v11);  // 调 堆释放
          v11 = nullptr;
          v12 = 0;
          v13 = 0;
        }
        Block2 = Block;
        v2 = v15;
        v3 = ++v17;
        v4 += 80;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pThis + 212))(  // 虚调用 vt+212
        pThis,
        "CHASER_EXPLOSION",  // 字符串 “CHASER_EXPLOSION”
        -1,
        0,
        0);
      j__free(Block2);  // 调 堆释放
    }
    else
    {
      j__free(Block);  // 调 堆释放
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
int /*thiscall*/ sub_5DD040(uint32_t *this, int nArg2, int pArg3, char pszArg4)  // 函数定义: 召唤物/弹体筛选收集（this[29] 碰撞表）：先按 pArg3 清空出口表…
{
  uint32_t *pThis; // esi
  int fld_e29; // eax
  unsigned int nIdx; // ebx
  int *pTableIt; // eax
  int nCollList; // eax
  int nCollBegin; // ecx
  int nCollHead; // eax
  int nCollList2; // ecx
  int nCollBegin2; // edx
  int pCollItem; // eax
  uint32_t *pMon; // eax
  uint32_t *pMon2; // edi
  int nCode; // ecx
  int nCollList3; // ecx
  int nCollBegin3; // edx
  int pCollItem2; // eax
  int pSummon; // eax
  int pSummon2; // esi
  int nOwner; // eax
  int *pTableIt2; // eax
  uint32_t *pRegItem; // [esp+8h] [ebp-14h] BYREF
  int nHitCount; // [esp+Ch] [ebp-10h]
  int nCollCount; // [esp+10h] [ebp-Ch]
  uint32_t *pSelfSave; // [esp+14h] [ebp-8h]
  char bInTable; // [esp+1Bh] [ebp-1h]

  pThis = this;
  fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
  nIdx = 0;
  pSelfSave = this;
  if ( fld_e29 == 0 )
    return 0;
  if ( pArg3 != 0 )  // 出口表先清空（begin/end/cap 三槽）
  {
    if ( *(uint32_t *)(pArg3 + 4) != 0 )  // pArg3+4〔宿主对象〕
      j__free(*(void **)(pArg3 + 4));  // 调 堆释放
    *(uint32_t *)(pArg3 + 4) = 0;  // pArg3+4〔宿主对象〕
    *(uint32_t *)(pArg3 + 8) = 0;  // pArg3+8〔nSkillRec8(推断)〕
    *(uint32_t *)(pArg3 + 12) = 0;  // pArg3+12〔nSkillRec12(推断)〕
  }
  pTableIt = &dword_738020;  // 召唤种码表 dword_738020..738030
  while ( nArg2 != *pTableIt )  // 当 nArg2 != *pTableIt 循环
  {
    if ( (int)++pTableIt >= (int)&dword_738030 )
    {
      bInTable = 0;
      goto LABEL_11;
    }
  }
  bInTable = 1;  // nArg2=通配码（0xFFFF 等）不在表内则 0
LABEL_11:
  nCollList = pThis[29];
  nCollBegin = *(uint32_t *)(nCollList + 120);
  nCollHead = nCollList + 116;
  nHitCount = 0;
  if ( nCollBegin != 0 )
    nCollCount = (*(uint32_t *)(nCollHead + 8) - nCollBegin) >> 2;  // 碰撞表元素个数
  else
    nCollCount = 0;
  if ( nCollCount > 0 )
  {
    do
    {
      nCollList2 = pThis[29];
      nCollBegin2 = *(uint32_t *)(nCollList2 + 120);
      if ( nCollBegin2 != 0 && nIdx < (*(uint32_t *)(nCollList2 + 124) - nCollBegin2) >> 2 )  // 向量元素数 = (end−begin)/4
        pCollItem = *(uint32_t *)(nCollBegin2 + 4 * nIdx);
      else
        pCollItem = 0;
      pMon = (uint32_t *)__RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                        pCollItem,
                        0,
                        &IRDCollisionObject `RTTI Type Descriptor',
                        &IRDMonster `RTTI Type Descriptor',
                        0);
      pMon2 = pMon;
      pRegItem = pMon;
      if ( pMon != nullptr )  // 是怪物型：主人回指 + 姿态过滤
      {
        if ( (uint32_t *)pMon[2088] != pThis  // 2088 槽=主人
          || (*(int (/*thiscall*/ **)(uint32_t *))(*pMon + 840))(pMon) == 13  // 姿态13 排除
          || (*(int (/*thiscall*/ **)(uint32_t *))(*pMon2 + 840))(pMon2) == 5 )  // 姿态5 排除
        {
          goto LABEL_44;
        }
        nCode = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*pMon2 + 340))(pMon2);  // vt+340 取召唤码
      }
      else  // 非怪物：试 CNSummonMonsterWithEffect 分支
      {
        nCollList3 = pThis[29];
        nCollBegin3 = *(uint32_t *)(nCollList3 + 120);
        if ( nCollBegin3 != 0 && nIdx < (*(uint32_t *)(nCollList3 + 124) - nCollBegin3) >> 2 )  // 向量元素数 = (end−begin)/4
          pCollItem2 = *(uint32_t *)(nCollBegin3 + 4 * nIdx);
        else
          pCollItem2 = 0;
        pSummon = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                pCollItem2,
                0,
                &IRDCollisionObject `RTTI Type Descriptor',
                &CNSummonMonsterWithEffect `RTTI Type Descriptor',
                0);
        pSummon2 = pSummon;
        if ( pSummon == 0 || (uint32_t *)(nOwner = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pSummon + 576))(pSummon)) != pSelfSave )  // 虚函数调用 槽+576
        {
          pThis = pSelfSave;
          goto LABEL_44;
        }
        nCode = *(uint16_t *)(pSummon2 + 973);  // +973 半字召唤码
        pThis = pSelfSave;
      }
      if ( nArg2 == 0xFFFF || nArg2 == nCode )  // 通配或码匹配
        goto LABEL_40;
      if ( bInTable != 0 && pszArg4 != 0 )  // 查登记表
      {
        pTableIt2 = &dword_738020;
        while ( nCode != *pTableIt2 )  // 当 nCode != *pTableIt2 循环
        {
          if ( (int)++pTableIt2 >= (int)&dword_738030 )
            goto LABEL_44;
        }
LABEL_40:
        ++nHitCount;  // 命中计数 +1
        if ( pArg3 != 0 && pMon2 != nullptr )  // 若 pArg3 != 0 与/或 pMon2 != nullptr
          sub_5DC730(&pRegItem);  // 登记到出口表
      }
LABEL_44:
      ++nIdx;
    }
    while ( (int)nIdx < nCollCount );
  }
  return nHitCount;
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5DD210 sub_5DD210 —— CNSummonMonsterAura 构造（召唤怪光环区）：·sub_5910D0 基类 CNRDAuraMaster 构造(0,18,250,1)
// ·置 CNSummonMonsterAura vftable、·sub_64EE80 装配、·sub_64F170 装载 SummonMonsterAuraArea 资源；被·0x5DD810 case 48 实例化
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DD210(uint32_t *this, int nArg2, int nArg3, int nArg4)  // CNSummonMonsterAura 构造（召唤怪光环区）：·sub_5910D0 基类
{
  sub_5910D0(this, 0, 18, 250, 1);  // CNRDAuraMaster 构造函数
  *this = &CNSummonMonsterAura::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_64EE80(this);  // 13 行小函数
  sub_64F170(nArg2, nArg3, nArg4);  // 装载 SummonMonsterAuraArea.ani（42FCB0/431860）
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD280 sub_5DD280 —— 三字段直写 setter（this+84/+128/+132 依次内存 nArg2/nArg3/nArg4）；本文件内无调用点【推断：vtable 挂接】
// ·与·0x5DD210 同属 CNSummonMonsterAura 族，疑似召唤区参数配置接口【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD280(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数定义: 三字段直写 setter（this+84/+128/+132 依次内存 nArg2/nArg3/nArg4）…
{
  *(this + 21) = nArg2;  // this+21 【推断】霸体状态字节
  *(this + 32) = nArg3;  // this+32 格子像素尺寸
  *(this + 33) = nArg4;  // this+33 【推断】职业数据脏位
  return nArg4;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD2A0 sub_5DD2A0 —— CNSummonMonsterAura 标量删除器（转调·sub_5DD2D0 析构，bit0 置位才 j__free）
// ·与·0x5DD3B0 同构，对应·0x5DD210/·0x5DD320 两构造
// ------------------------------------------------------------
void */*thiscall*/ sub_5DD2A0(void *Block, char pszArg2)  // CNSummonMonsterAura 标量删除器（转调·sub_5DD2D0 析构，bit
{
  sub_5DD2D0();  // CNSummonMonsterAura 析构：置 CNSummonMonsterAura v
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD2D0 sub_5DD2D0 —— CNSummonMonsterAura 析构：置 CNSummonMonsterAura vftable、·sub_64F1F0 召唤受击收尾
// ·末尾转·sub_591190 CNRDAuraMaster 基类析构（本组析构统一尾调）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD2D0(char *this)  // 实现：CNSummonMonsterAura 析构：置 CNSummonMonsterAura vftable、·sub_64F1F0 召唤受击收…
{
  *(uint32_t *)this = &CNSummonMonsterAura::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_64F1F0();  // 召唤受击（42AF90/657740）
  return sub_591190(this);  // CNRDAuraMaster 析构函数
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DD320 sub_5DD320 —— CNTargetIt 构造（标记球挂件）：·sub_5910D0 基类构造(0,18,250,0) → 置 CNTargetIt vftable
// ··sub_607240/·sub_607280 初始化 this+136 双子对象、this+160/164/168 三指针清零、·sub_64F230 装配、·sub_64FB80 装载 Character/Mage/Effect 资源
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DD320(uint32_t *this)  // CNTargetIt 构造（标记球挂件）：·sub_5910D0 基类构造(0,18,250
{
  sub_5910D0(this, 0, 18, 250, 0);  // CNRDAuraMaster 构造函数
  *this = &CNTargetIt::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_607240(this + 34);  // 计时结构初始化
  sub_607280(this + 34);  // 调 初始化 this+136 双子对象、this+160/164/168 三指针清零、
  *(this + 40) = 0;  // 写 this+40 = 0（状态子标志）
  *(this + 41) = 0;  // this+164〔fAdd164(推断)〕
  *(this + 42) = 0;  // this+168〔pAppendVec(推断)〕
  sub_64F230(this);  // 13 行小函数 2
  sub_64FB80(this);  // 装载 Character/Mage/Effect/Animation/TargetIt.an
  return this;  // 返回自身指针
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD3B0 sub_5DD3B0 —— CNTargetIt 标量删除器（转调·sub_5DD3E0 析构，bit0 置位才 j__free）
// ·与·0x5DD2A0 同构，对应 new(0xB0) 的 CNTargetIt 块释放【推断】
// ------------------------------------------------------------
void */*thiscall*/ sub_5DD3B0(void *Block, char pszArg2)  // CNTargetIt 标量删除器（转调·sub_5DD3E0 析构，bit0 置位才 j__
{
  sub_5DD3E0();  // CNTargetIt 析构：置 CNTargetIt vftable、·sub_64FC00
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DD3E0 sub_5DD3E0 —— CNTargetIt 析构：置 CNTargetIt vftable、·sub_64FC00 目标受击收尾
// ·释放 this+160 指针块并三清 +160/164/168，nullsub_3(this+136) 收末，末尾转·sub_591190 CNRDAuraMaster 基类析构
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD3E0(int this)  // 实现：CNTargetIt 析构：置 CNTargetIt vftable、·sub_64FC00 目标受击收尾
{
  *(uint32_t *)this = &CNTargetIt::`vftable';  // 写 vftable 指针（对象重定位/复位）
  sub_64FC00();  // 目标受击（42AF90/657740）
  if ( *(uint32_t *)(this + 160) != 0 )  // this+160 第 5 组·+1040 增量子倍率
    j__free(*(void **)(this + 160));  // this+160 第 5 组·+1040 增量子倍率
  *(uint32_t *)(this + 160) = 0;  // this+160 第 5 组·+1040 增量子倍率
  *(uint32_t *)(this + 164) = 0;  // this+164 第 5 组·+88 增量子倍率
  *(uint32_t *)(this + 168) = 0;  // this+168 附属对象向量 begin
  nullsub_3(this + 136);  // this+136 演出已播标志
  return sub_591190((char *)this);  // CNRDAuraMaster 析构函数
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
int /*thiscall*/ sub_5DD470(int this)  // 实现：CNMage/白魔 WZ 构造后段资源装配（由·0x579E70 接·0x5DA220 之后调用）：
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
  *(uint32_t *)(this + 6792) = 2;  // this+6792 【推断】炮车/子类参数面槽 1
  *(uint32_t *)(this + 6796) = 2;  // this+6796 【推断】炮车/子类参数面槽 2
  *(uint32_t *)(this + 6800) = 2;  // this+6800 【推断】炮车/子类参数面槽 3
  *(uint32_t *)(this + 6804) = 3;  // this+6804 【推断】炮车/子类参数面槽 4
  *(uint32_t *)(this + 6808) = 4;  // this+6808 【推断】炮车/子类参数面槽 5
  *(uint32_t *)(this + 6864) = 1;
  *(uint32_t *)(this + 6868) = 8;
  *(uint32_t *)(this + 6872) = 14;
  v3 = *(uint32_t *)(pThis_1ED4 + 4);  // this+4 宿主对象
  Block = (void *)3;  // Block = 转换(3)
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pThis_1ED4 + 8) - v3) >> 2;  // this+8 物品 id
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(pThis_1ED4 + 12) - v3) >> 2 )  // this+12 物品类型号
  {
    v5 = *(uint32_t **)(pThis_1ED4 + 8);  // this+8 物品 id
    *v5 = 3;
    *(uint32_t *)(pThis_1ED4 + 8) = v5 + 1;  // this+8 物品 id
  }
  else
  {
    sub_430C80(*(void **)(pThis_1ED4 + 8), 1, (int)&Block);  // uint32 vector 区间插入（同值填充）
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
  Block = operator new(0x12Cu);  // 堆分配 300 字节对象
  v9 = 0;
  if ( Block != nullptr )  // 若 Block 有效（非空）
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )  // 判定 “+384 SSO容量”
      pThis_16C = sub_4C3640(this + 364, "Effect/Particle/HandHit1.ptl", this);  // 字符串 “Effect/Particle/HandHit1.ptl”
    else
      pThis_16C = sub_4C3640(*(uint32_t *)(this + 364), "Effect/Particle/HandHit1.ptl", this);  // 字符串 “Effect/Particle/HandHit1.ptl”
  }
  else
  {
    pThis_16C = 0;
  }
  v9 = -1;
  *(uint32_t *)(this + 8416) = pThis_16C;
  Block = operator new(0x12Cu);  // 堆分配 300 字节对象
  v9 = 1;
  if ( Block != nullptr )  // 若 Block 有效（非空）
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )  // 判定 “+384 SSO容量”
      result = sub_4C3640(this + 364, "Effect/Particle/HandHit2.ptl", this);  // 字符串 “Effect/Particle/HandHit2.ptl”
    else
      result = sub_4C3640(*(uint32_t *)(this + 364), "Effect/Particle/HandHit2.ptl", this);  // 字符串 “Effect/Particle/HandHit2.ptl”
  }
  else
  {
    result = 0;
  }
  *(uint32_t *)(this + 8420) = result;  // this+8420 【推断】对象数组 begin
  return result;
}



// AI 字段访问（this+8372）
// ------------------------------------------------------------
// 0x5DD700 sub_5DD700 —— 召唤物受击转发：this+8372 挂件存活时·sub_5DD040(this,0xFFFF,...,1) 全量收集召唤物
// ·再逐个 vt+1052(obj, this, nArg2, nArg3, nArg4) 下发受击；随后取 nArg2 攻方档位 vt+348(nArg2)+60 判断本机关卡门，
// ·动画槽（this+120 挂载对象 +148==-1 时·sub_4938F0 帧游标复位、取 +112；this+642 则直取 this+644）就绪时 vt+216(this,11) 解忙
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD700(int this, int nArg2, int nArg3, int nArg4)  // 实现：召唤物受击转发：this+8372 挂件存活时·sub_5DD040(this,0xFFFF,...,1) 全量收集召唤物
{
  int fld_20B4; // eax  | +0x20B4 → 0x5DE690 累加值（fld_20B4，写入前读取）（CNMage；va=005DE690）
  uint32_t *Block2; // esi
  uint32_t *v7; // ebx
  int fld_284; // esi  | +0x0284 → 帧时刻覆盖值（0x5DD700 读）【基类字段】（CNMage；va=005DD700）
  int fld_78; // esi  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主；0x5DE690 经此 +148 取剩余硬直）【基类字段】（CNMage；va=00499020）
  char v11[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  uint32_t *v13; // [esp+14h] [ebp-14h]
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]

  fld_20B4 = *(uint32_t *)(this + 8372);  // this+8372 0x5DE690 累加值
  if ( fld_20B4 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_20B4 + 80))() != 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
  {
    Block = nullptr;
    v13 = nullptr;
    v14 = 0;
    v15 = 0;
    sub_5DD040((uint32_t *)this, 0xFFFF, (int)v11, 1);  // 召唤物/弹体筛选收集（this[29] 碰撞表）：先按 pArg3 清空出口表，nArg2
    Block2 = Block;
    v7 = v13;
    if ( Block != v13 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(*(uint32_t *)*Block2 + 1052))(*Block2, this, nArg2, nArg3, nArg4);  // 虚调用 vt+1052
        ++Block2;
      }
      while ( Block2 != v7 );
      Block2 = Block;
    }
    v15 = -1;
    if ( Block2 != nullptr )  // 若 Block2 有效（非空）
      j__free(Block2);  // 调 堆释放
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 60) != 0 )  // 虚函数调用 槽+348
  {
    if ( *(uint8_t *)(this + 642) != 0 )  // 判定 “+642 帧时刻覆盖开关”
    {
      fld_284 = *(uint32_t *)(this + 644);  // 读 fld_284 = this+644（帧时刻覆盖值）
    }
    else
    {
      fld_78 = *(uint32_t *)(this + 120);  // 读 fld_78 = this+120（动画对象）
      if ( fld_78 == 0 )
      {
LABEL_16:
        if ( (uint8_t)nArg4 == 0 )
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 11);  // this+216 【推断】子链标志字节
        return sub_4B9720(nArg2, nArg3, nArg4);  // 霸体特效（SuperArmorEffect.ani；sub_4920E0 全帧缩放；+40/
      }
      if ( *(uint32_t *)(fld_78 + 148) == -1 )
        sub_4938F0(*(uint32_t *)(this + 120));  // 调 调 sub_4938F0
      fld_284 = *(uint32_t *)(fld_78 + 112);
    }
    if ( fld_284 != 0 )
      return sub_4B9720(nArg2, nArg3, nArg4);  // 霸体特效（SuperArmorEffect.ani；sub_4920E0 全帧缩放；+40/
    goto LABEL_16;
  }
  return sub_4B9720(nArg2, nArg3, nArg4);  // 霸体特效（SuperArmorEffect.ani；sub_4920E0 全帧缩放；+40/
}



// 参数打包+数据表 AI（sub_431230+sub_47EF20, 160L）
// ------------------------------------------------------------
// 0x5DD810 sub_5DD810 —— 挂件槽按相位建销总表（pArg2 为相位/挂点号，Block 为开关量）：
// ·pArg2==1 时 Block<=0 转·sub_505FF0(1,0)；>0 且 this+7892 表不足 2 项则以·sub_431230 写入常量 4；
// ·pArg2==19 建 new(0x7C)+·sub_4B3C90 于 this+8552，vt+64(obj)+36 清标志，·sub_47EF20 抽参后 vt+124/vt+120(9,...)/vt+56 装配，
// ·Block<=0 且存活则·sub_53FE50 回收；pArg2==35/36 建 new(0x88)+·sub_4C2820 于 this+8556/8560 并经·sub_5F9DD0 起效；
// ·pArg2==48 建 new(0x8C)+·0x5DD210 于 this+8564，抽三参 sub_47EF20(2/1/0,...)*0.1 经 vt+148 定标后 vt+56 装配
// ------------------------------------------------------------
void /*thiscall*/ sub_5DD810(int *this, void *pArg2, int Block)  // 函数定义: 挂件槽按相位建销总表（pArg2 为相位/挂点号，Block 为开关量）：
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
  sub_4B3E70(this, pArg2, Block);  // Buff 图标/状态附加物增删
  if ( pArg2 == (void *)1 )
  {
    if ( Block2 <= 0 )
    {
      sub_505FF0(1, 0);
    }
    else
    {
      fld_e1974 = *(this + 1974);
      if ( fld_e1974 == 0 || (unsigned int)((*(this + 1975) - fld_e1974) >> 2) < 2 )  // 向量元素数 = (end−begin)/4
      {
        Block = 4;
        sub_431230((int)(this + 1973), &Block);  // uint32 vector push_back
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
        pMem = operator new(0x7Cu);  // 堆分配 124 字节对象
        Block = (int)pMem;
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
          pObj = sub_4B3C90((int)pMem, 0, 0);  // 结果 = CNChangeStatus 构造（双参）
        else
          pObj = 0;
        *(this + 2138) = pObj;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
      }
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 19);  // 虚调用 vt+1160
      v8 = sub_47EF20(0, Block2, -1, -1, 11);  // 调 读攻击数据表
      fld_e2138 = (int *)*(this + 2138);
      v10 = *fld_e2138;
      Block = v8;
      (*(void (/*thiscall*/ **)(int *))(v10 + 124))(fld_e2138);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      v22 = (float)Block;
      (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)*(this + 2138) + 120))(9, 0, LODWORD(v22));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2138) + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
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
    if ( fld_e21382 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21382 + 80))(fld_e21382) == 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
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
      if ( pObj4 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 80))(pObj4) == 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        return;
      fld_e21383 = *(this + v17 + 2139);
      goto LABEL_41;
    }
    if ( *(this + v17 + 2139) == 0 )
    {
      pMem2 = operator new(0x88u);  // 堆分配 136 字节对象
      if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
        pObj3 = sub_4C2820((int)pMem2, 3, (int)pArg2);  // 调 于 this+8556/8560 并经·sub_5F9DD0 起效
      else
        pObj3 = 0;
      *(this + v17 + 2139) = pObj3;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 64))(pObj3) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
    }
    sub_5F9DD0(Block);
    (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + v17 + 2139) + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
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
      if ( fld_e2141 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2141 + 80))(fld_e2141) == 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        return;
      fld_e21383 = *(this + 2141);
      goto LABEL_41;
    }
    if ( *(this + 2141) == 0 )
    {
      if ( operator new(0x8Cu) != nullptr )  // 堆分配 140 字节对象
        pObj2 = sub_5DD210(0, 0, 0);  // 结果 = CNSummonMonsterAura 构造（召唤怪光环区）：·sub_5910D0 基类
      else
        pObj2 = 0;
      *(this + 2141) = pObj2;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2) + 36) = 0;  // 虚函数调用 槽+64：文案槽（459700/4015C0/45A340
    }
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 48);  // 虚调用 vt+1160
    fld_e21412 = *(uint32_t *)*(this + 2141);
    v23 = (double)(int)sub_47EF20(2, Block, -1, -1, 11) * 0.1;  // 调 读攻击数据表
    v21 = (double)(int)sub_47EF20(1, Block, -1, -1, 11) * 0.1;  // 调 读攻击数据表
    v15 = sub_47EF20(0, Block, -1, -1, 11);  // 调 读攻击数据表
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(fld_e21412 + 148))(  // 虚函数调用 槽+148：槽（12 行）
      *(this + 2141),
      v15 / 2,
      LODWORD(v21),  // 调 取 64 位值低 32 位
      LODWORD(v23));  // 调 取 64 位值低 32 位
    (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2141) + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
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
int /*thiscall*/ sub_5DDBA0(uint32_t *this, int nArg2)  // 实现：标记球挂件挂装（this+8492 槽）：空则 new(0xB0)+·0x5DD320 建 CNTargetIt、vt+64(obj)+36…
{
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edi

  if ( *(this + 2123) == 0 )
  {
    pMem = operator new(0xB0u);  // 堆分配 176 字节对象
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v4 = sub_5DD320(pMem);  // 结果 = CNTargetIt 构造（标记球挂件）：·sub_5910D0 基类构造(0,18,250
    else
      v4 = nullptr;
    *(this + 2123) = v4;
    *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 64))(v4) + 36) = 0;  // 虚调用 vt+64
  }
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1140))(this);  // 结果 = 虚调用 vt+1140
  sub_64F250(v5);  // 目标数据（47EF20/607260/607280）
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1140))(this);  // 结果 = 虚调用 vt+1140
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*this + 1160))(this, 50, 0, v6);  // 虚调用 vt+1160
  v7 = sub_47EF20(50, -1, -1, 11, 50);  // 调 读攻击数据表
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2123) + 80))(*(this + 2123)) == 0  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    || *(uint32_t *)(*(this + 2123) + 4) != nArg2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2123) + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
      *(this + 2123),
      nArg2,
      this,
      1,
      0,
      0,
      -1);
  }
  return sub_64FAC0(v7);  // 目标锁业务（699000/430C80/47E9D0/64F390）
}



// 白魔相位字段大区（this+8232..8480, 247L —— WZ 专用字段块）
// ------------------------------------------------------------
// 0x5DDCA0 sub_5DDCA0 —— CNMage 白魔字段块总析构（this+8232..8564 全槽清理，由·0x579F10 构造链对偶调用）：
// ·先 vt[0](obj,1) 释放 this+8232/8236/8240/8248 四挂件指针；this+8276 起 4x2 与 this+8328 起 5x3 两组
// ·经·sub_42AF90+·sub_657740(obj,228) 双段回收（228 为对象池/尺寸码）并逐槽清零；
// ·再处理 +8372/8380、+8396 起 2x4 块（含 vt[0] 与·sub_42AF90 混合）、+8448/8452、+8456 起 2、+8464、+8468 起 3、
// ·+8480 起 2、+8492、+8500、+8524、+8544、+8552、+8556 起 2、+8564 各组【推断：+8396..8420 与·0x5DD470 的 HandHit 粒子槽对应】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DDCA0(int this)  // 实现：CNMage 白魔字段块总析构（this+8232..8564 全槽清理，由·0x579F10 构造链对偶调用）：
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

  pThis_2028 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8232);  // this+8232 【推断】抓取数据表读数
  if ( pThis_2028 != nullptr )  // 若 pThis_2028 有效（非空）
    (**pThis_2028)(pThis_2028, 1);  // 调 pThis_2028 的虚函数（vt+0）
  pThis_202C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8236);  // this+8236 反射/连击计数
  *(uint32_t *)(this + 8232) = 0;  // this+8232 【推断】抓取数据表读数
  if ( pThis_202C != nullptr )  // 若 pThis_202C 有效（非空）
    (**pThis_202C)(pThis_202C, 1);  // 调 pThis_202C 的虚函数（vt+0）
  pThis_2030 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8240);  // this+8240 抓取参数个数
  *(uint32_t *)(this + 8236) = 0;  // this+8236 反射/连击计数
  if ( pThis_2030 != nullptr )  // 若 pThis_2030 有效（非空）
    (**pThis_2030)(pThis_2030, 1);  // 调 pThis_2030 的虚函数（vt+0）
  pThis_2038 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8248);  // this+8248 变体值
  *(uint32_t *)(this + 8240) = 0;  // this+8240 抓取参数个数
  if ( pThis_2038 != nullptr )  // 若 pThis_2038 有效（非空）
    (**pThis_2038)(pThis_2038, 1);  // 调 pThis_2038 的虚函数（vt+0）
  *(uint32_t *)(this + 8248) = 0;  // this+8248 变体值
  pThis_2054 = (void ***)(this + 8276);  // this+8276 仅见复位
  for ( i = 4; i != 0; --i )  // 循环：i 从 4 递减到 0
  {
    for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
    {
      v7 = *pThis_2054;
      if ( *pThis_2054 != nullptr )
      {
        sub_42AF90(*pThis_2054);  // 帧对象析构（帧数组 + 元素数组）
        sub_657740(v7, 228);  // 池化结点弹出（写魔术标记后挂入链头）
      }
      *pThis_2054++ = nullptr;
    }
  }
  pThis_2088 = (void ***)(this + 8328);  // this+8328 仅见复位
  for ( k = 5; k != 0; --k )  // 循环：k 从 5 递减到 0
  {
    v9 = (int)*(pThis_2088 - 5);
    if ( v9 != 0 )
    {
      sub_42AF90(*(pThis_2088 - 5));  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v9, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    v10 = *pThis_2088;
    v11 = *pThis_2088 == nullptr;
    *(pThis_2088 - 5) = nullptr;
    if ( !v11 )
    {
      sub_42AF90(v10);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v10, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    v12 = pThis_2088[5];
    *pThis_2088 = nullptr;
    if ( v12 != nullptr )  // 若 v12 有效（非空）
    {
      sub_42AF90(v12);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v12, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    pThis_2088[5] = nullptr;
    ++pThis_2088;
  }
  pThis_20B4 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8372);  // this+8372 0x5EA970: *
  if ( pThis_20B4 != nullptr )  // 若 pThis_20B4 有效（非空）
    (**pThis_20B4)(pThis_20B4, 1);  // 调 pThis_20B4 的虚函数（vt+0）
  pThis_20BC = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8380);  // this+8380 【推断】动画对象 C
  *(uint32_t *)(this + 8372) = 0;  // this+8372 0x5EA970: *
  if ( pThis_20BC != nullptr )  // 若 pThis_20BC 有效（非空）
    (**pThis_20BC)(pThis_20BC, 1);  // 调 pThis_20BC 的虚函数（vt+0）
  *(uint32_t *)(this + 8380) = 0;  // this+8380 【推断】动画对象 C
  pThis_20E0 = this + 8416;
  for ( m = 2; m != 0; --m )  // 循环：m 从 2 递减到 0
  {
    v16 = *(uint32_t *)(pThis_20E0 - 8);
    if ( v16 != 0 )
    {
      sub_42AF90(*(void ***)(pThis_20E0 - 8));  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v16, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    v17 = *(void (/*thiscall*/ ****)(uint32_t, int))pThis_20E0;
    v11 = *(uint32_t *)pThis_20E0 == 0;
    *(uint32_t *)(pThis_20E0 - 8) = 0;
    if ( !v11 )
      (**v17)(v17, 1);  // 调 v17 的虚函数（vt+0）
    v18 = *(void ***)(pThis_20E0 + 8);  // this+8 物品 id
    *(uint32_t *)pThis_20E0 = 0;
    if ( v18 != nullptr )  // 若 v18 有效（非空）
    {
      sub_42AF90(v18);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v18, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    v19 = *(void ***)(pThis_20E0 + 16);  // this+16 频道型选中索引
    *(uint32_t *)(pThis_20E0 + 8) = 0;  // this+8 物品 id
    if ( v19 != nullptr )  // 若 v19 有效（非空）
    {
      sub_42AF90(v19);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v19, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *(uint32_t *)(pThis_20E0 + 16) = 0;  // this+16 频道型选中索引
    pThis_20E0 += 4;
  }
  fld_2100 = *(uint32_t *)(this + 8448);  // this+8448 【推断】收招数据值
  if ( fld_2100 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8448));  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_2100, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_2104 = *(void ***)(this + 8452);
  *(uint32_t *)(this + 8448) = 0;  // this+8448 【推断】收招数据值
  if ( fld_2104 != nullptr )  // 若 fld_2104 有效（非空）
  {
    sub_42AF90(fld_2104);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_2104, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  *(uint32_t *)(this + 8452) = 0;
  pThis_2108 = (void ***)(this + 8456);  // this+8456 攻击倍率组件
  for ( n = 2; n != 0; --n )  // 循环：n 从 2 递减到 0
  {
    v23 = *pThis_2108;
    if ( *pThis_2108 != nullptr )
    {
      sub_42AF90(*pThis_2108);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v23, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_2108++ = nullptr;
  }
  fld_2110 = *(uint32_t *)(this + 8464);
  if ( fld_2110 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8464));  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_2110, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  *(uint32_t *)(this + 8464) = 0;
  pThis_2114 = (void ***)(this + 8468);  // this+8468 【推断】技能对象指针
  for ( ii = 3; ii != 0; --ii )  // 循环：ii 从 3 递减到 0
  {
    v26 = *pThis_2114;
    if ( *pThis_2114 != nullptr )
    {
      sub_42AF90(*pThis_2114);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v26, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_2114++ = nullptr;
  }
  pThis_2120 = (void ***)(this + 8480);  // this+8480 【推断】攻击挂接对象
  v43 = 2;
  do
  {
    v28 = *pThis_2120;
    if ( *pThis_2120 != nullptr )
    {
      sub_42AF90(*pThis_2120);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v28, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_2120++ = nullptr;
    result = v43 - 1;
    v43 = result;
  }
  while ( result != 0 );
  pThis_212C = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8492);
  if ( pThis_212C != nullptr )  // 若 pThis_212C 有效（非空）
    result = (**pThis_212C)(pThis_212C, 1);  // 调 pThis_212C 的虚函数（vt+0）
  fld_2134 = *(void ***)(this + 8500);  // this+8500 【推断】充能计时
  *(uint32_t *)(this + 8492) = 0;
  if ( fld_2134 != nullptr )  // 若 fld_2134 有效（非空）
  {
    sub_42AF90(fld_2134);  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_2134, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_214C = *(void ***)(this + 8524);  // this+8524 复位批标志字节
  *(uint32_t *)(this + 8500) = 0;  // this+8500 【推断】充能计时
  if ( fld_214C != nullptr )  // 若 fld_214C 有效（非空）
  {
    sub_42AF90(fld_214C);  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_214C, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_2160 = *(void ***)(this + 8544);  // this+8544 0x5DE690 经 sub_4939E0
  *(uint32_t *)(this + 8524) = 0;  // this+8524 复位批标志字节
  if ( fld_2160 != nullptr )  // 若 fld_2160 有效（非空）
  {
    sub_42AF90(fld_2160);  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_2160, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  pThis_2168 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8552);
  *(uint32_t *)(this + 8544) = 0;  // this+8544 0x5DE690 经 sub_4939E0
  if ( pThis_2168 != nullptr )  // 若 pThis_2168 有效（非空）
    result = (**pThis_2168)(pThis_2168, 1);  // 调 pThis_2168 的虚函数（vt+0）
  *(uint32_t *)(this + 8552) = 0;
  pThis_216C = (uint32_t *)(this + 8556);
  for ( jj = 2; jj != 0; --jj )  // 循环：jj 从 2 递减到 0
  {
    if ( *pThis_216C != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_216C)(*pThis_216C, 1);
    *pThis_216C++ = 0;
  }
  pThis_2174 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8564);
  if ( pThis_2174 != nullptr )  // 若 pThis_2174 有效（非空）
    result = (**pThis_2174)(pThis_2174, 1);  // 调 pThis_2174 的虚函数（vt+0）
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
int /*thiscall*/ sub_5DE100(int *this, int nArg2, float *pArg3, int nArg4)  // 实现：冲刺命中（白魔 WZ_DASH_HIT）：vt+308 存活 + 攻方 vt+40(,17) 为玩家 + ·sub_4E4630 敌我成立 …
{
  uint32_t *pColObj; // edi
  int nVt1; // eax
  uint32_t *pEntry39; // eax
  int nDelay; // ebx
  int fld_e2060; // ecx
  int fld_e1639; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  char bDashState; // bl
  int nParam40; // eax
  int fld_e16392; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  int hAnim; // edi
  int fld_e91; // edx  | +0x016C → ★ 场景动画池指针（CNMage；va=005DE690）
  int *pWhipObj; // edi
  int fld_e29; // ecx  | +0x0074 → 0x5DE690 读取槽（fld_74）（CNMage；va=005DE690）
  int nWhipVt; // ebx
  uint64_t nPosPacked; // rax
  int nWhipVt2; // ebx
  int nWhipTarget; // eax
  int nWhipFace; // eax
  int nTargetRoom; // ebx
  int nEntry20a; // eax
  int *pNode273; // eax
  int nVt3; // edx
  int nNodeVt; // ebx
  uint32_t *pEntry20; // eax
  int nEntry20b; // eax
  int *pNode529; // eax
  int nVt4; // eax
  int pActive; // eax
  int pActive2; // edi
  int nDmgBlocked; // ebx
  int nVt5; // eax
  int nDmgType; // eax
  char *pEntry14; // edi
  int nParam14; // ebx
  int nBaseParam; // eax
  int nBaseParam2; // eax
  int nParam5; // eax
  int fld_e2135; // eax  | +0x215C → ★ 相位时间戳（CNMage；va=005DE690）
  int fld_e21352; // edx  | +0x215C → ★ 相位时间戳（CNMage；va=005DE690）
  int nHitCount; // eax
  int nVt6; // eax
  int nBaseParam3; // eax
  int nVt7; // eax
  int nCastResult; // eax
  int nArg40; // [esp-Ch] [ebp-74h]
  int nPosY; // [esp-4h] [ebp-6Ch]
  unsigned int uSelLost; // [esp+0h] [ebp-68h]
  int nParam6; // [esp+Ch] [ebp-5Ch]
  void *Block; // [esp+10h] [ebp-58h]
  int dwScratch; // [esp+14h] [ebp-54h] BYREF | 双用：case20 存鞭挞结点指针，case21 作伤害类型出参
  int fld_e21353; // [esp+18h] [ebp-50h] BYREF
  int16_t nSub4; // [esp+1Ch] [ebp-4Ch]
  int16_t nSub3; // [esp+1Eh] [ebp-4Ah]
  int16_t nSub15; // [esp+20h] [ebp-48h]
  int nParam7; // [esp+22h] [ebp-46h]
  int dword_796E502; // [esp+58h] [ebp-10h]
  int nFreeState; // [esp+64h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  pColObj = (uint32_t *)nArg2;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0  // 存活
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0  // 攻方类型17=玩家【推断】
    && sub_4E4630(this, nArg2)  // 敌我关系成立
    && (uint8_t)sub_5DB490(this) != 0  // 追击弹在（DASH 弹存在）
    && (uint8_t)nArg4 == 0 )  // 非格挡
  {
    nVt1 = *this;
    *(this + 2110) = nArg2;  // this+8440=目标记录
    pEntry39 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(nVt1 + 1160))(this, 39);  // 39 号数据表
    nDelay = sub_47E9D0(pEntry39, 0);  // 调 收招/结束例程
    *(this + 2111) = sub_699000((int)(this + 9)) + nDelay;  // this+8444=到期时刻=now+表值
  }
  fld_e2060 = *(this + 2060);  // this+8240〔nParamCnt〕
  if ( fld_e2060 != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2060 + 80))(fld_e2060) != 0  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    && (uint8_t)nArg4 == 0
    && sub_4E4630(this, nArg2) )  // 调 （上一表达式的参数/条件续行）
  {
    fld_e1639 = *(this + 1639);  // 读 fld_e1639 = this+6556（大状态ID）
    bDashState = 0;
    if ( fld_e1639 == 8 && *(this + 2054) == -1 || fld_e1639 == 12 || fld_e1639 == 7 )  // 主状态 8(攻)/12(冲刺)/7 命中态
      bDashState = 1;
    nArg40 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 40, -1);  // 结果 = 虚调用 vt+1140
    (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);  // 虚调用 vt+1160
    nParam40 = sub_47EF20(40, 3 - (bDashState != 0), nArg40, -1, 11);  // 40 号技能表读数（命中态取 3 档否则 4 档）
    sub_5DC590(nParam40);  // 发射概率门
  }
  fld_e16392 = *(this + 1639);  // 读 fld_e16392 = this+6556（大状态ID）
  switch ( fld_e16392 )  // 主状态镜像 12/20/21 分派
  {
    case 12:  // 冲刺命中首次：播 WZ_DASH_HIT
      if ( *((uint8_t *)this + 8228) == 0 )  // this+8228 0x5DE690: !=0 条件字节
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "WZ_DASH_HIT", -1, 0, 0);  // 字符串 “WZ_DASH_HIT”
        *((uint8_t *)this + 8228) = 1;  // 已播标志
      }
      return sub_4AFB30(this, pColObj, (int)pArg3, nArg4);
    case 20:  // 军团态：鞭击特效挂目标 + 建 CNWhipped 结点
      if ( *(this + 2129) != 20 || (uint8_t)nArg4 != 0 )
        return sub_4AFB30(this, pColObj, (int)pArg3, nArg4);
      hAnim = 0;
      nFreeState = 0;
      if ( sub_42FCB0(228) != 0 )  // 资源开关
      {
        if ( (unsigned int)*(this + 96) < 0x10 )  // 判定 “+384 SSO容量”
          LOBYTE(fld_e91) = (uint8_t)this + 108;  // this+108 第 1 组·宿主属性 +886 增量
        else
          fld_e91 = *(this + 91);  // 读 fld_e91 = this+364（场景动画池指针）
        hAnim = sub_431920(fld_e91, (char)"Effect/Animation/WhipToMonsterHit.ani", 1);  // 鞭打命中动画
      }
      nFreeState = 1;
      if ( sub_44B6C0(284) != 0 )  // CRT 一次性池初始化 2（池 &unk_98B6F8）
        pWhipObj = (int *)sub_44E1F0(hAnim, 1);  // 结果 = CNRDPooledObject 构造（虚表覆盖壳）
      else
        pWhipObj = nullptr;
      fld_e29 = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
      nFreeState = -1;
      sub_45FE80(fld_e29, (int)pWhipObj, 2, 0, (int)pWhipObj, nArg2, 0);  // 挂到目标场景
      nWhipVt = *pWhipObj;
      nPosY = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)nArg2 + 124))(nArg2, (uint64_t)(pArg3[5] * 0.5 + pArg3[2]));  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      nPosPacked = (uint64_t)(pArg3[3] * 0.5 + *pArg3);  // 命中点中点（偏移表 3/5 半程）
      (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, int))(nWhipVt + 112))(pWhipObj, HIDWORD(nPosPacked), nPosPacked, nPosY);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
      nWhipVt2 = *pWhipObj;
      nWhipTarget = (*(int (/*thiscall*/ **)(int *, int))(*this + 660))(this, nArg2);  // 结果 = 虚调用 vt+660
      nWhipFace = sub_432E50(nWhipTarget);  // 结果 = 关系码对调映射
      (*(void (/*thiscall*/ **)(int *, int))(nWhipVt2 + 148))(pWhipObj, nWhipFace);  // 对齐朝向
      nTargetRoom = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);  // 虚函数调用 槽+376：坐标同步包（type 37）
      if ( nTargetRoom == (*(int (/*thiscall*/ **)(int *))(*this + 376))(this) )  // 同房间才建结点
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 273) != 0 )  // 273=被鞭对象族
        {
          nFreeState = 2;
          if ( operator new(0x70u) != nullptr )  // 堆分配 112 字节对象
          {
            nEntry20a = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 20);  // 结果 = 虚调用 vt+1140
            pNode273 = (int *)sub_5DAFA0(0, nEntry20a);  // 弹种 0
          }
          else
          {
            pNode273 = nullptr;
          }
          nVt3 = *this;
          nNodeVt = *pNode273;
          dwScratch = (int)pNode273;
          nFreeState = -1;
          pEntry20 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int))(nVt3 + 1160))(this, 20, 1);  // 虚函数调用 槽+1160
LABEL_42:
          sub_47E9D0(pEntry20, uSelLost);  // 调 收招/结束例程
          (*(void (/*thiscall*/ **)(int, int, int *, int, uint32_t, int))(nNodeVt + 56))(dwScratch, nArg2, this, 1, 0, 11);  // 结点 vt+56 绑定（参数 11）
          goto LABEL_43;
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) != 0 )  // 529=哥布林族
        {
          nFreeState = 3;
          if ( operator new(0x70u) != nullptr )  // 堆分配 112 字节对象
          {
            nEntry20b = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 20);  // 结果 = 虚调用 vt+1140
            pNode529 = (int *)sub_5DAFA0(1, nEntry20b);  // 弹种 1
          }
          else
          {
            pNode529 = nullptr;
          }
          nNodeVt = *pNode529;
          dwScratch = (int)pNode529;
          nVt4 = *this;
          nFreeState = -1;
          pEntry20 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, uint32_t))(nVt4 + 1160))(this, 20, 0);  // 虚函数调用 槽+1160
          goto LABEL_42;
        }
      }
LABEL_43:
      pColObj = (uint32_t *)nArg2;
      return sub_4AFB30(this, pColObj, (int)pArg3, nArg4);
    case 21:  // 反应态 14 且 this+8532==1：试伤 + 48028 号伤害装配
      if ( *(this + 2134) != 14 || (uint8_t)nArg4 != 0 || *(this + 2133) != 1 )  // this+8532〔nPhaseValB(推断)〕
        return sub_4AFB30(this, pColObj, (int)pArg3, nArg4);
      pActive = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
              nArg2,
              0,
              &IRDCollisionObject `RTTI Type Descriptor',
              &IRDActiveObject `RTTI Type Descriptor',
              0);
      pActive2 = pActive;
      Block = (void *)pActive;
      if ( pActive != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pActive + 308))(pActive) != 0 )  // 目标存活
      {
        nDmgBlocked = sub_4AED20(nArg2);
        nVt5 = *(uint32_t *)nArg2;
        dwScratch = 100;
        nDmgType = (*(int (/*thiscall*/ **)(int, int *, int *))(nVt5 + 648))(nArg2, &dwScratch, this);  // vt+648 伤害类型
        if ( nDmgBlocked == 0 && nDmgType == 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pActive + 688))(pActive) + 20) != 0 )  // 虚函数调用 槽+688：附加块基址 this+6160
        {
          pEntry14 = (char *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 14);  // 14 号数据表
          nParam14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 14);  // 结果 = 虚调用 vt+1140
          nBaseParam = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);  // 结果 = 虚调用 vt+388
          nParam6 = sub_47EFD0(pEntry14, COERCE_FLOAT(6), nParam14, nBaseParam, nBaseParam, 0);  // 取 6 号参
          nBaseParam2 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);  // 结果 = 虚调用 vt+388
          nParam5 = sub_47EFD0(pEntry14, COERCE_FLOAT(5), nParam14, nBaseParam2, nBaseParam2, 0);  // 取 5 号参
          fld_e2135 = sub_423A80(nParam5, nParam6, *(this + 2135), dword_9B9340);  // 参数插值（进度 this+2135 → 时长）
          fld_e21352 = *(this + 2135);  // this+8540〔nPhaseStamp〕
          fld_e21353 = fld_e2135;
          nHitCount = 4;
          if ( fld_e21352 >= dword_9B9340 )  // 时长到点 → 追加多段
          {
            nSub4 = sub_47E9D0(pEntry14, 4u);  // 调 收招/结束例程
            nSub3 = sub_47E9D0(pEntry14, 3u);  // 调 收招/结束例程
            nVt6 = *this;
            nSub15 = 15;
            nBaseParam3 = (*(int (/*thiscall*/ **)(int *))(nVt6 + 388))(this);  // 虚函数调用 槽+388：属性块（vt+672(3)）首 DWORD
            nParam7 = sub_47EFD0(pEntry14, COERCE_FLOAT(7), nParam14, nBaseParam3, nBaseParam3, 0);  // 取 7 号参
            nHitCount = 14;
          }
          nVt7 = *this;
          nCastResult = (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int *))(*(uint32_t *)Block + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
                  Block,
                  0,
                  0,
                  0,
                  0,
                  0,
                  4,
                  0,
                  nHitCount,
                  &fld_e21353);  // 目标 vt+56 装配（段数=4/14）
          (*(void (/*thiscall*/ **)(int *, int, int))(nVt7 + 580))(this, 48028, nCastResult);  // 48028 号伤害/技能
        }
      }
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 14);  // 虚调用 vt+1160
      sub_47DCD0(this, -1);  // 调 震动/资源档位设置
      goto LABEL_43;
    default:
      break;
  }
  if ( fld_e16392 == 18  // 状态18 且 this+2100==4：连发 12/14/13 号计数复位
    && *(this + 2100) == 4  // this+8400〔pAppendage〕
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 12);  // 虚调用 vt+1160
    sub_47E440(1);
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 14);  // 虚调用 vt+1160
    sub_47E440(1);
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 13);  // 虚调用 vt+1160
    sub_47E440(1);
  }
  return sub_4AFB30(this, pColObj, (int)pArg3, nArg4);
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
void /*thiscall*/ sub_5DE690(int this)  // 函数定义: 白魔 WZ 每帧主状态机总入口（switch(this+6556) 大状态…
{
  double fDelayRet; // st7
  int fld_2184; // eax  | +0x2184 → ★ 相位阶段号（0x5DE690: 0→1→2 状态推进，驱动 sub_4BA730 与渐变）（CNMage；va=005DE690）
  int fld_21782; // eax  | +0x2178 → ★ 相位组索引（CNMage；va=005DE690）
  int fld_2178; // eax  | +0x2178 → ★ 相位组索引（CNMage；va=005DE690）
  int pThis_24; // eax
  int fld_2180; // edi  | +0x2180 → ★ 渐变 alpha（CNMage；va=005DE690）
  int fld_782; // edi  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主；0x5DE690 经此 +148 取剩余硬直）【基类字段】（CNMage；va=00499020）
  bool fld_78; // cc  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主；0x5DE690 经此 +148 取剩余硬直）【基类字段】（CNMage；va=00499020）
  int nVt1; // edi
  int pThis_494; // eax
  int fld_16C; // edx  | +0x016C → ★ 场景动画池指针（CNMage；va=005DE690）
  int hFollowMeAnim; // edi
  int *pFollowMeObj; // edi
  int fld_74; // ecx  | +0x0074 → 0x5DE690 读取槽（fld_74）（CNMage；va=005DE690）
  int pThis_11; // eax
  int nFollowMeVt1; // ebx
  int pThis_80; // eax
  int pThis_7C; // eax
  int nFollowMeVt2; // ebx
  int pThis_98; // eax
  int fld_2154; // eax  | +0x2154 → 0x5DE690 相位值 B（fld_2154）（CNMage；va=005DE690）
  int pThis_39C2; // edi
  int pThis_984; // eax
  int pThis_782; // eax
  int nVt2; // edx
  int nCastObjVt1; // ebx
  int nSelfZ2; // eax
  int pThis_7C3; // eax
  int pFlagField2; // eax
  void *fld_743; // ecx
  int fld_783; // ecx  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主；0x5DE690 经此 +148 取剩余硬直）【基类字段】（CNMage；va=00499020）
  bool fld_21842; // cc  | +0x2184 → ★ 相位阶段号（0x5DE690: 0→1→2 状态推进，驱动 sub_4BA730 与渐变）（CNMage；va=005DE690）
  int pThis_19A0; // eax
  int nAlpha; // eax
  int fld_2144; // eax  | +0x2144 → 0x5DE690 相位值 A（CNMage；va=005DE690）
  int nVt3; // edi
  int fld_2140; // eax  | +0x2140 → 0x5DE690: sub_432E50(*(this+8512)) 取值（CNMage；va=005DE690）
  int pThis_982; // eax
  int pThis_39C; // edi
  int pThis_983; // eax
  int nVt4; // edx
  int nCastObjVt2; // ebx
  int nSelfZ3; // eax
  int pThis_7C2; // eax
  int pThis_78; // eax
  int pFlagField; // eax
  void *fld_742; // ecx
  int *pSkillIt; // edi
  int fld_199C; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  int fld_20B4; // ecx  | +0x20B4 → 0x5DE690 累加值（fld_20B4，写入前读取）（CNMage；va=005DE690）
  int fld_199C2; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  bool pThis_308; // al
  int pThis_474; // eax
  int fld_199C3; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  int fld_199C4; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  int nLoopIdx; // edi
  int pThis_1FB4; // ecx
  int nSkillId; // eax
  int nCurCount; // ebx
  uint32_t *pMsgQ; // ebx
  int nMsgCode; // eax
  int nIdx; // ebx
  int pThis_488; // edi
  int pThis_4742; // eax
  int nDmgVal; // ebx
  int nSkillId2; // eax
  bool fld_199C5; // zf  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  int nTblVal; // eax
  char *pCurA; // edx
  uint32_t *pCurB; // edx
  int nSkillId3; // edi
  uint32_t *fld_217C2; // edx
  uint32_t *pCurC; // edx
  uint32_t *pCurD; // edx
  uint32_t *pCurE; // edx
  uint32_t *pCurF; // edx
  uint32_t *pCurG; // edx
  uint32_t *pCurH; // edx
  uint32_t *fld_199C62; // edx
  bool fld_20FC; // al  | +0x20FC → 0x5DE690: *(this+8444)!=-1 判据（CNMage；va=005DE690）
  int fld_199C7; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  uint32_t *pSkillPtr; // ebx
  int pThis_4882; // edi
  int pThis_4743; // ebx
  int nTblVal2; // eax
  int nLimitVal; // eax
  int nMatchVal; // eax
  int *pRangeIt1; // ecx
  uint32_t *pRangeIt2; // ecx
  char bInRange; // al
  uint32_t *pMsgQ2; // edi
  int nMsgCode2; // eax
  int nCount60006; // ebx
  uint32_t *pSkillPtr2; // ebx
  char *pCurI; // edx
  uint32_t *pCurJ; // edx
  int fld_217C3; // eax
  int nAtkVal; // eax
  char *pCurK; // ebx
  int nTblVal4; // eax
  char *pCurL; // ebx
  char *pCurM; // eax
  int fld_199C8; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  int fld_199C9; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  int fld_199C10; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  int fld_199C11; // eax  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  char pThis_3082; // [esp-4h] [ebp-58h]
  char fld_20FC2; // [esp-4h] [ebp-58h]
  char sStateBuf[4]; // [esp+Ch] [ebp-48h] BYREF
  void *pVecBegin; // [esp+10h] [ebp-44h]
  int nVecEnd; // [esp+14h] [ebp-40h]
  int nVecCap; // [esp+18h] [ebp-3Ch]
  char sStateBuf2[4]; // [esp+1Ch] [ebp-38h] BYREF
  void *Block; // [esp+20h] [ebp-34h]
  void *Src; // [esp+24h] [ebp-30h]
  int nVec2Cap; // [esp+28h] [ebp-2Ch]
  int fld_215C; // [esp+2Ch] [ebp-28h] BYREF  | +0x215C → ★ 相位时间戳（CNMage；va=005DE690）
  int fld_217C; // [esp+30h] [ebp-24h] BYREF  | +0x217C → ★ 相位已历时（CNMage；va=005DE690）
  int dwLoopCursor; // [esp+34h] [ebp-20h]
  int fld_199C6; // [esp+38h] [ebp-1Ch] BYREF
  int nStateParam2; // [esp+3Ch] [ebp-18h] BYREF
  int nStateParam3; // [esp+40h] [ebp-14h] BYREF
  bool bFacingLeft; // [esp+47h] [ebp-Dh]
  int nFreeState; // [esp+50h] [ebp-4h]

  sub_5DAC20();  // 倒计时槽计数广播（this+2062 存活门）
  fDelayRet = sub_5DAF10(this);  // 结果 = 延时播报到点触发：this+8596 时刻槽非 -1 且 dword_79D100 时钟已到
  sub_4B7430((int *)this, fDelayRet);  // 升级演出装配（LevelNormalizeLibra.ani + LevelNormaliz
  if ( *(uint32_t *)(this + 8568) != -1 )  // this+8568 相位组索引
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0  // 虚函数调用 槽+308
      && sub_699000(this + 36) >= *(uint32_t *)(this + 8572)  // 【clock_now(clk)】
      && (uint8_t)sub_4BFC10(this + 8116) == 0 )  // 全称判定（8 字节元素表）
    {
      pVecBegin = nullptr;
      nVecEnd = 0;
      nVecCap = 0;
      nFreeState = 0;
      fld_217C = 1;
      sub_431230(&fld_217C);  // uint32 vector push_back
      fld_217C = sub_699000(this + 36) - *(uint32_t *)(this + 8572);  // 【clock_now(clk)】
      sub_431230(&fld_217C);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 10, sStateBuf, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
      nFreeState = -1;
      sub_5E5260(sStateBuf);  // 调 动画子对象清理临时缓冲
    }
    fld_2184 = *(uint32_t *)(this + 8580);  // this+8580 相位阶段号
    if ( fld_2184 != 0 )
    {
      if ( fld_2184 == 1 )
      {
        if ( sub_699000(this + 36) >= *(uint32_t *)(this + 8572) + *(uint32_t *)(this + 8576)  // 【clock_now(clk)】
          && *(uint32_t *)(this + 616) == -1 )  // 涉及字段 “+616 受击反应态”
        {
          fld_2178 = sub_5DA1E0(*(uint32_t *)(this + 8568));  // 结果 = 索引→组号映射（nArg1>=55 归 4，否则查表 dword_738048；与 ·0x5
          sub_4BA730(1, fld_2178, 0, -*(uint32_t *)(this + 160));  // 魔能充能驱动（+204/+208/+216 槽；sub_493D00 变速；ENERGY_C
          *(uint32_t *)(this + 8580) = 2;  // this+8580 相位阶段号
        }
      }
      else if ( fld_2184 == 2 && sub_699000(this + 36) >= *(uint32_t *)(this + 8576) + *(uint32_t *)(this + 8572) + 200 )  // 【clock_now(clk)】
      {
        pThis_24 = sub_699000(this + 36);  // 【clock_now(clk)】
        fld_2180 = sub_42B420(255, 220, -200 - *(uint32_t *)(this + 8576) - *(uint32_t *)(this + 8572) + pThis_24, 100);  // 结果 = 往返插值（三角波）
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)this + 252))(this, 0, fld_2180);  // this+252 基类四元组 dword 槽 2
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 252))(this, 1, fld_2180);  // this+252 基类四元组 dword 槽 2
      }
    }
    else if ( sub_699000(this + 36) >= *(uint32_t *)(this + 8572) && *(uint32_t *)(this + 616) == -1 )  // 【clock_now(clk)】
    {
      fld_21782 = sub_5DA1E0(*(uint32_t *)(this + 8568));  // 结果 = 索引→组号映射（nArg1>=55 归 4，否则查表 dword_738048；与 ·0x5
      sub_4BA730(0, fld_21782, 0, -*(uint32_t *)(this + 160));  // 魔能充能驱动（+204/+208/+216 槽；sub_493D00 变速；ENERGY_C
      *(uint32_t *)(this + 8580) = 1;  // this+8580 相位阶段号
    }
  }
  switch ( *(uint32_t *)(this + 6556) )  // 大状态分派（0 序章/7-8 攻击/10 位姿/12 反应/14 召集/18-21 演出）
  {
    case 0:  // 序章待机
      if ( *(uint32_t *)(this + 8568) != -1 && *(uint32_t *)(this + 6644) != 0 )  // this+8568 相位组索引
        sub_5DACE0(this);  // 换锚重定（主状态镜像 +1639 为 0/11 且 this+2142 表参非 -1 时）
      break;
    case 7:  // 攻击段（动画帧 <2 时经 LABEL_32 播报一次）
      if ( *(uint8_t *)(this + 8220) == 0 )  // this+8220 抓取目标选择
      {
        fld_78 = *(uint32_t *)(*(uint32_t *)(this + 120) + 148) < 2;  // 涉及字段 “+120 动画对象”
        goto LABEL_32;
      }
      break;
    case 8:  // 攻击段：按 7028 段号查 dword_738604 帧表决定播报点
      if ( *(uint8_t *)(this + 8220) == 0 )  // this+8220 抓取目标选择
      {
        fld_782 = *(uint32_t *)(*(uint32_t *)(this + 120) + 148);  // 当前动画帧
        fld_78 = fld_782 < dword_738604[sub_41A5E0(this + 7028)];  // 帧表阈值（段号索引）
        goto LABEL_32;
      }
      break;
    case 0xA:  // 位姿同步态：双锚动画帧 ≥1 时 44/60 号位姿同步
      if ( *(uint32_t *)(this + 7812) == 0  // this+7812 子状态 A
        && *(uint32_t *)(this + 7828) == 0  // this+7828 子状态 D
        && *(uint32_t *)(this + 7816) == 11  // this+7816 子状态 B
        && *(uint32_t *)(this + 7808) == 1  // this+7808 风格/分支选择
        && *(int *)(*(uint32_t *)(this + 8428) + 148) >= 1 )  // this+8428 【推断】对象数组 cap
      {
        sub_5DB550(44, 60);  // 双锚位姿同步（v4=0/1 两挂点 this+8416 起步长 4）：vt+120/124/
      }
      break;
    case 0xC:  // 反应态 12：帧 3 时按 8228 标志决定收招或转相位 16
      if ( *(uint32_t *)(*(uint32_t *)(this + 120) + 148) == 3 )  // 判定 “+120 动画对象”
      {
        if ( *(uint8_t *)(this + 8228) != 0 )  // this+8228 0x5DE690: !=0 条件字节
        {
          sub_4AECE0(4);  // 调 切武器动画
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚函数调用 槽+308
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)this + 560))(this, 16, 0, 1, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
        }
      }
      if ( *(uint8_t *)(this + 8220) == 0 )  // this+8220 抓取目标选择
      {
        fld_78 = *(uint32_t *)(*(uint32_t *)(this + 120) + 148) < 2;  // 涉及字段 “+120 动画对象”
LABEL_32:
        if ( !fld_78 )
        {
          nVt1 = *(uint32_t *)this;
          pThis_494 = (*(int (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);  // 虚函数调用 槽+1172
          (*(void (/*thiscall*/ **)(int, int))(nVt1 + 212))(this, pThis_494);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
          *(uint8_t *)(this + 8220) = 1;  // this+8220 抓取目标选择
        }
      }
      break;
    case 0xE:  // 召集态：帧 30 一次性装载 FollowMeCast.ani 召集特效
      if ( *(uint32_t *)(this + 7964) == 30  // this+7964 技能号
        && *(uint8_t *)(this + 8376) == 0  // this+8376 【推断】特效/技能对象B
        && *(int *)(*(uint32_t *)(this + 120) + 148) >= 2 )  // 涉及字段 “+120 动画对象”
      {
        fld_215C = sub_42FCB0(228);  // 资源开关
        nFreeState = 1;
        if ( fld_215C != 0 )
        {
          if ( *(uint32_t *)(this + 384) < 0x10u )  // 判定 “+384 SSO容量”
            LOBYTE(fld_16C) = this + 108;  // this+108 第 1 组·宿主属性 +886 增量
          else
            fld_16C = *(uint32_t *)(this + 364);  // 读 fld_16C = this+364（场景动画池指针）
          hFollowMeAnim = sub_431920(fld_16C, (char)"Effect/Animation/FollowMeCast.ani", 1);  // 召集施法动画
        }
        else
        {
          hFollowMeAnim = 0;
        }
        nFreeState = -1;
        fld_215C = sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
        nFreeState = 2;
        if ( fld_215C != 0 )
          pFollowMeObj = (int *)sub_44E1F0(hFollowMeAnim, 1);  // 结果 = CNRDPooledObject 构造（虚表覆盖壳）
        else
          pFollowMeObj = nullptr;
        fld_74 = *(uint32_t *)(this + 116);  // 读 fld_74 = this+116（观察者容器）
        nFreeState = -1;
        sub_45FE80(fld_74, (int)pFollowMeObj, 2, 0, (int)pFollowMeObj, 0, 0);  // 挂到场景
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0 )  // this+152 第 4 组·+886 增量
          pThis_11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) + 17;  // 朝向→右侧17
        else
          pThis_11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - 17;  // 背向→左侧17
        nFollowMeVt1 = *pFollowMeObj;
        fld_217C = pThis_11;
        pThis_80 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // this+128 第 2 组·+1208 增量子倍率
        pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_80 + 81);  // Y偏移+81
        (*(void (/*thiscall*/ **)(int *, int, int))(nFollowMeVt1 + 112))(pFollowMeObj, fld_217C, pThis_7C);  // 落位
        nFollowMeVt2 = *pFollowMeObj;
        pThis_98 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // this+152 第 4 组·+886 增量
        (*(void (/*thiscall*/ **)(int *, int))(nFollowMeVt2 + 148))(pFollowMeObj, pThis_98);  // 对齐朝向
        *(uint8_t *)(this + 8376) = 1;  // 一次性门
      }
      break;
    case 0x12:  // 刺击态：帧≥4 播 PRICK
      if ( *(uint8_t *)(this + 8404) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 4 )  // 判定 “+120 动画对象”
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // this+212 【推断】子链状态槽
          this,
          "PRICK",  // 字符串 “PRICK”
          -1,
          0,
          0);
        *(uint8_t *)(this + 8404) = 1;  // this+8404 0x5DE690: ==0 且 *
      }
      break;
    case 0x13:  // 天击态：帧≥1 播 HEAVEN_HIT + WZ_HEAVEN_HIT，随后按弹体队列发 2103/2104
      if ( *(uint8_t *)(this + 8504) == 0 )  // this+8504 0x5DE690: ==0 判据字节
      {
        if ( *(int *)(*(uint32_t *)(this + 120) + 148) >= 1 )  // 判定 “+120 动画对象”
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚函数调用 槽+308
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
              this,
              0,
              500,
              500,
              0,
              -1500,
              1);
            nVt3 = *(uint32_t *)this;
            fld_2140 = sub_432E50(*(uint32_t *)(this + 8512));  // 结果 = 关系码对调映射
            pThis_982 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, fld_2140);  // this+152 第 4 组·+886 增量
            (*(void (/*thiscall*/ **)(int, int))(nVt3 + 896))(this, pThis_982);  // 虚函数调用 槽+896：默认虚槽桩（11 行 return）
          }
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // this+212 【推断】子链状态槽
            this,
            "HEAVEN_HIT",  // 字符串 “HEAVEN_HIT”
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // this+212 【推断】子链状态槽
            this,
            "WZ_HEAVEN_HIT",  // 字符串 “WZ_HEAVEN_HIT”
            -1,
            0,
            0);
          *(uint8_t *)(this + 8504) = 1;  // this+8504 0x5DE690: ==0 判据字节
        }
        if ( *(uint8_t *)(this + 8504) == 0  // this+8504 0x5DE690: ==0 判据字节
          && fabs(*(float *)(*(uint32_t *)(this + 112) + 20)) >= 20.0  // 竖直速度 ≥20（下落中）
          && sub_699000(this + 6560) >= *(uint32_t *)(this + 8508) + 150 )  // 【clock_now(clk)】冷却 150
        {
          pThis_39C = dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 924))(this, 2)];  // 全局弹体池[vt+924(2)]
          pThis_983 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // this+152 第 4 组·+886 增量
          nVt4 = *(uint32_t *)this;
          nCastObjVt2 = *(uint32_t *)pThis_39C;
          bFacingLeft = pThis_983 == 0;
          nSelfZ3 = (*(int (/*thiscall*/ **)(int))(nVt4 + 128))(this);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
          pThis_7C2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, nSelfZ3);  // this+124 第 2 组·+858/+1292 增量
          pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C2);  // this+120 动画对象指针
          (*(void (/*thiscall*/ **)(int, int))(nCastObjVt2 + 40))(pThis_39C, pThis_78);  // 弹体设坐标
          pFlagField = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_39C + 28))(pThis_39C);  // this+28 【推断】逐帧驱动对象
          *(uint8_t *)(pFlagField + 84) = bFacingLeft;  // 弹体朝向位
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pThis_39C + 12))(pThis_39C, 0);  // this+12 物品类型号
          (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pThis_39C + 92))(pThis_39C, sStateBuf2);  // 弹体序列化
          fld_742 = *(void **)(this + 116);  // this+116 0x5DE690 读取槽
          nFreeState = 4;
          sub_4600B0(fld_742, 2, 0, (int)sStateBuf2);  // 广播弹体包
          *(uint32_t *)(this + 8508) = sub_699000(this + 6560);  // 记发射时刻
          nFreeState = -1;
          sub_5E5260(sStateBuf2);  // 调 动画子对象清理临时缓冲
        }
      }
      break;
    case 0x14:  // 挥击态（8516==13 MAGE_SWING/WZ_SWING；==20 LESSON_START 教程）
      if ( *(uint8_t *)(this + 8520) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 3 )  // 判定 “+120 动画对象”
      {
        fld_2144 = *(uint32_t *)(this + 8516);  // this+8516 0x5DE690 相位值 A
        if ( fld_2144 == 13 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // this+212 【推断】子链状态槽
            this,
            "MAGE_SWING",  // 字符串 “MAGE_SWING”
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t, void *, int, int))(*(uint32_t *)this + 212))(  // this+212 【推断】子链状态槽
            this,
            "WZ_SWING",  // 字符串 “WZ_SWING”
            -1,
            0,
            0,
            pVecBegin,
            nVecEnd,
            nVecCap);
        }
        else if ( fld_2144 == 20 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // this+212 【推断】子链状态槽
            this,
            "LESSON_START",  // 字符串 “LESSON_START”
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t, void *, int, int))(*(uint32_t *)this + 212))(  // this+212 【推断】子链状态槽
            this,
            "R_WZ_LESSON_START",  // 字符串 “R_WZ_LESSON_START”
            -1,
            0,
            0,
            pVecBegin,
            nVecEnd,
            nVecCap);
        }
        *(uint8_t *)(this + 8520) = 1;  // this+8520 0x5DE690: ==0 且 *
      }
      break;
    case 0x15:  // 教学态：8532==1 时 57/63 位姿同步，否则下落触发弹体 + 屏幕白闪
      fld_2154 = *(uint32_t *)(this + 8532);  // this+8532 0x5DE690 相位值 B
      if ( fld_2154 != 0 )
      {
        if ( fld_2154 == 1 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 10 )  // 判定 “+120 动画对象”
          sub_5DB550(57, 63);  // 双锚位姿同步（v4=0/1 两挂点 this+8416 起步长 4）：vt+120/124/
      }
      else
      {
        if ( fabs(*(float *)(*(uint32_t *)(this + 112) + 16)) >= 20.0  // 水平速度 ≥20
          && sub_699000(this + 6560) >= *(uint32_t *)(this + 8548) + 200 )  // 【clock_now(clk)】冷却 200
        {
          pThis_39C2 = dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 924))(this, 2)];  // 弹体池
          pThis_984 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // this+152 第 4 组·+886 增量
          bFacingLeft = pThis_984 == 0;
          if ( pThis_984 != 0 )
            pThis_782 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - 20;  // 朝向→左20
          else
            pThis_782 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) + 20;  // 背向→右20
          nVt2 = *(uint32_t *)this;
          nCastObjVt1 = *(uint32_t *)pThis_39C2;
          fld_217C = pThis_782;
          nSelfZ2 = (*(int (/*thiscall*/ **)(int))(nVt2 + 128))(this);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
          pThis_7C3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, nSelfZ2);  // this+124 第 2 组·+858/+1292 增量
          (*(void (/*thiscall*/ **)(int, int, int))(nCastObjVt1 + 40))(pThis_39C2, fld_217C, pThis_7C3);  // 弹体设坐标
          pFlagField2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_39C2 + 28))(pThis_39C2);  // this+28 【推断】逐帧驱动对象
          *(uint8_t *)(pFlagField2 + 84) = bFacingLeft;
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pThis_39C2 + 12))(pThis_39C2, 0);  // this+12 物品类型号
          (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pThis_39C2 + 92))(pThis_39C2, sStateBuf2);  // this+92 插值起点 Z
          fld_743 = *(void **)(this + 116);  // this+116 0x5DE690 读取槽
          nFreeState = 3;
          sub_4600B0(fld_743, 2, 0, (int)sStateBuf2);  // 广播弹体包
          *(uint32_t *)(this + 8548) = sub_699000(this + 6560);  // clock_now(clk)
          nFreeState = -1;
          sub_5E5260(sStateBuf2);  // 调 动画子对象清理临时缓冲
        }
        fld_783 = *(uint32_t *)(this + 120);  // 读 fld_783 = this+120（动画对象）
        if ( *(int *)(fld_783 + 148) >= 7 && *(uint32_t *)(this + 8580) == 0 )  // 帧≥7 起屏幕表现
        {
          sub_4939E0(fld_783, 1);  // 播放/暂停级联（递归子链 +204）
          sub_4AECE0(7);  // 调 切武器动画
          sub_4939E0(*(uint32_t *)(this + 8544), 1);  // 播放/暂停级联（递归子链 +204）
          *(uint32_t *)(this + 8540) = sub_699000(this + 6560);  // clock_now(clk)
          sub_4BA610(4);  // 魔能充能动画选择（Character/Mage/Effect/Animation/Magic
          sub_4BA730(0, 4, 0, -106);  // BGM/演出通道 4
          *(uint32_t *)(this + 8580) = 1;  // this+8580 相位阶段号
        }
        fld_21842 = *(uint32_t *)(this + 8580) < 1;  // this+8580 相位阶段号
        if ( *(uint32_t *)(this + 8580) == 1 )  // this+8580 相位阶段号
        {
          if ( sub_699000(this + 6560) >= dword_9B9340 + *(uint32_t *)(this + 8540) )  // 【clock_now(clk)】+时长
          {
            sub_4BA730(1, 4, 0, -106);  // 魔能充能驱动（+204/+208/+216 槽；sub_493D00 变速；ENERGY_C
            *(uint32_t *)(this + 8580) = 2;  // this+8580 相位阶段号
          }
          fld_21842 = *(uint32_t *)(this + 8580) < 1;  // this+8580 相位阶段号
        }
        if ( !fld_21842 )
        {
          pThis_19A0 = sub_699000(this + 6560);  // 【clock_now(clk)】
          nAlpha = sub_42B420(150, 255, pThis_19A0, 150);  // 透明度插值 150→255（15 秒窗）
          sub_491F80(-1, -1, -1, nAlpha, 1);  // 屏幕染色渐变
        }
      }
      break;
    default:
      break;
  }
  if ( dword_8F7C04 == this && *(uint32_t *)(this + 200) != 2 )  // 全局 dword_8F7C04 = 本机角色对象
  {
    if ( *(uint32_t *)(this + 6556) == 10 && *(uint32_t *)(this + 7812) == 0 )  // 判定 “+6556 大状态ID”
    {
      if ( *(uint32_t *)(this + 7808) == 0  // this+7808 风格/分支选择
        && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 38) > 0  // 虚函数调用 槽+1140
        && *(uint32_t *)(this + 7820) == -1  // this+7820 【推断】交互信息快照对象
        && sub_699000(this + 36) >= *(uint32_t *)(this + 8572)  // 【clock_now(clk)】
        && ((*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1132))(this, 0) != 4  // this+1132 【推断】循环周期截止时刻
         || (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1132))(this, 1) != 4) )  // this+1132 【推断】循环周期截止时刻
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
      }
      if ( *(uint32_t *)(this + 7808) == 1  // this+7808 风格/分支选择
        && *(uint8_t *)(this + 8584) != 0  // this+8584 0x5DE690: !=0 判据字节
        && *(uint32_t *)(*(uint32_t *)(this + 112) + 192) == 4 )  // 涉及字段 “+112 宿主组件”
      {
        pVecBegin = nullptr;
        nVecEnd = 0;
        nVecCap = 0;
        nFreeState = 5;
        fld_217C = 2;
        sub_431230(&fld_217C);  // uint32 vector push_back
        fld_217C = 0;
        sub_431230(&fld_217C);  // uint32 vector push_back
        fld_217C = 0;
        sub_431230(&fld_217C);  // uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 6, sStateBuf, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
        nFreeState = -1;
        sub_5E5260(sStateBuf);  // 调 动画子对象清理临时缓冲
      }
    }
    if ( *(uint32_t *)(this + 6556) == 16 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )  // 判定 “+6556 大状态ID；+120 动画对象”
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 1, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
    pSkillIt = (int *)&unk_795930;
    do
    {
      fld_199C = *(uint32_t *)(this + 6556);  // 读 fld_199C = this+6556（大状态ID）
      if ( (fld_199C == 0 || fld_199C == 11)  // 若 fld_199C == 0 与/或 fld_199C == 11
        && sub_4842B0(*pSkillIt, nullptr) != -1  // 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, *pSkillIt) != 0 )  // this+1312 动画行向量 end
      {
        Block = nullptr;
        Src = nullptr;
        nVec2Cap = 0;
        fld_217C = *pSkillIt;
        nFreeState = 6;
        sub_431230(&fld_217C);  // uint32 vector push_back
        if ( *pSkillIt == 30 )
        {
          fld_20B4 = *(uint32_t *)(this + 8372);  // this+8372 0x5DE690 累加值
          if ( fld_20B4 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_20B4 + 80))(fld_20B4) != 0 )  // 虚函数调用 槽+80：槽（参数写入 3 转发）
          {
            fld_217C = 0;
            sub_431230(&fld_217C);  // uint32 vector push_back
          }
          else
          {
            fld_217C = 1;
            sub_431230(&fld_217C);  // uint32 vector push_back
          }
        }
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 14, sStateBuf2, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
        nFreeState = -1;
        if ( Block != nullptr )  // 若 Block 有效（非空）
          j__free(Block);  // 调 堆释放
        Block = nullptr;
        Src = nullptr;
        nVec2Cap = 0;
      }
      ++pSkillIt;
    }
    while ( (int)pSkillIt < (int)&dword_795948 );
    fld_199C2 = *(uint32_t *)(this + 6556);  // 读 fld_199C2 = this+6556（大状态ID）
    if ( (fld_199C2 == 4 || fld_199C2 == 3) && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 724))(this) == 0 )  // this+724 叉子攻击浮点
    {
      pThis_308 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 8) == 0  // 虚函数调用 槽+776：异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
         && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 16) == 0;  // 虚函数调用 槽+776：异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
      pThis_3082 = pThis_308;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 3);  // 虚函数调用 槽+1160
      sub_47E440(pThis_3082);
      if ( sub_4842B0(3, nullptr) != -1  // 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 3) != 0 )  // this+1312 动画行向量 end
      {
        pThis_474 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 3);  // 虚函数调用 槽+1140
        sub_5DCA10(pThis_474);  // 位移插值推进（this+6556 为 4/3 且 vt+724 静止门）：vt+776(8/
      }
    }
    if ( *(uint32_t *)(this + 6556) == 17 && sub_699000(this + 6560) >= *(uint32_t *)(this + 8396) )  // 【clock_now(clk)】
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
    fld_199C3 = *(uint32_t *)(this + 6556);  // 读 fld_199C3 = this+6556（大状态ID）
    if ( (fld_199C3 == 0 || fld_199C3 == 11)  // 若 fld_199C3 == 0 与/或 fld_199C3 == 11
      && sub_4842B0(4, nullptr) != -1  // 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 4) != 0 )  // this+1312 动画行向量 end
    {
      pVecBegin = nullptr;
      nVecEnd = 0;
      nVecCap = 0;
      nFreeState = 7;
      fld_217C = 4;
      sub_431230(&fld_217C);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 18, sStateBuf, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
      nFreeState = -1;
      if ( pVecBegin != nullptr )  // 若 pVecBegin 有效（非空）
        j__free(pVecBegin);  // 调 堆释放
    }
    if ( *(uint32_t *)(this + 6556) == 18 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )  // 判定 “+6556 大状态ID；+120 动画对象”
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
    fld_199C4 = *(uint32_t *)(this + 6556);  // 读 fld_199C4 = this+6556（大状态ID）
    if ( fld_199C4 == 0 || fld_199C4 == 11 || fld_199C4 == 8 || fld_199C4 == 6 )  // 若 fld_199C4 == 0 与/或 fld_199C4 == 11 与/或 fld_199C4 == 8
    {
      nLoopIdx = 0;
      dwLoopCursor = 0;
      do
      {
        pThis_1FB4 = sub_4842B0(dword_7958E8[nLoopIdx], (void *)(this + 8116));  // 结果 = 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
        nSkillId = dword_7958E8[nLoopIdx];
        fld_217C = pThis_1FB4;
        if ( nSkillId == 5 || nSkillId == 6 || nSkillId == 7 || nSkillId == 9 || nSkillId == 8 )  // 若 nSkillId == 5 与/或 nSkillId == 6 与/或 nSkillId == 7
        {
          if ( pThis_1FB4 == -1 )
            goto LABEL_246;
          nCurCount = sub_5DC170(0);  // 结果 = 本体所属追击弹收集器（唯一调用者链·0x5DC290/·0x5DC480/·0x5DCE00
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, dword_7958E8[nLoopIdx]);  // 虚函数调用 槽+1160
          if ( nCurCount >= sub_47E9D0(1) )  // 调 收招/结束例程
          {
            pMsgQ = *((uint32_t **)dword_8F8528 + 7);  // 全局 dword_8F8528 = 消息/弹窗管理器
            nMsgCode = sub_422E70(1205);  // 调 存 CStringManager::getStr 取本地化串
            sub_43BEE0(pMsgQ, nMsgCode, -6567706, 0, -1);  // 调 【播报上屏】
            goto LABEL_246;
          }
          pThis_1FB4 = fld_217C;
        }
        if ( pThis_1FB4 != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, dword_7958E8[nLoopIdx]) != 0 )  // this+1312 动画行向量 end
        {
          nIdx = dwLoopCursor;
          pThis_488 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, dword_7958E8[dwLoopCursor]);  // 虚函数调用 槽+1160
          pThis_4742 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, dword_7958E8[nIdx]);  // 虚函数调用 槽+1140
          nDmgVal = 0;
          nStateParam2 = 0;
          nStateParam3 = 0;
          fld_199C6 = 0;
          if ( pThis_4742 == -1 )
            pThis_4742 = sub_41A5E0(pThis_488 + 510);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          fld_217C = sub_41A5E0(*(uint32_t *)(pThis_488 + 316) + 14 * (pThis_4742 - 1));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          nSkillId2 = dword_7958E8[dwLoopCursor];
          switch ( nSkillId2 )  // 按 nSkillId2 分派
          {
            case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
            case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
            case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
            case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
            case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
            case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
              nTblVal = sub_47E9D0(0);  // 调 收招/结束例程
LABEL_197:
              nStateParam3 = 3;
LABEL_198:
              nDmgVal = nTblVal;
              nStateParam2 = nTblVal;
              break;
            case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
              nDmgVal = sub_47E9D0(0);  // 调 收招/结束例程
              nStateParam2 = nDmgVal;
              nStateParam3 = 0;
              fld_199C6 = sub_47E9D0(3);  // 调 收招/结束例程
              break;
            case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
              nDmgVal = sub_47E9D0(0);  // 调 收招/结束例程
              fld_199C5 = *(uint32_t *)(this + 6556) == 6;  // 涉及字段 “+6556 大状态ID”
              nStateParam2 = nDmgVal;
              nStateParam3 = 1;
              if ( fld_199C5 || (fld_199C6 = sub_47E9D0(1), *(uint32_t *)(this + 6556) == 6) )  // 调 收招/结束例程
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 42);  // 虚函数调用 槽+1160
                fld_217C = fld_217C * sub_47E9D0(2) / 100;  // 调 收招/结束例程
              }
              break;
            case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
              nDmgVal = sub_47E9D0(0);  // 调 收招/结束例程
              nStateParam2 = nDmgVal;
              nStateParam3 = 3;
              fld_199C6 = sub_47E9D0(5);  // 调 收招/结束例程
              break;
            case 17:  // case 17 = ENUM_CMDPACKET_SELECT_DUNGEON
              nDmgVal = sub_47E9D0(0);  // 调 收招/结束例程
              nStateParam2 = nDmgVal;
              nStateParam3 = 2;
              fld_199C6 = sub_47E9D0(2);  // 调 收招/结束例程
              break;
            case 18:  // case 18 = ENUM_CMDPACKET_SEND_MESSAGE
              nDmgVal = sub_47E9D0(0);  // 调 收招/结束例程
              nStateParam2 = nDmgVal;
              nStateParam3 = 0;
              fld_199C6 = sub_47E9D0(1);  // 调 收招/结束例程
              break;
            case 26:  // case 26 = ENUM_CMDPACKET_REPAIR_EQUIPMENT
            case 27:  // case 27 = ENUM_CMDPACKET_SET_ITEMTRADE_STATE
              nDmgVal = sub_47E9D0(0);  // 调 收招/结束例程
              nStateParam3 = 1;
              nStateParam2 = nDmgVal;
              fld_199C6 = sub_47E9D0(2);  // 调 收招/结束例程
              break;
            case 28:  // case 28 = ENUM_CMDPACKET_COMPOUND_ITEM
              nTblVal = sub_47E9D0(0);  // 调 收招/结束例程
              nStateParam3 = 2;
              goto LABEL_198;
            case 31:  // case 31 = ENUM_CMDPACKET_CHANGE_SKILLSLOT
              nDmgVal = 10000;
              nStateParam3 = 3;
              nStateParam2 = 10000;
              fld_199C6 = sub_47E9D0(0);  // 调 收招/结束例程
              break;
            case 43:  // case 43 = ENUM_CMDPACKET_DIE_MONSTER
              goto LABEL_195;
            case 49:  // case 49 = ENUM_CMDPACKET_MOVE_MAP
              nTblVal = sub_47E9D0(2);  // 调 收招/结束例程
              goto LABEL_197;
            case 50:  // case 50 = ENUM_CMDPACKET_SET_PLAY_RESULT
LABEL_195:
              nTblVal = sub_47E9D0(0);  // 调 收招/结束例程
              nStateParam3 = 0;
              goto LABEL_198;
            default:
              break;
          }
          Block = nullptr;
          Src = nullptr;
          nVec2Cap = 0;
          nFreeState = 8;
          fld_215C = 0;
          sub_430C80(nullptr, 1, (int)&fld_215C);  // uint32 vector 区间插入（同值填充）
          pCurA = (char *)Src;
          fld_215C = 0;
          if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
          {
            *(uint32_t *)Src = 0;
            pCurB = pCurA + 4;
            Src = pCurB;
          }
          else
          {
            sub_430C80(Src, 1, (int)&fld_215C);  // uint32 vector 区间插入（同值填充）
            pCurB = Src;
          }
          nSkillId3 = dword_7958E8[dwLoopCursor];
          fld_215C = nSkillId3;
          if ( Block != nullptr && ((char *)pCurB - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
          {
            *pCurB = nSkillId3;
            fld_217C2 = pCurB + 1;
            Src = fld_217C2;
          }
          else
          {
            sub_430C80(pCurB, 1, (int)&fld_215C);  // uint32 vector 区间插入（同值填充）
            fld_217C2 = Src;
          }
          if ( Block != nullptr && ((char *)fld_217C2 - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
          {
            *fld_217C2 = fld_217C;
            pCurC = fld_217C2 + 1;
            Src = pCurC;
          }
          else
          {
            sub_430C80(fld_217C2, 1, (int)&fld_217C);  // uint32 vector 区间插入（同值填充）
            pCurC = Src;
          }
          if ( Block != nullptr && ((char *)pCurC - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
          {
            *pCurC = nDmgVal;
            pCurD = pCurC + 1;
            Src = pCurD;
          }
          else
          {
            sub_430C80(pCurC, 1, (int)&nStateParam2);  // uint32 vector 区间插入（同值填充）
            pCurD = Src;
          }
          if ( Block != nullptr && ((char *)pCurD - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
          {
            *pCurD = nStateParam3;
            pCurE = pCurD + 1;
            Src = pCurE;
          }
          else
          {
            sub_430C80(pCurD, 1, (int)&nStateParam3);  // uint32 vector 区间插入（同值填充）
            pCurE = Src;
          }
          fld_215C = 4;
          if ( Block != nullptr && ((char *)pCurE - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
          {
            *pCurE = 4;
            pCurF = pCurE + 1;
            Src = pCurF;
          }
          else
          {
            sub_430C80(pCurE, 1, (int)&fld_215C);  // uint32 vector 区间插入（同值填充）
            pCurF = Src;
          }
          fld_215C = 4;
          if ( Block != nullptr && ((char *)pCurF - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
          {
            *pCurF = 4;
            pCurG = pCurF + 1;
            Src = pCurG;
          }
          else
          {
            sub_430C80(pCurF, 1, (int)&fld_215C);  // uint32 vector 区间插入（同值填充）
            pCurG = Src;
          }
          if ( fld_199C6 > 0 || *(uint32_t *)(this + 6556) == 6 )  // 判定 “+6556 大状态ID”
          {
            fld_215C = 1000;
            if ( Block != nullptr && ((char *)pCurG - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
            {
              *pCurG = 1000;
              pCurH = pCurG + 1;
              Src = pCurH;
            }
            else
            {
              sub_430C80(pCurG, 1, (int)&fld_215C);  // uint32 vector 区间插入（同值填充）
              pCurH = Src;
            }
            fld_215C = 1000;
            if ( Block != nullptr && ((char *)pCurH - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
            {
              *pCurH = 1000;
              fld_199C62 = pCurH + 1;
              Src = fld_199C62;
            }
            else
            {
              sub_430C80(pCurH, 1, (int)&fld_215C);  // uint32 vector 区间插入（同值填充）
              fld_199C62 = Src;
            }
            if ( Block != nullptr && ((char *)fld_199C62 - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
            {
              *fld_199C62 = fld_199C6;
              Src = fld_199C62 + 1;
            }
            else
            {
              sub_430C80(fld_199C62, 1, (int)&fld_199C6);  // uint32 vector 区间插入（同值填充）
            }
            if ( *(uint32_t *)(this + 6556) == 6 )  // 判定 “+6556 大状态ID”
            {
              fld_215C = 1;
              sub_431230(&fld_215C);  // uint32 vector push_back
            }
          }
          (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 10, sStateBuf2, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
          nFreeState = -1;
          if ( Block != nullptr )  // 若 Block 有效（非空）
            j__free(Block);  // 调 堆释放
          Block = nullptr;
          Src = nullptr;
          nVec2Cap = 0;
          nLoopIdx = dwLoopCursor;
        }
LABEL_246:
        dwLoopCursor = ++nLoopIdx;
      }
      while ( nLoopIdx < 18 );
    }
    fld_20FC = *(uint32_t *)(this + 8444) != -1  // this+8444 0x5DE690: *
       && *(uint32_t *)(this + 8440) != 0  // this+8440 0x5DE690: *
       && sub_699000(this + 36) < *(uint32_t *)(this + 8444)  // 【clock_now(clk)】
       && (uint8_t)sub_5DB490(this) != 0;  // 本体追击弹存在性查询：遍历 this[29] 碰撞对象表 RTTI cast 到 CNCha
    fld_20FC2 = fld_20FC;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 39);  // 虚函数调用 槽+1160
    sub_47E440(fld_20FC2);
    if ( sub_4842B0(39, nullptr) != -1  // 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 39) != 0 )  // this+1312 动画行向量 end
    {
      sub_5DCE00(*(uint32_t *)(this + 8440));  // 追击弹命中播报：nArg2 非 0 时·sub_5DC170 收集现存弹，取首弹 obj+9
    }
    fld_199C7 = *(uint32_t *)(this + 6556);  // 读 fld_199C7 = this+6556（大状态ID）
    if ( fld_199C7 == 0 || fld_199C7 == 11 )  // 若 fld_199C7 == 0 与/或 fld_199C7 == 11
    {
      dwLoopCursor = (int)&unk_737FFC;
      do
      {
        if ( sub_4842B0(*(uint32_t *)dwLoopCursor, nullptr) != -1 )  // 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
        {
          pSkillPtr = (uint32_t *)dwLoopCursor;
          pThis_4882 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1160))(this, *(uint32_t *)dwLoopCursor);  // 虚函数调用 槽+1160
          pThis_4743 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1140))(this, *pSkillPtr);  // 虚函数调用 槽+1140
          fld_217C = pThis_4743;
          nTblVal2 = sub_47E9D0(2);  // 调 收招/结束例程
          fld_215C = sub_5DD040(nTblVal2, 0, 1);  // 结果 = 召唤物/弹体筛选收集（this[29] 碰撞表）：先按 pArg3 清空出口表，nArg2
          nLimitVal = sub_47EF20(2, pThis_4743, -1, -1, 11);  // 调 读攻击数据表
          if ( fld_215C < nLimitVal )
          {
            if ( (int)sub_47E9D0(7) <= 0 || (nCount60006 = sub_5DD040(60006, 0, 1)) >= sub_47E9D0(7) )  // 调 收招/结束例程
            {
              pSkillPtr2 = (uint32_t *)dwLoopCursor;
              if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1312))(this, *(uint32_t *)dwLoopCursor) != 0 )  // this+1312 动画行向量 end
              {
                Block = nullptr;
                Src = nullptr;
                nVec2Cap = 0;
                nFreeState = 9;
                fld_215C = 0;
                sub_430C80(nullptr, 1, (int)&fld_215C);  // uint32 vector 区间插入（同值填充）
                pCurI = (char *)Src;
                fld_215C = 0;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = 0;
                  pCurJ = pCurI + 4;
                  Src = pCurJ;
                }
                else
                {
                  sub_430C80(Src, 1, (int)&fld_215C);  // uint32 vector 区间插入（同值填充）
                  pCurJ = Src;
                }
                if ( Block != nullptr && ((char *)pCurJ - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
                {
                  *pCurJ = *pSkillPtr2;
                  Src = pCurJ + 1;
                }
                else
                {
                  sub_430C80(pCurJ, 1, (int)pSkillPtr2);  // uint32 vector 区间插入（同值填充）
                }
                fld_217C3 = fld_217C;
                if ( fld_217C == -1 )
                  fld_217C3 = sub_41A5E0(pThis_4882 + 510);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
                nAtkVal = sub_41A5E0(*(uint32_t *)(pThis_4882 + 316) + 14 * (fld_217C3 - 1));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
                pCurK = (char *)Src;
                fld_217C = nAtkVal;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = fld_217C;
                  Src = pCurK + 4;
                }
                else
                {
                  sub_430C80(Src, 1, (int)&fld_217C);  // uint32 vector 区间插入（同值填充）
                }
                nTblVal4 = sub_47E9D0(4);  // 调 收招/结束例程
                pCurL = (char *)Src;
                fld_217C = nTblVal4;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = fld_217C;
                  Src = pCurL + 4;
                }
                else
                {
                  sub_430C80(Src, 1, (int)&fld_217C);  // uint32 vector 区间插入（同值填充）
                }
                fld_217C = sub_47E9D0(3);  // 调 收招/结束例程
                pCurM = (char *)Src;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((nVec2Cap - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = fld_217C;
                  Src = pCurM + 4;
                }
                else
                {
                  sub_430FB0((int)&fld_215C, Src, (int)&fld_217C);  // 单元素插入（返回新位置）
                }
                fld_215C = 4;
                sub_431230(&fld_215C);  // uint32 vector push_back
                fld_215C = 4;
                sub_431230(&fld_215C);  // uint32 vector push_back
                (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 10, sStateBuf2, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
                nFreeState = -1;
                if ( Block != nullptr )  // 若 Block 有效（非空）
                  j__free(Block);  // 调 堆释放
                Block = nullptr;
                Src = nullptr;
                nVec2Cap = 0;
              }
              goto LABEL_300;
            }
            pMsgQ2 = *((uint32_t **)dword_8F8528 + 7);  // 全局 dword_8F8528 = 消息/弹窗管理器
            nMsgCode2 = sub_422E70(2104);  // 调 存 CStringManager::getStr 取本地化串
          }
          else
          {
            nMatchVal = sub_47E9D0(2);  // 调 收招/结束例程
            pRangeIt1 = &dword_738020;
            while ( nMatchVal != *pRangeIt1 )  // 当 nMatchVal != *pRangeIt1 循环
            {
              if ( (int)++pRangeIt1 >= (int)&dword_738030 )
              {
                pRangeIt2 = &unk_738040;
                while ( nMatchVal != *pRangeIt2 )  // 当 nMatchVal != *pRangeIt2 循环
                {
                  if ( (int)++pRangeIt2 >= (int)&dword_738044 )
                  {
                    bInRange = 0;
                    goto LABEL_268;
                  }
                }
                break;
              }
            }
            bInRange = 1;
LABEL_268:
            pMsgQ2 = *((uint32_t **)dword_8F8528 + 7);  // 全局 dword_8F8528 = 消息/弹窗管理器
            nMsgCode2 = sub_422E70(bInRange != 0 ? 2103 : 1);  // 调 存 CStringManager::getStr 取本地化串
          }
          sub_43BEE0(pMsgQ2, nMsgCode2, -6567706, 0, -1);  // 调 【播报上屏】
        }
LABEL_300:
        dwLoopCursor += 4;
      }
      while ( dwLoopCursor < (int)&dword_738020 );
    }
    fld_199C8 = *(uint32_t *)(this + 6556);  // 读 fld_199C8 = this+6556（大状态ID）
    if ( (fld_199C8 == 0 || fld_199C8 == 11 || fld_199C8 == 8 || fld_199C8 == 18)  // 若 fld_199C8 == 0 与/或 fld_199C8 == 11 与/或 fld_199C8 == 8
      && sub_4842B0(12, nullptr) != -1  // 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 12) != 0 )  // this+1312 动画行向量 end
    {
      pVecBegin = nullptr;
      nVecEnd = 0;
      nVecCap = 0;
      nFreeState = 10;
      fld_215C = 12;
      sub_431230(&fld_215C);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 19, sStateBuf, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
      nFreeState = -1;
      if ( pVecBegin != nullptr )  // 若 pVecBegin 有效（非空）
        j__free(pVecBegin);  // 调 堆释放
    }
    if ( *(uint32_t *)(this + 6556) == 19 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )  // 判定 “+6556 大状态ID；+120 动画对象”
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
    fld_199C9 = *(uint32_t *)(this + 6556);  // 读 fld_199C9 = this+6556（大状态ID）
    if ( (fld_199C9 == 0 || fld_199C9 == 11 || fld_199C9 == 18)  // 若 fld_199C9 == 0 与/或 fld_199C9 == 11 与/或 fld_199C9 == 18
      && sub_4842B0(13, nullptr) != -1  // 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 13) != 0 )  // this+1312 动画行向量 end
    {
      pVecBegin = nullptr;
      nVecEnd = 0;
      nVecCap = 0;
      nFreeState = 11;
      fld_215C = 13;
      sub_431230(&fld_215C);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 20, sStateBuf, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
      nFreeState = -1;
      if ( pVecBegin != nullptr )  // 若 pVecBegin 有效（非空）
        j__free(pVecBegin);  // 调 堆释放
    }
    fld_199C10 = *(uint32_t *)(this + 6556);  // 读 fld_199C10 = this+6556（大状态ID）
    if ( (fld_199C10 == 0 || fld_199C10 == 11)  // 若 fld_199C10 == 0 与/或 fld_199C10 == 11
      && sub_4842B0(20, nullptr) != -1  // 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 20) != 0 )  // this+1312 动画行向量 end
    {
      pVecBegin = nullptr;
      nVecEnd = 0;
      nVecCap = 0;
      nFreeState = 12;
      fld_215C = 20;
      sub_431230(&fld_215C);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 20, sStateBuf, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
      nFreeState = -1;
      if ( pVecBegin != nullptr )  // 若 pVecBegin 有效（非空）
        j__free(pVecBegin);  // 调 堆释放
    }
    if ( *(uint32_t *)(this + 6556) == 20 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )  // 判定 “+6556 大状态ID；+120 动画对象”
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
    fld_199C11 = *(uint32_t *)(this + 6556);  // 读 fld_199C11 = this+6556（大状态ID）
    if ( (fld_199C11 == 0 || fld_199C11 == 11 || fld_199C11 == 8 || fld_199C11 == 18)  // 若 fld_199C11 == 0 与/或 fld_199C11 == 11 与/或 fld_199C11 == 8
      && sub_4842B0(14, (void *)(this + 8116)) != -1  // 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 14) != 0 )  // this+1312 动画行向量 end
    {
      pVecBegin = nullptr;
      nVecEnd = 0;
      nVecCap = 0;
      nFreeState = 13;
      fld_215C = 0;
      sub_431230(&fld_215C);  // uint32 vector push_back
      fld_215C = 14;
      sub_431230(&fld_215C);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 21, sStateBuf, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
      nFreeState = -1;
      if ( pVecBegin != nullptr )  // 若 pVecBegin 有效（非空）
        j__free(pVecBegin);  // 调 堆释放
    }
    if ( *(uint32_t *)(this + 6556) == 21 )  // 判定 “+6556 大状态ID”
    {
      if ( *(uint32_t *)(this + 8532) == 0  // this+8532 0x5DE690 相位值 B
        && *(uint32_t *)(*(uint32_t *)(this + 120) + 148) == 7  // 涉及字段 “+120 动画对象”
        && (uint8_t)sub_4BFC10(this + 8116) == 0 )  // 全称判定（8 字节元素表）
      {
        pVecBegin = nullptr;
        nVecEnd = 0;
        nVecCap = 0;
        nFreeState = 14;
        fld_215C = 1;
        sub_431230(&fld_215C);  // uint32 vector push_back
        fld_215C = sub_699000(this + 6560) - *(uint32_t *)(this + 8540);  // 【clock_now(clk)】
        sub_431230(&fld_215C);  // uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 21, sStateBuf, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
        if ( sub_699000(this + 6560) == *(uint32_t *)(this + 8540) )  // 【clock_now(clk)】
          sub_4BA730(2, 4, 0, 0);  // 魔能充能驱动（+204/+208/+216 槽；sub_493D00 变速；ENERGY_C
        nFreeState = -1;
        if ( pVecBegin != nullptr )  // 若 pVecBegin 有效（非空）
          j__free(pVecBegin);  // 调 堆释放
        pVecBegin = nullptr;
        nVecEnd = 0;
        nVecCap = 0;
      }
      if ( *(uint32_t *)(this + 8532) == 1 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )  // 判定 “+120 动画对象”
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
    }
  }
}

