// ============================================================
// 【40JP逆向源代码工程】src/game/gunner_state.cpp
// 模块: 0x4C0000-0x4D0000
// 来源: work/dump 素材  区块: 0x4C0070-0x4CFEE1 §A 武器状态 TAG 组
// 层级: L2 转写 + 证据标注层（函数体保持 Hex-Rays 忠实输出，零改动；
//       本文件由主代理自研流水线补注：每函数的字符串证据/调用链清单，
//       纯二进制事实提取（tools/annotate_evidence.py），零臆造）
// 函数数: 123
// ============================================================


#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============================================================
// §A 武器状态 TAG 组
// ============================================================
// 0x4C0070 sub_4C0070
// ------------------------------------------------------------
// 调: sub_4C0070 sub_698F90 sub_4BFFA0
char */*thiscall*/ sub_4C0070(void *this)  // 实现：调: sub_4C0070 sub_698F90 sub_4BFFA0
{
  sub_698F90((int)this + 4, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  return sub_4BFFA0((int)this + 44, 0x10u);  // sub_4BFFA0 —— 16 字节条目表扩容分配（内联 vector 分配路径）
}



// ------------------------------------------------------------
// 0x4C0090 sub_4C0090
// ------------------------------------------------------------
// 调: sub_4C0090 sub_40C0F0 sub_4BFCB0
uint32_t */*thiscall*/ sub_4C0090(uint32_t *this, int pArg2)  // 实现：调: sub_4C0090 sub_40C0F0 sub_4BFCB0
{
  uint32_t **fld_e21; // ecx
  uint32_t *v4; // esi
  uint32_t *result; // eax
  int pArg22; // edi
  uint32_t *v7; // edi
  uint32_t *v8; // ecx
  int i; // edx
  int v10; // esi

  fld_e21 = (uint32_t **)*(this + 21);  // this+84〔pFxObjA(推断)〕
  v4 = *fld_e21;  // fld_e21=this+84 pFxObjA
  result = *fld_e21;  // fld_e21=this+84 pFxObjA
  if ( *fld_e21 == fld_e21 )  // fld_e21=this+84 pFxObjA
  {
    pArg22 = pArg2;
  }
  else
  {
    do
    {
      pArg22 = pArg2;
      if ( result[2] == pArg2 )
        break;
      result = (uint32_t *)*result;
    }
    while ( result != fld_e21 );  // 循环直到 result != fld_e21
  }
  if ( result == fld_e21 )  // fld_e21=this+84 pFxObjA
  {
    if ( v4 != fld_e21 )  // fld_e21=this+84 pFxObjA
    {
      do
      {
        if ( (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 120))(this, pArg22, v4[2]) == 1 )  // 虚调用 vt+120（this）转发(对象+缓冲)
          break;
        v4 = (uint32_t *)*v4;
      }
      while ( v4 != (uint32_t *)*(this + 21) );  // this+84〔pFxObjA(推断)〕
    }
    v7 = sub_40C0F0((int)v4, v4[1], &pArg2);  // sub_40C0F0 —— list 结点分配（12B：前驱/后继/数据）
    sub_4BFCB0(this + 20, 1u);  // sub_4BFCB0 —— 列表计数记账（+8）
    v4[1] = v7;
    *(uint32_t *)v7[1] = v7;
    result = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v8 = *(uint32_t **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    for ( i = 0; result != v8; i += v10 )
    {
      v10 = result[5] + 2 * result[4];
      result += 6;
    }
    if ( i > *(this + 15) )  // this+60〔nFadeValue60(推断)〕
      *(this + 15) = i;  // 写字段 this+15 ← i
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C0140 sub_4C0140
// ------------------------------------------------------------
// 调: sub_4C0140 sub_699000
char /*thiscall*/ sub_4C0140(uint32_t *this)  // 实现：调: sub_4C0140 sub_699000
{
  uint32_t *pThis; // edi
  int pThis_1; // eax
  uint32_t *v3; // ecx
  uint32_t *v4; // edx
  int pThis_12; // esi
  uint32_t *v6; // eax
  uint32_t *v7; // edx
  uint32_t *v8; // edi
  int v9; // esi
  int j; // eax
  int *k; // eax
  int *v12; // ebx
  int v13; // esi
  char v14; // al
  uint32_t *v15; // edx
  uint32_t *v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // esi
  int v23; // ecx
  int *v24; // ecx
  uint32_t Block[3]; // [esp+Ch] [ebp-18h] BYREF
  char v27; // [esp+18h] [ebp-Ch]
  char v28; // [esp+19h] [ebp-Bh]
  uint32_t *pThis2; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  pThis_1 = sub_699000((int)(this + 1));  // 【clock_now(clk)】
  v3 = (uint32_t *)pThis[12];
  v4 = (uint32_t *)pThis[13];
  pThis_12 = pThis_1;
  v6 = v3;
  for ( i = pThis_12; v6 != v4; v6 += 4 )
  {
    if ( *((uint8_t *)v6 + 12) != 0 )
      break;
    if ( v6[1] + pThis[15] >= pThis_12 )
      break;
  }
  if ( v6 != v3 )
  {
    v7 = (uint32_t *)pThis[13];
    if ( v6 != v7 )
    {
      do
      {
        v8 = v3;
        *v3 = *v6;
        v3[1] = v6[1];  // v3[1] = 取 v6[1]
        v3[2] = v6[2];  // v3[2] = 取 v6[2]
        v9 = v6[3];
        v6 += 4;
        v3 += 4;
        v8[3] = v9;
      }
      while ( v6 != v7 );  // 循环直到 v6 != v7
      pThis = pThis2;
      pThis_12 = i;
    }
    pThis[13] = v3;
  }
  for ( j = pThis[12]; j != pThis[13]; j += 16 )
  {
    if ( *(uint8_t *)(j + 13) != 0 )
      *(uint8_t *)(j + 13) = 0;  // 写字段 j+13 ← 0
    if ( *(uint8_t *)(j + 12) != 0 )
      *(uint32_t *)(j + 8) = pThis_12 - *(uint32_t *)(j + 4);  // 写字段 j+8（nSkillRec8） ← pThis_12 - *(uint32_t *)(j + 4)
  }
  k = (int *)pThis[9];
  v12 = (int *)*k;
  if ( (int *)*k != k )
  {
    do
    {
      v13 = v12[3];
      v14 = (*(int (/*thiscall*/ **)(uint32_t *, int *))(*pThis + 48))(pThis, v12 + 4);  // 虚调用 vt+48（pThis）归属坐标x
      if ( v14 == 0 && *((uint8_t *)pThis + 66) != 0 )
      {
        v15 = (uint32_t *)pThis[18];
        v16 = (uint32_t *)*v15;
        if ( (uint32_t *)*v15 != v15 )
        {
          do
          {
            if ( v16[2] == v13 )
              break;
            v16 = (uint32_t *)*v16;
          }
          while ( v16 != v15 );  // 循环直到 v16 != v15
          if ( v16 != v15 )
            v14 = 1;
        }
      }
      v17 = pThis[12];
      if ( v17 != 0 )
        v18 = (pThis[13] - v17) >> 4;
      else
        v18 = 0;
      v19 = v18 - 1;  // 计算 v19 = v18 - 1
      if ( v19 >= 0 )
      {
        v20 = pThis[12] + 16 * v19;
        do
        {
          if ( *(uint32_t *)v20 == v13 && *(uint8_t *)(v20 + 12) != 0 )
            break;
          --v19;  // 计数自减 v19
          v20 -= 16;
        }
        while ( v19 >= 0 );  // 循环直到 v19 >= 0
      }
      if ( v14 != 0 )
      {
        if ( v19 == -1 )
        {
          Block[1] = i;
          v21 = pThis[12];
          Block[2] = 0;
          Block[0] = v13;
          v27 = 1;
          v28 = 1;
          if ( v21 != 0 && (pThis[13] - v21) >> 4 < (unsigned int)((pThis[14] - v21) >> 4) )
          {
            v22 = pThis[13];
            sub_4BF340(v22, 1, Block);  // sub_4BF340 —— 16 字节元素填充
            pThis[13] = v22 + 16;
          }
          else
          {
            sub_4BFD40(pThis[13], 1, Block);  // sub_4BFD40 —— 向量填装插入（_Insert_n）
          }
        }
      }
      else if ( v19 != -1 )
      {
        v23 = 16 * v19;  // 计算 v23 = 16 * v19
        *(uint8_t *)(v23 + pThis[12] + 12) = 0;
        *(uint8_t *)(v23 + pThis[12] + 13) = 1;
      }
      LOBYTE(k) = *((uint8_t *)v12 + 25);
      if ( (uint8_t)k == 0 )
      {
        v24 = (int *)v12[2];
        if ( *((uint8_t *)v24 + 25) != 0 )
        {
          for ( k = (int *)v12[1]; *((uint8_t *)k + 25) == 0; k = (int *)k[1] )
          {
            if ( v12 != (int *)k[2] )
              break;
            v12 = k;
          }
          v12 = k;
        }
        else
        {
          k = (int *)*v24;
          if ( *(uint8_t *)(*v24 + 25) == 0 )
          {
            do
            {
              v24 = k;
              k = (int *)*k;
            }
            while ( *((uint8_t *)k + 25) == 0 );
          }
          v12 = v24;
        }
      }
    }
    while ( v12 != (int *)pThis[9] );
  }
  return (char)k;
}


// ------------------------------------------------------------
// 0x4C0360 sub_4C0360
// ------------------------------------------------------------
// 调: sub_4C0360 sub_41A5E0
double /*thiscall*/ sub_4C0360(void *this)  // 实现：调: sub_4C0360 sub_41A5E0
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this + 524));  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4C0390 sub_4C0390
// ------------------------------------------------------------
// 调: sub_4C0390 sub_699000
int /*thiscall*/ sub_4C0390(uint32_t *this)  // 实现：调: sub_4C0390 sub_699000
{
  return *(this + 2185) + *(this + 1664) * sub_699000((int)(this + 1640)) / 1000;  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x4C03D0 sub_4C03D0
// ------------------------------------------------------------
// 调: sub_4C03D0 sub_699000
int /*thiscall*/ sub_4C03D0(uint32_t *this)  // 实现：调: sub_4C03D0 sub_699000
{
  return *(this + 1664) * sub_699000((int)(this + 1640)) / 1000;  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x4C0400 sub_4C0400
// ------------------------------------------------------------
// 证: "LANDRUNNER_OUT"
// 调: sub_4C0400
char /*cdecl*/ sub_4C0400(int nArg1)  // 实现：调: sub_4C0400
{
  uint32_t *v1; // eax

  v1 = &unk_6F6CC8;  // 取全局对象/数组首址（v1 ← unk_6F6CC8）
  while ( nArg1 != *v1 )  // 当 nArg1 != *v1 循环
  {
    if ( (int)++v1 >= (int)"LANDRUNNER_OUT" )  // 音效/动画 TAG LANDRUNNER_OUT
      return 0;
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4C0430 sub_4C0430
// ------------------------------------------------------------
// 调: sub_4C0430 sub_41A590
int /*fastcall*/ sub_4C0430(int pArg1, int nArg2)  // 实现：调: sub_4C0430 sub_41A590
{
  int v3; // edx

  *(uint32_t *)(pArg1 + 8216) = 0;  // 写字段 pArg1+8216（nAtkActionType） ← 0
  *(uint32_t *)(pArg1 + 8516) = -1;  // 写字段 pArg1+8516（f_2144） ← -1
  *(uint32_t *)(pArg1 + 8532) = 0;  // 写字段 pArg1+8532（nPhaseValB） ← 0
  *(uint32_t *)(pArg1 + 8536) = -1;  // 写字段 pArg1+8536 ← -1
  *(uint32_t *)(pArg1 + 8540) = -1;  // 写字段 pArg1+8540（nPhaseStamp） ← -1
  sub_41A590(pArg1 + 8544, nArg2, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(uint32_t *)(pArg1 + 8560) = -1;  // 写字段 pArg1+8560 ← -1
  *(uint32_t *)(pArg1 + 8564) = 0;  // 写字段 pArg1+8564 ← 0
  *(uint32_t *)(pArg1 + 8568) = 0;  // 写字段 pArg1+8568（nPhaseGroupIdx） ← 0
  *(uint32_t *)(pArg1 + 8572) = 0;  // 写字段 pArg1+8572（nPhaseElapsed） ← 0
  *(uint8_t *)(pArg1 + 8576) = 0;  // 写字段 pArg1+8576（nFadeAlpha） ← 0
  sub_41A590(pArg1 + 8577, v3, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(uint32_t *)(pArg1 + 8592) = 0;  // 写字段 pArg1+8592 ← 0
  *(uint8_t *)(pArg1 + 8596) = 0;  // 写字段 pArg1+8596（bTargetState） ← 0
  *(uint8_t *)(pArg1 + 8597) = 0;  // 写字段 pArg1+8597（bCapGate） ← 0
  *(uint32_t *)(pArg1 + 8600) = 0;  // 写字段 pArg1+8600（uAI8600） ← 0
  *(uint32_t *)(pArg1 + 8604) = 0;  // 写字段 pArg1+8604（bAI8604） ← 0
  *(uint32_t *)(pArg1 + 8648) = -1;  // 写字段 pArg1+8648（uPhase8648） ← -1
  *(uint32_t *)(pArg1 + 8664) = -1;  // 写字段 pArg1+8664（uAI8664） ← -1
  *(uint8_t *)(pArg1 + 8608) = 0;  // 写字段 pArg1+8608（uAI8608） ← 0
  *(uint32_t *)(pArg1 + 8612) = 0;  // 写字段 pArg1+8612（uAI8612） ← 0
  *(uint32_t *)(pArg1 + 8616) = 0;  // 写字段 pArg1+8616（uAI8616） ← 0
  *(uint32_t *)(pArg1 + 8620) = 0;  // 写字段 pArg1+8620（uAI8620） ← 0
  *(uint32_t *)(pArg1 + 8624) = 0;  // 写字段 pArg1+8624（uAI8624） ← 0
  *(uint32_t *)(pArg1 + 8628) = 0;  // 写字段 pArg1+8628（nPoolTime） ← 0
  *(uint32_t *)(pArg1 + 8632) = 0;  // 写字段 pArg1+8632（bDevourFlag） ← 0
  *(uint32_t *)(pArg1 + 8636) = 0;  // 写字段 pArg1+8636（pDollTarget） ← 0
  *(uint32_t *)(pArg1 + 8640) = 0;  // 写字段 pArg1+8640（uCastSlot8640） ← 0
  *(uint32_t *)(pArg1 + 8644) = 0;  // 写字段 pArg1+8644（uPhase8644） ← 0
  *(uint32_t *)(pArg1 + 8652) = 0;  // 写字段 pArg1+8652（uPhase8652） ← 0
  *(uint32_t *)(pArg1 + 8656) = 0;  // 写字段 pArg1+8656（uPair8656） ← 0
  *(uint32_t *)(pArg1 + 8660) = 0;  // 写字段 pArg1+8660（uEvt8660） ← 0
  *(uint32_t *)(pArg1 + 8668) = 0;  // 写字段 pArg1+8668（nCool8668） ← 0
  *(uint32_t *)(pArg1 + 8672) = 0;  // 写字段 pArg1+8672（uAI8672） ← 0
  *(uint8_t *)(pArg1 + 8676) = 0;  // 写字段 pArg1+8676（uAI8676） ← 0
  *(uint32_t *)(pArg1 + 8680) = 0;  // 写字段 pArg1+8680（uGate8680） ← 0
  *(uint32_t *)(pArg1 + 8684) = 0;  // 写字段 pArg1+8684（bGate8684） ← 0
  *(uint32_t *)(pArg1 + 8688) = -1;  // 写字段 pArg1+8688（bVec8688） ← -1
  *(uint8_t *)(pArg1 + 8692) = 0;  // 写字段 pArg1+8692（uVec8692） ← 0
  *(uint8_t *)(pArg1 + 8693) = 0;  // 写字段 pArg1+8693 ← 0
  *(uint8_t *)(pArg1 + 8694) = 0;  // 写字段 pArg1+8694 ← 0
  *(uint32_t *)(pArg1 + 8696) = 0;  // 写字段 pArg1+8696（uVec8696） ← 0
  *(uint32_t *)(pArg1 + 8700) = 0;  // 写字段 pArg1+8700（uPhase8700） ← 0
  *(uint32_t *)(pArg1 + 8704) = 0;  // 写字段 pArg1+8704（pSegNameTbl8704） ← 0
  *(uint32_t *)(pArg1 + 8708) = 0;  // 写字段 pArg1+8708（pCandTbl8708） ← 0
  *(uint32_t *)(pArg1 + 8712) = 0;  // 写字段 pArg1+8712（nCandTblEnd8712） ← 0
  *(uint32_t *)(pArg1 + 8716) = 0;  // 写字段 pArg1+8716（uArr8716） ← 0
  *(uint32_t *)(pArg1 + 8720) = 0;  // 写字段 pArg1+8720（pSegThrTbl8720） ← 0
  *(uint32_t *)(pArg1 + 8724) = 0;  // 写字段 pArg1+8724（nSegThrEnd8724） ← 0
  *(uint32_t *)(pArg1 + 8732) = -1;  // 写字段 pArg1+8732（bSegLatch8732） ← -1
  *(uint8_t *)(pArg1 + 8728) = 0;  // 写字段 pArg1+8728（nSegThrCap8728） ← 0
  *(uint32_t *)(pArg1 + 8736) = 0;  // 写字段 pArg1+8736 ← 0
  *(uint32_t *)(pArg1 + 8740) = 0;  // 写字段 pArg1+8740 ← 0
  *(uint32_t *)(pArg1 + 8744) = 0;  // 写字段 pArg1+8744（nCountdown8744） ← 0
  *(uint32_t *)(pArg1 + 8748) = 0;  // 写字段 pArg1+8748（bTail8748） ← 0
  *(uint32_t *)(pArg1 + 8752) = 0;  // 写字段 pArg1+8752 ← 0
  *(uint32_t *)(pArg1 + 8756) = 0;  // 写字段 pArg1+8756 ← 0
  memset((void *)(pArg1 + 8760), 0, 0xC8u);  // 调 内存按字节填充
  *(uint32_t *)(pArg1 + 8964) = 100;  // 写字段 pArg1+8964（nDmgCap） ← 100
  *(uint8_t *)(pArg1 + 8960) = 0;  // 写字段 pArg1+8960（bDmgCapOn） ← 0
  *(uint32_t *)(pArg1 + 8968) = 0;  // 写字段 pArg1+8968（nDmgCapCtx） ← 0
  memset((void *)(pArg1 + 8972), 0, 0x140u);  // pArg1+8972〔uEvtState8972(推断)〕
  *(uint32_t *)(pArg1 + 9292) = 0;  // 写字段 pArg1+9292 ← 0
  *(uint32_t *)(pArg1 + 9296) = 0;  // 写字段 pArg1+9296 ← 0
  *(uint8_t *)(pArg1 + 9300) = 0;  // 写字段 pArg1+9300 ← 0
  *(uint8_t *)(pArg1 + 9301) = 0;  // 写字段 pArg1+9301 ← 0
  *(uint32_t *)(pArg1 + 9304) = 0;  // 写字段 pArg1+9304 ← 0
  *(uint32_t *)(pArg1 + 9308) = 0;  // 写字段 pArg1+9308 ← 0
  *(uint32_t *)(pArg1 + 9312) = 0;  // 写字段 pArg1+9312 ← 0
  *(uint32_t *)(pArg1 + 9316) = 0;  // 写字段 pArg1+9316 ← 0
  *(uint32_t *)(pArg1 + 9320) = 0;  // 写字段 pArg1+9320 ← 0
  *(uint32_t *)(pArg1 + 9324) = 0;  // 写字段 pArg1+9324 ← 0
  *(uint32_t *)(pArg1 + 9328) = 0;  // 写字段 pArg1+9328 ← 0
  *(uint32_t *)(pArg1 + 9332) = 0;  // 写字段 pArg1+9332 ← 0
  *(uint32_t *)(pArg1 + 9336) = 0;  // 写字段 pArg1+9336 ← 0
  *(uint32_t *)(pArg1 + 9340) = 0;  // 写字段 pArg1+9340 ← 0
  *(uint32_t *)(pArg1 + 9344) = 0;  // 写字段 pArg1+9344 ← 0
  *(uint32_t *)(pArg1 + 9348) = 0;  // 写字段 pArg1+9348 ← 0
  *(uint32_t *)(pArg1 + 9352) = 0;  // 写字段 pArg1+9352 ← 0
  *(uint32_t *)(pArg1 + 9356) = 0;  // 写字段 pArg1+9356 ← 0
  *(uint32_t *)(pArg1 + 9360) = 0;  // 写字段 pArg1+9360 ← 0
  *(uint32_t *)(pArg1 + 9364) = 0;  // 写字段 pArg1+9364 ← 0
  *(uint8_t *)(pArg1 + 9368) = 0;  // 写字段 pArg1+9368 ← 0
  *(uint32_t *)(pArg1 + 9372) = 0;  // 写字段 pArg1+9372 ← 0
  *(uint32_t *)(pArg1 + 9376) = 0;  // 写字段 pArg1+9376 ← 0
  *(uint32_t *)(pArg1 + 9396) = 0;  // 写字段 pArg1+9396 ← 0
  *(uint32_t *)(pArg1 + 9380) = 0;  // 写字段 pArg1+9380 ← 0
  *(uint32_t *)(pArg1 + 9388) = 0;  // 写字段 pArg1+9388 ← 0
  *(uint32_t *)(pArg1 + 9400) = 0;  // 写字段 pArg1+9400 ← 0
  *(uint32_t *)(pArg1 + 9408) = 0;  // 写字段 pArg1+9408 ← 0
  *(uint32_t *)(pArg1 + 9384) = 0;  // 写字段 pArg1+9384 ← 0
  *(uint32_t *)(pArg1 + 9392) = 0;  // 写字段 pArg1+9392 ← 0
  *(uint32_t *)(pArg1 + 9404) = 0;  // 写字段 pArg1+9404 ← 0
  *(uint32_t *)(pArg1 + 9412) = 0;  // 写字段 pArg1+9412 ← 0
  *(uint8_t *)(pArg1 + 9416) = 0;  // 写字段 pArg1+9416 ← 0
  *(uint32_t *)(pArg1 + 9420) = 0;  // 写字段 pArg1+9420 ← 0
  *(uint32_t *)(pArg1 + 9424) = 0;  // 写字段 pArg1+9424 ← 0
  *(uint8_t *)(pArg1 + 9428) = 0;  // 写字段 pArg1+9428 ← 0
  *(uint32_t *)(pArg1 + 9432) = 0;  // 写字段 pArg1+9432 ← 0
  *(uint32_t *)(pArg1 + 9440) = 0;  // 写字段 pArg1+9440 ← 0
  *(uint32_t *)(pArg1 + 9444) = 0;  // 写字段 pArg1+9444 ← 0
  *(uint32_t *)(pArg1 + 9452) = 0;  // 写字段 pArg1+9452 ← 0
  *(uint32_t *)(pArg1 + 9456) = 0;  // 写字段 pArg1+9456 ← 0
  *(uint32_t *)(pArg1 + 9460) = 0;  // 写字段 pArg1+9460 ← 0
  *(uint32_t *)(pArg1 + 9464) = 0;  // 写字段 pArg1+9464 ← 0
  *(uint32_t *)(pArg1 + 9476) = 0;  // 写字段 pArg1+9476 ← 0
  *(uint32_t *)(pArg1 + 9472) = 0;  // 写字段 pArg1+9472 ← 0
  *(uint8_t *)(pArg1 + 9500) = 0;  // 写字段 pArg1+9500 ← 0
  *(uint32_t *)(pArg1 + 9516) = 0;  // 写字段 pArg1+9516 ← 0
  *(uint32_t *)(pArg1 + 9436) = 4;  // 写字段 pArg1+9436 ← 4
  *(uint32_t *)(pArg1 + 9448) = -1;  // 写字段 pArg1+9448 ← -1
  *(uint32_t *)(pArg1 + 9468) = 1;  // 写字段 pArg1+9468 ← 1
  *(uint32_t *)(pArg1 + 9480) = 0xFFFF;  // 写字段 pArg1+9480 ← 0xFFFF
  *(uint32_t *)(pArg1 + 9484) = -1;  // 写字段 pArg1+9484 ← -1
  return -1;
}


// ------------------------------------------------------------
// 0x4C0730 sub_4C0730
// ------------------------------------------------------------
// 调: sub_4C0730 sub_4AFC30
int /*thiscall*/ sub_4C0730(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：调: sub_4C0730 sub_4AFC30
{
  *((uint8_t *)this + 8960) = 0;  // 写字段 this+8960（bDmgCapOn）
  *(this + 2241) = 100;  // 写字段 this+2241 ← 100
  *((uint8_t *)this + 8597) = 0;  // 写字段 this+8597（bCapGate）
  return sub_4AFC30(this, nArg2, nArg3, nArg4);  // 调 受击流程
}



// ------------------------------------------------------------
// 0x4C0760 sub_4C0760
// ------------------------------------------------------------
// 调: sub_4C0760 sub_4AFBF0
int /*thiscall*/ sub_4C0760(int this, int *pDwArg2, int nArg3)  // 实现：调: sub_4C0760 sub_4AFBF0
{
  int result; // eax
  int fld_23042; // eax
  int fld_2304; // esi  | +0x2304 → ★ 伤害上限值（0x4C0760: *pDwArg2 >= +8964 则钳制）（CNGunner；va=004C0760）

  result = sub_4AFBF0((uint8_t *)this, pDwArg2, nArg3);  // 调 受击过滤
  if ( result != 3 )
  {
    if ( *(uint8_t *)(this + 8960) != 0 )  // this+8960〔bDmgCapOn〕
    {
      fld_23042 = *pDwArg2;
      fld_2304 = *(uint32_t *)(this + 8964);  // 读字段 fld_2304 = this+8964（nDmgCap）
      if ( *pDwArg2 >= fld_2304 )  // fld_2304=this+8964 nDmgCap
        fld_23042 = fld_2304;  // fld_2304=this+8964 nDmgCap
      *pDwArg2 = fld_23042;
      return 2;
    }
    else if ( *(uint8_t *)(this + 8597) != 0 )  // this+8597〔bCapGate〕
    {
      return 1;  // 返回 1(成功)
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C07C0 sub_4C07C0
// ------------------------------------------------------------
// 证: "LANDRUNNER_OUT"
// 调: sub_4C07C0 sub_4AFDB0 sub_432E50
uint8_t */*thiscall*/ sub_4C07C0(uint8_t **this, int nArg2, int nArg3)  // 实现：调: sub_4C07C0 sub_4AFDB0 sub_432E50
{
  uint8_t *result; // eax
  uint8_t *v5; // edi
  int v6; // eax
  int v7; // eax

  result = sub_4AFDB0(this, nArg2, nArg3);  // 调 基类发射后
  if ( nArg2 == 32 )
  {
    v5 = *this;
    v6 = (*((int (/*thiscall*/ **)(uint8_t **))*this + 38))(this);  // 虚调用 vt+38（this 虚表槽）
    v7 = sub_432E50(v6);  // sub_432E50 —— 存 关系码对调映射 【关系码对调映射】0 与 1 互换与 2 与 3 互换，其余返回 4
    return (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **, int))v5 + 36))(this, v7);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/60584…
  }
  else if ( nArg2 == 42 )
  {
    return (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **, const char *, int, uint32_t, uint32_t))*this + 53))(  // 虚调用 vt+53（this 虚表槽）
                      this,
                      "LANDRUNNER_OUT",  // 音效/动画 TAG LANDRUNNER_OUT
                      -1,
                      0,
                      0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C0820 sub_4C0820
// ------------------------------------------------------------
// 调: sub_4C0820 sub_4AFD50 sub_47E440
int /*userpurge*/ sub_4C0820@<eax>(uint8_t *pArg1@<ecx>, char pszArg2@<bl>, char pszArg3)  // 实现：调: sub_4C0820 sub_4AFD50 sub_47E440
{
  int result; // eax
  char pszArg32; // bl
  int v6; // eax
  bool v7; // al
  bool v8; // al
  bool v9; // al
  bool v10; // al
  bool v11; // al
  bool v12; // al
  bool v13; // al
  bool v14; // al
  char v16; // [esp-4h] [ebp-8h]
  char v17; // [esp-4h] [ebp-8h]
  char v18; // [esp-4h] [ebp-8h]
  char v19; // [esp-4h] [ebp-8h]
  char v20; // [esp-4h] [ebp-8h]
  char v21; // [esp-4h] [ebp-8h]
  char v22; // [esp-4h] [ebp-8h]
  char v23; // [esp-4h] [ebp-8h]

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1);  // 虚调用 vt+308（pArg1）是否本地玩家
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
    v6 = sub_4AFD50(pArg1, pszArg3);  // 调 过滤 → vt+1140 查 32 号表项 >0 判定 → vt+1160 写 1
    LOBYTE(v6) = pszArg32 != 0 && (v6 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 16)) > 0;  // 虚调用 vt+1140（pArg1）读技能表
    (*(void (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 12, v6);  // 虚调用 vt+1160（pArg1）读技能表(变体)
    sub_47E440(pszArg2);  // 调 条目可见性旗标联动(推断)
    v7 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 17) > 0;  // 虚调用 vt+1140（pArg1）读技能表
    v16 = v7;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 13);  // 虚调用 vt+1160（pArg1）读技能表(变体)
    sub_47E440(v16);  // 调 条目可见性旗标联动(推断)
    v8 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 17) > 0;  // 虚调用 vt+1140（pArg1）读技能表
    v17 = v8;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 36);  // 虚调用 vt+1160（pArg1）读技能表(变体)
    sub_47E440(v17);  // 调 条目可见性旗标联动(推断)
    v9 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 18) > 0;  // 虚调用 vt+1140（pArg1）读技能表
    v18 = v9;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 7);  // 虚调用 vt+1160（pArg1）读技能表(变体)
    sub_47E440(v18);  // 调 条目可见性旗标联动(推断)
    v10 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 19) > 0;  // 虚调用 vt+1140（pArg1）读技能表
    v19 = v10;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 6);  // 虚调用 vt+1160（pArg1）读技能表(变体)
    sub_47E440(v19);  // 调 条目可见性旗标联动(推断)
    v11 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 24) > 0;  // 虚调用 vt+1140（pArg1）读技能表
    v20 = v11;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 20);  // 虚调用 vt+1160（pArg1）读技能表(变体)
    sub_47E440(v20);  // 调 条目可见性旗标联动(推断)
    v12 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 24) > 0;  // 虚调用 vt+1140（pArg1）读技能表
    v21 = v12;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 5);  // 虚调用 vt+1160（pArg1）读技能表(变体)
    sub_47E440(v21);  // 调 条目可见性旗标联动(推断)
    v13 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 25) > 0;  // 虚调用 vt+1140（pArg1）读技能表
    v22 = v13;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 14);  // 虚调用 vt+1160（pArg1）读技能表(变体)
    sub_47E440(v22);  // 调 条目可见性旗标联动(推断)
    if ( pszArg32 != 0 )
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 39);  // 虚调用 vt+1140（pArg1）读技能表
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 1160))(pArg1);  // 虚调用 vt+1160（pArg1）读技能表(变体)
    sub_47E440(39);  // 调 条目可见性旗标联动(推断)
    v14 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 40) > 0;  // 虚调用 vt+1140（pArg1）读技能表
    v23 = v14;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 40);  // 虚调用 vt+1160（pArg1）读技能表(变体)
    return sub_47E440(v23);  // 返回 条目可见性旗标联动(推断)
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C0A30 sub_4C0A30
// ------------------------------------------------------------
// 调: sub_4C0A30 sub_4AFEC0 sub_47E440
char /*thiscall*/ sub_4C0A30(int this)  // 实现：调: sub_4C0A30 sub_4AFEC0 sub_47E440
{
  int fld_199C; // eax  | +0x199C → ★ 枪手大状态 ID（CNGunner；va=004C0A30）

  LOBYTE(fld_199C) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  if ( (uint8_t)fld_199C != 0 )
  {
    sub_4AFEC0((uint32_t *)this);  // 调 构成本地玩家操作权限三位一体。**
    LOBYTE(fld_199C) = *(uint8_t *)(this + 7730);  // this+7730〔bSubEnable〕
    if ( (uint8_t)fld_199C != 0 )
    {
      fld_199C = *(uint32_t *)(this + 6556);  // 读字段 fld_199C = this+6556（nMainState6556）
      switch ( fld_199C )  // 按 fld_199C 分派
      {
        case 0:  // case 0 分派（§A 武器状态 TAG 组）
        case 11:  // case 11 分派（§A 武器状态 TAG 组）
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 1);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 2);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 4);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 5);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 6);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 7);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 9);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 11);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 12);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 13);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 14);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 15);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 20);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 30);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 27);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 28);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 29);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 33);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 36);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 37);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 39);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 40);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 43);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 45);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 46);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 3);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 47);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 48);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 50);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 51);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 53);  // 虚调用 vt+1160（this）读技能表(变体)
          LOBYTE(fld_199C) = sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          break;
        case 7:  // case 7 分派（§A 武器状态 TAG 组）
        case 20:  // case 20 分派（§A 武器状态 TAG 组）
          goto LABEL_7;
        case 22:  // case 22 分派（§A 武器状态 TAG 组）
          if ( *(uint32_t *)(this + 8516) == 12 && *(uint32_t *)(this + 8968) == 1 )  // this+8968〔nDmgCapCtx(推断)〕
