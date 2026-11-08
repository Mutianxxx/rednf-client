// ============================================================
// 【40JP逆向源代码工程】game/missing_misc_a.cpp
// 模块: 0x48-0x4F 区补漏（会话 5 精确审计后补齐，三轮审计合并）
// 来源: work/dump_missing-audit.txt  区块: 0x480000-0x4F0000（散装）
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 105
// ------------------------------------------------------------
// ★ 内容定性（本文件 90% 为 3 行小桩）：
//   ① 0x48-0x4B 区：虚表槽残件 —— 字段偏移 getter（return this+N / *(this+N)）、
//      thunk 尾链转发、nullsub 空桩（转写任务规范§二.6：桩也逐一还原）
//   ② 0x4D-0x4E 区：数据对象/容器清理残件（递归树释放、vector 清理、链表重置、
//      字段重置族 —— 与 combat_core.cpp 0x4D 区对象工厂配套的析构侧）
//   ③ 已知锚点：0x498EF0 → sub_4A0650（P38 速率链 vt+980 应用层薄壳）；
//      0x4B3D10 → sub_5E5260（动画子对象析构，P30 子动画链）
// 注释体例：字段桩标注偏移；thunk/转发标注目标；带【】者为手写证据注释。
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============
// 【分区 1】第一轮审计：0x48-0x4B 区虚表槽残件（0x483C50-0x4BCE40）
// 字段偏移 getter/setter 薄壳、thunk 尾链、nullsub 空桩 —— 各主文件虚表的散落槽位实现。
// ============

// 0x483C50 unknown_libname_4
// ------------------------------------------------------------
// 薄转发（→ unknown_libname_4）

// Microsoft VisualC 2-14/net runtime
int /*thiscall*/ unknown_libname_4(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 0;  // this+4 = pHostObj
  *(this + 2) = 0;  // this+8 = 技能槽记录首字
  return 0;
}



// ------------------------------------------------------------
// 0x4859E0 sub_4859E0
// ------------------------------------------------------------
// 薄转发（→ sub_4859E0）

int /*thiscall*/ sub_4859E0(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 84))(this);  // 调用虚函数（虚表槽 +84）【推断: this+156 字节存取】
}



// ------------------------------------------------------------
// 0x485A90 sub_485A90
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

