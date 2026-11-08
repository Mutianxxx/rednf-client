// ============================================================
// 【40JP逆向源代码工程】src/platform/d3d8_loader.cpp
// 模块: 0x68A 区 —— D3DX8 风格数学库（SSE 路径 + 3DNow! 路径）
// 来源: work/dump_tail.txt  区块: 0x68A000-0x690000
//
// 【L1 精修层】本文件已完成 L1 精修（注释级），内容:
//   1) 分区组织（3 个 SECTION：SSE 变换群 / SSE 矩阵·平面群 / 3DNow! 矩阵群）
//   2) 全部 73 函数逐个一行以上语义注释（SIMD 指纹佐证，【推断】= 无自证串）
// 函数体逻辑与 L2 转写层逐字一致，未做任何改动（剥离插入注释行可逐字节还原）。
//
// 重要定位结论（本次精修推理）:
//   - 本文件不是 d3d8.dll 的加载器，而是 **D3DX8 静态数学库本体**：
//     0x68A4B0-0x68C6BE 为 SSE(__mm128) 实现，0x68C876-0x68FF1C 为
//     3DNow!(_m_p* 指令族) 实现 —— 两套同构函数群对应同一 D3DX API 的
//     CPU 厂商双分派（D3DX8 原版即带 _X86/_SSE 双实现）。
//   - "d3d8.dll/d3d8d.dll 加载 + DebugSetMute"、"Software\Microsoft\Direct3D"
//     注册表读取、"AuthenticAMD/UnknownVendr" CPU 检测的实际函数体在
//     missing_tail.cpp 0x68 区（0x680B13 RegOpenKeyA / ~0x680B00 区
//     LoadLibraryA("d3d8.dll")→GetProcAddress("DebugSetMute") /
//     0x680134、0x680380 CPU 品牌串），计划内不精修，只在此建立交叉引用。
//   - Direct3DCreate8 导入 thunk 在 missing_tail.cpp 0x67BA36；
//     消费方: src/nengine/log_dump.cpp:8259 Direct3DCreate8(220)。
//   - 与 socket_ime.cpp SECTION 1（0x691070 3DNow! 群）同一数学库家族。
// ============================================================

#include "../../common/arad_types.h"


// ============================================================
// SECTION 1  SSE 向量/矩阵变换（D3DX 风格 · Intel/SSE 路径）
//            （0x68A4B0-0x68AFA0）
// ------------------------------------------------------------
// __m128/_mm_* 指纹；成对 float 常数 0x3F800000=1.0f。
// D3DX8 数学库的 SSE 实现：向量变换（含 1/w 透视除法 _mm_rcp_ps +
// Newton 迭代）、4 顶点批量变换、4x4 矩阵乘、sqrt 归一化（x87 标量）。
// 与 SECTION 3 的 3DNow! 群互为同构实现。
// ============================================================
// ------------------------------------------------------------
// 0x68A4B0 sub_68A4B0
// ------------------------------------------------------------
// 【L1】SSE vec4×矩阵：4x4 乘（shuffle 展开）+ 平移行（D3DXVec4Transform 形态）
__m128 */*stdcall*/ sub_68A4B0(__m128 *a1, unsigned int *a2, __m128 *a3)
{
  *a1 = _mm_add_ps(
          _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((__m128)*a2, (__m128)*a2, 0), *a3), a3[3]),
          _mm_mul_ps(_mm_shuffle_ps((__m128)a2[1], (__m128)a2[1], 0), a3[1]));
  return a1;
}



// ------------------------------------------------------------
// 0x68A4F0 sub_68A4F0
// ------------------------------------------------------------
// 【L1】SSE 变换 + 1/w 透视除法：_mm_rcp_ps + Newton 精化（D3DXVec3Project 前段形态）【推断】
double */*stdcall*/ sub_68A4F0(double *a1, unsigned int *a2, __m128 *a3)
{
  __m128 v3; // xmm2
  __m128 v4; // xmm0
  __m128 v5; // xmm1

  v3 = _mm_add_ps(
         _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((__m128)*a2, (__m128)*a2, 0), *a3), a3[3]),
         _mm_mul_ps(_mm_shuffle_ps((__m128)a2[1], (__m128)a2[1], 0), a3[1]));
  v4 = _mm_rcp_ps(v3);
  v5 = _mm_mul_ps(_mm_mul_ps(v4, v4), v3);
  _mm_storel_ps(a1, _mm_mul_ps(v3, _mm_shuffle_ps(v5, v5, 255)));
  return a1;
}



// ------------------------------------------------------------
// 0x68A550 sub_68A550
// ------------------------------------------------------------
// 【L1】SSE 变换（输出低 2 分量 = vec2 投影结果）【推断】
double */*stdcall*/ sub_68A550(double *a1, unsigned int *a2, __m128 *a3)
{
  _mm_storel_ps(
    a1,
    _mm_add_ps(
      _mm_mul_ps(_mm_shuffle_ps((__m128)*a2, (__m128)*a2, 0), *a3),
      _mm_mul_ps(_mm_shuffle_ps((__m128)a2[1], (__m128)a2[1], 0), a3[1])));
  return a1;
}



// ------------------------------------------------------------
// 0x68A59E sub_68A59E
// ------------------------------------------------------------
// 【L1】SSE 4x4 转置乘双路径：a3&0xF 判对齐/未对齐（行/列主序兼容），loadh/storeh 各 4
__m128 */*stdcall*/ sub_68A59E(__m128 *a1, __m128 *a2, int a3)
{
  if ( (a3 & 0xF) != 0 )
    *a1 = _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_loadh_ps((const double *)(a3 + 8)), _mm_shuffle_ps(*a2, *a2, 0)),
              _mm_mul_ps(_mm_loadh_ps((const double *)(a3 + 24)), _mm_shuffle_ps(*a2, *a2, 85))),
            _mm_add_ps(
              _mm_mul_ps(_mm_loadh_ps((const double *)(a3 + 40)), _mm_shuffle_ps(*a2, *a2, 170)),
              _mm_mul_ps(_mm_loadh_ps((const double *)(a3 + 56)), _mm_shuffle_ps(*a2, *a2, 255))));
  else
    *a1 = _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_shuffle_ps(*a2, *a2, 0), *(__m128 *)a3),
              _mm_mul_ps(_mm_shuffle_ps(*a2, *a2, 85), *(__m128 *)(a3 + 16))),
            _mm_add_ps(
              _mm_mul_ps(_mm_shuffle_ps(*a2, *a2, 170), *(__m128 *)(a3 + 32)),
              _mm_mul_ps(_mm_shuffle_ps(*a2, *a2, 255), *(__m128 *)(a3 + 48))));
  return a1;
}



// ------------------------------------------------------------
// 0x68A65E sub_68A65E
// ------------------------------------------------------------
// 【L1】SSE 4 顶点批量矩阵变换：loadh/storeh/storel 各 4 全展开（矩阵每列点积直证）
double */*stdcall*/ sub_68A65E(double *a1, unsigned int *a2, const double *a3)
{
  __m128 v5; // xmm3
  __m128 v6; // xmm2
  __m128 v7; // xmm1
  __m128 v8; // xmm0
  __m128 v9; // xmm4
  __m128 v10; // xmm5
  __m128 v11; // xmm6
  __m128 v12; // xmm7
  __m128 v13; // xmm2
  __m128 v14; // xmm1
  __m128 v15; // xmm7

  v5 = _mm_loadh_ps(a3 + 1);
  v6 = _mm_loadh_ps(a3 + 3);
  v7 = _mm_loadh_ps(a3 + 5);
  v8 = _mm_loadh_ps(a3 + 7);
  v9 = _mm_add_ps(
         _mm_add_ps(
           _mm_add_ps(
             _mm_mul_ps(_mm_shuffle_ps((__m128)*a2, (__m128)*a2, 0), v5),
             _mm_mul_ps(_mm_shuffle_ps((__m128)a2[1], (__m128)a2[1], 0), v6)),
           _mm_mul_ps(_mm_shuffle_ps((__m128)a2[2], (__m128)a2[2], 0), v7)),
         _mm_mul_ps(_mm_shuffle_ps((__m128)a2[3], (__m128)a2[3], 0), v8));
  v10 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_shuffle_ps((__m128)a2[4], (__m128)a2[4], 0), v5),
              _mm_mul_ps(_mm_shuffle_ps((__m128)a2[5], (__m128)a2[5], 0), v6)),
            _mm_mul_ps(_mm_shuffle_ps((__m128)a2[6], (__m128)a2[6], 0), v7)),
          _mm_mul_ps(_mm_shuffle_ps((__m128)a2[7], (__m128)a2[7], 0), v8));
  v11 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_shuffle_ps((__m128)a2[8], (__m128)a2[8], 0), v5),
              _mm_mul_ps(_mm_shuffle_ps((__m128)a2[9], (__m128)a2[9], 0), v6)),
            _mm_mul_ps(_mm_shuffle_ps((__m128)a2[10], (__m128)a2[10], 0), v7)),
          _mm_mul_ps(_mm_shuffle_ps((__m128)a2[11], (__m128)a2[11], 0), v8));
  v12 = _mm_add_ps(
          _mm_mul_ps(_mm_shuffle_ps((__m128)a2[12], (__m128)a2[12], 0), v5),
          _mm_mul_ps(_mm_shuffle_ps((__m128)a2[13], (__m128)a2[13], 0), v6));
  v13 = _mm_mul_ps(_mm_shuffle_ps((__m128)a2[14], (__m128)a2[14], 0), v7);
  v14 = (__m128)a2[15];
  _mm_storel_ps(a1, v9);
  _mm_storeh_ps(a1 + 1, v9);
  _mm_storel_ps(a1 + 2, v10);
  _mm_storeh_ps(a1 + 3, v10);
  _mm_storel_ps(a1 + 4, v11);
  _mm_storeh_ps(a1 + 5, v11);
  v15 = _mm_add_ps(_mm_add_ps(v12, v13), _mm_mul_ps(_mm_shuffle_ps(v14, v14, 0), v8));
  _mm_storel_ps(a1 + 6, v15);
  _mm_storeh_ps(a1 + 7, v15);
  return a1;
}



// ------------------------------------------------------------
// 0x68A7AE sub_68A7AE
// ------------------------------------------------------------
// 【L1】x87 标量 vec 归一化（sqrt 长度 + 除法）【推断】
float */*stdcall*/ sub_68A7AE(float *a1, float *a2)
{
  float *result; // eax
  float v3; // xmm6_4
  float v4; // xmm5_4
  float v5; // xmm3_4
  float v6; // xmm3_4
  float v7; // xmm0_4

  result = a1;
  v3 = a2[1];
  v4 = a2[2];
  v5 = (float)((float)(*a2 * *a2) + (float)(v3 * v3)) + (float)(v4 * v4);
  if ( *(float *)&dword_9D5000 <= v5 )
  {
    v6 = 1.0 / fsqrt(v5);
    v7 = (float)(*(float *)&dword_9D5004 * v6)
       * (float)(*(float *)&dword_9D5008
               - (float)((float)((float)((float)((float)(*a2 * *a2) + (float)(a2[1] * a2[1])) + (float)(a2[2] * a2[2]))
                               * v6)
                       * v6));
    *a1 = v7 * *a2;
    a1[1] = v7 * v3;
    a1[2] = v7 * v4;
  }
  else
  {
    *a1 = 0.0;
    a1[1] = 0.0;
    a1[2] = 0.0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x68A87E sub_68A87E
// ------------------------------------------------------------
// 【L1】x87 标量 vec 归一化变体（与 68A7AE 成对）【推断】
float */*stdcall*/ sub_68A87E(float *a1, float *a2)
{
  float *result; // eax
  float v3; // xmm4_4
  float v4; // xmm6_4
  float v5; // xmm3_4
  float v6; // xmm3_4
  float v7; // xmm0_4

  result = a1;
  v3 = a2[1];
  v4 = a2[2];
  v5 = (float)((float)(*a2 * *a2) + (float)(v3 * v3)) + (float)(v4 * v4);
  if ( *(float *)&dword_9D500C <= v5 )
  {
    v6 = 1.0 / fsqrt(v5);
    v7 = (float)(*(float *)&dword_9D5010 * v6)
       * (float)(*(float *)&dword_9D5014
               - (float)((float)((float)((float)((float)(*a2 * *a2) + (float)(a2[1] * a2[1])) + (float)(a2[2] * a2[2]))
                               * v6)
                       * v6));
    *a1 = v7 * *a2;
    a1[1] = v7 * v3;
    a1[2] = v7 * v4;
    a1[3] = v7 * a2[3];
  }
  else
  {
    *a1 = 0.0;
    a1[1] = 0.0;
    a1[2] = 0.0;
    a1[3] = 0.0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x68A95E sub_68A95E
// ------------------------------------------------------------
// 【L1】SSE 矩阵×矩阵（4x4 乘，loadh×3 重组）【推断】
__m128 */*stdcall*/ sub_68A95E(__m128 *a1, int a2, int a3, int a4)
{
  __m128 v5; // xmm2
  __m128 v6; // xmm2
  __m128 v7; // xmm1
  __m128 v8; // xmm3
  __m128 v9; // xmm4
  __m128 v10; // xmm0
  __m128 v11; // xmm4
  __m128 v12; // xmm2
  __m128 v13; // xmm3
  __m128 v14; // xmm1

  v5 = _mm_loadh_ps((const double *)(a3 + 8));
  v6 = _mm_shuffle_ps(v5, v5, 57);
  v7 = _mm_loadh_ps((const double *)(a2 + 8));
  v8 = _mm_loadh_ps((const double *)(a4 + 8));
  v9 = _mm_shuffle_ps(v8, v8, 78);
  v10 = _mm_mul_ps(_mm_shuffle_ps(v9, v9, 57), v6);
  v11 = _mm_mul_ps(v9, v6);
  v12 = _mm_mul_ps(v6, v8);
  v13 = _mm_shuffle_ps(v7, v7, 57);
  v14 = _mm_shuffle_ps(v13, v13, 57);
  *a1 = _mm_xor_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(v13, _mm_sub_ps(_mm_shuffle_ps(v11, v11, 57), _mm_shuffle_ps(v12, v12, 78))),
              _mm_mul_ps(_mm_sub_ps(_mm_shuffle_ps(v10, v10, 78), v10), v14)),
            _mm_mul_ps(_mm_shuffle_ps(v14, v14, 57), _mm_sub_ps(v11, _mm_shuffle_ps(v12, v12, 57)))),
          (__m128)xmmword_79A280);
  return a1;
}



// ------------------------------------------------------------
// 0x68AA00 sub_68AA00
// ------------------------------------------------------------
// 【L1】x87 标量归一化变体【推断】
float */*stdcall*/ sub_68AA00(float *a1, float *a2)
{
  float v2; // xmm1_4
  float v3; // xmm2_4
  float v4; // xmm3_4
  float v5; // xmm4_4
  float v6; // xmm6_4
  float v7; // xmm5_4

  v2 = a2[1];
  v3 = a2[2];
  v4 = a2[3];
  v5 = (float)((float)(*a2 * *a2) + (float)(v2 * v2)) + (float)((float)(v3 * v3) + (float)(v4 * v4));
  v6 = 1.0 / fsqrt(v5);
  v7 = (float)((float)(*(float *)&dword_79A2A0 - (float)(v5 * (float)(v6 * v6))) * *(float *)&dword_79A290) * v6;
  *a1 = *a2 * v7;
  a1[1] = v2 * v7;
  a1[2] = v3 * v7;
  a1[3] = v4 * v7;
  return a1;
}



// ------------------------------------------------------------
// 0x68AAA0 sub_68AAA0
// ------------------------------------------------------------
// 【L1】SSE userpurge 变换（xmm 寄存器传参，编译器内联形态）【推断】
int /*userpurge*/ sub_68AAA0@<eax>(
        __m128 a1@<xmm1>,
        __m128 a2@<xmm2>,
        int a3,
        const double *a4,
        const double *a5,
        const double *a6,
        const double *a7,
        float a8)
{
  __m128 v8; // xmm0
  __m128 v9; // xmm0
  __m128 v10; // xmm4

  v8 = (__m128)LODWORD(a8);
  a1.m128_f32[0] = v8.m128_f32[0] * v8.m128_f32[0];
  a2.m128_f32[0] = a8 * (float)(v8.m128_f32[0] * v8.m128_f32[0]);
  v9 = _mm_add_ps(
         _mm_add_ps(
           _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v8, v8, 0), (__m128)xmmword_79A2E0), (__m128)xmmword_79A2C0),
           _mm_mul_ps(_mm_shuffle_ps(a1, a1, 0), (__m128)xmmword_79A2D0)),
         _mm_mul_ps(_mm_shuffle_ps(a2, a2, 0), (__m128)xmmword_79A2B0));
  v10 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_loadh_ps(a4), _mm_shuffle_ps(v9, v9, 0)),
              _mm_mul_ps(_mm_loadh_ps(a5), _mm_shuffle_ps(v9, v9, 85))),
            _mm_mul_ps(_mm_loadh_ps(a6), _mm_shuffle_ps(v9, v9, 170))),
          _mm_mul_ps(_mm_loadh_ps(a7), _mm_shuffle_ps(v9, v9, 255)));
  _mm_storeh_ps((double *)a3, v10);
  *(uint32_t *)(a3 + 8) = v10.m128_i32[0];
  return a3;
}



// ------------------------------------------------------------
// 0x68AB60 sub_68AB60
// ------------------------------------------------------------
// 【L1】SSE userpurge 变换变体【推断】
double */*userpurge*/ sub_68AB60@<eax>(
        __m128 a1@<xmm1>,
        __m128 a2@<xmm2>,
        double *a3,
        int a4,
        const double *a5,
        int a6,
        const double *a7,
        float a8)
{
  __m128 v8; // xmm0
  __m128 v9; // xmm0
  __m128 v10; // xmm6
  __m128 v11; // xmm4

  v8 = (__m128)LODWORD(a8);
  a1.m128_f32[0] = v8.m128_f32[0] * v8.m128_f32[0];
  a2.m128_f32[0] = a8 * (float)(v8.m128_f32[0] * v8.m128_f32[0]);
  v9 = _mm_add_ps(
         _mm_add_ps(
           _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v8, v8, 0), (__m128)xmmword_79A2E0), (__m128)xmmword_79A2C0),
           _mm_mul_ps(_mm_shuffle_ps(a1, a1, 0), (__m128)xmmword_79A2D0)),
         _mm_mul_ps(_mm_shuffle_ps(a2, a2, 0), (__m128)xmmword_79A2B0));
  v10 = _mm_mul_ps(_mm_loadh_ps(a7), _mm_shuffle_ps(v9, v9, 250));
  v11 = _mm_add_ps(_mm_mul_ps(_mm_loadh_ps(a5), _mm_shuffle_ps(v9, v9, 80)), v10);
  _mm_storel_ps(a3, _mm_add_ps(v11, _mm_movehl_ps(v10, v11)));
  return a3;
}



// ------------------------------------------------------------
// 0x68ABF0 sub_68ABF0
// ------------------------------------------------------------
// 【L1】SSE userpurge 变换变体【推断】
__m128 */*userpurge*/ sub_68ABF0@<eax>(
        __m128 a1@<xmm1>,
        __m128 a2@<xmm2>,
        __m128 *a3,
        __m128 *a4,
        __m128 *a5,
        __m128 *a6,
        __m128 *a7,
        float a8)
{
  __m128 v8; // xmm0
  __m128 v9; // xmm0

  v8 = (__m128)LODWORD(a8);
  a1.m128_f32[0] = v8.m128_f32[0] * v8.m128_f32[0];
  a2.m128_f32[0] = a8 * (float)(v8.m128_f32[0] * v8.m128_f32[0]);
  v9 = _mm_add_ps(
         _mm_add_ps(
           _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v8, v8, 0), (__m128)xmmword_79A2E0), (__m128)xmmword_79A2C0),
           _mm_mul_ps(_mm_shuffle_ps(a1, a1, 0), (__m128)xmmword_79A2D0)),
         _mm_mul_ps(_mm_shuffle_ps(a2, a2, 0), (__m128)xmmword_79A2B0));
  *a3 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(_mm_mul_ps(*a4, _mm_shuffle_ps(v9, v9, 0)), _mm_mul_ps(*a5, _mm_shuffle_ps(v9, v9, 85))),
            _mm_mul_ps(*a6, _mm_shuffle_ps(v9, v9, 170))),
          _mm_mul_ps(*a7, _mm_shuffle_ps(v9, v9, 255)));
  return a3;
}



// ------------------------------------------------------------
// 0x68ACA0 sub_68ACA0
// ------------------------------------------------------------
// 【L1】SSE userpurge 变换变体【推断】
int /*userpurge*/ sub_68ACA0@<eax>(
        __m128 a1@<xmm1>,
        __m128 a2@<xmm2>,
        int a3,
        const double *a4,
        const double *a5,
        const double *a6,
        const double *a7,
        float a8)
{
  __m128 v8; // xmm0
  __m128 v9; // xmm0
  __m128 v10; // xmm0
  __m128 v11; // xmm4

  v8 = (__m128)LODWORD(a8);
  a1.m128_f32[0] = v8.m128_f32[0] * v8.m128_f32[0];
  a2.m128_f32[0] = a8 * (float)(v8.m128_f32[0] * v8.m128_f32[0]);
  v9 = _mm_mul_ps(_mm_shuffle_ps(v8, v8, 0), (__m128)xmmword_79A320);
  v9.m128_f32[0] = v9.m128_f32[0] + *(float *)&dword_79A300;
  v10 = _mm_add_ps(
          _mm_add_ps(v9, _mm_mul_ps(_mm_shuffle_ps(a1, a1, 0), (__m128)xmmword_79A310)),
          _mm_mul_ps(_mm_shuffle_ps(a2, a2, 0), (__m128)xmmword_79A2F0));
  v11 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_loadh_ps(a4), _mm_shuffle_ps(v10, v10, 0)),
              _mm_mul_ps(_mm_loadh_ps(a5), _mm_shuffle_ps(v10, v10, 85))),
            _mm_mul_ps(_mm_loadh_ps(a6), _mm_shuffle_ps(v10, v10, 170))),
          _mm_mul_ps(_mm_loadh_ps(a7), _mm_shuffle_ps(v10, v10, 255)));
  _mm_storeh_ps((double *)a3, v11);
  *(uint32_t *)(a3 + 8) = v11.m128_i32[0];
  return a3;
}



// ------------------------------------------------------------
// 0x68AD60 sub_68AD60
// ------------------------------------------------------------
// 【L1】SSE userpurge 变换变体【推断】
__m128 */*userpurge*/ sub_68AD60@<eax>(
        __m128 a1@<xmm1>,
        __m128 a2@<xmm2>,
        __m128 *a3,
        __m128 *a4,
        __m128 *a5,
        __m128 *a6,
        __m128 *a7,
        float a8)
{
  __m128 v8; // xmm0
  __m128 v9; // xmm0
  __m128 v10; // xmm0

  v8 = (__m128)LODWORD(a8);
  a1.m128_f32[0] = v8.m128_f32[0] * v8.m128_f32[0];
  a2.m128_f32[0] = a8 * (float)(v8.m128_f32[0] * v8.m128_f32[0]);
  v9 = _mm_mul_ps(_mm_shuffle_ps(v8, v8, 0), (__m128)xmmword_79A320);
  v9.m128_f32[0] = v9.m128_f32[0] + *(float *)&dword_79A300;
  v10 = _mm_add_ps(
          _mm_add_ps(v9, _mm_mul_ps(_mm_shuffle_ps(a1, a1, 0), (__m128)xmmword_79A310)),
          _mm_mul_ps(_mm_shuffle_ps(a2, a2, 0), (__m128)xmmword_79A2F0));
  *a3 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(_mm_mul_ps(*a4, _mm_shuffle_ps(v10, v10, 0)), _mm_mul_ps(*a5, _mm_shuffle_ps(v10, v10, 85))),
            _mm_mul_ps(*a6, _mm_shuffle_ps(v10, v10, 170))),
          _mm_mul_ps(*a7, _mm_shuffle_ps(v10, v10, 255)));
  return a3;
}



// ------------------------------------------------------------
// 0x68AE00 sub_68AE00
// ------------------------------------------------------------
// 【L1】SSE userpurge 变换变体【推断】
double */*userpurge*/ sub_68AE00@<eax>(
        __m128 a1@<xmm1>,
        __m128 a2@<xmm2>,
        __m128 a3@<xmm3>,
        double *a4,
        int a5,
        const double *a6,
        int a7,
        const double *a8,
        float a9)
{
  __m128 v9; // xmm0
  __m128 v10; // xmm0
  __m128 v11; // xmm0
  __m128 v12; // xmm4

  v9 = (__m128)LODWORD(a9);
  a1.m128_f32[0] = v9.m128_f32[0] * v9.m128_f32[0];
  a2.m128_f32[0] = a9 * (float)(v9.m128_f32[0] * v9.m128_f32[0]);
  v10 = _mm_mul_ps(_mm_shuffle_ps(v9, v9, 0), (__m128)xmmword_79A320);
  v10.m128_f32[0] = v10.m128_f32[0] + *(float *)&dword_79A300;
  v11 = _mm_add_ps(
          _mm_add_ps(v10, _mm_mul_ps(_mm_shuffle_ps(a1, a1, 0), (__m128)xmmword_79A310)),
          _mm_mul_ps(_mm_shuffle_ps(a2, a2, 0), (__m128)xmmword_79A2F0));
  v12 = _mm_add_ps(
          _mm_mul_ps(_mm_loadh_ps(a6), _mm_shuffle_ps(v11, v11, 80)),
          _mm_mul_ps(_mm_loadh_ps(a8), _mm_shuffle_ps(v11, v11, 250)));
  _mm_storel_ps(a4, _mm_add_ps(v12, _mm_movehl_ps(a3, v12)));
  return a4;
}



// ------------------------------------------------------------
// 0x68AE90 sub_68AE90
// ------------------------------------------------------------
// 【L1】SSE 矩阵装配/设置（shuffle×2，双精度入参）【推断】
int /*stdcall*/ sub_68AE90(
        int a1,
        const double *a2,
        const double *a3,
        const double *a4,
        unsigned int a5,
        unsigned int a6)
{
  __m128 v6; // xmm2
  __m128 v7; // xmm3

  v6 = _mm_loadh_ps(a2);
  v7 = _mm_add_ps(
         _mm_add_ps(_mm_mul_ps(_mm_sub_ps(_mm_loadh_ps(a3), v6), _mm_shuffle_ps((__m128)a5, (__m128)a5, 0)), v6),
         _mm_mul_ps(_mm_sub_ps(_mm_loadh_ps(a4), v6), _mm_shuffle_ps((__m128)a6, (__m128)a6, 0)));
  *(uint32_t *)(a1 + 8) = v7.m128_i32[0];
  _mm_storeh_ps((double *)a1, v7);
  return a1;
}



// ------------------------------------------------------------
// 0x68AEF0 sub_68AEF0
// ------------------------------------------------------------
// 【L1】SSE 4x4 矩阵乘（紧凑 13 行，D3DXMatrixMultiply 形态）【推断】
__m128 */*stdcall*/ sub_68AEF0(__m128 *a1, __m128 *a2, __m128 *a3, __m128 *a4, unsigned int a5, unsigned int a6)
{
  *a1 = _mm_add_ps(
          _mm_add_ps(_mm_mul_ps(_mm_sub_ps(*a3, *a2), _mm_shuffle_ps((__m128)a5, (__m128)a5, 0)), *a2),
          _mm_mul_ps(_mm_sub_ps(*a4, *a2), _mm_shuffle_ps((__m128)a6, (__m128)a6, 0)));
  return a1;
}



// ------------------------------------------------------------
// 0x68AF40 sub_68AF40
// ------------------------------------------------------------
// 【L1】双精度包装：同 68AEF0 的 double 接口形态【推断】
double */*stdcall*/ sub_68AF40(
        double *a1,
        const double *a2,
        const double *a3,
        const double *a4,
        unsigned int a5,
        unsigned int a6)
{
  __m128 v6; // xmm2

  v6 = _mm_loadh_ps(a2);
  _mm_storeh_ps(
    a1,
    _mm_add_ps(
      _mm_add_ps(_mm_mul_ps(_mm_sub_ps(_mm_loadh_ps(a3), v6), _mm_shuffle_ps((__m128)a5, (__m128)a5, 0)), v6),
      _mm_mul_ps(_mm_sub_ps(_mm_loadh_ps(a4), v6), _mm_shuffle_ps((__m128)a6, (__m128)a6, 0))));
  return a1;
}



// ------------------------------------------------------------
// 0x68AFA0 sub_68AFA0
// ------------------------------------------------------------
// 【L1】SSE userpurge 大变换（xmm5/xmm6 传参）【推断】
int /*userpurge*/ sub_68AFA0@<eax>(
        __m128 a1@<xmm5>,
        __m128 a2@<xmm6>,
        int a3,
        __m128 *a4,
        const double *a5,
        const double *a6)
{
  __m128 v6; // xmm1
  __m128 v7; // xmm4
  __m128 v8; // xmm0
  __m128 v9; // xmm2
  __m128 v10; // xmm3
  __m128 v11; // xmm0
  __m128 v12; // xmm5
  __m128 v13; // xmm6
  __m128 v14; // xmm0
  float v15; // xmm5_4
  __m128 v16; // xmm3
  __m128 v17; // xmm1
  int v19; // [esp+0h] [ebp-4h]

  v19 = a3;
  v6 = _mm_loadh_ps(a5);
  v7 = *a4;
  v8 = _mm_shuffle_ps(v7, v7, 78);
  v9 = _mm_loadh_ps(a6);
  v10 = _mm_mul_ps(v6, v8);
  v11 = _mm_mul_ps(v8, v9);
  v12 = _mm_movehl_ps(a1, v10);
  v13 = _mm_movehl_ps(a2, v11);
  v16 = _mm_add_ps(v10, v12);
  v14 = _mm_add_ps(v11, v13);
  v16.m128_f32[0] = v16.m128_f32[0] + _mm_shuffle_ps(v12, v16, 85).m128_f32[0];
  v15 = v16.m128_f32[0] - (float)(v14.m128_f32[0] + _mm_shuffle_ps(v13, v14, 85).m128_f32[0]);
  v16.m128_f32[0] = v16.m128_f32[0] + _mm_shuffle_ps(v7, v7, 255).m128_f32[0];
  if ( v15 == *(float *)&dword_9D3740 )
    return 0;
  v16.m128_f32[0] = v16.m128_f32[0]
                  * (float)((float)((float)(1.0 / v15) + (float)(1.0 / v15))
                          - (float)((float)(v15 * (float)(1.0 / v15)) * (float)(1.0 / v15)));
  v17 = _mm_add_ps(v6, _mm_mul_ps(_mm_shuffle_ps(v16, v16, 0), _mm_sub_ps(v9, v6)));
  _mm_storeh_ps((double *)a3, v17);
  *(uint32_t *)(a3 + 8) = v17.m128_i32[0];
  return v19;
}




// ============================================================
// SECTION 2  SSE 矩阵运算/平面/透视（0x68B06E-0x68C6BE）
// ------------------------------------------------------------
// 平面归一化(sqrt)、透视投影(rcp)/反投影、4x4 矩阵求逆
// （0x68BC5E 伴随式 169 行巨型）、批量转置乘（0x68BF1E）。
// ============================================================
// ------------------------------------------------------------
// 0x68B06E sub_68B06E
// ------------------------------------------------------------
// 【L1】SSE 矩阵×向量展开（4 列点积，D3DXVec3Transform 形态）【推断】
double /*stdcall*/ sub_68B06E(int a1)
{
  __m128 v1; // xmm7
  __m128 v2; // xmm1
  __m128 v3; // xmm2
  __m128 v4; // xmm0
  __m128 v5; // xmm2
  __m128 v6; // xmm3
  __m128 v7; // xmm4
  __m128 v8; // xmm0
  __m128 v9; // xmm4
  __m128 v10; // xmm0
  __m128 v11; // xmm2
  __m128 v12; // xmm0
  __m128 v13; // xmm1
  __m128 v14; // xmm1
  __m128 v15; // xmm0

  if ( (a1 & 0xF) != 0 )
  {
    v2 = _mm_loadh_ps((const double *)(a1 + 24));
    v1 = _mm_loadh_ps((const double *)(a1 + 8));
    v3 = _mm_loadh_ps((const double *)(a1 + 40));
    v4 = _mm_loadh_ps((const double *)(a1 + 56));
  }
  else
  {
    v1 = *(__m128 *)a1;
    v2 = *(__m128 *)(a1 + 16);
    v3 = *(__m128 *)(a1 + 32);
    v4 = *(__m128 *)(a1 + 48);
  }
  v5 = _mm_shuffle_ps(v3, v3, 57);
  v6 = _mm_mul_ps(v4, v5);
  v7 = _mm_shuffle_ps(v4, v4, 78);
  v8 = _mm_shuffle_ps(v7, v7, 57);
  v9 = _mm_mul_ps(v7, v5);
  v10 = _mm_mul_ps(v5, v8);
  v11 = _mm_sub_ps(_mm_shuffle_ps(v10, v10, 78), v10);
  v12 = _mm_shuffle_ps(v2, v2, 57);
  v13 = _mm_shuffle_ps(v12, v12, 57);
  v14 = _mm_mul_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(v12, _mm_sub_ps(_mm_shuffle_ps(v9, v9, 57), _mm_shuffle_ps(v6, v6, 78))),
              _mm_mul_ps(v11, v13)),
            _mm_mul_ps(_mm_shuffle_ps(v13, v13, 57), _mm_sub_ps(v9, _mm_shuffle_ps(v6, v6, 57)))),
          v1);
  v15 = _mm_add_ps(v14, _mm_movehl_ps(v14, v14));
  return (float)(v15.m128_f32[0] - _mm_shuffle_ps(v15, v15, 1).m128_f32[0]);
}



// ------------------------------------------------------------
// 0x68B13E sub_68B13E
// ------------------------------------------------------------
// 【L1】SSE 平面归一化（sqrt 长度 + 全分量除，D3DXPlaneNormalize 形态）【推断】
__m128 */*stdcall*/ sub_68B13E(__m128 *a1, const double *a2, const double *a3, const double *a4)
{
  __m128 v5; // xmm3
  __m128 v6; // xmm1
  __m128 v7; // xmm0
  __m128 v8; // xmm4
  __m128 v9; // xmm5
  __m128 v10; // xmm3
  __m128 v11; // xmm5
  __m128 v12; // xmm1
  __m128 v13; // xmm3
  __m128 v14; // xmm5
  __m128 v15; // xmm0
  __m128 v16; // xmm5
  __m128 v17; // xmm3
  __m128 v18; // xmm0

  v5 = _mm_loadh_ps(a2);
  v6 = _mm_sub_ps(v5, _mm_loadh_ps(a4));
  v7 = _mm_shuffle_ps(v6, v6, 120);
  v8 = v5;
  v9 = _mm_sub_ps(v5, _mm_loadh_ps(a3));
  v10 = _mm_shuffle_ps(v9, v9, 99);
  v11 = _mm_mul_ps(_mm_shuffle_ps(v9, v9, 120), _mm_shuffle_ps(v6, v6, 99));
  v12 = (__m128)xmmword_79A350;
  v13 = _mm_sub_ps(_mm_mul_ps(v7, v10), v11);
  v14 = _mm_mul_ps(v13, v13);
  v15 = _mm_add_ps(v14, _mm_movehl_ps(v14, v14));
  v15.m128_f32[0] = v15.m128_f32[0] + _mm_shuffle_ps(v15, v15, 1).m128_f32[0];
  v16 = v15;
  v15.m128_f32[0] = fsqrt(v15.m128_f32[0]);
  v12.m128_f32[0] = (float)(*(float *)&xmmword_79A350 * (float)(1.0 / v15.m128_f32[0]))
                  * (float)(*(float *)&xmmword_79A340
                          - (float)((float)(v16.m128_f32[0] * (float)(1.0 / v15.m128_f32[0]))
                                  * (float)(1.0 / v15.m128_f32[0])));
  v17 = _mm_mul_ps(v13, _mm_shuffle_ps(v12, v12, 0));
  *a1 = v17;
  v18 = _mm_mul_ps(_mm_shuffle_ps(v8, v8, 14), v17);
  a1->m128_i32[3] = COERCE_UNSIGNED_INT(
                      v18.m128_f32[0]
                    + (float)(_mm_movehl_ps(v16, v18).m128_f32[0] + _mm_shuffle_ps(v18, v18, 85).m128_f32[0]))
                  ^ xmmword_79A330;
  return a1;
}



