// ============================================================
// 【40JP逆向源代码工程】src/game/creature/missing_monster.cpp
// 模块: 0x590000-0x5E0000 补漏
// 来源: work/dump 素材  区块: 0x598430-0x5D7CD1 §A 0x59 补漏
// 层级: L2 转写 + 证据标注层（函数体保持 Hex-Rays 忠实输出，零改动；
//       本文件由主代理自研流水线补注：每函数的字符串证据/调用链清单，
//       纯二进制事实提取（tools/annotate_evidence.py），零臆造）
// 函数数: 122
// ============================================================


#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============================================================
// §A 0x59 补漏
// ============================================================
// 0x598430 sub_598430
// 哥布林系（0x59 区块）三参转发桩：唯一语句转调 ·0x4DA3B0(int,int,int)，
// 语义随被调方（该地址族为怪物通用三参入口）【推断】
// ------------------------------------------------------------
// 调: sub_598430 sub_4DA3B0
int /*stdcall*/ sub_598430(int nArg1, int nArg2, int nArg3)  // 实现：调: sub_598430 sub_4DA3B0
{
  return sub_4DA3B0(nArg1, nArg2, nArg3);  // 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
}



// ------------------------------------------------------------
// ============================================================
// §B 0x5A 补漏
// ============================================================
// 0x5A36E0 sub_5A36E0
// 牛头兽子类单字段写入：this+8604 = 600。600 与同族函数写 30/50 的量级不同，
// 疑为毫秒/帧计数的一次性冷却量【推断】；供 ·0x5A36F0 冲撞起始族复用
// ------------------------------------------------------------
// 调: sub_5A36E0
void /*thiscall*/ sub_5A36E0(uint32_t *this)  // 实现：调: sub_5A36E0
{
  *(this + 2151) = 600;  // this+8604〔bAI8604(推断)〕
}



// ------------------------------------------------------------
// 0x5A5160 sub_5A5160
// 沙乌塔系（0x5A51xx）单参转发桩：转调 ·0x498F60(this)，本函数自身零逻辑；
// attributes: thunk = 链接器生成的跳板
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5A5160 sub_498F60
int /*thiscall*/ sub_5A5160(uint32_t *this)  // 实现：调: sub_5A5160 sub_498F60
{
  return sub_498F60(this);  // 取条件字节
}



// ------------------------------------------------------------
// 0x5AA350 sub_5AA350
// 控制器对象释放：取 this+8604 存的控制器指针，经其虚表首槽（vtable[0]，参数 1）
// 调用自毁，然后把槽清 0；无对象时不调用但仍清槽——典型"可选挂件销毁"模式，
// 与 tau_golem.cpp ·0x5A3510 装载的控制器对象（this+8604）配对
// ------------------------------------------------------------
// 调: sub_5AA350
int /*thiscall*/ sub_5AA350(uint32_t *this)  // 实现：调: sub_5AA350
{
  int (/*thiscall*/ ***fld_e2151)(uint32_t, int); // ecx
  int result; // eax

  fld_e2151 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2151);  // this+8604〔bAI8604(推断)〕
  if ( fld_e2151 != nullptr )  // 若 fld_e2151 有效（非空）
    result = (**fld_e2151)(fld_e2151, 1);  // 调 fld_e2151 的虚函数（vt+0）
  *(this + 2151) = 0;  // this+8604〔bAI8604(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x5AA420 sub_5AA420
// 飞龙姿态/朝向随机化步进：两次 rand()%2 掷点决定朝向档（nRand23 ∈ {0,1}）
// 与姿态档（v22 ∈ {2,3}）；据此用速度槽（vt+672(3)+816 与 +830 两轴乘积）
// 分别以 0.5 与 0.175 系数折算两组 vt+876 位移参数；再经 vt+896（姿态）、
// vt+148、vt+144（帧组）写入；末尾给关联对象（this+224 槽）置 +124 标志与
// +12 槽 30.0f（位型 1106247680 = 0x41F00000）【推断：随机拍翅巡航参数面】
// 注： `nRand != 4` 恒真（nRand=rand()%2 ∈{0,1}），是编译产物/反编译残留，
//      不改变任何实际执行路径
// ------------------------------------------------------------
// 调: sub_5AA420 sub_41A5E0
int /*thiscall*/ sub_5AA420(uint32_t *this)  // 实现：调: sub_5AA420 sub_41A5E0
{
  int nRand; // edi
  int nRand2; // eax
  int nRand23; // ebx
  int v5; // edi
  int v6; // edi
  uint64_t v7; // rax
  int v8; // edi
  int v9; // edi
  uint64_t v10; // rax
  int result; // eax
  int *fld_e28; // esi
  int pObj; // ecx
  bool v14; // zf
  int nRand22; // [esp+Ch] [ebp-18h]
  int v16; // [esp+Ch] [ebp-18h]
  float v17; // [esp+10h] [ebp-14h]
  int v18; // [esp+14h] [ebp-10h]
  int v19; // [esp+14h] [ebp-10h]
  float v20; // [esp+18h] [ebp-Ch]
  int v21; // [esp+1Ch] [ebp-8h]
  int v22; // [esp+20h] [ebp-4h]

  nRand = rand() % 2;  // nRand = 调 rand
  nRand2 = rand() % 2;  // nRand2 = 调 rand
  nRand22 = nRand2;
  if ( nRand != 0 )  // 若 nRand 非 0
  {
    if ( nRand == 1 )  // 若 nRand == 1
      nRand23 = 0;
    else  // 否则分支
      nRand23 = nRand2;
  }
  else  // 否则分支
  {
    nRand23 = 1;  // 朝向档 ∈ {0,1}
  }
  if ( nRand2 != 0 )  // 若 nRand2 非 0
  {
    if ( nRand2 == 1 )  // 若 nRand2 == 1
      v22 = 2;  // 姿态档 2
  }
  else  // 否则分支
  {
    v22 = 3;  // 姿态档 3
  }
  if ( nRand != 4 )  // 若 nRand != 4
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    v21 = sub_41A5E0(v5 + 816);  // 速度槽 X 轴
    v20 = COERCE_FLOAT(sub_41A5E0(v5 + 830));  // 速度槽 Y 轴
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    v18 = sub_41A5E0(v6 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v7 = (uint64_t)((double)(int)(uint64_t)((double)v18 * COERCE_FLOAT(sub_41A5E0(v6 + 830))) * 0.5);  // 两轴乘积 ×0.5
    (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      this,
      HIDWORD(v7),  // 调 取 64 位值高 32 位
      0,
      v7,
      (uint64_t)((double)(int)(uint64_t)((double)v21 * v20) * 0.5),  // 第二轴同系数 0.5
      0,
      0,
      0);
    nRand2 = nRand22;
  }
  if ( nRand2 != 4 )  // 若 nRand2 != 4
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    v16 = sub_41A5E0(v8 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v17 = COERCE_FLOAT(sub_41A5E0(v8 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    v19 = sub_41A5E0(v9 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v10 = (uint64_t)((double)(int)(uint64_t)((double)v19 * COERCE_FLOAT(sub_41A5E0(v9 + 830))) * 0.175);  // 第二组系数 0.175 = 0.35/2
    (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      this,
      HIDWORD(v10),  // 调 取 64 位值高 32 位
      1,
      v10,
      (uint64_t)((double)(int)(uint64_t)((double)v16 * v17) * 0.175),
      0,
      0,
      0);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, nRand23, v22);  // vt+896(朝向档, 姿态档)
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 148))(this, nRand23);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 144))(this, nRand23);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
  fld_e28 = (int *)*(this + 28);  // this+112〔pHostComp112〕
  pObj = *fld_e28;
  v14 = *fld_e28 == 0;
  *((uint8_t *)fld_e28 + 124) = 1;
  if ( !v14 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj);  // 调虚槽 +308：是否本地玩家
    if ( (uint8_t)result != 0 )
    {
      result = 1106247680;  // 浮点常量 30.0f
      if ( fld_e28[3] != 1106247680 )  // 1106247680 = 0x41F00000 = 30.0f（+12 槽速度上限）
      {
        fld_e28[3] = 1106247680;  // 浮点常量 30.0f
        *((uint8_t *)fld_e28 + 196) = 1;  // +196 脏标记（触发重算/重绘）
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AA750 sub_5AA750
// 飞龙待机行为掷点（双时钟门）：本尊时钟 this+8720 到期（≥this+8744）即刻过门，
// 或次时钟 this+8748 到期且 pszArg2==1（外部触发）时可重入；门内再判可行动
// （vt+308）后掷 rand()%100：≥50 从候选取值表（this+8708..8712，元素版）
// 随机挑一个写入 this+324（朝向档），否则固定写 135；末了清 this+8733/8734
// 两门、本尊时钟置 10 秒冷却、this+8761/8762 两门清零、次时钟置 3 秒冷却
// ------------------------------------------------------------
// 调: sub_5AA750 sub_699000 sub_698F90
char /*thiscall*/ sub_5AA750(int *this, char pszArg2)  // 实现：调: sub_5AA750 sub_699000 sub_698F90
{
  int pThis_884; // ebx
  int fld_e2186; // edi
  int fld_e2193; // edi
  int v6; // eax
  int fld_e2177; // eax
  unsigned int fld_e2178; // edi

  pThis_884 = (int)(this + 2180);  // this+8720〔pSegThrTbl8720(推断)〕
  fld_e2186 = *(this + 2186);  // this+8744〔nCountdown8744(推断)〕
  if ( sub_699000((int)(this + 2180)) >= fld_e2186  // 【clock_now(clk)】
    || (fld_e2193 = *(this + 2193), (v6 = sub_699000((int)(this + 2187))) >= fld_e2193) && pszArg2 == 1 )  // 【clock_now(clk)】
  {
    LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
    if ( (uint8_t)v6 != 0 )
    {
      if ( rand() % 100 >= 50 )  // 调 取伪随机数
      {
        fld_e2177 = *(this + 2177);  // this+8708〔pCandTbl8708(推断)〕
        if ( fld_e2177 != 0 )  // 若 fld_e2177 非 0
          fld_e2178 = (*(this + 2178) - fld_e2177) >> 2;  // this+8712〔nCandTblEnd8712(推断)〕
        else  // 否则分支
          fld_e2178 = 0;
        *(this + 81) = *(uint32_t *)(*(this + 2177) + 4 * (rand() % fld_e2178));  // this+324〔nRandPick324〕
      }
      else  // 否则分支
      {
        *(this + 81) = 135;  // this+324〔nRandPick324〕
      }
      *(uint8_t *)(pThis_884 + 13) = 0;
      *(uint8_t *)(pThis_884 + 14) = 0;
      sub_698F90(pThis_884, 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      *((uint8_t *)this + 8761) = 0;  // this+8761〔bAI8761〕
      *((uint8_t *)this + 8762) = 0;  // this+8762〔bAI8762〕
      LOBYTE(v6) = sub_698F90((int)(this + 2187), 3000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x5AABB0 sub_5AABB0
// 飞龙"高空扑咬"落地收势步进（与 ·0x5AB180 同构，差异：高度门用 >=130 而非 ==0，
// 且高度达标时先把本尊移到 vt+124(130) 处；vt+8701 门与 ·0x5AB180 的 vt+8700
// 是不同标志）——相位 1 且动画播完 → vt+604(0) 收招、可行动则 setState 0；
// 相位 0 且高度 >=130：vt+108 移位到 130 高度后配置帧表项 this+6216+52
// （vt+4926A0 与 vt+196），相位写 1、·0x424120(父+132, 2, 300) 收尾
// ------------------------------------------------------------
// 调: sub_5AABB0 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
int /*thiscall*/ sub_5AABB0(int *this)  // 实现：调: sub_5AABB0 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int fld_e1554; // edi
  int v7; // edx
  int v8; // eax

  result = *(this + 2153);  // this+8612〔uAI8612(推断)〕
  if ( result != 0 )  // 若结果非 0（成功）
  {
    if ( result == 1 )  // 若 result == 1
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
      if ( *(uint8_t *)(result + 170) != 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
        result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
        if ( (uint8_t)result != 0 )
          return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      }
    }
  }
  else  // 否则分支
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    if ( result >= 130 )  // 若 result >= 130
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, 130);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v4);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(int *, int))(v3 + 108))(this, v5);  // 虚函数调用 槽+108：槽（10 行）
      *(uint32_t *)(*(this + 28) + 24) = 0;  // this+112〔pHostComp112〕
      *(uint32_t *)(*(this + 28) + 36) = 0;  // this+112〔pHostComp112〕
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      if ( *((uint8_t *)this + 8701) == 0 )
      {
        *(uint32_t *)(sub_4924C0(0) + 48) = 500;  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
        fld_e1554 = *(uint32_t *)(*(this + 1554) + 52);  // fld_e1554 = 读 this+1554
        sub_4910E0(fld_e1554);  // 帧时刻推进（返回 1 表示时刻发生位移）
        sub_493A60(fld_e1554, *(uint32_t *)(fld_e1554 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 52));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 52));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      }
      v7 = *this;
      *(this + 2153) = 1;  // this+8612〔uAI8612(推断)〕
      v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 80))(this);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      return sub_424120(*(uint32_t **)(v8 + 132), 2, 300);  // 标签入口（解析器 sub_502F00 调用，全库 36 调用者）。
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AAED0 sub_5AAED0
// 飞龙"龙吟"（FLYDRAGON_CRY）动作启动：把 this+324 当前朝向档抄入 this+8620，
// vt+184 动作号（==4 时改记 5）写 this+8628、vt+188 写 this+8632、this+8616 清 0；
// 再按速度槽（vt+672(3)+816 × +830）以 1.5 倍写两组 vt+876 位移参数；
// 若场景挂载对象（this+224 槽，即 ·0x4924C0 族）可行动且其 +24 槽非 -600.0f
// （位型 -1005191168 = 0xC4160000）则改写为 -600.0f 并置 +196 标记（俯冲速度限）；
// 随后 ·0x495890(0,200) 状态推进、vt+196 选帧、·0x4926A0 帧游标复位、
// vt+344 写偏移 this+556+304；最后清 this+8700 相位并播报 FLYDRAGON_CRY
// ------------------------------------------------------------
// 证: "FLYDRAGON_CRY"
// 调: sub_5AAED0 sub_41A5E0 sub_495890 sub_4926A0
int /*thiscall*/ sub_5AAED0(uint32_t *this)  // 实现：调: sub_5AAED0 sub_41A5E0 sub_495890 sub_4926A0
{
  int v2; // edx
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edi
  int v7; // edi
  uint64_t v8; // rax
  uint32_t *fld_e28; // edi
  int v10; // eax
  int v11; // eax
  int v13; // [esp+Ch] [ebp-Ch]
  float v14; // [esp+10h] [ebp-8h]
  int v15; // [esp+14h] [ebp-4h]

  v2 = *this;
  *(this + 2155) = *(this + 81);  // this+8620〔uAI8620(推断)〕等 2 字段
  if ( (*(int (**)(void))(v2 + 184))() == 4 )  // 虚函数调用 槽+184：动画对象 z 倾斜转状态码
    v3 = 5;
  else  // 否则分支
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this);  // 调虚槽 +184：动画对象 z 倾斜转状态码
  v4 = *this;
  *(this + 2157) = v3;  // this+8628〔nPoolTime(推断)〕
  *(this + 2158) = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 188))(this);  // 虚函数调用 槽+188：动画对象 z 倾斜转状态码
  v5 = *this;
  *(this + 2154) = 0;  // this+8616〔uAI8616(推断)〕
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 672))(this, 3);  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
  v15 = sub_41A5E0(v6 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v14 = COERCE_FLOAT(sub_41A5E0(v6 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v13 = sub_41A5E0(v7 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v8 = (uint64_t)((double)(int)(uint64_t)((double)v13 * COERCE_FLOAT(sub_41A5E0(v7 + 830))) * 1.5);  // crypt4byte 解密校验（·0x41A590 逆运算）
  (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    this,
    HIDWORD(v8),  // 调 取 64 位值高 32 位
    0,
    v8,
    (uint64_t)((double)(int)(uint64_t)((double)v15 * v14) * 1.5),
    0,
    0,
    0);
  fld_e28 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  if ( *fld_e28 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0 && fld_e28[6] != -1005191168 )  // 复合条件判定（与/或）
  {
    fld_e28[6] = -1005191168;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 200);  // 模式选择式方位设置（1/2/其他 三分支）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  sub_4926A0(v10);  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 304);  // 调虚槽 +344：取坐标三元组
  v11 = *this;
  *((uint8_t *)this + 8700) = 0;  // this+8700〔uPhase8700(推断)〕
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v11 + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
           this,
           "FLYDRAGON_CRY",  // 资源/动画 TAG FLYDRAGON_CRY
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5AB3E0 sub_5AB3E0
// 飞龙"低空扑咬"进场门（相位 18）：需 this+8804 相位 ≠18、有宿主 this+7252、
// 大状态 vt+840 ≠8 三前置齐备；门内先 ·0x5AA190(this,200,1)/(300,1) 做两段
// 横向距离校验，任一不过则相位写 -1 并 vt+208 写帧表项 this+6216+16（放弃扑咬）；
// 两段全过且时钟 this+8776 冷却满（·0x41C6E0==1）时正式起手：·0x5AA0A0(this,18)
// 写相位、this+8604 记当前时刻（·0x699000）、this+8789/8790 两门清零、
// 时钟 this+8776 置 10 秒冷却
// ------------------------------------------------------------
// 调: sub_5AB3E0 sub_5AA190 sub_41C6E0 sub_5AA0A0 sub_699000
char /*thiscall*/ sub_5AB3E0(uint32_t *this)  // 实现：调: sub_5AB3E0 sub_5AA190 sub_41C6E0 sub_5AA0A0 sub_699000
{
  int pTbl6216; // eax  | +0x1848 → 【推断】资源/帧游标表〔+12 帧对象；5AA830 复位装载〕（CNDrakeLooseSerimalion；va=005AA830）
  int v4; // edx

  if ( *(this + 2201) != 18 && *(this + 1813) != 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 8 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    if ( sub_5AA190(this, 200, 1) != 0 || sub_5AA190(this, 300, 1) != 1 )  // 关联对象横向距离校验（this+7252 与 x 差 <= nArg2）
    {
      pTbl6216 = *(this + 1554);  // this+6216〔pTbl6216(推断)〕
      v4 = *this;
      *(this + 2201) = -1;  // this+8804〔相位〕
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 208))(this, *(uint32_t *)(pTbl6216 + 16));  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
    }
    else if ( (uint8_t)sub_41C6E0(this + 2194) == 1 )  // 超时判定（clock_now(clk) >= this+24 截止时刻）
    {
      sub_5AA0A0(this, 18);  // 同构 ·0x5A8FF0 简化版（包 29/2 仅写对象三元组 + nArg2）
      *(this + 2151) = sub_699000((int)(this + 9));  // clock_now(clk)
      *((uint8_t *)this + 8789) = 0;
      *((uint8_t *)this + 8790) = 0;
      sub_698F90((int)(this + 2194), 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      return 0;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5AB600 sub_5AB600
// 飞龙速度槽调节（增/减双向）：nArg3==0 时速度槽（vt+672(0)+830）−0.3 并 vt+676
// 应用，另把攻击系数面 this+7620+64 置 0；nArg3==2 且 nArg2==0 时 +0.3 并应用
// （增向不写系数面），nArg3 其余值直接返回 nArg3-2
// ------------------------------------------------------------
// 调: sub_5AB600 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5AB600(uint32_t *this, int nArg2, int nArg3)  // 实现：调: sub_5AB600 sub_41A5E0 sub_41A590
{
  int result; // eax
  unsigned int v5; // edi
  int v6; // edx
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+14h] [ebp+Ch]
  int v10; // [esp+14h] [ebp+Ch]

  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )  // 若 nArg3 == 2
    {
      result = nArg2;
      if ( nArg2 == 0 )  // 若 nArg2 为 0
      {
        v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
        *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v5)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
        sub_41A590(v5, v6, v9);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
      }
    }
  }
  else  // 否则分支
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v7)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v7, v8, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    *(uint8_t *)(*(this + 1905) + 64) = 0;  // this+7620〔pStatusPanel(推断)〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AB9B0 sub_5AB9B0
// 飞龙总步进（每帧复合 AI 入口）：先 ·0x4E1780 基类步进与 vt+1264 子过程；
// 距上次振翅（this+8624 + this+8696 冷却窗）已过则 vt+352 触发飞行姿态并戳时刻；
// 随后按"不可行动 或 大状态≠0 或 高度<140"（即空中/失控分支）分派：
//   大状态 14（低空扑咬）→ 段 2 且动画帧走完调 ·0x5AAED0（龙吟），否则 ·0x5AB180；
//   大状态 16（高空扑咬）→ 段 2 且帧走完调 ·0x5AAA20，否则 ·0x5AABB0；
//   大状态 0（地面）→ 动画对表 this+6164 时按难度播报 B_FLYDRAGON_FLAP 或
//   FLYDRAGON_FLAP（this+8692 防重），并当关联对象 +36 槽 0 且 +24 槽非 0 时
//   ·0x494F20(2,0.0) 复位；段 2 双条件齐则 ·0x5AA010 高度驱动；
// 末段 this+8608 门开着且动画结束帧到、·0x5AA340 返回对象 == this+6164 时
// vt+344/vt+196/·0x4926A0 做收招复位
// ------------------------------------------------------------
// 证: "B_FLYDRAGON_FLAP" | "FLYDRAGON_FLAP"
// 调: sub_5AB9B0 sub_4E1780 sub_699000 sub_5AAED0 sub_5AB180
char /*thiscall*/ sub_5AB9B0(int *this)  // 实现：调: sub_5AB9B0 sub_4E1780 sub_699000 sub_5AAED0 sub_5AB180
{
  int v1; // eax
  int v2; // eax
  int v4; // eax
  uint32_t *fld_e1554; // edi
  uint32_t *fld_e15542; // edi
  int pHostComp112; // ecx  | +0x0070 → 宿主对象指针（IRDActiveObject·基类；va=004D6970）
  uint32_t *fld_e15543; // edi
  int pFrameObj6164; // [esp+0h] [ebp-Ch]  | +0x1814 → 【推断】帧对象 A〔5AA830：大状态 0 且取向(vt+188)==4 时 sub_4926A0 复位并经 vt（CNFlyDragon；va=005AA830）

  sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  (*(void (/*thiscall*/ **)(int *))(*this + 1264))(this);  // 调虚槽 +1264
  if ( *(this + 2156) + *(this + 2174) < (unsigned int)sub_699000((int)(this + 9)) )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 352))(this);  // 调虚槽 +352：命中列表双链表清空
    *(this + 2156) = sub_699000((int)(this + 9));  // clock_now(clk)
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 0  // 调虚槽 +308：是否本地玩家
    || (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 0  // 调虚槽 +840：大状态 getter（this+6556）
    || (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) < 140 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
    {
      if ( *(this + 2154) == 2 )  // this+8616〔uAI8616(推断)〕
      {
        fld_e1554 = (uint32_t *)(*(this + 1554) + 16);  // this+6216〔pTbl6216(推断)〕
        if ( (*(int (/*fastcall*/ **)(int *))(*this + 200))(this) == *fld_e1554  // 调虚槽 +200：取动画对象
          && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) != 0 )  // 调虚槽 +200：取动画对象
        {
          sub_5AAED0(this);  // 飞龙「龙吟「（FLYDRAGON_CRY）动作启动：把 this+324 当前朝向档抄入
        }
      }
      else  // 否则分支
      {
        sub_5AB180(this);  // 飞龙「落地/振翅收势「步进（相位 this+8616 两态机）：相位 1 且动画播完（+
      }
    }
    else if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 16 )  // 调虚槽 +840：大状态 getter（this+6556）
    {
      if ( *(this + 2153) == 2 )  // this+8612〔uAI8612(推断)〕
      {
        fld_e15542 = (uint32_t *)(*(this + 1554) + 48);  // this+6216〔pTbl6216(推断)〕
        if ( (*(int (/*fastcall*/ **)(int *))(*this + 200))(this) == *fld_e15542  // 调虚槽 +200：取动画对象
          && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) != 0 )  // 调虚槽 +200：取动画对象
        {
          sub_5AAA20(this);
        }
      }
      else  // 否则分支
      {
        sub_5AABB0(this);
      }
    }
    else if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 0 )  // 调虚槽 +840：大状态 getter（this+6556）
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) == *(this + 1541) )  // 调虚槽 +200：取动画对象
      {
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) != 3 || *((uint8_t *)this + 8692) != 0 )  // 调虚槽 +200：取动画对象
        {
          if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 0 )  // 调虚槽 +200：取动画对象
            *((uint8_t *)this + 8692) = 0;  // this+8692〔防重〕
        }
        else  // 否则分支
        {
          if ( *(this + 1943) == 3 )  // this+7772〔nCounterState〕
            (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
              this,
              "B_FLYDRAGON_FLAP",  // 资源/动画 TAG B_FLYDRAGON_FLAP
              -1,
              0,
              0);
          else  // 否则分支
            (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
              this,
              "FLYDRAGON_FLAP",  // 资源/动画 TAG FLYDRAGON_FLAP
              -1,
              0,
              0);
          *((uint8_t *)this + 8692) = 1;  // this+8692〔防重〕
        }
      }
      pHostComp112 = *(this + 28);  // this+112〔pHostComp112〕
      if ( *(uint32_t *)(pHostComp112 + 36) == 0 && *(float *)(pHostComp112 + 24) != 0.0 )  // 复合条件判定（与/或）
        sub_494F20(2, 0.0);  // 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
    }
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 0 && *(this + 2154) == 2 && *(this + 2153) == 2 )  // 调虚槽 +840：大状态 getter（this+6556）
      sub_5AA010(this);  // 高度差驱动位移/攀爬（this+324 与 vt+128 高度槽之差）
    LOBYTE(v4) = *((uint8_t *)this + 8608);  // this+8608 骑乘/骑手槽
    if ( (uint8_t)v4 != 0 )
    {
      fld_e15543 = (uint32_t *)*(this + 1554);  // this+6216〔pTbl6216(推断)〕
      v4 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
      if ( v4 == *fld_e15543 )
      {
        v4 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
        if ( *(uint8_t *)(v4 + 170) != 0 )
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));  // 调虚槽 +344：取坐标三元组
          v1 = *this;
          pFrameObj6164 = *(this + 1541);  // this+6164〔pFrameObj6164〕
          *((uint8_t *)this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
          (*(void (/*thiscall*/ **)(int *, int))(v1 + 196))(this, pFrameObj6164);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
          v2 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
          LOBYTE(v4) = sub_4926A0(v2);  // 帧游标复位（+44 帧数组；递归子链 +204）
        }
      }
    }
  }
  else  // 否则分支
  {
    LOBYTE(v4) = (*(int (/*thiscall*/ **)(int *))(*this + 1256))(this);  // 调虚槽 +1256
  }
  return v4;
}



