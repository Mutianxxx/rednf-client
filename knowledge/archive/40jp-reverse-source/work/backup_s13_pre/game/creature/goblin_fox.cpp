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
// 0x5908C0 sub_5908C0 —— 子类 AI 状态复位（出场演出标志清零）
// 清 this+8600/8604/8605 三个子类 AI 字节：this+8604=出场动作已设标志、
// this+8605=KENSIN_APPEAR 已播标志（均为 sub_590970 的一次性演出门），
// 复位后下次登场可重走出场演出【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5908C0(int this)  // 实现：子类 AI 状态复位（出场演出标志清零）
{
  *(uint32_t *)(this + 8600) = 0;  // this+8600〔uAI8600(推断)〕
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 0;  // this+8605〔bAI8605(推断)〕
  return 0;
}



// 标志复位：this+8605=0；vt+648(伤害类型槽, 研究 20 §1.2) 掩码读回
// ------------------------------------------------------------
// 0x5908E0 sub_5908E0 —— 标志复位（APPEAR 已播标志清零）
// this+8605 清零允许重播 KENSIN_APPEAR；this+648 字段掩码清 bit0 后把原值返回
// （实例字段位标志，语义未定；与 vt+648 伤害类型槽并非同一物【推断】）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5908E0(int this)  // 实现：标志复位（APPEAR 已播标志清零）
{
  unsigned int result; // eax

  result = *(uint32_t *)(this + 648) & 0xFFFFFFFE;  // this+648〔uMonFlagBits〕
  *(uint8_t *)(this + 8605) = 0;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 648) = result;  // this+648〔uMonFlagBits〕
  return result;
}



// AI 触发阈值装载：__RTDynamicCast→CNFighter 后 vt+1160/vt+1140(8) 取计数，
//   sub_47EF20(1,…,11) 读数据表元素(研究 17/20 平衡读数族) → 存 this+2150 供时钟门比较
// ------------------------------------------------------------
// 0x590900 sub_590900 —— 阈值A装载（宿主 CNFighter 战斗读数）
// nArg2 为宿主/施法者对象：sub_4D9F50 写骑乘/宿主槽（this+8352 双写）→
// RTTI 转型 CNFighter → vt+1160/vt+1140(8) 取计数 → sub_47EF20(1,…,11) 数据表读数
// → 存 this+2150（sub_590970 出场时钟门的比较阈值）
// ------------------------------------------------------------
int /*thiscall*/ sub_590900(uint32_t *this, int nArg2)  // 实现：阈值A装载（宿主 CNFighter 战斗读数）
{
  int result; // eax
  int pObj; // esi
  int v5; // eax

  sub_4D9F50(nArg2);  // 骑乘/宿主槽写入（this+8352 双写）
  result = __RTDynamicCast(nArg2, 0, &IRDActiveObject `RTTI Type Descriptor', &CNFighter `RTTI Type Descriptor', 0);  // result = 调 __RTDynamicCast
  pObj = result;
  if ( result != 0 )  // 若结果非 0（成功）
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 1160))(result, 8);  // 调虚槽 +1160
    v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, 8);  // 调虚槽 +1140
    result = sub_47EF20(1, v5, -1, -1, 11);  // result = 调 sub_47EF20 返回值
    *(this + 2150) = result;  // this+8600〔uAI8600(推断)〕
  }
  return result;
}



// 【AI 相位：出场/近身检查】KENSIN_APPEAR 播报；sub_699000 时钟 >= this+2150 门通过后
//   sub_431230 打包参数表 → vt+560(this,5,…,2) 反应态写入(研究 15 vt+560=sub_4E7A80)
// ------------------------------------------------------------
// 0x590970 sub_590970 —— 出场技能演出主函数（KENSIN_APPEAR）
// 帧驱动出场相位：vt+124/vt+120/vt+136 接近检查，失败则 vt+84 停移动并置
// this+8605=1 抑制后续播报【推断】；存活(vt+308) 且主状态 this+1639==0 且
// clock_now(this+16) ≥ 阈值A this+2150 时，sub_431230 打包参数 → vt+560 写反应态 5
// （setState 族 sub_4E7A80，研究 15）；this+8604 门内经 this+1554 出场数据由
// vt+208/vt+196/vt+204 一次性设动作；末段 this+8605 门内 vt+212 播 KENSIN_APPEAR
// ------------------------------------------------------------
void /*thiscall*/ sub_590970(int *this)  // 实现：出场技能演出主函数（KENSIN_APPEAR）
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int fld_e30; // eax | =+0x0078 字段 x6（证据 00499020）
  uint8_t v6[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v8; // [esp+14h] [ebp-18h]
  int v9; // [esp+18h] [ebp-14h]
  int v10; // [esp+1Ch] [ebp-10h] BYREF
  int v11; // [esp+28h] [ebp-4h]

  sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v3);  // 调虚槽 +120：动画对象
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v2 + 136))(this, v4) == 0 )  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 84))(this, 0);  // 调虚槽 +84：CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
    *((uint8_t *)this + 8605) = 1;  // this+8605〔门内〕
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && *(this + 1639) == 0  // this+6556〔大状态ID〕
    && sub_699000((int)(this + 16)) >= *(this + 2150) )  // 【clock_now(clk)】
  {
    Block = nullptr;  // Block = 空指针
    v8 = 0;
    v9 = 0;
    v11 = 0;
    v10 = 0;
    sub_431230((int)v6, &v10);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(int *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 5, v6, 2, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    v11 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
    Block = nullptr;  // Block = 空指针
    v8 = 0;
    v9 = 0;
  }
  if ( *((uint8_t *)this + 8604) == 0 )  // this+8604〔bAI8604(推断)〕
  {
    fld_e30 = *(this + 30);  // this+120〔pAnimObj〕
    if ( fld_e30 != 0 && *(uint8_t *)(fld_e30 + 170) != 0 )  // 若 fld_e30 != 0
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));  // 调虚槽 +208：定时器移除
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
        this,
        1,
        *(uint32_t *)(*(this + 1554) + 8),  // this+6216〔pTbl6216(推断)〕
        0,
        0,
        0,
        0);
      *((uint8_t *)this + 8604) = 1;  // this+8604〔bAI8604(推断)〕
    }
  }
  if ( *((uint8_t *)this + 8605) == 0 )  // this+8605〔bAI8605(推断)〕
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "KENSIN_APPEAR", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    *((uint8_t *)this + 8605) = 1;  // this+8605〔门内〕
  }
}



// 【vmt200 命中处理器覆写】受击处理·直接伤害版（虚表 0x6CD0EC +512 槽）：vt+348 attackinfo → vt+648 类型 →
//   vt+628 伤害公式 → vt+736 GetHP 钳制 → sub_41A5E0 防篡读(研究 17) → vt+728 HP setter
//   → sub_4D5330 DNF.trc 日志；霸体门 vt+724 内 vt+560 反应态 5(击倒)；
//   无 50% 预表现/暴击分支 —— 对照基类 0x4D71B0 全流程（研究 20 §2）
// ------------------------------------------------------------
// 0x590AD0 sub_590AD0 —— 受击处理·直接伤害版（vmt200 命中槽覆写）
// 命中链：攻击者 nArg3 经 vt+348 取 attackinfo（+60 附加值）→ vt+648 伤害类型 →
// vt+628 伤害公式 → 与 vt+736 GetHP 取小钳制 → sub_41A5E0 守护读 this+1533 →
// vt+728 HP setter 扣血 → sub_4D5330 写 DNF.trc 伤害日志（研究 §2⑦）；
// 霸体检查 vt+724 非零时经 sub_431230 打包走 vt+560 反应态 5（击倒）；
// 较基类直伤流程无 50% 预表现与暴击分支（研究 20 §2），返回实际伤害值
// ------------------------------------------------------------
int /*userpurge*/ sub_590AD0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3, int nArg4, int nArg5)  // 实现：受击处理·直接伤害版（vmt200 命中槽覆写）
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

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) == 0 || (uint8_t)nArg5 != 0 )  // 调虚槽 +308：是否本地玩家
    return -1;
  nArg32 = nArg3;
  v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 348))(nArg3, nArg2);  // 调虚槽 +348：取坐标对象
  v8 = *pDwArg1;
  v19 = *(uint32_t *)(v7 + 60);
  LOBYTE(v21[0]) = 0;
  nArg5 = 100;
  nArg3 = 0;
  v9 = (*(int (/*thiscall*/ **)(int *, int *, int))(v8 + 648))(pDwArg1, &nArg5, nArg32);  // 调虚槽 +648：写入 100（格挡/减伤基础值槽）
  v10 = *pDwArg1;
  v18 = v9;
  v11 = (*(int (/*thiscall*/ **)(int *, uint32_t *, int *, int, int, int, uint32_t))(v10 + 628))(pDwArg1, v21, &nArg3, nArg5, nArg32, nArg4, 0);  // 调虚槽 +628：伤害流水线九步
  if ( v11 >= (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 736))(pDwArg1) )  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
    v20 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 736))(pDwArg1);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
  else  // 否则分支
    v20 = v11;
  v12 = sub_41A5E0((unsigned int)(pDwArg1 + 1533));  // crypt4byte 解密校验（·0x41A590 逆运算）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*pDwArg1 + 728))(pDwArg1, v12 - v11, 0);  // 调虚槽 +728：HP setter/扣血
  if ( v11 != 0 || v19 != 0 )  // 若 v11 != 0 与/或 v19 != 0
    sub_4D5330(nArg32, pDwArg1, nArg4, v11, v20, v21[0], nArg3, v18);  // 伤害日志写出（DNF.trc；研究 §2⑦ 定案勿与 HP setter 混淆）
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 724))(pDwArg1) != 0 )  // 调虚槽 +724：读 +6552 霸体字节
  {
    Block = nullptr;  // Block = 空指针
    v16 = 0;
    v17 = 0;
    v21[3] = 0;
    nArg4 = 0;
    sub_431230((int)v14, &nArg4);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(int *, int, uint8_t *, int, uint32_t))(*pDwArg1 + 560))(pDwArg1, 5, v14, 2, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
  }
  return v11;
}



// 幻影消散演出：sub_431920 装载 Animation/IllusionDestroyEffect.ani + IllusionDestroy.ani，
//   vt+212 播报 KENSIN_DISAPPEAR
// ------------------------------------------------------------
// 0x590C40 sub_590C40 —— 幻影消散演出主函数（KENSIN_DISAPPEAR）
// 事件分发：ArgList==0 → vt+204 以 this+1554 数据设默认动作；ArgList==5（消散事件）
// 取自身坐标(vt+120/124/128) 后，sub_42FCB0(228) 资源开关通过时 sub_431920 装载
// Animation/IllusionDestroyEffect.ani 与 IllusionDestroy.ani 两段消散动画 →
// sub_44B6C0(284) 建 CNRDPooledObject → sub_44E0D0 绑定动画 → sub_45FE80 投放
// this+29 场景，经对象 vt+148/vt+112 对齐朝向坐标后 vt+212 播 KENSIN_DISAPPEAR
// ------------------------------------------------------------
int /*thiscall*/ sub_590C40(int *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：幻影消散演出主函数（KENSIN_DISAPPEAR）
{
  int result; // eax
  int v7; // ebx
  int fld_e91; // ecx | =+0x016C 字段 x1（证据 00625C40）
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

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  v7 = 0;
  if ( ArgList == 0 )  // 若 ArgList 为 0
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
             this,
             1,
             *(uint32_t *)*(this + 1554),  // this+6216〔pTbl6216(推断)〕
             0,
             0,
             0,
             0);
  if ( ArgList == 5 )  // 若 ArgList == 5
  {
    v19 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
    v20 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    v21 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    {
      if ( (unsigned int)*(this + 96) < 0x10 )  // this+384〔nAnimNameCap(推断)〕
        LOBYTE(fld_e91) = (uint8_t)this + 108;
      else  // 否则分支
        fld_e91 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
      v7 = sub_431920(fld_e91, (char)"Animation/IllusionDestroyEffect.ani", 1);  // 动画件构造（文件名版）
    }
    v9 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    pObj2 = (int)v9;
    if ( v9 != nullptr )  // 若 v9 有效（非空）
    {
      sub_44E0D0(v9, v7, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else  // 否则分支
    {
      v10 = 0;
    }
    sub_45FE80(*(this + 29), v10, 2, 0, v10, (int)this, 0);  // 调 实体对象注册到演播层
    v11 = *(uint32_t *)v10;
    v12 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
    (*(void (/*thiscall*/ **)(int, int))(v11 + 148))(v10, v12);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 112))(v10, v19, v20, v21);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    {
      if ( (unsigned int)*(this + 96) < 0x10 )  // this+384〔nAnimNameCap(推断)〕
        LOBYTE(v13) = (uint8_t)this + 108;
      else  // 否则分支
        v13 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
      v14 = sub_431920(v13, (char)"Animation/IllusionDestroy.ani", 1);  // 动画件构造（文件名版）
    }
    else  // 否则分支
    {
      v14 = 0;
    }
    v15 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    v16 = (int)v15;
    if ( v15 != nullptr )  // 若 v15 有效（非空）
    {
      sub_44E0D0(v15, v14, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)v16 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else  // 否则分支
    {
      pObj = 0;
    }
    sub_45FE80(*(this + 29), pObj, 2, 0, pObj, (int)this, 0);  // 调 实体对象注册到演播层
    v17 = *(uint32_t *)pObj;
    v18 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
    (*(void (/*thiscall*/ **)(int, int))(v17 + 148))(pObj, v18);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 112))(pObj, v19, v20, v21);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "KENSIN_DISAPPEAR",  // 标签 KENSIN_DISAPPEAR
             -1,
             0,
             0);
  }
  return result;
}



// 阈值组清零：this+2150/2151/2152 三个 AI 阈值字段清零（与 sub_590F30 装载端成对）
// ------------------------------------------------------------
// 0x590E70 sub_590E70 —— AI 阈值组清零
// this+2150/2151/2152 三个 AI 阈值字段归零（装载端见 sub_590F30 与 sub_590900）；
// 阈值A=0 使 sub_590970/sub_591020 的 clock_now ≥ 阈值A 时钟门立即放行【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_590E70(uint32_t *this)  // 实现：AI 阈值组清零
{
  *(this + 2150) = 0;  // 阈值A（sub_590970 出场时钟门用）
  *(this + 2151) = 0;  // 阈值B
  *(this + 2152) = 0;  // 阈值C
  return 0;
}



// %s冰冻系受击反应（虚表 0x6CD60C +512 槽）：格挡位 a4==0 且 attackinfo(+16 状态/+0 伤害)
//   非空 → vt+212 连播 "FROZEN"+"SHU_DMG"；尾调 sub_4DA3B0 续接基类命中流程【推断】
// ------------------------------------------------------------
// 0x590E90 sub_590E90 —— 冰冻受击播报处理器（FROZEN）
// vmt200 命中槽覆写（虚表 0x6CD60C +512 槽）：nArg4==0（非格挡）且经攻击者 vt+348
// 取得的 attackinfo +16 状态位非零或 +0 伤害＞0 时，vt+212 连播 FROZEN 与 SHU_DMG；
// 尾调 sub_4DA3B0 续接基类命中包分发前置流程（研究 §1.1 case 0x1）
// ------------------------------------------------------------
int /*thiscall*/ sub_590E90(void *this, int nArg2, int nArg3, int nArg4)  // 实现：冰冻受击播报处理器（FROZEN）
{
  int v5; // eax

  if ( (uint8_t)nArg4 == 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // 调虚槽 +348：取坐标对象
    if ( *(uint8_t *)(v5 + 16) != 0 || *(float *)v5 > 0.0 )  // 复合条件判定（与/或）
    {
      (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
        this,
        "FROZEN",  // 标签 FROZEN
        -1,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
        this,
        "SHU_DMG",  // 标签 SHU_DMG
        -1,
        0,
        0);
    }
  }
  return sub_4DA3B0(nArg2, nArg3, nArg4);  // 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
}



// 死亡播报：a2==this 时 vt+212 广播 "SHU_DIE"（自灭/死亡确认，研究 31 死亡系统）
// ------------------------------------------------------------
// 0x590F00 sub_590F00 —— 死亡播报回调（SHU_DIE）
// sub_4D9170 前置后仅当死亡对象 pArg2==this 时经 vt+212 广播 SHU_DIE（研究 31 死亡系统）
// ------------------------------------------------------------
int /*thiscall*/ sub_590F00(void *this, void *pArg2)  // 实现：死亡播报回调（SHU_DIE）
{
  int result; // eax

  result = sub_4D9170(pArg2);  // result = 调 sub_4D9170 返回值
  if ( pArg2 == this )  // 若 pArg2 == this
    return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "SHU_DIE",  // 标签 SHU_DIE
             -1,
             0,
             0);
  return result;
}



// 数据表读数：sub_47E720(3,43) 选表 → sub_47EF20 按行号 nArg2 读 3 列阈值
//   存 this+2150/2151(=原值/2)/2152，随后 vt+204 设动作为默认待机 + 清 this+162 标志位0
// ------------------------------------------------------------
// 0x590F30 sub_590F30 —— AI 阈值装载·数据表(3,43)
// sub_47E720(3,43) 选表后 sub_47EF20 逐列读数：列0→this+2150、列1÷2→this+2151、
// 列2→this+2152（阈值B/C 由 sub_591350 作人偶光环构造参数消费）；
// 随后 vt+204 以 this+1554 数据设默认待机动作，并清 this+162 bit0 标志
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_590F30(int *this, int nArg2)  // 实现：AI 阈值装载·数据表(3,43)
{
  int v3; // eax
  int v4; // edx
  unsigned int result; // eax

  sub_47E720(3, 43);  // 选数据表 (3,43)
  *(this + 2150) = sub_47EF20(0, nArg2, -1, -1, 11);  // 列0 → 阈值A
  *(this + 2151) = sub_47EF20(1, nArg2, -1, -1, 11) / 2;  // 列1 → 阈值B（表值减半）
  v3 = sub_47EF20(2, nArg2, -1, -1, 11);  // 列2 → 阈值C
  v4 = *this;
  *(this + 2152) = v3;  // this+8608〔uAI8608(推断)〕
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v4 + 204))(  // 调虚槽 +204：定时器插入
    this,
    1,
    *(uint32_t *)*(this + 1554),  // this+6216〔pTbl6216(推断)〕
    0,
    0,
    0,
    0);
  result = *(this + 162) & 0xFFFFFFFE;  // this+648〔uMonFlagBits〕
  *(this + 162) = result;  // this+648〔uMonFlagBits〕
  return result;
}



// 事件回调（状态0=待机事件）：对 this+1554 持有的对象执行 sub_4926A0 + sub_4938F0
//   （寻路停止/朝向复位族【推断】，this+1554=子对象/皮肤指针）
// ------------------------------------------------------------
// 0x590FD0 sub_590FD0 —— 待机事件回调·子对象播放复位
// sub_4E33D0 基类事件处理后仅响应 ArgList==0（待机事件）：对 this+1554 持有的
// 子对象执行 sub_4926A0 帧游标复位 + sub_4938F0 播放驱动总入口
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_590FD0(int **this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：待机事件回调·子对象播放复位
{
  uint32_t *result; // eax

  result = (uint32_t *)sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 【事件分发基处理】
  if ( ArgList == 0 )  // 若 ArgList 为 0
  {
    sub_4926A0(**(this + 1554));  // 帧游标复位（+44 帧数组；递归子链 +204）
    return sub_4938F0(**(this + 1554));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  }
  return result;
}



// 【AI 相位：反应】sub_431230 参数打包 + sub_699000 时钟门 → vt+560 反应态写入
// ------------------------------------------------------------
// 0x591020 sub_591020 —— AI 反应相位·反应态5写入
// 与 sub_590970 同构时钟门：存活(vt+308) 且主状态 this+1639==0 且 clock_now(this+16)
// ≥ 阈值A this+2150（或 this+2088==0 旁路）时，sub_431230 打包 → vt+560 写反应态 5
// ------------------------------------------------------------
void /*thiscall*/ sub_591020(uint32_t *this)  // 实现：AI 反应相位·反应态5写入
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && *(this + 1639) == 0  // this+6556〔大状态ID〕
    && (sub_699000((int)(this + 16)) >= *(this + 2150) || *(this + 2088) == 0) )  // 【clock_now(clk)】
  {
    Block = nullptr;  // Block = 空指针
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 0;
    sub_431230((int)v2, v6);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 5, v2, 2, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
  }
}



// 构造：CNRDAuraMaster 基类构造（虚表挂接 + this+23 定时器初始化 + this+29 链表哨兵节点）
//   nArg2..nArg4/pszArg5 = 光环规格参数（子类如 CNProvocationDollAura 传 0,18,250,1）
// ------------------------------------------------------------
// 0x5910D0 sub_5910D0 —— CNRDAuraMaster 构造函数
// 挂基类虚表 → sub_607240/607280 初始化 this+23 定时器 → sub_433AC0 建 this+29
// 链表哨兵（三指针自指空链表）→ sub_64A150/64A160 装载光环基类规格参数
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5910D0(uint32_t *this, int nArg2, int nArg3, int nArg4, char pszArg5)  // 实现：CNRDAuraMaster 构造函数
{
  int pThis_1C; // eax

  sub_4B1030();  // IRDAppendage 基类构造
  *this = &CNRDAuraMaster::`vftable';  // 构造装配 vftable：CNRDAuraMaster
  sub_607240(this + 23);  // this+23 定时器/时钟字段初始化
  sub_607280(this + 23);  // 调 初始化 this+136 双子对象、this+160/164/168 三指针清零、
  pThis_1C = sub_433AC0(this + 28);  // 新建链表头（this+28 为 std::list 习惯位）
  *(this + 29) = pThis_1C;  // this+116〔会话上下文〕
  *(uint8_t *)(pThis_1C + 21) = 1;  // pThis_1C+21〔bArmorState(推断)〕
  *(uint32_t *)(*(this + 29) + 4) = *(this + 29);  // 哨兵节点三指针自指（空链表）
  *(uint32_t *)*(this + 29) = *(this + 29);  // this+116〔会话上下文〕
  *(uint32_t *)(*(this + 29) + 8) = *(this + 29);  // this+116〔会话上下文〕
  *(this + 30) = 0;  // this+120〔pAnimObj〕
  sub_64A150(this);  // 光环基类数据（14 行）
  sub_64A160(nArg2, nArg3, nArg4, pszArg5);  // 光环基类数据 2（607260）
  return this;
}



// 转发查询：vt+76(this,0)（存活/激活位查询族【推断】）
// ------------------------------------------------------------
// 0x591180 sub_591180 —— 转发查询（vt+76）
// 单行转发：vt+76(this,0)，存活/激活位查询族【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_591180(void *this)  // 实现：转发查询（vt+76）
{
  return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 76))(this, 0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
}



// 析构：CNRDAuraMaster 逆序析构（this+29 链表节点销毁 → IRDAppendage 基类 → IObject 基类）
// ------------------------------------------------------------
// 0x591190 sub_591190 —— CNRDAuraMaster 析构函数
// 逆序析构：sub_64A7C0 受击前置清理 → 销毁 this+29 链表哨兵（sub_52E960 + free）→
// 降级 IRDAppendage 基类（sub_5F6640）→ 归 nengine::IObject 虚表
// ------------------------------------------------------------
int /*thiscall*/ sub_591190(char *this)  // 实现：CNRDAuraMaster 析构函数
{
  int result; // eax
  int v3; // [esp-8h] [ebp-28h]
  int *pThis_1D; // [esp-4h] [ebp-24h]
  uint8_t v5[4]; // [esp+Ch] [ebp-14h] BYREF
  char *pThis; // [esp+10h] [ebp-10h]
  int v7; // [esp+1Ch] [ebp-4h]

  pThis = this;
  *(uint32_t *)this = &CNRDAuraMaster::`vftable';  // 构造装配 vftable：CNRDAuraMaster
  v7 = 2;
  sub_64A7C0();  // 受击前置（42AF90/657740）
  v4 = *((int **)this + 29);
  v3 = *v4;
  LOBYTE(v7) = 1;
  sub_52E960(v5, v3, v4);
  j__free(*((void **)this + 29));
  *((uint32_t *)this + 29) = 0;  // this[29] = 0
  *((uint32_t *)this + 30) = 0;  // this+120〔pAnimObj〕
  LOBYTE(v7) = 0;
  nullsub_3(this + 92);  // this+368〔nBindPos368(推断)〕
  *(uint32_t *)this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  v7 = 3;
  result = sub_5F6640(this);  // result = 调 sub_5F6640 返回值
  *(this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *((uint32_t *)this + 2) = &nengine::IObject::`vftable';  // this+8〔nSkillRec8(推断)〕
  return result;
}



// 删除析构：sub_591190 析构后按 deleting 标志位 free（标准 scalar deleting dtor 模式）
// ------------------------------------------------------------
// 0x591230 sub_591230 —— CNRDAuraMaster 删除析构
// scalar deleting dtor：调 sub_591190 析构后按 pszArg2 bit0 决定是否 free
// ------------------------------------------------------------
char */*thiscall*/ sub_591230(char *Block, char pszArg2)  // 实现：CNRDAuraMaster 删除析构
{
  sub_591190(Block);  // CNRDAuraMaster 析构函数
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// 构造：CNProvocationDollAura 挑衅人偶光环（基类 CNRDAuraMaster(0,18,250,1) + 子类虚表 + nArg2/nArg3 参数）
// ------------------------------------------------------------
// 0x591260 sub_591260 —— CNProvocationDollAura 挑衅人偶光环构造
// 先以 (0,18,250,1) 构造基类 CNRDAuraMaster（sub_5910D0）再挂子类虚表；
// sub_64A930 挑衅查询初始化，sub_64AD30 装载 ProvocationDollSymbol 符号数据（nArg2/nArg3）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_591260(uint32_t *this, int nArg2, int nArg3)  // 实现：CNProvocationDollAura 挑衅人偶光环构造
{
  sub_5910D0(this, 0, 18, 250, 1);  // CNRDAuraMaster 构造函数
  *this = &CNProvocationDollAura::`vftable';  // 构造装配 vftable：CNProvocationDollAura
  sub_64A930(this);  // 挑衅查询（16 行）
  sub_64AD30(nArg2, nArg3);  // 装载 ProvocationDollSymbol1/2.ani + ProvocationDollAreaStart/Loop.ani（42FCB0/431…
  return this;
}



// 删除析构：CNProvocationDollAura（sub_591300 析构后按标志 free）
// ------------------------------------------------------------
// 0x5912D0 sub_5912D0 —— CNProvocationDollAura 删除析构
// scalar deleting dtor：sub_591300 析构后按 pszArg2 bit0 决定是否 free
// ------------------------------------------------------------
void */*thiscall*/ sub_5912D0(void *Block, char pszArg2)  // 实现：CNProvocationDollAura 删除析构
{
  sub_591300();  // CNProvocationDollAura 析构函数
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// 析构：CNProvocationDollAura（子类清理 sub_64AE50 → 基类 sub_591190）
// ------------------------------------------------------------
// 0x591300 sub_591300 —— CNProvocationDollAura 析构函数
// 挂回子类虚表 → sub_64AE50 子类清理 → 委托基类析构 sub_591190
// ------------------------------------------------------------
int /*thiscall*/ sub_591300(char *this)  // 实现：CNProvocationDollAura 析构函数
{
  *(uint32_t *)this = &CNProvocationDollAura::`vftable';  // 构造装配 vftable：CNProvocationDollAura
  sub_64AE50();  // 受击表现 2（42AF90/657740）
  return sub_591190(this);  // CNRDAuraMaster 析构函数
}



// 出场播报：new CNProvocationDollAura(阈值B, -阈值C) 挂到 this（vt+56 绑定宿主/时长），
//   再 vt+212 广播 "SHU_APPEAR"（SHU 出场即带挑衅人偶光环）
// ------------------------------------------------------------
// 0x591350 sub_591350 —— SHU 出场挂人偶光环播报（SHU_APPEAR）
// sub_4D9760 收尾后 new 0x98 字节构造 CNProvocationDollAura：以阈值B/负阈值C 为构造参数，
// vt+56 绑定宿主 this 与时长字段 this+2088 → vt+212 广播 SHU_APPEAR
// （SHU 出场即自带挑衅人偶光环）
// ------------------------------------------------------------
int /*thiscall*/ sub_591350(int *this)  // 实现：SHU 出场挂人偶光环播报（SHU_APPEAR）
{
  uint32_t *pMem; // eax
  uint32_t *pDollAura; // eax

  sub_4D9760();  // 观察者广播后条件收尾
  pMem = operator new(0x98u);  // new(152 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pDollAura = sub_591260(pMem, *(this + 2151), -*(this + 2152));  // 半径=阈值B，Y偏移=-阈值C
  else  // 否则分支
    pDollAura = nullptr;  // pDollAura = 空指针
  (*(void (/*thiscall*/ **)(uint32_t *, int *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*pDollAura + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    pDollAura,
    this,
    *(this + 2088),  // this+8352〔nRideHost8352〕
    0,
    0,
    0,
    -1);
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SHU_APPEAR", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
}



// ============================================================
// 【分区 2】魔法师·克拉赫（Soceress Keraha）（0x5913F0-0x5933A0）
// 证据：ChillingAura 冰霜光环(sub_64B0F0)、SHIELD_ICE/WINDSHIELD_LOOP 冰盾、
//       KERA_CAST/KERA_COMMAND/SOR_SPIN、Summon.ani 召唤、Particle/EnergyBall.ptl、
//       B_KERAHA_01 登场曲、R_KERA_ATK/DMG/DIE 语音 + Hair02/Cloth02/Weapon02/Acc02.equ

// 子类扩展字段复位（this+8612..8628）
// ------------------------------------------------------------
// 0x5913F0 sub_5913F0 —— 克拉赫子类 AI 字段复位
// 清 this+8600/8612/8616/8624/8628 并置 this+8604=1；与 SHU 系 sub_5908C0 相反，
// 出场标志默认置位（克拉赫不走一次性出场动作门）【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5913F0(int this)  // 实现：克拉赫子类 AI 字段复位
{
  *(uint32_t *)(this + 8600) = 0;  // this+8600〔uAI8600(推断)〕
  *(uint32_t *)(this + 8604) = 1;  // this+8604〔bAI8604(推断)〕
  *(uint32_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint32_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  *(uint8_t *)(this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
  *(uint32_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  return 0;
}



// 死亡收尾：死亡对象==this 时 vt+216 停止循环音 7818（与 sub_591E10 冰盾 WINDSHIELD_LOOP 同一音id）
// ------------------------------------------------------------
// 0x591420 sub_591420 —— 死亡收尾·停冰盾循环音
// 死亡对象==this 时经 vt+216 停止循环音 id 7818（冰盾 WINDSHIELD_LOOP 收尾，研究 28）
// ------------------------------------------------------------
int /*thiscall*/ sub_591420(void *this, void *pArg2)  // 实现：死亡收尾·停冰盾循环音
{
  int result; // eax

  result = sub_4D9170(pArg2);  // result = 调 sub_4D9170 返回值
  if ( this == pArg2 )  // 若 this == pArg2
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 7818);  // 停循环音id 7818
  return result;
}



// %s受击后置（虚表 0x6CDB2C +512 槽）：vt+1104(this,4) 动作切换 +
//   this+2155 = clock_now(this+9) 受击时间戳【推断】；尾调 sub_4DA3B0 续程
// ------------------------------------------------------------
// 0x591450 sub_591450 —— 受击后置处理（vmt200 命中槽覆写）
// 虚表 0x6CDB2C +512 槽：先 sub_4DA3B0 走基类命中包分发取返回值；nArg4==0（非格挡）时
// vt+1104(this,4) 切受击姿态动作，并以 clock_now(this+9) 记受击时刻 this+2155
// （主 AI sub_5923A0 施法冷却门的时刻基准）
// ------------------------------------------------------------
int /*thiscall*/ sub_591450(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：受击后置处理（vmt200 命中槽覆写）
{
  int nHitResult; // edi

  nHitResult = sub_4DA3B0(nArg2, nArg3, nArg4);  // 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
  if ( (uint8_t)nArg4 == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 切动作状态4（受击姿态）
    *(this + 2155) = sub_699000((int)(this + 9));  // 记录受击时刻（供主AI冷却门比较）
  }
  return nHitResult;
}



// 瞬移贴近目标：vt+672(this,3) 取攻击盒 → 以目标 nArg2 为锚算坐标链(vt+124/vt+120)，
//   距离偏移 100(常态)/130(this+1908 狂气态) → vt+584 写回自身坐标（克拉赫贴身突进【推断】）
// ------------------------------------------------------------
// 0x5914A0 sub_5914A0 —— 瞬移贴近目标
// vt+672(3) 取 3 号攻击盒 → 以目标 nArg2 为锚经 vt+124/vt+120 坐标链算落点，
// 距离偏移狂气态 this+1908 非 0 时取 100、否则 130 → vt+584 写回自身坐标完成瞬移
// ------------------------------------------------------------
int /*thiscall*/ sub_5914A0(uint32_t *this, int nArg2)  // 实现：瞬移贴近目标
{
  int result; // eax
  int nVt; // ebx
  uint32_t *pAtkInfo; // eax
  int nPosRaw; // eax
  int nCoord1; // eax
  int nCoord2; // eax
  int nDestPos; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    nVt = *this;
    pAtkInfo = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 取3号攻击盒
    nPosRaw = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
           nArg2,
           *(this + 2154),  // this+8616〔uAI8616(推断)〕
           *pAtkInfo,
           0,
           4,
           *(this + 1908) != 0 ? 100 : 130,  // 狂气态贴近更远
           1,
           0,
           0);
    nCoord1 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, nPosRaw);  // 调虚槽 +120：动画对象
    nCoord2 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)nArg2 + 124))(nArg2, 0, nCoord1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nDestPos = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, nCoord2);  // 调虚槽 +120：动画对象
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(nVt + 584))(this, nDestPos);  // 写回自身坐标=瞬移
  }
  return result;
}



// 攻击发射：从 this+29 光环数据链(+132→+108→+112)取技能id 存 this+2151，
//   vt+152 建攻击请求(判定宽度0xFFFF) → vt+376 以(this+2160,this+2161)坐标施放 → vt+592 绑定目标槽 this+2152；
//   施放计数 this+2157+1 并清相位门 this+8624（克拉赫冰环施放【推断】）
// ------------------------------------------------------------
// 0x591520 sub_591520 —— 冰环攻击发射
// 从 this+29 光环数据链三级解引(+132→+108→+112)取技能id 存 this+2151 → vt+152 建
// 攻击请求（判定宽度 0xFFFF）→ vt+376 以 this+2160/2161 坐标施放 → vt+592 绑定
// 目标槽 this+2152；施放计数 this+2157 自增（主 AI 以 ≥5 封顶）并清相位门 this+8624
// ------------------------------------------------------------
int /*thiscall*/ sub_591520(uint32_t *this, int nArg2, int nArg3)  // 实现：冰环攻击发射
{
  int result; // eax
  int nVt; // edi
  int nAtkReq; // eax
  int hCastObj; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    nVt = *this;
    *(this + 2151) = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 108) + 112);  // 技能id（光环数据链三级解引）
    nAtkReq = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(nVt + 152))(  // 调虚槽 +152：效果通道 3
           this,
           2,
           0,
           0,
           0xFFFF,
           0,
           0,
           0,
           0);
    hCastObj = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 376))(  // 调虚槽 +376：坐标同步包（type 37）
           this,
           *(this + 2151),  // this+8604〔bAI8604(推断)〕
           *(this + 2160),  // this+8640〔uCastSlot8640(推断)〕
           *(this + 2161),  // this+8644〔uPhase8644(推断)〕
           0,
           nAtkReq);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(nVt + 592))(this, *(this + 2152), hCastObj);  // this+8608〔uAI8608(推断)〕
    result = *(this + 2157) + 1;  // 施放计数+1（主AI以 >=5 封顶）
    *((uint8_t *)this + 8624) = 0;  // 清相位门：本轮施放完成
    *(this + 2157) = result;  // this+8628〔nPoolTime(推断)〕
  }
  return result;
}



// 闪避/召唤 AI：50% 概率 sub_4DC730（位移闪避【推断】）；再 10% 概率 vt+580 释放 buff 48013（10级）
// ------------------------------------------------------------
// 0x5915B0 sub_5915B0 —— 随机行为·聚合广播与自我增益
// 50% 概率调 sub_4DC730 同队怪物聚合广播（包 type 29）；再 10% 概率经 vt+580 对自身
// 施放 buff/skill id 48013（10 级；末参 4 的语义未定【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_5915B0(void *this)  // 实现：随机行为·聚合广播与自我增益
{
  int result; // eax
  int nRand; // eax
  int nPct; // et2

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    if ( rand() % 100 < 50 )  // 50% 概率
      sub_4DC730(this);  // 同队怪物聚合广播（包 type 29）
    nRand = rand();  // nRand = 调 rand
    nPct = nRand % 100;
    result = nRand / 100;
    if ( nPct < 10 )  // 10% 概率释放 48013
      return (*(int (/*thiscall*/ **)(void *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
               this,
               48013,  // buff/skill id 48013
               10,     // 等级10
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



// 施法走位（帧驱动瞬移）：vt+200 当前动画帧(+148) 依次到达 3/5/7/9 帧时，
//   以目标 this+1813 为锚横向瞬移 ±50*(步数-2)（vt+152 朝向决定正负），vt+584 写回坐标；
//   帧过 expected+1 后步进 this+2159、清 this+2158（克拉赫施法中的左右闪步）
// ------------------------------------------------------------
// 0x591610 sub_591610 —— 施法走位·帧驱动四步横移
// 应到帧表 3/5/7/9：vt+200 当前动画帧(+148) 等于本步应到帧且 this+2158 未瞬移时，
// 横移量 50×(步-2)（步0=-100…步3=+100）经 vt+152 朝向翻转正负，以目标 this+1813
// 为锚经 vt+124/vt+120 坐标链算落点 → vt+584 瞬移到目标侧面；帧走过应到帧+1 后
// 清 this+2158、步进 this+2159 进入下一步（克拉赫施法中的左右闪步走位）
// ------------------------------------------------------------
int /*usercall*/ sub_591610@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：施法走位·帧驱动四步横移
{
  int nVt; // eax
  int pAnim; // eax
  int nStep; // ecx
  int nSideOffset; // ebx
  int *pTarget; // edi
  int pTargetVt; // edx
  int nCoord1; // eax
  int nCoord2; // eax
  int nCoord3; // eax
  int nDestPos; // eax
  int result; // eax
  int nStep2; // ecx
  int nFaceDir; // [esp-24h] [ebp-44h]
  int pAtkInfo; // [esp-20h] [ebp-40h]
  uint32_t nExpectedFrames[5]; // [esp+8h] [ebp-18h]
  int nVt2; // [esp+1Ch] [ebp-4h]

  nVt = *pArg1;
  nExpectedFrames[0] = 3;  // 步0 应到达帧
  nExpectedFrames[1] = 5;  // 步1
  nExpectedFrames[2] = 7;  // 步2
  nExpectedFrames[3] = 9;  // 步3
  pAnim = (*(int (/*thiscall*/ **)(uint32_t *))(nVt + 200))(pArg1);  // 调虚槽 +200：取动画对象
  nStep = pArg1[2159];  // nStep = 取 pArg1[2159]
  if ( *(uint32_t *)(pAnim + 148) == nExpectedFrames[nStep] && pArg1[2158] == 0 )  // 当前帧==本步应到帧且未瞬移
  {
    nSideOffset = 50 * (nStep - 2);  // 步0=-100 步1=-50 步2=+50 步3=+100
    if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 152))(pArg1, nArg2) == 1 )  // 调虚槽 +152：效果通道 3
      nSideOffset = -nSideOffset;  // 朝向翻转横移方向
    nVt2 = *pArg1;
    pAtkInfo = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(nVt2 + 672))(pArg1, 3);  // 调虚槽 +672：自身 HP
    pTarget = (int *)pArg1[1813];
    pTargetVt = *pTarget;
    nFaceDir = pArg1[2154];  // nFaceDir = 取 pArg1[2154]
    nExpectedFrames[4] = pTarget;  // 数组尾槽复用作暂存（Hex-Rays 伪影）
    nCoord1 = (*(int (/*stdcall*/ **)(int, int, uint32_t, int, int, int, uint32_t, uint32_t))(pTargetVt + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
           nFaceDir,
           pAtkInfo,
           0,
           4,
           100,
           1,
           0,
           0);
    nCoord2 = (*(int (/*thiscall*/ **)(int *, int))(*pTarget + 120))(pTarget, nCoord1);  // 调虚槽 +120：动画对象
    nCoord3 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*pTarget + 124))(pTarget, 0, nCoord2 - nSideOffset);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nDestPos = (*(int (/*thiscall*/ **)(int *, int))(*pTarget + 120))(pTarget, nCoord3);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(uint32_t *, int))(nVt2 + 584))(pArg1, nDestPos - nSideOffset);  // 瞬移到目标侧面
    pArg1[2158] = 1;  // 本步已瞬移标志
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);  // 调虚槽 +200：取动画对象
  nStep2 = pArg1[2159];  // nStep2 = 取 pArg1[2159]
  if ( *(uint32_t *)(result + 148) == nExpectedFrames[nStep2] + 1 )  // 帧走过应到帧→进入下一步
  {
    pArg1[2158] = 0;
    pArg1[2159] = nStep2 + 1;
  }
  return result;
}



// 四连瞬移绕位：以目标(nArg2, 缺省 this+1813)为锚依次瞬移 (-50,-50)→(-60,-60)→(+50,+50)→(+60,+60)
//   （对角四象限绕背走位，配合施法/攻击演出），结束置 this+2158=1
// ------------------------------------------------------------
// 0x591720 sub_591720 —— 四连瞬移绕背走位
// 锚定 nArg2（缺省用记忆目标 this+1813），vt+672(3) 攻击盒 + vt+124/vt+120 坐标链
// 反复取点，依次瞬移 (-50,-50)→(-60,-60)→(+50,+50)→(+60,+60) 四个对角象限
// （vt+584 写坐标），结束置 this+2158=1 绕位完成标志
// ------------------------------------------------------------
int /*thiscall*/ sub_591720(uint32_t *this, int nArg2)  // 实现：四连瞬移绕背走位
{
  int pAnchor; // esi
  int nVt1; // ebx
  uint32_t *pAtkInfo1; // eax
  int nPosRaw1; // eax
  int nC1a; // eax
  int nC1b; // eax
  int nC1c; // eax
  int nVt2; // ebx
  uint32_t *pAtkInfo2; // eax
  int nPosRaw2; // eax
  int nC2a; // eax
  int nC2b; // eax
  int nC2c; // eax
  int nVt3; // ebx
  uint32_t *pAtkInfo3; // eax
  int nPosRaw3; // eax
  int nC3a; // eax
  int nC3b; // eax
  int nC3c; // eax
  int nVt4; // ebx
  uint32_t *pAtkInfo4; // eax
  int nPosRaw4; // eax
  int nC4a; // eax
  int nC4b; // eax
  int nC4c; // eax
  int result; // eax

  pAnchor = nArg2;  // 锚定目标：传参优先，缺省用记忆目标 this+1813
  if ( nArg2 == 0 )  // 若 nArg2 为 0
    pAnchor = *(this + 1813);  // this+7252〔pTarget7252〕
  nVt1 = *this;
  pAtkInfo1 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  nPosRaw1 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pAnchor + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
         pAnchor,
         *(this + 2154),  // this+8616〔uAI8616(推断)〕
         *pAtkInfo1,
         0,
         4,
         100,
         1,
         0,
         0);
  nC1a = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pAnchor + 120))(pAnchor, nPosRaw1 - 50);  // 落点1：X-50
  nC1b = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pAnchor + 124))(pAnchor, 0, nC1a);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nC1c = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pAnchor + 120))(pAnchor, nC1b - 50);  // 落点1：Y-50
  (*(void (/*thiscall*/ **)(uint32_t *, int))(nVt1 + 584))(this, nC1c);  // 瞬移①(-50,-50)
  nVt2 = *this;
  pAtkInfo2 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  nPosRaw2 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pAnchor + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          pAnchor,
          *(this + 2154),  // this+8616〔uAI8616(推断)〕
          *pAtkInfo2,
          0,
          4,
          100,
          1,
          0,
          0);
  nC2a = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pAnchor + 120))(pAnchor, nPosRaw2);  // 调虚槽 +120：动画对象
  nC2b = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pAnchor + 124))(pAnchor, 0, nC2a - 60);  // 落点2：X-60
  nC2c = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pAnchor + 120))(pAnchor, nC2b);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(uint32_t *, int))(nVt2 + 584))(this, nC2c - 60);  // 瞬移②(-60,-60)
  nVt3 = *this;
  pAtkInfo3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  nPosRaw3 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pAnchor + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          pAnchor,
          *(this + 2154),  // this+8616〔uAI8616(推断)〕
          *pAtkInfo3,
          0,
          4,
          100,
          1,
          0,
          0);
  nC3a = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pAnchor + 120))(pAnchor, nPosRaw3 + 50);  // 落点3：X+50
  nC3b = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pAnchor + 124))(pAnchor, 0, nC3a);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nC3c = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pAnchor + 120))(pAnchor, nC3b + 50);  // 落点3：Y+50
  (*(void (/*thiscall*/ **)(uint32_t *, int))(nVt3 + 584))(this, nC3c);  // 瞬移③(+50,+50)
  nVt4 = *this;
  pAtkInfo4 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  nPosRaw4 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pAnchor + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          pAnchor,
          *(this + 2154),  // this+8616〔uAI8616(推断)〕
          *pAtkInfo4,
          0,
          4,
          100,
          1,
          0,
          0);
  nC4a = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pAnchor + 120))(pAnchor, nPosRaw4);  // 调虚槽 +120：动画对象
  nC4b = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pAnchor + 124))(pAnchor, 0, nC4a + 60);  // 落点4：X+60
  nC4c = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pAnchor + 120))(pAnchor, nC4b);  // 调虚槽 +120：动画对象
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(nVt4 + 584))(this, nC4c + 60);  // 瞬移④(+60,+60)
  *(this + 2158) = 1;  // 绕位完成标志
  return result;
}



// 受击联动瞬移：目标 nArg2 的 vt+576 查询非空时（可被瞬移标志）取返回值作锚瞬移（复用 sub_5914A0）
// ------------------------------------------------------------
// 0x591890 sub_591890 —— 受击联动瞬移
// 目标 nArg2 的 vt+576 查询非空（可被瞬移锚定）时取其返回值作锚，复用 sub_5914A0 瞬移
// ------------------------------------------------------------
void /*thiscall*/ sub_591890(uint32_t *this, int nArg2)  // 实现：受击联动瞬移
{
  int nAnchorPos; // eax

  if ( nArg2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )  // 调虚槽 +576
  {
    nAnchorPos = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 调虚槽 +576
    sub_5914A0(this, nAnchorPos);  // 瞬移贴近目标
  }
}



// 前跳试探：面向偏移 ±75（vt+152 朝向决定正负）作落点试探 sub_499560（第3参=模式3），
//   成功则 sub_591520 立即施放（克拉赫跳劈接冰环【推断】）
// ------------------------------------------------------------
// 0x5918D0 sub_5918D0 —— 前跳试探接施放
// vt+152 朝向决定 ±75 前跳偏移 → sub_499560 试探移动（模式3，落点写 this+2160/2161），
// 试探成功即以落点调 sub_591520 立即施放（跳劈接冰环【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_5918D0(int *this)  // 实现：前跳试探接施放
{
  int nDx; // edi
  int nDx2; // edi
  int nDy; // eax
  int result; // eax

  nDx = 75;  // 前跳距离75
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0 )  // 调虚槽 +152：效果通道 3
    nDx = -75;  // 朝向0则反向
  nDx2 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + nDx;  // 调虚槽 +120：动画对象
  nDy = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  result = sub_499560(this, this + 2160, this + 2161, nDx2, nDy, 3);  // 试探移动，落点写 this+2160/2161
  if ( (uint8_t)result != 0 )
    return sub_591520(this, *(this + 2160), *(this + 2161));  // 试探成功→落点施放
  return result;
}



// AI 相位辅助（80L）
// ------------------------------------------------------------
// 0x591930 sub_591930 —— 主 AI 相位分发器（施法走位/待机纠偏）
// 按 this+1639 相位分发：==8（施法态）且有目标 this+1813 时，经 sub_41A5E0 守护读
// this+1757 相位值：==1 走 sub_591610 帧驱动横移、==2 且 this+2158==0 走 sub_591720 绕位；
// ==14 且 this+30 对象 +170 位非零时经 vt+560 写反应态 0；
// ==0（待机）且 this+6752==0 时校验 vt+200 当前动画与期望动画（this+1541/1554 二选一），
// 不一致则 vt+196 设动画 + sub_4926A0 帧游标复位（待机动画纠偏）
// ------------------------------------------------------------
char /*usercall*/ sub_591930@<al>(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 实现：主 AI 相位分发器（施法走位/待机纠偏）
{
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int v6; // edi
  int v7; // eax
  int v8; // edi

  sub_4E1780(pDwArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  LOBYTE(v3) = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)v3 != 0 )
  {
    v3 = pDwArg1[1639];  // v3 = 取 pDwArg1[1639]
    if ( v3 != 0 )  // 若 v3 非 0
    {
      if ( v3 == 8 )  // 若 v3 == 8
      {
        v3 = pDwArg1[1813];  // v3 = 取 pDwArg1[1813]
        if ( v3 != 0 )  // 若 v3 非 0
        {
          if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
          {
            LOBYTE(v3) = sub_591610(pDwArg1, nArg2);  // 施法走位·帧驱动四步横移
          }
          else  // 否则分支
          {
            v3 = sub_41A5E0((unsigned int)(pDwArg1 + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
            if ( v3 == 2 )  // 若 v3 == 2
            {
              v3 = pDwArg1[2158];  // v3 = 取 pDwArg1[2158]
              if ( v3 == 0 )  // 若 v3 为 0
                LOBYTE(v3) = sub_591720(pDwArg1, 0);  // 四连瞬移绕背走位
            }
          }
        }
      }
      else if ( v3 == 14 )
      {
        LOBYTE(v3) = *(uint8_t *)(pDwArg1[30] + 170);
        if ( (uint8_t)v3 != 0 )
          LOBYTE(v3) = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      }
    }
    else  // 否则分支
    {
      LOBYTE(v3) = *((uint8_t *)pDwArg1 + 6752);
      if ( (uint8_t)v3 == 0 )
      {
        v4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调虚槽 +200：取动画对象
        v5 = *pDwArg1;
        if ( v4 == pDwArg1[1541] )
        {
          v6 = (*(int (/*thiscall*/ **)(int *))(v5 + 184))(pDwArg1);  // 调虚槽 +184：动画对象 z 倾斜转状态码
          v3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调虚槽 +152：效果通道 3
          if ( v6 == v3 )  // 若 v6 == v3
            return v3;
          v7 = *(uint32_t *)pDwArg1[1554];
        }
        else  // 否则分支
        {
          v8 = (*(int (/*thiscall*/ **)(int *))(v5 + 184))(pDwArg1);  // 调虚槽 +184：动画对象 z 倾斜转状态码
          v3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调虚槽 +152：效果通道 3
          if ( v8 != v3 )  // 若 v8 != v3
            return v3;
          v7 = pDwArg1[1541];  // v7 = 取 pDwArg1[1541]
        }
        (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 196))(pDwArg1, v7);  // 调虚槽 +196：动画对象设置（换域 + 播放）
        LOBYTE(v3) = sub_4926A0(pDwArg1[30]);  // 帧游标复位（+44 帧数组；递归子链 +204）
      }
    }
  }
  return v3;
}



// 动画/位移插值：sub_4049C0 帧间 lerp（研究 26）驱动的移动 AI
// ------------------------------------------------------------
// 0x591A40 sub_591A40 —— 瞬移逼近玩家 AI（距离概率门）
// 遍历所属场景 this+29 对象列表：类型 17【推断：玩家】且 sub_4E4630 敌我判定通过、
// sub_4E5CA0==0 门（语义未定【推断：无敌/不可选中】）、距离 ≤300 时，经 sub_4049C0
// 把距离 (1..299) 插值为 0..100 概率（越远越易瞬移），rand 判定通过则 vt+584 瞬移到
// 该玩家附近 ±30 随机偏移处；全场无可贴目标则退化为自身周围 ±100 随机游走
// ------------------------------------------------------------
int /*thiscall*/ sub_591A40(uint32_t *this)  // 实现：瞬移逼近玩家 AI（距离概率门）
{
  int result; // eax
  unsigned int i; // ebx
  int pRoom; // ecx
  int nBegin1; // edx
  int nCount; // eax
  int nBegin2; // edx
  int pObj; // ecx
  int pRoom2; // ecx
  int nBegin3; // edx
  void *pObj2; // edi
  int nDist; // eax
  int nTelePct; // ebx
  int nOffX; // ebx
  int nOffY; // eax
  uint32_t *pAtkInfo1; // eax
  int nPosRaw1; // eax
  int nC1a; // eax
  int nC1b; // eax
  int nC1c; // eax
  int nOffX2; // edi
  int nOffY2; // eax
  int nOffY3; // ebx
  uint32_t *pAtkInfo2; // eax
  int nPosRaw2; // eax
  int nD1; // eax
  int nD2; // eax
  int nD3; // eax
  int nOffYTmp; // [esp+4h] [ebp-8h]
  unsigned int nIdxSave; // [esp+8h] [ebp-4h]
  int nVt1; // [esp+8h] [ebp-4h]
  int nVt2; // [esp+8h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    for ( i = 0; ; ++i )  // 遍历所属场景(this+29)的对象列表
    {
      pRoom = *(this + 29);  // this+116〔会话上下文〕
      nBegin1 = *(uint32_t *)(pRoom + 8);
      nIdxSave = i;
      nCount = nBegin1 != 0 ? (*(uint32_t *)(pRoom + 12) - nBegin1) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)i >= nCount )
        break;  // 跳出循环/分支
      nBegin2 = *(uint32_t *)(pRoom + 8);
      if ( nBegin2 != 0 && i < (*(uint32_t *)(pRoom + 12) - nBegin2) >> 2 )  // 若 nBegin2 != 0
        pObj = *(uint32_t *)(nBegin2 + 4 * i);
      else  // 否则分支
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )  // 对象类型17=玩家【推断】
      {
        pRoom2 = *(this + 29);  // this+116〔会话上下文〕
        nBegin3 = *(uint32_t *)(pRoom2 + 8);
        if ( nBegin3 != 0 && i < (*(uint32_t *)(pRoom2 + 12) - nBegin3) >> 2 )  // 若 nBegin3 != 0
          pObj2 = *(void **)(nBegin3 + 4 * i);
        else  // 否则分支
          pObj2 = nullptr;  // pObj2 = 空指针
        if ( sub_4E4630(this, (int)pObj2)  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
          && sub_4E5CA0(pObj2) == 0  // 阵营号 200..204 判定（200 起逐个比较）
          && (*(int (/*thiscall*/ **)(uint32_t *, void *, uint32_t))(*this + 8))(this, pObj2, 0) <= 300  // 感知半径300
          && ((*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
           || (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)pObj2 + 940))(pObj2) == 0) )  // 调虚槽 +940
        {
          nDist = (*(int (/*thiscall*/ **)(uint32_t *, void *, uint32_t))(*this + 8))(this, pObj2, 0);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
          nTelePct = (uint64_t)sub_4049C0(0.0, 100.0, nDist - 1, 299);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】距离越远概率越高(1..299→0..100)
          if ( rand() % 100 >= nTelePct )  // 概率判定通过→瞬移到该玩家附近
          {
            nOffX = rand() % 60 - 30;  // 随机偏移 ±30
            nOffY = rand();  // nOffY = 调 rand
            nVt1 = *this;
            nOffYTmp = nOffY % 60 - 30;
            pAtkInfo1 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
            nPosRaw1 = (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
                    pObj2,
                    *(this + 2154),  // this+8616〔uAI8616(推断)〕
                    *pAtkInfo1,
                    0,
                    4,
                    *(this + 1908) != 0 ? 100 : 130,  // 狂气态100/常态130
                    1,
                    0,
                    0);
            nC1a = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)pObj2 + 120))(pObj2, nOffYTmp + nPosRaw1);  // 调虚槽 +120：动画对象
            nC1b = (*(int (/*thiscall*/ **)(void *, uint32_t, int))(*(uint32_t *)pObj2 + 124))(pObj2, 0, nOffX + nC1a);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
            nC1c = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)pObj2 + 120))(pObj2, nOffYTmp + nC1b);  // 调虚槽 +120：动画对象
            return (*(int (/*thiscall*/ **)(uint32_t *, int))(nVt1 + 584))(this, nOffX + nC1c);  // 瞬移
          }
          i = nIdxSave;
        }
      }
    }
    nOffX2 = rand() % 200 - 100;  // 无玩家可贴→自身周围 ±100 随机游走
    nOffY2 = rand();  // nOffY2 = 调 rand
    nVt2 = *this;
    nOffY3 = nOffY2 % 200 - 100;
    pAtkInfo2 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    nPosRaw2 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
            this,
            *(this + 2154),  // this+8616〔uAI8616(推断)〕
            *pAtkInfo2,
            0,
            4,
            *(this + 1908) != 0 ? 100 : 130,  // this+7632〔uWindow7632(推断)〕
            1,
            0,
            0);
    nD1 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, nOffY3 + nPosRaw2);  // 调虚槽 +120：动画对象
    nD2 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 124))(this, 0, nOffX2 + nD1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nD3 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, nOffY3 + nD2);  // 调虚槽 +120：动画对象
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(nVt2 + 584))(this, nOffX2 + nD3);  // 随机落点瞬移
  }
  return result;
}


// 同房间玩家计数：遍历场景(this+29)对象，类型17(玩家【推断】)且 vt+376 房间号相同、
//   距离 < nArg2 的个数（施法前 crowd 检查，主AI以 <2 判定）
// ------------------------------------------------------------
// 0x591C90 sub_591C90 —— 同房间近距玩家计数
// 遍历场景 this+29 对象列表统计：类型 17【推断：玩家】且经 vt+376 判同房间、
// vt+8 距离 < nArg2 的对象个数（sub_5923A0 施法前 crowd 检查，<2 判定）
// ------------------------------------------------------------
int /*thiscall*/ sub_591C90(uint32_t *this, int nArg2)  // 实现：同房间近距玩家计数
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
  while ( 1 )  // 条件循环
  {
    v4 = pThis[29];  // v4 = 取 pThis[29]
    v5 = *(uint32_t *)(v4 + 8);
    v6 = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)v3 >= v6 )
      break;  // 跳出循环/分支
    v7 = *(uint32_t *)(v4 + 8);
    if ( v7 != 0 && v3 < (*(uint32_t *)(v4 + 12) - v7) >> 2 )  // 若 v7 != 0
      pObj2 = *(uint32_t *)(v7 + 4 * v3);
    else  // 否则分支
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      v9 = pThis[29];  // v9 = 取 pThis[29]
      v10 = *(uint32_t *)(v9 + 8);
      if ( v10 != 0 && v3 < (*(uint32_t *)(v9 + 12) - v10) >> 2 )  // 若 v10 != 0
        pObj = *(uint32_t *)(v10 + 4 * v3);
      else  // 否则分支
        pObj = 0;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调虚槽 +376：坐标同步包（type 37）
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis);  // 调虚槽 +376：坐标同步包（type 37）
      pThis = this;
      if ( v14 == v12 && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj, 0) < nArg2 )  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
        ++v16;
    }
    ++v3;
  }
  return v16;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x591D60 sub_591D60 —— 自身减速应用（移速/攻速下调）
// nArg3==0 或 (nArg3==2 且 nArg2==0) 时生效：攻击盒 0 槽 +830 速度倍率浮点减 0.5 →
// vt+676 刷新 → this+1905 对象移速 X/Y 减半 → 全局计数 dword_795468 ÷3【推断：施法延迟】
// （与 sub_591E10 冰盾收尾段的加速恢复互为逆操作【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_591D60(uint32_t *this, int nArg2, int nArg3)  // 实现：自身减速应用（移速/攻速下调）
{
  uint64_t v4; // rax
  unsigned int v5; // edi
  int v6; // edx
  int v8; // [esp+14h] [ebp+Ch]

  if ( nArg3 == 0 || (LODWORD(v4) = nArg3 - 2, nArg3 == 2) && (LODWORD(v4) = nArg2, nArg2 == 0) )  // 若 nArg3 == 0
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 攻击盒0槽+830=速度倍率float
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.5;  // 速度倍率 -0.5
    sub_41A590(v5, v6, v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.5;  // 移速X减半
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.5;  // 移速Y减半
    v4 = (uint64_t)((double)dword_795468 * 0.33333334);  // 全局计数÷3【推断：施法计数】
    dword_795468 = v4;
  }
  return v4;
}



// 冰盾技能：sub_64B0F0 发射 Monster/Soceress/Animation_Keraha/ChillingAura 光环粒子；
//   vt+212 播报 SHIELD_ICE + WINDSHIELD_LOOP（Keraha 冰盾，对应 Aura 家族）
// ------------------------------------------------------------
// 0x591E10 sub_591E10 —— 冰盾开启主函数（SHIELD_ICE）
// 先清 this+7531..7558 与 this+1891..1899 状态字段；Block==nullptr（开盾分支）：
// vt+700 与 sub_53F6A0 收尾 → new 0x8C 经 sub_64B0F0 装载 Monster/Soceress/
// Animation_Keraha/ChillingAura 冰霜光环粒子挂自身 → sub_4DB130(24,2) 随机文案 →
// vt+212 播 SHIELD_ICE、vt+216 停 7818 后以 7818 循环播 WINDSHIELD_LOOP；
// 收尾（开盾 fallthrough 或 Block==2 且 nArg2==0）：攻速倍率 +0.5、移速翻倍、
// dword_795468 ×3（与 sub_591D60 减速互逆）
// ------------------------------------------------------------
int /*thiscall*/ sub_591E10(uint32_t *this, int nArg2, char *Block)  // 实现：冰盾开启主函数（SHIELD_ICE）
{
  char *pThis_1D73; // ecx
  uint64_t v5; // rax
  int pObj; // eax
  int v7; // edx
  unsigned int v8; // edi
  int v9; // edx
  int Blocka; // [esp+24h] [ebp+Ch]

  *((uint8_t *)this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *((uint8_t *)this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *((uint8_t *)this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *((uint8_t *)this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *((uint8_t *)this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *((uint8_t *)this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *((uint8_t *)this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)((char *)this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  pThis_1D73 = (char *)this + 7539;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *(this + 1893) = 0;  // this+7572〔uGrade7572(推断)〕
  *(this + 1892) = 0;  // this+7568〔uEnable7568(推断)〕
  *(this + 1891) = 0;  // this+7564〔uForm7564(推断)〕
  *(this + 1897) = 0;  // this+7588〔uForm7588〕
  *(this + 1896) = 0;  // this+7584〔uForm7584〕
  *(this + 1895) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(this + 1894) = 0;  // this+7576〔uPhase7576(推断)〕
  *(this + 1899) = 0;  // this+7596〔nOffset7596(推断)〕
  *((uint8_t *)this + 7534) = 1;  // this+7534〔bCfgBlock14(推断)〕
  if ( Block == nullptr )  // 若 Block 为空
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 700))(this);  // 调虚槽 +700：读 +6296 槽
    sub_53F6A0(this);  // 调 收尾路径
    if ( operator new(0x8Cu) != nullptr )  // new(140 字节) 分配对象
      pObj = sub_64B0F0(0, 0x40000000, 10, "Monster/Soceress/Animation_Keraha/ChillingAura");  // 动画装载模板 %s.ani/%sDamage.ani（5910D0/42FCB0/431860/493400）
    else  // 否则分支
      pObj = 0;
    (*(void (/*thiscall*/ **)(int, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
      pObj,
      this,
      this,
      0,
      0,
      0,
      -1);
    sub_4DB130(24, 2);  // 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SHIELD_ICE", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 7818);  // 调虚槽 +216：音效 TAG 查询
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
      this,
      "WINDSHIELD_LOOP",  // 标签 WINDSHIELD_LOOP
      7818,
      0,
      0);
    goto LABEL_9;
  }
  LODWORD(v5) = Block - 2;
  if ( Block == (char *)2 && nArg2 == 0 )  // 若 nArg2 == 0
  {
LABEL_9:  // 标签 LABEL_9（跳转合流点）
    v7 = *this;
    *(this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v7 + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&Blocka = COERCE_FLOAT(sub_41A5E0(v8)) + 0.5;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v8, v9, Blocka);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) + *(float *)(*(this + 1905) + 36);  // this+7620〔pStatusPanel(推断)〕
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) + *(float *)(*(this + 1905) + 68);  // this+7620〔pStatusPanel(推断)〕
    v5 = (uint64_t)((double)dword_795468 * 3.0);
    dword_795468 = v5;
  }
  return v5;
}



// AI 相位辅助（69L）
// ------------------------------------------------------------
// 0x592000 sub_592000 —— 近距玩家挂附魔对象（CNEnchantWeapon）
// 遍历场景对象：类型 17【推断：玩家】且同房间（vt+376）且距离 ≤300 时，new 0x84 字节
// 经 sub_4DF1B0 构造 CNEnchantWeapon（参数 = 3 号攻击盒伤害值 -5）并绑定该玩家
// 【推断：对玩家施加的武器附魔/减益标记】
// ------------------------------------------------------------
int /*thiscall*/ sub_592000(uint32_t *this)  // 实现：近距玩家挂附魔对象（CNEnchantWeapon）
{
  unsigned int i; // edi
  int pRoom; // ecx
  int nBegin1; // edx
  int result; // eax
  int nBegin2; // edx
  int pObj3; // ecx
  int pRoom2; // ecx
  int nBegin3; // edx
  int pObj2; // ebx
  int nOtherRoom; // edi
  int pObj; // eax
  uint32_t *pAtkInfo; // eax
  void *pMarkerMem; // [esp+Ch] [ebp-14h]
  unsigned int nIdxSave; // [esp+10h] [ebp-10h]

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    pRoom = *(this + 29);  // this+116〔会话上下文〕
    nBegin1 = *(uint32_t *)(pRoom + 8);
    nIdxSave = i;
    result = nBegin1 != 0 ? (*(uint32_t *)(pRoom + 12) - nBegin1) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;  // 跳出循环/分支
    nBegin2 = *(uint32_t *)(pRoom + 8);
    if ( nBegin2 != 0 && i < (*(uint32_t *)(pRoom + 12) - nBegin2) >> 2 )  // 若 nBegin2 != 0
      pObj3 = *(uint32_t *)(nBegin2 + 4 * i);
    else  // 否则分支
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 17) != 0 )  // 类型17=玩家【推断】
    {
      pRoom2 = *(this + 29);  // this+116〔会话上下文〕
      nBegin3 = *(uint32_t *)(pRoom2 + 8);
      if ( nBegin3 != 0 && i < (*(uint32_t *)(pRoom2 + 12) - nBegin3) >> 2 )  // 若 nBegin3 != 0
        pObj2 = *(uint32_t *)(nBegin3 + 4 * i);
      else  // 否则分支
        pObj2 = 0;
      nOtherRoom = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);  // 对方房间号
      if ( nOtherRoom == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)  // 同房间
        && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj2, 0) <= 300 )  // 距离≤300
      {
        pMarkerMem = operator new(0x84u);  // new(132 字节) 分配对象
        pObj = 0;
        if ( pMarkerMem != nullptr )  // 若 pMarkerMem 有效（非空）
        {
          pAtkInfo = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
          pObj = sub_4DF1B0(*pAtkInfo - 5, 1, 0, -1);  // 攻击盒3伤害-5 作参数
        }
        (*(void (/*thiscall*/ **)(int, int, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
          pObj,
          pObj2,  // 绑定到该玩家
          this,
          1,
          0,
          0,
          -1);
      }
      i = nIdxSave;
    }
  }
  return result;
}



// 施法 AI：vt+212 播报 KERA_CAST / SOR_SPIN（克拉赫旋身施法）
// ------------------------------------------------------------
// 0x592130 sub_592130 —— 克拉赫施法事件回调（KERA_CAST/SOR_SPIN）
// 按 this+1639 相位分流：==5 时 vt+216 停循环音 7818；==14 时按 this+2153 子相位执行
// 2→sub_4DB200 15% 门随机文案 + sub_591A40 瞬移逼近、1→sub_5918D0 前跳、0→sub_592000 挂附魔；
// 基处理 sub_4E33D0 后：==8 且 sub_41A5E0 守护读 this+1757 非 0 时播 KERA_CAST 并清
// this+2158/2159，否则播 SOR_SPIN；==14 时 vt+876 双调用 + vt+196 设动画 + vt+888(1,0,1000,1000)
// ------------------------------------------------------------
int /*thiscall*/ sub_592130(int *this, char ArgList, float fArg3, int nArg4, int nArg5)  // 实现：克拉赫施法事件回调（KERA_CAST/SOR_SPIN）
{
  int fld_e1639; // eax | =+0x199C 字段 x1（证据 005EA970）
  int fld_e2153; // eax | =+0x21A4 字段 x1（证据 0059A3F0）
  int nRand; // eax
  int result; // eax
  uint32_t v10[2]; // [esp+4h] [ebp-8h]

  fld_e1639 = *(this + 1639);  // this+6556〔大状态ID〕
  if ( fld_e1639 == 5 )  // 若 fld_e1639 == 5
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 7818);  // 调虚槽 +216：音效 TAG 查询
  }
  else if ( fld_e1639 == 14 )
  {
    fld_e2153 = *(this + 2153);  // this+8612〔uAI8612(推断)〕
    switch ( fld_e2153 )  // 按 fld_e2153 分派
    {
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        v10[0] = 0;
        v10[1] = 1;
        nRand = rand() % 2;  // nRand = 调 rand
        sub_4DB200(24, v10[nRand]);  // 15% 概率随机文案触发（0x4DB130 的门包装）
        sub_591A40(this);  // 瞬移逼近玩家 AI（距离概率门）
        break;  // 跳出循环/分支
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        sub_4DB200(24, 3);  // 15% 概率随机文案触发（0x4DB130 的门包装）
        sub_5918D0(this);  // 前跳试探接施放
        break;  // 跳出循环/分支
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        sub_592000(this);  // 近距玩家挂附魔对象（CNEnchantWeapon）
        break;  // 跳出循环/分支
      default:  // 默认分支
        break;  // 跳出循环/分支
    }
  }
  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  result = *(this + 1639);  // this+6556〔大状态ID〕
  if ( result == 8 )  // 若 result == 8
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                 this,
                 "KERA_CAST",  // 标签 KERA_CAST
                 -1,
                 0,
                 0);
      *(this + 2158) = 0;  // this+8632〔bDevourFlag(推断)〕
      *(this + 2159) = 0;  // this+8636〔pDollTarget(推断)〕
    }
    else  // 否则分支
    {
      return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SOR_SPIN", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    }
  }
  else if ( result == 14 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      this,
      0,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
    sub_4926A0(*(this + 30));  // 帧游标复位（+44 帧数组；递归子链 +204）
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  }
  return result;
}



// 召唤物生成：sub_431860 装载 Monster/Soceress/Effect/Summon.ani（召唤特效, 44L）
// ------------------------------------------------------------
// 0x5922B0 sub_5922B0 —— 召唤特效生成（Summon.ani）
// sub_42FCB0(228) 资源开关通过时 sub_431860 装载 Monster/Soceress/Effect/Summon.ani →
// sub_44B6C0(284) 建 CNRDPooledObject + sub_44E0D0 绑定动画 → sub_45FE80 投放自身场景，
// 对齐坐标(vt+120/124/128)与宿主(vt+60)、朝向(vt+148)，sub_4A06D0 收尾
// ------------------------------------------------------------
int /*thiscall*/ sub_5922B0(int *this)  // 实现：召唤特效生成（Summon.ani）
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
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    v2 = sub_431860((char)"Monster/Soceress/Effect/Summon.ani", 1);  // 动画件构造（资源 id 版）
  v3 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
  pObj = (int)v3;
  if ( v3 != nullptr )  // 若 v3 有效（非空）
  {
    sub_44E0D0(v3, v2, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else  // 否则分支
  {
    pObj = 0;
  }
  sub_45FE80(*(this + 29), pObj, 2, 0, pObj, (int)this, 0);  // 调 实体对象注册到演播层
  v5 = *(uint32_t *)pObj;
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v6);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(int, int))(v5 + 112))(pObj, v7);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  sub_4A06D0(v11);  // 调 绑定目标对象并记录相对偏移
  v8 = *(uint32_t *)pObj;
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
  return (*(int (/*thiscall*/ **)(int, int))(v8 + 148))(pObj, v9);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
}



// 克拉赫主攻 AI：sub_406D60 写 B_KERAHA_01 登场曲槽 + vt+212 KERA_CAST/KERA_COMMAND；
//   this+8624 相位门 + sub_699000 时钟门
// ------------------------------------------------------------
// 0x5923A0 sub_5923A0 —— 克拉赫主攻 AI 状态机（KERA_CAST/KERA_COMMAND）
// 按 this+1787 大状态 switch：case 0 切 vt+1104(16)，this+1943==3 时 sub_406D60 播
// B_KERAHA_01 登场曲；case 4/16 主分支：无目标切 13；clock_now > dword_795468+this+2155
// 冷却到时（非狂气且 state4）先 sub_591720 绕位再切 16；10% 进施法预备（vt+560 态14、
// this+2153=2，其中 30% 播 KERA_CAST）；施法门（有目标/!this+8624/this+2157<5/rand%300<5）
// 内 sub_4D8FE0 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+740/10 时 sub_5922B0
// 召唤 + KERA_COMMAND + 置 this+8624=1；尾段 1% 回态14 播 KERA_CAST；case 13/14/15 有目标切 4
// ------------------------------------------------------------
int /*thiscall*/ sub_5923A0(int *this)  // 实现：克拉赫主攻 AI 状态机（KERA_CAST/KERA_COMMAND）
{
  int result; // eax
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int nRand; // eax
  int v7; // et2
  int v8; // eax

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 16);  // 调虚槽 +1104
      if ( *(this + 1943) == 3 )  // this+7772〔nCounterState〕
        return sub_406D60("B_KERAHA_01");  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      return result;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
    case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
      if ( result == 14 )  // 若 result == 14
        return result;
      if ( sub_699000((int)(this + 9)) > (unsigned int)(dword_795468 + *(this + 2155)) )  // 【clock_now(clk)】
      {
        if ( *(this + 1908) == 0 && *(this + 1787) == 4 )  // 复合条件判定（与/或）
          sub_591720(this, (int)this);  // 四连瞬移绕背走位
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 16);  // 调虚槽 +1104
      }
      if ( rand() % 100 < 10 )  // 10% 概率触发（rand()%100 < 10）
      {
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        *(this + 2153) = 2;  // this+8612〔uAI8612(推断)〕
        if ( rand() % 100 < 30 )  // 30% 概率触发（rand()%100 < 30）
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "KERA_CAST", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      }
      if ( *(this + 1813) == 0 || *((uint8_t *)this + 8624) != 0 || *(this + 2157) >= 5 || rand() % 300 >= 5 )  // 复合条件判定（与/或）
        goto LABEL_25;
      result = *(this + 1908);  // this+7632〔uWindow7632(推断)〕
      if ( result == 2 && *(this + 1909) == 0 || result == 0 )  // this+7636〔nPosWinY〕
      {
        v3 = sub_4D8FE0(this);  // v3 = 调 sub_4D8FE0 返回值
        result = sub_591C90(this, 2 * v3);  // 同房间近距玩家计数
        if ( result < 2 )  // 若 result < 2
        {
          v4 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this) / 10;  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
          result = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
          if ( result >= v4 )  // 若 result >= v4
          {
            (*(void (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
            (*(void (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
            sub_5922B0(this);  // 召唤特效生成（Summon.ani）
            v5 = *this;
            *(this + 2153) = 1;  // this+8612〔uAI8612(推断)〕
            (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v5 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
              this,
              "KERA_COMMAND",  // 标签 KERA_COMMAND
              -1,
              0,
              0);
            *((uint8_t *)this + 8624) = 1;  // this+8624〔uAI8624(推断)〕
LABEL_25:  // 标签 LABEL_25（跳转合流点）
            nRand = rand();  // nRand = 调 rand
            v7 = nRand % 100;
            result = nRand / 100;
            if ( v7 < 1 )  // 若 v7 < 1
            {
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
              v8 = *this;
              *(this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
              return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                       this,
                       "KERA_CAST",  // 标签 KERA_CAST
                       -1,
                       0,
                       0);
            }
          }
        }
      }
      return result;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result == 0 )  // 若 result 为 0
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      return result;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      return result;
    default:  // 默认分支
      return result;
  }
}



// 克拉赫资源装载：sub_4015C0 注册 R_KERA_ATK/DMG/DIE + SOR_APPEAR 语音槽；
//   sub_4BA9E0 装载 Monster/Soceress/{Hair02,Cloth02,Weapon02,Acc02}.equ 四件外观
// ------------------------------------------------------------
// 0x592650 sub_592650 —— 克拉赫初始化·语音/外观/AI 参数装载
// 属性五连设值 this+1698..1702（2/2/2/3/4【推断：属性/抗性档位】）→ sub_4015C0 注册
// R_KERA_ATK/R_KERA_DMG/R_KERA_DIE/SOR_APPEAR 语音槽 → 4 次 new 0x544 经 sub_4BA9E0
// 装载 Monster/Soceress/Hair02/Cloth02/Weapon02/Acc02.equ 四件外观（vt+784 穿戴）；
// AI 参数 this+1830=100/this+1839=-30/this+1831=570【推断：判定基准/偏移/范围】，
// 按 3 号攻击盒值在 this+1820..1821 区间 lerp（sub_4049C0）装阈值 this+2150/2152，
// clock_now(this+9) 记登场时刻 this+2155，冷却 this+2120=10/this+2121=2000，技能id this+2154=30059【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_592650(uint32_t *this)  // 实现：克拉赫初始化·语音/外观/AI 参数装载
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

  *(this + 1698) = 2;  // ── 属性/抗性五连设值【推断】 ──
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_KERA_ATK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_KERA_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_KERA_DIE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("SOR_APPEAR", 0xAu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Soceress/Hair02.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v3 = nullptr;  // v3 = 空指针
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_4BA9E0(pMem2, "Monster/Soceress/Cloth02.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v6 = nullptr;  // v6 = 空指针
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj2 != 0 )  // 若 pObj2 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem3 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v9 = sub_4BA9E0(pMem3, "Monster/Soceress/Weapon02.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v9 = nullptr;  // v9 = 空指针
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v9);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj4 != 0 )  // 若 pObj4 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem4 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v12 = sub_4BA9E0(pMem4, "Monster/Soceress/Acc02.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v12 = nullptr;  // v12 = 空指针
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj3 != 0 )  // 若 pObj3 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  v14 = *this;
  *(this + 1830) = 100;   // AI 参数：攻击判定X基准
  *(this + 1839) = -30;   // AI 参数：Y 偏移
  *(this + 1831) = 570;   // AI 参数：射程/判定范围【推断】
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v14 + 384))(this, 0);  // 坐标取值0
  v22 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 坐标取值1
  fld_e1821 = *(this + 1821) - *(this + 1820);  // lerp 区间宽
  v16 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v20 = (float)v22;
  v19 = (float)(int)Block;
  fld_e1820 = (uint64_t)sub_4049C0(v19, v20, *v16 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】按攻击盒值在区间内插值
  HIDWORD(fld_e1820) = *this;
  *(this + 2150) = fld_e1820;  // this+8600〔uAI8600(推断)〕
  *(this + 2152) = (*(int (/*thiscall*/ **)(uint32_t *, int))(HIDWORD(fld_e1820) + 384))(this, 2);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】记录登场时刻
  *(this + 2155) = result;  // this+8620〔uAI8620(推断)〕
  *(this + 2120) = 10;     // 冷却帧数 10
  *(this + 2121) = 2000;   // 冷却帧数 2000（长冷却技）
  *(this + 2154) = 30059;  // 本体技能id 30059【推断】
  return result;
}



// 子类扩展字段复位（this+8600..8660）
// ------------------------------------------------------------
// 0x5928E0 sub_5928E0 —— 子类扩展AI字段整块复位（this+8600..8660）
// 本家族（彼诺修/能量球系）子类 AI 数据块的出厂复位：this+8600=发射组门清零、
// this+8604 置 1（子类 AI 状态字节；与 sub_5908C0 清 0 相反，此处初始化为已就绪【推断】）、
// this+8612/8616/8648 计数与缓存清零、this+8644 相位门清零、this+8660 标志清零；
// 供登场/重生时重建子类 AI 初始态【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5928E0(int this)  // 实现：子类扩展AI字段整块复位（this+8600..8660）
{
  *(uint32_t *)(this + 8600) = 0;  // this+8600〔uAI8600(推断)〕
  *(uint32_t *)(this + 8604) = 1;  // this+8604〔bAI8604(推断)〕
  *(uint32_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint32_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  *(uint8_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8660) = 0;  // this+8660〔uEvt8660(推断)〕
  return 0;
}



// 【vmt200 命中处理器覆写】小型时钟门版（虚表 0x6CE04C +512 槽）：sub_699000 时钟读 + this+86xx 门控
// ------------------------------------------------------------
// 0x592920 sub_592920 —— 命中处理覆写（vmt200 小型时钟门版）
// vmt200 命中处理器覆写（虚表 0x6CE04C +512 槽引用，研究 20 §1.2）：先转发
// sub_4DA3B0 命中包分发（研究 §1.1 case 0x1 链）并以其返回值为返回值；
// 裸命中（nArg4==0）时 vt+1104(this,4) 切受击姿态，并用 clock_now（sub_699000，
// 冻结感知时钟）记 this+2159=受击时刻，供主 AI 的受击冷却门读取【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_592920(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：命中处理覆写（vmt200 小型时钟门版）
{
  int nHitResult; // edi

  nHitResult = sub_4DA3B0(nArg2, nArg3, nArg4);  // 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
  if ( (uint8_t)nArg4 == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 切受击姿态
    *(this + 2159) = sub_699000((int)(this + 9));  // 记录受击时刻（主AI冷却门用）
  }
  return nHitResult;
}



// 攻击发射（彼诺修变体）：技能id 从场景数据链取存 this+2151，以记忆落点 this+2163/2164 施放；
//   施放计数 this+2162+1、清相位门 this+8644
// ------------------------------------------------------------
// 0x592970 sub_592970 —— 彼诺修落点施放（读场景数据链取技能id）
// vt+308 可行动校验通过后：三级解引场景数据（this+29→+132→+108→+112）把技能id
// 存 this+2151；vt+152 申请攻击序号（参 0xFFFF），vt+376 以记忆落点 this+2163/2164
// （由 sub_592F50 前跳试探写入）施放该技能，vt+592 挂接表现对象 this+2152；
// 末尾施放计数 this+2162 自增、清相位门 this+8644
// ------------------------------------------------------------
int /*thiscall*/ sub_592970(uint32_t *this, int nArg2, int nArg3)  // 实现：彼诺修落点施放（读场景数据链取技能id）
{
  int result; // eax
  int nVt; // edi
  int nAtkReq; // eax
  int hCastObj; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    nVt = *this;
    *(this + 2151) = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 108) + 112);  // 技能id（三级解引）
    nAtkReq = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(nVt + 152))(  // 调虚槽 +152：效果通道 3
           this,
           2,
           0,
           0,
           0xFFFF,
           0,
           0,
           0,
           0);
    hCastObj = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 376))(  // 调虚槽 +376：坐标同步包（type 37）
           this,
           *(this + 2151),  // this+8604〔bAI8604(推断)〕
           *(this + 2163),  // this+8652〔uPhase8652(推断)〕
           *(this + 2164),  // this+8656〔uPair8656(推断)〕
           0,
           nAtkReq);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(nVt + 592))(this, *(this + 2152), hCastObj);  // this+8608〔uAI8608(推断)〕
    result = *(this + 2162) + 1;  // 施放计数+1
    *((uint8_t *)this + 8644) = 0;  // 清相位门
    *(this + 2162) = result;  // this+8648〔uPhase8648(推断)〕
  }
  return result;
}



// 施法走位主门（克拉赫侧移施法，this+200 主状态内）：动画帧到达帧表 {3,3,6,6}（步进2）时
//   横向瞬移（偏移表 v14/侧别表 v15，±500 落点偏移）并发动 vt+584 多参攻击；
//   动画结束(+170)→ vt+564 收尾 + vt+560(this,16,0,2,0) 切主状态16
// ------------------------------------------------------------
// 0x592A00 sub_592A00 —— 克拉赫侧移施法主门（this+200 主状态内的帧驱动走位）
// 帧表 v16={3,3,6,6}、偏移表 v14（奇槽X/偶槽Y）、侧别表 v15 三组栈上常量表驱动：
// 动画当前帧（+148）等于本步应到帧且相位门 this+8624 空闲时，按 this+2157 步索引
// 取 ±500 侧向落点，经 vt+584 十四参攻击发射（技能id this+2154=30059、
// 插值参 this+2150、全局管理器 dword_8F82C8+28 查询值），置 this+8624=1 防重复；
// 帧走过应到帧+1 → this+2157 步进+2 并复开门；动画播完（+170）→ vt+564 收尾
// + vt+560(this,16,0,2,0) 切主状态 16
// ------------------------------------------------------------
int /*thiscall*/ sub_592A00(uint32_t *this)  // 实现：克拉赫侧移施法主门（this+200 主状态内的帧驱动走位）
{
  int v2; // eax
  int fld_e2157; // edi | =+0x21B4 字段 x1（证据 005A8900）
  int fld_e21572; // ebx
  int v5; // eax
  int v6; // edx
  int v7; // ebx
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int fld_e21573; // ecx
  int result; // eax
  int nUnused100; // [esp+Ch] [ebp-44h]
  uint32_t v14[7]; // [esp+10h] [ebp-40h]
  uint32_t v15[4]; // [esp+2Ch] [ebp-24h]
  uint32_t v16[4]; // [esp+3Ch] [ebp-14h]
  int v17; // [esp+4Ch] [ebp-4h]

  v16[0] = 3;  // 步0 应到帧
  v16[1] = 3;  // 步1
  v16[2] = 6;  // 步2
  v16[3] = 6;  // 步3
  v15[0] = 1;  // 步0 侧别=1（左）
  v15[3] = 1;  // 步3 侧别=1
  v2 = *this;
  nUnused100 = 100;
  v14[0] = 0;   // ── 偏移表（奇数槽=X偏移 / 偶数槽=Y偏移） ──
  v14[1] = 0;
  v14[2] = 50;
  v14[3] = -100;
  v14[4] = 0;
  v14[5] = 0;
  v14[6] = -50;
  v15[1] = 0;
  v15[2] = 0;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(v2 + 200))(this) + 148) == v16[*(this + 2157)]  // 当前帧==本步应到帧
    && *((uint8_t *)this + 8624) == 0 )  // 且相位门空闲
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F82C8 + 28))(dword_8F82C8);  // 全局管理器查询
      fld_e2157 = v14[2 * *(this + 2157) - 1] + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // X偏移+当前X
      fld_e21572 = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 当前Y
      v6 = v14[2 * fld_e21572];  // Y偏移
      v7 = v15[fld_e21572];  // 侧别
      v8 = v6 + v5;
      v9 = fld_e2157 + 500;  // 落点X+500
      if ( v7 != 0 )  // 若 v7 非 0
        v9 = fld_e2157 - 500;  // 侧别1→-500
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int, int, uint32_t, uint32_t, int, int, int, int, uint32_t, uint32_t))(*this + 584))(  // 调虚槽 +584
        this,
        v9,
        v8,
        400,
        fld_e2157,
        v8,
        *(this + 2154),   // 技能id 30059
        *(this + 2150),   // lerp 插值参数
        v17,
        v7,
        100,
        2,
        0,
        0);
    }
    *((uint8_t *)this + 8624) = 1;  // 本步已发动
  }
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  fld_e21573 = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
  if ( *(uint32_t *)(v10 + 148) == v16[fld_e21573] + 1 )  // 帧走过→步进+2
  {
    *((uint8_t *)this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
    *(this + 2157) = fld_e21573 + 2;  // this+8628〔nPoolTime(推断)〕
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  if ( *(uint8_t *)(result + 170) != 0 )  // 动画播完标志
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
    if ( (uint8_t)result != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);  // 收尾清理
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t))(*this + 560))(this, 16, 0, 2, 0);  // 切主状态16
    }
  }
  return result;
}



// 闪避/自buff AI：50% 概率 sub_4DC730（位移闪避【推断】）；15% 概率 vt+580 释放 buff 48013（10级）
// ------------------------------------------------------------
// 0x592B90 sub_592B90 —— 求援/自buff AI（50% 聚合广播 + 15% 自施增益）
// vt+308 可行动校验通过后掷两次百分骰：50% 触发 sub_4DC730 同队怪物聚合广播
// （包 type 29；对该怪而言即向同图同伴求援聚拢【推断】）；
// 15% 经 vt+580 给自己施放 buff 48013（10 级，尾参 4）
// ------------------------------------------------------------
int /*thiscall*/ sub_592B90(void *this)  // 实现：求援/自buff AI（50% 聚合广播 + 15% 自施增益）
{
  int result; // eax
  int nRand; // eax
  int nPct; // et2

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    if ( rand() % 100 < 50 )  // 50% 概率
      sub_4DC730(this);  // 同队怪物聚合广播（包 type 29）
    nRand = rand();  // nRand = 调 rand
    nPct = nRand % 100;
    result = nRand / 100;
    if ( nPct < 15 )  // 15% 概率
      return (*(int (/*thiscall*/ **)(void *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
               this,
               48013,  // buff/skill id 48013
               10,     // 等级10
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



// 死亡匹配清门：死亡对象==记忆目标 this+1815 且 vt+316 检查通过 → vt+312(this,0) 清门
// ------------------------------------------------------------
// 0x592C00 sub_592C00 —— 目标死亡回调（记忆目标匹配清门）
// 死亡对象 nArg2 等于记忆目标 this+1815 且 vt+316 校验通过时，vt+312(this,0)
// 清攻击门/复位追击标志；无论是否命中都尾调 sub_4D9170(nArg2)
// （死亡事件继续向上分发【推断：基类链】）
// ------------------------------------------------------------
int /*thiscall*/ sub_592C00(uint32_t *this, int nArg2)  // 实现：目标死亡回调（记忆目标匹配清门）
{
  if ( nArg2 == *(this + 1815) && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 316))(this) != 0 )  // 调虚槽 +316：CNEquipmentTeachingofGoraBoldness__vmt13C
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);  // 清门/复位标志
  return sub_4D9170(nArg2);  // 返回 调 sub_4D9170 返回值
}



// 能量球技能（118L）：动画帧≥3 且 this+8600 门开时分三相位发射——
//   相位0: vt+580 直接发射 30360 + Particle/EnergyBall.ptl（70/63 参数）；
//   相位1/2: sub_64B6C0 生成双子能量球（坐标组 1-3 / 4-6，球id 1/23）
// ------------------------------------------------------------
// 0x592C40 sub_592C40 —— 能量球三相位发射（118L 技能，双子球召唤物）
// 入场一次性蓄力：this+2090 已激活且 this+8609 未置时置 8609=1 并 vt+1312 播蓄力表现；
// 动画状态==8 时按 vt+908 相位-2 分派，各相位均要求帧≥3、vt+308 可行动、
// 组门 this+8600 开（发射即关门，每组只发一次）：
//   相位0：vt+588 装载 Particle/EnergyBall.ptl 粒子，vt+580 直接发射技能 30360（70/63 参）；
//   相位1：vt+384 取坐标组 1/2/3，sub_64B6C0 生成球id 1 的双子能量球（0x1D0 对象）；
//   相位2：坐标组 4/5/6，同法生成球id 23；生成后 vt+56 绑定宿主，尾调 sub_4E1780
// ------------------------------------------------------------
char /*usercall*/ sub_592C40@<al>(uint8_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：能量球三相位发射（118L 技能，双子球召唤物）
{
  int nVt1; // eax
  int nFrame; // edi
  int nPhase; // eax
  int nPhaseIdx; // eax
  int nX2; // edi
  int nY2; // ebx
  int nZ2; // eax
  int *pOrbObj; // eax
  int nX1; // edi
  int nY1; // ebx
  int nZ1; // eax
  int nArg0; // edx
  int nOrbVt; // edx
  int nVt2; // eax
  void *pPtcl; // eax
  int nVt3; // edi
  int nAtkReq; // eax
  int nOrbSpecA; // [esp+4h] [ebp-28h] BYREF
  char bOrbSpecA2; // [esp+8h] [ebp-24h]
  float fOrbSpecA3; // [esp+Ch] [ebp-20h]
  int nOrbSpecB; // [esp+10h] [ebp-1Ch] BYREF
  char bOrbSpecB2; // [esp+14h] [ebp-18h]
  float fOrbSpecB3; // [esp+18h] [ebp-14h]
  void *Block; // [esp+1Ch] [ebp-10h]
  int nFreeState; // [esp+28h] [ebp-4h]

  if ( *((uint32_t *)pArg1 + 2090) != 0 && pArg1[8609] == 0 )  // 复合条件判定（与/或）
  {
    nVt1 = *(uint32_t *)pArg1;
    pArg1[8609] = 1;
    (*(void (**)(void))(nVt1 + 1312))();  // 前置虚调用（蓄力表现【推断】）
  }
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 840))(pArg1) == 8 )  // 动画状态8
  {
    nFrame = *(uint32_t *)(*((uint32_t *)pArg1 + 30) + 148);  // 当前帧
    nPhase = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 908))(pArg1) - 2;  // 相位-2
    if ( nPhase != 0 )  // 若 nPhase 非 0
    {
      nPhaseIdx = nPhase - 1;
      if ( nPhaseIdx != 0 )  // 若 nPhaseIdx 非 0
      {
        if ( nPhaseIdx == 1  // 若 nPhaseIdx == 1
          && nFrame >= 3
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0  // 调虚槽 +308：是否本地玩家
          && pArg1[8600] != 0 )  // 相位2：第二组双子球
        {
          nX2 = (*(int (/*thiscall*/ **)(uint8_t *, int, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 4, nArg3, nArg2);  // 坐标组4
          nY2 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 5);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
          nZ2 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 6);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
          pArg1[8600] = 0;  // 关门：每组只发一次
          fOrbSpecB3 = (float)nZ2;
          nOrbSpecB = 23;  // 球id 23
          bOrbSpecB2 = 0;
          Block = operator new(0x1D0u);  // new(464 字节) 分配对象
          nFreeState = 1;
          if ( Block != nullptr )  // 若 Block 有效（非空）
          {
            pOrbObj = (int *)sub_64B6C0(nX2, &nOrbSpecB, 1, nY2, 1, 1);  // 火焰动画查询（5910D0）
LABEL_19:  // 标签 LABEL_19（跳转合流点）
            nOrbVt = *pOrbObj;
            nFreeState = -1;
            (*(void (/*thiscall*/ **)(int *, uint8_t *, uint8_t *, uint32_t, uint32_t))(nOrbVt + 56))(pOrbObj, pArg1, pArg1, 0, 0);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
            return sub_4E1780(pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
          }
          goto LABEL_18;
        }
      }
      else if ( nFrame >= 3 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && pArg1[8600] != 0 )  // 相位1：第一组双子球
      {
        nX1 = (*(int (/*thiscall*/ **)(uint8_t *, int, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 1, nArg3, nArg2);  // 坐标组1
        nY1 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 2);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
        nZ1 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 3);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
        pArg1[8600] = 0;  // 关门
        fOrbSpecA3 = (float)nZ1;
        nOrbSpecA = 1;  // 球id 1
        bOrbSpecA2 = 0;
        Block = operator new(0x1D0u);  // new(464 字节) 分配对象
        nFreeState = 0;
        if ( Block != nullptr )  // 若 Block 有效（非空）
        {
          pOrbObj = (int *)sub_64B6C0(nX1, &nOrbSpecA, 1, nY1, 1, 1);  // 火焰动画查询（5910D0）
          goto LABEL_19;
        }
LABEL_18:  // 标签 LABEL_18（跳转合流点）
        pOrbObj = nullptr;  // pOrbObj = 空指针
        goto LABEL_19;
      }
    }
    else if ( nFrame >= 3 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && pArg1[8600] != 0 )  // 相位0：单体能量弹
    {
      nArg0 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)pArg1 + 384))(pArg1, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
      nVt2 = *(uint32_t *)pArg1;
      pArg1[8600] = 0;  // 关门
      pPtcl = (void *)(*(int (/*thiscall*/ **)(uint8_t *, const char *))(nVt2 + 588))(pArg1, "Particle/EnergyBall.ptl");  // 能量弹粒子
      nVt3 = *(uint32_t *)pArg1;
      Block = pPtcl;
      nAtkReq = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t))(nVt3 + 152))(pArg1, 0, 0, 0);  // 调虚槽 +152：效果通道 3
      (*(void (/*thiscall*/ **)(uint8_t *, int, int, void *, uint32_t, int, uint32_t, int, int))(nVt3 + 580))(
        pArg1,
        30360,  // 技能id 30360
        nArg0,
        Block,
        0,
        70,
        0,
        63,
        nAtkReq);
    }
  }
  return sub_4E1780(pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}


// 主状态机小调度（this+1787）：态0→vt+1284 待机逻辑；态4/5/13/14/15→按有无目标
//   this+1813 用 vt+1104 在动画 5/13 间切换（无目标=13 待机，有目标=5 追击【推断】）
// ------------------------------------------------------------
// 0x592EB0 sub_592EB0 —— 主状态机小调度（this+1787 分派待机/追击切换）
// 头调 sub_4E0120（基类周期处理）后按 this+1787 分派：态 0 → vt+1284 待机逻辑；
// 态 4/5/13/14/15 → 按目标槽 this+1813 有无，用 vt+1104 在动画 5/13 间切换
// （有目标=5 追击、无目标=13 待机【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_592EB0(int *this)  // 实现：主状态机小调度（this+1787 分派待机/追击切换）
{
  int result; // eax
  int *pThis; // ecx

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调虚槽 +1284
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      pThis = this;
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
        goto LABEL_9;
      goto LABEL_4;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result == 0 )  // 若 result 为 0
LABEL_4:  // 标签 LABEL_4（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
      {
        pThis = this;
LABEL_9:  // 标签 LABEL_9（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(pThis, 5);  // 调虚槽 +1104
      }
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// 前跳试探（彼诺修版）：面向偏移 ±75 试探落点写 this+2163/2164，成功→ sub_592970 落点施放
// ------------------------------------------------------------
// 0x592F50 sub_592F50 —— 前跳试探落点（彼诺修版，喂 sub_592970 施放）
// 按面向（vt+152）取 ±75 前方试探点，sub_499560 试探可落性并把落点写
// this+2163/2164（模式 3）；成功则调 sub_592970 以该落点施放
// ------------------------------------------------------------
int /*thiscall*/ sub_592F50(int *this)  // 实现：前跳试探落点（彼诺修版，喂 sub_592970 施放）
{
  int v2; // edi
  int v3; // edi
  int v4; // eax
  int result; // eax

  v2 = 75;
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0 )  // 调虚槽 +152：效果通道 3
    v2 = -75;
  v3 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v2;  // 调虚槽 +120：动画对象
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  result = sub_499560(this, this + 2163, this + 2164, v3, v4, 3);  // 重试式预约（延迟 30 起每次 +10，最多 nArg6 次）
  if ( (uint8_t)result != 0 )
    return sub_592970(this, *(this + 2163), *(this + 2164));  // 彼诺修落点施放（读场景数据链取技能id）
  return result;
}



// 瞬移绕背（彼诺修）：找 300 内可攻击玩家，按相对站位瞬移到其背后 500 处
//   （vt+120 比较决定 +/-500），vt+584 写回坐标
// ------------------------------------------------------------
// 0x592FB0 sub_592FB0 —— 瞬移绕背（彼诺修位移技：找 300 内玩家闪现其身后 500）
// 遍历场景对象表（this+29→+120 数组/+124 计数），筛选：对象 vt+40(17) 状态校验
// 【推断：存活可选中】、sub_4E4630 敌我判定可攻击、sub_4E5CA0==0（冻结豁免门，
// 研究 §8）、vt+8 距离≤300、vt+940 无标记；命中后按自身 X 与目标 X 的相对位置
// 取目标身后 ±500 落点，经目标 vt+120/124 换算高度与全局管理器（dword_8F82C8+28）
// 参数后，vt+584 写回自身坐标完成瞬移
// ------------------------------------------------------------
int /*usercall*/ sub_592FB0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>)  // 实现：瞬移绕背（彼诺修位移技：找 300 内玩家闪现其身后 500）
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

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
    {
      v6 = pArg1[29];  // v6 = 取 pArg1[29]
      v7 = *(uint32_t *)(v6 + 120);
      result = v7 != 0 ? (*(uint32_t *)(v6 + 124) - v7) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)i >= result )
        break;  // 跳出循环/分支
      v8 = *(uint32_t *)(v6 + 120);
      if ( v8 != 0 && i < (*(uint32_t *)(v6 + 124) - v8) >> 2 )  // 若 v8 != 0
        pObj = *(uint32_t *)(v8 + 4 * i);
      else  // 否则分支
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        && (uint8_t)sub_4E4630(pObj) != 0  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
        && (uint8_t)sub_4E5CA0(pObj) == 0  // 阵营号 200..204 判定（200 起逐个比较）
        && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, pObj, 0) <= 300  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 940))(pObj) == 0 )  // 调虚槽 +940
      {
        v10 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 120))(pObj, nArg3, nArg2);  // 调虚槽 +120：动画对象
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) < v10;  // 调虚槽 +120：动画对象
        if ( v11 )
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) - 500;  // 调虚槽 +120：动画对象
        else  // 否则分支
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) + 500;  // 调虚槽 +120：动画对象
        v20 = v12;
        v19 = *pArg1;
        v13 = (*(int (/*thiscall*/ **)(int, BOOL, int, int))(*(uint32_t *)dword_8F82C8 + 28))(dword_8F82C8, v11, 100, 2);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
        v14 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 124))(pObj, pArg1[2154], pArg1[2150], v13);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v14);  // 调虚槽 +120：动画对象
        v16 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 124))(pObj, 400, v15);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v19 + 584))(pArg1, v20, v16);
      }
    }
  }
  return result;
}



// 跳跃着陆：this+81=目标高度 nArg2；播音效(vt+876 ×2) + 面向(vt+196) + vt+888(1,0,1000,1000) 锁定；
//   高度差 = nArg2 - vt+128 当前Z → sub_495890 给 ±1000 垂直速度；然后 this+2157=nArg3、
//   清相位门 this+8624、清 this+1905 buff 标志数组（32字节步进首字节）
// ------------------------------------------------------------
// 0x5930F0 sub_5930F0 —— 跳跃着陆结算（落点高度 nArg2 / 状态参 nArg3）
// this+81=目标高度后：vt+876 两级播音效（全局+实例）、vt+196 按 this+1554→+8 设面向、
// sub_4926A0 复位 this+30 帧游标、vt+888(1,0,1000,1000) 位移锁定；
// 高度差 = 目标高度 - vt+128 当前 Z：非零 → sub_495890 给 ±1000 垂直速度 +
// sub_4A0550/sub_4A0600(2) 下落结算；为零 → 清 this+28 对象的 +64 浮点标志与
// +196 字节、sub_495890(2,0) 落定；末尾 this+2157=nArg3、清相位门 this+8624、
// 逐 32 字节步进清 this+1905 buff 标志数组
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5930F0(int *this, int nArg2, int nArg3)  // 实现：跳跃着陆结算（落点高度 nArg2 / 状态参 nArg3）
{
  int v4; // edx
  int fld_e81; // edi | =+0x0144 字段 x1（证据 004D6970）
  uint32_t *fld_e28; // edi
  unsigned int result; // eax
  unsigned int v8; // ecx
  int i; // edx
  int fld_e1905; // edi | =+0x1DC4 字段 x1（证据 0059A020）

  v4 = *this;
  *(this + 81) = nArg2;  // this+324〔nRandPick324〕
  (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v4 + 876))(0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 8));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  sub_4926A0(*(this + 30));  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  fld_e81 = *(this + 81) - (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  if ( fld_e81 != 0 )  // 若 fld_e81 非 0
  {
    sub_495890(0, fld_e81 <= 0 ? 1000 : -1000);  // 模式选择式方位设置（1/2/其他 三分支）
    sub_4A0550(fld_e81);  // 调 镜头幅度
    result = sub_4A0600(2);  // result = 调 sub_4A0600 返回值
  }
  else  // 否则分支
  {
    fld_e28 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
    if ( *fld_e28 != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0  // 调虚槽 +308：是否本地玩家
      && *((float *)fld_e28 + 6) != 0.0 )
    {
      fld_e28[6] = 0;
      *((uint8_t *)fld_e28 + 196) = 1;
    }
    result = sub_495890(2, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  }
  *(this + 2157) = nArg3;  // this+8628〔nPoolTime(推断)〕
  v8 = 0;
  *((uint8_t *)this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
  for ( i = 0; ; i += 32 )  // 遍历循环
  {
    fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    if ( fld_e1905 == 0 )  // 若 fld_e1905 为 0
      break;  // 跳出循环/分支
    result = (*(this + 1906) - fld_e1905) >> 5;
    if ( v8 >= result )  // 若 v8 >= result
      break;  // 跳出循环/分支
    result = i + fld_e1905;
    ++v8;
    *(uint8_t *)(i + fld_e1905) = 0;
  }
  return result;
}



// buff 标志数组恢复：this+1905 数组（32字节步进）全部置1，随后 this+81=计时字段 this+2155
// ------------------------------------------------------------
// 0x593230 sub_593230 —— buff 标志数组全置 1 + 目标高度取计时字段（sub_593840 狂气buff 释放时调用）
// this+1905 数组（32 字节步进）首字节全部置 1（解除 0x5930F0/0x593340 的清位），
// 末尾 this+81 = this+2155 计时字段
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_593230(unsigned int *this)  // 实现：buff 标志数组全置 1 + 目标高度取计时字段（sub_593840 狂气buff 释放时调用）
{
  unsigned int v1; // edx
  int i; // esi
  int fld_e1905; // edi | =+0x1DC4 字段 x1（证据 0059A020）
  unsigned int result; // eax

  v1 = 0;
  for ( i = 0; ; i += 32 )  // 遍历循环
  {
    fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    if ( fld_e1905 == 0 )  // 若 fld_e1905 为 0
    {
      result = *(this + 2155);  // this+8620〔uAI8620(推断)〕
      *(this + 81) = result;  // this+324〔nRandPick324〕
      return result;
    }
    result = (int)(*(this + 1906) - fld_e1905) >> 5;
    if ( v1 >= result )  // 若 v1 >= result
      break;  // 跳出循环/分支
    ++v1;
    *(uint8_t *)(i + fld_e1905) = 1;
  }
  *(this + 81) = *(this + 2155);  // this+324〔nRandPick324〕
  return result;
}



// 缩放演出驱动：vt+1172 帧计数在 0..30 区间内用 sub_4049C0 在两坐标间插值，
//   ×0.01 得缩放比 → vt+688(1.0) 复位 + sub_4EB4B0/sub_4EB2C0 应用，并对 this+1617 起
//   18 个子对象槽应用 sub_4EB6A0 缩放（巨型化/缩小演出【推断】）
// ------------------------------------------------------------
// 0x593280 sub_593280 —— 缩放演出驱动（30 帧内插值出缩放比并应用到本体+18 部件）
// vt+1172 帧计数与 vt+384 取上/下限（参 0/10）喂 sub_4049C0（区间线性插值）
// 在 0..30 帧内插值，×0.01 得缩放比；vt+688(1.0f) 先复位本体缩放，
// sub_4EB4B0/sub_4EB2C0 应用插值结果，再对 this+1617 起 18 个子部件槽
// 非空者逐个 sub_4EB6E0/sub_4EB6A0 施加同比例缩放（巨型化/缩小演出【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_593280(uint32_t *this)  // 实现：缩放演出驱动（30 帧内插值出缩放比并应用到本体+18 部件）
{
  int v2; // edi
  int result; // eax
  uint32_t *pThis_651; // esi
  int i; // ebx
  float v6; // [esp+4h] [ebp-28h]
  float v7; // [esp+8h] [ebp-24h]
  float v8; // [esp+24h] [ebp-8h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1172))(this);  // 当前帧计数
  v7 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);  // 插值上限
  v6 = (float)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 10);  // 插值下限
  v8 = (double)(int)(uint64_t)sub_4049C0(v6, v7, v2, 30) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】30帧内插值→百分比
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 688))(this, 1065353216);  // 1.0f 缩放复位
  sub_4EB4B0(COERCE_FLOAT(11));  // 与 ·0x4EB2C0 同构（差异：·sub_4923F0 按倒数缩放）
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);  // 调虚槽 +688：附加块基址 this+6160
  result = sub_4EB2C0(v8);  // 应用插值缩放
  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )  // 对 18 个子部件应用同比例缩放
  {
    if ( *pThis_651 != 0 )
    {
      sub_4EB6E0(1.0);  // 与 ·0x4EB6A0 同构（差异：调 ·0x4EB4B0）
      result = sub_4EB6A0(v8);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
    }
    ++pThis_651;
  }
  return result;
}



// 帧阈值清 buff 标志：帧数>0 清 +64/+96/+128 位（分档 >5/>10/>15，逐步清更多 buff 位）
// ------------------------------------------------------------
// 0x593340 sub_593340 —— 帧阈值分级清 buff 标志（>0/>5/>10 逐档多清一位）
// vt+1172 帧数>0 时清 this+1905 数组内偏移 +64 位；帧数>5 再清 +96 位；
// 帧数>10 再清 +128 位；帧数>15 不动（分档解除攻击/受击相关 buff 位【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_593340(int *this)  // 实现：帧阈值分级清 buff 标志（>0/>5/>10 逐档多清一位）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 1172))(this);  // 调虚槽 +1172
  if ( result > 0 )  // 若 result > 0
  {
    if ( result > 5 )  // 若 result > 5
    {
      if ( result > 10 )  // 若 result > 10
      {
        if ( result > 15 )  // 若 result > 15
          return result;
        goto LABEL_5;
      }
    }
    else  // 否则分支
    {
      *(uint8_t *)(*(this + 1905) + 64) = 0;  // this+7620〔pStatusPanel(推断)〕
    }
    *(uint8_t *)(*(this + 1905) + 96) = 0;  // this+7620〔pStatusPanel(推断)〕
LABEL_5:  // 标签 LABEL_5（跳转合流点）
    result = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    *(uint8_t *)(result + 128) = 0;
  }
  return result;
}



// ============================================================
// 【分区 3】魔法师·彼诺修 & 路易斯（Vino & Luis）（0x5933A0-0x594370）
// 证据：VINO/R_LUIS_*/R_VINO_* 语音、AURA_FURY 狂气光环、VINO_CAST/VINO_COMMAND、
//       Monster/Soceress/Hair01-Cloth01-Weapon01-Acc01.equ 与 Luis_* 五件套

// 瞬移绕背（彼诺修多人版）：同 sub_592FB0 但遍历不返回，逐玩家瞬移并计数 v23；
//   施放参数带技能id 30362 与 vt+384(9) 高度
// ------------------------------------------------------------
// 0x5933A0 sub_5933A0 —— 瞬移绕背多人版（彼诺修 AOE 位移：逐个闪现至各玩家身后）
// 同 sub_592FB0 的筛选链（vt+40(17)/sub_4E4630 可攻击/sub_4E5CA0 冻结豁免门/
// vt+8 距离≤300/vt+940 无标记）但不提前返回：命中即按目标身后 ±500 落点
// vt+584 瞬移并计数 v23，直至 v23 达 nArg4 上限或遍历完；施放参数带
// 技能id 30362 与 vt+384(9) 取得的高度，nArg2/nArg3 用后即清零
// ------------------------------------------------------------
int /*userpurge*/ sub_5933A0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>, int nArg4)  // 实现：瞬移绕背多人版（彼诺修 AOE 位移：逐个闪现至各玩家身后）
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

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    v6 = 0;
    v23 = 0;
    v21 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 384))(pArg1, 9);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
    while ( 1 )  // 条件循环
    {
      v7 = pArg1[29];  // v7 = 取 pArg1[29]
      v8 = *(uint32_t *)(v7 + 120);
      v22 = v6;
      result = v8 != 0 ? (*(uint32_t *)(v7 + 124) - v8) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)v6 >= result )
        break;  // 跳出循环/分支
      v9 = *(uint32_t *)(v7 + 120);
      if ( v9 != 0 && v6 < (*(uint32_t *)(v7 + 124) - v9) >> 2 )  // 若 v9 != 0
        pObj = *(uint32_t *)(v9 + 4 * v6);
      else  // 否则分支
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        && (uint8_t)sub_4E4630(pObj) != 0  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
        && (uint8_t)sub_4E5CA0(pObj) == 0  // 阵营号 200..204 判定（200 起逐个比较）
        && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, pObj, 0) <= 300  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 940))(pObj) == 0 )  // 调虚槽 +940
      {
        v11 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 120))(pObj, nArg3, nArg2);  // 调虚槽 +120：动画对象
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) < v11;  // 调虚槽 +120：动画对象
        if ( v12 )
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) - 500;  // 调虚槽 +120：动画对象
        else  // 否则分支
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) + 500;  // 调虚槽 +120：动画对象
        nArg2 = 0;
        nArg3 = 0;
        v24 = v13;
        v20 = *pArg1;
        v14 = (*(int (/*thiscall*/ **)(int, BOOL, int, int))(*(uint32_t *)dword_8F82C8 + 28))(dword_8F82C8, v12, 100, 2);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
        v15 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 124))(pObj, 30362, v21, v14);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v15);  // 调虚槽 +120：动画对象
        v17 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 124))(pObj, 400, v16);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v20 + 584))(pArg1, v24, v17);
        result = ++v23;
        if ( v23 >= nArg4 )  // 若 v23 >= nArg4
          return result;
        v6 = v22;
      }
      ++v6;
    }
  }
  return result;
}



// 彼诺修技能事件分发：ArgList 5/13 → vt+384(8/7) 取坐标后 sub_5933A0 绕背瞬移；
//   ArgList 8 → 按 fArg4 事件参数：值1 且有标记对象(this+7252)时以 30364 瞬移贴身
//   （狂气态100/常态130），值2..4 → 开门 this+8600=1（能量球待发）
// ------------------------------------------------------------
// 0x593510 sub_593510 —— 彼诺修动画事件分发（绕背瞬移 / 贴身瞬移 / 能量球开门）
// 首次进入（this+8604==0）先 sub_593340 清 buff 标志并记 this+8604=当前帧数；
// 事件 5/13 → vt+384(8/7) 取坐标喂 sub_5933A0 绕背瞬移；事件 8 按 fArg4 事件参数：
// 值 1 且标记对象 this+7252 非空且 vt+308 可行动 → 经对象 vt+124/120 以技能 30364
// （狂气态 100 / 常态 130）瞬移贴身后 vt+584 写回；值 2..4 → 开门 this+8600=1
// （能量球待发，供 sub_592C40 消费）；其余事件走 sub_4E33D0 基类转发
// ------------------------------------------------------------
int /*userpurge*/ sub_593510@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)  // 实现：彼诺修动画事件分发（绕背瞬移 / 贴身瞬移 / 能量球开门）
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

  if ( *(uint32_t *)(pArg1 + 8604) == 0 )  // pArg1+8604〔bAI8604(推断)〕
  {
    sub_593340((int *)pArg1);  // 帧阈值分级清 buff 标志（>0/>5/>10 逐档多清一位）
    *(uint32_t *)(pArg1 + 8604) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1172))(pArg1);  // 调虚槽 +1172
  }
  v7 = ArgList;
  if ( ArgList != 8 )  // 若 ArgList != 8
  {
    if ( ArgList == 13 )  // 若 ArgList == 13
    {
      v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 7);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
    }
    else  // 否则分支
    {
      if ( ArgList != 5 )  // 若 ArgList != 5
        return sub_4E33D0(v7, fArg4, nArg5, nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
      v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 8);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
    }
    sub_5933A0((uint32_t *)pArg1, nArg2, pArg1, v15);  // 瞬移绕背多人版（彼诺修 AOE 位移：逐个闪现至各玩家身后）
    return sub_4E33D0(v7, fArg4, nArg5, nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  }
  v8 = **(uint32_t **)(LODWORD(fArg4) + 4);
  if ( v8 == 1 )  // 若 v8 == 1
  {
    if ( *(uint32_t *)(pArg1 + 7252) != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      v9 = *(uint32_t *)pArg1;
      pObj = *(uint32_t *)(pArg1 + 7252);  // pArg1+7252〔当前目标〕
      v11 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pObj + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
              pObj,
              30364,
              0,
              0,
              4,
              *(uint32_t *)(pArg1 + 7632) != 0 ? 100 : 130,
              1,
              0,
              0);
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v11);  // 调虚槽 +120：动画对象
      v13 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 124))(pObj, 0, v12);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v13);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(int, int))(v9 + 584))(pArg1, v14);
      v7 = 8;
    }
  }
  else if ( v8 > 1 && v8 <= 4 )
  {
    *(uint8_t *)(pArg1 + 8600) = 1;  // pArg1+8600〔uAI8600(推断)〕
  }
  return sub_4E33D0(v7, fArg4, nArg5, nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}



// 出场处理：vt+1104 切主状态16，clock_now 存 this+2160（出场时刻）；
//   难度字段 this+1943==3（困难级）时注册 "VINO" 语音槽
// ------------------------------------------------------------
// 0x593640 sub_593640 —— 彼诺修出场处理（切主状态16 + 记出场时刻 + 困难级语音注册）
// sub_4D9760 观察者广播收尾后 vt+1104 切主状态 16；clock_now（sub_699000）存
// this+2160（出场时刻，sub_593AC0 的 18 秒节拍基准）；难度字段 this+1943==3
// （困难级）时 sub_4015C0 注册 VINO 语音
// ------------------------------------------------------------
int /*thiscall*/ sub_593640(uint32_t *this)  // 实现：彼诺修出场处理（切主状态16 + 记出场时刻 + 困难级语音注册）
{
  int result; // eax

  sub_4D9760();  // 观察者广播后条件收尾
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 16);  // 调虚槽 +1104
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  *(this + 2160) = result;  // this+8640〔uCastSlot8640(推断)〕
  if ( *(this + 1943) == 3 )  // this+7772〔nCounterState〕
    return sub_4015C0("VINO", 4u);  // 【std::string构造赋值】
  return result;
}



// 语音注册：R_LUIS_ATK/DMG/DIE + SOR_APPEAR（sub_4015C0 → 语音槽, 研究 28）
// ------------------------------------------------------------
// 0x593680 sub_593680 —— 路易斯（Soceress）语音注册（R_LUIS 三件套 + SOR_APPEAR）
// this+1698..1702 依次写 2/2/2/3/4（语音类别权重槽【推断】）；sub_4015C0 把
// R_LUIS_ATK / R_LUIS_DMG / R_LUIS_DIE / SOR_APPEAR 写入语音槽（研究 28，
// 由 vt+212 播报）；随后 this+2151 技能id、this+8609 蓄力标志清零，vt+1308 收尾
// ------------------------------------------------------------
int /*thiscall*/ sub_593680(uint32_t *this)  // 实现：路易斯（Soceress）语音注册（R_LUIS 三件套 + SOR_APPEAR）
{
  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_LUIS_ATK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_LUIS_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_LUIS_DIE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("SOR_APPEAR", 0xAu);  // 【std::string构造赋值】
  *(this + 2151) = 0;  // this+8604〔bAI8604(推断)〕
  *((uint8_t *)this + 8609) = 0;  // this+8609〔bAI8609〕
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 调虚槽 +1308：CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
}



// 挑衅标记撒播（彼诺修版）：同 sub_592000——对 300 内同房间玩家附加 sub_4DF1B0 生成的
//   挑衅特效对象（第二参 0/1 之差：本函数=0），vt+56 绑定
// ------------------------------------------------------------
// 0x593710 sub_593710 —— 挑衅标记撒播（彼诺修版：对 300 内同房间玩家挂 CNEnchantWeapon）
// 遍历场景对象表（this+29→+8 数组/+12 计数）：vt+40(17) 状态校验、双方 vt+376
// 同房间判定【推断】、vt+8 距离≤300；命中则 new(0x84) 后以 vt+672(this,3) 取值-5
// 调 sub_4DF1B0（CNEnchantWeapon 构造）生成挑衅标记特效对象，经对象 vt+56 绑定
// （宿主=玩家、来源=本怪）；与 sub_592000 仅构造第二参 0/1 之差
// ------------------------------------------------------------
int /*thiscall*/ sub_593710(uint32_t *this)  // 实现：挑衅标记撒播（彼诺修版：对 300 内同房间玩家挂 CNEnchantWeapon）
{
  unsigned int i; // edi
  int fld_e29; // ecx | =+0x0074 字段 x2（证据 005FD6C0）
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

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v4 = *(uint32_t *)(fld_e29 + 8);
    v15 = i;
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;  // 跳出循环/分支
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 若 v6 != 0
      pObj3 = *(uint32_t *)(v6 + 4 * i);
    else  // 否则分支
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 若 v9 != 0
        pObj2 = *(uint32_t *)(v9 + 4 * i);
      else  // 否则分支
        pObj2 = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);  // 调虚槽 +376：坐标同步包（type 37）
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)  // 调虚槽 +376：坐标同步包（type 37）
        && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj2, 0) <= 300 )  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
      {
        Block = operator new(0x84u);  // new(132 字节) 分配对象
        pObj = 0;
        if ( Block != nullptr )  // 若 Block 有效（非空）
        {
          v13 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
          pObj = sub_4DF1B0(*v13 - 5, 0, 0, -1);  // CNEnchantWeapon 构造
        }
        (*(void (/*thiscall*/ **)(int, int, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
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



// 狂气光环 AI：vt+212 播报 AURA_FURY + SOR_SPIN（130L；彼诺修狂气化演出）
// ------------------------------------------------------------
// 0x593840 sub_593840 —— 彼诺修狂气化动画事件处理器（大状态 this+6556 驱动，130L 演出）
// 入口按块参/大状态收尾：块参==16 或大状态 15 → sub_593230 恢复 buff 标志数组；
// 大状态 14（狂气攻击阶段）按相位 this+8612 分派：0=sub_593710 挑衅撒播、
// 1=sub_4DB200(24,3)+sub_592F50 前跳试探、2=sub_4DB200(24,rand%2)+sub_592FB0 瞬移绕背；
// 中段 sub_4E33D0 事件继续转发；尾段按大状态分派：0 且 this+7632/8660 门开 →
// sub_64BBF0(180,3000,25) 生成狂气光环粒子（0x8C 对象）+ vt+212 播 AURA_FURY +
// 置 this+8660=1；8 → vt+212 播 SOR_SPIN；14 → 落地预备（vt+876 播音效 ×2 /
// vt+196 面向 this+6216→+4 / sub_4926A0 帧游标复位 / vt+888 位移锁定）；
// 15 → sub_5930F0 跳跃着陆（高度/状态参取自 fArg3 解引）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_593840(int this, void *Block, float fArg3, int nArg4, int nArg5)  // 实现：彼诺修狂气化动画事件处理器（大状态 this+6556 驱动，130L 演出）
{
  void *Block2; // ebx
  int fld_199C; // edi | =+0x199C 字段 x1（证据 005EA970）
  int fld_21A4; // eax | =+0x21A4 字段 x1（证据 0059A3F0）
  int nRand; // eax
  unsigned int result; // eax
  int *v11; // eax
  int v12; // edx
  uint32_t v13[2]; // [esp+Ch] [ebp-14h]
  int v14; // [esp+1Ch] [ebp-4h]
  void *Blocka; // [esp+28h] [ebp+8h]

  Block2 = Block;
  fld_199C = *(uint32_t *)(this + 6556);  // this+6556〔大状态ID〕
  if ( Block == (void *)16 )
  {
    sub_593230((unsigned int *)this);  // buff 标志数组全置 1 + 目标高度取计时字段（sub_593840 狂气buff 释放时调用）
    Block2 = nullptr;  // Block2 = 空指针
  }
  if ( fld_199C == 15 )  // 若 fld_199C == 15
  {
    if ( Block2 != (void *)16 )
      sub_593230((unsigned int *)this);  // buff 标志数组全置 1 + 目标高度取计时字段（sub_593840 狂气buff 释放时调用）
  }
  else if ( fld_199C == 14 )
  {
    fld_21A4 = *(uint32_t *)(this + 8612);  // fld_21A4 = 读 this+8612
    switch ( fld_21A4 )  // 按 fld_21A4 分派
    {
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        v13[0] = 0;
        v13[1] = 1;
        nRand = rand() % 2;  // nRand = 调 rand
        sub_4DB200(24, v13[nRand]);  // 15% 概率随机文案触发（0x4DB130 的门包装）
        sub_592FB0((uint32_t *)this, (int)Block2, this);  // 瞬移绕背（彼诺修位移技：找 300 内玩家闪现其身后 500）
        break;  // 跳出循环/分支
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        sub_4DB200(24, 3);  // 15% 概率随机文案触发（0x4DB130 的门包装）
        sub_592F50((int *)this);  // 前跳试探落点（彼诺修版，喂 sub_592970 施放）
        break;  // 跳出循环/分支
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        sub_593710((uint32_t *)this);  // 挑衅标记撒播（彼诺修版：对 300 内同房间玩家挂 CNEnchantWeapon）
        break;  // 跳出循环/分支
      default:  // 默认分支
        break;  // 跳出循环/分支
    }
  }
  sub_4E33D0((char)Block2, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  result = *(uint32_t *)(this + 6556);  // this+6556〔大状态ID〕
  switch ( result )  // 按 result 分派
  {
    case 0u:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = *(uint32_t *)(this + 7632);  // result = 读 this+7632
      if ( result == 0 )  // 若 result 为 0
      {
        result = *(uint8_t *)(this + 8660);  // result = 读 this+8660
        if ( (uint8_t)result == 0 )
        {
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
          sub_53F6A0(this);  // 调 收尾路径
          Blocka = operator new(0x8Cu);  // new(140 字节) 分配对象
          v14 = 0;
          if ( Blocka != nullptr )  // 若 Blocka 有效（非空）
            v11 = (int *)sub_64BBF0(180, 3000, 25);  // 火焰动画查询 2（5910D0）
          else  // 否则分支
            v11 = nullptr;  // v11 = 空指针
          v12 = *v11;
          v14 = -1;
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, int))(v12 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
            v11,
            this,
            this,
            0,
            0,
            0,
            -1);
          sub_4DB200(24, 2);  // 15% 概率随机文案触发（0x4DB130 的门包装）
          result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                     this,
                     "AURA_FURY",  // 标签 AURA_FURY
                     -1,
                     0,
                     0);
          *(uint8_t *)(this + 8660) = 1;  // this+8660〔uEvt8660(推断)〕
        }
      }
      break;  // 跳出循环/分支
    case 8u:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                 this,
                 "SOR_SPIN",  // 标签 SOR_SPIN
                 -1,
                 0,
                 0);
      break;  // 跳出循环/分支
    case 0xEu:
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      sub_4926A0(*(uint32_t *)(this + 120));  // 帧游标复位（+44 帧数组；递归子链 +204）
      result = (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 1, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
      break;  // 跳出循环/分支
    case 0xFu:
      result = sub_5930F0((int *)this, **(uint32_t **)(LODWORD(fArg3) + 4), *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4));  // 跳跃着陆结算（落点高度 nArg2 / 状态参 nArg3）
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}


// 绕后瞬移触发（18 秒节拍）：clock_now 超 this+2160+18000 即重置拍点；动画态0且有目标时
//   sub_431230 打包 (200, rand%2) 参数表 → vt+560(this,15,…) 反应态15（瞬移绕后【推断】）
// ------------------------------------------------------------
// 0x593AC0 sub_593AC0 —— 绕后瞬移节拍器（18 秒周期触发反应态 15）
// clock_now（sub_699000，冻结感知时钟）超过 this+2160+18000 时重置拍点；
// 动画态（vt+840）为 0 且有目标 this+1813 时：vt+564 收尾，sub_431230 两次打包
// (200, rand%2) 参数表，vt+560(this,15,…) 写反应态 15（瞬移绕后【推断】）
// ------------------------------------------------------------
void /*thiscall*/ sub_593AC0(uint32_t *this)  // 实现：绕后瞬移节拍器（18 秒周期触发反应态 15）
{
  int pThis_9; // edi
  int v3; // eax
  int v4; // edx
  uint8_t v5[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v7; // [esp+10h] [ebp-18h]
  int v8; // [esp+14h] [ebp-14h]
  uint32_t v9[4]; // [esp+18h] [ebp-10h] BYREF

  pThis_9 = (int)(this + 9);  // this+36〔nStateWord36(推断)〕
  if ( sub_699000((int)(this + 9)) > (unsigned int)(*(this + 2160) + 18000) )  // 【clock_now(clk)】
  {
    v3 = sub_699000(pThis_9);  // 【clock_now(clk)】
    v4 = *this;
    *(this + 2160) = v3;  // this+8640〔uCastSlot8640(推断)〕
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 840))(this) == 0 && *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);  // 调虚槽 +564
      v9[0] = 200;
      Block = nullptr;  // Block = 空指针
      v7 = 0;
      v8 = 0;
      v9[3] = 0;
      sub_431230((int)v5, v9);  // uint32 vector push_back
      v9[0] = rand() % 2;  // v9[0] = 调 rand
      sub_431230((int)v5, v9);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 15, v5, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
    }
  }
}



// 主状态门（this+200）
// ------------------------------------------------------------
// 0x593BA0 sub_593BA0 —— 彼诺修大状态机驱动（this+6556 分派：待机转向/施法收尾/侧移节拍）
// 头调 sub_4E1780（受击反应处理）后按大状态 this+6556 分派：
//   0：this+6752 门关时按动画（vt+200）与 this+6164 的匹配及 vt+184/vt+152 朝向比较，
//      用 vt+196 修面向 + sub_4926A0 复位帧游标（行走转向维持【推断】）；
//   14：动画播完（+170）→ vt+564 收尾 + vt+560(this,0,…) 复位反应态；
//   15：sub_592A00 侧移施法主门 + sub_593AC0 绕后节拍器
// ------------------------------------------------------------
void /*thiscall*/ sub_593BA0(int this)  // 实现：彼诺修大状态机驱动（this+6556 分派：待机转向/施法收尾/侧移节拍）
{
  int fld_199C; // eax | =+0x199C 字段 x1（证据 005EA970）
  int v3; // eax
  int pThis_B8; // edi
  int fld_1848; // eax | =+0x1848 字段 x15（证据 005EA970）
  int pThis_B82; // edi

  sub_4E1780((uint32_t *)this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    fld_199C = *(uint32_t *)(this + 6556);  // this+6556〔大状态ID〕
    if ( fld_199C != 0 )  // 若 fld_199C 非 0
    {
      v3 = fld_199C - 14;
      if ( v3 != 0 )  // 若 v3 非 0
      {
        if ( v3 == 1 )  // 若 v3 == 1
        {
          sub_592A00((uint32_t *)this);  // 克拉赫侧移施法主门（this+200 主状态内的帧驱动走位）
          sub_593AC0((uint32_t *)this);  // 绕后瞬移节拍器（18 秒周期触发反应态 15）
          return;
        }
      }
      else if ( *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )  // this+120〔pAnimObj〕
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 564))(this);  // 调虚槽 +564
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        sub_593AC0((uint32_t *)this);  // 绕后瞬移节拍器（18 秒周期触发反应态 15）
        return;
      }
      goto LABEL_15;
    }
    if ( *(uint8_t *)(this + 6752) == 0 )  // this+6752〔nReviveTimer〕
    {
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *(uint32_t *)(this + 6164) )  // 调虚槽 +200：取动画对象
      {
        pThis_B8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 184))(this);  // 调虚槽 +184：动画对象 z 倾斜转状态码
        if ( pThis_B8 != (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) )  // 调虚槽 +152：效果通道 3
        {
          fld_1848 = **(uint32_t **)(this + 6216);  // this+6216〔pTbl6216(推断)〕
LABEL_14:  // 标签 LABEL_14（跳转合流点）
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 196))(this, fld_1848);  // 调虚槽 +196：动画对象设置（换域 + 播放）
          sub_4926A0(*(uint32_t *)(this + 120));  // 帧游标复位（+44 帧数组；递归子链 +204）
        }
      }
      else  // 否则分支
      {
        pThis_B82 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 184))(this);  // 调虚槽 +184：动画对象 z 倾斜转状态码
        if ( pThis_B82 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) )  // 调虚槽 +152：效果通道 3
        {
          fld_1848 = *(uint32_t *)(this + 6164);  // this+6164〔pFrameObj6164〕
          goto LABEL_14;
        }
      }
    }
LABEL_15:  // 标签 LABEL_15（跳转合流点）
    sub_593AC0((uint32_t *)this);  // 绕后瞬移节拍器（18 秒周期触发反应态 15）
  }
}



// 召唤物生成：Monster/Soceress/Effect/Summon.ani（彼诺修版召唤特效）
// ------------------------------------------------------------
// 0x593CA0 sub_593CA0 —— 彼诺修召唤特效生成（Monster/Soceress/Effect/Summon.ani）
// sub_42FCB0(228) 池检查通过后 sub_431860 装载 Summon.ani 动画，sub_44B6C0(284)
// 分配 CNRDPooledObject 并 sub_44E0D0 绑定动画；sub_45FE80 挂入场景（this+29，
// 层参 2），vt+112 按本体 vt+128/124/120 链对齐 Z 高度、vt+60 绑定宿主本怪、
// vt+148 按 vt+152 面向摆放；供 sub_593D90 的 VINO_COMMAND 召唤流程调用
// ------------------------------------------------------------
int /*thiscall*/ sub_593CA0(int *this)  // 实现：彼诺修召唤特效生成（Monster/Soceress/Effect/Summon.ani）
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
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    v2 = sub_431860((char)"Monster/Soceress/Effect/Summon.ani", 1);  // 动画件构造（资源 id 版）
  v3 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
  pObj = (int)v3;
  if ( v3 != nullptr )  // 若 v3 有效（非空）
  {
    sub_44E0D0(v3, v2, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else  // 否则分支
  {
    pObj = 0;
  }
  sub_45FE80(*(this + 29), pObj, 2, 0, pObj, (int)this, 0);  // 调 实体对象注册到演播层
  v5 = *(uint32_t *)pObj;
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v6);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(int, int))(v5 + 112))(pObj, v7);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  sub_4A06D0(v11);  // 调 绑定目标对象并记录相对偏移
  v8 = *(uint32_t *)pObj;
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
  return (*(int (/*thiscall*/ **)(int, int))(v8 + 148))(pObj, v9);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
}



// 彼诺修主攻 AI：vt+212 VINO_CAST + VINO_COMMAND（101L；this+8644 相位门）
// ------------------------------------------------------------
// 0x593D90 sub_593D90 —— 彼诺修主攻 AI（this+1787 状态内：施法/召唤/补刀三骰决策）
// 头调 sub_4E0120 后按 this+1787 分派。态 4/16：无目标切动画 13；vt+840 动画态为
// 14/15（施法/召唤进行中）时让路；clock_now（sub_699000）超 this+2159+10000
// （受击后 10 秒）强制回主态 16；随后三段概率：12% → vt+560(14) 进施法态 +
// vt+212 播 VINO_CAST + this+2153=2；召唤门（有目标、相位门 this+8644 空、
// 施放数 this+2162<5、rand%300<5 ≈1.7%、sub_591C90 同房间近距玩家<2、
// 血线 vt+736≥vt+740/10 全过）→ sub_593CA0 生成召唤特效 + vt+212 播 VINO_COMMAND
// + this+2153=1 + 关相位门；尾段 3% 概率补发一次 VINO_CAST（this+2153=0）；
// 态 5/13/14/15 做目标有无的动画切换（4↔13）
// ------------------------------------------------------------
int /*thiscall*/ sub_593D90(uint32_t *this)  // 实现：彼诺修主攻 AI（this+1787 状态内：施法/召唤/补刀三骰决策）
{
  int result; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edi
  int v6; // edx
  int nRand; // eax
  int v8; // et2
  int v9; // edx

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787) - 4;  // this+7148〔nBigState〕
  switch ( *(this + 1787) )  // this+7148〔nBigState〕
  {
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
    case 0x10:
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 无目标→切动画13
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
      if ( result == 14 )  // 若 result == 14
        return result;
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
      if ( result == 15 )  // 若 result == 15
        return result;
      if ( sub_699000((int)(this + 9)) > (unsigned int)(*(this + 2159) + 10000) )  // 【clock_now(clk)】受击后 10 秒强制切16
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 16);  // 调虚槽 +1104
      if ( rand() % 100 < 12 )  // 12% 概率发起施法
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);  // 调虚槽 +564
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        v3 = *this;
        *(this + 2153) = 2;  // this+8612〔uAI8612(推断)〕
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v3 + 212))(this, "VINO_CAST", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      }
      if ( *(this + 1813) == 0 || *((uint8_t *)this + 8644) != 0 || (int)*(this + 2162) >= 5 || rand() % 300 >= 5 )  // 召唤门：有目标/相位空闲/施放数<5/1.7%概率
        goto LABEL_17;
      v4 = sub_4D8FE0(this);  // v4 = 调 sub_4D8FE0 返回值
      result = sub_591C90(this, 2 * v4);  // 同房间近距玩家计数
      if ( result < 2 )  // 附近≥2人不召唤
      {
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) / 10;  // 最大HP/10 血线门
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
        if ( result >= v5 )  // 若 result >= v5
        {
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调虚槽 +120：动画对象
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);  // 调虚槽 +564
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
          sub_593CA0(this);  // 彼诺修召唤特效生成（Monster/Soceress/Effect/Summon.ani）
          v6 = *this;
          *(this + 2153) = 1;  // this+8612〔uAI8612(推断)〕
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v6 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            this,
            "VINO_COMMAND",  // 标签 VINO_COMMAND
            -1,
            0,
            0);
          *((uint8_t *)this + 8644) = 1;  // this+8644〔uPhase8644(推断)〕
LABEL_17:  // 标签 LABEL_17（跳转合流点）
          nRand = rand();  // nRand = 调 rand
          v8 = nRand % 100;
          result = nRand / 100;
          if ( v8 < 3 )  // 3% 概率补发一次施法
          {
            (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);  // 调虚槽 +564
            (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
            v9 = *this;
            *(this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
            return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v9 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                     this,
                     "VINO_CAST",  // 标签 VINO_CAST
                     -1,
                     0,
                     0);
          }
        }
      }
      return result;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result == 0 )  // 若 result 为 0
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      return result;
    case 0xD:
    case 0xE:
    case 0xF:
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      return result;
    default:  // 默认分支
      return result;
  }
}



// 彼诺修资源装载：R_VINO_ATK/DMG/DIE + SOR_APPEAR 语音；
//   Monster/Soceress/{Hair01,Cloth01,Weapon01,Acc01}.equ 四件外观（123L）
// ------------------------------------------------------------
// 0x593FF0 sub_593FF0 —— 彼诺修资源装载（语音四槽 + .equ 四件外观 + 攻击参数初始化）
// this+1698..1702 写 2/2/2/3/4 权重槽后 sub_4015C0 注册 R_VINO_ATK/DMG/DIE +
// SOR_APPEAR 语音（研究 28，vt+212 播报）；循环 new(0x544)+sub_4BA9E0
// （CNRDEquipment）装载 Monster/Soceress/{Hair01,Cloth01,Weapon01,Acc01}.equ
// 并经 vt+784 挂装（vt+4 置 1）；攻击参数：this+1830=100 / this+1839=-30 /
// this+1831=570，sub_4049C0 按 this+1820/1821 区间插值出 this+2150，vt+384(2) 存
// this+2152；this+2159=clock_now、this+2155=this+81、sub_4E1390 注册 0x30004
// 属性项【推断】、this+2154=30066 本体技能id
// ------------------------------------------------------------
int /*thiscall*/ sub_593FF0(int *this)  // 实现：彼诺修资源装载（语音四槽 + .equ 四件外观 + 攻击参数初始化）
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

  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0((size_t *)this + 1761, "R_VINO_ATK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 1691, "R_VINO_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 1709, "R_VINO_DIE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 1934, "SOR_APPEAR", 0xAu);  // 【std::string构造赋值】
  pMem = operator new(0x544u);  // new(1348 字节) 分配对象
  Block = pMem;
  v33 = 0;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0((char *)pMem, "Monster/Soceress/Hair01.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v3 = nullptr;  // v3 = 空指针
  v4 = *this;
  v33 = -1;
  pObj4 = (*(int (/*thiscall*/ **)(int *, char *))(v4 + 784))(this, v3);
  if ( pObj4 != 0 )  // 若 pObj4 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = operator new(0x544u);  // new(1348 字节) 分配对象
  Block = pMem2;
  v33 = 1;
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v7 = sub_4BA9E0((char *)pMem2, "Monster/Soceress/Cloth01.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v7 = nullptr;  // v7 = 空指针
  v8 = *this;
  v33 = -1;
  pObj2 = (*(int (/*thiscall*/ **)(int *, char *))(v8 + 784))(this, v7);
  if ( pObj2 != 0 )  // 若 pObj2 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem3 = operator new(0x544u);  // new(1348 字节) 分配对象
  Block = pMem3;
  v33 = 2;
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v11 = sub_4BA9E0((char *)pMem3, "Monster/Soceress/Weapon01.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v11 = nullptr;  // v11 = 空指针
  v12 = *this;
  v33 = -1;
  pObj3 = (*(int (/*thiscall*/ **)(int *, char *))(v12 + 784))(this, v11);
  if ( pObj3 != 0 )  // 若 pObj3 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem4 = operator new(0x544u);  // new(1348 字节) 分配对象
  Block = pMem4;
  v33 = 3;
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v15 = sub_4BA9E0((char *)pMem4, "Monster/Soceress/Acc01.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v15 = nullptr;  // v15 = 空指针
  v16 = *this;
  v33 = -1;
  pObj = (*(int (/*thiscall*/ **)(int *, char *))(v16 + 784))(this, v15);
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  v18 = *this;
  *(this + 1830) = 100;
  *(this + 1839) = -30;
  *(this + 1831) = 570;
  v19 = (void *)(*(int (/*thiscall*/ **)(int *, uint32_t))(v18 + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v20 = *this;
  Block = v19;
  v21 = (*(int (/*thiscall*/ **)(int *, int))(v20 + 384))(this, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  fld_e1821 = *(this + 1821);
  fld_e1820 = *(this + 1820);
  v32 = v21;
  v24 = fld_e1821 - fld_e1820;
  v25 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v29 = (float)v32;
  v28 = (float)(int)Block;
  fld_e18202 = (uint64_t)sub_4049C0(v28, v29, *v25 - *(this + 1820), v24);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e18202) = *this;
  *(this + 2150) = fld_e18202;  // this+8600〔uAI8600(推断)〕
  *(this + 2152) = (*(int (/*thiscall*/ **)(int *, int))(HIDWORD(fld_e18202) + 384))(this, 2);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  *(this + 2159) = sub_699000((int)(this + 9));  // clock_now(clk)
  *(this + 2155) = *(this + 81);  // this+8620〔uAI8620(推断)〕等 2 字段
  v30 = 100000;
  result = sub_4E1390(this, (uint32_t *)0x30004, &v30);  // 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
  *(this + 2154) = 30066;  // this+8616〔uAI8616(推断)〕
  return result;
}


// 路易斯外观装载：Monster/Soceress/Luis_{Hair01,Cloth01,Weapon01,Acc01,Weapon02}.equ 五件
// ------------------------------------------------------------
// 0x594290 sub_594290 —— 路易斯外观装载（Luis 五件套 .equ 循环挂装）
// 栈上路径表 Monster/Soceress/Luis_{Hair01,Cloth01,Weapon01,Acc01,Weapon02}.equ
// 逐件 new(0x544)+sub_4BA9E0（CNRDEquipment）构造后经 vt+784 挂装（vt+4 置 1）；
// 与 sub_593FF0 同构但无语音/参数段（双武器槽外观配置【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_594290(int *this)  // 实现：路易斯外观装载（Luis 五件套 .equ 循环挂装）
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
  for ( i = 0; i < 5; ++i )  // 循环：i 从 0 递增到 5
  {
    pMem = operator new(0x544u);  // new(1348 字节) 分配对象
    v7[5] = pMem;
    v8 = 0;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v4 = sub_4BA9E0((char *)pMem, v7[i], 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
    else  // 否则分支
      v4 = nullptr;  // v4 = 空指针
    v5 = *this;
    v8 = -1;
    result = (*(int (/*thiscall*/ **)(int *, char *))(v5 + 784))(this, v4);
    if ( result != 0 )  // 若结果非 0（成功）
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  }
  return result;
}



// 子类扩展字段复位（this+8600..8620）
// ------------------------------------------------------------
// 0x594340 sub_594340 —— 子类扩展字段复位（this+8600..8628 九个字段清零）
// 本家族子类 AI 块出厂复位：this+8600/8601/8602 三字节、this+8604/8608 两字、
// this+8620 起 12 字节（3 字）全清【推断：攻击序列与落点缓存区】
// ------------------------------------------------------------
int /*thiscall*/ sub_594340(int this)  // 实现：子类扩展字段复位（this+8600..8628 九个字段清零）
{
  uint32_t *pThis_21AC; // ecx

  *(uint8_t *)(this + 8600) = 0;  // this+8600〔uAI8600(推断)〕
  *(uint8_t *)(this + 8601) = 0;  // this+8601〔bAI8601(推断)〕
  *(uint8_t *)(this + 8602) = 0;  // this+8602〔bAI8602(推断)〕
  *(uint32_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint32_t *)(this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
  pThis_21AC = (uint32_t *)(this + 8620);  // this+8620〔uAI8620(推断)〕
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
// 0x594370 sub_594370 —— 魔法师基类 AI 小调度（this+1787：待机逻辑 + 4↔13 动画切换）
// 头调 sub_4E0120（基类周期处理）后按 this+1787 分派：态 0 → vt+1284 待机逻辑；
// 态 4 无目标 → vt+1104(13)；态 13/14/15 有目标 → vt+1104(4)（追击↔待机切换【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_594370(int *this)  // 实现：魔法师基类 AI 小调度（this+1787：待机逻辑 + 4↔13 动画切换）
{
  int result; // eax

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调虚槽 +1284
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result == 0 )  // 若 result 为 0
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// AI 字段访问（this+8602）
// ------------------------------------------------------------
// 0x5943F0 sub_5943F0 —— 施法段推进辅助（动画状态4门控：音效起播 + 帧时刻对齐 + 收态）
// vt+308 可行动且动画对象 this+28→+192==4、相位门 this+8602 空时：vt+876 播音效、
// vt+896(4,4) 设表现参数；同门下 sub_491C70 换算第 1 帧累计时刻、sub_493A60 推进
// this+30 动画时间轴并置 this+8602=1（一次性门）；
// 动画播完（this+30→+170）→ vt+560(this,0,…) 复位反应态
// ------------------------------------------------------------
char /*thiscall*/ sub_5943F0(uint32_t *this)  // 实现：施法段推进辅助（动画状态4门控：音效起播 + 帧时刻对齐 + 收态）
{
  int fld_e30; // edi | =+0x0078 字段 x6（证据 00499020）
  int v3; // eax
  char result; // al

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && *(uint32_t *)(*(this + 28) + 192) == 4  // this+112〔pHostComp112〕
    && *((uint8_t *)this + 8602) == 0 )  // this+8602〔bAI8602(推断)〕
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      this,
      0,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  }
  if ( *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8602) == 0 )  // 复合条件判定（与/或）
  {
    fld_e30 = *(this + 30);  // this+120〔pAnimObj〕
    v3 = sub_491C70(fld_e30, 1);  // 帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
    sub_493A60(fld_e30, v3);  // 时间推进包装（累计 +32；+212 同步源优先）
    *((uint8_t *)this + 8602) = 1;  // this+8602〔bAI8602(推断)〕
  }
  result = *(uint8_t *)(*(this + 30) + 170);  // this+120〔pAnimObj〕
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  return result;
}



// 子类扩展字段复位（105L）
// ------------------------------------------------------------
// 0x594490 sub_594490 —— 魔法师大状态周期处理器（8=三段相位演出 / 14、15=委托子辅助）
// 头调 sub_4E1780（受击反应）后按大状态 this+6556 分派：14 → sub_595E50、
// 15 → sub_5943F0 施法段推进；大状态 8 为相位机 this+7028（sub_41A5E0 读相位）：
//   相位 0 且帧≥3 且 this+8600 空 → vt+352 起手 + 置 this+8600=1；
//   相位 1/2/3 在 vt+308 可行动且帧≥1 时按相位给位移参数（1:sub_596030(1000)+
//   sub_4A0550(120)；2:sub_5985E0(400) 限下限 300 后 sub_4A05C0(×0.5)；3:1000/90）；
//   this+8601 门：this+112→+24 浮点>0 时 sub_4AECE0(1) 并置 8601=1；
//   收尾门 this+8602：this+112→+192==4 时按相位 sub_4AECE0(6 或 2) 并置 8602=1
//   （三段演出相位各只走一次，门字段 this+8600/8601/8602 串行推进【推断】）
// ------------------------------------------------------------
void /*thiscall*/ sub_594490(int this)  // 实现：魔法师大状态周期处理器（8=三段相位演出 / 14、15=委托子辅助）
{
  double v2; // st7
  int v3; // ebx
  int *fld_78; // ecx

  sub_4E1780((uint32_t *)this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( *(uint32_t *)(this + 6556) != 8 )  // this+6556〔大状态ID〕
  {
    if ( *(uint32_t *)(this + 6556) == 14 )  // this+6556〔大状态ID〕
    {
      sub_595E50(this);  // 撕咬连击推进（大状态 14 帧驱动，计数 2152/上限 2153）
    }
    else if ( *(uint32_t *)(this + 6556) == 15 )  // this+6556〔大状态ID〕
    {
      sub_5943F0((uint32_t *)this);  // 施法段推进辅助（动画状态4门控：音效起播 + 帧时刻对齐 + 收态）
    }
    return;
  }
  if ( sub_41A5E0(this + 7028) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 3 && *(uint8_t *)(this + 8600) == 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);  // 调虚槽 +352：命中列表双链表清空
    *(uint8_t *)(this + 8600) = 1;  // this+8600〔uAI8600(推断)〕
  }
  if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 || sub_41A5E0(this + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) == 0 )  // 调虚槽 +308：是否本地玩家
    {
LABEL_28:  // 标签 LABEL_28（跳转合流点）
      if ( *(uint8_t *)(this + 8601) != 0  // this+8601〔bAI8601(推断)〕
        && *(uint32_t *)(*(uint32_t *)(this + 112) + 192) == 4  // this+112〔pHostComp112〕
        && *(uint8_t *)(this + 8602) == 0 )  // this+8602〔bAI8602(推断)〕
      {
        v3 = 0;
        if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          v3 = 6;
        }
        else if ( sub_41A5E0(this + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          v3 = 2;
        }
        sub_4AECE0(*(void **)(this + 120), v3);  // this+120〔pAnimObj〕
        *(uint8_t *)(this + 8602) = 1;  // this+8602〔bAI8602(推断)〕
      }
      goto LABEL_37;
    }
    if ( *(int *)(*(uint32_t *)(this + 120) + 148) >= 1 )  // this+120〔pAnimObj〕
    {
      if ( *(uint8_t *)(this + 8601) != 0 )  // this+8601〔bAI8601(推断)〕
      {
LABEL_25:  // 标签 LABEL_25（跳转合流点）
        if ( *(uint32_t *)(*(uint32_t *)(this + 112) + 192) == 4 && *(uint8_t *)(this + 8602) == 0 )  // this+112〔pHostComp112〕
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
        }
        goto LABEL_28;
      }
      if ( sub_41A5E0(this + 7028) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        sub_596030(1000);  // 朝目标突进的速率设定
        sub_4A0550(120);  // 调 镜头幅度
      }
      else if ( sub_41A5E0(this + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        v2 = (double)sub_5985E0(400.0);  // 朝目标突进：施加速率并返回所需时长
        if ( v2 < 300.0 )
          v2 = 300.0;
        sub_4A05C0((uint64_t)(v2 * 0.5));
      }
      else if ( sub_41A5E0(this + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        sub_596030(1000);  // 朝目标突进的速率设定
        sub_4A0550(90);  // 调 镜头幅度
      }
    }
    if ( *(uint8_t *)(this + 8601) == 0 )  // this+8601〔bAI8601(推断)〕
    {
LABEL_37:  // 标签 LABEL_37（跳转合流点）
      if ( *(float *)(*(uint32_t *)(this + 112) + 24) > 0.0 && *(uint8_t *)(this + 8601) == 0 )  // this+112〔pHostComp112〕
      {
        fld_78 = *(int **)(this + 120);  // this+120〔pAnimObj〕
        if ( fld_78[37] < 1 )
          sub_4AECE0(fld_78, 1);  // 调 切武器动画
        *(uint8_t *)(this + 8601) = 1;  // this+8601〔bAI8601(推断)〕
      }
      return;
    }
    goto LABEL_25;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5946D0 sub_5946D0 —— 施法中目标位移同步（动画态14 时跟随目标 X 位移）
// 仅当 nArg2==this+2151（目标句柄匹配）且动画态（vt+840）==14、多段计数
// this+2153>1 时生效：this+2154 步进计满 5*sub_491C10(this+1554 帧表)/1000 阈值
// 则 this+2153 递减并清零；随后对目标对象 this+2151 先后取 vt+120（X）差值
// （vt+916 为刷新调用），把同一 X 位移量经自身 vt+128/124/120 链折算后用 vt+112
// 加到自身 X 上（目标被击退/位移时施法者同步跟随【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_5946D0(uint32_t *this, int nArg2)  // 实现：施法中目标位移同步（动画态14 时跟随目标 X 位移）
{
  int result; // eax
  int fld_e1554; // eax | =+0x1848 字段 x15（证据 005EA970）
  int fld_e2154; // edx | =+0x21A8 字段 x1（证据 005C0490）
  int fld_e2151; // edi | =+0x219C 字段 x1（证据 0059A020）
  int fld_e21512; // eax  | +0x219C → 子类槽〔594340 复位〕（CNLugaru；va=00594340）
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = nArg2;
  if ( nArg2 == *(this + 2151) )  // this+8604〔bAI8604(推断)〕
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result == 14 && (int)*(this + 2153) > 1 )  // 若 result == 14
    {
      fld_e1554 = sub_491C10(*(uint32_t *)*(this + 1554));  // 遍历帧数组（首+44/尾+48，步长 88）
      fld_e2154 = *(this + 2154) + 1;  // this+8616〔uAI8616(推断)〕
      *(this + 2154) = fld_e2154;  // this+8616〔uAI8616(推断)〕
      if ( fld_e2154 >= 5 * fld_e1554 / 1000 )
      {
        --*(this + 2153);  // this+8612〔uAI8612(推断)〕
        *(this + 2154) = 0;  // this+8616〔uAI8616(推断)〕
      }
      fld_e2151 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 120))(*(this + 2151));  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 916))(*(this + 2151));  // this+8604〔bAI8604(推断)〕
      fld_e21512 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 120))(*(this + 2151));  // 调虚槽 +120：动画对象
      v8 = *this;
      v9 = fld_e2151 - fld_e21512;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v10);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v11);  // 调虚槽 +120：动画对象
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(v8 + 112))(this, v12 - v9);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
  }
  return result;
}



// 蓄力技能：vt+212 广播 "HOLD"（104L；sub_4049C0 插值控制蓄力表现）
// ------------------------------------------------------------
// 0x5947A0 sub_5947A0 —— 蓄力起手（锁定目标瞬移贴身 + HOLD 蓄力广播 + 段数初始化）
// sub_45EBE0 从事件参取对象并校验（vt+40(17) 存活、vt+128≤0 地面【推断】）存
// this+2151；有目标时把目标 X/Y/Z 存 this+2155/2156/2157，按自身面向（vt+152）
// 以 X±30、目标 Z+40 经目标 vt+124→vt+112 落到目标身边，并对目标 vt+848(1) 设标记；
// 随后 vt+196 定面向、vt+876 播音效 ×2、vt+888(0,2,1000,1000)/vt+896(4,4) 锁定、
// vt+344(this+139)、this+28 位移标志清理、sub_495890(0,0) 速度归零；
// sub_4049C0 按 this+1820/1821 区间与 vt+384(0/1) 插值出蓄力段数存 this+2153
// （this+2152/2154 清零），sub_4DB200(24,rand%2) 15% 随机文案，vt+212 播 HOLD
// ------------------------------------------------------------
int /*thiscall*/ sub_5947A0(int *this, int pArg2)  // 实现：蓄力起手（锁定目标瞬移贴身 + HOLD 蓄力广播 + 段数初始化）
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2151; // ecx | =+0x219C 字段 x1（证据 0059A020）
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

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));  // pObj2 = 调 sub_45EBE0 返回值
  pObj = pObj2;
  if ( pObj2 == 0  // 若 pObj2 为 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || (*(this + 2151) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  {
    *(this + 2151) = 0;  // this+8604〔bAI8604(推断)〕
  }
  fld_e2151 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
  if ( fld_e2151 != 0 )  // 若 fld_e2151 非 0
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2151 + 120))(fld_e2151);  // 调虚槽 +120：动画对象
    fld_e21512 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    *(this + 2155) = v6;  // this+8620〔uAI8620(推断)〕
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21512 + 124))(fld_e21512);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    fld_e21513 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    *(this + 2156) = v8;  // this+8624〔uAI8624(推断)〕
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21513 + 128))(fld_e21513);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    v11 = *this;
    *(this + 2157) = v10;  // this+8628〔nPoolTime(推断)〕
    v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 152))(this);  // 调虚槽 +152：效果通道 3
    fld_e21514 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    if ( v12 != 0 )  // 若 v12 非 0
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) - 30;  // 调虚槽 +120：动画对象
    else  // 否则分支
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) + 30;  // 调虚槽 +120：动画对象
    v15 = *this;
    v30 = v14;
    fld_e21515 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    v17 = *(uint32_t *)fld_e21515;
    fld_e215152 = fld_e21515;
    v18 = (*(int (/*thiscall*/ **)(int))(v17 + 128))(fld_e21515);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
    v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21515 + 124))(fld_e21515, v18 + 40);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    (*(void (/*thiscall*/ **)(int *, int, int))(v15 + 112))(this, v30, v19 + 1);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2151) + 848))(*(this + 2151), 1);  // 调虚槽 +848：冻结标志写入（+6744，0→-1 / 非0→0）
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));  // 调虚槽 +344：取坐标三元组
  fld_e28 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0  // 调虚槽 +308：是否本地玩家
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  fld_e215152 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v21 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v31 = v21;
  v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v27 = (float)v31;
  v26 = (float)fld_e215152;
  *(this + 2153) = (uint64_t)sub_4049C0(v26, v27, *v23 - *(this + 1820), fld_e1821);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
  *(this + 2152) = 0;  // this+8608〔uAI8608(推断)〕
  *(this + 2154) = 0;  // this+8616〔uAI8616(推断)〕
  v28 = 0;
  fld_e215152 = 1;
  nRand = rand() % 2;  // nRand = 调 rand
  sub_4DB200(24, *(&v28 + nRand));  // 15% 概率随机文案触发（0x4DB130 的门包装）
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5949F0 sub_5949F0 —— buff 数组字段缩放（this+1905 组 +104 = +100 × 0.76923）
// nArg3==0 且 nArg2 为 1/2 时：把 this+1905 标志数组内偏移 +100 的浮点值
// 乘 0.76923078（≈10/13）写回 +104（攻速/间隔折算【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_5949F0(uint32_t *this, int nArg2, int nArg3)  // 实现：buff 数组字段缩放（this+1905 组 +104 = +100 × 0.76923）
{
  int result; // eax
  int fld_e1905; // eax | =+0x1DC4 字段 x1（证据 0059A020）
  double v5; // st7

  result = nArg3;
  if ( nArg3 == 0 )  // 若 nArg3 为 0
  {
    result = nArg2;
    if ( nArg2 == 2 || nArg2 == 1 )  // 若 nArg2 == 2 与/或 nArg2 == 1
    {
      fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
      v5 = *(float *)(fld_e1905 + 100);
      result = fld_e1905 + 96;
      *(float *)(result + 4) = v5 * 0.76923078;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x594A20 sub_594A20 —— 分身/召唤行为参数块复位与模式初始化（this+7531..7596）
// 先整块清零 this+7531..7596（约 20 个门/计数字段）；再按参数设模式：
// nArg3==2 → this+7534=1；nArg3==0 且 nArg2∈{1,2} → this+7596=-30、this+7568=1、
// this+7620 对象 +100 浮点 ×1.3（属性增强【推断】）；nArg2==0 → 仅 this+7568=1、
// this+7596=-30（无参默认模式【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_594A20(int this, int nArg2, int nArg3)  // 实现：分身/召唤行为参数块复位与模式初始化（this+7531..7596）
{
  int result; // eax

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    if ( nArg3 == 2 )  // 若 nArg3 == 2
      *(uint8_t *)(this + 7534) = 1;  // this+7534〔bCfgBlock14(推断)〕
  }
  else if ( nArg2 == 2 || nArg2 == 1 )
  {
    *(uint32_t *)(this + 7596) = -30;  // this+7596〔nOffset7596(推断)〕
    *(uint32_t *)(this + 7568) = 1;  // this+7568〔uEnable7568(推断)〕
    *(float *)(*(uint32_t *)(this + 7620) + 100) = *(float *)(*(uint32_t *)(this + 7620) + 100) * 1.3;  // this+7620〔pStatusPanel(推断)〕
  }
  else if ( nArg2 == 0 )
  {
    *(uint32_t *)(this + 7568) = 1;  // this+7568〔uEnable7568(推断)〕
    *(uint32_t *)(this + 7596) = -30;  // this+7596〔nOffset7596(推断)〕
  }
  return result;
}



// ============================================================
// 【分区 5】狐狸系·本体与黑足（Lugaru / Kurogaru）（0x594B10-0x5968D0）
// 证据：R_FOX_TALK/DMG + FOX_DIE 语音、FOX_ATK/FOX_BITE_LOOP 攻击、
//       Monster/Lugaru/Teeth.equ 牙齿外观、B_KUROGARU_01 登场曲

// 语音注册：R_FOX_TALK(0xA) / R_FOX_DMG(9) / FOX_DIE(7) 狐狸三件套（权重参数随 TAG 不同）
// ------------------------------------------------------------
// 0x594B10 sub_594B10 —— 狐狸语音注册（R_FOX_TALK / R_FOX_DMG / FOX_DIE 三件套）
// this+1698..1702 写 2/2/2/3/4 权重槽后 sub_4015C0 依次注册 R_FOX_TALK(10)、
// R_FOX_DMG(9)、FOX_DIE(7)（第三参为 TAG 字符串长度，研究 28 语音层，
// 由 vt+212 播报）
// ------------------------------------------------------------
int /*thiscall*/ sub_594B10(uint32_t *this)  // 实现：狐狸语音注册（R_FOX_TALK / R_FOX_DMG / FOX_DIE 三件套）
{
  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_FOX_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_FOX_DMG", 9u);  // 【std::string构造赋值】
  return sub_4015C0("FOX_DIE", 7u);  // 【std::string构造赋值】
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x594B80 sub_594B80 —— 受击前置钩子（特殊态反击打包 → 反应态14，尾调反击判定链）
// 条件全过（this+1639==8、相位机 this+1757==3（sub_41A5E0 读）、nArg4==0、
// vt+308 可行动、攻击者 vt+40(17) 与 vt+948 校验、this+154!=14）时：
// sub_431230 打包攻击者 vt+48/vt+52 参数，vt+560(this,14,…) 写反应态 14，
// sub_5E5260 释放参数包；无论是否触发都尾调 sub_4DB480（★反击/架招触发判定，
// 尾链 sub_4D6D90）
// ------------------------------------------------------------
int /*thiscall*/ sub_594B80(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：受击前置钩子（特殊态反击打包 → 反应态14，尾调反击判定链）
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8  // this+6556〔大状态ID〕
    && sub_41A5E0((unsigned int)(this + 1757)) == 3  // crypt4byte 解密校验（·0x41A590 逆运算）
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 948))(pObj) != 0  // 调虚槽 +948
    && *(this + 154) != 14 )  // this+616〔nReactionState〕
  {
    memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
    v6 = *(uint32_t *)pObj;
    v9 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(v6 + 48))(pObj);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    v9 = -1;
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
  return sub_4DB480(pObj, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 参数打包 AI（89L sub_431230）
// ------------------------------------------------------------
// 0x594C80 sub_594C80 —— 蓄力释放收尾（把锁定目标拽回蓄力起点并写其受击反应态4）
// 对锁定的目标对象 this+2151（sub_5947A0 蓄力起手记录）：vt+604(1,nArg2)/vt+612(0,0)
// 预处理；位置校验 vt+136 用蓄力时记录的 this+2155/2156/2157 通过 → 目标 vt+112
// 直接落回该点；失败则经目标 vt+124(300,1,1)/vt+120 与 vt+140 路径校验后回退到
// 自身坐标链折算点；随后目标 vt+308 可行动时 sub_431230 打包 (4,0,1,200,200)
// 参数表、目标 vt+560(,4,…) 写受击反应态 4（被叼住/被擒【推断】）+ vt+564 收尾；
// 末尾目标 vt+848(0) 清标记、this+2151 归零
// ------------------------------------------------------------
void /*usercall*/ sub_594C80(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 实现：蓄力释放收尾（把锁定目标拽回蓄力起点并写其受击反应态4）
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

  pObj3 = pDwArg1[2151];  // pObj3 = 取 pDwArg1[2151]
  if ( pObj3 != 0 )  // 若 pObj3 非 0
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 612))(pDwArg1[2151], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 136))(  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
           pDwArg1[2151],
           pDwArg1[2155],
           pDwArg1[2156],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2151] + 112))(pDwArg1[2151], pDwArg1[2155], pDwArg1[2156], pDwArg1[2157]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
    else  // 否则分支
    {
      pObj = pDwArg1[2151];  // pObj = 取 pDwArg1[2151]
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);  // 调虚槽 +120：动画对象
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2155, pDwArg1 + 2156, v7);  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
      pObj2 = pDwArg1[2151];  // pObj2 = 取 pDwArg1[2151]
      if ( v8 != 0 )  // 若 v8 非 0
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2155], pDwArg1[2156], pDwArg1[2157]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
      else  // 否则分支
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2157]);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2151], v12);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 308))(pDwArg1[2151]) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      Block = nullptr;  // Block = 空指针
      v15 = 0;
      v16 = 0;
      v18 = 0;
      pObj4 = 4;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 0;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 1;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 560))(pDwArg1[2151], 4, v13, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 564))(pDwArg1[2151]);
      v18 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
      Block = nullptr;  // Block = 空指针
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 848))(pDwArg1[2151], 0);  // 调虚槽 +848：冻结标志写入（+6744，0→-1 / 非0→0）
    pDwArg1[2151] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x594E80 sub_594E80 —— 蓄力目标死亡/自身死亡回调（清蓄力链 + vt+216(33) 播报）
// 死亡对象==蓄力锁定目标 this+2151 时：动画态（vt+840）==14 则先 sub_594C80 收尾，
// 随后清 this+2151；死亡对象==自身时同样收尾蓄力链并 vt+216(this,33) 播报；
// 尾调 sub_4D9170(pDwArg3) 继续死亡分发【推断：基类链】
// ------------------------------------------------------------
int /*userpurge*/ sub_594E80@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)  // 实现：蓄力目标死亡/自身死亡回调（清蓄力链 + vt+216(33) 播报）
{
  if ( pDwArg3 == (int *)pDwArg1[2151] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
      sub_594C80(pDwArg1, nArg2);  // 蓄力释放收尾（把锁定目标拽回蓄力起点并写其受击反应态4）
    pDwArg1[2151] = 0;
  }
  if ( pDwArg3 == pDwArg1 )  // 若 pDwArg3 == pDwArg1
  {
    if ( pDwArg1[2151] != 0 )
    {
      sub_594C80(pDwArg1, nArg2);  // 蓄力释放收尾（把锁定目标拽回蓄力起点并写其受击反应态4）
      pDwArg1[2151] = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);  // 调虚槽 +216：音效 TAG 查询
  }
  return sub_4D9170(pDwArg3);  // 返回 调 sub_4D9170 返回值
}



// 攻击 AI：vt+212 播报 FOX_ATK（狐狸扑击）
// ------------------------------------------------------------
// 0x594EF0 sub_594EF0 —— 狐狸扑击动画事件分发（8=起手 / 14=蓄力 / 15=释放收尾）
// this+1639==15（释放中）且事件非 15 → vt+216(this,33) 打断播报；==14（蓄力中）
// → 先 sub_594C80 收尾；随后按事件分派：8 → 清相位门 this+8600/8601/8602 +
// vt+212 播 FOX_ATK；14 → sub_5947A0 蓄力起手（锁定目标贴身）；15 → sub_597890
// 释放段；尾部统一 sub_4E33D0 基类事件转发
// ------------------------------------------------------------
int /*userpurge*/ sub_594EF0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, int nArg4, int nArg5, int nArg6)  // 实现：狐狸扑击动画事件分发（8=起手 / 14=蓄力 / 15=释放收尾）
{
  int v7; // eax
  int v8; // edx

  v7 = pDwArg1[1639];  // v7 = 取 pDwArg1[1639]
  if ( v7 == 15 )  // 若 v7 == 15
  {
    if ( ArgList != 15 )  // 若 ArgList != 15
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);  // 调虚槽 +216：音效 TAG 查询
  }
  else if ( v7 == 14 )
  {
    sub_594C80(pDwArg1, nArg2);  // 蓄力释放收尾（把锁定目标拽回蓄力起点并写其受击反应态4）
  }
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      v8 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8600) = 0;
      *((uint8_t *)pDwArg1 + 8601) = 0;
      *((uint8_t *)pDwArg1 + 8602) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(pDwArg1, "FOX_ATK", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      break;  // 跳出循环/分支
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      sub_5947A0(pDwArg1, nArg4);  // 蓄力起手（锁定目标瞬移贴身 + HOLD 蓄力广播 + 段数初始化）
      break;  // 跳出循环/分支
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      sub_597890(pDwArg1);  // 大状态 15 入场处理（·0x595C40 同构）
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  return sub_4E33D0(ArgList, *(float *)&nArg4, nArg5, nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}



// 子类扩展字段复位（this+8600..8624）
// ------------------------------------------------------------
// 0x594F90 sub_594F90 —— 狐狸系子类AI字段复位（this+8600..8632 九个字段清零）
// this+8600/8601/8602 三相位门、this+8604/8608/8612 字段、this+8624 起 12 字节
// 全清；供登场/重生时重建狐狸扑击蓄力链的初始态【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_594F90(int this)  // 实现：狐狸系子类AI字段复位（this+8600..8632 九个字段清零）
{
  uint32_t *pThis_21B0; // ecx

  *(uint8_t *)(this + 8600) = 0;  // this+8600〔uAI8600(推断)〕
  *(uint8_t *)(this + 8601) = 0;  // this+8601〔bAI8601(推断)〕
  *(uint8_t *)(this + 8602) = 0;  // this+8602〔bAI8602(推断)〕
  *(uint32_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint32_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint8_t *)(this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
  pThis_21B0 = (uint32_t *)(this + 8624);  // this+8624〔uAI8624(推断)〕
  *pThis_21B0 = 0;
  pThis_21B0[1] = 0;
  pThis_21B0[2] = 0;
  return 0;
}



// AI 字段访问（this+8608）
// ------------------------------------------------------------
// 0x594FD0 sub_594FD0 —— 强化态标志读取（this+8608，空则回退基类 sub_4E1BE0）
// 单字段读取：this+8608 非零返回之；为零时调 sub_4E1BE0 取基类同义字段
// （黑足/强化态查询【推断】）
// ------------------------------------------------------------
char /*thiscall*/ sub_594FD0(uint8_t *this)  // 实现：强化态标志读取（this+8608，空则回退基类 sub_4E1BE0）
{
  char result; // al

  result = *(this + 8608);
  if ( result == 0 )  // 若 result 为 0
    return sub_4E1BE0();  // 仇恨目标重选（取仇恨值最大且 vt+724==0 的敌人）
  return result;
}



// AI 字段访问（this+8608）
// ------------------------------------------------------------
// 0x594FE0 sub_594FE0 —— 强化态解除（this+8608 门控：属性减益回退 + 外观恢复）
// this+8608 非零时：vt+672(0) 取属性对象，+830 浮点-0.3、+858 浮点-0.2、+928-200、
// +144/+60/+88 各-25（sub_41A590 写回，移除黑足化加成【推断】）；vt+676(0) 收尾、
// 清 this+8608，vt+788(7) 取第 7 槽对象并 vt+4(1) 恢复外观【推断】；
// sub_4DB200(24,4) 15% 概率随机文案
// ------------------------------------------------------------
char /*thiscall*/ sub_594FE0(uint8_t *this)  // 实现：强化态解除（this+8608 门控：属性减益回退 + 外观恢复）
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
  if ( result != 0 )  // 若结果非 0（成功）
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 672))(this, 0);  // 调虚槽 +672：自身 HP
    *(float *)&v15 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 830)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0 + 830, v4, v15);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    *(float *)&v16 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 858)) - 0.2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0 + 858, v16, v16);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v5 = sub_41A5E0(pThis_2A0 + 928);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0 + 928, v6, v5 - 200);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v7 = sub_41A5E0(pThis_2A0 + 144);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0 + 144, v8, v7 - 25);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v9 = sub_41A5E0(pThis_2A0 + 60);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0 + 60, v10, v9 - 25);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_2A0 += 88;
    v11 = sub_41A5E0(pThis_2A0);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, v12, v11 - 25);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
    v13 = *(uint32_t *)this;
    *(this + 8608) = 0;
    pObj = (*(int (/*thiscall*/ **)(uint8_t *, int))(v13 + 788))(this, 7);
    if ( pObj != 0 )  // 若 pObj 非 0
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
    return sub_4DB200(24, 4);  // 15% 概率随机文案触发（0x4DB130 的门包装）
  }
  return result;
}



// 子类扩展字段复位（105L）
// ------------------------------------------------------------
// 0x5950F0 sub_5950F0 —— 狐狸大状态周期处理器（8=三段相位演出 / 14、15=委托子辅助）
// 与 sub_594490 同构（魔法师/狐狸共用的相位演出骨架）：头调 sub_4E1780 后按
// 大状态 this+6556 分派：14 → sub_597120、15 → sub_5943F0 施法段推进；
// 大状态 8 相位机 this+7028（sub_41A5E0 读）：相位 0 且帧≥3 且 this+8600 空 →
// vt+352 起手置 8600=1；相位 1/2/3 按 vt+308/帧≥1 给位移参数（1:sub_596030(1000)
// +sub_4A0550(120)；2:sub_5985E0(400) 限下限 300 后 sub_4A05C0(×0.5)；3:1000/90）；
// this+8601 门 sub_4AECE0(1)、收尾门 this+8602 按相位 sub_4AECE0(6/2) 串行推进
// （门字段 this+8600/8601/8602 各只走一次【推断】）
// ------------------------------------------------------------
void /*thiscall*/ sub_5950F0(int this)  // 实现：狐狸大状态周期处理器（8=三段相位演出 / 14、15=委托子辅助）
{
  double v2; // st7
  int v3; // ebx
  int *fld_78; // ecx

  sub_4E1780((uint32_t *)this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( *(uint32_t *)(this + 6556) != 8 )  // this+6556〔大状态ID〕
  {
    if ( *(uint32_t *)(this + 6556) == 14 )  // this+6556〔大状态ID〕
    {
      sub_597120(this);  // 撕咬连击推进（·0x595E50 同构，计数 2153/上限 2154）
    }
    else if ( *(uint32_t *)(this + 6556) == 15 )  // this+6556〔大状态ID〕
    {
      sub_5943F0((uint32_t *)this);  // 施法段推进辅助（动画状态4门控：音效起播 + 帧时刻对齐 + 收态）
    }
    return;
  }
  if ( sub_41A5E0(this + 7028) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 3 && *(uint8_t *)(this + 8600) == 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);  // 调虚槽 +352：命中列表双链表清空
    *(uint8_t *)(this + 8600) = 1;  // this+8600〔uAI8600(推断)〕
  }
  if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 || sub_41A5E0(this + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) == 0 )  // 调虚槽 +308：是否本地玩家
    {
LABEL_28:  // 标签 LABEL_28（跳转合流点）
      if ( *(uint8_t *)(this + 8601) != 0  // this+8601〔bAI8601(推断)〕
        && *(uint32_t *)(*(uint32_t *)(this + 112) + 192) == 4  // this+112〔pHostComp112〕
        && *(uint8_t *)(this + 8602) == 0 )  // this+8602〔bAI8602(推断)〕
      {
        v3 = 0;
        if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          v3 = 6;
        }
        else if ( sub_41A5E0(this + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          v3 = 2;
        }
        sub_4AECE0(*(void **)(this + 120), v3);  // this+120〔pAnimObj〕
        *(uint8_t *)(this + 8602) = 1;  // this+8602〔bAI8602(推断)〕
      }
      goto LABEL_37;
    }
    if ( *(int *)(*(uint32_t *)(this + 120) + 148) >= 1 )  // this+120〔pAnimObj〕
    {
      if ( *(uint8_t *)(this + 8601) != 0 )  // this+8601〔bAI8601(推断)〕
      {
LABEL_25:  // 标签 LABEL_25（跳转合流点）
        if ( *(uint32_t *)(*(uint32_t *)(this + 112) + 192) == 4 && *(uint8_t *)(this + 8602) == 0 )  // this+112〔pHostComp112〕
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
        }
        goto LABEL_28;
      }
      if ( sub_41A5E0(this + 7028) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        sub_596030(1000);  // 朝目标突进的速率设定
        sub_4A0550(120);  // 调 镜头幅度
      }
      else if ( sub_41A5E0(this + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        v2 = (double)sub_5985E0(400.0);  // 朝目标突进：施加速率并返回所需时长
        if ( v2 < 300.0 )
          v2 = 300.0;
        sub_4A05C0((uint64_t)(v2 * 0.5));
      }
      else if ( sub_41A5E0(this + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        sub_596030(1000);  // 朝目标突进的速率设定
        sub_4A0550(90);  // 调 镜头幅度
      }
    }
    if ( *(uint8_t *)(this + 8601) == 0 )  // this+8601〔bAI8601(推断)〕
    {
LABEL_37:  // 标签 LABEL_37（跳转合流点）
      if ( *(float *)(*(uint32_t *)(this + 112) + 24) > 0.0 && *(uint8_t *)(this + 8601) == 0 )  // this+112〔pHostComp112〕
      {
        fld_78 = *(int **)(this + 120);  // this+120〔pAnimObj〕
        if ( fld_78[37] < 1 )
          sub_4AECE0(fld_78, 1);  // 调 切武器动画
        *(uint8_t *)(this + 8601) = 1;  // this+8601〔bAI8601(推断)〕
      }
      return;
    }
    goto LABEL_25;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x595330 sub_595330 —— buff 数组字段缩放（this+1905 组 +100 与 +64 各 ×0.76923）
// nArg3==0 或（nArg3==2 且 nArg2==0）时：this+1905 标志数组内偏移 +100、+64 的
// 浮点值原位乘 0.76923078（≈10/13，攻速/间隔折算【推断】；与 sub_5949F0 同族）
// ------------------------------------------------------------
int /*thiscall*/ sub_595330(uint32_t *this, int nArg2, int nArg3)  // 实现：buff 数组字段缩放（this+1905 组 +100 与 +64 各 ×0.76923）
{
  int result; // eax
  int fld_e1905; // eax | =+0x1DC4 字段 x1（证据 0059A020）
  double v5; // st7

  if ( nArg3 == 0 || (result = nArg3 - 2, nArg3 == 2) && (result = nArg2, nArg2 == 0) )  // 若 nArg3 == 0 与/或 result = nArg3 与/或 result = nArg2
  {
    *(float *)(*(this + 1905) + 100) = *(float *)(*(this + 1905) + 100) * 0.76923078;  // this+7620〔pStatusPanel(推断)〕
    fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    v5 = *(float *)(fld_e1905 + 68);
    result = fld_e1905 + 64;
    *(float *)(result + 4) = v5 * 0.76923078;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x595380 sub_595380 —— 分身/召唤行为参数块复位与强化初始化（this+7531..7596）
// 与 sub_594A20 同族：先整块清零 this+7531..7596，再按参数设模式：
// nArg3==2 且 nArg2∈{1,2} → 仅 this+7537=1；nArg3==0，或 nArg3==2 且 nArg2==0 →
// this+7596=50、this+7568=2、this+7620 对象 +100 与 +68 浮点各 ×1.3
// （后者另置 this+7537=1；强化出生参数【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_595380(int this, int nArg2, int nArg3)  // 实现：分身/召唤行为参数块复位与强化初始化（this+7531..7596）
{
  int result; // eax
  int fld_1DC4; // eax | =+0x1DC4 字段 x1（证据 0059A020）
  double v5; // st7

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  if ( nArg3 == 0 )  // 若 nArg3 为 0
    goto LABEL_7;
  if ( nArg3 == 2 )  // 若 nArg3 == 2
  {
    if ( nArg2 == 2 || nArg2 == 1 )  // 若 nArg2 == 2 与/或 nArg2 == 1
    {
      *(uint8_t *)(this + 7537) = 1;  // this+7537〔bCfgBlock17(推断)〕
      return result;
    }
    if ( nArg2 == 0 )  // 若 nArg2 为 0
    {
      *(uint8_t *)(this + 7537) = 1;  // this+7537〔bCfgBlock17(推断)〕
LABEL_7:  // 标签 LABEL_7（跳转合流点）
      fld_1DC4 = *(uint32_t *)(this + 7620);  // fld_1DC4 = 读 this+7620
      *(uint32_t *)(this + 7596) = 50;  // this+7596〔nOffset7596(推断)〕
      *(uint32_t *)(this + 7568) = 2;  // this+7568〔uEnable7568(推断)〕
      v5 = *(float *)(fld_1DC4 + 100) * 1.3;
      result = fld_1DC4 + 96;
      *(float *)(result + 4) = v5;
      *(float *)(*(uint32_t *)(this + 7620) + 68) = *(float *)(*(uint32_t *)(this + 7620) + 68) * 1.3;  // this+7620〔pStatusPanel(推断)〕
    }
  }
  return result;
}



// 语音注册：R_FOX_TALK/DMG + FOX_DIE（第二只狐狸实例, sub_4049C0 插值）
// ------------------------------------------------------------
// 0x595470 sub_595470 —— 第二只狐狸实例参数初始化（语音注册+登场插值）
// 写 this+6792..6808 五个参数槽（2/2/2/3/4）并经 sub_4015C0 注册语音 TAG
// R_FOX_TALK/R_FOX_DMG/FOX_DIE；再用 sub_4049C0 以 this+7280..7284（登场时刻窗）
// 对 vt+384(2)/(3) 与 vt+384(4)/(5) 两对参数按 vt+672(3) 时钟插值，
// 结果写 this+424/this+436【推断：登场演出用的渐变参数（速率/缩放类）】
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_595470(float *this)  // 实现：第二只狐狸实例参数初始化（语音注册+登场插值）
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

  *((uint32_t *)this + 1698) = 2;  // this[1698] = 2
  *((uint32_t *)this + 1699) = 2;  // this[1699] = 2
  *((uint32_t *)this + 1700) = 2;  // this[1700] = 2
  *((uint32_t *)this + 1701) = 3;  // this[1701] = 3
  *((uint32_t *)this + 1702) = 4;  // this[1702] = 4
  sub_4015C0("R_FOX_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_FOX_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("FOX_DIE", 7u);  // 【std::string构造赋值】
  pThis_180 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  pThis_2A0 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v10 = (float)pThis_1802;
  v8 = (float)pThis_180;
  pThis_71C = sub_4049C0(v8, v10, *pThis_2A0 - *((uint32_t *)this + 1820), *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820));  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v4 = *(uint32_t *)this;
  *(this + 106) = pThis_71C;  // this+424〔f_AtkRateX10〕
  v15 = (*(int (/*thiscall*/ **)(float *, int))(v4 + 384))(this, 4);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  pThis_1803 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 5);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  pThis_71D = *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820);
  pThis_2A02 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v11 = (float)pThis_1803;
  v9 = (float)v15;
  result = (uint64_t)sub_4049C0(v9, v11, *pThis_2A02 - *((uint32_t *)this + 1820), pThis_71D);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *((uint32_t *)this + 109) = result;  // this+436〔nAtkTableVal(推断)〕
  return result;
}



// 登场曲：sub_406D60 写 "B_KUROGARU_01"（黑足 Kurogaru 曲目槽）
// ------------------------------------------------------------
// 0x5955B0 sub_5955B0 —— 黑足相位机：登场曲+相位切换
// sub_4E0120 公共前置后按 AI 相位 this+1787 分支：0=出场（vt+1284 出场处理；困难级
// this+1943==3 经 sub_406D60 播 BGM B_KUROGARU_01）；4=行动相位（宿主槽 this+7252
// 为空时 vt+1104 切相位 13）；13/14/15=待机相位（宿主出现则切回 4）
// 【推断：vt+1104 为 AI 相位设定调用】
// ------------------------------------------------------------
int /*thiscall*/ sub_5955B0(int *this)  // 实现：黑足相位机：登场曲+相位切换
{
  int result; // eax

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调虚槽 +1284
      if ( *(this + 1943) == 3 )  // this+7772〔nCounterState〕
        result = sub_406D60("B_KUROGARU_01");  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result == 0 )  // 若 result 为 0
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x595650 sub_595650 —— 受击钩子：架招反应触发
// 七重门（大状态 this+6556==8、攻击段 this+7028==3、nArg4 低字节 0、自身存活 vt+308、
// 攻击者类型 vt+40(17)、vt+948、反应态 this+616 非 14）通过时，打包攻击者坐标
// 经 sub_431230 走 vt+560 受击反应 setState 14（架招【推断】），尾调 sub_4DB480 反击判定
// ------------------------------------------------------------
int /*thiscall*/ sub_595650(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：受击钩子：架招反应触发
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8  // this+6556〔大状态ID〕
    && sub_41A5E0((unsigned int)(this + 1757)) == 3  // crypt4byte 解密校验（·0x41A590 逆运算）
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 948))(pObj) != 0  // 调虚槽 +948
    && *(this + 154) != 14 )  // this+616〔nReactionState〕
  {
    memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
    v6 = *(uint32_t *)pObj;
    v9 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(v6 + 48))(pObj);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    v9 = -1;
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
  return sub_4DB480(pObj, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x595750 sub_595750 —— 困难级 50% 概率反应
// this+1943==3 且 rand%100<50 时以 sub_4E7F30 选取对象，比较双方 vt+120 数值置
// vt+144 布尔标志，再 vt+560 setState 8【推断：逃走/加速类反应】
// ------------------------------------------------------------
void /*thiscall*/ sub_595750(uint32_t *this)  // 实现：困难级 50% 概率反应
{
  int pObj; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v7[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && *(this + 1943) == 3  // this+7772〔nCounterState〕
    && rand() % 100 < 50 )  // 50% 概率触发（rand()%100 < 50）
  {
    pObj = sub_4E7F30(this, 100, 80, 0);  // 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
    if ( pObj != 0 )  // 若 pObj 非 0
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调虚槽 +120：动画对象
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t *, bool))(v3 + 144))(this, v5 < v4);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
      memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
      v7[3] = 0;
      v7[0] = 2;
      sub_431230((int)pBuf, v7);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
    }
  }
}



// 参数打包 AI（89L sub_431230）
// ------------------------------------------------------------
// 0x595820 sub_595820 —— 拆除/回收附属对象（this+8604 槽）
// 对附属物：vt+604/vt+612 停止并隐藏；坐标对齐三态回退——vt+136 直传 this+8624..8632
// 失败则 vt+140 碰撞修正（300,1,1）再试，仍败用自身坐标；对象存活（vt+308）时打包
// {4,0,1,200,200} 走 vt+560 setState 4 + vt+564【推断：200/200 为尺寸/位移参数】；
// 末尾 vt+848(0) 解绑并清 this+8604
// ------------------------------------------------------------
void /*usercall*/ sub_595820(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 实现：拆除/回收附属对象（this+8604 槽）
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

  pObj3 = pDwArg1[2151];  // pObj3 = 取 pDwArg1[2151]
  if ( pObj3 != 0 )  // 若 pObj3 非 0
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 612))(pDwArg1[2151], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 136))(  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
           pDwArg1[2151],
           pDwArg1[2156],
           pDwArg1[2157],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2151] + 112))(pDwArg1[2151], pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
    else  // 否则分支
    {
      pObj = pDwArg1[2151];  // pObj = 取 pDwArg1[2151]
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);  // 调虚槽 +120：动画对象
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2156, pDwArg1 + 2157, v7);  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
      pObj2 = pDwArg1[2151];  // pObj2 = 取 pDwArg1[2151]
      if ( v8 != 0 )  // 若 v8 非 0
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
      else  // 否则分支
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2158]);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2151], v12);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 308))(pDwArg1[2151]) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      Block = nullptr;  // Block = 空指针
      v15 = 0;
      v16 = 0;
      v18 = 0;
      pObj4 = 4;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 0;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 1;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 560))(pDwArg1[2151], 4, v13, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 564))(pDwArg1[2151]);
      v18 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
      Block = nullptr;  // Block = 空指针
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 848))(pDwArg1[2151], 0);  // 调虚槽 +848：冻结标志写入（+6744，0→-1 / 非0→0）
    pDwArg1[2151] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x595A20 sub_595A20 —— 死亡/移除通知分发
// 消亡对象为宿主槽 this+7252 且强化门 this+8608 开 → sub_594FE0 强化态解除；
// 为附属物 this+8604（自身态 14 时）或自身 → 先经 ·0x595820 拆附属再 vt+216 播报 33；
// 尾调 sub_4D9170
// ------------------------------------------------------------
int /*userpurge*/ sub_595A20@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3)  // 实现：死亡/移除通知分发
{
  if ( *(uint8_t *)(pArg1 + 8608) != 0 && nArg3 == *(uint32_t *)(pArg1 + 7252) )  // 复合条件判定（与/或）
    sub_594FE0((uint8_t *)pArg1);  // 强化态解除（this+8608 门控：属性减益回退 + 外观恢复）
  if ( nArg3 == *(uint32_t *)(pArg1 + 8604) )  // pArg1+8604〔bAI8604(推断)〕
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
      sub_595820((int *)pArg1, nArg2);  // 拆除/回收附属对象（this+8604 槽）
    *(uint32_t *)(pArg1 + 8604) = 0;  // pArg1+8604〔bAI8604(推断)〕
  }
  if ( nArg3 == pArg1 )  // 若 nArg3 == pArg1
  {
    if ( *(uint32_t *)(pArg1 + 8604) != 0 )  // pArg1+8604〔bAI8604(推断)〕
    {
      sub_595820((int *)pArg1, nArg2);  // 拆除/回收附属对象（this+8604 槽）
      *(uint32_t *)(pArg1 + 8604) = 0;  // pArg1+8604〔bAI8604(推断)〕
    }
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 33);  // 调虚槽 +216：音效 TAG 查询
  }
  return sub_4D9170(nArg3);  // 返回 调 sub_4D9170 返回值
}



// 外观装载：Monster/Lugaru/Teeth.equ（獠牙/牙齿部件, sub_4BA9E0）
// ------------------------------------------------------------
// 0x595AB0 sub_595AB0 —— 獠牙强化变身（this+8608 一次性门）
// vt+672 取状态块后以 sub_41A5E0/sub_41A590 施加：+830 浮点+0.3、+858+0.2、+928+200、
// +144/+60/+88 各+25【推断：攻速/移速/攻击/命中类属性】；vt+676 收尾、置 this+8608=1；
// new 0x544 经 sub_4BA9E0 装载 Monster/Lugaru/Teeth.equ 后 vt+784 挂载并激活；
// 尾调 sub_4DB200 走 15% 概率随机喊话（文案 24，参数 2/3 随机）
// ------------------------------------------------------------
char /*usercall*/ sub_595AB0@<al>(uint8_t *pArg1@<ecx>, int nArg2@<esi>)  // 实现：獠牙强化变身（this+8608 一次性门）
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

  result = pArg1[8608];  // result = 取 pArg1[8608]
  if ( result == 0 )  // 若 result 为 0
  {
    v4 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, int))(*(uint32_t *)pArg1 + 672))(pArg1, 0, nArg2);  // 调虚槽 +672：自身 HP
    *(float *)&Block = COERCE_FLOAT(sub_41A5E0(v4 + 830)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4 + 830, v5, (int)Block);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    *(float *)&Block = COERCE_FLOAT(sub_41A5E0(v4 + 858)) + 0.2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4 + 858, (int)Block, (int)Block);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v6 = sub_41A5E0(v4 + 928);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4 + 928, v7, v6 + 200);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v8 = sub_41A5E0(v4 + 144);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4 + 144, v9, v8 + 25);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v10 = sub_41A5E0(v4 + 60);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4 + 60, v11, v10 + 25);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v4 += 88;
    v12 = sub_41A5E0(v4);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4, v13, v12 + 25);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)pArg1 + 676))(pArg1, 0);  // 调虚槽 +676
    pArg1[8608] = 1;
    pMem = operator new(0x544u);  // new(1348 字节) 分配对象
    Block = pMem;
    v21 = 0;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v15 = sub_4BA9E0((char *)pMem, "Monster/Lugaru/Teeth.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
    else  // 否则分支
      v15 = nullptr;  // v15 = 空指针
    v16 = *(uint32_t *)pArg1;
    v21 = -1;
    pObj = (*(int (/*thiscall*/ **)(uint8_t *, char *))(v16 + 784))(pArg1, v15);
    if ( pObj != 0 )  // 若 pObj 非 0
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
    v19 = 2;
    Block = (void *)3;  // Block = 转换(3)
    nRand = rand() % 2;  // nRand = 调 rand
    return sub_4DB200(24, *(&v19 + nRand));  // 15% 概率随机文案触发（0x4DB130 的门包装）
  }
  return result;
}



// AI 相位门（this+8602/8604/8612）
// ------------------------------------------------------------
// 0x595C40 sub_595C40 —— 大状态 15 入场处理（技能/施放相位【推断】）
// this+8612>0 先走 ·0x595AB0 獠牙变身；vt+136/vt+132 移动校验失败且附属物 this+8604
// 存在时瞬移对齐其位置；表现复位组：vt+196 同步 *(this+6216)+4、vt+876 双槽
// （0=200/200、1=0）、vt+888(0,0,1000,1000)、vt+152(4) 经 sub_432E50 后 vt+896 装载；
// sub_495890(2,0)+sub_4A0550(10) 全局表现收尾，清 this+8602 相位门
// ------------------------------------------------------------
int /*thiscall*/ sub_595C40(int this)  // 实现：大状态 15 入场处理（技能/施放相位(推断)）
{
  int v2; // edi
  int pThis_7C; // eax
  int pThis_78; // eax
  int pThis_80; // edi
  int v6; // eax
  int fld_219C; // eax | =+0x219C 字段 x1（证据 0059A020）
  int fld_219C2; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int pThis_98; // eax
  int v15; // eax
  int result; // eax

  if ( *(int *)(this + 8612) > 0 )  // this+8612〔uAI8612(推断)〕
    sub_595AB0((uint8_t *)this, this);  // 獠牙强化变身（this+8608 一次性门）
  v2 = *(uint32_t *)this;
  pThis_7C = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 124))(this, 0);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C);  // 调虚槽 +120：动画对象
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(v2 + 136))(this, pThis_78) == 0  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
    || (pThis_80 = *(uint32_t *)this,
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this),  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        (*(uint8_t (/*thiscall*/ **)(int, int))(pThis_80 + 132))(this, v6) == 0) )  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉…
  {
    fld_219C = *(uint32_t *)(this + 8604);  // fld_219C = 读 this+8604
    if ( fld_219C != 0 )  // 若 fld_219C 非 0
    {
      fld_219C2 = *(uint32_t *)(this + 8604);  // fld_219C2 = 读 this+8604
      v9 = *(uint32_t *)this;
      v10 = (*(int (**)(void))(*(uint32_t *)fld_219C + 128))();  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_219C2 + 124))(fld_219C2, v10 + 40);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_219C2 + 120))(fld_219C2, v11);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(int, int))(v9 + 112))(this, v12);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
  }
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    this,
    0,
    200,
    200,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    this,
    1,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  v13 = *(uint32_t *)this;
  pThis_98 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);  // 调虚槽 +152：效果通道 3
  v15 = sub_432E50(pThis_98);  // 关系码对调映射
  (*(void (/*thiscall*/ **)(int, int))(v13 + 896))(this, v15);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  sub_495890(2, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  result = sub_4A0550(10);  // result = 调 sub_4A0550 返回值
  *(uint8_t *)(this + 8602) = 0;  // this+8602〔bAI8602(推断)〕
  return result;
}



// 攻击 AI：vt+212 播报 FOX_ATK
// ------------------------------------------------------------
// 0x595D70 sub_595D70 —— 大状态切换分发器
// 旧态 this+6556：15 退出时 vt+216 播报 33、14 退出时 ·0x595820 拆附属；
// 新态分发：8=攻击（清 8600/8601/8602 演出门+vt+212 播 FOX_ATK）、
// 14=撕咬（·0x597640 HOLD 蓄力入场）、15=施放相位（·0x595C40）；
// 尾调 sub_4E33D0 继续基类状态收尾【推断】
// ------------------------------------------------------------
int /*userpurge*/ sub_595D70@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)  // 实现：大状态切换分发器
{
  int v7; // eax
  int v8; // edx

  v7 = pDwArg1[1639];  // v7 = 取 pDwArg1[1639]
  if ( v7 == 15 )  // 若 v7 == 15
  {
    if ( ArgList != 15 )  // 若 ArgList != 15
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);  // 调虚槽 +216：音效 TAG 查询
  }
  else if ( v7 == 14 )
  {
    sub_595820(pDwArg1, nArg2);  // 拆除/回收附属对象（this+8604 槽）
  }
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      v8 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8600) = 0;
      *((uint8_t *)pDwArg1 + 8601) = 0;
      *((uint8_t *)pDwArg1 + 8602) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(pDwArg1, "FOX_ATK", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      break;  // 跳出循环/分支
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      sub_597640(LODWORD(fArg4));  // HOLD 蓄力入场：抓取目标（·0x596650 同构，上限槽 2154）
      break;  // 跳出循环/分支
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      sub_595C40((int)pDwArg1);  // 大状态 15 入场处理（技能/施放相位(推断)）
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  return sub_4E33D0(ArgList, fArg4, nArg5, nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}



// 子类扩展字段复位（this+8600..8628）
// ------------------------------------------------------------
// 0x595E10 sub_595E10 —— 子类 AI 状态区整块复位
// —— 清 this+8600..8636：演出门 8600-8602、附属槽 8604/8608、计数 8624、坐标缓存 8628..8636
// ------------------------------------------------------------
int /*thiscall*/ sub_595E10(int this)  // 实现：子类 AI 状态区整块复位
{
  uint32_t *pThis_21B4; // ecx

  *(uint8_t *)(this + 8600) = 0;  // this+8600〔uAI8600(推断)〕
  *(uint8_t *)(this + 8601) = 0;  // this+8601〔bAI8601(推断)〕
  *(uint8_t *)(this + 8602) = 0;  // this+8602〔bAI8602(推断)〕
  *(uint32_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint32_t *)(this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
  *(uint32_t *)(this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
  pThis_21B4 = (uint32_t *)(this + 8628);  // this+8628〔nPoolTime(推断)〕
  *pThis_21B4 = 0;
  pThis_21B4[1] = 0;
  pThis_21B4[2] = 0;
  return 0;
}



// 撕咬连击 AI：vt+212 播报 FOX_BITE_LOOP（33ms 延迟参数, 100L）
// ------------------------------------------------------------
// 0x595E50 sub_595E50 —— 撕咬连击推进（大状态 14 帧驱动，计数 2152/上限 2153）
// 附属槽 this+8604 为空直接 vt+560 setState 15 退出；目标态 vt+840==9 且动画帧标志
// （vt+200 结果+170）有效时，按扑咬落点（自身坐标朝向 ±15、y+45）调 sub_4E5F70 硬直率掷；
// 连击计数 ++this+8608 达上限 this+8612 或目标 HP（vt+684）耗尽 → setState 15 收招、
// 否则 sub_4926A0 复位帧游标续环；首击（计数==1）vt+212 播 FOX_BITE_LOOP；
// 目标未进 9 态且非 5 态时拉入 9【推断：被叼住判定】
// ------------------------------------------------------------
int /*usercall*/ sub_595E50@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：撕咬连击推进（大状态 14 帧驱动，计数 2152/上限 2153）
{
  int pGrabTgt; // ecx
  int nVtA; // edx
  int nPosX; // eax
  double fPosX; // st7
  int nVtB; // eax
  int nPosY; // eax
  int nVtC; // edx
  int nPosZ; // eax
  int nLimit; // edx
  int nCount; // eax
  int fld_grab; // ecx
  unsigned int uVt684; // eax
  int nStkObj2; // eax
  int result; // eax
  float fHitPtX; // [esp+4h] [ebp-1Ch] BYREF
  float fHitPtY; // [esp+8h] [ebp-18h]
  float fHitPtZ; // [esp+Ch] [ebp-14h]
  int nPad1; // [esp+10h] [ebp-10h]
  int nPad2; // [esp+14h] [ebp-Ch]
  int nPad3; // [esp+18h] [ebp-8h]
  int nTmpCoord; // [esp+1Ch] [ebp-4h]

  pGrabTgt = pArg1[2151];  // pGrabTgt = 取 pArg1[2151]
  if ( pGrabTgt == 0 )  // 无被抓目标：直接退出 15 态
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pGrabTgt + 840))(pGrabTgt) == 9 )  // 目标处于 9 态（被叼住）
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0 )  // 本体动作已结束段
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )  // 存活
      {
        nVtA = *pArg1;
        fHitPtX = 0.0;
        fHitPtY = 0.0;
        fHitPtZ = 0.0;
        nPad1 = 0;
        nPad2 = 0;
        nPad3 = 0;
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(nVtA + 152))(pArg1) != 0 )  // 调虚槽 +152：效果通道 3
          nPosX = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) + 15;  // 朝向→口部右15
        else  // 否则分支
          nPosX = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - 15;  // 背向→口部左15
        nTmpCoord = nPosX;
        fPosX = (double)nPosX;
        nVtB = *pArg1;
        fHitPtX = fPosX;
        nPosY = (*(int (/*thiscall*/ **)(uint32_t *))(nVtB + 124))(pArg1);  // 本体 Y
        nVtC = *pArg1;
        nTmpCoord = nPosY;
        fHitPtY = (float)nPosY;
        nPosZ = (*(int (/*thiscall*/ **)(uint32_t *))(nVtC + 128))(pArg1);  // 本体 Z
        fld_grab = pArg1[2151];  // fld_grab = 取 pArg1[2151]
        nTmpCoord = nPosZ + 45;  // 口部高度 = Z+45
        fHitPtZ = (float)(nPosZ + 45);
        sub_4E5F70(nArg2, (int)pArg1, fld_grab, &fHitPtX, 1, 1);  // 咬击判定（基点=口部坐标）
      }
      nLimit = pArg1[2153];  // 连击上限
      nCount = pArg1[2152] + 1;  // 撕咬计数 +1
      pArg1[2152] = nCount;
      if ( nCount >= nLimit  // 若 nCount >= nLimit
        || (uVt684 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 684))(pArg1[2151]), sub_41A5E0(uVt684) <= 0) )  // 上限到或目标 vt+684 归零（死亡）
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);  // 结束 15 态
      }
      else  // 否则分支
      {
        nStkObj2 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);  // 调虚槽 +200：取动画对象
        sub_4926A0(nStkObj2);  // 动作帧游标复位（继续下一口）
      }
      if ( pArg1[2152] == 1 )
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "FOX_BITE_LOOP", 33, 0, 0);  // 首口循环音
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pArg1[2151] + 604))(pArg1[2151], 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[2151] + 612))(pArg1[2151], 1, 1);  // 目标 vt+612(1,1) 擒抱锁定
  }
  else  // 目标不在 9 态：存活则强制拉入 9 态（被叼住）
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 840))(pArg1[2151]);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result != 5 )  // 若 result != 5
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 308))(pArg1[2151]);  // 调虚槽 +308：是否本地玩家
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2151] + 560))(  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
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
// 0x596030 sub_596030 —— 朝目标突进的速率设定
// 目标槽 this+7252 存在时：X 距差 ×1.2（clamp ±200）、Y 距差 ×1.2（clamp ±100），
// 按 nArg4 时长(ms) 换算毫秒速率写 vt+876 双轴速率槽（0=X 轴、1=Y 轴），
// 尾调 vt+896(this, X<0, 2/3 按 Y 符号) 翻转朝向；供 ·0x5961B0 攻击段 1/3 以 1000ms 调用
// ------------------------------------------------------------
int /*userpurge*/ sub_596030@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)  // 实现：朝目标突进的速率设定
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

  result = pArg1[1813];  // result = 取 pArg1[1813]
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v6 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)result + 120))(result, nArg3, nArg2);  // 调虚槽 +120：动画对象
    v16 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - v6) * 1.2;  // 调虚槽 +120：动画对象
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813]);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
    v8 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1) - v7) * 1.2;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
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
    v17 = fabs(v16) / v13 * 1000.0;  // v17 = 调 fabs
    v15 = fabs(v8) / v13 * 1000.0;  // v15 = 调 fabs
    v14 = 3;
    if ( v8 >= 0.0 )
      v14 = 2;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      pArg1,
      0,
      (uint64_t)v17,
      (uint64_t)v17,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      pArg1,
      1,
      (uint64_t)v15,
      (uint64_t)v15,
      0,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t *, bool, int))(*pArg1 + 896))(pArg1, v16 < 0.0, v14);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  }
  return result;
}



// AI 相位辅助（107L）
// ------------------------------------------------------------
// 0x5961B0 sub_5961B0 —— 每帧 AI 主驱动（攻击段推进）
// sub_4E1780 前置后按大状态 this+6556 分发：14 → ·0x595E50 撕咬推进、15 → sub_5943F0
// 施法段推进；8 = 攻击相位，按攻击段号 this+7028 推进：段 0 → vt+352 起手+置 8600 门、
// 段 1/3 → ·0x596030 突进+sub_4A0550(120/90) 延时、段 2 → sub_5985E0(400) 经 sub_4A05C0 延时；
// 动画对象 *(this+112)（+24 计时浮点/+192 动画态）驱动表现对象 *(this+120)：
// 计时>0 → sub_4AECE0(1)+置 8601；动画态 4 → 复位 vt+876/vt+896 后
// sub_4AECE0(1/2→6、3→2、4→9)+置 8602【推断：sub_4AECE0 参数为表现动作号】
// ------------------------------------------------------------
void /*usercall*/ sub_5961B0(int pArg1@<ecx>, int nArg2@<ebx>)  // 实现：每帧 AI 主驱动（攻击段推进）
{
  int nSegIdx; // edi
  double fStopTime; // st7
  int nStopCode; // ebx
  int *pActObj; // ecx

  sub_4E1780((uint32_t *)pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( *(uint32_t *)(pArg1 + 6556) != 8 )  // 非攻击大状态：转 14/15 态子处理
  {
    if ( *(uint32_t *)(pArg1 + 6556) == 14 )  // pArg1+6556〔大状态ID〕
    {
      sub_595E50((uint32_t *)pArg1, nArg2);  // 撕咬连击推进（大状态 14 帧驱动，计数 2152/上限 2153）
    }
    else if ( *(uint32_t *)(pArg1 + 6556) == 15 )  // pArg1+6556〔大状态ID〕
    {
      sub_5943F0((uint32_t *)pArg1);  // 施法段推进辅助（动画状态4门控：音效起播 + 帧时刻对齐 + 收态）
    }
    return;
  }
  nSegIdx = pArg1 + 7028;
  if ( sub_41A5E0(pArg1 + 7028) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 3 && *(uint8_t *)(pArg1 + 8600) == 0 )  // 段0 起手帧≥3
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 352))(pArg1);  // 起手动作
    *(uint8_t *)(pArg1 + 8600) = 1;  // 起手一次性门
  }
  if ( sub_41A5E0(pArg1 + 7028) >= 1 )  // 攻击段 1-4
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) == 0 )  // 死亡路径
    {
LABEL_27:  // 标签 LABEL_27（跳转合流点）
      if ( *(uint8_t *)(pArg1 + 8601) != 0 && *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )  // 复合条件判定（与/或）
      {
        nStopCode = 0;
        if ( sub_41A5E0(pArg1 + 7028) == 1 || sub_41A5E0(pArg1 + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
          nStopCode = 6;
        if ( sub_41A5E0(pArg1 + 7028) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          nStopCode = 9;
        }
        else if ( sub_41A5E0(pArg1 + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          nStopCode = 2;
        }
        sub_4AECE0(*(void **)(pArg1 + 120), nStopCode);  // 按段号差异化收招
        *(uint8_t *)(pArg1 + 8602) = 1;  // 收招门
      }
      goto LABEL_38;
    }
    if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1 )  // pArg1+120〔pAnimObj〕
    {
      if ( *(uint8_t *)(pArg1 + 8601) != 0 )  // pArg1+8601〔bAI8601(推断)〕
      {
LABEL_24:  // 标签 LABEL_24（跳转合流点）
        if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )  // 复合条件判定（与/或）
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
            pArg1,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 896))(pArg1, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
        }
        goto LABEL_27;
      }
      if ( sub_41A5E0(pArg1 + 7028) == 1 || sub_41A5E0(pArg1 + 7028) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        sub_596030((uint32_t *)pArg1, nArg2, nSegIdx, 1000);  // 段1/4：朝目标突进 1000ms
        sub_4A0550(120);  // 调 镜头幅度
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        fStopTime = (double)sub_5985E0(400.0);  // 朝目标突进：施加速率并返回所需时长
        if ( fStopTime < 300.0 )
          fStopTime = 300.0;  // 最短 300（帧数下限）
        sub_4A05C0((uint64_t)(fStopTime * 0.5));  // 一半时长
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        sub_596030((uint32_t *)pArg1, nArg2, nSegIdx, 1000);  // 段3：突进 1000ms
        sub_4A0550(90);  // 调 镜头幅度
      }
    }
    if ( *(uint8_t *)(pArg1 + 8601) == 0 )  // pArg1+8601〔bAI8601(推断)〕
    {
LABEL_38:  // 标签 LABEL_38（跳转合流点）
      if ( *(float *)(*(uint32_t *)(pArg1 + 112) + 24) > 0.0 && *(uint8_t *)(pArg1 + 8601) == 0 )  // 下落中（竖直速度>0）
      {
        pActObj = *(int **)(pArg1 + 120);  // pArg1+120〔pAnimObj〕
        if ( pActObj[37] < 1 )
          sub_4AECE0(pActObj, 1);  // 落地前收姿态 1
        *(uint8_t *)(pArg1 + 8601) = 1;  // 落地门
      }
      return;
    }
    goto LABEL_24;
  }
}



// 治愈技能：vt+212 播报 FOX_CURE（110L；治愈狐治疗演出, sub_4049C0 插值）
// ------------------------------------------------------------
// 0x596400 sub_596400 —— 治愈狐治疗技能（FOX_CURE，30% 概率触发）
// 遍历 *(this+116) 对象表，vt+40(obj,529) 过滤后要求同队（vt+376 相等）、距离
// vt+8<=300、当前 HP（vt+736）低于半血（vt+740/2）且 rand>=70 才出手；
// 每次消耗剩余次数 this+8624（·0x596990 初始化为 3），治疗量 = maxHP×0.25..0.5
// 经 sub_4049C0 在 this+7280..7284 时间窗插值写 this+8620，构造 sub_4D6810
// CNChangeHp（量,500,1,1）后 vt+56 施放；sub_4DB200(24,2) 喊话 + vt+212 播 FOX_CURE
// ------------------------------------------------------------
int /*thiscall*/ sub_596400(int *this)  // 实现：治愈狐治疗技能（FOX_CURE，30% 概率触发）
{
  unsigned int i; // edi
  int fld_e29; // ecx | =+0x0074 字段 x2（证据 005FD6C0）
  int nBegin1; // edx
  int result; // eax
  int nBegin2; // edx
  int pScanObj; // ecx
  int fld_e292; // ecx
  int nBegin3; // edx
  int *pAlly; // edi
  int nAllyRoom; // ebx
  int nHalfHp; // ebx
  uint64_t nHealMax; // rax
  int nSkillRow; // ebx
  int nSpan; // ebx
  int nSkillRow2; // eax
  int pHealObj; // eax
  float fHealMin; // [esp+10h] [ebp-34h]
  float fld_e2155; // [esp+10h] [ebp-34h] | =+0x21AC 字段 x1（证据 005AF910）
  float fHealMax; // [esp+14h] [ebp-30h]
  void *Block; // [esp+2Ch] [ebp-18h]
  int nHealMaxInt; // [esp+30h] [ebp-14h]
  unsigned int nIdxSave; // [esp+34h] [ebp-10h]
  uint32_t *pAtkBox3; // [esp+34h] [ebp-10h]

  for ( i = 0; ; ++i )  // 遍历场景对象表
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    nBegin1 = *(uint32_t *)(fld_e29 + 8);
    nIdxSave = i;
    result = nBegin1 != 0 ? (*(uint32_t *)(fld_e29 + 12) - nBegin1) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;  // 跳出循环/分支
    nBegin2 = *(uint32_t *)(fld_e29 + 8);
    if ( nBegin2 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - nBegin2) >> 2 )  // 若 nBegin2 != 0
      pScanObj = *(uint32_t *)(nBegin2 + 4 * i);
    else  // 否则分支
      pScanObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pScanObj + 40))(pScanObj, 529) != 0 )  // 529=哥布林族
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      nBegin3 = *(uint32_t *)(fld_e292 + 8);
      if ( nBegin3 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - nBegin3) >> 2 )  // 若 nBegin3 != 0
        pAlly = *(int **)(nBegin3 + 4 * i);
      else  // 否则分支
        pAlly = nullptr;  // pAlly = 空指针
      nAllyRoom = (*(int (/*thiscall*/ **)(int *))(*pAlly + 376))(pAlly);  // 调虚槽 +376：坐标同步包（type 37）
      if ( nAllyRoom == (*(int (/*thiscall*/ **)(int *))(*this + 376))(this)  // 同队伍
        && (*(int (/*thiscall*/ **)(int *, int *, uint32_t))(*this + 8))(this, pAlly, 0) <= 300  // 距离≤300
        && (*(this + 1908) != 2 || this != pAlly) )  // 狂气态不自我治疗
      {
        nHalfHp = (*(int (/*thiscall*/ **)(int *))(*pAlly + 740))(pAlly) / 2;  // 半血线
        if ( (*(int (/*thiscall*/ **)(int *))(*pAlly + 736))(pAlly) < nHalfHp  // 当前血 < 半血
          && (*(int (/*thiscall*/ **)(int *))(*pAlly + 736))(pAlly) > 0  // 活着
          && rand() % 100 >= 70 )  // 30% 概率出手
        {
          result = *(this + 2156);  // this+8624〔uAI8624(推断)〕
          *(this + 2156) = result - 1;  // 剩余次数 -1（初始化 3 次）
          if ( result > 0 )  // 若 result > 0
          {
            Block = (void *)(uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(*pAlly + 740))(pAlly) * 0.25);  // 治疗下限 = maxHP×0.25
            nHealMax = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(*pAlly + 740))(pAlly) * 0.5);  // 治疗上限 = maxHP×0.5
            nHealMaxInt = nHealMax;
            nSkillRow = (*(int (/*fastcall*/ **)(int *, uint32_t))(*this + 1032))(this, HIDWORD(nHealMax));  // 技能表行
            nSpan = *(uint32_t *)(nSkillRow + 52) - *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 1032))(this) + 48);  // 行时长
            pAtkBox3 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
            nSkillRow2 = (*(int (/*thiscall*/ **)(int *))(*this + 1032))(this);  // 调虚槽 +1032
            fHealMax = (float)nHealMaxInt;
            fHealMin = (float)(int)Block;
            *(this + 2155) = (uint64_t)sub_4049C0(fHealMin, fHealMax, *pAtkBox3 - *(uint32_t *)(nSkillRow2 + 48), nSpan);  // 治疗量按技能进度插值
            if ( operator new(0x80u) != nullptr )  // new(128 字节) 分配对象
            {
              fld_e2155 = (float)*(this + 2155);  // this+8620〔uAI8620(推断)〕
              pHealObj = sub_4D6810(LODWORD(fld_e2155), 500, 1, 1);  // CNChangeHp 治疗包（500/1/1）
            }
            else  // 否则分支
            {
              pHealObj = 0;
            }
            (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pHealObj + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
              pHealObj,
              pAlly,  // 绑定到队友
              this,
              0,
              0,
              0,
              -1);
            sub_4DB200(24, 2);  // 喊话（24 组 2 号）
            return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                     this,
                     "FOX_CURE",  // 标签 FOX_CURE
                     -1,
                     0,
                     0);
          }
          return result;
        }
      }
      i = nIdxSave;
    }
  }
  return result;
}



// 蓄力技能：vt+212 "HOLD"（104L）
// ------------------------------------------------------------
// 0x596650 sub_596650 —— HOLD 蓄力入场：抓取目标（连击上限槽 2153）
// sub_45EBE0 从 pArg2 参数包解析目标，类型 vt+40(17) 且高度槽 vt+128<=0【推断】
// 才存入 this+8604；抓取成功时缓存目标 vt+120/124/128 坐标至 this+8628..8636，
// 按自身朝向（vt+152）偏 ±30 经 vt+112 挪近目标、vt+848(目标,1) 建立绑定
// 【推断：拖拽/叼住】；表现复位组：vt+196、vt+876×2、vt+888(0,2,1000,1000)、
// vt+896(4,4)、vt+344；连击上限 this+8612 = vt+384(0)/(1) 经 sub_4049C0 插值；
// sub_4DB200(24, 0/1) 喊话 + vt+212 播 HOLD
// ------------------------------------------------------------
int /*thiscall*/ sub_596650(int *this, int pArg2)  // 实现：HOLD 蓄力入场：抓取目标（连击上限槽 2153）
{
  int pTarget; // eax
  int pTarget2; // edi
  int fld_e2151; // ecx | =+0x219C 字段 x1（证据 0059A020）
  int nGrabX; // eax
  int fld_e21512; // ecx
  int nGrabY; // eax
  int fld_e21513; // ecx
  int nGrabZ; // eax
  int nVt1; // edx
  int nFacing; // eax
  int fld_e21514; // ecx
  int nSnapX; // eax
  int nVt2; // ebx
  int fld_e21515; // edi
  int nTgtVt; // edx
  int nTgtZ; // eax
  int nTgtY; // eax
  uint32_t *fld_e28; // edi
  int nAx1; // eax
  int fld_e1821; // edi
  uint32_t *pAtkBox3; // eax
  int nRand; // eax
  float fAx0; // [esp+70h] [ebp-24h]
  float fAx1; // [esp+74h] [ebp-20h]
  int nVoiceIdx; // [esp+8Ch] [ebp-8h]
  int fld_e215152; // [esp+90h] [ebp-4h]
  int nSnapXAdj; // [esp+9Ch] [ebp+8h]
  int nAx1Tmp; // [esp+9Ch] [ebp+8h]

  pTarget = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));  // pTarget = 调 sub_45EBE0 返回值
  pTarget2 = pTarget;
  if ( pTarget == 0  // 若 pTarget 为 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pTarget + 40))(pTarget, 17) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || (*(this + 2151) = pTarget2, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 128))(pTarget2) > 0) )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  {
    *(this + 2151) = 0;  // this+8604〔bAI8604(推断)〕
  }
  fld_e2151 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
  if ( fld_e2151 != 0 )  // 若 fld_e2151 非 0
  {
    nGrabX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2151 + 120))(fld_e2151);  // 调虚槽 +120：动画对象
    fld_e21512 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    *(this + 2157) = nGrabX;  // this+8628〔nPoolTime(推断)〕
    nGrabY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21512 + 124))(fld_e21512);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    fld_e21513 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    *(this + 2158) = nGrabY;  // this+8632〔bDevourFlag(推断)〕
    nGrabZ = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21513 + 128))(fld_e21513);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    nVt1 = *this;
    *(this + 2159) = nGrabZ;  // this+8636〔pDollTarget(推断)〕
    nFacing = (*(int (/*thiscall*/ **)(int *))(nVt1 + 152))(this);  // 调虚槽 +152：效果通道 3
    fld_e21514 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    if ( nFacing != 0 )  // 若 nFacing 非 0
      nSnapX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) - 30;  // 调虚槽 +120：动画对象
    else  // 否则分支
      nSnapX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) + 30;  // 调虚槽 +120：动画对象
    nVt2 = *this;
    nSnapXAdj = nSnapX;
    fld_e21515 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    nTgtVt = *(uint32_t *)fld_e21515;
    fld_e215152 = fld_e21515;
    nTgtZ = (*(int (/*thiscall*/ **)(int))(nTgtVt + 128))(fld_e21515);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
    nTgtY = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21515 + 124))(fld_e21515, nTgtZ + 40);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    (*(void (/*thiscall*/ **)(int *, int, int))(nVt2 + 112))(this, nSnapXAdj, nTgtY + 1);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2151) + 848))(*(this + 2151), 1);  // 调虚槽 +848：冻结标志写入（+6744，0→-1 / 非0→0）
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));  // 调虚槽 +344：取坐标三元组
  fld_e28 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0  // 调虚槽 +308：是否本地玩家
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  fld_e215152 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  nAx1 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  fld_e1821 = *(this + 1821) - *(this + 1820);
  nAx1Tmp = nAx1;
  pAtkBox3 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  fAx1 = (float)nAx1Tmp;
  fAx0 = (float)fld_e215152;
  *(this + 2153) = (uint64_t)sub_4049C0(fAx0, fAx1, *pAtkBox3 - *(this + 1820), fld_e1821);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
  *(this + 2152) = 0;  // this+8608〔uAI8608(推断)〕
  *(this + 2154) = 0;  // this+8616〔uAI8616(推断)〕
  nVoiceIdx = 0;
  fld_e215152 = 1;
  nRand = rand() % 2;  // nRand = 调 rand
  sub_4DB200(24, *(&nVoiceIdx + nRand));  // 15% 概率随机文案触发（0x4DB130 的门包装）
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5968A0 sub_5968A0 —— 速度槽还原（·0x5968D0 的逆操作）
// —— nArg2==0 时把 *(this+7620)+100 浮点 × 0.76923078（×10/13）写回同槽
// ------------------------------------------------------------
int /*thiscall*/ sub_5968A0(uint32_t *this, int nArg2, int nArg3)  // 实现：速度槽还原（·0x5968D0 的逆操作）
{
  int result; // eax
  int fld_e1905; // eax | =+0x1DC4 字段 x1（证据 0059A020）
  double v5; // st7

  result = nArg2;
  if ( nArg2 == 0 )  // 若 nArg2 为 0
  {
    fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
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
// 0x5968D0 sub_5968D0 —— 变种狐 AI 区复位+相位选择
// 清 this+7531..7596 子类字段；nArg2==0 → this+7596=-30 且速度槽 *(this+7620)+100
// ×1.3（·0x5968A0 为其逆操作）；nArg2∈1..2 → this+7538=1
// ------------------------------------------------------------
int /*thiscall*/ sub_5968D0(int this, int nArg2, int nArg3)  // 实现：变种狐 AI 区复位+相位选择
{
  int result; // eax

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  if ( nArg2 != 0 )  // 若 nArg2 非 0
  {
    if ( nArg2 > 0 && nArg2 <= 2 )  // 若 nArg2 > 0 与/或 nArg2 <= 2
      *(uint8_t *)(this + 7538) = 1;  // this+7538〔bCfgBlock18(推断)〕
  }
  else  // 否则分支
  {
    *(uint32_t *)(this + 7596) = -30;  // this+7596〔nOffset7596(推断)〕
    *(float *)(*(uint32_t *)(this + 7620) + 100) = *(float *)(*(uint32_t *)(this + 7620) + 100) * 1.3;  // this+7620〔pStatusPanel(推断)〕
  }
  return result;
}



// 语音注册：R_FOX_TALK/DMG + FOX_DIE（第三只狐狸实例）
// ------------------------------------------------------------
// 0x596990 sub_596990 —— 第三只狐狸实例参数初始化（治愈狐）
// 写 this+6792..6808 参数槽（2/2/2/3/4）并注册 R_FOX_TALK/R_FOX_DMG/FOX_DIE 语音；
// vt+384(2)/(3) 两档参数按 vt+672(3) 时钟在 this+7280..7284 窗内 sub_4049C0 插值
// 写 this+8620 = 治疗量基数（·0x596400 FOX_CURE 引用），this+8624=3 为剩余治疗次数
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_596990(uint32_t *this)  // 实现：第三只狐狸实例参数初始化（治愈狐）
{
  int fld_e1821; // edi
  uint32_t *v3; // eax
  uint64_t result; // rax
  float v5; // [esp+Ch] [ebp-20h]
  float v6; // [esp+10h] [ebp-1Ch]
  int v7; // [esp+24h] [ebp-8h]
  int v8; // [esp+28h] [ebp-4h]

  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_FOX_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_FOX_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("FOX_DIE", 7u);  // 【std::string构造赋值】
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 2);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v6 = (float)v8;
  v5 = (float)v7;
  result = (uint64_t)sub_4049C0(v5, v6, *v3 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2155) = result;  // this+8620〔uAI8620(推断)〕
  *(this + 2156) = 3;  // this+8624〔uAI8624(推断)〕
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x596A70 sub_596A70 —— 受击钩子：架招反应触发（·0x595650 同构）
// 大状态 this+6556==8、攻击段 this+7028==3 等门通过时打包攻击者坐标走 vt+560
// setState 14（架招【推断】），尾调 sub_4DB480 反击判定
// ------------------------------------------------------------
int /*thiscall*/ sub_596A70(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：受击钩子：架招反应触发（·0x595650 同构）
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8  // this+6556〔大状态ID〕
    && sub_41A5E0((unsigned int)(this + 1757)) == 3  // crypt4byte 解密校验（·0x41A590 逆运算）
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 948))(pObj) != 0  // 调虚槽 +948
    && *(this + 154) != 14 )  // this+616〔nReactionState〕
  {
    memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
    v6 = *(uint32_t *)pObj;
    v9 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(v6 + 48))(pObj);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    v9 = -1;
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
  return sub_4DB480(pObj, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 参数打包 AI（75L）
// ------------------------------------------------------------
// 0x596B70 sub_596B70 —— 每帧相位机：治愈/呼喊决策
// 相位 this+1787：0 → vt+1284 出场；4 → 50% 概率分岔：未中签走 ·0x596400 治愈尝试，
// 中签且自身存活（vt+308）、无架招（vt+840==0）、宿主 this+7252 满足类型 17 与
// 距离/状态门（vt+128>60、|dx|<100、宿主 vt+840∈{6,7}）且概率 15%/30%（this+7636 门）
// → 打包 {4} 走 vt+560 setState 8【推断：号召/吼叫】；无宿主 → vt+1104 切相位 13、
// 相位 13/14/15 有宿主切回 4
// ------------------------------------------------------------
void /*thiscall*/ sub_596B70(int *this)  // 实现：每帧相位机：治愈/呼喊决策
{
  int fld_e1813; // eax | =+0x1C54 字段 x1
  int fld_e18132; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int v4; // ebx
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( *(this + 1787) )  // this+7148〔nBigState〕
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      (*(void (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调虚槽 +1284
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
      {
        if ( rand() % 100 >= 50 )  // rand()%100 取模随机
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
            && (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 0 )  // 调虚槽 +840：大状态 getter（this+6556）
          {
            fld_e1813 = *(this + 1813);  // this+7252〔pTarget7252〕
            if ( fld_e1813 != 0 && (*(uint8_t (/*stdcall*/ **)(int))(*(uint32_t *)fld_e1813 + 40))(17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
            {
              fld_e18132 = *(this + 1813);  // this+7252〔pTarget7252〕
              if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 128))(fld_e18132) > 60 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
              {
                v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 120))(fld_e18132);  // 调虚槽 +120：动画对象
                if ( (int)abs32(v4 - (*(int (/*thiscall*/ **)(int *))(*this + 120))(this)) < 100  // 调虚槽 +120：动画对象
                  && ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 840))(fld_e18132) == 6  // 调虚槽 +840：大状态 getter（this+6556）
                   || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 840))(fld_e18132) == 7)  // 调虚槽 +840：大状态 getter（this+6556）
                  && rand() % 100 < (*(this + 1909) != 0 ? 15 : 30) )  // this+7636〔nPosWinY〕
                {
                  memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
                  v6[3] = 0;
                  v6[0] = 4;
                  sub_431230((int)pBuf, v6);  // uint32 vector push_back
                  (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
                  sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
                }
              }
            }
          }
        }
        else  // 否则分支
        {
          sub_596400(this);  // 治愈狐治疗技能（FOX_CURE，30% 概率触发）
        }
      }
      else  // 否则分支
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      }
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
        goto LABEL_21;
      break;  // 跳出循环/分支
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
LABEL_21:  // 标签 LABEL_21（跳转合流点）
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      return;
  }
}



// 参数打包 AI（89L）
// ------------------------------------------------------------
// 0x596D90 sub_596D90 —— 拆除/回收附属对象（·0x595820 同构，坐标槽 2157-2159）
// 对 this+8604 附属：vt+604/vt+612 停止隐藏；坐标对齐三态回退（vt+136 直传
// this+8628..8636 → 失败 vt+140 碰撞修正 → 自身坐标）；存活时打包 {4,0,1,200,200}
// 走 vt+560 setState 4 + vt+564【推断：尺寸/位移参数】；末尾 vt+848(0) 解绑并清 this+8604
// ------------------------------------------------------------
void /*usercall*/ sub_596D90(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 实现：拆除/回收附属对象（·0x595820 同构，坐标槽 2157-2159）
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

  pObj3 = pDwArg1[2151];  // pObj3 = 取 pDwArg1[2151]
  if ( pObj3 != 0 )  // 若 pObj3 非 0
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 612))(pDwArg1[2151], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 136))(  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
           pDwArg1[2151],
           pDwArg1[2157],
           pDwArg1[2158],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2151] + 112))(pDwArg1[2151], pDwArg1[2157], pDwArg1[2158], pDwArg1[2159]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
    else  // 否则分支
    {
      pObj = pDwArg1[2151];  // pObj = 取 pDwArg1[2151]
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);  // 调虚槽 +120：动画对象
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2157, pDwArg1 + 2158, v7);  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
      pObj2 = pDwArg1[2151];  // pObj2 = 取 pDwArg1[2151]
      if ( v8 != 0 )  // 若 v8 非 0
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2157], pDwArg1[2158], pDwArg1[2159]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
      else  // 否则分支
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2159]);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2151], v12);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 308))(pDwArg1[2151]) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      Block = nullptr;  // Block = 空指针
      v15 = 0;
      v16 = 0;
      v18 = 0;
      pObj4 = 4;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 0;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 1;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 560))(pDwArg1[2151], 4, v13, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 564))(pDwArg1[2151]);
      v18 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
      Block = nullptr;  // Block = 空指针
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 848))(pDwArg1[2151], 0);  // 调虚槽 +848：冻结标志写入（+6744，0→-1 / 非0→0）
    pDwArg1[2151] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x596F90 sub_596F90 —— 死亡/移除通知分发（·0x595A20 同构）
// 消亡对象为附属 this+8604（自身态 14 时 ·0x596D90 拆除+清槽）或自身（先拆再 vt+216 播 33）；
// 尾调 sub_4D9170
// ------------------------------------------------------------
int /*userpurge*/ sub_596F90@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)  // 实现：死亡/移除通知分发（·0x595A20 同构）
{
  if ( pDwArg3 == (int *)pDwArg1[2151] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
      sub_596D90(pDwArg1, nArg2);  // 拆除/回收附属对象（·0x595820 同构，坐标槽 2157-2159）
    pDwArg1[2151] = 0;
  }
  if ( pDwArg3 == pDwArg1 )  // 若 pDwArg3 == pDwArg1
  {
    if ( pDwArg1[2151] != 0 )
    {
      sub_596D90(pDwArg1, nArg2);  // 拆除/回收附属对象（·0x595820 同构，坐标槽 2157-2159）
      pDwArg1[2151] = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);  // 调虚槽 +216：音效 TAG 查询
  }
  return sub_4D9170(pDwArg3);  // 返回 调 sub_4D9170 返回值
}



// 攻击 AI：vt+212 播报 FOX_ATK
// ------------------------------------------------------------
// 0x597000 sub_597000 —— 大状态切换分发器（·0x595D70 同构）
// 旧态 15 退出 → vt+216 播 33；旧态 14 退出 → ·0x596D90 拆附属；新态 8 → 清
// 8600/8601/8602 + vt+212 播 FOX_ATK；14 → ·0x596650 HOLD 蓄力；15 → ·0x597890
// 施放相位入场；尾调 sub_4E33D0 基类收尾【推断】
// ------------------------------------------------------------
int /*userpurge*/ sub_597000@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, int nArg4, int nArg5, int nArg6)  // 实现：大状态切换分发器（·0x595D70 同构）
{
  int v7; // eax
  int v8; // edx

  v7 = pDwArg1[1639];  // v7 = 取 pDwArg1[1639]
  if ( v7 == 15 )  // 若 v7 == 15
  {
    if ( ArgList != 15 )  // 若 ArgList != 15
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);  // 调虚槽 +216：音效 TAG 查询
  }
  else if ( v7 == 14 )
  {
    sub_596D90(pDwArg1, nArg2);  // 拆除/回收附属对象（·0x595820 同构，坐标槽 2157-2159）
  }
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      v8 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8600) = 0;
      *((uint8_t *)pDwArg1 + 8601) = 0;
      *((uint8_t *)pDwArg1 + 8602) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(pDwArg1, "FOX_ATK", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      break;  // 跳出循环/分支
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      sub_596650(pDwArg1, nArg4);  // HOLD 蓄力入场：抓取目标（连击上限槽 2153）
      break;  // 跳出循环/分支
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      sub_597890(pDwArg1);  // 大状态 15 入场处理（·0x595C40 同构）
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  return sub_4E33D0(ArgList, *(float *)&nArg4, nArg5, nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}



// 【vmt200 命中处理器覆写】（虚表 0x6CFF24 +512 槽，狐狸系子类）
// ------------------------------------------------------------
// 0x5970A0 sub_5970A0 —— vmt200 命中处理器覆写（受击特效）
// 10%/5% 概率（this+7632 非零时减半）经 vt+580 广播表现 48003（附带 this+8608 计数）；
// 尾调 sub_4DA3B0 命中包分发前置
// ------------------------------------------------------------
int /*thiscall*/ sub_5970A0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：vmt200 命中处理器覆写（受击特效）
{
  if ( rand() % 100 < (*(this + 1908) != 0 ? 5 : 10)  // this+7632〔uWindow7632(推断)〕
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
      this,
      48003,
      *(this + 2152),  // this+8608〔计数〕
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
  return sub_4DA3B0(nArg2, nArg3, nArg4);  // 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
}



// 撕咬连击 AI：FOX_BITE_LOOP（100L）
// ------------------------------------------------------------
// 0x597120 sub_597120 —— 撕咬连击推进（·0x595E50 同构，计数 2153/上限 2154）
// 附属 this+8604 态 9 时逐帧推进：扑咬落点（朝向 ±15、y+45）经 sub_4E5F70 硬直率掷；
// 连击计数 ++this+8612 达上限 this+8616 或目标 HP 尽 → vt+560 setState 15 收招、
// 否则 sub_4926A0 复位帧游标续环；首击播 FOX_BITE_LOOP；
// 目标未进 9 态且非 5 态时拉入 9【推断：被叼住判定】
// ------------------------------------------------------------
int /*usercall*/ sub_597120@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：撕咬连击推进（·0x595E50 同构，计数 2153/上限 2154）
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

  pObj = pArg1[2151];  // pObj = 取 pArg1[2151]
  if ( pObj == 0 )  // 若 pObj 为 0
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 9 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0 )  // 调虚槽 +200：取动画对象
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )  // 调虚槽 +308：是否本地玩家
      {
        v4 = *pArg1;
        v17 = 0.0;
        v18 = 0.0;
        v19 = 0.0;
        v20 = 0;
        v21 = 0;
        v22 = 0;
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 152))(pArg1) != 0 )  // 调虚槽 +152：效果通道 3
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) + 15;  // 调虚槽 +120：动画对象
        else  // 否则分支
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - 15;  // 调虚槽 +120：动画对象
        v23 = v5;
        v6 = (double)v5;
        v7 = *pArg1;
        v17 = v6;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 124))(pArg1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
        v9 = *pArg1;
        v23 = v8;
        v18 = (float)v8;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 128))(pArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
        v11 = pArg1[2151];  // v11 = 取 pArg1[2151]
        v23 = v10 + 45;
        v19 = (float)(v10 + 45);
        sub_4E5F70(nArg2, (int)pArg1, v11, &v17, 1, 1);  // 硬直率掷（研究 §5.1 第 14 轮定案：同构于暴击掷）
      }
      v12 = pArg1[2154];  // v12 = 取 pArg1[2154]
      v13 = pArg1[2153] + 1;
      pArg1[2153] = v13;
      if ( v13 >= v12  // 若 v13 >= v12
        || (v14 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 684))(pArg1[2151]), sub_41A5E0(v14) <= 0) )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      }
      else  // 否则分支
      {
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);  // 调虚槽 +200：取动画对象
        sub_4926A0(v15);  // 帧游标复位（+44 帧数组；递归子链 +204）
      }
      if ( pArg1[2153] == 1 )
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "FOX_BITE_LOOP", 33, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pArg1[2151] + 604))(pArg1[2151], 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[2151] + 612))(pArg1[2151], 1, 1);
  }
  else  // 否则分支
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 840))(pArg1[2151]);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result != 5 )  // 若 result != 5
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 308))(pArg1[2151]);  // 调虚槽 +308：是否本地玩家
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2151] + 560))(  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
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
// 0x597300 sub_597300 —— 每帧 AI 主驱动（·0x5961B0 同构）
// 大状态分发一致（14 → ·0x597120、15 → sub_5943F0、8 → 攻击段 this+7028 推进）；
// 差异：攻击段 2 与 4 均走 sub_5985E0(400) 延时路径；sub_4AECE0 段号映射为
// 1/2 → 6、3/4 → 2；8600/8601/8602 三门时序同 ·0x5961B0
// ------------------------------------------------------------
void /*usercall*/ sub_597300(int pArg1@<ecx>, int nArg2@<ebx>)  // 实现：每帧 AI 主驱动（·0x5961B0 同构）
{
  int v3; // edi
  double v4; // st7
  int v5; // ebx
  int *v6; // ecx

  sub_4E1780((uint32_t *)pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( *(uint32_t *)(pArg1 + 6556) != 8 )  // pArg1+6556〔大状态ID〕
  {
    if ( *(uint32_t *)(pArg1 + 6556) == 14 )  // pArg1+6556〔大状态ID〕
    {
      sub_597120((uint32_t *)pArg1, nArg2);  // 撕咬连击推进（·0x595E50 同构，计数 2153/上限 2154）
    }
    else if ( *(uint32_t *)(pArg1 + 6556) == 15 )  // pArg1+6556〔大状态ID〕
    {
      sub_5943F0((uint32_t *)pArg1);  // 施法段推进辅助（动画状态4门控：音效起播 + 帧时刻对齐 + 收态）
    }
    return;
  }
  v3 = pArg1 + 7028;
  if ( sub_41A5E0(pArg1 + 7028) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 3 && *(uint8_t *)(pArg1 + 8600) == 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 352))(pArg1);  // 调虚槽 +352：命中列表双链表清空
    *(uint8_t *)(pArg1 + 8600) = 1;  // pArg1+8600〔uAI8600(推断)〕
  }
  if ( sub_41A5E0(pArg1 + 7028) == 1  // crypt4byte 解密校验（·0x41A590 逆运算）
    || sub_41A5E0(pArg1 + 7028) == 2  // crypt4byte 解密校验（·0x41A590 逆运算）
    || sub_41A5E0(pArg1 + 7028) == 3  // crypt4byte 解密校验（·0x41A590 逆运算）
    || sub_41A5E0(pArg1 + 7028) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) == 0 )  // 调虚槽 +308：是否本地玩家
    {
LABEL_30:  // 标签 LABEL_30（跳转合流点）
      if ( *(uint8_t *)(pArg1 + 8601) != 0 && *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )  // 复合条件判定（与/或）
      {
        v5 = 0;
        if ( sub_41A5E0(pArg1 + 7028) == 1 || sub_41A5E0(pArg1 + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          v5 = 6;
        }
        else if ( sub_41A5E0(pArg1 + 7028) == 3 || sub_41A5E0(pArg1 + 7028) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          v5 = 2;
        }
        sub_4AECE0(*(void **)(pArg1 + 120), v5);  // 调 切武器动画
        *(uint8_t *)(pArg1 + 8602) = 1;  // pArg1+8602〔bAI8602(推断)〕
      }
      goto LABEL_40;
    }
    if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1 )  // pArg1+120〔pAnimObj〕
    {
      if ( *(uint8_t *)(pArg1 + 8601) != 0 )  // pArg1+8601〔bAI8601(推断)〕
      {
LABEL_27:  // 标签 LABEL_27（跳转合流点）
        if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )  // 复合条件判定（与/或）
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
            pArg1,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 896))(pArg1, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
        }
        goto LABEL_30;
      }
      if ( sub_41A5E0(pArg1 + 7028) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        sub_596030((uint32_t *)pArg1, nArg2, v3, 1000);  // 朝目标突进的速率设定
        sub_4A0550(120);  // 调 镜头幅度
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 2 || sub_41A5E0(pArg1 + 7028) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        v4 = (double)sub_5985E0(400.0);  // 朝目标突进：施加速率并返回所需时长
        if ( v4 < 300.0 )
          v4 = 300.0;
        sub_4A05C0((uint64_t)(v4 * 0.5));
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        sub_596030((uint32_t *)pArg1, nArg2, v3, 1000);  // 朝目标突进的速率设定
        sub_4A0550(90);  // 调 镜头幅度
      }
    }
    if ( *(uint8_t *)(pArg1 + 8601) == 0 )  // pArg1+8601〔bAI8601(推断)〕
    {
LABEL_40:  // 标签 LABEL_40（跳转合流点）
      if ( *(float *)(*(uint32_t *)(pArg1 + 112) + 24) > 0.0 && *(uint8_t *)(pArg1 + 8601) == 0 )  // 复合条件判定（与/或）
      {
        v6 = *(int **)(pArg1 + 120);  // pArg1+120〔pAnimObj〕
        if ( v6[37] < 1 )
          sub_4AECE0(v6, 1);  // 调 切武器动画
        *(uint8_t *)(pArg1 + 8601) = 1;  // pArg1+8601〔bAI8601(推断)〕
      }
      return;
    }
    goto LABEL_27;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x597570 sub_597570 —— HOLD 持续期拖拽跟随修正
// 对象==this+8604 且自身 vt+840==14 且剩余次数 this+8616>1 时：sub_491C10 取
// *(this+6216) 帧数，this+8620 计满 5×帧数/1000 → 次数-1；vt+916 更新目标后按其
// 坐标差 vt+112 反向修正自身位置【推断：叼住目标时的位移跟随】
// ------------------------------------------------------------
int /*thiscall*/ sub_597570(uint32_t *this, int nArg2)  // 实现：HOLD 持续期拖拽跟随修正
{
  int result; // eax
  int fld_e1554; // eax | =+0x1848 字段 x15（证据 005EA970）
  int fld_e2155; // edx | =+0x21AC 字段 x1（证据 005AF910）
  int fld_e2151; // edi | =+0x219C 字段 x1（证据 0059A020）
  int fld_e21512; // eax  | +0x219C → 子类槽〔594F90 复位〕（CNBlackLugaru；va=00594F90）
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = nArg2;
  if ( nArg2 == *(this + 2151) )  // this+8604〔bAI8604(推断)〕
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result == 14 && (int)*(this + 2154) > 1 )  // 若 result == 14
    {
      fld_e1554 = sub_491C10(*(uint32_t *)*(this + 1554));  // 遍历帧数组（首+44/尾+48，步长 88）
      fld_e2155 = *(this + 2155) + 1;  // this+8620〔uAI8620(推断)〕
      *(this + 2155) = fld_e2155;  // this+8620〔uAI8620(推断)〕
      if ( fld_e2155 >= 5 * fld_e1554 / 1000 )
      {
        --*(this + 2154);  // this+8616〔uAI8616(推断)〕
        *(this + 2155) = 0;  // this+8620〔uAI8620(推断)〕
      }
      fld_e2151 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 120))(*(this + 2151));  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 916))(*(this + 2151));  // this+8604〔bAI8604(推断)〕
      fld_e21512 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 120))(*(this + 2151));  // 调虚槽 +120：动画对象
      v8 = *this;
      v9 = fld_e2151 - fld_e21512;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v10);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v11);  // 调虚槽 +120：动画对象
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(v8 + 112))(this, v12 - v9);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
  }
  return result;
}



// 蓄力技能：vt+212 "HOLD"（104L）
// ------------------------------------------------------------
// 0x597640 sub_597640 —— HOLD 蓄力入场：抓取目标（·0x596650 同构，上限槽 2154）
// 目标解析（sub_45EBE0、类型 17、vt+128<=0）入 this+8604、坐标缓存 this+8624..8632、
// ±30 吸附 vt+112、vt+848(目标,1) 绑定；表现复位组（vt+196/vt+876×2/vt+888(0,2,1000,1000)/
// vt+896(4,4)/vt+344）一致；连击上限写 this+8616（计数 this+8612/this+8620 清零）；
// sub_4DB200(24, 0/1) 喊话 + vt+212 播 HOLD
// ------------------------------------------------------------
int /*thiscall*/ sub_597640(int *this, int pArg2)  // 实现：HOLD 蓄力入场：抓取目标（·0x596650 同构，上限槽 2154）
{
  int pTarget; // eax
  int pTarget2; // edi
  int fld_e2151; // ecx | =+0x219C 字段 x1（证据 0059A020）
  int nGrabX; // eax
  int fld_e21512; // ecx
  int nGrabY; // eax
  int fld_e21513; // ecx
  int nGrabZ; // eax
  int nVt1; // edx
  int nFacing; // eax
  int fld_e21514; // ecx
  int nSnapX; // eax
  int nVt2; // ebx
  int fld_e21515; // edi
  int nTgtVt; // edx
  int nTgtZ; // eax
  int nTgtY; // eax
  uint32_t *fld_e28; // edi
  int nAx1; // eax
  int fld_e1821; // edi
  uint32_t *pAtkBox3; // eax
  int nRand; // eax
  float fAx0; // [esp+70h] [ebp-24h]
  float fAx1; // [esp+74h] [ebp-20h]
  int nVoiceIdx; // [esp+8Ch] [ebp-8h]
  int fld_e215152; // [esp+90h] [ebp-4h]
  int nSnapXAdj; // [esp+9Ch] [ebp+8h]
  int nAx1Tmp; // [esp+9Ch] [ebp+8h]

  pTarget = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));  // pTarget = 调 sub_45EBE0 返回值
  pTarget2 = pTarget;
  if ( pTarget == 0  // 若 pTarget 为 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pTarget + 40))(pTarget, 17) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || (*(this + 2151) = pTarget2, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 128))(pTarget2) > 0) )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  {
    *(this + 2151) = 0;  // this+8604〔bAI8604(推断)〕
  }
  fld_e2151 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
  if ( fld_e2151 != 0 )  // 若 fld_e2151 非 0
  {
    nGrabX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2151 + 120))(fld_e2151);  // 调虚槽 +120：动画对象
    fld_e21512 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    *(this + 2156) = nGrabX;  // this+8624〔uAI8624(推断)〕
    nGrabY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21512 + 124))(fld_e21512);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    fld_e21513 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    *(this + 2157) = nGrabY;  // this+8628〔nPoolTime(推断)〕
    nGrabZ = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21513 + 128))(fld_e21513);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    nVt1 = *this;
    *(this + 2158) = nGrabZ;  // this+8632〔bDevourFlag(推断)〕
    nFacing = (*(int (/*thiscall*/ **)(int *))(nVt1 + 152))(this);  // 调虚槽 +152：效果通道 3
    fld_e21514 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    if ( nFacing != 0 )  // 若 nFacing 非 0
      nSnapX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) - 30;  // 调虚槽 +120：动画对象
    else  // 否则分支
      nSnapX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) + 30;  // 调虚槽 +120：动画对象
    nVt2 = *this;
    nSnapXAdj = nSnapX;
    fld_e21515 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    nTgtVt = *(uint32_t *)fld_e21515;
    fld_e215152 = fld_e21515;
    nTgtZ = (*(int (/*thiscall*/ **)(int))(nTgtVt + 128))(fld_e21515);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
    nTgtY = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21515 + 124))(fld_e21515, nTgtZ + 40);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    (*(void (/*thiscall*/ **)(int *, int, int))(nVt2 + 112))(this, nSnapXAdj, nTgtY + 1);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2151) + 848))(*(this + 2151), 1);  // 调虚槽 +848：冻结标志写入（+6744，0→-1 / 非0→0）
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));  // 调虚槽 +344：取坐标三元组
  fld_e28 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0  // 调虚槽 +308：是否本地玩家
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  fld_e215152 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  nAx1 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  fld_e1821 = *(this + 1821) - *(this + 1820);
  nAx1Tmp = nAx1;
  pAtkBox3 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  fAx1 = (float)nAx1Tmp;
  fAx0 = (float)fld_e215152;
  *(this + 2154) = (uint64_t)sub_4049C0(fAx0, fAx1, *pAtkBox3 - *(this + 1820), fld_e1821);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
  *(this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
  *(this + 2155) = 0;  // this+8620〔uAI8620(推断)〕
  nVoiceIdx = 0;
  fld_e215152 = 1;
  nRand = rand() % 2;  // nRand = 调 rand
  sub_4DB200(24, *(&nVoiceIdx + nRand));  // 15% 概率随机文案触发（0x4DB130 的门包装）
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
}



// AI 字段访问（this+8602）
// ------------------------------------------------------------
// 0x597890 sub_597890 —— 大状态 15 入场处理（·0x595C40 同构）
// vt+136/vt+132 移动校验失败且附属存在 → 瞬移对齐其位置；表现复位组
// （vt+876 0=200/200、1=0；vt+888(0,0,1000,1000)；vt+152(4) 经 sub_432E50 → vt+896 装载）、
// sub_495890(2,0)+sub_4A0550(10)、清 this+8602 全部一致
// ------------------------------------------------------------
int /*thiscall*/ sub_597890(uint32_t *this)  // 实现：大状态 15 入场处理（·0x595C40 同构）
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int fld_e2151; // eax | =+0x219C 字段 x1（证据 0059A020）
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
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v3);  // 调虚槽 +120：动画对象
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v2 + 136))(this, v4) == 0  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
    || (v5 = *this,
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this),  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v5 + 132))(this, v6) == 0) )  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉…
  {
    fld_e2151 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    if ( fld_e2151 != 0 )  // 若 fld_e2151 非 0
    {
      fld_e21512 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
      v9 = *this;
      v10 = (*(int (**)(void))(*(uint32_t *)fld_e2151 + 128))();  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21512 + 124))(fld_e21512, v10 + 40);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21512 + 120))(fld_e21512, v11);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 112))(this, v12);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 200, 200, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  v13 = *this;
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);  // 调虚槽 +152：效果通道 3
  v15 = sub_432E50(v14);  // 关系码对调映射
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v13 + 896))(this, v15);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  sub_495890(2, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  result = sub_4A0550(10);  // result = 调 sub_4A0550 返回值
  *((uint8_t *)this + 8602) = 0;  // this+8602〔bAI8602(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5979B0 sub_5979B0 —— 强化参数撤销（·0x597AB0 的逆操作）
// nArg3==0：状态块 +830 −0.3（sub_41A5E0/sub_41A590）+vt+676 收尾；nArg2==0 时速度槽
// *(this+7620)+132 ×0.769（nArg3==2 时另 vt+672 置 0.3333f + sub_4E99C0 防篡减法）；
// nArg2==1 → +68 ×0.769
// ------------------------------------------------------------
int /*thiscall*/ sub_5979B0(uint32_t *this, int nArg2, int nArg3)  // 实现：强化参数撤销（·0x597AB0 的逆操作）
{
  int result; // eax
  unsigned int v5; // edi
  int v6; // edx
  float v7; // [esp+0h] [ebp-4h]
  int v8; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 != 2 )  // 若 nArg3 != 2
      return result;
    result = nArg2;
    if ( nArg2 == 0 )  // 若 nArg2 为 0
    {
      *(float *)(*(this + 1905) + 132) = *(float *)(*(this + 1905) + 132) * 0.76923078;  // this+7620〔pStatusPanel(推断)〕
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 672))(this, 0, 1050253722);  // 调虚槽 +672：自身 HP
      sub_4E99C0(v7);  // 防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    }
  }
  else  // 否则分支
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v5, v6, v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    result = nArg2;
    if ( nArg2 == 0 )  // 若 nArg2 为 0
    {
      *(float *)(*(this + 1905) + 132) = *(float *)(*(this + 1905) + 132) * 0.76923078;  // this+7620〔pStatusPanel(推断)〕
      return result;
    }
  }
  if ( --result == 0 )
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.76923078;  // this+7620〔pStatusPanel(推断)〕
  return result;
}



// AI 相位辅助（101L）
// ------------------------------------------------------------
// 0x597AB0 sub_597AB0 —— 强化施加（Penril 变种，·0x5979B0 逆操作）
// 先清 this+7531..7555 与 this+7564..7596 子类字段；nArg3==0：状态块 +830 +0.3 + vt+676，
// nArg2==0 → this+7568=1、this+7596=50、速度槽 *(this+7620)+132 ×1.3，nArg2 1/2 →
// this+7564=1（nArg2==1 再 +68 ×1.3）；nArg3==2：nArg2==0 → this+7568=1、this+7596=50、
// +132 ×1.3、vt+672 置 0.3333f、sub_4AED60，nArg2 1/2 → this+7568=1（nArg2==1 +68 ×1.3）
// ------------------------------------------------------------
int /*thiscall*/ sub_597AB0(uint32_t *this, int nArg2, int nArg3)  // 实现：强化施加（Penril 变种，·0x5979B0 逆操作）
{
  char *pThis_1D73; // ecx
  int result; // eax
  int fld_e1905; // eax | =+0x1DC4 字段 x1（证据 0059A020）
  unsigned int v7; // edi
  int v8; // edx
  float v9; // [esp+0h] [ebp-8h]
  int v10; // [esp+14h] [ebp+Ch]

  *((uint8_t *)this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *((uint8_t *)this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *((uint8_t *)this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *((uint8_t *)this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *((uint8_t *)this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *((uint8_t *)this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *((uint8_t *)this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)((char *)this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  pThis_1D73 = (char *)this + 7539;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *(this + 1893) = 0;  // this+7572〔uGrade7572(推断)〕
  *(this + 1892) = 0;  // this+7568〔uEnable7568(推断)〕
  *(this + 1891) = 0;  // this+7564〔uForm7564(推断)〕
  *(this + 1897) = 0;  // this+7588〔uForm7588〕
  *(this + 1896) = 0;  // this+7584〔uForm7584〕
  *(this + 1895) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(this + 1894) = 0;  // this+7576〔uPhase7576(推断)〕
  *(this + 1899) = 0;  // this+7596〔nOffset7596(推断)〕
  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )  // 若 nArg3 == 2
    {
      if ( nArg2 != 0 )  // 若 nArg2 非 0
      {
        result = nArg2 - 1;
        if ( nArg2 == 1 )  // 若 nArg2 == 1
        {
          *(this + 1892) = 1;  // this+7568〔uEnable7568(推断)〕
          *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 1.3;  // this+7620〔pStatusPanel(推断)〕
        }
        else  // 否则分支
        {
          result = nArg2 - 2;
          if ( nArg2 == 2 )  // 若 nArg2 == 2
            *(this + 1892) = 1;  // this+7568〔uEnable7568(推断)〕
        }
      }
      else  // 否则分支
      {
        fld_e1905 = *(this + 1905) + 128;  // this+7620〔pStatusPanel(推断)〕
        *(this + 1892) = 1;  // this+7568〔uEnable7568(推断)〕
        *(this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
        *(float *)(fld_e1905 + 4) = *(float *)(fld_e1905 + 4) * 1.3;
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 672))(this, 0, 1050253722);  // 调虚槽 +672：自身 HP
        sub_4AED60(v9);
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
      }
    }
  }
  else  // 否则分支
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v7, v8, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    result = nArg2;
    if ( nArg2 != 0 )  // 若 nArg2 非 0
    {
      result = nArg2 - 1;
      if ( nArg2 == 1 )  // 若 nArg2 == 1
      {
        *(this + 1891) = 1;  // this+7564〔uForm7564(推断)〕
        *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 1.3;  // this+7620〔pStatusPanel(推断)〕
      }
      else  // 否则分支
      {
        result = nArg2 - 2;
        if ( nArg2 == 2 )  // 若 nArg2 == 2
          *(this + 1891) = 1;  // this+7564〔uForm7564(推断)〕
      }
    }
    else  // 否则分支
    {
      *(this + 1892) = 1;  // this+7568〔uEnable7568(推断)〕
      *(this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
      *(float *)(*(this + 1905) + 132) = *(float *)(*(this + 1905) + 132) * 1.3;  // this+7620〔pStatusPanel(推断)〕
    }
  }
  return result;
}



// 登场曲：sub_406D60 写 "B_PENRIL_01"（Penril 曲目槽）+ sub_699000 时钟门
// ------------------------------------------------------------
// 0x597CA0 sub_597CA0 —— Penril 相位机：登场曲+时钟门（·0x5955B0 同构扩展）
// 相位 this+1787：0 → vt+1284 出场，困难级（this+1943==3）经 sub_406D60 播 B_PENRIL_01；
// 4 无宿主 → 切 13；13/14/15 有宿主 → 切回 4；新增相位 21 = 定时待机：
// sub_699000(this+36 冻结感知时钟) − this+7704 > 1000ms 才切 13
// ------------------------------------------------------------
int /*thiscall*/ sub_597CA0(int *this)  // 实现：Penril 相位机：登场曲+时钟门（·0x5955B0 同构扩展）
{
  int result; // eax

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调虚槽 +1284
      if ( *(this + 1943) == 3 )  // this+7772〔nCounterState〕
        result = sub_406D60("B_PENRIL_01");  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result == 0 )  // 若 result 为 0
        goto LABEL_5;
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 21:  // case 21 = ENUM_CMDPACKET_SORT_ITEM
      result = sub_699000((int)(this + 9)) - *(this + 1926);  // 【clock_now(clk)】
      if ( result > 1000 )  // 若 result > 1000
LABEL_5:  // 标签 LABEL_5（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x597D70 sub_597D70 —— 受击钩子：架招反应触发（·0x595650 同构）
// 差异：攻击段号 this+7028 接受 3 或 4；其余门与 vt+560 setState 14（架招【推断】）
// + sub_4DB480 尾调一致
// ------------------------------------------------------------
int /*thiscall*/ sub_597D70(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：受击钩子：架招反应触发（·0x595650 同构）
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8  // this+6556〔大状态ID〕
    && (uint8_t)nArg4 == 0
    && (sub_41A5E0((unsigned int)(this + 1757)) == 3 || sub_41A5E0((unsigned int)(this + 1757)) == 4)  // crypt4byte 解密校验（·0x41A590 逆运算）
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 948))(pObj) != 0  // 调虚槽 +948
    && *(this + 154) != 14 )  // this+616〔nReactionState〕
  {
    memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
    v6 = *(uint32_t *)pObj;
    v9 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(v6 + 48))(pObj);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    v9 = -1;
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
  return sub_4DB480(pObj, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 参数打包 AI（89L）
// ------------------------------------------------------------
// 0x597E80 sub_597E80 —— 拆除/回收附属对象（·0x595820 同构）
// 对 this+8604 附属：vt+604/vt+612 停止隐藏，坐标对齐三态回退（vt+136 直传
// this+8624..8632 → vt+140 碰撞修正 → 自身坐标）；存活时打包 {4,0,1,200,200}
// 走 vt+560 setState 4 + vt+564；末尾 vt+848(0) 解绑并清 this+8604
// ------------------------------------------------------------
void /*usercall*/ sub_597E80(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 实现：拆除/回收附属对象（·0x595820 同构）
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

  pObj3 = pDwArg1[2151];  // pObj3 = 取 pDwArg1[2151]
  if ( pObj3 != 0 )  // 若 pObj3 非 0
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 612))(pDwArg1[2151], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 136))(  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
           pDwArg1[2151],
           pDwArg1[2156],
           pDwArg1[2157],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2151] + 112))(pDwArg1[2151], pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
    else  // 否则分支
    {
      pObj = pDwArg1[2151];  // pObj = 取 pDwArg1[2151]
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);  // 调虚槽 +120：动画对象
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2156, pDwArg1 + 2157, v7);  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
      pObj2 = pDwArg1[2151];  // pObj2 = 取 pDwArg1[2151]
      if ( v8 != 0 )  // 若 v8 非 0
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
      else  // 否则分支
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2158]);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2151], v12);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 308))(pDwArg1[2151]) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      Block = nullptr;  // Block = 空指针
      v15 = 0;
      v16 = 0;
      v18 = 0;
      pObj4 = 4;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 0;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 1;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 560))(pDwArg1[2151], 4, v13, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 564))(pDwArg1[2151]);
      v18 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
      Block = nullptr;  // Block = 空指针
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 848))(pDwArg1[2151], 0);  // 调虚槽 +848：冻结标志写入（+6744，0→-1 / 非0→0）
    pDwArg1[2151] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x598080 sub_598080 —— 死亡/移除通知分发（·0x596F90 同构）
// 消亡对象为附属 this+8604（自身态 14 时 ·0x597E80 拆除+清槽）或自身（拆后 vt+216 播 33）；
// 尾调 sub_4D9170
// ------------------------------------------------------------
int /*userpurge*/ sub_598080@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)  // 实现：死亡/移除通知分发（·0x596F90 同构）
{
  if ( pDwArg3 == (int *)pDwArg1[2151] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
      sub_597E80(pDwArg1, nArg2);  // 拆除/回收附属对象（·0x595820 同构）
    pDwArg1[2151] = 0;
  }
  if ( pDwArg3 == pDwArg1 )  // 若 pDwArg3 == pDwArg1
  {
    if ( pDwArg1[2151] != 0 )
    {
      sub_597E80(pDwArg1, nArg2);  // 拆除/回收附属对象（·0x595820 同构）
      pDwArg1[2151] = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);  // 调虚槽 +216：音效 TAG 查询
  }
  return sub_4D9170(pDwArg3);  // 返回 调 sub_4D9170 返回值
}



// 攻击 AI：vt+212 播报 FOX_ATK（58L）
// ------------------------------------------------------------
// 0x5980F0 sub_5980F0 —— 大状态切换分发器（·0x597000 同构+起手演出扩展）
// 旧态 15 → vt+216 播 33、旧态 14 → ·0x597E80 拆附属；新态 8 → 清演出门+vt+212 播
// FOX_ATK、14 → ·0x597640 HOLD、15 → ·0x597890；sub_4E33D0 收尾后追加：新态 8 且
// 攻击段 this+7028==0 时额外下发 vt+876(0,700,700,0,-2000,1)、vt+888(2,2,1000,1000)、
// vt+152(4) → vt+896 装载【推断：突进类起手演出参数】
// ------------------------------------------------------------
int /*userpurge*/ sub_5980F0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, int nArg4, int nArg5, int nArg6)  // 实现：大状态切换分发器（·0x597000 同构+起手演出扩展）
{
  int v7; // eax
  int v8; // edx
  int result; // eax
  int v10; // edi
  int v11; // eax

  v7 = pDwArg1[1639];  // v7 = 取 pDwArg1[1639]
  if ( v7 == 15 )  // 若 v7 == 15
  {
    if ( ArgList != 15 )  // 若 ArgList != 15
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);  // 调虚槽 +216：音效 TAG 查询
  }
  else if ( v7 == 14 )
  {
    sub_597E80(pDwArg1, nArg2);  // 拆除/回收附属对象（·0x595820 同构）
  }
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      v8 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8600) = 0;
      *((uint8_t *)pDwArg1 + 8601) = 0;
      *((uint8_t *)pDwArg1 + 8602) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(pDwArg1, "FOX_ATK", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      break;  // 跳出循环/分支
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      sub_597640(pDwArg1, nArg4);  // HOLD 蓄力入场：抓取目标（·0x596650 同构，上限槽 2154）
      break;  // 跳出循环/分支
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      sub_597890(pDwArg1);  // 大状态 15 入场处理（·0x595C40 同构）
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  result = sub_4E33D0(ArgList, *(float *)&nArg4, nArg5, nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 8 )  // 若 ArgList == 8
  {
    result = sub_41A5E0((unsigned int)(pDwArg1 + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 0 )  // 若 result 为 0
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*pDwArg1 + 876))(pDwArg1, 0, 700, 700, 0, -2000, 1);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*pDwArg1 + 888))(pDwArg1, 2, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
      v10 = *pDwArg1;
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);  // 调虚槽 +152：效果通道 3
      return (*(int (/*thiscall*/ **)(int *, int))(v10 + 896))(pDwArg1, v11);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
    }
  }
  return result;
}



// 狐狸资源装载：R_FOX_TALK/DMG + FOX_DIE 语音 + Monster/Lugaru/Teeth.equ（46L）
// ------------------------------------------------------------
// 0x598200 sub_598200 —— 牙齿装备型狐狸资源装载（出厂初始化）
// 写 this+6792..6808 参数槽 + 注册 R_FOX_TALK/R_FOX_DMG/FOX_DIE 语音；
// new 0x544 经 sub_4BA9E0 装载 Monster/Lugaru/Teeth.equ 后 vt+784 挂载（vt+4(obj,1) 激活）；
// 连击上限 this+8608 = vt+384(0)/(1) 经 sub_4049C0 时间窗插值；this+648 |= 2 位标志
// ------------------------------------------------------------
int /*thiscall*/ sub_598200(uint32_t *this)  // 实现：牙齿装备型狐狸资源装载（出厂初始化）
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

  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_FOX_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_FOX_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("FOX_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Lugaru/Teeth.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v3 = nullptr;  // v3 = 空指针
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v9 = (float)v11;
  v8 = (float)(int)Block;
  *(this + 2152) = (uint64_t)sub_4049C0(v8, v9, *v6 - *(this + 1820), fld_e1821);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
  result = *(this + 162) | 2;  // this+648〔uMonFlagBits〕
  *(this + 162) = result;  // this+648〔uMonFlagBits〕
  return result;
}



// 子类扩展字段复位（this+8600..8624）
// ------------------------------------------------------------
// 0x598350 sub_598350 —— 子类 AI 区清零
// —— 清 this+8600..8604 + 8624..8632（较 ·0x595E10 少 8608 与 8636）
// ------------------------------------------------------------
int /*thiscall*/ sub_598350(int this)  // 实现：子类 AI 区清零
{
  uint32_t *pThis_21B0; // ecx

  *(uint8_t *)(this + 8600) = 0;  // this+8600〔uAI8600(推断)〕
  *(uint8_t *)(this + 8601) = 0;  // this+8601〔bAI8601(推断)〕
  *(uint8_t *)(this + 8602) = 0;  // this+8602〔bAI8602(推断)〕
  *(uint32_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  pThis_21B0 = (uint32_t *)(this + 8624);  // this+8624〔uAI8624(推断)〕
  *pThis_21B0 = 0;
  pThis_21B0[1] = 0;
  pThis_21B0[2] = 0;
  return 0;
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x598380 sub_598380 —— 相位机（·0x597CA0 去登场曲版）
// 相位 this+1787：0 → vt+1284；4 无宿主 → 13；13/14/15 有宿主 → 4；
// 21 → sub_699000(this+36 时钟) − this+7704 > 1000ms 切 13
// ------------------------------------------------------------
int /*thiscall*/ sub_598380(int *this)  // 实现：相位机（·0x597CA0 去登场曲版）
{
  int result; // eax

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调虚槽 +1284
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result == 0 )  // 若 result 为 0
        goto LABEL_4;
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 21:  // case 21 = ENUM_CMDPACKET_SORT_ITEM
      result = sub_699000((int)(this + 9)) - *(this + 1926);  // 【clock_now(clk)】
      if ( result > 1000 )  // 若 result > 1000
LABEL_4:  // 标签 LABEL_4（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// AI 相位辅助（81L）
// ------------------------------------------------------------
// 0x598440 sub_598440 —— 朝目标突进的速率设定（·0x596030 同构+系数可选）
// 目标槽 this+7252 存在时：X/Y 距差 ×（pszArg5 非零 ? 1.6 : 1.2），clamp ±200/±100 后
// 按 nArg4 时长换算写 vt+876 双轴速率槽，vt+896(this, X<0, 2/3 按 Y 符号) 翻转朝向；
// ·0x598BA0 攻击段 1/3 分别以系数 0/1 调用
// ------------------------------------------------------------
int /*userpurge*/ sub_598440@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4, char pszArg5)  // 实现：朝目标突进的速率设定（·0x596030 同构+系数可选）
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

  result = pArg1[1813];  // result = 取 pArg1[1813]
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v8 = pszArg5 == 0;
    v22 = 1.6;
    if ( v8 )
      v22 = 1.2;
    v9 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[1813] + 120))(pArg1[1813], nArg3, nArg2);  // 调虚槽 +120：动画对象
    v20 = 1.6;
    v23 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - v9) * v22;  // 调虚槽 +120：动画对象
    if ( pszArg5 == 0 )  // 若 pszArg5 为 0
      v20 = 1.2;
    v10 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813]);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
    v11 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1) - v10) * v20;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
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
    v21 = fabs(v23) / v16 * 1000.0;  // v21 = 调 fabs
    v19 = fabs(v11) / v16 * 1000.0;  // v19 = 调 fabs
    v17 = 3;
    if ( v11 >= 0.0 )
      v17 = 2;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      pArg1,
      0,
      (uint64_t)v21,
      (uint64_t)v21,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      pArg1,
      1,
      (uint64_t)v19,
      (uint64_t)v19,
      0,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t *, bool, int))(*pArg1 + 896))(pArg1, v23 < 0.0, v17);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  }
  return result;
}



// AI 相位辅助（79L）
// ------------------------------------------------------------
// 0x5985E0 sub_5985E0 —— 朝目标突进：施加速率并返回所需时长
// 目标槽 this+7252 存在时 X/Y 距差 ×1.2（clamp ±200/±100），总时长 =
// sqrt(x²+y²)/fArg4×1000，按 X/Y 占比分配写 vt+876 双轴速率槽 + vt+896 朝向；
// 返回总时长供调用方折半延时（·0x597300/·0x598BA0 段 2/4：sub_4A05C0(max(时长,300)×0.5)）
// ------------------------------------------------------------
int /*userpurge*/ sub_5985E0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, float fArg4)  // 实现：朝目标突进：施加速率并返回所需时长
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

  pObj = pArg1[1813];  // pObj = 取 pArg1[1813]
  if ( pObj != 0 )  // 若 pObj 非 0
  {
    v6 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 120))(pObj, nArg3, nArg2);  // 调虚槽 +120：动画对象
    v19 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - v6) * 1.2;  // 调虚槽 +120：动画对象
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813]);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
    v8 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1) - v7) * 1.2;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
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
    v20 = sqrt(v8 * v8 + v19 * v19) / fArg4 * 1000.0;  // v20 = 调 sqrt
    v13 = 1.0 / v20;
    v18 = fabs(v19) * v13 * 1000.0;  // v18 = 调 fabs
    v17 = fabs(v8) * v13 * 1000.0;  // v17 = 调 fabs
    v14 = 3;
    if ( v8 >= 0.0 )
      v14 = 2;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      pArg1,
      0,
      (uint64_t)v18,
      (uint64_t)v18,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      pArg1,
      1,
      (uint64_t)v17,
      (uint64_t)v17,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, bool, int))(*pArg1 + 896))(pArg1, v19 < 0.0, v14);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
    return (uint64_t)v20;
  }
  else  // 否则分支
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
// 0x598790 sub_598790 —— 命中表现转发+粒子附加
// sub_4D8F90 转发默认处理后，nArg2!=1 且相位门 this+8636==1 时以 ±4 随机偏移调
// sub_491DE0 附加粒子（全局对象 dword_79C0B0，颜色参数 -16776961/-922746881）
// ------------------------------------------------------------
int /*thiscall*/ sub_598790(uint8_t *this, int nArg2, int nArg3, int nArg4, float fArg5)  // 实现：命中表现转发+粒子附加
{
  int result; // eax
  int dword_79C0B02; // [esp-20h] [ebp-2Ch]
  int nRand2; // [esp-1Ch] [ebp-28h]
  int nRand; // [esp-18h] [ebp-24h]

  result = sub_4D8F90(nArg2, nArg3, nArg4, LODWORD(fArg5));  // vmt144 转发垫片（IRDActiveObject__vmt144 族）
  if ( (uint8_t)nArg2 != 1 && *(this + 8636) == 1 )  // 复合条件判定（与/或）
  {
    nRand = rand() % 8 + nArg4 - 4;  // nRand = 调 rand
    nRand2 = rand() % 8 + nArg3 - 4;  // nRand2 = 调 rand
    dword_79C0B02 = dword_79C0B0;  // 默认字体/绘制资源
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);  // 调虚槽 +200：取动画对象
    return sub_491DE0(dword_79C0B02, nRand2, nRand, fArg5, 2, 1, -16776961, -922746881);  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
  }
  return result;
}



// AI 字段访问（this+8636）
// ------------------------------------------------------------
// 0x598820 sub_598820 —— 伤害类型过滤钩子（this+8636 门）
// —— 相位门 this+8636==1 时直接返回 1 吞掉默认处理，否则转发 sub_4DC390
// ------------------------------------------------------------
int /*thiscall*/ sub_598820(uint8_t *this, int nArg2, int nArg3)  // 实现：伤害类型过滤钩子（this+8636 门）
{
  int result; // eax

  result = 1;
  if ( *(this + 8636) != 1 )  // this+8636〔相位门〕
    return sub_4DC390(nArg2, nArg3);  // 伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
  return result;
}



// 蓄力技能：vt+212 "HOLD"（144L；this+8636 相位门）
// ------------------------------------------------------------
// 0x598840 sub_598840 —— HOLD 蓄力入场：抓取目标（·0x596650 同构+成长加成首入段）
// 首入（this+8636==0）先对状态块 +830/+858/+102/+158 各 += *(this+8680) 浮点
// 【推断：成长值/难度系数】、vt+676 收尾、置 this+8636=1；随后同族流程：目标
// （类型 17、vt+128<=0）入 this+8604、坐标缓存 this+8624..8632、±30 吸附 vt+112、
// vt+848(目标,1)、表现复位组（vt+196/vt+876×2/vt+888/vt+896/vt+344）、
// 连击上限 this+8616 插值、sub_4DB200(24, 0/1) 喊话 + vt+212 播 HOLD
// ------------------------------------------------------------
int /*thiscall*/ sub_598840(int *this, int pArg2)  // 实现：HOLD 蓄力入场：抓取目标（·0x596650 同构+成长加成首入段）
{
  int pTarget; // eax
  int pTarget2; // edi
  int nVt1; // edx
  unsigned int uMulAddr830; // edi
  int v7; // edx
  int nVt2; // edx
  unsigned int uMulAddr858; // edi
  int v10; // edx
  int nVt3; // edx
  unsigned int uMulAddr102; // edi
  int v13; // edx
  int nVt4; // edx
  unsigned int uMulAddr158; // edi
  int v16; // edx
  int fld_e2151; // ecx | =+0x219C 字段 x1（证据 0059A020）
  int nGrabX; // eax
  int fld_e21512; // ecx
  int nGrabY; // eax
  int fld_e21513; // ecx
  int nGrabZ; // eax
  int nVt5; // edx
  int nFacing; // eax
  int fld_e21514; // ecx
  int nSnapX; // eax
  int nVt6; // ebx
  int fld_e21515; // edi
  int nTgtVt; // edx
  int nTgtZ; // eax
  int nTgtY; // eax
  uint32_t *fld_e28; // edi
  int nAx1; // eax
  int fld_e1821; // edi
  uint32_t *pAtkBox3; // eax
  int nRand; // eax
  float fAx0; // [esp+84h] [ebp-24h]
  float fAx1; // [esp+88h] [ebp-20h]
  int nVoiceIdx; // [esp+A0h] [ebp-8h]
  int fld_e2170; // [esp+A4h] [ebp-4h] | =+0x21E8 字段 x6（证据 005CDA80）
  int fMul830; // [esp+B0h] [ebp+8h]
  int fMul858; // [esp+B0h] [ebp+8h]
  int fMul102; // [esp+B0h] [ebp+8h]
  int fMul158; // [esp+B0h] [ebp+8h]
  int nSnapXAdj; // [esp+B0h] [ebp+8h]
  int nAx1Tmp; // [esp+B0h] [ebp+8h]

  pTarget = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));  // 事件包解对象句柄
  pTarget2 = pTarget;
  if ( pTarget == 0  // 若 pTarget 为 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pTarget + 40))(pTarget, 17) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || (*(this + 2151) = pTarget2, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 128))(pTarget2) > 0) )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  {
    *(this + 2151) = 0;  // 非玩家型(vt+40!=17)或已浮空(vt+128>0)则清抓取槽（=字节 8604）
  }
  if ( *((uint8_t *)this + 8636) == 0 )  // 首入一次性段：成长加成
  {
    nVt1 = *this;
    fld_e2170 = *(this + 2170);  // 成长值【推断：难度/等级系数】
    uMulAddr830 = (*(int (/*thiscall*/ **)(int *, uint32_t))(nVt1 + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&fMul830 = COERCE_FLOAT(sub_41A5E0(uMulAddr830)) + *(float *)&fld_e2170;  // +830 倍率 += 成长值
    sub_41A590(uMulAddr830, v7, fMul830);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    nVt2 = *this;
    fld_e2170 = *(this + 2170);  // this+8680〔uGate8680(推断)〕
    uMulAddr858 = (*(int (/*thiscall*/ **)(int *, uint32_t))(nVt2 + 672))(this, 0) + 858;  // 调虚槽 +672：自身 HP
    *(float *)&fMul858 = COERCE_FLOAT(sub_41A5E0(uMulAddr858)) + *(float *)&fld_e2170;  // +858 倍率 += 成长值
    sub_41A590(uMulAddr858, v10, fMul858);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    nVt3 = *this;
    fld_e2170 = *(this + 2170);  // this+8680〔uGate8680(推断)〕
    uMulAddr102 = (*(int (/*thiscall*/ **)(int *, uint32_t))(nVt3 + 672))(this, 0) + 102;  // 调虚槽 +672：自身 HP
    *(float *)&fMul102 = COERCE_FLOAT(sub_41A5E0(uMulAddr102)) + *(float *)&fld_e2170;  // +102 倍率 += 成长值
    sub_41A590(uMulAddr102, v13, fMul102);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    nVt4 = *this;
    fld_e2170 = *(this + 2170);  // this+8680〔uGate8680(推断)〕
    uMulAddr158 = (*(int (/*thiscall*/ **)(int *, uint32_t))(nVt4 + 672))(this, 0) + 158;  // 调虚槽 +672：自身 HP
    *(float *)&fMul158 = COERCE_FLOAT(sub_41A5E0(uMulAddr158)) + *(float *)&fld_e2170;  // +158 倍率 += 成长值
    sub_41A590(uMulAddr158, v16, fMul158);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    *((uint8_t *)this + 8636) = 1;  // 首入完成，后续再入不再加成长值
  }
  fld_e2151 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
  if ( fld_e2151 != 0 )  // 有被抓目标：缓存其坐标并把自身吸附到其身旁
  {
    nGrabX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2151 + 120))(fld_e2151);  // 调虚槽 +120：动画对象
    fld_e21512 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    *(this + 2156) = nGrabX;  // 缓存目标 X（字节 8624）
    nGrabY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21512 + 124))(fld_e21512);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    fld_e21513 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    *(this + 2157) = nGrabY;  // 缓存目标 Y（字节 8628）
    nGrabZ = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21513 + 128))(fld_e21513);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    nVt5 = *this;
    *(this + 2158) = nGrabZ;  // 缓存目标 Z（字节 8632）
    nFacing = (*(int (/*thiscall*/ **)(int *))(nVt5 + 152))(this);  // 调虚槽 +152：效果通道 3
    fld_e21514 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    if ( nFacing != 0 )  // 若 nFacing 非 0
      nSnapX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) - 30;  // 朝向→目标左侧 30
    else  // 否则分支
      nSnapX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) + 30;  // 背向→目标右侧 30
    nVt6 = *this;
    nSnapXAdj = nSnapX;
    fld_e21515 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
    nTgtVt = *(uint32_t *)fld_e21515;
    fld_e2170 = fld_e21515;
    nTgtZ = (*(int (/*thiscall*/ **)(int))(nTgtVt + 128))(fld_e21515);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
    nTgtY = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21515 + 124))(fld_e21515, nTgtZ + 40);  // 目标 Y 偏移 +40
    (*(void (/*thiscall*/ **)(int *, int, int))(nVt6 + 112))(this, nSnapXAdj, nTgtY + 1);  // 自身坐标吸附点
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2151) + 848))(*(this + 2151), 1);  // 目标 vt+848(1) 被擒表现
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));  // 设默认动作
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // vt+888 参数(2,1000,1000)
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));  // 调虚槽 +344：取坐标三元组
  fld_e28 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0  // 调虚槽 +308：是否本地玩家
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  *(float *)&fld_e2170 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 384))(this, 0));  // 动作轴0 当前值
  nAx1 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  fld_e1821 = *(this + 1821) - *(this + 1820);
  nAx1Tmp = nAx1;
  pAtkBox3 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  fAx1 = (float)nAx1Tmp;
  fAx0 = (float)fld_e2170;
  *(this + 2154) = (uint64_t)sub_4049C0(fAx0, fAx1, *pAtkBox3 - *(this + 1820), fld_e1821);  // 帧间插值: 连击上限（按动作轴在攻击盒值区间内归一）【推断】
  *(this + 2153) = 0;  // 连击计数（字节 8612）清零
  *(this + 2155) = 0;  // 相位计时（字节 8620）清零
  nVoiceIdx = 0;
  fld_e2170 = 1;  // nVoiceIdx 与 fld_e2170 构成栈上 {0,1} 对，随机取一作喊话参数
  nRand = rand() % 2;  // nRand = 调 rand
  sub_4DB200(24, *(&nVoiceIdx + nRand));  // 50% 随机喊话（24 号文案组）
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
}


// 大型 AI（161L；sub_699000 时钟门驱动）
// ------------------------------------------------------------
// 0x598BA0 sub_598BA0 —— 大型每帧 AI：攻击驱动+投石（牙齿装备型合体）
// 前半同 ·0x597300：大状态 14 → ·0x597120 撕咬、15 → sub_5943F0 施法、8 → 攻击段
// this+7028 推进（段 1/3 → ·0x598440 突进+sub_4A0550(120/90)、段 2/4 → sub_5985E0(400)
// 延时、段 0 → vt+352 起手+8600 门）；尾部投石：this+8636/8637 双门开且
// sub_699000(this+8652 时钟) >= this+8676 且 rand < this+8648 → 从全局 dword_8F82CC 取弹体
// （参数 30/50、随机 0..this+8644、vt+192×0.7；vt+40 定位自身坐标、vt+92 经 sub_4E77D0
// 打包后 vt+80(this,2,0,..) 发射 → sub_4600B0 落点）；清 8665/8666、sub_698F90 重置倒计时
// ------------------------------------------------------------
void /*usercall*/ sub_598BA0(int pArg1@<ecx>, int nArg2@<ebx>)  // 实现：大型每帧 AI：攻击驱动+投石（牙齿装备型合体）
{
  int nSegIdx; // edi
  double fStopTime; // st7
  int nStopCode; // ebx
  int *pActObj; // ecx
  int nThrowCd; // edi
  int pMissile; // edi
  int nMolVt; // edx
  uint32_t *pParams; // ebx
  int nRand; // et2
  uint64_t nSpeedPacked; // rax
  int nMolVt2; // ebx
  int nMolX; // eax
  int nPkt; // eax
  void *pPacket; // eax
  int nPosY; // [esp-Ch] [ebp-48h]
  int nPosZ; // [esp-8h] [ebp-44h]
  void *v19[4]; // [esp+Ch] [ebp-30h] BYREF
  void *pBuf[4]; // [esp+1Ch] [ebp-20h] BYREF
  int nScratch; // [esp+2Ch] [ebp-10h]
  int nFreeState; // [esp+38h] [ebp-4h]

  sub_4E1780((uint32_t *)pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( *(uint32_t *)(pArg1 + 6556) != 8 )  // pArg1+6556〔大状态ID〕
  {
    if ( *(uint32_t *)(pArg1 + 6556) == 14 )  // pArg1+6556〔大状态ID〕
    {
      sub_597120((uint32_t *)pArg1, nArg2);  // 撕咬连击推进（·0x595E50 同构，计数 2153/上限 2154）
    }
    else if ( *(uint32_t *)(pArg1 + 6556) == 15 )  // pArg1+6556〔大状态ID〕
    {
      sub_5943F0((uint32_t *)pArg1);  // 施法段推进辅助（动画状态4门控：音效起播 + 帧时刻对齐 + 收态）
    }
    goto LABEL_45;
  }
  nSegIdx = pArg1 + 7028;
  if ( sub_41A5E0(pArg1 + 7028) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 3 && *(uint8_t *)(pArg1 + 8600) == 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 352))(pArg1);  // 调虚槽 +352：命中列表双链表清空
    *(uint8_t *)(pArg1 + 8600) = 1;  // pArg1+8600〔uAI8600(推断)〕
  }
  if ( sub_41A5E0(pArg1 + 7028) == 1  // crypt4byte 解密校验（·0x41A590 逆运算）
    || sub_41A5E0(pArg1 + 7028) == 2  // crypt4byte 解密校验（·0x41A590 逆运算）
    || sub_41A5E0(pArg1 + 7028) == 3  // crypt4byte 解密校验（·0x41A590 逆运算）
    || sub_41A5E0(pArg1 + 7028) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) == 0 )  // 调虚槽 +308：是否本地玩家
    {
LABEL_30:  // 标签 LABEL_30（跳转合流点）
      if ( *(uint8_t *)(pArg1 + 8601) != 0 && *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )  // 复合条件判定（与/或）
      {
        nStopCode = 0;
        if ( sub_41A5E0(pArg1 + 7028) == 1 || sub_41A5E0(pArg1 + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          nStopCode = 6;
        }
        else if ( sub_41A5E0(pArg1 + 7028) == 3 || sub_41A5E0(pArg1 + 7028) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          nStopCode = 2;
        }
        sub_4AECE0(*(void **)(pArg1 + 120), nStopCode);  // 调 切武器动画
        *(uint8_t *)(pArg1 + 8602) = 1;  // pArg1+8602〔bAI8602(推断)〕
      }
      goto LABEL_40;
    }
    if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1 )  // pArg1+120〔pAnimObj〕
    {
      if ( *(uint8_t *)(pArg1 + 8601) != 0 )  // pArg1+8601〔bAI8601(推断)〕
      {
LABEL_27:  // 标签 LABEL_27（跳转合流点）
        if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )  // 复合条件判定（与/或）
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
            pArg1,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 896))(pArg1, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
        }
        goto LABEL_30;
      }
      if ( sub_41A5E0(pArg1 + 7028) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        sub_598440((uint32_t *)pArg1, nArg2, nSegIdx, 1000, 0);  // 朝目标突进的速率设定（·0x596030 同构+系数可选）
        sub_4A0550(120);  // 调 镜头幅度
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 2 || sub_41A5E0(pArg1 + 7028) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        nScratch = sub_5985E0((uint32_t *)pArg1, nArg2, nSegIdx, 400.0);  // 朝目标突进：施加速率并返回所需时长
        fStopTime = (double)nScratch;
        if ( fStopTime < 300.0 )
          fStopTime = 300.0;
        sub_4A05C0((uint64_t)(fStopTime * 0.5));
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        sub_598440((uint32_t *)pArg1, nArg2, nSegIdx, 1000, 1);  // 朝目标突进的速率设定（·0x596030 同构+系数可选）
        sub_4A0550(90);  // 调 镜头幅度
      }
    }
    if ( *(uint8_t *)(pArg1 + 8601) == 0 )  // pArg1+8601〔bAI8601(推断)〕
    {
LABEL_40:  // 标签 LABEL_40（跳转合流点）
      if ( *(float *)(*(uint32_t *)(pArg1 + 112) + 24) > 0.0 && *(uint8_t *)(pArg1 + 8601) == 0 )  // 复合条件判定（与/或）
      {
        pActObj = *(int **)(pArg1 + 120);  // pArg1+120〔pAnimObj〕
        if ( pActObj[37] < 1 )
          sub_4AECE0(pActObj, 1);  // 调 切武器动画
        *(uint8_t *)(pArg1 + 8601) = 1;  // pArg1+8601〔bAI8601(推断)〕
      }
      goto LABEL_45;
    }
    goto LABEL_27;
  }
LABEL_45:  // 标签 LABEL_45（跳转合流点）
  if ( *(uint8_t *)(pArg1 + 8636) == 1 && *(uint8_t *)(pArg1 + 8637) == 1 )  // 复合条件判定（与/或）
  {
    nThrowCd = *(uint32_t *)(pArg1 + 8676);  // pArg1+8676〔uAI8676(推断)〕
    if ( sub_699000(pArg1 + 8652) >= nThrowCd && rand() % 100 < *(uint32_t *)(pArg1 + 8648) )  // 【clock_now(clk)】
    {
      pMissile = dword_8F82CC;
      memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
      nMolVt = *(uint32_t *)dword_8F82CC;
      nFreeState = 0;
      pParams = (uint32_t *)(*(int (/*thiscall*/ **)(int))(nMolVt + 36))(dword_8F82CC);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/60584…
      nRand = rand() % (*(uint32_t *)(pArg1 + 8644) + 1);  // nRand = 调 rand
      pParams[3] = 30;
      pParams[4] = 50;
      pParams[1] = nRand;
      nScratch = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 192))(pArg1);  // 调虚槽 +192
      nSpeedPacked = (uint64_t)((double)nScratch * 0.69999999);
      pParams[5] = nSpeedPacked;
      (*(void (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)pMissile + 12))(pMissile, HIDWORD(nSpeedPacked));  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
      nMolVt2 = *(uint32_t *)pMissile;
      nPosZ = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      nPosY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nMolX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(int, int))(nMolVt2 + 40))(pMissile, nMolX);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      nPkt = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)pMissile + 92))(pMissile, v19);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
      LOBYTE(nFreeState) = 1;
      sub_4E77D0((int)pBuf, nPkt);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
      LOBYTE(nFreeState) = 0;
      sub_5E5260(v19);  // 调 动画子对象清理临时缓冲
      pPacket = (void *)(*(int (/*thiscall*/ **)(int, int, uint32_t, void **))(*(uint32_t *)pArg1 + 80))(pArg1, 2, 0, pBuf);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      sub_4600B0(pPacket, nPosY, nPosZ, 0);  // 调 演播层注册(槽号)
      *(uint8_t *)(pArg1 + 8665) = 0;
      *(uint8_t *)(pArg1 + 8666) = 0;
      sub_698F90(pArg1 + 8652, *(uint32_t *)(pArg1 + 8640), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
    }
  }
}


// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x598F60 sub_598F60 —— 反击抓取钩子：大状态 8 被击时切反应态 14，尾调架招判定
// 大状态(this+6556)==8 且子状态链 this+7028 值为 3/4 时，对来击目标（vt+40 查 17、vt+948 可抓判定）
// 取其坐标（vt+48/52）经 sub_431230 打包，vt+560 反应态写入器切到态 14（=抓取反制相位）【推断】
// 条件不满足则仅尾调 ·0x4DB480 反击/架招触发判定并返回其结果
// ------------------------------------------------------------
int /*thiscall*/ sub_598F60(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：反击抓取钩子：大状态 8 被击时切反应态 14，尾调架招判定
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8  // this+6556〔大状态ID〕
    && (uint8_t)nArg4 == 0
    && (sub_41A5E0((unsigned int)(this + 1757)) == 3 || sub_41A5E0((unsigned int)(this + 1757)) == 4)  // crypt4byte 解密校验（·0x41A590 逆运算）
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 948))(pObj) != 0  // 调虚槽 +948
    && *(this + 154) != 14 )  // this+616〔nReactionState〕
  {
    memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
    v6 = *(uint32_t *)pObj;
    v9 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(v6 + 48))(pObj);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    v9 = -1;
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
  return sub_4DB480(pObj, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 参数打包 AI（89L）
// ------------------------------------------------------------
// 0x599070 sub_599070 —— 抓取释放：对 this+8604 槽的被抓目标落位、恢复并清槽
// 目标先 vt+604/vt+612 复位；按 this+8624/8628 记录坐标经 vt+136 判定落点，失败则以目标
// vt+124(300) 取点并经自身 vt+140 复核，最终 vt+112 把目标放到可行点【推断：放人位置解算】
// 目标存活（vt+308）时为其打包 setState 参数 4/0/1/200/200 经 vt+560+vt+564 写入，再 vt+848 清零
// 最后清 this+8604 抓取槽；被 ·0x599270 与 ·0x5992E0 态 14 调用
// ------------------------------------------------------------
void /*usercall*/ sub_599070(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 实现：抓取释放：对 this+8604 槽的被抓目标落位、恢复并清槽
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

  pObj3 = pDwArg1[2151];  // pObj3 = 取 pDwArg1[2151]
  if ( pObj3 != 0 )  // 若 pObj3 非 0
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 612))(pDwArg1[2151], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 136))(  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
           pDwArg1[2151],
           pDwArg1[2156],
           pDwArg1[2157],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2151] + 112))(pDwArg1[2151], pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
    else  // 否则分支
    {
      pObj = pDwArg1[2151];  // pObj = 取 pDwArg1[2151]
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);  // 调虚槽 +120：动画对象
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2156, pDwArg1 + 2157, v7);  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
      pObj2 = pDwArg1[2151];  // pObj2 = 取 pDwArg1[2151]
      if ( v8 != 0 )  // 若 v8 非 0
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
      else  // 否则分支
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2158]);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2151], v12);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 308))(pDwArg1[2151]) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      Block = nullptr;  // Block = 空指针
      v15 = 0;
      v16 = 0;
      v18 = 0;
      pObj4 = 4;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 0;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 1;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 560))(pDwArg1[2151], 4, v13, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 564))(pDwArg1[2151]);
      v18 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
      Block = nullptr;  // Block = 空指针
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 848))(pDwArg1[2151], 0);  // 调虚槽 +848：冻结标志写入（+6744，0→-1 / 非0→0）
    pDwArg1[2151] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x599270 sub_599270 —— 抓取清理钩子：目标或自身移除时调 ·0x599070 解除抓取
// pDwArg3 为被抓目标时：主状态 14 则释放并清 this+8604；pDwArg3 为自身时释放并另发 vt+216(33) 通知
// 尾调 ·0x4D9170 基类移除处理【推断：对象销毁回调链一环】
// ------------------------------------------------------------
int /*userpurge*/ sub_599270@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)  // 实现：抓取清理钩子：目标或自身移除时调 ·0x599070 解除抓取
{
  if ( pDwArg3 == (int *)pDwArg1[2151] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
      sub_599070(pDwArg1, nArg2);  // 抓取释放：对 this+8604 槽的被抓目标落位、恢复并清槽
    pDwArg1[2151] = 0;
  }
  if ( pDwArg3 == pDwArg1 )  // 若 pDwArg3 == pDwArg1
  {
    if ( pDwArg1[2151] != 0 )
    {
      sub_599070(pDwArg1, nArg2);  // 抓取释放：对 this+8604 槽的被抓目标落位、恢复并清槽
      pDwArg1[2151] = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);  // 调虚槽 +216：音效 TAG 查询
  }
  return sub_4D9170(pDwArg3);  // 返回 调 sub_4D9170 返回值
}



// 攻击 AI：vt+212 播报 FOX_ATK
// ------------------------------------------------------------
// 0x5992E0 sub_5992E0 —— 狐狸攻击入场分发器：态 8 出爪播 FOX_ATK / 态 14 抓取蓄力 / 态 15 抱摔
// 入场前按旧大状态清理：旧态 14 先 ·0x599070 释放被抓目标，态 15 转 8 时发 vt+216(33)
// 态 8 清 this+8600-8602 三标志并 vt+212 播 FOX_ATK；首次（this+7028 链空）经 vt+876/vt+888
// 配置位移与判定框参数（700/700、-2000 击退、1000/1000）后 vt+152(4)→vt+896 选动作【推断】
// 尾调 ·0x4E33D0 基类入场；态 14/15 分别转 ·0x598840（HOLD 蓄力抓目标）与 ·0x597890
// ------------------------------------------------------------
int /*userpurge*/ sub_5992E0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, int nArg4, int nArg5, int nArg6)  // 实现：狐狸攻击入场分发器：态 8 出爪播 FOX_ATK / 态 14 抓取蓄力 / 态 15 抱摔
{
  int v7; // eax
  int v8; // edx
  int result; // eax
  int v10; // edi
  int v11; // eax

  v7 = pDwArg1[1639];  // v7 = 取 pDwArg1[1639]
  if ( v7 == 15 )  // 若 v7 == 15
  {
    if ( ArgList != 15 )  // 若 ArgList != 15
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);  // 调虚槽 +216：音效 TAG 查询
  }
  else if ( v7 == 14 )
  {
    sub_599070(pDwArg1, nArg2);  // 抓取释放：对 this+8604 槽的被抓目标落位、恢复并清槽
  }
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      v8 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8600) = 0;
      *((uint8_t *)pDwArg1 + 8601) = 0;
      *((uint8_t *)pDwArg1 + 8602) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(pDwArg1, "FOX_ATK", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      break;  // 跳出循环/分支
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      sub_598840(pDwArg1, nArg4);  // HOLD 蓄力入场：抓取目标（·0x596650 同构+成长加成首入段）
      break;  // 跳出循环/分支
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      sub_597890(pDwArg1);  // 大状态 15 入场处理（·0x595C40 同构）
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  result = sub_4E33D0(ArgList, *(float *)&nArg4, nArg5, nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 8 )  // 若 ArgList == 8
  {
    result = sub_41A5E0((unsigned int)(pDwArg1 + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 0 )  // 若 result 为 0
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*pDwArg1 + 876))(pDwArg1, 0, 700, 700, 0, -2000, 1);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*pDwArg1 + 888))(pDwArg1, 2, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
      v10 = *pDwArg1;
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);  // 调虚槽 +152：效果通道 3
      return (*(int (/*thiscall*/ **)(int *, int))(v10 + 896))(pDwArg1, v11);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
    }
  }
  return result;
}



// 狐狸资源装载 2：R_FOX_* 语音 + Teeth.equ（this+8636/8637/8665/8666 相位字段）
// ------------------------------------------------------------
// 0x5993F0 sub_5993F0 —— 狐狸(Lugaru)装载：R_FOX_TALK/DMG、FOX_DIE 语音 + Monster/Lugaru/Teeth.equ 外观
// 语音 TAG 经 sub_4015C0 写槽（vt+212 播报）；Teeth.equ 经 ·0x4BA9E0 装载后 vt+784 挂载
// vt+384(0..6) 出场参数面：参数 0/1 与帧区间 this+7280/7284 做 ·0x4049C0 插值存 this+8608，
// 参数 2 置 this+8637 标志、参数 3 存 this+8640 并经 ·0x698F90 设 this+8652 倒计时钟、
// 参数 4/5 存 this+8644/8648、参数 6 ×0.01 存 this+8680 浮点【推断：出场节奏/相位调度参数面】
// ------------------------------------------------------------
int /*thiscall*/ sub_5993F0(uint32_t *this)  // 实现：狐狸(Lugaru)装载：R_FOX_TALK/DMG、FOX_DIE 语音 + Monster/Lugaru/Teeth.equ 外观
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

  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_FOX_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_FOX_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("FOX_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Lugaru/Teeth.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v3 = nullptr;  // v3 = 空指针
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v14 = (float)v16;
  v13 = (float)(int)Block;
  fld_e1820 = (uint64_t)sub_4049C0(v13, v14, *v6 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e1820) = *this;
  *(this + 2152) = fld_e1820;  // this+8608〔uAI8608(推断)〕
  *(this + 162) |= 2u;  // this+648〔uMonFlagBits〕
  *((uint8_t *)this + 8636) = 0;  // this+8636〔pDollTarget(推断)〕
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(HIDWORD(fld_e1820) + 384))(this, 2);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v9 = *this;
  *((uint8_t *)this + 8637) = v8 != 0;  // this+8637〔bSwingGate8637〕
  *(this + 2160) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v9 + 384))(this, 3);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  *((uint8_t *)this + 8665) = 0;
  *((uint8_t *)this + 8666) = 0;
  sub_698F90((int)(this + 2163), *(this + 2160), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(this + 2161) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 4);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v11 = *this;
  *(this + 2162) = v10;  // this+8648〔uPhase8648(推断)〕
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v11 + 384))(this, 6);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  *((float *)this + 2170) = (double)result * 0.0099999998;  // this+8680〔uGate8680(推断)〕
  return result;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x5997B0 sub_5997B0 —— 态 5/8 钩子（简化变体）：态 5 时 50% 触发 ·0x64BDF0 光环（this+7256 数据）
// 态 8 命中包子类型 0 时清 this+8612 突进标志；与 ·0x59A3F0 同构（差异：无 7028 链分支）
// 尾调 ·0x4E33D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5997B0(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：态 5/8 钩子（简化变体）：态 5 时 50% 触发 ·0x64BDF0 光环（this+7256 数据）
{
  if ( ArgList == 5 )  // 若 ArgList == 5
  {
    if ( rand() % 100 < 50 )  // 50% 概率触发（rand()%100 < 50）
      sub_64BDF0(this, *(uint32_t *)(this + 7256));  // 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
  }
  else if ( ArgList == 8 && **(uint32_t **)(LODWORD(fArg3) + 4) == 0 )
  {
    *(uint8_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  }
  return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x599820 sub_599820 —— 事件码 7 处理：空闲（大状态 0）时按距离置 vt+148 标志并自切反应态 8
// ·0x4D84F0 清头顶气泡；vt+120 距离与事件参数 uArg32+12 比较，近则 vt+148(1)；尾调 ·0x4D90A0 基类分发
// 【推断：近身威胁响应（发现玩家后转入接敌）】
// ------------------------------------------------------------
void /*userpurge*/ sub_599820(uint32_t *pArg1@<ecx>, int nArg2@<edi>, uint32_t *uArg3)  // 实现：事件码 7 处理：空闲（大状态 0）时按距离置 vt+148 标志并自切反应态 8
{
  uint32_t *uArg32; // ebx
  uint8_t v5[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h]
  int v9; // [esp+20h] [ebp-4h]

  uArg32 = uArg3;
  sub_4D90A0(uArg3);  // 调 校验指令包
  if ( *uArg32 == 7 && pArg1[1639] == 0 )  // 复合条件判定（与/或）
  {
    sub_4D84F0(0, 0);  // 头顶气泡 CommandReceive.ani（同 0x4D82D0 结构）
    if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg2) >= uArg32[3] )  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 148))(pArg1, 1);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    else  // 否则分支
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 148))(pArg1, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    Block = nullptr;  // Block = 空指针
    v7 = 0;
    v8 = 0;
    v9 = 0;
    uArg3 = nullptr;  // uArg3 = 空指针
    sub_431230((int)v5, &uArg3);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t))(*pArg1 + 560))(pArg1, 8, v5, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
  }
}



// 投石哥布林装载：R_GOBLIN_TALK/DMG/DIE 语音 + Monster/Goblin/{tcc2,acc2,hcc3,gcc1}.equ
//   + Particle/ThrowStone.ptl 石弹粒子 + THROW_STONE 播报（69L）
// ------------------------------------------------------------
// 0x5998E0 sub_5998E0 —— 投石哥布林装载：R_GOBLIN_TALK/DMG/DIE 语音 + tcc2/acc2/hcc3/gcc1.equ 四件外观
// 另取 Particle/ThrowStone.ptl 存 this+8616（vt+588 粒子句柄）、this+8620=30001、this+7316=500；
// THROW_STONE 写语音槽；装载结构与 ·0x5993F0 狐狸版同构（差异：四件 .equ、无插值参数面）
// ------------------------------------------------------------
int /*thiscall*/ sub_5998E0(uint32_t *this)  // 实现：投石哥布林装载：R_GOBLIN_TALK/DMG/DIE 语音 + tcc2/acc2/hcc3/gcc1.equ 四件外观
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

  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/tcc2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v3 = nullptr;  // v3 = 空指针
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/acc2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v6 = nullptr;  // v6 = 空指针
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj4 != 0 )  // 若 pObj4 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem3 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v9 = sub_4BA9E0(pMem3, "Monster/Goblin/hcc3.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v9 = nullptr;  // v9 = 空指针
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v9);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj3 != 0 )  // 若 pObj3 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem4 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v12 = sub_4BA9E0(pMem4, "Monster/Goblin/gcc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v12 = nullptr;  // v12 = 空指针
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj2 != 0 )  // 若 pObj2 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  *(this + 2154) = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/ThrowStone.ptl");  // 调虚槽 +588
  *(this + 2155) = 30001;  // this+8620〔uAI8620(推断)〕
  *(this + 2156) = 0;  // this+8624〔uAI8624(推断)〕
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
// 0x599AE0 sub_599AE0 —— 投石槽复位：this+8616/8620 双字清零（装载与事件流程使用的槽位）
// 清零后由装载/技能流程重填【推断：重置流程调用】
// ------------------------------------------------------------
int /*thiscall*/ sub_599AE0(uint32_t *this)  // 实现：投石槽复位：this+8616/8620 双字清零（装载与事件流程使用的槽位）
{
  *(this + 2155) = 0;  // this+8620〔uAI8620(推断)〕
  *(this + 2154) = 0;  // this+8616〔uAI8616(推断)〕
  return 0;
}



// 插值+时钟门 AI（sub_4049C0/sub_699000）
// ------------------------------------------------------------
// 0x599AF0 sub_599AF0 —— 蓄力染色渲染：大状态 7 时按经过时间把覆层透明度 100→220 线性拉升
// ·0x4D8F90 垫片转发后于 pass 0 绘制：·0x699000 感知时钟（this+36 槽）减 this+8620 戳，
// 超 700ms 恒 220；色 0xFF00FFFF 经 ·0x491690 提交【推断：投掷前蓄力预警渲染】
// ------------------------------------------------------------
int /*thiscall*/ sub_599AF0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：蓄力染色渲染：大状态 7 时按经过时间把覆层透明度 100→220 线性拉升
{
  int result; // eax
  unsigned int fld_e2155; // eax | =+0x21AC 字段 x1（证据 005AF910）
  uint64_t v8; // rax

  result = sub_4D8F90(nArg2, nArg3, nArg4, nArg5);  // vmt144 转发垫片（IRDActiveObject__vmt144 族）
  if ( (uint8_t)nArg2 == 0 )
  {
    if ( *(this + 1787) == 7 && *(this + 30) != 0 )  // this+7148〔nBigState〕
    {
      fld_e2155 = sub_699000((int)(this + 9)) - *(this + 2155);  // 【clock_now(clk)】
      if ( fld_e2155 >= 0x2BC )  // 若 fld_e2155 >= 0x2BC
        LOBYTE(v8) = -36;
      else  // 否则分支
        v8 = (uint64_t)sub_4049C0(100.0, 220.0, fld_e2155, 700);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      sub_491690(1, 2, 1, -16776961, ((uint8_t)v8 << 24) | 0xFFFFFF, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
    }
    return sub_4D8F90(0, nArg3, nArg4, nArg5);  // vmt144 转发垫片（IRDActiveObject__vmt144 族）
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x599BA0 sub_599BA0 —— 条件字节门：大状态 6 且主状态非 8 时对 vt+98 条件求值取反
// 其余路径原样返回 ·0x498F60 条件字节【推断：大状态 6 为隐匿/特殊相位的反相】
// ------------------------------------------------------------
int /*thiscall*/ sub_599BA0(uint32_t *this)  // 实现：条件字节门：大状态 6 且主状态非 8 时对 vt+98 条件求值取反
{
  if ( *(this + 1787) != 6 || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8 )  // 调虚槽 +840：大状态 getter（this+6556）
    return sub_498F60(this);  // 取条件字节
  else  // 否则分支
    return sub_498F60(this) == 0;  // 取条件字节
}



// %s哥布林通用受击处理（被 21 张子类虚表 +512 槽共享：0x6D096C..0x6D70E4）
//   —— 哥布林一族共用的伤害落地/反应入口（研究 20 §1.2 行为差异=数据+子类定制）
// ------------------------------------------------------------
// 0x599BD0 sub_599BD0 —— 哥布林一族共用受击入口（21 张子类虚表 +512 槽共享，研究 20 §1.2）
// 先走 ·0x4DA3B0 命中包分发前置，再以 10% 概率对 this+7256 光环数据调 ·0x64BDF0（受击反馈）
// 行为差异=数据+子类定制：各子类 vmt200 覆写群以本函数为共享兜底入口【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_599BD0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：哥布林一族共用受击入口（21 张子类虚表 +512 槽共享，研究 20 §1.2）
{
  int v5; // edi

  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);  // 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && rand() % 100 < 10 )  // 调虚槽 +308：是否本地玩家
    sub_64BDF0(this, *(this + 1814));  // 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
  return v5;
}



// AI 相位辅助（74L）
// ------------------------------------------------------------
// 0x599C30 sub_599C30 —— 攻击参数面复位/配置：全清 this+7531..7596 后按 (nArg3, nArg2) 档位组合填值
// nArg3=0/2 为方向档、nArg2=0..2 强度档，组合写 this+7556/7568/7572 与 this+7596（±50）
// 与 ·0x59AD50 同构（差异：59AD50 为入场向、档 0 另做 +0.30 浮点补偿）【推断：投掷伤害/击退档位表】
// ------------------------------------------------------------
int /*thiscall*/ sub_599C30(int this, int nArg2, int nArg3)  // 实现：攻击参数面复位/配置：全清 this+7531..7596 后按 (nArg3, nArg2) 档位组合填值
{
  int result; // eax

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    if ( nArg3 != 2 )  // 若 nArg3 != 2
      return result;
    if ( nArg2 != 0 )  // 若 nArg2 非 0
    {
      if ( nArg2 == 1 )  // 若 nArg2 == 1
      {
        *(uint32_t *)(this + 7596) = 50;  // this+7596〔nOffset7596(推断)〕
      }
      else if ( nArg2 != 2 )
      {
        return result;
      }
      *(uint32_t *)(this + 7572) = 2;  // this+7572〔uGrade7572(推断)〕
      *(uint32_t *)(this + 7568) = 1;  // this+7568〔uEnable7568(推断)〕
    }
    else  // 否则分支
    {
      *(uint32_t *)(this + 7568) = 1;  // this+7568〔uEnable7568(推断)〕
      *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
    }
  }
  else if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 )  // 若 nArg2 == 1
    {
      *(uint32_t *)(this + 7568) = 1;  // this+7568〔uEnable7568(推断)〕
      *(uint32_t *)(this + 7572) = 2;  // this+7572〔uGrade7572(推断)〕
    }
    else if ( nArg2 == 2 )
    {
      *(uint8_t *)(this + 7556) = 1;  // this+7556〔bAtk7556(推断)〕
      *(uint32_t *)(this + 7572) = 2;  // this+7572〔uGrade7572(推断)〕
    }
  }
  else  // 否则分支
  {
    *(uint32_t *)(this + 7596) = -50;  // this+7596〔nOffset7596(推断)〕
  }
  return result;
}



// 子类扩展字段复位（this+8612..8700）
// ------------------------------------------------------------
// 0x599D50 sub_599D50 —— 子类扩展字段复位：清 this+8612/8616/8680/8696/8700
// 8696 为 ·0x59A490 缓存的帧游标快照、8612 为突进标志【推断：重置流程用】
// ------------------------------------------------------------
int /*thiscall*/ sub_599D50(int this)  // 实现：子类扩展字段复位：清 this+8612/8616/8680/8696/8700
{
  *(uint8_t *)(this + 8680) = 0;  // this+8680〔uGate8680(推断)〕
  *(uint32_t *)(this + 8696) = 0;  // this+8696〔uVec8696(推断)〕
  *(uint8_t *)(this + 8700) = 0;  // this+8700〔uPhase8700(推断)〕
  *(uint8_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint32_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x599D80 sub_599D80 —— 虚表转发垫片：调用 vt+1308 并原样返回其结果
// 纯转发，无附加逻辑
// ------------------------------------------------------------
int /*thiscall*/ sub_599D80(void *this)  // 实现：虚表转发垫片：调用 vt+1308 并原样返回其结果
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1308))(this);  // 调虚槽 +1308：CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
}



// 瞄准炸弹技能：引用 Particle/AimingBomb.ptl（72L；投弹兵瞄准线粒子）
// ------------------------------------------------------------
// 0x599D90 sub_599D90 —— 瞄准炸弹生成：克隆 Particle/AimingBomb.ptl 模板解算弹道后经 vt+580 发投掷物 30370
// 目标 this+7252 经 vt+1244 存活校验；vt+588 取粒子模板拷 0x62 字节，按模板速度场算飞行帧，
// 峰值分量 clamp 180，尾字段按自身尺寸>200 取 400 否则 200【推断：抛射初速档】
// 被 ·0x59A580 分支 4 调用
// ------------------------------------------------------------
int /*usercall*/ sub_599D90@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>)  // 实现：瞄准炸弹生成：克隆 Particle/AimingBomb.ptl 模板解算弹道后经 vt+580 发投掷物 30370
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
  result = pArg1[1813];  // result = 取 pArg1[1813]
  v12 = result;
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1244))(pArg1, result);  // 调虚槽 +1244
    if ( (uint8_t)result != 0 )
    {
      qmemcpy(
        v13,
        (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int, int))(*pArg1 + 588))(  // 调虚槽 +588
                        pArg1,
                        "Particle/AimingBomb.ptl",  // 粒子 .ptl Particle/AimingBomb.ptl
                        nArg2,
                        nArg3),
        0x62u);
      v5 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v13[7] + 3)) / (double)v13[17] * 1000.0);
      v6 = 2 * v5;
      v7 = (uint64_t)((double (/*fastcall*/ *)(uint32_t *, uint32_t, int, uint32_t))*(uint32_t *)(*pArg1 + 164))(  // 调虚槽 +164：★ 与目标朝向角度（atan2 角度制；3D 俯视判定）【新发现(会话 3)】
                               pArg1,
                               HIDWORD(v5),
                               v12,
                               0);
      HIDWORD(v7) = *pArg1;
      v13[18] = v7;
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(HIDWORD(v7) + 8))(pArg1, v12, 0);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTT…
      *(uint32_t *)((char *)&v13[3] + 3) = 1000 * v8 / v6;
      v9 = 1000 * (*(int (/*fastcall*/ **)(uint32_t *, int, int, uint32_t))(*pArg1 + 8))(pArg1, 1000 * v8 % v6, v12, 0) / v6;  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
      *(uint32_t *)((char *)&v13[4] + 3) = v9;
      if ( *(uint32_t *)((char *)&v13[3] + 3) > 180 )
        *(uint32_t *)((char *)&v13[3] + 3) = 180;
      if ( v9 > 180 )  // 若 v9 > 180
        *(uint32_t *)((char *)&v13[4] + 3) = 180;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 8))(pArg1);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
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
// 0x599EC0 sub_599EC0 —— stdcall 转发垫片：参数原样转调 ·0x4D90A0，无附加逻辑
// 用于虚表槽位签名适配【推断】
// ------------------------------------------------------------
int /*stdcall*/ sub_599EC0(int nArg1)  // 实现：stdcall 转发垫片：参数原样转调 ·0x4D90A0，无附加逻辑
{
  return sub_4D90A0(nArg1);  // 返回 调 sub_4D90A0 返回值
}



// 时钟门 AI（sub_699000, 68L）
// ------------------------------------------------------------
// 0x599ED0 sub_599ED0 —— 投石哥布林事件分发：码 10 锁定目标 / 码 11 发射 30055 / 码 12 举石预备
// 码 10：目标写 this+7252、vt+1104(20) 瞄准待机、·0x4D84F0 气泡 + ·0x49C5F0(12,0,0,500)
// 码 11：存活则 vt+580 发投掷物 30055 后 vt+1256 收尾
// 码 12：this+7772 不为 1/2/3（非连投冷却）才进入：vt+1104(7) 蓄势、this+8620 盖 ·0x699000 时钟戳、
// 播 this+8656 语音串并 ·0x4DB200(24, 2/3) 随机文案【推断：12=蓄力开始，7772=连投计数】
// ------------------------------------------------------------
int /*thiscall*/ sub_599ED0(int *this, uint32_t *pArg2)  // 实现：投石哥布林事件分发：码 10 锁定目标 / 码 11 发射 30055 / 码 12 举石预备
{
  int result; // eax
  uint32_t *pThis_874; // eax
  int nRand; // eax
  int v6; // edx
  uint32_t v7[2]; // [esp+8h] [ebp-8h]

  sub_4D90A0(pArg2);  // 调 校验指令包
  if ( *pArg2 == 10 )
  {
    v6 = *this;
    *(this + 1813) = pArg2[3];  // this+7252〔pTarget7252〕
    (*(void (/*thiscall*/ **)(int *, int))(v6 + 1104))(this, 20);
    sub_4D84F0(0, 0);  // 头顶气泡 CommandReceive.ani（同 0x4D82D0 结构）
    return sub_49C5F0(12, 0, 0, 500);  // 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
  }
  else if ( *pArg2 == 11 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
    if ( (uint8_t)result != 0 )
    {
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
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
      return (*(int (/*thiscall*/ **)(int *))(*this + 1256))(this);  // 调虚槽 +1256
    }
  }
  else  // 否则分支
  {
    result = *pArg2 - 12;
    if ( *pArg2 == 12 )
    {
      result = *(this + 1943);  // this+7772〔nCounterState〕
      if ( result != 3 && result != 1 && result != 2 )  // 若 result != 3 与/或 result != 1 与/或 result != 2
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 7);  // 调虚槽 +1104
        *(this + 2155) = sub_699000((int)(this + 9));  // clock_now(clk)
        if ( (unsigned int)*(this + 2169) < 0x10 )  // this+8676〔uAI8676(推断)〕
          pThis_874 = this + 2164;
        else  // 否则分支
          pThis_874 = (uint32_t *)*(this + 2164);  // this+8656〔uPair8656(推断)〕
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_874, -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
        v7[0] = 2;
        v7[1] = 3;
        nRand = rand() % 2;  // nRand = 调 rand
        return sub_4DB200(24, v7[nRand]);  // 15% 概率随机文案触发（0x4DB130 的门包装）
      }
    }
  }
  return result;
}



// AI 字段访问（this+8604）
// ------------------------------------------------------------
// 0x59A020 sub_59A020 —— 大状态退出钩子：态 6 时 this+8604 标志触发 ·0x64BDF0 光环，态 7 时置速度对象
// ·0x4DBC20 先处理基类退出副作用；态 7 把 this+7620 指向对象首字节置 1、+32 清 0
// 与 ·0x59AF70 同构（差异：59AF70 另清 this+8684、无态 7 分支）【推断：8604=退出时光环开关】
// ------------------------------------------------------------
char /*thiscall*/ sub_59A020(int this, int nArg2)  // 实现：大状态退出钩子：态 6 时 this+8604 标志触发 ·0x64BDF0 光环，态 7 时置速度对象
{
  uint8_t *fld_1DC4; // eax

  sub_4DBC20(nArg2);  // 大状态退出副作用处理器（0x4DBA80 的还原对偶）
  if ( nArg2 == 6 )  // 若 nArg2 == 6
  {
    LOBYTE(fld_1DC4) = *(uint8_t *)(this + 8604);  // this+8604〔bAI8604(推断)〕
    if ( (uint8_t)fld_1DC4 != 0 )
      LOBYTE(fld_1DC4) = sub_64BDF0(this, *(uint32_t *)(this + 7256));  // 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
  }
  else  // 否则分支
  {
    LOBYTE(fld_1DC4) = nArg2 - 7;
    if ( nArg2 == 7 )  // 若 nArg2 == 7
    {
      fld_1DC4 = *(uint8_t **)(this + 7620);  // fld_1DC4 = 读 this+7620
      *fld_1DC4 = 1;
      *(uint8_t *)(*(uint32_t *)(this + 7620) + 32) = 0;  // this+7620〔pStatusPanel(推断)〕
    }
  }
  return (char)fld_1DC4;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59A080 sub_59A080 —— 突进入场：vt+1104(5) 切动作、速度对象（this+7620→+4 浮点）×1.5、置 this+8612
// 30% 概率播 this+8628 语音；退出对偶 ·0x59A100（×0.66666669 还原）【推断：突进加速状态】
// ------------------------------------------------------------
int /*thiscall*/ sub_59A080(uint32_t *this)  // 实现：突进入场：vt+1104(5) 切动作、速度对象（this+7620→+4 浮点）×1.5、置 this+8612
{
  int nRand; // eax
  int result; // eax
  int v4; // et2

  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);  // 调虚槽 +1104
  *(float *)(*(this + 1905) + 4) = *(float *)(*(this + 1905) + 4) * 1.5;  // this+7620〔pStatusPanel(推断)〕
  *((uint8_t *)this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
  nRand = rand();  // nRand = 调 rand
  v4 = nRand % 100;
  result = nRand / 100;
  if ( v4 < 30 )  // 若 v4 < 30
  {
    if ( *(this + 2162) < 0x10u )  // this+8648〔uPhase8648(推断)〕
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, this + 2157, -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    else  // 否则分支
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
               this,
               *(this + 2157),  // this+8628〔语音〕
               -1,
               0,
               0);
  }
  return result;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59A100 sub_59A100 —— 突进退出：清 this+8612、速度 ×0.66666669 还原（·0x59A080 ×1.5 的逆）
// 目标存活（vt+1244）时 vt+1140(-1,-1) 急停，否则 vt+1104(13)；·0x59A290 相位 5 超 3000ms 亦调本函数
// ------------------------------------------------------------
int /*thiscall*/ sub_59A100(uint32_t *this)  // 实现：突进退出：清 this+8612、速度 ×0.66666669 还原（·0x59A080 ×1.5 的逆）
{
  int result; // eax

  if ( *(this + 1813) != 0  // this+7252〔pTarget7252〕
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1244))(this, *(this + 1813)) != 0 )  // 调虚槽 +1244
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1140))(this, -1, -1);  // 调虚槽 +1140
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
  }
  result = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
  *(float *)(result + 4) = *(float *)(result + 4) * 0.66666669;
  *((uint8_t *)this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  return result;
}



// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x59A160 sub_59A160 —— 缩放演出：vt+1172 帧游标在 30 帧内把参数 3→参数 0 插值为 0.01 基系数
// 经 vt+688/·0x4EB4B0/·0x4EB2C0 施加本体，再遍历 this+6468 起 18 个挂件槽逐个 ·0x4EB6E0/·0x4EB6A0
// 【推断：身体缩小/放大类消散或生长演出】
// ------------------------------------------------------------
int /*thiscall*/ sub_59A160(uint32_t *this)  // 实现：缩放演出：vt+1172 帧游标在 30 帧内把参数 3→参数 0 插值为 0.01 基系数
{
  int v2; // edi
  int result; // eax
  uint32_t *pThis_651; // esi
  int i; // ebx
  float v6; // [esp+4h] [ebp-28h]
  float v7; // [esp+8h] [ebp-24h]
  float v8; // [esp+24h] [ebp-8h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1172))(this);  // 调虚槽 +1172
  v7 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v6 = (float)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v8 = (double)(int)(uint64_t)sub_4049C0(v6, v7, v2, 30) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 688))(this, 1065353216);  // 调虚槽 +688：附加块基址 this+6160
  sub_4EB4B0(COERCE_FLOAT(4));  // 与 ·0x4EB2C0 同构（差异：·sub_4923F0 按倒数缩放）
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);  // 调虚槽 +688：附加块基址 this+6160
  result = sub_4EB2C0(v8);  // 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )  // 循环：i 从 18 递减到 0
  {
    if ( *pThis_651 != 0 )
    {
      sub_4EB6E0(1.0);  // 与 ·0x4EB6A0 同构（差异：调 ·0x4EB4B0）
      result = sub_4EB6A0(v8);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
    }
    ++pThis_651;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59A220 sub_59A220 —— 帧游标分档清标志：vt+1172 游标越小清得越多（速度对象 this+7620）
// 清序：前 5 帧 +32，随游标推进依次 +64、+96、+128（>20 帧后不再清）【推断：随帧关闭攻击判定窗】
// 由 ·0x59A490 在 8696 快照为 0 时调用一次
// ------------------------------------------------------------
int /*thiscall*/ sub_59A220(int *this)  // 实现：帧游标分档清标志：vt+1172 游标越小清得越多（速度对象 this+7620）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 1172))(this);  // 调虚槽 +1172
  if ( result > 0 )  // 若 result > 0
  {
    if ( result > 5 )  // 若 result > 5
    {
      if ( result > 10 )  // 若 result > 10
      {
        if ( result > 15 )  // 若 result > 15
        {
          if ( result > 20 )  // 若 result > 20
            return result;
          goto LABEL_6;
        }
LABEL_5:  // 标签 LABEL_5（跳转合流点）
        *(uint8_t *)(*(this + 1905) + 96) = 0;  // this+7620〔pStatusPanel(推断)〕
LABEL_6:  // 标签 LABEL_6（跳转合流点）
        result = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
        *(uint8_t *)(result + 128) = 0;
        return result;
      }
    }
    else  // 否则分支
    {
      *(uint8_t *)(*(this + 1905) + 32) = 0;  // this+7620〔pStatusPanel(推断)〕
    }
    *(uint8_t *)(*(this + 1905) + 64) = 0;  // this+7620〔pStatusPanel(推断)〕
    goto LABEL_5;
  }
  return result;
}



// 时钟门 AI（this+8612, 77L）
// ------------------------------------------------------------
// 0x59A290 sub_59A290 —— 大状态机（this+7148）：0 待机 / 4 概率突进 / 5 突进超时退出 / 13-15 归位
// 相位 4：有目标且 rand < this+8616 时 ·0x59A080 突进；相位 5：this+8612 置位且 ·0x699000 时钟
// 超 this+7704 戳 3000ms 则 ·0x59A100 退出，无目标则 vt+1104(13)；13-15 有目标转 vt+1104(4)
// 尾段：主状态 0 且 this+7632/7636 均空时 1% 播 vt+1104(20) + ·0x4D84F0 气泡 + ·0x49C5F0(12,0,0,500)
// 【推断：闲时小动作】；·0x4E0120 每帧前置调用
// ------------------------------------------------------------
int /*thiscall*/ sub_59A290(uint32_t *this)  // 实现：大状态机（this+7148）：0 待机 / 4 概率突进 / 5 突进超时退出 / 13-15 归位
{
  int result; // eax
  int nRand; // eax
  int v4; // et2

  if ( *(this + 1787) == 7 )  // this+7148〔nBigState〕
    return sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( *(this + 1787) )  // this+7148〔nBigState〕
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);  // 调虚槽 +1284
      goto LABEL_15;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_6;
      if ( rand() % 100 < *(this + 2154) )  // this+8616〔uAI8616(推断)〕
        sub_59A080(this);  // 突进入场：vt+1104(5) 切动作、速度对象（this+7620→+4 浮点）×1.5、置 this+8612
      goto LABEL_15;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
      {
        if ( *((uint8_t *)this + 8612) == 1 && sub_699000((int)(this + 1910)) - *(this + 1926) > 3000 )  // 【clock_now(clk)】
          sub_59A100(this);  // 突进退出：清 this+8612、速度 ×0.66666669 还原（·0x59A080 ×1.5 的逆）
      }
      else  // 否则分支
      {
LABEL_6:  // 标签 LABEL_6（跳转合流点）
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      }
      goto LABEL_15;
    case 0xD:
    case 0xE:
    case 0xF:
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result == 0 )  // 若 result 为 0
        return result;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
LABEL_15:  // 标签 LABEL_15（跳转合流点）
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
        if ( result == 0 )  // 若 result 为 0
        {
          result = *(this + 1908);  // this+7632〔uWindow7632(推断)〕
          if ( result == 0 )  // 若 result 为 0
          {
            result = *(this + 1909);  // this+7636〔nPosWinY〕
            if ( result == 0 )  // 若 result 为 0
            {
              nRand = rand();  // nRand = 调 rand
              v4 = nRand % 100;
              result = nRand / 100;
              if ( v4 < 1 )  // 若 v4 < 1
              {
                (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 20);  // 调虚槽 +1104
                sub_4D84F0(0, 0);  // 头顶气泡 CommandReceive.ani（同 0x4D82D0 结构）
                result = sub_49C5F0(12, 0, 0, 500);  // 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
              }
            }
          }
        }
      }
      break;  // 跳出循环/分支
    default:  // 默认分支
      goto LABEL_15;
  }
  return result;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59A3F0 sub_59A3F0 —— 态 5/8 钩子：态 5 时 50% 触发 ·0x64BDF0 光环（this+7256 数据）
// 态 8 按 this+7028 链分流：链值 1 走 ·0x49C5F0(11,0,0,400)，突进标志 8612 置位则 ·0x59A100 退出
// 与 ·0x59B680 同构（差异：59B680 加 ·0x4DB200 随机文案）；尾调 ·0x4E33D0
// ------------------------------------------------------------
int /*thiscall*/ sub_59A3F0(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：态 5/8 钩子：态 5 时 50% 触发 ·0x64BDF0 光环（this+7256 数据）
{
  int result; // eax
  int nRand; // eax
  int v8; // et2

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 5 )  // 若 ArgList == 5
  {
    nRand = rand();  // nRand = 调 rand
    v8 = nRand % 100;
    result = nRand / 100;
    if ( v8 < 50 )  // 若 v8 < 50
      return sub_64BDF0(this, *(uint32_t *)(this + 7256));  // 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
  }
  else if ( ArgList == 8 )
  {
    result = sub_41A5E0(this + 7028);  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )  // 若 result == 1
    {
      return sub_49C5F0(11, 0, 0, 400);  // 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
    }
    else if ( *(uint8_t *)(this + 8612) == 1 )  // this+8612〔uAI8612(推断)〕
    {
      return sub_59A100((uint32_t *)this);  // 突进退出：清 this+8612、速度 ×0.66666669 还原（·0x59A080 ×1.5 的逆）
    }
  }
  return result;
}



// 硬直字段群（this+204/+208 主状态硬直, 研究 15；86xx 相位）
// ------------------------------------------------------------
// 0x59A490 sub_59A490 —— 投石相位参数写入：8696 快照为 0 时先 ·0x59A220 并缓存 vt+1172 游标
// 态 8 按命中包子类型分流：类型 1/2 置 this+8680 发投标志；类型 3 写三连投帧计划
// this+8684/8688/8692 = 2/6/10（由 ·0x59A580 分支 3 逐帧消费）；类型 4 复位动画游标（·0x4926A0）
// 后 vt+204 播 100 号动作；this+7028 链值 4 时 vt+208 直播；其余落 ·0x59A3F0 兜底
// ------------------------------------------------------------
int /*thiscall*/ sub_59A490(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：投石相位参数写入：8696 快照为 0 时先 ·0x59A220 并缓存 vt+1172 游标
{
  if ( *(uint32_t *)(this + 8696) == 0 )  // this+8696〔uVec8696(推断)〕
  {
    sub_59A220((int *)this);  // 帧游标分档清标志：vt+1172 游标越小清得越多（速度对象 this+7620）
    *(uint32_t *)(this + 8696) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1172))(this);  // 调虚槽 +1172
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0(this + 7028) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, **(uint32_t **)(this + 6216));  // 调虚槽 +208：定时器移除
  if ( ArgList == 8 )  // 若 ArgList == 8
  {
    switch ( **(uint32_t **)(LODWORD(fArg3) + 4) )  // 按 **(uint32_t **)(LODWORD(fArg3)… 分派
    {
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        goto LABEL_10;
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        *(uint32_t *)(this + 8684) = 2;  // this+8684〔bGate8684(推断)〕
        *(uint32_t *)(this + 8688) = 6;  // this+8688〔bVec8688(推断)〕
        *(uint32_t *)(this + 8692) = 10;  // this+8692〔uVec8692(推断)〕
        goto LABEL_10;
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        sub_4926A0(**(uint32_t **)(this + 6216));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调虚槽 +204：定时器插入
          this,
          100,
          **(uint32_t **)(this + 6216),  // this+6216〔pTbl6216(推断)〕
          0,
          0,
          0,
          0);
LABEL_10:  // 标签 LABEL_10（跳转合流点）
        *(uint8_t *)(this + 8680) = 1;  // this+8680〔uGate8680(推断)〕
        break;  // 跳出循环/分支
      default:  // 默认分支
        return sub_59A3F0(this, ArgList, fArg3, nArg4, nArg5);  // 态 5/8 钩子：态 5 时 50% 触发 ·0x64BDF0 光环（this+7256 数据）
    }
  }
  return sub_59A3F0(this, ArgList, fArg3, nArg4, nArg5);  // 态 5/8 钩子：态 5 时 50% 触发 ·0x64BDF0 光环（this+7256 数据）
}



// 投石主技能：Particle/ThrowStone.ptl + THROW_STONE（230L；RTTI cast→CNFighter 目标解算）
// ------------------------------------------------------------
// 0x59A580 sub_59A580 —— 投石主技能帧处理：按 this+7028 链值 1-4 分派，30372 石弹 / 34-35 双弹 / 30370 瞄准弹
// 前置：this+8360 非零且 8700 未置时置 8700 并调 vt+1312()；帧游标>5 时扫描 vt+700 附属列表，
// RTTI cast IRDAppendage→CNChangeStatus 后按存在性写速度对象 +32 标志
// 分支 1：清全部 CNChangeStatus 附件后以 ·0x4B3DF0 造类型 8/7 两投掷物（参数 0/1 为初速、2 共用）
// 经 +56 以槽 34/35 发射；分支 2/3：vt+580 发 30372 + vt+212 播 THROW_STONE（分支 3 轮询帧计划槽）
// 分支 4：调 ·0x599D90 发瞄准弹后 vt+208 播动作；各分支结束落 ·0x4E1780 兜底
// ------------------------------------------------------------
char /*thiscall*/ sub_59A580(uint8_t *this)  // 实现：投石主技能帧处理：按 this+7028 链值 1-4 分派，30372 石弹 / 34-35 双弹 / 30370 瞄准弹
{
  int nVt1; // eax
  int pStatusFound; // ebx
  unsigned int i; // edi
  int pAppend; // eax
  int nBegin1; // ecx
  int nCount1; // eax
  int pAppend2; // eax
  int nBegin2; // ecx
  int pItem; // ecx
  int pAppend3; // eax
  int nBegin3; // ecx
  int pItem2; // ecx
  int nCurFrame; // ebx
  uint32_t *pProjA; // ebx
  int nIdx; // edi
  uint32_t *pAppend4; // eax
  int pStatus; // eax
  int pStatus2; // eax
  uint32_t *pAppend5; // eax
  int nVt2; // edx
  int nParam2; // edi
  uint32_t *pMem; // eax
  uint32_t *pMem2; // eax
  uint32_t *pProjB; // edi
  int pPtcl; // eax
  int nPlanIdx; // edi
  int *pPlanIt; // ecx
  int pPtcl2; // eax
  uint32_t *pActionSlot; // eax
  int nVt3; // edx
  int fTmpA; // [esp+10h] [ebp-30h]
  int fTmpB; // [esp+10h] [ebp-30h]
  int nParam1; // [esp+2Ch] [ebp-14h]
  int nParam0; // [esp+30h] [ebp-10h]

  if ( *((uint32_t *)this + 2090) != 0 && *(this + 8700) == 0 )  // 2090 槽激活且 8700 未置：一次性前置
  {
    nVt1 = *(uint32_t *)this;
    *(this + 8700) = 1;
    (*(void (**)(void))(nVt1 + 1312))();  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施法与…
  }
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1172))(this) > 5 )  // 帧游标>5
  {
    pStatusFound = 0;
    for ( i = 0; ; ++i )  // 扫描 vt+700 附属表找 CNChangeStatus
    {
      pAppend = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
      nBegin1 = *(uint32_t *)(pAppend + 4);
      nCount1 = nBegin1 != 0 ? (*(uint32_t *)(pAppend + 8) - nBegin1) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)i >= nCount1 )
        break;  // 跳出循环/分支
      pAppend2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
      nBegin2 = *(uint32_t *)(pAppend2 + 4);
      if ( nBegin2 != 0 && i < (*(uint32_t *)(pAppend2 + 8) - nBegin2) >> 2 )  // 若 nBegin2 != 0
        pItem = *(uint32_t *)(nBegin2 + 4 * i);
      else  // 否则分支
        pItem = 0;
      if ( *(uint8_t **)(pItem + 4) == this )  // 回指校验
      {
        pAppend3 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
        nBegin3 = *(uint32_t *)(pAppend3 + 4);
        if ( nBegin3 != 0 && i < (*(uint32_t *)(pAppend3 + 8) - nBegin3) >> 2 )  // 若 nBegin3 != 0
          pItem2 = *(uint32_t *)(nBegin3 + 4 * i);
        else  // 否则分支
          pItem2 = 0;
        pStatusFound = __RTDynamicCast(pItem2, 0, &IRDAppendage `RTTI Type Descriptor', &CNChangeStatus `RTTI Type Descriptor', 0);  // pStatusFound = 调 __RTDynamicCast
      }
    }
    *(uint8_t *)(*((uint32_t *)this + 1905) + 32) = pStatusFound == 0;  // 速度对象 +32 标志=是否存在状态挂件
  }
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 8 )  // 姿态 8=投石
  {
    nCurFrame = *(uint32_t *)(*((uint32_t *)this + 30) + 148);  // 当前动画帧
    switch ( sub_41A5E0((unsigned int)(this + 7028)) )  // 攻击段号
    {
      case 1:  // 双弹齐投（34/35 槽）
        if ( nCurFrame >= 2  // 若 nCurFrame >= 2
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
          && *(this + 8680) != 0 )
        {
          pProjA = nullptr;  // pProjA = 空指针
          nIdx = 0;
          pAppend4 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
          if ( sub_41C5A0(pAppend4) > 0 )  // vector<T 4B> 大小查询（空返回 0）
          {
            do  // do-while 循环体起点
            {
              (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
              if ( *(uint8_t **)(sub_517740(nIdx) + 4) == this )  // 若调用结果为真
              {
                (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
                pStatus = sub_517740(nIdx);  // pStatus = 调 sub_517740 返回值
                pStatus2 = __RTDynamicCast(
                        pStatus,
                        0,
                        &IRDAppendage `RTTI Type Descriptor',
                        &CNChangeStatus `RTTI Type Descriptor',
                        0);
                if ( pStatus2 != 0 )  // 若 pStatus2 非 0
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pStatus2 + 76))(pStatus2, 0);  // 清状态挂件
              }
              ++nIdx;
              pAppend5 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
            }
            while ( nIdx < sub_41C5A0(pAppend5) );  // vector<T 4B> 大小查询（空返回 0）
          }
          nVt2 = *(uint32_t *)this;
          *(this + 8680) = 0;  // 投石槽清空
          nParam0 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(nVt2 + 384))(this, 0);  // 参数0
          nParam1 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 1);  // 参数1
          nParam2 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 2);  // 参数2（共用）
          pMem = operator new(0x7Cu);  // new(124 字节) 分配对象
          if ( pMem != nullptr )  // 若 pMem 有效（非空）
          {
            *(float *)&fTmpA = (float)nParam0;
            pProjA = sub_4B3DF0(pMem, 8, 0, fTmpA, nParam2, 1);  // 8 号投掷物
          }
          pMem2 = operator new(0x7Cu);  // new(124 字节) 分配对象
          if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
          {
            *(float *)&fTmpB = (float)nParam1;
            pProjB = sub_4B3DF0(pMem2, 7, 0, fTmpB, nParam2, 1);  // 7 号投掷物
          }
          else  // 否则分支
          {
            pProjB = nullptr;  // pProjB = 空指针
          }
          (*(void (/*thiscall*/ **)(uint32_t *, uint8_t *, uint8_t *, int, uint32_t, int, int))(*pProjA + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
            pProjA,
            this,
            this,
            1,
            0,
            34,  // 槽 34
            -1);
          (*(void (/*thiscall*/ **)(uint32_t *, uint8_t *, uint8_t *, int, uint32_t, int, int))(*pProjB + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
            pProjB,
            this,
            this,
            1,
            0,
            35,  // 槽 35
            -1);
        }
        break;  // 跳出循环/分支
      case 2:  // 单发 30372 石弹
        if ( nCurFrame >= 2  // 若 nCurFrame >= 2
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
          && *(this + 8680) != 0 )
        {
          pPtcl = (*(int (/*thiscall*/ **)(uint8_t *, const char *))(*(uint32_t *)this + 588))(this, "Particle/ThrowStone.ptl");  // 投石粒子模板
          (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
            this,
            30372,  // 技能 id 30372
            0,
            pPtcl,
            0,
            20,
            0,
            60,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            this,
            "THROW_STONE",  // 标签 THROW_STONE
            -1,
            0,
            0);
          *(this + 8680) = 0;
        }
        break;  // 跳出循环/分支
      case 3:  // 按帧计划槽（8684 起三项）逐个补投
        if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
        {
          nPlanIdx = 0;
          for ( pPlanIt = (int *)(this + 8684); nCurFrame < *pPlanIt || *pPlanIt <= 0; ++pPlanIt )  // 找首个未命中的计划帧
          {
            if ( ++nPlanIdx >= 3 )
              return sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
          }
          pPtcl2 = (*(int (/*thiscall*/ **)(uint8_t *, const char *))(*(uint32_t *)this + 588))(this, "Particle/ThrowStone.ptl");  // 调虚槽 +588
          (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
            this,
            30372,
            0,
            pPtcl2,
            0,
            20,
            0,
            60,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            this,
            "THROW_STONE",  // 标签 THROW_STONE
            -1,
            0,
            0);
          *((uint32_t *)this + nPlanIdx + 2171) = -1;  // 该计划槽标记已投
        }
        break;  // 跳出循环/分支
      case 4:  // 瞄准弹（599D90）
        if ( nCurFrame >= 2  // 若 nCurFrame >= 2
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
          && *(this + 8680) != 0 )
        {
          sub_599D90(this);  // 发瞄准弹
          pActionSlot = *((uint32_t **)this + 1554);
          nVt3 = *(uint32_t *)this;
          *(this + 8680) = 0;
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(nVt3 + 208))(this, *pActionSlot);  // 播动作
        }
        break;  // 跳出循环/分支
      default:  // 默认分支
        return sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
    }
  }
  return sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}


// 自杀哥布林装载：R_GOBLIN_* 语音 + GOBLIN_SUICIDAL/GOBLIN_SCARED 播报 +
//   Monster/Goblin/{gcc1,Weapon01}.equ（92L）
// ------------------------------------------------------------
// 0x59A990 sub_59A990 —— 自杀哥布林装载：R_GOBLIN_* + GOBLIN_SUICIDAL/GOBLIN_SCARED 语音、gcc1/Weapon01.equ
// 属性面：this+7320=100、7324=350、7328/7332=500、7356=-30；vt+384(0/1) 与帧区间做 ·0x4049C0
// 插值存 this+8616；vt+340 判定值==1 时把 this+8370 起 26 个半字填 50【推断：自爆参数/权重表】
// 与 ·0x5998E0 投石版装载同构（差异：无 THROW_STONE 槽，多自杀/恐惧文案）
// ------------------------------------------------------------
uint16_t */*thiscall*/ sub_59A990(uint32_t *this)  // 实现：自杀哥布林装载：R_GOBLIN_* + GOBLIN_SUICIDAL/GOBLIN_SCARED 语音、gcc1/Weapon01.eq…
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

  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("GOBLIN_SUICIDAL", 0xFu);  // 【std::string构造赋值】
  sub_4015C0("GOBLIN_SCARED", 0xDu);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/gcc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v3 = nullptr;  // v3 = 空指针
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/Weapon01.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v6 = nullptr;  // v6 = 空指针
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj2 != 0 )  // 若 pObj2 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  *(this + 1832) = 500;
  *(this + 1833) = 500;
  v8 = *this;
  *(this + 1830) = 100;
  *(this + 1839) = -30;
  *(this + 1831) = 350;
  *((uint8_t *)this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v8 + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v19 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v9 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  fld_e1820 = *(this + 1820);
  if ( *v9 - fld_e1820 >= 1 )
  {
    v12 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    fld_e1820 = *(this + 1820);
    v11 = *v12 - fld_e1820;
  }
  else  // 否则分支
  {
    v11 = 1;
  }
  v17 = (float)v19;
  v16 = (float)(int)Block;
  fld_e1821 = (uint64_t)sub_4049C0(v16, v17, v11, *(this + 1821) - fld_e1820);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e1821) = *this;
  *(this + 2154) = fld_e1821;  // this+8616〔uAI8616(推断)〕
  result = (uint16_t *)(*(int (/*thiscall*/ **)(uint32_t *))(HIDWORD(fld_e1821) + 340))(this);  // 调虚槽 +340：三元组基址（+284，vt+340）
  if ( *(uint32_t *)result == 1 )
  {
    result = (uint16_t *)this + 4185;
    for ( i = 26; i != 0; --i )  // 循环：i 从 26 递减到 0
    {
      *result = 50;
      result += 2;
    }
  }
  return result;
}



// 外观变体装载：Monster/Goblin/{acc9,acc9-2,acc9-3,bcc9,hcc9,weapon9}.equ 六件
// ------------------------------------------------------------
// 0x59ABD0 sub_59ABD0 —— 外观六件套装载：acc9/acc9-2/acc9-3/bcc9/hcc9/weapon9.equ 表驱动循环
// 每件 operator new(0x544) 后 ·0x4BA9E0 构造、vt+784 挂载；与 ·0x5998E0 单件式同构
// 【推断：acc9-2/3 为损伤阶段外观变体】
// ------------------------------------------------------------
int /*thiscall*/ sub_59ABD0(int *this)  // 实现：外观六件套装载：acc9/acc9-2/acc9-3/bcc9/hcc9/weapon9.equ 表驱动循环
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
  for ( i = 0; i < 6; ++i )  // 循环：i 从 0 递增到 6
  {
    pMem = operator new(0x544u);  // new(1348 字节) 分配对象
    v7[6] = pMem;
    v8 = 0;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v4 = sub_4BA9E0((char *)pMem, v7[i], 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
    else  // 否则分支
      v4 = nullptr;  // v4 = 空指针
    v5 = *this;
    v8 = -1;
    result = (*(int (/*thiscall*/ **)(int *, char *))(v5 + 784))(this, v4);
    if ( result != 0 )  // 若结果非 0（成功）
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  }
  return result;
}



// AI 相位辅助（41L）
// ------------------------------------------------------------
// 0x59AC90 sub_59AC90 —— 增益退出对偶：vt+672(0)+830/+858 两浮点各 -0.30 后 vt+676(0) 刷新
// 档 2 且 nArg3=0 时 this+8672 减半；与 ·0x59AD50 入场互逆（其 +0.30、×2）
// ------------------------------------------------------------
int /*thiscall*/ sub_59AC90(uint32_t *this, int nArg2, int nArg3)  // 实现：增益退出对偶：vt+672(0)+830/+858 两浮点各 -0.30 后 vt+676(0) 刷新
{
  int result; // eax
  unsigned int v5; // edi
  int v6; // edx
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+Ch] [ebp+8h]
  int v10; // [esp+Ch] [ebp+8h]

  if ( nArg2 != 0 )  // 若 nArg2 非 0
  {
    result = nArg2 - 2;
    if ( nArg2 == 2 )  // 若 nArg2 == 2
    {
      result = nArg3;
      if ( nArg3 == 0 )  // 若 nArg3 为 0
      {
        result = *(this + 2168) / 2;  // this+8672〔uAI8672(推断)〕
        *(this + 2168) = result;  // this+8672〔uAI8672(推断)〕
      }
    }
  }
  else  // 否则分支
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v5, v6, v9);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;  // 调虚槽 +672：自身 HP
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v7)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v7, v8, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  return result;
}



// AI 相位辅助（75L）
// ------------------------------------------------------------
// 0x59AD50 sub_59AD50 —— 增益入场：全清 this+7531..7596 判定参数面后按档位填值
// 档 1：this+7564=1、7572=2；档 2：另 this+7596=50 且 nArg3=0 时 this+8672 ×2；
// 档 0：this+7596=50 并对 vt+672(0)+830/+858 两浮点 +0.30 后 vt+676(0) 刷新
// 退出对偶见 ·0x59AC90【推断：狂暴化增益，浮点=移速/攻速系数】
// ------------------------------------------------------------
int /*thiscall*/ sub_59AD50(char *this, int nArg2, int nArg3)  // 实现：增益入场：全清 this+7531..7596 判定参数面后按档位填值
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
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  pThis_1D73 = this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *((uint32_t *)this + 1893) = 0;  // this[1893] = 0
  *((uint32_t *)this + 1892) = 0;  // this[1892] = 0
  *((uint32_t *)this + 1891) = 0;  // this[1891] = 0
  *((uint32_t *)this + 1897) = 0;  // this+7588〔uForm7588〕
  *((uint32_t *)this + 1896) = 0;  // this+7584〔uForm7584〕
  *((uint32_t *)this + 1895) = 0;  // this[1895] = 0
  *((uint32_t *)this + 1894) = 0;  // this[1894] = 0
  *((uint32_t *)this + 1899) = 0;  // this[1899] = 0
  if ( nArg2 != 0 )  // 若 nArg2 非 0
  {
    result = nArg2 - 1;
    if ( nArg2 == 1 )  // 若 nArg2 == 1
    {
      *((uint32_t *)this + 1891) = 1;  // this[1891] = 1
      *((uint32_t *)this + 1893) = 2;  // this[1893] = 2
    }
    else  // 否则分支
    {
      result = nArg2 - 2;
      if ( nArg2 == 2 )  // 若 nArg2 == 2
      {
        *((uint32_t *)this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
        *((uint32_t *)this + 1891) = 1;  // this[1891] = 1
        *((uint32_t *)this + 1893) = 2;  // this[1893] = 2
        if ( nArg3 == 0 )  // 若 nArg3 为 0
          *((uint32_t *)this + 2168) *= 2;  // this+8672〔uAI8672(推断)〕
      }
    }
  }
  else  // 否则分支
  {
    v6 = *(uint32_t *)this;
    *((uint32_t *)this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
    v7 = (*(int (/*thiscall*/ **)(char *, uint32_t))(v6 + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v7, v8, v11);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 858;  // 调虚槽 +672：自身 HP
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, v10, v12);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59AEC0 sub_59AEC0 —— 对象移除联动：移除对象匹配 this+8680 时清槽（主状态 14 则 vt+560 清反应态）
// 匹配 this+8684 时清投掷目标并 vt+1104(13)；尾调 ·0x4D9170 基类移除处理
// 【推断：被锁目标死亡/离场时的清理回调】
// ------------------------------------------------------------
int /*thiscall*/ sub_59AEC0(uint32_t *this, int nArg2)  // 实现：对象移除联动：移除对象匹配 this+8680 时清槽（主状态 14 则 vt+560 清反应态）
{
  int result; // eax
  int v4; // eax
  int v5; // edx

  result = sub_4D9170(nArg2);  // result = 调 sub_4D9170 返回值
  if ( nArg2 == *(this + 2170) )  // this+8680〔uGate8680(推断)〕
  {
    v4 = *this;
    *(this + 2170) = 0;  // this+8680〔uGate8680(推断)〕
    result = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result == 14 )  // 若 result == 14
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
      if ( (uint8_t)result != 0 )
        result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    }
  }
  if ( nArg2 == *(this + 2171) )  // this+8684〔bGate8684(推断)〕
  {
    v5 = *this;
    *(this + 2171) = 0;  // this+8684〔bGate8684(推断)〕
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 1104))(this, 13);
  }
  return result;
}



// 登场曲：sub_406D60 写 "BKWALKER_01"（骨头行者 BKWalker 曲目槽）
// ------------------------------------------------------------
// 0x59AF40 sub_59AF40 —— 大状态 6 入场播报：·0x4DBA80 副作用处理后 vt+212 播 BKWALKER_01 登场曲
// 曲目经 sub_406D60 写 BKWalker 曲目槽（见分区头）【推断：骨头行者类变身/登场演出】
// ------------------------------------------------------------
int /*thiscall*/ sub_59AF40(void *this, int nArg2)  // 实现：大状态 6 入场播报：·0x4DBA80 副作用处理后 vt+212 播 BKWALKER_01 登场曲
{
  int result; // eax

  result = sub_4DBA80(nArg2);  // 大状态进入副作用处理器（增益侧）
  if ( nArg2 == 6 )  // 若 nArg2 == 6
    return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "BKWALKER_01",  // 标签 BKWALKER_01
             -1,
             0,
             0);
  return result;
}



// AI 字段访问（this+8604/8684）
// ------------------------------------------------------------
// 0x59AF70 sub_59AF70 —— 大状态退出钩子：态 6 时 this+8604 标志触发 ·0x64BDF0 光环并清 this+8684
// 与 ·0x59A020 同构（差异：本函数另清 this+8684、无态 7 分支）；尾调 ·0x4DBC20 基类副作用
// ------------------------------------------------------------
char /*thiscall*/ sub_59AF70(int this, int nArg2)  // 实现：大状态退出钩子：态 6 时 this+8604 标志触发 ·0x64BDF0 光环并清 this+8684
{
  char result; // al

  result = sub_4DBC20(nArg2);  // 大状态退出副作用处理器（0x4DBA80 的还原对偶）
  if ( nArg2 == 6 )  // 若 nArg2 == 6
  {
    result = *(uint8_t *)(this + 8604);  // result = 读 this+8604
    if ( result != 0 )  // 若结果非 0（成功）
      result = sub_64BDF0(this, *(uint32_t *)(this + 7256));  // 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
    *(uint32_t *)(this + 8684) = 0;  // this+8684〔bGate8684(推断)〕
  }
  return result;
}



// 主状态门（this+200）
// ------------------------------------------------------------
// 0x59AFC0 sub_59AFC0 —— 朝向决策门：主状态 14 且 this+8680 非零时先走 vt+200，其余 ·0x4D8750 默认朝向
// vt+200 返回 0 亦回落 ·0x4D8750【推断：14=特殊态期间朝向跟随另一参照】
// ------------------------------------------------------------
int /*thiscall*/ sub_59AFC0(uint32_t *this)  // 实现：朝向决策门：主状态 14 且 this+8680 非零时先走 vt+200，其余 ·0x4D8750 默认朝向
{
  int result; // eax

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 14 )  // 调虚槽 +840：大状态 getter（this+6556）
    return sub_4D8750(this);  // 朝向决策（依据参照对象 vt+1813 的 x 比较得方向码 0/4）
  if ( *(this + 2170) == 0 )  // this+8680〔uGate8680(推断)〕
    return sub_4D8750(this);  // 朝向决策（依据参照对象 vt+1813 的 x 比较得方向码 0/4）
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  if ( result == 0 )  // 若 result 为 0
    return sub_4D8750(this);  // 朝向决策（依据参照对象 vt+1813 的 x 比较得方向码 0/4）
  return result;
}



// ============================================================
// 【分区 9】哥布林系·指挥官与恐惧（0x59B000-0x59B960）
// 证据：GOBLIN_COMMAND 命令广播（RTTI cast 到友军）、REPAIR_OBJECT 修复、
//       GOBLIN_SCARED 恐惧 AI（sub_699000 时钟门）

// 指挥 AI：vt+212 GOBLIN_COMMAND（RTTI cast 寻友军广播, 56L）
// ------------------------------------------------------------
// 0x59B000 sub_59B000 —— 指挥官命令广播（GOBLIN_COMMAND）：事件 13 解包两对象句柄后下发攻击令
// 句柄对经 ·0x45EBE0 还原对象并 RTTI 校验 CNGoblinGoblin 与 IRDActiveObject，成功则
// ·0x49C510(10, 自身, 哥布林, 目标, 0) 下发、·0x4D82D0 播 Command.ani 气泡、vt+212 播报、
// ·0x4DB200(24, 2/3/4) 随机文案；事件包经 ·0x4DC630 读取【推断：13=指挥官下达协同攻击】
// ------------------------------------------------------------
int /*thiscall*/ sub_59B000(uint32_t *this)  // 实现：指挥官命令广播（GOBLIN_COMMAND）：事件 13 解包两对象句柄后下发攻击令
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

  result = sub_4DC630();  // 关卡/交互事件包处理（关联对象 this+7260 校验）
  v3 = result;
  if ( result != -1 )
  {
    if ( (uint16_t)result == 13 )
    {
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v12);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v13);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v10);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v11);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
      v4 = sub_45EBE0(v12, v13);  // v4 = 调 sub_45EBE0 返回值
      v5 = __RTDynamicCast(v4, 0, &CNRDObject `RTTI Type Descriptor', &CNGoblinGoblin `RTTI Type Descriptor', 0);  // v5 = 调 __RTDynamicCast
      v6 = sub_45EBE0(v10, v11);  // v6 = 调 sub_45EBE0 返回值
      v7 = __RTDynamicCast(v6, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // v7 = 调 __RTDynamicCast
      if ( v5 != 0 && v7 != 0 )  // 若 v5 != 0 与/或 v7 != 0
      {
        sub_49C510(10, *(this + 1), *(uint32_t *)(v5 + 4), v7, 0);  // 命令下发入口（五元组写 dword_9A0250 后 ·sub_4AEA30 派发）
        sub_4D82D0(0, 0);  // 头顶气泡 Command.ani（a2/a3 = 定位偏移）
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
          this,
          "GOBLIN_COMMAND",  // 标签 GOBLIN_COMMAND
          -1,
          0,
          0);
        v9[0] = 2;
        v9[1] = 3;
        v9[2] = 4;
        nRand = rand();  // nRand = 调 rand
        sub_4DB200(24, v9[nRand % 3]);  // 15% 概率随机文案触发（0x4DB130 的门包装）
      }
    }
    return v3;
  }
  return result;
}



// 指挥 AI 扩展（118L；RTTI cast 目标解算）
// ------------------------------------------------------------
// 0x59B130 sub_59B130 —— 协同攻击令组包发送：遍历场景对象列表筛同族可指挥哥布林并广播命令 13
// 过滤：vt+40(529) 类型、vt+376 同组、RTTI cast CNGoblinGoblin、+7148 大状态非 7、vt+1244 可见
// 包体（dword_8F8520）：头 29/2 + 自身坐标（vt+48/52）+ 地图 ID（dword_8F7C04 vt+52）+ 命令 13
// + 指挥官与目标（this+7252 或 nArg4）坐标，vt+60(1,-1) 发送【推断：13=协同攻击指令】
// ------------------------------------------------------------
int /*userpurge*/ sub_59B130@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>, int nArg4)  // 实现：协同攻击令组包发送：遍历场景对象列表筛同族可指挥哥布林并广播命令 13
{
  int result; // eax
  unsigned int i; // esi
  int pScene; // ecx
  int nBegin1; // edx
  int nBegin2; // edx
  int pObjCheck; // ecx
  int pScene2; // ecx
  int nBegin3; // edx
  int pCandidate; // esi
  int nCandRoom; // ebx
  int pGoblin; // eax
  int pGoblin2; // esi
  int nPktVt1; // ebx
  int nSelfKeyA; // eax
  int nPktVt2; // ebx
  int nSelfKeyB; // eax
  int nPktVt3; // ebx
  int nMapId; // eax
  int pTgtGoblin; // edi
  int nPktVt4; // ebx
  int nGobKeyA; // eax
  int nPktVt5; // ebx
  int nGobKeyB; // eax
  int nPktVt6; // esi
  int nTgtKeyA; // eax
  int nPktVt7; // esi
  int nTgtKeyB; // eax
  unsigned int nIdxSave; // [esp+4h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )  // 存活门
  {
    result = pArg1[1813];  // 目标槽（7252 号字）
    if ( result != 0 )  // 若结果非 0（成功）
    {
      for ( i = 0; ; ++i )  // 遍历场景对象表（this+29 的 vector）
      {
        pScene = pArg1[29];  // pScene = 取 pArg1[29]
        nBegin1 = *(uint32_t *)(pScene + 8);
        nIdxSave = i;
        result = nBegin1 != 0 ? (*(uint32_t *)(pScene + 12) - nBegin1) >> 2 : 0;  // 元素个数
        if ( (int)i >= result )
          break;  // 跳出循环/分支
        nBegin2 = *(uint32_t *)(pScene + 8);
        if ( nBegin2 != 0 && i < (*(uint32_t *)(pScene + 12) - nBegin2) >> 2 )  // 若 nBegin2 != 0
          pObjCheck = *(uint32_t *)(nBegin2 + 4 * i);
        else  // 否则分支
          pObjCheck = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjCheck + 40))(pObjCheck, 529) != 0 )  // 类型529=哥布林族【推断】
        {
          pScene2 = pArg1[29];  // pScene2 = 取 pArg1[29]
          nBegin3 = *(uint32_t *)(pScene2 + 8);
          if ( nBegin3 != 0 && i < (*(uint32_t *)(pScene2 + 12) - nBegin3) >> 2 )  // 若 nBegin3 != 0
            pCandidate = *(uint32_t *)(nBegin3 + 4 * i);
          else  // 否则分支
            pCandidate = 0;
          nCandRoom = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCandidate + 376))(pCandidate);  // 候选对象房间号
          if ( nCandRoom == (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 376))(pArg1) )  // 同房间过滤
          {
            pGoblin = __RTDynamicCast(
                    pCandidate,
                    0,
                    &IRDActiveObject `RTTI Type Descriptor',
                    &CNGoblinGoblin `RTTI Type Descriptor',
                    0);
            pGoblin2 = pGoblin;
            if ( pGoblin != 0  // 若 pGoblin 非 0
              && *(uint32_t *)(pGoblin + 7148) != 7  // 大状态非7（非投石态）排除
              && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1244))(pArg1, pGoblin) != 0 )  // 可见性校验
            {
              (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(  // 网络包写入器 开包(29,2,...)
                dword_8F8520,  // 会话/UDP 管理器
                29,
                2,
                nArg2,
                nArg3);
              nPktVt1 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
              nSelfKeyA = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 48))(pArg1);  // 自身句柄A（vt+48）
              (*(void (/*thiscall*/ **)(int, int))(nPktVt1 + 36))(dword_8F8520, nSelfKeyA);  // 会话/UDP 管理器
              nPktVt2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
              nSelfKeyB = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);  // 自身句柄B（vt+52）
              (*(void (/*thiscall*/ **)(int, int))(nPktVt2 + 36))(dword_8F8520, nSelfKeyB);  // 会话/UDP 管理器
              nPktVt3 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
              nMapId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 全局对象句柄（地图侧）
              (*(void (/*thiscall*/ **)(int, int))(nPktVt3 + 36))(dword_8F8520, nMapId);  // 会话/UDP 管理器
              pTgtGoblin = pArg1[1813];  // pTgtGoblin = 取 pArg1[1813]
              if ( nArg4 != 0 )  // 若 nArg4 非 0
                pTgtGoblin = nArg4;  // 调用方可覆盖目标（bypass this+7252）
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 13);  // 命令码 13=协同攻击令
              nPktVt4 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
              nGobKeyA = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pGoblin2 + 48))(pGoblin2);  // 被指挥者句柄A
              (*(void (/*thiscall*/ **)(int, int))(nPktVt4 + 36))(dword_8F8520, nGobKeyA);  // 会话/UDP 管理器
              nPktVt5 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
              nGobKeyB = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pGoblin2 + 52))(pGoblin2);  // 被指挥者句柄B
              (*(void (/*thiscall*/ **)(int, int))(nPktVt5 + 36))(dword_8F8520, nGobKeyB);  // 会话/UDP 管理器
              nPktVt6 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
              nTgtKeyA = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTgtGoblin + 48))(pTgtGoblin);  // 目标句柄A
              (*(void (/*thiscall*/ **)(int, int))(nPktVt6 + 36))(dword_8F8520, nTgtKeyA);  // 会话/UDP 管理器
              nPktVt7 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
              nTgtKeyB = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTgtGoblin + 52))(pTgtGoblin);  // 目标句柄B
              (*(void (/*thiscall*/ **)(int, int))(nPktVt7 + 36))(dword_8F8520, nTgtKeyB);  // 会话/UDP 管理器
              return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 封包发送(1,-1)
            }
          }
          i = nIdxSave;  // 恢复循环下标（外层结构所致，非业务）
        }
      }
    }
  }
  return result;
}


// AI 字段访问
// ------------------------------------------------------------
// 0x59B310 sub_59B310 —— 指挥触发门：存活且 rand < this+8672 概率时调 ·0x59B130 发协同攻击令
// 目标取 this+7256（经 nArg4 覆盖 ·0x59B130 默认目标 this+7252）；前置 ·0x4DE3E0 基类处理
// 【推断：8672=指挥触发概率，可被 ·0x59AD50 档 2 翻倍】
// ------------------------------------------------------------
int /*usercall*/ sub_59B310@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：指挥触发门：存活且 rand < this+8672 概率时调 ·0x59B130 发协同攻击令
{
  int result; // eax
  int nRand; // eax
  int v5; // et2

  sub_4DE3E0();  // （短函数，转写体未含可辨字符串证据；语义待定(待验证)）
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();  // nRand = 调 rand
    v5 = nRand % 100;
    result = nRand / 100;
    if ( v5 < pArg1[2168] )
      return sub_59B130(pArg1, nArg2, (int)pArg1, pArg1[1814]);  // 协同攻击令组包发送：遍历场景对象列表筛同族可指挥哥布林并广播命令 13
  }
  return result;
}



// AI 字段访问（this+8668）
// ------------------------------------------------------------
// 0x59B350 sub_59B350 —— 突进入场（指挥官变体）：vt+1104(5)、速度 ×1.5、置 this+8668、30% 播 this+8616 语音
// 与 ·0x59A080 同构（差异：标志槽 8668、语音槽 8616）
// ------------------------------------------------------------
int /*thiscall*/ sub_59B350(uint32_t *this)  // 实现：突进入场（指挥官变体）：vt+1104(5)、速度 ×1.5、置 this+8668、30% 播 this+8616 语音
{
  int nRand; // eax
  int result; // eax
  int v4; // et2

  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);  // 调虚槽 +1104
  *(float *)(*(this + 1905) + 4) = *(float *)(*(this + 1905) + 4) * 1.5;  // this+7620〔pStatusPanel(推断)〕
  *((uint8_t *)this + 8668) = 1;  // this+8668〔nCool8668(推断)〕
  nRand = rand();  // nRand = 调 rand
  v4 = nRand % 100;
  result = nRand / 100;
  if ( v4 < 30 )  // 若 v4 < 30
  {
    if ( *(this + 2159) < 0x10u )  // this+8636〔pDollTarget(推断)〕
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, this + 2154, -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    else  // 否则分支
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
               this,
               *(this + 2154),  // this+8616〔语音〕
               -1,
               0,
               0);
  }
  return result;
}



// AI 字段访问（this+8668）
// ------------------------------------------------------------
// 0x59B3D0 sub_59B3D0 —— 突进退出（指挥官变体）：清 this+8668、速度 ×0.66666669
// 与 ·0x59A100 同构（差异：目标存活时多 ·0x4DB200(24,8) 随机文案）
// ------------------------------------------------------------
int /*thiscall*/ sub_59B3D0(uint32_t *this)  // 实现：突进退出（指挥官变体）：清 this+8668、速度 ×0.66666669
{
  int result; // eax

  if ( *(this + 1813) != 0  // this+7252〔pTarget7252〕
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1244))(this, *(this + 1813)) != 0 )  // 调虚槽 +1244
  {
    sub_4DB200(24, 8);  // 15% 概率随机文案触发（0x4DB130 的门包装）
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1140))(this, -1, -1);  // 调虚槽 +1140
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
  }
  result = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
  *(float *)(result + 4) = *(float *)(result + 4) * 0.66666669;
  *((uint8_t *)this + 8668) = 0;  // this+8668〔nCool8668(推断)〕
  return result;
}



// 指挥 AI 扩展（71L；RTTI cast）
// ------------------------------------------------------------
// 0x59B430 sub_59B430 —— 寻找待修地堡（CNGoblinBunker）：筛 vt+40(33)、同组、可见且血量比 <=65%
// 血量比 = +680/+684 双字相除；以地堡 vt+124/vt+120 求接近点经 vt+1140 走位，成功记 this+8684
// 【推断：65%=低血量维修阈值，8684 供修复流程使用】
// ------------------------------------------------------------
int /*thiscall*/ sub_59B430(uint32_t *this)  // 实现：寻找待修地堡（CNGoblinBunker）：筛 vt+40(33)、同组、可见且血量比 <=65%
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
  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    v3 = pThis[29];  // v3 = 取 pThis[29]
    v4 = *(uint32_t *)(v3 + 8);
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;  // 跳出循环/分支
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )  // 若 v6 != 0
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else  // 否则分支
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 33) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      v8 = pThis[29];  // v8 = 取 pThis[29]
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )  // 若 v9 != 0
        v10 = *(uint32_t *)(v9 + 4 * i);
      else  // 否则分支
        v10 = 0;
      pObj = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &CNGoblinBunker `RTTI Type Descriptor', 0);  // pObj = 调 __RTDynamicCast
      v12 = (int *)pObj;
      if ( pObj != 0 )  // 若 pObj 非 0
      {
        v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调虚槽 +376：坐标同步包（type 37）
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis);  // 调虚槽 +376：坐标同步包（type 37）
        pThis = this;
        if ( v17 == v13  // 若 v17 == v13
          && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int *))(*this + 1244))(this, v12) != 0  // 调虚槽 +1244
          && (double)v12[170] / (double)v12[171] * 100.0 <= 65.0 )
        {
          v14 = *this;
          v15 = (*(int (/*thiscall*/ **)(int *))(*v12 + 124))(v12);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          v16 = (*(int (/*thiscall*/ **)(int *, int))(*v12 + 120))(v12, v15);  // 调虚槽 +120：动画对象
          result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v14 + 1140))(this, v16);
          if ( (uint8_t)result != 0 )
            *(this + 2171) = v12;  // this+8684〔bGate8684(推断)〕
          return result;
        }
      }
    }
  }
  return result;
}



// 时钟门 AI（sub_699000, 64L）
// ------------------------------------------------------------
// 0x59B550 sub_59B550 —— 指挥官大状态机（this+7148）：与 ·0x59A290 同构
// 差异：相位 4 指挥概率 = this+8672 之半并 ·0x59B130 发协同令、另 10% 调 vt+1312 哨戒；
// 相位 5 突进超时 3000ms 退 ·0x59B3D0（标志槽 8668）；13-15 有目标转 vt+1104(4)
// ------------------------------------------------------------
int /*usercall*/ sub_59B550@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：指挥官大状态机（this+7148）：与 ·0x59A290 同构
{
  int result; // eax
  int nRand; // eax
  int v5; // et2

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = pArg1[1787];  // result = 取 pArg1[1787]
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1284))(pArg1);  // 调虚槽 +1284
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( pArg1[1813] == 0 )
        goto LABEL_6;
      if ( rand() % 100 < pArg1[2168] / 2 )  // rand()%100 取模随机
        sub_59B130(pArg1, nArg2, (int)pArg1, 0);  // 协同攻击令组包发送：遍历场景对象列表筛同族可指挥哥布林并广播命令 13
      nRand = rand();  // nRand = 调 rand
      v5 = nRand % 100;
      result = nRand / 100;
      if ( v5 < 10 )  // 若 v5 < 10
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1312))(pArg1);  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
      break;  // 跳出循环/分支
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      result = pArg1[1813];  // result = 取 pArg1[1813]
      if ( result != 0 )  // 若结果非 0（成功）
      {
        if ( *((uint8_t *)pArg1 + 8668) == 1 )
        {
          result = sub_699000((int)(pArg1 + 1910)) - pArg1[1926];  // 【clock_now(clk)】
          if ( result > 3000 )  // 若 result > 3000
            result = sub_59B3D0(pArg1);  // 突进退出（指挥官变体）：清 this+8668、速度 ×0.66666669
        }
      }
      else  // 否则分支
      {
LABEL_6:  // 标签 LABEL_6（跳转合流点）
        result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 13);  // 调虚槽 +1104
      }
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      result = pArg1[1813];  // result = 取 pArg1[1813]
      if ( result != 0 )  // 若结果非 0（成功）
        goto LABEL_16;
      break;  // 跳出循环/分支
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = pArg1[1813];  // result = 取 pArg1[1813]
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_16:  // 标签 LABEL_16（跳转合流点）
        result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 4);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// AI 字段访问（this+8668）
// ------------------------------------------------------------
// 0x59B680 sub_59B680 —— 态 5/8 钩子（指挥官变体）：态 5 时 50% ·0x64BDF0 光环 + ·0x4DB200(24,5/6) 文案
// 态 8 且 this+8668 置位时播文案 7 并 ·0x59B3D0 退出；与 ·0x59A3F0 同构（差异：文案、无 7028 链分支）
// ------------------------------------------------------------
int /*thiscall*/ sub_59B680(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：态 5/8 钩子（指挥官变体）：态 5 时 50% ·0x64BDF0 光环 + ·0x4DB200(24,5/6) 文案
{
  int result; // eax
  int nRand; // eax
  int v8; // et2
  int nRand2; // eax
  uint32_t v10[2]; // [esp+8h] [ebp-8h]

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 5 )  // 若 ArgList == 5
  {
    nRand = rand();  // nRand = 调 rand
    v8 = nRand % 100;
    result = nRand / 100;
    if ( v8 < 50 )  // 若 v8 < 50
    {
      sub_64BDF0(this, *(uint32_t *)(this + 7256));  // 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
      v10[0] = 5;
      v10[1] = 6;
      nRand2 = rand() % 2;  // nRand2 = 调 rand
      return sub_4DB200(24, v10[nRand2]);  // 15% 概率随机文案触发（0x4DB130 的门包装）
    }
  }
  else if ( ArgList == 8 && *(uint8_t *)(this + 8668) == 1 )  // this+8668〔nCool8668(推断)〕
  {
    sub_4DB200(24, 7);  // 15% 概率随机文案触发（0x4DB130 的门包装）
    return sub_59B3D0((uint32_t *)this);  // 突进退出（指挥官变体）：清 this+8668、速度 ×0.66666669
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59B730 sub_59B730 —— 指挥官帧 tick：先跑 ·0x59B550 状态机，空闲时寻地堡
// 空闲条件：存活、主状态 0、this+7148 非 6、this+8684 无地堡目标 → ·0x59B430
// ------------------------------------------------------------
int /*usercall*/ sub_59B730@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：指挥官帧 tick：先跑 ·0x59B550 状态机，空闲时寻地堡
{
  int result; // eax

  sub_59B550(pArg1, nArg2);  // 指挥官大状态机（this+7148）：与 ·0x59A290 同构
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result == 0 && pArg1[1787] != 6 )  // 若 result == 0
    {
      result = pArg1[2171];  // result = 取 pArg1[2171]
      if ( result == 0 )  // 若 result 为 0
        return sub_59B430(pArg1);  // 寻找待修地堡（CNGoblinBunker）：筛 vt+40(33)、同组、可见且血量比 <=65%
    }
  }
  return result;
}



// 修复技能：vt+212 播报 REPAIR_OBJECT（66L；工程哥布林修复演出）
// ------------------------------------------------------------
// 0x59B780 sub_59B780 —— 修复技能入场（REPAIR_OBJECT）：态 14 解包目标句柄（·0x45EBE0）存 this+8680
// 有效则 vt+888/vt+876 参数复位、动画游标复位（·0x4926A0）后 vt+196 播动作、vt+1104(13)、
// vt+212 播 REPAIR_OBJECT；目标无效且存活则 vt+560(0,0,0,0) 清反应态；非 14 态清 this+8680
// 前置复用 ·0x59B680【推断：工程哥布林对地堡的维修演出入场】
// ------------------------------------------------------------
int /*thiscall*/ sub_59B780(void *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：修复技能入场（REPAIR_OBJECT）：态 14 解包目标句柄（·0x45EBE0）存 this+8680
{
  int result; // eax
  int *v7; // eax
  int v8; // eax
  int v9; // [esp-8h] [ebp-14h]
  int v10; // [esp-4h] [ebp-10h]

  result = sub_59B680((int)this, ArgList, fArg3, nArg4, nArg5);  // 态 5/8 钩子（指挥官变体）：态 5 时 50% ·0x64BDF0 光环 + ·0x4DB200(24,5/6) 文案
  if ( ArgList == 14 )  // 若 ArgList == 14
  {
    v7 = *(int **)(LODWORD(fArg3) + 4);
    v10 = v7[1];  // v10 = 取 v7[1]
    v9 = *v7;
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    v8 = sub_45EBE0(v9, v10);  // v8 = 调 sub_45EBE0 返回值
    *((uint32_t *)this + 2170) = v8;  // this+8680〔uGate8680(推断)〕
    *((uint32_t *)this + 2171) = 0;  // this[2171] = 0
    if ( v8 != 0 )  // 若 v8 非 0
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
      sub_4926A0(**((uint32_t **)this + 1554));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, **((uint32_t **)this + 1554));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1104))(this, 13);  // 调虚槽 +1104
      return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
               this,
               "REPAIR_OBJECT",  // 标签 REPAIR_OBJECT
               -1,
               0,
               0);
    }
    else  // 否则分支
    {
      result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    }
  }
  else  // 否则分支
  {
    *((uint32_t *)this + 2170) = 0;  // this[2170] = 0
  }
  return result;
}



// 恐惧 AI：R_GOBLIN_* 语音 + GOBLIN_SCARED 播报（sub_699000 时钟门, 8668-8676 相位）
// ------------------------------------------------------------
// 0x59B8A0 sub_59B8A0 —— 哥布林恐惧 AI 初始化（语音 TAG + 恐惧参数面 + 相位时钟）
// 语音槽写入 R_GOBLIN_TALK/DMG/DIE 三件套 + GOBLIN_SCARED；this+7320=100、
// this+7324=350、this+7328=500、this+7356=-30 为恐惧触发参数（距离/概率）【推断】；
// this+8668 相位清零、this+8672=10 计数、this+8676=clock_now（sub_699000）时间戳
// ------------------------------------------------------------
int /*thiscall*/ sub_59B8A0(int this)  // 实现：哥布林恐惧 AI 初始化（语音 TAG + 恐惧参数面 + 相位时钟）
{
  int result; // eax

  *(uint32_t *)(this + 6792) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(uint32_t *)(this + 6796) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(uint32_t *)(this + 6800) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(uint32_t *)(this + 6804) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(uint32_t *)(this + 6808) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("GOBLIN_SCARED", 0xDu);  // 【std::string构造赋值】
  *(uint32_t *)(this + 7320) = 100;
  *(uint32_t *)(this + 7356) = -30;
  *(uint32_t *)(this + 7324) = 350;
  *(uint32_t *)(this + 7328) = 500;
  *(uint8_t *)(this + 8668) = 0;  // this+8668〔nCool8668(推断)〕
  result = sub_699000(this + 36);  // 【clock_now(clk)】
  *(uint32_t *)(this + 8676) = result;  // this+8676〔uAI8676(推断)〕
  *(uint32_t *)(this + 8672) = 10;  // this+8672〔uAI8672(推断)〕
  return result;
}



// ============================================================
// 【分区 10】哥布林系·狼牙棒/加洛克/圣装（0x59B960-0x59C290）
// 证据：MorningStar.equ 狼牙棒、GalokArmor.equ 加洛克护甲、CwGobSantaBeard.equ 圣诞胡装、
//       Weapon03/acc1/hcc1/gcc1 标准四件套

// AI 相位辅助
// ------------------------------------------------------------
// 0x59B960 sub_59B960 —— 被抓/叼住反应（vt+560 置反应态 14）
// 读目标 vt+48/52 两字段经 sub_430C80 写入状态参数包，再 vt+560(this,14) 进架招
// 反应态（反应态 14=架招）；两字段疑为攻击者参照值【推断】
// ------------------------------------------------------------
void /*thiscall*/ sub_59B960(void *this, int nArg2)  // 实现：被抓/叼住反应（vt+560 置反应态 14）
{
  int pObj; // esi
  uint8_t v3[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *Src; // [esp+14h] [ebp-18h]
  int v6; // [esp+18h] [ebp-14h]
  void *pThis; // [esp+1Ch] [ebp-10h]
  int v8; // [esp+28h] [ebp-4h]

  pThis = this;
  Block = nullptr;  // Block = 空指针
  Src = nullptr;  // Src = 空指针
  v6 = 0;
  pObj = nArg2;
  v8 = 0;
  nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 48))(nArg2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
  sub_430C80(nullptr, 1, (int)&nArg2);  // uint32 vector 区间插入（同值填充）
  nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  sub_430C80(nullptr, 1, (int)&nArg2);  // uint32 vector 区间插入（同值填充）
  (*(void (/*thiscall*/ **)(void *, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pThis + 560))(pThis, 14, v3, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);
}



// 主状态门（this+200, 57L）
// ------------------------------------------------------------
// 0x59BA50 sub_59BA50 —— 主状态门：接近触发架招 + 蓄力态反击决策
// 前段：vt+308 在场校验且 this+1787==6 时，对 this+2171 目标取其 vt+340 面板
// 半宽+30 与 vt+120/124 坐标做 X/Y 距离检测，命中即 sub_59B960 架招；后段：
// vt+840 大状态==14（蓄力/架招）且 this+2170 目标存活时先 vt+560(目标,4) 受击
// 后置，再按目标血量占比（obj+680/684 ≥65%）或 70% 随机率决定 vt+560(this,0)
// 复位或 sub_59B960 叼住
// ------------------------------------------------------------
void /*thiscall*/ sub_59BA50(int *this)  // 实现：主状态门：接近触发架招 + 蓄力态反击决策
{
  int fld_e2171; // eax | =+0x21EC 字段 x1（证据 005CD360）
  int v3; // edi
  int fld_e21713; // ebx  | +0x21EC → 子类 AI 门字节（CNBunker_Woker；va=0059AF70）
  int fld_e21714; // edi  | +0x21EC → 子类 AI 门字节（CNBunker_Woker；va=0059AF70）
  signed int fld_e21712; // [esp+4h] [ebp-4h]  | +0x21EC → 子类 AI 门字节（CNBunker_Woker；va=0059AF70）

  sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 && *(this + 1787) == 6 )  // 调虚槽 +308：是否本地玩家
  {
    fld_e2171 = *(this + 2171);  // this+8684〔bGate8684(推断)〕
    if ( fld_e2171 != 0 )  // 若 fld_e2171 非 0
    {
      v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2171 + 340))(fld_e2171) + 32) / 2 + 30;  // 调虚槽 +340：三元组基址（+284，vt+340）
      fld_e21712 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2171) + 340))(*(this + 2171)) + 36);  // fld_e21712 = 读 this+2171
      fld_e21713 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2171) + 120))(*(this + 2171));  // 调虚槽 +120：动画对象
      if ( (int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - fld_e21713) < v3 )  // 调虚槽 +120：动画对象
      {
        fld_e21714 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2171) + 124))(*(this + 2171));  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
        if ( (int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - fld_e21714) < fld_e21712 )  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          sub_59B960(this, *(this + 2171));  // 被抓/叼住反应（vt+560 置反应态 14）
      }
    }
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 14  // 调虚槽 +840：大状态 getter（this+6556）
    && *(this + 2170) != 0  // this+8680〔uGate8680(推断)〕
    && (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != 0  // 调虚槽 +200：取动画对象
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) != 0 )  // 调虚槽 +200：取动画对象
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2170) + 308))(*(this + 2170)) != 0 )  // 调虚槽 +308：是否本地玩家
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2170) + 560))(  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        *(this + 2170),  // this+8680〔uGate8680(推断)〕
        4,
        0,
        0,
        0);
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      if ( (double)*(int *)(*(this + 2170) + 680) / (double)*(int *)(*(this + 2170) + 684) * 100.0 >= 65.0  // this+8680〔uGate8680(推断)〕
        || rand() % 100 >= 30 )  // rand()%100 取模随机
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      }
      else  // 否则分支
      {
        sub_59B960(this, *(this + 2170));  // 被抓/叼住反应（vt+560 置反应态 14）
      }
    }
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59BBF0 sub_59BBF0 —— CNAuraMasterBattle 删除包装（标量析构 + bit0 条件 free）
// 调 ·0x59BC20 析构后按 delete 标志位释放 Block（编译器生成的 delete 适配器）
// ------------------------------------------------------------
void */*thiscall*/ sub_59BBF0(void *Block, char pszArg2)  // 实现：CNAuraMasterBattle 删除包装（标量析构 + bit0 条件 free）
{
  sub_59BC20();  // CNAuraMasterBattle 析构（重置虚表后转基类析构 sub_591190）
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59BC20 sub_59BC20 —— CNAuraMasterBattle 析构（重置虚表后转基类析构 sub_591190）
// 战斗光环析构：先把 this 虚表挂回 CNAuraMasterBattle 版本（虚析构进入路径），
// 实体清理全部委托基类析构 sub_591190（链表/子对象/基类降级）
// ------------------------------------------------------------
int /*thiscall*/ sub_59BC20(char *this)  // 实现：CNAuraMasterBattle 析构（重置虚表后转基类析构 sub_591190）
{
  *(uint32_t *)this = &CNAuraMasterBattle::`vftable';  // 构造装配 vftable：CNAuraMasterBattle
  return sub_591190(this);  // CNRDAuraMaster 析构函数
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59BC30 sub_59BC30 —— CNAuraMasterATDFSPEEDUp 删除包装（同构 ·0x59BBF0，析构转 ·0x59BC60）
// scalar deleting dtor：转调析构 ·0x59BC60 后按 pszArg2 bit0 决定 j__free
// ------------------------------------------------------------
void */*thiscall*/ sub_59BC30(void *Block, char pszArg2)  // 实现：CNAuraMasterATDFSPEEDUp 删除包装（同构 ·0x59BBF0，析构转 ·0x59BC60）
{
  sub_59BC60();  // CNAuraMasterATDFSPEEDUp 析构（重置虚表后转基类析构 sub_591190）
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59BC60 sub_59BC60 —— CNAuraMasterATDFSPEEDUp 析构（重置虚表后转基类析构 sub_591190）
// 攻击/移速增益光环（KingGalok 专用）：虚表挂回本类版本后实体清理全交基类析构 sub_591190
// ------------------------------------------------------------
int /*thiscall*/ sub_59BC60(char *this)  // 实现：CNAuraMasterATDFSPEEDUp 析构（重置虚表后转基类析构 sub_591190）
{
  *(uint32_t *)this = &CNAuraMasterATDFSPEEDUp::`vftable';  // 构造装配 vftable：CNAuraMasterATDFSPEEDUp
  return sub_591190(this);  // CNRDAuraMaster 析构函数
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59BC70 sub_59BC70 —— 施放战斗光环 CNAuraMasterBattleGoblinKinol
// sub_4DE410 名称模板+随机倒计时 → vt+700 预处理 → sub_53F6A0 → sub_64C2C0(300,50)
// 战斗动画查询 → new 0x84 构造 Kinol 光环并以 vt+56 绑定宿主（this,this,0,0,0,-1）
// 【推断：300/50 为动画区间参数】
// ------------------------------------------------------------
int /*thiscall*/ sub_59BC70(void *this)  // 实现：施放战斗光环 CNAuraMasterBattleGoblinKinol
{
  uint32_t *pMem; // edi
  uint32_t *pMem2; // ecx

  sub_4DE410();  // 名称模板写入 + 随机倒计时
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
  sub_53F6A0(this);  // 调 收尾路径
  pMem = operator new(0x84u);  // new(132 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
  {
    sub_64C2C0(300, 50);  // 战斗动画查询（5910D0）
    *pMem = &CNAuraMasterBattleGoblinKinol::`vftable';  // 构造装配 vftable：CNAuraMasterBattleGoblinKinol
    pMem2 = pMem;
  }
  else  // 否则分支
  {
    pMem2 = nullptr;  // pMem2 = 空指针
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, void *, void *, uint32_t, uint32_t, uint32_t, int))(*pMem2 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
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
// 0x59BD10 sub_59BD10 —— 加洛克王速度光环 CNAuraMasterATDFSPEEDUp_KingGalok（一次性）
// this+8680 为已施放门（首施后置 1）；vt+1308 预处理 → vt+384 出场参数面 0..3 通道
// 读数 ×0.01 → sub_64C710(300,x,y,z,w) 战斗动画查询 2 → new 0x90 构造光环以 vt+56
// 绑定宿主（同构 ·0x59BC70，差异：带四通道参数与一次性门）
// ------------------------------------------------------------
char /*usercall*/ sub_59BD10@<al>(int pArg1@<ecx>, int nArg2@<edi>)  // 实现：加洛克王速度光环 CNAuraMasterATDFSPEEDUp_KingGalok（一次性）
{
  char result; // al
  uint32_t *pMem; // edi
  uint32_t *pMem2; // ecx
  float v6; // [esp+8h] [ebp-1Ch]
  float v7; // [esp+Ch] [ebp-18h]
  float v8; // [esp+10h] [ebp-14h]
  float v9; // [esp+14h] [ebp-10h]

  sub_4E1780((uint32_t *)pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  result = *(uint8_t *)(pArg1 + 8680);  // pArg1+8680〔uGate8680(推断)〕
  if ( result == 0 )  // 若 result 为 0
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1308))(pArg1);  // 调虚槽 +1308：CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
    v6 = (double)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 384))(pArg1, 0) * 0.0099999998;  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
    v7 = (double)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 1) * 0.0099999998;  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
    v8 = (double)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 2) * 0.0099999998;  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
    v9 = (double)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 3) * 0.0099999998;  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 700))(pArg1, pArg1);  // 调虚槽 +700：读 +6296 槽
    sub_53F6A0(nArg2);  // 调 收尾路径
    pMem = operator new(0x90u);  // new(144 字节) 分配对象
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
    {
      sub_64C710(300, LODWORD(v6), LODWORD(v7), LODWORD(v8), LODWORD(v9));  // 战斗动画查询 2（5910D0）
      *pMem = &CNAuraMasterATDFSPEEDUp_KingGalok::`vftable';  // 构造装配 vftable：CNAuraMasterATDFSPEEDUp_KingGalok
      pMem2 = pMem;
    }
    else  // 否则分支
    {
      pMem2 = nullptr;  // pMem2 = 空指针
    }
    result = (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t))(*pMem2 + 56))(pMem2, pArg1, pArg1, 0, 0, 0);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    *(uint8_t *)(pArg1 + 8680) = 1;  // pArg1+8680〔uGate8680(推断)〕
  }
  return result;
}



// 狼牙棒哥布林装载：Monster/Goblin/{hcc1,gcc1,Weapon03,acc1}.equ（55L）
// ------------------------------------------------------------
// 0x59BE40 sub_59BE40 —— 狼牙棒哥布林外观装载（标准四件套）
// sub_4BA9E0（.equ 外观挂装）逐件构造后经 vt+784 挂装槽装入并置 vt+4(1) 生效：
// Monster/Goblin/{hcc1, gcc1, Weapon03（狼牙棒武器）, acc1}.equ
// ------------------------------------------------------------
int /*thiscall*/ sub_59BE40(void *this)  // 实现：狼牙棒哥布林外观装载（标准四件套）
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

  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/hcc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v3 = nullptr;  // v3 = 空指针
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_310 != 0 )  // 若 pThis_310 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/gcc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v6 = nullptr;  // v6 = 空指针
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_3102 != 0 )  // 若 pThis_3102 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem3 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v9 = sub_4BA9E0(pMem3, "Monster/Goblin/Weapon03.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v9 = nullptr;  // v9 = 空指针
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v9);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_3103 != 0 )  // 若 pThis_3103 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem4 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v12 = sub_4BA9E0(pMem4, "Monster/Goblin/acc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v12 = nullptr;  // v12 = 空指针
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v12);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  return result;
}



// 圣诞外观：Monster/Goblin/CwGobSantaBeard.equ（CwGob=圣诞哥布林换装）
// ------------------------------------------------------------
// 0x59BF90 sub_59BF90 —— 圣诞哥布林换装（CwGobSantaBeard.equ 圣诞胡装）
// 先清 this+2170/2171 两目标槽与 this+8605 出场标志，再单件挂装圣诞胡装
// ------------------------------------------------------------
int /*thiscall*/ sub_59BF90(uint32_t *this)  // 实现：圣诞哥布林换装（CwGobSantaBeard.equ 圣诞胡装）
{
  char *pMem; // eax
  char *v3; // eax
  int result; // eax

  *(this + 2170) = 0;  // this+8680〔uGate8680(推断)〕
  *(this + 2171) = 0;  // this+8684〔bGate8684(推断)〕
  *((uint8_t *)this + 8605) = 0;  // this+8605〔出场标志〕
  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/CwGobSantaBeard.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v3 = nullptr;  // v3 = 空指针
  result = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  return result;
}



// 加洛克装甲装载：{hcc1,gcc1,MorningStar,acc1}.equ + GalokArmor.equ + acc4.equ（83L）
// ------------------------------------------------------------
// 0x59C020 sub_59C020 —— 加洛克装甲外观装载（六件套 + 1.2 系数面）
// 挂装 {hcc1, gcc1, MorningStar（狼牙棒）, acc1, GalokArmor（加洛克护甲）, acc4}.equ
// 后调 vt+688 收尾；sub_4EB2C0(1.2) + 6 次 sub_4EB6A0(1.2) 逐部位设 1.2 缩放系数
// 【推断：4EB2C0/4EB6A0 为部件缩放/攻击系数设置】
// ------------------------------------------------------------
int /*thiscall*/ sub_59C020(void *this)  // 实现：加洛克装甲外观装载（六件套 + 1.2 系数面）
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

  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  v3 = nullptr;  // v3 = 空指针
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v20 = sub_4BA9E0(pMem, "Monster/Goblin/hcc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v20 = nullptr;  // v20 = 空指针
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v20);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_310 != 0 )  // 若 pThis_310 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v19 = sub_4BA9E0(pMem2, "Monster/Goblin/gcc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v19 = nullptr;  // v19 = 空指针
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v19);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_3102 != 0 )  // 若 pThis_3102 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem3 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v18 = sub_4BA9E0(pMem3, "Monster/Goblin/MorningStar.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v18 = nullptr;  // v18 = 空指针
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v18);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_3103 != 0 )  // 若 pThis_3103 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem4 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    Block = sub_4BA9E0(pMem4, "Monster/Goblin/acc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    Block = nullptr;  // Block = 空指针
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, Block);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_3104 != 0 )  // 若 pThis_3104 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem5 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v12 = sub_4BA9E0(pMem5, "Monster/Goblin/GalokArmor.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v12 = nullptr;  // v12 = 空指针
  pThis_3105 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v12);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_3105 != 0 )  // 若 pThis_3105 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3105 + 4))(pThis_3105, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem6 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
    v3 = sub_4BA9E0(pMem6, "Monster/Goblin/acc4.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  pThis_3106 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_3106 != 0 )  // 若 pThis_3106 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3106 + 4))(pThis_3106, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 688))(this);  // 调虚槽 +688：附加块基址 this+6160
  sub_4EB2C0(1.2);  // 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  sub_4EB6A0(1.2);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(1.2);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(1.2);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(1.2);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(1.2);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  return sub_4EB6A0(1.2);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
}



// ============================================================
// 【分区 11】哥布林系·炸弹兵与 PRAG（0x59C290-0x59CEC0）
// 证据：Particle/AimingBomb.ptl + Bomb.ptl 投弹双粒子（0x59C5C0/0x59C810）、
//       GOBLIN_COMMAND 指挥、PRAG_01 登场曲（0x59C9E0）

// 狼牙棒装载 2：{hcc1,gcc1,MorningStar,acc1}.equ（59L）
// ------------------------------------------------------------
// 0x59C290 sub_59C290 —— 狼牙棒装载 2（同构 ·0x59C020，差异：四件无 GalokArmor/acc4，系数 1.2→1.1）
// 资源：bcc1/acc1/hcc5/gcc1.equ 四件外观（比装甲版少两件）；vt+384 读等系数面时
// 速度类倍率取 1.1（装甲版 1.2）
// ------------------------------------------------------------
int /*thiscall*/ sub_59C290(void *this)  // 实现：狼牙棒装载 2（同构 ·0x59C020，差异：四件无 GalokArmor/acc4，系数 1.2→1.1）
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

  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  v3 = nullptr;  // v3 = 空指针
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v14 = sub_4BA9E0(pMem, "Monster/Goblin/hcc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v14 = nullptr;  // v14 = 空指针
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v14);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_310 != 0 )  // 若 pThis_310 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    Block = sub_4BA9E0(pMem2, "Monster/Goblin/gcc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    Block = nullptr;  // Block = 空指针
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, Block);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_3102 != 0 )  // 若 pThis_3102 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem3 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v8 = sub_4BA9E0(pMem3, "Monster/Goblin/MorningStar.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v8 = nullptr;  // v8 = 空指针
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v8);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_3103 != 0 )  // 若 pThis_3103 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem4 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v3 = sub_4BA9E0(pMem4, "Monster/Goblin/acc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pThis_3104 != 0 )  // 若 pThis_3104 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 688))(this);  // 调虚槽 +688：附加块基址 this+6160
  sub_4EB2C0(1.1);  // 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  sub_4EB6A0(1.1);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(1.1);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(1.1);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  return sub_4EB6A0(1.1);  // this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
}



// 子类扩展字段复位（this+8612..8656）
// ------------------------------------------------------------
// 0x59C440 sub_59C440 —— 子类扩展字段复位（this+8612..8656）
// this+8612 投弹一次性门清零、this+8616/8624 计数清零、this+8620=0xFFFF（定时器
// 满值初值）、this+8656=3（相位/段数初值）【推断：8620/8656 具体语义】
// ------------------------------------------------------------
int /*thiscall*/ sub_59C440(int this)  // 实现：子类扩展字段复位（this+8612..8656）
{
  *(uint8_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint32_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  *(uint32_t *)(this + 8620) = 0xFFFF;  // this+8620〔uAI8620(推断)〕
  *(uint32_t *)(this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
  *(uint32_t *)(this + 8656) = 3;  // this+8656〔uPair8656(推断)〕
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59C470 sub_59C470 —— 段数计数槽减半（this+2165/2166）
// nArg2==0：清 this+1899 并把 this+2165 减半；nArg2==1：把 this+2166 减半，
// nArg3==2 时再叠加 2165 减半；疑为受扰/受击后的攻击段数削减【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_59C470(uint32_t *this, int nArg2, int nArg3)  // 实现：段数计数槽减半（this+2165/2166）
{
  int result; // eax

  if ( nArg2 == 0 )  // 若 nArg2 为 0
  {
    *(this + 1899) = 0;  // this+7596〔nOffset7596(推断)〕
LABEL_6:  // 标签 LABEL_6（跳转合流点）
    result = *(this + 2165) / 2;  // this+8660〔uEvt8660(推断)〕
    *(this + 2165) = result;  // this+8660〔uEvt8660(推断)〕
    return result;
  }
  result = nArg2 - 1;
  if ( nArg2 == 1 )  // 若 nArg2 == 1
  {
    result = *(this + 2166) / 2;  // this+8664〔uAI8664(推断)〕
    *(this + 2166) = result;  // this+8664〔uAI8664(推断)〕
    if ( nArg3 == 2 )  // 若 nArg3 == 2
      goto LABEL_6;
  }
  return result;
}



// AI 相位门（this+8660/8664）
// ------------------------------------------------------------
// 0x59C4C0 sub_59C4C0 —— AI 相位门参数面复位/倍增（this+7531..7596 + 8660/8664）
// 先整面清零 7531..7596 攻击参数面；nArg2==0：this+8660 相位计时 ×2 且 7596=-100；
// nArg2==1：8664 ×2、7580=1、7572=2（nArg3==2 时 8660 亦 ×2）；nArg2==2：仅设
// 7580=1、7572=2；疑为难度/狂暴化的节奏倍率调整【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_59C4C0(int this, int nArg2, int nArg3)  // 实现：AI 相位门参数面复位/倍增（this+7531..7596 + 8660/8664）
{
  int result; // eax
  int fld_21D4; // edx | =+0x21D4 字段 x1

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  if ( nArg2 != 0 )  // 若 nArg2 非 0
  {
    if ( nArg2 == 1 )  // 若 nArg2 == 1
    {
      result = 2;
      *(uint32_t *)(this + 8664) *= 2;  // this+8664〔uAI8664(推断)〕
      *(uint32_t *)(this + 7580) = 1;  // this+7580〔uSegDefault7580(推断)〕
      *(uint32_t *)(this + 7572) = 2;  // this+7572〔uGrade7572(推断)〕
      if ( nArg3 == 2 )  // 若 nArg3 == 2
      {
        result = 2 * *(uint32_t *)(this + 8660);
        *(uint32_t *)(this + 8660) = result;  // this+8660〔uEvt8660(推断)〕
      }
    }
    else if ( nArg2 == 2 )
    {
      *(uint32_t *)(this + 7580) = 1;  // this+7580〔uSegDefault7580(推断)〕
      *(uint32_t *)(this + 7572) = 2;  // this+7572〔uGrade7572(推断)〕
    }
  }
  else  // 否则分支
  {
    fld_21D4 = 2 * *(uint32_t *)(this + 8660);
    *(uint32_t *)(this + 7596) = -100;  // this+7596〔nOffset7596(推断)〕
    *(uint32_t *)(this + 8660) = fld_21D4;  // this+8660〔uEvt8660(推断)〕
  }
  return result;
}



// 投弹技能：Particle/AimingBomb.ptl 瞄准 + Particle/Bomb.ptl 落点（73L）
// ------------------------------------------------------------
// 0x59C5C0 sub_59C5C0 —— 投弹：AimingBomb 瞄准弹 / 无预测直落弹
// this+1813 目标存活且 vt+1244 校验通过时装载 Particle/AimingBomb.ptl（vt+588 模板
// 查询），按 2×距离/初速 ×1.7 算飞行时长并以 vt+164 预测落点；否则直落
// Particle/Bomb.ptl；this+2167 效果 ID==30021 时模板 byte22=3 变体，最后经
// vt+580 以 this+2167 发射（60=生存帧参数）
// ------------------------------------------------------------
int /*thiscall*/ sub_59C5C0(uint32_t *this)  // 实现：投弹：AimingBomb 瞄准弹 / 无预测直落弹
{
  int v2; // esi
  uint64_t fld_e1813; // rax | =+0x1C54 字段 x1
  int fld_e18132; // eax
  int v5; // edx
  int fld_e2167; // eax | =+0x21DC 字段 x3（证据 005A82B0）
  uint32_t v8[26]; // [esp+10h] [ebp-68h] BYREF

  v8[25] = dword_796E50;
  sub_423A20(v8);  // 小结构初始化（0-100 刻度）
  if ( *(this + 1813) != 0  // this+7252〔pTarget7252〕
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1244))(this, *(this + 1813)) != 0 )  // 调虚槽 +1244
  {
    qmemcpy(
      v8,
      (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/AimingBomb.ptl"),  // 调虚槽 +588
      0x62u);
    v2 = (uint64_t)((double)(int)(uint64_t)((double)(2 * *(uint32_t *)((char *)&v8[7] + 3))
                                                          / (double)v8[17]
                                                          * 1000.0)
                          * 1.7);
    fld_e1813 = (uint64_t)((double (/*fastcall*/ *)(uint32_t *, uint32_t, uint32_t, uint32_t))*(uint32_t *)(*this + 164))(  // 调虚槽 +164：★ 与目标朝向角度（atan2 角度制；3D 俯视判定）【新发现(会话 3)】
                             this,
                             (uint64_t)((double)(int)(uint64_t)((double)(2
                                                                                       * *(uint32_t *)((char *)&v8[7] + 3))
                                                                              / (double)v8[17]
                                                                              * 1000.0)
                                              * 1.7) >> 32,
                             *(this + 1813),  // this+7252〔pTarget7252〕
                             0);
    HIDWORD(fld_e1813) = *this;
    v8[18] = fld_e1813;
    fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(HIDWORD(fld_e1813) + 8))(this, *(this + 1813), 0);  // this+7252〔pTarget7252〕
    v5 = *this;
    *(uint32_t *)((char *)&v8[3] + 3) = 1000 * fld_e18132 / v2;
    *(uint32_t *)((char *)&v8[4] + 3) = 1000
                                    * (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(v5 + 8))(  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTT…
                                        this,
                                        *(this + 1813),  // this+7252〔pTarget7252〕
                                        0)
                                    / v2;
  }
  else  // 否则分支
  {
    qmemcpy(
      v8,
      (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/Bomb.ptl"),  // 调虚槽 +588
      0x62u);
  }
  fld_e2167 = *(this + 2167);  // this+8668〔nCool8668(推断)〕
  if ( fld_e2167 == 30021 )  // 若 fld_e2167 == 30021
    BYTE1(v8[22]) = 3;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
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
// 0x59C700 sub_59C700 —— 哥布林指挥官：广播 GOBLIN_COMMAND 召唤掷石兵
// 遍历 this+29 单位列表，vt+40(obj,17) 类型校验且 vt+376 阵营一致、RTTI 动转
// CNGoblinStoner（掷石兵）、vt+156 距离 ≤300 时：取 this+1813 目标坐标经
// sub_49C620(7,坐标) 落点标记 + sub_4D82D0 气泡 + vt+212 播报 GOBLIN_COMMAND
// ------------------------------------------------------------
int /*thiscall*/ sub_59C700(uint32_t *this)  // 实现：哥布林指挥官：广播 GOBLIN_COMMAND 召唤掷石兵
{
  unsigned int i; // edi
  int fld_e29; // ecx | =+0x0074 字段 x2（证据 005FD6C0）
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // edi
  int v11; // ebx
  int v12; // eax
  int fld_e1813; // eax | =+0x1C54 字段 x1
  int v14; // [esp+0h] [ebp-10h]
  unsigned int v15; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v4 = *(uint32_t *)(fld_e29 + 8);
    v15 = i;
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;  // 跳出循环/分支
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 若 v6 != 0
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else  // 否则分支
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 若 v9 != 0
        pObj = *(uint32_t *)(v9 + 4 * i);
      else  // 否则分支
        pObj = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调虚槽 +376：坐标同步包（type 37）
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )  // 调虚槽 +376：坐标同步包（type 37）
      {
        v12 = __RTDynamicCast(
                pObj,
                0,
                &IRDActiveObject `RTTI Type Descriptor',
                &CNGoblinStoner `RTTI Type Descriptor',
                0);
        if ( v12 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 156))(this, v12) <= 300 )  // 调虚槽 +156：与目标 x/y 距离绝对值
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813), 0);  // this+7252〔pTarget7252〕
          sub_49C620(7, fld_e1813, v14);  // 命令下发包装（组 id = this+4，值重复两遍）
          sub_4D82D0(0, 0);  // 头顶气泡 Command.ani（a2/a3 = 定位偏移）
          v14 = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*this + 212))(this, "GOBLIN_COMMAND", -1, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
        }
      }
      i = v15;
    }
  }
  return result;
}



// 投弹技能 2：AimingBomb.ptl + Bomb.ptl（94L）
// ------------------------------------------------------------
// 0x59C810 sub_59C810 —— 投弹 2（带目标搜索门槛，同构 ·0x59C5C0）
// sub_4E0CD0(17,..) 目标收集计数 <2 或所选目标 vt+8 校验 ≥200 失败则返回 0 不投；
// 通过后与 ·0x59C5C0 同链：AimingBomb.ptl 预测落点 ×1.7 / Bomb.ptl 直落，
// 效果 30021 时 byte22=3，vt+580 发射并返回 1
// ------------------------------------------------------------
char /*usercall*/ sub_59C810@<al>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 实现：投弹 2（带目标搜索门槛，同构 ·0x59C5C0）
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
  Block = nullptr;  // Block = 空指针
  v13 = 0;
  v14 = 0;
  v16[28] = 0;
  if ( (int)sub_4E0CD0(17, 0, v11, -1) < 2  // 按条件号收集对象（阵营/距离/归属过滤，返回计数）
    || (*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(**(uint32_t **)Block + 8))(  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTT…
         *(uint32_t *)Block,
         *((uint32_t *)Block + 1),
         0) >= 200 )
  {
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
    return 0;
  }
  else  // 否则分支
  {
    sub_423A20(v16);  // 小结构初始化（0-100 刻度）
    v3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 1244))(pArg1, *(uint32_t *)Block, nArg2);  // 调虚槽 +1244
    v4 = *pArg1;
    if ( v3 != 0 )  // 若 v3 非 0
    {
      qmemcpy(
        v16,
        (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(v4 + 588))(pArg1, "Particle/AimingBomb.ptl"),  // 粒子 .ptl Particle/AimingBomb.ptl
        0x62u);
      v15 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v16[7] + 3)) / (double)v16[17] * 1000.0);
      v5 = (uint64_t)((double)v15 * 1.7);
      v6 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, uint32_t, uint32_t))*(uint32_t *)(*pArg1 + 164))(  // 调虚槽 +164：★ 与目标朝向角度（atan2 角度制；3D 俯视判定）【新发现(会话 3)】
                               pArg1,
                               *(uint32_t *)Block,
                               0);
      HIDWORD(v6) = *pArg1;
      v16[18] = v6;
      v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(HIDWORD(v6) + 8))(pArg1, *(uint32_t *)Block, 0);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTT…
      v8 = *pArg1;
      *(uint32_t *)((char *)&v16[3] + 3) = 1000 * v7 / v5;
      *(uint32_t *)((char *)&v16[4] + 3) = 1000
                                       * (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(v8 + 8))(  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTT…
                                           pArg1,
                                           *(uint32_t *)Block,
                                           0)
                                       / v5;
    }
    else  // 否则分支
    {
      qmemcpy(
        v16,
        (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(v4 + 588))(pArg1, "Particle/Bomb.ptl"),  // 粒子 .ptl Particle/Bomb.ptl
        0x62u);
    }
    v9 = pArg1[2167];  // v9 = 取 pArg1[2167]
    if ( v9 == 30021 )  // 若 v9 == 30021
      BYTE1(v16[22]) = 3;
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 调虚槽 +580
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
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
    return 1;  // 返回 1(成功)
  }
}



// 登场曲：sub_406D60 写 "PRAG_01"（普拉格曲目槽, 71L）
// ------------------------------------------------------------
// 0x59C9E0 sub_59C9E0 —— 掷石哥布林相位机（大状态 8 + this+1757 相位 0/3/4）
// 相位 4：vt+580 发效果 30043 + vt+212 播报 PRAG_01 登场曲；相位 3：vt+308 校验后
// sub_59C810 投弹、失败回退 sub_59C5C0；相位 0：vt+580 以 this+2155（效果 ID）/
// this+2156/this+2154（FastThrowStone.ptl 槽）速投 + vt+212 播报 this+2158 文案
// （THROW_STONE 语音）；this+8612 一次性门防重入，收尾 sub_4E1780
// ------------------------------------------------------------
char /*usercall*/ sub_59C9E0@<al>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 实现：掷石哥布林相位机（大状态 8 + this+1757 相位 0/3/4）
{
  int v3; // edi
  uint32_t *v5; // eax

  if ( pArg1[1639] == 8 )
  {
    v3 = (int)(pArg1 + 1757);
    if ( sub_41A5E0((unsigned int)(pArg1 + 1757)) == 4 && *(uint8_t *)(pArg1[30] + 170) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 308))(pArg1, nArg2) != 0 )  // 调虚槽 +308：是否本地玩家
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 调虚槽 +580
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
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*pArg1 + 212))(pArg1, "PRAG_01", -1, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    }
    if ( *((uint8_t *)pArg1 + 8612) == 0 && *(int *)(pArg1[30] + 148) > 2 )  // 复合条件判定（与/或）
    {
      if ( sub_41A5E0((unsigned int)(pArg1 + 1757)) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 && sub_59C810(pArg1, v3) == 0 )  // 投弹 2（带目标搜索门槛，同构 ·0x59C5C0）
        {
          sub_59C5C0(pArg1);  // 投弹：AimingBomb 瞄准弹 / 无预测直落弹
          *((uint8_t *)pArg1 + 8612) = 1;
          return sub_4E1780(pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
        }
      }
      else if ( sub_41A5E0((unsigned int)(pArg1 + 1757)) == 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 308))(pArg1, nArg2) != 0 )  // 调虚槽 +308：是否本地玩家
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 调虚槽 +580
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
        else  // 否则分支
          v5 = (uint32_t *)pArg1[2158];
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t))(*pArg1 + 212))(pArg1, v5, -1, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      }
      *((uint8_t *)pArg1 + 8612) = 1;
    }
  }
  return sub_4E1780(pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// 参数打包 AI（90L sub_431230）
// ------------------------------------------------------------
// 0x59CB40 sub_59CB40 —— 掷石哥布林行为字分发器（this+1787 switch）
// sub_4E0120 前置；case 1 追击：有目标时按 rand 对 this+2166/2165/1909 概率槽
// 分层决策 → vt+1104 切行为字（2/3/18，2164=3 连投计数）或 sub_59C700 指挥，
// 无目标 → 行为字 15；case 0xF/0xD：目标存在 → 行为字 1；case 0x12：this+1639==0
// 时 --this+2164 并经 sub_431230 打包参数 vt+560(this,8) 置攻击反应，计数归零回 1
// 【推断：vt+1104 为行为字（this+1787）写入器】
// ------------------------------------------------------------
void /*thiscall*/ sub_59CB40(uint32_t *this)  // 实现：掷石哥布林行为字分发器（this+1787 switch）
{
  int v2; // edx
  int fld_e29; // edi | =+0x0074 字段 x2（证据 005FD6C0）
  int fld_e1813; // ebx | =+0x1C54 字段 x1
  int v5; // ebx
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v7[4]; // [esp+14h] [ebp-10h] BYREF

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( *(this + 1787) )  // this+7148〔nBigState〕
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      goto LABEL_9;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
      {
        if ( rand() % 100 >= *(this + 2166) )  // this+8664〔uAI8664(推断)〕
        {
          if ( rand() % 100 >= *(this + 2165) )  // this+8660〔uEvt8660(推断)〕
          {
            if ( rand() % 100 >= 20 * ((*(this + 1909) == 0) + 1) )  // this+7636〔nPosWinY〕
            {
              if ( rand() % 100 < 5 )  // 5% 概率触发（rand()%100 < 5）
              {
                fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);  // fld_e29 = 读 this+29
                fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
                if ( (int)abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - fld_e1813) <= 60  // 调虚槽 +120：动画对象
                  && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) > 40 )  // 调虚槽 +120：动画对象
                {
                  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调虚槽 +120：动画对象
                  if ( v5 < sub_425050(fld_e29) - 40 )  // 总宽换算
                    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 3);  // 调虚槽 +1104
                }
              }
            }
            else  // 否则分支
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 2);  // 调虚槽 +1104
            }
          }
          else  // 否则分支
          {
            v2 = *this;
            *(this + 2164) = 3;  // this+8656〔uPair8656(推断)〕
            (*(void (/*thiscall*/ **)(uint32_t *, int))(v2 + 1104))(this, 18);
          }
        }
        else  // 否则分支
        {
          sub_59C700(this);  // 哥布林指挥官：广播 GOBLIN_COMMAND 召唤掷石兵
        }
      }
      else  // 否则分支
      {
LABEL_9:  // 标签 LABEL_9（跳转合流点）
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);  // 调虚槽 +1104
      }
      return;
    case 0xD:
      goto LABEL_21;
    case 0xF:
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
LABEL_21:  // 标签 LABEL_21（跳转合流点）
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 1);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 0x12:
      if ( *(this + 1639) == 0 )  // this+6556〔大状态ID〕
      {
        --*(this + 2164);  // this+8656〔uPair8656(推断)〕
        memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
        v7[3] = 0;
        v7[0] = 0;
        sub_431230((int)pBuf, v7);  // uint32 vector push_back
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        if ( *(this + 2164) == 0 )  // this+8656〔uPair8656(推断)〕
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 1);  // 调虚槽 +1104
        sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      }
      break;  // 跳出循环/分支
    default:  // 默认分支
      return;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59CDB0 sub_59CDB0 —— 速投相位分支（同构 ·0x59C9E0，差异：无 PRAG_01/30043 分支）
// 门更严：vt+308 && this+1639==8 && 相位 1757==0 && this+8612 未置 && 目标 +148>2；
// this+1787==18 或 1908/1909 置位或 rand≥20% 直接速投（2155/2156/2154 三槽 +
// vt+212 播报 2158 文案），否则 sub_59C810 失败回退 sub_59C5C0；收尾 sub_4E1780
// ------------------------------------------------------------
char /*usercall*/ sub_59CDB0@<al>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 实现：速投相位分支（同构 ·0x59C9E0，差异：无 PRAG_01/30043 分支）
{
  uint32_t *v4; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0  // 调虚槽 +308：是否本地玩家
    && pArg1[1639] == 8
    && sub_41A5E0((unsigned int)(pArg1 + 1757)) == 0  // crypt4byte 解密校验（·0x41A590 逆运算）
    && *((uint8_t *)pArg1 + 8612) == 0
    && *(int *)(pArg1[30] + 148) > 2 )
  {
    if ( pArg1[1787] == 18 || pArg1[1908] != 0 || pArg1[1909] != 0 || rand() % 100 >= 20 )  // 复合条件判定（与/或）
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 调虚槽 +580
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
      else  // 否则分支
        v4 = (uint32_t *)pArg1[2158];
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, v4, -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    }
    else if ( sub_59C810(pArg1, nArg2) == 0 )  // 投弹 2（带目标搜索门槛，同构 ·0x59C5C0）
    {
      sub_59C5C0(pArg1);  // 投弹：AimingBomb 瞄准弹 / 无预测直落弹
      *((uint8_t *)pArg1 + 8612) = 1;
      return sub_4E1780(pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
    }
    *((uint8_t *)pArg1 + 8612) = 1;
  }
  return sub_4E1780(pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// ============================================================
// 【分区 12】哥布林系·速投/火冰导弹/狂气光环（0x59CEC0-0x59E230）
// 证据：Particle/FastThrowStone.ptl 速投、PassiveObject/Common/Particle/
//       FireMissile.ptl 与 IceMissile.ptl 属性导弹、AURA_FURY 狂气光环（0x59DEE0）

// 速投哥布林装载：R_GOBLIN_* 语音 + {tcc2-3,acc2,hcc3-3,gcc1,acc1,bcc1-2}.equ
//   + Particle/FastThrowStone.ptl 速投粒子（98L）
// ------------------------------------------------------------
// 0x59CEC0 sub_59CEC0 —— 速投哥布林装载（语音 + 六件套 + FastThrowStone 粒子槽）
// this+1698..1702 语音槽配置（2/2/2/3/4，同构 ·0x59B8A0 的 6792..6808 面）+
// R_GOBLIN 三件套；挂装 {tcc2-3, acc2, hcc3-3, gcc1, acc1, bcc1-2}.equ；this+2154
// = vt+588 查 Particle/FastThrowStone.ptl、this+2155=30075 效果 ID、THROW_STONE
// 语音、this+1829/1870=500 射程、this+2165/2166=10/5 概率槽、this+2167=vt+384 通道 0
// ------------------------------------------------------------
int /*thiscall*/ sub_59CEC0(uint32_t *this)  // 实现：速投哥布林装载（语音 + 六件套 + FastThrowStone 粒子槽）
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

  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/tcc2-3.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v3 = nullptr;  // v3 = 空指针
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/acc2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v6 = nullptr;  // v6 = 空指针
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj2 != 0 )  // 若 pObj2 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem3 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v9 = sub_4BA9E0(pMem3, "Monster/Goblin/hcc3-3.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v9 = nullptr;  // v9 = 空指针
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v9);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj4 != 0 )  // 若 pObj4 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem4 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v12 = sub_4BA9E0(pMem4, "Monster/Goblin/gcc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v12 = nullptr;  // v12 = 空指针
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj3 != 0 )  // 若 pObj3 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem5 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v15 = sub_4BA9E0(pMem5, "Monster/Goblin/acc1.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v15 = nullptr;  // v15 = 空指针
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v15);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj5 != 0 )  // 若 pObj5 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem6 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
    v18 = sub_4BA9E0(pMem6, "Monster/Goblin/bcc1-2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v18 = nullptr;  // v18 = 空指针
  pObj6 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj6 != 0 )  // 若 pObj6 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 4))(pObj6, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  *(this + 2154) = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/FastThrowStone.ptl");  // 调虚槽 +588
  *(this + 2155) = 30075;  // this+8620〔uAI8620(推断)〕
  *(this + 2156) = 0;  // this+8624〔uAI8624(推断)〕
  sub_4015C0("THROW_STONE", 0xBu);  // 【std::string构造赋值】
  v20 = *this;
  *(this + 1829) = 500;
  *(this + 1870) = 500;
  *(this + 2165) = 10;  // this+8660〔uEvt8660(推断)〕
  *(this + 2166) = 5;  // this+8664〔uAI8664(推断)〕
  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v20 + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  *(this + 2167) = result;  // this+8668〔nCool8668(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59D180 sub_59D180 —— AI 相位门参数面复位（同构 ·0x59C4C0，差异：无 8660/8664 倍增）
// 整面清零 7531..7596；nArg2 1/2 → this+7588=1、7572=2；nArg2==0 → 7596=-50
// ------------------------------------------------------------
int /*thiscall*/ sub_59D180(int this, int nArg2, int nArg3)  // 实现：AI 相位门参数面复位（同构 ·0x59C4C0，差异：无 8660/8664 倍增）
{
  int result; // eax

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  if ( nArg2 != 0 )  // 若 nArg2 非 0
  {
    if ( nArg2 == 1 || nArg2 == 2 )  // 若 nArg2 == 1 与/或 nArg2 == 2
    {
      *(uint32_t *)(this + 7588) = 1;  // this+7588〔uForm7588〕
      *(uint32_t *)(this + 7572) = 2;  // this+7572〔uGrade7572(推断)〕
    }
  }
  else  // 否则分支
  {
    *(uint32_t *)(this + 7596) = -50;  // this+7596〔nOffset7596(推断)〕
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59D230 sub_59D230 —— 行为字分发器（同构 ·0x59CB40，差异：无指挥/连投分支）
// sub_4E0120 前置；case 0/无目标 → vt+1104(15)；case 1：rand < 3*((1909==0)+1) →
// 行为字 2，rand <10% 时近身检测（vt+120 X 距离 ≤60、>40 且 < sub_425050 边界-40）
// → 行为字 3；case 13/15：目标存在 → 行为字 1
// ------------------------------------------------------------
int /*thiscall*/ sub_59D230(int *this)  // 实现：行为字分发器（同构 ·0x59CB40，差异：无指挥/连投分支）
{
  int result; // eax
  int nRand; // eax
  int v4; // et2
  int fld_e29; // edi | =+0x0074 字段 x2（证据 005FD6C0）
  int fld_e1813; // ebx | =+0x1C54 字段 x1
  int v7; // edi

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);  // 调虚槽 +1104
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);  // 调虚槽 +1104
      if ( rand() % 100 < 3 * ((*(this + 1909) == 0) + 1) )  // this+7636〔nPosWinY〕
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 2);  // 调虚槽 +1104
      nRand = rand();  // nRand = 调 rand
      v4 = nRand % 100;
      result = nRand / 100;
      if ( v4 < 10 )  // 若 v4 < 10
      {
        fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);  // fld_e29 = 读 this+29
        fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
        result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - fld_e1813);  // 调虚槽 +120：动画对象
        if ( result <= 60 )  // 若 result <= 60
        {
          result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
          if ( result > 40 )  // 若 result > 40
          {
            v7 = sub_425050(fld_e29) - 40;  // 总宽换算
            result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
            if ( result < v7 )  // 若 result < v7
              return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 3);  // 调虚槽 +1104
          }
        }
      }
      return result;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      goto LABEL_4;
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_4:  // 标签 LABEL_4（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 1);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59D360 sub_59D360 —— 速投直发（同构 ·0x59CDB0 的速投支，差异：无条件、无 59C810 回退）
// 门同 ·0x59CDB0（vt+308 && this+1639==8 && 相位 1757==0 && this+8612 未置 &&
// 目标 +148>2），通过即 vt+580(this+2155/2156/2154 三槽) 速投 + vt+212 播报
// this+2158 文案、置 this+8612=1；收尾 sub_4E1780
// ------------------------------------------------------------
char /*thiscall*/ sub_59D360(uint32_t *this)  // 实现：速投直发（同构 ·0x59CDB0 的速投支，差异：无条件、无 59C810 回退）
{
  uint32_t *pThis_86E; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && *(this + 1639) == 8  // this+6556〔大状态ID〕
    && sub_41A5E0((unsigned int)(this + 1757)) == 0  // crypt4byte 解密校验（·0x41A590 逆运算）
    && *((uint8_t *)this + 8612) == 0  // this+8612〔uAI8612(推断)〕
    && *(int *)(*(this + 30) + 148) > 2 )  // this+120〔pAnimObj〕
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
      this,
      *(this + 2155),  // this+8620〔uAI8620(推断)〕
      *(this + 2156),  // this+8624〔uAI8624(推断)〕
      *(this + 2154),  // this+8616〔uAI8616(推断)〕
      0,
      20,
      0,
      60,
      4,
      0,
      0,
      0);
    if ( *(this + 2163) < 0x10u )  // this+8652〔uPhase8652(推断)〕
      pThis_86E = this + 2158;
    else  // 否则分支
      pThis_86E = (uint32_t *)*(this + 2158);  // this+8632〔bDevourFlag(推断)〕
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_86E, -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    *((uint8_t *)this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
  }
  return sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x59D410 sub_59D410 —— 指令接收处理（指令包类型 7 + CommandReceive 气泡）
// sub_4D90A0 校验指令包；*uArg3==7 且 this+1639==0 时：sub_4D84F0 头顶气泡
// CommandReceive.ani，vt+120(X) 与包阈值 uArg3[3] 比较写 vt+148 标志 1/0（就位/
// 朝向【推断】），再 sub_431230 打包经 vt+560(this,8) 置攻击反应
// ------------------------------------------------------------
void /*userpurge*/ sub_59D410(uint32_t *pArg1@<ecx>, int nArg2@<edi>, uint32_t *uArg3)  // 实现：指令接收处理（指令包类型 7 + CommandReceive 气泡）
{
  uint32_t *uArg32; // ebx
  uint8_t v5[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h]
  int v9; // [esp+20h] [ebp-4h]

  uArg32 = uArg3;
  sub_4D90A0(uArg3);  // 调 校验指令包
  if ( *uArg32 == 7 && pArg1[1639] == 0 )  // 复合条件判定（与/或）
  {
    sub_4D84F0(0, 0);  // 头顶气泡 CommandReceive.ani（同 0x4D82D0 结构）
    if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg2) >= uArg32[3] )  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 148))(pArg1, 1);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    else  // 否则分支
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 148))(pArg1, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    Block = nullptr;  // Block = 空指针
    v7 = 0;
    v8 = 0;
    v9 = 0;
    uArg3 = nullptr;  // uArg3 = 空指针
    sub_431230((int)v5, &uArg3);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t))(*pArg1 + 560))(pArg1, 8, v5, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
  }
}



// 火导弹哥布林装载：R_GOBLIN_* 语音 + {acc4-2,Hcc2-2,gcc1-3,tcc1-2,bcc1-2}.equ
//   + PassiveObject/Common/Particle/FireMissile.ptl（98L）
// ------------------------------------------------------------
// 0x59D4D0 sub_59D4D0 —— 火导弹哥布林装载（语音 + 五件套 + FireMissile 粒子）
// this+1698..1702 语音槽 + R_GOBLIN 三件套；挂装 {acc4-2, Hcc2-2, gcc1-3, tcc1-2,
// bcc1-2}.equ；this+2154 = FireMissile.ptl 粒子、this+2155=30047 效果 ID、
// this+2156 = sub_4049C0 以 vt+384 通道 0/1 与 vt+672(3)、this+1820/1821 帧区间
// 插值出的弹道参数；this+1829=500 射程
// ------------------------------------------------------------
uint64_t /*usercall*/ sub_59D4D0@<edx:eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：火导弹哥布林装载（语音 + 五件套 + FireMissile 粒子）
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
  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v4 = sub_4BA9E0(pMem, "Monster/Goblin/acc4-2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v4 = nullptr;  // v4 = 空指针
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*pArg1 + 784))(pArg1, v4, nArg2);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj3 != 0 )  // 若 pObj3 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v7 = sub_4BA9E0(pMem2, "Monster/Goblin/Hcc2-2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v7 = nullptr;  // v7 = 空指针
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v7);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj2 != 0 )  // 若 pObj2 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem3 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v10 = sub_4BA9E0(pMem3, "Monster/Goblin/gcc1-3.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v10 = nullptr;  // v10 = 空指针
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v10);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj5 != 0 )  // 若 pObj5 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem4 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v13 = sub_4BA9E0(pMem4, "Monster/Goblin/tcc1-2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v13 = nullptr;  // v13 = 空指针
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v13);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj4 != 0 )  // 若 pObj4 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem5 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v16 = sub_4BA9E0(pMem5, "Monster/Goblin/bcc1-2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v16 = nullptr;  // v16 = 空指针
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v16);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  v18 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
          dword_8F84E4,  // 全局 对象工厂/生成管理器
          "PassiveObject/Common/Particle/FireMissile.ptl");  // 粒子 .ptl PassiveObject/Common/Particle/FireMissile.ptl
  v19 = *pArg1;
  pArg1[2154] = v18;
  pArg1[2155] = 30047;
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v19 + 384))(pArg1, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 384))(pArg1, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v20 = pArg1[1821] - pArg1[1820];
  v21 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 672))(pArg1, 3);  // 调虚槽 +672：自身 HP
  v24 = (float)v26;
  v23 = (float)(int)Block;
  result = (uint64_t)sub_4049C0(v23, v24, *v21 - pArg1[1820], v20);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  pArg1[2156] = result;
  pArg1[1829] = 500;
  return result;
}



// 子类扩展字段复位（this+8612..8624）
// ------------------------------------------------------------
// 0x59D760 sub_59D760 —— 子类扩展字段复位（同构 ·0x59C440，差异：无 this+8656）
// this+8612 一次性门清零、8616/8624 清零、this+8620=0xFFFF（定时器满值初值）
// ------------------------------------------------------------
int /*thiscall*/ sub_59D760(int this)  // 实现：子类扩展字段复位（同构 ·0x59C440，差异：无 this+8656）
{
  *(uint8_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint32_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  *(uint32_t *)(this + 8620) = 0xFFFF;  // this+8620〔uAI8620(推断)〕
  *(uint32_t *)(this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59D780 sub_59D780 —— AI 相位门参数面复位（同构 ·0x59D180，差异：标志槽 7588→7534）
// 整面清零 7531..7596；nArg2 1/2 → this+7534=1、7572=2；nArg2==0 → 7596=-50
// ------------------------------------------------------------
int /*thiscall*/ sub_59D780(int this, int nArg2, int nArg3)  // 实现：AI 相位门参数面复位（同构 ·0x59D180，差异：标志槽 7588→7534）
{
  int result; // eax

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  if ( nArg2 != 0 )  // 若 nArg2 非 0
  {
    if ( nArg2 == 1 || nArg2 == 2 )  // 若 nArg2 == 1 与/或 nArg2 == 2
    {
      *(uint8_t *)(this + 7534) = 1;  // this+7534〔bCfgBlock14(推断)〕
      *(uint32_t *)(this + 7572) = 2;  // this+7572〔uGrade7572(推断)〕
    }
  }
  else  // 否则分支
  {
    *(uint32_t *)(this + 7596) = -50;  // this+7596〔nOffset7596(推断)〕
  }
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x59D830 sub_59D830 —— 指令接收处理（同构 ·0x59D410，函数体完全同构）
// 火导弹哥布林族的指令包路径：sub_4D90A0 校验 → 指令码 7 且空闲时头顶 CommandReceive
// 气泡、按包内 X 阈值写 vt+148 就位位 → sub_431230 打包 → vt+560(this,8) 置反应态
// ------------------------------------------------------------
void /*userpurge*/ sub_59D830(uint32_t *pArg1@<ecx>, int nArg2@<edi>, uint32_t *uArg3)  // 实现：指令接收处理（同构 ·0x59D410，函数体完全同构）
{
  uint32_t *uArg32; // ebx
  uint8_t v5[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h]
  int v9; // [esp+20h] [ebp-4h]

  uArg32 = uArg3;
  sub_4D90A0(uArg3);  // 调 校验指令包
  if ( *uArg32 == 7 && pArg1[1639] == 0 )  // 复合条件判定（与/或）
  {
    sub_4D84F0(0, 0);  // 头顶气泡 CommandReceive.ani（同 0x4D82D0 结构）
    if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg2) >= uArg32[3] )  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 148))(pArg1, 1);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    else  // 否则分支
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 148))(pArg1, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    Block = nullptr;  // Block = 空指针
    v7 = 0;
    v8 = 0;
    v9 = 0;
    uArg3 = nullptr;  // uArg3 = 空指针
    sub_431230((int)v5, &uArg3);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t))(*pArg1 + 560))(pArg1, 8, v5, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
  }
}



// 冰导弹哥布林装载：R_GOBLIN_* 语音 + {acc4,Hcc2,gcc1-3,tcc1-2,bcc1-2}.equ
//   + PassiveObject/Common/Particle/IceMissile.ptl（98L）
// ------------------------------------------------------------
// 0x59D8F0 sub_59D8F0 —— 冰导弹哥布林装载（同构 ·0x59D4D0，差异：冰系资源面）
// 挂装 {acc4, Hcc2, gcc1-3, tcc1-2, bcc1-2}.equ + IceMissile.ptl 粒子（this+2154）、
// this+2155=30057 效果 ID（火系 30047→冰系 30057）、2156 同法 sub_4049C0 插值
// ------------------------------------------------------------
uint64_t /*usercall*/ sub_59D8F0@<edx:eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：冰导弹哥布林装载（同构 ·0x59D4D0，差异：冰系资源面）
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
  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v4 = sub_4BA9E0(pMem, "Monster/Goblin/acc4.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v4 = nullptr;  // v4 = 空指针
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*pArg1 + 784))(pArg1, v4, nArg2);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj3 != 0 )  // 若 pObj3 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v7 = sub_4BA9E0(pMem2, "Monster/Goblin/Hcc2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v7 = nullptr;  // v7 = 空指针
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v7);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj2 != 0 )  // 若 pObj2 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem3 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v10 = sub_4BA9E0(pMem3, "Monster/Goblin/gcc1-3.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v10 = nullptr;  // v10 = 空指针
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v10);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj5 != 0 )  // 若 pObj5 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem4 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v13 = sub_4BA9E0(pMem4, "Monster/Goblin/tcc1-2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v13 = nullptr;  // v13 = 空指针
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v13);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj4 != 0 )  // 若 pObj4 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem5 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v16 = sub_4BA9E0(pMem5, "Monster/Goblin/bcc1-2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v16 = nullptr;  // v16 = 空指针
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v16);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  v18 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
          dword_8F84E4,  // 全局 对象工厂/生成管理器
          "PassiveObject/Common/Particle/IceMissile.ptl");  // 粒子 .ptl PassiveObject/Common/Particle/IceMissile.ptl
  v19 = *pArg1;
  pArg1[2154] = v18;
  pArg1[2155] = 30057;
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v19 + 384))(pArg1, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 384))(pArg1, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v20 = pArg1[1821] - pArg1[1820];
  v21 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 672))(pArg1, 3);  // 调虚槽 +672：自身 HP
  v24 = (float)v26;
  v23 = (float)(int)Block;
  result = (uint64_t)sub_4049C0(v23, v24, *v21 - pArg1[1820], v20);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  pArg1[2156] = result;
  pArg1[1829] = 500;
  return result;
}



// 子类扩展字段复位（this+8612..8632）
// ------------------------------------------------------------
// 0x59DB80 sub_59DB80 —— 子类扩展字段复位（同构 ·0x59D760，差异：8620 清零、多 8628=0xFFFF/8632）
// 冰导弹哥布林族：8612/8616/8620/8624 清 0，8628 置 0xFFFF（"无目标"哨兵）、8632 清 0
// ------------------------------------------------------------
int /*thiscall*/ sub_59DB80(int this)  // 实现：子类扩展字段复位（同构 ·0x59D760，差异：8620 清零、多 8628=0xFFFF/8632）
{
  *(uint8_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint32_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  *(uint32_t *)(this + 8620) = 0;  // this+8620〔uAI8620(推断)〕
  *(uint32_t *)(this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
  *(uint32_t *)(this + 8628) = 0xFFFF;  // this+8628〔nPoolTime(推断)〕
  *(uint32_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  return 0;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59DBB0 sub_59DBB0 —— 状态事件回调（事件 5 光环重建 / 事件 8 清门）
// 事件 5：50% 概率经 sub_64BDF0 对 this+7256 光环做基础数据重建；事件 8：清
// this+8612 一次性门；透传 sub_4E33D0 基类状态收尾【推断：5/8 为状态机事件号】
// ------------------------------------------------------------
int /*thiscall*/ sub_59DBB0(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：状态事件回调（事件 5 光环重建 / 事件 8 清门）
{
  if ( ArgList == 5 )  // 若 ArgList == 5
  {
    if ( rand() % 100 < 50 )  // 50% 概率触发（rand()%100 < 50）
      sub_64BDF0(this, *(uint32_t *)(this + 7256));  // 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
  }
  else if ( ArgList == 8 )
  {
    *(uint8_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  }
  return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}



// 子类扩展字段复位（77L）
// ------------------------------------------------------------
// 0x59DC10 sub_59DC10 —— 喷吐攻击段分发器（this+7028 攻击段号 0/1 → 连发 1-3 次）
// 门：vt+308 && this+6556 大状态==8 && this+8612 未置 && 目标 +148>2；段 0 →
// vt+580(this+8628/8632 效果面, this+8616 粒子) 单发；段 1 → 8616、8620、8624
// 三连发；尾段 vt+212 播报 this+8640 文案、this+8612=1 防重入、sub_4E1780 收尾
// ------------------------------------------------------------
char /*thiscall*/ sub_59DC10(int this)  // 实现：喷吐攻击段分发器（this+7028 攻击段号 0/1 → 连发 1-3 次）
{
  int fld_21A8; // eax | =+0x21A8 字段 x1（证据 005C0490）
  int pThis_21C0; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) == 0  // 调虚槽 +308：是否本地玩家
    || *(uint32_t *)(this + 6556) != 8  // this+6556〔大状态ID〕
    || *(uint8_t *)(this + 8612) != 0  // this+8612〔uAI8612(推断)〕
    || *(int *)(*(uint32_t *)(this + 120) + 148) <= 2 )  // this+120〔pAnimObj〕
  {
    return sub_4E1780((uint32_t *)this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  }
  if ( sub_41A5E0(this + 7028) == 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    fld_21A8 = *(uint32_t *)(this + 8616);  // fld_21A8 = 读 this+8616
LABEL_9:  // 标签 LABEL_9（跳转合流点）
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
      this,
      *(uint32_t *)(this + 8628),  // this+8628〔nPoolTime(推断)〕
      *(uint32_t *)(this + 8632),  // this+8632〔bDevourFlag(推断)〕
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
  if ( sub_41A5E0(this + 7028) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
      this,
      *(uint32_t *)(this + 8628),  // this+8628〔nPoolTime(推断)〕
      *(uint32_t *)(this + 8632),  // this+8632〔bDevourFlag(推断)〕
      *(uint32_t *)(this + 8616),  // this+8616〔粒子〕
      0,
      20,
      0,
      60,
      4,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
      this,
      *(uint32_t *)(this + 8628),  // this+8628〔nPoolTime(推断)〕
      *(uint32_t *)(this + 8632),  // this+8632〔bDevourFlag(推断)〕
      *(uint32_t *)(this + 8620),  // this+8620〔uAI8620(推断)〕
      0,
      20,
      0,
      60,
      4,
      0,
      0,
      0);
    fld_21A8 = *(uint32_t *)(this + 8624);  // fld_21A8 = 读 this+8624
    goto LABEL_9;
  }
LABEL_10:  // 标签 LABEL_10（跳转合流点）
  if ( *(uint32_t *)(this + 8660) < 0x10u )  // this+8660〔uEvt8660(推断)〕
    pThis_21C0 = this + 8640;
  else  // 否则分支
    pThis_21C0 = *(uint32_t *)(this + 8640);  // pThis_21C0 = 读 this+8640
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, pThis_21C0, -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
  *(uint8_t *)(this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
  return sub_4E1780((uint32_t *)this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// 指挥 AI：GOBLIN_COMMAND（RTTI cast, 67L）
// ------------------------------------------------------------
// 0x59DD40 sub_59DD40 —— 指挥官广播（同构 ·0x59C700，差异：RTTI 目标 CNGoblinMountainGab）
// 遍历 this+29 列表找 300 内同阵营 CNGoblinMountainGab（山地哥布林），
// sub_49C620(7,坐标) 落点标记 + sub_4D82D0 气泡 + vt+212 播报 GOBLIN_COMMAND
// ------------------------------------------------------------
int /*thiscall*/ sub_59DD40(uint32_t *this)  // 实现：指挥官广播（同构 ·0x59C700，差异：RTTI 目标 CNGoblinMountainGab）
{
  unsigned int i; // edi
  int fld_e29; // ecx | =+0x0074 字段 x2（证据 005FD6C0）
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // edi
  int v11; // ebx
  int v12; // eax
  int fld_e1813; // eax | =+0x1C54 字段 x1
  int v14; // [esp+0h] [ebp-10h]
  unsigned int v15; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v4 = *(uint32_t *)(fld_e29 + 8);
    v15 = i;
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;  // 跳出循环/分支
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 若 v6 != 0
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else  // 否则分支
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 若 v9 != 0
        pObj = *(uint32_t *)(v9 + 4 * i);
      else  // 否则分支
        pObj = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调虚槽 +376：坐标同步包（type 37）
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )  // 调虚槽 +376：坐标同步包（type 37）
      {
        v12 = __RTDynamicCast(
                pObj,
                0,
                &IRDActiveObject `RTTI Type Descriptor',
                &CNGoblinMountainGab `RTTI Type Descriptor',
                0);
        if ( v12 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 156))(this, v12) <= 300 )  // 调虚槽 +156：与目标 x/y 距离绝对值
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813), 0);  // this+7252〔pTarget7252〕
          sub_49C620(7, fld_e1813, v14);  // 命令下发包装（组 id = this+4，值重复两遍）
          sub_4D82D0(0, 0);  // 头顶气泡 Command.ani（a2/a3 = 定位偏移）
          v14 = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*this + 212))(this, "GOBLIN_COMMAND", -1, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
        }
      }
      i = v15;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59DE50 sub_59DE50 —— 狂暴衰减回调（·0x59DEE0 加速的逆操作）
// this+1905 面板速度 ×0.83333（=1/1.2）：nArg2==0 时改 +4 通道并对 vt+672(0)+858
// 速率槽经 sub_41A5E0/41A590 读改写 -0.2；nArg2==1 时改 +36 通道
// ------------------------------------------------------------
int /*thiscall*/ sub_59DE50(uint32_t *this, int nArg2, int nArg3)  // 实现：狂暴衰减回调（·0x59DEE0 加速的逆操作）
{
  int result; // eax
  unsigned int v5; // edi
  int v6; // edx
  int v7; // [esp+Ch] [ebp+8h]

  if ( nArg2 != 0 )  // 若 nArg2 非 0
  {
    result = nArg2 - 1;
    if ( nArg2 == 1 )  // 若 nArg2 == 1
      *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.83333331;  // this+7620〔pStatusPanel(推断)〕
  }
  else  // 否则分支
  {
    *(float *)(*(this + 1905) + 4) = *(float *)(*(this + 1905) + 4) * 0.83333331;  // this+7620〔pStatusPanel(推断)〕
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;  // 调虚槽 +672：自身 HP
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v5, v6, v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  return result;
}



// 狂气光环 AI：vt+212 播报 AURA_FURY（97L；狂暴化演出, 与 0x593840 彼诺修版同族）
// ------------------------------------------------------------
// 0x59DEE0 sub_59DEE0 —— 狂气光环（狂暴化：加速 ×1.2 + 火焰光环 + AURA_FURY 播报）
// 先整面清零 7531..7558 与 1891..1899 决策面板；Block==null 主分支：this+1905 面板
// +4 通道 ×1.2、vt+672(0)+858 速率槽 +0.2（sub_41A590 写回）、nArg3==0 时 vt+700
// 预处理 + new 0x8C 构造 sub_64BBF0(150,3000,25) 火焰光环绑定宿主 + sub_4DB200
// 随机文案（槽 24，值 2/3）+ vt+212 播报 AURA_FURY；Block==1 仅 +36 通道 ×1.2；
// Block==2 仅置 1897=1、1893=2 标志（与 ·0x593840 彼诺修版同族）
// ------------------------------------------------------------
int /*thiscall*/ sub_59DEE0(char *this, void *Block, int nArg3)  // 实现：狂气光环（狂暴化：加速 ×1.2 + 火焰光环 + AURA_FURY 播报）
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
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  pThis_1D73 = this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *((uint32_t *)this + 1893) = 0;  // this[1893] = 0
  *((uint32_t *)this + 1892) = 0;  // this[1892] = 0
  *((uint32_t *)this + 1891) = 0;  // this[1891] = 0
  *((uint32_t *)this + 1897) = 0;  // this+7588〔uForm7588〕
  *((uint32_t *)this + 1896) = 0;  // this+7584〔uForm7584〕
  *((uint32_t *)this + 1895) = 0;  // this[1895] = 0
  *((uint32_t *)this + 1894) = 0;  // this[1894] = 0
  *((uint32_t *)this + 1899) = 0;  // this[1899] = 0
  if ( Block != nullptr )  // 若 Block 有效（非空）
  {
    if ( Block == (void *)1 )
    {
      pThis_771 = *((uint32_t *)this + 1905);  // this+7620〔pStatusPanel(推断)〕
      v7 = *(float *)(pThis_771 + 36);  // pThis_771+36〔nStateWord36(推断)〕
      result = pThis_771 + 32;
      *(float *)(result + 4) = v7 * 1.2;
      *((uint32_t *)this + 1897) = 1;  // this+7588〔uForm7588〕
      *((uint32_t *)this + 1893) = 2;  // this[1893] = 2
    }
    else  // 否则分支
    {
      result = (int)Block - 2;
      if ( Block == (void *)2 )
      {
        *((uint32_t *)this + 1897) = 1;  // this+7588〔uForm7588〕
        *((uint32_t *)this + 1893) = 2;  // this[1893] = 2
      }
    }
  }
  else  // 否则分支
  {
    *(float *)(*((uint32_t *)this + 1905) + 4) = *(float *)(*((uint32_t *)this + 1905) + 4) * 1.2;  // this+7620〔pStatusPanel(推断)〕
    pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 858;  // 调虚槽 +672：自身 HP
    *(float *)&Blocka = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, v9, Blocka);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
    if ( nArg3 == 0 )  // 若 nArg3 为 0
    {
      (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
      sub_53F6A0(this);  // 调 收尾路径
      v14 = 0;
      if ( operator new(0x8Cu) != nullptr )  // new(140 字节) 分配对象
        v10 = (int *)sub_64BBF0(150, 3000, 25);  // 火焰动画查询 2（5910D0）
      else  // 否则分支
        v10 = nullptr;  // v10 = 空指针
      v11 = *v10;
      v14 = -1;
      (*(void (/*thiscall*/ **)(int *, char *, char *, int, uint32_t, uint32_t, int))(v11 + 56))(v10, this, this, 1, 0, 0, -1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
      v13[0] = 2;
      v13[1] = 3;
      nRand = rand() % 2;  // nRand = 调 rand
      sub_4DB200(24, v13[nRand]);  // 15% 概率随机文案触发（0x4DB130 的门包装）
      return (*(int (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
               this,
               "AURA_FURY",  // 标签 AURA_FURY
               -1,
               0,
               0);
    }
  }
  return result;
}



// AI 相位辅助（62L）
// ------------------------------------------------------------
// 0x59E0F0 sub_59E0F0 —— 行为字分发器（同构 ·0x59D230，差异：3% 概率先走指挥）
// case 1：rand <3% → sub_59DD40 指挥广播；rand <5*((1909==0)+1) → 行为字 2；
// rand <10% 近身检测 → 行为字 3；case 0/无目标 → 15，case 13/15 有目标 → 1
// ------------------------------------------------------------
int /*thiscall*/ sub_59E0F0(int *this)  // 实现：行为字分发器（同构 ·0x59D230，差异：3% 概率先走指挥）
{
  int result; // eax
  int nRand; // eax
  int v4; // et2
  int fld_e29; // edi | =+0x0074 字段 x2（证据 005FD6C0）
  int fld_e1813; // ebx | =+0x1C54 字段 x1
  int v7; // edi

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);  // 调虚槽 +1104
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);  // 调虚槽 +1104
      if ( rand() % 100 < 3 )  // 3% 概率触发（rand()%100 < 3）
        return sub_59DD40(this);  // 指挥官广播（同构 ·0x59C700，差异：RTTI 目标 CNGoblinMountainGab）
      if ( rand() % 100 < 5 * ((*(this + 1909) == 0) + 1) )  // this+7636〔nPosWinY〕
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 2);  // 调虚槽 +1104
      nRand = rand();  // nRand = 调 rand
      v4 = nRand % 100;
      result = nRand / 100;
      if ( v4 < 10 )  // 若 v4 < 10
      {
        fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);  // fld_e29 = 读 this+29
        fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
        result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - fld_e1813);  // 调虚槽 +120：动画对象
        if ( result <= 60 )  // 若 result <= 60
        {
          result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
          if ( result > 40 )  // 若 result > 40
          {
            v7 = sub_425050(fld_e29) - 40;  // 总宽换算
            result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
            if ( result < v7 )  // 若 result < v7
              return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 3);  // 调虚槽 +1104
          }
        }
      }
      return result;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      goto LABEL_4;
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_4:  // 标签 LABEL_4（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 1);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
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
// 0x59E230 sub_59E230 —— 卢佩特（Lupete）装载：语音 + 六件套 + 三向喷吐粒子
// this+1698..1702 语音槽 + R_GOBLIN 三件套；挂装 {acc3-2, acc4-2, Hcc2-2,
// LupetePants, LupeteShoulder, LupeteFoot}.equ；this+2154/2155/2156 =
// FireMissileGero{Center,Left,Right}.ptl 三向喷吐粒子、this+2157=30049 效果 ID、
// this+2158 = sub_4049C0 插值弹道参数、this+1829=500 射程
// ------------------------------------------------------------
int /*thiscall*/ sub_59E230(uint32_t *this)  // 实现：卢佩特（Lupete）装载：语音 + 六件套 + 三向喷吐粒子
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

  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/acc3-2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v3 = nullptr;  // v3 = 空指针
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/acc4-2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v6 = nullptr;  // v6 = 空指针
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj2 != 0 )  // 若 pObj2 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem3 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v9 = sub_4BA9E0(pMem3, "Monster/Goblin/Hcc2-2.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v9 = nullptr;  // v9 = 空指针
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v9);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj4 != 0 )  // 若 pObj4 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem4 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v12 = sub_4BA9E0(pMem4, "Monster/Goblin/LupetePants.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v12 = nullptr;  // v12 = 空指针
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj3 != 0 )  // 若 pObj3 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem5 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v15 = sub_4BA9E0(pMem5, "Monster/Goblin/LupeteShoulder.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v15 = nullptr;  // v15 = 空指针
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v15);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj5 != 0 )  // 若 pObj5 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem6 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
    v18 = sub_4BA9E0(pMem6, "Monster/Goblin/LupeteFoot.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    v18 = nullptr;  // v18 = 空指针
  pObj6 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( pObj6 != 0 )  // 若 pObj6 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 4))(pObj6, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  *(this + 2154) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
                     dword_8F84E4,  // 全局 对象工厂/生成管理器
                     "PassiveObject/Common/Particle/FireMissileGeroCenter.ptl");  // 粒子 .ptl PassiveObject/Common/Particle/FireMissileGeroCenter.ptl
  *(this + 2155) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
                     dword_8F84E4,  // 全局 对象工厂/生成管理器
                     "PassiveObject/Common/Particle/FireMissileGeroLeft.ptl");  // 粒子 .ptl PassiveObject/Common/Particle/FireMissileGeroLeft.ptl
  v20 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
          dword_8F84E4,  // 全局 对象工厂/生成管理器
          "PassiveObject/Common/Particle/FireMissileGeroRight.ptl");  // 粒子 .ptl PassiveObject/Common/Particle/FireMissileGeroRight.ptl
  v21 = *this;
  *(this + 2156) = v20;  // this+8624〔uAI8624(推断)〕
  *(this + 2157) = 30049;  // this+8628〔nPoolTime(推断)〕
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v21 + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  v22 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v32 = v22;
  v24 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v30 = (float)v32;
  v29 = (float)(int)Block;
  fld_e1820 = (uint64_t)sub_4049C0(v29, v30, *v24 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  fld_e18202 = fld_e1820;
  LODWORD(fld_e1820) = *this;
  *(this + 2158) = fld_e18202;  // this+8632〔bDevourFlag(推断)〕
  v27 = (uint32_t *)(*(int (/*fastcall*/ **)(uint32_t *, uint32_t, int))(fld_e1820 + 672))(this, HIDWORD(fld_e1820), 3);  // 调虚槽 +672：自身 HP
  result = off_77F3FC((char *)&byte_72E098, *v27, fld_e18202);  // result = 调 off_77F3FC
  *(this + 1829) = 500;
  return result;
}


// 子类扩展字段复位（this+8612..8620）
// ------------------------------------------------------------
// 0x59E550 sub_59E550 —— 子类扩展字段复位（同构 ·0x59D760，差异：仅 8612/8616/8620 三字段且 8620 清零）
// 卢佩特（Lupete）族：8612（触发门位）/8616（计数）/8620 三槽清 0，其余扩展槽不参与
// ------------------------------------------------------------
int /*thiscall*/ sub_59E550(int this)  // 实现：子类扩展字段复位（同构 ·0x59D760，差异：仅 8612/8616/8620 三字段且 8620 清零）
{
  *(uint8_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint32_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  *(uint32_t *)(this + 8620) = 0;  // this+8620〔uAI8620(推断)〕
  return 0;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59E570 sub_59E570 —— 攻击触发门（同构 ·0x59D360 的门结构，差异：经 vt+1312 直接触发动作）
// 门：vt+308 && this+1639==8 && 攻击段号 this+7028==0 && this+8612 未置 &&
// 目标 +148>2；通过即 vt+1312 触发、this+8612=1，收尾 sub_4E1780
// ------------------------------------------------------------
char /*thiscall*/ sub_59E570(uint8_t *this)  // 实现：攻击触发门（同构 ·0x59D360 的门结构，差异：经 vt+1312 直接触发动作）
{
  if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && *((uint32_t *)this + 1639) == 8  // this+6556〔大状态ID〕
    && sub_41A5E0((unsigned int)(this + 7028)) == 0  // crypt4byte 解密校验（·0x41A590 逆运算）
    && *(this + 8612) == 0
    && *(int *)(*((uint32_t *)this + 30) + 148) > 2 )  // this+120〔pAnimObj〕
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1312))(this);  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
    *(this + 8612) = 1;
  }
  return sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// AI 字段访问（this+8624）
// ------------------------------------------------------------
// 0x59E5D0 sub_59E5D0 —— 查询重定向（this+8624 标志接管）
// this+8624 置位时改判 vt+840 大状态是否为 5（受击反应态），否则透传
// sub_4D9210 原查询【推断：8624 为反应接管标志】
// ------------------------------------------------------------
char /*thiscall*/ sub_59E5D0(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 实现：查询重定向（this+8624 标志接管）
{
  if ( *(this + 8624) != 0 )  // this+8624〔标志接管〕
    return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 5;  // 调虚槽 +840：大状态 getter（this+6556）
  else  // 否则分支
    return sub_4D9210(nArg2, nArg3, nArg4);  // 返回 调 sub_4D9210 返回值
}



// AI 字段访问（this+8624）
// ------------------------------------------------------------
// 0x59E600 sub_59E600 —— 查询重定向（同构 ·0x59E5D0，差异：单参透传 sub_4D9200）
// this+8624（姿态/架招标志）非 0 时改答"本体姿态 vt+840 是否 ==5（架招中）"，
// 否则透传基类应答 sub_4D9200(nArg2)
// ------------------------------------------------------------
char /*thiscall*/ sub_59E600(uint8_t *this, int nArg2)  // 实现：查询重定向（同构 ·0x59E5D0，差异：单参透传 sub_4D9200）
{
  if ( *(this + 8624) != 0 )
    return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 5;  // 调虚槽 +840：大状态 getter（this+6556）
  else  // 否则分支
    return sub_4D9200(nArg2);  // 返回 调 sub_4D9200 返回值
}



// AI 相位门（this+8632/8636）
// ------------------------------------------------------------
// 0x59E630 sub_59E630 —— 架招触发相位门（this+8632/8636）
// vt+840 大状态==0（空闲）且 this+8636 未置、this+8632 已设时：5% 概率调
// sub_4E7F30(this,50,30,0)【推断：50/30 为距离/时长参数】，成功且当前动作号
// （vt+340 返回结构首字段）为 60/61 时 vt+560(this,14) 进架招反应、this+8636=1
// ------------------------------------------------------------
int /*thiscall*/ sub_59E630(int this)  // 实现：架招触发相位门（this+8632/8636）
{
  int result; // eax
  int nRand; // eax
  int v4; // et2

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result == 0 )  // 若 result 为 0
  {
    result = *(uint8_t *)(this + 8636);  // result = 读 this+8636
    if ( (uint8_t)result == 0 )
    {
      result = *(uint32_t *)(this + 8632);  // result = 读 this+8632
      if ( result != 0 )  // 若结果非 0（成功）
      {
        nRand = rand();  // nRand = 调 rand
        v4 = nRand % 100;
        result = nRand / 100;
        if ( v4 < 5 )  // 若 v4 < 5
        {
          result = sub_4E7F30((uint32_t *)this, 50, 30, 0);  // 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
          if ( result != 0 )  // 若结果非 0（成功）
          {
            result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
            if ( (uint8_t)result != 0
              && (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this) == 60  // 调虚槽 +340：三元组基址（+284，vt+340）
               || *(uint32_t *)(result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this)) == 61) )  // 调虚槽 +340：三元组基址（+284，vt+340）
            {
              result = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
                         this,
                         14,
                         0,
                         0,
                         0);
              *(uint8_t *)(this + 8636) = 1;  // this+8636〔pDollTarget(推断)〕
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
// 0x59E6C0 sub_59E6C0 —— 对象注销联动：跟踪槽命中即清
// sub_4D9170(nArg2) 注销通知后，若 this+2158 跟踪槽正记录该对象则一并清零
// （2154/2155 粒子槽邻位的伴随对象句柄【推断】），防悬挂引用
// ------------------------------------------------------------
int /*thiscall*/ sub_59E6C0(uint32_t *this, int nArg2)  // 实现：对象注销联动：跟踪槽命中即清
{
  int result; // eax

  sub_4D9170(nArg2);  // 调 消亡通知
  result = *(this + 2158);  // this+8632〔bDevourFlag(推断)〕
  if ( result != 0 && nArg2 == result )  // 若 result != 0 与/或 nArg2 == result
    *(this + 2158) = 0;  // this+8632〔bDevourFlag(推断)〕
  return result;
}



// ============================================================
// 【分区 14】哥布林系·冰导弹与手里剑兵（0x59E6F0-0x59F150）
// 证据：PassiveObject/Common/Particle/IceMissile.ptl、Particle/Suriken.ptl +
//       THROW_SHURIKEN 手里剑（0x59E950-0x59EC60 四连函数）

// 冰导弹技能：引用 PassiveObject/Common/Particle/IceMissile.ptl
// ------------------------------------------------------------
// 0x59E6F0 sub_59E6F0 —— 冰导弹发射（IceMissile.ptl）
// vt+588 惰性装载 PassiveObject/Common/Particle/IceMissile.ptl 入 this+2154 粒子句柄槽；
// vt+308 发射前置通过后经 vt+580 发射调用打出技能 id 30058（载荷取 this+2155 效果槽）
// ------------------------------------------------------------
int /*thiscall*/ sub_59E6F0(uint32_t *this)  // 实现：冰导弹发射（IceMissile.ptl）
{
  int result; // eax

  if ( *(this + 2154) == 0 )  // this+8616〔uAI8616(推断)〕
    *(this + 2154) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
                       dword_8F84E4,  // 全局 对象工厂/生成管理器
                       "PassiveObject/Common/Particle/IceMissile.ptl");  // 粒子 .ptl PassiveObject/Common/Particle/IceMissile.ptl
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
             this,
             30058,
             *(this + 2155),  // this+2155〔效果槽〕
             *(this + 2154),  // this+2154〔粒子句柄槽〕
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
// 0x59E750 sub_59E750 —— 自身销毁联动停音
// sub_4D9170 注销通知的销毁对象为自身时，经 vt+216 音效槽停 3510 号轨道
// （3510 与 ·0x59F420 冰盾 WINDSHIELD_LOOP 循环音同轨【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_59E750(void *this, void *pArg2)  // 实现：自身销毁联动停音
{
  int result; // eax

  result = sub_4D9170(pArg2);  // result = 调 sub_4D9170 返回值
  if ( this == pArg2 )  // 若 this == pArg2
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 3510);  // 调虚槽 +216：音效 TAG 查询
  return result;
}



// 瞄准炸弹 AI：Particle/AimingBomb.ptl（98L）
// ------------------------------------------------------------
// 0x59E790 sub_59E790 —— 瞄准炸弹 AI（AimingBomb.ptl 弹道引信）
// vt+1244 校验目标 this+1813 槽存活后，vt+588 装载 Particle/AimingBomb.ptl 参数面，
// 按弹道总时长换算引信毫秒（单段上限 180）、速度 200/400 两档【推断：远近档】；
// 10% 概率特殊演出：首次（this+2160 门）清 8657/8658 相位字节、this+2161 挂 1500ms
// 倒计时，并经 sub_4D8600 弹头顶 Question.ani 疑问气泡；末经 vt+580 发射 id 30006
// ------------------------------------------------------------
int /*usercall*/ sub_59E790@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>)  // 实现：瞄准炸弹 AI（AimingBomb.ptl 弹道引信）
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
  sub_423A20(v15);  // 小结构初始化（0-100 刻度）
  result = pArg1[1813];  // result = 取 pArg1[1813]
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 1244))(pArg1, pArg1[1813]);  // 调虚槽 +1244
    if ( (uint8_t)result != 0 )
    {
      qmemcpy(
        v15,
        (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int, int))(*pArg1 + 588))(  // 调虚槽 +588
                        pArg1,
                        "Particle/AimingBomb.ptl",  // 粒子 .ptl Particle/AimingBomb.ptl
                        nArg2,
                        nArg3),
        0x62u);
      v5 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v15[7] + 3)) / (double)v15[17] * 1000.0);
      v6 = 2 * v5;
      v7 = (uint64_t)((double (/*fastcall*/ *)(uint32_t *, uint32_t, uint32_t, uint32_t))*(uint32_t *)(*pArg1 + 164))(  // 调虚槽 +164：★ 与目标朝向角度（atan2 角度制；3D 俯视判定）【新发现(会话 3)】
                               pArg1,
                               HIDWORD(v5),
                               pArg1[1813],
                               0);
      HIDWORD(v7) = *pArg1;
      v15[18] = v7;
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(HIDWORD(v7) + 8))(pArg1, pArg1[1813], 0);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTT…
      v9 = *pArg1;
      *(uint32_t *)((char *)&v15[3] + 3) = 1000 * v8 / v6;
      v10 = 1000 * (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(v9 + 8))(pArg1, pArg1[1813], 0) / v6;  // v10 = 1000 * (*(int (thiscall **)(uint32_t *, uint32_t, uint32_t))(v9 + 8))(pArg1, pArg1[1813], 0) / v6
      *(uint32_t *)((char *)&v15[4] + 3) = v10;
      if ( *(uint32_t *)((char *)&v15[3] + 3) > 180 )
        *(uint32_t *)((char *)&v15[3] + 3) = 180;
      if ( v10 > 180 )  // 若 v10 > 180
        *(uint32_t *)((char *)&v15[4] + 3) = 180;
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*pArg1 + 8))(pArg1, pArg1[1813], 0);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
      v12 = *pArg1;
      *(uint32_t *)((char *)&v15[7] + 3) = v11 > 200 ? 400 : 200;
      result = (*(int (/*thiscall*/ **)(uint32_t *))(v12 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
      if ( (uint8_t)result != 0 )
      {
        if ( rand() % 100 < 10 )  // 10% 概率触发（rand()%100 < 10）
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
            v14 = pArg1[81];  // v14 = 取 pArg1[81]
            pArg1[81] = 0;
            sub_4D8600(0, 0);  // 头顶气泡 Question.ani（疑问；结构同上但少一层坐标补偿）
            pArg1[81] = v14;
          }
        }
        return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 调虚槽 +580
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
// 0x59E950 sub_59E950 —— 手里剑投掷 AI（Suriken.ptl + THROW_SHURIKEN 播报）
// vt+588 惰性装载 Particle/Suriken.ptl 入 this+2154 粒子槽；随机 dword_72E1D8 三选一
// 写粒子 +31/+35 字段（外观变体【推断】）；载荷目标取 vt+52(目标 this+1813) 对象号，
// 10% 概率改记 -1；10% 特殊演出：首次清 8657/8658 相位、this+2161 挂 1500ms 倒计时、
// sub_4D8600 弹头顶 Question.ani 疑问气泡；vt+580 发射 id 30080 后 vt+212 播报 THROW_SHURIKEN
// ------------------------------------------------------------
int /*thiscall*/ sub_59E950(int *this)  // 实现：手里剑投掷 AI（Suriken.ptl + THROW_SHURIKEN 播报）
{
  int result; // eax
  int nRand; // eax
  bool nRand2; // bl
  int fld_e1813; // eax | =+0x1C54 字段 x1
  int fld_e81; // edi | =+0x0144 字段 x1（证据 004D6970）

  result = *(this + 1813);  // this+7252〔pTarget7252〕
  if ( result != 0 )  // 若结果非 0（成功）
  {
    if ( *(this + 2154) == 0 )  // this+8616〔uAI8616(推断)〕
      *(this + 2154) = (*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/Suriken.ptl");  // 调虚槽 +588
    sub_432FA0();  // srand 播种
    nRand = rand();  // nRand = 调 rand
    *(uint32_t *)(*(this + 2154) + 31) = dword_72E1D8[2 * (nRand % 3)];  // this+8616〔uAI8616(推断)〕
    *(uint32_t *)(*(this + 2154) + 35) = dword_72E1DC[2 * (nRand % 3)];  // this+8616〔uAI8616(推断)〕
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      nRand2 = rand() % 100 < 10;  // nRand2 = 调 rand
      fld_e1813 = -1;
      if ( !nRand2 )
        fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 52))(*(this + 1813));  // this+7252〔pTarget7252〕
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
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
      if ( nRand2 && *(this + 2160) == 0 )  // 复合条件判定（与/或）
      {
        *(this + 2160) = 1;  // this+8640〔uCastSlot8640(推断)〕
        *((uint8_t *)this + 8657) = 0;  // this+8657〔bAI8657〕
        *((uint8_t *)this + 8658) = 0;  // this+8658〔bAI8658〕
        sub_698F90((int)(this + 2161), 1500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        fld_e81 = *(this + 81);  // this+324〔nRandPick324〕
        *(this + 81) = 0;  // this+324〔nRandPick324〕
        sub_4D8600(0, 0);  // 头顶气泡 Question.ani（疑问；结构同上但少一层坐标补偿）
        *(this + 81) = fld_e81;  // this+324〔nRandPick324〕
      }
    }
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "THROW_SHURIKEN",  // 标签 THROW_SHURIKEN
             -1,
             0,
             0);
  }
  return result;
}



// 手里剑结算：Suriken.ptl 命中处理（this+200 主状态门, 61L）
// ------------------------------------------------------------
// 0x59EA80 sub_59EA80 —— 手里剑四连波次结算（命中帧表驱动）
// 帧表 {3,5,7,9,11,13}：主状态(vt+200)对象 +148 帧号走到表项即一轮连发四枚 30079
// （粒子参数角向 15 度步进【推断】），置 8676/8612 相位防重入；帧走到表项+1 时
// 清 8676 并推进 this+2170（既定目标/威胁槽，此处作波次索引【推断】，共六轮）
// ------------------------------------------------------------
int /*thiscall*/ sub_59EA80(uint32_t *this)  // 实现：手里剑四连波次结算（命中帧表驱动）
{
  int v2; // eax
  int i; // esi
  int v4; // eax
  int result; // eax
  int fld_e2170; // ecx | =+0x21E8 字段 x6（证据 005CDA80）
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
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(v2 + 200))(this) + 148) == v7[*(this + 2170)]  // 调虚槽 +200：取动画对象
    && *((uint8_t *)this + 8676) == 0 )  // this+8676〔uAI8676(推断)〕
  {
    qmemcpy(
      v8,
      (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/Suriken.ptl"),  // 调虚槽 +588
      0x62u);
    for ( i = 0; i < 4; ++i )  // 循环：i 从 0 递增到 4
    {
      v4 = *this;
      v8[18] = 15 * (i + 4 * *(this + 2170));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v4 + 580))(
        this,
        30079,
        *(this + 2155),  // this+8620〔uAI8620(推断)〕
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
    *((uint8_t *)this + 8676) = 1;  // this+8676〔uAI8676(推断)〕
    *((uint8_t *)this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  fld_e2170 = *(this + 2170);  // this+8680〔uGate8680(推断)〕
  if ( *(uint32_t *)(result + 148) == v7[fld_e2170] + 1 )
  {
    *((uint8_t *)this + 8676) = 0;  // this+8676〔uAI8676(推断)〕
    *(this + 2170) = fld_e2170 + 1;  // this+8680〔uGate8680(推断)〕
  }
  return result;
}



// 手里剑技能变体：Suriken.ptl + THROW_SHURIKEN
// ------------------------------------------------------------
// 0x59EB90 sub_59EB90 —— 手里剑十字四连投（0/90/180/270 度向）
// 角向表写粒子参数面 v18 槽，vt+308 逐枚校验后经 vt+580 发射 30079 共四枚；
// vt+212 播报 THROW_SHURIKEN，末尾 this+2168=-1（发射标记复位【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_59EB90(uint32_t *this)  // 实现：手里剑十字四连投（0/90/180/270 度向）
{
  int i; // esi
  int v3; // edx
  int result; // eax
  uint32_t v5[4]; // [esp+Ch] [ebp-78h]
  uint32_t v6[26]; // [esp+1Ch] [ebp-68h] BYREF

  v6[25] = dword_796E50;
  qmemcpy(
    v6,
    (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/Suriken.ptl"),  // 调虚槽 +588
    0x62u);
  v5[0] = 0;
  v5[1] = 90;
  v5[2] = 180;
  v5[3] = 270;
  for ( i = 0; i < 4; ++i )  // 循环：i 从 0 递增到 4
  {
    v3 = *this;
    v6[18] = v5[i];  // v6[18] = 取 v5[i]
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v3 + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
        this,
        30079,
        *(this + 2155),  // this+8620〔uAI8620(推断)〕
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
  result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "THROW_SHURIKEN",  // 标签 THROW_SHURIKEN
             -1,
             0,
             0);
  *(this + 2168) = -1;  // this+8672〔uAI8672(推断)〕
  return result;
}



// 手里剑技能变体：Suriken.ptl + THROW_SHURIKEN
// ------------------------------------------------------------
// 0x59EC60 sub_59EC60 —— 手里剑斜十字四连投
// 与 ·0x59EB90 同构（差异：角向表 45/135/225/315 度向）；30079 四连发 + THROW_SHURIKEN 播报
// ------------------------------------------------------------
int /*thiscall*/ sub_59EC60(uint32_t *this)  // 实现：手里剑斜十字四连投
{
  int i; // esi
  int v3; // edx
  int result; // eax
  uint32_t v5[4]; // [esp+Ch] [ebp-78h]
  uint32_t v6[26]; // [esp+1Ch] [ebp-68h] BYREF

  v6[25] = dword_796E50;
  qmemcpy(
    v6,
    (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/Suriken.ptl"),  // 调虚槽 +588
    0x62u);
  v5[0] = 45;
  v5[1] = 135;
  v5[2] = 225;
  v5[3] = 315;
  for ( i = 0; i < 4; ++i )  // 循环：i 从 0 递增到 4
  {
    v3 = *this;
    v6[18] = v5[i];  // v6[18] = 取 v5[i]
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v3 + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
        this,
        30079,
        *(this + 2155),  // this+8620〔uAI8620(推断)〕
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
  result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "THROW_SHURIKEN",  // 标签 THROW_SHURIKEN
             -1,
             0,
             0);
  *(this + 2168) = -1;  // this+8672〔uAI8672(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59ED30 sub_59ED30 —— 四向 30065 弹幕齐射
// 从 this+2176 槽对象经其 vt+28 克隆粒子参数面，按角向表 310/340/20/50 连发四枚 30065，
// 末尾 this+2168=-1（与手里剑族同款复位【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_59ED30(int *this)  // 实现：四向 30065 弹幕齐射
{
  int fld_e2176; // ecx | =+0x2200 字段 x1
  int i; // esi
  int v4; // edx
  int result; // eax
  uint32_t v6[4]; // [esp+Ch] [ebp-78h]
  uint32_t v7[26]; // [esp+1Ch] [ebp-68h] BYREF

  fld_e2176 = *(this + 2176);  // this+8704〔pSegNameTbl8704(推断)〕
  v7[25] = dword_796E50;
  qmemcpy(v7, (const void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2176 + 28))(fld_e2176), 0x62u);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
  v6[0] = 310;
  v6[1] = 340;
  v6[2] = 20;
  v6[3] = 50;
  for ( i = 0; i < 4; ++i )  // 循环：i 从 0 递增到 4
  {
    v4 = *this;
    v7[18] = v6[i];  // v7[18] = 取 v6[i]
    result = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v4 + 580))(
               this,
               30065,
               *(this + 2155),  // this+8620〔uAI8620(推断)〕
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
  *(this + 2168) = -1;  // this+8672〔uAI8672(推断)〕
  return result;
}



// AI 相位门（this+8612/8672）
// ------------------------------------------------------------
// 0x59EDD0 sub_59EDD0 —— 投掷相位三选一调度
// rand 取模 3 写入 this+8672：0 走 ·0x59EB90 十字投、1 走 ·0x59EC60 斜十字、
// 2 走 ·0x59ED30 弹幕，各支路均置 8612 相位标志
// ------------------------------------------------------------
int /*thiscall*/ sub_59EDD0(int this)  // 实现：投掷相位三选一调度
{
  int nRand; // eax
  int v3; // eax
  int result; // eax

  nRand = rand() % 3;  // nRand = 调 rand
  *(uint32_t *)(this + 8672) = nRand;  // this+8672〔uAI8672(推断)〕
  if ( nRand != 0 )  // 若 nRand 非 0
  {
    v3 = nRand - 1;
    if ( v3 == 0 )  // 若 v3 为 0
    {
      result = sub_59EC60((uint32_t *)this);  // 手里剑斜十字四连投
      *(uint8_t *)(this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
      return result;
    }
    result = v3 - 1;
    if ( result == 0 )  // 若 result 为 0
    {
      result = sub_59ED30((int *)this);  // 四向 30065 弹幕齐射
      *(uint8_t *)(this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
      return result;
    }
  }
  else  // 否则分支
  {
    result = sub_59EB90((uint32_t *)this);  // 手里剑十字四连投（0/90/180/270 度向）
  }
  *(uint8_t *)(this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59EE30 sub_59EE30 —— 三元组块搬移辅助
// 将 [uArg1,uArg2) 区间按 3×uint32 步长复制到 uArg3（容器元素为三元组记录），
// 供 ·0x59FDB0 定点插入搬移调用，属容器内核而非业务 AI【推断：vector 辅助内核】
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_59EE30(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：三元组块搬移辅助
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; result += 3 )  // 遍历循环
  {
    if ( result != nullptr )  // 若 result 有效（非空）
    {
      *result = *uArg12;
      result[1] = uArg12[1];  // result[1] = 取 uArg12[1]
      result[2] = uArg12[2];  // result[2] = 取 uArg12[2]
    }
    uArg12 += 3;
  }
  return result;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59EE70 sub_59EE70 —— 状态事件处理器（入场挂光环/退场清相位）
// 事件 5（入场）：50% 概率经 sub_64BDF0（战斗光环基础数据）挂 this+1814 槽光环；
// 事件 8（退场）：附加参数对象 +4 字段为零时清 this+8612 相位字节；末尾 sub_4E33D0 基类收尾
// ------------------------------------------------------------
int /*thiscall*/ sub_59EE70(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：状态事件处理器（入场挂光环/退场清相位）
{
  if ( ArgList == 5 )  // 若 ArgList == 5
  {
    if ( rand() % 100 < 50 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
      sub_64BDF0(this, *(this + 1814));  // 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
  }
  else if ( ArgList == 8 && **(uint32_t **)(LODWORD(fArg3) + 4) == 0 )
  {
    *((uint8_t *)this + 8612) = 0;  // this+8612〔相位字节〕
  }
  return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59EEF0 sub_59EEF0 —— 事件包装（退场补停音变体）
// 与 ·0x59EE70 同构转发；追加 this+1639（主状态镜像）==5 时经 vt+216 音效槽停 3510 轨道
// 【推断：状态 5 收尾时收掉循环音】
// ------------------------------------------------------------
int /*thiscall*/ sub_59EEF0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：事件包装（退场补停音变体）
{
  int result; // eax

  result = sub_59EE70(this, ArgList, fArg3, nArg4, nArg5);  // 状态事件处理器（入场挂光环/退场清相位）
  if ( *(this + 1639) == 5 )  // this+6556〔大状态ID〕
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 3510);  // 调虚槽 +216：音效 TAG 查询
  return result;
}



// 指挥 AI：GOBLIN_COMMAND（RTTI cast, 67L）
// ------------------------------------------------------------
// 0x59EF30 sub_59EF30 —— 哥布林指挥号令（GOBLIN_COMMAND 群体指挥）
// 遍历 this+29 容器对象表：vt+40(obj,17) 类型校验、vt+376 阵营号与本怪一致【推断】、
// __RTDynamicCast 到 CNGoblinIslandGab（岛哥布林）、vt+156 距离 ≤300 四重门；
// 命中后 sub_4D82D0 弹头顶 Command.ani 指挥气泡、sub_49C620(7,目标坐标)【推断：指令包】、
// vt+212 播报 GOBLIN_COMMAND；vt+40 的 17 在既有批注记玩家类，此处后接哥布林 RTTI，
// 故 17 应为生物/怪物类 id【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_59EF30(uint32_t *this)  // 实现：哥布林指挥号令（GOBLIN_COMMAND 群体指挥）
{
  unsigned int i; // edi
  int fld_e29; // ecx | =+0x0074 字段 x2（证据 005FD6C0）
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // edi
  int v11; // ebx
  int v12; // eax
  int fld_e1813; // eax | =+0x1C54 字段 x1
  int v14; // [esp+0h] [ebp-10h]
  unsigned int v15; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v4 = *(uint32_t *)(fld_e29 + 8);
    v15 = i;
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;  // 跳出循环/分支
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 若 v6 != 0
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else  // 否则分支
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 若 v9 != 0
        pObj = *(uint32_t *)(v9 + 4 * i);
      else  // 否则分支
        pObj = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调虚槽 +376：坐标同步包（type 37）
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )  // 调虚槽 +376：坐标同步包（type 37）
      {
        v12 = __RTDynamicCast(
                pObj,
                0,
                &IRDActiveObject `RTTI Type Descriptor',
                &CNGoblinIslandGab `RTTI Type Descriptor',
                0);
        if ( v12 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 156))(this, v12) <= 300 )  // 调虚槽 +156：与目标 x/y 距离绝对值
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813), 0);  // this+7252〔pTarget7252〕
          sub_49C620(7, fld_e1813, v14);  // 命令下发包装（组 id = this+4，值重复两遍）
          sub_4D82D0(0, 0);  // 头顶气泡 Command.ani（a2/a3 = 定位偏移）
          v14 = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*this + 212))(this, "GOBLIN_COMMAND", -1, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
        }
      }
      i = v15;
    }
  }
  return result;
}



// 子类扩展字段复位（this+8624..8632）
// ------------------------------------------------------------
// 0x59F040 sub_59F040 —— 蓄力收手与架招联动（事件 14 + 大状态 14）
// 先转发 ·0x59EE70；事件 14（蓄力/架招事件号）时 sub_4926A0 复位 this+8628 槽对象
// 帧游标、vt+196 重设动作；this+8632 联动对象 +992 标志或大状态(vt+840)==14，且
// 动作号(vt+340)∈{60,61}、vt+736 计数>0【推断】时：大状态 this+6556=4、清 8624 相位、
// this+6664=-1500（位移速度【推断】）、sub_495890(2,0) 并自 this+6216 恢复 this+6180
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_59F040(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：蓄力收手与架招联动（事件 14 + 大状态 14）
{
  int fld_21B8; // eax | =+0x21B8 字段 x4（证据 005CDA80）
  uint32_t *result; // eax
  int fld_21B82; // ecx  | +0x21B8 → 【推断】联动对象〔5F150 检其 +992 标志触发架招〕（CNGoblinKagelBase；va=0059F150）

  sub_59EE70((uint32_t *)this, ArgList, fArg3, nArg4, nArg5);  // 状态事件处理器（入场挂光环/退场清相位）
  if ( ArgList == 14 )  // 若 ArgList == 14
  {
    sub_4926A0(*(uint32_t *)(this + 8628));  // 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(this + 8628));  // 调虚槽 +196：动画对象设置（换域 + 播放）
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this) + 40) = 0;  // 调虚槽 +340：三元组基址（+284，vt+340）
  }
  fld_21B8 = *(uint32_t *)(this + 8632);  // fld_21B8 = 读 this+8632
  if ( (fld_21B8 != 0 && *(uint8_t *)(fld_21B8 + 992) != 0  // 若 fld_21B8 != 0
     || (result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this)) == (uint32_t *)14)  // 调虚槽 +840：大状态 getter（this+6556）
    && (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this) == 60  // 调虚槽 +340：三元组基址（+284，vt+340）
     || *(result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this)) == 61) )  // 调虚槽 +340：三元组基址（+284，vt+340）
  {
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result != (uint32_t *)9 )
    {
      result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 736))(this);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
      if ( (int)result > 0 )
      {
        fld_21B82 = *(uint32_t *)(this + 8632);  // fld_21B82 = 读 this+8632
        *(uint32_t *)(this + 6556) = 4;  // this+6556〔大状态ID〕
        *(uint8_t *)(this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
        if ( fld_21B82 != 0 )  // 若 fld_21B82 非 0
          sub_621200();  // 调 触发切断坠落
        *(uint32_t *)(this + 324) = 0;  // this+324〔nRandPick324〕
        *(uint32_t *)(this + 6664) = -1500;  // this+6664〔uUI6664〕
        sub_495890(2, 0);  // 模式选择式方位设置（1/2/其他 三分支）
        result = *(uint32_t **)(this + 6180);  // this+6180〔pAtkCtxC6180〕
        if ( result == nullptr )  // 若 result 为空
        {
          result = *(uint32_t **)(this + 6216);  // result = 读 this+6216
          *(uint32_t *)(this + 6180) = *result;  // this+6180〔pAtkCtxC6180〕
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
// 0x59F150 sub_59F150 —— 岛哥布林大型主状态机（蓄力/架招/落地/惊叹相位）
// ·0x59E570 攻击触发门先行；大状态(vt+840)==14 时收手（清 8624、sub_621200、this+6664=-1500、sub_495890）；
// this+8632 联动对象 +992 标志时经 vt+560 写反应态 14（架招）、动作号(vt+340)∈{60,61} 时强制 this+6556=4；
// vt+128 高度≤0 落地：sub_58AD30 判可行走、不可走则 vt+140 推挤落位（vt+116 采样三格入 this+8300[3]【推断】）；
// this+8640 计时门到点：sub_4D83E0 弹 Exclamation.ani 惊叹气泡并重挂 1500ms 倒计时
// ------------------------------------------------------------
char /*thiscall*/ sub_59F150(int this)  // 实现：岛哥布林大型主状态机（蓄力/架招/落地/惊叹相位）
{
  int v2; // edi
  int fld_21B8; // eax | =+0x21B8 字段 x4（证据 005CDA80）
  int pThis_80; // eax
  int v5; // eax
  int pThis_78; // eax
  int pThis_782; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int *pThis_206C; // ebx
  int fld_21DC; // edi | =+0x21DC 字段 x3（证据 005A82B0）
  int fld_144; // edi | =+0x0144 字段 x1（证据 004D6970）
  int v15; // [esp-8h] [ebp-1Ch]
  int v16; // [esp+Ch] [ebp-8h] BYREF
  int pThis_7822; // [esp+10h] [ebp-4h] BYREF

  sub_59E570();  // 攻击触发门（同构 ·0x59D360 的门结构，差异：经 vt+1312 直接触发动作）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14  // 调虚槽 +840：大状态 getter（this+6556）
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )  // 调虚槽 +200：取动画对象
  {
    v2 = 0;
    if ( *(uint32_t *)(this + 8632) != 0 && *(uint8_t *)(this + 8624) == 1 )  // 复合条件判定（与/或）
    {
      *(uint8_t *)(this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
      sub_621200();  // 调 触发切断坠落
      *(uint32_t *)(this + 324) = 0;  // this+324〔nRandPick324〕
      *(uint32_t *)(this + 6664) = -1500;  // this+6664〔uUI6664〕
      sub_495890((int *)this, 2, 0);  // 模式选择式方位设置（1/2/其他 三分支）
    }
  }
  else  // 否则分支
  {
    v2 = 0;
  }
  fld_21B8 = *(uint32_t *)(this + 8632);  // fld_21B8 = 读 this+8632
  if ( fld_21B8 != 0  // 若 fld_21B8 非 0
    && *(uint8_t *)(fld_21B8 + 992) != 0
    && *(uint8_t *)(this + 8636) == 0  // this+8636〔pDollTarget(推断)〕
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this) == 60  // 调虚槽 +340：三元组基址（+284，vt+340）
     || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this) == 61) )  // 调虚槽 +340：三元组基址（+284，vt+340）
  {
    (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 14, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    *(uint8_t *)(this + 8636) = 1;  // this+8636〔pDollTarget(推断)〕
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 && *(uint8_t *)(this + 8624) == 0 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    if ( *(uint32_t *)(this + 6180) == 0 )  // this+6180〔pAtkCtxC6180〕
      *(uint32_t *)(this + 6180) = *(uint32_t *)(*(uint32_t *)(this + 6216) + 4);  // this+6180〔pAtkCtxC6180〕
    *(uint32_t *)(this + 7252) = 0;  // this+7252〔pTarget7252〕
    *(uint32_t *)(this + 6556) = 4;  // this+6556〔大状态ID〕
    *(uint32_t *)(this + 6664) = -1500;  // this+6664〔uUI6664〕
    sub_495890((int *)this, 2, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  }
  pThis_80 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  if ( pThis_80 <= 0 && *(uint32_t *)(this + 6664) == -1500 )  // this+6664〔uUI6664〕
  {
    v5 = *(uint32_t *)this;
    *(uint32_t *)(this + 6556) = 0;  // this+6556〔大状态ID〕
    *(uint32_t *)(this + 6664) = 0;  // this+6664〔uUI6664〕
    *(uint8_t *)(this + 6740) = 1;  // this+6740〔bFreeze6740〕
    v15 = (*(int (/*thiscall*/ **)(int))(v5 + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
    pThis_78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);  // 调虚槽 +120：动画对象
    pThis_80 = sub_58AD30(pThis_78, v15, 0);  // 可行走判定：网格值≠2 且（允许对角 或 网格值≠1）→ true
    if ( pThis_80 == 0 )  // 若 pThis_80 为 0
    {
      pThis_782 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);  // 调虚槽 +120：动画对象
      v8 = *(uint32_t *)this;
      pThis_7822 = pThis_782;
      v9 = (*(int (/*thiscall*/ **)(int))(v8 + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      v10 = *(uint32_t *)this;
      v16 = v9;
      (*(void (/*thiscall*/ **)(int, int *, int *, int, int, int, int, int))(v10 + 140))(  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
        this,
        &pThis_7822,
        &v16,
        pThis_7822,
        v9,
        240,
        1,
        1);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)this + 108))(this, pThis_7822, v16, 0);  // 调虚槽 +108：CNRDPrivateStoreWindow__vmt6C 槽（10 行）
      pThis_206C = (int *)(this + 8300);  // this+8300〔pHoldObj(推断)〕
      do  // do-while 循环体起点
      {
        pThis_80 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 116))(this, v2);  // 调虚槽 +116：取伤害数值
        *pThis_206C = pThis_80;
        ++v2;
        ++pThis_206C;
      }
      while ( v2 < 3 );  // 条件循环
    }
  }
  if ( *(uint32_t *)(this + 8640) != 0 )  // this+8640〔uCastSlot8640(推断)〕
  {
    fld_21DC = *(uint32_t *)(this + 8668);  // fld_21DC = 读 this+8668
    pThis_80 = sub_699000(this + 8644);  // 【clock_now(clk)】
    if ( pThis_80 >= fld_21DC )  // 若 pThis_80 >= fld_21DC
    {
      fld_144 = *(uint32_t *)(this + 324);  // this+324〔nRandPick324〕
      *(uint32_t *)(this + 8640) = 0;  // this+8640〔uCastSlot8640(推断)〕
      *(uint32_t *)(this + 324) = 0;  // this+324〔nRandPick324〕
      sub_4D83E0((int *)this, 0, 0);  // 头顶气泡 Exclamation.ani（惊叹；同 0x4D82D0 结构）
      *(uint32_t *)(this + 324) = fld_144;  // this+324〔nRandPick324〕
      *(uint8_t *)(this + 8657) = 0;  // this+8657〔bAI8657〕
      *(uint8_t *)(this + 8658) = 0;  // this+8658〔bAI8658〕
      LOBYTE(pThis_80) = sub_698F90(this + 8644, 1500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
  }
  return pThis_80;
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x59F390 sub_59F390 —— 减速面应用（增益撤销半程）
// nArg2==0 时遍历 this+1905 列表逐项 ×0.8333（5/6 减速系数，与 ·0x59F420 的 ×1.2 互逆）；
// vt+672 定位 +858 浮点字段经 sub_41A5E0/41A590 减 0.2 后 vt+676 提交
// ------------------------------------------------------------
int /*thiscall*/ sub_59F390(uint32_t *this, int nArg2, int nArg3)  // 实现：减速面应用（增益撤销半程）
{
  int result; // eax
  unsigned int v5; // edx
  int i; // edi
  int fld_e1905; // ecx | =+0x1DC4 字段 x1（证据 0059A020）
  int v8; // eax
  double v9; // st7
  unsigned int v10; // edi
  int v11; // edx
  int v12; // [esp+Ch] [ebp+8h]

  result = nArg2;
  if ( nArg2 == 0 )  // 若 nArg2 为 0
  {
    v5 = 0;
    for ( i = 0; ; i += 32 )  // 遍历循环
    {
      fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
      if ( fld_e1905 == 0 || v5 >= (*(this + 1906) - fld_e1905) >> 5 )  // 若 fld_e1905 == 0
        break;  // 跳出循环/分支
      v8 = i + fld_e1905;
      v9 = *(float *)(fld_e1905 + i + 4) * 0.83333331;
      ++v5;
      *(float *)(v8 + 4) = v9;
    }
    v10 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;  // 调虚槽 +672：自身 HP
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v10)) - 0.2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v10, v11, v12);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  return result;
}



// 冰盾技能（岛哥布林版）：sub_64B0F0 发射 Monster/Goblin/Animation_IslandGoblin/
//   ChillingAura 光环粒子 + vt+212 SHIELD_ICE + WINDSHIELD_LOOP（102L）
// ------------------------------------------------------------
// 0x59F420 sub_59F420 —— 冰盾开启（ChillingAura 光环 + WINDSHIELD_LOOP 循环音）
// 先清 this+7531..7596 分身/攻击参数面；Block=1/2 时仅置 7534/1893 盾层计数【推断】；
// Block 为空（常态开盾）：this+1905 列表 ×1.2 增速、+858 浮点 +0.2，new 0x8C 经
// sub_64B0F0 装载 Monster/Goblin/Animation_IslandGoblin/ChillingAura 光环粒子并挂接；
// sub_4DB200(24,2) 15% 概率随机文案；vt+212 播 SHIELD_ICE、vt+216 切 3510 轨后
// 以 3510 为声道循环 WINDSHIELD_LOOP
// ------------------------------------------------------------
int /*thiscall*/ sub_59F420(char *this, void *Block, int nArg3)  // 实现：冰盾开启（ChillingAura 光环 + WINDSHIELD_LOOP 循环音）
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
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  pThis_1D73 = this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *((uint32_t *)this + 1893) = 0;  // this[1893] = 0
  *((uint32_t *)this + 1892) = 0;  // this[1892] = 0
  *((uint32_t *)this + 1891) = 0;  // this[1891] = 0
  *((uint32_t *)this + 1897) = 0;  // this+7588〔uForm7588〕
  *((uint32_t *)this + 1896) = 0;  // this+7584〔uForm7584〕
  *((uint32_t *)this + 1895) = 0;  // this[1895] = 0
  *((uint32_t *)this + 1894) = 0;  // this[1894] = 0
  *((uint32_t *)this + 1899) = 0;  // this[1899] = 0
  if ( Block != nullptr )  // 若 Block 有效（非空）
  {
    result = (int)Block - 1;
    if ( Block == (void *)1 || (result = (int)Block - 2, Block == (void *)2) )  // 复合条件判定（与/或）
    {
      *(this + 7534) = 1;
      *((uint32_t *)this + 1893) = 2;  // this[1893] = 2
    }
  }
  else  // 否则分支
  {
    v6 = 0;
    for ( i = 0; ; i += 32 )  // 遍历循环
    {
      pThis_771 = *((uint32_t *)this + 1905);  // this+7620〔pStatusPanel(推断)〕
      if ( pThis_771 == 0 || v6 >= (*((uint32_t *)this + 1906) - pThis_771) >> 5 )  // 若 pThis_771 == 0
        break;  // 跳出循环/分支
      v9 = i + pThis_771;
      v10 = *(float *)(pThis_771 + i + 4) * 1.2;
      ++v6;
      *(float *)(v9 + 4) = v10;
    }
    pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 858;  // 调虚槽 +672：自身 HP
    *(float *)&Blocka = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, v12, Blocka);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
    if ( dword_9A05D4 <= 2 )  // 若 dword_9A05D4 <= 2
    {
      (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
      sub_53F6A0(this);  // 调 收尾路径
      if ( operator new(0x8Cu) != nullptr )  // new(140 字节) 分配对象
        pObj = sub_64B0F0(0, 0x40000000, 7, "Monster/Goblin/Animation_IslandGoblin/ChillingAura");  // 动画装载模板 %s.ani/%sDamage.ani（5910D0/42FCB0/431860/493400）
      else  // 否则分支
        pObj = 0;
      (*(void (/*thiscall*/ **)(int, char *, char *, int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
        pObj,
        this,
        this,
        1,
        0,
        0,
        -1);
      sub_4DB200(24, 2);  // 15% 概率随机文案触发（0x4DB130 的门包装）
      (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
        this,
        "SHIELD_ICE",  // 标签 SHIELD_ICE
        -1,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 216))(this, 3510);  // 调虚槽 +216：音效 TAG 查询
      return (*(int (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
               this,
               "WINDSHIELD_LOOP",  // 标签 WINDSHIELD_LOOP
               3510,
               0,
               0);
    }
  }
  return result;
}



// 硬直/相位字段（this+208/+8612/+8624）
// ------------------------------------------------------------
// 0x59F620 sub_59F620 —— 攻击相位驱动（主状态镜像 8 门控）
// this+1639==8（攻击）且 8612 未置：vt+208 切动作、vt+1312 收尾并置 8612 防重入；
// 1639==0 且 8624 置位时 vt+196 恢复动作【推断：vt+208/196 为动作切换槽】；末尾转 ·0x59F150
// ------------------------------------------------------------
char /*thiscall*/ sub_59F620(int *this)  // 实现：攻击相位驱动（主状态镜像 8 门控）
{
  int fld_e1639; // eax | =+0x199C 字段 x1（证据 005EA970）
  int fld_e1554; // ecx | =+0x1848 字段 x15（证据 005EA970）

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    fld_e1639 = *(this + 1639);  // this+6556〔大状态ID〕
    if ( fld_e1639 != 0 )  // 若 fld_e1639 非 0
    {
      if ( fld_e1639 == 8  // 若 fld_e1639 == 8
        && sub_41A5E0((unsigned int)(this + 1757)) == 0  // crypt4byte 解密校验（·0x41A590 逆运算）
        && *((uint8_t *)this + 8612) == 0  // this+8612〔uAI8612(推断)〕
        && *(int *)(*(this + 30) + 148) > 2 )  // this+120〔pAnimObj〕
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));  // 调虚槽 +208：定时器移除
        (*(void (/*thiscall*/ **)(int *))(*this + 1312))(this);  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
        *((uint8_t *)this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
      }
    }
    else if ( *((uint8_t *)this + 8624) == 1 )  // this+8624〔uAI8624(推断)〕
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1540));  // 调虚槽 +196：动画对象设置（换域 + 播放）
    }
  }
  if ( *(this + 1639) != 8 )  // this+6556〔大状态ID〕
  {
    fld_e1554 = *(uint32_t *)*(this + 1554);  // fld_e1554 = 读 this+1554
    if ( fld_e1554 != 0 )  // 若 fld_e1554 非 0
      (*(void (/*thiscall*/ **)(int *, int))(*this + 208))(this, fld_e1554);  // 调虚槽 +208：定时器移除
  }
  return sub_59F150(this);  // 岛哥布林大型主状态机（蓄力/架招/落地/惊叹相位）
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59F6D0 sub_59F6D0 —— 状态事件处理器（·0x59F040 变体）
// 与 ·0x59EE70 同构门：事件 5 半数概率挂 sub_64BDF0 光环（this+1814 槽）；事件 8 清 8612
// 并 sub_4926A0 复位 this+1554 槽帧游标，末尾转 ·0x59F040
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_59F6D0(int **this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：状态事件处理器（·0x59F040 变体）
{
  if ( ArgList == 5 )  // 若 ArgList == 5
  {
    if ( rand() % 100 < 50 && ((uint8_t (/*thiscall*/ *)(int **))(*this)[77])(this) != 0 )  // 复合条件判定（与/或）
      sub_64BDF0(this, *(this + 1814));  // 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
  }
  else if ( ArgList == 8 && **(uint32_t **)(LODWORD(fArg3) + 4) == 0 )
  {
    sub_4926A0(**(this + 1554));  // 帧游标复位（+44 帧数组；递归子链 +204）
    ((void (/*thiscall*/ *)(int **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      100,
      **(this + 1554),  // this+1554〔槽帧游标〕
      0,
      0,
      0,
      0);
    *((uint8_t *)this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  }
  return sub_59F040((int)this, ArgList, fArg3, nArg4, nArg5);  // 蓄力收手与架招联动（事件 14 + 大状态 14）
}



// 硬直/相位字段（this+208/+8612）
// ------------------------------------------------------------
// 0x59F770 sub_59F770 —— 攻击相位驱动（大状态 6556 变体）
// 与 ·0x59F620 同构（差异：以大状态 this+6556==8 为门、段号槽 this+7028、
// this+6216 为动作源）；末尾转 ·0x59F150
// ------------------------------------------------------------
char /*thiscall*/ sub_59F770(int this)  // 实现：攻击相位驱动（大状态 6556 变体）
{
  int fld_1848; // ecx | =+0x1848 字段 x15（证据 005EA970）

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) == 0 )  // 调虚槽 +308：是否本地玩家
    goto LABEL_7;
  if ( *(uint32_t *)(this + 6556) == 8 )  // this+6556〔大状态ID〕
  {
    if ( sub_41A5E0(this + 7028) == 0 && *(uint8_t *)(this + 8612) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) > 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, **(uint32_t **)(this + 6216));  // 调虚槽 +208：定时器移除
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1312))(this);  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
      *(uint8_t *)(this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
    }
LABEL_7:  // 标签 LABEL_7（跳转合流点）
    if ( *(uint32_t *)(this + 6556) == 8 )  // this+6556〔大状态ID〕
      return sub_59F150((int *)this);  // 岛哥布林大型主状态机（蓄力/架招/落地/惊叹相位）
  }
  fld_1848 = **(uint32_t **)(this + 6216);  // this+6216〔pTbl6216(推断)〕
  if ( fld_1848 != 0 )  // 若 fld_1848 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 208))(this, fld_1848);  // 调虚槽 +208：定时器移除
  return sub_59F150((int *)this);  // 岛哥布林大型主状态机（蓄力/架招/落地/惊叹相位）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59F800 sub_59F800 —— 对象注销联动清槽（2158 与 2172 容器）
// sub_4D9170 注销通知后，this+2158 跟踪槽与 this+2172 三元组容器（步长 12）中
// 命中 nArg2 的表项一并清零【推断：被毁对象引用清扫】
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_59F800(unsigned int *this, int nArg2)  // 实现：对象注销联动清槽（2158 与 2172 容器）
{
  int fld_e2158; // eax | =+0x21B8 字段 x4（证据 005CDA80）
  int v4; // ebx
  unsigned int i; // edi
  unsigned int result; // eax
  int fld_e2172; // eax | =+0x21F0 字段 x1（证据 005CD360）
  int v8; // edx
  uint32_t *v9; // eax

  sub_4D9170(nArg2);  // 调 消亡通知
  fld_e2158 = *(this + 2158);  // this+8632〔bDevourFlag(推断)〕
  v4 = 0;
  if ( fld_e2158 != 0 && nArg2 == fld_e2158 )  // 若 fld_e2158 != 0 与/或 nArg2 == fld_e2158
    *(this + 2158) = 0;  // this+8632〔bDevourFlag(推断)〕
  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    result = *(this + 2172);  // this+8688〔bVec8688(推断)〕
    if ( result == 0 )  // 若 result 为 0
      break;  // 跳出循环/分支
    result = (int)(*(this + 2173) - result) / 12;  // this+8692〔uVec8692(推断)〕
    if ( i >= result )  // 若 i >= result
      break;  // 跳出循环/分支
    fld_e2172 = *(this + 2172);  // this+8688〔bVec8688(推断)〕
    v8 = *(uint32_t *)(fld_e2172 + v4);
    v9 = (uint32_t *)(v4 + fld_e2172);
    if ( v8 == nArg2 )  // 若 v8 == nArg2
      *v9 = 0;
    v4 += 12;
  }
  return result;
}



// AI 字段访问（this+8700）
// ------------------------------------------------------------
// 0x59F880 sub_59F880 —— 相位字节复位（7620 面板 +8700）
// 清 this+7620 所指面板偏移 0/32/64 三标志与 this+8700 相位字节（与 ·0x59FD50 置位互逆）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_59F880(int this)  // 实现：相位字节复位（7620 面板 +8700）
{
  uint8_t *result; // eax

  **(uint8_t **)(this + 7620) = 0;  // this+7620〔所指面板偏移〕
  *(uint8_t *)(*(uint32_t *)(this + 7620) + 32) = 0;  // this+7620〔pStatusPanel(推断)〕
  result = (uint8_t *)(*(uint32_t *)(this + 7620) + 64);  // this+7620〔pStatusPanel(推断)〕
  *result = 0;
  *(uint32_t *)(this + 8700) = 0;  // this+8700〔uPhase8700(推断)〕
  return result;
}



// 瞄准炸弹 AI：Particle/AimingBomb.ptl（74L）
// ------------------------------------------------------------
// 0x59F8B0 sub_59F8B0 —— 瞄准炸弹逐目标齐射（AimingBomb.ptl ×30077）
// 与 ·0x59E790 同族（差异：无 10% 概率演出，按 this+2172 目标容器以 this+2175 计数逐发）；
// 目标存活走 vt+164/vt+8 实时弹道换算，否则直用容器缓存坐标（+4/+8 字段【推断】）；
// vt+580 逐发 30077 并递增计数，末尾置 8612 相位
// ------------------------------------------------------------
int /*thiscall*/ sub_59F8B0(int *this)  // 实现：瞄准炸弹逐目标齐射（AimingBomb.ptl ×30077）
{
  uint64_t v2; // rax
  int fld_e2175; // edi | =+0x21FC 字段 x1（证据 00599D50）
  int v4; // esi
  int fld_e2172; // edi | =+0x21F0 字段 x1（证据 005CD360）
  uint64_t v6; // rax
  int v7; // eax
  int v8; // eax
  int fld_e21722; // ecx
  int fld_e2155; // ecx | =+0x21AC 字段 x1（证据 005AF910）
  int v11; // edx
  uint32_t v13[26]; // [esp+10h] [ebp-68h] BYREF

  v13[25] = dword_796E50;
  qmemcpy(
    v13,
    (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/AimingBomb.ptl"),  // 调虚槽 +588
    0x62u);
  v2 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v13[7] + 3)) / (double)v13[17] * 1000.0);
  fld_e2175 = *(this + 2175);  // this+8700〔uPhase8700(推断)〕
  v4 = 2 * v2;
  if ( fld_e2175 >= 0 )  // 若 fld_e2175 >= 0
  {
    LODWORD(v2) = *(this + 2172);  // this+8688〔bVec8688(推断)〕
    if ( (uint32_t)v2 != 0 )
      LODWORD(v2) = (*(this + 2173) - (int)v2) / 12;  // this+8692〔uVec8692(推断)〕
    if ( fld_e2175 < (unsigned int)v2 )
    {
      fld_e2172 = *(uint32_t *)(*(this + 2172) + 12 * fld_e2175);  // fld_e2172 = 读 this+2172
      if ( fld_e2172 != 0 && (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 1244))(this, fld_e2172) != 0 )  // 调虚槽 +1244
      {
        v6 = (uint64_t)((double (/*thiscall*/ *)(int *, int, uint32_t))*(uint32_t *)(*this + 164))(this, fld_e2172, 0);  // 调虚槽 +164：★ 与目标朝向角度（atan2 角度制；3D 俯视判定）【新发现(会话 3)】
        HIDWORD(v6) = *this;
        v13[18] = v6;
        v7 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(HIDWORD(v6) + 8))(this, fld_e2172, 0);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTT…
        *(uint32_t *)((char *)&v13[3] + 3) = 1000 * v7 / v4;
        v8 = (*(int (/*fastcall*/ **)(int *, int, int, uint32_t))(*this + 8))(this, 1000 * v7 % v4, fld_e2172, 0);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
      }
      else  // 否则分支
      {
        fld_e21722 = *(this + 2172) + 12 * *(this + 2175);  // this+8688〔bVec8688(推断)〕等 2 字段
        v13[18] = *(uint32_t *)(fld_e21722 + 4);
        *(uint32_t *)((char *)&v13[3] + 3) = 1000 * *(uint32_t *)(fld_e21722 + 8) / v4;
        v8 = *(uint32_t *)(fld_e21722 + 8);
      }
      fld_e2155 = *(this + 2155);  // this+8620〔uAI8620(推断)〕
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
      ++*(this + 2175);  // this+8700〔uPhase8700(推断)〕
    }
  }
  *((uint8_t *)this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
  return v2;
}



// AI 相位辅助（76L）
// ------------------------------------------------------------
// 0x59FA10 sub_59FA10 —— 岛哥布林 AI 决策机（1787 相位 switch + 行为字写入）
// 相位字段 this+1787 分派，经 vt+1104 行为字写入器写行为码：相位 0 或缺目标
// this+1813 → 行为 15（施放入场）；相位 1 时 3% 概率 sub_59EF30 群体指挥号令、
// 5%（this+1909 空则 10%）→ 行为 2、10% 且与目标 vt+120 差 ≤60 且自身位于
// [40, sub_425050(基准)-40] 窗内 → 行为 3【推断：走位/投弹预备】；
// 相位 13/15 有目标则写行为 1（追击【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_59FA10(int *this)  // 实现：岛哥布林 AI 决策机（1787 相位 switch + 行为字写入）
{
  int result; // eax
  int nRand; // eax
  int v4; // et2
  int fld_e29; // edi | =+0x0074 字段 x2（证据 005FD6C0）
  int fld_e1813; // ebx | =+0x1C54 字段 x1
  int v7; // edi

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);  // 调虚槽 +1104
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);  // 调虚槽 +1104
      result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
      if ( (uint8_t)result != 0 )
      {
        if ( rand() % 100 >= 3 )  // rand()%100 取模随机
        {
          if ( rand() % 100 >= 5 * ((*(this + 1909) == 0) + 1) )  // this+7636〔nPosWinY〕
          {
            nRand = rand();  // nRand = 调 rand
            v4 = nRand % 100;
            result = nRand / 100;
            if ( v4 < 10 )  // 若 v4 < 10
            {
              fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);  // fld_e29 = 读 this+29
              fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
              result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - fld_e1813);  // 调虚槽 +120：动画对象
              if ( result <= 60 )  // 若 result <= 60
              {
                result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
                if ( result > 40 )  // 若 result > 40
                {
                  v7 = sub_425050(fld_e29) - 40;  // 总宽换算
                  result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
                  if ( result < v7 )  // 若 result < v7
                    return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 3);  // 调虚槽 +1104
                }
              }
            }
          }
          else  // 否则分支
          {
            return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 2);  // 调虚槽 +1104
          }
        }
        else  // 否则分支
        {
          return sub_59EF30(this);  // 哥布林指挥号令（GOBLIN_COMMAND 群体指挥）
        }
      }
      return result;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      goto LABEL_4;
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_4:  // 标签 LABEL_4（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 1);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59FB70 sub_59FB70 —— AI 步进 + 架招门（基础版）
// 先 ·0x59FA10 决策步进，vt+308 通过后进 ·0x59E630 架招触发相位门；
// 与 ·0x59FB90 同构（差异：无大状态 14 屏蔽与相位 0 行为 16 写入）
// ------------------------------------------------------------
int /*thiscall*/ sub_59FB70(int *this)  // 实现：AI 步进 + 架招门（基础版）
{
  int result; // eax

  sub_59FA10(this);  // 岛哥布林 AI 决策机（1787 相位 switch + 行为字写入）
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
    return sub_59E630((int)this);  // 架招触发相位门（this+8632/8636）
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59FB90 sub_59FB90 —— AI 步进 + 架招门（蓄力屏蔽变体）
// 与 ·0x59FB70 同构（差异：大状态(vt+840)==14 蓄力/架招期整段屏蔽；
// 相位 this+1787==0 额外经 vt+1104 写行为 16）
// ------------------------------------------------------------
int /*thiscall*/ sub_59FB90(int *this)  // 实现：AI 步进 + 架招门（蓄力屏蔽变体）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result != 14 )  // 若 result != 14
  {
    sub_59FA10(this);  // 岛哥布林 AI 决策机（1787 相位 switch + 行为字写入）
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
      sub_59E630((int)this);  // 架招触发相位门（this+8632/8636）
    result = *(this + 1787);  // this+7148〔nBigState〕
    if ( result == 0 )  // 若 result 为 0
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 16);  // 调虚槽 +1104
  }
  return result;
}



// 主状态门（this+200; 8612/8672 相位）
// ------------------------------------------------------------
// 0x59FBE0 sub_59FBE0 —— 手里剑/瞄准弹相位门（8672 与段号 7028 驱动）
// 相位 this+8672==3 且主状态非零：跑 ·0x59EA80 波次结算；大状态 this+6556==8 且
// 8612 未置时按段号槽 this+7028 分派：0 走 vt+1312 收手、2 触发 ·0x59F8B0 瞄准弹齐射
// ------------------------------------------------------------
char /*thiscall*/ sub_59FBE0(int this)  // 实现：手里剑/瞄准弹相位门（8672 与段号 7028 驱动）
{
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    if ( *(uint32_t *)(this + 8672) == 3 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) != 0 )  // 调虚槽 +200：取动画对象
    {
      sub_59EA80((uint32_t *)this);  // 手里剑四连波次结算（命中帧表驱动）
      return sub_59F150((int *)this);  // 岛哥布林大型主状态机（蓄力/架招/落地/惊叹相位）
    }
    if ( *(uint32_t *)(this + 6556) == 8 && *(uint8_t *)(this + 8612) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) > 2 )  // this+6556〔大状态ID〕
    {
      if ( sub_41A5E0(this + 7028) == 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1312))(this);  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
        return sub_59F150((int *)this);  // 岛哥布林大型主状态机（蓄力/架招/落地/惊叹相位）
      }
      if ( sub_41A5E0(this + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        sub_59F8B0((int *)this);  // 瞄准炸弹逐目标齐射（AimingBomb.ptl ×30077）
    }
  }
  return sub_59F150((int *)this);  // 岛哥布林大型主状态机（蓄力/架招/落地/惊叹相位）
}



// 语音注册：R_GOBLIN_TALK/DMG/DIE（岛哥布林三件套, sub_4015C0）
// ------------------------------------------------------------
// 0x59FC80 sub_59FC80 —— 岛哥布林语音三件套注册（R_GOBLIN_TALK/DMG/DIE）
// 优先级表 this+1698..1702 = {2,2,2,3,4}【推断：语音类别权重】；sub_4015C0 写入三件套
// 语音槽（由 vt+212 播报，见文件头定案）；vt+1308 初始化后 this+1829=500（语音冷却 ms【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_59FC80(uint32_t *this)  // 实现：岛哥布林语音三件套注册（R_GOBLIN_TALK/DMG/DIE）
{
  int result; // eax

  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 调虚槽 +1308：CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
  *(this + 1829) = 500;
  return result;
}



// 登场曲：sub_406D60 写 "B_BULLSEYE_01"（投掷哥布林 BullsEye 曲目槽）
// ------------------------------------------------------------
// 0x59FD00 sub_59FD00 —— 登场 AI + 困难级 BGM 注册（B_BULLSEYE_01）
// 与 ·0x59FB90 同构主干（决策步进 + 架招门 + 相位 0 写行为 16）；this+1943==3
// （困难级难度定案）时经 sub_4015C0 注册登场曲 B_BULLSEYE_01（投掷哥布林 BullsEye 曲目槽）
// ------------------------------------------------------------
int /*thiscall*/ sub_59FD00(int *this)  // 实现：登场 AI + 困难级 BGM 注册（B_BULLSEYE_01）
{
  int result; // eax

  sub_59FA10(this);  // 岛哥布林 AI 决策机（1787 相位 switch + 行为字写入）
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
    sub_59E630((int)this);  // 架招触发相位门（this+8632/8636）
  result = *(this + 1787);  // this+7148〔nBigState〕
  if ( result == 0 )  // 若 result 为 0
  {
    result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 16);  // 调虚槽 +1104
    if ( *(this + 1943) == 3 )  // this+7772〔nCounterState〕
      return sub_4015C0("B_BULLSEYE_01", 0xDu);  // 【std::string构造赋值】
  }
  return result;
}



// 相位门（this+8612/8672/8688..8696）
// ------------------------------------------------------------
// 0x59FD50 sub_59FD50 —— 相位置位与容器释放（撤场清理）
// 与 ·0x59F880 互逆：7620 面板三标志置 1、相位 this+8672=-1；free this+8688 容器
// 并清 8692/8696，末尾清 8612 相位
// ------------------------------------------------------------
void /*thiscall*/ sub_59FD50(int this)  // 实现：相位置位与容器释放（撤场清理）
{
  **(uint8_t **)(this + 7620) = 1;  // this+7620〔pStatusPanel(推断)〕
  *(uint8_t *)(*(uint32_t *)(this + 7620) + 32) = 1;  // this+7620〔pStatusPanel(推断)〕
  *(uint8_t *)(*(uint32_t *)(this + 7620) + 64) = 1;  // this+7620〔pStatusPanel(推断)〕
  *(uint32_t *)(this + 8672) = -1;  // this+8672〔uAI8672(推断)〕
  if ( *(uint32_t *)(this + 8688) != 0 )  // this+8688〔bVec8688(推断)〕
    j__free(*(void **)(this + 8688));  // 释放 this+8688〔bVec8688(推断)〕堆块
  *(uint32_t *)(this + 8688) = 0;  // this+8688〔bVec8688(推断)〕
  *(uint32_t *)(this + 8692) = 0;  // this+8692〔uVec8692(推断)〕
  *(uint32_t *)(this + 8696) = 0;  // this+8696〔uVec8696(推断)〕
  *(uint8_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
}



// 大型 AI（116L；岛哥布林投弹/走位）
// ------------------------------------------------------------
// 0x59FDB0 sub_59FDB0 —— 三元组容器定点插入（vector 12 字节元素内核）
// this+1/+2/+3 为 begin/end/cap 的 12 字节元素 vector，在偏移 uArg3 处插入 Block 三元组：
// 容量足走 sub_504450/5043B0 搬移，不足经 sub_4DA030 扩容 + operator new + sub_623C10
// 构造，溢出 sub_4A30C0 报错；属容器内核而非业务 AI【推断：std::vector 定点插入等价物】
// ------------------------------------------------------------
int /*thiscall*/ sub_59FDB0(int *this, int pArg2, unsigned int uArg3, int *Block)  // 实现：三元组容器定点插入（vector 12 字节元素内核）
{
  int v5; // ecx
  int v6; // edx
  int fld_e1; // ebx | =+0x0004 字段 x2（证据 005FD6C0）
  int result; // eax
  unsigned int fld_e3; // ecx | =+0x000C 字段 x1（证据 00485F70）
  int fld_e2; // eax | =+0x0008 字段 x1（证据 00485F70）
  int fld_e22; // eax | =+0x0058 字段 x1（证据 005FD640）
  unsigned int v13; // ecx
  int fld_e27; // eax | =+0x006C 字段 x1（证据 005F7040）
  int v15; // ebx
  int fld_e13; // eax | =+0x0034 字段 x2（证据 0064A300）
  unsigned int v17; // edi
  void *fld_e23; // ecx
  int fld_e26; // edi | =+0x0068 字段 x1（证据 005FF860）
  int fld_e12; // [esp-18h] [ebp-40h] | =+0x0030 字段 x1（证据 0046C300）
  int fld_e25; // [esp-Ch] [ebp-34h] | =+0x0064 字段 x1（证据 005FD640）
  unsigned int fld_e24; // [esp-8h] [ebp-30h] | =+0x0060 字段 x1（证据 00625C40）
  int v24; // [esp+0h] [ebp-28h] BYREF
  uint32_t v25[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v26; // [esp+24h] [ebp-4h]
  int v27; // [esp+30h] [ebp+8h]
  int v28; // [esp+34h] [ebp+Ch]
  char *Blocka; // [esp+38h] [ebp+10h]
  void *Blockb; // [esp+38h] [ebp+10h]

  v5 = *Block;
  v6 = Block[1];  // v6 = 取 Block[1]
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  result = Block[2];  // result = 取 Block[2]
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )  // 若 fld_e1 非 0
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 12;  // this+12〔nSkillRec12(推断)〕
  }
  else  // 否则分支
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 非 0
      fld_e2 = (*(this + 2) - fld_e1) / 12;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_4A30C0();
    if ( fld_e1 != 0 )  // 若 fld_e1 非 0
      fld_e22 = (*(this + 2) - fld_e1) / 12;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 12 >= uArg3 )
      {
        v27 = (int)fld_e23 - 12 * uArg3;
        *(this + 2) = sub_59EE30(v27, fld_e23, fld_e23);  // 三元组块搬移辅助
        sub_504450(pArg2, v27, Blockb);  // 调 搬移插入位后元素
        return sub_5043B0(pArg2, pArg2 + 12 * uArg3, v25);  // 返回 调 sub_5043B0 返回值
      }
      else  // 否则分支
      {
        sub_59EE30(pArg2, fld_e23, pArg2 + 12 * uArg3);  // 三元组块搬移辅助
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 12;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);  // 调 填充补足尾段
        fld_e26 = 12 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8〔nSkillRec8(推断)〕
        return sub_5043B0(pArg2, fld_e26 - 12 * uArg3, v25);  // 返回 调 sub_5043B0 返回值
      }
    }
    else  // 否则分支
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )
        v13 = (fld_e3 >> 1) + fld_e3;
      else  // 否则分支
        v13 = 0;
      if ( fld_e1 != 0 )  // 若 fld_e1 非 0
        fld_e27 = (*(this + 2) - fld_e1) / 12;  // this+8〔nSkillRec8(推断)〕
      else  // 否则分支
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);
      v15 = 12 * v13;
      Blocka = (char *)operator new(12 * v13);
      fld_e12 = *(this + 1);  // this+4〔宿主对象〕
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pArg2, Blocka);  // 三元组块搬移辅助
      sub_623C10(v28, uArg3, v25);  // 12 字节元素区间填充
      sub_59EE30(pArg2, *(this + 2), v28 + 12 * uArg3);  // 三元组块搬移辅助
      fld_e13 = *(this + 1);  // this+4〔宿主对象〕
      if ( fld_e13 != 0 )  // 若 fld_e13 非 0
        fld_e13 = (*(this + 2) - fld_e13) / 12;  // this+8〔nSkillRec8(推断)〕
      v17 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )  // this+4〔宿主对象〕
        j__free((void *)*(this + 1));  // this+4〔宿主对象〕
      *(this + 3) = (int)&Blocka[v15];  // this+12〔nSkillRec12(推断)〕
      *(this + 2) = (int)&Blocka[12 * v17];  // this+8〔nSkillRec8(推断)〕
      *(this + 1) = (int)Blocka;  // this+4〔宿主对象〕
      return (int)Blocka;
    }
  }
  return result;
}