// ------------------------------------------------------------
// 0x68B22E sub_68B22E
// ------------------------------------------------------------
// 【L1】SSE 平面变换 + 归一化（98 行，D3DXPlaneTransform 形态）【推断】
double */*stdcall*/ sub_68B22E(double *a1, __m128 *a2, __m128 *a3)
{
  __m128 v3; // xmm2
  __m128 v4; // xmm3
  __m128 v5; // xmm3
  __m128 v6; // xmm1
  __m128 v7; // xmm0
  char v8; // al
  __m128 v9; // xmm4
  float v10; // xmm3_4
  float v11; // xmm5_4
  double *result; // eax
  __m128 v13; // xmm4
  __m128 v14; // xmm0
  __m128 v15; // xmm0
  __m128 v16; // xmm0
  __m128 v17; // xmm5
  __m128 v18; // xmm6
  float v19; // xmm7_4
  __m128 v20; // xmm0
  __m128 v21; // xmm1
  __m128 v22; // xmm2
  __m128 v23; // xmm3

  v3 = *a3;
  v4 = _mm_and_ps((__m128)xmmword_79A3A0, *a3);
  v5 = _mm_mul_ps(v4, v4);
  v6 = _mm_add_ps(v5, _mm_movehl_ps((__m128)0LL, v5));
  v7 = _mm_shuffle_ps(v6, v6, 1);
  v7.m128_f32[0] = v7.m128_f32[0] + v6.m128_f32[0];
  if ( v7.m128_f32[0] != 0.0 )
  {
    v8 = byte_9D4FE0;
    if ( (byte_9D4FE0 & 1) != 0 )
    {
      v9 = (__m128)xmmword_9D4FC0;
    }
    else
    {
      v8 = byte_9D4FE0 | 1;
      v9 = (__m128)(unsigned int)dword_9D50C0;
      byte_9D4FE0 |= 1u;
      xmmword_9D4FC0 = (unsigned int)dword_9D50C0;
    }
    if ( (v8 & 2) != 0 )
    {
      v10 = *(float *)&xmmword_9D4FD0;
    }
    else
    {
      v10 = *(float *)&dword_9D50C4;
      byte_9D4FE0 = v8 | 2;
      xmmword_9D4FD0 = (unsigned int)dword_9D50C4;
    }
    v11 = 1.0 / fsqrt(v7.m128_f32[0]);
    v9.m128_f32[0] = (float)(v9.m128_f32[0] * v11) * (float)(v10 - (float)((float)(v7.m128_f32[0] * v11) * v11));
    v7 = _mm_mul_ps(v3, _mm_shuffle_ps(v9, v9, 0));
  }
  result = a1;
  v13 = _mm_xor_ps((__m128)xmmword_79A360, v7);
  v14 = _mm_mul_ps(v7, *a2);
  v15 = _mm_add_ps(v14, _mm_movehl_ps(v6, v14));
  v15.m128_f32[0] = v15.m128_f32[0] + _mm_shuffle_ps(v15, v15, 1).m128_f32[0];
  v16 = _mm_shuffle_ps(v15, v15, 0);
  v17 = _mm_and_ps((__m128)xmmword_79A380, v16);
  v18 = _mm_and_ps((__m128)xmmword_79A390, v16);
  v19 = v16.m128_f32[0];
  v20 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v13, v13, 85), *a2), _mm_and_ps((__m128)xmmword_79A370, v16));
  v21 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v13, v13, 170), *a2), v17);
  v23 = _mm_mul_ps(_mm_shuffle_ps(v13, v13, 0), *a2);
  v22 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v13, v13, 255), *a2), v18);
  v23.m128_f32[0] = v23.m128_f32[0] + v19;
  if ( ((uint8_t)a1 & 0xF) != 0 )
  {
    _mm_storel_ps(a1, v23);
    _mm_storeh_ps(a1 + 1, v23);
    _mm_storel_ps(a1 + 2, v20);
    _mm_storeh_ps(a1 + 3, v20);
    _mm_storel_ps(a1 + 4, v21);
    _mm_storeh_ps(a1 + 5, v21);
    _mm_storel_ps(a1 + 6, v22);
    _mm_storeh_ps(a1 + 7, v22);
  }
  else
  {
    *(__m128 *)a1 = v23;
    *((__m128 *)a1 + 1) = v20;
    *((__m128 *)a1 + 2) = v21;
    *((__m128 *)a1 + 3) = v22;
  }
  return result;
}



// ------------------------------------------------------------
// 0x68B3BE sub_68B3BE
// ------------------------------------------------------------
// 【L1】SSE sqrt 归一化变体【推断】
__m128 */*stdcall*/ sub_68B3BE(__m128 *a1, const double *a2)
{
  __m128 v3; // xmm1
  __m128 v4; // xmm0
  __m128 v5; // xmm3
  __m128 v6; // xmm4
  __m128 v7; // xmm0
  float v8; // xmm5_4
  __m128 v9; // xmm1
  __m128 v10; // xmm4
  __m128 v11; // xmm0
  __m128 v12; // xmm1
  __m128 v13; // xmm2
  __m128 v14; // xmm0
  __m128 v15; // xmm3
  __m128 v16; // xmm2
  __m128 v17; // xmm4

  v3 = _mm_loadl_ps(a2);
  v4 = _mm_and_ps((__m128)xmmword_79A420, v3);
  v5 = (__m128)(unsigned int)dword_79A410;
  v6 = _mm_mul_ps(v4, v4);
  v7 = _mm_add_ps(v6, _mm_movehl_ps(v6, v6));
  v8 = v7.m128_f32[0] + _mm_shuffle_ps(v7, v7, 1).m128_f32[0];
  v7.m128_f32[0] = 1.0 / fsqrt(v8);
  v5.m128_f32[0] = (float)(*(float *)&dword_79A410 * v7.m128_f32[0])
                 * (float)(*(float *)&dword_79A400 - (float)((float)(v8 * v7.m128_f32[0]) * v7.m128_f32[0]));
  v9 = _mm_mul_ps(v3, _mm_shuffle_ps(v5, v5, 0));
  v10 = _mm_mul_ps((__m128)xmmword_79A3F0, v9);
  v11 = v9;
  v12 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v9, v9, 0), v10), (__m128)xmmword_79A3E0);
  v13 = v11;
  v14 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v11, v11, 255), v10), (__m128)xmmword_79A3B0);
  v15 = v13;
  v16 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v13, v13, 170), v10), (__m128)xmmword_79A3C0);
  v17 = _mm_add_ps(_mm_mul_ps(v10, _mm_shuffle_ps(v15, v15, 85)), (__m128)xmmword_79A3D0);
  *a1 = v12;
  a1[1] = v17;
  a1[2] = v16;
  a1[3] = v14;
  return a1;
}



// ------------------------------------------------------------
// 0x68B490 sub_68B490
// ------------------------------------------------------------
// 【L1】SSE 变换小函数【推断】
double */*stdcall*/ sub_68B490(double *a1, int a2, int a3)
{
  __m128 v3; // xmm0
  __m128 v4; // xmm2
  __m128 v5; // xmm1
  __m128 v6; // xmm0
  __m128 v7; // xmm1
  __m128 v8; // xmm0
  __m128 v9; // xmm1

  v3 = _mm_loadh_ps((const double *)(a2 + 8));
  v4 = _mm_loadh_ps((const double *)(a3 + 8));
  v5 = _mm_mul_ps(_mm_shuffle_ps(v4, v4, 255), v3);
  v6 = _mm_shuffle_ps(v3, v3, 27);
  v7 = _mm_add_ps(v5, _mm_mul_ps(_mm_xor_ps(_mm_shuffle_ps(v4, v4, 0), (__m128)xmmword_9D5100), v6));
  v8 = _mm_shuffle_ps(v6, v6, 177);
  v9 = _mm_add_ps(
         _mm_add_ps(v7, _mm_mul_ps(_mm_xor_ps(_mm_shuffle_ps(v4, v4, 85), (__m128)xmmword_9D50F0), v8)),
         _mm_mul_ps(_mm_xor_ps(_mm_shuffle_ps(v4, v4, 170), (__m128)xmmword_9D50E0), _mm_shuffle_ps(v8, v8, 27)));
  _mm_storel_ps(a1, v9);
  _mm_storeh_ps(a1 + 1, v9);
  return a1;
}



// ------------------------------------------------------------
// 0x68B520 sub_68B520
// ------------------------------------------------------------
// 【L1】x87 标量 sqrt 归一化变体【推断】
float */*stdcall*/ sub_68B520(float *a1, float *a2)
{
  float v2; // xmm1_4
  float v3; // xmm2_4
  float v4; // xmm3_4
  float v5; // xmm4_4
  float v6; // xmm6_4
  float v7; // xmm5_4

  v2 = a2[1];
  v3 = a2[2];
  v4 = a2[3];
  v5 = (float)((float)(*a2 * *a2) + (float)(v2 * v2)) + (float)((float)(v3 * v3) + (float)(v4 * v4));
  v6 = 1.0 / fsqrt(v5);
  v7 = (float)((float)(*(float *)&dword_79A450 - (float)(v5 * (float)(v6 * v6))) * *(float *)&dword_79A440) * v6;
  *a1 = *a2 * v7;
  a1[1] = v2 * v7;
  a1[2] = v3 * v7;
  a1[3] = v4 * v7;
  return a1;
}



// ------------------------------------------------------------
// 0x68B5CE sub_68B5CE
// ------------------------------------------------------------
// 【L1】SSE 小型矩阵/向量操作【推断】
__m128 */*stdcall*/ sub_68B5CE(__m128 *a1, int a2)
{
  __m128 v3; // xmm1
  __m128 v4; // xmm2
  __m128 v5; // xmm0
  __m128 v6; // xmm3

  v3 = _mm_loadh_ps((const double *)(a2 + 8));
  v4 = _mm_mul_ps(v3, v3);
  v5 = _mm_add_ps(v4, _mm_movehl_ps(v4, v4));
  v4.m128_f32[0] = v5.m128_f32[0] + _mm_shuffle_ps(v5, v5, 85).m128_f32[0];
  v5.m128_f32[0] = 1.0 / v4.m128_f32[0];
  v6 = v5;
  v6.m128_f32[0] = (float)(v6.m128_f32[0] + v6.m128_f32[0])
                 - (float)((float)(v5.m128_f32[0] * v4.m128_f32[0]) * v5.m128_f32[0]);
  *a1 = _mm_mul_ps(_mm_mul_ps(v3, (__m128)xmmword_79A460), _mm_shuffle_ps(v6, v6, 0));
  return a1;
}



// ------------------------------------------------------------
// 0x68B630 sub_68B630
// ------------------------------------------------------------
// 【L1】x87 标量双 sqrt（距离/长度计算）【推断】
float */*stdcall*/ sub_68B630(float *a1, float *a2)
{
  float *result; // eax
  double v3; // st7
  float v4; // edi
  float v5; // esi
  int v6; // ebp
  double v7; // st7
  int v8; // ecx
  int v9; // ebx
  int v10; // ebp
  float *v11; // esi
  long double v12; // st6
  long double v13; // st7
  float *v14; // ecx
  long double v15; // st6
  long double v16; // st7
  uint32_t v17[7]; // [esp+0h] [ebp-1Ch]

  result = a1;
  v3 = *a2 + a2[5] + a2[10];
  v4 = *a2;
  v5 = a2[5];
  v6 = *((uint32_t *)a2 + 10);
  if ( flt_9D511C < v3 )
  {
    v15 = sqrt(v3 + flt_9D5120) * flt_9D5124;
    v16 = flt_9D5128 / v15;
    a1[3] = v15;
    *a1 = (a2[6] - a2[9]) * v16;
    a1[1] = (a2[8] - a2[2]) * v16;
    a1[2] = v16 * (a2[1] - a2[4]);
  }
  else
  {
    v7 = a2[10];
    *(float *)v17 = *a2;
    *(float *)&v17[1] = v5;
    v17[2] = v6;
    v8 = 2;
    if ( *(float *)&v17[v5 > (double)v4] >= v7 )
      v8 = v5 > (double)v4;
    v9 = dword_9D5110[v8];
    v10 = dword_9D5110[v9];
    v11 = &a2[v8];
    v12 = sqrt(flt_9D5130 + *(float *)&v17[v8] - *(float *)&v17[v9] - *(float *)&v17[v10]) * flt_9D5134;
    v13 = flt_9D5138 / v12;
    a1[v8] = v12;
    v14 = &a2[4 * v8];
    a1[v9] = (v14[v9] + v11[4 * v9]) * v13;
    a1[v10] = (v11[4 * v10] + v14[v10]) * v13;
    a1[3] = v13 * (a2[4 * v9 + v10] - a2[4 * v10 + v9]);
  }
  return result;
}



// ------------------------------------------------------------
// 0x68B75E sub_68B75E
// ------------------------------------------------------------
// 【L1】SSE 变换（shuffle×9 重组）【推断】
__m128 */*stdcall*/ sub_68B75E(__m128 *a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
  __m128 v4; // xmm0
  __m128 v5; // xmm1
  __m128 v6; // xmm3
  __m128 v7; // xmm2
  __m128 v8; // xmm3
  __m128 v10; // [esp+10h] [ebp-4Ch] BYREF
  __m128 v11[3]; // [esp+20h] [ebp-3Ch] BYREF

  v10 = _mm_mul_ps(
          _mm_shuffle_ps(
            _mm_unpacklo_ps((__m128)a3, (__m128)a4),
            _mm_unpacklo_ps((__m128)(unsigned int)dword_9D5160, (__m128)a2),
            17),
          (__m128)xmmword_9D5150);
  sub_694AC0(&v10, &v10, v11);
  v4 = _mm_shuffle_ps(v10, v11[0], 0);
  v5 = _mm_shuffle_ps(v4, v4, 138);
  v6 = _mm_shuffle_ps(v10, v11[0], 153);
  v7 = _mm_shuffle_ps(v6, v6, 247);
  v8 = _mm_shuffle_ps(v6, v6, 168);
  v10 = _mm_add_ps(
          _mm_mul_ps(_mm_mul_ps(v5, v7), v8),
          _mm_xor_ps(
            _mm_mul_ps(_mm_mul_ps(_mm_shuffle_ps(v5, v5, 138), _mm_shuffle_ps(v7, v7, 81)), _mm_shuffle_ps(v8, v8, 1)),
            (__m128)xmmword_9D5140));
  *a1 = v10;
  return a1;
}



// ------------------------------------------------------------
// 0x68B82E sub_68B82E
// ------------------------------------------------------------
// 【L1】SSE 矩阵×矩阵变体【推断】
int /*stdcall*/ sub_68B82E(int a1, int a2, int a3)
{
  __m128 v3; // xmm2
  __m128 v4; // xmm0
  __m128 v6; // xmm5
  __m128 v7; // xmm3

  if ( (a3 & 0xF) != 0 )
  {
    v6 = _mm_loadl_ps((const double *)a2);
    v7 = _mm_add_ps(
           _mm_add_ps(
             _mm_mul_ps(_mm_loadh_ps((const double *)(a3 + 8)), _mm_shuffle_ps(v6, v6, 0)),
             _mm_mul_ps(_mm_loadh_ps((const double *)(a3 + 24)), _mm_shuffle_ps(v6, v6, 85))),
           _mm_mul_ps(
             _mm_loadh_ps((const double *)(a3 + 40)),
             _mm_shuffle_ps((__m128)*(unsigned int *)(a2 + 8), (__m128)*(unsigned int *)(a2 + 8), 0)));
    _mm_storel_ps((double *)a1, v7);
    *(uint32_t *)(a1 + 8) = _mm_movehl_ps(v7, v7).m128_u32[0];
  }
  else
  {
    v3 = _mm_loadl_ps((const double *)a2);
    v4 = _mm_add_ps(
           _mm_add_ps(
             _mm_mul_ps(_mm_shuffle_ps(v3, v3, 0), *(__m128 *)a3),
             _mm_mul_ps(_mm_shuffle_ps(v3, v3, 85), *(__m128 *)(a3 + 16))),
           _mm_mul_ps(
             _mm_shuffle_ps((__m128)*(unsigned int *)(a2 + 8), (__m128)*(unsigned int *)(a2 + 8), 0),
             *(__m128 *)(a3 + 32)));
    _mm_storel_ps((double *)a1, v4);
    *(uint32_t *)(a1 + 8) = _mm_movehl_ps(v4, v4).m128_u32[0];
  }
  return a1;
}



// ------------------------------------------------------------
// 0x68B8EE sub_68B8EE
// ------------------------------------------------------------
// 【L1】SSE 矩阵×矩阵变体【推断】
__m128 */*stdcall*/ sub_68B8EE(__m128 *a1, int a2, int a3)
{
  __m128 v3; // xmm2
  __m128 v5; // xmm6

  if ( (a3 & 0xF) != 0 )
  {
    v5 = _mm_loadl_ps((const double *)a2);
    *a1 = _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_loadh_ps((const double *)(a3 + 8)), _mm_shuffle_ps(v5, v5, 0)),
              _mm_mul_ps(_mm_loadh_ps((const double *)(a3 + 24)), _mm_shuffle_ps(v5, v5, 85))),
            _mm_add_ps(
              _mm_mul_ps(
                _mm_loadh_ps((const double *)(a3 + 40)),
                _mm_shuffle_ps((__m128)*(unsigned int *)(a2 + 8), (__m128)*(unsigned int *)(a2 + 8), 0)),
              _mm_loadh_ps((const double *)(a3 + 56))));
  }
  else
  {
    v3 = _mm_loadl_ps((const double *)a2);
    *a1 = _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_shuffle_ps(v3, v3, 0), *(__m128 *)a3),
              _mm_mul_ps(_mm_shuffle_ps(v3, v3, 85), *(__m128 *)(a3 + 16))),
            _mm_add_ps(
              _mm_mul_ps(
                _mm_shuffle_ps((__m128)*(unsigned int *)(a2 + 8), (__m128)*(unsigned int *)(a2 + 8), 0),
                *(__m128 *)(a3 + 32)),
              *(__m128 *)(a3 + 48)));
  }
  return a1;
}



// ------------------------------------------------------------
// 0x68B9AE sub_68B9AE
// ------------------------------------------------------------
// 【L1】SSE 透视除法（rcp×2 = 1/w 与 1/w 精化，D3DXVec3Unproject 形态）【推断】
int /*stdcall*/ sub_68B9AE(int a1, int a2, int a3)
{
  __m128 v3; // xmm2
  __m128 v4; // xmm0
  __m128 v5; // xmm2
  __m128 v6; // xmm2
  __m128 v7; // xmm0
  __m128 v9; // xmm6
  __m128 v10; // xmm4
  __m128 v11; // xmm1
  __m128 v12; // xmm1
  __m128 v13; // xmm4

  if ( (a3 & 0xF) != 0 )
  {
    v9 = _mm_loadl_ps((const double *)a2);
    v10 = _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_loadh_ps((const double *)(a3 + 8)), _mm_shuffle_ps(v9, v9, 0)),
              _mm_mul_ps(_mm_loadh_ps((const double *)(a3 + 24)), _mm_shuffle_ps(v9, v9, 85))),
            _mm_add_ps(
              _mm_mul_ps(
                _mm_loadh_ps((const double *)(a3 + 40)),
                _mm_shuffle_ps((__m128)*(unsigned int *)(a2 + 8), (__m128)*(unsigned int *)(a2 + 8), 0)),
              _mm_loadh_ps((const double *)(a3 + 56))));
    v11 = _mm_rcp_ps(v10);
    v12 = _mm_sub_ps(_mm_add_ps(v11, v11), _mm_mul_ps(_mm_mul_ps(v11, v10), v11));
    v13 = _mm_mul_ps(v10, _mm_shuffle_ps(v12, v12, 255));
    _mm_storel_ps((double *)a1, v13);
    *(uint32_t *)(a1 + 8) = _mm_movehl_ps(v13, v13).m128_u32[0];
  }
  else
  {
    v3 = _mm_loadl_ps((const double *)a2);
    v4 = _mm_add_ps(
           _mm_add_ps(
             _mm_mul_ps(_mm_shuffle_ps(v3, v3, 0), *(__m128 *)a3),
             _mm_mul_ps(_mm_shuffle_ps(v3, v3, 85), *(__m128 *)(a3 + 16))),
           _mm_add_ps(
             _mm_mul_ps(
               _mm_shuffle_ps((__m128)*(unsigned int *)(a2 + 8), (__m128)*(unsigned int *)(a2 + 8), 0),
               *(__m128 *)(a3 + 32)),
             *(__m128 *)(a3 + 48)));
    v5 = _mm_rcp_ps(v4);
    v6 = _mm_sub_ps(_mm_add_ps(v5, v5), _mm_mul_ps(_mm_mul_ps(v5, v4), v5));
    v7 = _mm_mul_ps(v4, _mm_shuffle_ps(v6, v6, 255));
    _mm_storel_ps((double *)a1, v7);
    *(uint32_t *)(a1 + 8) = _mm_movehl_ps(v7, v7).m128_u32[0];
  }
  return a1;
}



// ------------------------------------------------------------
// 0x68BAAE sub_68BAAE
// ------------------------------------------------------------
// 【L1】x87 标量归一化变体【推断】
float */*stdcall*/ sub_68BAAE(float *a1, float *a2)
{
  float *result; // eax
  float v3; // xmm6_4
  float v4; // xmm5_4
  float v5; // xmm3_4
  float v6; // xmm3_4
  float v7; // xmm0_4

  result = a1;
  v3 = a2[1];
  v4 = a2[2];
  v5 = (float)((float)(*a2 * *a2) + (float)(v3 * v3)) + (float)(v4 * v4);
  if ( *(float *)&dword_9D5180 <= v5 )
  {
    v6 = 1.0 / fsqrt(v5);
    v7 = (float)(*(float *)&dword_9D5184 * v6)
       * (float)(*(float *)&dword_9D5188
               - (float)((float)((float)((float)((float)(*a2 * *a2) + (float)(a2[1] * a2[1])) + (float)(a2[2] * a2[2]))
                               * v6)
                       * v6));
    *a1 = v7 * *a2;
    a1[1] = v7 * v3;
    a1[2] = v7 * v4;
  }
  else
  {
    *a1 = 0.0;
    a1[1] = 0.0;
    a1[2] = 0.0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x68BB7E sub_68BB7E
// ------------------------------------------------------------
// 【L1】x87 标量归一化变体【推断】
float */*stdcall*/ sub_68BB7E(float *a1, float *a2)
{
  float *result; // eax
  float v3; // xmm4_4
  float v4; // xmm6_4
  float v5; // xmm3_4
  float v6; // xmm3_4
  float v7; // xmm0_4

  result = a1;
  v3 = a2[1];
  v4 = a2[2];
  v5 = (float)((float)(*a2 * *a2) + (float)(v3 * v3)) + (float)(v4 * v4);
  if ( *(float *)&dword_9D518C <= v5 )
  {
    v6 = 1.0 / fsqrt(v5);
    v7 = (float)(*(float *)&dword_9D5190 * v6)
       * (float)(*(float *)&dword_9D5194
               - (float)((float)((float)((float)((float)(*a2 * *a2) + (float)(a2[1] * a2[1])) + (float)(a2[2] * a2[2]))
                               * v6)
                       * v6));
    *a1 = v7 * *a2;
    a1[1] = v7 * v3;
    a1[2] = v7 * v4;
    a1[3] = v7 * a2[3];
  }
  else
  {
    *a1 = 0.0;
    a1[1] = 0.0;
    a1[2] = 0.0;
    a1[3] = 0.0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x68BC5E sub_68BC5E
// ------------------------------------------------------------
// 【L1】★ SSE 4x4 矩阵求逆（169 行伴随式 + 行列式，D3DXMatrixInverse 形态）【推断】
double */*stdcall*/ sub_68BC5E(double *a1, uint32_t *a2, const double *a3)
{
  __m128 v3; // xmm4
  __m128 v4; // xmm1
  __m128 v5; // xmm5
  __m128 v6; // xmm0
  __m128 v7; // xmm4
  __m128 v8; // xmm5
  __m128 v9; // xmm6
  __m128 v10; // xmm5
  __m128 v11; // xmm7
  __m128 v12; // xmm3
  __m128 v13; // xmm1
  __m128 v14; // xmm7
  __m128 v15; // xmm3
  __m128 v16; // xmm5
  __m128 v17; // xmm5
  __m128 v18; // xmm6
  __m128 v19; // xmm3
  __m128 v20; // xmm5
  __m128 v21; // xmm6
  __m128 v22; // xmm3
  __m128 v23; // xmm7
  __m128 v24; // xmm7
  __m128 v25; // xmm5
  __m128 v26; // xmm0
  __m128 v27; // xmm6
  __m128 v28; // xmm7
  __m128 v29; // xmm4
  __m128 v30; // xmm0
  __m128 v31; // xmm7
  __m128 v32; // xmm5
  __m128 v33; // xmm6
  __m128 v34; // xmm1
  __m128 v35; // xmm1
  __m128 v36; // xmm0
  __m128 v37; // xmm5
  __m128 v38; // xmm6
  __m128 v39; // xmm3
  __m128 v40; // xmm3
  __m128 v41; // xmm5
  __m128 v42; // xmm7
  __m128 v43; // xmm3
  __m128 v44; // xmm6
  __m128 v45; // xmm4
  __m128 v46; // xmm0
  __m128 v47; // xmm4
  __m128 v48; // xmm3
  __m128 v49; // xmm0
  __m128 v50; // xmm4
  __m128 v51; // xmm6
  __m128 v52; // xmm2
  __m128 v53; // xmm0
  __m128 v55; // xmm5
  __m128 v56; // xmm5
  __m128 v57; // xmm1
  __m128 v58; // xmm4
  __m128 v59; // xmm6
  __m128 v60; // xmm5
  __m128 v61; // [esp+20h] [ebp-FCh]
  __m128 v62; // [esp+30h] [ebp-ECh]
  __m128 v63; // [esp+40h] [ebp-DCh]
  __m128 v64; // [esp+50h] [ebp-CCh]
  __m128 v65; // [esp+60h] [ebp-BCh]
  __m128 v66; // [esp+70h] [ebp-ACh]
  __m128 v67; // [esp+80h] [ebp-9Ch]
  __m128 v68; // [esp+90h] [ebp-8Ch]
  __m128 v69; // [esp+A0h] [ebp-7Ch]
  __m128 v70; // [esp+B0h] [ebp-6Ch]
  __m128 v71; // [esp+E0h] [ebp-3Ch]

  v3 = _mm_loadh_ps(a3 + 7);
  v4 = _mm_loadh_ps(a3 + 2);
  v5 = _mm_loadh_ps(a3 + 3);
  v6 = _mm_shuffle_ps(v5, v3, 136);
  v7 = _mm_shuffle_ps(v3, v5, 221);
  v8 = _mm_mul_ps(v7, v6);
  v9 = _mm_shuffle_ps(v8, v8, 177);
  v10 = _mm_shuffle_ps(v9, v9, 78);
  v11 = _mm_loadh_ps(a3 + 6);
  v12 = _mm_shuffle_ps(v11, v4, 221);
  v13 = _mm_shuffle_ps(v4, v11, 136);
  v14 = v12;
  v15 = _mm_mul_ps(v12, v10);
  v62 = _mm_mul_ps(v10, v13);
  v16 = _mm_mul_ps(v14, v6);
  v17 = _mm_shuffle_ps(v16, v16, 177);
  v63 = _mm_mul_ps(v9, v13);
  v18 = _mm_add_ps(_mm_mul_ps(v7, v17), _mm_sub_ps(v15, _mm_mul_ps(v14, v9)));
  v19 = v17;
  v20 = _mm_shuffle_ps(v17, v17, 78);
  v64 = _mm_mul_ps(v19, v13);
  v21 = _mm_sub_ps(v18, _mm_mul_ps(v7, v20));
  v22 = v14;
  v23 = _mm_mul_ps(_mm_shuffle_ps(v14, v14, 78), v7);
  v24 = _mm_shuffle_ps(v23, v23, 177);
  v65 = _mm_mul_ps(v20, v13);
  v25 = _mm_shuffle_ps(v6, v6, 78);
  v26 = _mm_add_ps(_mm_mul_ps(v25, v24), v21);
  v27 = v24;
  v28 = _mm_shuffle_ps(v24, v24, 78);
  v66 = v7;
  v29 = v25;
  v30 = _mm_sub_ps(v26, _mm_mul_ps(v25, v28));
  v31 = _mm_sub_ps(_mm_mul_ps(v28, v13), _mm_mul_ps(v27, v13));
  v32 = v13;
  v33 = _mm_mul_ps(v13, v30);
  v61 = v30;
  v34 = _mm_add_ps(_mm_shuffle_ps(v33, v33, 78), v33);
  v30.m128_i32[0] = v34.m128_i32[0];
  v35 = _mm_shuffle_ps(v34, v34, 177);
  v35.m128_f32[0] = v35.m128_f32[0] + v30.m128_f32[0];
  v36 = v32;
  v37 = _mm_mul_ps(v32, v22);
  v38 = _mm_shuffle_ps(v37, v37, 177);
  v67 = v29;
  v68 = v22;
  v39 = _mm_mul_ps(v66, v36);
  v40 = _mm_shuffle_ps(v39, v39, 177);
  v69 = _mm_shuffle_ps(v38, v38, 78);
  v70 = v38;
  v41 = _mm_add_ps(
          _mm_mul_ps(v68, v40),
          _mm_sub_ps(_mm_mul_ps(v66, v69), _mm_add_ps(_mm_mul_ps(v66, v38), _mm_shuffle_ps(v31, v31, 78))));
  v42 = v40;
  v43 = _mm_shuffle_ps(v40, v40, 78);
  v44 = _mm_sub_ps(v41, _mm_mul_ps(v68, v43));
  v45 = _mm_sub_ps(v62, v63);
  v46 = _mm_mul_ps(v36, v67);
  v47 = _mm_add_ps(_mm_sub_ps(_mm_shuffle_ps(v45, v45, 78), _mm_mul_ps(v42, v67)), _mm_mul_ps(v43, v67));
  v48 = _mm_shuffle_ps(v46, v46, 177);
  v49 = _mm_shuffle_ps(v48, v48, 78);
  v71 = v44;
  v50 = _mm_sub_ps(_mm_add_ps(v47, _mm_mul_ps(v66, v48)), _mm_mul_ps(v66, v49));
  v51 = _mm_sub_ps(v65, v64);
  v52 = _mm_add_ps(
          _mm_mul_ps(v68, v49),
          _mm_sub_ps(
            _mm_sub_ps(_mm_sub_ps(_mm_mul_ps(v70, v67), _mm_shuffle_ps(v51, v51, 78)), _mm_mul_ps(v67, v69)),
            _mm_mul_ps(v48, v68)));
  if ( v35.m128_f32[0] == 0.0 )
    return nullptr;
  if ( a2 != nullptr )
    *a2 = v35.m128_i32[0];
  v53 = v35;
  v53.m128_f32[0] = 1.0 / v35.m128_f32[0];
  v55 = v53;
  v55.m128_f32[0] = (float)(v55.m128_f32[0] + v55.m128_f32[0])
                  - (float)(v35.m128_f32[0] * (float)(v53.m128_f32[0] * v53.m128_f32[0]));
  v56 = _mm_shuffle_ps(v55, v55, 0);
  v57 = _mm_mul_ps(v61, v56);
  _mm_storel_ps(a1, v57);
  _mm_storeh_ps(a1 + 1, v57);
  v58 = _mm_mul_ps(v50, v56);
  _mm_storel_ps(a1 + 2, v58);
  _mm_storeh_ps(a1 + 3, v58);
  v59 = _mm_mul_ps(v71, v56);
  _mm_storel_ps(a1 + 4, v59);
  _mm_storeh_ps(a1 + 5, v59);
  v60 = _mm_mul_ps(v56, v52);
  _mm_storel_ps(a1 + 6, v60);
  _mm_storeh_ps(a1 + 7, v60);
  return a1;
}


// ------------------------------------------------------------
// 0x68BF1E sub_68BF1E
// ------------------------------------------------------------
// 【L1】SSE 批量转置乘（71 行，loadh/storeh/storel 各 4，多顶点管线）【推断】
double */*stdcall*/ sub_68BF1E(double *a1, unsigned int *a2, const double *a3)
{
  __m128 v5; // xmm3
  __m128 v6; // xmm2
  __m128 v7; // xmm1
  __m128 v8; // xmm0
  __m128 v9; // xmm5
  __m128 v10; // xmm7
  __m128 v11; // xmm4
  __m128 v12; // xmm7
  __m128 v13; // xmm6
  __m128 v14; // xmm5
  __m128 v15; // xmm2
  __m128 v16; // xmm1
  __m128 v17; // xmm5
  __m128 v18; // xmm0
  __m128 v19; // xmm6
  __m128 v20; // xmm0

  v5 = _mm_loadh_ps(a3 + 1);
  v6 = _mm_loadh_ps(a3 + 3);
  v7 = _mm_loadh_ps(a3 + 5);
  v8 = _mm_loadh_ps(a3 + 7);
  v9 = _mm_add_ps(
         _mm_add_ps(
           _mm_add_ps(
             _mm_mul_ps(_mm_shuffle_ps((__m128)a2[4], (__m128)a2[4], 0), v5),
             _mm_mul_ps(_mm_shuffle_ps((__m128)a2[5], (__m128)a2[5], 0), v6)),
           _mm_mul_ps(_mm_shuffle_ps((__m128)a2[6], (__m128)a2[6], 0), v7)),
         _mm_mul_ps(_mm_shuffle_ps((__m128)a2[7], (__m128)a2[7], 0), v8));
  v10 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_shuffle_ps((__m128)*a2, (__m128)*a2, 0), v5),
              _mm_mul_ps(_mm_shuffle_ps((__m128)a2[1], (__m128)a2[1], 0), v6)),
            _mm_mul_ps(_mm_shuffle_ps((__m128)a2[2], (__m128)a2[2], 0), v7)),
          _mm_mul_ps(_mm_shuffle_ps((__m128)a2[3], (__m128)a2[3], 0), v8));
  v11 = _mm_unpacklo_ps(v10, v9);
  v12 = _mm_unpackhi_ps(v10, v9);
  v13 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(_mm_shuffle_ps((__m128)a2[8], (__m128)a2[8], 0), v5),
              _mm_mul_ps(_mm_shuffle_ps((__m128)a2[9], (__m128)a2[9], 0), v6)),
            _mm_mul_ps(_mm_shuffle_ps((__m128)a2[10], (__m128)a2[10], 0), v7)),
          _mm_mul_ps(_mm_shuffle_ps((__m128)a2[11], (__m128)a2[11], 0), v8));
  v14 = _mm_add_ps(
          _mm_mul_ps(_mm_shuffle_ps((__m128)a2[12], (__m128)a2[12], 0), v5),
          _mm_mul_ps(_mm_shuffle_ps((__m128)a2[13], (__m128)a2[13], 0), v6));
  v15 = _mm_mul_ps(_mm_shuffle_ps((__m128)a2[14], (__m128)a2[14], 0), v7);
  v16 = (__m128)a2[15];
  _mm_storel_ps(a1, v11);
  v17 = _mm_add_ps(_mm_add_ps(v14, v15), _mm_mul_ps(_mm_shuffle_ps(v16, v16, 0), v8));
  _mm_storeh_ps(a1 + 2, v11);
  _mm_storel_ps(a1 + 4, v12);
  _mm_storeh_ps(a1 + 6, v12);
  v18 = v13;
  v19 = _mm_unpacklo_ps(v13, v17);
  _mm_storel_ps(a1 + 1, v19);
  _mm_storeh_ps(a1 + 3, v19);
  v20 = _mm_unpackhi_ps(v18, v17);
  _mm_storel_ps(a1 + 5, v20);
  _mm_storeh_ps(a1 + 7, v20);
  return a1;
}