// ------------------------------------------------------------
// 0x5ABD90 sub_5ABD90
// 飞龙 vt+560 setState 拦截（大状态 8 门）：ArgList==8 且高度>80 且可行动时，
// 把状态改写作 0（取消进态）并从二元素取值表（this+8708）按 rand()%100<50 掷点
// 挑朝向写 this+324、宿主 this+7252 清 0；随后转发基类 ·0x5AB800 落态；
// 若大状态 this+6556 == 8（已进态）则按 ·0x41A5E0(this+7028) 分型收尾：
//   非 0 型（起飞型）：vt+876 双组参数清零、·0x4926A0 复位帧游标 this+6216+32、
//   vt+204 写 100、this+8797/8798 门清零、时钟 this+8784 立即到期（冷却清零）；
//   0 型（着陆型）：vt+876 写高度参数 (700,700,-2000)；
// 两型共同收尾：vt+888(this,2,2,1000,1000) 写双参、vt+152(4) 取帧号经 vt+896 落定
// ------------------------------------------------------------
// 调: sub_5ABD90 sub_5AB800 sub_41A5E0 sub_4926A0 sub_698F90
int /*thiscall*/ sub_5ABD90(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：调: sub_5ABD90 sub_5AB800 sub_41A5E0 sub_4926A0 sub_698F90
{
  char v5; // di
  int result; // eax
  int pThis_6DD; // eax
  int v9; // edx
  int v10; // edi
  int v11; // eax

  v5 = ArgList;
  if ( ArgList == 8  // 若 ArgList == 8
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) > 80  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    v5 = 0;
    *(this + 81) = *(uint32_t *)(*(this + 2177) + 4 * (rand() % 100 < 50));  // this+324〔nRandPick324〕
    *(this + 1813) = 0;  // this+7252〔pTarget7252〕
  }
  result = sub_5AB800(v5, fArg3, nArg4, nArg5);  // result = 调 sub_5AB800 返回值
  if ( *(this + 1639) == 8 )  // this+6556〔大状态ID〕
  {
    pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v9 = *this;
    if ( pThis_6DD != 0 )  // 若 pThis_6DD 非 0
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v9 + 876))(  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      sub_4926A0(*(uint32_t *)(*(this + 1554) + 32));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
        this,
        100,
        *(uint32_t *)(*(this + 1554) + 32),  // this+6216〔pTbl6216(推断)〕
        0,
        0,
        0,
        0);
      *((uint8_t *)this + 8797) = 0;
      *((uint8_t *)this + 8798) = 0;
      sub_698F90((int)(this + 2196), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    else  // 否则分支
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(v9 + 876))(this, 0, 700, 700, 0, -2000, 1);  // 虚函数调用 槽+876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        1,
        0,
        0,
        0,
        0,
        0);
    }
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
    v10 = *this;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);  // 调虚槽 +152：效果通道 3
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v10 + 896))(this, v11);  // 虚函数调用 槽+896：默认虚槽桩（11 行 return）
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AC110 sub_5AC110
// 飞龙扑咬子相位机步进：·0x5ABC20 算出新相位写 this+8804 并返回；相位落 18
// （低空扑咬起手）时追加 ·0x5AB4A0 起手脚；返回相位值供父级分派
// ------------------------------------------------------------
// 调: sub_5AC110 sub_5ABC20 sub_5AB4A0
int /*thiscall*/ sub_5AC110(uint32_t *this)  // 实现：调: sub_5AC110 sub_5ABC20 sub_5AB4A0
{
  int v2; // eax

  v2 = sub_5ABC20();  // v2 = 调 sub_5ABC20 返回值
  *(this + 2201) = v2;
  if ( v2 == 18 )  // 若 v2 == 18
    sub_5AB4A0(this);  // 飞龙「撕咬「（FLYDRAGON_BITE）起手：vt+344 写偏移（this+556
  return *(this + 2201);  // 返回成员 this+8804
}



// ------------------------------------------------------------
// 0x5AFCF0 sub_5AFCF0
// 龙人（Dragonman）行为字相位机：·0x4E0120 基类前置后按行为字 this+7148 分发——
//   0 登场：vt+1284 出场动作；
//   4 待机：无宿主 this+7252 时写 13，有宿主时 10% 概率写 5（出击）；
//   5 出击：无宿主直接落 13；有宿主 30% 概率落 4；
//   13/14/15 追敌：有宿主则回写 4
// ------------------------------------------------------------
// 调: sub_5AFCF0 sub_4E0120
int /*thiscall*/ sub_5AFCF0(int *this)  // 实现：调: sub_5AFCF0 sub_4E0120
{
  int result; // eax
  int nRand2; // eax
  int v4; // et2
  int nRand; // eax
  int v6; // et2

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调虚槽 +1284
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_4;
      nRand = rand();  // nRand = 调 rand
      v6 = nRand % 100;
      result = nRand / 100;
      if ( v6 < 10 )  // 若 v6 < 10
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
      {
        nRand2 = rand();  // nRand2 = 调 rand
        v4 = nRand2 % 100;
        result = nRand2 / 100;
        if ( v4 < 30 )  // 若 v4 < 30
          goto LABEL_11;
      }
      else  // 否则分支
      {
LABEL_4:  // 标签 LABEL_4（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      }
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_11:  // 标签 LABEL_11（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AFE80 sub_5AFE80
// 龙人总步进（每帧复合 AI 入口）：·0x4E1780 基类步进后三段分派——
//   1) 可行动 & 大状态 15 & this+8614==1 & 目标 this+8616 与其动作非空时，
//      若目标动画帧走完则 setState 16（追击转攻击）；
//   2) 大状态 8 且 ·0x41A5E0(this+7028)==1 调 ·0x5AFAB0；
//   3) 大状态 0 且动画对象非空时：动画对象对表 this+6164 或 this+6216[0] 时，
//      按 vt+184/vt+152 相等与否在两者间切换 vt+196 帧组并 ·0x4926A0 复位游标；
// 随后大状态 0 下按动作对 (vt+184, vt+188) 是否 ==(4,4) 切换幻影循环播报
// DRAGONMAN_ILLUSION_LOOP（this+8613 防重，退出时 vt+216 写 12）；
// 末段大状态 8 时按 ·0x41A5E0(this+7028) 分型播报：型 0 且动画段 >=3 播 DRGM_ATK1
// （this+8612 防重）、型 2 且段 >=4 播 DRGM_ATK2
// ------------------------------------------------------------
// 证: "DRAGONMAN_ILLUSION_LOOP" | "DRGM_ATK2" | "DRGM_ATK1"
// 调: sub_5AFE80 sub_4E1780 sub_41A5E0 sub_5AFAB0 sub_4926A0
char /*usercall*/ sub_5AFE80@<al>(int *pDwArg1@<ecx>, int nArg2@<edi>)  // 实现：调: sub_5AFE80 sub_4E1780 sub_41A5E0 sub_5AFAB0 sub_4926A0
{
  int pObj; // ecx
  uint32_t *v4; // edi
  int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // eax

  sub_4E1780(pDwArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0  // 调虚槽 +308：是否本地玩家
    && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 15  // 调虚槽 +840：大状态 getter（this+6556）
    && *((uint8_t *)pDwArg1 + 8614) == 1
    && (pObj = pDwArg1[2154]) != 0
    && pDwArg1[2159] != 0 )
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 200))(pObj) + 170) != 0 )  // 调虚槽 +200：取动画对象
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*pDwArg1 + 560))(pDwArg1, 16, 0, 2, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    sub_5AFAB0(pDwArg1);  // 龙人静态待机语音播报
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 0 && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) != 0 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) == pDwArg1[1541]  // 调虚槽 +200：取动画对象
      || (v4 = (uint32_t *)pDwArg1[1554], (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) == *v4) )  // 调虚槽 +200：取动画对象
    {
      v5 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 184))(pDwArg1, nArg2);  // 调虚槽 +184：动画对象 z 倾斜转状态码
      v6 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调虚槽 +152：效果通道 3
      v7 = *pDwArg1;
      if ( v6 == v5 )  // 若 v6 == v5
      {
        (*(void (/*thiscall*/ **)(int *, int))(v7 + 196))(pDwArg1, pDwArg1[1541]);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
        v8 = *(uint32_t *)pDwArg1[1554];
      }
      else  // 否则分支
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(v7 + 196))(pDwArg1, *(uint32_t *)pDwArg1[1554]);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
        v8 = pDwArg1[1541];  // v8 = 取 pDwArg1[1541]
      }
      sub_4926A0(v8);  // 帧游标复位（+44 帧数组；递归子链 +204）
    }
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 0 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 184))(pDwArg1) == 4 && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 188))(pDwArg1) == 4 )  // 调虚槽 +184：动画对象 z 倾斜转状态码
    {
      if ( *((uint8_t *)pDwArg1 + 8613) == 1 )
      {
        v9 = *pDwArg1;
        *((uint8_t *)pDwArg1 + 8613) = 0;
        (*(void (/*thiscall*/ **)(int *, int))(v9 + 216))(pDwArg1, 12);  // 虚函数调用 槽+216：音效 TAG 查询
      }
    }
    else if ( *((uint8_t *)pDwArg1 + 8613) == 0 )
    {
      v10 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8613) = 1;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v10 + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        pDwArg1,
        "DRAGONMAN_ILLUSION_LOOP",  // 资源/动画 TAG DRAGONMAN_ILLUSION_LOOP
        12,
        0,
        0);
    }
  }
  v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( v11 == 8 )  // 若 v11 == 8
  {
    v12 = sub_41A5E0((unsigned int)(pDwArg1 + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( v12 != 0 )  // 若 v12 非 0
    {
      v11 = v12 - 2;
      if ( v11 == 0 )  // 若 v11 为 0
      {
        v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调虚槽 +200：取动画对象
        if ( *(int *)(v11 + 148) >= 4 )
        {
          LOBYTE(v11) = *((uint8_t *)pDwArg1 + 8612);  // 调 取 16 位值低 8 位
          if ( (uint8_t)v11 == 0 )
          {
            LOBYTE(v11) = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                            pDwArg1,
                            "DRGM_ATK2",  // 资源/动画 TAG DRGM_ATK2
                            -1,
                            0,
                            0);
            *((uint8_t *)pDwArg1 + 8612) = 1;
          }
        }
      }
    }
    else  // 否则分支
    {
      v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调虚槽 +200：取动画对象
      if ( *(int *)(v11 + 148) >= 3 )
      {
        LOBYTE(v11) = *((uint8_t *)pDwArg1 + 8612);  // 调 取 16 位值低 8 位
        if ( (uint8_t)v11 == 0 )
        {
          LOBYTE(v11) = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                          pDwArg1,
                          "DRGM_ATK1",  // 资源/动画 TAG DRGM_ATK1
                          -1,
                          0,
                          0);
          *((uint8_t *)pDwArg1 + 8612) = 1;
        }
      }
    }
  }
  return v11;
}



// ------------------------------------------------------------
// ============================================================
// §C 0x5B 补漏(含空骨鱼反击)
// ============================================================
// 0x5B1CD0 sub_5B1CD0
// 齐格（ZIEG）激光双播报起手：清 this+8621/8622/8623 三相位字节后，
// 先以静态调用形式播 ZIEG_LASER_READY_LOOP（参数 45567 疑为静态声源/通道号
// 【推断】），再经本尊 vt+212 播 ZIEG_CAST_LASER
// ------------------------------------------------------------
// 证: "ZIEG_LASER_READY_LOOP" | "ZIEG_CAST_LASER"
// 调: sub_5B1CD0
int /*thiscall*/ sub_5B1CD0(uint8_t *this)  // 实现：调: sub_5B1CD0
{
  int v2; // eax

  v2 = *(uint32_t *)this;
  *(this + 8621) = 0;
  *(this + 8622) = 0;  // this+8622 【推断】循环音锁存
  *(this + 8623) = 0;
  (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(v2 + 212))("ZIEG_LASER_READY_LOOP", 45567, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
  return (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
           this,
           "ZIEG_CAST_LASER",  // 资源/动画 TAG ZIEG_CAST_LASER
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5B4A00 sub_5B4A00
// 齐格火种判定：取对象 vt+340 返回的形态/状态码，等于 260 / 263 / 264 任一
// 则返回 true（三个码为该 Boss 的"可点燃"形态位，属硬编码白名单）【推断】
// ------------------------------------------------------------
// 调: sub_5B4A00
bool /*stdcall*/ sub_5B4A00(int nArg1)  // 实现：调: sub_5B4A00
{
  return *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 260  // 调虚槽 +340：三元组基址（+284，vt+340）
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 263  // 调虚槽 +340：三元组基址（+284，vt+340）
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 264;  // 调虚槽 +340：三元组基址（+284，vt+340）
}



// ------------------------------------------------------------
// 0x5B4CE0 sub_5B4CE0
// 齐格出场收尾：·0x4D9760 观察者广播收尾 → vt+1284 出场动作 → this+8656 槽清 0、
// this+8632 字节清 0，返回 0
// ------------------------------------------------------------
// 调: sub_5B4CE0 sub_4D9760
int /*thiscall*/ sub_5B4CE0(uint32_t *this)  // 实现：调: sub_5B4CE0 sub_4D9760
{
  sub_4D9760();  // 观察者广播后条件收尾
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);  // 调虚槽 +1284
  *(this + 2164) = 0;  // this+8656〔uPair8656(推断)〕
  *((uint8_t *)this + 8632) = 0;  // this+8632〔字节清〕
  return 0;
}



// ------------------------------------------------------------
// 0x5B4ED0 sub_5B4ED0
// 齐格激光/火种发射点解算：目标 this+8612（关联对象）分两族——
//   · 该对象 vt+40(obj,273) 命中（273 型，火种/可点燃体）：按其 vt+1032 子形态
//     1/0/其余三档分别在本尊朝向（vt+152 非 0 为左）下把 X 偏移 −20 / −5 / 0，
//     Y 恒 +1，Z 取 +60 或 +75（不同高度）；
//   · 否则（非 273 型）再看 vt+40(obj,529) 命中且 ·0x5B4A00 形态白名单通过时，
//     更细地按朝向做 ±11 偏移、Z 取 +60；否则退回目标原始坐标 + Y+1 + Z(含 vt+192 叠加)
// 三个出参 pArg2/pArg3/pArg4 = 发射点 X/Y/Z【推断：多段判定点表】
// ------------------------------------------------------------
// 调: sub_5B4ED0 sub_5B4A00 sub_41A5E0
int /*thiscall*/ sub_5B4ED0(int *this, float *pArg2, float *pArg3, float *pArg4)  // 实现：调: sub_5B4ED0 sub_5B4A00 sub_41A5E0
{
  int fld_e21524; // edi
  int v6; // eax
  int fld_e21525; // ecx
  int v8; // eax
  double fld_e21522; // st7
  int v10; // eax
  int fld_e21526; // ecx
  int v12; // eax
  int v13; // eax
  int fld_e21527; // ecx
  int v15; // eax
  int v16; // eax
  int fld_e21528; // ecx
  int v18; // eax
  int fld_e2152; // ecx
  int v20; // eax
  int fld_e21523; // edi
  int result; // eax
  int v23; // [esp+14h] [ebp+8h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2152) + 40))(*(this + 2152), 273) == 0 )  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2152) + 40))(*(this + 2152), 529) != 0  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      && sub_5B4A00(*(this + 2152)) )  // this+8608〔uAI8608(推断)〕
    {
      v18 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
      fld_e2152 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
      if ( v18 != 0 )  // 若 v18 非 0
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2152 + 120))(fld_e2152) - 11;  // 调虚槽 +120：动画对象
      else  // 否则分支
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2152 + 120))(fld_e2152) + 11;  // 调虚槽 +120：动画对象
      *pArg2 = (float)v20;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 124))(*(this + 2152)) + 1);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      fld_e21522 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 128))(*(this + 2152)) + 60);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    }
    else  // 否则分支
    {
      *pArg2 = (float)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 120))(*(this + 2152));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 124))(*(this + 2152)) + 1);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      fld_e21523 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
      v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21523 + 128))(fld_e21523);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      fld_e21522 = (double)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21523 + 192))(fld_e21523) + v23);  // 调虚槽 +192
    }
    goto LABEL_28;
  }
  fld_e21524 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21524 + 1032))(fld_e21524) == 1 )  // 调虚槽 +1032
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
    fld_e21525 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
    if ( v6 != 0 )  // 若 v6 非 0
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21525 + 120))(fld_e21525) - 20;  // 调虚槽 +120：动画对象
    else  // 否则分支
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21525 + 120))(fld_e21525) + 20;  // 调虚槽 +120：动画对象
  }
  else  // 否则分支
  {
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21524 + 1032))(fld_e21524) == 0 )  // 调虚槽 +1032
    {
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
      fld_e21526 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
      if ( v10 != 0 )  // 若 v10 非 0
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21526 + 120))(fld_e21526) - 5;  // 调虚槽 +120：动画对象
      else  // 否则分支
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21526 + 120))(fld_e21526) + 5;  // 调虚槽 +120：动画对象
      *pArg2 = (float)v12;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 124))(*(this + 2152)) + 1);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      fld_e21522 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 128))(*(this + 2152)) + 75);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
      goto LABEL_28;
    }
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21524 + 1032))(fld_e21524) == 2 )  // 调虚槽 +1032
    {
      v13 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
      fld_e21527 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
      if ( v13 != 0 )  // 若 v13 非 0
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21527 + 120))(fld_e21527) - 7;  // 调虚槽 +120：动画对象
      else  // 否则分支
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21527 + 120))(fld_e21527) + 7;  // 调虚槽 +120：动画对象
      *pArg2 = (float)v15;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 124))(*(this + 2152)) + 1);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      fld_e21522 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 128))(*(this + 2152)) + 100);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
      goto LABEL_28;
    }
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21524 + 1032))(fld_e21524) != 3 )  // 调虚槽 +1032
      goto LABEL_29;
    v16 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
    fld_e21528 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
    if ( v16 != 0 )  // 若 v16 非 0
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21528 + 120))(fld_e21528) - 10;  // 调虚槽 +120：动画对象
    else  // 否则分支
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21528 + 120))(fld_e21528) + 10;  // 调虚槽 +120：动画对象
  }
  *pArg2 = (float)v8;
  *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 124))(*(this + 2152)) + 1);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  fld_e21522 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 128))(*(this + 2152)) + 70);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
LABEL_28:  // 标签 LABEL_28（跳转合流点）
  *pArg4 = fld_e21522;
LABEL_29:  // 标签 LABEL_29（跳转合流点）
  result = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
  if ( result == 6 )  // 若 result == 6
    *pArg4 = *pArg4 * 0.5 + *pArg4;
  return result;
}



// ------------------------------------------------------------
// 0x5B57E0 sub_5B57E0
// 齐格大状态 8 的"当前动画段是否踩在该分型的目标表项上"判定：四道前置全过
// （可行动 & rand()%100<30 & 目标 vt+348 返回结构 +12 槽为 0【推断：目标未架招/
// 未无敌】& 大状态==8）后，按 ·0x41A5E0(this+7028) 分型取动画对象表项比较——
// 型 1/4 比 this+6216+8、型 6 比 this+6216+24、型 3 比 this+6200+12、
// 型 5 比 this+6216+20；相等则 true（用于段击发门）
// ------------------------------------------------------------
// 调: sub_5B57E0 sub_41A5E0
bool /*thiscall*/ sub_5B57E0(uint32_t *this, int nArg2)  // 实现：调: sub_5B57E0 sub_41A5E0
{
  uint32_t *fld_e1550; // edi
  bool result; // al
  uint32_t *fld_e1554; // edi
  uint32_t *fld_e15542; // edi

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 0  // 调虚槽 +308：是否本地玩家
    || rand() % 100 >= 30  // 调 取伪随机数
    || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0  // 调虚槽 +348：取坐标对象
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 8 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    return false;
  }
  switch ( sub_41A5E0((unsigned int)(this + 1757)) )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      fld_e1554 = (uint32_t *)(*(this + 1554) + 8);  // this+6216〔pTbl6216(推断)〕
      goto LABEL_10;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      fld_e1550 = (uint32_t *)(*(this + 1550) + 12);  // this+6200〔pTbl6200〕
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) == *fld_e1550;  // 调虚槽 +200：取动画对象
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      fld_e15542 = (uint32_t *)(*(this + 1554) + 20);  // this+6216〔pTbl6216(推断)〕
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) == *fld_e15542;  // 调虚槽 +200：取动画对象
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      fld_e1554 = (uint32_t *)(*(this + 1554) + 24);  // this+6216〔pTbl6216(推断)〕
LABEL_10:  // 标签 LABEL_10（跳转合流点）
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) == *fld_e1554;  // 调虚槽 +200：取动画对象
      break;  // 跳出循环/分支
    default:  // 默认分支
      return false;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B5DC0 sub_5B5DC0
// 齐格瞬移落位：先 vt+136/vt+132 双轴可站立校验（本尊当前 X/Y 处），
// 任一不可站且关联对象 this+8612 非空时，把本尊位置（vt+112）改写到该对象
// 坐标偏置（vt+128 高度 +40 再取 X 链）；随后 vt+196 选帧组 this+6216+4、
// vt+876 双组参数写 (200,200) / 归零、vt+888(0,0,1000,1000)、
// vt+152(4) 取帧号经 ·0x432E50 换算后 vt+896 落定、·0x495890(2,0) 与
// ·0x4A0550(10) 状态推进、this+8605 门清零
// ------------------------------------------------------------
// 调: sub_5B5DC0 sub_432E50 sub_495890 sub_4A0550
int /*thiscall*/ sub_5B5DC0(uint32_t *this)  // 实现：调: sub_5B5DC0 sub_432E50 sub_495890 sub_4A0550
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int fld_e2152; // eax
  int fld_e21522; // edi
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
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v2 + 136))(this, v4) == 0  // 虚函数调用 槽+136：槽（10 行）
    || (v5 = *this,
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this),  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v5 + 132))(this, v6) == 0) )  // 虚函数调用 槽+132：受击事件槽（钉刺王变体，23 行）
  {
    fld_e2152 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
    if ( fld_e2152 != 0 )  // 若 fld_e2152 非 0
    {
      fld_e21522 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
      v9 = *this;
      v10 = (*(int (**)(void))(*(uint32_t *)fld_e2152 + 128))();  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21522 + 124))(fld_e21522, v10 + 40);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21522 + 120))(fld_e21522, v11);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 112))(this, v12);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 200, 200, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  v13 = *this;
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);  // 调虚槽 +152：效果通道 3
  v15 = sub_432E50(v14);  // 关系码对调映射
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v13 + 896))(this, v15);  // 虚函数调用 槽+896：默认虚槽桩（11 行 return）
  sub_495890(2, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  result = sub_4A0550(10);  // result = 调 sub_4A0550 返回值
  *((uint8_t *)this + 8605) = 0;  // this+8605〔门清零〕
  return result;
}



// ------------------------------------------------------------
// 0x5B6000 sub_5B6000
// 齐格增益/减益面翻转（四项位取反）：先 vt[288](this, this+8656 参) 与
// vt[276](this, 5)，再把 vt[260] 返回对象的 +8 字节清 0；随后把攻击系数面
// this+7620 的 +0 / +32 / +64 / +96 四个字节各自"==0 取反"翻转
// （典型的三速+一伤四档互斥开关）【推断】
// ------------------------------------------------------------
// 调: sub_5B6000
char /*thiscall*/ sub_5B6000(uint8_t **this)  // 函数定义: 起手并由 vt+472(0
{
  int fld_e1905; // esi
  char result; // al

  (*((void (/*thiscall*/ **)(uint8_t **, uint32_t))*this + 288))(this, *(this + 2164));  // this+288 主人绑定对象
  (*((void (/*thiscall*/ **)(uint8_t **, int))*this + 276))(this, 5);  // this+276〔pMapEntry〕
  *(uint8_t *)((*((int (/*thiscall*/ **)(uint8_t **))*this + 260))(this) + 8) = 0;  // this+260〔nQuad4〕
  **(this + 1905) = **(this + 1905) == 0;  // this+7620〔pStatusPanel(推断)〕
  (*(this + 1905))[32] = (*(this + 1905))[32] == 0;  // this+7620〔pStatusPanel(推断)〕
  (*(this + 1905))[64] = (*(this + 1905))[64] == 0;  // this+7620〔pStatusPanel(推断)〕
  fld_e1905 = (int)*(this + 1905);  // this+7620〔pStatusPanel(推断)〕
  result = *(uint8_t *)(fld_e1905 + 96);
  *(uint8_t *)(fld_e1905 + 96) = result == 0;
  return result;
}



// ------------------------------------------------------------
// 0x5B6180 sub_5B6180
// 齐格攻击参数面整块清零（this+7568 写 2 变体）：7531..7558 逐槽 + 7564..7596 清零，
// this+7564 段号槽写 2，nArg3==2 取 nArg2 做 nArg32；nArg32==0 时 this+7596 写 50
// 且 this+7620+4 系数项自加加倍（×2）
// ------------------------------------------------------------
// 调: sub_5B6180
int /*thiscall*/ sub_5B6180(int this, int nArg2, int nArg3)  // 实现：调: sub_5B6180
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558 【推断】攻击参数面字节槽
  *(uint8_t *)(this + 7557) = 0;  // this+7557 【推断】攻击面门字节
  *(uint8_t *)(this + 7556) = 0;  // this+7556 【推断】攻击面模式字节
  *(uint8_t *)(this + 7534) = 0;  // this+7534 内嵌配置块 +14 字节
  *(uint8_t *)(this + 7533) = 0;  // this+7533 内嵌配置块 +13 字节
  *(uint8_t *)(this + 7532) = 0;  // this+7532 内嵌配置块 +12 字节
  *(uint8_t *)(this + 7531) = 0;  // this+7531 内嵌配置块 +11 字节
  *(uint32_t *)(this + 7535) = 0;  // this+7535 内嵌配置块 +15 字节
  *(uint32_t *)(this + 7539) = 0;  // this+7539 配置块 17 字节循环搬运区起点
  *(uint32_t *)(this + 7543) = 0;  // this+7543 【推断】攻击参数面槽
  *(uint32_t *)(this + 7547) = 0;  // this+7547 【推断】攻击参数面槽
  *(uint32_t *)(this + 7551) = 0;  // this+7551 【推断】攻击参数面槽
  *(uint8_t *)(this + 7555) = 0;  // this+7555 【推断】攻击参数面字节槽
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;  // this+7572 【推断】模式 2 档
  *(uint32_t *)(this + 7568) = 0;  // this+7568 【推断】激活/模式槽
  *(uint32_t *)(this + 7564) = 0;  // this+7564 【推断】形态/模式槽
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580 【推断】攻击面门字节
  *(uint32_t *)(this + 7576) = 0;  // this+7576 相位槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 【推断】段号横向偏置
  *(uint32_t *)(this + 7568) = 2;  // this+7568 【推断】激活/模式槽
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    nArg32 = nArg2;
  if ( nArg32 == 0 )  // 若 nArg32 为 0
  {
    *(uint32_t *)(this + 7596) = 50;  // this+7596 【推断】段号横向偏置
    *(float *)(*(uint32_t *)(this + 7620) + 4) = *(float *)(*(uint32_t *)(this + 7620) + 4)  // this+7620 【推断】属性/速度面板对象
                                             + *(float *)(*(uint32_t *)(this + 7620) + 4);  // this+7620 【推断】属性/速度面板对象
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B62E0 sub_5B62E0
// 齐格攻击系数面减半（this+7534 清 0 变体）：nArg3==2 时 this+7534 字节清 0
// （形态门复位）；nArg3==0 时 this+7564 段号槽清 0、this+7596 清 0 且
// this+7620+4 系数项自乘 0.5
// ------------------------------------------------------------
// 调: sub_5B62E0
int /*thiscall*/ sub_5B62E0(int this, int nArg2, int nArg3)  // 实现：调: sub_5B62E0
{
  int result; // eax

  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )  // 若 nArg3 == 2
      *(uint8_t *)(this + 7534) = 0;  // this+7534 内嵌配置块 +14 字节
  }
  else  // 否则分支
  {
    result = *(uint32_t *)(this + 7620) + 160;  // result = 读 this+7620
    *(uint32_t *)(this + 7568) = 0;  // this+7568 【推断】激活/模式槽
    *(uint32_t *)(this + 7596) = 0;  // this+7596 【推断】段号横向偏置
    *(float *)(result + 4) = *(float *)(result + 4) * 0.5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5BBD70 sub_5BBD70
// 空骨鱼（BoneFish）反击触发判定：可行动 & 大状态 0 & 有宿主 this+7252 &
// 高度 ≥ this+8600 门后，与宿主 Y 距 <30、X 距 <90（两轴硬编码门），
// 再掷 rand()%300 <15（5% 概率）则 setState 14（反击/架招入态）
// ------------------------------------------------------------
// 调: sub_5BBD70
int /*thiscall*/ sub_5BBD70(int *this)  // 实现：调: sub_5BBD70
{
  int result; // eax
  int pTarget7252; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int pTarget7252_; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int nRand; // eax
  int v6; // et2

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result == 0 )  // 若 result 为 0
    {
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        if ( result >= *(this + 2150) )  // this+8600〔uAI8600(推断)〕
        {
          pTarget7252 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));  // this+7252〔pTarget7252〕
          result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - pTarget7252);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          if ( result < 30 )  // 若 result < 30
          {
            pTarget7252_ = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
            result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - pTarget7252_);  // 调虚槽 +120：动画对象
            if ( result < 90 )  // 若 result < 90
            {
              nRand = rand();  // nRand = 调 rand
              v6 = nRand % 300;
              result = nRand / 300;
              if ( v6 < 15 )  // 若 v6 < 15
                return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
            }
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5BBF50 sub_5BBF50
// 空骨鱼包围/环绕（·0x4D54E0 基类步进后）：大状态 ==8 且 ·0x41A5E0(this+7028)==1
// 时，把 this+8700/+8704/+8716/+8720 四槽句柄交 ·0x4938F0 释放/挂接，再按
// this+8684 计数（>10 则取 20−n 折返）算出角度档 −10×n，存 this+8696 并把该角度
// （度→弧度 ×0.01745328888888889）经 ·0x492080 连写四次（四槽同步朝向）
// ------------------------------------------------------------
// 调: sub_5BBF50 sub_4D54E0 sub_41A5E0 sub_4938F0 sub_492080
int /*thiscall*/ sub_5BBF50(int *this)  // 实现：调: sub_5BBF50 sub_4D54E0 sub_41A5E0 sub_4938F0 sub_492080
{
  int result; // eax
  int fld_e2171; // ecx
  int fld_e21712; // eax
  float v5; // [esp+4h] [ebp-4h]

  sub_4D54E0(this);  // 调 受击包后：+1639==10 主状态镜像 且 +1953==0/+1954==15
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result == 8 )  // 若 result == 8
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )  // 若 result == 1
    {
      sub_4938F0(*(this + 2175));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      sub_4938F0(*(this + 2176));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      sub_4938F0(*(this + 2179));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      sub_4938F0(*(this + 2180));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      fld_e2171 = *(this + 2171);  // this+8684〔bGate8684(推断)〕
      if ( fld_e2171 <= 10 )  // 若 fld_e2171 <= 10
        fld_e21712 = *(this + 2171);  // this+8684〔bGate8684(推断)〕
      else  // 否则分支
        fld_e21712 = 20 - fld_e2171;
      *(this + 2174) = -10 * fld_e21712;  // this+8696〔uVec8696(推断)〕
      v5 = (double)(-10 * fld_e21712) * 0.01745328888888889;
      sub_492080(v5);  // 播放速率写入（+172 新速率；差值补偿累计时刻 +88）
      sub_492080(v5);  // 播放速率写入（+172 新速率；差值补偿累计时刻 +88）
      sub_492080(v5);  // 播放速率写入（+172 新速率；差值补偿累计时刻 +88）
      return sub_492080(v5);  // 播放速率写入（+172 新速率；差值补偿累计时刻 +88）
    }
  }
  return result;
}