int /*thiscall*/ sub_485A90(void *this)
{
  return sub_41A5E0((unsigned int)this + 132);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x498EF0 sub_498EF0
// ------------------------------------------------------------
// 【P38 锚点】速度应用层薄壳：→ sub_4A0650（vt+980 移动速度应用，P38-3 链）

int /*stdcall*/ sub_498EF0(int nArg1)  // 实现：(P38 锚点)速度应用层薄壳：→ sub_4A0650（vt+980 移动速度应用，P38-3 链）
{
  return sub_4A0650(nArg1);
}



// ------------------------------------------------------------
// 0x49EC00 sub_49EC00
// ------------------------------------------------------------
// 薄转发（→ sub_49EC00）

int /*thiscall*/ sub_49EC00(uint32_t *this)
{
  uint32_t *pThis_4; // ecx

  pThis_4 = this + 4;
  *pThis_4 = &CNWarRoom::`vftable';  // vftable 复位
  return nullsub_3(pThis_4);  // 返回 调 nullsub_3
}



// ------------------------------------------------------------
// 0x4A0D50 sub_4A0D50
// ------------------------------------------------------------
// 字段基址 getter：return this + 388（虚表槽残件）

char */*thiscall*/ sub_4A0D50(char *this)  // 实现：字段基址 getter：return this + 388（虚表槽残件）
{
  return this + 388;  // 返回 this + 388
}



// ------------------------------------------------------------
// 0x4A0D90 sub_4A0D90
// ------------------------------------------------------------
// 字段读取桩：return *(this + 79)（虚表槽残件）

int /*thiscall*/ sub_4A0D90(uint32_t *this)  // 实现：字段读取桩：return *(this + 79)（虚表槽残件）
{
  return *(this + 79);
}



// ------------------------------------------------------------
// 0x4A0E50 sub_4A0E50
// ------------------------------------------------------------
// 字段读取桩：return *(this + 154)（虚表槽残件）

int /*thiscall*/ sub_4A0E50(uint32_t *this)  // 实现：字段读取桩：return *(this + 154)（虚表槽残件）
{
  return *(this + 154);  // this+616〔nReactionState〕
}



// ------------------------------------------------------------
// 0x4A0E90 sub_4A0E90
// ------------------------------------------------------------
// 字段读取桩：return *(this + 641)（虚表槽残件）

char /*thiscall*/ sub_4A0E90(uint8_t *this)  // 实现：字段读取桩：return *(this + 641)（虚表槽残件）
{
  return *(this + 641);
}



// ------------------------------------------------------------
// 0x4A1060 sub_4A1060
// ------------------------------------------------------------
// 字段读取桩：return *(this + 1686)（虚表槽残件）

int /*thiscall*/ sub_4A1060(uint32_t *this)  // 实现：字段读取桩：return *(this + 1686)（虚表槽残件）
{
  return *(this + 1686);  // this+6744〔nFrozenFlag〕
}



// ------------------------------------------------------------
// 0x4A1090 sub_4A1090
// ------------------------------------------------------------
// 字段读取桩：return *(this + 1700)（虚表槽残件）

int /*thiscall*/ sub_4A1090(uint32_t *this)  // 实现：字段读取桩：return *(this + 1700)（虚表槽残件）
{
  return *(this + 1700);  // this+6800 = 炮车/子类参数面槽 3
}



// ------------------------------------------------------------
// 0x4A10C0 sub_4A10C0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 1708)（虚表槽残件）

int /*thiscall*/ sub_4A10C0(uint32_t *this)  // 实现：字段读取桩：return *(this + 1708)（虚表槽残件）
{
  return *(this + 1708);
}



// ------------------------------------------------------------
// 0x4A6120 sub_4A6120
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

int /*thiscall*/ sub_4A6120(char *this, char pszArg2)
{
  return sub_4A6130(this - 8600, pszArg2);  // 调 CNGoblinAssaulter 删除析构壳
}



// ------------------------------------------------------------
// 0x4A70F0 sub_4A70F0
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

int /*thiscall*/ sub_4A70F0(char *this, char pszArg2)
{
  return sub_4A6EB0(this - 8600, pszArg2);  // 调 CNGoblinKagelBase 删除析构壳
}



// ------------------------------------------------------------
// 0x4AB6A0 sub_4AB6A0
// ------------------------------------------------------------
// 薄转发（→ sub_4AB6A0）

char sub_4AB6A0()
{
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4B10A0 nullsub_2
// ------------------------------------------------------------
// 空桩（nullsub，调用即返回）

void /*stdcall*/ nullsub_2(int nArg1, int nArg2, int nArg3, int nArg4)  // 实现：空桩（nullsub，调用即返回）
{
  ;
}



// ------------------------------------------------------------
// 0x4B3D10 sub_4B3D10
// ------------------------------------------------------------
// 【P30 锚点】动画子对象析构：sub_5E5260(this+20)（子动画链节点释放）

void /*thiscall*/ sub_4B3D10(void **this)  // 【→ sub_5E5260（动画子对象析构，P30 子动画链）】
{
  sub_5E5260(this + 20);  // this+80 = nAuraStage
}



// ------------------------------------------------------------
// 0x4BAC90 sub_4BAC90
// ------------------------------------------------------------
// 字段读取桩：return *(this + 321)（虚表槽残件）

int /*thiscall*/ sub_4BAC90(uint32_t *this)  // 实现：字段读取桩：return *(this + 321)（虚表槽残件）
{
  return *(this + 321);  // this+1284 = 效果触发计数
}



// ------------------------------------------------------------
// 0x4BACF0 sub_4BACF0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 320)（虚表槽残件）

int /*thiscall*/ sub_4BACF0(uint32_t *this)  // 实现：字段读取桩：return *(this + 320)（虚表槽残件）
{
  return *(this + 320);
}



// ------------------------------------------------------------
// 0x4BAD30 sub_4BAD30
// ------------------------------------------------------------
// 字段读取桩：return *(this + 333)（虚表槽残件）

int /*thiscall*/ sub_4BAD30(uint32_t *this)  // 实现：字段读取桩：return *(this + 333)（虚表槽残件）
{
  return *(this + 333);  // this+1332 = 装备/动画定义对象
}



// ------------------------------------------------------------
// ============
// 【分区 2】第一轮审计：0x4D-0x4E 区数据对象/容器清理残件（0x4D08F0-0x4E1FB0）
// 递归树释放（0x4D08F0）、vector 逐元素清理（0x4D09A0）、字段族重置（0x4D0F00/0x4D0D00）、
// 链表/list 重置（0x4D1350）、大清理（0x4D13A0）—— combat_core.cpp 0x4D 区对象工厂的析构侧。
// ============

// 0x4D08F0 sub_4D08F0
// ------------------------------------------------------------
// 递归树节点释放（+69 哨兵，沿 +0/+16 链 sub_4CEA60 + free）

char /*stdcall*/ sub_4D08F0(void **Block)  // 实现：递归树节点释放（+69 哨兵，沿 +0/+16 链 sub_4CEA60 + free）
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 69);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4D08F0(i[2]);
    i = (void **)*i;
    sub_4CEA60(Block2);
    j__free(Block2);  // 调 堆释放
    result = *((uint8_t *)i + 69);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D09A0 sub_4D09A0
// ------------------------------------------------------------
// vector 逐元素清理（56B/元素，sub_4CE820）→ 整块 free

int /*thiscall*/ sub_4D09A0(int *this)  // 实现：vector 逐元素清理（56B/元素，sub_4CE820）→ 整块 free
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);  // this+4 = pHostObj
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 56 )  // this+8 = 技能槽记录首字
      sub_4CE820(fld_e1);
    j__free((void *)*(this + 1));  // this+4 = pHostObj
    result = 0;
  }
  *(this + 1) = 0;  // this+4 = pHostObj
  *(this + 2) = 0;  // this+8 = 技能槽记录首字
  *(this + 3) = 0;  // this+12 = 技能槽记录次字
  return result;
}



// ------------------------------------------------------------
// 0x4D0AE0 sub_4D0AE0
// ------------------------------------------------------------
// 容器清理（17L：多 vector 逐段释放）

void /*thiscall*/ sub_4D0AE0(int this)  // 实现：容器清理（17L：多 vector 逐段释放）
{
  int fld_28; // eax
  int pThis_24; // esi

  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(this + 28) = 0;  // this+112 = pHostComp
  *(uint8_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  fld_28 = *(uint32_t *)(this + 40);  // this+40〔bStateSub40(推断)〕等 2 字段
  pThis_24 = this + 36;
  if ( fld_28 != 0 )
  {
    sub_42CC00(fld_28, *(uint32_t *)(pThis_24 + 8));  // 调 16 字节槽组释放
    j__free(*(void **)(pThis_24 + 4));  // 调 堆释放
  }
  *(uint32_t *)(pThis_24 + 4) = 0;  // pThis_24+4〔宿主对象〕
  *(uint32_t *)(pThis_24 + 8) = 0;  // pThis_24+8〔nSkillRec8(推断)〕
  *(uint32_t *)(pThis_24 + 12) = 0;  // pThis_24+12〔nSkillRec12(推断)〕
}



// ------------------------------------------------------------
// 0x4D0C30 sub_4D0C30
// ------------------------------------------------------------
// 容器清理（29L）

int /*thiscall*/ sub_4D0C30(int this)  // 实现：容器清理（29L）
{
  sub_423A20(this);  // 调 小结构初始化（0-100 刻度）
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
  *(uint32_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  *(uint8_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 156) = 100;  // this+156〔nAdd156(推断)〕
  *(uint32_t *)(this + 160) = 100;  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 164) = 100;  // this+164〔fAdd164(推断)〕
  *(uint8_t *)(this + 168) = 1;  // this+672 = 拾取/交互目标有效标志
  *(uint32_t *)(this + 184) = 0;  // this+184〔bSingleTarget(推断)〕
  *(uint32_t *)(this + 188) = 0;  // this+188〔nStatusIdx(推断)〕
  *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
  *(uint32_t *)(this + 220) = 15;  // this+220〔nSnapDst220(推断)〕
  *(uint32_t *)(this + 216) = 0;  // this+216〔bField216(推断)〕
  *(uint8_t *)(this + 200) = 0;  // this+200〔nMainState(推断)〕
  sub_4D0B90(this);
  return this;
}



// ------------------------------------------------------------
// 0x4D1020 sub_4D1020
// ------------------------------------------------------------
// 容器清理（16L）

int /*thiscall*/ sub_4D1020(uint32_t *this)  // 实现：容器清理（16L）
{
  uint32_t *fld_e25; // eax

  *this = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = -1;  // this+92 = pFxObjC
  sub_4D08F0(*(void ***)(*(this + 25) + 4));  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(*(this + 25) + 4) = *(this + 25);  // this+100〔bEnchantDone(推断)〕
  fld_e25 = (uint32_t *)*(this + 25);  // this+100〔bEnchantDone(推断)〕
  *(this + 26) = 0;  // this+104〔nTimerEnd(推断)〕
  *fld_e25 = fld_e25;
  *(uint32_t *)(*(this + 25) + 8) = *(this + 25);  // this+100〔bEnchantDone(推断)〕
  return sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x4D1140 sub_4D1140
// ------------------------------------------------------------
// 大清理（67L）：+304/+284/+260… 多段 vector 逐段 free 清零

void /*thiscall*/ sub_4D1140(int this)  // 实现：大清理（67L）：+304/+284/+260… 多段 vector 逐段 free 清零
{
  int fld_A8; // eax

  if ( *(uint32_t *)(this + 304) != 0 )  // this+304〔pLayer304(推断)〕
    j__free(*(void **)(this + 304));  // 调 堆释放
  *(uint32_t *)(this + 304) = 0;  // this+304〔pLayer304(推断)〕
  *(uint32_t *)(this + 308) = 0;  // this+1232〔pNameTagCtrl(推断)〕
  *(uint32_t *)(this + 312) = 0;
  if ( *(uint32_t *)(this + 284) != 0 )  // this+284〔bBindGate284(推断)〕
    j__free(*(void **)(this + 284));  // 调 堆释放
  *(uint32_t *)(this + 284) = 0;  // this+284〔bBindGate284(推断)〕
  *(uint32_t *)(this + 288) = 0;  // this+288〔pMaster288(推断)〕
  *(uint32_t *)(this + 292) = 0;  // this+292〔nOpenMode292(推断)〕
  if ( *(uint32_t *)(this + 260) != 0 )  // this+260〔nQuad4〕
    j__free(*(void **)(this + 260));  // 调 堆释放
  *(uint32_t *)(this + 260) = 0;  // this+260〔nQuad4〕
  *(uint32_t *)(this + 264) = 0;  // this+264〔nAnimHandle(推断)〕
  *(uint32_t *)(this + 268) = 0;
  if ( *(uint32_t *)(this + 228) != 0 )  // this+228〔nSnapDst228(推断)〕
    j__free(*(void **)(this + 228));  // 调 堆释放
  *(uint32_t *)(this + 228) = 0;  // this+228〔nSnapDst228(推断)〕
  *(uint32_t *)(this + 232) = 0;  // this+232〔bSyncFlag〕
  *(uint32_t *)(this + 236) = 0;  // this+944 = 名字已播出标志
  if ( *(uint32_t *)(this + 212) != 0 )  // this+212〔nField212(推断)〕
    j__free(*(void **)(this + 212));  // 调 堆释放
  *(uint32_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  *(uint32_t *)(this + 216) = 0;  // this+216〔bField216(推断)〕
  *(uint32_t *)(this + 220) = 0;  // this+220〔nSnapDst220(推断)〕
  if ( *(uint32_t *)(this + 184) != 0 )  // this+184〔bSingleTarget(推断)〕
    j__free(*(void **)(this + 184));  // 调 堆释放
  *(uint32_t *)(this + 184) = 0;  // this+184〔bSingleTarget(推断)〕
  *(uint32_t *)(this + 188) = 0;  // this+188〔nStatusIdx(推断)〕
  *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
  fld_A8 = *(uint32_t *)(this + 168);  // this+672 = 拾取/交互目标有效标志
  if ( fld_A8 != 0 )
  {
    sub_42CC00(fld_A8, *(uint32_t *)(this + 172));  // 调 16 字节槽组释放
    j__free(*(void **)(this + 168));  // this+672 = 拾取/交互目标有效标志
  }
  *(uint32_t *)(this + 168) = 0;  // this+672 = 拾取/交互目标有效标志
  *(uint32_t *)(this + 172) = 0;  // this+688 = 表现/名字快照[2]
  *(uint32_t *)(this + 176) = 0;  // this+704 = 表现/名字快照[24]
  if ( *(uint32_t *)(this + 144) != 0 )  // this+144〔pFrameList144(推断)〕等 2 字段
    j__free(*(void **)(this + 144));  // 调 堆释放
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 112) >= 0x10u )  // this+112〔pHostComp112〕
    j__free(*(void **)(this + 92));  // 调 堆释放
  *(uint32_t *)(this + 112) = 15;  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
  *(uint8_t *)(this + 92) = 0;  // this+92〔pFxObjC(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 84) >= 0x10u )  // this+84〔pFxObjA(推断)〕
    j__free(*(void **)(this + 64));  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 84) = 15;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  *(uint8_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  if ( *(uint32_t *)(this + 56) >= 0x10u )  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    j__free(*(void **)(this + 36));  // this+144 = pFrameList144
  *(uint32_t *)(this + 56) = 15;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint8_t *)(this + 36) = 0;  // this+144 = pFrameList144
  if ( *(uint32_t *)(this + 28) >= 0x10u )  // this+112 = pHostComp
    j__free(*(void **)(this + 8));  // 调 堆释放
  *(uint32_t *)(this + 28) = 15;  // this+112 = pHostComp
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
}



// ------------------------------------------------------------
// 0x4D1350 sub_4D1350
// ------------------------------------------------------------
// list 复位（27L：哨兵节点自指 + +8 计数清零）

uint32_t */*thiscall*/ sub_4D1350(uint32_t *this)  // 实现：list 复位（27L：哨兵节点自指 + +8 计数清零）
{
  uint32_t **fld_e1; // eax
  uint32_t *v3; // esi
  uint32_t *result; // eax
  bool fld_e12; // zf
  uint32_t *v6; // ebx

  fld_e1 = (uint32_t **)*(this + 1);  // this+4 = pHostObj
  v3 = *fld_e1;
  *fld_e1 = fld_e1;
  result = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  result[1] = result;
  fld_e12 = v3 == (uint32_t *)*(this + 1);  // this+4 = pHostObj
  *(this + 2) = 0;  // this+8 = 技能槽记录首字
  if ( !fld_e12 )
  {
    do
    {
      v6 = (uint32_t *)*v3;
      sub_4CFE70(v3);
      j__free(v3);  // 调 堆释放
      result = (uint32_t *)*(this + 1);  // this+4 = pHostObj
      v3 = v6;
    }
    while ( v6 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D1640 sub_4D1640
// ------------------------------------------------------------
// 清理薄壳（5L）

void /*thiscall*/ sub_4D1640(void **this)  // 实现：清理薄壳（5L）
{
  sub_4D1310(this);
  j__free(*(this + 1));  // this+4 = pHostObj
  *(this + 1) = nullptr;  // this+4 = pHostObj
}



// ------------------------------------------------------------
// 0x4D5F40 unknown_libname_5
// ------------------------------------------------------------
// 薄转发（→ unknown_libname_5）

// Microsoft VisualC 2-14/net runtime
int /*thiscall*/ unknown_libname_5(uint32_t *this, int nArg2)
{
  *(this + 4) = nArg2;  // this+16〔nChannelTypeSel(推断)〕
  return nArg2;
}



// ------------------------------------------------------------
// 0x4D5F70 sub_4D5F70
// ------------------------------------------------------------
// 桩（3L）

int /*thiscall*/ sub_4D5F70(void *this)  // 实现：桩（3L）
{
  return sub_699000((int)this + 60);  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x4D9F40 sub_4D9F40
// ------------------------------------------------------------
// 桩（3L）

int /*thiscall*/ sub_4D9F40(void *this)  // 实现：桩（3L）
{
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1104))(this, 13);  // 调用虚函数（虚表槽 +1104）
}



// ------------------------------------------------------------
// 0x4E1F20 sub_4E1F20
// ------------------------------------------------------------
// 字段读取桩：return *(this + 220)（虚表槽残件）

int /*thiscall*/ sub_4E1F20(uint32_t *this)  // 实现：字段读取桩：return *(this + 220)（虚表槽残件）
{
  return *(this + 220);
}



// ------------------------------------------------------------
// 0x4E1F50 sub_4E1F50
// ------------------------------------------------------------
// 字段读取桩：return *(this + 223)（虚表槽残件）

int /*thiscall*/ sub_4E1F50(uint32_t *this)  // 实现：字段读取桩：return *(this + 223)（虚表槽残件）
{
  return *(this + 223);
}



// ------------------------------------------------------------
// 0x4E1F80 sub_4E1F80
// ------------------------------------------------------------
// 字段读取桩：return *(this + 226)（虚表槽残件）

int /*thiscall*/ sub_4E1F80(uint32_t *this)  // 实现：字段读取桩：return *(this + 226)（虚表槽残件）
{
  return *(this + 226);
}



// ------------------------------------------------------------
// 0x4E1FB0 sub_4E1FB0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 240)（虚表槽残件）

int /*thiscall*/ sub_4E1FB0(uint32_t *this)  // 实现：字段读取桩：return *(this + 240)（虚表槽残件）
{
  return *(this + 240);  // this+960〔nBigStateMirror960(推断)〕
}



// ------------------------------------------------------------
// ============
// 【分区 3】第二轮审计补漏：0x48-0x4B 区（0x481250-0x4BCE40）
// ============

// 0x481250 sub_481250
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int /*thiscall*/ sub_481250(int *this)
{
  return sub_480F70(this);  // 调 44 字节条目容器析构（+4/+8/+12 三字段）
}



// ------------------------------------------------------------
// 0x485980 sub_485980
// ------------------------------------------------------------
// 字段基址 getter：return this + 8（虚表槽残件）

char */*thiscall*/ sub_485980(char *this)  // 实现：字段基址 getter：return this + 8（虚表槽残件）
{
  return this + 8;  // 返回 this + 8
}



// ------------------------------------------------------------
// 0x485A10 sub_485A10
// ------------------------------------------------------------
// 字段读取桩：return *(this + 9)（虚表槽残件）

BOOL /*thiscall*/ sub_485A10(uint32_t *this)  // 实现：字段读取桩：return *(this + 9)（虚表槽残件）
{
  return *(this + 9) != 2;  // this+36 = 状态字
}



// ------------------------------------------------------------
// 0x497180 sub_497180
// ------------------------------------------------------------
// 薄转发（→ sub_497180）

int /*thiscall*/ sub_497180(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 40))(this);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
}



// ------------------------------------------------------------
// 0x499790 sub_499790
// ------------------------------------------------------------
// 薄转发（→ sub_499790）

void /*thiscall*/ sub_499790(uint8_t *this)
{
  *(this + 276) = 0;  // this+1104〔nResetClock1104(推断)〕
}



// ------------------------------------------------------------
// 0x49F320 sub_49F320
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int /*thiscall*/ sub_49F320(uint32_t *this)
{
  return sub_49F0E0(this);  // 调 槽数组树整体清空（逐槽递归释放 + header 自环复位）
}



// ------------------------------------------------------------
// 0x4A0D60 sub_4A0D60
// ------------------------------------------------------------
// 字段基址 getter：return this + 540（虚表槽残件）

char */*thiscall*/ sub_4A0D60(char *this)  // 实现：字段基址 getter：return this + 540（虚表槽残件）
{
  return this + 540;  // 返回 this + 540
}



// ------------------------------------------------------------
// 0x4A0DA0 sub_4A0DA0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 80)（虚表槽残件）

int /*thiscall*/ sub_4A0DA0(uint32_t *this)  // 实现：字段读取桩：return *(this + 80)（虚表槽残件）
{
  return *(this + 80);
}



// ------------------------------------------------------------
// 0x4A0E60 sub_4A0E60
// ------------------------------------------------------------
// 薄转发（→ sub_4A0E60）

void /*thiscall*/ sub_4A0E60(uint32_t *this)
{
  *(this + 154) = -1;  // this+616〔nReactionState〕
}



// ------------------------------------------------------------
// 0x4A0EA0 sub_4A0EA0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 642)（虚表槽残件）

char /*thiscall*/ sub_4A0EA0(uint8_t *this)  // 实现：字段读取桩：return *(this + 642)（虚表槽残件）
{
  return *(this + 642);  // this+642 = 帧时刻覆盖开关
}



// ------------------------------------------------------------
// 0x4A1070 sub_4A1070
// ------------------------------------------------------------
// 字段读取桩：return *(this + 1661)（虚表槽残件）

int /*thiscall*/ sub_4A1070(uint32_t *this)  // 实现：字段读取桩：return *(this + 1661)（虚表槽残件）
{
  return *(this + 1661);  // this+6644〔nSubGate〕
}



// ------------------------------------------------------------
// 0x4A10A0 sub_4A10A0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 7092)（虚表槽残件）

char /*thiscall*/ sub_4A10A0(uint8_t *this)  // 实现：字段读取桩：return *(this + 7092)（虚表槽残件）
{
  return *(this + 7092);  // 返回 this + 28368 处指针
}



// ------------------------------------------------------------
// 0x4A1EA0 sub_4A1EA0
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

int /*thiscall*/ sub_4A1EA0(void *this)
{
  return sub_41A5E0((unsigned int)this + 6146);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4A64E0 sub_4A64E0
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

void */*thiscall*/ sub_4A64E0(char *this, char pszArg2)
{
  return sub_4A64F0(this - 8600, pszArg2);  // 调 CNBunker_Woker 删除析构壳
}



// ------------------------------------------------------------
// 0x4A9E40 sub_4A9E40
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int sub_4A9E40()
{
  return sub_5B77F0();  // 调 行为字节拍（高概率化变体）
}



// ------------------------------------------------------------
// 0x4B09A0 sub_4B09A0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 2053)（虚表槽残件）

int /*thiscall*/ sub_4B09A0(uint32_t *this)  // 实现：字段读取桩：return *(this + 2053)（虚表槽残件）
{
  return *(this + 2053);  // this+8212〔pHintText8212〕
}



// ------------------------------------------------------------
// 0x4B1210 sub_4B1210
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int /*thiscall*/ sub_4B1210(void *this)
{
  return sub_5F6FB0(this);
}



// ------------------------------------------------------------
// 0x4B5B70 sub_4B5B70
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int /*thiscall*/ sub_4B5B70(void ***this)
{
  return sub_4B5A50(this);  // 调 帧对象数组析构（·0x42AF90 后 228 字节池回收）
}



// ------------------------------------------------------------
// 0x4BACB0 sub_4BACB0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 1276)（虚表槽残件）

char /*thiscall*/ sub_4BACB0(uint8_t *this)  // 实现：字段读取桩：return *(this + 1276)（虚表槽残件）
{
  return *(this + 1276);  // this+1276 = 效果触发已激活标志
}



// ------------------------------------------------------------
// 0x4BAD00 sub_4BAD00
// ------------------------------------------------------------
// 字段基址 getter：return this + 1288（虚表槽残件）

char */*thiscall*/ sub_4BAD00(char *this)  // 实现：字段基址 getter：return this + 1288（虚表槽残件）
{
  return this + 1288;  // 返回 this + 1288
}



// ------------------------------------------------------------
// 0x4BCE40 sub_4BCE40
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int /*thiscall*/ sub_4BCE40(uint8_t *this)
{
  return sub_499C70(this);  // 调 ★主播放驱动
}



// ------------------------------------------------------------
// ============
// 【分区 4】第二轮审计补漏：0x4D-0x4E 区（0x4D0940-0x4E1FA0）
// ============

// 0x4D0940 sub_4D0940
// ------------------------------------------------------------
// 散装补漏小函数（3L）【语义未逐行展开】

void /*stdcall*/ sub_4D0940(int nArg1, int nArg2)
{
  int i; // esi

  for ( i = nArg1; i != nArg2; i += 56 )
    sub_4CE820(i);
}



// ------------------------------------------------------------
// 0x4D09E0 sub_4D09E0
// ------------------------------------------------------------
// vector 逐元素清理变体（18L）

int /*thiscall*/ sub_4D09E0(int this)  // 实现：vector 逐元素清理变体（18L）
{
  char *fld_4; // esi
  int result; // eax
  char *i; // edi

  fld_4 = *(char **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  result = 0;
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
  {
    for ( i = *(char **)(this + 8); fld_4 != i; fld_4 += 36 )  // this+32〔nHeight(推断)〕
      sub_501490(fld_4);  // 调 对象析构后释放堆块
    j__free(*(void **)(this + 4));  // 调 堆释放
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
  return result;
}



// ------------------------------------------------------------
// 0x4D0B30 sub_4D0B30
// ------------------------------------------------------------
// 容器清理（10L）

int /*thiscall*/ sub_4D0B30(int this)  // 实现：容器清理（10L）
{
  *(uint32_t *)(this + 24) = 15;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 20) = 0;  // this+80 = nAuraStage
  *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  sub_4D0AE0();
  return this;
}



// ------------------------------------------------------------
// 0x4D0D00 sub_4D0D00
// ------------------------------------------------------------
// 字段族重置（72L）：*this=−1、szPassword 空串 ×4、+116..+212 默认值填充（对象复位底座）

void /*thiscall*/ sub_4D0D00(void *this)  // 实现：字段族重置（72L）：*this=−1、szPassword 空串 ×4、+116..+212 默认值填充（对象复位底座）
{
  int pThis_2A; // eax

  *(uint32_t *)this = -1;  // *this = -1
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 29) = 0;  // this+116〔会话上下文〕
  *((uint32_t *)this + 31) = 0;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
  *((uint32_t *)this + 32) = -1;  // this+128〔szStatusKeyBuf(推断)〕
  *((uint32_t *)this + 51) = -1;  // this+204〔pSubAnim204(推断)〕
  *((uint8_t *)this + 120) = 0;  // this+120 = 动画对象指针
  *((uint32_t *)this + 33) = 4;  // this+132〔nAgeTicks〕
  *((uint32_t *)this + 34) = -1;  // this+136〔nCtx136(推断)〕
  if ( *((uint32_t *)this + 36) != 0 )  // this+144 = pFrameList144
    j__free(*((void **)this + 36));  // 调 堆释放
  *((uint32_t *)this + 36) = 0;  // this+144 = pFrameList144
  *((uint32_t *)this + 37) = 0;  // this+148〔fAdd148(推断)〕
  *((uint32_t *)this + 38) = 0;  // this+152〔nAdd152(推断)〕
  *((uint32_t *)this + 39) = 0;  // this+156〔nAdd156(推断)〕
  *((uint32_t *)this + 40) = 0;  // this+160〔fAdd160(推断)〕
  pThis_2A = *((uint32_t *)this + 42);  // this+168〔pAppendVec(推断)〕
  if ( pThis_2A != 0 )
  {
    sub_42CC00(pThis_2A, *((uint32_t *)this + 43));  // 调 16 字节槽组释放
    j__free(*((void **)this + 42));  // 调 堆释放
  }
  *((uint32_t *)this + 42) = 0;  // this+168〔pAppendVec(推断)〕
  *((uint32_t *)this + 43) = 0;  // this+172〔pAppendVecEnd(推断)〕
  *((uint32_t *)this + 44) = 0;  // this+176〔pAppendVecCap(推断)〕
  if ( *((uint32_t *)this + 46) != 0 )  // this+184〔bSingleTarget(推断)〕
    j__free(*((void **)this + 46));  // 调 堆释放
  *((uint32_t *)this + 46) = 0;  // this+184〔bSingleTarget(推断)〕
  *((uint32_t *)this + 47) = 0;  // this+188〔nStatusIdx(推断)〕
  *((uint32_t *)this + 48) = 0;  // this+192〔nDlgId(推断)〕
  *((uint32_t *)this + 49) = 0;
  *((uint8_t *)this + 200) = 0;  // this+200〔nMainState(推断)〕
  if ( *((uint32_t *)this + 53) != 0 )  // this+212〔nField212(推断)〕
    j__free(*((void **)this + 53));  // 调 堆释放
  *((uint32_t *)this + 53) = 0;  // this+212〔nField212(推断)〕
  *((uint32_t *)this + 54) = 0;  // this+216〔bField216(推断)〕
  *((uint32_t *)this + 55) = 0;  // this+220〔nSnapDst220(推断)〕
  if ( *((uint32_t *)this + 57) != 0 )  // this+228〔nSnapDst228(推断)〕
    j__free(*((void **)this + 57));  // 调 堆释放
  *((uint32_t *)this + 57) = 0;  // this+228〔nSnapDst228(推断)〕
  *((uint32_t *)this + 58) = 0;  // this+232 = 基类时刻同步开关位
  *((uint32_t *)this + 59) = 0;  // this+236 = 基类时刻同步参数 A
  *((uint32_t *)this + 60) = -1;  // this+240 = 基类时刻同步参数 B
  *((uint32_t *)this + 61) = -1;  // this+244 = 基类浮点时刻槽
  *((uint32_t *)this + 62) = -1;  // this+248 = 基类四元组字节槽 1
  *((uint32_t *)this + 63) = -1;  // this+252 = 基类四元组 dword 槽 2
  if ( *((uint32_t *)this + 65) != 0 )  // this+260 = 基类四元组 dword 槽 4
    j__free(*((void **)this + 65));  // 调 堆释放
  *((uint32_t *)this + 65) = 0;  // this+260 = 基类四元组 dword 槽 4
  *((uint32_t *)this + 66) = 0;  // this+264〔nAnimHandle(推断)〕
  *((uint32_t *)this + 67) = 0;
  *((uint32_t *)this + 68) = 0;
  *((uint32_t *)this + 69) = 0;  // this+276〔pMapEntry〕
  if ( *((uint32_t *)this + 71) != 0 )  // this+284〔bBindGate284(推断)〕
    j__free(*((void **)this + 71));  // 调 堆释放
  *((uint32_t *)this + 71) = 0;  // this+284〔bBindGate284(推断)〕
  *((uint32_t *)this + 72) = 0;  // this+288〔pMaster288(推断)〕
  *((uint32_t *)this + 73) = 0;  // this+292〔nOpenMode292(推断)〕
  *((uint32_t *)this + 74) = 0;  // this+296〔bInitFlag296(推断)〕
  if ( *((uint32_t *)this + 76) != 0 )  // this+304〔pLayer304(推断)〕
    j__free(*((void **)this + 76));  // 调 堆释放
  *((uint32_t *)this + 76) = 0;  // this+304〔pLayer304(推断)〕
  *((uint32_t *)this + 77) = 0;
  *((uint32_t *)this + 78) = 0;
  *((uint32_t *)this + 79) = -1;
  *((uint8_t *)this + 320) = 0;
}



// ------------------------------------------------------------
// 0x4D10A0 sub_4D10A0
// ------------------------------------------------------------
// 容器清理（19L）

void /*thiscall*/ sub_4D10A0(int this)  // 实现：容器清理（19L）
{
  int fld_28; // eax
  int pThis_24; // esi

  fld_28 = *(uint32_t *)(this + 40);  // this+40〔bStateSub40(推断)〕等 2 字段
  pThis_24 = this + 36;
  if ( fld_28 != 0 )
  {
    sub_42CC00(fld_28, *(uint32_t *)(this + 44));  // 调 16 字节槽组释放
    j__free(*(void **)(pThis_24 + 4));  // 调 堆释放
  }
  *(uint32_t *)(pThis_24 + 4) = 0;  // pThis_24+4〔宿主对象〕
  *(uint32_t *)(pThis_24 + 8) = 0;  // pThis_24+8〔nSkillRec8(推断)〕
  *(uint32_t *)(pThis_24 + 12) = 0;  // pThis_24+12〔nSkillRec12(推断)〕
  if ( *(uint32_t *)(this + 24) >= 0x10u )  // this+24〔nPageMax(推断)〕等 2 字段
    j__free(*(void **)(this + 4));  // 调 堆释放
  *(uint32_t *)(this + 20) = 0;  // this+80 = nAuraStage
  *(uint32_t *)(this + 24) = 15;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
}



// ------------------------------------------------------------
// 0x4D1300 sub_4D1300
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int /*thiscall*/ sub_4D1300(void *this)
{
  return sub_4D09A0(this);
}



// ------------------------------------------------------------
// 0x4D1390 sub_4D1390
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int /*thiscall*/ sub_4D1390(int this)
{
  return sub_4D09E0(this);
}



// ------------------------------------------------------------
// 0x4D5A50 sub_4D5A50
// ------------------------------------------------------------
// 空串桩：恒返回 szPassword（空字符串占位，字符串 getter 基类默认实现）

const CHAR */*stdcall*/ sub_4D5A50(int nArg1)
{
  return szPassword;
}



// ------------------------------------------------------------
// 0x4D5F50 sub_4D5F50
// ------------------------------------------------------------
// 桩（3L）

int /*thiscall*/ sub_4D5F50(uint32_t *this)  // 实现：桩（3L）
{
  return *(this + 4);  // this+16〔nChannelTypeSel(推断)〕
}



// ------------------------------------------------------------
// 0x4D5F80 sub_4D5F80
// ------------------------------------------------------------
// 桩（3L）

int /*thiscall*/ sub_4D5F80(uint32_t *this)  // 实现：桩（3L）
{
  return *(this + 21);  // this+84 = pFxObjA
}



// ------------------------------------------------------------
// 0x4E1F00 sub_4E1F00
// ------------------------------------------------------------
// 字段基址 getter：return this + 680（虚表槽残件）

char */*thiscall*/ sub_4E1F00(char *this)  // 实现：字段基址 getter：return this + 680（虚表槽残件）
{
  return this + 680;  // this+680〔nSnapshot680〕
}



// ------------------------------------------------------------
// 0x4E1F30 sub_4E1F30
// ------------------------------------------------------------
// 字段读取桩：return *(this + 221)（虚表槽残件）

int /*thiscall*/ sub_4E1F30(uint32_t *this)  // 实现：字段读取桩：return *(this + 221)（虚表槽残件）
{
  return *(this + 221);
}



// ------------------------------------------------------------
// 0x4E1F60 sub_4E1F60
// ------------------------------------------------------------
// 字段读取桩：return *(this + 224)（虚表槽残件）

int /*thiscall*/ sub_4E1F60(uint32_t *this)  // 实现：字段读取桩：return *(this + 224)（虚表槽残件）
{
  return *(this + 224);
}



// ------------------------------------------------------------
// 0x4E1F90 sub_4E1F90
// ------------------------------------------------------------
// 字段读取桩：return *(this + 227)（虚表槽残件）

int /*thiscall*/ sub_4E1F90(uint32_t *this)  // 实现：字段读取桩：return *(this + 227)（虚表槽残件）
{
  return *(this + 227);
}



// ------------------------------------------------------------
// ============
// 【分区 5】第三轮审计补漏：0x48-0x4E 区收尾（0x481E60-0x4E1FA0）
// ============

// 0x481E60 sub_481E60
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int /*thiscall*/ sub_481E60(void *this)
{
  return sub_481E20(this);  // 调 44 字节条目容器析构（与 ·0x481DF0 配套）
}



// ------------------------------------------------------------
// 0x4859A0 sub_4859A0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 32)（虚表槽残件）

int /*thiscall*/ sub_4859A0(uint32_t *this)  // 实现：字段读取桩：return *(this + 32)（虚表槽残件）
{
  return *(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
}



// ------------------------------------------------------------
// 0x485A30 sub_485A30
// ------------------------------------------------------------
// 字段读取桩：return *(this + 146)（虚表槽残件）

char /*thiscall*/ sub_485A30(uint8_t *this)  // 实现：字段读取桩：return *(this + 146)（虚表槽残件）
{
  return *(this + 146);
}



// ------------------------------------------------------------
// 0x497E30 sub_497E30
// ------------------------------------------------------------
// 薄转发（→ sub_497E30）

int /*thiscall*/ sub_497E30(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 96))(this);  // 调用虚函数（虚表槽 +96）【推断: 取 this+136】
}



// ------------------------------------------------------------
// 0x49A9C0 sub_49A9C0
// ------------------------------------------------------------
// 薄转发（→ sub_49A9C0）

void /*thiscall*/ sub_49A9C0(uint32_t *this)
{
  *(this + 22) = 0;  // this+88 = pFxObjB
}



// ------------------------------------------------------------
// 0x4A0CA0 sub_4A0CA0
// ------------------------------------------------------------
// 薄转发（→ sub_4A0CA0）

void /*thiscall*/ sub_4A0CA0(uint32_t *this)
{
  *this = &CNGoblinCommon::`vftable';  // vftable 复位
}



// ------------------------------------------------------------
// 0x4A0D80 sub_4A0D80
// ------------------------------------------------------------
// 字段读取桩：return *(this + 152)（虚表槽残件）

int /*thiscall*/ sub_4A0D80(uint32_t *this)  // 实现：字段读取桩：return *(this + 152)（虚表槽残件）
{
  return *(this + 152);  // this+608〔nAttackGate〕
}



// ------------------------------------------------------------
// 0x4A0DB0 sub_4A0DB0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 81)（虚表槽残件）

int /*thiscall*/ sub_4A0DB0(uint32_t *this)  // 实现：字段读取桩：return *(this + 81)（虚表槽残件）
{
  return *(this + 81);  // this+324 = 购买上下文 id（0x550480: dword
}



// ------------------------------------------------------------
// 0x4A0E80 sub_4A0E80
// ------------------------------------------------------------
// 字段读取桩：return *(this + 640)（虚表槽残件）

char /*thiscall*/ sub_4A0E80(uint8_t *this)  // 实现：字段读取桩：return *(this + 640)（虚表槽残件）
{
  return *(this + 640);
}



// ------------------------------------------------------------
// 0x4A0EB0 sub_4A0EB0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 161)（虚表槽残件）

int /*thiscall*/ sub_4A0EB0(uint32_t *this)  // 实现：字段读取桩：return *(this + 161)（虚表槽残件）
{
  return *(this + 161);  // this+644 = 帧时刻覆盖值
}



// ------------------------------------------------------------
// 0x4A1080 sub_4A1080
// ------------------------------------------------------------
// 字段读取桩：return *(this + 1662)（虚表槽残件）

int /*thiscall*/ sub_4A1080(uint32_t *this)  // 实现：字段读取桩：return *(this + 1662)（虚表槽残件）
{
  return *(this + 1662);
}



// ------------------------------------------------------------
// 0x4A10B0 sub_4A10B0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 7105)（虚表槽残件）

char /*thiscall*/ sub_4A10B0(uint8_t *this)  // 实现：字段读取桩：return *(this + 7105)（虚表槽残件）
{
  return *(this + 7105);  // 返回 this + 28420 处指针
}



// ------------------------------------------------------------
// 0x4A4420 sub_4A4420
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int /*thiscall*/ sub_4A4420(void *this)
{
  return sub_4A4170(this);
}



// ------------------------------------------------------------
// 0x4A6FC0 sub_4A6FC0
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

int /*thiscall*/ sub_4A6FC0(char *this, char pszArg2)
{
  return sub_4A6FD0(this - 8600, pszArg2);  // 调 CNGoblinBombKagel 删除析构壳
}



// ------------------------------------------------------------
// 0x4AA7E0 sub_4AA7E0
// ------------------------------------------------------------
// 散装补漏小函数（2L）【语义未逐行展开】

int /*thiscall*/ sub_4AA7E0(uint32_t *this)
{
  *this = &CNSpider::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4B1090 nullsub_10
// ------------------------------------------------------------
// 空桩（nullsub，调用即返回）

void /*stdcall*/ nullsub_10(int nArg1, int nArg2, int nArg3)  // 实现：空桩（nullsub，调用即返回）
{
  ;
}



// ------------------------------------------------------------
// 0x4B3D00 sub_4B3D00
// ------------------------------------------------------------
// 薄转发（→ sub_4B3D00）

char sub_4B3D00()
{
  return 0;
}



// ------------------------------------------------------------
// 0x4BA9D0 sub_4BA9D0
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int sub_4BA9D0()
{
  return sub_4BA990();  // 调 248 字节记录 vector 清空析构
}



// ------------------------------------------------------------
// 0x4BACC0 sub_4BACC0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 317)（虚表槽残件）

int /*thiscall*/ sub_4BACC0(uint32_t *this)  // 实现：字段读取桩：return *(this + 317)（虚表槽残件）
{
  return *(this + 317);
}



// ------------------------------------------------------------
// 0x4BAD20 sub_4BAD20
// ------------------------------------------------------------
// 字段读取桩：return *(this + 1320)（虚表槽残件）

char /*thiscall*/ sub_4BAD20(uint8_t *this)  // 实现：字段读取桩：return *(this + 1320)（虚表槽残件）
{
  return *(this + 1320);  // this+1320 = 动画件已装配门
}



// ------------------------------------------------------------
// 0x4C0720 sub_4C0720
// ------------------------------------------------------------
// 散装补漏小函数（1L）【语义未逐行展开】

// attributes: thunk
int sub_4C0720()
{
  return sub_4B32E0();  // 调 角色状态复位（含本地全局清理）
}



// ------------------------------------------------------------
// 0x4D0970 sub_4D0970
// ------------------------------------------------------------
// 散装补漏小函数（3L）【语义未逐行展开】

void /*stdcall*/ sub_4D0970(char *pszArg1, char *pszArg2)
{
  char *i; // esi

  for ( i = pszArg1; i != pszArg2; i += 36 )
    sub_501490(i);  // 调 对象析构后释放堆块
}



// ------------------------------------------------------------
// 0x4D0A20 sub_4D0A20
// ------------------------------------------------------------
// list 迁移/拼接（58L：Block/a4 端点对齐判断 + 节点搬移）

void ***/*thiscall*/ sub_4D0A20(void ***this, void ***uArg2, void **Block, void **pArg4)  // 实现：list 迁移/拼接（58L：Block/a4 端点对齐判断 + 节点搬移）
{
  void **pArg42; // ebx
  void **Block2; // esi
  void **fld_e1; // eax
  uint32_t *fld_e12; // eax
  void **Block22; // ecx
  void ***v11; // eax
  void **j; // eax
  void **i; // eax

  pArg42 = pArg4;
  Block2 = Block;
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( Block == *fld_e1 && pArg4 == fld_e1 )
  {
    sub_4D08F0(fld_e1[1]);
    (*(this + 1))[1] = *(this + 1);  // this+4 = pHostObj
    fld_e12 = *(this + 1);  // this+4 = pHostObj
    *(this + 2) = nullptr;  // this+8 = 技能槽记录首字
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = *(this + 1);  // this+4 = pHostObj
    *uArg2 = (void **)**(this + 1);  // this+4 = pHostObj
    return uArg2;
  }
  else
  {
    if ( Block != pArg4 )
    {
      do
      {
        Block22 = Block2;
        if ( *((uint8_t *)Block2 + 69) == 0 )
        {
          v11 = (void ***)Block2[2];
          if ( *((uint8_t *)v11 + 69) != 0 )
          {
            for ( i = (void **)Block2[1]; *((uint8_t *)i + 69) == 0; i = (void **)i[1] )
            {
              if ( Block2 != i[2] )
                break;
              Block2 = i;
            }
            Block2 = i;
          }
          else
          {
            Block2 = (void **)Block2[2];
            for ( j = *v11; *((uint8_t *)j + 69) == 0; j = (void **)*j )
              Block2 = j;
          }
        }
        sub_4CFEE0(this, &Block, Block22);
      }
      while ( Block2 != pArg42 );
    }
    *uArg2 = Block2;
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4D0B90 sub_4D0B90
// ------------------------------------------------------------
// 容器清理（25L）

int /*thiscall*/ sub_4D0B90(int this)  // 实现：容器清理（25L）
{
  sub_423A20(this);  // 调 小结构初始化（0-100 刻度）
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
  *(uint32_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  *(uint8_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 156) = 100;  // this+156〔nAdd156(推断)〕
  *(uint32_t *)(this + 160) = 100;  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 164) = 100;  // this+164〔fAdd164(推断)〕
  *(uint8_t *)(this + 168) = 1;  // this+672 = 拾取/交互目标有效标志
  *(uint32_t *)(this + 172) = 2;  // this+688 = 表现/名字快照[2]
  *(uint32_t *)(this + 176) = 1;  // this+704 = 表现/名字快照[24]
  sub_428480(this + 180);  // 调 32B 元素容器清空
  return sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x4D0F00 sub_4D0F00
// ------------------------------------------------------------
// 字段族重置（44L）：+24..+112 三元组（容量15/首0/标志0）连清 —— std::string/vector 槽复位

int /*thiscall*/ sub_4D0F00(int this)  // 实现：字段族重置（44L）：+24..+112 三元组（容量15/首0/标志0）连清 —— std::string/vector 槽复位
{
  *(uint32_t *)(this + 28) = 15;  // this+112 = pHostComp
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 15;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint8_t *)(this + 36) = 0;  // this+144 = pFrameList144
  *(uint32_t *)(this + 84) = 15;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  *(uint8_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 112) = 15;  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
  *(uint8_t *)(this + 92) = 0;  // this+92〔pFxObjC(推断)〕等 2 字段
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 168) = 0;  // this+672 = 拾取/交互目标有效标志
  *(uint32_t *)(this + 172) = 0;  // this+688 = 表现/名字快照[2]
  *(uint32_t *)(this + 176) = 0;  // this+704 = 表现/名字快照[24]
  *(uint32_t *)(this + 184) = 0;  // this+184〔bSingleTarget(推断)〕
  *(uint32_t *)(this + 188) = 0;  // this+188〔nStatusIdx(推断)〕
  *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
  *(uint32_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  *(uint32_t *)(this + 216) = 0;  // this+216〔bField216(推断)〕
  *(uint32_t *)(this + 220) = 0;  // this+220〔nSnapDst220(推断)〕
  *(uint32_t *)(this + 228) = 0;  // this+228〔nSnapDst228(推断)〕
  *(uint32_t *)(this + 232) = 0;  // this+232〔bSyncFlag〕
  *(uint32_t *)(this + 236) = 0;  // this+944 = 名字已播出标志
  *(uint32_t *)(this + 240) = -1;  // this+240〔nSyncArgB〕
  *(uint32_t *)(this + 244) = -1;  // this+976 = uCfgE976
  *(uint32_t *)(this + 248) = -1;  // this+992 = uCfgB992
  *(uint32_t *)(this + 252) = -1;  // this+252〔nQuad2〕
  *(uint32_t *)(this + 260) = 0;  // this+260〔nQuad4〕
  *(uint32_t *)(this + 264) = 0;  // this+264〔nAnimHandle(推断)〕
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 284) = 0;  // this+284〔bBindGate284(推断)〕
  *(uint32_t *)(this + 288) = 0;  // this+288〔pMaster288(推断)〕
  *(uint32_t *)(this + 292) = 0;  // this+292〔nOpenMode292(推断)〕
  *(uint32_t *)(this + 304) = 0;  // this+304〔pLayer304(推断)〕
  *(uint32_t *)(this + 308) = 0;  // this+1232〔pNameTagCtrl(推断)〕
  *(uint32_t *)(this + 312) = 0;
  sub_4D0D00((void *)this);
  return this;
}



// ------------------------------------------------------------
// 0x4D1100 sub_4D1100
// ------------------------------------------------------------
// 容器清理（8L）

int /*thiscall*/ sub_4D1100(int this)  // 实现：容器清理（8L）
{
  if ( *(uint32_t *)(this + 220) >= 0x10u )  // this+220〔nSnapDst220(推断)〕
    j__free(*(void **)(this + 200));  // 调 堆释放
  *(uint32_t *)(this + 220) = 15;  // this+220〔nSnapDst220(推断)〕
  *(uint32_t *)(this + 216) = 0;  // this+216〔bField216(推断)〕
  *(uint8_t *)(this + 200) = 0;  // this+200〔nMainState(推断)〕
  return sub_428480(this + 180);  // 调 32B 元素容器清空
}



// ------------------------------------------------------------
// 0x4D1310 sub_4D1310
// ------------------------------------------------------------
// list 复位（27L：+1/+2 首/尾指针回卷自指）

uint32_t */*thiscall*/ sub_4D1310(uint32_t *this)  // 实现：list 复位（27L：+1/+2 首/尾指针回卷自指）
{
  uint32_t **fld_e1; // eax
  uint32_t *v3; // esi
  uint32_t *result; // eax
  bool fld_e12; // zf
  uint32_t *v6; // ebx

  fld_e1 = (uint32_t **)*(this + 1);  // this+4 = pHostObj
  v3 = *fld_e1;
  *fld_e1 = fld_e1;
  result = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  result[1] = result;
  fld_e12 = v3 == (uint32_t *)*(this + 1);  // this+4 = pHostObj
  *(this + 2) = 0;  // this+8 = 技能槽记录首字
  if ( !fld_e12 )
  {
    do
    {
      v6 = (uint32_t *)*v3;
      sub_4CFE40(v3);
      j__free(v3);  // 调 堆释放
      result = (uint32_t *)*(this + 1);  // this+4 = pHostObj
      v3 = v6;
    }
    while ( v6 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D13A0 sub_4D13A0
// ------------------------------------------------------------
// ★ 大清理（107L）：sub_6569D0(+4) + +16 清零 + 多段 vector/list 逐段释放（对象总析构底座）

void /*thiscall*/ sub_4D13A0(int this)  // 实现：★ 大清理（107L）：sub_6569D0(+4) + +16 清零 + 多段 vector/list 逐段释放（对象总析构底座）
{
  char *fld_AC; // ebx
  void **fld_10C; // ebx
  uint32_t *pThis_160; // eax
  int k; // ecx
  void **pThis_1AC; // ebx
  void *Block; // [esp+8h] [ebp-8h]
  char *i; // [esp+Ch] [ebp-4h]
  void **j; // [esp+Ch] [ebp-4h]
  int m; // [esp+Ch] [ebp-4h]

  sub_6569D0(this + 4);  // 调 清 +28
  *(uint32_t *)(this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 24) != 0 )  // this+24〔nPageMax(推断)〕等 2 字段
    j__free(*(void **)(this + 24));  // 调 堆释放
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 28) = 0;  // this+112 = pHostComp
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  sub_4CFEA0(this + 36);  // this+144 = pFrameList144
  sub_6569D0(this + 48);  // 调 清 +28
  sub_4D09A0(this + 60);  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 76) = 0;  // this+76〔pBtnActionE〕
  sub_4D1310((uint32_t *)(this + 80));  // this+80〔nAuraStage(推断)〕
  sub_4D1350(this + 92);  // this+368〔nBindPos368(推断)〕
  *(uint32_t *)(this + 120) = 4;  // this+120〔pAnimObj〕
  sub_4017E0(this + 124);  // 调 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  sub_4017E0(this + 140);  // 调 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  *(uint32_t *)(this + 156) = 100;  // this+156〔nAdd156(推断)〕
  *(uint32_t *)(this + 160) = 100;  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 164) = 100;  // this+164〔fAdd164(推断)〕
  fld_AC = *(char **)(this + 172);  // this+688 = 表现/名字快照[2]
  if ( fld_AC != nullptr )  // 若 fld_AC 有效（非空）
  {
    for ( i = *(char **)(this + 176); fld_AC != i; fld_AC += 36 )  // this+704 = 表现/名字快照[24]
      sub_501490(fld_AC);  // 调 对象析构后释放堆块
    j__free(*(void **)(this + 172));  // this+688 = 表现/名字快照[2]
  }
  *(uint32_t *)(this + 172) = 0;  // this+688 = 表现/名字快照[2]
  *(uint32_t *)(this + 176) = 0;  // this+704 = 表现/名字快照[24]
  *(uint32_t *)(this + 180) = 0;  // this+180〔nRadius(推断)〕
  if ( *(uint32_t *)(this + 188) != 0 )  // this+188〔nStatusIdx(推断)〕
    j__free(*(void **)(this + 188));  // 调 堆释放
  *(uint32_t *)(this + 188) = 0;  // this+188〔nStatusIdx(推断)〕
  *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
  *(uint32_t *)(this + 196) = 0;
  if ( *(uint32_t *)(this + 204) != 0 )  // this+204〔pSubAnim204(推断)〕
    j__free(*(void **)(this + 204));  // 调 堆释放
  *(uint32_t *)(this + 204) = 0;  // this+204〔pSubAnim204(推断)〕
  *(uint32_t *)(this + 208) = 0;  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  *(uint32_t *)(this + 216) = 0;  // this+216〔bField216(推断)〕
  *(uint32_t *)(this + 220) = 0;  // this+220〔nSnapDst220(推断)〕
  *(uint32_t *)(this + 224) = 0;  // this+224〔nSnapDst224(推断)〕
  *(uint32_t *)(this + 228) = 0;  // this+228〔nSnapDst228(推断)〕
  *(uint32_t *)(this + 232) = 0;  // this+232〔bSyncFlag〕
  *(uint32_t *)(this + 236) = 0;  // this+944 = 名字已播出标志
  *(uint32_t *)(this + 240) = 0;  // this+240〔nSyncArgB〕
  *(uint32_t *)(this + 244) = 0;  // this+976 = uCfgE976
  *(uint32_t *)(this + 248) = 0;  // this+992 = uCfgB992
  *(uint32_t *)(this + 252) = 0;  // this+252〔nQuad2〕
  *(uint32_t *)(this + 256) = 0;  // this+256〔bQuad3〕
  *(uint32_t *)(this + 260) = 0;  // this+260〔nQuad4〕
  fld_10C = *(void ***)(this + 268);
  if ( fld_10C != nullptr )  // 若 fld_10C 有效（非空）
  {
    for ( j = *(void ***)(this + 272); fld_10C != j; ++fld_10C )
      sub_41B010(fld_10C);  // 调 驻留句柄析构（引用计数减到 0 释放）
    j__free(*(void **)(this + 268));  // 调 堆释放
  }
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;  // this+276〔pMapEntry〕
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0(&unk_6F8634, 0xAu);  // 【std::string构造赋值】
  *(uint32_t *)(this + 336) = 2;
  *(uint32_t *)(this + 340) = 8;  // this+340〔pSlotTbl340〕
  pThis_160 = (uint32_t *)(this + 352);  // this+352〔uHitCtx352〕
  for ( k = 3; k != 0; --k )  // 循环：k 从 3 递减到 0
  {
    *(pThis_160 - 2) = 0;
    *(pThis_160 - 1) = 0;
    *pThis_160 = 0;
    pThis_160[1] = 0;
    pThis_160 += 4;
  }
  *(uint32_t *)(this + 392) = 0;
  pThis_1AC = (void **)(this + 428);
  for ( m = 3; m != 0; --m )  // 循环：m 从 3 递减到 0
  {
    Block = *pThis_1AC;
    if ( *pThis_1AC != nullptr )
    {
      sub_501490(*pThis_1AC);  // 调 对象析构后释放堆块
      j__free(Block);  // 调 堆释放
    }
    *pThis_1AC++ = nullptr;
  }
  if ( *(uint32_t *)(this + 444) != 0 )
    j__free(*(void **)(this + 444));  // 调 堆释放
  *(uint32_t *)(this + 444) = 0;
  *(uint32_t *)(this + 448) = 0;  // this+448〔uAtkStage448(推断)〕
  *(uint32_t *)(this + 452) = 0;  // this+452〔nAtkRollVal(推断)〕
  if ( *(uint32_t *)(this + 460) != 0 )  // this+460〔bSpiritFlag(推断)〕
    j__free(*(void **)(this + 460));  // 调 堆释放
  *(uint32_t *)(this + 460) = 0;  // this+460〔bSpiritFlag(推断)〕
  *(uint32_t *)(this + 464) = 0;
  *(uint32_t *)(this + 468) = 0;
}



// ------------------------------------------------------------
// 0x4D5F30 sub_4D5F30
// ------------------------------------------------------------
// 字段桩（4L：a2 参数转发）

int /*thiscall*/ sub_4D5F30(uint32_t *this, int nArg2)  // 实现：字段桩（4L：a2 参数转发）
{
  *(this + 3) = nArg2;  // this+12 = 技能槽记录次字
  return nArg2;
}



// ------------------------------------------------------------
// 0x4D5F60 sub_4D5F60
// ------------------------------------------------------------
// BOOL 桩（3L）

BOOL /*thiscall*/ sub_4D5F60(uint32_t *this)  // 实现：BOOL 桩（3L）
{
  return *(this + 3) != 0;  // this+12 = 技能槽记录次字
}



// ------------------------------------------------------------
// 0x4D5F90 sub_4D5F90
// ------------------------------------------------------------
// 桩（3L）

char /*thiscall*/ sub_4D5F90(uint8_t *this)  // 实现：桩（3L）
{
  return *(this + 96);  // this+384〔nAnimNameCap(推断)〕
}



// ------------------------------------------------------------
// 0x4E1F10 sub_4E1F10
// ------------------------------------------------------------
// 字段读取桩：return *(this + 173)（虚表槽残件）

int /*thiscall*/ sub_4E1F10(uint32_t *this)  // 实现：字段读取桩：return *(this + 173)（虚表槽残件）
{
  return *(this + 173);  // this+692 = 表现/名字快照[3]
}



// ------------------------------------------------------------
// 0x4E1F40 sub_4E1F40
// ------------------------------------------------------------
// 字段读取桩：return *(this + 222)（虚表槽残件）

int /*thiscall*/ sub_4E1F40(uint32_t *this)  // 实现：字段读取桩：return *(this + 222)（虚表槽残件）
{
  return *(this + 222);
}



// ------------------------------------------------------------
// 0x4E1F70 sub_4E1F70
// ------------------------------------------------------------
// 字段读取桩：return *(this + 225)（虚表槽残件）

int /*thiscall*/ sub_4E1F70(uint32_t *this)  // 实现：字段读取桩：return *(this + 225)（虚表槽残件）
{
  return *(this + 225);
}



// ------------------------------------------------------------
// 0x4E1FA0 sub_4E1FA0
// ------------------------------------------------------------
// 字段读取桩：return *(this + 228)（虚表槽残件）

int /*thiscall*/ sub_4E1FA0(uint32_t *this)  // 实现：字段读取桩：return *(this + 228)（虚表槽残件）
{
  return *(this + 228);
}