// ------------------------------------------------------------
// 0x68C07E sub_68C07E
// ------------------------------------------------------------
// 【L1】SSE 矩阵×向量（与 68B06E 同构）【推断】
__m128 */*stdcall*/ sub_68C07E(__m128 *a1, int a2, int a3, int a4)
{
  __m128 v5; // xmm2
  __m128 v6; // xmm2
  __m128 v7; // xmm1
  __m128 v8; // xmm3
  __m128 v9; // xmm4
  __m128 v10; // xmm0
  __m128 v11; // xmm4
  __m128 v12; // xmm2
  __m128 v13; // xmm3
  __m128 v14; // xmm1

  v5 = _mm_loadh_ps((const double *)(a3 + 8));
  v6 = _mm_shuffle_ps(v5, v5, 57);
  v7 = _mm_loadh_ps((const double *)(a2 + 8));
  v8 = _mm_loadh_ps((const double *)(a4 + 8));
  v9 = _mm_shuffle_ps(v8, v8, 78);
  v10 = _mm_mul_ps(_mm_shuffle_ps(v9, v9, 57), v6);
  v11 = _mm_mul_ps(v9, v6);
  v12 = _mm_mul_ps(v6, v8);
  v13 = _mm_shuffle_ps(v7, v7, 57);
  v14 = _mm_shuffle_ps(v13, v13, 57);
  *a1 = _mm_xor_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_mul_ps(v13, _mm_sub_ps(_mm_shuffle_ps(v11, v11, 57), _mm_shuffle_ps(v12, v12, 78))),
              _mm_mul_ps(_mm_sub_ps(_mm_shuffle_ps(v10, v10, 78), v10), v14)),
            _mm_mul_ps(_mm_shuffle_ps(v14, v14, 57), _mm_sub_ps(v11, _mm_shuffle_ps(v12, v12, 57)))),
          (__m128)xmmword_79A480);
  return a1;
}



// ------------------------------------------------------------
// 0x68C12E sub_68C12E
// ------------------------------------------------------------
// 【L1】SSE 稀疏标量混合（storel×3 = 分量写回）【推断】
int /*stdcall*/ sub_68C12E(int a1, int a2)
{
  __m128 v2; // xmm0
  __m128 v3; // xmm2
  __m128 v5; // xmm3
  __m128 v6; // xmm0
  int v7; // [esp-14h] [ebp-44h]
  int v8; // [esp-10h] [ebp-40h]
  int v9; // [esp-Ch] [ebp-3Ch]
  int v10; // [esp-8h] [ebp-38h]
  void *vars0; // [esp+30h] [ebp+0h]
  void *retaddr; // [esp+38h] [ebp+8h]

  vars0 = retaddr;
  v2 = sub_694CB0(v7, v8, v9, v10);
  v3 = (__m128)xmmword_9D51B0;
  v5 = v2;
  v6 = (__m128)xmmword_9D51C0;
  *(_OWORD *)a1 = xmmword_9D51D0;
  *(uint32_t *)(a1 + 16) = v6.m128_i32[0];
  _mm_storel_ps((double *)(a1 + 20), v5);
  _mm_storel_ps((double *)(a1 + 28), v6);
  *(uint32_t *)(a1 + 44) = v6.m128_i32[0];
  _mm_storel_ps((double *)(a1 + 36), _mm_xor_ps(_mm_shuffle_ps(v5, v5, 17), v3));
  *(__m128 *)(a1 + 48) = v6;
  return a1;
}



// ------------------------------------------------------------
// 0x68C1AE sub_68C1AE
// ------------------------------------------------------------
// 【L1】SSE 稀疏标量混合变体【推断】
int /*stdcall*/ sub_68C1AE(int a1, int a2)
{
  __m128 v2; // xmm0
  __m128 v3; // xmm0
  __int128 v5; // xmm1
  int v6; // [esp-14h] [ebp-64h]
  int v7; // [esp-10h] [ebp-60h]
  int v8; // [esp-Ch] [ebp-5Ch]
  int v9; // [esp-8h] [ebp-58h]
  __m128 v10; // [esp+1Ch] [ebp-34h]
  __m128 v11; // [esp+2Ch] [ebp-24h]
  void *vars0; // [esp+50h] [ebp+0h]
  void *retaddr; // [esp+58h] [ebp+8h]

  vars0 = retaddr;
  v11 = (__m128)xmmword_9D5210;
  v10 = (__m128)xmmword_9D5200;
  v2 = sub_694CB0(v6, v7, v8, v9);
  v3 = _mm_and_ps(_mm_shuffle_ps(v2, v2, 80), v11);
  *(__m128 *)a1 = _mm_xor_ps(v10, v3);
  *(_OWORD *)(a1 + 16) = xmmword_9D51F0;
  v5 = xmmword_9D51E0;
  *(__m128 *)(a1 + 32) = _mm_shuffle_ps(v3, v3, 70);
  *(_OWORD *)(a1 + 48) = v5;
  return a1;
}



// ------------------------------------------------------------
// 0x68C23E sub_68C23E
// ------------------------------------------------------------
// 【L1】SSE 平面归一化变体（sqrt，与 68B13E 同构）【推断】
__m128 */*stdcall*/ sub_68C23E(__m128 *a1, const double *a2, const double *a3, const double *a4)
{
  __m128 v5; // xmm3
  __m128 v6; // xmm1
  __m128 v7; // xmm0
  __m128 v8; // xmm4
  __m128 v9; // xmm5
  __m128 v10; // xmm3
  __m128 v11; // xmm5
  __m128 v12; // xmm1
  __m128 v13; // xmm3
  __m128 v14; // xmm5
  __m128 v15; // xmm0
  __m128 v16; // xmm5
  __m128 v17; // xmm3
  __m128 v18; // xmm0

  v5 = _mm_loadh_ps(a2);
  v6 = _mm_sub_ps(v5, _mm_loadh_ps(a4));
  v7 = _mm_shuffle_ps(v6, v6, 120);
  v8 = v5;
  v9 = _mm_sub_ps(v5, _mm_loadh_ps(a3));
  v10 = _mm_shuffle_ps(v9, v9, 99);
  v11 = _mm_mul_ps(_mm_shuffle_ps(v9, v9, 120), _mm_shuffle_ps(v6, v6, 99));
  v12 = (__m128)xmmword_79A4B0;
  v13 = _mm_sub_ps(_mm_mul_ps(v7, v10), v11);
  v14 = _mm_mul_ps(v13, v13);
  v15 = _mm_add_ps(v14, _mm_movehl_ps(v14, v14));
  v15.m128_f32[0] = v15.m128_f32[0] + _mm_shuffle_ps(v15, v15, 1).m128_f32[0];
  v16 = v15;
  v15.m128_f32[0] = fsqrt(v15.m128_f32[0]);
  v12.m128_f32[0] = (float)(*(float *)&xmmword_79A4B0 * (float)(1.0 / v15.m128_f32[0]))
                  * (float)(*(float *)&xmmword_79A4A0
                          - (float)((float)(v16.m128_f32[0] * (float)(1.0 / v15.m128_f32[0]))
                                  * (float)(1.0 / v15.m128_f32[0])));
  v17 = _mm_mul_ps(v13, _mm_shuffle_ps(v12, v12, 0));
  *a1 = v17;
  v18 = _mm_mul_ps(_mm_shuffle_ps(v8, v8, 14), v17);
  a1->m128_i32[3] = COERCE_UNSIGNED_INT(
                      v18.m128_f32[0]
                    + (float)(_mm_movehl_ps(v16, v18).m128_f32[0] + _mm_shuffle_ps(v18, v18, 85).m128_f32[0]))
                  ^ xmmword_79A490;
  return a1;
}



// ------------------------------------------------------------
// 0x68C32E sub_68C32E
// ------------------------------------------------------------
// 【L1】SSE 平面变换 + 归一化（与 68B22E 同构）【推断】
double */*stdcall*/ sub_68C32E(double *a1, __m128 *a2, __m128 *a3)
{
  __m128 v3; // xmm2
  __m128 v4; // xmm3
  __m128 v5; // xmm3
  __m128 v6; // xmm1
  __m128 v7; // xmm0
  char v8; // al
  __m128 v9; // xmm4
  float v10; // xmm3_4
  float v11; // xmm5_4
  double *result; // eax
  __m128 v13; // xmm4
  __m128 v14; // xmm0
  __m128 v15; // xmm0
  __m128 v16; // xmm0
  __m128 v17; // xmm5
  __m128 v18; // xmm6
  float v19; // xmm7_4
  __m128 v20; // xmm0
  __m128 v21; // xmm1
  __m128 v22; // xmm2
  __m128 v23; // xmm3

  v3 = *a3;
  v4 = _mm_and_ps((__m128)xmmword_79A500, *a3);
  v5 = _mm_mul_ps(v4, v4);
  v6 = _mm_add_ps(v5, _mm_movehl_ps((__m128)0LL, v5));
  v7 = _mm_shuffle_ps(v6, v6, 1);
  v7.m128_f32[0] = v7.m128_f32[0] + v6.m128_f32[0];
  if ( v7.m128_f32[0] != 0.0 )
  {
    v8 = byte_9D4FE0;
    if ( (byte_9D4FE0 & 1) != 0 )
    {
      v9 = (__m128)xmmword_9D4FC0;
    }
    else
    {
      v8 = byte_9D4FE0 | 1;
      v9 = (__m128)(unsigned int)dword_9D5220;
      byte_9D4FE0 |= 1u;
      xmmword_9D4FC0 = (unsigned int)dword_9D5220;
    }
    if ( (v8 & 2) != 0 )
    {
      v10 = *(float *)&xmmword_9D4FD0;
    }
    else
    {
      v10 = *(float *)&dword_9D5224;
      byte_9D4FE0 = v8 | 2;
      xmmword_9D4FD0 = (unsigned int)dword_9D5224;
    }
    v11 = 1.0 / fsqrt(v7.m128_f32[0]);
    v9.m128_f32[0] = (float)(v9.m128_f32[0] * v11) * (float)(v10 - (float)((float)(v7.m128_f32[0] * v11) * v11));
    v7 = _mm_mul_ps(v3, _mm_shuffle_ps(v9, v9, 0));
  }
  result = a1;
  v13 = _mm_xor_ps((__m128)xmmword_79A4C0, v7);
  v14 = _mm_mul_ps(v7, *a2);
  v15 = _mm_add_ps(v14, _mm_movehl_ps(v6, v14));
  v15.m128_f32[0] = v15.m128_f32[0] + _mm_shuffle_ps(v15, v15, 1).m128_f32[0];
  v16 = _mm_shuffle_ps(v15, v15, 0);
  v17 = _mm_and_ps((__m128)xmmword_79A4E0, v16);
  v18 = _mm_and_ps((__m128)xmmword_79A4F0, v16);
  v19 = v16.m128_f32[0];
  v20 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v13, v13, 85), *a2), _mm_and_ps((__m128)xmmword_79A4D0, v16));
  v21 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v13, v13, 170), *a2), v17);
  v23 = _mm_mul_ps(_mm_shuffle_ps(v13, v13, 0), *a2);
  v22 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v13, v13, 255), *a2), v18);
  v23.m128_f32[0] = v23.m128_f32[0] + v19;
  if ( ((uint8_t)a1 & 0xF) != 0 )
  {
    _mm_storel_ps(a1, v23);
    _mm_storeh_ps(a1 + 1, v23);
    _mm_storel_ps(a1 + 2, v20);
    _mm_storeh_ps(a1 + 3, v20);
    _mm_storel_ps(a1 + 4, v21);
    _mm_storeh_ps(a1 + 5, v21);
    _mm_storel_ps(a1 + 6, v22);
    _mm_storeh_ps(a1 + 7, v22);
  }
  else
  {
    *(__m128 *)a1 = v23;
    *((__m128 *)a1 + 1) = v20;
    *((__m128 *)a1 + 2) = v21;
    *((__m128 *)a1 + 3) = v22;
  }
  return result;
}



// ------------------------------------------------------------
// 0x68C4BE sub_68C4BE
// ------------------------------------------------------------
// 【L1】SSE sqrt 归一化变体【推断】
__m128 */*stdcall*/ sub_68C4BE(__m128 *a1, const double *a2)
{
  __m128 v3; // xmm1
  __m128 v4; // xmm0
  __m128 v5; // xmm3
  __m128 v6; // xmm4
  __m128 v7; // xmm0
  float v8; // xmm5_4
  __m128 v9; // xmm1
  __m128 v10; // xmm4
  __m128 v11; // xmm0
  __m128 v12; // xmm1
  __m128 v13; // xmm2
  __m128 v14; // xmm0
  __m128 v15; // xmm3
  __m128 v16; // xmm2
  __m128 v17; // xmm4

  v3 = _mm_loadl_ps(a2);
  v4 = _mm_and_ps((__m128)xmmword_79A580, v3);
  v5 = (__m128)(unsigned int)dword_79A570;
  v6 = _mm_mul_ps(v4, v4);
  v7 = _mm_add_ps(v6, _mm_movehl_ps(v6, v6));
  v8 = v7.m128_f32[0] + _mm_shuffle_ps(v7, v7, 1).m128_f32[0];
  v7.m128_f32[0] = 1.0 / fsqrt(v8);
  v5.m128_f32[0] = (float)(*(float *)&dword_79A570 * v7.m128_f32[0])
                 * (float)(*(float *)&dword_79A560 - (float)((float)(v8 * v7.m128_f32[0]) * v7.m128_f32[0]));
  v9 = _mm_mul_ps(v3, _mm_shuffle_ps(v5, v5, 0));
  v10 = _mm_mul_ps((__m128)xmmword_79A550, v9);
  v11 = v9;
  v12 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v9, v9, 0), v10), (__m128)xmmword_79A540);
  v13 = v11;
  v14 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v11, v11, 255), v10), (__m128)xmmword_79A510);
  v15 = v13;
  v16 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(v13, v13, 170), v10), (__m128)xmmword_79A520);
  v17 = _mm_add_ps(_mm_mul_ps(v10, _mm_shuffle_ps(v15, v15, 85)), (__m128)xmmword_79A530);
  *a1 = v12;
  a1[1] = v17;
  a1[2] = v16;
  a1[3] = v14;
  return a1;
}



// ------------------------------------------------------------
// 0x68C590 sub_68C590
// ------------------------------------------------------------
// 【L1】x87 标量双 sqrt 变体（与 68B630 成对）【推断】
float */*stdcall*/ sub_68C590(float *a1, float *a2)
{
  float *result; // eax
  double v3; // st7
  float v4; // edi
  float v5; // esi
  int v6; // ebp
  double v7; // st7
  int v8; // ecx
  int v9; // ebx
  int v10; // ebp
  float *v11; // esi
  long double v12; // st6
  long double v13; // st7
  float *v14; // ecx
  long double v15; // st6
  long double v16; // st7
  uint32_t v17[7]; // [esp+0h] [ebp-1Ch]

  result = a1;
  v3 = *a2 + a2[5] + a2[10];
  v4 = *a2;
  v5 = a2[5];
  v6 = *((uint32_t *)a2 + 10);
  if ( flt_9D527C < v3 )
  {
    v15 = sqrt(v3 + flt_9D5280) * flt_9D5284;
    v16 = flt_9D5288 / v15;
    a1[3] = v15;
    *a1 = (a2[6] - a2[9]) * v16;
    a1[1] = (a2[8] - a2[2]) * v16;
    a1[2] = v16 * (a2[1] - a2[4]);
  }
  else
  {
    v7 = a2[10];
    *(float *)v17 = *a2;
    *(float *)&v17[1] = v5;
    v17[2] = v6;
    v8 = 2;
    if ( *(float *)&v17[v5 > (double)v4] >= v7 )
      v8 = v5 > (double)v4;
    v9 = dword_9D5270[v8];
    v10 = dword_9D5270[v9];
    v11 = &a2[v8];
    v12 = sqrt(flt_9D5290 + *(float *)&v17[v8] - *(float *)&v17[v9] - *(float *)&v17[v10]) * flt_9D5294;
    v13 = flt_9D5298 / v12;
    a1[v8] = v12;
    v14 = &a2[4 * v8];
    a1[v9] = (v14[v9] + v11[4 * v9]) * v13;
    a1[v10] = (v11[4 * v10] + v14[v10]) * v13;
    a1[3] = v13 * (a2[4 * v9 + v10] - a2[4 * v10 + v9]);
  }
  return result;
}



// ------------------------------------------------------------
// 0x68C6BE sub_68C6BE
// ------------------------------------------------------------
// 【L1】SSE 变换（shuffle×9，与 68B75E 同构）【推断】
__m128 */*stdcall*/ sub_68C6BE(__m128 *a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
  __m128 v4; // xmm0
  __m128 v5; // xmm1
  __m128 v6; // xmm3
  __m128 v7; // xmm2
  __m128 v8; // xmm3
  __m128 v10; // [esp+10h] [ebp-4Ch] BYREF
  __m128 v11[3]; // [esp+20h] [ebp-3Ch] BYREF

  v10 = _mm_mul_ps(
          _mm_shuffle_ps(
            _mm_unpacklo_ps((__m128)a3, (__m128)a4),
            _mm_unpacklo_ps((__m128)(unsigned int)dword_9D52C0, (__m128)a2),
            17),
          (__m128)xmmword_9D52B0);
  sub_694DA0(&v10, &v10, v11);
  v4 = _mm_shuffle_ps(v10, v11[0], 0);
  v5 = _mm_shuffle_ps(v4, v4, 138);
  v6 = _mm_shuffle_ps(v10, v11[0], 153);
  v7 = _mm_shuffle_ps(v6, v6, 247);
  v8 = _mm_shuffle_ps(v6, v6, 168);
  v10 = _mm_add_ps(
          _mm_mul_ps(_mm_mul_ps(v5, v7), v8),
          _mm_xor_ps(
            _mm_mul_ps(_mm_mul_ps(_mm_shuffle_ps(v5, v5, 138), _mm_shuffle_ps(v7, v7, 81)), _mm_shuffle_ps(v8, v8, 1)),
            (__m128)xmmword_9D52A0));
  *a1 = v10;
  return a1;
}




// ============================================================
// SECTION 3  3DNow!/MMX 四元数与矩阵（AMD 路径 · 0x68C876-0x68FF1C）
// ------------------------------------------------------------
// _m_pf*（3DNow!）/_m_femms 指纹 + x87 标量混合；pfacc = 半和点积
// （16 次 = 4x4 矩阵乘）、pswapd/pnacc = 转置点积。
// 四元数→旋转矩阵（0x68E4DD，x²+y²+z² 与 1.0f 组合直证）、
// 仿射组合巨型（0x68E592 967 行 / 0x68FF1C 946 行，四元数×缩放×平移）。
// CPU 分派上游: missing_tail.cpp 0x680134/0x680380 (AuthenticAMD/UnknownVendr)。
// ============================================================
// ------------------------------------------------------------
// 0x68C876 sub_68C876
// ------------------------------------------------------------
// 【L1】3DNow! 归一化混合实现（_m_pfrcp + x87 sqrt/rsqrt 混合，AMD 入口）【推断】
int /*stdcall*/ sub_68C876(__m64 *a1, int a2, uint32_t *a3)
{
  __m64 m64_u64; // mm2
  __m64 v4; // mm0
  __m64 v5; // mm5
  __m64 v6; // mm5
  __m64 v7; // mm1
  int result; // eax
  __m64 v9; // mm4
  __m64 v10; // mm1
  __m64 v11; // mm1

  m64_u64 = (__m64)a1->m64_u64;
  v4 = a1[1];
  v5 = _m_pfadd(_m_pfmul(m64_u64, m64_u64), _m_pfmul(v4, v4));
  v6 = _m_pfacc(v5, v5);
  v7 = _m_pfrsqrt(v6);
  result = _mm_cvtsi64_si32(_m_pfcmpge((__m64)0x80000000800000LL, v6));
  v9 = v7;
  if ( result != 0 )
  {
    if ( a2 != 0 )
    {
      *(uint64_t *)(a2 + 4) = 0;
      *(uint32_t *)a2 = _mm_cvtsi64_si32((__m64)0xBF8000003F800000uLL);
    }
    if ( a3 != nullptr )
      *a3 = _mm_cvtsi64_si32(0);
  }
  else
  {
    v10 = _m_pfmul(v7, v7);
    if ( a2 != 0 )
    {
      v11 = _m_pfrcpit2(_m_pfrsqit1(v10, v6), v9);
      *(__m64 *)a2 = _m_pfmul(m64_u64, v11);
      *(uint32_t *)(a2 + 8) = _mm_cvtsi64_si32(_m_pfmul(v11, v4));
    }
    if ( a3 != nullptr )
    {
      result = sub_6950C0(a3, a2);
      *a3 = _mm_cvtsi64_si32(_m_pfmul(_m_punpckhdq(v4, v4), (__m64)0x4000000040000000LL));
    }
  }
  _m_femms();
  return result;
}