LABEL_7:
            byte_9A0358 = 1;
          break;
        case 23:  // case 23 分派（§A 武器状态 TAG 组）
          byte_9A0358 = 1;
          byte_9A0384 = 1;  // byte_9A0384 —— 局部 byte_9A0384 → 1
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 15);  // 虚调用 vt+1160（this）读技能表(变体)
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 32);  // 虚调用 vt+1160（this）读技能表(变体)
          LOBYTE(fld_199C) = sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          break;
        default:
          return fld_199C;  // +0x199C → ★ 枪手大状态 ID（CNGunner；va=004C0A30）
      }
    }
  }
  return fld_199C;  // +0x199C → ★ 枪手大状态 ID（CNGunner；va=004C0A30）
}



// ------------------------------------------------------------
// 0x4C0D90 sub_4C0D90
// ------------------------------------------------------------
// 调: sub_4C0D90 sub_4B0530
int /*thiscall*/ sub_4C0D90(uint32_t *this, uint32_t *uArg2)  // 实现：调: sub_4C0D90 sub_4B0530
{
  int result; // eax

  sub_4B0530(this, uArg2);  // sub_4B0530 —— 结果 = 目标引用解除（清 +7888 缓存）
  result = 0;
  if ( (uint32_t *)*(this + 2175) == uArg2 )  // this+8700〔uPhase8700(推断)〕
    *(this + 2175) = 0;  // 写字段 this+2175 ← 0
  if ( (uint32_t *)*(this + 2336) == uArg2 )
    *(this + 2336) = 0;  // 写字段 this+2336 ← 0
  if ( uArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);  // 虚调用 vt+216（this）全场广播
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 12);  // 虚调用 vt+216（this）全场广播
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C0DF0 sub_4C0DF0
// ------------------------------------------------------------
// 调: sub_4C0DF0 sub_41A5E0 sub_47EF20
uint64_t /*thiscall*/ sub_4C0DF0(void *this, int nArg2)  // 实现：调: sub_4C0DF0 sub_41A5E0 sub_47EF20
{
  int pThis_2A0; // eax
  int pThis_474; // [esp-Ch] [ebp-1Ch]
  int pThis_E; // [esp+8h] [ebp-8h]
  float v8; // [esp+18h] [ebp+8h]

  pThis_E = sub_41A5E0((unsigned int)this + 14 * nArg2 + 8460);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 虚调用 vt+672（this）队伍编号取址
  v8 = 1.0 - (COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 1292)) - 1.0);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  if ( nArg2 == 1
    && (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1096))(this) == 0  // 虚调用 vt+1096（this）枪种分派
    && (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1140))(this, 22) > 0 )  // 虚调用 vt+1140（this）读技能表
  {
    pThis_474 = (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1140))(this, 22, -1);  // 虚调用 vt+1140（this）读技能表
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1160))(this);  // 虚调用 vt+1160（this）读技能表(变体)
    v8 = v8 - (double)(int)sub_47EF20(22, 0, pThis_474, -1, 11) * 0.0099999998;  // sub_47EF20 —— 读攻击数据表
  }
  return (uint64_t)((double)pThis_E * v8);
}



// ------------------------------------------------------------
// 0x4C0EB0 sub_4C0EB0
// ------------------------------------------------------------
// 调: sub_4C0EB0 sub_41A5E0 sub_47EF20
uint64_t /*thiscall*/ sub_4C0EB0(void *this)  // 实现：调: sub_4C0EB0 sub_41A5E0 sub_47EF20
{
  int pThis_2A0; // eax
  int pThis_474; // [esp-Ch] [ebp-1Ch]
  int pThis_2128; // [esp+4h] [ebp-Ch]
  float v6; // [esp+Ch] [ebp-4h]

  pThis_2128 = sub_41A5E0((unsigned int)this + 8488);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 虚调用 vt+672（this）队伍编号取址
  v6 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 1292)) - 1.0 + 1.0;  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1096))(this) != 0  // 虚调用 vt+1096（this）枪种分派
    || (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1140))(this, 23) <= 0 )  // 虚调用 vt+1140（this）读技能表
  {
    return (uint64_t)((double)pThis_2128 * v6);
  }
  pThis_474 = (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1140))(this, 23, -1);  // 虚调用 vt+1140（this）读技能表
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1160))(this);  // 虚调用 vt+1160（this）读技能表(变体)
  return (uint64_t)((double)pThis_2128 * ((double)(int)sub_47EF20(23, 0, pThis_474, -1, 11) * 0.0099999998 + v6));  // sub_47EF20 —— 读攻击数据表
}



// ------------------------------------------------------------
// 0x4C0F70 sub_4C0F70
// ------------------------------------------------------------
// 调: sub_4C0F70
char /*thiscall*/ sub_4C0F70(uint32_t *this, int nArg2)  // 实现：调: sub_4C0F70
{
  char result; // al

  if ( nArg2 != 8 )
    return 1;  // 返回 1(成功)
  switch ( *(this + 1639) )  // this+6556〔大状态ID〕
  {
    case 7:  // case 7 分派（§A 武器状态 TAG 组）
    case 8:  // case 8 分派（§A 武器状态 TAG 组）
    case 0x12:  // case 0x12 分派（§A 武器状态 TAG 组）
    case 0x14:  // case 0x14 分派（§A 武器状态 TAG 组）
    case 0x17:  // case 0x17 分派（§A 武器状态 TAG 组）
    case 0x1B:  // case 0x1B 分派（§A 武器状态 TAG 组）
      result = 0;
      break;
    default:
      return 1;  // 返回 1(成功)
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C0FD0 sub_4C0FD0
// ------------------------------------------------------------
// 调: sub_4C0FD0
int /*thiscall*/ sub_4C0FD0(uint32_t *this)  // 实现：调: sub_4C0FD0
{
  int fld_e2156; // eax

  fld_e2156 = *(this + 2156);  // 读字段 fld_e2156 = this+2156
  if ( fld_e2156 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2156 + 80))() != 0 )  // 虚调用 vt+80（fld_e2156）读 4 字节
    return *(this + 2157);  // 返回字段 this+8628（nPoolTime）
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4C1000 sub_4C1000
// ------------------------------------------------------------
// 调: sub_4C1000 sub_41A5E0
int /*thiscall*/ sub_4C1000(uint32_t *this)  // 实现：调: sub_4C1000 sub_41A5E0
{
  int fld_e2164; // eax
  int fld_e21642; // eax
  int v4; // eax
  int result; // eax
  bool v6; // zf

  fld_e2164 = *(this + 2164);  // 读字段 fld_e2164 = this+2164
  if ( fld_e2164 == 0  // fld_e2164=this+8656 【推断】子类AI标记字节
    || (*(uint8_t (**)(void))(*(uint32_t *)fld_e2164 + 80))() == 0  // 虚调用 vt+80（fld_e2164）读 4 字节
    || (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 140))(*(this + 2164)) <= 0 )  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
  {
    return 4;
  }
  fld_e21642 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 128))(*(this + 2164));  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
  v4 = sub_41A5E0(fld_e21642 + 4);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  if ( v4 == 1 )
    return 0;
  if ( v4 == 2 )
    return 1;  // 返回 1(成功)
  v6 = v4 == 30;
  result = 3;
  if ( !v6 )
    return 4;
  return result;
}



// ------------------------------------------------------------
// 0x4C1070 sub_4C1070
// ------------------------------------------------------------
// 调: sub_4C1070
bool /*thiscall*/ sub_4C1070(uint32_t *this)  // 实现：调: sub_4C1070
{
  int fld_e314; // edx

  fld_e314 = *(this + 314);  // 读字段 fld_e314 = this+314
  return fld_e314 != 0 && (*(this + 315) - fld_e314) >> 2 != 0;  // this+1260〔pCondVec1260〕
}



// ------------------------------------------------------------
// 0x4C10A0 sub_4C10A0
// ------------------------------------------------------------
// 调: sub_4C10A0 sub_4B1030 sub_650D20 sub_5F9160
uint8_t */*thiscall*/ sub_4C10A0(uint8_t *this)  // 实现：调: sub_4C10A0 sub_4B1030 sub_650D20 sub_5F9160
{
  sub_4B1030(this);  // sub_4B1030 —— IRDAppendage 基类构造
  *(uint32_t *)this = &CNBulletBuff::`vftable';  // 构造装配 vftable：CNBulletBuff
  sub_650D20(this);  // sub_650D20 —— 与 ·sub_650800 同构（差异：仅 +80..+92）
  sub_5F9160(this);
  return this;
}



// ------------------------------------------------------------
// 0x4C10F0 sub_4C10F0
// ------------------------------------------------------------
// 调: sub_4C10F0
int /*thiscall*/ sub_4C10F0(uint32_t *this, int nArg2, int nArg3)  // 实现：调: sub_4C10F0
{
  *(this + 20) = nArg2;  // 写字段 this+20（nPage） ← nArg2
  *(this + 21) = nArg3;  // 写字段 this+21（bArmorState） ← nArg3
  return nArg2;
}



// ------------------------------------------------------------
// 0x4C1110 sub_4C1110
// ------------------------------------------------------------
// 调: sub_4C1110
int /*thiscall*/ sub_4C1110(uint32_t *this, int nArg2)  // 实现：调: sub_4C1110
{
  *(this + 22) = nArg2;  // 写字段 this+22 ← nArg2
  return nArg2;
}



// ------------------------------------------------------------
// 0x4C1120 sub_4C1120
// ------------------------------------------------------------
// 调: sub_4C1120
int /*thiscall*/ sub_4C1120(uint32_t *this)  // 实现：调: sub_4C1120
{
  return *(this + 20);  // 返回字段 this+80（nAuraStage）
}



// ------------------------------------------------------------
// 0x4C1130 sub_4C1130
// ------------------------------------------------------------
// 调: sub_4C1130
int /*thiscall*/ sub_4C1130(uint32_t *this)  // 实现：调: sub_4C1130
{
  return *(this + 23);  // 返回字段 this+92（pFxObjC）
}



// ------------------------------------------------------------
// 0x4C1140 sub_4C1140
// ------------------------------------------------------------
// 调: sub_4C1140 sub_4C1170
void */*thiscall*/ sub_4C1140(void *Block, char pszArg2)  // 实现：调: sub_4C1140 sub_4C1170
{
  sub_4C1170();
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x4C1170 sub_4C1170
// ------------------------------------------------------------
// 调: sub_4C1170 sub_5F6640
int /*thiscall*/ sub_4C1170(uint32_t *this)  // 实现：调: sub_4C1170 sub_5F6640
{
  int result; // eax

  *this = &CNBulletBuff::`vftable';  // 构造装配 vftable：CNBulletBuff
  nullsub_3(this);
  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // 写字段 this+2 ← &nengine::IObject::`vftable
  *((uint8_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  return result;
}



// ------------------------------------------------------------
// 0x4C11D0 sub_4C11D0
// ------------------------------------------------------------
// 调: sub_4C11D0 sub_4B1030 sub_5F91F0 sub_650D30
uint8_t */*thiscall*/ sub_4C11D0(uint8_t *this, int nArg2)  // 实现：调: sub_4C11D0 sub_4B1030 sub_5F91F0 sub_650D30
{
  sub_4B1030(this);  // sub_4B1030 —— IRDAppendage 基类构造
  *(uint32_t *)this = &CNTrodden::`vftable';  // 构造装配 vftable：CNTrodden
  sub_5F91F0(this);
  sub_650D30(nArg2);  // sub_650D30 —— 参数化设置（+80 状态码）
  return this;
}



// ------------------------------------------------------------
// 0x4C1230 sub_4C1230
// ------------------------------------------------------------
// 调: sub_4C1230 sub_4C1260
void */*thiscall*/ sub_4C1230(void *Block, char pszArg2)  // 实现：调: sub_4C1230 sub_4C1260
{
  sub_4C1260();
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x4C1260 sub_4C1260
// ------------------------------------------------------------
// 调: sub_4C1260 sub_5F6640
int /*thiscall*/ sub_4C1260(uint32_t *this)  // 实现：调: sub_4C1260 sub_5F6640
{
  int result; // eax

  *this = &CNTrodden::`vftable';  // 构造装配 vftable：CNTrodden
  nullsub_3(this);
  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // 写字段 this+2 ← &nengine::IObject::`vftable
  *((uint8_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  return result;
}



// ------------------------------------------------------------
// 0x4C12C0 sub_4C12C0
// ------------------------------------------------------------
// 调: sub_4C12C0 sub_4B1030 sub_5F9510 sub_650D30
int /*thiscall*/ sub_4C12C0(int this, int nArg2)  // 实现：调: sub_4C12C0 sub_4B1030 sub_5F9510 sub_650D30
{
  sub_4B1030((uint8_t *)this);  // sub_4B1030 —— IRDAppendage 基类构造
  *(uint32_t *)this = &CNAerialGatlinged::`vftable';  // 构造装配 vftable：CNAerialGatlinged
  *(uint8_t *)(this + 112) = 0;  // 写字段 this+112（pHostComp） ← 0
  *(uint32_t *)(this + 108) = &off_6C2B88;  // 写字段 this+108（nAdd108） ← &off_6C2B88
  *(uint32_t *)(this + 116) = 0;  // 写字段 this+116（pSessionCtx） ← 0
  *(uint8_t *)(this + 120) = 1;  // 写字段 this+120（pAnimObj） ← 1
  *(uint8_t *)(this + 122) = 0;  // 写字段 this+122 ← 0
  *(uint8_t *)(this + 121) = 0;  // 写字段 this+121 ← 0
  *(uint32_t *)(this + 132) = 0;  // 写字段 this+132（nAdd132） ← 0
  *(uint32_t *)(this + 128) = 0;  // 写字段 this+128（szStatusKeyBuf） ← 0
  *(uint32_t *)(this + 124) = 0;  // 写字段 this+124（pAuraAnim） ← 0
  sub_5F9510(this);
  sub_650D30(nArg2);  // sub_650D30 —— 参数化设置（+80 状态码）
  return this;
}



// ------------------------------------------------------------
// 0x4C1340 sub_4C1340
// ------------------------------------------------------------
// 调: sub_4C1340 sub_698F90
char /*thiscall*/ sub_4C1340(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 实现：调: sub_4C1340 sub_698F90
{
  int pThis_6C; // ecx

  *(this + 120) = 1;  // 写字段 this+120（pAnimObj） ← 1
  pThis_6C = (int)(this + 108);  // this+108 第 1 组·宿主属性 +886 增量
  *(uint8_t *)(pThis_6C + 13) = 0;  // 写字段 pThis_6C+13 ← 0
  *(uint8_t *)(pThis_6C + 14) = 0;  // 写字段 pThis_6C+14 ← 0
  return sub_698F90(pThis_6C, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x4C1360 sub_4C1360
// ------------------------------------------------------------
// 调: sub_4C1360 sub_4C1390
void */*thiscall*/ sub_4C1360(void *Block, char pszArg2)  // 实现：调: sub_4C1360 sub_4C1390
{
  sub_4C1390();
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x4C1390 sub_4C1390
// ------------------------------------------------------------
// 调: sub_4C1390 sub_5F6640
int /*thiscall*/ sub_4C1390(uint32_t *this)  // 实现：调: sub_4C1390 sub_5F6640
{
  int result; // eax

  *this = &CNAerialGatlinged::`vftable';  // 构造装配 vftable：CNAerialGatlinged
  nullsub_3(this);
  *(this + 27) = &nengine::IObject::`vftable';  // 写字段 this+27 ← &nengine::IObject::`vftable
  *((uint8_t *)this + 112) = 0;  // 写字段 this+112（pHostComp）
  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // 写字段 this+2 ← &nengine::IObject::`vftable
  *((uint8_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  return result;
}



// ------------------------------------------------------------
// 0x4C1400 sub_4C1400
// ------------------------------------------------------------
// 调: sub_4C1400
char /*stdcall*/ sub_4C1400(void **Block)  // 实现：调: sub_4C1400
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);  // 读字段 result = Block+21（bArmorState）
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4C1400(i[2]);
    i = (void **)*i;
    j__free(Block2);  // 释放堆块
    result = *((uint8_t *)i + 21);  // 读字段 result = i+21（bArmorState）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C1440 sub_4C1440
// ------------------------------------------------------------
// 调: sub_4C1440 sub_6569D0 sub_699000
int /*thiscall*/ sub_4C1440(uint32_t *this)  // 实现：调: sub_4C1440 sub_6569D0 sub_699000
{
  int result; // eax

  sub_6569D0(this + 2130);  // sub_6569D0 —— (this+4)
  result = sub_699000((int)(this + 2));  // 【clock_now(clk)】
  *(this + 2133) = result;  // 写字段 this+2133 ← result
  return result;
}



// ------------------------------------------------------------
// 0x4C1460 sub_4C1460
// ------------------------------------------------------------
// 调: sub_4C1460 sub_4B2270 sub_47E9D0 sub_4B1BA0 sub_47DCC0
int /*thiscall*/ sub_4C1460(int this)  // 实现：调: sub_4C1460 sub_4B2270 sub_47E9D0 sub_4B1BA0 sub_47DCC0
{
  int result; // eax
  uint32_t *pThis_488; // edi
  unsigned int v4; // ebx
  int *v5; // edi
  int pThis_4882; // eax
  int v7; // eax
  int v8; // ecx
  int *v9; // [esp+4h] [ebp-10h] BYREF
  uint32_t *pThis_4883; // [esp+8h] [ebp-Ch]
  int v11; // [esp+Ch] [ebp-8h] BYREF
  int v12; // [esp+10h] [ebp-4h]

  sub_4B2270((uint32_t *)this);  // sub_4B2270 —— 部件特效时长汇总（18 槽）
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 44);  // 虚调用 vt+1140（this）读技能表
  if ( result > 0 )
  {
    pThis_488 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 44);  // 虚调用 vt+1160（this）读技能表(变体)
    result = pThis_488[103];
    v4 = 0;
    pThis_4883 = pThis_488;
    if ( result != 0 )
    {
      result = (pThis_488[104] - result) / 14;
      v12 = result;
    }
    else
    {
      v12 = 0;
    }
    if ( v12 > 0 )
    {
      while ( 1 )
      {
        v11 = sub_47E9D0(pThis_488, v4);  // sub_47E9D0 —— 收招/结束例程
        sub_4B1BA0((int **)(this + 7416), &v9, &v11);  // sub_4B1BA0 —— map lower_bound（键在 +12）
        v5 = v9;
        if ( v9 != *(int **)(this + 7420) )  // this+7420〔map7416End〕
        {
          pThis_4882 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, v11);  // 虚调用 vt+1160（this）读技能表(变体)
          v7 = sub_47DCC0(pThis_4882);
          v8 = v5[5];
          if ( v8 < v7 )
            v5[5] = v8 + 1;
        }
        result = v12;
        if ( (int)++v4 >= v12 )
          break;
        pThis_488 = pThis_4883;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C1530 sub_4C1530
// ------------------------------------------------------------
// 调: sub_4C1530 sub_41A5E0 sub_47E9D0 sub_47DCC0 sub_41A590
signed int /*usercall*/ sub_4C1530@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>)  // 实现：调: sub_4C1530 sub_41A5E0 sub_47E9D0 sub_47DCC0 sub_41A590
{
  signed int result; // eax
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // edx
  uint32_t *v11; // ebx
  int v12; // eax
  double v13; // st7
  int v14; // eax
  int v15; // edi
  int v16; // eax
  unsigned int v17; // ebx
  int v18; // edx
  double v19; // st7
  float v20; // [esp+4h] [ebp-14h]
  int v21; // [esp+8h] [ebp-10h]
  uint32_t *v22; // [esp+Ch] [ebp-Ch]
  uint32_t *v23; // [esp+Ch] [ebp-Ch]
  int v24; // [esp+10h] [ebp-8h]
  int v25; // [esp+10h] [ebp-8h]
  unsigned int v26; // [esp+14h] [ebp-4h]
  int v27; // [esp+14h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);  // 虚调用 vt+308（pDwArg1）是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    v4 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 1160))(pDwArg1, 44, nArg2);  // 虚调用 vt+1160（pDwArg1）读技能表(变体)
    v22 = v4;
    if ( sub_41A5E0((unsigned int)v4 + 510) > 0 )  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v5 = v4[103];
      v24 = v5 != 0 ? (v4[104] - v5) / 14 : 0;
      v26 = 0;
      if ( v24 > 0 )
      {
        while ( 1 )
        {
          v6 = *pDwArg1;
          v7 = sub_47E9D0(v4, v26);  // sub_47E9D0 —— 收招/结束例程
          v8 = (*(int (/*thiscall*/ **)(int *, int))(v6 + 1160))(pDwArg1, v7);
          v9 = sub_41A5E0(v8 + 510);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          if ( v9 > 0 && v9 < sub_47DCC0(v8) )
            sub_41A590(v8 + 510, v10, v9 + 1);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
          if ( (int)++v26 >= v24 )
            break;
          v4 = v22;
        }
      }
    }
    v11 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1160))(pDwArg1, 21);  // 虚调用 vt+1160（pDwArg1）读技能表(变体)
    v23 = v11;
    result = sub_41A5E0((unsigned int)v11 + 510);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result > 0 )
    {
      v12 = sub_41A5E0((unsigned int)v11 + 510);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v13 = (double)(int)sub_47EF20(0, v12, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
      v14 = v11[103];
      v20 = v13 * 0.0099999998;
      v15 = v14 != 0 ? (v11[104] - v14) / 14 : 0;
      result = 0;
      v27 = 0;
      if ( v15 > 0 )
      {
        while ( 1 )
        {
          v21 = *pDwArg1;
          v16 = sub_47E9D0(v11, result);  // sub_47E9D0 —— 收招/结束例程
          v17 = (*(int (/*thiscall*/ **)(int *, int))(v21 + 1160))(pDwArg1, v16) + 524;
          v19 = COERCE_FLOAT(sub_41A5E0(v17)) - v20;  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          if ( v19 <= 0.0 )
          {
            sub_41A590(v17, v18, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
          }
          else
          {
            *(float *)&v25 = v19;
            sub_41A590(v17, v18, v25);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
          }
          result = ++v27;
          if ( v27 >= v15 )
            break;
          v11 = v23;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C16F0 sub_4C16F0
// ------------------------------------------------------------
// 调: sub_4C16F0 sub_699000
double /*thiscall*/ sub_4C16F0(int this)  // 实现：调: sub_4C16F0 sub_699000
{
  int fld_214C; // edi
  uint32_t ***fld_214C2; // ecx
  uint32_t **v4; // eax
  int pThis_8; // eax
  double result; // st7
  int fld_2154; // [esp+8h] [ebp-4h]

  while ( *(uint32_t *)(this + 8528) != 0 )  // 当 *(uint32_t *)(this + 8528) != 0 循环
  {
    fld_214C = **(uint32_t **)(this + 8524);  // this+8524〔bMonCfgFlag〕
    if ( *(uint32_t *)(fld_214C + 8) >= sub_699000(this + 8) - 1000 )  // 【clock_now(clk)】
      break;
    fld_214C2 = *(uint32_t ****)(this + 8524);  // this+8524〔bMonCfgFlag〕
    v4 = *fld_214C2;  // fld_214C2=this+8524 bMonCfgFlag
    if ( *fld_214C2 != fld_214C2 )  // fld_214C2=this+8524 bMonCfgFlag
    {
      *v4[1] = *v4;
      (*v4)[1] = v4[1];
      j__free(v4);  // 释放堆块
      --*(uint32_t *)(this + 8528);  // this+8528 std::string 文案串起点
    }
  }
  pThis_8 = sub_699000(this + 8);  // 【clock_now(clk)】
  result = (double)*(int *)(this + 8528);  // this+8528 std::string 文案串起点
  fld_2154 = pThis_8 - *(uint32_t *)(this + 8532);  // this+8532〔nPhaseValB〕
  if ( fld_2154 >= 1000 )  // fld_2154=this+8532 nPhaseValB
  {
    if ( *(int *)(this + 8528) < 0 )  // this+8528 std::string 文案串起点
      return result + 4294967300.0;
  }
  else
  {
    if ( *(int *)(this + 8528) < 0 )  // this+8528 std::string 文案串起点
      result = result + 4294967300.0;
    return result * 1000.0 / (double)fld_2154;  // fld_2154=this+8532 nPhaseValB
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C17C0 sub_4C17C0
// ------------------------------------------------------------
// 调: sub_4C17C0 sub_41A5E0
int /*thiscall*/ sub_4C17C0(uint32_t *this, uint32_t *uArg2, uint32_t *uArg3, uint32_t *uArg4, int nArg5, int nArg6, int nArg7)  // 实现：调: sub_4C17C0 sub_41A5E0
{
  int fld_e1639; // eax
  int nArg52; // edi
  int nArg72; // ebx
  int fld_e1554; // edx
  int fld_e30; // ecx
  int v13; // eax
  int v14; // eax
  int result; // eax

  fld_e1639 = *(this + 1639);  // 读字段 fld_e1639 = this+1639（bMainStateMirror2）
  if ( fld_e1639 == 8 )  // fld_e1639=this+1639 bMainStateMirror2
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 1 )  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( *((uint8_t *)this + 8596) != 0 )  // this+8596〔bTargetState〕
      {
        nArg52 = nArg5 + 34;  // 计算 nArg52 = nArg5 + 34
        nArg72 = nArg7 - 5;  // 计算 nArg72 = nArg7 - 5
      }
      else
      {
        nArg52 = nArg5 + 38;  // 计算 nArg52 = nArg5 + 38
        nArg72 = nArg7 - 7;  // 计算 nArg72 = nArg7 - 7
      }
      goto LABEL_17;
    }
    goto LABEL_16;
  }
  if ( fld_e1639 == 7 )  // fld_e1639=this+1639 bMainStateMirror2
  {
    if ( *(this + 2154) == 1 )  // this+8616〔uAI8616(推断)〕
    {
      nArg52 = nArg5 + 7;  // 计算 nArg52 = nArg5 + 7
      nArg72 = nArg7 + 7;  // 计算 nArg72 = nArg7 + 7
      goto LABEL_17;
    }
    goto LABEL_16;
  }
  if ( fld_e1639 != 23 )  // fld_e1639=this+1639 bMainStateMirror2
  {
LABEL_16:
    nArg72 = nArg7;
    nArg52 = nArg5;
    goto LABEL_17;
  }
  fld_e1554 = *(this + 1554);  // 读字段 fld_e1554 = this+1554
  fld_e30 = *(this + 30);  // 读字段 fld_e30 = this+30
  v13 = 0;
  if ( fld_e30 == *(uint32_t *)(fld_e1554 + 96) )  // fld_e30=this+30 pAnimObj
  {
    v13 = *(uint32_t *)(fld_e30 + 148) + 1;  // fld_e30=this+30 pAnimObj
  }
  else if ( fld_e30 == *(uint32_t *)(fld_e1554 + 100) )  // fld_e30=this+30 pAnimObj
  {
    v13 = 8 - *(uint32_t *)(fld_e30 + 148);
  }
  nArg52 = dword_6F6C74[v13] + nArg5;
  nArg72 = dword_6F6C98[v13] + nArg7;
  if ( *(this + 2360) == 1 )
  {
    nArg52 -= 5;
    nArg72 -= 3;
  }
LABEL_17:
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )  // 虚调用 vt+152（this）取值(参数)
    v14 = nArg52 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
  else
    v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - nArg52;  // 虚调用 vt+120（this）转发(对象+缓冲)
  *uArg2 = v14;
  *uArg3 = nArg6 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 虚调用 vt+124（this）目标坐标y下界
  result = nArg72 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
  *uArg4 = result;
  return result;
}



// ------------------------------------------------------------
// 0x4C18E0 sub_4C18E0
// ------------------------------------------------------------
// 调: sub_4C18E0 sub_4C17C0 sub_4B2580
int /*thiscall*/ sub_4C18E0(uint8_t *this, uint32_t *uArg2, int *pDwArg3)  // 实现：调: sub_4C18E0 sub_4C17C0 sub_4B2580
{
  int v5; // edi
  int pThis_807; // edx
  int *v7; // eax
  int pThis_9C; // eax
  int v9; // edx
  int pThis_9C22; // eax
  int *pThis_808; // eax
  int v12; // edx
  int pThis_46C; // [esp+4h] [ebp-20h]
  int *v14; // [esp+4h] [ebp-20h]
  int pThis_46C2; // [esp+8h] [ebp-1Ch]
  int pThis_9C2; // [esp+8h] [ebp-1Ch]
  int v17; // [esp+Ch] [ebp-18h] BYREF
  int v18; // [esp+10h] [ebp-14h] BYREF
  int v19; // [esp+14h] [ebp-10h] BYREF
  int v20; // [esp+18h] [ebp-Ch] BYREF
  int v21; // [esp+1Ch] [ebp-8h] BYREF
  char fld_e8596; // [esp+23h] [ebp-1h]

  if ( *((uint32_t *)this + 2129) == 53 )  // this+2129 nPhaseValA
    return 1;  // 返回 1(成功)
  *uArg2 = 0;
  *pDwArg3 = 0;
  pThis_46C = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 1132))(this, 0);  // 虚调用 vt+1132（this 虚表槽）
  pThis_46C2 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1132))(this, 1);  // 虚调用 vt+1132（this 虚表槽）
  v5 = -1;
  if ( pThis_46C == (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this) )  // 虚调用 vt+152（this）取值(参数)
  {
    v5 = 0;
  }
  else if ( pThis_46C2 == 3 )
  {
    v5 = 1;
  }
  pThis_9C2 = -1;
  v14 = nullptr;
  fld_e8596 = *(this + 8596);  // 读字段 fld_e8596 = this+8596（bTargetState）
  if ( v5 == 0 || v5 == -1 )
  {
    v19 = 0;
    v20 = 0;
    v21 = 0;
    *(this + 8596) = 0;  // 写字段 this+8596（bTargetState） ← 0
    sub_4C17C0(this, &v19, &v20, &v21, 47, 0, 119);
    pThis_807 = *((uint32_t *)this + 2055);  // 读字段 pThis_807 = this[2055]
    *(this + 8596) = fld_e8596;  // 写字段 this+8596（bTargetState） ← fld_e8596
    v18 = 0;
    v17 = 0;
    v7 = sub_4B2580(&v18, &v17, (int)this, v19, v20, v21, 0, *(uint32_t *)(pThis_807 + 76), 4, 4, -1, 480, 34, 34, 34);  // sub_4B2580 —— 目标搜索 + 瞄准角输出
    if ( v7 != nullptr )
    {
      v14 = v7;
      pThis_9C = (*(int (/*thiscall*/ **)(uint8_t *, int *))(*(uint32_t *)this + 156))(this, v7);  // 虚调用 vt+156（this 虚表槽）
      v9 = v17;
      pThis_9C2 = pThis_9C;
      *uArg2 = v18;
      *pDwArg3 = v9;
    }
  }
  if ( v5 == 1 || v5 == -1 )
  {
    v19 = 0;
    v18 = 0;
    v17 = 0;
    *(this + 8596) = 1;  // 写字段 this+8596（bTargetState） ← 1
    sub_4C17C0(this, &v19, &v18, &v17, 47, 0, 119);
    pThis_9C22 = pThis_9C2;
    *(this + 8596) = fld_e8596;  // 写字段 this+8596（bTargetState） ← fld_e8596
    v20 = 0;
    v21 = 0;
    if ( pThis_9C2 != -1 )
      pThis_9C22 = pThis_9C2 + 1;
    pThis_808 = sub_4B2580(  // sub_4B2580 —— 目标搜索 + 瞄准角输出
            &v20,
            &v21,
            (int)this,
            v19,
            v18,
            v17,
            0,
            *(uint32_t *)(*((uint32_t *)this + 2056) + 76),  // this+8224〔f_2020〕
            4,
            4,
            pThis_9C22,
            480,
            34,
            34,
            34);
    if ( pThis_808 != nullptr && (pThis_808 != v14 || (int)abs32(v21) < (int)abs32(*pDwArg3)) )  // 判定 pThis_808 != nullptr 且 pThis_808 != v14
    {
      (*(void (/*thiscall*/ **)(uint8_t *, int *))(*(uint32_t *)this + 156))(this, pThis_808);  // 虚调用 vt+156（this 虚表槽）
      v12 = v21;
      *uArg2 = v20;
      *pDwArg3 = v12;
      return 1;  // 返回 1(成功)
    }
    if ( v5 == -1 )
      return 0;
  }
  return v5;
}



// ------------------------------------------------------------
// 0x4C1AF0 sub_4C1AF0
// ------------------------------------------------------------
// 证: "LANDRUNNER_OUT"
// 调: sub_4C1AF0
int /*thiscall*/ sub_4C1AF0(uint32_t *this)  // 实现：调: sub_4C1AF0
{
  int v1; // ebx
  unsigned int v3; // esi
  int fld_e29; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  uint32_t *v9; // eax
  int v10; // ecx
  uint32_t *v11; // eax

  v1 = 0;
  v3 = 0;
LABEL_2:
  while ( 1 )
  {
    fld_e29 = *(this + 29);  // 读字段 fld_e29 = this+29
    v5 = *(uint32_t *)(fld_e29 + 120);  // 读字段 v5 = fld_e29+120（pAnimObj）
    v6 = v5 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v5) >> 2 : 0;  // fld_e29=this+29 pSessionCtx
    if ( (int)v3 >= v6 )
      return v1;
    v7 = *(uint32_t *)(fld_e29 + 120);  // 读字段 v7 = fld_e29+120（pAnimObj）
    if ( v7 != 0 && v3 < (*(uint32_t *)(fld_e29 + 124) - v7) >> 2 )  // fld_e29=this+29 pSessionCtx
      v8 = *(uint32_t *)(v7 + 4 * v3);
    else
      v8 = 0;
    v9 = (uint32_t *)__RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                     v8,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &IRDMonster `RTTI Type Descriptor',
                     0);
    if ( v9 != nullptr && (uint32_t *)v9[2088] == this )
    {
      v10 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v9 + 340))(v9);  // 虚调用 vt+340（v9 虚表槽）
      v11 = &unk_6F6CC8;  // 取全局对象/数组首址（v11 ← unk_6F6CC8）
      while ( v10 != *v11 )  // 当 v10 != *v11 循环
      {
        if ( (int)++v11 >= (int)"LANDRUNNER_OUT" )  // 音效/动画 TAG LANDRUNNER_OUT
        {
          ++v3;  // 计数自增 v3
          goto LABEL_2;
        }
      }
      ++v1;  // 计数自增 v1
    }
    ++v3;  // 计数自增 v3
  }
}



// ------------------------------------------------------------
// 0x4C1BA0 sub_4C1BA0
// ------------------------------------------------------------
// 调: sub_4C1BA0 sub_41A590 sub_4015C0
int /*fastcall*/ sub_4C1BA0(uint32_t *pArg1, int nArg2)  // 实现：调: sub_4C1BA0 sub_41A590 sub_4015C0
{
  int v3; // edx
  int v4; // edx
  unsigned int v5; // edi
  int i; // ebx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  unsigned int v10; // ebx
  size_t *v11; // edi
  int v12; // edx
  int v13; // edx
  int v14; // edx
  int j; // [esp+Ch] [ebp-4h]

  *pArg1 = 0;
  pArg1[1] = 0;
  sub_41A590((unsigned int)(pArg1 + 2), nArg2, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  pArg1[6] = 0;
  sub_41A590((unsigned int)(pArg1 + 7), v3, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  v5 = (unsigned int)pArg1 + 42;
  for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    sub_41A590(v5, v4, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
    v5 += 14;
  }
  sub_41A590((unsigned int)pArg1 + 70, v4, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 21), v7, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 98, v8, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 28), v9, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  v10 = (unsigned int)(pArg1 + 60);  // pArg1+60〔nFadeValue60(推断)〕
  v11 = pArg1 + 46;  // 计算 v11 = pArg1 + 46
  for ( j = 2; j != 0; --j )  // 遍历计次循环（j != 0）
  {
    sub_4015C0(v11 - 14, szPassword, 0);  // 【std::string构造赋值】
    sub_4015C0(v11, szPassword, 0);  // 【std::string构造赋值】
    sub_41A590(v10, v12, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
    v11 += 7;
    v10 += 14;
  }
  sub_41A590((unsigned int)(pArg1 + 67), v13, 1000);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  return sub_41A590((unsigned int)pArg1 + 282, v14, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x4C1C80 sub_4C1C80
// ------------------------------------------------------------
// 调: sub_4C1C80 sub_4C1BA0 sub_41A5E0 sub_41A590 sub_41C150
int /*cdecl*/ sub_4C1C80(uint32_t *pArg1, int nArg2)  // 实现：调: sub_4C1C80 sub_4C1BA0 sub_41A5E0 sub_41A590 sub_41C150
{
  int result; // eax
  int pObj; // edi
  unsigned int v4; // esi
  int v5; // eax
  unsigned int v6; // eax
  char *v7; // ebx
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  unsigned int v16; // ecx
  int v17; // ecx
  unsigned int v18; // esi
  int v19; // eax
  int v20; // ecx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  void *v24; // eax
  int v25; // eax
  int v26; // edx
  unsigned int v27; // [esp+8h] [ebp-38h]
  int v28; // [esp+Ch] [ebp-34h]
  int v29; // [esp+10h] [ebp-30h]
  int v30; // [esp+10h] [ebp-30h]

  result = dword_796E50;  // dword_796E50 —— 栈检 cookie
  pObj = nArg2;
  v4 = 0;
  if ( nArg2 != 0 )
  {
    sub_4C1BA0(pArg1);
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 172))(nArg2);  // 虚调用 vt+172（nArg2 虚表槽）
    v6 = sub_41A5E0(v5 + 4);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    if ( dword_9A05AC != nullptr
      && (dword_9A05B0 - (int)dword_9A05AC) >> 4 > v6
      && (v7 = (char *)dword_9A05BC, dword_9A05BC != nullptr)
      && (dword_9A05C0 - (int)dword_9A05BC) >> 4 > v6 )
    {
      v8 = 16 * v6;  // 计算 v8 = 16 * v6
      v9 = *((uint32_t *)dword_9A05AC + 4 * v6 + 1);
      v28 = v8;
      if ( v9 != 0 )
        v29 = (*(uint32_t *)((char *)dword_9A05AC + v8 + 8) - v9) >> 2;
      else
        v29 = 0;
      if ( v29 > 0 )
      {
        while ( 1 )
        {
          v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2);  // 虚调用 vt+16（nArg2 虚表槽）
          v12 = *(uint32_t *)(v10 + 92);  // 读字段 v12 = v10+92（pFxObjC）
          v13 = v10 + 88;  // 计算 v13 = v10 + 88
          if ( v12 == 0
            || (*(uint32_t *)(v13 + 8) - v12) >> 2 <= v4
            || *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2) + 92) + 4 * v4) == -1 )  // 虚调用 vt+16（nArg2 虚表槽）
          {
            v14 = *(uint32_t *)((char *)dword_9A05AC + v28 + 4);
          }
          else
          {
            v14 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2) + 92);  // 虚调用 vt+16（nArg2 虚表槽）
          }
          v15 = *(uint32_t *)(v14 + 4 * v4);
          if ( v4 != 0 )
          {
            switch ( v4 )  // 按 v4 分派
            {
              case 1u:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
                sub_41A590((unsigned int)(pArg1 + 7), v11, v15);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
                break;
              case 2u:  // case 2 = ENUM_CMDPACKET_LOGIN
                sub_41A590((unsigned int)pArg1 + 70, v11, v15);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
                break;
              case 3u:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
                sub_41A590((unsigned int)pArg1 + 42, v11, v15);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
                break;
              case 4u:  // case 4 = ENUM_CMDPACKET_EXIT
                v16 = (unsigned int)(pArg1 + 60);  // pArg1+60〔nFadeValue60(推断)〕
LABEL_37:
                sub_41C150(v16, v11, v15);  // sub_41C150 —— crypt4byte 初始化转发（0x41A590）
                break;
              case 5u:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
                v16 = (unsigned int)pArg1 + 254;
                goto LABEL_37;
              case 6u:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
                v16 = (unsigned int)(pArg1 + 67);  // pArg1+67〔nPeriodMs〕
                goto LABEL_37;
              case 7u:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
                v16 = (unsigned int)(pArg1 + 21);  // pArg1+21〔bArmorState(推断)〕
                goto LABEL_37;
              case 8u:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
                v16 = (unsigned int)pArg1 + 98;
                goto LABEL_37;
              case 9u:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
                v16 = (unsigned int)(pArg1 + 28);  // pArg1+28〔pPanelVec(推断)〕
                goto LABEL_37;
              case 0xAu:
                v16 = (unsigned int)pArg1 + 282;
                goto LABEL_37;
              default:
                break;
            }
          }
          else
          {
            sub_41A590((unsigned int)(pArg1 + 2), v11, v15);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
          }
          if ( (int)++v4 >= v29 )
          {
            v7 = (char *)dword_9A05BC;
            v8 = v28;
            break;
          }
        }
      }
      v17 = *(uint32_t *)&v7[v8 + 4];
      if ( v17 != 0 )
        v30 = (*(uint32_t *)&v7[v8 + 8] - v17) >> 2;
      else
        v30 = 0;
      v18 = 0;
      v27 = 0;
      if ( v30 > 0 )
      {
        while ( 1 )
        {
          v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 虚调用 vt+16（pObj 虚表槽）
          v20 = *(uint32_t *)(v19 + 108);  // 读字段 v20 = v19+108（nAdd108）
          v21 = v19 + 104;  // 计算 v21 = v19 + 104
          if ( v20 == 0 || (*(uint32_t *)(v21 + 8) - v20) >> 2 <= v18 )
            goto LABEL_49;
          v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 虚调用 vt+16（pObj 虚表槽）
          if ( strcmp((const char *)sub_41ACF0(4 * v18 + *(uint32_t *)(v22 + 108)), szPassword) == 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
            break;
          v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2);  // 虚调用 vt+16（nArg2 虚表槽）
          v24 = (void *)sub_41ACF0(4 * v18 + *(uint32_t *)(v23 + 108));  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
          v18 = v27;
          pObj = nArg2;
LABEL_50:
          if ( v18 != 0 )
          {
            switch ( v18 )  // 按 v18 分派
            {
              case 1u:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
                pArg1[1] = (*(int (/*cdecl*/ **)(int, void *))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, v24);  // 虚调用 vt+12（dword_8F84E4 虚表槽）
                break;
              case 2u:  // case 2 = ENUM_CMDPACKET_LOGIN
                pArg1[6] = (*(int (/*cdecl*/ **)(int, void *))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, v24);  // 虚调用 vt+12（dword_8F84E4 虚表槽）
                break;
              case 3u:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
                sub_4015C0(v24, strlen((const char *)v24));  // 【std::string构造赋值】
                break;
              case 4u:  // case 4 = ENUM_CMDPACKET_EXIT
              case 5u:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
              case 6u:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
                sub_406D60(v24);  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
                break;
              default:
                break;
            }
          }
          else
          {
            *pArg1 = (*(int (/*cdecl*/ **)(int, void *))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, v24);  // 虚调用 vt+12（dword_8F84E4 虚表槽）
          }
          v27 = ++v18;
          if ( (int)v18 >= v30 )
            goto LABEL_63;
        }
        v18 = v27;
        pObj = nArg2;
LABEL_49:
        v24 = (void *)sub_41ACF0(*(uint32_t *)((char *)dword_9A05BC + v28 + 4) + 4 * v18);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        goto LABEL_50;
      }
LABEL_63:
      v25 = sub_41A5E0((unsigned int)pArg1 + 42);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      return sub_41A590((unsigned int)(pArg1 + 14), v26, v25);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
    else
    {
      return off_77F3FC(aCriticalErrorS, v6);  // off_77F3FC —— 日志打印（printf 风格）
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4C2020 sub_4C2020
// ------------------------------------------------------------
// 证: "GUN_IN" | "BOWGUN_IN"
// 调: sub_4C2020 sub_4015C0
int /*cdecl*/ sub_4C2020(int nArg1, int nArg2)  // 实现：调: sub_4C2020 sub_4015C0
{
  int result; // eax

  result = nArg2;
  if ( nArg2 >= 0 )
  {
    if ( nArg2 <= 3 )
    {
      return sub_4015C0("GUN_IN", 6u);  // 【std::string构造赋值】
    }
    else if ( nArg2 == 4 )
    {
      return sub_4015C0("BOWGUN_IN", 9u);  // 【std::string构造赋值】
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C2060 sub_4C2060
// ------------------------------------------------------------
// 证: "GUN_GRAB" | "BOWGUN_GRAB"
// 调: sub_4C2060 sub_4015C0
size_t */*cdecl*/ sub_4C2060(size_t *pArg1, int nArg2)  // 实现：调: sub_4C2060 sub_4015C0
{
  size_t *result; // eax

  result = (size_t *)nArg2;
  if ( nArg2 >= 0 )
  {
    if ( nArg2 <= 3 )
    {
      return sub_4015C0(pArg1, "GUN_GRAB", 8u);  // 【std::string构造赋值】
    }
    else if ( nArg2 == 4 )
    {
      return sub_4015C0(pArg1, "BOWGUN_GRAB", 0xBu);  // 【std::string构造赋值】
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C20A0 sub_4C20A0
// ------------------------------------------------------------
// 调: sub_4C20A0 sub_4015C0 sub_401740 sub_41C5E0 sub_52E300
int ***/*thiscall*/ sub_4C20A0(uint32_t *this, int ***uArg2, int **pDwArg3)  // 实现：调: sub_4C20A0 sub_4015C0 sub_401740 sub_41C5E0 sub_52E300
{
  int **pDwArg32; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *pThis2; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *pThis3; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v20[20]; // [esp+34h] [ebp-34h] BYREF
  int v21; // [esp+48h] [ebp-20h]
  int v22; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 21) != 0 )
  {
    v22 = 15;
    v21 = 0;
    v20[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v26 = 0;
    sub_401740(v20);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::out_of_range::`vftable';  // vftable 复位
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C5E0(&pDwArg3);  // sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
  if ( *((uint8_t *)*pDwArg32 + 21) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;  // 写字段 v8+4（pHostObj） ← v4
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);  // sub_52E300 —— v9 = sub_52E300(v4) 最左
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;  // 写字段 v10+8（nSkillRec8） ← = (uint32_t)pDwArg32
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;  // 写字段 v10+8（nSkillRec8） ← v6
      else
        *(uint32_t *)(v23 + 8) = sub_542490(v4);  // sub_542490 —— 表头+8 = sub_542490(v4) 最右
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 21) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;  // 写字段 v12+4（pHostObj） ← v5
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 20);  // 读字段 v14 = v5+20（nPage）
  *((uint8_t *)v5 + 20) = *((uint8_t *)pDwArg32 + 20);  // 写字段 v5+20（nPage）
  *((uint8_t *)pDwArg32 + 20) = v14;  // 写字段 pDwArg32+20（nPage）
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 20) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 0;  // 写字段 v6+20（nPage）
            sub_433130(v6);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
            v16 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 20) != 1 || *(uint8_t *)(v16[2] + 20) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 20) == 1 )
            {
              *(uint8_t *)(*v16 + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;  // 写字段 v16+20（nPage）
              sub_4296E0(v16);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 1;  // 写字段 v6+20（nPage）
            *(uint8_t *)(v16[2] + 20) = 1;
            sub_433130(v6);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 0;  // 写字段 v6+20（nPage）
            sub_4296E0(v6);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
            v16 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 20) != 1 || *(uint8_t *)(*v16 + 20) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 20) == 1 )
            {
              *(uint8_t *)(v16[2] + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;  // 写字段 v16+20（nPage）
              sub_433130(v16);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 1;  // 写字段 v6+20（nPage）
            *(uint8_t *)(*v16 + 20) = 1;
            sub_4296E0(v6);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
            break;
          }
        }
        *((uint8_t *)v16 + 20) = 0;  // 写字段 v16+20（nPage）
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 20) = 1;  // 写字段 v4+20（nPage）
  }
  j__free(Block);  // 释放堆块
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4C2360 sub_4C2360
// ------------------------------------------------------------
// 调: sub_4C2360 sub_4B36A0 sub_4C1C80
int */*thiscall*/ sub_4C2360(int this, int *pDwArg2)  // 实现：调: sub_4C2360 sub_4B36A0 sub_4C1C80
{
  unsigned int fld_1964; // ebx  | +0x1964 → ★ 当前武器/弹药物件 id（CNGunner；va=004C2360）
  int v4; // edx
  int *v5; // edi
  int fld_19642; // eax  | +0x1964 → ★ 当前武器/弹药物件 id（CNGunner；va=004C2360）

  fld_1964 = *(uint32_t *)(this + 6500);  // 读字段 fld_1964 = this+6500（nWeaponItemId）
  v5 = sub_4B36A0((int **)this, fld_1964, pDwArg2);  // sub_4B36A0 —— 挂载槽部件（观察者 vmt310）
  fld_19642 = *(uint32_t *)(this + 6500);  // 读字段 fld_19642 = this+6500（nWeaponItemId）
  if ( fld_19642 != 0 && fld_19642 != fld_1964 )  // 判定 fld_19642 != 0 且 fld_19642 != fld_1964
    sub_4C1C80(v4, (size_t *)(this + 8220), *(uint32_t *)(this + 6500));  // this+6500〔nWeaponItemId〕
  return v5;
}