// ------------------------------------------------------------
// ============================================================
// §D 0x5C 补漏
// ============================================================
// 0x5C3190 sub_5C3190
// 观察者广播转发桩（attributes: thunk）：唯一语句转调 ·0x4D9760(观察收尾广播)，
// 无参无返回值，纯跳板
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5C3190 sub_4D9760
int sub_5C3190()  // 实现：调: sub_5C3190 sub_4D9760
{
  return sub_4D9760();  // 观察者广播后条件收尾
}



// ------------------------------------------------------------
// 0x5C4F00 sub_5C4F00
// 某 Boss 攻击段切换例程（段计数递减 + 帧组重绑）：this+8648 段计数自减后写
// this+8600 = nArg2（新段号），vt+888(0,0,1000,1000) 写双参、·0x4926A0 与 vt+196
// 以 this+6216[0] 重设帧游标，并把表项邻接槽 this+6172/6176/6160 三值抄出；
// 攻击系数面 this+7620 的 +0/+32/+64 三字节清零（缓速标记复位），nArg2==1 时
// +96/+128 两字节置 1（强化标记）；vt+876 双组参数归零；末了速度槽
// （vt+672(3)+102）读出 +1.0 写回
// ------------------------------------------------------------
// 调: sub_5C4F00 sub_4926A0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C4F00(int *this, int nArg2)  // 实现：调: sub_5C4F00 sub_4926A0 sub_41A5E0 sub_41A590
{
  int v3; // edx
  uint32_t *fld_e1554; // eax
  unsigned int v5; // esi
  int v6; // edx
  int v8; // [esp+Ch] [ebp+8h]

  --*(this + 2162);  // this+8648〔uPhase8648(推断)〕
  v3 = *this;
  *(this + 2150) = nArg2;  // this+8600〔uAI8600(推断)〕
  (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int, int))(v3 + 888))(0, 0, 1000, 1000);  // 虚函数调用 槽+888：速率设置链: a2/a3 经 vt+976 换算 →…
  sub_4926A0(*(uint32_t *)*(this + 1554));  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  fld_e1554 = (uint32_t *)*(this + 1554);  // this+6216〔pTbl6216(推断)〕
  *(this + 1543) = fld_e1554[2];  // this+6172〔pAtkCtxA6172〕
  *(this + 1544) = fld_e1554[3];  // this+6176〔pAtkCtxB6176〕
  *(this + 1540) = fld_e1554[7];
  *(uint8_t *)*(this + 1905) = 0;  // this+7620〔pStatusPanel(推断)〕
  *(uint8_t *)(*(this + 1905) + 32) = 0;  // this+7620〔pStatusPanel(推断)〕
  *(uint8_t *)(*(this + 1905) + 64) = 0;  // this+7620〔pStatusPanel(推断)〕
  if ( *(this + 2150) == 1 )  // this+8600〔uAI8600(推断)〕
  {
    *(uint8_t *)(*(this + 1905) + 96) = 1;  // this+7620〔pStatusPanel(推断)〕
    *(uint8_t *)(*(this + 1905) + 128) = 1;  // this+7620〔pStatusPanel(推断)〕
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3) + 102;  // 调虚槽 +672：自身 HP
  *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v5)) + 1.0;  // crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(v5, v6, v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x5C51E0 sub_5C51E0
// Boss 攻击参数面整块重置（char* this，故下标按元素写）：7531..7555 逐字节 +
// 7535..7555 逐字 + 1891..1899 段号区共约 22 槽全清零；
// 之后三分支——nArg3==2 且 nArg2==0：this[1894] 写 1、this[1899] 写 50（满档）；
// nArg3==2 其余：this[1894] 写 1；nArg3==0：this[1895] 写 1、this[1899] 写 50，
// 系数面 this[1905]+32+4 项自加加倍（×2），速度槽（vt+672(0)+830）+1.0
// 经 ·0x41A590 写回并 vt+676 应用
// ------------------------------------------------------------
// 调: sub_5C51E0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C51E0(char *this, int nArg2, int nArg3)  // 实现：调: sub_5C51E0 sub_41A5E0 sub_41A590
{
  char *pThis_1D73; // ecx
  int result; // eax
  int pThis_771; // eax
  unsigned int pThis_2A0; // edi
  int v8; // edx
  int v9; // [esp+14h] [ebp+Ch]

  *(this + 7558) = 0;  // this+7558 【推断】攻击参数面字节槽
  *(this + 7557) = 0;  // this+7557 【推断】攻击面门字节
  *(this + 7556) = 0;  // this+7556 【推断】攻击面模式字节
  *(this + 7534) = 0;  // this+7534 内嵌配置块 +14 字节
  *(this + 7533) = 0;  // this+7533 内嵌配置块 +13 字节
  *(this + 7532) = 0;  // this+7532 内嵌配置块 +12 字节
  *(this + 7531) = 0;  // this+7531 内嵌配置块 +11 字节
  *(uint32_t *)(this + 7535) = 0;  // this+7535 内嵌配置块 +15 字节
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
  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )  // 若 nArg3 == 2
    {
      *((uint32_t *)this + 1894) = 1;  // this[1894] = 1
      if ( nArg2 == 0 )  // 若 nArg2 为 0
        *((uint32_t *)this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
    }
  }
  else  // 否则分支
  {
    pThis_771 = *((uint32_t *)this + 1905) + 32;  // this+7620〔pStatusPanel(推断)〕
    *((uint32_t *)this + 1895) = 1;  // this[1895] = 1
    *((uint32_t *)this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
    *(float *)(pThis_771 + 4) = *(float *)(pThis_771 + 4) + *(float *)(pThis_771 + 4);  // this+4 宿主对象
    pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 1.0;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, v8, v9);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C5450 sub_5C5450
// Boss 攻击参数面整块清零（负向档）：与 ·0x5C51E0 同为整面复位族（7531..7558 +
// 7564..7596 共 22 槽），但系数项写 −50 而非 +50；nArg3==2 且 nArg2==0：this+7564
// 写 1、this+7596 写 -50；nArg3==0：this+7564 写 1、this+7596 写 -50 且
// this+7620+36 系数项自加倍（×2）
// ------------------------------------------------------------
// 调: sub_5C5450
int /*thiscall*/ sub_5C5450(int this, int nArg2, int nArg3)  // 实现：调: sub_5C5450
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
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580 攻击面门字节
  *(uint32_t *)(this + 7576) = 0;  // this+7576 攻击参数面槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 段号横向偏置
  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    if ( nArg3 == 2 )  // 若 nArg3 == 2
    {
      *(uint32_t *)(this + 7564) = 1;  // this+7564 形态/模式槽
      if ( nArg2 == 0 )  // 若 nArg2 为 0
        *(uint32_t *)(this + 7596) = -50;  // this+7596 段号横向偏置
    }
  }
  else  // 否则分支
  {
    *(uint32_t *)(this + 7564) = 1;  // this+7564 形态/模式槽
    *(uint32_t *)(this + 7596) = -50;  // this+7596 段号横向偏置
    *(float *)(*(uint32_t *)(this + 7620) + 36) = *(float *)(*(uint32_t *)(this + 7620) + 36)  // this+7620 速度/属性参数对象
                                              + *(float *)(*(uint32_t *)(this + 7620) + 36);  // this+7620 速度/属性参数对象
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C55C0 sub_5C55C0
// Boss 攻击系数面降档（×0.5 双向变体）：nArg3==2 且 nArg2==0：this+7568 段号槽写 2、
// this+7596 写 50（满档标记）；nArg3==0：this+7568 写 1、this+7596 写 50，并把
// this+7620+36 系数项减半、this+7620+68 系数项也减半（两处独立 ×0.5）
// ------------------------------------------------------------
// 调: sub_5C55C0
int /*thiscall*/ sub_5C55C0(uint32_t *this, int nArg2, int nArg3)  // 实现：调: sub_5C55C0
{
  int result; // eax
  int pParamObj7620; // eax  | +0x1DC4 → 速度/属性参数对象（其 +4/+68/+100/+132 浮点被倍率改写）【推断】（CNRodinglo）
  double v5; // st7

  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )  // 若 nArg3 == 2
    {
      result = nArg2;
      *(this + 1892) = 2;  // this+7568〔uEnable7568(推断)〕
      if ( nArg2 == 0 )  // 若 nArg2 为 0
        *(this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
    }
  }
  else  // 否则分支
  {
    pParamObj7620 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    *(this + 1892) = 1;  // this+7568〔uEnable7568(推断)〕
    *(this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
    v5 = *(float *)(pParamObj7620 + 36) * 0.5;
    result = pParamObj7620 + 32;
    *(float *)(result + 4) = v5;
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.5;  // this+7620〔pStatusPanel(推断)〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C6330 sub_5C6330
// 命中回调类例程（nArg2 = 攻击方）：攻击方 vt+40(obj,17) 命中且 rand()%100 <5
// （5% 概率）且本尊可行动时，若双方 vt+152 朝向一致且攻击方仍为 17 型，
// 则 vt+192(this,4,...) 取参后经 vt+580 发射 48023 号（参数 10）反击弹
// ------------------------------------------------------------
// 调: sub_5C6330 sub_4DA3B0
int /*thiscall*/ sub_5C6330(int *this, int nArg2, int nArg3, int nArg4)  // 实现：调: sub_5C6330 sub_4DA3B0
{
  int v5; // ebx
  int v6; // ebx
  int v7; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && rand() % 100 < 5  // 调 取伪随机数
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 152))(nArg2);  // 调虚槽 +152：效果通道 3
    if ( v5 == (*(int (/*thiscall*/ **)(int *))(*this + 152))(this)  // 调虚槽 +152：效果通道 3
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      v6 = *this;
      v7 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 192))(this, 4, 0, 0, 0);  // 调虚槽 +192
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(v6 + 580))(  // 虚函数调用 槽+580：位置化动作发布（会话 3 定案：位置化动作）
        this,
        48023,
        10,
        0,
        0,
        0,
        0,
        v7 / 2);
    }
  }
  return sub_4DA3B0(nArg2, nArg3, nArg4);  // 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
}



// ------------------------------------------------------------
// 0x5C6560 sub_5C6560
// 目标筛型谓词：pArg2 非本尊且其 vt+340 形态/状态码 == 601 时为真
// （601 为巨人 Giant 族的充能弹幕/形态码，见 docs/91 会话日志）
// ------------------------------------------------------------
// 调: sub_5C6560
bool /*thiscall*/ sub_5C6560(void *this, void *pArg2)  // 实现：调: sub_5C6560
{
  return pArg2 != this && *(uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pArg2 + 340))(pArg2) == 601;  // 调虚槽 +340：三元组基址（+284，vt+340）
}



// ------------------------------------------------------------
// 0x5C65D0 sub_5C65D0
// 移动速度档微调：this+8744 速度上限槽写 5.0f（位型 1084227584 = 0x40A00000），
// 再取速度槽（vt+672(0)+466）按 pszArg2 符号 +5 / −5（·0x41A5E0 读、·0x41A590 写、
// vt+676 应用）——即开关型双向 ±5 速度步进
// ------------------------------------------------------------
// 调: sub_5C65D0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C65D0(uint32_t *this, char pszArg2)  // 实现：调: sub_5C65D0 sub_41A5E0 sub_41A590
{
  unsigned int v3; // edi
  int v4; // eax
  int v5; // edx

  *(this + 2186) = 1084227584;  // this+8744 = 5.0f
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 466;  // 调虚槽 +672：自身 HP
  if ( pszArg2 != 0 )  // 若 pszArg2 非 0
    v4 = sub_41A5E0(v3) + 5;  // crypt4byte 解密校验（·0x41A590 逆运算）
  else  // 否则分支
    v4 = sub_41A5E0(v3) - 5;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(v3, v5, v4);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
}



// ------------------------------------------------------------
// 0x5C6700 sub_5C6700
// Boss 攻击参数面整块清零（负向 + this+7537 置 1 变体）：与 ·0x5C5450 同族
// （7531..7558 逐槽 + 7564..7596 六槽清零），但把 this+7537 字节置 1（形态门），
// 且 nArg3==2 取 nArg2 做 nArg32，nArg32==0 时 this+7596 写 −50
// ------------------------------------------------------------
// 调: sub_5C6700
int /*thiscall*/ sub_5C6700(int this, int nArg2, int nArg3)  // 实现：调: sub_5C6700
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558 【推断】攻击参数面字节槽
  *(uint8_t *)(this + 7557) = 0;  // this+7557 【推断】攻击面门字节
  *(uint8_t *)(this + 7556) = 0;  // this+7556 【推断】攻击面模式字节
  *(uint8_t *)(this + 7534) = 0;  // this+7534 内嵌配置块 +14 字节
  *(uint8_t *)(this + 7533) = 0;  // this+7533 内嵌配置块 +13 字节
  *(uint8_t *)(this + 7532) = 0;  // this+7532 内嵌配置块 +12 字节
  *(uint8_t *)(this + 7531) = 0;  // this+7531 内嵌配置块 +11 字节
  *(uint32_t *)(this + 7535) = 0;  // this+7535 内嵌配置块 +15 字节
  *(uint32_t *)(this + 7539) = 0;  // this+7539 配置块 17 字节循环搬运区起点
  *(uint32_t *)(this + 7543) = 0;  // this+7543 【推断】攻击参数面槽
  *(uint32_t *)(this + 7547) = 0;  // this+7547 【推断】攻击参数面槽
  *(uint32_t *)(this + 7551) = 0;  // this+7551 【推断】攻击参数面槽
  *(uint8_t *)(this + 7555) = 0;  // this+7555 【推断】攻击参数面字节槽
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;  // this+7572 【推断】模式 2 档
  *(uint32_t *)(this + 7568) = 0;  // this+7568 【推断】激活/模式槽
  *(uint32_t *)(this + 7564) = 0;  // this+7564 【推断】形态/模式槽
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580 【推断】攻击面门字节
  *(uint32_t *)(this + 7576) = 0;  // this+7576 相位槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 【推断】段号横向偏置
  *(uint8_t *)(this + 7537) = 1;  // this+7537 内嵌配置块 +17 字节
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    nArg32 = nArg2;
  if ( nArg32 == 0 )  // 若 nArg32 为 0
    *(uint32_t *)(this + 7596) = -50;  // this+7596 【推断】段号横向偏置
  return result;
}



// ------------------------------------------------------------
// 0x5C6940 sub_5C6940
// 反击/反伤裁决入口（nArg2 = 攻击方）：·0x4E5AF0(nArg2,this) 判定命中成立
// 且攻击方为 17 型且可行动时，以 vt+760 附加伤害（参数 3、1092616192 = 10.0f、
// 参数 3、this 为源）——即把攻击方的这一击反弹；随后无条件转 ·0x4DB480
// 做通用伤害结算
// ------------------------------------------------------------
// 调: sub_5C6940 sub_4E5AF0 sub_4DB480
int /*thiscall*/ sub_5C6940(void *this, int nArg2, int nArg3, int nArg4)  // 实现：调: sub_5C6940 sub_4E5AF0 sub_4DB480
{
  if ( (uint8_t)sub_4E5AF0(nArg2, this) != 0  // 背击判定（研究 §3 定案：背击暴击加成 attackinfo+144）
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 308))(nArg2) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, void *, uint32_t))(*(uint32_t *)nArg2 + 760))(nArg2, 3, 1092616192, 3, this, 0);  // 调虚槽 +760：状态槽写入(17 槽异常状态)
  }
  return sub_4DB480(nArg2, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// ------------------------------------------------------------
// 0x5C6A90 sub_5C6A90
// 网络流写 uint16（this = 流对象）：向 缓冲基址 this[1] + 写偏移 this[2] 处写
// uArg2（2 字节小端），写偏移 +=2；若越界（> this[0] 即容量上限）调
// off_77F3FC(aCriticalError_40, 上限) 报致命错误（断言宏桩）
// ------------------------------------------------------------
// 调: sub_5C6A90
int /*thiscall*/ sub_5C6A90(int *this, int16_t uArg2)  // 函数定义: 网络流写 uint16
{
  int fld_e2; // esi
  int v3; // ecx
  int result; // eax

  *(uint16_t *)(*(this + 1) + *(this + 2)) = uArg2;  // this+4〔宿主对象〕等 2 字段
  fld_e2 = *(this + 2) + 2;  // this+8〔nSkillRec8(推断)〕
  *(this + 2) = fld_e2;  // this+8〔nSkillRec8(推断)〕
  v3 = *this;
  result = fld_e2;
  if ( fld_e2 > v3 )  // 若 fld_e2 > v3
    return off_77F3FC(aCriticalError_40, v3);  // 返回 调 off_77F3FC
  return result;
}



// ------------------------------------------------------------
// 0x5CBD40 sub_5CBD40
// CNMonsterFlower（巨型花怪）构造器：先把虚表指针写成 CNMonsterFlower::vftable
// （RTTI 直证类名），再转 ·0x4A50F0 做基类（CNMonster 族）构造
// ------------------------------------------------------------
// 调: sub_5CBD40 sub_4A50F0
int /*thiscall*/ sub_5CBD40(uint32_t *this)  // 实现：调: sub_5CBD40 sub_4A50F0
{
  *this = &CNMonsterFlower::`vftable';  // 写 vftable 指针（对象重定位/复位）
  return sub_4A50F0(this);  // 返回 调 sub_4A50F0 返回值
}



// ------------------------------------------------------------
// 0x5CF730 sub_5CF730
// 五参构造转发桩：原样转调 ·0x5CF520（同签名的真实现），本函数纯跳板
// ------------------------------------------------------------
// 调: sub_5CF730 sub_5CF520
int /*thiscall*/ sub_5CF730(int *this, int nArg2, int nArg3, int nArg4, float fArg5)  // 实现：调: sub_5CF730 sub_5CF520
{
  return sub_5CF520(this, nArg2, nArg3, nArg4, fArg5);  // 法术层绘制（通道 1 附着 / 通道 0 闪烁）
}



// ------------------------------------------------------------
// ============================================================
// §E 0x5D 补漏
// ============================================================
// 0x5D7730 sub_5D7730
// CNGuardBlock（守卫格挡体）构造器：先写虚表 CNGuardBlock::vftable（RTTI 直证），
// 再转 ·0x5D6F80 做基类构造
// ------------------------------------------------------------
// 调: sub_5D7730 sub_5D6F80
int /*thiscall*/ sub_5D7730(void ***this)  // 函数定义: 后按 pszArg2&1 释放
{
  *this = &CNGuardBlock::`vftable';  // 写 vftable 指针（对象重定位/复位）
  return sub_5D6F80(this);  // 守卫王族析构（CNKingGuard vftable + 特效槽释放 + 基析构）
}



// ------------------------------------------------------------
// 0x5DA8C0 sub_5DA8C0
// 单参转发桩（attributes: thunk）：转调 ·0x4B2270(this)
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5DA8C0 sub_4B2270
int /*thiscall*/ sub_5DA8C0(uint32_t *this)  // 实现：调: sub_5DA8C0 sub_4B2270
{
  return sub_4B2270(this);  // 部件特效时长汇总（18 槽）
}



// ------------------------------------------------------------
// 0x59E780 sub_59E780
// 无参转发桩（attributes: thunk）：转调 ·0x59E570()
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_59E780 sub_59E570
int sub_59E780()  // 实现：调: sub_59E780 sub_59E570
{
  return sub_59E570();  // 攻击触发门（同构 ·0x59D360 的门结构，差异：经 vt+1312 直接触发动作）
}



// ------------------------------------------------------------
// 0x5A4030 sub_5A4030
// 牛头系速度槽减向调节（弱化）：nArg3==0 时 this+7596 蓄力档清零，速度槽
// （vt+672(0)+830）读出 −0.3 经 ·0x41A590 写回并 vt+676 应用；nArg3 其余值原样返回
// ------------------------------------------------------------
// 调: sub_5A4030 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5A4030(uint32_t *this, int nArg2, int nArg3)  // 实现：调: sub_5A4030 sub_41A5E0 sub_41A590
{
  int result; // eax
  int v5; // eax
  unsigned int v6; // edi
  int v7; // edx
  int v8; // [esp+10h] [ebp+Ch]

  result = nArg3;
  if ( nArg3 == 0 )  // 若 nArg3 为 0
  {
    v5 = *this;
    *(this + 1899) = 0;  // this+7596〔nOffset7596(推断)〕
    v6 = (*(int (/*stdcall*/ **)(uint32_t))(v5 + 672))(0) + 830;  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v6)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v6, v7, v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  return result;
}



// ------------------------------------------------------------
// 0x5A5170 sub_5A5170
// 沙乌塔系三参转发桩（attributes: thunk，usercall：ecx/ebx/edi 三寄存器传参）：
// 转调 ·0x4DA1D0(uArg1, nArg2, nArg3)
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5A5170 sub_4DA1D0
int /*usercall*/ sub_5A5170@<eax>(uint32_t *uArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：调: sub_5A5170 sub_4DA1D0
{
  return sub_4DA1D0(uArg1, nArg2, nArg3);  // 返回 调 sub_4DA1D0 返回值
}



// ------------------------------------------------------------
// 0x5AA370 sub_5AA370
// 飞龙朝向对齐：默认取 vt+184 当前动作号 v2；若"大状态 ≠8 或 分型 ≠2"，
// 改用本尊 X 与宿主 this+7252 的 X 比较（本尊在左为真）重算 v2（朝向 0/1）；
// 末了仅在大状态 this+6556==0 且 v2≠4 时经 vt+148/vt+144 写帧组与朝向
// ------------------------------------------------------------
// 调: sub_5AA370 sub_41A5E0
int /*thiscall*/ sub_5AA370(int *this)  // 实现：调: sub_5AA370 sub_41A5E0
{
  int v2; // edi
  int pTarget7252; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);  // 调虚槽 +184：动画对象 z 倾斜转状态码
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 8 || sub_41A5E0((unsigned int)(this + 1757)) != 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    pTarget7252 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
    v2 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < pTarget7252;  // 调虚槽 +120：动画对象
  }
  result = *(this + 1639);  // this+6556〔大状态ID〕
  if ( result == 0 && v2 != 4 )  // 若 result == 0 与/或 v2 != 4
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, v2);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, v2);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AA640 sub_5AA640
// 飞龙受击位移处理器：先 ·0x495250 做通用受击（源/参转递）；仅在大状态 ==8 且
// 分型 ·0x41A5E0(this+7028)==2 时追加 ·0x5AA420 姿态随机化，并把本尊时钟
// this+7640 的当前时刻写 this+8624（受击时间戳登记）
// ------------------------------------------------------------
// 调: sub_5AA640 sub_495250 sub_41A5E0 sub_5AA420 sub_699000
int /*thiscall*/ sub_5AA640(int this, unsigned int uArg2, int nArg3, int nArg4)  // 实现：调: sub_5AA640 sub_495250 sub_41A5E0 sub_5AA420 sub_699000
{
  int result; // eax

  sub_495250((uint8_t *)this, uArg2, nArg3, nArg4);  // 双标志门 + 转发 vt+968
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result == 8 )  // 若 result == 8
  {
    result = sub_41A5E0(this + 7028);  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 2 )  // 若 result == 2
    {
      sub_5AA420(this);  // 飞龙姿态/朝向随机化步进：两次 rand()%2 掷点决定朝向档（nRand23 ∈ {
      result = sub_699000(this + 7640);  // 【clock_now(clk)】
      *(uint32_t *)(this + 8608) = result;  // this+8608 喷火相位字节
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AA830 sub_5AA830
// 飞龙行为字相位机（this+7148 分发）：大状态 14/16（扑咬飞行段）时直接返回不动；
// 否则 ·0x4E0120 基类前置后按行为字分派——
//   0 登场 vt+1284；4 写行为字 8 转飞行；
//   5 有宿主且 rand()%100<10 且可行动 → 写行为字 4（追击），无宿主 → 写 13；
//   8 有宿主且 10% 概率 → 写 5，无宿主 → 写 17 并 vt+1308(0)；
//   13 → 写 17；14/15 有宿主 → 写 4，无宿主 → 写 13；
//   17 有宿主 → 写 8 且 vt+1308(0)；
// 行为字分派后：可行动且大状态 0 时 vt+1312 追加处理；this+8608 门关着且大状态 0
// 时按 vt+188 是否为 4 在 this+6164（帧组）与 this+6216[3] 两处帧表项之间切换，
// 每次均 ·0x4926A0 复位游标再 vt+196 落定
// ------------------------------------------------------------
// 调: sub_5AA830 sub_4E0120 sub_4926A0
char /*thiscall*/ sub_5AA830(int this)  // 实现：调: sub_5AA830 sub_4E0120 sub_4926A0
{
  int pThis_348; // eax

  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( pThis_348 != 14 )  // 若 pThis_348 != 14
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( pThis_348 != 16 )  // 若 pThis_348 != 16
    {
      sub_4E0120((uint32_t *)this);  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
      switch ( *(uint32_t *)(this + 7148) )  // this+7148〔nBigState〕
      {
        case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1284))(this);  // 调虚槽 +1284
          break;  // 跳出循环/分支
        case 4:  // case 4 = ENUM_CMDPACKET_EXIT
          (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 1104))(8);  // 调虚槽 +1104
          break;  // 跳出循环/分支
        case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
          if ( *(uint32_t *)(this + 7252) != 0 )  // this+7252〔pTarget7252〕
          {
            if ( rand() % 100 < 10 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
              goto LABEL_21;
          }
          else  // 否则分支
          {
            (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 1104))(13);  // 调虚槽 +1104
          }
          break;  // 跳出循环/分支
        case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
          if ( *(uint32_t *)(this + 7252) != 0 )  // this+7252〔pTarget7252〕
          {
            if ( rand() % 100 < 10 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 5);  // 调虚槽 +1104
          }
          else  // 否则分支
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 17);  // 调虚槽 +1104
          }
          goto LABEL_14;
        case 0xD:
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 17);  // 调虚槽 +1104
          break;  // 跳出循环/分支
        case 0xE:
        case 0xF:
          if ( *(uint32_t *)(this + 7252) != 0 )  // this+7252〔pTarget7252〕
