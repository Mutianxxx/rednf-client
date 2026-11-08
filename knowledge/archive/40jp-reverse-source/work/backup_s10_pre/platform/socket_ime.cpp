
// ============================================================
// 【40JP逆向源代码工程】src/platform/socket_ime.cpp
// 模块: 0x69 区 —— ISocket/nIIme/NCEdit 三自证类 + 3DNow! 数学 + CRT 尾
// 来源: work/dump_tail.txt  区块: 0x690000-0x6A0000
//
// 【L1 精修层】本文件已完成 L1 精修（注释级），内容:
//   1) 分区组织（9 个 SECTION，按 VA 升序，见下方索引）
//   2) ISocket 网络栈全链标注（Init/Connect/OnSocketMsg/Send/Recv/Close/Cleanup，
//      与 src/nengine/net_socket.cpp 发包 API 的两级关系见 SECTION 4 说明）
//   3) NCEdit 聊天输入控件 + nIIme IME 组合处理链标注（SJIS 双字节逐字节佐证）
//   4) CWSBuffer 环形缓冲（ISocket 底层）方法体标注
//   5) 其余函数逐个一行语义注释（【推断】= 无字符串直证，按调用/常数佐证）
// 函数体逻辑与 L2 转写层逐字一致，未做任何改动（剥离本文件插入的注释行可
// 逐字节还原 L2 原文；自验见 work/refine_l1_socket_ime.py 运行时断言）。
//
// 本区重要结构结论（本次精修推理）:
//   - 三个 Neople 自证类全在本文件: ISocket(0x6985F0-0x698F80，网络) /
//     nIIme(IME 组合泵，主体 sub_69BE10 IsEndComposition) /
//     NCEdit(0x69AB50-0x69BE10，聊天输入控件)。自证串: "Disconnect %d" /
//     "ISocket::Send() : nWOULD_BLOCK_COUNT > 10000" / "NCEdit::Empty() call" /
//     "nIIme::IsEndComposition()...pCompositBuffer_*"。
//   - CWSBuffer（vtable off_749D94）= ISocket 收发环形缓冲，方法体物理上散落
//     文件尾 SECTION 8（0x69DE60-0x69DF70），由 ISocket 直接字段访问。
//   - SJIS 双字节判断以"负字节 == -127..-97 / -32..-22 / -19/-18/-6/-5/-4"
//     的巨型 or 链直证（0x81-0x9F / 0xE0-0xEF 首字节表），日化客户端关键证据。
//   - 0x691070-0x6957C0 的 3DNow!(_m_pfmul/_m_pfacc/_m_pswapd) 数学群与
//     d3d8_loader.cpp 的 SSE 群同构 —— 同一 D3DX 风格数学库的 AMD 分支，
//     与 missing_tail.cpp 0x680134/0x680380 (AuthenticAMD/UnknownVendr)
//     CPU 检测构成"厂商分派"关系。
//
// 交叉引用（0x69 区缺漏 24 函数在 missing_tail.cpp，计划内不精修）:
//   导入 thunk: ImmGetContext/ImmNotifyIME/ImmReleaseContext/
//   ImmGetCompositionStringA/ijl15_3/VerQueryValueA/GetFileVersionInfoA/
//   IcmpSendEcho/gethostbyname/ntohl/FSOUND_* —— 与本文件 SECTION 2 同族；
//   小桩: sub_69A4C0(虚表+0x10 转发，紧邻 69A4D0)、sub_69C690/69C6A0
//   (*(this+28)+112/+116 getter，紧邻 69C6B0)、sub_69CFB0(→sub_69C7B0 转发)。
//
// 函数数: 269
// ============================================================

#include "../../common/arad_types.h"


// ============================================================
// SECTION 1  3DNow!/MMX 向量与调色板数学（0x691070-0x6957C0）
// ------------------------------------------------------------
// _m_pfmul/_m_pfadd/_m_pfacc/_m_pswapd/_m_pfrcp* 为 AMD 3DNow! 指令，
// 成对 float 语义（0x3F000000=0.5f / 0x3F800000=1.0f 双字对）。
// 与 d3d8_loader.cpp 的 SSE 群（0x68A4B0-0x68C6BE）互为 CPU 厂商分支；
// 分派上游证据: missing_tail.cpp 0x680134/0x680380 (AuthenticAMD/UnknownVendr)
// 及 0x6759F7 ___sse2_available_init。尾段 0x694AC0 起为 SSE exp2 多项式。
// ============================================================
// ------------------------------------------------------------
// 0x691070 sub_691070
// ------------------------------------------------------------
// 【L1】3DNow! vec2 仿射变换：2x2 矩阵(_m_pswapd 转置)×两点 + 平移
int /*stdcall*/ sub_691070(__m64 *pArg1, uint32_t *uArg2, __m64 *pArg3)
{
  __m64 v3; // mm1
  __m64 v4; // mm2
  __m64 v5; // mm0
  __m64 v6; // mm5
  __m64 v7; // mm6
  __m64 v8; // mm1
  __m64 v9; // mm0
  __m64 v10; // mm7
  __m64 v11; // mm2
  __m64 v12; // rt1
  __m64 v13; // mm1
  __m64 v14; // mm0
  __m64 v15; // mm5
  __m64 v16; // mm6
  __m64 v17; // mm1
  __m64 v18; // mm0
  __m64 v19; // mm7
  __m64 v20; // mm2
  __m64 v21; // mm0
  __m64 v22; // mm0
  __m64 v23; // mm1
  int result; // eax
  __m64 v25; // mm0
  __m64 v26; // mm1
  __m64 v27; // mm3
  __m64 v28; // mm6
  __m64 v29; // mm4
  __m64 v30; // mm7
  __m64 v31; // mm3
  __m64 v32; // mm6
  __m64 v33; // mm4
  __m64 v34; // mm7
  __m64 v35; // [esp+0h] [ebp-40h]
  __m64 v36; // [esp+8h] [ebp-38h]
  __m64 v37; // [esp+10h] [ebp-30h]
  __m64 v38; // [esp+18h] [ebp-28h]
  __m64 v39; // [esp+20h] [ebp-20h]
  __m64 v40; // [esp+28h] [ebp-18h]
  __m64 v41; // [esp+30h] [ebp-10h]
  __m64 v42; // [esp+38h] [ebp-8h]

  v3 = pArg3[2];
  v4 = pArg3[4];
  v5 = _m_pswapd(pArg3[6]);
  v6 = _m_pfnacc(_m_pfmul(_m_pswapd(v3), (__m64)pArg3->m64_u64), _m_pfmul(_m_pswapd(v4), (__m64)pArg3->m64_u64));
  v7 = _m_pfnacc(_m_pfmul(v5, (__m64)pArg3->m64_u64), _m_pfmul(_m_pswapd(v4), v3));
  v8 = _m_pfnacc(_m_pfmul(v3, v5), _m_pfmul(v4, v5));
  v9 = pArg3[7];
  v10 = pArg3[5];
  v36 = _m_pfsub(
          _m_pfadd(_m_pfmul(_m_punpckhdq(v7, v7), v9), _m_pfmul(_m_punpckhdq(v8, v8), pArg3[3])),
          _m_pfmul(_m_punpckldq(v8, v8), v10));
  v38 = _m_pfadd(
          _m_pfsub(_m_pfmul(_m_punpckhdq(v6, v6), v9), _m_pfmul(_m_punpckldq(v7, v7), v10)),
          _m_pfmul(_m_punpckhdq(v8, v8), pArg3[1]));
  v11 = _m_punpckldq(v6, v6);
  v40 = _m_pfsub(
          _m_pfadd(_m_pfmul(v9, v11), _m_pfmul(_m_punpckldq(v8, v8), pArg3[1])),
          _m_pfmul(_m_punpckldq(v7, v7), pArg3[3]));
  v12 = pArg3[1];
  v42 = _m_pfadd(
          _m_pfsub(_m_pfmul(v11, v10), _m_pfmul(_m_punpckhdq(v6, v6), pArg3[3])),
          _m_pfmul(_m_punpckhdq(v7, v7), v12));
  v13 = pArg3[3];
  v14 = _m_pswapd(v9);
  v15 = _m_pfnacc(_m_pfmul(_m_pswapd(v13), v12), _m_pfmul(_m_pswapd(v10), v12));
  v16 = _m_pfnacc(_m_pfmul(v14, v12), _m_pfmul(_m_pswapd(v10), v13));
  v17 = _m_pfnacc(_m_pfmul(v13, v14), _m_pfmul(v10, v14));
  v18 = pArg3[6];
  v19 = pArg3[4];
  v35 = _m_pfsub(
          _m_pfadd(_m_pfmul(_m_punpckhdq(v16, v16), v18), _m_pfmul(_m_punpckhdq(v17, v17), pArg3[2])),
          _m_pfmul(_m_punpckldq(v17, v17), v19));
  v37 = _m_pfadd(
          _m_pfsub(_m_pfmul(_m_punpckhdq(v15, v15), v18), _m_pfmul(_m_punpckldq(v16, v16), v19)),
          _m_pfmul(_m_punpckhdq(v17, v17), (__m64)pArg3->m64_u64));
  v20 = _m_punpckldq(v15, v15);
  v39 = _m_pfsub(
          _m_pfadd(_m_pfmul(v18, v20), _m_pfmul(_m_punpckldq(v17, v17), (__m64)pArg3->m64_u64)),
          _m_pfmul(_m_punpckldq(v16, v16), pArg3[2]));
  v41 = _m_pfadd(
          _m_pfsub(_m_pfmul(v20, v19), _m_pfmul(_m_punpckhdq(v15, v15), pArg3[2])),
          _m_pfmul(_m_punpckhdq(v16, v16), (__m64)pArg3->m64_u64));
  v21 = _m_pfnacc(
          _m_pfmul(_m_punpckhdq(v39, v41), _m_punpckldq(v19, v18)),
          _m_pfmul(_m_punpckldq((__m64)pArg3->m64_u64, (__m64)pArg3[2].m64_u32[0]), _m_punpckhdq(v35, v37)));
  v22 = _m_pfacc(v21, v21);
  if ( uArg2 != nullptr )
    *uArg2 = _mm_cvtsi64_si32(v22);
  v23 = _m_pfrcp(v22);
  result = _mm_cvtsi64_si32(_m_pfcmpeq(0, v22));
  v25 = _m_pfmul(_m_pfrcpit2(_m_pfrcpit1(_m_punpckldq(v22, v22), v23), v23), (__m64)0xBF8000003F800000uLL);
  v26 = _m_pswapd(v25);
  if ( result == 0 )
  {
    result = (int)pArg1;
    v27 = _m_pfmul(v37, v25);
    v28 = _m_pfmul(v38, v25);
    v29 = _m_pfmul(v35, v26);
    v30 = _m_pfmul(v36, v26);
    pArg1->m64_u64 = (uint64_t)_m_punpckhdq(v29, v27);
    pArg1[2].m64_u64 = (uint64_t)_m_punpckldq(v29, v27);
    pArg1[4].m64_u64 = (uint64_t)_m_punpckhdq(v30, v28);
    pArg1[6].m64_u64 = (uint64_t)_m_punpckldq(v30, v28);
    v31 = _m_pfmul(v41, v25);
    v32 = _m_pfmul(v42, v25);
    v33 = _m_pfmul(v39, v26);
    v34 = _m_pfmul(v40, v26);
    pArg1[1].m64_u64 = (uint64_t)_m_punpckhdq(v33, v31);
    pArg1[3].m64_u64 = (uint64_t)_m_punpckldq(v33, v31);
    pArg1[5].m64_u64 = (uint64_t)_m_punpckhdq(v34, v32);
    pArg1[7].m64_u64 = (uint64_t)_m_punpckldq(v34, v32);
  }
  _m_femms();
  return result;
}


// ------------------------------------------------------------
// 0x691352 sub_691352
// ------------------------------------------------------------
// 【L1】3DNow! vec2 投影变换：含 1/w 透视除法（_m_pfrcp/_m_pfrcpit2 迭代精化）
__m64 */*stdcall*/ sub_691352(__m64 *pArg1, __m64 *pArg2, __m64 *pArg3)
{
  __m64 v3; // mm1
  __m64 v4; // mm4
  __m64 v5; // mm5
  __m64 v6; // mm7
  __m64 v7; // mm0
  __m64 v8; // mm1
  __m64 v9; // mm4
  __m64 *result; // eax
  __m64 v11; // mm4
  __m64 v12; // mm4
  __m64 v13; // mm4
  __m64 v14; // mm4
  __m64 v15; // mm4
  __m64 v16; // mm4
  __m64 v17; // mm4
  __m64 v18; // [esp+0h] [ebp-44h]
  __m64 v19; // [esp+0h] [ebp-44h]
  __m64 v20; // [esp+8h] [ebp-3Ch]
  __m64 v21; // [esp+8h] [ebp-3Ch]
  __m64 v22; // [esp+10h] [ebp-34h]
  __m64 v23; // [esp+10h] [ebp-34h]
  __m64 v24; // [esp+18h] [ebp-2Ch]
  __m64 v25; // [esp+18h] [ebp-2Ch]
  __m64 v26; // [esp+20h] [ebp-24h]
  __m64 v27; // [esp+20h] [ebp-24h]
  __m64 v28; // [esp+28h] [ebp-1Ch]
  __m64 v29; // [esp+28h] [ebp-1Ch]
  __m64 v30; // [esp+30h] [ebp-14h]
  __m64 v31; // [esp+38h] [ebp-Ch]

  _m_femms();
  v3 = pArg3[2];
  v4 = pArg3[7];
  v5 = pArg3[5];
  v18 = _m_punpckldq((__m64)pArg3->m64_u64, v3);
  v22 = _m_punpckhdq((__m64)pArg3->m64_u64, v3);
  v6 = pArg3[3];
  v7 = pArg3[4];
  v8 = pArg3[1];
  v28 = _m_punpckldq(v5, v4);
  v31 = _m_punpckhdq(v5, v4);
  v9 = pArg3[6];
  v26 = _m_punpckldq(v8, v6);
  v30 = _m_punpckhdq(v8, v6);
  v24 = _m_punpckhdq(v7, v9);
  v20 = _m_punpckldq(v7, v9);
  result = pArg1;
  v11 = _m_pfadd(
          _m_pfacc(_m_pfmul(v18, pArg2[4]), _m_pfmul(v18, pArg2[6])),
          _m_pfacc(_m_pfmul(v20, pArg2[5]), _m_pfmul(v20, pArg2[7])));
  if ( pArg2 == pArg1 )
  {
    v19 = _m_pfadd(
            _m_pfacc(_m_pfmul(v18, (__m64)pArg2->m64_u64), _m_pfmul(v18, pArg2[2])),
            _m_pfacc(_m_pfmul(v20, pArg2[1]), _m_pfmul(v20, pArg2[3])));
    v21 = v11;
    v15 = _m_pfadd(
            _m_pfacc(_m_pfmul(v22, pArg2[4]), _m_pfmul(v22, pArg2[6])),
            _m_pfacc(_m_pfmul(v24, pArg2[5]), _m_pfmul(v24, pArg2[7])));
    v23 = _m_pfadd(
            _m_pfacc(_m_pfmul(v22, (__m64)pArg2->m64_u64), _m_pfmul(v22, pArg2[2])),
            _m_pfacc(_m_pfmul(v24, pArg2[1]), _m_pfmul(v24, pArg2[3])));
    v25 = v15;
    v16 = _m_pfadd(
            _m_pfacc(_m_pfmul(v26, pArg2[4]), _m_pfmul(v26, pArg2[6])),
            _m_pfacc(_m_pfmul(v28, pArg2[5]), _m_pfmul(v28, pArg2[7])));
    v27 = _m_pfadd(
            _m_pfacc(_m_pfmul(v26, (__m64)pArg2->m64_u64), _m_pfmul(v26, pArg2[2])),
            _m_pfacc(_m_pfmul(v28, pArg2[1]), _m_pfmul(v28, pArg2[3])));
    v29 = v16;
    v17 = _m_pfadd(
            _m_pfacc(_m_pfmul(v30, pArg2[4]), _m_pfmul(v30, pArg2[6])),
            _m_pfacc(_m_pfmul(v31, pArg2[5]), _m_pfmul(v31, pArg2[7])));
    pArg1[6].m64_u64 = (uint64_t)_m_pfadd(
                                        _m_pfacc(_m_pfmul(v30, (__m64)pArg2->m64_u64), _m_pfmul(v30, pArg2[2])),
                                        _m_pfacc(_m_pfmul(v31, pArg2[1]), _m_pfmul(v31, pArg2[3])));
    pArg1[7].m64_u64 = (uint64_t)v17;
    pArg1->m64_u64 = (uint64_t)v19;
    pArg1[1].m64_u64 = (uint64_t)v21;
    pArg1[2].m64_u64 = (uint64_t)v23;
    pArg1[3].m64_u64 = (uint64_t)v25;
    pArg1[4].m64_u64 = (uint64_t)v27;
    pArg1[5].m64_u64 = (uint64_t)v29;
  }
  else
  {
    pArg1->m64_u64 = (uint64_t)_m_pfadd(
                                      _m_pfacc(_m_pfmul(v18, (__m64)pArg2->m64_u64), _m_pfmul(v18, pArg2[2])),
                                      _m_pfacc(_m_pfmul(v20, pArg2[1]), _m_pfmul(v20, pArg2[3])));
    pArg1[1].m64_u64 = (uint64_t)v11;
    v12 = _m_pfadd(
            _m_pfacc(_m_pfmul(v22, pArg2[4]), _m_pfmul(v22, pArg2[6])),
            _m_pfacc(_m_pfmul(v24, pArg2[5]), _m_pfmul(v24, pArg2[7])));
    pArg1[2].m64_u64 = (uint64_t)_m_pfadd(
                                        _m_pfacc(_m_pfmul(v22, (__m64)pArg2->m64_u64), _m_pfmul(v22, pArg2[2])),
                                        _m_pfacc(_m_pfmul(v24, pArg2[1]), _m_pfmul(v24, pArg2[3])));
    pArg1[3].m64_u64 = (uint64_t)v12;
    v13 = _m_pfadd(
            _m_pfacc(_m_pfmul(v26, pArg2[4]), _m_pfmul(v26, pArg2[6])),
            _m_pfacc(_m_pfmul(v28, pArg2[5]), _m_pfmul(v28, pArg2[7])));
    pArg1[4].m64_u64 = (uint64_t)_m_pfadd(
                                        _m_pfacc(_m_pfmul(v26, (__m64)pArg2->m64_u64), _m_pfmul(v26, pArg2[2])),
                                        _m_pfacc(_m_pfmul(v28, pArg2[1]), _m_pfmul(v28, pArg2[3])));
    pArg1[5].m64_u64 = (uint64_t)v13;
    v14 = _m_pfadd(
            _m_pfacc(_m_pfmul(v30, pArg2[4]), _m_pfmul(v30, pArg2[6])),
            _m_pfacc(_m_pfmul(v31, pArg2[5]), _m_pfmul(v31, pArg2[7])));
    pArg1[6].m64_u64 = (uint64_t)_m_pfadd(
                                        _m_pfacc(_m_pfmul(v30, (__m64)pArg2->m64_u64), _m_pfmul(v30, pArg2[2])),
                                        _m_pfacc(_m_pfmul(v31, pArg2[1]), _m_pfmul(v31, pArg2[3])));
    pArg1[7].m64_u64 = (uint64_t)v14;
  }
  _m_femms();
  return result;
}


// ------------------------------------------------------------
// 0x69174A sub_69174A
// ------------------------------------------------------------
// 【L1】3DNow! vec2 仿射变换变体（与 691070 同族，系数排布不同）
int /*stdcall*/ sub_69174A(__m64 *pArg1, uint32_t *uArg2, __m64 *pArg3)
{
  __m64 v3; // mm1
  __m64 v4; // mm2
  __m64 v5; // mm5
  __m64 v6; // mm0
  __m64 v7; // mm4
  __m64 v8; // mm3
  __m64 v9; // mm6
  __m64 v10; // mm4
  __m64 v11; // mm6
  __m64 v12; // mm1
  __m64 v13; // mm0
  __m64 v14; // mm7
  __m64 v15; // mm2
  __m64 v16; // mm0
  __m64 v17; // mm1
  __m64 v18; // mm5
  __m64 v19; // mm0
  __m64 v20; // mm4
  __m64 v21; // mm3
  __m64 v22; // mm6
  __m64 v23; // mm4
  __m64 v24; // mm6
  __m64 v25; // mm1
  __m64 v26; // mm0
  __m64 v27; // mm7
  __m64 v28; // mm2
  __m64 v29; // mm2
  __m64 v30; // mm0
  __m64 v31; // mm0
  __m64 v32; // mm1
  int result; // eax
  __m64 v34; // mm0
  __m64 v35; // mm1
  __m64 v36; // mm3
  __m64 v37; // mm6
  __m64 v38; // mm4
  __m64 v39; // mm7
  __m64 v40; // mm3
  __m64 v41; // mm6
  __m64 v42; // mm4
  __m64 v43; // mm7
  __m64 v44; // [esp+0h] [ebp-44h]
  __m64 v45; // [esp+8h] [ebp-3Ch]
  __m64 v46; // [esp+10h] [ebp-34h]
  __m64 v47; // [esp+18h] [ebp-2Ch]
  __m64 v48; // [esp+20h] [ebp-24h]
  __m64 v49; // [esp+28h] [ebp-1Ch]
  __m64 v50; // [esp+38h] [ebp-Ch]

  v3 = pArg3[2];
  v4 = pArg3[4];
  v5 = _m_pfsub(
         _m_pfmul(_m_punpckldq((__m64)pArg3->m64_u64, (__m64)pArg3->m64_u64), _m_punpckhdq(v3, v4)),
         _m_pfmul(_m_punpckhdq((__m64)pArg3->m64_u64, (__m64)pArg3->m64_u64), _m_punpckldq(v3, v4)));
  v6 = _m_punpckldq((__m64)pArg3->m64_u64, v3);
  v7 = pArg3[6];
  v8 = _m_punpckhdq(v7, v7);
  v9 = _m_punpckhdq(v7, v4);
  v10 = _m_punpckldq(v7, v4);
  v11 = _m_pfsub(_m_pfmul(v9, v6), _m_pfmul(_m_punpckhdq((__m64)pArg3->m64_u64, v3), v10));
  v12 = _m_pfsubr(_m_pfmul(_m_punpckhdq(v3, v4), _m_punpckldq(v10, v10)), _m_pfmul(_m_punpckhdq(v6, v10), v8));
  v13 = pArg3[7];
  v14 = pArg3[5];
  v45 = _m_pfsub(
          _m_pfadd(_m_pfmul(_m_punpckhdq(v11, v11), v13), _m_pfmul(_m_punpckhdq(v12, v12), pArg3[3])),
          _m_pfmul(_m_punpckldq(v12, v12), v14));
  v47 = _m_pfadd(
          _m_pfsub(_m_pfmul(_m_punpckhdq(v5, v5), v13), _m_pfmul(_m_punpckldq(v11, v11), v14)),
          _m_pfmul(_m_punpckhdq(v12, v12), pArg3[1]));
  v15 = _m_punpckldq(v5, v5);
  v49 = _m_pfsub(
          _m_pfadd(_m_pfmul(v13, v15), _m_pfmul(_m_punpckldq(v12, v12), pArg3[1])),
          _m_pfmul(_m_punpckldq(v11, v11), pArg3[3]));
  v50 = _m_pfadd(
          _m_pfsub(_m_pfmul(v15, v14), _m_pfmul(_m_punpckhdq(v5, v5), pArg3[3])),
          _m_pfmul(_m_punpckhdq(v11, v11), pArg3[1]));
  v16 = pArg3[1];
  v17 = pArg3[3];
  v18 = _m_pfsub(
          _m_pfmul(_m_punpckldq(v16, v16), _m_punpckhdq(v17, v14)),
          _m_pfmul(_m_punpckhdq(v16, v16), _m_punpckldq(v17, v14)));
  v19 = _m_punpckldq(v16, v17);
  v20 = pArg3[7];
  v21 = _m_punpckhdq(v20, v20);
  v22 = _m_punpckhdq(v20, v14);
  v23 = _m_punpckldq(v20, v14);
  v24 = _m_pfsub(_m_pfmul(v22, v19), _m_pfmul(_m_punpckhdq(pArg3[1], v17), v23));
  v25 = _m_pfsubr(_m_pfmul(_m_punpckhdq(v17, v14), _m_punpckldq(v23, v23)), _m_pfmul(_m_punpckhdq(v19, v23), v21));
  v26 = pArg3[6];
  v27 = pArg3[4];
  v44 = _m_pfsub(
          _m_pfadd(_m_pfmul(_m_punpckhdq(v24, v24), v26), _m_pfmul(_m_punpckhdq(v25, v25), pArg3[2])),
          _m_pfmul(_m_punpckldq(v25, v25), v27));
  v46 = _m_pfadd(
          _m_pfsub(_m_pfmul(_m_punpckhdq(v18, v18), v26), _m_pfmul(_m_punpckldq(v24, v24), v27)),
          _m_pfmul(_m_punpckhdq(v25, v25), (__m64)pArg3->m64_u64));
  v28 = _m_punpckldq(v18, v18);
  v48 = _m_pfsub(
          _m_pfadd(_m_pfmul(v26, v28), _m_pfmul(_m_punpckldq(v25, v25), (__m64)pArg3->m64_u64)),
          _m_pfmul(_m_punpckldq(v24, v24), pArg3[2]));
  v29 = _m_pfadd(
          _m_pfsub(_m_pfmul(v28, v27), _m_pfmul(_m_punpckhdq(v18, v18), pArg3[2])),
          _m_pfmul(_m_punpckhdq(v24, v24), (__m64)pArg3->m64_u64));
  v30 = _m_pfadd(
          _m_pfmul(_m_punpckhdq(v48, v29), _m_pfmul(_m_punpckldq(v27, v26), (__m64)0xBF8000003F800000uLL)),
          _m_pfmul(
            _m_pfmul(_m_punpckldq((__m64)pArg3->m64_u64, (__m64)pArg3[2].m64_u32[0]), (__m64)0xBF8000003F800000uLL),
            _m_punpckhdq(v44, v46)));
  v31 = _m_pfacc(v30, v30);
  if ( uArg2 != nullptr )
    *uArg2 = _mm_cvtsi64_si32(v31);
  v32 = _m_pfrcp(v31);
  result = _mm_cvtsi64_si32(_m_pfcmpeq(0, v31));
  v34 = _m_pfmul(_m_pfrcpit2(_m_pfrcpit1(_m_punpckldq(v31, v31), v32), v32), (__m64)0xBF8000003F800000uLL);
  v35 = _m_punpckhdq(v34, _m_punpckldq(v29, v34));
  if ( result == 0 )
  {
    v36 = _m_pfmul(v46, v34);
    v37 = _m_pfmul(v47, v34);
    v38 = _m_pfmul(v44, v35);
    v39 = _m_pfmul(v45, v35);
    pArg1->m64_u64 = (uint64_t)_m_punpckhdq(v38, v36);
    pArg1[2].m64_u64 = (uint64_t)_m_punpckldq(v38, v36);
    pArg1[4].m64_u64 = (uint64_t)_m_punpckhdq(v39, v37);
    pArg1[6].m64_u64 = (uint64_t)_m_punpckldq(v39, v37);
    v40 = _m_pfmul(v29, v34);
    v41 = _m_pfmul(v50, v34);
    v42 = _m_pfmul(v48, v35);
    v43 = _m_pfmul(v49, v35);
    pArg1[1].m64_u64 = (uint64_t)_m_punpckhdq(v42, v40);
    pArg1[3].m64_u64 = (uint64_t)_m_punpckldq(v42, v40);
    pArg1[5].m64_u64 = (uint64_t)_m_punpckhdq(v43, v41);
    pArg1[7].m64_u64 = (uint64_t)_m_punpckldq(v43, v41);
    return (int)pArg1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x691A7E sub_691A7E
// ------------------------------------------------------------
// 【L1】3DNow! vec2 变换 + 0.5 偏置半像素对齐（×0x3F000000=0.5f）
__m64 */*stdcall*/ sub_691A7E(__m64 *uArg1, uint32_t *uArg2, __m64 *uArg3)
{
  _m_femms();
  sub_69174A(uArg1, uArg2, uArg3);
  _m_femms();
  return uArg1;
}



// ------------------------------------------------------------
// 0x691B72 sub_691B72
// ------------------------------------------------------------
// 【L1】3DNow! vec2 双分量缩放/插值基元
__m64 */*stdcall*/ sub_691B72(__m64 *pArg1, __m64 *pArg2)
{
  __m64 v2; // mm3
  __m64 v3; // mm0
  __m64 v4; // mm0
  __m64 v5; // mm4
  __m64 v6; // mm5
  __m64 v8; // mm0

  _m_femms();
  v2 = _mm_cvtsi32_si64(pArg2[1].m64_u32[0]);
  v3 = _m_pfadd(_m_pfmul((__m64)pArg2->m64_u64, (__m64)pArg2->m64_u64), _m_pfmul(v2, v2));
  v4 = _m_pfacc(v3, v3);
  v5 = _m_pfrsqrt(v4);
  v6 = _m_pfcmpgt(v4, (__m64)0x80000000800000LL);
  v8 = _m_pfrcpit2(_m_pfrsqit1(v4, _m_pfmul(v5, v5)), v5);
  pArg1->m64_u64 = (uint64_t)_m_pfmul(_m_pand((__m64)pArg2->m64_u64, v6), v8);
  pArg1[1].m64_i32[0] = _mm_cvtsi64_si32(_m_pfmul(_m_pand(v2, v6), v8));
  _m_femms();
  return pArg1;
}



// ------------------------------------------------------------
// 0x691BD1 sub_691BD1
// ------------------------------------------------------------
// 【L1】3DNow! 三点插值混合（a5/a6 = 两轴插值参数）
__m64 */*stdcall*/ sub_691BD1(__m64 *pArg1, __m64 *pArg2, __m64 *pArg3, __m64 *pArg4, unsigned int uArg5, unsigned int uArg6)
{
  __m64 v6; // mm6
  __m64 v7; // mm5
  __m64 v8; // mm7
  __m64 v10; // mm6
  __m64 v11; // mm7
  __m64 v12; // mm1

  v6 = _mm_cvtsi32_si64(uArg5);
  v7 = _mm_cvtsi32_si64(pArg2[1].m64_u32[0]);
  v8 = _mm_cvtsi32_si64(uArg6);
  v10 = _m_punpckldq(v6, v6);
  v11 = _m_punpckldq(v8, v8);
  v12 = _m_pfadd(
          _m_pfadd(_m_pfmul(_m_pfsub(_mm_cvtsi32_si64(pArg3[1].m64_u32[0]), v7), v10), v7),
          _m_pfmul(_m_pfsub(_mm_cvtsi32_si64(pArg4[1].m64_u32[0]), v7), v11));
  pArg1->m64_u64 = (uint64_t)_m_pfadd(
                                    _m_pfadd(
                                      _m_pfmul(_m_pfsub((__m64)pArg3->m64_u64, (__m64)pArg2->m64_u64), v10),
                                      (__m64)pArg2->m64_u64),
                                    _m_pfmul(_m_pfsub((__m64)pArg4->m64_u64, (__m64)pArg2->m64_u64), v11));
  pArg1[1].m64_i32[0] = _mm_cvtsi64_si32(v12);
  _m_femms();
  return pArg1;
}



// ------------------------------------------------------------
// 0x691C42 sub_691C42
// ------------------------------------------------------------
// 【L1】3DNow! 三点插值混合变体（控制点独立传入）
__m64 */*stdcall*/ sub_691C42(__m64 *pArg1, __m64 *pArg2, __m64 *pArg3, __m64 *pArg4, __m64 *pArg5, unsigned int uArg6)
{
  __m64 v6; // mm0
  __m64 v7; // mm1
  __m64 v8; // mm2
  __m64 v9; // mm7
  __m64 v10; // mm4
  __m64 v11; // mm6
  __m64 v12; // mm2
  __m64 v13; // mm5
  __m64 v14; // mm1
  __m64 v15; // mm6
  __m64 v16; // mm2
  __m64 v17; // mm5
  __m64 v18; // mm0
  __m64 v19; // mm1
  __m64 v21; // mm4
  __m64 v22; // mm3
  __m64 v23; // mm0

  _m_femms();
  v6 = _mm_cvtsi32_si64(uArg6);
  v7 = _m_pfmul(v6, v6);
  v8 = _m_pfmul(v7, v6);
  v9 = _m_pfsub(v8, v7);
  v10 = _m_pfmul(v7, (__m64)0x4000000040000000LL);
  v11 = v8;
  v12 = _m_pfmul(v8, (__m64)0x4000000040000000LL);
  v13 = _m_pfmul(v7, (__m64)0x4040000040400000LL);
  v14 = _m_pfsub(v13, v12);
  v15 = _m_pfadd(_m_pfsub(v11, v10), v6);
  v16 = _m_pfadd(_m_pfsub(v12, v13), (__m64)0x3F8000003F800000LL);
  v17 = _m_punpckldq(v9, v9);
  v18 = _m_punpckldq(v14, v14);
  v19 = _m_pfmul(v18, (__m64)pArg4->m64_u64);
  v21 = _m_punpckldq(v15, v15);
  v22 = _m_punpckldq(v16, v16);
  v23 = _m_pfadd(
          _m_pfadd(_m_pfmul(v18, _mm_cvtsi32_si64(pArg4[1].m64_u32[0])), _m_pfmul(v17, _mm_cvtsi32_si64(pArg5[1].m64_u32[0]))),
          _m_pfadd(_m_pfmul(v22, _mm_cvtsi32_si64(pArg2[1].m64_u32[0])), _m_pfmul(v21, _mm_cvtsi32_si64(pArg3[1].m64_u32[0]))));
  pArg1->m64_u64 = (uint64_t)_m_pfadd(
                                    _m_pfadd(v19, _m_pfmul(v17, (__m64)pArg5->m64_u64)),
                                    _m_pfadd(_m_pfmul(v22, (__m64)pArg2->m64_u64), _m_pfmul(v21, (__m64)pArg3->m64_u64)));
  pArg1[1].m64_i32[0] = _mm_cvtsi64_si32(v23);
  _m_femms();
  return pArg1;
}



// ------------------------------------------------------------
// 0x691D16 sub_691D16
// ------------------------------------------------------------
// 【L1】3DNow! 三点插值混合变体（与 691C42 成对）
__m64 */*stdcall*/ sub_691D16(__m64 *pArg1, __m64 *pArg2, __m64 *pArg3, __m64 *pArg4, __m64 *pArg5, unsigned int uArg6)
{
  __m64 v6; // mm1
  __m64 v7; // mm0
  __m64 v8; // mm1
  __m64 v9; // mm0
  __m64 v10; // mm3
  __m64 v11; // mm1
  __m64 v12; // mm0
  __m64 v13; // mm5
  __m64 v14; // mm0
  __m64 v15; // mm2
  __m64 v16; // mm3
  __m64 v17; // mm4
  __m64 v18; // mm5
  __m64 v19; // mm6
  __m64 v21; // mm7
  __m64 v22; // mm0
  __m64 v23; // mm4

  v6 = _mm_cvtsi32_si64(uArg6);
  v7 = _m_punpckldq(v6, v6);
  v8 = _m_punpckldq(v6, (__m64)1065353216LL);
  v9 = _m_pfmul(_m_pfmul(v7, v7), v8);
  v10 = v8;
  v11 = _m_pfmul(v8, v8);
  v12 = _m_pfsub(v9, v11);
  v13 = _m_pfmul(v12, (__m64)0x4000000040400000LL);
  v14 = _m_punpckldq(v13, v12);
  v15 = _m_pfsub(_m_pfadd(_m_punpckldq(v11, v11), _m_pxor(_m_punpckldq(v10, v10), (__m64)0x8000000000000000uLL)), v14);
  v16 = _m_pfsub(v14, _m_punpckhdq(v13, 0));
  v17 = _m_punpckhdq(v15, v15);
  v18 = _m_punpckldq(v16, v16);
  v19 = _m_punpckldq(v15, v15);
  v21 = _m_punpckhdq(v16, v16);
  v22 = _m_pfadd(
          _m_pfadd(_m_pfmul(v18, (__m64)pArg3->m64_u64), _m_pfmul(v17, (__m64)pArg2->m64_u64)),
          _m_pfmul(v19, (__m64)pArg4->m64_u64));
  v23 = _m_pfadd(
          _m_pfadd(
            _m_pfadd(
              _m_pfmul(v17, _mm_cvtsi32_si64(pArg2[1].m64_u32[0])),
              _m_pfmul(v18, _mm_cvtsi32_si64(pArg3[1].m64_u32[0]))),
            _m_pfmul(v19, _mm_cvtsi32_si64(pArg4[1].m64_u32[0]))),
          _m_pfmul(v21, _mm_cvtsi32_si64(pArg5[1].m64_u32[0])));
  pArg1->m64_u64 = (uint64_t)_m_pfmul(
                                    _m_pfadd(v22, _m_pfmul(v21, (__m64)pArg5->m64_u64)),
                                    (__m64)0x3F0000003F000000LL);
  pArg1[1].m64_i32[0] = _mm_cvtsi64_si32(_m_pfmul(v23, (__m64)0x3F0000003F000000LL));
  _m_femms();
  return pArg1;
}



// ------------------------------------------------------------
// 0x691E00 sub_691E00
// ------------------------------------------------------------
// 【L1】3DNow! vec2 投影：mv 变换 + 1/w（_m_pfrcpit1/pit2 Newton 迭代）
__m64 */*stdcall*/ sub_691E00(__m64 *pArg1, __m64 *pArg2, __m64 *pArg3)
{
  __m64 m64_u64; // mm1
  __m64 v4; // mm0
  __m64 v5; // mm2
  __m64 v6; // mm4
  __m64 v7; // mm5
  __m64 v8; // mm1
  __m64 v9; // mm3
  __m64 v10; // mm5
  __m64 v11; // mm4
  __m64 v12; // mm5

  _m_femms();
  m64_u64 = (__m64)pArg2->m64_u64;
  v4 = _m_punpckldq(m64_u64, m64_u64);
  v5 = _mm_cvtsi32_si64(pArg2[1].m64_u32[0]);
  v6 = _m_punpckhdq(m64_u64, m64_u64);
  v7 = _m_punpckldq(v5, v5);
  v8 = _m_pfadd(_m_pfmul(v6, pArg3[2]), _m_pfmul(v7, pArg3[4]));
  v9 = _m_pfadd(_m_pfadd(_m_pfmul(v4, pArg3[1]), pArg3[7]), _m_pfadd(_m_pfmul(v6, pArg3[3]), _m_pfmul(v7, pArg3[5])));
  v10 = _m_punpckhdq(v9, v9);
  v11 = _m_pfrcp(v10);
  v12 = _m_pfrcpit2(_m_pfrcpit1(v10, v11), v11);
  pArg1->m64_u64 = (uint64_t)_m_pfmul(_m_pfadd(_m_pfadd(_m_pfmul(v4, (__m64)pArg3->m64_u64), pArg3[6]), v8), v12);
  pArg1[1].m64_i32[0] = _mm_cvtsi64_si32(_m_pfmul(v9, v12));
  _m_femms();
  return pArg1;
}



// ------------------------------------------------------------
// 0x691E8B sub_691E8B
// ------------------------------------------------------------
// 【L1】userpurge 多顶点变换流水线（编译器内联展开的批量变换，寄存器传参）【推断】
__m64 */*userpurge*/ sub_691E8B@<eax>(__m64 uArg1@<mm2>, __m64 uArg2@<mm3>, __m64 *pArg3, __m64 *pArg4, __m64 *pArg5)
{
  __m64 v5; // mm1
  __m64 v6; // mm2
  __m64 v7; // mm3
  __m64 v8; // mm0
  __m64 v9; // mm1
  __m64 v10; // mm2
  __m64 v11; // mm5
  __m64 v12; // mm3
  __m64 v13; // mm2
  __m64 v14; // mm7
  __m64 v15; // mm0
  __m64 v16; // mm3
  __m64 v17; // mm1
  __m64 m64_u64; // mm4
  __m64 v19; // mm2
  __m64 v20; // mm3
  __m64 v21; // mm0
  __m64 v22; // mm1
  __m64 v23; // mm2
  __m64 v24; // mm5
  __m64 v25; // mm3
  __m64 v26; // mm2
  __m64 v27; // mm7
  __m64 v28; // mm0
  __m64 v29; // mm3
  __m64 v30; // mm1
  __m64 v31; // mm4
  __m64 v32; // mm2
  __m64 v33; // mm3
  __m64 v34; // mm0
  __m64 v35; // mm1
  __m64 v36; // mm2
  __m64 v37; // mm5
  __m64 v38; // mm3
  __m64 v39; // mm2
  __m64 v40; // mm7
  __m64 v41; // mm0
  __m64 v42; // mm3
  __m64 v43; // mm1
  __m64 v44; // mm4
  __m64 v45; // mm2
  __m64 v46; // mm3
  __m64 v47; // mm0
  __m64 v48; // mm1
  __m64 v49; // mm2
  __m64 v50; // mm3
  __m64 v51; // mm7
  __m64 v52; // mm3

  v5 = pArg4[1];
  v6 = _m_punpckhdq(uArg1, (__m64)pArg4->m64_u64);
  v7 = _m_punpckhdq(uArg2, v5);
  v8 = _m_punpckldq((__m64)pArg4->m64_u64, (__m64)pArg4->m64_u64);
  v9 = _m_punpckldq(v5, v5);
  v10 = _m_punpckhdq(v6, v6);
  v11 = _m_pfmul(pArg5[2], v10);
  v12 = _m_punpckhdq(v7, v7);
  v13 = _m_pfadd(_m_pfadd(_m_pfmul(v10, pArg5[3]), _m_pfmul(v8, pArg5[1])), _m_pfmul(v9, pArg5[5]));
  v14 = _m_pfadd(_m_pfmul(pArg5[6], v12), _m_pfadd(_m_pfmul(pArg5[4], v9), _m_pfadd(v11, _m_pfmul((__m64)pArg5->m64_u64, v8))));
  v15 = pArg4[2];
  v16 = _m_pfadd(_m_pfmul(v12, pArg5[7]), v13);
  v17 = pArg4[3];
  pArg3->m64_u64 = (uint64_t)v14;
  m64_u64 = (__m64)pArg5->m64_u64;
  pArg3[1].m64_u64 = (uint64_t)v16;
  v19 = _m_punpckhdq(v13, v15);
  v20 = _m_punpckhdq(v16, v17);
  v21 = _m_punpckldq(v15, v15);
  v22 = _m_punpckldq(v17, v17);
  v23 = _m_punpckhdq(v19, v19);
  v24 = _m_pfmul(pArg5[2], v23);
  v25 = _m_punpckhdq(v20, v20);
  v26 = _m_pfadd(_m_pfadd(_m_pfmul(v23, pArg5[3]), _m_pfmul(v21, pArg5[1])), _m_pfmul(v22, pArg5[5]));
  v27 = _m_pfadd(_m_pfmul(pArg5[6], v25), _m_pfadd(_m_pfmul(pArg5[4], v22), _m_pfadd(v24, _m_pfmul(m64_u64, v21))));
  v28 = pArg4[4];
  v29 = _m_pfadd(_m_pfmul(v25, pArg5[7]), v26);
  v30 = pArg4[5];
  pArg3[2].m64_u64 = (uint64_t)v27;
  v31 = (__m64)pArg5->m64_u64;
  pArg3[3].m64_u64 = (uint64_t)v29;
  v32 = _m_punpckhdq(v26, v28);
  v33 = _m_punpckhdq(v29, v30);
  v34 = _m_punpckldq(v28, v28);
  v35 = _m_punpckldq(v30, v30);
  v36 = _m_punpckhdq(v32, v32);
  v37 = _m_pfmul(pArg5[2], v36);
  v38 = _m_punpckhdq(v33, v33);
  v39 = _m_pfadd(_m_pfadd(_m_pfmul(v36, pArg5[3]), _m_pfmul(v34, pArg5[1])), _m_pfmul(v35, pArg5[5]));
  v40 = _m_pfadd(_m_pfmul(pArg5[6], v38), _m_pfadd(_m_pfmul(pArg5[4], v35), _m_pfadd(v37, _m_pfmul(v31, v34))));
  v41 = pArg4[6];
  v42 = _m_pfadd(_m_pfmul(v38, pArg5[7]), v39);
  v43 = pArg4[7];
  pArg3[4].m64_u64 = (uint64_t)v40;
  v44 = (__m64)pArg5->m64_u64;
  pArg3[5].m64_u64 = (uint64_t)v42;
  v45 = _m_punpckhdq(v39, v41);
  v46 = _m_punpckhdq(v42, v43);
  v47 = _m_punpckldq(v41, v41);
  v48 = _m_punpckldq(v43, v43);
  v49 = _m_punpckhdq(v45, v45);
  v50 = _m_punpckhdq(v46, v46);
  v51 = _m_pfmul(pArg5[6], v50);
  v52 = _m_pfadd(
          _m_pfmul(v50, pArg5[7]),
          _m_pfadd(_m_pfadd(_m_pfmul(v49, pArg5[3]), _m_pfmul(v47, pArg5[1])), _m_pfmul(v48, pArg5[5])));
  pArg3[6].m64_u64 = (uint64_t)_m_pfadd(
                                      v51,
                                      _m_pfadd(_m_pfmul(pArg5[4], v48), _m_pfadd(_m_pfmul(pArg5[2], v49), _m_pfmul(v44, v47))));
  pArg3[7].m64_u64 = (uint64_t)v52;
  _m_femms();
  return pArg3;
}


// ------------------------------------------------------------
// 0x692052 sub_692052
// ------------------------------------------------------------
// 【L1】thunk → sub_692057（同体跳转）
// attributes: thunk
__m64 */*stdcall*/ sub_692052(__m64 *uArg1, __m64 *uArg2, __m64 *uArg3)
{
  return sub_691E00(uArg1, uArg2, uArg3);
}



// ------------------------------------------------------------
// 0x692057 sub_692057
// ------------------------------------------------------------
// 【L1】userpurge MMX 大混合体：多源像素/顶点混合流水线【推断，无自证串】
__m64 */*userpurge*/ sub_692057@<eax>(
        __m64 a1@<mm2>,
        __m64 a2@<mm3>,
        __m64 *a3,
        __m64 *a4,
        __m64 *a5,
        __m64 *a6,
        __m64 *a7,
        __m64 *a8)
{
  __m64 *v8; // esi
  __m64 v9; // mm2
  __m64 v10; // mm3
  __m64 v11; // mm1
  __m64 v13; // [esp+Ch] [ebp-40h] BYREF
  float v14; // [esp+14h] [ebp-38h]
  float v15; // [esp+18h] [ebp-34h]
  float v16; // [esp+1Ch] [ebp-30h]
  float v17; // [esp+20h] [ebp-2Ch]
  float v18; // [esp+24h] [ebp-28h]
  float v19; // [esp+28h] [ebp-24h]
  float v20; // [esp+2Ch] [ebp-20h]
  float v21; // [esp+30h] [ebp-1Ch]
  float v22; // [esp+34h] [ebp-18h]
  float v23; // [esp+38h] [ebp-14h]
  float v24; // [esp+3Ch] [ebp-10h]
  float v25; // [esp+40h] [ebp-Ch]
  float v26; // [esp+44h] [ebp-8h]
  float v27; // [esp+48h] [ebp-4h]

  v8 = &v13;
  switch ( (a6 != nullptr) | (2 * ((a7 != nullptr) | (2 * (a8 != nullptr)))) )
  {
    case 0:
      v26 = 0.0;
      v25 = 0.0;
      v24 = 0.0;
      v23 = 0.0;
      v21 = 0.0;
      v20 = 0.0;
      v19 = 0.0;
      v18 = 0.0;
      v16 = 0.0;
      v15 = 0.0;
      v14 = 0.0;
      v13.m64_f32[1] = 0.0;
      v27 = 1.0;
      v22 = 1.0;
      v17 = 1.0;
      v13.m64_f32[0] = 1.0;
      break;
    case 1:
      v8 = a6;
      break;
    case 2:
      v8 = a7;
      break;
    case 3:
      _m_femms();
      sub_691E8B(a1, a2, &v13, a7, a6);
      _m_femms();
      break;
    case 4:
      v8 = a8;
      break;
    case 5:
      _m_femms();
      sub_691E8B(a1, a2, &v13, a8, a6);
      _m_femms();
      break;
    case 6:
      _m_femms();
      sub_691E8B(a1, a2, &v13, a8, a7);
      _m_femms();
      break;
    case 7:
      _m_femms();
      sub_691E8B(a1, a2, &v13, a8, a7);
      sub_691E8B(v9, v10, &v13, &v13, a6);
      _m_femms();
      break;
    default:
      break;
  }
  sub_691E00(a3, a4, v8);
  if ( a5 != nullptr )
  {
    _m_femms();
    v11 = _m_pfadd(_m_pfmul(_mm_cvtsi32_si64(a3[1].m64_u32[0]), _m_pfsub(_m_punpckhdq(a5[2], a5[2]), a5[2])), a5[2]);
    a3->m64_u64 = (uint64_t)_m_pfadd(
                                      _m_pfmul(
                                        _m_pfadd(
                                          _m_pxor((__m64)a3->m64_u64, (__m64)0x8000000000000000uLL),
                                          (__m64)0x3F8000003F800000LL),
                                        _m_pfmul(_m_pi2fd(a5[1]), (__m64)0x3F0000003F000000LL)),
                                      _m_pi2fd((__m64)a5->m64_u64));
    a3[1].m64_i32[0] = _mm_cvtsi64_si32(v11);
    _m_femms();
  }
  return a3;
}



// ------------------------------------------------------------
// 0x6921DF sub_6921DF
// ------------------------------------------------------------
// 【L1】userpurge MMX 大混合体变体【推断】
__m64 */*userpurge*/ sub_6921DF@<eax>(
        __m64 a1@<mm2>,
        __m64 a2@<mm3>,
        __m64 *a3,
        __m64 *a4,
        __m64 *a5,
        __m64 *a6,
        __m64 *a7,
        __m64 *a8)
{
  __m64 v8; // mm2
  __m64 v9; // mm3
  __m64 v10; // mm4
  __m64 v11; // mm2
  __m64 v12; // mm5
  __m64 v13; // mm0
  __m64 v14; // mm5
  __m64 v15; // mm6
  __m64 v16; // mm3
  __m64 v18; // [esp+Ch] [ebp-40h] BYREF
  float v19; // [esp+14h] [ebp-38h]
  float v20; // [esp+18h] [ebp-34h]
  float v21; // [esp+1Ch] [ebp-30h]
  float v22; // [esp+20h] [ebp-2Ch]
  float v23; // [esp+24h] [ebp-28h]
  float v24; // [esp+28h] [ebp-24h]
  float v25; // [esp+2Ch] [ebp-20h]
  float v26; // [esp+30h] [ebp-1Ch]
  float v27; // [esp+34h] [ebp-18h]
  float v28; // [esp+38h] [ebp-14h]
  float v29; // [esp+3Ch] [ebp-10h]
  float v30; // [esp+40h] [ebp-Ch]
  float v31; // [esp+44h] [ebp-8h]
  float v32; // [esp+48h] [ebp-4h]

  switch ( (a6 != nullptr) | (2 * ((a7 != nullptr) | (2 * (a8 != nullptr)))) )
  {
    case 0:
      v31 = 0.0;
      v30 = 0.0;
      v29 = 0.0;
      v28 = 0.0;
      v26 = 0.0;
      v25 = 0.0;
      v24 = 0.0;
      v23 = 0.0;
      v21 = 0.0;
      v20 = 0.0;
      v19 = 0.0;
      v18.m64_f32[1] = 0.0;
      v32 = 1.0;
      v27 = 1.0;
      v22 = 1.0;
      v18.m64_f32[0] = 1.0;
      break;
    case 1:
      _m_femms();
      sub_69174A(&v18, nullptr, a6);
      _m_femms();
      break;
    case 2:
      _m_femms();
      sub_69174A(&v18, nullptr, a7);
      _m_femms();
      break;
    case 3:
      _m_femms();
      sub_691E8B(a1, a2, &v18, a7, a6);
      sub_69174A(&v18, nullptr, &v18);
      _m_femms();
      break;
    case 4:
      _m_femms();
      sub_69174A(&v18, nullptr, a8);
      _m_femms();
      break;
    case 5:
      _m_femms();
      sub_691E8B(a1, a2, &v18, a8, a6);
      sub_69174A(&v18, nullptr, &v18);
      _m_femms();
      break;
    case 6:
      _m_femms();
      sub_691E8B(a1, a2, &v18, a8, a7);
      sub_69174A(&v18, nullptr, &v18);
      _m_femms();
      break;
    case 7:
      _m_femms();
      sub_691E8B(a1, a2, &v18, a8, a7);
      sub_691E8B(v8, v9, &v18, &v18, a6);
      sub_69174A(&v18, nullptr, &v18);
      _m_femms();
      break;
    default:
      break;
  }
  if ( a5 != nullptr )
  {
    _m_femms();
    v10 = a5[2];
    v11 = _m_pi2fd(a5[1]);
    v12 = _m_punpckldq(_m_pfrcp(v11), _m_pfrcp(_m_punpckhdq(v11, v11)));
    v13 = _m_pfmul(
            _m_pfsub((__m64)a4->m64_u64, _m_pi2fd((__m64)a5->m64_u64)),
            _m_pfmul(_m_pfrcpit2(_m_pfrcpit1(v11, v12), v12), (__m64)0x4000000040000000LL));
    v14 = _m_pfsub(_m_punpckhdq(v10, v10), v10);
    v15 = _m_pfrcp(v14);
    v16 = _m_pfmul(_m_pfsub(_mm_cvtsi32_si64(a4[1].m64_u32[0]), v10), _m_pfrcpit2(_m_pfrcpit1(v14, v15), v15));
    a3->m64_u64 = (uint64_t)_m_pxor(_m_pfsub(v13, (__m64)0x3F8000003F800000LL), (__m64)0x8000000000000000uLL);
    a3[1].m64_i32[0] = _mm_cvtsi64_si32(v16);
    _m_femms();
    sub_691E00(a3, a3, &v18);
  }
  else
  {
    sub_691E00(a3, a4, &v18);
  }
  return a3;
}


// ------------------------------------------------------------
// 0x692405 sub_692405
// ------------------------------------------------------------
// 【L1】userpurge MMX 大混合体变体（最长 ~1.4KB）【推断】
__m64 */*userpurge*/ sub_692405@<eax>(
        __m64 a1@<mm2>,
        __m64 a2@<mm3>,
        __m64 *a3,
        __m64 *a4,
        __m64 *a5,
        __m64 *a6,
        __m64 *a7,
        __m64 *a8)
{
  __m64 v8; // mm2
  __m64 v9; // mm3
  __m64 v10; // mm4
  __m64 v11; // mm2
  __m64 v12; // mm5
  __m64 v13; // mm0
  __m64 v14; // mm5
  __m64 v15; // mm6
  __m64 v16; // mm3
  __m64 *v18; // [esp-4h] [ebp-50h]
  __m64 v19[8]; // [esp+Ch] [ebp-40h] BYREF

  switch ( (a6 != nullptr) | (2 * ((a7 != nullptr) | (2 * (a8 != nullptr)))) )
  {
    case 0:
      sub_68E3D2(v19);
      break;
    case 1:
      sub_691070(v19, nullptr, a6);
      break;
    case 2:
      sub_691070(v19, nullptr, a7);
      break;
    case 3:
      sub_691E8B(a1, a2, v19, a7, a6);
      goto LABEL_11;
    case 4:
      sub_691070(v19, nullptr, a8);
      break;
    case 5:
      v18 = a6;
      goto LABEL_9;
    case 6:
      v18 = a7;
LABEL_9:
      sub_691E8B(a1, a2, v19, a8, v18);
      goto LABEL_11;
    case 7:
      sub_691E8B(a1, a2, v19, a8, a7);
      sub_691E8B(v8, v9, v19, v19, a6);
LABEL_11:
      sub_691070(v19, nullptr, v19);
      break;
    default:
      break;
  }
  if ( a5 != nullptr )
  {
    _m_femms();
    v10 = a5[2];
    v11 = _m_pi2fd(a5[1]);
    v12 = _m_punpckldq(_m_pfrcp(v11), _m_pfrcp(_m_punpckhdq(v11, v11)));
    v13 = _m_pfmul(
            _m_pfsub((__m64)a4->m64_u64, _m_pi2fd((__m64)a5->m64_u64)),
            _m_pfmul(_m_pfrcpit2(_m_pfrcpit1(v11, v12), v12), (__m64)0x4000000040000000LL));
    v14 = _m_pfsub(_m_punpckhdq(v10, v10), v10);
    v15 = _m_pfrcp(v14);
    v16 = _m_pfmul(_m_pfsub(_mm_cvtsi32_si64(a4[1].m64_u32[0]), v10), _m_pfrcpit2(_m_pfrcpit1(v14, v15), v15));
    a3->m64_u64 = (uint64_t)_m_pxor(_m_pfsub(v13, (__m64)0x3F8000003F800000LL), (__m64)0x8000000000000000uLL);
    a3[1].m64_i32[0] = _mm_cvtsi64_si32(v16);
    _m_femms();
    sub_691E00(a3, a3, v19);
  }
  else
  {
    sub_691E00(a3, a4, v19);
  }
  return a3;
}



// ------------------------------------------------------------
// 0x6928FA sub_6928FA
// ------------------------------------------------------------
// 【L1】3DNow! vec2 叉积/旋转组合（_m_pfacc 半和半差指令）
__m64 */*stdcall*/ sub_6928FA(__m64 *pArg1, __m64 *pArg2, __m64 *pArg3, __m64 *pArg4)
{
  __m64 v5; // mm2
  __m64 v6; // mm3
  __m64 v7; // mm4
  __m64 v8; // mm5
  __m64 v9; // mm6
  __m64 v10; // mm1
  __m64 m64_u64; // mm0
  __m64 v12; // mm7
  __m64 v13; // mm2
  __m64 v14; // mm6
  __m64 v15; // mm7

  _m_femms();
  v5 = pArg3[1];
  v6 = pArg4[1];
  v7 = _m_pfsub(
         _m_pfmul(_m_punpckhdq(v6, v6), _m_punpckhdq(_m_punpckldq(v5, v5), (__m64)pArg3->m64_u64)),
         _m_pfmul(_m_punpckhdq(v5, v5), _m_punpckhdq(_m_punpckldq(v6, v6), (__m64)pArg4->m64_u64)));
  v8 = _m_pfsub(
         _m_pfmul(_m_punpckhdq((__m64)pArg3->m64_u64, v5), _m_punpckldq(v6, (__m64)pArg4->m64_u64)),
         _m_pfmul(_m_punpckhdq((__m64)pArg4->m64_u64, v6), _m_punpckldq(v5, (__m64)pArg3->m64_u64)));
  v9 = _m_pfsub(
         _m_pfmul(
           _m_punpckldq((__m64)pArg4->m64_u64, (__m64)pArg4->m64_u64),
           _m_punpckhdq(_m_punpckldq(v5, v5), (__m64)pArg3->m64_u64)),
         _m_pfmul(
           _m_punpckldq((__m64)pArg3->m64_u64, (__m64)pArg3->m64_u64),
           _m_punpckhdq(_m_punpckldq(v6, v6), (__m64)pArg4->m64_u64)));
  v10 = pArg2[1];
  m64_u64 = (__m64)pArg2->m64_u64;
  pArg1->m64_u64 = (uint64_t)_m_pfsub(
                                    _m_pfmul(
                                      _m_pxor(_m_punpckldq(v7, v7), (__m64)0x8000000000000000uLL),
                                      _m_punpckhdq(
                                        (__m64)pArg2->m64_u64,
                                        _m_punpckldq((__m64)pArg2->m64_u64, (__m64)pArg2->m64_u64))),
                                    _m_pfacc(
                                      _m_pxor(
                                        _m_pfmul(_m_punpckldq(_m_punpckhdq(v7, v7), v8), v10),
                                        (__m64)0x8000000000000000uLL),
                                      _m_pxor(
                                        _m_pfmul(_m_punpckldq(_m_punpckhdq(v8, v8), v9), v10),
                                        (__m64)0x8000000000000000uLL)));
  v12 = _m_psrlqi((__m64)0x8000000000000000uLL, 0x20u);
  v13 = _m_pxor(_m_punpckldq(v8, v9), v12);
  v14 = _m_pxor(_m_punpckhdq(v9, v9), v12);
  v15 = _m_psllqi(v12, 0x20u);
  pArg1[1].m64_u64 = (uint64_t)_m_pfadd(
                                      _m_pfmul(_m_punpckhdq(v10, _m_punpckldq(v10, v10)), v14),
                                      _m_pfacc(
                                        _m_pxor(
                                          _m_pfmul(_m_pxor(_m_punpckhdq(v7, v8), (__m64)0x8000000000000000uLL), m64_u64),
                                          v15),
                                        _m_pxor(_m_pfmul(v13, m64_u64), v15)));
  _m_femms();
  return pArg1;
}



// ------------------------------------------------------------
// 0x692A2C sub_692A2C
// ------------------------------------------------------------
// 【L1】3DNow! 双线性插值 (1-u-v)A + uB + vC（a5/a6 = u/v 定点输入）
__m64 */*stdcall*/ sub_692A2C(__m64 *pArg1, __m64 *pArg2, __m64 *pArg3, __m64 *pArg4, unsigned int uArg5, unsigned int uArg6)
{
  __m64 v6; // mm6
  __m64 v7; // mm7
  __m64 v9; // mm6
  __m64 v10; // mm7
  __m64 v11; // mm1

  v6 = _mm_cvtsi32_si64(uArg5);
  v7 = _mm_cvtsi32_si64(uArg6);
  v9 = _m_punpckldq(v6, v6);
  v10 = _m_punpckldq(v7, v7);
  v11 = _m_pfadd(_m_pfadd(_m_pfmul(_m_pfsub(pArg3[1], pArg2[1]), v9), pArg2[1]), _m_pfmul(_m_pfsub(pArg4[1], pArg2[1]), v10));
  pArg1->m64_u64 = (uint64_t)_m_pfadd(
                                    _m_pfadd(
                                      _m_pfmul(_m_pfsub((__m64)pArg3->m64_u64, (__m64)pArg2->m64_u64), v9),
                                      (__m64)pArg2->m64_u64),
                                    _m_pfmul(_m_pfsub((__m64)pArg4->m64_u64, (__m64)pArg2->m64_u64), v10));
  pArg1[1].m64_u64 = (uint64_t)v11;
  _m_femms();
  return pArg1;
}



// ------------------------------------------------------------
// 0x692A9D sub_692A9D
// ------------------------------------------------------------
// 【L1】3DNow! 三次插值：t^3-2t^2 基函数（0x40400000=3.0f 系数直证 Hermite/Bezier）
__m64 */*stdcall*/ sub_692A9D(__m64 *pArg1, __m64 *pArg2, __m64 *pArg3, __m64 *pArg4, __m64 *pArg5, unsigned int uArg6)
{
  __m64 v6; // mm0
  __m64 v7; // mm1
  __m64 v8; // mm2
  __m64 v9; // mm7
  __m64 v10; // mm4
  __m64 v11; // mm6
  __m64 v12; // mm2
  __m64 v13; // mm5
  __m64 v14; // mm1
  __m64 v15; // mm6
  __m64 v16; // mm2
  __m64 v17; // mm5
  __m64 v18; // mm0
  __m64 v19; // mm1
  __m64 v21; // mm4
  __m64 v22; // mm3
  __m64 v23; // mm0

  _m_femms();
  v6 = _mm_cvtsi32_si64(uArg6);
  v7 = _m_pfmul(v6, v6);
  v8 = _m_pfmul(v7, v6);
  v9 = _m_pfsub(v8, v7);
  v10 = _m_pfmul(v7, (__m64)0x4000000040000000LL);
  v11 = v8;
  v12 = _m_pfmul(v8, (__m64)0x4000000040000000LL);
  v13 = _m_pfmul(v7, (__m64)0x4040000040400000LL);
  v14 = _m_pfsub(v13, v12);
  v15 = _m_pfadd(_m_pfsub(v11, v10), v6);
  v16 = _m_pfadd(_m_pfsub(v12, v13), (__m64)0x3F8000003F800000LL);
  v17 = _m_punpckldq(v9, v9);
  v18 = _m_punpckldq(v14, v14);
  v19 = _m_pfmul(v18, (__m64)pArg4->m64_u64);
  v21 = _m_punpckldq(v15, v15);
  v22 = _m_punpckldq(v16, v16);
  v23 = _m_pfadd(
          _m_pfadd(_m_pfmul(v18, pArg4[1]), _m_pfmul(v17, pArg5[1])),
          _m_pfadd(_m_pfmul(v22, pArg2[1]), _m_pfmul(v21, pArg3[1])));
  pArg1->m64_u64 = (uint64_t)_m_pfadd(
                                    _m_pfadd(v19, _m_pfmul(v17, (__m64)pArg5->m64_u64)),
                                    _m_pfadd(_m_pfmul(v22, (__m64)pArg2->m64_u64), _m_pfmul(v21, (__m64)pArg3->m64_u64)));
  pArg1[1].m64_u64 = (uint64_t)v23;
  _m_femms();
  return pArg1;
}



// ------------------------------------------------------------
// 0x692B65 sub_692B65
// ------------------------------------------------------------
// 【L1】3DNow! 三控制点插值变体（u^2/u^3 基展开）
__m64 */*stdcall*/ sub_692B65(__m64 *pArg1, __m64 *pArg2, __m64 *pArg3, __m64 *pArg4, __m64 *pArg5, unsigned int uArg6)
{
  __m64 v6; // mm1
  __m64 v7; // mm0
  __m64 v8; // mm1
  __m64 v9; // mm0
  __m64 v10; // mm3
  __m64 v11; // mm1
  __m64 v12; // mm0
  __m64 v13; // mm5
  __m64 v14; // mm0
  __m64 v15; // mm2
  __m64 v16; // mm3
  __m64 v17; // mm4
  __m64 v18; // mm5
  __m64 v19; // mm6
  __m64 v20; // mm7
  __m64 v22; // mm0
  __m64 v23; // mm4

  v6 = _mm_cvtsi32_si64(uArg6);
  v7 = _m_punpckldq(v6, v6);
  v8 = _m_punpckldq(v6, (__m64)1065353216LL);
  v9 = _m_pfmul(_m_pfmul(v7, v7), v8);
  v10 = v8;
  v11 = _m_pfmul(v8, v8);
  v12 = _m_pfsub(v9, v11);
  v13 = _m_pfmul(v12, (__m64)0x4000000040400000LL);
  v14 = _m_punpckldq(v13, v12);
  v15 = _m_pfsub(_m_pfadd(_m_punpckldq(v11, v11), _m_pxor(_m_punpckldq(v10, v10), (__m64)0x8000000000000000uLL)), v14);
  v16 = _m_pfsub(v14, _m_punpckhdq(v13, 0));
  v17 = _m_punpckhdq(v15, v15);
  v18 = _m_punpckldq(v16, v16);
  v19 = _m_punpckldq(v15, v15);
  v20 = _m_punpckhdq(v16, v16);
  v22 = _m_pfadd(
          _m_pfadd(_m_pfmul(v18, (__m64)pArg3->m64_u64), _m_pfmul(v17, (__m64)pArg2->m64_u64)),
          _m_pfmul(v19, (__m64)pArg4->m64_u64));
  v23 = _m_pfadd(
          _m_pfadd(_m_pfadd(_m_pfmul(v17, pArg2[1]), _m_pfmul(v18, pArg3[1])), _m_pfmul(v19, pArg4[1])),
          _m_pfmul(v20, pArg5[1]));
  pArg1->m64_u64 = (uint64_t)_m_pfmul(
                                    _m_pfadd(v22, _m_pfmul(v20, (__m64)pArg5->m64_u64)),
                                    (__m64)0x3F0000003F000000LL);
  pArg1[1].m64_u64 = (uint64_t)_m_pfmul(v23, (__m64)0x3F0000003F000000LL);
  _m_femms();
  return pArg1;
}



// ------------------------------------------------------------
// 0x692E28 sub_692E28
// ------------------------------------------------------------
// 【L1】3DNow! vec2 线性变换（含 _m_pswapd 转置乘）
__m64 */*stdcall*/ sub_692E28(__m64 *pArg1, __m64 *pArg2)
{
  __m64 v2; // mm3
  __m64 v3; // mm2
  __m64 v4; // mm0
  __m64 v5; // mm0
  __m64 v6; // mm4
  __m64 v7; // mm5
  __m64 v9; // mm0

  v2 = pArg2[1];
  v3 = _m_pand(v2, (__m64)0xFFFFFFFFLL);
  v4 = _m_pfadd(_m_pfmul((__m64)pArg2->m64_u64, (__m64)pArg2->m64_u64), _m_pfmul(v3, v3));
  v5 = _m_pfacc(v4, v4);
  v6 = _m_pfrsqrt(v5);
  v7 = _m_pfcmpgt(v5, (__m64)0x80000000800000LL);
  v9 = _m_pfrcpit2(_m_pfrsqit1(v5, _m_pfmul(v6, v6)), v6);
  pArg1->m64_u64 = (uint64_t)_m_pfmul(_m_pand((__m64)pArg2->m64_u64, v7), v9);
  pArg1[1].m64_u64 = (uint64_t)_m_pfmul(_m_pand(v2, v7), v9);
  _m_femms();
  return pArg1;
}



// ------------------------------------------------------------
// 0x692E8C sub_692E8C
// ------------------------------------------------------------
// 【L1】3DNow! vec2 变换 + 倒数（_m_pfrcp）
__m64 */*stdcall*/ sub_692E8C(__m64 *pArg1, __m64 *pArg2, __m64 *pArg3)
{
  __m64 m64_u64; // mm1
  __m64 v4; // mm0
  __m64 v5; // mm3
  __m64 v6; // mm5
  __m64 v7; // mm6
  __m64 v8; // mm7
  __m64 v10; // mm4

  _m_femms();
  m64_u64 = (__m64)pArg2->m64_u64;
  v4 = _m_punpckldq(m64_u64, m64_u64);
  v5 = pArg2[1];
  v6 = _m_punpckhdq(m64_u64, m64_u64);
  v7 = _m_punpckldq(v5, v5);
  v8 = _m_punpckhdq(v5, v5);
  v10 = _m_pfadd(_m_pfadd(_m_pfmul(v4, pArg3[1]), _m_pfmul(v6, pArg3[3])), _m_pfadd(_m_pfmul(v7, pArg3[5]), _m_pfmul(v8, pArg3[7])));
  pArg1->m64_u64 = (uint64_t)_m_pfadd(
                                    _m_pfadd(_m_pfmul(v4, (__m64)pArg3->m64_u64), _m_pfmul(v6, pArg3[2])),
                                    _m_pfadd(_m_pfmul(v7, pArg3[4]), _m_pfmul(v8, pArg3[6])));
  pArg1[1].m64_u64 = (uint64_t)v10;
  _m_femms();
  return pArg1;
}



// ------------------------------------------------------------
// 0x692F0A sub_692F0A
// ------------------------------------------------------------
// 【L1】float[16] 序列 min/max 归一化（调色板动态范围统计）【推断】
float */*usercall*/ sub_692F0A@<eax>(float *result@<eax>, unsigned int uArg2@<ecx>)
{
  *result = (double)((uint16_t)uArg2 >> 11) * 0.032258064;
  result[1] = (double)((uArg2 >> 5) & 0x3F) * 0.015873017;
  result[2] = (double)(uArg2 & 0x1F) * 0.032258064;
  result[3] = 1.0;
  return result;
}



// ------------------------------------------------------------
// 0x692F56 sub_692F56
// ------------------------------------------------------------
// 【L1】fastcall float 数组范围统计（min/max 输出）【推断】
int /*fastcall*/ sub_692F56(float *pArg1)
{
  int i; // edx
  double v2; // st7
  double v3; // st7
  double v4; // st6
  double v5; // st6

  for ( i = 16; i != 0; --i )
  {
    if ( 0.0 == pArg1[3] )
    {
      *pArg1 = 0.0;
      pArg1[1] = 0.0;
      v2 = 0.0;
    }
    else
    {
      if ( pArg1[3] >= 1.0 )
        goto LABEL_15;
      v3 = 1.0 / pArg1[3];
      if ( *pArg1 >= (double)pArg1[3] )
        v4 = 1.0;
      else
        v4 = v3 * *pArg1;
      *pArg1 = v4;
      if ( pArg1[1] >= (double)pArg1[3] )
        v5 = 1.0;
      else
        v5 = v3 * pArg1[1];
      pArg1[1] = v5;
      if ( pArg1[2] >= (double)pArg1[3] )
        v2 = 1.0;
      else
        v2 = v3 * pArg1[2];
    }
    pArg1[2] = v2;
LABEL_15:
    pArg1 += 4;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x692FD4 sub_692FD4
// ------------------------------------------------------------
// 【L1】usercall 双 float 数组范围统计变体【推断】
int /*usercall*/ sub_692FD4@<eax>(float *pArg1@<eax>, float *pArg2@<ecx>)
{
  int v2; // edx
  double v3; // st7

  v2 = 16;
  do
  {
    v3 = pArg1[3] * *pArg1;
    pArg1 += 4;
    *pArg2 = v3;
    pArg2 += 4;
    --v2;
    *(pArg2 - 3) = *(pArg1 - 3) * *(pArg1 - 1);
    *(pArg2 - 2) = *(pArg1 - 2) * *(pArg1 - 1);
    *(pArg2 - 1) = *(pArg1 - 1);
  }
  while ( v2 != 0 );
  return 0;
}



// ------------------------------------------------------------
// 0x693004 sub_693004
// ------------------------------------------------------------
// 【L1】Gamma/RAMP 重建辅助（693121 调用前的表初始化）【推断】
int sub_693004()
{
  int v1; // [esp+0h] [ebp-8h]

  dword_9D3760 = v1;
  return v1;
}



// ------------------------------------------------------------
// 0x693027 sub_693027
// ------------------------------------------------------------
// 【L1】thiscall 颜色表对象方法（返回表指针）【推断】
int /*thiscall*/ sub_693027(float *this)
{
  double v1; // st6
  double v2; // st6
  double v3; // st7
  int v4; // ecx
  float v6; // [esp+0h] [ebp-18h]
  float fld_e1; // [esp+4h] [ebp-14h]
  float fld_e2; // [esp+8h] [ebp-10h]
  float v9; // [esp+10h] [ebp-8h]
  float v10; // [esp+10h] [ebp-8h]
  float v11; // [esp+14h] [ebp-4h]

  if ( *this < 0.0 )
  {
    v1 = 0.0;
LABEL_3:
    v6 = v1;
    goto LABEL_7;
  }
  if ( *this > 1.0 )
  {
    v1 = 1.0;
    goto LABEL_3;
  }
  v6 = *this;
LABEL_7:
  if ( *(this + 1) < 0.0 )
  {
    v2 = 0.0;
LABEL_9:
    fld_e1 = v2;
    goto LABEL_13;
  }
  if ( *(this + 1) > 1.0 )
  {
    v2 = 1.0;
    goto LABEL_9;
  }
  fld_e1 = *(this + 1);
LABEL_13:
  if ( *(this + 2) >= 0.0 )
  {
    if ( *(this + 2) <= 1.0 )
    {
      fld_e2 = *(this + 2);
      goto LABEL_19;
    }
    v3 = 1.0;
  }
  else
  {
    v3 = 0.0;
  }
  fld_e2 = v3;
LABEL_19:
  sub_693004();
  v11 = v6 * 31.0 + 0.5;
  v9 = fld_e1 * 63.0 + 0.5;
  v4 = (int)v9;
  v10 = fld_e2 * 31.0 + 0.5;
  return (int)v10 | (32 * (v4 | ((int)v11 << 6)));
}



// ------------------------------------------------------------
// 0x693121 sub_693121
// ------------------------------------------------------------
// 【L1】Gamma/RAMP 重建：16 槽浮点表 min/max → 8 段索引重映射（a4=6/8 两种格式）
float */*cdecl*/ sub_693121(float *pArg1, float *pArg2, int pArg3, unsigned int uArg4)
{
  unsigned int uArg42; // esi
  float *v5; // ebx
  unsigned int v6; // edx
  float *v7; // ecx
  float *v8; // ecx
  double v9; // st7
  int v10; // edx
  float *v11; // eax
  unsigned int v12; // edx
  float *v13; // ecx
  double v14; // st7
  unsigned int v15; // eax
  unsigned int v16; // eax
  double v17; // st7
  double v18; // st6
  float *v19; // eax
  float v20; // eax
  double v21; // st7
  double v22; // st7
  float v24[8]; // [esp+Ch] [ebp-50h] BYREF
  int v25; // [esp+2Ch] [ebp-30h]
  float v26; // [esp+30h] [ebp-2Ch]
  float v27; // [esp+34h] [ebp-28h]
  float v28; // [esp+38h] [ebp-24h]
  unsigned int i; // [esp+3Ch] [ebp-20h]
  uint8_t *v30; // [esp+40h] [ebp-1Ch]
  float v31; // [esp+44h] [ebp-18h]
  float v32; // [esp+48h] [ebp-14h]
  float v33; // [esp+4Ch] [ebp-10h]
  float v34; // [esp+50h] [ebp-Ch]
  float v35; // [esp+54h] [ebp-8h]
  float v36; // [esp+58h] [ebp-4h]

  uArg42 = uArg4;
  if ( uArg4 == 6 )
  {
    v5 = (float *)&unk_748B74;
    v30 = &unk_748B5C;
  }
  else
  {
    v5 = (float *)&unk_748B3C;
    v30 = &unk_748B1C;
  }
  v6 = 0;
  v36 = 1.0;
  v35 = 0.0;
  if ( uArg4 == 8 )
  {
    do
    {
      v7 = (float *)(pArg3 + 4 * v6);
      if ( *v7 < (double)v36 )
        v36 = *v7;
      if ( *v7 > (double)v35 )
        v35 = *v7;
      ++v6;
    }
    while ( v6 < 0x10 );
  }
  else
  {
    do
    {
      v8 = (float *)(pArg3 + 4 * v6);
      if ( *v8 < (double)v36 && *v8 > 0.0 )
        v36 = *v8;
      if ( *v8 > (double)v35 && *v8 < 1.0 )
        v35 = *v8;
      ++v6;
    }
    while ( v6 < 0x10 );
  }
  v25 = uArg4 - 1;
  v28 = (float)(uArg4 - 1);
  sub_693004();
  for ( i = 0; i < 8; ++i )
  {
    v9 = v35 - v36;
    if ( v9 < 0.00390625 )
      break;
    v27 = v28 / v9;
    if ( uArg42 != 0 )
    {
      v10 = v30 - (uint8_t *)v5;
      v11 = v5;
      do
      {
        *(float *)((char *)v11 + (char *)v24 - (char *)v5) = v35 * *(float *)((char *)v11 + v10) + v36 * *v11;
        ++v11;
        --uArg42;
      }
      while ( uArg42 != 0 );
      uArg42 = uArg4;
    }
    if ( uArg42 == 6 )
    {
      v24[6] = 0.0;
      v24[7] = 1.0;
    }
    v12 = 0;
    v34 = 0.0;
    v33 = 0.0;
    v32 = 0.0;
    v31 = 0.0;
    do
    {
      v13 = (float *)(pArg3 + 4 * v12);
      v14 = (*v13 - v36) * v27;
      if ( v14 > 0.0 )
      {
        if ( v14 < v28 )
        {
          v26 = v14 + 0.5;
          v25 = (int)v26;
          v15 = v25;
        }
        else
        {
          if ( uArg42 == 6 && (v35 + 1.0) * 0.5 <= *v13 )
            goto LABEL_38;
          v15 = uArg4 - 1;
        }
      }
      else
      {
        if ( uArg42 == 6 && v36 * 0.5 >= *v13 )
          goto LABEL_38;
        v15 = 0;
      }
      if ( v15 < uArg42 )
      {
        v16 = v15;
        v17 = *v13 - v24[v16];
        v34 = v17 * v5[v16] + v34;
        v18 = v5[v16];
        v19 = (float *)&v30[v16 * 4];
        v32 = v18 * v18 + v32;
        v33 = v17 * *v19 + v33;
        v31 = *v19 * *v19 + v31;
      }
LABEL_38:
      ++v12;
    }
    while ( v12 < 0x10 );
    if ( v32 > 0.0 )
      v36 = v36 - v34 / v32;
    if ( v31 > 0.0 )
      v35 = v35 - v33 / v31;
    if ( v36 > (double)v35 )
    {
      v20 = v35;
      v35 = v36;
      v36 = v20;
    }
    if ( v34 * v34 < 0.015625 && v33 * v33 < 0.015625 )
      break;
  }
  if ( v36 >= 0.0 )
  {
    if ( v36 <= 1.0 )
      v21 = v36;
    else
      v21 = 1.0;
  }
  else
  {
    v21 = 0.0;
  }
  *pArg1 = v21;
  if ( v35 >= 0.0 )
  {
    if ( v35 <= 1.0 )
      v22 = v35;
    else
      v22 = 1.0;
  }
  else
  {
    v22 = 0.0;
  }
  *pArg2 = v22;
  return pArg2;
}


// ------------------------------------------------------------
// 0x693426 sub_693426
// ------------------------------------------------------------
// 【L1】Gamma/RAMP 重建变体（整数索引路径，与 693121 成对）
float */*cdecl*/ sub_693426(float *pArg1, float *pArg2, int pArg3, int nArg4)
{
  double v4; // st7
  float *v5; // ecx
  int i; // edx
  double v7; // st6
  double v8; // st5
  uint8_t v10; // c0
  uint8_t v11; // c2
  float *result; // eax
  float v13; // ecx
  float *v14; // eax
  double v15; // st5
  int v16; // ecx
  double v17; // st6
  double v18; // st5
  double v19; // st5
  double v20; // st3
  double v21; // st3
  double v22; // st4
  char v23; // bl
  unsigned int j; // edx
  float *v25; // ecx
  float v26; // eax
  float v27; // eax
  double v29; // st7
  float *v30; // eax
  float *v31; // ecx
  int v32; // edx
  int k; // esi
  double v34; // st6
  double v35; // st5
  double v36; // st6
  double v37; // st5
  double v38; // st4
  double v39; // st4
  float *v40; // ecx
  int v41; // esi
  double v42; // st6
  int v43; // edx
  double v44; // st6
  double v45; // st5
  int v46; // eax
  float *v47; // edx
  double v48; // st4
  float *v49; // eax
  double v50; // st4
  double v51; // st3
  double v52; // st6
  double v53; // st6
  float v55[15]; // [esp+4h] [ebp-54h] BYREF
  float *v56; // [esp+40h] [ebp-18h]
  int v57; // [esp+44h] [ebp-14h]
  float v58; // [esp+48h] [ebp-10h]
  float v59; // [esp+4Ch] [ebp-Ch]
  float v60; // [esp+50h] [ebp-8h]
  float *v61; // [esp+58h] [ebp+0h]
  uint8_t *v62; // [esp+5Ch] [ebp+4h]
  float v63; // [esp+60h] [ebp+8h]
  float v64; // [esp+64h] [ebp+Ch]
  float v65; // [esp+68h] [ebp+10h]
  float v66; // [esp+6Ch] [ebp+14h]
  float v67; // [esp+70h] [ebp+18h]
  float v68; // [esp+74h] [ebp+1Ch]
  float v69; // [esp+7Ch] [ebp+24h]
  float v70; // [esp+80h] [ebp+28h]
  float v71; // [esp+84h] [ebp+2Ch]
  float v72; // [esp+88h] [ebp+30h]
  float v73; // [esp+90h] [ebp+38h] BYREF
  float v74; // [esp+94h] [ebp+3Ch]
  float v75; // [esp+98h] [ebp+40h]
  float v76; // [esp+9Ch] [ebp+44h]
  float v77; // [esp+A0h] [ebp+48h]
  float v78; // [esp+A4h] [ebp+4Ch]
  float v79; // [esp+A8h] [ebp+50h]
  float v80; // [esp+B0h] [ebp+58h]
  float v81; // [esp+B4h] [ebp+5Ch]
  float v82; // [esp+B8h] [ebp+60h]
  int unk_79A5EC2; // [esp+BCh] [ebp+64h]
  float v84; // [esp+D4h] [ebp+7Ch]

  if ( nArg4 == 3 )
  {
    v61 = (float *)&unk_748BC0;
    v62 = &unk_748BB4;
  }
  else
  {
    v61 = (float *)&unk_748BA4;
    v62 = &unk_748B94;
  }
  v77 = 0.0;
  v4 = 0.0;
  v78 = 0.0;
  v80 = flt_79A5E0;
  v81 = flt_79A5E4;
  v79 = 0.0;
  v82 = flt_79A5E8;
  unk_79A5EC2 = unk_79A5EC;
  v56 = (float *)(pArg3 + 8);
  v5 = (float *)(pArg3 + 8);
  for ( i = 16; i != 0; --i )
  {
    if ( *(v5 - 2) < (double)v80 )
      v80 = *(v5 - 2);
    if ( *(v5 - 1) < (double)v81 )
      v81 = *(v5 - 1);
    if ( *v5 < (double)v82 )
      v82 = *v5;
    if ( *(v5 - 2) > (double)v77 )
      v77 = *(v5 - 2);
    if ( v4 < *(v5 - 1) )
      v4 = *(v5 - 1);
    if ( *v5 > (double)v79 )
      v79 = *v5;
    v5 += 4;
  }
  v78 = v4;
  v70 = v77 - v80;
  v71 = v4 - v81;
  v7 = v79 - v82;
  v8 = v7 * v7 + v71 * v71 + v70 * v70;
  v69 = v8;
  if ( (v10 | v11) != 0 )
    goto LABEL_19;
  v14 = (float *)(pArg3 + 8);
  v15 = 1.0 / v8;
  v16 = 16;
  v58 = v70 * v15;
  v59 = v71 * v15;
  v60 = v15 * v7;
  v66 = (v77 + v80) * 0.5;
  v67 = (v4 + v81) * 0.5;
  v68 = (v79 + v82) * 0.5;
  v76 = 0.0;
  v75 = 0.0;
  v74 = 0.0;
  v17 = 0.0;
  do
  {
    v70 = (*(v14 - 2) - v66) * v58;
    v71 = (*(v14 - 1) - v67) * v59;
    v18 = *v14;
    v14 += 4;
    --v16;
    v19 = (v18 - v68) * v60;
    v20 = v71 + v19 + v70;
    v17 = v17 + v20 * v20;
    v21 = v71 + v70 - v19;
    v74 = v21 * v21 + v74;
    v22 = v70 - v71;
    v75 = (v22 + v19) * (v22 + v19) + v75;
    v76 = (v22 - v19) * (v22 - v19) + v76;
  }
  while ( v16 != 0 );
  v73 = v17;
  v23 = 0;
  for ( j = 1; j < 4; ++j )
  {
    v25 = &v73 + j;
    if ( v17 < *v25 )
    {
      v23 = j;
      v17 = *v25;
    }
  }
  if ( (v23 & 2) != 0 )
  {
    v26 = v81;
    v81 = v4;
    v64 = v26;
    v4 = v26;
    v78 = v26;
  }
  if ( (v23 & 1) != 0 )
  {
    v27 = v79;
    v79 = v82;
    v82 = v27;
  }
  if ( v69 < 0.00024414062 )
  {
LABEL_19:
    *pArg1 = v80;
    pArg1[1] = v81;
    pArg1[2] = v82;
    result = pArg2;
    v13 = v77;
    pArg2[1] = v4;
    *pArg2 = v13;
  }
  else
  {
    v64 = (float)(unsigned int)(nArg4 - 1);
    sub_693004();
    v69 = 0.0;
    v29 = 0.000015258789;
    do
    {
      if ( nArg4 != 0 )
      {
        v30 = v61;
        v31 = v55;
        v32 = v62 - (uint8_t *)v61;
        for ( k = nArg4; k != 0; --k )
        {
          *(v31 - 1) = v80 * *v30 + v77 * *(float *)((char *)v30 + v32);
          *v31 = v81 * *v30 + v78 * *(float *)((char *)v30 + v32);
          v34 = v82 * *v30;
          v35 = v79 * *(float *)((char *)v30++ + v32);
          v31[1] = v34 + v35;
          v31 += 4;
        }
      }
      v36 = v77 - v80;
      v71 = v78 - v81;
      v37 = v79 - v82;
      v38 = v37 * v37 + v71 * v71 + v36 * v36;
      if ( v38 < 0.00024414062 )
        break;
      v39 = v64 / v38;
      v40 = v56;
      v41 = 16;
      v70 = v39 * v36;
      v71 = v71 * v39;
      v72 = v39 * v37;
      v75 = 0.0;
      v74 = 0.0;
      v73 = 0.0;
      v68 = 0.0;
      v67 = 0.0;
      v66 = 0.0;
      v65 = 0.0;
      v84 = 0.0;
      do
      {
        v42 = (*(v40 - 1) - v81) * v71 + (*(v40 - 2) - v80) * v70 + (*v40 - v82) * v72;
        v63 = v42;
        if ( v42 < v64 )
        {
          v63 = v63 + 0.5;
          v57 = (int)v63;
          v43 = v57;
          v29 = 0.000015258789;
        }
        else
        {
          v43 = nArg4 - 1;
        }
        v44 = v55[4 * v43 - 1] - *(v40 - 2);
        v59 = v55[4 * v43] - *(v40 - 1);
        v45 = v55[4 * v43 + 1] - *v40;
        v46 = v43;
        v47 = &v61[v46];
        v48 = v61[v46];
        v49 = (float *)&v62[v46 * 4];
        v50 = v48 * 0.125;
        v40 += 4;
        --v41;
        v51 = *v49 * 0.125;
        v84 = v50 * *v47 + v84;
        v66 = v50 * v44 + v66;
        v67 = v50 * v59 + v67;
        v68 = v50 * v45 + v68;
        v65 = v51 * *v49 + v65;
        v73 = v51 * v44 + v73;
        v74 = v59 * v51 + v74;
        v75 = v51 * v45 + v75;
      }
      while ( v41 != 0 );
      if ( v84 > 0.0 )
      {
        v52 = -1.0 / v84;
        v80 = v66 * v52 + v80;
        v81 = v67 * v52 + v81;
        v82 = v52 * v68 + v82;
      }
      if ( v65 > 0.0 )
      {
        v53 = -1.0 / v65;
        v77 = v73 * v53 + v77;
        v78 = v74 * v53 + v78;
        v79 = v53 * v75 + v79;
      }
      if ( v66 * v66 < v29
        && v67 * v67 < v29
        && v68 * v68 < v29
        && v73 * v73 < v29
        && v74 * v74 < v29
        && v75 * v75 < v29 )
      {
        break;
      }
      ++LODWORD(v69);
    }
    while ( LODWORD(v69) < 8 );
    *pArg1 = v80;
    pArg1[1] = v81;
    pArg1[2] = v82;
    result = pArg2;
    *pArg2 = v77;
    pArg2[1] = v78;
  }
  result[2] = v79;
  return result;
}


// ------------------------------------------------------------
// 0x693991 sub_693991
// ------------------------------------------------------------
// 【L1】调色板量化：16 项 RGBA 浮点 → 统计 <0.5 透明项 → 输出索引色（RGB5551 方向）【推断】
int /*usercall*/ sub_693991@<eax>(float *pArg1@<eax>, int pArg2, int nArg3)
{
  int v4; // esi
  float *v5; // ecx
  int i; // edi
  char v7; // dl
  char *v8; // esi
  char *v9; // edi
  float *v10; // eax
  unsigned int v11; // ecx
  double v12; // st7
  double v13; // st6
  double v14; // st5
  double v15; // st4
  bool v16; // zf
  unsigned int v17; // esi
  int v18; // eax
  unsigned int v19; // edi
  float *v20; // esi
  float *v21; // esi
  double v22; // st7
  double v23; // st6
  double v24; // st4
  double v25; // st5
  double v26; // st4
  double v27; // st7
  double v28; // st6
  double v29; // st5
  unsigned int v30; // edx
  uint8_t *v31; // esi
  char *v32; // edi
  float *v33; // ecx
  double v34; // st7
  int v35; // eax
  int v36; // ebx
  int v37; // eax
  double v38; // st7
  int v39; // ebx
  double v40; // st6
  float v42[4]; // [esp+0h] [ebp-270h]
  float v43; // [esp+10h] [ebp-260h] BYREF
  float v44; // [esp+14h] [ebp-25Ch] BYREF
  uint8_t v45[248]; // [esp+18h] [ebp-258h] BYREF
  float pBuf[64]; // [esp+110h] [ebp-160h] BYREF
  float v47; // [esp+210h] [ebp-60h] BYREF
  float v48; // [esp+214h] [ebp-5Ch]
  float v49; // [esp+218h] [ebp-58h]
  int v50; // [esp+220h] [ebp-50h]
  char *v51; // [esp+224h] [ebp-4Ch]
  char *v52; // [esp+228h] [ebp-48h]
  char *v53; // [esp+22Ch] [ebp-44h]
  char *v54; // [esp+230h] [ebp-40h]
  char *v55; // [esp+234h] [ebp-3Ch]
  char *v56; // [esp+238h] [ebp-38h]
  char *v57; // [esp+23Ch] [ebp-34h]
  char *v58; // [esp+240h] [ebp-30h]
  char *v59; // [esp+244h] [ebp-2Ch]
  float v60; // [esp+248h] [ebp-28h]
  float v61; // [esp+24Ch] [ebp-24h]
  float v62; // [esp+250h] [ebp-20h]
  float v63; // [esp+254h] [ebp-1Ch]
  float v64; // [esp+258h] [ebp-18h]
  float v65; // [esp+25Ch] [ebp-14h]
  float v66; // [esp+260h] [ebp-10h]
  float v67; // [esp+264h] [ebp-Ch]
  float v68; // [esp+268h] [ebp-8h]
  float v69; // [esp+26Ch] [ebp-4h]
  float v70; // [esp+270h] [ebp+0h]
  float v71; // [esp+274h] [ebp+4h]
  float v72; // [esp+278h] [ebp+8h]
  float v73; // [esp+27Ch] [ebp+Ch]
  float v74; // [esp+280h] [ebp+10h]
  float v75; // [esp+284h] [ebp+14h]
  int v76; // [esp+288h] [ebp+18h]
  char *v77; // [esp+28Ch] [ebp+1Ch]
  char *v78; // [esp+290h] [ebp+20h]
  char *v79; // [esp+294h] [ebp+24h]
  float v80; // [esp+298h] [ebp+28h] BYREF
  float v81; // [esp+29Ch] [ebp+2Ch]
  float v82; // [esp+2A0h] [ebp+30h]
  float v83; // [esp+2A4h] [ebp+34h]
  float v84; // [esp+2A8h] [ebp+38h] BYREF
  float v85; // [esp+2ACh] [ebp+3Ch]
  float v86; // [esp+2B0h] [ebp+40h]
  char *v87; // [esp+2B8h] [ebp+48h]
  float v88; // [esp+2BCh] [ebp+4Ch]
  float v89; // [esp+2C0h] [ebp+50h]
  float v90; // [esp+2C4h] [ebp+54h] BYREF
  float v91; // [esp+2C8h] [ebp+58h]
  float v92; // [esp+2CCh] [ebp+5Ch]
  float v93; // [esp+2D0h] [ebp+60h]
  int v94; // [esp+2D4h] [ebp+64h]
  int v95; // [esp+2D8h] [ebp+68h]
  float v96; // [esp+2DCh] [ebp+6Ch]
  char v97; // [esp+2ECh] [ebp+7Ch]
  float v98; // [esp+2ECh] [ebp+7Ch]
  unsigned int v99; // [esp+2ECh] [ebp+7Ch]

  if ( nArg3 != 0 )
  {
    v4 = 0;
    v5 = pArg1 + 3;
    for ( i = 16; i != 0; --i )
    {
      if ( *v5 < 0.5 )
        ++v4;
      v5 += 4;
    }
    if ( v4 == 16 )
    {
      *(uint16_t *)(pArg2 + 2) = -1;
      *(uint32_t *)(pArg2 + 4) = -1;
      *(uint16_t *)pArg2 = 0;
      return 0;
    }
    v94 = 4 - (v4 != 0);
  }
  else
  {
    v94 = 4;
  }
  memset(pBuf, 0, sizeof(pBuf));
  sub_693004();
  v77 = (char *)((char *)&pBuf[2] - (char *)pArg1);
  v53 = (char *)((char *)&pBuf[3] - (char *)pArg1);
  v51 = (char *)((char *)&pBuf[4] - (char *)pArg1);
  v76 = (char *)&pBuf[10] - (char *)pArg1;
  v54 = (char *)((char *)&pBuf[11] - (char *)pArg1);
  v56 = (char *)((char *)&pBuf[12] - (char *)pArg1);
  LODWORD(v88) = (char *)&pBuf[14] - (char *)pArg1;
  v52 = (char *)((char *)&pBuf[15] - (char *)pArg1);
  v58 = (char *)((char *)&pBuf[16] - (char *)pArg1);
  v87 = (char *)((char *)&pBuf[18] - (char *)pArg1);
  v59 = (char *)((char *)&pBuf[19] - (char *)pArg1);
  v97 = v7;
  v8 = (char *)((char *)pBuf - (char *)pArg1);
  v55 = (char *)((char *)&pBuf[20] - (char *)pArg1);
  v9 = (char *)((char *)&v43 - (char *)pArg1);
  v10 = pArg1 + 2;
  v57 = (char *)((char *)pBuf - (char *)pArg1);
  v11 = 0;
  while ( 1 )
  {
    v90 = pBuf[v11] + *(v10 - 2);
    v91 = *(v10 - 1) + pBuf[v11 + 1];
    v92 = *(float *)((char *)v10 + (uint32_t)v8) + *v10;
    v96 = v90 * 31.0 + 0.5;
    v50 = (int)v96;
    v89 = (double)v50 * 0.032258064;
    *(float *)((char *)&v43 + v11 * 4) = v89;
    v96 = v91 * 63.0 + 0.5;
    v79 = (char *)(int)v96;
    v96 = (double)(int)v79 * 0.015873017;
    *(float *)&v45[v11 * 4 - 4] = v96;
    *(float *)&v95 = v92 * 31.0 + 0.5;
    v78 = (char *)(int)*(float *)&v95;
    v12 = (double)(int)v78 * 0.032258064;
    v95 = v97 & 3;
    *(float *)((char *)v10 + (uint32_t)v9) = v12;
    *(float *)((char *)v10 + (char *)&v44 - (char *)pArg1) = 1.0;
    v13 = v90 - v89;
    v14 = v91 - v96;
    v85 = v14;
    v15 = v92 - v12;
    v86 = v15;
    if ( (v97 & 3) != 3 )
    {
      *(float *)&v77[(uint32_t)v10] = v13 * 0.4375 + *(float *)&v77[(uint32_t)v10];
      *(float *)&v53[(uint32_t)v10] = v14 * 0.4375 + *(float *)&v53[(uint32_t)v10];
      *(float *)&v51[(uint32_t)v10] = v15 * 0.4375 + *(float *)&v51[(uint32_t)v10];
    }
    if ( v11 < 48 )
    {
      if ( *(float *)&v95 != 0.0 )
      {
        *(float *)((char *)v10 + v76) = v13 * 0.1875 + *(float *)((char *)v10 + v76);
        *(float *)&v54[(uint32_t)v10] = v14 * 0.1875 + *(float *)&v54[(uint32_t)v10];
        *(float *)&v56[(uint32_t)v10] = v15 * 0.1875 + *(float *)&v56[(uint32_t)v10];
      }
      *(float *)((char *)v10 + LODWORD(v88)) = v13 * 0.3125 + *(float *)((char *)v10 + LODWORD(v88));
      *(float *)&v52[(uint32_t)v10] = v14 * 0.3125 + *(float *)&v52[(uint32_t)v10];
      v16 = v95 == 3;
      *(float *)&v58[(uint32_t)v10] = v15 * 0.3125 + *(float *)&v58[(uint32_t)v10];
      if ( !v16 )
      {
        *(float *)&v87[(uint32_t)v10] = v13 * 0.0625 + *(float *)&v87[(uint32_t)v10];
        *(float *)&v59[(uint32_t)v10] = v85 * 0.0625 + *(float *)&v59[(uint32_t)v10];
        *(float *)&v55[(uint32_t)v10] = v86 * 0.0625 + *(float *)&v55[(uint32_t)v10];
      }
    }
    ++v97;
    v11 += 4;
    v42[v11] = v89 * flt_79A5E0;
    v42[v11 + 1] = v96 * flt_79A5E4;
    *(float *)((char *)v10 + (uint32_t)v9) = v12 * flt_79A5E8;
    v10 += 4;
    if ( v11 >= 64 )
      break;
    v8 = v57;
  }
  sub_693426(&v80, &v90, (int)&v43, v94);
  v47 = v80 * flt_79A5F0;
  v48 = v81 * flt_79A5F4;
  v49 = v82 * flt_79A5F8;
  v84 = v90 * flt_79A5F0;
  v85 = v91 * flt_79A5F4;
  v86 = v92 * flt_79A5F8;
  *(float *)&v17 = COERCE_FLOAT(sub_693027(&v47));
  v88 = *(float *)&v17;
  v18 = sub_693027(&v84);
  v19 = v18;
  v87 = (char *)v18;
  if ( v94 == 4 && (uint16_t)v17 == (uint16_t)v18 )
  {
    *(uint32_t *)(pArg2 + 4) = 0;
    *(uint16_t *)pArg2 = v17;
    *(uint16_t *)(pArg2 + 2) = v18;
  }
  else
  {
    sub_692F0A(&v47, v17);
    sub_692F0A(&v84, v19);
    v80 = v47 * flt_79A5E0;
    v81 = v48 * flt_79A5E4;
    v82 = v49 * flt_79A5E8;
    v90 = v84 * flt_79A5E0;
    v91 = v85 * flt_79A5E4;
    v92 = v86 * flt_79A5E8;
    if ( (v94 == 3) == (uint16_t)v19 >= (uint16_t)v17 )
    {
      *(uint16_t *)pArg2 = v17;
      *(uint16_t *)(pArg2 + 2) = v19;
      v60 = v80;
      v61 = v81;
      v62 = v82;
      v63 = v83;
      v20 = &v90;
    }
    else
    {
      *(uint16_t *)(pArg2 + 2) = v17;
      *(uint16_t *)pArg2 = v19;
      v60 = v90;
      v61 = v91;
      v62 = v92;
      v63 = v93;
      v20 = &v80;
    }
    v64 = *v20;
    v21 = v20 + 1;
    v65 = *v21++;
    v66 = *v21;
    v67 = v21[1];
    v22 = v64 - v60;
    if ( v94 == 3 )
    {
      v89 = COERCE_FLOAT(&unk_748BDC);
      v68 = 0.5 * v22 + v60;
      v23 = v65 - v61;
      v69 = v23 * 0.5 + v61;
      v24 = v66 - v62;
      v98 = v24;
      v70 = v24 * 0.5 + v62;
      v71 = (v67 - v63) * 0.5 + v63;
    }
    else
    {
      v89 = COERCE_FLOAT(&unk_748BCC);
      v68 = 0.33333334 * v22 + v60;
      v23 = v65 - v61;
      v69 = 0.33333334 * v23 + v61;
      v25 = v66 - v62;
      v98 = v25;
      v70 = 0.33333334 * v25 + v62;
      v26 = v67 - v63;
      v71 = 0.33333334 * v26 + v63;
      v72 = v22 * 0.66666669 + v60;
      v73 = v23 * 0.66666669 + v61;
      v74 = v25 * 0.66666669 + v62;
      v75 = v26 * 0.66666669 + v63;
    }
    v90 = v22;
    v27 = v23;
    v28 = v98;
    v96 = (float)(unsigned int)(v94 - 1);
    if ( LOWORD(v88) == (uint16_t)v87 )
      v29 = 0.0;
    else
      v29 = v96 / (v28 * v28 + v27 * v27 + v90 * v90);
    v90 = v90 * v29;
    memset(pBuf, 0, sizeof(pBuf));
    v91 = v29 * v27;
    v92 = v29 * v28;
    sub_693004();
    *(float *)&v95 = COERCE_FLOAT(pBuf);
    v87 = (char *)((char *)&pBuf[1] - (char *)pArg1);
    v77 = (char *)((char *)&pBuf[5] - (char *)pArg1);
    v78 = (char *)((char *)&pBuf[13] - (char *)pArg1);
    v31 = (uint8_t *)(v45 - (uint8_t *)pArg1);
    v32 = (char *)((char *)&pBuf[17] - (char *)pArg1);
    v99 = v30;
    v33 = pArg1 + 1;
    v79 = (char *)((char *)&pBuf[21] - (char *)pArg1);
    do
    {
      if ( v94 == 3 && v33[2] < 0.5 )
      {
        v30 = (v30 >> 2) | 0xC0000000;
      }
      else
      {
        v80 = flt_79A5E0 * *(v33 - 1) + *(float *)v95;
        v81 = flt_79A5E4 * *v33 + *(float *)&v57[(uint32_t)v33];
        v82 = flt_79A5E8 * v33[1] + *(float *)((char *)v33 + (uint32_t)v87);
        v34 = (v80 - v60) * v90 + (v82 - v62) * v92 + (v81 - v61) * v91;
        if ( v34 > 0.0 )
        {
          if ( v34 < v96 )
          {
            v88 = v34 + 0.5;
            v76 = (int)v88;
            v35 = *(uint32_t *)(LODWORD(v89) + 4 * v76);
          }
          else
          {
            v35 = 1;
          }
        }
        else
        {
          v35 = 0;
        }
        v36 = v35;
        v37 = 16 * v35;
        v30 = (v36 << 30) | (v30 >> 2);
        v38 = (v80 - *(float *)((char *)&v60 + v37)) * *(float *)((char *)v33 + (uint32_t)v31);
        v39 = v99 & 3;
        v40 = (v81 - *(float *)((char *)&v61 + v37)) * *(float *)((char *)v33 + (uint32_t)v31);
        v85 = v40;
        v86 = (v82 - *(float *)((char *)&v62 + v37)) * *(float *)((char *)v33 + (uint32_t)v31);
        if ( v39 != 3 )
        {
          *(float *)&v53[(uint32_t)v33] = v38 * 0.4375 + *(float *)&v53[(uint32_t)v33];
          *(float *)&v51[(uint32_t)v33] = 0.4375 * v40 + *(float *)&v51[(uint32_t)v33];
          *(float *)&v77[(uint32_t)v33] = v86 * 0.4375 + *(float *)&v77[(uint32_t)v33];
        }
        if ( v99 < 0xC )
        {
          if ( (v99 & 3) != 0 )
          {
            *(float *)&v54[(uint32_t)v33] = v38 * 0.1875 + *(float *)&v54[(uint32_t)v33];
            *(float *)&v56[(uint32_t)v33] = 0.1875 * v40 + *(float *)&v56[(uint32_t)v33];
            *(float *)&v78[(uint32_t)v33] = v86 * 0.1875 + *(float *)&v78[(uint32_t)v33];
          }
          *(float *)&v52[(uint32_t)v33] = v38 * 0.3125 + *(float *)&v52[(uint32_t)v33];
          *(float *)&v58[(uint32_t)v33] = v40 * 0.3125 + *(float *)&v58[(uint32_t)v33];
          *(float *)((char *)v33 + (uint32_t)v32) = v86 * 0.3125 + *(float *)((char *)v33 + (uint32_t)v32);
          if ( v39 != 3 )
          {
            *(float *)&v59[(uint32_t)v33] = v38 * 0.0625 + *(float *)&v59[(uint32_t)v33];
            *(float *)&v55[(uint32_t)v33] = v85 * 0.0625 + *(float *)&v55[(uint32_t)v33];
            *(float *)&v79[(uint32_t)v33] = v86 * 0.0625 + *(float *)&v79[(uint32_t)v33];
          }
        }
      }
      ++v99;
      v95 += 16;
      v33 += 4;
    }
    while ( v99 < 0x10 );
    *(uint32_t *)(pArg2 + 4) = v30;
  }
  return 0;
}


// ------------------------------------------------------------
// 0x694195 sub_694195
// ------------------------------------------------------------
// 【L1】DXT 调色板展开：8 项 4bit 索引 → float RGBA（×0.06666667 = /15）
int /*cdecl*/ sub_694195(float *pArg1, uint16_t *pArg2)
{
  uint16_t v3; // si
  unsigned int v4; // edi
  double v5; // st7
  double v6; // st5
  double v7; // st5
  double v8; // st5
  unsigned int v9; // ebx
  int i; // ecx
  int v12; // edx
  float *v13; // edi
  float v15; // [esp+Ch] [ebp-58h] BYREF
  float v16; // [esp+10h] [ebp-54h]
  float v17; // [esp+14h] [ebp-50h]
  float v18; // [esp+18h] [ebp-4Ch]
  float v19; // [esp+1Ch] [ebp-48h] BYREF
  float v20; // [esp+20h] [ebp-44h]
  float v21; // [esp+24h] [ebp-40h]
  float v22; // [esp+28h] [ebp-3Ch]
  float v23; // [esp+2Ch] [ebp-38h]
  float v24; // [esp+30h] [ebp-34h]
  float v25; // [esp+34h] [ebp-30h]
  float v26; // [esp+38h] [ebp-2Ch]
  float v27; // [esp+3Ch] [ebp-28h]
  float v28; // [esp+40h] [ebp-24h]
  float v29; // [esp+44h] [ebp-20h]
  float v30; // [esp+48h] [ebp-1Ch]
  float v31; // [esp+4Ch] [ebp-18h]
  float v32; // [esp+50h] [ebp-14h]
  float v33; // [esp+54h] [ebp-10h]
  float v34; // [esp+58h] [ebp-Ch]
  float v35; // [esp+5Ch] [ebp-8h]
  float v36; // [esp+60h] [ebp-4h]
  float v37; // [esp+70h] [ebp+Ch]

  v3 = *pArg2;
  sub_692F0A(&v15, *pArg2);
  v4 = pArg2[1];
  sub_692F0A(&v19, v4);
  if ( v3 > (uint16_t)v4 )
  {
    v5 = v19 - v15;
    v23 = v5 * 0.33333334 + v15;
    v6 = v20 - v16;
    v37 = v6;
    v24 = v6 * 0.33333334 + v16;
    v7 = v21 - v17;
    v36 = v7;
    v25 = v7 * 0.33333334 + v17;
    v8 = v22 - v18;
    v35 = v8;
    v26 = v8 * 0.33333334 + v18;
    v27 = v5 * 0.66666669 + v15;
    v28 = v37 * 0.66666669 + v16;
    v29 = v36 * 0.66666669 + v17;
    v30 = v35 * 0.66666669 + v18;
  }
  else
  {
    v23 = (v19 - v15) * 0.5 + v15;
    v24 = (v20 - v16) * 0.5 + v16;
    v25 = (v21 - v17) * 0.5 + v17;
    v26 = (v22 - v18) * 0.5 + v18;
    v31 = 0.0;
    v32 = 0.0;
    v33 = 0.0;
    v34 = 0.0;
    v27 = 0.0;
    v28 = 0.0;
    v29 = 0.0;
    v30 = 0.0;
  }
  v9 = *((uint32_t *)pArg2 + 1);
  for ( i = 16; i != 0; --i )
  {
    v12 = 16 * (v9 & 3);
    *pArg1 = *(float *)((char *)&v15 + v12);
    pArg1[1] = *(float *)((char *)&v15 + v12 + 4);
    pArg1[2] = *(float *)((char *)&v17 + v12);
    v13 = pArg1 + 3;
    pArg1 += 4;
    v9 >>= 2;
    *v13 = *(float *)((char *)&v18 + v12);
  }
  return 0;
}



// ------------------------------------------------------------
// 0x6942D3 sub_6942D3
// ------------------------------------------------------------
// 【L1】DXT1 调色板展开 + 两端色 4bit 解码（调 sub_694195）
int /*cdecl*/ sub_6942D3(float *pArg1, uint16_t *pArg2)
{
  int result; // eax
  unsigned int v3; // ecx
  int v4; // edx
  float *v5; // eax
  double v6; // st6
  unsigned int v7; // esi
  int v8; // ecx
  float *v9; // eax
  double v10; // st6

  result = sub_694195(pArg1, pArg2 + 4);
  if ( result >= 0 )
  {
    v3 = *(uint32_t *)pArg2;
    v4 = 8;
    v5 = pArg1 + 3;
    do
    {
      v6 = (double)(v3 & 0xF);
      v3 >>= 4;
      *v5 = v6 * 0.06666667;
      v5 += 4;
      --v4;
    }
    while ( v4 != 0 );
    v7 = *((uint32_t *)pArg2 + 1);
    v8 = 8;
    v9 = pArg1 + 35;
    do
    {
      v10 = (double)(v7 & 0xF);
      v7 >>= 4;
      *v9 = v10 * 0.06666667;
      v9 += 4;
      --v8;
    }
    while ( v8 != 0 );
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x694356 sub_694356
// ------------------------------------------------------------
// 【L1】DXT 调色板展开：3bit 索引（×0.14285715 = /7）+ RGB 灰度两端插值
int /*cdecl*/ sub_694356(float *pArg1, uint16_t *pArg2)
{
  int result; // eax
  uint8_t v3; // al
  uint8_t v4; // cl
  unsigned int j; // eax
  double v6; // st7
  double v7; // st6
  unsigned int i; // eax
  double v9; // st7
  double v10; // st6
  int v11; // edx
  unsigned int v12; // ecx
  float *v13; // eax
  int v14; // ebx
  int v15; // edx
  unsigned int v16; // ecx
  float *v17; // eax
  int v18; // esi
  float v19; // [esp+8h] [ebp-20h]
  float v20; // [esp+Ch] [ebp-1Ch]
  float v21; // [esp+20h] [ebp-8h]
  float v22; // [esp+24h] [ebp-4h]

  result = sub_694195(pArg1, pArg2 + 4);
  if ( result >= 0 )
  {
    v3 = *(uint8_t *)pArg2;
    v4 = *((uint8_t *)pArg2 + 1);
    v19 = (double)*(uint8_t *)pArg2 * 0.0039215689;
    v20 = (double)v4 * 0.0039215689;
    if ( v3 <= v4 )
    {
      for ( i = 1; i < 5; *(&v19 + i) = (v9 + v10) * 0.2 )
      {
        v9 = (double)(5 - i) * v19;
        v10 = (double)i++ * v20;
      }
      v21 = 0.0;
      v22 = 1.0;
    }
    else
    {
      for ( j = 1; j < 7; *(&v19 + j) = (v6 + v7) * 0.14285715 )
      {
        v6 = (double)(7 - j) * v19;
        v7 = (double)j++ * v20;
      }
    }
    v11 = 8;
    v12 = *((uint8_t *)pArg2 + 2) | (*(uint16_t *)((char *)pArg2 + 3) << 8);
    v13 = pArg1 + 3;
    do
    {
      v14 = v12 & 7;
      v12 >>= 3;
      *v13 = *(&v19 + v14);
      v13 += 4;
      --v11;
    }
    while ( v11 != 0 );
    v15 = 8;
    v16 = *((uint8_t *)pArg2 + 5) | (pArg2[3] << 8);
    v17 = pArg1 + 35;
    do
    {
      v18 = v16 & 7;
      v16 >>= 3;
      *v17 = *(&v19 + v18);
      v17 += 4;
      --v15;
    }
    while ( v15 != 0 );
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x694492 sub_694492
// ------------------------------------------------------------
// 【L1】调色板索引表写入（int 表 → float 表搬运）【推断】
int /*cdecl*/ sub_694492(int nArg1, float *pArg2)
{
  int result; // eax

  result = sub_693991(pArg2, nArg1, 1);
  if ( result >= 0 )
    return 0;
  return result;
}



// ------------------------------------------------------------
// 0x6944AA sub_6944AA
// ------------------------------------------------------------
// 【L1】调色板索引表写入变体（uint32 表）【推断】
int /*cdecl*/ sub_6944AA(uint32_t *pArg1, float *pArg2)
{
  unsigned int v3; // edx
  double v4; // st7
  int *v5; // edx
  int v6; // eax
  double v7; // st7
  int v8; // edx
  double v9; // st7
  float pBuf[16]; // [esp+Ch] [ebp-50h] BYREF
  float v12; // [esp+4Ch] [ebp-10h]
  float v13; // [esp+50h] [ebp-Ch]
  float v14; // [esp+54h] [ebp-8h]
  float *v15; // [esp+58h] [ebp-4h]
  unsigned int v16; // [esp+64h] [ebp+8h]

  *pArg1 = 0;
  pArg1[1] = 0;
  memset(pBuf, 0, sizeof(pBuf));
  sub_693004();
  v16 = v3;
  v15 = pArg2 + 3;
  do
  {
    v4 = pBuf[v16] + *v15;
    v14 = v4;
    v13 = v4 * 15.0 + 0.5;
    LODWORD(v12) = (int)v13;
    v5 = &pArg1[v16 >> 3];
    v6 = (LODWORD(v12) << 28) | ((unsigned int)*v5 >> 4);
    v13 = v12;
    v7 = (double)LODWORD(v12);
    *v5 = v6;
    v8 = v16 & 3;
    v9 = v14 - v7 * 0.06666667;
    if ( v8 != 3 )
      pBuf[v16 + 1] = 0.4375 * v9 + pBuf[v16 + 1];
    if ( v16 < 0xC )
    {
      if ( (v16 & 3) != 0 )
        pBuf[v16 + 3] = 0.1875 * v9 + pBuf[v16 + 3];
      pBuf[v16 + 4] = 0.3125 * v9 + pBuf[v16 + 4];
      if ( v8 != 3 )
        pBuf[v16 + 5] = v9 * 0.0625 + pBuf[v16 + 5];
    }
    ++v16;
    v15 += 4;
  }
  while ( v16 < 0x10 );
  return sub_693991(pArg2, (int)(pArg1 + 2), 0);
}



// ------------------------------------------------------------
// 0x6945BE sub_6945BE
// ------------------------------------------------------------
// 【L1】标量系数 × 调色板缩放（亮度调节方向）【推断】
int /*cdecl*/ sub_6945BE(float fArg1, int pArg2)
{
  float *v2; // ebx
  unsigned int v3; // edx
  float *v4; // edi
  double v5; // st7
  double v6; // st7
  uint8_t v8; // c0
  uint8_t v9; // c2
  double v10; // st7
  int v11; // esi
  float fArg12; // esi
  int result; // eax
  unsigned int v14; // edi
  char dword_9D376022; // cl
  double v16; // st7
  double v17; // st6
  unsigned int j; // eax
  double v19; // st7
  double v20; // st6
  unsigned int i; // eax
  double v22; // st7
  double v23; // st6
  double v24; // st7
  unsigned int dword_9D376023; // eax
  int v26; // ecx
  unsigned int v27; // edx
  unsigned int dword_9D3760232; // ebx
  double v29; // st7
  double v30; // st7
  int v31; // eax
  double v32; // st7
  int v33; // edi
  int v34; // [esp-4h] [ebp-40h]
  float pBuf[16]; // [esp+Ch] [ebp-30h] BYREF
  float v36[8]; // [esp+4Ch] [ebp+10h] BYREF
  float v37; // [esp+6Ch] [ebp+30h]
  float fArg13; // [esp+70h] [ebp+34h]
  float v39; // [esp+84h] [ebp+48h]
  float v40; // [esp+88h] [ebp+4Ch]
  int v41; // [esp+8Ch] [ebp+50h]
  float v42; // [esp+90h] [ebp+54h]
  float v43; // [esp+94h] [ebp+58h]
  float v44; // [esp+98h] [ebp+5Ch]
  float v45; // [esp+9Ch] [ebp+60h]
  float v46; // [esp+A0h] [ebp+64h]
  float v47; // [esp+A4h] [ebp+68h]
  int dword_9D37602; // [esp+A8h] [ebp+6Ch] BYREF

  v2 = (float *)(pArg2 + 12);
  v47 = *(float *)(pArg2 + 12);
  v46 = v47;
  memset(pBuf, 0, sizeof(pBuf));
  sub_693004();
  v3 = 0;
  v4 = v2;
  do
  {
    v5 = pBuf[v3] + *v4;
    v44 = v5;
    *(float *)&dword_9D37602 = v5 * 255.0 + 0.5;
    LODWORD(v45) = (int)*(float *)&dword_9D37602;
    *(float *)&dword_9D37602 = v45;
    v6 = (double)SLODWORD(v45) * 0.0039215689;
    v36[v3] = v6;
    if ( (v8 | v9) != 0 )
    {
      v47 = v6;
    }
    else if ( v6 > v46 )
    {
      v46 = v6;
    }
    v10 = v44 - v6;
    v11 = v3 & 3;
    if ( v11 != 3 )
      pBuf[v3 + 1] = 0.4375 * v10 + pBuf[v3 + 1];
    if ( v3 < 0xC )
    {
      if ( (v3 & 3) != 0 )
        pBuf[v3 + 3] = 0.1875 * v10 + pBuf[v3 + 3];
      pBuf[v3 + 4] = 0.3125 * v10 + pBuf[v3 + 4];
      if ( v11 != 3 )
        pBuf[v3 + 5] = v10 * 0.0625 + pBuf[v3 + 5];
    }
    ++v3;
    v4 += 4;
  }
  while ( v3 < 0x10 );
  dword_9D37602 = dword_9D3760;
  fArg12 = fArg1;
  result = sub_693991(LODWORD(fArg1) + 8, 0);
  if ( result < 0 )
    return result;
  if ( 1.0 == v47 )
  {
    *(uint8_t *)LODWORD(fArg12) = -1;
    *(uint8_t *)(LODWORD(fArg12) + 1) = -1;
LABEL_24:
    *(uint32_t *)(LODWORD(fArg12) + 2) = 0;
    *(uint16_t *)(LODWORD(fArg12) + 6) = 0;
    return 0;
  }
  if ( 0.0 == v47 || 1.0 == v46 )
  {
    pArg2 = 6;
    v14 = 6;
  }
  else
  {
    v14 = 8;
    pArg2 = 8;
  }
  sub_693121((float *)&dword_9D37602, &fArg1, (int)v36, v14);
  sub_693004();
  *(float *)&dword_9D37602 = *(float *)&dword_9D37602 * 255.0 + 0.5;
  LODWORD(v45) = (int)*(float *)&dword_9D37602;
  fArg1 = fArg1 * 255.0 + 0.5;
  dword_9D37602 = (int)fArg1;
  dword_9D376022 = dword_9D37602;
  v16 = (double)LOBYTE(v45) * 0.0039215689;
  v17 = (double)(uint8_t)dword_9D37602 * 0.0039215689;
  fArg1 = v17;
  if ( v14 == 8 )
  {
    if ( LOBYTE(v45) == (uint8_t)dword_9D37602 )
    {
      *(uint8_t *)LODWORD(fArg12) = LOBYTE(v45);
      *(uint8_t *)(LODWORD(fArg12) + 1) = dword_9D376022;
      goto LABEL_24;
    }
    *(uint8_t *)(LODWORD(fArg12) + 1) = LOBYTE(v45);
    v37 = v17;
    fArg13 = v16;
    *(uint8_t *)LODWORD(fArg12) = dword_9D376022;
    for ( i = 1; i < 7; *(&v37 + i) = (v22 + v23) * 0.14285715 )
    {
      v22 = (double)(7 - i) * v37;
      fArg1 = *(float *)&i;
      v23 = (double)i++ * fArg13;
    }
    v45 = COERCE_FLOAT(&unk_748BF4);
  }
  else
  {
    *(uint8_t *)LODWORD(fArg12) = LOBYTE(v45);
    v37 = v16;
    fArg13 = fArg1;
    *(uint8_t *)(LODWORD(fArg12) + 1) = dword_9D376022;
    for ( j = 1; j < 5; *(&v37 + j) = (v19 + v20) * 0.2 )
    {
      v19 = (double)(5 - j) * v37;
      fArg1 = *(float *)&j;
      v20 = (double)j++ * fArg13;
    }
    v45 = COERCE_FLOAT(&unk_748C14);
    v39 = 0.0;
    v40 = 1.0;
  }
  LODWORD(fArg1) = v14 - 1;
  v43 = (float)(v14 - 1);
  if ( v37 == fArg13 )
    v24 = 0.0;
  else
    v24 = v43 / (fArg13 - v37);
  v44 = v24;
  memset(pBuf, 0, sizeof(pBuf));
  sub_693004();
  dword_9D376023 = 0;
  v26 = LODWORD(fArg12) + 3;
  v47 = *(float *)&v2;
  do
  {
    *(float *)&v27 = 0.0;
    fArg1 = 0.0;
    dword_9D37602 = dword_9D376023 + 8;
    dword_9D3760232 = dword_9D376023;
    if ( dword_9D376023 >= dword_9D376023 + 8 )
      goto LABEL_58;
    v46 = v47;
    do
    {
      v29 = pBuf[dword_9D3760232] + *(float *)LODWORD(v46);
      fArg1 = v29;
      v30 = (v29 - v37) * v44;
      if ( v30 <= 0.0 )
      {
        if ( pArg2 != 6 || v37 * 0.5 < fArg1 )
        {
          v31 = 0;
          goto LABEL_49;
        }
        v34 = 6;
        goto LABEL_46;
      }
      if ( v30 < v43 )
      {
        v42 = v30 + 0.5;
        v41 = (int)v42;
        v31 = *(uint32_t *)(LODWORD(v45) + 4 * v41);
      }
      else
      {
        if ( pArg2 == 6 && (fArg13 + 1.0) * 0.5 <= fArg1 )
        {
          v34 = 7;
LABEL_46:
          v31 = v34;
          goto LABEL_49;
        }
        v31 = 1;
      }
LABEL_49:
      v32 = fArg1 - *(&v37 + v31);
      v27 = (v31 << 21) | (v27 >> 3);
      v33 = dword_9D3760232 & 3;
      if ( v33 != 3 )
        pBuf[dword_9D3760232 + 1] = 0.4375 * v32 + pBuf[dword_9D3760232 + 1];
      if ( dword_9D3760232 < 0xC )
      {
        if ( (dword_9D3760232 & 3) != 0 )
          pBuf[dword_9D3760232 + 3] = 0.1875 * v32 + pBuf[dword_9D3760232 + 3];
        pBuf[dword_9D3760232 + 4] = 0.3125 * v32 + pBuf[dword_9D3760232 + 4];
        if ( v33 != 3 )
          pBuf[dword_9D3760232 + 5] = v32 * 0.0625 + pBuf[dword_9D3760232 + 5];
      }
      LODWORD(v46) += 16;
      ++dword_9D3760232;
    }
    while ( dword_9D3760232 < dword_9D37602 );
    fArg1 = *(float *)&v27;
LABEL_58:
    LODWORD(v47) += 128;
    *(uint8_t *)(v26 + 1) = BYTE2(fArg1);
    dword_9D376023 = dword_9D37602;
    *(uint16_t *)(v26 - 1) = v27;
    v26 += 3;
  }
  while ( dword_9D376023 < 0x10 );
  pArg2 = dword_9D3760;
  return 0;
}


// ------------------------------------------------------------
// 0x694A10 sub_694A10
// ------------------------------------------------------------
// 【L1】DXT 调色板展开变体（与 694195 同构）
int /*cdecl*/ sub_694A10(float *pArg1, uint16_t *uArg2)
{
  int result; // eax

  result = sub_6942D3(pArg1, uArg2);
  if ( result >= 0 )
  {
    result = sub_692F56(pArg1);
    if ( result >= 0 )
      return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x694A56 sub_694A56
// ------------------------------------------------------------
// 【L1】调色板索引表写入变体（uint32 输入表）
int /*cdecl*/ sub_694A56(uint32_t *uArg1, float *pArg2)
{
  int result; // eax
  float v3[64]; // [esp+0h] [ebp-100h] BYREF

  result = sub_692FD4(pArg2, v3);
  if ( result >= 0 )
  {
    result = sub_6944AA(uArg1, v3);
    if ( result >= 0 )
      return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x694A8A sub_694A8A
// ------------------------------------------------------------
// 【L1】标量 × 调色板缩放变体
int /*cdecl*/ sub_694A8A(float fArg1, float *pArg2)
{
  int result; // eax
  float v3[64]; // [esp+0h] [ebp-100h] BYREF

  result = sub_692FD4(pArg2, v3);
  if ( result >= 0 )
  {
    result = sub_6945BE(fArg1, (int)v3);
    if ( result >= 0 )
      return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x694AC0 sub_694AC0
// ------------------------------------------------------------
// 【L1】SSE exp2 多项式近似（2^x，4 路并行，系数表 xmmword_79A8*）
__m128 */*cdecl*/ sub_694AC0(__m128 *uArg1, __m128 *uArg2, __m128 *uArg3)
{
  __m128 v3; // xmm1
  __m128 v4; // xmm2
  __m128 *v5; // edx
  __m128 v6; // xmm3
  __m128 v7; // xmm0
  __m128 v8; // xmm5
  __m128 v9; // xmm6
  __m128 v10; // xmm2
  __m128 v11; // xmm4
  __m128 v12; // xmm3
  __m128 v13; // xmm3
  __m128 v14; // xmm0
  __m128 v15; // xmm5
  __m128 v16; // xmm6
  __m128 v17; // xmm1
  __m128 v18; // xmm0
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  v3 = _mm_and_ps(*uArg1, (__m128)xmmword_79A8B0);
  v4 = _mm_and_ps(*uArg1, (__m128)xmmword_79A8C0);
  v5 = (__m128 *)(&savedregs - 16);
  v6 = _mm_add_ps(_mm_mul_ps(v4, (__m128)xmmword_79A8A0), (__m128)xmmword_79A850);
  v7 = _mm_sub_ps(v6, (__m128)xmmword_79A850);
  v8 = (__m128)xmmword_79A840;
  v9 = (__m128)xmmword_79A830;
  v10 = _mm_sub_ps(
          _mm_sub_ps(
            _mm_sub_ps(_mm_sub_ps(v4, _mm_mul_ps((__m128)xmmword_79A890, v7)), _mm_mul_ps((__m128)xmmword_79A880, v7)),
            _mm_mul_ps((__m128)xmmword_79A870, v7)),
          _mm_mul_ps((__m128)xmmword_79A860, v7));
  v11 = _mm_mul_ps(v10, v10);
  v12 = _mm_and_ps(v6, (__m128)xmmword_79A820);
  *v5 = _mm_and_ps(v12, (__m128)xmmword_79A810);
  v5[1] = v12;
  v5[2] = v12;
  v5[1].m128_i32[0] = (dword_79A800 & (v5[1].m128_i32[0] - v5->m128_i32[0])) << 30;
  v5[1].m128_i32[1] = (dword_79A800 & (v5[1].m128_i32[1] - v5->m128_i32[1])) << 30;
  v5[1].m128_i32[2] = (dword_79A800 & (v5[1].m128_i32[2] - v5->m128_i32[2])) << 30;
  v5[1].m128_i32[3] = (dword_79A800 & (v5[1].m128_i32[3] - v5->m128_i32[3])) << 30;
  v5[2].m128_i32[0] = (dword_79A800 & (v5->m128_i32[0] + v5[2].m128_i32[0])) << 30;
  v5[2].m128_i32[1] = (dword_79A800 & (v5->m128_i32[1] + v5[2].m128_i32[1])) << 30;
  v5[2].m128_i32[2] = (dword_79A800 & (v5->m128_i32[2] + v5[2].m128_i32[2])) << 30;
  v5[2].m128_i32[3] = (dword_79A800 & (v5->m128_i32[3] + v5[2].m128_i32[3])) << 30;
  v5->m128_i32[0] = *(&savedregs - 16) << 30;
  v5->m128_i32[1] <<= 30;
  v5->m128_i32[2] <<= 30;
  v5->m128_i32[3] = *(&savedregs - 13) << 30;
  v13 = _mm_xor_ps(*((__m128 *)&savedregs - 3), v3);
  v14 = _mm_cmpneq_ps(*((__m128 *)&savedregs - 4), (__m128)0LL);
  v15 = _mm_mul_ps(
          _mm_add_ps(
            _mm_mul_ps(
              _mm_add_ps(
                _mm_mul_ps(_mm_add_ps(_mm_mul_ps(v8, v11), (__m128)xmmword_79A7F0), v11),
                (__m128)xmmword_79A7D0),
              v11),
            (__m128)xmmword_79A7B0),
          v10);
  v16 = _mm_add_ps(
          _mm_mul_ps(
            _mm_add_ps(
              _mm_mul_ps(
                _mm_add_ps(
                  _mm_mul_ps(_mm_add_ps(_mm_mul_ps(v9, v11), (__m128)xmmword_79A7E0), v11),
                  (__m128)xmmword_79A7C0),
                v11),
              (__m128)xmmword_79A7A0),
            v11),
          (__m128)xmmword_79A790);
  v17 = _mm_or_ps(_mm_andnot_ps(v14, v15), _mm_and_ps(v14, v16));
  v18 = _mm_xor_ps(_mm_or_ps(_mm_and_ps(v14, v15), _mm_andnot_ps(v14, v16)), *((__m128 *)&savedregs - 2));
  *uArg2 = _mm_xor_ps(v17, v13);
  *uArg3 = v18;
  return uArg2;
}



// ------------------------------------------------------------
// 0x694CB0 sub_694CB0
// ------------------------------------------------------------
// 【L1】SSE exp2 userpurge 变体（xmm0 寄存器传参，整数格点修正）
__m128 /*userpurge*/ sub_694CB0@<xmm0>(__m128i uArg1@<xmm0>, int nArg2, int nArg3, int nArg4, int nArg5)
{
  __m128 v6; // xmm2
  __m128 v7; // xmm3
  __m128 v8; // xmm4
  __m128 v9; // xmm2
  __m128 v10; // xmm4
  __m128 v11; // xmm2
  __m128 v12; // xmm4
  __m128 v13; // xmm2
  __m128 v14; // xmm4
  __m128 v15; // xmm7
  __m128i v16; // xmm0
  __m128i v17; // xmm3
  __m128 v18; // xmm7
  __m128 v19; // xmm5
  __m128 v20; // xmm2
  __m128 v21; // xmm0
  __m128 v22; // xmm2

  v6 = (__m128)_mm_and_si128(uArg1, (__m128i)xmmword_79A9A0);
  v7 = _mm_add_ps(_mm_mul_ps(v6, (__m128)xmmword_79A980), (__m128)xmmword_79A960);
  v8 = _mm_mul_ps((__m128)xmmword_79A970, _mm_sub_ps(v7, (__m128)xmmword_79A960));
  v9 = _mm_sub_ps(v6, v8);
  v10 = _mm_shuffle_ps(v8, v8, 57);
  v11 = _mm_sub_ps(v9, v10);
  v12 = _mm_shuffle_ps(v10, v10, 57);
  v13 = _mm_sub_ps(_mm_sub_ps(v11, v12), _mm_shuffle_ps(v12, v12, 57));
  v14 = _mm_mul_ps(v13, v13);
  v15 = _mm_and_ps(v7, (__m128)xmmword_79A950);
  v16 = (__m128i)_mm_and_ps(v15, (__m128)xmmword_79A940);
  v17 = _mm_sub_epi32((__m128i)v15, v16);
  v18 = (__m128)_mm_slli_epi32(_mm_and_si128(_mm_add_epi32((__m128i)v15, v16), (__m128i)xmmword_79A930), 0x1Eu);
  v19 = _mm_add_ps(
          _mm_mul_ps(
            _mm_add_ps(
              _mm_mul_ps(
                _mm_add_ps(
                  _mm_mul_ps(_mm_add_ps(_mm_mul_ps((__m128)xmmword_79A920, v14), (__m128)xmmword_79A910), v14),
                  (__m128)xmmword_79A900),
                v14),
              (__m128)xmmword_79A8F0),
            _mm_unpacklo_ps(v13, v14)),
          (__m128)xmmword_79A8E0);
  v20 = _mm_cmpneq_ps((__m128)_mm_slli_epi32(v16, 0x1Eu), (__m128)0LL);
  v21 = _mm_and_ps(v20, v19);
  v22 = _mm_andnot_ps(v20, v19);
  return _mm_xor_ps(
           _mm_or_ps(v21, _mm_shuffle_ps(v22, v22, 177)),
           _mm_unpacklo_ps(
             v18,
             (__m128)_mm_xor_si128(
                       _mm_slli_epi32(_mm_and_si128(v17, (__m128i)xmmword_79A930), 0x1Eu),
                       _mm_and_si128(uArg1, (__m128i)xmmword_79A990))));
}



// ------------------------------------------------------------
// 0x694DA0 sub_694DA0
// ------------------------------------------------------------
// 【L1】SSE 2^x 精化实现（5 阶多项式，与 _pow_pentium4 配套）
__m128 */*cdecl*/ sub_694DA0(__m128i *uArg1, __m128 *uArg2, __m128 *uArg3)
{
  __m128 v3; // xmm2
  __m128 v4; // xmm3
  __m128 v5; // xmm0
  __m128 v6; // xmm2
  __m128 v7; // xmm4
  __m128 v8; // xmm7
  __m128i v9; // xmm0
  __m128i v10; // xmm3
  __m128 v11; // xmm7
  __m128 v12; // xmm0
  __m128 v13; // xmm5
  __m128 v14; // xmm6

  v3 = (__m128)_mm_and_si128(*uArg1, (__m128i)xmmword_79AAE0);
  v4 = _mm_add_ps(_mm_mul_ps(v3, (__m128)xmmword_79AAC0), (__m128)xmmword_79AA70);
  v5 = _mm_sub_ps(v4, (__m128)xmmword_79AA70);
  v6 = _mm_sub_ps(
         _mm_sub_ps(
           _mm_sub_ps(_mm_sub_ps(v3, _mm_mul_ps((__m128)xmmword_79AAB0, v5)), _mm_mul_ps((__m128)xmmword_79AAA0, v5)),
           _mm_mul_ps((__m128)xmmword_79AA90, v5)),
         _mm_mul_ps((__m128)xmmword_79AA80, v5));
  v7 = _mm_mul_ps(v6, v6);
  v8 = _mm_and_ps(v4, (__m128)xmmword_79AA40);
  v9 = (__m128i)_mm_and_ps(v8, (__m128)xmmword_79AA30);
  v10 = _mm_sub_epi32((__m128i)v8, v9);
  v11 = (__m128)_mm_slli_epi32(_mm_and_si128(_mm_add_epi32((__m128i)v8, v9), (__m128i)xmmword_79AA20), 0x1Eu);
  v12 = _mm_cmpneq_ps((__m128)_mm_slli_epi32(v9, 0x1Eu), (__m128)0LL);
  v13 = _mm_mul_ps(
          _mm_add_ps(
            _mm_mul_ps(
              _mm_add_ps(
                _mm_mul_ps(_mm_add_ps(_mm_mul_ps((__m128)xmmword_79AA60, v7), (__m128)xmmword_79AA10), v7),
                (__m128)xmmword_79A9F0),
              v7),
            (__m128)xmmword_79A9D0),
          v6);
  v14 = _mm_add_ps(
          _mm_mul_ps(
            _mm_add_ps(
              _mm_mul_ps(
                _mm_add_ps(
                  _mm_mul_ps(_mm_add_ps(_mm_mul_ps((__m128)xmmword_79AA50, v7), (__m128)xmmword_79AA00), v7),
                  (__m128)xmmword_79A9E0),
                v7),
              (__m128)xmmword_79A9C0),
            v7),
          (__m128)xmmword_79A9B0);
  *uArg2 = _mm_xor_ps(
          _mm_or_ps(_mm_andnot_ps(v12, v13), _mm_and_ps(v12, v14)),
          (__m128)_mm_xor_si128(
                    _mm_slli_epi32(_mm_and_si128(v10, (__m128i)xmmword_79AA20), 0x1Eu),
                    _mm_and_si128(*uArg1, (__m128i)xmmword_79AAD0)));
  *uArg3 = _mm_xor_ps(_mm_or_ps(_mm_and_ps(v12, v13), _mm_andnot_ps(v12, v14)), v11);
  return uArg2;
}



// ------------------------------------------------------------
// 0x694FC0 sub_694FC0
// ------------------------------------------------------------
// 【L1】空桩（nop/对齐，IDA 空函数）
void sub_694FC0()
{
  ;
}



// ------------------------------------------------------------
// 0x6950C0 sub_6950C0
// ------------------------------------------------------------
// 【L1】空桩（同上）
void sub_6950C0()
{
  ;
}



// ------------------------------------------------------------
// 0x6952C0 sub_6952C0
// ------------------------------------------------------------
// 【L1】空桩（同上）
void sub_6952C0()
{
  ;
}



// ------------------------------------------------------------
// 0x6956A0 sub_6956A0
// ------------------------------------------------------------
// 【L1】3DNow! fabs：mm0 低双字符号位清零（v & 0x80000000 ^ v）
unsigned int /*usercall*/ sub_6956A0@<eax>(__m64 uArg1@<mm0>)
{
  int v1; // eax

  v1 = _mm_cvtsi64_si32(uArg1);
  return v1 & 0x80000000 ^ v1;
}



// ------------------------------------------------------------
// 0x6957C0 sub_6957C0
// ------------------------------------------------------------
// 【L1】3DNow! fabs（与 6956A0 完全同体，双入口）
unsigned int /*usercall*/ sub_6957C0@<eax>(__m64 uArg1@<mm0>)
{
  int v1; // eax

  v1 = _mm_cvtsi64_si32(uArg1);
  return v1 & 0x80000000 ^ v1;
}




// ============================================================
// SECTION 2  导入 thunk + COM/BSTR 助手（0x695BB8-0x697B00）
// ------------------------------------------------------------
// DirectInput8Create / Imm(IME) / ijl15(Intel JPEG) / Icmp(ping) /
// GetFileVersionInfo 导入转发表；0x697630 起为 comutil（_com_error /
// ConvertStringToBSTR）支撑例程。配套 thunk（ImmGetContext/IcmpSendEcho/
// gethostbyname/ntohl/VerQueryValueA 等）在 missing_tail.cpp 0x69 区。
// ============================================================
// ------------------------------------------------------------
// 0x695BB8 DirectInput8Create
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp_DirectInput8Create（输入系统 API 面）
// attributes: thunk
HRESULT /*stdcall*/ DirectInput8Create(
        HINSTANCE hinst,
        DWORD dwVersion,
        const IID *const riidltf,
        LPVOID *ppvOut,
        LPUNKNOWN punkOuter)
{
  return __imp_DirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}



// ------------------------------------------------------------
// 0x697606 ImmSetCompositionWindow
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp_ImmSetCompositionWindow（nIIme 组合窗口定位 API）
// attributes: thunk
BOOL /*stdcall*/ ImmSetCompositionWindow(HIMC uArg1, LPCOMPOSITIONFORM lpCompForm)
{
  return __imp_ImmSetCompositionWindow(uArg1, lpCompForm);
}



// ------------------------------------------------------------
// 0x697618 ImmGetCandidateListA
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp_ImmGetCandidateListA（nIIme 候选字列表 API）
// attributes: thunk
DWORD /*stdcall*/ ImmGetCandidateListA(HIMC uArg1, DWORD deIndex, LPCANDIDATELIST lpCandList, DWORD dwBufLen)
{
  return __imp_ImmGetCandidateListA(uArg1, deIndex, lpCandList, dwBufLen);
}



// ------------------------------------------------------------
// 0x69762A ijl15_2
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp_ijl15_2（Intel JPEG 库 ijlInit，截屏 JPG 用）
// attributes: thunk
int ijl15_2()
{
  return __imp_ijl15_2();
}



// ------------------------------------------------------------
// 0x697630 sub_697630
// ------------------------------------------------------------
// 【L1】comutil 抛错助手：off_79BE04(hr,0)（noreturn，com_error 路径）【推断】
void /*stdcall*/ /*noreturn*/ sub_697630(int nArg1)
{
  off_79BE04(nArg1, 0);
}



// ------------------------------------------------------------
// 0x697640 sub_697640
// ------------------------------------------------------------
// 【L1】_com_util::ConvertStringToBSTR：MultiByteToWideChar + SysAllocString（>4KB 走堆，带 SEH）
BSTR /*stdcall*/ sub_697640(LPCSTR lpString)
{
  int v1; // ebx
  int v2; // eax
  int v3; // esi
  int v4; // eax
  void *v5; // esp
  uint8_t *pMem; // edi
  DWORD LastError; // eax
  uint16_t v8; // ax
  BSTR v10; // ebx
  uint8_t v11[12]; // [esp+0h] [ebp-30h] BYREF
  uint8_t *pMem2; // [esp+Ch] [ebp-24h]
  int v13; // [esp+10h] [ebp-20h]
  int v14; // [esp+14h] [ebp-1Ch]
  CPPEH_RECORD ms_exc; // [esp+18h] [ebp-18h]

  if ( lpString == nullptr )
    return nullptr;
  v1 = lstrlenA(lpString) + 1;
  v14 = v1;
  v2 = MultiByteToWideChar(0, 0, lpString, v1, nullptr, 0);
  v3 = v2;
  v13 = v2;
  if ( v2 == 0 )
    goto LABEL_11;
  ms_exc.registration.TryLevel = 0;
  v4 = 2 * v2;
  if ( v3 >= 4096 )
  {
    pMem = malloc(2 * v3);
    pMem2 = pMem;
  }
  else
  {
    v5 = alloca(v4);
    ms_exc.old_esp = (DWORD)v11;
    pMem = v11;
    pMem2 = v11;
  }
  ms_exc.registration.TryLevel = -1;
  if ( pMem == nullptr )
    sub_697630(-2147024882);
  if ( MultiByteToWideChar(0, 0, lpString, v1, (LPWSTR)pMem, v3) == 0 )
  {
    if ( v3 >= 4096 )
      free(pMem);
LABEL_11:
    if ( (int)GetLastError() <= 0 )
    {
      LastError = GetLastError();
      sub_697630(LastError);
    }
    v8 = GetLastError();
    sub_697630(v8 | 0x80070000);
  }
  v10 = SysAllocString((const OLECHAR *)pMem);
  if ( v3 >= 4096 )
    free(pMem);
  if ( v10 == nullptr )
    sub_697630(-2147024882);
  return v10;
}



// ------------------------------------------------------------
// 0x6977A0 sub_6977A0
// ------------------------------------------------------------
// 【L1】_com_util::ConvertBSTRToString：WideCharToMultiByte（失败链 → 697630 抛错）
void */*stdcall*/ sub_6977A0(LPCWCH lpWideCharStr)
{
  int v1; // esi
  size_t v2; // eax
  int v3; // edi
  DWORD LastError; // eax
  uint16_t v5; // ax
  void *pMem; // ebx
  unsigned int v8; // eax
  uint32_t v9[7]; // [esp+0h] [ebp-28h] BYREF
  int v10; // [esp+24h] [ebp-4h]

  v9[6] = v9;
  if ( lpWideCharStr == nullptr )
    return nullptr;
  v1 = wcslen(lpWideCharStr) + 1;
  v9[5] = v1;
  v2 = WideCharToMultiByte(0, 0, lpWideCharStr, v1, nullptr, 0, nullptr, nullptr);
  v3 = v2;
  v9[4] = v2;
  if ( v2 == 0 )
  {
    if ( (int)GetLastError() <= 0 )
    {
      LastError = GetLastError();
      sub_697630(LastError);
    }
    v5 = GetLastError();
    sub_697630(v5 | 0x80070000);
  }
  v10 = 0;
  pMem = operator new(v2);
  v10 = -1;
  if ( pMem == nullptr )
    sub_697630(-2147024882);
  if ( WideCharToMultiByte(0, 0, lpWideCharStr, v1, (LPSTR)pMem, v3, nullptr, nullptr) == 0 )
  {
    j__free(pMem);
    if ( (int)GetLastError() > 0 )
      v8 = (uint16_t)GetLastError() | 0x80070000;
    else
      v8 = GetLastError();
    sub_697630(v8);
  }
  return pMem;
}



// ------------------------------------------------------------
// 0x697900 sub_697900
// ------------------------------------------------------------
// 【L1】_com_raise_error：构造 _com_error{wcode,hresult} 并 _CxxThrowException
void /*cdecl*/ /*noreturn*/ sub_697900(int nArg1, int nArg2)
{
  uint32_t pExceptionObject[4]; // [esp+0h] [ebp-10h] BYREF

  pExceptionObject[0] = &_com_error::`vftable';
  pExceptionObject[1] = nArg1;
  pExceptionObject[2] = nArg2;
  pExceptionObject[3] = 0;
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_com_error__);
}



// ------------------------------------------------------------
// 0x697940 sub_697940
// ------------------------------------------------------------
// 【L1】_com_error 构造：vftable + wcode(+4)/hresult(+8)/ErrorInfo AddRef
uint32_t */*thiscall*/ sub_697940(uint32_t *this, int pArg2)
{
  int pObj; // edx

  *this = &_com_error::`vftable';
  *(this + 1) = *(uint32_t *)(pArg2 + 4);
  pObj = *(uint32_t *)(pArg2 + 8);
  *(this + 2) = pObj;
  *(this + 3) = 0;
  if ( pObj != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj + 4))(pObj);
  return this;
}



// ------------------------------------------------------------
// 0x697980 sub_697980
// ------------------------------------------------------------
// 【L1】_com_error 析构：ErrorInfo Release
HLOCAL /*thiscall*/ sub_697980(uint32_t *this)
{
  HLOCAL result; // eax
  void *fld_e3; // esi

  result = (HLOCAL)*(this + 2);
  *this = &_com_error::`vftable';
  if ( result != nullptr )
    result = (HLOCAL)(*(int (/*stdcall*/ **)(HLOCAL))(*(uint32_t *)result + 8))(result);
  fld_e3 = (void *)*(this + 3);
  if ( fld_e3 != nullptr )
    return LocalFree(fld_e3);
  return result;
}



// ------------------------------------------------------------
// 0x6979B0 sub_6979B0
// ------------------------------------------------------------
// 【L1】_com_error scalar deleting destructor（a2&1 → free）
void */*thiscall*/ sub_6979B0(void *Block, char pszArg2)
{
  int pObj; // eax

  pObj = *((uint32_t *)Block + 2);
  *(uint32_t *)Block = &_com_error::`vftable';
  if ( pObj != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj + 8))(pObj);
  if ( *((uint32_t *)Block + 3) != 0 )
    LocalFree(*((HLOCAL *)Block + 3));
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x697A07 sub_697A07
// ------------------------------------------------------------
// 【L1】_com_error::ErrorInfo 读取（this+2 槽）【推断】
uint32_t */*thiscall*/ sub_697A07(uint32_t *this)
{
  sub_401C90(this + 6);
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x697A37 sub_697A37
// ------------------------------------------------------------
// 【L1】_com_error 辅助方法（WCode/Description 路径）【推断】
int /*thiscall*/ sub_697A37(int this)
{
  struct _OSVERSIONINFOA VersionInformation; // [esp+4h] [ebp-20h] BYREF
  int dword_796E502; // [esp+98h] [ebp+74h]

  dword_796E502 = dword_796E50;
  sub_697A07((uint32_t *)this);
  *(uint32_t *)(this + 8) = 0x400000;
  *(uint32_t *)(this + 4) = 0x400000;
  *(uint32_t *)this = 60;
  *(uint8_t *)(this + 12) = 0;
  memset(&VersionInformation, 0, sizeof(VersionInformation));
  VersionInformation.dwOSVersionInfoSize = 148;
  GetVersionExA(&VersionInformation);
  if ( VersionInformation.dwPlatformId == 2 )
  {
    if ( VersionInformation.dwMajorVersion < 5 )
      goto LABEL_9;
  }
  else if ( VersionInformation.dwPlatformId != 1
         || VersionInformation.dwMajorVersion <= 4
         && (VersionInformation.dwMajorVersion != 4 || VersionInformation.dwMinorVersion == 0) )
  {
LABEL_9:
    *(uint32_t *)(this + 16) = 1808;
    *(uint32_t *)(this + 20) = &unk_749D84;
    if ( sub_401CB0((LPCRITICAL_SECTION)(this + 24)) < 0 )
      byte_79C558 = 1;
    return this;
  }
  *(uint8_t *)(this + 12) = 1;
  goto LABEL_9;
}



// ------------------------------------------------------------
// 0x697AE2 IcmpCloseHandle
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp_IcmpCloseHandle（ping 探测；配套 IcmpSendEcho 在 missing_tail）
// attributes: thunk
BOOL /*stdcall*/ IcmpCloseHandle(HANDLE IcmpHandle)
{
  return __imp_IcmpCloseHandle(IcmpHandle);
}



// ------------------------------------------------------------
// 0x697AEE IcmpCreateFile
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp_IcmpCreateFile（ICMP 句柄打开）
// attributes: thunk
HANDLE /*stdcall*/ IcmpCreateFile()
{
  return __imp_IcmpCreateFile();
}



// ------------------------------------------------------------
// 0x697B00 GetFileVersionInfoSizeA
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp_GetFileVersionInfoSizeA（版本查询；配套 VerQueryValueA 在 missing_tail）
// attributes: thunk
DWORD /*stdcall*/ GetFileVersionInfoSizeA(LPCSTR lptstrFilename, LPDWORD lpdwHandle)
{
  return __imp_GetFileVersionInfoSizeA(lptstrFilename, lpdwHandle);
}




// ============================================================
// SECTION 3  字符串键缓存/定时器映射助手（0x697B20-0x6983E0）
// ------------------------------------------------------------
// std::map<std::string,T>（MSVC _Tree 红黑树）实例化方法群 +
// timeGetTime 过期驱逐的"带 TTL 资源缓存"（0x697D00/0x6983E0）。
// 消费方为渲染/声音资源的句柄缓存（【推断】无自证串）。
// ============================================================
// ------------------------------------------------------------
// 0x697B20 sub_697B20
// ------------------------------------------------------------
// 【L1】std::string 键节点清理助手（红黑树节点析构前段）【推断】
void /*thiscall*/ sub_697B20(uint8_t *this)
{
  *(this + 8) = 0;
  *(this + 280) = 1;
}



// ------------------------------------------------------------
// 0x697B30 sub_697B30
// ------------------------------------------------------------
// 【L1】映射节点构造：key=字符串(+8 SSO 布局)/值 a2、a4 入槽，容量 15 直证 std::string
unsigned int /*thiscall*/ sub_697B30(int this, int nArg2, const char *pArg3, int nArg4)
{
  unsigned int result; // eax
  uint16_t *pThis_7; // edi
  char v6; // al

  *(uint32_t *)(this + 4) = nArg2;
  strcpy((char *)(this + 8), pArg3);
  result = strlen((const char *)(this + 8));
  if ( result != 0 )
  {
    if ( *(uint8_t *)(this + strlen((const char *)(this + 8)) + 7) == 92 )
    {
LABEL_7:
      *(uint32_t *)(this + 264) = nArg4;
      return nArg4;
    }
    result = strlen((const char *)(this + 8));
    if ( *(uint8_t *)(result + this + 7) != 47 )
    {
      pThis_7 = (uint16_t *)(this + 7);
      do
      {
        v6 = *((uint8_t *)pThis_7 + 1);
        pThis_7 = (uint16_t *)((char *)pThis_7 + 1);
      }
      while ( v6 != 0 );
      *pThis_7 = 92;
      goto LABEL_7;
    }
  }
  *(uint32_t *)(this + 264) = nArg4;
  return result;
}



// ------------------------------------------------------------
// 0x697BD0 sub_697BD0
// ------------------------------------------------------------
// 【L1】std::map clear：红黑树递归释放（erase 路径）
int /*thiscall*/ sub_697BD0(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 20))(this);
}



// ------------------------------------------------------------
// 0x697BE0 sub_697BE0
// ------------------------------------------------------------
// 【L1】varargs 格式化 → 虚调用 +8（格式化查询/日志入口）【推断】
int sub_697BE0(int nArg1, char *Format, ...)
{
  va_list va; // [esp+Ch] [ebp+Ch] BYREF

  va_start(va, Format);
  vsprintf(byte_9D37C8, Format, va);
  return (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)nArg1 + 4))(nArg1, byte_9D37C8);
}



// ------------------------------------------------------------
// 0x697C10 sub_697C10
// ------------------------------------------------------------
// 【L1】varargs 格式化到全局 byte_9D38C8 → 虚调用 +8（带静态缓冲的格式化入口）
int sub_697C10(int nArg1, int nArg2, char *Format, ...)
{
  va_list va; // [esp+10h] [ebp+10h] BYREF

  va_start(va, Format);
  vsprintf(byte_9D38C8, Format, va);
  return (*(int (/*thiscall*/ **)(int, int, char *))(*(uint32_t *)nArg1 + 8))(nArg1, nArg2, byte_9D38C8);
}



// ------------------------------------------------------------
// 0x697C40 sub_697C40
// ------------------------------------------------------------
// 【L1】std::map<std::string>::lower_bound：memcmp 字典序下降（+45 头哨兵判据）
int */*thiscall*/ sub_697C40(int **this, int pArg2)
{
  int *result; // eax
  int *v3; // ebp
  unsigned int v4; // eax
  const char **v5; // ecx
  const char *v6; // edi
  unsigned int v7; // ebx
  int v8; // ecx
  const char *v9; // esi
  int nCmp; // edx
  bool v11; // sf
  int *v12; // [esp+4h] [ebp-8h]
  unsigned int v13; // [esp+8h] [ebp-4h]
  const char **i; // [esp+10h] [ebp+4h]

  result = *(this + 1);
  v3 = (int *)result[1];
  v12 = result;
  if ( *((uint8_t *)v3 + 45) == 0 )
  {
    v4 = *(uint32_t *)(pArg2 + 20);
    v5 = (const char **)(pArg2 + 4);
    v13 = *(uint32_t *)(pArg2 + 24);
    for ( i = (const char **)(pArg2 + 4); ; v5 = i )
    {
      if ( v13 < 0x10 )
        v6 = (const char *)v5;
      else
        v6 = *v5;
      v7 = v3[8];
      if ( v7 == 0 )
        goto LABEL_14;
      v8 = v3[8];
      if ( v7 >= v4 )
        v8 = v4;
      v9 = (unsigned int)v3[9] < 0x10 ? (const char *)(v3 + 4) : (const char *)v3[4];
      nCmp = memcmp(v9, v6, v8);
      v11 = nCmp < 0;
      if ( nCmp == 0 )
      {
LABEL_14:
        if ( v7 < v4 )
          goto LABEL_17;
        v11 = false;
      }
      if ( v11 )
      {
LABEL_17:
        v3 = (int *)v3[2];
        goto LABEL_19;
      }
      v12 = v3;
      v3 = (int *)*v3;
LABEL_19:
      if ( *((uint8_t *)v3 + 45) != 0 )
        return v12;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x697D00 sub_697D00
// ------------------------------------------------------------
// 【L1】★ TTL 缓存轮询：timeGetTime() 驱逐过期条目（+66=存活时限, +68=条目链, 虚+44 删除回调）
DWORD /*thiscall*/ sub_697D00(DWORD *this)
{
  DWORD result; // eax
  uint32_t *fld_e68; // edi
  uint32_t *v4; // esi
  int fld_e66; // ebp
  uint32_t *v6; // [esp+4h] [ebp-8h] BYREF
  unsigned int v7; // [esp+8h] [ebp-4h]

  result = *(this + 66);
  if ( result != 0 )
  {
    result = timeGetTime();
    v7 = result;
    do
    {
      fld_e68 = (uint32_t *)*(this + 68);
      v4 = (uint32_t *)*fld_e68;
      v6 = (uint32_t *)*fld_e68;
      if ( v6 != fld_e68 )
      {
        fld_e66 = *(this + 66);
        while ( v7 <= fld_e66 + *(uint32_t *)(v4[10] + 4) )
        {
          result = sub_40BEA0(&v6);
          v4 = v6;
          if ( v6 == fld_e68 )
            goto LABEL_9;
        }
        result = (*(int (/*thiscall*/ **)(DWORD *, uint32_t *))(*this + 44))(this, v4);
      }
LABEL_9:
      ;
    }
    while ( v4 != (uint32_t *)*(this + 68) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x697D80 sub_697D80
// ------------------------------------------------------------
// 【L1】map find-or-insert 前置：lower_bound + 键比较（sub_40BF00 = char 比较）
int **/*thiscall*/ sub_697D80(int **this, int **pDwArg2, unsigned int *pDwArg3)
{
  int *v5; // eax
  unsigned int v6; // ecx
  const char *v7; // eax
  int *v9; // [esp+14h] [ebp+8h]

  v5 = sub_697C40(this, (int)pDwArg3);
  v9 = v5;
  if ( v5 == *(this + 1)
    || ((v6 = v5[8], (unsigned int)v5[9] < 0x10) ? (v7 = (const char *)(v5 + 4)) : (v7 = (const char *)v5[4]),
        sub_40BF00((std::_String_base *)pDwArg3, 0, pDwArg3[5], v7, v6) < 0) )
  {
    *pDwArg2 = *(this + 1);
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = v9;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x697DF0 sub_697DF0
// ------------------------------------------------------------
// 【L1】缓存条目构造：key/value/期限入槽，+44=红黑树颜色位，+45=哨兵位
uint32_t */*thiscall*/ sub_697DF0(uint32_t *this, int nArg2, int nArg3, int nArg4, int pArg5, char pszArg6)
{
  char *pThis_3; // edi

  *(this + 1) = nArg3;
  pThis_3 = (char *)(this + 3);
  *this = nArg2;
  *(this + 2) = nArg4;
  *(this + 9) = 15;
  *(this + 8) = 0;
  *((uint8_t *)this + 16) = 0;
  sub_4014D0((std::_String_base *)(this + 3), pArg5, 0, -1);
  *((uint32_t *)pThis_3 + 7) = *(uint32_t *)(pArg5 + 28);
  *((uint8_t *)this + 44) = pszArg6;
  *((uint8_t *)this + 45) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x697E50 sub_697E50
// ------------------------------------------------------------
// 【L1】operator new(0x30) + 条目构造（std::map 节点分配包装）
uint32_t */*stdcall*/ sub_697E50(int nArg1, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  uint32_t *pMem; // esi
  void *v7[9]; // [esp+0h] [ebp-24h] BYREF

  v7[5] = v7;
  pMem = operator new(0x30u);
  v7[4] = pMem;
  v7[8] = (void *)1;
  v7[3] = pMem;
  if ( pMem != nullptr )
    sub_697DF0(pMem, nArg1, nArg2, nArg3, nArg4, pszArg5);
  return pMem;
}



// ------------------------------------------------------------
// 0x697EE0 sub_697EE0
// ------------------------------------------------------------
// 【L1】std::map insert + 红黑树再平衡（"map/set<T> too long" 0x7FFFFFE 容量哨兵直证）
uint32_t */*thiscall*/ sub_697EE0(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
{
  uint32_t *fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
  uint32_t *fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebp
  int v14; // edx
  uint8_t v16[20]; // [esp+8h] [ebp-50h] BYREF
  int v17; // [esp+1Ch] [ebp-3Ch]
  int v18; // [esp+20h] [ebp-38h]
  uint32_t pExceptionObject[13]; // [esp+24h] [ebp-34h] BYREF
  uint32_t *fld_e15; // [esp+68h] [ebp+10h]

  if ( (unsigned int)*(this + 2) >= 0x7FFFFFE )
  {
    v18 = 15;
    v17 = 0;
    v16[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    pExceptionObject[12] = 0;
    sub_401740(pExceptionObject, (int)v16);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_697E50(*(this + 1), (int)pArg4, *(this + 1), nArg5, 0);
  fld_e12 = (uint32_t *)*(this + 1);
  fld_e15 = fld_e1;
  ++*(this + 2);
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = fld_e1 + 1;
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(fld_e1[1] + 44) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 44) != 0 )
        {
          if ( fld_e16 == (uint32_t *)v12[2] )
          {
            fld_e16 = (uint32_t *)*v10;
            sub_442AC0(*v10);
          }
          *(uint8_t *)(fld_e16[1] + 44) = 1;
          *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
          sub_433290(*(uint32_t *)(fld_e16[1] + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 44) != 0 )
      {
        if ( fld_e16 == (uint32_t *)*v12 )
        {
          fld_e16 = (uint32_t *)*v10;
          sub_433290(*v10);
        }
        *(uint8_t *)(fld_e16[1] + 44) = 1;
        *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
        sub_442AC0(*(uint32_t *)(fld_e16[1] + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 44) = 1;
      *(uint8_t *)(v14 + 44) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 44) = 0;
      fld_e16 = *(uint32_t **)(*v10 + 4);
LABEL_21:
      v10 = fld_e16 + 1;
      if ( *(uint8_t *)(fld_e16[1] + 44) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 44) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x698090 sub_698090
// ------------------------------------------------------------
// 【L1】缓存条目删除：虚 +52 通知 + free（erase 收尾）
void /*thiscall*/ sub_698090(void *this, int pArg2)
{
  uint32_t *v2; // edi

  v2 = *(uint32_t **)(pArg2 + 40);
  sub_435140(&pArg2, pArg2);
  (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 52))(this, *v2);
  j__free(v2);
}



// ------------------------------------------------------------
// 0x6980D0 sub_6980D0
// ------------------------------------------------------------
// 【L1】std::map erase + 红黑树删除再平衡（与 697EE0 成对）
int /*thiscall*/ sub_6980D0(int *this, int pArg2, uint32_t *pArg3)
{
  int fld_e1; // ebp
  uint32_t *fld_e12; // ebx
  char v5; // al
  uint32_t *pArg32; // edi
  unsigned int i; // ecx
  unsigned int v8; // ebx
  const char *v9; // eax
  unsigned int v10; // edx
  int v11; // ecx
  const char *v12; // esi
  int nCmp; // eax
  bool v14; // sf
  int v15; // eax
  uint32_t *fld_e122; // esi
  const char *v18; // eax
  char v19; // [esp+10h] [ebp-14h]
  int *pThis; // [esp+14h] [ebp-10h]
  uint32_t *v21; // [esp+20h] [ebp-4h]

  fld_e1 = *(uint32_t *)(*(this + 1) + 4);
  fld_e12 = (uint32_t *)*(this + 1);
  v5 = 1;
  pArg32 = pArg3;
  pThis = this;
  v19 = 1;
  if ( *(uint8_t *)(fld_e1 + 45) == 0 )
  {
    for ( i = pArg3[5]; ; i = pArg3[5] )
    {
      v8 = *(uint32_t *)(fld_e1 + 32);
      v21 = (uint32_t *)fld_e1;
      if ( *(uint32_t *)(fld_e1 + 36) < 0x10u )
        v9 = (const char *)(fld_e1 + 16);
      else
        v9 = *(const char **)(fld_e1 + 16);
      v10 = pArg3[5];
      if ( i < v10 )
        v10 = i;
      if ( v10 == 0 )
        goto LABEL_16;
      v11 = v10;
      if ( v10 >= v8 )
        v11 = *(uint32_t *)(fld_e1 + 32);
      v12 = pArg32[6] < 0x10u ? (const char *)(pArg32 + 1) : (const char *)pArg32[1];
      nCmp = memcmp(v12, v9, v11);
      v14 = nCmp < 0;
      pArg32 = pArg3;
      if ( nCmp == 0 )
      {
LABEL_16:
        if ( v10 >= v8 )
          v15 = v10 != v8;
        else
          v15 = -1;
        v14 = v15 < 0;
      }
      v5 = v14;
      v19 = v14;
      fld_e1 = v14 ? *(uint32_t *)fld_e1 : *(uint32_t *)(fld_e1 + 8);
      if ( *(uint8_t *)(fld_e1 + 45) != 0 )
        break;
    }
    fld_e12 = v21;
    this = pThis;
  }
  fld_e122 = fld_e12;
  pArg3 = fld_e12;
  if ( v5 != 0 )
  {
    if ( fld_e12 == *(uint32_t **)*(this + 1) )
    {
      *(uint32_t *)pArg2 = *sub_697EE0(this, &pArg3, 1, fld_e12, (int)pArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      return pArg2;
    }
    sub_501430(&pArg3);
    fld_e122 = pArg3;
  }
  if ( pArg32[6] < 0x10u )
    v18 = (const char *)(pArg32 + 1);
  else
    v18 = (const char *)pArg32[1];
  if ( sub_40BF00((std::_String_base *)(fld_e122 + 3), 0, fld_e122[8], v18, pArg32[5]) >= 0 )
  {
    *(uint32_t *)pArg2 = fld_e122;
    *(uint8_t *)(pArg2 + 4) = 0;
  }
  else
  {
    *(uint32_t *)pArg2 = *sub_697EE0(pThis, &pArg3, v19, fld_e12, (int)pArg32);
    *(uint8_t *)(pArg2 + 4) = 1;
  }
  return pArg2;
}



// ------------------------------------------------------------
// 0x698250 sub_698250
// ------------------------------------------------------------
// 【L1】全局字符串表查找/登记（unk_9D39C8，资源名归一化）【推断】
int /*cdecl*/ sub_698250(int nArg1, const char *pArg2)
{
  signed int v2; // ebp
  int v3; // esi
  uint32_t *Block2; // edi
  uint32_t *v5; // ebx
  const char *psz; // edx
  char v7; // cl
  char v8; // al
  char v9; // al
  int v11; // [esp+10h] [ebp-20h] BYREF
  void *Block; // [esp+18h] [ebp-18h]
  void *Src; // [esp+1Ch] [ebp-14h]
  int v14; // [esp+20h] [ebp-10h]
  int v15; // [esp+2Ch] [ebp-4h]

  v2 = 0;
  Block = nullptr;
  Src = nullptr;
  v14 = 0;
  v15 = 0;
  v11 = 0;
  sub_430C80(nullptr, 1, (int)&v11);
  v3 = 0;
  Block2 = Block;
  if ( (int)strlen(pArg2) > 0 )
  {
    v5 = Src;
    do
    {
      psz = pArg2;
      v7 = pArg2[v2];
      if ( v7 == 92 || v7 == 47 )
      {
        *(uint8_t *)(v3 + nArg1) = 47;
        v11 = ++v3;
        if ( Block2 == nullptr || v5 - Block2 >= (unsigned int)((v14 - (int)Block2) >> 2) )
        {
          sub_430C80(v5, 1, (int)&v11);
          v5 = Src;
          Block2 = Block;
          goto LABEL_21;
        }
        *v5++ = v3;
        Src = v5;
      }
      else
      {
        if ( v7 != 46 )
          goto LABEL_16;
        v8 = pArg2[v2 + 1];
        if ( v8 != 92 && v8 != 47 )
        {
          if ( pArg2[v2 + 1] == 46 )
          {
            v9 = pArg2[v2 + 2];
            if ( v9 == 92 || v9 == 47 )
            {
              v2 += 2;
              if ( Block2 != nullptr && (unsigned int)(v5 - Block2) > 1 )
              {
                Src = --v5;
                v3 = *(v5 - 1);
              }
              else
              {
                *(uint32_t *)(v3 + nArg1) = 3092014;
                v3 += 3;
                *Block2 = v3;
              }
              goto LABEL_22;
            }
          }
LABEL_16:
          *(uint8_t *)(v3 + nArg1) = tolower(v7);
          ++v3;
LABEL_21:
          psz = pArg2;
          goto LABEL_22;
        }
        ++v2;
      }
LABEL_22:
      ++v2;
    }
    while ( v2 < (int)strlen(psz) );
  }
  *(uint8_t *)(v3 + nArg1) = 0;
  if ( Block2 != nullptr )
    j__free(Block2);
  return nArg1;
}



// ------------------------------------------------------------
// 0x6983E0 sub_6983E0
// ------------------------------------------------------------
// 【L1】★ 带 TTL 的资源缓存查询：key = 前缀(+8)+Src，命中刷新 timeGetTime，未命中虚 +48 加载并 insert
int /*thiscall*/ sub_6983E0(uint32_t *this, int nArg2, char *Src)
{
  int fld_e1; // eax
  int pThis_118; // eax
  void *v6; // eax
  int *pThis_43; // ebp
  int v8; // edi
  int *pMem; // eax
  int *pMem2; // esi
  int v11; // esi
  int *v13[2]; // [esp+8h] [ebp-254h] BYREF
  int v14; // [esp+10h] [ebp-24Ch] BYREF
  void *Block; // [esp+14h] [ebp-248h]
  int v16; // [esp+24h] [ebp-238h]
  unsigned int v17; // [esp+28h] [ebp-234h]
  int *pMem22; // [esp+2Ch] [ebp-230h]
  unsigned int v19; // [esp+30h] [ebp-22Ch] BYREF
  void *v20; // [esp+34h] [ebp-228h]
  int v21; // [esp+44h] [ebp-218h]
  unsigned int v22; // [esp+48h] [ebp-214h]
  char Buffer[512]; // [esp+4Ch] [ebp-210h] BYREF
  int dword_796E502; // [esp+24Ch] [ebp-10h]
  int v25; // [esp+258h] [ebp-4h]

  dword_796E502 = dword_796E50;
  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
  {
    if ( fld_e1 != 1 )
      return 0;
    sprintf(Buffer, "%s%s", (const char *)this + 8, Src);
    return (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*this + 48))(this, Buffer, nArg2);
  }
  v22 = 15;
  v21 = 0;
  LOBYTE(v20) = 0;
  pThis_118 = *((uint8_t *)this + 280);
  v25 = 0;
  if ( (uint8_t)pThis_118 != 0 )
  {
    v6 = (void *)sub_698250((int)&unk_9D39C8, Src);
    sub_4015C0(v6, strlen((const char *)v6));  // 【std::string构造赋值】
  }
  else
  {
    sub_4015C0(Src, strlen(Src));  // 【std::string构造赋值】
  }
  pThis_43 = this + 67;
  sub_697D80((int **)this + 67, v13, &v19);
  if ( v13[0] == (int *)*(this + 68) )
  {
    sprintf(Buffer, "%s%s", (const char *)this + 8, Src);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*this + 48))(this, Buffer, nArg2);
    if ( v8 == 0 )
      goto LABEL_17;
    pMem = (int *)operator new(8u);
    if ( pMem != nullptr )
    {
      *pMem = 0;
      pMem[1] = 0;
      pMem2 = pMem;
    }
    else
    {
      pMem2 = nullptr;
    }
    *pMem2 = v8;
    v17 = 15;
    v16 = 0;
    LOBYTE(Block) = 0;
    sub_4014D0((std::_String_base *)&v14, &v19, 0, -1);
    pMem22 = pMem2;
    LOBYTE(v25) = 1;
    sub_6980D0(pThis_43, (int)v13, &v14);
    if ( v17 >= 0x10 )
      j__free(Block);
  }
  else
  {
    pMem2 = (int *)v13[0][10];
  }
  if ( pMem2 != nullptr )
  {
    pMem2[1] = timeGetTime();
    v11 = *pMem2;
    if ( v22 >= 0x10 )
      j__free(v20);
    return v11;
  }
LABEL_17:
  if ( v22 >= 0x10 )
    j__free(v20);
  return 0;
}




// ============================================================
// SECTION 4  ★ ISocket 网络栈 + CWSBuffer 环形缓冲（0x6985F0-0x698F80）
// ------------------------------------------------------------
// ISocket = Neople 自研 TCP 封装（WSAAsyncSelect 异步模型）。
//   对象布局: +0 vtable / +4 已初始化(BYTE) / +8 已连接(BYTE) / +12 HWND
//     / +16 WSADATA(400B) / +416 IP串[16] / +432 端口 / +436 SOCKET
//     / +440 接收 CWSBuffer* / +444 发送 CWSBuffer*
//   错误码: 0x80000001 未初始化 / 0x80000002 重复初始化 / 0x80000008 new失败
//     / 0x80000050 WSAStartup失败 / 0x80000051 socket失败 / 0x80000053 已连接
//     / 0x80000054 未连接 / 0x80000055 套接字错误 / 0x80000000 一般失败
// 与上层（src/nengine/net_socket.cpp 0x423200/0x423380 packet Begin/Commit）
// 的两级关系:
//   应用层 Begin(type) ──► sub_698D70 申领发送上下文(=发送环读指针)
//                      ──► sub_698C80(hdr,12) 包头入发送环（sub_69DF10 Write）
//   应用层 Commit()    ──► sub_698A50 ISocket::Send 真正 send() 下网卡
//   接收方向: WndProc(0x464 消息) ──► sub_698F80/698CA0 OnSocketMsg
//             ──► sub_698B50 Recv 收入接收环 ──► sub_698C50 取包(sub_69DF70 Read)
//   连接/断开: sub_698DC0 Connect / sub_6989F0 Close("Disconnect %d" 自证)
// CWSBuffer（vtable off_749D94）对象布局: +0 vtable / +4 就绪(BYTE)
//   / +8 缓冲基址 / +12 容量 / +16 读指针 / +20 写指针；
//   其方法体在 SECTION 8（0x69DE60-0x69DF70）。
// ============================================================
// ------------------------------------------------------------
// 0x6985F0 sub_6985F0
// ------------------------------------------------------------
// 【L1】CWSBuffer 构造：vtable=off_749D94，调 sub_69DE60 清零五字段
// （+4 就绪/+8 基址/+12 容量/+16 读/+20 写）。ISocket 在 sub_698870 中
// operator new(0x18) 后构造两个实例：+440 接收环、+444 发送环。
uint8_t */*thiscall*/ sub_6985F0(uint8_t *this)
{
  *(this + 4) = 0;
  *(uint32_t *)this = off_749D94;
  sub_69DE60();
  return this;
}



// ------------------------------------------------------------
// 0x698640 sub_698640
// ------------------------------------------------------------
// 【L1】CWSBuffer scalar deleting destructor（调 sub_698670 析构后按 a2&1 free）
void */*thiscall*/ sub_698640(void *Block, char pszArg2)
{
  sub_698670();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x698670 sub_698670
// ------------------------------------------------------------
// 【L1】CWSBuffer 析构体：释放缓冲（vtable 槽 1，Cleanup 经 (**v2)(v2,1) 虚调用到达）
int /*thiscall*/ sub_698670(uint8_t *this)
{
  int result; // eax

  *(uint32_t *)this = off_749D94;
  result = sub_69DEE0();
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6986C0 ??1?$_AutoDeleter@U_TaskProcHandle@details@Concurrency@@@details@Concurrency@@QAE@XZ
// ------------------------------------------------------------
// 【L1】Concurrency::_AutoDeleter<_TaskProcHandle> 析构（CRT/PPL 符号混入，与本区无关，计划内保留原名）
int /*thiscall*/ Concurrency::details::_AutoDeleter<Concurrency::details::_TaskProcHandle>::~_AutoDeleter<Concurrency::details::_TaskProcHandle>(
        uint32_t *this)
{
  int (/*thiscall*/ ***v1)(uint32_t, int); // ecx
  int result; // eax

  v1 = (int (/*thiscall*/ ***)(uint32_t, int))*this;
  if ( v1 != nullptr )
    return (**v1)(v1, 1);
  return result;
}



// ------------------------------------------------------------
// 0x6986D0 sub_6986D0
// ------------------------------------------------------------
// 【L1】std::allocator<char> 式助手（返回 this）【推断】
char */*thiscall*/ sub_6986D0(char *this)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &off_749D98;
  *((uint32_t *)this + 110) = 0;
  *((uint32_t *)this + 111) = 0;
  *(this + 8) = 0;
  memset(this + 16, 0, 0x190u);
  *((uint32_t *)this + 104) = 0;
  *((uint32_t *)this + 105) = 0;
  *((uint32_t *)this + 106) = 0;
  *((uint32_t *)this + 107) = 0;
  *((uint32_t *)this + 108) = 0;
  *((uint32_t *)this + 109) = 0;
  *((uint32_t *)this + 3) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x698720 sub_698720
// ------------------------------------------------------------
// 【L1】CWSBuffer 析构前段（被 698840 调用；与 698670 同族另一实例布局）
int /*thiscall*/ sub_698720(char *this)
{
  int result; // eax
  int (/*thiscall*/ ***pThis_6F)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_6E)(uint32_t, int); // ecx

  *(uint32_t *)this = &off_749D98;
  result = 0;
  *(this + 8) = 0;
  memset(this + 16, 0, 0x190u);
  *((uint32_t *)this + 104) = 0;
  *((uint32_t *)this + 105) = 0;
  *((uint32_t *)this + 106) = 0;
  *((uint32_t *)this + 107) = 0;
  pThis_6F = *((int (/*thiscall*/ ****)(uint32_t, int))this + 111);
  *((uint32_t *)this + 108) = 0;
  *((uint32_t *)this + 109) = 0;
  *((uint32_t *)this + 3) = 0;
  *(this + 4) = 0;
  if ( pThis_6F != nullptr )
    result = (**pThis_6F)(pThis_6F, 1);
  pThis_6E = *((int (/*thiscall*/ ****)(uint32_t, int))this + 110);
  if ( pThis_6E != nullptr )
    result = (**pThis_6E)(pThis_6E, 1);
  *(this + 4) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
  return result;
}



// ------------------------------------------------------------
// 0x6987C0 sub_6987C0
// ------------------------------------------------------------
// 【L1】★ ISocket::Cleanup：WSACleanup() + 释放收发两环（虚调用槽1）+ 清字段
// +8 已连接=0、memset(+16,0x190) 清 WSADATA、+416..436 清零。返回 1。
int /*thiscall*/ sub_6987C0(int this)
{
  void (/*thiscall*/ ***pThis_1B8)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_1BC)(uint32_t, int); // ecx

  pThis_1B8 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 440);
  if ( pThis_1B8 != nullptr )
    (**pThis_1B8)(pThis_1B8, 1);
  *(uint32_t *)(this + 440) = 0;
  pThis_1BC = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 444);
  if ( pThis_1BC != nullptr )
    (**pThis_1BC)(pThis_1BC, 1);
  *(uint32_t *)(this + 444) = 0;
  WSACleanup();
  *(uint8_t *)(this + 8) = 0;
  memset((void *)(this + 16), 0, 0x190u);
  *(uint32_t *)(this + 416) = 0;
  *(uint32_t *)(this + 420) = 0;
  *(uint32_t *)(this + 424) = 0;
  *(uint32_t *)(this + 428) = 0;
  *(uint32_t *)(this + 432) = 0;
  *(uint32_t *)(this + 436) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint8_t *)(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x698840 sub_698840
// ------------------------------------------------------------
// 【L1】CWSBuffer deleting destructor（调 sub_698720，a2&1 → j__free）
char */*thiscall*/ sub_698840(char *Block, char pszArg2)
{
  sub_698720(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x698870 sub_698870
// ------------------------------------------------------------
// 【L1】★ ISocket::Init(hwnd, Size)：网络栈启动
// 流程: 重复初始化检查(+4→0x80000002) → 存 HWND(+12) → operator new(0x18)x2
// 构造接收环(+440)/发送环(+444) → 两次 sub_69DE80(Size) 分配环形缓冲 →
// WSAStartup(0x202) 成功置 +4=1 返回 1；
// 失败: WSA→0x80000050，分配失败→sub_6987C0 清理后透传/0x80000008。
int /*thiscall*/ sub_698870(int this, void *Block, size_t Size)
{
  uint8_t *pMem; // eax
  uint8_t *v6; // edi
  void (/*thiscall*/ ***pThis_1BC)(uint32_t, int); // ecx
  uint8_t *pMem2; // eax
  uint8_t *v9; // edi
  void (/*thiscall*/ ***pThis_1B8)(uint32_t, int); // ecx
  int v11; // edi

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  *(uint32_t *)(this + 12) = Block;
  pMem = operator new(0x18u);
  v6 = nullptr;
  if ( pMem != nullptr )
    v6 = sub_6985F0(pMem);
  pThis_1BC = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 444);
  if ( v6 != (uint8_t *)pThis_1BC && pThis_1BC != nullptr )
    (**pThis_1BC)(pThis_1BC, 1);
  *(uint32_t *)(this + 444) = v6;
  pMem2 = operator new(0x18u);
  if ( pMem2 != nullptr )
    v9 = sub_6985F0(pMem2);
  else
    v9 = nullptr;
  pThis_1B8 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 440);
  if ( v9 != (uint8_t *)pThis_1B8 && pThis_1B8 != nullptr )
    (**pThis_1B8)(pThis_1B8, 1);
  *(uint32_t *)(this + 440) = v9;
  if ( *(uint32_t *)(this + 444) != 0 && v9 != nullptr )
  {
    v11 = sub_69DE80(Size);
    if ( v11 >= 0 && (v11 = sub_69DE80(Size)) >= 0 )
    {
      if ( WSAStartup(0x202u, (LPWSADATA)(this + 16)) >= 0 )
      {
        *(uint8_t *)(this + 4) = 1;
        return 1;
      }
      else
      {
        return -2147483568;
      }
    }
    else
    {
      sub_6987C0(this);
      return v11;
    }
  }
  else
  {
    sub_6987C0(this);
    return -2147483640;
  }
}



// ------------------------------------------------------------
// 0x6989F0 sub_6989F0
// ------------------------------------------------------------
// 【L1】★ ISocket::Close：断开连接（"Disconnect %d" 自证串）
// 流程: off_77F3FC 日志 → closesocket(+436) → SOCKET=0 →
// 发送环(+444)与接收环(+440)读/写指针(+16/+20)清零 → +8 已连接=0。返回 1。
int /*thiscall*/ sub_6989F0(int this)
{
  int fld_1BC; // eax
  int fld_1B8; // eax

  if ( *(uint32_t *)(this + 436) != 0 )
  {
    off_77F3FC("Disconnect %d", *(uint32_t *)(this + 436));
    closesocket(*(uint32_t *)(this + 436));
    *(uint32_t *)(this + 436) = 0;
  }
  fld_1BC = *(uint32_t *)(this + 444);
  *(uint32_t *)(fld_1BC + 16) = 0;
  *(uint32_t *)(fld_1BC + 20) = 0;
  fld_1B8 = *(uint32_t *)(this + 440);
  *(uint32_t *)(fld_1B8 + 16) = 0;
  *(uint32_t *)(fld_1B8 + 20) = 0;
  *(uint8_t *)(this + 8) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x698A50 sub_698A50
// ------------------------------------------------------------
// 【L1】★ ISocket::Send：把发送环数据真正 send() 下网卡
// （自证串 "ISocket::Send() : nWOULD_BLOCK_COUNT > 10000"，IDA 串名 aIsocketSendNwo）
// 流程: 未初始化→0x80000001 / 未连接→0x80000054；
// 待发 = 写指针(+20)-读指针(+16)（对 +444 发送环）；v4==0 直接返回 1；
// send() 循环推进读指针，满圈(+16==+20)归零对；
// WSAEWOULDBLOCK(10035) → Sleep(1) 重试计数；
// >10000 次 → 打日志返回 0x80000000；
// 其他错误 → 打 "ISocket::Secv() : SocketError %d"（原版串拼写如此，实为 Send）
// → sub_6989F0 Close → 返回 0x80000055。上层调用方: net_socket.cpp Commit()。
int /*thiscall*/ sub_698A50(int this)
{
  unsigned int v3; // edi
  unsigned int fld_1BC; // ebx
  int fld_1B4; // eax
  int fld_1BC2; // ecx
  int Error; // eax
  int v8; // [esp+4h] [ebp-4h]

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( *(uint8_t *)(this + 8) == 0 )
    return -2147483564;
  v3 = 0;
  fld_1BC = *(uint32_t *)(*(uint32_t *)(this + 444) + 20) - *(uint32_t *)(*(uint32_t *)(this + 444) + 16);
  v8 = 0;
  if ( fld_1BC == 0 )
    return 1;
  while ( 1 )
  {
    if ( v8 > 10000 )
    {
      off_77F3FC(aIsocketSendNwo);
      return 0x80000000;
    }
    fld_1B4 = send(
           *(uint32_t *)(this + 436),
           (const char *)(*(uint32_t *)(*(uint32_t *)(this + 444) + 8) + *(uint32_t *)(*(uint32_t *)(this + 444) + 16)),
           fld_1BC - v3,
           0);
    if ( fld_1B4 != 0 )
      break;
LABEL_13:
    if ( v3 >= fld_1BC )
      return 1;
  }
  if ( fld_1B4 != -1 )
  {
    fld_1BC2 = *(uint32_t *)(this + 444);
    *(uint32_t *)(fld_1BC2 + 16) += fld_1B4;
    v3 += fld_1B4;
    if ( *(uint32_t *)(fld_1BC2 + 16) == *(uint32_t *)(fld_1BC2 + 20) )
    {
      *(uint32_t *)(fld_1BC2 + 16) = 0;
      *(uint32_t *)(fld_1BC2 + 20) = 0;
    }
    goto LABEL_13;
  }
  if ( WSAGetLastError() == 10035 )
  {
    Sleep(1u);
    ++v8;
    goto LABEL_13;
  }
  Error = WSAGetLastError();
  off_77F3FC("!!!!!!!!!!!!!!!ISocket::Secv() : SocketError %d", Error);
  sub_6989F0(this);
  return -2147483563;
}



// ------------------------------------------------------------
// 0x698B50 sub_698B50
// ------------------------------------------------------------
// 【L1】★ ISocket::Recv：ioctlsocket(FIONREAD=0x4004667F) 查可读量并 recv() 入接收环
// 流程: 未初始化→0x80000001 / 未连接→0x80000054；FIONREAD==0 → 返回 0；
// recv 循环写入 +440 环（基址+8 + 写偏移+20，容量+12 封顶），累计 >= argp 止；
// WSAEWOULDBLOCK → 返回 0（正常轮询路径）；其他错误 → 打
// "ISocket::Recv() : SocketError %d" → Close → 0x80000055。
u_long /*thiscall*/ sub_698B50(int this)
{
  u_long result; // eax
  SOCKET fld_1B4; // ecx
  u_long v4; // edi
  int fld_1B42; // eax
  int Error; // eax
  u_long argp; // [esp+4h] [ebp-4h] BYREF

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( *(uint8_t *)(this + 8) == 0 )
    return -2147483564;
  fld_1B4 = *(uint32_t *)(this + 436);
  v4 = 0;
  argp = 0;
  if ( ioctlsocket(fld_1B4, 1074030207, &argp) == -1 )
  {
    sub_6989F0(this);
    return -2147483563;
  }
  else if ( argp != 0 )
  {
    while ( 1 )
    {
      fld_1B42 = recv(
             *(uint32_t *)(this + 436),
             (char *)(*(uint32_t *)(*(uint32_t *)(this + 440) + 8) + *(uint32_t *)(*(uint32_t *)(this + 440) + 20)),
             *(uint32_t *)(*(uint32_t *)(this + 440) + 12) - *(uint32_t *)(*(uint32_t *)(this + 440) + 20),
             0);
      if ( fld_1B42 == -1 )
        break;
      v4 += fld_1B42;
      *(uint32_t *)(*(uint32_t *)(this + 440) + 20) += fld_1B42;
      result = argp;
      if ( v4 >= argp )
        return result;
    }
    if ( WSAGetLastError() == 10035 )
    {
      return 0;
    }
    else
    {
      Error = WSAGetLastError();
      off_77F3FC("!!!!!!!!!!!!!!!ISocket::Recv() : SocketError %d", Error);
      sub_6989F0(this);
      return -2147483563;
    }
  }
  else
  {
    return 0;
  }
}



// ------------------------------------------------------------
// 0x698C50 sub_698C50
// ------------------------------------------------------------
// 【L1】★ ISocket::取包：激活且已连接时 sub_69DF70(接收环, len) = Read/出队
// （读指针 +16 前进 len，读完归零对；越界写 SocketLog.log "Devector Error"）。
int /*thiscall*/ sub_698C50(uint8_t *this, int nArg2)
{
  if ( *(this + 4) != 0 && *(this + 8) != 0 )
    return sub_69DF70(nArg2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x698C80 sub_698C80
// ------------------------------------------------------------
// 【L1】★ ISocket::发写入队：激活时 sub_69DF10(len, buf, size) = Write/入队；
// 上层 net_socket.cpp 的 packet_send_begin 用它入 12 字节包头框架。
int /*thiscall*/ sub_698C80(uint8_t *this, int nArg2, int nArg3)
{
  if ( *(this + 4) != 0 )
    return sub_69DF10(nArg2, nArg3);
  else
    return -2147483647;
}



// ------------------------------------------------------------
// 0x698CA0 sub_698CA0
// ------------------------------------------------------------
// 【L1】★ ISocket::OnSocketMsg：0x464 自定义窗口消息处理器（WSAAsyncSelect 回调）
// a5 低字=事件: 16=FD_CONNECT → 高字错误码非 0 → Close+日志；
// 成功 → 重新 WSAAsyncSelect(+436, HWND+12, 0x464, 35=FD_READ|FD_WRITE|FD_CLOSE)
// 并置 +8=1（已连接）；32=FD_CLOSE → 日志+Close 返回 1；其他事件忽略。
unsigned int /*thiscall*/ sub_698CA0(int this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int Error; // eax
  int v8; // eax

  if ( (uint16_t)nArg5 != 16 )
  {
    if ( (uint16_t)nArg5 == 32 )
    {
      Error = WSAGetLastError();
      off_77F3FC((char *)&byte_749EA8, Error);
      sub_6989F0(this);
      return 1;
    }
    return 1;
  }
  if ( HIWORD(nArg5) != 0 )
  {
    sub_6989F0(this);
    off_77F3FC((char *)&byte_749E58, HIWORD(nArg5));
    return 1;
  }
  if ( WSAAsyncSelect(*(uint32_t *)(this + 436), *(HWND *)(this + 12), 0x464u, 35) == -1 )
  {
    v8 = WSAGetLastError();
    off_77F3FC((char *)&byte_749E80, v8);
    sub_6989F0(this);
    return 0x80000000;
  }
  else
  {
    *(uint8_t *)(this + 8) = 1;
    return 1;
  }
}



// ------------------------------------------------------------
// 0x698D70 sub_698D70
// ------------------------------------------------------------
// 【L1】★ ISocket::GetSendReadPtr：返回发送环(+444)当前读位置（基址+8+读偏移+16）；
// 即 net_socket.cpp 注释中的"申领发送上下文"（12 字节包头写入起点）。
int /*thiscall*/ sub_698D70(uint32_t *this)
{
  return *(uint32_t *)(*(this + 111) + 8) + *(uint32_t *)(*(this + 111) + 16);
}



// ------------------------------------------------------------
// 0x698D80 sub_698D80
// ------------------------------------------------------------
// 【L1】★ ISocket::GetRecvReadPtr：返回接收环(+440)当前读位置（基址+8+读偏移+16）
int /*thiscall*/ sub_698D80(uint32_t *this)
{
  return *(uint32_t *)(*(this + 110) + 8) + *(uint32_t *)(*(this + 110) + 16);
}



// ------------------------------------------------------------
// 0x698D90 sub_698D90
// ------------------------------------------------------------
// 【L1】★ ISocket::IsRecvPending：已初始化 && 接收环就绪(+4) && 读(+16)<写(+20)
bool /*thiscall*/ sub_698D90(int this)
{
  int fld_1B8; // eax

  return *(uint8_t *)(this + 4) != 0
      && *(uint8_t *)((fld_1B8 = *(uint32_t *)(this + 440)) + 4) != 0
      && *(uint32_t *)(fld_1B8 + 16) < *(uint32_t *)(fld_1B8 + 20);
}



// ------------------------------------------------------------
// 0x698DC0 sub_698DC0
// ------------------------------------------------------------
// 【L1】★ ISocket::Connect(ip, port)：异步 TCP 连接（docs/13 网络层衔接）
// 流程: 未初始化→0x80000001 / 已连接→0x80000053；
// strcpy IP 到 +416、端口入 +432 → socket(AF_INET=2, SOCK_STREAM=1, IPPROTO_TCP=6)
// → setsockopt(SOL_SOCKET=0xFFFF, SO_SNDBUF=4097, 100000)
// → setsockopt(SO_RCVBUF=4098, 0x989680【原值直写，数值 0x989680=10,000,000，推断 10MB】)
// → setsockopt(optname=1【原值，WinSock 语义 SO_DEBUG】, 1)
// → WSAAsyncSelect(0x464 自定义消息, FD_CONNECT=16)
// → inet_addr(+416)+htons(+432) → connect()；
// connect 返回 -1 时仅取 WSAGetLastError 不视为失败（异步模型：结果经
// 0x464/FD_CONNECT 回调 698CA0）。socket 失败→0x80000051。
int /*thiscall*/ sub_698DC0(int this, int optval, int nArg3)
{
  char *v5; // eax
  int pThis_1A0; // edx
  char v7; // cl
  int v8; // eax
  u_short fld_1B0; // ax
  unsigned int pThis_1A02; // eax
  SOCKET fld_1B4; // [esp-1Ch] [ebp-34h]
  SOCKET fld_1B42; // [esp-1Ch] [ebp-34h]
  SOCKET fld_1B43; // [esp-10h] [ebp-28h]
  struct sockaddr name; // [esp+4h] [ebp-14h] BYREF
  int dword_796E502; // [esp+14h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( *(uint8_t *)(this + 8) != 0 )
    return -2147483565;
  v5 = (char *)optval;
  pThis_1A0 = this + 416 - optval;
  do
  {
    v7 = *v5;
    v5[pThis_1A0] = *v5;
    ++v5;
  }
  while ( v7 != 0 );
  *(uint32_t *)(this + 432) = nArg3;
  v8 = socket(2, 1, 6);
  *(uint32_t *)(this + 436) = v8;
  if ( v8 >= 0 )
  {
    optval = 100000;
    setsockopt(v8, 0xFFFF, 4097, (const char *)&optval, 4);
    fld_1B4 = *(uint32_t *)(this + 436);
    optval = (int)&unk_989680;
    setsockopt(fld_1B4, 0xFFFF, 4098, (const char *)&optval, 4);
    fld_1B42 = *(uint32_t *)(this + 436);
    nArg3 = 1;
    if ( setsockopt(fld_1B42, 0xFFFF, 1, (const char *)&nArg3, 4) == -1 )
    {
      sub_6989F0(this);
      return -2147483647;
    }
    else if ( WSAAsyncSelect(*(uint32_t *)(this + 436), *(HWND *)(this + 12), 0x464u, 16) == -1 )
    {
      return 0x80000000;
    }
    else
    {
      fld_1B0 = *(uint16_t *)(this + 432);
      memset(&name.sa_data[2], 0, 12);
      name.sa_family = 2;
      *(uint16_t *)name.sa_data = htons(fld_1B0);
      pThis_1A02 = inet_addr((const char *)(this + 416));
      fld_1B43 = *(uint32_t *)(this + 436);
      *(uint32_t *)&name.sa_data[2] = pThis_1A02;
      if ( connect(fld_1B43, &name, 16) == -1 )
        WSAGetLastError();
      return 1;
    }
  }
  else
  {
    sub_6989F0(this);
    return -2147483567;
  }
}



// ------------------------------------------------------------
// 0x698F80 sub_698F80
// ------------------------------------------------------------
// 【L1】ISocket::OnSocketMsg 转发桩：原参数尾调 sub_698CA0（第二个入口）
unsigned int /*thiscall*/ sub_698F80(int this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  return sub_698CA0(this, nArg2, nArg3, nArg4, nArg5);
}




// ============================================================
// SECTION 5  UI 基础设施：光标闪烁/子系统注册/截屏/数字标签/CNUIObject
//            （0x698F90-0x69AB00）
// ------------------------------------------------------------
// ·0x698F90-0x699070 光标闪烁节拍（dword_79D100[16] 时间表，NCEdit +132 内嵌）；
// ·0x6990D0-0x6992C0 子系统注册表（按 bank 登记条目，【推断】）；
// ·0x6993C0-0x69A110 截屏器（单例 dword_9D3BDC/9D3BE0）+ 数字标签；
// ·0x69A4D0-0x69AB00 CNUIObject 基类（渲染/命中/拖动递归）。
// 全局: dword_9D3BC8 渲染器(vt+72 Begin/+76 End/+80 DrawText, sub_416430)
//       dword_9D3BD8 字体引擎(vt+16 测宽/+24 适配截断)
//       dword_89D26C 鼠标消息态(1=按下/8/16)  dword_9D3BCC 控件 id 分配器
//       dword_79BE3C/40/44/54/58/5C/60/64 按下/拖动/悬停/焦点控件 id 组
// ============================================================
// ------------------------------------------------------------
// 0x698F90 sub_698F90
// ------------------------------------------------------------
// 【L1】光标闪烁对象·焦点获得：+12 基准有效(+13=1)时记录锚点
// +16 = a3 - dword_79D100[bank(+8)]；拖动分支(+14)记 +20=a3、+24=a2。
// NCEdit 于 +132 内嵌此对象（sub_69AB90 Create 时 sub_698F90(this+132,1,0)）。
char /*thiscall*/ sub_698F90(int this, int nArg2, int nArg3)  // 【clock_set_countdown(clk, duration=a2, star…】
{
  char result; // al

  result = *(uint8_t *)(this + 12);
  if ( result != 0 )
  {
    result = *(uint8_t *)(this + 13);
    if ( result == 0 )
    {
      result = *(uint8_t *)(this + 14);
      *(uint8_t *)(this + 13) = 1;
      if ( result != 0 )
        *(uint32_t *)(this + 20) = nArg3;
      else
        *(uint32_t *)(this + 16) = nArg3 - dword_79D100[*(uint32_t *)(this + 8)];
      *(uint32_t *)(this + 24) = nArg2;
      if ( result != 0 )
        *(uint32_t *)(this + 20) = nArg3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x698FE0 sub_698FE0
// ------------------------------------------------------------
// 【L1】光标闪烁·焦点丢失：清 +14 并把 +20 锚点换算回 +16（- dword_79D100[bank]）
char /*thiscall*/ sub_698FE0(int this)  // 【clock_unfreeze(clk)】
{
  int v1; // eax
  int fld_8; // edx
  int fld_14; // eax

  LOBYTE(v1) = *(uint8_t *)(this + 14);
  if ( (uint8_t)v1 != 0 )
  {
    fld_8 = *(uint32_t *)(this + 8);
    fld_14 = *(uint32_t *)(this + 20);
    *(uint8_t *)(this + 14) = 0;
    v1 = fld_14 - dword_79D100[fld_8];
    *(uint32_t *)(this + 16) = v1;
  }
  return v1;
}



// ------------------------------------------------------------
// 0x699000 sub_699000
// ------------------------------------------------------------
// 【L1】光标闪烁·取当前节拍：+14 置位返回 +20，否则 +16 + dword_79D100[bank]
int /*thiscall*/ sub_699000(int this)  // 【clock_now(clk)】
{
  if ( *(uint8_t *)(this + 12) == 0 || *(uint8_t *)(this + 13) == 0 )
    return 0;
  if ( *(uint8_t *)(this + 14) != 0 )
    return *(uint32_t *)(this + 20);
  return *(uint32_t *)(this + 16) + dword_79D100[*(uint32_t *)(this + 8)];
}



// ------------------------------------------------------------
// 0x699030 sub_699030
// ------------------------------------------------------------
// 【L1】光标闪烁·刷新：按 +16+dword_79D100[bank] 重算 +20 并置 +14=1
char /*thiscall*/ sub_699030(int this)  // 【clock_freeze(clk)】
{
  int fld_10; // eax

  LOBYTE(fld_10) = *(uint8_t *)(this + 14);
  if ( (uint8_t)fld_10 == 0 )
  {
    if ( *(uint8_t *)(this + 12) != 0 && *(uint8_t *)(this + 13) != 0 )
    {
      fld_10 = *(uint32_t *)(this + 16) + dword_79D100[*(uint32_t *)(this + 8)];
      *(uint32_t *)(this + 20) = fld_10;
      *(uint8_t *)(this + 14) = 1;
    }
    else
    {
      *(uint32_t *)(this + 20) = 0;
      *(uint8_t *)(this + 14) = 1;
      LOBYTE(fld_10) = 0;
    }
  }
  return fld_10;
}



// ------------------------------------------------------------
// 0x699070 sub_699070
// ------------------------------------------------------------
// 【L1】光标闪烁·换 bank：a2<0x10 时迁移基准（+16/+20 换算保持相位）
void /*thiscall*/ sub_699070(int this, unsigned int uArg2)  // 【clock_bind_domain(clk, newDomainId)】
{
  int fld_14; // eax
  bool fld_E; // zf

  if ( uArg2 < 0x10 )
  {
    if ( *(uint8_t *)(this + 12) != 0 && *(uint8_t *)(this + 13) != 0 )
    {
      if ( *(uint8_t *)(this + 14) != 0 )
        fld_14 = *(uint32_t *)(this + 20);
      else
        fld_14 = *(uint32_t *)(this + 16) + dword_79D100[*(uint32_t *)(this + 8)];
    }
    else
    {
      fld_14 = 0;
    }
    fld_E = *(uint8_t *)(this + 14) == 0;
    *(uint32_t *)(this + 8) = uArg2;
    if ( fld_E )
      *(uint32_t *)(this + 16) = fld_14 - dword_79D100[uArg2];
    else
      *(uint32_t *)(this + 20) = fld_14;
  }
}



// ------------------------------------------------------------
// 0x6990D0 sub_6990D0
// ------------------------------------------------------------
// 【L1】子系统注册表·激活：置 bank id(+8) 并 +4=1【推断】
int /*thiscall*/ sub_6990D0(int this, int nArg2)
{
  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  *(uint32_t *)(this + 8) = nArg2;
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x699100 sub_699100
// ------------------------------------------------------------
// 【L1】子系统注册表·清空条目（步进 4/28 双数组，std::string 赋空串释放）【推断】
int /*thiscall*/ sub_699100(int this)
{
  int fld_14; // esi
  int fld_24; // edi
  int fld_18; // eax
  char v6[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  int v8; // [esp+1Ch] [ebp-18h]
  unsigned int v9; // [esp+20h] [ebp-14h]
  int dword_796E502; // [esp+24h] [ebp-10h]
  int v11; // [esp+30h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  fld_14 = *(uint32_t *)(this + 20);
  fld_24 = *(uint32_t *)(this + 36);
  if ( fld_14 != *(uint32_t *)(this + 24) )
  {
    do
    {
      v9 = 15;
      v8 = 0;
      LOBYTE(Block) = 0;
      sub_4014D0((std::_String_base *)v6, fld_24, 0, -1);
      v11 = 0;
      sub_419550((char)v6, 0);
      v11 = -1;
      if ( v9 >= 0x10 )
        j__free(Block);
      fld_18 = *(uint32_t *)(this + 24);
      fld_14 += 4;
      fld_24 += 28;
      v9 = 15;
      v8 = 0;
      LOBYTE(Block) = 0;
    }
    while ( fld_14 != fld_18 );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x6991D0 sub_6991D0
// ------------------------------------------------------------
// 【L1】子系统注册表·释放内存（free 指针数组 + sub_4166A0 清第二数组）【推断】
void /*thiscall*/ sub_6991D0(int this)
{
  int fld_24; // eax
  int pThis_20; // esi

  *(uint32_t *)(this + 8) = 0;
  if ( *(uint32_t *)(this + 20) != 0 )
    j__free(*(void **)(this + 20));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  fld_24 = *(uint32_t *)(this + 36);
  pThis_20 = this + 32;
  if ( fld_24 != 0 )
  {
    sub_4166A0(fld_24, *(uint32_t *)(pThis_20 + 8));
    j__free(*(void **)(pThis_20 + 4));
  }
  *(uint32_t *)(pThis_20 + 4) = 0;
  *(uint32_t *)(pThis_20 + 8) = 0;
  *(uint32_t *)(pThis_20 + 12) = 0;
}



// ------------------------------------------------------------
// 0x699230 sub_699230
// ------------------------------------------------------------
// 【L1】子系统注册表·销毁全部：逐项虚调用槽1释放后 free 数组、+4=0【推断】
int /*thiscall*/ sub_699230(int this)
{
  uint32_t *i; // edi
  int fld_24; // eax

  for ( i = *(uint32_t **)(this + 20); i != *(uint32_t **)(this + 24); ++i )
  {
    if ( *i != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*i)(*i, 1);
    *i = 0;
  }
  *(uint32_t *)(this + 8) = 0;
  if ( *(uint32_t *)(this + 20) != 0 )
    j__free(*(void **)(this + 20));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  fld_24 = *(uint32_t *)(this + 36);
  if ( fld_24 != 0 )
  {
    sub_4166A0(fld_24, *(uint32_t *)(this + 40));
    j__free(*(void **)(this + 36));
  }
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint8_t *)(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x6992C0 sub_6992C0
// ------------------------------------------------------------
// 【L1】子系统注册表·登记：new(0x68)+sub_419480(bank) 构造，拷贝名称 Src【推断】
int /*thiscall*/ sub_6992C0(int this, void *Src)
{
  void *pMem; // eax
  char *fld_8; // eax
  uint8_t v6[4]; // [esp+4h] [ebp-2Ch] BYREF
  void *Block; // [esp+8h] [ebp-28h]
  int v8; // [esp+18h] [ebp-18h]
  unsigned int v9; // [esp+1Ch] [ebp-14h]
  void *pMem2; // [esp+20h] [ebp-10h] BYREF
  int v11; // [esp+2Ch] [ebp-4h]

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  pMem = operator new(0x68u);
  pMem2 = pMem;
  v11 = 0;
  if ( pMem != nullptr )
    fld_8 = sub_419480((char *)pMem, *(uint32_t *)(this + 8));
  else
    fld_8 = nullptr;
  v11 = -1;
  pMem2 = fld_8;
  if ( fld_8 == nullptr )
    return -2147483640;
  sub_4BC260(&pMem2);
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  v11 = 1;
  sub_416C40(v6);
  if ( v9 >= 0x10 )
    j__free(Block);
  return 1;
}



// ------------------------------------------------------------
// 0x6993C0 sub_6993C0
// ------------------------------------------------------------
// 【L1】截屏·探测空闲序号：sprintf("%s%05d", 前缀, i) 后缀 .BMP/.JPG，
// CreateFileA(GENERIC_READ, OPEN_EXISTING) 探测，两者都不存在即返回 i。
int /*stdcall*/ sub_6993C0(const char *pArg1)
{
  char v1; // bl
  char *pBuf2; // edi
  char v3; // al
  HANDLE FileA; // eax
  char *pBuf; // edi
  char v6; // al
  HANDLE v7; // eax
  int i; // [esp+Ch] [ebp-108h] BYREF
  CHAR FileName[256]; // [esp+10h] [ebp-104h] BYREF
  int dword_796E502; // [esp+110h] [ebp-4h]

  dword_796E502 = dword_796E50;
  for ( i = 0; ; ++i )
  {
    v1 = 1;
    sprintf(FileName, "%s%05d", pArg1, i);
    pBuf2 = (char *)&i + 3;
    do
      v3 = *++pBuf2;
    while ( v3 != 0 );
    strcpy(pBuf2, ".BMP");
    FileA = CreateFileA(FileName, 0x80000000, 1u, nullptr, 3u, 0x80u, nullptr);
    if ( FileA != (HANDLE)-1 )
      v1 = 0;
    CloseHandle(FileA);
    sprintf(FileName, "%s%05d", pArg1, i);
    pBuf = (char *)&i + 3;
    do
      v6 = *++pBuf;
    while ( v6 != 0 );
    strcpy(pBuf, ".JPG");
    v7 = CreateFileA(FileName, 0x80000000, 1u, nullptr, 3u, 0x80u, nullptr);
    if ( v7 != (HANDLE)-1 )
      v1 = 0;
    CloseHandle(v7);
    if ( v1 == 1 )
      break;
  }
  return i;
}



// ------------------------------------------------------------
// 0x6994E0 sub_6994E0
// ------------------------------------------------------------
// 【L1】截屏·D3DFORMAT → 扩展名映射：0/1/2→dword_749ED4/749ECC/.TGA，
// 3→.PNG / 4→DDS / 5→.PPM / 6→.DIB / 7→.HDR / 8→.PFM
char */*thiscall*/ sub_6994E0(uint32_t *this)
{
  int fld_e22; // eax

  fld_e22 = *(this + 22);
  switch ( fld_e22 )
  {
    case 0:
      return (char *)&dword_749ED4;
    case 1:
      return (char *)&dword_749ECC;
    case 2:
      return ".TGA";
    case 3:
      return ".PNG";
    case 4:
      return "DDS";
    case 5:
      return ".PPM";
    case 6:
      return ".DIB";
    case 7:
      return ".HDR";
    default:
      break;
  }
  return fld_e22 != 8 ? nullptr : ".PFM";
}



// ------------------------------------------------------------
// 0x699550 sub_699550
// ------------------------------------------------------------
// 【L1】截屏单例 scalar deleting destructor（vtable off_749F18，refcount 清零）
uint32_t */*thiscall*/ sub_699550(uint32_t *Block, char pszArg2)
{
  *Block = off_749F18;
  dword_9D3BDC = 0;
  dword_9D3BE0 = 0;
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x699580 sub_699580
// ------------------------------------------------------------
// 【L1】截屏单例 Release：--dword_9D3BDC 归零时虚删 dword_9D3BE0
int sub_699580()
{
  int result; // eax

  if ( --dword_9D3BDC == 0 )
  {
    if ( dword_9D3BE0 != 0 )
      result = (**(int (/*thiscall*/ ***)(int, int))dword_9D3BE0)(dword_9D3BE0, 1);
    dword_9D3BE0 = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6995B0 sub_6995B0
// ------------------------------------------------------------
// 【L1】截屏单例 Acquire：refcount++ 或 new(0x60) 构造
// （vtable off_749F1C；3 个 std::string SSO 成员 +8/+32/+56，容量 15 直证）
uint32_t *sub_6995B0()
{
  uint32_t *result; // eax

  if ( dword_9D3BDC != 0 )
  {
    ++dword_9D3BDC;
    return (uint32_t *)dword_9D3BE0;
  }
  else
  {
    result = operator new(0x60u);
    if ( result != nullptr )
    {
      dword_9D3BDC = 0;
      *result = &off_749F1C;
      result[6] = 0;
      result[7] = 15;
      *((uint8_t *)result + 8) = 0;
      result[14] = 15;
      result[13] = 0;
      *((uint8_t *)result + 36) = 0;
      result[21] = 15;
      result[20] = 0;
      *((uint8_t *)result + 64) = 0;
    }
    else
    {
      result = nullptr;
    }
    dword_9D3BE0 = (int)result;
    ++dword_9D3BDC;
  }
  return result;
}



// ------------------------------------------------------------
// 0x699620 sub_699620
// ------------------------------------------------------------
// 【L1】截屏单例 deleting destructor（调 sub_699650 析构体）
void */*thiscall*/ sub_699620(void *Block, char pszArg2)
{
  sub_699650();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x699650 sub_699650
// ------------------------------------------------------------
// 【L1】截屏单例析构体：释放 3 个 std::string（容量>=0x10 才 free）+ refcount 清零
void /*thiscall*/ sub_699650(void **this)
{
  if ( (unsigned int)*(this + 21) >= 0x10 )
    j__free(*(this + 16));
  *(this + 21) = (void *)15;
  *(this + 20) = nullptr;
  *((uint8_t *)this + 64) = 0;
  if ( (unsigned int)*(this + 14) >= 0x10 )
    j__free(*(this + 9));
  *(this + 14) = (void *)15;
  *(this + 13) = nullptr;
  *((uint8_t *)this + 36) = 0;
  if ( (unsigned int)*(this + 7) >= 0x10 )
    j__free(*(this + 2));
  *(this + 6) = nullptr;
  *(this + 7) = (void *)15;
  *((uint8_t *)this + 8) = 0;
  *this = off_749F18;
  dword_9D3BDC = 0;
  dword_9D3BE0 = 0;
}



// ------------------------------------------------------------
// 0x6996D0 sub_6996D0
// ------------------------------------------------------------
// 【L1】std::string 拼接助手：a2 串 + a3 串 → 结果写回 a1（sub_4014D0 assign）
int /*cdecl*/ sub_6996D0(int pArg1, int nArg2, int nArg3)
{
  int v3; // eax
  uint8_t v5[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  int v7; // [esp+1Ch] [ebp-18h]
  unsigned int v8; // [esp+20h] [ebp-14h]
  int v9; // [esp+24h] [ebp-10h]
  int v10; // [esp+30h] [ebp-4h]

  v9 = 0;
  v8 = 15;
  v7 = 0;
  LOBYTE(Block) = 0;
  sub_4014D0((std::_String_base *)v5, nArg2, 0, -1);
  v10 = 0;
  v3 = sub_4021F0((std::_String_base *)v5, nArg3, 0, -1);
  *(uint32_t *)(pArg1 + 24) = 15;
  *(uint32_t *)(pArg1 + 20) = 0;
  *(uint8_t *)(pArg1 + 4) = 0;
  sub_4014D0((std::_String_base *)pArg1, v3, 0, -1);
  if ( v8 >= 0x10 )
    j__free(Block);
  return pArg1;
}



// ------------------------------------------------------------
// 0x699760 sub_699760
// ------------------------------------------------------------
// 【L1】截屏参数装载：Singleton() 后写 名称1(+4)/名称2(+32)/标志(+88)/id(+92)
int /*cdecl*/ sub_699760(int nArg1, int nArg2, int nArg3, int nArg4)
{
  sub_6995B0();
  sub_4014D0((std::_String_base *)(dword_9D3BE0 + 4), nArg2, 0, -1);
  sub_4014D0((std::_String_base *)(dword_9D3BE0 + 32), nArg3, 0, -1);
  *(uint32_t *)(dword_9D3BE0 + 88) = nArg4;
  *(uint32_t *)(dword_9D3BE0 + 92) = nArg1;
  return dword_9D3BE0;
}



// ------------------------------------------------------------
// 0x6997C0 sub_6997C0
// ------------------------------------------------------------
// 【L1】★★ ScreenShot 主函数（自证串 "ScreenShot File [" / "ScreenShot Capture FAIL!!"）
// usercall: this=截屏配置@ecx, a2=D3D 设备@edi。
// 流程: 探测序号(sub_6993C0) → 拼 "%s%05d"+扩展名(sub_6994E0) →
// 按配置[22] 分派: =1 且设备就绪 → 设备 vt+128/+108 取 640x480 前后缓冲 →
// 按表面格式(0x15/0x16=32bit / 0x17-0x19=16bit R5G6B5/R5G5B5X1) 软件转换
// 3 字节 BGR → sub_69E010(ijl15) 编码 JPG → CreateFileA+WriteFile 落盘；
// 其他格式 → sub_680134（missing_tail 0x68 区）直接存 .BMP →
// 拼 "ScreenShot File [...is Saved." 日志串返回；
// 失败返回 "ScreenShot Capture FAIL!!"。
const char */*usercall*/ sub_6997C0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int v4; // eax
  void **v5; // eax
  int v6; // eax
  void **v7; // ecx
  const char *psz; // esi
  unsigned int nLen; // eax
  char *v10; // edi
  char v11; // cl
  char *v12; // edi
  const char *v13; // esi
  unsigned int v14; // ecx
  bool v15; // zf
  int pObj4; // eax
  int pObj; // ebx
  int v18; // edi
  char *pMem; // eax
  void *pMem2; // esi
  int v21; // edx
  uint8_t *v22; // ecx
  int v23; // esi
  int v24; // eax
  char v25; // al
  unsigned int v26; // eax
  char v27; // dl
  void *pMem32; // ebx
  void *v29; // esi
  HANDLE FileA; // edi
  void **v31; // eax
  char *pBuf; // edi
  char v33; // al
  size_t *v34; // edi
  size_t *v35; // eax
  size_t *v36; // eax
  size_t *v37; // eax
  size_t v38; // edi
  size_t *v39; // esi
  size_t *v40; // eax
  size_t *v41; // eax
  size_t *v42; // eax
  size_t *v43; // esi
  int pObj32; // [esp-10h] [ebp-22Ch]
  uint8_t v46[28]; // [esp+8h] [ebp-214h] BYREF
  uint32_t v47[8]; // [esp+24h] [ebp-1F8h] BYREF
  uint8_t v48[4]; // [esp+44h] [ebp-1D8h] BYREF
  void *v49; // [esp+48h] [ebp-1D4h]
  unsigned int v50; // [esp+5Ch] [ebp-1C0h]
  uint8_t v51[4]; // [esp+60h] [ebp-1BCh] BYREF
  void *Block; // [esp+64h] [ebp-1B8h]
  int v53; // [esp+74h] [ebp-1A8h]
  unsigned int v54; // [esp+78h] [ebp-1A4h]
  uint8_t v55[4]; // [esp+7Ch] [ebp-1A0h] BYREF
  void *v56; // [esp+80h] [ebp-19Ch]
  int v57; // [esp+90h] [ebp-18Ch]
  unsigned int v58; // [esp+94h] [ebp-188h]
  uint32_t v59[2]; // [esp+98h] [ebp-184h] BYREF
  uint8_t v60[4]; // [esp+A0h] [ebp-17Ch] BYREF
  void *v61; // [esp+A4h] [ebp-178h]
  uint32_t v62[2]; // [esp+ACh] [ebp-170h] BYREF
  int v63; // [esp+B4h] [ebp-168h]
  unsigned int v64; // [esp+B8h] [ebp-164h]
  int v65; // [esp+BCh] [ebp-160h] BYREF
  int v66; // [esp+C0h] [ebp-15Ch]
  void *pMem3; // [esp+C4h] [ebp-158h]
  DWORD NumberOfBytesWritten; // [esp+C8h] [ebp-154h] BYREF
  size_t *v69; // [esp+CCh] [ebp-150h]
  DWORD nNumberOfBytesToWrite; // [esp+D0h] [ebp-14Ch] BYREF
  int v71; // [esp+D4h] [ebp-148h]
  int v72; // [esp+D8h] [ebp-144h]
  int v73; // [esp+DCh] [ebp-140h]
  int i; // [esp+E0h] [ebp-13Ch]
  int pObj2; // [esp+E4h] [ebp-138h] BYREF
  int pObj3; // [esp+E8h] [ebp-134h] BYREF
  char v77; // [esp+EFh] [ebp-12Dh] BYREF
  WCHAR FileName[128]; // [esp+F0h] [ebp-12Ch] BYREF
  uint8_t v79[4]; // [esp+1F0h] [ebp-2Ch] BYREF
  void *v80[5]; // [esp+1F4h] [ebp-28h] BYREF
  unsigned int v81; // [esp+208h] [ebp-14h]
  int dword_796E502; // [esp+20Ch] [ebp-10h]
  int v83; // [esp+218h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( pArg1[23] == 0 )
    return nullptr;
  v4 = sub_4E70B0((int)v51, pArg1 + 1, (char *)SubBlock);
  v83 = 0;
  sub_6996D0(v79, v4, pArg1 + 8);
  LOBYTE(v83) = 2;
  if ( v54 >= 0x10 )
    j__free(Block);
  v54 = 15;
  v53 = 0;
  LOBYTE(Block) = 0;
  pObj3 = 0;
  v69 = pArg1 + 15;
  sub_4015C0(pArg1 + 15, "ScreenShot File [", 0x11u);  // 【std::string构造赋值】
  v5 = (void **)v80[0];
  if ( v81 < 0x10 )
    v5 = v80;
  v6 = sub_6993C0(v5);
  v7 = (void **)v80[0];
  i = v6;
  if ( v81 < 0x10 )
    v7 = v80;
  sprintf((char *const)FileName, "%s%05d", (const char *)v7, v6);
  psz = (const char *)sub_6994E0(pArg1);
  nLen = strlen(psz) + 1;
  v10 = &v77;
  do
    v11 = *++v10;
  while ( v11 != 0 );
  qmemcpy(v10, psz, 4 * (nLen >> 2));
  v13 = &psz[4 * (nLen >> 2)];
  v12 = &v10[4 * (nLen >> 2)];
  v14 = nLen & 3;
  v15 = pArg1[22] == 1;
  pObj4 = pArg1[23];
  qmemcpy(v12, v13, v14);
  if ( v15 )
  {
    pObj2 = 0;
    (*(void (/*stdcall*/ **)(int, int *))(*(uint32_t *)pObj4 + 128))(pObj4, &pObj3);
    (*(void (/*stdcall*/ **)(int, uint32_t *))(*(uint32_t *)pObj3 + 32))(pObj3, v47);
    (*(void (/*stdcall*/ **)(uint32_t, int, int, uint32_t, int *))(*(uint32_t *)pArg1[23] + 108))(pArg1[23], 640, 480, v47[0], &pObj2);
    pObj = pArg1[23];
    v62[0] = 0;
    v62[1] = 0;
    v63 = 640;
    v64 = 480;
    v59[0] = 0;
    v59[1] = 0;
    (*(void (/*stdcall*/ **)(int, int, uint32_t *, int, int, uint32_t *))(*(uint32_t *)pObj + 112))(pObj, pObj3, v62, 1, pObj2, v59);
    (*(void (/*stdcall*/ **)(int, int *, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 36))(pObj2, &v65, 0, 0);
    v18 = v66;
    if ( v66 != 0 )
    {
      pMem = (char *)operator new(0xE1000u);
      pMem2 = pMem;
      pMem3 = pMem;
      v77 = 1;
      switch ( v47[0] )
      {
        case 0x15:
        case 0x16:
          v71 = 4;
          goto LABEL_19;
        case 0x17:
        case 0x18:
        case 0x19:
          v77 = 0;
          v71 = 2;
LABEL_19:
          v21 = 0;
          v72 = 0;
          v73 = 1;
          v22 = pMem + 1;
          do
          {
            v23 = 0;
            for ( i = 640; i != 0; --i )
            {
              if ( v77 == 1 )
              {
                v24 = v23 + v21 * v65;
                *(v22 - 1) = *(uint8_t *)(v24 + v18 + 2);
                *v22 = *(uint8_t *)(v24 + v18 + 1);
                v25 = *(uint8_t *)(v24 + v18);
              }
              else
              {
                v26 = *(uint16_t *)(v23 + v21 * v65 + v18);
                if ( v47[0] == 23 )
                {
                  *(v22 - 1) = BYTE1(v26) & 0xF8;
                  v27 = (v26 >> 3) & 0xFC;
                }
                else
                {
                  *(v22 - 1) = (v26 >> 7) & 0xF8;
                  v27 = (v26 >> 2) & 0xF8;
                }
                *v22 = v27;
                v25 = 8 * v26;
              }
              v22[v73] = v25;
              v23 += v71;
              v21 = v72;
              v22 += 3;
            }
            v21 = v72 + 1;
            v72 = v21;
          }
          while ( v21 < 480 );
          pMem32 = pMem3;
          nNumberOfBytesToWrite = 0;
          v29 = (void *)sub_69E010(pMem3, 640, 480, 3, &nNumberOfBytesToWrite, 100);
          NumberOfBytesWritten = 0;
          FileA = CreateFileA((LPCSTR)FileName, 0x40000000u, 1u, nullptr, 2u, 0x80u, nullptr);
          WriteFile(FileA, v29, nNumberOfBytesToWrite, &NumberOfBytesWritten, nullptr);
          CloseHandle(FileA);
          (*(void (/*stdcall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, nArg2);
          j_j__free(v29);
          j_j__free(pMem32);
          (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj2 + 8))(pObj2);
          goto LABEL_38;
        default:
          v31 = (void **)v80[0];
          if ( v81 < 0x10 )
            v31 = v80;
          sprintf((char *const)FileName, "%s%05d", (const char *)v31, i);
          pBuf = &v77;
          do
            v33 = *++pBuf;
          while ( v33 != 0 );
          pObj32 = pObj3;
          strcpy(pBuf, ".BMP");
          sub_680134(FileName, 0, pObj32, 0, 0);
          (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj2 + 40))(pObj2);
          (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj2 + 8))(pObj2);
          (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj3 + 8))(pObj3);
          j_j__free(pMem2);
          v34 = v69;
          v35 = (size_t *)sub_4E70B0((int)v46, v69, (char *)FileName);
          LOBYTE(v83) = 3;
          v36 = (size_t *)sub_4E70B0((int)v55, v35, "]");
          LOBYTE(v83) = 4;
          v37 = (size_t *)sub_4E70B0((int)v48, v36, "is Saved.");
          LOBYTE(v83) = 5;
          sub_4014D0(v34, v37, 0, 0xFFFFFFFF);
          sub_501490(v48);
          sub_501490(v55);
          sub_501490(v46);
          if ( v34[6] < 0x10 )
          {
            sub_501490(v79);
            return (const char *)(v34 + 1);
          }
          else
          {
            v38 = v34[1];
            sub_501490(v79);
            return (const char *)v38;
          }
      }
    }
    if ( v81 >= 0x10 )
      j__free(v80[0]);
    return "ScreenShot Capture FAIL!!";
  }
  else
  {
    (*(void (/*stdcall*/ **)(int, int *, int))(*(uint32_t *)pObj4 + 128))(pObj4, &pObj3, nArg2);
    sub_680134(FileName, pArg1[22], pObj3, 0, 0);
LABEL_38:
    (*(void (/*cdecl*/ **)(int))(*(uint32_t *)pObj3 + 8))(pObj3);
    v39 = v69;
    v40 = (size_t *)sub_4E70B0((int)v48, v69, (char *)FileName);
    LOBYTE(v83) = 6;
    v41 = (size_t *)sub_4E70B0((int)v55, v40, "]");
    LOBYTE(v83) = 7;
    v42 = (size_t *)sub_4E70B0((int)v60, v41, "is Saved.");
    LOBYTE(v83) = 8;
    sub_4014D0(v39, v42, 0, 0xFFFFFFFF);
    if ( v64 >= 0x10 )
      j__free(v61);
    v64 = 15;
    v63 = 0;
    LOBYTE(v61) = 0;
    if ( v58 >= 0x10 )
      j__free(v56);
    v58 = 15;
    v57 = 0;
    LOBYTE(v56) = 0;
    if ( v50 >= 0x10 )
      j__free(v49);
    if ( v39[6] < 0x10 )
      v43 = v39 + 1;
    else
      v43 = (size_t *)v39[1];
    if ( v81 >= 0x10 )
      j__free(v80[0]);
    return (const char *)v43;
  }
}


// ------------------------------------------------------------
// 0x699E20 sub_699E20
// ------------------------------------------------------------
// 【L1】数字标签（CNumberLabel 类）构造：字段清零，+20=-1(未知值)，返回 0
int /*thiscall*/ sub_699E20(int this)
{
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = -1;
  *(uint8_t *)(this + 24) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x699E40 sub_699E40
// ------------------------------------------------------------
// 【L1】数字标签 Create：+8/+12 位置、+28 字体句柄表、+32 位数上限；
// new(a5+2) 数字缓冲（+16），memset 清零，+4=1。
int /*thiscall*/ sub_699E40(int this, int nArg2, int nArg3, int nArg4, int pArg5)
{
  void *pMem; // edi

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  *(uint32_t *)(this + 8) = nArg2;
  *(uint32_t *)(this + 12) = nArg3;
  *(uint32_t *)(this + 28) = nArg4;
  *(uint32_t *)(this + 32) = pArg5;
  pMem = operator new(pArg5 + 2);
  *(uint32_t *)(this + 16) = pMem;
  if ( pMem == nullptr )
    return -2147483640;
  memset(pMem, 0, pArg5 + 2);
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x699EC0 sub_699EC0
// ------------------------------------------------------------
// 【L1】数字标签 Destroy：free 数字缓冲(+16) 并清字段，+20=-1
int /*thiscall*/ sub_699EC0(int this)
{
  if ( *(uint32_t *)(this + 16) != 0 )
    j_j__free(*(void **)(this + 16));
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint8_t *)(this + 24) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 20) = -1;
  return 1;
}



// ------------------------------------------------------------
// 0x699F00 sub_699F00
// ------------------------------------------------------------
// 【L1】数字标签 SetNumber：_itoa(10 进制) 后逐字节 -47 映射为字形索引
// （'0'=48→1 .. '9'=57→10；'-'+45→-2，缺字/负号占位），+24=逐字填充模式开关。
unsigned int /*thiscall*/ sub_699F00(int this, int Value)
{
  unsigned int result; // eax
  char *fld_10; // eax
  unsigned int nLen; // ecx
  unsigned int fld_20; // edx
  unsigned int v7; // eax
  char fld_102; // dl
  int fld_202; // ebx
  int fld_103; // edx
  char v11; // bl
  uint8_t *v12; // edx
  int Valuea; // [esp+10h] [ebp+8h]

  result = *(uint32_t *)(this + 20);
  if ( result != Value )
  {
    fld_10 = *(char **)(this + 16);
    *(uint32_t *)(this + 20) = Value;
    _itoa(Value, fld_10, 10);
    nLen = strlen(*(const char **)(this + 16));
    if ( *(uint8_t *)(this + 24) != 0 )
    {
      fld_20 = *(uint32_t *)(this + 32) - nLen;
      v7 = 0;
      Valuea = fld_20;
      if ( nLen != 0 )
      {
        do
        {
          fld_102 = *(uint8_t *)(*(uint32_t *)(this + 16) - v7 + nLen - 1) - 47;
          fld_202 = *(uint32_t *)(this + 32) - v7++;
          *(uint8_t *)(fld_202 + *(uint32_t *)(this + 16) - 1) = fld_102;
        }
        while ( v7 < nLen );
        fld_20 = Valuea;
      }
      for ( result = 0; result < fld_20; ++result )
        *(uint8_t *)(result + *(uint32_t *)(this + 16)) = 1;
    }
    else
    {
      result = 0;
      if ( Value < 0 )
      {
        **(uint8_t **)(this + 16) -= 45;
        result = 1;
      }
      for ( ; result < nLen; *v12 = v11 - 47 )
      {
        fld_103 = *(uint32_t *)(this + 16);
        v11 = *(uint8_t *)(fld_103 + result);
        v12 = (uint8_t *)(result + fld_103);
        ++result;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x699FC0 sub_699FC0
// ------------------------------------------------------------
// 【L1】数字标签 GetWidth：按模式 0/2 累计每字形宽度
// （sub_418DD0 字形句柄 + 36 处宽度 + 字距 +40），负值走 '-' 字形占位。
int /*thiscall*/ sub_699FC0(int this, int Value)
{
  int fld_24; // eax
  int fld_28; // ebx
  int v6; // edi
  const char *fld_102; // eax
  const char *fld_10; // eax
  unsigned int nLen; // eax
  int v10; // edi
  int i; // ebx
  int v12; // [esp+4h] [ebp-4h]
  int Valuea; // [esp+10h] [ebp+8h]

  if ( *(uint8_t *)(this + 4) == 0 )
    return -1;
  sub_699F00(this, Value);
  fld_24 = *(uint32_t *)(this + 36);
  fld_28 = 0;
  if ( fld_24 != 0 )
  {
    if ( fld_24 == 2 )
    {
      fld_10 = *(const char **)(this + 16);
      v12 = 0;
      if ( Value >= 0 )
      {
        nLen = strlen(fld_10);
      }
      else
      {
        nLen = strlen(fld_10 + 1) + 1;
        v12 = 1;
      }
      v10 = nLen - 1;
      for ( i = 0; v10 >= v12; --v10 )
        i += *(uint32_t *)(this + 40)
           + *(uint32_t *)(sub_418DD0(*(uint32_t *)(this + 28) + *(char *)(*(uint32_t *)(this + 16) + v10)) + 36);
      if ( Value < 0 )
        i += *(uint32_t *)(this + 40) + *(uint32_t *)(sub_418DD0(*(uint32_t *)(this + 28)) + 36);
      return i;
    }
    else
    {
      return -1;
    }
  }
  else
  {
    v6 = 0;
    fld_102 = *(const char **)(this + 16);
    if ( Value >= 0 )
    {
      Valuea = strlen(fld_102);
    }
    else
    {
      Valuea = strlen(fld_102 + 1) + 1;
      fld_28 = *(uint32_t *)(this + 40) + *(uint32_t *)(sub_418DD0(*(uint32_t *)(this + 28)) + 36);
      v6 = 1;
    }
    for ( ; v6 < Valuea; ++v6 )
      fld_28 += *(uint32_t *)(this + 40)
          + *(uint32_t *)(sub_418DD0(*(uint32_t *)(this + 28) + *(char *)(*(uint32_t *)(this + 16) + v6)) + 36);
    return fld_28;
  }
}



// ------------------------------------------------------------
// 0x69A110 sub_69A110
// ------------------------------------------------------------
// 【L1】数字标签 Draw：按对齐/着色分派图片 vt+152（普通）或 vt+128（10 参含 Alpha 版）
// （1065353216=1.0f / 1333788672=0x4F800000 原值保留）；位数 >9 时 clamp 到 10^9-1。
int /*thiscall*/ sub_69A110(int this, int nArg2, int nArg3, int Value, int nArg5)
{
  unsigned int fld_20; // eax
  int v8; // edi
  int v9; // eax
  int fld_24; // eax
  int fld_282; // ebx
  const char *fld_102; // eax
  uint32_t *fld_1C4; // edi
  int fld_1C5; // eax
  int fld_1C6; // eax
  uint32_t *fld_1C7; // edi
  const char *fld_10; // eax
  unsigned int nLen; // eax
  int v20; // edi
  int v21; // eax
  uint32_t *fld_1C; // ecx
  int fld_28; // edi
  int fld_1C3; // eax
  int v25; // [esp+4h] [ebp-8h]
  signed int nLen2; // [esp+8h] [ebp-4h]
  int v27; // [esp+8h] [ebp-4h]
  uint32_t *fld_1C2; // [esp+14h] [ebp+8h]
  int Valuea; // [esp+1Ch] [ebp+10h]
  int Valueb; // [esp+1Ch] [ebp+10h]

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  fld_20 = *(uint32_t *)(this + 32);
  if ( fld_20 < 9 )
  {
    v8 = Value;
    v9 = sub_410790(10, fld_20) - 1;
    if ( Value < v9 )
      goto LABEL_7;
    Value = v9;
  }
  v8 = Value;
LABEL_7:
  sub_699F00(this, v8);
  fld_24 = *(uint32_t *)(this + 36);
  fld_282 = 0;
  if ( fld_24 != 0 )
  {
    if ( fld_24 == 2 )
    {
      fld_10 = *(const char **)(this + 16);
      v25 = 0;
      if ( v8 >= 0 )
      {
        nLen = strlen(fld_10);
      }
      else
      {
        nLen = strlen(fld_10 + 1) + 1;
        v25 = 1;
      }
      v20 = 0;
      v21 = nLen - 1;
      v27 = v21;
      if ( v21 >= v25 )
      {
        while ( 1 )
        {
          fld_1C = (uint32_t *)sub_418DD0(*(uint32_t *)(this + 28) + *(char *)(v21 + *(uint32_t *)(this + 16)));
          v20 += *(uint32_t *)(this + 40) + fld_1C[9];
          if ( nArg5 == -1 )
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*fld_1C + 152))(fld_1C, nArg2 - v20, nArg3, *(uint32_t *)(this + 8));
          else
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, int, int, uint32_t, int, int, int))(*fld_1C + 128))(
              fld_1C,
              nArg2 - v20,
              nArg3,
              *(uint32_t *)(this + 8),
              1065353216,
              1065353216,
              0,
              ((uint8_t)nArg5 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          if ( --v27 < v25 )
            break;
          v21 = v27;
        }
      }
      if ( Value < 0 )
      {
        fld_1C2 = (uint32_t *)sub_418DD0(*(uint32_t *)(this + 28));
        fld_28 = *(uint32_t *)(this + 40) + fld_1C2[9] + v20;
        if ( nArg5 == -1 )
        {
          fld_1C3 = sub_418DD0(*(uint32_t *)(this + 28) + 1);
          (*(void (/*stdcall*/ **)(int, int, uint32_t))(*fld_1C2 + 152))(
            nArg2 - fld_28,
            nArg3 + (*(uint32_t *)(fld_1C3 + 40) >> 1) - (fld_1C2[10] >> 1),
            *(uint32_t *)(this + 8));
          return 1;
        }
        Valueb = sub_418DD0(*(uint32_t *)(this + 28) + 1);
        (*(void (/*stdcall*/ **)(int, int, uint32_t, int, int, uint32_t, int, int, int))(*fld_1C2 + 128))(
          nArg2 - fld_28,
          nArg3 + (*(uint32_t *)(Valueb + 40) >> 1) - (fld_1C2[10] >> 1),
          *(uint32_t *)(this + 8),
          1065353216,
          1065353216,
          0,
          ((uint8_t)nArg5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      }
    }
    return 1;
  }
  fld_102 = *(const char **)(this + 16);
  Valuea = 0;
  if ( v8 >= 0 )
  {
    nLen2 = strlen(fld_102);
  }
  else
  {
    nLen2 = strlen(fld_102 + 1) + 1;
    fld_1C4 = (uint32_t *)sub_418DD0(*(uint32_t *)(this + 28));
    if ( nArg5 == -1 )
    {
      fld_1C5 = sub_418DD0(*(uint32_t *)(this + 28) + 1);
      sub_40FC80(nArg2, nArg3 + (*(uint32_t *)(fld_1C5 + 40) >> 1) - (fld_1C4[10] >> 1), fld_1C4);
      fld_282 = *(uint32_t *)(this + 40) + fld_1C4[9];
      Valuea = 1;
    }
    else
    {
      fld_1C6 = sub_418DD0(*(uint32_t *)(this + 28) + 1);
      if ( fld_1C4 != nullptr )
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, int, int, uint32_t, int, int, int))(*fld_1C4 + 128))(
          fld_1C4,
          nArg2,
          nArg3 + (*(uint32_t *)(fld_1C6 + 40) >> 1) - (fld_1C4[10] >> 1),
          *(uint32_t *)(this + 8),
          1065353216,
          1065353216,
          0,
          ((uint8_t)nArg5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      fld_282 = *(uint32_t *)(this + 40) + fld_1C4[9];
      Valuea = 1;
    }
  }
  if ( Valuea >= nLen2 )
    return 1;
  do
  {
    fld_1C7 = (uint32_t *)sub_418DD0(*(uint32_t *)(this + 28) + *(char *)(Valuea + *(uint32_t *)(this + 16)));
    if ( nArg5 == -1 )
    {
      if ( fld_1C7 != nullptr )
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*fld_1C7 + 152))(fld_1C7, fld_282 + nArg2, nArg3, *(uint32_t *)(this + 8));
    }
    else if ( fld_1C7 != nullptr )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, int, int, uint32_t, int, int, int))(*fld_1C7 + 128))(
        fld_1C7,
        fld_282 + nArg2,
        nArg3,
        *(uint32_t *)(this + 8),
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg5 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    }
    fld_282 += *(uint32_t *)(this + 40) + fld_1C7[9];
    ++Valuea;
  }
  while ( Valuea < nLen2 );
  return 1;
}


// ------------------------------------------------------------
// 0x69A4D0 sub_69A4D0
// ------------------------------------------------------------
// 【L1】CNUIObject::IsMouseOver：可见(+17) && dword_79BE3C==id(+12) && dword_89D26C==1
// （1 = WM_LBUTTONDOWN 活动态）
char /*thiscall*/ sub_69A4D0(int this)
{
  char result; // al

  if ( *(uint8_t *)(this + 17) == 0 )
    return 0;
  if ( dword_79BE3C != *(uint32_t *)(this + 12) )
    return 0;
  result = 1;
  if ( dword_89D26C != 1 )
    return 0;
  return result;
}



// ------------------------------------------------------------
// 0x69A500 sub_69A500
// ------------------------------------------------------------
// 【L1】CNUIObject::IsHover 查询：可见(+17) && dword_79BE44==id(+12)
bool /*thiscall*/ sub_69A500(int this)
{
  return *(uint8_t *)(this + 17) != 0 && dword_79BE44 == *(uint32_t *)(this + 12);
}



// ------------------------------------------------------------
// 0x69A520 sub_69A520
// ------------------------------------------------------------
// 【L1】CNUIObject 构造：字段清零，+16/+17 可见与激活置 1，
// id(+12) = dword_9D3BCC++（全局控件 id 分配器），+64=1，sub_6569D0(+92) 初始化子结构
int /*thiscall*/ sub_69A520(int this)
{
  *(uint32_t *)(this + 8) = 0;
  *(uint8_t *)(this + 16) = 1;
  *(uint8_t *)(this + 17) = 1;
  *(uint8_t *)(this + 18) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  sub_6569D0(this + 92);
  *(uint32_t *)(this + 68) = 0;
  *(uint8_t *)(this + 64) = 1;
  *(uint32_t *)(this + 12) = dword_9D3BCC;
  return ++dword_9D3BCC;
}



// ------------------------------------------------------------
// 0x69A580 sub_69A580
// ------------------------------------------------------------
// 【L1】CNUIObject::RemoveChild：子链(+24 环形双链)按值摘除并 free，计数(+25)--
int /*thiscall*/ sub_69A580(void ***this, void *pArg2)
{
  void **fld_e24; // ecx
  void **v5; // eax

  if ( pArg2 == nullptr )
    return 0x80000000;
  fld_e24 = *(this + 24);
  v5 = (void **)*fld_e24;
  if ( *fld_e24 == fld_e24 )
    return 0x80000000;
  while ( v5[2] != pArg2 )
  {
    v5 = (void **)*v5;
    if ( v5 == fld_e24 )
      return 0x80000000;
  }
  if ( v5 != *(this + 24) )
  {
    *(uint32_t *)v5[1] = *v5;
    *((uint32_t *)*v5 + 1) = v5[1];
    j__free(v5);
    *(this + 25) = (void **)((char *)*(this + 25) - 1);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x69A5F0 sub_69A5F0
// ------------------------------------------------------------
// 【L1】CNUIObject::MoveWindow(dx,dy)：位置(+5/+6)平移并记旧值(+9/+10)，
// 递归平移全部子项（子 +20/+24 相对偏移补偿）
uint32_t */*thiscall*/ sub_69A5F0(uint32_t *this, int nArg2, int nArg3)
{
  int fld_e5; // eax
  int fld_e6; // ecx
  uint32_t *result; // eax
  uint32_t *v7; // edi

  fld_e5 = *(this + 5);
  fld_e6 = *(this + 6);
  *(this + 9) = fld_e5;
  *(this + 6) = nArg3;
  result = (uint32_t *)*(this + 25);
  *(this + 10) = fld_e6;
  *(this + 5) = nArg2;
  if ( result != nullptr )
  {
    result = (uint32_t *)*(this + 24);
    v7 = (uint32_t *)*result;
    if ( (uint32_t *)*result != result )
    {
      do
      {
        result = (uint32_t *)sub_69A5F0(
                             *(this + 5) + *(uint32_t *)(v7[2] + 20) - *(this + 9),
                             *(this + 6) + *(uint32_t *)(v7[2] + 24) - *(this + 10));
        v7 = (uint32_t *)*v7;
      }
      while ( v7 != (uint32_t *)*(this + 24) );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x69A650 sub_69A650
// ------------------------------------------------------------
// 【L1】CNUIObject::DragWindow：dword_79BE40 拖动态管理；
// 按下时(+17 且 dword_79BE3C==id)记录抓取点(+44/+48 = pt - pos(+20/+24))，
// 移动帧按 dword_79BE40==id 调 MoveWindow(pt - 抓取点)
int /*thiscall*/ sub_69A650(int this)
{
  int fld_C; // edx
  int dword_79BE402; // eax
  int fld_18; // ebx

  fld_C = *(uint32_t *)(this + 12);
  dword_79BE402 = dword_79BE40;
  if ( dword_79BE40 != fld_C && dword_79BE40 != -1 )
    return 1;
  if ( *(uint8_t *)(this + 17) != 0 && dword_79BE3C == fld_C )
  {
    if ( dword_89D26C != 1 )
      return 1;
    if ( dword_79BE40 != -1 )
      goto LABEL_9;
    fld_18 = *(uint32_t *)(this + 24);
    *(uint32_t *)(this + 44) = pt.x - *(uint32_t *)(this + 20);
    *(uint32_t *)(this + 48) = pt.y - fld_18;
    dword_79BE402 = fld_C;
    dword_79BE40 = fld_C;
  }
  if ( dword_89D26C != 1 )
    return 1;
LABEL_9:
  if ( dword_79BE402 == *(uint32_t *)(this + 12) )
    sub_69A5F0((uint32_t *)this, pt.x - *(uint32_t *)(this + 44), pt.y - *(uint32_t *)(this + 48));
  return 1;
}



// ------------------------------------------------------------
// 0x69A6E0 sub_69A6E0
// ------------------------------------------------------------
// 【L1】CNUIObject::Render 递归：虚槽 +24 绘制自身 → 可见(+21) 时经
// dword_9D3BD8 遮罩或渲染器 vt+72 Begin/+80 DrawText/+76 End 绘制纹理(+13..+20)
// → 遍历子链递归（子可见时 Render，且拖动态调 DragWindow）
int /*thiscall*/ sub_69A6E0(uint32_t *this)
{
  void (/*stdcall*/ ***fld_e17)(uint32_t *); // eax
  uint32_t *fld_e24; // eax
  uint32_t *v4; // ebx
  uint8_t *v5; // edi

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 24))(this);
  if ( *(this + 21) != 0 )
  {
    if ( dword_9D3BD8 != 0 )
    {
      sub_416430(dword_9D3BC8, *(this + 5) + *(this + 13), *(this + 6) + *(this + 14), *(this + 15), *(this + 20));
    }
    else
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_9D3BC8 + 72))(dword_9D3BC8, 0);
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)dword_9D3BC8 + 80))(
        dword_9D3BC8,
        *(this + 5) + *(this + 13),
        *(this + 6) + *(this + 14),
        *(this + 15),
        *(this + 20));
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_9D3BC8 + 76))(dword_9D3BC8);
    }
  }
  fld_e17 = (void (/*stdcall*/ ***)(uint32_t *))*(this + 17);
  if ( fld_e17 != nullptr )
    (**fld_e17)(this);
  fld_e24 = (uint32_t *)*(this + 24);
  v4 = (uint32_t *)*fld_e24;
  if ( (uint32_t *)*fld_e24 != fld_e24 )
  {
    do
    {
      v5 = (uint8_t *)v4[2];
      if ( v5[16] != 0 )
      {
        sub_69A6E0(v4[2]);
        if ( v5[17] != 0 && v5[18] != 0 )
          sub_69A650((int)v5);
      }
      v4 = (uint32_t *)*v4;
    }
    while ( v4 != (uint32_t *)*(this + 24) );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x69A7B0 sub_69A7B0
// ------------------------------------------------------------
// 【L1】std::list<T> 尺寸增长哨兵：0x3FFFFFFF 上限，超额抛 length_error（"list<T> too long"）
int /*thiscall*/ sub_69A7B0(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
    v8 = 0;
    sub_401740(pExceptionObject, (int)v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x69A840 sub_69A840
// ------------------------------------------------------------
// 【L1】CNUIObject::PushChild：list 尾插（sub_40C0F0 + 69A7B0 计数）
int /*thiscall*/ sub_69A840(uint32_t *this, int nArg2)
{
  int fld_e24; // edi
  uint32_t *pThis_17; // esi
  int v5; // ebx

  if ( nArg2 == 0 )
    return 0x80000000;
  fld_e24 = *(this + 24);
  pThis_17 = this + 23;
  v5 = sub_40C0F0(fld_e24, *(uint32_t *)(fld_e24 + 4), &nArg2);
  sub_69A7B0(pThis_17, 1u);
  *(uint32_t *)(fld_e24 + 4) = v5;
  **(uint32_t **)(v5 + 4) = v5;
  return 1;
}



// ------------------------------------------------------------
// 0x69A890 sub_69A890
// ------------------------------------------------------------
// 【L1】CNUIObject::HitTest 递归：深度优先命中矩形(+20/+24/+28/+32)，
// dword_89D26C 分派 1/8/16（左键/拖动/滚轮）：命中后按子类型(+8: 2=子容器递归删插、
// 8=焦点 id dword_79BE54)写 dword_79BE3C/34/38/44/4C/50/54/58/5C/60/64 状态组
int /*thiscall*/ sub_69A890(int this)
{
  int result; // eax
  uint32_t *fld_60; // edi
  int v4; // esi
  LONG v5; // ecx
  LONG v6; // eax
  int v7; // eax
  int fld_8; // ecx

  if ( *(uint8_t *)(this + 16) == 0 || *(uint8_t *)(this + 17) == 0 )
    return -1;
  if ( *(uint32_t *)(this + 100) == 0 )
    return -1;
  fld_60 = *(uint32_t **)(this + 96);
  if ( fld_60 == (uint32_t *)*fld_60 )
    return -1;
  while ( 1 )
  {
    v4 = *(uint32_t *)(fld_60[1] + 8);
    result = sub_69A890(v4);
    if ( result != -1 )
      return result;
    if ( *(uint8_t *)(v4 + 17) != 0 && *(uint8_t *)(v4 + 16) != 0 )
      break;
LABEL_18:
    fld_60 = (uint32_t *)fld_60[1];
    if ( fld_60 == **(uint32_t ***)(this + 96) )
      return -1;
  }
  v5 = *(uint32_t *)(v4 + 20);
  if ( pt.x < v5
    || (v6 = *(uint32_t *)(v4 + 24), pt.y < v6)
    || pt.x > *(uint32_t *)(v4 + 28) + v5 - 1
    || pt.y > *(uint32_t *)(v4 + 32) + v6 - 1 )
  {
    if ( dword_89D26C == 8 )
    {
      dword_79BE34 = -1;
      dword_79BE40 = -1;
    }
    else if ( dword_89D26C == 16 )
    {
      dword_79BE38 = -1;
    }
    goto LABEL_18;
  }
  if ( dword_89D26C == 1 )
  {
    if ( dword_79BE4C != *(uint32_t *)(v4 + 12) && dword_79BE40 == -1 )
    {
      dword_79BE50 = *(uint32_t *)(this + 12);
      dword_79BE4C = *(uint32_t *)(v4 + 12);
      v7 = *(uint32_t *)(v4 + 8);
      if ( v7 == 2 )
      {
        sub_69A580(v4);
        sub_69A840(v4);
        dword_79BE3C = *(uint32_t *)(v4 + 12);
        return dword_79BE4C;
      }
      else if ( v7 == 8 )
      {
        dword_79BE54 = *(uint32_t *)(v4 + 12);
        dword_79BE3C = *(uint32_t *)(v4 + 12);
        return dword_79BE4C;
      }
      else
      {
        if ( *(uint32_t *)(this + 8) != 11 )
          dword_79BE60 = -1;
        dword_79BE3C = *(uint32_t *)(v4 + 12);
        return dword_79BE4C;
      }
    }
LABEL_43:
    result = *(uint32_t *)(v4 + 12);
    dword_79BE3C = result;
    return result;
  }
  if ( dword_89D26C != 8 )
  {
    if ( dword_89D26C == 16 )
    {
      dword_89D26C = 0;
      result = *(uint32_t *)(v4 + 12);
      dword_79BE38 = result;
      return result;
    }
    goto LABEL_43;
  }
  dword_79BE5C = -1;
  dword_89D26C = 0;
  dword_79BE50 = *(uint32_t *)(this + 12);
  dword_79BE4C = *(uint32_t *)(v4 + 12);
  result = *(uint32_t *)(v4 + 12);
  dword_79BE34 = result;
  fld_8 = *(uint32_t *)(this + 8);
  switch ( fld_8 )
  {
    case 7:
      dword_79BE58 = *(uint32_t *)(this + 12);
      if ( *(uint32_t *)(v4 + 8) == 6 )
      {
        dword_79BE64 = *(uint32_t *)(v4 + 12);
        dword_79BE40 = -1;
        dword_79BE44 = *(uint32_t *)(v4 + 12);
        return result;
      }
      break;
    case 12:
      dword_79BE60 = *(uint32_t *)(this + 12);
      dword_79BE40 = -1;
      dword_79BE44 = *(uint32_t *)(v4 + 12);
      return result;
    case 2:
      dword_79BE5C = *(uint32_t *)(this + 12);
      dword_79BE40 = -1;
      dword_79BE44 = *(uint32_t *)(v4 + 12);
      return result;
    case 8:
      dword_79BE54 = *(uint32_t *)(this + 12);
      break;
    default:
      break;
  }
  dword_79BE40 = -1;
  dword_79BE44 = *(uint32_t *)(v4 + 12);
  return result;
}


// ------------------------------------------------------------
// 0x69AB00 sub_69AB00
// ------------------------------------------------------------
// 【L1】CNUIObject::Update：可见(+64)时清 dword_79BE34/38/3C/64/44/48 全局状态组，
// 然后 HitTest(69A890) + Render(69A6E0) —— 每帧入口
int /*thiscall*/ sub_69AB00(int this)
{
  if ( *(uint8_t *)(this + 64) != 0 )
  {
    dword_79BE34 = -1;
    dword_79BE38 = -1;
    dword_79BE3C = -1;
    dword_79BE64 = -1;
    dword_79BE44 = -1;
    dword_79BE48 = -1;
  }
  sub_69A890(this);
  sub_69A6E0((uint32_t *)this);
  return 1;
}




// ============================================================
// SECTION 6  ★ NCEdit 聊天输入控件 + nIIme IME 处理链（0x69AB50-0x69BE10）
// ------------------------------------------------------------
// NCEdit（"NCEdit::Empty() call" 自证）= 单行聊天/输入框控件。
//   对象布局: +4 激活(BYTE) / +8 类型(=8) / +12 控件id / +16 可见 / +17 焦点
//     / +104 最大输入字节 m_MaxLen / +108 缓冲尺寸 / +112 滚动基准
//     / +116 组合提交中(BYTE) / +117 组合进行(BYTE) / +120 光标 m_dwCaretPos
//     / +128 颜色 / +132 光标闪烁对象(0x698F90 群)
//     / +164..+176 主串{+164就绪,+168指针,+172长度,+176容量}
//     / +184..+196 次串(IME 组合中) / +200 渲染用 std::string / +208 m_String
//     / +212 长度 / +220 内容变更(BYTE) / +221 IME重聚焦(BYTE) / +224 IME下划线光标
// nIIme = IME 组合泵（"nIIme::IsEndComposition()" 自证），全局状态:
//   byte_8A6A98[0x400] 组合串A / byte_8A6698[0x400] 组合串B
//   byte_8A6298[0x400] 虚键缓冲 / byte_8A6E98 提交标志 / byte_8A6E9A 上屏标志
//   byte_8A6E9B 串B有效 / byte_8A6E9C 组合中 / dword_8A6EA8 组合长度
//   dword_8A6EB8 字体引擎备份 / byte_8A6EAC 引擎切换标志
// 处理链（逐帧）: WndProc 填 IME 全局 ──► sub_69BE10 IsEndComposition
//   ──► sub_69B590 宽度适配(字体引擎 vt+24) ──► 光标处拼接(sub_402DE0/402CB0)
//   ──► 超长则 sub_407400 completeIMEComposit 强制上屏。
// 键盘链: sub_69BAF0 方向/行首行尾(35 End/36 Home/37 Left/39 Right 直证)
//   ──► sub_69B7B0 退格 / sub_69B970 删除（均 SJIS 双字节感知，2 字节回退）。
// SJIS 首字节表: -127..-97(0x81-0x9F) / -32..-22(0xE0-0xEF) / -19/-18/-6/-5/-4
// ============================================================
// ------------------------------------------------------------
// 0x69AB50 sub_69AB50
// ------------------------------------------------------------
// 【L1】NCEdit::Init：类型(+8)=8、光标/滚动/IME 标志全清、byte_9D3BE4=0
int /*thiscall*/ sub_69AB50(int this)
{
  *(uint32_t *)(this + 8) = 8;
  *(uint8_t *)(this + 116) = 0;
  *(uint8_t *)(this + 117) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 128) = -1;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint8_t *)(this + 220) = 0;
  *(uint8_t *)(this + 221) = 0;
  *(uint32_t *)(this + 224) = 0;
  byte_9D3BE4 = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x69AB90 sub_69AB90
// ------------------------------------------------------------
// 【L1】NCEdit::Create(maxChars, bufSize)：重复创建→0x80000002；
// 最大输入 +104=a2；缓冲尺寸 +108 = (a3==-1 ? 5*a2 : a3)；
// sub_403080 分配主串与滚动表；光标闪烁对象 sub_698F90(this+132,1,0) 初始化；+4=1
int /*thiscall*/ sub_69AB90(int this, int pArg2, int nArg3)
{
  int nArg32; // ecx

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  nArg32 = nArg3;
  *(uint32_t *)(this + 104) = pArg2;
  if ( nArg3 == -1 )
    nArg32 = 5 * pArg2;
  *(uint32_t *)(this + 108) = nArg32;
  sub_403080(pArg2 + 5);
  sub_403080(*(uint32_t *)(this + 108) / 5u + 5);
  sub_698F90(this + 132, 1, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x69AC10 sub_69AC10
// ------------------------------------------------------------
// 【L1】NCEdit::Destroy：全字段复位（与 Init 对应），byte_9D3BE4=0，+4=0
int /*thiscall*/ sub_69AC10(int this)
{
  *(uint8_t *)(this + 116) = 0;
  *(uint8_t *)(this + 117) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint8_t *)(this + 220) = 0;
  *(uint8_t *)(this + 221) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 8) = 8;
  *(uint32_t *)(this + 128) = -1;
  byte_9D3BE4 = 0;
  *(uint8_t *)(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x69AC60 sub_69AC60
// ------------------------------------------------------------
// 【L1】分页查询：dword_77F400 != -1 即有分页数据【推断】
bool sub_69AC60()
{
  return dword_77F400 != -1;
}



// ------------------------------------------------------------
// 0x69AC70 sub_69AC70
// ------------------------------------------------------------
// 【L1】分页查询：取当前页最大行号（36 字节/项表 @9032376=0x89D668，dword_77F404=页大小）
int sub_69AC70()
{
  int v1; // esi
  int v2; // eax
  int *v3; // edx
  int dword_77F4042; // ecx

  if ( dword_77F400 == -1 )
    return 0;
  v1 = 0;
  v2 = dword_77F404 * ((int)dwValue / dword_77F404);
  if ( v2 < v2 + dword_77F404 )
  {
    v3 = (int *)(36 * v2 + 9032376);
    dword_77F4042 = dword_77F404;
    do
    {
      if ( v1 < *v3 )
        v1 = *v3;
      v3 += 9;
      --dword_77F4042;
    }
    while ( dword_77F4042 != 0 );
  }
  return v1;
}



// ------------------------------------------------------------
// 0x69ACE0 sub_69ACE0
// ------------------------------------------------------------
// 【L1】NCEdit::DrawPageNumbers：a2<600 时按页渲染页码列表（sub_416430 文本绘制，
// 当前页 -16725766 高亮色），页脚 "%d/%d"
int /*thiscall*/ sub_69ACE0(uint32_t *this, int pArg2, int nArg3)
{
  int result; // eax
  unsigned int dword_77F4042; // ecx
  int v5; // esi
  int v6; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // esi
  int dword_77F4002; // [esp+0h] [ebp-40h]
  int dword_77F4043; // [esp+4h] [ebp-3Ch]
  unsigned int dword_8A6EB02; // [esp+8h] [ebp-38h]
  int v13; // [esp+Ch] [ebp-34h]
  int v14; // [esp+10h] [ebp-30h]
  int v15; // [esp+14h] [ebp-2Ch]
  char Buffer; // [esp+1Ch] [ebp-24h] BYREF
  int v18; // [esp+1Dh] [ebp-23h]
  int v19; // [esp+21h] [ebp-1Fh]
  int v20; // [esp+25h] [ebp-1Bh]
  int v21; // [esp+29h] [ebp-17h]
  int v22; // [esp+2Dh] [ebp-13h]
  int v23; // [esp+31h] [ebp-Fh]
  int v24; // [esp+35h] [ebp-Bh]
  int16_t v25; // [esp+39h] [ebp-7h]
  char v26; // [esp+3Bh] [ebp-5h]
  int dword_796E502; // [esp+3Ch] [ebp-4h]

  result = dword_796E50;
  dword_796E502 = dword_796E50;
  if ( pArg2 < 600 )
  {
    result = dword_77F400;
    dword_77F4002 = dword_77F400;
    if ( dword_77F400 != -1 )
    {
      dword_77F4042 = dword_77F404;
      dword_8A6EB02 = dword_8A6EB0;
      v18 = 0;
      v19 = 0;
      v20 = 0;
      v21 = 0;
      v22 = 0;
      v23 = 0;
      v24 = 0;
      v25 = 0;
      v26 = 0;
      dword_77F4043 = dword_77F404;
      v15 = 1;
      Buffer = 0;
      v5 = (int)dwValue / dword_77F404;
      v6 = dword_77F404 * ((int)dwValue / dword_77F404);
      v13 = (int)dwValue / dword_77F404;
      v7 = v6;
      v14 = v6 + dword_77F404;
      if ( v6 < v6 + dword_77F404 )
      {
        v8 = 36 * v6 + 9032344;
        v9 = nArg3 - 140;
        do
        {
          sprintf(&Buffer, "%d", v15++);
          sub_416430(dword_9D3BC8, pArg2 - 10, v9, *(this + 32), &Buffer);
          sub_416430(dword_9D3BC8, pArg2, v9, *(this + 32), v8);
          if ( dword_77F4002 == v7 )
          {
            sub_416430(dword_9D3BC8, pArg2 + 1, v9, -16725766, v8);
            sub_416430(dword_9D3BC8, pArg2 - 9, v9, -16725766, &Buffer);
          }
          ++v7;
          v9 += 13;
          v8 += 36;
        }
        while ( v7 < v14 );
        dword_77F4042 = dword_77F4043;
        v5 = v13;
      }
      sprintf(&Buffer, "%d/%d", v5 + 1, dword_8A6EB02 / dword_77F4042 + 1);
      return sub_416430(dword_9D3BC8, pArg2 - 10, nArg3 - 23, *(this + 32), &Buffer);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x69AEA0 sub_69AEA0
// ------------------------------------------------------------
// 【L1】NCEdit::Render 主绘制：SJIS 首字节判定选取主/次串(+160/+180) →
// sub_4030C0 取显示窗口切片 → sub_402AE0 写渲染串 → 遮罩/直绘两条路径；
// 焦点态(dword_79BE54==id)时按 sub_699000 节拍（274877907e 低位 / 0x1F4 偶数双路径）
// 在测量宽(dword_9D3BD8 vt+16)之后画 "|" 光标
char /*thiscall*/ sub_69AEA0(int this)
{
  int64_t pThis_84; // rax
  int pThis_A0; // ecx
  unsigned int fld_6C; // edx
  int fld_702; // ecx
  char fld_D0; // al
  char *fld_D02; // eax
  uint8_t *v8; // edx
  char v9; // cl
  int v10; // edi
  char *fld_D03; // eax
  uint8_t *v12; // edx
  char v13; // cl
  int v14; // edi
  const char *fld_70; // [esp-8h] [ebp-434h]
  uint32_t v17[5]; // [esp+8h] [ebp-424h] BYREF
  uint8_t pBuf2[512]; // [esp+1Ch] [ebp-410h] BYREF
  uint8_t pBuf[516]; // [esp+21Ch] [ebp-210h] BYREF
  int v20; // [esp+428h] [ebp-4h]

  *(uint32_t *)&pBuf[512] = dword_796E50;
  LOBYTE(pThis_84) = *(uint8_t *)(this + 16);
  if ( (uint8_t)pThis_84 != 0 )
  {
    pThis_A0 = this + 160;
    if ( *(uint32_t *)(this + 192) != 0 )
      pThis_A0 = this + 180;
    LODWORD(pThis_84) = *(uint32_t *)(pThis_A0 + 12);
    if ( (unsigned int)pThis_84 <= 0x1000 && *(uint32_t *)(this + 120) <= 0x1000u )
    {
      fld_70 = *((const char **)sub_4030C0(pThis_A0, v17, *(uint32_t *)(this + 112), *(uint32_t *)(this + 108) / 5u) + 2);
      v20 = 0;
      sub_402AE0(this + 200, fld_70);
      v20 = -1;
      sub_403010(v17);
      fld_6C = *(uint32_t *)(this + 108) / 5u;
      if ( *(uint32_t *)(this + 212) > fld_6C )
      {
        fld_702 = *(uint32_t *)(this + 112);
        fld_D0 = *(uint8_t *)(fld_702 + *(uint32_t *)(this + 208) + fld_6C - 1);
        if ( fld_D0 < 0
          && (fld_D0 == -127
           || fld_D0 == -126
           || fld_D0 == -125
           || fld_D0 == -124
           || fld_D0 == -121
           || fld_D0 == -120
           || fld_D0 == -119
           || fld_D0 == -118
           || fld_D0 == -117
           || fld_D0 == -116
           || fld_D0 == -115
           || fld_D0 == -114
           || fld_D0 == -113
           || fld_D0 == -112
           || fld_D0 == -111
           || fld_D0 == -110
           || fld_D0 == -109
           || fld_D0 == -108
           || fld_D0 == -107
           || fld_D0 == -106
           || fld_D0 == -105
           || fld_D0 == -104
           || fld_D0 == -103
           || fld_D0 == -102
           || fld_D0 == -101
           || fld_D0 == -100
           || fld_D0 == -99
           || fld_D0 == -98
           || fld_D0 == -97
           || fld_D0 == -32
           || fld_D0 == -31
           || fld_D0 == -30
           || fld_D0 == -29
           || fld_D0 == -28
           || fld_D0 == -27
           || fld_D0 == -26
           || fld_D0 == -25
           || fld_D0 == -24
           || fld_D0 == -23
           || fld_D0 == -22
           || fld_D0 == -19
           || fld_D0 == -18
           || fld_D0 == -6
           || fld_D0 == -5
           || fld_D0 == -4) )
        {
          sub_402DE0(this + 200, fld_6C + fld_702, 1);
        }
      }
      if ( dword_9D3BD8 != 0 )
      {
        sub_69ACE0(*(uint32_t *)(this + 20), *(uint32_t *)(this + 24));
        LOBYTE(pThis_84) = sub_416430(
                       (void *)dword_9D3BD8,
                       dword_9D3BC8,
                       *(uint32_t *)(this + 20),
                       *(uint32_t *)(this + 24),
                       *(uint32_t *)(this + 128),
                       *(uint32_t *)(this + 208));
        if ( *(uint32_t *)(this + 12) == dword_79BE54 )
        {
          memset(pBuf, 0, 512);
          fld_D02 = *(char **)(this + 208);
          v8 = (uint8_t *)(pBuf - fld_D02);
          do
          {
            v9 = *fld_D02;
            v8[(uint32_t)fld_D02] = *fld_D02;
            ++fld_D02;
          }
          while ( v9 != 0 );
          if ( *(uint32_t *)(this + 120) >= 0x200u )
            *(uint32_t *)(this + 120) = 0;
          if ( *(uint32_t *)(this + 224) >= 0x200u )
            *(uint32_t *)(this + 224) = 0;
          if ( *(uint8_t *)(this + 117) != 0 )
            pBuf[*(uint32_t *)(this + 224)] = 0;
          else
            pBuf[*(uint32_t *)(this + 120)] = 0;
          v10 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_9D3BD8 + 16))(dword_9D3BD8, pBuf) - 2;
          pThis_84 = 274877907LL * (unsigned int)sub_699000(this + 132);  // 【clock_now(clk)】
          if ( (pThis_84 & 0x2000000000LL) != 0 && *(uint32_t *)(this + 192) == 0 )
            LOBYTE(pThis_84) = sub_416430(
                           (void *)dword_9D3BD8,
                           dword_9D3BC8,
                           v10 + *(uint32_t *)(this + 20),
                           *(uint32_t *)(this + 24),
                           *(uint32_t *)(this + 128),
                           (int)"|");
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_9D3BC8 + 72))(dword_9D3BC8, 0);
        (*(void (/*cdecl*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)dword_9D3BC8 + 80))(
          dword_9D3BC8,
          *(uint32_t *)(this + 20),
          *(uint32_t *)(this + 24),
          *(uint32_t *)(this + 128),
          *(uint32_t *)(this + 208));
        sub_69ACE0(*(uint32_t *)(this + 20), *(uint32_t *)(this + 24));
        if ( *(uint32_t *)(this + 12) == dword_79BE54 )
        {
          memset(pBuf2, 0, sizeof(pBuf2));
          fld_D03 = *(char **)(this + 208);
          v12 = (uint8_t *)(pBuf2 - fld_D03);
          do
          {
            v13 = *fld_D03;
            v12[(uint32_t)fld_D03] = *fld_D03;
            ++fld_D03;
          }
          while ( v13 != 0 );
          if ( *(uint32_t *)(this + 120) >= 0x200u )
            *(uint32_t *)(this + 120) = 0;
          if ( *(uint32_t *)(this + 224) >= 0x200u )
            *(uint32_t *)(this + 224) = 0;
          if ( *(uint8_t *)(this + 117) != 0 )
            pBuf2[*(uint32_t *)(this + 224)] = 0;
          else
            pBuf2[*(uint32_t *)(this + 120)] = 0;
          v14 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_9D3BD8 + 16))(dword_9D3BD8, pBuf2) - 2;
          if ( ((sub_699000(this + 132) / 0x1F4u) & 1) != 0 && *(uint32_t *)(this + 192) == 0 )  // 【clock_now(clk)】
            sub_416430(
              (void *)dword_9D3BD8,
              dword_9D3BC8,
              v14 + *(uint32_t *)(this + 20),
              *(uint32_t *)(this + 24),
              *(uint32_t *)(this + 128),
              (int)"|");
        }
        LOBYTE(pThis_84) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_9D3BC8 + 76))(dword_9D3BC8);
      }
    }
  }
  return pThis_84;
}


// ------------------------------------------------------------
// 0x69B2E0 sub_69B2E0
// ------------------------------------------------------------
// 【L1】NCEdit::滚动窗口：a2=0 右滚 / =1 左滚，步进 = 缓冲(+27)/5，
// 滚动时逐字节 SJIS 双字节感知（首字节表）避免劈开全角字符
unsigned int /*thiscall*/ sub_69B2E0(unsigned int *this, unsigned int uArg2)
{
  unsigned int result; // eax
  int fld_e422; // esi
  int fld_e283; // edx
  char v5; // al
  int fld_e28; // esi
  unsigned int fld_e30; // edi
  unsigned int fld_e27; // ebx
  int fld_e42; // esi
  int fld_e282; // edx
  char v11; // al

  result = uArg2;
  if ( uArg2 != 0 )
  {
    if ( uArg2 == 1 )
    {
      fld_e28 = *(this + 28);
      if ( fld_e28 != 0 )
      {
        fld_e30 = *(this + 30);
        if ( fld_e30 == fld_e28 )
        {
          result = -858993459 * *(this + 27);
          fld_e27 = *(this + 27) / 0xA;
          if ( fld_e30 < fld_e27 + fld_e28 )
          {
            fld_e42 = *(this + 42);
            do
            {
              fld_e282 = *(this + 28);
              v11 = *(uint8_t *)(fld_e42 + fld_e282 - 1);
              if ( v11 < 0
                && (v11 == -127
                 || v11 == -126
                 || v11 == -125
                 || v11 == -124
                 || v11 == -121
                 || v11 == -120
                 || v11 == -119
                 || v11 == -118
                 || v11 == -117
                 || v11 == -116
                 || v11 == -115
                 || v11 == -114
                 || v11 == -113
                 || v11 == -112
                 || v11 == -111
                 || v11 == -110
                 || v11 == -109
                 || v11 == -108
                 || v11 == -107
                 || v11 == -106
                 || v11 == -105
                 || v11 == -104
                 || v11 == -103
                 || v11 == -102
                 || v11 == -101
                 || v11 == -100
                 || v11 == -99
                 || v11 == -98
                 || v11 == -97
                 || v11 == -32
                 || v11 == -31
                 || v11 == -30
                 || v11 == -29
                 || v11 == -28
                 || v11 == -27
                 || v11 == -26
                 || v11 == -25
                 || v11 == -24
                 || v11 == -23
                 || v11 == -22
                 || v11 == -19
                 || v11 == -18
                 || v11 == -6
                 || v11 == -5
                 || v11 == -4) )
              {
                *(this + 28) = fld_e282 - 1;
              }
              result = *(this + 28) - 1;
              *(this + 28) = result;
              if ( result == 0 )
                break;
              result += fld_e27;
            }
            while ( *(this + 30) < result );
          }
        }
      }
    }
  }
  else
  {
    result = *(this + 30);
    if ( result > *(this + 28) + *(this + 27) / 5 )
    {
      fld_e422 = *(this + 42);
      do
      {
        fld_e283 = *(this + 28);
        v5 = *(uint8_t *)(fld_e422 + fld_e283);
        if ( v5 < 0
          && (v5 == -127
           || v5 == -126
           || v5 == -125
           || v5 == -124
           || v5 == -121
           || v5 == -120
           || v5 == -119
           || v5 == -118
           || v5 == -117
           || v5 == -116
           || v5 == -115
           || v5 == -114
           || v5 == -113
           || v5 == -112
           || v5 == -111
           || v5 == -110
           || v5 == -109
           || v5 == -108
           || v5 == -107
           || v5 == -106
           || v5 == -105
           || v5 == -104
           || v5 == -103
           || v5 == -102
           || v5 == -101
           || v5 == -100
           || v5 == -99
           || v5 == -98
           || v5 == -97
           || v5 == -32
           || v5 == -31
           || v5 == -30
           || v5 == -29
           || v5 == -28
           || v5 == -27
           || v5 == -26
           || v5 == -25
           || v5 == -24
           || v5 == -23
           || v5 == -22
           || v5 == -19
           || v5 == -18
           || v5 == -6
           || v5 == -5
           || v5 == -4) )
        {
          *(this + 28) = fld_e283 + 1;
        }
        ++*(this + 28);
        result = *(this + 30);
      }
      while ( result > *(this + 28) + *(this + 27) / 5 );
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x69B590 sub_69B590
// ------------------------------------------------------------
// 【L1】nIIme 组合串宽度适配：字体引擎 dword_9D3BD8 vt+16 测宽，
// 超宽时 vt+24 逐字截断（返回截断长度，a2[result-1]=0）
int /*thiscall*/ sub_69B590(unsigned int *this, const char *pArg2, int *pDwArg3)
{
  unsigned int fld_e42; // eax
  unsigned int fld_e27; // ecx
  int result; // eax

  fld_e42 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_9D3BD8 + 16))(dword_9D3BD8, *(this + 42));
  fld_e27 = *(this + 27);
  if ( fld_e42 < fld_e27 )
  {
    result = (*(int (/*thiscall*/ **)(int, const char *, unsigned int))(*(uint32_t *)dword_9D3BD8 + 24))(
               dword_9D3BD8,
               pArg2,
               fld_e27 - fld_e42);
    if ( result != -1 )
    {
      pArg2[result - 1] = 0;
      result = strlen(pArg2);
      *pDwArg3 = result;
    }
  }
  else
  {
    *pArg2 = 0;
    *pDwArg3 = 0;
    return (int)pArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x69B600 sub_69B600
// ------------------------------------------------------------
// 【L1】NCEdit::CaretLeft：光标(+30)左移，跨过 SJIS 双字节则 -2（防劈字）
void /*thiscall*/ sub_69B600(unsigned int *this)
{
  unsigned int fld_e30; // esi
  unsigned int i; // edx
  char fld_e42; // al
  char v4; // al

  fld_e30 = *(this + 30);
  if ( fld_e30 != 0 )
  {
    for ( i = 0; i < fld_e30; ++i )
    {
      fld_e42 = *(uint8_t *)(*(this + 42) + i);
      if ( fld_e42 < 0
        && (fld_e42 == -127
         || fld_e42 == -126
         || fld_e42 == -125
         || fld_e42 == -124
         || fld_e42 == -121
         || fld_e42 == -120
         || fld_e42 == -119
         || fld_e42 == -118
         || fld_e42 == -117
         || fld_e42 == -116
         || fld_e42 == -115
         || fld_e42 == -114
         || fld_e42 == -113
         || fld_e42 == -112
         || fld_e42 == -111
         || fld_e42 == -110
         || fld_e42 == -109
         || fld_e42 == -108
         || fld_e42 == -107
         || fld_e42 == -106
         || fld_e42 == -105
         || fld_e42 == -104
         || fld_e42 == -103
         || fld_e42 == -102
         || fld_e42 == -101
         || fld_e42 == -100
         || fld_e42 == -99
         || fld_e42 == -98
         || fld_e42 == -97
         || fld_e42 == -32
         || fld_e42 == -31
         || fld_e42 == -30
         || fld_e42 == -29
         || fld_e42 == -28
         || fld_e42 == -27
         || fld_e42 == -26
         || fld_e42 == -25
         || fld_e42 == -24
         || fld_e42 == -23
         || fld_e42 == -22
         || fld_e42 == -19
         || fld_e42 == -18
         || fld_e42 == -6
         || fld_e42 == -5
         || fld_e42 == -4) )
      {
        ++i;
        v4 = 1;
      }
      else
      {
        v4 = 0;
      }
    }
    if ( v4 != 0 )
      *(this + 30) = fld_e30 - 2;
    else
      *(this + 30) = fld_e30 - 1;
  }
}



// ------------------------------------------------------------
// 0x69B740 sub_69B740
// ------------------------------------------------------------
// 【L1】NCEdit::GetMaxLength?：sub_402EA0(10,32) 后返回主串长度(+168 槽)【推断】
int /*thiscall*/ sub_69B740(int this)
{
  int pThis_A0; // esi

  if ( *(uint8_t *)(this + 4) == 0 )
    return 0;
  pThis_A0 = this + 160;
  if ( *(uint32_t *)(this + 192) != 0 )
    pThis_A0 = this + 180;
  sub_402EA0(10, 32);
  return *(uint32_t *)(pThis_A0 + 8);
}



// ------------------------------------------------------------
// 0x69B780 sub_69B780
// ------------------------------------------------------------
// 【L1】NCEdit::ClearString(str)：memset(str.ptr, 0, cap+1)，长度(+12)=0
char /*thiscall*/ sub_69B780(int this)
{
  char result; // al

  result = *(uint8_t *)(this + 4);
  if ( result != 0 )
  {
    memset(*(void **)(this + 8), 0, *(uint32_t *)(this + 16) + 1);
    *(uint32_t *)(this + 12) = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x69B7B0 sub_69B7B0
// ------------------------------------------------------------
// 【L1】NCEdit::Backspace：主串(+168)末字节 SJIS 判定 → 退 2 或 1 字节
// （sub_402DE0 区间置 0），长度 -2/-1，随后 69B2E0 左滚同步；
// 次串(+184 就绪)存在时优先清次串
int /*thiscall*/ sub_69B7B0(int this)
{
  int fld_78; // edx
  int v3; // ecx
  char fld_A8; // al
  char v5; // al

  if ( *(uint32_t *)(this + 192) != 0 && *(uint8_t *)(this + 184) != 0 )
  {
    memset(*(void **)(this + 188), 0, *(uint32_t *)(this + 196) + 1);
    *(uint32_t *)(this + 192) = 0;
  }
  fld_78 = *(uint32_t *)(this + 120);
  if ( fld_78 != 0 )
  {
    v3 = 0;
    if ( fld_78 > 0 )
    {
      do
      {
        fld_A8 = *(uint8_t *)(*(uint32_t *)(this + 168) + v3);
        if ( fld_A8 < 0
          && (fld_A8 == -127
           || fld_A8 == -126
           || fld_A8 == -125
           || fld_A8 == -124
           || fld_A8 == -121
           || fld_A8 == -120
           || fld_A8 == -119
           || fld_A8 == -118
           || fld_A8 == -117
           || fld_A8 == -116
           || fld_A8 == -115
           || fld_A8 == -114
           || fld_A8 == -113
           || fld_A8 == -112
           || fld_A8 == -111
           || fld_A8 == -110
           || fld_A8 == -109
           || fld_A8 == -108
           || fld_A8 == -107
           || fld_A8 == -106
           || fld_A8 == -105
           || fld_A8 == -104
           || fld_A8 == -103
           || fld_A8 == -102
           || fld_A8 == -101
           || fld_A8 == -100
           || fld_A8 == -99
           || fld_A8 == -98
           || fld_A8 == -97
           || fld_A8 == -32
           || fld_A8 == -31
           || fld_A8 == -30
           || fld_A8 == -29
           || fld_A8 == -28
           || fld_A8 == -27
           || fld_A8 == -26
           || fld_A8 == -25
           || fld_A8 == -24
           || fld_A8 == -23
           || fld_A8 == -22
           || fld_A8 == -19
           || fld_A8 == -18
           || fld_A8 == -6
           || fld_A8 == -5
           || fld_A8 == -4) )
        {
          v3 += 2;
          v5 = 1;
        }
        else
        {
          ++v3;
          v5 = 0;
        }
      }
      while ( v3 < fld_78 );
      if ( v5 != 0 )
      {
        sub_402DE0(fld_78 - 2, 2);
        *(uint32_t *)(this + 120) -= 2;
        sub_69B2E0((unsigned int *)this, 1u);
        return 0;
      }
    }
    sub_402DE0(fld_78 - 1, 1);
    --*(uint32_t *)(this + 120);
    sub_69B2E0((unsigned int *)this, 1u);
  }
  return 0;
}



// ------------------------------------------------------------
// 0x69B970 sub_69B970
// ------------------------------------------------------------
// 【L1】NCEdit::Delete：光标处 SJIS 双字节则先 sub_402DE0(+1)，再删 1 字节；
// 清 byte_8A6298[0x400] 虚键缓冲与 byte_8A6E9A
char /*thiscall*/ sub_69B970(int this)
{
  int fld_C0; // eax
  int fld_78; // ecx
  char fld_A8; // al

  fld_C0 = *(uint32_t *)(this + 192);
  if ( fld_C0 != 0 )
  {
    LOBYTE(fld_C0) = *(uint8_t *)(this + 184);
    if ( (uint8_t)fld_C0 != 0 )
    {
      LOBYTE(fld_C0) = 0;
      memset(*(void **)(this + 188), 0, *(uint32_t *)(this + 196) + 1);
      *(uint32_t *)(this + 192) = 0;
    }
  }
  fld_78 = *(uint32_t *)(this + 120);
  if ( *(uint32_t *)(this + 172) != fld_78 )
  {
    fld_A8 = *(uint8_t *)(fld_78 + *(uint32_t *)(this + 168));
    if ( fld_A8 < 0
      && (fld_A8 == -127
       || fld_A8 == -126
       || fld_A8 == -125
       || fld_A8 == -124
       || fld_A8 == -121
       || fld_A8 == -120
       || fld_A8 == -119
       || fld_A8 == -118
       || fld_A8 == -117
       || fld_A8 == -116
       || fld_A8 == -115
       || fld_A8 == -114
       || fld_A8 == -113
       || fld_A8 == -112
       || fld_A8 == -111
       || fld_A8 == -110
       || fld_A8 == -109
       || fld_A8 == -108
       || fld_A8 == -107
       || fld_A8 == -106
       || fld_A8 == -105
       || fld_A8 == -104
       || fld_A8 == -103
       || fld_A8 == -102
       || fld_A8 == -101
       || fld_A8 == -100
       || fld_A8 == -99
       || fld_A8 == -98
       || fld_A8 == -97
       || fld_A8 == -32
       || fld_A8 == -31
       || fld_A8 == -30
       || fld_A8 == -29
       || fld_A8 == -28
       || fld_A8 == -27
       || fld_A8 == -26
       || fld_A8 == -25
       || fld_A8 == -24
       || fld_A8 == -23
       || fld_A8 == -22
       || fld_A8 == -19
       || fld_A8 == -18
       || fld_A8 == -6
       || fld_A8 == -5
       || fld_A8 == -4) )
    {
      sub_402DE0(fld_78, 1);
    }
    sub_402DE0(*(uint32_t *)(this + 120), 1);
    memset(&byte_8A6298, 0, 0x400u);
    byte_8A6E9A = 0;
    LOBYTE(fld_C0) = 0;
  }
  return fld_C0;
}



// ------------------------------------------------------------
// 0x69BAF0 sub_69BAF0
// ------------------------------------------------------------
// 【L1】NCEdit::MoveCaret(key)：37 '%'/VK_LEFT → CaretLeft(69B600)；
// 39 '''(VK_RIGHT) → +1 或 SJIS +2；36 '$'/VK_HOME → 光标=0(+112=0)；
// 35 '#'/VK_END → 光标=串长(+172)。a2 指向 byte_8A6298 虚键缓冲。
char /*thiscall*/ sub_69BAF0(int this, char *pszArg2)
{
  char result; // al
  unsigned int *v4; // ecx
  int fld_78; // ecx
  char fld_A8; // al

  if ( *(uint32_t *)(this + 192) != 0 && *(uint8_t *)(this + 184) != 0 )
  {
    memset(*(void **)(this + 188), 0, *(uint32_t *)(this + 196) + 1);
    *(uint32_t *)(this + 192) = 0;
  }
  result = *pszArg2;
  if ( *pszArg2 == 37 )
  {
    if ( *(uint32_t *)(this + 120) != 0 )
    {
      sub_69B600((unsigned int *)this);
      return sub_69B2E0(v4, 1u);
    }
  }
  else
  {
    switch ( result )
    {
      case '\'':
        fld_78 = *(uint32_t *)(this + 120);
        if ( fld_78 != *(uint32_t *)(this + 172) )
        {
          fld_A8 = *(uint8_t *)(fld_78 + *(uint32_t *)(this + 168));
          if ( fld_A8 < 0
            && (fld_A8 == -127
             || fld_A8 == -126
             || fld_A8 == -125
             || fld_A8 == -124
             || fld_A8 == -121
             || fld_A8 == -120
             || fld_A8 == -119
             || fld_A8 == -118
             || fld_A8 == -117
             || fld_A8 == -116
             || fld_A8 == -115
             || fld_A8 == -114
             || fld_A8 == -113
             || fld_A8 == -112
             || fld_A8 == -111
             || fld_A8 == -110
             || fld_A8 == -109
             || fld_A8 == -108
             || fld_A8 == -107
             || fld_A8 == -106
             || fld_A8 == -105
             || fld_A8 == -104
             || fld_A8 == -103
             || fld_A8 == -102
             || fld_A8 == -101
             || fld_A8 == -100
             || fld_A8 == -99
             || fld_A8 == -98
             || fld_A8 == -97
             || fld_A8 == -32
             || fld_A8 == -31
             || fld_A8 == -30
             || fld_A8 == -29
             || fld_A8 == -28
             || fld_A8 == -27
             || fld_A8 == -26
             || fld_A8 == -25
             || fld_A8 == -24
             || fld_A8 == -23
             || fld_A8 == -22
             || fld_A8 == -19
             || fld_A8 == -18
             || fld_A8 == -6
             || fld_A8 == -5
             || fld_A8 == -4) )
          {
            *(uint32_t *)(this + 120) = fld_78 + 2;
            return sub_69B2E0((unsigned int *)this, 0);
          }
          else
          {
            *(uint32_t *)(this + 120) = fld_78 + 1;
            return sub_69B2E0((unsigned int *)this, 0);
          }
        }
        break;
      case '$':
        *(uint32_t *)(this + 120) = 0;
        *(uint32_t *)(this + 112) = 0;
        break;
      case '#':
        *(uint32_t *)(this + 120) = *(uint32_t *)(this + 172);
        return sub_69B2E0((unsigned int *)this, 0);
      default:
        break;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x69BCC0 sub_69BCC0
// ------------------------------------------------------------
// 【L1】NCEdit::Empty（自证串 "\n NCEdit::Empty() call"）：
// 全串清零（主/次/三块 IME 全局），标志位清零后 sub_40BE20 打调试串 +
// sub_407430 收尾，byte_9D3BE4=0
int /*usercall*/ sub_69BCC0@<eax>(int pArg1@<ecx>, char pszArg2@<dil>)
{
  if ( *(uint8_t *)(pArg1 + 4) == 0 )
    return -2147483647;
  *(uint32_t *)(pArg1 + 120) = 0;
  *(uint32_t *)(pArg1 + 124) = 0;
  *(uint32_t *)(pArg1 + 112) = 0;
  *(uint8_t *)(pArg1 + 117) = 0;
  *(uint8_t *)(pArg1 + 116) = 0;
  if ( *(uint8_t *)(pArg1 + 164) != 0 )
  {
    memset(*(void **)(pArg1 + 168), 0, *(uint32_t *)(pArg1 + 176) + 1);
    *(uint32_t *)(pArg1 + 172) = 0;
  }
  if ( *(uint8_t *)(pArg1 + 184) != 0 )
  {
    memset(*(void **)(pArg1 + 188), 0, *(uint32_t *)(pArg1 + 196) + 1);
    *(uint32_t *)(pArg1 + 192) = 0;
  }
  memset(&byte_8A6A98, 0, 0x400u);
  memset(&byte_8A6698, 0, 0x400u);
  memset(&byte_8A6298, 0, 0x400u);
  byte_8A6E9A = 0;
  sub_40BE20("\n NCEdit::Empty() call", pszArg2);
  sub_407430();
  byte_9D3BE4 = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x69BD90 sub_69BD90
// ------------------------------------------------------------
// 【L1】NCEdit::SetStringf：vsprintf → 写主串（sub_402EF0），光标置末尾(69B2E0)，
// 次串就绪时清次串。外部注入文本入口。
int sub_69BD90(int pArg1, char *Format, ...)
{
  va_list va; // [esp+14h] [ebp+10h] BYREF

  va_start(va, Format);
  if ( *(uint8_t *)(pArg1 + 4) == 0 )
    return -2147483647;
  sub_402EF0(Format, va);
  *(uint32_t *)(pArg1 + 120) = *(uint32_t *)(pArg1 + 172);
  sub_69B2E0((unsigned int *)pArg1, 0);
  if ( *(uint32_t *)(pArg1 + 192) != 0 && *(uint8_t *)(pArg1 + 184) != 0 )
  {
    memset(*(void **)(pArg1 + 188), 0, *(uint32_t *)(pArg1 + 196) + 1);
    *(uint32_t *)(pArg1 + 192) = 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x69BE10 sub_69BE10
// ------------------------------------------------------------
// 【L1】★★ nIIme::IsEndComposition：IME 组合泵（自证串 x5）
// 仅焦点控件(dword_79BE54==+12)处理；逐帧链:
// 1) byte_8A6E98 提交标志 → +116=1；
// 2) byte_8A6E9A 上屏标志 → sub_69BAF0 处理虚键，'.'(46)→Delete(69B970)，
// 清 A/B/虚键三缓冲与标志；
// 3) 否则 +221 IME 重聚焦分支清主串，或恢复字体引擎(dword_8A6EB8)；
// 4) 组合串 A(byte_8A6A98) 非空: 首字节==8(VK_BACK)→Backspace(69B7B0)；
// 非 ESC(27) → "Composition Success" 路径: 宽度适配(69B590)、
// m_MaxLen(+104) 封顶、光标处拼接(dword_9D3BE8=IME 插入偏移)、+220 变更=1；
// 5) byte_8A6E9C 组合中 → 串 B 上屏提交；
// 6) 串 B(byte_8A6698) 有效(byte_8A6E9B): 超长 → sub_407400
// completeIMEComposit 强制上屏；否则边组合边拼入主串（+117=1 组合中）；
// 7) IME 下划线光标 +224 = dword_8A6EA8 + caret - dword_9D3BE8；
// 尾部: 主/次串共存时清次串；最后虚槽 +28 基类 Update。
int /*usercall*/ sub_69BE10@<eax>(int pArg1@<ecx>, char pszArg2@<bl>)
{
  int v3; // eax
  int result; // eax
  unsigned int nLen; // kr00_4
  bool v6; // zf
  unsigned int nLen32; // ebx
  int dword_9D3BE82; // eax
  int v9; // ecx
  unsigned int v10; // ecx
  unsigned int v11; // edx
  unsigned int v12; // eax
  int v13; // eax
  int nLen22; // ebx
  unsigned int v15; // edi
  int dword_9D3BE84; // eax
  int v17; // ecx
  char v18; // [esp-14h] [ebp-20h]
  int v19; // [esp-10h] [ebp-1Ch]
  char v20; // [esp-10h] [ebp-1Ch]
  char v21; // [esp-10h] [ebp-1Ch]
  int dword_9D3BE83; // [esp-Ch] [ebp-18h]
  int v23; // [esp-Ch] [ebp-18h]
  char v24; // [esp-Ch] [ebp-18h]
  char pszArg22; // [esp-8h] [ebp-14h]
  char v26; // [esp-8h] [ebp-14h]
  unsigned int nLen3; // [esp+4h] [ebp-8h] BYREF
  unsigned int nLen2; // [esp+8h] [ebp-4h] BYREF

  v3 = *(uint32_t *)(pArg1 + 12);
  *(uint8_t *)(pArg1 + 220) = 0;
  if ( v3 == dword_79BE54 )
  {
    if ( *(uint8_t *)(pArg1 + 17) == 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 28))(pArg1);
      byte_8A6E98 = 0;
      return result;
    }
    nLen = strlen(&byte_8A6A98);
    nLen3 = nLen;
    nLen2 = strlen(&byte_8A6698);
    v6 = byte_8A6E98 == 0;
    byte_8A6E98 = 0;
    if ( !v6 && *(uint8_t *)(pArg1 + 17) != 0 )
      *(uint8_t *)(pArg1 + 116) = 1;
    if ( byte_8A6E9A != 0 )
    {
      sub_69BAF0(&byte_8A6298);
      if ( byte_8A6298 == 46 )
        sub_69B970(pArg1);
      memset(&byte_8A6A98, 0, 0x400u);
      memset(&byte_8A6698, 0, 0x400u);
      memset(&byte_8A6298, 0, 0x400u);
      byte_8A6E9A = 0;
      *(uint8_t *)(pArg1 + 117) = 0;
    }
    else
    {
      if ( *(uint8_t *)(pArg1 + 221) != 0 && dword_79BE54 == *(uint32_t *)(pArg1 + 12) )
      {
        dword_9D3BE8 = 0;
        sub_69B780(pArg1 + 160);
        byte_8A6EAC = 0;
      }
      else
      {
        dword_8A6EB8 = dword_9D3BD8;
        byte_8A6EAC = 1;
      }
      pszArg22 = pszArg2;
      if ( nLen != 0 )
      {
        if ( byte_8A6A98 == 8 )
        {
          sub_69B7B0(pArg1);
          memset(&byte_8A6A98, 0, 0x400u);
        }
        else
        {
          if ( *(uint8_t *)(pArg1 + 117) != 0 || byte_8A6A98 != 27 )
          {
            sub_40BE20("\n\n Composition Success---------------------", pszArg2);
            sub_40BE20("\n 1. pBuffer : %s, %d", (char)&byte_8A6A98);
            sub_69B590(&byte_8A6A98, &nLen3);
            nLen32 = nLen3;
            sub_40BE20("\n 2. pBuffer : %s, %d", (char)&byte_8A6A98);
            sub_40BE20("\n 3. MaxLen <%d>, m_String<%d, %s>", *(uint32_t *)(pArg1 + 104));
            if ( *(uint32_t *)(pArg1 + 104) >= *(uint32_t *)(pArg1 + 172) )
            {
              dword_9D3BE82 = dword_9D3BE8;
              v9 = *(uint32_t *)(pArg1 + 120) - dword_9D3BE8;
              *(uint32_t *)(pArg1 + 120) = v9;
              sub_402DE0(v9, dword_9D3BE82);
              sub_402CB0(*(uint32_t *)(pArg1 + 120), &byte_8A6A98);
              v10 = *(uint32_t *)(pArg1 + 104);
              v11 = *(uint32_t *)(pArg1 + 172);
              v12 = nLen32 + *(uint32_t *)(pArg1 + 120);
              *(uint32_t *)(pArg1 + 120) = v12;
              if ( v10 < v11 )
              {
                sub_402DE0(v12, nLen32);
                *(uint32_t *)(pArg1 + 120) -= nLen32;
                sub_40BE20("\n m_String <%d, %s>, m_dwCaretPos : %d", *(uint32_t *)(pArg1 + 172));
              }
              v18 = *(uint32_t *)(pArg1 + 172);
              dword_9D3BE8 = 0;
              sub_40BE20("\n 4. m_String <%d, %s>, m_dwCaretPos : %d\n", v18);
            }
            *(uint8_t *)(pArg1 + 220) = 1;
            *(uint8_t *)(pArg1 + 117) = 0;
            byte_9D3BE4 = 0;
            sub_40BE20("\n 5. end-------------------------------", v26);
          }
          memset(&byte_8A6A98, 0, 0x400u);
        }
      }
      else
      {
        v6 = byte_8A6E9C == 0;
        byte_8A6E9C = 0;
        if ( !v6 )
        {
          sub_40BE20("nIIme::IsEndComposition()...pCompositBuffer_1 : %s", (char)&byte_8A6698);
          sub_69B590(&byte_8A6698, &nLen2);
          sub_40BE20("nIIme::IsEndComposition()...pCompositBuffer_2 : %s", (char)&byte_8A6698);
          sub_40BE20(
            "\nIIme::IsEndComposition().... : <%s>, pBuffer : <%s>, m_dwCaretPos : %d\n",
            *(uint32_t *)(pArg1 + 168));
          v13 = *(uint32_t *)(pArg1 + 120);
          if ( v13 != 0 )
          {
            dword_9D3BE83 = dword_9D3BE8;
            v19 = v13 - dword_9D3BE8;
            *(uint32_t *)(pArg1 + 120) = v13 - dword_9D3BE8;
            sub_402DE0(v19, dword_9D3BE83);
            sub_402CB0(*(uint32_t *)(pArg1 + 120), &byte_8A6698);
            dword_9D3BE8 = 0;
          }
          *(uint8_t *)(pArg1 + 220) = 1;
          *(uint32_t *)(pArg1 + 224) = 0;
          dword_8A6EA8 = 0;
          *(uint8_t *)(pArg1 + 117) = 0;
          byte_9D3BE4 = 0;
          sub_40BE20("nIIme::IsEndComposition()...pCompositBuffer_3 : %s", *(uint32_t *)(pArg1 + 168));
        }
      }
      if ( nLen2 != 0 && byte_8A6E9B != 0 )
      {
        sub_69B590(&byte_8A6698, &nLen2);
        nLen22 = nLen2;
        v15 = *(uint32_t *)(pArg1 + 172);
        if ( *(uint8_t *)(pArg1 + 117) != 0 )
        {
          sub_40BE20("\n ......<check_len2 : %d>", *(uint32_t *)(pArg1 + 172));
        }
        else
        {
          v15 += nLen2;
          sub_40BE20("\n ......<check_len1 : %d, %d>", v15);
        }
        if ( *(uint32_t *)(pArg1 + 104) < v15 )
        {
          sub_40BE20("\n --------------------------", pszArg22);
          sub_40BE20("\n completeIMEComposit call", v24);
          sub_40BE20("\n --------------------------", v21);
          sub_407400();
        }
        else
        {
          dword_9D3BE84 = dword_9D3BE8;
          v17 = *(uint32_t *)(pArg1 + 120) - dword_9D3BE8;
          *(uint32_t *)(pArg1 + 120) = v17;
          sub_402DE0(v17, dword_9D3BE84);
          sub_402CB0(*(uint32_t *)(pArg1 + 120), &byte_8A6698);
          v23 = nLen22 + *(uint32_t *)(pArg1 + 120);
          v20 = *(uint32_t *)(pArg1 + 168);
          dword_9D3BE8 = nLen22;
          *(uint32_t *)(pArg1 + 120) = v23;
          sub_40BE20("\n ......composit ing... : <%s>, m_dwCaretPos : %d\n", v20);
        }
        *(uint8_t *)(pArg1 + 220) = 1;
        *(uint8_t *)(pArg1 + 117) = 1;
        byte_9D3BE4 = 1;
        sub_40BE20("\n\n ing : %d", 1);
        memset(&byte_8A6698, 0, 0x400u);
      }
      if ( *(uint8_t *)(pArg1 + 117) != 0 )
        *(uint32_t *)(pArg1 + 224) = dword_8A6EA8 + *(uint32_t *)(pArg1 + 120) - dword_9D3BE8;
    }
    if ( *(uint32_t *)(pArg1 + 172) != 0 && *(uint32_t *)(pArg1 + 192) != 0 )
      sub_69B780(pArg1 + 180);
  }
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 28))(pArg1);
}



// ============================================================
// SECTION 7  UI 派生控件族（0x69C2D0-0x69DE30）
// ------------------------------------------------------------
// 类型号 = 对象 +8 字段（ctor 直证）: 9 文本列表 / 3 图片框 / 1 按钮
//   / 5 滑条 / 7 标签页 / 6 图片组 / 2 标签。均为 SECTION 5 CNUIObject 派生，
//   纹理经 sub_418DD0 句柄表解析；绘图走渲染器 dword_9D3BC8 或图片 vt+152/+128。
// ============================================================
// ------------------------------------------------------------
// 0x69C2D0 sub_69C2D0
// ------------------------------------------------------------
// 【L1】文本列表控件 ctor（类型 9）：+8=9，子槽(+26)=0
void /*thiscall*/ sub_69C2D0(uint32_t *this)
{
  *(this + 2) = 9;
  *(this + 26) = 0;
}



// ------------------------------------------------------------
// 0x69C2E0 sub_69C2E0
// ------------------------------------------------------------
// 【L1】文本列表 dtor：释放 +104 列表对象（虚删），+8=9 复位，+4=0
int /*thiscall*/ sub_69C2E0(int this)
{
  void (/*thiscall*/ ***pThis_68)(uint32_t, int); // ecx

  pThis_68 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 104);
  if ( pThis_68 != nullptr )
    (**pThis_68)(pThis_68, 1);
  *(uint32_t *)(this + 8) = 9;
  *(uint32_t *)(this + 104) = 0;
  *(uint8_t *)(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x69C310 sub_69C310
// ------------------------------------------------------------
// 【L1】文本列表 Render：可见(+16)时把 +20/+24 位置写入列表对象 +32/+36，
// 尾调 sub_69D780（GDI/渲染器绘制）
char /*thiscall*/ sub_69C310(int this)
{
  char result; // al
  int fld_18; // edx
  int fld_68; // eax

  result = *(uint8_t *)(this + 16);
  if ( result != 0 )
  {
    fld_18 = *(uint32_t *)(this + 24);
    fld_68 = *(uint32_t *)(this + 104);
    *(uint32_t *)(fld_68 + 32) = *(uint32_t *)(this + 20);
    *(uint32_t *)(fld_68 + 36) = fld_18;
    return sub_69D780(*(uint32_t *)(this + 104));
  }
  return result;
}



// ------------------------------------------------------------
// 0x69C340 sub_69C340
// ------------------------------------------------------------
// 【L1】文本列表 Clear：激活时 sub_69D6C0(n)（删 n 行，-1 全清）
int /*thiscall*/ sub_69C340(uint8_t *this, int nArg2)
{
  if ( *(this + 4) != 0 )
    return sub_69D6C0(nArg2);
  else
    return -2147483647;
}



// ------------------------------------------------------------
// 0x69C360 sub_69C360
// ------------------------------------------------------------
// 【L1】文本列表 AddString：激活时 sub_69DB10(文本, 模式)（多行拆分入列）
int /*thiscall*/ sub_69C360(uint8_t *this, int nArg2, int nArg3)
{
  if ( *(this + 4) != 0 )
    return sub_69DB10(nArg2, nArg3);
  else
    return -2147483647;
}



// ------------------------------------------------------------
// 0x69C380 sub_69C380
// ------------------------------------------------------------
// 【L1】文本列表 GetCount：+104 对象 +68 槽（行数）
int /*thiscall*/ sub_69C380(int this)
{
  if ( *(uint8_t *)(this + 4) != 0 )
    return *(uint32_t *)(*(uint32_t *)(this + 104) + 68);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x69C3A0 sub_69C3A0
// ------------------------------------------------------------
// 【L1】文本列表 GetScrollPos：+104 对象 +72 槽
int /*thiscall*/ sub_69C3A0(int this)
{
  if ( *(uint8_t *)(this + 4) != 0 )
    return *(uint32_t *)(*(uint32_t *)(this + 104) + 72);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x69C3C0 sub_69C3C0
// ------------------------------------------------------------
// 【L1】文本列表 setter：+104 对象 +92 槽（描边/阴影开关?）【推断】
char /*thiscall*/ sub_69C3C0(int this, int nArg2)
{
  int fld_68; // eax

  LOBYTE(fld_68) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_68 != 0 )
  {
    fld_68 = *(uint32_t *)(this + 104);
    *(uint32_t *)(fld_68 + 92) = nArg2;
  }
  return fld_68;
}



// ------------------------------------------------------------
// 0x69C3E0 sub_69C3E0
// ------------------------------------------------------------
// 【L1】文本列表 setter：+104 对象 +72 槽（滚动位置）
char /*thiscall*/ sub_69C3E0(int this, int nArg2)
{
  int fld_68; // eax

  LOBYTE(fld_68) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_68 != 0 )
  {
    fld_68 = *(uint32_t *)(this + 104);
    *(uint32_t *)(fld_68 + 72) = nArg2;
  }
  return fld_68;
}



// ------------------------------------------------------------
// 0x69C400 sub_69C400
// ------------------------------------------------------------
// 【L1】文本列表 setter：+104 对象 +68 槽（可见行数?）【推断】
char /*thiscall*/ sub_69C400(int this, int nArg2)
{
  int fld_68; // eax

  LOBYTE(fld_68) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_68 != 0 )
  {
    fld_68 = *(uint32_t *)(this + 104);
    *(uint32_t *)(fld_68 + 68) = nArg2;
  }
  return fld_68;
}



// ------------------------------------------------------------
// 0x69C420 sub_69C420
// ------------------------------------------------------------
// 【L1】文本列表 setter：+104 对象 +64 槽（行高?）【推断】
char /*thiscall*/ sub_69C420(int this, int nArg2)
{
  int fld_68; // eax

  LOBYTE(fld_68) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_68 != 0 )
  {
    fld_68 = *(uint32_t *)(this + 104);
    *(uint32_t *)(fld_68 + 64) = nArg2;
  }
  return fld_68;
}



// ------------------------------------------------------------
// 0x69C440 sub_69C440
// ------------------------------------------------------------
// 【L1】文本列表 setter：+104 对象 +80 槽（滚动上限?）【推断】
char /*thiscall*/ sub_69C440(int this, int nArg2)
{
  int fld_68; // eax

  LOBYTE(fld_68) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_68 != 0 )
  {
    fld_68 = *(uint32_t *)(this + 104);
    *(uint32_t *)(fld_68 + 80) = nArg2;
  }
  return fld_68;
}



// ------------------------------------------------------------
// 0x69C460 sub_69C460
// ------------------------------------------------------------
// 【L1】文本列表 setter：+104 对象 +62 字节（对齐标志?）【推断】
char /*thiscall*/ sub_69C460(int this, char pszArg2)
{
  int fld_68; // eax

  LOBYTE(fld_68) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_68 != 0 )
  {
    fld_68 = *(uint32_t *)(this + 104);
    *(uint8_t *)(fld_68 + 62) = pszArg2;
  }
  return fld_68;
}



// ------------------------------------------------------------
// 0x69C480 sub_69C480
// ------------------------------------------------------------
// 【L1】文本列表 setter：+104 对象 +88 槽（字体颜色 B?）【推断】
char /*thiscall*/ sub_69C480(int this, int nArg2)
{
  int fld_68; // eax

  LOBYTE(fld_68) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_68 != 0 )
  {
    fld_68 = *(uint32_t *)(this + 104);
    *(uint32_t *)(fld_68 + 88) = nArg2;
  }
  return fld_68;
}



// ------------------------------------------------------------
// 0x69C4A0 sub_69C4A0
// ------------------------------------------------------------
// 【L1】文本列表 setter：+104 对象 +76 槽（字体颜色 A?）【推断】
char /*thiscall*/ sub_69C4A0(int this, int nArg2)
{
  int fld_68; // eax

  LOBYTE(fld_68) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_68 != 0 )
  {
    fld_68 = *(uint32_t *)(this + 104);
    *(uint32_t *)(fld_68 + 76) = nArg2;
  }
  return fld_68;
}



// ------------------------------------------------------------
// 0x69C4C0 sub_69C4C0
// ------------------------------------------------------------
// 【L1】控件子槽 setter：*(this+26) 槽 +56 = a2
int /*thiscall*/ sub_69C4C0(uint32_t *this, int nArg2)
{
  int result; // eax

  result = *(this + 26);
  *(uint32_t *)(result + 56) = nArg2;
  return result;
}



// ------------------------------------------------------------
// 0x69C4D0 sub_69C4D0
// ------------------------------------------------------------
// 【L1】文本列表 SetText：虚槽 +12 转发 + 子槽(+26) +8 记录 a2
char /*thiscall*/ sub_69C4D0(uint8_t *this, int nArg2)
{
  char result; // al

  result = *(this + 4);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 12))(this, nArg2);
    *(uint32_t *)(*((uint32_t *)this + 26) + 8) = nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x69C500 sub_69C500
// ------------------------------------------------------------
// 【L1】文本列表 GetCount2：列表对象首尾指针差 >>2（vector<T*> size）
int /*thiscall*/ sub_69C500(int this)
{
  int fld_68; // eax
  int v2; // ecx
  int v3; // eax

  if ( *(uint8_t *)(this + 4) != 0 && (fld_68 = *(uint32_t *)(this + 104), v2 = *(uint32_t *)(fld_68 + 16), v3 = fld_68 + 12, v2 != 0) )
    return (*(uint32_t *)(v3 + 8) - v2) >> 2;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x69C520 sub_69C520
// ------------------------------------------------------------
// 【L1】文本列表 Create：new(0x60) → sub_50F0B0(渲染器, a3, a2) 构造行对象入 +104
// （失败→0x80000008；成功 +4=1）
int /*thiscall*/ sub_69C520(int this, int nArg2, int nArg3)
{
  int v5; // eax

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  if ( operator new(0x60u) != nullptr )
    v5 = sub_50F0B0(dword_9D3BC8, nArg3, nArg2);
  else
    v5 = 0;
  *(uint32_t *)(this + 104) = v5;
  if ( v5 == 0 )
    return -2147483640;
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x69C5D0 sub_69C5D0
// ------------------------------------------------------------
// 【L1】控件复位：子槽(+26/+27/+28)清零
int /*thiscall*/ sub_69C5D0(uint32_t *this)
{
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x69C5E0 sub_69C5E0
// ------------------------------------------------------------
// 【L1】控件复位：+104/+108/+112 清零，+4=0
int /*thiscall*/ sub_69C5E0(int this)
{
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint8_t *)(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x69C600 sub_69C600
// ------------------------------------------------------------
// 【L1】滑条/列表滚轮：可见且激活时按 dword_79BE34==id 判定，
// 经 +112 分组对象 +112 槽 ±1 调 sub_69CAF0(SetScrollPos)
char /*thiscall*/ sub_69C600(int this)
{
  int fld_6C; // eax
  int fld_68; // eax

  LOBYTE(fld_6C) = *(uint8_t *)(this + 16);
  if ( (uint8_t)fld_6C != 0 )
  {
    LOBYTE(fld_6C) = *(uint8_t *)(this + 17);
    if ( (uint8_t)fld_6C != 0 )
    {
      fld_68 = *(uint32_t *)(this + 104);
      if ( *(uint8_t *)(fld_68 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_68 + 12) )
      {
        LOBYTE(fld_6C) = sub_69CAF0(*(uint32_t *)(*(uint32_t *)(this + 112) + 112) - 1);
      }
      else
      {
        fld_6C = *(uint32_t *)(this + 108);
        if ( *(uint8_t *)(fld_6C + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_6C + 12) )
          LOBYTE(fld_6C) = sub_69CAF0(*(uint32_t *)(*(uint32_t *)(this + 112) + 112) + 1);
      }
    }
  }
  return fld_6C;
}



// ------------------------------------------------------------
// 0x69C650 sub_69C650
// ------------------------------------------------------------
// 【L1】控件 Enable(a2)：+112 组对象虚槽+40，+104/+108 两子对象 +17 = a2!=0
bool /*thiscall*/ sub_69C650(int this, int nArg2)
{
  (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 112) + 40))(*(uint32_t *)(this + 112), nArg2);
  *(uint8_t *)(*(uint32_t *)(this + 104) + 17) = nArg2 != 0;
  *(uint8_t *)(*(uint32_t *)(this + 108) + 17) = nArg2 != 0;
  return nArg2 != 0;
}



// ------------------------------------------------------------
// 0x69C680 sub_69C680
// ------------------------------------------------------------
// 【L1】sub_69CAF0 的 stdcall 包装（导出/回调形态）
int /*stdcall*/ sub_69C680(int nArg1)
{
  return sub_69CAF0(nArg1);
}



// ------------------------------------------------------------
// 0x69C6B0 sub_69C6B0
// ------------------------------------------------------------
// 【L1】图片框 ctor（类型 3）：+8=3，子槽(+26)=0
void /*thiscall*/ sub_69C6B0(uint32_t *this)
{
  *(this + 2) = 3;
  *(this + 26) = 0;
}



// ------------------------------------------------------------
// 0x69C6C0 sub_69C6C0
// ------------------------------------------------------------
// 【L1】图片框 SetTexture：sub_418DD0(a3) 句柄解析入 +104，
// 宽高取句柄 +36/+40 到 +28/+32；a2=0 时跳过纹理
int /*thiscall*/ sub_69C6C0(int this, int nArg2, int nArg3)
{
  int v5; // eax

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  if ( nArg2 != 0 )
  {
    v5 = sub_418DD0(nArg3);
    *(uint32_t *)(this + 104) = v5;
    *(uint32_t *)(this + 28) = *(uint32_t *)(v5 + 36);
    *(uint32_t *)(this + 32) = *(uint32_t *)(v5 + 40);
  }
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x69C710 sub_69C710
// ------------------------------------------------------------
// 【L1】图片框 dtor：+104=0，+4=0，+8=3
int /*thiscall*/ sub_69C710(int this)
{
  *(uint32_t *)(this + 104) = 0;
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 3;
  return 1;
}



// ------------------------------------------------------------
// 0x69C730 sub_69C730
// ------------------------------------------------------------
// 【L1】图片框 SetTexture 变体：a2!=0 && a3!=-1 时解析句柄（同 69C6C0）
int /*thiscall*/ sub_69C730(int this, int nArg2, int nArg3)
{
  int v5; // eax

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( nArg2 != 0 && nArg3 != -1 )
  {
    v5 = sub_418DD0(nArg3);
    *(uint32_t *)(this + 104) = v5;
    *(uint32_t *)(this + 28) = *(uint32_t *)(v5 + 36);
    *(uint32_t *)(this + 32) = *(uint32_t *)(v5 + 40);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x69C780 sub_69C780
// ------------------------------------------------------------
// 【L1】按钮 ctor（类型 1）：+8=1，+104..+124 与 +128/+129 清零
int /*thiscall*/ sub_69C780(int this)
{
  *(uint32_t *)(this + 8) = 1;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint8_t *)(this + 129) = 0;
  *(uint8_t *)(this + 128) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x69C7B0 sub_69C7B0
// ------------------------------------------------------------
// 【L1】按钮 SetTextures：解析 常态(+104)/悬停(+112)/按下(+108)/禁用(+116) 四纹理句柄，
// a7=0 用默认 dword_9D3BD0、a8=0 用 dword_9D3BD4；宽高取常态句柄 +36/+40
int /*thiscall*/ sub_69C7B0(int this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7, int nArg8)
{
  int nArg72; // eax
  int fld_68; // eax

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  *(uint32_t *)(this + 104) = sub_418DD0(nArg3);
  *(uint32_t *)(this + 112) = sub_418DD0(nArg4);
  *(uint32_t *)(this + 108) = sub_418DD0(nArg5);
  if ( nArg6 != -1 )
    *(uint32_t *)(this + 116) = sub_418DD0(nArg6);
  nArg72 = nArg7;
  if ( nArg7 == 0 )
    nArg72 = dword_9D3BD0;
  *(uint32_t *)(this + 120) = nArg72;
  if ( nArg8 != 0 )
    *(uint32_t *)(this + 124) = nArg8;
  else
    *(uint32_t *)(this + 124) = dword_9D3BD4;
  fld_68 = *(uint32_t *)(this + 104);
  *(uint32_t *)(this + 28) = *(uint32_t *)(fld_68 + 36);
  *(uint32_t *)(this + 32) = *(uint32_t *)(fld_68 + 40);
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x69C850 sub_69C850
// ------------------------------------------------------------
// 【L1】按钮 dtor：与 69C780 对应的全字段复位
int /*thiscall*/ sub_69C850(int this)
{
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint8_t *)(this + 129) = 0;
  *(uint8_t *)(this + 128) = 0;
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x69C880 sub_69C880
// ------------------------------------------------------------
// 【L1】按钮 Render：三态绘制 —— 激活(69A4D0 命中)→悬停图(+108)，
// 焦点态(+129 未画过)补 sub_414530；非命中→常态图(+104)；
// 禁用分支画 +116；+128/+129 一次性触发位
char /*thiscall*/ sub_69C880(int this)
{
  char result; // al
  int fld_6C; // ecx
  int fld_74; // ecx

  result = *(uint8_t *)(this + 16);
  if ( result != 0 )
  {
    result = *(uint8_t *)(this + 17);
    if ( result != 0 )
    {
      result = sub_69A4D0(this);
      if ( result != 0 )
      {
        fld_6C = *(uint32_t *)(this + 108);
        if ( fld_6C != 0 )
          result = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_6C + 152))(
                     fld_6C,
                     *(uint32_t *)(this + 20),
                     *(uint32_t *)(this + 24),
                     dword_9D3BC8);
        if ( *(uint32_t *)(this + 120) != 0 )
        {
          result = *(uint8_t *)(this + 129);
          if ( result == 0 )
          {
            result = sub_414530();
            *(uint8_t *)(this + 129) = 1;
          }
        }
      }
      else if ( *(uint8_t *)(this + 17) != 0 && dword_79BE3C == *(uint32_t *)(this + 12) )
      {
        result = sub_40FC80(*(uint32_t *)(this + 20), *(uint32_t *)(this + 24), *(uint32_t *)(this + 112));
        if ( *(uint32_t *)(this + 124) != 0 )
        {
          result = *(uint8_t *)(this + 128);
          if ( result == 0 )
          {
            result = sub_414530();
            *(uint8_t *)(this + 128) = 1;
          }
        }
      }
      else
      {
        result = sub_40FC80(*(uint32_t *)(this + 20), *(uint32_t *)(this + 24), *(uint32_t *)(this + 104));
        *(uint8_t *)(this + 129) = 0;
        *(uint8_t *)(this + 128) = 0;
      }
    }
    else
    {
      fld_74 = *(uint32_t *)(this + 116);
      if ( fld_74 != 0 )
        return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_74 + 152))(
                 fld_74,
                 *(uint32_t *)(this + 20),
                 *(uint32_t *)(this + 24),
                 dword_9D3BC8);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x69C980 sub_69C980
// ------------------------------------------------------------
// 【L1】按钮 SetTextures 变体：四个 -1 哨兵跳过解析（保留旧纹理），a7/a8 直接赋值
int /*thiscall*/ sub_69C980(int this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7, int nArg8)
{
  int v10; // eax

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( nArg3 != -1 )
  {
    v10 = sub_418DD0(nArg3);
    *(uint32_t *)(this + 104) = v10;
    *(uint32_t *)(this + 28) = *(uint32_t *)(v10 + 36);
    *(uint32_t *)(this + 32) = *(uint32_t *)(v10 + 40);
  }
  if ( nArg4 != -1 )
    *(uint32_t *)(this + 112) = sub_418DD0(nArg4);
  if ( nArg5 != -1 )
    *(uint32_t *)(this + 108) = sub_418DD0(nArg5);
  if ( nArg6 != -1 )
    *(uint32_t *)(this + 116) = sub_418DD0(nArg6);
  if ( nArg7 != 0 )
    *(uint32_t *)(this + 120) = nArg7;
  if ( nArg8 != 0 )
    *(uint32_t *)(this + 124) = nArg8;
  return 1;
}



// ------------------------------------------------------------
// 0x69CA20 sub_69CA20
// ------------------------------------------------------------
// 【L1】滑条 ctor（类型 5）：+8=5，+120 double=0.0（滑块比例），+132=1
int /*thiscall*/ sub_69CA20(int this)
{
  *(double *)(this + 120) = 0.0;
  *(uint32_t *)(this + 8) = 5;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint8_t *)(this + 132) = 1;
  return 0;
}



// ------------------------------------------------------------
// 0x69CA50 sub_69CA50
// ------------------------------------------------------------
// 【L1】滑条 SetTexture：a3!=-1 解析滑块纹理(+104)，a4!=-1 解析轨道(+108)
int /*thiscall*/ sub_69CA50(int this, int nArg2, int nArg3, int nArg4)
{
  int v6; // eax

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  if ( nArg2 != 0 )
  {
    if ( nArg3 != -1 )
    {
      v6 = sub_418DD0(nArg3);
      *(uint32_t *)(this + 104) = v6;
      *(uint32_t *)(this + 28) = *(uint32_t *)(v6 + 36);
      *(uint32_t *)(this + 32) = *(uint32_t *)(v6 + 40);
    }
    if ( nArg4 != -1 )
      *(uint32_t *)(this + 108) = sub_418DD0(nArg4);
  }
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x69CAB0 sub_69CAB0
// ------------------------------------------------------------
// 【L1】滑条 dtor：与 69CA20 对应复位
int /*thiscall*/ sub_69CAB0(int this)
{
  *(uint32_t *)(this + 104) = 0;
  *(double *)(this + 120) = 0.0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 5;
  *(uint8_t *)(this + 132) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x69CAF0 sub_69CAF0
// ------------------------------------------------------------
// 【L1】滑条 SetScrollPos：clamp [0, +29 最大值] 后写 +28
int /*thiscall*/ sub_69CAF0(int *this, int nArg2)
{
  int result; // eax

  result = *(this + 29);
  if ( nArg2 <= result )
    result = nArg2 < 0 ? 0 : nArg2;
  *(this + 28) = result;
  return result;
}



// ------------------------------------------------------------
// 0x69CB10 sub_69CB10
// ------------------------------------------------------------
// 【L1】滑条 SetTextures 变体：解析 +26 滑块/+27 轨道，宽高 +7/+8 槽，
// 尾调虚槽+40 刷新(+29)
int /*thiscall*/ sub_69CB10(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  int v6; // eax

  if ( *(this + 4) == 0 )
    return -2147483647;
  if ( nArg2 != 0 )
  {
    if ( nArg3 != -1 )
    {
      v6 = sub_418DD0(nArg3);
      *((uint32_t *)this + 26) = v6;
      *((uint32_t *)this + 7) = *(uint32_t *)(v6 + 36);
      *((uint32_t *)this + 8) = *(uint32_t *)(v6 + 40);
    }
    if ( nArg4 != -1 )
      *((uint32_t *)this + 27) = sub_418DD0(nArg4);
  }
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 40))(this, *((uint32_t *)this + 29));
  *(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x69CB80 sub_69CB80
// ------------------------------------------------------------
// 【L1】滑条 SetRange：a2 上限；+116=a2，比例 +120 = (+32 值域)/a2 - 滑块(+40)/a2
// （double 几何换算，轨道像素映射）
int /*thiscall*/ sub_69CB80(int this, unsigned int uArg2)
{
  int result; // eax
  unsigned int fld_74; // ecx

  if ( *(uint32_t *)(this + 112) > uArg2 )
    sub_69CAF0((int *)this, uArg2);
  *(uint32_t *)(this + 116) = uArg2;
  result = *(uint32_t *)(this + 108);
  if ( result != 0 )
  {
    fld_74 = *(uint32_t *)(this + 116);
    if ( fld_74 != 0 )
      *(double *)(this + 120) = (double)*(unsigned int *)(this + 32) / (double)fld_74
                              - (double)*(unsigned int *)(result + 40) / (double)fld_74;
    else
      *(double *)(this + 120) = (double)*(unsigned int *)(this + 32) - (double)*(unsigned int *)(result + 40);
  }
  return result;
}



// ------------------------------------------------------------
// 0x69CC30 sub_69CC30
// ------------------------------------------------------------
// 【L1】滑条 Update：虚槽+28 基类更新 → 可见(+17) && +132 时虚槽+36 绘制
char /*thiscall*/ sub_69CC30(uint8_t *this)
{
  char result; // al

  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 28))(this);
  result = *(this + 17);
  if ( result != 0 )
  {
    result = *(this + 132);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 36))(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x69CC60 sub_69CC60
// ------------------------------------------------------------
// 【L1】滑条 Render：滑块图(+104) 于 +20/+24；轨道图(+108) 于
// +24 + (+112 范围 × +120 比例 + 0.5 取整)（vt+152）
char /*thiscall*/ sub_69CC60(int this)
{
  int fld_74; // eax
  int fld_68; // ecx
  int fld_6C; // edi

  LOBYTE(fld_74) = *(uint8_t *)(this + 16);
  if ( (uint8_t)fld_74 != 0 )
  {
    fld_68 = *(uint32_t *)(this + 104);
    if ( fld_68 != 0 )
      LOBYTE(fld_74) = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_68 + 152))(
                     fld_68,
                     *(uint32_t *)(this + 20),
                     *(uint32_t *)(this + 24),
                     dword_9D3BC8);
    fld_6C = *(uint32_t *)(this + 108);
    if ( fld_6C != 0 )
    {
      fld_74 = *(uint32_t *)(this + 116);
      if ( fld_74 != 0 )
        LOBYTE(fld_74) = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_6C + 152))(
                       fld_6C,
                       *(uint32_t *)(this + 20),
                       (uint64_t)((double)*(unsigned int *)(this + 112) * *(double *)(this + 120)
                                        + (double)*(int *)(this + 24)
                                        + 0.5),
                       dword_9D3BC8);
    }
  }
  return fld_74;
}



// ------------------------------------------------------------
// 0x69CCE0 sub_69CCE0
// ------------------------------------------------------------
// 【L1】滑条 ThumbDrag：dword_79BE40 命中/拖动判定，
// pt.y 反算比例 → sub_69CAF0(pos)（(pt.y - 轨道中心 - +24)/+120）
char /*thiscall*/ sub_69CCE0(int this)
{
  int fld_6C; // eax

  LOBYTE(fld_6C) = *(uint8_t *)(this + 16);
  if ( (uint8_t)fld_6C != 0 )
  {
    LOBYTE(fld_6C) = *(uint8_t *)(this + 17);
    if ( (uint8_t)fld_6C != 0 )
    {
      fld_6C = *(uint32_t *)(this + 108);
      if ( fld_6C != 0 )
      {
        LOBYTE(fld_6C) = dword_79BE40;
        if ( dword_79BE40 == *(uint32_t *)(this + 12) || dword_79BE40 == -1 )
        {
          LOBYTE(fld_6C) = sub_69A4D0(this);
          if ( (uint8_t)fld_6C != 0 )
          {
            fld_6C = *(uint32_t *)(this + 12);
            dword_79BE40 = fld_6C;
          }
          if ( dword_89D26C == 1 && dword_79BE40 == *(uint32_t *)(this + 12) )
            LOBYTE(fld_6C) = sub_69CAF0(
                           (int *)this,
                           (uint64_t)((double)(pt.y
                                                     - *(uint32_t *)(*(uint32_t *)(this + 108) + 40) / 2
                                                     - *(uint32_t *)(this + 24))
                                            / *(double *)(this + 120)));
        }
      }
    }
  }
  return fld_6C;
}



// ------------------------------------------------------------
// 0x69CD70 sub_69CD70
// ------------------------------------------------------------
// 【L1】组合控件 Create：+104=a2 主图/+108=a3 副图/+112=a4 组对象，
// 高度 = 主+32 + a4[8] + 副+32；sub_69A5F0 定位两个子项，
// sub_69A840 依次 push 主/副/组三项
int /*thiscall*/ sub_69CD70(int this, int pArg2, int pArg3, uint32_t *pArg4)
{
  int fld_68; // [esp-8h] [ebp-Ch]

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  *(uint32_t *)(this + 108) = pArg3;
  *(uint32_t *)(this + 104) = pArg2;
  *(uint32_t *)(this + 112) = pArg4;
  *(uint32_t *)(this + 28) = *(uint32_t *)(pArg2 + 28);
  *(uint32_t *)(this + 32) = *(uint32_t *)(pArg2 + 32) + pArg4[8] + *(uint32_t *)(pArg3 + 32);
  sub_69A5F0(pArg4, *(uint32_t *)(this + 20), *(uint32_t *)(pArg2 + 32) + *(uint32_t *)(this + 24));
  sub_69A5F0(
    *(uint32_t **)(this + 108),
    *(uint32_t *)(this + 20),
    *(uint32_t *)(this + 24) + *(uint32_t *)(*(uint32_t *)(this + 104) + 32) + *(uint32_t *)(*(uint32_t *)(this + 112) + 32));
  fld_68 = *(uint32_t *)(this + 104);
  *(uint8_t *)(this + 4) = 1;
  sub_69A840((uint32_t *)this, fld_68);
  sub_69A840((uint32_t *)this, *(uint32_t *)(this + 108));
  sub_69A840((uint32_t *)this, *(uint32_t *)(this + 112));
  return 1;
}



// ------------------------------------------------------------
// 0x69CE10 sub_69CE10
// ------------------------------------------------------------
// 【L1】标签页 ctor（类型 7）：+8=7，+104=-1（无选中），+108=0
void /*thiscall*/ sub_69CE10(int this)
{
  *(uint32_t *)(this + 8) = 7;
  *(uint32_t *)(this + 104) = -1;
  *(uint8_t *)(this + 108) = 0;
}



// ------------------------------------------------------------
// 0x69CE30 sub_69CE30
// ------------------------------------------------------------
// 【L1】标签页 dtor：与 69CE10 对应复位
int /*thiscall*/ sub_69CE30(int this)
{
  *(uint8_t *)(this + 108) = 0;
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 7;
  *(uint32_t *)(this + 104) = -1;
  return 1;
}



// ------------------------------------------------------------
// 0x69CE50 sub_69CE50
// ------------------------------------------------------------
// 【L1】标签页 SelectTab(a2)：遍历子链(+96)给每项 +132 写选中布尔（==a2 判定），
// +104=a2，+108=1
char /*thiscall*/ sub_69CE50(int this, uint32_t *uArg2)
{
  uint32_t *fld_64; // eax
  uint32_t *fld_60; // edx
  uint32_t *v4; // esi
  int v5; // edx

  LOBYTE(fld_64) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_64 != 0 )
  {
    fld_64 = *(uint32_t **)(this + 100);
    if ( fld_64 != nullptr )
    {
      fld_64 = *(uint32_t **)(this + 104);
      if ( fld_64 != uArg2 )
      {
        fld_60 = *(uint32_t **)(this + 96);
        fld_64 = (uint32_t *)*fld_60;
        v4 = nullptr;
        if ( (uint32_t *)*fld_60 != fld_60 )
        {
          do
          {
            v5 = fld_64[2];
            *(uint8_t *)(v5 + 132) = uArg2 == v4;
            fld_64 = (uint32_t *)*fld_64;
            v4 = (uint32_t *)((char *)v4 + 1);
          }
          while ( fld_64 != *(uint32_t **)(this + 96) );
        }
        *(uint32_t *)(this + 104) = uArg2;
        *(uint8_t *)(this + 108) = 1;
      }
    }
  }
  return (char)fld_64;
}



// ------------------------------------------------------------
// 0x69CEB0 sub_69CEB0
// ------------------------------------------------------------
// 【L1】标签页 DeselectAll：子链全部 +132=0，+104=-1
char /*thiscall*/ sub_69CEB0(int this)
{
  uint32_t *fld_64; // eax
  uint32_t *fld_60; // edx

  LOBYTE(fld_64) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_64 != 0 )
  {
    fld_64 = *(uint32_t **)(this + 100);
    if ( fld_64 != nullptr )
    {
      fld_60 = *(uint32_t **)(this + 96);
      fld_64 = (uint32_t *)*fld_60;
      if ( (uint32_t *)*fld_60 != fld_60 )
      {
        do
        {
          *(uint8_t *)(fld_64[2] + 132) = 0;
          fld_64 = (uint32_t *)*fld_64;
        }
        while ( fld_64 != *(uint32_t **)(this + 96) );
      }
      *(uint32_t *)(this + 104) = -1;
    }
  }
  return (char)fld_64;
}



// ------------------------------------------------------------
// 0x69CEF0 sub_69CEF0
// ------------------------------------------------------------
// 【L1】标签页::dword_79BE58 联动：全局选择 id 命中本页时清 dword_79BE58，
// 按 dword_79BE64 查找对应子项并 SelectTab
char /*thiscall*/ sub_69CEF0(int this)
{
  uint32_t *v1; // eax
  int fld_C; // edx
  uint32_t *fld_60; // edx
  uint32_t *v4; // esi

  LOBYTE(v1) = *(uint8_t *)(this + 17);
  if ( (uint8_t)v1 != 0 )
  {
    fld_C = *(uint32_t *)(this + 12);
    *(uint8_t *)(this + 108) = 0;
    LOBYTE(v1) = dword_79BE58;
    if ( dword_79BE58 == fld_C )
    {
      dword_79BE58 = -1;
      fld_60 = *(uint32_t **)(this + 96);
      v1 = (uint32_t *)*fld_60;
      v4 = nullptr;
      if ( (uint32_t *)*fld_60 != fld_60 )
      {
        while ( *(uint32_t *)(v1[2] + 12) != dword_79BE64 )
        {
          v1 = (uint32_t *)*v1;
          v4 = (uint32_t *)((char *)v4 + 1);
          if ( v1 == *(uint32_t **)(this + 96) )
            return (char)v1;
        }
        LOBYTE(v1) = sub_69CE50(this, v4);
      }
    }
  }
  return (char)v1;
}



// ------------------------------------------------------------
// 0x69CF50 sub_69CF50
// ------------------------------------------------------------
// 【L1】标签页 Select 包装：+4=1 后 sub_69CE50(a2)
int /*thiscall*/ sub_69CF50(uint8_t *this, uint32_t *uArg2)
{
  if ( *(this + 4) != 0 )
    return -2147483646;
  *(this + 4) = 1;
  sub_69CE50((int)this, uArg2);
  return 1;
}



// ------------------------------------------------------------
// 0x69CF80 sub_69CF80
// ------------------------------------------------------------
// 【L1】图片组 ctor（类型 6）：+8=6，+104..+132 全清
int /*thiscall*/ sub_69CF80(int this)
{
  *(uint32_t *)(this + 8) = 6;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint8_t *)(this + 129) = 0;
  *(uint8_t *)(this + 128) = 0;
  *(uint8_t *)(this + 132) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x69CFC0 sub_69CFC0
// ------------------------------------------------------------
// 【L1】图片组 dtor：与 69CF80 对应复位
int /*thiscall*/ sub_69CFC0(int this)
{
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint8_t *)(this + 129) = 0;
  *(uint8_t *)(this + 128) = 0;
  *(uint8_t *)(this + 132) = 0;
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 6;
  return 1;
}



// ------------------------------------------------------------
// 0x69D000 sub_69D000
// ------------------------------------------------------------
// 【L1】图片组::切换态翻转：dword_79BE64==-1 && dword_79BE34==id 时 +132 取反；
// 尾调 Concurrency::SpinYield（CRT 符号混入的基类虚槽调用，按原样保留）
void /*thiscall*/ sub_69D000(int this)
{
  if ( *(uint8_t *)(this + 17) != 0 && dword_79BE64 == -1 && dword_79BE34 == *(uint32_t *)(this + 12) )
    *(uint8_t *)(this + 132) = *(uint8_t *)(this + 132) == 0;
  Concurrency::details::ExternalContextBase::SpinYield((Concurrency::details::ExternalContextBase *)this);
}



// ------------------------------------------------------------
// 0x69D02B ?SpinYield@ExternalContextBase@details@Concurrency@@UAEXXZ
// ------------------------------------------------------------
// 【L1】Concurrency::details::ExternalContextBase::SpinYield（虚槽+28 转发；CRT 符号混入）
void /*thiscall*/ Concurrency::details::ExternalContextBase::SpinYield(Concurrency::details::ExternalContextBase *this)
{
  (*(void (/*thiscall*/ **)(Concurrency::details::ExternalContextBase *))(*(uint32_t *)this + 28))(this);
}



// ------------------------------------------------------------
// 0x69D030 sub_69D030
// ------------------------------------------------------------
// 【L1】标签(类型 2) Render：可见(+16)时 —— 激活(+132 翻转态)画 +108；
// 悬停(69A4D0)画 +112 且 +120 一次性触发 sub_414530(+129 位)；
// 常态画 +104；不可见交互时画 +116
char /*thiscall*/ sub_69D030(int this)
{
  char result; // al
  int fld_74; // ecx

  result = *(uint8_t *)(this + 16);
  if ( result != 0 )
  {
    result = *(uint8_t *)(this + 17);
    if ( result == 0 )
    {
      fld_74 = *(uint32_t *)(this + 116);
      if ( fld_74 == 0 )
        return result;
      return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_74 + 152))(
               fld_74,
               *(uint32_t *)(this + 20),
               *(uint32_t *)(this + 24),
               dword_9D3BC8);
    }
    result = *(uint8_t *)(this + 132);
    if ( result != 0 )
    {
      fld_74 = *(uint32_t *)(this + 108);
      if ( fld_74 == 0 )
        return result;
      return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_74 + 152))(
               fld_74,
               *(uint32_t *)(this + 20),
               *(uint32_t *)(this + 24),
               dword_9D3BC8);
    }
    if ( sub_69A4D0(this) != 0 )
    {
      result = sub_40FC80(*(uint32_t *)(this + 20), *(uint32_t *)(this + 24), *(uint32_t *)(this + 108));
      if ( *(uint32_t *)(this + 120) != 0 )
      {
        result = *(uint8_t *)(this + 129);
        if ( result == 0 )
        {
          result = sub_414530();
          *(uint8_t *)(this + 129) = 1;
        }
      }
    }
    else if ( *(uint8_t *)(this + 17) != 0 && dword_79BE3C == *(uint32_t *)(this + 12) )
    {
      result = sub_40FC80(*(uint32_t *)(this + 20), *(uint32_t *)(this + 24), *(uint32_t *)(this + 112));
      if ( *(uint32_t *)(this + 124) != 0 )
      {
        result = *(uint8_t *)(this + 128);
        if ( result == 0 )
        {
          result = sub_414530();
          *(uint8_t *)(this + 128) = 1;
        }
      }
    }
    else
    {
      result = sub_40FC80(*(uint32_t *)(this + 20), *(uint32_t *)(this + 24), *(uint32_t *)(this + 104));
      *(uint8_t *)(this + 129) = 0;
      *(uint8_t *)(this + 128) = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x69D150 sub_69D150
// ------------------------------------------------------------
// 【L1】文本列表 Create：+8=a2 类型/+40 行缓冲尺寸 a3(new a3+1)/+44 行对象尺寸 a4
// （new a4）；行指针数组 memset 清零；失败→0x80000008
int /*thiscall*/ sub_69D150(int this, int nArg2, int pArg3, int nArg4)
{
  void *pMem; // eax
  void *pMem2; // eax

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  *(uint32_t *)(this + 8) = nArg2;
  *(uint32_t *)(this + 40) = pArg3;
  *(uint32_t *)(this + 44) = nArg4;
  pMem = operator new(pArg3 + 1);
  *(uint32_t *)(this + 52) = pMem;
  if ( pMem == nullptr )
    return -2147483640;
  pMem2 = operator new(*(uint32_t *)(this + 44));
  *(uint32_t *)(this + 48) = pMem2;
  if ( pMem2 == nullptr )
  {
    if ( *(uint32_t *)(this + 52) != 0 )
      j_j__free(*(void **)(this + 52));
    *(uint32_t *)(this + 52) = 0;
    return -2147483640;
  }
  memset(*(void **)(this + 52), 0, *(uint32_t *)(this + 40) + 1);
  memset(*(void **)(this + 48), 0, *(uint32_t *)(this + 44) / 5u + 4);
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x69D210 sub_69D210
// ------------------------------------------------------------
// 【L1】文本列表 Draw（GDI 路径）：+68 起始行遍历到 +68+72，
// 每行按 +92 对齐模式(1 居中/2 右对齐)算 x 偏移；
// 有字体(+56)走渲染器 sub_416430；否则 GDI TextOutA 8 方向描边
// （+88 阴影色/+84 高光色/+0 主色，+8/+9/+10 描边开关位）
int /*thiscall*/ sub_69D210(int this, HDC hdc)
{
  int pThis; // eax
  unsigned int fld_44; // edx
  unsigned int fld_442; // ebx
  int v7; // esi
  int v8; // esi
  int v9; // ebx
  unsigned int fld_2C; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int pThis2; // esi
  unsigned int fld_443; // [esp+0h] [ebp-Ch]
  const CHAR *lpString; // [esp+4h] [ebp-8h]
  HDC hdca; // [esp+14h] [ebp+8h]

  pThis = this;
  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  fld_44 = *(uint32_t *)(this + 68);
  fld_442 = fld_44;
  fld_443 = fld_44;
  if ( fld_44 < fld_44 + *(uint32_t *)(this + 72) )
  {
    while ( 1 )
    {
      v7 = *(uint32_t *)(pThis + 16);
      if ( v7 == 0 || fld_442 >= (*(uint32_t *)(pThis + 20) - v7) >> 2 )
        return 1;
      v8 = *(uint32_t *)(v7 + 4 * fld_442);
      v9 = *(uint32_t *)(pThis + 36) + (*(uint32_t *)(pThis + 64) + 12) * (fld_442 - fld_44);
      fld_2C = 0;
      if ( *(uint32_t *)(pThis + 92) == 1 )
      {
        fld_2C = (unsigned int)(*(uint32_t *)(this + 44)
                           - (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pThis + 56) + 16))(
                               *(uint32_t *)(pThis + 56),
                               *(uint32_t *)(v8 + 24))) >> 1;
      }
      else
      {
        if ( *(uint32_t *)(pThis + 92) != 2 )
          goto LABEL_13;
        fld_2C = *(uint32_t *)(this + 44)
            - (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pThis + 56) + 16))(
                *(uint32_t *)(pThis + 56),
                *(uint32_t *)(v8 + 24));
      }
      pThis = this;
LABEL_13:
      v11 = fld_2C + *(uint32_t *)(pThis + 32);
      v12 = *(uint32_t *)(v8 + 12);
      hdca = (HDC)v11;
      if ( v12 != 0 )
      {
        hdca = (HDC)(v12 + v11 + 4 * v12);
        v11 = (int)hdca;
      }
      if ( *(uint32_t *)(pThis + 56) != 0 )
      {
        unknown_libname_3(*(void **)(pThis + 56));
        if ( *(uint8_t *)(v8 + 8) != 0 )
        {
          v13 = *(uint32_t *)(v8 + 24);
          v14 = *(uint32_t *)v8;
          pThis2 = this;
          sub_416430(*(void **)(this + 56), *(uint32_t *)(this + 8), (int)hdca - 1, v9, v14, v13);
          goto LABEL_27;
        }
      }
      else
      {
        if ( *(uint8_t *)(v8 + 10) != 0 )
        {
          lpString = *(const CHAR **)(v8 + 24);
          SetTextColor(hdc, *(uint32_t *)(pThis + 88) & 0xFFFFFF);
          TextOutA(hdc, (int)hdca - 1, v9, lpString, *(uint32_t *)(v8 + 4));
          TextOutA(hdc, (int)hdca + 1, v9, lpString, *(uint32_t *)(v8 + 4));
          TextOutA(hdc, (int)hdca, v9 - 1, lpString, *(uint32_t *)(v8 + 4));
          TextOutA(hdc, (int)hdca, v9 + 1, lpString, *(uint32_t *)(v8 + 4));
          TextOutA(hdc, (int)hdca - 1, v9 - 1, lpString, *(uint32_t *)(v8 + 4));
          TextOutA(hdc, (int)hdca - 1, v9 + 1, lpString, *(uint32_t *)(v8 + 4));
          TextOutA(hdc, (int)hdca + 1, v9 - 1, lpString, *(uint32_t *)(v8 + 4));
          TextOutA(hdc, (int)hdca + 1, v9 + 1, lpString, *(uint32_t *)(v8 + 4));
          SetTextColor(hdc, *(uint32_t *)v8 & 0xFFFFFF);
          v11 = (int)hdca;
          pThis = this;
        }
        if ( *(uint8_t *)(v8 + 9) != 0 )
        {
          SetTextColor(hdc, *(uint32_t *)(pThis + 84) & 0xFFFFFF);
          TextOutA(hdc, (int)hdca + 1, v9 + 1, *(LPCSTR *)(v8 + 24), *(uint32_t *)(v8 + 4));
          SetTextColor(hdc, *(uint32_t *)v8 & 0xFFFFFF);
          v11 = (int)hdca;
        }
        if ( *(uint32_t *)v8 != 0 )
        {
          SetTextColor(hdc, *(uint32_t *)v8 & 0xFFFFFF);
          v11 = (int)hdca;
        }
        TextOutA(hdc, v11, v9, *(LPCSTR *)(v8 + 24), *(uint32_t *)(v8 + 4));
        if ( *(uint8_t *)(v8 + 8) != 0 )
          TextOutA(hdc, (int)hdca - 1, v9, *(LPCSTR *)(v8 + 24), *(uint32_t *)(v8 + 4));
      }
      pThis2 = this;
LABEL_27:
      fld_44 = *(uint32_t *)(pThis2 + 68);
      if ( ++fld_443 >= fld_44 + *(uint32_t *)(pThis2 + 72) )
        return 1;
      fld_442 = fld_443;
      pThis = this;
    }
  }
  return 1;
}


// ------------------------------------------------------------
// 0x69D4E0 sub_69D4E0
// ------------------------------------------------------------
// 【L1】文本列表 ClearAll：逐行 free(行对象+24 文本/+6 槽) + free 数组 + 字段复位
int /*thiscall*/ sub_69D4E0(int this)
{
  *(uint32_t *)(this + 8) = 0;
  if ( *(uint32_t *)(this + 16) != 0 )
    j__free(*(void **)(this + 16));
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint8_t *)(this + 28) = 1;
  *(uint32_t *)(this + 72) = -1;
  *(uint32_t *)(this + 80) = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x69D550 sub_69D550
// ------------------------------------------------------------
// 【L1】文本列表 Destroy：先 ClearAll 语义再释放 +48/+52 缓冲与全部字段（+4=0）
int /*thiscall*/ sub_69D550(int this)
{
  void ***i; // edi
  void **v3; // eax
  void *fld_34; // eax
  void **v6; // [esp+Ch] [ebp-4h]

  for ( i = *(void ****)(this + 16); i != *(void ****)(this + 20); ++i )
  {
    v3 = *i;
    v6 = *i;
    if ( *i != nullptr )
    {
      if ( v3[6] != nullptr )
      {
        j_j__free(v3[6]);
        v3 = v6;
      }
      v3[6] = nullptr;
      j__free(v3);
    }
    *i = nullptr;
  }
  if ( *(uint32_t *)(this + 16) != 0 )
    j__free(*(void **)(this + 16));
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  if ( *(uint32_t *)(this + 48) != 0 )
    j_j__free(*(void **)(this + 48));
  fld_34 = *(void **)(this + 52);
  *(uint32_t *)(this + 48) = 0;
  if ( fld_34 != nullptr )
    j_j__free(fld_34);
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 8) = 0;
  if ( *(uint32_t *)(this + 16) != 0 )
    j__free(*(void **)(this + 16));
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = -1;
  *(uint32_t *)(this + 80) = -1;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint8_t *)(this + 4) = 0;
  *(uint8_t *)(this + 28) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x69D640 sub_69D640
// ------------------------------------------------------------
// 【L1】文本列表 ClearItems：行数组区间 free + 数组指针/容量清零（保留配置字段）
int /*thiscall*/ sub_69D640(int this)
{
  void ***i; // esi
  void **v4; // edi

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  for ( i = *(void ****)(this + 16); i != *(void ****)(this + 20); ++i )
  {
    v4 = *i;
    if ( *i != nullptr )
    {
      if ( v4[6] != nullptr )
        j_j__free(v4[6]);
      v4[6] = nullptr;
      j__free(v4);
    }
    *i = nullptr;
  }
  if ( *(uint32_t *)(this + 16) != 0 )
    j__free(*(void **)(this + 16));
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x69D6C0 sub_69D6C0
// ------------------------------------------------------------
// 【L1】文本列表 DeleteItems(n)：-1 全清(69D640)；否则删前 n 行并 memmove 压缩数组
int /*thiscall*/ sub_69D6C0(int this, unsigned int uArg2)
{
  unsigned int uArg22; // edx
  unsigned int v5; // edi
  int fld_10; // ecx
  uint32_t *fld_102; // ebx
  uint32_t *fld_103; // eax
  char *fld_104; // edi
  char *v10; // ecx
  size_t fld_14; // ebx

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  uArg22 = uArg2;
  if ( uArg2 == -1 )
    return sub_69D640(this);
  v5 = 0;
  if ( uArg2 != 0 )
  {
    do
    {
      fld_10 = *(uint32_t *)(*(uint32_t *)(this + 16) + 4 * v5);
      if ( fld_10 != 0 )
      {
        fld_102 = *(uint32_t **)(*(uint32_t *)(this + 16) + 4 * v5);
        if ( *(uint32_t *)(fld_10 + 24) != 0 )
          j_j__free(*(void **)(fld_10 + 24));
        fld_102[6] = 0;
        j__free(fld_102);
        uArg22 = uArg2;
      }
      fld_103 = (uint32_t *)(4 * v5++ + *(uint32_t *)(this + 16));
      *fld_103 = 0;
    }
    while ( v5 < uArg22 );
  }
  fld_104 = *(char **)(this + 16);
  v10 = &fld_104[4 * uArg22];
  if ( fld_104 != v10 )
  {
    fld_14 = 4 * ((*(uint32_t *)(this + 20) - (int)v10) >> 2);
    *(uint32_t *)(this + 20) = (char *)memcpy_0(fld_104, &fld_104[4 * uArg22], fld_14) + fld_14;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x69D780 sub_69D780
// ------------------------------------------------------------
// 【L1】文本列表 Flush：+28 就绪时 渲染器 vt+72 Begin → vt+96 取 HDC →
// sub_69D210 逐行画 → vt+76 End
int /*thiscall*/ sub_69D780(int this)
{
  HDC fld_8; // eax

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( *(uint8_t *)(this + 28) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8) + 72))(*(uint32_t *)(this + 8), 0);
    fld_8 = (HDC)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8) + 96))(*(uint32_t *)(this + 8));
    sub_69D210(this, fld_8);
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8) + 76))(*(uint32_t *)(this + 8));
  }
  return 1;
}



// ------------------------------------------------------------
// 0x69D7D0 sub_69D7D0
// ------------------------------------------------------------
// 【L1】std::vector<T*>::insert 中段（扩容/搬移三路分支，0x3FFFFFFF 哨兵）
unsigned int /*thiscall*/ sub_69D7D0(int this, int Src, unsigned int uArg3, int *pDwArg4)
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

  fld_4 = *(uint32_t *)(this + 4);
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_50F040(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(uint8_t **)(this + 8);
      v21 = (int)&fld_83[-Src] >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);
        fld_84 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = fld_84;
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( fld_4 != 0 )
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
        else
          fld_86 = 0;
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;
      else
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &pMem[v28];
      *(uint32_t *)(this + 8) = &pMem[4 * v18];
      *(uint32_t *)(this + 4) = pMem;
      return (unsigned int)pMem;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x69D9B0 sub_69D9B0
// ------------------------------------------------------------
// 【L1】std::vector<T*>::push_back：容量足直接尾插，否则转 69D7D0 扩容插入
unsigned int /*thiscall*/ sub_69D9B0(int *this, int *pDwArg2)
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 2;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 2 )
    return sub_69D7D0((int)this, *(this + 2), 1u, pDwArg2);
  fld_e22 = (int *)*(this + 2);
  *fld_e22 = *pDwArg2;
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x69DA00 sub_69DA00
// ------------------------------------------------------------
// 【L1】文本列表 AddLine：new(0x20) 行对象（继承 +80 颜色/+60/61/62 标志/+84/+88，
// +12 行号 a3/+28 a4），strncpy 文本，push_back 入 +12 行 vector
int /*thiscall*/ sub_69DA00(int this, char *Source, int nArg3, int nArg4)
{
  uint8_t *pMem; // eax
  uint8_t *fld_50; // esi
  size_t nLen; // ebx
  char *pMem2; // eax
  uint8_t *fld_502; // [esp+8h] [ebp-4h] BYREF

  pMem = operator new(0x20u);
  if ( pMem != nullptr )
  {
    pMem[10] = 0;
    pMem[9] = 0;
    pMem[8] = 0;
    *((uint32_t *)pMem + 7) = 0;
    *((uint32_t *)pMem + 5) = 0;
    *((uint32_t *)pMem + 4) = 0;
    *((uint32_t *)pMem + 3) = 0;
    *((uint32_t *)pMem + 1) = 0;
    *(uint32_t *)pMem = 0;
    *((uint32_t *)pMem + 6) = 0;
    fld_50 = pMem;
  }
  else
  {
    fld_50 = nullptr;
  }
  fld_502 = fld_50;
  if ( fld_50 == nullptr )
    return -2147483640;
  *(uint32_t *)fld_50 = *(uint32_t *)(this + 80);
  fld_50[8] = *(uint8_t *)(this + 60);
  fld_50[9] = *(uint8_t *)(this + 61);
  fld_50[10] = *(uint8_t *)(this + 62);
  *((uint32_t *)fld_50 + 4) = *(uint32_t *)(this + 84);
  *((uint32_t *)fld_50 + 5) = *(uint32_t *)(this + 88);
  *((uint32_t *)fld_50 + 3) = nArg3;
  *((uint32_t *)fld_50 + 7) = nArg4;
  nLen = strlen(Source);
  *((uint32_t *)fld_50 + 1) = nLen;
  pMem2 = (char *)operator new(*(uint32_t *)(this + 40) + 1);
  *((uint32_t *)fld_50 + 6) = pMem2;
  if ( pMem2 != nullptr )
  {
    strncpy(pMem2, Source, nLen);
    *(uint8_t *)(nLen + *((uint32_t *)fld_50 + 6)) = 0;
    sub_69D9B0((int *)(this + 12), (int *)&fld_502);
    return 1;
  }
  else
  {
    *((uint32_t *)fld_50 + 6) = 0;
    j__free(fld_50);
    return -2147483640;
  }
}



// ------------------------------------------------------------
// 0x69DB10 sub_69DB10
// ------------------------------------------------------------
// 【L1】文本列表 AddExtra：超长(+40)拒绝打日志；按 CR/LF(13/10) 拆行，
// SJIS 双字节不拆，行宽经字体引擎 vt+24 适配截断，逐行 sub_69DA00 入列；返回行数
int /*thiscall*/ sub_69DB10(int this, const char *pArg2, int nArg3)
{
  unsigned int nLen; // eax
  unsigned int v6; // ebx
  char *pMem; // esi
  size_t v8; // ecx
  int fld_34; // edx
  char v10; // al
  int fld_38; // eax
  size_t v12; // ecx
  char *Block; // [esp+4h] [ebp-10h]
  unsigned int nLen2; // [esp+8h] [ebp-Ch]
  int v15; // [esp+Ch] [ebp-8h]
  size_t i; // [esp+10h] [ebp-4h]
  unsigned int v17; // [esp+1Ch] [ebp+8h]

  if ( *(uint8_t *)(this + 4) == 0 )
    return 0;
  nLen = strlen(pArg2);
  nLen2 = nLen;
  if ( nLen <= *(uint32_t *)(this + 40) )
  {
    strcpy(*(char **)(this + 52), pArg2);
    v6 = 0;
    v15 = 0;
    v17 = 0;
    pMem = (char *)operator new(*(uint32_t *)(this + 40) + 1);
    for ( Block = pMem; ; pMem = Block )
    {
      if ( v6 < nLen2 )
      {
        v8 = v6 - v17;
        for ( i = v6 - v17; ; v8 = i )
        {
          fld_34 = *(uint32_t *)(this + 52);
          v10 = *(uint8_t *)(fld_34 + v6);
          if ( v10 < 0
            && (v10 == -127
             || v10 == -126
             || v10 == -125
             || v10 == -124
             || v10 == -121
             || v10 == -120
             || v10 == -119
             || v10 == -118
             || v10 == -117
             || v10 == -116
             || v10 == -115
             || v10 == -114
             || v10 == -113
             || v10 == -112
             || v10 == -111
             || v10 == -110
             || v10 == -109
             || v10 == -108
             || v10 == -107
             || v10 == -106
             || v10 == -105
             || v10 == -104
             || v10 == -103
             || v10 == -102
             || v10 == -101
             || v10 == -100
             || v10 == -99
             || v10 == -98
             || v10 == -97
             || v10 == -32
             || v10 == -31
             || v10 == -30
             || v10 == -29
             || v10 == -28
             || v10 == -27
             || v10 == -26
             || v10 == -25
             || v10 == -24
             || v10 == -23
             || v10 == -22
             || v10 == -19
             || v10 == -18
             || v10 == -6
             || v10 == -5
             || v10 == -4) )
          {
            strncpy(pMem, (const char *)(v17 + fld_34), v8);
            pMem[v6 - v17] = 0;
            fld_38 = (*(int (/*thiscall*/ **)(uint32_t, char *, uint32_t))(**(uint32_t **)(this + 56) + 24))(
                    *(uint32_t *)(this + 56),
                    pMem,
                    *(uint32_t *)(this + 44));
            if ( fld_38 != -1 )
              break;
            v6 += 2;
            i += 2;
            v12 = i;
          }
          else
          {
            if ( v10 == 13 )
            {
              *(uint8_t *)(fld_34 + v6++) = 0;
              ++v8;
            }
            if ( *(uint8_t *)(v6 + *(uint32_t *)(this + 52)) == 10 )
            {
              *(uint8_t *)(v6 + *(uint32_t *)(this + 52)) = 0;
              ++v6;
              goto LABEL_67;
            }
            ++v6;
            v12 = v8 + 1;
            i = v12;
          }
          strncpy(pMem, (const char *)(v17 + *(uint32_t *)(this + 52)), v12);
          pMem[v6 - v17] = 0;
          fld_38 = (*(int (/*thiscall*/ **)(uint32_t, char *, uint32_t))(**(uint32_t **)(this + 56) + 24))(
                  *(uint32_t *)(this + 56),
                  pMem,
                  *(uint32_t *)(this + 44));
          if ( fld_38 != -1 )
            break;
          if ( v6 >= nLen2 )
            goto LABEL_67;
        }
        pMem[fld_38 - 1] = 0;
      }
LABEL_67:
      strncpy(*(char **)(this + 48), (const char *)(v17 + *(uint32_t *)(this + 52)), v6 - v17);
      *(uint8_t *)(v6 - v17 + *(uint32_t *)(this + 48)) = 0;
      v17 = v6;
      if ( v15 != 0 )
        sub_69DA00(this, *(char **)(this + 48), *(uint32_t *)(this + 76), nArg3);
      else
        sub_69DA00(this, *(char **)(this + 48), 0, nArg3);
      ++v15;
      if ( v6 >= nLen2 )
        break;
    }
    j_j__free(Block);
    return v15;
  }
  else
  {
    sub_40BE20("\nAddExtra() <len : %d>, <buffsize : %d>", nLen);
    return 0;
  }
}

// ------------------------------------------------------------
// 0x69DDB0 sub_69DDB0
// ------------------------------------------------------------
// 【L1】文本列表 AddLinef：vsprintf 到 +52 缓冲 → sub_69DB10 格式化追加行
int sub_69DDB0(int pArg1, char *Format, ...)
{
  va_list va; // [esp+14h] [ebp+10h] BYREF

  va_start(va, Format);
  if ( *(uint8_t *)(pArg1 + 4) == 0 )
    return 0;
  vsprintf(*(char *const *)(pArg1 + 52), Format, va);
  return sub_69DB10(pArg1, *(const char **)(pArg1 + 52), 0);
}



// ------------------------------------------------------------
// 0x69DDF0 sub_69DDF0
// ------------------------------------------------------------
// 【L1】标签(类型 2) ctor：+8=2，子槽(+26)=0
void /*thiscall*/ sub_69DDF0(uint32_t *this)
{
  *(this + 2) = 2;
  *(this + 26) = 0;
}



// ------------------------------------------------------------
// 0x69DE00 sub_69DE00
// ------------------------------------------------------------
// 【L1】标签 dtor：+104=0，+4=0，+8=2
int /*thiscall*/ sub_69DE00(int this)
{
  *(uint32_t *)(this + 104) = 0;
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 2;
  return 1;
}



// ------------------------------------------------------------
// 0x69DE30 sub_69DE30
// ------------------------------------------------------------
// 【L1】标签 Render：可见(+16)且 +104 图非空时 vt+152 绘制于 +20/+24
int /*thiscall*/ sub_69DE30(int this)
{
  int result; // eax
  int fld_68; // ecx

  result = this;
  if ( *(uint8_t *)(this + 16) != 0 )
  {
    fld_68 = *(uint32_t *)(this + 104);
    if ( fld_68 != 0 )
      return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_68 + 152))(
               fld_68,
               *(uint32_t *)(result + 20),
               *(uint32_t *)(result + 24),
               dword_9D3BC8);
  }
  return result;
}




// ============================================================
// SECTION 8  CWSBuffer 方法体（ISocket 底层环形缓冲）+ ijl15 JPEG 编码
//            （0x69DE60-0x69E010）
// ------------------------------------------------------------
// 物理位置在文件尾、逻辑归属 SECTION 4 的 ISocket 收发缓冲类
// （vtable off_749D94，由 0x6985F0 构造）。布局: +4 就绪 / +8 基址
// / +12 容量 / +16 读 / +20 写。0x69E010 为截屏 JPG 路径的 Intel ijl15 编码。
// ============================================================
// ------------------------------------------------------------
// 0x69DE60 sub_69DE60
// ------------------------------------------------------------
// 【L1】CWSBuffer::Reset：+4..+20 五字段清零（vtable off_749D94 的构造尾巴）
int /*thiscall*/ sub_69DE60(int this)
{
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x69DE80 sub_69DE80
// ------------------------------------------------------------
// 【L1】CWSBuffer::Allocate(Size)：重复分配→0x80000002；new(Size) 入 +8 基址，
// 容量 +12=Size，memset 清零，+4=1；失败→0x80000000。ISocket::Init 调用两次。
int /*thiscall*/ sub_69DE80(int this, size_t Size)
{
  void *pMem; // edi

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  *(uint32_t *)(this + 12) = Size;
  pMem = operator new(Size);
  *(uint32_t *)(this + 8) = pMem;
  if ( pMem == nullptr )
    return 0x80000000;
  memset(pMem, 0, *(uint32_t *)(this + 12));
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x69DEE0 sub_69DEE0
// ------------------------------------------------------------
// 【L1】CWSBuffer::Free：free(+8) 基址，五字段清零
int /*thiscall*/ sub_69DEE0(int this)
{
  if ( *(uint32_t *)(this + 8) != 0 )
    j__free(*(void **)(this + 8));
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x69DF10 sub_69DF10
// ------------------------------------------------------------
// 【L1】CWSBuffer::Write(buf,len)（入队）：+4 未就绪→0x80000001；
// 写指针(+20)+len > 容量(+12) → 0x80000000（环满）；
// qmemcpy 到 基址+8+写偏移，+20 += len。上层: sub_698C80 包头入队。
int /*thiscall*/ sub_69DF10(int this, const void *pArg2, unsigned int uArg3)
{
  int fld_14; // edx

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  fld_14 = *(uint32_t *)(this + 20);
  if ( fld_14 + uArg3 > *(uint32_t *)(this + 12) )
    return 0x80000000;
  qmemcpy((void *)(fld_14 + *(uint32_t *)(this + 8)), pArg2, uArg3);
  *(uint32_t *)(this + 20) += uArg3;
  return 1;
}



// ------------------------------------------------------------
// 0x69DF70 sub_69DF70
// ------------------------------------------------------------
// 【L1】CWSBuffer::Read(len)（出队）：+4 未就绪→0；
// 读(+16)+len > 写(+20) → 越界：fopen("SocketLog.log","a") 写
// "* Devector Error" 四行现场（读/len/写）后返回 0；
// 正常：读指针 += len，读完(+16==+20)归零对，返回 基址+8+旧读偏移。
int /*thiscall*/ sub_69DF70(int this, int nArg2)
{
  int fld_10; // edx
  unsigned int fld_14; // ecx
  int v6; // eax
  FILE *pFile; // edi
  int pFile2; // [esp-20h] [ebp-24h]

  if ( *(uint8_t *)(this + 4) == 0 )
    return 0;
  fld_10 = *(uint32_t *)(this + 16);
  fld_14 = *(uint32_t *)(this + 20);
  v6 = fld_10 + nArg2;
  if ( fld_10 + nArg2 <= fld_14 )
  {
    *(uint32_t *)(this + 16) = v6;
    if ( v6 == fld_14 )
    {
      *(uint32_t *)(this + 16) = 0;
      *(uint32_t *)(this + 20) = 0;
    }
    return fld_10 + *(uint32_t *)(this + 8);
  }
  else
  {
    pFile = fopen("SocketLog.log", "a");
    fprintf(pFile, "* Devector Error\n");
    fprintf(pFile, "    - m_dwStartPoint + dwLen > m_dwEndPoint == true\n");
    fprintf(pFile, "    - m_dwStartPoint[%d]\n", pFile2);
    fprintf(pFile, "    - dwLen[%d]\n", nArg2);
    fprintf(pFile, "    - m_dwEndPoint[%d]\n", *(uint32_t *)(this + 20));
    fclose(pFile);
    return 0;
  }
}



// ------------------------------------------------------------
// 0x69E010 sub_69E010
// ------------------------------------------------------------
// 【L1】ijl15 JPEG 编码（截屏 JPG 路径）：ijlInit(69762A) 失败 → MessageBox "ijlInit..."；
// 填 JPEG_CORE_PROPERTIES(维度/通道 3或4/quality=a6=100 调用点) →
// ijlWrite(第9号调用) 失败 → "ijlWrite..."；ijlFree 后返回压缩缓冲与 *a7=大小。
void */*usercall*/ sub_69E010@<eax>(int nArg1@<edi>, int nArg2@<esi>, int nArg3, int nArg4, int nArg5, int nArg6, int *pDwArg7, int nArg8)
{
  int v9; // esi
  void *pMem; // edi
  uint8_t v13[4]; // [esp+0h] [ebp-4E6Ch] BYREF
  int nArg32; // [esp+4h] [ebp-4E68h]
  int nArg42; // [esp+8h] [ebp-4E64h]
  int nArg52; // [esp+Ch] [ebp-4E60h]
  int v17; // [esp+10h] [ebp-4E5Ch]
  int nArg62; // [esp+14h] [ebp-4E58h]
  int v19; // [esp+18h] [ebp-4E54h]
  int v20; // [esp+1Ch] [ebp-4E50h]
  void *pMem2; // [esp+24h] [ebp-4E48h]
  int v22; // [esp+28h] [ebp-4E44h]
  int nArg43; // [esp+2Ch] [ebp-4E40h]
  int nArg53; // [esp+30h] [ebp-4E3Ch]
  int nArg63; // [esp+34h] [ebp-4E38h]
  int v26; // [esp+38h] [ebp-4E34h]
  int v27; // [esp+3Ch] [ebp-4E30h]
  int nArg82; // [esp+50h] [ebp-4E1Ch]
  int dword_796E502; // [esp+4E68h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( ijl15_2() != 0 )
  {
    MessageBoxA(nullptr, "ijlInit...", &byte_74A308, 0);
    ijl15_3(v13);
    return nullptr;
  }
  else
  {
    nArg32 = nArg3;
    nArg42 = nArg4;
    nArg52 = nArg5;
    nArg43 = nArg4;
    nArg53 = nArg5;
    v17 = 0;
    nArg62 = nArg6;
    nArg63 = nArg6;
    v20 = 0;
    if ( nArg6 == 3 )
    {
      v9 = 1;
      v26 = 3;
      v27 = 1;
    }
    else
    {
      v9 = 4;
      v26 = 4;
      v27 = 0;
    }
    v19 = v9;
    pMem = operator new(nArg6 * nArg5 * nArg4);
    v22 = nArg6 * nArg5 * nArg4;
    pMem2 = pMem;
    nArg82 = nArg8;
    if ( ijl15_5(v13, 9, nArg1, nArg2) != 0 )
    {
      MessageBoxA(nullptr, "ijlWrite...", &byte_74A308, 0);
      ijl15_3(v13);
      return nullptr;
    }
    else
    {
      *pDwArg7 = v22;
      if ( ijl15_3(v13) != 0 )
      {
        MessageBoxA(nullptr, "ijlFree...", &byte_74A308, 0);
        return nullptr;
      }
      else
      {
        return pMem;
      }
    }
  }
}




// ============================================================
// SECTION 9  CRT 尾部：FSOUND/文件/longjmp/x87 数学（0x69E1A8-0x69FE27）
// ------------------------------------------------------------
// MSVC 静态 CRT 与 FMOD 导入 thunk（配套在 missing_tail.cpp）。
// 计划内以标准库语义注释，不逐行还原（docs/04 §CRT 替代原则）。
// ============================================================
// ------------------------------------------------------------
// 0x69E1A8 _FSOUND_SetDriver@4
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp__FSOUND_SetDriver@4（FMOD 声音库）
// attributes: thunk
int /*stdcall*/ FSOUND_SetDriver(int nArg1)
{
  return __imp__FSOUND_SetDriver@4(nArg1);
}



// ------------------------------------------------------------
// 0x69E1BA _FSOUND_SetVolume@8
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp__FSOUND_SetVolume@8
// attributes: thunk
int /*stdcall*/ FSOUND_SetVolume(int nArg1, int nArg2)
{
  return __imp__FSOUND_SetVolume@8(nArg1, nArg2);
}



// ------------------------------------------------------------
// 0x69E1C6 _FSOUND_Stream_SetEndCallback@12
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp__FSOUND_Stream_SetEndCallback@12
// attributes: thunk
int /*stdcall*/ FSOUND_Stream_SetEndCallback(int nArg1, int nArg2, int nArg3)
{
  return __imp__FSOUND_Stream_SetEndCallback@12(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x69E1D8 _FSOUND_Stream_Play@8
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp__FSOUND_Stream_Play@8
// attributes: thunk
int /*stdcall*/ FSOUND_Stream_Play(int nArg1, int nArg2)
{
  return __imp__FSOUND_Stream_Play@8(nArg1, nArg2);
}



// ------------------------------------------------------------
// 0x69E1EA _FSOUND_Stream_Open@16
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp__FSOUND_Stream_Open@16
// attributes: thunk
int /*stdcall*/ FSOUND_Stream_Open(int nArg1, int nArg2, int nArg3, int nArg4)
{
  return __imp__FSOUND_Stream_Open@16(nArg1, nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x69E1F6 RtlUnwind
// ------------------------------------------------------------
// 【L1】导入 thunk → __imp_RtlUnwind（SEH 展开链）
// attributes: thunk
void /*stdcall*/ RtlUnwind(PVOID TargetFrame, PVOID TargetIp, PEXCEPTION_RECORD ExceptionRecord, PVOID ReturnValue)
{
  __imp_RtlUnwind(TargetFrame, TargetIp, ExceptionRecord, ReturnValue);
}



// ------------------------------------------------------------
// 0x69E1FC __filelength
// ------------------------------------------------------------
// 【L1】CRT _filelength：句柄表锁内 _lseek_lk(END) 取文件长，失败 errno=9(EBADF)
int /*cdecl*/ _filelength(int FileHandle)
{
  int v1; // esi
  LONG v2; // esi
  int v4; // [esp+10h] [ebp-1Ch]

  if ( FileHandle < uNumber )
  {
    v1 = 36 * (FileHandle & 0x1F);
    if ( (*(uint8_t *)(dword_9D3E60[FileHandle >> 5] + v1 + 4) & 1) != 0 )
    {
      _lock_fhandle(FileHandle);
      if ( (*(uint8_t *)(dword_9D3E60[FileHandle >> 5] + v1 + 4) & 1) != 0 )
      {
        v2 = _lseek_lk(FileHandle, 0, 1u);
        if ( v2 != -1 )
        {
          v4 = _lseek_lk(FileHandle, 0, 2u);
          if ( v2 != v4 )
            _lseek_lk(FileHandle, v2, 0);
          goto LABEL_9;
        }
      }
      else
      {
        *_errno() = 9;
        *__doserrno() = 0;
      }
      v4 = -1;
LABEL_9:
      _unlock_fhandle(FileHandle);
      return v4;
    }
  }
  *_errno() = 9;
  *__doserrno() = 0;
  return -1;
}



// ------------------------------------------------------------
// 0x69E2D0 __fileno
// ------------------------------------------------------------
// 【L1】CRT _fileno：FILE->_file
int /*cdecl*/ _fileno(FILE *Stream)
{
  return Stream->_file;
}



// ------------------------------------------------------------
// 0x69E2D8 _longjmp
// ------------------------------------------------------------
// 【L1】CRT longjmp：FS:0 帧校验 → _global_unwind2/_local_unwind2 →
// 1447244336=0x56433230 法线校验 → _NLG_Notify → 跳转
void /*cdecl*/ /*noreturn*/ longjmp(jmp_buf Buf, int Value)
{
  int v2; // esi
  void (/*stdcall*/ *v3)(int *__attribute__((__org_typedef(jmp_buf)))); // eax

  v2 = Buf[6];
  if ( v2 != __readfsdword(0) )
    _global_unwind2((PVOID)Buf[6]);
  if ( v2 != 0 )
  {
    if ( _rt_probe_read4(Buf + 8) != 0 && Buf[8] == 1447244336 )
    {
      v3 = (void (/*stdcall*/ *)(int *__attribute__((__org_typedef(jmp_buf)))))Buf[9];
      if ( v3 != nullptr )
        v3(Buf);
    }
    else
    {
      _local_unwind2(v2, Buf[7]);
    }
  }
  _NLG_Notify(0);
  ((void (*)(void))Buf[5])();
}



// ------------------------------------------------------------
// 0x69E350 nullsub_14
// ------------------------------------------------------------
// 【L1】空桩 nullsub_14（CRT 对齐）
void nullsub_14()
{
  ;
}



// ------------------------------------------------------------
// 0x69E360 _pow
// ------------------------------------------------------------
// 【L1】CRT _pow（反编译失败计划内替代 → math.h pow；610B 大函数）
// (decomp failed → 标准库替代) _pow
// [计划内] 本函数属 MSVC 静态 CRT，源码层以标准库调用替代，不做逐行还原。
// 替代: 幂函数 → <math.h> pow()（曾因 610B 大函数反编译卡死）


// ------------------------------------------------------------
// 0x69E5C2 _test_whether_TOS_is_int
// ------------------------------------------------------------
// 【L1】CRT x87 TOS 整数判定（rint 等价，dbl_79BE70=2^63 缩放）
void /*usercall*/ test_whether_TOS_is_int(long double fArg1@<st0>)
{
  char v1; // cl

  if ( rint(fArg1) == fArg1 )
  {
    v1 = 1;
    if ( rint(fArg1 * dbl_79BE70) == fArg1 * dbl_79BE70 )
      v1 = 2;
    odd(v1);
  }
}



// ------------------------------------------------------------
// 0x69E5E6 _odd
// ------------------------------------------------------------
// 【L1】CRT x87 空 helper（odd）
void odd()
{
  ;
}



// ------------------------------------------------------------
// 0x69E5F0 __CIacos
// ------------------------------------------------------------
// 【L1】CRT _CIacos：x87 寄存器版 acos（_checkTOS_withFB 前置）
double /*usercall*/ _CIacos@<st0>(uint64_t x@<st0>)
{
  int v2; // [esp+0h] [ebp-Ch]
  int v3; // [esp+4h] [ebp-8h]

  _checkTOS_withFB(x, HIDWORD(x));
  return start_1(v2, v3);
}



// ------------------------------------------------------------
// 0x69E604 _acos
// ------------------------------------------------------------
// 【L1】CRT acos（cdecl 入口 → start_1 主体）
double /*cdecl*/ acos(double X)
{
  int v1; // ecx

  _fload_withFB(v1, &X);
  return start_1(LODWORD(X), HIDWORD(X));
}



// ------------------------------------------------------------
// 0x69E60D start_1
// ------------------------------------------------------------
// 【L1】CRT acos/asin 主体（反编译失败计划内替代；链接器/CRT 桩）
// (decomp failed → 标准库替代) start_1
// [计划内] 本函数属 MSVC 静态 CRT，源码层以标准库调用替代，不做逐行还原。
// 替代: CRT 段启动桩 → 链接器生成


// ------------------------------------------------------------
// 0x69E6BB __finite
// ------------------------------------------------------------
// 【L1】CRT _finite：指数位 != 0x7FF0 即有限
int /*cdecl*/ _finite(double X)
{
  return (HIWORD(X) & 0x7FF0) != 32752;
}



// ------------------------------------------------------------
// 0x69E6D0 __fpclass
// ------------------------------------------------------------
// 【L1】CRT _fpclass：IEEE754 分类（512/4/2/1/16/128/32/64/8/256 全谱）
int /*cdecl*/ _fpclass(double X)
{
  int v1; // eax
  int v2; // eax
  int v4; // ecx

  if ( (HIWORD(X) & 0x7FF0) == 0x7FF0 )
  {
    v1 = _sptype(LODWORD(X), HIDWORD(X)) - 1;
    if ( v1 != 0 )
    {
      v2 = v1 - 1;
      if ( v2 == 0 )
        return 4;
      if ( v2 != 1 )
        return 1;
      return 2;
    }
    else
    {
      return 512;
    }
  }
  else
  {
    v4 = HIWORD(X) & 0x8000;
    if ( (HIWORD(X) & 0x7FF0) == 0 && ((HIDWORD(X) & 0xFFFFF) != 0 || LODWORD(X) != 0) )
    {
      return (HIWORD(X) & 0x8000) != 0 ? 16 : 128;
    }
    else if ( X == 0.0 )
    {
      return v4 != 0 ? 32 : 64;
    }
    else
    {
      return v4 != 0 ? 8 : 256;
    }
  }
}



// ------------------------------------------------------------
// 0x69E76C __ftol
// ------------------------------------------------------------
// 【L1】CRT _ftol：x87→int64（原型 usercall st0）
int64_t /*usercall*/ _ftol@<edx:eax>(double fArg1@<st0>)
{
  return (int64_t)fArg1;
}



// ------------------------------------------------------------
// 0x69E7A0 _floor
// ------------------------------------------------------------
// 【L1】CRT floor：SSE 快路径（MXCSR 0x1F80 检测）+ x87 慢路径（计划内替代 floor）
double /*cdecl*/ floor(double X)
{
  int v1; // eax
  bool v2; // zf
  __m128i v3; // xmm7
  __m128d v4; // xmm0
  int v5; // eax
  __m128i v6; // xmm2
  __m128i v7; // xmm1
  double v8; // xmm1_8
  double result; // st7
  __m128d v10; // xmm1
  __m128d v11; // xmm3
  double v12; // xmm0_8
  char v13; // [esp+8h] [ebp-8h]

  if ( dword_9D3BF8 == 0 )
    goto _floor;
  v1 = _mm_getcsr() & 0x1F80;
  v2 = v1 == 8064;
  if ( v1 == 8064 )
    v2 = (v13 & 0x7F) == 127;
  if ( v2 )
  {
    v3 = _mm_loadl_epi64((const __m128i *)&X);
    v4 = (__m128d)_mm_srli_epi64(v3, 0x34u);
    v5 = _mm_cvtsi128_si32((__m128i)v4);
    v6 = _mm_sub_epi32((__m128i)xmmword_74A340, (__m128i)_mm_and_pd(v4, (__m128d)xmmword_74A370));
    v7 = _mm_srl_epi64(v3, v6);
    if ( (v5 & 0x800) != 0 )
    {
      v10 = (__m128d)_mm_sll_epi64(v7, v6);
      v11 = (__m128d)_mm_loadl_epi64((const __m128i *)&X);
      v12 = _mm_cmplt_pd(v11, v10).m128d_f64[0];
      if ( v5 < 3071 )
      {
        *(uint64_t *)&X = *(uint64_t *)&_mm_cmplt_pd(v11, (__m128d)xmmword_74A360).m128d_f64[0] & 0x3FF0000000000000LL
                      | 0x8000000000000000uLL;
        return X;
      }
      else
      {
        if ( v5 > 3122 )
          return X;
        return v10.m128d_f64[0] - COERCE_DOUBLE(*(uint64_t *)&v12 & 0x3FF0000000000000LL);
      }
    }
    else
    {
      if ( v5 >= 1023 )
      {
        *(uint64_t *)&v8 = v7.m128i_i64[0] << v6.m128i_i8[0];
        if ( v5 <= 1074 )
        {
          X = v8;
          return v8;
        }
        return X;
      }
      return 0.0;
    }
  }
  else
  {
_floor:
    _floor_default(X);
  }
  return result;
}



// ------------------------------------------------------------
// 0x69E8D0 __aullshr
// ------------------------------------------------------------
// 【L1】CRT _aullshr：uint64 逻辑右移（cl 计数）
uint64_t /*usercall*/ _aullshr@<edx:eax>(uint64_t uArg1@<edx:eax>, uint8_t uArg2@<cl>)
{
  if ( uArg2 >= 0x40u )
    return 0;
  else
    return uArg1 >> uArg2;
}



// ------------------------------------------------------------
// 0x69E8EF _wcslen
// ------------------------------------------------------------
// 【L1】CRT wcslen
size_t /*cdecl*/ wcslen(const wchar_t *String)
{
  const wchar_t *String2; // eax
  int16_t v2; // cx

  String2 = String;
  do
    v2 = *String2++;
  while ( v2 != 0 );
  return String2 - String - 1;
}



// ------------------------------------------------------------
// 0x69E905 __rt_probe_read4@4
// ------------------------------------------------------------
// 【L1】CRT _rt_probe_read4：4 字节安全读探测（SEH frame 探针）
int /*stdcall*/ _rt_probe_read4(int nArg1)
{
  return 1;
}



// ------------------------------------------------------------
// 0x69E950 __CIpow_pentium4
// ------------------------------------------------------------
// 【L1】CRT _CIpow_pentium4：x87 寄存器版 pow（P4 分派入口）
void /*usercall*/ _CIpow_pentium4(double fArg1@<st1>, double fArg2@<st0>)
{
  _pow_pentium4(fArg2, fArg1);
}



// ------------------------------------------------------------
// 0x69E969 __pow_pentium4
// ------------------------------------------------------------
// 【L1】CRT _pow_pentium4：pow 主体（exp2(y*log2(x)) 管线，2.2KB 大函数）
double /*usercall*/ _pow_pentium4@<st0>(
        __m128d a1@<xmm0>,
        __m128d a2@<xmm1>,
        __m128d a3@<xmm2>,
        __m128d a4@<xmm3>,
        __m128d a5@<xmm4>,
        __m128d a6@<xmm5>,
        __m128d a7@<xmm7>,
        double a8,
        double a9)
{
  __m128d v9; // xmm7
  __m128i inserted; // xmm0
  int epi16; // ecx
  int v12; // eax
  __m128d v13; // xmm7
  __m128d v14; // xmm6
  int v15; // edx
  unsigned int v16; // ecx
  unsigned int v17; // edx
  __m128d v18; // xmm1
  __m128d v19; // xmm0
  __m128d v20; // xmm7
  int v21; // eax
  __m128d v22; // xmm6
  double v23; // xmm2_8
  int v24; // eax
  double v25; // xmm2_8
  double v26; // xmm5_8
  double v27; // xmm2_8
  double v28; // xmm2_8
  __m128i v29; // xmm1
  int v30; // edx
  double v31; // xmm2_8
  __m128d v32; // xmm0
  __m128d v33; // xmm6
  __m128d v34; // xmm7
  unsigned int v35; // eax
  double v36; // xmm2_8
  double v37; // xmm4_8
  double v38; // xmm3_8
  double v39; // xmm1_8
  double v40; // xmm3_8
  double v41; // xmm5_8
  double v42; // xmm5_8
  double v43; // xmm4_8
  double v44; // xmm5_8
  int v45; // eax
  __m128d v46; // xmm2
  __m128d v47; // xmm7
  __m128i v48; // xmm2
  __m128i v49; // xmm3
  __m128d v50; // xmm0
  __m128d v51; // xmm6
  double v52; // xmm4_8
  __m128d v53; // xmm0
  __m128i v54; // xmm7
  double result; // st7
  int v56; // eax
  __m128i v57; // xmm1
  unsigned int v58; // ecx
  __m128i v59; // xmm2
  __m128i v60; // xmm1
  __m128i v61; // xmm2
  uint8_t v62; // al
  unsigned int v63; // edx
  __m128i v64; // xmm1
  int v65; // edx
  int v66; // eax
  __m128d v67; // xmm7
  int v68; // eax
  __m128d v69; // xmm0
  int v70; // edx
  __m128i v71; // xmm1
  int v72; // eax
  int v73; // eax
  int v74; // eax
  __m128i v75; // xmm4
  int v76; // ecx
  unsigned int v77; // eax
  int v78; // eax
  unsigned int v79; // ecx
  unsigned int v80; // edx
  unsigned int v81; // edi
  double v82; // xmm4_8
  __m128d v83; // xmm2
  __m128d v84; // xmm7
  __m128i v85; // xmm2
  __m128i v86; // xmm3
  __m128d v87; // xmm0
  __m128d v88; // xmm6
  double v89; // xmm4_8
  __m128i v90; // xmm7
  double v91; // xmm7_8
  double v92; // xmm1_8
  int64_t v93; // xmm4_8
  double v94; // xmm1_8
  double v95; // xmm6_8
  int v96; // eax
  int v97; // eax
  int v98; // eax
  int v99; // edx
  unsigned int v100; // eax
  int v101; // [esp+0h] [ebp-1Ch] BYREF
  double v102; // [esp+10h] [ebp-Ch] BYREF

  a1.m128d_f64[0] = a8;
  a7.m128d_f64[0] = COERCE_DOUBLE(0xFFFFFFFFFFFFFLL);
  a3.m128d_f64[0] = 1.0;
  v9 = _mm_and_pd(a7, a1);
  a5.m128d_f64[0] = a8;
  inserted = _mm_srli_epi64((__m128i)a1, 0x2Cu);
  v13 = _mm_or_pd(v9, a3);
  epi16 = _mm_extract_epi16((__m128i)a5, 3);
  v12 = ((uint8_t)_mm_extract_epi16(inserted, 0) + 1) & 0x1FE;
  v13.m128d_f64[0] = v13.m128d_f64[0] * *(double *)((char *)&qword_74A390 + 4 * v12);
  a6.m128d_f64[0] = *(double *)((char *)&qword_74A390 + 4 * v12);
  v14 = *(__m128d *)((char *)&xmmword_74A7A0 + 8 * v12);
  v15 = 32751 - epi16;
  if ( ((32751 - epi16) | (unsigned int)(epi16 - 16)) < 0x80000000 )
  {
    v16 = 0;
    v17 = 261759;
    goto BACK_MAIN;
  }
  a2.m128d_f64[0] = a9;
  a4.m128d_f64[0] = NAN;
  v56 = _mm_cvtsi128_si32((__m128i)a2);
  a3.m128d_f64[0] = a9;
  v57 = _mm_srli_epi64((__m128i)_mm_and_pd(a2, a4), 0x20u);
  v58 = _mm_cvtsi128_si32(v57);
  if ( v58 >= 0x7FF00000 )
  {
    v13.m128d_f64[0] = a8;
    a5.m128d_f64[0] = a8;
    v30 = _mm_cvtsi128_si32((__m128i)v13);
    v16 = _mm_cvtsi128_si32(_mm_srli_epi64((__m128i)v13, 0x20u));
    if ( (v16 & 0x7FFFFFFF) < 0x7FF00000 || (v16 & 0x7FFFFFFF) <= 0x7FF00000 && v30 == 0 )
      goto Y_INF_NAN;
    goto X_NAN;
  }
  if ( (v58 | v56) == 0 )
  {
    v74 = _mm_cvtsi128_si32((__m128i)a5);
    v75 = _mm_srli_epi64((__m128i)a5, 0x20u);
    v76 = v74;
    v69.m128d_f64[0] = 1.0;
    v70 = 26;
    if ( (_mm_cvtsi128_si32(v75) & 0x7FFFFFFF | v74) != 0 )
    {
      v70 = 29;
      v77 = _mm_cvtsi128_si32(v75) & 0x7FFFFFFF;
      if ( v77 <= 0x7FF00000 && (v77 < 0x7FF00000 || v76 == 0) )
      {
        v102 = 1.0;
        return 1.0;
      }
    }
    goto CALL_LIBM_ERROR;
  }
  if ( v15 >= 0 )
  {
    v16 = 0;
    goto DENORMAL_X;
  }
  v59 = (__m128i)_mm_or_pd(a3, (__m128d)_mm_slli_epi64((__m128i)a4, 0x34u));
  a4 = 0;
  v60 = _mm_max_epi16(_mm_sub_epi32(_mm_srli_epi64(v57, 0x14u), _mm_cvtsi32_si128(0x3F3u)), (__m128i)0LL);
  v61 = _mm_cmpeq_epi32(_mm_sll_epi64(v59, v60), (__m128i)0LL);
  v62 = _mm_movemask_epi8(v61);
  v63 = (32751 - v15) & 0x7FFF;
  if ( v63 >= 0x7FF0 )
  {
    a4.m128d_f64[0] = COERCE_DOUBLE(0xFFFFFFFFFFFFFLL);
    v71 = _mm_cmpeq_epi32((__m128i)0LL, (__m128i)_mm_and_pd(a4, a5));
    if ( (uint8_t)_mm_movemask_epi8(v71) == 255 )
    {
      if ( (_mm_extract_epi16((__m128i)a5, 3) & 0x8000) != 0 )
      {
        if ( v62 == 255 )
        {
          *(double *)v71.m128i_i64 = a9;
          *(double *)v61.m128i_i64 = a9;
          v71 = _mm_sub_epi32(
                  _mm_srli_epi64((__m128i)_mm_and_pd((__m128d)v71, (__m128d)xmmword_74DC40), 0x34u),
                  _mm_cvtsi32_si128(0x3F4u));
          if ( (uint8_t)_mm_movemask_epi8(_mm_cmpeq_epi32(_mm_sll_epi64(v61, v71), (__m128i)0LL)) != 255 )
          {
            *(double *)v71.m128i_i64 = a9;
            if ( (_mm_extract_epi16(v71, 3) & 0x8000) == 0 )
              return -INFINITY;
            return -0.0;
          }
        }
        *(double *)v71.m128i_i64 = a9;
        if ( (_mm_extract_epi16(v71, 3) & 0x8000) != 0 )
          return 0.0;
      }
      else
      {
        *(double *)v71.m128i_i64 = a9;
        if ( (_mm_extract_epi16(v71, 3) & 0x8000) != 0 )
          return 0.0;
      }
      return INFINITY;
    }
X_NAN:
    v69.m128d_f64[0] = a5.m128d_f64[0] + a5.m128d_f64[0];
    v70 = 1006;
    goto CALL_LIBM_ERROR;
  }
  if ( v62 != 255 )
  {
    *(double *)v61.m128i_i64 = a8;
    v72 = _mm_cvtsi128_si32(v61);
    a3 = (__m128d)_mm_srli_epi64(v61, 0x20u);
    v66 = _mm_cvtsi128_si32((__m128i)a3) & 0x7FFFFFFF | v72;
    v16 = 0;
    if ( v66 != 0 )
    {
      v69.m128d_f64[0] = NAN;
      v70 = 28;
      goto CALL_LIBM_ERROR;
    }
    goto ZERO_X;
  }
  *(double *)v60.m128i_i64 = a9;
  *(double *)v61.m128i_i64 = a9;
  a4 = (__m128d)_mm_cvtsi32_si128(0x3F4u);
  v64 = _mm_sub_epi32(_mm_srli_epi64((__m128i)_mm_and_pd((__m128d)v60, (__m128d)xmmword_74DC40), 0x34u), (__m128i)a4);
  a4.m128d_f64[0] = -0.0;
  a3 = (__m128d)_mm_cmpeq_epi32(_mm_sll_epi64(v61, v64), (__m128i)a4);
  v16 = ((uint8_t)_mm_movemask_epi8((__m128i)a3) + 261889) & 0x40000;
  if ( v63 >= 0x10 )
  {
    v17 = 786047;
    goto BACK_MAIN;
  }
DENORMAL_X:
  inserted = _mm_insert_epi16((__m128i)0LL, 0x43F0u, 3);
  v13.m128d_f64[0] = COERCE_DOUBLE(0xFFFFFFFFFFFFFLL);
  a3.m128d_f64[0] = 1.0;
  *(double *)inserted.m128i_i64 = *(double *)inserted.m128i_i64 * a8;
  v65 = _mm_cvtsi128_si32((__m128i)a5);
  a5 = (__m128d)_mm_srli_epi64((__m128i)a5, 0x20u);
  v66 = _mm_cvtsi128_si32((__m128i)a5);
  if ( v65 == 0 )
  {
ZERO_X:
    if ( (v66 & 0x7FFFFFFF) != 0 )
      goto BACK_DEN;
    if ( a9 < 0.0 )
    {
      *(uint64_t *)&v69.m128d_f64[0] = _mm_cvtsi32_si128((v16 << 13) & v66 | 0x7FF00000).m128i_u64[0] << 32;
      v70 = 27;
      goto CALL_LIBM_ERROR;
    }
    if ( ((v16 << 13) & v66) == 0 )
      return 0.0;
    return -0.0;
  }
BACK_DEN:
  v67 = _mm_and_pd(v13, (__m128d)inserted);
  a5.m128d_f64[0] = *(double *)inserted.m128i_i64;
  inserted = _mm_srli_epi64((__m128i)_mm_and_pd((__m128d)inserted, (__m128d)xmmword_74DC40), 0x2Cu);
  v13 = _mm_or_pd(v67, a3);
  v68 = ((uint8_t)_mm_extract_epi16(inserted, 0) + 1) & 0x1FE;
  v13.m128d_f64[0] = v13.m128d_f64[0] * *(double *)((char *)&qword_74A390 + 4 * v68);
  a6.m128d_f64[0] = *(double *)((char *)&qword_74A390 + 4 * v68);
  v14 = *(__m128d *)((char *)&xmmword_74A7A0 + 8 * v68);
  v17 = 278143;
BACK_MAIN:
  v18 = (__m128d)_mm_cvtsi32_si128(v17);
  v19 = _mm_cvtepi32_pd(_mm_srli_epi64(_mm_sub_epi64(inserted, (__m128i)v18), 8u));
  v18.m128d_f64[0] = NAN;
  a4.m128d_f64[0] = v13.m128d_f64[0];
  v20 = (__m128d)_mm_srli_epi64((__m128i)v13, 0x26u);
  v21 = ((uint8_t)_mm_extract_epi16((__m128i)v20, 0) + 1) & 0x1FE;
  a4.m128d_f64[0] = a4.m128d_f64[0] * *(double *)((char *)&qword_74AFB0 + 4 * v21);
  a6.m128d_f64[0] = a6.m128d_f64[0] * *(double *)((char *)&qword_74AFB0 + 4 * v21);
  v22 = _mm_add_pd(v14, *(__m128d *)((char *)&xmmword_74B3C0 + 8 * v21));
  a5 = _mm_or_pd(_mm_and_pd(a5, (__m128d)xmmword_74DC20), (__m128d)xmmword_74DC30);
  v22.m128d_f64[0] = v22.m128d_f64[0] + v19.m128d_f64[0];
  v29 = (__m128i)_mm_and_pd(v18, a5);
  v23 = a4.m128d_f64[0];
  a4 = (__m128d)_mm_srli_epi64((__m128i)a4, 0x1Fu);
  v19.m128d_f64[0] = NAN;
  a5.m128d_f64[0] = a5.m128d_f64[0] - *(double *)v29.m128i_i64;
  v24 = ((_mm_extract_epi16((__m128i)a4, 0) & 0x1FF) + 1) & 0x3FE;
  a6.m128d_f64[0] = a6.m128d_f64[0] * *(double *)((char *)&qword_74BBD0 + 4 * v24);
  v25 = v23 * *(double *)((char *)&qword_74BBD0 + 4 * v24);
  v33 = _mm_add_pd(v22, *(__m128d *)((char *)&xmmword_74C3E0 + 8 * v24));
  v32 = _mm_and_pd(v19, a6);
  v26 = a6.m128d_f64[0] - v32.m128d_f64[0];
  v20.m128d_f64[0] = v25 + -1.442694902420044;
  a4.m128d_f64[0] = v32.m128d_f64[0];
  v27 = v25 - v32.m128d_f64[0] * *(double *)v29.m128i_i64;
  v32.m128d_f64[0] = v33.m128d_f64[0];
  v28 = v27 - *(double *)v29.m128i_i64 * v26;
  v33.m128d_f64[0] = v33.m128d_f64[0] + v20.m128d_f64[0];
  *(double *)v29.m128i_i64 = a9;
  v30 = _mm_extract_epi16((__m128i)v33, 3);
  v31 = v28 - a4.m128d_f64[0] * a5.m128d_f64[0] - a5.m128d_f64[0] * v26;
  a5.m128d_f64[0] = v33.m128d_f64[0];
  v32.m128d_f64[0] = v32.m128d_f64[0] - v33.m128d_f64[0] + v20.m128d_f64[0];
  v20.m128d_f64[0] = v20.m128d_f64[0] - v31;
  v33.m128d_f64[0] = v33.m128d_f64[0] - v31;
  v34 = _mm_unpacklo_pd(v20, v20);
  v35 = _mm_extract_epi16(v29, 3) & 0x7FF0;
  if ( v35 >= 0x7FF0 )
  {
    a5.m128d_f64[0] = a8;
    a3.m128d_f64[0] = a9;
    if ( _mm_cvtsi128_si32((__m128i)a5) == 0 )
    {
      a5 = (__m128d)_mm_srli_epi64((__m128i)a5, 0x20u);
      v30 = _mm_cvtsi128_si32((__m128i)a5);
      if ( v30 == 1072693248 )
        goto RET_ONE;
      if ( v30 == -1074790400 )
      {
        a4.m128d_f64[0] = COERCE_DOUBLE(0xFFFFFFFFFFFFFLL);
        if ( _mm_movemask_epi8(_mm_cmpeq_epi32((__m128i)0LL, (__m128i)_mm_and_pd(a4, a3))) == 255 )
          return 1.0;
        goto RET_Y_NAN;
      }
    }
Y_INF_NAN:
    a4.m128d_f64[0] = COERCE_DOUBLE(0xFFFFFFFFFFFFFLL);
    if ( (uint8_t)_mm_movemask_epi8(_mm_cmpeq_epi32((__m128i)0LL, (__m128i)_mm_and_pd(a4, a3))) != 255 )
    {
RET_Y_NAN:
      v69.m128d_f64[0] = a3.m128d_f64[0] + a3.m128d_f64[0];
      v70 = 1006;
      goto CALL_LIBM_ERROR;
    }
    a5.m128d_f64[0] = a8;
    v73 = _mm_extract_epi16((__m128i)a3, 3) & 0x8000;
    if ( (v16 ^ 0xBFF00000 | v30) != 0 )
    {
      if ( v73 != 0 )
      {
        if ( (_mm_extract_epi16((__m128i)a5, 3) & 0x7FF0u) >= 0x3FF0 )
          return 0.0;
      }
      else if ( (_mm_extract_epi16((__m128i)a5, 3) & 0x7FF0u) < 0x3FF0 )
      {
        return 0.0;
      }
      return INFINITY;
    }
RET_ONE:
    v69.m128d_f64[0] = a9 + NAN;
    v70 = 28;
    goto CALL_LIBM_ERROR;
  }
  if ( (((v30 & 0x7FF0) + v35 - 16368 - 15472) | (16544 - ((v30 & 0x7FF0) + v35 - 16368))) < 0x80000000
    || (a5 = _mm_mul_pd((__m128d)_mm_shuffle_epi32(v29, 68), v33),
        v98 = _mm_extract_epi16((__m128i)a5, 3) & 0x7FF0,
        v99 = 16544 - v98,
        ((v100 = v98 - 15472) | v99) < 0x80000000) )
  {
    v36 = v31 - (a5.m128d_f64[0] - v33.m128d_f64[0]);
    *(uint64_t *)&v37 = COERCE_UNSIGNED_INT64(NAN) & *(uint64_t *)&v33.m128d_f64[0];
    v32.m128d_f64[0] = v32.m128d_f64[0] - v36;
    v38 = COERCE_DOUBLE(COERCE_UNSIGNED_INT64(NAN) & *(uint64_t *)&a9)
        * COERCE_DOUBLE(COERCE_UNSIGNED_INT64(NAN) & *(uint64_t *)&v33.m128d_f64[0]);
    v33.m128d_f64[0] = v33.m128d_f64[0] - COERCE_DOUBLE(COERCE_UNSIGNED_INT64(NAN) & *(uint64_t *)&v33.m128d_f64[0]);
    v39 = a9 - COERCE_DOUBLE(COERCE_UNSIGNED_INT64(NAN) & *(uint64_t *)&a9);
    v40 = v38 * *(double *)_mm_insert_epi16((__m128i)0LL, 0x4060u, 3).m128i_i64;
    v41 = COERCE_DOUBLE(COERCE_UNSIGNED_INT64(NAN) & *(uint64_t *)&a9) * v33.m128d_f64[0];
    v33.m128d_f64[0] = v33.m128d_f64[0] * v39;
    v42 = v41 + v37 * v39;
    *(uint64_t *)&v43 = _mm_shuffle_epi32((__m128i)v33, 238).m128i_u64[0];
    v44 = v42 + v33.m128d_f64[0];
    v45 = (int)v40;
    if ( (((int)v40 + 123391) | (130943 - (int)v40)) > 0 )
    {
      v46 = _mm_mul_pd((__m128d)xmmword_74D3F0, v34);
      v47 = _mm_mul_pd(v34, v34);
      v48 = (__m128i)_mm_add_pd(v46, _mm_mul_pd((__m128d)xmmword_74D400, v47));
      *(double *)v48.m128i_i64 = *(double *)v48.m128i_i64 * v47.m128d_f64[0]
                               + *(double *)_mm_shuffle_epi32(v48, 238).m128i_i64
                               + v43
                               + v32.m128d_f64[0];
      v32.m128d_f64[0] = (v40 - (v40 + 6.755399441055744e15 - 6.755399441055744e15))
                       * *(double *)_mm_insert_epi16((__m128i)0LL, 0x3F80u, 3).m128i_i64;
      v49 = (__m128i)_mm_mul_pd(
                       *((__m128d *)&unk_74D410 + ((int)v40 & 0x7F)),
                       (__m128d)_mm_shuffle_epi32(
                                  _mm_slli_epi64(_mm_cvtsi32_si128((((int)v40 + v16) & 0xFFFFFF80) + 130944), 0x2Du),
                                  68));
      v32.m128d_f64[0] = v32.m128d_f64[0] + v44 + *(double *)v48.m128i_i64 * a9;
      v50 = _mm_unpacklo_pd(v32, v32);
      v51 = _mm_mul_pd((__m128d)xmmword_74DC50, v50);
      v52 = 0.6931471805599453 * v50.m128d_f64[0];
      v53 = _mm_mul_pd(v50, v50);
      v54 = (__m128i)_mm_mul_pd(_mm_add_pd((__m128d)xmmword_74DC60, v51), v53);
      return v53.m128d_f64[0] * *(double *)v49.m128i_i64 * *(double *)v54.m128i_i64
           + *(double *)_mm_shuffle_epi32(v49, 238).m128i_i64
           + *(double *)_mm_shuffle_epi32(v54, 238).m128i_i64 * *(double *)v49.m128i_i64
           + v52 * *(double *)v49.m128i_i64
           + *(double *)v49.m128i_i64;
    }
    if ( v45 <= 0 )
    {
      if ( v45 <= -261632 )
      {
RET_ZERO_UF:
        *(uint64_t *)&v69.m128d_f64[0] = COERCE_UNSIGNED_INT64(2.225073858507201e-308 * 2.225073858507201e-308)
                                     | (_mm_cvtsi32_si128(v16).m128i_u64[0] << 45);
        v70 = 25;
        goto CALL_LIBM_ERROR;
      }
      v78 = (int)v40 & 0x7F;
      v79 = v16 + 128;
      v80 = ((int)v40 & 0xFFFFFF80) + 261760;
      v81 = 0;
    }
    else
    {
      if ( (unsigned int)v45 >= 0x40000 )
        goto RET_INF_OF;
      v78 = (int)v40 & 0x7F;
      v79 = v16 + 261888;
      v80 = ((int)v40 - 128) & 0xFFFFFF80;
      v81 = 16368;
    }
    v82 = v43 + v32.m128d_f64[0];
    v83 = _mm_mul_pd((__m128d)xmmword_74D3F0, v34);
    v84 = _mm_mul_pd(v34, v34);
    v32.m128d_f64[0] = v40 - (v40 + 6.755399441055744e15 - 6.755399441055744e15);
    v85 = (__m128i)_mm_add_pd(v83, _mm_mul_pd((__m128d)xmmword_74D400, v84));
    v86 = (__m128i)_mm_mul_pd(
                     *((__m128d *)&unk_74D410 + v78),
                     (__m128d)_mm_shuffle_epi32(_mm_slli_epi64(_mm_cvtsi32_si128(v80), 0x2Du), 68));
    v32.m128d_f64[0] = v32.m128d_f64[0] * *(double *)_mm_insert_epi16((__m128i)0LL, 0x3F80u, 3).m128i_i64
                     + v44
                     + (*(double *)v85.m128i_i64 * v84.m128d_f64[0]
                      + *(double *)_mm_shuffle_epi32(v85, 238).m128i_i64
                      + v82)
                     * a9;
    v87 = _mm_unpacklo_pd(v32, v32);
    v88 = _mm_mul_pd((__m128d)xmmword_74DC50, v87);
    v89 = 0.6931471805599453 * v87.m128d_f64[0];
    v69 = _mm_mul_pd(v87, v87);
    v90 = (__m128i)_mm_mul_pd(_mm_add_pd((__m128d)xmmword_74DC60, v88), v69);
    v88.m128d_f64[0] = *(double *)_mm_shuffle_epi32(v90, 238).m128i_i64;
    v69.m128d_f64[0] = v69.m128d_f64[0] * *(double *)v86.m128i_i64 * *(double *)v90.m128i_i64;
    *(uint64_t *)&v91 = _mm_cvtsi32_si128(v79).m128i_u64[0] << 45;
    v85.m128i_i8[0] = _mm_cvtsi32_si128((((uint8_t)((int)(130944 - v80) >> 7) + 2) & 0x20u) + ((int)(130944 - v80) >> 7) + 2).m128i_u8[0];
    *(uint64_t *)&v92 = (-1LL << v85.m128i_i8[0]) & v86.m128i_i64[0];
    v69.m128d_f64[0] = v69.m128d_f64[0]
                     + *(double *)_mm_shuffle_epi32(v86, 238).m128i_i64
                     + v88.m128d_f64[0] * *(double *)v86.m128i_i64
                     + v89 * *(double *)v86.m128i_i64;
    v93 = -1LL << v85.m128i_i8[0];
    *(double *)v86.m128i_i64 = *(double *)v86.m128i_i64 - v92;
    *(double *)v85.m128i_i64 = v92;
    *(uint64_t *)&v94 = COERCE_UNSIGNED_INT64(v92 + v69.m128d_f64[0]) & v93;
    *(uint64_t *)&v95 = _mm_insert_epi16((__m128i)0LL, v81, 3).m128i_u64[0];
    v69.m128d_f64[0] = v69.m128d_f64[0] + *(double *)v85.m128i_i64 - v94 + *(double *)v86.m128i_i64;
    if ( (int)(v80 - 130944) > 0 )
    {
      v69.m128d_f64[0] = (v69.m128d_f64[0] + v94) * v91 + v95 * ((v69.m128d_f64[0] + v94) * v91);
      v97 = _mm_extract_epi16((__m128i)v69, 3) & 0x7FF0;
      v70 = 24;
      if ( v97 != 32752 )
      {
        v70 = 25;
        if ( v97 != 0 )
        {
          v102 = v69.m128d_f64[0];
          return v69.m128d_f64[0];
        }
      }
    }
    else
    {
      v69.m128d_f64[0] = v69.m128d_f64[0] * v91 + v94 * v91 + v95 * (v69.m128d_f64[0] * v91 + v94 * v91);
      v96 = _mm_extract_epi16((__m128i)v69, 3) & 0x7FF0;
      v70 = 24;
      if ( v96 != 32752 )
      {
        v70 = 25;
        if ( v96 != 0 )
        {
          v102 = v69.m128d_f64[0];
          return v69.m128d_f64[0];
        }
      }
    }
CALL_LIBM_ERROR:
    v102 = v69.m128d_f64[0];
    __libm_error_support((double *)&v101 + 4, &a9, &v102, v70);
    return v102;
  }
  if ( v100 < 0x80000000 )
  {
    a5.m128d_f64[0] = a8;
    if ( (((uint16_t)((_mm_extract_epi16((__m128i)a5, 3) & 0x7FF0) - 16368)
         ^ (uint16_t)_mm_extract_epi16(v29, 3))
        & 0x8000) == 0 )
    {
RET_INF_OF:
      v70 = 24;
      if ( v16 != 0 )
        v69.m128d_f64[0] = -INFINITY;
      else
        v69.m128d_f64[0] = INFINITY;
      goto CALL_LIBM_ERROR;
    }
    goto RET_ZERO_UF;
  }
  *(uint64_t *)&result = _mm_cvtsi32_si128(v16 | 0x1FF80).m128i_u64[0] << 45;
  return result;
}

// ------------------------------------------------------------
// 0x69F5FE __ffexpm1
// ------------------------------------------------------------
// 【L1】CRT pow 内部：expm1 分支（正 SP 偏移警告，Hex-Rays 计划内噪声）
// positive sp value has been detected, the output may be wrong!
int /*usercall*/ _ffexpm1@<eax>(int nArg1@<ebp>, long double fArg2@<st0>)
{
  bool v2; // c0
  char v3; // c2
  bool v4; // c3
  int result; // eax
  double v6; // st6
  int16_t v7; // fps
  bool v8; // c0
  char v9; // c2
  bool v10; // c3
  int16_t v11; // fps
  long double v12; // st6
  bool v13; // c0
  char v14; // c2
  bool v15; // c3
  int16_t v16; // fps
  long double v17; // st6
  bool v18; // c0
  char v19; // c2
  bool v20; // c3

  v6 = fabs(fArg2);
  v8 = *(double *)&tbyte_79BEBE < v6;
  v9 = 0;
  v10 = *(double *)&tbyte_79BEBE == v6;
  *(uint16_t *)(nArg1 - 160) = v7;
  if ( (*(uint8_t *)(nArg1 - 159) & 0x41) != 0 )
  {
    v2 = fArg2 < 0.0;
    v3 = 0;
    v4 = fArg2 == 0.0;
    *(uint16_t *)(nArg1 - 160) = v7;
    if ( (*(uint8_t *)(nArg1 - 159) & 1) != 0 )
    {
      *(uint8_t *)(nArg1 - 144) = 4;
      JUMPOUT(0x69F7B6);
    }
    return expbigret();
  }
  else
  {
    v12 = rint(fArg2);
    v13 = v12 < 0.0;
    v14 = 0;
    v15 = v12 == 0.0;
    *(uint16_t *)(nArg1 - 160) = v11;
    v17 = fArg2 - v12;
    v18 = v17 < 0.0;
    v19 = 0;
    v20 = v17 == 0.0;
    *(uint16_t *)(nArg1 - 160) = v16;
  }
  return result;
}



// ------------------------------------------------------------
// 0x69F641 _isintTOS
// ------------------------------------------------------------
// 【L1】CRT x87 isintTOS 判定
int /*usercall*/ isintTOS@<eax>(long double fArg1@<st0>)
{
  if ( rint(fArg1) != fArg1 )
    return notanint();
  if ( rint(fArg1 * dbl_79BED2) == fArg1 * dbl_79BED2 )
    return evenint();
  return isintTOSret();
}



// ------------------------------------------------------------
// 0x69F666 _isintTOSret
// ------------------------------------------------------------
// 【L1】CRT x87 isintTOS 返回桩
void isintTOSret()
{
  ;
}



// ------------------------------------------------------------
// 0x69F675 _usepowhlp
// ------------------------------------------------------------
// 【L1】CRT powhlp 调度入口（usepowhlp：2^x 快路径选择）
double /*usercall*/ usepowhlp@<st0>(int nArg1@<ebp>, double fArg2@<st1>, double fArg3@<st0>)
{
  int v4; // eax
  double result; // st7
  double *v6; // [esp+10h] [ebp-7Ch]
  double v7[15]; // [esp+14h] [ebp-78h] BYREF

  _ESI = v7;
  v6 = v7;
  __asm { fsave   byte ptr [esi+8] }
  v4 = _powhlp(fArg3, fArg2, (int)v7);
  __asm { frstor  byte ptr [esi+8] }
  result = v7[0];
  if ( v4 != 0 )
    *(uint8_t *)(nArg1 - 144) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x69F880 __startTwoArgErrorHandling
// ------------------------------------------------------------
// 【L1】CRT 双参数错误处理入口（_startTwoArgErrorHandling）
void _startTwoArgErrorHandling()
{
  JUMPOUT(0x69F8A0);
}



// ------------------------------------------------------------
// 0x69F897 __startOneArgErrorHandling
// ------------------------------------------------------------
// 【L1】CRT 单参数错误处理入口（_startOneArgErrorHandling）
double /*usercall*/ _startOneArgErrorHandling@<st0>(
        int a1@<eax>,
        int a2@<edx>,
        int a3@<ecx>,
        double a4@<st0>,
        int16_t a5,
        int a6,
        int a7,
        int a8)
{
  uint32_t v9[6]; // [esp+0h] [ebp-20h] BYREF
  double v10; // [esp+18h] [ebp-8h]

  v9[0] = a1;
  v10 = a4;
  v9[1] = a3;
  v9[2] = a7;
  v9[3] = a8;
  _87except(a2, (int)v9, &a5);
  return v10;
}



// ------------------------------------------------------------
// 0x69F8E0 __twoToTOS
// ------------------------------------------------------------
// 【L1】CRT x87 2^TOS（_twoToTOS）
long double /*usercall*/ _twoToTOS@<st0>(long double fArg1@<st0>)
{
  long double v1; // rt0

  v1 = rint(fArg1);
  return __FSCALE__(__F2XM1__(-(v1 - fArg1)) + 1.0, v1);
}



// ------------------------------------------------------------
// 0x69F8F5 __load_CW
// ------------------------------------------------------------
// 【L1】CRT x87 控制字加载（_load_CW）
void _load_CW()
{
  ;
}



// ------------------------------------------------------------
// 0x69F90C __convertTOStoQNaN
// ------------------------------------------------------------
// 【L1】CRT TOS→QNaN 转换（_convertTOStoQNaN）
double /*usercall*/ _convertTOStoQNaN@<st0>(int nArg1@<eax>, double result@<st0>)
{
  if ( (nArg1 & 0x80000) == 0 )
    return result + 1.0;
  return result;
}



// ------------------------------------------------------------
// 0x69F925 __fload_withFB
// ------------------------------------------------------------
// 【L1】CRT _fload_withFB：带 FB 状态的浮点加载
double /*fastcall*/ _fload_withFB(int nArg1, uint32_t *pArg2)
{
  double result; // st7

  if ( (pArg2[1] & 0x7FF00000) != 0x7FF00000 )
    return *(double *)pArg2;
  *(uint64_t *)&result = *(uint64_t *)pArg2 << 11;
  return result;
}



// ------------------------------------------------------------
// 0x69F968 __checkTOS_withFB
// ------------------------------------------------------------
// 【L1】CRT _checkTOS_withFB：TOS 合法性检查
int /*cdecl*/ _checkTOS_withFB(int nArg1, int nArg2)
{
  int result; // eax

  result = nArg2 & 0x7FF00000;
  if ( (nArg2 & 0x7FF00000) == 0x7FF00000 )
    return nArg2;
  return result;
}



// ------------------------------------------------------------
// 0x69F9B5 __check_overflow_exit
// ------------------------------------------------------------
// 【L1】CRT 溢出退出桩（_check_overflow_exit）
void _check_overflow_exit()
{
  JUMPOUT(0x69F9DD);
}



// ------------------------------------------------------------
// 0x69F9C9 __check_range_exit
// ------------------------------------------------------------
// 【L1】CRT 范围退出桩（反编译失败计划内替代）
// (decomp failed → 标准库替代) __check_range_exit
// [计划内] 本函数属 MSVC 静态 CRT，源码层以标准库调用替代，不做逐行还原。
// 替代: 范围检查退出桩 → 编译器运行时内置


// ------------------------------------------------------------
// 0x69FA6C __d_inttype
// ------------------------------------------------------------
// 【L1】CRT _d_inttype：double→整型分类
int /*cdecl*/ _d_inttype(double X)
{
  if ( (_fpclass(X) & 0x90) != 0 )
    return 0;
  _frnd(X);
  _frnd(X / 2.0);
  return 2;
}



// ------------------------------------------------------------
// 0x69FADA __powhlp
// ------------------------------------------------------------
// 【L1】CRT _powhlp：pow 核心助手（参数归一/特殊值分流，1.1KB）
int /*cdecl*/ _powhlp(double fArg1, double fArg2, double *pArg3)
{
  double fArg12; // st7
  int v4; // esi
  double *pArg32; // eax
  double v6; // st7
  int v7; // ecx

  fArg12 = fArg1;
  v4 = 0;
  if ( fArg1 < 0.0 )
    fArg12 = -fArg1;
  if ( HIDWORD(fArg2) == 2146435072 )
  {
    if ( LODWORD(fArg2) == 0 )
    {
      if ( fArg12 <= 1.0 )
      {
        pArg32 = pArg3;
        if ( fArg12 >= 1.0 )
          goto LABEL_7;
LABEL_18:
        v6 = 0.0;
        goto LABEL_31;
      }
LABEL_16:
      v6 = dbl_797C10;
      goto LABEL_30;
    }
  }
  else if ( fArg2 == -INFINITY )
  {
    if ( fArg12 <= 1.0 )
    {
      pArg32 = pArg3;
      if ( fArg12 < 1.0 )
      {
        v6 = dbl_797C10;
        goto LABEL_31;
      }
LABEL_7:
      v6 = dbl_797C18;
      v4 = 1;
LABEL_31:
      *pArg32 = v6;
      return v4;
    }
    v6 = 0.0;
LABEL_30:
    pArg32 = pArg3;
    goto LABEL_31;
  }
  if ( HIDWORD(fArg1) == 2146435072 )
  {
    if ( LODWORD(fArg1) == 0 )
    {
      if ( fArg2 <= 0.0 )
      {
        pArg32 = pArg3;
        if ( fArg2 >= 0.0 )
        {
          v6 = 1.0;
          goto LABEL_31;
        }
        goto LABEL_18;
      }
      goto LABEL_16;
    }
  }
  else if ( fArg1 == -INFINITY )
  {
    v7 = _d_inttype(fArg2);
    if ( fArg2 <= 0.0 )
    {
      if ( fArg2 >= 0.0 )
      {
        v6 = 1.0;
      }
      else if ( v7 == 1 )
      {
        v6 = dbl_797C30;
      }
      else
      {
        v6 = 0.0;
      }
    }
    else
    {
      v6 = dbl_797C10;
      if ( v7 == 1 )
        v6 = -dbl_797C10;
    }
    goto LABEL_30;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x69FC3C __floor_default
// ------------------------------------------------------------
// 【L1】CRT _floor_default：floor 通用路径
double /*cdecl*/ _floor_default(double pArg1)
{
  int v1; // ebx
  int v2; // eax

  v1 = _ctrlfp(dword_79BF30, 0xFFFF);
  if ( (HIWORD(pArg1) & 0x7FF0) == 0x7FF0 )
  {
    v2 = _sptype(LODWORD(pArg1), HIDWORD(pArg1));
    if ( v2 <= 0 )
    {
LABEL_7:
      _except1(8u, 11, pArg1, pArg1 + 1.0, v1);
      return pArg1;
    }
    if ( v2 > 2 )
    {
      if ( v2 == 3 )
      {
        _handle_qnan1(11, pArg1, v1);
        return pArg1;
      }
      goto LABEL_7;
    }
  }
  else
  {
    _frnd(pArg1);
  }
  _ctrlfp(v1, 0xFFFF);
  return pArg1;
}



// ------------------------------------------------------------
// 0x69FD10 unknown_libname_16
// ------------------------------------------------------------
// 【L1】CRT 运行时未知桩（Microsoft VisualC 2-14/net runtime 签名）
// Microsoft VisualC 2-14/net runtime
double /*cdecl*/ unknown_libname_16(_TBYTE nArg1, _TBYTE nArg2)
{
  double v2; // st7
  double v3; // st6
  unsigned int v4; // eax

  v2 = *(double *)&nArg2;
  v3 = *(double *)&nArg1;
  while ( !__CFADD__(DWORD1(nArg1), DWORD1(nArg1)) )
  {
    if ( *(uint64_t *)&nArg1 == 0 || (HIWORD(nArg1) & 0x7FFF) != 0 )
      return v2 / v3;
    if ( (HIWORD(nArg2) & 0x7FFF) != 0 )
    {
      if ( (HIWORD(nArg2) & 0x7FFF) == 0x7FFF || !__CFADD__(DWORD1(nArg2), DWORD1(nArg2)) )
        return v2 / v3;
    }
    else if ( __CFADD__(DWORD1(nArg2), DWORD1(nArg2)) )
    {
      return v2 / v3;
    }
    *(double *)&nArg1 = v3 * flt_79BF58;
    v2 = *(double *)&nArg2;
  }
  v4 = (2 * DWORD1(nArg1)) ^ 0xE000000;
  if ( (v4 & 0xE000000) != 0 )
    return v2 / v3;
  if ( byte_79BF40[v4 >> 28] == 0 )
    return v2 / v3;
  if ( (HIWORD(nArg1) & 0x7FFF) == 0 || (HIWORD(nArg1) & 0x7FFF) == 0x7FFF )
    return v2 / v3;
  if ( (HIWORD(nArg2) & 0x7FFF) == 1 )
    return v2 * flt_79BF54 / (v3 * flt_79BF54);
  else
    return v2 * flt_79BF50 / (v3 * flt_79BF50);
}



// ------------------------------------------------------------
// 0x69FE27 unknown_libname_17
// ------------------------------------------------------------
// 【L1】CRT 运行时未知桩（同上）\
// Microsoft VisualC 2-14/net runtime
// positive sp value has been detected, the output may be wrong!
int /*usercall*/ unknown_libname_17@<eax>(char pszArg1@<al>)
{
  int result; // eax
  _TBYTE v2; // [esp-2Ch] [ebp-58h]
  _TBYTE v3; // [esp-20h] [ebp-4Ch]
  int v11; // [esp-14h] [ebp-40h]
  int v12; // [esp-10h] [ebp-3Ch]
  _TBYTE v20; // [esp+0h] [ebp-2Ch]
  _TBYTE v21; // [esp+Ch] [ebp-20h]
  int v29; // [esp+18h] [ebp-14h]
  int v30; // [esp+1Ch] [ebp-10h]

  result = pszArg1 & 0x3F;
  switch ( result )
  {
    case 0:
      __asm { fdiv    st, st; jumptable 0069FE2D case 0 }
      return result;
    case 1:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_4;
    case 2:
LABEL_4:
      __asm { fdivr   st, st; jumptable 0069FE2D case 2 }
      return result;
    case 3:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_6;
    case 4:
LABEL_6:
      __asm { fdiv    st, st; jumptable 0069FE2D case 4 }
      return result;
    case 5:
      __asm { fdivp   st, st; jumptable 0069FE2D case 5 }
      return result;
    case 6:
      __asm { fdivr   st, st; jumptable 0069FE2D case 6 }
      return result;
    case 7:
      __asm { fdivrp  st, st; jumptable 0069FE2D case 7 }
      return result;
    case 8:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 8
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fld     [esp+2Ch+var_C]
        fxch    st(1)
      }
      return result;
    case 9:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_12;
    case 10:
LABEL_12:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0069FE2D case 10
        fstp    [esp+arg_8]; _TBYTE
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fld     [esp+arg_8]
        fxch    st(1)
      }
      return result;
    case 11:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_14;
    case 12:
LABEL_14:
      __asm
      {
        fxch    st(1); jumptable 0069FE2D case 12
        fstp    [esp+arg_8]; _TBYTE
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm { fld     [esp+arg_1C] }
      return result;
    case 13:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0069FE2D case 13
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      return unknown_libname_16(v2, v3, v11, v12);
    case 14:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 14
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fld     [esp+2Ch+var_20] }
      return result;
    case 15:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 15
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      return unknown_libname_16(v2, v3, v11, v12);
    case 16:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 16
        fxch    st(1)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(1)
        fld     [esp+2Ch+var_C]
        fxch    st(2)
      }
      return result;
    case 17:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_20;
    case 18:
LABEL_20:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0069FE2D case 18
        fxch    st(1)
        fstp    [esp+arg_8]; _TBYTE
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(1)
        fld     [esp+arg_8]
        fxch    st(2)
      }
      return result;
    case 19:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_22;
    case 20:
LABEL_22:
      __asm
      {
        fxch    st(2); jumptable 0069FE2D case 20
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(1)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(1)
        fld     [esp+arg_1C]
      }
      return result;
    case 21:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0069FE2D case 21
        fxch    st(1)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(1) }
      return result;
    case 22:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 22
        fxch    st(1)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(1)
        fld     [esp+2Ch+var_20]
      }
      return result;
    case 23:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 23
        fxch    st(1)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(1) }
      return result;
    case 24:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 24
        fxch    st(2)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(2)
        fld     [esp+2Ch+var_C]
        fxch    st(3)
      }
      return result;
    case 25:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_28;
    case 26:
LABEL_28:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0069FE2D case 26
        fxch    st(2)
        fstp    [esp+arg_8]; _TBYTE
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(2)
        fld     [esp+arg_8]
        fxch    st(3)
      }
      return result;
    case 27:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_30;
    case 28:
LABEL_30:
      __asm
      {
        fxch    st(3); jumptable 0069FE2D case 28
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(2)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(2)
        fld     [esp+arg_1C]
      }
      return result;
    case 29:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0069FE2D case 29
        fxch    st(2)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(2) }
      return result;
    case 30:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 30
        fxch    st(2)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(2)
        fld     [esp+2Ch+var_20]
      }
      return result;
    case 31:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 31
        fxch    st(2)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(2) }
      return result;
    case 32:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 32
        fxch    st(3)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(3)
        fld     [esp+2Ch+var_C]
        fxch    st(4)
      }
      return result;
    case 33:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_36;
    case 34:
LABEL_36:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0069FE2D case 34
        fxch    st(3)
        fstp    [esp+arg_8]; _TBYTE
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(3)
        fld     [esp+arg_8]
        fxch    st(4)
      }
      return result;
    case 35:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_38;
    case 36:
LABEL_38:
      __asm
      {
        fxch    st(4); jumptable 0069FE2D case 36
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(3)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(3)
        fld     [esp+arg_1C]
      }
      return result;
    case 37:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0069FE2D case 37
        fxch    st(3)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(3) }
      return result;
    case 38:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 38
        fxch    st(3)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(3)
        fld     [esp+2Ch+var_20]
      }
      return result;
    case 39:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 39
        fxch    st(3)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(3) }
      return result;
    case 40:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 40
        fxch    st(4)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(4)
        fld     [esp+2Ch+var_C]
        fxch    st(5)
      }
      return result;
    case 41:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_44;
    case 42:
LABEL_44:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0069FE2D case 42
        fxch    st(4)
        fstp    [esp+arg_8]; _TBYTE
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(4)
        fld     [esp+arg_8]
        fxch    st(5)
      }
      return result;
    case 43:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_46;
    case 44:
LABEL_46:
      __asm
      {
        fxch    st(5); jumptable 0069FE2D case 44
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(4)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(4)
        fld     [esp+arg_1C]
      }
      return result;
    case 45:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0069FE2D case 45
        fxch    st(4)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(4) }
      return result;
    case 46:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 46
        fxch    st(4)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(4)
        fld     [esp+2Ch+var_20]
      }
      return result;
    case 47:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 47
        fxch    st(4)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(4) }
      return result;
    case 48:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 48
        fxch    st(5)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(5)
        fld     [esp+2Ch+var_C]
        fxch    st(6)
      }
      return result;
    case 49:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_52;
    case 50:
LABEL_52:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0069FE2D case 50
        fxch    st(5)
        fstp    [esp+arg_8]; _TBYTE
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(5)
        fld     [esp+arg_8]
        fxch    st(6)
      }
      return result;
    case 51:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_54;
    case 52:
LABEL_54:
      __asm
      {
        fxch    st(6); jumptable 0069FE2D case 52
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(5)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(5)
        fld     [esp+arg_1C]
      }
      return result;
    case 53:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0069FE2D case 53
        fxch    st(5)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(5) }
      return result;
    case 54:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 54
        fxch    st(5)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(5)
        fld     [esp+2Ch+var_20]
      }
      return result;
    case 55:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 55
        fxch    st(5)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(5) }
      return result;
    case 56:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 56
        fxch    st(6)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(6)
        fld     [esp+2Ch+var_C]
        fxch    st(7)
      }
      return result;
    case 57:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_60;
    case 58:
LABEL_60:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0069FE2D case 58
        fxch    st(6)
        fstp    [esp+arg_8]; _TBYTE
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(6)
        fld     [esp+arg_8]
        fxch    st(7)
      }
      return result;
    case 59:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_62;
    case 60:
LABEL_62:
      __asm
      {
        fxch    st(7); jumptable 0069FE2D case 60
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(6)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      result = unknown_libname_16(v20, v21, v29, v30);
      __asm
      {
        fxch    st(6)
        fld     [esp+arg_1C]
      }
      break;
    case 61:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0069FE2D case 61
        fxch    st(6)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(6) }
      break;
    case 62:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 62
        fxch    st(6)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm
      {
        fxch    st(6)
        fld     [esp+2Ch+var_20]
      }
      break;
    case 63:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0069FE2D case 63
        fxch    st(6)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      result = unknown_libname_16(v2, v3, v11, v12);
      __asm { fxch    st(6) }
      break;
  }
  return result;
}