// ------------------------------------------------------------
// 0x4C23A0 sub_4C23A0
// ------------------------------------------------------------
// 证: "BOWGUN_DRAW1" | "GUN_LOAD" | "BOWGUN_LOAD" | "GUN_DRAW1"
// 调: sub_4C23A0 sub_4CE8A0 sub_406D60 sub_4C2020 sub_4015C0
void /*cdecl*/ sub_4C23A0(int nArg1, int nArg2, int nArg3)  // 实现：调: sub_4C23A0 sub_4CE8A0 sub_406D60 sub_4C2020 sub_4015C0
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  void **Block2; // eax
  uint8_t v7[4]; // [esp+4h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+8h] [ebp-28h] BYREF
  unsigned int v9; // [esp+1Ch] [ebp-14h]
  int dword_796E502; // [esp+20h] [ebp-10h]
  int v11; // [esp+2Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  if ( nArg2 == 9 || nArg2 == 12 || nArg2 == 14 || nArg2 == 15 || nArg2 == 16 )  // 判定 nArg2 == 9 或 nArg2 == 12 或 nArg2 == 14
  {
    v3 = sub_4CE8A0(nArg3);  // sub_4CE8A0 —— 调用 sub_4CE8A0
    if ( v3 != 0 )
    {
      v9 = 15;
      Block[4] = nullptr;
      LOBYTE(Block[0]) = 0;
      v11 = 0;
      if ( nArg2 == 9 )
      {
        v4 = *(uint32_t *)(v3 + 96);  // 读字段 v4 = v3+96（nStatusMode）
        if ( v4 < 0 )
          goto LABEL_29;
        if ( v4 > 3 )
        {
          if ( v4 == 4 )
          {
LABEL_11:
            sub_406D60("BOWGUN_DRAW1");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
            goto LABEL_28;
          }
LABEL_29:
          Block2 = Block;
LABEL_30:
          (*(void (/*thiscall*/ **)(int, void **, int, uint32_t, uint32_t))(*(uint32_t *)nArg1 + 212))(nArg1, Block2, -1, 0, 0);  // 虚调用 vt+212（nArg1 虚表槽）
          if ( v9 >= 0x10 )
            j__free(Block[0]);  // 释放堆块
          return;
        }
        goto LABEL_19;
      }
      if ( nArg2 == 16 )
      {
        sub_4C2020(v7, *(uint32_t *)(v3 + 96));
        goto LABEL_28;
      }
      v5 = *(uint32_t *)(v3 + 96);  // 读字段 v5 = v3+96（nStatusMode）
      if ( v5 < 0 )
        goto LABEL_29;
      if ( v5 <= 2 )
      {
        if ( nArg2 == 12 )
        {
          sub_406D60("GUN_LOAD");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
          goto LABEL_28;
        }
      }
      else
      {
        if ( v5 != 4 )
          goto LABEL_29;
        if ( nArg2 == 12 )
        {
          sub_406D60("BOWGUN_LOAD");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
          goto LABEL_28;
        }
      }
      if ( nArg2 == 14 )
      {
        if ( v5 > 3 )
          goto LABEL_11;
LABEL_19:
        sub_4015C0("GUN_DRAW1", 9u);  // 【std::string构造赋值】
        goto LABEL_28;
      }
      if ( v5 <= 3 )
        sub_406D60("GUN_DRAW2");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      else
        sub_406D60("BOWGUN_DRAW2");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
LABEL_28:
      Block2 = (void **)Block[0];
      if ( v9 >= 0x10 )
        goto LABEL_30;
      goto LABEL_29;
    }
  }
}



// ------------------------------------------------------------
// 0x4C2530 sub_4C2530
// ------------------------------------------------------------
// 证: "GUN_DRAW1" | "BOWGUN_DRAW1" | "GUN_ROTATE" | "BOWGUN_ROTATE"
// 调: sub_4C2530 sub_4015C0 sub_406D60 sub_4C2020 sub_4C2060
void /*thiscall*/ sub_4C2530(uint32_t *this, int nArg2)  // 实现：调: sub_4C2530 sub_4015C0 sub_406D60 sub_4C2020 sub_4C2060
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void **Block2; // eax
  uint8_t v8[4]; // [esp+4h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+8h] [ebp-28h] BYREF
  unsigned int v10; // [esp+1Ch] [ebp-14h]
  int dword_796E502; // [esp+20h] [ebp-10h]
  int v12; // [esp+2Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  if ( (nArg2 == 10 || nArg2 == 11 || nArg2 == 13 || nArg2 == 15) && *(this + 1625) != 0 )  // 判定 nArg2 == 10 或 nArg2 == 11 或 nArg2 == 13
  {
    v10 = 15;
    Block[4] = nullptr;
    LOBYTE(Block[0]) = 0;
    v12 = 0;
    switch ( nArg2 )  // 按 nArg2 分派
    {
      case 10:  // case 10 分派（§A 武器状态 TAG 组）
        v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this);  // 虚调用 vt+1096（this）枪种分派
        if ( v3 >= 0 )
        {
          if ( v3 <= 3 )
          {
            sub_4015C0("GUN_DRAW1", 9u);  // 【std::string构造赋值】
          }
          else if ( v3 == 4 )
          {
            sub_406D60("BOWGUN_DRAW1");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
          }
        }
        break;
      case 15:  // case 15 分派（§A 武器状态 TAG 组）
        v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this);  // 虚调用 vt+1096（this）枪种分派
        sub_4C2020(v8, v4);
        break;
      case 11:  // case 11 分派（§A 武器状态 TAG 组）
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this);  // 虚调用 vt+1096（this）枪种分派
        if ( v5 >= 0 )
        {
          if ( v5 <= 3 )
          {
            sub_406D60("GUN_ROTATE");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
          }
          else if ( v5 == 4 )
          {
            sub_406D60("BOWGUN_ROTATE");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
          }
        }
        break;
      default:
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this);  // 虚调用 vt+1096（this）枪种分派
        sub_4C2060(v8, v6);
        break;
    }
    Block2 = (void **)Block[0];
    if ( v10 < 0x10 )
      Block2 = Block;
    (*(void (/*thiscall*/ **)(uint32_t *, void **, int, uint32_t, uint32_t))(*this + 212))(this, Block2, -1, 0, 0);  // 虚调用 vt+212（this 虚表槽）
    if ( v10 >= 0x10 )
      j__free(Block[0]);  // 释放堆块
  }
}



// ------------------------------------------------------------
// 0x4C26A0 sub_4C26A0
// ------------------------------------------------------------
// 调: sub_4C26A0 sub_4C1400 sub_4C20A0
int **/*thiscall*/ sub_4C26A0(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)  // 实现：调: sub_4C26A0 sub_4C1400 sub_4C20A0
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);  // this+4〔宿主对象〕
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )  // fld_e1=this+4 宿主对象
  {
    sub_4C1400(*(void ***)(fld_e1 + 4));  // fld_e1=this+4 宿主对象
    (*(this + 1))[1] = (int *)*(this + 1);  // this+4〔宿主对象〕
    fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
    *(this + 2) = nullptr;  // 写字段 this+2 ← nullptr
    *fld_e12 = fld_e12;  // fld_e12=this+4 宿主对象
    (*(this + 1))[2] = (int *)*(this + 1);  // this+4〔宿主对象〕
    *pDwArg2 = **(this + 1);  // this+4〔宿主对象〕
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 21) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_4C20A0(this, (int ***)&pDwArg3, v10);
      }
      while ( pDwArg32 != pDwArg42 );  // 循环直到 pDwArg32 != pDwArg42
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4C2760 sub_4C2760
// ------------------------------------------------------------
// 调: sub_4C2760 sub_41DC80
int /*cdecl*/ sub_4C2760(int nArg1, int nArg2, int nArg3)  // 实现：调: sub_4C2760 sub_41DC80
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 16 )
    result = sub_41DC80(i, nArg3);  // sub_41DC80 —— vector<T 4B 驻留句柄> 拷贝赋值 operator=
  return result;
}



// ------------------------------------------------------------
// 0x4C2790 sub_4C2790
// ------------------------------------------------------------
// 调: sub_4C2790 sub_41DC80
int /*cdecl*/ sub_4C2790(int nArg1, int nArg2, int nArg3)  // 实现：调: sub_4C2790 sub_41DC80
{
  int nArg22; // esi
  int nArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    nArg22 -= 16;
    nArg32 -= 16;
    sub_41DC80(nArg32, nArg22);  // sub_41DC80 —— vector<T 4B 驻留句柄> 拷贝赋值 operator=
  }
  while ( nArg22 != nArg1 );  // 循环直到 nArg22 != nArg1
  return nArg32;
}



// ------------------------------------------------------------
// 0x4C27D0 sub_4C27D0
// ------------------------------------------------------------
// 调: sub_4C27D0 sub_699000 sub_40C0F0 sub_437320
int /*thiscall*/ sub_4C27D0(int *this)  // 实现：调: sub_4C27D0 sub_699000 sub_40C0F0 sub_437320
{
  int pThis_2; // eax
  int fld_e2131; // edi
  int v4; // ecx
  uint32_t *v5; // ebx
  int result; // eax
  int pThis_22; // [esp+Ch] [ebp-4h] BYREF

  pThis_2 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
  fld_e2131 = *(this + 2131);  // 读字段 fld_e2131 = this+2131
  v4 = *(uint32_t *)(fld_e2131 + 4);  // 读字段 v4 = fld_e2131+4（pHostObj）
  pThis_22 = pThis_2;
  v5 = sub_40C0F0(fld_e2131, v4, &pThis_22);  // sub_40C0F0 —— list 结点分配（12B：前驱/后继/数据）
  result = sub_437320(1);  // sub_437320 —— 链表计数累加
  *(uint32_t *)(fld_e2131 + 4) = v5;  // 写字段 fld_e2131+4（pHostObj） ← v5
  *(uint32_t *)v5[1] = v5;
  return result;
}



// ------------------------------------------------------------
// 0x4C2820 sub_4C2820
// ------------------------------------------------------------
// 调: sub_4C2820 sub_4B1030 sub_5F9AE0 sub_5F9B20
int /*thiscall*/ sub_4C2820(int this, int nArg2, int nArg3)  // 实现：调: sub_4C2820 sub_4B1030 sub_5F9AE0 sub_5F9B20
{
  sub_4B1030((uint8_t *)this);  // sub_4B1030 —— IRDAppendage 基类构造
  *(uint32_t *)this = &CNWeaponMastery::`vftable';  // 构造装配 vftable：CNWeaponMastery
  *(uint32_t *)(this + 84) = 0;  // 写字段 this+84（pFxObjA） ← 0
  *(uint32_t *)(this + 88) = 0;  // 写字段 this+88（pFxObjB） ← 0
  *(uint32_t *)(this + 92) = 0;  // 写字段 this+92（pFxObjC） ← 0
  sub_5F9AE0(this);
  sub_5F9B20(nArg2, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x4C2890 sub_4C2890
// ------------------------------------------------------------
// 调: sub_4C2890 sub_4C28C0
void */*thiscall*/ sub_4C2890(void *Block, char pszArg2)  // 实现：调: sub_4C2890 sub_4C28C0
{
  sub_4C28C0();
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x4C28C0 sub_4C28C0
// ------------------------------------------------------------
// 调: sub_4C28C0 sub_5F6640
int /*thiscall*/ sub_4C28C0(void **this)  // 实现：调: sub_4C28C0 sub_5F6640
{
  int result; // eax

  *this = &CNWeaponMastery::`vftable';  // 构造装配 vftable：CNWeaponMastery
  nullsub_3(this);
  if ( *(this + 21) != nullptr )  // this+84〔pFxObjA(推断)〕
    j__free(*(this + 21));  // 释放堆块
  *(this + 21) = nullptr;  // 写字段 this+21（bArmorState） ← nullptr
  *(this + 22) = nullptr;  // 写字段 this+22 ← nullptr
  *(this + 23) = nullptr;  // 写字段 this+23 ← nullptr
  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // 调 基类析构
  *((uint8_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  *(this + 2) = &nengine::IObject::`vftable';  // 写字段 this+2 ← &nengine::IObject::`vftable
  return result;
}



// ------------------------------------------------------------
// 0x4C2940 sub_4C2940
// ------------------------------------------------------------
// 调: sub_4C2940 sub_4B3E70 sub_53FE50 sub_4C2820 sub_5F9DD0
void /*thiscall*/ sub_4C2940(int *this, void *pArg2, void *Block)  // 实现：调: sub_4C2940 sub_4B3E70 sub_53FE50 sub_4C2820 sub_5F9DD0
{
  void *pMem; // eax
  int pObj; // eax
  int fld_e2379; // ecx

  sub_4B3E70(this, pArg2, (int)Block);  // sub_4B3E70 —— Buff 图标/状态附加物增删
  if ( pArg2 == (void *)52 )
  {
    if ( (int)Block <= 0 )
    {
      fld_e2379 = *(this + 2379);  // 读字段 fld_e2379 = this+2379
      if ( fld_e2379 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2379 + 80))(fld_e2379) != 0 )  // 虚调用 vt+80（fld_e2379）读 4 字节
        sub_53FE50(*(this + 2379));  // 调 按指针移除：找到 a2 → vt+32(0) → memmove 收缩 → vt+76/vt+68(0)
    }
    else
    {
      if ( *(this + 2379) == 0 )
      {
        pMem = operator new(0x88u);  // 堆分配
        if ( pMem != nullptr )
          pObj = sub_4C2820((int)pMem, 2, 52);  // 调 于 this+8556/8560 并经·sub_5F9DD0 起效
        else
          pObj = 0;
        *(this + 2379) = pObj;  // 写字段 this+2379 ← pObj
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;  // 虚调用 vt+64（pObj）读游标登记(跳过包头)
      }
      sub_5F9DD0(Block);
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2379) + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
        *(this + 2379),
        this,
        this,
        0,
        0,
        0,
        -1);
    }
  }
}