LABEL_21:  // 标签 LABEL_21（跳转合流点）
            (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 1104))(4);  // 调虚槽 +1104
          else  // 否则分支
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 13);  // 调虚槽 +1104
          break;  // 跳出循环/分支
        case 0x11:  // case 0x11 = 类型 18 ENUM_CMDPACKET_DELETE_ITEM（删物品回报）
          if ( *(uint32_t *)(this + 7252) != 0 )  // this+7252〔pTarget7252〕
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 8);  // 调虚槽 +1104
LABEL_14:  // 标签 LABEL_14（跳转合流点）
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1308))(this, 0);  // 调虚槽 +1308：CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
          break;  // 跳出循环/分支
        default:  // 默认分支
          break;  // 跳出循环/分支
      }
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
        && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )  // 调虚槽 +840：大状态 getter（this+6556）
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1312))(this);  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
      }
      LOBYTE(pThis_348) = *(uint8_t *)(this + 8608);  // this+8608 骑乘/骑手槽
      if ( (uint8_t)pThis_348 == 0 )
      {
        pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
        if ( pThis_348 == 0 )  // 若 pThis_348 为 0
        {
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 188))(this) == 4 )  // 调虚槽 +188：动画对象 z 倾斜转状态码
          {
            sub_4926A0(*(uint32_t *)(this + 6164));  // 帧游标复位（+44 帧数组；递归子链 +204）
            LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(this + 6164));  // 调虚槽 +196：动画对象设置（换域 + 播放）
          }
          else  // 否则分支
          {
            sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 12));  // 帧游标复位（+44 帧数组；递归子链 +204）
            LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(  // 调虚槽 +196：动画对象设置（换域 + 播放）
                           this,
                           *(uint32_t *)(*(uint32_t *)(this + 6216) + 12));  // this+6216 【推断】资源/帧游标表
          }
        }
      }
    }
  }
  return pThis_348;
}



// ------------------------------------------------------------
// 0x5AAD10 sub_5AAD10
// 飞龙"低空扑咬"攻击段起手（段相位 2）：把朝向档 this+324 抄入 this+8620、
// this+8612 段相位写 2、vt+888(1,0,1000,1000) 双参；随后取 this+6172 上的动画
// 对象（·0x4924C0 族）把其 +48 帧长除以 10（加速 10 倍）、·0x4910E0 与
// ·0x493A60 重设动画时钟；连续 vt+208 写入 this+6216+24/28/32/36/40 五个帧表项
// （攻击段帧组）；vt+196 以 this+6164 落定、·0x4926A0 复位游标、vt+344 写偏移
// this+556；末了 vt+604(this,1) 进入攻击段
// ------------------------------------------------------------
// 调: sub_5AAD10 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
int /*thiscall*/ sub_5AAD10(int *this)  // 实现：调: sub_5AAD10 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
{
  int v2; // edx
  int fld_e1543; // eax
  int fld_e15432; // edi
  int v5; // eax

  v2 = *this;
  *(this + 81) = *(this + 2155);  // this+324〔nRandPick324〕
  *(this + 2153) = 2;  // this+8612〔uAI8612(推断)〕
  (*(void (/*stdcall*/ **)(int, uint32_t, int, int))(v2 + 888))(1, 0, 1000, 1000);  // 虚函数调用 槽+888：速率设置链: a2/a3 经 vt+976 换算 →…
  fld_e1543 = sub_4924C0((int *)*(this + 1543), 0);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
  *(int *)(fld_e1543 + 48) /= 10;
  fld_e15432 = *(this + 1543);  // this+6172〔pAtkCtxA6172〕
  sub_4910E0(fld_e15432);  // 帧时刻推进（返回 1 表示时刻发生位移）
  sub_493A60(fld_e15432, *(uint32_t *)(fld_e15432 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 28));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 32));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 36));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1541));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  sub_4926A0(v5);  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));  // 调虚槽 +344：取坐标三元组
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
}



// ------------------------------------------------------------
// 0x5AB060 sub_5AB060
// 飞龙"高空扑咬"攻击段起手（与 ·0x5AAD10 同构，差异：段相位写 this+8616=2，
// 且末段 vt+196 落定用 this+6164 而非表项链）——同样把 this+6172 动画对象 +48
// 帧长 ÷10 加速、重设动画时钟、vt+208 连写五个帧表项、vt+344 写偏移、vt+604(1) 进段
// ------------------------------------------------------------
// 调: sub_5AB060 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
int /*thiscall*/ sub_5AB060(int *this)  // 实现：调: sub_5AB060 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
{
  int v2; // edx
  int fld_e1543; // eax
  int fld_e15432; // edi
  int v5; // eax

  v2 = *this;
  *(this + 81) = *(this + 2155);  // this+324〔nRandPick324〕
  *(this + 2154) = 2;  // this+8616〔uAI8616(推断)〕
  (*(void (/*stdcall*/ **)(int, uint32_t, int, int))(v2 + 888))(1, 0, 1000, 1000);  // 虚函数调用 槽+888：速率设置链: a2/a3 经 vt+976 换算 →…
  fld_e1543 = sub_4924C0((int *)*(this + 1543), 0);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
  *(int *)(fld_e1543 + 48) /= 10;
  fld_e15432 = *(this + 1543);  // this+6172〔pAtkCtxA6172〕
  sub_4910E0(fld_e15432);  // 帧时刻推进（返回 1 表示时刻发生位移）
  sub_493A60(fld_e15432, *(uint32_t *)(fld_e15432 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 28));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 32));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 36));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1541));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  sub_4926A0(v5);  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));  // 调虚槽 +344：取坐标三元组
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
}



// ------------------------------------------------------------
// 0x5AB4A0 sub_5AB4A0
// 飞龙"撕咬"（FLYDRAGON_BITE）起手：vt+344 写偏移（this+556+152）、this+8608
// 门置 1、vt+196 取帧表首项、·0x4926A0 复位游标、播报 FLYDRAGON_BITE；
// then this+8808 置 1、vt+184 动作号（4 改记 5）写 this+8628、vt+188 写 this+8632；
// 循环 3 次（v8=0..2）把 vt+116(this, i) 三个子对象句柄存入 this+8816/8820/8824、
// vt+152 朝向写 this+8828；this+8789/8790 两门清零、时钟 this+8776 置 10 秒冷却；
// 末了 vt+204(this,100, 帧表项 this+6216+16) 启动攻击表现
// ------------------------------------------------------------
// 证: "FLYDRAGON_BITE"
// 调: sub_5AB4A0 sub_4926A0 sub_698F90
int /*thiscall*/ sub_5AB4A0(uint32_t *this)  // 实现：调: sub_5AB4A0 sub_4926A0 sub_698F90
{
  uint32_t *fld_e1554; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // edi
  uint32_t *pThis_89C; // ebx

  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152);  // 调虚槽 +344：取坐标三元组
  fld_e1554 = (uint32_t *)*(this + 1554);  // this+6216〔pTbl6216(推断)〕
  v3 = *this;
  *((uint8_t *)this + 8608) = 1;  // this+8608〔uAI8608(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 196))(this, *fld_e1554);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  sub_4926A0(v4);  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "FLYDRAGON_BITE", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
  v5 = *this;
  *((uint8_t *)this + 8808) = 1;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 184))(this) == 4 )  // 虚函数调用 槽+184：动画对象 z 倾斜转状态码
    v6 = 5;
  else  // 否则分支
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this);  // 调虚槽 +184：动画对象 z 倾斜转状态码
  v7 = *this;
  *(this + 2157) = v6;  // this+8628〔nPoolTime(推断)〕
  *(this + 2158) = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 188))(this);  // 虚函数调用 槽+188：动画对象 z 倾斜转状态码
  v8 = 0;
  pThis_89C = this + 2204;
  do  // do-while 循环体起点
    *pThis_89C++ = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 116))(this, v8++);  // 调虚槽 +116：取伤害数值
  while ( v8 < 3 );  // 条件循环
  *(this + 2207) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
  *((uint8_t *)this + 8789) = 0;
  *((uint8_t *)this + 8790) = 0;
  sub_698F90((int)(this + 2194), 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
           this,
           100,
           *(uint32_t *)(*(this + 1554) + 16),  // this+6216〔pTbl6216(推断)〕
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5AB6C0 sub_5AB6C0
// 飞龙速度槽调节（增向 + 段号/系数面复位）：先把 7531..7558 参数面与 1891..1899
// 段号区整块清零，再把 this+1897 写 1（该函数独有：系"加速档"标记）；
// nArg3==2 且 nArg2==0：速度槽（vt+672(0)+830）+0.3 并 vt+676 应用；
// nArg3==0：速度槽 +0.3 应用且攻击系数面 this+7620+64 置 1（增伤标记）
// ------------------------------------------------------------
// 调: sub_5AB6C0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5AB6C0(char *this, int nArg2, int nArg3)  // 实现：调: sub_5AB6C0 sub_41A5E0 sub_41A590
{
  char *pThis_1D73; // ecx
  int result; // eax
  unsigned int pThis_2A0; // edi
  int v7; // edx
  unsigned int pThis_2A02; // edi
  int v9; // edx
  int v10; // [esp+18h] [ebp+Ch]
  int v11; // [esp+18h] [ebp+Ch]

  *(this + 7558) = 0;  // this+7558 【推断】攻击参数面字节槽
  *(this + 7557) = 0;  // this+7557 【推断】攻击面门字节
  *(this + 7556) = 0;  // this+7556 【推断】攻击面模式字节
  *(this + 7534) = 0;  // this+7534 内嵌配置块 +14 字节
  *(this + 7533) = 0;  // this+7533 内嵌配置块 +13 字节
  *(this + 7532) = 0;  // this+7532 内嵌配置块 +12 字节
  *(this + 7531) = 0;  // this+7531 内嵌配置块 +11 字节
  *(uint32_t *)(this + 7535) = 0;  // this+7535 内嵌配置块 +15 字节
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
  *((uint32_t *)this + 1897) = 1;  // this+7588〔uForm7588〕
  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 && nArg2 == 0 )  // 若 nArg3 == 2 与/或 nArg2 == 0
    {
      pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
      *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pThis_2A0, v7, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
    }
  }
  else  // 否则分支
  {
    pThis_2A02 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A02, v9, v11);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
    *(uint8_t *)(*((uint32_t *)this + 1905) + 64) = 1;  // this+7620〔pStatusPanel(推断)〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x5ABC20 sub_5ABC20
// 飞龙网络指令接收（·0x4DC630 取事件）：事件 14 时从会话流 dword_8F8520 读两个
// uint16（v5 在前、v4 在后），把 v5 写 vt+148（姿态/朝向槽）、行为字写 23
// （this+7148），可行动时 vt+896(v5, v4) 落定；事件 15 时转 ·0x5AAE70 处理并
// 原样返回 15；其余事件原样返回事件号；取包失败（-1）直接返回
// ------------------------------------------------------------
// 调: sub_5ABC20 sub_4DC630 sub_5AAE70
int /*thiscall*/ sub_5ABC20(uint32_t *this)  // 实现：调: sub_5ABC20 sub_4DC630 sub_5AAE70
{
  int result; // eax
  int v3; // edi
  uint16_t v4; // [esp+8h] [ebp-8h] BYREF
  uint16_t v5; // [esp+Ch] [ebp-4h] BYREF

  result = sub_4DC630(this);  // 关卡/交互事件包处理（关联对象 this+7260 校验）
  v3 = result;
  if ( result != -1 )
  {
    if ( result == 14 )  // 若 result == 14
    {
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v5);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v4);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 148))(this, v5);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 23);  // 调虚槽 +1104
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 896))(this, v5, v4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
    }
    else if ( result == 15 )
    {
      sub_5AAE70(this);  // 飞龙「撕咬「起手（简式）：vt+344 写偏移（this+556+152）、this+8
      return 15;
    }
    return v3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5ABEF0 sub_5ABEF0
// 飞龙 vt+560 setState 拦截（含扑咬相位 18 收尾）：ArgList==8 且高度>80 且可行动
// 时改写作 0 并按二元素表（this+8708）rand()%100<50 掷点写朝向 this+324、
// 宿主 this+7252 清 0；若相位 this+8804==18（低空扑咬中）则清 this+8816 标志、
// 相位写 -1、vt+208 落帧表项 this+6216+16；随后转发 ·0x5AB800 基类；
// 大状态 this+6556==8 时收尾同 ·0x5ABD90 的着陆型：vt+876 写 (700,700,-2000)、
// 第二组归零、vt+888(2,2,1000,1000)、vt+152(4) 取帧号经 vt+896 落定
// ------------------------------------------------------------
// 调: sub_5ABEF0 sub_5AB800
int /*thiscall*/ sub_5ABEF0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：调: sub_5ABEF0 sub_5AB800
{
  char v5; // di
  int pTbl6216; // eax  | +0x1848 → 【推断】资源/帧游标表〔+12 帧对象；5AA830 复位装载〕（CNDrakeLooseSerimalion；va=005AA830）
  int v8; // edx
  int result; // eax
  int v10; // edi
  int v11; // eax

  v5 = ArgList;
  if ( ArgList == 8  // 若 ArgList == 8
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) > 80  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    v5 = 0;
    *(this + 81) = *(uint32_t *)(*(this + 2177) + 4 * (rand() % 100 < 50));  // this+324〔nRandPick324〕
    *(this + 1813) = 0;  // this+7252〔pTarget7252〕
  }
  if ( *(this + 2201) == 18 )
  {
    pTbl6216 = *(this + 1554);  // this+6216〔pTbl6216(推断)〕
    v8 = *this;
    *((uint8_t *)this + 8808) = 0;
    *(this + 2201) = -1;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v8 + 208))(this, *(uint32_t *)(pTbl6216 + 16));  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
  }
  result = sub_5AB800(v5, fArg3, nArg4, nArg5);  // result = 调 sub_5AB800 返回值
  if ( *(this + 1639) == 8 )  // this+6556〔大状态ID〕
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(this, 0, 700, 700, 0, -2000, 1);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      this,
      1,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
    v10 = *this;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);  // 调虚槽 +152：效果通道 3
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v10 + 896))(this, v11);  // 虚函数调用 槽+896：默认虚槽桩（11 行 return）
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AC140 sub_5AC140
// 飞龙 vt+560 setState 拦截（高度 ==80 门变体）：ArgList==8 且高度 !=80 时改写
// 作 0（只有恰在高度 80 才允许进 8 态）；转发 ·0x5AB800 基类后，大状态==8 时
// 收尾同着陆型 (vt+876 写 (700,700,-2000)、第二组归零、vt+888(2,2,1000,1000)、
// vt+152(4)→vt+896)
// ------------------------------------------------------------
// 调: sub_5AC140 sub_5AB800
int /*thiscall*/ sub_5AC140(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：调: sub_5AC140 sub_5AB800
{
  char v5; // di
  int result; // eax
  int v8; // edi
  int v9; // eax

  v5 = ArgList;
  if ( ArgList == 8 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) != 80 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    v5 = 0;
  result = sub_5AB800(v5, fArg3, nArg4, nArg5);  // result = 调 sub_5AB800 返回值
  if ( *(this + 1639) == 8 )  // this+6556〔大状态ID〕
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(this, 0, 700, 700, 0, -2000, 1);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      this,
      1,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
    v8 = *this;
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);  // 调虚槽 +152：效果通道 3
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v8 + 896))(this, v9);  // 虚函数调用 槽+896：默认虚槽桩（11 行 return）
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AFDD0 sub_5AFDD0
// 龙人/光之领主攻击参数面初始化：把 7539/7543/7547/7551 四槽各写 16843009
// （= 0x01010101，即四字节 1/1/1/1 打包，同时给四个连续字节参数位）、
// this+7555 字节写 1；随后取 vt+672(0) 动作对象，读其 +60 与 +74 两槽（经
// ·0x41A5E0 取值）相乘，结果存 this+8640（判定尺/伤害尺 ∏ 两轴）
// ------------------------------------------------------------
// 调: sub_5AFDD0 sub_41A5E0
uint64_t /*thiscall*/ sub_5AFDD0(char *this)  // 实现：调: sub_5AFDD0 sub_41A5E0
{
  int pThis_2A0; // edi
  uint64_t result; // rax
  int v4; // [esp+Ch] [ebp-4h]

  *(uint32_t *)(this + 7539) = 16843009;  // this+7539 配置块 17 字节循环搬运区起点
  *(uint32_t *)(this + 7543) = 16843009;  // this+7543 【推断】攻击参数面槽
  *(uint32_t *)(this + 7547) = 16843009;  // this+7547 【推断】攻击参数面槽
  *(uint32_t *)(this + 7551) = 16843009;  // this+7551 【推断】攻击参数面槽
  *(this + 7555) = 1;  // this+7555 【推断】攻击参数面字节槽
  pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  v4 = sub_41A5E0(pThis_2A0 + 60);  // crypt4byte 解密校验（·0x41A590 逆运算）
  result = (uint64_t)((double)v4 * COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 74)));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *((uint32_t *)this + 2160) = result;  // this+8640〔uCastSlot8640(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x5B1A60 sub_5B1A60
// 光之领主（LordofLight）事件 14 处理：·0x4DC630 取事件包，事件 14 时从会话流
// 读一个 uint16（v14 作为放置参数/槽号），经 ·0x4ABE10(0xBB8=3000, 动作对象, 0)
// 创建附属对象存 this+8640；随后对该对象连续配置：vt+372(0) 初始化、
// vt+1040 取结构置 -1、+8638 清 0、+8640 写 1；再 ·0x45FE80 挂到宿主
// （vt+80 取父、v3 事件号、v14 参、附属对象）并 vt+148 写朝向、
// vt+112 定位到 (−3000, 本尊 Y)，末了 vt+1120/vt+596/vt+604 三项收尾
// ------------------------------------------------------------
// 调: sub_5B1A60 sub_4DC630 sub_4ABE10 sub_45FE80
int /*thiscall*/ sub_5B1A60(int *this)  // 实现：调: sub_5B1A60 sub_4DC630 sub_4ABE10 sub_45FE80
{
  int result; // eax
  int v3; // edi
  void **v4; // eax
  int pObj; // eax
  int v6; // eax
  int pDialogObj8640_; // ebx  | +0x21C0 → 对话/存活奖励对象指针（CNLordofLightBase；va=005B2F40）
  int v8; // eax
  int pDialogObj8640_2; // ebx  | +0x21C0 → 对话/存活奖励对象指针（CNLordofLightBase；va=005B2F40）
  int v10; // eax
  int v11; // eax
  int v12; // [esp-14h] [ebp-20h]
  int pDialogObj8640; // [esp-10h] [ebp-1Ch]  | +0x21C0 → 对话/存活奖励对象指针（CNLordofLightBase；va=005B2F40）
  uint16_t v14; // [esp+8h] [ebp-4h] BYREF

  result = sub_4DC630(this);  // 关卡/交互事件包处理（关联对象 this+7260 校验）
  v3 = result;
  if ( result != -1 )
  {
    if ( (uint16_t)result == 14 )
    {
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v14);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
      v4 = (void **)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
      pObj = sub_4ABE10((void *)0xBB8, *v4, 0);  // size=10050
      *(this + 2160) = pObj;  // this+8640〔uCastSlot8640(推断)〕
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 372))(pObj, 0);  // 调虚槽 +372：目标点写入
      *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2160) + 1040))(*(this + 2160)) = -1;  // 虚函数调用 槽+1040
      *(uint8_t *)(*(this + 2160) + 8638) = 0;  // this+8640〔uCastSlot8640(推断)〕
      *(uint32_t *)(*(this + 2160) + 8640) = 1;  // this+8640〔uCastSlot8640(推断)〕
      pDialogObj8640 = *(this + 2160);  // this+8640〔uCastSlot8640(推断)〕
      v12 = v14;
      v6 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      sub_45FE80(v6, v3, 0, v12, pDialogObj8640, 0, 0);  // 调 对象注册
      pDialogObj8640_ = *(uint32_t *)*(this + 2160);  // fld_e21602 = 读 this+2160
      v8 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
      (*(void (/*thiscall*/ **)(uint32_t, int))(pDialogObj8640_ + 148))(*(this + 2160), v8);  // 虚函数调用 槽+148：槽（12 行）
      pDialogObj8640_2 = *(uint32_t *)*(this + 2160);  // fld_e21603 = 读 this+2160
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v10);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(pDialogObj8640_2 + 112))(*(this + 2160), -3000, v11);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2160) + 1120))(*(this + 2160));  // 虚函数调用 槽+1120：默认虚槽桩（10 行 return）
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2160) + 596))(*(this + 2160), 0);  // 虚函数调用 槽+596：[RTTI: IRDCollisionObject__vmt254…
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2160) + 604))(*(this + 2160), 0);  // 虚函数调用 槽+604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    }
    return v3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B1D20 sub_5B1D20
