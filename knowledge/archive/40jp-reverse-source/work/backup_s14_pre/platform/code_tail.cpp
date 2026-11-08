// ============================================================
// 【40JP逆向源代码工程】src/platform/code_tail.cpp
// 模块: 0x6A-0x6C 代码尾/数据混区 —— CRT x87 数学助手 + 全局对象
//       动态初始化/析构桩群
// 来源: work/dump_tail.txt  区块: 0x6A0000-0x6C1000
//
// 【L1 精修层】本文件已完成 L1 精修（注释级），内容:
//   1) 分区组织（2 个 SECTION：x87 数学/异常群、动态初始化/析构桩群）
//   2) 全部 61 函数逐个一行语义注释（【推断】= 无自证串）
// 函数体逻辑与 L2 转写层逐字一致，未做任何改动（剥离插入注释行可逐字节还原）。
//
// 定位结论（本次精修推理）:
//   - 0x6A02C6-0x6A0A9B: MSVC x87 双精度比较/异常内部库（unknown_libname
//     18/19/28/29/30/31/32/33 = _CMP/FUNCI 比较包装与 FPREM 规约核心，
//     __87except = x87 异常 → _handle_exc/_raise_exc/errno 分派）。
//   - 0x6BE880-0x6C0200: MSVC /GX 全局对象动态初始化器与析构桩
//     （_dynamic_initializer / _dynamic_atexit_destructor 形态）：
//     JUMPOUT(0x657880/0x6578AD) 双出口 = 条件析构桩；sub_401000 =
//     nengine::IObject 首槽（见 src/nengine/log_dump.cpp 0x401000）。
//   - 两个 RTTI 直证: 0x6BF4D0 Camera::vftable、0x6BF4E0 CNRDAStar::vftable
//     （docs/03 类总表的镜头系统与寻路类）。
//   - 0x6C00BE/EE/11E/14E 的 InterlockedDecrement(&Addend) 守卫与
//     272-275 的 ostream/istream vtable 装配 = MSVC iostream 静态 Init/灭。
// ============================================================

#include "../../common/arad_types.h"


// ============================================================
// SECTION 1  CRT x87 双精度比较/异常助手（0x6A02C6-0x6A0A9B）
// ------------------------------------------------------------
// st0/st1 寄存器传参（usercall）+ FPREM 规约 + fnstenv 状态字读取，
// 属 MSVC "net runtime" 比较库（_CMP 内部）；__87except 为 x87 异常
// 到 errno 的桥（_handle_exc/_raise_exc/_ctrlfp/_set_errno）。
// ============================================================
// ------------------------------------------------------------
// 0x6A02C6 unknown_libname_18
// ------------------------------------------------------------
// 【L1】CRT x87 比较包装 A：st1/st0 → unknown_libname_16（FUCOMI 路径）
// Microsoft VisualC 2-14/net runtime
void /*usercall*/ unknown_libname_18(double fArg1@<st1>, double fArg2@<st0>)
{
  _TBYTE fArg12; // [esp+0h] [ebp-2Ch]
  _TBYTE fArg22; // [esp+Ch] [ebp-20h]

  *(double *)&fArg12 = fArg1;
  *(double *)&fArg22 = fArg2;
  unknown_libname_16(fArg12, fArg22);  // IDA 未命名库函数调用（CRT/数学库）
}



// ------------------------------------------------------------
// 0x6A02D9 unknown_libname_19
// ------------------------------------------------------------
// 【L1】CRT x87 比较包装 B：操作数交换序（a2/a3 对调）【推断】
// Microsoft VisualC 2-14/net runtime
void /*usercall*/ unknown_libname_19(double fArg1@<st1>, double fArg2@<st0>)
{
  _TBYTE fArg22; // [esp+0h] [ebp-2Ch]
  _TBYTE fArg12; // [esp+Ch] [ebp-20h]

  *(double *)&fArg12 = fArg1;
  *(double *)&fArg22 = fArg2;
  unknown_libname_16(fArg22, fArg12);  // IDA 未命名库函数调用（CRT/数学库）
}



// ------------------------------------------------------------
// 0x6A04EC unknown_libname_28
// ------------------------------------------------------------
// 【L1】CRT x87 比较包装 C（__spoils edx,ecx/st0 变体）【推断】
// Microsoft VisualC 2-14/net runtime
void /*usercall*/ __spoils<edx,ecx,st0> unknown_libname_28(double fArg1@<st1>, double fArg2@<st0>)
{
  _TBYTE fArg12; // [esp+0h] [ebp-30h]
  _TBYTE fArg22; // [esp+Ch] [ebp-24h]

  *(double *)&fArg12 = fArg1;
  *(double *)&fArg22 = fArg2;
  unknown_libname_16(fArg12, fArg22);  // IDA 未命名库函数调用（CRT/数学库）
}



// ------------------------------------------------------------
// 0x6A0501 unknown_libname_29
// ------------------------------------------------------------
// 【L1】CRT x87 比较包装 D（同族交换序变体）【推断】
// Microsoft VisualC 2-14/net runtime
void /*usercall*/ __spoils<edx,ecx,st0> unknown_libname_29(double fArg1@<st1>, double fArg2@<st0>)
{
  _TBYTE fArg22; // [esp+0h] [ebp-30h]
  _TBYTE fArg12; // [esp+Ch] [ebp-24h]

  *(double *)&fArg12 = fArg1;
  *(double *)&fArg22 = fArg2;
  unknown_libname_16(fArg22, fArg12);  // IDA 未命名库函数调用（CRT/数学库）
}



