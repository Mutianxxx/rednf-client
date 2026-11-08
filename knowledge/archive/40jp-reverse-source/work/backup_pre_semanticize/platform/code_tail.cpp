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
void /*usercall*/ unknown_libname_18(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-2Ch]
  _TBYTE v3; // [esp+Ch] [ebp-20h]

  *(double *)&v2 = a1;
  *(double *)&v3 = a2;
  unknown_libname_16(v2, v3);
}



// ------------------------------------------------------------
// 0x6A02D9 unknown_libname_19
// ------------------------------------------------------------
// 【L1】CRT x87 比较包装 B：操作数交换序（a2/a3 对调）【推断】
// Microsoft VisualC 2-14/net runtime
void /*usercall*/ unknown_libname_19(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-2Ch]
  _TBYTE v3; // [esp+Ch] [ebp-20h]

  *(double *)&v3 = a1;
  *(double *)&v2 = a2;
  unknown_libname_16(v2, v3);
}



// ------------------------------------------------------------
// 0x6A04EC unknown_libname_28
// ------------------------------------------------------------
// 【L1】CRT x87 比较包装 C（__spoils edx,ecx/st0 变体）【推断】
// Microsoft VisualC 2-14/net runtime
void /*usercall*/ __spoils<edx,ecx,st0> unknown_libname_28(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-30h]
  _TBYTE v3; // [esp+Ch] [ebp-24h]

  *(double *)&v2 = a1;
  *(double *)&v3 = a2;
  unknown_libname_16(v2, v3);
}



// ------------------------------------------------------------
// 0x6A0501 unknown_libname_29
// ------------------------------------------------------------
// 【L1】CRT x87 比较包装 D（同族交换序变体）【推断】
// Microsoft VisualC 2-14/net runtime
void /*usercall*/ __spoils<edx,ecx,st0> unknown_libname_29(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-30h]
  _TBYTE v3; // [esp+Ch] [ebp-24h]

  *(double *)&v3 = a1;
  *(double *)&v2 = a2;
  unknown_libname_16(v2, v3);
}



