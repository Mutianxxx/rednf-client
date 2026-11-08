// ============================================================
// 【40JP逆向源代码工程】creature/spider_trap.cpp
// 模块: 怪物AI 0x5C —— 蜘蛛/机器人/树精/属性精灵/陷阱莲花/刺王/锤王/玛格纳/阿莫尔
// 来源: work/dump_monster.txt  区块: 0x5C0000-0x5D0000
// 层级: L2 转写层 + L1 精修（函数体保持 Hex-Rays 忠实输出，仅升级注释与分区）
// 函数数: 232
// ------------------------------------------------------------
// ★ 本文件已按《20_打击感与HitStop系统研究》定案升级注释（研究 20 §x 为引）：
//   · vmt200(=vt+512 字节槽) 命中处理器覆写：本文件【无】—— 0x5C 段全部虚表在 +512 槽
//     继承基类 0x4D71B0（纯 Python 直读 PE 全域扫描证实），行为差异全靠数据与技能函数；
//     0x5B4D90 一类的覆写仅存在于 0x59-0x5B 段（见各文件头）
//   · 0x5C92D0 调 sub_4E4430 = HP 受击处理器（研究 31 Boss 终局族）
//   · AI 状态：this+200 主状态 / vt+560 反应态（研究 15）；陷阱类（章鱼/莲花/草）以
//     this+204/+208 硬直字段作触发节拍
//   · 语音 TAG 组（R_SPIDER_*/WATERSOUL_*/LOTUS_*/R_ECHEVERRA_*/R_GIANT_*）经 sub_4015C0
//     写语音槽，vt+212(sub_499110) 播报（研究 28）；sub_431230=vector 打包 setState 参数
//   · 资源标注：sub_431860/431920=.ani 装载 / sub_4BA9E0=.equ 外观 / sub_47EF20=数据表读数 /
//     sub_4049C0=帧间插值 / sub_406D60=BGM 曲名槽 / sub_493D00=动画变速换锚
//   · 高达梗粒子实证：particle/Rx78_Boom.ptl（ROBOT_EX_01 爆点）与 particle/Ez8_Boom.ptl
//     （ROBOT_EX_02 爆点）+ Monster/Gunner/Ez8/Ez8_Num.img —— ZGM 机动怪三件套
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】蜘蛛·本体与蜘蛛王（Spider / SpiderBoss）（0x5C0220-0x5C1FC0）
// 证据：BORROW_UP/BORROW_DOWN 钻地 + Monster/Spider{,Boss}Ani/BurrowEnd.ani 出土、
//       SPIDER_ROLLING_LOOP 滚冲、R_SPIDER_ATK/DMG + SPIDER_DIE/R_SPIDER 语音（另 PSPIDER/KSPIDER
//       毒/黑蜘蛛变体）、Thread.ani 吐丝 + MissileGero{Center,Left,Right}.ptl 三向吐酸、
//       ThreadSpark.ani 蛛丝火花

// 钻地/出土 AI：BORROW_UP + BORROW_DOWN 播报 + SPIDER_ROLLING_LOOP（76L；
//   this+8616/8617/8637/8638/8652 相位）
// ------------------------------------------------------------
// 0x5C0220 sub_5C0220 —— 蜘蛛·钻地出土与滚动状态机（BORROW_UP/BORROW_DOWN）
// 大状态门控：vt+840==15 播 BORROW_UP 并 ·sub_460110(this,1)、==8 经 vt+216 切 9（特殊）。
// ArgList==15 走出土收尾：·sub_4926A0 帧游标复位 + vt+196 切帧 + ·sub_460110(this,2) +
//   this+8637/8638/8652 清零 + ·sub_698F90(this+8624,4000ms) 倒计时 + vt+876 双轴归零。
// 尾段转 ·sub_5BF7E0 事件提交；子状态 this+1757∈{0,1,2} 时播 SPIDER_ROLLING_LOOP(9) 滚冲，
//   大状态 14 转 ·sub_5BF9E0 滚动起步。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C0220(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 蜘蛛·钻地出土与滚动状态机（BORROW_UP/BORROW_DOWN）
{
  int v6; // eax
  int v7; // edx
  uint32_t *v8; // edx
  int v9; // eax

  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( v6 == 15 )
  {
    sub_460110(this, 1);  // 调 图标对象换槽（重写槽号后重挂）
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BORROW_UP", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
  }
  else if ( v6 == 8 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
  }
  if ( ArgList == 15 )
  {
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 12));  // this+6216 = 资源/帧游标表
    sub_460110(this, 2);  // 调 图标对象换槽（重写槽号后重挂）
    ++*(this + 2155);  // this+8620 = uAI8620
    *((uint8_t *)this + 8637) = 0;  // this+8637 普攻播报单次门
    *((uint8_t *)this + 8638) = 0;  // this+8638 【推断】子类扩展标志字节
    sub_698F90((int)(this + 2156), 4000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    v7 = *this;
    *((uint8_t *)this + 8652) = 0;  // this+8652 = 相位槽
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v7 + 212))(this, "BORROW_DOWN", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
      this,
      0,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
      this,
      1,
      0,
      0,
      0,
      0,
      0);
  }
  sub_5BF7E0((uint32_t **)this, ArgList, fArg3, nArg4, nArg5);  // 调 事件提交基函数（大状态 8/6 分支 + 随机速率微调）
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && (sub_41A5E0((unsigned int)(this + 1757)) == 0  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
     || sub_41A5E0((unsigned int)(this + 1757)) == 1  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
     || sub_41A5E0((unsigned int)(this + 1757)) == 2) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v8 = (uint32_t *)*this;
    *((uint8_t *)this + 8616) = 0;  // this+8616 = uAI8616
    *((uint8_t *)this + 8617) = 0;  // this+8617 【推断】钻地相位字节2
    LOBYTE(v9) = ((int (/*thiscall*/ *)(uint32_t *, const char *, int, uint32_t, uint32_t))v8[53])(  // 调 取 16 位值低 8 位
                   this,
                   "SPIDER_ROLLING_LOOP",  // 资源/动画 TAG SPIDER_ROLLING_LOOP
                   9,
                   0,
                   0);
  }
  else
  {
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    if ( v9 == 14 )
      LOBYTE(v9) = sub_5BF9E0(this);  // 调 蜘蛛·滚动起步（速率表提交 + 350ms 倒计时锁 this+8618）
  }
  return v9;
}



// 蜘蛛语音装载：R_SPIDER_ATK/DMG + SPIDER_DIE + R_SPIDER（this+8616..8620 相位）
// ------------------------------------------------------------
// 0x5C0390 sub_5C0390 —— 蜘蛛本体语音装载（R_SPIDER_ATK/DMG + SPIDER_DIE）
// 清 this+8616/8617/8618 与 this+8620 相位槽后，经 ·sub_4015C0 依次写四个语音 TAG
//   （ATK/DMG/DIE/登场），供 vt+212 播报（研究 28）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C0390(int this)  // 函数: 蜘蛛本体语音装载（R_SPIDER_ATK/DMG + SPIDER_DIE）
{
  *(uint8_t *)(this + 8616) = 0;  // this+8616 【推断】钻地相位字节1
  *(uint8_t *)(this + 8617) = 0;  // this+8617 【推断】钻地相位字节2
  *(uint8_t *)(this + 8618) = 0;  // this+8618 【推断】滚动/钻地相位字节3
  *(uint32_t *)(this + 8620) = 0;  // this+8620 相位双字节门
  sub_4015C0("R_SPIDER_ATK", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_SPIDER_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("SPIDER_DIE", 0xAu);  // 【std::string构造赋值】
  return sub_4015C0("R_SPIDER", 8u);  // 【std::string构造赋值】
}



// 毒蜘蛛语音：R_SPIDER_ATK/DMG + PSPIDER_DIE + R_PSPIDER
// ------------------------------------------------------------
// 0x5C0400 sub_5C0400 —— 毒蜘蛛（PSPIDER）出场参数与语音装配
// 变体装配：this+8604=30017（技能 id）、this+8620=6、this+8608=1，清 this+8616 后经 vt+384
//   出场参数面两次写入；再经 ·sub_4015C0 装 R_SPIDER_ATK/DMG、PSPIDER_DIE、R_PSPIDER。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C0400(uint8_t *this)  // 函数: 毒蜘蛛（PSPIDER）出场参数与语音装配
{
  int v2; // eax

  v2 = *(uint32_t *)this;
  *(this + 8616) = 0;  // this+8616 = uAI8616
  *((uint32_t *)this + 2151) = 30017;  // this+8604 = bAI8604
  (*(void (/*stdcall*/ **)(uint32_t))(v2 + 384))(0);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 1);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  *((uint32_t *)this + 2155) = 6;  // this+8620 = uAI8620
  *((uint32_t *)this + 2152) = 1;  // this+8608 = uAI8608
  sub_4015C0("R_SPIDER_ATK", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_SPIDER_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("PSPIDER_DIE", 0xBu);  // 【std::string构造赋值】
  return sub_4015C0("R_PSPIDER", 9u);  // 【std::string构造赋值】
}



// 黑蜘蛛语音：KSPIDER_ATK + R_KSPIDER_DMG/DIE/R_KSPIDER（this+8616..8764 相位）
// ------------------------------------------------------------
// 0x5C0490 sub_5C0490 —— 黑蜘蛛（KSPIDER）语音装载与大相位区清零
// 一次清 this+8616/8617/8632/8636/8640/8644/8652/8653/8764 九个相位与计时槽
//   （对应钻地、传送与滚动相位），再经 ·sub_4015C0 装 KSPIDER_ATK、R_KSPIDER_DMG/DIE/登场。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C0490(int this)  // 函数: 黑蜘蛛（KSPIDER）语音装载与大相位区清零
{
  *(uint8_t *)(this + 8616) = 0;  // this+8616 【推断】钻地相位字节1
  *(uint8_t *)(this + 8617) = 0;  // this+8617 【推断】钻地相位字节2
  *(uint32_t *)(this + 8640) = 0;  // this+8640 【推断】出土相位槽
  *(uint32_t *)(this + 8636) = 0;  // this+8636 【推断】传送/钻地相位槽
  *(uint8_t *)(this + 8652) = 0;  // this+8652 【推断】相位门字节
  *(uint8_t *)(this + 8653) = 0;  // this+8653 【推断】相位门字节
  *(uint32_t *)(this + 8632) = 0;  // this+8632 【推断】子类 AI 资源/计数槽
  *(uint32_t *)(this + 8644) = 0;  // this+8644 【推断】相位计数槽
  *(uint32_t *)(this + 8764) = 0;  // this+8764 【推断】滚动/传送相位槽
  sub_4015C0("KSPIDER_ATK", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("R_KSPIDER_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("KSPIDER_DIE", 0xBu);  // 【std::string构造赋值】
  return sub_4015C0("R_KSPIDER", 9u);  // 【std::string构造赋值】
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5C0520 sub_5C0520 —— 蜘蛛·273 标记目标架招反击门
// 存活(vt+308) + 目标须 vt+40 标记 273 且 vt+948 通过 + 自身 this+616 非 14【推断：架招态】时：
//   ·sub_431230 打包目标 vt+48/vt+52 两字段作参数，经 vt+560 setState(14/架招)，
//   随后清参数缓冲；尾调 ·sub_4DB480 反击判定（传入 nArg3/nArg4）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C0520(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 蜘蛛·273 标记目标架招反击门
{
  char v5; // al
  int pObj; // esi
  int v7; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v10; // [esp+20h] [ebp-4h]

  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  pObj = nArg2;
  if ( v5 != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 273) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 948))(pObj) != 0  // 调用虚函数（虚表槽 +948）
    && *(this + 154) != 14 )  // this+154 施放标志 B
  {
    memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
    v7 = *(uint32_t *)pObj;
    v10 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(v7 + 48))(pObj);  // 调用虚函数（虚表槽 +48）
    sub_431230((int)pBuf, &nArg2);  // 调 uint32 vector push_back
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调用虚函数（虚表槽 +52）
    sub_431230((int)pBuf, &nArg2);  // 调 uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    v10 = -1;
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
  return sub_4DB480(pObj, nArg3, nArg4);  // 调 ★ 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 参数打包 AI（89L sub_431230）
// ------------------------------------------------------------
// 0x5C0600 sub_5C0600 —— 蜘蛛·茧位载人对象（this+8608）解绑与收尾
// this[2152]（位 8608 挂载对象）非空时：vt+604 置忙、vt+612 清位，再 vt+136 坐标校验通过
//   则 vt+112 直接落座，否则经 vt+124 换算 300 档位 + vt+120 折算后二次校验落座。
// 落座位下 vt+308 时走 setState(4) 参数包（4,0,1,200,200）+ vt+564 立即提交。
// 末尾 vt+848 关闭挂载并清 this[2152]。
// ------------------------------------------------------------
void /*usercall*/ sub_5C0600(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 函数: 蜘蛛·茧位载人对象（this+8608）解绑与收尾
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

  pObj3 = pDwArg1[2152];
  if ( pObj3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2152] + 612))(pDwArg1[2152], 0, 0);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2152] + 136))(  // 调用虚函数（虚表槽 +136）
           pDwArg1[2152],
           pDwArg1[2156],
           pDwArg1[2157],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2152] + 112))(pDwArg1[2152], pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    }
    else
    {
      pObj = pDwArg1[2152];
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);  // 调用虚函数（虚表槽 +124）
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2156, pDwArg1 + 2157, v7);  // 调用虚函数（虚表槽 +140）【推断: ★ 螺旋式寻找空位（同心方环，从 (a4,a5) 起向外扫）】
      pObj2 = pDwArg1[2152];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      }
      else
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2158]);  // 调用虚函数（虚表槽 +124）
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2152], v12);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 308))(pDwArg1[2152]) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    {
      Block = nullptr;
      v15 = 0;
      v16 = 0;
      v18 = 0;
      pObj4 = 4;
      sub_431230((int)v13, &pObj4);  // 调 uint32 vector push_back
      pObj4 = 0;
      sub_431230((int)v13, &pObj4);  // 调 uint32 vector push_back
      pObj4 = 1;
      sub_431230((int)v13, &pObj4);  // 调 uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // 调 uint32 vector push_back
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);  // 调 uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2152] + 560))(pDwArg1[2152], 4, v13, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 564))(pDwArg1[2152]);  // 调用虚函数（虚表槽 +564）【推断: ★ 位移同步包 vt+234（会话 3 定案：UDP type=…】
      v18 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
      Block = nullptr;
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2152] + 848))(pDwArg1[2152], 0);  // 调用虚函数（虚表槽 +848）【推断: [RTTI: IRDActiveObject__vmt350 ·…】
    pDwArg1[2152] = 0;
  }
}



// 参数打包+时钟门 AI（92L；sub_431230+sub_699000）
// ------------------------------------------------------------
// 0x5C0800 sub_5C0800 —— 蜘蛛·待机行为决策（vt+840==0）与随机走位
// 门控：vt+308 存活且 vt+840 大状态 0（待机）。vt+184/vt+188 取向锁定后按 this[1787]（行为字）
//   分支：行为 4 用 ·sub_4DA6B0 滚动格判定，行为 5/9 → ·sub_4DBDB0 空间栅格重叠检测定走位格；
//   命中走位格时用 ·sub_699000 + 1000ms，否则 +300ms 设 this[1818] 走位截止时刻。
// 再按 this[2092]+this[1787] 的 int16 高低半字作概率阈值（命中则强制目标格 4），
//   vt+896 写 (走位格A, 走位格B)，最后经 ·sub_431230 + ·sub_58E710 组装 setState(6/待机) 参数。
// ------------------------------------------------------------
void /*usercall*/ sub_5C0800(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 函数: 蜘蛛·待机行为决策（vt+840==0）与随机走位
{
  int v3; // eax
  int nRand; // eax
  int v5; // eax
  int v6; // edi
  int v7; // edi
  int v8; // eax
  uint8_t v9[4]; // [esp+4h] [ebp-28h] BYREF
  void *Block; // [esp+8h] [ebp-24h]
  int v11; // [esp+Ch] [ebp-20h]
  int v12; // [esp+10h] [ebp-1Ch]
  int v13; // [esp+14h] [ebp-18h] BYREF
  int nRand2; // [esp+18h] [ebp-14h] BYREF
  uint32_t v15[4]; // [esp+1Ch] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 184))(pArg1, nArg2);  // 调用虚函数（虚表槽 +184）【推断: 动画对象 z 倾斜转状态码】
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 188))(pArg1);  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
    v3 = pArg1[1787] - 4;
    v15[0] = 4;
    nRand2 = 4;
    switch ( v3 )  // 按 v3 分派
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        if ( rand() % 100 >= 80 || (uint8_t)sub_4DA6B0(v15) != 0 )  // 调 以 16 位种子状态递推并返回 15 位结果
          goto LABEL_7;
        goto LABEL_6;
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
LABEL_6:
        sub_4DBDB0(v15, &nRand2);  // 调 ★ 空间栅格重叠检测（碰撞/挤压分离轴；研究第 24/25 轮族）
        goto LABEL_7;
      case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
        if ( rand() % 100 >= 40 )  // 调 以 16 位种子状态递推并返回 15 位结果
        {
LABEL_7:
          nRand = nRand2;
        }
        else
        {
          if ( (uint8_t)sub_4DA6B0(v15) == 0 )  // 调 滚动格判定
            v15[0] = rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
          nRand = rand() % 2 + 2;  // 调 以 16 位种子状态递推并返回 15 位结果
          nRand2 = nRand;
        }
        if ( v15[0] == 4 && nRand == 4 )
          goto LABEL_10;
        v5 = sub_699000((int)(pArg1 + 9)) + 1000;  // 【clock_now(clk)】
        break;
      default:
LABEL_10:
        v5 = sub_699000((int)(pArg1 + 9)) + 300;  // 【clock_now(clk)】
        break;
    }
    v6 = pArg1[1787];
    pArg1[1818] = v5;
    if ( rand() % 100 < SLOWORD(pArg1[v6 + 2092]) )  // 调 以 16 位种子状态递推并返回 15 位结果
      v15[0] = 4;
    v7 = pArg1[1787];
    if ( rand() % 100 < SHIWORD(pArg1[v7 + 2092]) )  // 调 以 16 位种子状态递推并返回 15 位结果
      nRand2 = 4;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 896))(pArg1, v15[0]);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
    sub_5FDFE0(pArg1[1932]);  // 调 粒子与 vt+1080 收手
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1080))(pArg1);  // 调用虚函数（虚表槽 +1080）
    if ( v15[0] != 4 || nRand2 != 4 )
    {
      Block = nullptr;
      v11 = 0;
      v12 = 0;
      v15[3] = 0;
      v13 = 0;
      sub_431230((int)v9, &v13);  // 调 uint32 vector push_back
      v13 = 0;
      sub_431230((int)v9, &v13);  // 调 uint32 vector push_back
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 672))(pArg1, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      v13 = sub_58E710(v8);  // 调 食尸鬼族通用：41A5E0 粒子挂载（第二变体）
      sub_431230((int)v9, &v13);  // 调 uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 6, v9, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
    }
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C0A50 sub_5C0A50 —— 蜘蛛·滚动/茧相位转发（收录 this+6556 前状态）
// 先取 this[1639]（主状态镜像 2）留档，vt+184/vt+188 取向锁定；前态 14(架招) 时
//   ·sub_5C0600 解绑茧位对象；本帧入参 ArgList==14 → ·sub_5BF5F0 蓄力起手（273 目标捕获），
//   ==15 → ·sub_5BEB90 茧位校准，最后 ·sub_4E33D0 状态收尾。
// ------------------------------------------------------------
int /*userpurge*/ sub_5C0A50@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, int nArg4, int nArg5, int nArg6)  // 实现：蜘蛛·滚动/茧相位转发（收录 this+6556 前状态）
{
  int v7; // edi

  v7 = pDwArg1[1639];
  (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 184))(pDwArg1);  // 调用虚函数（虚表槽 +184）【推断: 动画对象 z 倾斜转状态码】
  (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 188))(pDwArg1);  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
  if ( v7 == 14 )
    sub_5C0600(pDwArg1, nArg2);  // 调 蜘蛛·茧位载人对象（this+8608）解绑与收尾
  if ( ArgList == 14 )
  {
    sub_5BF5F0(pDwArg1, nArg4);  // 调 蜘蛛·HOLD 蓄力起手（273 标记目标捕获 + 段时长插值）
  }
  else if ( ArgList == 15 )
  {
    sub_5BEB90(pDwArg1);  // 调 蜘蛛·茧位校准（不可站位时贴至猎物 Z+40 并重设速率轴）
  }
  return sub_4E33D0(ArgList, *(float *)&nArg4, nArg5, nArg6);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C0AC0 sub_5C0AC0 —— 蜘蛛·消亡/脱离时茧位对象清理（观察者回调）
// pDwArg3 命中 this[2152]（茧位挂载）时：前态 vt+840==14 则 ·sub_5C0600 解绑；命中自身
//   且仍持挂载时同样解绑，两路都清 this[2152]，最后统一 ·sub_4D9170 消亡通知。
// ------------------------------------------------------------
int /*userpurge*/ sub_5C0AC0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)  // 实现：蜘蛛·消亡/脱离时茧位对象清理（观察者回调）
{
  if ( pDwArg3 == (int *)pDwArg1[2152] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      sub_5C0600(pDwArg1, nArg2);  // 调 蜘蛛·茧位载人对象（this+8608）解绑与收尾
    pDwArg1[2152] = 0;
  }
  if ( pDwArg3 == pDwArg1 && pDwArg1[2152] != 0 )
  {
    sub_5C0600(pDwArg1, nArg2);  // 调 蜘蛛·茧位载人对象（this+8608）解绑与收尾
    pDwArg1[2152] = 0;
  }
  return sub_4D9170(pDwArg3);  // 调 消亡通知
}



// 蜘蛛·跳扑/钻地循环（285L）：大状态8 攻击——8616 空中相位；子状态0/1 起跳向目标
//   (vt+876 水平=目标X差/垂直=目标Y差、滞空 60~119 帧)，子状态2 用 dword_72FD68 查表
//   平移；落地段(+192==4) vt+896(4,4) 硬直，子状态2 直接 setState(14)；高度过
//   dword_72FD78/80 查表阈值切 1554+4/+8 起跳/落地动画；大状态14 且 8618 时调
//   0x5BF4E0；大状态15(钻地)——到 this[2162] 唤醒时刻播 BurrowEnd.ani 出土
//   (vt+876 弹起 30/30)、2 秒后按 vt+740×0.3 生成回血文本(3000ms)；空闲且血量
//   ≤vt+740×0.5 时 setState(15) 主动钻地
// ------------------------------------------------------------
// 0x5C0B20 sub_5C0B20 —— 蜘蛛·跳扑与钻地循环（大状态 8/14/15 三态主驱动）
// 前置 ·sub_5BECF0 吐丝触发门；this+8617 落地标志置 1 即 vt+216 切 9（特殊/潜入）。
// 大状态 8 且子状态 vt+908∈{0,1}：vt+876 双轴写目标 X/Y 差、滞空 60~119 帧；==2 用
//   dword_72FD68/70 查表平移；落地 (this[28]+192==4) 时 vt+896(4,4) 硬直。
// 高度过 dword_72FD78/80 阈值切 1554+4/+8 起跳/落地动画；大状态 14 且 8618 转 ·sub_5BF4E0；
//   15 到 this[2162] 唤醒时刻播 BurrowEnd.ani + 2s 后 vt+740×0.3 回血文本；血量≤半血主动钻地(15)。
// ------------------------------------------------------------
void /*thiscall*/ sub_5C0B20(int *this)  // 函数: 蜘蛛·跳扑与钻地循环（大状态 8/14/15 三态主驱动）
{
  int nSubType1; // ebx
  int nSubType2; // eax
  int nSubType3; // eax
  int nCamAmp; // edi
  int nAirFrames; // edx
  int pTarget; // ecx
  int nTgtX; // ebx
  unsigned int nAbsDx; // eax
  int pTarget2; // ecx
  int nTgtYRaw; // ebx
  int64_t nDy64; // rax
  int nDyI; // ebx
  int nAbsDy; // ebx
  int pTarget3; // ecx
  int nSparkId; // ebx
  int nTgtY2; // ebx
  int pVt; // edi
  int hAniKind; // eax
  char bAirFlag; // cl
  int pSelf; // edx
  int nSubType4; // edi
  uint32_t *pResSlot4; // edi
  int nSubType5; // edi
  uint32_t *pResSlot8; // edi
  int nWakeTime; // edi
  int nResGate; // eax
  int hAniBurrow; // edi
  int *pFxBurrow; // edi
  int pFxBurrowVt; // ebx
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  int pFxBurrowVt2; // ebx
  int nFaceDir; // eax
  int nSubType6; // eax
  int pVt2; // edi
  int hAniKind4; // eax
  uint8_t *pTextObj; // eax
  uint8_t *pTextObj2; // eax
  int fHealF; // [esp+44h] [ebp-34h]
  int nAniSlot; // [esp+50h] [ebp-28h]
  int nAirFramesSaved; // [esp+60h] [ebp-18h]
  int nHealVal; // [esp+60h] [ebp-18h]
  double fHalfHp; // [esp+64h] [ebp-14h]
  void *nAbsDxSlot; // [esp+68h] [ebp-10h]

  sub_5BECF0();  // 调 蜘蛛·吐丝触发门（攻击帧段匹配 + 相位锁）
  if ( *((uint8_t *)this + 8617) == 1 )  // this+8617 【推断】钻地相位字节2
    (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && ((*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 0  // 调用虚函数（虚表槽 +908）
     || (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 1  // 调用虚函数（虚表槽 +908）
     || (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 2) )  // 调用虚函数（虚表槽 +908）
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      goto LABEL_29;
    if ( *(int *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) >= 1 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    {
      if ( *((uint8_t *)this + 8616) != 0 )  // this+8616 = uAI8616
      {
LABEL_25:
        if ( *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8617) == 0 )  // this+112 = pHostComp
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
            this,
            1,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 2 )  // 调用虚函数（虚表槽 +908）
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        }
        goto LABEL_29;
      }
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 0  // 调用虚函数（虚表槽 +908）
        || (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 1 )  // 调用虚函数（虚表槽 +908）
      {
        nCamAmp = (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) != 1 ? 320 : 160;  // 调用虚函数（虚表槽 +908）
        nAirFrames = rand() % 60 + 60;  // 调 以 16 位种子状态递推并返回 15 位结果
        pTarget = *(this + 1813);  // this+7252 = pTarget7252
        nAirFramesSaved = nAirFrames;
        if ( pTarget != 0 )
        {
          nTgtX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget + 120))(pTarget);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          nAbsDx = abs32(nTgtX - (*(int (/*thiscall*/ **)(int *))(*this + 120))(this));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          nAirFrames = nAirFramesSaved;
        }
        else
        {
          nAbsDx = 0;
        }
        pTarget2 = *(this + 1813);  // this+7252 = pTarget7252
        nAbsDxSlot = (void *)nAbsDx;
        if ( pTarget2 != 0 )
        {
          nTgtYRaw = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 124))(pTarget2);  // 调用虚函数（虚表槽 +124）
          nDy64 = nTgtYRaw - (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
          nDyI = nDy64;
          nAbsDx = (unsigned int)nAbsDxSlot;
          nAbsDy = (HIDWORD(nDy64) ^ nDyI) - HIDWORD(nDy64);  // 调 取 64 位值高 32 位
        }
        else
        {
          nAbsDy = nAirFrames;
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          nAbsDx,
          nAbsDx,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, nAbsDy, nAbsDy, 0, 0, 0);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
        pTarget3 = *(this + 1813);  // this+7252 = pTarget7252
        nSparkId = 2;
        if ( pTarget3 != 0 )
        {
          nTgtY2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget3 + 124))(pTarget3);  // 调用虚函数（虚表槽 +124）
          nSparkId = (nTgtY2 > (*(int (/*thiscall*/ **)(int *))(*this + 124))(this)) + 2;  // 调用虚函数（虚表槽 +124）
        }
        sub_4A0550(nCamAmp);  // 调 镜头幅度
        nAniSlot = nSparkId;
      }
      else
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) != 2 )  // 调用虚函数（虚表槽 +908）
          goto LABEL_24;
        nSubType1 = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        nSubType2 = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          dword_72FD68[nSubType2],
          dword_72FD68[nSubType1],
          0,
          0,
          0);
        nSubType3 = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        sub_4A0550(dword_72FD70[nSubType3]);  // 调 镜头幅度
        nAniSlot = 4;
      }
      pVt = *this;
      hAniKind = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, nAniSlot);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      (*(void (/*thiscall*/ **)(int *, int))(pVt + 896))(this, hAniKind);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
    }
LABEL_24:
    if ( *((uint8_t *)this + 8616) != 0 )  // this+8616 = uAI8616
      goto LABEL_25;
LABEL_29:
    bAirFlag = *((uint8_t *)this + 8616);  // this+8616 = uAI8616
    if ( bAirFlag != 0 && *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8617) == 0 )  // this+112 = pHostComp
      *((uint8_t *)this + 8617) = 1;  // this+8617 【推断】钻地相位字节2
    pSelf = *(this + 28);  // this+112 = pHostComp
    if ( *(float *)(pSelf + 24) > 0.0 && bAirFlag == 0 )
      *((uint8_t *)this + 8616) = 1;  // this+8616 = uAI8616
    if ( *((uint8_t *)this + 8616) != 0 )  // this+8616 = uAI8616
    {
      if ( *(float *)(pSelf + 24) > 0.0 )
      {
        nSubType4 = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) > dword_72FD78[nSubType4] )  // 调用虚函数（虚表槽 +128）
        {
          pResSlot4 = (uint32_t *)(*(this + 1554) + 4);  // this+6216 = 资源/帧游标表
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != *pResSlot4 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));  // 调用虚函数（虚表槽 +344）
            sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // this+6216 = 资源/帧游标表
          }
        }
      }
      if ( *((uint8_t *)this + 8616) != 0 && *(float *)(*(this + 28) + 24) < 0.0 )  // this+8616 = uAI8616
      {
        nSubType5 = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) < dword_72FD80[nSubType5] )  // 调用虚函数（虚表槽 +128）
        {
          pResSlot8 = (uint32_t *)(*(this + 1554) + 8);  // this+6216 = 资源/帧游标表
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != *pResSlot8 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          {
            sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 8));  // this+6216 = 资源/帧游标表
          }
        }
      }
    }
    return;
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 14 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( *((uint8_t *)this + 8618) != 0 )  // this+8618 【推断】滚动/钻地相位字节3
      sub_5BF4E0(this);  // 调 定时解锁门（clock_now 到期 → this+8618=0 + setState 0）
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 15 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    {
      nWakeTime = *(this + 2162);  // this+8648 = 相位/缓存槽
      if ( sub_699000((int)(this + 2156)) >= nWakeTime )  // 【clock_now(clk)】
      {
        nResGate = sub_42FCB0(228);  // 调 CRT 一次性初始化
        hAniBurrow = 0;
        if ( nResGate != 0 )
          hAniBurrow = sub_431860(nResGate, "Monster/Spider/SpiderAni/BurrowEnd.ani", 1);  // 调 动画件构造（资源 id 版）
        if ( hAniBurrow != 0 )
        {
          if ( sub_44B6C0(284) != 0 )  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
            pFxBurrow = (int *)sub_44E1F0(hAniBurrow, 1);  // 调 CNRDPooledObject 构造（虚表覆盖壳）
          else
            pFxBurrow = nullptr;
          sub_45FE80(*(this + 29), (int)pFxBurrow, 2, 0, (int)pFxBurrow, (int)this, 0);  // 调 对象注册
          pFxBurrowVt = *pFxBurrow;
          nZ = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
          nY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ);  // 调用虚函数（虚表槽 +124）
          nX = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nY);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          (*(void (/*thiscall*/ **)(int *, int))(pFxBurrowVt + 112))(pFxBurrow, nX);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
          pFxBurrowVt2 = *pFxBurrow;
          nFaceDir = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          (*(void (/*thiscall*/ **)(int *, int))(pFxBurrowVt2 + 144))(pFxBurrow, nFaceDir);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          30,
          30,
          0,
          0,
          0);
        nSubType6 = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        sub_4A0550(dword_72FD70[nSubType6]);  // 调 镜头幅度
        pVt2 = *this;
        hAniKind4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        (*(void (/*thiscall*/ **)(int *, int))(pVt2 + 896))(this, hAniKind4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
      }
      if ( *((uint8_t *)this + 8652) == 0 && sub_699000((int)(this + 2156)) > 2000 )  // 【clock_now(clk)】
      {
        nHealVal = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(*this + 740))(this) * 0.30000001);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
        pTextObj = operator new(0x80u);  // operator new 分配 128 字节
        if ( pTextObj != nullptr )  // 若 pTextObj 有效（非空）
        {
          *(float *)&fHealF = (float)nHealVal;
          pTextObj2 = sub_4D6810(pTextObj, fHealF, 3000, 1, 1);  // 调 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
        }
        else
        {
          pTextObj2 = nullptr;
        }
        (*(void (/*thiscall*/ **)(uint8_t *, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pTextObj2 + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
          pTextObj2,
          this,
          this,
          0,
          0,
          0,
          -1);
        *((uint8_t *)this + 8652) = 1;  // this+8652 = 相位槽
      }
    }
  }
  else if ( *(this + 2155) == 0 )  // this+8620 = uAI8620
  {
    fHalfHp = (double)(*(int (/*thiscall*/ **)(int *))(*this + 740))(this) * 0.5;  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    if ( (double)(*(int (/*thiscall*/ **)(int *))(*this + 736))(this) <= fHalfHp )  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 15, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
  }
}


// 吐丝/吐酸：Thread.ani 蛛丝 + PassiveObject/Common/Particle/MissileGero{Center,Left,
//   Right}.ptl 三向喷吐（32L）
// ------------------------------------------------------------
// 0x5C11B0 sub_5C11B0 —— 蜘蛛王·三向吐酸资源装载（吐丝序列 30100 前置）
// 经 dword_8F84E4 资源表 vt+4 依名取句柄写入 this+8620/8624/8628：
//   PassiveObject/Common/Particle/MissileGero{Center,Left,Right}.ptl 三向酸液；
// 再循环 3 次把 Monster/Spider/SpiderBossAni/Thread.ani 载入 this+8752 起的三个句柄槽。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C11B0(uint32_t *this)  // 函数: 蜘蛛王·三向吐酸资源装载（吐丝序列 30100 前置）
{
  uint32_t *pThis_88C; // esi
  int i; // edi
  int result; // eax

  *(this + 2155) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // this+8620 = uAI8620
                     dword_8F84E4,  // 全局 对象工厂/生成管理器
                     "PassiveObject/Common/Particle/MissileGeroCenter.ptl");  // 资源路径 PassiveObject/Common/Particle/MissileGeroCenter.ptl
  *(this + 2156) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // this+8624 = uAI8624
                     dword_8F84E4,  // 全局 对象工厂/生成管理器
                     "PassiveObject/Common/Particle/MissileGeroLeft.ptl");  // 资源路径 PassiveObject/Common/Particle/MissileGeroLeft.ptl
  *(this + 2157) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // this+8628 = 指挥计时戳
                     dword_8F84E4,  // 全局 对象工厂/生成管理器
                     "PassiveObject/Common/Particle/MissileGeroRight.ptl");  // 资源路径 PassiveObject/Common/Particle/MissileGeroRight.ptl
  pThis_88C = this + 2188;
  for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
  {
    if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
      result = sub_431860((char)"Monster/Spider/SpiderBossAni/Thread.ani", 1);  // 调 动画件构造（资源 id 版）
    else
      result = 0;
    *pThis_88C++ = result;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C1270 sub_5C1270 —— 蜘蛛王·Thread.ani 三句柄槽释放（与 ·0x5C11B0 成对）
// 遍历 this+8752 起三槽：非空则 ·sub_42AF90(vt+? 释放) + ·sub_657740(ptr,228) 回收，
//   槽位清零；供吐酸资源重载前调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C1270(void ***this)  // 函数: 蜘蛛王·Thread.ani 三句柄槽释放（与 ·0x5C11B0 成对）
{
  void ***pThis_88C; // esi
  int i; // ebx
  void **v3; // edi
  int result; // eax

  pThis_88C = this + 2188;
  for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
  {
    v3 = *pThis_88C;
    if ( *pThis_88C != nullptr )
    {
      sub_42AF90(*pThis_88C);  // 调 帧对象析构（帧数组 + 元素数组）
      result = sub_657740(v3, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_88C++ = nullptr;
  }
  return result;
}



// 蜘蛛王出土（130L）：Monster/Spider/SpiderBossAni/BurrowEnd.ani（sub_431860+sub_699000）
// ------------------------------------------------------------
// 0x5C12B0 sub_5C12B0 —— 蜘蛛王·钻地传送出土四相机（this+8640 相位 1..3）
// 启动门 this[2160]==0 且高度(vt+128)<600：置 1、·sub_698F90(+8688,2000ms)、vt+36 备份到
//   this[2186] 后 ·sub_495890 抹除（潜地隐藏）；相位 1 到 this[2178] 截止时以目标 pArg1[1813]
//   坐标 vt+108 落点 + setState(17/绑定) + 音效 48012；相位 2 落地(vt+128≤0)：镜头 2/450、
//   帧对齐、vt+876(200,200) 击退、镜头 150、BurrowEnd.ani 出土 + 30201 音效；相位 3 动作尾后
//   setState(0) 置 4 收束。
// ------------------------------------------------------------
int /*usercall*/ sub_5C12B0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 实现：蜘蛛王·钻地传送出土四相机（this+8640 相位 1..3）
{
  int pSelf; // ecx
  int result; // eax
  int nWakeDeadline; // edi
  int nEmergeX; // edi
  int nY; // eax
  int pTarget; // ecx
  int nEmergeY; // ebx
  int nZ; // eax
  int nFaceDir; // eax
  int pMount; // eax
  int pCurAct; // edi
  int nAnimId; // eax
  int hAniBurrow; // edi
  int *pFxBurrow; // edi
  int pFxBurrowVt; // ebx
  int nZ2; // eax
  int nY2; // eax
  int nX2; // eax
  int pFxBurrowVt2; // ebx
  int nFaceDir2; // eax
  int nX3; // eax
  int nY3; // [esp-1Ch] [ebp-34h]
  int nZ3; // [esp-14h] [ebp-2Ch]
  int pVt; // [esp+8h] [ebp-10h]

  if ( pArg1[2160] != 0 || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1) < 600 )  // 调用虚函数（虚表槽 +128）
  {
    result = pArg1[2160];
    switch ( result )  // 按 result 分派
    {
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        nWakeDeadline = pArg1[2178];
        result = sub_699000((int)(pArg1 + 2172));  // 【clock_now(clk)】
        if ( result >= nWakeDeadline )
        {
          nEmergeX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg2);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          nY = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);  // 调用虚函数（虚表槽 +124）
          pTarget = pArg1[1813];
          nEmergeY = nY;
          if ( pTarget != 0 )
          {
            nEmergeX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget + 120))(pTarget);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
            nEmergeY = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813]);  // 调用虚函数（虚表槽 +124）
            pVt = *pArg1;
            nZ = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);  // 调用虚函数（虚表槽 +128）
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(pVt + 108))(pArg1, nEmergeX, nEmergeY, nZ);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
          }
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 17, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
          nFaceDir = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          return sub_4E4A50(pArg1, 48012, 2, nEmergeX, nEmergeY, 0, nFaceDir, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
        }
        break;
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);  // 调用虚函数（虚表槽 +128）
        if ( result <= 0 )
        {
          pMount = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1);  // 调用虚函数（虚表槽 +80）
          sub_424120(*(uint32_t **)(pMount + 132), 2, 450);  // 调 屏幕震动启动
          pCurAct = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          nAnimId = sub_491C70(pCurAct, 1);  // 调 ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
          sub_493A60(pCurAct, nAnimId);  // 调 时间推进包装（累计 +32；+212 同步源优先）
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
            pArg1,
            0,
            200,
            200,
            0,
            0,
            0);
          sub_4A0550(150);  // 调 镜头幅度
          if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
            hAniBurrow = sub_431860((char)"Monster/Spider/SpiderBossAni/BurrowEnd.ani", 1);  // 调 动画件构造（资源 id 版）
          else
            hAniBurrow = 0;
          if ( hAniBurrow != 0 )
          {
            if ( sub_44B6C0(284) != 0 )  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
              pFxBurrow = (int *)sub_44E1F0(hAniBurrow, 1);  // 调 CNRDPooledObject 构造（虚表覆盖壳）
            else
              pFxBurrow = nullptr;
            sub_45FE80(pArg1[29], (int)pFxBurrow, 2, 0, (int)pFxBurrow, (int)pArg1, 0);  // 调 对象注册
            pFxBurrowVt = *pFxBurrow;
            nZ2 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);  // 调用虚函数（虚表槽 +128）
            nY2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, nZ2);  // 调用虚函数（虚表槽 +124）
            nX2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nY2);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
            (*(void (/*thiscall*/ **)(int *, int))(pFxBurrowVt + 112))(pFxBurrow, nX2);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
            pFxBurrowVt2 = *pFxBurrow;
            nFaceDir2 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            (*(void (/*thiscall*/ **)(int *, int))(pFxBurrowVt2 + 144))(pFxBurrow, nFaceDir2);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
          }
          nZ3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          nY3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);  // 调用虚函数（虚表槽 +124）
          nX3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          result = sub_4E4A50(pArg1, 30201, 0, nX3, nY3, 0, nZ3, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
          pArg1[2160] = 3;
        }
        break;
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        if ( *(uint8_t *)(result + 170) != 0 )
        {
          result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
          pArg1[2160] = 4;
        }
        break;
      default:
        break;
    }
  }
  else
  {
    *((uint8_t *)pArg1 + 8701) = 0;
    *((uint8_t *)pArg1 + 8702) = 0;
    sub_698F90((int)(pArg1 + 2172), 2000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    pSelf = pArg1[28];
    pArg1[2160] = 1;
    pArg1[2186] = *(uint32_t *)(pSelf + 36);
    sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
    result = pArg1[28];
    *(uint32_t *)(result + 36) = 0;
  }
  return result;
}


// 蜘蛛王出土 2（83L；this+200 相位）
// ------------------------------------------------------------
// 0x5C15A0 sub_5C15A0 —— 蜘蛛王·出土收束（this+8660 时钟门，大状态 16 尾段）
// this+8684 截止时刻到点后：播 Monster/Spider/SpiderBossAni/BurrowEnd.ani（·sub_44E0D0 挂载 +
//   CNRDPooledObject 池化 + ·sub_45FE80 挂到宿主 this[29]、按 vt+120/124/128 落座与 vt+152 朝向），
//   setState(16) + vt+876 双轴归零 + 镜头 700 + vt+152→vt+896 动画切换；
// 末尾 this[1554]+12 帧槽与当前动画不同且高度≤0 时 ·sub_4926A0 + vt+196 回切。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C15A0(int *this)  // 函数: 蜘蛛王·出土收束（this+8660 时钟门，大状态 16 尾段）
{
  int pThis_875; // ecx
  int nWakeDeadline; // edi
  int hAniBurrow; // ebx
  char *pPool; // eax
  char *pFxBurrow; // edi
  int pFxBurrowVt; // ebx
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  int pFxBurrowVt2; // ebx
  int nFaceDir; // eax
  int pVt; // edi
  int hAniKind4; // eax
  uint32_t *pResSlot12; // edi
  int result; // eax

  pThis_875 = (int)(this + 2165);  // this+8660 = uEvt8660
  nWakeDeadline = *(uint32_t *)(pThis_875 + 24);  // this+24 页数上限
  if ( sub_699000(pThis_875) >= nWakeDeadline )  // 【clock_now(clk)】
  {
    if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
      hAniBurrow = sub_431860((char)"Monster/Spider/SpiderBossAni/BurrowEnd.ani", 1);  // 调 动画件构造（资源 id 版）
    else
      hAniBurrow = 0;
    if ( hAniBurrow != 0 )
    {
      pPool = (char *)sub_44B6C0(284);  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
      pFxBurrow = pPool;
      if ( pPool != nullptr )  // 若 pPool 有效（非空）
      {
        sub_44E0D0(pPool, hAniBurrow, 1);  // 调 CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)pFxBurrow = &CNRDPooledObject::`vftable';  // vftable 复位
      }
      else
      {
        pFxBurrow = nullptr;
      }
      sub_45FE80(*(this + 29), (int)pFxBurrow, 2, 0, (int)pFxBurrow, (int)this, 0);  // 调 对象注册
      pFxBurrowVt = *(uint32_t *)pFxBurrow;
      nZ = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
      nY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ);  // 调用虚函数（虚表槽 +124）
      nX = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nY);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      (*(void (/*thiscall*/ **)(char *, int))(pFxBurrowVt + 112))(pFxBurrow, nX);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      pFxBurrowVt2 = *(uint32_t *)pFxBurrow;
      nFaceDir = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      (*(void (/*thiscall*/ **)(char *, int))(pFxBurrowVt2 + 144))(pFxBurrow, nFaceDir);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
    }
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 16, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
      this,
      0,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
    sub_4A0550(700);  // 调 镜头幅度
    pVt = *this;
    hAniKind4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(int *, int))(pVt + 896))(this, hAniKind4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
  }
  pResSlot12 = (uint32_t *)(*(this + 1554) + 12);  // this+6216 = 资源/帧游标表
  result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  if ( result != *pResSlot12 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
    if ( result <= 0 )
    {
      sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 12));  // this+6216 = 资源/帧游标表
    }
  }
  return result;
}



// 蜘蛛王·钻地传送追击（231L；相位 this+8636=1..6）：相位1 高空(Z≥600)启动——
//   8688 时钟 30s、传送次数 8632=sub_5BF430（全局 dword_9A05D4>2 时归零）、8716 时钟 1s；
//   相位2 每 1s 随机抽一名玩家(sub_5AE3C0)按 vt+140 落点检查后 vt+592(420) 传袭+音效 48012，
//   次数耗尽进相位3(3s)；相位3 到 8740 截止时刻从目标(this+7252)处出土、音效 48012、
//   setState(19)；相位4 Z≤0 落地——vt+876(200,200) 击退、镜头 150、播 BurrowEnd.ani；
//   相位5 动作尾(+170)后 setState(0) 进相位6
// ------------------------------------------------------------
// 0x5C1750 sub_5C1750 —— 蜘蛛王·钻地传送追击相位机（this+8636 相位 1..6）
// 相位 1 高空(≥600)启动：30s 时钟 + vt+36 备份抹除 + 相位 2 + this+8632=·sub_5BF430 传送次数
//   （全局 dword_9A05D4>2 归零）+ 1s 时钟；相位 2 每 1s 经 ·sub_5AE3C0 随机抽玩家，vt+140 落点
//   校验 + vt+376 层过滤后 vt+592(420) 传袭 48012，次数耗尽进相位 3(3s)；相位 3 从 this+7252
//   记录点出土、48012、setState(19)；相位 4 落地：镜头 2/300、vt+876(200,200) 击退、
//   BurrowEnd.ani，进相位 5；相位 5 动作尾后 setState(0) 终相位 6。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C1750(int this)  // 函数: 蜘蛛王·钻地传送追击相位机（this+8636 相位 1..6）
{
  int fld_21BC; // eax
  int nPhaseDeadline; // ebx
  int nPlayerCnt; // eax
  int pRandomPlayer; // eax
  int pVt; // edi
  int nZ160; // ebx
  int nRand; // eax
  int nSpawnX; // ebx
  int nRand2; // eax
  int pLayerMgr; // eax
  int pVt2; // edi
  int nLayerId; // ebx
  int nFindRes; // eax
  int nZBase; // eax
  int nDestId; // eax
  int nFaceDir; // eax
  bool fld_21B82; // zf
  int nPhaseDeadline2; // edi
  int nEmergeX; // edi
  int nEmergeY; // eax
  int nTarget; // ecx
  int nEmergeY2; // ebx
  int nZ2; // eax
  int nFaceDir2; // eax
  int pMount; // eax
  void *pCurAct; // eax
  int hAniBurrow; // edi
  int *pFxBurrow; // edi
  int pFxHost; // ecx
  int pFxBurrowVt; // ebx
  int nZ3; // eax
  int nY3; // eax
  int nX3; // eax
  int pFxBurrowVt2; // ebx
  int nFaceDir3; // eax
  int v38; // [esp+0h] [ebp-24h]
  int pObj; // [esp+Ch] [ebp-18h]
  int v40; // [esp+Ch] [ebp-18h]
  int v41; // [esp+10h] [ebp-14h] BYREF
  int v42; // [esp+14h] [ebp-10h] BYREF
  int v43; // [esp+20h] [ebp-4h]

  if ( *(uint32_t *)(this + 8636) == 1 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this) >= 600 )  // 调用虚函数（虚表槽 +128）
  {
    *(uint8_t *)(this + 8701) = 0;
    *(uint8_t *)(this + 8702) = 0;
    sub_698F90(this + 8688, 30000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(uint32_t *)(this + 8744) = *(uint32_t *)(*(uint32_t *)(this + 112) + 36);  // this+8744 【推断】主倒计时截止
    sub_495890((int *)this, 2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
    *(uint32_t *)(*(uint32_t *)(this + 112) + 36) = 0;  // this+112 第 1 组·宿主属性 +46 增量子倍率
    *(uint32_t *)(this + 8636) = 2;  // this+8636 【推断】传送/钻地相位槽
    *(uint32_t *)(this + 8632) = sub_5BF430(this);  // 调 档位换算表（·sub_456390(0) 查询 → 2/3/4/6）
    if ( dword_9A05D4 > 2 )  // 全局 竞技场/PVP 深度计数
      *(uint32_t *)(this + 8632) = 0;  // this+8632 【推断】子类 AI 资源/计数槽
    *(uint8_t *)(this + 8729) = 0;
    *(uint8_t *)(this + 8730) = 0;
    LOBYTE(fld_21BC) = sub_698F90(this + 8716, 1000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  else
  {
    fld_21BC = *(uint32_t *)(this + 8636);  // this+8636 【推断】传送/钻地相位槽
    switch ( fld_21BC )  // 按 fld_21BC 分派
    {
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        LOBYTE(fld_21BC) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        if ( (uint8_t)fld_21BC != 0 )
        {
          nPhaseDeadline = *(uint32_t *)(this + 8740);
          fld_21BC = sub_699000(this + 8716);  // 【clock_now(clk)】
          if ( fld_21BC >= nPhaseDeadline )
          {
            *(uint8_t *)(this + 8729) = 0;
            *(uint8_t *)(this + 8730) = 0;
            sub_698F90(this + 8716, 1000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
            if ( *(int *)(this + 8632) > 0 )  // this+8632 【推断】子类 AI 资源/计数槽
            {
              nPlayerCnt = sub_456390(0);  // 调 存 座位号查询
              pRandomPlayer = sub_5AE3C0(*(uint32_t *)(this + 8632) % nPlayerCnt);  // 调 关联对象取字段（数组槽 pArg2+4 解引用 +196）
              pObj = pRandomPlayer;
              if ( pRandomPlayer != 0 )
              {
                pVt = *(uint32_t *)this;
                nZ160 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pRandomPlayer + 124))(pRandomPlayer, 160, 1, 1);  // 调用虚函数（虚表槽 +124）
                nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
                nSpawnX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, nRand % 50 + nZ160);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
                nRand2 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
                if ( (*(uint8_t (/*thiscall*/ **)(int, int *, int *, int))(pVt + 140))(  // 调用虚函数（虚表槽 +140）【推断: ★ 螺旋式寻找空位（同心方环，从 (a4,a5) 起向外扫）】
                       this,
                       &v41,
                       &v42,
                       nRand2 % 50 + nSpawnX) != 0 )
                {
                  pLayerMgr = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
                  pVt2 = *(uint32_t *)this;
                  nLayerId = *(uint32_t *)(*(uint32_t *)(pLayerMgr + 108) + 112);
                  nFindRes = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                          this,
                          2,
                          0,
                          0,
                          0xFFFF,
                          0,
                          0,
                          0,
                          0);
                  nZBase = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 128))(this, nFindRes);  // 调用虚函数（虚表槽 +128）
                  nDestId = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 376))(  // 调用虚函数（虚表槽 +376）
                          this,
                          nLayerId,
                          v41,
                          v42,
                          nZBase);
                  (*(void (/*thiscall*/ **)(int, int, int))(pVt2 + 592))(this, 420, nDestId);  // 调用虚函数（虚表槽 +592）【推断: 位置/状态同步包发布（短版 48024 / 长版 type 22…】
                  nFaceDir = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                  sub_4E4A50(pVt2, this, 48012, 1, v41, v42, 0, nFaceDir, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
                }
              }
            }
            fld_21BC = *(uint32_t *)(this + 8632) - 1;  // this+8632 【推断】子类 AI 资源/计数槽
            fld_21B82 = *(uint32_t *)(this + 8632) == 1;  // this+8632 【推断】子类 AI 资源/计数槽
            *(uint32_t *)(this + 8632) = fld_21BC;  // this+8632 【推断】子类 AI 资源/计数槽
            if ( fld_21BC < 0 || fld_21B82 )
            {
              *(uint8_t *)(this + 8729) = 0;
              *(uint8_t *)(this + 8730) = 0;
              LOBYTE(fld_21BC) = sub_698F90(this + 8716, 3000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
              *(uint32_t *)(this + 8636) = 3;  // this+8636 【推断】传送/钻地相位槽
            }
          }
        }
        break;
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        nPhaseDeadline2 = *(uint32_t *)(this + 8740);
        fld_21BC = sub_699000(this + 8716);  // 【clock_now(clk)】
        if ( fld_21BC >= nPhaseDeadline2 )
        {
          nEmergeX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          nEmergeY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 124))(this);  // 调用虚函数（虚表槽 +124）
          nTarget = *(uint32_t *)(this + 7252);  // this+7252 当前目标/技能对象
          nEmergeY2 = nEmergeY;
          if ( nTarget != 0 )
          {
            nEmergeX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nTarget + 120))(nTarget);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
            nEmergeY2 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 124))(*(uint32_t *)(this + 7252));  // 调用虚函数（虚表槽 +124）
            v40 = *(uint32_t *)this;
            nZ2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // 调用虚函数（虚表槽 +128）
            (*(void (/*thiscall*/ **)(int, int, int, int))(v40 + 108))(this, nEmergeX, nEmergeY2, nZ2);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
          }
          nFaceDir2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          sub_4E4A50(nEmergeX, this, 48012, 2, nEmergeX, nEmergeY2, 0, nFaceDir2, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
          LOBYTE(fld_21BC) = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
                         this,
                         19,
                         0,
                         0,
                         0);
        }
        break;
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        fld_21BC = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // 调用虚函数（虚表槽 +128）
        if ( fld_21BC <= 0 )
        {
          pMount = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 80))(this);  // 调用虚函数（虚表槽 +80）
          sub_424120(*(uint32_t **)(pMount + 132), 2, 300);  // 调 屏幕震动启动
          pCurAct = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 200))(this, 1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          sub_4AECE0(pCurAct, v38);  // 调 切武器动画
          hAniBurrow = 0;
          (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
            this,
            0,
            200,
            200,
            0,
            0);
          sub_4A0550(*(float **)(this + 112), 150);  // this+112 第 1 组·宿主属性 +46 增量子倍率
          fld_21BC = sub_42FCB0(228);  // 调 CRT 一次性初始化
          v43 = 0;
          if ( fld_21BC != 0 )
          {
            fld_21BC = sub_431860((char)"Monster/Spider/SpiderAni/BurrowEnd.ani", 1);  // 调 动画件构造（资源 id 版）
            hAniBurrow = fld_21BC;
          }
          v43 = -1;
          if ( hAniBurrow != 0 )
          {
            v43 = 1;
            if ( sub_44B6C0(284) != 0 )  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
              pFxBurrow = (int *)sub_44E1F0(hAniBurrow, 1);  // 调 CNRDPooledObject 构造（虚表覆盖壳）
            else
              pFxBurrow = nullptr;
            pFxHost = *(uint32_t *)(this + 116);  // this+116 观察者 vector 尾针
            v43 = -1;
            sub_45FE80(pFxHost, (int)pFxBurrow, 2, 0, (int)pFxBurrow, this, 0);  // 调 对象注册
            pFxBurrowVt = *pFxBurrow;
            nZ3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // 调用虚函数（虚表槽 +128）
            nY3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, nZ3);  // 调用虚函数（虚表槽 +124）
            nX3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, nY3);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
            (*(void (/*thiscall*/ **)(int *, int))(pFxBurrowVt + 112))(pFxBurrow, nX3);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
            pFxBurrowVt2 = *pFxBurrow;
            nFaceDir3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            LOBYTE(fld_21BC) = (*(int (/*thiscall*/ **)(int *, int))(pFxBurrowVt2 + 144))(pFxBurrow, nFaceDir3);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
          }
          *(uint32_t *)(this + 8636) = 5;  // this+8636 【推断】传送/钻地相位槽
        }
        break;
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        fld_21BC = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        if ( *(uint8_t *)(fld_21BC + 170) != 0 )
        {
          LOBYTE(fld_21BC) = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
                         this,
                         0,
                         0,
                         0,
                         0);
          *(uint32_t *)(this + 8636) = 6;  // this+8636 【推断】传送/钻地相位槽
        }
        break;
      default:
        break;
    }
  }
  return fld_21BC;
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5C1C00 sub_5C1C00 —— 幼蛛（CNYoungSpider）构造：vftable 换装 + 子类复位
// 基类构造 ·sub_4A4EA0 后把 vftable 指向 CNYoungSpider 的 vftable（RTTI 名），再经 ·sub_5BE7C0
//   执行蜘蛛子类字段复位（六槽动作号 + this+732），最后 ·sub_4D50A0 复位 1554 指向的帧槽。
// ------------------------------------------------------------
uint32_t **/*thiscall*/ sub_5C1C00(uint32_t **this, char ArgList, int nArg3, int nArg4)  // 函数: 幼蛛（CNYoungSpider）构造：vftable 换装 + 子类复位
{
  sub_4A4EA0(ArgList, nArg3);  // 调 IRDMonster 基类构造
  *this = &CNYoungSpider::`vftable';  // vftable 复位
  sub_5BE7C0(this);  // 调 蜘蛛·子类字段复位（六槽动作号 + this+7324 类型号）
  sub_4D50A0(**(this + 1554));  // this+6216 = 资源/帧游标表
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C1C70 sub_5C1C70 —— 幼蛛析构（标量删除版）：vftable 复原 + 可选 j__free
// 先调 ·sub_5C1CA0 走析构体（vftable 回 CNYoungSpider 类），若 pszArg2 低位为 1（持有堆块）则
//   j__free(Block) 释放自身。
// ------------------------------------------------------------
void */*thiscall*/ sub_5C1C70(void *Block, char pszArg2)  // 函数: 幼蛛析构（标量删除版）：vftable 复原 + 可选 j__free
{
  sub_5C1CA0();  // 调 幼蛛析构体：vftable 复原 + 基类释构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C1CA0 sub_5C1CA0 —— 幼蛛析构体：vftable 复原 + 基类释构
// vftable 回写 CNYoungSpider 的 vftable（RTTI 名）后转 ·sub_4A50F0 基类析构，无独占释放动作。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C1CA0(uint32_t *this)  // 函数: 幼蛛析构体：vftable 复原 + 基类释构
{
  *this = &CNYoungSpider::`vftable';  // vftable 复位
  return sub_4A50F0();  // 调 IRDMonster 基类析构
}



// 蛛丝火花：Monster/Spider/SpiderBossAni/ThreadSpark.ani（100L；sub_431860）
// ------------------------------------------------------------
// 0x5C1CB0 sub_5C1CB0 —— 蜘蛛王·伏击行（大状态 6 待机 / 8 攻击 / 15..19 剧情节转发）
// 前置 ·sub_5BECF0 吐丝触发门；this+8653 置 1 即 vt+216 切 9；大状态 6 且 8616 与动作帧(+148)≥4
//   时镜头 2/450 清 8616（伏击收束）；大状态 8 按 vt+908 分派：0 → ·sub_5BF210 三连蛛网 30100、
//   1 → ·sub_5BF2D0 Boss 导弹、2 → ·sub_5BFE90 滚动跳跃冲撞、3 → 高度≤0 且 8748==1 播
//   ThreadSpark.ani 蛛丝火花后 setState(18)；15 → ·sub_5C15A0、16/17 → ·sub_5C12B0 出土、
//   18/19 → this[2159] 非 0 走 ·sub_5C1750 传送追击否则 ·sub_5BF3D0。
// ------------------------------------------------------------
void /*usercall*/ sub_5C1CB0(int *pDwArg1@<ecx>, int nArg2@<edi>)  // 函数: 蜘蛛王·伏击行（大状态 6 待机 / 8 攻击 / 15..19 剧情节转发）
{
  int v3; // eax
  int v4; // edi
  int *v5; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int v13; // eax

  sub_5BECF0((int)pDwArg1);  // 调 蜘蛛·吐丝触发门（攻击帧段匹配 + 相位锁）
  if ( *((uint8_t *)pDwArg1 + 8653) == 1 )
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
  if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 6 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( *((uint8_t *)pDwArg1 + 8616) != 0 && *(int *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) + 148) >= 4 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    {
      v3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 调用虚函数（虚表槽 +80）
      sub_424120(*(uint32_t **)(v3 + 132), 2, 450);  // 调 屏幕震动启动
      *((uint8_t *)pDwArg1 + 8616) = 0;
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 908))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +908）
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 908))(pDwArg1) == 1 )  // 调用虚函数（虚表槽 +908）
      {
        sub_5BF2D0(pDwArg1);  // 调 Boss·导弹齐射（BossMissile1/3/2/4.ptl，30200 号 × this+2161 发）
      }
      else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 908))(pDwArg1) == 2 )  // 调用虚函数（虚表槽 +908）
      {
        sub_5BFE90(pDwArg1);  // 调 滚动蜘蛛·跳跃冲撞（双相驱动，概要见上方既有注释）
      }
      else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 908))(pDwArg1) == 3 )  // 调用虚函数（虚表槽 +908）
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) <= 0 && *((uint8_t *)pDwArg1 + 8748) == 1 )  // 调用虚函数（虚表槽 +128）
        {
          v4 = 0;
          if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
            v4 = sub_431860((char)"Monster/Spider/SpiderBossAni/ThreadSpark.ani", 1);  // 调 动画件构造（资源 id 版）
          if ( v4 != 0 )
          {
            if ( sub_44B6C0(284) != 0 )  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
              v5 = (int *)sub_44E1F0(v4, 1);  // 调 CNRDPooledObject 构造（虚表覆盖壳）
            else
              v5 = nullptr;
            v6 = *v5;
            v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            (*(void (/*thiscall*/ **)(int *, int))(v6 + 144))(v5, v7);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
            sub_45FE80(pDwArg1[29], (int)v5, 2, 0, (int)v5, (int)pDwArg1, 0);  // 调 对象注册
            v8 = *v5;
            v9 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调用虚函数（虚表槽 +128）
            v10 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v9);  // 调用虚函数（虚表槽 +124）
            v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v10);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
            (*(void (/*thiscall*/ **)(int *, int))(v8 + 112))(v5, v11);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
            v12 = *v5;
            v13 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            (*(void (/*thiscall*/ **)(int *, int))(v12 + 144))(v5, v13);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
          }
          *((uint8_t *)pDwArg1 + 8748) = 0;
        }
        if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) + 170) != 0  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 568))(pDwArg1) != 18 )  // 调用虚函数（虚表槽 +568）
        {
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 18, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        }
      }
    }
    else
    {
      sub_5BF210(pDwArg1);  // 调 蜘蛛·三连蛛网齐射（30100 号挂 this+2155/2156/2157 三槽）
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 15 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    sub_5C15A0(pDwArg1);  // 调 蜘蛛王·出土收束（this+8660 时钟门，大状态 16 尾段）
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 16 || (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 17 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    sub_5C12B0(pDwArg1, nArg2);  // 调 蜘蛛王·钻地传送出土四相机（this+8640 相位 1..3）
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 18 || (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 19 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( pDwArg1[2159] != 0 )
      sub_5C1750(pDwArg1);  // 调 蜘蛛王·钻地传送追击相位机（this+8636 相位 1..6）
    else
      sub_5BF3D0(pDwArg1);  // 调 蜘蛛·冲撞准备（速率轴清位 + 姿态档 4 提交）
  }
}



// ============================================================
// 【分区 2】机器人·自爆与弹簧（高达梗粒子）（0x5C1FC0-0x5C3A30）
// 证据：ROBOT_WORK_LOOP/SPRING_UNWINDS_LOOP/EX_SET/EX_READY/MOVE_LOOP/CLICK_LOOP、
//       ROBOT_EX_01 + PassiveObject/Common/Animation/EarthQuake.ani + particle/Rx78_Boom.ptl、
//       ROBOT_EX_02 + particle/Ez8_Boom.ptl、BOMB_READY_LOOP、Particle/{Exs_Bullet,EXS_Boom}.ptl

// 子类扩展字段复位（this+8600..8616）
// ------------------------------------------------------------
// 0x5C1FC0 sub_5C1FC0 —— 机器人·子类扩展字段复位（this+8600..8616，出怪初始化）
// 一次清 this+8600/8604/8608 三个句柄槽、this+8612 置 0xFFFF（无效句柄哨兵）、this+8616 清 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C1FC0(int this)  // 函数: 机器人·子类扩展字段复位（this+8600..8616，出怪初始化）
{
  *(uint32_t *)(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
  *(uint32_t *)(this + 8604) = 0;  // this+8604 子类 AI 状态槽/相位门
  *(uint32_t *)(this + 8608) = 0;  // this+8608 骑乘/骑手槽
  *(uint32_t *)(this + 8612) = 0xFFFF;  // 常量 0xFFFF（= 0xFFFF）
  *(uint8_t *)(this + 8616) = 0;  // this+8616 【推断】钻地相位字节1
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C1FF0 sub_5C1FF0 —— 机器人·挂载对象释放（this+8608 槽，与 ·0x5C28A0/·0x5C3170 同构）
// 槽 this[2152] 非空时经其 vt[0](obj,1) 走删除路径，随后槽清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C1FF0(uint32_t *this)  // 函数: 机器人·挂载对象释放（this+8608 槽，与 ·0x5C28A0/·0x5C3170 同构）
{
  int (/*thiscall*/ ***fld_e2152)(uint32_t, int); // ecx
  int result; // eax

  fld_e2152 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2152);  // this+8608 = uAI8608
  if ( fld_e2152 != nullptr )  // 若 fld_e2152 有效（非空）
    result = (**fld_e2152)(fld_e2152, 1);  // 调 fld_e2152 的虚函数（vt+0）
  *(this + 2152) = 0;  // this+8608 = uAI8608
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C2010 sub_5C2010 —— 机器人·大状态进入副作用门（24 除外）
// nArg1 即新大状态号；非 24 时转 ·sub_4DBA80 大状态进入副作用处理器（增益侧），24 直接返回。
// ------------------------------------------------------------
int /*stdcall*/ sub_5C2010(int nArg1)  // 函数: 机器人·大状态进入副作用门（24 除外）
{
  int result; // eax

  result = nArg1;
  if ( nArg1 != 24 )
    return sub_4DBA80(nArg1);  // 调 大状态进入副作用处理器（增益侧）
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C2030 sub_5C2030 —— 机器人·观察者广播收尾 + 目标槽清空
// 先走 ·sub_4D9760 观察者广播后条件收尾，再把 this[1812]（目标对象槽）清 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2030(uint32_t *this)  // 函数: 机器人·观察者广播收尾 + 目标槽清空
{
  int result; // eax

  result = sub_4D9760();  // 调 观察者广播后条件收尾
  *(this + 1812) = 0;
  return result;
}



// 待机循环：ROBOT_WORK_LOOP + SPRING_UNWINDS_LOOP 播报（机器人待机/弹簧松脱, 47L）
// ------------------------------------------------------------
// 0x5C2050 sub_5C2050 —— 机器人·待机行为字选择与循环音播报
// ·sub_4E0120 前置后按 this[1787]（行为字）：非 0 且为 5——无目标(this[1813]==0) 写 23、否则；
//   ==21 直接返回；其余无目标写 23、有目标写 5；
// 行为字 0（初始）时写 23 并播 ROBOT_WORK_LOOP(10099) + SPRING_UNWINDS_LOOP(10101) 循环音。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2050(int *this)  // 函数: 机器人·待机行为字选择与循环音播报
{
  int result; // eax

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148 = nBigState
  if ( result != 0 )  // 若结果非 0（成功）
  {
    if ( result == 5 )
    {
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 23);  // 调用虚函数（虚表槽 +1104）
    }
    else
    {
      if ( result == 21 )
        return result;
      if ( *(this + 1813) == 0 )  // this+7252 = pTarget7252
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 23);  // 调用虚函数（虚表槽 +1104）
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);  // 调用虚函数（虚表槽 +1104）
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 23);  // 调用虚函数（虚表槽 +1104）
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      this,
      "ROBOT_WORK_LOOP",  // 资源/动画 TAG ROBOT_WORK_LOOP
      10099,
      0,
      0);
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
             this,
             "SPRING_UNWINDS_LOOP",  // 资源/动画 TAG SPRING_UNWINDS_LOOP
             10101,
             0,
             0);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C20F0 sub_5C20F0 —— 机器人·自爆挂载句柄门（this+8612）
// this[2153] 为 0xFFFF（无效哨兵）时转 ·sub_4DA1D0（触发自爆收尾），否则不做动作。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C20F0(uint32_t *this)  // 函数: 机器人·自爆挂载句柄门（this+8612）
{
  int result; // eax

  if ( *(this + 2153) == 0xFFFF )  // this+8612 = uAI8612
    return sub_4DA1D0();
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C2110 sub_5C2110 —— 机器人·按行为字分派的落点格选取
// 按 this[1787]（行为字）分派：5（自爆中）→ ·sub_4DBDB0 空间栅格重叠检测；
//   21 → vt+184 取向 + ·sub_432E50 + 随机 2/3 格，vt+144 落座；
//   23 → 当前朝向 vt+152 直接作格；
//   其余 → ·sub_4DF2D0 大状态逐帧 tick 分派器兜底。
// ------------------------------------------------------------
int /*userpurge*/ sub_5C2110@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int *pDwArg3, uint32_t *uArg4, int nArg5)  // 实现：机器人·按行为字分派的落点格选取
{
  int result; // eax
  int v7; // eax

  switch ( pArg1[1787] )  // 按 pArg1[1787] 分派
  {
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      return sub_4DBDB0(pDwArg3, uArg4);  // 调 ★ 空间栅格重叠检测（碰撞/挤压分离轴；研究第 24/25 轮族）
    case 0x15:
      v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 184))(pArg1, nArg2);  // 调用虚函数（虚表槽 +184）【推断: 动画对象 z 倾斜转状态码】
      *pDwArg3 = sub_432E50(v7);  // 调 关系码对调映射
      *uArg4 = 3 - (rand() % 2 != 0);  // 调 以 16 位种子状态递推并返回 15 位结果
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 144))(pArg1, *pDwArg3);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
    case 0x17:
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      *pDwArg3 = result;
      *uArg4 = 4;
      break;
    default:
      return sub_4DF2D0(pDwArg3, uArg4, nArg5);  // 调 ★ 大状态逐帧 tick 分派器（研究 §16 P41：tick case 硬编码）
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C21D0 sub_5C21D0 —— 机器人·自爆挂载生效时移出场景
// this[2153]（自爆挂载句柄）非 0xFFFF 时 vt+112 把本体写到 (-10000,-10000) 移出视野，
//   再走 ·sub_4D54E0（机器人帧序服务）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C21D0(uint32_t *this)  // 函数: 机器人·自爆挂载生效时移出场景
{
  if ( *(this + 2153) != 0xFFFF )  // this+8612 = uAI8612
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 112))(this, -10000, -10000, 0);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
  return sub_4D54E0(this);  // 调 受击包后：+1639==10 主状态镜像 且 +1953==0/+1954==15
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C2200 sub_5C2200 —— 机器人·消亡观察者回调（停止循环音 / 引爆转发）
// pArg2==this（自身消亡）→ vt+216 依次停 10099、10101、10100 三条循环音后 ·sub_4D9170 消亡通知；
// 否则目标须 vt+40 标记 33 且 vt+52 等于 this[2153]（自爆挂载句柄）时调 vt+1256（引爆/触发）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2200(uint32_t *this, uint32_t *pArg2)  // 函数: 机器人·消亡观察者回调（停止循环音 / 引爆转发）
{
  if ( pArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10099);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10101);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10100);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
    return sub_4D9170(pArg2);  // 调 消亡通知
  }
  else
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 33) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
      && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 52))(pArg2) == *(this + 2153) )  // this+8612 = uAI8612
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1256))(this);  // 调用虚函数（虚表槽 +1256）
    }
    return sub_4D9170(pArg2);  // 调 消亡通知
  }
}



// 数据表读数 + RTTI cast（sub_47EF20 —— 目标数值读取, 研究 17/20）
// ------------------------------------------------------------
// 0x5C2280 sub_5C2280 —— 机器人一型·属性重算与数据表读数（ROBOT_EX_01 数值装配）
// ·sub_4DD8F0 属性块整体重算后，RTDynamicCast 把 this[2088] 转为 CNGunner 实例；
//   经 vt+672 取数据表条目：+60×+74 与 +116×+130 两组乘积分别写入 this+184/this+198 双精度槽，
//   vt+676 提交；再 ·sub_47E720(2,27)/vt+1140(27) → ·sub_47EF20 读表得 this[2150]、
//   ·sub_47EFD0 生成 this[2151]（技能 40002 用的伤害档位与关联参数）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2280(int *this, int nArg2, int nArg3)  // 函数: 机器人一型·属性重算与数据表读数（ROBOT_EX_01 数值装配）
{
  int result; // eax
  int pObj; // esi
  int v6; // ebx
  uint64_t v7; // rax
  int v8; // ebx
  uint64_t v9; // rax
  char *v10; // ebx
  int v11; // eax
  int v12; // [esp+14h] [ebp+Ch]
  int v13; // [esp+14h] [ebp+Ch]
  int v14; // [esp+14h] [ebp+Ch]

  sub_4DD8F0(this, nArg2, nArg3);  // 调 属性块整体重算（全量成长）
  result = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
             *(this + 2088),  // this+8352 = 骑乘/宿主槽
             0,
             &IRDActiveObject `RTTI Type Descriptor',
             &CNGunner `RTTI Type Descriptor',
             0);
  pObj = result;
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 672))(result, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    v12 = sub_41A5E0(v6 + 60);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    v7 = (uint64_t)((double)v12 * COERCE_FLOAT(sub_41A5E0(v6 + 74)));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590((unsigned int)(this + 184), SHIDWORD(v7), v7);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    v13 = sub_41A5E0(v8 + 116);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    v9 = (uint64_t)((double)v13 * COERCE_FLOAT(sub_41A5E0(v8 + 130)));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590((unsigned int)(this + 198), SHIDWORD(v9), v9);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
    v10 = (char *)sub_47E720(2, 27);  // 调 调 sub_47E720
    v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, 27);  // 调用虚函数（虚表槽 +1140）
    *(this + 2150) = sub_47EF20(2, v14, -1, -1, 11);  // this+8600 = uAI8600
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);  // 调用虚函数（虚表槽 +388）【推断: [RTTI: IRDActiveObject__vmt184 ·…】
    result = sub_47EFD0(v10, COERCE_FLOAT(1), v14, v11, v11, 0);
    *(this + 2151) = result;  // this+8604 = bAI8604
  }
  return result;
}



// 布设状态机：ROBOT_EX_SET + ROBOT_EX_READY + ROBOT_MOVE_LOOP 三段播报（60L）
// ------------------------------------------------------------
// 0x5C23A0 sub_5C23A0 —— 机器人一型·布设与移动三段状态机（ROBOT_EX_SET/EX_READY/MOVE_LOOP）
// ArgList==14（架招/被绑定）时直接把参数对象首字段存 this[2153]（挂载句柄）；否则按 this[1639]
//   （主状态镜像 2）：8 → vt[52] 帧槽复位、0 → vt[54] 播 10100；随后 ·sub_4E33D0 状态收尾。
// ArgList==8（进入攻击）：vt+888 写 (0,0,1000,1000)、·sub_4926A0 帧游标复位、vt+204 写 1000 帧起播、
//   依次播 ROBOT_EX_SET + ROBOT_EX_READY；ArgList==0（待机）→ 播 ROBOT_MOVE_LOOP(10100)。
// ------------------------------------------------------------
int **/*thiscall*/ sub_5C23A0(int **this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 机器人一型·布设与移动三段状态机（ROBOT_EX_SET/EX_READY/MOVE_LOOP）
{
  int **result; // eax
  int fld_e1639; // eax

  if ( ArgList == 14 )
  {
    result = *(int ***)(LODWORD(fArg3) + 4);  // 调 取 64 位值低 32 位
    *(this + 2153) = *result;  // this+8612 = uAI8612
  }
  else
  {
    fld_e1639 = (int)*(this + 1639);  // this+6556 = 主状态镜像
    if ( fld_e1639 == 8 )
    {
      ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[52])(this, **(this + 1554));  // this+6216 = 资源/帧游标表
    }
    else if ( fld_e1639 == 0 )
    {
      ((void (/*thiscall*/ *)(int **, int))(*this)[54])(this, 10100);
    }
    result = (int **)sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
    if ( ArgList == 8 )
    {
      ((void (/*thiscall*/ *)(int **, uint32_t, uint32_t, int, int))(*this)[222])(this, 0, 0, 1000, 1000);
      sub_4926A0(**(this + 1554));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      ((void (/*thiscall*/ *)(int **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
        this,
        1000,
        **(this + 1554),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      ((void (/*thiscall*/ *)(int **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "ROBOT_EX_SET", -1, 0, 0);  // 资源/动画 TAG ROBOT_EX_SET
      return (int **)((int (/*thiscall*/ *)(int **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                       this,
                       "ROBOT_EX_READY",  // 资源/动画 TAG ROBOT_EX_READY
                       -1,
                       0,
                       0);
    }
    else if ( ArgList == 0 )
    {
      return (int **)((int (/*thiscall*/ *)(int **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                       this,
                       "ROBOT_MOVE_LOOP",  // 资源/动画 TAG ROBOT_MOVE_LOOP
                       10100,
                       0,
                       0);
    }
  }
  return result;
}



// 自爆一型（125L）：ROBOT_EX_01 播报 + PassiveObject/Common/Animation/EarthQuake.ani
//   震地 + particle/Rx78_Boom.ptl 爆点（★高达梗: Rx78）
// ------------------------------------------------------------
// 0x5C24B0 sub_5C24B0 —— 机器人一型·自爆（ROBOT_EX_01 + EarthQuake.ani + Rx78_Boom.ptl）
// this+8616==0 时一次性执行：播 ROBOT_EX_01；爆点取本体 vt+120/124/128——大状态 8 时按朝向
//   vt+152 偏移 ±65 且 Z+20，否则 Z+30；·sub_44B6C0 池 + ·sub_42FCB0(228) + ·sub_431860 载
//   EarthQuake.ani 震地挂宿主 this[29]；this[2152] 未占则 new(0x12C) + ·sub_4C3640 生成
//   particle/Rx78_Boom.ptl（★高达梗 Rx78 爆点），vt+40 定位 + ·sub_4600B0 挂载；置 8616=1，
//   存活时 ·sub_4E4A50 技能 40002 + setState(14) + vt+108 隐至 (-10000,-10000)。
// ------------------------------------------------------------
void /*usercall*/ sub_5C24B0(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 函数: 机器人一型·自爆（ROBOT_EX_01 + EarthQuake.ani + Rx78_Boom.ptl）
{
  int nY; // eax
  int pVt; // edx
  int nZ; // ebx
  int nBlastZ; // ebx
  char *pQuakeFx; // edi
  void *pResGate; // eax
  int hAniQuake; // eax
  int pQuakeFxVt; // eax
  int *pBoomPtl; // eax
  int pBoomPtlVt; // edx
  void *pFxHost; // ecx
  int pVt2; // edx
  int nFaceDir; // eax
  char v16[4]; // [esp+4h] [ebp-3Ch] BYREF
  void *v17; // [esp+8h] [ebp-38h]
  int v18; // [esp+Ch] [ebp-34h]
  int v19; // [esp+10h] [ebp-30h]
  char v20[4]; // [esp+14h] [ebp-2Ch] BYREF
  void *Block; // [esp+18h] [ebp-28h]
  int v22; // [esp+1Ch] [ebp-24h]
  int v23; // [esp+20h] [ebp-20h]
  void *pResGate2; // [esp+24h] [ebp-1Ch]
  char *pQuakeFx2; // [esp+28h] [ebp-18h]
  int nBlastY; // [esp+2Ch] [ebp-14h]
  int nBlastX; // [esp+30h] [ebp-10h]
  int v28; // [esp+3Ch] [ebp-4h]

  if ( *((uint8_t *)pDwArg1 + 8616) == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(pDwArg1, "ROBOT_EX_01", -1, 0, 0, nArg2);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
    nBlastX = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    nY = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);  // 调用虚函数（虚表槽 +124）
    pVt = *pDwArg1;
    nBlastY = nY;
    nZ = (*(int (/*thiscall*/ **)(int *))(pVt + 128))(pDwArg1);  // 调用虚函数（虚表槽 +128）
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    {
      nBlastX += (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1) != 0 ? 65 : -65;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      nBlastZ = nZ + 20;
    }
    else
    {
      nBlastZ = nZ + 30;
    }
    pQuakeFx = (char *)sub_44B6C0(284);  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
    pQuakeFx2 = pQuakeFx;
    v28 = 0;
    if ( pQuakeFx != nullptr )  // 若 pQuakeFx 有效（非空）
    {
      pResGate = (void *)sub_42FCB0(228);  // 调 CRT 一次性初始化
      pResGate2 = pResGate;
      LOBYTE(v28) = 1;  // 调 取 16 位值低 8 位
      if ( pResGate != nullptr )  // 若 pResGate 有效（非空）
        hAniQuake = sub_431860((int)pResGate, "PassiveObject/Common/Animation/EarthQuake.ani", 1);  // 调 动画件构造（资源 id 版）
      else
        hAniQuake = 0;
      LOBYTE(v28) = 0;  // 调 取 16 位值低 8 位
      sub_44E0D0(pQuakeFx, hAniQuake, 1);  // 调 CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)pQuakeFx = &CNRDPooledObject::`vftable';  // vftable 复位
    }
    else
    {
      pQuakeFx = nullptr;
    }
    pQuakeFxVt = *(uint32_t *)pQuakeFx;
    v28 = -1;
    (*(void (/*thiscall*/ **)(char *, int))(pQuakeFxVt + 72))(pQuakeFx, 2);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    sub_45FE80(pDwArg1[29], (int)pQuakeFx, 2, 0, (int)pQuakeFx, (int)pDwArg1, 0);  // 调 对象注册
    (*(void (/*thiscall*/ **)(char *, int, int, int))(*(uint32_t *)pQuakeFx + 112))(pQuakeFx, nBlastX, nBlastY + 1, nBlastZ);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    if ( pDwArg1[2152] == 0 )
    {
      pResGate2 = operator new(0x12Cu);  // operator new 分配 300 字节
      v28 = 2;
      if ( pResGate2 != nullptr )  // 若 pResGate2 有效（非空）
      {
        if ( (unsigned int)pDwArg1[96] < 0x10 )
          pBoomPtl = (int *)sub_4C3640(pDwArg1 + 91, "particle/Rx78_Boom.ptl", pDwArg1);  // 资源路径 particle/Rx78_Boom.ptl
        else
          pBoomPtl = (int *)sub_4C3640(pDwArg1[91], "particle/Rx78_Boom.ptl", pDwArg1);  // 资源路径 particle/Rx78_Boom.ptl
      }
      else
      {
        pBoomPtl = nullptr;
      }
      pDwArg1[2152] = (int)pBoomPtl;
      pBoomPtlVt = *pBoomPtl;
      v28 = -1;
      (*(void (/*thiscall*/ **)(int *, uint32_t))(pBoomPtlVt + 12))(pBoomPtl, 0);  // 调用虚函数（虚表槽 +12）
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2152] + 40))(pDwArg1[2152], nBlastX, nBlastY, nBlastZ);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pDwArg1[2152] + 92))(pDwArg1[2152], v20);  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
      pFxHost = (void *)pDwArg1[29];
      v28 = 3;
      sub_4600B0(pFxHost, 2, 0, (int)v20);  // 调 演播层注册(槽号)
      v28 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
      Block = nullptr;
      v22 = 0;
      v23 = 0;
    }
    pVt2 = *pDwArg1;
    *((uint8_t *)pDwArg1 + 8616) = 1;
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(pVt2 + 308))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    {
      nFaceDir = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      pDwArg1[2153] = sub_4E4A50(pDwArg1, 40002, pDwArg1[2151], nBlastX, nBlastY, nBlastZ, nFaceDir, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
      v17 = nullptr;
      v18 = 0;
      v19 = 0;
      v28 = 4;
      sub_431230((int)v16, pDwArg1 + 2153);  // 调 uint32 vector push_back
      (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 14, v16, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(*pDwArg1 + 108))(pDwArg1, -10000, -10000, 0);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
      if ( v17 != nullptr )  // 若 v17 有效（非空）
        j__free(v17);  // 调 堆释放
    }
  }
}


// 时钟门 AI（sub_699000; this+8600/8612）
// ------------------------------------------------------------
// 0x5C2760 sub_5C2760 —— 机器人一型·自爆倒计时驱动（this+8600 截止 − clock_now(this+36)）
// ·sub_4E1780 前置后算剩余毫秒：this+8612 为 0xFFFF（未引爆）时——剩余 ≤1500ms 且动作对象
//   (this+120) 存在则 ·sub_42B420(50,255,now,250) 闪烁相位 + ·sub_491690 写 0xFF00FFFF 系
//   亮度调制（引信闪光）；大状态 8 且动作尾(+170) 或 非 8 且剩余≤0 且 this+264==0 →
//   ·sub_5C24B0 引爆一型。
// ------------------------------------------------------------
void /*thiscall*/ sub_5C2760(int this)  // 函数: 机器人一型·自爆倒计时驱动（this+8600 截止 − clock_now(this+36)）
{
  int fld_2198; // ebx  | +0x2198 → 【推断】引信截止时刻（CNRobotRX78；va=005C2760）
  int pThis_24; // eax
  uint8_t v4; // al
  int fld_78; // eax  | +0x0078 → 动画对象指针〔CNRDObject.h +0x078；499020/499080 帧推进对象〕（CNRobotRX78；va=00499020）

  sub_4E1780((uint32_t *)this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  fld_2198 = *(uint32_t *)(this + 8600) - sub_699000(this + 36);  // 【clock_now(clk)】
  if ( *(uint32_t *)(this + 8612) == 0xFFFF )  // this+8612 锁定/相位字节 A
  {
    if ( fld_2198 <= 1500 && *(uint32_t *)(this + 120) != 0 )  // this+120 动画对象指针
    {
      pThis_24 = sub_699000(this + 36);  // 【clock_now(clk)】
      v4 = sub_42B420(50, 255, pThis_24, 250);  // 调 往返插值（三角波）
      sub_491690(1, 2, 1, -16776961, (v4 << 24) | 0xFFFFFF, 1);  // 调 图层后处理配置（this+176..196 图层参数块写入）
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    {
      fld_78 = *(uint32_t *)(this + 120);  // this+120 动画对象指针
      if ( fld_78 != 0 && *(uint8_t *)(fld_78 + 170) != 0 )
        sub_5C24B0((int *)this, fld_2198);  // 调 机器人一型·自爆（ROBOT_EX_01 + EarthQuake.ani + Rx78_Boom.ptl）
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) != 8 && fld_2198 <= 0 && *(uint8_t *)(this + 264) == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      sub_5C24B0((int *)this, fld_2198);  // 调 机器人一型·自爆（ROBOT_EX_01 + EarthQuake.ani + Rx78_Boom.ptl）
  }
}



// 子类扩展字段复位（this+8600..8630）
// ------------------------------------------------------------
// 0x5C2830 sub_5C2830 —— 机器人二型·子类扩展字段复位（this+8600..8630）
// 清 this+8600/8604/8608/8620/8624 句柄与计时槽，this+8624 置 0xFFFF（无效哨兵），
//   this+8628/8629/8630 三个标志位清 0（对应 Ez8 自爆与号码牌相位）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2830(int this)  // 函数: 机器人二型·子类扩展字段复位（this+8600..8630）
{
  *(uint32_t *)(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
  *(uint32_t *)(this + 8604) = 0;  // this+8604 子类 AI 状态槽/相位门
  *(uint32_t *)(this + 8608) = 0;  // this+8608 骑乘/骑手槽
  *(uint32_t *)(this + 8620) = 0;  // this+8620 相位双字节门
  *(uint32_t *)(this + 8624) = 0xFFFF;  // 常量 0xFFFF（= 0xFFFF）
  *(uint8_t *)(this + 8628) = 0;  // this+8628 【推断】指挥计时戳
  *(uint8_t *)(this + 8629) = 0;  // this+8629 【推断】引信点击音锁存
  *(uint8_t *)(this + 8630) = 0;  // this+8630 【推断】BOMB_READY 已播标志
  return 0;
}



// 号码牌资源：Monster/Gunner/Ez8/Ez8_Num.img（★高达梗: Ez8 机体编号图, 18L）
// ------------------------------------------------------------
// 0x5C2870 sub_5C2870 —— 机器人二型·Ez8 号码牌资源装配（Monster/Gunner/Ez8/Ez8_Num.img）
// 清 this+8612，this+8616=4（号牌档位），经 dword_8F84B8 vt+60 载 Ez8_Num.img 句柄写入
//   this+8608（★高达梗: Ez8 机体编号图，供 vt+376 目标层过滤链后的自爆 40002 显示）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2870(int this)  // 函数: 机器人二型·Ez8 号码牌资源装配（Monster/Gunner/Ez8/Ez8_Num.img）
{
  int result; // eax

  *(uint8_t *)(this + 8612) = 0;  // this+8612 锁定/相位字节 A
  *(uint32_t *)(this + 8616) = 4;  // this+8616 【推断】钻地相位字节1
  result = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
             dword_8F84B8,  // 全局 攻击判定管理器
             "Monster/Gunner/Ez8/Ez8_Num.img");  // 资源路径 Monster/Gunner/Ez8/Ez8_Num.img
  *(uint32_t *)(this + 8608) = result;  // this+8608 骑乘/骑手槽
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C28A0 sub_5C28A0 —— 机器人二型·爆点对象释放（this+8620 槽）
// 槽 this[2155] 非空时经其 vt[0](obj,1) 删除，随后槽清零（与 ·0x5C1FF0/·0x5C3170 同构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C28A0(uint32_t *this)  // 函数: 机器人二型·爆点对象释放（this+8620 槽）
{
  int (/*thiscall*/ ***fld_e2155)(uint32_t, int); // ecx
  int result; // eax

  fld_e2155 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2155);  // this+8620 = uAI8620
  if ( fld_e2155 != nullptr )  // 若 fld_e2155 有效（非空）
    result = (**fld_e2155)(fld_e2155, 1);  // 调 fld_e2155 的虚函数（vt+0）
  *(this + 2155) = 0;  // this+8620 = uAI8620
  return result;
}



// AI 字段访问（this+8630）
// ------------------------------------------------------------
// 0x5C28C0 sub_5C28C0 —— 机器人二型·消亡观察者回调（号码牌/引爆转发）
// this==uArg2（自身消亡）→ vt+216 停 10，且 this+8630 非 0（BOMB_READY 已播）时再停 9，
//   走 ·sub_4D9170；否则目标须 vt+40 标记 33 且 vt+52 等于 this[2156]（爆点挂载句柄）时调 vt+1256。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C28C0(uint8_t *this, uint8_t *uArg2)  // 函数: 机器人二型·消亡观察者回调（号码牌/引爆转发）
{
  if ( this == uArg2 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 10);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
    if ( *(this + 8630) != 0 )  // this+8630 【推断】BOMB_READY 已播标志
    {
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
      return sub_4D9170(uArg2);  // 调 消亡通知
    }
  }
  else if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)uArg2 + 40))(uArg2, 33) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
         && (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)uArg2 + 52))(uArg2) == *((uint32_t *)this + 2156) )  // this+8624 = uAI8624
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1256))(this);  // 调用虚函数（虚表槽 +1256）
  }
  return sub_4D9170(uArg2);  // 调 消亡通知
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C2930 sub_5C2930 —— 机器人二型·行为字归位（强制 23 自爆准备）
// ·sub_4E0120 前置后，this[1787] 非 23 时经 vt+1104 写行为字 23（引信/自爆准备态）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2930(uint32_t *this)  // 函数: 机器人二型·行为字归位（强制 23 自爆准备）
{
  int result; // eax

  result = sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  if ( *(this + 1787) != 23 )  // this+7148 = nBigState
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 23);  // 调用虚函数（虚表槽 +1104）
  return result;
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5C2950 sub_5C2950 —— 机器人二型·号码牌显隐门（层不同且倒计时 >1s）
// ·sub_4D54E0 后比较本体 vt+376 层号与全局 dword_8F7C04 的层号：不同且剩余
//   this[2150]−clock_now(this+36) 绝对值 >1000ms 时，取 this[30] 做 ·sub_4938F0 播放驱动
//   + ·sub_491F80 写 RGBA(-1,-1,-1,0,1)（保留原色、透明度归零 → 号牌隐藏）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2950(int *this)  // 函数: 机器人二型·号码牌显隐门（层不同且倒计时 >1s）
{
  int v2; // edi
  int result; // eax
  int fld_e30; // ecx  | +0x0078 → 动画对象指针〔CNRDObject.h +0x078；499020/499080 帧推进对象〕（CNRobotEz8；va=00499020）

  sub_4D54E0(this);  // 调 受击包后：+1639==10 主状态镜像 且 +1953==0/+1954==15
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 376))(this);  // 调用虚函数（虚表槽 +376）
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);  // 调用虚函数（虚表槽 +376）
  if ( v2 != result )
  {
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( (unsigned int)(*(this + 2150) - result) > 0x3E8 )  // this+8600 = uAI8600
    {
      fld_e30 = *(this + 30);  // this+120 = 动画对象指针
      if ( fld_e30 != 0 )
      {
        sub_4938F0(fld_e30);  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
        return sub_491F80(-1, -1, -1, 0, 1);  // 调 RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
      }
    }
  }
  return result;
}



// 时钟门 AI（sub_699000, 53L）
// ------------------------------------------------------------
// 0x5C29B0 sub_5C29B0 —— 机器人二型·自爆倒计时数字牌绘制（Ez8_Num.img 六字位）
// vt[144] 转发垫片 ·sub_4D8F90 后，仅 nArg2==1（绘制通道）且本体层号等于全局
//   dword_8F7C04 层号时：剩余 this[2150]−clock_now ≥500ms 则拆成 百分位/十分位/秒/分 五位
//   （·sub_418DD0 取字符图元 + ·sub_499690 以 x=-31/-16/-1/6/18、y=-63 与 1065353216(1.0f)
//   缩放逐位贴出）；<500ms 则按 150ms 周期闪烁（返回闪烁相位）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C29B0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 函数: 机器人二型·自爆倒计时数字牌绘制（Ez8_Num.img 六字位）
{
  int v7; // eax
  int v8; // ebx
  int fld_e2150; // ecx  | +0x2198 → 【推断】引信截止时刻（CNRobotEz8；va=005C2C00）
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v17; // [esp+1Ch] [ebp+10h]

  LOBYTE(v7) = sub_4D8F90(nArg2, nArg3, nArg4, nArg5);  // 调 vmt144 转发垫片（IRDActiveObject__vmt144 族）
  if ( (uint8_t)nArg2 == 1 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this);  // 调用虚函数（虚表槽 +376）
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);  // 调用虚函数（虚表槽 +376）
    if ( v8 == v7 )
    {
      fld_e2150 = *(this + 2150) - sub_699000((int)(this + 9));  // 【clock_now(clk)】
      v10 = 0;
      v17 = 0;
      if ( fld_e2150 >= 500 )
      {
        v10 = (fld_e2150 - 500) / 1000 % 100;
        v17 = (fld_e2150 - 500) % 1000 / 10;
LABEL_6:
        v11 = sub_418DD0(v10 / 10);  // 调 资源句柄 (101)
        sub_499690(dword_79C0B0, nArg3, nArg4, -31, -63, 0.0, v11, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 调 绘制基元包装（按标志翻转 X 偏移与缩放）
        v12 = sub_418DD0(v10 % 10);  // 调 资源句柄 (101)
        sub_499690(dword_79C0B0, nArg3, nArg4, -16, -63, 0.0, v12, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 调 绘制基元包装（按标志翻转 X 偏移与缩放）
        v13 = sub_418DD0(10);  // 调 资源句柄 (101)
        sub_499690(dword_79C0B0, nArg3, nArg4, -1, -63, 0.0, v13, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 调 绘制基元包装（按标志翻转 X 偏移与缩放）
        v14 = sub_418DD0(v17 / 10 + 11);  // 调 资源句柄 (101)
        sub_499690(dword_79C0B0, nArg3, nArg4, 6, -63, 0.0, v14, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 调 绘制基元包装（按标志翻转 X 偏移与缩放）
        v15 = sub_418DD0(v17 % 10 + 11);  // 调 资源句柄 (101)
        LOBYTE(v7) = sub_499690(dword_79C0B0, nArg3, nArg4, 18, -63, 0.0, v15, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 调 绘制基元包装（按标志翻转 X 偏移与缩放）
        return v7;
      }
      LOBYTE(v7) = fld_e2150 / 150 % 2 == 1;  // 调 取 16 位值低 8 位
      if ( fld_e2150 / 150 % 2 != 1 )
        goto LABEL_6;
    }
  }
  return v7;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C2BC0 sub_5C2BC0 —— 机器人二型·被绑定参数收货（ArgList==14）
// ArgList==14 时取参数对象首字段存 this[2156]（爆点挂载句柄），否则 ·sub_4E33D0 状态收尾。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5C2BC0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 机器人二型·被绑定参数收货（ArgList==14）
{
  uint32_t *result; // eax

  if ( ArgList != 14 )
    return (uint32_t *)sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  result = *(uint32_t **)(LODWORD(fArg3) + 4);  // 调 取 64 位值低 32 位
  *(this + 2156) = *result;  // this+8624 = uAI8624
  return result;
}



// 数据表读数 + RTTI cast（sub_47EF20; this+8352/8600/8604/8630 相位）
// ------------------------------------------------------------
// 0x5C2C00 sub_5C2C00 —— 机器人二型·属性重算与数据表读数（ROBOT_EX_02/Ez8 数值装配）
// ·sub_4DD8F0 属性块重算后，RTDynamicCast 把 this+8352 转为 CNGunner；vt+672(3) 取表条目：
//   +60×+74 与 +116×+130 乘积写 this+736/this+792 双精度槽（vt+676 提交）；
//   ·sub_47E720(2,28)/vt+1140(28) → ·sub_47EF20 得 this+8600（自爆倒计时基值）、
//   ·sub_47EFD0 得 this+8604 档位；数据表当前条目 v5[2371]==51 时 vt+1160(51) + ·sub_47E9D0 覆盖
//   8600 并置 8630=1、v5[2371]=-1（BOMB_READY 分支）；最后 8600 += 500 提前量。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2C00(int this, int nArg2, int nArg3)  // 函数: 机器人二型·属性重算与数据表读数（ROBOT_EX_02/Ez8 数值装配）
{
  int result; // eax
  uint32_t *v5; // esi
  int v6; // ebx
  uint64_t v7; // rax
  int v8; // ebx
  uint64_t v9; // rax
  char *v10; // ebx
  int v11; // eax
  uint32_t *v12; // eax
  int v13; // [esp+14h] [ebp+Ch]
  int v14; // [esp+14h] [ebp+Ch]
  int v15; // [esp+14h] [ebp+Ch]

  sub_4DD8F0((uint32_t *)this, nArg2, nArg3);  // 调 属性块整体重算（全量成长）
  result = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
             *(uint32_t *)(this + 8352),  // this+8352 骑乘/宿主槽
             0,
             &IRDActiveObject `RTTI Type Descriptor',
             &CNGunner `RTTI Type Descriptor',
             0);
  v5 = (uint32_t *)result;
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 672))(result, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    v13 = sub_41A5E0(v6 + 60);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    v7 = (uint64_t)((double)v13 * COERCE_FLOAT(sub_41A5E0(v6 + 74)));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(this + 736, SHIDWORD(v7), v7);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v5 + 672))(v5, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    v14 = sub_41A5E0(v8 + 116);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    v9 = (uint64_t)((double)v14 * COERCE_FLOAT(sub_41A5E0(v8 + 130)));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(this + 792, SHIDWORD(v9), v9);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
    v10 = (char *)sub_47E720(2, 28);  // 调 调 sub_47E720
    v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v5 + 1140))(v5, 28);  // 调用虚函数（虚表槽 +1140）
    *(uint32_t *)(this + 8600) = sub_47EF20(2, v15, -1, -1, 11);  // 调 读攻击数据表
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 388))(v5);  // 调用虚函数（虚表槽 +388）【推断: [RTTI: IRDActiveObject__vmt184 ·…】
    result = sub_47EFD0(v10, COERCE_FLOAT(1), v15, v11, v11, 0);
    *(uint32_t *)(this + 8604) = result;  // this+8604 子类 AI 状态槽/相位门
    if ( v5[2371] == 51 )
    {
      v12 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*v5 + 1160))(v5, 51);  // 调用虚函数（虚表槽 +1160）
      result = sub_47E9D0(v12, 0);  // 调 收招/结束例程
      *(uint32_t *)(this + 8600) = result;  // this+8600 子类 AI 状态字节 1
      v5[2371] = -1;
      *(uint8_t *)(this + 8630) = 1;  // this+8630 【推断】BOMB_READY 已播标志
    }
    *(uint32_t *)(this + 8600) += 500;  // this+8600 子类 AI 状态字节 1
  }
  return result;
}



// 自爆二型（121L）：ROBOT_EX_02 播报 + EarthQuake.ani 震地 + particle/Ez8_Boom.ptl
//   爆点（★高达梗: Ez8）
// ------------------------------------------------------------
// 0x5C2D60 sub_5C2D60 —— 机器人二型·自爆（ROBOT_EX_02 + EarthQuake.ani + Ez8_Boom.ptl）
// 与 ·0x5C24B0 同构（一型 Rx78）：this+8628==0 时一次性执行——播 ROBOT_EX_02；爆点取本体
//   vt+120/124/128（Z+30）；·sub_44B6C0 池 + ·sub_42FCB0(228) + ·sub_431860 载 EarthQuake.ani
//   震地挂宿主 this[29]；this[2155] 未占则 new(0x12C) + ·sub_4C3640 生成 particle/Ez8_Boom.ptl
//   （★高达梗 Ez8 爆点），vt+40 定位 + ·sub_4600B0 挂载；置 8628=1，存活时技能 40002 +
//   setState(14) + vt+108 隐至 (-10000,-10000)。差异：无 ±65 朝向偏移。
// ------------------------------------------------------------
void /*usercall*/ sub_5C2D60(int *pDwArg1@<ecx>, int nArg2@<edi>)  // 函数: 机器人二型·自爆（ROBOT_EX_02 + EarthQuake.ani + Ez8_Boom.ptl）
{
  int nY; // eax
  int pVt; // edx
  char *pQuakeFx; // edi
  int hAniQuake; // eax
  int pQuakeFxVt; // eax
  int pQuakeFxVt2; // ebx
  int nZ; // eax
  int nY2; // eax
  int nX2; // eax
  int *pBoomPtl; // eax
  int pBoomPtlVt; // edx
  void *pFxHost; // ecx
  int pVt2; // edx
  int nFaceDir; // eax
  char v17[4]; // [esp+8h] [ebp-40h] BYREF
  void *v18; // [esp+Ch] [ebp-3Ch]
  int v19; // [esp+10h] [ebp-38h]
  int v20; // [esp+14h] [ebp-34h]
  char v21[4]; // [esp+18h] [ebp-30h] BYREF
  void *Block; // [esp+1Ch] [ebp-2Ch]
  int v23; // [esp+20h] [ebp-28h]
  int v24; // [esp+24h] [ebp-24h]
  void *pResGate; // [esp+28h] [ebp-20h]
  char *pQuakeFx2; // [esp+2Ch] [ebp-1Ch]
  int nBlastX; // [esp+30h] [ebp-18h]
  int nBlastY; // [esp+34h] [ebp-14h]
  int nBlastZ; // [esp+38h] [ebp-10h]
  int v30; // [esp+44h] [ebp-4h]

  if ( *((uint8_t *)pDwArg1 + 8628) == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(pDwArg1, "ROBOT_EX_02", -1, 0, 0, nArg2);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
    nBlastX = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    nY = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);  // 调用虚函数（虚表槽 +124）
    pVt = *pDwArg1;
    nBlastY = nY;
    nBlastZ = (*(int (/*thiscall*/ **)(int *))(pVt + 128))(pDwArg1) + 30;  // 调用虚函数（虚表槽 +128）
    pQuakeFx = (char *)sub_44B6C0(284);  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
    pQuakeFx2 = pQuakeFx;
    v30 = 0;
    if ( pQuakeFx != nullptr )  // 若 pQuakeFx 有效（非空）
    {
      pResGate = (void *)sub_42FCB0(228);  // 调 CRT 一次性初始化
      LOBYTE(v30) = 1;  // 调 取 16 位值低 8 位
      if ( pResGate != nullptr )  // 若 pResGate 有效（非空）
        hAniQuake = sub_431860((char)"PassiveObject/Common/Animation/EarthQuake.ani", 1);  // 调 动画件构造（资源 id 版）
      else
        hAniQuake = 0;
      LOBYTE(v30) = 0;  // 调 取 16 位值低 8 位
      sub_44E0D0(pQuakeFx, hAniQuake, 1);  // 调 CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)pQuakeFx = &CNRDPooledObject::`vftable';  // vftable 复位
    }
    else
    {
      pQuakeFx = nullptr;
    }
    pQuakeFxVt = *(uint32_t *)pQuakeFx;
    v30 = -1;
    (*(void (/*thiscall*/ **)(char *, int))(pQuakeFxVt + 72))(pQuakeFx, 2);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    sub_45FE80(pDwArg1[29], (int)pQuakeFx, 2, 0, (int)pQuakeFx, (int)pDwArg1, 0);  // 调 对象注册
    pQuakeFxVt2 = *(uint32_t *)pQuakeFx;
    nZ = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调用虚函数（虚表槽 +128）
    nY2 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, nZ);  // 调用虚函数（虚表槽 +124）
    nX2 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY2 + 1);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    (*(void (/*thiscall*/ **)(char *, int))(pQuakeFxVt2 + 112))(pQuakeFx, nX2);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    if ( pDwArg1[2155] == 0 )
    {
      pResGate = operator new(0x12Cu);  // operator new 分配 300 字节
      v30 = 2;
      if ( pResGate != nullptr )  // 若 pResGate 有效（非空）
      {
        if ( (unsigned int)pDwArg1[96] < 0x10 )
          pBoomPtl = (int *)sub_4C3640(pDwArg1 + 91, "particle/Ez8_Boom.ptl", pDwArg1);  // 资源路径 particle/Ez8_Boom.ptl
        else
          pBoomPtl = (int *)sub_4C3640(pDwArg1[91], "particle/Ez8_Boom.ptl", pDwArg1);  // 资源路径 particle/Ez8_Boom.ptl
      }
      else
      {
        pBoomPtl = nullptr;
      }
      pDwArg1[2155] = (int)pBoomPtl;
      pBoomPtlVt = *pBoomPtl;
      v30 = -1;
      (*(void (/*thiscall*/ **)(int *, uint32_t))(pBoomPtlVt + 12))(pBoomPtl, 0);  // 调用虚函数（虚表槽 +12）
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2155] + 40))(pDwArg1[2155], nBlastX, nBlastY, nBlastZ);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pDwArg1[2155] + 92))(pDwArg1[2155], v21);  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
      pFxHost = (void *)pDwArg1[29];
      v30 = 3;
      sub_4600B0(pFxHost, 2, 0, (int)v21);  // 调 演播层注册(槽号)
      v30 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
      Block = nullptr;
      v23 = 0;
      v24 = 0;
    }
    pVt2 = *pDwArg1;
    *((uint8_t *)pDwArg1 + 8628) = 1;
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(pVt2 + 308))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    {
      nFaceDir = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      pDwArg1[2156] = sub_4E4A50(pDwArg1, 40002, pDwArg1[2151], nBlastX, nBlastY, nBlastZ, nFaceDir, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
      v18 = nullptr;
      v19 = 0;
      v20 = 0;
      v30 = 4;
      sub_431230((int)v17, pDwArg1 + 2156);  // 调 uint32 vector push_back
      (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 14, v17, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(*pDwArg1 + 108))(pDwArg1, -10000, -10000, 0);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
      if ( v18 != nullptr )  // 若 v18 有效（非空）
        j__free(v18);  // 调 堆释放
    }
  }
}


// 起爆倒计时：ROBOT_CLICK_LOOP + BOMB_READY_LOOP + ROBOT_CLICK_EX 播报（63L）
// ------------------------------------------------------------
// 0x5C2FE0 sub_5C2FE0 —— 机器人二型·引信点击音与起爆节拍（ROBOT_CLICK_LOOP/BOMB_READY_LOOP）
// this+8629==0 时首播 ROBOT_CLICK_LOOP(10)，若 8630（BOMB_READY 标志）非 0 再播
//   BOMB_READY_LOOP(9)，置 8629=1。
// 剩余 this+8600−clock_now(this+36)：>600ms 时用 1554 指向的 +0 帧槽、≤600ms 用 +4 帧槽
//   （vt+200 比较 + vt+196 切帧），并在 <600 段 vt+216 停 10（8630 时再停 9）+ 播 ROBOT_CLICK_EX；
// 剩余 ≤0 且 this+8624 为 0xFFFF 未引爆时 ·sub_5C2D60 引爆二型。
// ------------------------------------------------------------
void /*usercall*/ sub_5C2FE0(int pArg1@<ecx>, int nArg2@<edi>)  // 函数: 机器人二型·引信点击音与起爆节拍（ROBOT_CLICK_LOOP/BOMB_READY_LOOP）
{
  int v3; // ecx
  uint32_t *v4; // edi
  uint32_t *v5; // edi

  sub_4E1780((uint32_t *)pArg1);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( *(uint8_t *)(pArg1 + 8629) == 0 )  // pArg1+8629〔bClickLatch(推断)〕
  {
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      pArg1,
      "ROBOT_CLICK_LOOP",  // 资源/动画 TAG ROBOT_CLICK_LOOP
      10,
      0,
      0);
    if ( *(uint8_t *)(pArg1 + 8630) != 0 )  // pArg1+8630〔bBombReady(推断)〕
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        pArg1,
        "BOMB_READY_LOOP",  // 资源/动画 TAG BOMB_READY_LOOP
        9,
        0,
        0);
    *(uint8_t *)(pArg1 + 8629) = 1;  // pArg1+8629〔bClickLatch(推断)〕
  }
  v3 = *(uint32_t *)(pArg1 + 8600) - sub_699000(pArg1 + 36);  // 【clock_now(clk)】
  if ( v3 > 0 )
  {
    if ( v3 > 600 )
    {
      if ( v3 <= 5500 )
      {
        v5 = *(uint32_t **)(pArg1 + 6216);  // pArg1+6216〔pTbl6216(推断)〕
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) != *v5 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, **(uint32_t **)(pArg1 + 6216));  // 调用虚函数（虚表槽 +196）
      }
    }
    else
    {
      v4 = (uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4);  // pArg1+6216〔pTbl6216(推断)〕
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) != *v4 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pArg1 + 196))(  // 调用虚函数（虚表槽 +196）
          pArg1,
          *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4),
          nArg2);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 10);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
        if ( *(uint8_t *)(pArg1 + 8630) != 0 )  // pArg1+8630〔bBombReady(推断)〕
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, "ROBOT_CLICK_EX", -1, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      }
    }
  }
  else if ( *(uint32_t *)(pArg1 + 8624) == 0xFFFF )  // pArg1+8624〔uAI8624(推断)〕
  {
    sub_5C2D60((int *)pArg1, nArg2);  // 调 机器人二型·自爆（ROBOT_EX_02 + EarthQuake.ani + Ez8_Boom.ptl）
  }
}



// 子类扩展字段复位（this+8600..8652 全区, 25L）
// ------------------------------------------------------------
// 0x5C3100 sub_5C3100 —— 机器人二型·子类扩展字段全区复位（this+8600..8656）
// 逐槽清零 this+8600/8604/8612/8616/8620/8624/8628/8632/8636/8640/8644/8648/8652/8656，
//   其中 this+8608 例外置 1000（引信初始提前量，见 ·0x5C2C00 末尾 +500 的刻度基准）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3100(int this)  // 函数: 机器人二型·子类扩展字段全区复位（this+8600..8656）
{
  *(uint32_t *)(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
  *(uint32_t *)(this + 8604) = 0;  // this+8604 子类 AI 状态槽/相位门
  *(uint32_t *)(this + 8608) = 1000;  // this+8608 骑乘/骑手槽
  *(uint32_t *)(this + 8612) = 0;  // this+8612 锁定/相位字节 A
  *(uint32_t *)(this + 8616) = 0;  // this+8616 【推断】钻地相位字节1
  *(uint32_t *)(this + 8620) = 0;  // this+8620 相位双字节门
  *(uint32_t *)(this + 8624) = 0;  // this+8624 【推断】子类AI槽
  *(uint32_t *)(this + 8628) = 0;  // this+8628 【推断】指挥计时戳
  *(uint32_t *)(this + 8632) = 0;  // this+8632 【推断】子类 AI 资源/计数槽
  *(uint32_t *)(this + 8636) = 0;  // this+8636 【推断】传送/钻地相位槽
  *(uint32_t *)(this + 8640) = 0;  // this+8640 【推断】出土相位槽
  *(uint32_t *)(this + 8644) = 0;  // this+8644 【推断】相位计数槽
  *(uint8_t *)(this + 8648) = 0;  // this+8648 【推断】距离解算缓存
  *(uint32_t *)(this + 8652) = 0;  // this+8652 【推断】相位门字节
  *(uint32_t *)(this + 8656) = 0;  // this+8656 【推断】子类AI标记字节
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3170 sub_5C3170 —— 机器人二型·出土/挂载对象释放（this+8640 槽）
// 槽 this[2160] 非空时经其 vt[0](obj,1) 删除，随后槽清零（与 ·0x5C1FF0/·0x5C28A0 同构，
//   this[2160] 即 ·0x5C12B0 使用的出土相位/挂载槽）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3170(uint32_t *this)  // 函数: 机器人二型·出土/挂载对象释放（this+8640 槽）
{
  int (/*thiscall*/ ***fld_e2160)(uint32_t, int); // ecx
  int result; // eax

  fld_e2160 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2160);  // this+8640 = uCastSlot8640
  if ( fld_e2160 != nullptr )  // 若 fld_e2160 有效（非空）
    result = (**fld_e2160)(fld_e2160, 1);  // 调 fld_e2160 的虚函数（vt+0）
  *(this + 2160) = 0;  // this+8640 = uCastSlot8640
  return result;
}



// 时钟门 AI（sub_699000, 67L）
// ------------------------------------------------------------
// 0x5C31A0 sub_5C31A0 —— 机动炮怪·弹道发射节拍（Exs_Bullet 弹体）
// 取与目标 this+1813 的夹角（vt+168）写入角度槽 this+2163，>80 钳 80、<0 钳 0，尾段转弧度。
// 经 vt+308 玩家校验 + 时钟门 this+2151/+2152 冷却后，向 ·0x5C3760 预建的粒子弹体
//   *(this+2161) 写弹道：+76 角度、+0/+4/+8 弹着点（sin/cos*52 绕 vt+120/124/128 位姿，
//   纵轴带 ±5 随机抖动）、+84 朝向标志；·sub_4E4C10(this, 22016, …) 请求弹道效果并回写时钟。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C31A0(unsigned int *this)  // 函数: 机动炮怪·弹道发射节拍（Exs_Bullet 弹体）
{
  unsigned int result; // eax
  int nRand; // edi
  double v4; // st7
  double pThis_8732; // st7
  float pThis_873; // [esp+8h] [ebp-Ch]
  float v7; // [esp+Ch] [ebp-8h]
  float pThis_8733; // [esp+Ch] [ebp-8h]
  int nRand2; // [esp+10h] [ebp-4h]

  result = *(this + 1813);  // this+7252 = pTarget7252
  nRand = 0;
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v4 = ((double (/*thiscall*/ *)(unsigned int *, unsigned int, uint32_t))*(uint32_t *)(*this + 168))(this, result, 0);  // 调用虚函数（虚表槽 +168）【推断: 与目标俯仰角（z 轴）】
    *((float *)this + 2163) = v4;  // this+8652 = 相位槽
    if ( v4 > 80.0 )
      *(this + 2163) = 1117782016;  // this+8652 = 相位槽
    if ( *((float *)this + 2163) < 0.0 )  // this+8652 = 相位槽
      *(this + 2163) = 0;  // this+8652 = 相位槽
    result = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    if ( (uint8_t)result != 0 )
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( *(this + 2151) + *(this + 2152) < result )  // this+8604 = bAI8604
      {
        *(uint32_t *)(*(this + 2161) + 76) = (uint64_t)*((float *)this + 2163);  // this+8652 = 相位槽
        nRand2 = 0;
        if ( *(uint32_t *)(*(this + 2161) + 76) == 0 )  // this+8644 = 相位槽
        {
          nRand = rand() % 10 - 5;  // 调 以 16 位种子状态递推并返回 15 位结果
          nRand2 = rand() % 10 - 5;  // 调 以 16 位种子状态递推并返回 15 位结果
        }
        if ( (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this) != 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        {
          pThis_873 = sub_405400((uint64_t)*((float *)this + 2163)) * 52.0;  // 调 cos 查表（dword_79D154 表，角度 %360 归一含负角修正）
          pThis_8732 = (double)(*(int (/*thiscall*/ **)(unsigned int *))(*this + 120))(this) + pThis_873;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        }
        else
        {
          v7 = (float)(*(int (/*thiscall*/ **)(unsigned int *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          pThis_8732 = v7 - sub_405400((uint64_t)*((float *)this + 2163)) * 52.0;  // 调 cos 查表（dword_79D154 表，角度 %360 归一含负角修正）
        }
        *(uint32_t *)*(this + 2161) = (uint64_t)pThis_8732;  // this+8644 = 相位槽
        *(uint32_t *)(*(this + 2161) + 4) = nRand + (*(int (/*thiscall*/ **)(unsigned int *))(*this + 124))(this);  // this+8644 = 相位槽
        pThis_8733 = sub_4053E0((uint64_t)*((float *)this + 2163)) * 52.0;  // 调 sin 查表（dword_79D150 表，角度 %360 归一含负角修正）
        *(uint32_t *)(*(this + 2161) + 8) = (uint64_t)((double)((*(int (/*thiscall*/ **)(unsigned int *))(*this + 128))(this)  // this+8644 = 相位槽
                                                                    + 60)
                                                           + pThis_8733
                                                           + (double)nRand2);
        *(uint8_t *)(*(this + 2161) + 84) = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this) != 1;  // this+8644 = 相位槽
        sub_4E4C10(this, 22016, *(this + 2154), *(this + 2161), 0, 0, 0, 0);  // 调 与 ·0x4E4A50 同构（差异：上下文使能位固定 1 + 数据块打包）
        result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
        *(this + 2151) = result;  // this+8604 = bAI8604
      }
    }
    *((float *)this + 2163) = *((float *)this + 2163) * 0.017453289;  // this+8652 = 相位槽
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C33B0 sub_5C33B0 —— 条件字节迁移（this+2155==4 时才改写）
// 仅当 this+2155==4（与反应态 4=受击后置 同值【推断】）时改写为 nArg2，
//   并经 ·sub_498F00（vmt90）同步动画对象 +52 条件字节。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C33B0(uint32_t *this, int nArg2)  // 函数: 条件字节迁移（this+2155==4 时才改写）
{
  int result; // eax

  if ( *(this + 2155) == 4 )  // this+8620 = uAI8620
  {
    *(this + 2155) = nArg2;  // this+8620 = uAI8620
    return sub_498F00(nArg2);  // 调 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查）
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C33D0 sub_5C33D0 —— 双动画对象播放驱动（大状态分派）
// 先 ·sub_4D54E0 基类帧步进；按 vt+840 大状态：==5 驱动 this+2158 对象（帧游标 -1 时
//   ·sub_4938F0 重播、+88 归零）、==8/==3 驱动 this+2157 对象（+88 写 this+2163 速率）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5C33D0(int *this)  // 函数: 双动画对象播放驱动（大状态分派）
{
  uint32_t *result; // eax
  int fld_e2158; // esi  | +0x21B8 → 【推断】动作/状态号槽 C（CNRobotExs；va=005C3100）
  int fld_e2157; // edi  | +0x21B4 → 【推断】动作/状态号槽 B（CNRobotExs；va=005C3100）

  sub_4D54E0(this);  // 调 受击包后：+1639==10 主状态镜像 且 +1953==0/+1954==15
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 5 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    result = sub_4938F0(*(this + 2158));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    fld_e2158 = *(this + 2158);  // this+8632〔bDevourFlag(推断)〕
    if ( *(uint32_t *)(fld_e2158 + 148) == -1 )
      result = sub_4938F0(fld_e2158);  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    *(uint32_t *)(fld_e2158 + 88) = 0;
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
         || (result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 840))(this)) == (uint32_t *)3 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    result = sub_4938F0(*(this + 2157));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    fld_e2157 = *(this + 2157);  // this+8628 = 指挥计时戳
    if ( *(uint32_t *)(fld_e2157 + 148) == -1 )
      result = sub_4938F0(*(this + 2157));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    *(uint32_t *)(fld_e2157 + 88) = *(this + 2163);  // this+8652 = 相位槽
  }
  return result;
}



// 数据表读数 + RTTI cast（sub_47EF20, 69L）
// ------------------------------------------------------------
// 0x5C3460 sub_5C3460 —— 属性块整体重算 + 机动炮怪成长修正
// 先转 ·sub_4DD8F0 全量属性重算；再把 this+2088 动态转型为 CNGunner（RTTI 直证）：
//   经 vt+672(3) 取属性块，用 ·sub_41A5E0 组装 this+184 / this+198 两组双精度值。
// 经 ·sub_47E720(2,29) + vt+1140 读表，·sub_47EFD0 生成 this+2164/2154 两个粒子族，
//   ·sub_47EF20(2,·)/·sub_47EF20(4,·) 得冷却阈值 this+2152 与 this+2150（this+2151=-this+2152）。
// 若 vt+792(8) 子对象（+4 类型 32241/32267）存在，则两粒子族增益 1.25 倍。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3460(int *this, int nArg2, int nArg3)  // 函数: 属性块整体重算 + 机动炮怪成长修正
{
  uint64_t pObj2; // rax
  int pObj; // esi
  int v6; // ebx
  uint64_t v7; // rax
  int v8; // ebx
  uint64_t v9; // rax
  char *v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int pObj3; // esi
  double fld_e2154; // st7  | +0x21A8 → 【推断】子类 AI 状态槽〔5C3100 清零（无其他读点）〕（CNRobotExs；va=005C3100）
  int v17; // [esp+14h] [ebp+Ch]
  int v18; // [esp+14h] [ebp+Ch]
  int v19; // [esp+14h] [ebp+Ch]

  sub_4DD8F0(this, nArg2, nArg3);  // 调 属性块整体重算（全量成长）
  LODWORD(pObj2) = __RTDynamicCast(  // 调 取 64 位值低 32 位
                  *(this + 2088),  // this+8352 = 骑乘/宿主槽
                  0,
                  &IRDActiveObject `RTTI Type Descriptor',
                  &CNGunner `RTTI Type Descriptor',
                  0);
  pObj = pObj2;
  if ( (uint32_t)pObj2 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pObj2 + 672))(pObj2, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    v17 = sub_41A5E0(v6 + 60);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    v7 = (uint64_t)((double)v17 * COERCE_FLOAT(sub_41A5E0(v6 + 74)));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590((unsigned int)(this + 184), SHIDWORD(v7), v7);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    v18 = sub_41A5E0(v8 + 116);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    v9 = (uint64_t)((double)v18 * COERCE_FLOAT(sub_41A5E0(v8 + 130)));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590((unsigned int)(this + 198), SHIDWORD(v9), v9);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
    v10 = (char *)sub_47E720(2, 29);  // 调 调 sub_47E720
    v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, 29);  // 调用虚函数（虚表槽 +1140）
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);  // 调用虚函数（虚表槽 +388）【推断: [RTTI: IRDActiveObject__vmt184 ·…】
    *(this + 2164) = sub_47EFD0(v10, COERCE_FLOAT(3), v19, v11, v11, 0);  // this+8656 = 事件 16/17 配对槽
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);  // 调用虚函数（虚表槽 +388）【推断: [RTTI: IRDActiveObject__vmt184 ·…】
    *(this + 2154) = sub_47EFD0(v10, COERCE_FLOAT(1), v19, v12, v12, 0);  // this+8616 = uAI8616
    v13 = sub_47EF20(2, v19, -1, -1, 11);  // 调 读攻击数据表
    *(this + 2152) = v13;  // this+8608 = uAI8608
    *(this + 2151) = -v13;  // this+8604 = bAI8604
    *(this + 2150) = sub_47EF20(4, v19, -1, -1, 11);  // this+8600 = uAI8600
    LODWORD(pObj2) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 792))(pObj, 8);  // 调用虚函数（虚表槽 +792）
    pObj3 = pObj2;
    if ( (uint32_t)pObj2 != 0 )
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj2 + 16))(pObj2) + 4) == 32241  // 调用虚函数（虚表槽 +16）
        || (LODWORD(pObj2) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 16))(pObj3), *(uint32_t *)(pObj2 + 4) == 32267) )  // 调用虚函数（虚表槽 +16）
      {
        fld_e2154 = (double)*(this + 2154);  // this+8616 = uAI8616
        *(this + 2164) = (uint64_t)((double)*(this + 2164) * 1.25);  // this+8656 = 事件 16/17 配对槽
        pObj2 = (uint64_t)(fld_e2154 * 1.25);
        *(this + 2154) = pObj2;  // this+8616 = uAI8616
      }
    }
  }
  return pObj2;
}



// 时钟门 AI（sub_699000, 68L）
// ------------------------------------------------------------
// 0x5C3630 sub_5C3630 —— 主 AI 节拍：濒死闪光/零距门 → 姿态切换
// ·sub_4E1780 基类步进；时钟距 this+2150 阈值 ≤1500ms 时用 ·sub_42B420 取 50..255 呼吸通道值，
//   对本体（this+30）与链表族（this+32）逐个 ·sub_491690 泛红染色（0xFF0000FF + alpha 高字节）。
// 大状态 8 时走 ·0x5C31A0 弹道节拍，且目标 this+1813 失效 + vt+308 玩家校验通过则 vt+560 setState(0) 归位；
//   其余状态时钟超阈后 vt+736 姿态查询 >0 则 vt+728 切状态 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3630(uint32_t *this)  // 函数: 主 AI 节拍：濒死闪光/零距门 → 姿态切换
{
  int pThis_9; // eax
  uint8_t v3; // al
  uint8_t v4; // bl
  uint32_t **fld_e32; // eax
  uint32_t *v6; // edi
  int v7; // ebx
  int result; // eax

  sub_4E1780(this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (unsigned int)(*(this + 2150) - sub_699000((int)(this + 9))) <= 0x5DC )  // 【clock_now(clk)】
  {
    pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    v3 = sub_42B420(50, 255, pThis_9, 250);  // 调 往返插值（三角波）
    v4 = v3;
    if ( *(this + 30) != 0 )  // this+120 = 动画对象指针
      sub_491690(1, 2, 1, -16776961, (v3 << 24) | 0xFFFFFF, 1);  // 调 图层后处理配置（this+176..196 图层参数块写入）
    fld_e32 = (uint32_t **)*(this + 32);  // this+32 格子像素尺寸
    v6 = *fld_e32;
    if ( *fld_e32 != fld_e32 )
    {
      v7 = (v4 << 24) | 0xFFFFFF;
      do
      {
        sub_491690(1, 2, 1, -16776961, v7, 1);  // 调 图层后处理配置（this+176..196 图层参数块写入）
        v6 = (uint32_t *)*v6;
      }
      while ( v6 != (uint32_t *)*(this + 32) );  // this+32 格子像素尺寸
    }
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    sub_5C31A0(this);  // 调 机动炮怪·弹道发射节拍（Exs_Bullet 弹体）
    result = *(this + 1813);  // this+7252 = pTarget7252
    if ( result == 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    if ( result != 5 )
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( (unsigned int)result >= *(this + 2150) )  // this+8600 = uAI8600
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        if ( (uint8_t)result != 0 )
        {
          result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
          if ( result > 0 )
            return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t))(*this + 728))(this, 0, 1, 0);  // 调用虚函数（虚表槽 +728）【推断: ★★ HP setter / DMGAPPLY vt+728（研…】
        }
      }
    }
  }
  return result;
}



// 自爆子弹：引用 Particle/Exs_Bullet.ptl（this+8648 相位）
// ------------------------------------------------------------
// 0x5C3760 sub_5C3760 —— 机动炮怪初始化：载入 Exs_Bullet 弹体资源
// 从 this+1554 持有的对象[2..5] 抄出 this+2156/2157/2158/2159 四槽状态号；
// 经 vt+588（.equ 挂装）载入 Particle/Exs_Bullet.ptl 存 this+2161，帧槽 this+2153=-1、
//   锁存字节 +8648 与角度槽 this+2163 归零。字符串实证弹体粒子。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3760(uint32_t *this)  // 函数: 机动炮怪初始化：载入 Exs_Bullet 弹体资源
{
  uint32_t *fld_e1554; // eax
  int v3; // edx
  int v4; // eax

  fld_e1554 = (uint32_t *)*(this + 1554);  // this+6216 = 资源/帧游标表
  *(this + 2156) = fld_e1554[3];  // this+8624 = uAI8624
  *(this + 2157) = fld_e1554[4];  // this+8628 = 指挥计时戳
  *(this + 2158) = fld_e1554[2];  // this+8632〔bDevourFlag(推断)〕
  v3 = fld_e1554[5];
  v4 = *this;
  *(this + 2159) = v3;  // this+8636 = pDollTarget
  *(this + 2161) = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(v4 + 588))(this, "Particle/Exs_Bullet.ptl");  // this+8644 = 相位槽
  *(this + 2153) = -1;  // this+8612 = uAI8612
  *((uint8_t *)this + 8648) = 0;  // this+8648 = 相位/缓存槽
  *(this + 2163) = 0;  // this+8652 = 相位槽
  return 0;
}



// 自爆炸点：引用 particle/EXS_Boom.ptl（65L）
// ------------------------------------------------------------
// 0x5C37C0 sub_5C37C0 —— 机动炮怪自爆：EXS_Boom 爆点 + 40002 号效果
// 首次调用（this+2160 空）new 0x12C 字节粒子对象并 ·sub_4C3640 绑定 particle/EXS_Boom.ptl
//   （this+96 判长串以取 this+91 内联缓冲或堆指针），vt+12 复位后 vt+40 定位到本体
//   vt+120/124/128（高度 +30），vt+92 取包围盒，·sub_4600B0(fld_e29,2,…) 登记特效。
// 尾段 vt+308 玩家校验通过则 ·sub_4E4A50(this, 40002, this+2164, 位姿…, vt+152 朝向) 请求效果。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C37C0(uint32_t *this)  // 函数: 机动炮怪自爆：EXS_Boom 爆点 + 40002 号效果
{
  int v2; // ebx
  int v3; // edi
  int *pThis_5B; // eax
  int v5; // edx
  void *fld_e29; // ecx
  int result; // eax
  int v8; // eax
  uint8_t v9[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  int v11; // [esp+14h] [ebp-1Ch]
  int v12; // [esp+18h] [ebp-18h]
  void *pMem; // [esp+1Ch] [ebp-14h]
  int v14; // [esp+20h] [ebp-10h]
  int v15; // [esp+2Ch] [ebp-4h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) + 30;  // 调用虚函数（虚表槽 +128）
  if ( *(this + 2160) == 0 )  // this+8640 = uCastSlot8640
  {
    pMem = operator new(0x12Cu);  // operator new 分配 300 字节
    v15 = 0;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
    {
      if ( *(this + 96) < 0x10u )  // this+384 = 动画件名 SSO 容量判据
        pThis_5B = (int *)sub_4C3640(this + 91, "particle/EXS_Boom.ptl", this);  // 资源路径 particle/EXS_Boom.ptl
      else
        pThis_5B = (int *)sub_4C3640(*(this + 91), "particle/EXS_Boom.ptl", this);  // this+364 = 动画件名缓冲 SSO 内联首址
    }
    else
    {
      pThis_5B = nullptr;
    }
    *(this + 2160) = pThis_5B;  // this+8640 = uCastSlot8640
    v5 = *pThis_5B;
    v15 = -1;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v5 + 12))(pThis_5B, 0);  // 调用虚函数（虚表槽 +12）
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2160) + 40))(*(this + 2160), v2, v14, v3);  // this+8640 = uCastSlot8640
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2160) + 92))(*(this + 2160), v9);  // this+8640 = uCastSlot8640
    fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
    v15 = 1;
    sub_4600B0(fld_e29, 2, 0, (int)v9);  // 调 演播层注册(槽号)
    v15 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
    Block = nullptr;
    v11 = 0;
    v12 = 0;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    return sub_4E4A50(this, 40002, *(this + 2164), v2, v14, v3, v8, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
  }
  return result;
}



// 时钟门 AI（sub_699000; this+204/+208 硬直联动）
// ------------------------------------------------------------
// 0x5C3920 sub_5C3920 —— 自爆状态机：切换态驱动 + 帧游标复位
// ·sub_4E33D0 状态收尾后，把 this+2156/2157/2159 三套动作号写入 vt+208 帧槽；
// 按 ArgList：5 → vt+204(-100, this+2158) 定位并转 ·0x5C37C0 播爆点；8 → ·sub_4926A0(this+2157)
//   复位帧游标 + vt+204 定位 + 记录时钟到 this+2153；0 → 速率槽 this+2163 归零 + ·sub_4926A0(this+2156)；
//   3/9 → ·sub_4926A0(this+2159) 复位后同法定位。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3920(int *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 自爆状态机：切换态驱动 + 帧游标复位
{
  int result; // eax
  int fld_e2156; // ecx  | +0x21B0 → 【推断】动作/状态号槽 A（CNRobotExs；va=005C3100）
  int fld_e21562; // eax

  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2156));  // this+8624 = uAI8624
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2157));  // this+8628 = 指挥计时戳
  result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2159));  // this+8636 = pDollTarget
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -100,
        *(this + 2158),  // this+8632〔bDevourFlag(推断)〕
        0,
        -60,
        0,
        0);
      return sub_5C37C0(this);  // 调 机动炮怪自爆：EXS_Boom 爆点 + 40002 号效果
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      sub_4926A0(*(this + 2157));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -100,
        *(this + 2157),  // this+8628 = 指挥计时戳
        0,
        -60,
        0,
        0);
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      *(this + 2153) = result;  // this+8612 = uAI8612
      return result;
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      fld_e2156 = *(this + 2156);  // this+8624 = uAI8624
      *(this + 2163) = 0;  // this+8652 = 相位槽
      sub_4926A0(fld_e2156);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      fld_e21562 = *(this + 2156);  // this+8624 = uAI8624
      return (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, int, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
               this,
               -100,
               fld_e21562,
               0,
               -60,
               0,
               0);
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      sub_4926A0(*(this + 2159));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      fld_e21562 = *(this + 2159);  // this+8636 = pDollTarget
      return (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, int, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
               this,
               -100,
               fld_e21562,
               0,
               -60,
               0,
               0);
    default:
      break;
  }
  return result;
}



// ============================================================
// 【分区 3】树精（Dendroid）（0x5C3A30-0x5C6190）
// 证据：DENDROID_SPIT/ATK/SWISH_01/02/DRIVE_01/01_LOOP、R_DENDROID_DMG + DENDROID_DIE、
//       Particle/Seed.ptl 种子弹、BEFORE_THUNDER 蓄雷、TRAP_OCTOPUS_TIGHTEN 缠绕（复用）、
//       Monster/Dendroid/CommonAni/{GrabAttack,Grab}.ani 抓取

// 子类扩展字段复位（this+8600..8656）
// ------------------------------------------------------------
// 0x5C3A30 sub_5C3A30 —— 子类扩展字段整块复位（this+8600..8664）
// 清 8600/8604/8608/8612/8620/8624/8648/8640 为 0，8616/8644/8652 置 -1（无索引哨兵），
//   this+8656/8660/8664 三元组（疑为坐标或向量缓存【推断】）清零。返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3A30(int this)  // 函数: 子类扩展字段整块复位（this+8600..8664）
{
  uint32_t *pThis_21D0; // ecx

  *(uint32_t *)(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
  *(uint32_t *)(this + 8604) = 0;  // this+8604 动作号快照A
  *(uint32_t *)(this + 8608) = 0;  // this+8608 动作号快照B
  *(uint32_t *)(this + 8612) = 0;  // this+8612 动作号快照C
  *(uint32_t *)(this + 8616) = -1;  // this+8616 【推断】钻地相位字节1
  *(uint32_t *)(this + 8620) = 0;  // this+8620 相位双字节门
  *(uint32_t *)(this + 8624) = 0;  // this+8624 【推断】子类AI槽
  *(uint32_t *)(this + 8648) = 0;  // this+8648 【推断】距离解算缓存
  *(uint8_t *)(this + 8640) = 0;  // this+8640 【推断】出土相位槽
  *(uint32_t *)(this + 8644) = -1;  // this+8644 【推断】相位计数槽
  *(uint32_t *)(this + 8652) = -1;  // this+8652 【推断】相位门字节
  pThis_21D0 = (uint32_t *)(this + 8656);  // this+8656 【推断】子类AI标记字节
  *pThis_21D0 = 0;
  pThis_21D0[1] = 0;
  pThis_21D0[2] = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C3A90 sub_5C3A90 —— 树精承伤修正：类型过滤 + 档位减伤 25%
// ·sub_4DC390 类型过滤返回 3 时原样放行；否则经 vt+348 取攻击方档位，
//   若 vt+576 判定成立【推断】则将伤害量 *pDwArg1 乘 0.75 并返回 0，否则回传过滤码。
// ------------------------------------------------------------
int /*stdcall*/ sub_5C3A90(int *pDwArg1, int nArg2)  // 函数: 树精承伤修正：类型过滤 + 档位减伤 25%
{
  int result; // eax
  int v3; // esi

  result = sub_4DC390(pDwArg1, nArg2);  // 调 伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
  v3 = result;
  if ( result != 3 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // 调用虚函数（虚表槽 +348）
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )  // 调用虚函数（虚表槽 +576）
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.75);
      return 0;
    }
    else
    {
      return v3;
    }
  }
  return result;
}



// 主状态门（this+200/8640）
// ------------------------------------------------------------
// 0x5C3AF0 sub_5C3AF0 —— 玩家校验后向目标锚点一次性贴合（this+8640 锁存）
// vt+308 玩家校验 + this+1813 目标存在 + 目标 vt+200 对象的 +148 档位 ≥3 + this+8640 未置位时：
//   以 this+2167 为参数经目标 vt+124/vt+120 逐级换算，并用本体 vt+152(this,150,1,0,0) 求高度，
//   结果经 vt+584 位置写入回填自机；随后 this+8640=1 锁存，保证只贴合一次。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C3AF0(int *this)  // 函数: 玩家校验后向目标锚点一次性贴合（this+8640 锁存）
{
  int fld_e1813; // eax  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int v3; // ebx
  int fld_e18132; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int v5; // eax
  int fld_e2167; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax

  LOBYTE(fld_e1813) = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)fld_e1813 != 0 )
  {
    fld_e1813 = *(this + 1813);  // this+7252 = pTarget7252
    if ( fld_e1813 != 0 )
    {
      fld_e1813 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      if ( *(int *)(fld_e1813 + 148) >= 3 )
      {
        LOBYTE(fld_e1813) = *((uint8_t *)this + 8640);  // this+8640 = uCastSlot8640
        if ( (uint8_t)fld_e1813 == 0 )
        {
          v3 = *this;
          fld_e18132 = *(this + 1813);  // this+7252 = pTarget7252
          v5 = (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(*this + 152))(this, 150, 1, 0, 0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          fld_e2167 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)fld_e18132 + 124))(  // 调用虚函数（虚表槽 +124）
                 fld_e18132,
                 *(this + 2167),  // this+8668 = nCool8668
                 0,
                 0,
                 v5);
          v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e18132 + 120))(fld_e18132, fld_e2167);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          v8 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)fld_e18132 + 124))(fld_e18132, 0, v7);  // 调用虚函数（虚表槽 +124）
          v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e18132 + 120))(fld_e18132, v8);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          LOBYTE(fld_e1813) = (*(int (/*thiscall*/ **)(int *, int))(v3 + 584))(this, v9);  // 调用虚函数（虚表槽 +584）【推断: ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6…】
          *((uint8_t *)this + 8640) = 1;  // this+8640 = uCastSlot8640
        }
      }
    }
  }
  return fld_e1813;  // | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3BA0 sub_5C3BA0 —— 占用槽读取：this+2150 非 0 直返，否则取基类值
// 另有 ·sub_4DA1D0 兜底调用（this+2150 为 0 时）。this+2150 疑为抓取/骑乘占用槽【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3BA0(int *this)  // 函数: 占用槽读取：this+2150 非 0 直返，否则取基类值
{
  int result; // eax

  result = *(this + 2150);  // this+8600 = uAI8600
  if ( result == 0 )
    return sub_4DA1D0();
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3BB0 sub_5C3BB0 —— 与 ·sub_5C3BA0 同构（差异：转调 ·sub_4D9210(nArg2,nArg3,nArg4)）
// this+2150 非 0 时返回 0 拦截，否则转发基类三参实现。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C3BB0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 与 ·sub_5C3BA0 同构（差异：转调 ·sub_4D9210(nArg2,nArg3,nArg4)）
{
  if ( *(this + 2150) != 0 )  // this+8600 = uAI8600
    return 0;
  else
    return sub_4D9210(nArg2, nArg3, nArg4);  // 调 原查询【推断：8624 为反应接管标志】
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3BD0 sub_5C3BD0 —— 与 ·sub_5C3BA0 同构（差异：单参转调 ·sub_4D9200(nArg2)）
// this+2150 非 0 时返回 0 拦截，否则转发基类单参实现。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C3BD0(uint32_t *this, int nArg2)  // 函数: 与 ·sub_5C3BA0 同构（差异：单参转调 ·sub_4D9200(nArg2)）
{
  if ( *(this + 2150) != 0 )  // this+8600 = uAI8600
    return 0;
  else
    return sub_4D9200(nArg2);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3BF0 sub_5C3BF0 —— 与 ·sub_5C3BA0 同构（差异：转调 ·sub_4D8750 朝向决策）
// this+2150 非 0 时直返，否则以参照对象 vt+1813 的 x 比较决定朝向。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3BF0(int *this)  // 函数: 与 ·sub_5C3BA0 同构（差异：转调 ·sub_4D8750 朝向决策）
{
  int result; // eax

  result = *(this + 2150);  // this+8600 = uAI8600
  if ( result == 0 )
    return sub_4D8750(this);  // 调 朝向决策（依据参照对象 vt+1813 的 x 比较得方向码 0/4）
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3C00 sub_5C3C00 —— 与 ·sub_5C3BA0 同构（差异：转调 ·sub_498F00 条件字节写）
// this+2150 非 0 时直返，否则经动画对象 +52 设置条件字节（vmt90）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3C00(uint32_t *this, int nArg2)  // 函数: 与 ·sub_5C3BA0 同构（差异：转调 ·sub_498F00 条件字节写）
{
  int result; // eax

  result = *(this + 2150);  // this+8600 = uAI8600
  if ( result == 0 )
    return sub_498F00(nArg2);  // 调 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查）
  return result;
}



// AI 相位辅助（76L）
// ------------------------------------------------------------
// 0x5C3C20 sub_5C3C20 —— 树精藤鞭/触须锚点定位（this+2154 模式分派）
// 模式 1：从 this+2155 对象 vt+128 取锚点高度，经本体 vt+124/vt+120 反算后写回该对象 vt+112。
// 模式 2：以 345/258/232/283/313 分段表按目标 vt+200 的 +148 档位（pThis_94）索引取偏移，
//   朝向（vt+152==0）决定正负号；对每段 185 纵轴偏移，经本体 vt+124/vt+120 换算后写回 vt+112。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3C20(int *this)  // 函数: 树精藤鞭/触须锚点定位（this+2154 模式分派）
{
  int result; // eax
  int fld_e2155; // ebx
  int fld_e21552; // edi
  int nAnchorZ; // eax
  int nAnchorY2; // eax
  int nAnchorX2; // eax
  int pVt; // eax
  int pThis_94; // edi
  bool bFaceLeft; // zf
  int nSegBase; // eax
  int nOffX; // edi
  int fld_e21553; // ebx
  int nOffY; // eax
  int nOffX2; // eax
  uint32_t aSegTbl[2]; // [esp+Ch] [ebp-60h]
  uint32_t aJointTbl[22]; // [esp+14h] [ebp-58h]

  result = *(this + 2154);  // this+8616 = uAI8616
  if ( result == 1 )
  {
    fld_e2155 = *(uint32_t *)*(this + 2155);  // this+8620 = uAI8620
    fld_e21552 = *(this + 2155);  // this+8620 = uAI8620
    nAnchorZ = (*(int (**)(void))(fld_e2155 + 128))();  // 调用虚函数（虚表槽 +128）
    nAnchorY2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nAnchorZ);  // 调用虚函数（虚表槽 +124）
    nAnchorX2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21552 + 120))(fld_e21552, nAnchorY2 - 1);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e2155 + 112))(*(this + 2155), nAnchorX2);  // this+8620 = uAI8620
  }
  else if ( result == 2 )
  {
    aSegTbl[1] = 0;
    aJointTbl[0] = 0;
    aJointTbl[2] = 0;
    aJointTbl[5] = 0;
    aJointTbl[6] = 185;
    aJointTbl[8] = 0;
    aJointTbl[11] = 0;
    aJointTbl[12] = 185;
    aJointTbl[14] = 0;
    aJointTbl[17] = 0;
    aJointTbl[18] = 185;
    aJointTbl[20] = 0;
    aJointTbl[21] = 0;
    pVt = *this;
    aSegTbl[0] = 345;
    aJointTbl[1] = 258;
    aJointTbl[3] = 232;
    aJointTbl[4] = 283;
    aJointTbl[7] = 258;
    aJointTbl[9] = 232;
    aJointTbl[10] = 283;
    aJointTbl[13] = 258;
    aJointTbl[15] = 232;
    aJointTbl[16] = 283;
    aJointTbl[19] = 313;
    pThis_94 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(pVt + 200))(this) + 148);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    bFaceLeft = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    nSegBase = 3 * pThis_94;
    if ( bFaceLeft )
      nOffX = -aSegTbl[3 * pThis_94];
    else
      nOffX = aSegTbl[3 * pThis_94];
    fld_e21553 = *(uint32_t *)*(this + 2155);  // this+8620 = uAI8620
    nOffY = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, aJointTbl[nSegBase]);  // 调用虚函数（虚表槽 +124）
    nOffX2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nOffY - 1);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e21553 + 112))(*(this + 2155), nOffX + nOffX2);  // this+8620 = uAI8620
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C3D40 sub_5C3D40 —— 树精转向贴近/绑定决策（大状态 0 门控）
// 需 this+2150 占用槽非 0 + vt+308 玩家校验 + vt+840 大状态==0 + 目标 this+1813 存在。
// 强制参数 pszArg3 非 0，或朝向 vt+152==0 时本体 x 小于目标 x，或朝向==1 时
//   rand()%300 < nArg2，任一成立即 vt+560 setState(17) 转绑定态（贴身位移）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3D40(int *this, int nArg2, char pszArg3)  // 函数: 树精转向贴近/绑定决策（大状态 0 门控）
{
  int result; // eax
  int fld_e1813; // edi
  int fld_e18132; // edi
  int nRand; // eax
  int v8; // et2

  result = *(this + 2150);  // this+8600 = uAI8600
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      if ( result == 0 )
      {
        result = *(this + 1813);  // this+7252 = pTarget7252
        if ( result != 0 )  // 若结果非 0（成功）
        {
          if ( pszArg3 != 0 )
          {
            return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 17, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
          }
          else
          {
            if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            {
              fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252 = pTarget7252
              if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < fld_e1813 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
                return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 17, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
            }
            result = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            if ( result == 1 )
            {
              fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252 = pTarget7252
              result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              if ( result >= fld_e18132 )
              {
                nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
                v8 = nRand % 300;
                result = nRand / 300;
                if ( v8 < nArg2 )
                  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 17, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
              }
            }
          }
        }
      }
    }
  }
  return result;
}



// 种子弹技能：DENDROID_SPIT 播报 + Particle/Seed.ptl（this+200/8640/8685 相位）
// ------------------------------------------------------------
// 0x5C3E20 sub_5C3E20 —— 种子散射：DENDROID_SPIT 播报 + Particle/Seed.ptl 多发
// 目标档位 ≥4 且 this+8685 未播报时经 vt+212 播 DENDROID_SPIT 语音并置位；
//   档位 ≥6 且 this+8640 未触发 + vt+308 玩家校验通过时，载入 Particle/Seed.ptl（vt+588）
//   复制 0x62 字节模板，随机 4-8 发，每发扰动 v8[18..20] 与 v8[17] 后经 vt+580 发射（id 112）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C3E20(uint8_t *this)  // 函数: 种子散射：DENDROID_SPIT 播报 + Particle/Seed.ptl 多发
{
  int *pThis_C8; // eax
  int nRand3; // esi
  int nRand2; // eax
  int v5; // edx
  int nRand; // [esp+4h] [ebp-6Ch]
  uint32_t v8[26]; // [esp+8h] [ebp-68h] BYREF

  v8[25] = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  if ( *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148) >= 4 && *(this + 8685) == 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      this,
      "DENDROID_SPIT",  // 资源/动画 TAG DENDROID_SPIT
      -1,
      0,
      0);
    *(this + 8685) = 1;  // this+8685 【推断】挥击/散射语音锁存
  }
  pThis_C8 = (int *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  if ( pThis_C8[37] >= 6 )
  {
    LOBYTE(pThis_C8) = *(this + 8640);  // this+8640 = uCastSlot8640
    if ( (uint8_t)pThis_C8 == 0 )
    {
      LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)pThis_C8 != 0 )
      {
        sub_432FA0();  // 调 srand 播种
        nRand = rand() % 5 + 4;  // 调 以 16 位种子状态递推并返回 15 位结果
        pThis_C8 = (int *)(*(int (/*thiscall*/ **)(uint8_t *, const char *))(*(uint32_t *)this + 588))(this, "Particle/Seed.ptl");  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
        qmemcpy(v8, pThis_C8, 0x62u);  // 调 内存块拷贝(内联展开)
        nRand3 = nRand;
        if ( nRand > 0 )
        {
          do
          {
            v8[18] = rand() % 90 - 46;  // 调 以 16 位种子状态递推并返回 15 位结果
            v8[19] = rand() % 90 - 46;  // 调 以 16 位种子状态递推并返回 15 位结果
            v8[20] = rand() % 90 - 46;  // 调 以 16 位种子状态递推并返回 15 位结果
            nRand2 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
            v5 = *(uint32_t *)this;
            v8[17] = v8[17] + nRand2 % 50 - 26;
            LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t *, uint32_t, int, int, int, int, uint32_t, uint32_t, uint32_t))(v5 + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
                           this,
                           *((uint32_t *)this + 2161),  // this+8644 = 相位槽
                           0,
                           v8,
                           0,
                           50,
                           1,
                           112,
                           4,
                           0,
                           0,
                           0);
            --nRand3;
          }
          while ( nRand3 != 0 );
        }
      }
      *(this + 8640) = 1;  // this+8640 【推断】出土相位槽
    }
  }
  return (char)pThis_C8;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C3F70 sub_5C3F70 —— 树精小刺散射（30052/30051 号效果）
// 强制 pszArg2 非 0，或 vt+1908!=2 且 rand()%100≥95（5% 概率）时发动；
//   经 vt+308 玩家校验后发 rand()%3+3（3-5）枚：每枚在本体位姿 ±100/±35 抖动，
//   ·sub_4D9210 落点校验（最多试 100 次），通过则 ·sub_4E4A50 请求 30052/30051（rand 择一），
//   参数 5、朝向 4。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C3F70(uint32_t *this, char pszArg2)  // 函数: 树精小刺散射（30052/30051 号效果）
{
  int v2; // eax
  int nRand; // eax
  int v5; // et2
  int nRand2; // eax
  int v7; // et2
  int v8; // edx
  int v9; // edi
  int nRand3; // edi
  int v11; // ebx
  int nRand4; // ebx
  int nRand5; // eax
  int v15; // [esp+4h] [ebp-4h]
  int v16; // [esp+10h] [ebp+8h]

  LOBYTE(v2) = pszArg2;  // 调 取 16 位值低 8 位
  if ( pszArg2 != 0 || *(this + 1908) != 2 && (nRand = rand(), v5 = nRand % 100, v2 = nRand / 100, v5 >= 95) )  // 调 以 16 位种子状态递推并返回 15 位结果
  {
    LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    if ( (uint8_t)v2 != 0 )
    {
      sub_432FA0();  // 调 srand 播种
      nRand2 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
      v7 = nRand2 % 3;
      v2 = nRand2 / 3;
      v8 = v7 + 3;
      if ( v7 + 3 > 0 )
      {
        v15 = v8;
        do
        {
          v16 = 100;
          while ( 1 )  // 无限循环
          {
            v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
            nRand3 = v9 + rand() % 200 - 100;  // 调 以 16 位种子状态递推并返回 15 位结果
            v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
            nRand4 = v11 + rand() % 70 - 35;  // 调 以 16 位种子状态递推并返回 15 位结果
            if ( (uint8_t)sub_4D9210(nRand3, nRand4, 0) != 0 )  // 调 原查询【推断：8624 为反应接管标志】
              break;
            LOBYTE(v2) = --v16;  // 调 取 16 位值低 8 位
            if ( v16 <= 0 )
              goto LABEL_12;
          }
          nRand5 = rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
          LOBYTE(v2) = sub_4E4A50(this, 30052 - (nRand5 != 0), 5, nRand3, nRand4, 0, 4, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
LABEL_12:
          --v15;
        }
        while ( v15 != 0 );
      }
    }
  }
  return v2;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C4080 sub_5C4080 —— 技能参数预设 A：效果号 30038
// 写 this+2162=3（档位）与 this+2167=30038（效果/技能 id），供 ·0x5C3AF0 系列贴合与发射取参。
// ------------------------------------------------------------
void /*thiscall*/ sub_5C4080(uint32_t *this)  // 函数: 技能参数预设 A：效果号 30038
{
  *(this + 2162) = 3;  // this+8648 = 相位/缓存槽
  *(this + 2167) = 30038;  // this+8668 = nCool8668
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C40A0 sub_5C40A0 —— 承伤链增强：占用态 2 且攻击方 +20 非 0 则免伤
// 先转 ·0x5C3A90 类型过滤/减伤，返回非 3 时若 this+2150==2 且攻击方 vt+348 档位块
//   +20 字段非 0，将伤害 *pDwArg2 清零并返回 2（完全免伤【推断】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C40A0(uint32_t *this, int *pDwArg2, int nArg3)  // 函数: 承伤链增强：占用态 2 且攻击方 +20 非 0 则免伤
{
  int result; // eax
  int v5; // ebx

  result = sub_5C3A90(pDwArg2, nArg3);  // 调 树精承伤修正：类型过滤 + 档位减伤 25%
  v5 = result;
  if ( result != 3 )
  {
    if ( *(this + 2150) == 2 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 20) != 0 )  // this+8600 = uAI8600
    {
      *pDwArg2 = 0;
      return 2;
    }
    else
    {
      return v5;
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C4100 sub_5C4100 —— 技能参数预设 B：效果号 30039
// 写 this+2162=1（档位）与 this+2167=30039（效果/技能 id），供贴合与发射取参。
// ------------------------------------------------------------
void /*thiscall*/ sub_5C4100(uint32_t *this)  // 函数: 技能参数预设 B：效果号 30039
{
  *(this + 2162) = 1;  // this+8648 = 相位/缓存槽
  *(this + 2167) = 30039;  // this+8668 = nCool8668
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C4120 sub_5C4120 —— 状态施加拦截（架招/占用态屏蔽）
// 大状态 vt+840==14（架招）或 this+2150 占用槽非 0 时不转发；否则转 ·sub_4D6030
//   状态施加入口（17 状态槽懒创建 + 转发）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C4120(uint32_t *this, void *Block, int nArg3, int nArg4)  // 函数: 状态施加拦截（架招/占用态屏蔽）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( result != 14 )
  {
    result = *(this + 2150);  // this+8600 = uAI8600
    if ( result == 0 )
      return sub_4D6030((int)this, Block, nArg3, nArg4);  // 调 ★ 状态施加入口（17 状态槽懒创建 + 转发）
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C4160 sub_5C4160 —— 触须命中反馈特效（30032 号）
// vt+308 玩家校验后取 this+2155 挂载对象的 vt+120/124/152（位姿 + 朝向），
//   以 ·sub_4E4A50(this, 30032, 0, x, y, 0, 朝向) 请求命中特效。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C4160(uint32_t *this)  // 函数: 触须命中反馈特效（30032 号）
{
  int result; // eax
  int fld_e2155; // edi  | +0x21AC → 换目标横向补偿标志（0x5B32C0 0↔1 对调 ±50 偏置）【推断】（CNRodinglo）
  int v4; // eax
  int v5; // [esp-20h] [ebp-24h]
  int v6; // [esp-18h] [ebp-1Ch]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    fld_e2155 = *(this + 2155);  // this+8620 = uAI8620
    v6 = (*(int (**)(void))(*(uint32_t *)fld_e2155 + 152))();  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2155 + 124))(fld_e2155);  // 调用虚函数（虚表槽 +124）
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2155 + 120))(fld_e2155);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    return sub_4E4A50(this, 30032, 0, v4, v5, 0, v6, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C41B0 sub_5C41B0 —— 技能参数预设 C：效果号 30040 + 超时常量
// 写 this+2162=9999（无档位哨兵）、this+2167=30040，另写 this+2120=10 与 this+2121=2000
//   （疑为次数/毫秒超时【推断】）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5C41B0(uint32_t *this)  // 函数: 技能参数预设 C：效果号 30040 + 超时常量
{
  *(this + 2162) = 9999;  // this+8648 = 相位/缓存槽
  *(this + 2167) = 30040;  // this+8668 = nCool8668
  *(this + 2120) = 10;  // this+8480〔pAtkObj〕
  *(this + 2121) = 2000;
}



// 蓄雷 AI：BEFORE_THUNDER 播报（91L；树精复用雷系演出）
// ------------------------------------------------------------
// 0x5C41E0 sub_5C41E0 —— 蓄雷演出：BEFORE_THUNDER 播报 + 逐段位移
// vt+308 玩家校验；无目标时 vt+560 setState(0) 归位。有目标时按档位表 v17={2,4,6,8} 比对
//   this+2168 索引：档位不符或 this+8640 已置位则清零重来，否则 vt+212 播 BEFORE_THUNDER；
//   this+2172/2173 首次锁定目标坐标，按朝向取 ±50*(idx-1) 横偏，vt+152(this,100*(idx+1),1) 求高度，
//   经 vt+584 位置写入推进 this+2168 并置 this+8640 锁存（逐段梯次落位）。
// ------------------------------------------------------------
char /*usercall*/ sub_5C41E0@<al>(uint8_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：蓄雷演出：BEFORE_THUNDER 播报 + 逐段位移
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int pObj; // ecx
  int v8; // edi
  int v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // edi
  uint16_t v13; // dx
  int v14; // eax
  uint32_t v17[4]; // [esp+4h] [ebp-14h]
  int v18; // [esp+14h] [ebp-4h]

  LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)v4 != 0 )
  {
    if ( *((uint32_t *)pArg1 + 1813) != 0 )
    {
      v5 = *(uint32_t *)pArg1;
      v17[0] = 2;
      v17[1] = 4;
      v17[2] = 6;
      v17[3] = 8;
      v4 = (*(int (/*thiscall*/ **)(uint8_t *))(v5 + 200))(pArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      if ( *(uint32_t *)(v4 + 148) != v17[*((uint32_t *)pArg1 + 2168)] || (LOBYTE(v4) = pArg1[8640], (uint8_t)v4 != 0) )  // 调 取 16 位值低 8 位
      {
        pArg1[8640] = 0;
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          pArg1,
          "BEFORE_THUNDER",  // 资源/动画 TAG BEFORE_THUNDER
          -1,
          0,
          0);
        if ( *((uint32_t *)pArg1 + 2172) == -1 )
        {
          v6 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)pArg1 + 1813) + 120))(*((uint32_t *)pArg1 + 1813));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          pObj = *((uint32_t *)pArg1 + 1813);
          *((uint32_t *)pArg1 + 2172) = v6;
          *((uint32_t *)pArg1 + 2173) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 调用虚函数（虚表槽 +124）
        }
        v8 = *((uint32_t *)pArg1 + 2168) - 1;
        if ( (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pArg1 + 152))(pArg1, nArg3, nArg2) == 1 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          v9 = 50 * v8;
        else
          v9 = -50 * v8;
        v10 = *((uint32_t *)pArg1 + 2173);
        v11 = v9;
        v12 = *(uint32_t *)pArg1;
        v13 = *((uint16_t *)pArg1 + 4336) + 1;
        v18 = v11 + *((uint32_t *)pArg1 + 2172);
        v14 = (*(int (/*thiscall*/ **)(uint8_t *, int, int))(v12 + 152))(pArg1, 100 * v13, 1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t, int))(v12 + 584))(  // 调用虚函数（虚表槽 +584）【推断: ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6…】
          pArg1,
          v18,
          v10,
          0,
          v18,
          v10,
          *((uint32_t *)pArg1 + 2167),
          0,
          0,
          v14);
        v4 = *((uint32_t *)pArg1 + 2168) + 1;
        *((uint32_t *)pArg1 + 2168) = v4;
        pArg1[8640] = 1;
      }
    }
    else
    {
      LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
                     pArg1,
                     0,
                     0,
                     0,
                     0);
    }
  }
  return v4;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C4340 sub_5C4340 —— 向攻击方挂点贴合（this+2167 效果参）
// 取 nArg2 的 vt+576（挂接对象【推断】）非 0 时，以本体 vt+152(this,100,1,0,0) 求高度，
//   经该对象 vt+124/vt+120 两轮换算得坐标，vt+584 位置写入回填自机（贴到挂载点）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5C4340(uint32_t *this, int nArg2)  // 函数: 向攻击方挂点贴合（this+2167 效果参）
{
  int pObj3; // ebx
  int pObj2; // esi
  int v6; // eax
  int fld_e2167; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // [esp+8h] [ebp-8h]
  int pObj; // [esp+Ch] [ebp-4h]
  int pObj4; // [esp+18h] [ebp+8h]

  if ( nArg2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )  // 调用虚函数（虚表槽 +576）
  {
    pObj3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 调用虚函数（虚表槽 +576）
    pObj4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 调用虚函数（虚表槽 +576）
    pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 调用虚函数（虚表槽 +576）
    pObj2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 调用虚函数（虚表槽 +576）
    v11 = *this;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t))(*this + 152))(this, 100, 1, 0, 0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    fld_e2167 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj3 + 124))(pObj3, *(this + 2167), 0, 0, v6);  // this+8668 = nCool8668
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 120))(pObj4, fld_e2167);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v9 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 124))(pObj, 0, v8);  // 调用虚函数（虚表槽 +124）
    v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v9);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v11 + 584))(this, v10);  // 调用虚函数（虚表槽 +584）【推断: ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6…】
  }
}



// 陷阱·缠绕收紧（114L；章鱼陷阱触手收紧, 树精复用）：pArg1[2155](被缠目标)处于
//   大状态9 时清其 60 对象+24/+36 字段、本地玩家且动作尾时按目标 X/Y/宽×0.7+Z
//   结算一次触手伤害(sub_4E5F70)并播 TRAP_OCTOPUS_TIGHTEN；收紧计数 this[2156] 达
//   this[2157] 或目标 vt+724(挣脱标志)置位 → setState(15) 放开；变体 this[2154]==2
//   追加 300 帧硬直并在计数满时调 vt+331(爆裂释放)
// ------------------------------------------------------------
// 0x5C4400 sub_5C4400 —— 缠绕收紧循环（TRAP_OCTOPUS_TIGHTEN）
// 被缠对象 this+2155 空则 vt+560 setState(15) 收手；其大状态 9 时清其 60 号对象 +24/+36，
//   本地玩家（vt+50 的 +170）且动作判定（vt+77）成立时按目标 X/Y/宽×0.7+Z 结算一次
//   ·sub_4E5F70 硬直率掷伤害，并 vt+212 播 TRAP_OCTOPUS_TIGHTEN。收紧计数 this+2156 达 this+2157
//   或目标 vt+724 挣脱置位 → setState(15) 放开，否则 ·sub_4926A0 复位帧游标；this+2154==2 变体追加
//   ·sub_424120(…,2,300) 三百帧硬直并在计数满时 vt+331 爆裂释放，尾段 ·0x5C3C20 调触须锚点。
// ------------------------------------------------------------
int /*usercall*/ sub_5C4400@<eax>(uint32_t **pArg1@<ecx>, int nArg2@<ebx>)  // 实现：缠绕收紧循环（TRAP_OCTOPUS_TIGHTEN）
{
  uint32_t *pHeldObj; // ecx
  int pHeldState; // eax
  int pHeldVt; // edx
  uint32_t *pHeldObj2; // ecx
  int nHeldX; // eax
  uint32_t *pHeldObj3; // ecx
  int nHeldY; // eax
  uint32_t *pHeldObj4; // edi
  int pHeldVt2; // eax
  int nHeldZ2; // eax
  int pHeldId; // edx
  uint32_t *pHeldObj5; // ecx
  int nTightenCnt1; // eax
  int pCurAct; // eax
  int pMount; // eax
  int result; // eax
  float fHitX; // [esp+4h] [ebp-20h] BYREF
  float fHitY; // [esp+8h] [ebp-1Ch]
  float fHitZ; // [esp+Ch] [ebp-18h]
  int nZero1; // [esp+10h] [ebp-14h]
  int nZero2; // [esp+14h] [ebp-10h]
  int nZero3; // [esp+18h] [ebp-Ch]
  float fW70; // [esp+1Ch] [ebp-8h]
  int nHeldVal; // [esp+20h] [ebp-4h]

  pHeldObj = pArg1[2155];
  if ( pHeldObj == nullptr )  // 若 pHeldObj 为空
    return ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*pArg1)[140])(pArg1, 15, 0, 0, 0);
  pHeldState = (*(int (/*thiscall*/ **)(uint32_t *))(*pHeldObj + 840))(pHeldObj);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  pHeldVt = *pArg1[2155];
  if ( pHeldState == 9 )
  {
    *(uint32_t *)((*(int (**)(void))(pHeldVt + 60))() + 24) = 0;  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1[2155] + 60))(pArg1[2155]) + 36) = 0;  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
    if ( *(uint8_t *)(((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[50])(pArg1) + 170) != 0 )
    {
      if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*pArg1)[77])(pArg1) != 0 )
      {
        pHeldObj2 = pArg1[2155];
        fHitX = 0.0;
        fHitY = 0.0;
        fHitZ = 0.0;
        nZero1 = 0;
        nZero2 = 0;
        nZero3 = 0;
        nHeldX = (*(int (/*thiscall*/ **)(uint32_t *))(*pHeldObj2 + 120))(pHeldObj2);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        pHeldObj3 = pArg1[2155];
        nHeldVal = nHeldX;
        fHitX = (float)nHeldX;
        nHeldY = (*(int (/*thiscall*/ **)(uint32_t *))(*pHeldObj3 + 124))(pHeldObj3);  // 调用虚函数（虚表槽 +124）
        pHeldObj4 = pArg1[2155];
        nHeldVal = nHeldY;
        fHitY = (float)nHeldY;
        nHeldVal = (*(int (/*thiscall*/ **)(uint32_t *))(*pHeldObj4 + 192))(pHeldObj4);  // 调用虚函数（虚表槽 +192）
        pHeldVt2 = *pHeldObj4;
        fW70 = (double)nHeldVal * 0.69999999;
        nHeldZ2 = (*(int (/*thiscall*/ **)(uint32_t *))(pHeldVt2 + 128))(pHeldObj4);  // 调用虚函数（虚表槽 +128）
        pHeldId = (int)pArg1[2155];
        nHeldVal = nHeldZ2;
        fHitZ = (double)nHeldZ2 + fW70;
        sub_4E5F70(nArg2, (int)pArg1, pHeldId, &fHitX, 1, 1);  // 调 ★ 硬直率掷（研究 §5.1 第 14 轮定案：同构于暴击掷）
      }
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*pArg1)[53])(
        pArg1,
        "TRAP_OCTOPUS_TIGHTEN",  // 资源/动画 TAG TRAP_OCTOPUS_TIGHTEN
        -1,
        0,
        0);
      pHeldObj5 = pArg1[2157];
      nTightenCnt1 = (int)pArg1[2156] + 1;
      pArg1[2156] = (uint32_t *)nTightenCnt1;
      if ( nTightenCnt1 >= (int)pHeldObj5 || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1[2155] + 724))(pArg1[2155]) != 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
      {
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*pArg1)[140])(pArg1, 15, 0, 0, 0);
      }
      else
      {
        pCurAct = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[50])(pArg1);
        sub_4926A0(pCurAct);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      }
      if ( pArg1[2154] == (uint32_t *)2 )
      {
        pMount = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[20])(pArg1);
        sub_424120(*(uint32_t **)(pMount + 132), 2, 300);  // 调 屏幕震动启动
        if ( (int)pArg1[2156] >= (int)pArg1[2157]
          || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1[2155] + 724))(pArg1[2155]) != 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
        {
          ((void (/*thiscall*/ *)(uint32_t **))(*pArg1)[331])(pArg1);
        }
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1[2155] + 604))(pArg1[2155], 0);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1[2155] + 612))(pArg1[2155], 1, 1);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
    return sub_5C3C20(pArg1);  // 调 树精藤鞭/触须锚点定位（this+2154 模式分派）
  }
  else
  {
    result = (*(int (**)(void))(pHeldVt + 840))();  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    if ( result != 5 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1[2155] + 308))(pArg1[2155]);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1[2155] + 560))(pArg1[2155], 9, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    }
  }
  return result;
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5C4650 sub_5C4650 —— 承伤反馈：背击触发 + 伤害数字 + 命中包分发
// this+2150==1 且 ·sub_4E5AF0 背击判定成立时 ·0x5C3D40(this,50,0) 反击贴近（该 50 为百分比门限）；
// 攻击方 vt+348 档位块 +20==1 时按该块首字段×0.01 折百分比，new 0x80 字节经 ·sub_4D6810
//   构造 CNChangeHp 文本并 vt+56 播放；末段把 vt+348 块 +20 存入 this+2163 并转 ·sub_4DA3B0 命中包分发。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C4650(int *this, int nArg2, int nArg3, int nArg4)  // 函数: 承伤反馈：背击触发 + 伤害数字 + 命中包分发
{
  int pHitData; // eax
  int nDmgPct; // edi
  int pTextObj; // eax
  float fDmg; // [esp+0h] [ebp-2Ch]
  int nDmgMin; // [esp+34h] [ebp+8h]

  if ( *(this + 2150) == 1 && (uint8_t)sub_4E5AF0(this, nArg2) != 0 )  // 调 ★ 背击判定（研究 §3 定案：背击暴击加成 attackinfo+144）
    sub_5C3D40(this, 50, 0);  // 调 树精转向贴近/绑定决策（大状态 0 门控）
  pHitData = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // 调用虚函数（虚表槽 +348）
  if ( *(uint32_t *)(pHitData + 20) == 1 )
  {
    nDmgPct = (uint64_t)(*(float *)pHitData * 0.0099999998);  // ×0.01f（百分数转比例）
    if ( operator new(0x80u) != nullptr )  // operator new 分配 128 字节
    {
      nDmgMin = 1;
      if ( nDmgPct >= 1 )
        nDmgMin = nDmgPct;
      fDmg = (float)nDmgMin;
      pTextObj = sub_4D6810(LODWORD(fDmg), 100, 1, 1);  // 调 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
    }
    else
    {
      pTextObj = 0;
    }
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pTextObj + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
      pTextObj,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  *(this + 2163) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 20);  // this+8652 = 相位槽
  return sub_4DA3B0(nArg2, nArg3, nArg4);  // 调 ★ 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C4750 sub_5C4750 —— 承伤链包装：先散射再结算
// 先 ·0x5C3F70(this,0) 走概率散射（自动判定，非强制），再转 ·0x5C4650 走背击/伤害数字/命中分发。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C4750(int *this, int nArg2, int nArg3, int nArg4)  // 函数: 承伤链包装：先散射再结算
{
  sub_5C3F70(this, 0);  // 调 树精小刺散射（30052/30051 号效果）
  return sub_5C4650(this, nArg2, nArg3, nArg4);  // 调 承伤反馈：背击触发 + 伤害数字 + 命中包分发
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C4780 sub_5C4780 —— 动作号修复：占用态收手 + 索引回填
// this+2150 非 0 时先 vt+1316 收手/触发；再从 this+1554 表对象[2]/[3]/[7] 判断本机
//   this+1543/1544/1540 动作号是否需还原为 this+2151/2152/2153 预设值；末段对
//   this+2169 起两个挂点对象逐个 vt+84(…,0) 复位。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C4780(uint32_t *this)  // 函数: 动作号修复：占用态收手 + 索引回填
{
  uint32_t *fld_e1554; // eax
  uint32_t *pThis_879; // esi
  int i; // edi
  int result; // eax

  if ( *(this + 2150) != 0 )  // this+8600 = uAI8600
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1316))(this);  // 调用虚函数（虚表槽 +1316）
  fld_e1554 = (uint32_t *)*(this + 1554);  // this+6216 = 资源/帧游标表
  if ( *(this + 1543) == fld_e1554[2] )  // this+6172〔pAtkCtxA6172〕
    *(this + 1543) = *(this + 2151);  // this+8604 = bAI8604
  if ( *(this + 1544) == fld_e1554[3] )  // this+6176〔pAtkCtxB6176〕
    *(this + 1544) = *(this + 2152);  // this+8608 = uAI8608
  if ( *(this + 1540) == fld_e1554[7] )
    *(this + 1540) = *(this + 2153);  // this+8612 = uAI8612
  pThis_879 = this + 2169;
  for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_879 + 84))(*pThis_879, 0);  // 调用虚函数（虚表槽 +84）【推断: this+156 字节存取】
    ++pThis_879;
  }
  return result;
}



// 树精行进状态机（141L）：DENDROID_SWISH_02/SWISH_01/DRIVE_01/01_LOOP 四段播报
//   （this+200/8600/8620/8684/8685 相位 —— 钻地行进→突刺循环【推断】）
// ------------------------------------------------------------
// 0x5C4810 sub_5C4810 —— 树精主循环：四段播报 + 攻克门控
// 以主状态镜像 this+6556 分派：8（攻击）按攻击段号槽 this+7028 取值——1/2 段时比对 6200 表对象，
//   若 200 对象为当前段且 +170 非 0 且 this+8620 未置位则 ·sub_4926A0 复位 6216 表 +24 帧游标并 vt+196 切帧，
//   否则动作不符时 vt+560 setState(0)；段号 3 转 ·0x5C3E20 种子散射、4 转 vt+1308、0 段按档位≥3 播 DENDROID_SWISH_01。
// 档位 ≥2 时播 DENDROID_SWISH_02（this+8685 锁存）；14 转 ·0x5C4400 缠绕收紧；16 播 DENDROID_DRIVE_01；
//   15/17 在弹出条件成立时 vt+560 setState(0) 收位；尾段 ·sub_4E1780 基类步进 + 8600==2 且挂点 +170 时转绑定 17 + 待机 9。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C4810(int this)  // 函数: 树精主循环：四段播报 + 攻克门控
{
  uint32_t *fld_1838; // edi
  uint32_t *fld_1848; // edi
  char fld_78; // al  | +0x0078 → 动画对象指针〔CNRDObject.h +0x078；499020/499080 帧推进对象〕（CNDendroidBasic；va=00499020）
  int pThis_348; // eax

  switch ( *(uint32_t *)(this + 6556) )  // this+6556 主状态镜像
  {
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      {
        fld_1838 = (uint32_t *)(*(uint32_t *)(this + 6200) + 4 * sub_41A5E0(this + 7028));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *fld_1838  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          && *(uint32_t *)(this + 8620) == 0 )  // this+8620 相位双字节门
        {
          sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 24));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(  // 调用虚函数（虚表槽 +196）
            this,
            *(uint32_t *)(*(uint32_t *)(this + 6216) + 24));  // this+6216 【推断】资源/帧游标表
        }
        else
        {
          fld_1848 = (uint32_t *)(*(uint32_t *)(this + 6216) + 24);  // this+6216 【推断】资源/帧游标表
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *fld_1848  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
            && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
            && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
          }
        }
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 2  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          && *(uint8_t *)(this + 8685) == 0 )  // this+8685 【推断】挥击/散射语音锁存
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
            this,
            "DENDROID_SWISH_02",  // 资源/动画 TAG DENDROID_SWISH_02
            -1,
            0,
            0);
          *(uint8_t *)(this + 8685) = 1;  // this+8685 【推断】挥击/散射语音锁存
        }
      }
      else if ( sub_41A5E0(this + 7028) == 3 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      {
        sub_5C3E20(this);  // 调 种子散射：DENDROID_SPIT 播报 + Particle/Seed.ptl 多发
      }
      else if ( sub_41A5E0(this + 7028) == 4 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1308))(this);  // 调用虚函数（虚表槽 +1308）
      }
      else if ( sub_41A5E0(this + 7028) == 0  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
             && *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 3  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
             && *(uint8_t *)(this + 8685) == 0 )  // this+8685 【推断】挥击/散射语音锁存
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          this,
          "DENDROID_SWISH_01",  // 资源/动画 TAG DENDROID_SWISH_01
          -1,
          0,
          0);
        *(uint8_t *)(this + 8685) = 1;  // this+8685 【推断】挥击/散射语音锁存
      }
      break;
    case 0xE:
      sub_5C4400(this);  // 调 缠绕收紧循环（TRAP_OCTOPUS_TIGHTEN）
      break;
    case 0xF:
      fld_78 = *(uint8_t *)(*(uint32_t *)(this + 120) + 170);  // this+120 动画对象指针
      goto LABEL_33;
    case 0x10:
      if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 3  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        && *(uint8_t *)(this + 8685) == 0 )  // this+8685 【推断】挥击/散射语音锁存
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          this,
          "DENDROID_DRIVE_01",  // 资源/动画 TAG DENDROID_DRIVE_01
          -1,
          0,
          0);
        *(uint8_t *)(this + 8685) = 1;  // this+8685 【推断】挥击/散射语音锁存
      }
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      {
        goto LABEL_34;
      }
      break;
    case 0x11:
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      {
        fld_78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
LABEL_33:
        if ( fld_78 != 0 )
LABEL_34:
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      }
      break;
    default:
      break;
  }
  sub_4E1780((uint32_t *)this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( *(uint32_t *)(this + 8600) == 2  // this+8600 子类 AI 状态字节 1
    && *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 6216) + 32) + 170) != 0  // this+6216 【推断】资源/帧游标表
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  {
    (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 17, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
  }
  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( pThis_348 != 0
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 184))(this) == 4  // 调用虚函数（虚表槽 +184）【推断: 动画对象 z 倾斜转状态码】
    && (pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 188))(this)) == 4 )  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
  {
    if ( *(uint8_t *)(this + 8684) == 1 )  // this+8684 【推断】子类 AI 门字节
    {
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
      *(uint8_t *)(this + 8684) = 0;  // this+8684 【推断】子类 AI 门字节
    }
  }
  else
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8684);  // 调 取 16 位值低 8 位
    if ( (uint8_t)pThis_348 == 0 )
    {
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                     this,
                     "DENDROID_01_LOOP",  // 资源/动画 TAG DENDROID_01_LOOP
                     9,
                     0,
                     0);
      *(uint8_t *)(this + 8684) = 1;  // this+8684 【推断】子类 AI 门字节
    }
  }
  return pThis_348;
}


// AI 相位辅助（83L）
// ------------------------------------------------------------
// 0x5C5720 sub_5C5720 —— 行为字槽门控：拉近/脱离转态 + 帧数组标记
// ·sub_4E0120 基类步进后按 this+1787 行为字分派：0 → vt+1284；4 → 无目标时 vt+1104 写 13；
//   12 → this+2150==1 且玩家校验通过时 vt+560 setState(17)；13/14/15 → 有目标时 vt+1104 写 4。
// 尾段在无占用（this+2150==0）且有目标时，按 |Δx|（this+1905 起帧数组，步长 32，索引 0..2）
//   逐帧写 0/1 标记：距离 ≤280 写 0 否则写 1（疑为帧事件开关【推断】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C5720(uint32_t *this)  // 函数: 行为字槽门控：拉近/脱离转态 + 帧数组标记
{
  uint32_t *pThis2; // esi
  int result; // eax
  int v3; // edi
  unsigned int v4; // ebx
  int i; // edx
  int v6; // edi
  uint8_t *v7; // ecx
  uint32_t *pThis; // ecx

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( *(this + 1787) )  // this+7148 = nBigState
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
      pThis = this;
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
        goto LABEL_10;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
      pThis = this;
      break;
    case 0xC:
      if ( *(this + 2150) == 1 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // this+8600 = uAI8600
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 17, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      goto LABEL_10;
    case 0xD:
    case 0xE:
    case 0xF:
      if ( *(this + 1813) == 0 )  // this+7252 = pTarget7252
        goto LABEL_10;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 调用虚函数（虚表槽 +1104）
      pThis = this;
      break;
    default:
LABEL_10:
      pThis = this;
      break;
  }
  pThis2 = pThis;
  result = pThis[2150];
  if ( result == 0 )
  {
    result = pThis[1813];
    if ( result != 0 )  // 若结果非 0（成功）
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 120))(result);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      result = abs32((*(int (/*thiscall*/ **)(uint32_t *))(*pThis2 + 120))(pThis2) - v3);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      v4 = 0;
      for ( i = 0; ; i += 32 )
      {
        while ( 1 )  // 无限循环
        {
          v6 = pThis2[1905];
          if ( v6 == 0 || v4 >= (pThis2[1906] - v6) >> 5 )
            return result;
          if ( i > 0 && i <= 64 )  // 若 i > 0 与/或 i <= 64
            break;
LABEL_21:
          ++v4;
          i += 32;
        }
        v7 = (uint8_t *)(i + v6);
        if ( result <= 280 )
        {
          *v7 = 0;
          goto LABEL_21;
        }
        ++v4;
        *v7 = 1;
      }
    }
  }
  return result;
}



// 树精语音：R_DENDROID_DMG + DENDROID_DIE（this+8684/8685 相位）
// ------------------------------------------------------------
// 0x5C57F0 sub_5C57F0 —— 树精初始化：语音 TAG 注册 + 动作号快照
// 经 ·sub_4015C0 注册 R_DENDROID_DMG(14) 与 DENDROID_DIE(12) 语音槽；
//   写 this+2158=8（状态号）、vt+384(this,2) 取出场参数存 this+2161，this+8684/8685 相位清零；
//   ·sub_4E1390(196613, 100000) 设死亡超时；末段把本机动作号 this+1543/1544/1540
//   快照进 this+2151/2152/2153 供 ·0x5C4780 还原比对。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C57F0(uint32_t *this)  // 函数: 树精初始化：语音 TAG 注册 + 动作号快照
{
  int v2; // eax
  int result; // eax
  int fld_e1540; // ecx
  int v5; // [esp+4h] [ebp-4h] BYREF

  sub_4015C0("R_DENDROID_DMG", 0xEu);  // 【std::string构造赋值】
  sub_4015C0("DENDROID_DIE", 0xCu);  // 【std::string构造赋值】
  v2 = *this;
  *(this + 2158) = 8;  // this+8632〔bDevourFlag(推断)〕
  *(this + 2161) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v2 + 384))(this, 2);  // this+8644 = 相位槽
  *((uint8_t *)this + 8684) = 0;  // this+8684 【推断】子类 AI 门字节
  *((uint8_t *)this + 8685) = 0;  // this+8685 【推断】挥击/散射语音锁存
  v5 = 100000;
  sub_4E1390(196613, &v5);  // 调 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
  result = *(this + 1544);  // this+6176〔pAtkCtxB6176〕
  fld_e1540 = *(this + 1540);
  *(this + 2151) = *(this + 1543);  // this+8604 = bAI8604
  *(this + 2152) = result;  // this+8608 = uAI8608
  *(this + 2153) = fld_e1540;  // this+8612 = uAI8612
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5C5890 sub_5C5890 —— 攻击反制：攻击者贴身段号 1/2 时反向架招
// 条件：主状态镜像 this+1639==8、段号槽 this+1757∈{1,2}、nArg4==0、vt+308 玩家校验通过、
//   攻击者 vt+40(pObj,17) 类型校验（17=玩家）+ vt+948 判定通过、this+154 !=14。
// 满足则用 ·sub_431230 打包 vt+48/vt+52/段号 三参，vt+560 setState(14) 架招；末尾
//   ·sub_4DB480 反击判定兜底。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C5890(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 攻击反制：攻击者贴身段号 1/2 时反向架招
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8  // this+6556 = 主状态镜像
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2)  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 948))(pObj) != 0  // 调用虚函数（虚表槽 +948）
    && *(this + 154) != 14 )  // this+154 施放标志 B
  {
    memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
    v6 = *(uint32_t *)pObj;
    v9 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(v6 + 48))(pObj);  // 调用虚函数（虚表槽 +48）
    sub_431230((int)pBuf, &nArg2);  // 调 uint32 vector push_back
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调用虚函数（虚表槽 +52）
    sub_431230((int)pBuf, &nArg2);  // 调 uint32 vector push_back
    nArg2 = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_431230((int)pBuf, &nArg2);  // 调 uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    v9 = -1;
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
  return sub_4DB480(pObj, nArg3, nArg4);  // 调 ★ 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 参数打包 AI（107L sub_431230）
// ------------------------------------------------------------
// 0x5C59C0 sub_5C59C0 —— 缠绕解除：被缠者脱身定位 + 状态回写
// this+2155 被缠对象 vt+604(1,nArg2) 与 vt+612(0,0) 解开抓取，再经其 vt+136(this+2164, this+2165, 0)
//   站台校验成功则 vt+112 落位；失败时改以自身 vt+140 校验本机位移，不行则改用 this+2166 备用偏移落位。
// 被缠对象玩家校验通过后：·sub_431230 打包 4/0/1/200/200 五参并经其 vt+560 setState(4) + vt+564 收尾。
// this+2154 类型 1 时 vt+848 reset；类型 2 时 ·sub_495890(2,0) + vt+60 + ·sub_4A0550(10)，
//   若对象为 dword_8F7C04（本机本地玩家）则经 vt+80 取挂载列表 ·sub_424A40 移出。
// ------------------------------------------------------------
void /*usercall*/ sub_5C59C0(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 函数: 缠绕解除：被缠者脱身定位 + 状态回写
{
  int pHeldObj; // ecx
  int pHeldObj2; // edi
  int pHeldVt; // edx
  int nTryY; // eax
  int nTryX; // eax
  char bMoveOk; // al
  int pHeldObj3; // ecx
  int pHeldVt2; // edi
  int nAltY; // eax
  int nAltX; // eax
  int nTrapType; // eax
  int pMountList; // eax
  char v15[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v17; // [esp+10h] [ebp-18h]
  int v18; // [esp+14h] [ebp-14h]
  int nPackVal; // [esp+18h] [ebp-10h] BYREF
  int v20; // [esp+24h] [ebp-4h]

  pHeldObj = pDwArg1[2155];
  if ( pHeldObj != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pHeldObj + 604))(pHeldObj, 1, nArg2);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2155] + 612))(pDwArg1[2155], 0, 0);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2155] + 136))(  // 调用虚函数（虚表槽 +136）
           pDwArg1[2155],
           pDwArg1[2164],
           pDwArg1[2165],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pDwArg1[2155] + 112))(pDwArg1[2155], pDwArg1[2164], pDwArg1[2165]);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    }
    else
    {
      pHeldObj2 = pDwArg1[2155];
      pHeldVt = *(uint32_t *)pHeldObj2;
      nPackVal = pHeldObj2;
      nPackVal = *pDwArg1;
      nTryY = (*(int (/*thiscall*/ **)(int, int, int, int))(pHeldVt + 124))(pHeldObj2, 300, 1, 1);  // 调用虚函数（虚表槽 +124）
      nTryX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pHeldObj2 + 120))(pHeldObj2, nTryY);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      bMoveOk = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(nPackVal + 140))(pDwArg1, pDwArg1 + 2164, pDwArg1 + 2165, nTryX);  // 调用虚函数（虚表槽 +140）【推断: ★ 螺旋式寻找空位（同心方环，从 (a4,a5) 起向外扫）】
      pHeldObj3 = pDwArg1[2155];
      if ( bMoveOk != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pHeldObj3 + 112))(pHeldObj3, pDwArg1[2164], pDwArg1[2165]);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      }
      else
      {
        pHeldVt2 = *(uint32_t *)pHeldObj3;
        nAltY = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2166]);  // 调用虚函数（虚表槽 +124）
        nAltX = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nAltY);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        (*(void (/*thiscall*/ **)(int, int))(pHeldVt2 + 112))(pDwArg1[2155], nAltX);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2155] + 308))(pDwArg1[2155]) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    {
      Block = nullptr;
      v17 = 0;
      v18 = 0;
      v20 = 0;
      nPackVal = 4;
      sub_431230((int)v15, &nPackVal);  // 调 uint32 vector push_back
      nPackVal = 0;
      sub_431230((int)v15, &nPackVal);  // 调 uint32 vector push_back
      nPackVal = 1;
      sub_431230((int)v15, &nPackVal);  // 调 uint32 vector push_back
      nPackVal = 200;
      sub_431230((int)v15, &nPackVal);  // 调 uint32 vector push_back
      nPackVal = 200;
      sub_431230((int)v15, &nPackVal);  // 调 uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2155] + 560))(pDwArg1[2155], 4, v15, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2155] + 564))(pDwArg1[2155]);  // 调用虚函数（虚表槽 +564）【推断: ★ 位移同步包 vt+234（会话 3 定案：UDP type=…】
      v20 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
      Block = nullptr;
      v17 = 0;
      v18 = 0;
    }
    nTrapType = pDwArg1[2154];
    if ( nTrapType == 1 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2155] + 848))(pDwArg1[2155], 0);  // 调用虚函数（虚表槽 +848）【推断: [RTTI: IRDActiveObject__vmt350 ·…】
    }
    else if ( nTrapType == 2 )
    {
      sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2155] + 60))(pDwArg1[2155]);  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
      sub_4A0550(10);  // 调 镜头幅度
      if ( pDwArg1[2155] == dword_8F7C04 )  // dword_8F7C04 = 本地玩家对象
      {
        pMountList = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 调用虚函数（虚表槽 +80）
        sub_424A40(*(uint32_t **)(pMountList + 132), pDwArg1[2155]);  // 调 锚定角色 setter
      }
    }
    pDwArg1[2155] = 0;
  }
  pDwArg1[2154] = -1;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5C5C20 sub_5C5C20 —— 概率起手：rand()%300 门限后进入状态 16
// 条件：this+2150 无占用 + 玩家校验 + 行为字 this+1787 !=12 + 大状态 vt+840==0 + 目标存在
//   + rand()%300 < nArg3 + this+2162>0 + vt+8 距离判定 <200。
// 满足则 ·sub_431230 打包 nArg2 并 vt+560 setState(16)（出土/驱动），随后 ·sub_5E5260 释放缓冲。
// ------------------------------------------------------------
void /*thiscall*/ sub_5C5C20(uint32_t *this, int nArg2, int nArg3)  // 函数: 概率起手：rand()%300 门限后进入状态 16
{
  void *pBuf[7]; // [esp+8h] [ebp-1Ch] BYREF

  if ( *(this + 2150) == 0  // this+8600 = uAI8600
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && *(this + 1787) != 12  // this+7148 = nBigState
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && *(this + 1813) != 0  // this+7252 = pTarget7252
    && rand() % 300 < nArg3  // 调 以 16 位种子状态递推并返回 15 位结果
    && (int)*(this + 2162) > 0  // this+8648 = 相位/缓存槽
    && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 8))(this, *(this + 1813), 0) < 200 )  // this+7252 = pTarget7252
  {
    memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
    pBuf[6] = nullptr;
    sub_431230((int)pBuf, &nArg2);  // 调 uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 16, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C5D00 sub_5C5D00 —— 行为字 0 分支：追踪 + 低概率 30 门限起手
// ·0x5C5720 行为字门控 + ·0x5C5C20(this,1,30)（1/300 概率起手）+ ·0x5C3D40(this,50,0) 反击贴近。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C5D00(int *this)  // 函数: 行为字 0 分支：追踪 + 低概率 30 门限起手
{
  sub_5C5720(this);  // 调 行为字槽门控：拉近/脱离转态 + 帧数组标记
  sub_5C5C20(this, 1, 30);  // 调 概率起手：rand()%300 门限后进入状态 16
  return sub_5C3D40(this, 50, 0);  // 调 树精转向贴近/绑定决策（大状态 0 门控）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C5D20 sub_5C5D20 —— 行为字分支：血线低于 25% 时高概率起手
// ·0x5C5720 门控后比较 vt+736 姿态查询值与 vt+740 上限×0.25：若上限的四分之一 > 当前值
//   （即血量低于 25%【推断】），转 ·0x5C5C20(this,2,300) 满概率起手。
// ------------------------------------------------------------
void /*thiscall*/ sub_5C5D20(uint32_t *this)  // 函数: 行为字分支：血线低于 25% 时高概率起手
{
  float v2; // [esp+4h] [ebp-8h]

  sub_5C5720(this);  // 调 行为字槽门控：拉近/脱离转态 + 帧数组标记
  v2 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
  if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * 0.25 > v2 )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    sub_5C5C20(this, 2, 300);  // 调 概率起手：rand()%300 门限后进入状态 16
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C5D80 sub_5C5D80 —— 行为字分支：满概率起手 + 100 门限反击
// ·0x5C5720 门控 + ·0x5C5C20(this,1,300)（必发）+ ·0x5C3D40(this,100,0)。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C5D80(int *this)  // 函数: 行为字分支：满概率起手 + 100 门限反击
{
  sub_5C5720(this);  // 调 行为字槽门控：拉近/脱离转态 + 帧数组标记
  sub_5C5C20(this, 1, 300);  // 调 概率起手：rand()%300 门限后进入状态 16
  return sub_5C3D40(this, 100, 0);  // 调 树精转向贴近/绑定决策（大状态 0 门控）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C5DB0 sub_5C5DB0 —— 消亡通知：解缠绕 + 状态归位后转 ·sub_4D9170
// 若归档参数 pDwArg3 即被缠对象 this+2155：大状态 14 时先 ·0x5C59C0 解缠绕，再清 this+2155。
// 若 pDwArg3 为本机：仍有被缠对象则 ·0x5C59C0 解除并清空，随后 vt+216 切状态 9；
// 末尾转 ·sub_4D9170(pDwArg3) 消亡通知（发亡语/掉装备）。
// ------------------------------------------------------------
int /*userpurge*/ sub_5C5DB0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)  // 实现：消亡通知：解缠绕 + 状态归位后转 ·sub_4D9170
{
  if ( pDwArg3 == (int *)pDwArg1[2155] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      sub_5C59C0(pDwArg1, nArg2);  // 调 缠绕解除：被缠者脱身定位 + 状态回写
    pDwArg1[2155] = 0;
  }
  if ( pDwArg3 == pDwArg1 )
  {
    if ( pDwArg1[2155] != 0 )
    {
      sub_5C59C0(pDwArg1, nArg2);  // 调 缠绕解除：被缠者脱身定位 + 状态回写
      pDwArg1[2155] = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
  }
  return sub_4D9170(pDwArg3);  // 调 消亡通知
}



// 攻击 AI：DENDROID_ATK 播报（92L）
// ------------------------------------------------------------
// 0x5C5E20 sub_5C5E20 —— 树精攻击状态机：分派 + DENDROID_ATK 播报
// 主状态镜像 this+6556==14（架招）时先 ·0x5C59C0 解缠绕；再按 ArgList：14 → ·sub_5C4CA0(Block)、
//   15 → vt+196 切帧（6216 表 +24）、16 → vt+1312 收手（*Block[1]）、17 → vt+1316 触发。清 this+8685
//   后 ·sub_4E33D0 收尾；ArgList==5 且 this+8652==0 时 ·0x5C3F70(this,1) 强制散射；ArgList==8 清
//   this+8640/8672 并按段号槽 this+7028∈{0,4} 播 DENDROID_ATK；ArgList==0 且 v12==16 且 8600==2 时
//   复位 6216 表 +32 帧游标 + vt+204 定位，按 vt+740×0.75 − vt+736 差值经 ·sub_4D6810 播伤害文本。
// ------------------------------------------------------------
char /*userpurge*/ sub_5C5E20@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, uint32_t **Block, int nArg5, int nArg6)  // 实现：树精攻击状态机：分派 + DENDROID_ATK 播报
{
  int v7; // eax
  int v8; // eax
  int pObj; // eax
  float v11; // [esp+18h] [ebp-2Ch]
  int v12; // [esp+34h] [ebp-10h]
  int ArgLista; // [esp+4Ch] [ebp+8h]
  float Blocka; // [esp+50h] [ebp+Ch]

  v12 = *(uint32_t *)(pArg1 + 6556);  // pArg1+6556〔大状态ID〕
  if ( v12 == 14 )
    sub_5C59C0((int *)pArg1, nArg2);  // 调 缠绕解除：被缠者脱身定位 + 状态回写
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      sub_5C4CA0(Block);
      break;
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 24));  // 调用虚函数（虚表槽 +196）
      break;
    case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 1312))(pArg1, *Block[1]);  // 调用虚函数（虚表槽 +1312）
      break;
    case 17:  // case 17 = ENUM_CMDPACKET_SELECT_DUNGEON
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1316))(pArg1);  // 调用虚函数（虚表槽 +1316）
      break;
    default:
      break;
  }
  *(uint8_t *)(pArg1 + 8685) = 0;  // pArg1+8685〔bGate8685(推断)〕
  LOBYTE(v7) = sub_4E33D0(ArgList, *(float *)&Block, nArg5, nArg6);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList != 0 )
  {
    if ( ArgList == 5 )
    {
      if ( *(uint32_t *)(pArg1 + 8652) == 0 )  // pArg1+8652〔uPhase8652(推断)〕
        LOBYTE(v7) = sub_5C3F70((uint32_t *)pArg1, 1);  // 调 树精小刺散射（30052/30051 号效果）
    }
    else if ( ArgList == 8 )
    {
      *(uint8_t *)(pArg1 + 8640) = 0;  // pArg1+8640〔uCastSlot8640(推断)〕
      *(uint32_t *)(pArg1 + 8672) = 0;  // pArg1+8672〔uAI8672(推断)〕
      if ( sub_41A5E0(pArg1 + 7028) == 0 || (v7 = sub_41A5E0(pArg1 + 7028)) == 4 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                       pArg1,
                       "DENDROID_ATK",  // 资源/动画 TAG DENDROID_ATK
                       -1,
                       0,
                       0);
    }
  }
  else if ( v12 == 16 && *(uint32_t *)(pArg1 + 8600) == 2 )  // pArg1+8600〔uAI8600(推断)〕
  {
    sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 32));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(  // 调用虚函数（虚表槽 +204）
      pArg1,
      100,
      *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 32),
      0,
      0,
      0,
      0);
    Blocka = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 740))(pArg1) * 0.75;  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    ArgLista = (uint64_t)(Blocka - (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 736))(pArg1));  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
    if ( operator new(0x80u) != nullptr )  // operator new 分配 128 字节
    {
      v8 = sub_4924C0(0);  // 调 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      v11 = (float)ArgLista;
      pObj = sub_4D6810(LODWORD(v11), *(uint32_t *)(v8 + 48), 1, 1);  // 调 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
    }
    else
    {
      pObj = 0;
    }
    LOBYTE(v7) = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
                   pObj,
                   pArg1,
                   pArg1,
                   0,
                   0,
                   0,
                   -1);
  }
  return v7;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C6040 sub_5C6040 —— 与 ·sub_5C5E20 同构（差异：叠加段号 4 时 8688/8692 置 -1）
// 转发攻击状态机后，若 ArgList==8 且段号槽 this+7028==4，将 pArg1+8688 与 +8692 置 -1 并返回 -1。
// ------------------------------------------------------------
char /*userpurge*/ sub_5C6040@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, uint32_t **Block, int nArg5, int nArg6)  // 实现：与 ·sub_5C5E20 同构（差异：叠加段号 4 时 8688/8692 置 -1）
{
  int v7; // eax

  LOBYTE(v7) = sub_5C5E20(pArg1, nArg2, ArgList, Block, nArg5, nArg6);  // 调 树精攻击状态机：分派 + DENDROID_ATK 播报
  if ( ArgList == 8 )
  {
    v7 = sub_41A5E0(pArg1 + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( v7 == 4 )
    {
      *(uint32_t *)(pArg1 + 8688) = -1;  // pArg1+8688〔bVec8688(推断)〕
      *(uint32_t *)(pArg1 + 8692) = -1;  // pArg1+8692〔uVec8692(推断)〕
      LOBYTE(v7) = -1;  // 调 取 16 位值低 8 位
    }
  }
  return v7;
}



// 抓取技能：Monster/Dendroid/CommonAni/{GrabAttack,Grab}.ani（51L；抓取→拖拽两段）
// ------------------------------------------------------------
// 0x5C6090 sub_5C6090 —— 抓取挂点初始化：GrabAttack.ani + Grab.ani
// ·sub_4DA130 基类初始化后，对 this+2169 起两个挂点槽循环：逐槽 ·sub_42FCB0(228) 建动画实体，
//   经 ·sub_431860 装载 Monster/Dendroid/CommonAni/GrabAttack.ani 与 Grab.ani（v8 表），
//   new 0x11C 字节经 ·sub_44E0D0 构造对象存入挂点、vt+72(2) 设模式，再 ·sub_45FE80 登记到 this+29 特效集，
//   最后 vt+112(-1000,-1000,0) 把挂点移出屏幕（抓取时才吸附）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C6090(int *this)  // 函数: 抓取挂点初始化：GrabAttack.ani + Grab.ani
{
  int v2; // edi
  int *pThis_879; // esi
  void *pMem; // eax
  char *v5; // eax
  int v6; // edx
  int result; // eax
  void *v8[3]; // [esp+Ch] [ebp-1Ch]
  int v9; // [esp+18h] [ebp-10h]
  int v10; // [esp+24h] [ebp-4h]

  sub_4DA130();  // 调 基类初始化后
  v8[0] = "Monster/Dendroid/CommonAni/GrabAttack.ani";  // 资源路径 Monster/Dendroid/CommonAni/GrabAttack.ani
  v8[1] = "Monster/Dendroid/CommonAni/Grab.ani";  // 资源路径 Monster/Dendroid/CommonAni/Grab.ani
  v2 = 0;
  pThis_879 = this + 2169;
  do
  {
    v9 = sub_42FCB0(228);  // 调 CRT 一次性初始化
    v10 = 0;
    if ( v9 != 0 )
      v9 = sub_431860((char)v8[v2], 1);  // 调 动画件构造（资源 id 版）
    else
      v9 = 0;
    v10 = -1;
    pMem = operator new(0x11Cu);  // operator new 分配 284 字节
    v8[2] = pMem;
    v10 = 1;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v5 = sub_44E0D0((char *)pMem, v9, 0);  // 调 CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    else
      v5 = nullptr;
    *pThis_879 = (int)v5;
    v6 = *(uint32_t *)v5;
    v10 = -1;
    (*(void (/*thiscall*/ **)(char *, int))(v6 + 72))(v5, 2);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    sub_45FE80(*(this + 29), v2, 2, 0, *pThis_879, (int)this, 1);  // 调 对象注册
    result = (*(int (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)*pThis_879 + 112))(*pThis_879, -1000, -1000, 0);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    ++v2;
    ++pThis_879;
  }
  while ( v2 < 2 );
  return result;
}



// ============================================================
// 【分区 4】属性精灵四色（Water/Fire/Dark/Light Soul）（0x5C6190-0x5C9360）
// 证据：{WATER,FIRESOUL,DARKSOUL,LIGHTSOUL}_{CREATE,CAST,ATK_1/2(+READY),DMG,DIE,01_LOOP} 全套、
//       Monster/Spirit/{Water,Fire,Dark,Light}Animation/Die.ani + LightAnimation/DieGlow.ani、
//       Particle/NaiasSacrificeAttack.ptl 水精灵献祭、Monster/Spirit/Light1Glow.equ、
//       0x5C92D0 调 sub_4E4430（HP 受击处理器/Boss 终局族）

// AI 字段访问
// ------------------------------------------------------------
// 0x5C6190 sub_5C6190 —— 替身槽清空
//   把 this[2184]（RTTI 转出的 CNDecoy 替身指针槽）置 0；·0x5C88C0 事件 14 写入、事件 16 亦清此槽。
// ------------------------------------------------------------
void /*thiscall*/ sub_5C6190(uint32_t *this)  // 函数: 替身槽清空
{
  *(this + 2184) = 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C61A0 sub_5C61A0 —— 目标触发登记（类型 529）
//   目标经 vt+40(obj,529) 判为陷阱族、本体 vt+724 未激活且 vt+1316（触发校验）通过时，
//   经 vt+1320(this,1) 登记触发；与 ·0x5C61F0 的撤销成对。【触发位含义推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5C61A0(void *this, int nArg2)  // 函数: 目标触发登记（类型 529）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 724))(this);  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
    if ( (uint8_t)result == 0 )
    {
      result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1316))(this, nArg2);  // 调用虚函数（虚表槽 +1316）
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1320))(this, 1);  // 调用虚函数（虚表槽 +1320）
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C61F0 sub_5C61F0 —— 目标触发撤销/消亡清理
//   类型 529 且 vt+724 未激活时经 vt+1320(this,0) 撤登记；自身即目标则 vt+216(this,9)，
//   替身槽 this[2184] 指向目标则清空，尾调 sub_4D9170 消亡通知。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C61F0(uint32_t *this, uint32_t *pArg2)  // 函数: 目标触发撤销/消亡清理
{
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 529) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t *))(*this + 1316))(this, pArg2) != 0 )  // 调用虚函数（虚表槽 +1316）
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1320))(this, 0);  // 调用虚函数（虚表槽 +1320）
  }
  if ( this == pArg2 )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
  if ( (uint32_t *)*(this + 2184) == pArg2 )
    *(this + 2184) = 0;
  return sub_4D9170(pArg2);  // 调 消亡通知
}



// AI 相位辅助（63L）
// ------------------------------------------------------------
// 0x5C6B50 sub_5C6B50 —— 替身目标追击/施放分派（无替身尾转 vt+1308）
//   行为字 this[1787] 按 this[1813] 标志在 4 与 13 间双向切换（vt+1104 写入）；
//   有替身 this[2184] 时以 vt+8 距离对 sub_4D8FE0 索敌上限比较：≤50 走 setState(15) 施放，
//   50 至上限经 vt+1144 追击，超出上限 setState(16) 钻地；无替身则尾转 vt+1308。【分段阈值推断】
// ------------------------------------------------------------
int /*usercall*/ sub_5C6B50@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：替身目标追击/施放分派（无替身尾转 vt+1308）
{
  int result; // eax
  int v4; // edi
  int v5; // ebx
  int pObj; // edi
  int v7; // eax
  int v8; // eax

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( pArg1[1787] )  // 按 pArg1[1787] 分派
  {
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( pArg1[1813] == 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 13);  // 调用虚函数（虚表槽 +1104）
      break;
    case 0xD:
    case 0xE:
    case 0xF:
      if ( pArg1[1813] != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 4);  // 调用虚函数（虚表槽 +1104）
      break;
    default:
      break;
  }
  if ( pArg1[2184] == 0 )
    __asm { jmp     dword ptr [eax+51Ch] }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*pArg1 + 8))(pArg1, pArg1[2184], 0, nArg3);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
    result = sub_4D8FE0(pArg1);  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
    if ( v4 < result )
    {
      if ( v4 > 50 )
      {
        if ( pArg1[1787] != 25 )
        {
          v5 = *pArg1;
          pObj = pArg1[2184];
          v7 = (*(int (/*cdecl*/ **)(int))(*(uint32_t *)pObj + 124))(nArg2);  // 调用虚函数（虚表槽 +124）
          v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v7);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          return (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 1144))(pArg1, v8);  // 调用虚函数（虚表槽 +1144）
        }
      }
      else
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      }
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 16, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C6BE0 sub_5C6BE0 —— 行为字 7 分流
//   行为字 this[1787]==7（悬浮/待机段）时走通用分派 sub_4E0120，否则转发 ·0x5C6B50。
// ------------------------------------------------------------
int /*usercall*/ sub_5C6BE0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：行为字 7 分流
{
  if ( pArg1[1787] == 7 )
    return sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  else
    return sub_5C6B50(pArg1, nArg2, nArg3);  // 调 替身目标追击/施放分派（无替身尾转 vt+1308）
}



// 时钟门+插值 AI（sub_699000+sub_4049C0, 55L）
// ------------------------------------------------------------
// 0x5C6C00 sub_5C6C00 —— 出土传送淡入控时
//   先 sub_4D8F90 基类转发垫片；主状态镜像 this[1639]==19（出土传送）时算
//   clock_now 减 this[2185]（出土时刻）得耗时：<1500ms 由 sub_4049C0 线性插值 alpha 0→255，
//   经 sub_491690 对 vt+200 对象的 +204 子链逐项施加；≥1500ms 走 vt+316 收束，未亮则 vt+312(0)。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C6C00(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 函数: 出土传送淡入控时
{
  uint32_t *pThis; // esi
  unsigned int result; // eax
  int v7; // ebx
  int v8; // edi
  uint32_t **v9; // eax
  uint32_t *v10; // esi
  unsigned int v12; // [esp+20h] [ebp+14h]

  pThis = this;
  result = sub_4D8F90(nArg2, nArg3, nArg4, nArg5);  // 调 vmt144 转发垫片（IRDActiveObject__vmt144 族）
  if ( (uint8_t)nArg2 == 0 && pThis[1639] == 19 )
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 200))(pThis);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    result = sub_699000((int)(pThis + 2)) - pThis[2185];  // 【clock_now(clk)】
    v12 = result;
    if ( v7 != 0 )
    {
      if ( result >= 0x5DC )
      {
LABEL_9:
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 316))(pThis);  // 调用虚函数（虚表槽 +316）
        if ( (uint8_t)result == 0 )
          return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pThis + 312))(pThis, 0);  // 虚函数调用 槽+312：濒死/一击表现（LAST STRIKE；死亡链上游）【新发现(会话 3)】
        return result;
      }
      v8 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 255.0, result, 1500) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      sub_491690(1, 5, 1, -1, v8, 1);  // 调 图层后处理配置（this+176..196 图层参数块写入）
      v9 = *(uint32_t ***)(v7 + 204);
      v10 = *v9;
      if ( *v9 != v9 )
      {
        do
        {
          sub_491690(1, 5, 1, -1, v8, 1);  // 调 图层后处理配置（this+176..196 图层参数块写入）
          v10 = (uint32_t *)*v10;
        }
        while ( v10 != *(uint32_t **)(v7 + 204) );
      }
      result = v12;
      pThis = this;
    }
    if ( result < 0x5DC )
      return result;
    goto LABEL_9;
  }
  return result;
}



// 时钟门+插值 AI（this+200 相位）
// ------------------------------------------------------------
// 0x5C6D00 sub_5C6D00 —— 蓝色闪光第二段计时
//   转发 ·0x5C6C00；行为字 this[1787]==7 且 vt+200 有效时按 clock_now 减 this[2186] 在 700ms 内
//   由 sub_4049C0(100→220) 取量并对 sub_491690 发蓝通道项（掩码 0xFF0000FF）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C6D00(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 函数: 蓝色闪光第二段计时
{
  unsigned int result; // eax
  unsigned int fld_e2186; // eax
  uint64_t v8; // rax

  result = sub_5C6C00(this, nArg2, nArg3, nArg4, nArg5);  // 调 出土传送淡入控时
  if ( (uint8_t)nArg2 == 0 )
  {
    if ( *(this + 1787) == 7 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) != 0 )  // this+7148 = nBigState
    {
      fld_e2186 = sub_699000((int)(this + 9)) - *(this + 2186);  // 【clock_now(clk)】
      if ( fld_e2186 >= 0x2BC )
        LOBYTE(v8) = -36;  // 调 取 16 位值低 8 位
      else
        v8 = (uint64_t)sub_4049C0(100.0, 220.0, fld_e2186, 700);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      sub_491690(1, 2, 1, -16776961, ((uint8_t)v8 << 24) | 0xFFFFFF, 1);  // 调 图层后处理配置（this+176..196 图层参数块写入）
    }
    return sub_5C6C00(this, 0, nArg3, nArg4, nArg5);  // 调 出土传送淡入控时
  }
  return result;
}



// 复合字段（this+200/568/8700..8732 —— +568=最后受击时刻, 研究 20 §1.2）
// ------------------------------------------------------------
// 0x5C6DC0 sub_5C6DC0 —— 攻击段表现驱动
//   姿态 vt+840==8、段索引 this[7028] 落在 this+8720 阈值表内、且 vt+200 的 +148 计数达到表内阈值时，
//   从 this+8700 的 std::string 表（28 字节/条）取段名交 vt+212 播报，this[8732] 作一次性门；
//   姿态 15 时校验 vt+308 与 vt+200 的 +170 标记后 setState(0) 收招。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C6DC0(int this)  // 函数: 攻击段表现驱动
{
  int fld_2210; // eax  | +0x2210 → 【推断】段阈值表首针〔5C6DC0：与 7028 段索引/帧计数 +148 比对〕（CNSpirit；va=005C6DC0）
  unsigned int fld_2214; // ebx  | +0x2214 → 【推断】段阈值表尾针（元素数=(8724-8720)>>2）〔5C6DC0〕（CNSpirit；va=005C6DC0）
  unsigned int pThis_1B74; // eax
  int pThis_94; // ebx
  unsigned int pThis_1B742; // ebx
  int pThis_1B743; // eax
  int fld_2200; // edx  | +0x2200 → 【推断】段名表数据指针（std::string 28 字节/条）〔5C6DC0 取段名交 vt+212 播报〕（CNSpirit；va=005C6DC0）
  unsigned int v9; // ecx
  int v10; // eax
  int v11; // eax

  sub_4E1780((uint32_t *)this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    fld_2210 = *(uint32_t *)(this + 8720);  // this+8720 【推断】段阈值表首针
    if ( fld_2210 != 0 )
      fld_2214 = (*(uint32_t *)(this + 8724) - fld_2210) >> 2;  // this+8724 【推断】段阈值表尾针
    else
      fld_2214 = 0;
    pThis_1B74 = sub_41A5E0(this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( fld_2214 > pThis_1B74 )
    {
      pThis_94 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      pThis_1B74 = *(uint32_t *)(this + 8720) + 4 * sub_41A5E0(this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( pThis_94 >= *(uint32_t *)pThis_1B74 )
      {
        LOBYTE(pThis_1B74) = *(uint8_t *)(this + 8732);  // 调 取 16 位值低 8 位
        if ( (uint8_t)pThis_1B74 == 0 )
        {
          pThis_1B742 = sub_41A5E0(this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
          pThis_1B74 = sub_52AEF0(this + 8700);  // 调 v10 = 插入数 + sub_52AEF0
          if ( pThis_1B74 > pThis_1B742 )
          {
            pThis_1B743 = 28 * sub_41A5E0(this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
            fld_2200 = *(uint32_t *)(this + 8704);  // this+8704 【推断】动态数组/表首指针
            v9 = *(uint32_t *)(pThis_1B743 + fld_2200 + 24);
            v10 = fld_2200 + pThis_1B743;
            if ( v9 < 0x10 )
              v11 = v10 + 4;
            else
              v11 = *(uint32_t *)(v10 + 4);
            LOBYTE(pThis_1B74) = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                           this,
                           v11,
                           -1,
                           0,
                           0);
          }
          *(uint8_t *)(this + 8732) = 1;  // this+8732 【推断】段名一次性门
        }
      }
    }
  }
  else
  {
    pThis_1B74 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    if ( pThis_1B74 == 15 )
    {
      LOBYTE(pThis_1B74) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)pThis_1B74 != 0 )
      {
        pThis_1B74 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        if ( *(uint8_t *)(pThis_1B74 + 170) != 0 )
          LOBYTE(pThis_1B74) = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
                         this,
                         0,
                         0,
                         0,
                         0);
      }
    }
  }
  return pThis_1B74;
}



// 字段访问（this+200/8744）
// ------------------------------------------------------------
// 0x5C6EE0 sub_5C6EE0 —— 段 1 附加触发门
//   姿态 8、段索引 7028==1、this[2186]（行为字 7 时刻戳）为 0 且 vt+200 的 +148 计数非空时，
//   触发 sub_5C63E0；随后统一交 ·0x5C6DC0 走段表现。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C6EE0(uint8_t *this)  // 函数: 段 1 附加触发门
{
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && sub_41A5E0((unsigned int)(this + 7028)) == 1  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    && *(this + 8744) == 0  // this+8744 【推断】主倒计时截止
    && *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148) > 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  {
    sub_5C63E0(this);
  }
  return sub_5C6DC0((int)this);  // 调 攻击段表现驱动
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5C6F30 sub_5C6F30 —— 行为字 7 进入门
//   行为字非 7 且 vt+736 值降到 vt+740 的 15% 以下（动画/进度比阈值）时写行为字 7，
//   并把 clock_now 记入 this[2186]（供 ·0x5C6D00 蓝闪计时）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C6F30(uint32_t *this)  // 函数: 行为字 7 进入门
{
  float v3; // [esp+4h] [ebp-8h]

  if ( *(this + 1787) != 7 )  // this+7148 = nBigState
  {
    v3 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
    if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * 0.15000001 >= v3 )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 7);  // 调用虚函数（虚表槽 +1104）
      *(this + 2186) = sub_699000((int)(this + 9));  // this+36 = 状态字
    }
  }
  return sub_5C6DC0((int)this);  // 调 攻击段表现驱动
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C6FA0 sub_5C6FA0 —— 大状态进入副作用（行为字 7）
//   转发 sub_4DBA80 进入处理器；nArg2==7 时把 this[1905] 所指状态块首字节清 0、块 +32 处置 1
//   （与 ·0x5C6FD0 的还原对偶）。【+7620 块语义推断】
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5C6FA0(uint8_t **this, int nArg2)  // 函数: 大状态进入副作用（行为字 7）
{
  uint8_t *result; // eax

  result = (uint8_t *)sub_4DBA80(nArg2);  // 调 大状态进入副作用处理器（增益侧）
  if ( nArg2 == 7 )
  {
    **(this + 1905) = 0;  // this+7620 = 速度/属性参数对象
    result = *(this + 1905) + 32;  // this+7620 = 速度/属性参数对象
    *result = 1;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C6FD0 sub_5C6FD0 —— 大状态退出副作用（行为字 7）
//   转发 sub_4DBC20；nArg2==7 时把同一 +7620 块首字节置 1、块 +32 处清 0——·0x5C6FA0 的逆操作。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5C6FD0(uint8_t **this, int nArg2)  // 函数: 大状态退出副作用（行为字 7）
{
  uint8_t *result; // eax

  result = (uint8_t *)sub_4DBC20(nArg2);  // 调 大状态退出副作用处理器（0x4DBA80 的还原对偶）
  if ( nArg2 == 7 )
  {
    **(this + 1905) = 1;  // this+7620 = 速度/属性参数对象
    result = *(this + 1905) + 32;  // this+7620 = 速度/属性参数对象
    *result = 0;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C7000 sub_5C7000 —— 出场参数换算入 vt+688
//   取 vt+384（出场参数面）乘 0.01 经 vt+688 写入（控制器参数），尾调 sub_4EB2C0(0.0)
//   重置某浮点累加器。【·0x5C88C0 事件 15 亦读 vt+688 的 +56】
// ------------------------------------------------------------
int /*thiscall*/ sub_5C7000(void *this)  // 函数: 出场参数换算入 vt+688
{
  float pThis_180; // [esp+4h] [ebp-4h]

  pThis_180 = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 384))(this) * 0.0099999998;  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 688))(this, LODWORD(pThis_180));  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
  return sub_4EB2C0(0.0);  // 调 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
}



// 属性精灵·夺取召唤物（100L）：扫场景存活对象(17)，只处理异阵营(vt+376 房间号不同)者——
//   清空其 vt+700 召唤物列表(逐个 vt+76 激活)、再扫其 16 个槽位中类型 16 的挂载物
//   重新绑定宿主为自己(vt+4(0,this))；有绑定成功则调 vt+956 生效
// ------------------------------------------------------------
// 0x5C7040 sub_5C7040 —— 夺舍执行体（段 0 门后调用）
//   仅在异房间号（vt+376 不同）时下手：先将其 vt+700 列表内各项经 vt+76 解除激活，
//   再扫 16 个挂载槽（vt+772/vt+776 + sub_496F80 类型 16）逐个 vt+4(0,this) 改绑本体，
//   有改绑则 vt+956 生效；调用点见 ·0x5C71C0 段 0 且 +148 计数 ≥8。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C7040(uint32_t *this)  // 函数: 夺舍执行体（段 0 门后调用）
{
  uint32_t *pThis; // ebx
  unsigned int i; // esi
  int pVecHdr; // ecx
  int pVecBegin; // edx
  int result; // eax
  int pVecHdr2; // edx
  int pScanObj; // edi
  int pListVec; // eax
  int pListVecB; // ebx
  int pVecBegin2; // ecx
  unsigned int nListIdx; // esi
  int pVecBegin3; // ecx
  int pListObj; // ecx
  int pVecBegin4; // ecx
  int pListObj2; // ecx
  int j; // esi
  int pSlotObj; // eax
  unsigned int nIdxSaved; // [esp+10h] [ebp-Ch]
  int nObjRoom; // [esp+14h] [ebp-8h]
  int nBoundCnt; // [esp+14h] [ebp-8h]
  int nListCnt; // [esp+18h] [ebp-4h]

  pThis = this;
  for ( i = 0; ; ++i )
  {
    pVecHdr = pThis[29];
    pVecBegin = *(uint32_t *)(pVecHdr + 8);
    nIdxSaved = i;
    result = pVecBegin != 0 ? (*(uint32_t *)(pVecHdr + 12) - pVecBegin) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;
    pVecHdr2 = *(uint32_t *)(pVecHdr + 8);
    if ( pVecHdr2 != 0 && i < (*(uint32_t *)(pVecHdr + 12) - pVecHdr2) >> 2 )  // 向量元素数 = (end−begin)/4
      pScanObj = *(uint32_t *)(pVecHdr2 + 4 * i);
    else
      pScanObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pScanObj + 40))(pScanObj, 17) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      nObjRoom = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pScanObj + 376))(pScanObj);  // 调用虚函数（虚表槽 +376）
      if ( nObjRoom != (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis) )  // 调用虚函数（虚表槽 +376）
      {
        pListVec = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pScanObj + 700))(pScanObj);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
        pListVecB = pListVec;
        pVecBegin2 = *(uint32_t *)(pListVec + 4);
        nListIdx = 0;
        if ( pVecBegin2 != 0 )
          nListCnt = (*(uint32_t *)(pListVec + 8) - pVecBegin2) >> 2;  // 向量元素数 = (end−begin)/4
        else
          nListCnt = 0;
        nBoundCnt = 0;
        if ( nListCnt > 0 )
        {
          do
          {
            pVecBegin3 = *(uint32_t *)(pListVecB + 4);
            if ( pVecBegin3 != 0 && nListIdx < (*(uint32_t *)(pListVecB + 8) - pVecBegin3) >> 2 )  // 向量元素数 = (end−begin)/4
              pListObj = *(uint32_t *)(pVecBegin3 + 4 * nListIdx);
            else
              pListObj = 0;
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pListObj + 92))(pListObj) != 0 )  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
            {
              pVecBegin4 = *(uint32_t *)(pListVecB + 4);
              if ( pVecBegin4 != 0 && nListIdx < (*(uint32_t *)(pListVecB + 8) - pVecBegin4) >> 2 )  // 向量元素数 = (end−begin)/4
                pListObj2 = *(uint32_t *)(pVecBegin4 + 4 * nListIdx);
              else
                pListObj2 = 0;
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pListObj2 + 76))(pListObj2, 0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
            }
            ++nListIdx;
          }
          while ( (int)nListIdx < nListCnt );
        }
        for ( j = 0; j < 16; ++j )  // 循环：j 从 0 递增到 16
        {
          if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pScanObj + 772))(pScanObj, j) != 0  // 调用虚函数（虚表槽 +772）【推断: [RTTI: IRDActiveObject__vmt304 ·…】
            && sub_496F80(j) == 16  // 调 状态号映射表（12 直通、15→14、16→15，其余→16）
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pScanObj + 776))(pScanObj, j) != 0 )  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
          {
            pSlotObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pScanObj + 772))(pScanObj, j);  // 调用虚函数（虚表槽 +772）【推断: [RTTI: IRDActiveObject__vmt304 ·…】
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t *))(*(uint32_t *)pSlotObj + 4))(pSlotObj, 0, this);  // 调用虚函数（虚表槽 +4）
            ++nBoundCnt;
          }
        }
        if ( nBoundCnt > 0 )
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pScanObj + 956))(pScanObj);  // 调用虚函数（虚表槽 +956）
        i = nIdxSaved;
      }
    }
    pThis = this;
  }
  return result;
}



// AI 字段访问（this+8748）
// ------------------------------------------------------------
// 0x5C71C0 sub_5C71C0 —— 段门调度（主状态 8）
//   主状态镜像 this[6556]==8 时按段索引 7028（减 2）分派：段 2 且 this[8748] 置位→清标志转
//   ·0x5C6F30；段 0 且 vt+120 的 +148 计数 ≥8 且标志置位→·0x5C7040 夺舍后清标志；
//   尾调 ·0x5C6F30 统一进入行为字 7 门。【段号语义推断】
// ------------------------------------------------------------
char /*thiscall*/ sub_5C71C0(int this)  // 函数: 段门调度（主状态 8）
{
  int fld_78; // edi  | +0x0078 → 动画对象指针（CNSoulEter；va=00499020）
  int pThis_1B74; // eax

  fld_78 = *(uint32_t *)(*(uint32_t *)(this + 120) + 148);  // this+120 动画对象指针
  if ( *(uint32_t *)(this + 6556) == 8 )  // this+6556 主状态镜像
  {
    pThis_1B74 = sub_41A5E0(this + 7028) - 2;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( pThis_1B74 != 0 )
    {
      if ( pThis_1B74 == 1 && *(uint8_t *)(this + 8748) != 0 )  // this+8748 子类 AI 尾部槽
      {
        *(uint8_t *)(this + 8748) = 0;  // this+8748 子类 AI 尾部槽
        return sub_5C6F30((uint32_t *)this);  // 调 行为字 7 进入门
      }
    }
    else if ( *(uint8_t *)(this + 8748) != 0 && fld_78 >= 8 )  // this+8748 子类 AI 尾部槽
    {
      sub_5C7040((uint32_t *)this);  // 调 夺舍执行体（段 0 门后调用）
      *(uint8_t *)(this + 8748) = 0;  // this+8748 子类 AI 尾部槽
    }
  }
  return sub_5C6F30((uint32_t *)this);  // 调 行为字 7 进入门
}



// 语音注册（sub_4015C0; 23L）
// ------------------------------------------------------------
// 0x5C7230 sub_5C7230 —— vector 溢出异常抛出（noreturn）
//   sub_4015C0 构造「vector<T> too long」后 sub_401740 组装 std::length_error 对象并
//   _CxxThrowException 抛出；仅由 ·0x5C72A0 容量上界检查失败时进入。
// ------------------------------------------------------------
void /*noreturn*/ sub_5C7230()  // 函数: vector 溢出异常抛出（noreturn）
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
  sub_401740(v1);  // 调 std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消…
  pExceptionObject = &std::length_error::`vftable';  // vftable 复位
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// AI 相位辅助（112L）
// ------------------------------------------------------------
// 0x5C72A0 sub_5C72A0 —— 三指针容器插入/扩容（vector<uint32_t> 实例）
//   this+4/+8/+12 为 begin/end/cap，元素 4 字节；uArg3 个元素的批量插入：尾部有余量则
//   sub_55E7F0 后移 + sub_5DAF70 搬迁 + sub_49A9D0 填值，否则按 1.5 倍或所需值经 operator new
//   重分配、memcpy_0 搬迁并 j__free 旧块；上界 0x3FFFFFFF 溢出转 ·0x5C7230 抛异常。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C72A0(int this, int Src, unsigned int uArg3, int *pDwArg4)  // 函数: 三指针容器插入/扩容（vector<uint32_t> 实例）
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

  fld_4 = *(uint32_t *)(this + 4);  // this+4 宿主对象
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;  // this+12 物品类型号
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_5C7230(this);  // 调 vector 溢出异常抛出（noreturn）
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
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
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // 调 商城状态（10 行）
        sub_5DAF70((void *)Src, v24, v29);  // 调 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推得，尾段整体后移一格
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // 调 区间填充（逐 uint32 写同值）
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // 调 商城状态（10 行）
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // 调 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];  // this+8 物品 id
        *(uint32_t *)(this + 8) = fld_84;  // this+8 物品 id
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // 调 区间填充（逐 uint32 写同值）
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( fld_4 != 0 )
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
        else
          fld_86 = 0;
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);  // this+4 宿主对象
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+4 宿主对象
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // 调 填充补足尾段
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));  // this+8 物品 id
      fld_43 = *(uint32_t *)(this + 4);  // this+4 宿主对象
      if ( fld_43 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8 物品 id
      else
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));  // 调 堆释放
      *(uint32_t *)(this + 12) = &pMem[v28];  // this+12 物品类型号
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // this+8 物品 id
      *(uint32_t *)(this + 4) = pMem;  // this+4 宿主对象
      return (unsigned int)pMem;
    }
  }
  return result;
}



// 献祭攻击：Particle/NaiasSacrificeAttack.ptl（100L；sub_47EF20 数据表读数 ——
//   水精灵 Naias 献祭爆【推断】）
// ------------------------------------------------------------
// 0x5C7480 sub_5C7480 —— 献祭弹群生成（42007 通道）
//   sub_47E720(3,49) 取模板、sub_47EF20(1/3,…) 读参数表后，逐目标以 sub_4B3C90(v18,1) 生成
//   0x7C 字节子对象（vt+120 写 5/26），经 vt+56 以 (目标, this[2088] 宿主, 19 类型) 投放；
//   nArg3>0 且宿主非空时向 0..315 每 45 度方位发 Particle/NaiasSacrificeAttack.ptl
//   （sub_47EFD0 打包 + sub_4E4C10 通道 42007）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C7480(unsigned int *this, int nArg2, int nArg3, unsigned int pArg4)  // 函数: 献祭弹群生成（42007 通道）
{
  uint32_t *v5; // edi
  unsigned int i; // ebx
  unsigned int result; // eax
  int v8; // ecx
  int pObj; // edi
  char *v10; // eax
  bool v11; // cc
  uint32_t *v12; // edi
  int j; // ebx
  int fld_e2088; // eax  | +0x20A0 → 骑乘/宿主槽〔通用偏移表 this+8352〕（CNNaias；va=004D94A0）
  int v15; // eax
  int v16; // [esp+10h] [ebp-14h]
  char *v17; // [esp+10h] [ebp-14h]
  int v18; // [esp+14h] [ebp-10h]
  int fld_e20882; // [esp+14h] [ebp-10h]  | +0x20A0 → 骑乘/宿主槽〔通用偏移表 this+8352〕（CNNaias；va=004D94A0）
  float v20; // [esp+2Ch] [ebp+8h]
  int dword_78FE2C2; // [esp+2Ch] [ebp+8h]
  float v22; // [esp+34h] [ebp+10h]
  float v23; // [esp+34h] [ebp+10h]
  int dword_78FE282; // [esp+34h] [ebp+10h]

  v5 = (uint32_t *)sub_47E720(3, 49);  // 调 调 sub_47E720
  v18 = sub_47EF20(1, nArg2, -1, -1, 11);  // 调 读攻击数据表
  v20 = (float)(int)sub_47EF20(3, nArg2, -1, -1, 11);  // 调 读攻击数据表
  v16 = sub_47E9D0(v5, 1u);  // 调 收招/结束例程
  for ( i = 0; ; ++i )
  {
    result = pArg4;
    v8 = *(uint32_t *)(pArg4 + 4);  // pArg4+4〔宿主对象〕
    if ( v8 == 0 )
      break;
    result = (*(uint32_t *)(pArg4 + 8) - v8) >> 2;  // pArg4+8〔nSkillRec8(推断)〕
    if ( i >= result )
      break;
    pObj = 0;
    if ( operator new(0x7Cu) != nullptr )  // operator new 分配 124 字节
      pObj = sub_4B3C90(v18, 1);  // 调 CNChangeStatus 构造（双参）
    (*(void (/*thiscall*/ **)(int, int, uint32_t, float))(*(uint32_t *)pObj + 120))(pObj, 5, 0, COERCE_FLOAT(LODWORD(v20)));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    (*(void (/*thiscall*/ **)(int, int, uint32_t, float))(*(uint32_t *)pObj + 120))(pObj, 26, 0, COERCE_FLOAT(LODWORD(v20)));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, uint32_t, int, int))(*(uint32_t *)pObj + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
      pObj,
      *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4 * i),
      *(this + 2088),  // this+8352 = 骑乘/宿主槽
      1,
      0,
      19,
      v16);
  }
  if ( nArg3 > 0 )
  {
    result = *(this + 2088);  // this+8352 = 骑乘/宿主槽
    if ( result != 0 )  // 若结果非 0（成功）
    {
      v10 = (char *)sub_47E720(3, 52);  // 调 调 sub_47E720
      dword_78FE2C = 0;
      *(uint16_t *)dword_78FE28 = 100;
      v11 = dword_78FE2C + 2 <= *(uint32_t *)dword_78FE24;
      v17 = v10;
      dword_78FE2C += 2;
      if ( !v11 )
        off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
      v22 = (double)(int)sub_47EF20(2, nArg3, -1, -1, 11) * 0.1;  // 调 读攻击数据表
      *(float *)(dword_78FE28 + dword_78FE2C) = v22;
      dword_78FE2C += 4;
      if ( dword_78FE2C > *(int *)dword_78FE24 )
        off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
      v23 = (float)(int)sub_47EF20(3, nArg3, -1, -1, 11);  // 调 读攻击数据表
      *(float *)(dword_78FE28 + dword_78FE2C) = v23;
      dword_78FE2C += 4;
      if ( dword_78FE2C > *(int *)dword_78FE24 )
        off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
      v12 = (uint32_t *)(*(int (/*thiscall*/ **)(unsigned int *, const char *))(*this + 588))(  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
                        this,
                        "Particle/NaiasSacrificeAttack.ptl");  // 资源路径 Particle/NaiasSacrificeAttack.ptl
      *(uint32_t *)((char *)v12 + 85) = sub_47EF20(0, nArg3, -1, -1, 11);  // 调 读攻击数据表
      for ( j = 0; j < 360; j += 45 )
      {
        *v12 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        v12[1] = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
        v12[2] = 0;
        v12[18] = j;
        dword_78FE282 = dword_78FE28;
        dword_78FE2C2 = dword_78FE2C;
        fld_e2088 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2088) + 388))(*(this + 2088));  // this+8352 = 骑乘/宿主槽
        fld_e20882 = *(this + 2088);  // this+8352 = 骑乘/宿主槽
        v15 = sub_47EFD0(v17, COERCE_FLOAT(1), nArg3, fld_e2088, fld_e2088, 0);
        result = sub_4E4C10(fld_e20882, 42007, v15, v12, 0, 0, dword_78FE2C2, dword_78FE282);  // 调 与 ·0x4E4A50 同构（差异：上下文使能位固定 1 + 数据块打包）
      }
    }
  }
  return result;
}



// 数据表读数 AI（sub_47EF20, 95L）
// ------------------------------------------------------------
// 0x5C7750 sub_5C7750 —— 弹幕群发射（40002 通道）
//   与 ·0x5C7480 同构家族（同为 sub_47E720/sub_47EF20/sub_47EFD0 链）：差异为无 .ptl 资源、
//   子对象参数写 1、vt+56 类型 18，弹幕表由 sub_47E720(3,51) 取，末经 sub_4E4A50 通道 40002
//   以本体坐标 + vt+192/2 高度发射。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C7750(int *this, int nArg2, int nArg3, unsigned int pArg4)  // 函数: 弹幕群发射（40002 通道）
{
  uint32_t *v5; // edi
  unsigned int i; // ebx
  unsigned int result; // eax
  int v8; // ecx
  int pObj; // edi
  char *v10; // edi
  int fld_e2088; // eax  | +0x20A0 → 骑乘/宿主槽〔通用偏移表 this+8352〕（CNAdor；va=004D94A0）
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // [esp-18h] [ebp-3Ch]
  int v16; // [esp-14h] [ebp-38h]
  int v17; // [esp-10h] [ebp-34h]
  int v18; // [esp+10h] [ebp-14h]
  int v19; // [esp+14h] [ebp-10h]
  float v20; // [esp+2Ch] [ebp+8h]
  int dword_78FE2C2; // [esp+2Ch] [ebp+8h]
  int fld_e20882; // [esp+30h] [ebp+Ch]  | +0x20A0 → 骑乘/宿主槽〔通用偏移表 this+8352〕（CNAdor；va=004D94A0）
  float v23; // [esp+34h] [ebp+10h]
  float v24; // [esp+34h] [ebp+10h]
  int dword_78FE282; // [esp+34h] [ebp+10h]

  v5 = (uint32_t *)sub_47E720(3, 49);  // 调 调 sub_47E720
  v19 = sub_47EF20(1, nArg2, -1, -1, 11);  // 调 读攻击数据表
  v20 = (float)(int)sub_47EF20(2, nArg2, -1, -1, 11);  // 调 读攻击数据表
  v18 = sub_47E9D0(v5, 1u);  // 调 收招/结束例程
  for ( i = 0; ; ++i )
  {
    result = pArg4;
    v8 = *(uint32_t *)(pArg4 + 4);  // pArg4+4〔宿主对象〕
    pObj = 0;
    if ( v8 == 0 )
      break;
    result = (*(uint32_t *)(pArg4 + 8) - v8) >> 2;  // pArg4+8〔nSkillRec8(推断)〕
    if ( i >= result )
      break;
    if ( operator new(0x7Cu) != nullptr )  // operator new 分配 124 字节
      pObj = sub_4B3C90(v19, 1);  // 调 CNChangeStatus 构造（双参）
    (*(void (/*thiscall*/ **)(int, int, uint32_t, float))(*(uint32_t *)pObj + 120))(pObj, 1, 0, COERCE_FLOAT(LODWORD(v20)));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, uint32_t, int, int))(*(uint32_t *)pObj + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
      pObj,
      *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4 * i),
      *(this + 2088),  // this+8352 = 骑乘/宿主槽
      1,
      0,
      18,
      v18);
  }
  if ( nArg3 > 0 && *(this + 2088) != 0 )  // this+8352 = 骑乘/宿主槽
  {
    v10 = (char *)sub_47E720(3, 51);  // 调 调 sub_47E720
    dword_78FE2C = 0;
    *(uint16_t *)dword_78FE28 = sub_47EF20(0, nArg3, -1, -1, 11);  // 调 读攻击数据表
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
    *(uint16_t *)(dword_78FE28 + dword_78FE2C) = 0;
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
    *(uint8_t *)(dword_78FE28 + dword_78FE2C++) = 9;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
    v23 = (double)(int)sub_47EF20(2, nArg3, -1, -1, 11) * 0.1;  // 调 读攻击数据表
    *(float *)(dword_78FE28 + dword_78FE2C) = v23;
    dword_78FE2C += 4;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
    v24 = (float)(int)sub_47EF20(3, nArg3, -1, -1, 11);  // 调 读攻击数据表
    *(float *)(dword_78FE28 + dword_78FE2C) = v24;
    dword_78FE2C += 4;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
    dword_78FE282 = dword_78FE28;
    dword_78FE2C2 = dword_78FE2C;
    fld_e2088 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2088) + 388))(*(this + 2088));  // this+8352 = 骑乘/宿主槽
    v12 = sub_47EFD0(v10, COERCE_FLOAT(1), nArg3, fld_e2088, fld_e2088, 0);
    fld_e20882 = *(this + 2088);  // this+8352 = 骑乘/宿主槽
    v17 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v13 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this) / 2;  // 调用虚函数（虚表槽 +192）
    v16 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + v13;  // 调用虚函数（虚表槽 +128）
    v15 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
    v14 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    return sub_4E4A50(fld_e20882, 40002, v12, v14, v15, v16, v17, 0, dword_78FE2C2, dword_78FE282);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
  }
  return result;
}



// 数据表读数 AI（sub_47EF20, 95L）
// ------------------------------------------------------------
// 0x5C7A60 sub_5C7A60 —— 弹幕群发射（44001 通道）
//   与 ·0x5C7750 同构（差异：参数表 sub_47EF20(4,…) 乘 0.1 作 v20、子对象 vt+120 写 12、
//   vt+56 类型 20、弹幕表 sub_47E720(3,53)、末发通道 44001）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C7A60(int *this, int nArg2, int nArg3, unsigned int pArg4)  // 函数: 弹幕群发射（44001 通道）
{
  uint32_t *v5; // edi
  unsigned int i; // ebx
  unsigned int result; // eax
  int v8; // ecx
  int pObj; // edi
  char *v10; // edi
  int fld_e2088; // eax  | +0x20A0 → 骑乘/宿主槽〔通用偏移表 this+8352〕（CNStalker；va=004D94A0）
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // [esp-18h] [ebp-3Ch]
  int v16; // [esp-14h] [ebp-38h]
  int v17; // [esp-10h] [ebp-34h]
  int v18; // [esp+10h] [ebp-14h]
  int v19; // [esp+14h] [ebp-10h]
  float v20; // [esp+2Ch] [ebp+8h]
  int dword_78FE2C2; // [esp+2Ch] [ebp+8h]
  int fld_e20882; // [esp+30h] [ebp+Ch]  | +0x20A0 → 骑乘/宿主槽〔通用偏移表 this+8352〕（CNStalker；va=004D94A0）
  float v23; // [esp+34h] [ebp+10h]
  float v24; // [esp+34h] [ebp+10h]
  int dword_78FE282; // [esp+34h] [ebp+10h]

  v5 = (uint32_t *)sub_47E720(3, 49);  // 调 调 sub_47E720
  v19 = sub_47EF20(1, nArg2, -1, -1, 11);  // 调 读攻击数据表
  v20 = (double)(int)sub_47EF20(4, nArg2, -1, -1, 11) * 0.1;  // 调 读攻击数据表
  v18 = sub_47E9D0(v5, 1u);  // 调 收招/结束例程
  for ( i = 0; ; ++i )
  {
    result = pArg4;
    v8 = *(uint32_t *)(pArg4 + 4);  // pArg4+4〔宿主对象〕
    pObj = 0;
    if ( v8 == 0 )
      break;
    result = (*(uint32_t *)(pArg4 + 8) - v8) >> 2;  // pArg4+8〔nSkillRec8(推断)〕
    if ( i >= result )
      break;
    if ( operator new(0x7Cu) != nullptr )  // operator new 分配 124 字节
      pObj = sub_4B3C90(v19, 1);  // 调 CNChangeStatus 构造（双参）
    (*(void (/*thiscall*/ **)(int, int, uint32_t, float))(*(uint32_t *)pObj + 120))(pObj, 12, 0, COERCE_FLOAT(LODWORD(v20)));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, uint32_t, int, int))(*(uint32_t *)pObj + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
      pObj,
      *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4 * i),
      *(this + 2088),  // this+8352 = 骑乘/宿主槽
      1,
      0,
      20,
      v18);
  }
  if ( nArg3 > 0 && *(this + 2088) != 0 )  // this+8352 = 骑乘/宿主槽
  {
    v10 = (char *)sub_47E720(3, 53);  // 调 调 sub_47E720
    dword_78FE2C = 0;
    *(uint16_t *)dword_78FE28 = sub_47EF20(0, nArg3, -1, -1, 11);  // 调 读攻击数据表
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
    *(uint16_t *)(dword_78FE28 + dword_78FE2C) = 0;
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
    *(uint8_t *)(dword_78FE28 + dword_78FE2C++) = 4;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
    v23 = (double)(int)sub_47EF20(2, nArg3, -1, -1, 11) * 0.1;  // 调 读攻击数据表
    *(float *)(dword_78FE28 + dword_78FE2C) = v23;
    dword_78FE2C += 4;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
    v24 = (float)(int)sub_47EF20(3, nArg3, -1, -1, 11);  // 调 读攻击数据表
    *(float *)(dword_78FE28 + dword_78FE2C) = v24;
    dword_78FE2C += 4;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);  // 调 off_77F3FC（引擎日志输出函数）
    dword_78FE282 = dword_78FE28;
    dword_78FE2C2 = dword_78FE2C;
    fld_e2088 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2088) + 388))(*(this + 2088));  // this+8352 = 骑乘/宿主槽
    v12 = sub_47EFD0(v10, COERCE_FLOAT(1), nArg3, fld_e2088, fld_e2088, 0);
    fld_e20882 = *(this + 2088);  // this+8352 = 骑乘/宿主槽
    v17 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v13 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this) / 2;  // 调用虚函数（虚表槽 +192）
    v16 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + v13;  // 调用虚函数（虚表槽 +128）
    v15 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
    v14 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    return sub_4E4A50(fld_e20882, 44001, v12, v14, v15, v16, v17, 0, dword_78FE2C2, dword_78FE282);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
  }
  return result;
}



// 数据表读数 AI（sub_47EF20, 99L）
// ------------------------------------------------------------
// 0x5C7D80 sub_5C7D80 —— 弹幕喷射 + 23019 锁定打击
//   与 ·0x5C7750 同构前段（差异：子对象 vt+120 写 8 与 7、vt+56 类型 21，弹幕表 sub_47E720(3,54)）；
//   nArg3>0 时改扫场景列表（this+29 的 +120/+124 面），对通过 sub_4E4630 敌我判定、vt+624 可击
//   且 vt+8 距离 ≤ 参数表阈值者，沿 vt+124/vt+120/vt+128 链解算 23019 号打击并 vt+584 落位到宿主。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C7D80(int *this, int nArg2, int nArg3, int pArg4)  // 函数: 弹幕喷射 + 23019 锁定打击
{
  uint32_t *v5; // esi
  unsigned int i; // ebx
  int result; // eax
  int v8; // ecx
  int pObj; // esi
  unsigned int j; // ebx
  int fld_e29; // ecx
  int v12; // edx
  int v13; // edx
  int pObj2; // esi
  int fld_e2088; // ebx  | +0x20A0 → 骑乘/宿主槽〔通用偏移表 this+8352〕（CNWisp；va=004D94A0）
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // [esp+10h] [ebp-14h]
  int fld_e20882; // [esp+10h] [ebp-14h]  | +0x20A0 → 骑乘/宿主槽〔通用偏移表 this+8352〕（CNWisp；va=004D94A0）
  int v24; // [esp+14h] [ebp-10h]
  float v25; // [esp+2Ch] [ebp+8h]
  int v26; // [esp+2Ch] [ebp+8h]
  unsigned int v27; // [esp+34h] [ebp+10h]

  v5 = (uint32_t *)sub_47E720(3, 49);  // 调 调 sub_47E720
  v24 = sub_47EF20(1, nArg2, -1, -1, 11);  // 调 读攻击数据表
  v25 = (double)(int)sub_47EF20(5, nArg2, -1, -1, 11) * 0.1;  // 调 读攻击数据表
  v22 = sub_47E9D0(v5, 1u);  // 调 收招/结束例程
  for ( i = 0; ; ++i )
  {
    result = pArg4;
    v8 = *(uint32_t *)(pArg4 + 4);  // pArg4+4〔宿主对象〕
    if ( v8 == 0 )
      break;
    result = (*(uint32_t *)(pArg4 + 8) - v8) >> 2;  // pArg4+8〔nSkillRec8(推断)〕
    if ( i >= result )
      break;
    pObj = 0;
    if ( operator new(0x7Cu) != nullptr )  // operator new 分配 124 字节
      pObj = sub_4B3C90(v24, 1);  // 调 CNChangeStatus 构造（双参）
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pObj + 120))(pObj, 8, 1, COERCE_FLOAT(LODWORD(v25)));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pObj + 120))(pObj, 7, 1, COERCE_FLOAT(LODWORD(v25)));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, uint32_t, int, int))(*(uint32_t *)pObj + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
      pObj,
      *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4 * i),
      *(this + 2088),  // this+8352 = 骑乘/宿主槽
      1,
      0,
      21,
      v22);
  }
  if ( nArg3 > 0 )
  {
    result = *(this + 2088);  // this+8352 = 骑乘/宿主槽
    if ( result != 0 )  // 若结果非 0（成功）
    {
      sub_47E720(3, 54);  // 调 调 sub_47E720
      v26 = sub_47EF20(0, nArg3, -1, -1, 11);  // 调 读攻击数据表
      for ( j = 0; ; ++j )
      {
        fld_e29 = *(this + 29);  // this+116〔会话上下文〕
        v12 = *(uint32_t *)(fld_e29 + 120);
        v27 = j;
        result = v12 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v12) >> 2 : 0;  // 向量元素数 = (end−begin)/4
        if ( (int)j >= result )
          break;
        v13 = *(uint32_t *)(fld_e29 + 120);
        if ( v13 != 0 && j < (*(uint32_t *)(fld_e29 + 124) - v13) >> 2 )  // 向量元素数 = (end−begin)/4
          pObj2 = *(uint32_t *)(v13 + 4 * j);
        else
          pObj2 = 0;
        if ( (uint8_t)sub_4E4630(pObj2) != 0  // 调 ★ 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
          && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 624))(pObj2) != 0  // 调用虚函数（虚表槽 +624）【推断: [RTTI: IRDActiveObject__vmt270 ·…】
          && (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, pObj2, 0) <= v26 )  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
        {
          fld_e2088 = *(uint32_t *)*(this + 2088);  // this+8352 = 骑乘/宿主槽
          fld_e20882 = *(this + 2088);  // this+8352 = 骑乘/宿主槽
          v16 = (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(*this + 152))(this, 250, 1, 0, 0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          v17 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)pObj2 + 124))(pObj2, 23019, nArg3, 0, v16);  // 调用虚函数（虚表槽 +124）
          v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v17);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 128))(pObj2, v18);  // 调用虚函数（虚表槽 +128）
          v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 124))(pObj2, v19);  // 调用虚函数（虚表槽 +124）
          v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v20);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          (*(void (/*thiscall*/ **)(int, int))(fld_e2088 + 584))(fld_e20882, v21);  // 调用虚函数（虚表槽 +584）【推断: ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6…】
          j = v27;
        }
      }
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C7FB0 sub_5C7FB0 —— 单元素尾部追加（this+4/+8/+12 容器）
//   同 ·0x5C72A0 的三指针容器：尾部有余量则直接写入 *pDwArg2 并让 this+8 前移，
//   否则转 ·0x5C72A0(this, end, 1, pDwArg2) 走扩容插入；调用者见 ·0x5C8000 候选表收集。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C7FB0(int *this, int *pDwArg2)  // 函数: 单元素尾部追加（this+4/+8/+12 容器）
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = *(this + 1);  // this+4 = pHostObj
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 2;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 2 )  // this+12 = 技能槽记录次字
    return sub_5C72A0((int)this, *(this + 2), 1u, pDwArg2);  // 调 三指针容器插入/扩容（vector<uint32_t> 实例）
  fld_e22 = (int *)*(this + 2);  // this+8 = 技能槽记录首字
  *fld_e22 = *pDwArg2;
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = result;  // this+8 = 技能槽记录首字
  return result;
}



// 属性精灵·传送集结（161L）：空闲且本地玩家门——扫场景标记 33 且类型 23001 的对象
//   （其他属性精灵）经 sub_5C7FB0 收集成候选表，取距自身最近者(vt+8 距离比较)，
//   最近距离 ≥ sub_4D8FE0(索敌上限) 则放弃；否则 vt+564 复位并把目标 X/Y 打包
//   setState(14) 传送过去
// ------------------------------------------------------------
// 0x5C8000 sub_5C8000 —— 传送集结（就地协防）
//   前置门：vt+308 可用且 vt+840 姿态为 0（空闲）；扫 this[29] 场景列表的 +120/+124 面，
//   收 vt+40(obj,33) 标记且 vt+340 类型 ==23001 的其他属性精灵为候选（经 ·0x5C7FB0 入表）；
//   取 vt+8 距离最近者，≥ sub_4D8FE0 索敌上限则放弃，否则 vt+564 复位后把目标 vt+48/vt+52
//   的 X/Y 打包 setState(14) 传送过去。
// ------------------------------------------------------------
char /*usercall*/ sub_5C8000@<al>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>)  // 实现：传送集结（就地协防）
{
  unsigned int nScanIdx; // esi
  uint32_t *pCandVec; // ebx
  int pVecHdr; // ecx
  int pVecBeginA; // edx
  int nCnt; // eax
  int pVecHdr2; // edx
  int pScanObj; // ecx
  int pVecHdr3; // ecx
  int pVecBegin; // edx
  int pScanObj2; // ecx
  int pVecHdr4; // ecx
  int pVecBegin2; // edx
  unsigned int nCandCnt; // eax
  int *pNearest; // esi
  unsigned int i; // ebx
  bool bCmp; // cf
  int pVt; // eax
  int nDist1; // eax
  int pVt2; // edx
  int nDist2; // eax
  int nMinDist; // ebx
  int pTargetVt; // eax
  char *nTgtX; // ebx
  int nTgtY; // ebx
  char *nTgtX2; // eax
  int nCandI; // [esp-10h] [ebp-4Ch]
  int v33; // [esp+4h] [ebp-38h] BYREF
  void *v34; // [esp+8h] [ebp-34h]
  int v35; // [esp+Ch] [ebp-30h]
  int v36; // [esp+10h] [ebp-2Ch]
  uint8_t v37[4]; // [esp+14h] [ebp-28h] BYREF
  void *Block; // [esp+18h] [ebp-24h]
  void *Src; // [esp+1Ch] [ebp-20h]
  int v40; // [esp+20h] [ebp-1Ch]
  int nCandCntSaved; // [esp+24h] [ebp-18h] BYREF
  int nDistMin; // [esp+28h] [ebp-14h]
  int pScanObj3; // [esp+2Ch] [ebp-10h] BYREF
  int v44; // [esp+38h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) == 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) != 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    return 0;
  }
  nScanIdx = 0;
  pCandVec = nullptr;
  v34 = nullptr;
  v35 = 0;
  v36 = 0;
  v44 = 0;
  while ( 1 )  // 无限循环
  {
    pVecHdr = pArg1[29];
    pVecBeginA = *(uint32_t *)(pVecHdr + 120);
    nCnt = pVecBeginA != 0 ? (*(uint32_t *)(pVecHdr + 124) - pVecBeginA) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)nScanIdx >= nCnt )
      break;
    pVecHdr2 = *(uint32_t *)(pVecHdr + 120);
    if ( pVecHdr2 != 0 && nScanIdx < (*(uint32_t *)(pVecHdr + 124) - pVecHdr2) >> 2 )  // 向量元素数 = (end−begin)/4
      pScanObj = *(uint32_t *)(pVecHdr2 + 4 * nScanIdx);
    else
      pScanObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pScanObj + 40))(pScanObj, 33) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      pVecHdr3 = pArg1[29];
      pVecBegin = *(uint32_t *)(pVecHdr3 + 120);
      if ( pVecBegin != 0 && nScanIdx < (*(uint32_t *)(pVecHdr3 + 124) - pVecBegin) >> 2 )  // 向量元素数 = (end−begin)/4
        pScanObj2 = *(uint32_t *)(pVecBegin + 4 * nScanIdx);
      else
        pScanObj2 = 0;
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pScanObj2 + 340))(pScanObj2) == 23001 )  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
      {
        pVecHdr4 = pArg1[29];
        pVecBegin2 = *(uint32_t *)(pVecHdr4 + 120);
        if ( pVecBegin2 != 0 && nScanIdx < (*(uint32_t *)(pVecHdr4 + 124) - pVecBegin2) >> 2 )  // 向量元素数 = (end−begin)/4
          pScanObj3 = *(uint32_t *)(pVecBegin2 + 4 * nScanIdx);
        else
          pScanObj3 = 0;
        sub_5C7FB0(&v33, &pScanObj3);  // 调 单元素尾部追加（this+4/+8/+12 容器）
        pCandVec = v34;
      }
    }
    ++nScanIdx;
  }
  if ( pCandVec == nullptr )  // 若 pCandVec 为空
    return 0;
  nCandCnt = (v35 - (int)pCandVec) >> 2;
  nCandCntSaved = nCandCnt;
  if ( nCandCnt == 0 )
  {
    j__free(pCandVec);  // 调 堆释放
    return 0;
  }
  pNearest = (int *)*pCandVec;
  for ( i = 1; ; ++i )
  {
    bCmp = i < nCandCnt;
    pVt = *pArg1;
    pScanObj3 = i;
    if ( !bCmp )
      break;
    nDist1 = (*(int (/*thiscall*/ **)(uint32_t *, int *, uint32_t))(pVt + 8))(pArg1, pNearest, 0);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
    pVt2 = *pArg1;
    nCandI = *((uint32_t *)v34 + i);
    nDistMin = nDist1;
    nDist2 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(pVt2 + 8))(pArg1, nCandI, 0);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
    if ( nDist2 < nDistMin )
      pNearest = *((int **)v34 + i);
    nCandCnt = nCandCntSaved;
  }
  nMinDist = (*(int (/*thiscall*/ **)(uint32_t *, int *, uint32_t))(pVt + 8))(pArg1, pNearest, 0);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
  if ( nMinDist >= sub_4D8FE0(pArg1) )  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
  {
    j__free(v34);  // 调 堆释放
    return 0;
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 564))(pArg1, nArg3, nArg2);  // 调用虚函数（虚表槽 +564）【推断: ★ 位移同步包 vt+234（会话 3 定案：UDP type=…】
  Block = nullptr;
  Src = nullptr;
  v40 = 0;
  pTargetVt = *pNearest;
  LOBYTE(v44) = 1;  // 调 取 16 位值低 8 位
  pScanObj3 = (*(int (/*thiscall*/ **)(int *))(pTargetVt + 48))(pNearest);  // 调用虚函数（虚表槽 +48）
  nTgtX = (char *)Src;
  if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v40 - (int)Block) >> 2) )
  {
    *(uint32_t *)Src = pScanObj3;
    Src = nTgtX + 4;
  }
  else
  {
    sub_430C80(Src, 1, (int)&pScanObj3);  // 调 uint32 vector 区间插入（同值填充）
  }
  nTgtY = (*(int (/*thiscall*/ **)(int *))(*pNearest + 52))(pNearest);  // 调用虚函数（虚表槽 +52）
  nTgtX2 = (char *)Src;
  nCandCntSaved = nTgtY;
  if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v40 - (int)Block) >> 2) )
  {
    *(uint32_t *)Src = nTgtY;
    Src = nTgtX2 + 4;
  }
  else
  {
    sub_430C80(Src, 1, (int)&nCandCntSaved);  // 调 uint32 vector 区间插入（同值填充）
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *))(*pArg1 + 560))(pArg1, 14, v37);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 堆释放
  Block = nullptr;
  Src = nullptr;
  v40 = 0;
  j__free(v34);  // 调 堆释放
  return 1;  // 返回 1(成功)
}


// 水精灵语音全套：WATERSOUL_DIE/DMG/01_LOOP/CREATE/CAST/ATK_1_READY/ATK_2_READY/
//   ATK_1/ATK_2 九段播报（66L）
// ------------------------------------------------------------
// 0x5C8290 sub_5C8290 —— 水精灵语音注册（id 196613）
//   与 ·0x5C8470 ·0x5C8650 ·0x5C8FE0 同构：逐条 sub_4015C0 构造九段标准串并按 0..3 索引
//   交 sub_416C40 登记，末以 196613 号与 100000 参数调 sub_4E1390 注册语音组。
// ------------------------------------------------------------
int sub_5C8290()  // 函数: 水精灵语音注册（id 196613）
{
  uint8_t v1[4]; // [esp+Ch] [ebp-48h] BYREF
  void *Block; // [esp+10h] [ebp-44h]
  int v3; // [esp+20h] [ebp-34h]
  unsigned int v4; // [esp+24h] [ebp-30h]
  uint8_t v5[4]; // [esp+28h] [ebp-2Ch] BYREF
  void *v6; // [esp+2Ch] [ebp-28h]
  int v7; // [esp+3Ch] [ebp-18h]
  unsigned int v8; // [esp+40h] [ebp-14h]
  int v9; // [esp+44h] [ebp-10h] BYREF
  int v10; // [esp+50h] [ebp-4h]

  sub_4015C0("WATERSOUL_DIE", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("WATERSOUL_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("WATERSOUL_01_LOOP", 0x11u);  // 【std::string构造赋值】
  sub_4015C0("WATERSOUL_CREATE", 0x10u);  // 【std::string构造赋值】
  sub_4015C0("WATERSOUL_CAST", 0xEu);  // 【std::string构造赋值】
  v4 = 15;
  v3 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("WATERSOUL_ATK_1_READY", 0x15u);  // 【std::string构造赋值】
  v10 = 0;
  sub_416C40(v1);  // 调 尾插一条 28B 记录（满则走插入路径）
  v10 = -1;
  if ( v4 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v4 = 15;
  v3 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("WATERSOUL_ATK_2_READY", 0x15u);  // 【std::string构造赋值】
  v10 = 1;
  sub_416C40(v1);  // 调 尾插一条 28B 记录（满则走插入路径）
  v10 = -1;
  if ( v4 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v4 = 15;
  v3 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("WATERSOUL_ATK_1", 0xFu);  // 【std::string构造赋值】
  v10 = 2;
  sub_416C40(v1);  // 调 尾插一条 28B 记录（满则走插入路径）
  v10 = -1;
  if ( v4 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v8 = 15;
  v7 = 0;
  LOBYTE(v6) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("WATERSOUL_ATK_2", 0xFu);  // 【std::string构造赋值】
  v10 = 3;
  sub_416C40(v5);  // 调 尾插一条 28B 记录（满则走插入路径）
  v10 = -1;
  if ( v8 >= 0x10 )
    j__free(v6);  // 调 堆释放
  v8 = 15;
  v7 = 0;
  LOBYTE(v6) = 0;  // 调 取 16 位值低 8 位
  v9 = 100000;
  return sub_4E1390(196613, &v9);  // 调 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
}



// 火精灵语音全套：FIRESOUL_* 九段播报（69L；与水精灵同构）
// ------------------------------------------------------------
// 0x5C8470 sub_5C8470 —— 火精灵语音注册（id 196612）
//   与 ·0x5C8290 同构（差异：FIRESOUL_ 前缀九串、注册号 196612，尾附 this[2186]=0 清时序戳）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C8470(uint32_t *this)  // 函数: 火精灵语音注册（id 196612）
{
  int result; // eax
  uint8_t v3[4]; // [esp+Ch] [ebp-48h] BYREF
  void *Block; // [esp+10h] [ebp-44h]
  int v5; // [esp+20h] [ebp-34h]
  unsigned int v6; // [esp+24h] [ebp-30h]
  uint8_t v7[4]; // [esp+28h] [ebp-2Ch] BYREF
  void *v8; // [esp+2Ch] [ebp-28h]
  int v9; // [esp+3Ch] [ebp-18h]
  unsigned int v10; // [esp+40h] [ebp-14h]
  int v11; // [esp+44h] [ebp-10h] BYREF
  int v12; // [esp+50h] [ebp-4h]

  sub_4015C0("FIRESOUL_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("FIRESOUL_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("FIRESOUL_01_LOOP", 0x10u);  // 【std::string构造赋值】
  sub_4015C0("FIRESOUL_CREATE", 0xFu);  // 【std::string构造赋值】
  sub_4015C0("FIRESOUL_CAST", 0xDu);  // 【std::string构造赋值】
  v6 = 15;
  v5 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("FIRESOUL_ATK_1_READY", 0x14u);  // 【std::string构造赋值】
  v12 = 0;
  sub_416C40(v3);  // 调 尾插一条 28B 记录（满则走插入路径）
  v12 = -1;
  if ( v6 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v6 = 15;
  v5 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("FIRESOUL_ATK_2_READY", 0x14u);  // 【std::string构造赋值】
  v12 = 1;
  sub_416C40(v3);  // 调 尾插一条 28B 记录（满则走插入路径）
  v12 = -1;
  if ( v6 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v6 = 15;
  v5 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("FIRESOUL_ATK_1", 0xEu);  // 【std::string构造赋值】
  v12 = 2;
  sub_416C40(v3);  // 调 尾插一条 28B 记录（满则走插入路径）
  v12 = -1;
  if ( v6 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v10 = 15;
  v9 = 0;
  LOBYTE(v8) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("FIRESOUL_ATK_2", 0xEu);  // 【std::string构造赋值】
  v12 = 3;
  sub_416C40(v7);  // 调 尾插一条 28B 记录（满则走插入路径）
  v12 = -1;
  if ( v10 >= 0x10 )
    j__free(v8);  // 调 堆释放
  v10 = 15;
  v9 = 0;
  LOBYTE(v8) = 0;  // 调 取 16 位值低 8 位
  v11 = 100000;
  result = sub_4E1390(196612, &v11);  // 调 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
  *(this + 2186) = 0;  // this+8744〔nCountdown8744(推断)〕
  return result;
}



// 暗精灵语音全套：DARKSOUL_* 九段播报（98L；this+8720..8728 相位）
// ------------------------------------------------------------
// 0x5C8650 sub_5C8650 —— 暗精灵语音注册（id 196615）
//   与 ·0x5C8290 同构（差异：DARKSOUL_ 前缀九串、注册号 196615；尾段以 sub_430C80 向
//   this+8720 的 int 表（28 字节步进面）追加 2 与 3 两条索引）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C8650(int this)  // 函数: 暗精灵语音注册（id 196615）
{
  int fld_2210; // ecx  | +0x2210 → 【推断】段阈值表首针〔5C6DC0：与 7028 段索引/帧计数 +148 比对〕（CNStalker；va=005C6DC0）
  unsigned int fld_2214; // edx  | +0x2214 → 【推断】段阈值表尾针（元素数=(8724-8720)>>2）〔5C6DC0〕（CNStalker；va=005C6DC0）
  uint32_t *fld_22142; // eax
  int fld_22102; // edx  | +0x2210 → 【推断】段阈值表首针〔5C6DC0：与 7028 段索引/帧计数 +148 比对〕（CNStalker；va=005C6DC0）
  unsigned int fld_22143; // ecx  | +0x2214 → 【推断】段阈值表尾针（元素数=(8724-8720)>>2）〔5C6DC0〕（CNStalker；va=005C6DC0）
  uint32_t *fld_22144; // eax
  uint8_t v9[4]; // [esp+Ch] [ebp-30h] BYREF
  void *Block; // [esp+10h] [ebp-2Ch]
  int v11; // [esp+20h] [ebp-1Ch]
  unsigned int v12; // [esp+24h] [ebp-18h]
  int v13; // [esp+28h] [ebp-14h] BYREF
  int v14; // [esp+2Ch] [ebp-10h] BYREF
  int v15; // [esp+38h] [ebp-4h]

  sub_4015C0("DARKSOUL_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("DARKSOUL_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("DARKSOUL_01_LOOP", 0x10u);  // 【std::string构造赋值】
  sub_4015C0("DARKSOUL_CREATE", 0xFu);  // 【std::string构造赋值】
  sub_4015C0("DARKSOUL_CAST", 0xDu);  // 【std::string构造赋值】
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("DARKSOUL_ATK_1_READY", 0x14u);  // 【std::string构造赋值】
  v15 = 0;
  sub_416C40(v9);  // 调 尾插一条 28B 记录（满则走插入路径）
  v15 = -1;
  if ( v12 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("DARKSOUL_ATK_2_READY", 0x14u);  // 【std::string构造赋值】
  v15 = 1;
  sub_416C40(v9);  // 调 尾插一条 28B 记录（满则走插入路径）
  v15 = -1;
  if ( v12 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("DARKSOUL_ATK_1", 0xEu);  // 【std::string构造赋值】
  v15 = 2;
  sub_416C40(v9);  // 调 尾插一条 28B 记录（满则走插入路径）
  v15 = -1;
  if ( v12 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("DARKSOUL_ATK_2", 0xEu);  // 【std::string构造赋值】
  v15 = 3;
  sub_416C40(v9);  // 调 尾插一条 28B 记录（满则走插入路径）
  v15 = -1;
  if ( v12 >= 0x10 )
    j__free(Block);  // 调 堆释放
  fld_2210 = *(uint32_t *)(this + 8720);  // this+8720 【推断】段阈值表首针
  v14 = 2;
  if ( fld_2210 != 0 )
    fld_2214 = (*(uint32_t *)(this + 8724) - fld_2210) >> 2;  // this+8724 【推断】段阈值表尾针
  else
    fld_2214 = 0;
  if ( fld_2210 != 0 && fld_2214 < (*(uint32_t *)(this + 8728) - fld_2210) >> 2 )  // this+8728 【推断】段阈值表容量端
  {
    fld_22142 = *(uint32_t **)(this + 8724);  // this+8724 【推断】段阈值表尾针
    *fld_22142 = 2;
    *(uint32_t *)(this + 8724) = fld_22142 + 1;  // this+8724 【推断】段阈值表尾针
  }
  else
  {
    sub_430C80(*(void **)(this + 8724), 1, (int)&v14);  // 调 uint32 vector 区间插入（同值填充）
  }
  fld_22102 = *(uint32_t *)(this + 8720);  // this+8720 【推断】段阈值表首针
  v14 = 3;
  if ( fld_22102 != 0 )
    fld_22143 = (*(uint32_t *)(this + 8724) - fld_22102) >> 2;  // this+8724 【推断】段阈值表尾针
  else
    fld_22143 = 0;
  if ( fld_22102 != 0 && fld_22143 < (*(uint32_t *)(this + 8728) - fld_22102) >> 2 )  // this+8728 【推断】段阈值表容量端
  {
    fld_22144 = *(uint32_t **)(this + 8724);  // this+8724 【推断】段阈值表尾针
    *fld_22144 = 3;
    *(uint32_t *)(this + 8724) = fld_22144 + 1;  // this+8724 【推断】段阈值表尾针
  }
  else
  {
    sub_430C80(*(void **)(this + 8724), 1, (int)&v14);  // 调 uint32 vector 区间插入（同值填充）
  }
  v13 = 100000;
  return sub_4E1390(196615, &v13);  // 调 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
}



// 属性精灵·大型事件分发（307L）：事件14 用事件参数对 sub_45EBE0 解算并 RTTI cast 为
//   CNDecoy(替身)存 this[2184] 后 sub_4D83E0 挂接；事件16 清替身槽；事件18=复活名单——
//   遍历参数表(8字节/对)收集存活者(sub_4E7BA0)后 vt+1324 复活、参数[1]非 0 走 vt+1256
//   否则 setState(13,2)；事件5 死亡特效——按类型 0x258/0x259/0x25A/0x25B(水/火/暗/光)
//   加载 Monster/Spirit/{Water,Fire,Dark,Light}Animation/Die.ani，光系追加
//   DieGlow.ani；事件8/17 按 28 字节/串的 this[2172] 语音表取子类型对应 TAG 播报；
//   事件15 替身触发——播 this[2165] TAG、vt+688+56 动画、sub_617370、替身 vt+312(0)，
//   本地玩家进动作13；事件19 出土——记 this[2185]=now、按目标位置 ±70(朝向) 移动
// ------------------------------------------------------------
// 0x5C88C0 sub_5C88C0 —— 属性精灵事件总线
//   参数面：ArgList=事件号、fArg3 为事件参数块指针（以 float 位模式传，+0/+4 对象键、+8 条数、
//   +12 起 8 字节/对）；替身写 this[2184]、出土时刻写 this[2185]、语音表用 this[2172]（28 字节/条）。
//   事件 5 死亡特效按类型 0x258/0x259/0x25A/0x25B 加载四系 Die.ani（光系另加载 DieGlow.ani）。
// ------------------------------------------------------------
void /*userpurge*/ sub_5C88C0(int *pDwArg1@<ecx>, double fArg2@<st0>, int ArgList, int pArg4, int nArg5, int nArg6)  // 函数: 属性精灵事件总线
{
  int nEvt; // edi
  int pResolveObj; // eax
  int pAllyObj; // edi
  int hAniDieW; // eax
  int hAniDie; // ebx
  int hAniDieF; // eax
  int hAniDieD; // eax
  int hAniDieL; // eax
  int hGlowLight; // eax
  char *pPool; // eax
  int pDieFx; // edi
  int pDieFxVt; // ebx
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  int pDieFxVt2; // ebx
  int nFaceDir; // eax
  uint32_t *pszVoice; // eax
  int nVoiceTab; // eax
  unsigned int nVoiceIdx; // ebx
  int nSlotOff; // eax
  int pTabBase; // edx
  unsigned int nStrLen; // ecx
  int pSlotBase; // eax
  int pszVoice2; // eax
  int pCtrl688; // eax
  int pCtrl688b; // eax
  int pReviveTarget; // edi
  int nTgtX; // ebx
  int nMyX; // eax
  bool v38; // sf
  bool v39; // of
  int pVt3; // ebx
  int nMyZ; // eax
  int nSelfY; // eax
  int nSelfX2; // eax
  int *pEvtArgs; // eax
  int nObjKey; // eax
  int pDecoy; // eax
  int nKey1; // [esp-18h] [ebp-44h]
  int nKey2; // [esp-14h] [ebp-40h]
  int v49; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-20h]
  int v51; // [esp+10h] [ebp-1Ch]
  int v52; // [esp+14h] [ebp-18h]
  int nAllyCnt; // [esp+18h] [ebp-14h]
  int pObj42; // [esp+1Ch] [ebp-10h] BYREF
  int v55; // [esp+28h] [ebp-4h]
  int hGlowAni; // [esp+34h] [ebp+8h]
  int nResGateL; // [esp+34h] [ebp+8h]
  int nResGateGlow; // [esp+34h] [ebp+8h]
  int nSideDx; // [esp+34h] [ebp+8h]
  int v60; // [esp+38h] [ebp+Ch]
  int nResGateW; // [esp+38h] [ebp+Ch]
  int nResGateF; // [esp+38h] [ebp+Ch]
  int nResGateD; // [esp+38h] [ebp+Ch]

  nEvt = ArgList;
  if ( ArgList == 14 )
  {
    pEvtArgs = *(int **)(pArg4 + 4);  // pArg4+4〔宿主对象〕
    nKey2 = pEvtArgs[1];
    nKey1 = *pEvtArgs;
    (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 调用虚函数（虚表槽 +80）
    nObjKey = sub_45EBE0(nKey1, nKey2);  // 调 存 id 对 → 对象查找
    pDecoy = __RTDynamicCast(nObjKey, 0, &CNRDObject `RTTI Type Descriptor', &CNDecoy `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    pDwArg1[2184] = pDecoy;
    if ( pDecoy != 0 )
      sub_4D83E0(pDwArg1, 0, 0);  // 头顶气泡 Exclamation.ani（惊叹；同 0x4D82D0 结构）
  }
  else
  {
    if ( ArgList == 16 )
    {
      pDwArg1[2184] = 0;
      return;
    }
    if ( ArgList == 18 )
    {
      nAllyCnt = *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 8);  // pArg4+4〔宿主对象〕
      Block = nullptr;
      v51 = 0;
      v52 = 0;
      v55 = 0;
      v60 = 0;
      if ( nAllyCnt > 0 )
      {
        do
        {
          pResolveObj = sub_45EBE0(  // 调 存 id 对 → 对象查找
                 *(uint32_t *)(8 * v60 + *(uint32_t *)(pArg4 + 4) + 12),
                 *(uint32_t *)(8 * v60 + *(uint32_t *)(pArg4 + 4) + 16));  // pArg4+4〔宿主对象〕
          pAllyObj = pResolveObj;
          if ( pResolveObj != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pResolveObj + 40))(pResolveObj, 17) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
          {
            pObj42 = pAllyObj;
            sub_4E7BA0(&v49, &pObj42);  // 调 4 字节 vector push_back（容量不足 → ·sub_4E75F0 增 1）
          }
          ++v60;
        }
        while ( v60 < nAllyCnt );
        nEvt = ArgList;
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int *))(*pDwArg1 + 1324))(  // 调用虚函数（虚表槽 +1324）
        pDwArg1,
        **(uint32_t **)(pArg4 + 4),
        *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4),
        &v49);
      if ( *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4) != 0 )  // pArg4+4〔宿主对象〕
        (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 1256))(pDwArg1);  // 调用虚函数（虚表槽 +1256）
      else
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*pDwArg1 + 560))(pDwArg1, 13, 0, 2, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      v55 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
      Block = nullptr;
      v51 = 0;
      v52 = 0;
    }
    sub_4E33D0((int)pDwArg1, pArg4, fArg2, nEvt, pArg4, *(float *)&nArg5, *(float *)&nArg6);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
    switch ( nEvt )  // 按 nEvt 分派
    {
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        hGlowAni = 0;
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, 0);  // 调用虚函数（虚表槽 +196）
        switch ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 340))(pDwArg1) )  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
        {
          case 0x258:
            nResGateW = sub_42FCB0(228);  // 调 CRT 一次性初始化
            v55 = 1;
            if ( nResGateW == 0 )
              goto LABEL_24;
            hAniDieW = sub_431860((char)"Monster/Spirit/WaterAnimation/Die.ani", 1);  // 调 动画件构造（资源 id 版）
            v55 = -1;
            hAniDie = hAniDieW;
            goto LABEL_32;
          case 0x259:
            nResGateF = sub_42FCB0(228);  // 调 CRT 一次性初始化
            v55 = 2;
            if ( nResGateF == 0 )
              goto LABEL_24;
            hAniDieF = sub_431860((char)"Monster/Spirit/FireAnimation/Die.ani", 1);  // 调 动画件构造（资源 id 版）
            v55 = -1;
            hAniDie = hAniDieF;
            goto LABEL_32;
          case 0x25A:
            nResGateD = sub_42FCB0(228);  // 调 CRT 一次性初始化
            v55 = 3;
            if ( nResGateD != 0 )
            {
              hAniDieD = sub_431860((char)"Monster/Spirit/DarkAnimation/Die.ani", 1);  // 调 动画件构造（资源 id 版）
              v55 = -1;
              hAniDie = hAniDieD;
            }
            else
            {
LABEL_24:
              v55 = -1;
              hAniDie = 0;
            }
            goto LABEL_32;
          case 0x25B:
            nResGateL = sub_42FCB0(228);  // 调 CRT 一次性初始化
            v55 = 4;
            if ( nResGateL != 0 )
              hAniDieL = sub_431860((char)"Monster/Spirit/LightAnimation/Die.ani", 1);  // 调 动画件构造（资源 id 版）
            else
              hAniDieL = 0;
            v55 = -1;
            hAniDie = hAniDieL;
            nResGateGlow = sub_42FCB0(228);  // 调 CRT 一次性初始化
            v55 = 5;
            if ( nResGateGlow != 0 )
              hGlowLight = sub_431860((char)"Monster/Spirit/LightAnimation/DieGlow.ani", 1);  // 调 动画件构造（资源 id 版）
            else
              hGlowLight = 0;
            v55 = -1;
            hGlowAni = hGlowLight;
LABEL_32:
            if ( hAniDie != 0 )
            {
              pPool = (char *)sub_44B6C0(284);  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
              pDieFx = (int)pPool;
              v55 = 6;
              if ( pPool != nullptr )  // 若 pPool 有效（非空）
              {
                sub_44E0D0(pPool, hAniDie, 1);  // 调 CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
                *(uint32_t *)pDieFx = &CNRDPooledObject::`vftable';  // vftable 复位
              }
              else
              {
                pDieFx = 0;
              }
              v55 = -1;
              if ( hGlowAni != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pDieFx + 204))(  // 调用虚函数（虚表槽 +204）
                  pDieFx,
                  100,
                  hGlowAni,
                  0,
                  0,
                  0,
                  0);
              sub_45FE80(pDwArg1[29], pDieFx, 2, 0, pDieFx, (int)pDwArg1, 0);  // 调 对象注册
              pDieFxVt = *(uint32_t *)pDieFx;
              nZ = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调用虚函数（虚表槽 +128）
              nY = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, nZ);  // 调用虚函数（虚表槽 +124）
              nX = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              (*(void (/*thiscall*/ **)(int, int))(pDieFxVt + 112))(pDieFx, nX);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
              pDieFxVt2 = *(uint32_t *)pDieFx;
              nFaceDir = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              (*(void (/*thiscall*/ **)(int, int))(pDieFxVt2 + 144))(pDieFx, nFaceDir);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
            }
            break;
          default:
            return;
        }
        return;
      case 17:  // case 17 = ENUM_CMDPACKET_SELECT_DUNGEON
        if ( (unsigned int)pDwArg1[2170] < 0x10 )
          pszVoice = pDwArg1 + 2165;
        else
          pszVoice = (uint32_t *)pDwArg1[2165];
        goto LABEL_44;
      case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
        *((uint8_t *)pDwArg1 + 8732) = 0;
        nVoiceTab = pDwArg1[2172];
        if ( nVoiceTab != 0 )
          nVoiceIdx = (pDwArg1[2173] - nVoiceTab) / 28;
        else
          nVoiceIdx = 0;
        if ( nVoiceIdx <= sub_41A5E0((unsigned int)(pDwArg1 + 1757)) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
          return;
        nSlotOff = 28 * sub_41A5E0((unsigned int)(pDwArg1 + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        pTabBase = pDwArg1[2172];
        nStrLen = *(uint32_t *)(nSlotOff + pTabBase + 24);
        pSlotBase = pTabBase + nSlotOff;
        if ( nStrLen < 0x10 )
          pszVoice = (uint32_t *)(pSlotBase + 4);
        else
          pszVoice = *(uint32_t **)(pSlotBase + 4);
LABEL_44:
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, pszVoice, -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        return;
      case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
        if ( pDwArg1[2184] != 0 )
        {
          pszVoice2 = (unsigned int)pDwArg1[2170] < 0x10 ? (int)(pDwArg1 + 2165) : pDwArg1[2165];
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, pszVoice2, -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
            pDwArg1,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          pCtrl688 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 688))(pDwArg1);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
          sub_4926A0(**(uint32_t **)(pCtrl688 + 56));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
          pCtrl688b = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 688))(pDwArg1);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, **(uint32_t **)(pCtrl688b + 56));  // 调用虚函数（虚表槽 +196）
          sub_617370(pDwArg1);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2184] + 312))(pDwArg1[2184], 0);  // 虚函数调用 槽+312：濒死/一击表现（LAST STRIKE；死亡链上游）【新发现(会话 3)】
          if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
            (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1104))(pDwArg1, 13);  // 调用虚函数（虚表槽 +1104）
        }
        break;
      case 19:  // case 19 = ENUM_CMDPACKET_DELETE_ITEM
        pDwArg1[2185] = sub_699000((int)(pDwArg1 + 2));  // 【clock_now(clk)】
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          pDwArg1,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 604))(pDwArg1, 0);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
        pReviveTarget = sub_45EBE0(**(uint32_t **)(pArg4 + 4), *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4));  // 调 存 id 对 → 对象查找
        if ( pReviveTarget != 0 )
        {
          nTgtX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pReviveTarget + 120))(pReviveTarget);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          nMyX = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          v39 = __OFSUB__(nMyX, nTgtX);  // v39 = 调 __OFSUB__
          v38 = nMyX - nTgtX < 0;
          pVt3 = *pDwArg1;
          nSideDx = v38 == v39 ? 70 : -70;
          nMyZ = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调用虚函数（虚表槽 +128）
          nSelfY = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pReviveTarget + 124))(pReviveTarget, nMyZ);  // 调用虚函数（虚表槽 +124）
          nSelfX2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pReviveTarget + 120))(pReviveTarget, nSelfY);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          (*(void (/*thiscall*/ **)(int *, int))(pVt3 + 108))(pDwArg1, nSideDx + nSelfX2);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
        }
        break;
      default:
        break;
    }
  }
}


// AI 字段访问（this+8744）
// ------------------------------------------------------------
// 0x5C8EE0 sub_5C8EE0 —— 事件前钩（清段 1 门）
//   事件 8 且参数块首项 ==1 时把 this+8744 低字节清 0（即抹掉 ·0x5C6F30 写入的时钟戳，
//   使 ·0x5C6EE0 的段 1 触发门重新成立），随后统一转发 ·0x5C88C0。【该字节复用语义推断】
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C8EE0(int this, unsigned int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 事件前钩（清段 1 门）
{
  if ( ArgList == 8 && **(uint32_t **)(LODWORD(fArg3) + 4) == 1 )  // 调 取 64 位值低 32 位
    *(uint8_t *)(this + 8744) = 0;  // this+8744 【推断】主倒计时截止
  return sub_5C88C0((uint32_t *)this, ArgList, fArg3, nArg4, nArg5);  // 调 属性精灵事件总线
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C8F20 sub_5C8F20 —— 事件总线透传
//   无副作用直转 ·0x5C88C0（thiscall 前两参对齐）；与 ·0x5C8EE0 ·0x5C8F30 同为一族包装。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C8F20(uint32_t *this, unsigned int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 事件总线透传
{
  return sub_5C88C0(this, ArgList, fArg3, nArg4, nArg5);  // 调 属性精灵事件总线
}



// AI 字段访问（this+8748）
// ------------------------------------------------------------
// 0x5C8F30 sub_5C8F30 —— 事件前钩（置段 2 门）
//   事件 8 且参数块首项落在 2..3 时置 this+8748 = 1（供 ·0x5C71C0 段 2 分支消费后再清 0），
//   随后统一转发 ·0x5C88C0。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C8F30(int this, unsigned int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 事件前钩（置段 2 门）
{
  int v5; // eax

  if ( ArgList == 8 )
  {
    v5 = **(uint32_t **)(LODWORD(fArg3) + 4);  // 调 取 64 位值低 32 位
    if ( v5 >= 2 && v5 <= 3 )  // 若 v5 >= 2 与/或 v5 <= 3
      *(uint8_t *)(this + 8748) = 1;  // this+8748 子类 AI 尾部槽
  }
  return sub_5C88C0((uint32_t *)this, ArgList, fArg3, nArg4, nArg5);  // 调 属性精灵事件总线
}



// 硬直字段（this+204）
// ------------------------------------------------------------
// 0x5C8F70 sub_5C8F70 —— 事件后钩（硬直段 1 收招）
//   先转发 ·0x5C88C0；事件 8 且段索引 7028==1 时经 sub_4926A0 复位 this[1554]+12 处帧游标，
//   再经 vt+204(this,100,帧句柄) 写 100ms 硬直节奏（this[1554] 为硬直/段参数基址）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C8F70(uint32_t *this, unsigned int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 事件后钩（硬直段 1 收招）
{
  int result; // eax

  result = sub_5C88C0(this, ArgList, fArg3, nArg4, nArg5);  // 调 属性精灵事件总线
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )
    {
      sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
               this,
               100,
               *(uint32_t *)(*(this + 1554) + 12),  // this+6216 = 资源/帧游标表
               0,
               0,
               0,
               0);
    }
  }
  return result;
}



// 光精灵语音全套：LIGHTSOUL_* 九段播报 + Monster/Spirit/Light1Glow.equ 发光外观（115L）
// ------------------------------------------------------------
// 0x5C8FE0 sub_5C8FE0 —— 光精灵语音注册（id 196614）+ 发光外观挂装
//   与 ·0x5C8290 同构（差异：LIGHTSOUL_ 前缀九串、注册号 196614）；随后向 this+8720 表
//   追加 2 与 4，operator new(0x544) 后 sub_4BA9E0 载 Monster/Spirit/Light1Glow.equ，
//   经 vt+784 挂装并对结果 vt+4(result,1) 启用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C8FE0(int *this)  // 函数: 光精灵语音注册（id 196614）+ 发光外观挂装
{
  int fld_e2180; // ecx  | +0x2210 → 【推断】段阈值表首针〔5C6DC0：与 7028 段索引/帧计数 +148 比对〕（CNWisp；va=005C6DC0）
  unsigned int fld_e2181; // edx  | +0x2214 → 【推断】段阈值表尾针（元素数=(8724-8720)>>2）〔5C6DC0〕（CNWisp；va=005C6DC0）
  uint32_t *fld_e21812; // eax
  int fld_e21802; // edx  | +0x2210 → 【推断】段阈值表首针〔5C6DC0：与 7028 段索引/帧计数 +148 比对〕（CNWisp；va=005C6DC0）
  unsigned int fld_e21813; // ecx  | +0x2214 → 【推断】段阈值表尾针（元素数=(8724-8720)>>2）〔5C6DC0〕（CNWisp；va=005C6DC0）
  uint32_t *fld_e21814; // eax
  void *pMem; // eax
  char *v9; // eax
  int v10; // edx
  int result; // eax
  uint8_t v12[4]; // [esp+Ch] [ebp-30h] BYREF
  void *Block; // [esp+10h] [ebp-2Ch]
  int v14; // [esp+20h] [ebp-1Ch]
  unsigned int v15; // [esp+24h] [ebp-18h]
  int v16; // [esp+28h] [ebp-14h] BYREF
  void *pMem2; // [esp+2Ch] [ebp-10h] BYREF
  int v18; // [esp+38h] [ebp-4h]

  sub_4015C0("LIGHTSOUL_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("LIGHTSOUL_DIE", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("LIGHTSOUL_01_LOOP", 0x11u);  // 【std::string构造赋值】
  sub_4015C0("LIGHTSOUL_CREATE", 0x10u);  // 【std::string构造赋值】
  sub_4015C0("LIGHTSOUL_CAST", 0xEu);  // 【std::string构造赋值】
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("LIGHTSOUL_ATK_1_READY", 0x15u);  // 【std::string构造赋值】
  v18 = 0;
  sub_416C40(v12);  // 调 尾插一条 28B 记录（满则走插入路径）
  v18 = -1;
  if ( v15 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("LIGHTSOUL_ATK_2_READY", 0x15u);  // 【std::string构造赋值】
  v18 = 1;
  sub_416C40(v12);  // 调 尾插一条 28B 记录（满则走插入路径）
  v18 = -1;
  if ( v15 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("LIGHTSOUL_ATK_1", 0xFu);  // 【std::string构造赋值】
  v18 = 2;
  sub_416C40(v12);  // 调 尾插一条 28B 记录（满则走插入路径）
  v18 = -1;
  if ( v15 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("LIGHTSOUL_ATK_2", 0xFu);  // 【std::string构造赋值】
  v18 = 3;
  sub_416C40(v12);  // 调 尾插一条 28B 记录（满则走插入路径）
  v18 = -1;
  if ( v15 >= 0x10 )
    j__free(Block);  // 调 堆释放
  fld_e2180 = *(this + 2180);  // this+8720〔pSegThrTbl8720〕
  pMem2 = (void *)2;  // pMem2 = 转换(2)
  if ( fld_e2180 != 0 )
    fld_e2181 = (*(this + 2181) - fld_e2180) >> 2;  // this+8724〔nSegThrEnd8724〕
  else
    fld_e2181 = 0;
  if ( fld_e2180 != 0 && fld_e2181 < (*(this + 2182) - fld_e2180) >> 2 )  // this+8728〔nSegThrCap8728〕
  {
    fld_e21812 = (uint32_t *)*(this + 2181);  // this+8724〔nSegThrEnd8724〕
    *fld_e21812 = 2;
    *(this + 2181) = (int)(fld_e21812 + 1);  // this+8724〔nSegThrEnd8724〕
  }
  else
  {
    sub_430C80((void *)*(this + 2181), 1, (int)&pMem2);  // 调 uint32 vector 区间插入（同值填充）
  }
  fld_e21802 = *(this + 2180);  // this+8720〔pSegThrTbl8720〕
  pMem2 = (void *)4;  // pMem2 = 转换(4)
  if ( fld_e21802 != 0 )
    fld_e21813 = (*(this + 2181) - fld_e21802) >> 2;  // this+8724〔nSegThrEnd8724〕
  else
    fld_e21813 = 0;
  if ( fld_e21802 != 0 && fld_e21813 < (*(this + 2182) - fld_e21802) >> 2 )  // this+8728〔nSegThrCap8728〕
  {
    fld_e21814 = (uint32_t *)*(this + 2181);  // this+8724〔nSegThrEnd8724〕
    *fld_e21814 = 4;
    *(this + 2181) = (int)(fld_e21814 + 1);  // this+8724〔nSegThrEnd8724〕
  }
  else
  {
    sub_430C80((void *)*(this + 2181), 1, (int)&pMem2);  // 调 uint32 vector 区间插入（同值填充）
  }
  v16 = 100000;
  sub_4E1390(196614, &v16);  // 调 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
  pMem = operator new(0x544u);  // operator new 分配 1348 字节
  pMem2 = pMem;
  v18 = 4;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v9 = sub_4BA9E0((char *)pMem, "Monster/Spirit/Light1Glow.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v9 = nullptr;
  v10 = *this;
  v18 = -1;
  result = (*(int (/*thiscall*/ **)(int *, char *))(v10 + 784))(this, v9);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C92A0 sub_5C92A0 —— 挂接对象释放
//   this[2157]（·0x5CB360 中由 sub_4C3640 载 Particle/DieSmoke.ptl 建成的粒子体）非空时
//   经其 vt+0 首槽 (obj,1) 释放，随后清槽置 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C92A0(uint32_t *this)  // 函数: 挂接对象释放
{
  int (/*thiscall*/ ***fld_e2157)(uint32_t, int); // ecx
  int result; // eax

  fld_e2157 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2157);  // this+8628 = 指挥计时戳
  if ( fld_e2157 != nullptr )  // 若 fld_e2157 有效（非空）
    result = (**fld_e2157)(fld_e2157, 1);  // 调 fld_e2157 的虚函数（vt+0）
  *(this + 2157) = 0;  // this+8628 = 指挥计时戳
  return result;
}



// 死亡/终局钩：调 sub_4E4430 = HP 受击处理器（研究 31 Boss 终局长震族, 20L）
// ------------------------------------------------------------
// 0x5C92D0 sub_5C92D0 —— 受击转发 + 困难级震屏
//   转发 sub_4E4430（HP 受击处理器/Boss 终局族）；此后 vt+724 有效且 this+7772 ==3
//   （困难级，见 ·0x5C9360 同族字段）时经 vt+80 取控制器再 sub_424120(ctrl+132,4,1000)
//   发 1000ms 强震屏。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C92D0(int this, int nArg2, int nArg3, char pszArg4)  // 【调 sub_4E4430（HP 受击处理器/Boss 终局族）】
{
  int result; // eax
  int pThis_50; // eax

  sub_4E4430((char *)this, nArg2, nArg3, pszArg4);  // 【HP 受击处理器含 Boss 终局（研究 P35 第 31 轮）】
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 724))(this);  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
  if ( (uint8_t)result != 0 && *(uint32_t *)(this + 7772) == 3 )  // this+7772 反击态
  {
    pThis_50 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 80))(this);  // 调用虚函数（虚表槽 +80）
    return sub_424120(*(uint32_t **)(pThis_50 + 132), 4, 1000);  // 调 屏幕震动启动
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C9320 sub_5C9320 —— 名牌偏移绘制
//   取 vt+152（朝向）非 0 则 x+90、否则 x-90 后交 sub_4DAE50（头顶名牌/文本绘制）
//   —— 使名牌始终偏向角色面向侧。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9320(void *this, int nArg2, int nArg3)  // 函数: 名牌偏移绘制
{
  int pThis_98; // eax

  pThis_98 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  return sub_4DAE50((pThis_98 != 0 ? 90 : -90) + nArg2, nArg3);  // 调 头顶名牌/文本绘制
}



// ============================================================
// 【分区 5】章鱼陷阱与莲花（Trap Octopus / Lotus）（0x5C9360-0x5CBC00）
// 证据：TRAP_OCTOPUS_READY/TIGHTEN/SWING 触手三连、LOTUS_DIE/BREAK/TWIST/READY/ATK/SWEEP/
//       SWEEP_LOOP/READY_LOOP/LAUGH/DMG 全套 + R_BELIEVER_ALERT（莲花=信徒伪装!）、
//       Particle/PoisonBug.ptl + TRAP_GRASS_UP 草丛升起、Particle/DieSmoke.ptl

// AI 字段访问（this+8624）
// ------------------------------------------------------------
// 0x5C9360 sub_5C9360 —— 触发中/死亡判定（this+8624）
//   返回 this+8624（莲花触发相位字节，见 ·0x5CA5F0 写入）=1 或全局态 5（死亡）成立；
//   与 ·0x5C9380 同族读取，此处多叠一项姿态 5 门。
// ------------------------------------------------------------
bool /*thiscall*/ sub_5C9360(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 触发中/死亡判定（this+8624）
{
  return *(this + 8624) != 0 || (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 5;  // this+8624 = uAI8624
}



// AI 字段访问（this+8624）
// ------------------------------------------------------------
// 0x5C9380 sub_5C9380 —— 触发中判定（纯读）
//   单读 this+8624 !=0；·0x5C9360 的裁剪版（去掉死亡门）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_5C9380(uint8_t *this, int nArg2)  // 函数: 触发中判定（纯读）
{
  return *(this + 8624) != 0;  // this+8624 = uAI8624
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C9390 sub_5C9390 —— 攻击窗口左移 230
//   取本体位置经 vt+112 写入 x-230 后调 sub_4E22E0（基类触发/判定派发，参数原样透传），
//   返回前再 vt+112 写回 x+230 —— 以临时左偏移让判定发生在本体之左侧。【偏移量语义推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9390(int *this, int nArg2, int nArg3, int nArg4, int nArg5, void *Block, int nArg7)  // 函数: 攻击窗口左移 230
{
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // eax

  v8 = *this;
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
  v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v9);  // 调用虚函数（虚表槽 +124）
  v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v10);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  (*(void (/*thiscall*/ **)(int *, int))(v8 + 112))(this, v11 - 230);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
  sub_4E22E0(nArg2, nArg3, nArg4, nArg5, Block, nArg7);  // 调 掉落物生成（角度均分 + 定位 + 文本倒计时）
  v12 = *this;
  v13 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
  v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v13);  // 调用虚函数（虚表槽 +124）
  v15 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v14);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  return (*(int (/*thiscall*/ **)(int *, int))(v12 + 112))(this, v15 + 230);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
}



// 触手就绪：TRAP_OCTOPUS_READY 播报（83L；RTTI cast 触发判定）
// ------------------------------------------------------------
// 0x5C9410 sub_5C9410 —— 触手就绪/挂接分派
//   nArg2==15 播「TRAP_OCTOPUS_READY」返回 1；nArg2==16 扫参数块（+4 为对象键对表，0xFFFF 终止）：
//   每项 sub_45EBE0 解算后 RTTI 转 IRDActiveObject，经全局表 dword_730C10..730C1C 查其 vt+776 槽位；
//   命中本机玩家则排除 cnEquipmentHyperJammer（抑扰器免疫），否则 vt+764(obj, 值, 8, this, 0) 挂接。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C9410(void *this, int nArg2, int pArg3)  // 函数: 触手就绪/挂接分派
{
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int pObj; // esi
  int *v8; // ebx
  int v9; // eax
  int v11; // [esp-20h] [ebp-28h]
  int v12; // [esp-1Ch] [ebp-24h]
  int v13; // [esp+4h] [ebp-4h]
  int v14; // [esp+10h] [ebp+8h]

  if ( nArg2 == 16 )
  {
    v4 = 0;
    do
    {
      v5 = *(uint32_t *)(pArg3 + 4);  // pArg3+4〔宿主对象〕
      v13 = v4 + 12;
      v12 = *(uint32_t *)(v4 + v5 + 4);
      v14 = *(uint32_t *)(v4 + 12 + v5 - 4);
      v11 = *(uint32_t *)(v4 + v5);
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);  // 调用虚函数（虚表槽 +80）
      v6 = sub_45EBE0(v11, v12);  // 调 存 id 对 → 对象查找
      pObj = __RTDynamicCast(v6, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      if ( pObj != 0 )
      {
        v8 = &dword_730C10;
        while ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 776))(pObj, *v8) == 0 )  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
        {
          if ( (int)++v8 >= (int)dword_730C1C )
          {
            if ( pObj == dword_8F7C04 )  // dword_8F7C04 = 本地玩家对象
            {
              v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, 16);  // 调用虚函数（虚表槽 +792）
              if ( __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                     v9,
                     0,
                     &CNRDEquipment `RTTI Type Descriptor',
                     &CNEquipmentHyperJammer `RTTI Type Descriptor',
                     0) == 0 )
                (*(void (/*thiscall*/ **)(int, int, int, void *, uint32_t))(*(uint32_t *)dword_8F7C04 + 764))(  // 调用虚函数（虚表槽 +764）
                  dword_8F7C04,  // dword_8F7C04 = 本地玩家对象
                  v14,
                  8,
                  this,
                  0);
            }
            else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
            {
              (*(void (/*thiscall*/ **)(int, int, int, void *, uint32_t))(*(uint32_t *)pObj + 764))(pObj, v14, 8, this, 0);  // 调用虚函数（虚表槽 +764）
            }
            break;
          }
        }
      }
      v4 = v13;
    }
    while ( *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + v13) != 0xFFFF );  // pArg3+4〔宿主对象〕
    return 1;  // 返回 1(成功)
  }
  else if ( nArg2 == 15 )
  {
    (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      this,
      "TRAP_OCTOPUS_READY",  // 资源/动画 TAG TRAP_OCTOPUS_READY
      -1,
      0,
      0);
    return 1;  // 返回 1(成功)
  }
  else
  {
    return 0;
  }
}



// 触手复合 AI（191L；this+204/+208 硬直节拍 + 8653/8654 相位）
// ------------------------------------------------------------
// 0x5C9550 sub_5C9550 —— 触手硬直节拍表（按段写本+位移）
//   段号 nArg2 分派：0/4 与 1/5 与 2/6 与 3/7 分别对 this[1554]+40/44/48/52 帧经 vt+208 写帧、
//   vt+204 写 -600/-100/200/300 节奏；8/12..15 全表四连写；9 全表四连写后再写 +128..+140 四帧；
//   16 收尾写 +68/+64 并清 this+8653/8654 两相位字节、sub_698F90(this+2160, 0, 0) 归零倒计时。
// ------------------------------------------------------------
char /*thiscall*/ sub_5C9550(uint32_t *this, int nArg2)  // 函数: 触手硬直节拍表（按段写本+位移）
{
  char result; // al
  int savedregs; // [esp+8h] [ebp+0h]
  int savedregsa; // [esp+8h] [ebp+0h]

  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));  // this+6216 = 资源/帧游标表
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
                 this,
                 -600,
                 *(uint32_t *)(*(this + 1554) + 40),  // this+6216 = 资源/帧游标表
                 0,
                 0,
                 0,
                 0);
      break;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));  // this+6216 = 资源/帧游标表
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
                 this,
                 -100,
                 *(uint32_t *)(*(this + 1554) + 44),  // this+6216 = 资源/帧游标表
                 0,
                 0,
                 0,
                 0);
      break;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));  // this+6216 = 资源/帧游标表
      savedregs = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        200,
        *(uint32_t *)(*(this + 1554) + 48),  // this+6216 = 资源/帧游标表
        0);
      goto LABEL_6;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));  // this+6216 = 资源/帧游标表
      savedregsa = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        300,
        *(uint32_t *)(*(this + 1554) + 52),  // this+6216 = 资源/帧游标表
        0);
LABEL_6:
      result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1550) + 4 * nArg2));  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
      break;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
    case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -600,
        *(uint32_t *)(*(this + 1554) + 40),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -100,
        *(uint32_t *)(*(this + 1554) + 44),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        200,
        *(uint32_t *)(*(this + 1554) + 48),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));  // this+6216 = 资源/帧游标表
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
                 this,
                 300,
                 *(uint32_t *)(*(this + 1554) + 52),  // this+6216 = 资源/帧游标表
                 0,
                 0,
                 0,
                 0);
      break;
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -600,
        *(uint32_t *)(*(this + 1554) + 40),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -100,
        *(uint32_t *)(*(this + 1554) + 44),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        200,
        *(uint32_t *)(*(this + 1554) + 48),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        300,
        *(uint32_t *)(*(this + 1554) + 52),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 128));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 132));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 136));  // this+6216 = 资源/帧游标表
      result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 140));  // this+6216 = 资源/帧游标表
      break;
    case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -600,
        *(uint32_t *)(*(this + 1554) + 40),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -100,
        *(uint32_t *)(*(this + 1554) + 44),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        200,
        *(uint32_t *)(*(this + 1554) + 48),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        300,
        *(uint32_t *)(*(this + 1554) + 52),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 68));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 64));  // this+6216 = 资源/帧游标表
      *((uint8_t *)this + 8653) = 0;  // this+8653 【推断】相位门字节
      *((uint8_t *)this + 8654) = 0;
      result = sub_698F90((int)(this + 2160), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      break;
    default:
      return result;
  }
  return result;
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5C9A00 sub_5C9A00 —— 帧游标复位 + 帧写入
//   经 sub_4926A0 复位 this[1554]+56 处记录的帧游标，再 vt+196(this, 该帧句柄) 写回
//   —— 与 ·0x5C9BE0 尾段 sub_4924C0 后写 +48 的两处硬直复位互为引用点。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9A00(uint32_t *this)  // 函数: 帧游标复位 + 帧写入
{
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 56));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 56));  // this+6216 = 资源/帧游标表
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C9A30 sub_5C9A30 —— 同房间 529 族存活计数
//   扫 this[29] 场景列表（+8/+12 面）中 vt+40(obj,529) 成立者，再要求 sub_5B46A0（映射对象族
//   vt+340 ∈ 250..253）成立且 vt+376 房间号与本体重合，命中则计数 +1；
//   调用者见 ·0x5CA5F0 段 14 以 <3 作投弹门。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9A30(uint32_t *this)  // 函数: 同房间 529 族存活计数
{
  unsigned int v1; // edi
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // esi
  int v11; // esi
  int v13; // [esp+Ch] [ebp-4h]

  v1 = 0;
  v13 = 0;
  while ( 1 )  // 无限循环
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v4 = *(uint32_t *)(fld_e29 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)v1 >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && v1 < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj2 = *(uint32_t *)(v6 + 4 * v1);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && v1 < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj = *(uint32_t *)(v9 + 4 * v1);
      else
        pObj = 0;
      if ( sub_5B46A0(pObj) )  // 调 映射对象族判定（vt+340 ∈ 250..253）
      {
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调用虚函数（虚表槽 +376）
        if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )  // 调用虚函数（虚表槽 +376）
          ++v13;
      }
    }
    ++v1;
  }
  return v13;
}



// RTTI cast 目标解算（67L）
// ------------------------------------------------------------
// 0x5C9AF0 sub_5C9AF0 —— 抑扰器在场检测（写 1905 块 +512）
//   遍历 vt+80 管理器列表（+8/+12 面）中 vt+40(obj,273) 成立者，逐个 vt+792(obj,16) 取装备后
//   RTTI 判是否 cnEquipmentHyperJammer（抑扰器）；全程无一命中则本标志清零，否则置 1。
//   【设备类型作用推断：与 ·0x5C9410 同一抑扰机制】
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9AF0(int *this)  // 函数: 抑扰器在场检测（写 1905 块 +512）
{
  char v2; // bl
  unsigned int i; // edi
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int result; // eax
  int v8; // eax
  int v9; // edx
  int pObj2; // ecx
  int v11; // eax
  int v12; // edx
  int pObj; // ecx
  int v14; // eax

  v2 = 1;
  for ( i = 0; ; ++i )
  {
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调用虚函数（虚表槽 +80）
    v5 = *(uint32_t *)(v4 + 8);
    v6 = v4 + 4;
    result = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调用虚函数（虚表槽 +80）
    v9 = *(uint32_t *)(v8 + 8);
    if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj2 = *(uint32_t *)(v9 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调用虚函数（虚表槽 +80）
      v12 = *(uint32_t *)(v11 + 8);
      if ( v12 != 0 && i < (*(uint32_t *)(v11 + 12) - v12) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj = *(uint32_t *)(v12 + 4 * i);
      else
        pObj = 0;
      v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 792))(pObj, 16);  // 调用虚函数（虚表槽 +792）
      if ( __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
             v14,
             0,
             &CNRDEquipment `RTTI Type Descriptor',
             &CNEquipmentHyperJammer `RTTI Type Descriptor',
             0) == 0 )
        v2 = 0;
    }
  }
  if ( v2 != 0 )
  {
    result = *(this + 1908);  // this+7632〔uWindow7632(推断)〕
    if ( result == 0 )
      *(uint8_t *)(*(this + 1905) + 512) = 0;  // this+7620 = 速度/属性参数对象
  }
  else
  {
    *(uint8_t *)(*(this + 1905) + 512) = 1;  // this+7620 = 速度/属性参数对象
  }
  return result;
}



// 硬直联动 AI（this+204/+208, 72L）
// ------------------------------------------------------------
// 0x5C9BE0 sub_5C9BE0 —— 触手硬直联动（±4 段配对）
//   nArg2==nArg3+4 时对 this[1554]+4*(pArg3+28) 帧经 vt+208/vt+204(dword_730C90[pArg3]) 写入；
//   this[2159] == -1 时追加 +4*pArg3+80 帧与 dword_730C70[pArg3] 后 sub_4924C0(0) 复位帧游标并
//   写 +48=500；nArg2==nArg3 分支用 +128 帧与 dword_730CA0 / +96 与 dword_730C80，尾写 +48=70。
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9BE0(uint32_t *this, int nArg2, int pArg3)  // 函数: 触手硬直联动（±4 段配对）
{
  int result; // eax
  int v5; // ebx
  uint32_t *fld_e1554; // eax
  int v7; // ecx
  int v8; // ebx

  result = nArg2;
  if ( nArg2 == pArg3 + 4 )
  {
    v5 = 4 * pArg3 + 112;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(v5 + *(this + 1554)));  // this+6216 = 资源/帧游标表
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
      this,
      dword_730C90[pArg3],
      *(uint32_t *)(v5 + *(this + 1554)),  // this+6216 = 资源/帧游标表
      0,
      0,
      0,
      0);
    if ( *(this + 2159) == -1 )  // this+8636 = pDollTarget
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(4 * pArg3 + 80 + *(this + 1554)));  // this+6216 = 资源/帧游标表
      fld_e1554 = (uint32_t *)(4 * pArg3 + 80 + *(this + 1554));  // this+6216 = 资源/帧游标表
      v7 = dword_730C70[pArg3];
LABEL_7:
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        v7,
        *fld_e1554,
        0,
        0,
        0,
        0);
      result = sub_4924C0(0);  // 调 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      *(uint32_t *)(result + 48) = 500;
      return result;
    }
  }
  else
  {
    if ( nArg2 != pArg3 )
      return result;
    v8 = 4 * pArg3 + 128;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(v8 + *(this + 1554)));  // this+6216 = 资源/帧游标表
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
      this,
      dword_730CA0[pArg3],
      *(uint32_t *)(v8 + *(this + 1554)),  // this+6216 = 资源/帧游标表
      0,
      0,
      0,
      0);
    if ( *(this + 2159) == -1 )  // this+8636 = pDollTarget
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(4 * pArg3 + 96 + *(this + 1554)));  // this+6216 = 资源/帧游标表
      fld_e1554 = (uint32_t *)(4 * pArg3 + 96 + *(this + 1554));  // this+6216 = 资源/帧游标表
      v7 = dword_730C80[pArg3];
      goto LABEL_7;
    }
  }
  result = sub_4924C0(0);  // 调 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
  *(uint32_t *)(result + 48) = 70;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C9D60 sub_5C9D60 —— 迟滞态进入（14 段阈值减半）
//   判定对：nArg2==0 且 nArg3==2，或 nArg2 在 1..2 且 nArg3==0，成立则 this[2152] /= 2
//   （压低 ·0x5CAEC0 中 rand%300 < 阈值的 14 段触发率）；nArg3==2 清 this[1891]，
//   否则清 this[1892] 与 this[1905]+512。与 ·0x5C9DD0 互为逆操作。【迟滞含义推断】
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5C9D60(uint32_t *this, int nArg2, int nArg3)  // 函数: 迟滞态进入（14 段阈值减半）
{
  bool v3; // zf
  uint8_t *result; // eax

  if ( nArg2 != 0 )
  {
    if ( nArg2 <= 0 || nArg2 > 2 )  // 若 nArg2 <= 0 与/或 nArg2 > 2
      goto LABEL_8;
    v3 = nArg3 == 0;
  }
  else
  {
    v3 = nArg3 == 2;
  }
  if ( v3 )
    *(this + 2152) /= 2;  // this+8608 = uAI8608
LABEL_8:
  if ( nArg3 != 0 )
  {
    result = (uint8_t *)(nArg3 - 2);
    if ( nArg3 == 2 )
      *(this + 1891) = 0;  // this+7564 = 形态/模式槽
  }
  else
  {
    result = (uint8_t *)(*(this + 1905) + 512);  // this+7620 = 速度/属性参数对象
    *(this + 1892) = 0;  // this+7568 = 激活/模式槽
    *result = 0;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C9DD0 sub_5C9DD0 —— 迟滞态退出（阈值翻倍复原）
//   同一判定式下 this[2152] *= 2 复原；nArg3==2 置 this[1891]=2，否则置 this[1892]=1 与
//   this[1905]+512=1 —— ·0x5C9D60 的逆操作。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5C9DD0(uint32_t *this, int nArg2, int nArg3)  // 函数: 迟滞态退出（阈值翻倍复原）
{
  bool v3; // zf
  uint8_t *result; // eax

  if ( nArg2 != 0 )
  {
    if ( nArg2 <= 0 || nArg2 > 2 )  // 若 nArg2 <= 0 与/或 nArg2 > 2
      goto LABEL_8;
    v3 = nArg3 == 0;
  }
  else
  {
    v3 = nArg3 == 2;
  }
  if ( v3 )
    *(this + 2152) *= 2;  // this+8608 = uAI8608
LABEL_8:
  if ( nArg3 != 0 )
  {
    result = (uint8_t *)(nArg3 - 2);
    if ( nArg3 == 2 )
      *(this + 1891) = 2;  // this+7564 = 形态/模式槽
  }
  else
  {
    result = (uint8_t *)(*(this + 1905) + 512);  // this+7620 = 速度/属性参数对象
    *(this + 1892) = 1;  // this+7568 = 激活/模式槽
    *result = 1;
  }
  return result;
}



// 莲花死亡：LOTUS_DIE + LOTUS_BREAK 播报（105L；this+204/+208 节拍）
// ------------------------------------------------------------
// 0x5C9E30 sub_5C9E30 —— 莲花死亡演出（碎裂）
//   播 LOTUS_DIE 与 LOTUS_BREAK；this[2155] 快照入 this[1545] 并经 vt+196 生效；
//   以朝向 ±90、高度 +120 定位 this[2157] 粒子体经 vt+12(0)/vt+40(位置)/vt+92 输出，
//   交 sub_4600B0(场景, 2, ...) 生成碎裂物；随后对 this[1554] 帧表 0..60 批量 vt+208/vt+204
//   写 -600/-500/-400/-300/-100/+100 节奏收束。
// ------------------------------------------------------------
void /*thiscall*/ sub_5C9E30(uint32_t *this)  // 函数: 莲花死亡演出（碎裂）
{
  int v2; // edx
  int v3; // edi
  int v4; // edi
  int v5; // ebx
  int v6; // edx
  int v7; // eax
  void *fld_e29; // ecx
  int fld_e2155; // [esp-4h] [ebp-30h]
  uint8_t v10[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int fld_e2157; // [esp+1Ch] [ebp-10h]
  int v13; // [esp+28h] [ebp-4h]

  sub_432EA0("LOTUS_DIE", -1, 0, 0);  // 调 音效播放包装（非空判定）
  sub_432EA0("LOTUS_BREAK", -1, 0, 0);  // 调 音效播放包装（非空判定）
  v2 = *this;
  fld_e2155 = *(this + 2155);  // this+8620 = uAI8620
  *(this + 1545) = fld_e2155;  // this+6180〔pAtkCtxC6180〕
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v2 + 196))(this, fld_e2155);  // 调用虚函数（虚表槽 +196）
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 ? 90 : -90;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + v3;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) + 120;  // 调用虚函数（虚表槽 +128）
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2157) + 12))(*(this + 2157), 0);  // this+8628 = 指挥计时戳
  v6 = *this;
  fld_e2157 = *(uint32_t *)*(this + 2157);  // this+8628 = 指挥计时戳
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v6 + 124))(this, v5);  // 调用虚函数（虚表槽 +124）
  (*(void (/*thiscall*/ **)(uint32_t, int, int))(fld_e2157 + 40))(*(this + 2157), v4, v7 + 2);  // this+8628 = 指挥计时戳
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2157) + 92))(*(this + 2157), v10);  // this+8628 = 指挥计时戳
  fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
  v13 = 0;
  sub_4600B0(fld_e29, 2, 0, (int)v10);  // 调 演播层注册(槽号)
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 4));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 8));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
    this,
    -500,
    *(uint32_t *)(*(this + 1554) + 20),  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
    this,
    -400,
    *(uint32_t *)(*(this + 1554) + 24),  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 28));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
    this,
    -300,
    *(uint32_t *)(*(this + 1554) + 28),  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 32));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
    this,
    -100,
    *(uint32_t *)(*(this + 1554) + 32),  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 36));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
    this,
    -100,
    *(uint32_t *)(*(this + 1554) + 36),  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 60));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
    this,
    100,
    *(uint32_t *)(*(this + 1554) + 60),  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 堆释放
}



// 触手挥击（175L）：TRAP_OCTOPUS_SWING + LOTUS_TWIST + LOTUS_READY 三段播报
//   （this+204/+208/8616 相位 —— 章鱼陷阱与莲花共演）
// ------------------------------------------------------------
// 0x5CA150 sub_5CA150 —— 触手挥击/莲花挥手分派
//   进入先清 this+8616；段 0/4..3/7 各写本段帧并对「TRAP_OCTOPUS_SWING」播报后
//   sub_5C9BE0(this, 段, 段) 硬直联动；段 8 播 LOTUS_TWIST 转 LABEL_11；
//   段 9 播 SWING 并四连写 +128..+140 带节奏；段 10/11 写 this[2158]=6、this[2159]=0/1
//   后取 +72/+76 帧；段 12..15 播 LOTUS_READY 并写 +40..+52；段 16 写 +68/-200 与 +64/400。
// ------------------------------------------------------------
void /*thiscall*/ sub_5CA150(uint32_t *this, int nArg2)  // 函数: 触手挥击/莲花挥手分派
{
  int fld_e1554; // eax
  int v4; // edx
  uint32_t *fld_e15542; // eax
  int fld_e15543; // eax
  int v7; // edx

  *((uint8_t *)this + 8616) = 0;  // this+8616 = uAI8616
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        this,
        "TRAP_OCTOPUS_SWING",  // 资源/动画 TAG TRAP_OCTOPUS_SWING
        -1,
        0,
        0);
      sub_5C9BE0(this, nArg2, 0);  // 调 触手硬直联动（±4 段配对）
      return;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        this,
        "TRAP_OCTOPUS_SWING",  // 资源/动画 TAG TRAP_OCTOPUS_SWING
        -1,
        0,
        0);
      sub_5C9BE0(this, nArg2, 1);  // 调 触手硬直联动（±4 段配对）
      return;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        this,
        "TRAP_OCTOPUS_SWING",  // 资源/动画 TAG TRAP_OCTOPUS_SWING
        -1,
        0,
        0);
      sub_5C9BE0(this, nArg2, 2);  // 调 触手硬直联动（±4 段配对）
      return;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        this,
        "TRAP_OCTOPUS_SWING",  // 资源/动画 TAG TRAP_OCTOPUS_SWING
        -1,
        0,
        0);
      sub_5C9BE0(this, nArg2, 3);  // 调 触手硬直联动（±4 段配对）
      return;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "LOTUS_TWIST", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      goto LABEL_11;
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        this,
        "TRAP_OCTOPUS_SWING",  // 资源/动画 TAG TRAP_OCTOPUS_SWING
        -1,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 128));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -600,
        *(uint32_t *)(*(this + 1554) + 128),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 132));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -100,
        *(uint32_t *)(*(this + 1554) + 132),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 136));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        200,
        *(uint32_t *)(*(this + 1554) + 136),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 140));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        300,
        *(uint32_t *)(*(this + 1554) + 140),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      return;
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
      fld_e1554 = *(this + 1554);  // this+6216 = 资源/帧游标表
      v4 = *this;
      *(this + 2158) = 6;  // this+8632〔bDevourFlag(推断)〕
      *(this + 2159) = 0;  // this+8636 = pDollTarget
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 208))(this, *(uint32_t *)(fld_e1554 + 72));  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
      fld_e15542 = (uint32_t *)(*(this + 1554) + 72);  // this+6216 = 资源/帧游标表
      goto LABEL_9;
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
      fld_e15543 = *(this + 1554);  // this+6216 = 资源/帧游标表
      v7 = *this;
      *(this + 2158) = 6;  // this+8632〔bDevourFlag(推断)〕
      *(this + 2159) = 1;  // this+8636 = pDollTarget
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v7 + 208))(this, *(uint32_t *)(fld_e15543 + 76));  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
      fld_e15542 = (uint32_t *)(*(this + 1554) + 76);  // this+6216 = 资源/帧游标表
LABEL_9:
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -200,
        *fld_e15542,
        0,
        0,
        0,
        0);
      break;
    case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
LABEL_11:
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "LOTUS_READY", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));  // this+6216 = 资源/帧游标表
      break;
    case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 68));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        -200,
        *(uint32_t *)(*(this + 1554) + 68),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 64));  // this+6216 = 资源/帧游标表
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        400,
        *(uint32_t *)(*(this + 1554) + 64),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      break;
    default:
      return;
  }
}


// 大型触发 AI（287L 全文件第二；this+8624 相位 —— 陷阱触发→撕咬循环【推断】）
// ------------------------------------------------------------
// 0x5CA5F0 sub_5CA5F0 —— 莲花触发弹幕机（按段随机开火）
//   外层至多 1000 次（超限 off_77F3FC(aCriticalError_41) 报错），内层扫目标表 pArg2 的 +4/+8 面，
//   跳过非类型 17 与 vt+724 已激活者；按段索引 sub_41A5E0(this+7028) 分派：段 12 七五成概率抽
//   左右沿 vt+124/vt+120 链解 30028 打击后 vt+584 落位并 setState(15)；段 13 发 rand%3+2 枚
//   30029 散射；段 14 五连发 1029 号，sub_5C9A30(同房族计数)<3 时置 this+8624=1 经 vt+592 投
//   250/252/253 之一，bFired 后 sub_424120(震屏 3/2000)；段 15 对单目标 sub_4E4A50(…1025…)。
// ------------------------------------------------------------
char /*thiscall*/ sub_5CA5F0(uint8_t *this, int pArg2)  // 函数: 莲花触发弹幕机（按段随机开火）
{
  int pTargetList; // ebx
  int nByteOff; // edi
  int pListBegin; // ecx
  int nRand; // eax
  int pVtTmp; // edx
  int nParam30028; // eax
  int nZ1; // eax
  int nY1; // eax
  int nZ2; // eax
  int nX1; // eax
  int pVt2; // eax
  int nRand2; // edx
  int pTgt3; // ebx
  int nRand3; // eax
  int pObj; // ecx
  int pTgt4; // ebx
  int nRand5; // eax
  int pTgt5; // ebx
  int nRet; // eax
  int pThis_34; // eax
  int pVt3; // edx
  int pThis_342; // eax
  int nRand6; // eax
  int pObj2; // ecx
  int pTgt6; // ebx
  int nRand7; // eax
  int pObj5; // ecx
  int pTgt7; // ebx
  int nRand8; // eax
  int pObj3; // ecx
  int pTgt8; // ebx
  int nRand9; // edx
  int pTgt9; // ebx
  int nRet2; // eax
  int pVt4; // edx
  int nTmp; // ecx
  int pTgt10; // ebx
  int pTgt11; // ebx
  int nRand10; // eax
  int pObj6; // ecx
  int pTgt12; // ebx
  int nRand11; // ebx
  int nRet3; // eax
  int pTgt13; // eax
  int nRand12; // eax
  int pThis_50; // eax
  char result; // al
  int nArgTmp; // [esp-18h] [ebp-54h]
  int pThis_178; // [esp-4h] [ebp-40h]
  uint32_t aShotIds[3]; // [esp+Ch] [ebp-30h]
  int pThis_2A0; // [esp+18h] [ebp-24h]
  int nRand4; // [esp+1Ch] [ebp-20h]
  int nTimer; // [esp+20h] [ebp-1Ch]
  int pTgt; // [esp+24h] [ebp-18h]
  int pTgt2; // [esp+28h] [ebp-14h]
  int i; // [esp+2Ch] [ebp-10h]
  unsigned int nIdx; // [esp+30h] [ebp-Ch]
  int pVtSelf; // [esp+34h] [ebp-8h]
  char bFired; // [esp+3Bh] [ebp-1h]

  pTargetList = pArg2;
  bFired = 0;
  nTimer = 1000;
  while ( 1 )  // 无限循环
  {
    nByteOff = 0;
    nIdx = 0;
    while ( 1 )  // 无限循环
    {
      pListBegin = *(uint32_t *)(pTargetList + 4);
      if ( pListBegin == 0 || nIdx >= (*(uint32_t *)(pTargetList + 8) - pListBegin) >> 2 )  // 向量元素数 = (end−begin)/4
        break;
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pListBegin + nByteOff) + 40))(*(uint32_t *)(pListBegin + nByteOff), 17) == 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
        || (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(nByteOff + *(uint32_t *)(pTargetList + 4)) + 724))(*(uint32_t *)(nByteOff + *(uint32_t *)(pTargetList + 4))) == 1 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
      {
LABEL_35:
        ++nIdx;
        nByteOff += 4;
      }
      else
      {
        switch ( sub_41A5E0((unsigned int)(this + 7028)) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        {
          case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) == 0 || rand() % 100 >= 75 )  // 调 以 16 位种子状态递推并返回 15 位结果
              goto LABEL_35;
            nRand = rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
            pTgt = *(uint32_t *)(nByteOff + *(uint32_t *)(pTargetList + 4));
            pTgt2 = pTgt;
            i = pTgt;
            pVtTmp = *(uint32_t *)this;
            nRand4 = pTgt;
            pVtSelf = pVtTmp;
            nParam30028 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, bool, int, int, uint32_t, uint32_t))(pVtTmp + 52))(  // 调用虚函数（虚表槽 +52）
                   this,
                   0,
                   nRand == 0,
                   200,
                   1,
                   0,
                   0);
            nZ1 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pTgt + 124))(pTgt, 30028, nParam30028);  // 调用虚函数（虚表槽 +124）
            nY1 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pTgt2 + 120))(pTgt2, nZ1);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
            nZ2 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)i + 124))(i, 450, nY1);  // 调用虚函数（虚表槽 +124）
            nX1 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nRand4 + 120))(nRand4, nZ2);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
            (*(void (/*thiscall*/ **)(uint8_t *, int))(pVtSelf + 584))(this, nX1);  // 调用虚函数（虚表槽 +584）【推断: ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6…】
            pVt2 = *(uint32_t *)this;
            bFired = 1;
            (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t))(pVt2 + 560))(this, 15, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
            ++nIdx;
            nByteOff += 4;
            break;
          case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) == 0 || rand() % 100 >= 75 )  // 调 以 16 位种子状态递推并返回 15 位结果
              goto LABEL_35;
            nRand2 = rand() % 3 + 2;  // 调 以 16 位种子状态递推并返回 15 位结果
            if ( nRand2 > 0 )
            {
              for ( i = nRand2; i != 0; --i )  // 循环：i 从 nRand2 递减到 0
              {
                pTgt3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(nByteOff + *(uint32_t *)(pTargetList + 4)) + 120))(*(uint32_t *)(nByteOff + *(uint32_t *)(pTargetList + 4)));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
                nRand3 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
                pObj = *(uint32_t *)(nByteOff + *(uint32_t *)(pArg2 + 4));  // pArg2+4〔宿主对象〕
                pTgt = pTgt3 + nRand3 % 140 - 71;
                pTgt4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 调用虚函数（虚表槽 +124）
                nRand4 = pTgt4 + rand() % 100 - 51;  // 调 以 16 位种子状态递推并返回 15 位结果
                nRand5 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
                pVtSelf = *(uint32_t *)this;
                pTgt5 = nRand5 % 200 + 399;
                nRet = (*(int (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t))(pVtSelf + 152))(this, 200, 1, 0, 0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                pThis_34 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, int))(*(uint32_t *)this + 52))(this, 0, nRet);  // 调用虚函数（虚表槽 +52）
                (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int, int, int, int))(pVtSelf + 584))(  // 调用虚函数（虚表槽 +584）【推断: ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6…】
                  this,
                  pTgt,
                  nRand4,
                  pTgt5,
                  pTgt,
                  nRand4,
                  30029,
                  pThis_34);
                pTargetList = pArg2;
              }
            }
            pVt3 = *(uint32_t *)this;
            bFired = 1;
            (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t))(pVt3 + 560))(this, 15, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
            ++nIdx;
            nByteOff += 4;
            break;
          case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
            {
              for ( i = 5; i != 0; --i )  // 循环：i 从 5 递减到 0
              {
                if ( rand() % 100 < 75 )  // 调 以 16 位种子状态递推并返回 15 位结果
                {
                  nRand6 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
                  pObj2 = *(uint32_t *)(nByteOff + *(uint32_t *)(pTargetList + 4));
                  nRand4 = nRand6 % 5;
                  pTgt6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
                  nRand7 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
                  pObj5 = *(uint32_t *)(nByteOff + *(uint32_t *)(pArg2 + 4));  // pArg2+4〔宿主对象〕
                  pTgt2 = pTgt6 + nRand7 % 81 - 40;
                  pTgt7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 124))(pObj5);  // 调用虚函数（虚表槽 +124）
                  nRand8 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
                  pObj3 = *(uint32_t *)(nByteOff + *(uint32_t *)(pArg2 + 4));  // pArg2+4〔宿主对象〕
                  pTgt = pTgt7 + nRand8 % 61 - 30;
                  pTgt8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 128))(pObj3);  // 调用虚函数（虚表槽 +128）
                  nRand9 = pTgt8 + rand() % 200 + 300;  // 调 以 16 位种子状态递推并返回 15 位结果
                  pTgt9 = *(uint32_t *)this;
                  pVtSelf = nRand9;
                  nRet2 = (*(int (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t))(pTgt9 + 152))(this, 130, 1, 0, 0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                  (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int, int, int, int, uint32_t, int))(pTgt9 + 584))(  // 调用虚函数（虚表槽 +584）【推断: ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6…】
                    this,
                    pTgt2,
                    pTgt,
                    pVtSelf,
                    pTgt2,
                    pTgt,
                    1029,
                    nRand4,
                    0,
                    nRet2);
                  pTargetList = pArg2;
                  bFired = 1;
                }
              }
              if ( sub_5C9A30(this) < 3 )  // 调 同房间 529 族存活计数
              {
                for ( pTgt = 2; pTgt != 0; --pTgt )  // 循环：pTgt 从 2 递减到 0
                {
                  if ( rand() % 100 < 50 )  // 调 以 16 位种子状态递推并返回 15 位结果
                  {
                    pThis_2A0 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 672))(this, 3) - 1;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
                    pVt4 = **(uint32_t **)(nByteOff + *(uint32_t *)(pTargetList + 4));
                    nTmp = *(uint32_t *)(nByteOff + *(uint32_t *)(pTargetList + 4));
                    aShotIds[0] = 250;
                    aShotIds[1] = 252;
                    aShotIds[2] = 253;
                    i = 100;
                    pTgt10 = (*(int (/*thiscall*/ **)(int))(pVt4 + 128))(nTmp);  // 调用虚函数（虚表槽 +128）
                    nRand4 = pTgt10 + rand() % 200 + 500;  // 调 以 16 位种子状态递推并返回 15 位结果
                    do
                    {
                      pTgt11 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(nByteOff + *(uint32_t *)(pArg2 + 4)) + 120))(*(uint32_t *)(nByteOff + *(uint32_t *)(pArg2 + 4)));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
                      nRand10 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
                      pObj6 = *(uint32_t *)(nByteOff + *(uint32_t *)(pArg2 + 4));  // pArg2+4〔宿主对象〕
                      pTgt2 = pTgt11 + nRand10 % 40 - 20;
                      pTgt12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj6 + 124))(pObj6);  // 调用虚函数（虚表槽 +124）
                      nRand11 = pTgt12 + rand() % 20 - 10;  // 调 以 16 位种子状态递推并返回 15 位结果
                      if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)this + 136))(  // 调用虚函数（虚表槽 +136）
                             this,
                             pTgt2,
                             nRand11,
                             0) != 0 )
                        break;
                    }
                    while ( i-- > 0 );
                    nRet3 = *(uint32_t *)this;
                    *(this + 8624) = 1;  // this+8624 【推断】子类AI槽
                    pVtSelf = nRet3;
                    pTgt13 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(nRet3 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                            this,
                            0,
                            0,
                            0,
                            0xFFFF,
                            0,
                            0,
                            0,
                            0);
                    pThis_178 = (*(int (/*thiscall*/ **)(uint8_t *, int, int, int, int, int))(*(uint32_t *)this + 376))(  // 调用虚函数（虚表槽 +376）
                            this,
                            pThis_2A0,
                            pTgt2,
                            nRand11,
                            nRand4,
                            pTgt13);
                    nRand12 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
                    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, int))(pVtSelf + 592))(this, aShotIds[nRand12 % 3], pThis_178);  // 调用虚函数（虚表槽 +592）【推断: 位置/状态同步包发布（短版 48024 / 长版 type 22…】
                    pTargetList = pArg2;
                    *(this + 8624) = 0;  // this+8624 【推断】子类AI槽
                    bFired = 1;
                  }
                }
              }
            }
            if ( bFired != 0 )
            {
              pThis_50 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);  // 调用虚函数（虚表槽 +80）
              sub_424120(*(uint32_t **)(pThis_50 + 132), 3, 2000);  // 调 屏幕震动启动
            }
            goto LABEL_35;
          case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) == 0 || rand() % 100 >= 75 )  // 调 以 16 位种子状态递推并返回 15 位结果
              goto LABEL_35;
            nArgTmp = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(nByteOff + *(uint32_t *)(pTargetList + 4)) + 124))(*(uint32_t *)(nByteOff + *(uint32_t *)(pTargetList + 4)));  // 调用虚函数（虚表槽 +124）
            pThis_342 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 52))(this);  // 调用虚函数（虚表槽 +52）
            sub_4E4A50(nByteOff, (int)this, 1025, pThis_342, 0, nArgTmp, 500, 0, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
            bFired = 1;
            ++nIdx;
            nByteOff += 4;
            break;
          default:
            goto LABEL_35;
        }
      }
    }
    if ( --nTimer <= 0 )
      return off_77F3FC(aCriticalError_41);  // 调 off_77F3FC（引擎日志输出函数）
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    if ( result != 0 )  // 若结果非 0（成功）
    {
      result = bFired;
      if ( bFired == 0 )
        continue;
    }
    return result;
  }
}


// 窃笑：LOTUS_LAUGH 播报（84L；sub_699000+sub_493D00 变速换锚 —— 笑时动画变速）
// ------------------------------------------------------------
// 0x5CABB0 sub_5CABB0 —— 笑态事件钩（LOTUS_LAUGH）
//   先 sub_5C9410 试挂接；事件 8 且参数首项 16 且 clock_now(this+2160)>5000（距上次笑超 5 秒）时
//   继续：递减 this[2158] 计数（归零则清 this[2159]=-1 并转段 0），主状态镜像 this[1639]==8 时
//   sub_5C9550(段) 重写节拍、==14 时 vt+604(1) 蓄力；再 sub_4E33D0 基类收尾后分段：5 走
//   ·0x5C9E30 死亡演出、8 走 ·0x5CA150 并 sub_493D00 变速 100/200.0 后 sub_493B70、
//   14 走 vt+604(0) 并播「LOTUS_LAUGH」。
// ------------------------------------------------------------
char /*thiscall*/ sub_5CABB0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 笑态事件钩（LOTUS_LAUGH）
{
  int v5; // edi
  unsigned int pThis_870; // eax
  int fld_e2158; // eax
  int fld_e1639; // eax
  int pThis_6DD; // eax
  int pThis_6DD2; // eax
  unsigned int pThis_6DD3; // ecx
  int v13; // eax
  int pThis_6DD4; // eax
  int v15; // eax

  v5 = ArgList;
  LOBYTE(pThis_870) = sub_5C9410(ArgList, LODWORD(fArg3));  // 调 触手就绪/挂接分派
  if ( (uint8_t)pThis_870 == 0
    && (ArgList != 8 || **(uint32_t **)(LODWORD(fArg3) + 4) != 16 || (int)(pThis_870 = sub_699000((int)(this + 2160))) > 5000) )  // 【clock_now(clk)】
  {
    if ( *(this + 2159) != -1 )  // this+8636 = pDollTarget
    {
      if ( ArgList != 8 || (fld_e2158 = *(this + 2158), *(this + 2158) = fld_e2158 - 1, fld_e2158 <= 0) )  // this+8632〔bDevourFlag(推断)〕
      {
        *(this + 2159) = -1;  // this+8636 = pDollTarget
        v5 = 0;
      }
    }
    fld_e1639 = *(this + 1639);  // this+6556 = 主状态镜像
    if ( fld_e1639 == 8 )
    {
      pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      sub_5C9550(pThis_6DD);  // 调 触手硬直节拍表（按段写本+位移）
    }
    else if ( fld_e1639 == 14 )
    {
      (*(void (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
    }
    LOBYTE(pThis_870) = sub_4E33D0(v5, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
    switch ( v5 )  // 按 v5 分派
    {
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        LOBYTE(pThis_870) = sub_5C9E30(this);  // 调 莲花死亡演出（碎裂）
        break;
      case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
        pThis_6DD2 = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        sub_5CA150(pThis_6DD2);  // 调 触手挥击/莲花挥手分派
        pThis_870 = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        if ( pThis_870 < 8 )
        {
          pThis_6DD3 = (unsigned int)(this + 1757);  // this+7028〔nAttackSegSlot(推断)〕
          if ( *(this + 2159) == -1 )  // this+8636 = pDollTarget
          {
            v15 = sub_41A5E0(pThis_6DD3);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
            sub_493D00(*(uint32_t *)(*(this + 1550) + 4 * v15), 100.0);  // 调 ★变速（研究§26）
          }
          else
          {
            v13 = sub_41A5E0(pThis_6DD3);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
            sub_493D00(*(uint32_t *)(*(this + 1550) + 4 * v13), 200.0);  // 调 ★变速（研究§26）
          }
          pThis_6DD4 = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
          LOBYTE(pThis_870) = sub_493B70(*(uint32_t *)(*(this + 1550) + 4 * pThis_6DD4));  // 调 同步源模式下重算累计时间（sub_493A60 链）
        }
        break;
      case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
        LOBYTE(pThis_870) = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                       this,
                       "LOTUS_LAUGH",  // 资源/动画 TAG LOTUS_LAUGH
                       -1,
                       0,
                       0);
        break;
      default:
        break;
    }
  }
  return pThis_870;
}



// 参数打包 AI（sub_431230; this+568 最后受击时刻）
// ------------------------------------------------------------
// 0x5CAD60 sub_5CAD60 —— 段 8 随机招（阈值 this[2150]）
//   门：vt+308 可用、vt+568 状态 !=8、vt+840 姿态为 0，且 rand()%300 < this[2150]（万分比阈值）。
//   以 sub_431230 打包 v3[0]=12 后 setState(8, 包体) 触发，尾 sub_5E5260 释放包体。
// ------------------------------------------------------------
void /*thiscall*/ sub_5CAD60(uint32_t *this)  // 函数: 段 8 随机招（阈值 this[2150]）
{
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v3[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 568))(this) != 8  // 调用虚函数（虚表槽 +568）
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && rand() % 300 < *(this + 2150) )  // 调 以 16 位种子状态递推并返回 15 位结果
  {
    memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
    v3[3] = 0;
    v3[0] = 12;
    sub_431230((int)pBuf, v3);  // 调 uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
}



// 参数打包 AI（sub_431230; this+568）
// ------------------------------------------------------------
// 0x5CAE10 sub_5CAE10 —— 与 ·0x5CAD60 同构（差异：阈值 this[2151]、包体 v3[0]=13）
//   阈值四连槽 this+2150..2153 由 ·0x5CB360 经 vt[96](0..3) 一次性初始化。
// ------------------------------------------------------------
void /*thiscall*/ sub_5CAE10(uint32_t *this)  // 函数: 与 ·0x5CAD60 同构（差异：阈值 this[2151]、包体 v3[0]=13）
{
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v3[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 568))(this) != 8  // 调用虚函数（虚表槽 +568）
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && rand() % 300 < *(this + 2151) )  // 调 以 16 位种子状态递推并返回 15 位结果
  {
    memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
    v3[3] = 0;
    v3[0] = 13;
    sub_431230((int)pBuf, v3);  // 调 uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
}



// 参数打包 AI（sub_431230; this+568）
// ------------------------------------------------------------
// 0x5CAEC0 sub_5CAEC0 —— 与 ·0x5CAD60 同构（差异：阈值 this[2152]、包体 v3[0]=14；
//   this[2152] 由 ·0x5C9D60 ·0x5C9DD0 收放）
// ------------------------------------------------------------
void /*thiscall*/ sub_5CAEC0(uint32_t *this)  // 函数: 与 ·0x5CAD60 同构（差异：阈值 this[2152]、包体 v3[0]=14；
{
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v3[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 568))(this) != 8  // 调用虚函数（虚表槽 +568）
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && rand() % 300 < *(this + 2152) )  // 调 以 16 位种子状态递推并返回 15 位结果
  {
    memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
    v3[3] = 0;
    v3[0] = 14;
    sub_431230((int)pBuf, v3);  // 调 uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
}



// 参数打包 AI（sub_431230; this+568）
// ------------------------------------------------------------
// 0x5CAF70 sub_5CAF70 —— 与 ·0x5CAD60 同构（差异：阈值 this[2153]、包体 v3[0]=15）
//   本槽为四连槽末位（this+2153），同为 ·0x5CB020 依次调用的四个段 8 随机招之一。
// ------------------------------------------------------------
void /*thiscall*/ sub_5CAF70(uint32_t *this)  // 函数: 与 ·0x5CAD60 同构（差异：阈值 this[2153]、包体 v3[0]=15）
{
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v3[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 568))(this) != 8  // 调用虚函数（虚表槽 +568）
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && rand() % 300 < *(this + 2153) )  // 调 以 16 位种子状态递推并返回 15 位结果
  {
    memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
    v3[3] = 0;
    v3[0] = 15;
    sub_431230((int)pBuf, v3);  // 调 uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CB020 sub_5CB020 —— 行为字 23 相位驱动
//   sub_4E0120 通用分派；行为字 this[1787] !=23 时 vt+1104(this,23) 切入；
//   随后连做 ·0x5CAD60 ·0x5CAE10 ·0x5CAEC0 ·0x5CAF70 四个段 8 随机招门，
//   尾调 ·0x5C9AF0（抑扰器在场检测）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CB020(int *this)  // 函数: 行为字 23 相位驱动
{
  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  if ( *(this + 1787) != 23 )  // this+7148 = nBigState
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 23);  // 调用虚函数（虚表槽 +1104）
  sub_5CAD60(this);  // 调 段 8 随机招（阈值 this[2150]）
  sub_5CAE10(this);  // 调 与 ·0x5CAD60 同构（差异：阈值 this[2151]、包体 v3[0]=13）
  sub_5CAEC0(this);  // 调 与 ·0x5CAD60 同构（差异：阈值 this[2152]、包体 v3[0]=14；
  sub_5CAF70(this);  // 调 与 ·0x5CAD60 同构（差异：阈值 this[2153]、包体 v3[0]=15）
  return sub_5C9AF0(this);  // 调 抑扰器在场检测（写 1905 块 +512）
}



// 大型 AI（124L）
// ------------------------------------------------------------
// 0x5CB070 sub_5CB070 —— 信徒集结压制（256 段目标广播）
//   sub_4E0CD0(17,0,v14,-1) 取型 17 目标表后逐项：rand()%3 取 dword_730C10 三槽之一作莲花 id，
//   经 vt+48/vt+52 取目标 X/Y 与随机 id 以 sub_430C80 压入三列参数表，append 0xFFFF 终止符，
//   末 setState(16, 表体)；调用点 ·0x5CB690 段 16 且 vt+200+148==1。【id 表语义推断】
// ------------------------------------------------------------
void /*thiscall*/ sub_5CB070(void *this)  // 函数: 信徒集结压制（256 段目标广播）
{
  uint8_t *pVecBegin; // edx
  char *pVecEnd; // esi
  int nVecCap; // ecx
  unsigned int nIdx; // ebx
  int nRand; // eax
  int pTgt; // ecx
  int nTgtX; // eax
  char *pVecEnd3; // edi
  int nTgtY; // eax
  char *pVecEnd4; // esi
  uint32_t *pVecEnd5; // edx
  uint32_t *pVecEnd6; // eax
  unsigned int nCnt; // eax
  char v14[4]; // [esp+Ch] [ebp-38h] BYREF
  void *Block; // [esp+10h] [ebp-34h]
  int v16; // [esp+14h] [ebp-30h]
  int v17; // [esp+18h] [ebp-2Ch]
  char v18[4]; // [esp+1Ch] [ebp-28h] BYREF
  uint8_t *pVecBegin2; // [esp+20h] [ebp-24h]
  void *Src; // [esp+24h] [ebp-20h]
  int nVecCap2; // [esp+28h] [ebp-1Ch]
  void *pThis; // [esp+2Ch] [ebp-18h]
  int nLotusId; // [esp+30h] [ebp-14h] BYREF
  int v24; // [esp+34h] [ebp-10h] BYREF
  int v25; // [esp+40h] [ebp-4h]

  pThis = this;
  Block = nullptr;
  v16 = 0;
  v17 = 0;
  v25 = 0;
  sub_4E0CD0(17, 0, v14, -1);  // 调 按条件号收集对象（阵营/距离/归属过滤，返回计数）
  pVecBegin = nullptr;
  pVecEnd = nullptr;
  nVecCap = 0;
  pVecBegin2 = nullptr;
  Src = nullptr;
  nVecCap2 = 0;
  LOBYTE(v25) = 1;  // 调 取 16 位值低 8 位
  nIdx = 0;
  while ( Block != nullptr && nIdx < (v16 - (int)Block) >> 2 )
  {
    nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
    pTgt = *((uint32_t *)Block + nIdx);
    nLotusId = dword_730C10[nRand % 3];
    nTgtX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTgt + 48))(pTgt);  // 调用虚函数（虚表槽 +48）
    pVecEnd3 = (char *)Src;
    v24 = nTgtX;
    if ( pVecBegin2 != nullptr && ((uint8_t *)Src - pVecBegin2) >> 2 < (unsigned int)((nVecCap2 - (int)pVecBegin2) >> 2) )  // 向量元素数 = (end−begin)/4
    {
      *(uint32_t *)Src = nTgtX;
      Src = pVecEnd3 + 4;
    }
    else
    {
      sub_430C80(Src, 1, (int)&v24);  // 调 uint32 vector 区间插入（同值填充）
    }
    nTgtY = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + nIdx) + 52))(*((uint32_t *)Block + nIdx));  // 调用虚函数（虚表槽 +52）
    pVecEnd4 = (char *)Src;
    v24 = nTgtY;
    if ( pVecBegin2 != nullptr && ((uint8_t *)Src - pVecBegin2) >> 2 < (unsigned int)((nVecCap2 - (int)pVecBegin2) >> 2) )  // 向量元素数 = (end−begin)/4
    {
      pVecEnd5 = (char *)Src + 4;
      *(uint32_t *)Src = nTgtY;
      Src = pVecEnd4 + 4;
    }
    else
    {
      sub_430C80(Src, 1, (int)&v24);  // 调 uint32 vector 区间插入（同值填充）
      pVecEnd5 = Src;
    }
    if ( pVecBegin2 != nullptr && ((char *)pVecEnd5 - pVecBegin2) >> 2 < (unsigned int)((nVecCap2 - (int)pVecBegin2) >> 2) )  // 向量元素数 = (end−begin)/4
    {
      pVecEnd6 = pVecEnd5;
      *pVecEnd5 = nLotusId;
      nVecCap = nVecCap2;
      pVecBegin = pVecBegin2;
      pVecEnd = (char *)(pVecEnd6 + 1);
      ++nIdx;
      Src = pVecEnd6 + 1;
    }
    else
    {
      sub_430C80(pVecEnd5, 1, (int)&nLotusId);  // 调 uint32 vector 区间插入（同值填充）
      pVecEnd = (char *)Src;
      nVecCap = nVecCap2;
      pVecBegin = pVecBegin2;
      ++nIdx;
    }
  }
  if ( pVecBegin != nullptr )  // 若 pVecBegin 有效（非空）
  {
    nCnt = (pVecEnd - pVecBegin) >> 2;  // 向量元素数 = (end−begin)/4
    if ( nCnt != 0 )
    {
      nLotusId = 0xFFFF;  // 常量 0xFFFF（= 0xFFFF）
      if ( nCnt >= (nVecCap - (int)pVecBegin) >> 2 )
      {
        sub_430C80(pVecEnd, 1, (int)&nLotusId);  // 调 uint32 vector 区间插入（同值填充）
      }
      else
      {
        *(uint32_t *)pVecEnd = 0xFFFF;  // 常量 0xFFFF（= 0xFFFF）
        Src = pVecEnd + 4;
      }
      (*(void (/*thiscall*/ **)(void *, int, char *, uint32_t, uint32_t))(*(uint32_t *)pThis + 560))(pThis, 16, v18, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      pVecBegin = pVecBegin2;
    }
    if ( pVecBegin != nullptr )  // 若 pVecBegin 有效（非空）
      j__free(pVecBegin);  // 调 堆释放
  }
  pVecBegin2 = nullptr;
  Src = nullptr;
  nVecCap2 = 0;
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 堆释放
}


// 参数打包 AI（sub_431230; this+200）
// ------------------------------------------------------------
// 0x5CB270 sub_5CB270 —— 段 10/11 随机子招（this[2159] 选半区）
//   门：vt+200 的 +170 标记非 0 且 vt+308 可用。由静态表 {4,5,6,7,0,1,2,3} 按
//   v2[4 * this[2159] + rand()%4]（this[2159] 为 0/1 两半区）取样后 sub_431230 打包，
//   setState(8, 包体) 触发，尾 j__free 释放。
// ------------------------------------------------------------
void /*thiscall*/ sub_5CB270(uint32_t *this)  // 函数: 段 10/11 随机子招（this[2159] 选半区）
{
  uint32_t v2[8]; // [esp+8h] [ebp-40h]
  uint8_t v3[4]; // [esp+28h] [ebp-20h] BYREF
  void *Block; // [esp+2Ch] [ebp-1Ch]
  int v5; // [esp+30h] [ebp-18h]
  int v6; // [esp+34h] [ebp-14h]
  uint32_t v7[4]; // [esp+38h] [ebp-10h] BYREF

  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  {
    v2[0] = 4;
    v2[1] = 5;
    v2[2] = 6;
    v2[3] = 7;
    v2[4] = 0;
    v2[5] = 1;
    v2[6] = 2;
    v2[7] = 3;
    v7[0] = v2[4 * *(this + 2159) + rand() % 4];  // 调 以 16 位种子状态递推并返回 15 位结果
    Block = nullptr;
    v5 = 0;
    v6 = 0;
    v7[3] = 0;
    sub_431230((int)v3, v7);  // 调 uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v3, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
  }
}



// 莲花受击演出：Particle/DieSmoke.ptl + LOTUS_DMG + LOTUS_LAUGH 播报（142L；
//   this+8616/8624/8653/8654/8668/8669 相位）
// ------------------------------------------------------------
// 0x5CB360 sub_5CB360 —— 莲花初始化/受击演出复位
//   以 vt[52]/vt[51]（vt+208/vt+204）对 this[1554] 帧表 0..4/10..13 批量写 -600..+300 节奏；
//   this[2150..2153] 由 vt[96]（vt+384 出场参数面）取 0..3 号值；清 this+7528/8616，vt+144(0) 归位，
//   this[1545] 与 this[2155] 互换快照；operator new(0x12Cu) 后 sub_4C3640 载 Particle/DieSmoke.ptl 交 this[2157]；
//   构造 LOTUS_DMG/LOTUS_LAUGH 文案并 sub_4E1390(196613) 注册；this[40]=200，this[2158]=0，
//   this[2159]=-1，清 +8653/8654、sub_698F90(this+2160) 启倒计时、清 +8668/8669。
// ------------------------------------------------------------
char /*thiscall*/ sub_5CB360(uint32_t **this)  // 函数: 莲花初始化/受击演出复位
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  uint32_t *fld_e1545; // eax
  uint32_t *pThis_5B; // eax
  char result; // al
  int v9; // [esp+Ch] [ebp-10h] BYREF
  int v10; // [esp+18h] [ebp-4h]

  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 1554));  // this+6216 = 资源/帧游标表
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -500,
    **(this + 1554),  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[1]);  // this+6216 = 资源/帧游标表
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -400,
    (*(this + 1554))[1],  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[2]);  // this+6216 = 资源/帧游标表
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -300,
    (*(this + 1554))[2],  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[3]);  // this+6216 = 资源/帧游标表
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -100,
    (*(this + 1554))[3],  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[4]);  // this+6216 = 资源/帧游标表
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -100,
    (*(this + 1554))[4],  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[10]);  // this+6216 = 资源/帧游标表
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -600,
    (*(this + 1554))[10],  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[11]);  // this+6216 = 资源/帧游标表
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -100,
    (*(this + 1554))[11],  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[12]);  // this+6216 = 资源/帧游标表
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    200,
    (*(this + 1554))[12],  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[13]);  // this+6216 = 资源/帧游标表
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    300,
    (*(this + 1554))[13],  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  *(this + 2150) = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[96])(this, 0);  // this+8600 = uAI8600
  v2 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[96])(this, 1);
  v3 = (int)*this;
  *(this + 2151) = (uint32_t *)v2;  // this+8604 = bAI8604
  *(this + 2152) = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t **, int))(v3 + 384))(this, 2);  // this+8608 = uAI8608
  v4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[96])(this, 3);
  v5 = (int)*this;
  *(this + 2153) = (uint32_t *)v4;  // this+8612 = uAI8612
  *((uint8_t *)this + 7528) = 0;  // this+7528 = 内嵌配置块 +8 字节
  *((uint8_t *)this + 8616) = 0;  // this+8616 = uAI8616
  (*(void (/*thiscall*/ **)(uint32_t **, uint32_t))(v5 + 144))(this, 0);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
  fld_e1545 = *(this + 1545);  // this+6180〔pAtkCtxC6180〕
  *(this + 1702) = nullptr;  // this+6808 = 炮车/子类参数面槽 5
  *(this + 2155) = fld_e1545;  // this+8620 = uAI8620
  *(this + 1545) = nullptr;  // this+6180〔pAtkCtxC6180〕
  v10 = 0;
  if ( operator new(0x12Cu) != nullptr )  // operator new 分配 300 字节
  {
    if ( (unsigned int)*(this + 96) < 0x10 )  // this+384 = 动画件名 SSO 容量判据
      pThis_5B = (uint32_t *)sub_4C3640(this + 91, "Particle/DieSmoke.ptl", this);  // 资源路径 Particle/DieSmoke.ptl
    else
      pThis_5B = (uint32_t *)sub_4C3640(*(this + 91), "Particle/DieSmoke.ptl", this);  // this+364 = 动画件名缓冲 SSO 内联首址
  }
  else
  {
    pThis_5B = nullptr;
  }
  v10 = -1;
  *(this + 2157) = pThis_5B;  // this+8628 = 指挥计时戳
  sub_4015C0("LOTUS_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("LOTUS_LAUGH", 0xBu);  // 【std::string构造赋值】
  *(this + 40) = (uint32_t *)200;  // this+40 物品状态附属标志
  v9 = 100000;
  sub_4E1390(196613, &v9);  // 调 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
  *((uint8_t *)this + 8624) = 0;  // this+8624 = uAI8624
  *(this + 2158) = nullptr;  // this+8632〔bDevourFlag(推断)〕
  *(this + 2159) = (uint32_t *)-1;  // this+8636 = pDollTarget
  *((uint8_t *)this + 8653) = 0;  // this+8653 【推断】相位门字节
  *((uint8_t *)this + 8654) = 0;
  result = sub_698F90((int)(this + 2160), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint8_t *)this + 8668) = 0;  // this+8668 = nCool8668
  *((uint8_t *)this + 8669) = 0;  // this+8669 = 守卫激活位
  return result;
}


// 莲花攻击状态机（127L）：LOTUS_ATK + LOTUS_SWEEP + R_BELIEVER_ALERT（信徒警觉!）+
//   LOTUS_SWEEP_LOOP/READY_LOOP（this+200/8616/8636/8668/8669 相位）
// ------------------------------------------------------------
// 0x5CB690 sub_5CB690 —— 莲花攻击状态机（姿态 8 分派）
//   sub_4E1780 基类前置；姿态 8 时按段索引 this[7028] 分派：段 0..7 在 vt+200+148 ≥3 且 this+8616
//   未触发时播「LOTUS_ATK」，flags 门 this+8636 != -1 落 LABEL_7 转 ·0x5CB270；段 8 播「LOTUS_SWEEP」；
//   段 10/11 亦转 ·0x5CB270；段 12..15 在计数==3 时 sub_4E0CD0(17…) 取表，非空转 ·0x5CA5F0、
//   空则 ·0x5C9A00，段 15 追加播「R_BELIEVER_ALERT」（信徒警觉）；段 16 在 vt+308 且 +170 非 0 时
//   setState(0) 收或转 ·0x5CB070；尾部按 (姿态 8 且段 15)/空闲维护「LOTUS_SWEEP_LOOP」/「LOTUS_READY_LOOP」。
// ------------------------------------------------------------
uint8_t /*thiscall*/ sub_5CB690(int this)  // 函数: 莲花攻击状态机（姿态 8 分派）
{
  bool pThis_348; // zf
  uint8_t result; // al
  void *v4; // [esp+8h] [ebp-1Ch] BYREF
  int v5; // [esp+Ch] [ebp-18h]
  int v6; // [esp+10h] [ebp-14h]
  int v7; // [esp+14h] [ebp-10h]
  int v8; // [esp+20h] [ebp-4h]

  sub_4E1780((uint32_t *)this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    switch ( sub_41A5E0(this + 7028) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 3  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          && *(uint8_t *)(this + 8616) == 0 )  // this+8616 【推断】钻地相位字节1
        {
          sub_432EA0("LOTUS_ATK", -1, 0, 0);  // 调 音效播放包装（非空判定）
          *(uint8_t *)(this + 8616) = 1;  // this+8616 【推断】钻地相位字节1
        }
        if ( *(uint32_t *)(this + 8636) != -1 )  // this+8636 【推断】传送/钻地相位槽
          goto LABEL_7;
        break;
      case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 3  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          && *(uint8_t *)(this + 8616) == 0 )  // this+8616 【推断】钻地相位字节1
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
            this,
            "LOTUS_SWEEP",  // 资源/动画 TAG LOTUS_SWEEP
            -1,
            0,
            0);
          *(uint8_t *)(this + 8616) = 1;  // this+8616 【推断】钻地相位字节1
        }
        break;
      case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
      case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
LABEL_7:
        sub_5CB270(this);  // 调 段 10/11 随机子招（this[2159] 选半区）
        break;
      case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
      case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) == 3  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          && *(uint8_t *)(this + 8616) == 0 )  // this+8616 【推断】钻地相位字节1
        {
          v5 = 0;
          v6 = 0;
          v7 = 0;
          v8 = 0;
          sub_4E0CD0((uint32_t *)this, 17, 0, (int)&v4, -1);  // 调 按条件号收集对象（阵营/距离/归属过滤，返回计数）
          if ( v5 != 0 && (v6 - v5) >> 2 != 0 )  // 向量元素数 = (end−begin)/4
            sub_5CA5F0((uint8_t *)this, (int)&v4);  // 调 莲花触发弹幕机（按段随机开火）
          else
            sub_5C9A00(this);  // 调 帧游标复位 + 帧写入
          *(uint8_t *)(this + 8616) = 1;  // this+8616 【推断】钻地相位字节1
          if ( sub_41A5E0(this + 7028) == 15 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
            sub_432EA0("R_BELIEVER_ALERT", -1, 0, 0);  // 调 音效播放包装（非空判定）
          v8 = -1;
          sub_5E5260(&v4);  // 调 动画子对象清理临时缓冲
        }
        break;
      case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        {
          if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
          }
          else if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) == 1  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
                 && *(uint8_t *)(this + 8616) == 0 )  // this+8616 【推断】钻地相位字节1
          {
            sub_5CB070(this);  // 调 信徒集结压制（256 段目标广播）
            *(uint8_t *)(this + 8616) = 1;  // this+8616 【推断】钻地相位字节1
          }
        }
        break;
      default:
        break;
    }
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0(this + 7028) == 15 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( *(uint8_t *)(this + 8668) == 0 )  // this+8668 【推断】人偶行为模式
    {
      sub_432EA0("LOTUS_SWEEP_LOOP", 9, 0, 0);  // 调 音效播放包装（非空判定）
      *(uint8_t *)(this + 8668) = 1;  // this+8668 【推断】人偶行为模式
    }
  }
  else if ( *(uint8_t *)(this + 8668) == 1 )  // this+8668 【推断】人偶行为模式
  {
    sub_432EE0(9);  // 调 音效 TAG 查询包装
    *(uint8_t *)(this + 8668) = 0;  // this+8668 【推断】人偶行为模式
  }
  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0;  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  result = *(uint8_t *)(this + 8669);  // this+8669 守卫激活位
  if ( pThis_348 )
  {
    if ( result == 0 )
    {
      result = (uint8_t)sub_432EA0("LOTUS_READY_LOOP", 9, 0, 0);  // 调 音效播放包装（非空判定）
      *(uint8_t *)(this + 8669) = 1;  // this+8669 守卫激活位
    }
  }
  else if ( result == 1 )
  {
    result = sub_432EE0(9);  // 调 音效 TAG 查询包装
    *(uint8_t *)(this + 8669) = 0;  // this+8669 守卫激活位
  }
  return result;
}


// 子类扩展字段复位（this+8600..8609）
// ------------------------------------------------------------
// 0x5CB970 sub_5CB970 —— 章鱼/莲花子类状态复位
//   清 this+8604 与 +8600/+8601/+8602/+8608/+8609 六个相位字节及 +7144 处字节，返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CB970(int this)  // 函数: 章鱼/莲花子类状态复位
{
  *(uint32_t *)(this + 8604) = 0;  // this+8604 子类 AI 状态槽
  *(uint8_t *)(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
  *(uint8_t *)(this + 8601) = 0;  // this+8601 子类 AI 状态字节 2
  *(uint8_t *)(this + 8602) = 0;  // this+8602 子类 AI 状态字节 3
  *(uint8_t *)(this + 8608) = 0;  // this+8608 攻击/触发一次性门
  *(uint8_t *)(this + 8609) = 0;  // this+8609 攻击/触发一次性门伴位
  *(uint8_t *)(this + 7144) = 0;  // this+7144 单次门字节
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CB9A0 sub_5CB9A0 —— 双向跟随槽解绑
// ·参数与自身相等时查 vt+316 判定，为假则 vt+312 清挂接
// ·与 fld 1815 主对象相等时反向处理；尾部转发 sub_4D9170 消亡通知【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5CB9A0(uint32_t *this, uint32_t *uArg2)  // 函数: 双向跟随槽解绑
{
  if ( uArg2 == this && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 316))(this) == 0 )  // 调用虚函数（虚表槽 +316）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);  // 虚函数调用 槽+312：濒死/一击表现（LAST STRIKE；死亡链上游）【新发现(会话 3)】
  if ( uArg2 == (uint32_t *)*(this + 1815) && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 316))(this) != 0 )  // 调用虚函数（虚表槽 +316）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);  // 虚函数调用 槽+312：濒死/一击表现（LAST STRIKE；死亡链上游）【新发现(会话 3)】
  return sub_4D9170(uArg2);  // 调 消亡通知
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CBA00 sub_5CBA00 —— 挂接对象坐标同步
// ·fld 1813 挂接对象非空时取 vt+152 参数面(100,1)，经其 vt+124/120 双轴解算
// ·结果经 vt+584 位置写入同步分身坐标【推断】
// ------------------------------------------------------------
void /*thiscall*/ sub_5CBA00(uint32_t *this)  // 函数: 挂接对象坐标同步
{
  int fld_e1813; // esi
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax

  fld_e1813 = *(this + 1813);  // this+7252 = pTarget7252
  if ( fld_e1813 != 0 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t))(*this + 152))(this, 100, 1, 0, 0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v5 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813, 30351, 0, 0, v4);  // 调用虚函数（虚表槽 +124）
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, v5);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v7 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813, 0, v6);  // 调用虚函数（虚表槽 +124）
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, v7);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v3 + 584))(this, v8);  // 调用虚函数（虚表槽 +584）【推断: ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6…】
  }
}



// 草丛陷阱：Particle/PoisonBug.ptl 毒虫 + TRAP_GRASS_UP 草丛升起（102L）
// ------------------------------------------------------------
// 0x5CBA60 sub_5CBA60 —— 草丛陷阱段分派
// ·this+8608 惰性门触发 vt+1308；主状态镜像 1639==8 时按 7028 段号分流
// ·段 0/2 调 5CBA00 分身同步；段 1 发射 48021 并 vt+588 载 Particle/PoisonBug.ptl 毒虫
// ·段号空：vt+212 播 TRAP_GRASS_UP 草丛升起，置 8609 一次门
// ------------------------------------------------------------
char /*thiscall*/ sub_5CBA60(uint8_t *this)  // 函数: 草丛陷阱段分派
{
  int v2; // eax
  int pThis_1E; // edi
  int pThis_1B74; // eax
  int v5; // eax
  int pThis_180; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edi
  int v10; // ebx
  int pThis_98; // eax
  int pThis_982; // eax

  if ( *((uint32_t *)this + 2090) != 0 && *(this + 8608) == 0 )  // this+8360 = 拾取信息 7 字节对象指针
  {
    v2 = *(uint32_t *)this;
    *(this + 8608) = 1;  // this+8608 = uAI8608
    (*(void (**)(void))(v2 + 1308))();  // 调用虚函数（虚表槽 +1308）
  }
  if ( *((uint32_t *)this + 1639) == 8 )  // this+6556 = 主状态镜像
  {
    pThis_1E = *(uint32_t *)(*((uint32_t *)this + 30) + 148);  // this+120 = 动画对象指针
    pThis_1B74 = sub_41A5E0((unsigned int)(this + 7028));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( pThis_1B74 != 0 )
    {
      v5 = pThis_1B74 - 1;
      if ( v5 != 0 )
      {
        if ( v5 == 1 )
        {
          if ( pThis_1E >= 3
            && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
            && *(this + 8600) != 0 )  // this+8600 子类 AI 状态字节 1
          {
            pThis_180 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 384))(this, 0);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
            (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t, int, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
              this,
              48021,
              pThis_180,
              0,
              0,
              100,
              1,
              0,
              4,
              0,
              0,
              0);
            *(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
          }
          if ( pThis_1E >= 4
            && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
            && *(this + 8601) != 0 )  // this+8601 子类 AI 状态字节 2
          {
            v7 = *(uint32_t *)this;
            *(this + 8601) = 0;  // this+8601 子类 AI 状态字节 2
            v8 = (*(int (/*thiscall*/ **)(uint8_t *, const char *))(v7 + 588))(this, "Particle/PoisonBug.ptl");  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
            v9 = *(uint32_t *)this;
            v10 = v8;
            pThis_98 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(this, 0, 0, 0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            pThis_982 = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                    this,
                    v10,
                    0,
                    0,
                    0,
                    50,
                    pThis_98);
            (*(void (/*thiscall*/ **)(uint8_t *, int, int))(v9 + 580))(this, 30350, pThis_982);  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
            return sub_4E1780(this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
          }
        }
      }
      else if ( pThis_1E >= 2
             && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
             && *(this + 8602) != 0 )  // this+8602 子类 AI 状态字节 3
      {
        *(this + 8602) = 0;  // this+8602 子类 AI 状态字节 3
        sub_5CBA00(this);  // 调 挂接对象坐标同步
        return sub_4E1780(this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
      }
    }
    else if ( pThis_1E >= 4 && *(this + 8609) == 0 )  // this+8609 攻击/触发一次性门伴位
    {
      (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        this,
        "TRAP_GRASS_UP",  // 资源/动画 TAG TRAP_GRASS_UP
        -1,
        0,
        0);
      *(this + 8609) = 1;  // this+8609 攻击/触发一次性门伴位
    }
  }
  return sub_4E1780(this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// ============================================================
// 【分区 6】陷阱基类与字段群（0x5CBC00-0x5CC490）
// 证据：sub_4049C0 插值、RTTI cast 目标解算群（陷阱触发对象判定）

// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x5CBC00 sub_5CBC00 —— 速率收敛插值
// ·取 vt+384(0)/vt+384(1) 两轴经 sub_4049C0 区间插值，收敛到 vt+1172 速率值 ×0.01
// ·再经 vt+688 写入速率浮点槽 this+858（sub_4EB4B0/2C0 为浮点栈辅助）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CBC00(void *this)  // 函数: 速率收敛插值
{
  int pThis_494; // edi
  float pThis_1802; // [esp+4h] [ebp-24h]
  float pThis_180; // [esp+8h] [ebp-20h]
  float v6; // [esp+20h] [ebp-8h]

  pThis_494 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1172))(this);  // 调用虚函数（虚表槽 +1172）
  pThis_180 = (float)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 384))(this);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  pThis_1802 = (float)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 384))(this, 1);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v6 = (double)(int)(uint64_t)sub_4049C0(pThis_1802, pThis_180, pThis_494, 30) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 688))(this, 1065353216);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
  sub_4EB4B0(COERCE_FLOAT(2));  // 调 与 ·0x4EB2C0 同构（差异：·sub_4923F0 按倒数缩放）
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 688))(this);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
  return sub_4EB2C0(v6);  // 调 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
}



// 子类扩展字段复位（this+8600..8609）
// ------------------------------------------------------------
// 0x5CBCA0 sub_5CBCA0 —— 子类复位与子阶段门
// ·2151 门槛下按 vt+1172 区间清 fld1905 派生节点标志（子节点 32/64）
// ·ArgList==8 时按 fArg3 指向的段号置 8600/8601/8602/8609 子阶段门
// ·尾部 sub_4E33D0 状态收尾转发
// ------------------------------------------------------------
int /*thiscall*/ sub_5CBCA0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 子类复位与子阶段门
{
  int v6; // eax
  int v7; // eax
  int v8; // eax

  if ( *(this + 2151) == 0 )  // this+8604 = bAI8604
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1172))(this);  // 调用虚函数（虚表槽 +1172）
    if ( v6 > 0 )
    {
      if ( v6 <= 5 )
      {
        *(uint8_t *)(*(this + 1905) + 32) = 0;  // this+7620 = 速度/属性参数对象
      }
      else if ( v6 > 10 )
      {
        goto LABEL_8;
      }
      *(uint8_t *)(*(this + 1905) + 64) = 0;  // this+7620 = 速度/属性参数对象
    }
LABEL_8:
    *(this + 2151) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1172))(this);  // this+8604 = bAI8604
  }
  if ( ArgList == 8 )
  {
    v7 = **(uint32_t **)(LODWORD(fArg3) + 4);  // 调 取 64 位值低 32 位
    if ( v7 != 0 )
    {
      v8 = v7 - 1;
      if ( v8 != 0 )
      {
        if ( v8 == 1 )
        {
          *((uint8_t *)this + 8600) = 1;  // this+8600 = uAI8600
          *((uint8_t *)this + 8601) = 1;  // this+8601 = 子类 AI 状态字节 2
        }
      }
      else
      {
        *((uint8_t *)this + 8602) = 1;  // this+8602 子类 AI 状态字节 3
      }
    }
    else
    {
      *((uint8_t *)this + 8609) = 0;  // this+8609 攻击/触发一次性门伴位
    }
  }
  return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CBD50 sub_5CBD50 —— 参数装载与倒计时
// ·vt+1308 后从 vt+384 取参数 21..24 存入 2163/2164/2172/2173
// ·以 2172 为时长对 2165 时钟槽设倒计时（sub_698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_5CBD50(int *this)  // 函数: 参数装载与倒计时
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int fld_e2172; // [esp-8h] [ebp-Ch]

  (*(void (/*thiscall*/ **)(int *))(*this + 1308))(this);  // 调用虚函数（虚表槽 +1308）
  *(this + 2163) = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 21);  // this+8652 = 相位槽
  v2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 22);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v3 = *this;
  *(this + 2164) = v2;  // this+8656 = 事件 16/17 配对槽
  *(this + 2172) = (*(int (/*thiscall*/ **)(int *, int))(v3 + 384))(this, 23);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 24);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  fld_e2172 = *(this + 2172);  // this+8688〔bVec8688(推断)〕
  *(this + 2173) = v4;  // this+8692〔uVec8692(推断)〕
  return sub_698F90((int)(this + 2165), fld_e2172, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CBDC0 sub_5CBDC0 —— 命中前置位移
// ·vt+308 就绪且 10% 随机时用 vt+576 反查挂接主体
// ·按自身与目标坐标差取 ±50 偏移点，vt+140 校验后 vt+108 写入位移
// ·尾部 sub_4DA3B0 命中包分发前置
// ------------------------------------------------------------
int /*userpurge*/ sub_5CBDC0@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4, int nArg5)  // 实现：命中前置位移
{
  char v6; // al
  int pObj2; // ebx
  int pObj; // edi
  int v9; // edi
  int v10; // eax
  int v11; // edx
  int v12; // edi
  int v13; // eax
  int v15; // [esp+8h] [ebp-4h] BYREF

  v6 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  pObj2 = nArg3;
  if ( v6 != 0 && rand() % 100 < 10 )  // 调 以 16 位种子状态递推并返回 15 位结果
  {
    if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 576))(pObj2, nArg2) != 0 )  // 调用虚函数（虚表槽 +576）
      pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 576))(pObj2);  // 调用虚函数（虚表槽 +576）
    else
      pObj = pObj2;
    nArg3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 调用虚函数（虚表槽 +124）
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) >= v9 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      v10 = nArg3 - 50;
    else
      v10 = nArg3 + 50;
    v11 = *pDwArg1;
    nArg3 = v10;
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int *, int *, int, int, int, int))(v11 + 140))(  // 调用虚函数（虚表槽 +140）【推断: ★ 螺旋式寻找空位（同心方环，从 (a4,a5) 起向外扫）】
           pDwArg1,
           &nArg3,
           &v15,
           v10,
           v15,
           100,
           1) != 0 )
    {
      v12 = *pDwArg1;
      v13 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调用虚函数（虚表槽 +128）
      (*(void (/*thiscall*/ **)(int *, int, int, int))(v12 + 108))(pDwArg1, nArg3, v15, v13);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
    }
  }
  return sub_4DA3B0(pObj2, nArg4, nArg5);  // 调 ★ 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
}



// RTTI cast 目标解算（72L）
// ------------------------------------------------------------
// 0x5CBEA0 sub_5CBEA0 —— 四向挂点档位选择
// ·vt+40(obj,17) 类型校验后 RTTI 下转 IRDCollisionObject 至 IRDActiveObject
// ·逐槽 sub_4DA0F0(0..3) 统计四向挂点数量，选最少者经 vt+348 写档位 +20
// ·尾部 sub_4DB480 反击判定
// ------------------------------------------------------------
int /*thiscall*/ sub_5CBEA0(void *this, int nArg2, int nArg3, int nArg4)  // 函数: 四向挂点档位选择
{
  int pObj2; // eax
  int pObj; // esi
  int v6; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // ecx
  int v11; // [esp+4h] [ebp-8h]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
  {
    pObj2 = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    pObj = pObj2;
    if ( pObj2 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 672))(pObj2, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      v6 = sub_4DA0F0(0);  // 调 受方属性抗性值
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      v7 = sub_4DA0F0(1);  // 调 受方属性抗性值
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      v11 = sub_4DA0F0(2);  // 调 受方属性抗性值
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      v8 = sub_4DA0F0(3);  // 调 受方属性抗性值
      if ( v6 < 5 || v7 < 5 )  // 若 v6 < 5 与/或 v7 < 5
      {
        v9 = v11;
      }
      else
      {
        v9 = v11;
        if ( v11 >= 5 && v8 >= 5 )  // 若 v11 >= 5 与/或 v8 >= 5
        {
          *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 20) = 4;  // 调用虚函数（虚表槽 +348）
          return sub_4DB480(nArg2, nArg3, nArg4);  // 调 ★ 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
        }
      }
      if ( v7 < v6 )
        goto LABEL_15;
      if ( v6 <= v9 && v6 <= v8 )  // 若 v6 <= v9 与/或 v6 <= v8
      {
        *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 20) = 0;  // 调用虚函数（虚表槽 +348）
        return sub_4DB480(nArg2, nArg3, nArg4);  // 调 ★ 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
      }
      if ( v7 <= v6 )
      {
LABEL_15:
        if ( v7 <= v9 && v7 <= v8 )  // 若 v7 <= v9 与/或 v7 <= v8
        {
          *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 20) = 1;  // 调用虚函数（虚表槽 +348）
          return sub_4DB480(nArg2, nArg3, nArg4);  // 调 ★ 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
        }
      }
      if ( v9 > v6 || v9 > v7 || v9 > v8 )  // 若 v9 > v6 与/或 v9 > v7 与/或 v9 > v8
      {
        if ( v8 <= v6 && v8 <= v7 && v8 <= v9 )  // 若 v8 <= v6 与/或 v8 <= v7 与/或 v8 <= v9
          *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 20) = 3;  // 调用虚函数（虚表槽 +348）
      }
      else
      {
        *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 20) = 2;  // 调用虚函数（虚表槽 +348）
      }
    }
  }
  return sub_4DB480(nArg2, nArg3, nArg4);  // 调 ★ 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 主状态门（this+200）
// ------------------------------------------------------------
// 0x5CC010 sub_5CC010 —— 尾迹光带绘制
// ·遍历 2154 环形链表（节点 5 字：色/端点对），按 2163 递减算 alpha（fld<<24）
// ·sub_45E490/45E4D0 取色与端点，sub_491DE0 绘制渐隐光带
// ·尾部 vt+144 转发垫片 sub_4D8F90
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC010(int *this, int nArg2, int nArg3, int nArg4, float fArg5)  // 函数: 尾迹光带绘制
{
  uint32_t *fld_e2154; // eax
  uint32_t *v7; // edi
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int fld_e2163; // [esp+8h] [ebp-8h]
  uint8_t fld_e21632; // [esp+Fh] [ebp-1h]

  if ( (uint8_t)nArg2 == 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    fld_e2154 = (uint32_t *)*(this + 2154);  // this+8616 = uAI8616
    v7 = (uint32_t *)*fld_e2154;
    fld_e2163 = *(this + 2163);  // this+8652 = 相位槽
    if ( (uint32_t *)*fld_e2154 != fld_e2154 )
    {
      do
      {
        fld_e21632 = (uint64_t)((double)fld_e2163-- * 150.0 / (double)*(this + 2163));  // this+8652 = 相位槽
        if ( fld_e21632 == 0 )
          break;
        v8 = (*(int (/*thiscall*/ **)(int *))(*this + 36))(this);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
        v9 = sub_45E490(v7[2], *(uint32_t *)(v8 + 8));  // 调 屏幕 y → 演出层坐标（减基线）
        v10 = (*(int (/*thiscall*/ **)(int *))(*this + 36))(this);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
        v11 = sub_45E4D0(v7[3], v7[4], *(uint32_t *)(v10 + 8), 1.0);  // 调 带比例的回换算（nArg2 - nArg3*f + 120）
        sub_491DE0(dword_79C0B0, v9, v11, fArg5, 0, 0, 0, (fld_e21632 << 24) | 0xFFFFFF);  // 调 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
        v7 = (uint32_t *)*v7;
      }
      while ( v7 != (uint32_t *)*(this + 2154) );  // this+8616 = uAI8616
    }
  }
  return sub_4D8F90(nArg2, nArg3, nArg4, LODWORD(fArg5));  // 调 vmt144 转发垫片（IRDActiveObject__vmt144 族）
}



// RTTI cast 目标解算（65L）
// ------------------------------------------------------------
// 0x5CC110 sub_5CC110 —— 最近精灵选择
// ·遍历 this+29 对象向量，vt+40(...,17) 筛玩家系
// ·RTTI 下转 CNSpirit 且 vt+376 与自身同值，取 vt+8 距离最近者
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC110(uint32_t *this)  // 函数: 最近精灵选择
{
  unsigned int v1; // esi
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // esi
  int v11; // ebx
  int v12; // eax
  int v13; // esi
  int v15; // [esp+Ch] [ebp-Ch]
  int v16; // [esp+10h] [ebp-8h]
  unsigned int v17; // [esp+14h] [ebp-4h]

  v1 = 0;
  v16 = 99999;
  v15 = 0;
  while ( 1 )  // 无限循环
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v4 = *(uint32_t *)(fld_e29 + 8);
    v17 = v1;
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)v1 >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && v1 < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj2 = *(uint32_t *)(v6 + 4 * v1);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && v1 < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj = *(uint32_t *)(v9 + 4 * v1);
      else
        pObj = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调用虚函数（虚表槽 +376）
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )  // 调用虚函数（虚表槽 +376）
      {
        v12 = __RTDynamicCast(pObj, 0, &IRDActiveObject `RTTI Type Descriptor', &CNSpirit `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
        v13 = v12;
        if ( v12 != 0 && v16 > (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 8))(this, v12, 1) )  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
        {
          v16 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 8))(this, v13, 1);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
          v15 = v13;
        }
      }
      v1 = v17;
    }
    ++v1;
  }
  return v15;
}



// RTTI cast 目标解算（67L）
// ------------------------------------------------------------
// 0x5CC200 sub_5CC200 —— 精灵命中计数
// ·同 5CC110 的 CNSpirit 枚举模式，改为计数：vt+376 同值且 vt+304 相等
// ·返回命中个数【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC200(uint32_t *this, int nArg2)  // 函数: 精灵命中计数
{
  uint32_t *pThis; // ebx
  unsigned int v3; // edi
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int pObj3; // ecx
  int v9; // ecx
  int v10; // edx
  int pObj2; // esi
  int pObj; // eax
  int v13; // esi
  int v15; // [esp+Ch] [ebp-Ch]
  int v16; // [esp+10h] [ebp-8h]

  pThis = this;
  v3 = 0;
  v16 = 0;
  while ( 1 )  // 无限循环
  {
    v4 = pThis[29];
    v5 = *(uint32_t *)(v4 + 8);
    v6 = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)v3 >= v6 )
      return v16;
    v7 = *(uint32_t *)(v4 + 8);
    if ( v7 != 0 && v3 < (*(uint32_t *)(v4 + 12) - v7) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj3 = *(uint32_t *)(v7 + 4 * v3);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 17) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      v9 = pThis[29];
      v10 = *(uint32_t *)(v9 + 8);
      if ( v10 != 0 && v3 < (*(uint32_t *)(v9 + 12) - v10) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj2 = *(uint32_t *)(v10 + 4 * v3);
      else
        pObj2 = 0;
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);  // 调用虚函数（虚表槽 +376）
      if ( v15 != (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis)  // 调用虚函数（虚表槽 +376）
        || (pObj = __RTDynamicCast(pObj2, 0, &IRDActiveObject `RTTI Type Descriptor', &CNSpirit `RTTI Type Descriptor', 0)) == 0 )  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      {
        pThis = this;
        goto LABEL_20;
      }
      pThis = this;
      v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 304))(pObj);  // 调用虚函数（虚表槽 +304）
      if ( v13 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 304))(this) )  // 调用虚函数（虚表槽 +304）
        goto LABEL_20;
      ++v16;
      ++v3;
    }
    else
    {
LABEL_20:
      ++v3;
    }
  }
}



// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x5CC300 sub_5CC300 —— 十八槽浮点插值
// ·同 5CBC00 插值模式但取 vt+384(17) 轴，并对 this+1617 起 18 个槽
// ·逐槽 sub_4EB6E0/6A0 写浮点（血条/进度条族）【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC300(uint32_t *this)  // 函数: 十八槽浮点插值
{
  int v2; // edi
  int result; // eax
  uint32_t *pThis_651; // esi
  int i; // ebx
  float v6; // [esp+4h] [ebp-28h]
  float v7; // [esp+8h] [ebp-24h]
  float v8; // [esp+24h] [ebp-8h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1172))(this);  // 调用虚函数（虚表槽 +1172）
  v7 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v6 = (float)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 17);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v8 = (double)(int)(uint64_t)sub_4049C0(v6, v7, v2, 30) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 688))(this, 1065353216);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
  sub_4EB4B0(COERCE_FLOAT(18));  // 调 与 ·0x4EB2C0 同构（差异：·sub_4923F0 按倒数缩放）
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
  result = sub_4EB2C0(v8);  // 调 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )  // 循环：i 从 18 递减到 0
  {
    if ( *pThis_651 != 0 )
    {
      sub_4EB6E0(1.0);  // 调 与 ·0x4EB6A0 同构（差异：调 ·0x4EB4B0）
      result = sub_4EB6A0(v8);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
    }
    ++pThis_651;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CC3C0 sub_5CC3C0 —— 子节点可见门
// ·依据 5CC200 计数与 2151/2152 阈值写 fld1905 派生节点 32/64 两个可见开关
// ·另受 vt+736/740 血量比 15% 门控
// ------------------------------------------------------------
void /*thiscall*/ sub_5CC3C0(uint32_t *this)  // 函数: 子节点可见门
{
  bool *fld_e1905; // edi
  float v3; // [esp+4h] [ebp-8h]

  *(uint8_t *)(*(this + 1905) + 32) = *(this + 2151) < (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 19)  // this+7620 = 速度/属性参数对象
                                 && sub_5CC200(this, 1) != 0;  // 调 精灵命中计数
  fld_e1905 = (bool *)(*(this + 1905) + 64);  // this+7620 = 速度/属性参数对象
  *fld_e1905 = sub_5CC200(this, 0) != 0;  // 调 精灵命中计数
  if ( *(this + 2152) >= (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 20) )  // this+8608 = uAI8608
    *(uint8_t *)(*(this + 1905) + 64) = 0;  // this+7620 = 速度/属性参数对象
  v3 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
  if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * 0.15000001 < v3 )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    *(uint8_t *)(*(this + 1905) + 64) = 0;  // this+7620 = 速度/属性参数对象
}



// ============================================================
// 【分区 7】埃切维里亚/刺王（Echeverria / SpikeKing）（0x5CC490-0x5CD170）
// 证据：R_ECHEVERRA_DMG + ECHEVERRA_DIE、ECHEVERRA_ARM_ATK 触手攻击、
//       ECHEVERRA_INTENSE_AURA + Animation_SpikeKing/Aura.ani（368L 巨型 aura 态）、
//       Monster/SpikeKing/SpikeKing_{Acc,Clothes,Glow,Hair}.equ

// 刺王语音：R_ECHEVERRA_DMG + ECHEVERRA_DIE（this+8600..8696 相位）
// ------------------------------------------------------------
// 0x5CC490 sub_5CC490 —— 刺王语音注册与相位复位
// ·填 6792..6808 五段间隔，清 8600/8604/8608 与 8673/8674/8696 相位字节
// ·sub_4015C0 注册语音条目 R_ECHEVERRA_DMG、ECHEVERRA_DIE
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC490(int this)  // 函数: 刺王语音注册与相位复位
{
  int result; // eax

  *(uint32_t *)(this + 6792) = 2;  // this+6792 技能/登场参数槽 1
  *(uint32_t *)(this + 6796) = 3;  // this+6796 技能/登场参数槽 2
  *(uint32_t *)(this + 6800) = 5;  // this+6800 技能/登场参数槽 3
  *(uint32_t *)(this + 6804) = 4;  // this+6804 技能/登场参数槽 4
  *(uint32_t *)(this + 6808) = 5;  // this+6808 技能/登场参数槽 5
  *(uint8_t *)(this + 8600) = 0;  // this+8600 狂气光环单次门
  *(uint32_t *)(this + 8604) = 0;  // this+8604 子类 AI 相位槽
  *(uint32_t *)(this + 8608) = 0;  // this+8608 子类 AI 相位槽
  sub_4015C0("R_ECHEVERRA_DMG", 0xFu);  // 【std::string构造赋值】
  result = sub_4015C0("ECHEVERRA_DIE", 0xDu);  // 【std::string构造赋值】
  *(uint8_t *)(this + 8673) = 0;  // this+8673 相位字节
  *(uint8_t *)(this + 8674) = 0;  // this+8674 相位字节
  *(uint8_t *)(this + 8696) = 0;  // this+8696 相位字节
  return result;
}



// 语音注册（sub_4015C0; 32L）
// ------------------------------------------------------------
// 0x5CC510 sub_5CC510 —— 容器长度检查
// ·std::vector 增长检查：容量余量不足 357913941 时抛 list 超长异常
// ·否则累加长度字段；属容器模板实例【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC510(uint32_t *this, unsigned int uArg2)  // 函数: 容器长度检查
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  if ( 357913941 - fld_e2 < uArg2 )
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
    v8 = 0;
    sub_401740(v5);  // 调 std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消…
    pExceptionObject = &std::length_error::`vftable';  // vftable 复位
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+8 = 技能槽记录首字
  return result;
}



// AI 相位辅助（112L）
// ------------------------------------------------------------
// 0x5CC5A0 sub_5CC5A0 —— 向量插入重分配
// ·std::vector 三指针（fld4/8/12）插入：余量足则搬移腾位，不足翻倍重分配
// ·operator new/free 与 memcpy 搬移（sub_523700 搬尾、sub_55E7F0 重叠搬移）【推断】
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5CC5A0(int this, int Src, unsigned int uArg3, int *pDwArg4)  // 函数: 向量插入重分配
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

  fld_4 = *(uint32_t *)(this + 4);  // this+4 宿主对象
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;  // this+12 物品类型号
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_52E630(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
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
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // 调 商城状态（10 行）
        sub_5DAF70((void *)Src, v24, v29);  // 调 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推得，尾段整体后移一格
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // 调 区间填充（逐 uint32 写同值）
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // 调 商城状态（10 行）
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // 调 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];  // this+8 物品 id
        *(uint32_t *)(this + 8) = fld_84;  // this+8 物品 id
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // 调 区间填充（逐 uint32 写同值）
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( fld_4 != 0 )
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
        else
          fld_86 = 0;
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);  // this+4 宿主对象
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+4 宿主对象
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // 调 填充补足尾段
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));  // this+8 物品 id
      fld_43 = *(uint32_t *)(this + 4);  // this+4 宿主对象
      if ( fld_43 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8 物品 id
      else
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));  // 调 堆释放
      *(uint32_t *)(this + 12) = &pMem[v28];  // this+12 物品类型号
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // this+8 物品 id
      *(uint32_t *)(this + 4) = pMem;  // this+4 宿主对象
      return (unsigned int)pMem;
    }
  }
  return result;
}



// 触手攻击：ECHEVERRA_ARM_ATK 播报（76L；this+8600/8637/8638/8696 相位）
// ------------------------------------------------------------
// 0x5CC780 sub_5CC780 —— 触手攻击与记录续期
// ·8600 惰性门调 5CC300；主状态镜像 1639==8 且 7028 段空且敌距≥1 时
// ·vt+212 播 ECHEVERRA_ARM_ATK（8696 一次门）
// ·2162 计时到点：摘尾、sub_5D1490 五元组记录挂回 2154 链表、复位 8637/8638 续期
// ------------------------------------------------------------
char /*thiscall*/ sub_5CC780(int *this)  // 函数: 触手攻击与记录续期
{
  int fld_e1639; // eax
  int v3; // edx
  int fld_e2162; // edi
  int fld_e2154; // ecx
  uint32_t **v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int fld_e21542; // ebx
  int v11; // eax
  uint32_t v13[3]; // [esp+8h] [ebp-10h] BYREF
  int v14; // [esp+14h] [ebp-4h]

  if ( *(this + 2090) != 0 && *((uint8_t *)this + 8600) == 0 )  // this+8600 = uAI8600
  {
    *((uint8_t *)this + 8600) = 1;  // this+8600 = uAI8600
    sub_5CC300(this);  // 调 十八槽浮点插值
  }
  fld_e1639 = *(this + 1639);  // this+6556 = 主状态镜像
  if ( fld_e1639 != 0 )
  {
    if ( fld_e1639 == 8
      && sub_41A5E0((unsigned int)(this + 1757)) == 0  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      && *(int *)(*(this + 30) + 148) >= 1  // this+120 = 动画对象指针
      && *((uint8_t *)this + 8696) == 0 )  // this+8696 相位字节
    {
      v3 = *this;
      *((uint8_t *)this + 8696) = 1;  // this+8696 相位字节
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v3 + 212))(this, "ECHEVERRA_ARM_ATK", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
    }
  }
  else
  {
    sub_5CC3C0(this);  // 调 子节点可见门
  }
  fld_e2162 = *(this + 2162);  // this+8648 = 相位/缓存槽
  if ( sub_699000((int)(this + 2156)) >= fld_e2162 )  // 【clock_now(clk)】
  {
    if ( *(this + 2155) == *(this + 2163) )  // this+8620 = uAI8620
    {
      fld_e2154 = *(this + 2154);  // this+8616 = uAI8616
      v6 = *(uint32_t ***)(fld_e2154 + 4);
      if ( v6 != (uint32_t **)fld_e2154 )
      {
        *v6[1] = *v6;
        (*v6)[1] = v6[1];
        j__free(v6);  // 调 堆释放
        --*(this + 2155);  // this+8620 = uAI8620
      }
    }
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v8 = *this;
    v13[0] = v7;
    v13[1] = (*(int (/*thiscall*/ **)(int *))(v8 + 124))(this);  // 调用虚函数（虚表槽 +124）
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
    fld_e21542 = *(uint32_t *)*(this + 2154);  // this+8616 = uAI8616
    v13[2] = v9;
    v14 = sub_5D1490(fld_e21542, *(uint32_t *)(fld_e21542 + 4), v13);  // 调 五元组记录构造（20 字节堆分配）
    sub_5CC510(this + 2153, 1u);  // 调 容器长度检查
    v11 = v14;
    *(uint32_t *)(fld_e21542 + 4) = v14;
    **(uint32_t **)(v11 + 4) = v11;
    *((uint8_t *)this + 8637) = 0;  // this+8637 普攻播报单次门
    *((uint8_t *)this + 8638) = 0;  // this+8638 【推断】子类扩展标志字节
    sub_698F90((int)(this + 2156), *(this + 2164), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return sub_4E1780(this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CC8E0 sub_5CC8E0 —— 光环状态机析构
// ·CNAuraChangeStatusMaster 析构：写回基类 vftable，经 sub_64A7C0 受击前置
// ·再转 sub_591190 基类析构【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC8E0(char *this)  // 函数: 光环状态机析构
{
  *(uint32_t *)this = &CNAuraChangeStatusMaster::`vftable';  // vftable 复位
  sub_64A7C0();  // 调 受击前置（42AF90/657740）
  return sub_591190(this);  // 调 CNRDAuraMaster 析构函数
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CC930 sub_5CC930 —— 光环状态机标量删除器
// ·与 ·sub_5CC8E0 同构（差异：标量删除器，按 pszArg2 位 0 释放堆块）
// ------------------------------------------------------------
char */*thiscall*/ sub_5CC930(char *Block, char pszArg2)  // 函数: 光环状态机标量删除器
{
  sub_5CC8E0(Block);  // 调 光环状态机析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CC960 sub_5CC960 —— 刺王光环机构造
// ·CNAuraChangeStatusMasterSpikeKing 构造：先 sub_64B6C0 建立基类
// ·再覆盖派系 vftable
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5CC960(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, char pszArg6, int nArg7)  // 函数: 刺王光环机构造
{
  sub_64B6C0(nArg2, nArg3, nArg4, nArg5, pszArg6, nArg7);  // 调 火焰动画查询（5910D0）
  *this = &CNAuraChangeStatusMasterSpikeKing::`vftable';  // vftable 复位
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CC9A0 sub_5CC9A0 —— 刺王光环机标量删除器
// ·与 ·sub_5CC8E0 同构（差异：标量删除器包 ·sub_5CC9D0）
// ------------------------------------------------------------
void */*thiscall*/ sub_5CC9A0(void *Block, char pszArg2)  // 函数: 刺王光环机标量删除器
{
  sub_5CC9D0();  // 调 刺王光环机析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CC9D0 sub_5CC9D0 —— 刺王光环机析构
// ·写回派系 vftable 后转 sub_5CC8E0【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC9D0(char *this)  // 函数: 刺王光环机析构
{
  *(uint32_t *)this = &CNAuraChangeStatusMasterSpikeKing::`vftable';  // vftable 复位
  sub_64A7C0();  // 调 受击前置（42AF90/657740）
  return sub_5CC8E0(this);  // 调 光环状态机析构
}



// 强力光环态（368L 全文件最大）：ECHEVERRA_INTENSE_AURA 播报 +
//   Animation_SpikeKing/Aura.ani（sub_431230+RTTI cast —— 刺王 aura 形态切换）
// ------------------------------------------------------------
// 0x5CCA20 sub_5CCA20 —— 强力光环态
// ·vt+840==8 时按 7028 段判 2 或空，vt+208 帧写入换姿
// ·ArgList==8 段 1：sub_5CC110 找最近 CNSpirit，sub_431230 打包坐标
// ·vt+560 置 19 绑定态，遍历 vt+700 挂接物下转 CNChangeStatus 解除
// ·段 2：vt+212 播 ECHEVERRA_INTENSE_AURA，sub_5CC960 构造刺王光环机
// ·sub_64B480 挂 Animation_SpikeKing/Aura.ani，sub_4D6810 建 CNChangeHp
// ------------------------------------------------------------
void /*userpurge*/ sub_5CCA20(int *pDwArg1@<ecx>, int nArg2@<edi>, double fArgTmp@<st0>, int ArgList, int pArg5, int nArg6, int nArg7)  // 函数: 强力光环态
{
  int nSubPhase; // eax
  int pBindTarget; // ebx
  int pNearestSpirit; // edi
  int nDistSpirit; // eax
  uint32_t *pAuraPhase; // ecx
  int nPhaseSel; // eax
  int nPhaseMod; // eax
  int nAppendIdx; // edi
  int pVt; // edx
  int pAppendVec; // eax
  int pVecBegin; // ecx
  int nAppendCnt; // eax
  int pAppendObj; // eax
  int pObj; // eax
  int nParamA; // eax
  int pVt2; // edx
  void *pParamB; // eax
  int pVt3; // edx
  void *pParamC; // eax
  int pVt4; // edx
  int nParamD; // edi
  int *pStatusObj; // eax
  int pStatusVt; // edx
  uint8_t *pMem; // edi
  uint8_t *pDmgTextObj; // eax
  int pDmgTextVt; // edx
  void *pParamE; // eax
  int pVt5; // edx
  void *pParamF; // eax
  int pVt6; // edx
  int nParamG; // edi
  int *pAuraObj; // edi
  int pAuraVt; // edx
  void *pAniTmp; // eax
  int pVt7; // eax
  int nHpRatio; // edi
  int nParamH; // eax
  int pVt8; // edx
  unsigned int nAppendIdx2; // edi
  int pAppendVec2; // eax
  int pVecBegin2; // ecx
  int nAppendCnt2; // eax
  int pAppendVec3; // eax
  int pVecBegin3; // ecx
  int pAppendObj2; // ecx
  int pAppendObj3; // eax
  int pObj2; // eax
  int *pStatusObj2; // eax
  int pStatusVt2; // edx
  int fPackArg; // [esp+80h] [ebp-A8h]
  int nEntry0Id; // [esp+98h] [ebp-90h] BYREF
  char bEntry0Flag; // [esp+9Ch] [ebp-8Ch]
  float fEntry0Val; // [esp+A0h] [ebp-88h]
  int nEntry1Id; // [esp+A4h] [ebp-84h]
  char bEntry1Flag; // [esp+A8h] [ebp-80h]
  float fEntry1Val; // [esp+ACh] [ebp-7Ch]
  int nEntry2Id; // [esp+B0h] [ebp-78h]
  char bEntry2Flag; // [esp+B4h] [ebp-74h]
  float fEntry2Val; // [esp+B8h] [ebp-70h]
  int nEntry3Id; // [esp+BCh] [ebp-6Ch]
  char bEntry3Flag; // [esp+C0h] [ebp-68h]
  float fEntry3Val; // [esp+C4h] [ebp-64h]
  void *pBuf[4]; // [esp+C8h] [ebp-60h] BYREF
  int nEntryB0Id; // [esp+D8h] [ebp-50h] BYREF
  char bEntryB0Flag; // [esp+DCh] [ebp-4Ch]
  float fEntryB0Val; // [esp+E0h] [ebp-48h]
  int nEntryB1Id; // [esp+E4h] [ebp-44h]
  char bEntryB1Flag; // [esp+E8h] [ebp-40h]
  float fEntryB1Val; // [esp+ECh] [ebp-3Ch]
  int nEntryB2Id; // [esp+F0h] [ebp-38h]
  char bEntryB2Flag; // [esp+F4h] [ebp-34h]
  float fEntryB2Val; // [esp+F8h] [ebp-30h]
  int nEntryB3Id; // [esp+FCh] [ebp-2Ch]
  char bEntryB3Flag; // [esp+100h] [ebp-28h]
  float fEntryB3Val; // [esp+104h] [ebp-24h]
  int nPackVal; // [esp+108h] [ebp-20h] BYREF
  int nParamBVal; // [esp+10Ch] [ebp-1Ch]
  void *pMem3; // [esp+110h] [ebp-18h]
  void *pMem2; // [esp+114h] [ebp-14h]
  void *Block; // [esp+118h] [ebp-10h]
  int nCtorState; // [esp+124h] [ebp-4h]

  if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    nSubPhase = sub_41A5E0((unsigned int)(pDwArg1 + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    pBindTarget = 0;
    if ( nSubPhase != 0 )
    {
      if ( nSubPhase == 2 )
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 4));  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
    }
    else
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)pDwArg1[1554]);  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
    }
  }
  else
  {
    pBindTarget = 0;
  }
  if ( ArgList == 8 )
  {
    pNearestSpirit = sub_5CC110(pDwArg1);  // 调 最近精灵选择
    nDistSpirit = 0;
    if ( pNearestSpirit != 0 )
      nDistSpirit = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 8))(pDwArg1, pNearestSpirit, 1);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
    pAuraPhase = *(uint32_t **)(pArg5 + 4);  // pArg5+4〔宿主对象〕
    if ( *pAuraPhase == 2 && (pNearestSpirit == 0 || nDistSpirit > 100) )  // 若 pNearestSpirit == 0 与/或 nDistSpirit > 100
      *pAuraPhase = 1;
    nPhaseSel = **(uint32_t **)(pArg5 + 4);  // pArg5+4〔宿主对象〕
    if ( nPhaseSel != 0 )
    {
      nPhaseMod = nPhaseSel - 1;
      if ( nPhaseMod != 0 )
      {
        if ( nPhaseMod == 1 && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        {
          pBindTarget = sub_5CC110(pDwArg1);  // 调 最近精灵选择
          nAppendIdx = 0;
          if ( pBindTarget != 0 )
          {
            memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
            pVt = *pDwArg1;
            nCtorState = 2;
            nPackVal = (*(int (/*thiscall*/ **)(int *, int))(pVt + 48))(pDwArg1, nArg2);  // 调用虚函数（虚表槽 +48）
            sub_431230((int)pBuf, &nPackVal);  // 调 uint32 vector push_back
            nPackVal = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 52))(pDwArg1);  // 调用虚函数（虚表槽 +52）
            sub_431230((int)pBuf, &nPackVal);  // 调 uint32 vector push_back
            (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)pBindTarget + 560))(pBindTarget, 19, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
            while ( 1 )  // 无限循环
            {
              pAppendVec = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
              pVecBegin = *(uint32_t *)(pAppendVec + 4);
              nAppendCnt = pVecBegin != 0 ? (*(uint32_t *)(pAppendVec + 8) - pVecBegin) >> 2 : 0;  // 向量元素数 = (end−begin)/4
              if ( nAppendIdx >= nAppendCnt )
                break;
              (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
              if ( *(int **)(sub_517740(nAppendIdx) + 4) == pDwArg1 )
              {
                (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
                pAppendObj = sub_517740(nAppendIdx);
                pObj = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                        pAppendObj,
                        0,
                        &IRDAppendage `RTTI Type Descriptor',
                        &CNChangeStatus `RTTI Type Descriptor',
                        0);
                if ( pObj != 0 )
                {
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
                  break;
                }
              }
              ++nAppendIdx;
            }
            nParamA = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 9);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
            pVt2 = *pDwArg1;
            nPackVal = nParamA;
            nParamBVal = (*(int (/*thiscall*/ **)(int *, int))(pVt2 + 384))(pDwArg1, 10);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
            pParamB = (void *)(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 11);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
            pVt3 = *pDwArg1;
            pMem3 = pParamB;
            Block = (void *)(*(int (/*thiscall*/ **)(int *, int))(pVt3 + 384))(pDwArg1, 12);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
            pParamC = (void *)(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 13);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
            pVt4 = *pDwArg1;
            pMem2 = pParamC;
            nParamD = (*(int (/*thiscall*/ **)(int *, int))(pVt4 + 384))(pDwArg1, 14);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
            fEntry0Val = (float)nPackVal;
            nEntry0Id = 0;
            bEntry0Flag = 1;
            nEntry1Id = 3;
            bEntry1Flag = 1;
            fEntry1Val = (float)nParamBVal;
            nEntry2Id = 7;
            bEntry2Flag = 1;
            nEntry3Id = 8;
            bEntry3Flag = 1;
            fEntry2Val = (float)(int)pMem3;
            fArgTmp = (double)(int)Block;
            fEntry3Val = fArgTmp;
            Block = operator new(0x7Cu);  // operator new 分配 124 字节
            LOBYTE(nCtorState) = 3;  // 调 取 16 位值低 8 位
            if ( Block != nullptr )  // 若 Block 有效（非空）
              pStatusObj = (int *)sub_5101B0(&nEntry0Id, 4, nParamD, 1);  // 调 v87 = sub_5101B0 · CNChangeStatus 构造器
            else
              pStatusObj = nullptr;
            pStatusVt = *pStatusObj;
            LOBYTE(nCtorState) = 2;  // 调 取 16 位值低 8 位
            (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t, int))(pStatusVt + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
              pStatusObj,
              pDwArg1,
              pDwArg1,
              0,
              0,
              0,
              -1);
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(  // 调用虚函数（虚表槽 +204）
              pDwArg1,
              100,
              *(uint32_t *)(pDwArg1[1554] + 4),
              0,
              0,
              0,
              0);
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pBindTarget + 204))(  // 调用虚函数（虚表槽 +204）
              pBindTarget,
              100,
              *(uint32_t *)(pDwArg1[1554] + 8),
              0,
              0,
              0,
              0);
            pMem = operator new(0x80u);  // operator new 分配 128 字节
            pMem3 = pMem;
            LOBYTE(nCtorState) = 4;  // 调 取 16 位值低 8 位
            if ( pMem != nullptr )  // 若 pMem 有效（非空）
            {
              Block = (void *)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
              fArgTmp = (double)(int)Block * ((double)(int)pMem2 * 0.0099999998);  // ×0.01f（百分数转比例）
              *(float *)&fPackArg = fArgTmp;
              pDmgTextObj = sub_4D6810(pMem, fPackArg, 1000, 1, 1);  // 调 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
            }
            else
            {
              pDmgTextObj = nullptr;
            }
            pDmgTextVt = *(uint32_t *)pDmgTextObj;
            LOBYTE(nCtorState) = 2;  // 调 取 16 位值低 8 位
            (*(void (/*thiscall*/ **)(uint8_t *, int *, int *, uint32_t, uint32_t, uint32_t))(pDmgTextVt + 56))(pDmgTextObj, pDwArg1, pDwArg1, 0, 0, 0);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
            ++pDwArg1[2152];
            nCtorState = -1;
            sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          }
        }
      }
      else if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          pDwArg1,
          "ECHEVERRA_INTENSE_AURA",  // 资源/动画 TAG ECHEVERRA_INTENSE_AURA
          -1,
          0,
          0,
          nArg2);
        pParamE = (void *)(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 4);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        pVt5 = *pDwArg1;
        pMem2 = pParamE;
        Block = (void *)(*(int (/*thiscall*/ **)(int *, int))(pVt5 + 384))(pDwArg1, 5);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        pParamF = (void *)(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 6);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        pVt6 = *pDwArg1;
        pMem3 = pParamF;
        nParamBVal = (*(int (/*thiscall*/ **)(int *, int))(pVt6 + 384))(pDwArg1, 7);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        nParamG = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 8);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        fEntryB0Val = (float)(int)pMem2;
        nEntryB0Id = 0;
        bEntryB0Flag = 1;
        nEntryB1Id = 3;
        bEntryB1Flag = 1;
        fEntryB1Val = (float)(int)Block;
        nEntryB2Id = 7;
        bEntryB2Flag = 1;
        nEntryB3Id = 8;
        bEntryB3Flag = 1;
        fEntryB2Val = (float)(int)pMem3;
        fArgTmp = (double)nParamBVal;
        fEntryB3Val = fArgTmp;
        pMem2 = operator new(0x1D0u);  // operator new 分配 464 字节
        nCtorState = 1;
        if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
          pAuraObj = (int *)sub_5CC960(300, &nEntryB0Id, 4, nParamG, 0, 1);  // 调 刺王光环机构造
        else
          pAuraObj = nullptr;
        pAuraVt = *pAuraObj;
        nCtorState = -1;
        (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t))(pAuraVt + 56))(pAuraObj, pDwArg1, pDwArg1, 0, 0, 0);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
        if ( (unsigned int)pDwArg1[96] < 0x10 )
          pAniTmp = pDwArg1 + 91;
        else
          pAniTmp = (void *)pDwArg1[91];
        sub_64B480(pAniTmp, (int)"Animation_SpikeKing/Aura.ani");  // 调 状态变化文本（4015C0/4022F0）
        ++pDwArg1[2151];
      }
    }
    else
    {
      pVt7 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8696) = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(pVt7 + 308))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      {
        nHpRatio = sub_5CC200(0);  // 调 精灵命中计数
        pMem2 = (void *)(nHpRatio * (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 384))(pDwArg1, 0, nArg2));  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        nParamH = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 1);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        pVt8 = *pDwArg1;
        Block = (void *)(nHpRatio * nParamH);
        pMem3 = (void *)(nHpRatio * (*(int (/*thiscall*/ **)(int *, int))(pVt8 + 384))(pDwArg1, 2));  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        nParamBVal = nHpRatio * (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 3);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        for ( nAppendIdx2 = 0; ; ++nAppendIdx2 )
        {
          pAppendVec2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
          pVecBegin2 = *(uint32_t *)(pAppendVec2 + 4);
          nAppendCnt2 = pVecBegin2 != 0 ? (*(uint32_t *)(pAppendVec2 + 8) - pVecBegin2) >> 2 : 0;  // 向量元素数 = (end−begin)/4
          if ( (int)nAppendIdx2 >= nAppendCnt2 )
            break;
          pAppendVec3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
          pVecBegin3 = *(uint32_t *)(pAppendVec3 + 4);
          if ( pVecBegin3 != 0 && nAppendIdx2 < (*(uint32_t *)(pAppendVec3 + 8) - pVecBegin3) >> 2 )  // 向量元素数 = (end−begin)/4
            pAppendObj2 = *(uint32_t *)(pVecBegin3 + 4 * nAppendIdx2);
          else
            pAppendObj2 = 0;
          if ( *(int **)(pAppendObj2 + 4) == pDwArg1 )
          {
            (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
            pAppendObj3 = sub_517740(nAppendIdx2);
            pObj2 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                    pAppendObj3,
                    0,
                    &IRDAppendage `RTTI Type Descriptor',
                    &CNChangeStatus `RTTI Type Descriptor',
                    0);
            if ( pObj2 != 0 )
            {
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 76))(pObj2, 0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
              break;
            }
          }
        }
        nEntryB0Id = 0;
        bEntryB0Flag = 1;
        fEntryB0Val = (float)(int)pMem2;
        nEntryB1Id = 3;
        bEntryB1Flag = 1;
        nEntryB2Id = 7;
        bEntryB2Flag = 1;
        fEntryB1Val = (float)(int)Block;
        nEntryB3Id = 8;
        bEntryB3Flag = 1;
        fEntryB2Val = (float)(int)pMem3;
        fArgTmp = (double)nParamBVal;
        fEntryB3Val = fArgTmp;
        pMem2 = operator new(0x7Cu);  // operator new 分配 124 字节
        nCtorState = 0;
        if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
          pStatusObj2 = (int *)sub_5101B0(&nEntryB0Id, 4, 0, 1);  // 调 v87 = sub_5101B0 · CNChangeStatus 构造器
        else
          pStatusObj2 = nullptr;
        pStatusVt2 = *pStatusObj2;
        nCtorState = -1;
        (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t))(pStatusVt2 + 56))(pStatusObj2, pDwArg1, pDwArg1, 0, 0, 0);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(  // 调用虚函数（虚表槽 +204）
          pDwArg1,
          100,
          *(uint32_t *)pDwArg1[1554],
          0,
          0,
          0,
          0);
      }
    }
  }
  sub_4E33D0(pDwArg1, pObj3, fArgTmp, ArgList, pArg5, *(float *)&nArg6, *(float *)&nArg7);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}


// 刺王外观装载：Monster/SpikeKing/SpikeKing_{Acc,Clothes,Glow,Hair}.equ 四件
// ------------------------------------------------------------
// 0x5CD050 sub_5CD050 —— 刺王外观装载
// ·依次 new 0x544 并 sub_4BA9E0 挂装 SpikeKing_Acc/Clothes/Glow/Hair 四件 .equ
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD050(int *this)  // 函数: 刺王外观装载
{
  int i; // edi
  void *pMem; // eax
  char *v4; // eax
  int v5; // edx
  int result; // eax
  void *v7[5]; // [esp+8h] [ebp-20h]
  int v8; // [esp+24h] [ebp-4h]

  v7[0] = "Monster/SpikeKing/SpikeKing_Acc.equ";  // 资源路径 Monster/SpikeKing/SpikeKing_Acc.equ
  v7[1] = "Monster/SpikeKing/SpikeKing_Clothes.equ";  // 资源路径 Monster/SpikeKing/SpikeKing_Clothes.equ
  v7[2] = "Monster/SpikeKing/SpikeKing_Glow.equ";  // 资源路径 Monster/SpikeKing/SpikeKing_Glow.equ
  v7[3] = "Monster/SpikeKing/SpikeKing_Hair.equ";  // 资源路径 Monster/SpikeKing/SpikeKing_Hair.equ
  for ( i = 0; i < 4; ++i )  // 循环：i 从 0 递增到 4
  {
    pMem = operator new(0x544u);  // operator new 分配 1348 字节
    v7[4] = pMem;
    v8 = 0;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v4 = sub_4BA9E0((char *)pMem, v7[i], 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
    else
      v4 = nullptr;
    v5 = *this;
    v8 = -1;
    result = (*(int (/*thiscall*/ **)(int *, char *))(v5 + 784))(this, v4);  // 调用虚函数（虚表槽 +784）
    if ( result != 0 )  // 若结果非 0（成功）
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  }
  return result;
}



// AI 相位门（this+8628..8676）
// ------------------------------------------------------------
// 0x5CD100 sub_5CD100 —— 相位字段初始化
// ·清 8628/8676/8661/8662；vt+52 取当前值写 2161/2160
// ·8648 时钟置 10000，2170 派生对象槽清零
// ------------------------------------------------------------
char /*thiscall*/ sub_5CD100(uint8_t *this)  // 函数: 相位字段初始化
{
  int v2; // eax
  int v3; // eax
  char result; // al

  v2 = *(uint32_t *)this;
  *(this + 8628) = 0;  // this+8628 = 指挥计时戳
  *(this + 8676) = 0;  // this+8676 【推断】子类 AI 相位槽
  v3 = (*(int (**)(void))(v2 + 52))();  // 调用虚函数（虚表槽 +52）
  *((uint32_t *)this + 2161) = v3;  // this+8644 = 相位槽
  *((uint32_t *)this + 2160) = v3;  // this+8640 = uCastSlot8640
  *(this + 8661) = 0;
  *(this + 8662) = 0;
  result = sub_698F90((int)(this + 8648), 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint32_t *)this + 2170) = 0;  // this+8680〔uGate8680(推断)〕
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CD150 sub_5CD150 —— 派生对象槽释放
// ·fld2170 非空经对象 vt[0]+4 自毁，槽清零
// ·（5CD2A0/5CD3F0/5CF0A0 为同构变体）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD150(uint32_t *this)  // 函数: 派生对象槽释放
{
  int (/*thiscall*/ ***fld_e2170)(uint32_t, int); // ecx
  int result; // eax

  fld_e2170 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2170);  // this+8680〔uGate8680(推断)〕
  if ( fld_e2170 != nullptr )  // 若 fld_e2170 有效（非空）
    result = (**fld_e2170)(fld_e2170, 1);  // 调 fld_e2170 的虚函数（vt+0）
  *(this + 2170) = 0;  // this+8680〔uGate8680(推断)〕
  return result;
}



// ============================================================
// 【分区 8】锤王与巨人（HammerKing / Giant）（0x5CD170-0x5CDA80）
// 证据：HAMMER_KING_CRASH 崩击、TAU_GROUND_HIT 砸地（0x5CD6F0 复用 0x5A 音效）、
//       R_GIANT_ATK/ROAR/DMG/DIE + R_GOLEM_AMB 巨人语音组、B_FLATANY_01 登场曲、
//       Monster/Magma/Animation_Common/DownAttackEffect.ani

// 崩击：HAMMER_KING_CRASH 播报（27L）
// ------------------------------------------------------------
// 0x5CD170 sub_5CD170 —— 崩击播报
// ·vt+840 取态后转 sub_4E33D0；ArgList==4 播 HAMMER_KING_CRASH 崩击
// ·ArgList==8 且 7028 段空时清 2158
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD170(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 崩击播报
{
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 4 )
    return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
             this,
             "HAMMER_KING_CRASH",  // 资源/动画 TAG HAMMER_KING_CRASH
             -1,
             0,
             0);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 0 )
      *(this + 2158) = 0;  // this+8632〔bDevourFlag(推断)〕
  }
  return result;
}



// 锤王相位字段（this+8684..8716, 20L）
// ------------------------------------------------------------
// 0x5CD1E0 sub_5CD1E0 —— 相位字段复位
// ·清锤王相位字段 8684/8685 与 8688..8716 十个计数（硬直后重置）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD1E0(int this)  // 函数: 相位字段复位
{
  *(uint8_t *)(this + 8684) = 0;  // this+8684 充能弹幕一次门 A
  *(uint8_t *)(this + 8685) = 0;  // this+8685 充能弹幕一次门 B
  *(uint32_t *)(this + 8688) = 0;  // this+8688 动态数组首指针
  *(uint32_t *)(this + 8692) = 0;  // this+8692 动态数组游标/计数
  *(uint32_t *)(this + 8696) = 0;  // this+8696 动态数组容量端
  *(uint32_t *)(this + 8700) = 0;  // this+8700 相位字节
  *(uint32_t *)(this + 8704) = 0;  // this+8704 动态数组/表首指针
  *(uint32_t *)(this + 8708) = 0;  // this+8708 数组当前指针/计数
  *(uint32_t *)(this + 8712) = 0;  // this+8712 数组容量端
  *(uint32_t *)(this + 8716) = 0;  // this+8716 数组尾槽/标志
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CD220 sub_5CD220 —— 六阈值装载
// ·vt+1308 后从 vt+384 取参数 0..5 写入 2172..2177 阈值组
// ·供 5CDDD0 充能时按 vt+736/740 血量比使用
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD220(uint32_t *this)  // 函数: 六阈值装载
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 调用虚函数（虚表槽 +1308）
  *(this + 2172) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v3 = *this;
  *(this + 2173) = v2;  // this+8692〔uVec8692(推断)〕
  *(this + 2174) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 384))(this, 2);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v5 = *this;
  *(this + 2175) = v4;  // this+8700〔uPhase8700(推断)〕
  *(this + 2176) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 4);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  *(this + 2177) = result;  // this+8708〔pCandTbl8708(推断)〕
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CD2A0 sub_5CD2A0 —— 派生对象槽释放
// ·与 ·sub_5CD150 同构（差异：字段 this+2178）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD2A0(uint32_t *this)  // 函数: 派生对象槽释放
{
  int (/*thiscall*/ ***fld_e2178)(uint32_t, int); // ecx
  int result; // eax

  fld_e2178 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2178);  // this+8712〔nCandTblEnd8712(推断)〕
  if ( fld_e2178 != nullptr )  // 若 fld_e2178 有效（非空）
    result = (**fld_e2178)(fld_e2178, 1);  // 调 fld_e2178 的虚函数（vt+0）
  *(this + 2178) = 0;  // this+8712〔nCandTblEnd8712(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CD2C0 sub_5CD2C0 —— 攻击参数面复位
// ·清 7531..7558 攻击参数面与 7564..7596 计数；nArg3 为 0/2 时置 7535 门
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD2C0(int this, int nArg2, int nArg3)  // 函数: 攻击参数面复位
{
  int result; // eax

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558 攻击参数面字节槽
  *(uint8_t *)(this + 7557) = 0;  // this+7557 攻击面门字节
  *(uint8_t *)(this + 7556) = 0;  // this+7556 攻击面模式字节
  *(uint8_t *)(this + 7534) = 0;  // this+7534 配置块 +14 / 段选门
  *(uint8_t *)(this + 7533) = 0;  // this+7533 配置块 +13
  *(uint8_t *)(this + 7532) = 0;  // this+7532 配置块 +12
  *(uint8_t *)(this + 7531) = 0;  // this+7531 配置块 +11 / 攻击参数面首字节
  *(uint32_t *)(this + 7535) = 0;  // this+7535 配置块 +15 / 门
  *(uint32_t *)(this + 7539) = 0;  // this+7539 配置块 +19
  *(uint32_t *)(this + 7543) = 0;  // this+7543 攻击参数面槽
  *(uint32_t *)(this + 7547) = 0;  // this+7547 攻击参数面槽
  *(uint32_t *)(this + 7551) = 0;  // this+7551 攻击参数面槽
  *(uint8_t *)(this + 7555) = 0;  // this+7555 攻击参数面字节槽
  *(uint32_t *)(this + 7572) = 0;  // this+7572 模式 2 档
  *(uint32_t *)(this + 7568) = 0;  // this+7568 激活/模式槽
  *(uint32_t *)(this + 7564) = 0;  // this+7564 形态/模式槽
  *(uint32_t *)(this + 7588) = 0;  // this+7588 形态槽
  *(uint32_t *)(this + 7584) = 0;  // this+7584 形态槽
  *(uint32_t *)(this + 7580) = 0;  // this+7580 攻击面门字节
  *(uint32_t *)(this + 7576) = 0;  // this+7576 攻击参数面槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 段号横向偏置
  if ( nArg3 == 0 || nArg3 == 2 )  // 若 nArg3 == 0 与/或 nArg3 == 2
    *(uint8_t *)(this + 7535) = 1;  // this+7535 配置块 +15 / 门
  return result;
}



// 锤王相位字段（this+8684..8696）
// ------------------------------------------------------------
// 0x5CD360 sub_5CD360 —— 轻量相位复位
// ·清 8684/8688/8692/8696（保留 8685 与 8700 之后的字段）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD360(int this)  // 函数: 轻量相位复位
{
  *(uint32_t *)(this + 8684) = 0;  // this+8684 子类 AI 门字节
  *(uint8_t *)(this + 8688) = 0;  // this+8688 子类 AI 向量/防护槽
  *(uint32_t *)(this + 8692) = 0;  // this+8692 子类 AI 向量槽
  *(uint32_t *)(this + 8696) = 0;  // this+8696 子类 AI 向量槽
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CD380 sub_5CD380 —— 双阈值装载
// ·vt+1308 后取 vt+384(0/1) 写 2171/2173 双阈值
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD380(uint32_t *this)  // 函数: 双阈值装载
{
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 调用虚函数（虚表槽 +1308）
  *(this + 2171) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  *(this + 2173) = result;  // this+8692〔uVec8692(推断)〕
  return result;
}



// 锤王相位字段（this+8684..8692）
// ------------------------------------------------------------
// 0x5CD3C0 sub_5CD3C0 —— 三字节门复位
// ·与 ·sub_5CD360 同构（差异：拆出 8688/8689/8690 三个独立字节门）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD3C0(int this)  // 函数: 三字节门复位
{
  *(uint32_t *)(this + 8684) = 0;  // this+8684 子类 AI 槽
  *(uint8_t *)(this + 8688) = 0;  // this+8688 护盾探测门 1
  *(uint8_t *)(this + 8689) = 0;  // this+8689 三字节门 2
  *(uint8_t *)(this + 8690) = 0;  // this+8690 硬直分支门
  *(uint32_t *)(this + 8692) = 0;  // this+8692 语音/相位门
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CD3F0 sub_5CD3F0 —— 派生对象槽释放
// ·与 ·sub_5CD150 同构（差异：字段 this+2171）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD3F0(uint32_t *this)  // 函数: 派生对象槽释放
{
  int (/*thiscall*/ ***fld_e2171)(uint32_t, int); // ecx
  int result; // eax

  fld_e2171 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2171);  // this+8684〔bGate8684(推断)〕
  if ( fld_e2171 != nullptr )  // 若 fld_e2171 有效（非空）
    result = (**fld_e2171)(fld_e2171, 1);  // 调 fld_e2171 的虚函数（vt+0）
  *(this + 2171) = 0;  // this+8684〔bGate8684(推断)〕
  return result;
}



// 硬直字段（this+208）
// ------------------------------------------------------------
// 0x5CD410 sub_5CD410 —— 硬直与语音分档
// ·vt+840==8 时 vt+208 写 1554 面第 3 项帧；ArgList==8 且 7028 段==1 播语音档(24,3)
// ·ArgList==5 按 1943==3 困难级分档(24,5)/(24,4)；ArgList==0 按 50% 走 sub_4DB200
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD410(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 硬直与语音分档
{
  int v6; // edi
  int result; // eax
  int nRand; // eax

  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  result = sub_5CD170(this, ArgList, fArg3, nArg4, nArg5);  // 调 崩击播报
  if ( v6 == 8 )
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 8));  // this+6216 = 资源/帧游标表
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )
    {
      result = sub_4DB130(24, 3);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      *(this + 2179) = 0;  // this+8716〔uArr8716〕
    }
  }
  else if ( ArgList != 0 )
  {
    if ( ArgList == 5 )
    {
      if ( *(this + 1943) == 3 )  // this+7772 = nCounterState
        return sub_4DB130(24, 5);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      else
        return sub_4DB130(24, 4);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
    }
  }
  else
  {
    nRand = rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
    return sub_4DB200(24, nRand == 0);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
  }
  return result;
}



// 硬直/相位（this+208/8690/8692）
// ------------------------------------------------------------
// 0x5CD4E0 sub_5CD4E0 —— 硬直与语音分档
// ·与 ·sub_5CD410 同构（差异：帧源字段 6216、困难级字段 7772、语音档 (24,6)/(24,7)）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD4E0(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 硬直与语音分档
{
  int pThis_348; // edi
  int result; // eax
  int nRand; // eax

  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  result = sub_5CD170((uint32_t *)this, ArgList, fArg3, nArg4, nArg5);  // 调 崩击播报
  if ( pThis_348 == 8 )
    result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
               this,
               *(uint32_t *)(*(uint32_t *)(this + 6216) + 8));  // this+6216 资源/帧游标表
  if ( ArgList == 8 )
  {
    result = sub_41A5E0(this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )
    {
      *(uint32_t *)(this + 8692) = 0;  // this+8692 语音/相位门
      return sub_4DB130(24, 3);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
    }
  }
  else if ( ArgList != 0 )
  {
    if ( ArgList == 5 )
    {
      if ( *(uint32_t *)(this + 7772) == 3 )  // this+7772 反击态/难度槽
        return sub_4DB130(24, 7);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      else
        return sub_4DB130(24, 6);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
    }
  }
  else
  {
    nRand = rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
    result = sub_4DB200(24, nRand == 0);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
    if ( pThis_348 == 8 )
    {
      result = sub_41A5E0(this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result == 2 )
        *(uint8_t *)(this + 8690) = 1;  // this+8690 硬直分支门
    }
  }
  return result;
}



// 锤王相位字段（this+8688/8689）
// ------------------------------------------------------------
// 0x5CD5E0 sub_5CD5E0 —— 护盾与光环探测
// ·遍历 fld 1C54 挂接物表查 vt+92 护盾写 8688；再扫 16 槽查 sub_496F80==16
// ·光环（vt+772/776，命中即 vt[0]+12），合并写 fld1905 节点 64 可见开关
// ------------------------------------------------------------
char /*thiscall*/ sub_5CD5E0(int this)  // 函数: 护盾与光环探测
{
  int v2; // eax
  int v3; // ebx
  int v4; // ecx
  unsigned int v5; // esi
  int v6; // ecx
  int pObj2; // ecx
  int v8; // esi
  int pObj; // eax
  char result; // al
  int fld_1C54; // [esp+Ch] [ebp-8h]
  int v12; // [esp+10h] [ebp-4h]

  fld_1C54 = *(uint32_t *)(this + 7252);  // this+7252 当前目标/技能对象
  v2 = (*(int (/*fastcall*/ **)(int))(*(uint32_t *)fld_1C54 + 700))(fld_1C54);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
  v3 = v2;
  v4 = *(uint32_t *)(v2 + 4);
  v5 = 0;
  if ( v4 != 0 )
    v12 = (*(uint32_t *)(v2 + 8) - v4) >> 2;  // 向量元素数 = (end−begin)/4
  else
    v12 = 0;
  if ( v12 > 0 )
  {
    while ( 1 )  // 无限循环
    {
      v6 = *(uint32_t *)(v3 + 4);
      if ( v6 != 0 && v5 < (*(uint32_t *)(v3 + 8) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj2 = *(uint32_t *)(v6 + 4 * v5);
      else
        pObj2 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 92))(pObj2) != 0 )  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
        break;
      *(uint8_t *)(this + 8688) = 0;  // this+8688 【推断】子类 AI 向量/防护槽
      if ( (int)++v5 >= v12 )
        goto LABEL_13;
    }
    *(uint8_t *)(this + 8688) = 1;  // this+8688 【推断】子类 AI 向量/防护槽
  }
LABEL_13:
  v8 = 0;
  while ( sub_496F80(v8) != 16 || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_1C54 + 776))(fld_1C54, v8) == 0 )  // 调 状态号映射表（12 直通、15→14、16→15，其余→16）
  {
    ++v8;
    *(uint8_t *)(this + 8689) = 0;  // this+8689 三字节门 2
    if ( v8 >= 16 )
      goto LABEL_19;
  }
  pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_1C54 + 772))(fld_1C54, v8);  // 调用虚函数（虚表槽 +772）【推断: [RTTI: IRDActiveObject__vmt304 ·…】
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 12))(pObj);  // 调用虚函数（虚表槽 +12）
  *(uint8_t *)(this + 8689) = 1;  // this+8689 三字节门 2
LABEL_19:
  result = *(uint8_t *)(this + 8688);  // this+8688 【推断】子类 AI 向量/防护槽
  *(uint8_t *)(*(uint32_t *)(this + 7620) + 64) = result != 0 || (result = *(uint8_t *)(this + 8689)) != 0;  // this+7620 【推断】属性/速度面板对象
  return result;
}



// 砸地技能：TAU_GROUND_HIT 播报（90L；复用 0x5A 牛头系音效 TAG —— 锤王砸地）
// ------------------------------------------------------------
// 0x5CD6F0 sub_5CD6F0 —— 砸地窗口
// ·vt+200 状态与 1541 镜像相等时起 100 帧窗口
// ·子段 5 走 sub_424120 音效并播 TAU_GROUND_HIT（8636 门）
// ·到点取 dword_8F8270[vt+924(42)] 特效，vt+124 随机 40 内、vt+152 取 ±10 摆位
// ·sub_4600B0 挂接后置 8628 清 8637/8638 并续期
// ------------------------------------------------------------
void /*thiscall*/ sub_5CD6F0(char *this)  // 函数: 砸地窗口
{
  bool pThis_94; // zf
  char fld_e8636; // al
  int pThis_21982; // ebx
  uint32_t *pThis_39C; // edi
  int v6; // edx
  int v7; // eax
  int v8; // ebx
  int pThis_80; // edi
  int nRand; // eax
  int pThis_7C; // eax
  int pThis_98; // edi
  uint32_t *pThis_39C22; // edi
  void *pThis_1D; // ecx
  int v15; // ecx
  int pThis_78; // [esp-Ch] [ebp-38h]
  char v17[4]; // [esp+4h] [ebp-28h] BYREF
  void *Block; // [esp+8h] [ebp-24h]
  char *pThis_2198; // [esp+14h] [ebp-18h]
  uint32_t *pThis_39C2; // [esp+18h] [ebp-14h]
  bool v21; // [esp+1Fh] [ebp-Dh]
  int v22; // [esp+28h] [ebp-4h]

  if ( (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 200))(this) != 0  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    && (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 200))(this) == *((uint32_t *)this + 1541) )  // this+6164 = 帧游标对象槽
  {
    pThis_2198 = this + 8600;  // this+8600 子类 AI 状态字节 1
    sub_698F90((int)(this + 8600), 100, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    pThis_94 = *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 200))(this) + 148) == 5;  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    fld_e8636 = *(this + 8636);  // this+8636 【推断】传送/钻地相位槽
    if ( pThis_94 )
    {
      if ( fld_e8636 == 0 )
      {
        sub_424120(*(uint32_t **)(*((uint32_t *)this + 29) + 132), 1, 100);  // 调 屏幕震动启动
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          this,
          "TAU_GROUND_HIT",  // 资源/动画 TAG TAU_GROUND_HIT
          -1,
          0,
          0);
        *(this + 8636) = 1;  // this+8636 【推断】传送/钻地相位槽
      }
    }
    else if ( fld_e8636 == 1 )
    {
      *(this + 8636) = 0;  // this+8636 【推断】传送/钻地相位槽
    }
    if ( *(this + 8628) != 0 || (pThis_21982 = *((uint32_t *)this + 2156), sub_699000((int)(this + 8600)) < pThis_21982) )  // 【clock_now(clk)】
    {
      *(this + 8628) = 0;  // this+8628 【推断】指挥计时戳
    }
    else
    {
      pThis_39C = (uint32_t *)dword_8F8270[(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 924))(this, 42)];  // 调用虚函数（虚表槽 +924）
      v6 = *(uint32_t *)this;
      pThis_39C2 = pThis_39C;
      v7 = (*(int (/*thiscall*/ **)(char *))(v6 + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      v8 = *pThis_39C;
      v21 = v7 == 0;
      pThis_80 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);  // 调用虚函数（虚表槽 +128）
      nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
      pThis_7C = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, nRand % 40 + pThis_80);  // 调用虚函数（虚表槽 +124）
      pThis_98 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 152))(this, pThis_7C + 20) != 0 ? -10 : 10;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      pThis_78 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 120))(this) + pThis_98;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      pThis_39C22 = pThis_39C2;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v8 + 40))(pThis_39C2, pThis_78);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
      *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pThis_39C2 + 28))(pThis_39C2) + 84) = v21;  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pThis_39C22 + 12))(pThis_39C22, 0);  // 调用虚函数（虚表槽 +12）
      (*(void (/*thiscall*/ **)(uint32_t *, char *))(*pThis_39C22 + 92))(pThis_39C22, v17);  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
      pThis_1D = *((void **)this + 29);
      v22 = 0;
      sub_4600B0(pThis_1D, 2, 0, (int)v17);  // 调 演播层注册(槽号)
      v15 = (int)pThis_2198;
      *(this + 8628) = 1;  // this+8628 【推断】指挥计时戳
      *(uint8_t *)(v15 + 13) = 0;
      *(uint8_t *)(v15 + 14) = 0;
      sub_698F90(v15, 100, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
    }
  }
}



// 巨人语音装载：R_GIANT_ATK/ROAR/DMG/DIE + R_GOLEM_AMB（this+8613..8636 相位）
// ------------------------------------------------------------
// 0x5CD8D0 sub_5CD8D0 —— 巨人语音装载
// ·填 6792..6808 五段间隔与 7324==300；sub_4015C0 装载
// ·R_GIANT_ATK/ROAR/DMG/DIE 与 R_GOLEM_AMB（供 sub_4DE5E0 随机倒计时播报）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD8D0(int this)  // 函数: 巨人语音装载
{
  char v3; // [esp-24h] [ebp-2Ch] BYREF
  void *v4; // [esp-20h] [ebp-28h]
  int v5; // [esp-1Ch] [ebp-24h]
  int v6; // [esp-18h] [ebp-20h]
  int v7; // [esp-14h] [ebp-1Ch]
  int v8; // [esp-10h] [ebp-18h]
  int v9; // [esp-Ch] [ebp-14h]
  int v10; // [esp-8h] [ebp-10h]
  size_t v11; // [esp-4h] [ebp-Ch]
  char *v12; // [esp+4h] [ebp-4h]

  v11 = 11;
  v10 = (int)"R_GIANT_ATK";  // 资源/动画 TAG R_GIANT_ATK
  *(uint32_t *)(this + 6792) = 2;  // this+6792 【推断】炮车/子类参数面槽 1
  *(uint32_t *)(this + 6796) = 2;  // this+6796 【推断】炮车/子类参数面槽 2
  *(uint32_t *)(this + 6800) = 3;  // this+6800 【推断】炮车/子类参数面槽 3
  *(uint32_t *)(this + 6804) = 4;  // this+6804 【推断】炮车/子类参数面槽 4
  *(uint32_t *)(this + 6808) = 6;  // this+6808 【推断】炮车/子类参数面槽 5
  sub_4015C0((void *)v10, v11);  // 【std::string构造赋值】
  sub_4015C0("R_GIANT_ROAR", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GIANT_DMG", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("R_GIANT_DIE", 0xBu);  // 【std::string构造赋值】
  v11 = 10000;
  v10 = 5000;
  *(uint32_t *)(this + 7324) = 300;
  *(uint32_t *)(this + 8632) = 0;  // this+8632 【推断】子类 AI 资源/计数槽
  *(uint8_t *)(this + 8636) = 0;  // this+8636 【推断】传送/钻地相位槽
  v12 = &v3;
  *(uint8_t *)(this + 8613) = 0;  // this+8613 锁定/相位字节 B
  *(uint8_t *)(this + 8614) = 0;  // this+8614 锁定/相位字节 C
  v9 = 15;
  v8 = 0;
  LOBYTE(v4) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("R_GOLEM_AMB", 0xBu);  // 【std::string构造赋值】
  return sub_4DE5E0(v3, v4, v5, v6, v7, v8, v9, v10, v11);  // 调 文案条目装载 + 随机倒计时（0x4DE410 的配套件）
}



// 登场曲：sub_406D60 写 "B_FLATANY_01"（47L；与 0x5A6FF0 石魔像同曲）
// ------------------------------------------------------------
// 0x5CD9B0 sub_5CD9B0 —— 登场曲与行为字分派
// ·按行为字槽 1787 分派：0 段在 1943==3 困难级播 B_FLATANY_01 登场曲
// ·4/5/13/14/15 段经 vt+1104 切换行为字（0 与 5、13 与 5 互切）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD9B0(int *this)  // 函数: 登场曲与行为字分派
{
  int result; // eax
  int *pThis; // ecx

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148 = nBigState
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
      if ( *(this + 1943) == 3 )  // this+7772 = nCounterState
        result = sub_406D60("B_FLATANY_01");  // 调 std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      pThis = this;
      if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
        goto LABEL_10;
      goto LABEL_5;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result == 0 )
LABEL_5:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
      break;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result != 0 )  // 若结果非 0（成功）
      {
        pThis = this;
LABEL_10:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(pThis, 5);  // 调用虚函数（虚表槽 +1104）
      }
      break;
    default:
      return result;
  }
  return result;
}



// ============================================================
// 【分区 9】玛格纳三巨头（Goliath / Atlas / Titan）（0x5CDA80-0x5CEFD0）
// 证据：SIZZLE_CREATE/ENERGY_CHARGE 充能、Monster/Magma/Animation_Atlas/die.ani +
//       Equipment/Monster/Magma/Atlas/Atlas{Arm,Belly,Head,Leg1,Leg2}Animation/die.ani
//       五部件分体死亡、ThrowWeb.ptl + Animation_Atlas/ThrowWebEffect.ani + QUICK_TURN、
//       UPPER_HIT、Monster/Magma/{Goliath,Atlas,Titan}/* 五件套外观

// 巨人砸地（164L）：Monster/Magma/Animation_Common/DownAttackEffect.ani +
//   TAU_GROUND_HIT 播报（this+200/8632/8680 相位）
// ------------------------------------------------------------
// 0x5CDA80 sub_5CDA80 —— 巨人砸地
// ·vt+724==0 先转 5CD6F0；vt+840==8 时懒建 8680 霸体 PO（sub_51A7D0）
// ·子段 2：sub_431860 载 DownAttackEffect.ani，sub_44E1F0/432E50 建特效体
// ·vt+124 随机 ±21、vt+152 朝向取 ±150 偏移后 vt+112 摆位
// ·8632==1：sub_424120 音效 + TAU_GROUND_HIT + 发射 30054 砸地弹
// ·取 dword_8F8270[vt+924(40)] 特效随机 ±30 摆位后 sub_4600B0 挂接
// ------------------------------------------------------------
char /*thiscall*/ sub_5CDA80(int this)  // 函数: 巨人砸地
{
  void *pMem; // eax
  int *pFlagObj; // eax
  int pFlagVt; // edx
  int fld_21E8; // ecx  | +0x21E8 → 子类 AI 门字节（哥布林/人偶族机关门；哥布林工兵 +8680 区）【推断】（证据 va=005CDA80）（CNAbom；va=005CDA80）
  int pThis_94; // eax
  int hAniDown; // edi
  int *pFxObj; // edi
  int pVt; // eax
  int pFxVt; // ebx
  int nFaceRet; // eax
  int nFxId; // eax
  int nZ; // edi
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_98; // ebx
  int pThis_78; // eax
  int fld_74; // ecx  | +0x0074 → 观察者 vector 尾针（CNAbom；va=005CDA80）
  int *pThis_39C; // edi
  int nY; // eax
  int nX; // eax
  int pVt2; // edx
  int pFxVt2; // ebx
  int nProp884; // edi
  int nRand; // eax
  int pThis_7C2; // eax
  int pThis_982; // edi
  void *pObj; // edi
  void *fld_742; // ecx
  int pThis_782; // [esp-8h] [ebp-34h]
  void *aArgList[4]; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+18h] [ebp-14h]
  bool bFired; // [esp+1Fh] [ebp-Dh]
  int nCtorState; // [esp+28h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 724))(this) == 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
    sub_5CD6F0((char *)this);  // 调 砸地窗口
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( *(uint32_t *)(this + 8680) == 0 )  // this+8680 子类 AI 门字节
    {
      pMem = operator new(0x64u);  // operator new 分配 100 字节
      Block = pMem;
      nCtorState = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        pFlagObj = (int *)sub_51A7D0(pMem);  // 调 构造后把时长写入虚 64 结果 +40
      else
        pFlagObj = nullptr;
      *(uint32_t *)(this + 8680) = pFlagObj;  // this+8680 子类 AI 门字节
      pFlagVt = *pFlagObj;
      nCtorState = -1;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(pFlagVt + 64))(pFlagObj) + 36) = 0;  // 调用虚函数（虚表槽 +64）【推断: 取观察者容器（懒创建 0x44 字节 sb_499960(thi…】
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8680) + 80))(*(uint32_t *)(this + 8680)) == 0 )  // 调用虚函数（虚表槽 +80）
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, uint32_t, int))(**(uint32_t **)(this + 8680) + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
        *(uint32_t *)(this + 8680),  // this+8680 子类 AI 门字节
        this,
        this,
        1,
        0,
        0,
        -1);
  }
  else
  {
    fld_21E8 = *(uint32_t *)(this + 8680);  // this+8680 子类 AI 门字节
    if ( fld_21E8 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_21E8 + 80))(fld_21E8) == 1 )  // 调用虚函数（虚表槽 +80）
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8680) + 76))(*(uint32_t *)(this + 8680), 0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0(this + 7028) == 0 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    pThis_94 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    if ( pThis_94 == 2 )
    {
      if ( *(uint32_t *)(this + 8632) == 0 )  // this+8632 子类 AI 资源/计数槽
      {
        *(uint32_t *)(this + 8632) = 1;  // this+8632 子类 AI 资源/计数槽
        nCtorState = 1;
        if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
          hAniDown = sub_431860((char)"Monster/Magma/Animation_Common/DownAttackEffect.ani", 1);  // 调 动画件构造（资源 id 版）
        else
          hAniDown = 0;
        Block = (void *)sub_44B6C0(284);  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
        nCtorState = 2;
        if ( Block != nullptr )  // 若 Block 有效（非空）
          pFxObj = (int *)sub_44E1F0(hAniDown, 1);  // 调 CNRDPooledObject 构造（虚表覆盖壳）
        else
          pFxObj = nullptr;
        pVt = *(uint32_t *)this;
        pFxVt = *pFxObj;
        Block = pFxObj;
        nCtorState = -1;
        nFaceRet = (*(int (/*thiscall*/ **)(int))(pVt + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        nFxId = sub_432E50(nFaceRet);  // 调 关系码对调映射
        (*(void (/*thiscall*/ **)(int *, int))(pFxVt + 148))(pFxObj, nFxId);  // 调用虚函数（虚表槽 +148）【推断: 同 vmt90 但不检查（直接写）】
        sub_45FE80(*(uint32_t *)(this + 116), (int)pFxObj, 2, 0, (int)pFxObj, this, 0);  // 调 对象注册
        nZ = *pFxObj;
        pThis_80 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // 调用虚函数（虚表槽 +128）
        pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_80 + 21);  // 调用虚函数（虚表槽 +124）
        pThis_98 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, pThis_7C) != 0 ? 150 : -150;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        pThis_78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        (*(void (/*thiscall*/ **)(void *, int))(nZ + 112))(Block, pThis_78 + pThis_98);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      }
    }
    else if ( pThis_94 < 2 )
    {
      return sub_4E1780((uint32_t *)this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
    }
    if ( *(uint32_t *)(this + 8632) == 1 )  // this+8632 子类 AI 资源/计数槽
    {
      fld_74 = *(uint32_t *)(this + 116);  // this+116 观察者 vector 尾针
      *(uint32_t *)(this + 8632) = 3;  // this+8632 子类 AI 资源/计数槽
      sub_424120(*(uint32_t **)(fld_74 + 132), 4, 400);  // 调 屏幕震动启动
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        this,
        "TAU_GROUND_HIT",  // 资源/动画 TAG TAU_GROUND_HIT
        -1,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
        this,
        30054,
        2,
        0,
        0,
        100,
        0,
        0,
        4,
        0,
        0,
        0);
      pThis_39C = (int *)dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 924))(this, 40)];  // 调用虚函数（虚表槽 +924）
      nY = *(uint32_t *)this;
      Block = pThis_39C;
      nX = (*(int (/*thiscall*/ **)(int))(nY + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      pVt2 = *(uint32_t *)this;
      pFxVt2 = *pThis_39C;
      bFired = nX == 0;
      nProp884 = (*(int (/*thiscall*/ **)(int))(pVt2 + 128))(this);  // 调用虚函数（虚表槽 +128）
      nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
      pThis_7C2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, nRand % 10 + nProp884);  // 调用虚函数（虚表槽 +124）
      pThis_982 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, pThis_7C2 + 30) != 0 ? 100 : -100;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      pThis_782 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) + pThis_982;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      pObj = Block;
      (*(void (/*thiscall*/ **)(void *, int))(pFxVt2 + 40))(Block, pThis_782);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
      *(uint8_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 28))(Block) + 84) = bFired;  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);  // 调用虚函数（虚表槽 +12）
      (*(void (/*thiscall*/ **)(void *, void **))(*(uint32_t *)pObj + 92))(pObj, aArgList);  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
      fld_742 = *(void **)(this + 116);  // this+116 观察者 vector 尾针
      nCtorState = 3;
      sub_4600B0(fld_742, 2, 0, (int)aArgList);  // 调 演播层注册(槽号)
      nCtorState = -1;
      sub_5E5260(aArgList);  // 调 动画子对象清理临时缓冲
    }
  }
  return sub_4E1780((uint32_t *)this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}


// 充能态（197L）：SIZZLE_CREATE 生成 + ENERGY_CHARGE 充能播报
//   （this+200/204/208/8684/8685 相位）
// ------------------------------------------------------------
// 0x5CDDD0 sub_5CDDD0 —— 充能弹幕
// ·按 vt+736/740 血量比创建/回收 2178 霸体 PO
// ·2172/2173 阈值下按 2176/2177 数量沿 51.43 度均布 sin/cos 摆位
// ·逐个 vt+592 发射 601 弹幕，语音档(24,2)，置 8684/8685 一次门
// ·840==8 且 7028 段 1/0 切换 2179 分段，播 SIZZLE_CREATE/ENERGY_CHARGE
// ·尾部转 5CDA80
// ------------------------------------------------------------
int /*thiscall*/ sub_5CDDD0(uint32_t *this)  // 函数: 充能弹幕
{
  void *pMem; // eax
  int pObj; // eax
  int fld_e2178; // ecx  | +0x2208 → 数组容量端（(8712-8704)>>2 = 元素数）【推断】（CNGoliath）
  int fld_e2172; // edi  | +0x21F0 → 动态数组首指针（0x4A71C0 释放；0x5CD1E0 硬直清零）【推断：弹幕计数】（CNGoliath）
  int nIdx; // ebx
  int pVt; // edi
  int nParam601; // eax
  int nZ10; // eax
  uint64_t nYCos; // rax
  int fld_e2174; // eax  | +0x21F8 → 动态数组容量端（同 8688 三件套）【推断】（CNGoliath）
  int fld_e2173; // edi  | +0x21F4 → 动态数组游标/计数（同 8688 三件套）【推断】（CNGoliath）
  int nIdx2; // ebx
  int pVt2; // edi
  int nParam601b; // eax
  int nZ10b; // eax
  uint64_t nYCosb; // rax
  int fld_e2175; // eax  | +0x21FC → 相位字节（0x5CD1E0 清；0x5CF0F0 置 1；0x5CFB50 ==-1 判定）（CNGoliath）
  int nPhase; // eax
  uint32_t *fld_e15542; // eax
  int edxTmp; // edx
  int fld_e1554; // eax
  int edxTmp2; // edx
  float Block; // [esp+8h] [ebp-1Ch]
  void *Blocka; // [esp+8h] [ebp-1Ch]
  void *Blockb; // [esp+8h] [ebp-1Ch]
  long double fAngle; // [esp+Ch] [ebp-18h]
  long double v29; // [esp+Ch] [ebp-18h]
  float fHpRatio; // [esp+10h] [ebp-14h]
  int nIdxA; // [esp+14h] [ebp-10h]
  int nIdxB; // [esp+14h] [ebp-10h]

  fHpRatio = (double)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 6) * 0.0099999998;  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  Block = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
  if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * fHpRatio < Block )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
  {
    fld_e2178 = *(this + 2178);  // this+8712〔nCandTblEnd8712(推断)〕
    if ( fld_e2178 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2178 + 80))(fld_e2178) == 1 )  // 调用虚函数（虚表槽 +80）
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2178) + 76))(*(this + 2178), 0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  }
  else
  {
    if ( *(this + 2178) == 0 )  // this+8712〔nCandTblEnd8712(推断)〕
    {
      pMem = operator new(0x64u);  // operator new 分配 100 字节
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        pObj = sub_51A7D0(pMem);  // 调 构造后把时长写入虚 64 结果 +40
      else
        pObj = 0;
      *(this + 2178) = pObj;  // this+8712〔nCandTblEnd8712(推断)〕
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;  // 调用虚函数（虚表槽 +64）【推断: 取观察者容器（懒创建 0x44 字节 sb_499960(thi…】
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2178) + 80))(*(this + 2178)) == 0 )  // 调用虚函数（虚表槽 +80）
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2178) + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
        *(this + 2178),  // this+8712〔nCandTblEnd8712(推断)〕
        this,
        this,
        1,
        0,
        0,
        -1);
  }
  fld_e2172 = *(this + 2172) * (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) / 100;  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) < fld_e2172 && *((uint8_t *)this + 8684) == 0 )  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    {
      nIdx = 0;
      for ( nIdxA = 0; nIdx < *(this + 2176); nIdxA = nIdx )  // this+8704〔pSegNameTbl8704(推断)〕
      {
        pVt = *this;
        fAngle = (double)nIdxA * 51.42857142857143;
        nParam601 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t))(*this + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
               this,
               0,
               0,
               0,
               0xFFFF,
               0,
               1,
               0,
               0);
        nZ10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 128))(this, nParam601);  // 调用虚函数（虚表槽 +128）
        nYCos = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nZ10 + 10)  // 调用虚函数（虚表槽 +124）
                               + sin(fAngle) * 100.0);  // 调 正弦
        Blocka = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 120))(this, nYCos);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        fld_e2174 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 376))(  // 调用虚函数（虚表槽 +376）
                this,
                *(this + 2174),  // this+8696〔uVec8696(推断)〕
                (uint64_t)((double)(int)Blocka + cos(fAngle) * 100.0));  // 调 余弦
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(pVt + 592))(this, 601, fld_e2174);  // 调用虚函数（虚表槽 +592）【推断: 位置/状态同步包发布（短版 48024 / 长版 type 22…】
        ++nIdx;
      }
    }
    sub_4DB130(this, 24, 2u);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
    *((uint8_t *)this + 8684) = 1;  // this+8684 充能弹幕一次门 A
  }
  fld_e2173 = *(this + 2173) * (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) / 100;  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) < fld_e2173 && *((uint8_t *)this + 8685) == 0 )  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    {
      nIdx2 = 0;
      for ( nIdxB = 0; nIdx2 < *(this + 2177); nIdxB = nIdx2 )  // this+8708〔pCandTbl8708(推断)〕
      {
        pVt2 = *this;
        v29 = (double)nIdxB * 51.42857142857143;
        nParam601b = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t))(*this + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                this,
                0,
                0,
                0,
                0xFFFF,
                0,
                1,
                0,
                0);
        nZ10b = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 128))(this, nParam601b);  // 调用虚函数（虚表槽 +128）
        nYCosb = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nZ10b + 10)  // 调用虚函数（虚表槽 +124）
                               + sin(v29) * 100.0);  // 调 正弦
        Blockb = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 120))(this, nYCosb);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        fld_e2175 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 376))(  // 调用虚函数（虚表槽 +376）
                this,
                *(this + 2175),  // this+8700〔uPhase8700(推断)〕
                (uint64_t)((double)(int)Blockb + cos(v29) * 100.0));  // 调 余弦
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(pVt2 + 592))(this, 601, fld_e2175);  // 调用虚函数（虚表槽 +592）【推断: 位置/状态同步包发布（短版 48024 / 长版 type 22…】
        ++nIdx2;
      }
    }
    sub_4DB130(this, 24, 2u);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
    *((uint8_t *)this + 8685) = 1;  // this+8685 充能弹幕一次门 B
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    nPhase = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    if ( nPhase != 0 )
    {
      if ( nPhase >= 1 && *(this + 2179) == 1 )  // this+8716〔uArr8716〕
      {
        fld_e1554 = *(this + 1554);  // this+6216 = 资源/帧游标表
        edxTmp2 = *this;
        *(this + 2179) = 2;  // this+8716〔uArr8716〕
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(edxTmp2 + 208))(this, *(uint32_t *)(fld_e1554 + 4));  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));  // this+6216 = 资源/帧游标表
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
          this,
          0,
          *(uint32_t *)(*(this + 1554) + 8),  // this+6216 = 资源/帧游标表
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          this,
          "SIZZLE_CREATE",  // 资源/动画 TAG SIZZLE_CREATE
          -1,
          0,
          0);
      }
    }
    else if ( *(this + 2179) == 0 )  // this+8716〔uArr8716〕
    {
      fld_e15542 = (uint32_t *)*(this + 1554);  // this+6216 = 资源/帧游标表
      edxTmp = *this;
      *(this + 2179) = 1;  // this+8716〔uArr8716〕
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(edxTmp + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        0,
        *fld_e15542,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        0,
        *(uint32_t *)(*(this + 1554) + 4),  // this+6216 = 资源/帧游标表
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        this,
        "ENERGY_CHARGE",  // 资源/动画 TAG ENERGY_CHARGE
        -1,
        0,
        0);
    }
  }
  return sub_5CDA80(this);  // 调 巨人砸地
}


// 阿特拉斯分体死亡（113L）：Monster/Magma/Animation_Atlas/die.ani + Equipment/Monster/
//   Magma/Atlas/Atlas{Arm,Belly,Head,Leg1,Leg2}Animation/die.ani —— 五部件各自倒地
// ------------------------------------------------------------
// 0x5CE240 sub_5CE240 —— 阿特拉斯分体死亡
// ·vt+840 后转 5CD170；死亡段 ArgList==5 按 1943==3 分语音档(24,4)/(24,3)
// ·sub_431860 载 Animation_Atlas/die.ani 与 Atlas{Arm,Belly,Head,Leg1,Leg2}
// ·Animation/die.ani 六件，经 vt+196/204 写各部件帧（分体倒地）
// ·ArgList==8 段 2 清 2174；段空按 50% 走 sub_4DB200
// ------------------------------------------------------------
int /*thiscall*/ sub_5CE240(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 阿特拉斯分体死亡
{
  int result; // eax
  int nRand; // eax
  int v8; // ebx
  int v9; // edi
  int ArgLista; // [esp+24h] [ebp+8h]
  int v11; // [esp+28h] [ebp+Ch]
  int v12; // [esp+2Ch] [ebp+10h]
  int v13; // [esp+30h] [ebp+14h]

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  result = sub_5CD170(this, ArgList, fArg3, nArg4, nArg5);  // 调 崩击播报
  if ( ArgList == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result == 2 )
        *(this + 2174) = 0;  // this+8696〔uVec8696(推断)〕
    }
    else
    {
      return sub_4DB130(24, 2);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
    }
  }
  else if ( ArgList != 0 )
  {
    if ( ArgList == 5 )
    {
      if ( *(this + 1943) == 3 )  // this+7772 = nCounterState
        sub_4DB130(24, 4);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      else
        sub_4DB130(24, 3);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
        v13 = sub_431860((char)"Monster/Magma/Animation_Atlas/die.ani", 1);  // 调 动画件构造（资源 id 版）
      else
        v13 = 0;
      v8 = 0;
      if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
        v12 = sub_431860((char)"Equipment/Monster/Magma/Atlas/AtlasArmAnimation/die.ani", 1);  // 调 动画件构造（资源 id 版）
      else
        v12 = 0;
      if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
        v11 = sub_431860((char)"Equipment/Monster/Magma/Atlas/AtlasBellyAnimation/die.ani", 1);  // 调 动画件构造（资源 id 版）
      else
        v11 = 0;
      if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
        ArgLista = sub_431860((char)"Equipment/Monster/Magma/Atlas/AtlasHeadAnimation/die.ani", 1);  // 调 动画件构造（资源 id 版）
      else
        ArgLista = 0;
      if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
        v8 = sub_431860((char)"Equipment/Monster/Magma/Atlas/AtlasLeg1Animation/die.ani", 1);  // 调 动画件构造（资源 id 版）
      if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
        v9 = sub_431860((char)"Equipment/Monster/Magma/Atlas/AtlasLeg2Animation/die.ani", 1);  // 调 动画件构造（资源 id 版）
      else
        v9 = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 196))(this, v13);  // 调用虚函数（虚表槽 +196）
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        1,
        v12,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        2,
        v11,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        3,
        ArgLista,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        4,
        v8,
        0,
        0,
        0,
        0);
      return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
               this,
               5,
               v9,
               0,
               0,
               0,
               0);
    }
  }
  else
  {
    nRand = rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
    return sub_4DB200(24, nRand == 0);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
  }
  return result;
}



// 吐丝/转身（125L）：ENERGY_CHARGE + Particle/ThrowWeb.ptl +
//   Animation_Atlas/ThrowWebEffect.ani + QUICK_TURN 播报（sub_431920）
// ------------------------------------------------------------
// 0x5CE500 sub_5CE500 —— 吐丝与转身
// ·1943==3 困难级且 vt+736 低于 2171 比例阈值时 vt+672 双段速率缩放
// ·（sub_4AED60），触发 8688 一次门
// ·840==8 且 7028 段==2：ENERGY_CHARGE 播报后 vt+588 载 Particle/ThrowWeb.ptl
// ·sub_431920 载 Animation_Atlas/ThrowWebEffect.ani，投掷件偏移 +65 摆位
// ·vt+212 播 QUICK_TURN，尾部转 5CDA80
// ------------------------------------------------------------
int /*usercall*/ sub_5CE500@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, float fArg3@<edi>)  // 实现：吐丝与转身
{
  int nHpThresh; // edi
  int nPoseIdx; // edi
  uint32_t *pAniTbl; // eax
  int pVt; // edx
  int pAniBlk; // eax
  int pVt2; // edx
  int pVt3; // edi
  int pAniSrc; // eax
  int hWebFxAni; // edi
  int pNameBase; // ecx
  int *pFxObj; // edi
  int pFxVt; // ebx
  int nFaceRet; // eax
  int nX2; // eax
  int nZ2; // ebx
  int nY2; // eax
  int nX3; // eax
  float fArg32; // [esp-8h] [ebp-1Ch]
  int nPad1; // [esp+4h] [ebp-10h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  {
    fArg32 = fArg3;
    if ( pDwArg1[1943] == 3 )
    {
      nHpThresh = pDwArg1[2171] * (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1) / 100;  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
      if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 736))(pDwArg1) < nHpThresh && *((uint8_t *)pDwArg1 + 8688) == 0 )  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 672))(pDwArg1, 0, 1069547520);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
        sub_4AED60(fArg32);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 672))(pDwArg1, 0);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
        sub_4AED60(1.5);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 676))(pDwArg1, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
        *((uint8_t *)pDwArg1 + 8688) = 1;
      }
    }
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      nPoseIdx = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) + 148);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      if ( nPoseIdx == 0 && pDwArg1[2174] == 0 )
      {
        pAniTbl = (uint32_t *)pDwArg1[1554];
        pVt = *pDwArg1;
        pDwArg1[2174] = 1;
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 204))(  // 调用虚函数（虚表槽 +204）
          pDwArg1,
          0,
          *pAniTbl,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(  // 调用虚函数（虚表槽 +204）
          pDwArg1,
          0,
          *(uint32_t *)(pDwArg1[1554] + 4),
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ENERGY_CHARGE", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      }
      if ( pDwArg1[2174] == 1 && nPoseIdx == 4 )
      {
        pAniBlk = pDwArg1[1554];
        pVt2 = *pDwArg1;
        pDwArg1[2174] = 2;
        (*(void (/*thiscall*/ **)(int *, uint32_t, float, int))(pVt2 + 208))(  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
          pDwArg1,
          *(uint32_t *)(pAniBlk + 4),
          COERCE_FLOAT(LODWORD(fArg32)),  // 调 取 64 位值低 32 位
          nArg2);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)pDwArg1[1554]);  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
        pVt3 = *pDwArg1;
        pAniSrc = (*(int (/*thiscall*/ **)(int *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 588))(  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
                pDwArg1,
                "Particle/ThrowWeb.ptl",  // 资源路径 Particle/ThrowWeb.ptl
                0,
                65,
                0,
                50,
                4,
                0,
                0,
                0);
        (*(void (/*thiscall*/ **)(int *, int, int, int))(pVt3 + 580))(pDwArg1, 21015, pDwArg1[2173], pAniSrc);  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
        hWebFxAni = 0;
        if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
        {
          if ( (unsigned int)pDwArg1[96] < 0x10 )
            LOBYTE(pNameBase) = (uint8_t)pDwArg1 + 108;  // 调 取 16 位值低 8 位
          else
            pNameBase = pDwArg1[91];
          hWebFxAni = sub_431920(pNameBase, (char)"Animation_Atlas/ThrowWebEffect.ani", 1);  // 调 动画件构造（文件名版）
        }
        if ( sub_44B6C0(284) != 0 )  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
          pFxObj = (int *)sub_44E1F0(hWebFxAni, 1);  // 调 CNRDPooledObject 构造（虚表覆盖壳）
        else
          pFxObj = nullptr;
        sub_45FE80(pDwArg1[29], (int)pFxObj, 2, 0, (int)pFxObj, (int)pDwArg1, 0);  // 调 对象注册
        pFxVt = *pFxObj;
        nFaceRet = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        (*(void (/*thiscall*/ **)(int *, int))(pFxVt + 148))(pFxObj, nFaceRet);  // 调用虚函数（虚表槽 +148）【推断: 同 vmt90 但不检查（直接写）】
        if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          nX2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) + 65;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        else
          nX2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) - 65;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        nZ2 = *pFxObj;
        nPad1 = nX2;
        nY2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调用虚函数（虚表槽 +128）
        nX3 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, nY2 + 50);  // 调用虚函数（虚表槽 +124）
        (*(void (/*thiscall*/ **)(int *, int, int))(nZ2 + 112))(pFxObj, nPad1, nX3 - 10);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "QUICK_TURN", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      }
    }
  }
  return sub_5CDA80(pDwArg1);  // 调 巨人砸地
}


// 上勾/充能（134L）：UPPER_HIT + ENERGY_CHARGE 播报（this+200/204/208/8690 相位）
// ------------------------------------------------------------
// 0x5CE7F0 sub_5CE7F0 —— 上勾与充能
// ·vt+308 就绪：1813 非空且 840==0 时先调 5CD5E0 探测护盾
// ·vt+736 高于阈值建 2171 霸体 PO 并播档(24,4)；840==8 段 1/0 切 2173 分段
// ·播 UPPER_HIT/ENERGY_CHARGE
// ·840==8 段 2 且 8690 门且 vt+200 子段==11 时发射 48043 并清门
// ·尾部转 5CDA80
// ------------------------------------------------------------
char /*thiscall*/ sub_5CE7F0(uint32_t *this)  // 函数: 上勾与充能
{
  void *pMem; // eax
  int pObj; // eax
  int fld_e2171; // ecx  | +0x21EC → 子类 AI 槽（0x5CD3C0 三字节门复位族首槽）（证据 va=005CD3C0）（CNTitan；va=005CD3C0）
  int v5; // eax
  uint32_t *fld_e15542; // eax
  int v7; // edx
  int fld_e1554; // eax  | +0x1848 → 资源/帧游标表（0x5CD4E0 取 +8 经 vt+208 复位绑定动画）（证据 va=005CD4E0）（CNTitan；va=005CD4E0）
  int v9; // edx
  float Block; // [esp+4h] [ebp-18h]
  float v12; // [esp+8h] [ebp-14h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  {
    if ( *(this + 1813) != 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0 )  // this+7252 = pTarget7252
      sub_5CD5E0((int)this);  // 调 护盾与光环探测
    v12 = (double)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0) * 0.0099999998;  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
    Block = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
    if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * v12 < Block )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    {
      fld_e2171 = *(this + 2171);  // this+8684〔bGate8684(推断)〕
      if ( fld_e2171 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2171 + 80))(fld_e2171) == 1 )  // 调用虚函数（虚表槽 +80）
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2171) + 76))(*(this + 2171), 0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    }
    else
    {
      if ( *(this + 2171) == 0 )  // this+8684〔bGate8684(推断)〕
      {
        pMem = operator new(0x64u);  // operator new 分配 100 字节
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
          pObj = sub_51A7D0(pMem);  // 调 构造后把时长写入虚 64 结果 +40
        else
          pObj = 0;
        *(this + 2171) = pObj;  // this+8684〔bGate8684(推断)〕
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;  // 调用虚函数（虚表槽 +64）【推断: 取观察者容器（懒创建 0x44 字节 sb_499960(thi…】
        sub_4DB130(24, 4);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      }
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2171) + 80))(*(this + 2171)) == 0 )  // 调用虚函数（虚表槽 +80）
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2171) + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
          *(this + 2171),  // this+8684〔bGate8684(推断)〕
          this,
          this,
          1,
          0,
          0,
          -1);
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      if ( v5 != 0 )
      {
        if ( v5 >= 1 && *(this + 2173) == 1 )  // this+8692〔uVec8692(推断)〕
        {
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 4));  // this+6216 = 资源/帧游标表
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));  // this+6216 = 资源/帧游标表
          fld_e1554 = *(this + 1554);  // this+6216 = 资源/帧游标表
          v9 = *this;
          *(this + 2173) = 2;  // this+8692〔uVec8692(推断)〕
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v9 + 204))(  // 调用虚函数（虚表槽 +204）
            this,
            0,
            *(uint32_t *)(fld_e1554 + 8),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
            this,
            "UPPER_HIT",  // 资源/动画 TAG UPPER_HIT
            -1,
            0,
            0);
        }
      }
      else if ( *(this + 2173) == 0 )  // this+8692〔uVec8692(推断)〕
      {
        fld_e15542 = (uint32_t *)*(this + 1554);  // this+6216 = 资源/帧游标表
        v7 = *this;
        *(this + 2173) = 1;  // this+8692〔uVec8692(推断)〕
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v7 + 204))(  // 调用虚函数（虚表槽 +204）
          this,
          0,
          *fld_e15542,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
          this,
          0,
          *(uint32_t *)(*(this + 1554) + 4),  // this+6216 = 资源/帧游标表
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          this,
          "ENERGY_CHARGE",  // 资源/动画 TAG ENERGY_CHARGE
          -1,
          0,
          0);
      }
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      && sub_41A5E0((unsigned int)(this + 1757)) == 2  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      && *((uint8_t *)this + 8690) != 0  // this+8690 硬直分支门
      && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) == 11 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
        this,
        48043,
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
      sub_4DB130(24, 5);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      *((uint8_t *)this + 8690) = 0;  // this+8690 硬直分支门
    }
  }
  return sub_5CDA80((int)this);  // 调 巨人砸地
}


// 戈利亚外观：Monster/Magma/Goliath/{GoliathHead,Arm,Belly,Leg1,Leg2}.equ 五件
// ------------------------------------------------------------
// 0x5CEAC0 sub_5CEAC0 —— 戈利亚外观装载
// ·依次 new 0x544 并 sub_4BA9E0 挂装 Goliath 五件 .equ（Head/Arm/Belly/Leg1/Leg2）
// ·与 ·sub_5CEC70 ·sub_5CEE20 同构（差异：路径换 Atlas/Titan）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CEAC0(void *this)  // 函数: 戈利亚外观装载
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *pMem4; // eax
  char *pMem5; // eax
  char *v8; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int pThis_3104; // eax
  int result; // eax
  char *Block; // [esp+Ch] [ebp-18h]
  char *v15; // [esp+10h] [ebp-14h]
  char *v16; // [esp+14h] [ebp-10h]

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    Block = sub_4BA9E0(pMem, "Monster/Magma/Goliath/GoliathHead.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    Block = nullptr;
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v15 = sub_4BA9E0(pMem2, "Monster/Magma/Goliath/GoliathArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v15 = nullptr;
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v16 = sub_4BA9E0(pMem3, "Monster/Magma/Goliath/GoliathBelly.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v16 = nullptr;
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v3 = sub_4BA9E0(pMem4, "Monster/Magma/Goliath/GoliathLeg1.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pMem5 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v8 = sub_4BA9E0(pMem5, "Monster/Magma/Goliath/GoliathLeg2.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v8 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v8);  // 调用虚函数（虚表槽 +784）
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v16);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v15);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);  // 调用虚函数（虚表槽 +4）
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, Block);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  return result;
}



// 阿特拉斯外观：Monster/Magma/Atlas/{AtlasHead,Arm,Belly,Leg1,Leg2}.equ 五件
// ------------------------------------------------------------
// 0x5CEC70 sub_5CEC70 —— 阿特拉斯外观装载
// ·与 ·sub_5CEAC0 同构（差异：Monster/Magma/Atlas 五件 .equ）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CEC70(void *this)  // 函数: 阿特拉斯外观装载
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *pMem4; // eax
  char *pMem5; // eax
  char *v8; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int pThis_3104; // eax
  int result; // eax
  char *v14; // [esp+Ch] [ebp-18h]
  char *v15; // [esp+10h] [ebp-14h]
  char *v16; // [esp+14h] [ebp-10h]

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v14 = sub_4BA9E0(pMem, "Monster/Magma/Atlas/AtlasHead.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v14 = nullptr;
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v15 = sub_4BA9E0(pMem2, "Monster/Magma/Atlas/AtlasArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v15 = nullptr;
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v16 = sub_4BA9E0(pMem3, "Monster/Magma/Atlas/AtlasBelly.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v16 = nullptr;
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v3 = sub_4BA9E0(pMem4, "Monster/Magma/Atlas/AtlasLeg1.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pMem5 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v8 = sub_4BA9E0(pMem5, "Monster/Magma/Atlas/AtlasLeg2.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v8 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v8);  // 调用虚函数（虚表槽 +784）
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v16);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v15);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);  // 调用虚函数（虚表槽 +4）
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v14);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  return result;
}



// 泰坦外观：Monster/Magma/Titan/{TitanHead,Arm,Belly,Leg1,Leg2}.equ 五件
// ------------------------------------------------------------
// 0x5CEE20 sub_5CEE20 —— 泰坦外观装载
// ·与 ·sub_5CEAC0 同构（差异：Monster/Magma/Titan 五件 .equ）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CEE20(void *this)  // 函数: 泰坦外观装载
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *pMem4; // eax
  char *pMem5; // eax
  char *v8; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int pThis_3104; // eax
  int result; // eax
  char *v14; // [esp+Ch] [ebp-18h]
  char *v15; // [esp+10h] [ebp-14h]
  char *v16; // [esp+14h] [ebp-10h]

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v14 = sub_4BA9E0(pMem, "Monster/Magma/Titan/TitanHead.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v14 = nullptr;
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v15 = sub_4BA9E0(pMem2, "Monster/Magma/Titan/TitanArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v15 = nullptr;
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v16 = sub_4BA9E0(pMem3, "Monster/Magma/Titan/TitanBelly.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v16 = nullptr;
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v3 = sub_4BA9E0(pMem4, "Monster/Magma/Titan/TitanLeg1.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pMem5 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v8 = sub_4BA9E0(pMem5, "Monster/Magma/Titan/TitanLeg2.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v8 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v8);  // 调用虚函数（虚表槽 +784）
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v16);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v15);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);  // 调用虚函数（虚表槽 +4）
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v14);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  return result;
}



// ============================================================
// 【分区 10】法师·阿莫尔（Amor）（0x5CEFD0-0x5CFF60）
// 证据：STAFF_HIT 法杖命中、AMOR_AMB_LOOP 环绕音、CONDITION_HASTE 加速状态播报、
//       this+8840..9012 扩展字段区（与 0x5D 守卫族同构, 见 expeller_guard.cpp）

// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5CEFD0 sub_5CEFD0 —— 状态施加门
// ·8669 门==1 时转 sub_4D6030 状态施加入口（略过式转发），否则直返
// ------------------------------------------------------------
int /*thiscall*/ sub_5CEFD0(uint8_t *this, void *pArg2, int nArg3, int nArg4)  // 函数: 状态施加门
{
  int result; // eax

  if ( *(this + 8669) == 1 )  // this+8669 = 守卫激活位
    return sub_4D6030((int)this, pArg2, nArg3, nArg4);  // 调 ★ 状态施加入口（17 状态槽懒创建 + 转发）
  return result;
}



// 法杖命中：STAFF_HIT 播报（this+200/8668..8686 相位）
// ------------------------------------------------------------
// 0x5CEFF0 sub_5CEFF0 —— 法杖命中
// ·8668 门==1 且 2175==0：vt+144 后取 vt+200 对象 sub_493400 帧索引 +
// ·sub_4939E0 播放级联，置 8668/2175 与 8672 时钟 2000
// ·vt+840==14 蓄力架招时播 STAFF_HIT，尾部 4DA3B0 命中分发
// ------------------------------------------------------------
int /*thiscall*/ sub_5CEFF0(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 法杖命中
{
  int pThis_C8; // eax
  int pThis_C82; // eax

  if ( *(this + 8668) == 1 && *((uint32_t *)this + 2175) == 0 )  // this+8668 = nCool8668
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 144))(this);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
    pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 200))(this, 0);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    sub_493400(pThis_C8, 1);  // 调 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
    pThis_C82 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    sub_4939E0(pThis_C82, 1);  // 调 播放/暂停级联（递归子链 +204）
    *(this + 8668) = 1;  // this+8668 【推断】人偶行为模式
    *(this + 8685) = 0;  // this+8685 【推断】挥击/散射语音锁存
    *(this + 8686) = 0;
    sub_698F90((int)(this + 8672), 2000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *((uint32_t *)this + 2175) = 1;  // this+8700〔uPhase8700(推断)〕
  }
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 14 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      this,
      "STAFF_HIT",  // 资源/动画 TAG STAFF_HIT
      -1,
      0,
      0);
  return sub_4DA3B0(nArg2, nArg3, nArg4);  // 调 ★ 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CF0A0 sub_5CF0A0 —— 派生对象槽释放
// ·与 ·sub_5CD150 同构（差异：字段 this+2166）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF0A0(uint32_t *this)  // 函数: 派生对象槽释放
{
  int (/*thiscall*/ ***fld_e2166)(uint32_t, int); // ecx
  int result; // eax

  fld_e2166 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2166);  // this+8664 = 子类 AI 槽
  if ( fld_e2166 != nullptr )  // 若 fld_e2166 有效（非空）
    result = (**fld_e2166)(fld_e2166, 1);  // 调 fld_e2166 的虚函数（vt+0）
  *(this + 2166) = 0;  // this+8664 = 子类 AI 槽
  return result;
}



// AI 字段访问（this+8722）
// ------------------------------------------------------------
// 0x5CF0C0 sub_5CF0C0 —— 消亡通知转发
// ·转发 sub_4D9170 消亡通知；若 uArg2 为自身且 8722==1 再 vt+216 音效(10)
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF0C0(uint8_t *this, uint8_t *uArg2)  // 函数: 消亡通知转发
{
  int result; // eax

  result = sub_4D9170(uArg2);  // 调 消亡通知
  if ( uArg2 == this && *(this + 8722) == 1 )
    return (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 10);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
  return result;
}



// AI 字段访问（this+8668/8700）
// ------------------------------------------------------------
// 0x5CF0F0 sub_5CF0F0 —— 闸门复位
// ·清 8672 时钟门与 +13/+14 字节，重设 2000；置 8700==1、8668==0
// ------------------------------------------------------------
char /*thiscall*/ sub_5CF0F0(int this)  // 函数: 闸门复位
{
  int pThis_21E0; // ecx
  char result; // al

  pThis_21E0 = this + 8672;  // this+8672 【推断】子类 AI 相位槽
  *(uint8_t *)(pThis_21E0 + 13) = 0;
  *(uint8_t *)(pThis_21E0 + 14) = 0;
  result = sub_698F90(pThis_21E0, 2000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint32_t *)(this + 8700) = 1;  // this+8700 【推断】投石初始化标志
  *(uint8_t *)(this + 8668) = 0;  // this+8668 【推断】人偶行为模式
  return result;
}



// 主状态门（this+200/8668/8672）
// ------------------------------------------------------------
// 0x5CF120 sub_5CF120 —— 法杖态关闭
// ·清 8668 与 8672 时钟门，2175=2；vt+200 对象帧游标复位（sub_4926A0）
// ·并经 sub_4939E0 暂停播放级联
// ------------------------------------------------------------
char /*thiscall*/ sub_5CF120(uint8_t *this)  // 函数: 法杖态关闭
{
  int pThis_21E0; // ecx
  int v3; // eax
  int v4; // eax
  int pThis_C8; // eax

  pThis_21E0 = (int)(this + 8672);  // this+8672 = 子类 AI 槽
  *(this + 8668) = 0;  // this+8668 = nCool8668
  *(uint8_t *)(pThis_21E0 + 13) = 0;
  *(uint8_t *)(pThis_21E0 + 14) = 0;
  sub_698F90(pThis_21E0, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  v3 = *(uint32_t *)this;
  *((uint32_t *)this + 2175) = 2;  // this+8700〔uPhase8700(推断)〕
  v4 = (*(int (/*thiscall*/ **)(uint8_t *))(v3 + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  sub_4926A0(v4);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
  pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  return sub_4939E0(pThis_C8, 0);  // 调 播放/暂停级联（递归子链 +204）
}



// 环绕音：AMOR_AMB_LOOP 播报（57L；this+8600/8669/8721）
// ------------------------------------------------------------
// 0x5CF180 sub_5CF180 —— 环绕音管理
// ·8669==0 时 vt+1320 后初始化 2176..2178 三槽（全 -1 时逐槽取 vt+116(0..2)）
// ·8600==1 且 8669==1 时取 vt+1312 收手值经 vt+1316 触发
// ·2175>0 且 fld50==1 转 vt+232；状态非待机或死亡（双 4）时经 vt+216 收环绕音
// ·空闲且 8721 门未置时 vt+212 播 AMOR_AMB_LOOP(9)
// ------------------------------------------------------------
char /*thiscall*/ sub_5CF180(uint32_t *this)  // 函数: 环绕音管理
{
  int fld_e2176; // eax
  uint32_t *pThis_880; // ebx
  int i; // edi
  int v5; // edi
  int v6; // eax

  if ( *((uint8_t *)this + 8669) == 0 )  // this+8669 = 守卫激活位
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1320))(this);  // 调用虚函数（虚表槽 +1320）
    fld_e2176 = *(this + 2176);  // this+8704〔pSegNameTbl8704(推断)〕
    pThis_880 = this + 2176;
    if ( fld_e2176 == -1 && *(this + 2177) == -1 && *(this + 2178) == -1 )  // 若 fld_e2176 == -1
    {
      for ( i = 0; i < 3; ++i )  // 循环：i 从 0 递增到 3
        *pThis_880++ = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 116))(this, i);  // 调用虚函数（虚表槽 +116）
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*this + 108))(this, fld_e2176, *(this + 2177), *(this + 2178));  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
    }
  }
  if ( *((uint8_t *)this + 8600) == 1  // this+8600 = uAI8600
    && *((uint8_t *)this + 8669) == 1  // this+8669 = 守卫激活位
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1312))(this) >= 0 )  // 调用虚函数（虚表槽 +1312）
  {
    v5 = *this;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1312))(this);  // 调用虚函数（虚表槽 +1312）
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v5 + 1316))(this, v6);  // 调用虚函数（虚表槽 +1316）
  }
  if ( (int)*(this + 2175) > 0 && *(this + 50) == 1 )  // this+8700〔uPhase8700(推断)〕等 2 字段
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 232))(this);  // 调用虚函数（虚表槽 +232）
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 0  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this) == 4  // 调用虚函数（虚表槽 +184）【推断: 动画对象 z 倾斜转状态码】
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 188))(this) == 4 )  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
  {
    if ( *((uint8_t *)this + 8721) == 1 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
      *((uint8_t *)this + 8721) = 0;
    }
  }
  else if ( *((uint8_t *)this + 8721) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "AMOR_AMB_LOOP", 9, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
    *((uint8_t *)this + 8721) = 1;
    return sub_4E1780(this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  }
  return sub_4E1780(this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CF2C0 sub_5CF2C0 —— 血量档位计数
// ·按 vt+736/740 血量比与阈值 0.75/0.5/0.2 逐个比较，返回满足数（-1..2）
// ·【阈值取 1061158912/1056964608/1045220557 位型】
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF2C0(int *this)  // 函数: 血量档位计数
{
  int v1; // ebx
  int i; // edi
  int v4; // eax
  int v5; // edx
  uint32_t v7[3]; // [esp+Ch] [ebp-14h]
  float v8; // [esp+18h] [ebp-8h]
  int v9; // [esp+1Ch] [ebp-4h]

  v1 = -1;
  v7[0] = 1061158912;  // 常量 0.75f
  v7[1] = 1056964608;  // 常量 0.5f
  v7[2] = 1045220557;  // 浮点常量 0.2f
  for ( i = 0; i < 3; ++i )  // 循环：i 从 0 递增到 3
  {
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
    v5 = *this;
    v9 = v4;
    v8 = (float)v4;
    v9 = (*(int (/*thiscall*/ **)(int *))(v5 + 740))(this);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    if ( (double)v9 * *(float *)&v7[i] >= v8 )
      ++v1;
  }
  return v1;
}



// AI 字段访问（this+8604）
// ------------------------------------------------------------
// 0x5CF330 sub_5CF330 —— 受击后置门
// ·8604 门不为 1 时转 sub_4DA1D0 转发（否则直返）
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF330(uint8_t *this)  // 函数: 受击后置门
{
  int result; // eax

  if ( *(this + 8604) != 1 )  // this+8604 = bAI8604
    return sub_4DA1D0();
  return result;
}



// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5CF340 sub_5CF340 —— 伤害过滤与架招减伤
// ·sub_4DC390 伤害过滤得类型码；8669==0 时伤害按 0.01 缩放并返 0
// ·8669 非 0 且 840==14 架招时按攻方档位 vt+348 折算并返 2
// ·+12 档位==1 时 ×0.5，否则按 +124 档位 0/1 取 ×0.35/×0.25
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF340(uint8_t *this, int *pDwArg2, int nArg3)  // 函数: 伤害过滤与架招减伤
{
  int result; // eax
  int v5; // ebx

  result = sub_4DC390(pDwArg2, nArg3);  // 调 伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
  v5 = result;
  if ( result != 3 )
  {
    if ( *(this + 8669) != 0 )  // this+8669 守卫激活位
    {
      if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 14 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      {
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12) == 1 )  // 调用虚函数（虚表槽 +348）
        {
          *pDwArg2 = (uint64_t)((double)*pDwArg2 * 0.5);
          return 2;
        }
        else
        {
          if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 124) == 0 )  // 调用虚函数（虚表槽 +348）
            *pDwArg2 = (uint64_t)((double)*pDwArg2 * 0.34999999);
          if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 124) == 1 )  // 调用虚函数（虚表槽 +348）
            *pDwArg2 = (uint64_t)((double)*pDwArg2 * 0.25);
          return 2;
        }
      }
      else
      {
        return v5;
      }
    }
    else
    {
      *pDwArg2 = (uint64_t)((double)*pDwArg2 * 0.0099999998);  // ×0.01f（百分数转比例）
      return 0;
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CF430 sub_5CF430 —— 缓速判定位面初始化
// ·2203..2208 六槽置 1、2209 置 0 后返回 1（缓速判定位面初始化）【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF430(uint32_t *this)  // 函数: 缓速判定位面初始化
{
  *(this + 2203) = 1;  // this+8812〔uCharge8812(推断)〕
  *(this + 2204) = 1;  // this+8816〔uCharge8816(推断)〕
  *(this + 2205) = 1;  // this+8820〔uCharge8820(推断)〕
  *(this + 2206) = 1;  // this+8824〔uCharge8824〕
  *(this + 2207) = 1;
  *(this + 2208) = 1;  // this+8832〔uCharge8832〕
  *(this + 2209) = 0;
  return 1;  // 返回 1(成功)
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CF470 sub_5CF470 —— 架招反击挂钩（姿态 14 + vt+1336 触发）
//   姿态 vt+840==14（蓄力架招）且 nArg4==0 时先经 vt+1336 触发专属架招反击，再统一转 ·sub_5CEFF0 法杖命中分发 —— 与 ·0x5D06E0 守卫族同构。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF470(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 架招反击挂钩（姿态 14 + vt+1336 触发）
{
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 14 && (uint8_t)nArg4 == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)this + 1336))(this, nArg2, nArg3, 0);  // 调用虚函数（虚表槽 +1336）
  return sub_5CEFF0(this, nArg2, nArg3, nArg4);  // 调 法杖命中
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CF4C0 sub_5CF4C0 —— 伤害过滤门（姿态 8 + 2203 子槽）
//   姿态 vt+840!=8 或子状态 vt+908>=4 时一律转 ·sub_5CF340 伤害过滤与架招减伤；姿态 8 下查 this+2203+子状态 槽，等于 1 才就地返 1（该档伤害吸收【推断】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF4C0(uint8_t *this, int *pDwArg2, int nArg3)  // 函数: 伤害过滤门（姿态 8 + 2203 子槽）
{
  int pThis_89B; // edx
  int result; // eax

  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) != 8 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    return sub_5CF340(this, pDwArg2, nArg3);  // 调 伤害过滤与架招减伤
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 908))(this) >= 4 )  // 调用虚函数（虚表槽 +908）
    return sub_5CF340(this, pDwArg2, nArg3);  // 调 伤害过滤与架招减伤
  pThis_89B = *((uint32_t *)this + (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 908))(this) + 2203);  // 调用虚函数（虚表槽 +908）
  result = 1;
  if ( pThis_89B != 1 )
    return sub_5CF340(this, pDwArg2, nArg3);  // 调 伤害过滤与架招减伤
  return result;
}



// 时钟门 AI（sub_699000; this+200）
// ------------------------------------------------------------
// 0x5CF520 sub_5CF520 —— 法术层绘制（通道 1 附着 / 通道 0 闪烁）
//   先转 ·sub_4D8F90 基类绘制垫片；通道 nArg2==1（附着层）在 this+7801==1 且 vt+940==0 时，把 2209 绑定对象经 ·sub_4938F0 播放驱动 + ·sub_4924C0 取帧后，以 ·sub_491D00 在本体左移 6、上移 30 处下发图层。
//   通道 0（主层）在姿态 8、子状态 vt+908<4 且 2203 子槽==1、2208 门开、距 this+1777 时刻 >1000ms 时以 rand 作 ±4 抖动，经 ·sub_491DE0 纯 STENCIL 变体加绘闪烁（色 0xFF0000FF 蓝、透明度 0xC8 即 200【位型直读】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF520(int *this, int nArg2, int nArg3, int nArg4, float fArg5)  // 函数: 法术层绘制（通道 1 附着 / 通道 0 闪烁）
{
  int result; // eax
  int fld_e2209; // ecx
  int pObj; // eax
  int dword_79C0B02; // [esp-20h] [ebp-2Ch]
  int nRand2; // [esp-1Ch] [ebp-28h]
  int nRand; // [esp-18h] [ebp-24h]

  result = sub_4D8F90(nArg2, nArg3, nArg4, LODWORD(fArg5));  // 调 vmt144 转发垫片（IRDActiveObject__vmt144 族）
  if ( (uint8_t)nArg2 == 1 )
  {
    if ( *((uint8_t *)this + 7801) == 1 )  // this+7801 【推断】外观/激活门
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 940))(this);  // 调用虚函数（虚表槽 +940）
      if ( (uint8_t)result == 0 )
      {
        fld_e2209 = *(this + 2209);
        if ( fld_e2209 != 0 )
        {
          sub_4938F0(fld_e2209);  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
          pObj = sub_4924C0(0);  // 调 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
          return sub_491D00(dword_79C0B0, nArg3 - (*(uint32_t *)(*(uint32_t *)pObj + 20) >> 1) - 6, nArg4 - *(this + 40) - 30, 0.0);  // 调 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        }
      }
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    if ( result == 8 )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 940))(this);  // 调用虚函数（虚表槽 +940）
      if ( (uint8_t)result == 0 )
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 908))(this);  // 调用虚函数（虚表槽 +908）
        if ( result < 4 )
        {
          result = (*(int (/*thiscall*/ **)(int *))(*this + 908))(this);  // 调用虚函数（虚表槽 +908）
          if ( *(this + result + 2203) == 1 )
          {
            result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
            if ( result != 0 && *(this + 2208) == 1 )  // this+8832〔uCharge8832〕
            {
              result = sub_699000((int)(this + 9)) - *(this + 1777);  // 【clock_now(clk)】
              if ( result > 1000 )
              {
                nRand = rand() % 8 + nArg4 - 4;  // 调 以 16 位种子状态递推并返回 15 位结果
                nRand2 = rand() % 8 + nArg3 - 4;  // 调 以 16 位种子状态递推并返回 15 位结果
                dword_79C0B02 = dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
                (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
                return sub_491DE0(dword_79C0B02, nRand2, nRand, fArg5, 2, 1, -16776961, -922746881);  // 调 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
              }
            }
          }
        }
      }
    }
  }
  return result;
}



// 阿莫尔相位字段 A（this+8840..8972, 33L —— 与 0x5D 守卫族 88xx 字段区同构）
// ------------------------------------------------------------
// 0x5CF690 sub_5CF690 —— 相位字段复位 A（8853..9008）
//   清 8853/8854/8881/8882/8909/8910/8936/8953/8954 九位，8924 置 1、8928/8932 归零，8968..9008 十字段清零 —— 阿莫尔相位复位第一段（与 ·0x5D 守卫族 88xx 字段区同构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF690(int this)  // 函数: 相位字段复位 A（8853..9008）
{
  *(uint8_t *)(this + 8853) = 0;  // this+8853 相位标志
  *(uint8_t *)(this + 8854) = 0;  // this+8854 相位标志
  *(uint8_t *)(this + 8881) = 0;  // this+8881 相位/连段门
  *(uint8_t *)(this + 8882) = 0;  // this+8882 相位/连段门
  *(uint8_t *)(this + 8909) = 0;  // this+8909 相位字节
  *(uint8_t *)(this + 8910) = 0;  // this+8910 相位字节
  *(uint8_t *)(this + 8924) = 1;  // this+8924 相位门
  *(uint32_t *)(this + 8928) = 0;  // this+8928 相位/计数槽
  *(uint32_t *)(this + 8932) = 0;  // this+8932 三连段段号
  *(uint8_t *)(this + 8936) = 0;  // this+8936 相位字节
  *(uint8_t *)(this + 8953) = 0;  // this+8953 相位字节
  *(uint8_t *)(this + 8954) = 0;  // this+8954 相位字节
  *(uint32_t *)(this + 8968) = 0;  // this+8968 形态门
  *(uint32_t *)(this + 8972) = 0;  // this+8972 事件档位
  *(uint32_t *)(this + 8976) = 0;  // this+8976 事件档位
  *(uint32_t *)(this + 8980) = 0;  // this+8980 特效/资源槽
  *(uint32_t *)(this + 8984) = 0;  // this+8984 内嵌子对象 vftable 槽
  *(uint32_t *)(this + 8988) = 0;  // this+8988 内嵌子对象旗标
  *(uint32_t *)(this + 8992) = 0;  // this+8992 段时长换算槽
  *(uint32_t *)(this + 8996) = 0;  // this+8996 相位字节
  *(uint32_t *)(this + 9000) = 0;  // this+9000 相位槽
  *(uint32_t *)(this + 9004) = 0;  // this+9004 相位槽
  *(uint32_t *)(this + 9008) = 0;  // this+9008 段时长重排源
  return 0;
}



// 阿莫尔相位字段 B（this+8840..8912）
// ------------------------------------------------------------
// 0x5CF740 sub_5CF740 —— 相位字段复位 B（8840..8932）
//   清 8840/8844 双计数器与 8848/8865/8866 标志，8880..8888 与 8900..8932 两段归零，8896 写 0xBF800000（-1.0f）—— 阿莫尔相位初始化第二段。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF740(int this)  // 函数: 相位字段复位 B（8840..8932）
{
  *(uint32_t *)(this + 8840) = 0;  // this+8840 相位/档位槽
  *(uint32_t *)(this + 8844) = 0;  // this+8844 相位时钟槽
  *(uint8_t *)(this + 8848) = 0;  // this+8848 相位标志字节
  *(uint8_t *)(this + 8865) = 0;  // this+8865 相位标志字节
  *(uint8_t *)(this + 8866) = 0;  // this+8866 相位标志字节
  *(uint32_t *)(this + 8880) = 0;  // this+8880 相位区槽
  *(uint32_t *)(this + 8884) = 0;  // this+8884 相位区槽
  *(uint32_t *)(this + 8888) = 0;  // this+8888 相位区槽
  *(uint32_t *)(this + 8892) = 0;  // this+8892 呼吸发光中心/档位色基址
  *(uint32_t *)(this + 8896) = -1082130432;  // this+8896 呼吸发光振幅
  *(uint32_t *)(this + 8900) = 0;  // this+8900 呼吸周期/抖动振幅
  *(uint32_t *)(this + 8904) = 0;  // this+8904 呼吸/抖动渲染透明度源
  *(uint32_t *)(this + 8908) = 0;  // this+8908 相位区槽
  *(uint32_t *)(this + 8912) = 0;  // this+8912 相位区槽
  *(uint32_t *)(this + 8916) = 0;  // this+8916 相位区槽
  *(uint32_t *)(this + 8920) = 0;  // this+8920 相位区槽
  *(uint32_t *)(this + 8924) = 0;  // this+8924 相位门
  *(uint32_t *)(this + 8928) = 0;  // this+8928 相位区槽
  *(uint32_t *)(this + 8932) = 0;  // this+8932 相位槽/三连段段号
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CF7C0 sub_5CF7C0 —— 全局主管理器 +2492 槽清零
//   取全局 ·dword_8F8528（主管理器）把其 +2492 槽（第 623 号 dword）清零并返回该全局指针 —— 与 ·0x5D 守卫族同款收尾清位。
// ------------------------------------------------------------
void *sub_5CF7C0()  // 调 全局主管理器 +2492 槽清零
{
  void *result; // eax

  result = dword_8F8528;  // dword_8F8528 = 主管理器
  *((uint32_t *)dword_8F8528 + 623) = 0;  // dword_8F8528 = 主管理器
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CF7E0 sub_5CF7E0 —— 播放驱动转发（7801 门）
//   this+7801==1（外观/激活标记【推断】）时转 ·sub_499FF0 主播放驱动 usercall 变体，否则直返 —— 与 ·sub_5CF520 附着层同一 7801 门。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF7E0(uint8_t *this)  // 函数: 播放驱动转发（7801 门）
{
  int result; // eax

  if ( *(this + 7801) == 1 )  // this+7801 【推断】外观/激活门
    return sub_499FF0(this);  // 调 主播放驱动·usercall 变体（ecx/ebx 传参；+44 尾帧事件）
  return result;
}



// 阿莫尔相位字段 C（this+8840..9012）
// ------------------------------------------------------------
// 0x5CF7F0 sub_5CF7F0 —— 相位字段复位 C（8840..9048）
//   清 8840/8857/8858/8872/8889/8890/8929/8930/8957/8958 十字节标志与 8972..8980、9012..9048 两段 —— 阿莫尔相位复位第三段（字段区延展到 +9048）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF7F0(int this)  // 函数: 相位字段复位 C（8840..9048）
{
  *(uint8_t *)(this + 8840) = 0;  // this+8840 相位/档位槽
  *(uint8_t *)(this + 8857) = 0;  // this+8857 相位标志
  *(uint8_t *)(this + 8858) = 0;  // this+8858 相位标志
  *(uint8_t *)(this + 8872) = 0;  // this+8872 相位时长槽
  *(uint8_t *)(this + 8889) = 0;  // this+8889 相位字节
  *(uint8_t *)(this + 8890) = 0;  // this+8890 相位字节
  *(uint8_t *)(this + 8929) = 0;  // this+8929 相位字节
  *(uint8_t *)(this + 8930) = 0;  // this+8930 相位字节
  *(uint8_t *)(this + 8957) = 0;  // this+8957 相位字节
  *(uint8_t *)(this + 8958) = 0;  // this+8958 相位字节
  *(uint32_t *)(this + 8972) = 0;  // this+8972 事件档位
  *(uint32_t *)(this + 8976) = 0;  // this+8976 事件档位
  *(uint32_t *)(this + 8980) = 0;  // this+8980 特效/资源槽
  *(uint32_t *)(this + 9012) = 0;  // this+9012 时钟时长
  *(uint32_t *)(this + 9016) = 0;  // this+9016 阿莫尔相位第三段
  *(uint32_t *)(this + 9020) = 0;  // this+9020 阿莫尔相位第三段复位区
  *(uint32_t *)(this + 9024) = 0;  // this+9024 阿莫尔相位第三段复位区
  *(uint32_t *)(this + 9028) = 0;  // this+9028 阿莫尔相位第三段复位区
  *(uint32_t *)(this + 9032) = 0;  // this+9032 阿莫尔相位第三段复位区
  *(uint32_t *)(this + 9036) = 0;  // this+9036 阿莫尔相位第三段复位区
  *(uint32_t *)(this + 9040) = 0;  // this+9040 阿莫尔相位第三段复位区
  *(uint32_t *)(this + 9044) = 0;  // this+9044 阿莫尔相位第三段复位区
  *(uint32_t *)(this + 9048) = 0;  // this+9048 阿莫尔相位第三段复位区末槽
  return 0;
}



// 加速状态：CONDITION_HASTE 播报（35L）
// ------------------------------------------------------------
// 0x5CF880 sub_5CF880 —— 加速状态施加（CONDITION_HASTE + 三参数放速）
//   取 this+2259/+2260 千分比（×0.01）加到 vt+672(this,0) 参数块的 +830/+858/+914 三槽：·sub_41A5E0 读、·sub_41A590 回写并重建校验字，再 vt+676 应用。
//   随后 vt+212 播报 CONDITION_HASTE，并按 this+2243 经 ·sub_4DB130(24, …) 播随机文案/语音 —— 与 ·sub_5CFD80 变速应用（8840 档位）配套。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF880(int *this)  // 函数: 加速状态施加（CONDITION_HASTE + 三参数放速）
{
  unsigned int v2; // edi
  int v3; // edx
  unsigned int v4; // edi
  int v5; // edx
  unsigned int v6; // edi
  int v7; // edx
  float fld_e2260; // [esp+8h] [ebp-Ch]
  int v10; // [esp+8h] [ebp-Ch]
  int v11; // [esp+Ch] [ebp-8h]
  int v12; // [esp+Ch] [ebp-8h]
  float fld_e2259; // [esp+10h] [ebp-4h]

  fld_e2259 = (double)*(this + 2259) * 0.0099999998;  // this+9036〔uPhaseC9036〕
  fld_e2260 = (double)*(this + 2260) * 0.0099999998;  // this+9040〔uPhaseC9040〕
  v2 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(v2)) + fld_e2259;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(v2, v3, v11);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v4 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 858;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v4)) + fld_e2259;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(v4, v5, v12);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v6 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 914;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v6)) + fld_e2260;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(v6, v7, v10);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "CONDITION_HASTE", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
  return sub_4DB130(24, *(this + 2243));  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
}



// 时钟门 AI（sub_699000; this+8840/8857/8858）
// ------------------------------------------------------------
// 0x5CF980 sub_5CF980 —— 受击观察者通知（8840 置位 + 时钟门）
//   先把 8840 相位字节置 1；vt+940==1 且距 this+1777 时刻 >1000ms 时经 vt+944(this, 0, -1) 触发，清 8857/8858 并以 this+2253 为时长重排 this+2211 时钟。
//   尾调 ·sub_4D4A80 受方命中通知（18 观察者 vt+140 + 击杀归属时刻记录）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF980(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 受击观察者通知（8840 置位 + 时钟门）
{
  int v5; // eax

  v5 = *this;
  *((uint8_t *)this + 8840) = 1;  // this+8840 相位/档位槽
  if ( (*(uint8_t (**)(void))(v5 + 940))() == 1 && sub_699000((int)(this + 9)) - *(this + 1777) > 1000 )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 944))(this, 0, -1);  // 调用虚函数（虚表槽 +944）
    *((uint8_t *)this + 8857) = 0;  // this+8857 相位标志
    *((uint8_t *)this + 8858) = 0;  // this+8858 相位标志
    sub_698F90((int)(this + 2211), *(this + 2253), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return sub_4D4A80(this, nArg2, nArg3, nArg4);  // 调 受击后观察者 vt+516（六回调第 6 号，研究 §1.1/§1.2）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CF9F0 sub_5CF9F0 —— 事件包 17 分支（会话坐标取用 + 状态 13）
//   转 ·sub_4DC630 关卡/交互事件包处理后：返回 17 时从全局 ·dword_8F8520（会话/UDP 管理器）vt+80 连取两值作坐标交 vt+108 设置，再 vt+1104(this, 13) 切状态并返 -1 消化事件。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF9F0(void *this)  // 函数: 事件包 17 分支（会话坐标取用 + 状态 13）
{
  int result; // eax
  int v3; // [esp+8h] [ebp-8h] BYREF
  int v4; // [esp+Ch] [ebp-4h] BYREF

  result = sub_4DC630();  // 调 关卡/交互事件包处理（关联对象 this+7260 校验）
  if ( result == 17 )
  {
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v3);  // 调用虚函数（虚表槽 +80）
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v4);  // 调用虚函数（虚表槽 +80）
    (*(void (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 108))(this, v3, v4, 0);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
    return -1;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CFA60 sub_5CFA60 —— 反击前参数写 100.0f + 转反击判定
//   vt+348 攻击方档位块非空时把其 +72 处写 0x42C80000（100.0f，命中/反击倍率【推断】），再转 ·sub_4DB480 反击/架招触发判定（尾调攻方完整反应 ·sub_4D6D90）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFA60(void *this, int nArg2, int nArg3, int nArg4)  // 函数: 反击前参数写 100.0f + 转反击判定
{
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) != 0 )  // 调用虚函数（虚表槽 +348）
    *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 72) = 1120403456;  // 调用虚函数（虚表槽 +348）
  return sub_4DB480(nArg2, nArg3, nArg4);  // 调 ★ 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 阿莫尔相位字段 D（this+8853..8888）
// ------------------------------------------------------------
// 0x5CFAA0 sub_5CFAA0 —— 相位字段复位 D（8853..8888）
//   清 8853/8854，8868 置 1、8872..8888 五段归零 —— 阿莫尔相位复位第四段（与 ·sub_5CF690 同族，字段区间更短）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFAA0(int this)  // 函数: 相位字段复位 D（8853..8888）
{
  *(uint8_t *)(this + 8853) = 0;  // this+8853 相位标志
  *(uint8_t *)(this + 8854) = 0;  // this+8854 相位标志
  *(uint8_t *)(this + 8868) = 1;  // this+8868 冰守卫交互门
  *(uint32_t *)(this + 8872) = 0;  // this+8872 相位时长槽
  *(uint32_t *)(this + 8876) = 0;  // this+8876 相位区槽
  *(uint32_t *)(this + 8880) = 0;  // this+8880 相位区槽
  *(uint32_t *)(this + 8884) = 0;  // this+8884 相位区槽
  *(uint32_t *)(this + 8888) = 0;  // this+8888 相位区槽
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CFAE0 sub_5CFAE0 —— 节拍区复位（2210 置 2 + 2211..2226 清零）
//   2210 置 2（节奏/模式索引【推断】），this+2211 起的时钟块（·sub_698F90 载体）与 2212..2226 子状态槽全部清零 —— ·sub_5CF980/·sub_5CFB50 族共用的节拍区初始化。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFAE0(uint32_t *this)  // 函数: 节拍区复位（2210 置 2 + 2211..2226 清零）
{
  *(this + 2210) = 2;  // this+8840〔uPhase8840(推断)〕
  *(this + 2211) = 0;  // this+8844〔uPhaseClock8844〕
  *(this + 2212) = 0;  // this+8848〔bPhase8848〕
  *(this + 2213) = 0;
  *(this + 2214) = 0;
  *(this + 2215) = 0;
  *(this + 2216) = 0;
  *(this + 2217) = 0;  // this+8868〔bGate8868〕
  *(this + 2218) = 0;  // this+8872〔uDur8872(推断)〕
  *(this + 2219) = 0;  // this+8876〔uPhase8876〕
  *(this + 2220) = 0;  // this+8880〔uPhase8880〕
  *(this + 2221) = 0;  // this+8884〔uPhase8884〕
  *(this + 2222) = 0;  // this+8888〔uPhase8888〕
  *(this + 2223) = 0;  // this+8892〔nGlowCenter8892(推断)〕
  *(this + 2224) = 0;  // this+8896〔uGlowAmp8896〕
  *(this + 2225) = 0;  // this+8900〔uGlowPeriod8900(推断)〕
  *(this + 2226) = 0;  // this+8904〔bGlowAlpha8904(推断)〕
  return 0;
}



// 复合门（this+200/8700/8840/8900/8904）
// ------------------------------------------------------------
// 0x5CFB50 sub_5CFB50 —— 通道 0 抖动加绘（8840 档位配色 + 8900 振幅）
//   先转 ·sub_5CF520 绘制；非附着通道、8840!=2、8700==-1 且 vt+940==0、vt+200 非空时：以 this+8900 为振幅 rand 双向抖动坐标，按档位取 this+8892+4*8840 颜色、this+8904<<24 作透明度，经 ·sub_491DE0 纯 STENCIL 变体加绘。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFB50(int this, int nArg2, int nArg3, int nArg4, float fArg5)  // 函数: 通道 0 抖动加绘（8840 档位配色 + 8900 振幅）
{
  int result; // eax
  int fld_22C4; // ebx  | +0x22C4 → 抖动振幅（0x5CFB50：2*rand()%本槽 − 本槽 的双向抖动）（CNGuardBlock）
  int nRand; // edi
  int fld_22C42; // ebx  | +0x22C4 → 抖动振幅（0x5CFB50：2*rand()%本槽 − 本槽 的双向抖动）（CNGuardBlock）
  int nRand2; // eax
  int dword_79C0B02; // [esp-24h] [ebp-2Ch]
  int v12; // [esp-1Ch] [ebp-24h]
  int fld_2288; // [esp-Ch] [ebp-14h]  | +0x2288 → 相位/档位槽（0x5CFB50：!=2 才加绘，并按 +4*本槽 取色档）（CNGuardBlock）
  int fld_22C8; // [esp-8h] [ebp-10h]  | +0x22C8 → 渲染透明度源（0x5CFB50：本槽 <<24 | 0xFFFFFF 作 ARGB）（CNGuardBlock）

  result = sub_5CF520((int *)this, nArg2, nArg3, nArg4, fArg5);  // 调 法术层绘制（通道 1 附着 / 通道 0 闪烁）
  if ( (uint8_t)nArg2 != 1 && *(uint32_t *)(this + 8840) != 2 && *(uint32_t *)(this + 8700) == -1 )  // this+8840 相位/档位槽
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 940))(this);  // 调用虚函数（虚表槽 +940）
    if ( (uint8_t)result == 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      if ( result != 0 )  // 若结果非 0（成功）
      {
        fld_22C4 = *(uint32_t *)(this + 8900);  // this+8900 抖动振幅
        nRand = 2 * (rand() % fld_22C4) - fld_22C4;  // 调 以 16 位种子状态递推并返回 15 位结果
        fld_22C42 = *(uint32_t *)(this + 8900);  // this+8900 抖动振幅
        nRand2 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
        fld_22C8 = (*(uint8_t *)(this + 8904) << 24) | 0xFFFFFF;  // this+8904 渲染透明度源
        fld_2288 = *(uint32_t *)(this + 4 * *(uint32_t *)(this + 8840) + 8892);  // this+4 宿主对象
        v12 = nArg4 + 2 * (nRand2 % fld_22C42) - fld_22C42;
        dword_79C0B02 = dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        return sub_491DE0(dword_79C0B02, nArg3 + nRand, v12, fArg5, 2, 1, fld_2288, fld_22C8);  // 调 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
      }
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CFC30 sub_5CFC30 —— 吟唱进度转发（2175==-1 门）
//   this+2175（法杖/吟唱状态槽）等于 -1 时转 ·sub_4D7C60 吟唱进度/收尾表现（进度条三段绘制 + EndofCasting.ani 分支），否则直返。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFC30(uint32_t *this)  // 函数: 吟唱进度转发（2175==-1 门）
{
  int result; // eax

  if ( *(this + 2175) == -1 )  // this+8700〔uPhase8700(推断)〕
    return sub_4D7C60();  // 【吟唱条/进度渲染（EndofCasting.ani 分支）】
  return result;
}



// AI 字段访问（this+8840）
// ------------------------------------------------------------
// 0x5CFC40 sub_5CFC40 —— 伤害门（8840 相位 × 攻方档位 +12）
//   先取 ·sub_5CF4C0 伤害过滤门结果；8840==0 且攻方档位块 vt+348(nArg3)+12 为 0 时伤害清零并判 1，8840==1 时同条件（+12==1）再清零 —— 阿莫尔相位决定伤害吸收【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFC40(int this, int *pDwArg2, int nArg3)  // 函数: 伤害门（8840 相位 × 攻方档位 +12）
{
  int v5; // edx
  int result; // eax
  int v7; // [esp+18h] [ebp+Ch]

  v7 = sub_5CF4C0((uint8_t *)this, pDwArg2, nArg3);  // 调 伤害过滤门（姿态 8 + 2203 子槽）
  if ( *(uint32_t *)(this + 8840) == 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12) == 0 )  // 调用虚函数（虚表槽 +348）
  {
    *pDwArg2 = 0;
    v7 = 1;
  }
  if ( *(uint32_t *)(this + 8840) != 1 )  // this+8840 相位/档位槽
    return v7;
  v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12);  // 调用虚函数（虚表槽 +348）
  result = 1;
  if ( v5 != 1 )
    return v7;
  *pDwArg2 = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CFCC0 sub_5CFCC0 —— 相位参数块重置（8841 校验字 + 8860/8864=1.0f）
//   8840 清零后经 ·sub_41A590(8841, nArg2) 重建 +8841 参数块（随机密钥 + 双校验字），8856 与 8868..8936 段归零，8860/8864 两槽写 0x3F800000（1.0f）并返回。
// ------------------------------------------------------------
int /*fastcall*/ sub_5CFCC0(int pArg1, int nArg2)  // 函数: 相位参数块重置（8841 校验字 + 8860/8864=1.0f）
{
  *(uint8_t *)(pArg1 + 8840) = 0;  // pArg1+8840〔uPhase8840(推断)〕
  sub_41A590(pArg1 + 8841, nArg2, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(uint32_t *)(pArg1 + 8856) = 0;
  *(uint32_t *)(pArg1 + 8868) = 0;  // pArg1+8868〔bGate8868(推断)〕
  *(uint32_t *)(pArg1 + 8872) = 0;  // pArg1+8872〔uDur8872(推断)〕
  *(uint32_t *)(pArg1 + 8876) = 0;  // pArg1+8876〔uPhase8876(推断)〕
  *(uint32_t *)(pArg1 + 8880) = 0;  // pArg1+8880〔uPhase8880(推断)〕
  *(uint32_t *)(pArg1 + 8884) = 0;  // pArg1+8884〔uPhase8884(推断)〕
  *(uint32_t *)(pArg1 + 8896) = 0;  // pArg1+8896〔uGlowAmp8896(推断)〕
  *(uint32_t *)(pArg1 + 8900) = 0;  // pArg1+8900〔uGlowPeriod8900(推断)〕
  *(uint32_t *)(pArg1 + 8904) = 0;  // pArg1+8904〔bGlowAlpha8904(推断)〕
  *(uint32_t *)(pArg1 + 8908) = 0;  // pArg1+8908〔uPhase8908(推断)〕
  *(uint32_t *)(pArg1 + 8912) = 0;  // pArg1+8912〔uPhase8912(推断)〕
  *(uint32_t *)(pArg1 + 8916) = 0;  // pArg1+8916〔uPhase8916(推断)〕
  *(uint32_t *)(pArg1 + 8920) = 0;  // pArg1+8920〔uPhase8920(推断)〕
  *(uint32_t *)(pArg1 + 8924) = 0;  // pArg1+8924〔uPhase8924(推断)〕
  *(uint32_t *)(pArg1 + 8928) = 0;  // pArg1+8928〔uPhase8928(推断)〕
  *(uint32_t *)(pArg1 + 8932) = 0;  // pArg1+8932〔nComboSeg8932(推断)〕
  *(uint32_t *)(pArg1 + 8936) = 0;  // pArg1+8936〔bPhase8936(推断)〕
  *(uint32_t *)(pArg1 + 8860) = 1065353216;  // 常量 1.0f
  *(uint32_t *)(pArg1 + 8864) = 1065353216;  // 常量 1.0f
  return 1065353216;  // 常量 1.0f
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CFD60 sub_5CFD60 —— 派生对象槽释放（2214）
//   取 this+2214 派生对象槽，非空则虚表槽 0 带参 1 释放后归零 —— 与 ·sub_5CF0A0（槽 2166）同构。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFD60(uint32_t *this)  // 函数: 派生对象槽释放（2214）
{
  int (/*thiscall*/ ***fld_e2214)(uint32_t, int); // ecx
  int result; // eax

  fld_e2214 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2214);
  if ( fld_e2214 != nullptr )  // 若 fld_e2214 有效（非空）
    result = (**fld_e2214)(fld_e2214, 1);  // 调 fld_e2214 的虚函数（vt+0）
  *(this + 2214) = 0;
  return result;
}



// AI 字段访问（this+8840）
// ------------------------------------------------------------
// 0x5CFD80 sub_5CFD80 —— 变速应用（档位倍率 + 位移 ±20 + 火焰特效）
//   随 8840 档位：≤1 时 2215 倍率置 1.0f，否则 1.0 + 0.01*2226*(档位-1)；Block（增速）时档位 2 把本体 +40 抬升 20，减速时档位 1 下移 20。
//   再 vt+700 应用、·sub_53F6A0 卸载旧附属光环；8840!=0 时 new 140B 经 ·sub_64BBF0(this+2227..2229) 挂火焰动画对象。
//   最后按 this+2230 千分比符号（Block ±1）叠加到参数块 +830/+858（·sub_41A5E0/·sub_41A590）并 vt+676 应用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFD80(uint8_t *this, void *Block)  // 函数: 变速应用（档位倍率 + 位移 ±20 + 火焰特效）
{
  uint8_t fld_e8840; // al
  int pThis_28; // eax
  int pThis_8B3; // eax
  double v6; // st7
  unsigned int pThis_2A0; // edi
  int v8; // edx
  unsigned int pThis_2A02; // edi
  int v10; // edx
  int v12; // [esp+8h] [ebp-10h]
  float Blocka; // [esp+20h] [ebp+8h]
  int Blockb; // [esp+20h] [ebp+8h]

  fld_e8840 = *(this + 8840);  // this+8840 相位/档位槽
  if ( fld_e8840 <= 1u )
    *((uint32_t *)this + 2215) = 1065353216;  // this+8860 = 1.0f
  else
    *((float *)this + 2215) = (double)(*((uint32_t *)this + 2226) * (fld_e8840 - 1)) * 0.0099999998 + 1.0;  // this+8904〔bGlowAlpha8904(推断)〕
  if ( (uint8_t)Block != 0 )
  {
    if ( fld_e8840 != 2 )
      goto LABEL_10;
    pThis_28 = *((uint32_t *)this + 40) + 20;  // this+40 物品状态附属标志
  }
  else
  {
    if ( fld_e8840 != 1 )
      goto LABEL_10;
    pThis_28 = *((uint32_t *)this + 40) - 20;  // this+40 物品状态附属标志
  }
  *((uint32_t *)this + 40) = pThis_28;  // this+40 物品状态附属标志
LABEL_10:
  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
  sub_53F6A0(this);  // 调 收尾路径
  if ( *(this + 8840) != 0 )  // this+8840 相位/档位槽
  {
    if ( operator new(0x8Cu) != nullptr )  // operator new 分配 140 字节
      pThis_8B3 = sub_64BBF0(*((uint32_t *)this + 2227), *((uint32_t *)this + 2228), *((uint32_t *)this + 2229));  // 调 火焰动画查询 2（5910D0）
    else
      pThis_8B3 = 0;
    (*(void (/*thiscall*/ **)(int, uint8_t *, uint8_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pThis_8B3 + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
      pThis_8B3,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  if ( (uint8_t)Block != 0 )
    v6 = 1.0;
  else
    v6 = -1.0;
  Blocka = (double)*((int *)this + 2230) * v6 * 0.0099999998;  // this+8920〔uPhase8920〕
  pThis_2A0 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + Blocka;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pThis_2A0, v8, v12);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  pThis_2A02 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 858;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  *(float *)&Blockb = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) + Blocka;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pThis_2A02, v10, Blockb);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
}



// AI 字段访问（this+8841）
// ------------------------------------------------------------
// 0x5CFF20 sub_5CFF20 —— 参数块 +8841 自增 + 受击通知
//   读 this+8841 参数块当前值（·sub_41A5E0）加 1 后经 ·sub_41A590 回写（重建校验字），再转 ·sub_4D4A80 受方命中通知 —— 命中计数/累积槽【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFF20(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 参数块 +8841 自增 + 受击通知
{
  unsigned int pThis_2289; // edi
  int pThis_22892; // eax
  int v7; // edx

  pThis_2289 = (unsigned int)this + 8841;
  pThis_22892 = sub_41A5E0((unsigned int)this + 8841);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pThis_2289, v7, pThis_22892 + 1);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  return sub_4D4A80(this, nArg2, nArg3, nArg4);  // 调 受击后观察者 vt+516（六回调第 6 号，研究 §1.1/§1.2）
}



// 复合门（this+200/8840/8892..8900）
// ------------------------------------------------------------
// 0x5CFF60 sub_5CFF60 —— 呼吸发光加绘（sin 周期 → α 通道）
//   先转 ·sub_5CF520；主通道、8840 相位非 0、vt+940==0 且 vt+200 非空时按 6.283184（2π）周期取样 sin：振幅 this+8896/2、中心 this+8892、频率分母 8900/档位。
//   正弦值落在 (0,255) 时作 α 合成 ((α<<24)|0xFFFFFF) 交 ·sub_491DE0 纯 STENCIL 变体加绘蓝色（基色 0xFF0000FF）呼吸光。
// ------------------------------------------------------------
void /*thiscall*/ sub_5CFF60(int this, int nArg2, int nArg3, int nArg4, float fArg5)  // 函数: 呼吸发光加绘（sin 周期 → α 通道）
{
  long double dwNow; // st7
  int dword_79C0B02; // [esp-20h] [ebp-2Ch]

  sub_5CF520((int *)this, nArg2, nArg3, nArg4, fArg5);  // 调 法术层绘制（通道 1 附着 / 通道 0 闪烁）
  if ( (uint8_t)nArg2 != 0
    && *(uint8_t *)(this + 8840) != 0  // this+8840 相位/档位槽
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 940))(this) == 0  // 调用虚函数（虚表槽 +940）
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) != 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  {
    dwNow = sin(  // 调 正弦
           (double)timeGetTime()  // 调 取系统毫秒时刻
         * 6.283184
         / (double)(*(uint32_t *)(this + 8900) / (int)*(uint8_t *)(this + 8840)))  // this+8900 呼吸发光周期分母
       * (double)(*(uint32_t *)(this + 8896) / 2)  // this+8896 呼吸发光振幅
       + (double)*(int *)(this + 8892);  // this+8892 呼吸发光中心值
    if ( dwNow > 0.0 && dwNow < 255.0 )  // 若 dwNow > 0 与/或 dwNow < 255
    {
      dword_79C0B02 = dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      sub_491DE0(dword_79C0B02, nArg3, nArg4, fArg5, 2, 1, -16776961, ((uint8_t)(uint64_t)dwNow << 24) | 0xFFFFFF);  // 调 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
    }
  }
}