// ------------------------------------------------------------
// 0x6A0516 unknown_libname_30
// ------------------------------------------------------------
// 【L1】CRT x87 精细比较核心：FPREM 规约循环 + 64 位手工相减比较，返回 FPU 状态字 & 0x4300
// Microsoft VisualC 2-14/net runtime
unsigned int /*usercall*/ unknown_libname_30@<eax>(char pszArg1@<dl>, __int128 nArg2, int nArg3, int nArg4, __int128 nArg5)
{
  unsigned int result; // eax
  int v6; // ecx
  double v7; // st7
  int16_t v8; // fps
  double v9; // st6
  bool v10; // c0
  char v11; // c2
  bool v12; // c3
  int16_t v13; // fps

  result = *(uint32_t *)((char *)&nArg2 + 6) ^ 0x700;
  if ( ((*(uint32_t *)((char *)&nArg2 + 6) ^ 0x700) & 0x700) == 0 )  // 若 ((*(uint32_t *)((char *)&nArg2 + 6) ^ 0x700) & 0x700) == 0
  {
    result = (result >> 11) & 0xF;  // 取状态字 TOP（栈顶指针，3 位）
    if ( byte_79BF5C[result] != 0 )  // 若 byte_79BF5C[result] != 0
    {
      result = *(uint32_t *)((uint8_t *)&nArg2 + 6) & 0x7FFF0000;  // 取 x87 扩展精度指数域（0x7FFF=Inf/NaN）
      if ( (*(uint32_t *)((uint8_t *)&nArg2 + 6) & 0x7FFF0000) != 0x7FFF0000 )  // 若 (*(uint32_t *)((uint8_t *)&nArg2 + 6) & 0x7FFF0000) != 0x7FFF0..
      {
        result = *(uint32_t *)((uint8_t *)&nArg5 + 6) & 0x7FFF0000;  // 取 x87 扩展精度指数域（0x7FFF=Inf/NaN）
        if ( (*(uint32_t *)((uint8_t *)&nArg5 + 6) & 0x7FFF0000) != 0 && result != 2147418112 )  // 取 x87 扩展精度指数域（0x7FFF=Inf/NaN）
        {
          result = 2 * DWORD1(nArg5);  // 尾数最高位 ×2（规格化前判位）
          if ( 2 * DWORD1(nArg5) == 0 )  // 若 2 * DWORD1(nArg5) == 0
          {
            result = 2 * DWORD1(nArg2);  // 尾数最高位 ×2（规格化前判位）
            if ( 2 * DWORD1(nArg2) == 0 )  // 若 2 * DWORD1(nArg2) == 0
            {
              if ( (WORD4(nArg5) & 0x7FFFu) > (WORD4(nArg2) & 0x7FFFu) + 63 )  // 若 (WORD4(nArg5) & 0x7FFFu) > (WORD4(nArg2) & 0x7FFFu) + 63
              {
                v6 = ((BYTE8(nArg5) - BYTE8(nArg2)) & 0x3F | 0x20) + 1;
                v7 = fabs(*(long double *)&nArg2);  // 取绝对值
                v9 = fabs(*(long double *)&nArg5);  // 取绝对值
                do
                {
                  v10 = v9 < v7;
                  v11 = 0;
                  v12 = v9 == v7;
                  result = v8 & 0x100;
                  if ( (v8 & 0x100) == 0 )  // 判定位掩码：v8 & 0x100
                    v9 = v9 - v7;  // 计算 v9 = v9 - v7
                  v7 = v7 * dbl_79BF8C;  // 计算 v7 = v7 * dbl_79BF8C
                  --v6;  // 计数自减 v6
                }
                while ( v6 != 0 );  // 循环直到 v6 != 0
              }
              else
              {
                while ( 1 )  // 当 1 循环
                {
                  result = (WORD4(nArg2) & 0x7FFF) + 10;  // 取 _TBYTE 指数域（15 位）
                  if ( (int)((WORD4(nArg5) & 0x7FFF) - result) < 0 )  // 若 (int)((WORD4(nArg5) & 0x7FFF) - result) < 0
                    break;
                  *(double *)&nArg5 = __FPREM__(*(long double *)&nArg5, *(long double *)&nArg2);  // x87 FPREM 求余（规约 |x| 到 <|y|）
                }
              }
            }
          }
        }
      }
    }
  }
  if ( (pszArg1 & 3) != 0 )  // 判定位掩码：pszArg1 & 3
  {
    __asm { fnstenv [esp+28h+var_28] }  // 内联汇编块
    __asm { fldenv  [esp+28h+var_28] }  // 内联汇编块
    return v13 & 0x4300;  // 取 FPU 状态字 C0/C3+C1（比较结果位）
  }
  return result;
}



// ------------------------------------------------------------
// 0x6A071C unknown_libname_31
// ------------------------------------------------------------
// 【L1】CRT 双精度比较入口：subnormal 缩放 2^63（dbl_79BF74）后转 0x6A0516
// Microsoft VisualC 2-14/net runtime
int /*usercall*/ __spoils<ecx,st0> unknown_libname_31@<eax>(double fArg1@<st1>, double fArg2@<st0>)
{
  int result; // eax
  char v3; // dl
  uint8_t fArg22[20]; // [esp+0h] [ebp-34h]
  int v5; // [esp+14h] [ebp-20h]
  __int128 fArg12; // [esp+18h] [ebp-1Ch]

  *(double *)&fArg12 = fArg1;
  *(double *)fArg22 = fArg2;
  if ( (*(uint32_t *)&fArg22[6] & 0x7FFF0000) != 0 )  // 若 (*(uint32_t *)&fArg22[6] & 0x7FFF0000) != 0
    return unknown_libname_30(0, *(__int128 *)fArg22, *(int *)&fArg22[16], v5, fArg12);  // 调 unknown_libname_30
  result = *(uint32_t *)&fArg22[4] | *(uint32_t *)fArg22;  // 尾数高低段或合并（是否为 0 判定）
  if ( fArg2 != 0.0 )
  {
    *(double *)&fArg22[12] = fArg2;
    v3 = 2;
    if ( (WORD4(fArg12) & 0x7FFFu) <= 0x7FBE )  // 若 (WORD4(fArg12) & 0x7FFFu) <= 0x7FBE
    {
      v3 = 3;
      *(double *)&fArg12 = fArg1 * dbl_79BF74;  // 乘 2^63 缩放 subnormal（x87 归一化扩程）
    }
    *(double *)fArg22 = fArg2 * dbl_79BF74;  // 乘 2^63 缩放 subnormal（x87 归一化扩程）
    return unknown_libname_30(v3, *(__int128 *)fArg22, HIDWORD(*(uint64_t *)&fArg2), v5, fArg12);  // 调 unknown_libname_30
  }
  return result;
}