// ------------------------------------------------------------
// 0x4C2A30 sub_4C2A30
// ------------------------------------------------------------
// 调: sub_4C2A30 sub_4C1070 sub_4B3DF0
int /*thiscall*/ sub_4C2A30(uint32_t *this, void *Block)  // 实现：调: sub_4C2A30 sub_4C1070 sub_4B3DF0
{
  int result; // eax
  int pObj; // esi
  bool v5; // bl
  int v6; // esi
  int pObj2; // eax
  float v8; // [esp+Ch] [ebp-28h]
  int v9; // [esp+24h] [ebp-10h]

  nullsub_1(Block);
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 52))(Block);  // 虚调用 vt+52（Block）归属坐标y
  if ( result == *(this + 2370) )
  {
    result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)Block + 40))(Block, 529);  // 虚调用 vt+40（Block）条件查询(273等)
    if ( (uint8_t)result == 1 )
    {
      pObj = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 792))(this, 8);  // 虚调用 vt+792（this）角色槽物品取
      if ( pObj != 0
        || (result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 792))(this, 10), pObj = result, result != 0) )  // 虚调用 vt+792（this）角色槽物品取
      {
        result = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 4);  // 虚调用 vt+16（pObj 虚表槽）
        v5 = false;
        v9 = 20;
        if ( result == 32240 || result == 32265 )  // 判定 result == 32240 或 result == 32265
          goto LABEL_11;
        if ( result == 10095 )
        {
          result = sub_4C1070(pObj);
          if ( (uint8_t)result != 0 )
          {
            result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 224))(pObj);  // 虚调用 vt+224（pObj）以 &hWnd 写出窗口句柄，返回该句柄非 4 —— 调用方据此判网页控件存活。
            v5 = (uint8_t)result != 0;
          }
          v9 = 15;
          if ( v5 )
          {
LABEL_11:
            v6 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                   (int)Block,
                   0,
                   &CNRDObject `RTTI Type Descriptor',
                   &IRDActiveObject `RTTI Type Descriptor',
                   0);
            if ( operator new(0x7Cu) != nullptr )  // 堆分配
            {
              v8 = (float)v9;
              pObj2 = sub_4B3DF0(8, 1, LODWORD(v8), 0, 0);  // sub_4B3DF0 —— 存 CNChangeStatus 状态附加(状态=3, 标志=1, 数值=-100.0f, 时长=60000ms, 1)
            }
            else
            {
              pObj2 = 0;
            }
            result = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj2 + 56))(  // 虚调用 vt+56（pObj2 虚表槽）
                       pObj2,
                       v6,
                       v6,
                       0,
                       0,
                       0,
                       -1);
          }
        }
        *(this + 2370) = 0xFFFF;  // 写字段 this+2370 ← 0xFFFF
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C2B80 sub_4C2B80
// ------------------------------------------------------------
// 调: sub_4C2B80 sub_4C2790
int /*cdecl*/ sub_4C2B80(int nArg1, int nArg2, int nArg3)  // 实现：调: sub_4C2B80 sub_4C2790
{
  return sub_4C2790(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x4C2BA0 sub_4C2BA0
// ------------------------------------------------------------
// 调: sub_4C2BA0 sub_4B3600
unsigned int ***/*cdecl*/ sub_4C2BA0(unsigned int ***uArg1, int nArg2, int nArg3)  // 实现：调: sub_4C2BA0 sub_4B3600
{
  unsigned int ***uArg12; // esi
  unsigned int ***result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg12 = uArg1;
  v6[4] = v6;
  v6[3] = uArg1;
  v7 = 0;
  while ( nArg2 != 0 )  // 循环直到 nArg2 != 0
  {
    LOBYTE(v7) = 1;
    if ( uArg12 != nullptr )
      result = sub_4B3600(uArg12, nArg3);  // sub_4B3600 —— 指针容器拷贝赋值
    --nArg2;  // 计数自减 nArg2
    uArg12 += 4;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C2C30 sub_4C2C30
// ------------------------------------------------------------
// 调: sub_4C2C30 sub_4C26A0
int /*thiscall*/ sub_4C2C30(int this)  // 实现：调: sub_4C2C30 sub_4C26A0
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4C26A0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));  // this+16〔nChannelTypeSel(推断)〕
  j__free(*(void **)(this + 4));  // 释放堆块
  *(uint32_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x4C2C70 sub_4C2C70
// ------------------------------------------------------------
// 调: sub_4C2C70 sub_47E9D0 sub_699000 sub_47E440 sub_4AED20
int /*thiscall*/ sub_4C2C70(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：调: sub_4C2C70 sub_47E9D0 sub_699000 sub_47E440 sub_4AED20
{
  int v5; // esi
  int pThis_668; // esi
  int v7; // eax
  int pObj2; // esi
  int pObj; // eax
  int pObj3; // eax
  int v11; // eax
  int v12; // eax
  void *v14; // [esp+Ch] [ebp-20h] BYREF
  int v15; // [esp+10h] [ebp-1Ch]
  int v16; // [esp+14h] [ebp-18h]
  int v17; // [esp+18h] [ebp-14h]
  int v18; // [esp+1Ch] [ebp-10h] BYREF
  int v19; // [esp+28h] [ebp-4h]

  if ( *(this + 1639) == 12  // this+6556〔大状态ID〕
    && (uint32_t *)dword_8F7C04 == this  // 本地玩家对象
    && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 8) > 0 )  // 虚调用 vt+1140（this）读技能表
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 8);  // 虚调用 vt+1160（this）读技能表(变体)
    v5 = sub_47E9D0(1);  // sub_47E9D0 —— 收招/结束例程
    pThis_668 = sub_699000((int)(this + 1640)) + v5;  // 【clock_now(clk)】
    v7 = *this;
    *(this + 2162) = pThis_668;  // 写字段 this+2162 ← pThis_668
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v7 + 1160))(this, 3);
    sub_47E440(1);  // 调 条目可见性旗标联动(推断)
    byte_9A0358 = 1;
  }
  pObj2 = nArg2;
  if ( *(this + 1639) == 17  // this+6556〔大状态ID〕
    && *(this + 154) == -1  // this+616〔nReactionState〕
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    pObj = __RTDynamicCast(pObj2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // pObj = 调 __RTDynamicCast
    if ( pObj != 0
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 824))(pObj) != 0  // 虚调用 vt+824（pObj 虚表槽）
      && (unsigned int)sub_4AED20(pObj2) <= 1 )  // this+642 非 0 → 直接返回 this+644；否则从动画对象 +112 读帧
    {
      v15 = 0;
      v16 = 0;
      v17 = 0;
      v19 = 0;
      nArg2 = 0;
      sub_431230(&nArg2);  // sub_431230 —— uint32 vector push_back
      nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);  // 虚调用 vt+48（pObj2）归属坐标x
      sub_431230(&nArg2);  // sub_431230 —— uint32 vector push_back
      nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);  // 虚调用 vt+52（pObj2）归属坐标y
      sub_431230(&nArg2);  // sub_431230 —— uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 18, &v14, 0, 0);  // 虚调用 vt+560（this 虚表槽）
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 596))(pObj2, 0);  // 虚调用 vt+596（pObj2 虚表槽）
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);  // 虚调用 vt+604（this）收招例程
      v19 = -1;
      sub_5E5260(&v14);  // 调 动画子对象清理临时缓冲
    }
  }
  if ( *(this + 1639) == 16  // this+6556〔大状态ID〕
    && *(this + 2172) == 14  // this+8688〔bVec8688(推断)〕
    && *(this + 154) == -1  // this+616〔nReactionState〕
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    pObj3 = __RTDynamicCast(pObj2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // pObj3 = 调 __RTDynamicCast
    if ( pObj3 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 824))(pObj3) != 0 )  // 虚调用 vt+824（pObj3 虚表槽）
    {
      v18 = sub_4AED20(pObj2);  // 调 this+642 非 0 → 直接返回 this+644；否则从动画对象 +112 读帧
      v11 = *(uint32_t *)pObj2;
      nArg2 = 100;
      v12 = (*(int (/*thiscall*/ **)(int, int *, uint32_t *))(v11 + 648))(pObj2, &nArg2, this);  // 调虚槽 +648：写入 100（格挡/减伤基础值槽）
      if ( v18 == 0 && v12 == 0 )
      {
        v15 = 0;
        v16 = 0;
        v17 = 0;
        v19 = 1;
        v18 = 14;
        sub_431230(&v18);  // sub_431230 —— uint32 vector push_back
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);  // 虚调用 vt+48（pObj2）归属坐标x
        sub_431230(&v18);  // sub_431230 —— uint32 vector push_back
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);  // 虚调用 vt+52（pObj2）归属坐标y
        sub_431230(&v18);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 16, &v14, 0, 0);  // 虚调用 vt+560（this 虚表槽）
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 596))(pObj2, 0);  // 虚调用 vt+596（pObj2 虚表槽）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);  // 虚调用 vt+604（this）收招例程
        v19 = -1;
        sub_5E5260(&v14);  // 调 动画子对象清理临时缓冲
      }
    }
  }
  return sub_4AFB30(pObj2, nArg3, nArg4);  // 返回 先 vt+1104(this, 8)；再转发基类 sub_4D6D90（=IRDActiveObject_vmt1F4 攻方完整反应…
}



// ------------------------------------------------------------
// 0x4C2F40 sub_4C2F40
// ------------------------------------------------------------
// 调: sub_4C2F40 sub_47EF20 sub_445870 sub_431230 sub_5E5260
int /*thiscall*/ sub_4C2F40(uint32_t *this, int nArg2, float *pArg3, char pszArg4)  // 实现：调: sub_4C2F40 sub_47EF20 sub_445870 sub_431230 sub_5E5260
{
  int pObj; // ebx
  float *v6; // eax
  int v7; // edx
  float *v8; // edi
  int fld_e1639; // eax  | +0x199C → ★ 枪手大状态 ID（CNGunner；va=004C0A30）
  int v10; // eax
  int v11; // edx
  float *v12; // ecx
  int v13; // eax
  int v14; // eax
  float *pArg32; // edi
  int fld_e16392; // eax  | +0x199C → ★ 枪手大状态 ID（CNGunner；va=004C0A30）
  int v17; // edi
  int v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // edi
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v30; // [esp-Ch] [ebp-40h]
  int v31; // [esp-Ch] [ebp-40h]
  int v32; // [esp-4h] [ebp-38h]
  int v33; // [esp+0h] [ebp-34h]
  int v34; // [esp+4h] [ebp-30h]
  int v35; // [esp+8h] [ebp-2Ch]
  void *v36; // [esp+Ch] [ebp-28h] BYREF
  int v37; // [esp+10h] [ebp-24h]
  int v38; // [esp+14h] [ebp-20h] BYREF
  int v39; // [esp+18h] [ebp-1Ch]
  int v40; // [esp+1Ch] [ebp-18h]
  float *v41; // [esp+20h] [ebp-14h]
  int v42; // [esp+24h] [ebp-10h]
  int v43; // [esp+30h] [ebp-4h]

  pObj = nArg2;
  v6 = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // 虚调用 vt+348（nArg2）渲染数据块指针
  v7 = *(uint32_t *)pObj;
  v8 = v6;
  v41 = v6;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(v7 + 368))(pObj) == 0  // 调虚槽 +368：位移预测写入
    || (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 10) <= 0  // 虚调用 vt+1140（this）读技能表
    || *((uint8_t *)v8 + 16) == 0 && *v8 <= 0.0 )
  {
    goto LABEL_20;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) != 0 )  // 虚调用 vt+128（this）目标坐标y上界
    goto LABEL_20;
  fld_e1639 = *(this + 1639);  // 读字段 fld_e1639 = this+1639（bMainStateMirror2）
  if ( fld_e1639 == 4 )  // fld_e1639=this+1639 bMainStateMirror2
    goto LABEL_20;
  if ( fld_e1639 == 9 )  // fld_e1639=this+1639 bMainStateMirror2
    goto LABEL_20;
  if ( pszArg4 != 0 )
    goto LABEL_20;
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 10);  // 虚调用 vt+1160（this）读技能表(变体)
  v11 = *this;
  v42 = v10;
  nArg2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v11 + 1140))(this, 10);
  v40 = sub_47EF20(0, nArg2, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
  if ( sub_445870(&unk_6D0B57, 10000) >= (signed int)(100 * (uint64_t)(double)v40)  // sub_445870 —— 结果 = 槽表随机数
    || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1312))(this, 10) == 0 )  // 虚调用 vt+1312（this 虚表槽）
  {
    goto LABEL_20;
  }
  v12 = v41;
  *((uint8_t *)this + 8960) = 1;  // 写字段 this+8960（bDmgCapOn）
  v13 = *((uint32_t *)v12 + 3);  // 读字段 v13 = v12[3]
  if ( v13 == 1 )
  {
    v14 = sub_47EF20(2, nArg2, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
  }
  else
  {
    if ( v13 != 0 )
    {
      if ( v13 == 2 )
        *(this + 2241) = 100;  // 写字段 this+2241 ← 100
      goto LABEL_18;
    }
    v14 = sub_47EF20(1, nArg2, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
  }
  *(this + 2241) = 100 - v14;  // 写字段 this+2241 ← 100 - v14
LABEL_18:
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    v37 = 0;
    v38 = 0;
    v39 = 0;
    v43 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)pObj + 660))(pObj, this);  // 虚调用 vt+660（pObj 虚表槽）
    sub_431230((int)&v36, &nArg2);  // sub_431230 —— uint32 vector push_back
    pArg32 = pArg3;
    nArg2 = (uint64_t)(pArg3[3] * 0.5 + *pArg3);
    sub_431230((int)&v36, &nArg2);  // sub_431230 —— uint32 vector push_back
    nArg2 = (uint64_t)(pArg32[5] * 0.5 + pArg32[2]);
    sub_431230((int)&v36, &nArg2);  // sub_431230 —— uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 21, &v36, 0, 0);  // 虚调用 vt+560（this 虚表槽）
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 8);  // 虚调用 vt+1104（this 虚表槽）
    v43 = -1;
    sub_5E5260(&v36);  // 调 动画子对象清理临时缓冲
  }
LABEL_20:
  if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 26) > 0  // 虚调用 vt+1140（this）读技能表
    && *((uint8_t *)this + 8960) == 0  // this+8960〔bDmgCapOn〕
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) == 0 )  // 虚调用 vt+128（this）目标坐标y上界
  {
    fld_e16392 = *(this + 1639);  // 读字段 fld_e16392 = this+1639（bMainStateMirror2）
    if ( fld_e16392 != 4 && fld_e16392 != 9 && sub_4AED00(v41) && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 576))(pObj) != 0 )  // 虚调用 vt+576（pObj）受击方判定体
    {
      v30 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1140))(this, 26, -1);  // 虚调用 vt+1140（this）读技能表
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1160))(this);  // 虚调用 vt+1160（this）读技能表(变体)
      v17 = sub_47EF20(26, 0, v30, -1, 11);  // sub_47EF20 —— 读攻击数据表
      if ( sub_445870(28748541, 10000) < 100 * v17  // sub_445870 —— 结果 = 槽表随机数
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1312))(this, 26) != 0 )  // 虚调用 vt+1312（this 虚表槽）
      {
        *((uint8_t *)this + 8597) = 1;  // 写字段 this+8597（bCapGate）
      }
    }
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 虚调用 vt+308（this）是否本地玩家
    && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 42) > 0 )  // 虚调用 vt+1140（this）读技能表
  {
    v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj);  // 虚调用 vt+348（pObj）渲染数据块指针
    if ( *(uint8_t *)(v18 + 16) != 0 || *(float *)v18 > 0.0 )
    {
      v31 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1140))(this, 42, -1);  // 虚调用 vt+1140（this）读技能表
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1160))(this);  // 虚调用 vt+1160（this）读技能表(变体)
      v19 = sub_47EF20(42, 0, v31, -1, 11);  // sub_47EF20 —— 读攻击数据表
      v32 = sub_445870(253547152, 0);  // sub_445870 —— 结果 = 槽表随机数
      v20 = sub_445870(253547151, 0);  // sub_445870 —— 结果 = 槽表随机数
      off_77F3FC("RAND %d %d", v20, v32);  // off_77F3FC —— 日志打印（printf 风格）
      if ( sub_445870(253547151, 100) < v19  // sub_445870 —— 结果 = 槽表随机数
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1312))(this, 42) != 0 )  // 虚调用 vt+1312（this 虚表槽）
      {
        LOWORD(v38) = rand() % 50 + 25;  // 调 以 16 位种子状态递推并返回 15 位结果
        HIWORD(v38) = rand() % 50 + 25;  // 调 以 16 位种子状态递推并返回 15 位结果
        BYTE2(v39) = rand() % 2 == 0;  // 调 以 16 位种子状态递推并返回 15 位结果
        HIBYTE(v39) = 3 - (rand() % 2 != 0);  // 调 以 16 位种子状态递推并返回 15 位结果
        LOWORD(v39) = rand() % 60 + 40;  // 调 以 16 位种子状态递推并返回 15 位结果
        v21 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 1140))(this, 27, -1, -1, 11);  // 虚调用 vt+1140（this）读技能表
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*this + 1160))(this, 27, 0, v21);  // 虚调用 vt+1160（this）读技能表(变体)
        v22 = sub_47EF20(v33, v34, v35, v36, v37);  // sub_47EF20 —— 读攻击数据表
        v23 = *this;
        v37 = 0;
        v36 = nullptr;
        nArg2 = v22;
        v24 = (*(int (/*thiscall*/ **)(uint32_t *, int, int *, int))(v23 + 152))(this, 1, &v38, 8);  // 调虚槽 +152：效果通道 3
        v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 128))(this, v24);  // 虚调用 vt+128（this）目标坐标y上界
        v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v25);  // 虚调用 vt+124（this）目标坐标y下界
        v27 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v26);  // 虚调用 vt+120（this）转发(对象+缓冲)
        v28 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 376))(this, nArg2, v27);  // 虚调用 vt+376（this 虚表槽）
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v23 + 592))(this, 60002, v28);
      }
    }
  }
  return sub_4AFB80(this, pObj, (int)pArg3, pszArg4);  // 返回 rand 种子 87723146 —— 第二处固定随机源（与 0x4A58F0 的 88771231 并列）
}


// ------------------------------------------------------------
// 0x4C3400 sub_4C3400
// ------------------------------------------------------------
// 调: sub_4C3400 sub_4B9720 sub_431230 sub_5E5260
int /*thiscall*/ sub_4C3400(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：调: sub_4C3400 sub_4B9720 sub_431230 sub_5E5260
{
  int v5; // edi
  int fld_e154; // eax  | +0x0268 → 受击反应态（IRDActiveObject·基类）
  void *pBuf[7]; // [esp+Ch] [ebp-1Ch] BYREF

  v5 = sub_4B9720(nArg2, nArg3, nArg4);  // sub_4B9720 —— 霸体特效（SuperArmorEffect.ani；sub_4920E0 全帧缩放；+40/+52 槽；调 sub_4D71B0 命中主处理器【待验证】）
  if ( *((uint8_t *)this + 8597) != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    fld_e154 = *(this + 154);  // 读字段 fld_e154 = this+154（bCastFlagB）
    if ( fld_e154 != 3 && fld_e154 != 4 && fld_e154 != 5 )  // 判定 fld_e154 != 3 且 fld_e154 != 4 且 fld_e154 != 5
    {
      memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
      pBuf[6] = nullptr;
      nArg4 = 0;
      sub_431230(&nArg4);  // sub_431230 —— uint32 vector push_back
      nArg4 = 26;
      sub_431230(&nArg4);  // sub_431230 —— uint32 vector push_back
      nArg4 = (*(int (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)nArg2 + 660))(nArg2, this);  // 虚调用 vt+660（nArg2 虚表槽）
      sub_431230(&nArg4);  // sub_431230 —— uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 24, pBuf, 0, 0);  // 虚调用 vt+560（this 虚表槽）
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x4C34F0 sub_4C34F0
// ------------------------------------------------------------
// 调: sub_4C34F0 sub_431230
void /*thiscall*/ sub_4C34F0(uint32_t *this, int nArg2)  // 实现：调: sub_4C34F0 sub_431230
{
  uint8_t v3[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v5; // [esp+Ch] [ebp-14h]
  int v6; // [esp+10h] [ebp-10h]
  int v7; // [esp+1Ch] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    if ( nArg2 < 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
    }
    else
    {
      Block = nullptr;
      v5 = 0;
      v6 = 0;
      v7 = 0;
      sub_431230((int)v3, this + 2129);  // sub_431230 —— uint32 vector push_back
      sub_431230((int)v3, this + 2242);  // sub_431230 —— uint32 vector push_back
      sub_431230((int)v3, &nArg2);  // sub_431230 —— uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 26, v3, 0, 0);  // 虚调用 vt+560（this 虚表槽）
      if ( Block != nullptr )
        j__free(Block);  // 释放堆块
    }
  }
}



// ------------------------------------------------------------
// 0x4C35C0 sub_4C35C0
// ------------------------------------------------------------
// 调: sub_4C35C0 sub_425120 sub_498190 sub_497E30
int /*thiscall*/ sub_4C35C0(int this, int nArg2)  // 实现：调: sub_4C35C0 sub_425120 sub_498190 sub_497E30
{
  sub_425120();  // sub_425120 —— CNRDParticleCreater 构造
  *(uint32_t *)this = &CNRDObjectParticleCreater::`vftable';  // 构造装配 vftable：CNRDObjectParticleCreater
  *(uint32_t *)(this + 252) = 0;  // 写字段 this+252（nParamSlotB） ← 0
  *(uint32_t *)(this + 256) = 0;  // 写字段 this+256（bParamSlotC） ← 0
  *(uint32_t *)(this + 260) = 0;  // 写字段 this+260（nParamSlotD） ← 0
  *(uint32_t *)(this + 296) = 15;  // 写字段 this+296（bInitFlag296） ← 15
  *(uint32_t *)(this + 292) = 0;  // 写字段 this+292（nOpenMode292） ← 0
  *(uint8_t *)(this + 276) = 0;  // 写字段 this+276（pMapEntry） ← 0
  sub_498190((size_t *)this);  // sub_498190 —— 对象默认字段装配（+236..+272）
  sub_497E30(this, nArg2);
  return this;
}



// ------------------------------------------------------------
// 0x4C3640 sub_4C3640
// ------------------------------------------------------------
// 调: sub_4C3640 sub_425120 sub_498190 sub_497E40
int /*thiscall*/ sub_4C3640(int this, int nArg2, int nArg3, int nArg4)  // 实现：调: sub_4C3640 sub_425120 sub_498190 sub_497E40
{
  sub_425120();  // sub_425120 —— CNRDParticleCreater 构造
  *(uint32_t *)this = &CNRDObjectParticleCreater::`vftable';  // 构造装配 vftable：CNRDObjectParticleCreater
  *(uint32_t *)(this + 252) = 0;  // 写字段 this+252（nParamSlotB） ← 0
  *(uint32_t *)(this + 256) = 0;  // 写字段 this+256（bParamSlotC） ← 0
  *(uint32_t *)(this + 260) = 0;  // 写字段 this+260（nParamSlotD） ← 0
  *(uint32_t *)(this + 296) = 15;  // 写字段 this+296（bInitFlag296） ← 15
  *(uint32_t *)(this + 292) = 0;  // 写字段 this+292（nOpenMode292） ← 0
  *(uint8_t *)(this + 276) = 0;  // 写字段 this+276（pMapEntry） ← 0
  sub_498190((size_t *)this);  // sub_498190 —— 对象默认字段装配（+236..+272）
  sub_497E40((void *)this, nArg2, nArg3, nArg4);  // sub_497E40 —— 双虚转发 vt+96 与 vt+4
  return this;
}



// ------------------------------------------------------------
// 0x4C36D0 sub_4C36D0
// ------------------------------------------------------------
// 调: sub_4C36D0 sub_4B1030 sub_433AC0 sub_5FA160 sub_5F9160
int /*thiscall*/ sub_4C36D0(int this)  // 实现：调: sub_4C36D0 sub_4B1030 sub_433AC0 sub_5FA160 sub_5F9160
{
  int pThis_50; // eax

  sub_4B1030((uint8_t *)this);  // sub_4B1030 —— IRDAppendage 基类构造
  *(uint32_t *)this = &CNRobotics::`vftable';  // 构造装配 vftable：CNRobotics
  pThis_50 = sub_433AC0(this + 80);  // sub_433AC0 —— 结果 = map 节点分配（0x18）
  *(uint32_t *)(this + 84) = pThis_50;  // 写字段 this+84（pFxObjA） ← pThis_50
  *(uint8_t *)(pThis_50 + 21) = 1;  // 写字段 pThis_50+21（bArmorState） ← 1
  *(uint32_t *)(*(uint32_t *)(this + 84) + 4) = *(uint32_t *)(this + 84);  // this+84〔pFxObjA(推断)〕
  **(uint32_t **)(this + 84) = *(uint32_t *)(this + 84);  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(*(uint32_t *)(this + 84) + 8) = *(uint32_t *)(this + 84);  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 88) = 0;  // 写字段 this+88（pFxObjB） ← 0
  sub_5FA160(this);
  sub_5F9160(this);
  return this;
}



// ------------------------------------------------------------
// 0x4C3750 sub_4C3750
// ------------------------------------------------------------
// 调: sub_4C3750 sub_4C3780
void */*thiscall*/ sub_4C3750(void *Block, char pszArg2)  // 实现：调: sub_4C3750 sub_4C3780
{
  sub_4C3780();
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x4C3780 sub_4C3780
// ------------------------------------------------------------
// 调: sub_4C3780 sub_4C26A0 sub_5F6640
int /*thiscall*/ sub_4C3780(int this)  // 实现：调: sub_4C3780 sub_4C26A0 sub_5F6640
{
  int result; // eax
  int *v3; // [esp-8h] [ebp-28h]
  int *fld_54; // [esp-4h] [ebp-24h]
  int *v5[2]; // [esp+Ch] [ebp-14h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  v5[1] = (int *)this;
  *(uint32_t *)this = &CNRobotics::`vftable';  // 构造装配 vftable：CNRobotics
  v6 = 1;
  nullsub_3(this);
  v4 = *(int **)(this + 84);  // this+84 插值起点 X
  v3 = (int *)*v4;  // v4=this+84 插值起点 X
  LOBYTE(v6) = 0;
  sub_4C26A0((int ***)(this + 80), v5, v3, v4);  // this+80 关联角色对象
  j__free(*(void **)(this + 84));  // 释放堆块
  *(uint32_t *)(this + 84) = 0;  // 写字段 this+84（pFxObjA） ← 0
  *(uint32_t *)(this + 88) = 0;  // 写字段 this+88（pFxObjB） ← 0
  *(uint32_t *)this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  v6 = 2;
  result = sub_5F6640(this);  // 调 基类析构
  *(uint8_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  *(uint32_t *)(this + 8) = &nengine::IObject::`vftable';  // 写字段 this+8（nSkillRec8） ← &nengine::IObject::`vftable
  return result;
}



// ------------------------------------------------------------
// 0x4C3810 sub_4C3810
// ------------------------------------------------------------
// 证: "R_GN_DMG" | "R_GN_DIE" | "GN_JUMP" | "GN_BACK_STEP"
// 调: sub_4C3810 sub_4015C0 sub_4C35C0
void */*thiscall*/ sub_4C3810(uint32_t *this)  // 实现：调: sub_4C3810 sub_4015C0 sub_4C35C0
{
  void *result; // eax

  *(this + 1698) = 2;  // 写字段 this+1698 ← 2
  *(this + 1699) = 2;  // 写字段 this+1699 ← 2
  *(this + 1700) = 2;  // 写字段 this+1700 ← 2
  *(this + 1701) = 3;  // 写字段 this+1701 ← 3
  *(this + 1702) = 4;  // 写字段 this+1702 ← 4
  *(this + 1716) = 1;  // 写字段 this+1716 ← 1
  *(this + 1717) = 7;  // 写字段 this+1717 ← 7
  *(this + 1718) = 13;  // 写字段 this+1718 ← 13
  *(this + 1977) = 0;  // 写字段 this+1977 ← 0
  *(this + 1978) = 0;  // 写字段 this+1978 ← 0
  *(this + 1979) = 0;  // 写字段 this+1979 ← 0
  *(this + 1980) = 0;  // 写字段 this+1980 ← 0
  *(this + 1961) = 44;  // 写字段 this+1961 ← 44
  *(this + 1962) = 65;  // 写字段 this+1962 ← 65
  *(this + 1963) = 2;  // 写字段 this+1963 ← 2
  *(this + 1982) = 8;  // 写字段 this+1982 ← 8
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0("R_GN_DMG", 8u);  // 【std::string构造赋值】
  sub_4015C0("R_GN_DIE", 8u);  // 【std::string构造赋值】
  sub_4015C0("GN_JUMP", 7u);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0("GN_BACK_STEP", 0xCu);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0("R_GN_NOMANA", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("R_GN_COMMAND_PET", 0x10u);  // 【std::string构造赋值】
  sub_4015C0("GN_THROW", 8u);  // 【std::string构造赋值】
  result = operator new(0x12Cu);  // 堆分配
  if ( result != nullptr )
  {
    result = (void *)sub_4C35C0(this);
    *(this + 2054) = result;  // 写字段 this+2054 ← result
  }
  else
  {
    *(this + 2054) = 0;  // 写字段 this+2054 ← 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C39D0 sub_4C39D0
// ------------------------------------------------------------
// 证: "BUFF_FLAMESHOT" | "BUFF_ICESHOT" | "BUFF_SILVERSHOT" | "Common/CommonEffect/BuffIcon.img"
// 调: sub_4C39D0 sub_4B4170 sub_41A5E0 sub_4C10A0 sub_47EF20
int /*thiscall*/ sub_4C39D0(int this, uint32_t *Block, void *pArg3)  // 实现：调: sub_4C39D0 sub_4B4170 sub_41A5E0 sub_4C10A0 sub_47EF20
{
  int result; // eax
  int v5; // edi
  void *pMem2; // eax
  int v7; // eax
  int fld_21D4; // edi  | +0x21D4 → ★ 属性弹 Buff 对象 2（0x4C39D0 与 +21D0 成对，同样懒创建）（CNGunner；va=004C39D0）
  int v9; // ebx
  int fld_21D02; // edi
  int v11; // eax
  int fld_21D03; // ecx
  int **pThis_21B0; // ebx
  uint8_t *pMem3; // eax
  int *v15; // eax
  int *v16; // ebx
  int v17; // ebx
  int pThis_184; // edi
  int pThis_4743; // ebx
  char *pThis_488; // eax
  int v21; // ebx
  uint8_t *pMem; // eax
  uint8_t *v23; // eax
  int fld_21D0; // edi  | +0x21D0 → ★ 属性弹 Buff 对象（CNGunner；va=004C39D0）
  int pThis_474; // eax
  int v26; // eax
  int pThis_4742; // [esp-Ch] [ebp-28h]
  int v28; // [esp+0h] [ebp-1Ch]
  void *v29; // [esp+Ch] [ebp-10h]
  int Blocka; // [esp+24h] [ebp+8h]
  int **pThis_21B02; // [esp+28h] [ebp+Ch]

  sub_4B4170((float *)this, Block, pArg3);  // sub_4B4170 —— ★Buff 图标条装配
  result = sub_41A5E0((unsigned int)(Block + 1));  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v5 = result;
  switch ( result )  // 按 result 分派
  {
    case 1:  // case 1 分派（§A 武器状态 TAG 组）
    case 2:  // case 2 分派（§A 武器状态 TAG 组）
    case 30:  // case 30 分派（§A 武器状态 TAG 组）
      v21 = 0;
      if ( *(uint32_t *)(this + 8656) == 0 )  // this+8656〔uPair8656(推断)〕
      {
        pMem = operator new(0x60u);  // 堆分配
        if ( pMem != nullptr )
          v23 = sub_4C10A0(pMem);
        else
          v23 = nullptr;
        *(uint32_t *)(this + 8656) = v23;  // 写字段 this+8656（uPair8656） ← v23
      }
      switch ( v5 )  // 按 v5 分派
      {
        case 1:  // case 1 分派（§A 武器状态 TAG 组）
          v21 = 13;
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
            this,
            "BUFF_FLAMESHOT",  // 音效/动画 TAG BUFF_FLAMESHOT
            -1,
            0,
            0);
          break;
        case 2:  // case 2 分派（§A 武器状态 TAG 组）
          v21 = 14;
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
            this,
            "BUFF_ICESHOT",  // 音效/动画 TAG BUFF_ICESHOT
            -1,
            0,
            0);
          break;
        case 30:  // case 30 分派（§A 武器状态 TAG 组）
          v21 = 15;
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
            this,
            "BUFF_SILVERSHOT",  // 音效/动画 TAG BUFF_SILVERSHOT
            -1,
            0,
            0);
          break;
        default:
          break;
      }
      if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 49) <= 0 )  // 虚调用 vt+1140（this）读技能表
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8656) + 124))(*(uint32_t *)(this + 8656), 0);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      }
      else
      {
        fld_21D0 = **(uint32_t **)(this + 8656);  // this+8656 pBulletBuff
        pThis_474 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1140))(this);  // 虚调用 vt+1140（this）读技能表
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)this + 1160))(this, 49, 0, pThis_474);  // 虚调用 vt+1160（this）读技能表(变体)
        v26 = sub_47EF20(49, -1, -1, 11, v28);  // sub_47EF20 —— 读攻击数据表
        (*(void (/*thiscall*/ **)(uint32_t, int))(fld_21D0 + 124))(*(uint32_t *)(this + 8656), v26);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      }
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *))(**(uint32_t **)(this + 8656) + 120))(*(uint32_t *)(this + 8656), Block);  // 调虚槽 +120：动画对象
      fld_21D02 = **(uint32_t **)(this + 8656);  // this+8656 pBulletBuff
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
        dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
        "Common/CommonEffect/BuffIcon.img",  // 资源 Common/CommonEffect/BuffIcon.img
        v21,
        0,
        -1);
      v11 = sub_418DD0(pArg3);  // sub_418DD0 —— 资源句柄 (101)
      fld_21D03 = *(uint32_t *)(this + 8656);  // 读字段 fld_21D03 = this+8656（uPair8656）
      return (*(int (/*thiscall*/ **)(int, int, int, int, int))(fld_21D02 + 56))(fld_21D03, this, this, 1, v11);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
    case 46:  // case 46 分派（§A 武器状态 TAG 组）
      if ( *(uint32_t *)(this + 8660) == 0 )  // this+8660〔uEvt8660(推断)〕
      {
        pMem2 = operator new(0x6Cu);  // 堆分配
        if ( pMem2 != nullptr )
          v7 = sub_4C36D0((int)pMem2);
        else
          v7 = 0;
        *(uint32_t *)(this + 8660) = v7;  // 写字段 this+8660（uEvt8660） ← v7
      }
      fld_21D4 = *(uint32_t *)(this + 8660);  // 读字段 fld_21D4 = this+8660（uEvt8660）
      v9 = sub_47EF20(0, pArg3, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
      *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_21D4 + 64))(fld_21D4) + 40) = v9;  // 虚调用 vt+64（fld_21D4）读游标登记(跳过包头)
      fld_21D02 = **(uint32_t **)(this + 8660);  // this+8660 pBulletBuff2
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8);  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
      v11 = sub_418DD0("Common/CommonEffect/BuffIcon.img");  // sub_418DD0 —— 资源句柄 (101)
      fld_21D03 = *(uint32_t *)(this + 8660);  // 读字段 fld_21D03 = this+8660（uEvt8660）
      return (*(int (/*thiscall*/ **)(int, int, int, int, int))(fld_21D02 + 56))(fld_21D03, this, this, 1, v11);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
    case 33:  // case 33 分派（§A 武器状态 TAG 组）
    case 37:  // case 37 分派（§A 武器状态 TAG 组）
      if ( result == 33 )
      {
        pThis_21B0 = (int **)(this + 8624);  // this+8624 【推断】子类AI槽
        Blocka = 17;
      }
      else
      {
        pThis_21B0 = (int **)(this + 8652);  // this+8652 【推断】相位门字节
        Blocka = 18;
      }
      pThis_21B02 = pThis_21B0;  // pThis_21B0=this+8652 【推断】相位门字节
      if ( *pThis_21B0 == nullptr )  // pThis_21B0=this+8652 【推断】相位门字节
      {
        pMem3 = operator new(0x50u);  // 堆分配
        if ( pMem3 != nullptr )
          v15 = (int *)sub_4B1030(pMem3);  // sub_4B1030 —— IRDAppendage 基类构造
        else
          v15 = nullptr;
        *pThis_21B0 = v15;  // pThis_21B0=this+8652 【推断】相位门字节
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v15 + 64))(v15) + 36) = 0;  // 虚调用 vt+64（v15）读游标登记(跳过包头)
      }
      v16 = *pThis_21B0;  // pThis_21B0=this+8652 【推断】相位门字节
      pThis_4742 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 1140))(this, v5, -1);  // 虚调用 vt+1140（this）读技能表
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1160))(this);  // 虚调用 vt+1160（this）读技能表(变体)
      v29 = (void *)sub_47EF20(v5, 0, pThis_4742, -1, 11);  // sub_47EF20 —— 读攻击数据表
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*v16 + 64))(v16) + 40) = v29;  // 虚调用 vt+64（v16）读游标登记(跳过包头)
      v17 = **pThis_21B02;
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
        dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
        "Common/CommonEffect/BuffIcon.img",  // 资源 Common/CommonEffect/BuffIcon.img
        Blocka,
        0,
        -1);
      sub_418DD0(v28);  // sub_418DD0 —— 资源句柄 (101)
      result = (*(int (/*thiscall*/ **)(int *, int, int, int))(v17 + 56))(*pThis_21B02, this, this, 1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
      if ( v5 == 33 )
      {
        pThis_184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // 虚调用 vt+388（this）攻击计算
        pThis_4743 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 33);  // 虚调用 vt+1140（this）读技能表
        pThis_488 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 33);  // 虚调用 vt+1160（this）读技能表(变体)
        result = sub_47EFD0(pThis_488, COERCE_FLOAT(1), pThis_4743, pThis_184, pThis_184, 0);  // 调 技能表槽位设置（越界打 aCriticalError_8；+87 处 14 字节/项表）(推断)
        *(uint32_t *)(this + 8628) = result;  // 写字段 this+8628（nPoolTime） ← result
      }
      break;
    default:
      break;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4C3D40 sub_4C3D40