// 光之领主激光落点抽样（1 型十段相位机）：十项大状态表 {1..10} 按 this+8612 段号
// 索引；当前动画态 == 该段目标态且 this+8608 防重门未开时，可行动下做至多 100 次
// 落点试位——本尊 X ±200（rand()%400−201）、Y ±50（rand()%100−51）抖动，
// vt+136 校验可站即停；随后 vt+152(this,150,1,...) 取判定基准，vt+584 以
// (nRand,nRand2) 双坐标生成 30072 号判定体携带 this+8600 参；末尾置
// this+8608=1 防重，并在动画播完（态 == 表项+1）时清防重门、段号+1
// ------------------------------------------------------------
// 调: sub_5B1D20
int /*thiscall*/ sub_5B1D20(int *this)  // 实现：调: sub_5B1D20
{
  int v2; // eax
  int v3; // edi
  int nRand; // edi
  int v5; // ebx
  int nRand2; // ebx
  int v8; // eax
  int v9; // eax
  int fld_e2153; // ecx
  int result; // eax
  uint32_t v12[10]; // [esp+8h] [ebp-2Ch]
  int v13; // [esp+30h] [ebp-4h]

  v2 = *this;
  v12[0] = 1;
  v12[1] = 2;
  v12[2] = 3;
  v12[3] = 4;
  v12[4] = 5;
  v12[5] = 6;
  v12[6] = 7;
  v12[7] = 8;
  v12[8] = 9;
  v12[9] = 10;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v2 + 200))(this) + 148) == v12[*(this + 2153)]  // 虚函数调用 槽+200：取动画对象
    && *((uint8_t *)this + 8608) == 0 )  // this+8608 骑乘/骑手槽
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      v13 = 100;
      do  // do-while 循环体起点
      {
        v3 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
        nRand = v3 + rand() % 400 - 201;  // 调 取伪随机数
        v5 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        nRand2 = v5 + rand() % 100 - 51;  // 调 取伪随机数
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(*this + 136))(this, nRand, nRand2, 0) != 0 )  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
          break;  // 跳出循环/分支
      }
      while ( v13-- > 0 );  // 条件循环
      v13 = *this;
      v8 = (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v13 + 152))(this, 150, 1, 0, 0);  // 虚函数调用 槽+152：效果通道 3
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, uint32_t, uint32_t, int))(v13 + 584))(  // 虚函数调用 槽+584：动作数据包发布（会话 3 定案：类型 48012 + 0x6E 字节
        this,
        nRand,
        nRand2,
        0,
        nRand,
        nRand2,
        30072,
        *(this + 2150),  // this+8600〔uAI8600(推断)〕
        0,
        v8);
    }
    *((uint8_t *)this + 8608) = 1;  // this+8608〔uAI8608(推断)〕
  }
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  fld_e2153 = *(this + 2153);  // this+8612〔uAI8612(推断)〕
  if ( *(uint32_t *)(v9 + 148) == v12[fld_e2153] + 1 )
  {
    *((uint8_t *)this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
    *(this + 2153) = fld_e2153 + 1;  // this+8612〔uAI8612(推断)〕
  }
  result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  if ( *(uint8_t *)(result + 170) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
    if ( (uint8_t)result != 0 )
    {
      (*(void (/*thiscall*/ **)(int *))(*this + 564))(this);  // 调虚槽 +564
      return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 15, 0, 2, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B4A50 sub_5B4A50
// 光之领主"弹幕雨"批量投放（userpurge：ecx=本尊，nArg2/nArg3 出参占位，
// nArg4/nArg5 = 投弹数范围，nArg6 = 弹种（-1 随机），nArg7 = 目标句柄（-1 自动））：
// 可行动时按 rand 均分投弹数 v12 ∈ [nArg5, nArg4]；每发循环内——
// 落点在本尊 X ±20 / Y ±10 抖动，vt+136 至多 100 次校验可站；
// 三参 v27 = {X 幅度 rand%200+100, Y 幅度 rand%100+50, Z rand%60+40}、
// 翻转位 rand%2、帧组 3−(rand%2)、弹种默认从 {250,252,253} 三选一；
// ·0x460230 解算落点→this+8636、vt+152(this,1,v27,8,...) 构造参数、vt+376 求
// 判定体、vt+592(弹种, 判定体) 真正发射（每发总数由 v31 递减控制）
// ------------------------------------------------------------
// 调: sub_5B4A50 sub_460230
int /*userpurge*/ sub_5B4A50@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4, int nArg5, int nArg6, int nArg7)  // 实现：调: sub_5B4A50 sub_460230
{
  int result; // eax
  int nRand; // eax
  int v10; // edi
  int v11; // et2
  int v12; // edx
  int v13; // edi
  int nRand2; // ebx
  int v15; // edi
  int nRand3; // eax
  int v17; // edx
  int v19; // eax
  int v20; // edi
  int v21; // eax
  int v22; // eax
  int v23; // eax
  uint32_t v26[3]; // [esp+4h] [ebp-1Ch]
  uint16_t v27[3]; // [esp+10h] [ebp-10h] BYREF
  bool nRand4; // [esp+16h] [ebp-Ah]
  char nRand5; // [esp+17h] [ebp-9h]
  int v30; // [esp+18h] [ebp-8h]
  int v31; // [esp+1Ch] [ebp-4h]
  int v32; // [esp+28h] [ebp+8h]
  int nRand6; // [esp+28h] [ebp+8h]
  int nArg72; // [esp+2Ch] [ebp+Ch]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();  // nRand = 调 rand
    v10 = nArg4 - nArg5 + 1;
    v11 = nRand % v10;
    result = nRand / v10;
    v12 = nArg5 + v11;
    if ( nArg5 + v11 > 0 )
    {
      v26[0] = 250;
      v26[1] = 252;
      v26[2] = 253;
      v31 = v12;
      do  // do-while 循环体起点
      {
        if ( nArg7 == -1 )
          nArg72 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1) + 132) + 108) + 112);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        else  // 否则分支
          nArg72 = nArg7;
        v32 = 100;
        do  // do-while 循环体起点
        {
          v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);  // 调虚槽 +120：动画对象
          nRand2 = v13 + rand() % 40 - 20;  // 调 取伪随机数
          v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          nRand3 = rand();  // nRand3 = 调 rand
          v17 = *pArg1;
          v30 = v15 + nRand3 % 20 - 10;
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(v17 + 136))(pArg1, nRand2, v30, 0) != 0 )  // 虚函数调用 槽+136：槽（10 行）
            break;  // 跳出循环/分支
        }
        while ( v32-- > 0 );  // 条件循环
        v27[0] = rand() % 200 + 100;  // v27[0] = 调 rand
        v27[1] = rand() % 100 + 50;  // v27[1] = 调 rand
        nRand4 = rand() % 2 == 0;  // nRand4 = 调 rand
        nRand5 = 3 - (rand() % 2 != 0);  // rand()%2 取模随机
        v27[2] = rand() % 60 + 40;  // v27[2] = 调 rand
        v19 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 80))(pArg1, nArg2, nArg3);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        pArg1[2159] = sub_460230(v19);  // 图标槽随机 id 分配（线性探测）
        if ( nArg6 == -1 )
          nRand6 = v26[rand() % 3];  // nRand6 = 取 v26[rand() % 3]
        else  // 否则分支
          nRand6 = nArg6;
        v20 = *pArg1;
        nArg3 = 0;
        nArg2 = 0;
        v21 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint16_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 152))(  // 调虚槽 +152：效果通道 3
                pArg1,
                1,
                v27,
                8,
                pArg1[2159],
                0,
                0);
        v22 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 128))(pArg1, v21);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        v23 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*pArg1 + 376))(pArg1, nArg72, nRand2, v30, v22 + 10);  // 调虚槽 +376：坐标同步包（type 37）
        result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v20 + 592))(pArg1, nRand6, v23);  // 虚函数调用 槽+592：位置/状态同步包发布（短版 48024 / 长版 type 22）
        --v31;
      }
      while ( v31 != 0 );  // 条件循环
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B4D10 sub_5B4D10
// 光之领主朝向对齐（与 ·0x5AA370 同构，差异：分型门用 ·0x41A5E0(this+7028)!=5
// 而非 !=2）——大状态≠8 或分型≠5 时按本尊 X 与宿主 X 比较重算朝向 v2，
// 仅大状态==0 且 v2≠4 时 vt+148/vt+144 落定
// ------------------------------------------------------------
// 调: sub_5B4D10 sub_41A5E0
int /*thiscall*/ sub_5B4D10(int *this)  // 实现：调: sub_5B4D10 sub_41A5E0
{
  int v2; // edi
  int pTarget7252; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);  // 调虚槽 +184：动画对象 z 倾斜转状态码
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 8 || sub_41A5E0((unsigned int)(this + 1757)) != 5 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    pTarget7252 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
    v2 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < pTarget7252;  // 调虚槽 +120：动画对象
  }
  result = *(this + 1639);  // this+6556〔大状态ID〕
  if ( result == 0 && v2 != 4 )  // 若 result == 0 与/或 v2 != 4
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, v2);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, v2);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B51D0 sub_5B51D0
// 光之领主姿态/朝向随机化（与 ·0x5AA420 同族，差异：第二组速率系数 0.35 而非
// 0.175，且写的是 vt+896(bool, 3−bit)/vt+148/vt+144 三处）——两掷 rand()%2 决定
// 朝向位 v19 与姿态档 v4=3−bit；速度槽两轴乘积分别以 1.0 与 0.35 折算两组
// vt+876 参数；`nRand != 4` 与 `nRand2 != 4` 均恒真（rand()%2∈{0,1}），
// 属编译产物/反编译残留，不影响执行路径
// ------------------------------------------------------------
// 调: sub_5B51D0 sub_41A5E0
int /*thiscall*/ sub_5B51D0(void *this)  // 实现：调: sub_5B51D0 sub_41A5E0
{
  int nRand; // ebx
  int nRand2; // eax
  int v4; // edi
  int pThis_2A0; // ebx
  int pThis_2A02; // ebx
  uint64_t v7; // rax
  int pThis_2A03; // ebx
  int pThis_2A04; // ebx
  uint64_t v10; // rax
  int nRand22; // [esp+Ch] [ebp-18h]
  int v13; // [esp+Ch] [ebp-18h]
  float v14; // [esp+10h] [ebp-14h]
  int v15; // [esp+14h] [ebp-10h]
  int v16; // [esp+14h] [ebp-10h]
  float v17; // [esp+18h] [ebp-Ch]
  int v18; // [esp+1Ch] [ebp-8h]
  BOOL v19; // [esp+20h] [ebp-4h]

  nRand = rand() % 2;  // nRand = 调 rand
  nRand2 = rand() % 2;  // nRand2 = 调 rand
  v4 = 3 - (nRand2 != 0);
  nRand22 = nRand2;
  v19 = nRand == 0;
  if ( nRand != 4 )  // 若 nRand != 4
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    v18 = sub_41A5E0(pThis_2A0 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v17 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    v15 = sub_41A5E0(pThis_2A02 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v7 = (uint64_t)(double)(int)(uint64_t)((double)v15 * COERCE_FLOAT(sub_41A5E0(pThis_2A02 + 830)));  // crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*fastcall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      this,
      HIDWORD(v7),  // 调 取 64 位值高 32 位
      0,
      v7,
      (uint64_t)(double)(int)(uint64_t)((double)v18 * v17),
      0,
      0,
      0);
    nRand2 = nRand22;
  }
  if ( nRand2 != 4 )  // 若 nRand2 != 4
  {
    pThis_2A03 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    v13 = sub_41A5E0(pThis_2A03 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v14 = COERCE_FLOAT(sub_41A5E0(pThis_2A03 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
    pThis_2A04 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    v16 = sub_41A5E0(pThis_2A04 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v10 = (uint64_t)((double)(int)(uint64_t)((double)v16 * COERCE_FLOAT(sub_41A5E0(pThis_2A04 + 830)))  // crypt4byte 解密校验（·0x41A590 逆运算）
                           * 0.34999999);
    (*(void (/*fastcall*/ **)(void *, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      this,
      HIDWORD(v10),  // 调 取 64 位值高 32 位
      1,
      v10,
      (uint64_t)((double)(int)(uint64_t)((double)v13 * v14) * 0.34999999),
      0,
      0,
      0);
  }
  (*(void (/*thiscall*/ **)(void *, BOOL, int))(*(uint32_t *)this + 896))(this, v19, v4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  (*(void (/*thiscall*/ **)(void *, BOOL))(*(uint32_t *)this + 148))(this, v19);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
  return (*(int (/*thiscall*/ **)(void *, BOOL))(*(uint32_t *)this + 144))(this, v19);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
}



// ------------------------------------------------------------
// 0x5B58D0 sub_5B58D0
// 海星（CNStarFish）子对象消亡回调：仅当消亡者 == this+8612（子对象槽）且
// 本尊 vt[210] 状态 ==14 且 this+8616 计数 >1 时——·0x491C10 释放帧表首项，
// 计数减 1、this+8624 句柄清空，取消亡者 vt+120 X 与本尊 vt+120 X 求差 v8，
// 再链式 vt[32]→vt[31]→vt[30] 取本尊 X，末了 vt[28] 以 (X − v8) 写入修正坐标
// （子对象消亡后把本尊回拉到原位置，抵消挂接偏移）【推断】
// ------------------------------------------------------------
// 调: sub_5B58D0 sub_491C10
int /*thiscall*/ sub_5B58D0(int **this, int nArg2)  // 实现：调: sub_5B58D0 sub_491C10
{
  int result; // eax
  int pAttachHost; // ecx  | +0x21A0 → 子类槽〔5B4700 归零〕（CNStarFish；va=005B4700）
  int v5; // edi
  int pAttachHost_; // eax  | +0x21A0 → 子类槽〔5B4700 归零〕（CNStarFish；va=005B4700）
  int *v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax

  result = nArg2;
  if ( (int *)nArg2 == *(this + 2152) )  // this+8608〔uAI8608(推断)〕
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[210])(this);
    if ( result == 14 && (int)*(this + 2154) > 1 )  // 若 result == 14
    {
      sub_491C10(**(this + 1554));  // 遍历帧数组（首+44/尾+48，步长 88）
      pAttachHost = (int)*(this + 2152);  // this+8608〔uAI8608(推断)〕
      *(this + 2154) = (int *)((char *)*(this + 2154) - 1);  // this+8616〔uAI8616(推断)〕
      *(this + 2156) = nullptr;  // this+8624〔uAI8624(推断)〕
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAttachHost + 120))(pAttachHost);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t))(**(this + 2152) + 916))(*(this + 2152));  // 虚函数调用 槽+916
      pAttachHost_ = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2152) + 120))(*(this + 2152));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      v7 = *this;
      v8 = v5 - pAttachHost_;
      v9 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
      v10 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v9);
      v11 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v10);
      return ((int (/*thiscall*/ *)(int **, int))v7[28])(this, v11 - v8);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B5EE0 sub_5B5EE0
// 光之领主攻击参数面整块清零（this+7584 写 2 变体）：与 ·0x5C6700 同族
// （7531..7558 逐槽 + 7564..7596 清零），差异是 this+7584 写 2（非 7537 写 1），
// 且 nArg32==0 时把 this+7620+4 系数项自加加倍（×2）而非写 −50
// ------------------------------------------------------------
// 调: sub_5B5EE0
int /*thiscall*/ sub_5B5EE0(int this, int nArg2, int nArg3)  // 实现：调: sub_5B5EE0
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558 【推断】攻击参数面字节槽
  *(uint8_t *)(this + 7557) = 0;  // this+7557 【推断】攻击面门字节
  *(uint8_t *)(this + 7556) = 0;  // this+7556 【推断】攻击面模式字节
  *(uint8_t *)(this + 7534) = 0;  // this+7534 内嵌配置块 +14 字节
  *(uint8_t *)(this + 7533) = 0;  // this+7533 内嵌配置块 +13 字节
  *(uint8_t *)(this + 7532) = 0;  // this+7532 内嵌配置块 +12 字节
  *(uint8_t *)(this + 7531) = 0;  // this+7531 内嵌配置块 +11 字节
  *(uint32_t *)(this + 7535) = 0;  // this+7535 内嵌配置块 +15 字节
  *(uint32_t *)(this + 7539) = 0;  // this+7539 配置块 17 字节循环搬运区起点
  *(uint32_t *)(this + 7543) = 0;  // this+7543 【推断】攻击参数面槽
  *(uint32_t *)(this + 7547) = 0;  // this+7547 【推断】攻击参数面槽
  *(uint32_t *)(this + 7551) = 0;  // this+7551 【推断】攻击参数面槽
  *(uint8_t *)(this + 7555) = 0;  // this+7555 【推断】攻击参数面字节槽
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;  // this+7572 【推断】模式 2 档
  *(uint32_t *)(this + 7568) = 0;  // this+7568 【推断】激活/模式槽
  *(uint32_t *)(this + 7564) = 0;  // this+7564 【推断】形态/模式槽
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580 【推断】攻击面门字节
  *(uint32_t *)(this + 7576) = 0;  // this+7576 相位槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 【推断】段号横向偏置
  *(uint32_t *)(this + 7584) = 2;  // this+7584〔uForm7584〕
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    nArg32 = nArg2;
  if ( nArg32 == 0 )  // 若 nArg32 为 0
    *(float *)(*(uint32_t *)(this + 7620) + 4) = *(float *)(*(uint32_t *)(this + 7620) + 4)  // this+7620 【推断】属性/速度面板对象
                                             + *(float *)(*(uint32_t *)(this + 7620) + 4);  // this+7620 【推断】属性/速度面板对象
  return result;
}



// ------------------------------------------------------------
// 0x5B6080 sub_5B6080
// 场景扫描：找出"可被点燃的火种"——遍历 this+116 场景对象列表，vt+40(obj,529)
// 筛型后其 vt+340 形态码 ∈ {260,263,264}（·0x5B4A00 同款白名单，此处内联展开）
// 且 vt+1244 目标资格门通过者，返回该对象指针；全扫完无命中返回 0
// ------------------------------------------------------------
// 调: sub_5B6080
int /*thiscall*/ sub_5B6080(uint32_t *this)  // 函数定义: 生成召唤体
{
  unsigned int i; // edi
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // esi

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v4 = *(uint32_t *)(fld_e29 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= v5 )
      break;  // 跳出循环/分支
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 若 v6 != 0
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else  // 否则分支
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 若 v9 != 0
        pObj = *(uint32_t *)(v9 + 4 * i);
      else  // 否则分支
        pObj = 0;
      if ( (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 260  // 调虚槽 +340：三元组基址（+284，vt+340）
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 263  // 调虚槽 +340：三元组基址（+284，vt+340）
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 264)  // 调虚槽 +340：三元组基址（+284，vt+340）
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj) != 0 )  // 调虚槽 +1244
      {
        return pObj;
      }
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5B6240 sub_5B6240
// 光之领主攻速/体型微调：vt+688 取子对象（动画/模型轴）交 ·0x4EB2C0(obj, 4.0)
// 以 4.0 幅度调整；this+8628 写 1065353216（= 1.0f 位型 0x3F800000）、
// this+7288 写 -1（未知计数器归 -1）
// ------------------------------------------------------------
// 调: sub_5B6240 sub_4EB2C0
char /*thiscall*/ sub_5B6240(uint32_t *this)  // 实现：调: sub_5B6240 sub_4EB2C0
{
  int *v2; // eax
  char result; // al

  v2 = (int *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);  // 调虚槽 +688：附加块基址 this+6160
  result = sub_4EB2C0(v2, 4.0);  // 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  *(this + 2157) = 1065353216;  // this+8628 = 1.0f
  *(this + 1822) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x5B6330 sub_5B6330
// 光之领主攻击系数面档位（正向 + 段号 2 变体）：nArg3==2 时 this+7534 字节写 1
// （形态门）；nArg3==0 时 this+7564 段号槽写 2、this+7596 写 50 且 this+7620+36
// 系数项自加加倍（×2）
// ------------------------------------------------------------
// 调: sub_5B6330
int /*thiscall*/ sub_5B6330(int this, int nArg2, int nArg3)  // 实现：调: sub_5B6330
{
  int result; // eax

  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )  // 若 nArg3 == 2
      *(uint8_t *)(this + 7534) = 1;  // this+7534 内嵌配置块 +14 字节
  }
  else  // 否则分支
  {
    result = *(uint32_t *)(this + 7620) + 160;  // result = 读 this+7620
    *(uint32_t *)(this + 7568) = 2;  // this+7568 【推断】激活/模式槽
    *(uint32_t *)(this + 7596) = 50;  // this+7596 【推断】段号横向偏置
    *(float *)(result + 4) = *(float *)(result + 4) + *(float *)(result + 4);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5BBE20 sub_5BBE20
// 空骨鱼（或同族）每帧复合：先 ·0x5BB450 子过程，再经 vt+1320 与 vt+1312
// 两个派生槽各调一次（1312 返回值作为本函数返回值）【推断：扫描/漂移双步】
// ------------------------------------------------------------
// 调: sub_5BBE20 sub_5BB450
int /*thiscall*/ sub_5BBE20(void *this)  // 实现：调: sub_5BBE20 sub_5BB450
{
  sub_5BB450();  // 飞艇·反应态决策机（行为字 this+1787 概率互转）
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1320))(this);  // 调虚槽 +1320：CNGhoul 技能槽 vmt528（11 行轻量）
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1312))(this);  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
}



// ------------------------------------------------------------
// 0x5BCFB0 sub_5BCFB0
// 无参转发桩（attributes: thunk）：转调 ·0x594370()
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5BCFB0 sub_594370
int sub_5BCFB0()  // 实现：调: sub_5BCFB0 sub_594370
{
  return sub_594370();  // 魔法师基类 AI 小调度（this+1787：待机逻辑 + 4↔13 动画切换）
}



// ------------------------------------------------------------
// 0x5C4C00 sub_5C4C00
// 树精机偶（CNDendroid）子对象消亡回调：this+8616==1 且 消亡者==this+8620 且
// 大状态==14 且 this+8628 计数 >1 时——·0x491C10 取帧长 fld_e1554，
// this+8636 计帧 +1，累计达 5‰ 帧长（5×fld/1000）则计数 this+8628 减 1 且
// 计帧归 0；每次都对 this+8620 对象调 vt+120 与 vt+916（重取值/更新）
// ------------------------------------------------------------
// 调: sub_5C4C00 sub_491C10
void /*thiscall*/ sub_5C4C00(uint32_t *this, int nArg2)  // 实现：调: sub_5C4C00 sub_491C10
{
  int pTbl6216; // eax  | +0x1848 → 【推断】资源/帧游标表〔+24 帧游标；5C4810 sub_4926A0 复位〕（CNDendroidBasic；va=005C4810）
  int fld_e2159; // edx

  if ( *(this + 2154) == 1  // this+8616〔uAI8616(推断)〕
    && nArg2 == *(this + 2155)  // this+8620〔uAI8620(推断)〕
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14  // 调虚槽 +840：大状态 getter（this+6556）
    && (int)*(this + 2157) > 1 )  // this+8628〔nPoolTime(推断)〕
  {
    pTbl6216 = sub_491C10(*(uint32_t *)(*(this + 1554) + 16));  // 遍历帧数组（首+44/尾+48，步长 88）
    fld_e2159 = *(this + 2159) + 1;  // this+8636〔pDollTarget(推断)〕
    *(this + 2159) = fld_e2159;  // this+8636〔pDollTarget(推断)〕
    if ( fld_e2159 >= 5 * pTbl6216 / 1000 )
    {
      --*(this + 2157);  // this+8628〔nPoolTime(推断)〕
      *(this + 2159) = 0;  // this+8636〔pDollTarget(推断)〕
    }
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2155) + 120))(*(this + 2155));  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2155) + 916))(*(this + 2155));  // 虚函数调用 槽+916
  }
}



// ------------------------------------------------------------
// 0x5C5020 sub_5C5020
// 树精机偶切段配置（与 ·0x5C4F00 为对偶：那里清标记，这里置标记）：
// vt+208 写帧表项 this+6216+32、vt+888(0,0,1000,1000)、·0x4926A0 与 vt+196 以
// this+6216[1] 重设游标；把 this+8604/8608 两快照抄入 this+6172/6176、
// this+8612 抄入 this+6160；攻击系数面 this+7620 的 +0/+32/+64 三字节置 1，
// this+8600==1 时 +96/+128 两字节清 0；随后 this+8600 清 0、速度槽
// （vt+672(3)+102）读出 −1.0 写回
// ------------------------------------------------------------
// 调: sub_5C5020 sub_4926A0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C5020(uint32_t *this)  // 实现：调: sub_5C5020 sub_4926A0 sub_41A5E0 sub_41A590
{
  int nActSnapA8604; // ecx  | +0x219C → 动作号快照A〔5C57F0 写 this+1543 值；5C4780 用于还原比对〕（CNDendroidBasic；va=005C3A30）
  int nActSnapB8608; // edx  | +0x21A0 → 动作号快照B〔5C57F0 写 this+1544 值；5C4780 还原比对〕（CNDendroidBasic；va=005C3A30）
  uint8_t *fld_e1905; // eax
  int v5; // edx
  unsigned int v6; // esi
  int v7; // edx
  int v9; // [esp+4h] [ebp-4h]

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 32));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  nActSnapA8604 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
  nActSnapB8608 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
  *(this + 1540) = *(this + 2153);  // this+8612〔uAI8612(推断)〕
  fld_e1905 = (uint8_t *)*(this + 1905);  // this+7620〔pStatusPanel(推断)〕
  *(this + 1543) = nActSnapA8604;  // this+6172〔pAtkCtxA6172〕
  *(this + 1544) = nActSnapB8608;  // this+6176〔pAtkCtxB6176〕
  *fld_e1905 = 1;
  *(uint8_t *)(*(this + 1905) + 32) = 1;  // this+7620〔pStatusPanel(推断)〕
  *(uint8_t *)(*(this + 1905) + 64) = 1;  // this+7620〔pStatusPanel(推断)〕
  if ( *(this + 2150) == 1 )  // this+8600〔uAI8600(推断)〕
  {
    *(uint8_t *)(*(this + 1905) + 96) = 0;  // this+7620〔pStatusPanel(推断)〕
    *(uint8_t *)(*(this + 1905) + 128) = 0;  // this+7620〔pStatusPanel(推断)〕
  }
  v5 = *this;
  *(this + 2150) = 0;  // this+8600〔uAI8600(推断)〕
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 672))(this, 3) + 102;  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
  *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v6)) - 1.0;  // crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(v6, v7, v9);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x5C5300 sub_5C5300
// 树精机偶"落石/种子散布"发射：·0x5C4F00 切段后，可行动时 ·0x432FA0 取参，
// 掷 rand()%3 得发作数（v6 = 掷值+3，即 3..5 发）；每发做至多 100 次落点试位
// （本尊 X ±100、Y ±35，·0x4D9210 校验可站），成功即 ·0x4E4A50 生成效果号
// 1007 或 1006（rand()%2 决定，参数 1、朝向 4）；试位失败则跳过本发
// ------------------------------------------------------------
// 调: sub_5C5300 sub_5C4F00 sub_432FA0 sub_4D9210 sub_4E4A50
int /*thiscall*/ sub_5C5300(uint32_t *this, int nArg2)  // 实现：调: sub_5C5300 sub_5C4F00 sub_432FA0 sub_4D9210 sub_4E4A50
{
  int result; // eax
  int nRand; // eax
  int v5; // et2
  int v6; // edx
  int v7; // edi
  int nRand2; // edi
  int v9; // ebx
  int nRand3; // ebx
  int nRand4; // eax
  int v12; // [esp+4h] [ebp-4h]
  int v13; // [esp+10h] [ebp+8h]

  sub_5C4F00(nArg2);  // 某 Boss 攻击段切换例程（段计数递减 + 帧组重绑）：this+8648 段计数自减
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    sub_432FA0();  // srand 播种
    nRand = rand();  // nRand = 调 rand
    v5 = nRand % 3;
    result = nRand / 3;
    v6 = v5 + 3;
    if ( v5 + 3 > 0 )
    {
      v12 = v6;
      do  // do-while 循环体起点
      {
        v13 = 100;
        while ( 1 )  // 条件循环
        {
          v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调虚槽 +120：动画对象
          nRand2 = v7 + rand() % 200 - 100;  // 调 取伪随机数
          v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          nRand3 = v9 + rand() % 70 - 35;  // 调 取伪随机数
          if ( sub_4D9210(this, nRand2, nRand3, nullptr) )  // 若调用结果为真
            break;  // 跳出循环/分支
          result = --v13;
          if ( v13 <= 0 )  // 若 v13 <= 0
            goto LABEL_9;
        }
        nRand4 = rand() % 2;  // nRand4 = 调 rand
        result = sub_4E4A50(nRand2, (int)this, 1007 - (nRand4 != 0), 1, nRand2, nRand3, 0, 4, 0, 0, 0);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
LABEL_9:  // 标签 LABEL_9（跳转合流点）
        --v12;
      }
      while ( v12 != 0 );  // 条件循环
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C5520 sub_5C5520
// 树精机偶切段后速度槽增向：·0x5C4F00(nArg2) 切段，再把速度槽
// （vt+672(3)+158）读出 +1.0 经 ·0x41A590 写回（不调 vt+676 应用）
// ------------------------------------------------------------
// 调: sub_5C5520 sub_5C4F00 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C5520(void *this, int nArg2)  // 实现：调: sub_5C5520 sub_5C4F00 sub_41A5E0 sub_41A590
{
  unsigned int pThis_2A0; // esi
  int v4; // edx
  int v6; // [esp+Ch] [ebp+8h]

  sub_5C4F00(nArg2);  // 某 Boss 攻击段切换例程（段计数递减 + 帧组重绑）：this+8648 段计数自减
  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3) + 158;  // 调虚槽 +672：自身 HP
  *(float *)&v6 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 1.0;  // crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(pThis_2A0, v4, v6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x5C5640 sub_5C5640
// 树精机偶攻击参数面整块清零（正向档）：7531..7558 逐槽 + 7564..7596 清零；
// nArg3==2 且 nArg2==0：this+7568 写 2、this+7596 写 50；
// nArg3==0：this+7568 写 1、this+7596 写 50 且系数面 this+7620+36 与 +68
// 两项系数各自自加加倍（×2）
// ------------------------------------------------------------
// 调: sub_5C5640
int /*thiscall*/ sub_5C5640(int this, int nArg2, int nArg3)  // 实现：调: sub_5C5640
{
  int result; // eax
  int pParamObj7620; // eax  | +0x1DC4 → 速度/属性参数对象（其 +4/+68/+100/+132 浮点被倍率改写）【推断】（CNRodinglo）
  double v5; // st7

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
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580 攻击面门字节
  *(uint32_t *)(this + 7576) = 0;  // this+7576 攻击参数面槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 段号横向偏置
  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    if ( nArg3 == 2 )  // 若 nArg3 == 2
    {
      *(uint32_t *)(this + 7568) = 2;  // this+7568 激活/模式槽
      if ( nArg2 == 0 )  // 若 nArg2 为 0
        *(uint32_t *)(this + 7596) = 50;  // this+7596 段号横向偏置
    }
  }
  else  // 否则分支
  {
    pParamObj7620 = *(uint32_t *)(this + 7620);  // fld_1DC4 = 读 this+7620
    *(uint32_t *)(this + 7568) = 1;  // this+7568 激活/模式槽
    *(uint32_t *)(this + 7596) = 50;  // this+7596 段号横向偏置
    v5 = *(float *)(pParamObj7620 + 36);
    result = pParamObj7620 + 32;
    *(float *)(result + 4) = v5 + v5;
    *(float *)(*(uint32_t *)(this + 7620) + 68) = *(float *)(*(uint32_t *)(this + 7620) + 68)  // this+7620 速度/属性参数对象
                                              + *(float *)(*(uint32_t *)(this + 7620) + 68);  // this+7620 速度/属性参数对象
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C63E0 sub_5C63E0
// 树精机偶对宿主发射效果：有宿主 this+7252 且可行动时，取宿主 X/Y 坐标，
// 效果号默认 30094；若本尊 vt+340 形态码 == 60006 则改用 30380（分型差异化
// 效果号，硬编码直证）；以本尊 vt+152 朝向为参调 ·0x4E4A50 生成效果，
// 并把 this+8856 标志置 1
// ------------------------------------------------------------
// 调: sub_5C63E0 sub_4E4A50
int /*thiscall*/ sub_5C63E0(uint8_t *this)  // 实现：调: sub_5C63E0 sub_4E4A50
{
  int result; // eax
  int pThis_715; // ebx
  int v4; // edi
  int pThis_98; // eax
  int pThis_7152; // [esp+4h] [ebp-4h]

  result = *((uint32_t *)this + 1813);  // this+7252〔pTarget7252〕
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
    if ( (uint8_t)result != 0 )
    {
      pThis_715 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1813) + 120))(*((uint32_t *)this + 1813));  // this+7252〔pTarget7252〕
      pThis_7152 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1813) + 124))(*((uint32_t *)this + 1813));  // this+7252〔pTarget7252〕
      v4 = 30094;
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 340))(this) == 60006 )  // 调虚槽 +340：三元组基址（+284，vt+340）
        v4 = 30380;
      pThis_98 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this);  // 调虚槽 +152：效果通道 3
      result = sub_4E4A50(v4, (int)this, v4, 1, pThis_715, pThis_7152, 0, pThis_98, 0, 0, 0);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
      *(this + 8744) = 1;  // this+8744 【推断】主倒计时截止
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C6590 sub_5C6590
// 树精机偶收尾：this+8860（this[2215]）计数清零后转 vt+1312（派生扫描槽），
// 返回其返回值（典型的"清计数 + 调派生"两行模式）
// ------------------------------------------------------------
// 调: sub_5C6590
int /*thiscall*/ sub_5C6590(uint8_t *this)  // 实现：调: sub_5C6590
{
  int v1; // eax

  v1 = *(uint32_t *)this;
  *(this + 8748) = 0;  // this+8748 【推断】子类 AI 尾部槽
  return (*(int (**)(void))(v1 + 1312))();  // 虚函数调用 槽+1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/49…
}