// ------------------------------------------------------------
// 0x6A07CE unknown_libname_32
// ------------------------------------------------------------
// 【L1】CRT x87 精细比较核心变体（与 6A0516 同体双入口）【推断】
// Microsoft VisualC 2-14/net runtime
unsigned int /*usercall*/ unknown_libname_32@<eax>(char pszArg1@<dl>, __int128 nArg2, int nArg3, int nArg4, __int128 nArg5)
{
  unsigned int result; // eax
  int v6; // ecx
  double v7; // st7
  int16_t v8; // fps
  double v9; // st6
  bool v10; // c0
  char v11; // c2
  bool v12; // c3
  int16_t v13; // fps

  result = *(uint32_t *)((char *)&nArg2 + 6) ^ 0x700;
  if ( ((*(uint32_t *)((char *)&nArg2 + 6) ^ 0x700) & 0x700) == 0 )  // 若 ((*(uint32_t *)((char *)&nArg2 + 6) ^ 0x700) & 0x700) == 0
  {
    result = (result >> 11) & 0xF;  // 取状态字 TOP（栈顶指针，3 位）
    if ( byte_79BF5C[result] != 0 )  // 若 byte_79BF5C[result] != 0
    {
      result = *(uint32_t *)((uint8_t *)&nArg2 + 6) & 0x7FFF0000;  // 取 x87 扩展精度指数域（0x7FFF=Inf/NaN）
      if ( (*(uint32_t *)((uint8_t *)&nArg2 + 6) & 0x7FFF0000) != 0x7FFF0000 )  // 若 (*(uint32_t *)((uint8_t *)&nArg2 + 6) & 0x7FFF0000) != 0x7FFF0..
      {
        result = *(uint32_t *)((uint8_t *)&nArg5 + 6) & 0x7FFF0000;  // 取 x87 扩展精度指数域（0x7FFF=Inf/NaN）
        if ( (*(uint32_t *)((uint8_t *)&nArg5 + 6) & 0x7FFF0000) != 0 && result != 2147418112 )  // 取 x87 扩展精度指数域（0x7FFF=Inf/NaN）
        {
          result = 2 * DWORD1(nArg5);  // 尾数最高位 ×2（规格化前判位）
          if ( 2 * DWORD1(nArg5) == 0 )  // 若 2 * DWORD1(nArg5) == 0
          {
            result = 2 * DWORD1(nArg2);  // 尾数最高位 ×2（规格化前判位）
            if ( 2 * DWORD1(nArg2) == 0 )  // 若 2 * DWORD1(nArg2) == 0
            {
              if ( (WORD4(nArg5) & 0x7FFFu) > (WORD4(nArg2) & 0x7FFFu) + 63 )  // 若 (WORD4(nArg5) & 0x7FFFu) > (WORD4(nArg2) & 0x7FFFu) + 63
              {
                v6 = ((BYTE8(nArg5) - BYTE8(nArg2)) & 0x3F | 0x20) + 1;
                v7 = fabs(*(long double *)&nArg2);  // 取绝对值
                v9 = fabs(*(long double *)&nArg5);  // 取绝对值
                do
                {
                  v10 = v9 < v7;
                  v11 = 0;
                  v12 = v9 == v7;
                  result = v8 & 0x100;
                  if ( (v8 & 0x100) == 0 )  // 判定位掩码：v8 & 0x100
                    v9 = v9 - v7;  // 计算 v9 = v9 - v7
                  v7 = v7 * dbl_79BF8C;  // 计算 v7 = v7 * dbl_79BF8C
                  --v6;  // 计数自减 v6
                }
                while ( v6 != 0 );  // 循环直到 v6 != 0
              }
              else
              {
                while ( 1 )  // 当 1 循环
                {
                  result = (WORD4(nArg2) & 0x7FFF) + 10;  // 取 _TBYTE 指数域（15 位）
                  if ( (int)((WORD4(nArg5) & 0x7FFF) - result) < 0 )  // 若 (int)((WORD4(nArg5) & 0x7FFF) - result) < 0
                    break;
                  *(double *)&nArg5 = __FPREM__(*(long double *)&nArg5, *(long double *)&nArg2);  // x87 FPREM 求余（规约 |x| 到 <|y|）
                }
              }
            }
          }
        }
      }
    }
  }
  if ( (pszArg1 & 3) != 0 )  // 判定位掩码：pszArg1 & 3
  {
    __asm { fnstenv [esp+28h+var_28] }  // 内联汇编块
    __asm { fldenv  [esp+28h+var_28] }  // 内联汇编块
    return v13 & 0x4300;  // 取 FPU 状态字 C0/C3+C1（比较结果位）
  }
  return result;
}



// ------------------------------------------------------------
// 0x6A09D4 unknown_libname_33
// ------------------------------------------------------------
// 【L1】CRT 双精度比较入口变体（与 6A071C 成对）【推断】
// Microsoft VisualC 2-14/net runtime
int /*usercall*/ __spoils<ecx,st0> unknown_libname_33@<eax>(double fArg1@<st1>, double fArg2@<st0>)
{
  int result; // eax
  char v3; // dl
  uint8_t fArg22[20]; // [esp+0h] [ebp-34h]
  int v5; // [esp+14h] [ebp-20h]
  __int128 fArg12; // [esp+18h] [ebp-1Ch]

  *(double *)&fArg12 = fArg1;
  *(double *)fArg22 = fArg2;
  if ( (*(uint32_t *)&fArg22[6] & 0x7FFF0000) != 0 )  // 若 (*(uint32_t *)&fArg22[6] & 0x7FFF0000) != 0
    return unknown_libname_32(0, *(__int128 *)fArg22, *(int *)&fArg22[16], v5, fArg12);  // 调 unknown_libname_32
  result = *(uint32_t *)&fArg22[4] | *(uint32_t *)fArg22;  // 尾数高低段或合并（是否为 0 判定）
  if ( fArg2 != 0.0 )
  {
    *(double *)&fArg22[12] = fArg2;
    v3 = 2;
    if ( (WORD4(fArg12) & 0x7FFFu) <= 0x7FBE )  // 若 (WORD4(fArg12) & 0x7FFFu) <= 0x7FBE
    {
      v3 = 3;
      *(double *)&fArg12 = fArg1 * dbl_79BF74;  // 乘 2^63 缩放 subnormal（x87 归一化扩程）
    }
    *(double *)fArg22 = fArg2 * dbl_79BF74;  // 乘 2^63 缩放 subnormal（x87 归一化扩程）
    return unknown_libname_32(v3, *(__int128 *)fArg22, HIDWORD(*(uint64_t *)&fArg2), v5, fArg12);  // 调 unknown_libname_32
  }
  return result;
}