// ------------------------------------------------------------
// 0x68C929 sub_68C929
// ------------------------------------------------------------
// 【L1】3DNow! 大函数：四元数/轴角→矩阵（137 行，rcp4/subr2 直证旋转公式）【推断】
__m64 */*stdcall*/ sub_68C929(__m64 *a1, __m64 *a2)
{
  __m64 v2; // mm4
  __m64 v3; // mm5
  __m64 v4; // mm3
  __m64 v5; // mm0
  __m64 v6; // mm1
  __m64 v7; // mm2
  __m64 v8; // mm5
  __m64 v9; // mm3
  __m64 v10; // mm0
  __m64 v11; // mm3
  __m64 v12; // mm6
  int v13; // ecx
  __m64 v14; // mm0
  __m64 v15; // mm7
  __m64 v16; // mm2
  __m64 v17; // mm0
  __m64 v18; // mm4
  __m64 *result; // eax
  __m64 v20; // mm1
  __m64 v21; // mm1
  __m64 v22; // mm0
  __m64 v23; // mm1
  __m64 v24; // mm4
  __m64 v25; // mm1
  __m64 v26; // mm2
  __m64 v27; // mm0
  __m64 v28; // mm2
  __m64 v29; // mm4
  __m64 v30; // mm1
  __m64 v31; // mm3
  __m64 v32; // mm0
  __m64 v33; // mm3
  __m64 v34; // mm2
  __m64 v35; // mm3

  v2 = _mm_cvtsi32_si64(a2[2].m64_u32[1]);
  v3 = _mm_cvtsi32_si64(a2[5].m64_u32[0]);
  v4 = _m_pfsubr((__m64)a2->m64_u64, v3);
  v5 = _m_pfadd(_m_pfadd((__m64)a2->m64_u64, v2), v3);
  v6 = _m_pfsub(_m_pfsub((__m64)a2->m64_u64, v2), v3);
  v7 = _m_pfsub(_m_pfsubr((__m64)a2->m64_u64, v2), v3);
  v8 = a2[4];
  v9 = _m_pfsub(v4, v2);
  v10 = _m_punpckldq(v5, v7);
  v11 = _m_punpckldq(v9, v9);
  v12 = _m_packssdw(_m_pfcmpge(_m_punpckldq(0, v6), v10), _m_pfcmpge(_m_punpckldq(v7, v6), v11));
  v13 = _mm_cvtsi64_si32(_m_packsswb(v12, v12));
  if ( (v13 & 1) != 0 )
  {
    if ( (v13 & 0xFF00FF00) == 0xFF00FF00 )
    {
      v21 = _m_pfadd(v6, (__m64)0xBF8000003F800000uLL);
      v22 = _m_pfrsqrt(v21);
      v23 = _m_punpckldq(v21, v21);
      v24 = _m_pfmul(_m_pfrcpit2(_m_pfrsqit1(_m_pfmul(v22, v22), v23), v22), (__m64)0x3F0000003F000000LL);
      v25 = _m_punpckldq(
              _m_pfmul(v23, v24),
              _m_pfmul(_m_pfsub(_mm_cvtsi32_si64(a2[2].m64_u32[0]), _m_punpckhdq(v7, v7)), v24));
      a1[1].m64_u64 = (uint64_t)_m_pfmul(
                                          _m_pfadd(
                                            _m_punpckldq(v8, (__m64)a2[3].m64_u32[0]),
                                            _m_pxor(
                                              _m_punpckldq(_mm_cvtsi32_si64(a2[1].m64_u32[0]), _m_punpckhdq(v8, v8)),
                                              (__m64)0x8000000000000000uLL)),
                                          v24);
      a1->m64_u64 = (uint64_t)v25;
      _m_femms();
      return a1;
    }
    else
    {
      result = a1;
      if ( (v13 & 0x10000) != 0 )
      {
        v26 = _m_pfadd(v7, (__m64)0xBF8000003F800000uLL);
        v27 = _m_pfrsqrt(v26);
        v28 = _m_punpckldq(v26, v26);
        v29 = _m_pfmul(_m_pfrcpit2(_m_pfrsqit1(_m_pfmul(v27, v27), v28), v27), (__m64)0x3F0000003F000000LL);
        v30 = _m_punpckldq(
                _m_pfmul(_m_pfadd(_m_punpckhdq(v6, v6), _mm_cvtsi32_si64(a2[2].m64_u32[0])), v29),
                _m_pfmul(v28, v29));
        a1[1].m64_u64 = (uint64_t)_m_pfmul(
                                            _m_pfadd(
                                              _m_punpckldq(_mm_cvtsi32_si64(a2[3].m64_u32[0]), v8),
                                              _m_pxor(
                                                _m_punpckldq(_m_punpckhdq(v8, v8), (__m64)a2[1].m64_u32[0]),
                                                (__m64)0x8000000000000000uLL)),
                                            v29);
        a1->m64_u64 = (uint64_t)v30;
      }
      else
      {
        v31 = _m_pfadd(v11, (__m64)0xBF8000003F800000uLL);
        v32 = _m_pfrsqrt(v31);
        v33 = _m_punpckldq(v31, v31);
        v34 = _m_pfmul(_m_pfrcpit2(_m_pfrsqit1(_m_pfmul(v32, v32), v33), v32), (__m64)0x3F0000003F000000LL);
        v35 = _m_punpckldq(
                _m_pfmul(v33, v34),
                _m_pfmul(_m_pfsub(_m_punpckhdq(v6, v6), _mm_cvtsi32_si64(a2[2].m64_u32[0])), v34));
        a1->m64_u64 = (uint64_t)_m_pfmul(
                                          _m_pfadd(
                                            _m_punpckldq(v8, (__m64)a2[3].m64_u32[0]),
                                            _m_punpckldq(_mm_cvtsi32_si64(a2[1].m64_u32[0]), _m_punpckhdq(v8, v8))),
                                          v34);
        a1[1].m64_u64 = (uint64_t)v35;
      }
      _m_femms();
    }
  }
  else
  {
    v14 = _m_pfadd(v10, (__m64)0xBF8000003F800000uLL);
    v15 = _mm_cvtsi32_si64(a2[1].m64_u32[0]);
    v16 = _m_pfrsqrt(v14);
    v17 = _m_punpckldq(v14, v14);
    v18 = _m_pfmul(_m_pfrcpit2(_m_pfrsqit1(_m_pfmul(v16, v16), v17), v16), (__m64)0x3F0000003F000000LL);
    v20 = _m_punpckldq(
            _m_pfmul(_m_pfsub(_m_punpckhdq(v6, v6), _mm_cvtsi32_si64(a2[2].m64_u32[0])), v18),
            _m_pfmul(v17, v18));
    a1->m64_u64 = (uint64_t)_m_pfmul(
                                      _m_pfsub(
                                        _m_punpckldq(_mm_cvtsi32_si64(a2[3].m64_u32[0]), v8),
                                        _m_punpckhdq(v8, _m_punpckldq(v15, v15))),
                                      v18);
    a1[1].m64_u64 = (uint64_t)v20;
    _m_femms();
    return a1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x68CB45 sub_68CB45
// ------------------------------------------------------------
// 【L1】3DNow! 四元数→矩阵变体（与 68C929 成对，另一寄存器布局）【推断】
__m64 */*stdcall*/ sub_68CB45(__m64 *a1, __m64 *a2)
{
  __m64 v2; // mm4
  __m64 v3; // mm5
  __m64 v4; // mm3
  __m64 v5; // mm0
  __m64 v6; // mm1
  __m64 v7; // mm2
  __m64 v8; // mm5
  __m64 v9; // mm3
  __m64 v10; // mm0
  __m64 v11; // mm3
  char v12; // cl
  __m64 v13; // mm0
  __m64 v14; // mm7
  __m64 v15; // mm2
  __m64 v16; // mm0
  __m64 v17; // mm4
  __m64 *result; // eax
  __m64 v19; // mm1
  __m64 v20; // mm1
  __m64 v21; // mm0
  __m64 v22; // mm1
  __m64 v23; // mm4
  __m64 v24; // mm1
  __m64 v25; // mm2
  __m64 v26; // mm0
  __m64 v27; // mm2
  __m64 v28; // mm4
  __m64 v29; // mm1
  __m64 v30; // mm3
  __m64 v31; // mm0
  __m64 v32; // mm3
  __m64 v33; // mm2
  __m64 v34; // mm3

  v2 = _mm_cvtsi32_si64(a2[2].m64_u32[1]);
  v3 = _mm_cvtsi32_si64(a2[5].m64_u32[0]);
  v4 = _m_pfsubr((__m64)a2->m64_u64, v3);
  v5 = _m_pfadd(_m_pfadd((__m64)a2->m64_u64, v2), v3);
  v6 = _m_pfsub(_m_pfsub((__m64)a2->m64_u64, v2), v3);
  v7 = _m_pfsub(_m_pfsubr((__m64)a2->m64_u64, v2), v3);
  v8 = a2[4];
  v9 = _m_pfsub(v4, v2);
  v10 = _m_punpckldq(v5, v7);
  v11 = _m_punpckldq(v9, v9);
  v12 = _m_pmovmskb(_m_packssdw(_m_pfcmpge(_m_punpckldq(0, v6), v10), _m_pfcmpge(_m_punpckldq(v7, v6), v11)));
  if ( (v12 & 1) != 0 )
  {
    if ( (v12 & 0xCC) == 0xCC )
    {
      v20 = _m_pfadd(v6, (__m64)0xBF8000003F800000uLL);
      v21 = _m_pfrsqrt(v20);
      v22 = _m_punpckldq(v20, v20);
      v23 = _m_pfmul(_m_pfrcpit2(_m_pfrsqit1(_m_pfmul(v21, v21), v22), v21), (__m64)0x3F0000003F000000LL);
      v24 = _m_punpckldq(
              _m_pfmul(v22, v23),
              _m_pfmul(_m_pfsub(_mm_cvtsi32_si64(a2[2].m64_u32[0]), _m_punpckhdq(v7, v7)), v23));
      a1[1].m64_u64 = (uint64_t)_m_pfmul(
                                          _m_pfadd(
                                            _m_punpckldq(v8, (__m64)a2[3].m64_u32[0]),
                                            _m_pxor(
                                              _m_punpckldq(_mm_cvtsi32_si64(a2[1].m64_u32[0]), _m_punpckhdq(v8, v8)),
                                              (__m64)0x8000000000000000uLL)),
                                          v23);
      a1->m64_u64 = (uint64_t)v24;
      _m_femms();
      return a1;
    }
    else
    {
      result = a1;
      if ( (v12 & 0x10) != 0 )
      {
        v25 = _m_pfadd(v7, (__m64)0xBF8000003F800000uLL);
        v26 = _m_pfrsqrt(v25);
        v27 = _m_punpckldq(v25, v25);
        v28 = _m_pfmul(_m_pfrcpit2(_m_pfrsqit1(_m_pfmul(v26, v26), v27), v26), (__m64)0x3F0000003F000000LL);
        v29 = _m_punpckldq(
                _m_pfmul(_m_pfadd(_m_punpckhdq(v6, v6), _mm_cvtsi32_si64(a2[2].m64_u32[0])), v28),
                _m_pfmul(v27, v28));
        a1[1].m64_u64 = (uint64_t)_m_pfmul(
                                            _m_pfadd(
                                              _m_punpckldq(_mm_cvtsi32_si64(a2[3].m64_u32[0]), v8),
                                              _m_pxor(
                                                _m_punpckldq(_m_punpckhdq(v8, v8), (__m64)a2[1].m64_u32[0]),
                                                (__m64)0x8000000000000000uLL)),
                                            v28);
        a1->m64_u64 = (uint64_t)v29;
      }
      else
      {
        v30 = _m_pfadd(v11, (__m64)0xBF8000003F800000uLL);
        v31 = _m_pfrsqrt(v30);
        v32 = _m_punpckldq(v30, v30);
        v33 = _m_pfmul(_m_pfrcpit2(_m_pfrsqit1(_m_pfmul(v31, v31), v32), v31), (__m64)0x3F0000003F000000LL);
        v34 = _m_punpckldq(
                _m_pfmul(v32, v33),
                _m_pfmul(_m_pfsub(_m_punpckhdq(v6, v6), _mm_cvtsi32_si64(a2[2].m64_u32[0])), v33));
        a1->m64_u64 = (uint64_t)_m_pfmul(
                                          _m_pfadd(
                                            _m_punpckldq(v8, (__m64)a2[3].m64_u32[0]),
                                            _m_punpckldq(_mm_cvtsi32_si64(a2[1].m64_u32[0]), _m_punpckhdq(v8, v8))),
                                          v33);
        a1[1].m64_u64 = (uint64_t)v34;
      }
      _m_femms();
    }
  }
  else
  {
    v13 = _m_pfadd(v10, (__m64)0xBF8000003F800000uLL);
    v14 = _mm_cvtsi32_si64(a2[1].m64_u32[0]);
    v15 = _m_pfrsqrt(v13);
    v16 = _m_punpckldq(v13, v13);
    v17 = _m_pfmul(_m_pfrcpit2(_m_pfrsqit1(_m_pfmul(v15, v15), v16), v15), (__m64)0x3F0000003F000000LL);
    v19 = _m_punpckldq(
            _m_pfmul(_m_pfsub(_m_punpckhdq(v6, v6), _mm_cvtsi32_si64(a2[2].m64_u32[0])), v17),
            _m_pfmul(v16, v17));
    a1->m64_u64 = (uint64_t)_m_pfmul(
                                      _m_pfsub(
                                        _m_punpckldq(_mm_cvtsi32_si64(a2[3].m64_u32[0]), v8),
                                        _m_punpckhdq(v8, _m_punpckldq(v14, v14))),
                                      v17);
    a1[1].m64_u64 = (uint64_t)v19;
    _m_femms();
    return a1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x68CD5A sub_68CD5A
// ------------------------------------------------------------
// 【L1】3DNow! userpurge（half=0.5f×2，半像素/半角缩放）【推断】
__m64 */*userpurge*/ sub_68CD5A@<eax>(__m64 *a1, __m64 a2, __m64 a3)
{
  __m64 v3; // mm1
  __m64 v5; // mm6
  __m64 v6; // mm2
  __m64 v7; // mm6
  __m64 v8; // mm7
  __m64 v9; // [esp+10h] [ebp-10h]

  _m_femms();
  v9 = _m_pfmul((__m64)0x3F0000003F000000LL, a2);
  sub_6956A0();
  sub_6956A0();
  sub_6956A0();
  v3 = _m_pfmul((__m64)0x3F0000003F000000LL, a3);
  v5 = _m_punpckhdq(v9, v9);
  v6 = _m_punpckldq(v5, v5);
  v7 = _m_punpckhdq(v5, v5);
  v8 = _m_punpckldq(_m_punpckhdq(v3, v3), v3);
  a1->m64_u64 = (uint64_t)_m_pfadd(
                                    _m_pfmul(
                                      _m_pfmul(_m_pxor(_m_punpckldq(v9, v9), (__m64)0x8000000000000000uLL), v7),
                                      v3),
                                    _m_pfmul(_m_pfmul(_m_punpckhdq(v9, v9), v6), v8));
  a1[1].m64_u64 = (uint64_t)_m_pfadd(
                                      _m_pfmul(_m_pfmul(_m_punpckldq(v9, v9), v6), v8),
                                      _m_pfmul(
                                        _m_pfmul(
                                          _m_pxor(_m_punpckhdq(v9, v9), _m_psrlqi((__m64)0x8000000000000000uLL, 0x20u)),
                                          v7),
                                        v3));
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68CE1F sub_68CE1F
// ------------------------------------------------------------
// 【L1】3DNow! 小型变换（cvtsi 整数入参）【推断】
__m64 */*stdcall*/ sub_68CE1F(__m64 *a1, int a2, unsigned int a3)
{
  __m64 v3; // mm0
  __m64 v5; // mm3
  __m64 v6; // mm2
  __m64 v7; // [esp+0h] [ebp-18h] BYREF
  unsigned int v8; // [esp+8h] [ebp-10h]

  _m_femms();
  sub_691B72(&v7, a2);
  v3 = _m_pfmul(_mm_cvtsi32_si64(a3), (__m64)0x3F0000003F000000LL);
  sub_6956A0();
  v5 = _m_punpckhdq(v3, v3);
  v6 = _m_punpckldq(_m_pfmul(_mm_cvtsi32_si64(v8), v5), v3);
  a1->m64_u64 = (uint64_t)_m_pfmul(v7, v5);
  a1[1].m64_u64 = (uint64_t)v6;
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68CE8B sub_68CE8B
// ------------------------------------------------------------
// 【L1】3DNow! 中型变换（rcp+pfacc，矩阵×向量 + 1/w）【推断】
__m64 */*stdcall*/ sub_68CE8B(__m64 *a1, __m64 *a2, __m64 *a3, unsigned int a4)
{
  __m64 v4; // mm1
  __m64 v5; // mm4
  __m64 v6; // mm0
  __m64 v7; // mm1
  __m64 v8; // mm7
  __m64 v9; // mm1
  __m64 v10; // mm3
  __m64 v11; // mm4
  __m64 v12; // mm0
  __m64 v13; // mm1
  __m64 v15; // mm4
  __m64 v16; // mm5
  __m64 v17; // mm6
  __m64 v18; // mm0
  __m64 v19; // mm5
  unsigned int v20; // [esp+28h] [ebp+10h]

  _m_femms();
  v4 = _m_pfadd(_m_pfmul((__m64)a2->m64_u64, (__m64)a3->m64_u64), _m_pfmul(a2[1], a3[1]));
  v5 = _mm_cvtsi32_si64(a4);
  v6 = _m_pfsub(_mm_cvtsi32_si64(0x3F800000u), v5);
  v7 = _m_pfacc(v4, v4);
  v8 = _m_pand(_m_pfcmpge(0, v7), (__m64)0x8000000080000000uLL);
  v9 = _m_pxor(v7, v8);
  v10 = _m_pfsubr(_m_pfmul(v9, v9), (__m64)0x3F8000003F800000LL);
  if ( _mm_cvtsi64_si32(_m_pfcmpge((__m64)0x3F7FFF583F7FFF58LL, v9)) != 0 )
  {
    v11 = _m_pfrsqrt(v10);
    sub_694FC0();
    sub_6957C0();
    v20 = _mm_cvtsi64_si32(_m_pfmul(v9, _mm_cvtsi32_si64(a4)));
    v12 = _m_pfmul(_mm_cvtsi32_si64(_mm_cvtsi64_si32(v9)), _mm_cvtsi32_si64(_mm_cvtsi64_si32(v6)));
    sub_6957C0();
    v13 = _mm_cvtsi32_si64(_mm_cvtsi64_si32(_m_pfrcpit2(_m_pfrsqit1(v10, _m_pfmul(v11, v11)), v11)));
    v8 = _mm_cvtsi32_si64(_mm_cvtsi64_si32(v8));
    v6 = _m_pfmul(v12, v13);
    v5 = _m_pfmul(_mm_cvtsi32_si64(v20), v13);
  }
  v15 = _m_pxor(v5, v8);
  v16 = _m_punpckldq(v6, v6);
  v17 = _m_punpckldq(v15, v15);
  v18 = _m_pfmul(v16, (__m64)a2->m64_u64);
  v19 = _m_pfadd(_m_pfmul(v16, a2[1]), _m_pfmul(v17, a3[1]));
  a1->m64_u64 = (uint64_t)_m_pfadd(v18, _m_pfmul(v17, (__m64)a3->m64_u64));
  a1[1].m64_u64 = (uint64_t)v19;
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68CFC2 sub_68CFC2
// ------------------------------------------------------------
// 【L1】3DNow! 归一化（rcp×3 = 三分量倒数）【推断】
__m64 */*stdcall*/ sub_68CFC2(__m64 *a1, __m64 *a2, __m64 *a3, __m64 *a4, unsigned int a5, unsigned int a6)
{
  __m64 v6; // mm0
  __m64 v7; // mm2
  __m64 v9[2]; // [esp+Ch] [ebp-24h] BYREF
  __m64 v10[2]; // [esp+1Ch] [ebp-14h] BYREF
  unsigned int v11; // [esp+44h] [ebp+14h]

  _m_femms();
  v11 = _mm_cvtsi64_si32(_m_pfadd(_mm_cvtsi32_si64(a5), _mm_cvtsi32_si64(a6)));
  sub_68CE8B(v9, a2, a3, v11);
  sub_68CE8B(v10, a2, a4, v11);
  v6 = _mm_cvtsi32_si64(v11);
  v7 = _m_pfrcp(v6);
  sub_68CE8B(a1, v9, v10, _mm_cvtsi64_si32(_m_pfmul(_m_pfrcpit2(_m_pfrcpit1(v6, v7), v7), _mm_cvtsi32_si64(a6))));
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68D04F sub_68D04F
// ------------------------------------------------------------
// 【L1】3DNow! 小型操作【推断】
__m64 */*stdcall*/ sub_68D04F(__m64 *a1, __m64 *a2, __m64 *a3, __m64 *a4, __m64 *a5, unsigned int a6)
{
  __m64 v6; // mm1
  __m64 *result; // eax
  __m64 v8[2]; // [esp+10h] [ebp-20h] BYREF
  __m64 v9[2]; // [esp+20h] [ebp-10h] BYREF

  sub_68CE8B(v8, a2, a5, a6);
  sub_68CE8B(v9, a3, a4, a6);
  v6 = _mm_cvtsi32_si64(a6);
  result = sub_68CE8B(
             a1,
             v8,
             v9,
             _mm_cvtsi64_si32(_m_pfmul(_m_pfsub(v6, _m_pfmul(v6, v6)), (__m64)0x4000000040000000LL)));
  _m_femms();
  return result;
}



// ------------------------------------------------------------
// 0x68D0E1 sub_68D0E1
// ------------------------------------------------------------
// 【L1】3DNow! pfacc 点积归一化【推断】
__m64 */*stdcall*/ sub_68D0E1(__m64 *a1, __m64 *a2)
{
  __m64 v2; // mm3
  __m64 v3; // mm0
  __m64 v4; // mm0
  __m64 v6; // mm4
  __m64 v7; // mm5
  __m64 v8; // mm0

  v2 = a2[1];
  v3 = _m_pfadd(_m_pfmul((__m64)a2->m64_u64, (__m64)a2->m64_u64), _m_pfmul(v2, v2));
  v4 = _m_pfacc(v3, v3);
  v6 = _m_pfrcp(v4);
  v7 = _m_pfcmpgt(v4, (__m64)0x80000000800000LL);
  v8 = _m_pfrcpit2(_m_pfrcpit1(v4, v6), v6);
  a1->m64_u64 = (uint64_t)_m_pfmul(_m_pand(_m_pxor((__m64)a2->m64_u64, (__m64)0x8000000080000000uLL), v7), v8);
  a1[1].m64_u64 = (uint64_t)_m_pfmul(_m_pand(_m_pxor(v2, (__m64)0x80000000LL), v7), v8);
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68D145 sub_68D145
// ------------------------------------------------------------
// 【L1】3DNow! 变换 + 1.0f 组合（齐次 w 分量处理）【推断】
__m64 */*stdcall*/ sub_68D145(__m64 *a1, __m64 *a2)
{
  __m64 *result; // eax
  __m64 m64_u64; // mm1
  __m64 v4; // mm2
  __m64 v5; // mm0
  __m64 v6; // mm3
  __m64 v7; // mm4
  __m64 v8; // mm3
  unsigned int v9; // [esp+0h] [ebp-Ch]

  _m_femms();
  result = a1;
  m64_u64 = (__m64)a2->m64_u64;
  v4 = a2[1];
  v5 = _m_punpckhdq(v4, v4);
  if ( _mm_cvtsi64_si32(_m_pfcmpge(v5, (__m64)0x3F8000003F800000LL)) == 0 )
  {
    sub_6950C0(0, a2);
    v9 = _mm_cvtsi64_si32(v5);
    sub_6957C0();
    result = a1;
    m64_u64 = (__m64)a2->m64_u64;
    v4 = a2[1];
    if ( _mm_cvtsi64_si32(_m_pfcmpge(_m_pand(v5, (__m64)0x7FFFFFFF7FFFFFFFLL), (__m64)0x3400000034000000LL)) != 0 )
    {
      v6 = _mm_cvtsi32_si64(v9);
      v7 = _m_pfrcp(v5);
      v8 = _m_pfmul(_m_punpckldq(v6, v6), _m_pfrcpit2(_m_pfrcpit1(v5, v7), v7));
      m64_u64 = _m_pfmul(m64_u64, v8);
      v4 = _m_pfmul(v4, v8);
    }
  }
  result->m64_u64 = (uint64_t)m64_u64;
  result[1].m64_u64 = (uint64_t)_m_pand(v4, (__m64)0xFFFFFFFFLL);
  _m_femms();
  return result;
}



// ------------------------------------------------------------
// 0x68D1EC sub_68D1EC
// ------------------------------------------------------------
// 【L1】3DNow! userpurge（rcp+sqrt+rsqrt 全套，综合变换）【推断】
__m64 */*userpurge*/ sub_68D1EC@<eax>(unsigned int a1@<esi>, __m64 *a2, __m64 *a3)
{
  __m64 v3; // mm1
  __m64 v4; // mm0
  __m64 v5; // mm0
  __m64 v6; // mm2
  __m64 v7; // mm1
  __m64 v8; // mm1
  __m64 v9; // mm0
  __m64 *result; // eax
  char v11; // cl
  __m64 m64_u64; // mm2
  __m64 v13; // mm0
  __m64 v14; // mm1
  __m64 v15; // mm3
  __m64 v16; // mm1
  __m64 v17; // [esp+0h] [ebp-Ch]

  v3 = _mm_cvtsi32_si64(a3[1].m64_u32[0]);
  v4 = _m_pfadd(_m_pfmul((__m64)a3->m64_u64, (__m64)a3->m64_u64), _m_pfmul(v3, v3));
  v5 = _m_pfacc(v4, v4);
  v6 = _m_pfrsqrt(v5);
  v7 = _m_pfrcpit2(_m_pfrsqit1(_m_pfmul(v6, v6), v5), v6);
  v17.m64_u64 = __PAIR64__(a1, _mm_cvtsi64_si32(v7));
  sub_6956A0();
  v8 = _m_pfmul(v5, v7);
  v9 = _m_pfcmpge(_m_pand(v8, (__m64)0x7FFFFFFFFFFFFFFFLL), (__m64)0x3400000034000000LL);
  result = a2;
  v11 = _mm_cvtsi64_si32(_m_punpckhdq(v9, v9));
  m64_u64 = (__m64)a3->m64_u64;
  v13 = v8;
  v14 = _m_pfmul(_m_punpckhdq(v8, v8), v17);
  v15 = _mm_cvtsi32_si64(a3[1].m64_u32[0]);
  if ( (v11 & 1) != 0 )
  {
    v16 = _m_punpckldq(v14, v14);
    v15 = _m_pfmul(v15, v16);
    m64_u64 = _m_pfmul(m64_u64, v16);
  }
  a2->m64_u64 = (uint64_t)m64_u64;
  a2[1].m64_u64 = (uint64_t)_m_punpckldq(v15, v13);
  _m_femms();
  return result;
}



// ------------------------------------------------------------
// 0x68D291 sub_68D291
// ------------------------------------------------------------
// 【L1】★ 3DNow! 批量顶点变换管线（382 行，rcp/pfacc×20 = 多矩阵×多顶点全展开，软渲染顶点路径）【推断】
__m64 */*userpurge*/ sub_68D291@<eax>(
        unsigned int a1@<esi>,
        __m64 *a2,
        __m64 *a3,
        __m64 *a4,
        __m64 *a5,
        __m64 *a6,
        __m64 *a7,
        __m64 *a8)
{
  __m64 v8; // mm0
  __m64 v9; // mm1
  __m64 v10; // mm2
  __m64 v11; // mm3
  __m64 v12; // mm0
  __m64 v13; // mm2
  __m64 v14; // mm4
  __m64 v15; // mm5
  __m64 v16; // mm1
  __m64 v17; // mm3
  __m64 v18; // mm2
  int v19; // eax
  __m64 v20; // mm4
  __m64 v21; // mm6
  __m64 v22; // mm7
  __m64 v23; // mm3
  __m64 v24; // mm5
  __m64 v25; // mm6
  __m64 v26; // mm3
  __m64 v27; // mm0
  __m64 v28; // mm0
  __m64 v29; // mm4
  __m64 v30; // mm5
  __m64 v31; // mm0
  __m64 v32; // mm6
  __m64 v33; // mm7
  __m64 v34; // mm6
  __m64 v35; // mm7
  __m64 v36; // mm1
  __m64 v37; // mm2
  __m64 v38; // mm0
  __m64 v39; // mm3
  __m64 v40; // mm4
  __m64 v41; // mm3
  __m64 v42; // mm1
  __m64 v43; // mm2
  __m64 v44; // mm0
  __m64 v45; // mm3
  __m64 v46; // mm4
  __m64 v47; // mm3
  __m64 v48; // mm1
  __m64 v49; // mm0
  __m64 v50; // mm0
  __m64 v51; // mm2
  __m64 v52; // mm1
  int32_t v53; // edx
  __m64 v54; // mm1
  __m64 v55; // mm0
  char v56; // cl
  __m64 v57; // mm2
  __m64 v58; // mm0
  __m64 v59; // mm1
  __m64 v60; // mm3
  __m64 v61; // mm1
  __m64 v62; // mm6
  __m64 v63; // mm7
  __m64 v64; // mm0
  __m64 v65; // mm0
  __m64 v66; // mm4
  __m64 v67; // mm5
  __m64 v68; // mm0
  __m64 v69; // mm6
  __m64 v70; // mm7
  __m64 v71; // mm6
  __m64 v72; // mm7
  __m64 v73; // mm1
  __m64 v74; // mm2
  __m64 v75; // mm0
  __m64 v76; // mm3
  __m64 v77; // mm4
  __m64 v78; // mm3
  __m64 v79; // mm1
  __m64 v80; // mm2
  __m64 v81; // mm0
  __m64 v82; // mm3
  __m64 v83; // mm4
  __m64 v84; // mm3
  __m64 v85; // mm1
  __m64 v86; // mm0
  __m64 v87; // mm0
  __m64 v88; // mm2
  __m64 v89; // mm1
  __m64 v90; // mm1
  __m64 v91; // mm0
  char v92; // cl
  __m64 v93; // mm2
  __m64 v94; // mm0
  __m64 v95; // mm1
  __m64 v96; // mm3
  __m64 v97; // mm1
  __m64 v98; // mm6
  __m64 v99; // mm7
  unsigned int v101; // [esp+0h] [ebp-ACh]
  unsigned int v102; // [esp+0h] [ebp-ACh]
  __m64 v103; // [esp+0h] [ebp-ACh]
  unsigned int v104; // [esp+0h] [ebp-ACh]
  unsigned int v105; // [esp+0h] [ebp-ACh]
  __m64 v106; // [esp+0h] [ebp-ACh]
  __m64 m64_u64; // [esp+Ch] [ebp-A0h]
  __m64 v108; // [esp+14h] [ebp-98h]
  __m64 v109; // [esp+1Ch] [ebp-90h]
  __m64 v110; // [esp+24h] [ebp-88h]
  __m64 v111; // [esp+2Ch] [ebp-80h]
  __m64 v112; // [esp+34h] [ebp-78h]
  __m64 v113; // [esp+3Ch] [ebp-70h]
  __m64 v114; // [esp+44h] [ebp-68h]
  __m64 v115; // [esp+4Ch] [ebp-60h]
  __m64 v116; // [esp+4Ch] [ebp-60h]
  __m64 v117; // [esp+54h] [ebp-58h]
  __m64 v118; // [esp+54h] [ebp-58h]
  __m64 v119; // [esp+5Ch] [ebp-50h]
  __m64 v120; // [esp+5Ch] [ebp-50h]
  __m64 v121; // [esp+64h] [ebp-48h]
  __m64 v122; // [esp+64h] [ebp-48h]
  __m64 v123; // [esp+84h] [ebp-28h]
  __m64 v124; // [esp+84h] [ebp-28h]
  __m64 v125; // [esp+8Ch] [ebp-20h]
  __m64 v126; // [esp+8Ch] [ebp-20h]
  __m64 v127; // [esp+8Ch] [ebp-20h]
  __m64 v128; // [esp+8Ch] [ebp-20h]
  __m64 v129; // [esp+94h] [ebp-18h]
  float v130; // [esp+94h] [ebp-18h]
  __m64 v131; // [esp+94h] [ebp-18h]
  float v132; // [esp+94h] [ebp-18h]
  __m64 v133; // [esp+9Ch] [ebp-10h]
  __m64 v134; // [esp+9Ch] [ebp-10h]
  __m64 v135; // [esp+A4h] [ebp-8h]
  __m64 v136; // [esp+A4h] [ebp-8h]

  m64_u64 = (__m64)a5->m64_u64;
  v108 = a5[1];
  v109 = (__m64)a6->m64_u64;
  v8 = _m_pfadd((__m64)a5->m64_u64, (__m64)a6->m64_u64);
  v110 = a6[1];
  v9 = _m_pfadd(v108, v110);
  v10 = _m_pfsub((__m64)a5->m64_u64, (__m64)a6->m64_u64);
  v11 = _m_pfsub(v108, v110);
  v12 = _m_pfadd(_m_pfmul(v8, v8), _m_pfmul(v9, v9));
  v13 = _m_pfadd(_m_pfmul(v10, v10), _m_pfmul(v11, v11));
  v111 = (__m64)a7->m64_u64;
  v112 = a7[1];
  v14 = _m_pfadd((__m64)a6->m64_u64, (__m64)a7->m64_u64);
  v15 = _m_pfadd(v110, v112);
  v16 = _m_pfsub((__m64)a6->m64_u64, (__m64)a7->m64_u64);
  v17 = _m_pfsub(v110, v112);
  v18 = _m_pfcmpgt(
          _m_pfacc(v13, _m_pfadd(_m_pfmul(v16, v16), _m_pfmul(v17, v17))),
          _m_pfacc(v12, _m_pfadd(_m_pfmul(v14, v14), _m_pfmul(v15, v15))));
  v19 = _mm_cvtsi64_si32(_m_packsswb(v18, v18));
  if ( (v19 & 1) != 0 )
  {
    m64_u64 = _m_pxor((__m64)0x8000000080000000uLL, (__m64)a5->m64_u64);
    v108 = _m_pxor((__m64)0x8000000080000000uLL, a5[1]);
  }
  if ( (v19 & 0x10000) != 0 )
  {
    v111 = _m_pxor((__m64)0x8000000080000000uLL, (__m64)a7->m64_u64);
    v112 = _m_pxor((__m64)0x8000000080000000uLL, a7[1]);
  }
  v20 = a8[1];
  v21 = _m_pfadd(v111, (__m64)a8->m64_u64);
  v113 = (__m64)a8->m64_u64;
  v22 = _m_pfadd(v112, v20);
  v114 = v20;
  v23 = _m_pfsub(v111, (__m64)a8->m64_u64);
  v24 = _m_pfsub(v112, v20);
  v25 = _m_pfadd(_m_pfmul(v21, v21), _m_pfmul(v22, v22));
  v26 = _m_pfadd(_m_pfmul(v23, v23), _m_pfmul(v24, v24));
  if ( (_mm_cvtsi64_si32(_m_pfcmpgt(_m_pfacc(v26, v26), _m_pfacc(v25, v25))) & 1) != 0 )
  {
    v113 = _m_pxor((__m64)0x8000000080000000uLL, (__m64)a8->m64_u64);
    v114 = _m_pxor((__m64)0x8000000080000000uLL, a8[1]);
  }
  v27 = _m_pfadd(_m_pfmul(v109, v109), _m_pfmul(v110, v110));
  v28 = _m_pfacc(v27, v27);
  v29 = _m_pfrcp(v28);
  v30 = _m_pfcmpgt(v28, (__m64)0x80000000800000LL);
  v31 = _m_pfrcpit2(_m_pfrcpit1(v28, v29), v29);
  v115 = _m_pfmul(_m_pand(_m_pxor(v109, (__m64)0x8000000080000000uLL), v30), v31);
  v117 = _m_pfmul(_m_pand(_m_pxor(v110, (__m64)0x80000000LL), v30), v31);
  v32 = _m_punpckldq(_m_punpckhdq(m64_u64, m64_u64), m64_u64);
  v33 = _m_punpckldq(_m_punpckhdq(v108, v108), v108);
  v125 = _m_pfacc(
           _m_pfsub(_m_pfmul(v32, v117), _m_pfmul(_m_pxor(v33, (__m64)0x80000000LL), v115)),
           _m_pfadd(_m_pxor(_m_pfmul(m64_u64, v117), (__m64)0x80000000LL), _m_pfmul(v108, v115)));
  v129 = _m_pfacc(
           _m_pfadd(_m_pfmul(_m_pxor(v32, (__m64)0x80000000LL), v115), _m_pfmul(v33, v117)),
           _m_pfsub(_m_pfmul(_m_pxor(v108, (__m64)0x80000000LL), v117), _m_pfmul(m64_u64, v115)));
  v34 = _m_punpckldq(_m_punpckhdq(v111, v111), v111);
  v35 = _m_punpckldq(_m_punpckhdq(v112, v112), v112);
  v133 = _m_pfacc(
           _m_pfsub(_m_pfmul(v34, v117), _m_pfmul(_m_pxor(v35, (__m64)0x80000000LL), v115)),
           _m_pfadd(_m_pxor(_m_pfmul(v111, v117), (__m64)0x80000000LL), _m_pfmul(v112, v115)));
  v135 = _m_pfacc(
           _m_pfadd(_m_pfmul(_m_pxor(v34, (__m64)0x80000000LL), v115), _m_pfmul(v35, v117)),
           _m_pfsub(_m_pfmul(_m_pxor(v112, (__m64)0x80000000LL), v117), _m_pfmul(v111, v115)));
  v36 = v125;
  v37 = v129;
  v38 = _m_punpckhdq(v129, v129);
  if ( _mm_cvtsi64_si32(_m_pfcmpge(v38, (__m64)0x3F8000003F800000LL)) == 0 )
  {
    ((void (*)(void))sub_6950C0)();
    v101 = _mm_cvtsi64_si32(v38);
    sub_6957C0();
    v36 = v125;
    v37 = v129;
    if ( _mm_cvtsi64_si32(_m_pfcmpge(_m_pand(v38, (__m64)0x7FFFFFFF7FFFFFFFLL), (__m64)0x3400000034000000LL)) != 0 )
    {
      v39 = _mm_cvtsi32_si64(v101);
      v40 = _m_pfrcp(v38);
      v41 = _m_pfmul(_m_punpckldq(v39, v39), _m_pfrcpit2(_m_pfrcpit1(v38, v40), v40));
      v36 = _m_pfmul(v125, v41);
      v37 = _m_pfmul(v129, v41);
    }
  }
  v119 = v36;
  v121 = _m_pand(v37, (__m64)0xFFFFFFFFLL);
  v42 = v133;
  v43 = v135;
  v44 = _m_punpckhdq(v135, v135);
  if ( _mm_cvtsi64_si32(_m_pfcmpge(v44, (__m64)0x3F8000003F800000LL)) == 0 )
  {
    ((void (*)(void))sub_6950C0)();
    v102 = _mm_cvtsi64_si32(v44);
    sub_6957C0();
    v42 = v133;
    v43 = v135;
    if ( _mm_cvtsi64_si32(_m_pfcmpge(_m_pand(v44, (__m64)0x7FFFFFFF7FFFFFFFLL), (__m64)0x3400000034000000LL)) != 0 )
    {
      v45 = _mm_cvtsi32_si64(v102);
      v46 = _m_pfrcp(v44);
      v47 = _m_pfmul(_m_punpckldq(v45, v45), _m_pfrcpit2(_m_pfrcpit1(v44, v46), v46));
      v42 = _m_pfmul(v133, v47);
      v43 = _m_pfmul(v135, v47);
    }
  }
  v126 = _m_pfmul(_m_pfadd(v119, v42), (__m64)0xBE800000BE800000uLL);
  v130 = _m_pfmul(_m_pfadd(v121, _m_pand(v43, (__m64)0xFFFFFFFFLL)), (__m64)0xBE800000BE800000uLL).m64_f32[0];
  v48 = _mm_cvtsi32_si64(LODWORD(v130));
  v49 = _m_pfadd(_m_pfmul(v126, v126), _m_pfmul(v48, v48));
  v50 = _m_pfacc(v49, v49);
  v51 = _m_pfrsqrt(v50);
  v52 = _m_pfrcpit2(_m_pfrsqit1(_m_pfmul(v51, v51), v50), v51);
  v103.m64_u64 = __PAIR64__(a1, _mm_cvtsi64_si32(v52));
  sub_6956A0();
  v54 = _m_pfmul(v50, v52);
  v55 = _m_pfcmpge(_m_pand(v54, (__m64)0x7FFFFFFFFFFFFFFFLL), (__m64)0x3400000034000000LL);
  v56 = _mm_cvtsi64_si32(_m_punpckhdq(v55, v55));
  v57 = v126;
  v58 = v54;
  v59 = _m_pfmul(_m_punpckhdq(v54, v54), v103);
  v60 = _mm_cvtsi32_si64(LODWORD(v130));
  if ( (v56 & 1) != 0 )
  {
    v61 = _m_punpckldq(v59, v59);
    v60 = _m_pfmul(v60, v61);
    v57 = _m_pfmul(v126, v61);
  }
  v123 = _m_punpckldq(v60, v58);
  v62 = _m_punpckldq(_m_punpckhdq(v57, v57), v57);
  v63 = _m_punpckldq(_m_punpckhdq(v123, v123), v123);
  a2->m64_u64 = (uint64_t)_m_pfacc(
                                    _m_pfsub(_m_pfmul(v62, v110), _m_pfmul(_m_pxor(v63, (__m64)0x80000000LL), v109)),
                                    _m_pfadd(_m_pxor(_m_pfmul(v57, v110), (__m64)0x80000000LL), _m_pfmul(v123, v109)));
  a2[1].m64_u64 = (uint64_t)_m_pfacc(
                                      _m_pfadd(_m_pfmul(_m_pxor(v62, (__m64)0x80000000LL), v109), _m_pfmul(v63, v110)),
                                      _m_pfsub(_m_pfmul(_m_pxor(v123, (__m64)0x80000000LL), v110), _m_pfmul(v57, v109)));
  v64 = _m_pfadd(_m_pfmul(v111, v111), _m_pfmul(v112, v112));
  v65 = _m_pfacc(v64, v64);
  v66 = _m_pfrcp(v65);
  v67 = _m_pfcmpgt(v65, (__m64)0x80000000800000LL);
  v68 = _m_pfrcpit2(_m_pfrcpit1(v65, v66), v66);
  v116 = _m_pfmul(_m_pand(_m_pxor(v111, (__m64)0x8000000080000000uLL), v67), v68);
  v118 = _m_pfmul(_m_pand(_m_pxor(v112, (__m64)0x80000000LL), v67), v68);
  v69 = _m_punpckldq(_m_punpckhdq(v109, v109), v109);
  v70 = _m_punpckldq(_m_punpckhdq(v110, v110), v110);
  v127 = _m_pfacc(
           _m_pfsub(_m_pfmul(v69, v118), _m_pfmul(_m_pxor(v70, (__m64)0x80000000LL), v116)),
           _m_pfadd(_m_pxor(_m_pfmul(v109, v118), (__m64)0x80000000LL), _m_pfmul(v110, v116)));
  v131 = _m_pfacc(
           _m_pfadd(_m_pfmul(_m_pxor(v69, (__m64)0x80000000LL), v116), _m_pfmul(v70, v118)),
           _m_pfsub(_m_pfmul(_m_pxor(v110, (__m64)0x80000000LL), v118), _m_pfmul(v109, v116)));
  v71 = _m_punpckldq(_m_punpckhdq(v113, v113), v113);
  v72 = _m_punpckldq(_m_punpckhdq(v114, v114), v114);
  v134 = _m_pfacc(
           _m_pfsub(_m_pfmul(v71, v118), _m_pfmul(_m_pxor(v72, (__m64)0x80000000LL), v116)),
           _m_pfadd(_m_pxor(_m_pfmul(v113, v118), (__m64)0x80000000LL), _m_pfmul(v114, v116)));
  v136 = _m_pfacc(
           _m_pfadd(_m_pfmul(_m_pxor(v71, (__m64)0x80000000LL), v116), _m_pfmul(v72, v118)),
           _m_pfsub(_m_pfmul(_m_pxor(v114, (__m64)0x80000000LL), v118), _m_pfmul(v113, v116)));
  v73 = v127;
  v74 = v131;
  v75 = _m_punpckhdq(v131, v131);
  if ( _mm_cvtsi64_si32(_m_pfcmpge(v75, (__m64)0x3F8000003F800000LL)) == 0 )
  {
    ((void (*)(void))sub_6950C0)();
    v104 = _mm_cvtsi64_si32(v75);
    sub_6957C0();
    v53 = m64_u64.m64_i32[1];
    v73 = v127;
    v74 = v131;
    if ( _mm_cvtsi64_si32(_m_pfcmpge(_m_pand(v75, (__m64)0x7FFFFFFF7FFFFFFFLL), (__m64)0x3400000034000000LL)) != 0 )
    {
      v76 = _mm_cvtsi32_si64(v104);
      v77 = _m_pfrcp(v75);
      v78 = _m_pfmul(_m_punpckldq(v76, v76), _m_pfrcpit2(_m_pfrcpit1(v75, v77), v77));
      v73 = _m_pfmul(v127, v78);
      v74 = _m_pfmul(v131, v78);
    }
  }
  v120 = v73;
  v122 = _m_pand(v74, (__m64)0xFFFFFFFFLL);
  v79 = v134;
  v80 = v136;
  v81 = _m_punpckhdq(v136, v136);
  if ( _mm_cvtsi64_si32(_m_pfcmpge(v81, (__m64)0x3F8000003F800000LL)) == 0 )
  {
    sub_6950C0(0, v53);
    v105 = _mm_cvtsi64_si32(v81);
    sub_6957C0();
    v79 = v134;
    v80 = v136;
    if ( _mm_cvtsi64_si32(_m_pfcmpge(_m_pand(v81, (__m64)0x7FFFFFFF7FFFFFFFLL), (__m64)0x3400000034000000LL)) != 0 )
    {
      v82 = _mm_cvtsi32_si64(v105);
      v83 = _m_pfrcp(v81);
      v84 = _m_pfmul(_m_punpckldq(v82, v82), _m_pfrcpit2(_m_pfrcpit1(v81, v83), v83));
      v79 = _m_pfmul(v134, v84);
      v80 = _m_pfmul(v136, v84);
    }
  }
  v128 = _m_pfmul(_m_pfadd(v120, v79), (__m64)0xBE800000BE800000uLL);
  v132 = _m_pfmul(_m_pfadd(v122, _m_pand(v80, (__m64)0xFFFFFFFFLL)), (__m64)0xBE800000BE800000uLL).m64_f32[0];
  v85 = _mm_cvtsi32_si64(LODWORD(v132));
  v86 = _m_pfadd(_m_pfmul(v128, v128), _m_pfmul(v85, v85));
  v87 = _m_pfacc(v86, v86);
  v88 = _m_pfrsqrt(v87);
  v89 = _m_pfrcpit2(_m_pfrsqit1(_m_pfmul(v88, v88), v87), v88);
  v106.m64_u64 = __PAIR64__(v103.m64_u32[1], _mm_cvtsi64_si32(v89));
  sub_6956A0();
  v90 = _m_pfmul(v87, v89);
  v91 = _m_pfcmpge(_m_pand(v90, (__m64)0x7FFFFFFFFFFFFFFFLL), (__m64)0x3400000034000000LL);
  v92 = _mm_cvtsi64_si32(_m_punpckhdq(v91, v91));
  v93 = v128;
  v94 = v90;
  v95 = _m_pfmul(_m_punpckhdq(v90, v90), v106);
  v96 = _mm_cvtsi32_si64(LODWORD(v132));
  if ( (v92 & 1) != 0 )
  {
    v97 = _m_punpckldq(v95, v95);
    v96 = _m_pfmul(v96, v97);
    v93 = _m_pfmul(v128, v97);
  }
  v124 = _m_punpckldq(v96, v94);
  v98 = _m_punpckldq(_m_punpckhdq(v93, v93), v93);
  v99 = _m_punpckldq(_m_punpckhdq(v124, v124), v124);
  a3->m64_u64 = (uint64_t)_m_pfacc(
                                    _m_pfsub(_m_pfmul(v98, v112), _m_pfmul(_m_pxor(v99, (__m64)0x80000000LL), v111)),
                                    _m_pfadd(_m_pxor(_m_pfmul(v93, v112), (__m64)0x80000000LL), _m_pfmul(v124, v111)));
  a3[1].m64_u64 = (uint64_t)_m_pfacc(
                                      _m_pfadd(_m_pfmul(_m_pxor(v98, (__m64)0x80000000LL), v111), _m_pfmul(v99, v112)),
                                      _m_pfsub(_m_pfmul(_m_pxor(v124, (__m64)0x80000000LL), v112), _m_pfmul(v93, v111)));
  a4->m64_u64 = (uint64_t)v111;
  a4[1].m64_u64 = (uint64_t)v112;
  _m_femms();
  return a4;
}


// ------------------------------------------------------------
// 0x68DCEA sub_68DCEA
// ------------------------------------------------------------
// 【L1】★ 3DNow! 4x4 矩阵乘（pfacc×16 = 16 个点积直证，D3DXMatrixMultiply AMD 版）【推断】
__m64 */*stdcall*/ sub_68DCEA(__m64 *a1, __m64 *a2, __m64 *a3)
{
  __m64 v3; // mm1
  __m64 v4; // mm4
  __m64 v5; // mm5
  __m64 v6; // mm7
  __m64 v7; // mm1
  __m64 v8; // mm6
  __m64 v9; // mm4
  __m64 v10; // mm2
  __m64 v12; // mm5
  __m64 v13; // mm4
  __m64 v14; // mm4
  __m64 v15; // mm5
  __m64 v16; // mm4
  __m64 v17; // mm5
  __m64 v18; // mm4
  __m64 v19; // mm5
  __m64 v20; // [esp+0h] [ebp-44h]
  __m64 v21; // [esp+8h] [ebp-3Ch]
  __m64 v22; // [esp+10h] [ebp-34h]
  __m64 v23; // [esp+18h] [ebp-2Ch]
  __m64 v24; // [esp+28h] [ebp-1Ch]
  __m64 v25; // [esp+30h] [ebp-14h]
  __m64 v26; // [esp+38h] [ebp-Ch]

  _m_femms();
  v3 = a3[2];
  v4 = a3[7];
  v5 = a3[5];
  v20 = _m_punpckldq((__m64)a3->m64_u64, v3);
  v22 = _m_punpckhdq((__m64)a3->m64_u64, v3);
  v6 = a3[3];
  v7 = a3[1];
  v24 = _m_punpckldq(v5, v4);
  v26 = _m_punpckhdq(v5, v4);
  v8 = _m_punpckldq(v7, v6);
  v9 = a3[6];
  v10 = a3[4];
  v25 = _m_punpckhdq(v7, v6);
  v23 = _m_punpckhdq(v10, v9);
  v21 = _m_punpckldq(v10, v9);
  v12 = a2[1];
  v13 = _m_pfadd(
          _m_pfacc(_m_pfmul((__m64)a2->m64_u64, v8), _m_pfmul((__m64)a2->m64_u64, v25)),
          _m_pfacc(_m_pfmul(v12, v24), _m_pfmul(v12, v26)));
  a1->m64_u64 = (uint64_t)_m_pfadd(
                                    _m_pfacc(_m_pfmul((__m64)a2->m64_u64, v20), _m_pfmul((__m64)a2->m64_u64, v22)),
                                    _m_pfacc(_m_pfmul(v12, v21), _m_pfmul(v12, v23)));
  a1[1].m64_u64 = (uint64_t)v13;
  v14 = a2[2];
  v15 = a2[3];
  a1[2].m64_u64 = (uint64_t)_m_pfadd(
                                      _m_pfacc(_m_pfmul(v14, v20), _m_pfmul(v14, v22)),
                                      _m_pfacc(_m_pfmul(v15, v21), _m_pfmul(v15, v23)));
  a1[3].m64_u64 = (uint64_t)_m_pfadd(
                                      _m_pfacc(_m_pfmul(v14, v8), _m_pfmul(v14, v25)),
                                      _m_pfacc(_m_pfmul(v15, v24), _m_pfmul(v15, v26)));
  v16 = a2[4];
  v17 = a2[5];
  a1[4].m64_u64 = (uint64_t)_m_pfadd(
                                      _m_pfacc(_m_pfmul(v16, v20), _m_pfmul(v16, v22)),
                                      _m_pfacc(_m_pfmul(v17, v21), _m_pfmul(v17, v23)));
  a1[5].m64_u64 = (uint64_t)_m_pfadd(
                                      _m_pfacc(_m_pfmul(v16, v8), _m_pfmul(v16, v25)),
                                      _m_pfacc(_m_pfmul(v17, v24), _m_pfmul(v17, v26)));
  v18 = a2[6];
  v19 = a2[7];
  a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                      _m_pfacc(_m_pfmul(v18, v20), _m_pfmul(v18, v22)),
                                      _m_pfacc(_m_pfmul(v19, v21), _m_pfmul(v19, v23)));
  a1[7].m64_u64 = (uint64_t)_m_pfadd(
                                      _m_pfacc(_m_pfmul(v18, v8), _m_pfmul(v18, v25)),
                                      _m_pfacc(_m_pfmul(v19, v24), _m_pfmul(v19, v26)));
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68DF1C sub_68DF1C
// ------------------------------------------------------------
// 【L1】3DNow! 矩阵行列式/伴随计算（pfacc 密集）【推断】
double /*stdcall*/ sub_68DF1C(unsigned int *a1)
{
  __m64 v1; // mm0
  __m64 v2; // mm3
  __m64 v3; // mm4
  __m64 v4; // mm2
  __m64 v5; // mm3
  __m64 v6; // mm4

  v1 = *(__m64 *)(a1 + 9);
  v2 = *(__m64 *)(a1 + 13);
  v3 = _m_pfsub(
         _m_pfmul(_m_punpckhdq(*((__m64 *)a1 + 7), *((__m64 *)a1 + 7)), v1),
         _m_pfmul(_m_punpckhdq(*((__m64 *)a1 + 5), *((__m64 *)a1 + 5)), v2));
  v4 = _m_pfsub(
         _m_pfmul(_m_punpckldq(*((__m64 *)a1 + 4), *((__m64 *)a1 + 4)), *((__m64 *)a1 + 7)),
         _m_pfmul(_m_punpckldq(*((__m64 *)a1 + 6), *((__m64 *)a1 + 6)), *((__m64 *)a1 + 5)));
  v5 = _m_pfsub(_m_pfmul(v2, *((__m64 *)a1 + 4)), _m_pfmul(v1, *((__m64 *)a1 + 6)));
  v6 = _m_pfsub(
         _m_pfmul(
           _m_pfsub(
             _m_pfadd(
               _m_pfmul(v3, *((__m64 *)a1 + 2)),
               _m_pfmul(v5, _m_punpckhdq(*((__m64 *)a1 + 3), *((__m64 *)a1 + 3)))),
             _m_pfmul(_m_punpckldq(_m_punpckhdq(v4, v4), v3), *(__m64 *)(a1 + 5))),
           _m_punpckldq(*((__m64 *)a1 + 1), (__m64)*a1)),
         _m_pfmul(
           _m_pfsub(
             _m_pfadd(
               _m_pfmul(_m_punpckhdq(v5, v3), _m_punpckldq(*((__m64 *)a1 + 2), *((__m64 *)a1 + 2))),
               _m_pfmul(_m_punpckldq(v5, v4), *((__m64 *)a1 + 3))),
             _m_pfmul(v4, *(__m64 *)(a1 + 5))),
           _m_punpckhdq(*((__m64 *)a1 + 1), *(__m64 *)a1)));
  _m_femms();
  return COERCE_FLOAT(_mm_cvtsi64_si32(_m_pfacc(v6, v6)));
}



// ------------------------------------------------------------
// 0x68DFEB sub_68DFEB
// ------------------------------------------------------------
// 【L1】3DNow! 单位矩阵构造（1.0f 对角 + femms）【推断】
__m64 */*stdcall*/ sub_68DFEB(__m64 *a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
  _m_femms();
  a1->m64_u64 = 1065353216;
  a1[1].m64_u64 = 0;
  a1[2].m64_u64 = 0x3F80000000000000LL;
  a1[3].m64_u64 = 0;
  a1[4].m64_u64 = 0;
  a1[5].m64_u64 = 1065353216;
  a1[6].m64_u64 = (uint64_t)_m_punpckldq(_mm_cvtsi32_si64(a2), _mm_cvtsi32_si64(a3));
  a1[7].m64_u64 = (uint64_t)_m_punpckldq(_mm_cvtsi32_si64(a4), (__m64)1065353216LL);
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68E03B sub_68E03B
// ------------------------------------------------------------
// 【L1】3DNow! 矩阵变换中型【推断】
__m64 */*stdcall*/ sub_68E03B(__m64 *a1, __m64 *a2, int a3)
{
  __m64 m64_u64; // mm6
  __m64 v5; // mm7
  __m64 v6; // mm3
  __m64 v7; // mm1
  __m64 v8; // mm0
  __m64 v9; // mm2
  __m64 v10; // mm1
  __m64 v11; // mm3
  __m64 v12; // mm1
  __m64 v13; // mm3
  __m64 v14; // [esp+0h] [ebp-14h] BYREF
  __m64 v15; // [esp+8h] [ebp-Ch]

  _m_femms();
  sub_692E28(&v14, a3);
  m64_u64 = (__m64)a2->m64_u64;
  v5 = a2[1];
  v6 = _m_pfmul(v5, v15);
  v7 = _m_pfadd(_m_pfmul((__m64)a2->m64_u64, v14), v6);
  v8 = _m_pxor(v14, (__m64)0x8000000080000000uLL);
  v9 = _m_pxor(v15, (__m64)0x8000000080000000uLL);
  v10 = _m_pfacc(v7, v7);
  v11 = _m_punpckldq(v6, v10);
  v12 = _m_psllqi(v10, 0x20u);
  v13 = _m_psrlqi(v11, 0x20u);
  a1->m64_u64 = (uint64_t)_m_pfadd(_m_pfmul(_m_punpckldq(v8, v8), (__m64)a2->m64_u64), v13);
  a1[1].m64_u64 = (uint64_t)_m_pfmul(_m_punpckldq(v8, v8), v5);
  a1[2].m64_u64 = (uint64_t)_m_pfadd(_m_pfmul(_m_punpckhdq(v8, v8), m64_u64), v12);
  a1[3].m64_u64 = (uint64_t)_m_pfmul(_m_punpckhdq(v8, v8), v5);
  a1[4].m64_u64 = (uint64_t)_m_pfmul(_m_punpckldq(v9, v9), m64_u64);
  a1[5].m64_u64 = (uint64_t)_m_pfadd(_m_pfmul(_m_punpckldq(v9, v9), v5), v13);
  a1[6].m64_u64 = (uint64_t)_m_pfmul(_m_punpckhdq(v9, v9), m64_u64);
  a1[7].m64_u64 = (uint64_t)_m_pfadd(_m_pfmul(_m_punpckhdq(v9, v9), v5), v12);
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68E126 sub_68E126
// ------------------------------------------------------------
// 【L1】3DNow! 矩阵构造/缩放（1.0f×3 对角）【推断】
__m64 */*stdcall*/ sub_68E126(__m64 *a1, int a2)
{
  __m64 v3; // mm3
  __m64 v4; // mm0
  __m64 v5; // mm1
  __m64 v6; // mm6
  __m64 v7; // mm4
  __m64 v8; // mm6
  __m64 v9; // mm4
  __m64 v10; // mm6
  __m64 v11; // [esp+0h] [ebp-14h] BYREF
  __m64 v12; // [esp+8h] [ebp-Ch]

  _m_femms();
  sub_692E28(&v11, a2);
  v3 = v12;
  v4 = _m_pfmul(v11, (__m64)0xC0000000C0000000uLL);
  v5 = _m_pfmul(v12, (__m64)0x3F800000C0000000LL);
  v6 = v11;
  v7 = _m_punpckldq(v6, v6);
  v8 = _m_punpckhdq(v6, v6);
  a1->m64_u64 = (uint64_t)_m_pfadd(_m_pfmul(v7, v4), (__m64)1065353216LL);
  a1[1].m64_u64 = (uint64_t)_m_pfmul(_m_psrlqi(v7, 0x20u), v5);
  a1[2].m64_u64 = (uint64_t)_m_pfadd(_m_pfmul(v8, v4), (__m64)0x3F80000000000000LL);
  a1[3].m64_u64 = (uint64_t)_m_pfmul(_m_psrlqi(v8, 0x20u), v5);
  v9 = _m_punpckldq(v3, v3);
  v10 = _m_punpckhdq(v3, v3);
  a1[4].m64_u64 = (uint64_t)_m_pfmul(v9, v4);
  a1[5].m64_u64 = (uint64_t)_m_pfadd(_m_pfmul(_m_psrlqi(v9, 0x20u), v5), (__m64)1065353216LL);
  a1[6].m64_u64 = (uint64_t)_m_pfmul(v10, v4);
  a1[7].m64_u64 = (uint64_t)_m_pfadd(_m_pfmul(_m_psrlqi(v10, 0x20u), v5), (__m64)0x3F80000000000000LL);
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68E202 sub_68E202
// ------------------------------------------------------------
// 【L1】混合路径小型变换（SSE+3DNow! 混编，整数入参 cvtsi×7）【推断】
__m64 */*stdcall*/ sub_68E202(__m64 *a1, unsigned int a2)
{
  __m64 v2; // mm0
  __m64 v4; // mm4

  _m_femms();
  v2 = _mm_cvtsi32_si64(a2);
  sub_6956A0();
  v4 = _m_psrlqi(v2, 0x20u);
  a1->m64_u64 = 1065353216;
  a1[1].m64_u64 = 0;
  a1[2].m64_i32[0] = _mm_cvtsi64_si32(0);
  a1[2].m64_i32[1] = _mm_cvtsi64_si32(v2);
  a1[3].m64_u64 = (uint64_t)v4;
  a1[6].m64_u64 = 0;
  a1[7].m64_u64 = 0x3F80000000000000LL;
  a1[4].m64_i32[0] = _mm_cvtsi64_si32(0);
  a1[4].m64_i32[1] = _mm_cvtsi64_si32(_m_pxor(v4, (__m64)0x80000000LL));
  a1[5].m64_i32[0] = _mm_cvtsi64_si32(v2);
  a1[5].m64_i32[1] = _mm_cvtsi64_si32(0);
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68E265 sub_68E265
// ------------------------------------------------------------
// 【L1】混合路径小型变换变体【推断】
__m64 */*stdcall*/ sub_68E265(__m64 *a1, unsigned int a2)
{
  __m64 v3; // mm4
  __m64 v4; // mm0
  __m64 v5; // mm4

  _m_femms();
  sub_6956A0();
  v3 = _mm_cvtsi32_si64(a2);
  v4 = _m_pand(v3, (__m64)0xFFFFFFFFLL);
  v5 = _m_psrlqi(v3, 0x20u);
  a1[2].m64_u64 = 0x3F80000000000000LL;
  a1[3].m64_u64 = 0;
  a1[6].m64_u64 = 0;
  a1[7].m64_u64 = 0x3F80000000000000LL;
  a1[4].m64_u64 = (uint64_t)v5;
  a1->m64_u64 = (uint64_t)v4;
  a1[5].m64_u64 = (uint64_t)v4;
  a1[1].m64_u64 = (uint64_t)_m_pxor(v5, (__m64)0x80000000LL);
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68E2C3 sub_68E2C3
// ------------------------------------------------------------
// 【L1】混合路径小型变换变体【推断】
__m64 */*stdcall*/ sub_68E2C3(__m64 *a1, unsigned int a2)
{
  __m64 v2; // mm0

  _m_femms();
  v2 = _mm_cvtsi32_si64(a2);
  sub_6956A0();
  a1->m64_u64 = (uint64_t)v2;
  a1[1].m64_u64 = 0;
  a1[3].m64_u64 = 0;
  a1[4].m64_u64 = 0;
  a1[5].m64_u64 = 1065353216;
  a1[6].m64_u64 = 0;
  a1[7].m64_u64 = 0x3F80000000000000LL;
  a1[2].m64_u64 = (uint64_t)_m_pxor(_m_punpckldq(_m_punpckhdq(v2, v2), v2), (__m64)0x80000000LL);
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68E31C sub_68E31C
// ------------------------------------------------------------
// 【L1】3DNow! 矩阵装配（三整数入参 → 单矩阵写入，与 68E2C3 成对）【推断】
__m64 */*stdcall*/ sub_68E31C(__m64 *a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
  _m_femms();
  a1->m64_u64 = (uint64_t)_mm_cvtsi32_si64(a2);
  a1[1].m64_u64 = 0;
  a1[3].m64_u64 = 0;
  a1[4].m64_u64 = 0;
  a1[6].m64_u64 = 0;
  a1[2].m64_u64 = (uint64_t)_m_psllqi(_mm_cvtsi32_si64(a3), 0x20u);
  a1[5].m64_u64 = (uint64_t)_mm_cvtsi32_si64(a4);
  a1[7].m64_u64 = 0x3F80000000000000LL;
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68E363 sub_68E363
// ------------------------------------------------------------
// 【L1】混合路径小型变换变体【推断】
__m64 */*stdcall*/ sub_68E363(__m64 *a1, __m64 *a2)
{
  __m64 v2; // mm1
  __m64 v3; // mm4
  __m64 v5; // mm2
  __m64 v6; // mm5
  __m64 v7; // mm7
  __m64 v8; // mm0
  __m64 v9; // mm1
  __m64 v10; // mm4

  v2 = a2[2];
  v3 = a2[7];
  v5 = _m_punpckhdq((__m64)a2->m64_u64, v2);
  v6 = a2[5];
  a1->m64_u64 = (uint64_t)_m_punpckldq((__m64)a2->m64_u64, v2);
  a1[2].m64_u64 = (uint64_t)v5;
  v7 = a2[3];
  v8 = a2[4];
  v9 = a2[1];
  a1[5].m64_u64 = (uint64_t)_m_punpckldq(v6, v3);
  a1[7].m64_u64 = (uint64_t)_m_punpckhdq(v6, v3);
  v10 = a2[6];
  a1[4].m64_u64 = (uint64_t)_m_punpckldq(v9, v7);
  a1[6].m64_u64 = (uint64_t)_m_punpckhdq(v9, v7);
  a1[3].m64_u64 = (uint64_t)_m_punpckhdq(v8, v10);
  a1[1].m64_u64 = (uint64_t)_m_punpckldq(v8, v10);
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68E3D2 sub_68E3D2
// ------------------------------------------------------------
// 【L1】3DNow! 矩阵转置/轻操作（cdecl 单参）【推断】
__m64 */*cdecl*/ sub_68E3D2(__m64 *a1)
{
  __m64 v1; // mm1
  __m64 v3; // mm2

  v1 = _mm_cvtsi32_si64(0x3F800000u);
  a1->m64_u64 = (uint64_t)v1;
  a1[1].m64_u64 = 0;
  a1[3].m64_u64 = 0;
  a1[4].m64_u64 = 0;
  a1[5].m64_u64 = (uint64_t)v1;
  v3 = _m_punpckldq(_m_punpckhdq(v1, v1), v1);
  a1[6].m64_u64 = 0;
  a1[2].m64_u64 = (uint64_t)v3;
  a1[7].m64_u64 = (uint64_t)v3;
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68E40B sub_68E40B
// ------------------------------------------------------------
// 【L1】混合路径小型变换变体【推断】
__m64 */*stdcall*/ sub_68E40B(__m64 *a1, __m64 *a2)
{
  __m64 m64_u64; // mm3
  __m64 v4; // mm0
  __m64 v5; // mm7
  __m64 v6; // mm2
  __m64 v7; // mm4
  __m64 v8; // mm3
  __m64 v9; // mm1
  __m64 v10; // mm5
  __m64 v11; // mm7
  __m64 v12; // mm6
  __m64 v13; // mm2
  __m64 v14; // mm1
  __m64 v15; // mm6
  __m64 v16; // mm7
  __m64 v17; // mm3
  __m64 v18; // mm2
  __m64 v19; // mm3
  __m64 v20; // mm5
  __m64 v21; // mm6

  m64_u64 = (__m64)a2->m64_u64;
  v4 = _m_pfadd(m64_u64, m64_u64);
  v5 = a2[1];
  v6 = _m_punpckhdq(m64_u64, m64_u64);
  v7 = _m_punpckhdq(v5, v5);
  v8 = _m_pfmul((__m64)a2->m64_u64, v4);
  v9 = _m_punpckldq(_m_pfadd(v5, v5), v4);
  v10 = _m_pfmul(v4, v7);
  v11 = _m_pfmul(_m_punpckldq(v5, v5), v9);
  v12 = _m_pfmul(v9, v7);
  v13 = _m_pfmul(v9, v6);
  v14 = _m_punpckhdq(v13, v11);
  a1[6].m64_u64 = 0;
  v15 = _m_punpckhdq(_m_punpckldq(v12, v12), v10);
  v16 = _m_pfsubr(_m_pfadd(_m_punpckldq(v11, v11), v8), (__m64)0x3F8000003F800000LL);
  a1[5].m64_u64 = (uint64_t)_m_punpckldq(_m_pfsubr(_m_pfacc(v8, v8), (__m64)0x3F8000003F800000LL), 0);
  v17 = v13;
  v18 = _m_pfadd(v13, v10);
  v19 = _m_pfsub(v17, v10);
  v20 = _m_pfsub(v14, v15);
  v21 = _m_pfadd(v14, v15);
  a1[3].m64_u64 = (uint64_t)_m_punpckldq(v18, 0);
  a1[1].m64_u64 = (uint64_t)_m_punpckhdq(v20, 0);
  a1[2].m64_u64 = (uint64_t)_m_punpckldq(v20, v16);
  a1->m64_u64 = (uint64_t)_m_punpckhdq(v16, _m_punpckldq(v21, v21));
  a1[4].m64_u64 = (uint64_t)_m_punpckldq(_m_punpckhdq(v21, v21), v19);
  a1[7].m64_u64 = (uint64_t)_m_punpckldq(0, (__m64)1065353216LL);
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68E4DD sub_68E4DD
// ------------------------------------------------------------
// 【L1】★ 3DNow! 四元数→旋转矩阵（x²/y²/z² 与 1-2(y²+z²) 组合直证，D3DXQuaternionRotationMatrix AMD 版）
__m64 */*stdcall*/ sub_68E4DD(__m64 *a1, __m64 *a2)
{
  __m64 v3; // mm4
  __m64 v4; // mm1
  __m64 v5; // mm5
  __m64 v6; // mm0
  __m64 v7; // mm5
  __m64 v8; // mm2
  __m64 v9; // mm3
  __m64 v10; // mm1
  __m64 v11; // mm6
  __m64 v12; // mm3
  __m64 v13; // mm6
  __m64 v14; // mm2
  __m64 v15; // mm1

  v3 = a2[1];
  v4 = _m_pfadd(v3, v3);
  v5 = _m_pfadd((__m64)a2->m64_u64, (__m64)a2->m64_u64);
  v6 = _m_pfmul(v5, (__m64)a2->m64_u64);
  v7 = _m_punpckldq(v5, v4);
  v8 = _m_pfmul((__m64)a2->m64_u64, v4);
  v9 = _m_pfmul(_m_pswapd((__m64)a2->m64_u64), v4);
  v10 = _m_pfmul(v4, v3);
  v11 = _m_pfmul(_m_punpckhdq((__m64)a2->m64_u64, v3), v7);
  v12 = _m_pfpnacc(v9, v9);
  v13 = _m_pfpnacc(v11, v11);
  v14 = _m_pfpnacc(v8, v8);
  v15 = _m_pfsub(_m_pfsubr(v6, (__m64)0x3F8000003F800000LL), _m_punpckldq(v10, v10));
  a1[6].m64_u64 = 0;
  a1[4].m64_u64 = (uint64_t)_m_punpckldq(_m_pswapd(v14), v12);
  a1[1].m64_u64 = (uint64_t)_m_punpckldq(v14, 0);
  a1[5].m64_u64 = (uint64_t)_m_punpckhdq(_m_pfsubr(_m_pfacc(v6, v6), (__m64)0x3F8000003F800000LL), 0);
  a1->m64_u64 = (uint64_t)_m_punpckhdq(v15, v13);
  a1[2].m64_u64 = (uint64_t)_m_punpckldq(v13, v15);
  a1[3].m64_u64 = (uint64_t)_m_punpckhdq(v12, 0);
  a1[7].m64_u64 = (uint64_t)_m_punpckldq(0, (__m64)1065353216LL);
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68E592 sub_68E592
// ------------------------------------------------------------
// 【L1】★ 3DNow! 仿射组合巨型（967 行，7 参：四元数×缩放×平移全展开，D3DXMatrixAffineTransformation AMD 版）
__m64 */*stdcall*/ sub_68E592(__m64 *a1, __m64 *a2, __m64 *a3, __m64 *a4, __m64 *a5, __m64 *a6, __m64 *a7)
{
  __m64 *result; // eax
  __m64 m64_u64; // mm3
  __m64 v9; // mm0
  __m64 v10; // mm7
  __m64 v11; // mm2
  __m64 v12; // mm4
  __m64 v13; // mm3
  __m64 v14; // mm1
  __m64 v15; // mm5
  __m64 v16; // mm7
  __m64 v17; // mm6
  __m64 v18; // mm2
  __m64 v19; // mm1
  __m64 v20; // mm6
  __m64 v21; // mm7
  __m64 v22; // mm3
  __m64 v23; // mm2
  __m64 v24; // mm3
  __m64 v25; // mm5
  __m64 v26; // mm6
  __m64 v27; // mm3
  __m64 v28; // mm4
  __m64 v29; // mm1
  __m64 v30; // mm2
  __m64 v31; // mm2
  __m64 v32; // mm1
  __m64 v33; // mm2
  __m64 v34; // mm3
  __m64 v35; // mm0
  __m64 v36; // mm1
  __m64 v37; // mm2
  __m64 v38; // mm5
  __m64 v39; // mm3
  __m64 v40; // mm2
  __m64 v41; // mm7
  __m64 v42; // mm0
  __m64 v43; // mm3
  __m64 v44; // mm1
  __m64 v45; // mm2
  __m64 v46; // mm3
  __m64 v47; // mm0
  __m64 v48; // mm1
  __m64 v49; // mm2
  __m64 v50; // mm5
  __m64 v51; // mm3
  __m64 v52; // mm2
  __m64 v53; // mm7
  __m64 v54; // mm0
  __m64 v55; // mm3
  __m64 v56; // mm1
  __m64 v57; // mm2
  __m64 v58; // mm3
  __m64 v59; // mm0
  __m64 v60; // mm1
  __m64 v61; // mm2
  __m64 v62; // mm5
  __m64 v63; // mm3
  __m64 v64; // mm2
  __m64 v65; // mm7
  __m64 v66; // mm0
  __m64 v67; // mm3
  __m64 v68; // mm1
  __m64 v69; // mm2
  __m64 v70; // mm3
  __m64 v71; // mm0
  __m64 v72; // mm1
  __m64 v73; // mm2
  __m64 v74; // mm5
  __m64 v75; // mm3
  __m64 v76; // mm7
  __m64 v77; // mm2
  __m64 v78; // mm3
  __m64 v79; // mm1
  __m64 v80; // mm2
  __m64 v81; // mm3
  __m64 v82; // mm0
  __m64 v83; // mm1
  __m64 v84; // mm2
  __m64 v85; // mm5
  __m64 v86; // mm3
  __m64 v87; // mm2
  __m64 v88; // mm7
  __m64 v89; // mm0
  __m64 v90; // mm3
  __m64 v91; // mm1
  __m64 v92; // mm2
  __m64 v93; // mm3
  __m64 v94; // mm0
  __m64 v95; // mm1
  __m64 v96; // mm2
  __m64 v97; // mm5
  __m64 v98; // mm3
  __m64 v99; // mm2
  __m64 v100; // mm7
  __m64 v101; // mm0
  __m64 v102; // mm3
  __m64 v103; // mm1
  __m64 v104; // mm2
  __m64 v105; // mm3
  __m64 v106; // mm0
  __m64 v107; // mm1
  __m64 v108; // mm2
  __m64 v109; // mm5
  __m64 v110; // mm3
  __m64 v111; // mm2
  __m64 v112; // mm7
  __m64 v113; // mm0
  __m64 v114; // mm3
  __m64 v115; // mm1
  __m64 v116; // mm2
  __m64 v117; // mm3
  __m64 v118; // mm0
  __m64 v119; // mm1
  __m64 v120; // mm2
  __m64 v121; // mm5
  __m64 v122; // mm3
  __m64 v123; // mm7
  __m64 v124; // mm2
  __m64 v125; // mm3
  __m64 v126; // mm1
  __m64 v127; // mm2
  __m64 v128; // mm3
  __m64 v129; // mm0
  __m64 v130; // mm1
  __m64 v131; // mm2
  __m64 v132; // mm5
  __m64 v133; // mm3
  __m64 v134; // mm2
  __m64 v135; // mm7
  __m64 v136; // mm0
  __m64 v137; // mm3
  __m64 v138; // mm1
  __m64 v139; // mm2
  __m64 v140; // mm3
  __m64 v141; // mm0
  __m64 v142; // mm1
  __m64 v143; // mm2
  __m64 v144; // mm5
  __m64 v145; // mm3
  __m64 v146; // mm2
  __m64 v147; // mm7
  __m64 v148; // mm0
  __m64 v149; // mm3
  __m64 v150; // mm1
  __m64 v151; // mm2
  __m64 v152; // mm3
  __m64 v153; // mm0
  __m64 v154; // mm1
  __m64 v155; // mm2
  __m64 v156; // mm5
  __m64 v157; // mm3
  __m64 v158; // mm2
  __m64 v159; // mm7
  __m64 v160; // mm0
  __m64 v161; // mm3
  __m64 v162; // mm1
  __m64 v163; // mm2
  __m64 v164; // mm3
  __m64 v165; // mm0
  __m64 v166; // mm1
  __m64 v167; // mm2
  __m64 v168; // mm3
  __m64 v169; // mm2
  __m64 v170; // mm3
  __m64 v171; // mm2
  __m64 v172; // mm1
  __m64 v173; // mm2
  __m64 v174; // mm3
  __m64 v175; // mm0
  __m64 v176; // mm1
  __m64 v177; // mm2
  __m64 v178; // mm5
  __m64 v179; // mm3
  __m64 v180; // mm2
  __m64 v181; // mm7
  __m64 v182; // mm0
  __m64 v183; // mm3
  __m64 v184; // mm1
  __m64 v185; // mm2
  __m64 v186; // mm3
  __m64 v187; // mm0
  __m64 v188; // mm1
  __m64 v189; // mm2
  __m64 v190; // mm5
  __m64 v191; // mm3
  __m64 v192; // mm2
  __m64 v193; // mm7
  __m64 v194; // mm0
  __m64 v195; // mm3
  __m64 v196; // mm1
  __m64 v197; // mm2
  __m64 v198; // mm3
  __m64 v199; // mm0
  __m64 v200; // mm1
  __m64 v201; // mm2
  __m64 v202; // mm5
  __m64 v203; // mm3
  __m64 v204; // mm2
  __m64 v205; // mm7
  __m64 v206; // mm0
  __m64 v207; // mm3
  __m64 v208; // mm1
  __m64 v209; // mm2
  __m64 v210; // mm3
  __m64 v211; // mm0
  __m64 v212; // mm1
  __m64 v213; // mm2
  __m64 v214; // mm5
  __m64 v215; // mm3
  __m64 v216; // mm7
  __m64 v217; // mm2
  __m64 v218; // mm3
  __m64 v219; // mm1
  __m64 v220; // mm2
  __m64 v221; // mm3
  __m64 v222; // mm0
  __m64 v223; // mm1
  __m64 v224; // mm2
  __m64 v225; // mm5
  __m64 v226; // mm3
  __m64 v227; // mm2
  __m64 v228; // mm7
  __m64 v229; // mm0
  __m64 v230; // mm3
  __m64 v231; // mm1
  __m64 v232; // mm2
  __m64 v233; // mm3
  __m64 v234; // mm0
  __m64 v235; // mm1
  __m64 v236; // mm2
  __m64 v237; // mm5
  __m64 v238; // mm3
  __m64 v239; // mm2
  __m64 v240; // mm7
  __m64 v241; // mm0
  __m64 v242; // mm3
  __m64 v243; // mm1
  __m64 v244; // mm2
  __m64 v245; // mm3
  __m64 v246; // mm0
  __m64 v247; // mm1
  __m64 v248; // mm2
  __m64 v249; // mm5
  __m64 v250; // mm3
  __m64 v251; // mm2
  __m64 v252; // mm7
  __m64 v253; // mm0
  __m64 v254; // mm3
  __m64 v255; // mm1
  __m64 v256; // mm2
  __m64 v257; // mm3
  __m64 v258; // mm0
  __m64 v259; // mm1
  __m64 v260; // mm2
  __m64 v261; // mm3
  __m64 v262; // mm4
  __m64 v263; // mm5
  __m64 v264; // mm1
  __m64 v265; // mm2
  __m64 v266; // mm3
  __m64 v267; // mm0
  __m64 v268; // mm7
  __m64 v269; // mm2
  __m64 v270; // mm4
  __m64 v271; // mm3
  __m64 v272; // mm1
  __m64 v273; // mm5
  __m64 v274; // mm7
  __m64 v275; // mm6
  __m64 v276; // mm2
  __m64 v277; // mm1
  __m64 v278; // mm6
  __m64 v279; // mm7
  __m64 v280; // mm3
  __m64 v281; // mm2
  __m64 v282; // mm3
  __m64 v283; // mm5
  __m64 v284; // mm2
  __m64 v285; // mm6
  __m64 v286; // mm2
  __m64 v287; // mm3
  __m64 v288; // mm1
  __m64 v289; // mm1
  __m64 v290; // mm2
  __m64 v291; // mm3
  __m64 v292; // mm0
  __m64 v293; // mm1
  __m64 v294; // mm2
  __m64 v295; // mm5
  __m64 v296; // mm3
  __m64 v297; // mm2
  __m64 v298; // mm7
  __m64 v299; // mm0
  __m64 v300; // mm3
  __m64 v301; // mm1
  __m64 v302; // mm2
  __m64 v303; // mm3
  __m64 v304; // mm0
  __m64 v305; // mm1
  __m64 v306; // mm2
  __m64 v307; // mm5
  __m64 v308; // mm3
  __m64 v309; // mm2
  __m64 v310; // mm7
  __m64 v311; // mm0
  __m64 v312; // mm3
  __m64 v313; // mm1
  __m64 v314; // mm2
  __m64 v315; // mm3
  __m64 v316; // mm0
  __m64 v317; // mm1
  __m64 v318; // mm2
  __m64 v319; // mm5
  __m64 v320; // mm3
  __m64 v321; // mm2
  __m64 v322; // mm7
  __m64 v323; // mm0
  __m64 v324; // mm3
  __m64 v325; // mm1
  __m64 v326; // mm2
  __m64 v327; // mm3
  __m64 v328; // mm0
  __m64 v329; // mm1
  __m64 v330; // mm2
  __m64 v331; // mm3
  __m64 v332; // mm1
  __m64 v333; // mm1
  __m64 v334; // mm2
  __m64 v335; // mm3
  __m64 v336; // mm0
  __m64 v337; // mm1
  __m64 v338; // mm2
  __m64 v339; // mm5
  __m64 v340; // mm3
  __m64 v341; // mm2
  __m64 v342; // mm7
  __m64 v343; // mm0
  __m64 v344; // mm3
  __m64 v345; // mm1
  __m64 v346; // mm2
  __m64 v347; // mm3
  __m64 v348; // mm0
  __m64 v349; // mm1
  __m64 v350; // mm2
  __m64 v351; // mm5
  __m64 v352; // mm3
  __m64 v353; // mm2
  __m64 v354; // mm7
  __m64 v355; // mm0
  __m64 v356; // mm3
  __m64 v357; // mm1
  __m64 v358; // mm2
  __m64 v359; // mm3
  __m64 v360; // mm0
  __m64 v361; // mm1
  __m64 v362; // mm2
  __m64 v363; // mm5
  __m64 v364; // mm3
  __m64 v365; // mm2
  __m64 v366; // mm7
  __m64 v367; // mm0
  __m64 v368; // mm3
  __m64 v369; // mm1
  __m64 v370; // mm2
  __m64 v371; // mm3
  __m64 v372; // mm0
  __m64 v373; // mm1
  __m64 v374; // mm2
  __m64 v375; // mm3
  __m64 v376; // mm1
  __m64 v377; // [esp+0h] [ebp-C0h]
  __m64 v378; // [esp+10h] [ebp-B0h]
  __m64 v379; // [esp+28h] [ebp-98h]
  __m64 v380; // [esp+40h] [ebp-80h]
  __m64 v381; // [esp+40h] [ebp-80h]
  __m64 v382; // [esp+48h] [ebp-78h]
  __m64 v383; // [esp+48h] [ebp-78h]
  __m64 v384; // [esp+50h] [ebp-70h]
  __m64 v385; // [esp+50h] [ebp-70h]
  __m64 v386; // [esp+58h] [ebp-68h]
  __m64 v387; // [esp+58h] [ebp-68h]
  __m64 v388; // [esp+60h] [ebp-60h]
  __m64 v389; // [esp+60h] [ebp-60h]
  __m64 v390; // [esp+68h] [ebp-58h]
  __m64 v391; // [esp+68h] [ebp-58h]
  __m64 v392; // [esp+78h] [ebp-48h]
  __m64 v393; // [esp+78h] [ebp-48h]
  __m64 v394; // [esp+80h] [ebp-40h]
  __m64 v395; // [esp+88h] [ebp-38h]
  __m64 v396; // [esp+90h] [ebp-30h]
  __m64 v397; // [esp+98h] [ebp-28h]
  __m64 v398; // [esp+A0h] [ebp-20h]
  __m64 v399; // [esp+A8h] [ebp-18h]
  __m64 v400; // [esp+B0h] [ebp-10h]
  __m64 v401; // [esp+B8h] [ebp-8h]

  result = a1;
  if ( a4 != nullptr )
  {
    if ( a3 != nullptr )
    {
      v377 = _m_punpckldq((__m64)a4->m64_u64, 0);
      v378 = _m_punpckhdq(0, (__m64)a4->m64_u64);
      v379 = _mm_cvtsi32_si64(a4[1].m64_u32[0]);
      m64_u64 = (__m64)a3->m64_u64;
      v9 = _m_pfadd(m64_u64, m64_u64);
      v10 = a3[1];
      v11 = _m_punpckhdq(m64_u64, m64_u64);
      v12 = _m_punpckhdq(v10, v10);
      v13 = _m_pfmul((__m64)a3->m64_u64, v9);
      v14 = _m_punpckldq(_m_pfadd(v10, v10), v9);
      v15 = _m_pfmul(v9, v12);
      v16 = _m_pfmul(_m_punpckldq(v10, v10), v14);
      v17 = _m_pfmul(v14, v12);
      v18 = _m_pfmul(v14, v11);
      v19 = _m_punpckhdq(v18, v16);
      v20 = _m_punpckhdq(_m_punpckldq(v17, v17), v15);
      v21 = _m_pfsubr(_m_pfadd(_m_punpckldq(v16, v16), v13), (__m64)0x3F8000003F800000LL);
      v390 = _m_punpckldq(_m_pfsubr(_m_pfacc(v13, v13), (__m64)0x3F8000003F800000LL), 0);
      v22 = v18;
      v23 = _m_pfadd(v18, v15);
      v24 = _m_pfsub(v22, v15);
      v25 = _m_pfsub(v19, v20);
      v26 = _m_pfadd(v19, v20);
      v386 = _m_punpckldq(v23, 0);
      v382 = _m_punpckhdq(v25, 0);
      v384 = _m_punpckldq(v25, v21);
      v380 = _m_punpckhdq(v21, _m_punpckldq(v26, v26));
      v388 = _m_punpckldq(_m_punpckhdq(v26, v26), v24);
      v392 = _m_punpckldq(0, (__m64)1065353216LL);
      if ( a2 != nullptr )
      {
        v394 = _m_punpckldq(v380, v384);
        v396 = _m_punpckhdq(v380, v384);
        v399 = _m_punpckldq(v390, v392);
        v401 = _m_punpckhdq(v390, v392);
        v398 = _m_punpckldq(v382, v386);
        v400 = _m_punpckhdq(v382, v386);
        v397 = _m_punpckhdq(v388, 0);
        v395 = _m_punpckldq(v388, 0);
        result = a1;
        v27 = (__m64)a2->m64_u64;
        v28 = _mm_cvtsi32_si64(a2[1].m64_u32[0]);
        v29 = _mm_cvtsi32_si64(0x3F800000u);
        v30 = _m_punpckldq(_m_punpckhdq(v29, v29), v29);
        a1->m64_u64 = (uint64_t)v29;
        a1[1].m64_u64 = 0;
        a1[2].m64_u64 = (uint64_t)v30;
        a1[3].m64_u64 = 0;
        a1[4].m64_u64 = 0;
        a1[5].m64_u64 = (uint64_t)v29;
        v31 = _m_pfsub(v30, v28);
        a1[7].m64_u64 = (uint64_t)v31;
        a1[6].m64_u64 = (uint64_t)_m_pfsub(0, v27);
        v32 = a1[1];
        v33 = _m_punpckhdq(v31, (__m64)a1->m64_u64);
        v34 = _m_punpckhdq(v27, v32);
        v35 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
        v36 = _m_punpckldq(v32, v32);
        v37 = _m_punpckhdq(v33, v33);
        v38 = _m_pfmul(v396, v37);
        v39 = _m_punpckhdq(v34, v34);
        v40 = _m_pfadd(_m_pfadd(_m_pfmul(v37, v397), _m_pfmul(v35, v395)), _m_pfmul(v36, v399));
        v41 = _m_pfadd(_m_pfmul(v400, v39), _m_pfadd(_m_pfmul(v398, v36), _m_pfadd(v38, _m_pfmul(v394, v35))));
        v42 = a1[2];
        v43 = _m_pfadd(_m_pfmul(v39, v401), v40);
        v44 = a1[3];
        a1->m64_u64 = (uint64_t)v41;
        a1[1].m64_u64 = (uint64_t)v43;
        v45 = _m_punpckhdq(v40, v42);
        v46 = _m_punpckhdq(v43, v44);
        v47 = _m_punpckldq(v42, v42);
        v48 = _m_punpckldq(v44, v44);
        v49 = _m_punpckhdq(v45, v45);
        v50 = _m_pfmul(v396, v49);
        v51 = _m_punpckhdq(v46, v46);
        v52 = _m_pfadd(_m_pfadd(_m_pfmul(v49, v397), _m_pfmul(v47, v395)), _m_pfmul(v48, v399));
        v53 = _m_pfadd(_m_pfmul(v400, v51), _m_pfadd(_m_pfmul(v398, v48), _m_pfadd(v50, _m_pfmul(v394, v47))));
        v54 = a1[4];
        v55 = _m_pfadd(_m_pfmul(v51, v401), v52);
        v56 = a1[5];
        a1[2].m64_u64 = (uint64_t)v53;
        a1[3].m64_u64 = (uint64_t)v55;
        v57 = _m_punpckhdq(v52, v54);
        v58 = _m_punpckhdq(v55, v56);
        v59 = _m_punpckldq(v54, v54);
        v60 = _m_punpckldq(v56, v56);
        v61 = _m_punpckhdq(v57, v57);
        v62 = _m_pfmul(v396, v61);
        v63 = _m_punpckhdq(v58, v58);
        v64 = _m_pfadd(_m_pfadd(_m_pfmul(v61, v397), _m_pfmul(v59, v395)), _m_pfmul(v60, v399));
        v65 = _m_pfadd(_m_pfmul(v400, v63), _m_pfadd(_m_pfmul(v398, v60), _m_pfadd(v62, _m_pfmul(v394, v59))));
        v66 = a1[6];
        v67 = _m_pfadd(_m_pfmul(v63, v401), v64);
        v68 = a1[7];
        a1[4].m64_u64 = (uint64_t)v65;
        a1[5].m64_u64 = (uint64_t)v67;
        v69 = _m_punpckhdq(v64, v66);
        v70 = _m_punpckhdq(v67, v68);
        v71 = _m_punpckldq(v66, v66);
        v72 = _m_punpckldq(v68, v68);
        v73 = _m_punpckhdq(v69, v69);
        v74 = _m_pfmul(v396, v73);
        v75 = _m_punpckhdq(v70, v70);
        v76 = _m_pfmul(v400, v75);
        v77 = _m_pfadd(_m_pfadd(_m_pfmul(v73, v397), _m_pfmul(v71, v395)), _m_pfmul(v72, v399));
        v78 = _m_pfadd(_m_pfmul(v75, v401), v77);
        a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                            v76,
                                            _m_pfadd(_m_pfmul(v398, v72), _m_pfadd(v74, _m_pfmul(v394, v71))));
        a1[7].m64_u64 = (uint64_t)v78;
        v79 = a1[1];
        v80 = _m_punpckhdq(v77, (__m64)a1->m64_u64);
        v81 = _m_punpckhdq(v78, v79);
        v82 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
        v83 = _m_punpckldq(v79, v79);
        v84 = _m_punpckhdq(v80, v80);
        v85 = _m_pfmul(v378, v84);
        v86 = _m_punpckhdq(v81, v81);
        v87 = _m_pfadd(_m_pfadd(_m_pfmul(v84, 0), _m_pfmul(v82, 0)), _m_pfmul(v83, v379));
        v88 = _m_pfadd(_m_pfmul(0, v86), _m_pfadd(_m_pfmul(0, v83), _m_pfadd(v85, _m_pfmul(v377, v82))));
        v89 = a1[2];
        v90 = _m_pfadd(_m_pfmul(v86, (__m64)0x3F80000000000000LL), v87);
        v91 = a1[3];
        a1->m64_u64 = (uint64_t)v88;
        a1[1].m64_u64 = (uint64_t)v90;
        v92 = _m_punpckhdq(v87, v89);
        v93 = _m_punpckhdq(v90, v91);
        v94 = _m_punpckldq(v89, v89);
        v95 = _m_punpckldq(v91, v91);
        v96 = _m_punpckhdq(v92, v92);
        v97 = _m_pfmul(v378, v96);
        v98 = _m_punpckhdq(v93, v93);
        v99 = _m_pfadd(_m_pfadd(_m_pfmul(v96, 0), _m_pfmul(v94, 0)), _m_pfmul(v95, v379));
        v100 = _m_pfadd(_m_pfmul(0, v98), _m_pfadd(_m_pfmul(0, v95), _m_pfadd(v97, _m_pfmul(v377, v94))));
        v101 = a1[4];
        v102 = _m_pfadd(_m_pfmul(v98, (__m64)0x3F80000000000000LL), v99);
        v103 = a1[5];
        a1[2].m64_u64 = (uint64_t)v100;
        a1[3].m64_u64 = (uint64_t)v102;
        v104 = _m_punpckhdq(v99, v101);
        v105 = _m_punpckhdq(v102, v103);
        v106 = _m_punpckldq(v101, v101);
        v107 = _m_punpckldq(v103, v103);
        v108 = _m_punpckhdq(v104, v104);
        v109 = _m_pfmul(v378, v108);
        v110 = _m_punpckhdq(v105, v105);
        v111 = _m_pfadd(_m_pfadd(_m_pfmul(v108, 0), _m_pfmul(v106, 0)), _m_pfmul(v107, v379));
        v112 = _m_pfadd(_m_pfmul(0, v110), _m_pfadd(_m_pfmul(0, v107), _m_pfadd(v109, _m_pfmul(v377, v106))));
        v113 = a1[6];
        v114 = _m_pfadd(_m_pfmul(v110, (__m64)0x3F80000000000000LL), v111);
        v115 = a1[7];
        a1[4].m64_u64 = (uint64_t)v112;
        a1[5].m64_u64 = (uint64_t)v114;
        v116 = _m_punpckhdq(v111, v113);
        v117 = _m_punpckhdq(v114, v115);
        v118 = _m_punpckldq(v113, v113);
        v119 = _m_punpckldq(v115, v115);
        v120 = _m_punpckhdq(v116, v116);
        v121 = _m_pfmul(v378, v120);
        v122 = _m_punpckhdq(v117, v117);
        v123 = _m_pfmul(0, v122);
        v124 = _m_pfadd(_m_pfadd(_m_pfmul(v120, 0), _m_pfmul(v118, 0)), _m_pfmul(v119, v379));
        v125 = _m_pfadd(_m_pfmul(v122, (__m64)0x3F80000000000000LL), v124);
        a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                            v123,
                                            _m_pfadd(_m_pfmul(0, v119), _m_pfadd(v121, _m_pfmul(v377, v118))));
        a1[7].m64_u64 = (uint64_t)v125;
        v126 = a1[1];
        v127 = _m_punpckhdq(v124, (__m64)a1->m64_u64);
        v128 = _m_punpckhdq(v125, v126);
        v129 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
        v130 = _m_punpckldq(v126, v126);
        v131 = _m_punpckhdq(v127, v127);
        v132 = _m_pfmul(v384, v131);
        v133 = _m_punpckhdq(v128, v128);
        v134 = _m_pfadd(_m_pfadd(_m_pfmul(v131, v386), _m_pfmul(v129, v382)), _m_pfmul(v130, v390));
        v135 = _m_pfadd(_m_pfmul(0, v133), _m_pfadd(_m_pfmul(v388, v130), _m_pfadd(v132, _m_pfmul(v380, v129))));
        v136 = a1[2];
        v137 = _m_pfadd(_m_pfmul(v133, v392), v134);
        v138 = a1[3];
        a1->m64_u64 = (uint64_t)v135;
        a1[1].m64_u64 = (uint64_t)v137;
        v139 = _m_punpckhdq(v134, v136);
        v140 = _m_punpckhdq(v137, v138);
        v141 = _m_punpckldq(v136, v136);
        v142 = _m_punpckldq(v138, v138);
        v143 = _m_punpckhdq(v139, v139);
        v144 = _m_pfmul(v384, v143);
        v145 = _m_punpckhdq(v140, v140);
        v146 = _m_pfadd(_m_pfadd(_m_pfmul(v143, v386), _m_pfmul(v141, v382)), _m_pfmul(v142, v390));
        v147 = _m_pfadd(_m_pfmul(0, v145), _m_pfadd(_m_pfmul(v388, v142), _m_pfadd(v144, _m_pfmul(v380, v141))));
        v148 = a1[4];
        v149 = _m_pfadd(_m_pfmul(v145, v392), v146);
        v150 = a1[5];
        a1[2].m64_u64 = (uint64_t)v147;
        a1[3].m64_u64 = (uint64_t)v149;
        v151 = _m_punpckhdq(v146, v148);
        v152 = _m_punpckhdq(v149, v150);
        v153 = _m_punpckldq(v148, v148);
        v154 = _m_punpckldq(v150, v150);
        v155 = _m_punpckhdq(v151, v151);
        v156 = _m_pfmul(v384, v155);
        v157 = _m_punpckhdq(v152, v152);
        v158 = _m_pfadd(_m_pfadd(_m_pfmul(v155, v386), _m_pfmul(v153, v382)), _m_pfmul(v154, v390));
        v159 = _m_pfadd(_m_pfmul(0, v157), _m_pfadd(_m_pfmul(v388, v154), _m_pfadd(v156, _m_pfmul(v380, v153))));
        v160 = a1[6];
        v161 = _m_pfadd(_m_pfmul(v157, v392), v158);
        v162 = a1[7];
        a1[4].m64_u64 = (uint64_t)v159;
        a1[5].m64_u64 = (uint64_t)v161;
        v163 = _m_punpckhdq(v158, v160);
        v164 = _m_punpckhdq(v161, v162);
        v165 = _m_punpckldq(v160, v160);
        v166 = _m_punpckldq(v162, v162);
        v167 = _m_punpckhdq(v163, v163);
        v168 = _m_punpckhdq(v164, v164);
        a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                            _m_pfmul(0, v168),
                                            _m_pfadd(
                                              _m_pfmul(v388, v166),
                                              _m_pfadd(_m_pfmul(v384, v167), _m_pfmul(v380, v165))));
        a1[7].m64_u64 = (uint64_t)_m_pfadd(
                                            _m_pfmul(v168, v392),
                                            _m_pfadd(
                                              _m_pfadd(_m_pfmul(v167, v386), _m_pfmul(v165, v382)),
                                              _m_pfmul(v166, v390)));
        v169 = _m_pfadd(_mm_cvtsi32_si64(a2[1].m64_u32[0]), _mm_cvtsi32_si64(a1[7].m64_u32[0]));
        a1[6].m64_u64 = (uint64_t)_m_pfadd((__m64)a2->m64_u64, a1[6]);
        a1[7].m64_i32[0] = _mm_cvtsi64_si32(v169);
      }
      else
      {
        result = a1;
        a1->m64_u64 = (uint64_t)_m_punpckldq(v380, v384);
        a1[2].m64_u64 = (uint64_t)_m_punpckhdq(v380, v384);
        v170 = _m_punpckldq(v390, v392);
        a1[5].m64_u64 = (uint64_t)v170;
        a1[7].m64_u64 = (uint64_t)_m_punpckhdq(v390, v392);
        a1[4].m64_u64 = (uint64_t)_m_punpckldq(v382, v386);
        v171 = _m_punpckldq(v388, 0);
        a1[6].m64_u64 = (uint64_t)_m_punpckhdq(v382, v386);
        a1[3].m64_u64 = (uint64_t)_m_punpckhdq(v388, 0);
        a1[1].m64_u64 = (uint64_t)v171;
        v172 = a1[1];
        v173 = _m_punpckhdq(v171, (__m64)a1->m64_u64);
        v174 = _m_punpckhdq(v170, v172);
        v175 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
        v176 = _m_punpckldq(v172, v172);
        v177 = _m_punpckhdq(v173, v173);
        v178 = _m_pfmul(v378, v177);
        v179 = _m_punpckhdq(v174, v174);
        v180 = _m_pfadd(_m_pfadd(_m_pfmul(v177, 0), _m_pfmul(v175, 0)), _m_pfmul(v176, v379));
        v181 = _m_pfadd(_m_pfmul(0, v179), _m_pfadd(_m_pfmul(0, v176), _m_pfadd(v178, _m_pfmul(v377, v175))));
        v182 = a1[2];
        v183 = _m_pfadd(_m_pfmul(v179, (__m64)0x3F80000000000000LL), v180);
        v184 = a1[3];
        a1->m64_u64 = (uint64_t)v181;
        a1[1].m64_u64 = (uint64_t)v183;
        v185 = _m_punpckhdq(v180, v182);
        v186 = _m_punpckhdq(v183, v184);
        v187 = _m_punpckldq(v182, v182);
        v188 = _m_punpckldq(v184, v184);
        v189 = _m_punpckhdq(v185, v185);
        v190 = _m_pfmul(v378, v189);
        v191 = _m_punpckhdq(v186, v186);
        v192 = _m_pfadd(_m_pfadd(_m_pfmul(v189, 0), _m_pfmul(v187, 0)), _m_pfmul(v188, v379));
        v193 = _m_pfadd(_m_pfmul(0, v191), _m_pfadd(_m_pfmul(0, v188), _m_pfadd(v190, _m_pfmul(v377, v187))));
        v194 = a1[4];
        v195 = _m_pfadd(_m_pfmul(v191, (__m64)0x3F80000000000000LL), v192);
        v196 = a1[5];
        a1[2].m64_u64 = (uint64_t)v193;
        a1[3].m64_u64 = (uint64_t)v195;
        v197 = _m_punpckhdq(v192, v194);
        v198 = _m_punpckhdq(v195, v196);
        v199 = _m_punpckldq(v194, v194);
        v200 = _m_punpckldq(v196, v196);
        v201 = _m_punpckhdq(v197, v197);
        v202 = _m_pfmul(v378, v201);
        v203 = _m_punpckhdq(v198, v198);
        v204 = _m_pfadd(_m_pfadd(_m_pfmul(v201, 0), _m_pfmul(v199, 0)), _m_pfmul(v200, v379));
        v205 = _m_pfadd(_m_pfmul(0, v203), _m_pfadd(_m_pfmul(0, v200), _m_pfadd(v202, _m_pfmul(v377, v199))));
        v206 = a1[6];
        v207 = _m_pfadd(_m_pfmul(v203, (__m64)0x3F80000000000000LL), v204);
        v208 = a1[7];
        a1[4].m64_u64 = (uint64_t)v205;
        a1[5].m64_u64 = (uint64_t)v207;
        v209 = _m_punpckhdq(v204, v206);
        v210 = _m_punpckhdq(v207, v208);
        v211 = _m_punpckldq(v206, v206);
        v212 = _m_punpckldq(v208, v208);
        v213 = _m_punpckhdq(v209, v209);
        v214 = _m_pfmul(v378, v213);
        v215 = _m_punpckhdq(v210, v210);
        v216 = _m_pfmul(0, v215);
        v217 = _m_pfadd(_m_pfadd(_m_pfmul(v213, 0), _m_pfmul(v211, 0)), _m_pfmul(v212, v379));
        v218 = _m_pfadd(_m_pfmul(v215, (__m64)0x3F80000000000000LL), v217);
        a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                            v216,
                                            _m_pfadd(_m_pfmul(0, v212), _m_pfadd(v214, _m_pfmul(v377, v211))));
        a1[7].m64_u64 = (uint64_t)v218;
        v219 = a1[1];
        v220 = _m_punpckhdq(v217, (__m64)a1->m64_u64);
        v221 = _m_punpckhdq(v218, v219);
        v222 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
        v223 = _m_punpckldq(v219, v219);
        v224 = _m_punpckhdq(v220, v220);
        v225 = _m_pfmul(v384, v224);
        v226 = _m_punpckhdq(v221, v221);
        v227 = _m_pfadd(_m_pfadd(_m_pfmul(v224, v386), _m_pfmul(v222, v382)), _m_pfmul(v223, v390));
        v228 = _m_pfadd(_m_pfmul(0, v226), _m_pfadd(_m_pfmul(v388, v223), _m_pfadd(v225, _m_pfmul(v380, v222))));
        v229 = a1[2];
        v230 = _m_pfadd(_m_pfmul(v226, v392), v227);
        v231 = a1[3];
        a1->m64_u64 = (uint64_t)v228;
        a1[1].m64_u64 = (uint64_t)v230;
        v232 = _m_punpckhdq(v227, v229);
        v233 = _m_punpckhdq(v230, v231);
        v234 = _m_punpckldq(v229, v229);
        v235 = _m_punpckldq(v231, v231);
        v236 = _m_punpckhdq(v232, v232);
        v237 = _m_pfmul(v384, v236);
        v238 = _m_punpckhdq(v233, v233);
        v239 = _m_pfadd(_m_pfadd(_m_pfmul(v236, v386), _m_pfmul(v234, v382)), _m_pfmul(v235, v390));
        v240 = _m_pfadd(_m_pfmul(0, v238), _m_pfadd(_m_pfmul(v388, v235), _m_pfadd(v237, _m_pfmul(v380, v234))));
        v241 = a1[4];
        v242 = _m_pfadd(_m_pfmul(v238, v392), v239);
        v243 = a1[5];
        a1[2].m64_u64 = (uint64_t)v240;
        a1[3].m64_u64 = (uint64_t)v242;
        v244 = _m_punpckhdq(v239, v241);
        v245 = _m_punpckhdq(v242, v243);
        v246 = _m_punpckldq(v241, v241);
        v247 = _m_punpckldq(v243, v243);
        v248 = _m_punpckhdq(v244, v244);
        v249 = _m_pfmul(v384, v248);
        v250 = _m_punpckhdq(v245, v245);
        v251 = _m_pfadd(_m_pfadd(_m_pfmul(v248, v386), _m_pfmul(v246, v382)), _m_pfmul(v247, v390));
        v252 = _m_pfadd(_m_pfmul(0, v250), _m_pfadd(_m_pfmul(v388, v247), _m_pfadd(v249, _m_pfmul(v380, v246))));
        v253 = a1[6];
        v254 = _m_pfadd(_m_pfmul(v250, v392), v251);
        v255 = a1[7];
        a1[4].m64_u64 = (uint64_t)v252;
        a1[5].m64_u64 = (uint64_t)v254;
        v256 = _m_punpckhdq(v251, v253);
        v257 = _m_punpckhdq(v254, v255);
        v258 = _m_punpckldq(v253, v253);
        v259 = _m_punpckldq(v255, v255);
        v260 = _m_punpckhdq(v256, v256);
        v261 = _m_punpckhdq(v257, v257);
        a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                            _m_pfmul(0, v261),
                                            _m_pfadd(
                                              _m_pfmul(v388, v259),
                                              _m_pfadd(_m_pfmul(v384, v260), _m_pfmul(v380, v258))));
        a1[7].m64_u64 = (uint64_t)_m_pfadd(
                                            _m_pfmul(v261, v392),
                                            _m_pfadd(
                                              _m_pfadd(_m_pfmul(v260, v386), _m_pfmul(v258, v382)),
                                              _m_pfmul(v259, v390)));
      }
    }
    else
    {
      v262 = _mm_cvtsi32_si64(a4[1].m64_u32[0]);
      v263 = _m_punpckhdq(0, (__m64)a4->m64_u64);
      a1->m64_u64 = (uint64_t)_m_punpckldq((__m64)a4->m64_u64, 0);
      a1[1].m64_u64 = 0;
      a1[2].m64_u64 = (uint64_t)v263;
      a1[3].m64_u64 = 0;
      a1[4].m64_u64 = 0;
      a1[5].m64_u64 = (uint64_t)v262;
      a1[6].m64_u64 = 0;
      a1[7].m64_u64 = 0x3F80000000000000LL;
    }
  }
  else
  {
    v264 = _mm_cvtsi32_si64(0x3F800000u);
    v265 = _m_punpckldq(_m_punpckhdq(v264, v264), v264);
    a1->m64_u64 = (uint64_t)v264;
    a1[1].m64_u64 = 0;
    a1[2].m64_u64 = (uint64_t)v265;
    a1[3].m64_u64 = 0;
    a1[4].m64_u64 = 0;
    a1[5].m64_u64 = (uint64_t)v264;
    a1[6].m64_u64 = 0;
    a1[7].m64_u64 = (uint64_t)v265;
  }
  if ( a6 != nullptr )
  {
    v266 = (__m64)a6->m64_u64;
    v267 = _m_pfadd(v266, v266);
    v268 = a6[1];
    v269 = _m_punpckhdq(v266, v266);
    v270 = _m_punpckhdq(v268, v268);
    v271 = _m_pfmul((__m64)a6->m64_u64, v267);
    v272 = _m_punpckldq(_m_pfadd(v268, v268), v267);
    v273 = _m_pfmul(v267, v270);
    v274 = _m_pfmul(_m_punpckldq(v268, v268), v272);
    v275 = _m_pfmul(v272, v270);
    v276 = _m_pfmul(v272, v269);
    v277 = _m_punpckhdq(v276, v274);
    v278 = _m_punpckhdq(_m_punpckldq(v275, v275), v273);
    v279 = _m_pfsubr(_m_pfadd(_m_punpckldq(v274, v274), v271), (__m64)0x3F8000003F800000LL);
    v391 = _m_punpckldq(_m_pfsubr(_m_pfacc(v271, v271), (__m64)0x3F8000003F800000LL), 0);
    v280 = v276;
    v281 = _m_pfadd(v276, v273);
    v282 = _m_pfsub(v280, v273);
    v283 = _m_pfsub(v277, v278);
    v284 = _m_punpckldq(v281, 0);
    v285 = _m_pfadd(v277, v278);
    v387 = v284;
    v383 = _m_punpckhdq(v283, 0);
    v385 = _m_punpckldq(v283, v279);
    v381 = _m_punpckhdq(v279, _m_punpckldq(v285, v285));
    v389 = _m_punpckldq(_m_punpckhdq(v285, v285), v282);
    v393 = _m_punpckldq(0, (__m64)1065353216LL);
    if ( a5 != nullptr )
    {
      v286 = (__m64)a5->m64_u64;
      v287 = _mm_cvtsi32_si64(a5[1].m64_u32[0]);
      v288 = _m_pfsub(_mm_cvtsi32_si64(result[7].m64_u32[0]), v287);
      result[6].m64_u64 = (uint64_t)_m_pfsub(result[6], (__m64)a5->m64_u64);
      result[7].m64_i32[0] = _mm_cvtsi64_si32(v288);
      v289 = result[1];
      v290 = _m_punpckhdq(v286, (__m64)result->m64_u64);
      v291 = _m_punpckhdq(v287, v289);
      v292 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
      v293 = _m_punpckldq(v289, v289);
      v294 = _m_punpckhdq(v290, v290);
      v295 = _m_pfmul(v385, v294);
      v296 = _m_punpckhdq(v291, v291);
      v297 = _m_pfadd(_m_pfadd(_m_pfmul(v294, v387), _m_pfmul(v292, v383)), _m_pfmul(v293, v391));
      v298 = _m_pfadd(_m_pfmul(0, v296), _m_pfadd(_m_pfmul(v389, v293), _m_pfadd(v295, _m_pfmul(v381, v292))));
      v299 = result[2];
      v300 = _m_pfadd(_m_pfmul(v296, v393), v297);
      v301 = result[3];
      result->m64_u64 = (uint64_t)v298;
      result[1].m64_u64 = (uint64_t)v300;
      v302 = _m_punpckhdq(v297, v299);
      v303 = _m_punpckhdq(v300, v301);
      v304 = _m_punpckldq(v299, v299);
      v305 = _m_punpckldq(v301, v301);
      v306 = _m_punpckhdq(v302, v302);
      v307 = _m_pfmul(v385, v306);
      v308 = _m_punpckhdq(v303, v303);
      v309 = _m_pfadd(_m_pfadd(_m_pfmul(v306, v387), _m_pfmul(v304, v383)), _m_pfmul(v305, v391));
      v310 = _m_pfadd(_m_pfmul(0, v308), _m_pfadd(_m_pfmul(v389, v305), _m_pfadd(v307, _m_pfmul(v381, v304))));
      v311 = result[4];
      v312 = _m_pfadd(_m_pfmul(v308, v393), v309);
      v313 = result[5];
      result[2].m64_u64 = (uint64_t)v310;
      result[3].m64_u64 = (uint64_t)v312;
      v314 = _m_punpckhdq(v309, v311);
      v315 = _m_punpckhdq(v312, v313);
      v316 = _m_punpckldq(v311, v311);
      v317 = _m_punpckldq(v313, v313);
      v318 = _m_punpckhdq(v314, v314);
      v319 = _m_pfmul(v385, v318);
      v320 = _m_punpckhdq(v315, v315);
      v321 = _m_pfadd(_m_pfadd(_m_pfmul(v318, v387), _m_pfmul(v316, v383)), _m_pfmul(v317, v391));
      v322 = _m_pfadd(_m_pfmul(0, v320), _m_pfadd(_m_pfmul(v389, v317), _m_pfadd(v319, _m_pfmul(v381, v316))));
      v323 = result[6];
      v324 = _m_pfadd(_m_pfmul(v320, v393), v321);
      v325 = result[7];
      result[4].m64_u64 = (uint64_t)v322;
      result[5].m64_u64 = (uint64_t)v324;
      v326 = _m_punpckhdq(v321, v323);
      v327 = _m_punpckhdq(v324, v325);
      v328 = _m_punpckldq(v323, v323);
      v329 = _m_punpckldq(v325, v325);
      v330 = _m_punpckhdq(v326, v326);
      v331 = _m_punpckhdq(v327, v327);
      result[6].m64_u64 = (uint64_t)_m_pfadd(
                                              _m_pfmul(0, v331),
                                              _m_pfadd(
                                                _m_pfmul(v389, v329),
                                                _m_pfadd(_m_pfmul(v385, v330), _m_pfmul(v381, v328))));
      result[7].m64_u64 = (uint64_t)_m_pfadd(
                                              _m_pfmul(v331, v393),
                                              _m_pfadd(
                                                _m_pfadd(_m_pfmul(v330, v387), _m_pfmul(v328, v383)),
                                                _m_pfmul(v329, v391)));
      v332 = _m_pfadd(_mm_cvtsi32_si64(result[7].m64_u32[0]), _mm_cvtsi32_si64(a5[1].m64_u32[0]));
      result[6].m64_u64 = (uint64_t)_m_pfadd(result[6], (__m64)a5->m64_u64);
      result[7].m64_i32[0] = _mm_cvtsi64_si32(v332);
    }
    else
    {
      v333 = result[1];
      v334 = _m_punpckhdq(v284, (__m64)result->m64_u64);
      v335 = _m_punpckhdq(v282, v333);
      v336 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
      v337 = _m_punpckldq(v333, v333);
      v338 = _m_punpckhdq(v334, v334);
      v339 = _m_pfmul(v385, v338);
      v340 = _m_punpckhdq(v335, v335);
      v341 = _m_pfadd(_m_pfadd(_m_pfmul(v338, v387), _m_pfmul(v336, v383)), _m_pfmul(v337, v391));
      v342 = _m_pfadd(_m_pfmul(0, v340), _m_pfadd(_m_pfmul(v389, v337), _m_pfadd(v339, _m_pfmul(v381, v336))));
      v343 = result[2];
      v344 = _m_pfadd(_m_pfmul(v340, v393), v341);
      v345 = result[3];
      result->m64_u64 = (uint64_t)v342;
      result[1].m64_u64 = (uint64_t)v344;
      v346 = _m_punpckhdq(v341, v343);
      v347 = _m_punpckhdq(v344, v345);
      v348 = _m_punpckldq(v343, v343);
      v349 = _m_punpckldq(v345, v345);
      v350 = _m_punpckhdq(v346, v346);
      v351 = _m_pfmul(v385, v350);
      v352 = _m_punpckhdq(v347, v347);
      v353 = _m_pfadd(_m_pfadd(_m_pfmul(v350, v387), _m_pfmul(v348, v383)), _m_pfmul(v349, v391));
      v354 = _m_pfadd(_m_pfmul(0, v352), _m_pfadd(_m_pfmul(v389, v349), _m_pfadd(v351, _m_pfmul(v381, v348))));
      v355 = result[4];
      v356 = _m_pfadd(_m_pfmul(v352, v393), v353);
      v357 = result[5];
      result[2].m64_u64 = (uint64_t)v354;
      result[3].m64_u64 = (uint64_t)v356;
      v358 = _m_punpckhdq(v353, v355);
      v359 = _m_punpckhdq(v356, v357);
      v360 = _m_punpckldq(v355, v355);
      v361 = _m_punpckldq(v357, v357);
      v362 = _m_punpckhdq(v358, v358);
      v363 = _m_pfmul(v385, v362);
      v364 = _m_punpckhdq(v359, v359);
      v365 = _m_pfadd(_m_pfadd(_m_pfmul(v362, v387), _m_pfmul(v360, v383)), _m_pfmul(v361, v391));
      v366 = _m_pfadd(_m_pfmul(0, v364), _m_pfadd(_m_pfmul(v389, v361), _m_pfadd(v363, _m_pfmul(v381, v360))));
      v367 = result[6];
      v368 = _m_pfadd(_m_pfmul(v364, v393), v365);
      v369 = result[7];
      result[4].m64_u64 = (uint64_t)v366;
      result[5].m64_u64 = (uint64_t)v368;
      v370 = _m_punpckhdq(v365, v367);
      v371 = _m_punpckhdq(v368, v369);
      v372 = _m_punpckldq(v367, v367);
      v373 = _m_punpckldq(v369, v369);
      v374 = _m_punpckhdq(v370, v370);
      v375 = _m_punpckhdq(v371, v371);
      result[6].m64_u64 = (uint64_t)_m_pfadd(
                                              _m_pfmul(0, v375),
                                              _m_pfadd(
                                                _m_pfmul(v389, v373),
                                                _m_pfadd(_m_pfmul(v385, v374), _m_pfmul(v381, v372))));
      result[7].m64_u64 = (uint64_t)_m_pfadd(
                                              _m_pfmul(v375, v393),
                                              _m_pfadd(
                                                _m_pfadd(_m_pfmul(v374, v387), _m_pfmul(v372, v383)),
                                                _m_pfmul(v373, v391)));
    }
  }
  if ( a7 != nullptr )
  {
    v376 = _m_pfadd(_mm_cvtsi32_si64(result[7].m64_u32[0]), _mm_cvtsi32_si64(a7[1].m64_u32[0]));
    result[6].m64_u64 = (uint64_t)_m_pfadd(result[6], (__m64)a7->m64_u64);
    result[7].m64_i32[0] = _mm_cvtsi64_si32(v376);
  }
  _m_femms();
  return result;
}


// ------------------------------------------------------------
// 0x68F72A sub_68F72A
// ------------------------------------------------------------
// 【L1】3DNow! 四元数→矩阵（fabs×3 半角规范化 + 0.5f，与 68E4DD 同族）
__m64 */*userpurge*/ sub_68F72A@<eax>(__m64 *a1, __m64 a2, __m64 a3)
{
  __m64 v3; // mm0
  __m64 v4; // mm6
  __m64 v5; // mm2
  __m64 v6; // mm6
  __m64 v7; // mm7
  __m64 v9; // mm3
  __m64 v10; // mm0
  __m64 v11; // mm7
  __m64 v12; // mm2
  __m64 v13; // mm4
  __m64 v14; // mm3
  __m64 v15; // mm1
  __m64 v16; // mm5
  __m64 v17; // mm7
  __m64 v18; // mm6
  __m64 v19; // mm2
  __m64 v20; // mm1
  __m64 v21; // mm6
  __m64 v22; // mm7
  __m64 v23; // mm3
  __m64 v24; // mm2
  __m64 v25; // mm3
  __m64 v26; // mm5
  __m64 v27; // mm6
  __m64 v28; // [esp+8h] [ebp-28h]
  __m64 v29; // [esp+28h] [ebp-8h]

  sub_6956A0();
  v28 = _m_pfmul((__m64)0x3F0000003F000000LL, a3);
  sub_6956A0();
  v3 = _m_pfmul((__m64)0x3F0000003F000000LL, a2);
  sub_6956A0();
  v4 = _m_punpckhdq(v3, v3);
  v5 = _m_punpckldq(v4, v4);
  v6 = _m_punpckhdq(v4, v4);
  v7 = _m_punpckldq(_m_punpckhdq(v28, v28), v28);
  v29 = _m_pfadd(
          _m_pfmul(_m_pfmul(_m_punpckldq(v3, v3), v5), v7),
          _m_pfmul(_m_pfmul(_m_pxor(_m_punpckhdq(v3, v3), _m_psrlqi((__m64)0x8000000000000000uLL, 0x20u)), v6), v28));
  v9 = _m_pfadd(
         _m_pfmul(_m_pfmul(_m_pxor(_m_punpckldq(v3, v3), (__m64)0x8000000000000000uLL), v6), v28),
         _m_pfmul(_m_pfmul(_m_punpckhdq(v3, v3), v5), v7));
  v10 = _m_pfadd(v9, v9);
  v11 = v29;
  v12 = _m_punpckhdq(v9, v9);
  v13 = _m_punpckhdq(v11, v11);
  v14 = _m_pfmul(v9, v10);
  v15 = _m_punpckldq(_m_pfadd(v11, v11), v10);
  v16 = _m_pfmul(v10, v13);
  v17 = _m_pfmul(_m_punpckldq(v11, v11), v15);
  v18 = _m_pfmul(v15, v13);
  v19 = _m_pfmul(v15, v12);
  v20 = _m_punpckhdq(v19, v17);
  a1[6].m64_u64 = 0;
  v21 = _m_punpckhdq(_m_punpckldq(v18, v18), v16);
  v22 = _m_pfsubr(_m_pfadd(_m_punpckldq(v17, v17), v14), (__m64)0x3F8000003F800000LL);
  a1[5].m64_u64 = (uint64_t)_m_punpckldq(_m_pfsubr(_m_pfacc(v14, v14), (__m64)0x3F8000003F800000LL), 0);
  v23 = v19;
  v24 = _m_pfadd(v19, v16);
  v25 = _m_pfsub(v23, v16);
  v26 = _m_pfsub(v20, v21);
  v27 = _m_pfadd(v20, v21);
  a1[3].m64_u64 = (uint64_t)_m_punpckldq(v24, 0);
  a1[1].m64_u64 = (uint64_t)_m_punpckhdq(v26, 0);
  a1[2].m64_u64 = (uint64_t)_m_punpckldq(v26, v22);
  a1->m64_u64 = (uint64_t)_m_punpckhdq(v22, _m_punpckldq(v27, v27));
  a1[4].m64_u64 = (uint64_t)_m_punpckldq(_m_punpckhdq(v27, v27), v25);
  a1[7].m64_u64 = (uint64_t)_m_punpckldq(0, (__m64)1065353216LL);
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68F8CF sub_68F8CF
// ------------------------------------------------------------
// 【L1】3DNow! 缩放+旋转+平移组合（对角 1.0f 基阵 → 四元数块 → 平移列，AffineTransformation 变体）
__m64 */*stdcall*/ sub_68F8CF(__m64 *a1, unsigned int a2, __m64 *a3, __m64 *a4, __m64 *a5)
{
  __m64 *result; // eax
  __m64 v6; // mm6
  __m64 m64_u64; // mm3
  __m64 v8; // mm0
  __m64 v9; // mm7
  __m64 v10; // mm2
  __m64 v11; // mm4
  __m64 v12; // mm3
  __m64 v13; // mm1
  __m64 v14; // mm5
  __m64 v15; // mm7
  __m64 v16; // mm6
  __m64 v17; // mm2
  __m64 v18; // mm1
  __m64 v19; // mm6
  __m64 v20; // mm7
  __m64 v21; // mm3
  __m64 v22; // mm2
  __m64 v23; // mm3
  __m64 v24; // mm5
  __m64 v25; // mm2
  __m64 v26; // mm6
  __m64 v27; // mm2
  __m64 v28; // mm3
  __m64 v29; // mm1
  __m64 v30; // mm1
  __m64 v31; // mm2
  __m64 v32; // mm3
  __m64 v33; // mm0
  __m64 v34; // mm1
  __m64 v35; // mm2
  __m64 v36; // mm5
  __m64 v37; // mm3
  __m64 v38; // mm2
  __m64 v39; // mm7
  __m64 v40; // mm0
  __m64 v41; // mm3
  __m64 v42; // mm1
  __m64 v43; // mm2
  __m64 v44; // mm3
  __m64 v45; // mm0
  __m64 v46; // mm1
  __m64 v47; // mm2
  __m64 v48; // mm5
  __m64 v49; // mm3
  __m64 v50; // mm2
  __m64 v51; // mm7
  __m64 v52; // mm0
  __m64 v53; // mm3
  __m64 v54; // mm1
  __m64 v55; // mm2
  __m64 v56; // mm3
  __m64 v57; // mm0
  __m64 v58; // mm1
  __m64 v59; // mm2
  __m64 v60; // mm5
  __m64 v61; // mm3
  __m64 v62; // mm2
  __m64 v63; // mm7
  __m64 v64; // mm0
  __m64 v65; // mm3
  __m64 v66; // mm1
  __m64 v67; // mm2
  __m64 v68; // mm3
  __m64 v69; // mm0
  __m64 v70; // mm1
  __m64 v71; // mm2
  __m64 v72; // mm3
  __m64 v73; // mm1
  __m64 v74; // mm1
  __m64 v75; // mm2
  __m64 v76; // mm3
  __m64 v77; // mm0
  __m64 v78; // mm1
  __m64 v79; // mm2
  __m64 v80; // mm5
  __m64 v81; // mm3
  __m64 v82; // mm2
  __m64 v83; // mm7
  __m64 v84; // mm0
  __m64 v85; // mm3
  __m64 v86; // mm1
  __m64 v87; // mm2
  __m64 v88; // mm3
  __m64 v89; // mm0
  __m64 v90; // mm1
  __m64 v91; // mm2
  __m64 v92; // mm5
  __m64 v93; // mm3
  __m64 v94; // mm2
  __m64 v95; // mm7
  __m64 v96; // mm0
  __m64 v97; // mm3
  __m64 v98; // mm1
  __m64 v99; // mm2
  __m64 v100; // mm3
  __m64 v101; // mm0
  __m64 v102; // mm1
  __m64 v103; // mm2
  __m64 v104; // mm5
  __m64 v105; // mm3
  __m64 v106; // mm2
  __m64 v107; // mm7
  __m64 v108; // mm0
  __m64 v109; // mm3
  __m64 v110; // mm1
  __m64 v111; // mm2
  __m64 v112; // mm3
  __m64 v113; // mm0
  __m64 v114; // mm1
  __m64 v115; // mm2
  __m64 v116; // mm3
  __m64 v117; // mm1
  __m64 v118; // [esp+0h] [ebp-40h]
  __m64 v119; // [esp+8h] [ebp-38h]
  __m64 v120; // [esp+10h] [ebp-30h]
  __m64 v121; // [esp+18h] [ebp-28h]
  __m64 v122; // [esp+20h] [ebp-20h]
  __m64 v123; // [esp+28h] [ebp-18h]
  __m64 v124; // [esp+38h] [ebp-8h]

  result = a1;
  v6 = _mm_cvtsi32_si64(a2);
  a1->m64_u64 = (uint64_t)v6;
  a1[1].m64_u64 = 0;
  a1[2].m64_i32[0] = _mm_cvtsi64_si32(0);
  a1[2].m64_i32[1] = _mm_cvtsi64_si32(v6);
  a1[3].m64_u64 = 0;
  a1[4].m64_u64 = 0;
  a1[5].m64_u64 = (uint64_t)v6;
  a1[6].m64_u64 = 0;
  a1[7].m64_u64 = 0x3F80000000000000LL;
  if ( a4 != nullptr )
  {
    m64_u64 = (__m64)a4->m64_u64;
    v8 = _m_pfadd(m64_u64, m64_u64);
    v9 = a4[1];
    v10 = _m_punpckhdq(m64_u64, m64_u64);
    v11 = _m_punpckhdq(v9, v9);
    v12 = _m_pfmul((__m64)a4->m64_u64, v8);
    v13 = _m_punpckldq(_m_pfadd(v9, v9), v8);
    v14 = _m_pfmul(v8, v11);
    v15 = _m_pfmul(_m_punpckldq(v9, v9), v13);
    v16 = _m_pfmul(v13, v11);
    v17 = _m_pfmul(v13, v10);
    v18 = _m_punpckhdq(v17, v15);
    v19 = _m_punpckhdq(_m_punpckldq(v16, v16), v14);
    v20 = _m_pfsubr(_m_pfadd(_m_punpckldq(v15, v15), v12), (__m64)0x3F8000003F800000LL);
    v123 = _m_punpckldq(_m_pfsubr(_m_pfacc(v12, v12), (__m64)0x3F8000003F800000LL), 0);
    v21 = v17;
    v22 = _m_pfadd(v17, v14);
    v23 = _m_pfsub(v21, v14);
    v24 = _m_pfsub(v18, v19);
    v25 = _m_punpckldq(v22, 0);
    v26 = _m_pfadd(v18, v19);
    v121 = v25;
    v119 = _m_punpckhdq(v24, 0);
    v120 = _m_punpckldq(v24, v20);
    v118 = _m_punpckhdq(v20, _m_punpckldq(v26, v26));
    v122 = _m_punpckldq(_m_punpckhdq(v26, v26), v23);
    v124 = _m_punpckldq(0, (__m64)1065353216LL);
    if ( a3 != nullptr )
    {
      v27 = (__m64)a3->m64_u64;
      v28 = _mm_cvtsi32_si64(a3[1].m64_u32[0]);
      v29 = _m_pfsub(_mm_cvtsi32_si64(a1[7].m64_u32[0]), v28);
      a1[6].m64_u64 = (uint64_t)_m_pfsub(a1[6], (__m64)a3->m64_u64);
      a1[7].m64_i32[0] = _mm_cvtsi64_si32(v29);
      v30 = a1[1];
      v31 = _m_punpckhdq(v27, (__m64)a1->m64_u64);
      v32 = _m_punpckhdq(v28, v30);
      v33 = _m_punpckldq((__m64)a1->m64_u64, (__m64)a1->m64_u64);
      v34 = _m_punpckldq(v30, v30);
      v35 = _m_punpckhdq(v31, v31);
      v36 = _m_pfmul(v120, v35);
      v37 = _m_punpckhdq(v32, v32);
      v38 = _m_pfadd(_m_pfadd(_m_pfmul(v35, v121), _m_pfmul(v33, v119)), _m_pfmul(v34, v123));
      v39 = _m_pfadd(_m_pfmul(0, v37), _m_pfadd(_m_pfmul(v122, v34), _m_pfadd(v36, _m_pfmul(v118, v33))));
      v40 = a1[2];
      v41 = _m_pfadd(_m_pfmul(v37, v124), v38);
      v42 = a1[3];
      a1->m64_u64 = (uint64_t)v39;
      a1[1].m64_u64 = (uint64_t)v41;
      v43 = _m_punpckhdq(v38, v40);
      v44 = _m_punpckhdq(v41, v42);
      v45 = _m_punpckldq(v40, v40);
      v46 = _m_punpckldq(v42, v42);
      v47 = _m_punpckhdq(v43, v43);
      v48 = _m_pfmul(v120, v47);
      v49 = _m_punpckhdq(v44, v44);
      v50 = _m_pfadd(_m_pfadd(_m_pfmul(v47, v121), _m_pfmul(v45, v119)), _m_pfmul(v46, v123));
      v51 = _m_pfadd(_m_pfmul(0, v49), _m_pfadd(_m_pfmul(v122, v46), _m_pfadd(v48, _m_pfmul(v118, v45))));
      v52 = a1[4];
      v53 = _m_pfadd(_m_pfmul(v49, v124), v50);
      v54 = a1[5];
      a1[2].m64_u64 = (uint64_t)v51;
      a1[3].m64_u64 = (uint64_t)v53;
      v55 = _m_punpckhdq(v50, v52);
      v56 = _m_punpckhdq(v53, v54);
      v57 = _m_punpckldq(v52, v52);
      v58 = _m_punpckldq(v54, v54);
      v59 = _m_punpckhdq(v55, v55);
      v60 = _m_pfmul(v120, v59);
      v61 = _m_punpckhdq(v56, v56);
      v62 = _m_pfadd(_m_pfadd(_m_pfmul(v59, v121), _m_pfmul(v57, v119)), _m_pfmul(v58, v123));
      v63 = _m_pfadd(_m_pfmul(0, v61), _m_pfadd(_m_pfmul(v122, v58), _m_pfadd(v60, _m_pfmul(v118, v57))));
      v64 = a1[6];
      v65 = _m_pfadd(_m_pfmul(v61, v124), v62);
      v66 = a1[7];
      a1[4].m64_u64 = (uint64_t)v63;
      a1[5].m64_u64 = (uint64_t)v65;
      v67 = _m_punpckhdq(v62, v64);
      v68 = _m_punpckhdq(v65, v66);
      v69 = _m_punpckldq(v64, v64);
      v70 = _m_punpckldq(v66, v66);
      v71 = _m_punpckhdq(v67, v67);
      v72 = _m_punpckhdq(v68, v68);
      a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                          _m_pfmul(0, v72),
                                          _m_pfadd(
                                            _m_pfmul(v122, v70),
                                            _m_pfadd(_m_pfmul(v120, v71), _m_pfmul(v118, v69))));
      a1[7].m64_u64 = (uint64_t)_m_pfadd(
                                          _m_pfmul(v72, v124),
                                          _m_pfadd(
                                            _m_pfadd(_m_pfmul(v71, v121), _m_pfmul(v69, v119)),
                                            _m_pfmul(v70, v123)));
      v73 = _m_pfadd(_mm_cvtsi32_si64(a1[7].m64_u32[0]), _mm_cvtsi32_si64(a3[1].m64_u32[0]));
      a1[6].m64_u64 = (uint64_t)_m_pfadd(a1[6], (__m64)a3->m64_u64);
      a1[7].m64_i32[0] = _mm_cvtsi64_si32(v73);
    }
    else
    {
      v74 = a1[1];
      v75 = _m_punpckhdq(v25, (__m64)a1->m64_u64);
      v76 = _m_punpckhdq(v23, v74);
      v77 = _m_punpckldq((__m64)a1->m64_u64, (__m64)a1->m64_u64);
      v78 = _m_punpckldq(v74, v74);
      v79 = _m_punpckhdq(v75, v75);
      v80 = _m_pfmul(v120, v79);
      v81 = _m_punpckhdq(v76, v76);
      v82 = _m_pfadd(_m_pfadd(_m_pfmul(v79, v121), _m_pfmul(v77, v119)), _m_pfmul(v78, v123));
      v83 = _m_pfadd(_m_pfmul(0, v81), _m_pfadd(_m_pfmul(v122, v78), _m_pfadd(v80, _m_pfmul(v118, v77))));
      v84 = a1[2];
      v85 = _m_pfadd(_m_pfmul(v81, v124), v82);
      v86 = a1[3];
      a1->m64_u64 = (uint64_t)v83;
      a1[1].m64_u64 = (uint64_t)v85;
      v87 = _m_punpckhdq(v82, v84);
      v88 = _m_punpckhdq(v85, v86);
      v89 = _m_punpckldq(v84, v84);
      v90 = _m_punpckldq(v86, v86);
      v91 = _m_punpckhdq(v87, v87);
      v92 = _m_pfmul(v120, v91);
      v93 = _m_punpckhdq(v88, v88);
      v94 = _m_pfadd(_m_pfadd(_m_pfmul(v91, v121), _m_pfmul(v89, v119)), _m_pfmul(v90, v123));
      v95 = _m_pfadd(_m_pfmul(0, v93), _m_pfadd(_m_pfmul(v122, v90), _m_pfadd(v92, _m_pfmul(v118, v89))));
      v96 = a1[4];
      v97 = _m_pfadd(_m_pfmul(v93, v124), v94);
      v98 = a1[5];
      a1[2].m64_u64 = (uint64_t)v95;
      a1[3].m64_u64 = (uint64_t)v97;
      v99 = _m_punpckhdq(v94, v96);
      v100 = _m_punpckhdq(v97, v98);
      v101 = _m_punpckldq(v96, v96);
      v102 = _m_punpckldq(v98, v98);
      v103 = _m_punpckhdq(v99, v99);
      v104 = _m_pfmul(v120, v103);
      v105 = _m_punpckhdq(v100, v100);
      v106 = _m_pfadd(_m_pfadd(_m_pfmul(v103, v121), _m_pfmul(v101, v119)), _m_pfmul(v102, v123));
      v107 = _m_pfadd(_m_pfmul(0, v105), _m_pfadd(_m_pfmul(v122, v102), _m_pfadd(v104, _m_pfmul(v118, v101))));
      v108 = a1[6];
      v109 = _m_pfadd(_m_pfmul(v105, v124), v106);
      v110 = a1[7];
      a1[4].m64_u64 = (uint64_t)v107;
      a1[5].m64_u64 = (uint64_t)v109;
      v111 = _m_punpckhdq(v106, v108);
      v112 = _m_punpckhdq(v109, v110);
      v113 = _m_punpckldq(v108, v108);
      v114 = _m_punpckldq(v110, v110);
      v115 = _m_punpckhdq(v111, v111);
      v116 = _m_punpckhdq(v112, v112);
      a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                          _m_pfmul(0, v116),
                                          _m_pfadd(
                                            _m_pfmul(v122, v114),
                                            _m_pfadd(_m_pfmul(v120, v115), _m_pfmul(v118, v113))));
      a1[7].m64_u64 = (uint64_t)_m_pfadd(
                                          _m_pfmul(v116, v124),
                                          _m_pfadd(
                                            _m_pfadd(_m_pfmul(v115, v121), _m_pfmul(v113, v119)),
                                            _m_pfmul(v114, v123)));
    }
  }
  if ( a5 != nullptr )
  {
    v117 = _m_pfadd(_mm_cvtsi32_si64(a5[1].m64_u32[0]), _mm_cvtsi32_si64(a1[7].m64_u32[0]));
    a1[6].m64_u64 = (uint64_t)_m_pfadd((__m64)a5->m64_u64, a1[6]);
    a1[7].m64_i32[0] = _mm_cvtsi64_si32(v117);
  }
  _m_femms();
  return result;
}


// ------------------------------------------------------------
// 0x68FE03 sub_68FE03
// ------------------------------------------------------------
// 【L1】3DNow! 组合变换（310 行，矩阵初始化 1.0f + 复合）【推断】
__m64 */*stdcall*/ sub_68FE03(__m64 *a1, __m64 *a2, unsigned int a3)
{
  __m64 v3; // mm1
  __m64 v4; // mm1
  __m64 v5; // mm0
  __m64 v6; // mm7
  __m64 v7; // mm3
  __m64 v8; // mm0
  __m64 v9; // mm1
  __m64 v10; // mm2
  __m64 v12; // mm3
  __m64 v13; // mm4
  __m64 v14; // mm5
  __m64 v15; // mm1
  __m64 v16; // mm1
  __m64 v17; // mm6
  __m64 v18; // mm7
  __m64 v19; // mm1
  __m64 v20; // mm6
  __m64 v21; // mm2
  __m64 v22; // mm1
  uint64_t m64_u64; // [esp+0h] [ebp-18h] BYREF
  unsigned int v24; // [esp+8h] [ebp-10h]
  unsigned int v25; // [esp+Ch] [ebp-Ch]

  v3 = _mm_cvtsi32_si64(a2[1].m64_u32[0]);
  m64_u64 = a2->m64_u64;
  v24 = _mm_cvtsi64_si32(v3);
  sub_691B72(&m64_u64, &m64_u64);
  sub_6956A0();
  v4 = _mm_cvtsi32_si64(a3);
  v5 = _m_pfsubr(v4, (__m64)0x3F8000003F800000LL);
  v25 = _mm_cvtsi64_si32(_m_punpckhdq(v4, v4));
  v6 = _mm_cvtsi32_si64(v24);
  v7 = _m_punpckldq(v6, v6);
  v8 = _m_punpckldq(v5, v5);
  v9 = _m_punpckldq(v4, v4);
  v10 = _m_pfmul(_m_pfmul(_m_punpckhdq((__m64)m64_u64, v7), (__m64)m64_u64), v8);
  v12 = _m_pfmul(_m_pfmul(v7, (__m64)m64_u64), v8);
  v13 = _m_pfadd(_m_pfmul(_m_pfmul((__m64)m64_u64, (__m64)m64_u64), v8), v9);
  v14 = _m_pfadd(_m_pfmul(_m_pfmul(v6, v6), v8), v9);
  v15 = _mm_cvtsi32_si64(v25);
  v16 = _m_punpckldq(v15, v15);
  v17 = _m_pfmul((__m64)m64_u64, v16);
  a1[6].m64_u64 = 0;
  v18 = _m_punpckldq(_m_pfmul(v6, v16), v17);
  v19 = v10;
  v20 = _m_punpckhdq(v17, v17);
  a1[5].m64_u64 = (uint64_t)_m_punpckldq(v14, 0);
  v21 = _m_pfsub(v10, v18);
  v22 = _m_pfadd(v19, v18);
  a1->m64_u64 = (uint64_t)_m_punpckldq(v13, v22);
  a1[1].m64_u64 = (uint64_t)_m_punpckldq(_m_pfsub(v12, v20), 0);
  a1[3].m64_u64 = (uint64_t)_m_punpckhdq(v22, 0);
  a1[7].m64_u64 = (uint64_t)_m_punpckhdq(0, (__m64)0x3F8000003F800000LL);
  a1[4].m64_u64 = (uint64_t)_m_punpckhdq(_m_pfadd(_m_punpckldq(v12, v12), v20), v21);
  a1[2].m64_u64 = (uint64_t)_m_punpckldq(v21, _m_punpckhdq(v13, v13));
  _m_femms();
  return a1;
}



// ------------------------------------------------------------
// 0x68FF1C sub_68FF1C
// ------------------------------------------------------------
// 【L1】★ 3DNow! 仿射组合巨型（946 行，7 参，与 68E592 成对的另一展开布局）【推断】
__m64 */*stdcall*/ sub_68FF1C(__m64 *a1, __m64 *a2, __m64 *a3, __m64 *a4, __m64 *a5, __m64 *a6, __m64 *a7)
{
  __m64 *result; // eax
  __m64 v8; // mm4
  __m64 v9; // mm1
  __m64 v10; // mm5
  __m64 v11; // mm0
  __m64 v12; // mm5
  __m64 v13; // mm2
  __m64 v14; // mm3
  __m64 v15; // mm1
  __m64 v16; // mm6
  __m64 v17; // mm3
  __m64 v18; // mm6
  __m64 v19; // mm2
  __m64 v20; // mm1
  __m64 m64_u64; // mm3
  __m64 v22; // mm4
  __m64 v23; // mm1
  __m64 v24; // mm2
  __m64 v25; // mm2
  __m64 v26; // mm1
  __m64 v27; // mm2
  __m64 v28; // mm3
  __m64 v29; // mm0
  __m64 v30; // mm1
  __m64 v31; // mm2
  __m64 v32; // mm5
  __m64 v33; // mm3
  __m64 v34; // mm2
  __m64 v35; // mm7
  __m64 v36; // mm0
  __m64 v37; // mm3
  __m64 v38; // mm1
  __m64 v39; // mm2
  __m64 v40; // mm3
  __m64 v41; // mm0
  __m64 v42; // mm1
  __m64 v43; // mm2
  __m64 v44; // mm5
  __m64 v45; // mm3
  __m64 v46; // mm2
  __m64 v47; // mm7
  __m64 v48; // mm0
  __m64 v49; // mm3
  __m64 v50; // mm1
  __m64 v51; // mm2
  __m64 v52; // mm3
  __m64 v53; // mm0
  __m64 v54; // mm1
  __m64 v55; // mm2
  __m64 v56; // mm5
  __m64 v57; // mm3
  __m64 v58; // mm2
  __m64 v59; // mm7
  __m64 v60; // mm0
  __m64 v61; // mm3
  __m64 v62; // mm1
  __m64 v63; // mm2
  __m64 v64; // mm3
  __m64 v65; // mm0
  __m64 v66; // mm1
  __m64 v67; // mm2
  __m64 v68; // mm5
  __m64 v69; // mm3
  __m64 v70; // mm7
  __m64 v71; // mm2
  __m64 v72; // mm3
  __m64 v73; // mm1
  __m64 v74; // mm2
  __m64 v75; // mm3
  __m64 v76; // mm0
  __m64 v77; // mm1
  __m64 v78; // mm2
  __m64 v79; // mm5
  __m64 v80; // mm3
  __m64 v81; // mm2
  __m64 v82; // mm7
  __m64 v83; // mm0
  __m64 v84; // mm3
  __m64 v85; // mm1
  __m64 v86; // mm2
  __m64 v87; // mm3
  __m64 v88; // mm0
  __m64 v89; // mm1
  __m64 v90; // mm2
  __m64 v91; // mm5
  __m64 v92; // mm3
  __m64 v93; // mm2
  __m64 v94; // mm7
  __m64 v95; // mm0
  __m64 v96; // mm3
  __m64 v97; // mm1
  __m64 v98; // mm2
  __m64 v99; // mm3
  __m64 v100; // mm0
  __m64 v101; // mm1
  __m64 v102; // mm2
  __m64 v103; // mm5
  __m64 v104; // mm3
  __m64 v105; // mm2
  __m64 v106; // mm7
  __m64 v107; // mm0
  __m64 v108; // mm3
  __m64 v109; // mm1
  __m64 v110; // mm2
  __m64 v111; // mm3
  __m64 v112; // mm0
  __m64 v113; // mm1
  __m64 v114; // mm2
  __m64 v115; // mm5
  __m64 v116; // mm3
  __m64 v117; // mm7
  __m64 v118; // mm2
  __m64 v119; // mm3
  __m64 v120; // mm1
  __m64 v121; // mm2
  __m64 v122; // mm3
  __m64 v123; // mm0
  __m64 v124; // mm1
  __m64 v125; // mm2
  __m64 v126; // mm5
  __m64 v127; // mm3
  __m64 v128; // mm2
  __m64 v129; // mm7
  __m64 v130; // mm0
  __m64 v131; // mm3
  __m64 v132; // mm1
  __m64 v133; // mm2
  __m64 v134; // mm3
  __m64 v135; // mm0
  __m64 v136; // mm1
  __m64 v137; // mm2
  __m64 v138; // mm5
  __m64 v139; // mm3
  __m64 v140; // mm2
  __m64 v141; // mm7
  __m64 v142; // mm0
  __m64 v143; // mm3
  __m64 v144; // mm1
  __m64 v145; // mm2
  __m64 v146; // mm3
  __m64 v147; // mm0
  __m64 v148; // mm1
  __m64 v149; // mm2
  __m64 v150; // mm5
  __m64 v151; // mm3
  __m64 v152; // mm2
  __m64 v153; // mm7
  __m64 v154; // mm0
  __m64 v155; // mm3
  __m64 v156; // mm1
  __m64 v157; // mm2
  __m64 v158; // mm3
  __m64 v159; // mm0
  __m64 v160; // mm1
  __m64 v161; // mm2
  __m64 v162; // mm3
  __m64 v163; // mm2
  __m64 v164; // mm3
  __m64 v165; // mm2
  __m64 v166; // mm1
  __m64 v167; // mm2
  __m64 v168; // mm3
  __m64 v169; // mm0
  __m64 v170; // mm1
  __m64 v171; // mm2
  __m64 v172; // mm5
  __m64 v173; // mm3
  __m64 v174; // mm2
  __m64 v175; // mm7
  __m64 v176; // mm0
  __m64 v177; // mm3
  __m64 v178; // mm1
  __m64 v179; // mm2
  __m64 v180; // mm3
  __m64 v181; // mm0
  __m64 v182; // mm1
  __m64 v183; // mm2
  __m64 v184; // mm5
  __m64 v185; // mm3
  __m64 v186; // mm2
  __m64 v187; // mm7
  __m64 v188; // mm0
  __m64 v189; // mm3
  __m64 v190; // mm1
  __m64 v191; // mm2
  __m64 v192; // mm3
  __m64 v193; // mm0
  __m64 v194; // mm1
  __m64 v195; // mm2
  __m64 v196; // mm5
  __m64 v197; // mm3
  __m64 v198; // mm2
  __m64 v199; // mm7
  __m64 v200; // mm0
  __m64 v201; // mm3
  __m64 v202; // mm1
  __m64 v203; // mm2
  __m64 v204; // mm3
  __m64 v205; // mm0
  __m64 v206; // mm1
  __m64 v207; // mm2
  __m64 v208; // mm5
  __m64 v209; // mm3
  __m64 v210; // mm7
  __m64 v211; // mm2
  __m64 v212; // mm3
  __m64 v213; // mm1
  __m64 v214; // mm2
  __m64 v215; // mm3
  __m64 v216; // mm0
  __m64 v217; // mm1
  __m64 v218; // mm2
  __m64 v219; // mm5
  __m64 v220; // mm3
  __m64 v221; // mm2
  __m64 v222; // mm7
  __m64 v223; // mm0
  __m64 v224; // mm3
  __m64 v225; // mm1
  __m64 v226; // mm2
  __m64 v227; // mm3
  __m64 v228; // mm0
  __m64 v229; // mm1
  __m64 v230; // mm2
  __m64 v231; // mm5
  __m64 v232; // mm3
  __m64 v233; // mm2
  __m64 v234; // mm7
  __m64 v235; // mm0
  __m64 v236; // mm3
  __m64 v237; // mm1
  __m64 v238; // mm2
  __m64 v239; // mm3
  __m64 v240; // mm0
  __m64 v241; // mm1
  __m64 v242; // mm2
  __m64 v243; // mm5
  __m64 v244; // mm3
  __m64 v245; // mm2
  __m64 v246; // mm7
  __m64 v247; // mm0
  __m64 v248; // mm3
  __m64 v249; // mm1
  __m64 v250; // mm2
  __m64 v251; // mm3
  __m64 v252; // mm0
  __m64 v253; // mm1
  __m64 v254; // mm2
  __m64 v255; // mm3
  __m64 v256; // mm4
  __m64 v257; // mm5
  __m64 v258; // mm1
  __m64 v259; // mm2
  __m64 v260; // mm4
  __m64 v261; // mm1
  __m64 v262; // mm5
  __m64 v263; // mm0
  __m64 v264; // mm5
  __m64 v265; // mm2
  __m64 v266; // mm3
  __m64 v267; // mm1
  __m64 v268; // mm6
  __m64 v269; // mm3
  __m64 v270; // mm6
  __m64 v271; // mm2
  __m64 v272; // mm1
  __m64 v273; // mm5
  __m64 v274; // mm2
  __m64 v275; // mm3
  __m64 v276; // mm2
  __m64 v277; // mm3
  __m64 v278; // mm1
  __m64 v279; // mm1
  __m64 v280; // mm2
  __m64 v281; // mm3
  __m64 v282; // mm0
  __m64 v283; // mm1
  __m64 v284; // mm2
  __m64 v285; // mm5
  __m64 v286; // mm3
  __m64 v287; // mm2
  __m64 v288; // mm7
  __m64 v289; // mm0
  __m64 v290; // mm3
  __m64 v291; // mm1
  __m64 v292; // mm2
  __m64 v293; // mm3
  __m64 v294; // mm0
  __m64 v295; // mm1
  __m64 v296; // mm2
  __m64 v297; // mm5
  __m64 v298; // mm3
  __m64 v299; // mm2
  __m64 v300; // mm7
  __m64 v301; // mm0
  __m64 v302; // mm3
  __m64 v303; // mm1
  __m64 v304; // mm2
  __m64 v305; // mm3
  __m64 v306; // mm0
  __m64 v307; // mm1
  __m64 v308; // mm2
  __m64 v309; // mm5
  __m64 v310; // mm3
  __m64 v311; // mm2
  __m64 v312; // mm7
  __m64 v313; // mm0
  __m64 v314; // mm3
  __m64 v315; // mm1
  __m64 v316; // mm2
  __m64 v317; // mm3
  __m64 v318; // mm0
  __m64 v319; // mm1
  __m64 v320; // mm2
  __m64 v321; // mm3
  __m64 v322; // mm1
  __m64 v323; // mm1
  __m64 v324; // mm2
  __m64 v325; // mm3
  __m64 v326; // mm0
  __m64 v327; // mm1
  __m64 v328; // mm2
  __m64 v329; // mm5
  __m64 v330; // mm3
  __m64 v331; // mm2
  __m64 v332; // mm7
  __m64 v333; // mm0
  __m64 v334; // mm3
  __m64 v335; // mm1
  __m64 v336; // mm2
  __m64 v337; // mm3
  __m64 v338; // mm0
  __m64 v339; // mm1
  __m64 v340; // mm2
  __m64 v341; // mm5
  __m64 v342; // mm3
  __m64 v343; // mm2
  __m64 v344; // mm7
  __m64 v345; // mm0
  __m64 v346; // mm3
  __m64 v347; // mm1
  __m64 v348; // mm2
  __m64 v349; // mm3
  __m64 v350; // mm0
  __m64 v351; // mm1
  __m64 v352; // mm2
  __m64 v353; // mm5
  __m64 v354; // mm3
  __m64 v355; // mm2
  __m64 v356; // mm7
  __m64 v357; // mm0
  __m64 v358; // mm3
  __m64 v359; // mm1
  __m64 v360; // mm2
  __m64 v361; // mm3
  __m64 v362; // mm0
  __m64 v363; // mm1
  __m64 v364; // mm2
  __m64 v365; // mm3
  __m64 v366; // mm1
  __m64 v367; // [esp+0h] [ebp-C0h]
  __m64 v368; // [esp+10h] [ebp-B0h]
  __m64 v369; // [esp+28h] [ebp-98h]
  __m64 v370; // [esp+40h] [ebp-80h]
  __m64 v371; // [esp+40h] [ebp-80h]
  __m64 v372; // [esp+48h] [ebp-78h]
  __m64 v373; // [esp+48h] [ebp-78h]
  __m64 v374; // [esp+50h] [ebp-70h]
  __m64 v375; // [esp+50h] [ebp-70h]
  __m64 v376; // [esp+58h] [ebp-68h]
  __m64 v377; // [esp+58h] [ebp-68h]
  __m64 v378; // [esp+60h] [ebp-60h]
  __m64 v379; // [esp+60h] [ebp-60h]
  __m64 v380; // [esp+68h] [ebp-58h]
  __m64 v381; // [esp+68h] [ebp-58h]
  __m64 v382; // [esp+78h] [ebp-48h]
  __m64 v383; // [esp+78h] [ebp-48h]
  __m64 v384; // [esp+80h] [ebp-40h]
  __m64 v385; // [esp+88h] [ebp-38h]
  __m64 v386; // [esp+90h] [ebp-30h]
  __m64 v387; // [esp+98h] [ebp-28h]
  __m64 v388; // [esp+A0h] [ebp-20h]
  __m64 v389; // [esp+A8h] [ebp-18h]
  __m64 v390; // [esp+B0h] [ebp-10h]
  __m64 v391; // [esp+B8h] [ebp-8h]

  result = a1;
  if ( a4 != nullptr )
  {
    if ( a3 != nullptr )
    {
      v367 = _m_punpckldq((__m64)a4->m64_u64, 0);
      v368 = _m_punpckhdq(0, (__m64)a4->m64_u64);
      v369 = _mm_cvtsi32_si64(a4[1].m64_u32[0]);
      v8 = a3[1];
      v9 = _m_pfadd(v8, v8);
      v10 = _m_pfadd((__m64)a3->m64_u64, (__m64)a3->m64_u64);
      v11 = _m_pfmul(v10, (__m64)a3->m64_u64);
      v12 = _m_punpckldq(v10, v9);
      v13 = _m_pfmul((__m64)a3->m64_u64, v9);
      v14 = _m_pfmul(_m_pswapd((__m64)a3->m64_u64), v9);
      v15 = _m_pfmul(v9, v8);
      v16 = _m_pfmul(_m_punpckhdq((__m64)a3->m64_u64, v8), v12);
      v17 = _m_pfpnacc(v14, v14);
      v18 = _m_pfpnacc(v16, v16);
      v19 = _m_pfpnacc(v13, v13);
      v20 = _m_pfsub(_m_pfsubr(v11, (__m64)0x3F8000003F800000LL), _m_punpckldq(v15, v15));
      v378 = _m_punpckldq(_m_pswapd(v19), v17);
      v372 = _m_punpckldq(v19, 0);
      v380 = _m_punpckhdq(_m_pfsubr(_m_pfacc(v11, v11), (__m64)0x3F8000003F800000LL), 0);
      v370 = _m_punpckhdq(v20, v18);
      v374 = _m_punpckldq(v18, v20);
      v376 = _m_punpckhdq(v17, 0);
      v382 = _m_punpckldq(0, (__m64)1065353216LL);
      if ( a2 != nullptr )
      {
        v384 = _m_punpckldq(v370, v374);
        v386 = _m_punpckhdq(v370, v374);
        v389 = _m_punpckldq(v380, v382);
        v391 = _m_punpckhdq(v380, v382);
        v388 = _m_punpckldq(v372, v376);
        v390 = _m_punpckhdq(v372, v376);
        v387 = _m_punpckhdq(v378, 0);
        v385 = _m_punpckldq(v378, 0);
        result = a1;
        m64_u64 = (__m64)a2->m64_u64;
        v22 = _mm_cvtsi32_si64(a2[1].m64_u32[0]);
        v23 = _mm_cvtsi32_si64(0x3F800000u);
        v24 = _m_pswapd(v23);
        a1->m64_u64 = (uint64_t)v23;
        a1[1].m64_u64 = 0;
        a1[2].m64_u64 = (uint64_t)v24;
        a1[3].m64_u64 = 0;
        a1[4].m64_u64 = 0;
        a1[5].m64_u64 = (uint64_t)v23;
        v25 = _m_pfsub(v24, v22);
        a1[7].m64_u64 = (uint64_t)v25;
        a1[6].m64_u64 = (uint64_t)_m_pfsub(0, m64_u64);
        v26 = a1[1];
        v27 = _m_punpckhdq(v25, (__m64)a1->m64_u64);
        v28 = _m_punpckhdq(m64_u64, v26);
        v29 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
        v30 = _m_punpckldq(v26, v26);
        v31 = _m_punpckhdq(v27, v27);
        v32 = _m_pfmul(v386, v31);
        v33 = _m_punpckhdq(v28, v28);
        v34 = _m_pfadd(_m_pfadd(_m_pfmul(v31, v387), _m_pfmul(v29, v385)), _m_pfmul(v30, v389));
        v35 = _m_pfadd(_m_pfmul(v390, v33), _m_pfadd(_m_pfmul(v388, v30), _m_pfadd(v32, _m_pfmul(v384, v29))));
        v36 = a1[2];
        v37 = _m_pfadd(_m_pfmul(v33, v391), v34);
        v38 = a1[3];
        a1->m64_u64 = (uint64_t)v35;
        a1[1].m64_u64 = (uint64_t)v37;
        v39 = _m_punpckhdq(v34, v36);
        v40 = _m_punpckhdq(v37, v38);
        v41 = _m_punpckldq(v36, v36);
        v42 = _m_punpckldq(v38, v38);
        v43 = _m_punpckhdq(v39, v39);
        v44 = _m_pfmul(v386, v43);
        v45 = _m_punpckhdq(v40, v40);
        v46 = _m_pfadd(_m_pfadd(_m_pfmul(v43, v387), _m_pfmul(v41, v385)), _m_pfmul(v42, v389));
        v47 = _m_pfadd(_m_pfmul(v390, v45), _m_pfadd(_m_pfmul(v388, v42), _m_pfadd(v44, _m_pfmul(v384, v41))));
        v48 = a1[4];
        v49 = _m_pfadd(_m_pfmul(v45, v391), v46);
        v50 = a1[5];
        a1[2].m64_u64 = (uint64_t)v47;
        a1[3].m64_u64 = (uint64_t)v49;
        v51 = _m_punpckhdq(v46, v48);
        v52 = _m_punpckhdq(v49, v50);
        v53 = _m_punpckldq(v48, v48);
        v54 = _m_punpckldq(v50, v50);
        v55 = _m_punpckhdq(v51, v51);
        v56 = _m_pfmul(v386, v55);
        v57 = _m_punpckhdq(v52, v52);
        v58 = _m_pfadd(_m_pfadd(_m_pfmul(v55, v387), _m_pfmul(v53, v385)), _m_pfmul(v54, v389));
        v59 = _m_pfadd(_m_pfmul(v390, v57), _m_pfadd(_m_pfmul(v388, v54), _m_pfadd(v56, _m_pfmul(v384, v53))));
        v60 = a1[6];
        v61 = _m_pfadd(_m_pfmul(v57, v391), v58);
        v62 = a1[7];
        a1[4].m64_u64 = (uint64_t)v59;
        a1[5].m64_u64 = (uint64_t)v61;
        v63 = _m_punpckhdq(v58, v60);
        v64 = _m_punpckhdq(v61, v62);
        v65 = _m_punpckldq(v60, v60);
        v66 = _m_punpckldq(v62, v62);
        v67 = _m_punpckhdq(v63, v63);
        v68 = _m_pfmul(v386, v67);
        v69 = _m_punpckhdq(v64, v64);
        v70 = _m_pfmul(v390, v69);
        v71 = _m_pfadd(_m_pfadd(_m_pfmul(v67, v387), _m_pfmul(v65, v385)), _m_pfmul(v66, v389));
        v72 = _m_pfadd(_m_pfmul(v69, v391), v71);
        a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                            v70,
                                            _m_pfadd(_m_pfmul(v388, v66), _m_pfadd(v68, _m_pfmul(v384, v65))));
        a1[7].m64_u64 = (uint64_t)v72;
        v73 = a1[1];
        v74 = _m_punpckhdq(v71, (__m64)a1->m64_u64);
        v75 = _m_punpckhdq(v72, v73);
        v76 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
        v77 = _m_punpckldq(v73, v73);
        v78 = _m_punpckhdq(v74, v74);
        v79 = _m_pfmul(v368, v78);
        v80 = _m_punpckhdq(v75, v75);
        v81 = _m_pfadd(_m_pfadd(_m_pfmul(v78, 0), _m_pfmul(v76, 0)), _m_pfmul(v77, v369));
        v82 = _m_pfadd(_m_pfmul(0, v80), _m_pfadd(_m_pfmul(0, v77), _m_pfadd(v79, _m_pfmul(v367, v76))));
        v83 = a1[2];
        v84 = _m_pfadd(_m_pfmul(v80, (__m64)0x3F80000000000000LL), v81);
        v85 = a1[3];
        a1->m64_u64 = (uint64_t)v82;
        a1[1].m64_u64 = (uint64_t)v84;
        v86 = _m_punpckhdq(v81, v83);
        v87 = _m_punpckhdq(v84, v85);
        v88 = _m_punpckldq(v83, v83);
        v89 = _m_punpckldq(v85, v85);
        v90 = _m_punpckhdq(v86, v86);
        v91 = _m_pfmul(v368, v90);
        v92 = _m_punpckhdq(v87, v87);
        v93 = _m_pfadd(_m_pfadd(_m_pfmul(v90, 0), _m_pfmul(v88, 0)), _m_pfmul(v89, v369));
        v94 = _m_pfadd(_m_pfmul(0, v92), _m_pfadd(_m_pfmul(0, v89), _m_pfadd(v91, _m_pfmul(v367, v88))));
        v95 = a1[4];
        v96 = _m_pfadd(_m_pfmul(v92, (__m64)0x3F80000000000000LL), v93);
        v97 = a1[5];
        a1[2].m64_u64 = (uint64_t)v94;
        a1[3].m64_u64 = (uint64_t)v96;
        v98 = _m_punpckhdq(v93, v95);
        v99 = _m_punpckhdq(v96, v97);
        v100 = _m_punpckldq(v95, v95);
        v101 = _m_punpckldq(v97, v97);
        v102 = _m_punpckhdq(v98, v98);
        v103 = _m_pfmul(v368, v102);
        v104 = _m_punpckhdq(v99, v99);
        v105 = _m_pfadd(_m_pfadd(_m_pfmul(v102, 0), _m_pfmul(v100, 0)), _m_pfmul(v101, v369));
        v106 = _m_pfadd(_m_pfmul(0, v104), _m_pfadd(_m_pfmul(0, v101), _m_pfadd(v103, _m_pfmul(v367, v100))));
        v107 = a1[6];
        v108 = _m_pfadd(_m_pfmul(v104, (__m64)0x3F80000000000000LL), v105);
        v109 = a1[7];
        a1[4].m64_u64 = (uint64_t)v106;
        a1[5].m64_u64 = (uint64_t)v108;
        v110 = _m_punpckhdq(v105, v107);
        v111 = _m_punpckhdq(v108, v109);
        v112 = _m_punpckldq(v107, v107);
        v113 = _m_punpckldq(v109, v109);
        v114 = _m_punpckhdq(v110, v110);
        v115 = _m_pfmul(v368, v114);
        v116 = _m_punpckhdq(v111, v111);
        v117 = _m_pfmul(0, v116);
        v118 = _m_pfadd(_m_pfadd(_m_pfmul(v114, 0), _m_pfmul(v112, 0)), _m_pfmul(v113, v369));
        v119 = _m_pfadd(_m_pfmul(v116, (__m64)0x3F80000000000000LL), v118);
        a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                            v117,
                                            _m_pfadd(_m_pfmul(0, v113), _m_pfadd(v115, _m_pfmul(v367, v112))));
        a1[7].m64_u64 = (uint64_t)v119;
        v120 = a1[1];
        v121 = _m_punpckhdq(v118, (__m64)a1->m64_u64);
        v122 = _m_punpckhdq(v119, v120);
        v123 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
        v124 = _m_punpckldq(v120, v120);
        v125 = _m_punpckhdq(v121, v121);
        v126 = _m_pfmul(v374, v125);
        v127 = _m_punpckhdq(v122, v122);
        v128 = _m_pfadd(_m_pfadd(_m_pfmul(v125, v376), _m_pfmul(v123, v372)), _m_pfmul(v124, v380));
        v129 = _m_pfadd(_m_pfmul(0, v127), _m_pfadd(_m_pfmul(v378, v124), _m_pfadd(v126, _m_pfmul(v370, v123))));
        v130 = a1[2];
        v131 = _m_pfadd(_m_pfmul(v127, v382), v128);
        v132 = a1[3];
        a1->m64_u64 = (uint64_t)v129;
        a1[1].m64_u64 = (uint64_t)v131;
        v133 = _m_punpckhdq(v128, v130);
        v134 = _m_punpckhdq(v131, v132);
        v135 = _m_punpckldq(v130, v130);
        v136 = _m_punpckldq(v132, v132);
        v137 = _m_punpckhdq(v133, v133);
        v138 = _m_pfmul(v374, v137);
        v139 = _m_punpckhdq(v134, v134);
        v140 = _m_pfadd(_m_pfadd(_m_pfmul(v137, v376), _m_pfmul(v135, v372)), _m_pfmul(v136, v380));
        v141 = _m_pfadd(_m_pfmul(0, v139), _m_pfadd(_m_pfmul(v378, v136), _m_pfadd(v138, _m_pfmul(v370, v135))));
        v142 = a1[4];
        v143 = _m_pfadd(_m_pfmul(v139, v382), v140);
        v144 = a1[5];
        a1[2].m64_u64 = (uint64_t)v141;
        a1[3].m64_u64 = (uint64_t)v143;
        v145 = _m_punpckhdq(v140, v142);
        v146 = _m_punpckhdq(v143, v144);
        v147 = _m_punpckldq(v142, v142);
        v148 = _m_punpckldq(v144, v144);
        v149 = _m_punpckhdq(v145, v145);
        v150 = _m_pfmul(v374, v149);
        v151 = _m_punpckhdq(v146, v146);
        v152 = _m_pfadd(_m_pfadd(_m_pfmul(v149, v376), _m_pfmul(v147, v372)), _m_pfmul(v148, v380));
        v153 = _m_pfadd(_m_pfmul(0, v151), _m_pfadd(_m_pfmul(v378, v148), _m_pfadd(v150, _m_pfmul(v370, v147))));
        v154 = a1[6];
        v155 = _m_pfadd(_m_pfmul(v151, v382), v152);
        v156 = a1[7];
        a1[4].m64_u64 = (uint64_t)v153;
        a1[5].m64_u64 = (uint64_t)v155;
        v157 = _m_punpckhdq(v152, v154);
        v158 = _m_punpckhdq(v155, v156);
        v159 = _m_punpckldq(v154, v154);
        v160 = _m_punpckldq(v156, v156);
        v161 = _m_punpckhdq(v157, v157);
        v162 = _m_punpckhdq(v158, v158);
        a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                            _m_pfmul(0, v162),
                                            _m_pfadd(
                                              _m_pfmul(v378, v160),
                                              _m_pfadd(_m_pfmul(v374, v161), _m_pfmul(v370, v159))));
        a1[7].m64_u64 = (uint64_t)_m_pfadd(
                                            _m_pfmul(v162, v382),
                                            _m_pfadd(
                                              _m_pfadd(_m_pfmul(v161, v376), _m_pfmul(v159, v372)),
                                              _m_pfmul(v160, v380)));
        v163 = _m_pfadd(_mm_cvtsi32_si64(a2[1].m64_u32[0]), _mm_cvtsi32_si64(a1[7].m64_u32[0]));
        a1[6].m64_u64 = (uint64_t)_m_pfadd((__m64)a2->m64_u64, a1[6]);
        a1[7].m64_i32[0] = _mm_cvtsi64_si32(v163);
      }
      else
      {
        result = a1;
        a1->m64_u64 = (uint64_t)_m_punpckldq(v370, v374);
        a1[2].m64_u64 = (uint64_t)_m_punpckhdq(v370, v374);
        v164 = _m_punpckldq(v380, v382);
        a1[5].m64_u64 = (uint64_t)v164;
        a1[7].m64_u64 = (uint64_t)_m_punpckhdq(v380, v382);
        a1[4].m64_u64 = (uint64_t)_m_punpckldq(v372, v376);
        v165 = _m_punpckldq(v378, 0);
        a1[6].m64_u64 = (uint64_t)_m_punpckhdq(v372, v376);
        a1[3].m64_u64 = (uint64_t)_m_punpckhdq(v378, 0);
        a1[1].m64_u64 = (uint64_t)v165;
        v166 = a1[1];
        v167 = _m_punpckhdq(v165, (__m64)a1->m64_u64);
        v168 = _m_punpckhdq(v164, v166);
        v169 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
        v170 = _m_punpckldq(v166, v166);
        v171 = _m_punpckhdq(v167, v167);
        v172 = _m_pfmul(v368, v171);
        v173 = _m_punpckhdq(v168, v168);
        v174 = _m_pfadd(_m_pfadd(_m_pfmul(v171, 0), _m_pfmul(v169, 0)), _m_pfmul(v170, v369));
        v175 = _m_pfadd(_m_pfmul(0, v173), _m_pfadd(_m_pfmul(0, v170), _m_pfadd(v172, _m_pfmul(v367, v169))));
        v176 = a1[2];
        v177 = _m_pfadd(_m_pfmul(v173, (__m64)0x3F80000000000000LL), v174);
        v178 = a1[3];
        a1->m64_u64 = (uint64_t)v175;
        a1[1].m64_u64 = (uint64_t)v177;
        v179 = _m_punpckhdq(v174, v176);
        v180 = _m_punpckhdq(v177, v178);
        v181 = _m_punpckldq(v176, v176);
        v182 = _m_punpckldq(v178, v178);
        v183 = _m_punpckhdq(v179, v179);
        v184 = _m_pfmul(v368, v183);
        v185 = _m_punpckhdq(v180, v180);
        v186 = _m_pfadd(_m_pfadd(_m_pfmul(v183, 0), _m_pfmul(v181, 0)), _m_pfmul(v182, v369));
        v187 = _m_pfadd(_m_pfmul(0, v185), _m_pfadd(_m_pfmul(0, v182), _m_pfadd(v184, _m_pfmul(v367, v181))));
        v188 = a1[4];
        v189 = _m_pfadd(_m_pfmul(v185, (__m64)0x3F80000000000000LL), v186);
        v190 = a1[5];
        a1[2].m64_u64 = (uint64_t)v187;
        a1[3].m64_u64 = (uint64_t)v189;
        v191 = _m_punpckhdq(v186, v188);
        v192 = _m_punpckhdq(v189, v190);
        v193 = _m_punpckldq(v188, v188);
        v194 = _m_punpckldq(v190, v190);
        v195 = _m_punpckhdq(v191, v191);
        v196 = _m_pfmul(v368, v195);
        v197 = _m_punpckhdq(v192, v192);
        v198 = _m_pfadd(_m_pfadd(_m_pfmul(v195, 0), _m_pfmul(v193, 0)), _m_pfmul(v194, v369));
        v199 = _m_pfadd(_m_pfmul(0, v197), _m_pfadd(_m_pfmul(0, v194), _m_pfadd(v196, _m_pfmul(v367, v193))));
        v200 = a1[6];
        v201 = _m_pfadd(_m_pfmul(v197, (__m64)0x3F80000000000000LL), v198);
        v202 = a1[7];
        a1[4].m64_u64 = (uint64_t)v199;
        a1[5].m64_u64 = (uint64_t)v201;
        v203 = _m_punpckhdq(v198, v200);
        v204 = _m_punpckhdq(v201, v202);
        v205 = _m_punpckldq(v200, v200);
        v206 = _m_punpckldq(v202, v202);
        v207 = _m_punpckhdq(v203, v203);
        v208 = _m_pfmul(v368, v207);
        v209 = _m_punpckhdq(v204, v204);
        v210 = _m_pfmul(0, v209);
        v211 = _m_pfadd(_m_pfadd(_m_pfmul(v207, 0), _m_pfmul(v205, 0)), _m_pfmul(v206, v369));
        v212 = _m_pfadd(_m_pfmul(v209, (__m64)0x3F80000000000000LL), v211);
        a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                            v210,
                                            _m_pfadd(_m_pfmul(0, v206), _m_pfadd(v208, _m_pfmul(v367, v205))));
        a1[7].m64_u64 = (uint64_t)v212;
        v213 = a1[1];
        v214 = _m_punpckhdq(v211, (__m64)a1->m64_u64);
        v215 = _m_punpckhdq(v212, v213);
        v216 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
        v217 = _m_punpckldq(v213, v213);
        v218 = _m_punpckhdq(v214, v214);
        v219 = _m_pfmul(v374, v218);
        v220 = _m_punpckhdq(v215, v215);
        v221 = _m_pfadd(_m_pfadd(_m_pfmul(v218, v376), _m_pfmul(v216, v372)), _m_pfmul(v217, v380));
        v222 = _m_pfadd(_m_pfmul(0, v220), _m_pfadd(_m_pfmul(v378, v217), _m_pfadd(v219, _m_pfmul(v370, v216))));
        v223 = a1[2];
        v224 = _m_pfadd(_m_pfmul(v220, v382), v221);
        v225 = a1[3];
        a1->m64_u64 = (uint64_t)v222;
        a1[1].m64_u64 = (uint64_t)v224;
        v226 = _m_punpckhdq(v221, v223);
        v227 = _m_punpckhdq(v224, v225);
        v228 = _m_punpckldq(v223, v223);
        v229 = _m_punpckldq(v225, v225);
        v230 = _m_punpckhdq(v226, v226);
        v231 = _m_pfmul(v374, v230);
        v232 = _m_punpckhdq(v227, v227);
        v233 = _m_pfadd(_m_pfadd(_m_pfmul(v230, v376), _m_pfmul(v228, v372)), _m_pfmul(v229, v380));
        v234 = _m_pfadd(_m_pfmul(0, v232), _m_pfadd(_m_pfmul(v378, v229), _m_pfadd(v231, _m_pfmul(v370, v228))));
        v235 = a1[4];
        v236 = _m_pfadd(_m_pfmul(v232, v382), v233);
        v237 = a1[5];
        a1[2].m64_u64 = (uint64_t)v234;
        a1[3].m64_u64 = (uint64_t)v236;
        v238 = _m_punpckhdq(v233, v235);
        v239 = _m_punpckhdq(v236, v237);
        v240 = _m_punpckldq(v235, v235);
        v241 = _m_punpckldq(v237, v237);
        v242 = _m_punpckhdq(v238, v238);
        v243 = _m_pfmul(v374, v242);
        v244 = _m_punpckhdq(v239, v239);
        v245 = _m_pfadd(_m_pfadd(_m_pfmul(v242, v376), _m_pfmul(v240, v372)), _m_pfmul(v241, v380));
        v246 = _m_pfadd(_m_pfmul(0, v244), _m_pfadd(_m_pfmul(v378, v241), _m_pfadd(v243, _m_pfmul(v370, v240))));
        v247 = a1[6];
        v248 = _m_pfadd(_m_pfmul(v244, v382), v245);
        v249 = a1[7];
        a1[4].m64_u64 = (uint64_t)v246;
        a1[5].m64_u64 = (uint64_t)v248;
        v250 = _m_punpckhdq(v245, v247);
        v251 = _m_punpckhdq(v248, v249);
        v252 = _m_punpckldq(v247, v247);
        v253 = _m_punpckldq(v249, v249);
        v254 = _m_punpckhdq(v250, v250);
        v255 = _m_punpckhdq(v251, v251);
        a1[6].m64_u64 = (uint64_t)_m_pfadd(
                                            _m_pfmul(0, v255),
                                            _m_pfadd(
                                              _m_pfmul(v378, v253),
                                              _m_pfadd(_m_pfmul(v374, v254), _m_pfmul(v370, v252))));
        a1[7].m64_u64 = (uint64_t)_m_pfadd(
                                            _m_pfmul(v255, v382),
                                            _m_pfadd(
                                              _m_pfadd(_m_pfmul(v254, v376), _m_pfmul(v252, v372)),
                                              _m_pfmul(v253, v380)));
      }
    }
    else
    {
      v256 = _mm_cvtsi32_si64(a4[1].m64_u32[0]);
      v257 = _m_punpckhdq(0, (__m64)a4->m64_u64);
      a1->m64_u64 = (uint64_t)_m_punpckldq((__m64)a4->m64_u64, 0);
      a1[1].m64_u64 = 0;
      a1[2].m64_u64 = (uint64_t)v257;
      a1[3].m64_u64 = 0;
      a1[4].m64_u64 = 0;
      a1[5].m64_u64 = (uint64_t)v256;
      a1[6].m64_u64 = 0;
      a1[7].m64_u64 = 0x3F80000000000000LL;
    }
  }
  else
  {
    v258 = _mm_cvtsi32_si64(0x3F800000u);
    v259 = _m_pswapd(v258);
    a1->m64_u64 = (uint64_t)v258;
    a1[1].m64_u64 = 0;
    a1[2].m64_u64 = (uint64_t)v259;
    a1[3].m64_u64 = 0;
    a1[4].m64_u64 = 0;
    a1[5].m64_u64 = (uint64_t)v258;
    a1[6].m64_u64 = 0;
    a1[7].m64_u64 = (uint64_t)v259;
  }
  if ( a6 != nullptr )
  {
    v260 = a6[1];
    v261 = _m_pfadd(v260, v260);
    v262 = _m_pfadd((__m64)a6->m64_u64, (__m64)a6->m64_u64);
    v263 = _m_pfmul(v262, (__m64)a6->m64_u64);
    v264 = _m_punpckldq(v262, v261);
    v265 = _m_pfmul((__m64)a6->m64_u64, v261);
    v266 = _m_pfmul(_m_pswapd((__m64)a6->m64_u64), v261);
    v267 = _m_pfmul(v261, v260);
    v268 = _m_pfmul(_m_punpckhdq((__m64)a6->m64_u64, v260), v264);
    v269 = _m_pfpnacc(v266, v266);
    v270 = _m_pfpnacc(v268, v268);
    v271 = _m_pfpnacc(v265, v265);
    v272 = _m_pfsub(_m_pfsubr(v263, (__m64)0x3F8000003F800000LL), _m_punpckldq(v267, v267));
    v273 = _m_punpckldq(_m_pswapd(v271), v269);
    v274 = _m_punpckldq(v271, 0);
    v379 = v273;
    v275 = _m_punpckhdq(v269, 0);
    v373 = v274;
    v381 = _m_punpckhdq(_m_pfsubr(_m_pfacc(v263, v263), (__m64)0x3F8000003F800000LL), 0);
    v371 = _m_punpckhdq(v272, v270);
    v375 = _m_punpckldq(v270, v272);
    v377 = v275;
    v383 = _m_punpckldq(0, (__m64)1065353216LL);
    if ( a5 != nullptr )
    {
      v276 = (__m64)a5->m64_u64;
      v277 = _mm_cvtsi32_si64(a5[1].m64_u32[0]);
      v278 = _m_pfsub(_mm_cvtsi32_si64(result[7].m64_u32[0]), v277);
      result[6].m64_u64 = (uint64_t)_m_pfsub(result[6], (__m64)a5->m64_u64);
      result[7].m64_i32[0] = _mm_cvtsi64_si32(v278);
      v279 = result[1];
      v280 = _m_punpckhdq(v276, (__m64)result->m64_u64);
      v281 = _m_punpckhdq(v277, v279);
      v282 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
      v283 = _m_punpckldq(v279, v279);
      v284 = _m_punpckhdq(v280, v280);
      v285 = _m_pfmul(v375, v284);
      v286 = _m_punpckhdq(v281, v281);
      v287 = _m_pfadd(_m_pfadd(_m_pfmul(v284, v377), _m_pfmul(v282, v373)), _m_pfmul(v283, v381));
      v288 = _m_pfadd(_m_pfmul(0, v286), _m_pfadd(_m_pfmul(v379, v283), _m_pfadd(v285, _m_pfmul(v371, v282))));
      v289 = result[2];
      v290 = _m_pfadd(_m_pfmul(v286, v383), v287);
      v291 = result[3];
      result->m64_u64 = (uint64_t)v288;
      result[1].m64_u64 = (uint64_t)v290;
      v292 = _m_punpckhdq(v287, v289);
      v293 = _m_punpckhdq(v290, v291);
      v294 = _m_punpckldq(v289, v289);
      v295 = _m_punpckldq(v291, v291);
      v296 = _m_punpckhdq(v292, v292);
      v297 = _m_pfmul(v375, v296);
      v298 = _m_punpckhdq(v293, v293);
      v299 = _m_pfadd(_m_pfadd(_m_pfmul(v296, v377), _m_pfmul(v294, v373)), _m_pfmul(v295, v381));
      v300 = _m_pfadd(_m_pfmul(0, v298), _m_pfadd(_m_pfmul(v379, v295), _m_pfadd(v297, _m_pfmul(v371, v294))));
      v301 = result[4];
      v302 = _m_pfadd(_m_pfmul(v298, v383), v299);
      v303 = result[5];
      result[2].m64_u64 = (uint64_t)v300;
      result[3].m64_u64 = (uint64_t)v302;
      v304 = _m_punpckhdq(v299, v301);
      v305 = _m_punpckhdq(v302, v303);
      v306 = _m_punpckldq(v301, v301);
      v307 = _m_punpckldq(v303, v303);
      v308 = _m_punpckhdq(v304, v304);
      v309 = _m_pfmul(v375, v308);
      v310 = _m_punpckhdq(v305, v305);
      v311 = _m_pfadd(_m_pfadd(_m_pfmul(v308, v377), _m_pfmul(v306, v373)), _m_pfmul(v307, v381));
      v312 = _m_pfadd(_m_pfmul(0, v310), _m_pfadd(_m_pfmul(v379, v307), _m_pfadd(v309, _m_pfmul(v371, v306))));
      v313 = result[6];
      v314 = _m_pfadd(_m_pfmul(v310, v383), v311);
      v315 = result[7];
      result[4].m64_u64 = (uint64_t)v312;
      result[5].m64_u64 = (uint64_t)v314;
      v316 = _m_punpckhdq(v311, v313);
      v317 = _m_punpckhdq(v314, v315);
      v318 = _m_punpckldq(v313, v313);
      v319 = _m_punpckldq(v315, v315);
      v320 = _m_punpckhdq(v316, v316);
      v321 = _m_punpckhdq(v317, v317);
      result[6].m64_u64 = (uint64_t)_m_pfadd(
                                              _m_pfmul(0, v321),
                                              _m_pfadd(
                                                _m_pfmul(v379, v319),
                                                _m_pfadd(_m_pfmul(v375, v320), _m_pfmul(v371, v318))));
      result[7].m64_u64 = (uint64_t)_m_pfadd(
                                              _m_pfmul(v321, v383),
                                              _m_pfadd(
                                                _m_pfadd(_m_pfmul(v320, v377), _m_pfmul(v318, v373)),
                                                _m_pfmul(v319, v381)));
      v322 = _m_pfadd(_mm_cvtsi32_si64(result[7].m64_u32[0]), _mm_cvtsi32_si64(a5[1].m64_u32[0]));
      result[6].m64_u64 = (uint64_t)_m_pfadd(result[6], (__m64)a5->m64_u64);
      result[7].m64_i32[0] = _mm_cvtsi64_si32(v322);
    }
    else
    {
      v323 = result[1];
      v324 = _m_punpckhdq(v274, (__m64)result->m64_u64);
      v325 = _m_punpckhdq(v275, v323);
      v326 = _m_punpckldq((__m64)result->m64_u64, (__m64)result->m64_u64);
      v327 = _m_punpckldq(v323, v323);
      v328 = _m_punpckhdq(v324, v324);
      v329 = _m_pfmul(v375, v328);
      v330 = _m_punpckhdq(v325, v325);
      v331 = _m_pfadd(_m_pfadd(_m_pfmul(v328, v377), _m_pfmul(v326, v373)), _m_pfmul(v327, v381));
      v332 = _m_pfadd(_m_pfmul(0, v330), _m_pfadd(_m_pfmul(v379, v327), _m_pfadd(v329, _m_pfmul(v371, v326))));
      v333 = result[2];
      v334 = _m_pfadd(_m_pfmul(v330, v383), v331);
      v335 = result[3];
      result->m64_u64 = (uint64_t)v332;
      result[1].m64_u64 = (uint64_t)v334;
      v336 = _m_punpckhdq(v331, v333);
      v337 = _m_punpckhdq(v334, v335);
      v338 = _m_punpckldq(v333, v333);
      v339 = _m_punpckldq(v335, v335);
      v340 = _m_punpckhdq(v336, v336);
      v341 = _m_pfmul(v375, v340);
      v342 = _m_punpckhdq(v337, v337);
      v343 = _m_pfadd(_m_pfadd(_m_pfmul(v340, v377), _m_pfmul(v338, v373)), _m_pfmul(v339, v381));
      v344 = _m_pfadd(_m_pfmul(0, v342), _m_pfadd(_m_pfmul(v379, v339), _m_pfadd(v341, _m_pfmul(v371, v338))));
      v345 = result[4];
      v346 = _m_pfadd(_m_pfmul(v342, v383), v343);
      v347 = result[5];
      result[2].m64_u64 = (uint64_t)v344;
      result[3].m64_u64 = (uint64_t)v346;
      v348 = _m_punpckhdq(v343, v345);
      v349 = _m_punpckhdq(v346, v347);
      v350 = _m_punpckldq(v345, v345);
      v351 = _m_punpckldq(v347, v347);
      v352 = _m_punpckhdq(v348, v348);
      v353 = _m_pfmul(v375, v352);
      v354 = _m_punpckhdq(v349, v349);
      v355 = _m_pfadd(_m_pfadd(_m_pfmul(v352, v377), _m_pfmul(v350, v373)), _m_pfmul(v351, v381));
      v356 = _m_pfadd(_m_pfmul(0, v354), _m_pfadd(_m_pfmul(v379, v351), _m_pfadd(v353, _m_pfmul(v371, v350))));
      v357 = result[6];
      v358 = _m_pfadd(_m_pfmul(v354, v383), v355);
      v359 = result[7];
      result[4].m64_u64 = (uint64_t)v356;
      result[5].m64_u64 = (uint64_t)v358;
      v360 = _m_punpckhdq(v355, v357);
      v361 = _m_punpckhdq(v358, v359);
      v362 = _m_punpckldq(v357, v357);
      v363 = _m_punpckldq(v359, v359);
      v364 = _m_punpckhdq(v360, v360);
      v365 = _m_punpckhdq(v361, v361);
      result[6].m64_u64 = (uint64_t)_m_pfadd(
                                              _m_pfmul(0, v365),
                                              _m_pfadd(
                                                _m_pfmul(v379, v363),
                                                _m_pfadd(_m_pfmul(v375, v364), _m_pfmul(v371, v362))));
      result[7].m64_u64 = (uint64_t)_m_pfadd(
                                              _m_pfmul(v365, v383),
                                              _m_pfadd(
                                                _m_pfadd(_m_pfmul(v364, v377), _m_pfmul(v362, v373)),
                                                _m_pfmul(v363, v381)));
    }
  }
  if ( a7 != nullptr )
  {
    v366 = _m_pfadd(_mm_cvtsi32_si64(result[7].m64_u32[0]), _mm_cvtsi32_si64(a7[1].m64_u32[0]));
    result[6].m64_u64 = (uint64_t)_m_pfadd(result[6], (__m64)a7->m64_u64);
    result[7].m64_i32[0] = _mm_cvtsi64_si32(v366);
  }
  _m_femms();
  return result;
}