// ------------------------------------------------------------
// 调: sub_4C3D40 sub_4C2BA0
unsigned int ***/*stdcall*/ sub_4C3D40(unsigned int ***pArg1, int nArg2, int nArg3)  // 实现：调: sub_4C3D40 sub_4C2BA0
{
  sub_4C2BA0(pArg1, nArg2, nArg3);  // 调 就地按 nArg2 复制构造并 +16 递增
  return &pArg1[4 * nArg2];
}



// ------------------------------------------------------------
// 0x4C3D70 sub_4C3D70
// ------------------------------------------------------------
// 调: sub_4C3D70 sub_4B3B60 sub_4B4950
int */*thiscall*/ sub_4C3D70(int *this, int *pDwArg2, int nArg3, int nArg4)  // 实现：调: sub_4C3D70 sub_4B3B60 sub_4B4950
{
  int fld_e2; // edi

  if ( nArg3 != nArg4 )
  {
    fld_e2 = sub_4B3B60(nArg4, *(this + 2), nArg3);  // sub_4B3B60 —— 16 字节元素区间拷贝
    sub_4B4950(fld_e2, *(this + 2));  // sub_4B4950 —— 16 字节记录数组析构（逐元素清 +4 向量后 free）
    *(this + 2) = fld_e2;  // 写字段 this+2 ← fld_e2
  }
  *pDwArg2 = nArg3;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x4C3DC0 sub_4C3DC0
// ------------------------------------------------------------
// 调: sub_4C3DC0 sub_4B3600 sub_4B2F20 sub_4B5060 sub_4C2B80
void /*thiscall*/ sub_4C3DC0(int this, int pArg2, unsigned int uArg3, int nArg4)  // 实现：调: sub_4C3DC0 sub_4B3600 sub_4B2F20 sub_4B5060 sub_4C2B80
{
  int fld_4; // edx
  int fld_8; // ecx
  unsigned int fld_C; // eax
  int fld_82; // ecx
  unsigned int v10; // eax
  int fld_87; // ecx
  int fld_88; // eax
  char *pMem; // ebx
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v16; // edi
  char *fld_83; // eax
  int fld_86; // edi
  char *v19; // edi
  int v20; // eax
  void *v21; // ebx
  void **v22; // edi
  void **v23; // esi
  int fld_42; // [esp-18h] [ebp-4Ch]
  void *Block2; // [esp-18h] [ebp-4Ch]
  int fld_85; // [esp-Ch] [ebp-40h]
  unsigned int fld_84; // [esp-8h] [ebp-3Ch]
  int v28; // [esp+0h] [ebp-34h] BYREF
  char v29[4]; // [esp+Ch] [ebp-28h] BYREF
  void *v30; // [esp+10h] [ebp-24h]
  void **v31; // [esp+14h] [ebp-20h]
  void *Block; // [esp+1Ch] [ebp-18h]
  int pThis; // [esp+20h] [ebp-14h]
  int *v34; // [esp+24h] [ebp-10h]
  int v35; // [esp+30h] [ebp-4h]
  int v36; // [esp+40h] [ebp+Ch]
  int v37; // [esp+44h] [ebp+10h]

  v34 = &v28;
  pThis = this;
  sub_4B3600(nArg4);  // sub_4B3600 —— 指针容器拷贝赋值
  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  fld_8 = 0;
  v35 = 0;
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 4;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    fld_C = 0;  // fld_C=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
    if ( 0xFFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_4B2F20(this);  // sub_4B2F20 —— vector 长度超限抛出
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( fld_C >= uArg3 + fld_82 )  // fld_C=this+12 nSkillRec12
    {
      fld_83 = *(char **)(this + 8);  // this+32〔nHeight(推断)〕
      Block = fld_83;  // fld_83=this+32 nHeight
      if ( (int)&fld_83[-pArg2] >> 4 >= uArg3 )  // fld_83=this+32 nHeight
      {
        v19 = &fld_83[-16 * uArg3];  // fld_83=this+32 nHeight
        v20 = sub_4B5060(v19, fld_83, fld_83);  // sub_4B5060 —— 16 字节记录区间拷贝（返回尾址）
        Block2 = Block;
        *(uint32_t *)(this + 8) = v20;  // 写字段 this+8（nSkillRec8） ← v20
        sub_4C2B80(pArg2, v19, Block2);
        sub_4C2760(pArg2, pArg2 + 16 * uArg3, v29);
      }
      else
      {
        sub_4B5060(pArg2, fld_83, pArg2 + 16 * uArg3);  // sub_4B5060 —— 16 字节记录区间拷贝（返回尾址）
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 4);  // this+8〔nSkillRec8(推断)〕等 2 字段
        fld_85 = *(uint32_t *)(this + 8);  // 读字段 fld_85 = this+8（nSkillRec8）
        LOBYTE(v35) = 3;
        sub_4C3D40(fld_85, fld_84, v29);  // fld_85=this+8 nSkillRec8
        fld_86 = 16 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;  // 写字段 this+8（nSkillRec8） ← fld_86
        v35 = 0;
        sub_4C2760(pArg2, fld_86 - 16 * uArg3, v29);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (fld_C >> 1) >= fld_C )  // fld_C=this+12 nSkillRec12
        v10 = (fld_C >> 1) + fld_C;  // fld_C=this+12 nSkillRec12
      else
        v10 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_87 )  // fld_87=this+8 nSkillRec8
      {
        if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else
          fld_88 = 0;  // fld_88=this+8 nSkillRec8
        v10 = uArg3 + fld_88;  // 计算 v10 = uArg3 + fld_88
      }
      v37 = 16 * v10;  // 计算 v37 = 16 * v10
      pMem = (char *)operator new(16 * v10);  // 堆分配
      fld_42 = *(uint32_t *)(this + 4);  // 读字段 fld_42 = this+4（pHostObj）
      Block = pMem;
      LOBYTE(v35) = 1;
      v36 = sub_4B5060(fld_42, pArg2, pMem);  // sub_4B5060 —— 16 字节记录区间拷贝（返回尾址）
      sub_4C2BA0(v36, uArg3, v29);  // 调 就地按 nArg2 复制构造并 +16 递增
      sub_4B5060(pArg2, *(uint32_t *)(this + 8), 16 * uArg3 + v36);  // sub_4B5060 —— 16 字节记录区间拷贝（返回尾址）
      fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
      v35 = 0;
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_89 = 0;  // fld_89=this+8 nSkillRec8
      v16 = fld_89 + uArg3;  // 计算 v16 = fld_89 + uArg3
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
      {
        sub_4B4950(fld_43, *(uint32_t *)(this + 8));  // sub_4B4950 —— 16 字节记录数组析构（逐元素清 +4 向量后 free）
        j__free(*(void **)(this + 4));  // 释放堆块
      }
      *(uint32_t *)(this + 12) = &pMem[v37];  // 写字段 this+12（nSkillRec12） ← &pMem[v37]
      *(uint32_t *)(this + 8) = &pMem[16 * v16];  // 写字段 this+8（nSkillRec8） ← &pMem[16 * v16]
      *(uint32_t *)(this + 4) = pMem;  // 写字段 this+4（pHostObj） ← pMem
    }
  }
  v21 = v30;
  v35 = -1;
  if ( v30 != nullptr )
  {
    v22 = v31;
    v23 = (void **)v30;
    if ( v30 != v31 )
    {
      do
        sub_41B010(v23++);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
      while ( v23 != v22 );  // 循环直到 v23 != v22
    }
    j__free(v21);  // 释放堆块
  }
}


// ------------------------------------------------------------
// 0x4C4080 sub_4C4080
// ------------------------------------------------------------
// 调: sub_4C4080 sub_4C3D70 sub_4C3DC0 sub_41B010
void /*thiscall*/ sub_4C4080(int *this, unsigned int uArg2, char pszArg3, void *Block, void *pArg5, int nArg6)  // 实现：调: sub_4C4080 sub_4C3D70 sub_4C3DC0 sub_41B010
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int fld_e22; // edx
  void *Block2; // ebx
  int v10; // edi
  void **v11; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( fld_e2 >= uArg2 )  // fld_e2=this+8 nSkillRec8
  {
    if ( fld_e1 != 0 && uArg2 < (*(this + 2) - fld_e1) >> 4 )  // fld_e1=this+4 宿主对象
      sub_4C3D70(this, (int *)&uArg2, fld_e1 + 16 * uArg2, *(this + 2));  // this+8〔nSkillRec8(推断)〕
  }
  else
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    sub_4C3DC0((int)this, *(this + 2), uArg2 - fld_e22, (int)&pszArg3);  // 调 扩容追加
  }
  Block2 = Block;
  if ( Block != nullptr )
  {
    v10 = (int)pArg5;
    v11 = (void **)Block;
    if ( Block != pArg5 )
    {
      do
        sub_41B010(v11++);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
      while ( v11 != (void **)v10 );
    }
    j__free(Block2);  // 释放堆块
  }
}