// ------------------------------------------------------------
// 0x6A0A9B __87except
// ------------------------------------------------------------
// 【L1】__87except：x87 异常码分派(8/4/17/18/16) → _handle_exc/_raise_exc → _ctrlfp + _set_errno
int /*cdecl*/ _87except(int nArg1, int pArg2, int16_t *uArg3)
{
  int16_t v3; // cx
  bool v4; // zf
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  DWORD v11; // ebx
  int result; // eax
  int v13; // [esp-4h] [ebp-94h]
  int v14; // [esp+Ch] [ebp-84h] BYREF
  ULONG_PTR Arguments[12]; // [esp+10h] [ebp-80h] BYREF
  double v16; // [esp+40h] [ebp-50h]
  unsigned int v17; // [esp+50h] [ebp-40h]
  int dword_796E502; // [esp+8Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  v3 = *uArg3;
  v5 = *(uint32_t *)pArg2 - 1;
  v4 = *(uint32_t *)pArg2 == 1;
  v14 = (uint16_t)*uArg3;
  if ( !v4 )  // 若 !v4
  {
    v6 = v5 - 1;  // 计算 v6 = v5 - 1
    if ( v6 == 0 )
    {
      v13 = 4;
      goto LABEL_14;  // 跳转 LABEL_14
    }
    v7 = v6 - 1;  // 计算 v7 = v6 - 1
    if ( v7 == 0 )
    {
      v13 = 17;
      goto LABEL_14;  // 跳转 LABEL_14
    }
    v8 = v7 - 1;  // 计算 v8 = v7 - 1
    if ( v8 == 0 )
    {
      v13 = 18;
      goto LABEL_14;  // 跳转 LABEL_14
    }
    v9 = v8 - 1;  // 计算 v9 = v8 - 1
    if ( v9 != 0 )
    {
      v10 = v9 - 2;  // 计算 v10 = v9 - 2
      if ( v10 == 0 )
      {
        *(uint32_t *)pArg2 = 1;
        goto LABEL_21;  // 跳转 LABEL_21
      }
      if ( v10 == 1 )
      {
        v13 = 16;
        goto LABEL_14;  // 跳转 LABEL_14
      }
LABEL_21:
      _ctrlfp(v14, 0xFFFF);  // CRT 设置 FPU 控制字（精度/舍入/掩码）
      if ( *(uint32_t *)pArg2 == 8 )
        return _set_errno(*(uint32_t *)pArg2);
      if ( dword_797B20 != 0 )
        return _set_errno(*(uint32_t *)pArg2);
      result = sub_679ABC(pArg2);  // sub_679ABC —— 恒返回 0 的桩
      if ( result == 0 )
        return _set_errno(*(uint32_t *)pArg2);
      return result;
    }
  }
  v13 = 8;
LABEL_14:
  v11 = v13;
  if ( !_handle_exc(v13, (double *)(pArg2 + 24), v3) )  // 若 !_handle_exc(v13, (double *)(pArg2 + 24), v3)
  {
    if ( nArg1 == 16 || nArg1 == 22 || nArg1 == 29 )  // 判定 nArg1 == 16 或 nArg1 == 22 或 nArg1 == 29
    {
      v16 = *(double *)(pArg2 + 16);  // v16 = pArg2+16
      v17 = v17 & 0xFFFFFFE0 | 3;  // 写入异常记录号 3（NaN/无效运算）
    }
    else
    {
      v17 &= ~1u;
    }
    _raise_exc((ULONG_PTR)Arguments, (unsigned int *)&v14, v11, nArg1, (double *)(pArg2 + 8), (double *)(pArg2 + 24));  // CRT x87 异常上报（构造 EXCEPTION_RECORD）
  }
  goto LABEL_21;  // 跳转 LABEL_21
}




// ============================================================
// SECTION 2  全局对象动态初始化/析构桩（0x6BE880-0x6C0200）
// ------------------------------------------------------------
// MSVC /GX 对 C++ 全局对象的 _dynamic_initializer / atexit 析构桩群。
// 识别特征: 单一构造转发、sub_4166A0/sub_42CC00 等容器清空 + j__free、
// JUMPOUT(0x657880/0x6578AD) 双出口条件析构、SSO string 析构
// （容量 >= 0x10 才 free）。RTTI 直证: Camera / CNRDAStar vtable 装配。
// ============================================================
// ------------------------------------------------------------
// 0x6BE880 sub_6BE880
// ------------------------------------------------------------
// 【L1】★ clong 对象数组动态初始化：8 组 {4,4000,12,12000,32,40000,64,100000}（clong vftable），
// 配 sub_422E70(1160-1163) 字符串 id【推断：经验/数值配置表】，atexit → 0x6BFD70
int sub_6BE880()
{
  int v0; // edx
  int v1; // edx
  int v2; // edx
  int v3; // edx
  int v4; // edx
  int v5; // edx
  int v6; // edx
  int v7; // edx

  sub_41A630((unsigned int)dword_9B7C90);  // sub_41A630 —— 调 sub_41A630
  dword_9B7C90[0] = (int)&clong::`vftable';  // 装虚表 clong::vftable
  sub_41A590((unsigned int)dword_9B7C90, v0, 4);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A630((unsigned int)&dword_9B7C9E);  // sub_41A630 —— 调 sub_41A630
  dword_9B7C9E = (int)&clong::`vftable';  // 装虚表 clong::vftable
  sub_41A590((unsigned int)&dword_9B7C9E, v1, 4000);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  dword_9B7CAC = (int)sub_422E70(1160);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
  sub_41A630((unsigned int)&dword_9B7CB0);  // sub_41A630 —— 调 sub_41A630
  dword_9B7CB0 = (int)&clong::`vftable';  // 装虚表 clong::vftable
  sub_41A590((unsigned int)&dword_9B7CB0, v2, 12);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A630((unsigned int)&dword_9B7CBE);  // sub_41A630 —— 调 sub_41A630
  dword_9B7CBE = (int)&clong::`vftable';  // 装虚表 clong::vftable
  sub_41A590((unsigned int)&dword_9B7CBE, v3, 12000);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  dword_9B7CCC = (int)sub_422E70(1161);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
  sub_41A630((unsigned int)&dword_9B7CD0);  // sub_41A630 —— 调 sub_41A630
  dword_9B7CD0 = (int)&clong::`vftable';  // 装虚表 clong::vftable
  sub_41A590((unsigned int)&dword_9B7CD0, v4, 32);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A630((unsigned int)&dword_9B7CDE);  // sub_41A630 —— 调 sub_41A630
  dword_9B7CDE = (int)&clong::`vftable';  // 装虚表 clong::vftable
  sub_41A590((unsigned int)&dword_9B7CDE, v5, 40000);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  dword_9B7CEC = (int)sub_422E70(1162);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
  sub_41A630((unsigned int)&dword_9B7CF0);  // sub_41A630 —— 调 sub_41A630
  dword_9B7CF0 = (int)&clong::`vftable';  // 装虚表 clong::vftable
  sub_41A590((unsigned int)&dword_9B7CF0, v6, 64);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A630((unsigned int)&dword_9B7CFE);  // sub_41A630 —— 调 sub_41A630
  dword_9B7CFE = (int)&clong::`vftable';  // 装虚表 clong::vftable
  sub_41A590((unsigned int)&dword_9B7CFE, v7, 100000);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  dword_9B7D0C = (int)sub_422E70(1163);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
  return atexit(sub_6BFD70);  // 注册退出清理例程（atexit sub_6BFD70）
}



// ------------------------------------------------------------
// 0x6BEE80 sub_6BEE80
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_423A20(&unk_9B8DD8)
int sub_6BEE80()  // 函数: 转发 ·sub_423A20
{
  return sub_423A20(&unk_9B8DD8);  // sub_423A20 —— 小结构初始化（0-100 刻度）
}