// ------------------------------------------------------------
// 0x6A0516 unknown_libname_30
// ------------------------------------------------------------
// 【L1】CRT x87 精细比较核心：FPREM 规约循环 + 64 位手工相减比较，返回 FPU 状态字 & 0x4300
// Microsoft VisualC 2-14/net runtime
unsigned int /*usercall*/ unknown_libname_30@<eax>(char a1@<dl>, __int128 a2, int a3, int a4, __int128 a5)
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

  result = *(uint32_t *)((char *)&a2 + 6) ^ 0x700;
  if ( ((*(uint32_t *)((char *)&a2 + 6) ^ 0x700) & 0x700) == 0 )
  {
    result = (result >> 11) & 0xF;
    if ( byte_79BF5C[result] != 0 )
    {
      result = *(uint32_t *)((uint8_t *)&a2 + 6) & 0x7FFF0000;
      if ( (*(uint32_t *)((uint8_t *)&a2 + 6) & 0x7FFF0000) != 0x7FFF0000 )
      {
        result = *(uint32_t *)((uint8_t *)&a5 + 6) & 0x7FFF0000;
        if ( (*(uint32_t *)((uint8_t *)&a5 + 6) & 0x7FFF0000) != 0 && result != 2147418112 )
        {
          result = 2 * DWORD1(a5);
          if ( 2 * DWORD1(a5) == 0 )
          {
            result = 2 * DWORD1(a2);
            if ( 2 * DWORD1(a2) == 0 )
            {
              if ( (WORD4(a5) & 0x7FFFu) > (WORD4(a2) & 0x7FFFu) + 63 )
              {
                v6 = ((BYTE8(a5) - BYTE8(a2)) & 0x3F | 0x20) + 1;
                v7 = fabs(*(long double *)&a2);
                v9 = fabs(*(long double *)&a5);
                do
                {
                  v10 = v9 < v7;
                  v11 = 0;
                  v12 = v9 == v7;
                  result = v8 & 0x100;
                  if ( (v8 & 0x100) == 0 )
                    v9 = v9 - v7;
                  v7 = v7 * dbl_79BF8C;
                  --v6;
                }
                while ( v6 != 0 );
              }
              else
              {
                while ( 1 )
                {
                  result = (WORD4(a2) & 0x7FFF) + 10;
                  if ( (int)((WORD4(a5) & 0x7FFF) - result) < 0 )
                    break;
                  *(double *)&a5 = __FPREM__(*(long double *)&a5, *(long double *)&a2);
                }
              }
            }
          }
        }
      }
    }
  }
  if ( (a1 & 3) != 0 )
  {
    __asm { fnstenv [esp+28h+var_28] }
    __asm { fldenv  [esp+28h+var_28] }
    return v13 & 0x4300;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6A071C unknown_libname_31
// ------------------------------------------------------------
// 【L1】CRT 双精度比较入口：subnormal 缩放 2^63（dbl_79BF74）后转 0x6A0516
// Microsoft VisualC 2-14/net runtime
int /*usercall*/ __spoils<ecx,st0> unknown_libname_31@<eax>(double a1@<st1>, double a2@<st0>)
{
  int result; // eax
  char v3; // dl
  uint8_t v4[20]; // [esp+0h] [ebp-34h]
  int v5; // [esp+14h] [ebp-20h]
  __int128 v6; // [esp+18h] [ebp-1Ch]

  *(double *)&v6 = a1;
  *(double *)v4 = a2;
  if ( (*(uint32_t *)&v4[6] & 0x7FFF0000) != 0 )
    return unknown_libname_30(0, *(__int128 *)v4, *(int *)&v4[16], v5, v6);
  result = *(uint32_t *)&v4[4] | *(uint32_t *)v4;
  if ( a2 != 0.0 )
  {
    *(double *)&v4[12] = a2;
    v3 = 2;
    if ( (WORD4(v6) & 0x7FFFu) <= 0x7FBE )
    {
      v3 = 3;
      *(double *)&v6 = a1 * dbl_79BF74;
    }
    *(double *)v4 = a2 * dbl_79BF74;
    return unknown_libname_30(v3, *(__int128 *)v4, HIDWORD(*(uint64_t *)&a2), v5, v6);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6A07CE unknown_libname_32
// ------------------------------------------------------------
// 【L1】CRT x87 精细比较核心变体（与 6A0516 同体双入口）【推断】
// Microsoft VisualC 2-14/net runtime
unsigned int /*usercall*/ unknown_libname_32@<eax>(char a1@<dl>, __int128 a2, int a3, int a4, __int128 a5)
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

  result = *(uint32_t *)((char *)&a2 + 6) ^ 0x700;
  if ( ((*(uint32_t *)((char *)&a2 + 6) ^ 0x700) & 0x700) == 0 )
  {
    result = (result >> 11) & 0xF;
    if ( byte_79BF5C[result] != 0 )
    {
      result = *(uint32_t *)((uint8_t *)&a2 + 6) & 0x7FFF0000;
      if ( (*(uint32_t *)((uint8_t *)&a2 + 6) & 0x7FFF0000) != 0x7FFF0000 )
      {
        result = *(uint32_t *)((uint8_t *)&a5 + 6) & 0x7FFF0000;
        if ( (*(uint32_t *)((uint8_t *)&a5 + 6) & 0x7FFF0000) != 0 && result != 2147418112 )
        {
          result = 2 * DWORD1(a5);
          if ( 2 * DWORD1(a5) == 0 )
          {
            result = 2 * DWORD1(a2);
            if ( 2 * DWORD1(a2) == 0 )
            {
              if ( (WORD4(a5) & 0x7FFFu) > (WORD4(a2) & 0x7FFFu) + 63 )
              {
                v6 = ((BYTE8(a5) - BYTE8(a2)) & 0x3F | 0x20) + 1;
                v7 = fabs(*(long double *)&a2);
                v9 = fabs(*(long double *)&a5);
                do
                {
                  v10 = v9 < v7;
                  v11 = 0;
                  v12 = v9 == v7;
                  result = v8 & 0x100;
                  if ( (v8 & 0x100) == 0 )
                    v9 = v9 - v7;
                  v7 = v7 * dbl_79BF8C;
                  --v6;
                }
                while ( v6 != 0 );
              }
              else
              {
                while ( 1 )
                {
                  result = (WORD4(a2) & 0x7FFF) + 10;
                  if ( (int)((WORD4(a5) & 0x7FFF) - result) < 0 )
                    break;
                  *(double *)&a5 = __FPREM__(*(long double *)&a5, *(long double *)&a2);
                }
              }
            }
          }
        }
      }
    }
  }
  if ( (a1 & 3) != 0 )
  {
    __asm { fnstenv [esp+28h+var_28] }
    __asm { fldenv  [esp+28h+var_28] }
    return v13 & 0x4300;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6A09D4 unknown_libname_33
// ------------------------------------------------------------
// 【L1】CRT 双精度比较入口变体（与 6A071C 成对）【推断】
// Microsoft VisualC 2-14/net runtime
int /*usercall*/ __spoils<ecx,st0> unknown_libname_33@<eax>(double a1@<st1>, double a2@<st0>)
{
  int result; // eax
  char v3; // dl
  uint8_t v4[20]; // [esp+0h] [ebp-34h]
  int v5; // [esp+14h] [ebp-20h]
  __int128 v6; // [esp+18h] [ebp-1Ch]

  *(double *)&v6 = a1;
  *(double *)v4 = a2;
  if ( (*(uint32_t *)&v4[6] & 0x7FFF0000) != 0 )
    return unknown_libname_32(0, *(__int128 *)v4, *(int *)&v4[16], v5, v6);
  result = *(uint32_t *)&v4[4] | *(uint32_t *)v4;
  if ( a2 != 0.0 )
  {
    *(double *)&v4[12] = a2;
    v3 = 2;
    if ( (WORD4(v6) & 0x7FFFu) <= 0x7FBE )
    {
      v3 = 3;
      *(double *)&v6 = a1 * dbl_79BF74;
    }
    *(double *)v4 = a2 * dbl_79BF74;
    return unknown_libname_32(v3, *(__int128 *)v4, HIDWORD(*(uint64_t *)&a2), v5, v6);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6A0A9B __87except
// ------------------------------------------------------------
// 【L1】__87except：x87 异常码分派(8/4/17/18/16) → _handle_exc/_raise_exc → _ctrlfp + _set_errno
int /*cdecl*/ _87except(int a1, int a2, int16_t *a3)
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
  int v18; // [esp+8Ch] [ebp-4h]

  v18 = dword_796E50;
  v3 = *a3;
  v5 = *(uint32_t *)a2 - 1;
  v4 = *(uint32_t *)a2 == 1;
  v14 = (uint16_t)*a3;
  if ( !v4 )
  {
    v6 = v5 - 1;
    if ( v6 == 0 )
    {
      v13 = 4;
      goto LABEL_14;
    }
    v7 = v6 - 1;
    if ( v7 == 0 )
    {
      v13 = 17;
      goto LABEL_14;
    }
    v8 = v7 - 1;
    if ( v8 == 0 )
    {
      v13 = 18;
      goto LABEL_14;
    }
    v9 = v8 - 1;
    if ( v9 != 0 )
    {
      v10 = v9 - 2;
      if ( v10 == 0 )
      {
        *(uint32_t *)a2 = 1;
        goto LABEL_21;
      }
      if ( v10 == 1 )
      {
        v13 = 16;
        goto LABEL_14;
      }
LABEL_21:
      _ctrlfp(v14, 0xFFFF);
      if ( *(uint32_t *)a2 == 8 )
        return _set_errno(*(uint32_t *)a2);
      if ( dword_797B20 != 0 )
        return _set_errno(*(uint32_t *)a2);
      result = sub_679ABC(a2);
      if ( result == 0 )
        return _set_errno(*(uint32_t *)a2);
      return result;
    }
  }
  v13 = 8;
LABEL_14:
  v11 = v13;
  if ( !_handle_exc(v13, (double *)(a2 + 24), v3) )
  {
    if ( a1 == 16 || a1 == 22 || a1 == 29 )
    {
      v16 = *(double *)(a2 + 16);
      v17 = v17 & 0xFFFFFFE0 | 3;
    }
    else
    {
      v17 &= ~1u;
    }
    _raise_exc((ULONG_PTR)Arguments, (unsigned int *)&v14, v11, a1, (double *)(a2 + 8), (double *)(a2 + 24));
  }
  goto LABEL_21;
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

  sub_41A630((unsigned int)dword_9B7C90);
  dword_9B7C90[0] = (int)&clong::`vftable';
  sub_41A590((unsigned int)dword_9B7C90, v0, 4);
  sub_41A630((unsigned int)&dword_9B7C9E);
  dword_9B7C9E = (int)&clong::`vftable';
  sub_41A590((unsigned int)&dword_9B7C9E, v1, 4000);
  dword_9B7CAC = (int)sub_422E70(1160);
  sub_41A630((unsigned int)&dword_9B7CB0);
  dword_9B7CB0 = (int)&clong::`vftable';
  sub_41A590((unsigned int)&dword_9B7CB0, v2, 12);
  sub_41A630((unsigned int)&dword_9B7CBE);
  dword_9B7CBE = (int)&clong::`vftable';
  sub_41A590((unsigned int)&dword_9B7CBE, v3, 12000);
  dword_9B7CCC = (int)sub_422E70(1161);
  sub_41A630((unsigned int)&dword_9B7CD0);
  dword_9B7CD0 = (int)&clong::`vftable';
  sub_41A590((unsigned int)&dword_9B7CD0, v4, 32);
  sub_41A630((unsigned int)&dword_9B7CDE);
  dword_9B7CDE = (int)&clong::`vftable';
  sub_41A590((unsigned int)&dword_9B7CDE, v5, 40000);
  dword_9B7CEC = (int)sub_422E70(1162);
  sub_41A630((unsigned int)&dword_9B7CF0);
  dword_9B7CF0 = (int)&clong::`vftable';
  sub_41A590((unsigned int)&dword_9B7CF0, v6, 64);
  sub_41A630((unsigned int)&dword_9B7CFE);
  dword_9B7CFE = (int)&clong::`vftable';
  sub_41A590((unsigned int)&dword_9B7CFE, v7, 100000);
  dword_9B7D0C = (int)sub_422E70(1163);
  return atexit(sub_6BFD70);
}



// ------------------------------------------------------------
// 0x6BEE80 sub_6BEE80
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_423A20(&unk_9B8DD8)
int sub_6BEE80()
{
  return sub_423A20(&unk_9B8DD8);
}



// ------------------------------------------------------------
// 0x6BEFD0 sub_6BEFD0
// ------------------------------------------------------------
// 【L1】8 组 0x800 字节环形缓冲初始化（word_9B9D50 起步长 1032，容量 768）【推断：消息环】
int sub_6BEFD0()
{
  int16_t *v0; // edx
  int i; // esi
  int result; // eax

  v0 = &word_9B9D50;
  for ( i = 8; i != 0; --i )
  {
    result = 0;
    memset(v0 - 1024, 0, 0x800u);
    *((uint32_t *)v0 + 1) = 0;
    *(uint32_t *)v0 = 0;
    *((uint32_t *)v0 + 2) = 0;
    *((uint32_t *)v0 + 3) = 768;
    v0 += 1032;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6BF19A sub_6BF19A
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_669C81(&unk_9D24ED)
int sub_6BF19A()
{
  return sub_669C81(&unk_9D24ED);
}



// ------------------------------------------------------------
// 0x6BF2D0 sub_6BF2D0
// ------------------------------------------------------------
// 【L1】全局缓冲析构：sub_4166A0 + j__free(dword_8F7A68)，三字段清零
void sub_6BF2D0()
{
  if ( dword_8F7A68 != nullptr )
  {
    sub_4166A0(dword_8F7A68, dword_8F7A6C);
    j__free(dword_8F7A68);
  }
  dword_8F7A68 = nullptr;
  dword_8F7A6C = 0;
  dword_8F7A70 = 0;
}



// ------------------------------------------------------------
// 0x6BF390 sub_6BF390
// ------------------------------------------------------------
// 【L1】全局缓冲析构同族（dword_8F7C58）【推断】
void sub_6BF390()
{
  if ( dword_8F7C58 != nullptr )
  {
    sub_4166A0(dword_8F7C58, dword_8F7C5C);
    j__free(dword_8F7C58);
  }
  dword_8F7C58 = nullptr;
  dword_8F7C5C = 0;
  dword_8F7C60 = 0;
}



// ------------------------------------------------------------
// 0x6BF450 sub_6BF450
// ------------------------------------------------------------
// 【L1】字符串数组析构：unk_8F8140 链式 free + sub_6599B0 计数递减
void /*cdecl*/ sub_6BF450()
{
  char *v0; // eax
  char *v1; // edi

  v0 = (char *)unk_8F8140;
  if ( unk_8F8140 != 0 )
  {
    do
    {
      v1 = *(char **)&v0[unk_8F8138 - 4];
      free(v0);
      --unk_8F8148;
      sub_6599B0(unk_8F8138);
      v0 = v1;
    }
    while ( v1 != nullptr );
  }
}



// ------------------------------------------------------------
// 0x6BF4D0 sub_6BF4D0
// ------------------------------------------------------------
// 【L1】★ Camera 全局 vtable 装配（off_77FD68 = &Camera::vftable，docs/12 镜头系统直证）
void sub_6BF4D0()
{
  off_77FD68 = &Camera::`vftable';
}



// ------------------------------------------------------------
// 0x6BF4E0 sub_6BF4E0
// ------------------------------------------------------------
// 【L1】★ CNRDAStar 全局 vtable 装配（off_77FD90，寻路类直证）
void sub_6BF4E0()
{
  off_77FD90 = &CNRDAStar::`vftable';
}



// ------------------------------------------------------------
// 0x6BF530 sub_6BF530
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_437850(&dword_8F8558)
int sub_6BF530()
{
  return sub_437850(&dword_8F8558);
}



// ------------------------------------------------------------
// 0x6BF540 sub_6BF540
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_437950(&unk_8F85B4)
int sub_6BF540()
{
  return sub_437950(&unk_8F85B4);
}



// ------------------------------------------------------------
// 0x6BF560 sub_6BF560
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_65D270(&unk_9789A0)
int sub_6BF560()
{
  return sub_65D270(&unk_9789A0);
}



// ------------------------------------------------------------
// 0x6BF570 sub_6BF570
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_444020(&unk_97B248)
int sub_6BF570()
{
  return sub_444020(&unk_97B248);
}



// ------------------------------------------------------------
// 0x6BF590 sub_6BF590
// ------------------------------------------------------------
// 【L1】IObject 槽初始化转发：sub_401000(&unk_97B6B4)（首函数 sub_401000 见 log_dump.cpp）
void sub_6BF590()
{
  sub_401000(&unk_97B6B4);
}



// ------------------------------------------------------------
// 0x6BF5A0 sub_6BF5A0
// ------------------------------------------------------------
// 【L1】IObject 槽初始化转发：sub_401000(&unk_97B698)
void sub_6BF5A0()
{
  sub_401000(&unk_97B698);
}



// ------------------------------------------------------------
// 0x6BF5B0 sub_6BF5B0
// ------------------------------------------------------------
// 【L1】条件析构桩：unk_97B6E4 非空走 JUMPOUT(0x657880) 否则 0x6578AD（Hex-Rays 尾跳转形态）
void /*cdecl*/ sub_6BF5B0()
{
  if ( unk_97B6E4 != 0 )
    JUMPOUT(0x657880);
  JUMPOUT(0x6578AD);
}



// ------------------------------------------------------------
// 0x6BF5C0 sub_6BF5C0
// ------------------------------------------------------------
// 【L1】条件析构桩同族（unk_98B708）【推断】
void /*cdecl*/ sub_6BF5C0()
{
  if ( unk_98B708 != 0 )
    JUMPOUT(0x657880);
  JUMPOUT(0x6578AD);
}



// ------------------------------------------------------------
// 0x6BF670 sub_6BF670
// ------------------------------------------------------------
// 【L1】GDI 资源析构：DeleteObject(ho) + 位图/调色板字段组（byte_98B8C8..dword_98B8F8）清零
void /*cdecl*/ sub_6BF670()
{
  if ( ho != nullptr )
    DeleteObject(ho);
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
  ho = nullptr;
  dword_98B8F8 = 0;
}



// ------------------------------------------------------------
// 0x6BF740 sub_6BF740
// ------------------------------------------------------------
// 【L1】析构转发：nullsub_3(&unk_98BB68)
void /*cdecl*/ sub_6BF740()
{
  nullsub_3(&unk_98BB68);
}



// ------------------------------------------------------------
// 0x6BF760 sub_6BF760
// ------------------------------------------------------------
// 【L1】IObject 槽初始化转发：sub_401000(&unk_99FBE0)
void sub_6BF760()
{
  sub_401000(&unk_99FBE0);
}



// ------------------------------------------------------------
// 0x6BF880 sub_6BF880
// ------------------------------------------------------------
// 【L1】IObject 槽初始化转发：sub_401000(&unk_99FC80)
void sub_6BF880()
{
  sub_401000(&unk_99FC80);
}



// ------------------------------------------------------------
// 0x6BF910 sub_6BF910
// ------------------------------------------------------------
// 【L1】IObject 槽初始化转发：sub_401000(&unk_99FD70)
void sub_6BF910()
{
  sub_401000(&unk_99FD70);
}



// ------------------------------------------------------------
// 0x6BF9D0 sub_6BF9D0
// ------------------------------------------------------------
// 【L1】条件析构桩同族（unk_9A023C）【推断】
void /*cdecl*/ sub_6BF9D0()
{
  if ( unk_9A023C != 0 )
    JUMPOUT(0x657880);
  JUMPOUT(0x6578AD);
}



// ------------------------------------------------------------
// 0x6BFA80 sub_6BFA80
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_437950(&unk_9A0330)
int sub_6BFA80()
{
  return sub_437950(&unk_9A0330);
}



// ------------------------------------------------------------
// 0x6BFA90 sub_6BFA90
// ------------------------------------------------------------
// 【L1】动态初始化转发：sub_437950(&unk_9A035C)
int sub_6BFA90()
{
  return sub_437950(&unk_9A035C);
}



// ------------------------------------------------------------
// 0x6BFAE0 sub_6BFAE0
// ------------------------------------------------------------
// 【L1】全局缓冲析构：sub_42CC00 + j__free(dword_9A05AC)
void sub_6BFAE0()
{
  if ( dword_9A05AC != nullptr )
  {
    sub_42CC00(dword_9A05AC, dword_9A05B0);
    j__free(dword_9A05AC);
  }
  dword_9A05AC = nullptr;
  dword_9A05B0 = 0;
  dword_9A05B4 = 0;
}



// ------------------------------------------------------------
// 0x6BFB40 sub_6BFB40
// ------------------------------------------------------------
// 【L1】全局缓冲析构：sub_4B4950 + j__free(dword_9A05BC)
void sub_6BFB40()
{
  if ( dword_9A05BC != nullptr )
  {
    sub_4B4950(dword_9A05BC, dword_9A05C0);
    j__free(dword_9A05BC);
  }
  dword_9A05BC = nullptr;
  dword_9A05C0 = 0;
  dword_9A05C4 = 0;
}



// ------------------------------------------------------------
// 0x6BFBA0 sub_6BFBA0
// ------------------------------------------------------------
// 【L1】std::string 全局析构：容量 >= 0x10 才 free（SSO 直证），复位 15/0/空
void /*cdecl*/ sub_6BFBA0()
{
  if ( (unsigned int)dword_9B0AA8 >= 0x10 )
    j__free(dword_9B0A94);
  dword_9B0AA8 = 15;
  dword_9B0AA4 = 0;
  LOBYTE(dword_9B0A94) = 0;
}



// ------------------------------------------------------------
// 0x6BFD00 sub_6BFD00
// ------------------------------------------------------------
// 【L1】全局缓冲析构：sub_42CC00 + j__free(dword_9B7C64)
void sub_6BFD00()
{
  if ( dword_9B7C64 != nullptr )
  {
    sub_42CC00(dword_9B7C64, dword_9B7C68);
    j__free(dword_9B7C64);
  }
  dword_9B7C64 = nullptr;
  dword_9B7C68 = 0;
  dword_9B7C6C = 0;
}



// ------------------------------------------------------------
// 0x6BFD60 sub_6BFD60
// ------------------------------------------------------------
// 【L1】析构转发：sub_432D10(&unk_9B7D10)
void sub_6BFD60()
{
  sub_432D10(&unk_9B7D10);
}



// ------------------------------------------------------------
// 0x6BFD70 sub_6BFD70
// ------------------------------------------------------------
// 【L1】0x6BE880 数组的 atexit 回调：eh vector destructor iterator(元素 0x20, 4 个, sub_50D520)
void /*cdecl*/ sub_6BFD70()
{
  `eh vector destructor iterator'(dword_9B7C90, 0x20u, 4, (void (/*thiscall*/ *)(void *))sub_50D520);
}



// ------------------------------------------------------------
// 0x6BFDB0 sub_6BFDB0
// ------------------------------------------------------------
// 【L1】条件析构桩同族（unk_9B7FD4）【推断】
void /*cdecl*/ sub_6BFDB0()
{
  if ( unk_9B7FD4 != 0 )
    JUMPOUT(0x657880);
  JUMPOUT(0x6578AD);
}



// ------------------------------------------------------------
// 0x6BFDC0 sub_6BFDC0
// ------------------------------------------------------------
// 【L1】条件析构桩同族（unk_9B7FF8）【推断】
void /*cdecl*/ sub_6BFDC0()
{
  if ( unk_9B7FF8 != 0 )
    JUMPOUT(0x657880);
  JUMPOUT(0x6578AD);
}



// ------------------------------------------------------------
// 0x6BFDD0 sub_6BFDD0
// ------------------------------------------------------------
// 【L1】条件析构桩同族（unk_9B801C）【推断】
void /*cdecl*/ sub_6BFDD0()
{
  if ( unk_9B801C != 0 )
    JUMPOUT(0x657880);
  JUMPOUT(0x6578AD);
}



// ------------------------------------------------------------
// 0x6BFF00 sub_6BFF00
// ------------------------------------------------------------
// 【L1】std::string 全局析构（SSO 同 6BFBA0，dword_9B9388 组）【推断】
void /*cdecl*/ sub_6BFF00()
{
  if ( (unsigned int)dword_9B939C >= 0x10 )
    j__free(dword_9B9388);
  dword_9B939C = 15;
  dword_9B9398 = 0;
  LOBYTE(dword_9B9388) = 0;
}



// ------------------------------------------------------------
// 0x6BFF30 sub_6BFF30
// ------------------------------------------------------------
// 【L1】指针三元组析构（dword_9B93AC/B0/B4 双 free）【推断】
void /*cdecl*/ sub_6BFF30()
{
  if ( dword_9B93AC != nullptr )
    j__free(dword_9B93AC);
  dword_9B93AC = nullptr;
  dword_9B93B0 = nullptr;
  dword_9B93B4 = 0;
}



// ------------------------------------------------------------
// 0x6C0090 sub_6C0090
// ------------------------------------------------------------
// 【L1】析构转发：sub_5E5260(&dword_9B9474)
void sub_6C0090()
{
  sub_5E5260(&dword_9B9474);
}



// ------------------------------------------------------------
// 0x6C00BE sub_6C00BE
// ------------------------------------------------------------
// 【L1】iostream 静态析构守卫：InterlockedDecrement(&Addend) < 0 → 遍历
// critical section 数组（stru_9D21E8..9D2248, sub_66A30D）
LONG sub_6C00BE()
{
  LONG result; // eax
  struct _RTL_CRITICAL_SECTION *v1; // esi

  result = InterlockedDecrement(&Addend);
  if ( result < 0 )
  {
    v1 = &stru_9D21E8;
    do
      result = sub_66A30D(v1++);
    while ( (int)v1 < (int)&unk_9D2248 );
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
  *(int *)((char *)&dword_9D2320 + *(uint32_t *)(dword_9D2320 + 4)) = (int)&std::ostream::`vftable';
  return sub_65CCD0(&unk_9D2324);
}



// ------------------------------------------------------------
// 0x6C00E4 sub_6C00E4
// ------------------------------------------------------------
// 【L1】析构转发：sub_6697B6(&unk_9D22C0)
int sub_6C00E4()
{
  return sub_6697B6(&unk_9D22C0);
}



// ------------------------------------------------------------
// 0x6C00EE sub_6C00EE
// ------------------------------------------------------------
// 【L1】iostream 静态析构守卫同族（与 6C00BE 同体）【推断】
LONG sub_6C00EE()
{
  LONG result; // eax
  struct _RTL_CRITICAL_SECTION *v1; // esi

  result = InterlockedDecrement(&Addend);
  if ( result < 0 )
  {
    v1 = &stru_9D21E8;
    do
      result = sub_66A30D(v1++);
    while ( (int)v1 < (int)&unk_9D2248 );
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
  *(int *)((char *)&dword_9D23C0 + *(uint32_t *)(dword_9D23C0 + 4)) = (int)&std::ostream::`vftable';
  return sub_65CCD0(&unk_9D23C4);
}



// ------------------------------------------------------------
// 0x6C0114 sub_6C0114
// ------------------------------------------------------------
// 【L1】析构转发：sub_6697B6(&unk_9D2360)
int sub_6C0114()
{
  return sub_6697B6(&unk_9D2360);
}



// ------------------------------------------------------------
// 0x6C011E sub_6C011E
// ------------------------------------------------------------
// 【L1】iostream 静态析构守卫同族【推断】
LONG sub_6C011E()
{
  LONG result; // eax
  struct _RTL_CRITICAL_SECTION *v1; // esi

  result = InterlockedDecrement(&Addend);
  if ( result < 0 )
  {
    v1 = &stru_9D21E8;
    do
      result = sub_66A30D(v1++);
    while ( (int)v1 < (int)&unk_9D2248 );
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
  *(int *)((char *)&dword_9D2458 + *(uint32_t *)(dword_9D2458 + 4)) = (int)&std::ostream::`vftable';
  return sub_65CCD0(&unk_9D245C);
}



// ------------------------------------------------------------
// 0x6C0144 sub_6C0144
// ------------------------------------------------------------
// 【L1】析构转发：sub_6697B6(&unk_9D23F8)
int sub_6C0144()
{
  return sub_6697B6(&unk_9D23F8);
}



// ------------------------------------------------------------
// 0x6C014E sub_6C014E
// ------------------------------------------------------------
// 【L1】iostream 静态析构守卫同族【推断】
LONG sub_6C014E()
{
  LONG result; // eax
  struct _RTL_CRITICAL_SECTION *v1; // esi

  result = InterlockedDecrement(&Addend);
  if ( result < 0 )
  {
    v1 = &stru_9D21E8;
    do
      result = sub_66A30D(v1++);
    while ( (int)v1 < (int)&unk_9D2248 );
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
  *(int *)((char *)&dword_9D24F0 + *(uint32_t *)(dword_9D24F0 + 4)) = (int)&std::istream::`vftable';
  return sub_65CCD0(&unk_9D24F8);
}



// ------------------------------------------------------------
// 0x6C0174 sub_6C0174
// ------------------------------------------------------------
// 【L1】析构转发：sub_6697B6(&unk_9D2490)
int sub_6C0174()
{
  return sub_6697B6(&unk_9D2490);
}



// ------------------------------------------------------------
// 0x6C017E sub_6C017E
// ------------------------------------------------------------
// 【L1】析构转发：sub_66A262(&dword_9D252C)
void /*cdecl*/ sub_6C017E()
{
  sub_66A262(&dword_9D252C);
}



// ------------------------------------------------------------
// 0x6C0192 sub_6C0192
// ------------------------------------------------------------
// 【L1】_Init_atexit 析构（CRT atexit 注册器收尾）
void sub_6C0192()
{
  _Init_atexit::~_Init_atexit((_Init_atexit *)&unk_9D2585);
}



// ------------------------------------------------------------
// 0x6C0200 sub_6C0200
// ------------------------------------------------------------
// 【L1】CRT atexit 表槽位估算：((a1-3)/0xC+1) 组 → (12n - a1)/2 + 5【推断：_Init_atexit 容量】
int /*usercall*/ sub_6C0200@<eax>(int a1@<edi>)
{
  unsigned int v1; // eax

  if ( a1 - 3 >= 0 )
    v1 = (a1 - 3) / 0xCu + 1;
  else
    v1 = 0;
  return (int)(12 * v1 - a1) / 2 + 5;
}