// ------------------------------------------------------------
// 0x4C4150 sub_4C4150
// ------------------------------------------------------------
// 调: sub_4C4150 sub_430B70 sub_4A2CF0 sub_493BD0 sub_494E40
int /*thiscall*/ sub_4C4150(int this, int nArg2, int nArg3, const char *ArgList, char pszArg5)  // 实现：调: sub_4C4150 sub_430B70 sub_4A2CF0 sub_493BD0 sub_494E40
{
  uint32_t *pThis_3C; // ecx

  *(uint8_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  *(uint32_t *)this = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  *(uint8_t *)(this + 12) = 1;  // 写字段 this+12（nSkillRec12） ← 1
  *(uint8_t *)(this + 14) = 0;  // 写字段 this+14 ← 0
  *(uint8_t *)(this + 13) = 0;  // 写字段 this+13 ← 0
  *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
  *(uint32_t *)(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
  *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
  *(uint32_t *)(this + 44) = 0;  // 写字段 this+44（nExpireMs） ← 0
  *(uint32_t *)(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
  *(uint32_t *)(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
  pThis_3C = (uint32_t *)(this + 60);  // this+60〔nFadeValue60(推断)〕等 2 字段
  pThis_3C[15] = 0;  // pThis_3C=this+60 nFadeValue60
  pThis_3C[16] = 0;  // pThis_3C=this+60 nFadeValue60
  pThis_3C[17] = 0;  // pThis_3C=this+60 nFadeValue60
  pThis_3C[19] = 0;  // pThis_3C=this+60 nFadeValue60
  pThis_3C[20] = 0;  // pThis_3C=this+60 nFadeValue60
  pThis_3C[21] = 0;  // pThis_3C=this+60 nFadeValue60
  sub_430B70(pThis_3C);  // sub_430B70 —— 88B 帧条目复位
  *(uint32_t *)(this + 204) = sub_4A2CF0();  // 写字段 this+204（pSubAnim204） ← sub_4A2CF0()
  *(uint32_t *)(this + 208) = 0;  // 写字段 this+208（nField208） ← 0
  sub_493BD0(this);  // sub_493BD0 —— 动画对象复位
  sub_494E40((uint8_t *)this, szPassword, ArgList, pszArg5, 1, 0, nArg2, nArg3);  // sub_494E40 —— 动画创建入口
  return this;
}



// ------------------------------------------------------------
// 0x4C4210 sub_4C4210
// ------------------------------------------------------------
// 调: sub_4C4210 sub_42AF90 sub_657740
int sub_4C4210()  // 实现：调: sub_4C4210 sub_42AF90 sub_657740
{
  void ***v0; // esi
  int i; // ebx
  void **v2; // edi
  int result; // eax

  v0 = (void ***)&dword_9A0598;
  do
  {
    for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
    {
      v2 = *v0;
      if ( *v0 != nullptr )
      {
        sub_42AF90(*v0);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
        result = sub_657740(v2, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
      }
      *v0++ = nullptr;
    }
  }
  while ( (int)v0 < (int)&dword_9A05A8 );
  return result;
}



// ------------------------------------------------------------
// 0x4C4260 sub_4C4260
// ------------------------------------------------------------
// 调: sub_4C4260 sub_42AF90 sub_657740
int /*thiscall*/ sub_4C4260(int this)  // 实现：调: sub_4C4260 sub_42AF90 sub_657740
{
  void (/*thiscall*/ ***pThis_2018)(uint32_t, int); // ecx
  void ***pThis_2198; // edi
  void **v4; // ebx
  int fld_21A4; // edi
  void (/*thiscall*/ ***pThis_21B0)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_21CC)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_21D0)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_21D4)(uint32_t, int); // ecx
  void ***pThis_21E8; // edi
  void **v11; // ebx
  void (/*thiscall*/ ***pThis_220C)(uint32_t, int); // ecx
  void ***pThis_2210; // edi
  void **v14; // ebx
  void ***pThis_2238; // esi
  int ii; // ebx
  void **v17; // edi
  void ***v18; // esi
  int mm; // ebx
  void **v20; // edi
  int pThis2; // edi
  void (/*thiscall*/ ***v22)(uint32_t, int); // ecx
  void ***v23; // esi
  void **v24; // ebx
  void (/*thiscall*/ ***v25)(uint32_t, int); // ecx
  void **v26; // esi
  void **v27; // esi
  void **v28; // esi
  void **v29; // esi
  void ***v30; // esi
  int v31; // ebx
  void **v32; // ebx
  bool v33; // zf
  void **v34; // ebx
  void **v35; // ebx
  int result; // eax
  int v37; // esi
  int (/*thiscall*/ ***v38)(uint32_t, int); // ecx
  int pThis; // [esp+Ch] [ebp-Ch]
  int nn; // [esp+Ch] [ebp-Ch]
  int v41; // [esp+Ch] [ebp-Ch]
  int m; // [esp+10h] [ebp-8h]
  int kk; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]
  int j; // [esp+14h] [ebp-4h]
  int k; // [esp+14h] [ebp-4h]
  int n; // [esp+14h] [ebp-4h]
  int jj; // [esp+14h] [ebp-4h]

  pThis_2018 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8216);  // this+8216〔nAtkActionType〕
  pThis = this;
  if ( pThis_2018 != nullptr )  // pThis_2018=this+8216 nAtkActionType
    (**pThis_2018)(pThis_2018, 1);  // 调 pThis_2018 的虚函数（vt+0）
  *(uint32_t *)(this + 8216) = 0;  // 写字段 this+8216（nAtkActionType） ← 0
  pThis_2198 = (void ***)(this + 8600);  // this+8600 子类 AI 状态字节 1
  for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    v4 = *pThis_2198;  // pThis_2198=this+8600 子类 AI 状态字节 1
    if ( *pThis_2198 != nullptr )  // pThis_2198=this+8600 子类 AI 状态字节 1
    {
      sub_42AF90(*pThis_2198);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v4, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_2198++ = nullptr;  // pThis_2198=this+8600 子类 AI 状态字节 1
  }
  fld_21A4 = *(uint32_t *)(this + 8612);  // 读字段 fld_21A4 = this+8612（uAI8612）
  if ( fld_21A4 != 0 )  // fld_21A4=this+8612 uAI8612
  {
    sub_42AF90(*(void ***)(this + 8612));  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_21A4, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  pThis_21B0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8624);  // this+8624 【推断】子类AI槽
  *(uint32_t *)(this + 8612) = 0;  // 写字段 this+8612（uAI8612） ← 0
  if ( pThis_21B0 != nullptr )
    (**pThis_21B0)(pThis_21B0, 1);  // 调 pThis_21B0 的虚函数（vt+0）
  pThis_21CC = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8652);  // this+8652 【推断】相位门字节
  *(uint32_t *)(this + 8624) = 0;  // 写字段 this+8624（uAI8624） ← 0
  if ( pThis_21CC != nullptr )
    (**pThis_21CC)(pThis_21CC, 1);  // 调 pThis_21CC 的虚函数（vt+0）
  pThis_21D0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8656);  // this+8656 【推断】子类AI标记字节
  *(uint32_t *)(this + 8652) = 0;  // 写字段 this+8652（uPhase8652） ← 0
  if ( pThis_21D0 != nullptr )
    (**pThis_21D0)(pThis_21D0, 1);  // 调 pThis_21D0 的虚函数（vt+0）
  pThis_21D4 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8660);  // this+8660 事件配对/相位槽
  *(uint32_t *)(this + 8656) = 0;  // 写字段 this+8656（uPair8656） ← 0
  if ( pThis_21D4 != nullptr )
    (**pThis_21D4)(pThis_21D4, 1);  // 调 pThis_21D4 的虚函数（vt+0）
  *(uint32_t *)(this + 8660) = 0;  // 写字段 this+8660（uEvt8660） ← 0
  pThis_21E8 = (void ***)(this + 8680);  // this+8680 子类 AI 门字节
  for ( j = 2; j != 0; --j )  // 遍历计次循环（j != 0）
  {
    v11 = *pThis_21E8;  // pThis_21E8=this+8680 子类 AI 门字节
    if ( *pThis_21E8 != nullptr )  // pThis_21E8=this+8680 子类 AI 门字节
    {
      sub_42AF90(*pThis_21E8);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v11, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_21E8++ = nullptr;  // pThis_21E8=this+8680 子类 AI 门字节
  }
  pThis_220C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8716);  // this+8716〔uArr8716〕
  if ( pThis_220C != nullptr )  // pThis_220C=this+8716 uArr8716
    (**pThis_220C)(pThis_220C, 1);  // 调 pThis_220C 的虚函数（vt+0）
  *(uint32_t *)(this + 8716) = 0;  // 写字段 this+8716（uArr8716） ← 0
  pThis_2210 = (void ***)(this + 8720);  // this+8720〔pSegThrTbl8720〕
  for ( k = 2; k != 0; --k )  // 遍历计次循环（k != 0）
  {
    v14 = *pThis_2210;  // pThis_2210=this+8720 pSegThrTbl8720
    if ( *pThis_2210 != nullptr )  // pThis_2210=this+8720 pSegThrTbl8720
    {
      sub_42AF90(*pThis_2210);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v14, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_2210++ = nullptr;  // pThis_2210=this+8720 pSegThrTbl8720
  }
  pThis_2238 = (void ***)(this + 8760);
  for ( m = 5; m != 0; --m )  // 遍历计次循环（m != 0）
  {
    for ( n = 5; n != 0; --n )  // 遍历计次循环（n != 0）
    {
      for ( ii = 2; ii != 0; --ii )  // 遍历计次循环（ii != 0）
      {
        v17 = *pThis_2238;
        if ( *pThis_2238 != nullptr )
        {
          sub_42AF90(*pThis_2238);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
          sub_657740(v17, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
        }
        *pThis_2238++ = nullptr;
      }
    }
  }
  v18 = (void ***)(pThis + 8972);  // pThis+8972〔uEvtState8972(推断)〕
  for ( jj = 5; jj != 0; --jj )  // 遍历计次循环（jj != 0）
  {
    for ( kk = 8; kk != 0; --kk )  // 遍历计次循环（kk != 0）
    {
      for ( mm = 2; mm != 0; --mm )  // 遍历计次循环（mm != 0）
      {
        v20 = *v18;
        if ( *v18 != nullptr )
        {
          sub_42AF90(*v18);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
          sub_657740(v20, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
        }
        *v18++ = nullptr;
      }
    }
  }
  pThis2 = pThis;
  v22 = *(void (/*thiscall*/ ****)(uint32_t, int))(pThis + 9328);
  if ( v22 != nullptr )
    (**v22)(v22, 1);  // 调 v22 的虚函数（vt+0）
  *(uint32_t *)(pThis + 9328) = 0;  // 写字段 pThis+9328 ← 0
  v23 = (void ***)(pThis + 9332);
  for ( nn = 3; nn != 0; --nn )  // 遍历计次循环（nn != 0）
  {
    v24 = *v23;
    if ( *v23 != nullptr )
    {
      sub_42AF90(*v23);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v24, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    *v23++ = nullptr;
  }
  v25 = *(void (/*thiscall*/ ****)(uint32_t, int))(pThis2 + 9360);
  if ( v25 != nullptr )
    (**v25)(v25, 1);  // 调 v25 的虚函数（vt+0）
  v26 = *(void ***)(pThis2 + 9364);
  *(uint32_t *)(pThis2 + 9360) = 0;  // 写字段 pThis2+9360 ← 0
  if ( v26 != nullptr )
  {
    sub_42AF90(v26);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    sub_657740(v26, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  v27 = *(void ***)(pThis2 + 9372);
  *(uint32_t *)(pThis2 + 9364) = 0;  // 写字段 pThis2+9364 ← 0
  if ( v27 != nullptr )
  {
    sub_42AF90(v27);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    sub_657740(v27, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  v28 = *(void ***)(pThis2 + 9376);
  *(uint32_t *)(pThis2 + 9372) = 0;  // 写字段 pThis2+9372 ← 0
  if ( v28 != nullptr )
  {
    sub_42AF90(v28);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    sub_657740(v28, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  v29 = *(void ***)(pThis2 + 9396);
  *(uint32_t *)(pThis2 + 9376) = 0;  // 写字段 pThis2+9376 ← 0
  if ( v29 != nullptr )
  {
    sub_42AF90(v29);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    sub_657740(v29, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  *(uint32_t *)(pThis2 + 9396) = 0;  // 写字段 pThis2+9396 ← 0
  v30 = (void ***)(pThis2 + 9388);
  v41 = 2;
  do
  {
    v31 = (int)*(v30 - 2);
    if ( v31 != 0 )
    {
      sub_42AF90(*(v30 - 2));  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v31, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    v32 = *v30;
    v33 = *v30 == nullptr;
    *(v30 - 2) = nullptr;
    if ( !v33 )
    {
      sub_42AF90(v32);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v32, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    v34 = v30[3];
    *v30 = nullptr;
    if ( v34 != nullptr )
    {
      sub_42AF90(v34);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v34, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    v35 = v30[5];
    v30[3] = nullptr;
    if ( v35 != nullptr )
    {
      sub_42AF90(v35);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v35, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    v30[5] = nullptr;
    ++v30;  // 计数自增 v30
    result = v41 - 1;
    v41 = result;
  }
  while ( result != 0 );  // 循环直到 result != 0
  v37 = *(uint32_t *)(pThis2 + 9432);  // 读字段 v37 = pThis2+9432
  if ( v37 != 0 )
  {
    sub_42AF90(*(void ***)(pThis2 + 9432));  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(v37, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  v38 = *(int (/*thiscall*/ ****)(uint32_t, int))(pThis2 + 9516);
  *(uint32_t *)(pThis2 + 9432) = 0;  // 写字段 pThis2+9432 ← 0
  if ( v38 != nullptr )
    result = (**v38)(v38, 1);  // 调 v38 的虚函数（vt+0）
  *(uint32_t *)(pThis2 + 9516) = 0;  // 写字段 pThis2+9516 ← 0
  return result;
}


// ------------------------------------------------------------
// 0x4C46B0 sub_4C46B0
// ------------------------------------------------------------
// 证: "Character/Gunner/Effect/Animation/ShootEffec" | "Down" | "Jump" | "Tread"
// 调: sub_4C46B0 sub_4015C0 sub_4022F0 sub_402410 sub_501490
int /*thiscall*/ sub_4C46B0(void *this, int nArg2)  // sub_4C46B0 —— v90 = sub_4C46B0
{
  int v3; // edi
  void **Block2; // ecx
  int v5; // esi
  int i; // edi
  int v7; // eax
  int v8; // eax
  int v10; // [esp+Ch] [ebp-30h]
  uint8_t v11[4]; // [esp+10h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+14h] [ebp-28h] BYREF
  unsigned int v13; // [esp+28h] [ebp-14h]
  int dword_796E502; // [esp+2Ch] [ebp-10h]
  int v15; // [esp+38h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  v13 = 15;
  Block[4] = nullptr;
  LOBYTE(Block[0]) = 0;
  sub_4015C0("Character/Gunner/Effect/Animation/ShootEffect/", 0x2Eu);  // 【std::string构造赋值】
  v15 = 0;
  if ( nArg2 != 0 )
  {
    switch ( nArg2 )  // 按 nArg2 分派
    {
      case 1:  // case 1 分派（§A 武器状态 TAG 组）
        sub_4022F0((std::_String_base *)v11, "Down", 4);  // sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
        break;
      case 2:  // case 2 分派（§A 武器状态 TAG 组）
        sub_4022F0((std::_String_base *)v11, "Jump", 4);  // sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
        break;
      case 3:  // case 3 分派（§A 武器状态 TAG 组）
        sub_402410("Tread");  // sub_402410 —— std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
        break;
      default:
        sub_501490(v11);  // 调 对象析构后释放堆块
        return 0;
    }
  }
  else
  {
    sub_4022F0((std::_String_base *)v11, "Up", 2);  // sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
  }
  switch ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1096))(this) )  // 虚调用 vt+1096（this）枪种分派
  {
    case 0:  // case 0 分派（§A 武器状态 TAG 组）
      if ( nArg2 != 3 )
        goto LABEL_14;
      sub_402410("Revolver.ani");  // sub_402410 —— std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
      break;
    case 1:  // case 1 分派（§A 武器状态 TAG 组）
      if ( nArg2 == 3 )
        sub_402410("Automatic.ani");  // sub_402410 —— std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
      else
LABEL_14:
        sub_402410("Pistol.ani");  // sub_402410 —— std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
      break;
    case 2:  // case 2 分派（§A 武器状态 TAG 组）
      sub_4022F0((std::_String_base *)v11, "Musket.ani", 10);  // sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
      break;
    case 3:  // case 3 分派（§A 武器状态 TAG 组）
      sub_4022F0((std::_String_base *)v11, "HandCannon.ani", 14);  // sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
      break;
    case 4:  // case 4 分派（§A 武器状态 TAG 组）
      sub_4022F0((std::_String_base *)v11, "BowGun.ani", 10);  // sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
      break;
    default:
      break;
  }
  v3 = sub_4C1000(this);  // 调 或按 this[2*(pMem+v184)] 取件
  v10 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
  LOBYTE(v15) = 1;
  if ( v10 != 0 )
  {
    LOBYTE(Block2) = Block[0];
    if ( v13 < 0x10 )
      Block2 = Block;
    v5 = sub_4C4150(0, v3, (char)Block2, 1);
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v15) = 0;
  if ( v3 == 1 )
  {
    for ( i = 0; ; ++i )
    {
      v7 = *(uint32_t *)(v5 + 44);  // 读字段 v7 = v5+44（nExpireMs）
      v8 = v7 != 0 ? (*(uint32_t *)(v5 + 48) - v7) / 88 : 0;
      if ( i >= v8 )
        break;
      *(uint32_t *)(sub_4924C0(i) + 40) = 2;  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
    }
  }
  if ( v13 >= 0x10 )
    j__free(Block[0]);  // 释放堆块
  return v5;
}



// ------------------------------------------------------------
// 0x4C4890 sub_4C4890
// ------------------------------------------------------------
// 证: "Effect/Animation/SubWeapon/SubWeaponFrontOnc" | "Effect/Animation/SubWeapon/SubWeaponFrontRap" |
//  "Effect/Animation/SubWeapon/SubWeaponUpOnce1a" | "Effect/Animation/SubWeapon/SubWeaponUpOnce1b"
// 调: sub_4C4890 sub_4015C0 sub_406D60 sub_42FCB0 sub_4319E0
int /*thiscall*/ sub_4C4890(uint32_t *this, int nArg2, int nArg3)  // 实现：调: sub_4C4890 sub_4015C0 sub_406D60 sub_42FCB0 sub_4319E0
{
  int v4; // edi
  int fld_e91; // edx
  int v6; // eax
  void **p_Block; // edx
  int fld_e912; // ecx
  int v9; // eax
  int result; // eax
  int v11; // [esp+Ch] [ebp-4Ch]
  void *v12; // [esp+14h] [ebp-44h] BYREF
  int v13; // [esp+24h] [ebp-34h]
  unsigned int v14; // [esp+28h] [ebp-30h]
  void *Block; // [esp+30h] [ebp-28h] BYREF
  int v16; // [esp+40h] [ebp-18h]
  unsigned int v17; // [esp+44h] [ebp-14h]
  int dword_796E502; // [esp+48h] [ebp-10h]
  int v19; // [esp+54h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  v4 = nArg3 + 8 * nArg2;
  if ( *(this + 2 * v4 + 2213) == 0 )
  {
    v14 = 15;
    v13 = 0;
    LOBYTE(v12) = 0;
    v19 = 1;
    v17 = 15;
    v16 = 0;
    LOBYTE(Block) = 0;
    switch ( nArg3 )  // 按 nArg3 分派
    {
      case 15:  // case 15 分派（§A 武器状态 TAG 组）
        sub_4015C0("Effect/Animation/SubWeapon/SubWeaponFrontOnce1a.ani", 0x33u);  // 【std::string构造赋值】
        sub_4015C0("Effect/Animation/SubWeapon/SubWeaponFrontOnce1b.ani", 0x33u);  // 【std::string构造赋值】
        break;
      case 16:  // case 16 分派（§A 武器状态 TAG 组）
        sub_4015C0("Effect/Animation/SubWeapon/SubWeaponFrontOnce2a.ani", 0x33u);  // 【std::string构造赋值】
        sub_4015C0("Effect/Animation/SubWeapon/SubWeaponFrontOnce2b.ani", 0x33u);  // 【std::string构造赋值】
        break;
      case 17:  // case 17 分派（§A 武器状态 TAG 组）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponFrontRapid1a.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponFrontRapid1b.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        break;
      case 18:  // case 18 分派（§A 武器状态 TAG 组）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponFrontRapid2a.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponFrontRapid2b.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        break;
      case 19:  // case 19 分派（§A 武器状态 TAG 组）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpOnce1a.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpOnce1b.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        break;
      case 20:  // case 20 分派（§A 武器状态 TAG 组）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpOnce2a.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpOnce2b.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        break;
      case 21:  // case 21 分派（§A 武器状态 TAG 组）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpRapid1a.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpRapid1b.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        break;
      case 22:  // case 22 分派（§A 武器状态 TAG 组）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpRapid2a.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpRapid2b.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        break;
      default:
        break;
    }
    LOBYTE(v19) = 2;
    if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    {
      if ( *(this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
        LOBYTE(fld_e91) = (uint8_t)this + 108;  // this+108 第 1 组·宿主属性 +886 增量
      else
        fld_e91 = *(this + 91);  // 读字段 fld_e91 = this+91
      v6 = sub_4319E0(nArg2, 0, fld_e91, (char)&v12, 1);  // sub_4319E0 —— 动画件构造（文件名与参数版）
    }
    else
    {
      v6 = 0;
    }
    LOBYTE(v19) = 1;
    *(this + 2 * v4 + 2213) = v6;
    v11 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    LOBYTE(v19) = 3;
    if ( v11 != 0 )
    {
      LOBYTE(p_Block) = (uint8_t)Block;
      if ( v17 < 0x10 )
        p_Block = &Block;
      if ( *(this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
        LOBYTE(fld_e912) = (uint8_t)this + 108;  // this+108 第 1 组·宿主属性 +886 增量
      else
        fld_e912 = *(this + 91);  // 读字段 fld_e912 = this+91
      v9 = sub_4319E0(nArg2, 0, fld_e912, (char)p_Block, 1);  // sub_4319E0 —— 动画件构造（文件名与参数版）
    }
    else
    {
      v9 = 0;
    }
    *(this + 2 * v4 + 2214) = v9;
    if ( v17 >= 0x10 )
      j__free(Block);  // 释放堆块
    v17 = 15;
    v16 = 0;
    LOBYTE(Block) = 0;
    v19 = -1;
    if ( v14 >= 0x10 )
      j__free(v12);  // 释放堆块
    v14 = 15;
    v13 = 0;
    LOBYTE(v12) = 0;
  }
  sub_494240(2151, *(this + 2 * v4 + 2213));  // sub_494240 —— 子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
  sub_494240(651, *(this + 2 * v4 + 2214));  // sub_494240 —— 子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
  result = *(this + 2 * v4 + 2213);
  *(this + 2323) = result;  // 写字段 this+2323 ← result
  *(this + 2324) = *(this + 2 * v4 + 2214);  // 写字段 this+2324 ← *(this + 2 * v4 + 2214)
  return result;
}


// ------------------------------------------------------------
// 0x4C4B40 sub_4C4B40
// ------------------------------------------------------------
// 证: "Etc/GunnerDefaultGunInfo.etc"
// 调: sub_4C4B40 sub_442A10 sub_41BFE0 sub_42CC00 sub_4B4950
void sub_4C4B40()  // 实现：调: sub_4C4B40 sub_442A10 sub_41BFE0 sub_42CC00 sub_4B4950
{
  int v0; // ecx
  const char *p_Block; // esi
  int nCmp; // eax
  unsigned int v3; // esi
  int v4; // ebx
  uint32_t *v5; // esi
  int v6; // eax
  int v7; // esi
  char *v8; // ecx
  unsigned int v9; // edi
  int *v10; // edx
  int v11; // ebx
  char *v12; // esi
  int v13; // ecx
  unsigned int v14; // edx
  int v15; // edi
  char v16[8]; // [esp-10h] [ebp-58h] BYREF
  char *v17; // [esp-8h] [ebp-50h]
  void **i; // [esp-4h] [ebp-4Ch]
  unsigned int v19; // [esp+Ch] [ebp-3Ch]
  void *v20; // [esp+10h] [ebp-38h] BYREF
  int j; // [esp+14h] [ebp-34h] BYREF
  char v22; // [esp+1Bh] [ebp-2Dh] BYREF
  uint8_t v23[4]; // [esp+1Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+20h] [ebp-28h] BYREF
  unsigned int v25; // [esp+30h] [ebp-18h]
  unsigned int v26; // [esp+34h] [ebp-14h]
  int dword_796E502; // [esp+38h] [ebp-10h]
  int v28; // [esp+44h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"Etc/GunnerDefaultGunInfo.etc") != 0 )  // sub_442A10 —— 结果 = 脚本载入调度（PVF 或磁盘）
  {
    v26 = 15;
    v25 = 0;
    LOBYTE(Block) = 0;
    v28 = 0;
    v20 = nullptr;
    sub_41BFE0(&v20, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
    LOBYTE(v28) = 1;
    v22 = 0;
    if ( dword_9A05AC != nullptr )
    {
      i = (void **)j;
      v17 = (char *)&unk_9A05A8;
      sub_42CC00(dword_9A05AC, dword_9A05B0);  // sub_42CC00 —— 16 字节槽组释放
      j__free(dword_9A05AC);  // 释放堆块
    }
    dword_9A05AC = nullptr;
    dword_9A05B0 = 0;
    dword_9A05B4 = 0;
    if ( dword_9A05BC != nullptr )
    {
      i = (void **)j;
      v17 = (char *)&unk_9A05B8;
      sub_4B4950(dword_9A05BC, dword_9A05C0);  // sub_4B4950 —— 16 字节记录数组析构（逐元素清 +4 向量后 free）
      j__free(dword_9A05BC);  // 释放堆块
    }
    dword_9A05BC = nullptr;
    dword_9A05C0 = 0;
    dword_9A05C4 = 0;
    v19 = 0;
    if ( (uint8_t)sub_443430(v23) != 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
    {
      while ( 1 )
      {
        sub_442B20(v23);  // sub_442B20 —— 国家码标签配对校验（void）
        if ( v25 == 0 )
          goto LABEL_22;
        v0 = v25;
        if ( v25 >= 0xA )
          v0 = 10;
        p_Block = (const char *)Block;
        if ( v26 < 0x10 )
          p_Block = (const char *)&Block;
        nCmp = memcmp(p_Block, "[sub type]", v0);  // nCmp = 调 memcmp
        if ( nCmp != 0 || v25 < 0xA || (LOBYTE(nCmp) = v25 != 10, nCmp != 0) )  // 判定 nCmp != 0 或 v25 < 0xA 或 v25 != 10
        {
LABEL_22:
          if ( sub_40BF00((std::_String_base *)v23, 0, v25, "[integer]", 9u) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00((std::_String_base *)v23, 0, v25, "[string]", 8u) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
            {
              v11 = 16 * v19;  // 计算 v11 = 16 * v19
              sub_4017E0((char *)dword_9A05BC + 16 * v19);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
              for ( i = &v20; sub_442E10() != 0; i = &v20 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
              {
                v12 = (char *)dword_9A05BC + v11;
                v13 = *(uint32_t *)((char *)dword_9A05BC + v11 + 4);
                if ( v13 != 0 )
                  v14 = (*((uint32_t *)v12 + 2) - v13) >> 2;
                else
                  v14 = 0;
                if ( v13 != 0 && v14 < (*((uint32_t *)v12 + 3) - v13) >> 2 )
                {
                  v15 = *((uint32_t *)v12 + 2);  // 读字段 v15 = v12[2]
                  i = (void **)j;
                  v17 = (char *)dword_9A05BC + v11;
                  sub_41FFE0(v15, 1, &v20);  // sub_41FFE0 —— 驻留句柄区间填充 nArg2 个元素
                  *((uint32_t *)v12 + 2) = v15 + 4;  // 写字段 v12[2]（宽4字节）
                }
                else
                {
                  sub_4206D0(*((uint32_t *)v12 + 2), 1, &v20);  // sub_4206D0 —— vector 中间插入（4 字节元素）
                }
              }
            }
          }
          else
          {
            v4 = 16 * v19;  // 计算 v4 = 16 * v19
            v5 = (char *)dword_9A05AC + 16 * v19;
            if ( v5[1] != 0 )
              j__free(*((void **)dword_9A05AC + 4 * v19 + 1));  // 释放堆块
            i = (void **)&v22;
            v5[1] = 0;
            v5[2] = 0;
            v5[3] = 0;
            v6 = sub_4423D0(i);  // sub_4423D0 —— [LOOP] → 动画对象+160
            for ( j = v6; v22 != 0; j = v6 )
            {
              v7 = *(uint32_t *)((char *)dword_9A05AC + v4 + 4);
              v8 = (char *)dword_9A05AC + v4;
              if ( v7 != 0 )
                v9 = (*((uint32_t *)v8 + 2) - v7) >> 2;
              else
                v9 = 0;
              if ( v7 != 0 && v9 < (*((uint32_t *)v8 + 3) - v7) >> 2 )
              {
                v10 = *((int **)v8 + 2);
                *v10 = v6;
                *((uint32_t *)v8 + 2) = v10 + 1;  // 写字段 v8[2]（宽4字节）
              }
              else
              {
                sub_430C80(*((void **)v8 + 2), 1, (int)&j);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
              }
              v6 = sub_4423D0(&v22);  // sub_4423D0 —— [LOOP] → 动画对象+160
            }
          }
          goto LABEL_45;
        }
        v3 = sub_4423D0(nullptr);  // sub_4423D0 —— [LOOP] → 动画对象+160
        v19 = v3;
        if ( dword_9A05AC == nullptr || (dword_9A05B0 - (int)dword_9A05AC) >> 4 <= v3 )  // 判定 dword_9A05AC == nullptr 或 4 <= v3
        {
          j = (int)v16;
          sub_489720(v3 + 1, v16[0], nullptr, 0, 0);  // sub_489720 —— 16 字节元素容器重设长度（缩删/伸补）
        }
        if ( dword_9A05BC == nullptr )
          goto LABEL_21;
        if ( (dword_9A05C0 - (int)dword_9A05BC) >> 4 <= v3 )
          break;
LABEL_45:
        if ( (uint8_t)sub_443430(v23) == 0 )  // sub_443430 —— 读 token 到 string + 国家码标记
          goto LABEL_46;
      }
      v3 = v19;
LABEL_21:
      j = (int)v16;
      sub_4C4080(v3 + 1, v16[0], nullptr, 0, 0);
      goto LABEL_45;
    }
LABEL_46:
    LOBYTE(v28) = 0;
    sub_41B010(&v20);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    if ( v26 >= 0x10 )
      j__free(Block);  // 释放堆块
  }
}


// ------------------------------------------------------------
// 0x4C4EF0 sub_4C4EF0
// ------------------------------------------------------------
// 证: "Character/Gunner/Effect/Animation/MechanicSt" | "Character/Gunner/Effect/Animation/MechanicFr"
// 调: sub_4C4EF0 sub_42FCB0 sub_431860 sub_4053E0 sub_4938F0
int /*cdecl*/ sub_4C4EF0(int nArg1, int nArg2, int nArg3, char pszArg4, int nArg5)  // 实现：调: sub_4C4EF0 sub_42FCB0 sub_431860 sub_4053E0 sub_4938F0
{
  int result; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  DWORD Time; // eax
  int v11; // edi
  int v12; // eax
  BOOL v13; // esi
  int *v14; // esi
  int v15; // eax
  int i; // [esp+0h] [ebp-18h]
  int v17; // [esp+4h] [ebp-14h]
  float v18; // [esp+8h] [ebp-10h]

  result = nArg5;
  if ( nArg5 != 0
    && (pszArg4 == 0
     || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 200))(nArg1) == 0  // 虚调用 vt+200（nArg1）取值比较
     || *(uint8_t *)((result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 200))(nArg1)) + 161) != 0) )  // 虚调用 vt+200（nArg1）取值比较
  {
    if ( dword_9A0598 == 0 )
    {
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v6 = sub_431860((char)"Character/Gunner/Effect/Animation/MechanicStay1.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v6 = 0;
      dword_9A0598 = v6;
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v7 = sub_431860((char)"Character/Gunner/Effect/Animation/MechanicStay2.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v7 = 0;
      dword_9A059C = v7;
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v8 = sub_431860((char)"Character/Gunner/Effect/Animation/MechanicFront1.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v8 = 0;
      dword_9A05A0 = v8;
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v9 = sub_431860((char)"Character/Gunner/Effect/Animation/MechanicFront2.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v9 = 0;
      dword_9A05A4 = v9;
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 152))(nArg1) != 0 )  // 虚调用 vt+152（nArg1）取值(参数)
      v17 = nArg2 - 40;  // 计算 v17 = nArg2 - 40
    else
      v17 = nArg2 + 40;  // 计算 v17 = nArg2 + 40
    Time = timeGetTime();  // Time = 调 timeGetTime
    v11 = 150 - (uint64_t)(sub_4053E0(Time / 5 % 0x168) * -10.0);  // sub_4053E0 —— sin 查表（dword_79D150 表，角度 %360 归一含负角修正）
    LOBYTE(v18) = 0;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 184))(nArg1);  // 虚调用 vt+184（nArg1）字符串/朝向写入
    v13 = v12 != 4;
    if ( v12 == 0 || v12 == 4 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 152))(nArg1) == 0 )  // 虚调用 vt+152（nArg1）取值(参数)
      LOBYTE(v18) = 1;
    v14 = (int *)(8 * v13 + 10093976);
    for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
    {
      sub_4938F0(*v14);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      sub_491F80(*v14, -1, -1, -1, nArg5, 1);  // sub_491F80 —— RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
      if ( pszArg4 != 0 )
      {
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 128))(nArg1);  // 虚调用 vt+128（nArg1）目标坐标y上界
        sub_491EA0(*v14, dword_79C0B0, v17, nArg3, v18, v11 + v15, 0.40000001, 0.30000001, 100);  // sub_491EA0 —— 帧图像绘制入口（递归 +204 子链；byte_790AD0 全局开关 + 自身 +161 阴影位门）
      }
      else
      {
        sub_491D00(*v14, dword_79C0B0, v17, nArg3 - v11, v18);  // sub_491D00 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      }
      ++v14;  // 计数自增 v14
      result = i - 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// ============================================================
// §B 大状态 tick 区(含 0x4C5250)
// ============================================================
// 0x4C5160 sub_4C5160
// ------------------------------------------------------------
// 调: sub_4C5160 sub_4938F0 sub_4C4EF0 sub_4B1E50
uint32_t */*thiscall*/ sub_4C5160(int *this, int nArg2, int nArg3, int nArg4, uint32_t *uArg5)  // 实现：调: sub_4C5160 sub_4938F0 sub_4C4EF0 sub_4B1E50
{
  int fld_e30; // edi  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主）【基类字段】（CNGunner；va=00499020）

  if ( (uint8_t)nArg2 != 0 && *(this + 1788) == 3 )
  {
    fld_e30 = *(this + 30);  // 读字段 fld_e30 = this+30
    if ( fld_e30 != 0 )  // fld_e30=this+30 pAnimObj
    {
      if ( *(uint32_t *)(fld_e30 + 148) == -1 )  // fld_e30=this+30 pAnimObj
        sub_4938F0(*(this + 30));  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      sub_4C4EF0((int)this, nArg3, nArg4, 0, *(uint8_t *)(fld_e30 + 95));  // 调 与 ·sub_4323E0(1
    }
  }
  return sub_4B1E50(this, nArg4, nArg2, nArg3, nArg4, uArg5);  // sub_4B1E50 —— ★外观渲染主驱动（帧推进 sub_4938F0、+52/+56 槽、sub_424760 提交、sub_42FDA0 变换）
}



// ------------------------------------------------------------
// 0x4C51D0 sub_4C51D0
// ------------------------------------------------------------
// 调: sub_4C51D0 sub_4938F0 sub_4C4EF0 sub_4AF4B0
char /*thiscall*/ sub_4C51D0(int *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：调: sub_4C51D0 sub_4938F0 sub_4C4EF0 sub_4AF4B0
{
  int fld_e30; // edi  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主）【基类字段】（CNGunner；va=00499020）

  if ( (uint8_t)nArg2 != 0 && *(this + 1788) == 3 )
  {
    fld_e30 = *(this + 30);  // 读字段 fld_e30 = this+30
    if ( fld_e30 != 0 )  // fld_e30=this+30 pAnimObj
    {
      if ( *(uint32_t *)(fld_e30 + 148) == -1 )  // fld_e30=this+30 pAnimObj
        sub_4938F0(*(this + 30));  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      sub_4C4EF0((int)this, nArg3, nArg4, 1, *(uint8_t *)(fld_e30 + 95));  // 调 与 ·sub_4323E0(1
    }
  }
  return sub_4AF4B0(this, nArg2, nArg3, nArg4, nArg5);  // 返回 对偶形态的成对触发（进入/退出）。sub_58E750 是基类同名实现（前后各调一次）
}



// ------------------------------------------------------------
// 0x4C5240 sub_4C5240
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_4C5240 sub_4C4B40
void sub_4C5240(void)  // 实现：调: sub_4C5240 sub_4C4B40
{
  sub_4C4B40();
}



// ------------------------------------------------------------
// ============================================================
// §C 弹尘与特效
// ============================================================
// 0x4CE550 sub_4CE550
// ------------------------------------------------------------
// 调: sub_4CE550
int /*thiscall*/ sub_4CE550(uint32_t *this)  // sub_4CE550 —— 命令记录写入包装
{
  *this = 0;
  *(this + 1) = 0;  // 写字段 this+1 ← 0
  *((uint16_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  *((uint16_t *)this + 5) = 0;  // 写字段 this[5]（宽2字节）
  *((uint16_t *)this + 6) = 0;  // 写字段 this[6]（宽2字节）
  *((uint16_t *)this + 7) = 0;  // 写字段 this+7（uPathTerm）
  *(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  *(this + 5) = 0;  // 写字段 this+5 ← 0
  *(this + 6) = 0;  // 写字段 this+6 ← 0
  *(this + 7) = 0;  // 写字段 this+7（uPathTerm） ← 0
  *(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  *(this + 9) = 0;  // 写字段 this+9 ← 0
  *(this + 10) = 0;  // 写字段 this+10 ← 0
  *(this + 11) = 0;  // 写字段 this+11 ← 0
  *(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  *(this + 13) = 0;  // 写字段 this+13 ← 0
  *(this + 14) = 0;  // 写字段 this+14 ← 0
  *((uint16_t *)this + 30) = 0;  // 写字段 this[30]（宽2字节）
  *((uint16_t *)this + 31) = 0;  // 写字段 this[31]（宽2字节）
  *((uint16_t *)this + 32) = 0;  // 写字段 this+32（nHeight）
  *((uint16_t *)this + 33) = 0;  // 写字段 this+33（bJobVecDirty）
  *((uint16_t *)this + 34) = 0;  // 写字段 this[34]（宽2字节）
  *((uint16_t *)this + 35) = 0;  // 写字段 this[35]（宽2字节）
  *((uint16_t *)this + 36) = 0;  // 写字段 this+36（nStateWord36）
  *(uint32_t *)((char *)this + 74) = 0;  // this+74〔bResetB74(推断)〕
  *((uint8_t *)this + 78) = 0;  // 写字段 this+78（bGuildFlagC）
  return 0;
}



// ------------------------------------------------------------
// 0x4CE5B0 sub_4CE5B0
// ------------------------------------------------------------
// 调: sub_4CE5B0
int /*cdecl*/ sub_4CE5B0(int pArg1)  // 实现：调: sub_4CE5B0
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 69) == 0; i = *(uint32_t *)(i + 8) )  // 读字段 i = pArg1+8（nSkillRec8）
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x4CE5D0 sub_4CE5D0
// ------------------------------------------------------------
// 调: sub_4CE5D0
uint32_t */*cdecl*/ sub_4CE5D0(uint32_t *pArg1)  // 实现：调: sub_4CE5D0
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 69) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 69) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4CE5F0 sub_4CE5F0
// ------------------------------------------------------------
// 调: sub_4CE5F0
int */*thiscall*/ sub_4CE5F0(int *this)  // sub_4CE5F0 —— 调用 sub_4CE5F0
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 69) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 69) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 69) == 0; result = (int *)result[1] )
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
      if ( *(uint8_t *)(*v2 + 69) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 69) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4CE650 sub_4CE650
// ------------------------------------------------------------
// 调: sub_4CE650
uint32_t */*thiscall*/ sub_4CE650(uint32_t *this, int pArg2)  // 实现：调: sub_4CE650
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
  *(uint32_t *)(pArg2 + 8) = *result;  // 写字段 pArg2+8（nSkillRec8） ← *result
  if ( *(uint8_t *)(*result + 69) == 0 )
    *(uint32_t *)(*result + 4) = pArg2;
  result[1] = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( pArg2 == *(uint32_t *)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // 写字段 fld_e1+4（pHostObj） ← result
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // 写字段 pArg2+4（pHostObj） ← result
  }
  else
  {
    v4 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( pArg2 == *v4 )
      *v4 = result;
    else
      v4[2] = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // 写字段 pArg2+4（pHostObj） ← result
  }
  return result;
}



// ------------------------------------------------------------
// 0x4CE6B0 sub_4CE6B0
// ------------------------------------------------------------
// 调: sub_4CE6B0
int /*thiscall*/ sub_4CE6B0(uint32_t *this, uint32_t *pArg2)  // 实现：调: sub_4CE6B0
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);  // 读字段 v3 = result+8（nSkillRec8）
  if ( *(uint8_t *)(v3 + 69) == 0 )
    *(uint32_t *)(v3 + 4) = pArg2;  // 写字段 v3+4（pHostObj） ← pArg2
  *(uint32_t *)(result + 4) = pArg2[1];  // 写字段 result+4（pHostObj） ← pArg2[1]
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( pArg2 == *(uint32_t **)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // 写字段 fld_e1+4（pHostObj） ← result
    *(uint32_t *)(result + 8) = pArg2;  // 写字段 result+8（nSkillRec8） ← pArg2
    pArg2[1] = result;
  }
  else
  {
    v5 = (uint32_t *)pArg2[1];
    if ( pArg2 == (uint32_t *)v5[2] )
      v5[2] = result;
    else
      *v5 = result;
    *(uint32_t *)(result + 8) = pArg2;  // 写字段 result+8（nSkillRec8） ← pArg2
    pArg2[1] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4CE710 sub_4CE710
// ------------------------------------------------------------
// 调: sub_4CE710
uint32_t *sub_4CE710()  // 实现：调: sub_4CE710
{
  uint32_t *result; // eax

  result = operator new(0x34u);  // 堆分配
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4CE730 sub_4CE730
// ------------------------------------------------------------
// 调: sub_4CE730
uint32_t *sub_4CE730()  // 实现：调: sub_4CE730
{
  uint32_t *result; // eax

  result = operator new(0x18u);  // 堆分配
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4CE750 sub_4CE750
// ------------------------------------------------------------
// 调: sub_4CE750
uint32_t *sub_4CE750()  // 实现：调: sub_4CE750
{
  uint32_t *result; // eax

  result = operator new(0x3Cu);  // 堆分配
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4CE770 sub_4CE770
// ------------------------------------------------------------
// 调: sub_4CE770
uint32_t *sub_4CE770()  // 实现：调: sub_4CE770
{
  uint32_t *result; // eax

  result = operator new(0x28u);  // 堆分配
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4CE790 sub_4CE790
// ------------------------------------------------------------
// 调: sub_4CE790
uint32_t *sub_4CE790()  // 实现：调: sub_4CE790
{
  uint32_t *result; // eax

  result = operator new(0x48u);  // 堆分配
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 68) = 1;  // 写字段 result+68（nCharCount）
  *((uint8_t *)result + 69) = 0;  // 写字段 result[69]（宽1字节）
  return result;
}



// ------------------------------------------------------------
// 0x4CE7D0 sub_4CE7D0
// ------------------------------------------------------------
// 调: sub_4CE7D0
void /*thiscall*/ sub_4CE7D0(int this)  // 实现：调: sub_4CE7D0
{
  if ( *(uint32_t *)(this + 40) != 0 )  // this+40〔bStateSub40(推断)〕等 2 字段
    j__free(*(void **)(this + 40));  // 释放堆块
  *(uint32_t *)(this + 40) = 0;  // 写字段 this+40（bStateSub40） ← 0
  *(uint32_t *)(this + 44) = 0;  // 写字段 this+44（nExpireMs） ← 0
  *(uint32_t *)(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
  if ( *(uint32_t *)(this + 28) >= 0x10u )  // this+28〔pPanelVec(推断)〕等 2 字段
    j__free(*(void **)(this + 8));  // 释放堆块
  *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
  *(uint32_t *)(this + 28) = 15;  // 写字段 this+28（pPanelVec） ← 15
  *(uint8_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
}



// ------------------------------------------------------------
// 0x4CE820 sub_4CE820
// ------------------------------------------------------------
// 调: sub_4CE820
void /*thiscall*/ sub_4CE820(int this)  // 实现：调: sub_4CE820
{
  if ( *(uint32_t *)(this + 44) != 0 )  // this+44〔nExpireMs(推断)〕等 2 字段
    j__free(*(void **)(this + 44));  // 释放堆块
  *(uint32_t *)(this + 44) = 0;  // 写字段 this+44（nExpireMs） ← 0
  *(uint32_t *)(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
  *(uint32_t *)(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
}



// ------------------------------------------------------------
// 0x4CE850 sub_4CE850
// ------------------------------------------------------------
// 调: sub_4CE850
void /*thiscall*/ sub_4CE850(int this)  // 实现：调: sub_4CE850
{
  if ( *(uint32_t *)(this + 48) != 0 )  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    j__free(*(void **)(this + 48));  // 释放堆块
  *(uint32_t *)(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
  *(uint32_t *)(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
  *(uint32_t *)(this + 56) = 0;  // 写字段 this+56（pCmdVecCap56） ← 0
  if ( *(uint32_t *)(this + 40) >= 0x10u )  // this+40〔bStateSub40(推断)〕等 2 字段
    j__free(*(void **)(this + 20));  // 释放堆块
  *(uint32_t *)(this + 36) = 0;  // 写字段 this+36（nStateWord36） ← 0
  *(uint32_t *)(this + 40) = 15;  // 写字段 this+40（bStateSub40） ← 15
  *(uint8_t *)(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
}



// ------------------------------------------------------------
// 0x4CE8A0 sub_4CE8A0
// ------------------------------------------------------------
// 调: sub_4CE8A0 sub_442D00
int /*thiscall*/ sub_4CE8A0(uint32_t *this, int nArg2)  // sub_4CE8A0 —— 调用 sub_4CE8A0
{
  uint32_t *v3; // esi
  int v4; // eax
  int result; // eax
  int v6; // [esp+8h] [ebp-4h] BYREF

  switch ( *(this + 72) )  // 按 *(this + 72) 分派
  {
    case 0:  // case 0 分派（§C 弹尘与特效）
      v3 = &unk_9B7C3C;  // 取全局对象/数组首址（v3 ← unk_9B7C3C）
      goto LABEL_14;
    case 1:  // case 1 分派（§C 弹尘与特效）
      v3 = &unk_9B7C30;  // 取全局对象/数组首址（v3 ← unk_9B7C30）
      goto LABEL_14;
    case 2:  // case 2 分派（§C 弹尘与特效）
      v3 = &unk_9B7C48;  // 取全局对象/数组首址（v3 ← unk_9B7C48）
      goto LABEL_14;
    case 3:  // case 3 分派（§C 弹尘与特效）
      v3 = &unk_9B7C70;  // 取全局对象/数组首址（v3 ← unk_9B7C70）
      goto LABEL_14;
    case 4:  // case 4 分派（§C 弹尘与特效）
      v3 = &unk_9B6C6C;  // unk_9B6C6C —— 脚本文件列表装表
      goto LABEL_14;
    case 5:  // case 5 分派（§C 弹尘与特效）
      v3 = &unk_9B6C60;  // unk_9B6C60 —— 脚本文件列表装表
      goto LABEL_14;
    case 7:  // case 7 分派（§C 弹尘与特效）
      v3 = &unk_9B7408;  // 取全局对象/数组首址（v3 ← unk_9B7408）
      goto LABEL_14;
    case 0xA:  // case 0xA 分派（§C 弹尘与特效）
      v3 = &unk_9B71B8;  // 取全局对象/数组首址（v3 ← unk_9B71B8）
      goto LABEL_14;
    case 0xB:  // case 0xB 分派（§C 弹尘与特效）
      v3 = &unk_9B70A8;  // 取全局对象/数组首址（v3 ← unk_9B70A8）
      goto LABEL_14;
    case 0xC:  // case 0xC 分派（§C 弹尘与特效）
      v3 = &unk_9B6D78;  // 取全局对象/数组首址（v3 ← unk_9B6D78）
      goto LABEL_14;
    case 0xD:  // case 0xD 分派（§C 弹尘与特效）
      v3 = &unk_9B6E88;  // 取全局对象/数组首址（v3 ← unk_9B6E88）
      goto LABEL_14;
    case 0xE:  // case 0xE 分派（§C 弹尘与特效）
      v3 = &unk_9B7C54;  // 取全局对象/数组首址（v3 ← unk_9B7C54）
LABEL_14:
      sub_442D00(&v6, &nArg2);  // sub_442D00 —— 红黑树等键查找（_Find）
      if ( v6 == v3[1] )
        goto LABEL_20;
      v4 = *(uint32_t *)(v6 + 40) < 0x10u ? v6 + 20 : *(uint32_t *)(v6 + 20);
      if ( v4 == 0 )
        goto LABEL_20;
      result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 4))(this, v4);  // 虚调用 vt+4（this）对象赋值/迁移
      break;
    default:
LABEL_20:
      result = 0;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4CE9A0 sub_4CE9A0
// ------------------------------------------------------------
// 调: sub_4CE9A0
void /*thiscall*/ sub_4CE9A0(int this)  // 实现：调: sub_4CE9A0
{
  if ( *(uint32_t *)(this + 44) != 0 )  // this+44〔nExpireMs(推断)〕等 2 字段
    j__free(*(void **)(this + 44));  // 释放堆块
  *(uint32_t *)(this + 44) = 0;  // 写字段 this+44（nExpireMs） ← 0
  *(uint32_t *)(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
  *(uint32_t *)(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
  if ( *(uint32_t *)(this + 32) >= 0x10u )  // this+32〔nHeight(推断)〕等 2 字段
    j__free(*(void **)(this + 12));  // 释放堆块
  *(uint32_t *)(this + 28) = 0;  // 写字段 this+28（pPanelVec） ← 0
  *(uint32_t *)(this + 32) = 15;  // 写字段 this+32（nHeight） ← 15
  *(uint8_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
}



// ------------------------------------------------------------
// 0x4CE9F0 sub_4CE9F0
// ------------------------------------------------------------
// 调: sub_4CE9F0 sub_406D00
uint32_t */*thiscall*/ sub_4CE9F0(uint32_t *this)  // 实现：调: sub_4CE9F0 sub_406D00
{
  uint8_t *pThis_1; // ecx
  unsigned int fld_e6; // edx
  uint8_t *pThis_12; // edi
  void *v6[5]; // [esp+8h] [ebp-14h] BYREF

  pThis_1 = this + 1;
  *(this + 6) = 15;  // 写字段 this+6 ← 15
  *(this + 5) = 0;  // 写字段 this+5 ← 0
  v6[1] = this;
  *pThis_1 = 0;
  fld_e6 = *(this + 6);  // 读字段 fld_e6 = this+6
  v6[4] = nullptr;
  if ( fld_e6 < 0x10 )  // fld_e6=this+24 页数上限
    pThis_12 = pThis_1;
  else
    pThis_12 = *(uint8_t **)pThis_1;
  if ( fld_e6 >= 0x10 )  // fld_e6=this+24 页数上限
    pThis_1 = *(uint8_t **)pThis_1;
  sub_406D00(this, v6, (int)pThis_1, (unsigned int)&pThis_12[*(this + 5)]);  // sub_406D00 —— std::string 中段擦除（·sub_401230 erase，pos 与 n 由指针差换算）
  return this;
}



// ------------------------------------------------------------
// 0x4CEA60 sub_4CEA60
// ------------------------------------------------------------
// 调: sub_4CEA60
void /*thiscall*/ sub_4CEA60(int this)  // 实现：调: sub_4CEA60
{
  if ( *(uint32_t *)(this + 56) != 0 )  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    j__free(*(void **)(this + 56));  // 释放堆块
  *(uint32_t *)(this + 56) = 0;  // 写字段 this+56（pCmdVecCap56） ← 0
  *(uint32_t *)(this + 60) = 0;  // 写字段 this+60（nFadeValue60） ← 0
  *(uint32_t *)(this + 64) = 0;  // 写字段 this+64（apServerTabBtn） ← 0
  if ( *(uint32_t *)(this + 44) >= 0x10u )  // this+44〔nExpireMs(推断)〕等 2 字段
    j__free(*(void **)(this + 24));  // 释放堆块
  *(uint32_t *)(this + 40) = 0;  // 写字段 this+40（bStateSub40） ← 0
  *(uint32_t *)(this + 44) = 15;  // 写字段 this+44（nExpireMs） ← 15
  *(uint8_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
}



// ------------------------------------------------------------
// 0x4CEAB0 sub_4CEAB0
// ------------------------------------------------------------
// 调: sub_4CEAB0 sub_4015C0 sub_401740
void /*noreturn*/ sub_4CEAB0()  // 实现：调: sub_4CEAB0 sub_4015C0 sub_401740
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
  sub_401740(pExceptionObject, &v1);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject[0] = &std::length_error::`vftable';  // vftable 复位
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
}



// ------------------------------------------------------------
// 0x4CEB20 sub_4CEB20
// ------------------------------------------------------------
// 调: sub_4CEB20
void /*thiscall*/ sub_4CEB20(int this)  // 实现：调: sub_4CEB20
{
  if ( *(uint32_t *)(this + 40) != 0 )  // this+40〔bStateSub40(推断)〕等 2 字段
    j__free(*(void **)(this + 40));  // 释放堆块
  *(uint32_t *)(this + 40) = 0;  // 写字段 this+40（bStateSub40） ← 0
  *(uint32_t *)(this + 44) = 0;  // 写字段 this+44（nExpireMs） ← 0
  *(uint32_t *)(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
}



// ------------------------------------------------------------
// 0x4CEB50 sub_4CEB50
// ------------------------------------------------------------
// 调: sub_4CEB50
void /*thiscall*/ sub_4CEB50(int this)  // sub_4CEB50 —— 成员清理
{
  if ( *(uint32_t *)(this + 20) != 0 )  // this+20〔nPage(推断)〕等 2 字段
    j__free(*(void **)(this + 20));  // 释放堆块
  *(uint32_t *)(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
  *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
  *(uint32_t *)(this + 28) = 0;  // 写字段 this+28（pPanelVec） ← 0
}



// ------------------------------------------------------------
// 0x4CEB80 sub_4CEB80
// ------------------------------------------------------------
// 调: sub_4CEB80 sub_4015C0
void /*thiscall*/ sub_4CEB80(char *this)  // 实现：调: sub_4CEB80 sub_4015C0
{
  char *pThis_44; // edi
  uint32_t *pThis_1B0; // edx
  uint32_t *pThis_E4; // eax
  uint32_t *v5; // ecx
  int k; // edi
  uint32_t *pThis_E42; // ecx
  int m; // edi
  char *pThis_270; // edi
  void **pThis_C7; // edi
  void **pThis_CB; // edi
  void **pThis_D6; // edi
  void **pThis_DA; // edi
  char *pThis_3C0; // eax
  void **v15; // edi
  void **v16; // [esp+8h] [ebp-Ch]
  void **ii; // [esp+Ch] [ebp-8h]
  void **jj; // [esp+Ch] [ebp-8h]
  void **kk; // [esp+Ch] [ebp-8h]
  void **mm; // [esp+Ch] [ebp-8h]
  int nn; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]
  int j; // [esp+10h] [ebp-4h]
  int n; // [esp+10h] [ebp-4h]
  char *pThis_3C02; // [esp+10h] [ebp-4h]

  *(uint32_t *)this = 0;  // *this = 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 9) = 0;  // 写字段 this[9]（宽4字节）
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 11) = 1;  // 写字段 this[11]（宽4字节）
  if ( *((uint32_t *)this + 13) != 0 )  // this+52〔bAuraState(推断)〕
    j__free(*((void **)this + 13));  // 释放堆块
  *((uint32_t *)this + 13) = 0;  // 写字段 this[13]（宽4字节）
  *((uint32_t *)this + 14) = 0;  // 写字段 this[14]（宽4字节）
  *((uint32_t *)this + 15) = 0;  // 写字段 this[15]（宽4字节）
  pThis_44 = this + 68;  // this+68 角色数（begin/end 差 >>2；>=8 …
  for ( i = 4; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    if ( *(uint32_t *)pThis_44 != 0 )  // pThis_44=this+68 角色数（begin/end 差 >>2；>=8 …
      j__free(*(void **)pThis_44);  // 释放堆块
    *(uint32_t *)pThis_44 = 0;  // *pThis_44 = 0
    *((uint32_t *)pThis_44 + 1) = 0;  // 写字段 pThis_44[1]（宽4字节）
    *((uint32_t *)pThis_44 + 2) = 0;  // 写字段 pThis_44[2]（宽4字节）
    pThis_44 += 16;  // pThis_44=this+68 角色数（begin/end 差 >>2；>=8 …
  }
  if ( *((uint32_t *)this + 33) != 0 )  // this+132〔nAgeTicks〕
    j__free(*((void **)this + 33));  // 释放堆块
  *((uint32_t *)this + 33) = 0;  // 写字段 this+33（bJobVecDirty）
  *((uint32_t *)this + 34) = 0;  // 写字段 this[34]（宽4字节）
  *((uint32_t *)this + 35) = 0;  // 写字段 this[35]（宽4字节）
  *((uint32_t *)this + 36) = 0;  // 写字段 this+36（nStateWord36）
  *((uint32_t *)this + 37) = 0;  // 写字段 this+37（bFadeFlag37）
  *((uint32_t *)this + 38) = 0;  // 写字段 this+38（bFadeFlag38）
  *((uint32_t *)this + 39) = 0;  // 写字段 this[39]（宽4字节）
  *((uint32_t *)this + 40) = 0;  // 写字段 this+40（bStateSub40）
  *((uint32_t *)this + 41) = 0;  // 写字段 this[41]（宽4字节）
  *((uint32_t *)this + 42) = 0;  // 写字段 this[42]（宽4字节）
  *((uint32_t *)this + 43) = 0;  // 写字段 this[43]（宽4字节）
  *((uint32_t *)this + 44) = 0;  // 写字段 this+44（nExpireMs）
  *((uint32_t *)this + 45) = 0;  // 写字段 this[45]（宽4字节）
  *((uint32_t *)this + 46) = 0;  // 写字段 this[46]（宽4字节）
  pThis_1B0 = this + 432;
  pThis_E4 = this + 228;  // this+228 快照副本 C
  for ( j = 2; j != 0; --j )  // 遍历计次循环（j != 0）
  {
    v5 = pThis_E4 - 8;  // 计算 v5 = pThis_E4 - 8
    for ( k = 4; k != 0; --k )  // 遍历计次循环（k != 0）
    {
      *v5 = 0;
      v5 += 2;
    }
    pThis_E42 = pThis_E4;  // pThis_E4=this+228 快照副本 C
    for ( m = 16; m != 0; --m )  // 遍历计次循环（m != 0）
    {
      *pThis_E42 = 0;
      pThis_E42 += 2;
    }
    pThis_E4[32] = 0;  // pThis_E4=this+228 快照副本 C
    pThis_E4[34] = 0;  // pThis_E4=this+228 快照副本 C
    pThis_E4[36] = 0;  // pThis_E4=this+228 快照副本 C
    pThis_E4[38] = 0;  // pThis_E4=this+228 快照副本 C
    pThis_E4[40] = 0;  // pThis_E4=this+228 快照副本 C
    pThis_E4[42] = 0;  // pThis_E4=this+228 快照副本 C
    pThis_E4[44] = 0;  // pThis_E4=this+228 快照副本 C
    pThis_E4[46] = 100;  // pThis_E4=this+228 快照副本 C
    pThis_E4[48] = 0;  // pThis_E4=this+228 快照副本 C
    *(pThis_1B0 - 1) = 0;
    *pThis_1B0 = 0;
    ++pThis_E4;  // 计数自增 pThis_E4
    pThis_1B0 += 2;
  }
  *((uint32_t *)this + 111) = 200;  // 写字段 this[111]（宽4字节）
  *((uint32_t *)this + 112) = 1000;  // 写字段 this+112（pHostComp）
  *(this + 452) = 0;  // 写字段 this+452（nAtkRollVal） ← 0
  *(this + 453) = 0;  // 写字段 this+453 ← 0
  *((uint32_t *)this + 114) = 0;  // 写字段 this[114]（宽4字节）
  *((uint32_t *)this + 115) = 0;  // 写字段 this[115]（宽4字节）
  *((uint32_t *)this + 116) = 0;  // 写字段 this+116（pSessionCtx）
  *(this + 468) = 0;  // 写字段 this+468 ← 0
  *(this + 469) = 0;  // 写字段 this+469 ← 0
  *(this + 470) = 0;  // 写字段 this+470 ← 0
  *((uint32_t *)this + 118) = 0;  // 写字段 this[118]（宽4字节）
  *((uint32_t *)this + 119) = 0;  // 写字段 this[119]（宽4字节）
  *((uint32_t *)this + 120) = 0;  // 写字段 this+120（pAnimObj）
  *((uint32_t *)this + 121) = 0;  // 写字段 this[121]（宽4字节）
  *(this + 488) = 0;  // 写字段 this+488 ← 0
  *((uint32_t *)this + 123) = 50;  // 写字段 this[123]（宽4字节）
  *((uint32_t *)this + 124) = 1000;  // 写字段 this+124（pAuraAnim）
  *(this + 500) = 0;  // 写字段 this+500 ← 0
  *((uint32_t *)this + 126) = 0;  // 写字段 this+126（field_007E）
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 134) = 0;  // 写字段 this[134]（宽4字节）
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_270 = this + 624;
  for ( n = 2; n != 0; --n )  // 遍历计次循环（n != 0）
  {
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pThis_270 += 28;
  }
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_C7 = *((void ***)this + 199);
  if ( pThis_C7 != nullptr )
  {
    for ( ii = *((void ***)this + 200); pThis_C7 != ii; ++pThis_C7 )  // this+200 主状态（0x5DE690: dword_8F7C…
      sub_41B010(pThis_C7);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 199));  // 释放堆块
  }
  *((uint32_t *)this + 199) = 0;  // 写字段 this[199]（宽4字节）
  *((uint32_t *)this + 200) = 0;  // 写字段 this+200（field_00C8）
  *((uint32_t *)this + 201) = 0;  // 写字段 this[201]（宽4字节）
  pThis_CB = *((void ***)this + 203);
  if ( pThis_CB != nullptr )
  {
    for ( jj = *((void ***)this + 204); pThis_CB != jj; ++pThis_CB )  // this+204 子动画链指针
      sub_41B010(pThis_CB);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 203));  // 释放堆块
  }
  *((uint32_t *)this + 203) = 0;  // 写字段 this[203]（宽4字节）
  *((uint32_t *)this + 204) = 0;  // 写字段 this+204（pSubAnim204）
  *((uint32_t *)this + 205) = 0;  // 写字段 this[205]（宽4字节）
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_D6 = *((void ***)this + 214);
  if ( pThis_D6 != nullptr )
  {
    for ( kk = *((void ***)this + 215); pThis_D6 != kk; ++pThis_D6 )
      sub_41B010(pThis_D6);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 214));  // 释放堆块
  }
  *((uint32_t *)this + 214) = 0;  // 写字段 this[214]（宽4字节）
  *((uint32_t *)this + 215) = 0;  // 写字段 this[215]（宽4字节）
  *((uint32_t *)this + 216) = 0;  // 写字段 this+216（bField216）
  pThis_DA = *((void ***)this + 218);
  if ( pThis_DA != nullptr )
  {
    for ( mm = *((void ***)this + 219); pThis_DA != mm; ++pThis_DA )
      sub_41B010(pThis_DA);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 218));  // 释放堆块
  }
  *((uint32_t *)this + 218) = 0;  // 写字段 this[218]（宽4字节）
  *((uint32_t *)this + 219) = 0;  // 写字段 this[219]（宽4字节）
  *((uint32_t *)this + 220) = 0;  // 写字段 this+220（nSnapDst220）
  if ( *((uint32_t *)this + 222) != 0 )
    j__free(*((void **)this + 222));  // 释放堆块
  *((uint32_t *)this + 222) = 0;  // 写字段 this[222]（宽4字节）
  *((uint32_t *)this + 223) = 0;  // 写字段 this[223]（宽4字节）
  *((uint32_t *)this + 224) = 0;  // 写字段 this+224（nSnapDst224）
  if ( *((uint32_t *)this + 226) != 0 )
    j__free(*((void **)this + 226));  // 释放堆块
  *((uint32_t *)this + 226) = 0;  // 写字段 this[226]（宽4字节）
  *((uint32_t *)this + 227) = 0;  // 写字段 this[227]（宽4字节）
  *((uint32_t *)this + 228) = 0;  // 写字段 this+228（nSnapDst228）
  *((uint32_t *)this + 229) = -1;  // 写字段 this[229]（宽4字节）
  *((uint32_t *)this + 230) = 0;  // 写字段 this[230]（宽4字节）
  *((uint32_t *)this + 231) = 0;  // 写字段 this[231]（宽4字节）
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_3C0 = this + 960;  // this+960 大状态镜像/状态槽
  pThis_3C02 = this + 960;  // this+960 大状态镜像/状态槽
  for ( nn = 29; nn != 0; --nn )  // 遍历计次循环（nn != 0）
  {
    v15 = *(void ***)pThis_3C0;  // pThis_3C0=this+960 大状态镜像/状态槽
    if ( *(uint32_t *)pThis_3C0 != 0 )  // pThis_3C0=this+960 大状态镜像/状态槽
    {
      v16 = *((void ***)pThis_3C0 + 1);  // pThis_3C0=this+960 大状态镜像/状态槽
      if ( v15 != v16 )
      {
        do
          sub_41B010(v15++);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
        while ( v15 != v16 );  // 循环直到 v15 != v16
        pThis_3C0 = pThis_3C02;  // pThis_3C0=this+960 大状态镜像/状态槽
      }
      j__free(*(void **)pThis_3C0);  // 释放堆块
      pThis_3C0 = pThis_3C02;  // pThis_3C0=this+960 大状态镜像/状态槽
    }
    *(uint32_t *)pThis_3C0 = 0;  // *pThis_3C0 = 0
    *((uint32_t *)pThis_3C0 + 1) = 0;  // 写字段 pThis_3C0[1]（宽4字节）
    *((uint32_t *)pThis_3C0 + 2) = 0;  // 写字段 pThis_3C0[2]（宽4字节）
    pThis_3C0 += 16;  // pThis_3C0=this+960 大状态镜像/状态槽
    pThis_3C02 = pThis_3C0;  // pThis_3C02=this+960 大状态镜像/状态槽
  }
  if ( *((uint32_t *)this + 356) != 0 )
    j__free(*((void **)this + 356));  // 释放堆块
  *((uint32_t *)this + 356) = 0;  // 写字段 this[356]（宽4字节）
  *((uint32_t *)this + 357) = 0;  // 写字段 this[357]（宽4字节）
  *((uint32_t *)this + 358) = 0;  // 写字段 this[358]（宽4字节）
  *((uint32_t *)this + 359) = 0;  // 写字段 this[359]（宽4字节）
}


// ------------------------------------------------------------
// 0x4CF050 sub_4CF050
// ------------------------------------------------------------
// 调: sub_4CF050 sub_4015C0 sub_4017E0
size_t */*thiscall*/ sub_4CF050(void *this)  // 实现：调: sub_4CF050 sub_4015C0 sub_4017E0
{
  *(uint32_t *)this = 0;  // *this = 0
  sub_4015C0((size_t *)this + 1, szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 9) = 0;  // 写字段 this[9]（宽4字节）
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 11) = 1;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  *((uint32_t *)this + 13) = 0;  // 写字段 this[13]（宽4字节）
  if ( *((uint32_t *)this + 15) != 0 )  // this+60〔nFadeValue60(推断)〕
    j__free(*((void **)this + 15));  // 释放堆块
  *((uint32_t *)this + 15) = 0;  // 写字段 this[15]（宽4字节）
  *((uint32_t *)this + 16) = 0;  // 写字段 this+16（nChannelTypeSel）
  *((uint32_t *)this + 17) = 0;  // 写字段 this+17（bEnable）
  sub_4015C0((size_t *)this + 18, szPassword, 0);  // 【std::string构造赋值】
  sub_4017E0((int)this + 100);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  sub_4015C0((size_t *)this + 29, szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 36, szPassword, 0);  // 【std::string构造赋值】
  sub_4017E0((int)this + 172);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *((uint32_t *)this + 48) != 0 )  // this+192〔nDlgId(推断)〕
    j__free(*((void **)this + 48));  // 释放堆块
  *((uint32_t *)this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48）
  *((uint32_t *)this + 49) = 0;  // 写字段 this+49（bUdpReported）
  *((uint32_t *)this + 50) = 0;  // 写字段 this+50（bCharSelSent）
  sub_4017E0((int)this + 204);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  return sub_4015C0((size_t *)this + 55, szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x4CF120 sub_4CF120
// ------------------------------------------------------------
// 调: sub_4CF120 sub_4015C0 sub_41B010
size_t */*thiscall*/ sub_4CF120(char *this)  // 实现：调: sub_4CF120 sub_4015C0 sub_41B010
{
  uint32_t *pThis_40; // eax
  int i; // ecx
  void **pThis_1C; // edi
  void **pThis_20; // edi
  void **pThis_28; // edi
  void **j; // [esp+Ch] [ebp-4h]
  void **k; // [esp+Ch] [ebp-4h]
  void **m; // [esp+Ch] [ebp-4h]

  *(uint32_t *)this = 0;  // *this = 0
  sub_4015C0((size_t *)this + 1, szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 11) = 1;  // 写字段 this[11]（宽4字节）
  *(this + 52) = 1;  // 写字段 this+52（bAuraState） ← 1
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 9) = 0;  // 写字段 this[9]（宽4字节）
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  pThis_40 = this + 64;  // this+64 服务器页签按钮组 6 个
  for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    *(pThis_40 - 2) = 0;  // pThis_40=this+64 服务器页签按钮组 6 个
    *pThis_40++ = 0;  // pThis_40=this+64 服务器页签按钮组 6 个
  }
  *((uint32_t *)this + 18) = 0;  // 写字段 this+18（bDragChild）
  sub_4015C0((size_t *)this + 20, szPassword, 0);  // 【std::string构造赋值】
  pThis_1C = *((void ***)this + 28);  // this+28 逐帧驱动对象
  if ( pThis_1C != nullptr )  // pThis_1C=this+112 第 1 组·宿主属性 +46 增量子倍率
  {
    for ( j = *((void ***)this + 29); pThis_1C != j; ++pThis_1C )  // this+29 pSessionCtx
      sub_41B010(pThis_1C);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 28));  // 释放堆块
  }
  *((uint32_t *)this + 28) = 0;  // 写字段 this+28（pPanelVec）
  *((uint32_t *)this + 29) = 0;  // 写字段 this[29]（宽4字节）
  *((uint32_t *)this + 30) = 0;  // 写字段 this[30]（宽4字节）
  pThis_20 = *((void ***)this + 32);  // this+32 格子像素尺寸
  if ( pThis_20 != nullptr )  // pThis_20=this+128 第 2 组·+1208 增量子倍率
  {
    for ( k = *((void ***)this + 33); pThis_20 != k; ++pThis_20 )  // this+33〔bJobVecDirty〕
      sub_41B010(pThis_20);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 32));  // 释放堆块
  }
  *((uint32_t *)this + 32) = 0;  // 写字段 this+32（nHeight）
  *((uint32_t *)this + 33) = 0;  // 写字段 this+33（bJobVecDirty）
  *((uint32_t *)this + 34) = 0;  // 写字段 this[34]（宽4字节）
  if ( *((uint32_t *)this + 36) != 0 )  // this+144〔pFrameList144(推断)〕
    j__free(*((void **)this + 36));  // 释放堆块
  *((uint32_t *)this + 36) = 0;  // 写字段 this+36（nStateWord36）
  *((uint32_t *)this + 37) = 0;  // 写字段 this+37（bFadeFlag37）
  *((uint32_t *)this + 38) = 0;  // 写字段 this+38（bFadeFlag38）
  pThis_28 = *((void ***)this + 40);  // this+40 物品状态附属标志
  if ( pThis_28 != nullptr )  // pThis_28=this+160 第 5 组·+1040 增量子倍率
  {
    for ( m = *((void ***)this + 41); pThis_28 != m; ++pThis_28 )  // pThis_28=this+160 第 5 组·+1040 增量子倍率
      sub_41B010(pThis_28);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 40));  // 释放堆块
  }
  *((uint32_t *)this + 40) = 0;  // 写字段 this+40（bStateSub40）
  *((uint32_t *)this + 41) = 0;  // 写字段 this[41]（宽4字节）
  *((uint32_t *)this + 42) = 0;  // 写字段 this[42]（宽4字节）
  return sub_4015C0((size_t *)this + 43, szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x4CF290 sub_4CF290
// ------------------------------------------------------------
// 调: sub_4CF290 sub_4015C0 sub_41B010
size_t */*thiscall*/ sub_4CF290(char *this)  // 实现：调: sub_4CF290 sub_4015C0 sub_41B010
{
  uint32_t *pThis_44; // eax
  int i; // ecx
  void **pThis_442; // edi
  void **pThis_48; // edi
  void **pThis_50; // edi
  void **j; // [esp+Ch] [ebp-4h]
  void **k; // [esp+Ch] [ebp-4h]
  void **m; // [esp+Ch] [ebp-4h]

  *(uint32_t *)this = 0;  // *this = 0
  sub_4015C0((size_t *)this + 1, szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 9) = 0;  // 写字段 this[9]（宽4字节）
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 11) = 1;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  *((uint32_t *)this + 13) = 0;  // 写字段 this[13]（宽4字节）
  *(this + 56) = 1;  // 写字段 this+56（pCmdVecCap56） ← 1
  pThis_44 = this + 68;  // this+68 角色数（begin/end 差 >>2；>=8 …
  for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    *(pThis_44 - 2) = 0;  // pThis_44=this+68 角色数（begin/end 差 >>2；>=8 …
    *pThis_44++ = 0;  // pThis_44=this+68 角色数（begin/end 差 >>2；>=8 …
  }
  *((uint32_t *)this + 19) = 0;  // 写字段 this[19]（宽4字节）
  *((uint32_t *)this + 20) = 1500;  // 写字段 this+20（nPage）
  *((uint32_t *)this + 21) = 1;  // 写字段 this+21（bArmorState）
  *((uint32_t *)this + 22) = 1;  // 写字段 this[22]（宽4字节）
  *((uint32_t *)this + 23) = 0;  // 写字段 this[23]（宽4字节）
  *((uint32_t *)this + 24) = 1;  // 写字段 this+24（nPageMax）
  sub_4015C0((size_t *)this + 25, szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 32, szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 39, szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 46, szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 53, szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 60, szPassword, 0);  // 【std::string构造赋值】
  pThis_442 = *((void ***)this + 68);  // this+68 角色数（begin/end 差 >>2；>=8 …
  if ( pThis_442 != nullptr )
  {
    for ( j = *((void ***)this + 69); pThis_442 != j; ++pThis_442 )
      sub_41B010(pThis_442);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 68));  // 释放堆块
  }
  *((uint32_t *)this + 68) = 0;  // 写字段 this+68（nCharCount）
  *((uint32_t *)this + 69) = 0;  // 写字段 this[69]（宽4字节）
  *((uint32_t *)this + 70) = 0;  // 写字段 this[70]（宽4字节）
  pThis_48 = *((void ***)this + 72);  // this+72 快照槽（0x6491A0：*(this+72) …
  if ( pThis_48 != nullptr )  // pThis_48=this+288 主人绑定对象
  {
    for ( k = *((void ***)this + 73); pThis_48 != k; ++pThis_48 )  // this+73 基类名字缓冲 SSO 首字节
      sub_41B010(pThis_48);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 72));  // 释放堆块
  }
  *((uint32_t *)this + 72) = 0;  // 写字段 this+72（nSnapshot72）
  *((uint32_t *)this + 73) = 0;  // 写字段 this+73（szDigitalName）
  *((uint32_t *)this + 74) = 0;  // 写字段 this+74（field_004A）
  if ( *((uint32_t *)this + 76) != 0 )  // this+304〔pLayer304(推断)〕
    j__free(*((void **)this + 76));  // 释放堆块
  *((uint32_t *)this + 76) = 0;  // 写字段 this+76（szEmblemPath）
  *((uint32_t *)this + 77) = 0;  // 写字段 this+77（bGuildFlagB）
  *((uint32_t *)this + 78) = 0;  // 写字段 this+78（bGuildFlagC）
  pThis_50 = *((void ***)this + 80);  // this+80 关联角色对象
  if ( pThis_50 != nullptr )
  {
    for ( m = *((void ***)this + 81); pThis_50 != m; ++pThis_50 )  // this+81 高度提交槽
      sub_41B010(pThis_50);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 80));  // 释放堆块
  }
  *((uint32_t *)this + 80) = 0;  // 写字段 this+80（nAuraStage）
  *((uint32_t *)this + 81) = 0;  // 写字段 this[81]（宽4字节）
  *((uint32_t *)this + 82) = 0;  // 写字段 this[82]（宽4字节）
  return sub_4015C0((size_t *)this + 83, szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x4CF480 sub_4CF480
// ------------------------------------------------------------
// 调: sub_4CF480 sub_41BFE0 sub_41B010
void /*thiscall*/ sub_4CF480(void *this)  // 实现：调: sub_4CF480 sub_41BFE0 sub_41B010
{
  void **pThis_23; // eax
  void **pThis_232; // edi
  void **pThis_24; // [esp+Ch] [ebp-4h]

  *(uint32_t *)this = 0;  // *this = 0
  sub_41BFE0((void **)this + 1, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  sub_41BFE0((void **)this + 2, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  sub_41BFE0((void **)this + 3, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  sub_41BFE0((void **)this + 4, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 5) = 0;  // 写字段 this[5]（宽4字节）
  *((uint32_t *)this + 6) = 0;  // 写字段 this[6]（宽4字节）
  *((uint32_t *)this + 7) = 0;  // 写字段 this+7（uPathTerm）
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 9) = 0;  // 写字段 this[9]（宽4字节）
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 11) = 0;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  *((uint32_t *)this + 13) = -1;  // 写字段 this[13]（宽4字节）
  *((uint32_t *)this + 14) = 0;  // 写字段 this[14]（宽4字节）
  *((uint32_t *)this + 15) = 0;  // 写字段 this[15]（宽4字节）
  *((uint32_t *)this + 16) = 0;  // 写字段 this+16（nChannelTypeSel）
  *((uint32_t *)this + 17) = 0;  // 写字段 this+17（bEnable）
  *((uint32_t *)this + 18) = -1;  // 写字段 this+18（bDragChild）
  *((uint8_t *)this + 76) = 0;  // 写字段 this+76（szEmblemPath）
  sub_41BFE0((void **)this + 20, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 21) = 0;  // 写字段 this+21（bArmorState）
  sub_41BFE0((void **)this + 22, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 23) = 0;  // 写字段 this[23]（宽4字节）
  *((uint32_t *)this + 24) = 0;  // 写字段 this+24（nPageMax）
  *((uint32_t *)this + 25) = 8;  // 写字段 this[25]（宽4字节）
  sub_41BFE0((void **)this + 26, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  sub_41BFE0((void **)this + 29, szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  if ( *((uint32_t *)this + 31) != 0 )  // this+124〔pAuraAnim(推断)〕
    j__free(*((void **)this + 31));  // 释放堆块
  *((uint32_t *)this + 31) = 0;  // 写字段 this[31]（宽4字节）
  *((uint32_t *)this + 32) = 0;  // 写字段 this+32（nHeight）
  *((uint32_t *)this + 33) = 0;  // 写字段 this+33（bJobVecDirty）
  pThis_23 = *((void ***)this + 35);  // pThis_23=this+140 第 3 组·+900 增量
  if ( pThis_23 != nullptr )  // pThis_23=this+140 第 3 组·+900 增量
  {
    pThis_232 = *((void ***)this + 35);  // pThis_232=this+140 第 3 组·+900 增量
    pThis_24 = *((void ***)this + 36);  // this+36 物品状态字
    if ( pThis_23 != pThis_24 )  // pThis_23=this+140 第 3 组·+900 增量
    {
      do
        sub_41B010(pThis_232++);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
      while ( pThis_232 != pThis_24 );  // 循环直到 pThis_232 != pThis_24
    }
    j__free(*((void **)this + 35));  // 释放堆块
  }
  *((uint32_t *)this + 35) = 0;  // 写字段 this[35]（宽4字节）
  *((uint32_t *)this + 36) = 0;  // 写字段 this+36（nStateWord36）
  *((uint32_t *)this + 37) = 0;  // 写字段 this+37（bFadeFlag37）
  *((uint32_t *)this + 40) = -1;  // 写字段 this+40（bStateSub40）
  *((uint8_t *)this + 152) = 0;  // 写字段 this+152（nAdd152）
  *((uint32_t *)this + 39) = 0;  // 写字段 this[39]（宽4字节）
}



// ------------------------------------------------------------
// 0x4CF5C0 sub_4CF5C0
// ------------------------------------------------------------
// 调: sub_4CF5C0 sub_401940 sub_4017E0 sub_501490 sub_5E5260
void /*thiscall*/ sub_4CF5C0(int this)  // 实现：调: sub_4CF5C0 sub_401940 sub_4017E0 sub_501490 sub_5E5260
{
  void *fld_590; // eax

  fld_590 = *(void **)(this + 1424);
  if ( fld_590 != nullptr )
    j__free(fld_590);  // 释放堆块
  *(uint32_t *)(this + 1424) = 0;  // 写字段 this+1424 ← 0
  *(uint32_t *)(this + 1428) = 0;  // 写字段 this+1428 ← 0
  *(uint32_t *)(this + 1432) = 0;  // 写字段 this+1432（bTriggerLatch1432） ← 0
  `eh vector destructor iterator'((void *)(this + 956), 0x10u, 29, sub_401940);  // 调 : 转发 ·sub_4017E0
  if ( *(uint32_t *)(this + 952) >= 0x10u )
    j__free(*(void **)(this + 932));  // 释放堆块
  *(uint32_t *)(this + 952) = 15;  // 写字段 this+952 ← 15
  *(uint32_t *)(this + 948) = 0;  // 写字段 this+948 ← 0
  *(uint8_t *)(this + 932) = 0;  // 写字段 this+932 ← 0
  if ( *(uint32_t *)(this + 904) != 0 )
    j__free(*(void **)(this + 904));  // 释放堆块
  *(uint32_t *)(this + 904) = 0;  // 写字段 this+904 ← 0
  *(uint32_t *)(this + 908) = 0;  // 写字段 this+908 ← 0
  *(uint32_t *)(this + 912) = 0;  // 写字段 this+912 ← 0
  if ( *(uint32_t *)(this + 888) != 0 )
    j__free(*(void **)(this + 888));  // 释放堆块
  *(uint32_t *)(this + 888) = 0;  // 写字段 this+888 ← 0
  *(uint32_t *)(this + 892) = 0;  // 写字段 this+892 ← 0
  *(uint32_t *)(this + 896) = 0;  // 写字段 this+896 ← 0
  sub_4017E0(this + 868);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  sub_4017E0(this + 852);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 848) >= 0x10u )
    j__free(*(void **)(this + 828));  // 释放堆块
  *(uint32_t *)(this + 848) = 15;  // 写字段 this+848 ← 15
  *(uint32_t *)(this + 844) = 0;  // 写字段 this+844 ← 0
  *(uint8_t *)(this + 828) = 0;  // 写字段 this+828 ← 0
  sub_4017E0(this + 808);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  sub_4017E0(this + 792);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 788) >= 0x10u )
    j__free(*(void **)(this + 768));  // 释放堆块
  *(uint32_t *)(this + 788) = 15;  // 写字段 this+788 ← 15
  *(uint32_t *)(this + 784) = 0;  // 写字段 this+784 ← 0
  *(uint8_t *)(this + 768) = 0;  // 写字段 this+768 ← 0
  if ( *(uint32_t *)(this + 760) >= 0x10u )  // this+760〔fVal760(推断)〕
    j__free(*(void **)(this + 740));  // 释放堆块
  *(uint32_t *)(this + 760) = 15;  // 写字段 this+760（fVal760） ← 15
  *(uint32_t *)(this + 756) = 0;  // 写字段 this+756 ← 0
  *(uint8_t *)(this + 740) = 0;  // 写字段 this+740 ← 0
  if ( *(uint32_t *)(this + 732) >= 0x10u )
    j__free(*(void **)(this + 712));  // 释放堆块
  *(uint32_t *)(this + 732) = 15;  // 写字段 this+732 ← 15
  *(uint32_t *)(this + 728) = 0;  // 写字段 this+728 ← 0
  *(uint8_t *)(this + 712) = 0;  // 写字段 this+712（pResTbl712） ← 0
  if ( *(uint32_t *)(this + 704) >= 0x10u )  // this+704〔nSnapshot704〕
    j__free(*(void **)(this + 684));  // 释放堆块
  *(uint32_t *)(this + 704) = 15;  // 写字段 this+704（nSnapshot704） ← 15
  *(uint32_t *)(this + 700) = 0;  // 写字段 this+700（bSnapshot700） ← 0
  *(uint8_t *)(this + 684) = 0;  // 写字段 this+684（nSnapshot684） ← 0
  `eh vector destructor iterator'((void *)(this + 624), 0x1Cu, 2, sub_501490);  // 调 对象析构后释放堆块
  if ( *(uint32_t *)(this + 620) >= 0x10u )
    j__free(*(void **)(this + 600));  // 释放堆块
  *(uint32_t *)(this + 620) = 15;  // 写字段 this+620 ← 15
  *(uint32_t *)(this + 616) = 0;  // 写字段 this+616（nReactionState） ← 0
  *(uint8_t *)(this + 600) = 0;  // 写字段 this+600 ← 0
  if ( *(uint32_t *)(this + 592) >= 0x10u )
    j__free(*(void **)(this + 572));  // 释放堆块
  *(uint32_t *)(this + 592) = 15;  // 写字段 this+592 ← 15
  *(uint32_t *)(this + 588) = 0;  // 写字段 this+588 ← 0
  *(uint8_t *)(this + 572) = 0;  // 写字段 this+572 ← 0
  if ( *(uint32_t *)(this + 564) >= 0x10u )
    j__free(*(void **)(this + 544));  // 释放堆块
  *(uint32_t *)(this + 564) = 15;  // 写字段 this+564 ← 15
  *(uint32_t *)(this + 560) = 0;  // 写字段 this+560 ← 0
  *(uint8_t *)(this + 544) = 0;  // 写字段 this+544（pEqVec544） ← 0
  if ( *(uint32_t *)(this + 532) >= 0x10u )
    j__free(*(void **)(this + 512));  // 释放堆块
  *(uint32_t *)(this + 532) = 15;  // 写字段 this+532 ← 15
  *(uint32_t *)(this + 528) = 0;  // 写字段 this+528 ← 0
  *(uint8_t *)(this + 512) = 0;  // 写字段 this+512（nAbilityId） ← 0
  if ( *(uint32_t *)(this + 132) != 0 )  // this+132〔nAgeTicks〕
    j__free(*(void **)(this + 132));  // 释放堆块
  *(uint32_t *)(this + 132) = 0;  // 写字段 this+132（nAdd132） ← 0
  *(uint32_t *)(this + 136) = 0;  // 写字段 this+136（nCtx136） ← 0
  *(uint32_t *)(this + 140) = 0;  // 写字段 this+140（nAdd140） ← 0
  `eh vector destructor iterator'((void *)(this + 64), 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
  if ( *(uint32_t *)(this + 52) != 0 )  // this+52〔bAuraState(推断)〕等 2 字段
    j__free(*(void **)(this + 52));  // 释放堆块
  *(uint32_t *)(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
  *(uint32_t *)(this + 56) = 0;  // 写字段 this+56（pCmdVecCap56） ← 0
  *(uint32_t *)(this + 60) = 0;  // 写字段 this+60（nFadeValue60） ← 0
  if ( *(uint32_t *)(this + 28) >= 0x10u )  // this+28〔pPanelVec(推断)〕等 2 字段
    j__free(*(void **)(this + 8));  // 释放堆块
  *(uint32_t *)(this + 28) = 15;  // 写字段 this+28（pPanelVec） ← 15
  *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
  *(uint8_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
}



// ------------------------------------------------------------
// 0x4CF8F0 sub_4CF8F0
// ------------------------------------------------------------
// 调: sub_4CF8F0 sub_4017E0
void /*thiscall*/ sub_4CF8F0(int this)  // 实现：调: sub_4CF8F0 sub_4017E0
{
  if ( *(uint32_t *)(this + 244) >= 0x10u )  // this+244〔fSyncTime〕
    j__free(*(void **)(this + 224));  // 释放堆块
  *(uint32_t *)(this + 244) = 15;  // 写字段 this+244（fSyncValue） ← 15
  *(uint32_t *)(this + 240) = 0;  // 写字段 this+240（nSyncArgB） ← 0
  *(uint8_t *)(this + 224) = 0;  // 写字段 this+224（nSnapDst224） ← 0
  sub_4017E0(this + 204);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 192) != 0 )  // this+192〔nDlgId(推断)〕
    j__free(*(void **)(this + 192));  // 释放堆块
  *(uint32_t *)(this + 192) = 0;  // 写字段 this+192（nDlgId） ← 0
  *(uint32_t *)(this + 196) = 0;  // 写字段 this+196 ← 0
  *(uint32_t *)(this + 200) = 0;  // 写字段 this+200（field_00C8） ← 0
  sub_4017E0(this + 172);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 168) >= 0x10u )  // this+168〔pAppendVec(推断)〕等 2 字段
    j__free(*(void **)(this + 148));  // 释放堆块
  *(uint32_t *)(this + 168) = 15;  // 写字段 this+168（pAppendVec） ← 15
  *(uint32_t *)(this + 164) = 0;  // 写字段 this+164（fAdd164） ← 0
  *(uint8_t *)(this + 148) = 0;  // 写字段 this+148（fAdd148） ← 0
  if ( *(uint32_t *)(this + 140) >= 0x10u )  // this+140〔nAdd140(推断)〕
    j__free(*(void **)(this + 120));  // 释放堆块
  *(uint32_t *)(this + 140) = 15;  // 写字段 this+140（nAdd140） ← 15
  *(uint32_t *)(this + 136) = 0;  // 写字段 this+136（nCtx136） ← 0
  *(uint8_t *)(this + 120) = 0;  // 写字段 this+120（pAnimObj） ← 0
  sub_4017E0(this + 100);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 96) >= 0x10u )  // this+96〔nStatusMode(推断)〕等 2 字段
    j__free(*(void **)(this + 76));  // 释放堆块
  *(uint32_t *)(this + 96) = 15;  // 写字段 this+96（nStatusMode） ← 15
  *(uint32_t *)(this + 92) = 0;  // 写字段 this+92（pFxObjC） ← 0
  *(uint8_t *)(this + 76) = 0;  // 写字段 this+76（szEmblemPath） ← 0
  if ( *(uint32_t *)(this + 60) != 0 )  // this+60〔nFadeValue60(推断)〕等 2 字段
    j__free(*(void **)(this + 60));  // 释放堆块
  *(uint32_t *)(this + 60) = 0;  // 写字段 this+60（nFadeValue60） ← 0
  *(uint32_t *)(this + 64) = 0;  // 写字段 this+64（apServerTabBtn） ← 0
  *(uint32_t *)(this + 68) = 0;  // 写字段 this+68（nCharCount） ← 0
  if ( *(uint32_t *)(this + 28) >= 0x10u )  // this+28〔pPanelVec(推断)〕等 2 字段
    j__free(*(void **)(this + 8));  // 释放堆块
  *(uint32_t *)(this + 28) = 15;  // 写字段 this+28（pPanelVec） ← 15
  *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
  *(uint8_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
}



// ------------------------------------------------------------
// 0x4CFA50 sub_4CFA50
// ------------------------------------------------------------
// 调: sub_4CFA50 sub_4017E0
void /*thiscall*/ sub_4CFA50(int this)  // 实现：调: sub_4CFA50 sub_4017E0
{
  if ( *(uint32_t *)(this + 196) >= 0x10u )
    j__free(*(void **)(this + 176));  // 释放堆块
  *(uint32_t *)(this + 196) = 15;  // 写字段 this+196 ← 15
  *(uint32_t *)(this + 192) = 0;  // 写字段 this+192（nDlgId） ← 0
  *(uint8_t *)(this + 176) = 0;  // 写字段 this+176（pAppendVecCap） ← 0
  sub_4017E0(this + 156);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 144) != 0 )  // this+144〔pFrameList144(推断)〕等 2 字段
    j__free(*(void **)(this + 144));  // 释放堆块
  *(uint32_t *)(this + 144) = 0;  // 写字段 this+144（pFrameList144） ← 0
  *(uint32_t *)(this + 148) = 0;  // 写字段 this+148（fAdd148） ← 0
  *(uint32_t *)(this + 152) = 0;  // 写字段 this+152（nAdd152） ← 0
  sub_4017E0(this + 124);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  sub_4017E0(this + 108);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 104) >= 0x10u )  // this+104〔nTimerEnd(推断)〕
    j__free(*(void **)(this + 84));  // 释放堆块
  *(uint32_t *)(this + 104) = 15;  // 写字段 this+104（nTimerEnd） ← 15
  *(uint32_t *)(this + 100) = 0;  // 写字段 this+100（bEnchantDone） ← 0
  *(uint8_t *)(this + 84) = 0;  // 写字段 this+84（pFxObjA） ← 0
  if ( *(uint32_t *)(this + 28) >= 0x10u )  // this+28〔pPanelVec(推断)〕等 2 字段
    j__free(*(void **)(this + 8));  // 释放堆块
  *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
  *(uint32_t *)(this + 28) = 15;  // 写字段 this+28（pPanelVec） ← 15
  *(uint8_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
}



// ------------------------------------------------------------
// 0x4CFB40 sub_4CFB40
// ------------------------------------------------------------
// 调: sub_4CFB40 sub_4017E0 sub_41B010
void /*thiscall*/ sub_4CFB40(int this)  // 实现：调: sub_4CFB40 sub_4017E0 sub_41B010
{
  sub_4017E0(this + 136);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 124) != 0 )  // this+124〔pAuraAnim(推断)〕
    j__free(*(void **)(this + 124));  // 释放堆块
  *(uint32_t *)(this + 124) = 0;  // 写字段 this+124（pAuraAnim） ← 0
  *(uint32_t *)(this + 128) = 0;  // 写字段 this+128（szStatusKeyBuf） ← 0
  *(uint32_t *)(this + 132) = 0;  // 写字段 this+132（nAdd132） ← 0
  sub_41B010((void **)(this + 116));  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 112));  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 108));  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 104));  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 88));  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 80));  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 16));  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 12));  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 8));  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 4));  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
}