// ------------------------------------------------------------
// 0x6BEFD0 sub_6BEFD0
// ------------------------------------------------------------
// 【L1】8 组 0x800 字节环形缓冲初始化（word_9B9D50 起步长 1032，容量 768）【推断：消息环】
int sub_6BEFD0()  // 函数: 清零缓冲
{
  int16_t *pBuf; // edx
  int i; // esi
  int result; // eax

  pBuf = &word_9B9D50;  // 取全局对象/数组首址（pBuf ← word_9B9D50）
  for ( i = 8; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    result = 0;
    memset(pBuf - 1024, 0, 0x800u);  // 调 memset 按字节填充
    *((uint32_t *)pBuf + 1) = 0;  // 写字段 pBuf[1]（宽4字节）
    *(uint32_t *)pBuf = 0;
    *((uint32_t *)pBuf + 2) = 0;  // 写字段 pBuf[2]（宽4字节）
    *((uint32_t *)pBuf + 3) = 768;  // 写字段 pBuf[3]（宽4字节）
    pBuf += 1032;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6BF19A sub_6BF19A
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_669C81(&unk_9D24ED)
int sub_6BF19A()  // 函数: 转发 ·sub_669C81
{
  return sub_669C81(&unk_9D24ED);  // sub_669C81 —— 标准流初始化辅助：回填虚表层偏移（表 dword_9D24F0）
}



// ------------------------------------------------------------
// 0x6BF2D0 sub_6BF2D0
// ------------------------------------------------------------
// 【L1】全局缓冲析构：sub_4166A0 + j__free(dword_8F7A68)，三字段清零
void sub_6BF2D0()  // 函数: 释放后返回
{
  if ( dword_8F7A68 != nullptr )
  {
    sub_4166A0(dword_8F7A68, dword_8F7A6C);  // sub_4166A0 —— 析构区间内 28B string 元素
    j__free(dword_8F7A68);  // 释放堆块
  }
  dword_8F7A68 = nullptr;  // dword_8F7A68 = nullptr 空指针
  dword_8F7A6C = 0;
  dword_8F7A70 = 0;
}



// ------------------------------------------------------------
// 0x6BF390 sub_6BF390
// ------------------------------------------------------------
// 【L1】全局缓冲析构同族（dword_8F7C58）【推断】
void sub_6BF390()  // 函数: 释放后返回
{
  if ( dword_8F7C58 != nullptr )  // dword_8F7C58 —— 析构区间内 28B string 元素
  {
    sub_4166A0(dword_8F7C58, dword_8F7C5C);  // sub_4166A0 —— 析构区间内 28B string 元素
    j__free(dword_8F7C58);  // dword_8F7C58 —— 析构区间内 28B string 元素
  }
  dword_8F7C58 = nullptr;  // dword_8F7C58 —— 析构区间内 28B string 元素
  dword_8F7C5C = 0;  // dword_8F7C5C —— 析构区间内 28B string 元素
  dword_8F7C60 = 0;
}



// ------------------------------------------------------------
// 0x6BF450 sub_6BF450
// ------------------------------------------------------------
// 【L1】字符串数组析构：unk_8F8140 链式 free + sub_6599B0 计数递减
void /*cdecl*/ sub_6BF450()  // 函数: 释放后返回
{
  char *v0; // eax
  char *v1; // edi

  v0 = (char *)unk_8F8140;
  if ( unk_8F8140 != 0 )
  {
    do
    {
      v1 = *(char **)&v0[unk_8F8138 - 4];
      free(v0);  // 释放堆块
      --unk_8F8148;  // 计数自减 unk_8F8148
      sub_6599B0(unk_8F8138);  // sub_6599B0 —— peer 发送记账递减（+132 计数与 +140 计数字段）
      v0 = v1;
    }
    while ( v1 != nullptr );  // 循环直到 v1 != nullptr
  }
}



// ------------------------------------------------------------
// 0x6BF4D0 sub_6BF4D0
// ------------------------------------------------------------
// 【L1】★ Camera 全局 vtable 装配（off_77FD68 = &Camera::vftable，docs/12 镜头系统直证）
void sub_6BF4D0()
{
  off_77FD68 = &Camera::`vftable';  // 取类虚表指针
}



// ------------------------------------------------------------
// 0x6BF4E0 sub_6BF4E0
// ------------------------------------------------------------
// 【L1】★ CNRDAStar 全局 vtable 装配（off_77FD90，寻路类直证）
void sub_6BF4E0()
{
  off_77FD90 = &CNRDAStar::`vftable';  // 取类虚表指针
}



// ------------------------------------------------------------
// 0x6BF530 sub_6BF530
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_437850(&dword_8F8558)
int sub_6BF530()  // 函数: 转发 ·sub_437850
{
  return sub_437850(&dword_8F8558);  // sub_437850 —— CNCommandChecker 析构
}



// ------------------------------------------------------------
// 0x6BF540 sub_6BF540
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_437950(&unk_8F85B4)
int sub_6BF540()  // 函数: 转发 ·sub_437950
{
  return sub_437950(&unk_8F85B4);  // sub_437950 —— 子对象析构（向量+缓冲）
}



// ------------------------------------------------------------
// 0x6BF560 sub_6BF560
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_65D270(&unk_9789A0)
int sub_6BF560()  // 函数: 转发 ·sub_65D270
{
  return sub_65D270(&unk_9789A0);  // sub_65D270 —— 音频对象析构（释放引用对象与字符串缓冲）
}



// ------------------------------------------------------------
// 0x6BF570 sub_6BF570
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_444020(&unk_97B248)
int sub_6BF570()  // 函数: 转发 ·sub_444020
{
  return sub_444020(&unk_97B248);  // sub_444020 —— map 整表清空
}



// ------------------------------------------------------------
// 0x6BF590 sub_6BF590
// ------------------------------------------------------------
// 【L1】IObject 槽初始化转发：sub_401000(&unk_97B6B4)（首函数 sub_401000 见 log_dump.cpp）
void sub_6BF590()  // 函数: 转发 ·sub_401000
{
  sub_401000(&unk_97B6B4);  // 【基础设施：nengine::IObject 构造/析构桩 + MSVC std::s…】
}



// ------------------------------------------------------------
// 0x6BF5A0 sub_6BF5A0
// ------------------------------------------------------------
// 【L1】IObject 槽初始化转发：sub_401000(&unk_97B698)
void sub_6BF5A0()  // 函数: 转发 ·sub_401000
{
  sub_401000(&unk_97B698);  // 【基础设施：nengine::IObject 构造/析构桩 + MSVC std::s…】
}



// ------------------------------------------------------------
// 0x6BF5B0 sub_6BF5B0
// ------------------------------------------------------------
// 【L1】条件析构桩：unk_97B6E4 非空走 JUMPOUT(0x657880) 否则 0x6578AD（Hex-Rays 尾跳转形态）
void /*cdecl*/ sub_6BF5B0()
{
  if ( unk_97B6E4 != 0 )
    JUMPOUT(0x657880);  // 跳转至未还原代码块（越过本函数体）
  JUMPOUT(0x6578AD);  // 跳转至未还原代码块（越过本函数体）
}



// ------------------------------------------------------------
// 0x6BF5C0 sub_6BF5C0
// ------------------------------------------------------------
// 【L1】条件析构桩同族（unk_98B708）【推断】
void /*cdecl*/ sub_6BF5C0()
{
  if ( unk_98B708 != 0 )
    JUMPOUT(0x657880);  // 跳转至未还原代码块（越过本函数体）
  JUMPOUT(0x6578AD);  // 跳转至未还原代码块（越过本函数体）
}



// ------------------------------------------------------------
// 0x6BF670 sub_6BF670
// ------------------------------------------------------------
// 【L1】GDI 资源析构：DeleteObject(ho) + 位图/调色板字段组（byte_98B8C8..dword_98B8F8）清零
void /*cdecl*/ sub_6BF670()
{
  if ( ho != nullptr )
    DeleteObject(ho);  // 调 DeleteObject 删除 GDI 对象
  byte_98B8C8 = 0;
  byte_98B8C9 = 0;
  byte_98B8CA = 0;
  byte_98B8CB = 0;
  dword_98B8D4 = 0;
  dword_98B8D8 = 0;
  dword_98B8DC = 0;
  dword_98B8E0 = 0;
  dword_98B8E4 = 0;
  dword_98B8E8 = 0;
  dword_98B8EC = 0;
  dword_98B8F0 = 0;
  ho = nullptr;  // ho = nullptr 空指针
  dword_98B8F8 = 0;
}



// ------------------------------------------------------------
// 0x6BF740 sub_6BF740
// ------------------------------------------------------------
// 【L1】析构转发：nullsub_3(&unk_98BB68)
void /*cdecl*/ sub_6BF740()
{
  nullsub_3(&unk_98BB68);  // unk_98BB68＝的初始化
}



// ------------------------------------------------------------
// 0x6BF760 sub_6BF760
// ------------------------------------------------------------
// 【L1】IObject 槽初始化转发：sub_401000(&unk_99FBE0)
void sub_6BF760()  // 函数: 转发 ·sub_401000
{
  sub_401000(&unk_99FBE0);  // 【基础设施：nengine::IObject 构造/析构桩 + MSVC std::s…】
}



// ------------------------------------------------------------
// 0x6BF880 sub_6BF880
// ------------------------------------------------------------
// 【L1】IObject 槽初始化转发：sub_401000(&unk_99FC80)
void sub_6BF880()  // 函数: 转发 ·sub_401000
{
  sub_401000(&unk_99FC80);  // 【基础设施：nengine::IObject 构造/析构桩 + MSVC std::s…】
}



// ------------------------------------------------------------
// 0x6BF910 sub_6BF910
// ------------------------------------------------------------
// 【L1】IObject 槽初始化转发：sub_401000(&unk_99FD70)
void sub_6BF910()  // 函数: 转发 ·sub_401000
{
  sub_401000(&unk_99FD70);  // 【基础设施：nengine::IObject 构造/析构桩 + MSVC std::s…】
}



// ------------------------------------------------------------
// 0x6BF9D0 sub_6BF9D0
// ------------------------------------------------------------
// 【L1】条件析构桩同族（unk_9A023C）【推断】
void /*cdecl*/ sub_6BF9D0()
{
  if ( unk_9A023C != 0 )
    JUMPOUT(0x657880);  // 跳转至未还原代码块（越过本函数体）
  JUMPOUT(0x6578AD);  // 跳转至未还原代码块（越过本函数体）
}



// ------------------------------------------------------------
// 0x6BFA80 sub_6BFA80
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_437950(&unk_9A0330)
int sub_6BFA80()  // 函数: 转发 ·sub_437950
{
  return sub_437950(&unk_9A0330);  // sub_437950 —— 子对象析构（向量+缓冲）
}



// ------------------------------------------------------------
// 0x6BFA90 sub_6BFA90
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_437950(&unk_9A035C)
int sub_6BFA90()  // 函数: 转发 ·sub_437950
{
  return sub_437950(&unk_9A035C);  // sub_437950 —— 子对象析构（向量+缓冲）
}



// ------------------------------------------------------------
// 0x6BFAE0 sub_6BFAE0
// ------------------------------------------------------------
// 【L1】全局缓冲析构：sub_42CC00 + j__free(dword_9A05AC)
void sub_6BFAE0()  // 函数: 释放后返回
{
  if ( dword_9A05AC != nullptr )
  {
    sub_42CC00(dword_9A05AC, dword_9A05B0);  // sub_42CC00 —— 16 字节槽组释放
    j__free(dword_9A05AC);  // 释放堆块
  }
  dword_9A05AC = nullptr;  // dword_9A05AC = nullptr 空指针
  dword_9A05B0 = 0;
  dword_9A05B4 = 0;
}



// ------------------------------------------------------------
// 0x6BFB40 sub_6BFB40
// ------------------------------------------------------------
// 【L1】全局缓冲析构：sub_4B4950 + j__free(dword_9A05BC)
void sub_6BFB40()  // 函数: 释放后返回
{
  if ( dword_9A05BC != nullptr )
  {
    sub_4B4950(dword_9A05BC, dword_9A05C0);  // sub_4B4950 —— 16 字节记录数组析构（逐元素清 +4 向量后 free）
    j__free(dword_9A05BC);  // 释放堆块
  }
  dword_9A05BC = nullptr;  // dword_9A05BC = nullptr 空指针
  dword_9A05C0 = 0;
  dword_9A05C4 = 0;
}



// ------------------------------------------------------------
// 0x6BFBA0 sub_6BFBA0
// ------------------------------------------------------------
// 【L1】std::string 全局析构：容量 >= 0x10 才 free（SSO 直证），复位 15/0/空
void /*cdecl*/ sub_6BFBA0()  // 函数: 释放后返回
{
  if ( (unsigned int)dword_9B0AA8 >= 0x10 )
    j__free(dword_9B0A94);  // 释放堆块
  dword_9B0AA8 = 15;
  dword_9B0AA4 = 0;
  LOBYTE(dword_9B0A94) = 0;
}



// ------------------------------------------------------------
// 0x6BFD00 sub_6BFD00
// ------------------------------------------------------------
// 【L1】全局缓冲析构：sub_42CC00 + j__free(dword_9B7C64)
void sub_6BFD00()  // 函数: 释放后返回
{
  if ( dword_9B7C64 != nullptr )
  {
    sub_42CC00(dword_9B7C64, dword_9B7C68);  // sub_42CC00 —— 16 字节槽组释放
    j__free(dword_9B7C64);  // 释放堆块
  }
  dword_9B7C64 = nullptr;  // dword_9B7C64 = nullptr 空指针
  dword_9B7C68 = 0;
  dword_9B7C6C = 0;
}



// ------------------------------------------------------------
// 0x6BFD60 sub_6BFD60
// ------------------------------------------------------------
// 【L1】析构转发：sub_432D10(&unk_9B7D10)
void sub_6BFD60()  // 函数: 转发 ·sub_432D10
{
  sub_432D10(&unk_9B7D10);  // sub_432D10 —— 调 sub_432D10
}



// ------------------------------------------------------------
// 0x6BFD70 sub_6BFD70
// ------------------------------------------------------------
// 【L1】0x6BE880 数组的 atexit 回调：eh vector destructor iterator(元素 0x20, 4 个, sub_50D520)
void /*cdecl*/ sub_6BFD70()
{
  `eh vector destructor iterator'(dword_9B7C90, 0x20u, 4, (void (/*thiscall*/ *)(void *))sub_50D520);  // 调 双串槽析构（+14 与 +0）
}



// ------------------------------------------------------------
// 0x6BFDB0 sub_6BFDB0
// ------------------------------------------------------------
// 【L1】条件析构桩同族（unk_9B7FD4）【推断】
void /*cdecl*/ sub_6BFDB0()
{
  if ( unk_9B7FD4 != 0 )
    JUMPOUT(0x657880);  // 跳转至未还原代码块（越过本函数体）
  JUMPOUT(0x6578AD);  // 跳转至未还原代码块（越过本函数体）
}



// ------------------------------------------------------------
// 0x6BFDC0 sub_6BFDC0
// ------------------------------------------------------------
// 【L1】条件析构桩同族（unk_9B7FF8）【推断】
void /*cdecl*/ sub_6BFDC0()
{
  if ( unk_9B7FF8 != 0 )
    JUMPOUT(0x657880);  // 跳转至未还原代码块（越过本函数体）
  JUMPOUT(0x6578AD);  // 跳转至未还原代码块（越过本函数体）
}



// ------------------------------------------------------------
// 0x6BFDD0 sub_6BFDD0
// ------------------------------------------------------------
// 【L1】条件析构桩同族（unk_9B801C）【推断】
void /*cdecl*/ sub_6BFDD0()
{
  if ( unk_9B801C != 0 )
    JUMPOUT(0x657880);  // 跳转至未还原代码块（越过本函数体）
  JUMPOUT(0x6578AD);  // 跳转至未还原代码块（越过本函数体）
}



// ------------------------------------------------------------
// 0x6BFF00 sub_6BFF00
// ------------------------------------------------------------
// 【L1】std::string 全局析构（SSO 同 6BFBA0，dword_9B9388 组）【推断】
void /*cdecl*/ sub_6BFF00()  // 函数: 释放后返回
{
  if ( (unsigned int)dword_9B939C >= 0x10 )
    j__free(dword_9B9388);  // 释放堆块
  dword_9B939C = 15;
  dword_9B9398 = 0;
  LOBYTE(dword_9B9388) = 0;
}



// ------------------------------------------------------------
// 0x6BFF30 sub_6BFF30
// ------------------------------------------------------------
// 【L1】指针三元组析构（dword_9B93AC/B0/B4 双 free）【推断】
void /*cdecl*/ sub_6BFF30()  // 函数: 释放后返回
{
  if ( dword_9B93AC != nullptr )
    j__free(dword_9B93AC);  // 释放堆块
  dword_9B93AC = nullptr;  // dword_9B93AC = nullptr 空指针
  dword_9B93B0 = nullptr;  // dword_9B93B0 = nullptr 空指针
  dword_9B93B4 = 0;
}



// ------------------------------------------------------------
// 0x6C0090 sub_6C0090
// ------------------------------------------------------------
// 【L1】析构转发：sub_5E5260(&dword_9B9474)
void sub_6C0090()  // 函数: 转发 ·sub_5E5260
{
  sub_5E5260(&dword_9B9474);  // 调 sub_5E5260
}



// ------------------------------------------------------------
// 0x6C00BE sub_6C00BE
// ------------------------------------------------------------
// 【L1】iostream 静态析构守卫：InterlockedDecrement(&Addend) < 0 → 遍历
// critical section 数组（stru_9D21E8..9D2248, sub_66A30D）
LONG sub_6C00BE()  // 函数: 引用计数释放（归零自删）
{
  LONG result; // eax
  struct _RTL_CRITICAL_SECTION *v1; // esi

  result = InterlockedDecrement(&Addend);  // 原子递减（引用计数）
  if ( result < 0 )
  {
    v1 = &stru_9D21E8;  // 取全局对象/数组首址（v1 ← stru_9D21E8）
    do
      result = sub_66A30D(v1++);  // sub_66A30D —— 删除临界区（DeleteCriticalSection 包装）
    while ( (int)v1 < (int)&unk_9D2248 );  // 当 (int)v1 < (int)&unk_9D2248 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x6C00C8 unknown_libname_272
// ------------------------------------------------------------
// 【L1】std::ostream 动态初始化：vftable 装配（dword_9D2320）+ sub_65CCD0（MSVC ios Init 族）
// Microsoft VisualC 2-14/net runtime
int unknown_libname_272()
{
  *(int *)((char *)&dword_9D2320 + *(uint32_t *)(dword_9D2320 + 4)) = (int)&std::ostream::`vftable';  // dword_9D2320 —— 字符串 “Could not load winsock”
  return sub_65CCD0(&unk_9D2324);  // sub_65CCD0 —— std::ios 析构包装：挂 std::ios::vftable 后调 std::ios_base::~ios_base
}



// ------------------------------------------------------------
// 0x6C00E4 sub_6C00E4
// ------------------------------------------------------------
// 【L1】析构转发：sub_6697B6(&unk_9D22C0)
int sub_6C00E4()  // 函数: 转发 ·sub_6697B6
{
  return sub_6697B6(&unk_9D22C0);  // sub_6697B6 —— std::filebuf 析构（关文件并释放缓冲）
}



// ------------------------------------------------------------
// 0x6C00EE sub_6C00EE
// ------------------------------------------------------------
// 【L1】iostream 静态析构守卫同族（与 6C00BE 同体）【推断】
LONG sub_6C00EE()  // 函数: 引用计数释放（归零自删）
{
  LONG result; // eax
  struct _RTL_CRITICAL_SECTION *v1; // esi

  result = InterlockedDecrement(&Addend);  // 原子递减（引用计数）
  if ( result < 0 )
  {
    v1 = &stru_9D21E8;  // 取全局对象/数组首址（v1 ← stru_9D21E8）
    do
      result = sub_66A30D(v1++);  // sub_66A30D —— 删除临界区（DeleteCriticalSection 包装）
    while ( (int)v1 < (int)&unk_9D2248 );  // 当 (int)v1 < (int)&unk_9D2248 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x6C00F8 unknown_libname_273
// ------------------------------------------------------------
// 【L1】std::ostream 动态初始化同族（dword_9D23C0）【推断】
// Microsoft VisualC 2-14/net runtime
int unknown_libname_273()
{
  *(int *)((char *)&dword_9D23C0 + *(uint32_t *)(dword_9D23C0 + 4)) = (int)&std::ostream::`vftable';  // 装虚表 ostream::vftable
  return sub_65CCD0(&unk_9D23C4);  // sub_65CCD0 —— std::ios 析构包装：挂 std::ios::vftable 后调 std::ios_base::~ios_base
}



// ------------------------------------------------------------
// 0x6C0114 sub_6C0114
// ------------------------------------------------------------
// 【L1】析构转发：sub_6697B6(&unk_9D2360)
int sub_6C0114()  // 函数: 转发 ·sub_6697B6
{
  return sub_6697B6(&unk_9D2360);  // sub_6697B6 —— std::filebuf 析构（关文件并释放缓冲）
}



// ------------------------------------------------------------
// 0x6C011E sub_6C011E
// ------------------------------------------------------------
// 【L1】iostream 静态析构守卫同族【推断】
LONG sub_6C011E()  // 函数: 引用计数释放（归零自删）
{
  LONG result; // eax
  struct _RTL_CRITICAL_SECTION *v1; // esi

  result = InterlockedDecrement(&Addend);  // 原子递减（引用计数）
  if ( result < 0 )
  {
    v1 = &stru_9D21E8;  // 取全局对象/数组首址（v1 ← stru_9D21E8）
    do
      result = sub_66A30D(v1++);  // sub_66A30D —— 删除临界区（DeleteCriticalSection 包装）
    while ( (int)v1 < (int)&unk_9D2248 );  // 当 (int)v1 < (int)&unk_9D2248 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x6C0128 unknown_libname_274
// ------------------------------------------------------------
// 【L1】std::ostream 动态初始化同族（dword_9D2458）【推断】
// Microsoft VisualC 2-14/net runtime
int unknown_libname_274()
{
  *(int *)((char *)&dword_9D2458 + *(uint32_t *)(dword_9D2458 + 4)) = (int)&std::ostream::`vftable';  // 装虚表 ostream::vftable
  return sub_65CCD0(&unk_9D245C);  // sub_65CCD0 —— std::ios 析构包装：挂 std::ios::vftable 后调 std::ios_base::~ios_base
}



// ------------------------------------------------------------
// 0x6C0144 sub_6C0144
// ------------------------------------------------------------
// 【L1】析构转发：sub_6697B6(&unk_9D23F8)
int sub_6C0144()  // 函数: 转发 ·sub_6697B6
{
  return sub_6697B6(&unk_9D23F8);  // sub_6697B6 —— std::filebuf 析构（关文件并释放缓冲）
}



// ------------------------------------------------------------
// 0x6C014E sub_6C014E
// ------------------------------------------------------------
// 【L1】iostream 静态析构守卫同族【推断】
LONG sub_6C014E()  // 函数: 引用计数释放（归零自删）
{
  LONG result; // eax
  struct _RTL_CRITICAL_SECTION *v1; // esi

  result = InterlockedDecrement(&Addend);  // 原子递减（引用计数）
  if ( result < 0 )
  {
    v1 = &stru_9D21E8;  // 取全局对象/数组首址（v1 ← stru_9D21E8）
    do
      result = sub_66A30D(v1++);  // sub_66A30D —— 删除临界区（DeleteCriticalSection 包装）
    while ( (int)v1 < (int)&unk_9D2248 );  // 当 (int)v1 < (int)&unk_9D2248 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x6C0158 unknown_libname_275
// ------------------------------------------------------------
// 【L1】std::istream 动态初始化：&std::istream::vftable 装配（dword_9D24F0）+ sub_65CCD0
// Microsoft VisualC 2-14/net runtime
int unknown_libname_275()
{
  *(int *)((char *)&dword_9D24F0 + *(uint32_t *)(dword_9D24F0 + 4)) = (int)&std::istream::`vftable';  // 装虚表 istream::vftable
  return sub_65CCD0(&unk_9D24F8);  // sub_65CCD0 —— std::ios 析构包装：挂 std::ios::vftable 后调 std::ios_base::~ios_base
}



// ------------------------------------------------------------
// 0x6C0174 sub_6C0174
// ------------------------------------------------------------
// 【L1】析构转发：sub_6697B6(&unk_9D2490)
int sub_6C0174()  // 函数: 转发 ·sub_6697B6
{
  return sub_6697B6(&unk_9D2490);  // sub_6697B6 —— std::filebuf 析构（关文件并释放缓冲）
}



// ------------------------------------------------------------
// 0x6C017E sub_6C017E
// ------------------------------------------------------------
// 【L1】析构转发：sub_66A262(&dword_9D252C)
void /*cdecl*/ sub_6C017E()  // 函数: 转发 ·sub_66A262
{
  sub_66A262(&dword_9D252C);  // sub_66A262 —— std::bad_alloc 析构：挂 vftable 后转 sub_66B034
}



// ------------------------------------------------------------
// 0x6C0192 sub_6C0192
// ------------------------------------------------------------
// 【L1】_Init_atexit 析构（CRT atexit 注册器收尾）
void sub_6C0192()
{
  _Init_atexit::~_Init_atexit((_Init_atexit *)&unk_9D2585);  // _Init_atexit 静态注册器（CRT atexit 表守卫）
}



// ------------------------------------------------------------
// 0x6C0200 sub_6C0200
// ------------------------------------------------------------
// 【L1】CRT atexit 表槽位估算：((a1-3)/0xC+1) 组 → (12n - a1)/2 + 5【推断：_Init_atexit 容量】
int /*usercall*/ sub_6C0200@<eax>(int nArg1@<edi>)
{
  unsigned int v1; // eax

  if ( nArg1 - 3 >= 0 )
    v1 = (nArg1 - 3) / 0xCu + 1;  // 按 12 字节元素换算槽数（atexit 表项）
  else
    v1 = 0;
  return (int)(12 * v1 - nArg1) / 2 + 5;
}