// ------------------------------------------------------------
// 0x5C6640 sub_5C6640
// 树精机偶受击裁决：·0x4E5B50(nArg2, this) 命中成立且攻击方为 17 型时，
// 把攻击方 RTTI cast 成 IRDActiveObject 后经其 vt+760 追加伤害
// （参数 4、1120403456 = 100.0f、参数 10、this 为源）；随后无条件转
// ·0x4DB480(this, pArg2, nArg3, nArg4) 做通用伤害结算
// ------------------------------------------------------------
// 调: sub_5C6640 sub_4E5B50 sub_4DB480
int /*thiscall*/ sub_5C6640(void *this, uint32_t *pArg2, int nArg3, int nArg4)  // 实现：调: sub_5C6640 sub_4E5B50 sub_4DB480
{
  int pObj; // eax

  if ( sub_4E5B50((int)pArg2, (int)this) && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0 )  // 暴击/有效命中判定（研究 20 §5.1 全文定案）
  {
    pObj = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
           (int)pArg2,
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &IRDActiveObject `RTTI Type Descriptor',
           0);
    (*(void (/*thiscall*/ **)(int, int, int, int, void *, uint32_t))(*(uint32_t *)pObj + 760))(pObj, 4, 1120403456, 10, this, 0);  // 调虚槽 +760：状态槽写入(17 槽异常状态)
  }
  return sub_4DB480((int)this, pArg2, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// ------------------------------------------------------------
// 0x5C67B0 sub_5C67B0
// 目标筛型谓词：pArg2 非本尊且其 vt+340 形态码 == 603 时为真
// （与 ·0x5C6560 的 601 同族，603 为另一形态码）
// ------------------------------------------------------------
// 调: sub_5C67B0
bool /*thiscall*/ sub_5C67B0(void *this, void *pArg2)  // 实现：调: sub_5C67B0
{
  return pArg2 != this && *(uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pArg2 + 340))(pArg2) == 603;  // 调虚槽 +340：三元组基址（+284，vt+340）
}



// ------------------------------------------------------------
// 0x5C69A0 sub_5C69A0
// 树精机偶攻击参数面整块清零（正向 + this+7538 置 1 变体）：7531..7558 逐槽 +
// 7564..7596 八槽清零，this+7538 字节写 1（形态门），nArg3==2 取 nArg2 做 nArg32，
// nArg32==0 时 this+7596 写 50
// ------------------------------------------------------------
// 调: sub_5C69A0
int /*thiscall*/ sub_5C69A0(int this, int nArg2, int nArg3)  // 实现：调: sub_5C69A0
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558 【推断】攻击参数面字节槽
  *(uint8_t *)(this + 7557) = 0;  // this+7557 【推断】攻击面门字节
  *(uint8_t *)(this + 7556) = 0;  // this+7556 【推断】攻击面模式字节
  *(uint8_t *)(this + 7534) = 0;  // this+7534 内嵌配置块 +14 字节
  *(uint8_t *)(this + 7533) = 0;  // this+7533 内嵌配置块 +13 字节
  *(uint8_t *)(this + 7532) = 0;  // this+7532 内嵌配置块 +12 字节
  *(uint8_t *)(this + 7531) = 0;  // this+7531 内嵌配置块 +11 字节
  *(uint32_t *)(this + 7535) = 0;  // this+7535 内嵌配置块 +15 字节
  *(uint32_t *)(this + 7539) = 0;  // this+7539 配置块 17 字节循环搬运区起点
  *(uint32_t *)(this + 7543) = 0;  // this+7543 【推断】攻击参数面槽
  *(uint32_t *)(this + 7547) = 0;  // this+7547 【推断】攻击参数面槽
  *(uint32_t *)(this + 7551) = 0;  // this+7551 【推断】攻击参数面槽
  *(uint8_t *)(this + 7555) = 0;  // this+7555 【推断】攻击参数面字节槽
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;  // this+7572 【推断】模式 2 档
  *(uint32_t *)(this + 7568) = 0;  // this+7568 【推断】激活/模式槽
  *(uint32_t *)(this + 7564) = 0;  // this+7564 【推断】形态/模式槽
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580 【推断】攻击面门字节
  *(uint32_t *)(this + 7576) = 0;  // this+7576 相位槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 【推断】段号横向偏置
  *(uint8_t *)(this + 7538) = 1;  // this+7538 内嵌配置块 +18 字节
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    nArg32 = nArg2;
  if ( nArg32 == 0 )  // 若 nArg32 为 0
    *(uint32_t *)(this + 7596) = 50;  // this+7596 【推断】段号横向偏置
  return result;
}



// ------------------------------------------------------------
// 0x5C6AD0 sub_5C6AD0
// 树精机偶消亡收尾：·0x4D9760 观察者广播 + vt+1284 出场/离场动作后，两次
// vt+212 播报——第一次取 this+8624（<0x10 用内联缓冲地址否则用指针，
// 即 std::string SSO 判定）播报 9 号；第二次取 this+8632 同法播报 -1 号
// （两条日志/语音 TAG，字符串内容由调用方预填）【推断】
// ------------------------------------------------------------
// 调: sub_5C6AD0 sub_4D9760
int /*thiscall*/ sub_5C6AD0(uint32_t *this)  // 实现：调: sub_5C6AD0 sub_4D9760
{
  uint32_t *pThis_867; // eax

  sub_4D9760(this);  // 观察者广播后条件收尾
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);  // 调虚槽 +1284
  if ( *(this + 2156) < 0x10u )  // this+8624〔uAI8624(推断)〕
    pThis_867 = this + 2151;
  else  // 否则分支
    pThis_867 = (uint32_t *)*(this + 2151);  // this+8604〔bAI8604(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_867, 9, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
  if ( *(this + 2163) < 0x10u )  // this+8652〔uPhase8652(推断)〕
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, this + 2158, -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
  else  // 否则分支
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t))(*this + 212))(this, *(this + 2158), -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
}



// ------------------------------------------------------------
// 0x5CDA70 sub_5CDA70
// 无参转发桩（attributes: thunk）：转调 ·0x5CD9B0()
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5CDA70 sub_5CD9B0
int sub_5CDA70()  // 实现：调: sub_5CDA70 sub_5CD9B0
{
  return sub_5CD9B0();  // 登场曲与行为字分派
}



// ------------------------------------------------------------
// 0x5CF7D0 sub_5CF7D0
// 事件包取号转发桩（attributes: thunk）：转调 ·0x4DC630(this)（关卡/交互事件包
// 读取器，返回事件号，-1 表示取包失败）
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5CF7D0 sub_4DC630
int /*thiscall*/ sub_5CF7D0(uint32_t *this)  // 实现：调: sub_5CF7D0 sub_4DC630
{
  return sub_4DC630(this);  // 关卡/交互事件包处理（关联对象 this+7260 校验）
}



// ------------------------------------------------------------
// 0x5D7AD0 sub_5D7AD0
// CNHeavenExpeller（天堂驱逐者）构造器：先写虚表 CNHeavenExpeller::vftable
// （RTTI 直证类名），再转 ·0x5D6E40 做基类构造
// ------------------------------------------------------------
// 调: sub_5D7AD0 sub_5D6E40
int /*thiscall*/ sub_5D7AD0(uint32_t *this)  // 函数定义: 本条为该型析构的近邻定义
{
  *this = &CNHeavenExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  return sub_5D6E40();  // 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
}



// ------------------------------------------------------------
// 0x592BF0 sub_592BF0
// 哥布林系子类单字段清零：this+8600 槽写 0（与 ·0x5A36E0 写 600 同槽位，
// 属子类 AI 数据块首槽的复位）
// ------------------------------------------------------------
// 调: sub_592BF0
void /*thiscall*/ sub_592BF0(uint8_t *this)  // 实现：调: sub_592BF0
{
  *(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
}



// ------------------------------------------------------------
// 0x5A1540 sub_5A1540
// 协同攻击令广播桩：转调 ·0x59B130(0)（无本尊参数版本，0 作为首个实参占位）
// ------------------------------------------------------------
// 调: sub_5A1540 sub_59B130
int sub_5A1540()  // 实现：调: sub_5A1540 sub_59B130
{
  return sub_59B130(0);  // 协同攻击令组包发送：遍历场景对象列表筛同族可指挥哥布林并广播命令 13
}



// ------------------------------------------------------------
// 0x5A4090 sub_5A4090
// 牛头系速度槽增向调节（强化）：nArg3==0 时 this+7596 蓄力档写 30，速度槽
// （vt+672(0)+830）读出 +0.3 经 ·0x41A590 写回并 vt+676 应用；nArg3 其余值原样返回
// ------------------------------------------------------------
// 调: sub_5A4090 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5A4090(uint32_t *this, int nArg2, int nArg3)  // 实现：调: sub_5A4090 sub_41A5E0 sub_41A590
{
  int result; // eax
  int v5; // eax
  unsigned int v6; // edi
  int v7; // edx
  int v8; // [esp+10h] [ebp+Ch]

  result = nArg3;
  if ( nArg3 == 0 )  // 若 nArg3 为 0
  {
    v5 = *this;
    *(this + 1899) = 30;  // this+7596〔nOffset7596(推断)〕
    v6 = (*(int (/*stdcall*/ **)(uint32_t))(v5 + 672))(0) + 830;  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v6)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v6, v7, v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AA340 sub_5AA340
// 飞龙单字段清零：this+8604（this[2151]）槽写 0——与 ·0x5AA350 的"销毁并清槽"
// 配对（本函数只清不销毁）
// ------------------------------------------------------------
// 调: sub_5AA340
void /*thiscall*/ sub_5AA340(uint32_t *this)  // 实现：调: sub_5AA340
{
  *(this + 2151) = 0;  // this+8604〔bAI8604(推断)〕
}



// ------------------------------------------------------------
// 0x5AA3F0 sub_5AA3F0
// 对象消亡钩子（含自消亡判定）：先 ·0x4D9170(pArg2) 做通用消亡登记；
// 若消亡者恰是本尊（pArg2 == this）则 vt+216(this, 45230) 写 45230 号参数
// （本尊消亡时的收尾参数，语义未定【待验证】）
// ------------------------------------------------------------
// 调: sub_5AA3F0 sub_4D9170
int /*thiscall*/ sub_5AA3F0(void *this, void *pArg2)  // 实现：调: sub_5AA3F0 sub_4D9170
{
  int result; // eax

  result = sub_4D9170(pArg2);  // result = 调 sub_4D9170 返回值
  if ( pArg2 == this )  // 若 pArg2 == this
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 45230);  // 调虚槽 +216：音效 TAG 查询
  return result;
}



// ------------------------------------------------------------
// 0x5AA6A0 sub_5AA6A0
// 飞龙待机行为掷点（双时钟门，与 ·0x5AA750 同族）：本尊时钟 this+8720 到期
// （≥this+8744）即刻过门，或次时钟 this+8748 到期且 pszArg2==1（外部触发）时重入；
// 门内不做概率分支，直接从候选表 this+8708..8712（同 ·0x4A8350 推入的 15/80/135
// 三项）随机取一项写 this+324（朝向档）；末了清 this+8733/8734 两门、
// 本尊时钟置 10 秒冷却、this+8761/8762 清零、次时钟置 3 秒冷却
// ------------------------------------------------------------
// 调: sub_5AA6A0 sub_699000 sub_698F90
char /*thiscall*/ sub_5AA6A0(int this, char pszArg2)  // 实现：调: sub_5AA6A0 sub_699000 sub_698F90
{
  int nCountdown8744; // ebx  | +0x2228 → 【推断】主倒计时截止〔5AA6A0：clock_now(8720) >= 此值 → 重抽 + 10000ms 上弦〕（CNFlyDragon；va=005AA6A0）
  int pThis_2210; // edi
  int nAltDeadline8772; // ebx  | +0x2244 → 【推断】备用倒计时截止〔5AA6A0：clock_now(8748) >= 此值且参=1 亦重抽 + 3000ms（CNFlyDragon；va=005AA6A0）
  int v6; // eax
  int pCandTbl8708; // eax  | +0x2204 → 【推断】候选表首针（4 字节元素；4A8350 构造推入 15/80/135 三项）〔5AA6A0 随机抽取源〕（CNFlyDragon；va=005AA6A0）
  unsigned int nCandTblEnd8712; // ebx  | +0x2208 → 【推断】候选表尾针（元素数=(8712-8708)>>2）〔5AA6A0 rand()%n 上界〕（CNFlyDragon；va=005AA6A0）

  nCountdown8744 = *(uint32_t *)(this + 8744);  // fld_2228 = 读 this+8744
  pThis_2210 = this + 8720;  // this+8720〔pSegThrTbl8720〕
  if ( sub_699000(this + 8720) >= nCountdown8744 || (nAltDeadline8772 = *(uint32_t *)(this + 8772), (v6 = sub_699000(this + 8748)) >= nAltDeadline8772) && pszArg2 == 1 )  // 【clock_now(clk)】
  {
    pCandTbl8708 = *(uint32_t *)(this + 8708);  // fld_2204 = 读 this+8708
    if ( pCandTbl8708 != 0 )  // 若 fld_2204 非 0
      nCandTblEnd8712 = (*(uint32_t *)(this + 8712) - pCandTbl8708) >> 2;  // this+8712 【推断】候选表尾针
    else  // 否则分支
      nCandTblEnd8712 = 0;
    *(uint32_t *)(this + 324) = *(uint32_t *)(*(uint32_t *)(this + 8708) + 4 * (rand() % nCandTblEnd8712));  // this+324〔nRandPick324〕
    *(uint8_t *)(pThis_2210 + 13) = 0;
    *(uint8_t *)(pThis_2210 + 14) = 0;
    sub_698F90(pThis_2210, 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(uint8_t *)(this + 8761) = 0;  // this+8761〔bAI8761〕
    *(uint8_t *)(this + 8762) = 0;  // this+8762〔bAI8762〕
    LOBYTE(v6) = sub_698F90(this + 8748, 3000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return v6;
}



// ------------------------------------------------------------
// 0x5AAA20 sub_5AAA20
// 飞龙"高空龙吟"起手（与 ·0x5AAED0 同构，差异：this+8612 段相位清 0、
// 动画表项取 this+6216+44、vt+344 偏移 +608、标志槽 this+8701，
// 关联对象 +12 槽写 600.0f 位型 1142292480 = 0x44160000）——
// 同样：this+8620 抄朝向、this+8628 动作号（4→5）、this+8632 写 vt+188、
// 速度槽 (816×830)×1.5 写双组 vt+876、·0x495890(0,200)、vt+196 选帧与
// ·0x4926A0 帧游标复位、vt+344 写偏移，末了播报 FLYDRAGON_CRY
// ------------------------------------------------------------
// 证: "FLYDRAGON_CRY"
// 调: sub_5AAA20 sub_41A5E0 sub_495890 sub_4926A0
int /*thiscall*/ sub_5AAA20(uint32_t *this)  // 实现：调: sub_5AAA20 sub_41A5E0 sub_495890 sub_4926A0
{
  int v2; // edx
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edi
  int v7; // edi
  uint64_t v8; // rax
  uint32_t *fld_e28; // edi
  int v10; // eax
  int v11; // eax
  int v13; // [esp+Ch] [ebp-Ch]
  float v14; // [esp+10h] [ebp-8h]
  int v15; // [esp+14h] [ebp-4h]

  v2 = *this;
  *(this + 2155) = *(this + 81);  // this+8620〔uAI8620(推断)〕等 2 字段
  if ( (*(int (**)(void))(v2 + 184))() == 4 )  // 虚函数调用 槽+184：动画对象 z 倾斜转状态码
    v3 = 5;
  else  // 否则分支
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this);  // 调虚槽 +184：动画对象 z 倾斜转状态码
  v4 = *this;
  *(this + 2157) = v3;  // this+8628〔nPoolTime(推断)〕
  *(this + 2158) = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 188))(this);  // 虚函数调用 槽+188：动画对象 z 倾斜转状态码
  v5 = *this;
  *(this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 672))(this, 3);  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
  v15 = sub_41A5E0(v6 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v14 = COERCE_FLOAT(sub_41A5E0(v6 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v13 = sub_41A5E0(v7 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v8 = (uint64_t)((double)(int)(uint64_t)((double)v13 * COERCE_FLOAT(sub_41A5E0(v7 + 830))) * 1.5);  // crypt4byte 解密校验（·0x41A590 逆运算）
  (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    this,
    HIDWORD(v8),  // 调 取 64 位值高 32 位
    0,
    v8,
    (uint64_t)((double)(int)(uint64_t)((double)v15 * v14) * 1.5),
    0,
    0,
    0);
  fld_e28 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  if ( *fld_e28 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0 && fld_e28[6] != 1142292480 )  // 复合条件判定（与/或）
  {
    fld_e28[6] = 1142292480;  // 浮点常量 600f
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 200);  // 模式选择式方位设置（1/2/其他 三分支）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 44));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  sub_4926A0(v10);  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 608);  // 调虚槽 +344：取坐标三元组
  v11 = *this;
  *((uint8_t *)this + 8701) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v11 + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
           this,
           "FLYDRAGON_CRY",  // 资源/动画 TAG FLYDRAGON_CRY
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5AAE70 sub_5AAE70
// 飞龙"撕咬"起手（简式）：vt+344 写偏移（this+556+152）、this+8608 门置 1、
// vt+196 取帧表首项、·0x4926A0 复位帧游标、播报 FLYDRAGON_BITE；
// 与 ·0x5AB4A0 的区别是本函数不配置 3 个子对象句柄与冷却时钟
// ------------------------------------------------------------
// 证: "FLYDRAGON_BITE"
// 调: sub_5AAE70 sub_4926A0
int /*thiscall*/ sub_5AAE70(uint32_t *this)  // 实现：调: sub_5AAE70 sub_4926A0
{
  uint32_t *fld_e1554; // eax
  int v3; // edx
  int v4; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152);  // 调虚槽 +344：取坐标三元组
  fld_e1554 = (uint32_t *)*(this + 1554);  // this+6216〔pTbl6216(推断)〕
  v3 = *this;
  *((uint8_t *)this + 8608) = 1;  // this+8608〔门置〕
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 196))(this, *fld_e1554);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  sub_4926A0(v4);  // 帧游标复位（+44 帧数组；递归子链 +204）
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
           this,
           "FLYDRAGON_BITE",  // 资源/动画 TAG FLYDRAGON_BITE
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5AB180 sub_5AB180
// 飞龙"落地/振翅收势"步进（相位 this+8616 两态机）：相位 1 且动画播完（+170）时
// vt+604(0) 收招且可行动则 setState 0 归地；相位 0 且高度 ==0 时进入落地配置——
// 关联对象 +24/+36 两槽清零、vt+876 双组归零、按 this+8700 标志选帧表项
// this+6216+20（置 500 帧长）或不置（2000 帧长），并额外配置 +24/+28 与
// +36/+40 四个帧表项经 vt+204 以 −100 / +100 / −200 / +200 四组参数启动；
// 末了相位写 1 并经 vt+80 取父对象 +132 交 ·0x424120(obj,2,300) 收尾
// ------------------------------------------------------------
// 调: sub_5AB180 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
int /*usercall*/ sub_5AB180@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 实现：调: sub_5AB180 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
{
  int result; // eax
  int v4; // edi
  int v5; // edi
  int v6; // edx
  int v7; // eax

  result = pArg1[2154];  // result = 取 pArg1[2154]
  if ( result != 0 )  // 若结果非 0（成功）
  {
    if ( result == 1 )  // 若 result == 1
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);  // 调虚槽 +200：取动画对象
      if ( *(uint8_t *)(result + 170) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 604))(pArg1, 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
        if ( (uint8_t)result != 0 )
          return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      }
    }
  }
  else  // 否则分支
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    if ( result == 0 )  // 若 result 为 0
    {
      *(uint32_t *)(pArg1[28] + 24) = 0;
      *(uint32_t *)(pArg1[28] + 36) = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        pArg1,
        0,
        0,
        0,
        0,
        0,
        0,
        nArg2);  // （上一调用/表达式的参数续行）
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      if ( *((uint8_t *)pArg1 + 8700) != 0 )
      {
        *(uint32_t *)(sub_4924C0(0) + 48) = 500;  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
        v5 = *(uint32_t *)(pArg1[1554] + 20);
        sub_4910E0(v5);  // 帧时刻推进（返回 1 表示时刻发生位移）
        sub_493A60(v5, *(uint32_t *)(v5 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 20));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 20));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      }
      else  // 否则分支
      {
        *(uint32_t *)(sub_4924C0(0) + 48) = 2000;  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
        v4 = *(uint32_t *)(pArg1[1554] + 20);
        sub_4910E0(v4);  // 帧时刻推进（返回 1 表示时刻发生位移）
        sub_493A60(v4, *(uint32_t *)(v4 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 20));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 20));  // 调虚槽 +196：动画对象设置（换域 + 播放）
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 24));  // 帧游标复位（+44 帧数组；递归子链 +204）
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 28));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 204))(  // 调虚槽 +204：定时器插入
          pArg1,
          -100,
          *(uint32_t *)(pArg1[1554] + 24),
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 204))(  // 调虚槽 +204：定时器插入
          pArg1,
          100,
          *(uint32_t *)(pArg1[1554] + 28),
          0,
          0,
          0,
          0);
      }
      sub_4926A0(*(uint32_t *)(pArg1[1554] + 36));  // 帧游标复位（+44 帧数组；递归子链 +204）
      sub_4926A0(*(uint32_t *)(pArg1[1554] + 40));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 204))(  // 调虚槽 +204：定时器插入
        pArg1,
        -200,
        *(uint32_t *)(pArg1[1554] + 36),
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 204))(  // 调虚槽 +204：定时器插入
        pArg1,
        200,
        *(uint32_t *)(pArg1[1554] + 40),
        0,
        0,
        0,
        0);
      v6 = *pArg1;
      pArg1[2154] = 1;
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 80))(pArg1);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      return sub_424120(*(uint32_t **)(v7 + 132), 2, 300);  // 标签入口（解析器 sub_502F00 调用，全库 36 调用者）。
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AB5B0 sub_5AB5B0
// 飞龙攻击段收招瞬间（清冷却 + 推进表现）：this+8612 时钟立即到期
// （sub_698F90(...,0,0) 把倒计时清零，相当于冷却刷新为 0），·0x4926A0 复位
// 帧表首项游标，末了 vt+204(this, 100, 帧表首项, 0,0,0,0) 启动下一次表现
// ------------------------------------------------------------
// 调: sub_5AB5B0 sub_698F90 sub_4926A0
int /*thiscall*/ sub_5AB5B0(int **this)  // 实现：调: sub_5AB5B0 sub_698F90 sub_4926A0
{
  int pThis_869; // ecx

  pThis_869 = (int)(this + 2153);  // this+8612〔uAI8612(推断)〕
  *(uint8_t *)(pThis_869 + 13) = 0;
  *(uint8_t *)(pThis_869 + 14) = 0;
  sub_698F90(pThis_869, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  sub_4926A0(**(this + 1554));  // 帧游标复位（+44 帧数组；递归子链 +204）
  return ((int (/*thiscall*/ *)(int **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
           this,
           100,
           **(this + 1554),  // this+6216〔pTbl6216(推断)〕
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5AB800 sub_5AB800
// 飞龙 setState 基类落地（userpurge：ecx=本尊，fArg2 由 st0 传参）：
// 先记旧大状态 v7 = this+6556、this+8696 冷却窗写 1000，再转 ·0x4E33D0 走
// 通用落态流程；ArgList != 5 时按"新旧态对"追加清理——
//   ArgList==3：vt+1308(1)（姿态收尾）；
//   旧态 !=14 且 新态 ==14（进低空扑咬）：vt+196 取帧表项 this+6216+16、
//   ·0x4926A0 复位当前与 this+6216+32 游标、vt+204(100, this+6216+32) 起表现、
//   vt+876 双组参数归零；
//   旧态 !=16 且 新态 ==16（进高空扑咬）：同上但帧表项取 this+6216+48；
//   旧态 ==14 且 新态 !=14（退低空扑咬）：转 ·0x5AB060 起高空段的收势；
//   旧态 ==16 且 新态 !=16（退高空扑咬）：转 ·0x5AAD10
// ------------------------------------------------------------
// 调: sub_5AB800 sub_4E33D0 sub_4926A0 sub_5AB060 sub_5AAD10
void /*userpurge*/ sub_5AB800(int *pDwArg1@<ecx>, double fArg2@<st0>, int ArgList, int nArg4, int nArg5, int nArg6)  // 实现：调: sub_5AB800 sub_4E33D0 sub_4926A0 sub_5AB060 sub_5AAD10
{
  int v7; // edi
  int v8; // eax
  int v9; // eax

  v7 = pDwArg1[1639];  // v7 = 取 pDwArg1[1639]
  pDwArg1[2174] = 1000;
  sub_4E33D0(pDwArg1, ArgList, fArg2, ArgList, nArg4, *(float *)&nArg5, *(float *)&nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList != 5 )  // 若 ArgList != 5
  {
    if ( ArgList == 3 )  // 若 ArgList == 3
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1308))(pDwArg1, 1);  // 调虚槽 +1308：CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
    if ( v7 != 14 && ArgList == 14 )  // 若 v7 != 14 与/或 ArgList == 14
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 16));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      v8 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调虚槽 +200：取动画对象
      sub_4926A0(v8);  // 帧游标复位（+44 帧数组；递归子链 +204）
      sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 32));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(  // 调虚槽 +204：定时器插入
        pDwArg1,
        100,
        *(uint32_t *)(pDwArg1[1554] + 32),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    }
    if ( v7 != 16 && ArgList == 16 )  // 若 v7 != 16 与/或 ArgList == 16
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 48));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      v9 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调虚槽 +200：取动画对象
      sub_4926A0(v9);  // 帧游标复位（+44 帧数组；递归子链 +204）
      sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 32));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(  // 调虚槽 +204：定时器插入
        pDwArg1,
        100,
        *(uint32_t *)(pDwArg1[1554] + 32),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    }
    if ( v7 == 14 )  // 若 v7 == 14
    {
      if ( ArgList != 14 )  // 若 ArgList != 14
        sub_5AB060(pDwArg1);  // 飞龙「高空扑咬「攻击段起手——同样把 this+6172 动画对象 +48 帧长 ÷10
    }
    else if ( v7 == 16 && ArgList != 16 )
    {
      sub_5AAD10(pDwArg1);  // 飞龙「低空扑咬「攻击段起手（段相位 2）：把朝向档 this+324 抄入 this+8
    }
  }
}



// ------------------------------------------------------------
// 0x5ABCC0 sub_5ABCC0
// 飞龙落地/起跳判定（叠加 ·0x5AB9B0 总步进）：大状态 ==8 且分型 ·0x41A5E0==1 且
// 冷却时钟 this+8784 已计时（clock_now >0）时，若帧表项 this+6216+32 的动画
// 播完标志（+170）为 1 则经 vt+876 写 (1400,...) 高度参数（起飞/落地速度，
// 后续参数见完整函数体）【推断：落地-起跳高度曲线】
// ------------------------------------------------------------
// 调: sub_5ABCC0 sub_5AB9B0 sub_41A5E0 sub_699000
int /*thiscall*/ sub_5ABCC0(uint8_t *this)  // 实现：调: sub_5ABCC0 sub_5AB9B0 sub_41A5E0 sub_699000
{
  int result; // eax
  int pThis_612; // eax
  int v4; // ecx
  int v5; // edi
  int pThis_98; // eax

  sub_5AB9B0();  // 段 2 且动画帧走完调 ·0x5AAED0
  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result == 8 )  // 若 result == 8
  {
    result = sub_41A5E0((unsigned int)(this + 7028));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )  // 若 result == 1
    {
      result = sub_699000((int)(this + 8784));  // 【clock_now(clk)】
      if ( result > 0 )  // 若 result > 0
      {
        pThis_612 = *((uint32_t *)this + 1554);  // this+6216〔pTbl6216(推断)〕
        v4 = *(uint32_t *)(pThis_612 + 32);  // this+32 格子像素尺寸
        result = pThis_612 + 32;
        if ( *(uint8_t *)(v4 + 170) == 1 )
        {
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
            this,
            0,
            1400,
            1400,
            0,
            -4000,
            1);
          (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
            this,
            1,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int))(*(uint32_t *)this + 888))(this, 2, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
          v5 = *(uint32_t *)this;
          pThis_98 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 152))(this, 4);  // 调虚槽 +152：效果通道 3
          result = (*(int (/*thiscall*/ **)(uint8_t *, int))(v5 + 896))(this, pThis_98);  // 虚函数调用 槽+896：默认虚槽桩（11 行 return）
          *(this + 8797) = 0;
          *(this + 8798) = 0;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AC000 sub_5AC000
// 飞龙"低空扑咬"锁定循环（叠加 ·0x5AB9B0 总步进）：相位 this+8804 !=18（未扑咬）
// 时清 this+8816 标志直接返回；相位 ==18 时循环 3 次（v3=0..2）遍历
// this+8816/8820/8824 三个子对象句柄（·0x5AB4A0 存的），逐个校验其关联对象
// （this+224 槽）是否可行动、位置差是否在判定内，命中则记录并推进【推断：
// 三段咬合点轮询】
// ------------------------------------------------------------
// 调: sub_5AC000 sub_5AB9B0
int /*thiscall*/ sub_5AC000(char *this)  // 实现：调: sub_5AC000 sub_5AB9B0
{
  int result; // eax
  int v3; // ebx
  int *pThis_1C; // edi
  int pObj; // ecx
  bool v6; // zf
  double v7; // st7
  int v8; // edx
  int pThis_89B; // eax
  int v10; // [esp+4h] [ebp-8h]
  int *pThis_2270; // [esp+8h] [ebp-4h]

  result = sub_5AB9B0();  // result = 调 sub_5AB9B0 返回值
  if ( *((uint32_t *)this + 2201) != 18 )
  {
LABEL_11:  // 标签 LABEL_11（跳转合流点）
    *(this + 8808) = 0;
    return result;
  }
  v3 = 0;
  pThis_2270 = (int *)(this + 8816);  // this+8816 蓄力计时戳
  do  // do-while 循环体起点
  {
    pThis_1C = *((int **)this + 28);  // this+28 【推断】逐帧驱动对象
    pObj = *pThis_1C;
    v6 = *pThis_1C == 0;
    v10 = *pThis_2270;
    *((uint8_t *)pThis_1C + 124) = 1;
    if ( !v6 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      v7 = (double)v10;
      if ( *(float *)&pThis_1C[v3 + 1] != v7 )
      {
        *(float *)&pThis_1C[v3 + 1] = v7;
        *((uint8_t *)pThis_1C + 196) = 1;
      }
    }
    ++v3;
    ++pThis_2270;
  }
  while ( v3 < 3 );  // 条件循环
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 144))(this, *((uint32_t *)this + 2207));  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
  v8 = *(uint32_t *)this;
  if ( *(this + 8808) == 1 )
  {
    result = (*(int (/*thiscall*/ **)(char *))(v8 + 200))(this);  // 虚函数调用 槽+200：取动画对象
    if ( *(int *)(result + 148) <= 2 )
      return result;
    pThis_89B = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 2203) + 28))(*((uint32_t *)this + 2203));  // 虚函数调用 槽+28：生成装配：Character/Mage/Effect/Animation/Fol…
    result = (*(int (/*thiscall*/ **)(char *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
               this,
               50806,
               0,
               pThis_89B,
               0,
               50,
               0,
               20,
               4,
               0,
               0,
               0);
    goto LABEL_11;
  }
  result = (*(int (/*thiscall*/ **)(char *, uint32_t))(v8 + 208))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 16));  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
  *((uint32_t *)this + 1639) = 0;  // this+6556〔大状态ID〕
  *((uint32_t *)this + 2201) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x5AFCC0 sub_5AFCC0
// 龙人伤害修正钩子：先走 ·0x4E6770 九步伤害流水线（vt+628，研究 P14），
// 若 *uArg2（伤害类型/标记字节）非 0 则结果 ×2（该伤害类型下翻倍）
// ------------------------------------------------------------
// 调: sub_5AFCC0 sub_4E6770
int /*thiscall*/ sub_5AFCC0(uint32_t *this, uint8_t *uArg2, uint32_t *uArg3, int nArg4, int *pDwArg5, float *pArg6, int nArg7)  // 实现：调: sub_5AFCC0 sub_4E6770
{
  int result; // eax

  result = sub_4E6770(this, uArg2, uArg3, nArg4, pDwArg5, pArg6, 0);  // 【伤害流水线 vt+628（研究 P14 九步公式）】
  if ( *uArg2 != 0 )
    result *= 2;
  return result;
}



// ------------------------------------------------------------
// 0x5AFE40 sub_5AFE40
// 全局白名单查询（cdecl 单参）：遍历 dword_9B9424..dword_9B9428 的 4 字节元素
// 动态数组，任一元素 == nArg1 即返回 1，否则 0——进程级 ID 白名单/黑名单
// 【推断：用于判定该 ID 是否属本怪有效目标/物品】
// ------------------------------------------------------------
// 调: sub_5AFE40
char /*cdecl*/ sub_5AFE40(int nArg1)  // 实现：调: sub_5AFE40
{
  unsigned int i; // edx

  for ( i = 0; dword_9B9424 != 0 && i < (dword_9B9428 - dword_9B9424) >> 2; ++i )  // 遍历循环
  {
    if ( *(uint32_t *)(dword_9B9424 + 4 * i) == nArg1 )
      return 1;  // 返回 1(成功)
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5B1BA0 sub_5B1BA0
// 光之领主行为字相位机（与 ·0x5AFCF0 同族，差异：返回值以行为字−4 起算，
// 行为字 0 无登场分支）——·0x4E0120 基类前置后按 this+7148 分发：
//   4 有宿主 10% → 写 5，无宿主落 13；5 有宿主 30% → 落 4，无宿主落 13；
//   13/14/15 有宿主 → 回写 4
// ------------------------------------------------------------
// 调: sub_5B1BA0 sub_4E0120
int /*thiscall*/ sub_5B1BA0(int *this)  // 函数定义: 帧前处理
{
  int result; // eax
  int nRand2; // eax
  int nRoll; // et2  rand()%100 掷点（行为字 5 处）
  int nRand; // eax
  int nRoll2; // et2  rand()%100 掷点（行为字 4 处）

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787) - 4;  // this+7148〔nBigState〕
  switch ( *(this + 1787) )  // this+7148〔nBigState〕
  {
    case 4:  // 待机：无宿主落 13，有宿主 10% 出击
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_8;
      nRand = rand();  // nRand = 调 rand
      nRoll2 = nRand % 100;
      result = nRand / 100;
      if ( nRoll2 < 10 )  // 若 nRoll2 < 10
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 5:  // 出击：无宿主落 13，有宿主 30% 回待机
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
      {
        nRand2 = rand();  // nRand2 = 调 rand
        nRoll = nRand2 % 100;
        result = nRand2 / 100;
        if ( nRoll < 30 )  // 若 nRoll < 30
          goto LABEL_12;
      }
      else  // 否则分支
      {
LABEL_8:  // 标签 LABEL_8（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      }
      break;  // 跳出循环/分支
    case 13:  // 追敌
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
        goto LABEL_12;
      break;  // 跳出循环/分支
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_12:  // 标签 LABEL_12（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 回写待机 4
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B1EC0 sub_5B1EC0
// 光之领主伤害减免钩子：先走 ·0x4DC390(pDwArg2, nArg3) 通用伤害前置；若其
// 返回值非 3（非该特例伤害类型）且 this+8644 减免门开着，则把伤害值 *pDwArg2
// 乘 0.7（−30% 减伤），并调 nArg3 对象的 vt+348（受击反馈），返回 0 表示已处理
// ------------------------------------------------------------
// 调: sub_5B1EC0 sub_4DC390
int /*thiscall*/ sub_5B1EC0(uint8_t *this, int *pDwArg2, int nArg3)  // 实现：调: sub_5B1EC0 sub_4DC390
{
  int result; // eax

  result = sub_4DC390(pDwArg2, nArg3);  // 伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
  if ( result != 3 && *(this + 8644) != 0 )  // 若 result != 3
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3);  // 调虚槽 +348：取坐标对象
    *pDwArg2 = (uint64_t)((double)*pDwArg2 * 0.69999999);
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B4C30 sub_5B4C30
// 光之领主攻击参数面整块清零（正向 + this+7580 置 1 变体）：7531..7558 逐槽 +
// 7564..7596 清零，this+7580 槽写 1（形态/档位门，与 ·0x5C6700 写 7537、
// ·0x5C69A0 写 7538 是同族不同槽的变体）；nArg3==2 取 nArg2 做 nArg32，
// nArg32==0 时 this+7596 写 50（正向满档）
// ------------------------------------------------------------
// 调: sub_5B4C30
int /*thiscall*/ sub_5B4C30(int this, int nArg2, int nArg3)  // 实现：调: sub_5B4C30
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558 【推断】攻击参数面字节槽
  *(uint8_t *)(this + 7557) = 0;  // this+7557 【推断】攻击面门字节
  *(uint8_t *)(this + 7556) = 0;  // this+7556 【推断】攻击面模式字节
  *(uint8_t *)(this + 7534) = 0;  // this+7534 内嵌配置块 +14 字节
  *(uint8_t *)(this + 7533) = 0;  // this+7533 内嵌配置块 +13 字节
  *(uint8_t *)(this + 7532) = 0;  // this+7532 内嵌配置块 +12 字节
  *(uint8_t *)(this + 7531) = 0;  // this+7531 内嵌配置块 +11 字节
  *(uint32_t *)(this + 7535) = 0;  // this+7535 内嵌配置块 +15 字节
  *(uint32_t *)(this + 7539) = 0;  // this+7539 配置块 17 字节循环搬运区起点
  *(uint32_t *)(this + 7543) = 0;  // this+7543 【推断】攻击参数面槽
  *(uint32_t *)(this + 7547) = 0;  // this+7547 【推断】攻击参数面槽
  *(uint32_t *)(this + 7551) = 0;  // this+7551 【推断】攻击参数面槽
  *(uint8_t *)(this + 7555) = 0;  // this+7555 【推断】攻击参数面字节槽
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;  // this+7572 【推断】模式 2 档
  *(uint32_t *)(this + 7568) = 0;  // this+7568 【推断】激活/模式槽
  *(uint32_t *)(this + 7564) = 0;  // this+7564 【推断】形态/模式槽
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580 【推断】攻击面门字节
  *(uint32_t *)(this + 7576) = 0;  // this+7576 相位槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 【推断】段号横向偏置
  *(uint32_t *)(this + 7580) = 1;  // 形态/档位门（同族变体：7537 / 7538 / 7580 三处）
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    nArg32 = nArg2;
  if ( nArg32 == 0 )  // 若 nArg32 为 0
    *(uint32_t *)(this + 7596) = 50;  // 正向满档
  return result;
}



// ------------------------------------------------------------
// 0x5B4D90 sub_5B4D90
// 海星族受击后反击包（三处概率掷点，RTTI 分型决定弹幕强度）：
//   1) 可行动 且 rand()%100<10：调 this+8600 槽对象（this+2150）的虚表首槽
//      ——以（this, this+7256）为参的委托回调【推断：受击委托/反击回调】；
//   2) 再判可行动、目标 vt+348 结构 +12 槽为 0（目标未架招）、rand()%100<15 且
//      RTTI 判型为 CNStarFishKing 时，调 ·0x5B4A50(1,1,-1,-1) 撒弹幕（参数全自动）；
// 主体先转 ·0x4DA3B0(nArg2,nArg3,nArg4) 通用受击结算；
//   3) 若 vt[184] 动作号 >0、可行动、目标 vt+348 结构 +128 字节 ==1、
//      this+8636 槽 ==0xFFFF、rand()%100<2 且 RTTI 判型为 CNStarFishRukuku 时，
//      以 vt[85] 返回的参指针（首元素作弹种）调 ·0x5B4A50(1,1,弹种,-1)
// ------------------------------------------------------------
// 调: sub_5B4D90 sub_5B4A50 sub_4DA3B0
int /*thiscall*/ sub_5B4D90(void (/*thiscall*/ ***this)(int, void *, uint32_t), int nArg2, int nArg3, int nArg4)  // 【一类的覆写仅存在于 0x59-0x5B 段（见各文件头）】
{
  int v5; // edi
  uint32_t *v6; // eax

  if ( ((uint8_t (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[77])(this) != 0
    && rand() % 100 < 10 )  // 调 取伪随机数
  {
    (**(this + 2150))((int)(this + 2150), this, *(this + 1814));  // 虚函数调用 槽+2150
  }
  if ( ((uint8_t (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[77])(this) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) == 0  // 调虚槽 +348：取坐标对象
    && rand() % 100 < 15  // 调 取伪随机数
    && __RTDynamicCast((int)this, 0, &CNStarFish `RTTI Type Descriptor', &CNStarFishKing `RTTI Type Descriptor', 0) != 0 )  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
  {
    sub_5B4A50(1, 1, -1, -1);
  }
  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);  // 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
  if ( ((int (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[184])(this) > 0
    && ((uint8_t (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[77])(this) != 0
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 128) == 1  // 调虚槽 +348：取坐标对象
    && *(this + 2159) == (void (/*thiscall*/ **)(int, void *, uint32_t))0xFFFF  // this+8636〔pDollTarget(推断)〕
    && rand() % 100 < 2  // 调 取伪随机数
    && __RTDynamicCast((int)this, 0, &CNStarFish `RTTI Type Descriptor', &CNStarFishRukuku `RTTI Type Descriptor', 0) != 0 )  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
  {
    v6 = (uint32_t *)((int (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[85])(this);
    sub_5B4A50(1, 1, *v6, -1);
  }
  return v5;
}



// ------------------------------------------------------------
// 0x5B5390 sub_5B5390
// 海星王"吸附/吞噬"（ZGM_ATTACH）主例程（usercall：ecx=本尊，nArg2/nArg3 寄存器参）：
// 宿主 this+8612 为空则直接 setState 15（无事可做）；
// 宿主大状态 !=9 时：本尊不可行动则原样返回，宿主动作 !=5 则叫宿主进态 9
// （吸附目标侧），否则本尊 setState 15（放弃）；
// 宿主已处于 9 且其动画播完（+170）时：先清 v24/v25/pBuf 三槽并以
// ·0x5B4ED0(&v24,&v25,pBuf) 解算发射点三元组，交 ·0x4E5F70(nArg2, 本尊, 宿主,
// &v24, 1, 1) 触发吸附表现，播报 ZGM_ATTACK；随后吸附计数 this+8612 为 0 且
// RTTI 判型 CNStarFishKing 时按 20% 概率追加 ·0x5B4A50(1,1,-1,-1) 弹幕与
// 宿主 vt+760 附加伤害（15 号、10.0f 位型 1106247680、参数 7）；
// 吸附计数 this+8612 自增并与上限 this+8614 比较，达标或宿主 vt+724 判定成立
// 则收尾——再分型（·0x41A5E0==2 且宿主 vt+40(obj,529) 且 ·0x5B4A00 白名单）
// 时把宿主 vt+732(0,0,1)，new 0x80 经 ·0x4D6810 造参对象并以 vt+56 挂接本尊、
// vec/速度面经 vt+672/vt+676 与 ·0x4AED60 配置，this+8632 置 1（吞噬态）；
// 计数未达上限时宿主 vt+772(obj,5) 且可行动则 vt+764(5,0,本尊,1) 续吸；
// 达标后 RTTI 再分型 CNStarFishDevourer 走宿主 vt+760 的 11 号 100.0f 一击，
// 否则（分型≠6）走 5 号 100.0f；末了本尊 setState 15 结束；
// 未达标则 ·0x4926A0 复位帧游标；
// 末段统一收尾：宿主 vt+604(0)、vt+612(1,1)，以本尊 vt+128 → vt+124 → vt+120
// 链反算出吸附位置写宿主 vt+112（宿主被搬到本尊坐标上），宿主朝向写
// ·0x432E50(本尊 vt+152)【推断：海星王吞吸玩家的搬运链】
// ------------------------------------------------------------
// 证: "ZGM_ATTACK" | "ZGM_ATTACH"
// 调: sub_5B5390 sub_5B4ED0 sub_4E5F70 sub_5B4A50 sub_41A5E0
int /*usercall*/ sub_5B5390@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：调: sub_5B5390 sub_5B4ED0 sub_4E5F70 sub_5B4A50 sub_41A5E0
{
  int pObj; // ecx
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  uint8_t *pMem; // edi
  int v9; // ebx
  uint8_t *v10; // eax
  int v11; // edx
  int pObj2; // eax
  int v13; // ebx
  int pObj3; // edi
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // eax
  int result; // eax
  int v22; // [esp+4Ch] [ebp-40h]
  float v23; // [esp+5Ch] [ebp-30h]
  int v24; // [esp+60h] [ebp-2Ch] BYREF
  int v25; // [esp+64h] [ebp-28h] BYREF
  void *pBuf[5]; // [esp+68h] [ebp-24h] BYREF
  int v27; // [esp+7Ch] [ebp-10h]
  int v28; // [esp+88h] [ebp-4h]

  pObj = pDwArg1[2152];  // pObj = 取 pDwArg1[2152]
  if ( pObj == 0 )  // 若 pObj 为 0
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 15, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) != 9 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 308))(pDwArg1[2152]);  // 虚函数调用 槽+308
    if ( (uint8_t)result == 0 )
      return result;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 840))(pDwArg1[2152]) != 5 )  // 虚函数调用 槽+840：大状态 getter（this+6556）
      return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2152] + 560))(pDwArg1[2152], 9, 0, 0, 0);  // 虚函数调用 槽+560：受击反应 setState / vt+560（研究 20 §1.
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 15, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  }
  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 200))(pDwArg1, nArg3, nArg2) + 170) != 0 )  // 调虚槽 +200：取动画对象
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      v24 = 0;
      v25 = 0;
      memset(pBuf, 0, 16);  // 清零 pBuf 起 16 字节
      sub_5B4ED0(&v24, &v25, pBuf);  // 齐格激光/火种发射点解算：目标 this+8612（关联对象）分两族—— · 该对象 v
      sub_4E5F70(nArg2, (int)pDwArg1, pDwArg1[2152], (float *)&v24, 1, 1);  // 硬直率掷（研究 §5.1 第 14 轮定案：同构于暴击掷）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_ATTACK", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    }
    if ( pDwArg1[2153] == 0
      && __RTDynamicCast((int)pDwArg1, 0, &CNStarFish `RTTI Type Descriptor', &CNStarFishKing `RTTI Type Descriptor', 0) != 0 )  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 && rand() % 100 < 20 )  // 调虚槽 +308：是否本地玩家
        sub_5B4A50(1, 1, -1, -1);
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 308))(pDwArg1[2152]) != 0 )  // 虚函数调用 槽+308
        (*(void (/*thiscall*/ **)(int, int, int, int, int *, uint32_t))(*(uint32_t *)pDwArg1[2152] + 760))(  // 虚函数调用 槽+760
          pDwArg1[2152],
          15,
          1106247680,  // 浮点常量 30.0f
          7,
          pDwArg1,
          0);
    }
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_ATTACH", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    v5 = pDwArg1[2154];  // v5 = 取 pDwArg1[2154]
    v6 = pDwArg1[2153] + 1;
    pDwArg1[2153] = v6;
    if ( v6 >= v5 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 724))(pDwArg1[2152]) != 0 )  // 若 v6 >= v5
    {
      if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 2  // crypt4byte 解密校验（·0x41A590 逆运算）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[2152] + 40))(pDwArg1[2152], 529) != 0  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
        && (uint8_t)sub_5B4A00(pDwArg1[2152]) != 0 )  // 齐格火种判定：取对象 vt+340 返回的形态/状态码，等于 260 / 263 / 2
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pDwArg1[2152] + 732))(pDwArg1[2152], 0, 0, 1);  // 虚函数调用 槽+732
        pMem = operator new(0x80u);  // new(128 字节) 分配对象
        pBuf[4] = pMem;
        v28 = 0;
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
        {
          v9 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1);  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
          v27 = v9 - (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 736))(pDwArg1);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
          *(float *)&v22 = (float)v27;
          v10 = sub_4D6810(pMem, v22, 500, 1, 1);  // CNChangeHp 构造（研究 §2⑦ 的延滞伤分支）
        }
        else  // 否则分支
        {
          v10 = nullptr;  // v10 = 空指针
        }
        v11 = *(uint32_t *)v10;
        v28 = -1;
        (*(void (/*thiscall*/ **)(uint8_t *, int *, int *, uint32_t, uint32_t, uint32_t, int))(v11 + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
          v10,
          pDwArg1,
          pDwArg1,
          0,
          0,
          0,
          -1);
        (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 672))(pDwArg1, 0, 1056964608);  // 调虚槽 +672：自身 HP
        sub_4AED60(v23);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 676))(pDwArg1, 0);  // 调虚槽 +676
        *((uint8_t *)pDwArg1 + 8632) = 1;
      }
      if ( pDwArg1[2153] < pDwArg1[2155] )
      {
        if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[2152] + 772))(pDwArg1[2152], 5) != 0  // 虚函数调用 槽+772：17 状态槽数组访问（+6228+4*a2）
          && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )  // 调虚槽 +308：是否本地玩家
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int *, int))(*(uint32_t *)pDwArg1[2152] + 764))(pDwArg1[2152], 5, 0, pDwArg1, 1);  // 虚函数调用 槽+764
        }
      }
      else if ( __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                  (int)pDwArg1,
                  0,
                  &CNStarFish `RTTI Type Descriptor',
                  &CNStarFishDevourer `RTTI Type Descriptor',
                  0) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int, int *, uint32_t))(*(uint32_t *)pDwArg1[2152] + 760))(  // 虚函数调用 槽+760
          pDwArg1[2152],
          11,
          1120403456,  // 浮点常量 100.0f
          1,
          pDwArg1,
          0);
      }
      else if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 6 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        (*(void (/*thiscall*/ **)(int, int, int, int, int *, uint32_t))(*(uint32_t *)pDwArg1[2152] + 760))(  // 虚函数调用 槽+760
          pDwArg1[2152],
          5,
          1120403456,  // 浮点常量 100.0f
          5,
          pDwArg1,
          0);
      }
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 15, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    }
    else  // 否则分支
    {
      v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调虚槽 +200：取动画对象
      sub_4926A0(v7);  // 帧游标复位（+44 帧数组；递归子链 +204）
    }
  }
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2152] + 604))(pDwArg1[2152], 0);  // 虚函数调用 槽+604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pDwArg1[2152] + 612))(pDwArg1[2152], 1, 1);  // 虚函数调用 槽+612：帧时刻覆盖开关（this+642 标志 / this+644 时刻）
  pObj2 = pDwArg1[2152];  // pObj2 = 取 pDwArg1[2152]
  v13 = *(uint32_t *)pObj2;
  pObj3 = pObj2;
  v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj2);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  v16 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v15);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 120))(pObj3, v16 - 1);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(int, int))(v13 + 112))(pDwArg1[2152], v17);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  v18 = *(uint32_t *)pDwArg1[2152];
  v19 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调虚槽 +152：效果通道 3
  v20 = sub_432E50(v19);  // 关系码对调映射
  return (*(int (/*thiscall*/ **)(int, int))(v18 + 148))(pDwArg1[2152], v20);  // 虚函数调用 槽+148：槽（12 行）
}