// ------------------------------------------------------------
// 0x4CFC20 sub_4CFC20
// ------------------------------------------------------------
// 调: sub_4CFC20
void /*thiscall*/ sub_4CFC20(int this)  // 实现：调: sub_4CFC20
{
  if ( *(uint32_t *)(this + 68) != 0 )  // this+68〔nCharCount(推断)〕
    j__free(*(void **)(this + 68));  // 释放堆块
  *(uint32_t *)(this + 68) = 0;  // 写字段 this+68（nCharCount） ← 0
  *(uint32_t *)(this + 72) = 0;  // 写字段 this+72（nSnapshot72） ← 0
  *(uint32_t *)(this + 76) = 0;  // 写字段 this+76（szEmblemPath） ← 0
  if ( *(uint32_t *)(this + 56) >= 0x10u )  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    j__free(*(void **)(this + 36));  // 释放堆块
  *(uint32_t *)(this + 56) = 15;  // 写字段 this+56（pCmdVecCap56） ← 15
  *(uint32_t *)(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
  *(uint8_t *)(this + 36) = 0;  // 写字段 this+36（nStateWord36） ← 0
  if ( *(uint32_t *)(this + 28) >= 0x10u )  // this+28〔pPanelVec(推断)〕等 2 字段
    j__free(*(void **)(this + 8));  // 释放堆块
  *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
  *(uint32_t *)(this + 28) = 15;  // 写字段 this+28（pPanelVec） ← 15
  *(uint8_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
}



// ------------------------------------------------------------
// 0x4CFC80 sub_4CFC80
// ------------------------------------------------------------
// 调: sub_4CFC80 sub_4017E0
void /*thiscall*/ sub_4CFC80(int this)  // 实现：调: sub_4CFC80 sub_4017E0
{
  if ( *(uint32_t *)(this + 356) >= 0x10u )
    j__free(*(void **)(this + 336));  // 释放堆块
  *(uint32_t *)(this + 356) = 15;  // 写字段 this+356 ← 15
  *(uint32_t *)(this + 352) = 0;  // 写字段 this+352（uHitCtx352） ← 0
  *(uint8_t *)(this + 336) = 0;  // 写字段 this+336 ← 0
  sub_4017E0(this + 316);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 304) != 0 )  // this+304〔pLayer304(推断)〕
    j__free(*(void **)(this + 304));  // 释放堆块
  *(uint32_t *)(this + 304) = 0;  // 写字段 this+304（pLayer304） ← 0
  *(uint32_t *)(this + 308) = 0;  // 写字段 this+308 ← 0
  *(uint32_t *)(this + 312) = 0;  // 写字段 this+312 ← 0
  sub_4017E0(this + 284);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  sub_4017E0(this + 268);  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 264) >= 0x10u )  // this+264〔nAnimHandle(推断)〕
    j__free(*(void **)(this + 244));  // 释放堆块
  *(uint32_t *)(this + 264) = 15;  // 写字段 this+264（nAnimHandle） ← 15
  *(uint32_t *)(this + 260) = 0;  // 写字段 this+260（nParamSlotD） ← 0
  *(uint8_t *)(this + 244) = 0;  // 写字段 this+244（fSyncValue） ← 0
  if ( *(uint32_t *)(this + 236) >= 0x10u )  // this+236〔nSyncArgA〕
    j__free(*(void **)(this + 216));  // 释放堆块
  *(uint32_t *)(this + 236) = 15;  // 写字段 this+236（nSyncArgA） ← 15
  *(uint32_t *)(this + 232) = 0;  // 写字段 this+232（bSyncSwitch） ← 0
  *(uint8_t *)(this + 216) = 0;  // 写字段 this+216（bField216） ← 0
  if ( *(uint32_t *)(this + 208) >= 0x10u )  // this+208〔nField208(推断)〕
    j__free(*(void **)(this + 188));  // 释放堆块
  *(uint32_t *)(this + 208) = 15;  // 写字段 this+208（nField208） ← 15
  *(uint32_t *)(this + 204) = 0;  // 写字段 this+204（pSubAnim204） ← 0
  *(uint8_t *)(this + 188) = 0;  // 写字段 this+188（nStatusIdx） ← 0
  if ( *(uint32_t *)(this + 180) >= 0x10u )  // this+180〔nRadius(推断)〕
    j__free(*(void **)(this + 160));  // 释放堆块
  *(uint32_t *)(this + 180) = 15;  // 写字段 this+180（nRadius） ← 15
  *(uint32_t *)(this + 176) = 0;  // 写字段 this+176（pAppendVecCap） ← 0
  *(uint8_t *)(this + 160) = 0;  // 写字段 this+160（fAdd160） ← 0
  if ( *(uint32_t *)(this + 152) >= 0x10u )  // this+152〔nAdd152(推断)〕等 2 字段
    j__free(*(void **)(this + 132));  // 释放堆块
  *(uint32_t *)(this + 152) = 15;  // 写字段 this+152（nAdd152） ← 15
  *(uint32_t *)(this + 148) = 0;  // 写字段 this+148（fAdd148） ← 0
  *(uint8_t *)(this + 132) = 0;  // 写字段 this+132（nAdd132） ← 0
  if ( *(uint32_t *)(this + 124) >= 0x10u )  // this+124〔pAuraAnim(推断)〕
    j__free(*(void **)(this + 104));  // 释放堆块
  *(uint32_t *)(this + 124) = 15;  // 写字段 this+124（pAuraAnim） ← 15
  *(uint32_t *)(this + 120) = 0;  // 写字段 this+120（pAnimObj） ← 0
  *(uint8_t *)(this + 104) = 0;  // 写字段 this+104（nTimerEnd） ← 0
  if ( *(uint32_t *)(this + 28) >= 0x10u )  // this+28〔pPanelVec(推断)〕等 2 字段
    j__free(*(void **)(this + 8));  // 释放堆块
  *(uint32_t *)(this + 28) = 15;  // 写字段 this+28（pPanelVec） ← 15
  *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
  *(uint8_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
}



