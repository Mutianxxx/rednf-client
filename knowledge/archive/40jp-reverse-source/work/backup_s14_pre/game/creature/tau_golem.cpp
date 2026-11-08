// ============================================================
// 【40JP逆向源代码工程】creature/tau_golem.cpp
// 模块: 怪物AI 0x5A —— 牛头兵(Tau)/石魔像(Golem)/人偶师/飞龙/猎人/僵尸
// 来源: work/dump_monster.txt  区块: 0x5A0000-0x5B0000
// 层级: L2 转写层 + L1 精修（函数体保持 Hex-Rays 忠实输出，仅升级注释与分区）
// 函数数: 249
// ------------------------------------------------------------
// ★ 本文件已按《20_打击感与HitStop系统研究》定案升级注释（研究 20 §x 为引）：
//   · vmt200(=vt+512 字节槽) 命中处理器覆写：0x5A3160×5表 / 0x5A4B20×1 /
//     0x5A8360×6 / 0x5AD0B0×4（虚表农场 0x6CB000-0x6EB000 +512 槽, 纯 Python 直读 PE）
//   · AI 大状态机（this+6556, 研究 15/20）：0x5A0420(vt+560 setState 形拦截, 态 8)、
//     0x5A5610(沙乌塔地震 态 8 门)、0x5A6630(C_BERSERK 狂暴)、0x5A9100(人偶浮游 态 14)、
//     0x5AEAB0(僵尸眼 态 14 条件) —— 本文件是五文件中 6556 证据最密集的一块
//   · 0x5AE990 调 sub_4E4430 = HP 受击处理器（研究 31 Boss 终局族）
//   · 语音 TAG 组（R_TAU_*/GOLEM_*/FLYDRAGON_*/HUNTER_*/ZOMBIE_*）经 sub_4015C0
//     写入语音槽, vt+212(sub_499110) 播报（研究 28）；sub_431230=vector 打包 setState 参数
//   · 资源标注：sub_431860/431920=.ani 装载 / sub_64B0F0=光环粒子(.ptl) /
//     sub_4BA9E0=.equ 外观 / sub_4049C0=帧间插值 / sub_406D60=BGM 曲名槽写入
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】哥布林基础与装备变体（0x5A0060-0x5A0780）
// 证据：{acc3,acc4,Hcc2,gcc1-3,tcc1,bcc1}.equ 六件外观（0x5A0530）、
//       0x5A0420 为 vt+560 setState 形拦截（this+6556 态 8 门）

// AI 字段复位（20L）
// ------------------------------------------------------------
// 0x5A0060 sub_5A0060 —— 12 字节元素容器插入辅助
// 经 ·0x59FDB0 定点插入内核写入元素（uArg2 为出参返回插入位），按 pszArg3 与容器
// 首针（this+1/+2 槽）的 12 字节对齐差折算插入序号
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5A0060(int *this, uint32_t *uArg2, char *pszArg3, int *Block)  // 函数: 12 字节元素容器插入辅助
{
  int pBegin; // esi  this+4 容器的 begin 指针
  int nInsertIdx; // esi  新元素将落到的槽序号（按 12 字节元素折算）

  pBegin = *(this + 1);  // this+4 = pHostObj
  if ( pBegin != 0 && (*(this + 2) - pBegin) / 12 != 0 )  // this+8 = 技能槽记录首字
    nInsertIdx = (int)&pszArg3[-pBegin] / 12;  // 目标地址相对 begin 的元素序号
  else
    nInsertIdx = 0;
  sub_59FDB0(this, pszArg3, 1u, Block);  // 调 三元组容器定点插入（vector 12 字节元素内核）
  *uArg2 = *(this + 1) + 12 * nInsertIdx;  // 出参回填：插入后新元素的地址（begin 可能因扩容搬家）
  return uArg2;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A00D0 sub_5A00D0 —— 12 字节元素容器尾插/emplace
// 容量未满（this+8 尾针 < this+12 上限针）就地经 ·0x623C10 构造并推进尾针；
// 已满走 ·0x5A0060 扩容插入
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5A00D0(int this, int *Block)  // 函数: 12 字节元素容器尾插/emplace
{
  int pBegin; // edi  this+4 begin 针
  unsigned int nCount; // ecx  现有元素数 = (end-begin)/12
  int pEnd; // edi  this+8 end 针
  uint32_t *result; // eax

  pBegin = *(uint32_t *)(this + 4);  // this+4 宿主对象
  if ( pBegin != 0 )
    nCount = (*(uint32_t *)(this + 8) - pBegin) / 12;  // this+8 物品 id
  else
    nCount = 0;
  if ( pBegin == 0 || nCount >= (*(uint32_t *)(this + 12) - pBegin) / 12 )  // this+12 物品类型号
    return sub_5A0060((int *)this, &Block, *(char **)(this + 8), Block);  // 容量不足：走扩容插入
  pEnd = *(uint32_t *)(this + 8);  // this+8 物品 id
  result = (uint32_t *)sub_623C10(pEnd, 1, Block);  // 就地构造（拷贝构造 1 个）
  *(uint32_t *)(this + 8) = pEnd + 12;  // 尾针推进 12 字节 = 1 个元素
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A0150 sub_5A0150 —— int 元素容器尾插（this+972 处 vector）
// 容量足则直写尾元素并自增尾针，已满经 ·0x45F8A0 扩容插入；供 ·0x5A01B0 吊灯
// 携带表登记复用
// ------------------------------------------------------------
int /*thiscall*/ sub_5A0150(char *this, int nArg2)  // 函数: int 元素容器尾插（this+972 处 vector）
{
  char *pThis_3CC; // ecx  容器对象基址 = this+972（即元素下标 243）
  int pBegin; // esi
  unsigned int nCount; // edx
  int *pEnd; // eax
  int result; // eax

  pThis_3CC = this + 972;  // this+972 叉子缩放计数
  pBegin = *((uint32_t *)pThis_3CC + 1);
  if ( pBegin != 0 )
    nCount = (*((uint32_t *)pThis_3CC + 2) - pBegin) >> 2;  // >>2 = 4 字节 int 元素
  else
    nCount = 0;
  if ( pBegin == 0 || nCount >= (*((uint32_t *)pThis_3CC + 3) - pBegin) >> 2 )  // 向量元素数 = (end−begin)/4
    return sub_45F8A0(*((void **)pThis_3CC + 2), 1, (int)&nArg2);  // 容量不足：扩容插入
  pEnd = *((int **)pThis_3CC + 2);
  *pEnd = nArg2;
  result = (int)(pEnd + 1);
  *((uint32_t *)pThis_3CC + 2) = result;
  return result;
}



// RTTI cast 目标解算 AI（86L；this+8624 相位）
// ------------------------------------------------------------
// 0x5A01B0 sub_5A01B0 —— 吊灯（CNChandelier）挂接判定
// 遍历场景对象列表（this+29 槽所指容器），vt+40(obj,33) 过滤后 RTTI cast 到
// CNChandelier；X 距 ±55（vt+120）、vt+124 层位相等、vt+128 高度达标则按吊灯
// 坐标+10 偏移写入本尊位置（vt+112），并 ·0x5A0150 把自己登记进吊灯携带表、
// 记宿主 this+2158 槽；成功置相位 this+8624=1，无命中清 0（天空之城吊灯运输【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A01B0(uint8_t *this)  // 函数: 吊灯（CNChandelier）挂接判定
{
  unsigned int i; // ebx  场景对象列表下标
  int fld_e29; // ecx
  int pBegin; // edx
  int result; // eax
  int pBegin2; // edx
  int pObj3; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int v10; // eax
  int pObj2; // eax
  char *pObj; // esi
  int nChandXMinus55; // ebx
  int nChandXPlus55; // ebx
  int nChandLayer; // ebx
  int nChandZ; // ebx
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  int pThis_78; // eax
  unsigned int v21; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    fld_e29 = *((uint32_t *)this + 29);  // this+116〔会话上下文〕
    pBegin = *(uint32_t *)(fld_e29 + 8);
    v21 = i;
    result = pBegin != 0 ? (*(uint32_t *)(fld_e29 + 12) - pBegin) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;
    pBegin2 = *(uint32_t *)(fld_e29 + 8);
    if ( pBegin2 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - pBegin2) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj3 = *(uint32_t *)(pBegin2 + 4 * i);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 33) != 0 )  // vt+40(obj,33) 类型过滤
    {
      fld_e292 = *((uint32_t *)this + 29);  // this+116〔会话上下文〕
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      pObj2 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &CNChandelier `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      pObj = (char *)pObj2;
      if ( pObj2 != 0 )  // 是吊灯
      {
        nChandXMinus55 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2) - 55;  // 吊灯X - 55：X 距判定下界
        if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) >= nChandXMinus55 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        {
          nChandXPlus55 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 120))(pObj) + 55;  // 吊灯X + 55：判定上界
          if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) <= nChandXPlus55 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          {
            nChandLayer = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 124))(pObj);  // vt+124 = 层位(Y)
            if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this) == nChandLayer )  // 调用虚函数（虚表槽 +124）
            {
              nChandZ = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 128))(pObj);  // vt+128 = 高度(Z)
              if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this) >= nChandZ )  // 调用虚函数（虚表槽 +128）
              {
                v17 = *(uint32_t *)this;
                v18 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 128))(pObj);  // 调用虚函数（虚表槽 +128）
                v19 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj + 124))(pObj, v18 + 10);  // 挂点 Z+10
                pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, v19 + 1);  // 挂点 Y+1
                (*(void (/*thiscall*/ **)(uint8_t *, int))(v17 + 112))(this, pThis_78);  // vt+112 写本尊位置
                result = sub_5A0150(pObj, (int)this);  // 调 int 元素容器尾插（this+972 处 vector）
                *((uint32_t *)this + 2158) = pObj;  // this+2158 槽（元素下标，字节 8632）记宿主吊灯
                *(this + 8624) = 1;  // 相位 this+8624 = 已挂接
                return result;
              }
            }
          }
        }
        i = v21;
      }
    }
  }
  *(this + 8624) = 0;  // 无吊灯可挂：相位清 0
  return result;
}



// RTTI cast 目标解算（61L）
// ------------------------------------------------------------
// 0x5A0300 sub_5A0300 —— 目标扫描入表
// 遍历对象列表，RTTI cast IRDActiveObject 且 ·0x4E4630 敌我判定、vt+1244 门通过者，
// 取（对象, vt+164 测度, vtbl+8 测度）12 字节三元组经 ·0x5A00D0 推入目标容器
// （this+2171 槽为头，begin/end/cap = 8688/8692/8696）；容器非空返回 true，
// 供 ·0x5A0420 大状态 8 门作有无目标判据
// ------------------------------------------------------------
bool /*thiscall*/ sub_5A0300(uint32_t *this)  // 函数: 目标扫描入表
{
  unsigned int i; // ebx  场景对象列表下标
  int fld_e29; // ecx
  int pBegin; // edx
  int nCount; // eax
  int v6; // edx
  int v7; // eax
  int pObj; // eax  当前候选对象
  int pActive; // esi  RTTI cast 成 IRDActiveObject 的结果
  int v10; // eax
  uint64_t v11; // rax
  int fld_e2172; // eax  目标容器 begin
  unsigned int fld_e2173; // edx
  bool result; // al
  int Block[4]; // [esp+Ch] [ebp-10h] BYREF  12 字节三元组：对象指针 + vt+164 测度 + vtbl+8 测度

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    pBegin = *(uint32_t *)(fld_e29 + 8);
    nCount = pBegin != 0 ? (*(uint32_t *)(fld_e29 + 12) - pBegin) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= nCount )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      v7 = *(uint32_t *)(v6 + 4 * i);
    else
      v7 = 0;
    pObj = __RTDynamicCast(v7, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    pActive = pObj;
    if ( pObj != 0
      && (uint8_t)sub_4E4630(pObj) != 0  // 敌我判定（可为攻击目标）
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pActive) != 0 )  // vt+1244 目标资格门
    {
      v10 = *this;
      Block[0] = pActive;
      v11 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v10 + 164))(this, pActive, 0);  // vt+164 取测度（距离/威胁值）
      HIDWORD(v11) = *this;  // 调 取 64 位值高 32 位
      Block[1] = v11;
      Block[2] = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(HIDWORD(v11) + 8))(this, pActive, 0);  // vtbl+8 第二测度
      sub_5A00D0((int)(this + 2171), Block);  // 推入 this+8684 目标容器（尾插）
    }
  }
  fld_e2172 = *(this + 2172);  // this+8688〔bVec8688(推断)〕
  result = false;
  if ( fld_e2172 != 0 )
  {
    fld_e2173 = (int)((uint64_t)(715827883LL * (*(this + 2173) - fld_e2172)) >> 32) >> 1;  // 除法魔数：×715827883>>32>>1 = ÷12
    Block[3] = (*(this + 2173) - fld_e2172) / 12;  // this+8692〔uVec8692(推断)〕
    if ( fld_e2173 + (fld_e2173 >> 31) != 0 )  // 元素数 != 0
      return true;  // 容器非空 → 有目标
  }
  return result;
}



// AI 字段访问（this+8628）
// ------------------------------------------------------------
// 0x5A0400 sub_5A0400 —— 观察收尾 + 吊灯挂接 + 房号同步
// 先 ·0x4D9760 广播收尾，再 ·0x5A01B0 吊灯挂接刷新，末了把 this+6200 首字段
// 抄入 this+8628（房号/区域号【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A0400(int this)  // 函数: 观察收尾 + 吊灯挂接 + 房号同步
{
  int result; // eax

  sub_4D9760();  // 调 观察者广播后条件收尾
  sub_5A01B0((uint8_t *)this);  // 调 吊灯（CNChandelier）挂接判定
  result = **(uint32_t **)(this + 6200);  // this+6200 【推断】段表对象
  *(uint32_t *)(this + 8628) = result;  // this+8628 【推断】指挥计时戳
  return result;
}



// 【AI 大状态拦截】vt+560 setState 形参表(this, 状态, 参数, 优先级, 标志)：
//   this+6556==8 进/出态门 —— 清 this+8672/+8612；sub_41A5E0(this+7028) 怪物数据分型 1/2
//   走不同清理（研究 15/20 三层状态; 56L）
// ------------------------------------------------------------
// 0x5A0420 sub_5A0420 —— vt+560 setState 拦截：大状态 8 进出门
// 离开态 8（this+6556==8 转他态）时按 ·0x41A5E0（this+7028）分型清理——1 型置
// this+8672=-1、2 型走 ·0x59FD50 撤场——并复位 this+8612；进态 8 时若 ·0x5A0300
// 无目标则清参数面目标项（·0x59F040 基类链与 vt+308 可动门之后）；1 型置
// this+8672=3 起手段，2 型置 4 并 ·0x59F880 相位复位
// ------------------------------------------------------------
int /*thiscall*/ sub_5A0420(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 【为 vt+560 setState 形拦截（this+6556 态 8 门）】
{
  int result; // eax

  if ( *(uint32_t *)(this + 6556) == 8 && ArgList != 8 )  // 离开大状态 8
  {
    if ( sub_41A5E0(this + 7028) == 1 )  // 1 型：仅改写相位槽
    {
      *(uint32_t *)(this + 8672) = -1;  // this+8672 【推断】子类 AI 相位槽
    }
    else if ( sub_41A5E0(this + 7028) == 2 )  // 2 型：走撤场流程
    {
      sub_59FD50(this);  // 调 相位置位与容器释放（撤场清理）
    }
    *(uint8_t *)(this + 8612) = 0;  // this+8612 锁定/相位字节 A
  }
  if ( *(uint32_t *)(this + 8672) != 4  // this+8672 【推断】子类 AI 相位槽
    && ArgList == 8
    && **(uint32_t **)(LODWORD(fArg3) + 4) == 2  // 参数包第 1 项 == 2（目标类参数）
    && !sub_5A0300((uint32_t *)this) )  // 且扫不出目标
  {
    **(uint32_t **)(LODWORD(fArg3) + 4) = 0;  // 目标项清 0
  }
  sub_59F040(this, ArgList, fArg3, nArg4, nArg5);  // 基类 setState
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // vt+308 可行动门
  if ( (uint8_t)result != 0 && ArgList == 8 )
  {
    result = sub_41A5E0(this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )
    {
      *(uint32_t *)(this + 8672) = 3;  // 1 型进态：起手段 3
      *(uint8_t *)(this + 8676) = 0;  // this+8676 【推断】子类 AI 相位槽
      *(uint32_t *)(this + 8680) = 0;  // this+8680 【推断】子类 AI 门字节
    }
    else
    {
      result = sub_41A5E0(this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result == 2 )  // 2 型进态：相位 4 + 复位
      {
        result = 4;
        if ( *(uint32_t *)(this + 8672) != 4 )  // this+8672 【推断】子类 AI 相位槽
        {
          *(uint32_t *)(this + 8672) = 4;  // this+8672 【推断】子类 AI 相位槽
          return (int)sub_59F880(this);  // 调 相位字节复位（7620 面板 +8700）
        }
      }
    }
  }
  return result;
}



// 哥布林近战装载：Monster/Goblin/{acc3,acc4,Hcc2,gcc1-3,tcc1,bcc1}.equ（92L）
// ------------------------------------------------------------
// 0x5A0530 sub_5A0530 —— 哥布林近战型六件 .equ 挂装 + 效果值插值
// 六件（acc3/acc4/Hcc2/gcc1-3/tcc1/bcc1）各 new 0x544 经 ·0x4BA9E0 装载、vt+784
// 挂装并置可见（vt+4(obj,1)）；取出场参数面 vt+384(0/1) 两端值按帧进度
// （vt+672(3) 对 this+1820..1821 区间）经 ·0x4049C0 插值写 this+2155 槽
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5A0530(uint32_t *this)  // 函数: 哥布林近战型六件 .equ 挂装 + 效果值插值
{
  char *pMem; // eax  六件 .equ 的原始堆块（0x544 = CNRDEquipment 尺寸）
  char *pEqu; // eax
  int pObj; // eax  挂装返回的外观操作对象
  char *pMem2; // eax
  char *pEqu2; // eax
  int pObj2; // eax
  char *pMem3; // eax
  char *pEqu3; // eax
  int pObj4; // eax
  char *pMem4; // eax
  char *pEqu4; // eax
  int pObj3; // eax
  char *pMem5; // eax
  char *pEqu5; // eax
  int pObj5; // eax
  char *pMem6; // eax
  char *pEqu6; // eax
  int pObj6; // eax
  int nFrameSpan; // edi  this+1821 - this+1820 = 出场参数面区间长度
  uint32_t *pAnim; // eax
  uint64_t result; // rax
  float fV0; // [esp+3Ch] [ebp-2Ch]  插值起点（vt+384(0) 出场参数 0）
  float fV1; // [esp+40h] [ebp-28h]  插值终点（vt+384(1) 出场参数 1）
  void *Block; // [esp+54h] [ebp-14h]
  int v26; // [esp+58h] [ebp-10h]

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pEqu = sub_4BA9E0(pMem, "Monster/Goblin/acc3.equ", 0);  // 装载 .equ 外观
  else
    pEqu = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, pEqu);  // vt+784 挂装
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // vt+4(obj,1) 置可见
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    pEqu2 = sub_4BA9E0(pMem2, "Monster/Goblin/acc4.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEqu2 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, pEqu2);  // 调用虚函数（虚表槽 +784）
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调用虚函数（虚表槽 +4）
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    pEqu3 = sub_4BA9E0(pMem3, "Monster/Goblin/Hcc2.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEqu3 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, pEqu3);  // 调用虚函数（虚表槽 +784）
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调用虚函数（虚表槽 +4）
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    pEqu4 = sub_4BA9E0(pMem4, "Monster/Goblin/gcc1-3.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEqu4 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, pEqu4);  // 调用虚函数（虚表槽 +784）
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调用虚函数（虚表槽 +4）
  pMem5 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    pEqu5 = sub_4BA9E0(pMem5, "Monster/Goblin/tcc1.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEqu5 = nullptr;
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, pEqu5);  // 调用虚函数（虚表槽 +784）
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);  // 调用虚函数（虚表槽 +4）
  pMem6 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
    pEqu6 = sub_4BA9E0(pMem6, "Monster/Goblin/bcc1.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEqu6 = nullptr;
  pObj6 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, pEqu6);  // 调用虚函数（虚表槽 +784）
  if ( pObj6 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 4))(pObj6, 1);  // 调用虚函数（虚表槽 +4）
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 出场参数 0
  v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 出场参数 1
  nFrameSpan = *(this + 1821) - *(this + 1820);
  pAnim = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // vt+672(3) 动作对象
  fV1 = (float)v26;
  fV0 = (float)(int)Block;
  result = (uint64_t)sub_4049C0(fV0, fV1, *pAnim - *(this + 1820), nFrameSpan);  // 按帧进度 lerp 0..1  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2155) = result;  // this+8620 存插值结果（六段蓄雷的段距基数）
  return result;
}



// ============================================================
// 【分区 2】天空之城哥布林三型外观（0x5A0780-0x5A0D00）
// 证据：Monster/Goblin/SkyCastle/{BombKagel,SurikenKagel,BullsEye}/ 五件套 +
//       PassiveObject/Common/Particle/RedRock.ptl（投掷哥布林落石）

// 天空之城·炸弹加格尔装载：Monster/Goblin/SkyCastle/BombKagel/{Face,hair,pants,wrist,belt}.equ
// ------------------------------------------------------------
// 0x5A0780 sub_5A0780 —— 炸弹加格尔（BombKagel）五件套挂装
// 五件 .equ 各 new 0x544 经 ·0x4BA9E0 装载、vt+784 挂装（首件带槽参 nArg2@ebx）
// 并置可见（vt+4(obj,1)）；末尾清 pArg1[1666] 槽（挂装完成标志【推断】）
// ------------------------------------------------------------
int /*usercall*/ sub_5A0780@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：炸弹加格尔（BombKagel）五件套挂装
{
  char *pMem; // eax  Face 装备堆块（0x544）
  char *pEquFace; // eax
  int pObjFace; // eax
  char *pMem2; // eax
  char *pEquHair; // eax
  int pObjHair; // eax
  char *pMem3; // eax
  char *pEquPants; // eax
  int pObjPants; // eax
  char *pMem4; // eax
  char *pEquWrist; // eax
  int pObjWrist; // eax
  char *pMem5; // eax
  char *pEquBelt; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pEquFace = sub_4BA9E0(pMem, "Monster/Goblin/SkyCastle/BombKagel/Face.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquFace = nullptr;
  pObjFace = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*pArg1 + 784))(pArg1, pEquFace, nArg2);  // 首件带槽参
  if ( pObjFace != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjFace + 4))(pObjFace, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    pEquHair = sub_4BA9E0(pMem2, "Monster/Goblin/SkyCastle/BombKagel/hair.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquHair = nullptr;
  pObjHair = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, pEquHair);  // 调用虚函数（虚表槽 +784）
  if ( pObjHair != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjHair + 4))(pObjHair, 1);  // 调用虚函数（虚表槽 +4）
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    pEquPants = sub_4BA9E0(pMem3, "Monster/Goblin/SkyCastle/BombKagel/pants.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquPants = nullptr;
  pObjPants = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, pEquPants);  // 调用虚函数（虚表槽 +784）
  if ( pObjPants != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjPants + 4))(pObjPants, 1);  // 调用虚函数（虚表槽 +4）
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    pEquWrist = sub_4BA9E0(pMem4, "Monster/Goblin/SkyCastle/BombKagel/wrist.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquWrist = nullptr;
  pObjWrist = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, pEquWrist);  // 调用虚函数（虚表槽 +784）
  if ( pObjWrist != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjWrist + 4))(pObjWrist, 1);  // 调用虚函数（虚表槽 +4）
  pMem5 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    pEquBelt = sub_4BA9E0(pMem5, "Monster/Goblin/SkyCastle/BombKagel/belt.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquBelt = nullptr;
  result = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, pEquBelt);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  pArg1[1666] = 0;  // this+6664 挂装完成相关槽清零【推断】
  return result;
}



// 天空之城·手里剑加格尔装载：Monster/Goblin/SkyCastle/SurikenKagel/ 五件套
// ------------------------------------------------------------
// 0x5A0930 sub_5A0930 —— 与 ·0x5A0780 同构
// （差异：手里剑加格尔 SurikenKagel 五件套，末尾同样清 pArg1[1666] 槽）
// ------------------------------------------------------------
int /*usercall*/ sub_5A0930@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：与 ·0x5A0780 同构
{
  char *pMem; // eax  Face 装备堆块（0x544）
  char *pEquFace; // eax
  int pObjFace; // eax
  char *pMem2; // eax
  char *pEquHair; // eax
  int pObjHair; // eax
  char *pMem3; // eax
  char *pEquPants; // eax
  int pObjPants; // eax
  char *pMem4; // eax
  char *pEquWrist; // eax
  int pObjWrist; // eax
  char *pMem5; // eax
  char *pEquBelt; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pEquFace = sub_4BA9E0(pMem, "Monster/Goblin/SkyCastle/SurikenKagel/Face.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquFace = nullptr;
  pObjFace = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*pArg1 + 784))(pArg1, pEquFace, nArg2);  // 调用虚函数（虚表槽 +784）
  if ( pObjFace != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjFace + 4))(pObjFace, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    pEquHair = sub_4BA9E0(pMem2, "Monster/Goblin/SkyCastle/SurikenKagel/hair.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquHair = nullptr;
  pObjHair = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, pEquHair);  // 调用虚函数（虚表槽 +784）
  if ( pObjHair != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjHair + 4))(pObjHair, 1);  // 调用虚函数（虚表槽 +4）
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    pEquPants = sub_4BA9E0(pMem3, "Monster/Goblin/SkyCastle/SurikenKagel/pants.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquPants = nullptr;
  pObjPants = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, pEquPants);  // 调用虚函数（虚表槽 +784）
  if ( pObjPants != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjPants + 4))(pObjPants, 1);  // 调用虚函数（虚表槽 +4）
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    pEquWrist = sub_4BA9E0(pMem4, "Monster/Goblin/SkyCastle/SurikenKagel/wrist.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquWrist = nullptr;
  pObjWrist = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, pEquWrist);  // 调用虚函数（虚表槽 +784）
  if ( pObjWrist != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjWrist + 4))(pObjWrist, 1);  // 调用虚函数（虚表槽 +4）
  pMem5 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    pEquBelt = sub_4BA9E0(pMem5, "Monster/Goblin/SkyCastle/SurikenKagel/belt.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquBelt = nullptr;
  result = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, pEquBelt);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  pArg1[1666] = 0;  // this+6664 槽清零（同 BombKagel 型）
  return result;
}



// 天空之城·投掷哥布林装载：Monster/Goblin/SkyCastle/BullsEye/ 五件套 +
//   PassiveObject/Common/Particle/RedRock.ptl 落石粒子（86L）
// ------------------------------------------------------------
// 0x5A0AE0 sub_5A0AE0 —— 投掷哥布林（BullsEye）挂装 + 子类状态复位 + 落石粒子创建
// 五件套 .equ（vt+784）同前两型；随后复位子类 AI 面（this+8672=-1、+8676/+8680
// 清零、释放 +8688 缓冲并清 +8692/+8696）；末尾 new 0x12C 经 ·0x428F30 创建落石
// 粒子 RedRock.ptl，句柄存 this+8704
// ------------------------------------------------------------
uint32_t */*usercall*/ sub_5A0AE0@<eax>(int pArg1@<ecx>, int nArg2@<edi>)  // 实现：投掷哥布林（BullsEye）挂装 + 子类状态复位 + 落石粒子创建
{
  char *pMem; // eax  Face 装备堆块（0x544）
  char *pEquFace; // eax
  int pObjFace; // eax
  char *pMem2; // eax
  char *pEquHair; // eax
  int pObjHair; // eax
  char *pMem3; // eax
  char *pEquPants; // eax
  int pObjPants; // eax
  char *pMem4; // eax
  char *pEquWrist; // eax
  int pObjWrist; // eax
  char *pMem5; // eax
  char *pEquBelt; // eax
  int pObjBelt; // eax
  uint32_t *result; // eax  落石粒子对象

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pEquFace = sub_4BA9E0(pMem, "Monster/Goblin/SkyCastle/BullsEye/Face.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquFace = nullptr;
  pObjFace = (*(int (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)pArg1 + 784))(pArg1, pEquFace, nArg2);  // 调用虚函数（虚表槽 +784）
  if ( pObjFace != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjFace + 4))(pObjFace, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    pEquHair = sub_4BA9E0(pMem2, "Monster/Goblin/SkyCastle/BullsEye/hair.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquHair = nullptr;
  pObjHair = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, pEquHair);  // 调用虚函数（虚表槽 +784）
  if ( pObjHair != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjHair + 4))(pObjHair, 1);  // 调用虚函数（虚表槽 +4）
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    pEquPants = sub_4BA9E0(pMem3, "Monster/Goblin/SkyCastle/BullsEye/pants.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquPants = nullptr;
  pObjPants = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, pEquPants);  // 调用虚函数（虚表槽 +784）
  if ( pObjPants != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjPants + 4))(pObjPants, 1);  // 调用虚函数（虚表槽 +4）
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    pEquWrist = sub_4BA9E0(pMem4, "Monster/Goblin/SkyCastle/BullsEye/wrist.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquWrist = nullptr;
  pObjWrist = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, pEquWrist);  // 调用虚函数（虚表槽 +784）
  if ( pObjWrist != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjWrist + 4))(pObjWrist, 1);  // 调用虚函数（虚表槽 +4）
  pMem5 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    pEquBelt = sub_4BA9E0(pMem5, "Monster/Goblin/SkyCastle/BullsEye/belt.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    pEquBelt = nullptr;
  pObjBelt = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, pEquBelt);  // 调用虚函数（虚表槽 +784）
  if ( pObjBelt != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObjBelt + 4))(pObjBelt, 1);  // 调用虚函数（虚表槽 +4）
  *(uint32_t *)(pArg1 + 8672) = -1;  // 子类相位：-1 = 未启动
  *(uint32_t *)(pArg1 + 6664) = 0;  // this+6664 挂装相关槽【推断】
  *(uint8_t *)(pArg1 + 8676) = 0;  // pArg1+8676〔uAI8676(推断)〕
  *(uint32_t *)(pArg1 + 8680) = 0;  // pArg1+8680〔uGate8680(推断)〕
  if ( *(uint32_t *)(pArg1 + 8688) != 0 )  // pArg1+8688〔bVec8688(推断)〕
    j__free(*(void **)(pArg1 + 8688));  // 释放旧目标容器缓冲（this+8688 = begin）
  *(uint32_t *)(pArg1 + 8688) = 0;  // pArg1+8688〔bVec8688(推断)〕
  *(uint32_t *)(pArg1 + 8692) = 0;  // pArg1+8692〔uVec8692(推断)〕
  *(uint32_t *)(pArg1 + 8696) = 0;  // pArg1+8696〔uVec8696(推断)〕
  result = operator new(0x12Cu);  // operator new 分配 300 字节
  if ( result != nullptr )  // 若 result 有效（非空）
  {
    result = sub_428F30(result, (int)"PassiveObject/Common/Particle/RedRock.ptl", 0);  // 创建落石粒子
    *(uint32_t *)(pArg1 + 8704) = result;  // this+8704 存粒子句柄
  }
  else
  {
    *(uint32_t *)(pArg1 + 8704) = 0;  // pArg1+8704〔pSegNameTbl8704(推断)〕
  }
  return result;
}



// ============================================================
// 【分区 3】落雷凯诺（LightningKinol）（0x5A0D00-0x5A2020）
// 证据：BEFORE_THUNDER 蓄雷播报、THUNDER_STRIKE 落雷 + Animation_LightningKinol/
//       DieThunderbolt.ani、B_KINOL_01 登场曲、Lkinolpants.equ

// AI 字段访问
// ------------------------------------------------------------
// 0x5A0D00 sub_5A0D00 —— AI 字段访问
// 单字段清零：this+2153 效果槽归零
// ------------------------------------------------------------
void /*thiscall*/ sub_5A0D00(uint32_t *this)  // 函数: AI 字段访问
{
  *(this + 2153) = 0;  // this+8612 = uAI8612
}



// 蓄雷 AI：BEFORE_THUNDER 播报（this+200 主状态门 + 8624 相位, 64L）
// ------------------------------------------------------------
// 0x5A0D10 sub_5A0D10 —— 落雷凯诺六段蓄雷相位机（1 型）
// 大状态逐段（vt+200 态面 +148 字段 == 3..8，段号 this+2157）首次进入时播报
// BEFORE_THUNDER（vt+212），可动（vt+308）则在 30070 判定圆落雷：段距 =
// this+2155×(段+1)、方向随 vt+152 翻转，半径按 this+1908 取 100/130；该段动画
// 走完（态 == 段+1）清段内防重门 this+8624 并段号+1
// ------------------------------------------------------------
int /*thiscall*/ sub_5A0D10(uint32_t *this)  // 函数: 落雷凯诺六段蓄雷相位机（1 型）
{
  int pVtbl; // eax  缓存的虚表指针 = *this
  int nStepDist; // edi  该段落雷段距 = 段距基数 × (段号+1)
  int v4; // ebx
  int fld_e2154; // eax
  int fld_e21542; // eax
  int result; // eax
  int fld_e2157; // ecx  当前段号 this+2157（元素下标，字节偏移 8628）
  uint32_t v9[6]; // [esp+8h] [ebp-18h]  1 型六段的大状态表 {3,4,5,6,7,8}

  pVtbl = *this;
  v9[0] = 3;  // 蓄雷期大状态 3..8 对应动画段 1..6
  v9[1] = 4;
  v9[2] = 5;
  v9[3] = 6;
  v9[4] = 7;
  v9[5] = 8;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(pVtbl + 200))(this) + 148) == v9[*(this + 2157)]  // 当前动画 == 该段目标态
    && *((uint8_t *)this + 8624) == 0 )  // 且本段尚未落雷
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      this,
      "BEFORE_THUNDER",  // 蓄雷播报
      -1,
      0,
      0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 可行动
    {
      nStepDist = *(this + 2155) * (*(this + 2157) + 1);  // 段距随段号线性放大
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1 )  // vt+152 朝向 == 1
        nStepDist = -nStepDist;  // 朝向 1 时反向
      v4 = *this;
      fld_e2154 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 120))(  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
             this,
             *(this + 2154),  // this+8616 = uAI8616
             30070,  // 30070 = 落雷判定体编号
             *(this + 2153),  // this+8612 = uAI8612
             0,
             4,
             *(this + 1908) != 0 ? 100 : 130,  // 困难级半径 100，普通 130
             1,
             0,
             0);
      fld_e21542 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*this + 120))(this, *(this + 2154), 0, fld_e2154 - nStepDist);  // this+8616 = uAI8616
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 584))(this, fld_e21542 - nStepDist);  // 沿轴双端偏移落雷
    }
    *((uint8_t *)this + 8624) = 1;  // 本段已落雷防重
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  fld_e2157 = *(this + 2157);  // this+8628 = 指挥计时戳
  if ( *(uint32_t *)(result + 148) == v9[fld_e2157] + 1 )  // 该段动画播完（进下一态）
  {
    *((uint8_t *)this + 8624) = 0;  // 清防重门
    *(this + 2157) = fld_e2157 + 1;  // 段号 +1
  }
  return result;
}



// 蓄雷 AI 扩展：BEFORE_THUNDER（102L；+200/8624 门）
// ------------------------------------------------------------
// 0x5A0E50 sub_5A0E50 —— 与 ·0x5A0D10 同构的蓄雷相位机（2 型）
// （差异：12 段、大状态 2-13；落雷点取函数内 23 项坐标表奇/偶项按
// this+2158×0.01 缩放，直接以双坐标形 vt+584 生成 30070 判定圆，无段距递增）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A0E50(uint32_t *this)  // 函数: 与 ·0x5A0D10 同构的蓄雷相位机（2 型）
{
  int pVtbl; // eax  缓存的虚表指针 = *this
  int nSelfX; // eax  vt+120 读出的本尊 X
  int fld_e2157; // ecx  当前段号 this+2157（元素下标，字节偏移 8628）
  int nBoltX; // edi  落雷点 X = 本尊X + 偏移表X × (this+2158 × 0.01)
  uint64_t fld_e21572; // rax  落雷点 Y
  int result; // eax
  int fld_e21573; // ecx
  int nPad0; // [esp+Ch] [ebp-94h]  恒 0；其地址紧邻下表，被 v10[-1] 越界读走（Hex-Rays 栈布局直证）
  uint32_t v10[23]; // [esp+10h] [ebp-90h]  12 段落雷点偏移表（奇索引=ΔX、偶索引=ΔY，×0.01 百分比缩放）
  uint32_t v11[12]; // [esp+6Ch] [ebp-34h]  2 型的 12 段目标大状态 {2..13}
  int v12; // [esp+9Ch] [ebp-4h]  先接本尊X（死写）、后改接 vt+124 读出本尊 Y

  v10[3] = 135;
  v10[7] = 135;
  v10[1] = 75;
  v10[9] = 75;
  v10[2] = -70;
  v10[10] = -70;
  v10[15] = -135;
  v10[19] = -135;
  v10[22] = -70;
  pVtbl = *this;
  v11[0] = 2;  // 段 0..11 对应大状态 2..13
  v11[1] = 3;
  v11[2] = 4;
  v11[3] = 5;
  v11[4] = 6;
  v11[5] = 7;
  v11[6] = 8;
  v11[7] = 9;
  v11[8] = 10;
  v11[9] = 11;
  v11[10] = 12;
  v11[11] = 13;
  nPad0 = 0;  // 段 0 的 ΔX 由 v10[-1] 落到本槽读出（即 0）
  v10[0] = -85;
  v10[4] = -45;
  v10[5] = 175;
  v10[6] = 0;
  v10[8] = 45;
  v10[11] = 0;
  v10[12] = 85;
  v10[13] = -75;
  v10[14] = 70;
  v10[16] = 45;
  v10[17] = -175;
  v10[18] = 0;
  v10[20] = -45;
  v10[21] = -75;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(pVtbl + 200))(this) + 148) == v11[*(this + 2157)]  // this+8628 = 指挥计时戳
    && *((uint8_t *)this + 8624) == 0 )  // this+8624 = uAI8624
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      this,
      "BEFORE_THUNDER",  // 资源/动画 TAG BEFORE_THUNDER
      -1,
      0,
      0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    {
      nSelfX = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      fld_e2157 = *(this + 2157);  // this+8628 = 指挥计时戳
      v12 = nSelfX;  // 死写（寄存器合并残留）
      nBoltX = (uint64_t)((double)nSelfX + (double)v10[2 * fld_e2157 - 1] * ((double)(int)*(this + 2158) * 0.0099999998));  // ×0.01：百分比缩放
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
      fld_e21572 = (uint64_t)((double)v12
                            + (double)(int)v10[2 * *(this + 2157)] * ((double)(int)*(this + 2158) * 0.0099999998));  // this+8628 = 指挥计时戳
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 584))(  // 调用虚函数（虚表槽 +584）【推断: ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6…】
        this,
        nBoltX,
        fld_e21572,
        0,
        nBoltX,
        fld_e21572,
        30070,  // 30070 = 落雷判定体
        *(this + 2153),  // this+8612 = uAI8612
        0,
        4,
        *(this + 1908) != 0 ? 100 : 130,  // this+7632〔uWindow7632(推断)〕
        1,
        0,
        0);
    }
    *((uint8_t *)this + 8624) = 1;  // this+8624 = uAI8624
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  fld_e21573 = *(this + 2157);  // this+8628 = 指挥计时戳
  if ( *(uint32_t *)(result + 148) == v11[fld_e21573] + 1 )
  {
    *((uint8_t *)this + 8624) = 0;  // this+8624 = uAI8624
    *(this + 2157) = fld_e21573 + 1;  // this+8628 = 指挥计时戳
  }
  return result;
}



// 大型 AI（137L；落雷凯诺走位）
// ------------------------------------------------------------
// 0x5A1070 sub_5A1070 —— 困难级落雷齐射（走位压制）
// 困难级（this+1943==3）且 vt+308 时 75% 概率：·0x4E7F30(100,60,0) 范围判定通过
// 【推断：近身有敌】则以本尊为心在 ±50 网格四点各生成 30070 判定圆落雷
// （vt+120/124 坐标换算、vt+584 生成，半径 100/130），收尾 ·0x49C970 与
// ·0x49C5F0(9,...,1000) 表现调用；判定不过则对本尊 this+1813 宿主单点落雷
// ------------------------------------------------------------
int /*thiscall*/ sub_5A1070(int *this)  // 函数: 困难级落雷齐射（走位压制）
{
  int result; // eax
  int nRand; // eax
  int nRoll; // et2  rand()%100 掷点
  int pVtbl; // edi  缓存的虚表指针
  int fld_e2153; // eax  第一个落雷点（判定圆链中间值）  | +0x21A4 → bAtkGate8612〔族字典〕（族字典）
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int pVtbl2; // edi
  int fld_e21532; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int pVtbl3; // edi
  int fld_e21533; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int pVtbl4; // edi
  int fld_e21534; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int pVtbl5; // ebx
  int pTarget7252; // edi  宿主对象 this+7252  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int fld_e21535; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 && *(this + 1943) == 3 )  // 可行动 + 困难级
  {
    nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
    nRoll = nRand % 100;
    result = nRand / 100;
    if ( nRoll < 75 )  // 75% 齐射
    {
      if ( sub_4E7F30(this, 100, 60, 0) != 0 )  // 近身判定：半径 100 / 门槛 60
      {
        pVtbl = *this;
        fld_e2153 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(  // 调用虚函数（虚表槽 +124）
               this,
               30070,
               *(this + 2153),  // this+8612 = uAI8612
               0,
               4,
               *(this + 1908) != 0 ? 100 : 130,  // 困难级半径 100，普通 130
               1,
               0,
               0);
        v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, fld_e2153);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        v8 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v7 - 50);  // 网格 −50
        v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        (*(void (/*thiscall*/ **)(int *, int))(pVtbl + 584))(this, v9 - 50);  // 落雷点 1
        pVtbl2 = *this;
        fld_e21532 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(  // 调用虚函数（虚表槽 +124）
                this,
                30070,
                *(this + 2153),  // this+8612 = uAI8612
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,  // this+7632〔uWindow7632(推断)〕
                1,
                0,
                0);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, fld_e21532);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        v13 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v12 + 50);  // 网格 +50
        v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        (*(void (/*thiscall*/ **)(int *, int))(pVtbl2 + 584))(this, v14 + 50);  // 落雷点 2
        pVtbl3 = *this;
        fld_e21533 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(  // 调用虚函数（虚表槽 +124）
                this,
                30070,
                *(this + 2153),  // this+8612 = uAI8612
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,  // this+7632〔uWindow7632(推断)〕
                1,
                0,
                0);
        v17 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, fld_e21533 - 50);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        v18 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v17);  // 调用虚函数（虚表槽 +124）
        v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v18 - 50);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        (*(void (/*thiscall*/ **)(int *, int))(pVtbl3 + 584))(this, v19);  // 落雷点 3
        pVtbl4 = *this;
        fld_e21534 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(  // 调用虚函数（虚表槽 +124）
                this,
                30070,
                *(this + 2153),  // this+8612 = uAI8612
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,  // this+7632〔uWindow7632(推断)〕
                1,
                0,
                0);
        v22 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, fld_e21534 + 50);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        v23 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v22);  // 调用虚函数（虚表槽 +124）
        v24 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v23 + 50);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        (*(void (/*thiscall*/ **)(int *, int))(pVtbl4 + 584))(this, v24);  // 落雷点 4
        sub_49C970(8, 0, 0);  // 调 池分配包装（this+4 复制为第 2/3 参）
        return sub_49C5F0(9, 0, 0, 1000);  // 9 号表现延时 1000ms
      }
      else
      {
        result = *(this + 1813);  // this+7252 = pTarget7252
        if ( result != 0 )  // 若结果非 0（成功）
        {
          pVtbl5 = *this;
          pTarget7252 = *(this + 1813);  // this+7252 = pTarget7252
          fld_e21535 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)result + 124))(  // 调用虚函数（虚表槽 +124）
                  result,
                  30070,
                  *(this + 2153),  // this+8612 = uAI8612
                  0,
                  4,
                  *(this + 1908) != 0 ? 100 : 130,  // this+7632〔uWindow7632(推断)〕
                  1,
                  0,
                  0);
          v28 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pTarget7252 + 120))(pTarget7252, fld_e21535);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          v29 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pTarget7252 + 124))(pTarget7252, 0, v28);  // 调用虚函数（虚表槽 +124）
          v30 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pTarget7252 + 120))(pTarget7252, v29);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          return (*(int (/*thiscall*/ **)(int *, int))(pVtbl5 + 584))(this, v30);  // 单点落雷（宿主坐标）
        }
      }
    }
  }
  return result;
}


// AI 字段访问（this+8604）
// ------------------------------------------------------------
// 0x5A12C0 sub_5A12C0 —— 大状态 6 退出钩子
// 经 ·0x4DBC20 处理退出副作用后，若开关 this+8604 开着，以 this+7256 重挂
// 战斗光环（·0x64BDF0）
// ------------------------------------------------------------
char /*thiscall*/ sub_5A12C0(int this, int nArg2)  // 函数: 大状态 6 退出钩子
{
  char result; // al

  result = sub_4DBC20(nArg2);  // 调 大状态退出副作用处理器（0x4DBA80 的还原对偶）
  if ( nArg2 == 6 )
  {
    result = *(uint8_t *)(this + 8604);  // this+8604 子类 AI 状态槽/相位门
    if ( result != 0 )  // 若结果非 0（成功）
      return sub_64BDF0(this, *(uint32_t *)(this + 7256));  // 调 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A1300 sub_5A1300 —— 对目标施放单点判定
// 取 nArg2 子对象（vt+576）坐标链（vt+120/124，30070 判定圆，vt+152 取基准 100）
// 换算后经 vt+584 写入生成【推断：与蓄雷族同款施放链】
// ------------------------------------------------------------
void /*thiscall*/ sub_5A1300(int *this, int nArg2)  // 函数: 对目标施放单点判定
{
  int pObj3; // ebx
  int pObj2; // esi
  int v6; // eax
  int v7; // eax
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
    v6 = (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(*this + 152))(this, 100, 1, 0, 0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v7 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int))(*(uint32_t *)pObj3 + 124))(pObj3, 30070, 0, 0, v6);  // 调用虚函数（虚表槽 +124）
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 120))(pObj4, v7);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v9 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 124))(pObj, 0, v8);  // 调用虚函数（虚表槽 +124）
    v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v9);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    (*(void (/*thiscall*/ **)(int *, int))(v11 + 584))(this, v10);  // 调用虚函数（虚表槽 +584）【推断: ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6…】
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A13C0 sub_5A13C0 —— 蓄雷分型步进
// 大状态 8（this+6556）时按 ·0x41A5E0（this+7028）分型走 ·0x5A0D10（1 型六段）或
// ·0x5A0E50（2 型 12 段）；其余状态走基类步进 ·0x4E1780
// ------------------------------------------------------------
char /*thiscall*/ sub_5A13C0(uint32_t *this)  // 函数: 蓄雷分型步进
{
  if ( *(this + 1639) == 8 )  // this+6556 = 主状态镜像
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      sub_5A0D10(this);  // 调 落雷凯诺六段蓄雷相位机（1 型）
      return sub_4E1780(this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
    }
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      sub_5A0E50(this);  // 调 与 ·0x5A0D10 同构的蓄雷相位机（2 型）
  }
  return sub_4E1780(this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// 指挥 AI：GOBLIN_COMMAND（RTTI cast, 56L）
// ------------------------------------------------------------
// 0x5A1410 sub_5A1410 —— 哥布林指挥事件处理（GOBLIN_COMMAND）
// ·0x4DC630 取事件包并从 dword_8F8520 流读四个 uint16（命令者/目标句柄对）；
// 事件 13 时 ·0x45EBE0 句柄还原 + RTTI 双验（CNGoblinGoblin/IRDActiveObject）后
// ·0x49C510 下发协同攻击令（组 10），头顶气泡 ·0x4D82D0 Command.ani、播报
// GOBLIN_COMMAND，并 ·0x4DB200 以 2/3/4 号文案随机播报
// ------------------------------------------------------------
int /*thiscall*/ sub_5A1410(uint32_t *this)  // 函数: 哥布林指挥事件处理（GOBLIN_COMMAND）
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

  result = sub_4DC630();  // 调 关卡/交互事件包处理（关联对象 this+7260 校验）
  v3 = result;
  if ( result != -1 )
  {
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v12);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v13);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v10);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v11);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    if ( (uint16_t)v3 == 13 )
    {
      v4 = sub_45EBE0(v12, v13);  // 调 存 id 对 → 对象查找
      v5 = __RTDynamicCast(v4, 0, &CNRDObject `RTTI Type Descriptor', &CNGoblinGoblin `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      v6 = sub_45EBE0(v10, v11);  // 调 存 id 对 → 对象查找
      v7 = __RTDynamicCast(v6, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      if ( v5 != 0 && v7 != 0 )  // 若 v5 != 0 与/或 v7 != 0
      {
        sub_49C510(10, *(this + 1), *(uint32_t *)(v5 + 4), v7, 0);  // 调 命令下发入口（五元组写 dword_9A0250 后 ·sub_4AEA30 派发）
        sub_4D82D0(0, 0);  // 头顶气泡 Command.ani（a2/a3 = 定位偏移）
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          this,
          "GOBLIN_COMMAND",  // 资源/动画 TAG GOBLIN_COMMAND
          -1,
          0,
          0);
        v9[0] = 2;
        v9[1] = 3;
        v9[2] = 4;
        nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
        sub_4DB200(24, v9[nRand % 3]);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
      }
    }
    return v3;
  }
  return result;
}



// AI 相位辅助（96L）
// ------------------------------------------------------------
// 0x5A1550 sub_5A1550 —— 闪敌贴身（瞬移至目标）
// vt+308 门下遍历对象列表，筛 17/545 型、异阵营（vt+376）、距离 vt+8<=300 且
// （非 17 型或 vt+940 条件不成立）者，50% 概率经坐标换算链（vt+120/124，±25 抖动）
// 写本尊位置（vt+584）并 setState 14（vt+560 蓄力/架招）【推断：落雷凯诺瞬移接敌】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A1550(uint32_t *this)  // 函数: 闪敌贴身（瞬移至目标）
{
  int result; // eax
  unsigned int i; // esi
  int fld_e29; // ecx
  int v5; // edx
  int v6; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj3; // ecx
  int fld_e293; // ecx
  int v12; // edx
  int pObj2; // esi
  int v14; // ebx
  int nRand2; // eax
  int v16; // ebx
  int fld_e2153; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int nRand; // [esp+4h] [ebp-Ch]
  int v22; // [esp+8h] [ebp-8h]
  unsigned int v23; // [esp+Ch] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      fld_e29 = *(this + 29);  // this+116〔会话上下文〕
      v5 = *(uint32_t *)(fld_e29 + 8);
      v23 = i;
      result = v5 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)i >= result )
        break;
      v6 = *(uint32_t *)(fld_e29 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj = *(uint32_t *)(v6 + 4 * i);
      else
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) == 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
      {
        fld_e292 = *(this + 29);  // this+116〔会话上下文〕
        v9 = *(uint32_t *)(fld_e292 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
          pObj3 = *(uint32_t *)(v9 + 4 * i);
        else
          pObj3 = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 545) == 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
          continue;
      }
      fld_e293 = *(this + 29);  // this+116〔会话上下文〕
      v12 = *(uint32_t *)(fld_e293 + 8);
      if ( v12 != 0 && i < (*(uint32_t *)(fld_e293 + 12) - v12) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj2 = *(uint32_t *)(v12 + 4 * i);
      else
        pObj2 = 0;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);  // 调用虚函数（虚表槽 +376）
      if ( v14 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)  // 调用虚函数（虚表槽 +376）
        && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj2, 0) <= 300  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
        && ((*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
         || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 940))(pObj2) == 0)  // 调用虚函数（虚表槽 +940）
        && rand() % 100 >= 50 )  // 调 以 16 位种子状态递推并返回 15 位结果
      {
        nRand = rand() % 50 - 25;  // 调 以 16 位种子状态递推并返回 15 位结果
        nRand2 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
        v16 = *this;
        v22 = nRand2 % 50 - 25;
        fld_e2153 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 124))(  // 调用虚函数（虚表槽 +124）
                pObj2,
                30070,
                *(this + 2153),  // this+8612 = uAI8612
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,  // this+7632〔uWindow7632(推断)〕
                1,
                0,
                0);
        v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v22 + fld_e2153);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        v19 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj2 + 124))(pObj2, 0, nRand + v18);  // 调用虚函数（虚表槽 +124）
        v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v22 + v19);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v16 + 584))(this, nRand + v20);  // 调用虚函数（虚表槽 +584）【推断: ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6…】
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      }
      i = v23;
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A1720 sub_5A1720 —— 协同攻击令概率触发
// 前置 ·0x4DE3E0（语义待定【待验证】）；vt+308 门下 30% 概率经 ·0x59B130 向同族
// 哥布林广播攻击令（携 nArg2 与 this+1814 槽参）
// ------------------------------------------------------------
int /*usercall*/ sub_5A1720@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：协同攻击令概率触发
{
  int result; // eax
  int nRand; // eax
  int v5; // et2

  sub_4DE3E0();  // （短函数，转写体未含可辨字符串证据；语义待定(待验证)）
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
    v5 = nRand % 100;
    result = nRand / 100;
    if ( v5 < 30 )
      return sub_59B130(pArg1, nArg2, (int)pArg1, pArg1[1814]);  // 调 协同攻击令组包发送：遍历场景对象列表筛同族可指挥哥布林并广播命令 13
  }
  return result;
}



// 参数打包 AI（sub_431230, 53L）
// ------------------------------------------------------------
// 0x5A1760 sub_5A1760 —— 落点试位并携参施放（setState 8）
// 以 this+1813 宿主坐标 ±50 抖动试位（vt+136 校验可站，至多 100 次），命中点经
// ·0x431230 打包（型 1、坐标、时长 rand%50+25）后 vt+560 以态 8 携参施放
// 【推断：随机轰击宿主邻近区】
// ------------------------------------------------------------
void /*thiscall*/ sub_5A1760(int **this)  // 函数: 落点试位并携参施放（setState 8）
{
  int fld_e1813; // ebx
  int nRand; // eax
  int *fld_e18132; // ecx
  int v5; // eax
  int v6; // edx
  int *v7; // ebx
  int v8; // eax
  uint8_t v10[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  int v12; // [esp+Ch] [ebp-1Ch]
  int v13; // [esp+10h] [ebp-18h]
  int nRand2; // [esp+14h] [ebp-14h] BYREF
  uint32_t v15[4]; // [esp+18h] [ebp-10h] BYREF

  if ( ((uint8_t (/*thiscall*/ *)(int **))(*this)[77])(this) != 0 && *(this + 1813) != nullptr )  // this+7252 = pTarget7252
  {
    v15[0] = 100;
    do
    {
      fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1813) + 124))(*(this + 1813));  // this+7252 = pTarget7252
      nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
      fld_e18132 = *(this + 1813);  // this+7252 = pTarget7252
      v5 = fld_e1813 + nRand % 100 - 50;
      v6 = *fld_e18132;
      v7 = *this;
      nRand2 = v5;
      v8 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(v6 + 120))(fld_e18132, v5, 0);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      if ( ((uint8_t (/*thiscall*/ *)(int **, int))v7[34])(this, v8) != 0 )
        break;
    }
    while ( v15[0]-- > 0 );
    Block = nullptr;
    v12 = 0;
    v13 = 0;
    v15[3] = 0;
    v15[0] = 1;
    sub_431230((int)v10, v15);  // 调 uint32 vector push_back
    sub_431230((int)v10, &nRand2);  // 调 uint32 vector push_back
    nRand2 = rand() % 50 + 25;  // 调 以 16 位种子状态递推并返回 15 位结果
    sub_431230((int)v10, &nRand2);  // 调 uint32 vector push_back
    ((void (/*thiscall*/ *)(int **, int, uint8_t *, uint32_t, uint32_t))(*this)[140])(this, 8, v10, 0, 0);
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
  }
}



// 参数打包 AI（sub_431230, 29L）
// ------------------------------------------------------------
// 0x5A1880 sub_5A1880 —— 与 ·0x5A1760 同构的 setState 8 携参施放
// （差异：不试落点，直接打包型 2 + 时长 10×(rand%5+5)=50-90 经 vt+560 发出）
// ------------------------------------------------------------
void /*thiscall*/ sub_5A1880(uint32_t *this)  // 函数: 与 ·0x5A1760 同构的 setState 8 携参施放
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && *(this + 1813) != 0 )  // this+7252 = pTarget7252
  {
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 2;
    sub_431230((int)v2, v6);  // 调 uint32 vector push_back
    v6[0] = 10 * (rand() % 5 + 5);  // 调 以 16 位种子状态递推并返回 15 位结果
    sub_431230((int)v2, v6);  // 调 uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
  }
}



// 登场曲：sub_406D60 写 "B_KINOL_01"（落雷凯诺曲目槽, 71L）
// ------------------------------------------------------------
// 0x5A1930 sub_5A1930 —— 落雷凯诺行为字相位机
// 相位 this+1787 分派：case 0 入场初始化（vt+1284）并在困难级（this+1943==3）挂
// BGM B_KINOL_01（·0x406D60）；case 4/5 有宿主（this+1813）时掷骰分流至 vt+1056 /
// ·0x5A1550 闪敌 / ·0x5A1880 型 2 施放 / ·0x5A1760 落点施放（各自概率门），无宿主写
// 行为字 13（vt+1104）；case 13/14/15 收束回行为字 4
// ------------------------------------------------------------
void /*thiscall*/ sub_5A1930(int **this)  // 函数: 落雷凯诺行为字相位机
{
  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( (unsigned int)*(this + 1787) )  // this+7148 = nBigState
  {
    case 0u:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      ((void (/*thiscall*/ *)(int **))(*this)[321])(this);
      if ( *(this + 1943) == (int *)3 )  // this+7772 = nCounterState
        sub_406D60("B_KINOL_01");  // 调 std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      return;
    case 4u:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == nullptr )  // this+7252 = pTarget7252
        goto LABEL_10;
      if ( rand() % 100 >= 5 )  // 调 以 16 位种子状态递推并返回 15 位结果
        goto LABEL_12;
      goto LABEL_8;
    case 5u:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) != nullptr )  // this+7252 = pTarget7252
      {
        if ( rand() % 100 < 5 )  // 调 以 16 位种子状态递推并返回 15 位结果
        {
LABEL_8:
          ((void (/*thiscall*/ *)(int **))(*this)[264])(this);
        }
        else
        {
LABEL_12:
          if ( rand() % 100 >= 15 )  // 调 以 16 位种子状态递推并返回 15 位结果
          {
            if ( rand() % 100 >= 8 )  // 调 以 16 位种子状态递推并返回 15 位结果
            {
              if ( rand() % 100 < 8 )  // 调 以 16 位种子状态递推并返回 15 位结果
                sub_5A1760(this);  // 调 落点试位并携参施放（setState 8）
            }
            else
            {
              sub_5A1880(this);  // 调 与 ·0x5A1760 同构的 setState 8 携参施放
            }
          }
          else
          {
            sub_5A1550(this);  // 调 闪敌贴身（瞬移至目标）
          }
        }
      }
      else
      {
LABEL_10:
        ((void (/*thiscall*/ *)(int **, int))(*this)[276])(this, 13);
      }
      return;
    case 0xDu:
      if ( *(this + 1813) != nullptr )  // this+7252 = pTarget7252
        goto LABEL_19;
      return;
    case 0xEu:
    case 0xFu:
      if ( *(this + 1813) != nullptr )  // this+7252 = pTarget7252
LABEL_19:
        ((void (/*thiscall*/ *)(int **, int))(*this)[276])(this, 4);
      break;
    default:
      return;
  }
}



// 落雷技能：THUNDER_STRIKE 播报 + Animation_LightningKinol/DieThunderbolt.ani
//   死亡落雷特效（61L）
// ------------------------------------------------------------
// 0x5A1A90 sub_5A1A90 —— 死亡落雷（THUNDER_STRIKE）
// this+1942 计数 +300、vt+260 屏幕效果、播报 THUNDER_STRIKE；vt+308 门下 8 次循环：
// ·0x42FCB0 预检后 ·0x431920 装载 Animation_LightningKinol/DieThunderbolt.ani，
// ·0x44B6C0/+0x44E0D0 建 CNRDPooledObject 特效体并 ·0x45FE80 投入场景容器
// （this+29 槽），落点在本尊坐标 ±15/±35 抖动
// ------------------------------------------------------------
int /*thiscall*/ sub_5A1A90(int *this)  // 函数: 死亡落雷（THUNDER_STRIKE）
{
  int result; // eax
  int v3; // ebx
  int fld_e91; // edx  | +0x016C → pAnimNameStr〔族字典〕（族字典）
  char *v5; // eax
  char *v6; // edi
  int v7; // edi
  int v8; // ebx
  int nRand; // eax
  int v10; // ebx
  int nRand2; // eax
  int i; // [esp+4h] [ebp-14h]
  char *v13; // [esp+8h] [ebp-10h]

  *(this + 1942) += 300;  // this+7768〔pObj7768〕
  (*(void (/*thiscall*/ **)(int *, int, int, int))(*this + 260))(this, 1, 5, -16777216);  // 调用虚函数（虚表槽 +260）【推断: 开关关闭时的时刻同步（+232 位 + +236/+240 参数…】
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "THUNDER_STRIKE", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    for ( i = 8; i != 0; --i )  // 循环：i 从 8 递减到 0
    {
      v3 = 0;
      if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
      {
        if ( (unsigned int)*(this + 96) < 0x10 )  // this+384 = 动画件名 SSO 容量判据
          LOBYTE(fld_e91) = (uint8_t)this + 108;  // 调 取 16 位值低 8 位
        else
          fld_e91 = *(this + 91);  // this+364 = 动画件名缓冲 SSO 内联首址
        v3 = sub_431920(fld_e91, (char)"Animation_LightningKinol/DieThunderbolt.ani", 1);  // 调 动画件构造（文件名版）
      }
      v5 = (char *)sub_44B6C0(284);  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
      v6 = v5;
      if ( v5 != nullptr )  // 若 v5 有效（非空）
      {
        sub_44E0D0(v5, v3, 1);  // 调 CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)v6 = &CNRDPooledObject::`vftable';  // vftable 复位
      }
      else
      {
        v6 = nullptr;
      }
      v13 = v6;
      sub_45FE80(*(this + 29), (int)v6, 2, 0, (int)v6, (int)this, 0);  // 调 对象注册
      v7 = *(uint32_t *)v6;
      v8 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);  // 调用虚函数（虚表槽 +124）
      nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8 + nRand % 30 - 15);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      nRand2 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
      result = (*(int (/*thiscall*/ **)(char *, int))(v7 + 112))(v13, v10 + nRand2 % 70 - 35);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    }
  }
  return result;
}



// 蓄雷 AI：BEFORE_THUNDER（52L；8624 相位）
// ------------------------------------------------------------
// 0x5A1BF0 sub_5A1BF0 —— setState 携参拦截（蓄雷参数装载 + 死亡落雷触发）
// 态 14 直播报 BEFORE_THUNDER；大状态 8（this+6556）分型进态 8 时从参数面取参——
// 型 1 写 this+2154/2155（目标/段距）、型 2 写 this+2158（偏移比例），他态进 8 时
// 清相位 this+8624/段号 this+2157；·0x4E33D0 基类收尾后反应态（vt+840）==5
// （死亡【推断】）时 50% 挂光环（·0x64BDF0，this+1814）并执行 ·0x5A1A90 死亡落雷
// ------------------------------------------------------------
int /*thiscall*/ sub_5A1BF0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: setState 携参拦截（蓄雷参数装载 + 死亡落雷触发）
{
  int result; // eax
  uint32_t *v7; // eax

  if ( ArgList == 14 )
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
             this,
             "BEFORE_THUNDER",  // 资源/动画 TAG BEFORE_THUNDER
             -1,
             0,
             0);
  if ( *(this + 1639) == 8  // this+6556 = 主状态镜像
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( ArgList == 8 )
      goto LABEL_9;
    *((uint8_t *)this + 8624) = 0;  // this+8624 = uAI8624
    *(this + 2157) = 0;  // this+8628 = 指挥计时戳
  }
  if ( ArgList == 8 )
  {
LABEL_9:
    v7 = *(uint32_t **)(LODWORD(fArg3) + 4);  // 调 取 64 位值低 32 位
    if ( *v7 == 1 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BEFORE_THUNDER", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      *(this + 2154) = *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4);  // this+8616 = uAI8616
      *(this + 2155) = *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 8);  // this+8620 = uAI8620
    }
    else if ( *v7 == 2 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BEFORE_THUNDER", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      *(this + 2158) = *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4);  // 调 取 64 位值低 32 位
    }
  }
  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( result == 5 )
  {
    if ( rand() % 100 < 50 )  // 调 以 16 位种子状态递推并返回 15 位结果
      sub_64BDF0(this, *(this + 1814));  // 调 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
    return sub_5A1A90(this);  // 调 死亡落雷（THUNDER_STRIKE）
  }
  return result;
}



// 基诺尔装载：R_GOBLIN_TALK/DMG/DIE 语音 + Monster/Goblin/{hcc1,Lkinolpants,Weapon03-2,acc1}.equ
//   （115L；8624 相位）
// ------------------------------------------------------------
// 0x5A1D20 sub_5A1D20 —— 落雷凯诺（型 1）装载
// 常量组 this+1698..1702 槽 = 2/2/2/3/4；语音 TAG 三连（R_GOBLIN_TALK/DMG/DIE 经
// ·0x4015C0 写语音槽）；四件 .equ（hcc1/Lkinolpants/Weapon03-2/acc1）经 vt+784
// 挂装；出场参数面 vt+384(0..5) 三对端值按帧进度 ·0x4049C0 插值写 this+106/+109/+2153；
// 相位 this+8624/段号 this+2157 清零，计时 this+2120=10、this+2121=2000
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5A1D20(float *this)  // 函数: 落雷凯诺（型 1）装载
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
  int pThis_3104; // eax
  uint32_t *pThis_2A0; // eax
  double pThis_71C; // st7
  int v16; // eax
  int pThis_71D; // edi
  uint32_t *pThis_2A02; // eax
  uint64_t pThis_71C2; // rax
  int pThis_1802; // eax
  int pThis_71D2; // edi
  uint32_t *pThis_2A03; // eax
  uint64_t result; // rax
  float v24; // [esp+44h] [ebp-2Ch]
  float v25; // [esp+44h] [ebp-2Ch]
  float v26; // [esp+44h] [ebp-2Ch]
  float v27; // [esp+48h] [ebp-28h]
  float v28; // [esp+48h] [ebp-28h]
  float v29; // [esp+48h] [ebp-28h]
  void *Block; // [esp+5Ch] [ebp-14h]
  void *Blocka; // [esp+5Ch] [ebp-14h]
  void *Blockb; // [esp+5Ch] [ebp-14h]
  int pThis_180; // [esp+60h] [ebp-10h]
  int v34; // [esp+60h] [ebp-10h]
  int v35; // [esp+60h] [ebp-10h]

  *((uint32_t *)this + 1698) = 2;  // this+6792 = 炮车/子类参数面槽 1
  *((uint32_t *)this + 1699) = 2;  // this+6796 = 炮车/子类参数面槽 2
  *((uint32_t *)this + 1700) = 2;  // this+6800 = 炮车/子类参数面槽 3
  *((uint32_t *)this + 1701) = 3;  // this+6804 = 炮车/子类参数面槽 4
  *((uint32_t *)this + 1702) = 4;  // this+6808 = 炮车/子类参数面槽 5
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/hcc1.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v3 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/Lkinolpants.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v6 = nullptr;
  pThis_3102 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v6);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调用虚函数（虚表槽 +4）
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v9 = sub_4BA9E0(pMem3, "Monster/Goblin/Weapon03-2.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v9 = nullptr;
  pThis_3103 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v9);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);  // 调用虚函数（虚表槽 +4）
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v12 = sub_4BA9E0(pMem4, "Monster/Goblin/acc1.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v12 = nullptr;
  pThis_3104 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v12);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);  // 调用虚函数（虚表槽 +4）
  Block = (void *)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  pThis_180 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  pThis_2A0 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v27 = (float)pThis_180;
  v24 = (float)(int)Block;
  pThis_71C = sub_4049C0(v24, v27, *pThis_2A0 - *((uint32_t *)this + 1820), *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820));  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v16 = *(uint32_t *)this;
  *(this + 106) = pThis_71C;  // this+106 模块时钟解冻门
  v34 = (*(int (/*thiscall*/ **)(float *, int))(v16 + 384))(this, 2);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  Blocka = (void *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  pThis_71D = *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820);
  pThis_2A02 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v28 = (float)(int)Blocka;
  v25 = (float)v34;
  pThis_71C2 = (uint64_t)sub_4049C0(v25, v28, *pThis_2A02 - *((uint32_t *)this + 1820), pThis_71D);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *((float *)&pThis_71C2 + 1) = *this;
  *((uint32_t *)this + 109) = pThis_71C2;  // this+436〔nAtkTableVal(推断)〕
  v35 = (*(int (/*thiscall*/ **)(float *, int))(HIDWORD(pThis_71C2) + 384))(this, 4);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 5);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  pThis_71D2 = *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820);
  Blockb = (void *)pThis_1802;
  pThis_2A03 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v29 = (float)(int)Blockb;
  v26 = (float)v35;
  result = (uint64_t)sub_4049C0(v26, v29, *pThis_2A03 - *((uint32_t *)this + 1820), pThis_71D2);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *((uint32_t *)this + 2153) = result;  // this+8612 = uAI8612
  *((uint8_t *)this + 8624) = 0;  // this+8624 = uAI8624
  *(this + 2157) = 0.0;  // this+8628 = 指挥计时戳
  *((uint32_t *)this + 2120) = 10;  // this+8480〔pAtkObj〕
  *((uint32_t *)this + 2121) = 2000;
  return result;
}



// ============================================================
// 【分区 4】胆小鬼哥布林（CowardGoblin）（0x5A2020-0x5A2E30）
// 证据：Goblin/CowardGoblin.mob 引用、POWER_UP/POWER_DOWN 强化弱化、
//       MonsterPowerUp/MonsterPowerDown.ptl、B_CWGBN_01 登场曲、CwGobSantaBeard.equ

// 子类扩展字段复位（this+8612..8644, 29L）
// ------------------------------------------------------------
// 0x5A2020 sub_5A2020 —— 胆小鬼子类扩展字段复位
// 惰性经 ·0x422E70 取资源 875-878 入全局 dword_9B9328..9B9334（强化/弱化表现
// 资源对【推断：音效】）；清 this+8612..8644 面（+8624 置浮点 1.0）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2020(int this)  // 函数: 胆小鬼子类扩展字段复位
{
  if ( dword_9B9328 == 0 )
  {
    dword_9B9328 = sub_422E70(875);  // 调 存 CStringManager::getStr 取本地化串
    dword_9B932C = sub_422E70(876);  // 调 存 CStringManager::getStr 取本地化串
  }
  if ( dword_9B9330 == 0 )
  {
    dword_9B9330 = sub_422E70(877);  // 调 存 CStringManager::getStr 取本地化串
    dword_9B9334 = sub_422E70(878);  // 调 存 CStringManager::getStr 取本地化串
  }
  *(uint32_t *)(this + 8616) = 0;  // this+8616 强化粒子句柄
  *(uint32_t *)(this + 8620) = 0;  // this+8620 弱化粒子句柄
  *(uint32_t *)(this + 8612) = -1;  // this+8612 锁定/相位字节 A
  *(uint32_t *)(this + 8624) = 1065353216;  // this+8624 【推断】子类AI槽
  *(uint32_t *)(this + 8628) = 0;  // this+8628 【推断】指挥计时戳
  *(uint32_t *)(this + 8632) = 0;  // this+8632 【推断】子类 AI 资源/计数槽
  *(uint32_t *)(this + 8636) = 0;  // this+8636 【推断】传送/钻地相位槽
  *(uint32_t *)(this + 8640) = 0;  // this+8640 【推断】出土相位槽
  *(uint8_t *)(this + 8644) = 0;  // this+8644 【推断】相位计数槽
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A20C0 sub_5A20C0 —— 释放双粒子句柄
// this+2154/2155 各经 vt+0 虚调销毁后清槽
// ------------------------------------------------------------
int /*thiscall*/ sub_5A20C0(uint32_t *this)  // 函数: 释放双粒子句柄
{
  int (/*thiscall*/ ***fld_e2154)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e2155)(uint32_t, int); // ecx

  fld_e2154 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2154);  // this+8616 = uAI8616
  if ( fld_e2154 != nullptr )  // 若 fld_e2154 有效（非空）
    result = (**fld_e2154)(fld_e2154, 1);  // 调 fld_e2154 的虚函数（vt+0）
  fld_e2155 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2155);  // this+8620 = uAI8620
  *(this + 2154) = 0;  // this+8616 = uAI8616
  if ( fld_e2155 != nullptr )  // 若 fld_e2155 有效（非空）
    result = (**fld_e2155)(fld_e2155, 1);  // 调 fld_e2155 的虚函数（vt+0）
  *(this + 2155) = 0;  // this+8620 = uAI8620
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A2100 sub_5A2100 —— setState 基类转发 + 态 5 光环
// ·0x4E33D0 收尾转发；进入态 5 时 50% 概率挂战斗光环（·0x64BDF0，this+1814）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2100(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: setState 基类转发 + 态 5 光环
{
  int result; // eax
  int nRand; // eax
  int v8; // et2

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 5 )
  {
    nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
    v8 = nRand % 100;
    result = nRand / 100;
    if ( v8 < 50 )
      return sub_64BDF0(this, *(this + 1814));  // 调 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
  }
  return result;
}



// mob 引用：Goblin/CowardGoblin.mob（胆小鬼哥布林数据文件, 34L）
// ------------------------------------------------------------
// 0x5A2150 sub_5A2150 —— 按 nArg2 挂 CowardGoblin.mob 并钳制碰撞体
// vt+1024 设模型引用（Goblin/CowardGoblin.mob），按缩放前后差值经 vt+736/740 读、
// vt+732 写重算并钳制碰撞尺寸
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2150(int *this, int nArg2)  // 函数: 按 nArg2 挂 CowardGoblin.mob 并钳制碰撞体
{
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v8; // [esp+Ch] [ebp-4h]
  bool v9; // [esp+1Bh] [ebp+Bh]

  v9 = *(uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3) > nArg2;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
  (*(void (/*thiscall*/ **)(int *, int, const char *))(*this + 1024))(this, nArg2, "Goblin/CowardGoblin.mob");  // 调用虚函数（虚表槽 +1024）
  v5 = *this;
  if ( !v9 )
  {
    v4 += (*(int (/*thiscall*/ **)(int *))(v5 + 740))(this) - v8;  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 740))(this) < v4 )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
      goto LABEL_3;
LABEL_5:
    v6 = v4;
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 732))(this, v6, 0, 1);  // 调用虚函数（虚表槽 +732）
  }
  if ( v4 < (*(int (/*thiscall*/ **)(int *))(v5 + 740))(this) )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    goto LABEL_5;
LABEL_3:
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 732))(this, v6, 0, 1);  // 调用虚函数（虚表槽 +732）
}



// AI 相位辅助（67L）
// ------------------------------------------------------------
// 0x5A2200 sub_5A2200 —— 分身/攻击参数面配置（this+7531..7596）
// 整面清零后按 nArg2（档 0/1/2）× nArg3（模式 0/2）写档位项：this+7596 = 50/-100/-20、
// +7568 = 1、+7572 = 2 等组合【推断：强化/弱化档位参数】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2200(int this, int nArg2, int nArg3)  // 函数: 分身/攻击参数面配置（this+7531..7596）
{
  int result; // eax

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
  *(uint32_t *)(this + 7572) = 0;  // this+7572 【推断】模式 2 档
  *(uint32_t *)(this + 7568) = 0;  // this+7568 【推断】激活/模式槽
  *(uint32_t *)(this + 7564) = 0;  // this+7564 【推断】形态/模式槽
  *(uint32_t *)(this + 7588) = 0;  // this+7588 【推断】形态槽
  *(uint32_t *)(this + 7584) = 0;  // this+7584 【推断】形态槽
  *(uint32_t *)(this + 7580) = 0;  // this+7580 【推断】攻击面门字节
  *(uint32_t *)(this + 7576) = 0;  // this+7576 相位槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 【推断】段号横向偏置
  if ( nArg3 != 0 )
  {
    if ( nArg3 != 2 )
      return result;
    if ( nArg2 != 0 )
    {
      if ( nArg2 != 1 )
      {
        if ( nArg2 != 2 )
          return result;
        goto LABEL_6;
      }
    }
    else
    {
      *(uint32_t *)(this + 7596) = 50;  // this+7596 【推断】段号横向偏置
    }
    *(uint32_t *)(this + 7572) = 2;  // this+7572 【推断】模式 2 档
    *(uint32_t *)(this + 7568) = 1;  // this+7568 【推断】激活/模式槽
    return result;
  }
  if ( nArg2 == 0 )
  {
LABEL_6:
    *(uint32_t *)(this + 7596) = -100;  // this+7596 【推断】段号横向偏置
    return result;
  }
  if ( (unsigned int)(nArg2 - 1) <= 1 )
  {
    *(uint32_t *)(this + 7596) = -20;  // this+7596 【推断】段号横向偏置
    *(uint32_t *)(this + 7568) = 1;  // this+7568 【推断】激活/模式槽
    *(uint32_t *)(this + 7572) = 2;  // this+7572 【推断】模式 2 档
  }
  return result;
}



// AI 相位辅助（60L）
// ------------------------------------------------------------
// 0x5A2300 sub_5A2300 —— 统计场上已强化同类数
// 遍历对象列表筛 529 型且内部标记容器（obj+83/84 槽）含标签 19（与 ·0x4DAB60(19)
// 同一标签体系）且非本尊，返回计数；供强化/弱化档位换算（·0x5A2490 中 ×2 钳 1-29）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2300(uint32_t *this)  // 函数: 统计场上已强化同类数
{
  int v1; // ebx
  unsigned int i; // esi
  int fld_e29; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v10; // edx
  uint32_t *v11; // edx
  uint32_t *v12; // ecx
  uint32_t *v13; // eax

  v1 = 0;
  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v5 = *(uint32_t *)(fld_e29 + 8);
    v6 = v5 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= v6 )
      break;
    v7 = *(uint32_t *)(fld_e29 + 8);
    if ( v7 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v7) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj = *(uint32_t *)(v7 + 4 * i);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v10 = *(uint32_t *)(fld_e292 + 8);
      if ( v10 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v10) >> 2 )  // 向量元素数 = (end−begin)/4
        v11 = *(uint32_t **)(v10 + 4 * i);
      else
        v11 = nullptr;
      v12 = (uint32_t *)v11[84];
      v13 = (uint32_t *)v11[83];
      if ( v13 != v12 )
      {
        do
        {
          if ( *v13 == 19 )
            break;
          ++v13;
        }
        while ( v13 != v12 );
        if ( v13 != v12 && this != v11 )  // 若 v13 != v12 与/或 this != v11
          ++v1;
      }
    }
  }
  return v1;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A23C0 sub_5A23C0 —— 体型缩放步进
// this+2156 处于 (1.0, 1.5) 开区间时 ±0.095（nArg2=0 加 / 1 减），经 ·0x4EB4B0/
// ·0x4EB2C0 与槽位 this+2157..2160 的 ·0x4EB6E0/+0x4EB6A0 成套应用模型缩放
// ------------------------------------------------------------
void /*thiscall*/ sub_5A23C0(float *this, int nArg2)  // 函数: 体型缩放步进
{
  double fld_e2156; // st7
  int v4; // edx
  float fld_e21562; // ebx
  uint32_t *pThis_86D; // edi
  float fld_e21563; // [esp-Ch] [ebp-1Ch]
  uint32_t v8[3]; // [esp+4h] [ebp-Ch]
  int i; // [esp+18h] [ebp+8h]

  fld_e2156 = *(this + 2156);  // this+8624 = uAI8624
  v8[0] = 1036831949;  // 常量 0.1f
  v8[1] = -1110651699;  // 浮点常量 44.8f
  if ( fld_e2156 > 1.0 && *(this + 2156) < 1.5 )  // this+8624 = uAI8624
  {
    v4 = *(uint32_t *)this;
    fld_e21562 = *(this + 2156);  // this+8624 = uAI8624
    *(this + 2156) = *(float *)&v8[nArg2] + fld_e21562;  // this+8624 = uAI8624
    *(float *)&v8[2] = fld_e21562;
    (*(void (/*thiscall*/ **)(float *))(v4 + 688))(this);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
    sub_4EB4B0(fld_e21562);  // 调 与 ·0x4EB2C0 同构（差异：·sub_4923F0 按倒数缩放）
    fld_e21563 = *(this + 2156);  // this+8624 = uAI8624
    (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 688))(this);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
    sub_4EB2C0(fld_e21563);  // 调 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
    pThis_86D = this + 2157;
    for ( i = 4; i != 0; --i )  // 循环：i 从 4 递减到 0
    {
      if ( *pThis_86D != 0 )
      {
        sub_4EB6E0(fld_e21562);  // 调 与 ·0x4EB6A0 同构（差异：调 ·0x4EB4B0）
        sub_4EB6A0(*(this + 2156));  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
      }
      ++pThis_86D;
    }
  }
}



// 强化状态：POWER_UP 播报（46L）
// ------------------------------------------------------------
// 0x5A2490 sub_5A2490 —— 胆小鬼强化（POWER_UP）
// 门判：nArg2 为 529 型、本尊 vt+724 未标记、标签 19 未中（·0x4DAB60）、同阵营
// （vt+376）；按 ·0x5A2300 计数×2（钳 1-29）经 ·0x5A2150 换 mob；vt+192>0 时播
// dword_9B9328 资源对（·0x50EF20）、清 this+2153 并复位粒子柄 this+2154（vt+12），
// 播报 POWER_UP；末尾 ·0x5A23C0(this,0) 体型放大一档
// ------------------------------------------------------------
void /*thiscall*/ sub_5A2490(int *this, int nArg2)  // 函数: 胆小鬼强化（POWER_UP）
{
  int v3; // edi
  int v4; // eax
  int nRand; // eax
  int v6; // eax
  int pPowerUpParticle; // ecx  | +0x21A8 → 强化粒子句柄〔粒子句柄〔通用偏移表 dword2154〕；5A2A50 存 MonsterPowerUp.ptl（CNCowardGoblin；va=005A2020）

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
    && (uint8_t)sub_4DAB60(19) != 0 )  // 调 标签/条件集合成员判定
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);  // 调用虚函数（虚表槽 +376）
    if ( v3 == (*(int (/*thiscall*/ **)(int *))(*this + 376))(this) )  // 调用虚函数（虚表槽 +376）
    {
      v4 = 2 * sub_5A2300(this);  // 调 统计场上已强化同类数
      if ( v4 > 1 )
      {
        if ( v4 >= 29 )
          v4 = 29;
      }
      else
      {
        v4 = 1;
      }
      sub_5A2150(this, v4);  // 调 按 nArg2 挂 CowardGoblin.mob 并钳制碰撞体
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 192))(this) > 0 )  // 调用虚函数（虚表槽 +192）
      {
        nRand = rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
        v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 64))(this, dword_9B9328[nRand]);  // 调用虚函数（虚表槽 +64）【推断: 取观察者容器（懒创建 0x44 字节 sb_499960(thi…】
        sub_50EF20(v6, 0, -1);  // 调 气泡文本设置与量算（行数/半高/倒计时）
        pPowerUpParticle = *(this + 2154);  // this+8616 = uAI8616
        *(this + 2153) = 0;  // this+8612 = uAI8612
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pPowerUpParticle + 12))(pPowerUpParticle, 0);  // 调用虚函数（虚表槽 +12）
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "POWER_UP", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      }
      sub_5A23C0((float *)this, 0);  // 调 体型缩放步进
    }
  }
}



// 弱化状态：POWER_DOWN 播报（103L；RTTI cast 目标解算）
// ------------------------------------------------------------
// 0x5A2590 sub_5A2590 —— 胆小鬼弱化（POWER_DOWN）
// 门判与 ·0x5A2490 同；计数 -1×2（钳 1-29）换 mob，播 dword_9B9330 资源对、
// 置 this+2153=1、复位粒子柄 this+2155，播报 POWER_DOWN 并 ·0x5A23C0(this,1)
// 缩小一档；再扫碰撞对象表 cast CNCowardGoblin，本尊为 ·0x425A00 命中项时以
// ·0x422E70(879) 格式串组公告（·0x43BEE0 跑马灯，色 -10158236）；返回 ·0x4D9170(nArg2)
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2590(int *this, int nArg2)  // 函数: 胆小鬼弱化（POWER_DOWN）
{
  int v3; // edi
  int v4; // eax
  int nRand; // eax
  int v6; // eax
  int pPowerDownParticle; // ecx  | +0x21AC → 弱化粒子句柄〔粒子句柄〔通用偏移表 dword2155〕；5A2A50 存 MonsterPowerDown.ptl（CNCowardGoblin；va=005A2020）
  unsigned int i; // edi
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int pObj; // ecx
  int v16; // eax
  int v17; // edx
  int v18; // eax
  const char *v19; // eax
  int v21; // [esp-8h] [ebp-214h]
  int v22; // [esp-4h] [ebp-210h]
  char Buffer[512]; // [esp+8h] [ebp-204h] BYREF
  int dword_796E502; // [esp+208h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
    && (uint8_t)sub_4DAB60(19) != 0 )  // 调 标签/条件集合成员判定
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);  // 调用虚函数（虚表槽 +376）
    if ( v3 == (*(int (/*thiscall*/ **)(int *))(*this + 376))(this) )  // 调用虚函数（虚表槽 +376）
    {
      v4 = 2 * (sub_5A2300(this) - 1);  // 调 统计场上已强化同类数
      if ( v4 > 1 )
      {
        if ( v4 >= 29 )
          v4 = 29;
      }
      else
      {
        v4 = 1;
      }
      sub_5A2150(this, v4);  // 调 按 nArg2 挂 CowardGoblin.mob 并钳制碰撞体
      nRand = rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
      v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 64))(this, dword_9B9330[nRand]);  // 调用虚函数（虚表槽 +64）【推断: 取观察者容器（懒创建 0x44 字节 sb_499960(thi…】
      sub_50EF20(v6, 0, -1);  // 调 气泡文本设置与量算（行数/半高/倒计时）
      pPowerDownParticle = *(this + 2155);  // this+8620 = uAI8620
      *(this + 2153) = 1;  // this+8612 = uAI8612
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pPowerDownParticle + 12))(pPowerDownParticle, 0);  // 调用虚函数（虚表槽 +12）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "POWER_DOWN", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      sub_5A23C0((float *)this, 1);  // 调 体型缩放步进
      for ( i = 0; ; ++i )
      {
        v9 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调用虚函数（虚表槽 +80）
        v10 = *(uint32_t *)(v9 + 120);
        v11 = v9 + 116;
        v12 = v10 != 0 ? (*(uint32_t *)(v11 + 8) - v10) >> 2 : 0;  // 向量元素数 = (end−begin)/4
        if ( (int)i >= v12 )
          break;
        v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 80))(this, v22);  // 调用虚函数（虚表槽 +80）
        v14 = *(uint32_t *)(v13 + 120);
        if ( v14 != 0 && i < (*(uint32_t *)(v13 + 124) - v14) >> 2 )  // 向量元素数 = (end−begin)/4
          pObj = *(uint32_t *)(v14 + 4 * i);
        else
          pObj = 0;
        v22 = 529;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 40))(pObj) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
        {
          v16 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调用虚函数（虚表槽 +80）
          v17 = *(uint32_t *)(v16 + 120);
          if ( v17 != 0 && i < (*(uint32_t *)(v16 + 124) - v17) >> 2 )  // 向量元素数 = (end−begin)/4
            v18 = *(uint32_t *)(v17 + 4 * i);
          else
            v18 = 0;
          if ( __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                 v18,
                 0,
                 &IRDCollisionObject `RTTI Type Descriptor',
                 &CNCowardGoblin `RTTI Type Descriptor',
                 0) != 0 )
          {
            (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调用虚函数（虚表槽 +80）
            if ( this == (int *)sub_425A00(i) )  // 调 元素取值（+30 组）
            {
              v21 = sub_4633B0(this);  // 调 std::string 取数据指针（SSO 判定）
              v19 = (const char *)sub_422E70(879);  // 调 存 CStringManager::getStr 取本地化串
              sprintf(Buffer, v19, v21);  // 调 格式化到缓冲
              sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -10158236, 0, -1);  // dword_8F8528 = 主管理器
            }
            return sub_4D9170(nArg2);  // 调 消亡通知
          }
        }
      }
    }
  }
  return sub_4D9170(nArg2);  // 调 消亡通知
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A27A0 sub_5A27A0 —— 强化粒子落地（this+2154 驱动）
// 句柄 vt+68 就绪则置 this+2153=-1；取句柄数据（vtbl+40/+92）经 vt+80 生成物件，
// 携本尊坐标（vt+120/124/128）交 ·0x4600B0 处理【推断：强化特效实体化】
// ------------------------------------------------------------
void /*thiscall*/ sub_5A27A0(uint32_t *this)  // 函数: 强化粒子落地（this+2154 驱动）
{
  int fld_e2154; // edi
  int v3; // edx
  void *v4; // eax
  int v5; // [esp-Ch] [ebp-30h]
  int v6; // [esp-8h] [ebp-2Ch]
  int v7; // [esp-4h] [ebp-28h]
  uint8_t v8[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v10; // [esp+20h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2154) + 68))(*(this + 2154)) != 0 )  // this+8616 = uAI8616
    *(this + 2153) = -1;  // this+8612 = uAI8612
  fld_e2154 = *(uint32_t *)*(this + 2154);  // this+8616 = uAI8616
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  (*(void (/*thiscall*/ **)(uint32_t))(fld_e2154 + 40))(*(this + 2154));  // this+8616 = uAI8616
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2154) + 92))(*(this + 2154), v8);  // this+8616 = uAI8616
  v3 = *this;
  v10 = 0;
  v4 = (void *)(*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint8_t *))(v3 + 80))(this, 2, 0, v8);  // 调用虚函数（虚表槽 +80）
  sub_4600B0(v4, v5, v6, v7);  // 调 演播层注册(槽号)
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 堆释放
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A2850 sub_5A2850 —— 与 ·0x5A27A0 同构
// （差异：驱动粒子柄 this+2155，弱化特效落地）
// ------------------------------------------------------------
void /*thiscall*/ sub_5A2850(uint32_t *this)  // 函数: 与 ·0x5A27A0 同构
{
  int fld_e2155; // edi
  int v3; // edx
  void *v4; // eax
  int v5; // [esp-Ch] [ebp-30h]
  int v6; // [esp-8h] [ebp-2Ch]
  int v7; // [esp-4h] [ebp-28h]
  uint8_t v8[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v10; // [esp+20h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2155) + 68))(*(this + 2155)) != 0 )  // this+8620 = uAI8620
    *(this + 2153) = -1;  // this+8612 = uAI8612
  fld_e2155 = *(uint32_t *)*(this + 2155);  // this+8620 = uAI8620
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  (*(void (/*thiscall*/ **)(uint32_t))(fld_e2155 + 40))(*(this + 2155));  // this+8620 = uAI8620
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2155) + 92))(*(this + 2155), v8);  // this+8620 = uAI8620
  v3 = *this;
  v10 = 0;
  v4 = (void *)(*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint8_t *))(v3 + 80))(this, 2, 0, v8);  // 调用虚函数（虚表槽 +80）
  sub_4600B0(v4, v5, v6, v7);  // 调 演播层注册(槽号)
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 堆释放
}



// 登场曲：sub_406D60 写 "B_CWGBN_01"（胆小鬼哥布林曲目槽, 47L）
// ------------------------------------------------------------
// 0x5A2900 sub_5A2900 —— 胆小鬼哥布林行为字相位机
// 相位 this+1787 分派：case 0 入场初始化（vt+1284）+ 困难级挂 BGM B_CWGBN_01
// （·0x406D60）；宿主 this+1813 有无定走向——case 4/5 无宿主写行为字 13、
// case 13/14/15 有宿主写 4（均经 vt+1104）——与 ·0x5A1930 同构（差异：无随机
// 行动分流，行动由 POWER_UP/POWER_DOWN 事件驱动）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2900(int *this)  // 函数: 胆小鬼哥布林行为字相位机
{
  int result; // eax

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148 = nBigState
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
      if ( *(this + 1943) == 3 )  // this+7772 = nCounterState
        result = sub_406D60("B_CWGBN_01");  // 调 std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result == 0 )
        goto LABEL_7;
      break;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result == 0 )
LABEL_7:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
      break;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result != 0 )  // 若结果非 0（成功）
        goto LABEL_11;
      break;
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_11:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调用虚函数（虚表槽 +1104）
      break;
    default:
      return result;
  }
  return result;
}



// AI 相位门（this+8612/8644）
// ------------------------------------------------------------
// 0x5A29E0 sub_5A29E0 —— 胆小鬼步进：首帧自强化 + 粒子落地选择
// 基类 ·0x4E1780 后，this+8644==0 时按强化计数（·0x5A2300 ×2 钳 1-29）换 mob 并
// ·0x5A23C0(this,0) 放大一档、置 this+8644=1；随后按 this+8612 选 ·0x5A27A0（0）/
// ·0x5A2850（1）落地对应粒子
// ------------------------------------------------------------
void /*thiscall*/ sub_5A29E0(int this)  // 函数: 胆小鬼步进：首帧自强化 + 粒子落地选择
{
  int v2; // eax
  int uPowerMode; // eax  | +0x21A4 → 【推断】强化/弱化模式〔5A29E0 读：0 → 5A27A0 落地 / 1 → 5A2850（CNCowardGoblin；va=005A29E0）

  sub_4E1780((uint32_t *)this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( *(uint8_t *)(this + 8644) == 0 )  // this+8644 【推断】相位计数槽
  {
    v2 = 2 * sub_5A2300((uint32_t *)this);  // 调 统计场上已强化同类数
    if ( v2 > 1 )
    {
      if ( v2 >= 29 )
        v2 = 29;
    }
    else
    {
      v2 = 1;
    }
    sub_5A2150((int *)this, v2);  // 调 按 nArg2 挂 CowardGoblin.mob 并钳制碰撞体
    sub_5A23C0((float *)this, 0);  // 调 体型缩放步进
    *(uint8_t *)(this + 8644) = 1;  // this+8644 【推断】相位计数槽
  }
  uPowerMode = *(uint32_t *)(this + 8612);  // this+8612 锁定/相位字节 A
  if ( uPowerMode != 0 )
  {
    if ( uPowerMode == 1 )
      sub_5A2850((uint32_t *)this);  // 调 与 ·0x5A27A0 同构
  }
  else
  {
    sub_5A27A0((uint32_t *)this);  // 调 强化粒子落地（this+2154 驱动）
  }
}



// 胆小鬼装载：R_GOBLIN_* 语音 + {gcc1,Weapon01,CwGobSantaBeard}.equ +
//   Common/CommonEffect/Particle/{MonsterPowerUp,MonsterPowerDown}.ptl（65L）
// ------------------------------------------------------------
// 0x5A2A50 sub_5A2A50 —— 胆小鬼哥布林装载
// 常量组 this+1698..1702 槽 = 2/2/2/3/4；语音 TAG 三连（R_GOBLIN_TALK/DMG/DIE 经
// ·0x4015C0）；三件 .equ（gcc1/Weapon01/CwGobSantaBeard）挂装并存柄 this+2157..2159；
// 参数 this+1830=100、+1831=570、+1839=-30；创建强化/弱化双粒子（·0x428F30，
// MonsterPowerUp/Down.ptl）存 this+2154/2155 并以 vt+112 绑定本尊
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2A50(uint32_t *this)  // 函数: 胆小鬼哥布林装载
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *v5; // edi
  char *pMem3; // eax
  char *v7; // edi
  uint32_t *pMem4; // eax
  uint32_t *v9; // eax
  uint32_t *pMem5; // eax
  uint32_t *v11; // eax

  *(this + 1698) = 2;  // this+6792 = 炮车/子类参数面槽 1
  *(this + 1699) = 2;  // this+6796 = 炮车/子类参数面槽 2
  *(this + 1700) = 2;  // this+6800 = 炮车/子类参数面槽 3
  *(this + 1701) = 3;  // this+6804 = 炮车/子类参数面槽 4
  *(this + 1702) = 4;  // this+6808 = 炮车/子类参数面槽 5
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/gcc1.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  (*(void (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  *(this + 2157) = v3;  // this+8628 = 指挥计时戳
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v5 = sub_4BA9E0(pMem2, "Monster/Goblin/Weapon01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v5 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v5);  // 调用虚函数（虚表槽 +784）
  *(this + 2158) = v5;  // this+8632〔bDevourFlag(推断)〕
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v7 = sub_4BA9E0(pMem3, "Monster/Goblin/CwGobSantaBeard.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v7 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v7);  // 调用虚函数（虚表槽 +784）
  *(this + 2159) = v7;  // this+8636 = pDollTarget
  *(this + 1830) = 100;
  *(this + 1839) = -30;
  *(this + 1831) = 570;
  pMem4 = operator new(0x12Cu);  // operator new 分配 300 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v9 = sub_428F30(pMem4, (int)"Common/CommonEffect/Particle/MonsterPowerUp.ptl", (int)this);  // 调 CNRDObjectParticleCreater 构造
  else
    v9 = nullptr;
  *(this + 2154) = v9;  // this+8616 = uAI8616
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v9 + 112))(v9, this);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
  pMem5 = operator new(0x12Cu);  // operator new 分配 300 字节
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v11 = sub_428F30(pMem5, (int)"Common/CommonEffect/Particle/MonsterPowerDown.ptl", (int)this);  // 调 CNRDObjectParticleCreater 构造
  else
    v11 = nullptr;
  *(this + 2155) = v11;  // this+8620 = uAI8620
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v11 + 112))(v11, this);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A2C50 sub_5A2C50 —— 指令接收处理（CommandReceive）
// ·0x4D90A0 解包；包型 10 → 写行为字 5（vt+1104）；包型 11 → 头顶气泡
// ·0x4D84F0 CommandReceive.ani、记宿主 this+1813=pArg2[3]、写行为字 20、
// ·0x49C5F0(10,...,500) 延时表现
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2C50(uint32_t *this, uint32_t *pArg2)  // 函数: 指令接收处理（CommandReceive）
{
  int result; // eax
  int v4; // edx

  sub_4D90A0(pArg2);  // 调 校验指令包
  if ( *pArg2 == 10 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);  // 调用虚函数（虚表槽 +1104）
  result = *pArg2 - 11;
  if ( *pArg2 == 11 )
  {
    sub_4D84F0(0, 0);  // 头顶气泡 CommandReceive.ani（同 0x4D82D0 结构）
    v4 = *this;
    *(this + 1813) = pArg2[3];  // this+7252 = pTarget7252
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 1104))(this, 20);  // 调用虚函数（虚表槽 +1104）
    return sub_49C5F0(10, 0, 0, 500);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A2CC0 sub_5A2CC0
// 基类帧驱动转发（thunk 桩）：唯一语句转调 ·0x4E1780（大状态帧推进器），
// 本函数自身零逻辑，挂牛头系虚表槽供派生类默认继承
// ------------------------------------------------------------
// attributes: thunk
char /*thiscall*/ sub_5A2CC0(uint32_t *this)  // 实现：本函数自身零逻辑，挂牛头系虚表槽供派生类默认继承
{
  return sub_4E1780(this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A2CD0 sub_5A2CD0 —— 攻击参数面降档（弱化方向调整）
// 档位组合（nArg2=0,nArg3=2 或 1<=nArg2<=2,nArg3=0）命中时对 +7620 面参数块 +36
// 偏移的速率项 ×0.769（=÷1.3）；nArg3==2 清 this+1892 槽、nArg3==0 清 this+7556
// 字节、置 this+1899=30，并对 this+830 浮点 -0.3（·0x41A5E0 读 / ·0x41A590 写）后
// vt+676 收尾——与 ·0x5A2D80 互为还原对
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2CD0(uint32_t *this, int nArg2, int nArg3)  // 函数: 攻击参数面降档（弱化方向调整）
{
  bool v4; // zf
  int result; // eax
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+Ch] [ebp+8h]

  if ( nArg2 != 0 )
  {
    if ( nArg2 <= 0 || nArg2 > 2 )  // 若 nArg2 <= 0 与/或 nArg2 > 2
      goto LABEL_8;
    v4 = nArg3 == 0;
  }
  else
  {
    v4 = nArg3 == 2;
  }
  if ( v4 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.76923078;  // this+7620 = 速度/属性参数对象
LABEL_8:
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
      *(this + 1892) = 0;  // this+7568 = 激活/模式槽
  }
  else
  {
    v6 = *this;
    *((uint8_t *)this + 7556) = 0;  // this+7556 = 攻击面模式字节
    *(this + 1899) = 30;  // this+7596 = 段号横向偏置
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v7)) - 0.30000001;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v7, v8, v9);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A2D80 sub_5A2D80 —— 与 ·0x5A2CD0 互为还原对（差异：升档方向）
// 速率项 ×1.3、this+830 浮点 +0.3、置 this+7556=1、this+1899=30、this+1892=2
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2D80(uint32_t *this, int nArg2, int nArg3)  // 函数: 与 ·0x5A2CD0 互为还原对（差异：升档方向）
{
  bool v4; // zf
  int result; // eax
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+Ch] [ebp+8h]

  if ( nArg2 != 0 )
  {
    if ( nArg2 <= 0 || nArg2 > 2 )  // 若 nArg2 <= 0 与/或 nArg2 > 2
      goto LABEL_8;
    v4 = nArg3 == 0;
  }
  else
  {
    v4 = nArg3 == 2;
  }
  if ( v4 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 1.3;  // this+7620 = 速度/属性参数对象
LABEL_8:
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
      *(this + 1892) = 2;  // this+7568 = 激活/模式槽
  }
  else
  {
    v6 = *this;
    *((uint8_t *)this + 7556) = 1;  // this+7556 = 攻击面模式字节
    *(this + 1899) = 30;  // this+7596 = 段号横向偏置
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v7, v8, v9);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  }
  return result;
}



// ============================================================
// 【分区 5】牛头兵 Tau（0x5A2E30-0x5A5180）
// 证据：B_TAUARMY_01 登场曲、R_TAU_TALK/DMG + TAU_DIE 语音、TAU_BREATH/TAU_GROUND_HIT、
//       STATEMACHINE:TACKLESTART 冲撞状态机、TAU_RUSH_LOOP、TAU_COMMAND、
//       AURA_DEFEND + TAU_ROAR、GuardSpark 格挡 = vmt200 覆写（0x5A4B20）

// 登场曲：sub_406D60 写 "B_TAUARMY_01"（牛头军曲目槽, 60L）
// ------------------------------------------------------------
// 0x5A2E30 sub_5A2E30 —— 牛头兵行为字相位机
// 相位 this+1787 分派：case 0 入场初始化（vt+1284）+ 困难级挂 BGM B_TAUARMY_01
// （·0x406D60）；有宿主（this+1813）时 case 4 掷 10% 写行为字 5、case 5 掷 1% 写 4，
// 无宿主 case 4/5 写 13，case 13/14/15 收束写 4（均经 vt+1104）——与 ·0x5A2900
// 同构（差异：随机分流阈值 10%/1%，无外部分支函数）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2E30(int *this)  // 函数: 牛头兵行为字相位机
{
  int result; // eax
  int nRand; // eax
  int v4; // et2
  int nRand2; // eax
  int v6; // et2

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148 = nBigState
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
      if ( *(this + 1943) == 3 )  // this+7772 = nCounterState
        result = sub_406D60("B_TAUARMY_01");  // 调 std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == 0 )  // this+7252 = pTarget7252
        goto LABEL_5;
      nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
      v4 = nRand % 100;
      result = nRand / 100;
      if ( v4 < 10 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);  // 调用虚函数（虚表槽 +1104）
      break;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
      {
        nRand2 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
        v6 = nRand2 % 100;
        result = nRand2 / 100;
        if ( v6 < 1 )
          goto LABEL_12;
      }
      else
      {
LABEL_5:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
      }
      break;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_12:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调用虚函数（虚表槽 +1104）
      break;
    default:
      return result;
  }
  return result;
}



// 牛头兵装载：R_TAU_TALK / R_TAU_DMG / TAU_DIE 语音 + Monster/Tau/{Weapon01,Horn01}.equ（49L）
// ------------------------------------------------------------
// 0x5A2F30 sub_5A2F30 —— 牛头兵标准型装载
// AI 阈值面 this+1698..1702 写 2/2/2/3/4；语音 TAG 三枚（R_TAU_TALK / R_TAU_DMG / TAU_DIE）
// 经 ·0x4015C0 写入语音槽，vt+784 挂装 Weapon01 / Horn01 两件 .equ 后 vt+688 刷新外观
// sub_4EB2C0 / sub_4EB6A0 部件缩放 0.8；攻击参数面 this+1830=30 / +1839=-30 / +1831=300
// 字节 this+7542 置 1【推断：攻击判定面使能】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2F30(uint32_t *this)  // 函数: 牛头兵标准型装载
{
  char *pMem; // eax
  char *v3; // edi
  char *v4; // ebx
  int pObj; // eax
  char *pMem2; // eax
  int pObj2; // eax
  int result; // eax

  *(this + 1698) = 2;  // this+6792 = 炮车/子类参数面槽 1
  *(this + 1699) = 2;  // this+6796 = 炮车/子类参数面槽 2
  *(this + 1700) = 2;  // this+6800 = 炮车/子类参数面槽 3
  *(this + 1701) = 3;  // this+6804 = 炮车/子类参数面槽 4
  *(this + 1702) = 4;  // this+6808 = 炮车/子类参数面槽 5
  sub_4015C0("R_TAU_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("TAU_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v4 = sub_4BA9E0(pMem, "Monster/Tau/Weapon01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v4 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v4);  // 调用虚函数（虚表槽 +784）
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v3 = sub_4BA9E0(pMem2, "Monster/Tau/Horn01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调用虚函数（虚表槽 +4）
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
  sub_4EB2C0(0.80000001);  // 调 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  sub_4EB6A0(0.80000001);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  result = sub_4EB6A0(0.80000001);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  *(this + 1830) = 30;
  *(this + 1839) = -30;
  *(this + 1831) = 300;
  *((uint8_t *)this + 7542) = 1;
  return result;
}



// 语音播报：R_TAU_TALK（this+8608 相位）
// ------------------------------------------------------------
// 0x5A30B0 sub_5A30B0 —— 大状态 8 入场拦截 · R_TAU_TALK 播报
// ·0x4E33D0 基类状态收尾后，大状态 8（攻击）进入时复位相位字节 this+8608
// 攻击段号槽 this+7028==2 时经 vt+212 播报 R_TAU_TALK（受击谈话语音【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A30B0(uint8_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 大状态 8 入场拦截 · R_TAU_TALK 播报
{
  int result; // eax

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 8 )
  {
    *(this + 8608) = 0;  // this+8608 骑乘/骑手槽
    result = sub_41A5E0((unsigned int)(this + 7028));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 2 )
      return (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
               this,
               "R_TAU_TALK",  // 资源/动画 TAG R_TAU_TALK
               -1,
               0,
               0);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A3110 sub_5A3110 —— 指令包响应（指令 6 → 行为字 20）
// ·0x4D90A0 解析指令包；指令码 6 时先 ·0x4D84F0 清头顶气泡
// 取 pArg2+3 写目标槽 this+1813，vt+1104 写行为字 20【推断：受令跟进】
// ·0x49C5F0 起 4 号 500ms 倒计时门
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3110(int *this, uint32_t *pArg2)  // 函数: 指令包响应（指令 6 → 行为字 20）
{
  int result; // eax
  int v4; // edx

  result = sub_4D90A0(pArg2);  // 调 校验指令包
  if ( *pArg2 == 6 )
  {
    sub_4D84F0(0, 0);  // 头顶气泡 CommandReceive.ani（同 0x4D82D0 结构）
    v4 = *this;
    *(this + 1813) = pArg2[3];  // this+7252 = pTarget7252
    (*(void (/*thiscall*/ **)(int *, int))(v4 + 1104))(this, 20);  // 调用虚函数（虚表槽 +1104）
    return sub_49C5F0(4, 0, 0, 500);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A3160 sub_5A3160 —— 命中处理器（vmt200 覆写，5 张虚表共用）
// ·0x4DA3B0 命中包分发前置照走返回；vt+308 可行动门成立且 10% 概率时
// 经 this+8600 槽函数指针以 this+1814 为目标发起反击【推断：受击概率反击 Functor】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3160(void (/*thiscall*/ ***this)(int, void *, uint32_t), int nArg2, int nArg3, int nArg4)  // 函数: 命中处理器（vmt200 覆写，5 张虚表共用）
{
  int v5; // edi

  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);  // 调 ★ 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
  if ( ((uint8_t (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[77])(this) != 0
    && rand() % 100 < 10 )  // 调 以 16 位种子状态递推并返回 15 位结果
  {
    (**(this + 2150))((int)(this + 2150), this, *(this + 1814));  // this+8600 = uAI8600
  }
  return v5;
}



// 技能播报：TAU_BREATH（牛头喷息）
// ------------------------------------------------------------
// 0x5A31C0 sub_5A31C0 —— 待机语音 · TAU_BREATH（20% 概率）
// ·0x4DA1D0 前置清理后读 vt+840 大状态；==0（待机）且 rand 20% 时
// 经 vt+212 播报待机喷息语音 TAU_BREATH
// ------------------------------------------------------------
int /*thiscall*/ sub_5A31C0(void *this)  // 函数: 待机语音 · TAU_BREATH（20% 概率）
{
  int result; // eax
  int nRand; // eax
  int v4; // et2

  sub_4DA1D0();
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( result == 0 )
  {
    nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
    v4 = nRand % 100;
    result = nRand / 100;
    if ( v4 < 20 )
      return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
               this,
               "TAU_BREATH",  // 资源/动画 TAG TAU_BREATH
               -1,
               0,
               0);
  }
  return result;
}



// 技能播报：TAU_GROUND_HIT（牛头砸地, 72L）
// ------------------------------------------------------------
// 0x5A3200 sub_5A3200 —— 砸地攻击帧钩子 · TAU_GROUND_HIT
// ·0x4E1780 基类帧驱动后限 vt+840==8（攻击态）；相位字节 this+8608 单次防重入
// 段 2：动作帧 +148==1 时 ·0x491C10 遍历帧数组并 ·0x424120(槽,5,…) 触发砸地判定
// 段 0：帧 +148==4 时按朝向 vt+152 施 ±110 位移（·0x4E4A50 强制位移 30022），
// ·0x424120(槽,2,500) 收段并播报 TAU_GROUND_HIT
// ------------------------------------------------------------
char /*usercall*/ sub_5A3200@<al>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：砸地攻击帧钩子 · TAU_GROUND_HIT
{
  int v4; // eax
  int v5; // eax
  int v6; // edx
  uint32_t *v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v14; // [esp-18h] [ebp-1Ch]
  int v15; // [esp-10h] [ebp-14h]

  sub_4E1780(pDwArg1);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  v4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( v4 == 8 )
  {
    if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      LOBYTE(v4) = *((uint8_t *)pDwArg1 + 8608);  // 调 取 16 位值低 8 位
      if ( (uint8_t)v4 != 1 )
      {
        v4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        if ( *(uint32_t *)(v4 + 148) == 1 )
        {
          v5 = pDwArg1[29];
          v6 = *pDwArg1;
          *((uint8_t *)pDwArg1 + 8608) = 1;
          v7 = *(uint32_t **)(v5 + 132);
          v8 = (*(int (/*thiscall*/ **)(int *))(v6 + 200))(pDwArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          v9 = sub_491C10(v8);  // 调 遍历帧数组（首+44/尾+48，步长 88）
          LOBYTE(v4) = sub_424120(v7, 5, v9);  // 调 屏幕震动启动
        }
      }
    }
    else
    {
      v4 = sub_41A5E0((unsigned int)(pDwArg1 + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( v4 == 0 )
      {
        LOBYTE(v4) = *((uint8_t *)pDwArg1 + 8608);  // 调 取 16 位值低 8 位
        if ( (uint8_t)v4 != 1 )
        {
          v4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          if ( *(uint32_t *)(v4 + 148) == 4 )
          {
            v10 = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 152))(pDwArg1, nArg3, nArg2) != 0 ? 110 : -110;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
            {
              v15 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              v14 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);  // 调用虚函数（虚表槽 +124）
              v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              sub_4E4A50(pDwArg1, 30022, 0, v10 + v11, v14, 0, v15, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
            }
            v12 = pDwArg1[29];
            *((uint8_t *)pDwArg1 + 8608) = 1;
            sub_424120(*(uint32_t **)(v12 + 132), 2, 500);  // 调 屏幕震动启动
            LOBYTE(v4) = (*(int (/*thiscall*/ **)(int *, const char *, int))(*pDwArg1 + 212))(pDwArg1, "TAU_GROUND_HIT", -1);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          }
        }
      }
    }
  }
  return v4;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A3350 sub_5A3350 —— 减速弱化侧（速度槽 858）
// nArg3==0 时：速度槽（vt+672(0)+858）读出 -0.3 经 ·0x41A590 写回并 vt+676 应用，this+1899 清 0
// nArg3==2 或 nArg2==0 时攻击系数面 this+1905+68 乘 0.76923（÷1.3）
// 与 ·0x5A33E0 互为强化/弱化对偶
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3350(uint32_t *this, int nArg2, int nArg3)  // 函数: 减速弱化侧（速度槽 858）
{
  int result; // eax
  bool v5; // zf
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 != 2 )
      return result;
    result = nArg2;
    v5 = nArg2 == 0;
  }
  else
  {
    v6 = *this;
    *(this + 1899) = 0;  // this+7596 = 段号横向偏置
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0) + 858;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v7)) - 0.30000001;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v7, v8, v9);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
    result = nArg2;
    v5 = nArg2 == 1;
  }
  if ( v5 )
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.76923078;  // this+7620 = 速度/属性参数对象
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A33E0 sub_5A33E0 —— 增益强化侧（速度槽 858，与 ·0x5A3350 互为对偶）
// nArg3==0：速度槽（vt+672(0)+858）读出 +0.3 经 ·0x41A590 写回、vt+676 应用，
// this+1899 写 30（强化持续帧/等级档【推断】）；系数面 this+1905+68 乘 1.3 的门是
// (nArg3==0 且 nArg2==1) 或 (nArg3==2 且 nArg2==0)；nArg3 其余值直接返回 nArg3-2
// ------------------------------------------------------------
int /*thiscall*/ sub_5A33E0(uint32_t *this, int nArg2, int nArg3)  // 函数: 增益强化侧（速度槽 858，与 ·0x5A3350 互为对偶）
{
  int result; // eax
  bool v5; // zf
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 != 2 )
      return result;
    result = nArg2;
    v5 = nArg2 == 0;
  }
  else
  {
    v6 = *this;
    *(this + 1899) = 30;  // this+7596 = 段号横向偏置
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0) + 858;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v7, v8, v9);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
    result = nArg2;
    v5 = nArg2 == 1;
  }
  if ( v5 )
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 1.3;  // this+7620 = 速度/属性参数对象
  return result;
}



// 登场曲：sub_406D60 写 "B_TAUBEAST_01"（牛头兽曲目槽）
// ------------------------------------------------------------
// 0x5A3470 sub_5A3470 —— 牛头兽行为字相位机（B_TAUBEAST_01）
// 行为字槽 this+1787 分发：态 0 出场（vt+1284），困难级 this+1943==3 时 ·0x406D60 写登场曲 B_TAUBEAST_01
// 态 4 目标槽 this+1813 为空 → vt+1104 写 13；态 13/14/15 有目标 → 写 4【推断：行为字语义】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3470(int *this)  // 函数: 牛头兽行为字相位机（B_TAUBEAST_01）
{
  int result; // eax

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148 = nBigState
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
      if ( *(this + 1943) == 3 )  // this+7772 = nCounterState
        result = sub_406D60("B_TAUBEAST_01");  // 调 std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result == 0 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
      break;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result != 0 )  // 若结果非 0（成功）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调用虚函数（虚表槽 +1104）
      break;
    default:
      return result;
  }
  return result;
}



// 牛头兽装载：R_TAU_TALK/DMG + TAU_DIE 语音 + Monster/Tau/{Hair-Beast,Horn-Beast}.equ（70L）
// ------------------------------------------------------------
// 0x5A3510 sub_5A3510 —— 牛头兽装载（Hair-Beast / Horn-Beast）
// 与 ·0x5A2F30 同构装载：阈值面 1698..1702、R_TAU_* / TAU_DIE 语音、两件 .equ、缩放 1.55
// 差异：new(0x64) 经 ·0x51A7D0 构造控制器对象写 this+2151 并经其 vt+56 绑定宿主【推断：僚机/特效控制器】
// 收尾 this+8608 相位清 0、分身参数面字节 this+7531 置 1
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3510(uint32_t *this)  // 函数: 牛头兽装载（Hair-Beast / Horn-Beast）
{
  char *pMem; // eax
  char *v3; // edi
  char *v4; // ebx
  int pObj; // eax
  char *pMem2; // eax
  int pObj3; // eax
  int v8; // eax
  void *pMem3; // eax
  int pObj2; // eax
  int result; // eax

  *(this + 1698) = 2;  // this+6792 = 炮车/子类参数面槽 1
  *(this + 1699) = 2;  // this+6796 = 炮车/子类参数面槽 2
  *(this + 1700) = 2;  // this+6800 = 炮车/子类参数面槽 3
  *(this + 1701) = 3;  // this+6804 = 炮车/子类参数面槽 4
  *(this + 1702) = 4;  // this+6808 = 炮车/子类参数面槽 5
  sub_4015C0("R_TAU_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("TAU_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v4 = sub_4BA9E0(pMem, "Monster/Tau/Hair-Beast.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v4 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v4);  // 调用虚函数（虚表槽 +784）
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v3 = sub_4BA9E0(pMem2, "Monster/Tau/Horn-Beast.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调用虚函数（虚表槽 +4）
  v8 = *this;
  *(this + 1830) = 30;
  *(this + 1839) = -30;
  *(this + 1831) = 300;
  (*(void (/*thiscall*/ **)(uint32_t *))(v8 + 688))(this);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
  sub_4EB2C0(1.55);  // 调 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  sub_4EB6A0(1.55);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(1.55);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  pMem3 = operator new(0x64u);  // operator new 分配 100 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    pObj2 = sub_51A7D0(pMem3);  // 调 构造后把时长写入虚 64 结果 +40
  else
    pObj2 = 0;
  *(this + 2151) = pObj2;  // this+8604 = bAI8604
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2) + 36) = 0;  // 调用虚函数（虚表槽 +64）【推断: 取观察者容器（懒创建 0x44 字节 sb_499960(thi…】
  result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2151)  // this+8604 = bAI8604
                                                                                          + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
             *(this + 2151),  // this+8604 = bAI8604
             this,
             this,
             0,
             0,
             0,
             -1);
  *((uint8_t *)this + 8608) = 0;  // this+8608 = uAI8608
  *((uint8_t *)this + 7531) = 1;  // this+7531 = 内嵌配置块 +11 字节
  return result;
}



// 状态机字符串证据："STATEMACHINE:TACKLESTART"（冲撞起始态, 35L；.ani/mob 状态机指令）
// ------------------------------------------------------------
// 0x5A36F0 sub_5A36F0 —— 冲撞起始态拦截 · TACKLESTART
// ·0x4E33D0 基类收尾；大状态 8 进入且攻击段号槽 this+7028==1 时：vt+1104 写行为字 19、
// 触发状态机指令 STATEMACHINE:TACKLESTART、vt+196 换帧、·0x4926A0 复位帧游标（this+30）、·0x49C5F0 起 500ms 段门
// 非态 8 侧分支在段 1 时以 vt+216 提前收招【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A36F0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 冲撞起始态拦截 · TACKLESTART
{
  int fld_e1639; // edi  | +0x199C → nMainState6556〔族字典〕（族字典）
  int result; // eax

  fld_e1639 = *(this + 1639);  // this+6556 = 主状态镜像
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( fld_e1639 != 8 )
    goto LABEL_5;
  if ( ArgList != 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )
      result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 216))(this, 0);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
LABEL_5:
    if ( ArgList != 8 )
      return result;
  }
  result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  if ( result == 1 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 19);  // 调用虚函数（虚表槽 +1104）
    off_77F3FC("STATEMACHINE:TACKLESTART");  // 调 off_77F3FC（引擎日志输出函数）
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));  // this+6216 = 资源/帧游标表
    sub_4926A0(*(this + 30));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
    return sub_49C5F0(10, 0, 0, 500);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A37A0 sub_5A37A0 —— 减速弱化侧（速度槽 830）
// nArg3==0 时：速度槽（vt+672(0)+830）-0.3 写回、vt+676 应用；相位 this+1895 清 0、字节 this+7556 清 0
// nArg3==2 或 nArg2==0 时系数面 this+1905+36 乘 0.76923（÷1.3）；与 ·0x5A3850 互为对偶
// ------------------------------------------------------------
int /*thiscall*/ sub_5A37A0(uint32_t *this, int nArg2, int nArg3)  // 函数: 减速弱化侧（速度槽 830）
{
  int v4; // eax
  unsigned int v5; // edi
  int v6; // edx
  int result; // eax
  int v8; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    if ( nArg3 == 2 )
      *(this + 1895) = 0;  // this+7580 = 攻击面门字节
  }
  else
  {
    v4 = *this;
    *((uint8_t *)this + 7556) = 0;  // this+7556 = 攻击面模式字节
    *(this + 1899) = 0;  // this+7596 = 段号横向偏置
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 672))(this, 0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.30000001;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v5, v6, v8);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.76923078;  // this+7620 = 速度/属性参数对象
  }
  result = nArg2;
  if ( nArg2 == 0 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.76923078;  // this+7620 = 速度/属性参数对象
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A3850 sub_5A3850 —— 牛头兽·冲撞强化侧（速度槽 830，与 ·0x5A37A0 互为对偶）
// nArg3==2：段号槽 this+1895 写 2；nArg3==0：·0x41A5E0 读速度槽（vt+672(0)+830）
// 加 0.3 写回、vt+676 应用，this+1899 写 30、this+7556 置 1（冲撞段判定标志），
// 系数面 this+1905+36 乘 1.3；nArg2==0 时再乘一次 1.3（两处独立判定）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3850(uint32_t *this, int nArg2, int nArg3)  // 函数: 牛头兽·冲撞强化侧（速度槽 830，与 ·0x5A37A0 互为对偶）
{
  int v4; // eax
  unsigned int v5; // edi
  int v6; // edx
  int result; // eax
  int v8; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    if ( nArg3 == 2 )
      *(this + 1895) = 2;  // this+7580 = 攻击面门字节
  }
  else
  {
    v4 = *this;
    *((uint8_t *)this + 7556) = 1;  // this+7556 = 攻击面模式字节
    *(this + 1899) = 30;  // this+7596 = 段号横向偏置
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 672))(this, 0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v5)) + 0.30000001;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v5, v6, v8);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 1.3;  // this+7620 = 速度/属性参数对象
  }
  result = nArg2;
  if ( nArg2 == 0 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 1.3;  // this+7620 = 速度/属性参数对象
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A3900 sub_5A3900 —— 冲撞段 1 帧锁定钩子
// vt+308 可行动且大状态 8（this+6556）、段槽 this+7028==1 齐备时：当前动作帧 this+30 的 +170 标记
// 成立且与 this+1554+4 一致则 vt+196 锁帧并 ·0x4926A0 复位游标；尾调 ·0x4E1780 基类帧驱动
// ------------------------------------------------------------
char /*thiscall*/ sub_5A3900(int *this)  // 函数: 冲撞段 1 帧锁定钩子
{
  int pAnimObj; // ecx  | +0x0078 → 动画对象指针（CNTauAssaulter；va=00499020）
  int fld_e1554; // eax  | +0x1848 → pTbl6216〔族字典〕（族字典）

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && *(this + 1639) == 8  // this+6556 = 主状态镜像
    && sub_41A5E0((unsigned int)(this + 1757)) == 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    pAnimObj = *(this + 30);  // this+120 = 动画对象指针
    if ( *(uint8_t *)(pAnimObj + 170) != 0 )
    {
      fld_e1554 = *(this + 1554);  // this+6216 = 资源/帧游标表
      if ( pAnimObj == *(uint32_t *)(fld_e1554 + 4) )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(fld_e1554 + 4));  // 调用虚函数（虚表槽 +196）
        sub_4926A0(*(this + 30));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      }
    }
  }
  return sub_4E1780(this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A3960 sub_5A3960 —— 冲撞位移跟踪（叠 ·0x5A36F0）
// 先走 ·0x5A36F0 起始拦截；大状态 8 且帧参数 +4==2 时按朝向 vt+152 施 ±70 横移（vt+136 位移写入）
// 位移受阻（返回 0）则 vt+560 setState 复位收招【推断：撞墙取消】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3960(int *this, int nArg2, float fArg3, int nArg4, int nArg5)  // 函数: 冲撞位移跟踪（叠 ·0x5A36F0）
{
  int result; // eax
  int v7; // edi
  int v8; // eax
  int v9; // ebx
  int v10; // edi
  int v11; // eax

  result = sub_5A36F0(this, nArg2, fArg3, nArg4, nArg5);  // 调 冲撞起始态拦截 · TACKLESTART
  if ( nArg2 == 8 && **(uint32_t **)(LODWORD(fArg3) + 4) == 2 )  // 调 取 64 位值低 32 位
  {
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 ? 70 : -70;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v9 = *this;
    v10 = v8 + v7;
    v11 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);  // 调用虚函数（虚表槽 +124）
    result = (*(int (/*thiscall*/ **)(int *, int, int))(v9 + 136))(this, v10, v11);  // 调用虚函数（虚表槽 +136）
    if ( (uint8_t)result == 0 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
  }
  return result;
}



// 登场/技能播报：ROCKMOUDE_01（岩石虫/岩鼠曲, 49L）
// ------------------------------------------------------------
// 0x5A39E0 sub_5A39E0 —— 岩鼠投技发射 · ROCKMOUDE_01 播报
// 叠 ·0x5A3900；vt+840==8 且段槽 this+7028==2、动作帧 +170 标记、vt+308 可行动齐备时
// 经 vt+580 发射 1018/1019（按朝向，参数 70/4），随后 vt+212 播报 ROCKMOUDE_01【推断：岩虫吼声】
// ------------------------------------------------------------
char /*thiscall*/ sub_5A39E0(int *this)  // 函数: 岩鼠投技发射 · ROCKMOUDE_01 播报
{
  int pThis_6DD; // eax
  int v3; // eax

  sub_5A3900(this);  // 调 冲撞段 1 帧锁定钩子
  pThis_6DD = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( pThis_6DD == 8 )
  {
    pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( pThis_6DD == 2 )
    {
      LOBYTE(pThis_6DD) = *(uint8_t *)(*(this + 30) + 170);  // this+120 = 动画对象指针
      if ( (uint8_t)pThis_6DD != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        {
          v3 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
            this,
            (v3 != 0) + 1018,
            0,
            0,
            0,
            70,
            0,
            0,
            4,
            0,
            0,
            0);
        }
        LOBYTE(pThis_6DD) = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                       this,
                       "ROCKMOUDE_01",  // 资源/动画 TAG ROCKMOUDE_01
                       -1,
                       0,
                       0);
      }
    }
  }
  return pThis_6DD;
}



// 冲刺 AI：TAU_RUSH_LOOP 播报（74L；sub_431230 参数打包）
// ------------------------------------------------------------
// 0x5A3A70 sub_5A3A70 —— 牛头兵指令包相位机 · 冲刺循环 TAU_RUSH_LOOP
// ·0x4D90A0 分发：6=受令（目标写 this+1813、vt+1104 行为字 20、·0x49C5F0 500ms 门、vt+768(12,3)、this+1881=10000 时限）
// 0xA=冲刺段：·0x498F60 取条件字节经 vt+896 设向、vt+876 速率双轴与 vt+888 伴随设置、
// ·0x49C5F0(11) 300-600ms 抖动、vt+196 换帧并播报 TAU_RUSH_LOOP
// 0xB=vt+1104 写行为字 15；0xC=this+6556 为 0 时 ·0x431230 打包经 vt+560 setState 进大状态 8（·0x5E5260 释放参数包）
// ------------------------------------------------------------
void /*thiscall*/ sub_5A3A70(uint32_t *this, int nArg2)  // 函数: 牛头兵指令包相位机 · 冲刺循环 TAU_RUSH_LOOP
{
  uint32_t *v2; // edi
  int v4; // edx
  int v5; // edi
  int v6; // eax
  int nRand; // eax
  void *pBuf[7]; // [esp+8h] [ebp-1Ch] BYREF

  v2 = (uint32_t *)nArg2;
  sub_4D90A0(nArg2);  // 调 校验指令包
  switch ( *v2 )  // 按 *v2 分派
  {
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      sub_4D84F0(0, 0);  // 头顶气泡 CommandReceive.ani（同 0x4D82D0 结构）
      v4 = *this;
      *(this + 1813) = v2[3];  // this+7252 = pTarget7252
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 1104))(this, 20);  // 调用虚函数（虚表槽 +1104）
      sub_49C5F0(4, 0, 0, 500);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 768))(this, 12, 3, 0);  // 调用虚函数（虚表槽 +768）【推断: ★ 状态施加入口（17 状态槽懒创建 + 转发）】
      *(this + 1881) = 10000;  // this+7524 = 内嵌配置块 +4
      break;
    case 0xA:
      if ( *(this + 30) == *(uint32_t *)*(this + 1554) )  // this+120 = 动画对象指针
      {
        v5 = *this;
        v6 = sub_498F60(this);  // 调 取条件字节
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v5 + 896))(this, v6, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          *(this + 2151),  // this+8604 = bAI8604
          *(this + 2151),  // this+8604 = bAI8604
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
        sub_49C5F0(11, 0, 0, nRand % 300 + 300);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // this+6216 = 资源/帧游标表
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          this,
          "TAU_RUSH_LOOP",  // 资源/动画 TAG TAU_RUSH_LOOP
          0,
          0,
          0);
      }
      break;
    case 0xB:
      if ( *(this + 30) == *(uint32_t *)(*(this + 1554) + 4) )  // this+120 = 动画对象指针
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);  // 调用虚函数（虚表槽 +1104）
      break;
    case 0xC:
      if ( *(this + 1639) == 0 )  // this+6556 = 主状态镜像
      {
        *(this + 1813) = v2[3];  // this+7252 = pTarget7252
        memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
        pBuf[6] = nullptr;
        nArg2 = 1;
        sub_431230((int)pBuf, &nArg2);  // 调 uint32 vector push_back
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      }
      break;
    default:
      return;
  }
}



// 牛头装载 2：R_TAU_* 语音 + Monster/Tau/{wrap02,Horn02}.equ（63L）
// ------------------------------------------------------------
// 0x5A3C80 sub_5A3C80 —— 牛头·透装型装载 2（wrap02 / Horn02）
// 与 ·0x5A2F30 同构装载（阈值面 / 语音 / 两件 .equ）；差异：vt+384 出场参数面双读经
// ·0x4049C0 区间插值写 this+2151【推断：出场透明度曲线】、vt+688 带参调用
// sub_4EB2C0(0.0) 与 sub_4EB6A0(0.95) 分部件缩放；this+7542 置 1
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3C80(uint32_t *this)  // 函数: 牛头·透装型装载 2（wrap02 / Horn02）
{
  char *pMem; // eax
  int pObj2; // eax
  char *pMem2; // eax
  char *v5; // ebx
  int pObj; // eax
  int fld_e1821; // edi
  uint32_t *v8; // eax
  uint64_t fld_e1820; // rax
  int result; // eax
  float v11; // [esp+18h] [ebp-38h]
  float v12; // [esp+1Ch] [ebp-34h]
  void *Block; // [esp+38h] [ebp-18h]
  int v14; // [esp+3Ch] [ebp-14h]
  char *v15; // [esp+40h] [ebp-10h]

  *(this + 1698) = 2;  // this+6792 = 炮车/子类参数面槽 1
  *(this + 1699) = 2;  // this+6796 = 炮车/子类参数面槽 2
  *(this + 1700) = 2;  // this+6800 = 炮车/子类参数面槽 3
  *(this + 1701) = 3;  // this+6804 = 炮车/子类参数面槽 4
  *(this + 1702) = 4;  // this+6808 = 炮车/子类参数面槽 5
  sub_4015C0("R_TAU_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("TAU_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v15 = sub_4BA9E0(pMem, "Monster/Tau/wrap02.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v15 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v15);  // 调用虚函数（虚表槽 +784）
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v5 = sub_4BA9E0(pMem2, "Monster/Tau/Horn02.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v5 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v5);  // 调用虚函数（虚表槽 +784）
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调用虚函数（虚表槽 +4）
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v8 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v12 = (float)v14;
  v11 = (float)(int)Block;
  fld_e1820 = (uint64_t)sub_4049C0(v11, v12, *v8 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e1820) = *this;  // 调 取 64 位值高 32 位
  *(this + 2151) = fld_e1820;  // this+8604 = bAI8604
  (*(void (/*thiscall*/ **)(uint32_t *, int))(HIDWORD(fld_e1820) + 688))(this, 1064514355);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
  sub_4EB2C0(0.0);  // 调 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  sub_4EB6A0(0.94999999);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  result = sub_4EB6A0(0.94999999);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  *((uint8_t *)this + 7542) = 1;
  return result;
}



// 子类扩展字段复位（this+8604..8612）
// ------------------------------------------------------------
// 0x5A3E50 sub_5A3E50 —— 子类相位字节复位（this+8604/8608/8612）
// 三槽 AI 相位/标志清零
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3E50(int this)  // 函数: 子类相位字节复位（this+8604/8608/8612）
{
  *(uint8_t *)(this + 8604) = 0;  // this+8604 子类 AI 状态槽/相位门
  *(uint32_t *)(this + 8608) = 0;  // this+8608 骑乘/骑手槽或动作号快照 B
  *(uint8_t *)(this + 8612) = 0;  // this+8612 锁定/相位字节 A 或开火相位字节
  return 0;
}



// AI 字段访问（this+8604）
// ------------------------------------------------------------
// 0x5A3E70 sub_5A3E70 —— 伤害修正钩子 · 格挡减伤 / 浮空增伤
// ·0x4DC390 类型过滤后：this+8604 格挡标志成立时按攻击标签 +12 / +124 分档减伤
// （×0.5 / ×0.35 / ×0.25，返回 2=格挡吸收【推断】）
// 未格挡且本体离地（vt+128 高度>0）伤害翻倍返回 0【推断：浮空易伤】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3E70(uint8_t *this, int *pDwArg2, int nArg3)  // 函数: 伤害修正钩子 · 格挡减伤 / 浮空增伤
{
  int result; // eax
  int v5; // ebx

  result = sub_4DC390(pDwArg2, nArg3);  // 调 伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
  v5 = result;
  if ( result != 3 )
  {
    if ( *(this + 8604) != 0 )  // this+8604 子类 AI 状态槽/相位门
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
    else if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this) <= 0 )  // 调用虚函数（虚表槽 +128）
    {
      return v5;
    }
    else
    {
      *pDwArg2 = (uint64_t)((double)*pDwArg2 + (double)*pDwArg2);
      return 0;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A40F0 sub_5A40F0 —— 待机索敌 · 概率写行为字 22
// ·0x4E1780 基类帧驱动；施放入场态 15 且帧标记齐备即 vt+560 复位
// 待机态 0 时对目标 this+1813 做 vt+40(17) 类型校验，目标处于攻击/受击态
// （vt+840∈8/7 或 273 型+12）且 vt+8 距离<100 时按 this+1909 权重 20%/50% 写行为字 22【推断：反击选择】
// ------------------------------------------------------------
int /*usercall*/ sub_5A40F0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 实现：待机索敌 · 概率写行为字 22
{
  int pObj; // edi
  int nRand; // edx
  int result; // eax

  sub_4E1780(pArg1);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 15  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) != 0  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    && *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      if ( result == 0 && pArg1[1787] != 22 )
      {
        result = pArg1[1813];
        if ( result != 0 )  // 若结果非 0（成功）
        {
          result = (*(int (/*cdecl*/ **)(int))(*(uint32_t *)result + 40))(17);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
          if ( (uint8_t)result != 0 )
          {
            pObj = pArg1[1813];
            if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 840))(pObj, nArg2) == 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
              || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 7  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
              || (uint8_t)(result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273)) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
              && (result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj)) == 12 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
            {
              result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, pObj, 0);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
              if ( result < 100 )
              {
                nRand = rand() % 100;  // 调 以 16 位种子状态递推并返回 15 位结果
                result = pArg1[1909] != 0 ? 20 : 50;
                if ( nRand < result )
                  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 22);  // 调用虚函数（虚表槽 +1104）
              }
            }
          }
        }
      }
    }
  }
  return result;
}



// 指挥 AI：TAU_COMMAND（RTTI cast, 67L）
// ------------------------------------------------------------
// 0x5A4170 sub_5A4170 —— 集群指挥 · 同伴牛头兵集结（TAU_COMMAND）
// 遍历同组容器（this+29 槽 vector）：vt+40(17) 怪物校验 + vt+376 阵营一致后
// RTTI 判型 CNTauAssaulter，距离 vt+156≤300 者发 ·0x49C620(12, this+1813) 并播报 TAU_COMMAND【推断：下令攻击】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A4170(uint32_t *this)  // 函数: 集群指挥 · 同伴牛头兵集结（TAU_COMMAND）
{
  unsigned int i; // esi
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // esi
  int v11; // ebx
  int v12; // eax
  unsigned int v13; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v4 = *(uint32_t *)(fld_e29 + 8);
    v13 = i;
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj = *(uint32_t *)(v9 + 4 * i);
      else
        pObj = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调用虚函数（虚表槽 +376）
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )  // 调用虚函数（虚表槽 +376）
      {
        v12 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                pObj,
                0,
                &IRDActiveObject `RTTI Type Descriptor',
                &CNTauAssaulter `RTTI Type Descriptor',
                0);
        if ( v12 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 156))(this, v12) <= 300 )  // 调用虚函数（虚表槽 +156）【推断: 与目标 x/y 距离绝对值】
        {
          sub_49C620(12, *(this + 1813), 0);  // 调 命令下发包装（组 id = this+4，值重复两遍）
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
            this,
            "TAU_COMMAND",  // 资源/动画 TAG TAU_COMMAND
            -1,
            0,
            0);
        }
      }
      i = v13;
    }
  }
  return result;
}



// RTTI cast 目标解算（54L）
// ------------------------------------------------------------
// 0x5A4270 sub_5A4270 —— 同构 ·0x5A4170（差异：RTTI 判型 CNTauArmy、指令 ·0x49C620(11,…)、无播报）
// vt+40(obj,17) 筛型 → vt+376 阵营号一致（同族）→ RTTI cast CNTauArmy 且
// vt+156 距离 <=300 者，交 ·0x49C620(11, this+1813, 0) 下发集結/掩护指令
// ------------------------------------------------------------
int /*thiscall*/ sub_5A4270(uint32_t *this)  // 函数: 同构 ·0x5A4170（差异：RTTI 判型 CNTauArmy、指令 ·0x49C620(11,…)、无播报）
{
  unsigned int i; // esi
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // esi
  int v11; // ebx
  int v12; // eax
  unsigned int v13; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v4 = *(uint32_t *)(fld_e29 + 8);
    v13 = i;
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj = *(uint32_t *)(v9 + 4 * i);
      else
        pObj = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调用虚函数（虚表槽 +376）
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )  // 调用虚函数（虚表槽 +376）
      {
        v12 = __RTDynamicCast(pObj, 0, &IRDActiveObject `RTTI Type Descriptor', &CNTauArmy `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
        if ( v12 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 156))(this, v12) <= 300 )  // 调用虚函数（虚表槽 +156）【推断: 与目标 x/y 距离绝对值】
          sub_49C620(11, *(this + 1813), 0);  // 调 命令下发包装（组 id = this+4，值重复两遍）
      }
      i = v13;
    }
  }
  return result;
}



// AI 相位辅助（72L）
// ------------------------------------------------------------
// 0x5A4360 sub_5A4360 —— 同伴状态扫描 · 转发指令 6
// 目标槽 this+1814 成立时遍历同组容器：vt+40(529) 类型校验、阵营一致且非自身
// 扫描同伴行为字向量（+83/+84）含 20 即发 ·0x49C620(6, this+1814)【推断：转发集火目标】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A4360(uint32_t *this)  // 函数: 同伴状态扫描 · 转发指令 6
{
  uint32_t *pThis; // ebx
  int result; // eax
  unsigned int i; // edi
  int v4; // ecx
  int v5; // edx
  int v6; // edx
  int pObj; // ecx
  int v8; // ecx
  int v9; // edx
  uint32_t *v10; // esi
  int v11; // eax
  uint32_t *v12; // ecx
  uint32_t *v13; // eax
  int v14; // [esp+4h] [ebp-8h]

  pThis = this;
  result = *(this + 1814);  // this+7256 = 光环对象槽
  if ( result != 0 )  // 若结果非 0（成功）
  {
    for ( i = 0; ; ++i )
    {
      v4 = pThis[29];
      v5 = *(uint32_t *)(v4 + 8);
      result = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)i >= result )
        break;
      v6 = *(uint32_t *)(v4 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(v4 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj = *(uint32_t *)(v6 + 4 * i);
      else
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
      {
        v8 = pThis[29];
        v9 = *(uint32_t *)(v8 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
          v10 = *(uint32_t **)(v9 + 4 * i);
        else
          v10 = nullptr;
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*v10 + 376))(v10);  // 调用虚函数（虚表槽 +376）
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis);  // 调用虚函数（虚表槽 +376）
        pThis = this;
        if ( v14 == v11 && v10 != this )  // 若 v14 == v11 与/或 v10 != this
        {
          v12 = (uint32_t *)v10[84];
          v13 = (uint32_t *)v10[83];
          if ( v13 != v12 )
          {
            do
            {
              if ( *v13 == 20 )
                break;
              ++v13;
            }
            while ( v13 != v12 );
            if ( v13 != v12 )
              sub_49C620(6, *(this + 1814), 0);  // 调 命令下发包装（组 id = this+4，值重复两遍）
          }
        }
      }
    }
  }
  return result;
}



// 防御光环 AI：AURA_DEFEND + TAU_ROAR 吼叫播报（109L）
// ------------------------------------------------------------
// 0x5A4460 sub_5A4460 —— 防御光环施放相位机 · AURA_DEFEND + TAU_ROAR
// 态 14 架招进出管理：离开 14 且 vt+288 标记时 vt+284 撤除；进 14 时 vt+196 换帧、
// vt+876 速率双轴清零、vt+284 写色 -14803201【推断：光环底色】
// 态 15 施放入场：this+8612 置 1，按 pArg5 成对目标表（0xFFFF 结尾）逐个 ·0x45EBE0 拾取、
// new(0x7C) ·0x4B3DF0 构造光环实体（参数 140.0 / 30000【推断：半径与时长】，vt+56 绑定、槽 38）并播报 AURA_DEFEND
// 收尾 ·0x4DB200 24 号文案（50% 两选一）+ TAU_ROAR 吼叫，尾调 ·0x4E33D0 基类收尾
// ------------------------------------------------------------
void /*userpurge*/ sub_5A4460(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, double fArg3@<st0>, int ArgList, int pArg5, int nArg6, int nArg7)  // 函数: 防御光环施放相位机 · AURA_DEFEND + TAU_ROAR
{
  int v8; // eax
  uint32_t *v9; // eax
  int v10; // ebx
  int v11; // edi
  uint32_t *pMem; // eax
  int *v13; // eax
  int v14; // edx
  int v15; // ecx
  int nRand; // eax
  int v17; // [esp-10h] [ebp-28h]
  int v18; // [esp-Ch] [ebp-24h]
  int nArg22; // [esp-4h] [ebp-1Ch]
  int v20; // [esp+4h] [ebp-14h]
  void *Block; // [esp+8h] [ebp-10h]
  int v22; // [esp+14h] [ebp-4h]

  if ( pArg1[1639] == 14 && ArgList != 14 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 288))(pArg1) == 1 )  // 调用虚函数（虚表槽 +288）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*pArg1 + 284))(pArg1, 0, 0, 1, 2);  // 调用虚函数（虚表槽 +284）【推断: 四字段批量写（+248..+260）】
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      fArg3 = sub_5A4360(pArg1);  // 调 同伴状态扫描 · 转发指令 6
      break;
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 8));  // 调用虚函数（虚表槽 +196）
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
        pArg1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 288))(pArg1) == 0  // 调用虚函数（虚表槽 +288）
        || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 292))(pArg1) != -14803201 )  // 调用虚函数（虚表槽 +292）
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, int))(*pArg1 + 284))(pArg1, 1, -14803201, 0, 1);  // 调用虚函数（虚表槽 +284）【推断: 四字段批量写（+248..+260）】
      }
      break;
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      v8 = pArg1[1554];
      *((uint8_t *)pArg1 + 8612) = 1;
      sub_4926A0(*(uint32_t *)(v8 + 12));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 12));  // 调用虚函数（虚表槽 +196）
      v9 = *(uint32_t **)(pArg5 + 4);  // pArg5+4〔宿主对象〕
      if ( *v9 != 0xFFFF )
      {
        nArg22 = nArg2;
        v10 = 0;
        do
        {
          v18 = v9[v10 + 1];
          v17 = v9[v10];
          (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1);  // 调用虚函数（虚表槽 +80）
          v11 = sub_45EBE0(v17, v18);  // 调 存 id 对 → 对象查找
          if ( v11 != 0 )
          {
            pMem = operator new(0x7Cu);  // operator new 分配 124 字节
            Block = pMem;
            v22 = 0;
            if ( pMem != nullptr )  // 若 pMem 有效（非空）
              v13 = sub_4B3DF0(pMem, 3, 1, 1124204544, 30000, 1);  // 调 CNChangeStatus 构造（六参）
            else
              v13 = nullptr;
            v14 = *v13;
            v22 = -1;
            (*(void (/*thiscall*/ **)(int *, int, uint32_t *, int, uint32_t, int, int))(v14 + 56))(v13, v11, pArg1, 1, 0, 38, -1);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
              pArg1,
              "AURA_DEFEND",  // 资源/动画 TAG AURA_DEFEND
              -1,
              0,
              0);
          }
          v9 = *(uint32_t **)(pArg5 + 4);  // pArg5+4〔宿主对象〕
          v15 = v9[v10 + 2];
          v10 += 2;
        }
        while ( v15 != 0xFFFF );
        nArg2 = nArg22;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
        pArg1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
      v20 = 0;
      Block = (void *)1;  // Block = 转换(1)
      nRand = rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
      sub_4DB200(pArg1, 24, *(&v20 + nRand));  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "TAU_ROAR", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      break;
    default:
      break;
  }
  sub_4E33D0((int)pArg1, nArg2, fArg3, ArgList, pArg5, *(float *)&nArg6, *(float *)&nArg7);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}


// AI 相位辅助（99L；sub_431230+sub_699000 时钟门, 8608/8612 相位）
// ------------------------------------------------------------
// 0x5A46C0 sub_5A46C0 —— 光环续施扫描（30s 冷却门）
// 光环激活标志 this+8612==1 豁免；否则距上次 this+8608 ≥30s（·0x699000 clock_now）时扫描同组
// vt+40(529) 同伴：阵营一致 + vt+1244 校验 + ·0x4DAB60(20) 标签在身者，收其 vt+48/vt+52
// 坐标经 ·0x431230 打包成对表，非空补 0xFFFF 后 vt+560 setState(15) 重走光环施放；末尾刷新 this+2152 时间戳
// ------------------------------------------------------------
void /*thiscall*/ sub_5A46C0(int this)  // 函数: 光环续施扫描（30s 冷却门）
{
  uint32_t *pThis; // ebx
  bool fld_21A4; // zf
  int v3; // esi
  unsigned int i; // edi
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int pObj; // ecx
  int v10; // ecx
  int v11; // edx
  int pObj2; // esi
  int v13; // eax
  int v14; // edx
  int v15; // eax
  void *Block2; // ecx
  uint8_t v17[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  int v19; // [esp+Ch] [ebp-1Ch]
  int v20; // [esp+10h] [ebp-18h]
  int v21; // [esp+14h] [ebp-14h] BYREF
  uint32_t *pThis2; // [esp+18h] [ebp-10h]
  int v23; // [esp+24h] [ebp-4h]

  pThis = (uint32_t *)this;
  fld_21A4 = *(uint8_t *)(this + 8612) == 1;  // this+8612 锁定/相位字节 A
  pThis2 = (uint32_t *)this;
  if ( !fld_21A4 && *(uint32_t *)(this + 8608) + 30000 <= (unsigned int)sub_699000(this + 36) )  // 【clock_now(clk)】
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pThis + 308))(pThis) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    {
      v3 = 0;
      Block = nullptr;
      v19 = 0;
      v20 = 0;
      v23 = 0;
      for ( i = 0; ; ++i )
      {
        v5 = pThis[29];
        v6 = *(uint32_t *)(v5 + 120);
        v7 = v6 != 0 ? (*(uint32_t *)(v5 + 124) - v6) >> 2 : 0;  // 向量元素数 = (end−begin)/4
        if ( (int)i >= v7 )
          break;
        v8 = *(uint32_t *)(v5 + 120);
        if ( v8 != 0 && i < (*(uint32_t *)(v5 + 124) - v8) >> 2 )  // 向量元素数 = (end−begin)/4
          pObj = *(uint32_t *)(v8 + 4 * i);
        else
          pObj = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
        {
          v10 = pThis[29];
          v11 = *(uint32_t *)(v10 + 120);
          if ( v11 != 0 && i < (*(uint32_t *)(v10 + 124) - v11) >> 2 )  // 向量元素数 = (end−begin)/4
            pObj2 = *(uint32_t *)(v11 + 4 * i);
          else
            pObj2 = 0;
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);  // 调用虚函数（虚表槽 +376）
          v14 = *pThis;
          v21 = v13;
          v15 = (*(int (/*thiscall*/ **)(uint32_t *))(v14 + 376))(pThis);  // 调用虚函数（虚表槽 +376）
          pThis = pThis2;
          if ( v21 == v15
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pThis2 + 1244))(pThis2, pObj2) != 0  // 调用虚函数（虚表槽 +1244）
            && (uint8_t)sub_4DAB60(20) != 0 )  // 调 标签/条件集合成员判定
          {
            v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);  // 调用虚函数（虚表槽 +48）
            sub_431230((int)v17, &v21);  // 调 uint32 vector push_back
            v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);  // 调用虚函数（虚表槽 +52）
            sub_431230((int)v17, &v21);  // 调 uint32 vector push_back
          }
        }
        v3 = v19;
      }
      Block2 = Block;
      if ( Block != nullptr && (v3 - (int)Block) >> 2 != 0 )
      {
        v21 = 0xFFFF;  // 常量 0xFFFF（= 0xFFFF）
        sub_431230((int)v17, &v21);  // 调 uint32 vector push_back
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*pThis + 560))(pThis, 15, v17, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        Block2 = Block;
      }
      v23 = -1;
      if ( Block2 != nullptr )  // 若 Block2 有效（非空）
        j__free(Block2);  // 调 堆释放
      Block = nullptr;
      v19 = 0;
      v20 = 0;
    }
    pThis[2152] = sub_699000((int)(pThis + 9));  // 【clock_now(clk)】
  }
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5A4890 sub_5A4890 —— 近身随机攻击发起（50% 概率）
// 50% 且目标 this+1813 通过 vt+40(17) 校验、vt+8 距离<100 时，以空参数
// ·0x431230 打包经 vt+560 setState 进入大状态 8（攻击）
// ------------------------------------------------------------
void /*thiscall*/ sub_5A4890(uint32_t *this)  // 函数: 近身随机攻击发起（50% 概率）
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  if ( rand() % 100 < 50  // 调 以 16 位种子状态递推并返回 15 位结果
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1813) + 40))(*(this + 1813), 17) != 0  // this+7252 = pTarget7252
    && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 8))(this, *(this + 1813), 0) < 100 )  // this+7252 = pTarget7252
  {
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 0;
    sub_431230((int)v2, v6);  // 调 uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
  }
}



// AI 相位辅助（84L）
// ------------------------------------------------------------
// 0x5A4940 sub_5A4940 —— 牛头兵王行为字相位机（集群调度）
// 行为字槽 this+1787 总调度：0=出场 vt+1284；4=各 1% 走 ·0x5A4270（指令 11）/ ·0x5A4170（指令 12），
// 其余按 this+1908/+1909 组合走 ·0x5A46C0 光环续施
// 态 13/14/15 有目标回落写 4；态 22（0x16）架招且高度占优时 20% 写 4 并 ·0x5A4890 近身攻击，否则写 5；无目标写 13
// ------------------------------------------------------------
void /*thiscall*/ sub_5A4940(uint32_t *this)  // 函数: 牛头兵王行为字相位机（集群调度）
{
  int fld_e1908; // eax  | +0x1DD0 → uWindow7632〔族字典〕（族字典）
  int pTarget7252; // eax  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int v4; // edi
  int fld_e18132; // edi

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( *(this + 1787) )  // this+7148 = nBigState
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == 0 )  // this+7252 = pTarget7252
        goto LABEL_20;
      if ( rand() % 100 >= 1 )  // 调 以 16 位种子状态递推并返回 15 位结果
      {
        if ( rand() % 100 >= 1 )  // 调 以 16 位种子状态递推并返回 15 位结果
        {
          fld_e1908 = *(this + 1908);  // this+7632〔uWindow7632(推断)〕
          if ( fld_e1908 == 2 && *(this + 1909) == 1 || fld_e1908 == 0 && (int)*(this + 1909) >= 1 )  // this+7636〔nPosWinY〕
            sub_5A46C0((int)this);  // 调 光环续施扫描（30s 冷却门）
        }
        else
        {
          sub_5A4170(this);  // 调 集群指挥 · 同伴牛头兵集结（TAU_COMMAND）
        }
      }
      else
      {
        sub_5A4270(this);  // 调 同构 ·0x5A4170（差异：RTTI 判型 CNTauArmy、指令 ·0x49C620(11,…)、无播报）
      }
      break;
    case 0xD:
      if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 调用虚函数（虚表槽 +1104）
      break;
    case 0xE:
    case 0xF:
      if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 调用虚函数（虚表槽 +1104）
      break;
    case 0x16:
      if ( *(this + 1813) != 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14 )  // this+7252 = pTarget7252
      {
        pTarget7252 = *(this + 1813);  // this+7252 = pTarget7252
        if ( pTarget7252 != 0 )
        {
          v4 = (*(int (**)(void))(*(uint32_t *)pTarget7252 + 120))();  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          if ( ((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) >= v4  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
             || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0)  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            && ((fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),  // this+7252 = pTarget7252
                 (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < fld_e18132)  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
             || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 1) )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          {
            if ( rand() % 100 < 20 )  // 调 以 16 位种子状态递推并返回 15 位结果
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 调用虚函数（虚表槽 +1104）
              sub_5A4890(this);  // 调 近身随机攻击发起（50% 概率）
            }
          }
          else
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);  // 调用虚函数（虚表槽 +1104）
          }
        }
      }
      else
      {
LABEL_20:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
      }
      break;
    default:
      return;
  }
}



// 【vmt200 命中处理器覆写】格挡反应 handler（虚表 0x6D8AD4 +512 槽, 135L）：
//   Character/Swordman/Effect/Animation/{GuardSpark,GuardCircle}.ani + 播报 SWD_GUARDED +
//   R_TAU_DMG —— 对照研究 20 §3 vt+644 格挡特效族（GuardSpark 家族）的牛头子类实现
// ------------------------------------------------------------
// 0x5A4B20 sub_5A4B20 —— 格挡反应命中处理器（vmt200 覆写 · GuardSpark 族）
// vt+840==14（架招）且 nArg4==0 时吃伤：字节 this+642 / 当前帧 +112 计数 ≤1 方入格挡分支，
// 经 vt+180 判定写 vt+1104 行为字 13，否则置 this+8604 格挡标志
// 格挡成立：vt+876 反冲（300 / -3000）+ vt+888 重置，·0x432E50 翻面后于命中点（pArg3 半和）
// 挂 GuardSpark.ani + GuardCircle.ani 双特效（·0x431860 装载 → ·0x45FE80 入场）并播报 SWD_GUARDED
// 尾段照走 ·0x4DA3B0 分发前置并清 this+8604；非架招态 10% 概率经 this+8600 槽函数指针反击（目标 this+1814）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A4B20(unsigned int *this, int nArg2, float *pArg3, int nArg4)  // 函数: 格挡反应命中处理器（vmt200 覆写 · GuardSpark 族）
{
  float *pArg32; // ebx
  unsigned int nFrameOverrideTime; // edi  | +0x0284 → 帧时刻覆盖值（4E5C10）【基类字段】（证据 va=004E5C10）（CNTauGuard；va=004E5C10）
  int pAnimObj; // edi  | +0x0078 → 动画对象指针（CNTauGuard；va=00499020）
  int v8; // eax
  unsigned int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int pObj; // edi
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // edi
  int pObj2; // edi
  int v20; // ebx
  int v21; // eax
  int v22; // edi
  unsigned int v24; // [esp+10h] [ebp-18h]
  int v25; // [esp+10h] [ebp-18h]
  int v26; // [esp+14h] [ebp-14h]
  int v27; // [esp+18h] [ebp-10h]

  pArg32 = pArg3;
  if ( (*(int (/*thiscall*/ **)(unsigned int *))(*this + 840))(this) != 14 || (uint8_t)nArg4 != 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    goto LABEL_27;
  if ( *((uint8_t *)this + 642) != 0 )  // this+642 = 帧时刻覆盖开关
  {
    nFrameOverrideTime = *(this + 161);  // this+644 = 帧时刻覆盖值
    goto LABEL_9;
  }
  pAnimObj = *(this + 30);  // this+120 = 动画对象指针
  if ( pAnimObj != 0 )
  {
    if ( *(uint32_t *)(pAnimObj + 148) == -1 )
      sub_4938F0(*(this + 30));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    nFrameOverrideTime = *(uint32_t *)(pAnimObj + 112);
LABEL_9:
    if ( nFrameOverrideTime > 1 )
      goto LABEL_27;
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0  // 调用虚函数（虚表槽 +348）
    || (v24 = *this,
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2),  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        (*(uint8_t (/*thiscall*/ **)(unsigned int *, int))(v24 + 180))(this, v8) != 0) )  // 调用虚函数（虚表槽 +180）【推断: 目标方位判定（vt+152 朝向）】
  {
    (*(void (/*thiscall*/ **)(unsigned int *, int))(*this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
  }
  else
  {
    *((uint8_t *)this + 8604) = 1;  // this+8604 = bAI8604
  }
  if ( *((uint8_t *)this + 8604) != 0 )  // this+8604 = bAI8604
  {
    (*(void (/*thiscall*/ **)(unsigned int *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
      this,
      0,
      300,
      300,
      0,
      -3000,
      1);
    (*(void (/*thiscall*/ **)(unsigned int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
      this,
      1,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(unsigned int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
    v9 = *this;
    v10 = (*(int (/*thiscall*/ **)(unsigned int *, int))(*this + 152))(this, 4);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v11 = sub_432E50(v10);  // 调 关系码对调映射
    (*(void (/*thiscall*/ **)(unsigned int *, int))(v9 + 896))(this, v11);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
    v25 = (uint64_t)(pArg3[3] * 0.5 + *pArg3);
    v26 = (*(int (/*fastcall*/ **)(unsigned int *, uint32_t))(*this + 124))(  // 调用虚函数（虚表槽 +124）
            this,
            (uint64_t)(pArg3[3] * 0.5 + *pArg3) >> 32);
    v27 = (uint64_t)(pArg3[5] * 0.5 + pArg3[2]);
    v12 = sub_42FCB0(228);  // 调 CRT 一次性初始化
    v13 = 0;
    if ( v12 != 0 )
      v13 = sub_431860(v12, "Character/Swordman/Effect/Animation/GuardSpark.ani", 1);  // 调 动画件构造（资源 id 版）
    if ( sub_44B6C0(284) != 0 )  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
      pObj = sub_44E1F0(v13, 1);  // 调 CNRDPooledObject 构造（虚表覆盖壳）
    else
      pObj = 0;
    sub_45FE80(*(this + 29), pObj, 2, 0, pObj, (int)this, 0);  // 调 对象注册
    v15 = *(uint32_t *)pObj;
    v16 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(int, int))(v15 + 148))(pObj, v16);  // 调用虚函数（虚表槽 +148）【推断: 同 vmt90 但不检查（直接写）】
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 112))(pObj, v25, v26, v27);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    v17 = sub_42FCB0(228);  // 调 CRT 一次性初始化
    if ( v17 != 0 )
      v18 = sub_431860(v17, "Character/Swordman/Effect/Animation/GuardCircle.ani", 1);  // 调 动画件构造（资源 id 版）
    else
      v18 = 0;
    if ( sub_44B6C0(284) != 0 )  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
      pObj2 = sub_44E1F0(v18, 1);  // 调 CNRDPooledObject 构造（虚表覆盖壳）
    else
      pObj2 = 0;
    sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);  // 调 对象注册
    v20 = *(uint32_t *)pObj2;
    v21 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(int, int))(v20 + 148))(pObj2, v21);  // 调用虚函数（虚表槽 +148）【推断: 同 vmt90 但不检查（直接写）】
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, v25, v26, v27);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    (*(void (/*thiscall*/ **)(unsigned int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      this,
      "SWD_GUARDED",  // 资源/动画 TAG SWD_GUARDED
      -1,
      0,
      0);
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pArg32 = pArg3;
  }
LABEL_27:
  v22 = sub_4DA3B0(nArg2, pArg32, nArg4);  // 调 ★ 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
  *((uint8_t *)this + 8604) = 0;  // this+8604 = bAI8604
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
  if ( (*(int (/*thiscall*/ **)(unsigned int *))(*this + 840))(this) != 14  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && rand() % 100 < 10 )  // 调 以 16 位种子状态递推并返回 15 位结果
  {
    (*(void (/*thiscall*/ **)(unsigned int *, unsigned int *, uint32_t))*(this + 2150))(this + 2150, this, *(this + 1814));  // this+8600 = uAI8600
  }
  return v22;
}


// 牛头装载 3：R_TAU_TALK/DMG + TAU_DIE 语音 + Monster/Tau/{wrap01,armlet01,tattoo01,
//   Hair02,Horn01,Weapon01}.equ 六件（97L）
// ------------------------------------------------------------
// 0x5A4E70 sub_5A4E70 —— 牛头精英装载 3（六件 .equ）
// 与 ·0x5A2F30 同构装载；差异：wrap01/armlet01/tattoo01/Hair02/Horn01/Weapon01 六件全挂、七次 0.8 缩放
// this+2152 写 clock_now+15000（15s 延时门【推断】）；this+1894=2、this+7542 置 1
// ------------------------------------------------------------
int /*thiscall*/ sub_5A4E70(uint32_t *this)  // 函数: 牛头精英装载 3（六件 .equ）
{
  char *pMem; // eax
  char *v3; // edi
  int pObj; // eax
  char *pMem2; // eax
  int pObj6; // eax
  char *pMem3; // eax
  int pObj5; // eax
  char *pMem4; // eax
  int pObj3; // eax
  char *pMem5; // eax
  char *v12; // ebx
  int pObj2; // eax
  char *pMem6; // eax
  int pObj4; // eax
  int result; // eax
  char *Block; // [esp+10h] [ebp-1Ch]
  char *v18; // [esp+14h] [ebp-18h]
  char *v19; // [esp+18h] [ebp-14h]
  char *v20; // [esp+1Ch] [ebp-10h]

  *(this + 1698) = 2;  // this+6792 = 炮车/子类参数面槽 1
  *(this + 1699) = 2;  // this+6796 = 炮车/子类参数面槽 2
  *(this + 1700) = 2;  // this+6800 = 炮车/子类参数面槽 3
  *(this + 1701) = 3;  // this+6804 = 炮车/子类参数面槽 4
  *(this + 1702) = 4;  // this+6808 = 炮车/子类参数面槽 5
  sub_4015C0("R_TAU_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("TAU_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v20 = sub_4BA9E0(pMem, "Monster/Tau/wrap01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v20 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v20);  // 调用虚函数（虚表槽 +784）
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v19 = sub_4BA9E0(pMem2, "Monster/Tau/armlet01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v19 = nullptr;
  pObj6 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v19);  // 调用虚函数（虚表槽 +784）
  if ( pObj6 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 4))(pObj6, 1);  // 调用虚函数（虚表槽 +4）
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v18 = sub_4BA9E0(pMem3, "Monster/Tau/tattoo01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v18 = nullptr;
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);  // 调用虚函数（虚表槽 +784）
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);  // 调用虚函数（虚表槽 +4）
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    Block = sub_4BA9E0(pMem4, "Monster/Tau/Hair02.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    Block = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, Block);  // 调用虚函数（虚表槽 +784）
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调用虚函数（虚表槽 +4）
  pMem5 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v12 = sub_4BA9E0(pMem5, "Monster/Tau/Horn01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v12 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);  // 调用虚函数（虚表槽 +784）
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调用虚函数（虚表槽 +4）
  pMem6 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
    v3 = sub_4BA9E0(pMem6, "Monster/Tau/Weapon01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调用虚函数（虚表槽 +4）
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
  sub_4EB2C0(0.80000001);  // 调 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  sub_4EB6A0(0.80000001);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(0.80000001);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(0.80000001);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(0.80000001);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(0.80000001);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(0.80000001);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  result = sub_699000((int)(this + 9)) + 15000;  // 【clock_now(clk)】
  *(this + 2152) = result;  // this+8608 = uAI8608
  *(this + 1894) = 2;  // this+7576 = 相位槽
  *((uint8_t *)this + 7542) = 1;
  return result;
}



// ============================================================
// 【分区 6】牛头·沙乌塔（Tangas）（0x5A5180-0x5A5BB0）
// 证据：TAU_EQUAKE_CAST/TAU_AXE_SWING、TangasAnimation/EF_EarthQuake{,Strong}.ani、
//       TangasAxeAfterImage.ani 残影、B_SHAUTA_01 登场曲、tangasHair01/tangasAcc01

// 技能播报：TAU_EQUAKE_CAST（地震施法）+ TAU_AXE_SWING（巨斧横扫）（this+8604/8605 相位）
// ------------------------------------------------------------
// 0x5A5180 sub_5A5180 —— 沙乌塔攻击段播报 · TAU_AXE_SWING / TAU_EQUAKE_CAST
// ·0x4E33D0 收尾后限大状态 8；按攻击段号槽 this+7028 分支：0=起手播报 TAU_AXE_SWING
// 1=vt+1104 写 19、vt+196 换帧、·0x4926A0 复位游标、·0x49C5F0 250ms 段门
// 2/3=清 this+8604/8605 相位并播报 TAU_EQUAKE_CAST（地震施法）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5180(void *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 沙乌塔攻击段播报 · TAU_AXE_SWING / TAU_EQUAKE_CAST
{
  int result; // eax
  uint32_t *v7; // edx

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 8 )
  {
    if ( sub_41A5E0((unsigned int)this + 7028) != 0 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( sub_41A5E0((unsigned int)this + 7028) == 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      {
        (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1104))(this, 19);  // 调用虚函数（虚表槽 +1104）
        (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, **((uint32_t **)this + 1554));  // 调用虚函数（虚表槽 +196）
        sub_4926A0(*((uint32_t *)this + 30));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
        return sub_49C5F0(10, 0, 0, 250);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
      }
      else if ( sub_41A5E0((unsigned int)this + 7028) == 2 || (result = sub_41A5E0((unsigned int)this + 7028)) == 3 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      {
        v7 = *(uint32_t **)this;
        *((uint8_t *)this + 8605) = 0;  // this+8605 = 子类 AI 标志
        *((uint8_t *)this + 8604) = 0;  // this+8604 = bAI8604
        return ((int (/*thiscall*/ *)(void *, const char *, int, uint32_t, uint32_t))v7[53])(
                 this,
                 "TAU_EQUAKE_CAST",  // 资源/动画 TAG TAU_EQUAKE_CAST
                 -1,
                 0,
                 0);
      }
    }
    else
    {
      return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
               this,
               "TAU_AXE_SWING",  // 资源/动画 TAG TAU_AXE_SWING
               -1,
               0,
               0);
    }
  }
  return result;
}



// 冲刺 AI：TAU_RUSH_LOOP（105L）
// ------------------------------------------------------------
// 0x5A5260 sub_5A5260 —— 同构 ·0x5A3A70 指令包相位机（差异：vt+768(12,8)、冲刺 vt+876 速率 600、0xB 加 vt+216 收招）
// 0xC/0xD 段经 vt+580 发射 30053 / 30054【推断：冲撞判定弹】
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5A5260(uint32_t *this, uint32_t *pArg2)  // 函数: 同构 ·0x5A3A70 指令包相位机（差异：vt+768(12,8)、冲刺 vt+876 速率 600、0xB 加 vt+…
{
  uint32_t *result; // eax
  int v4; // edx
  int v5; // edi
  int v6; // eax
  int nRand; // eax
  int fld_e1554; // eax
  int v9; // edx

  sub_4D90A0(pArg2);  // 调 校验指令包
  result = (uint32_t *)(*pArg2 - 6);
  switch ( *pArg2 )  // 按 *pArg2 分派
  {
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      sub_4D84F0(0, 0);  // 头顶气泡 CommandReceive.ani（同 0x4D82D0 结构）
      v4 = *this;
      *(this + 1813) = pArg2[3];  // this+7252 = pTarget7252
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 1104))(this, 20);  // 调用虚函数（虚表槽 +1104）
      sub_49C5F0(4, 0, 0, 500);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 768))(this, 12, 8, 0);  // 调用虚函数（虚表槽 +768）【推断: ★ 状态施加入口（17 状态槽懒创建 + 转发）】
      *(this + 1881) = 10000;  // this+7524 = 内嵌配置块 +4
      break;
    case 0xA:
      result = (uint32_t *)*(this + 1554);  // this+6216 = 资源/帧游标表
      if ( *(this + 30) == *result )  // this+120 = 动画对象指针
      {
        v5 = *this;
        v6 = sub_498F60(this);  // 调 取条件字节
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v5 + 896))(this, v6, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          600,
          600,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
        sub_49C5F0(11, 0, 0, nRand % 300 + 300);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // this+6216 = 资源/帧游标表
        result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                             this,
                             "TAU_RUSH_LOOP",  // 资源/动画 TAG TAU_RUSH_LOOP
                             0,
                             0,
                             0);
      }
      break;
    case 0xB:
      fld_e1554 = *(this + 1554);  // this+6216 = 资源/帧游标表
      v9 = *(uint32_t *)(fld_e1554 + 4);
      result = (uint32_t *)(fld_e1554 + 4);
      if ( *(this + 30) == v9 )  // this+120 = 动画对象指针
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);  // 调用虚函数（虚表槽 +1104）
        result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
      }
      break;
    case 0xC:
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)result != 0 )
        result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
                             this,
                             30053,
                             1,
                             0,
                             0,
                             180,
                             0,
                             0,
                             4,
                             0,
                             0,
                             0);
      break;
    case 0xD:
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)result != 0 )
        result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
                             this,
                             30054,
                             2,
                             0,
                             0,
                             180,
                             0,
                             0,
                             4,
                             0,
                             0,
                             0);
      break;
    default:
      return result;
  }
  return result;
}



// 登场曲：sub_406D60 写 "B_SHAUTA_01"（牛头曲, 52L）
// ------------------------------------------------------------
// 0x5A5450 sub_5A5450 —— 同构 ·0x5A3470 行为字相位机（差异：登场曲 B_SHAUTA_01；
// 态 4 有目标 30% 写 5 / 无目标写 13；态 14/15 写 5）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5450(int *this)  // 函数: 同构 ·0x5A3470 行为字相位机（差异：登场曲 B_SHAUTA_01；
{
  int result; // eax
  int nRand; // eax
  int v4; // et2

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148 = nBigState
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
      if ( *(this + 1943) == 3 )  // this+7772 = nCounterState
        result = sub_406D60("B_SHAUTA_01");  // 调 std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
      {
        nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
        v4 = nRand % 100;
        result = nRand / 100;
        if ( v4 < 30 )
          goto LABEL_5;
      }
      else
      {
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
      }
      break;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result != 0 )  // 若结果非 0（成功）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调用虚函数（虚表槽 +1104）
      break;
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_5:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);  // 调用虚函数（虚表槽 +1104）
      break;
    default:
      return result;
  }
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5A5530 sub_5A5530 —— 困难级跳劈发起（50% · 近身检测门）
// 困难级 this+1943==3 且 50% 掷点：·0x4E7F30(150,80) 近身检测取得目标后按双方 vt+120
// 高度比较写 vt+144 朝向布尔，再以参数 1 ·0x431230 打包经 vt+560 setState 进大状态 8【推断：跳劈】
// ------------------------------------------------------------
void /*thiscall*/ sub_5A5530(uint32_t *this)  // 函数: 困难级跳劈发起（50% · 近身检测门）
{
  int pObj; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v7[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && *(this + 1943) == 3  // this+7772 = nCounterState
    && rand() % 100 < 50 )  // 调 以 16 位种子状态递推并返回 15 位结果
  {
    pObj = sub_4E7F30(this, 150, 80, 0);  // 调 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
    if ( pObj != 0 )
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      (*(void (/*thiscall*/ **)(uint32_t *, bool))(v3 + 144))(this, v5 < v4);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
      memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
      v7[3] = 0;
      v7[0] = 1;
      sub_431230((int)pBuf, v7);  // 调 uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
    }
  }
}



// 沙乌塔地震技能：TangasAnimation/EF_EarthQuake.ani + EF_EarthQuakeStrong.ani +
//   Monster/Tau/TangasAnimation/TangasAxeAfterImage.ani 残影（124L；
//   this+6556==8 大状态门 + vt+308 本地玩家门, 研究 20 §1.2）
// ------------------------------------------------------------
// 0x5A5610 sub_5A5610 —— 沙乌塔地震帧钩子（this+6556==8 大状态门）
// vt+308 可行动且 this+6556==8 方进入；段 1 仅帧锁定（vt+196 + ·0x4926A0）
// 段 2/3：帧标 +148==2 且 this+8605 未置时按朝向 ±55 落点挂 EF_EarthQuake{,Strong}.ani 裂痕
// （·0x431920 装载 → ·0x45FE80 挂场景，+8605 防重）
// 帧标 ≥4 且 this+8604 未置时 ±196 落点挂 TangasAxeAfterImage.ani 残影（·0x431860 装载、·0x432E50 翻面），
// 段 2/3 分别 ·0x49C5F0(12/13, x, 0, 100) 起判定段；其余走 ·0x4E1780 基类帧驱动
// ------------------------------------------------------------
char /*usercall*/ sub_5A5610@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：沙乌塔地震帧钩子（this+6556==8 大状态门）
{
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int *v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int *v17; // edi
  int v18; // ebx
  int v19; // eax
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int v25; // [esp+8h] [ebp-10h]
  int v26; // [esp+8h] [ebp-10h]

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) == 0 || *(uint32_t *)(pArg1 + 6556) != 8 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    return sub_4E1780((uint32_t *)pArg1);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( sub_41A5E0(pArg1 + 7028) == 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v4 = *(uint32_t *)(pArg1 + 120);  // pArg1+120〔pAnimObj〕
    if ( *(uint8_t *)(v4 + 170) != 0 )
    {
      v5 = *(uint32_t *)(pArg1 + 6216);  // pArg1+6216〔pTbl6216(推断)〕
      if ( v4 == *(uint32_t *)(v5 + 4) )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(v5 + 4));  // 调用虚函数（虚表槽 +196）
        sub_4926A0(*(uint32_t *)(pArg1 + 120));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      }
    }
    return sub_4E1780((uint32_t *)pArg1);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  }
  if ( sub_41A5E0(pArg1 + 7028) != 2 && sub_41A5E0(pArg1 + 7028) != 3 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    return sub_4E1780((uint32_t *)pArg1);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) == 2 && *(uint8_t *)(pArg1 + 8605) == 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  {
    if ( (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 152))(pArg1, nArg2, nArg3) != 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 55;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    else
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 55;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v25 = v6;
    if ( sub_41A5E0(pArg1 + 7028) == 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
      {
        if ( *(uint32_t *)(pArg1 + 384) < 0x10u )  // pArg1+384〔nAnimNameCap(推断)〕
          v7 = sub_431920(pArg1 + 108, (char)"TangasAnimation/EF_EarthQuake.ani", 1);  // 调 动画件构造（文件名版）
        else
          v7 = sub_431920(*(uint32_t *)(pArg1 + 364), (char)"TangasAnimation/EF_EarthQuake.ani", 1);  // 调 动画件构造（文件名版）
        goto LABEL_24;
      }
    }
    else if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
    {
      if ( *(uint32_t *)(pArg1 + 384) < 0x10u )  // pArg1+384〔nAnimNameCap(推断)〕
        v7 = sub_431920(pArg1 + 108, (char)"TangasAnimation/EF_EarthQuakeStrong.ani", 1);  // 调 动画件构造（文件名版）
      else
        v7 = sub_431920(*(uint32_t *)(pArg1 + 364), (char)"TangasAnimation/EF_EarthQuakeStrong.ani", 1);  // 调 动画件构造（文件名版）
LABEL_24:
      v8 = v7;
      if ( sub_44B6C0(284) != 0 )  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
        v9 = (int *)sub_44E1F0(v8, 1);  // 调 CNRDPooledObject 构造（虚表覆盖壳）
      else
        v9 = nullptr;
      sub_45FE80(*(uint32_t *)(pArg1 + 116), (int)v9, 2, 0, (int)v9, pArg1, 0);  // 调 对象注册
      v10 = *v9;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 调用虚函数（虚表槽 +128）
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v11 + 195);  // 调用虚函数（虚表槽 +124）
      (*(void (/*thiscall*/ **)(int *, int, int))(v10 + 112))(v9, v25, v12);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      v13 = *v9;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      (*(void (/*thiscall*/ **)(int *, int))(v13 + 148))(v9, v14);  // 调用虚函数（虚表槽 +148）【推断: 同 vmt90 但不检查（直接写）】
      *(uint8_t *)(pArg1 + 8605) = 1;  // pArg1+8605〔bAI8605(推断)〕
      return sub_4E1780((uint32_t *)pArg1);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
    }
    v7 = 0;
    goto LABEL_24;
  }
  if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 4 && *(uint8_t *)(pArg1 + 8604) == 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  {
    if ( (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 152))(pArg1, nArg2, nArg3) != 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 196;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    else
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 196;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v26 = v15;
    if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
      v16 = sub_431860((char)"Monster/Tau/TangasAnimation/TangasAxeAfterImage.ani", 1);  // 调 动画件构造（资源 id 版）
    else
      v16 = 0;
    if ( sub_44B6C0(284) != 0 )  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
      v17 = (int *)sub_44E1F0(v16, 1);  // 调 CNRDPooledObject 构造（虚表覆盖壳）
    else
      v17 = nullptr;
    sub_45FE80(*(uint32_t *)(pArg1 + 116), (int)v17, 2, 0, (int)v17, pArg1, 0);  // 调 对象注册
    v18 = *v17;
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 调用虚函数（虚表槽 +128）
    v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v19 + 21);  // 调用虚函数（虚表槽 +124）
    (*(void (/*thiscall*/ **)(int *, int, int))(v18 + 112))(v17, v26, v20);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    v21 = *v17;
    v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v23 = sub_432E50(v22);  // 调 关系码对调映射
    (*(void (/*thiscall*/ **)(int *, int))(v21 + 148))(v17, v23);  // 调用虚函数（虚表槽 +148）【推断: 同 vmt90 但不检查（直接写）】
    *(uint8_t *)(pArg1 + 8604) = 1;  // pArg1+8604〔bAI8604(推断)〕
    if ( sub_41A5E0(pArg1 + 7028) == 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      sub_49C5F0(12, v26, 0, 100);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
    else
      sub_49C5F0(13, v26, 0, 100);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
  }
  return sub_4E1780((uint32_t *)pArg1);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}


// 沙乌塔装载：R_TAU_* 语音 + Monster/Tau/{wrap01,tattoo01,tangasHair01,tangasAcc01,weapon03}.equ（78L）
// ------------------------------------------------------------
// 0x5A5990 sub_5A5990 —— 沙乌塔装载（五件 .equ）
// 与 ·0x5A2F30 同构装载（阈值面 + R_TAU_* / TAU_DIE 语音）；五件外观
// wrap01/tattoo01/tangasHair01/tangasAcc01/weapon03
// 尾段 vt+672(3) 读数 >14 时 vt+612(1,1)【推断：部件显隐/层级切换】
// ------------------------------------------------------------
int */*usercall*/ sub_5A5990@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：沙乌塔装载（五件 .equ）
{
  char *pMem; // eax
  char *v4; // eax
  int pObj2; // eax
  char *pMem2; // eax
  char *v7; // eax
  int pObj4; // eax
  char *pMem3; // eax
  char *v10; // eax
  int pObj3; // eax
  char *pMem4; // eax
  char *v13; // eax
  int pObj5; // eax
  char *pMem5; // eax
  char *v16; // eax
  int pObj; // eax
  int *result; // eax

  pArg1[1698] = 2;
  pArg1[1699] = 2;
  pArg1[1700] = 2;
  pArg1[1701] = 3;
  pArg1[1702] = 4;
  sub_4015C0("R_TAU_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("TAU_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v4 = sub_4BA9E0(pMem, "Monster/Tau/wrap01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v4 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*pArg1 + 784))(pArg1, v4, nArg2);  // 调用虚函数（虚表槽 +784）
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v7 = sub_4BA9E0(pMem2, "Monster/Tau/tattoo01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v7 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v7);  // 调用虚函数（虚表槽 +784）
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调用虚函数（虚表槽 +4）
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v10 = sub_4BA9E0(pMem3, "Monster/Tau/tangasHair01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v10 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v10);  // 调用虚函数（虚表槽 +784）
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调用虚函数（虚表槽 +4）
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v13 = sub_4BA9E0(pMem4, "Monster/Tau/tangasAcc01.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v13 = nullptr;
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v13);  // 调用虚函数（虚表槽 +784）
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);  // 调用虚函数（虚表槽 +4）
  pMem5 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v16 = sub_4BA9E0(pMem5, "Monster/Tau/weapon03.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v16 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v16);  // 调用虚函数（虚表槽 +784）
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调用虚函数（虚表槽 +4）
  result = (int *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 672))(pArg1, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  if ( *result > 14 )
    return (int *)(*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 612))(pArg1, 1, 1);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
  return result;
}



// ============================================================
// 【分区 7】石魔像 Golem（0x5A5BB0-0x5A73E0）
// 证据：Particle/StoneLaser.ptl + STONE_LASER_FIRE/READY、Particle/StoneBlade.ptl、
//       SWING_LONG、GOLEM_02、C_BERSERK 狂暴(+6556)、RAIZO_01、GOLEM_DOWN/FIND/DMG/DIE、
//       R_GOLEM_AMB、B_FLATANY_01、STGolemFireSmoke.ani

// 子类扩展字段复位（this+8600..8672, 20L）
// ------------------------------------------------------------
// 0x5A5BB0 sub_5A5BB0 —— 石魔像子类字段复位（this+8600/8604/8644..8672）
// 石魔像 AI 状态区十槽清零
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5BB0(int this)  // 函数: 石魔像子类字段复位（this+8600/8604/8644..8672）
{
  *(uint32_t *)(this + 8600) = 0;  // this+8600 子类 AI 状态区首槽
  *(uint8_t *)(this + 8604) = 0;  // this+8604 子类 AI 状态字节/狂暴段门
  *(uint32_t *)(this + 8644) = 0;  // this+8644 子类 AI 相位槽
  *(uint32_t *)(this + 8648) = 0;  // this+8648 子类 AI 相位槽
  *(uint32_t *)(this + 8652) = 0;  // this+8652 子类 AI 相位槽
  *(uint32_t *)(this + 8656) = 0;  // this+8656 子类 AI 相位槽
  *(uint32_t *)(this + 8660) = 0;  // this+8660 子类 AI 相位槽
  *(uint32_t *)(this + 8664) = 0;  // this+8664 子类 AI 相位槽
  *(uint32_t *)(this + 8668) = 0;  // this+8668 子类 AI 相位槽
  *(uint32_t *)(this + 8672) = 0;  // this+8672 子类 AI 相位槽
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A5BF0 sub_5A5BF0 —— 槽对象释放（this+2166..2168）
// 三枚对象槽逐个调其 vt+0(·,1) 释放后清空【推断：特效/绑定句柄】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5BF0(uint32_t *this)  // 函数: 槽对象释放（this+2166..2168）
{
  uint32_t *pThis_876; // esi
  int i; // edi
  int result; // eax
  int (/*thiscall*/ ***fld_e2168)(uint32_t, int); // ecx

  pThis_876 = this + 2166;
  for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
  {
    if ( *pThis_876 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_876)(*pThis_876, 1);
    *pThis_876++ = 0;
  }
  fld_e2168 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2168);  // this+8672 = 子类 AI 槽
  if ( fld_e2168 != nullptr )  // 若 fld_e2168 有效（非空）
    result = (**fld_e2168)(fld_e2168, 1);  // 调 fld_e2168 的虚函数（vt+0）
  *(this + 2168) = 0;  // this+8672 = 子类 AI 槽
  return result;
}



// 行走 AI：GOLEM_WALK 播报（this+200 主状态门 + 8640 相位）
// ------------------------------------------------------------
// 0x5A5C40 sub_5A5C40 —— 行走播报 · GOLEM_WALK（单次门）
// 主状态与 this[1541] 匹配时监控动作帧 +148：进入帧 3 且 this+8640 为 0 则播报 GOLEM_WALK 并置位，
// 离开帧 3 复位（保证单次播报）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5C40(uint8_t *this)  // 函数: 行走播报 · GOLEM_WALK（单次门）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    if ( result == *((uint32_t *)this + 1541) )  // this+6164 = 帧游标对象槽
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148) != 3 || *(this + 8640) != 0 )  // this+8640 = uCastSlot8640
      {
        result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        if ( *(uint32_t *)(result + 148) != 3 && *(this + 8640) == 1 )  // this+8640 = uCastSlot8640
          *(this + 8640) = 0;  // this+8640 = uCastSlot8640
      }
      else
      {
        result = (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                   this,
                   "GOLEM_WALK",  // 资源/动画 TAG GOLEM_WALK
                   -1,
                   0,
                   0);
        *(this + 8640) = 1;  // this+8640 = uCastSlot8640
      }
    }
  }
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5A5CD0 sub_5A5CD0 —— 伤害修正 · 对剑魂 1.5 倍
// ·0x4DC390 类型过滤后 RTTI 判型 CNFighter（剑魂），且其 vt+840==19（特定姿态【推断】）时伤害 ×1.5 返回 0
// ------------------------------------------------------------
int /*stdcall*/ sub_5A5CD0(int *pDwArg1, int nArg2)  // 函数: 伤害修正 · 对剑魂 1.5 倍
{
  int result; // eax
  int v3; // esi
  int pObj; // eax

  result = sub_4DC390(pDwArg1, nArg2);  // 调 伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
  v3 = result;
  if ( result != 3 )
  {
    pObj = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNFighter `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    if ( pObj != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 19 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 1.5);
      return 0;
    }
    else
    {
      return v3;
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A5D40 sub_5A5D40 —— 大状态 9 进入副作用 · 速度槽 +0.2
// ·0x4DBA80 增益侧进入处理；nArg2==9 时速度槽（vt+672(0)+102）+0.2 写回并 vt+676 应用
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5D40(void *this, int nArg2)  // 函数: 大状态 9 进入副作用 · 速度槽 +0.2
{
  int result; // eax
  unsigned int pThis_2A0; // edi
  int v5; // edx
  int v6; // [esp+10h] [ebp+8h]

  result = sub_4DBA80(nArg2);  // 调 大状态进入副作用处理器（增益侧）
  if ( nArg2 == 9 )
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v6 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.2;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, v5, v6);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A5DA0 sub_5A5DA0 —— 大状态 9 退出副作用 · 速度槽还原
// 与 ·0x5A5D40 成对：·0x4DBC20(nArg2) 处理退出；nArg2==9 时把速度槽
// （vt+672(0)+102）读出 -0.2 写回并经 vt+676 应用，还原该大状态进入时的 +0.2
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5DA0(void *this, int nArg2)  // 函数: 大状态 9 退出副作用 · 速度槽还原
{
  int result; // eax
  unsigned int pThis_2A0; // edi
  int v5; // edx
  int v6; // [esp+10h] [ebp+8h]

  result = sub_4DBC20(nArg2);  // 调 大状态退出副作用处理器（0x4DBA80 的还原对偶）
  if ( nArg2 == 9 )
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v6 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) - 0.2;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, v5, v6);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  }
  return result;
}



// 石激光技能：Particle/StoneLaser.ptl + STONE_LASER_FIRE 播报（sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5A5E00 sub_5A5E00 —— 石魔像激光 · StoneLaser.ptl（200ms 冷却）
// vt+308 可行动且距上次 this+2169 ≥200ms（·0x699000 clock_now 门）时：
// vt+588 实体化 Particle/StoneLaser.ptl（参数面 90/60/4）→ vt+580 发射 30027 携粒子句柄，
// 刷新时间戳并播报 STONE_LASER_FIRE
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5E00(uint32_t *this)  // 函数: 石魔像激光 · StoneLaser.ptl（200ms 冷却）
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int pThis_668; // eax
  int v6; // edx

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    result = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
    if ( *(this + 2169) + 200 < result )  // this+8676〔uAI8676(推断)〕
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
             this,
             "Particle/StoneLaser.ptl",  // 资源路径 Particle/StoneLaser.ptl
             0,
             90,
             0,
             60,
             4,
             0,
             0,
             0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(v3 + 580))(this, 30027, 0, v4);  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
      pThis_668 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
      v6 = *this;
      *(this + 2169) = pThis_668;  // this+8676〔uAI8676(推断)〕
      return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v6 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
               this,
               "STONE_LASER_FIRE",  // 资源/动画 TAG STONE_LASER_FIRE
               -1,
               0,
               0);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A5E90 sub_5A5E90 —— 分身/攻击参数面复位（this+7531..7596）
// 参数面整面清零后置 this+7580=1【推断：默认段选】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5E90(int this, int nArg2, int nArg3)  // 函数: 分身/攻击参数面复位（this+7531..7596）
{
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
  *(uint32_t *)(this + 7580) = 1;  // this+7580 攻击面门字节
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A5F20 sub_5A5F20 —— 伤害修正（叠 ·0x5A5CD0）
// 攻击标签 +12 为 0 且 +128 标志成立时伤害 ×0.5 返回 2【推断：受击方状态减伤】
// ------------------------------------------------------------
int /*stdcall*/ sub_5A5F20(int *pDwArg1, int nArg2)  // 函数: 伤害修正（叠 ·0x5A5CD0）
{
  int result; // eax
  int v3; // edi

  result = sub_5A5CD0(pDwArg1, nArg2);  // 调 伤害修正 · 对剑魂 1.5 倍
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0  // 调用虚函数（虚表槽 +348）
      || *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 128) == 0 )  // 调用虚函数（虚表槽 +348）
    {
      return v3;
    }
    else
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.5);
      return 2;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A5F90 sub_5A5F90 —— 伤害修正 · 系数 0.6 档
// 叠 ·0x5A5CD0 基础修正（RTTI 判 CNFighter 剑魂 1.5 倍）；返回非 3 时查受击方
// vt+348 子对象 +12 标签：为 0 则伤害 ×0.6 并返回 0（已改写），否则沿原返回值透传
// ------------------------------------------------------------
int /*stdcall*/ sub_5A5F90(int *pDwArg1, int nArg2)  // 函数: 伤害修正 · 系数 0.6 档
{
  int result; // eax
  int v3; // esi

  result = sub_5A5CD0(pDwArg1, nArg2);  // 调 伤害修正 · 对剑魂 1.5 倍
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0 )  // 调用虚函数（虚表槽 +348）
    {
      return v3;
    }
    else
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.60000002);
      return 0;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A5FF0 sub_5A5FF0 —— 同构 ·0x5A5F90（差异：系数 0.7 档）
// 门槛与透传规则一致：·0x5A5CD0 返回非 3 且受击标签 +12 为 0 时伤害 ×0.7 并返回 0
// ------------------------------------------------------------
int /*stdcall*/ sub_5A5FF0(int *pDwArg1, int nArg2)  // 函数: 同构 ·0x5A5F90（差异：系数 0.7 档）
{
  int result; // eax
  int v3; // esi

  result = sub_5A5CD0(pDwArg1, nArg2);  // 调 伤害修正 · 对剑魂 1.5 倍
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0 )  // 调用虚函数（虚表槽 +348）
    {
      return v3;
    }
    else
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.69999999);
      return 0;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A6050 sub_5A6050 —— 四段连击攻击包相位机（30068 · 40px 步进扫段）
// 段号槽 this[2170]（0..3）对应动画帧表 {2,3,4,5}：当前帧 +148 命中该段且段门
// this[2169] 未置时，取目标 this+1813 坐标（vt+124/vt+120）发 ·0x4E4A50 包 30068
// （第 3 参 10 为附加参数，X 偏移 −8×(5×段号−10) 即 +80/+40/0/−40 四段；vt+152
// 朝向为 1 时偏移取反）；发射后置段门，帧推进到该段帧 +1 时清门并段号自增
// （门保证每段只发一次）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6050(int **this)  // 函数: 四段连击攻击包相位机（30068 · 40px 步进扫段）
{
  int *v2; // eax
  int v3; // eax
  int fld_e2170; // ecx
  int v5; // ebx
  int *fld_e1813; // edi
  int v7; // edx
  int v8; // eax
  int result; // eax
  int fld_e21702; // ecx
  int v11; // [esp-1Ch] [ebp-38h]
  uint32_t v12[5]; // [esp+8h] [ebp-14h]

  v2 = *this;
  v12[0] = 2;
  v12[1] = 3;
  v12[2] = 4;
  v12[3] = 5;
  v3 = ((int (/*thiscall*/ *)(int **))v2[50])(this);
  fld_e2170 = (int)*(this + 2170);  // this+8680〔uGate8680(推断)〕
  if ( *(uint32_t *)(v3 + 148) == v12[fld_e2170] && *(this + 2169) == nullptr )  // this+8676〔uAI8676(推断)〕
  {
    v5 = 8 * (5 * fld_e2170 - 10);
    if ( ((int (/*thiscall*/ *)(int **))(*this)[38])(this) == 1 )
      v5 = -v5;
    fld_e1813 = *(this + 1813);  // this+7252 = pTarget7252
    v7 = *fld_e1813;
    v12[4] = fld_e1813;
    v11 = (*(int (**)(void))(v7 + 124))();  // 调用虚函数（虚表槽 +124）
    v8 = (*(int (/*thiscall*/ **)(int *))(*fld_e1813 + 120))(fld_e1813);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    sub_4E4A50(this, 30068, 10, v8 - v5, v11, 0, 4, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    *(this + 2169) = (int *)1;  // this+8676〔uAI8676(推断)〕
  }
  result = ((int (/*thiscall*/ *)(int **))(*this)[50])(this);
  fld_e21702 = (int)*(this + 2170);  // this+8680〔uGate8680(推断)〕
  if ( *(uint32_t *)(result + 148) == v12[fld_e21702] + 1 )
  {
    *(this + 2169) = nullptr;  // this+8676〔uAI8676(推断)〕
    *(this + 2170) = (int *)(fld_e21702 + 1);  // this+8680〔uGate8680(推断)〕
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A6130 sub_5A6130 —— 与 ·0x5A6050 同族（差异：单次三点扇形 30068，
// 落点 = 目标 (X±30, Y−30)、(X, Y)、(X±30, Y+30) 三发齐射，靠 this[2169] 单次门防重入）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6130(int *this)  // 函数: 与 ·0x5A6050 同族（差异：单次三点扇形 30068，
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  int fld_e1813; // ebx
  int v6; // edi
  int v7; // eax
  int fld_e18132; // ebx
  int v9; // eax
  int fld_e18133; // ebx
  int v11; // eax
  int v12; // [esp-20h] [ebp-28h]
  int v13; // [esp-20h] [ebp-28h]
  int v14; // [esp-20h] [ebp-28h]

  result = *(this + 2169);  // this+8676〔uAI8676(推断)〕
  if ( result == 0 )
  {
    v3 = *this;
    *(this + 2169) = 1;  // this+8676〔uAI8676(推断)〕
    v4 = (*(int (**)(void))(v3 + 152))();  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    fld_e1813 = *(this + 1813);  // this+7252 = pTarget7252
    v6 = v4 != 0 ? -30 : 30;
    v12 = (*(int (**)(void))(*(uint32_t *)fld_e1813 + 124))() - 30;  // 调用虚函数（虚表槽 +124）
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    sub_4E4A50(this, 30068, 10, v6 + v7, v12, 0, 4, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    fld_e18132 = *(this + 1813);  // this+7252 = pTarget7252
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 124))(fld_e18132);  // 调用虚函数（虚表槽 +124）
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 120))(fld_e18132);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    sub_4E4A50(this, 30068, 10, v9, v13, 0, 4, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    fld_e18133 = *(this + 1813);  // this+7252 = pTarget7252
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18133 + 124))(fld_e18133) + 30;  // 调用虚函数（虚表槽 +124）
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18133 + 120))(fld_e18133);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    return sub_4E4A50(this, 30068, 10, v6 + v11, v14, 0, 4, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A6210 sub_5A6210 —— 攻击段号门（vt+308 可行动 + vt+840 姿态==8 + this+7028 段号==1）
// 四条件全真才返回真（段号读取经 ·0x41A5E0 防篡读）
// ------------------------------------------------------------
char /*thiscall*/ sub_5A6210(void *this, int nArg2)  // 函数: 攻击段号门（vt+308 可行动 + vt+840 姿态==8 + this+7028 段号==1）
{
  int pThis_1B74; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) == 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0  // 调用虚函数（虚表槽 +348）
    || (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) != 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    || (pThis_1B74 = sub_41A5E0((unsigned int)this + 7028)) != 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    LOBYTE(pThis_1B74) = 0;  // 调 取 16 位值低 8 位
  }
  return pThis_1B74;
}



// 石刃技能：引用 Particle/StoneBlade.ptl
// ------------------------------------------------------------
// 0x5A6270 sub_5A6270 —— 石刃粒子发射（Particle/StoneBlade.ptl + 30026）
// vt+588 实体化石刃粒子（参数面 50/135/4）→ vt+580 以 30026 号发射并携粒子句柄
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6270(int *this)  // 函数: 石刃粒子发射（Particle/StoneBlade.ptl + 30026）
{
  int v2; // edi
  int v3; // eax

  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(int *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
         this,
         "Particle/StoneBlade.ptl",  // 资源路径 Particle/StoneBlade.ptl
         0,
         50,
         0,
         135,
         4,
         0,
         0,
         0);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int))(v2 + 580))(this, 30026, 0, v3);  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
}



// 挥击技能：SWING_LONG 播报（this+200/+204 主状态硬直 + 8640/8641 相位）
// ------------------------------------------------------------
// 0x5A62B0 sub_5A62B0 —— 挥击主状态相位机（SWING_LONG + 8640/8641 双单次门）
// 先过 vt+724 冻结门走 ·0x5A5C40 行走播报；大状态 8 且段号 7028 为 0/2 时，动作帧
// +148 进 2 播报 SWING_LONG（置 8640 门，帧 >2 复位）；段号 2 且帧 1 时取 this+6216
// 向量首元素经 ·0x4926A0 复位后 vt+204 绑定动画（1000/XYZ−55/−150/1），置 8641 门；
// 尾调 ·0x4E1780 基类收尾
// ------------------------------------------------------------
char /*thiscall*/ sub_5A62B0(int this)  // 函数: 挥击主状态相位机（SWING_LONG + 8640/8641 双单次门）
{
  int *fld_1848; // ecx

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 724))(this) == 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
    sub_5A5C40((uint8_t *)this);  // 调 行走播报 · GOLEM_WALK（单次门）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && (sub_41A5E0(this + 7028) == 0 || sub_41A5E0(this + 7028) == 2) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( *(uint8_t *)(this + 8640) != 0  // this+8640 挥击播报单次门 A
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) != 2 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    {
      if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) > 2 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        *(uint8_t *)(this + 8640) = 0;  // this+8640 挥击播报单次门 A
    }
    else
    {
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        this,
        "SWING_LONG",  // 资源/动画 TAG SWING_LONG
        -1,
        0,
        0);
      *(uint8_t *)(this + 8640) = 1;  // this+8640 挥击播报单次门 A
    }
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && sub_41A5E0(this + 7028) == 2  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    && *(uint8_t *)(this + 8641) == 0  // this+8641 挥击相位单次门 B
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) == 1 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  {
    fld_1848 = *(int **)(this + 6216);  // this+6216 【推断】资源/帧游标表
    if ( fld_1848 != nullptr && (*(uint32_t *)(this + 6220) - (int)fld_1848) >> 2 != 0 )  // this+6220 资源/帧游标表尾针
    {
      sub_4926A0(*fld_1848);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int, int, uint32_t))(*(uint32_t *)this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        1000,
        **(uint32_t **)(this + 6216),  // this+6216 【推断】资源/帧游标表
        -55,
        -150,
        1,
        0);
      *(uint8_t *)(this + 8641) = 1;  // this+8641 挥击相位单次门 B
    }
  }
  return sub_4E1780((uint32_t *)this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
}



// 技能播报：GOLEM_02（魔像二段动作, this+208/8641）
// ------------------------------------------------------------
// 0x5A63E0 sub_5A63E0 —— 攻击段切换回调（GOLEM_02 + 大状态进出钩）
// 转发 ·0x4E33D0 基类状态收尾；进段 ArgList==8 且段号 7028==2 时清 8641 门，
// 段号非 1 时播报 GOLEM_02；离开段（前态 v8==8）且段号归 2 时取 this+1554 向量首项
// 经 vt+208 复位绑定（镜像 ·0x5A62B0 的进段演出）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A63E0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 攻击段切换回调（GOLEM_02 + 大状态进出钩）
{
  int result; // eax
  uint32_t *fld_e1554; // ecx
  int v8; // [esp+8h] [ebp-4h]

  v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      *((uint8_t *)this + 8641) = 0;  // this+8641 挥击相位单次门 B
    result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result != 1 )
      result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                 this,
                 "GOLEM_02",  // 资源/动画 TAG GOLEM_02
                 -1,
                 0,
                 0);
  }
  if ( v8 == 8 && ArgList != 8 )  // 若 v8 == 8 与/或 ArgList != 8
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 2 )
    {
      fld_e1554 = (uint32_t *)*(this + 1554);  // this+6216 = 资源/帧游标表
      if ( fld_e1554 != nullptr )  // 若 fld_e1554 有效（非空）
      {
        result = (*(this + 1555) - (int)fld_e1554) >> 2;  // this+6220〔pFrameVecEnd(推断)〕
        if ( result != 0 )  // 若结果非 0（成功）
          return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *fld_e1554);  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
      }
    }
  }
  return result;
}



// 石激光开火：STONE_LASER_FIRE 播报（this+208/8604 相位）
// ------------------------------------------------------------
// 0x5A64A0 sub_5A64A0 —— 石激光开火门（STONE_LASER_FIRE + 8604 单次门）
// 主动作对象 this+30 帧 +148 ≥3 时 vt+888(2,2,1000,1000) 挂伴随参数，vt+308 可行动
// 则调 ·0x5A5E00 发射激光；8604 门为 0 时 vt+208 绑定粒子句柄 *(this+1554)、置门
// 并播报 STONE_LASER_FIRE
// ------------------------------------------------------------
char /*thiscall*/ sub_5A64A0(uint32_t *this)  // 函数: 石激光开火门（STONE_LASER_FIRE + 8604 单次门）
{
  int fld_e30; // eax
  int v3; // edx

  fld_e30 = *(this + 30);  // this+120 = 动画对象指针
  if ( *(int *)(fld_e30 + 148) >= 3 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      sub_5A5E00(this);  // 调 石魔像激光 · StoneLaser.ptl（200ms 冷却）
    LOBYTE(fld_e30) = *((uint8_t *)this + 8604);  // this+8604 = bAI8604
    if ( (uint8_t)fld_e30 == 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));  // this+6216 = 资源/帧游标表
      v3 = *this;
      *((uint8_t *)this + 8604) = 1;  // this+8604 = bAI8604
      LOBYTE(fld_e30) = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v3 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                     this,
                     "STONE_LASER_FIRE",  // 资源/动画 TAG STONE_LASER_FIRE
                     -1,
                     0,
                     0);
    }
  }
  return fld_e30;
}



// 石激光蓄力：STONE_LASER_READY 播报（this+204/+208/8604 相位, 66L）
// ------------------------------------------------------------
// 0x5A6520 sub_5A6520 —— 石激光蓄力（STONE_LASER_READY + 8604/2169 复位）
// 前置 this+1639 主状态镜像后转发 ·0x5A63E0；进段 8 且段号 7028==1 时 vt+888(0,0,1000,1000)
// 清伴随参数、清 8604 与段门 this[2169]、播报 STONE_LASER_READY，取 this+1554 向量首项
// 经 ·0x4926A0 复位后 vt+204 绑定动画（1000/70/−55/1）；离段（1639 由 8 转非 8）且段号
// 仍为 1 时 vt+208 回退绑定同一句柄（与开火门 ·0x5A64A0 成对）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6520(int *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 石激光蓄力（STONE_LASER_READY + 8604/2169 复位）
{
  int fld_e1639; // ebx
  int result; // eax
  int v8; // edx
  int *fld_e1554; // ecx
  uint32_t *fld_e15542; // ecx

  fld_e1639 = *(this + 1639);  // this+6556 = 主状态镜像
  result = sub_5A63E0(this, ArgList, fArg3, nArg4, nArg5);  // 调 攻击段切换回调（GOLEM_02 + 大状态进出钩）
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
      v8 = *this;
      *((uint8_t *)this + 8604) = 0;  // this+8604 = bAI8604
      *(this + 2169) = 0;  // this+8676〔uAI8676(推断)〕
      result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                 this,
                 "STONE_LASER_READY",  // 资源/动画 TAG STONE_LASER_READY
                 -1,
                 0,
                 0);
      fld_e1554 = (int *)*(this + 1554);  // this+6216 = 资源/帧游标表
      if ( fld_e1554 != nullptr )  // 若 fld_e1554 有效（非空）
      {
        result = (*(this + 1555) - (int)fld_e1554) >> 2;  // this+6220〔pFrameVecEnd(推断)〕
        if ( result != 0 )  // 若结果非 0（成功）
        {
          sub_4926A0(*fld_e1554);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
          result = (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, int, int, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
                     this,
                     1000,
                     *(uint32_t *)*(this + 1554),  // this+6216 = 资源/帧游标表
                     70,
                     -55,
                     1,
                     0);
        }
      }
    }
  }
  if ( fld_e1639 == 8 && ArgList != 8 )  // 若 fld_e1639 == 8 与/或 ArgList != 8
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )
    {
      fld_e15542 = (uint32_t *)*(this + 1554);  // this+6216 = 资源/帧游标表
      if ( fld_e15542 != nullptr )  // 若 fld_e15542 有效（非空）
      {
        result = (*(this + 1555) - (int)fld_e15542) >> 2;  // this+6220〔pFrameVecEnd(推断)〕
        if ( result != 0 )  // 若结果非 0（成功）
          return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *fld_e15542);  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
      }
    }
  }
  return result;
}



// 狂暴 AI：C_BERSERK 播报（62L；读 this+6556 大状态 → 狂暴条件门【推断：濒死/血线触发】）
// ------------------------------------------------------------
// 0x5A6630 sub_5A6630 —— 狂暴（C_BERSERK）攻击段相位
// 前置读 this+6556 大状态镜像后转发 ·0x5A63E0；进段 8 且段号 7028==1 时清 8604 门，
// 取 this+6216 向量首项经 ·0x4926A0 复位 → vt+204 绑定动画（1000/85/−55/1）并播报
// C_BERSERK；离段（6556 由 8 转非 8）且段号仍为 1 时 vt+208 回退绑定
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6630(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 狂暴（C_BERSERK）攻击段相位
{
  int nMainState6556; // ebx  | +0x199C → 主状态镜像（全库通用 this+6556；vt+840 读取器 / 0x5A9100 大状态门）（CNGolemSteel）
  int result; // eax
  int *fld_1848; // ecx
  uint32_t *fld_18482; // ecx

  nMainState6556 = *(uint32_t *)(this + 6556);  // this+6556 主状态镜像
  result = sub_5A63E0((uint32_t *)this, ArgList, fArg3, nArg4, nArg5);  // 调 攻击段切换回调（GOLEM_02 + 大状态进出钩）
  if ( ArgList == 8 )
  {
    result = sub_41A5E0(this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )
    {
      *(uint8_t *)(this + 8604) = 0;  // this+8604 狂暴段门
      fld_1848 = *(int **)(this + 6216);  // this+6216 【推断】资源/帧游标表
      if ( fld_1848 != nullptr )  // 若 fld_1848 有效（非空）
      {
        result = (*(uint32_t *)(this + 6220) - (int)fld_1848) >> 2;  // this+6220 资源/帧游标表尾针
        if ( result != 0 )  // 若结果非 0（成功）
        {
          sub_4926A0(*fld_1848);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int, int, uint32_t))(*(uint32_t *)this + 204))(  // 调用虚函数（虚表槽 +204）
            this,
            1000,
            **(uint32_t **)(this + 6216),  // this+6216 【推断】资源/帧游标表
            85,
            -55,
            1,
            0);
          result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                     this,
                     "C_BERSERK",  // 资源/动画 TAG C_BERSERK
                     -1,
                     0,
                     0);
        }
      }
    }
  }
  if ( nMainState6556 == 8 && ArgList != 8 )  // 若 fld_199C == 8 与/或 ArgList != 8
  {
    result = sub_41A5E0(this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )
    {
      fld_18482 = *(uint32_t **)(this + 6216);  // this+6216 【推断】资源/帧游标表
      if ( fld_18482 != nullptr )  // 若 fld_18482 有效（非空）
      {
        result = (*(uint32_t *)(this + 6220) - (int)fld_18482) >> 2;  // this+6220 资源/帧游标表尾针
        if ( result != 0 )  // 若结果非 0（成功）
          return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *fld_18482);  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
      }
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A6710 sub_5A6710 —— 收手组合入口
// this+1639 主状态==8 且段号 7028==1 时 vt+1312 动作触发（收手），随后无条件走
// ·0x5A62B0 挥击相位机
// ------------------------------------------------------------
char /*thiscall*/ sub_5A6710(uint32_t *this)  // 函数: 收手组合入口
{
  if ( *(this + 1639) == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1312))(this);  // 调用虚函数（虚表槽 +1312）
  return sub_5A62B0((int)this);  // 调 挥击主状态相位机（SWING_LONG + 8640/8641 双单次门）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A6740 sub_5A6740 —— 系数面降档（nArg3==0）
// this+1905 参数块 +68 速率项 ×0.76923（÷1.3）写回；与 ·0x5A2CD0 同族的 +1905 面版本
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6740(uint32_t *this, int nArg2, int nArg3)  // 函数: 系数面降档（nArg3==0）
{
  int result; // eax
  int pParamObj7620; // eax  | +0x1DC4 → 速度/属性参数对象（CNGolemGold）
  double v5; // st7

  result = nArg3;
  if ( nArg3 == 0 )
  {
    pParamObj7620 = *(this + 1905);  // this+7620 = 速度/属性参数对象
    v5 = *(float *)(pParamObj7620 + 68);
    result = pParamObj7620 + 64;
    *(float *)(result + 4) = v5 * 0.76923078;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A6770 sub_5A6770 —— 分身/攻击参数面重置（this+7531..7596）+ 增幅档
// 面内各槽清零后置 this+7534=1（缺省段选【推断】）；nArg3==0 时速度/参数对象
// this+7620 +68 浮点 ×1.3【推断：速率增幅档】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6770(int this, int nArg2, int nArg3)  // 函数: 分身/攻击参数面重置（this+7531..7596）+ 增幅档
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
  *(uint8_t *)(this + 7534) = 1;  // this+7534 配置块 +14 / 段选门
  if ( nArg3 == 0 )
    *(float *)(*(uint32_t *)(this + 7620) + 68) = *(float *)(*(uint32_t *)(this + 7620) + 68) * 1.3;  // this+7620 速度/属性参数对象
  return result;
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5A6820 sub_5A6820 —— 进段时钟门 + 时间戳登记
// 进段（ArgList==8）且来参 4 号槽计数 ≥1 时按距离取消：目标 vt+120 与自身 vt+120 差
// 小于速度面对象 this[1905]+16 阈值则把该槽清零【推断：贴身时撤销蓄力/位移标记】；
// 转发 ·0x4E33D0 收尾后清段门 this[2169]/段号 this[2170]，并以 ·0x699000 登记
// this[2171] 时间戳（供 ·0x5A6C40 的 25ms 节流基准）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6820(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 进段时钟门 + 时间戳登记
{
  int pTarget7252; // ecx  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int v7; // ebx
  int result; // eax

  if ( ArgList == 8 && *(int *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) >= 1 )  // 调 取 64 位值低 32 位
  {
    pTarget7252 = *(this + 1813);  // this+7252 = pTarget7252
    if ( pTarget7252 != 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget7252 + 120))(pTarget7252);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      if ( (signed int)abs32(v7 - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this)) < *(uint32_t *)(*(this + 1905) + 16) )  // this+7620 = 速度/属性参数对象
        *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) = 0;  // 调 取 64 位值低 32 位
    }
  }
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 8 )
  {
    *(this + 2169) = 0;  // this+8676〔uAI8676(推断)〕
    *(this + 2170) = 0;  // this+8680〔uGate8680(推断)〕
    result = sub_699000((int)(this + 1910));  // 【clock_now(clk)】
    *(this + 2171) = result;  // this+8684〔bGate8684(推断)〕
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A68C0 sub_5A68C0 —— 速度面减档（-1.0 档 + ×0.5 档；与 ·0x5A69C0 互为还原对）
// nArg3==0：vt+672(0) 速度容器的 +102/+158 两浮点槽各 -1.0（·0x41A5E0 读 / ·0x41A590 写）
// 后 vt+676 应用；nArg2==0 对速度面对象 +36 ×0.5；nArg2 1..2（nArg3==0 侧）或 nArg3==2
// 且 0<=nArg2<=1 时，对 +68 与 +100 各 ×0.5【推断：减速/降攻弱化档】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A68C0(uint32_t *this, int nArg2, int nArg3)  // 函数: 速度面减档（-1.0 档 + ×0.5 档；与 ·0x5A69C0 互为还原对）
{
  int result; // eax
  bool v5; // cc
  unsigned int v6; // edi
  int v7; // edx
  unsigned int v8; // edi
  int v9; // edx
  int fld_e1905; // eax
  double v11; // st7
  int v12; // [esp+10h] [ebp+Ch]
  int v13; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 102;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v6)) - 1.0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v6, v7, v12);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 158;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v13 = COERCE_FLOAT(sub_41A5E0(v8)) - 1.0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v8, v9, v13);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
    result = nArg2;
    if ( nArg2 == 0 )
    {
      *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.5;  // this+7620 = 速度/属性参数对象
      return result;
    }
    if ( nArg2 <= 0 )
      return result;
    v5 = nArg2 <= 2;
    goto LABEL_8;
  }
  result = nArg3 - 2;
  if ( nArg3 == 2 )
  {
    result = nArg2;
    if ( nArg2 >= 0 )
    {
      v5 = nArg2 <= 1;
LABEL_8:
      if ( v5 )
      {
        fld_e1905 = *(this + 1905);  // this+7620 = 速度/属性参数对象
        v11 = *(float *)(fld_e1905 + 68);
        result = fld_e1905 + 64;
        *(float *)(result + 4) = v11 * 0.5;
        *(float *)(*(this + 1905) + 100) = *(float *)(*(this + 1905) + 100) * 0.5;  // this+7620 = 速度/属性参数对象
      }
    }
  }
  return result;
}



// AI 相位辅助（94L）
// ------------------------------------------------------------
// 0x5A69C0 sub_5A69C0 —— 与 ·0x5A68C0 同构（差异：速度面 +102/+158 各 +1.0、+36/+68/+100
// 各 ×2 为增幅方向；nArg3==0 时另置 this+7596=50；开头额外整面清 this+7531..7596
// 分身参数面并置 this+7580=1——复位侧与 ·0x5A5E90 同型）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A69C0(char *this, int nArg2, int nArg3)  // 函数: 与 ·0x5A68C0 同构（差异：速度面 +102/+158 各 +1.0、+36/+68/+100
{
  char *pThis_1D73; // ecx
  int result; // eax
  int pThis_771; // eax
  double v7; // st7
  int v8; // edx
  unsigned int v9; // edi
  int v10; // edx
  unsigned int pThis_2A0; // edi
  int v12; // edx
  int pThis_7712; // eax
  double v14; // st7
  int v15; // [esp+14h] [ebp+Ch]
  int v16; // [esp+14h] [ebp+Ch]

  *(this + 7558) = 0;  // this+7558 = 攻击参数面字节槽
  *(this + 7557) = 0;  // this+7557 = 攻击面门字节
  *(this + 7556) = 0;  // this+7556 = 攻击面模式字节
  *(this + 7534) = 0;  // this+7534 = 内嵌配置块 +14 字节
  *(this + 7533) = 0;  // this+7533 = 内嵌配置块 +13 字节
  *(this + 7532) = 0;  // this+7532 = 内嵌配置块 +12 字节
  *(this + 7531) = 0;  // this+7531 = 内嵌配置块 +11 字节
  *(uint32_t *)(this + 7535) = 0;  // this+7535 = 内嵌配置块 +15 字节
  pThis_1D73 = this + 7539;  // this+7539 配置块 17 字节循环搬运区起点
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *((uint32_t *)this + 1893) = 0;  // this+7572 = 模式 2 档
  *((uint32_t *)this + 1892) = 0;  // this+7568 = 激活/模式槽
  *((uint32_t *)this + 1891) = 0;  // this+7564 = 形态/模式槽
  *((uint32_t *)this + 1897) = 0;  // this+7588 = 形态槽
  *((uint32_t *)this + 1896) = 0;  // this+7584 = 形态槽
  *((uint32_t *)this + 1895) = 0;  // this+7580 = 攻击面门字节
  *((uint32_t *)this + 1894) = 0;  // this+7576 = 相位槽
  *((uint32_t *)this + 1899) = 0;  // this+7596 = 段号横向偏置
  *((uint32_t *)this + 1895) = 1;  // this+7580 = 攻击面门字节
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
    {
      result = nArg2;
      if ( (unsigned int)nArg2 <= 1 )
      {
        pThis_771 = *((uint32_t *)this + 1905);  // this+7620 = 速度/属性参数对象
        v7 = *(float *)(pThis_771 + 68);  // this+68 角色数
        result = pThis_771 + 64;  // this+64 服务器页签按钮组 6 个
        *(float *)(result + 4) = v7 + v7;
        *(float *)(*((uint32_t *)this + 1905) + 100) = *(float *)(*((uint32_t *)this + 1905) + 100)  // this+7620 = 速度/属性参数对象
                                                   + *(float *)(*((uint32_t *)this + 1905) + 100);  // this+7620 = 速度/属性参数对象
      }
    }
  }
  else
  {
    v8 = *(uint32_t *)this;
    *((uint32_t *)this + 1899) = 50;  // this+7596 = 段号横向偏置
    v9 = (*(int (/*thiscall*/ **)(char *, uint32_t))(v8 + 672))(this, 0) + 102;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v15 = COERCE_FLOAT(sub_41A5E0(v9)) + 1.0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v9, v10, v15);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 158;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v16 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 1.0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, v12, v16);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
    result = nArg2;
    if ( nArg2 != 0 )
    {
      if ( nArg2 > 0 && nArg2 <= 2 )  // 若 nArg2 > 0 与/或 nArg2 <= 2
      {
        pThis_7712 = *((uint32_t *)this + 1905);  // this+7620 = 速度/属性参数对象
        v14 = *(float *)(pThis_7712 + 68);  // this+68 角色数
        result = pThis_7712 + 64;  // this+64 服务器页签按钮组 6 个
        *(float *)(result + 4) = v14 + v14;
        *(float *)(*((uint32_t *)this + 1905) + 100) = *(float *)(*((uint32_t *)this + 1905) + 100)  // this+7620 = 速度/属性参数对象
                                                   + *(float *)(*((uint32_t *)this + 1905) + 100);  // this+7620 = 速度/属性参数对象
      }
    }
    else
    {
      *(float *)(*((uint32_t *)this + 1905) + 36) = *(float *)(*((uint32_t *)this + 1905) + 36)  // this+7620 = 速度/属性参数对象
                                                + *(float *)(*((uint32_t *)this + 1905) + 36);  // this+7620 = 速度/属性参数对象
    }
  }
  return result;
}



// AI 字段访问（this+8680）
// ------------------------------------------------------------
// 0x5A6B60 sub_5A6B60 —— 蓄力段号 3 分支（800ms 动画绑定）
// 大状态 8 且段号 7028==3 时先 vt+208 以 this[1554] 首项绑定；转发 ·0x5A6520
// 蓄力相位机；进段且段号仍为 3 时清 this+8680 单次门，·0x4926A0 复位首项句柄后
// vt+204 绑定动画（1000/70/−55/1）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6B60(uint32_t **this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 蓄力段号 3 分支（800ms 动画绑定）
{
  int result; // eax
  int *fld_e1554; // eax

  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[210])(this) == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 3 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 1554));  // this+6216 = 资源/帧游标表
  result = sub_5A6520((int *)this, ArgList, fArg3, nArg4, nArg5);  // 调 石激光蓄力（STONE_LASER_READY + 8604/2169 复位）
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 3 )
    {
      fld_e1554 = *(this + 1554);  // this+6216 = 资源/帧游标表
      *((uint8_t *)this + 8680) = 0;  // this+8680 石刃一次性门
      sub_4926A0(*fld_e1554);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      return ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, int, int, uint32_t))(*this)[51])(
               this,
               1000,
               **(this + 1554),  // this+6216 = 资源/帧游标表
               70,
               -55,
               1,
               0);
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A6C00 sub_5A6C00 —— 挥击+激光组合门
// 走 ·0x5A62B0 挥击相位机；vt+840 姿态==8 且段号 7028==1 时接 ·0x5A64A0 石激光开火门
// ------------------------------------------------------------
char /*thiscall*/ sub_5A6C00(uint32_t *this)  // 函数: 挥击+激光组合门
{
  int pThis_6DD; // eax

  sub_5A62B0((int)this);  // 调 挥击主状态相位机（SWING_LONG + 8640/8641 双单次门）
  pThis_6DD = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( pThis_6DD == 8 )
  {
    pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( pThis_6DD == 1 )
      LOBYTE(pThis_6DD) = sub_5A64A0(this);  // 调 石激光开火门（STONE_LASER_FIRE + 8604 单次门）
  }
  return pThis_6DD;
}



// AI 主状态门（this+200, 76L）
// ------------------------------------------------------------
// 0x5A6C40 sub_5A6C40 —— 段号 1 相位机（起手：速率双轴 + 25ms 周期坐标粒子）
// 可行动（vt+308）且段门 this[2169] 未置、动作帧 +148==4 时起手：置门后经 vt+876 两次
// 写速率双轴（第 0 轴 1800/1800/0/−300/1，第 1 轴全零），vt+152(4) 求值经 vt+896 写伴随参数；
// 随后帧 ≥4 且距时间戳 this[2171] 超 25ms 节流门时，以 vt+924(42) 作下标从 dword_8F8270
// 句柄表取对象【推断：粒子对象】：其 vt+40 写 X（vt+120 ± 依 vt+152 的 30）、vt+28 子对象 +84
// 写方向标志、vt+12 激活、vt+92 取坐标经 ·0x4600B0 实体化；末刷新时间戳
// ------------------------------------------------------------
void /*thiscall*/ sub_5A6C40(uint32_t *this)  // 函数: 段号 1 相位机（起手：速率双轴 + 25ms 周期坐标粒子）
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  int v10; // edi
  int nRand; // eax
  int v12; // eax
  int v13; // edi
  uint32_t *v14; // edi
  void *fld_e29; // ecx
  int v16; // [esp-8h] [ebp-34h]
  char v17[4]; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-20h]
  uint32_t *v19; // [esp+18h] [ebp-14h]
  bool v20; // [esp+1Fh] [ebp-Dh]
  int v21; // [esp+28h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && *(this + 2169) == 0  // this+8676〔uAI8676(推断)〕
    && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) == 4 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  {
    v2 = *this;
    *(this + 2169) = 1;  // this+8676〔uAI8676(推断)〕
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(v2 + 876))(this, 0, 1800, 1800, 0, -300, 1);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
      this,
      1,
      0,
      0,
      0,
      0,
      0);
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v3 + 896))(this, v4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
  }
  if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) >= 4  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    && *(this + 2171) + 25 < (unsigned int)sub_699000((int)(this + 1910)) )  // 【clock_now(clk)】
  {
    v5 = (uint32_t *)dword_8F8270[(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 924))(this, 42)];  // 调用虚函数（虚表槽 +924）
    v6 = *this;
    v19 = v5;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v8 = *this;
    v9 = *v5;
    v20 = v7 == 0;
    v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 128))(this);  // 调用虚函数（虚表槽 +128）
    nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
    v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nRand % 40 + v10);  // 调用虚函数（虚表槽 +124）
    v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, v12 + 10) != 0 ? -30 : 30;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + v13;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v14 = v19;
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 40))(v19, v16);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v19 + 28))(v19) + 84) = v20;  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v14 + 12))(v14, 0);  // 调用虚函数（虚表槽 +12）
    (*(void (/*thiscall*/ **)(uint32_t *, char *))(*v14 + 92))(v14, v17);  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
    fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
    v21 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v17);  // 调 演播层注册(槽号)
    *(this + 2171) = sub_699000((int)(this + 1910));  // 调 【clock_now(clk)】
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
  }
}



// 登场/技能播报：RAIZO_01（曲/语音槽, this+8680）
// ------------------------------------------------------------
// 0x5A6E00 sub_5A6E00 —— 段号 3 相位机（RAIZO_01 播报 + 石刃发射）
// 先走 ·0x5A62B0 挥击相位机；姿态 8 且段号 7028==1 时接 ·0x5A64A0 石激光开火门；
// this+8680 单次门为 0、姿态 8、段号==3 且当前动画对象 this+120 帧 ≥4 时：可行动
// 则 ·0x5A6270 发射石刃粒子，播报 RAIZO_01 并置 8680 门
// ------------------------------------------------------------
char /*thiscall*/ sub_5A6E00(int this)  // 函数: 段号 3 相位机（RAIZO_01 播报 + 石刃发射）
{
  int pThis_348; // eax

  sub_5A62B0(this);  // 调 挥击主状态相位机（SWING_LONG + 8640/8641 双单次门）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0(this + 7028) == 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_5A64A0((uint32_t *)this);  // 调 石激光开火门（STONE_LASER_FIRE + 8604 单次门）
  LOBYTE(pThis_348) = *(uint8_t *)(this + 8680);  // 调 取 16 位值低 8 位
  if ( (uint8_t)pThis_348 == 0 )
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    if ( pThis_348 == 8 )
    {
      pThis_348 = sub_41A5E0(this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( pThis_348 == 3 )
      {
        pThis_348 = *(uint32_t *)(this + 120);  // this+120 动画/帧对象指针
        if ( pThis_348 != 0 && *(int *)(pThis_348 + 148) >= 4 )  // this+148 第 4 组·+802 增量子倍率
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
            sub_5A6270((int *)this);  // 调 石刃粒子发射（Particle/StoneBlade.ptl + 30026）
          LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                         this,
                         "RAIZO_01",  // 资源/动画 TAG RAIZO_01
                         -1,
                         0,
                         0);
          *(uint8_t *)(this + 8680) = 1;  // this+8680 石刃一次性门
        }
      }
    }
  }
  return pThis_348;
}



// 埋伏魔像语音组：GOLEM_DOWN/GOLEM_FIND/GOLEM_DMG/GOLEM_DIE + R_GOLEM_AMB（伏击埋地）
// ------------------------------------------------------------
// 0x5A6EA0 sub_5A6EA0 —— 埋伏型魔像语音组装载（伏击埋地配置）
// 语音档面 this+6792..6808 写 {1,2,3,3,4}；经 ·0x4015C0 依次注册 GOLEM_DOWN /
// GOLEM_FIND / GOLEM_DMG / GOLEM_DIE 四语音槽，并清 8640 门、this+7324=300；
// 末尾注册 R_GOLEM_AMB 槽交 ·0x4DE5E0 装载随机倒计时（区间 5000..10000、档 15）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6EA0(int this)  // 函数: 埋伏型魔像语音组装载（伏击埋地配置）
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

  v11 = 10;
  v10 = (int)"GOLEM_DOWN";  // 资源/动画 TAG GOLEM_DOWN
  *(uint32_t *)(this + 6792) = 1;  // this+6792 【推断】炮车/子类参数面槽 1
  *(uint32_t *)(this + 6796) = 2;  // this+6796 【推断】炮车/子类参数面槽 2
  *(uint32_t *)(this + 6800) = 3;  // this+6800 【推断】炮车/子类参数面槽 3
  *(uint32_t *)(this + 6804) = 3;  // this+6804 【推断】炮车/子类参数面槽 4
  *(uint32_t *)(this + 6808) = 4;  // this+6808 【推断】炮车/子类参数面槽 5
  sub_4015C0((void *)v10, v11);  // 【std::string构造赋值】
  sub_4015C0("GOLEM_FIND", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("GOLEM_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("GOLEM_DIE", 9u);  // 【std::string构造赋值】
  v11 = 10000;
  v10 = 5000;
  v12 = &v3;
  *(uint32_t *)(this + 7324) = 300;
  *(uint8_t *)(this + 8640) = 0;  // this+8640 【推断】出土相位槽
  v9 = 15;
  v8 = 0;
  LOBYTE(v4) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("R_GOLEM_AMB", 0xBu);  // 【std::string构造赋值】
  return sub_4DE5E0(v3, v4, v5, v6, v7, v8, v9, v10, v11);  // 调 文案条目装载 + 随机倒计时（0x4DE410 的配套件）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A6F70 sub_5A6F70 —— 攻击段号分派器
// 前置 ·0x5A62B0；姿态 8 时按段号 7028−1 分派：0 走 ·0x5A6C40、1 走 ·0x5A6050、
// 2 走 ·0x5A6130（后两支要求目标 this+1813 非空且 vt+308 可行动）
// ------------------------------------------------------------
void /*thiscall*/ sub_5A6F70(int *this)  // 函数: 攻击段号分派器
{
  int pThis_6DD; // eax
  int v3; // eax

  sub_5A62B0((int)this);  // 调 挥击主状态相位机（SWING_LONG + 8640/8641 双单次门）
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    pThis_6DD = sub_41A5E0((unsigned int)(this + 1757)) - 1;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( pThis_6DD != 0 )
    {
      v3 = pThis_6DD - 1;
      if ( v3 != 0 )
      {
        if ( v3 == 1 && *(this + 1813) != 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // this+7252 = pTarget7252
          sub_5A6130(this);  // 调 与 ·0x5A6050 同族（差异：单次三点扇形 30068，
      }
      else if ( *(this + 1813) != 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // this+7252 = pTarget7252
      {
        sub_5A6050((int **)this);  // 调 四段连击攻击包相位机（30068 · 40px 步进扫段）
      }
    }
    else
    {
      sub_5A6C40(this);  // 调 段号 1 相位机（起手：速率双轴 + 25ms 周期坐标粒子）
    }
  }
}



// 登场曲：sub_406D60 写 "B_FLATANY_01"（77L）
// ------------------------------------------------------------
// 0x5A6FF0 sub_5A6FF0 —— 行为字相位机 + 血线霸体门（B_FLATANY_01 登场曲）
// 头调 ·0x4E0120 基类周期处理后按行为字 this+1787 分派：态 0 → vt+1284 入场处理，困难级
// （this+1943==3）经 ·0x406D60 写登场曲 B_FLATANY_01；态 4/5 无目标 → vt+1104(13)；态
// 13/14/15 有目标 → vt+1104(5)。随后以出场参数面 vt+384(0)×0.01 为血线比例：当前血
// vt+736 不高于 满血 vt+740×比例 时经 ·0x51A7D0 造 0x64 字节霸体(CNSuperArmor) PO 入
// this[2168] 并 vt+56 绑定本尊；高于血线且 PO 已激活（vt+80==1）则 vt+76(0) 撤销【推断：残血霸体】
// ------------------------------------------------------------
void /*thiscall*/ sub_5A6FF0(uint32_t *this)  // 函数: 行为字相位机 + 血线霸体门（B_FLATANY_01 登场曲）
{
  uint32_t *pThis; // ecx
  void *pMem; // eax
  int pObj; // eax
  int uAI8672; // ecx  | +0x21E0 → 子类 AI 相位槽（0x5A5BB0 十槽清零族）（证据 va=005A5BB0）（CNGolem；va=005A5BB0）
  float Block; // [esp+4h] [ebp-18h]
  float v7; // [esp+8h] [ebp-14h]

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( *(this + 1787) )  // this+7148 = nBigState
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
      if ( *(this + 1943) == 3 )  // this+7772 = nCounterState
        sub_406D60("B_FLATANY_01");  // 调 std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      pThis = this;
      if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
        goto LABEL_10;
      goto LABEL_5;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) == 0 )  // this+7252 = pTarget7252
LABEL_5:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
      break;
    case 0xD:
    case 0xE:
    case 0xF:
      if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
      {
        pThis = this;
LABEL_10:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(pThis, 5);  // 调用虚函数（虚表槽 +1104）
      }
      break;
    default:
      break;
  }
  v7 = (double)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0) * 0.0099999998;  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  Block = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
  if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * v7 < Block )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
  {
    uAI8672 = *(this + 2168);  // this+8672 = 子类 AI 槽
    if ( uAI8672 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)uAI8672 + 80))(uAI8672) == 1 )  // 调用虚函数（虚表槽 +80）
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2168) + 76))(*(this + 2168), 0);  // this+8672 = 子类 AI 槽
  }
  else
  {
    if ( *(this + 2168) == 0 )  // this+8672 = 子类 AI 槽
    {
      pMem = operator new(0x64u);  // operator new 分配 100 字节
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        pObj = sub_51A7D0(pMem);  // 调 构造后把时长写入虚 64 结果 +40
      else
        pObj = 0;
      *(this + 2168) = pObj;  // this+8672 = 子类 AI 槽
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;  // 调用虚函数（虚表槽 +64）【推断: 取观察者容器（懒创建 0x44 字节 sb_499960(thi…】
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2168) + 80))(*(this + 2168)) == 0 )  // this+8672 = 子类 AI 槽
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2168) + 56))(  // this+8672 = 子类 AI 槽
        *(this + 2168),  // this+8672 = 子类 AI 槽
        this,
        this,
        1,
        0,
        0,
        -1);
  }
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5A71B0 sub_5A71B0 —— 困难级行为掷点（近身转向攻击 / 位移表现包）
// 可行动且困难级（this+1943==3）时二分掷 50%：近身侧经 ·0x4E7F30(200,75) 检测取对象，
// 按双方 vt+120 比大小经 vt+144 转向，·0x431230 打包参数后 vt+560 setState(8) 攻击；
// 另一侧再掷 25%（净 12.5%）发 ·0x4E4A50(30022) 表现包，携自身坐标 vt+120/vt+124
// 与朝向 vt+152【推断：位移/表现资源】
// ------------------------------------------------------------
void /*thiscall*/ sub_5A71B0(uint32_t *this)  // 函数: 困难级行为掷点（近身转向攻击 / 位移表现包）
{
  int pObj; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // [esp-18h] [ebp-3Ch]
  int v8; // [esp-10h] [ebp-34h]
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v10[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && *(this + 1943) == 3 )  // this+7772 = nCounterState
  {
    if ( rand() % 100 >= 50 )  // 调 以 16 位种子状态递推并返回 15 位结果
    {
      if ( rand() % 100 < 25 )  // 调 以 16 位种子状态递推并返回 15 位结果
      {
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        sub_4E4A50(this, 30022, 0, v6, v7, 0, v8, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
      }
    }
    else
    {
      pObj = sub_4E7F30(this, 200, 75, 0);  // 调 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
      if ( pObj != 0 )
      {
        v3 = *this;
        v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        (*(void (/*thiscall*/ **)(uint32_t *, bool))(v3 + 144))(this, v5 < v4);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
        memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
        v10[3] = 0;
        v10[0] = 1;
        sub_431230((int)pBuf, v10);  // 调 uint32 vector push_back
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      }
    }
  }
}



// 格挡特效：Character/Swordman/Effect/Animation/GuardSpark.ani + SWD_GUARDED 播报
//   （43L；与 0x5A4B20 vmt200 覆写同族, 此为普通槽位版本）
// ------------------------------------------------------------
// 0x5A72E0 sub_5A72E0 —— 格挡火花特效（SWD_GUARDED 播报 · 43L）
// 资源门 ·0x42FCB0(228) 通过则 ·0x431860 装载 Character/Swordman/Effect/Animation/GuardSpark.ani；
// ·0x44B6C0(284) 造特效对象并以 ·0x44E0D0 绑动画、写 vftable，经 ·0x45FE80 入演播层 2；
// 对象 vt+148 写自身朝向 vt+152，落点由 pArg3 三浮点取（X/Y 取 pArg3[0]/[1] 位型，
// Z = vt+124(pArg3[2] 截整) − 1）经对象 vt+112 摆放；末尾 vt+212 播报 SWD_GUARDED
// （与 vmt200 覆写 0x5A4B20 同族）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A72E0(int *this, int nArg2, float *pArg3)  // 函数: 格挡火花特效（SWD_GUARDED 播报 · 43L）
{
  int v4; // ebx
  char *v5; // eax
  char *v6; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // ebx
  int v11; // [esp-4h] [ebp-20h]

  v4 = 0;
  if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
    v4 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardSpark.ani", 1);  // 调 动画件构造（资源 id 版）
  v5 = (char *)sub_44B6C0(284);  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
  v6 = v5;
  if ( v5 != nullptr )  // 若 v5 有效（非空）
  {
    sub_44E0D0(v5, v4, 1);  // 调 CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)v6 = &CNRDPooledObject::`vftable';  // vftable 复位
  }
  else
  {
    v6 = nullptr;
  }
  sub_45FE80(*(this + 29), (int)v6, 2, 0, (int)v6, (int)this, 0);  // 调 对象注册
  v7 = *(uint32_t *)v6;
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  (*(void (/*thiscall*/ **)(char *, int))(v7 + 148))(v6, v8);  // 调用虚函数（虚表槽 +148）【推断: 同 vmt90 但不检查（直接写）】
  v9 = *(uint32_t *)v6;
  v11 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, (uint64_t)pArg3[2]) - 1;  // 调用虚函数（虚表槽 +124）
  (*(void (/*fastcall*/ **)(char *, uint32_t, uint32_t, int))(v9 + 112))(  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    v6,
    (uint64_t)*pArg3 >> 32,
    (uint64_t)*pArg3,
    v11);
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SWD_GUARDED", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
}



// ============================================================
// 【分区 8】石魔像·五色兵装（SG/ST/CL/GD/BR/PT）（0x5A73E0-0x5A82B0）
// 证据：Monster/Golem/{SG,ST,CL,GD,BR}/ST*.equ 分色部件 + GD/PT* 头/角件、
//       Particle/STGolemBullet.ptl / STGolemFire.ptl / STGolemHikari.ptl / BRGolemBullet.ptl

// 烟火特效装载：Monster/Golem/Particle/ani/STGolemFireSmoke.ani（102L；sub_431860）
// ------------------------------------------------------------
// 0x5A73E0 sub_5A73E0 —— 埋地烟火烟雾双发（STGolemFireSmoke.ani）
// 按朝向 vt+152 求落点偏置 ±95（基于 vt+120 坐标）：先对 this[2166] 起的两个池化
// 对象循环设位（X=偏置点，第二坐标经 vt+124 按 vt+128 高度+65 求值）→ 对象 vt+92
// 打包坐标交 ·0x4600B0 实体化；再装载 STGolemFireSmoke.ani 造对象、设朝向，
// 按（偏置点，vt+124(vt+128 高度+110)）摆放
// ------------------------------------------------------------
int /*thiscall*/ sub_5A73E0(uint32_t *this)  // 函数: 埋地烟火烟雾双发（STGolemFireSmoke.ani）
{
  int v2; // edi
  int v3; // edi
  int **pThis_876; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  void *fld_e29; // ecx
  bool v9; // zf
  int v10; // edi
  int v11; // edi
  char *v12; // eax
  char *v13; // edi
  int fld_e292; // ecx
  int v15; // ebx
  int v16; // eax
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  char v21[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int v23; // [esp+14h] [ebp-20h]
  int v24; // [esp+18h] [ebp-1Ch]
  char *v25; // [esp+1Ch] [ebp-18h]
  int v26; // [esp+20h] [ebp-14h]
  int v27; // [esp+24h] [ebp-10h]
  int v28; // [esp+30h] [ebp-4h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v3 = v2 + 95;
  else
    v3 = v2 - 95;
  v27 = v3;
  pThis_876 = (int **)(this + 2166);  // this+8664 = 子类 AI 槽
  v26 = 2;
  do
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(**pThis_876 + 12))(*pThis_876, 0);  // 调用虚函数（虚表槽 +12）
    v5 = **pThis_876;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v6 + 65);  // 调用虚函数（虚表槽 +124）
    (*(void (/*thiscall*/ **)(int *, int, int))(v5 + 40))(*pThis_876, v27, v7);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    (*(void (/*thiscall*/ **)(int *, char *))(**pThis_876 + 92))(*pThis_876, v21);  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
    fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
    v28 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v21);  // 调 演播层注册(槽号)
    v28 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
    ++pThis_876;
    v9 = v26 == 1;
    Block = nullptr;
    v23 = 0;
    v24 = 0;
    --v26;
  }
  while ( !v9 );
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v11 = v10 + 95;
  else
    v11 = v10 - 95;
  v27 = v11;
  v26 = sub_42FCB0(228);  // 调 CRT 一次性初始化
  v28 = 1;
  if ( v26 != 0 )
    v26 = sub_431860((char)"Monster/Golem/Particle/ani/STGolemFireSmoke.ani", 1);  // 调 动画件构造（资源 id 版）
  else
    v26 = 0;
  v28 = -1;
  v12 = (char *)sub_44B6C0(284);  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
  v13 = v12;
  v25 = v12;
  v28 = 2;
  if ( v12 != nullptr )  // 若 v12 有效（非空）
  {
    sub_44E0D0(v12, v26, 1);  // 调 CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)v13 = &CNRDPooledObject::`vftable';  // vftable 复位
  }
  else
  {
    v13 = nullptr;
  }
  fld_e292 = *(this + 29);  // this+116〔会话上下文〕
  v28 = -1;
  sub_45FE80(fld_e292, (int)v13, 2, 0, (int)v13, (int)this, 0);  // 调 对象注册
  v15 = *(uint32_t *)v13;
  v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  (*(void (/*thiscall*/ **)(char *, int))(v15 + 148))(v13, v16);  // 调用虚函数（虚表槽 +148）【推断: 同 vmt90 但不检查（直接写）】
  v17 = *(uint32_t *)v13;
  v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
  v19 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v18 + 110);  // 调用虚函数（虚表槽 +124）
  return (*(int (/*thiscall*/ **)(char *, int, int))(v17 + 112))(v13, v27, v19);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
}



// 埋地/起立 AI：GOLEM_DOWN 播报（this+8604 相位）
// ------------------------------------------------------------
// 0x5A7590 sub_5A7590 —— 埋地起立门（GOLEM_DOWN + 30009 发射）
// 相位 this+8604 为 0 且动作帧 +148==2 时置相位并（可行动时）本尊 vt+580 发射 30009
// （携 this[2161] 粒子句柄，末参 = vt+128(4,0,0,0) 基准 +55）、·0x5A73E0 补烟雾，
// 播报 GOLEM_DOWN
// ------------------------------------------------------------
char /*thiscall*/ sub_5A7590(uint32_t *this)  // 函数: 埋地起立门（GOLEM_DOWN + 30009 发射）
{
  int fld_e30; // eax  | +0x0078 → 动画/帧对象指针（全库通用：动画对象 = this+120）（CNGolemBronze）
  int v3; // edx
  int v4; // edi
  int v5; // eax

  LOBYTE(fld_e30) = *((uint8_t *)this + 8604);  // this+8604 = bAI8604
  if ( (uint8_t)fld_e30 == 0 )
  {
    fld_e30 = *(this + 30);  // this+120 = 动画对象指针
    if ( *(uint32_t *)(fld_e30 + 148) == 2 )
    {
      v3 = *this;
      *((uint8_t *)this + 8604) = 1;  // this+8604 = bAI8604
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v3 + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      {
        v4 = *this;
        v5 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 128))(this, 4, 0, 0, 0);  // 调用虚函数（虚表槽 +128）
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int))(v4 + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
          this,
          30009,
          0,
          *(this + 2161),  // this+8644 = 相位槽
          0,
          85,
          0,
          v5 + 55);
      }
      sub_5A73E0(this);  // 调 埋地烟火烟雾双发（STGolemFireSmoke.ani）
      LOBYTE(fld_e30) = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                     this,
                     "GOLEM_DOWN",  // 资源/动画 TAG GOLEM_DOWN
                     -1,
                     0,
                     0);
    }
  }
  return fld_e30;  // +0x0078 → 动画/帧对象指针（全库通用：动画对象 = this+120）（CNGolemBronze）
}



// 埋地/起立 AI：GOLEM_DOWN 播报（this+8604 相位, 68L）
// ------------------------------------------------------------
// 0x5A7610 sub_5A7610 —— 埋地起立门 · 群体版（GOLEM_DOWN + 30002 五连）
// 相位 this+8604 为 0 且动作帧 +148==3 且 vt+308 类判通过时：对 this[2161] 起连续五个
// 粒子句柄逐一备份本块 98 字节，以 rand%20 系数(0.80~0.99) 缩放 +15/+19 两坐标并存差到
// +63，+72 槽写 rand%71−35 抖动，再 vt+580 逐个发 30002（携该句柄，末参 = vt+128(4,…)
// 基准 +55），发完原样回写备份；随后 vt+208 以 this[1554] 首项绑定、·0x5A73E0 补烟雾
// 并播报 GOLEM_DOWN
// ------------------------------------------------------------
char /*thiscall*/ sub_5A7610(uint32_t **this)  // 函数: 埋地起立门 · 群体版（GOLEM_DOWN + 30002 五连）
{
  uint32_t **pThis; // ebx
  int fld_e30; // eax  | +0x0078 → 动画/帧对象指针（全库通用：动画对象 = this+120）（CNGolemSteel）
  const void **v3; // ebx
  double nRand; // st7
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // eax
  int v9; // [esp+8h] [ebp-70h]
  uint8_t v11[98]; // [esp+10h] [ebp-68h]

  pThis = this;
  LOBYTE(fld_e30) = *((uint8_t *)this + 8604);  // this+8604 = bAI8604
  if ( (uint8_t)fld_e30 == 0 )
  {
    fld_e30 = (int)*(this + 30);  // this+120 = 动画对象指针
    if ( *(uint32_t *)(fld_e30 + 148) == 3 )
    {
      if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
      {
        v3 = (const void **)(pThis + 2161);
        v9 = 5;
        do
        {
          qmemcpy(v11, *v3, sizeof(v11));  // 调 内存块拷贝(内联展开)
          nRand = (double)(100 - rand() % 20) * 0.0099999998;  // 调 以 16 位种子状态递推并返回 15 位结果
          *(uint32_t *)((char *)*v3 + 15) = (uint64_t)((double)*(int *)((char *)*v3 + 15) * nRand);
          *(uint32_t *)((char *)*v3 + 19) = (uint64_t)((double)*(int *)((char *)*v3 + 19) * nRand);
          *(uint32_t *)((char *)*v3 + 63) = *(uint32_t *)((char *)*v3 + 19) - *(uint32_t *)((char *)*v3 + 15);
          *((uint32_t *)*v3 + 18) = rand() % 71 - 35;  // 调 以 16 位种子状态递推并返回 15 位结果
          v5 = *this;
          v6 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*this)[32])(this, 4, 0, 0, 0);
          ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, const void *, uint32_t, int, uint32_t, int))v5[145])(
            this,
            30002,
            0,
            *v3,
            0,
            85,
            0,
            v6 + 55);
          v7 = v9;
          qmemcpy((void *)*v3++, v11, 98);  // 调 内存块拷贝(内联展开)
          --v9;
        }
        while ( v7 != 1 );
        pThis = this;
      }
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*pThis)[52])(pThis, *pThis[1554]);
      sub_5A73E0(pThis);  // 调 埋地烟火烟雾双发（STGolemFireSmoke.ani）
      LOBYTE(fld_e30) = ((int (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*pThis)[53])(  // 调 取 16 位值低 8 位
                     pThis,
                     "GOLEM_DOWN",  // 资源/动画 TAG GOLEM_DOWN
                     -1,
                     0,
                     0);
      *((uint8_t *)pThis + 8604) = 1;  // this+8604 狂暴段门
    }
  }
  return fld_e30;  // +0x0078 → 动画/帧对象指针（全库通用：动画对象 = this+120）（CNGolemSteel）
}



// SG 魔像装载：Monster/Golem/SG/{STHead,STLeftArm,STRightArm,STLeg}.equ 四部件
// ------------------------------------------------------------
// 0x5A7770 sub_5A7770 —— SG 魔像四件套装（.equ 挂装面 vt+784）
// 逐件 operator new(0x544) 经 ·0x4BA9E0 构造四 .equ：SG/STHead、STLeftArm、STRightArm、
// STLeg，按 臂/腿/左臂/头 顺序交 vt+784 挂装并对返回对象 vt+4(1) 启用
// ------------------------------------------------------------
int /*thiscall*/ sub_5A7770(void *this)  // 函数: SG 魔像四件套装（.equ 挂装面 vt+784）
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *v6; // ebx
  char *pMem4; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int result; // eax
  char *Block; // [esp+Ch] [ebp-14h]
  char *v13; // [esp+10h] [ebp-10h]

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    Block = sub_4BA9E0(pMem, "Monster/Golem/SG/STHead.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    Block = nullptr;
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v13 = sub_4BA9E0(pMem2, "Monster/Golem/SG/STLeftArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v13 = nullptr;
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v6 = sub_4BA9E0(pMem3, "Monster/Golem/SG/STRightArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v6 = nullptr;
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v3 = sub_4BA9E0(pMem4, "Monster/Golem/SG/STLeg.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);  // 调用虚函数（虚表槽 +784）
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v13);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);  // 调用虚函数（虚表槽 +4）
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, Block);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  return result;
}



// ST 魔像装载：Monster/Golem/ST/ST*.equ 四部件 + Particle/{STGolemBullet,STGolemFire,
//   STGolemHikari}.ptl 三粒子（99L）
// ------------------------------------------------------------
// 0x5A78E0 sub_5A78E0 —— ST 魔像四件套 + 三粒子装载（石魔像标准型）
// 四件 ST 部件（STHead/LeftArm/RightArm/Leg）同 ·0x5A7770 挂装；随后对 this[2161]
// 起连续五槽循环 vt+588 实体化 Particle/STGolemBullet.ptl 作弹药句柄；
// this[2166] 旧对象 vt+0(·,1) 释放后重建 Particle/STGolemFire.ptl，
// this[2167] 同法重建 Particle/STGolemHikari.ptl（大字符串走堆指针，否则内联缓冲）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A78E0(uint32_t *this)  // 函数: ST 魔像四件套 + 三粒子装载（石魔像标准型）
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *v6; // ebx
  char *pMem4; // eax
  int pObj4; // eax
  int pObj; // eax
  int pObj3; // eax
  int pObj2; // eax
  uint32_t *pThis_871; // edi
  int i; // ebx
  void (/*thiscall*/ ***fld_e2166)(uint32_t, int); // ecx
  int pThis_5B; // eax
  void (/*thiscall*/ ***fld_e2167)(uint32_t, int); // ecx
  int result; // eax
  char *Block; // [esp+10h] [ebp-14h]
  char *v19; // [esp+14h] [ebp-10h]

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    Block = sub_4BA9E0(pMem, "Monster/Golem/ST/STHead.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    Block = nullptr;
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v19 = sub_4BA9E0(pMem2, "Monster/Golem/ST/STLeftArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v19 = nullptr;
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v6 = sub_4BA9E0(pMem3, "Monster/Golem/ST/STRightArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v6 = nullptr;
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v3 = sub_4BA9E0(pMem4, "Monster/Golem/ST/STLeg.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);  // 调用虚函数（虚表槽 +784）
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调用虚函数（虚表槽 +4）
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调用虚函数（虚表槽 +4）
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v19);  // 调用虚函数（虚表槽 +784）
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调用虚函数（虚表槽 +4）
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, Block);  // 调用虚函数（虚表槽 +784）
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调用虚函数（虚表槽 +4）
  pThis_871 = this + 2161;
  for ( i = 5; i != 0; --i )  // 循环：i 从 5 递减到 0
    *pThis_871++ = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/STGolemBullet.ptl");  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
  fld_e2166 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2166);  // this+8664 = 子类 AI 槽
  if ( fld_e2166 != nullptr )  // 若 fld_e2166 有效（非空）
  {
    (**fld_e2166)(fld_e2166, 1);  // 调 fld_e2166 的虚函数（vt+0）
    *(this + 2166) = 0;  // this+8664 = 子类 AI 槽
  }
  if ( operator new(0x12Cu) != nullptr )  // operator new 分配 300 字节
  {
    if ( *(this + 96) < 0x10u )  // this+384 = 动画件名 SSO 容量判据
      pThis_5B = sub_4C3640(this + 91, "Particle/STGolemFire.ptl", this);  // 资源路径 Particle/STGolemFire.ptl
    else
      pThis_5B = sub_4C3640(*(this + 91), "Particle/STGolemFire.ptl", this);  // this+364 = 动画件名缓冲 SSO 内联首址
  }
  else
  {
    pThis_5B = 0;
  }
  fld_e2167 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2167);  // this+8668 = nCool8668
  *(this + 2166) = pThis_5B;  // this+8664 = 子类 AI 槽
  if ( fld_e2167 != nullptr )  // 若 fld_e2167 有效（非空）
  {
    (**fld_e2167)(fld_e2167, 1);  // 调 fld_e2167 的虚函数（vt+0）
    *(this + 2167) = 0;  // this+8668 = nCool8668
  }
  if ( operator new(0x12Cu) != nullptr )  // operator new 分配 300 字节
  {
    if ( *(this + 96) < 0x10u )  // this+384 = 动画件名 SSO 容量判据
      result = sub_4C3640(this + 91, "Particle/STGolemHikari.ptl", this);  // 资源路径 Particle/STGolemHikari.ptl
    else
      result = sub_4C3640(*(this + 91), "Particle/STGolemHikari.ptl", this);  // this+364 = 动画件名缓冲 SSO 内联首址
  }
  else
  {
    result = 0;
  }
  *(this + 2167) = result;  // this+8668 = nCool8668
  return result;
}



// CL 魔像装载：Monster/Golem/CL/ST*.equ 四部件
// ------------------------------------------------------------
// 0x5A7B50 sub_5A7B50 —— CL 魔像四件套装
// 与 ·0x5A7770 同构（差异：四 .equ 路径改 CL/ 分色：CL/STHead、STLeftArm、STRightArm、STLeg）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A7B50(void *this)  // 函数: CL 魔像四件套装
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *v6; // ebx
  char *pMem4; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int result; // eax
  char *v12; // [esp+Ch] [ebp-14h]
  char *v13; // [esp+10h] [ebp-10h]

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v12 = sub_4BA9E0(pMem, "Monster/Golem/CL/STHead.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v12 = nullptr;
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v13 = sub_4BA9E0(pMem2, "Monster/Golem/CL/STLeftArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v13 = nullptr;
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v6 = sub_4BA9E0(pMem3, "Monster/Golem/CL/STRightArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v6 = nullptr;
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v3 = sub_4BA9E0(pMem4, "Monster/Golem/CL/STLeg.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);  // 调用虚函数（虚表槽 +784）
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v13);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);  // 调用虚函数（虚表槽 +4）
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v12);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  return result;
}



// GD 魔像装载：Monster/Golem/GD/ST*.equ 四部件
// ------------------------------------------------------------
// 0x5A7CC0 sub_5A7CC0 —— GD 魔像四件套装
// 与 ·0x5A7770 同构（差异：四 .equ 路径改 GD/ 分色：GD/STHead、STLeftArm、STRightArm、STLeg）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A7CC0(void *this)  // 函数: GD 魔像四件套装
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *v6; // ebx
  char *pMem4; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int result; // eax
  char *v12; // [esp+Ch] [ebp-14h]
  char *v13; // [esp+10h] [ebp-10h]

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v12 = sub_4BA9E0(pMem, "Monster/Golem/GD/STHead.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v12 = nullptr;
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v13 = sub_4BA9E0(pMem2, "Monster/Golem/GD/STLeftArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v13 = nullptr;
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v6 = sub_4BA9E0(pMem3, "Monster/Golem/GD/STRightArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v6 = nullptr;
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v3 = sub_4BA9E0(pMem4, "Monster/Golem/GD/STLeg.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);  // 调用虚函数（虚表槽 +784）
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v13);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);  // 调用虚函数（虚表槽 +4）
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v12);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  return result;
}



// BR 魔像装载：Monster/Golem/BR/ST*.equ 四部件 + Particle/{BRGolemBullet,STGolemFire,
//   STGolemHikari}.ptl（97L）
// ------------------------------------------------------------
// 0x5A7E30 sub_5A7E30 —— BR 魔像四件套 + 三粒子（红/铜分色型）
// 与 ·0x5A78E0 同构（差异：部件改 BR/ 路径且弹药粒子为 Particle/BRGolemBullet.ptl
// 写单槽 this[2161]；开火/光柱粒子仍复用 ST 的 STGolemFire.ptl / STGolemHikari.ptl）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A7E30(uint32_t *this)  // 函数: BR 魔像四件套 + 三粒子（红/铜分色型）
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *v6; // ebx
  char *pMem4; // eax
  int pObj4; // eax
  int pObj; // eax
  int pObj3; // eax
  int pObj2; // eax
  int v12; // eax
  void (/*thiscall*/ ***fld_e2166)(uint32_t, int); // ecx
  int pThis_5B; // eax
  void (/*thiscall*/ ***fld_e2167)(uint32_t, int); // ecx
  int result; // eax
  char *v17; // [esp+10h] [ebp-14h]
  char *v18; // [esp+14h] [ebp-10h]

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v17 = sub_4BA9E0(pMem, "Monster/Golem/BR/STHead.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v17 = nullptr;
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v18 = sub_4BA9E0(pMem2, "Monster/Golem/BR/STLeftArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v18 = nullptr;
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v6 = sub_4BA9E0(pMem3, "Monster/Golem/BR/STRightArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v6 = nullptr;
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v3 = sub_4BA9E0(pMem4, "Monster/Golem/BR/STLeg.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);  // 调用虚函数（虚表槽 +784）
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);  // 调用虚函数（虚表槽 +4）
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调用虚函数（虚表槽 +4）
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);  // 调用虚函数（虚表槽 +784）
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调用虚函数（虚表槽 +4）
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v17);  // 调用虚函数（虚表槽 +784）
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调用虚函数（虚表槽 +4）
  v12 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/BRGolemBullet.ptl");  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
  fld_e2166 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2166);  // this+8664 = 子类 AI 槽
  *(this + 2161) = v12;  // this+8644 = 相位槽
  if ( fld_e2166 != nullptr )  // 若 fld_e2166 有效（非空）
  {
    (**fld_e2166)(fld_e2166, 1);  // 调 fld_e2166 的虚函数（vt+0）
    *(this + 2166) = 0;  // this+8664 = 子类 AI 槽
  }
  if ( operator new(0x12Cu) != nullptr )  // operator new 分配 300 字节
  {
    if ( *(this + 96) < 0x10u )  // this+384 = 动画件名 SSO 容量判据
      pThis_5B = sub_4C3640(this + 91, "Particle/STGolemFire.ptl", this);  // 资源路径 Particle/STGolemFire.ptl
    else
      pThis_5B = sub_4C3640(*(this + 91), "Particle/STGolemFire.ptl", this);  // this+364 = 动画件名缓冲 SSO 内联首址
  }
  else
  {
    pThis_5B = 0;
  }
  fld_e2167 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2167);  // this+8668 = nCool8668
  *(this + 2166) = pThis_5B;  // this+8664 = 子类 AI 槽
  if ( fld_e2167 != nullptr )  // 若 fld_e2167 有效（非空）
  {
    (**fld_e2167)(fld_e2167, 1);  // 调 fld_e2167 的虚函数（vt+0）
    *(this + 2167) = 0;  // this+8668 = nCool8668
  }
  if ( operator new(0x12Cu) != nullptr )  // operator new 分配 300 字节
  {
    if ( *(this + 96) < 0x10u )  // this+384 = 动画件名 SSO 容量判据
      result = sub_4C3640(this + 91, "Particle/STGolemHikari.ptl", this);  // 资源路径 Particle/STGolemHikari.ptl
    else
      result = sub_4C3640(*(this + 91), "Particle/STGolemHikari.ptl", this);  // this+364 = 动画件名缓冲 SSO 内联首址
  }
  else
  {
    result = 0;
  }
  *(this + 2167) = result;  // this+8668 = nCool8668
  return result;
}



// GD/PT 魔像装载：Monster/Golem/GD/{PTHead,PTLeftArm,PTRightArm,PTLeg,PTHorn}.equ 五部件（71L）
// ------------------------------------------------------------
// 0x5A80A0 sub_5A80A0 —— GD/PT 五件套 + 部件缩放/攻击系数（1.5 倍档）
// 五 .equ（GD/PTHead、PTLeftArm、PTRightArm、PTLeg、PTHorn 头角件）按 臂/腿/左臂/头/角
// 顺序 vt+784 挂装；随后 vt+688 姿态刷新，并以 ·0x4EB2C0(1.5) 与五次 ·0x4EB6A0(1.5)
// 把部件缩放与攻击系数升至 1.5 倍（PT 强化型的体型增幅【推断】）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A80A0(void *this)  // 函数: GD/PT 五件套 + 部件缩放/攻击系数（1.5 倍档）
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *pMem4; // eax
  char *pMem5; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int pThis_3104; // eax
  int pThis_3105; // eax
  char *Block; // [esp+10h] [ebp-1Ch]
  char *v15; // [esp+14h] [ebp-18h]
  char *v16; // [esp+18h] [ebp-14h]
  char *v17; // [esp+1Ch] [ebp-10h]

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  v3 = nullptr;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    Block = sub_4BA9E0(pMem, "Monster/Golem/GD/PTHead.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    Block = nullptr;
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v15 = sub_4BA9E0(pMem2, "Monster/Golem/GD/PTLeftArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v15 = nullptr;
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v17 = sub_4BA9E0(pMem3, "Monster/Golem/GD/PTRightArm.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v17 = nullptr;
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v16 = sub_4BA9E0(pMem4, "Monster/Golem/GD/PTLeg.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v16 = nullptr;
  pMem5 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    v3 = sub_4BA9E0(pMem5, "Monster/Golem/GD/PTHorn.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v17);  // 调用虚函数（虚表槽 +784）
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v16);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v15);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, Block);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);  // 调用虚函数（虚表槽 +4）
  pThis_3105 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3105 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3105 + 4))(pThis_3105, 1);  // 调用虚函数（虚表槽 +4）
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 688))(this);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
  sub_4EB2C0(1.5);  // 调 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  sub_4EB6A0(1.5);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(1.5);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(1.5);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  sub_4EB6A0(1.5);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
  return sub_4EB6A0(1.5);  // 调 this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
}



// ============================================================
// 【分区 9】人偶师 DollMaster（0x5A82B0-0x5AC1F0）
// 证据：DOLL_SUMMON/COMMAND/FLOAT_LOOP/CAST/DMG/DIE、Monster/DollMaster/DollMaster.equ、
//       R_DOLL_AMB、Particle/StoneBubble.ptl 石泡、JEWEL_HIT/SWING_SHORT/STONE_DMG、
//       STONE_SET、B_MASTERDOGRY_01 登场曲、+6556 态 14 门（0x5A9100）

// 子类扩展字段复位（this+8600..8668, 21L）
// ------------------------------------------------------------
// 0x5A82B0 sub_5A82B0 —— 人偶师子类字段复位（this+8600..8668）
// 子类 AI 状态区十二槽清零；this+8636 置 -1（无效索引）、this+8656 字节清 0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A82B0(int this)  // 函数: 人偶师子类字段复位（this+8600..8668）
{
  *(uint8_t *)(this + 8620) = 0;  // this+8620 警报/唤醒标志
  *(uint32_t *)(this + 8616) = 0;  // this+8616 【推断】钻地相位字节1
  *(uint32_t *)(this + 8612) = 0;  // this+8612 锁定/相位字节 A
  *(uint32_t *)(this + 8608) = 0;  // this+8608 骑乘/骑手槽
  *(uint32_t *)(this + 8604) = 0;  // this+8604 子类 AI 状态槽/相位门
  *(uint32_t *)(this + 8600) = 0;  // this+8600 距主人距离阈值
  *(uint32_t *)(this + 8624) = 0;  // this+8624 【推断】子类AI槽
  *(uint32_t *)(this + 8636) = -1;  // this+8636 人偶目标槽
  *(uint32_t *)(this + 8640) = 0;  // this+8640 【推断】出土相位槽
  *(uint8_t *)(this + 8656) = 0;  // this+8656 【推断】子类AI标记字节
  *(uint32_t *)(this + 8668) = 0;  // this+8668 人偶行为模式
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8300 sub_5A8300 —— this+2163 槽对象释放
// 槽内对象存在时经 vt+0(·,1) 释放后清槽（与 ·0x5A5BF0 同型，单槽版）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8300(uint32_t *this)  // 函数: this+2163 槽对象释放
{
  int (/*thiscall*/ ***fld_e2163)(uint32_t, int); // ecx
  int result; // eax

  fld_e2163 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2163);  // this+8652 = 相位槽
  if ( fld_e2163 != nullptr )  // 若 fld_e2163 有效（非空）
    result = (**fld_e2163)(fld_e2163, 1);  // 调 fld_e2163 的虚函数（vt+0）
  *(this + 2163) = 0;  // this+8652 = 相位槽
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8320 sub_5A8320 —— 对象消亡回调（引用清理）
// 先走 ·0x4D9170 对象移除引用清理；被移除对象命中槽 this+2156 即清槽；若移除对象正是
// 本尊，经 vt+216 停循环音 19804【推断：人偶/随从消亡联动】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8320(uint32_t *this, uint32_t *uArg2)  // 函数: 对象消亡回调（引用清理）
{
  int result; // eax

  result = sub_4D9170(uArg2);  // 调 消亡通知
  if ( uArg2 == (uint32_t *)*(this + 2156) )  // this+8624 = uAI8624
    *(this + 2156) = 0;  // this+8624 = uAI8624
  if ( uArg2 == this )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 19804);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
  return result;
}



// 【vmt200 命中处理器覆写】人偶系小型覆写（17L；虚表 0x6DBE6C/0x6DC394/0x6DC8BC/0x6DCDE4/0x6DD30C/0x6DD834
//   六张 +512 槽共享）
// ------------------------------------------------------------
// 0x5A8360 sub_5A8360 —— vmt200 命中覆写 · 人偶系小型（17L）
// 前置 ·0x4DA3B0 命中包分发；vt+724 非冻结时若槽 this+2156 非空【推断：随从/跟随对象槽，
// 同区分区内另作 vt+304 存在性判与句柄对打包】、该对象状态 +7148 非 9（特殊态）、目标
// this+1814 非空且距上次时间戳 this[2151]+this[2157] 已过（·0x699000 clock_now 门）
// → vt+1056 触发指令；末段 1908==0 且 1909!=0 时 50% 掷点调 ·0x4DC730 聚合广播（type 29）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8360(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数: vmt200 命中覆写 · 人偶系小型（17L）
{
  int v5; // edi
  int uPatrolGate; // eax  | +0x21B0 → 子类槽〔5A82B0 复位〕（CNDollMaster）

  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);  // 调 ★ 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
  {
    uPatrolGate = *(this + 2156);  // this+8624 = uAI8624
    if ( uPatrolGate != 0
      && *(uint32_t *)(uPatrolGate + 7148) != 9
      && *(this + 1814) != 0  // this+7256 = 光环对象槽
      && sub_699000((int)(this + 9)) > (unsigned int)(*(this + 2151) + *(this + 2157)) )  // 【clock_now(clk)】
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1056))(this);  // 调用虚函数（虚表槽 +1056）
    }
  }
  if ( *(this + 1908) == 0 && *(this + 1909) != 0 && rand() % 100 < 50 )  // 调 以 16 位种子状态递推并返回 15 位结果
    sub_4DC730(this);  // 调 同队怪物聚合广播（包 type 29）
  return v5;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8400 sub_5A8400 —— 目标姿态条件转发（vt+1308 收尾）
// 来参非空且其时目标体 vt+576 判定体查询非 0（目标仍受击/存活）时调 vt+1308【推断：人偶回收门】
// ------------------------------------------------------------
void /*thiscall*/ sub_5A8400(void *this, int nArg2)  // 函数: 目标姿态条件转发（vt+1308 收尾）
{
  if ( nArg2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )  // 调用虚函数（虚表槽 +576）
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1308))(this);  // 调用虚函数（虚表槽 +1308）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A8430 sub_5A8430 —— 判定体攻击请求三连（vt+152 → vt+376 → vt+592）
// 取 vt+672(0) 速度容器首值作请求参数、vt+152 建攻击请求（判定宽度 0xFFFF、无攻击号）
// → vt+376 以 (nArg2, nArg3) 坐标施放 → vt+592 施放结果绑 into 目标槽 this+2152
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8430(uint32_t *this, int nArg2, int nArg3)  // 函数: 判定体攻击请求三连（vt+152 → vt+376 → vt+592）
{
  int v4; // edi
  uint32_t *v5; // ebx
  int v6; // eax
  int v7; // eax

  v4 = *this;
  v5 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(v4 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
         this,
         2,
         0,
         0,
         0xFFFF,
         0,
         0,
         0,
         0);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int))(*this + 376))(this, *v5, nArg2, nArg3, 0, v6);  // 调用虚函数（虚表槽 +376）
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(v4 + 592))(this, *(this + 2152), v7);  // this+8608 = uAI8608
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8490 sub_5A8490 —— 感知半径解算（有对象取距离，无对象取视野+100）
// 槽 this+2156 非空时经 vt+8(this, nArg2, 0) 取距离值，否则返回 ·0x4D8FE0 视野值加 100
// （盲眼时视野为 10）【推断：槽语义同 ·0x5A8360】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8490(uint32_t *this, int nArg2)  // 函数: 感知半径解算（有对象取距离，无对象取视野+100）
{
  if ( *(this + 2156) != 0 )  // this+8624 = uAI8624
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, nArg2, 0);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
  else
    return sub_4D8FE0(this) + 100;  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
}



// AI 相位辅助（48L）
// ------------------------------------------------------------
// 0x5A84C0 sub_5A84C0 —— 指令包广播（会话管理器 dword_8F8520 · type 29 + 字段 11）
// 槽 this+2156 经其 vt+304 存在性确认非 0 时组包：vt+8(29,2) 开包 → 依序写入该对象
// vt+48/vt+52 句柄对、其 vt+304 返回体的 vt+52 句柄、常量 11、目标 this+1814 的
// vt+48/vt+52 句柄对 → vt+60(1,−1) 收尾发包【推断：人偶/随从指令同步包】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A84C0(uint32_t **this)  // 函数: 指令包广播（会话管理器 dword_8F8520 · type 29 + 字段 11）
{
  int result; // eax
  int v3; // edi
  int fld_e2156; // eax
  int v5; // edi
  int fld_e21562; // eax
  int fld_e21563; // eax
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int fld_e1814; // eax
  int fld_e18142; // ecx
  int v13; // esi
  int v14; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 304))(*(this + 2156));  // this+8624 = uAI8624
  if ( result != 0 )  // 若结果非 0（成功）
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
    v3 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
    fld_e2156 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 48))(*(this + 2156));  // this+8624 = uAI8624
    (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, fld_e2156);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
    v5 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
    fld_e21562 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 52))(*(this + 2156));  // this+8624 = uAI8624
    (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, fld_e21562);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
    fld_e21563 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 304))(*(this + 2156));  // this+8624 = uAI8624
    v8 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21563 + 52))(fld_e21563);  // 调用虚函数（虚表槽 +52）
    (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 11);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
    v10 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
    fld_e1814 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1814) + 48))(*(this + 1814));  // this+7256 = 光环对象槽
    (*(void (/*thiscall*/ **)(int, int))(v10 + 36))(dword_8F8520, fld_e1814);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
    fld_e18142 = (int)*(this + 1814);  // this+7256 = 光环对象槽
    v13 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18142 + 52))(fld_e18142);  // 调用虚函数（虚表槽 +52）
    (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
    return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
  }
  return result;
}



// 技能播报：STONE_SET（石块放置, 37L）
// ------------------------------------------------------------
// 0x5A85B0 sub_5A85B0
// ------------------------------------------------------------
// positive sp value has been detected, the output may be wrong!
int /*usercall*/ sub_5A85B0@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>)  // 实现：技能播报：STONE_SET（石块放置, 37L）
{
  int v3; // edi
  int nRand; // eax
  int pObj; // ecx
  int v6; // edi
  int nRand2; // eax
  int v8; // edx
  int v10; // [esp+4h] [ebp-8h] BYREF
  int v11; // [esp+8h] [ebp-4h] BYREF
  int savedregs; // [esp+Ch] [ebp+0h]

  if ( pDwArg1[1813] != 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  {
    v3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[1813] + 120))(pDwArg1[1813], nArg2);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
    pObj = pDwArg1[1813];
    v11 = v3 + nRand % 180 - 90;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 调用虚函数（虚表槽 +124）
    nRand2 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
    savedregs = 10;
    v11 = 0;
    v10 = 300;
    v8 = *pDwArg1;
    v10 = v6 + nRand2 % 180 - 90;
    (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, int))(v8 + 140))(pDwArg1, &v11, &v10, 0, v10);  // 调用虚函数（虚表槽 +140）【推断: ★ 螺旋式寻找空位（同心方环，从 (a4,a5) 起向外扫）】
    sub_4E4A50(pDwArg1, 30069, pDwArg1[2161], v11, v10, 0, 4, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
  }
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "STONE_SET", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A8680 sub_5A8680 —— 距离档写入（this+2167 = 0/1/2 三档）
// 有目标 this+1813 时：vt+8 取距离 ÷ ·0x4D8FE0 视野 ×100 得占比，>50 写 2、10..50 写 1、
// ≤10 写 0；无目标直接写 2（远档）【推断：近/中/远行为档，供 ·0x5A84C0 指令包消费】
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8680(uint32_t *this)  // 函数: 距离档写入（this+2167 = 0/1/2 三档）
{
  uint64_t v2; // rax
  float v4; // [esp+4h] [ebp-8h]

  LODWORD(v2) = *(this + 1813);  // this+7252 = pTarget7252
  if ( (uint32_t)v2 != 0 )
  {
    v4 = (float)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 8))(this, v2, 0);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
    v2 = (uint64_t)(v4 / (double)sub_4D8FE0(this) * 100.0);  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
    if ( (int)v2 > 10 )
      *(this + 2167) = ((int)v2 > 50) + 1;  // this+8668 = nCool8668
    else
      *(this + 2167) = 0;  // this+8668 = nCool8668
  }
  else
  {
    *(this + 2167) = 2;  // this+8668 = nCool8668
  }
  return v2;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A8700 sub_5A8700 —— 同构 ·0x5A5E90（差异：整面清 this+7531..7596 分身/攻击
// 参数面后缺省段选 this+7580 置 2，而 ·0x5A5E90 置 1）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8700(int this, int nArg2, int nArg3)  // 函数: 同构 ·0x5A5E90（差异：整面清 this+7531..7596 分身/攻击
{
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
  *(uint32_t *)(this + 7572) = 0;  // this+7572 【推断】模式 2 档
  *(uint32_t *)(this + 7568) = 0;  // this+7568 【推断】激活/模式槽
  *(uint32_t *)(this + 7564) = 0;  // this+7564 【推断】形态/模式槽
  *(uint32_t *)(this + 7588) = 0;  // this+7588 【推断】形态槽
  *(uint32_t *)(this + 7584) = 0;  // this+7584 【推断】形态槽
  *(uint32_t *)(this + 7580) = 0;  // this+7580 【推断】攻击面门字节
  *(uint32_t *)(this + 7576) = 0;  // this+7576 相位槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 【推断】段号横向偏置
  *(uint32_t *)(this + 7580) = 2;  // this+7580 【推断】攻击面门字节
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A8790 sub_5A8790 —— 分身/攻击参数面整体复位（this+7531..7596 清零）
// this+7531..7555 逐字节、this+7535..7551 与 7564..7596 逐字清零，末置 this+7576 = 2
// 【推断】this+7576 为相位槽（2 = 复位待命），与前一函数置 this+7580 = 2 构成成对复位
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8790(int this, int nArg2, int nArg3)  // 函数: 分身/攻击参数面整体复位（this+7531..7596 清零）
{
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
  *(uint32_t *)(this + 7572) = 0;  // this+7572 【推断】模式 2 档
  *(uint32_t *)(this + 7568) = 0;  // this+7568 【推断】激活/模式槽
  *(uint32_t *)(this + 7564) = 0;  // this+7564 【推断】形态/模式槽
  *(uint32_t *)(this + 7588) = 0;  // this+7588 【推断】形态槽
  *(uint32_t *)(this + 7584) = 0;  // this+7584 【推断】形态槽
  *(uint32_t *)(this + 7580) = 0;  // this+7580 【推断】攻击面门字节
  *(uint32_t *)(this + 7576) = 0;  // this+7576 相位槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 【推断】段号横向偏置
  *(uint32_t *)(this + 7576) = 2;  // this+7576 相位槽
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A8820 sub_5A8820 —— 关联对象 30025 号效果请求（挂件/标记体定位）
// 若 this+7252 关联对象非空且本对象 vt+308 行动校验通过，取关联体 vt+120/vt+124
// （世界坐标对）与本对象 vt+152，经 ·0x4E4A50 发起编号 30025 的效果/技能请求
// 【推断】30025 为分体标记特效编号，this+7252 = 关联对象指针槽（与 7260 事件槽相邻）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8820(int *this)  // 函数: 关联对象 30025 号效果请求（挂件/标记体定位）
{
  int result; // eax
  int fld_e1813; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int fld_e18132; // ebx  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int v5; // eax

  result = *(this + 1813);  // this+7252 = pTarget7252
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    if ( (uint8_t)result != 0 )
    {
      fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252 = pTarget7252
      fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));  // this+7252 = pTarget7252
      v5 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      return sub_4E4A50(this, 30025, 1, fld_e1813, fld_e18132, 0, v5, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    }
  }
  return result;
}



// 召唤 AI：DOLL_SUMMON 播报（人偶召唤, 33L）
// ------------------------------------------------------------
// 0x5A8880 sub_5A8880 —— 召唤落点解算 + DOLL_SUMMON 播报
// 以 vt+152（朝向）取 ±75 偏移贴到 vt+120（x）上，·0x499560 在 (x,y) 半径 3 内解算
// 合法落点；命中则 ·0x5A8430 追加判定体攻击请求三连（vt+152 → vt+376 链路），
// 并经 vt+212（播报槽）喊出字符串证据 DOLL_SUMMON
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8880(uint32_t *this)  // 函数: 召唤落点解算 + DOLL_SUMMON 播报
{
  int v2; // edi
  int v3; // edi
  int v4; // eax
  int result; // eax
  int v6; // [esp+8h] [ebp-8h] BYREF
  int v7; // [esp+Ch] [ebp-4h] BYREF

  v2 = 75;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v2 = -75;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + v2;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
  result = sub_499560(this, &v6, &v7, v3, v4, 3);  // 调 重试式预约（延迟 30 起每次 +10，最多 nArg6 次）
  if ( (uint8_t)result != 0 )
  {
    sub_5A8430(this, v6, v7);  // 调 判定体攻击请求三连（vt+152 → vt+376 → vt+592）
    return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
             this,
             "DOLL_SUMMON",  // 资源/动画 TAG DOLL_SUMMON
             -1,
             0,
             0);
  }
  return result;
}



// 指挥 AI：DOLL_COMMAND 播报（sub_699000 时钟门, this+8628 相位）
// ------------------------------------------------------------
// 0x5A8900 sub_5A8900 —— 指令下发（DOLL_COMMAND 播报 + 时长置位）
// vt+308 行动校验通过则 ·0x5A84C0 指令包广播（会话管理器 dword_8F8520），随后
// ·0x4D82D0 弹头顶气泡 Command.ani；写 this+8628 = clock_now（子类AI状态区计时戳，
// 与 ·0x5A8C70 的 500ms 门同区）并清 this+7256，末经 vt+212 喊 DOLL_COMMAND
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8900(int this)  // 函数: 指令下发（DOLL_COMMAND 播报 + 时长置位）
{
  int pThis_24; // eax
  uint32_t *v3; // edx

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    sub_5A84C0((uint32_t **)this);  // 调 指令包广播（会话管理器 dword_8F8520 · type 29 + 字段 11）
  sub_4D82D0(0, 0);  // 头顶气泡 Command.ani（a2/a3 = 定位偏移）
  pThis_24 = sub_699000(this + 36);  // 【clock_now(clk)】
  v3 = *(uint32_t **)this;
  *(uint32_t *)(this + 8628) = pThis_24;  // this+8628 指挥计时戳
  *(uint32_t *)(this + 7256) = 0;  // this+7256 光环对象槽
  return ((int (/*thiscall*/ *)(int, const char *, int, uint32_t, uint32_t))v3[53])(this, "DOLL_COMMAND", -1, 0, 0);  // 资源/动画 TAG DOLL_COMMAND
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8950 sub_5A8950 —— CNChangeDamageBonusRate 构造器（伤害加成率修饰器）
// 基类初始化 ·0x4B1030 后挂本类 vftable，再经 ·0x64C9F0 / ·0x64CA10 战斗光环查询族
// 写入参数（pszArg2/nArg3/nArg4/nArg5/pszArg6 透传）；与 ·0x5A5CD0 伤害修正 1.5/0.6/0.7 族同源
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5A8950(uint32_t *this, char pszArg2, int nArg3, int nArg4, int nArg5, char pszArg6)  // 函数: CNChangeDamageBonusRate 构造器（伤害加成率修饰器）
{
  sub_4B1030();  // 调 IRDAppendage 基类构造
  *this = &CNChangeDamageBonusRate::`vftable';  // vftable 复位
  sub_64C9F0(this);  // 调 战斗光环查询（15 行）
  sub_64CA10(pszArg2, nArg3, nArg4, nArg5, pszArg6);  // 调 战斗光环查询 2（15 行）
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A89C0 sub_5A89C0 —— CNChangeDamageBonusRate 删除器（标量析构）
// 先经 ·0x5A89F0 走析构链，pszArg2 位 0 置位时 j__free(Block) 释放堆块
// ------------------------------------------------------------
void */*thiscall*/ sub_5A89C0(void *Block, char pszArg2)  // 函数: CNChangeDamageBonusRate 删除器（标量析构）
{
  sub_5A89F0();  // 调 CNChangeDamageBonusRate 析构本体（vftable 逐级回退）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A89F0 sub_5A89F0 —— CNChangeDamageBonusRate 析构本体（vftable 逐级回退）
// CNChangeDamageBonusRate → IRDAppendage → nengine::IObject 三段 vftable 回退，
// 中段走 ·0x64CA40 战斗光环注销，末段 ·0x5F6640 基类析构 + this+12 清零
// ------------------------------------------------------------
int /*thiscall*/ sub_5A89F0(uint32_t *this)  // 函数: CNChangeDamageBonusRate 析构本体（vftable 逐级回退）
{
  int result; // eax

  *this = &CNChangeDamageBonusRate::`vftable';  // vftable 复位
  sub_64CA40();  // 调 战斗光环查询 3（17 行）
  *this = &IRDAppendage::`vftable';  // vftable 复位
  result = sub_5F6640(this);  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // this+8 = 技能槽记录首字
  *((uint8_t *)this + 12) = 0;  // this+12 = 技能槽记录次字
  return result;
}



// RTTI cast 大型 AI（101L）
// ------------------------------------------------------------
// 0x5A8A50 sub_5A8A50 —— 事件包分派：伤害加成率/HP 修改器挂装
// ·0x4DC630 关卡/交互事件包处理返回包型：-1 无包直接返回；2 = 从会话管理器
// dword_8F8520（vt+76 读 u16、vt+80 读数据块）循环读配对坐标对，·0x45EBE0 取对象后
// RTDynamicCast 成 IRDActiveObject，new 0x64 字节经 ·0x5A8950（CNChangeDamageBonusRate）
// 构造并 vt+56 挂到目标；3 = 单目标 + ·0x4D6810 构造 CNChangeHp（500ms 计时，研究 §2⑦）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8A50(void *this)  // 函数: 事件包分派：伤害加成率/HP 修改器挂装
{
  int result; // eax
  int v3; // ebx
  int v4; // eax
  int v5; // esi
  int *v6; // eax
  int v7; // edx
  int v8; // ebx
  int v9; // eax
  int v10; // esi
  int *v11; // eax
  int v12; // edx
  float v13; // [esp+Ch] [ebp-48h]
  void *Block; // [esp+28h] [ebp-2Ch] BYREF
  void *pMem; // [esp+2Ch] [ebp-28h] BYREF
  uint16_t v16; // [esp+32h] [ebp-22h] BYREF
  uint16_t v17; // [esp+34h] [ebp-20h] BYREF
  uint16_t v18; // [esp+38h] [ebp-1Ch] BYREF
  int v19; // [esp+3Ch] [ebp-18h] BYREF
  uint16_t v20; // [esp+40h] [ebp-14h] BYREF
  uint16_t v21; // [esp+44h] [ebp-10h] BYREF
  int v22; // [esp+50h] [ebp-4h]

  result = sub_4DC630();  // 调 关卡/交互事件包处理（关联对象 this+7260 校验）
  v3 = result;
  v19 = result;
  if ( result == -1 )
    return result;
  if ( result != 3 )
  {
    if ( result == 2 )
    {
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v21);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v16);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &Block);  // 调用虚函数（虚表槽 +80）
      v8 = 0;
      if ( v21 != 0 )
      {
        do
        {
          (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v17);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
          (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v18);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
          v9 = sub_45EBE0(v17, v18);  // 调 存 id 对 → 对象查找
          v10 = __RTDynamicCast(v9, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
          if ( v10 != 0 )
          {
            pMem = operator new(0x64u);  // operator new 分配 100 字节
            v22 = 1;
            if ( pMem != nullptr )  // 若 pMem 有效（非空）
              v11 = (int *)sub_5A8950(1, 3, v16, Block, 1);  // 调 CNChangeDamageBonusRate 构造器（伤害加成率修饰器）
            else
              v11 = nullptr;
            v12 = *v11;
            v22 = -1;
            (*(void (/*thiscall*/ **)(int *, int, void *, int, uint32_t, uint32_t, int))(v12 + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
              v11,
              v10,
              this,
              1,
              0,
              0,
              -1);
          }
          ++v8;
        }
        while ( v8 < v21 );
      }
      return v19;
    }
    return v3;
  }
  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, (char *)&v19 + 2);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v20);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &pMem);  // 调用虚函数（虚表槽 +80）
  v4 = sub_45EBE0(HIWORD(v19), v20);  // 调 取 32 位值高 16 位
  v5 = __RTDynamicCast(v4, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
  if ( v5 == 0 )
    return v3;
  Block = operator new(0x80u);  // operator new 分配 128 字节
  v22 = 0;
  if ( Block != nullptr )  // 若 Block 有效（非空）
  {
    v13 = (float)(unsigned int)pMem;
    v6 = (int *)sub_4D6810(LODWORD(v13), 500, 1, 1);  // 调 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
  }
  else
  {
    v6 = nullptr;
  }
  v7 = *v6;
  v22 = -1;
  (*(void (/*thiscall*/ **)(int *, int, void *, uint32_t, uint32_t, uint32_t, int))(v7 + 56))(v6, v5, this, 0, 0, 0, -1);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
  return 3;
}



// RTTI cast + 时钟门 AI（80L）
// ------------------------------------------------------------
// 0x5A8C70 sub_5A8C70 —— 同族侦测 + 惊叹气泡（500ms 时钟门, this+2165 戳）
// this+2165（clock_now 戳）500ms 门；扫 this+29 对象数组，vt+40(obj,529) 类型校验 +
// RTDynamicCast IRDMonster 后按 vt+340 判族（31..35 或 3001）；同队（vt+376 相等）且
// vt+1244 判定通过者成为目标：目标变更时 ·0x4D83E0 弹 Exclamation.ani，写 this+2156 目标槽
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8C70(uint32_t *this)  // 函数: 同族侦测 + 惊叹气泡（500ms 时钟门, this+2165 戳）
{
  int pThis_9; // esi
  int result; // eax
  unsigned int i; // ebx
  int fld_e29; // ecx
  int v6; // edx
  int v7; // edx
  int pObj3; // ecx
  int fld_e292; // ecx
  int v10; // edx
  int v11; // eax
  int pObj; // eax
  int pObj2; // esi
  int v14; // ebx
  unsigned int v15; // [esp+8h] [ebp-4h]

  pThis_9 = (int)(this + 9);  // this+36 = 状态字
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  if ( *(this + 2165) + 500 > (unsigned int)result )  // this+8660 = uEvt8660
    return result;
  *(this + 2165) = sub_699000(pThis_9);  // this+8660 = uEvt8660
  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v6 = *(uint32_t *)(fld_e29 + 8);
    v15 = i;
    if ( v6 != 0 )
      result = (*(uint32_t *)(fld_e29 + 12) - v6) >> 2;  // 向量元素数 = (end−begin)/4
    else
      result = 0;
    if ( (int)i >= result )
    {
      *(this + 2156) = 0;  // this+8624 = uAI8624
      return result;
    }
    v7 = *(uint32_t *)(fld_e29 + 8);
    if ( v7 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v7) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj3 = *(uint32_t *)(v7 + 4 * i);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 529) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v10 = *(uint32_t *)(fld_e292 + 8);
      if ( v10 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v10) >> 2 )  // 向量元素数 = (end−begin)/4
        v11 = *(uint32_t *)(v10 + 4 * i);
      else
        v11 = 0;
      pObj = __RTDynamicCast(v11, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      pObj2 = pObj;
      if ( pObj != 0
        && (*(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) >= 31  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
         && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) <= 35  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 3001) )  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
      {
        break;
      }
    }
LABEL_23:
    ;
  }
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);  // 调用虚函数（虚表槽 +376）
  if ( v14 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)  // 调用虚函数（虚表槽 +376）
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj2)) == 0 )  // 调用虚函数（虚表槽 +1244）
  {
    i = v15;
    goto LABEL_23;
  }
  if ( *(this + 2156) != pObj2 )  // this+8624 = uAI8624
    result = sub_4D83E0(0, 0);  // 头顶气泡 Exclamation.ani（惊叹；同 0x4D82D0 结构）
  *(this + 2156) = pObj2;  // this+8624 = uAI8624
  return result;
}



// 硬直字段（this+204, 研究 15）
// ------------------------------------------------------------
// 0x5A8DD0 sub_5A8DD0 —— 按 AI 状态选帧组写入 vt+204（帧/姿态槽）
// this+8636（子类AI状态区）为 4 或 5（受击后置/受击反应）时只写 (this+6216)+12 单帧；
// 其余状态依次写 +4 / +8 / +12 三帧，每帧经 ·0x4926A0 复位帧游标
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8DD0(uint32_t *this)  // 函数: 按 AI 状态选帧组写入 vt+204（帧/姿态槽）
{
  int fld_e2159; // eax

  fld_e2159 = *(this + 2159);  // this+8636 = pDollTarget
  if ( fld_e2159 == 4 || fld_e2159 == 5 )  // 若 fld_e2159 == 4 与/或 fld_e2159 == 5
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
      this,
      1,
      *(uint32_t *)(*(this + 1554) + 12),  // this+6216 = 资源/帧游标表
      0,
      0,
      0,
      0);
    return sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
      this,
      1,
      *(uint32_t *)(*(this + 1554) + 4),  // this+6216 = 资源/帧游标表
      0,
      0,
      0,
      0);
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
      this,
      3,
      *(uint32_t *)(*(this + 1554) + 8),  // this+6216 = 资源/帧游标表
      0,
      0,
      0,
      0);
    return sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
  }
}



// 硬直字段（this+208）
// ------------------------------------------------------------
// 0x5A8E80 sub_5A8E80 —— (this+6216)+4/8/12 三帧写入 vt+208 位姿槽（与 ·0x5A8DD0 配对）
// 5 行三连调用，无分支；【推断】vt+208 为帧数据的位姿/朝向槽，与 ·0x5A8DD0 的 vt+204 帧槽成对使用
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8E80(uint32_t *this)  // 函数: (this+6216)+4/8/12 三帧写入 vt+208 位姿槽（与 ·0x5A8DD0 配对）
{
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 4));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 8));  // this+6216 = 资源/帧游标表
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));  // this+6216 = 资源/帧游标表
}



// RTTI cast 目标解算（65L）
// ------------------------------------------------------------
// 0x5A8ED0 sub_5A8ED0 —— 同族目标解算（无时钟门，命中值回传）
// 与 ·0x5A8C70 同构的扫描（this+29 数组 + vt+40(obj,529) + IRDMonster 族 31..35/3001 +
// 同队 vt+376 + vt+1244 判定）；差异：无 500ms 门、不写 this+2156 目标槽、不弹气泡，
// 以候选 vt+736 返回值 >0 作为命中条件并返回该值
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8ED0(uint32_t *this)  // 函数: 同族目标解算（无时钟门，命中值回传）
{
  uint32_t *pThis; // ebx
  unsigned int i; // edi
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj3; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int pObj2; // eax
  int pObj; // esi
  int v13; // eax
  int v14; // [esp+Ch] [ebp-8h]

  pThis = this;
  for ( i = 0; ; ++i )
  {
    v3 = pThis[29];
    v4 = *(uint32_t *)(v3 + 8);
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj3 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 529) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      v8 = pThis[29];
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      pObj2 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      pObj = pObj2;
      if ( pObj2 != 0
        && (*(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) >= 31  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
         && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) <= 35  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 3001) )  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
      {
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调用虚函数（虚表槽 +376）
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis);  // 调用虚函数（虚表槽 +376）
        pThis = this;
        if ( v14 == v13 && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj) != 0 )  // 调用虚函数（虚表槽 +1244）
        {
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 736))(pObj);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
          if ( result > 0 )
            break;
        }
      }
    }
  }
  return result;
}



// AI 相位辅助（48L）
// ------------------------------------------------------------
// 0x5A8FF0 sub_5A8FF0 —— 会话管理器 dword_8F8520 包 29/2 构造发送
// vt+8 起包（29, 2），vt+36 依次写本对象 vt+48、vt+52、全局 dword_8F7C04 的 vt+52、
// 常数 2、pArg2（this+116 起始的 8 字节元素数组）条数、nArg3；vt+40 写 nArg4；
// 再逐条写两 u16 字段，末 vt+60(1,-1) 提交；【推断】包体为对象坐标/清单数据
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8FF0(void *this, int pArg2, int nArg3, int nArg4)  // 函数: 会话管理器 dword_8F8520 包 29/2 构造发送
{
  int v5; // edi
  int pThis_30; // eax
  int v7; // edi
  int pThis_34; // eax
  int v9; // esi
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  unsigned int i; // edi
  int v14; // edx

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
  v5 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  pThis_30 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);  // 调用虚函数（虚表槽 +48）
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_30);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  v7 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  pThis_34 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);  // 调用虚函数（虚表槽 +52）
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, pThis_34);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  v9 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 调用虚函数（虚表槽 +52）
  (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 2);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  v11 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v11 != 0 )
    v12 = (*(uint32_t *)(pArg2 + 8) - v11) >> 3;  // pArg2+8〔nSkillRec8(推断)〕
  else
    v12 = 0;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v12);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg3);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nArg4);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
  for ( i = 0; ; ++i )
  {
    v14 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v14 == 0 || i >= (*(uint32_t *)(pArg2 + 8) - v14) >> 3 )  // pArg2+8〔nSkillRec8(推断)〕
      break;
    (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 36))(*(uint16_t *)(8 * i + v14));  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
    (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 36))(*(uint16_t *)(8 * i + *(uint32_t *)(pArg2 + 4) + 4));  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  }
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
}



// 人偶浮游 AI：DOLL_FLOAT_LOOP + DOLL_CAST 播报（75L；
//   this+6556==14 大状态门 + 8620..8664 相位字段）
// ------------------------------------------------------------
// 0x5A9100 sub_5A9100 —— 人偶浮游态状态机（this+6556 大状态镜像门 + 别名播报）
// this+6556==14（蓄力/架招）且入口 ArgList!=14 时先 ·0x5A8E80 写帧槽，this+8636==0
// 再 ·0x4D93D0；随后 super ·0x4E33D0 基类状态收尾，按 6556 分派：0 = 初始态写
// vt+216(19804) 并喊 DOLL_FLOAT_LOOP；4 = 仅写 19804；8 = 清 this+8664；
// 14 = vt+876 双轴归零 + vt+196 帧首 + this+8636 目标槽写入 + ·0x5A8DD0 选帧 +
// 目标空则 ·0x4D9360 并置 this+8620=1，喊 DOLL_CAST，vt+888(1,0,1000,1000) 收手
// ------------------------------------------------------------
int /*thiscall*/ sub_5A9100(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 人偶浮游态状态机（this+6556 大状态镜像门 + 别名播报）
{
  int result; // eax

  if ( *(uint32_t *)(this + 6556) == 14 && ArgList != 14 )  // this+6556 主状态镜像
  {
    sub_5A8E80((uint32_t *)this);  // 调 (this+6216)+4/8/12 三帧写入 vt+208 位姿槽（与 ·0x5A8DD0 配对）
    if ( *(uint32_t *)(this + 8636) == 0 )  // this+8636 人偶目标槽
      sub_4D93D0(this);
  }
  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  result = *(uint32_t *)(this + 6556);  // this+6556 主状态镜像
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 19804);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
      result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                 this,
                 "DOLL_FLOAT_LOOP",  // 资源/动画 TAG DOLL_FLOAT_LOOP
                 19804,
                 0,
                 0);
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 19804);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
      break;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      *(uint8_t *)(this + 8664) = 0;  // this+8664 【推断】子类AI相位槽
      break;
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 6216));  // 调用虚函数（虚表槽 +196）
      sub_4926A0(*(uint32_t *)(this + 120));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      *(uint32_t *)(this + 8636) = **(uint32_t **)(LODWORD(fArg3) + 4);  // 调 取 64 位值低 32 位
      *(uint32_t *)(this + 8640) = 0;  // this+8640 【推断】出土相位槽
      sub_5A8DD0((uint32_t *)this);  // 调 按 AI 状态选帧组写入 vt+204（帧/姿态槽）
      if ( *(uint32_t *)(this + 8636) == 0 )  // this+8636 人偶目标槽
      {
        sub_4D9360(this);
        *(uint8_t *)(this + 8620) = 1;  // this+8620 警报/唤醒标志
      }
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        this,
        "DOLL_CAST",  // 资源/动画 TAG DOLL_CAST
        -1,
        0,
        0);
      result = (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 1, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
      break;
    default:
      return result;
  }
  return result;
}



// 登场曲：sub_406D60 写 "B_MASTERDOGRY_01"（人偶师曲目槽, 82L）
// ------------------------------------------------------------
// 0x5A9290 sub_5A9290 —— 人偶师主 AI 相位机（this+1787 行为字 + B_MASTERDOGRY_01 登场曲）
// ·0x4E0120 基类前置；按 this+1787 相位分派：0 = vt+1284 出场触发，困难级
// （this+1943==3）经 ·0x406D60 写 BGM 曲名 B_MASTERDOGRY_01；4/5 = 无关联对象时
// vt+1104 写行为字 13；13/14/15 = 有关联对象时写回 4。vt+308 校验后 ·0x5A8680 距离档
// 写入、有关联对象走 vt+1312 收手；vt+840 非受击时以 this+2156 目标经 ·0x5A8490 感知
// 半径校验（超 ·0x4D8FE0 视距则清目标，无目标走 ·0x5A8C70 侦测），近 30 距离内
// ·0x4DC130 单向拒绝测试后 vt+896 位移/施放写入
// ------------------------------------------------------------
int /*thiscall*/ sub_5A9290(int *this)  // 函数: 人偶师主 AI 相位机（this+1787 行为字 + B_MASTERDOGRY_01 登场曲）
{
  int result; // eax
  int uPatrolGate; // eax  | +0x21B0 → 子类槽〔5A82B0 复位〕（CNDollMaster）
  int v4; // edi
  int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int uPatrolGate_; // edx  | +0x21B0 → 子类槽〔5A82B0 复位〕（CNDollMaster）
  int v10; // [esp+4h] [ebp-8h] BYREF
  int v11; // [esp+8h] [ebp-4h] BYREF

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( *(this + 1787) )  // this+7148 = nBigState
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      (*(void (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
      if ( *(this + 1943) == 3 )  // this+7772 = nCounterState
        sub_406D60("B_MASTERDOGRY_01");  // 调 std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) == 0 )  // this+7252 = pTarget7252
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
      break;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调用虚函数（虚表槽 +1104）
      break;
    default:
      break;
  }
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    sub_5A8680(this);  // 调 距离档写入（this+2167 = 0/1/2 三档）
    if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
      (*(void (/*thiscall*/ **)(int *))(*this + 1312))(this);  // 调用虚函数（虚表槽 +1312）
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    if ( result == 0 )
    {
      uPatrolGate = *(this + 2156);  // this+8624 = uAI8624
      if ( uPatrolGate != 0 )
      {
        v4 = sub_5A8490(this, uPatrolGate);  // 调 感知半径解算（有对象取距离，无对象取视野+100）
        if ( v4 > sub_4D8FE0(this) )  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
          *(this + 2156) = 0;  // this+8624 = uAI8624
      }
      else
      {
        sub_5A8C70(this);  // 调 同族侦测 + 惊叹气泡（500ms 时钟门, this+2165 戳）
      }
      result = *(this + 2156);  // this+8624 = uAI8624
      if ( result != 0 )  // 若结果非 0（成功）
      {
        v5 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, result, 0);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
        result = sub_4D8FE0(this) - 30;  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
        if ( v5 > result )
        {
          v6 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);  // 调用虚函数（虚表槽 +184）【推断: 动画对象 z 倾斜转状态码】
          v7 = *this;
          v10 = v6;
          v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 188))(this);  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
          uPatrolGate_ = *(this + 2156);  // this+8624 = uAI8624
          v11 = v8;
          sub_4DC130(uPatrolGate_, &v10, &v11);  // 调 单向拒绝测试（0x4DBDB0 的简化版，只判越界方向）
          return (*(int (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, v10, v11);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        }
      }
    }
  }
  return result;
}



// RTTI cast + 时钟门 AI（84L）
// ------------------------------------------------------------
// 0x5A9410 sub_5A9410 —— 同族坐标汇总发包（this+29 扫描 + 包 50/5000）
// 与 ·0x5A8ED0 同构的扫描（vt+40(obj,529) + IRDMonster 族 31..35/3001 + 同队 vt+376 +
// vt+1244 判定）；差异：命中者取 vt+48/vt+52 坐标对存栈经 ·0x474950 汇集，末
// ·0x5A8FF0 以包型 (50, 5000) 发送清单，写 this+8632 = clock_now 计时戳
// ------------------------------------------------------------
void /*thiscall*/ sub_5A9410(int *this)  // 函数: 同族坐标汇总发包（this+29 扫描 + 包 50/5000）
{
  int *pThis; // ebx
  unsigned int i; // edi
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int pObj3; // eax
  int pObj2; // esi
  int v13; // eax
  int v14; // edx
  int v15; // eax
  uint8_t v16[4]; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+10h] [ebp-28h]
  int v18; // [esp+14h] [ebp-24h]
  int v19; // [esp+18h] [ebp-20h]
  uint32_t v20[2]; // [esp+1Ch] [ebp-1Ch] BYREF
  int v21; // [esp+24h] [ebp-14h]
  int *pThis2; // [esp+28h] [ebp-10h]
  int v23; // [esp+34h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  Block = nullptr;
  v18 = 0;
  v19 = 0;
  v23 = 0;
  for ( i = 0; ; ++i )
  {
    v3 = pThis[29];
    v4 = *(uint32_t *)(v3 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= v5 )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj = *(uint32_t *)(v6 + 4 * i);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      v8 = pThis[29];
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      pObj3 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      pObj2 = pObj3;
      if ( pObj3 != 0
        && (*(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 340))(pObj3) >= 31  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
         && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) <= 35  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 3001) )  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
      {
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);  // 调用虚函数（虚表槽 +376）
        v14 = *pThis;
        v21 = v13;
        v15 = (*(int (/*thiscall*/ **)(int *))(v14 + 376))(pThis);  // 调用虚函数（虚表槽 +376）
        pThis = pThis2;
        if ( v21 == v15 && (*(uint8_t (/*thiscall*/ **)(int *, int))(*pThis2 + 1244))(pThis2, pObj2) != 0 )  // 调用虚函数（虚表槽 +1244）
        {
          v20[0] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);  // 调用虚函数（虚表槽 +48）
          v20[1] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);  // 调用虚函数（虚表槽 +52）
          sub_474950(v20);  // 调 调用 sub_474950
        }
      }
    }
  }
  sub_5A8FF0(pThis, (int)v16, 50, 5000);  // 调 会话管理器 dword_8F8520 包 29/2 构造发送
  pThis[2158] = sub_699000((int)(pThis + 9));  // 【clock_now(clk)】
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 堆释放
}



// 人偶字段群（this+8600/8620/8648/8668）
// ------------------------------------------------------------
// 0x5A95A0 sub_5A95A0 —— 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
// ·0x430C80 打包 nArg2 参数块，再经 vt+560 以态 14 写回（与 0x5A0420/0x5A9100 的
// 6556 态 14 族呼应）；调用方以编号区分：0 归位 / 1 待机 / 2 巡视 / 3 施放 / 4~5 攻击变体
// ------------------------------------------------------------
void /*thiscall*/ sub_5A95A0(void *this, int nArg2)  // 函数: 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
{
  uint8_t v3[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  int v6; // [esp+14h] [ebp-10h]
  int v7; // [esp+20h] [ebp-4h]

  Block = nullptr;
  v5 = 0;
  v6 = 0;
  v7 = 0;
  sub_430C80(nullptr, 1, (int)&nArg2);  // 调 uint32 vector 区间插入（同值填充）
  (*(void (/*thiscall*/ **)(void *, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 14, v3, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 堆释放
}



// ------------------------------------------------------------
// 0x5A9620 sub_5A9620 —— 人偶行为选择（攻击型 4 号）
// 骨架：vt+840 非受击 且（this+8620 置位 或 vt+684 距主子距离 > this+8600 阈值）才行动，
// 否则 ·0x5A95A0(0) 归位。本变体：this+8668==2 时 2% 概率指令 1；==1 时经 this+7252
// 关联对象 vt+776(7) 校验后 10% 概率指令 4，并写 this+8648 = vt+164 距离解算值
// ------------------------------------------------------------
void /*thiscall*/ sub_5A9620(int this)  // 函数: 人偶行为选择（攻击型 4 号）
{
  unsigned int nDistThreshold; // eax  | +0x2198 → 【推断】距主人距离阈值〔5A9620：vt+684 距离 > 此值才行动〕（CNStoneMaster；va=005A82B0）
  int pLinkSlot7252; // ecx  | +0x1C54 → 【推断】关联对象/主人引用〔5A9620 检 vt+776 关联体；5F150 置 0 清链〕（CNStoneMaster；va=005A9620）

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( *(uint8_t *)(this + 8620) != 0  // this+8620 相位双字节门
      || (nDistThreshold = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(nDistThreshold) > *(uint32_t *)(this + 8600)) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( *(uint32_t *)(this + 8668) == 2 && rand() % 100 < 2 )  // 调 以 16 位种子状态递推并返回 15 位结果
      {
        sub_5A95A0((void *)this, 1);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
      }
      else if ( *(uint32_t *)(this + 8668) == 1 )  // this+8668 【推断】人偶行为模式
      {
        pLinkSlot7252 = *(uint32_t *)(this + 7252);  // this+7252 当前目标/技能对象
        if ( pLinkSlot7252 != 0
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pLinkSlot7252 + 776))(pLinkSlot7252, 7) == 0  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
          && rand() % 100 < 10 )  // 调 以 16 位种子状态递推并返回 15 位结果
        {
          sub_5A95A0((void *)this, 4);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
          *(uint32_t *)(this + 8648) = (uint64_t)((double (/*thiscall*/ *)(int, uint32_t, uint32_t))*(uint32_t *)(*(uint32_t *)this + 164))(  // 调用虚函数（虚表槽 +164）【推断: ★ 与目标朝向角度（atan2 角度制；3D 俯视判定）】
                                                         this,
                                                         *(uint32_t *)(this + 7252),  // this+7252 当前目标/技能对象
                                                         0);
        }
      }
    }
    else
    {
      sub_5A95A0((void *)this, 0);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
    }
  }
}



// 人偶字段群（sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5A96F0 sub_5A96F0 —— 同构 ·0x5A9620（人偶行为选择之巡视型）
// 差异：this+8668==2 仍是 2% 指令 1；替代分支改为 this+8624 非空 + 15% 概率 +
// this+8632 计时戳 5000ms 冷却（clock_now 门）时指令 2
// ------------------------------------------------------------
void /*thiscall*/ sub_5A96F0(int this)  // 函数: 同构 ·0x5A9620（人偶行为选择之巡视型）
{
  unsigned int nDistThreshold; // eax  | +0x2198 → 距主人距离阈值〔5A9620：vt+684 距离 > 此值才行动〕【推断】（CNSteelMaster）

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( *(uint8_t *)(this + 8620) != 0  // this+8620 警报/唤醒标志
      || (nDistThreshold = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(nDistThreshold) > *(uint32_t *)(this + 8600)) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( *(uint32_t *)(this + 8668) == 2 && rand() % 100 < 2 )  // 调 以 16 位种子状态递推并返回 15 位结果
      {
        sub_5A95A0((void *)this, 1);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
      }
      else if ( *(uint32_t *)(this + 8624) != 0  // this+8624 【推断】子类AI槽
             && rand() % 100 < 15  // 调 以 16 位种子状态递推并返回 15 位结果
             && *(uint32_t *)(this + 8632) + 5000 < (unsigned int)sub_699000(this + 36) )  // 【clock_now(clk)】
      {
        sub_5A95A0((void *)this, 2);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
      }
    }
    else
    {
      sub_5A95A0((void *)this, 0);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
    }
  }
}



// 人偶字段群
// ------------------------------------------------------------
// 0x5A97A0 sub_5A97A0 —— 同构 ·0x5A9620（人偶行为选择之常态攻击型）
// 差异：分支条件合并为 this+8668==1 且 this+7252 非空且 10% 概率，直接指令 5
// （不查关联对象 vt+776(7)），同样写 this+8648 = vt+164 距离解算值
// ------------------------------------------------------------
void /*thiscall*/ sub_5A97A0(int this)  // 函数: 同构 ·0x5A9620（人偶行为选择之常态攻击型）
{
  unsigned int nDistThreshold; // eax  | +0x2198 → 【推断】距主人距离阈值〔5A97A0：vt+684 距离 > 此值才行动〕（CNClayMaster；va=005A82B0）

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( *(uint8_t *)(this + 8620) != 0  // this+8620 相位双字节门
      || (nDistThreshold = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(nDistThreshold) > *(uint32_t *)(this + 8600)) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( *(uint32_t *)(this + 8668) == 2 && rand() % 100 < 2 )  // 调 以 16 位种子状态递推并返回 15 位结果
      {
        sub_5A95A0((void *)this, 1);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
      }
      else if ( *(uint32_t *)(this + 8668) == 1 && *(uint32_t *)(this + 7252) != 0 && rand() % 100 < 10 )  // 调 以 16 位种子状态递推并返回 15 位结果
      {
        sub_5A95A0((void *)this, 5);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
        *(uint32_t *)(this + 8648) = (uint64_t)((double (/*thiscall*/ *)(int, uint32_t, uint32_t))*(uint32_t *)(*(uint32_t *)this + 164))(  // 调用虚函数（虚表槽 +164）【推断: ★ 与目标朝向角度（atan2 角度制；3D 俯视判定）】
                                                       this,
                                                       *(uint32_t *)(this + 7252),  // this+7252 当前目标/技能对象
                                                       0);
      }
    }
    else
    {
      sub_5A95A0((void *)this, 0);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
    }
  }
}



// 人偶字段群
// ------------------------------------------------------------
// 0x5A9860 sub_5A9860 —— 同构 ·0x5A9620（人偶行为选择之施放优先型）
// 差异：优先级改为 10% 且 this+8624 非空 → 指令 3；再 this+8668==2 时 15% → 指令 1；
// 末 this+8668==1 走 ·0x5A9620 同款 vt+776(7) 校验 + 10% → 指令 4 + this+8648 写入
// ------------------------------------------------------------
void /*thiscall*/ sub_5A9860(int this)  // 函数: 同构 ·0x5A9620（人偶行为选择之施放优先型）
{
  unsigned int nDistThreshold; // eax  | +0x2198 → 距主人距离阈值〔5A9620：vt+684 距离 > 此值才行动〕【推断】（CNMasterDogri）
  int pLinkSlot7252; // ecx  | +0x1C54 → 关联对象/主人引用〔5A9620 检 vt+776 关联体；5F150 置 0 清链〕【推断】（CNMasterDogri）

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( *(uint8_t *)(this + 8620) != 0  // this+8620 警报/唤醒标志
      || (nDistThreshold = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(nDistThreshold) > *(uint32_t *)(this + 8600)) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( rand() % 100 < 10 && *(uint32_t *)(this + 8624) != 0 )  // 调 以 16 位种子状态递推并返回 15 位结果
      {
        sub_5A95A0((void *)this, 3);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
      }
      else if ( *(uint32_t *)(this + 8668) == 2 && rand() % 100 < 15 )  // 调 以 16 位种子状态递推并返回 15 位结果
      {
        sub_5A95A0((void *)this, 1);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
      }
      else if ( *(uint32_t *)(this + 8668) == 1 )  // this+8668 人偶行为模式
      {
        pLinkSlot7252 = *(uint32_t *)(this + 7252);  // this+7252 关联对象/主人引用
        if ( pLinkSlot7252 != 0
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pLinkSlot7252 + 776))(pLinkSlot7252, 7) == 0  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
          && rand() % 100 < 10 )  // 调 以 16 位种子状态递推并返回 15 位结果
        {
          sub_5A95A0((void *)this, 4);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
          *(uint32_t *)(this + 8648) = (uint64_t)((double (/*thiscall*/ *)(int, uint32_t, uint32_t))*(uint32_t *)(*(uint32_t *)this + 164))(  // 调用虚函数（虚表槽 +164）【推断: ★ 与目标朝向角度（atan2 角度制；3D 俯视判定）】
                                                         this,
                                                         *(uint32_t *)(this + 7252),  // this+7252 关联对象/主人引用
                                                         0);
        }
      }
    }
    else
    {
      sub_5A95A0((void *)this, 0);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
    }
  }
}



// 人偶字段群
// ------------------------------------------------------------
// 0x5A9950 sub_5A9950 —— 同构 ·0x5A9620（人偶行为选择之简式）
// 差异：仅一条分支——this+8668 为 1 或 2 且 20% 概率时指令 1，无距离/关联对象校验
// ------------------------------------------------------------
void /*thiscall*/ sub_5A9950(int this)  // 函数: 同构 ·0x5A9620（人偶行为选择之简式）
{
  unsigned int nDistThreshold; // eax  | +0x2198 → 距主人距离阈值〔5A9620：vt+684 距离 > 此值才行动〕【推断】（CNIceDoll_Sharedo）
  int nDollMode; // eax  | +0x21DC → 人偶行为模式〔5A9620：1=常态攻击指令5；2=巡视 2% 指令1〕【推断】（CNIceDoll_Sharedo）

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( *(uint8_t *)(this + 8620) != 0  // this+8620 警报/唤醒标志
      || (nDistThreshold = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(nDistThreshold) > *(uint32_t *)(this + 8600)) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      nDollMode = *(uint32_t *)(this + 8668);  // this+8668 人偶行为模式
      if ( (nDollMode == 2 || nDollMode == 1) && rand() % 100 < 20 )  // 调 以 16 位种子状态递推并返回 15 位结果
        sub_5A95A0((void *)this, 1);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
    }
    else
    {
      sub_5A95A0((void *)this, 0);  // 调 人偶动作指令下行（vt+560 setState 形, 反应态 14 = 架招）
    }
  }
}



// 石泡技能：引用 PassiveObject/Common/Particle/StoneBubble.ptl（54L）
// ------------------------------------------------------------
// 0x5A99C0 sub_5A99C0 —— 石泡技能 1（StoneBubble 粒子 + vt+580 发射 48010）
// vt+308 校验通过后惰性构造：this+8652 空时 new 0x12C 经 ·0x428F30 构造
// PassiveObject/Common/Particle/StoneBubble.ptl 并缓存；有关联对象 (this+7252) 时经
// vt+164 距离解算写粒体 +72 偏移，否则用 this+8648；末 vt+580 以编号 48010 发射
// ------------------------------------------------------------
int /*usercall*/ sub_5A99C0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：石泡技能 1（StoneBubble 粒子 + vt+580 发射 48010）
{
  int result; // eax
  uint32_t *pMem; // eax
  uint32_t *v6; // eax
  int v7; // eax
  int pObj; // edi
  uint64_t v9; // rax
  int v10; // edi
  int v11; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    if ( pArg1[2163] == 0 )
    {
      pMem = operator new(0x12Cu);  // operator new 分配 300 字节
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v6 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/StoneBubble.ptl", 0);  // 调 CNRDObjectParticleCreater 构造
      else
        v6 = nullptr;
      pArg1[2163] = v6;
    }
    v7 = pArg1[1813];
    if ( v7 != 0 )
    {
      pObj = pArg1[2163];
      v9 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t, int))*(uint32_t *)(*pArg1 + 164))(pArg1, v7, 0, nArg2);  // 调用虚函数（虚表槽 +164）【推断: ★ 与目标朝向角度（atan2 角度制；3D 俯视判定）】
      *(uint32_t *)((*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 28))(pObj, HIDWORD(v9)) + 72) = v9;  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
    }
    else
    {
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pArg1[2163] + 28))(pArg1[2163], nArg3) + 72) = pArg1[2162];  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
    }
    v10 = *pArg1;
    v11 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)pArg1[2163] + 28))(  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
            pArg1[2163],
            0,
            15,
            0,
            55,
            1,
            0,
            0);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(v10 + 580))(pArg1, 48010, 0, v11);  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
  }
  return result;
}



// 石泡技能 2：PassiveObject/Common/Particle/StoneBubble.ptl（54L）
// ------------------------------------------------------------
// 0x5A9AC0 sub_5A9AC0 —— 同构 ·0x5A99C0（石泡技能变体, 差异：发射编号 48014 替代 48010）
// 同样 new 0x12C + ·0x428F30 构造 PassiveObject/Common/Particle/StoneBubble.ptl 并缓存
// this+8652；有关联对象 (this+7252) 时经 vt+164 距离解算写目标 +72 偏移，否则用 this+8648；
// 末 vt+580 发射 48014
// ------------------------------------------------------------
int /*usercall*/ sub_5A9AC0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：同构 ·0x5A99C0（石泡技能变体, 差异：发射编号 48014 替代 48010）
{
  int result; // eax
  uint32_t *pMem; // eax
  uint32_t *v6; // eax
  int v7; // eax
  int pObj; // edi
  uint64_t v9; // rax
  int v10; // edi
  int v11; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    if ( pArg1[2163] == 0 )
    {
      pMem = operator new(0x12Cu);  // operator new 分配 300 字节
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v6 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/StoneBubble.ptl", 0);  // 调 CNRDObjectParticleCreater 构造
      else
        v6 = nullptr;
      pArg1[2163] = v6;
    }
    v7 = pArg1[1813];
    if ( v7 != 0 )
    {
      pObj = pArg1[2163];
      v9 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t, int))*(uint32_t *)(*pArg1 + 164))(pArg1, v7, 0, nArg2);  // 调用虚函数（虚表槽 +164）【推断: ★ 与目标朝向角度（atan2 角度制；3D 俯视判定）】
      *(uint32_t *)((*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 28))(pObj, HIDWORD(v9)) + 72) = v9;  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
    }
    else
    {
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pArg1[2163] + 28))(pArg1[2163], nArg3) + 72) = pArg1[2162];  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
    }
    v10 = *pArg1;
    v11 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)pArg1[2163] + 28))(  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
            pArg1[2163],
            0,
            15,
            0,
            55,
            1,
            0,
            0);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(v10 + 580))(pArg1, 48014, 0, v11);  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
  }
  return result;
}



// AI 相位辅助（52L）
// ------------------------------------------------------------
// 0x5A9BC0 sub_5A9BC0 —— 反应态(14) 下的攻击段号分派器（this+8636 段号槽）
// vt+840 == 14（架招态）且本对象帧首 == (this+6216) 帧首一致时：this+8640 未置位且
// 当前帧 (vt+200)+148 == 6 时按 this+8636 段号 0..5 分派——0 人偶召唤 ·0x5A8880 /
// 1 vt+1308 / 2 坐标汇总 ·0x5A9410 / 3 目标解算 ·0x5A8ED0 / 4~5 石泡技能 ·0x5A99C0/·0x5A9AC0，
// 置 this+8640=1 防重；帧 +170 置位时 vt+560 归还状态 (0,0,0,0)
// ------------------------------------------------------------
int /*usercall*/ sub_5A9BC0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 实现：反应态(14) 下的攻击段号分派器（this+8636 段号槽）
{
  int result; // eax
  uint32_t *v4; // edi

  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( result == 14 )
  {
    v4 = (uint32_t *)pDwArg1[1554];
    result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    if ( result == *v4 )
    {
      if ( pDwArg1[2160] == 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) + 148) == 6 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      {
        switch ( pDwArg1[2159] )  // 按 pDwArg1[2159] 分派
        {
          case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
            sub_5A8880(pDwArg1);  // 调 召唤落点解算 + DOLL_SUMMON 播报
            break;
          case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
            (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 1308))(pDwArg1);  // 调用虚函数（虚表槽 +1308）
            break;
          case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
            sub_5A9410(pDwArg1);  // 调 同族坐标汇总发包（this+29 扫描 + 包 50/5000）
            break;
          case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
            sub_5A8ED0(pDwArg1);  // 调 同族目标解算（无时钟门，命中值回传）
            break;
          case 4:  // case 4 = ENUM_CMDPACKET_EXIT
            sub_5A99C0(pDwArg1, nArg2, (int)v4);  // 调 石泡技能 1（StoneBubble 粒子 + vt+580 发射 48010）
            break;
          case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
            sub_5A9AC0(pDwArg1, nArg2, (int)v4);  // 调 同构 ·0x5A99C0（石泡技能变体, 差异：发射编号 48014 替代 48010）
            break;
          default:
            break;
        }
        pDwArg1[2160] = 1;
      }
      result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      if ( *(uint8_t *)(result + 170) != 0 )
        return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    }
  }
  return result;
}



// 技能播报：JEWEL_HIT（宝石命中）+ SWING_SHORT + STONE_DMG（65L）
// ------------------------------------------------------------
// 0x5A9CA0 sub_5A9CA0 —— 攻击段号相位联动播报（JEWEL_HIT / SWING_SHORT / STONE_DMG）
// ·0x4E1780 基类前置 + vt+308 校验后走 ·0x5A9BC0 段号分派；vt+840 == 8（攻击态）时
// 按 this+7028 段号槽：==1 且帧 +148==3 且 this+8664 未播 → 喊 JEWEL_HIT 并置位；
// 段号槽为 0 时帧 +148==1 → SWING_SHORT 置位、帧 +148==6 且已置位 → STONE_DMG 复位
// ------------------------------------------------------------
char /*usercall*/ sub_5A9CA0@<al>(int pArg1@<ecx>, int nArg2@<ebx>)  // 实现：攻击段号相位联动播报（JEWEL_HIT / SWING_SHORT / STONE_DMG）
{
  int v3; // eax

  sub_4E1780((uint32_t *)pArg1);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    sub_5A9BC0((int *)pArg1, nArg2);  // 调 反应态(14) 下的攻击段号分派器（this+8636 段号槽）
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( v3 == 8 )
  {
    if ( sub_41A5E0(pArg1 + 7028) != 0 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v3 = sub_41A5E0(pArg1 + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( v3 == 1 )
      {
        v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        if ( *(uint32_t *)(v3 + 148) == 3 )
        {
          LOBYTE(v3) = *(uint8_t *)(pArg1 + 8664);  // 调 取 16 位值低 8 位
          if ( (uint8_t)v3 == 0 )
          {
            LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                           pArg1,
                           "JEWEL_HIT",  // 资源/动画 TAG JEWEL_HIT
                           -1,
                           0,
                           0);
            *(uint8_t *)(pArg1 + 8664) = 1;  // pArg1+8664〔uAI8664(推断)〕
          }
        }
      }
    }
    else
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) == 1 && *(uint8_t *)(pArg1 + 8664) == 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          pArg1,
          "SWING_SHORT",  // 资源/动画 TAG SWING_SHORT
          -1,
          0,
          0);
        *(uint8_t *)(pArg1 + 8664) = 1;  // pArg1+8664〔uAI8664(推断)〕
      }
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      if ( *(uint32_t *)(v3 + 148) == 6 && *(uint8_t *)(pArg1 + 8664) == 1 )  // pArg1+8664〔uAI8664(推断)〕
      {
        LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                       pArg1,
                       "STONE_DMG",  // 资源/动画 TAG STONE_DMG
                       -1,
                       0,
                       0);
        *(uint8_t *)(pArg1 + 8664) = 0;  // pArg1+8664〔uAI8664(推断)〕
      }
    }
  }
  return v3;
}



// 人偶师装载：DOLL_DMG/DOLL_DIE 播报 + Monster/DollMaster/DollMaster.equ +
//   R_DOLL_AMB 语音（109L）
// ------------------------------------------------------------
// 0x5A9DA0 sub_5A9DA0 —— 人偶师装载初始化（DOLL_DMG/DOLL_DIE 语音池 + DollMaster.equ 外观）
// this+6792..6808 写 1,2,3,2,4（伤害类型/音效映射表），·0x4015C0 构造 DOLL_DMG/DOLL_DIE/
// R_DOLL_AMB 三字符串；new 0x544 经 ·0x4BA9E0(.equ 外观挂装) 读 Monster/DollMaster/DollMaster.equ
// 并由 vt+784 挂装；vt+384 出场参数面依次写 this+8600(100)/this+8636(-30)/this+8624(570) 与
// 2150/2151/2152/2153/2154 阈值及粒子句柄槽；·0x4049C0 帧间插值写 this+8644；
// this+8620 清 0，this+8628/8632/8660 时钟戳三连、this+8652 石泡句柄清 0、this+8480=20/8484=2000；
// 末 ·0x4DE5E0 装载 R_DOLL_AMB 文案条目（随机倒计时 5000/10000）
// ------------------------------------------------------------
int /*thiscall*/ sub_5A9DA0(uint32_t *this)  // 函数: 人偶师装载初始化（DOLL_DMG/DOLL_DIE 语音池 + DollMaster.equ 外观）
{
  void *pMem; // eax
  char *v3; // eax
  int v4; // edx
  int pObj; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edx
  uint64_t v9; // rax
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  void *v16; // eax
  int fld_e1821; // edi
  int fld_e1820; // edi
  int fld_e18202; // eax
  char v21[4]; // [esp+14h] [ebp-44h] BYREF
  void *v22; // [esp+18h] [ebp-40h]
  int v23; // [esp+1Ch] [ebp-3Ch]
  int v24; // [esp+20h] [ebp-38h]
  int v25; // [esp+24h] [ebp-34h]
  float v26; // [esp+28h] [ebp-30h]
  int v27; // [esp+2Ch] [ebp-2Ch]
  int v28; // [esp+30h] [ebp-28h]
  size_t v29; // [esp+34h] [ebp-24h]
  void *Block; // [esp+44h] [ebp-14h]
  int v31; // [esp+48h] [ebp-10h]
  int v32; // [esp+54h] [ebp-4h]

  v29 = 8;
  v28 = (int)"DOLL_DMG";  // 资源/动画 TAG DOLL_DMG
  *(this + 1698) = 1;  // this+6792 = 炮车/子类参数面槽 1
  *(this + 1699) = 2;  // this+6796 = 炮车/子类参数面槽 2
  *(this + 1700) = 3;  // this+6800 = 炮车/子类参数面槽 3
  *(this + 1701) = 2;  // this+6804 = 炮车/子类参数面槽 4
  *(this + 1702) = 4;  // this+6808 = 炮车/子类参数面槽 5
  sub_4015C0((void *)v28, v29);  // 【std::string构造赋值】
  sub_4015C0("DOLL_DIE", 8u);  // 【std::string构造赋值】
  pMem = operator new(0x544u);  // operator new 分配 1348 字节
  Block = pMem;
  v32 = 0;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0((char *)pMem, "Monster/DollMaster/DollMaster.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v3 = nullptr;
  v4 = *this;
  v32 = -1;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(v4 + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调用虚函数（虚表槽 +4）
  v6 = *this;
  v29 = 0;
  *(this + 1830) = 100;
  *(this + 1839) = -30;
  *(this + 1831) = 570;
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, size_t))(v6 + 384))(this, v29);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v8 = *this;
  v31 = v7;
  *(float *)&Block = (double)v7 * 0.01;
  v31 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 740))(this);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
  v9 = (uint64_t)((double)v31 * *(float *)&Block);
  *(this + 2150) = v9;  // this+8600 = uAI8600
  v10 = (*(int (/*fastcall*/ **)(uint32_t *, uint32_t, int))(*this + 384))(this, HIDWORD(v9), 1);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v11 = *this;
  v29 = 2;
  *(this + 2151) = v10;  // this+8604 = bAI8604
  *(this + 2152) = (*(int (/*thiscall*/ **)(uint32_t *, size_t))(v11 + 384))(this, v29);  // this+8608 = uAI8608
  v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v13 = *this;
  v29 = 4;
  *(this + 2153) = v12;  // this+8612 = uAI8612
  *(this + 2154) = (*(int (/*thiscall*/ **)(uint32_t *, size_t))(v13 + 384))(this, v29);  // this+8616 = uAI8616
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v15 = *this;
  v31 = v14;
  v16 = (void *)(*(int (/*thiscall*/ **)(uint32_t *, int))(v15 + 384))(this, 6);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  fld_e1821 = *(this + 1821);
  Block = v16;
  fld_e1820 = fld_e1821 - *(this + 1820);
  fld_e18202 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3) - *(this + 1820);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  *(float *)&v27 = (float)(int)Block;
  v26 = (float)v31;
  *(this + 2161) = (uint64_t)sub_4049C0(v26, *(float *)&v27, fld_e18202, fld_e1820);  // this+8644 = 相位槽
  *((uint8_t *)this + 8620) = 0;  // this+8620 = uAI8620
  *(this + 2157) = sub_699000((int)(this + 9));  // this+8628 = 指挥计时戳
  *(this + 2158) = sub_699000((int)(this + 9));  // this+36 = 状态字
  *(this + 2163) = 0;  // this+8652 = 相位槽
  v29 = 10000;
  v28 = 5000;
  *(float *)&Block = COERCE_FLOAT(v21);
  *(this + 2165) = sub_699000((int)(this + 9));  // this+8660 = uEvt8660
  *(this + 2120) = 20;  // this+8480〔pAtkObj〕
  *(this + 2121) = 2000;
  v27 = 15;
  v26 = 0.0;
  LOBYTE(v22) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("R_DOLL_AMB", 0xAu);  // 【std::string构造赋值】
  return sub_4DE5E0(v21[0], v22, v23, v24, v25, SLODWORD(v26), v27, v28, v29);  // 调 文案条目装载 + 随机倒计时（0x4DE410 的配套件）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A9FF0 sub_5A9FF0 —— 蓄力阈值与倒计时复位（this+8600 = 0, this+8696 = 1000）
// 4 行无分支；【推断】this+8600 为人偶距离阈值（·0x5A9620 族比较对象），this+8696 = 蓄力倒计时初值
// ------------------------------------------------------------
void /*thiscall*/ sub_5A9FF0(uint32_t *this)  // 函数: 蓄力阈值与倒计时复位（this+8600 = 0, this+8696 = 1000）
{
  *(this + 2150) = 0;  // this+8600 = uAI8600
  *(this + 2174) = 1000;  // this+8696〔uVec8696(推断)〕
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AA010 sub_5AA010 —— 高度差驱动位移/攀爬（this+324 与 vt+128 高度槽之差）
// fld_e81 = this+324 - vt+128(高度槽)：非零时按正负取 ±1000 速率经 ·0x495890 下发，
// ·0x4A0550 与 ·0x4A0600(2) 推进位移；差为零时检查 this+112 关联体的 vt+308 与
// 浮点 +24（速率/滞空），非零则归零并置 +196 标志位（落地），再 ·0x495890(2,0) 收速
// ------------------------------------------------------------
int /*thiscall*/ sub_5AA010(uint32_t *this)  // 函数: 高度差驱动位移/攀爬（this+324 与 vt+128 高度槽之差）
{
  int fld_e81; // edi
  uint32_t *fld_e28; // edi

  fld_e81 = *(this + 81) - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // this+324 = 购买上下文 id（0x550480: dword
  if ( fld_e81 != 0 )
  {
    sub_495890(0, fld_e81 <= 0 ? 1000 : -1000);  // 调 模式选择式方位设置（1/2/其他 三分支）
    sub_4A0550(fld_e81);  // 调 镜头幅度
    return sub_4A0600(2);
  }
  else
  {
    fld_e28 = (uint32_t *)*(this + 28);  // this+112 = pHostComp
    if ( *fld_e28 != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      && *((float *)fld_e28 + 6) != 0.0 )
    {
      fld_e28[6] = 0;
      *((uint8_t *)fld_e28 + 196) = 1;
    }
    return sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AA0A0 sub_5AA0A0 —— 同构 ·0x5A8FF0 简化版（包 29/2 仅写对象三元组 + nArg2）
// 会话管理器 dword_8F8520 起包 (29,2)，vt+36 依次写本对象 vt+48、vt+52、全局 dword_8F7C04
// 的 vt+52、nArg2；无清单循环与 vt+40 写；末 vt+60(1,-1) 提交
// ------------------------------------------------------------
int /*thiscall*/ sub_5AA0A0(void *this, int nArg2)  // 函数: 同构 ·0x5A8FF0 简化版（包 29/2 仅写对象三元组 + nArg2）
{
  int v3; // edi
  int pThis_30; // eax
  int v5; // edi
  int pThis_34; // eax
  int v7; // esi
  int v8; // eax

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
  v3 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  pThis_30 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);  // 调用虚函数（虚表槽 +48）
  (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, pThis_30);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  v5 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  pThis_34 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);  // 调用虚函数（虚表槽 +52）
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_34);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  v7 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 调用虚函数（虚表槽 +52）
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg2);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
}



// AI 字段访问（this+8700/8701）
// ------------------------------------------------------------
// 0x5AA130 sub_5AA130 —— 受击/架招一次性标志 + 反击触发判定
// vt+840 == 14（架招态）且 this+8700 未置位则置 1（架招命中标记）；否则 vt+840 == 16
// 且 this+8701 未置位则置 1；末走 ·0x4DB480（★ 反击/架招触发判定，尾调 sub_4D6D90）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AA130(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 受击/架招一次性标志 + 反击触发判定
{
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) != 14 || *(this + 8700) != 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 16 && *(this + 8701) == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      *(this + 8701) = 1;
  }
  else
  {
    *(this + 8700) = 1;  // this+8700 【推断】投石初始化标志
  }
  return sub_4DB480(nArg2, nArg3, nArg4);  // 调 ★ 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AA190 sub_5AA190 —— 关联对象横向距离校验（this+7252 与 x 差 <= nArg2）
// 关联对象空直接 0；否则取关联体 vt+120(x) 与本对象 vt+120(x) 之 |差|，超过 nArg2 返回 0；
// pszArg3 非空且本对象 vt+152 朝向 <= 1 时读关联体 vt+120 与本对象 vt+120（取位对齐），返回 1
// ------------------------------------------------------------
char /*thiscall*/ sub_5AA190(uint32_t *this, signed int nArg2, char pszArg3)  // 函数: 关联对象横向距离校验（this+7252 与 x 差 <= nArg2）
{
  int fld_e1813; // eax
  int v5; // edi

  fld_e1813 = *(this + 1813);  // this+7252 = pTarget7252
  if ( fld_e1813 == 0 )
    return 0;
  v5 = (*(int (**)(void))(*(uint32_t *)fld_e1813 + 120))();  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  if ( (int)abs32(v5 - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this)) > nArg2 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    return 0;
  if ( pszArg3 != 0 && (unsigned int)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) <= 1 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  {
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252 = pTarget7252
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  }
  return 1;  // 返回 1(成功)
}



// RTTI cast 目标解算（this+8608）
// ------------------------------------------------------------
// 0x5AA200 sub_5AA200 —— 碰撞体反击反馈（this+8608 == 1 时对撞方 vt+760 附加伤害号）
// nArg4 为 0 且 this+8608 == 1 时：取本对象 vt+736 值，与 vt+740 值的 0.5 倍比较，
// 高于半值取伤害号 15 否则 5；IRDCollisionObject → IRDActiveObject RTDynamicCast 通过者
// 经 vt+760(1, 伤害号, 3, nArg2, 0) 施加；末转 ·0x5AA130 走反击/架招触发判定
// ------------------------------------------------------------
int /*thiscall*/ sub_5AA200(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 碰撞体反击反馈（this+8608 == 1 时对撞方 vt+760 附加伤害号）
{
  int pObj; // eax
  float v9; // [esp+0h] [ebp-1Ch]
  float pThis_2E0; // [esp+24h] [ebp+8h]
  int v11; // [esp+2Ch] [ebp+10h]

  if ( (uint8_t)nArg4 == 0 && *(this + 8608) == 1 )  // this+8608 = uAI8608
  {
    pThis_2E0 = (float)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 736))(this);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
    v11 = 15;
    if ( (double)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 740))(this) * 0.5 <= pThis_2E0 )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
      v11 = 5;
    pObj = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    if ( pObj != 0 )
    {
      v9 = (float)v11;
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int, uint32_t))(*(uint32_t *)pObj + 760))(pObj, 1, LODWORD(v9), 3, nArg2, 0);  // 调用虚函数（虚表槽 +760）【推断: ★ 状态施加通用壳（a2=状态id, a3=强度, a4/a5=…】
    }
  }
  return sub_5AA130(this, nArg2, nArg3, nArg4);  // 调 受击/架招一次性标志 + 反击触发判定
}



// ============================================================
// 【分区 10】飞龙 Flydragon（0x5AC1F0-0x5ACF40）
// 证据：FLYDRAGON_MAD/FIRE/HIT/DMG/DIE/CRY/FLAP 全套播报、FLAMETHROWER_LOOP、
//       Particle/FireBreath.ptl 火息、FDRG_DIE、B_SELLION_01 登场曲

// AI 主状态门（this+200, sub_699000）
// ------------------------------------------------------------
// 0x5AC1F0 sub_5AC1F0 —— 相位停滞 10 秒自解（this+8780/8776 相位镜像 + 10000ms 门）
// ·0x5AB9B0 前置；当前帧 (vt+200)+148 与 this+8780（相位镜像）一致时：this+8776 计时戳
// 空则记 clock_now，随后若已过期 10000ms（0x2710）且 vt+308 校验通过则 vt+1256 自解；
// 相位不一致时清 this+8776 并刷新 this+8780 = 帧 +148
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5AC1F0(uint32_t *this)  // 函数: 相位停滞 10 秒自解（this+8780/8776 相位镜像 + 10000ms 门）
{
  unsigned int result; // eax
  int v2; // edx

  sub_5AB9B0();
  if ( *(this + 2195) == *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  {
    if ( *(this + 2194) == 0 )
      *(this + 2194) = sub_699000((int)(this + 9));  // this+36 = 状态字
    result = sub_699000((int)(this + 9)) - *(this + 2194);  // 【clock_now(clk)】
    if ( result > 0x2710 )  // 比较常量 0x2710（= 10000）
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)result == 1 )
        return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1256))(this);  // 调用虚函数（虚表槽 +1256）
    }
  }
  else
  {
    v2 = *this;
    *(this + 2194) = 0;
    result = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(v2 + 200))(this) + 148);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    *(this + 2195) = result;
  }
  return result;
}



// 狂暴 AI：FLYDRAGON_MAD 播报（90L；飞龙狂暴化）
// ------------------------------------------------------------
// 0x5AC200 sub_5AC200 —— 飞龙狂暴/突进状态机（this+6556 主状态镜像 8 门 + FLYDRAGON_MAD）
// this+6556==8（攻击）且 this+7028 段号槽为 1/2 时 vt+216(45230) 写表现槽；ArgList==8 且
// 段参数 (fArg3)+4 的 +4 == 1 时按 this+7252 关联体 x 差 < this+7620+16 阈值清该标记；
// super ·0x4E33D0 后 ArgList==8：段号 1/2 走 ·0x5AB5B0 + this+8628 = clock_now，
// 段号 2 喊 FLYDRAGON_MAD 并 ·0x4DB130(24,0) 随机语音；段号 0 且 vt+308 通过时 10% 概率
// 经 vt+672(3) 与 ·0x4954C0 三次取反算朝向，vt+876 写速率、vt+896 写位移（突进）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AC200(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 飞龙狂暴/突进状态机（this+6556 主状态镜像 8 门 + FLYDRAGON_MAD）
{
  int pTarget7252; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int result; // eax
  int nRand; // eax
  int v10; // et2
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // eax
  int v21; // [esp+18h] [ebp+Ch]

  if ( *(this + 1639) == 8  // this+6556 = 主状态镜像
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 45230);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
  }
  if ( ArgList == 8 && *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) == 1 )  // 调 取 64 位值低 32 位
  {
    pTarget7252 = *(this + 1813);  // this+7252 = pTarget7252
    if ( pTarget7252 != 0 )
    {
      v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      if ( (signed int)abs32((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget7252 + 120))(pTarget7252) - v21) < *(uint32_t *)(*(this + 1905) + 16) )  // this+7620 = 速度/属性参数对象
        *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) = 0;  // 调 取 64 位值低 32 位
    }
  }
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      sub_5AB5B0(this);
      *(this + 2152) = sub_699000((int)(this + 1910));  // this+8608 = uAI8608
      result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result == 2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
          this,
          "FLYDRAGON_MAD",  // 资源/动画 TAG FLYDRAGON_MAD
          -1,
          0,
          0);
        return sub_4DB130(24, 0);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      }
    }
    else
    {
      result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result == 0 )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        if ( (uint8_t)result != 0 )
        {
          nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
          v10 = nRand % 100;
          result = nRand / 100;
          if ( v10 < 10 )
          {
            v11 = *this;
            v12 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 672))(this, 3, 0);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
            v13 = sub_4954C0(v12);  // 调 槽对乘积读取（+816/+830）
            v14 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*this + 672))(this, 3, 0, -v13);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
            v15 = sub_4954C0(v14);  // 调 槽对乘积读取（+816/+830）
            v16 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 672))(this, 3, v15);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
            v17 = sub_4954C0(v16);  // 调 槽对乘积读取（+816/+830）
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(v11 + 876))(this, 0, v17);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
            v18 = *this;
            v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 188))(this);  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
            v20 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, v19);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            return (*(int (/*thiscall*/ **)(uint32_t *, int))(v18 + 896))(this, v20);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
          }
        }
      }
    }
  }
  return result;
}



// 火焰喷射：FLYDRAGON_FIRE + FLAMETHROWER_LOOP 播报（this+8625/8626 相位, 49L）
// ------------------------------------------------------------
// 0x5AC3D0 sub_5AC3D0 —— 火焰喷射（命中判定走帧 +170 + FireBreath 粒子发射 + 播报）
// vt+200 帧 +170 置位（判定帧）时：以 this+8628 粒子句柄 vt+40 触发、vt+92 取位置块，
// vt+80(2,0,块) 取容器后 ·0x4600B0 发射，参数为 vt+128(高度)+43 / vt+124 / vt+120 ±47
// （按 vt+152 朝向取符号）；未到判定帧而 this+8632 倒计时 > 0 时 vt+12 复位句柄并连喊
// FLYDRAGON_FIRE 与 FLAMETHROWER_LOOP(45230)，清 this+8625/8626 两相位字节
// ------------------------------------------------------------
void /*thiscall*/ sub_5AC3D0(uint32_t **this)  // 函数: 火焰喷射（命中判定走帧 +170 + FireBreath 粒子发射 + 播报）
{
  int fld_e2151; // edi
  int v3; // ebx
  int v4; // edx
  void *v5; // eax
  int v6; // [esp-Ch] [ebp-34h]
  int v7; // [esp-8h] [ebp-30h]
  int v8; // [esp-4h] [ebp-2Ch]
  uint8_t v9[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v11; // [esp+24h] [ebp-4h]

  if ( *(uint8_t *)(**(this + 1554) + 170) != 0 )  // this+6216 = 资源/帧游标表
  {
    fld_e2151 = **(this + 2151);  // this+8604 = bAI8604
    v8 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) + 43;
    v7 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[31])(this);
    v3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) != 1 ? -47 : 47;
    v6 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) + v3;
    (*(void (/*thiscall*/ **)(uint32_t))(fld_e2151 + 40))(*(this + 2151));  // this+8604 = bAI8604
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 2151) + 92))(*(this + 2151), v9);  // this+8604 = bAI8604
    v4 = (int)*this;
    v11 = 0;
    v5 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int, uint32_t, uint8_t *))(v4 + 80))(this, 2, 0, v9);  // 调用虚函数（虚表槽 +80）
    sub_4600B0(v5, v6, v7, v8);  // 调 演播层注册(槽号)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
  }
  else if ( sub_699000((int)(this + 2153)) > 0 )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 2151) + 12))(*(this + 2151), 0);  // this+8604 = bAI8604
    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "FLYDRAGON_FIRE", -1, 0, 0);  // 资源/动画 TAG FLYDRAGON_FIRE
    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
      this,
      "FLAMETHROWER_LOOP",  // 资源/动画 TAG FLAMETHROWER_LOOP
      45230,
      0,
      0);
    *((uint8_t *)this + 8625) = 0;
    *((uint8_t *)this + 8626) = 0;
  }
}



// 飞龙语音装载：FLYDRAGON_HIT/DMG/DIE + FLYDRAGON_CRY 龙吟（this+8608/8692 相位）
// ------------------------------------------------------------
// 0x5AC500 sub_5AC500 —— 飞龙语音装载（FLYDRAGON_HIT/DMG/DIE + FLYDRAGON_CRY 龙吟）
// this+6792..6808 写 2,2,2,3,4（伤害类型/音效映射），·0x4015C0 构造 FLYDRAGON_HIT/DMG/DIE
// 与 FLYDRAGON_CRY 四字符串；vt+384 出场参数面写 this+8600 与 this+7732；清 this+8608、
// this+8692 两相位字节，this+8616/8620 写 2；末 ·0x4DE5E0 装载文案条目（5000/10000 倒计时）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AC500(uint32_t *this)  // 函数: 飞龙语音装载（FLYDRAGON_HIT/DMG/DIE + FLYDRAGON_CRY 龙吟）
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  char v6; // [esp-24h] [ebp-34h] BYREF
  void *v7; // [esp-20h] [ebp-30h]
  int v8; // [esp-1Ch] [ebp-2Ch]
  int v9; // [esp-18h] [ebp-28h]
  int v10; // [esp-14h] [ebp-24h]
  int v11; // [esp-10h] [ebp-20h]
  int v12; // [esp-Ch] [ebp-1Ch]
  int v13; // [esp-8h] [ebp-18h]
  size_t v14; // [esp-4h] [ebp-14h]
  char *v15; // [esp+Ch] [ebp-4h]

  v14 = 13;
  v13 = (int)"FLYDRAGON_HIT";  // 资源/动画 TAG FLYDRAGON_HIT
  *(this + 1698) = 2;  // this+6792 = 炮车/子类参数面槽 1
  *(this + 1699) = 2;  // this+6796 = 炮车/子类参数面槽 2
  *(this + 1700) = 2;  // this+6800 = 炮车/子类参数面槽 3
  *(this + 1701) = 3;  // this+6804 = 炮车/子类参数面槽 4
  *(this + 1702) = 4;  // this+6808 = 炮车/子类参数面槽 5
  sub_4015C0((void *)v13, v14);  // 【std::string构造赋值】
  sub_4015C0("FLYDRAGON_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("FLYDRAGON_DIE", 0xDu);  // 【std::string构造赋值】
  v2 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v3 = *this;
  v14 = 1;
  *(this + 2150) = v2;  // this+8600 = uAI8600
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, size_t))(v3 + 384))(this, v14);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v14 = 10000;
  v13 = 5000;
  v15 = &v6;
  *(this + 1933) = v4;  // this+7732〔f_1E34〕
  *((uint8_t *)this + 8608) = 0;  // this+8608 = uAI8608
  *(this + 2154) = 2;  // this+8616 = uAI8616
  *(this + 2153) = 2;  // this+8612 = uAI8612
  *((uint8_t *)this + 8692) = 0;  // this+8692 【推断】子类 AI 向量槽
  v12 = 15;
  v11 = 0;
  LOBYTE(v7) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0("FLYDRAGON_CRY", 0xDu);  // 【std::string构造赋值】
  return sub_4DE5E0(v6, v7, v8, v9, v10, v11, v12, v13, v14);  // 调 文案条目装载 + 随机倒计时（0x4DE410 的配套件）
}



// 振翅 AI：FLYDRAGON_FLAP 播报（this+200/8600/8604/8608 相位, 57L）
// ------------------------------------------------------------
// 0x5AC5E0 sub_5AC5E0 —— 振翅/落地状态机（vt+840 == 8 分派段号 + FLYDRAGON_FLAP）
// ·0x4E1780 前置；攻击态 8 下按 this+7028 段号：1 走 ·0x5AC3D0 火焰喷射；2 走 ·0x5AC3D0 +
// this+8604 句柄 vt+68 判定帧且 vt+308 通过时 vt+560 归还状态，并 1000ms 门内
// （clock_now）·0x5AA420 + vt+352 且刷新 this+8608；末段：帧号 == this+6164 主状态镜像
// 且帧 +148==3 且 this+8600 未置位时喊 FLYDRAGON_FLAP 并置位，帧 +148==0 则复位
// ------------------------------------------------------------
int /*thiscall*/ sub_5AC5E0(int this)  // 函数: 振翅/落地状态机（vt+840 == 8 分派段号 + FLYDRAGON_FLAP）
{
  int result; // eax

  sub_4E1780((uint32_t *)this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( sub_41A5E0(this + 7028) == 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      sub_5AC3D0((uint32_t **)this);  // 调 火焰喷射（命中判定走帧 +170 + FireBreath 粒子发射 + 播报）
    }
    else if ( sub_41A5E0(this + 7028) == 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      sub_5AC3D0((uint32_t **)this);  // 调 火焰喷射（命中判定走帧 +170 + FireBreath 粒子发射 + 播报）
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8604) + 68))(*(uint32_t *)(this + 8604)) != 0  // 调用虚函数（虚表槽 +68）【推断: 观察者组件懒创建（0x10 字节）】
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      }
      if ( *(uint32_t *)(this + 8608) + 1000 <= (unsigned int)sub_699000(this + 7640) )  // 【clock_now(clk)】
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
          sub_5AA420(this);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);  // 调用虚函数（虚表槽 +352）【推断: [RTTI: IRDCollisionObject__vmt16…】
        *(uint32_t *)(this + 8608) = sub_699000(this + 7640);  // 调 【clock_now(clk)】
      }
    }
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  if ( result == *(uint32_t *)(this + 6164) )  // this+6164 帧游标对象槽
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) != 3  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      || *(uint8_t *)(this + 8600) != 0 )  // this+8600 喷火塞利昂资源对象
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      if ( *(uint32_t *)(result + 148) == 0 )
        *(uint8_t *)(this + 8600) = 0;  // this+8600 喷火塞利昂资源对象
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                 this,
                 "FLYDRAGON_FLAP",  // 资源/动画 TAG FLYDRAGON_FLAP
                 -1,
                 0,
                 0);
      *(uint8_t *)(this + 8600) = 1;  // this+8600 喷火塞利昂资源对象
    }
  }
  return result;
}



// 登场曲：sub_406D60 写 "B_SELLION_01"（飞龙曲目槽, 75L）
// ------------------------------------------------------------
// 0x5AC710 sub_5AC710 —— 同构 ·0x5A9290（飞龙相位机, 差异：BGM 曲名 B_SELLION_01）
// ·0x4E0120 前置；this+1787 相位分派：0 = vt+1284 出场触发 + 困难级（this+1943==3）
// ·0x406D60 写 B_SELLION_01；4 = 有关联对象且 10% 概率 vt+1104 写 5，否则写 13；
// 5 = 有关联对象且 30% 概率写 4，否则写 13；13/14/15 = 有关联对象时写回 4
// ------------------------------------------------------------
int /*thiscall*/ sub_5AC710(int *this)  // 函数: 同构 ·0x5A9290（飞龙相位机, 差异：BGM 曲名 B_SELLION_01）
{
  int result; // eax
  bool v3; // zf
  int nRand2; // eax
  int v5; // et2
  int nRand; // eax
  int v7; // et2

  sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148 = nBigState
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
      if ( *(this + 1943) == 3 )  // this+7772 = nCounterState
        result = sub_406D60("B_SELLION_01");  // 调 std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == 0 )  // this+7252 = pTarget7252
        goto LABEL_11;
      nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
      v7 = nRand % 100;
      result = nRand / 100;
      if ( v7 < 10 )
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        if ( (uint8_t)result != 0 )
          result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);  // 调用虚函数（虚表槽 +1104）
      }
      break;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
      {
        nRand2 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
        v5 = nRand2 % 100;
        result = nRand2 / 100;
        if ( v5 < 30 )
        {
          result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
          v3 = (uint8_t)result == 0;
          goto LABEL_5;
        }
      }
      else
      {
LABEL_11:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
      }
      break;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      result = *(this + 1813);  // this+7252 = pTarget7252
      if ( result != 0 )  // 若结果非 0（成功）
        goto LABEL_16;
      break;
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252 = pTarget7252
      v3 = result == 0;
LABEL_5:
      if ( !v3 )
LABEL_16:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调用虚函数（虚表槽 +1104）
      break;
    default:
      return result;
  }
  return result;
}



// AI 相位辅助（100L；this+8608）
// ------------------------------------------------------------
// 0x5AC830 sub_5AC830 —— 低空扑咬选目标（vt+560 写态 16；this+8608 段号门 == 2）
// 前置：this+8612==2 且 this+8608==0 且 vt+128 高度槽==15（低空）；
// ·0x4E0CD0(17, 0, 清单, 300) 取 300 半径附近对象；逐个 |vt+124 差| < 40 命中后按朝向
// （vt+152 0=向左 1=向右）判 dx ∈ (50,300) 且 20% 概率 → vt+560 写态 16 并返回 1
// ------------------------------------------------------------
char /*thiscall*/ sub_5AC830(uint32_t *this)  // 函数: 低空扑咬选目标（vt+560 写态 16；this+8608 段号门 == 2）
{
  uint32_t *Block2; // ecx
  int v3; // eax
  unsigned int v4; // ebx
  int *v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edi
  int *v10; // edi
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // edi
  int v15; // edi
  void *v17; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v19; // [esp+14h] [ebp-18h]
  int v20; // [esp+18h] [ebp-14h]
  int v21; // [esp+1Ch] [ebp-10h]
  int v22; // [esp+28h] [ebp-4h]

  if ( *(this + 2153) == 2  // this+8612 = uAI8612
    && *((uint8_t *)this + 8608) == 0  // this+8608 = uAI8608
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) == 15 )  // 调用虚函数（虚表槽 +128）
  {
    Block = nullptr;
    v19 = 0;
    v20 = 0;
    v22 = 0;
    sub_4E0CD0(17, 0, &v17, 300);  // 调 按条件号收集对象（阵营/距离/归属过滤，返回计数）
    Block2 = Block;
    if ( Block != nullptr )  // 若 Block 有效（非空）
    {
      v3 = v19;
      if ( (v19 - (int)Block) >> 2 != 0 )
      {
        v4 = 0;
        while ( Block2 != nullptr )  // 当 Block2 != nullptr 循环
        {
          if ( v4 >= (v3 - (int)Block2) >> 2 )
            goto LABEL_21;
          v5 = (int *)Block2[v4];
          v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
          v7 = *v5;
          v21 = v6;
          v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 124))(v5);  // 调用虚函数（虚表槽 +124）
          if ( (int)abs32(v21 - v8) < 40 )
          {
            if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            {
              v9 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v4) + 120))(*((uint32_t *)Block + v4));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v9 < 300 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              {
                v10 = *((int **)Block + v4);
                v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
                v12 = *v10;
                v21 = v11;
                v13 = (*(int (/*thiscall*/ **)(int *))(v12 + 120))(v10);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
                if ( v21 - v13 > 50 && rand() % 100 < 20 )  // 调 以 16 位种子状态递推并返回 15 位结果
                  goto LABEL_19;
              }
            }
            if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            {
              v14 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v4) + 120))(*((uint32_t *)Block + v4));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              if ( v14 - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < 300 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              {
                v15 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v4) + 120))(*((uint32_t *)Block + v4));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
                if ( v15 - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) > 50 && rand() % 100 < 20 )  // 调 以 16 位种子状态递推并返回 15 位结果
                {
LABEL_19:
                  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 16, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
                  sub_5E5260(&v17);  // 调 动画子对象清理临时缓冲
                  return 1;  // 返回 1(成功)
                }
              }
            }
          }
          v3 = v19;
          Block2 = Block;
          ++v4;
        }
      }
      else
      {
LABEL_21:
        j__free(Block2);  // 调 堆释放
      }
    }
  }
  return 0;
}



// AI 相位辅助（79L；this+8608）
// ------------------------------------------------------------
// 0x5ACA40 sub_5ACA40 —— 高空扑咬选目标（vt+560 写态 14；this+8632 高度下探门）
// 前置：this+8616/8612 均 == 2、this+8608==0、vt+840==0 且 vt+128 高度 >= this+324（已低于高度阈值）；
// ·0x4E0CD0(17, 0, 清单, 300) 取附近对象；|vt+124 差| < 40 且按朝向判 dx ∈ (50,300) 且
// 20% 概率 → vt+560 写态 14（蓄力/俯冲前）并返回 1；与 ·0x5AC830 同构（差异：写态与高度门方向）
// ------------------------------------------------------------
char /*thiscall*/ sub_5ACA40(uint32_t *this)  // 函数: 高空扑咬选目标（vt+560 写态 14；this+8632 高度下探门）
{
  int v2; // ecx
  int v3; // eax
  unsigned int i; // ebx
  int *v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int nRand; // edi
  int v10; // edi
  int v11; // edi
  int v12; // edi
  void *v14; // [esp+Ch] [ebp-20h] BYREF
  int v15; // [esp+10h] [ebp-1Ch]
  int v16; // [esp+14h] [ebp-18h]
  int v17; // [esp+18h] [ebp-14h]
  int v18; // [esp+1Ch] [ebp-10h]
  int v19; // [esp+28h] [ebp-4h]

  if ( *(this + 2154) == 2  // this+8616 = uAI8616
    && *(this + 2153) == 2  // this+8612 = uAI8612
    && *((uint8_t *)this + 8608) == 0  // this+8608 = uAI8608
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) >= *(this + 81) )  // this+324 = 购买上下文 id（0x550480: dword
  {
    v15 = 0;
    v16 = 0;
    v17 = 0;
    v19 = 0;
    sub_4E0CD0(17, 0, &v14, 300);  // 调 按条件号收集对象（阵营/距离/归属过滤，返回计数）
    v2 = v15;
    if ( v15 != 0 )
    {
      v3 = v16;
      if ( (v16 - v15) >> 2 != 0 )  // 向量元素数 = (end−begin)/4
      {
        for ( i = 0; v2 != 0 && i < (v3 - v2) >> 2; ++i )  // 向量元素数 = (end−begin)/4
        {
          v5 = *(int **)(v2 + 4 * i);
          v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
          v7 = *v5;
          v18 = v6;
          v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 124))(v5);  // 调用虚函数（虚表槽 +124）
          if ( (int)abs32(v18 - v8) < 40 )
          {
            if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              && (nRand = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v15 + 4 * i) + 120))(*(uint32_t *)(v15 + 4 * i)),  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
                  (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - nRand < 300)  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              && (v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v15 + 4 * i) + 120))(*(uint32_t *)(v15 + 4 * i)),  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
                  (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v10 > 50)  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              && rand() % 100 < 20  // 调 以 16 位种子状态递推并返回 15 位结果
              || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              && (v11 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v15 + 4 * i) + 120))(*(uint32_t *)(v15 + 4 * i)))  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
               - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < 300  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              && (v12 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v15 + 4 * i) + 120))(*(uint32_t *)(v15 + 4 * i)))  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
               - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) > 50  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              && rand() % 100 < 20 )  // 调 以 16 位种子状态递推并返回 15 位结果
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
              sub_5E5260(&v14);  // 调 动画子对象清理临时缓冲
              return 1;  // 返回 1(成功)
            }
          }
          v3 = v16;
          v2 = v15;
        }
      }
    }
    sub_5E5260(&v14);  // 调 动画子对象清理临时缓冲
  }
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5ACC70 sub_5ACC70 —— 按 vt+128 高度槽分派扑咬（15 低空 / >=130 高空）
// 7 行三分支：==15 走 ·0x5AC830 低空扑咬；<130 直接 0；否则走 ·0x5ACA40 高空扑咬
// ------------------------------------------------------------
char /*thiscall*/ sub_5ACC70(uint32_t *this)  // 函数: 按 vt+128 高度槽分派扑咬（15 低空 / >=130 高空）
{
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) == 15 )  // 调用虚函数（虚表槽 +128）
    return sub_5AC830(this);  // 调 低空扑咬选目标（vt+560 写态 16；this+8608 段号门 == 2）
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) < 130 )  // 调用虚函数（虚表槽 +128）
    return 0;
  return sub_5ACA40(this);  // 调 高空扑咬选目标（vt+560 写态 14；this+8632 高度下探门）
}



// AI 复合（sub_431230+sub_699000+RTTI cast, 55L）
// ------------------------------------------------------------
// 0x5ACCB0 sub_5ACCB0 —— 碰撞反击触发（打回 60.0f + vt+560 写态 4 + 10 秒蓄力戳）
// 条件：nArg2 对象 vt+40(nArg2,17)==1 且 nArg4 为 0 且 this+7028 段号槽 == 1；
// RTDynamicCast IRDCollisionObject→IRDActiveObject 后 vt+760(3, 60.0f(1120403456), 2, this, 0)
// 打回伤害；vt+308 通过则 vt+764 镜像反击、this+8604 = clock_now + 10000（×10000 蓄力戳）；
// ·0x431230 打包 [4,0,1,200,200] 经 vt+560(4, 参数块) 写态 4（受击后置），vt+564 收尾，
// 末转 ·0x5AA130 反击/架招触发判定
// ------------------------------------------------------------
int /*thiscall*/ sub_5ACCB0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 碰撞反击触发（打回 60.0f + vt+560 写态 4 + 10 秒蓄力戳）
{
  int nArg22; // edi
  int pObj; // eax
  void *pBuf[4]; // [esp+8h] [ebp-20h] BYREF
  int v9; // [esp+18h] [ebp-10h] BYREF
  int v10; // [esp+24h] [ebp-4h]

  nArg22 = nArg2;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 1  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    && (uint8_t)nArg4 == 0
    && sub_41A5E0((unsigned int)(this + 1757)) == 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    pObj = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    if ( pObj != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int, uint32_t *, uint32_t))(*(uint32_t *)pObj + 760))(  // 调用虚函数（虚表槽 +760）【推断: ★ 状态施加通用壳（a2=状态id, a3=强度, a4/a5=…】
        pObj,
        3,
        1120403456,  // 浮点常量 100.0f
        2,
        this,
        0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t *, uint32_t))(*this + 764))(this, 3, 2, this, 0);  // 调用虚函数（虚表槽 +764）
        *(this + 2151) = sub_699000((int)(this + 9)) + 10000;  // this+8604 = bAI8604
        memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
        v10 = 0;
        v9 = 4;
        sub_431230((int)pBuf, &v9);  // 调 uint32 vector push_back
        v9 = 0;
        sub_431230((int)pBuf, &v9);  // 调 uint32 vector push_back
        v9 = 1;
        sub_431230((int)pBuf, &v9);  // 调 uint32 vector push_back
        v9 = 200;
        sub_431230((int)pBuf, &v9);  // 调 uint32 vector push_back
        v9 = 200;
        sub_431230((int)pBuf, &v9);  // 调 uint32 vector push_back
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 4, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);  // 调用虚函数（虚表槽 +564）【推断: ★ 位移同步包 vt+234（会话 3 定案：UDP type=…】
        v10 = -1;
        sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
        nArg22 = nArg2;
      }
    }
  }
  return sub_5AA130(this, nArg22, nArg3, nArg4);  // 调 受击/架招一次性标志 + 反击触发判定
}



// 飞龙装载 2：FLYDRAGON_HIT/DMG + FDRG_DIE 语音 + Particle/FireBreath.ptl 火息粒子（41L）
// ------------------------------------------------------------
// 0x5ACE30 sub_5ACE30 —— 飞龙火息装载（FLYDRAGON_HIT/DMG + FDRG_DIE 语音 + FireBreath 粒子）
// ·0x4015C0 构造 FLYDRAGON_HIT/FLYDRAGON_DMG/FDRG_DIE 三字符串；this+8600 清零后 vt+688 清场；
// ·0x4EB2C0(1.5) 伤害修正族 1.5；new 0x12C 经 ·0x4C3640 构造 Particle/FireBreath.ptl
// （按 +364 起短字符串容量 +96 < 0x10 走内部缓冲，否则用 +364 长指针）写 this+8604 粒句柄，
// vt+112 挂接；this+8608 = clock_now；末 ·0x4E1390(196612, 100000) 登记倒计时/播报
// ------------------------------------------------------------
int /*thiscall*/ sub_5ACE30(char *this)  // 函数: 飞龙火息装载（FLYDRAGON_HIT/DMG + FDRG_DIE 语音 + FireBreath 粒子）
{
  int v2; // eax
  int *pThis_16C; // eax
  int v4; // edx
  int v6; // [esp+8h] [ebp-10h] BYREF
  int v7; // [esp+14h] [ebp-4h]

  sub_4015C0("FLYDRAGON_HIT", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("FLYDRAGON_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("FDRG_DIE", 8u);  // 【std::string构造赋值】
  v2 = *(uint32_t *)this;
  *(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
  (*(void (/*thiscall*/ **)(char *))(v2 + 688))(this);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
  sub_4EB2C0(1.5);  // 调 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  v7 = 0;
  if ( operator new(0x12Cu) != nullptr )  // operator new 分配 300 字节
  {
    if ( *((uint32_t *)this + 96) < 0x10u )  // this+384 = 动画件名 SSO 容量判据
      pThis_16C = (int *)sub_4C3640(this + 364, "Particle/FireBreath.ptl", this);  // this+364 动画件名缓冲 SSO 内联首址
    else
      pThis_16C = (int *)sub_4C3640(*((uint32_t *)this + 91), "Particle/FireBreath.ptl", this);  // this+364 = 动画件名缓冲 SSO 内联首址
  }
  else
  {
    pThis_16C = nullptr;
  }
  *((uint32_t *)this + 2151) = pThis_16C;  // this+8604 = bAI8604
  v4 = *pThis_16C;
  v7 = -1;
  (*(void (/*thiscall*/ **)(int *, char *))(v4 + 112))(pThis_16C, this);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
  *((uint32_t *)this + 2152) = sub_699000((int)(this + 7640));  // this+8608 = uAI8608
  v6 = 100000;
  return sub_4E1390(196612, &v6);  // 调 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
}



// ============================================================
// 【分区 11】猎人 Hunter（HH/HM/HA 三型）（0x5ACF40-0x5AE3C0）
// 证据：HUNTER_SPIT/READY/SCREAM/FIND/DMG/DIE/ATK、HUNT_BREATH_LOOP/HUNT_HARD_BREATH_LOOP、
//       HUNT_JUMP、Particle/HunterSpittle.ptl 酸液、Monster/Hunter/{HH,HM,HA}/*.equ

// AI 字段访问
// ------------------------------------------------------------
// 0x5ACF40 sub_5ACF40 —— 消亡通知后出场触发（4 行复合）
// ·0x4D9760 观察者广播后条件收尾，随即 vt+1284 出场/登场触发；【推断】用于尸体消亡链尾接下一段演出
// ------------------------------------------------------------
int /*thiscall*/ sub_5ACF40(void *this)  // 函数: 消亡通知后出场触发（4 行复合）
{
  sub_4D9760();  // 调 观察者广播后条件收尾
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5ACF60 sub_5ACF60 —— 消亡引用清理钩
// ·0x4D9170 对象引用清扫（PVP 场景与 7252/7248/7256 三参照清零）；清扫对象为自身时
// 走 vt+216 表现槽写 9【推断：尸消链尾申报】
// ------------------------------------------------------------
int /*thiscall*/ sub_5ACF60(void *this, void *pArg2)  // 函数: 消亡引用清理钩
{
  int result; // eax

  result = sub_4D9170(pArg2);  // 调 消亡通知
  if ( this == pArg2 )
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
  return result;
}



// AI 相位辅助（63L）
// ------------------------------------------------------------
// 0x5ACF90 sub_5ACF90 —— 待机追敌朝向对准（行为字 vt+1104 驱动）
// ·0x4E0120 基础 AI 调度后：行为字 1787 非 16 且关联对象 1813 非空时先写 vt+1104(5)，
// 再由 vt+308 本地门 + vt+840 姿态==6（待机）取自身与目标 vt+120/124 的 XY 差，
// 任一轴超 100 即组装象限码，经 vt+896 写方向（0/1 与 +2 组合）；
// 目标为空则直接写 vt+1104(13)【推断：巡逻/寻找态】
// ------------------------------------------------------------
int /*usercall*/ sub_5ACF90@<eax>(uint32_t **pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：待机追敌朝向对准（行为字 vt+1104 驱动）
{
  int result; // eax
  int v5; // edi
  int v6; // eax
  uint32_t *v7; // ebx
  int v8; // edi
  int64_t v9; // rax
  int v10; // ebx
  int v11; // edi
  int v12; // edi
  int v13; // [esp+4h] [ebp-8h]
  int v14; // [esp+4h] [ebp-8h]
  int v15; // [esp+8h] [ebp-4h]

  result = sub_4E0120();  // 调 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  if ( pArg1[1787] != (uint32_t *)16 )
  {
    if ( pArg1[1813] != nullptr )
    {
      ((void (/*thiscall*/ *)(uint32_t **, int))(*pArg1)[276])(pArg1, 5);
      result = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[77])(pArg1);
      if ( (uint8_t)result != 0 )
      {
        result = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[210])(pArg1);
        if ( result == 6 )
        {
          v5 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1[1813] + 120))(pArg1[1813], nArg3, nArg2);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          v6 = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[30])(pArg1);
          v7 = pArg1[1813];
          v8 = abs32(v6 - v5);  // v8 = 调 abs32
          v13 = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[31])(pArg1);
          v9 = v13 - (*(int (/*thiscall*/ **)(uint32_t *))(*v7 + 124))(v7);  // 调用虚函数（虚表槽 +124）
          v10 = (HIDWORD(v9) ^ v9) - HIDWORD(v9);  // 调 取 64 位值高 32 位
          v14 = 4;
          v15 = 4;
          if ( v8 > 100 )
          {
            v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1[1813] + 120))(pArg1[1813]);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
            v14 = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[30])(pArg1) < v11;
          }
          if ( v10 > 100 )
          {
            v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1[1813] + 124))(pArg1[1813]);  // 调用虚函数（虚表槽 +124）
            v15 = (((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[31])(pArg1) < v12) + 2;
          }
          return ((int (/*thiscall*/ *)(uint32_t **, int, int))(*pArg1)[224])(pArg1, v14, v15);
        }
      }
    }
    else
    {
      return ((int (/*thiscall*/ *)(uint32_t **, int))(*pArg1)[276])(pArg1, 13);
    }
  }
  return result;
}



// 【vmt200 命中处理器覆写】猎人系小型覆写（13L；虚表 0x6DF754/0x6DFC7C/0x6E01A4/0x6E06CC 四张 +512 槽）
// ------------------------------------------------------------
// 0x5AD0B0 sub_5AD0B0 —— vmt200 命中门：类型 1 拦截
// 命中类型 nArg3 为 1 时直接返 0（命中被吞），否则透传给 ·0x4DA3B0
// 命中包分发前置（研究 §1.1 case 0x13 客户端入口）
// ------------------------------------------------------------
int /*stdcall*/ sub_5AD0B0(int nArg1, int nArg2, int nArg3)  // 函数: vmt200 命中门：类型 1 拦截
{
  if ( (uint8_t)nArg3 == 1 )
    return 0;
  else
    return sub_4DA3B0(nArg1, nArg2, nArg3);  // 调 ★ 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AD0E0 sub_5AD0E0
// 基类帧驱动转发（thunk 桩）：唯一语句转调 ·0x4E1BE0；
// HH 猎人系虚表槽的默认继承实现
// ------------------------------------------------------------
// attributes: thunk
int sub_5AD0E0()  // 实现：HH 猎人系虚表槽的默认继承实现
{
  return sub_4E1BE0();  // 调 仇恨目标重选（取仇恨值最大且 vt+724==0 的敌人）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AD0F0 sub_5AD0F0 —— 表现序列启动（动画对象参数 3/100）
// 取 this+116 容器 +132 动画对象交 ·0x424120(obj,3,100) 写 +50/+51 参数槽，
// 再推 ·0x49C620(8,0,0) 与 ·0x49C5F0(9,0,0,400) 两条表现序列
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD0F0(uint32_t *this)  // 函数: 表现序列启动（动画对象参数 3/100）
{
  sub_424120(*(uint32_t **)(*(this + 29) + 132), 3, 100);  // 调 屏幕震动启动
  sub_49C620(8, 0, 0);  // 调 命令下发包装（组 id = this+4，值重复两遍）
  return sub_49C5F0(9, 0, 0, 400);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD130 sub_5AD130 —— 网络包封装发送（起包 29 + 坐标参数）
// 全局包构造器 dword_8F8520 起包 29，依次压入 vt+48/vt+52 与本地玩家 dword_8F7C04
// 的 vt+52、nArg2 参量；nArg2 落 14/15（架招/施放）时追加随机数，
// 最后 vt+60(1,-1) 发送【推断：相位同步包】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD130(void *this, int nArg2)  // 函数: 网络包封装发送（起包 29 + 坐标参数）
{
  int v3; // edi
  int pThis_30; // eax
  int v5; // edi
  int pThis_34; // eax
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int nRand; // eax

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
  v3 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  pThis_30 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);  // 调用虚函数（虚表槽 +48）
  (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, pThis_30);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  v5 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  pThis_34 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);  // 调用虚函数（虚表槽 +52）
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_34);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  v7 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 调用虚函数（虚表槽 +52）
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg2);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  if ( (uint16_t)nArg2 >= 0xEu && (uint16_t)nArg2 <= 0xFu )
  {
    v9 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
    nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
    (*(void (/*thiscall*/ **)(int, int))(v9 + 40))(dword_8F8520, nRand);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
  }
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
}



// 技能播报：HUNTER_SPIT（吐酸）
// ------------------------------------------------------------
// 0x5AD1E0 sub_5AD1E0 —— 技能播报 HUNTER_SPIT 吐酸（vt+580 发射）
// vt+152 态查询选 80/70 参量，vt+128 取位姿基值 +50，经 vt+580(this,30003,0,nArg2,...)
// 投递 30003 号弹体，尾调 vt+212 播报 HUNTER_SPIT 语音 TAG
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD1E0(int *this, int nArg2)  // 函数: 技能播报 HUNTER_SPIT 吐酸（vt+580 发射）
{
  int v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // eax

  v3 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  v4 = *this;
  v5 = v3 != 0 ? 80 : 70;
  v6 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 128))(this, 4, 0, 0, 0);  // 调用虚函数（虚表槽 +128）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t, int, uint32_t, int))(v4 + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
    this,
    30003,
    0,
    nArg2,
    0,
    v5,
    0,
    v6 + 50);
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HUNTER_SPIT", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD250 sub_5AD250 —— 远程攻击抉择：随机掷 + 困难级 48001 弹体
// vt+308 本地门通过后掷 rand100：>=10 时若 this+1943==3（困难级）再掷 rand100，
// <50 则 vt+580 投 48001(2,...) 并接 ·0x49C970(8)/·0x49C5F0(9,...,1000) 表现；
// <10 则改走 ·0x5AD130(this,16) 包发送（重呼吸相位）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD250(uint32_t *this)  // 函数: 远程攻击抉择：随机掷 + 困难级 48001 弹体
{
  int result; // eax
  int nRand; // eax
  int v4; // et2
  int nRand2; // eax
  int v6; // et2

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
    v4 = nRand % 100;
    result = nRand / 100;
    if ( v4 >= 10 )
    {
      if ( *(this + 1943) == 3 )  // this+7772 = nCounterState
      {
        nRand2 = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
        v6 = nRand2 % 100;
        result = nRand2 / 100;
        if ( v6 < 50 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
            this,
            48001,
            2,
            0,
            0,
            0,
            0,
            0,
            4,
            0,
            0,
            0);
          sub_49C970(8, 0, 0);  // 调 池分配包装（this+4 复制为第 2/3 参）
          return sub_49C5F0(9, 0, 0, 1000);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
        }
      }
    }
    else
    {
      return sub_5AD130(this, 16);  // 调 网络包封装发送（起包 29 + 坐标参数）
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD2E0 sub_5AD2E0 —— 效果请求 30064（表现启动 + 位置快照）
// ·0x424120(obj,3,100) 与 ·0x49C620(8)/·0x49C5F0(9,...,400) 表现后本地门过，
// 取 vt+120/124/152 三坐标为参调 ·0x4E4A50(this,30064,...) 效果请求族
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD2E0(uint32_t *this)  // 函数: 效果请求 30064（表现启动 + 位置快照）
{
  int result; // eax
  int v3; // eax
  int v4; // [esp-18h] [ebp-1Ch]
  int v5; // [esp-10h] [ebp-14h]

  sub_424120(*(uint32_t **)(*(this + 29) + 132), 3, 100);  // 调 屏幕震动启动
  sub_49C620(8, 0, 0);  // 调 命令下发包装（组 id = this+4，值重复两遍）
  sub_49C5F0(9, 0, 0, 400);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    return sub_4E4A50(this, 30064, 0, v3, v4, 0, v5, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD360 sub_5AD360 —— 效果请求 30022（表现启动 + 位置快照）
// 与 ·0x5AD2E0 同构：先 ·0x424120(动画对象,3,100) 写参数槽、·0x49C620(8,0,0) 与
// ·0x49C5F0(9,0,0,400) 两条表现序列；可行动时取 vt+120/124 坐标 + vt+152 朝向，
// 交 ·0x4E4A50(this, 30022, ...) 生成效果
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD360(uint32_t *this)  // 函数: 效果请求 30022（表现启动 + 位置快照）
{
  int result; // eax
  int v3; // eax
  int v4; // [esp-18h] [ebp-1Ch]
  int v5; // [esp-10h] [ebp-14h]

  sub_424120(*(uint32_t **)(*(this + 29) + 132), 3, 100);  // 调 屏幕震动启动
  sub_49C620(8, 0, 0);  // 调 命令下发包装（组 id = this+4，值重复两遍）
  sub_49C5F0(9, 0, 0, 400);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    return sub_4E4A50(this, 30022, 0, v3, v4, 0, v5, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD3E0 sub_5AD3E0 —— 速率槽调整（减向 · 酸液弹慢速档）
// nArg3==0 时取 vt+672(obj,0)+830 速率浮点槽，经 ·0x41A5E0 读出 −1.0 后
// ·0x41A590 写回并 vt+676(0) 提交；nArg2==0 时清 this+1899 蓄力档槽（归零）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD3E0(uint32_t *this, int nArg2, int nArg3)  // 函数: 速率槽调整（减向 · 酸液弹慢速档）
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) - 1.0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4, v5, v7);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  }
  result = nArg2;
  if ( nArg2 == 0 )
    *(this + 1899) = 0;  // this+7596 = 段号横向偏置
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD450 sub_5AD450 —— 速率槽调整（增向 · 酸液弹快速档，与 ·0x5AD3E0 为对偶）
// 差异：速率浮点槽 +1.0（而非 -1.0）；nArg2==0 时 this+1899 写 50（而非清 0）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD450(uint32_t *this, int nArg2, int nArg3)  // 函数: 速率槽调整（增向 · 酸液弹快速档，与 ·0x5AD3E0 为对偶）
{
  unsigned int v4; // esi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) + 1.0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4, v5, v7);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  }
  result = nArg2;
  if ( nArg2 == 0 )
    *(this + 1899) = 50;  // this+7596 = 段号横向偏置
  return result;
}



// 瞄准 AI：HUNTER_READY 播报（this+200/8604-8606 相位, 28L）
// ------------------------------------------------------------
// 0x5AD4C0 sub_5AD4C0 —— 瞄准态建立：HUNTER_READY 播报
// vt+196 选 1550 容器的表项（nArg3!=14 → 下标 2 否则 3）写姿态槽，vt+200 取动画
// 对象交 ·0x4926A0 帧游标复位，vt+212 播报 HUNTER_READY；随后置
// this+2154=nArg3、8604=1、8605/8606=0、2152=0、2153=nArg2 五相位字段
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD4C0(uint32_t *this, int nArg2, int nArg3)  // 函数: 瞄准态建立：HUNTER_READY 播报
{
  int v4; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1550) + 4 * ((nArg3 != 14) + 2)));  // 调用虚函数（虚表槽 +196）
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  sub_4926A0(v4);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
  result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
             this,
             "HUNTER_READY",  // 资源/动画 TAG HUNTER_READY
             -1,
             0,
             0);
  *(this + 2154) = nArg3;  // this+8616 = uAI8616
  *((uint8_t *)this + 8604) = 1;  // this+8604 = bAI8604
  *((uint8_t *)this + 8606) = 0;  // this+8606 = 子类 AI 标志
  *((uint8_t *)this + 8605) = 0;  // this+8605 = 子类 AI 标志
  *(this + 2152) = 0;  // this+8608 = uAI8608
  *(this + 2153) = nArg2;  // this+8612 = uAI8612
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AD550 sub_5AD550 —— 酸液弹发射启动（1000 号弹体 + 帧复位）
// vt+208 姿态写入 1554 容器首项，同项交 ·0x4926A0 帧游标复位，
// 再 vt+204(this,1000,...) 投 1000 号弹体【推断：吐酸动作对象切换】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD550(int **this)  // 函数: 酸液弹发射启动（1000 号弹体 + 帧复位）
{
  ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[52])(this, **(this + 1554));  // this+6216 = 资源/帧游标表
  sub_4926A0(**(this + 1554));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
  return ((int (/*thiscall*/ *)(int **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
           this,
           1000,
           **(this + 1554),  // this+6216 = 资源/帧游标表
           0,
           0,
           0,
           0);
}



// 酸液弹：引用 Particle/HunterSpittle.ptl（this+200/8605/8606）
// ------------------------------------------------------------
// 0x5AD5A0 sub_5AD5A0 —— 酸液弹单发（帧 6 判定 + 8605/8606 双相位）
// 动画对象 vt+200 帧 +148==6 且 8605==0 时先 ·0x5AD550 启动并置 8605；
// 同帧再判 8606==0 则 vt+588 取 Particle/HunterSpittle.ptl 交 ·0x5AD1E0 吐酸并置 8606
// ------------------------------------------------------------
char /*thiscall*/ sub_5AD5A0(int this)  // 函数: 酸液弹单发（帧 6 判定 + 8605/8606 双相位）
{
  int pThis_C8; // eax
  int pThis_24C; // eax

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) == 6  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    && *(uint8_t *)(this + 8605) == 0 )  // this+8605 子类 AI 标志
  {
    sub_5AD550((int **)this);  // 调 酸液弹发射启动（1000 号弹体 + 帧复位）
    *(uint8_t *)(this + 8605) = 1;  // this+8605 子类 AI 标志
  }
  pThis_C8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  if ( *(uint32_t *)(pThis_C8 + 148) == 6 )  // this+148 第 4 组·+802 增量子倍率
  {
    LOBYTE(pThis_C8) = *(uint8_t *)(this + 8606);  // 调 取 16 位值低 8 位
    if ( (uint8_t)pThis_C8 == 0 )
    {
      pThis_24C = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 588))(this, "Particle/HunterSpittle.ptl");  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
      LOBYTE(pThis_C8) = sub_5AD1E0((int *)this, pThis_24C);  // 调 技能播报 HUNTER_SPIT 吐酸（vt+580 发射）
      *(uint8_t *)(this + 8606) = 1;  // this+8606 【推断】子类 AI 标志
    }
  }
  return pThis_C8;
}



// 酸液弹 2：Particle/HunterSpittle.ptl（67L；this+200/8605/8606/8608）
// ------------------------------------------------------------
// 0x5AD610 sub_5AD610 —— 酸液弹三连发（帧序 8/10/12 + 参数 0/45/320）
// 索引 this+8608 在 v11 表 {8,10,12} 取帧号、v10 表 {0,45,320} 取参量，
// 帧匹配时 vt+588 加载 Particle/HunterSpittle.ptl 拷 0x60 字节后 ·0x5AD1E0 发射；
// 帧 +148==表值+1 时清 8606 并推进索引；另经 this+7252 关联对象 vt+120 与自身
// vt+120 比差驱动 vt+144 距离标志（0/1 两向）【推断：三连吐酸节拍】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD610(int this)  // 函数: 酸液弹三连发（帧序 8/10/12 + 参数 0/45/320）
{
  int *v2; // eax
  uint16_t *pThis_24C; // eax
  int fld_21A0; // edx
  int pThis_C8; // eax
  int fld_21A02; // ecx
  int fld_1C54; // esi
  int result; // eax
  int fld_1C542; // esi
  uint32_t v10[3]; // [esp+8h] [ebp-80h]
  uint32_t v11[3]; // [esp+14h] [ebp-74h]
  uint32_t v12[26]; // [esp+20h] [ebp-68h] BYREF

  v12[25] = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  v2 = *(int **)this;
  v11[0] = 8;
  v11[1] = 10;
  v11[2] = 12;
  v10[0] = 0;
  v10[1] = 45;
  v10[2] = 320;
  if ( *(uint32_t *)(((int (/*thiscall*/ *)(int))v2[50])(this) + 148) == 8 && *(uint8_t *)(this + 8605) == 0 )  // this+8605 子类 AI 标志
  {
    sub_5AD550((int **)this);  // 调 酸液弹发射启动（1000 号弹体 + 帧复位）
    *(uint8_t *)(this + 8605) = 1;  // this+8605 子类 AI 标志
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) == v11[*(uint32_t *)(this + 8608)]  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    && *(uint8_t *)(this + 8606) == 0 )  // this+8606 【推断】子类 AI 标志
  {
    pThis_24C = (uint16_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 588))(this, "Particle/HunterSpittle.ptl");  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
    qmemcpy(v12, pThis_24C, 0x60u);  // 调 内存块拷贝(内联展开)
    fld_21A0 = v10[*(uint32_t *)(this + 8608)];  // this+8608 骑乘/骑手槽
    LOWORD(v12[24]) = pThis_24C[48];  // 调 取 32 位值低 16 位
    v12[18] = fld_21A0;
    sub_5AD1E0((int *)this, (int)v12);  // 调 技能播报 HUNTER_SPIT 吐酸（vt+580 发射）
    *(uint8_t *)(this + 8606) = 1;  // this+8606 【推断】子类 AI 标志
  }
  pThis_C8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  fld_21A02 = *(uint32_t *)(this + 8608);  // this+8608 骑乘/骑手槽
  if ( *(uint32_t *)(pThis_C8 + 148) == v11[fld_21A02] + 1 )  // this+148 第 4 组·+802 增量子倍率
  {
    *(uint8_t *)(this + 8606) = 0;  // this+8606 【推断】子类 AI 标志
    *(uint32_t *)(this + 8608) = fld_21A02 + 1;  // this+8608 骑乘/骑手槽
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) == 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  {
    fld_1C54 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) < fld_1C54 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 144))(this, 1);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  if ( result == 1 )
  {
    fld_1C542 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252));  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    if ( result >= fld_1C542 )
      return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 144))(this, 0);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
  }
  return result;
}



// AI 字段访问（this+8621）
// ------------------------------------------------------------
// 0x5AD780 sub_5AD780 —— 攻击距离门写入（1905 对象 +32 字节）
// 关联对象 1813 非空 且 this+8621==1 且 |自身 vt+120 与目标 vt+120 之差| < this+2150
// （AI 阈值三字段之一）时，把 *(this+1905)+32 置真；否则置假
// 【推断：朝向/出手许可标记】
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5AD780(uint32_t *this)  // 函数: 攻击距离门写入（1905 对象 +32 字节）
{
  unsigned int result; // eax
  int fld_e1813; // edi

  result = *(this + 1813);  // this+7252 = pTarget7252
  *(uint8_t *)(*(this + 1905) + 32) = result != 0  // this+7620 = 速度/属性参数对象
                                 && *((uint8_t *)this + 8621) == 1
                                 && (fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),  // this+7252 = pTarget7252
                                     (signed int)(result = abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - fld_e1813)) < *(this + 2150));  // this+8600 = uAI8600
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD7E0 sub_5AD7E0 —— 速率槽调整（减向变体：nArg3==0 时速率浮点槽 −1.0，
// 并把攻击系数面 this+1905+96 置 0 清增伤标记；nArg2==0 时 this+1899 清零）
// 与 ·0x5AD850 的 +1.0 / 写 1 为对偶
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD7E0(uint32_t *this, int nArg2, int nArg3)  // 函数: 速率槽调整（减向变体：nArg3==0 时速率浮点槽 −1.0，
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) - 1.0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4, v5, v7);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
    *(uint8_t *)(*(this + 1905) + 96) = 0;  // this+7620 = 速度/属性参数对象
  }
  result = nArg2;
  if ( nArg2 == 0 )
    *(this + 1899) = 0;  // this+7596 = 段号横向偏置
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD850 sub_5AD850 —— 速率槽调整（增向变体，与 ·0x5AD7E0 为对偶）
// 差异：速率浮点槽 +1.0；nArg3==0 时另把攻击系数面 this+1905+96 置 1（增伤标记
// 【推断】）；nArg2==0 时 this+1899 写 50（蓄力档满档）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD850(uint32_t *this, int nArg2, int nArg3)  // 函数: 速率槽调整（增向变体，与 ·0x5AD7E0 为对偶）
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) + 1.0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4, v5, v7);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
    *(uint8_t *)(*(this + 1905) + 96) = 1;  // this+7620 = 速度/属性参数对象
  }
  result = nArg2;
  if ( nArg2 == 0 )
    *(this + 1899) = 50;  // this+7596 = 段号横向偏置
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD8C0 sub_5AD8C0 —— 速率槽调整（减向变体：nArg2 落 1..2 时攻击系数面
// this+1905+132 的速率项自乘 0.5 减半；nArg2==0 时 this+1899 蓄力档清零）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD8C0(uint32_t *this, int nArg2, int nArg3)  // 函数: 速率槽调整（减向变体：nArg2 落 1..2 时攻击系数面
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) - 1.0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4, v5, v7);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  }
  result = nArg2;
  if ( nArg2 != 0 )
  {
    if ( nArg2 > 0 && nArg2 <= 2 )  // 若 nArg2 > 0 与/或 nArg2 <= 2
      *(float *)(*(this + 1905) + 132) = *(float *)(*(this + 1905) + 132) * 0.5;  // this+7620 = 速度/属性参数对象
  }
  else
  {
    *(this + 1899) = 0;  // this+7596 = 段号横向偏置
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD950 sub_5AD950 —— 速率槽调整（增向变体，与 ·0x5AD8C0 为对偶）
// 速率浮点槽 +1.0；nArg2 落 1..2 时 this+1905+132 速率项自加自身（×2 加倍，
// 加法写成 x=x+x 是编译产物）；nArg2==0 时 this+1899 写 50
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD950(uint32_t *this, int nArg2, int nArg3)  // 函数: 速率槽调整（增向变体，与 ·0x5AD8C0 为对偶）
{
  unsigned int v4; // esi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) + 1.0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v4, v5, v7);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  }
  result = nArg2;
  if ( nArg2 != 0 )
  {
    if ( nArg2 > 0 && nArg2 <= 2 )  // 若 nArg2 > 0 与/或 nArg2 <= 2
      *(float *)(*(this + 1905) + 132) = *(float *)(*(this + 1905) + 132) + *(float *)(*(this + 1905) + 132);  // this+7620 = 速度/属性参数对象
  }
  else
  {
    *(this + 1899) = 50;  // this+7596 = 段号横向偏置
  }
  return result;
}



// AI 复合字段（this+200/8604/8616..8648, 62L）
// ------------------------------------------------------------
// 0x5AD9E0 sub_5AD9E0 —— 酸液/AI 总调度（8604 相位 + 8616 帧型分流）
// ·0x4E1780 基础 AI 后：8604 相位开启且动画对象非零时，按 this+8616 帧型选
// ·0x5AD5A0 单发或 ·0x5AD610 三连发吐酸（需 7252 关联对象），动画 +170 终止位则清 8604；
// 关相位时 vt+840==6（待机）且帧 +148>=3 经 vt+352 起手并置 8620；
// 其余走 ·0x5AD780 距离门；反应态 4/4 与 8622 相位互锁 vt+216(9)，
// 否则 vt+212 播报 this+8628 串（8648<0x10 走内联 SSO 否则取指针）
// ------------------------------------------------------------
char /*thiscall*/ sub_5AD9E0(int this)  // 函数: 酸液/AI 总调度（8604 相位 + 8616 帧型分流）
{
  int pThis_348; // eax
  int pThis_21B4; // eax

  sub_4E1780((uint32_t *)this);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( *(uint8_t *)(this + 8604) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) != 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  {
    if ( *(uint32_t *)(this + 7252) != 0 )  // this+7252 当前目标/技能对象
    {
      if ( *(uint32_t *)(this + 8616) == 14 )  // this+8616 【推断】钻地相位字节1
        sub_5AD5A0(this);  // 调 酸液弹单发（帧 6 判定 + 8605/8606 双相位）
      else
        sub_5AD610(this);  // 调 酸液弹三连发（帧序 8/10/12 + 参数 0/45/320）
    }
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      *(uint8_t *)(this + 8604) = 0;  // this+8604 吐酸相位开
  }
  else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 6 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 3 && *(uint8_t *)(this + 8620) == 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);  // 调用虚函数（虚表槽 +352）【推断: [RTTI: IRDCollisionObject__vmt16…】
      *(uint8_t *)(this + 8620) = 1;  // this+8620 相位双字节门
    }
  }
  else
  {
    sub_5AD780((uint32_t *)this);  // 调 攻击距离门写入（1905 对象 +32 字节）
  }
  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( pThis_348 != 0
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 184))(this) == 4  // 调用虚函数（虚表槽 +184）【推断: 动画对象 z 倾斜转状态码】
    && (pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 188))(this)) == 4 )  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
  {
    if ( *(uint8_t *)(this + 8622) == 1 )  // this+8622 【推断】循环音锁存
    {
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
      *(uint8_t *)(this + 8622) = 0;  // this+8622 【推断】循环音锁存
    }
  }
  else
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8622);  // 调 取 16 位值低 8 位
    if ( (uint8_t)pThis_348 == 0 )
    {
      if ( *(uint32_t *)(this + 8648) < 0x10u )  // this+8648 【推断】距离解算缓存
        pThis_21B4 = this + 8628;  // this+8628 【推断】指挥计时戳
      else
        pThis_21B4 = *(uint32_t *)(this + 8628);  // this+8628 【推断】指挥计时戳
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, pThis_21B4, 9, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      *(uint8_t *)(this + 8622) = 1;  // this+8622 【推断】循环音锁存
    }
  }
  return pThis_348;
}



// 猎人语音装载：HUNTER_FIND/DMG/DIE/ATK + HUNT_BREATH_LOOP 呼吸循环（27L）
// ------------------------------------------------------------
// 0x5ADB10 sub_5ADB10 —— 猎人语音装载表（6792..6872 索引面 + 五 TAG 写槽）
// 先写 this+6792..6872 八个动作→语音索引（1,1,2,3,3,4,3,5 表），
// 再经 ·0x4015C0 写入 HUNTER_FIND/HUNTER_DMG/HUNTER_DIE/HUNTER_ATK 与
// HUNT_BREATH_LOOP（呼吸循环）语音槽，尾清 8622/8604 两相位
// ------------------------------------------------------------
int /*thiscall*/ sub_5ADB10(int this)  // 函数: 猎人语音装载表（6792..6872 索引面 + 五 TAG 写槽）
{
  int result; // eax

  *(uint32_t *)(this + 6792) = 1;  // this+6792 【推断】炮车/子类参数面槽 1
  *(uint32_t *)(this + 6864) = 1;
  *(uint32_t *)(this + 6796) = 2;  // this+6796 【推断】炮车/子类参数面槽 2
  *(uint32_t *)(this + 6800) = 3;  // this+6800 【推断】炮车/子类参数面槽 3
  *(uint32_t *)(this + 6804) = 3;  // this+6804 【推断】炮车/子类参数面槽 4
  *(uint32_t *)(this + 6808) = 4;  // this+6808 【推断】炮车/子类参数面槽 5
  *(uint32_t *)(this + 6868) = 3;
  *(uint32_t *)(this + 6872) = 5;
  sub_4015C0("HUNTER_FIND", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("HUNTER_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("HUNTER_DIE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("HUNTER_ATK", 0xAu);  // 【std::string构造赋值】
  *(uint8_t *)(this + 8622) = 0;  // this+8622 【推断】循环音锁存
  result = sub_4015C0("HUNT_BREATH_LOOP", 0x10u);  // 【std::string构造赋值】
  *(uint8_t *)(this + 8604) = 0;  // this+8604 子类 AI 状态槽/相位门
  return result;
}



// 语音播报：HUNT_HARD_BREATH_LOOP（重呼吸/暴走前兆, 12L）
// ------------------------------------------------------------
// 0x5ADBD0 sub_5ADBD0 —— 重呼吸播报（HUNT_HARD_BREATH_LOOP 一次性写）
// this+1908 为 0 时经 ·0x4015C0 写 HUNT_HARD_BREATH_LOOP（暴走/重呼吸 21 字节 TAG），
// 随后统一转 ·0x5AD9E0 酸液总调度
// ------------------------------------------------------------
char /*thiscall*/ sub_5ADBD0(uint32_t *this)  // 函数: 重呼吸播报（HUNT_HARD_BREATH_LOOP 一次性写）
{
  if ( *(this + 1908) == 0 )  // this+7632〔uWindow7632(推断)〕
    sub_4015C0("HUNT_HARD_BREATH_LOOP", 0x15u);  // 【std::string构造赋值】
  return sub_5AD9E0((int)this);  // 调 酸液/AI 总调度（8604 相位 + 8616 帧型分流）
}



// 扑跳 AI：HUNT_JUMP 播报（43L；sub_431230 参数打包）
// ------------------------------------------------------------
// 0x5ADC00 sub_5ADC00 —— 扑跳动作 HUNT_JUMP（参数包 + vt+472 起状态）
// vt+212 播报 HUNT_JUMP；this+8621 开启时用 ·0x431230 三次打包坐标向量
// （第三项取 vt+672(obj,3)+928 与 +942 两轴乘出跳距），
// 交 vt+472(this,6,v4,1,1) 起跳（setState 参数面）
// ------------------------------------------------------------
void /*thiscall*/ sub_5ADC00(uint8_t *this)  // 函数: 扑跳动作 HUNT_JUMP（参数包 + vt+472 起状态）
{
  int pThis_2A0; // edi
  float v3; // eax
  uint8_t v4[4]; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-20h]
  int v6; // [esp+10h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-18h]
  int v8; // [esp+18h] [ebp-14h] BYREF
  uint32_t v9[4]; // [esp+1Ch] [ebp-10h] BYREF

  (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
    this,
    "HUNT_JUMP",  // 资源/动画 TAG HUNT_JUMP
    -1,
    0,
    0);
  if ( *(this + 8621) != 0 )
  {
    Block = nullptr;
    v6 = 0;
    v7 = 0;
    v9[3] = 0;
    v9[0] = 0;
    sub_431230((int)v4, v9);  // 调 uint32 vector push_back
    v9[0] = 0;
    sub_431230((int)v4, v9);  // 调 uint32 vector push_back
    pThis_2A0 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    v9[0] = sub_41A5E0(pThis_2A0 + 928);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    v3 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 942));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    v8 = (uint64_t)((double)v9[0] * v3);
    sub_431230((int)v4, &v8);  // 调 uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint8_t *, int, uint8_t *, int, int))(*(uint32_t *)this + 472))(this, 6, v4, 1, 1);  // 调用虚函数（虚表槽 +472）
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 调 堆释放
  }
}



// 尖啸 AI：HUNTER_SCREAM 播报（70L；this+208/8620 相位）
// ------------------------------------------------------------
// 0x5ADCF0 sub_5ADCF0 —— 主状态钩子（1639 镜像 + 1757 动作字分流）
// this+1639==6 且 ArgList==0 走 vt+1312 收手；==8 且 1757 落 2/3 走 vt+208 姿态写入；
// 随后 ·0x4E33D0 状态收尾居中放行；ArgList==6 时按关联对象 1813 的 vt+120/124 象限
// 经 vt+896 定方向并清 8620（对象为空退 vt+472(this,0,0,1,1)）；
// ArgList==8 按 1757：1→·0x5ADC00 扑跳、2→·0x5AD130(14)、3→·0x5AD130(15)、4→播 HUNTER_SCREAM
// ------------------------------------------------------------
void /*thiscall*/ sub_5ADCF0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 主状态钩子（1639 镜像 + 1757 动作字分流）
{
  int fld_e1639; // eax  | +0x199C → nMainState6556〔族字典〕（族字典）
  int pTarget7252; // ecx  | +0x1C54 → 【推断】当前目标/关联对象〔5AD9E0: 非 0 才进单发/三连吐酸分支〕（CNHunter；va=005AD9E0）
  int v8; // edi
  BOOL v9; // edi
  int fld_e18132; // ebx  | +0x1C54 → 【推断】当前目标/关联对象〔5AD9E0: 非 0 才进单发/三连吐酸分支〕（CNHunter；va=005AD9E0）
  int v11; // eax

  fld_e1639 = *(this + 1639);  // this+6556 = 主状态镜像
  if ( fld_e1639 == 6 )
  {
    if ( ArgList == 0 )
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1312))(this);  // 调用虚函数（虚表槽 +1312）
  }
  else if ( fld_e1639 == 8 && (sub_41A5E0((unsigned int)(this + 1757)) == 2 || sub_41A5E0((unsigned int)(this + 1757)) == 3) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));  // this+6216 = 资源/帧游标表
  }
  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 6 )
  {
    pTarget7252 = *(this + 1813);  // this+7252 = pTarget7252
    if ( pTarget7252 != 0 )
    {
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget7252 + 120))(pTarget7252);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < v8;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));  // this+7252 = pTarget7252
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 调用虚函数（虚表槽 +124）
      (*(void (/*thiscall*/ **)(uint32_t *, BOOL, int))(*this + 896))(this, v9, (v11 < fld_e18132) + 2);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
      *((uint8_t *)this + 8620) = 0;  // this+8620 = uAI8620
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 472))(this, 0, 0, 1, 1);  // 调用虚函数（虚表槽 +472）
    }
  }
  else if ( ArgList == 8 && sub_41A5E0((unsigned int)(this + 1757)) != 0 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 1 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      sub_5ADC00(this);  // 调 扑跳动作 HUNT_JUMP（参数包 + vt+472 起状态）
    }
    else if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        sub_5AD130(this, 14);  // 调 网络包封装发送（起包 29 + 坐标参数）
    }
    else if ( sub_41A5E0((unsigned int)(this + 1757)) == 3 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        sub_5AD130(this, 15);  // 调 网络包封装发送（起包 29 + 坐标参数）
    }
    else if ( sub_41A5E0((unsigned int)(this + 1757)) == 4 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        this,
        "HUNTER_SCREAM",  // 资源/动画 TAG HUNTER_SCREAM
        -1,
        0,
        0);
    }
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5ADEA0 sub_5ADEA0 —— 事件包取参分派（·0x4DC630 关卡/交互事件包）
// 返回 -1 直接透传；否则再读一值为参：事件 14/15 转 ·0x5AD4C0 瞄准态建立，
// 事件 16 转 ·0x5ADC00 扑跳
// ------------------------------------------------------------
int /*thiscall*/ sub_5ADEA0(uint32_t *this)  // 函数: 事件包取参分派（·0x4DC630 关卡/交互事件包）
{
  int result; // eax
  int v3; // esi
  int v4; // [esp+8h] [ebp-4h] BYREF

  result = sub_4DC630();  // 调 关卡/交互事件包处理（关联对象 this+7260 校验）
  v3 = result;
  if ( result != -1 )
  {
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v4);  // 调用虚函数（虚表槽 +80）
    if ( (uint16_t)v3 >= 0xEu )
    {
      if ( (uint16_t)v3 <= 0xFu )
      {
        sub_5AD4C0(this, v4, (uint16_t)v3);  // 调 瞄准态建立：HUNTER_READY 播报
      }
      else if ( (uint16_t)v3 == 16 )
      {
        sub_5ADC00(this);  // 调 扑跳动作 HUNT_JUMP（参数包 + vt+472 起状态）
        return v3;
      }
    }
    return v3;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5ADF00 sub_5ADF00 —— 尖啸变体收尾（1757==0 时速率双轴 + 计数递减）
// 先转 ·0x5ADCF0 主钩；ArgList==8 且 1757==0 时取 vt+672(obj,3)+816 与 +830 相乘
// 得双轴速率（V 轴半分、前后反向）经 vt+876 写双轴，vt+888 定标，
// vt+896 姿态，尾 --*(this+2163) 段计数
// ------------------------------------------------------------
void /*thiscall*/ sub_5ADF00(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: 尖啸变体收尾（1757==0 时速率双轴 + 计数递减）
{
  int v6; // edi
  uint64_t v7; // rax
  int v8; // edi
  int v9; // eax
  int v10; // [esp+1Ch] [ebp+14h]

  sub_5ADCF0(this, ArgList, fArg3, nArg4, nArg5);  // 调 主状态钩子（1639 镜像 + 1757 动作字分流）
  if ( ArgList == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 0 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    v10 = sub_41A5E0(v6 + 816);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    v7 = (uint64_t)((double)v10 * COERCE_FLOAT(sub_41A5E0(v6 + 830)));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
      this,
      0,
      (int)v7 / 2,
      (int)v7 / 2,
      0,
      -2 * ((int)v7 / 2),
      1);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
      this,
      1,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
    v8 = *this;
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v8 + 896))(this, v9);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
    --*(this + 2163);  // this+8652 = 相位槽
  }
}



// HH 猎人装载：Monster/Hunter/HH/{horn,hair,clothes,claws}.equ（59L）
// ------------------------------------------------------------
// 0x5ADFE0 sub_5ADFE0 —— HH 猎人外观装载（.equ 面 + 8648/8600/7576 相位）
// 依次 new 0x544 经 ·0x4BA9E0 构造 Monster/Hunter/HH 的 horn/hair/clothes/claws 四件
// 装备，均经 vt+784(.equ 挂装) 挂载并 vt+4(1) 启用；
// 尾置 8652=0、8621=1、8600=150、7576=2（攻击参数面）
// ------------------------------------------------------------
int /*usercall*/ sub_5ADFE0@<eax>(int pArg1@<ecx>, int nArg2@<ebx>)  // 实现：HH 猎人外观装载（.equ 面 + 8648/8600/7576 相位）
{
  char *pMem; // eax
  char *v4; // eax
  int pObj; // eax
  char *pMem2; // eax
  char *v7; // eax
  int pObj3; // eax
  char *pMem3; // eax
  char *v10; // eax
  int pObj2; // eax
  char *pMem4; // eax
  char *v13; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v4 = sub_4BA9E0(pMem, "Monster/Hunter/HH/horn.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v4 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)pArg1 + 784))(pArg1, v4, nArg2);  // 调用虚函数（虚表槽 +784）
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v7 = sub_4BA9E0(pMem2, "Monster/Hunter/HH/hair.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v7 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, v7);  // 调用虚函数（虚表槽 +784）
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调用虚函数（虚表槽 +4）
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v10 = sub_4BA9E0(pMem3, "Monster/Hunter/HH/clothes.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v10 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, v10);  // 调用虚函数（虚表槽 +784）
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调用虚函数（虚表槽 +4）
  pMem4 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v13 = sub_4BA9E0(pMem4, "Monster/Hunter/HH/claws.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v13 = nullptr;
  result = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, v13);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  *(uint32_t *)(pArg1 + 8652) = 0;  // pArg1+8652〔uPhase8652(推断)〕
  *(uint8_t *)(pArg1 + 8621) = 1;
  *(uint32_t *)(pArg1 + 8600) = 150;  // pArg1+8600〔uAI8600(推断)〕
  *(uint32_t *)(pArg1 + 7576) = 2;  // pArg1+7576〔uPhase7576(推断)〕
  return result;
}



// HM 猎人装载：Monster/Hunter/HM/{horn,hair,clothes}.equ（this+8621 相位）
// ------------------------------------------------------------
// 0x5AE160 sub_5AE160 —— HM 猎人外观装载（三件 .equ：horn/hair/clothes）
// 与 ·0x5ADFE0 同构（差异：HM 路径三件、无 claws，尾置 8621=1、2150=150、7537=1）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE160(uint8_t *this)  // 函数: HM 猎人外观装载（三件 .equ：horn/hair/clothes）
{
  char *pMem; // eax
  char *v3; // eax
  int pThis_310; // eax
  char *pMem2; // eax
  char *v6; // eax
  int pThis_3102; // eax
  char *pMem3; // eax
  char *v9; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Hunter/HM/horn.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v3 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_4BA9E0(pMem2, "Monster/Hunter/HM/hair.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v6 = nullptr;
  pThis_3102 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v6);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调用虚函数（虚表槽 +4）
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v9 = sub_4BA9E0(pMem3, "Monster/Hunter/HM/clothes.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v9 = nullptr;
  result = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v9);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  *(this + 8621) = 1;
  *((uint32_t *)this + 2150) = 150;  // this+8600 = uAI8600
  *(this + 7537) = 1;  // this+7537 内嵌配置块 +17 字节
  return result;
}



// HA 猎人装载：Monster/Hunter/HA/{horn,clothes,blindfold}.equ（蒙眼布, this+8621）
// ------------------------------------------------------------
// 0x5AE290 sub_5AE290 —— HA 猎人外观装载（三件 .equ：horn/clothes/blindfold 蒙眼布）
// 与 ·0x5ADFE0 同构（差异：HA 路径，蒙眼布代 hair/claws，尾置 8621=0、2150=0、1895=1）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE290(uint8_t *this)  // 函数: HA 猎人外观装载（三件 .equ：horn/clothes/blindfold 蒙眼布）
{
  char *pMem; // eax
  char *v3; // eax
  int pThis_310; // eax
  char *pMem2; // eax
  char *v6; // eax
  int pThis_3102; // eax
  char *pMem3; // eax
  char *v9; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_4BA9E0(pMem, "Monster/Hunter/HA/horn.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v3 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_4BA9E0(pMem2, "Monster/Hunter/HA/clothes.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v6 = nullptr;
  pThis_3102 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v6);  // 调用虚函数（虚表槽 +784）
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);  // 调用虚函数（虚表槽 +4）
  pMem3 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v9 = sub_4BA9E0(pMem3, "Monster/Hunter/HA/blindfold.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v9 = nullptr;
  result = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v9);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若结果非 0（成功）
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  *(this + 8621) = 0;
  *((uint32_t *)this + 2150) = 0;  // this+8600 = uAI8600
  *((uint32_t *)this + 1895) = 1;  // this+7580 = 攻击面门字节
  return result;
}



// ============================================================
// 【分区 12】僵尸 & 卡尔卡扎克（Zombie / Kalkazak）（0x5AE3C0-0x5AFAB0）
// 证据：ZOMBIE_EYEPULL/BITE/FIND/DMG/DIE/ATK、zombie/Kalkazak.mob、Particle/ZombieEye.ptl、
//       KALKAZAK_01 + ENLARGE 巨大化、0x5AE990 调 sub_4E4430（HP 受击处理器/Boss 终局族）

// AI 字段访问
// ------------------------------------------------------------
// 0x5AE3C0 sub_5AE3C0 —— 关联对象取字段（数组槽 pArg2+4 解引用 +196）
// this+(pArg2+4) 指针非空时返回其 +196 字段，否则 0【推断：分身槽查询】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE3C0(uint32_t *this, int pArg2)  // 函数: 关联对象取字段（数组槽 pArg2+4 解引用 +196）
{
  int v2; // eax

  v2 = *(this + pArg2 + 4);
  if ( v2 != 0 )
    return *(uint32_t *)(v2 + 196);
  else
    return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AE3E0 sub_5AE3E0 —— 攻击相位面清零（2150/2151/2158 + 2160 三连清）
// 一次性清 AI 阈值三字段起首两个与 2158、以及 2160/2161/2162 三槽，返回 0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE3E0(uint32_t *this)  // 函数: 攻击相位面清零（2150/2151/2158 + 2160 三连清）
{
  uint32_t *pThis_870; // ecx

  *(this + 2150) = 0;  // this+8600 = uAI8600
  *(this + 2151) = 0;  // this+8604 = bAI8604
  *(this + 2158) = 0;  // this+8632〔bDevourFlag(推断)〕
  pThis_870 = this + 2160;
  *pThis_870 = 0;
  pThis_870[1] = 0;
  pThis_870[2] = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AE410 sub_5AE410 —— 网络包封装发送（僵尸变体：无条件附随机数）
// 与 ·0x5AD130 同构（差异：起包 29 后必压 rand()，无 14/15 相位判断）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE410(void *this, int nArg2)  // 函数: 网络包封装发送（僵尸变体：无条件附随机数）
{
  int v3; // edi
  int pThis_30; // eax
  int v5; // edi
  int pThis_34; // eax
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int nRand; // eax

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
  v3 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  pThis_30 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);  // 调用虚函数（虚表槽 +48）
  (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, pThis_30);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  v5 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  pThis_34 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);  // 调用虚函数（虚表槽 +52）
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_34);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  v7 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 调用虚函数（虚表槽 +52）
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg2);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  v9 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
  nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
  (*(void (/*thiscall*/ **)(int, int))(v9 + 40))(dword_8F8520, nRand);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
}



// 技能播报：ZOMBIE_EYEPULL（抠眼, 31L）
// ------------------------------------------------------------
// 0x5AE4B0 sub_5AE4B0 —— 技能播报 ZOMBIE_EYEPULL 抠眼（30004 弹体）
// vt+152 态查询选 40/30 参量，this+2157 作第四参，vt+580 投 30004 号弹体
// （附 50/4 参量与 0 组），尾调 vt+212 播报 ZOMBIE_EYEPULL 语音 TAG
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE4B0(uint32_t *this, int nArg2)  // 函数: 技能播报 ZOMBIE_EYEPULL 抠眼（30004 弹体）
{
  int v3; // eax

  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
    this,
    30004,
    *(this + 2157),  // this+8628 = 指挥计时戳
    nArg2,
    0,
    v3 != 0 ? 40 : 30,
    0,
    50,
    4,
    0,
    0,
    0);
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
           this,
           "ZOMBIE_EYEPULL",  // 资源/动画 TAG ZOMBIE_EYEPULL
           -1,
           0,
           0);
}



// 撕咬 AI：ZOMBIE_BITE 播报（99L）
// ------------------------------------------------------------
// 0x5AE510 sub_5AE510 —— 撕咬命中驱动 ZOMBIE_BITE（硬直率掷 + 2151/2152 咬合计数）
// 目标 2150 为空直接 setState 15；目标 vt+840==9（特殊态）且动画 +170 终止位立起时，
// 本地门过则按朝向 40 偏置组装命中坐标，·0x4E5F70 硬直率掷并上报；
// 咬合计数 2151 自增，达阈值 2152 或目标 vt+684 HP<=0 → setState 15，
// 否则播 ZOMBIE_BITE 并 ·0x4926A0 帧复位；尾调目标 vt+604(0)/vt+612(1,1)；
// 目标非 9 态且非 5（死亡）时本地门过则驱动目标 setState 9
// ------------------------------------------------------------
int /*usercall*/ sub_5AE510@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：撕咬命中驱动 ZOMBIE_BITE（硬直率掷 + 2151/2152 咬合计数）
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

  pObj = pArg1[2150];
  if ( pObj == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 9 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      {
        v4 = *pArg1;
        v17 = 0.0;
        v18 = 0.0;
        v19 = 0.0;
        v20 = 0;
        v21 = 0;
        v22 = 0;
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 152))(pArg1) != 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) + 40;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        else
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - 40;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        v23 = v5;
        v6 = (double)v5;
        v7 = *pArg1;
        v17 = v6;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 124))(pArg1);  // 调用虚函数（虚表槽 +124）
        v9 = *pArg1;
        v23 = v8;
        v18 = (float)v8;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 128))(pArg1);  // 调用虚函数（虚表槽 +128）
        v11 = pArg1[2150];
        v23 = v10;
        v19 = (float)v10;
        sub_4E5F70(nArg2, (int)pArg1, v11, &v17, 1, 1);  // 调 ★ 硬直率掷（研究 §5.1 第 14 轮定案：同构于暴击掷）
      }
      v12 = pArg1[2152];
      v13 = pArg1[2151] + 1;
      pArg1[2151] = v13;
      if ( v13 >= v12
        || (v14 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2150] + 684))(pArg1[2150]), sub_41A5E0(v14) <= 0) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "ZOMBIE_BITE", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        sub_4926A0(v15);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pArg1[2150] + 604))(pArg1[2150], 0);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[2150] + 612))(pArg1[2150], 1, 1);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2150] + 840))(pArg1[2150]);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    if ( result != 5 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2150] + 308))(pArg1[2150]);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2150] + 560))(  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
                 pArg1[2150],
                 9,
                 0,
                 0,
                 0);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AE6E0 sub_5AE6E0 —— 分身/攻击参数面复位（7531..7596 区块全清 + 768 写 2、7550 写 1）
// 16 个字节/双字槽归零后置 7568=2、7550=1，返回 0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE6E0(int this, int nArg2, int nArg3)  // 函数: 分身/攻击参数面复位（7531..7596 区块全清 + 768 写 2、7550 写 1）
{
  *(uint8_t *)(this + 7558) = 0;  // this+7558 攻击参数面字节槽
  *(uint8_t *)(this + 7557) = 0;  // this+7557 攻击参数面门字节
  *(uint8_t *)(this + 7556) = 0;  // this+7556 攻击参数面模式字节
  *(uint8_t *)(this + 7534) = 0;  // this+7534 内嵌配置块 +14 字节
  *(uint8_t *)(this + 7533) = 0;  // this+7533 内嵌配置块 +13 字节
  *(uint8_t *)(this + 7532) = 0;  // this+7532 内嵌配置块 +12 字节
  *(uint8_t *)(this + 7531) = 0;  // this+7531 内嵌配置块 +11 字节 / 攻击参数面首字节
  *(uint32_t *)(this + 7535) = 0;  // this+7535 内嵌配置块 +15 字节
  *(uint32_t *)(this + 7539) = 0;  // this+7539 配置块 17 字节循环搬运区起点
  *(uint32_t *)(this + 7543) = 0;  // this+7543 攻击参数面槽
  *(uint32_t *)(this + 7547) = 0;  // this+7547 攻击参数面槽
  *(uint32_t *)(this + 7551) = 0;  // this+7551 攻击参数面槽
  *(uint8_t *)(this + 7555) = 0;  // this+7555 攻击参数面字节槽
  *(uint32_t *)(this + 7572) = 0;  // this+7572 档位槽
  *(uint32_t *)(this + 7568) = 0;  // this+7568 使能/段选槽
  *(uint32_t *)(this + 7564) = 0;  // this+7564 形态槽
  *(uint32_t *)(this + 7588) = 0;  // this+7588 形态槽
  *(uint32_t *)(this + 7584) = 0;  // this+7584 形态槽
  *(uint32_t *)(this + 7580) = 0;  // this+7580 缺省段选
  *(uint32_t *)(this + 7576) = 0;  // this+7576 相位槽
  *(uint32_t *)(this + 7596) = 0;  // this+7596 段号横向偏置
  *(uint32_t *)(this + 7568) = 2;  // this+7568 使能/段选槽
  *(uint8_t *)(this + 7550) = 1;  // this+7550 攻击参数面字节槽
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AE770 sub_5AE770 —— 诅咒/名称装配与附属物挂接
// ·0x4DE410 名称模板写入 + 随机倒计时，vt+700(this,this) 自挂，
// ·0x53F6A0 收尾；再由 vt+384 分别取参数 2/3/4 三对象，
// new 0x88 经 ·0x649CF0 构造诅咒动画对象（5910D0 查询族），vt+56 驱动播放
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE770(void *this)  // 函数: 诅咒/名称装配与附属物挂接
{
  int pThis_180; // edi
  int pThis_1802; // ebx
  int pObj; // eax
  int v6; // [esp+0h] [ebp-20h]
  int pThis_1803; // [esp+10h] [ebp-10h]

  sub_4DE410();  // 调 名称模板写入 + 随机倒计时
  (*(void (/*thiscall*/ **)(void *, void *))(*(uint32_t *)this + 700))(this, this);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
  sub_53F6A0(v6);  // 调 收尾路径
  pThis_180 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 384))(this, 2);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  pThis_1802 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 384))(this, 3);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  pThis_1803 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 384))(this, 4);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  if ( operator new(0x88u) != nullptr )  // operator new 分配 136 字节
    pObj = sub_649CF0(pThis_1802, pThis_1803, pThis_180);  // 调 诅咒动画查询（5910D0）
  else
    pObj = 0;
  return (*(int (/*thiscall*/ **)(int, void *, void *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
           pObj,
           this,
           this,
           0,
           0,
           0,
           -1);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AE830 sub_5AE830 —— 属性注册（196613 号 + 100000 参）
// 栈上置 100000，转 ·0x4E1390(196613, &v1) 注册属性【推断：分身/巨大化的属性 id】
// ------------------------------------------------------------
int sub_5AE830()  // 函数: 属性注册（196613 号 + 100000 参）
{
  int v1; // [esp+0h] [ebp-4h] BYREF

  v1 = 100000;
  return sub_4E1390(196613, &v1);  // 调 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
}



// mob 引用：zombie/Kalkazak.mob（卡尔卡扎克数据文件, 34L）
// ------------------------------------------------------------
// 0x5AE850 sub_5AE850 —— 卡尔卡扎克形态数据切换（zombie/Kalkazak.mob）
// 取 vt+672(obj,3) 与 nArg2 比定形态方向标志 v9，暂存 vt+736/vt+740 两值；
// vt+1024(this,nArg2,"zombie/Kalkazak.mob") 装载形态数据后按方向把 vt+740
// （最大 HP 类）与暂存值比较，取大或取新值经 vt+732(this,v6,0,1) 提交
// 【推断：巨大化/形态切换的 HP 与模型同步】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE850(int *this, int nArg2)  // 函数: 卡尔卡扎克形态数据切换（zombie/Kalkazak.mob）
{
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v8; // [esp+Ch] [ebp-4h]
  bool v9; // [esp+1Bh] [ebp+Bh]

  v9 = *(uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3) > nArg2;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
  (*(void (/*thiscall*/ **)(int *, int, const char *))(*this + 1024))(this, nArg2, "zombie/Kalkazak.mob");  // 调用虚函数（虚表槽 +1024）
  v5 = *this;
  if ( !v9 )
  {
    v4 += (*(int (/*thiscall*/ **)(int *))(v5 + 740))(this) - v8;  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 740))(this) < v4 )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
      goto LABEL_3;
LABEL_5:
    v6 = v4;
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 732))(this, v6, 0, 1);  // 调用虚函数（虚表槽 +732）
  }
  if ( v4 < (*(int (/*thiscall*/ **)(int *))(v5 + 740))(this) )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    goto LABEL_5;
LABEL_3:
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 732))(this, v6, 0, 1);  // 调用虚函数（虚表槽 +732）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AE900 sub_5AE900 —— 消亡链收尾（观察者广播 + 定时器与场景挂接）
// ·0x4D9760 观察者广播后条件收尾；vt+768(this,9,10,0) 与 vt+772(this,9,999999999)
// 两槽写入（超大时钟 = 阻断后续），返回对象交 ·0x497110（vt+84 分发）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE900(void *this)  // 函数: 消亡链收尾（观察者广播 + 定时器与场景挂接）
{
  int pThis_304; // eax

  sub_4D9760();  // 调 观察者广播后条件收尾
  (*(void (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 768))(this, 9, 10, 0);  // 调用虚函数（虚表槽 +768）【推断: ★ 状态施加入口（17 状态槽懒创建 + 转发）】
  pThis_304 = (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 772))(this, 9, 999999999);  // 调用虚函数（虚表槽 +772）【推断: [RTTI: IRDActiveObject__vmt304 ·…】
  return sub_497110(pThis_304);  // 调 虚转发 vt+84
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AE940 sub_5AE940 —— 伤害类型门（·0x4DC390 过滤后追加无效化）
// ·0x4DC390 伤害类型过滤返回 3 直接透传；否则受方 vt+348 容器 +20 非零亦透传，
// 否则 *uArg1=0 并返 2（伤害无效化）
// ------------------------------------------------------------
int /*stdcall*/ sub_5AE940(uint32_t *uArg1, int nArg2)  // 函数: 伤害类型门（·0x4DC390 过滤后追加无效化）
{
  int result; // eax
  int v3; // esi

  result = sub_4DC390(uArg1, nArg2);  // 调 伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 20) != 0 )  // 调用虚函数（虚表槽 +348）
    {
      return v3;
    }
    else
    {
      *uArg1 = 0;
      return 2;
    }
  }
  return result;
}



// 死亡/终局钩：调 sub_4E4430 = HP 受击处理器（研究 31 Boss 终局长震/R_STAGE_FINALE 族；
//   this+8652 相位, 30L）
// ------------------------------------------------------------
// 0x5AE990 sub_5AE990 —— HP 受击钩（·0x4E4430 Boss 终局族 + 8652 低血文案门）
// 先转 ·0x4E4430 HP 受击处理器（含 Boss 终局长震/R_STAGE_FINALE 族）；
// 8652 相位为 0 且本次伤害 nArg2 >= 最大 HP(vt+740)×0.25 时置 8652=1，
// 取 vt+672(obj,3)+830 速率浮点槽 +1.0 写回并经 vt+676(0) 提交，
// 尾调 ·0x4DB200(24,1) 触发 24 号随机文案
// ------------------------------------------------------------
void /*thiscall*/ sub_5AE990(char *this, int nArg2, int nArg3, char pszArg4)  // 函数: HP 受击钩（·0x4E4430 Boss 终局族 + 8652 低血文案门）
{
  int v5; // edx
  unsigned int v6; // edi
  int v7; // edx
  int v8; // [esp+Ch] [ebp+8h]
  float v9; // [esp+14h] [ebp+10h]

  sub_4E4430(this, nArg2, nArg3, pszArg4);  // 【HP 受击处理器含 Boss 终局（研究 P35 第 31 轮）】
  if ( *(this + 8652) == 0 )  // this+8652 【推断】相位门字节
  {
    v9 = (float)nArg2;
    if ( (double)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 740))(this) * 0.25 >= v9 )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    {
      v5 = *(uint32_t *)this;
      *(this + 8652) = 1;  // this+8652 【推断】相位门字节
      v6 = (*(int (/*thiscall*/ **)(char *, int))(v5 + 672))(this, 3) + 830;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v6)) + 1.0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v6, v7, v8);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
      sub_4DB200(24, 1);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
    }
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AEA40 sub_5AEA40 —— 魔法师基类 AI 调度 + 低概率文案
// 先转 ·0x594370 魔法师基类小调度（1787 待机逻辑 + 4↔13 动画切换），
// 再掷 rand100 < 2 时 ·0x4DB200(24,0) 触发 24 号文案【推断：2% 概率随机台词】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AEA40(int *this)  // 函数: 魔法师基类 AI 调度 + 低概率文案
{
  int nRand; // eax
  int result; // eax
  int v3; // et2

  sub_594370(this);  // 调 魔法师基类 AI 小调度（this+1787：待机逻辑 + 4↔13 动画切换）
  nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
  v3 = nRand % 100;
  result = nRand / 100;
  if ( v3 < 2 )
    return sub_4DB200(24, 0);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
  return result;
}



// 硬直字段（this+208/8616）
// ------------------------------------------------------------
// 0x5AEA70 sub_5AEA70 —— 姿态收尾（清 8616 + vt+208 双写）
// this+8616 相位清零后，vt+208 以 1554 容器 +8 与 +12 两槽先后写姿态表项
// ------------------------------------------------------------
int /*thiscall*/ sub_5AEA70(uint32_t *this)  // 函数: 姿态收尾（清 8616 + vt+208 双写）
{
  int fld_e1554; // eax
  int v3; // edx

  fld_e1554 = *(this + 1554);  // this+6216 = 资源/帧游标表
  v3 = *this;
  *((uint8_t *)this + 8616) = 0;  // this+8616 = uAI8616
  (*(void (/*stdcall*/ **)(uint32_t))(v3 + 208))(*(uint32_t *)(fld_e1554 + 8));  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));  // this+6216 = 资源/帧游标表
}



// 僵尸眼技能：引用 Particle/ZombieEye.ptl（44L；this+6556==14 与 -15 派生条件
//   【推断：卡尔卡扎克巨大化/分身态判定】）
// ------------------------------------------------------------
// 0x5AEAB0 sub_5AEAB0 —— 僵尸眼总调度（8616 相位 + 6556==14/15 大状态门）
// ·0x4E1780 基础 AI 后：8616 相位开启时动画 +148==6 且 8617==0 则 vt+588 加载
// Particle/ZombieEye.ptl 交 ·0x5AE4B0 抠眼并置 8617，动画 +170 终止位经 ·0x5AEA70 收尾；
// 相位关时 this+6556==14 → ·0x5AE510 撕咬；==15 且 +120 对象 +170 终止位立起 →
// vt+560(this,0,...) setState 0（回待机）
// ------------------------------------------------------------
int /*usercall*/ sub_5AEAB0@<eax>(int pArg1@<ecx>, int nArg2@<ebx>)  // 实现：僵尸眼总调度（8616 相位 + 6556==14/15 大状态门）
{
  int v3; // eax
  int result; // eax

  sub_4E1780((uint32_t *)pArg1);  // 调 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( *(uint8_t *)(pArg1 + 8616) != 0 )  // pArg1+8616〔uAI8616(推断)〕
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) == 6 && *(uint8_t *)(pArg1 + 8617) == 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    {
      v3 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)pArg1 + 588))(pArg1, "Particle/ZombieEye.ptl");  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
      sub_5AE4B0((uint32_t *)pArg1, v3);  // 调 技能播报 ZOMBIE_EYEPULL 抠眼（30004 弹体）
      *(uint8_t *)(pArg1 + 8617) = 1;  // pArg1+8617〔bPhase8617(推断)〕
    }
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    if ( result != 0 )  // 若结果非 0（成功）
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      if ( *(uint8_t *)(result + 170) != 0 )
        return sub_5AEA70((uint32_t *)pArg1);  // 调 姿态收尾（清 8616 + vt+208 双写）
    }
  }
  else if ( *(uint32_t *)(pArg1 + 6556) == 14 )  // pArg1+6556〔大状态ID〕
  {
    return sub_5AE510((uint32_t *)pArg1, nArg2);  // 调 撕咬命中驱动 ZOMBIE_BITE（硬直率掷 + 2151/2152 咬合计数）
  }
  else
  {
    result = *(uint32_t *)(pArg1 + 6556) - 15;  // pArg1+6556〔大状态ID〕
    if ( *(uint32_t *)(pArg1 + 6556) == 15 )  // pArg1+6556〔大状态ID〕
    {
      result = *(uint32_t *)(pArg1 + 120);  // pArg1+120〔pAnimObj〕
      if ( *(uint8_t *)(result + 170) != 0 )
        return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    }
  }
  return result;
}



// AI 相位辅助（53L）
// ------------------------------------------------------------
// 0x5AEB60 sub_5AEB60 —— 体型缩放（ENLARGE）双态翻转
// 以 this+7252 对象的 vt+776 第 11 项查询与 this+2158 标记比对决定放大/缩小：翻转时经
// vt+672/vt+676（第三参 0.3f）压住节奏，缩放因子 1.3 与其倒数 0.76923078 在 this+2159
// 与 1905 指针 +36 槽上互逆互换；转入放大侧经 ·0x4D82D0 播头顶气泡，并统一以
// ·0x4DB200 组 24 文案按 rand%2 随机播报（与 5AF040 的 ENLARGE 同为形态面证据）
// ------------------------------------------------------------
void /*thiscall*/ sub_5AEB60(float *this)  // 函数: 体型缩放（ENLARGE）双态翻转
{
  int pThis_715; // ecx
  bool v3; // zf
  int pThis_86E; // eax
  int nRand; // eax
  double fld_e2159; // st7
  float v7; // [esp+0h] [ebp-Ch]
  uint32_t v8[2]; // [esp+4h] [ebp-8h]

  pThis_715 = *((uint32_t *)this + 1813);  // this+7252 = pTarget7252
  if ( pThis_715 != 0 )
  {
    v3 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_715 + 776))(pThis_715, 11) == 0;  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
    pThis_86E = *((uint32_t *)this + 2158);  // this+8632〔bDevourFlag(推断)〕
    if ( v3 )
    {
      if ( pThis_86E == 1 )
      {
        (*(void (/*thiscall*/ **)(float *, uint32_t, int))(*(uint32_t *)this + 672))(this, 0, 1050253722);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
        sub_4E99C0(v7);  // 调 防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
        fld_e2159 = *(this + 2159) * 1.3;  // this+8636 = pDollTarget
        *(this + 2158) = 0.0;  // this+8632〔bDevourFlag(推断)〕
        *(this + 2159) = fld_e2159;  // this+8636 = pDollTarget
        *(float *)(*((uint32_t *)this + 1905) + 36) = *(float *)(*((uint32_t *)this + 1905) + 36) * 0.76923078;  // this+7620 = 速度/属性参数对象
      }
    }
    else
    {
      if ( pThis_86E == 0 )
      {
        (*(void (/*thiscall*/ **)(float *, uint32_t, int))(*(uint32_t *)this + 672))(this, 0, 1050253722);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
        sub_4AED60(v7);
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
        *(this + 2159) = *(this + 2159) * 0.76923078;  // this+8636 = pDollTarget
        *((uint32_t *)this + 2158) = 1;  // this+8632〔bDevourFlag(推断)〕
        sub_4D82D0(0, 0);  // 头顶气泡 Command.ani（a2/a3 = 定位偏移）
        *(float *)(*((uint32_t *)this + 1905) + 36) = *(float *)(*((uint32_t *)this + 1905) + 36) * 1.3;  // this+7620 = 速度/属性参数对象
      }
      v8[0] = 0;
      v8[1] = 1;
      nRand = rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
      sub_4DB200(24, v8[nRand]);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
    }
  }
}



// 硬直字段（this+204）
// ------------------------------------------------------------
// 0x5AECA0 sub_5AECA0 —— 帧组双档游标复位
// 对 this+6216 帧组对象的 +8/+12 两个子档各经 vt+204 写入帧号 1 与 3，随即各以
// ·0x4926A0 复位该档帧数组游标（+44 首针 / 递归子链 +204），常用于收手回起手帧
// ------------------------------------------------------------
int /*thiscall*/ sub_5AECA0(uint32_t *this)  // 函数: 帧组双档游标复位
{
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
    this,
    1,
    *(uint32_t *)(*(this + 1554) + 8),  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
    this,
    3,
    *(uint32_t *)(*(this + 1554) + 12),  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  return sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
}



// AI 相位辅助（46L）
// ------------------------------------------------------------
// 0x5AED10 sub_5AED10 —— 架招连段计数推进与目标侧向位移补偿
// 入参等于 this+8600 锁定对象指针、vt+840 姿态为 14（架招）且 this+8608 段数大于 1 时，
// 按 ·0x491C10 帧总长的 5/1000 节拍递增 this+8612 计数，满格则段数自减一并清零计数；
// 随后取该对象 ·vt+916 调用前后的 vt+120 坐标差为漂移量，从自身经 vt+128→vt+124→
// vt+120 逐级求得的坐标中扣除，末经 vt+112 双轴写回【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AED10(uint32_t *this, int nArg2)  // 函数: 架招连段计数推进与目标侧向位移补偿
{
  int result; // eax
  int fld_e1554; // eax
  int fld_e2153; // edx
  int fld_e2150; // edi
  int fld_e21502; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = nArg2;
  if ( nArg2 == *(this + 2150) )  // this+8600 = uAI8600
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    if ( result == 14 && (int)*(this + 2152) > 1 )  // this+8608 = uAI8608
    {
      fld_e1554 = sub_491C10(*(uint32_t *)*(this + 1554));  // 调 遍历帧数组（首+44/尾+48，步长 88）
      fld_e2153 = *(this + 2153) + 1;  // this+8612 = uAI8612
      *(this + 2153) = fld_e2153;  // this+8612 = uAI8612
      if ( fld_e2153 >= 5 * fld_e1554 / 1000 )
      {
        --*(this + 2152);  // this+8608 = uAI8608
        *(this + 2153) = 0;  // this+8612 = uAI8612
      }
      fld_e2150 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2150) + 120))(*(this + 2150));  // this+8600 = uAI8600
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2150) + 916))(*(this + 2150));  // this+8600 = uAI8600
      fld_e21502 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2150) + 120))(*(this + 2150));  // this+8600 = uAI8600
      v8 = *this;
      v9 = fld_e2150 - fld_e21502;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v10);  // 调用虚函数（虚表槽 +124）
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v11);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(v8 + 112))(this, v12 - v9);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    }
  }
  return result;
}



// 蓄力技能：vt+212 "HOLD"（111L；sub_4049C0 插值）
// ------------------------------------------------------------
// 0x5AEDE0 sub_5AEDE0 —— HOLD 蓄力架招起手与段数插值
// 经 ·0x45EBE0 解包目标（vt+40 类型 17 校验且 vt+128 高度非正），写入 this+8600 并把目标
// 三坐标快照存 8640/8644/8648；按 vt+152 分侧横偏 40 后经 vt+112 落位、vt+848 挂装，
// 继以 vt+876 清速率双轴、vt+888 设千毫秒窗口、vt+896 四对四绑定，并清 112 号子对象延时；
// 末由 vt+384 两档出场参数经 ·0x4049C0 在 1820→1821 跨度插值为段数写 this+8608，播 HOLD
// ------------------------------------------------------------
int /*thiscall*/ sub_5AEDE0(uint32_t *this, int pArg2)  // 函数: HOLD 蓄力架招起手与段数插值
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2150; // ecx
  int v6; // eax
  int fld_e21502; // ecx
  int v8; // eax
  int fld_e21503; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int fld_e21504; // ecx
  int v14; // eax
  int v15; // ebx
  int fld_e21505; // edi
  int v17; // eax
  int v18; // eax
  uint32_t *fld_e28; // edi
  int v20; // eax
  int fld_e1821; // edi
  uint32_t *v22; // eax
  uint64_t fld_e1820; // rax
  float v25; // [esp+70h] [ebp-20h]
  float v26; // [esp+74h] [ebp-1Ch]
  int v27; // [esp+8Ch] [ebp-4h]
  int v28; // [esp+98h] [ebp+8h]
  int v29; // [esp+98h] [ebp+8h]

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));  // 调 存 id 对 → 对象查找
  pObj = pObj2;
  if ( pObj2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    || (*(this + 2150) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )  // this+8600 = uAI8600
  {
    *(this + 2150) = 0;  // this+8600 = uAI8600
  }
  fld_e2150 = *(this + 2150);  // this+8600 = uAI8600
  if ( fld_e2150 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2150 + 120))(fld_e2150);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    fld_e21502 = *(this + 2150);  // this+8600 = uAI8600
    *(this + 2160) = v6;  // this+8640 = uCastSlot8640
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21502 + 124))(fld_e21502);  // 调用虚函数（虚表槽 +124）
    fld_e21503 = *(this + 2150);  // this+8600 = uAI8600
    *(this + 2161) = v8;  // this+8644 = 相位槽
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21503 + 128))(fld_e21503);  // 调用虚函数（虚表槽 +128）
    v11 = *this;
    *(this + 2162) = v10;  // this+8648 = 相位/缓存槽
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(v11 + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    fld_e21504 = *(this + 2150);  // this+8600 = uAI8600
    if ( v12 != 0 )
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21504 + 120))(fld_e21504) - 40;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    else
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21504 + 120))(fld_e21504) + 40;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v15 = *this;
    v28 = v14;
    fld_e21505 = *(this + 2150);  // this+8600 = uAI8600
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21505 + 128))(fld_e21505);  // 调用虚函数（虚表槽 +128）
    v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21505 + 124))(fld_e21505, v17);  // 调用虚函数（虚表槽 +124）
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v15 + 112))(this, v28, v18 + 1);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2150) + 848))(*(this + 2150), 1);  // this+8600 = uAI8600
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));  // this+6216 = 资源/帧游标表
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));  // 调用虚函数（虚表槽 +344）
  fld_e28 = (uint32_t *)*(this + 28);  // this+112 = pHostComp
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
  v27 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v20 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v29 = v20;
  v22 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v26 = (float)v29;
  v25 = (float)v27;
  fld_e1820 = (uint64_t)sub_4049C0(v25, v26, *v22 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2152) = fld_e1820;  // this+8608 = uAI8608
  LODWORD(fld_e1820) = *this;  // 调 取 64 位值低 32 位
  *(this + 2151) = 0;  // this+8604 = bAI8604
  *(this + 2153) = 0;  // this+8612 = uAI8612
  return (*(int (/*fastcall*/ **)(uint32_t *, uint32_t, const char *, int, uint32_t, uint32_t))(fld_e1820 + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
           this,
           HIDWORD(fld_e1820),  // 调 取 64 位值高 32 位
           "HOLD",  // 资源/动画 TAG HOLD
           -1,
           0,
           0);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AF000 sub_5AF000 —— 动作子对象换装钩子
// 取旧值 this+7252，经 ·0x4D97E0 将入参直写槽位后比对：发生变化且新值通过 vt+40 类型
// 17 校验时转 ·0x5AEB60 体型缩放翻转（ENLARGE 形态面刷新）
// ------------------------------------------------------------
void /*thiscall*/ sub_5AF000(int this, int nArg2)  // 函数: 动作子对象换装钩子
{
  int pLinkTarget7252; // ebx  | +0x1C54 → 关联/锁定目标对象（CNZombie；va=005AF000）

  pLinkTarget7252 = *(uint32_t *)(this + 7252);  // this+7252 关联/锁定目标对象
  sub_4D97E0(nArg2);  // 调 动作子对象状态槽直写
  if ( pLinkTarget7252 != nArg2 && nArg2 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    sub_5AEB60((float *)this);  // 调 体型缩放（ENLARGE）双态翻转
}



// 登场/巨大化播报：KALKAZAK_01 + ENLARGE（87L）
// ------------------------------------------------------------
// 0x5AF040 sub_5AF040 —— 卡尔卡扎克吞噬成长阶梯
// 轮询全局 0x8F850C 表偏移 +16/+20/+24/+28 四槽对象，各取其 vt+700 向量并统计 vt+92 为真
// 的元素总数（存活可吞计数）；当计数超过上帧 this+8656 且阶梯号 this+8652 < 5 时升一阶：
// 经 vt+688 按 1.0+0.1n → 1.0+0.1(n+1) 两段式缩放调档，转 ·0x5AE850 切形态数据（索引
// *vt+672(3)+1），并由 vt+212 连播 KALKAZAK_01 与 ENLARGE 两条语音【推断：两段缩放为成长动画插值】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF040(int *this)  // 函数: 卡尔卡扎克吞噬成长阶梯
{
  int result; // eax
  int v3; // eax
  unsigned int v4; // edi
  int pObj; // ebx
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int pObj2; // ecx
  int v11; // edi
  uint32_t *v12; // eax
  float v13; // [esp+4h] [ebp-14h]
  int i; // [esp+Ch] [ebp-Ch]
  float v15; // [esp+Ch] [ebp-Ch]
  int v16; // [esp+10h] [ebp-8h]
  float v17; // [esp+10h] [ebp-8h]
  int v18; // [esp+14h] [ebp-4h]

  result = 16;
  v16 = 0;
  for ( i = 16; i < 32; i += 4 )
  {
    v3 = *(uint32_t *)(result + dword_8F850C);  // 读 dword_8F850C（房间/席位表）
    v4 = 0;
    if ( v3 != 0 )
      pObj = *(uint32_t *)(v3 + 196);
    else
      pObj = 0;
    if ( pObj != 0 )
    {
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
      v7 = *(uint32_t *)(v6 + 4);
      v18 = v7 != 0 ? (*(uint32_t *)(v6 + 8) - v7) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( v18 > 0 )
      {
        do
        {
          v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
          v9 = *(uint32_t *)(v8 + 4);
          if ( v9 != 0 && v4 < (*(uint32_t *)(v8 + 8) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
            pObj2 = *(uint32_t *)(v9 + 4 * v4);
          else
            pObj2 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 92))(pObj2) != 0 )  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
            ++v16;
          ++v4;
        }
        while ( (int)v4 < v18 );
      }
    }
    result = i + 4;
  }
  v11 = v16;
  if ( *(this + 2164) < v16 )  // this+8656 = 事件 16/17 配对槽
  {
    result = *(this + 2163);  // this+8652 = 相位槽
    if ( result < 5 )
    {
      v17 = (double)(10 * result) * 0.0099999998 + 1.0;  // ×0.01f（百分数转比例）
      v15 = (double)(10 * result + 10) * 0.0099999998 + 1.0;  // ×0.01f（百分数转比例）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 688))(this, LODWORD(v17));  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
      sub_4EB4B0(v13);  // 调 与 ·0x4EB2C0 同构（差异：·sub_4923F0 按倒数缩放）
      (*(void (/*thiscall*/ **)(int *))(*this + 688))(this);  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
      sub_4EB2C0(v15);  // 调 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
      ++*(this + 2163);  // this+8652 = 相位槽
      v12 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      sub_5AE850(this, *v12 + 1);  // 调 卡尔卡扎克形态数据切换（zombie/Kalkazak.mob）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "KALKAZAK_01", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
      result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                 this,
                 "ENLARGE",  // 资源/动画 TAG ENLARGE
                 -1,
                 0,
                 0);
    }
  }
  *(this + 2164) = v11;  // this+8656 = 事件 16/17 配对槽
  return result;
}



// 主状态门（this+200/8616/8617）
// ------------------------------------------------------------
// 0x5AF1C0 sub_5AF1C0 —— 相位帧组装载与相位字复写
// 经 vt+196 指向 this+6200 帧组第 8 字节档，再由 vt+200 取档对象交 ·0x4926A0 复位游标；
// 继调 ·0x5AECA0 双档游标回位，置 this+8616=1（相位联动标志）与 8617=0，入参存 8624
// 供 5AF220 消费（8616 清零即解除）——大量相位分支以此为前置【推断：8624 为相位参】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF1C0(uint32_t *this, int nArg2, int nArg3)  // 函数: 相位帧组装载与相位字复写
{
  int v4; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1550) + 8));  // 调用虚函数（虚表槽 +196）
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  sub_4926A0(v4);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
  sub_5AECA0(this);  // 调 帧组双档游标复位
  *((uint8_t *)this + 8616) = 1;  // this+8616 = uAI8616
  *((uint8_t *)this + 8617) = 0;  // this+8617 【推断】钻地相位字节2
  *(this + 2156) = nArg2;  // this+8624 = uAI8624
  return nArg2;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AF210 sub_5AF210 —— 每帧复合 AI 入口
// 先转魔法师基类小调度 ·0x594370（this+1787 行为字槽分流），再转 ·0x5AF040 成长阶梯判定
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF210(int *this)  // 函数: 每帧复合 AI 入口
{
  sub_594370(this);  // 调 魔法师基类 AI 小调度（this+1787：待机逻辑 + 4↔13 动画切换）
  return sub_5AF040(this);  // 调 卡尔卡扎克吞噬成长阶梯
}



// 僵尸语音装载：ZOMBIE_FIND/DMG/DIE/ATK 四件套（sub_4015C0, this+8616 相位）
// ------------------------------------------------------------
// 0x5AF220 sub_5AF220 —— 僵尸四段语音装载与相位解除
// 预置 this+6792/6796/6800/6804/6808 = 2/2/2/3/4（语音槽组编号），经 ·0x4015C0 依次装载
// ZOMBIE_FIND/DMG/DIE/ATK 四条 TAG（次参 0x0B/0x0A/0x0A/0x0A 为槽位）；再由 vt+384 两档
// 出场参数经 ·0x4049C0 插值为 this+8628 值域，末清 this+8616 相位联动标志（与 5AF1C0 反配）
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5AF220(uint32_t *this)  // 函数: 僵尸四段语音装载与相位解除
{
  int fld_e1821; // edi
  uint32_t *v3; // eax
  uint64_t result; // rax
  float v5; // [esp+Ch] [ebp-20h]
  float v6; // [esp+10h] [ebp-1Ch]
  int v7; // [esp+24h] [ebp-8h]
  int v8; // [esp+28h] [ebp-4h]

  *(this + 1698) = 2;  // this+6792 = 炮车/子类参数面槽 1
  *(this + 1699) = 2;  // this+6796 = 炮车/子类参数面槽 2
  *(this + 1700) = 2;  // this+6800 = 炮车/子类参数面槽 3
  *(this + 1701) = 3;  // this+6804 = 炮车/子类参数面槽 4
  *(this + 1702) = 4;  // this+6808 = 炮车/子类参数面槽 5
  sub_4015C0("ZOMBIE_FIND", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("ZOMBIE_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("ZOMBIE_DIE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("ZOMBIE_ATK", 0xAu);  // 【std::string构造赋值】
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 2);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v6 = (float)v8;
  v5 = (float)v7;
  result = (uint64_t)sub_4049C0(v5, v6, *v3 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2157) = result;  // this+8628 = 指挥计时戳
  *((uint8_t *)this + 8616) = 0;  // this+8616 = uAI8616
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AF310 sub_5AF310 —— 关卡事件 14 号转相位装载
// 先轮询 ·0x4DC630 关卡/交互事件包（返回 -1 即无事件直接退出）；命中时经全局
// ·0x8F8520 的 vt+80 取出事件载荷，仅当低 16 位等于 14（架招相位）时转 ·0x5AF1C0 装载
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF310(uint32_t *this)  // 函数: 关卡事件 14 号转相位装载
{
  int result; // eax
  int v3; // esi
  int v4; // [esp+8h] [ebp-4h] BYREF

  result = sub_4DC630();  // 调 关卡/交互事件包处理（关联对象 this+7260 校验）
  v3 = result;
  if ( result != -1 )
  {
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v4);  // 调用虚函数（虚表槽 +80）
    if ( (uint16_t)v3 == 14 )
      sub_5AF1C0(this, v4, 14);  // 调 相位帧组装载与相位字复写
    return v3;
  }
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5AF360 sub_5AF360 —— 攻击命中转架招（14）入态门
// 门列：this+6556 主状态 8（攻击）、·0x41A5E0(this+7028) 段号门为 1、nArg4 低字节 0、
// vt+308 可行动、目标 vt+40 类型 17、目标 vt+948 可受招、this+616 反应态非 14；
// 通过后经 ·0x431230 把目标 vt+48 与 vt+52 两值打包为 vector 参数，经 vt+560 setState
// 切反应态 14（架招），末无条件尾调 ·0x4DB480 反击/架招触发判定并透传其返回
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF360(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 攻击命中转架招（14）入态门
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8  // this+6556 = 主状态镜像
    && sub_41A5E0((unsigned int)(this + 1757)) == 1  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
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
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    v9 = -1;
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
  return sub_4DB480(pObj, nArg3, nArg4);  // 调 ★ 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 参数打包 AI（89L sub_431230）
// ------------------------------------------------------------
// 0x5AF460 sub_5AF460 —— 架招收手：投摔目标落点安置与姿态收尾
// this+8600 锁定目标非空时启动：vt+604(1,nArg2) 置收手标志、vt+612 清双参；再按目标
// vt+136(快照坐标) 判定落点合法性——成立即 vt+112 直写 8640/8644/8648 三坐标；否则以
// 自身 vt+140 校验目标 vt+124(300,1,1)→vt+120 求得点位，仍不成立则取自身 vt+124(8648)
// →vt+120 结果经 vt+112 单参写；随后 vt+308 门经 ·0x431230 打包 (4,0,1,200,200) 五参由
// vt+560 切反应态 4（受击后置）并 vt+564 补写，释放缓冲后 vt+848(0) 解除挂装、8600 清 0
// ------------------------------------------------------------
void /*usercall*/ sub_5AF460(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 函数: 架招收手：投摔目标落点安置与姿态收尾
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

  pObj3 = pDwArg1[2150];
  if ( pObj3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2150] + 612))(pDwArg1[2150], 0, 0);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2150] + 136))(  // 调用虚函数（虚表槽 +136）
           pDwArg1[2150],
           pDwArg1[2160],
           pDwArg1[2161],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2150] + 112))(pDwArg1[2150], pDwArg1[2160], pDwArg1[2161], pDwArg1[2162]);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
    }
    else
    {
      pObj = pDwArg1[2150];
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);  // 调用虚函数（虚表槽 +124）
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2160, pDwArg1 + 2161, v7);  // 调用虚函数（虚表槽 +140）【推断: ★ 螺旋式寻找空位（同心方环，从 (a4,a5) 起向外扫）】
      pObj2 = pDwArg1[2150];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2160], pDwArg1[2161], pDwArg1[2162]);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      }
      else
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2162]);  // 调用虚函数（虚表槽 +124）
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2150], v12);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2150] + 308))(pDwArg1[2150]) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
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
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2150] + 560))(pDwArg1[2150], 4, v13, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2150] + 564))(pDwArg1[2150]);  // 调用虚函数（虚表槽 +564）【推断: ★ 位移同步包 vt+234（会话 3 定案：UDP type=…】
      v18 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 堆释放
      Block = nullptr;
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2150] + 848))(pDwArg1[2150], 0);  // 调用虚函数（虚表槽 +848）【推断: [RTTI: IRDActiveObject__vmt350 ·…】
    pDwArg1[2150] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AF660 sub_5AF660 —— 架招命中叠加 25% 效果请求
// 先转 ·0x5AF360 完成入态判定并保留其返回值；仅在 vt+308 可行动、rand()%100<25、
// vt+348 反馈对象（+16 标志或首浮点非零即有效）且 nArg4 低字节 0 时，以目标三点坐标与
// vt+152 参数经 ·0x4E4A50 发起 30320 号效果请求（效果 ID 常量）【推断：30320 为架招附加特效编号】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF660(uint32_t *this, int nArg2, float *pArg3, int nArg4)  // 函数: 架招命中叠加 25% 效果请求
{
  int v5; // ebx
  int v6; // eax
  int v8; // [esp-10h] [ebp-1Ch]

  v5 = sub_5AF360(this, nArg2, (int)pArg3, nArg4);  // 调 攻击命中转架招（14）入态门
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && rand() % 100 < 25 )  // 调 以 16 位种子状态递推并返回 15 位结果
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this);  // 调用虚函数（虚表槽 +348）
    if ( (*(uint8_t *)(v6 + 16) != 0 || *(float *)v6 > 0.0) && (uint8_t)nArg4 == 0 )
    {
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      sub_4E4A50(this, 30320, 0, (uint64_t)*pArg3, (uint64_t)pArg3[1], (uint64_t)pArg3[2], v8, 0, 0, 0);  // 调 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    }
  }
  return v5;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AF710 sub_5AF710 —— 对象消亡回调转架招收手
// 两路触发：被消亡对象等于 this+8600 锁定目标且 vt+840 姿态为 14（架招），或消亡对象即
// 自身而仍有锁定目标——两路均转 ·0x5AF460 完成落点安置与姿态收尾并清 8600；
// 末无条件转 ·0x4D9170 消亡通知【推断：本函数为引擎注销链上的清理回调】
// ------------------------------------------------------------
int /*userpurge*/ sub_5AF710@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)  // 实现：对象消亡回调转架招收手
{
  if ( pDwArg3 == (int *)pDwArg1[2150] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      sub_5AF460(pDwArg1, nArg2);  // 调 架招收手：投摔目标落点安置与姿态收尾
    pDwArg1[2150] = 0;
  }
  if ( pDwArg3 == pDwArg1 && pDwArg1[2150] != 0 )
  {
    sub_5AF460(pDwArg1, nArg2);  // 调 架招收手：投摔目标落点安置与姿态收尾
    pDwArg1[2150] = 0;
  }
  return sub_4D9170(pDwArg3);  // 调 消亡通知
}



// AI 相位辅助（102L）
// ------------------------------------------------------------
// 0x5AF770 sub_5AF770 —— 五参状态切换总调度（架招/蓄力/施放三分支）
// 前置：主状态 this+6556 旧值 14 → 先 ·0x5AF460 收手；旧值 8 且 ·0x41A5E0(this+7028) 为 2
// 时新态非 8 即 ·0x5AEA70 姿态收尾。新态为 8 时按自身 vt+120 与 1813 对象 vt+120 的大小
// 置 vt+148/vt+144 朝向双标志。分支 switch：5 → ·0x4DB200(24,2) 随机文案；14 → ·0x5AEDE0
// 蓄力 HOLD 起手；15 → 施放：自身 vt+136/vt+132 位置校验失败则把锁定目标 vt+128→vt+124
// →vt+120 链所得坐标经 vt+112 写回自身，并 vt+196 指向帧组 6200+4 档。收尾统一
// ·0x4E33D0 状态收尾，且新态 8 与段号门 2 且 vt+308 成立时设 vt+888(0,0,1000,1000) 窗口
// 并经 ·0x5AE410 发网络包（附态 14）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF770(int *this, int ArgList, int nArg3, int nArg4, int nArg5)  // 函数: 五参状态切换总调度（架招/蓄力/施放三分支）
{
  int v5; // ebx
  int fld_e1639; // eax  | +0x199C → nMainState6556〔族字典〕（族字典）
  int pLinkTarget7252; // edi  | +0x1C54 → 关联/锁定目标对象（CNZombie；va=005AF000）
  BOOL v9; // edi
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int fld_e2150; // eax  | +0x2198 → uAI8600〔族字典〕（族字典）
  int v16; // ebx
  int fld_e21502; // edi  | +0x2198 → uAI8600〔族字典〕（族字典）
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int result; // eax
  int v22; // [esp+Ch] [ebp-4h]

  v5 = ArgList;
  fld_e1639 = *(this + 1639);  // this+6556 = 主状态镜像
  if ( fld_e1639 != 8 )
  {
    if ( fld_e1639 == 14 )
      sub_5AF460(this, ArgList);  // 调 架招收手：投摔目标落点安置与姿态收尾
LABEL_7:
    if ( ArgList != 8 )
      goto LABEL_10;
    goto LABEL_8;
  }
  if ( sub_41A5E0((unsigned int)(this + 1757)) != 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    goto LABEL_7;
  if ( ArgList != 8 )
  {
    sub_5AEA70(this);  // 调 姿态收尾（清 8616 + vt+208 双写）
    goto LABEL_7;
  }
LABEL_8:
  if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
  {
    pLinkTarget7252 = *(this + 1813);  // this+7252 = pTarget7252
    v22 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v9 = v22 < (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pLinkTarget7252 + 120))(pLinkTarget7252);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    (*(void (/*thiscall*/ **)(int *, BOOL))(*this + 148))(this, v9);  // 调用虚函数（虚表槽 +148）【推断: 同 vmt90 但不检查（直接写）】
    (*(void (/*thiscall*/ **)(int *, BOOL))(*this + 144))(this, v9);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
  }
LABEL_10:
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      sub_4DB200(24, 2);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
      break;
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      sub_5AEDE0(this, nArg3);  // 调 HOLD 蓄力架招起手与段数插值
      break;
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      v10 = *this;
      v11 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);  // 调用虚函数（虚表槽 +124）
      v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v10 + 136))(this, v12) == 0  // 调用虚函数（虚表槽 +136）
        || (v13 = *this,
            v14 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this),  // 调用虚函数（虚表槽 +128）
            (*(uint8_t (/*thiscall*/ **)(int *, int))(v13 + 132))(this, v14) == 0) )  // 调用虚函数（虚表槽 +132）
      {
        fld_e2150 = *(this + 2150);  // this+8600 = uAI8600
        if ( fld_e2150 != 0 )
        {
          v16 = *this;
          fld_e21502 = *(this + 2150);  // this+8600 = uAI8600
          v18 = (*(int (**)(void))(*(uint32_t *)fld_e2150 + 128))();  // 调用虚函数（虚表槽 +128）
          v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21502 + 124))(fld_e21502, v18);  // 调用虚函数（虚表槽 +124）
          v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21502 + 120))(fld_e21502, v19);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          (*(void (/*thiscall*/ **)(int *, int))(v16 + 112))(this, v20);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
          v5 = ArgList;
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // this+6216 = 资源/帧游标表
      break;
    default:
      break;
  }
  result = sub_4E33D0(v5, *(float *)&nArg3, nArg4, nArg5);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( v5 == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 2 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
      result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)result != 0 )
        return sub_5AE410(this, 14);  // 调 网络包封装发送（僵尸变体：无条件附随机数）
    }
  }
  return result;
}



// 子类扩展字段复位（this+8600..8636）
// ------------------------------------------------------------
// 0x5AF910 sub_5AF910 —— 子类扩展字段整块复位
// 逐字段清零 8600/8601/8614、dword 8616（连 8617 相位双字节）、u16 8620、dword 8636、
// 8612/8613；即 5AF1C0/5AF220/5AF460/5AFA00 所依赖的锁定与相位联动面全量归零（重生或退场）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF910(int this)  // 函数: 子类扩展字段整块复位
{
  *(uint8_t *)(this + 8600) = 0;  // this+8600 子类 AI 状态字节 1
  *(uint8_t *)(this + 8601) = 0;  // this+8601 子类 AI 状态字节 2
  *(uint8_t *)(this + 8614) = 0;  // this+8614 锁定/相位字节 C
  *(uint32_t *)(this + 8616) = 0;  // this+8616 【推断】钻地相位字节1
  *(uint16_t *)(this + 8620) = 0;  // this+8620 相位双字节门
  *(uint32_t *)(this + 8636) = 0;  // this+8636 【推断】传送/钻地相位槽
  *(uint8_t *)(this + 8612) = 0;  // this+8612 锁定/相位字节 A
  *(uint8_t *)(this + 8613) = 0;  // this+8613 锁定/相位字节 B
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AF950 sub_5AF950 —— 两挂装槽释放
// 8604 槽（this+2151）非空则取其 vt 首项以参 1 释放引用并清槽；8616 槽（this+2154，粒子/
// 效果槽）非空则经 vt+84(0) 解除并清槽【推断：8616 同时被 5AF1C0 当相位标志字节写，或为重叠复用】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF950(uint32_t *this)  // 函数: 两挂装槽释放
{
  int (/*thiscall*/ ***fld_e2151)(uint32_t, int); // ecx
  int result; // eax
  int uEffectSlot8616; // ecx  | +0x21A8 → 【推断】特效对象/相位联动槽（双语义复用；this[2154] 等价）〔5B0D10 case 15 存 EF_Ha（CNDraconian；va=005AF910）

  fld_e2151 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2151);  // this+8604 = bAI8604
  if ( fld_e2151 != nullptr )  // 若 fld_e2151 有效（非空）
    result = (**fld_e2151)(fld_e2151, 1);  // 调 fld_e2151 的虚函数（vt+0）
  uEffectSlot8616 = *(this + 2154);  // this+8616 = uAI8616
  *(this + 2151) = 0;  // this+8604 = bAI8604
  if ( uEffectSlot8616 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)uEffectSlot8616 + 84))(uEffectSlot8616, 0);  // 调用虚函数（虚表槽 +84）【推断: this+156 字节存取】
    *(this + 2154) = 0;  // this+8616 = uAI8616
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AF990 sub_5AF990 —— 消亡对象引用清理
// 先经 ·0x4D9170 发消亡通知；被消亡对象即自身时以 vt+216 连刷 9/10/11/12 四档表现槽
// （退场表现/音效清场）；末比对 8636 与 8616 两槽内引用等于该对象则置 0（悬垂引用防呆）
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF990(uint32_t *this, uint32_t *uArg2)  // 函数: 消亡对象引用清理
{
  int result; // eax

  sub_4D9170(uArg2);  // 调 消亡通知
  if ( this == uArg2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 12);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
  }
  result = 0;
  if ( (uint32_t *)*(this + 2159) == uArg2 )  // this+8636 = pDollTarget
    *(this + 2159) = 0;  // this+8636 = pDollTarget
  if ( (uint32_t *)*(this + 2154) == uArg2 )  // this+8616 = uAI8616
    *(this + 2154) = 0;  // this+8616 = uAI8616
  return result;
}



// AI 字段访问（this+8600）
// ------------------------------------------------------------
// 0x5AFA00 sub_5AFA00 —— 受伤害值按攻击方档位折算
// 先经 ·0x4DC390 伤害类型过滤得原结果；返值非 3 且 8600 标志非零时改判：攻击方 vt+348
// 对象 +12 等于 1 则入伤乘 0.5 返 2；否则 +124 为 0 乘 0.35、为 1 乘 0.25，均返 2
// 【推断：+12/+124 为攻击方类别与武器档，折算为减伤比】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AFA00(uint8_t *this, int *pDwArg2, int nArg3)  // 函数: 受伤害值按攻击方档位折算
{
  int result; // eax

  result = sub_4DC390(pDwArg2, nArg3);  // 调 伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
  if ( result != 3 && *(this + 8600) != 0 )  // this+8600 子类 AI 状态字节 1
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
  return result;
}



// ============================================================
// 【分区 13】龙人静态桥接（0x5AFAB0-0x5B0000）
// 证据：DRAGONMAN_STATIC 播报 —— 龙人（Draconian）类在本区块的收尾函数，主体见 dragonman.cpp

// 静态播报：DRAGONMAN_STATIC（this+200/8601 门；龙人系首函数, 主体在 0x5B 区 dragonman.cpp）
// ------------------------------------------------------------
// 0x5AFAB0 sub_5AFAB0 —— 龙人静态待机语音播报
// 经 vt+200 取帧组对象，其 +148 等于 1 时检查字节 8601：为 0 则先 vt+216(11) 设表现档，
// 再以 vt+212 播 DRAGONMAN_STATIC，末置 8601=1 锁存防重复【推断：+148==1 为待机/静立门】
// ------------------------------------------------------------
char /*thiscall*/ sub_5AFAB0(uint8_t *this)  // 函数: 龙人静态待机语音播报
{
  int pThis_C8; // eax

  pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
  if ( *(uint32_t *)(pThis_C8 + 148) == 1 )  // this+148 第 4 组·+802 增量子倍率
  {
    LOBYTE(pThis_C8) = *(this + 8601);  // this+8601 = 子类 AI 状态字节 2
    if ( (uint8_t)pThis_C8 == 0 )
    {
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 11);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
      LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                     this,
                     "DRAGONMAN_STATIC",  // 资源/动画 TAG DRAGONMAN_STATIC
                     -1,
                     0,
                     0);
      *(this + 8601) = 1;  // this+8601 = 子类 AI 状态字节 2
    }
  }
  return pThis_C8;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AFB00 sub_5AFB00 —— 攻击态反击追加执行与伤害日志
// 先无条件转 ·0x4DB480 反击/架招触发判定；门列：vt+840 姿态为 8（攻击）、·0x41A5E0
// (this+7028) 段号门为 1、vt+308 可行动、目标 vt+40 类型 17、nArg4 低字节 0。通过后把
// 目标 vt+736 值三分：1/3 经 vt+728 立即结算，余 2/3 为 v6 经 ·0x4D5330 写伤害日志
// （DNF.trc）并作为返回值【推断：736/728 为伤害数值与结算槽，三分比为反击追偿比例】
// ------------------------------------------------------------
int /*thiscall*/ sub_5AFB00(void *this, int nArg2, int nArg3, int nArg4)  // 函数: 攻击态反击追加执行与伤害日志
{
  int v5; // ebx
  int v6; // edi

  sub_4DB480(nArg2, nArg3, nArg4);  // 调 ★ 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) != 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    || sub_41A5E0((unsigned int)this + 7028) != 1  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    || (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) == 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    || (uint8_t)nArg4 != 0 )
  {
    return 0;
  }
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 736))(nArg2) / 3;  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 736))(nArg2) - v5;  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
  (*(void (/*thiscall*/ **)(int, int, uint32_t, void *))(*(uint32_t *)nArg2 + 728))(nArg2, v5, 0, this);  // 调用虚函数（虚表槽 +728）【推断: ★★ HP setter / DMGAPPLY vt+728（研…】
  if ( v6 != 0 )
    sub_4D5330(this, nArg2, nArg3, v6, v6, 1, 0, 0);  // 调 伤害日志写出（DNF.trc；研究 §2⑦ 定案勿与 HP setter 混淆）
  return v6;
}