// ------------------------------------------------------------
// 0x5B5B90 sub_5B5B90
// 海星族"HOLD/ZGM_ATTACK"起手（fArg2 为事件包指针，取包内句柄对还原目标）：
// 经 ·0x45EBE0 还原目标对象，判定其 vt+40(obj,17) 命中且 Z 高度 >0 才采纳
// （否则槽清 0）；采纳后把目标坐标 X/Y/Z 分别抄入 this+8640/8644/8648，
// ·0x5B4ED0 解算发射点写 this+112，目标 vt+848(1)、分型 ==0 时目标 vt+768(5,40,本尊)；
// 连播 ZGM_ATTACK 与 HOLD 两语音；末段按分型 ·0x41A5E0==6 与否选帧表
// （+6 项或首项）、vt+876 双组归零、vt+888(0,2,1000,1000)、vt+896(4,4)、
// 本尊关联对象速度槽清 0、·0x495890(0,0)，并按分型决定 vt+344 偏移
// （分型 6 用 this+556+304 且 this+8616 = 3×this+8620，否则用 this+556）；
// 末了 this+8612 与 this+8624 两槽清零
// ------------------------------------------------------------
// 证: "ZGM_ATTACK" | "HOLD"
// 调: sub_5B5B90 sub_45EBE0 sub_5B4ED0 sub_41A5E0 sub_495890
int /*thiscall*/ sub_5B5B90(int *this, float fArg2)  // 实现：调: sub_5B5B90 sub_45EBE0 sub_5B4ED0 sub_41A5E0 sub_495890
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2152; // ecx
  int v6; // eax
  int fld_e21522; // ecx
  int v8; // eax
  int fld_e21523; // ecx
  bool pThis_6DD; // zf
  uint32_t *fld_e1554; // eax
  uint32_t *fld_e28; // edi
  int pThis_6DD2; // eax
  int v14; // edx
  int fld_e2155; // eax
  int fld_e139; // eax
  float v18; // [esp+Ch] [ebp-8h] BYREF
  float v19; // [esp+10h] [ebp-4h] BYREF

  pObj2 = sub_45EBE0(**(uint32_t **)(LODWORD(fArg2) + 4), *(uint32_t *)(*(uint32_t *)(LODWORD(fArg2) + 4) + 4));  // pObj2 = 调 sub_45EBE0 返回值
  pObj = pObj2;
  if ( pObj2 == 0  // 若 pObj2 为 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || (*(this + 2152) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  {
    *(this + 2152) = 0;  // this+8608〔uAI8608(推断)〕
  }
  fld_e2152 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
  if ( fld_e2152 != 0 )  // 若 fld_e2152 非 0
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2152 + 120))(fld_e2152);  // 调虚槽 +120：动画对象
    fld_e21522 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
    *(this + 2160) = v6;  // this+8640〔uCastSlot8640(推断)〕
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21522 + 124))(fld_e21522);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    fld_e21523 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
    *(this + 2161) = v8;  // this+8644〔uPhase8644(推断)〕
    *(this + 2162) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21523 + 128))(fld_e21523);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    sub_5B4ED0(&v18, &v19, &fArg2);  // 齐格激光/火种发射点解算：目标 this+8612（关联对象）分两族—— · 该对象 v
    (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 112))(  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      this,
      (uint64_t)v18 >> 32,
      (uint64_t)v18,
      (uint64_t)v19,
      (uint64_t)fArg2);
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2152) + 848))(*(this + 2152), 1);  // 虚函数调用 槽+848：冻结标志写入（+6744，0→-1 / 非0→0）
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int *))(*(uint32_t *)*(this + 2152) + 768))(*(this + 2152), 5, 40, this);  // 虚函数调用 槽+768：状态施加入口（17 状态槽懒创建 + 转发）
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ZGM_ATTACK", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
  }
  pThis_6DD = sub_41A5E0((unsigned int)(this + 1757)) == 6;  // crypt4byte 解密校验（·0x41A590 逆运算）
  fld_e1554 = (uint32_t *)*(this + 1554);  // this+6216〔pTbl6216(推断)〕
  if ( pThis_6DD )
    fld_e1554 += 6;
  (*(void (/*stdcall*/ **)(uint32_t))(*this + 196))(*fld_e1554);  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  fld_e28 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0  // 虚函数调用 槽+308
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  pThis_6DD2 = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
  v14 = *this;
  pThis_6DD = pThis_6DD2 == 6;
  fld_e2155 = *(this + 2155);  // this+8620〔uAI8620(推断)〕
  if ( pThis_6DD )
  {
    *(this + 2154) = 3 * fld_e2155;  // this+8616〔uAI8616(推断)〕
    fld_e139 = *(this + 139) + 304;  // this+556〔nGrabAnimBase〕
  }
  else  // 否则分支
  {
    *(this + 2154) = fld_e2155;  // this+8616〔uAI8616(推断)〕
    fld_e139 = *(this + 139);  // this+556〔nGrabAnimBase〕
  }
  (*(void (/*stdcall*/ **)(int))(v14 + 344))(fld_e139);  // 虚函数调用 槽+344：交互槽（45E490/45E4D0/525CE0）
  *(this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
  *(this + 2156) = 0;  // this+8624〔uAI8624(推断)〕
  return 0;
}