// ------------------------------------------------------------
// 0x4CFE40 sub_4CFE40
// ------------------------------------------------------------
// 调: sub_4CFE40
void /*thiscall*/ sub_4CFE40(int this)  // 实现：调: sub_4CFE40
{
  if ( *(uint32_t *)(this + 48) != 0 )  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    j__free(*(void **)(this + 48));  // 释放堆块
  *(uint32_t *)(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
  *(uint32_t *)(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
  *(uint32_t *)(this + 56) = 0;  // 写字段 this+56（pCmdVecCap56） ← 0
}



// ------------------------------------------------------------
// 0x4CFE70 sub_4CFE70
// ------------------------------------------------------------
// 调: sub_4CFE70
void /*thiscall*/ sub_4CFE70(int this)  // 实现：调: sub_4CFE70
{
  if ( *(uint32_t *)(this + 28) != 0 )  // this+28〔pPanelVec(推断)〕等 2 字段
    j__free(*(void **)(this + 28));  // 释放堆块
  *(uint32_t *)(this + 28) = 0;  // 写字段 this+28（pPanelVec） ← 0
  *(uint32_t *)(this + 32) = 0;  // 写字段 this+32（nHeight） ← 0
  *(uint32_t *)(this + 36) = 0;  // 写字段 this+36（nStateWord36） ← 0
}



// ------------------------------------------------------------
// 0x4CFEA0 sub_4CFEA0
// ------------------------------------------------------------
// 调: sub_4CFEA0 sub_40D9A0
uint32_t */*thiscall*/ sub_4CFEA0(uint32_t *this)  // 实现：调: sub_4CFEA0 sub_40D9A0
{
  uint32_t **fld_e1; // eax
  uint32_t *v3; // esi
  uint32_t *result; // eax
  bool fld_e12; // zf
  uint32_t *v6; // ebx

  fld_e1 = (uint32_t **)*(this + 1);  // this+4〔宿主对象〕
  v3 = *fld_e1;  // fld_e1=this+4 宿主对象
  *fld_e1 = fld_e1;  // fld_e1=this+4 宿主对象
  result = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  result[1] = result;  // result=this+4 宿主对象
  fld_e12 = v3 == (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  *(this + 2) = 0;  // 写字段 this+2 ← 0
  if ( !fld_e12 )  // fld_e12=this+4 宿主对象
  {
    do
    {
      v6 = (uint32_t *)*v3;
      sub_40D9A0((int)v3);  // sub_40D9A0 —— 单字段串析构（this+12 起；容量 ≥16 才 free）
      j__free(v3);  // 释放堆块
      result = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
      v3 = v6;
    }
    while ( v6 != result );  // 循环直到 v6 != result
  }
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x4CFEE0 sub_4CFEE0
// ------------------------------------------------------------
// 调: sub_4CFEE0 sub_4015C0 sub_401740 sub_4CE5F0 sub_4CE5D0
int **/*thiscall*/ sub_4CFEE0(uint32_t *this, int **pDwArg2, int *Block)  // 实现：调: sub_4CFEE0 sub_4015C0 sub_401740 sub_4CE5F0 sub_4CE5D0
{
  int *Block2; // ebx
  char v4; // al
  int v5; // edi
  int *Block3; // ecx
  int v7; // esi
  uint32_t *pThis2; // ecx
  int v9; // eax
  uint32_t *v10; // eax
  int v11; // eax
  int v12; // eax
  int **Block32; // eax
  char v14; // al
  uint8_t *pObj; // eax
  bool v16; // zf
  int v17; // eax
  uint32_t pExceptionObject[10]; // [esp+8h] [ebp-54h] BYREF
  size_t v20; // [esp+30h] [ebp-2Ch] BYREF
  char v21; // [esp+34h] [ebp-28h]
  int v22; // [esp+44h] [ebp-18h]
  int v23; // [esp+48h] [ebp-14h]
  uint32_t *pThis; // [esp+4Ch] [ebp-10h]
  int v25; // [esp+58h] [ebp-4h]

  Block2 = Block;
  v4 = *((uint8_t *)Block + 69);  // 读字段 v4 = Block[69]
  pThis = this;
  if ( v4 != 0 )
  {
    v23 = 15;
    v22 = 0;
    v21 = 0;
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v25 = 0;
    sub_401740(pExceptionObject, &v20);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::out_of_range::`vftable';  // vftable 复位
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  sub_4CE5F0((int *)&Block);  // sub_4CE5F0 —— 调用 sub_4CE5F0
  if ( *(uint8_t *)(*Block2 + 69) != 0 )
  {
    v5 = Block2[2];
LABEL_8:
    v7 = Block2[1];
    if ( *(uint8_t *)(v5 + 69) == 0 )
      *(uint32_t *)(v5 + 4) = v7;  // 写字段 v5+4（pHostObj） ← v7
    pThis2 = pThis;
    v9 = pThis[1];
    if ( *(int **)(v9 + 4) == Block2 )
    {
      *(uint32_t *)(v9 + 4) = v5;  // 写字段 v9+4（pHostObj） ← v5
    }
    else if ( *(int **)v7 == Block2 )
    {
      *(uint32_t *)v7 = v5;  // *v7 = v5
    }
    else
    {
      *(uint32_t *)(v7 + 8) = v5;  // 写字段 v7+8（nSkillRec8） ← v5
    }
    if ( *(int **)pThis2[1] == Block2 )
    {
      if ( *(uint8_t *)(v5 + 69) != 0 )
      {
        v10 = (uint32_t *)v7;
      }
      else
      {
        v10 = sub_4CE5D0((uint32_t *)v5);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v10;
    }
    if ( *(int **)(pThis2[1] + 8) == Block2 )
    {
      if ( *(uint8_t *)(v5 + 69) != 0 )
      {
        *(uint32_t *)(pThis2[1] + 8) = v7;
      }
      else
      {
        v11 = sub_4CE5B0(v5);
        pThis2 = pThis;
        *(uint32_t *)(pThis[1] + 8) = v11;
      }
    }
    goto LABEL_35;
  }
  if ( *(uint8_t *)(Block2[2] + 69) != 0 )
  {
    v5 = *Block2;
    goto LABEL_8;
  }
  Block3 = Block;
  v5 = Block[2];
  if ( Block == Block2 )
    goto LABEL_8;
  *(uint32_t *)(*Block2 + 4) = Block;
  *Block3 = *Block2;
  if ( Block3 == (int *)Block2[2] )
  {
    v7 = (int)Block3;
  }
  else
  {
    v7 = Block3[1];
    if ( *(uint8_t *)(v5 + 69) == 0 )
      *(uint32_t *)(v5 + 4) = v7;  // 写字段 v5+4（pHostObj） ← v7
    *(uint32_t *)v7 = v5;  // *v7 = v5
    Block3[2] = Block2[2];  // Block3[2] = 取 Block2[2]
    *(uint32_t *)(Block2[2] + 4) = Block3;
  }
  v12 = pThis[1];
  if ( *(int **)(v12 + 4) == Block2 )
  {
    *(uint32_t *)(v12 + 4) = Block3;  // 写字段 v12+4（pHostObj） ← Block3
  }
  else
  {
    Block32 = (int **)Block2[1];
    if ( *Block32 == Block2 )
      *Block32 = Block3;
    else
      Block32[2] = Block3;
  }
  Block3[1] = Block2[1];  // Block3[1] = 取 Block2[1]
  v14 = *((uint8_t *)Block3 + 68);  // 读字段 v14 = Block3+68（nCharCount）
  *((uint8_t *)Block3 + 68) = *((uint8_t *)Block2 + 68);  // 写字段 Block3+68（nCharCount）
  pThis2 = pThis;
  *((uint8_t *)Block2 + 68) = v14;  // 写字段 Block2+68（nCharCount）
LABEL_35:
  if ( *((uint8_t *)Block2 + 68) == 1 )
  {
    if ( v5 != *(uint32_t *)(pThis2[1] + 4) )
    {
      do
      {
        if ( *(uint8_t *)(v5 + 68) != 1 )
          break;
        pObj = *(uint8_t **)v7;
        if ( v5 == *(uint32_t *)v7 )
        {
          pObj = *(uint8_t **)(v7 + 8);
          if ( pObj[68] == 0 )
          {
            pObj[68] = 1;
            *(uint8_t *)(v7 + 68) = 0;  // 写字段 v7+68（nCharCount） ← 0
            sub_4CE650(pThis2, v7);
            pObj = *(uint8_t **)(v7 + 8);
            pThis2 = pThis;
          }
          if ( pObj[69] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)pObj + 68) != 1 || *(uint8_t *)(*((uint32_t *)pObj + 2) + 68) != 1 )
          {
            if ( *(uint8_t *)(*((uint32_t *)pObj + 2) + 68) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)pObj + 68) = 1;
              pObj[68] = 0;
              sub_4CE6B0(pThis2, pObj);
              pObj = *(uint8_t **)(v7 + 8);
              pThis2 = pThis;
            }
            pObj[68] = *(uint8_t *)(v7 + 68);
            *(uint8_t *)(v7 + 68) = 1;  // 写字段 v7+68（nCharCount） ← 1
            *(uint8_t *)(*((uint32_t *)pObj + 2) + 68) = 1;
            sub_4CE650(pThis2, v7);
            break;
          }
        }
        else
        {
          if ( pObj[68] == 0 )
          {
            pObj[68] = 1;
            *(uint8_t *)(v7 + 68) = 0;  // 写字段 v7+68（nCharCount） ← 0
            sub_4CE6B0(pThis2, (uint32_t *)v7);
            pObj = *(uint8_t **)v7;
            pThis2 = pThis;
          }
          if ( pObj[69] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*((uint32_t *)pObj + 2) + 68) != 1 || *(uint8_t *)(*(uint32_t *)pObj + 68) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)pObj + 68) == 1 )
            {
              *(uint8_t *)(*((uint32_t *)pObj + 2) + 68) = 1;
              pObj[68] = 0;
              sub_4CE650(pThis2, (int)pObj);
              pObj = *(uint8_t **)v7;
              pThis2 = pThis;
            }
            pObj[68] = *(uint8_t *)(v7 + 68);
            *(uint8_t *)(v7 + 68) = 1;  // 写字段 v7+68（nCharCount） ← 1
            *(uint8_t *)(*(uint32_t *)pObj + 68) = 1;
            sub_4CE6B0(pThis2, (uint32_t *)v7);
            break;
          }
        }
        pObj[68] = 0;
LABEL_53:
        v5 = v7;
        v16 = v7 == *(uint32_t *)(pThis2[1] + 4);
        v7 = *(uint32_t *)(v7 + 4);  // 读字段 v7 = v7+4（pHostObj）
      }
      while ( !v16 );
    }
    *(uint8_t *)(v5 + 68) = 1;  // 写字段 v5+68（nCharCount） ← 1
  }
  if ( Block2[14] != 0 )
    j__free((void *)Block2[14]);  // 释放堆块
  Block2[14] = 0;
  Block2[15] = 0;
  Block2[16] = 0;
  if ( (unsigned int)Block2[11] >= 0x10 )
    j__free((void *)Block2[6]);  // 释放堆块
  Block2[11] = 15;
  Block2[10] = 0;
  *((uint8_t *)Block2 + 24) = 0;  // 写字段 Block2+24（nPageMax）
  j__free(Block2);  // 释放堆块
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *pDwArg2 = Block;
  return pDwArg2;
}