// ------------------------------------------------------------
// 0x5B5F90 sub_5B5F90
// 齐格增益/减益面翻转（三项版 + 形态标记）：this+8656 计数清 0、vt+1152(0)、
// vt+1040 返回对象 +8 字节置 1；再把攻击系数面 this+7620 的 +0/+32/+64/+96
// 四个字节各自"==0 取反"翻转（与 ·0x5B6000 同族，差异在首尾三行）
// ------------------------------------------------------------
// 调: sub_5B5F90
char /*thiscall*/ sub_5B5F90(uint32_t *this)  // 实现：调: sub_5B5F90
{
  int v2; // eax
  int fld_e1905; // esi
  char result; // al

  v2 = *this;
  *(this + 2164) = 0;  // this+8656〔uPair8656(推断)〕
  (*(void (/*stdcall*/ **)(uint32_t))(v2 + 1152))(0);  // 虚函数调用 槽+1152
  *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 1040))(this) + 8) = 1;  // 调虚槽 +1040
  *(uint8_t *)*(this + 1905) = *(uint8_t *)*(this + 1905) == 0;  // this+7620〔pStatusPanel(推断)〕
  *(uint8_t *)(*(this + 1905) + 32) = *(uint8_t *)(*(this + 1905) + 32) == 0;  // this+7620〔pStatusPanel(推断)〕
  *(uint8_t *)(*(this + 1905) + 64) = *(uint8_t *)(*(this + 1905) + 64) == 0;  // this+7620〔pStatusPanel(推断)〕
  fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
  result = *(uint8_t *)(fld_e1905 + 96);
  *(uint8_t *)(fld_e1905 + 96) = result == 0;
  return result;
}



// ------------------------------------------------------------
// 0x5B6150 sub_5B6150
// 齐格攻击系数面减半（最简式）：nArg3==2 时把档位取 nArg2，最终档位为 0 时把
// 攻击系数面 this+7620 的 +4 系数项自乘 0.5；其余情况原样返回
// ------------------------------------------------------------
// 调: sub_5B6150
int /*thiscall*/ sub_5B6150(uint32_t *this, int nArg2, int nArg3)  // 实现：调: sub_5B6150
{
  int result; // eax

  result = nArg3;
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    result = nArg2;
  if ( result == 0 )  // 若 result 为 0
  {
    result = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    *(float *)(result + 4) = *(float *)(result + 4) * 0.5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B6270 sub_5B6270
// 齐格受击处理器（受击后触发姿态随机化）：先 ·0x495250 通用受击；uArg2 !=2
// （非该伤害类型）且大状态 ==8 且分型 ·0x41A5E0(this+7028)==5 且当前动画
// == 帧表项 this+6216+20 时，追加 ·0x5B51D0 姿态/朝向随机化
// ------------------------------------------------------------
// 调: sub_5B6270 sub_495250 sub_41A5E0 sub_5B51D0
char /*thiscall*/ sub_5B6270(int this, unsigned int uArg2, int nArg3, int nArg4)  // 实现：调: sub_5B6270 sub_495250 sub_41A5E0 sub_5B51D0
{
  int pThis_348; // eax
  uint32_t *fld_1848; // edi

  LOBYTE(pThis_348) = sub_495250((uint8_t *)this, uArg2, nArg3, nArg4);  // 双标志门 + 转发 vt+968
  if ( uArg2 != 2 )  // 若 uArg2 != 2
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( pThis_348 == 8 )  // 若 pThis_348 == 8
    {
      pThis_348 = sub_41A5E0(this + 7028);  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( pThis_348 == 5 )  // 若 pThis_348 == 5
      {
        fld_1848 = (uint32_t *)(*(uint32_t *)(this + 6216) + 20);  // this+6216 【推断】资源/帧游标表
        pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调虚槽 +200：取动画对象
        if ( pThis_348 == *fld_1848 )
          LOBYTE(pThis_348) = sub_5B51D0(this);  // 调 取 16 位值低 8 位
      }
    }
  }
  return pThis_348;
}



// ------------------------------------------------------------
// 0x5B7BE0 sub_5B7BE0
// 光之领主受击视觉/计数复合处理：先 ·0x4D8F90(nArg2..nArg5) 通用受击；
// nArg2==0（该伤害类别）时——若 this+8607 门与动画对象非空，取时钟 this+8608
// 当前值经 ·0x42B420(50,150,now,500) 求闪烁 alpha（50..150 区间 500ms 周期，
// 随时刻推移），把 alpha 装进 ARGB（(v8<<24)|0xFFFFFF，颜色 −16776961 = 0xFF00FFFF
// 青→白渐变）交 ·0x491690(1,2,1,...) 做受击染色；this+8676 计数 >0 时另有分支
// ------------------------------------------------------------
// 调: sub_5B7BE0 sub_4D8F90 sub_699000 sub_42B420 sub_491690
int /*thiscall*/ sub_5B7BE0(int this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：调: sub_5B7BE0 sub_4D8F90 sub_699000 sub_42B420 sub_491690
{
  int result; // eax
  int pThis_21A0; // eax
  uint8_t v8; // al
  int pThis_21A02; // eax
  uint8_t v10; // al

  result = sub_4D8F90(nArg2, nArg3, nArg4, nArg5);  // vmt144 转发垫片（IRDActiveObject__vmt144 族）
  if ( (uint8_t)nArg2 == 0 )
  {
    if ( *(uint8_t *)(this + 8607) != 0 && *(uint32_t *)(this + 120) != 0 )  // this+8607〔bAI8607〕
    {
      pThis_21A0 = sub_699000(this + 8608);  // 【clock_now(clk)】
      v8 = sub_42B420(50, 150, pThis_21A0, 500);  // 往返插值（三角波）
      sub_491690(1, 2, 1, -16776961, (v8 << 24) | 0xFFFFFF, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
    }
    if ( *(int *)(this + 8668) > 0 )  // this+8668 反击/架招冷却计时
    {
      pThis_21A02 = sub_699000(this + 8608);  // 【clock_now(clk)】
      v10 = sub_42B420(50, 150, pThis_21A02, 500);  // 往返插值（三角波）
      sub_491690(1, 2, 1, -65536, (v10 << 24) | 0xFFFFFF, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
    }
    return sub_4D8F90(0, nArg3, nArg4, nArg5);  // vmt144 转发垫片（IRDActiveObject__vmt144 族）
  }
  return result;
}



// ------------------------------------------------------------
// 0x5BBE40 sub_5BBE40
// 空骨鱼/海星"起身/跃出"触发：高度（vt+128）≤ this+8612 阈值且 this+8624 门
// 未开时进入——后续按分型 ·0x41A5E0 与时钟 this+8640 计算跳跃参数
// 【推断：高度门触发的姿态切换】
// ------------------------------------------------------------
// 调: sub_5BBE40 sub_41A5E0 sub_699000
int /*thiscall*/ sub_5BBE40(int *this)  // 实现：调: sub_5BBE40 sub_41A5E0 sub_699000
{
  int fld_e2153; // ebx  | +0x21A4 → bAtkGate8612〔族字典〕（族字典）
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // edi
  float v9; // eax
  int result; // eax
  int v11; // [esp+Ch] [ebp-Ch]
  float v12; // [esp+10h] [ebp-8h]
  int v13; // [esp+14h] [ebp-4h]

  fld_e2153 = *(this + 2153);  // this+8612〔uAI8612(推断)〕
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) <= fld_e2153 && *((uint8_t *)this + 8608) == 0 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, fld_e2153);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v4);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(int *, int))(v3 + 112))(this, v5);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
    v6 = *this;
    *((uint8_t *)this + 8608) = 1;  // this+8608〔uAI8608(推断)〕
    v7 = (*(int (/*thiscall*/ **)(int *, int))(v6 + 672))(this, 3);  // 虚函数调用 槽+672：子对象基址 getter（1364 字节步长，this+1364*a2+676）
    v13 = sub_41A5E0(v7 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v12 = COERCE_FLOAT(sub_41A5E0(v7 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    v11 = sub_41A5E0(v8 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v9 = COERCE_FLOAT(sub_41A5E0(v8 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      this,
      (uint64_t)((double)v11 * v9) >> 32,
      0,
      (uint64_t)((double)v11 * v9),
      (uint64_t)((double)v13 * v12),
      0,
      0,
      0);
  }
  result = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
  if ( result > 1000 )  // 若 result > 1000
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 16, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  }
  return result;
}



// ------------------------------------------------------------
// 0x5BDF70 sub_5BDF70
// 单参转发桩（stdcall）：转调 ·0x5BDF10(nArg1)
// ------------------------------------------------------------
// 调: sub_5BDF70 sub_5BDF10
int /*stdcall*/ sub_5BDF70(int nArg1)  // 实现：调: sub_5BDF70 sub_5BDF10
{
  return sub_5BDF10(nArg1);  // 抱杀关系析构通知（被抱者/自身消亡时解挂）
}



// ------------------------------------------------------------
// 0x5C4CA0 sub_5C4CA0
// 树精机偶"HOLD"（施法/架招）目标处理：pArg2 为目标对象，经 ·0x45EBE0 还原
// 句柄对后取 this+8620/8624/8628 一组槽做坐标比对，命中则 ·0x424A40 触发
// 表现【推断：抓取/束缚类技能的目标锁定】
// ------------------------------------------------------------
// 证: "HOLD"
// 调: sub_5C4CA0 sub_45EBE0 sub_424A40
int /*thiscall*/ sub_5C4CA0(int *this, int pArg2)  // 实现：调: sub_5C4CA0 sub_45EBE0 sub_424A40
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2155; // ecx
  int v6; // eax
  int fld_e21552; // ecx
  int v8; // eax
  int fld_e21553; // ecx
  int v10; // eax
  int fld_e21554; // ebx
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int result; // eax
  int fld_e2158; // eax
  int v18; // edx
  int fld_e21555; // edi
  unsigned int v20; // eax
  int v21; // eax
  unsigned int v22; // [esp-4h] [ebp-10h]

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));  // pObj2 = 调 sub_45EBE0 返回值
  pObj = pObj2;
  if ( pObj2 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    *(this + 2155) = pObj;  // this+8620〔uAI8620(推断)〕
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 50 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      *(this + 2155) = 0;  // this+8620〔uAI8620(推断)〕
    *(this + 2154) = *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 8);  // this+8616〔uAI8616(推断)〕
  }
  else  // 否则分支
  {
    *(this + 2155) = 0;  // this+8620〔uAI8620(推断)〕
  }
  fld_e2155 = *(this + 2155);  // this+8620〔uAI8620(推断)〕
  if ( fld_e2155 != 0 )  // 若 fld_e2155 非 0
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2155 + 120))(fld_e2155);  // 调虚槽 +120：动画对象
    fld_e21552 = *(this + 2155);  // this+8620〔uAI8620(推断)〕
    *(this + 2164) = v6;  // this+8656〔uPair8656(推断)〕
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21552 + 124))(fld_e21552);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    fld_e21553 = *(this + 2155);  // this+8620〔uAI8620(推断)〕
    *(this + 2165) = v8;  // this+8660〔uEvt8660(推断)〕
    *(this + 2166) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21553 + 128))(fld_e21553);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
    fld_e21554 = *(uint32_t *)*(this + 2155);  // fld_e21554 = 读 this+2155
    v12 = v10 != 1 ? -350 : 350;
    v13 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13 - 1);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e21554 + 112))(*(this + 2155), v12 + v14);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
    if ( *(this + 2154) == 1 )  // this+8616〔uAI8616(推断)〕
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2155) + 848))(*(this + 2155), 1);  // 虚函数调用 槽+848：冻结标志写入（+6744，0→-1 / 非0→0）
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  v15 = *this;
  *(this + 2156) = 0;  // this+8624〔uAI8624(推断)〕
  *(this + 2159) = 0;  // this+8636〔pDollTarget(推断)〕
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v15 + 212))(this, "HOLD", -1, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
  result = *(this + 2154);  // this+8616〔uAI8616(推断)〕
  if ( result == 1 )  // 若 result == 1
  {
    fld_e2158 = *(this + 2158);  // this+8632〔bDevourFlag(推断)〕
    if ( *(this + 1908) != 2 )  // this+7632〔uWindow7632(推断)〕
      fld_e2158 /= 2;
    v18 = *this;
    *(this + 2157) = fld_e2158;  // this+8628〔nPoolTime(推断)〕
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v18 + 196))(this, *(uint32_t *)(*(this + 1554) + 16));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));  // 调虚槽 +344：取坐标三元组
  }
  else if ( result == 2 )
  {
    if ( *(this + 1908) == 2 )  // this+7632〔uWindow7632(推断)〕
    {
      *(this + 2157) = 1;  // this+8628〔nPoolTime(推断)〕
    }
    else  // 否则分支
    {
      fld_e21555 = *(this + 2155);  // this+8620〔uAI8620(推断)〕
      v20 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
      if ( fld_e21555 != 0 )  // 若 fld_e21555 非 0
      {
        v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21555 + 52))(fld_e21555) + v20;  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        srand(v22);  // 调 设置随机种子
      }
      else  // 否则分支
      {
        srand(v20);  // 调 设置随机种子
      }
      *(this + 2157) = rand() % 3 + 1;  // 调 取伪随机数
    }
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 20));  // 调虚槽 +196：动画对象设置（换域 + 播放）
    (*(void (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 152);  // 调虚槽 +344：取坐标三元组
    result = *(this + 2155);  // this+8620〔uAI8620(推断)〕
    if ( result == dword_8F7C04 )  // 本地玩家对象
    {
      v21 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      return sub_424A40(*(uint32_t **)(v21 + 132), 0);  // 锚定角色 setter
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C5130 sub_5C5130
// 树精机偶速度槽减向 + 系数面减半：nArg3==2 且 nArg2==0：this[1894] 写 1、
// this[1899] 写 50；nArg3==0：this[1895] 写 1、this[1899] 写 50，系数面
// this[1905]+32+4 项自乘 0.5，速度槽（vt+672(0)+830）读出 −1.0 经 ·0x41A590
// 写回并 vt+676 应用
// ------------------------------------------------------------
// 调: sub_5C5130 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C5130(uint32_t *this, int nArg2, int nArg3)  // 实现：调: sub_5C5130 sub_41A5E0 sub_41A590
{
  int result; // eax
  int fld_e1905; // eax
  unsigned int v6; // edi
  int v7; // edx
  int v8; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )  // 若 nArg3 == 2
    {
      result = nArg2;
      *(this + 1894) = 1;  // this+7576〔uPhase7576(推断)〕
      if ( nArg2 == 0 )  // 若 nArg2 为 0
        *(this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
    }
  }
  else  // 否则分支
  {
    fld_e1905 = *(this + 1905) + 32;  // this+7620〔pStatusPanel(推断)〕
    *(this + 1895) = 1;  // this+7580〔uSegDefault7580(推断)〕
    *(this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
    *(float *)(fld_e1905 + 4) = *(float *)(fld_e1905 + 4) * 0.5;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v6)) - 1.0;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v6, v7, v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C53F0 sub_5C53F0
// 树精机偶攻击档位（负向档）：nArg3==2 且 nArg2==0：this[1891] 写 1、
// this[1899] 写 −50；nArg3==0：this[1891] 写 1、this[1899] 写 −50，系数面
// this[1905]+36 项自乘 0.5（负向档伴随系数减半）
// ------------------------------------------------------------
// 调: sub_5C53F0
int /*thiscall*/ sub_5C53F0(uint32_t *this, int nArg2, int nArg3)  // 实现：调: sub_5C53F0
{
  int result; // eax

  result = nArg3;
  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )  // 若 nArg3 == 2
    {
      result = nArg2;
      *(this + 1891) = 1;  // this+7564〔uForm7564(推断)〕
      if ( nArg2 == 0 )  // 若 nArg2 为 0
        *(this + 1899) = -50;  // this+7596〔nOffset7596(推断)〕
    }
  }
  else  // 否则分支
  {
    *(this + 1891) = 1;  // this+7564〔uForm7564(推断)〕
    *(this + 1899) = -50;  // this+7596〔nOffset7596(推断)〕
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.5;  // this+7620〔pStatusPanel(推断)〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C5570 sub_5C5570
// 树精机偶切段（置标记版）+ 速度槽减向：·0x5C5020 切段配置后，速度槽
// （vt+672(3)+158）读出 −1.0 经 ·0x41A590 写回（与 ·0x5C5520 的 +1.0 为对偶）
// ------------------------------------------------------------
// 调: sub_5C5570 sub_5C5020 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C5570(void *this)  // 实现：调: sub_5C5570 sub_5C5020 sub_41A5E0 sub_41A590
{
  unsigned int pThis_2A0; // esi
  int v3; // edx
  int v5; // [esp+4h] [ebp-4h]

  sub_5C5020();  // 树精机偶切段配置： vt+208 写帧表项 this+6216+32、vt+888(0,
  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3) + 158;  // 调虚槽 +672：自身 HP
  *(float *)&v5 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) - 1.0;  // crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(pThis_2A0, v3, v5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x5C6300 sub_5C6300
// 目标筛型谓词：pArg2 非本尊且其 vt+340 形态码 == 600 时为真
// （600 与 ·0x5C6560 的 601、·0x5C67B0 的 603 构成同族形态码白名单）
// ------------------------------------------------------------
// 调: sub_5C6300
bool /*thiscall*/ sub_5C6300(void *this, void *pArg2)  // 实现：调: sub_5C6300
{
  return pArg2 != this && *(uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pArg2 + 340))(pArg2) == 600;  // 调虚槽 +340：三元组基址（+284，vt+340）
}



// ------------------------------------------------------------
// 0x5C6470 sub_5C6470
// 树精机偶速度槽双轴 ±0.07 调节：pszArg2 非 0 时速度槽 A（vt+672(0)+1054）与
// 速度槽 B（同对象 +1110）各 +0.07（·0x41A5E0 读、·0x41A590 写）；
// pszArg2==0 时同两槽各 −0.07；两分支均不调 vt+676（应用延迟到别处）
// ------------------------------------------------------------
// 调: sub_5C6470 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C6470(void *this, char pszArg2)  // 实现：调: sub_5C6470 sub_41A5E0 sub_41A590
{
  unsigned int pThis_2A0; // edi
  int v4; // edx
  unsigned int pThis_2A02; // esi
  int v6; // edx
  int v8; // edx
  int v9; // [esp+10h] [ebp+8h]
  int v10; // [esp+10h] [ebp+8h]
  int v11; // [esp+10h] [ebp+8h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 1054;  // 调虚槽 +672：自身 HP
  if ( pszArg2 != 0 )  // 若 pszArg2 非 0
  {
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.07;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, v4, v9);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 1110;  // 调虚槽 +672：自身 HP
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) + 0.07;  // crypt4byte 解密校验（·0x41A590 逆运算）
  }
  else  // 否则分支
  {
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) - 0.07;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, v8, v11);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 1110;  // 调虚槽 +672：自身 HP
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) - 0.07;  // crypt4byte 解密校验（·0x41A590 逆运算）
  }
  return sub_41A590(pThis_2A02, v6, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x5C65A0 sub_5C65A0
// 目标筛型谓词：pArg2 非本尊且其 vt+340 形态码 == 602 时为真
// （600/601/602/603 四连形态码，构成树精机偶族的目标白名单）
// ------------------------------------------------------------
// 调: sub_5C65A0
bool /*thiscall*/ sub_5C65A0(void *this, void *pArg2)  // 实现：调: sub_5C65A0
{
  return pArg2 != this && *(uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pArg2 + 340))(pArg2) == 602;  // 调虚槽 +340：三元组基址（+284，vt+340）
}



// ------------------------------------------------------------
// 0x5C66B0 sub_5C66B0
// 树精机偶伤害减免钩子（stdcall 版）：先走 ·0x4DC390(pDwArg1, nArg2) 伤害前置；
// 返回非 3（非该特例类型）且 nArg2 对象 vt+576 子对象非空时，伤害值 *pDwArg1
// 乘 0.7（−30% 减伤）并返回 0 表示已处理；否则原样返回前置结果 v3
// ------------------------------------------------------------
// 调: sub_5C66B0 sub_4DC390
int /*stdcall*/ sub_5C66B0(int *pDwArg1, int nArg2)  // 实现：调: sub_5C66B0 sub_4DC390
{
  int result; // eax
  int v3; // esi

  result = sub_4DC390(pDwArg1, nArg2);  // 伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
  v3 = result;
  if ( result != 3 )  // 若 result != 3
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )  // 调虚槽 +576
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.69999999);
      return 0;
    }
    else  // 否则分支
    {
      return v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C67E0 sub_5C67E0
// 树精机偶速度三轴微调（float* this 版，两常量 10.0/20.0）：先把 this+8744 写
// 10.0f、this+8748 写 20.0f（两步进幅度常量）；pszArg2 非 0 时：速度槽 A
// （vt+672(0)+60）+10（常量），速度槽 B（同对象 +116）+ 10.0，速度槽 C（+830）
// + this+8748×0.001（即 +0.02）；pszArg2==0 时对应 −10 / −10.0 / −0.02 三分支
// ------------------------------------------------------------
// 调: sub_5C67E0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C67E0(float *this, char pszArg2)  // 实现：调: sub_5C67E0 sub_41A5E0 sub_41A590
{
  unsigned int pThis_2A0; // edi
  int v4; // eax
  int v5; // edx
  int fld_e2186; // ebx
  unsigned int pThis_2A02; // edi
  int v8; // eax
  int v9; // edx
  unsigned int pThis_2A03; // edi
  int v11; // edx
  int fld_e21862; // ebx
  unsigned int fld_e21863; // edi
  int v14; // eax
  int v15; // edx
  float fld_e2187; // [esp+Ch] [ebp-4h]
  float fld_e21872; // [esp+Ch] [ebp-4h]
  int v19; // [esp+18h] [ebp+8h]

  *(this + 2186) = 10.0;  // this+8744〔nCountdown8744(推断)〕
  *(this + 2187) = 20.0;  // this+8748〔bTail8748〕
  pThis_2A0 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 60;  // 调虚槽 +672：自身 HP
  v4 = sub_41A5E0(pThis_2A0);  // crypt4byte 解密校验（·0x41A590 逆运算）
  if ( pszArg2 != 0 )  // 若 pszArg2 非 0
  {
    sub_41A590(pThis_2A0, v5, v4 + 10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_e2186 = (uint64_t)*(this + 2186);  // this+8744〔nCountdown8744(推断)〕
    pThis_2A02 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 116;  // 调虚槽 +672：自身 HP
    v8 = sub_41A5E0(pThis_2A02);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A02, v9, fld_e2186 + v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_e2187 = *(this + 2187) * 0.001;  // this+8748〔bTail8748〕
    pThis_2A03 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&v19 = COERCE_FLOAT(sub_41A5E0(pThis_2A03)) + fld_e2187;  // crypt4byte 解密校验（·0x41A590 逆运算）
  }
  else  // 否则分支
  {
    sub_41A590(pThis_2A0, v5, v4 - 10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_e21862 = (uint64_t)*(this + 2186);  // this+8744〔nCountdown8744(推断)〕
    fld_e21863 = (*(int (/*fastcall*/ **)(float *, uint32_t, uint32_t))(*(uint32_t *)this + 672))(  // 调虚槽 +672：自身 HP
            this,
            (uint64_t)*(this + 2186) >> 32,  // this+8744〔nCountdown8744(推断)〕
            0)
        + 116;
    v14 = sub_41A5E0(fld_e21863);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(fld_e21863, v15, v14 - fld_e21862);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fld_e21872 = *(this + 2187) * 0.001;  // this+8748〔bTail8748〕
    pThis_2A03 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&v19 = COERCE_FLOAT(sub_41A5E0(pThis_2A03)) - fld_e21872;  // crypt4byte 解密校验（·0x41A590 逆运算）
  }
  sub_41A590(pThis_2A03, v11, v19);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
}



// ------------------------------------------------------------
// 0x5C6A50 sub_5C6A50
// 网络流写 uint8（与 ·0x5C6A90 同族，宽度 1 字节）：向 缓冲基址 this[1] +
// 写偏移 this[2] 处写 pszArg2，写偏移 +=1；越界（> this[0] 容量上限）调
// off_77F3FC(aCriticalError_40, 上限) 报致命错误
// ------------------------------------------------------------
// 调: sub_5C6A50
int /*thiscall*/ sub_5C6A50(int *this, char pszArg2)  // 实现：调: sub_5C6A50
{
  int fld_e2; // ebx
  int v3; // ecx
  int result; // eax

  *(uint8_t *)(*(this + 1) + *(this + 2)) = pszArg2;  // this+4〔宿主对象〕等 2 字段
  fld_e2 = *(this + 2) + 1;  // this+8〔nSkillRec8(推断)〕
  *(this + 2) = fld_e2;  // this+8〔nSkillRec8(推断)〕
  v3 = *this;
  result = fld_e2;
  if ( fld_e2 > v3 )  // 若 fld_e2 > v3
    return off_77F3FC(aCriticalError_40, v3);  // 返回 调 off_77F3FC
  return result;
}



// ------------------------------------------------------------
// 0x5C92C0 sub_5C92C0
// 单参转发桩（stdcall）：转调 ·0x498F00(0)（实参被硬编码为 0）
// ------------------------------------------------------------
// 调: sub_5C92C0 sub_498F00
int /*stdcall*/ sub_5C92C0(int nArg1)  // 实现：调: sub_5C92C0 sub_498F00
{
  return sub_498F00(0);  // 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查）
}



// ------------------------------------------------------------
// 0x5CF720 sub_5CF720
// 伤害结算三参转发桩（stdcall）：原样转调 ·0x4DB480(nArg1,nArg2,nArg3)
// （通用伤害结算器，多族共用）
// ------------------------------------------------------------
// 调: sub_5CF720 sub_4DB480
int /*stdcall*/ sub_5CF720(int nArg1, int nArg2, int nArg3)  // 实现：调: sub_5CF720 sub_4DB480
{
  return sub_4DB480(nArg1, nArg2, nArg3);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// ------------------------------------------------------------
// 0x5D2010 sub_5D2010
// 四参转发桩（stdcall）：原样转调 ·0x5D19C0(pszArg1, fArg2, nArg3, nArg4)
// ------------------------------------------------------------
// 调: sub_5D2010 sub_5D19C0
int /*stdcall*/ sub_5D2010(char pszArg1, float fArg2, int nArg3, int nArg4)  // 实现：调: sub_5D2010 sub_5D19C0
{
  return sub_5D19C0(pszArg1, fArg2, nArg3, nArg4);  // 状态事件总透传（架招退出 + 反击效果 30022）
}



// ------------------------------------------------------------
// 0x5D7CD0 sub_5D7CD0
// CNSandorExpeller（沙多驱逐者）构造器：先写虚表 CNSandorExpeller::vftable
// （RTTI 直证类名），再转 ·0x5D6E40 做基类构造（与 ·0x5D7AD0 的
// CNHeavenExpeller 共用同一基类构造器）
// ------------------------------------------------------------
// 调: sub_5D7CD0 sub_5D6E40
int /*thiscall*/ sub_5D7CD0(uint32_t *this)  // 函数定义: 本条为沙多驱逐者析构的近邻定义
{
  *this = &CNSandorExpeller::`vftable';  // 写 vftable 指针（对象重定位/复位）
  return sub_5D6E40();  // 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
}


