// ============================================================
// 【40JP逆向源代码工程】src/nengine/zlib_inflate.cpp
// 模块: 0x65 区 —— Neople 演出代码 + zlib 1.2.3 静态链接 + 内嵌 OLE 浏览器 + UDP 中继客户端
// 来源: work/dump_tail_a.txt 系  区块: 0x650000-0x660000
// 层级: L2 转写层（Hex-Rays 逐字对应）+【L1 精修层】
//
// 【L1 精修内容】（注释级，函数体与 L2 逐字一致，零改动）:
//   ① 文件头重写 + 13 个 SECTION 分区横幅（13 段生效）+ SECTION 索引表
//   ② 35 个关键函数【解读】注释块（inflate 全家、OLE 浏览器、QUAKE_WAVE、UDP 中继）
//   ③ 2 个函数标记行追加 [串: "..."] 字符串证据尾注（逐函数覆盖）
//
// ★ Neople 自研 vs 第三方 对照（本区判定）:
//   [zlib 1.2.3 标准 —— 版本串 "1.2.3"（0x652E00），0x652DE0-0x655A40]
//     0x652E00 uncompress / 0x652EB0 inflateReset / 0x652F10 inflateInit2_ /
//     0x653120 inflate(1477 行状态机) / 0x6548D8 inflate_fast（★MMX 定制版，官方 1.2.3 无 SIMD）
//     / 0x654F70 inflate_table / 0x655460+0x6556B0 crc32 / 0x654750 inflateEnd /
//     0x6547A0+0x6547C0 zcalloc/zcfree
//     → 上游消费者: gfx_texture.cpp 0x4116A0 族（IMG 图像块解压）
//   [Neople 自研]
//     0x650030-0x6527C0 演出代码（.ptl 粒子加载 / QUAKE_WAVE / SM_GHOSTSTEP / .ani 应用 /
//       效果对象状态机）、0x655A90 计时调试、0x6560D0-0x656D70 容器与调度、
//       0x657120-0x6572C0 UDP 中继客户端
//   [内嵌 OLE 浏览器 —— 0x6527F0-0x652DE0]
//     "Browser Example" 宿主窗口类（Neople 工程残留命名）+ "NEOPLE_WEB" 标题 +
//     OleCreate WebBrowser 控件 + Navigate + "NAVIGATION START/END" 调试标记
//     （docs/04 所记“寻路”实为此网页导航调试，非寻路算法；flex yy_create_buffer
//      残留在 src/platform/missing_tail.cpp，不在本文件）
//   [编译器注入 —— 非游戏逻辑]
//     0x656810/0x656820/0x656830 = MSVC ConcRT ContextBase::SweepUnstructured ×3
//
// 函数数: 153（L1 覆盖 153：解读 35 / 串证据 2 / 分区 13）
// ============================================================

#include "../../common/arad_types.h"
// ============================================================
// SECTION 索引（按 VA 升序）
// ============================================================
//   0x650030 — Neople 游戏演出代码：技能/效果对象状态机（虚调用密集，与 0x42-0x46 战斗区衔接）
//   0x650C30 — 粒子特效加载（Common/CommonEffect/Particle/*.ptl）
//   0x6510A0 — 剑魂震波音效族（QUAKE_WAVE_READY_LOOP / QUAKE_WAVE_LOOP / SM_GHOSTSTEP 幽灵步克隆）
//   0x651B60 — 状态解除/斗气/瞄准要害演出（RemoveActiveStatus.ptl / Provocationed.ani / AimedVitalPoint.ani）
//   0x6525A0 — 窗口/客户端小工具（GetClientRect 等）
//   0x6527F0 — ★★ 内嵌 OLE 浏览器（NEOPLE_WEB: OleCreate WebBrowser 控件 / Navigate / NAVIGATION START/END 调试标记）
//   0x652DE0 — ★★★ zlib 1.2.3 静态链接（uncompress / inflateInit2_ / inflate / inflate_table / inflate_fast(MMX) / crc32 / zalloc/zfree；版本串 "1.2.3"）
//   0x655A90 — Neople 调试打印（enduranceTime/waitTime/elapsedTime 计时调试 → 0x40BE20 控制台）
//   0x6560D0 — 观察者/容器族（vector 工具 + 对象分配，供上层效果系统）
//   0x656810 — MSVC ConcRT 运行时桩（ContextBase::SweepUnstructured ×3 —— 编译器注入，非游戏逻辑）
//   0x656840 — 定时器/调度容器（GetTickCount / timeGetTime 节流链表）
//   0x656D70 — 链表/网络对象工具（通用双向链表清空 0x6569D0 全引擎复用）
//   0x657120 — ★ UDP 中继客户端（startup/connected to Relayserver/Disconnected —— socket/htons/inet_addr）
// ============================================================

// ============================================================
// SECTION 0x650030 — Neople 游戏演出代码：技能/效果对象状态机（虚调用密集，与 0x42-0x46 战斗区衔接）
// ============================================================
// ------------------------------------------------------------
// 0x650030 sub_650030
// ------------------------------------------------------------
int /*thiscall*/ sub_650030(int this)
{
  int fld_4; // ecx
  int result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 88) = -1;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 104) = 1;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_4 + 776))(fld_4, 3);
  if ( (uint8_t)result != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 556))(*(uint32_t *)(this + 4), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 768))(
      *(uint32_t *)(this + 4),
      3,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 556))(*(uint32_t *)(this + 4), 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6500A0 sub_6500A0
// ------------------------------------------------------------
char /*thiscall*/ sub_6500A0(uint32_t *this, char pszArg2)
{
  char result; // al
  int fld_e1; // esi

  result = pszArg2;
  if ( pszArg2 == 0 )
  {
    fld_e1 = *(this + 1);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)fld_e1 + 272))(fld_e1, 0, 0);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)fld_e1 + 612))(fld_e1, 0, 0);
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1 + 820))(fld_e1, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6500E0 sub_6500E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6500E0(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = -1;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650100 sub_650100
// ------------------------------------------------------------
uint32_t */*usercall*/ sub_650100@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  uint32_t *result; // eax
  int *v5; // edi
  int v6; // ebx
  int v7; // ebx
  int *v8; // ecx
  int v9; // eax
  int v10; // eax
  int pObj3; // ecx
  int v12; // ecx
  int v13; // eax
  int pObj2; // ecx
  int v15; // eax
  char v16; // bl
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int pObj; // [esp+4h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 840))(*(uint32_t *)(pArg1 + 80));
  if ( result == (uint32_t *)24 )
  {
    v5 = *(int **)(pArg1 + 4);
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 840))(v5);
    if ( result == (uint32_t *)9 )
    {
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 200))(*(uint32_t *)(pArg1 + 80));
      v6 = (int)result;
      if ( result != nullptr )
      {
        if ( (*(int (/*thiscall*/ **)(int *, int, int))(*v5 + 236))(v5, nArg2, nArg3) == 1 )
          (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*v5 + 228))(v5, 0, -1, 0);
        sub_4938F0(v6);
        v7 = *(uint32_t *)(v6 + 148);
        if ( v7 != *(uint32_t *)(pArg1 + 84) )
        {
          v8 = *(int **)(pArg1 + 80);
          if ( v7 >= 9 )
          {
            v9 = *v8;
            if ( v7 == 9 )
            {
              v10 = (*(int (**)(void))(v9 + 152))();
              pObj3 = *(uint32_t *)(pArg1 + 4);
              *(uint32_t *)(pArg1 + 88) = v10 != 0 ? 37 : -37;
              *(uint32_t *)(pArg1 + 92) = -1;
              if ( 65 - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 192))(pObj3) <= 0 )
                v12 = 0;
              else
                v12 = 65 - (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 192))(*(uint32_t *)(pArg1 + 4));
            }
            else
            {
              v13 = (*(int (**)(void))(v9 + 152))();
              pObj2 = *(uint32_t *)(pArg1 + 4);
              *(uint32_t *)(pArg1 + 88) = v13 != 0 ? 58 : -58;
              *(uint32_t *)(pArg1 + 92) = -1;
              if ( 113 - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 192))(pObj2) <= 20 )
                v12 = 20;
              else
                v12 = 113 - (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 192))(*(uint32_t *)(pArg1 + 4));
            }
            *(uint32_t *)(pArg1 + 96) = v12;
          }
          else
          {
            *(uint32_t *)(pArg1 + 88) = (*(int (/*thiscall*/ **)(int *))(*v8 + 152))(v8) != 0 ? 80 : -80;
            *(uint32_t *)(pArg1 + 92) = -1;
            *(uint32_t *)(pArg1 + 96) = 0;
          }
          *(uint32_t *)(pArg1 + 84) = v7;
        }
        v15 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 152))(*(uint32_t *)(pArg1 + 80));
        v16 = sub_432E50(v15);
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v5 + 60))(v5) + 52) = v16;
        v17 = *v5;
        pObj = *(uint32_t *)(pArg1 + 80);
        v18 = (*(int (**)(void))(*(uint32_t *)pObj + 128))();
        v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 124))(pObj, *(uint32_t *)(pArg1 + 96) + v18);
        v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, *(uint32_t *)(pArg1 + 92) + v19);
        (*(void (/*thiscall*/ **)(int *, int))(v17 + 112))(v5, *(uint32_t *)(pArg1 + 88) + v20);
        (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 612))(v5, 1, 1);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*v5 + 820))(v5, 0);
        result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
        if ( result != nullptr )
        {
          v21 = (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
          return sub_4938F0(v21);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6502E0 sub_6502E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6502E0(uint32_t *this)
{
  int fld_e1; // ecx
  int result; // eax

  fld_e1 = *(this + 1);
  *(this + 21) = -1;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1 + 776))(fld_e1, 3);
  if ( (uint8_t)result != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 556))(*(this + 1), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 768))(*(this + 1), 3, 0, 0);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 556))(*(this + 1), 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x650340 sub_650340
// ------------------------------------------------------------
int /*thiscall*/ sub_650340(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = -1;
  *(this + 22) = -1;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650360 sub_650360
// ------------------------------------------------------------
uint32_t */*usercall*/ sub_650360@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>)
{
  uint32_t *result; // eax
  int *v5; // esi
  uint32_t *v6; // ebx
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  char v10; // bl
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v18; // [esp+4h] [ebp-4h]
  int pObj; // [esp+4h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 840))(*(uint32_t *)(pArg1 + 80));
  if ( result == (uint32_t *)10 )
  {
    v5 = *(int **)(pArg1 + 4);
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 840))(v5);
    if ( result == (uint32_t *)9 )
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 236))(v5) == 1 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*v5 + 228))(v5, 0, -1, 0);
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 200))(*(uint32_t *)(pArg1 + 80));
      v6 = result;
      if ( result != nullptr )
      {
        sub_4938F0((int)result);
        v18 = v6[37];
        v7 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(pArg1 + 80) + 1288))(*(uint32_t *)(pArg1 + 80), nArg2, nArg3);
        if ( v7 != *(uint32_t *)(pArg1 + 84) || v18 != *(uint32_t *)(pArg1 + 88) )
        {
          if ( v7 != 0 )
          {
            *(uint32_t *)(pArg1 + 92) = 0;
            *(uint32_t *)(pArg1 + 96) = 1;
            if ( 93 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) / 2 <= 40 )
              v8 = 40;
            else
              v8 = 93 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) / 2;
            *(uint32_t *)(pArg1 + 100) = v8;
          }
          else
          {
            *(uint32_t *)(pArg1 + 92) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 152))(*(uint32_t *)(pArg1 + 80)) != 0
                                 ? 60
                                 : -60;
            *(uint32_t *)(pArg1 + 96) = -1;
            if ( 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) <= 0 )
              *(uint32_t *)(pArg1 + 100) = 0;
            else
              *(uint32_t *)(pArg1 + 100) = 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5);
          }
          *(uint32_t *)(pArg1 + 84) = v7;
          *(uint32_t *)(pArg1 + 88) = v18;
        }
        v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 152))(*(uint32_t *)(pArg1 + 80));
        v10 = sub_432E50(v9);
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v5 + 60))(v5) + 52) = v10;
        v11 = *v5;
        pObj = *(uint32_t *)(pArg1 + 80);
        v12 = (*(int (**)(void))(*(uint32_t *)pObj + 128))();
        v13 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 124))(pObj, *(uint32_t *)(pArg1 + 100) + v12);
        v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, *(uint32_t *)(pArg1 + 96) + v13);
        (*(void (/*thiscall*/ **)(int *, int))(v11 + 112))(v5, *(uint32_t *)(pArg1 + 92) + v14);
        (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 612))(v5, 1, 1);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*v5 + 820))(v5, 0);
        result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
        if ( result != nullptr )
        {
          v15 = (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
          return sub_4938F0(v15);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x650540 sub_650540
// ------------------------------------------------------------
int /*thiscall*/ sub_650540(int this)
{
  *(uint32_t *)(this + 80) = 17;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint8_t *)(this + 92) = 0;
  *(uint8_t *)(this + 93) = 1;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650560 sub_650560
// ------------------------------------------------------------
int /*thiscall*/ sub_650560(void *this, int nArg2, float fArg3, int nArg4, int nArg5, int nArg6, int nArg7)
{
  return (*(int (/*fastcall*/ **)(void *, uint32_t, int, uint32_t, int, int, int, int))(*(uint32_t *)this + 120))(
           this,
           (uint64_t)fArg3 >> 32,
           nArg2,
           (uint64_t)fArg3,
           nArg4,
           nArg5,
           nArg6,
           nArg7);
}



// ------------------------------------------------------------
// 0x6505A0 sub_6505A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6505A0(uint32_t *this, int pArg2)
{
  int result; // eax
  uint32_t *v3; // edx

  result = 0;
  v3 = (uint32_t *)(pArg2 + 24);
  while ( *v3 != 17 )
  {
    ++result;
    ++v3;
    if ( result >= 3 )
    {
      result = 2;
      break;
    }
  }
  *(uint32_t *)(pArg2 + 4 * result + 24) = *(this + 20);
  *(uint32_t *)(pArg2 + 4 * result + 36) = *(this + 21);
  *(uint32_t *)(pArg2 + 4 * result + 48) = *(this + 22);
  return result;
}



// ------------------------------------------------------------
// 0x6505F0 sub_6505F0
// ------------------------------------------------------------
char /*thiscall*/ sub_6505F0(uint32_t *this, int pArg2)
{
  char result; // al
  int pThis_2; // eax
  uint8_t v4; // al

  result = *(uint8_t *)(pArg2 + 176);
  if ( result == 0 && *(this + 20) == 2 )
  {
    pThis_2 = sub_699000((int)(this + 2));
    v4 = sub_42B420(50, 170, pThis_2, 500);
    return sub_491690(1, 0, 1, -4449923, (v4 << 24) | 0xFFFFFF, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x650650 sub_650650
// ------------------------------------------------------------
void /*thiscall*/ sub_650650(int this)
{
  int pThis; // ebx
  int v2; // esi
  int v3; // esi
  int pObj; // ecx
  int v5; // eax
  uint32_t *v6; // edx
  int v7; // ecx
  uint32_t *v8; // eax
  uint32_t *v9; // edi
  int v10; // ecx
  unsigned int v11; // edx
  uint32_t *v12; // eax
  int v13; // [esp+Ch] [ebp-18h]
  int v14; // [esp+10h] [ebp-14h]
  uint32_t *i; // [esp+14h] [ebp-10h]
  int v17; // [esp+1Ch] [ebp-8h]
  char v18; // [esp+23h] [ebp-1h]

  pThis = this;
  v18 = 0;
  if ( *(uint32_t *)(this + 96) != (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4)) )
  {
    v18 = 1;
    *(uint32_t *)(pThis + 96) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pThis + 4) + 200))(*(uint32_t *)(pThis + 4));
  }
  v2 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pThis + 4) + 792))(*(uint32_t *)(pThis + 4), 8);
  if ( v2 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pThis + 4) + 40))(*(uint32_t *)(pThis + 4), 273) != 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pThis + 4) + 1084))(*(uint32_t *)(pThis + 4), 8);
  }
  if ( *(uint32_t *)(pThis + 100) == v2 )
  {
    if ( v18 == 0 )
      return;
  }
  else
  {
    *(uint32_t *)(pThis + 100) = v2;
  }
  v3 = pThis + 104;
  if ( *(uint32_t *)(pThis + 108) != 0 )
    j__free(*(void **)(pThis + 108));
  *(uint32_t *)(pThis + 108) = 0;
  *(uint32_t *)(pThis + 112) = 0;
  *(uint32_t *)(pThis + 116) = 0;
  if ( *(uint32_t *)(pThis + 96) != 0 )
  {
    pObj = *(uint32_t *)(pThis + 100);
    if ( pObj != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 248))(pObj);
      v6 = *(uint32_t **)(v5 + 4);
      v13 = v5;
      for ( i = v6; v6 != *(uint32_t **)(v13 + 8); i = v6 )
      {
        v7 = *(uint32_t *)(pThis + 96) + 200;
        v14 = *v6;
        v8 = *(uint32_t **)(*(uint32_t *)(pThis + 96) + 204);
        v9 = (uint32_t *)*v8;
        v17 = v7;
        if ( (uint32_t *)*v8 != v8 )
        {
          do
          {
            if ( v9[2] == v14 )
            {
              v10 = *(uint32_t *)(v3 + 4);
              if ( v10 != 0 )
                v11 = (*(uint32_t *)(v3 + 8) - v10) >> 2;
              else
                v11 = 0;
              if ( v10 != 0 && v11 < (*(uint32_t *)(v3 + 12) - v10) >> 2 )
              {
                v12 = *(uint32_t **)(v3 + 8);
                *v12 = v9[3];
                *(uint32_t *)(v3 + 8) = v12 + 1;
              }
              else
              {
                sub_42AC90(*(void **)(v3 + 8), 1, (int)(v9 + 3));
              }
              v7 = v17;
              pThis = this;
            }
            v9 = (uint32_t *)*v9;
          }
          while ( v9 != *(uint32_t **)(v7 + 4) );
          v6 = i;
        }
        v6 += 31;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x6507C0 sub_6507C0
// ------------------------------------------------------------
void /*thiscall*/ sub_6507C0(int this, char pszArg2, int nArg3, int nArg4, int nArg5)
{
  int *i; // esi

  if ( pszArg2 == 0 && *(uint8_t *)(this + 93) != 0 )
  {
    sub_650650(this);
    for ( i = *(int **)(this + 108); i != *(int **)(this + 112); ++i )
      sub_6505F0((uint32_t *)this, *i);
  }
}



// ------------------------------------------------------------
// 0x650800 sub_650800
// ------------------------------------------------------------
int /*thiscall*/ sub_650800(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 23) = 0;
  *(this + 22) = 0;
  *(this + 24) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650820 sub_650820
// ------------------------------------------------------------
void /*thiscall*/ sub_650820(uint32_t *this, int pArg2)
{
  int fld_e1; // edi
  int fld_e20; // ebx
  int v5; // eax
  int v6; // edx
  double fld_e202; // st7
  int v8; // eax
  int v9; // edx
  float fld_e21; // [esp+0h] [ebp-28h]
  float fld_e23; // [esp+0h] [ebp-28h]
  float fld_e22; // [esp+4h] [ebp-24h]
  float fld_e24; // [esp+4h] [ebp-24h]
  float v14; // [esp+20h] [ebp-8h]
  float v15; // [esp+24h] [ebp-4h]

  fld_e1 = *(this + 1);
  v14 = (double)(*(int (/*fastcall*/ **)(int))(*(uint32_t *)fld_e1 + 736))(fld_e1) * 100.0;
  v15 = v14 / (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 740))(fld_e1);
  if ( (double)(int)*(this + 20) >= v15 )
  {
    fld_e22 = (float)(int)*(this + 22);
    fld_e21 = (float)(int)*(this + 21);
    fld_e20 = (uint64_t)sub_4049C0(
                             fld_e21,
                             fld_e22,
                             (uint64_t)(((double)(int)*(this + 20) - v15) * 1000.0),
                             (uint64_t)(1000.0 * (double)(int)*(this + 20)));
    v5 = sub_41A5E0(pArg2 + 60);
    sub_41A590(pArg2 + 60, v6, fld_e20 + v5);
    fld_e24 = (float)(int)*(this + 24);
    fld_e23 = (float)(int)*(this + 23);
    fld_e202 = sub_4049C0(
           fld_e23,
           fld_e24,
           (uint64_t)(((double)(int)*(this + 20) - v15) * 1000.0),
           (uint64_t)(1000.0 * (double)(int)*(this + 20)));
    v8 = sub_41A5E0(pArg2 + 466);
    sub_41A590(pArg2 + 466, v9, (uint64_t)fld_e202 + v8);
  }
}



// ------------------------------------------------------------
// 0x650950 sub_650950
// ------------------------------------------------------------
int /*thiscall*/ sub_650950(uint32_t *this, int nArg2)
{
  uint32_t *v3; // eax
  int result; // eax

  v3 = (uint32_t *)sub_47E720(0, 19);
  *(this + 20) = sub_47E9D0(v3, 0);
  *(this + 21) = sub_47EF20(0, nArg2, -1, -1, 11);
  *(this + 22) = sub_47EF20(1, nArg2, -1, -1, 11);
  *(this + 23) = sub_47EF20(2, nArg2, -1, -1, 11);
  result = sub_47EF20(3, nArg2, -1, -1, 11);
  *(this + 24) = result;
  return result;
}



// ------------------------------------------------------------
// 0x6509D0 sub_6509D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6509D0(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6509F0 sub_6509F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6509F0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e27)(uint32_t, int); // ecx
  int result; // eax

  fld_e27 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 27);
  if ( fld_e27 != nullptr )
    result = (**fld_e27)(fld_e27, 1);
  *(this + 27) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x650A10 sub_650A10
// ------------------------------------------------------------
int /*thiscall*/ sub_650A10(int this, int pArg2)
{
  int v4; // eax
  int v5; // edx
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // edx
  int v10; // ebx
  unsigned int v11; // edi
  int result; // eax
  int v13; // eax
  int fld_50; // [esp+Ch] [ebp-4h]
  float fld_64; // [esp+Ch] [ebp-4h]
  float fld_68; // [esp+Ch] [ebp-4h]
  float fld_58; // [esp+Ch] [ebp-4h]
  float fld_5C; // [esp+Ch] [ebp-4h]
  int v19; // [esp+18h] [ebp+8h]
  int fld_54; // [esp+18h] [ebp+8h]
  int v21; // [esp+18h] [ebp+8h]
  int v22; // [esp+18h] [ebp+8h]
  int v23; // [esp+18h] [ebp+8h]
  int fld_60; // [esp+18h] [ebp+8h]

  fld_50 = *(uint32_t *)(this + 80);
  v4 = sub_41A5E0(pArg2 + 60);
  sub_41A590(pArg2 + 60, v5, fld_50 + v4);
  fld_64 = *(float *)(this + 100);
  *(float *)&v19 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1054)) + fld_64;
  sub_41A590(pArg2 + 1054, v6, v19);
  fld_54 = *(uint32_t *)(this + 84);
  v7 = sub_41A5E0(pArg2 + 116);
  sub_41A590(pArg2 + 116, fld_54, fld_54 + v7);
  fld_68 = *(float *)(this + 104);
  *(float *)&v21 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1110)) + fld_68;
  sub_41A590(pArg2 + 1110, v8, v21);
  fld_58 = (double)*(int *)(this + 88) * 0.001;
  *(float *)&v22 = COERCE_FLOAT(sub_41A5E0(pArg2 + 830)) + fld_58;
  sub_41A590(pArg2 + 830, v22, v22);
  fld_5C = (double)*(int *)(this + 92) * 0.001;
  *(float *)&v23 = COERCE_FLOAT(sub_41A5E0(pArg2 + 858)) + fld_5C;
  sub_41A590(pArg2 + 858, v9, v23);
  v10 = 0;
  v11 = pArg2 + 284;
  do
  {
    result = sub_497040(v10);
    if ( result != 17 )
    {
      fld_60 = *(uint32_t *)(this + 96);
      v13 = sub_41A5E0(v11);
      result = sub_41A590(v11, fld_60, fld_60 + v13);
    }
    ++v10;
    v11 += 14;
  }
  while ( v10 < 16 );
  return result;
}



// ------------------------------------------------------------
// 0x650B50 sub_650B50
// ------------------------------------------------------------
int /*thiscall*/ sub_650B50(int this, int nArg2)
{
  int result; // eax

  sub_47E720(0, 40);
  *(uint32_t *)(this + 44) = sub_47EF20(0, nArg2, -1, -1, 11);
  *(uint32_t *)(this + 80) = sub_47EF20(1, nArg2, -1, -1, 11);
  *(float *)(this + 100) = (double)(int)sub_47EF20(2, nArg2, -1, -1, 11) * -0.0099999998;
  *(float *)(this + 104) = (double)(int)sub_47EF20(3, nArg2, -1, -1, 11) * -0.0099999998;
  *(uint32_t *)(this + 84) = -sub_47EF20(4, nArg2, -1, -1, 11);
  *(uint32_t *)(this + 88) = sub_47EF20(5, nArg2, -1, -1, 11);
  *(uint32_t *)(this + 92) = sub_47EF20(6, nArg2, -1, -1, 11);
  result = sub_47EF20(7, nArg2, -1, -1, 11);
  *(uint32_t *)(this + 96) = result;
  return result;
}



// ============================================================
// SECTION 0x650C30 — 粒子特效加载（Common/CommonEffect/Particle/*.ptl）
// ============================================================
// ------------------------------------------------------------
// 0x650C30 sub_650C30
// ------------------------------------------------------------
// 【解读】
//   加载 Common/CommonEffect/Particle/AttackPowerUp.ptl（攻击力上升粒子，new + sub_428F30 粒子对象）。
// ------------------------------------------------------------
void /*thiscall*/ sub_650C30(int *this)
{
  int fld_e1; // esi
  uint32_t *pMem; // eax
  int *v4; // eax
  int v5; // edx
  int fld_e27; // ebx
  int v7; // eax
  void *v8; // eax
  int v9; // [esp-Ch] [ebp-38h]
  int v10; // [esp-8h] [ebp-34h]
  int v11; // [esp-4h] [ebp-30h]
  uint8_t v12[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *pMem2; // [esp+1Ch] [ebp-10h]
  int v15; // [esp+28h] [ebp-4h]

  sub_5F66C0();
  fld_e1 = *(this + 1);
  if ( *(this + 27) == 0 )
  {
    pMem = operator new(0x12Cu);
    pMem2 = pMem;
    v15 = 0;
    if ( pMem != nullptr )
      v4 = sub_428F30(pMem, (int)"Common/CommonEffect/Particle/AttackPowerUp.ptl", fld_e1);
    else
      v4 = nullptr;
    *(this + 27) = (int)v4;
    v5 = *v4;
    v15 = -1;
    (*(void (/*thiscall*/ **)(int *, int))(v5 + 112))(v4, fld_e1);
  }
  fld_e27 = *(uint32_t *)*(this + 27);
  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 128))(fld_e1) + 50;
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 124))(fld_e1);
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 120))(fld_e1);
  (*(void (/*thiscall*/ **)(uint32_t))(fld_e27 + 40))(*(this + 27));
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 27) + 92))(*(this + 27), v12);
  v7 = *(uint32_t *)fld_e1;
  v15 = 1;
  v8 = (void *)(*(int (/*thiscall*/ **)(int, int, uint32_t, uint8_t *))(v7 + 80))(fld_e1, 2, 0, v12);
  sub_4600B0(v8, v9, v10, v11);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x650D20 sub_650D20
// ------------------------------------------------------------
int /*thiscall*/ sub_650D20(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650D30 sub_650D30
// ------------------------------------------------------------
int /*thiscall*/ sub_650D30(int this, int nArg2)
{
  *(uint32_t *)(this + 80) = nArg2;
  *(uint8_t *)(this + 40) = 0;
  return nArg2;
}



// ------------------------------------------------------------
// 0x650D50 sub_650D50
// ------------------------------------------------------------
uint32_t */*usercall*/ sub_650D50@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>)
{
  uint32_t *result; // eax
  int *v5; // esi
  int v6; // ebx
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  char v10; // bl
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int pObj; // [esp+8h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 840))(*(uint32_t *)(pArg1 + 80));
  if ( result == (uint32_t *)22 )
  {
    v5 = *(int **)(pArg1 + 4);
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 840))(v5);
    if ( result == (uint32_t *)9 )
    {
      if ( (*(int (/*thiscall*/ **)(int *, int))(*v5 + 236))(v5, nArg3) == 1 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*v5 + 228))(v5, 0, -1, 0);
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *, int))(*v5 + 688))(v5, nArg2) + 16) != 0 )
      {
        v6 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);
        if ( *(uint32_t *)(v6 + 16) != (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5) )
        {
          v7 = *v5;
          v8 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v7 + 196))(v5, *(uint32_t *)(v8 + 16));
        }
      }
      v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 152))(*(uint32_t *)(pArg1 + 80));
      v10 = sub_432E50(v9);
      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v5 + 60))(v5) + 52) = v10;
      v11 = *v5;
      pObj = *(uint32_t *)(pArg1 + 80);
      v12 = (*(int (**)(void))(*(uint32_t *)pObj + 128))();
      v13 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 124))(pObj, *(uint32_t *)(pArg1 + 92) + v12);
      v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, *(uint32_t *)(pArg1 + 88) + v13);
      (*(void (/*thiscall*/ **)(int *, int))(v11 + 112))(v5, *(uint32_t *)(pArg1 + 84) + v14);
      (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 612))(v5, 1, 1);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*v5 + 820))(v5, 0);
      result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
      if ( result != nullptr )
      {
        v15 = (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
        return sub_4938F0(v15);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x650E80 sub_650E80
// ------------------------------------------------------------
int /*thiscall*/ sub_650E80(int this)
{
  int fld_50; // eax
  int fld_4; // ecx
  int fld_42; // ecx
  int result; // eax

  fld_50 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 152))(*(uint32_t *)(this + 80));
  fld_4 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 84) = fld_50 != 0 ? 43 : -43;
  *(uint32_t *)(this + 88) = -1;
  if ( 110 - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 192))(fld_4) <= 10 )
    fld_42 = 10;
  else
    fld_42 = 110 - (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));
  *(uint32_t *)(this + 92) = fld_42;
  result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 776))(*(uint32_t *)(this + 4), 3);
  if ( (uint8_t)result != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 556))(*(uint32_t *)(this + 4), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 768))(
      *(uint32_t *)(this + 4),
      3,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 556))(*(uint32_t *)(this + 4), 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x650F20 sub_650F20
// ------------------------------------------------------------
int /*thiscall*/ sub_650F20(int this)
{
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 1065353216;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint8_t *)(this + 184) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650F70 sub_650F70
// ------------------------------------------------------------
int /*thiscall*/ sub_650F70(uint32_t *this)
{
  uint32_t *pThis_27; // esi
  int i; // edi
  int result; // eax

  pThis_27 = this + 39;
  for ( i = 3; i != 0; --i )
  {
    if ( *pThis_27 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_27)(*pThis_27, 1);
    *pThis_27++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x650FA0 sub_650FA0
// ------------------------------------------------------------
bool /*thiscall*/ sub_650FA0(uint32_t *this, int nArg2)
{
  return (uint8_t)sub_4E4630(nArg2) != 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 128))(nArg2) <= *(this + 37)
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 624))(nArg2) != 0
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 724))(nArg2) == 0;
}



// ------------------------------------------------------------
// 0x651000 sub_651000
// ------------------------------------------------------------
int /*thiscall*/ sub_651000(int this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int result; // eax
  double v7; // st7
  uint32_t *pThis_A0; // ebx
  int i; // esi
  int *v10; // edi
  int v11; // [esp+8h] [ebp+8h]
  float fld_98; // [esp+Ch] [ebp+Ch]

  result = nArg2;
  *(uint32_t *)(this + 128) = nArg3;
  *(uint32_t *)(this + 140) = nArg4;
  *(uint32_t *)(this + 144) = nArg5;
  *(uint32_t *)(this + 84) = nArg2;
  *(uint32_t *)(this + 148) = nArg6;
  if ( nArg2 != 0 )
  {
    v7 = (double)nArg2 * 0.0083333338;
    pThis_A0 = (uint32_t *)(this + 160);
    v11 = 2;
    fld_98 = v7 / *(float *)(this + 152);
    *(float *)(this + 152) = v7;
    do
    {
      for ( i = 12; i < 24; i += 4 )
      {
        v10 = (int *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_A0 + 36))(*pThis_A0) + i);
        *v10 = (uint64_t)((double)*v10 * fld_98);
      }
      ++pThis_A0;
      result = --v11;
    }
    while ( v11 != 0 );
  }
  return result;
}



// ============================================================
// SECTION 0x6510A0 — 剑魂震波音效族（QUAKE_WAVE_READY_LOOP / QUAKE_WAVE_LOOP / SM_GHOSTSTEP 幽灵步克隆）
// ============================================================
// ------------------------------------------------------------
// 0x6510A0 sub_6510A0
// ------------------------------------------------------------
// 【解读】
//   "QUAKE_WAVE_READY_LOOP" 音效状态查询（返回就绪循环标志）。
// ------------------------------------------------------------
int /*thiscall*/ sub_6510A0(int this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
             *(uint32_t *)(this + 4),
             "QUAKE_WAVE_READY_LOOP",
             7,
             0,
             0);
  *(uint8_t *)(this + 184) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6510D0 sub_6510D0
// ------------------------------------------------------------
void /*thiscall*/ sub_6510D0(int this, uint32_t *pArg2)
{
  int pObj; // eax
  float v5; // [esp+4h] [ebp-28h]
  float fld_90; // [esp+34h] [ebp+8h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 273) != 0 )
    fld_90 = *(float *)(this + 144);
  else
    fld_90 = *(float *)(this + 140);
  if ( operator new(0x80u) != nullptr )
  {
    v5 = -fld_90;
    pObj = sub_4D6810(LODWORD(v5), -1, 1, 2);
  }
  else
  {
    pObj = 0;
  }
  (*(void (/*thiscall*/ **)(int, uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
    pObj,
    pArg2,
    *(uint32_t *)(this + 4),
    0,
    0,
    0,
    -1);
  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4)) != 0
    && *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4))
                             + 132)
                 + 52) == *(uint32_t *)(this + 4) )
  {
    sub_4684F0(*((uint32_t *)dword_8F8528 + 4), pArg2);
  }
}



// ------------------------------------------------------------
// 0x6511B0 sub_6511B0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_6511B0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; ++result )
    *result = *uArg12++;
  return result;
}



// ------------------------------------------------------------
// 0x6511E0 sub_6511E0
// ------------------------------------------------------------
// 【解读】
//   "QUAKE_WAVE_READY_LOOP" 设置/清除（sub_64A570 音对象转发）。
// ------------------------------------------------------------
int /*thiscall*/ sub_6511E0(int this)
{
  uint32_t *pThis_9C; // edi
  int i; // ebx

  sub_64A570();
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  pThis_9C = (uint32_t *)(this + 156);
  for ( i = 3; i != 0; --i )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_9C + 12))(*pThis_9C, 0);
    ++pThis_9C;
  }
  if ( *(uint32_t *)(this + 172) != 0 )
    j__free(*(void **)(this + 172));
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
           *(uint32_t *)(this + 4),
           "QUAKE_WAVE_READY_LOOP",
           7,
           0,
           0);
}



// ------------------------------------------------------------
// 0x651260 sub_651260
// ------------------------------------------------------------
// 【解读】
//   "SM_GHOSTSTEP" 幽灵步（剑魂被动）状态克隆: __RTDynamicCast 跨层次转型 + sub_64A360 复制。
// ------------------------------------------------------------
void /*thiscall*/ sub_651260(int this, int nArg2)
{
  int fld_4; // eax
  int pObj; // edi
  int v5; // ebx
  int v6; // eax
  uint32_t *i; // edi

  sub_64A360(nArg2);
  if ( (uint8_t)nArg2 == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4)) != 0 )
    {
      fld_4 = __RTDynamicCast(
             *(uint32_t *)(this + 4),
             0,
             &IRDActiveObject `RTTI Type Descriptor',
             &CNSwordman `RTTI Type Descriptor',
             0);
      pObj = fld_4;
      if ( fld_4 != 0 )
      {
        v5 = *(uint32_t *)fld_4;
        v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_4 + 1140))(fld_4, 52);
        (*(void (/*thiscall*/ **)(int, int, int))(v5 + 1296))(pObj, 52, v6);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pObj + 212))(
          pObj,
          "SM_GHOSTSTEP",
          -1,
          0,
          0);
      }
    }
    for ( i = *(uint32_t **)(this + 172); i != *(uint32_t **)(this + 176); ++i )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*i + 84))(*i, 0);
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 216))(*(uint32_t *)(this + 4), 7);
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 216))(*(uint32_t *)(this + 4), 8);
    *(uint8_t *)(this + 184) = 0;
  }
  if ( *(uint32_t *)(this + 172) != 0 )
    j__free(*(void **)(this + 172));
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
}



// ------------------------------------------------------------
// 0x651350 sub_651350
// ------------------------------------------------------------
void /*thiscall*/ sub_651350(uint32_t *this, int nArg2)
{
  unsigned int i; // ebx
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int pObj; // ecx
  int fld_e1; // edi
  int v13; // eax
  int v14; // ecx
  int v15; // ecx
  uint32_t *v16; // eax

  if ( nArg2 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
      v4 = *(uint32_t *)(v3 + 4);
      v5 = v4 != 0 ? (*(uint32_t *)(v3 + 8) - v4) >> 2 : 0;
      if ( (int)i >= v5 )
        break;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
      v7 = *(uint32_t *)(v6 + 4);
      if ( v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2 )
        v8 = *(uint32_t *)(v7 + 4 * i);
      else
        v8 = 0;
      if ( *(uint32_t *)(v8 + 4) == nArg2 )
      {
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
        v10 = *(uint32_t *)(v9 + 4);
        if ( v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2 )
          pObj = *(uint32_t *)(v10 + 4 * i);
        else
          pObj = 0;
        fld_e1 = *(this + 1);
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 32) == fld_e1 )
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
          v14 = *(uint32_t *)(v13 + 4);
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )
            v15 = *(uint32_t *)(v14 + 4 * i);
          else
            v15 = 0;
          v16 = (uint32_t *)__RTDynamicCast(
                            v15,
                            0,
                            &IRDAppendage `RTTI Type Descriptor',
                            &CNChangeHp `RTTI Type Descriptor',
                            0);
          if ( v16 != nullptr && v16[25] == 2 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v16 + 76))(v16, 0);
            return;
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x651450 sub_651450
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_651450(int this, int nArg2)
{
  int nArg22; // edi
  uint32_t *i; // edi
  uint32_t *fld_B0; // ecx
  uint32_t *result; // eax

  nArg22 = nArg2;
  sub_64A5E0(nArg2);
  if ( nArg2 == *(uint32_t *)(this + 4) )
  {
    for ( i = *(uint32_t **)(this + 172); i != *(uint32_t **)(this + 176); ++i )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*i + 84))(*i, 0);
    if ( *(uint32_t *)(this + 172) != 0 )
      j__free(*(void **)(this + 172));
    nArg22 = nArg2;
    *(uint32_t *)(this + 172) = 0;
    *(uint32_t *)(this + 176) = 0;
    *(uint32_t *)(this + 180) = 0;
  }
  fld_B0 = *(uint32_t **)(this + 176);
  result = *(uint32_t **)(this + 172);
  if ( result != fld_B0 )
  {
    do
    {
      if ( *result == nArg22 )
        break;
      ++result;
    }
    while ( result != fld_B0 );
    if ( result != fld_B0 )
    {
      memcpy_0(result, result + 1, 4 * ((*(uint32_t *)(this + 176) - (int)(result + 1)) >> 2));
      result = (uint32_t *)(*(uint32_t *)(this + 176) - 4);
      *(uint32_t *)(this + 176) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x651510 sub_651510
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_651510(int this, uint32_t *Src, uint32_t *uArg3, uint32_t *uArg4, int nArg5)
{
  int fld_4; // edx
  unsigned int v7; // ecx
  unsigned int result; // eax
  int fld_8; // edi
  int fld_82; // edi
  unsigned int v11; // eax
  int fld_86; // edi
  int fld_87; // eax
  char *pMem; // ebx
  size_t fld_42; // edi
  char *v16; // eax
  uint32_t *v17; // eax
  int fld_44; // ecx
  int fld_88; // eax
  unsigned int v20; // edi
  int fld_83; // ebx
  uint32_t *fld_84; // ebx
  const void *fld_43; // [esp-Ch] [ebp-34h]
  uint32_t *fld_85; // [esp-Ch] [ebp-34h]
  int v26; // [esp+0h] [ebp-28h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v28; // [esp+10h] [ebp-18h]
  unsigned int v29; // [esp+14h] [ebp-14h]
  int *v30; // [esp+18h] [ebp-10h]
  int v31; // [esp+24h] [ebp-4h]
  int Srca; // [esp+30h] [ebp+8h]
  void *Srcb; // [esp+30h] [ebp+8h]

  fld_4 = *(uint32_t *)(this + 4);
  v7 = uArg4 - uArg3;
  v30 = &v26;
  v29 = v7;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    result = 0;
  if ( v7 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < v7 )
      sub_42CB90(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( result >= v7 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);
      if ( (fld_83 - (int)Src) >> 2 >= v7 )
      {
        Srcb = (void *)(fld_83 - 4 * v7);
        *(uint32_t *)(this + 8) = sub_55E7F0(Srcb, fld_83, *(void **)(this + 8));
        sub_5DAF70(Src, (int)Srcb, fld_83);
        return (unsigned int)sub_6511B0(uArg3, uArg4, Src);
      }
      else
      {
        Srca = 4 * v7;
        sub_55E7F0(Src, fld_83, &Src[v7]);
        fld_84 = &uArg3[(*(uint32_t *)(this + 8) - (int)Src) >> 2];
        fld_85 = *(uint32_t **)(this + 8);
        v31 = 2;
        sub_497E70(fld_84, uArg4, fld_85);
        *(uint32_t *)(this + 8) += Srca;
        return (unsigned int)sub_6511B0(uArg3, fld_84, Src);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v11 = (result >> 1) + result;
      else
        v11 = 0;
      if ( fld_4 != 0 )
        fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
      else
        fld_86 = 0;
      if ( v11 < v7 + fld_86 )
      {
        if ( fld_4 != 0 )
          fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
        else
          fld_87 = 0;
        v11 = v7 + fld_87;
      }
      v28 = 4 * v11;
      pMem = (char *)operator new(4 * v11);
      fld_42 = 4 * (((int)Src - *(uint32_t *)(this + 4)) >> 2);
      fld_43 = *(const void **)(this + 4);
      Block = pMem;
      v31 = 0;
      v16 = (char *)memcpy_0(pMem, fld_43, fld_42);
      v17 = sub_497E70(uArg3, uArg4, &v16[fld_42]);
      memcpy_0(v17, Src, 4 * ((*(uint32_t *)(this + 8) - (int)Src) >> 2));
      fld_44 = *(uint32_t *)(this + 4);
      if ( fld_44 != 0 )
        fld_88 = (*(uint32_t *)(this + 8) - fld_44) >> 2;
      else
        fld_88 = 0;
      v20 = fld_88 + v29;
      if ( fld_44 != 0 )
        j__free(*(void **)(this + 4));
      result = (unsigned int)&pMem[v28];
      *(uint32_t *)(this + 12) = &pMem[v28];
      *(uint32_t *)(this + 8) = &pMem[4 * v20];
      *(uint32_t *)(this + 4) = pMem;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x651760 sub_651760
// ------------------------------------------------------------
// 【解读】
//   "QUAKE_WAVE_LOOP" 震波循环主逻辑（154 行）: sub_64A790 音对象 + sub_699000 时钟 +
//    sub_4922F0 效果查询 + sub_651510（120 行状态构建）。
// ------------------------------------------------------------
char /*thiscall*/ sub_651760(void *this)
{
  double v2; // st7
  double pThis_20; // st7
  char v5; // c0
  int pThis_1; // ecx
  int pThis_12; // edi
  int *pThis_13; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int *pThis_14; // edi
  int v13; // edx
  int v14; // eax
  int v15; // eax
  int pThis_82; // ebx
  uint32_t *Block2; // edi
  int v18; // eax
  void *pThis_15; // eax
  int **pThis_2B; // eax
  bool pThis_2C; // zf
  int *v22; // eax
  int pThis_16; // edi
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  int pThis_2C2; // ecx
  char result; // al
  float pThis_26; // [esp-4h] [ebp-34h]
  uint8_t v30[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  int v32; // [esp+14h] [ebp-1Ch]
  int v33; // [esp+18h] [ebp-18h]
  int v34; // [esp+1Ch] [ebp-14h]
  int pThis_8; // [esp+20h] [ebp-10h]
  int v36; // [esp+2Ch] [ebp-4h]

  sub_64A790();
  pThis_8 = sub_699000((int)this + 8) - *((uint32_t *)this + 34);
  v2 = (double)pThis_8;
  *((uint32_t *)this + 34) = sub_699000((int)this + 8);
  pThis_20 = v2 * *((float *)this + 32) * 0.001 + *((float *)this + 33);
  *((float *)this + 33) = pThis_20;
  if ( v5 == 0 )
  {
    pThis_1 = *((uint32_t *)this + 1);
    pThis_12 = (uint64_t)pThis_20;
    pThis_8 = pThis_12;
    *((float *)this + 33) = pThis_20 - (double)pThis_12;
    if ( pThis_12 > (*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)pThis_1 + 752))(pThis_1, (uint64_t)pThis_20 >> 32) )
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 76))(this, 0);
      pThis_12 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1) + 752))(*((uint32_t *)this + 1));
      pThis_8 = pThis_12;
    }
    if ( pThis_12 > 0 )
    {
      pThis_13 = *((int **)this + 1);
      v9 = *pThis_13;
      v10 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*pThis_13 + 752))(pThis_13, 0);
      (*(void (/*thiscall*/ **)(int *, int))(v9 + 744))(pThis_13, v10 - pThis_8);
    }
  }
  v11 = 0;
  pThis_8 = 0;
  do
  {
    pThis_14 = *((int **)this + 1);
    v13 = *pThis_14;
    v34 = **((uint32_t **)this + v11 + 39);
    v14 = (*(int (/*thiscall*/ **)(int *, bool))(v13 + 124))(pThis_14, v11 == 1);
    v15 = (*(int (/*thiscall*/ **)(int *, int))(*pThis_14 + 120))(pThis_14, v14);
    pThis_82 = pThis_8;
    (*(void (/*thiscall*/ **)(uint32_t, int))(v34 + 40))(*((uint32_t *)this + pThis_8 + 39), v15);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**((uint32_t **)this + pThis_82 + 39) + 92))(*((uint32_t *)this + pThis_82 + 39), v30);
    v36 = 0;
    if ( pThis_82 == 0 )
    {
      Block2 = Block;
      v18 = v32;
      if ( Block != (void *)v32 )
      {
        do
        {
          *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 36))(*Block2) + 8) = 2;
          pThis_26 = *((float *)this + 38);
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 96))(*Block2);
          sub_4922F0(pThis_26);
          v18 = v32;
          ++Block2;
        }
        while ( Block2 != (uint32_t *)v32 );
        Block2 = Block;
      }
      sub_651510(*((void **)this + 44), (int)Block2, v18, v34);
    }
    pThis_15 = (void *)(*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1) + 80))(*((uint32_t *)this + 1));
    sub_4600B0(pThis_15, 2, 0, (int)v30);
    v36 = -1;
    if ( Block != nullptr )
      j__free(Block);
    v11 = pThis_82 + 1;
    Block = nullptr;
    v32 = 0;
    v33 = 0;
    pThis_8 = v11;
  }
  while ( v11 < 3 );
  pThis_2B = *((int ***)this + 43);
  pThis_2C = pThis_2B == *((int ***)this + 44);
  pThis_8 = (int)pThis_2B;
  if ( !pThis_2C )
  {
    do
    {
      v22 = *pThis_2B;
      pThis_16 = *((uint32_t *)this + 1);
      v24 = *v22;
      v34 = (int)v22;
      v25 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pThis_16 + 124))(pThis_16, 0);
      v26 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_16 + 120))(pThis_16, v25);
      (*(void (/*thiscall*/ **)(int, int))(v24 + 112))(v34, v26);
      pThis_2C2 = *((uint32_t *)this + 44);
      pThis_2B = (int **)(pThis_8 + 4);
      pThis_8 += 4;
    }
    while ( pThis_8 != pThis_2C2 );
  }
  result = *((uint8_t *)this + 184);
  if ( *((uint32_t *)this + 30) != 0 )
  {
    if ( result == 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**((uint32_t **)this + 1) + 212))(
                 *((uint32_t *)this + 1),
                 "QUAKE_WAVE_LOOP",
                 8,
                 0,
                 0);
      *((uint8_t *)this + 184) = 1;
    }
  }
  else if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)this + 1) + 216))(*((uint32_t *)this + 1), 8);
    *((uint8_t *)this + 184) = 0;
  }
  return result;
}


// ------------------------------------------------------------
// 0x6519E0 sub_6519E0
// ------------------------------------------------------------
// 【解读】
//   加载 Character/Swordman/Effect/Particle/DOTArea{Quake,Rock,Dust}.ptl 三连 ——
//   剑魂（Swordman）范围 DOT 状态的震波/落石/尘土粒子。
// ------------------------------------------------------------
int /*thiscall*/ sub_6519E0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  uint32_t *pMem; // eax
  uint32_t *v8; // eax
  uint32_t *pMem2; // eax
  uint32_t *v10; // eax
  uint32_t *pMem3; // eax
  uint32_t *v12; // eax

  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    v8 = sub_428F30(pMem, (int)"Character/Swordman/Effect/Particle/DOTAreaQuake.ptl", 0);
  else
    v8 = nullptr;
  *(this + 39) = v8;
  pMem2 = operator new(0x12Cu);
  if ( pMem2 != nullptr )
    v10 = sub_428F30(pMem2, (int)"Character/Swordman/Effect/Particle/DOTAreaRock.ptl", 0);
  else
    v10 = nullptr;
  *(this + 40) = v10;
  pMem3 = operator new(0x12Cu);
  if ( pMem3 != nullptr )
    v12 = sub_428F30(pMem3, (int)"Character/Swordman/Effect/Particle/DOTAreaDust.ptl", 0);
  else
    v12 = nullptr;
  *(this + 41) = v12;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int, int, int))(*this + 148))(this, nArg2, nArg3, nArg4, nArg5, nArg6);
}



// ------------------------------------------------------------
// 0x651AF0 sub_651AF0
// ------------------------------------------------------------
int /*thiscall*/ sub_651AF0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e25)(uint32_t, int); // ecx
  int result; // eax

  fld_e25 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 25);
  if ( fld_e25 != nullptr )
    result = (**fld_e25)(fld_e25, 1);
  *(this + 25) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x651B10 sub_651B10
// ------------------------------------------------------------
int /*thiscall*/ sub_651B10(int this)
{
  int fld_64; // ecx
  int result; // eax

  *(uint8_t *)(this + 80) = 0;
  fld_64 = *(uint32_t *)(this + 100);
  if ( fld_64 != 0 )
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_64 + 12))(fld_64, 0);
  return result;
}



// ------------------------------------------------------------
// 0x651B30 sub_651B30
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_651B30(int nArg1, int nArg2, uint32_t *uArg3)
{
  int nArg22; // ecx
  uint32_t *result; // eax
  int v5; // esi

  nArg22 = nArg2;
  for ( result = uArg3; nArg22 != nArg1; *result = v5 )
  {
    v5 = *(uint32_t *)(nArg22 - 4);
    nArg22 -= 4;
    --result;
  }
  return result;
}



// ============================================================
// SECTION 0x651B60 — 状态解除/斗气/瞄准要害演出（RemoveActiveStatus.ptl / Provocationed.ani / AimedVitalPoint.ani）
// ============================================================
// ------------------------------------------------------------
// 0x651B60 sub_651B60
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_651B60(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *result; // eax
  uint32_t *uArg22; // ecx

  result = uArg2;
  if ( uArg2 != nullptr )
  {
    uArg22 = uArg2;
    result = uArg1;
    do
    {
      if ( result != nullptr )
        *result = *uArg3;
      ++result;
      uArg22 = (uint32_t *)((char *)uArg22 - 1);
    }
    while ( uArg22 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x651B90 sub_651B90
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_651B90(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  sub_651B60(uArg1, uArg2, uArg3);
  return &uArg1[(uint32_t)uArg2];
}



// ------------------------------------------------------------
// 0x651BC0 sub_651BC0
// ------------------------------------------------------------
void /*thiscall*/ sub_651BC0(uint32_t *this)
{
  int *fld_e1; // esi
  uint32_t *i; // ebx
  int *fld_e25; // eax
  int v5; // ebx
  int v6; // edx
  void *v7; // eax
  int v8; // [esp-Ch] [ebp-34h]
  int v9; // [esp-8h] [ebp-30h]
  int v10; // [esp-4h] [ebp-2Ch]
  uint8_t v11[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v13; // [esp+24h] [ebp-4h]

  sub_5F66C0();
  fld_e1 = (int *)*(this + 1);
  if ( *((uint8_t *)this + 80) == 0 )
  {
    for ( i = (uint32_t *)*(this + 22); i != (uint32_t *)*(this + 23); ++i )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *, uint32_t))(*fld_e1 + 776))(fld_e1, *i) != 0 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int *, uint32_t))(*fld_e1 + 764))(fld_e1, *i, 0, fld_e1, 0);
    }
    *((uint8_t *)this + 80) = 1;
  }
  fld_e25 = (int *)*(this + 25);
  if ( fld_e25 != nullptr )
  {
    v5 = *fld_e25;
    v10 = (*(int (/*thiscall*/ **)(int *))(*fld_e1 + 128))(fld_e1) + 90;
    v9 = (*(int (/*thiscall*/ **)(int *))(*fld_e1 + 124))(fld_e1) + 30;
    v8 = (*(int (/*thiscall*/ **)(int *))(*fld_e1 + 120))(fld_e1);
    (*(void (/*thiscall*/ **)(uint32_t))(v5 + 40))(*(this + 25));
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 25) + 92))(*(this + 25), v11);
    v6 = *fld_e1;
    v13 = 0;
    v7 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v6 + 80))(fld_e1, 2, 0, v11);
    sub_4600B0(v7, v8, v9, v10);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 68))(*(this + 25)) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 76))(this, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x651CC0 sub_651CC0
// ------------------------------------------------------------
void /*thiscall*/ sub_651CC0(int this, int nArg2, unsigned int uArg3, uint32_t *uArg4)
{
  int fld_4; // edx
  uint32_t *v6; // ecx
  unsigned int fld_C; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v11; // eax
  int fld_87; // ecx
  int fld_88; // eax
  char *pMem; // edi
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v17; // ebx
  uint32_t *fld_83; // eax
  bool v20; // cf
  int v21; // ecx
  int fld_86; // ebx
  int v23; // ebx
  int fld_42; // [esp-18h] [ebp-3Ch]
  uint32_t *fld_85; // [esp-Ch] [ebp-30h]
  uint32_t *fld_84; // [esp-8h] [ebp-2Ch]
  int v27; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v29; // [esp+10h] [ebp-14h]
  int *v30; // [esp+14h] [ebp-10h]
  int v31; // [esp+20h] [ebp-4h]
  int v32; // [esp+2Ch] [ebp+8h]
  uint32_t *v33; // [esp+30h] [ebp+Ch]
  uint32_t *fld_832; // [esp+30h] [ebp+Ch]

  fld_4 = *(uint32_t *)(this + 4);
  v6 = (uint32_t *)*uArg4;
  v30 = &v27;
  uArg4 = v6;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_6024A0(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t **)(this + 8);
      v20 = ((int)fld_83 - nArg2) >> 2 < uArg3;
      v21 = 4 * uArg3;
      v32 = 4 * uArg3;
      fld_832 = fld_83;
      if ( v20 )
      {
        sub_497E70(nArg2, fld_83, nArg2 + v21);
        fld_84 = (uint32_t *)(uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 2));
        fld_85 = *(uint32_t **)(this + 8);
        v31 = 2;
        sub_651B90(fld_85, fld_84, &uArg4);
        fld_86 = v32 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        sub_49A9D0(nArg2, fld_86 - v32, &uArg4);
      }
      else
      {
        v23 = (int)&fld_83[v21 / 0xFFFFFFFC];
        *(uint32_t *)(this + 8) = sub_497E70(&fld_83[v21 / 0xFFFFFFFC], fld_83, fld_83);
        sub_651B30(nArg2, v23, fld_832);
        sub_49A9D0(nArg2, nArg2 + v32, &uArg4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (fld_C >> 1) >= fld_C )
        v11 = (fld_C >> 1) + fld_C;
      else
        v11 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
      else
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
        else
          fld_88 = 0;
        v11 = uArg3 + fld_88;
      }
      v29 = 4 * v11;
      pMem = (char *)operator new(4 * v11);
      fld_42 = *(uint32_t *)(this + 4);
      Block = pMem;
      v31 = 0;
      v33 = (uint32_t *)sub_497E70(fld_42, nArg2, pMem);
      sub_651B60(v33, (uint32_t *)uArg3, &uArg4);
      sub_497E70(nArg2, *(uint32_t *)(this + 8), &v33[uArg3]);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 2;
      else
        fld_89 = 0;
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &pMem[v29];
      *(uint32_t *)(this + 8) = &pMem[4 * v17];
      *(uint32_t *)(this + 4) = pMem;
    }
  }
}


// ------------------------------------------------------------
// 0x651F00 sub_651F00
// ------------------------------------------------------------
void /*thiscall*/ sub_651F00(int *this, uint32_t *uArg2)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  uint32_t *fld_e22; // edi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 2;
  else
    fld_e2 = 0;
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) >> 2 )
  {
    fld_e22 = (uint32_t *)*(this + 2);
    sub_651B60(fld_e22, (uint32_t *)1, uArg2);
    *(this + 2) = (int)(fld_e22 + 1);
  }
  else
  {
    sub_651CC0((int)this, *(this + 2), 1u, uArg2);
  }
}



// ------------------------------------------------------------
// 0x651F70 sub_651F70
// ------------------------------------------------------------
// 【解读】
//   加载 Common/CommonEffect/Particle/RemoveActiveStatus.ptl（状态解除特效）。
// ------------------------------------------------------------
char /*thiscall*/ sub_651F70(int *this, int nArg2, void *Block)
{
  char result; // al
  uint32_t *pMem; // eax
  uint32_t *fld_e1; // eax
  int fld_e12; // ecx

  sub_651F00(this + 21, &nArg2);
  result = (char)Block;
  if ( (uint8_t)Block != 0 )
  {
    pMem = operator new(0x12Cu);
    Block = pMem;
    if ( pMem != nullptr )
      fld_e1 = sub_428F30(pMem, (int)"Common/CommonEffect/Particle/RemoveActiveStatus.ptl", *(this + 1));
    else
      fld_e1 = nullptr;
    fld_e12 = *(this + 1);
    *(this + 25) = (int)fld_e1;
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*fld_e1 + 112))(fld_e1, fld_e12);
  }
  else
  {
    *(this + 25) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x652010 sub_652010
// ------------------------------------------------------------
int /*thiscall*/ sub_652010(uint32_t *this, int nArg2, int nArg3)
{
  *(this + 11) = nArg2;
  *(this + 20) = nArg3;
  return nArg2;
}



// ------------------------------------------------------------
// 0x652030 sub_652030
// ------------------------------------------------------------
int /*thiscall*/ sub_652030(float *this, int pArg2)
{
  unsigned int v2; // esi
  int v3; // edx
  float fld_e20; // [esp+4h] [ebp-4h]
  int v6; // [esp+10h] [ebp+8h]

  v2 = pArg2 + 1264;
  fld_e20 = *(this + 20);
  *(float *)&v6 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1264)) + fld_e20;
  return sub_41A590(v2, v3, v6);
}



// ------------------------------------------------------------
// 0x652070 sub_652070
// ------------------------------------------------------------
char /*thiscall*/ sub_652070(int *this, char pszArg2)
{
  uint8_t *fld_e1; // eax

  LOBYTE(fld_e1) = pszArg2;
  if ( pszArg2 == 0 )
  {
    fld_e1 = (uint8_t *)__RTDynamicCast(
                    *(this + 1),
                    0,
                    &IRDActiveObject `RTTI Type Descriptor',
                    &IRDMonster `RTTI Type Descriptor',
                    0);
    if ( fld_e1 != nullptr )
    {
      fld_e1 = (uint8_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)fld_e1 + 1040))(fld_e1);
      fld_e1[8] = 1;
    }
  }
  return (char)fld_e1;
}



// ------------------------------------------------------------
// 0x6520B0 sub_6520B0
// ------------------------------------------------------------
// 【解读】
//   应用 Character/Fighter/Effect/Animation/Provocationed.ani（斗气爆发）—— 格斗家演出切换（__RTDynamicCast + 动画接口族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_6520B0(int *this)
{
  int v1; // ebx
  int fld_e1; // esi
  char *v4; // eax
  char *v5; // edi
  int v6; // eax
  int v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int result; // eax
  int v12; // [esp-4h] [ebp-2Ch]
  int fld_e9; // [esp+10h] [ebp-18h]
  int pObj; // [esp+14h] [ebp-14h]
  char *pObj2; // [esp+18h] [ebp-10h]

  v1 = 0;
  fld_e1 = *(this + 1);
  pObj = __RTDynamicCast(fld_e1, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
  fld_e9 = __RTDynamicCast(
          *(this + 9),
          0,
          &IRDCollisionObject `RTTI Type Descriptor',
          &IRDActiveObject `RTTI Type Descriptor',
          0);
  if ( sub_42FCB0(228) != 0 )
    v1 = sub_431860((char)"Character/Fighter/Effect/Animation/Provocationed.ani", 1);
  v4 = (char *)sub_44B6C0(284);
  v5 = v4;
  if ( v4 != nullptr )
  {
    sub_44E0D0(v4, v1, 1);
    *(uint32_t *)v5 = &CNRDPooledObject::`vftable';
  }
  else
  {
    v5 = nullptr;
  }
  pObj2 = v5;
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 80))(fld_e1);
  sub_45FE80(v6, (int)v5, 2, 0, (int)v5, 0, 0);
  v7 = *(uint32_t *)v5;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 192))(fld_e1);
  v12 = v8 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 128))(fld_e1) + 30;
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 124))(fld_e1);
  v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1 + 120))(fld_e1, v9);
  (*(void (/*thiscall*/ **)(char *, int))(v7 + 112))(pObj2, v10);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj2 + 60))(pObj2, fld_e1);
  result = sub_4A06D0(v12);
  if ( pObj != 0 )
  {
    result = fld_e9;
    if ( fld_e9 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 1152))(pObj, *(this + 9));
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1040))(pObj) + 8) = 0;
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1104))(pObj, 9);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x652220 sub_652220
// ------------------------------------------------------------
int /*thiscall*/ sub_652220(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x652230 sub_652230
// ------------------------------------------------------------
int /*thiscall*/ sub_652230(int this, int nArg2)
{
  int result; // eax

  sub_47E720(1, 39);
  *(float *)(this + 80) = (double)(int)sub_47EF20(0, nArg2, -1, -1, 11) * 0.1;
  *(uint32_t *)(this + 84) = sub_47EF20(3, nArg2, -1, -1, 11);
  result = sub_47EF20(1, nArg2, -1, -1, 11);
  *(uint32_t *)(this + 44) = result;
  return result;
}



// ------------------------------------------------------------
// 0x6522A0 sub_6522A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6522A0(int this, int pArg2)
{
  unsigned int v4; // edi
  int v5; // edx
  int fld_54; // esi
  int v7; // eax
  int v8; // edx
  float fld_50; // [esp+Ch] [ebp-4h]
  int v11; // [esp+18h] [ebp+8h]

  v4 = pArg2 + 1278;
  fld_50 = *(float *)(this + 80);
  *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1278)) - fld_50;
  sub_41A590(v4, v5, v11);
  fld_54 = *(uint32_t *)(this + 84);
  v7 = sub_41A5E0(pArg2 + 466);
  return sub_41A590(pArg2 + 466, v8, v7 - fld_54);
}



// ------------------------------------------------------------
// 0x652300 sub_652300
// ------------------------------------------------------------
char /*thiscall*/ sub_652300(int this, char pszArg2, int nArg3, int nArg4, int nArg5)
{
  char result; // al
  int fld_4; // eax

  result = pszArg2;
  if ( pszArg2 != 0 )
  {
    sub_4938F0(*(uint32_t *)(this + 88));
    fld_4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));
    return sub_491D00(dword_79C0B0, nArg3, nArg4 - fld_4 - 30, 0.0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x652350 sub_652350
// ------------------------------------------------------------
int /*thiscall*/ sub_652350(void ***this)
{
  int fld_e22; // esi
  int result; // eax

  fld_e22 = (int)*(this + 22);
  if ( fld_e22 != 0 )
  {
    sub_42AF90(*(this + 22));
    result = sub_657740(fld_e22, 228);
  }
  *(this + 22) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x652380 sub_652380
// ------------------------------------------------------------
// 【解读】
//   应用 Character/Fighter/Effect/Animation/AimedVitalPoint.ani（瞄准要害）。
// ------------------------------------------------------------
int /*thiscall*/ sub_652380(int *this)
{
  int v2; // eax

  if ( *(this + 22) == 0 )
  {
    if ( sub_42FCB0(228) != 0 )
      v2 = sub_431860((char)"Character/Fighter/Effect/Animation/AimedVitalPoint.ani", 1);
    else
      v2 = 0;
    *(this + 22) = v2;
  }
  return sub_4926A0(*(this + 22));
}



// ------------------------------------------------------------
// 0x652400 sub_652400
// ------------------------------------------------------------
int /*thiscall*/ sub_652400(uint32_t *this, int nArg2, int nArg3)
{
  *(this + 21) = nArg2;
  *(this + 22) = nArg3;
  return nArg2;
}



// ------------------------------------------------------------
// 0x652420 sub_652420
// ------------------------------------------------------------
// attributes: thunk
int sub_652420()
{
  return sub_5F66C0();
}



// ------------------------------------------------------------
// 0x652430 sub_652430
// ------------------------------------------------------------
int /*thiscall*/ sub_652430(uint32_t *this, int nArg2)
{
  uint32_t *pThis; // ebx
  unsigned int v3; // esi
  int v4; // edi
  int v5; // eax
  int v6; // edx
  int v7; // edi
  unsigned int v8; // esi
  int result; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // edx
  int i; // [esp+10h] [ebp-4h]

  pThis = this;
  v3 = nArg2 + 172;
  for ( i = 4; i != 0; --i )
  {
    v4 = pThis[21];
    v5 = sub_41A5E0(v3);
    sub_41A590(v3, v6, v5 - v4);
    v3 += 14;
  }
  v7 = 0;
  v8 = nArg2 + 284;
  do
  {
    result = sub_497040(v7);
    if ( result != 17 )
    {
      v10 = pThis[22];
      v11 = sub_41A5E0(v8);
      result = sub_41A590(v8, v12, v11 - v10);
      pThis = this;
    }
    ++v7;
    v8 += 14;
  }
  while ( v7 < 16 );
  return result;
}



// ------------------------------------------------------------
// 0x6524C0 sub_6524C0
// ------------------------------------------------------------
int /*thiscall*/ sub_6524C0(uint32_t *this, float *pArg2, int *pDwArg3)
{
  int result; // eax

  if ( *pDwArg3 == 0 )
    *pArg2 = -*pArg2;
  if ( pDwArg3[1] == 2 )
    pArg2[1] = -pArg2[1];
  *(this + 21) = *(uint32_t *)pArg2;
  *(this + 22) = *((uint32_t *)pArg2 + 1);
  result = *pDwArg3;
  *(this + 23) = *pDwArg3;
  *(this + 24) = pDwArg3[1];
  return result;
}



// ------------------------------------------------------------
// 0x652500 sub_652500
// ------------------------------------------------------------
char /*userpurge*/ sub_652500@<al>(int pArg1@<ecx>, int nArg2@<edi>, int nArg3)
{
  double v3; // st7
  int v5; // ebx
  int v6; // edi
  int *v7; // ecx
  int v8; // ebx
  int v9; // eax
  int *v11; // [esp+0h] [ebp-4h]
  int v12; // [esp+Ch] [ebp+8h]
  int v13; // [esp+Ch] [ebp+8h]

  v3 = (double)nArg3;
  v5 = (uint64_t)(v3 * *(float *)(pArg1 + 84) * 0.033333335);
  v12 = (uint64_t)(v3 * *(float *)(pArg1 + 88) * 0.033333335);
  v6 = v5
     + (*(int (/*fastcall*/ **)(uint32_t, uint32_t, int))(**(uint32_t **)(pArg1 + 4) + 120))(
         *(uint32_t *)(pArg1 + 4),
         (uint64_t)(v3 * *(float *)(pArg1 + 88) * 0.033333335) >> 32,
         nArg2);
  v13 = v12 + (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 124))(*(uint32_t *)(pArg1 + 4));
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(pArg1 + 4) + 136))(
         *(uint32_t *)(pArg1 + 4),
         v6,
         v13,
         0) != 0 )
  {
    v7 = *(int **)(pArg1 + 4);
    v8 = *v7;
    v11 = v7;
    v9 = (*(int (**)(void))(*v7 + 128))();
    (*(void (/*thiscall*/ **)(int *, int, int, int))(v8 + 112))(v11, v6, v13, v9);
  }
  *(uint8_t *)(pArg1 + 21) = 0;
  *(uint8_t *)(pArg1 + 22) = 0;
  return sub_698F90(pArg1 + 8, 0, 0);
}



// ============================================================
// SECTION 0x6525A0 — 窗口/客户端小工具（GetClientRect 等）
// ============================================================
// ------------------------------------------------------------
// 0x6525A0 sub_6525A0
// ------------------------------------------------------------
int /*stdcall*/ sub_6525A0(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7)
{
  return -2147467263;
}



// ------------------------------------------------------------
// 0x6525B0 sub_6525B0
// ------------------------------------------------------------
int /*stdcall*/ sub_6525B0(int nArg1, int nArg2)
{
  return 0;
}



// ------------------------------------------------------------
// 0x6525C0 sub_6525C0
// ------------------------------------------------------------
int /*stdcall*/ sub_6525C0(int pArg1, uint32_t *uArg2)
{
  *uArg2 = *(uint32_t *)(pArg1 + 4);
  return 0;
}



// ------------------------------------------------------------
// 0x6525E0 sub_6525E0
// ------------------------------------------------------------
int /*stdcall*/ sub_6525E0(int nArg1, int nArg2, int nArg3, int nArg4)
{
  return 0;
}



// ------------------------------------------------------------
// 0x6525F0 sub_6525F0
// ------------------------------------------------------------
int /*stdcall*/ sub_6525F0(int nArg1, const void *pArg2, uint32_t *uArg3)
{
  int result; // eax

  if ( memcmp(pArg2, &dword_743370, 0x10u) == 0 || memcmp(pArg2, &unk_743360, 0x10u) == 0 )
  {
    *uArg3 = nArg1;
    return 0;
  }
  else
  {
    result = 0;
    if ( memcmp(pArg2, &unk_743340, 0x10u) == 0 )
    {
      *uArg3 = nArg1 + 4;
    }
    else
    {
      *uArg3 = 0;
      return -2147467262;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x652670 sub_652670
// ------------------------------------------------------------
int /*stdcall*/ sub_652670(int pArg1, uint32_t *uArg2)
{
  *uArg2 = *(uint32_t *)(*(uint32_t *)(pArg1 + 4) + 4);
  return 0;
}



// ------------------------------------------------------------
// 0x652690 sub_652690
// ------------------------------------------------------------
int /*stdcall*/ sub_652690(int pArg1, int nArg2, uint32_t *uArg3, LPRECT lpRect, LPRECT uArg5, int pArg6)
{
  HWND v6; // edx

  *(uint32_t *)nArg2 = *(uint32_t *)(pArg1 + 4);
  *uArg3 = 0;
  *(uint32_t *)(pArg6 + 4) = 0;
  v6 = *(HWND *)(*(uint32_t *)nArg2 + 4);
  *(uint32_t *)(pArg6 + 12) = 0;
  *(uint32_t *)(pArg6 + 16) = 0;
  *(uint32_t *)(pArg6 + 8) = v6;
  GetClientRect(v6, lpRect);
  GetClientRect(*(HWND *)(pArg6 + 8), uArg5);
  return 0;
}



// ------------------------------------------------------------
// 0x6526F0 sub_6526F0
// ------------------------------------------------------------
int /*stdcall*/ sub_6526F0(int nArg1, uint32_t *uArg2)
{
  *uArg2 = 0;
  return -2147467262;
}



// ------------------------------------------------------------
// 0x652720 sub_652720
// ------------------------------------------------------------
int /*stdcall*/ sub_652720(int nArg1, int *pDwArg2, uint32_t *uArg3)
{
  int v3; // ecx

  v3 = *pDwArg2;
  if ( (*pDwArg2 != 0 || *((uint16_t *)pDwArg2 + 2) != 0 || *((uint16_t *)pDwArg2 + 3) != 0)
    && (v3 != 132096 || *((uint16_t *)pDwArg2 + 2) != 0 || *((uint16_t *)pDwArg2 + 3) != 0)
    && (v3 != 883365280 || *((uint16_t *)pDwArg2 + 2) != 25991 || *((uint16_t *)pDwArg2 + 3) != 4560) )
  {
    return -2147467262;
  }
  *uArg3 = nArg1;
  return 0;
}



// ------------------------------------------------------------
// 0x6527B0 sub_6527B0
// ------------------------------------------------------------
int /*stdcall*/ sub_6527B0(int nArg1)
{
  return 1;
}



// ------------------------------------------------------------
// 0x6527C0 sub_6527C0
// ------------------------------------------------------------
int /*stdcall*/ sub_6527C0(int nArg1, int nArg2)
{
  return -2147467263;
}



// ------------------------------------------------------------
// 0x6527D0 sub_6527D0
// ------------------------------------------------------------
int /*stdcall*/ sub_6527D0(int nArg1, int nArg2, int nArg3, int nArg4)
{
  return -2147467263;
}



// ------------------------------------------------------------
// 0x6527E0 sub_6527E0
// ------------------------------------------------------------
int /*stdcall*/ sub_6527E0(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  return -2147467263;
}



// ============================================================
// SECTION 0x6527F0 — ★★ 内嵌 OLE 浏览器（NEOPLE_WEB: OleCreate WebBrowser 控件 / Navigate / NAVIGATION START/END 调试标记）
// ============================================================
// ------------------------------------------------------------
// 0x6527F0 sub_6527F0
// ------------------------------------------------------------
// 【解读】
//   导航调试标记: "************** NAVIGATION START **************" / "...NAVIGATION END..."
//    → OutputDebugStringA + PostMessageA。（docs/04 把本区归为“寻路/导航”实为此导航调试，非寻路算法。）
// ------------------------------------------------------------
int /*stdcall*/ sub_6527F0(int pArg1, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7, int nArg8, int nArg9)
{
  int v10; // eax

  switch ( nArg2 )
  {
    case 263:
      PostMessageA(*(HWND *)(pArg1 + 4), 0x10u, 0, 0);
      return 0;
    case 252:
      if ( *(uint32_t *)(pArg1 + 8) == 0 )
      {
        *(uint32_t *)(pArg1 + 8) = *(uint32_t *)(*(uint32_t *)nArg6 + 24);
        OutputDebugStringA("************** NAVIGATION START **************\n");
        return 0;
      }
      break;
    case 259:
      v10 = *(uint32_t *)(pArg1 + 8);
      if ( v10 != 0 && v10 == *(uint32_t *)(*(uint32_t *)nArg6 + 24) )
      {
        *(uint32_t *)(pArg1 + 8) = 0;
        OutputDebugStringA("************** NAVIGATION END **************\n");
      }
      break;
    default:
      break;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x652880 sub_652880
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_652880(HWND hWnd)
{
  uint32_t *result; // eax
  void *v2; // edi
  int pObj; // esi

  result = (uint32_t *)GetWindowLongA(hWnd, -21);
  v2 = result;
  if ( result != nullptr )
  {
    pObj = *result;
    (*(void (/*stdcall*/ **)(uint32_t, int))(*(uint32_t *)*result + 24))(*result, 1);
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj + 8))(pObj);
    GlobalFree(v2);
    return (uint32_t *)SetWindowLongA(hWnd, -21, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6528C0 sub_6528C0
// ------------------------------------------------------------
// 【解读】
//   OleCreate 内嵌 WebBrowser 控件: GlobalAlloc 站点内存 → OleCreate(IOleObject) →
//     OleSetContainedObject → SetWindowLong 挂站点。0x652880 = 控件分离（还原 WndProc + GlobalFree）。
// ------------------------------------------------------------
int /*cdecl*/ sub_6528C0(HWND hWnd)
{
  IOleClientSite *v1; // eax
  IOleClientSite *v2; // edi
  IOleClientSite *v4; // ebx
  struct tagRECT Rect; // [esp+4h] [ebp-28h] BYREF
  uint8_t v6[4]; // [esp+14h] [ebp-18h] BYREF
  IOleClientSite *v7; // [esp+18h] [ebp-14h]
  int pObj3; // [esp+1Ch] [ebp-10h] BYREF
  int pObj; // [esp+20h] [ebp-Ch] BYREF
  LPVOID ppvObj; // [esp+24h] [ebp-8h] BYREF
  int pObj2; // [esp+28h] [ebp-4h] BYREF

  v1 = (IOleClientSite *)GlobalAlloc(0, 0x24u);
  v2 = v1;
  if ( v1 == nullptr )
    return -1;
  v1[1].lpVtbl = (struct IOleClientSiteVtbl *)&off_79602C;
  v1[2].lpVtbl = (struct IOleClientSiteVtbl *)hWnd;
  v4 = v1 + 3;
  v1[5].lpVtbl = (struct IOleClientSiteVtbl *)&v1[1];
  v1[3].lpVtbl = (struct IOleClientSiteVtbl *)&off_7960A4;
  v1[4].lpVtbl = (struct IOleClientSiteVtbl *)&off_796068;
  v7 = v1 + 6;
  v1[6].lpVtbl = (struct IOleClientSiteVtbl *)&off_7960C8;
  v1[7].lpVtbl = (struct IOleClientSiteVtbl *)hWnd;
  v1[8].lpVtbl = nullptr;
  if ( OleCreate(&stru_743310, &stru_743350, 1u, nullptr, v1 + 3, &pStg, &ppvObj) != 0 )
  {
    GlobalFree(v2);
    return -2;
  }
  else
  {
    v2->lpVtbl = (struct IOleClientSiteVtbl *)ppvObj;
    SetWindowLongA(hWnd, -21, (LONG)v2);
    (*(void (/*stdcall*/ **)(LPVOID, _UNKNOWN **, uint32_t))(*(uint32_t *)ppvObj + 20))(ppvObj, &off_73F25C, 0);
    GetClientRect(hWnd, &Rect);
    if ( OleSetContainedObject((LPUNKNOWN)ppvObj, true) != 0
      || (*(int (/*stdcall*/ **)(LPVOID, int, uint32_t, IOleClientSite *, int, HWND, struct tagRECT *))(*(uint32_t *)ppvObj
                                                                                                  + 44))(
           ppvObj,
           -1,
           0,
           v4,
           -1,
           hWnd,
           &Rect) != 0
      || (**(int (/*stdcall*/ ***)(LPVOID, const IID *, int *))ppvObj)(ppvObj, &stru_743330, &pObj2) != 0 )
    {
      sub_652880(hWnd);
      return -3;
    }
    else
    {
      GetClientRect(hWnd, &Rect);
      (*(void (/*stdcall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 88))(pObj2, 0);
      (*(void (/*stdcall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 96))(pObj2, 0);
      (*(void (/*stdcall*/ **)(int, LONG))(*(uint32_t *)pObj2 + 104))(pObj2, Rect.right);
      (*(void (/*stdcall*/ **)(int, LONG))(*(uint32_t *)pObj2 + 112))(pObj2, Rect.bottom);
      (**(void (/*stdcall*/ ***)(int, void *, int *))pObj2)(pObj2, &unk_743390, &pObj);
      (*(void (/*stdcall*/ **)(int, int *, int *))(*(uint32_t *)pObj + 16))(pObj, &dword_743320, &pObj3);
      (*(void (/*stdcall*/ **)(int, IOleClientSite *, uint8_t *))(*(uint32_t *)pObj3 + 20))(pObj3, v7, v6);
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj + 8))(pObj);
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj2 + 8))(pObj2);
      return 0;
    }
  }
}



// ------------------------------------------------------------
// 0x652A70 sub_652A70
// ------------------------------------------------------------
// 【解读】
//   Navigate: MultiByteToWideChar + SysAllocString(BSTR URL) → Variant 打包 → 浏览器控件 Navigate
//    → VariantClear。内嵌浏览器的 URL 跳转入口。
// ------------------------------------------------------------
int /*cdecl*/ sub_652A70(HWND hWnd, LPCCH lpMultiByteStr)
{
  uint32_t *WindowLongA; // eax
  int v3; // edi
  WCHAR *v4; // eax
  OLECHAR *v5; // esi
  VARIANTARG pvarg; // [esp+0h] [ebp-14h] BYREF
  int pObj; // [esp+10h] [ebp-4h] BYREF

  WindowLongA = (uint32_t *)GetWindowLongA(hWnd, -21);
  if ( (**(int (/*stdcall*/ ***)(uint32_t, const IID *, int *))*WindowLongA)(*WindowLongA, &stru_743330, &pObj) != 0 )
    return -5;
  VariantInit(&pvarg);
  pvarg.vt = 8;
  v3 = MultiByteToWideChar(0, 0, lpMultiByteStr, -1, nullptr, 0);
  v4 = (WCHAR *)GlobalAlloc(0, 2 * v3);
  v5 = v4;
  if ( v4 != nullptr
    && (MultiByteToWideChar(0, 0, lpMultiByteStr, -1, v4, v3),
        pvarg.lVal = (LONG)SysAllocString(v5),
        GlobalFree(v5),
        pvarg.lVal != 0) )
  {
    (*(void (/*stdcall*/ **)(int, VARIANTARG *, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj + 208))(
      pObj,
      &pvarg,
      0,
      0,
      0,
      0);
    VariantClear(&pvarg);
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj + 8))(pObj);
    return 0;
  }
  else
  {
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj + 8))(pObj);
    return -6;
  }
}



// ------------------------------------------------------------
// 0x652B50 sub_652B50
// ------------------------------------------------------------
// 【解读】
//   浏览器宿主 WndProc: OleUninitialize / GetParent / SetFocus / EnableWindow / DefWindowProcA 分发。
// ------------------------------------------------------------
LRESULT /*stdcall*/ sub_652B50(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  UINT v4; // ebx
  HWND Parent; // eax
  HWND v7; // esi
  void (/*stdcall*/ ****WindowLongA)(uint32_t, const IID *, int *); // eax
  void (/*stdcall*/ ***v9)(uint32_t, const IID *, int *); // eax
  void (/*stdcall*/ ***v10)(uint32_t, void *, UINT *); // [esp+4h] [ebp-Ch] BYREF
  void (/*stdcall*/ ***v11)(uint32_t, void *, LPARAM *); // [esp+8h] [ebp-8h] BYREF
  int pObj; // [esp+Ch] [ebp-4h] BYREF

  v4 = Msg;
  switch ( Msg )
  {
    case 1u:
      if ( sub_6528C0(hWnd) != 0 )
        return -1;
      ++byte_9B9548;
      return 0;
    case 0x10u:
      sub_652880(hWnd);
      if ( --byte_9B9548 == 0 )
        OleUninitialize();
      Parent = GetParent(hWnd);
      v7 = Parent;
      if ( Parent != nullptr )
      {
        SetFocus(Parent);
        EnableWindow(v7, true);
      }
      break;
    case 0x317u:
      pObj = 0;
      v11 = nullptr;
      lParam = 0;
      v10 = nullptr;
      Msg = 0;
      WindowLongA = (void (/*stdcall*/ ****)(uint32_t, const IID *, int *))GetWindowLongA(hWnd, -21);
      if ( WindowLongA == nullptr )
        return 0;
      v9 = *WindowLongA;
      if ( v9 == nullptr )
        return 0;
      (**v9)(v9, &stru_743330, &pObj);
      if ( pObj == 0 )
        return 0;
      (*(void (/*stdcall*/ **)(int, void (/*stdcall*/ ****)(uint32_t, void *, LPARAM *)))(*(uint32_t *)pObj + 72))(pObj, &v11);
      if ( v11 == nullptr )
        return 0;
      (**v11)(v11, &unk_7433A0, &lParam);
      if ( lParam == 0 )
        return 0;
      (*(void (/*stdcall*/ **)(LPARAM, void (/*stdcall*/ ****)(uint32_t, void *, UINT *)))(*(uint32_t *)lParam + 36))(
        lParam,
        &v10);
      if ( v10 == nullptr )
        return 0;
      (**v10)(v10, &unk_7433B0, &Msg);
      if ( Msg == 0 )
        return 0;
      (*(void (/*stdcall*/ **)(UINT, WPARAM))(*(uint32_t *)Msg + 12))(Msg, wParam);
      (*(void (/*stdcall*/ **)(UINT))(*(uint32_t *)Msg + 8))(Msg);
      (*(void (/*stdcall*/ **)(LPARAM))(*(uint32_t *)lParam + 8))(lParam);
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj + 8))(pObj);
      return 1;
    default:
      break;
  }
  return DefWindowProcA(hWnd, v4, wParam, lParam);
}



// ------------------------------------------------------------
// 0x652CC0 sub_652CC0
// ------------------------------------------------------------
BOOL /*stdcall*/ sub_652CC0(HWND hWnd)
{
  void (/*stdcall*/ ****WindowLongA)(uint32_t, const IID *, int *); // eax
  void (/*stdcall*/ ***v2)(uint32_t, const IID *, int *); // eax
  int pObj; // [esp+0h] [ebp-4h] BYREF

  pObj = 0;
  WindowLongA = (void (/*stdcall*/ ****)(uint32_t, const IID *, int *))GetWindowLongA(hWnd, -21);
  if ( WindowLongA == nullptr )
    return false;
  v2 = *WindowLongA;
  if ( v2 == nullptr )
    return false;
  (**v2)(v2, &stru_743330, &pObj);
  if ( pObj == 0 )
    return false;
  (*(void (/*stdcall*/ **)(int, HWND *, int))(*(uint32_t *)pObj + 224))(pObj, &hWnd, pObj);
  (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pObj + 8))(pObj);
  return hWnd != (HWND)4;
}



// ------------------------------------------------------------
// 0x652D30 sub_652D30
// ------------------------------------------------------------
// 【解读】
//   ★ 内嵌浏览器宿主窗口注册: OleInitialize → RegisterClassExA("Browser Example") →
//     CreateWindowExA（标题 "NEOPLE_WEB"，与 log_dump.cpp 0x4090D0 抓屏目标对应）→ EnableWindow。
//     "Browser Example" 为 Neople 集成 IE 控件时的工程残留命名。
// ------------------------------------------------------------
HWND /*stdcall*/ sub_652D30(HWND hWndParent, HINSTANCE hInstance, int *pDwArg3, int nArg4)
{
  HWND Window; // edi
  WNDCLASSEXA pBuf; // [esp+0h] [ebp-30h] BYREF

  if ( byte_9B9548 != 0 && OleInitialize(nullptr) != 0 )
    return nullptr;
  memset(&pBuf, 0, sizeof(pBuf));
  pBuf.cbSize = 48;
  pBuf.hInstance = hInstance;
  pBuf.lpfnWndProc = sub_652B50;
  pBuf.lpszClassName = "Browser Example";
  RegisterClassExA(&pBuf);
  Window = CreateWindowExA(
             0,
             "Browser Example",
             "NEOPLE_WEB",
             0x80000000,
             *pDwArg3,
             pDwArg3[1],
             pDwArg3[2],
             pDwArg3[3],
             hWndParent,
             nullptr,
             hInstance,
             nullptr);
  if ( nArg4 == 1 )
    EnableWindow(hWndParent, false);
  return Window;
}



// ============================================================
// SECTION 0x652DE0 — ★★★ zlib 1.2.3 静态链接（uncompress / inflateInit2_ / inflate / inflate_table / inflate_fast(MMX) / crc32 / zalloc/zfree；版本串 "1.2.3"）
// ============================================================
// ------------------------------------------------------------
// 0x652DE0 sub_652DE0
// ------------------------------------------------------------
int /*stdcall*/ sub_652DE0(HWND hWnd, LPCCH lpMultiByteStr)
{
  return sub_652A70(hWnd, lpMultiByteStr);
}



// ------------------------------------------------------------
// 0x652E00 sub_652E00
// ------------------------------------------------------------
// 【解读】
//   ★ uncompress()（zlib 1.2.3）: inflateInit_(version="1.2.3", sizeof(z_stream)=56) →
//     inflate(4=Z_FINISH) → inflateEnd；Z_OK → 输出总长；Z_BUF_ERROR(-3)/Z_DATA_ERROR 透传。
//     ★ 被 gfx_texture.cpp 0x4116A0/0x411B30/0x412150/0x412700 调用 —— IMG 图像块解压入口。
// ------------------------------------------------------------
int /*cdecl*/ sub_652E00(int nArg1, int *pDwArg2, uint8_t *uArg3, int nArg4)
{
  int v4; // eax
  int result; // eax
  int v6; // esi
  uint8_t *uArg32; // [esp+4h] [ebp-38h] BYREF
  int nArg42; // [esp+8h] [ebp-34h]
  int nArg12; // [esp+10h] [ebp-2Ch]
  int v10; // [esp+14h] [ebp-28h]
  int v11; // [esp+18h] [ebp-24h]
  int v12; // [esp+24h] [ebp-18h]
  int v13; // [esp+28h] [ebp-14h]

  nArg42 = nArg4;
  uArg32 = uArg3;
  v4 = *pDwArg2;
  nArg12 = nArg1;
  v10 = v4;
  v12 = 0;
  v13 = 0;
  result = sub_652FE0(&uArg32, "1.2.3", 56);
  if ( result == 0 )
  {
    v6 = sub_653120(&uArg32, 4);
    if ( v6 == 1 )
    {
      *pDwArg2 = v11;
      return sub_654750(&uArg32);
    }
    else
    {
      sub_654750(&uArg32);
      if ( v6 == 2 || v6 == -5 && nArg42 == 0 )
        return -3;
      else
        return v6;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x652EB0 sub_652EB0
// ------------------------------------------------------------
// 【解读】
//   inflateReset(): 状态复位（窗口 0x8000、window 指针 +332、计数清零）。zlib 标准。
// ------------------------------------------------------------
int /*cdecl*/ sub_652EB0(uint32_t *pArg1)
{
  uint32_t *v1; // eax

  if ( pArg1 == nullptr )
    return -2;
  v1 = (uint32_t *)pArg1[7];
  if ( v1 == nullptr )
    return -2;
  v1[7] = 0;
  pArg1[5] = 0;
  pArg1[2] = 0;
  pArg1[6] = 0;
  pArg1[12] = 1;
  *v1 = 0;
  v1[1] = 0;
  v1[3] = 0;
  v1[8] = 0;
  v1[10] = 0;
  v1[11] = 0;
  v1[12] = 0;
  v1[14] = 0;
  v1[15] = 0;
  v1[5] = 0x8000;
  v1[27] = v1 + 332;
  v1[20] = v1 + 332;
  v1[19] = v1 + 332;
  return 0;
}



// ------------------------------------------------------------
// 0x652F10 sub_652F10
// ------------------------------------------------------------
// 【解读】
//   inflateInit2_(): 版本校验（version 首字节必须为 0x31 即字符1 + stream_size==56）→ zcalloc 分配 9520B 状态
//    → windowBits>>4+1 建窗口。zlib 标准（windowBits 语义见 zlib 源 inftrees/inflate）。
// ------------------------------------------------------------
int /*cdecl*/ sub_652F10(uint32_t *pArg1, int nArg2, uint8_t *uArg3, int nArg4)
{
  bool v4; // zf
  uint32_t *v5; // eax
  int nArg22; // ecx

  if ( uArg3 == nullptr || *uArg3 != 49 || nArg4 != 56 )
    return -6;
  if ( pArg1 != nullptr )
  {
    v4 = pArg1[8] == 0;
    pArg1[6] = 0;
    if ( v4 )
    {
      pArg1[8] = sub_6547A0;
      pArg1[10] = 0;
    }
    if ( pArg1[9] == 0 )
      pArg1[9] = sub_6547C0;
    v5 = (uint32_t *)((int (/*cdecl*/ *)(uint32_t, int, int))pArg1[8])(pArg1[10], 1, 9520);
    if ( v5 == nullptr )
      return -4;
    nArg22 = nArg2;
    pArg1[7] = v5;
    if ( nArg2 >= 0 )
    {
      v5[2] = (nArg2 >> 4) + 1;
      if ( nArg2 < 48 )
        nArg22 = nArg2 & 0xF;
    }
    else
    {
      v5[2] = 0;
      nArg22 = -nArg2;
    }
    if ( nArg22 >= 8 && nArg22 <= 15 )
    {
      v5[9] = nArg22;
      v5[13] = 0;
      return sub_652EB0(pArg1);
    }
    ((void (/*cdecl*/ *)(uint32_t, uint32_t *))pArg1[9])(pArg1[10], v5);
    pArg1[7] = 0;
  }
  return -2;
}



// ------------------------------------------------------------
// 0x652FE0 sub_652FE0
// ------------------------------------------------------------
int /*cdecl*/ sub_652FE0(uint32_t *uArg1, uint8_t *uArg2, int nArg3)
{
  return sub_652F10(uArg1, 15, uArg2, nArg3);
}



// ------------------------------------------------------------
// 0x653000 sub_653000
// ------------------------------------------------------------
// 【解读】
//   inflate 内部子过程（78 行，间接调用密集）【推断：fixed tables/边界分支】。zlib 标准体。
// ------------------------------------------------------------
int /*usercall*/ sub_653000@<eax>(int nArg1@<eax>, int pArg2)
{
  int v3; // ebx
  int v5; // eax
  int v7; // edx
  unsigned int v8; // ecx
  unsigned int v9; // esi
  int v10; // ecx
  unsigned int v11; // ecx
  unsigned int v12; // eax
  unsigned int v13; // eax
  unsigned int v14; // edx
  unsigned int v15; // edx
  unsigned int v16; // [esp+14h] [ebp+4h]

  v3 = *(uint32_t *)(pArg2 + 28);
  if ( *(uint32_t *)(v3 + 52) == 0 )
  {
    v5 = (*(int (/*cdecl*/ **)(uint32_t, int, int))(pArg2 + 32))(*(uint32_t *)(pArg2 + 40), 1 << *(uint32_t *)(v3 + 36), 1);
    *(uint32_t *)(v3 + 52) = v5;
    if ( v5 == 0 )
      return 1;
  }
  if ( *(uint32_t *)(v3 + 40) == 0 )
  {
    v7 = 1 << *(uint32_t *)(v3 + 36);
    *(uint32_t *)(v3 + 48) = 0;
    *(uint32_t *)(v3 + 44) = 0;
    *(uint32_t *)(v3 + 40) = v7;
  }
  v8 = *(uint32_t *)(v3 + 40);
  v9 = nArg1 - *(uint32_t *)(pArg2 + 16);
  if ( v9 < v8 )
  {
    v11 = v8 - *(uint32_t *)(v3 + 48);
    v16 = v11;
    if ( v11 > v9 )
    {
      v11 = v9;
      v16 = v9;
    }
    qmemcpy((void *)(*(uint32_t *)(v3 + 48) + *(uint32_t *)(v3 + 52)), (const void *)(*(uint32_t *)(pArg2 + 12) - v9), v11);
    v12 = v9 - v16;
    if ( v9 == v16 )
    {
      v13 = *(uint32_t *)(v3 + 40);
      v14 = v16 + *(uint32_t *)(v3 + 48);
      *(uint32_t *)(v3 + 48) = v14;
      if ( v14 == v13 )
        *(uint32_t *)(v3 + 48) = 0;
      v15 = *(uint32_t *)(v3 + 44);
      if ( v15 < v13 )
        *(uint32_t *)(v3 + 44) = v16 + v15;
      return 0;
    }
    else
    {
      qmemcpy(*(void **)(v3 + 52), (const void *)(*(uint32_t *)(pArg2 + 12) - v12), v12);
      *(uint32_t *)(v3 + 48) = v12;
      *(uint32_t *)(v3 + 44) = *(uint32_t *)(v3 + 40);
      return 0;
    }
  }
  else
  {
    qmemcpy(*(void **)(v3 + 52), (const void *)(*(uint32_t *)(pArg2 + 12) - *(uint32_t *)(v3 + 40)), *(uint32_t *)(v3 + 40));
    v10 = *(uint32_t *)(v3 + 40);
    *(uint32_t *)(v3 + 48) = 0;
    *(uint32_t *)(v3 + 44) = v10;
    return 0;
  }
}



// ------------------------------------------------------------
// 0x653120 sub_653120
// ------------------------------------------------------------
// 【解读】
//   ★★★ inflate() 主状态机（1477 行，zlib 1.2.3 直证）:
//     错误串 "incorrect header check" / "unknown compression method" / "invalid window size" /
//     "unknown header flags set" / "header crc mismatch" / "invalid block type" /
//     "invalid stored block lengths" / "invalid distance code" / "invalid distance too far back" /
//     "invalid literal/length code"。0x65 区 zlib 群的核心；IMG 解码（0x41 区）的底层。
// ------------------------------------------------------------
int /*cdecl*/ sub_653120(uint8_t **pArg1, int nArg2)
{
  int *v2; // ebx
  unsigned int v3; // edx
  unsigned int v4; // ebp
  uint8_t *v5; // esi
  unsigned int v6; // edi
  unsigned int v7; // eax
  int v8; // ecx
  int result; // eax
  int v10; // edx
  int v11; // eax
  uint8_t v12; // cl
  unsigned int v13; // ecx
  int v14; // eax
  int v15; // edx
  uint32_t *v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // ecx
  unsigned int v24; // ecx
  int v25; // edx
  int v26; // edx
  int v27; // edi
  unsigned int v28; // edx
  int v29; // edi
  int v30; // eax
  unsigned int v31; // ecx
  int v32; // edx
  int v33; // ecx
  unsigned int v34; // edx
  unsigned int v35; // ecx
  int v36; // ecx
  unsigned int v37; // ecx
  int v38; // edx
  int v39; // ecx
  unsigned int v40; // edx
  unsigned int v41; // ecx
  int v42; // ecx
  int v43; // edx
  int v44; // eax
  int v45; // eax
  int v46; // edx
  uint16_t v47; // dx
  int v48; // eax
  int v49; // eax
  int v50; // ecx
  int v51; // edx
  int v52; // ecx
  unsigned int v53; // eax
  unsigned int v54; // ebp
  int v55; // ecx
  int v56; // edx
  int v57; // ecx
  unsigned int v58; // ecx
  unsigned int v59; // edx
  int v60; // edx
  int v61; // ecx
  unsigned int v62; // eax
  char v63; // dl
  unsigned int v64; // ecx
  unsigned int v65; // edx
  int v66; // edx
  char v67; // cl
  unsigned int v68; // ecx
  unsigned int v69; // edx
  unsigned int v70; // ecx
  int v71; // edx
  unsigned int v72; // ecx
  int v73; // edx
  int v74; // ecx
  int v75; // edx
  int v76; // ecx
  int v77; // ecx
  int v78; // edx
  int v79; // edx
  unsigned int v80; // eax
  int v81; // edi
  int v82; // edx
  unsigned int v83; // eax
  int16_t v84; // dx
  int v85; // edx
  int v86; // ecx
  char *v87; // ecx
  unsigned int v88; // edx
  unsigned int v89; // edx
  uint8_t *v90; // edx
  int v91; // edx
  int v92; // ecx
  int v93; // edx
  unsigned int v94; // ecx
  int v95; // edx
  int v96; // ecx
  uint8_t *v97; // edx
  int v98; // edx
  int v99; // ecx
  int v100; // edx
  unsigned int v101; // ecx
  int v102; // edx
  int v103; // ecx
  unsigned int v104; // ecx
  unsigned int v105; // ecx
  unsigned int v106; // edx
  int v107; // edx
  char *v108; // edx
  char *v109; // ecx
  bool v110; // zf
  char *v111; // ecx
  int v112; // edx
  unsigned int v113; // ecx
  int v114; // edx
  int v115; // edx
  int v116; // eax
  int v117; // ecx
  uint16_t v118; // dx
  int v119; // edx
  int v120; // eax
  unsigned int v121; // ebp
  unsigned int v122; // edi
  uint8_t *v123; // edx
  int v124; // eax
  int v125; // eax
  unsigned int i; // [esp+4h] [ebp-38h]
  unsigned int v127; // [esp+8h] [ebp-34h]
  uint8_t *v128; // [esp+Ch] [ebp-30h]
  unsigned int v129; // [esp+10h] [ebp-2Ch]
  unsigned int v130; // [esp+10h] [ebp-2Ch]
  unsigned int v131; // [esp+10h] [ebp-2Ch]
  unsigned int v132; // [esp+10h] [ebp-2Ch]
  unsigned int v133; // [esp+10h] [ebp-2Ch]
  int v134; // [esp+10h] [ebp-2Ch]
  int v135; // [esp+10h] [ebp-2Ch]
  int v136; // [esp+10h] [ebp-2Ch]
  unsigned int v137; // [esp+10h] [ebp-2Ch]
  unsigned int v138; // [esp+14h] [ebp-28h]
  unsigned int v139; // [esp+18h] [ebp-24h] BYREF
  char *v140; // [esp+1Ch] [ebp-20h]
  int v141; // [esp+20h] [ebp-1Ch]
  unsigned int v142; // [esp+24h] [ebp-18h]
  int v143; // [esp+28h] [ebp-14h]
  unsigned int v144; // [esp+2Ch] [ebp-10h]
  unsigned int v145; // [esp+30h] [ebp-Ch]
  unsigned int v146; // [esp+34h] [ebp-8h]

  if ( pArg1 == nullptr )
    return -2;
  v2 = (int *)pArg1[7];
  if ( v2 == nullptr || pArg1[3] == nullptr || *pArg1 == nullptr && pArg1[1] != nullptr )
    return -2;
  if ( *v2 == 11 )
    *v2 = 12;
  v3 = (unsigned int)pArg1[4];
  v4 = v2[15];
  v5 = *pArg1;
  v6 = (unsigned int)pArg1[1];
  v7 = v2[14];
  v140 = (char *)pArg1[3];
  v8 = *v2;
  v138 = v3;
  v128 = v5;
  v127 = v6;
  i = v7;
  v145 = v6;
  v142 = v3;
  v143 = 0;
  while ( 2 )
  {
    switch ( v8 )
    {
      case 0:
        if ( v2[2] == 0 )
        {
          *v2 = 12;
          goto LABEL_297;
        }
        for ( ; v4 < 0x10; v128 = v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v10 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v10;
          ++v5;
          i = v7;
        }
        if ( (v2[2] & 2) != 0 && v7 == 35615 )
        {
          v4 = 0;
          v2[6] = sub_655990(0, 0, 0);
          LOWORD(v139) = -29921;
          v2[6] = sub_655990(v2[6], &v139, 2);
          i = 0;
          *v2 = 1;
          v7 = 0;
          goto LABEL_297;
        }
        v11 = v2[8];
        v2[4] = 0;
        if ( v11 != 0 )
          *(uint32_t *)(v11 + 48) = -1;
        if ( (v2[2] & 1) == 0 || ((i >> 8) + ((uint8_t)i << 8)) % 0x1F != 0 )
        {
          pArg1[6] = "incorrect header check";
          v7 = i;
          goto LABEL_296;
        }
        v12 = i;
        if ( (i & 0xF) != 8 )
        {
          pArg1[6] = "unknown compression method";
          v7 = i;
          goto LABEL_296;
        }
        i >>= 4;
        v13 = (v12 >> 4) + 8;
        v4 -= 4;
        if ( v13 > v2[9] )
        {
          v7 = i;
          pArg1[6] = "invalid window size";
          goto LABEL_296;
        }
        v4 = 0;
        v2[5] = 1 << v13;
        v14 = sub_655460(0, 0, 0);
        v2[6] = v14;
        pArg1[12] = (uint8_t *)v14;
        *v2 = ~BYTE1(i) & 2 | 9;
        i = 0;
        v7 = 0;
        goto LABEL_297;
      case 1:
        for ( ; v4 < 0x10; v128 = v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v15 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v15;
          ++v5;
          i = v7;
        }
        v2[4] = v7;
        if ( (uint8_t)v7 != 8 )
        {
          pArg1[6] = "unknown compression method";
          goto LABEL_296;
        }
        if ( (v7 & 0xE000) != 0 )
        {
          pArg1[6] = "unknown header flags set";
          goto LABEL_296;
        }
        v16 = (uint32_t *)v2[8];
        if ( v16 != nullptr )
          *v16 = (v7 & 0x100) != 0;
        if ( (v2[4] & 0x200) != 0 )
        {
          LOWORD(v139) = i;
          v2[6] = sub_655990(v2[6], &v139, 2);
        }
        v7 = 0;
        v4 = 0;
        *v2 = 2;
        do
        {
LABEL_44:
          if ( v6 == 0 )
            goto LABEL_304;
          v17 = *v5 << v4;
          --v6;
          v4 += 8;
          v7 += v17;
          ++v5;
          i = v7;
        }
        while ( v4 < 0x20 );
LABEL_46:
        v18 = v2[8];
        if ( v18 != 0 )
          *(uint32_t *)(v18 + 4) = v7;
        if ( (v2[4] & 0x200) != 0 )
        {
          v139 = i;
          v2[6] = sub_655990(v2[6], &v139, 4);
        }
        v7 = 0;
        v4 = 0;
        *v2 = 3;
        do
        {
LABEL_52:
          if ( v6 == 0 )
            goto LABEL_304;
          v19 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v19;
          ++v5;
          LOWORD(i) = v7;
          v128 = v5;
        }
        while ( v4 < 0x10 );
LABEL_54:
        v20 = v2[8];
        if ( v20 != 0 )
        {
          *(uint32_t *)(v20 + 8) = (uint8_t)v7;
          *(uint32_t *)(v2[8] + 12) = v7 >> 8;
        }
        if ( (v2[4] & 0x200) != 0 )
        {
          LOWORD(v139) = i;
          v2[6] = sub_655990(v2[6], &v139, 2);
        }
        v7 = 0;
        i = 0;
        v4 = 0;
        *v2 = 4;
LABEL_59:
        if ( (v2[4] & 0x400) != 0 )
        {
          if ( v4 < 0x10 )
          {
            while ( v6 != 0 )
            {
              v21 = *v5 << v4;
              --v6;
              v4 += 8;
              v127 = v6;
              v7 += v21;
              ++v5;
              LOWORD(i) = v7;
              v128 = v5;
              if ( v4 >= 0x10 )
                goto LABEL_63;
            }
            goto LABEL_304;
          }
LABEL_63:
          v22 = v2[8];
          v2[16] = v7;
          if ( v22 != 0 )
            *(uint32_t *)(v22 + 20) = v7;
          if ( (v2[4] & 0x200) != 0 )
          {
            LOWORD(v139) = i;
            v2[6] = sub_655990(v2[6], &v139, 2);
          }
          v7 = 0;
          i = 0;
          v4 = 0;
        }
        else
        {
          v23 = v2[8];
          if ( v23 != 0 )
            *(uint32_t *)(v23 + 16) = 0;
        }
        *v2 = 5;
LABEL_71:
        if ( (v2[4] & 0x400) != 0 )
        {
          v24 = v2[16];
          v129 = v24;
          if ( v24 > v6 )
          {
            v24 = v6;
            v129 = v6;
          }
          if ( v24 != 0 )
          {
            v25 = v2[8];
            if ( v25 != 0 )
            {
              v144 = *(uint32_t *)(v25 + 16);
              if ( v144 != 0 )
              {
                v26 = v2[8];
                v27 = *(uint32_t *)(v26 + 20);
                v28 = *(uint32_t *)(v26 + 24);
                v29 = v27 - v2[16];
                if ( v24 + v29 > v28 )
                  v24 = v28 - v29;
                qmemcpy((void *)(v144 + v29), v128, v24);
                v24 = v129;
                v6 = v127;
                v5 = v128;
              }
            }
            if ( (v2[4] & 0x200) != 0 )
            {
              v30 = sub_655990(v2[6], v5, v129);
              v24 = v129;
              v2[6] = v30;
              v7 = i;
            }
            v6 -= v24;
            v5 += v24;
            v127 = v6;
            v128 = v5;
            v2[16] -= v24;
          }
          if ( v2[16] != 0 )
            goto LABEL_304;
        }
        v2[16] = 0;
        *v2 = 6;
LABEL_85:
        if ( (v2[4] & 0x800) != 0 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v31 = 0;
          do
          {
            v32 = v5[v31];
            v130 = v31 + 1;
            v33 = v2[8];
            v141 = v32;
            if ( v33 != 0 )
            {
              v144 = *(uint32_t *)(v33 + 28);
              if ( v144 != 0 )
              {
                v34 = v2[16];
                if ( v34 < *(uint32_t *)(v33 + 32) )
                {
                  v35 = v144;
                  v6 = v127;
                  v144 = v7;
                  *(uint8_t *)(v35 + v34) = v141;
                  ++v2[16];
                  v7 = v144;
                }
              }
            }
            if ( v141 == 0 )
              break;
            v31 = v130;
          }
          while ( v130 < v6 );
          if ( (v2[4] & 0x200) != 0 )
          {
            v2[6] = sub_655990(v2[6], v5, v130);
            v7 = i;
          }
          v6 -= v130;
          v5 += v130;
          v127 = v6;
          v128 = v5;
          if ( v141 != 0 )
            goto LABEL_304;
        }
        else
        {
          v36 = v2[8];
          if ( v36 != 0 )
            *(uint32_t *)(v36 + 28) = 0;
        }
        v2[16] = 0;
        *v2 = 7;
LABEL_101:
        if ( (v2[4] & 0x1000) != 0 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v37 = 0;
          do
          {
            v38 = v5[v37];
            v131 = v37 + 1;
            v39 = v2[8];
            v141 = v38;
            if ( v39 != 0 )
            {
              v144 = *(uint32_t *)(v39 + 36);
              if ( v144 != 0 )
              {
                v40 = v2[16];
                if ( v40 < *(uint32_t *)(v39 + 40) )
                {
                  v41 = v144;
                  v6 = v127;
                  v144 = v7;
                  *(uint8_t *)(v41 + v40) = v141;
                  ++v2[16];
                  v7 = v144;
                }
              }
            }
            if ( v141 == 0 )
              break;
            v37 = v131;
          }
          while ( v131 < v6 );
          if ( (v2[4] & 0x200) != 0 )
          {
            v2[6] = sub_655990(v2[6], v5, v131);
            v7 = i;
          }
          v6 -= v131;
          v5 += v131;
          v127 = v6;
          v128 = v5;
          if ( v141 != 0 )
            goto LABEL_304;
        }
        else
        {
          v42 = v2[8];
          if ( v42 != 0 )
            *(uint32_t *)(v42 + 36) = 0;
        }
        *v2 = 8;
LABEL_117:
        if ( (v2[4] & 0x200) != 0 )
        {
          if ( v4 < 0x10 )
          {
            while ( v6 != 0 )
            {
              v43 = *v5 << v4;
              --v6;
              v4 += 8;
              v127 = v6;
              v7 += v43;
              ++v5;
              i = v7;
              v128 = v5;
              if ( v4 >= 0x10 )
                goto LABEL_121;
            }
            goto LABEL_304;
          }
LABEL_121:
          if ( v7 != (uint16_t)v2[6] )
          {
            pArg1[6] = "header crc mismatch";
            goto LABEL_296;
          }
          v4 = 0;
          i = 0;
        }
        v44 = v2[8];
        if ( v44 != 0 )
        {
          *(uint32_t *)(v44 + 44) = (v2[4] >> 9) & 1;
          *(uint32_t *)(v2[8] + 48) = 1;
        }
        v45 = sub_655990(0, 0, 0);
        v2[6] = v45;
        pArg1[12] = (uint8_t *)v45;
        v7 = i;
        *v2 = 11;
        goto LABEL_297;
      case 2:
        if ( v4 < 0x20 )
          goto LABEL_44;
        goto LABEL_46;
      case 3:
        if ( v4 < 0x10 )
          goto LABEL_52;
        goto LABEL_54;
      case 4:
        goto LABEL_59;
      case 5:
        goto LABEL_71;
      case 6:
        goto LABEL_85;
      case 7:
        goto LABEL_101;
      case 8:
        goto LABEL_117;
      case 9:
        for ( ; v4 < 0x20; v128 = v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v46 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v46;
          ++v5;
          BYTE2(i) = BYTE2(v7);
        }
        LOBYTE(v47) = 0;
        HIBYTE(v47) = BYTE2(i);
        v48 = v47 + (((v7 << 16) + (v7 & 0xFF00)) << 8) + HIBYTE(v7);
        v2[6] = v48;
        pArg1[12] = (uint8_t *)v48;
        v7 = 0;
        i = 0;
        v4 = 0;
        *v2 = 10;
LABEL_131:
        if ( v2[3] == 0 )
        {
          pArg1[3] = (uint8_t *)v140;
          pArg1[1] = (uint8_t *)v6;
          *pArg1 = v5;
          pArg1[4] = (uint8_t *)v138;
          v2[15] = v4;
          v2[14] = v7;
          return 2;
        }
        v49 = sub_655460(0, 0, 0);
        v2[6] = v49;
        pArg1[12] = (uint8_t *)v49;
        v7 = i;
        *v2 = 11;
LABEL_133:
        if ( nArg2 == 5 )
          goto LABEL_304;
LABEL_134:
        if ( v2[1] != 0 )
        {
          v50 = v4 & 7;
          v7 >>= v50;
          v4 -= v50;
          *v2 = 24;
          i = v7;
        }
        else
        {
          if ( v4 < 3 )
          {
            while ( v6 != 0 )
            {
              v51 = *v5 << v4;
              --v6;
              v4 += 8;
              v127 = v6;
              v7 += v51;
              v128 = ++v5;
              if ( v4 >= 3 )
                goto LABEL_139;
            }
            goto LABEL_304;
          }
LABEL_139:
          v52 = v7 & 1;
          v53 = v7 >> 1;
          v2[1] = v52;
          v54 = v4 - 1;
          switch ( v53 & 3 )
          {
            case 0u:
              v7 = v53 >> 2;
              *v2 = 13;
              i = v7;
              v4 = v54 - 2;
              break;
            case 1u:
              v7 = v53 >> 2;
              v2[19] = (int)"`\a";
              v2[21] = 9;
              v2[20] = (int)&unk_73FA80;
              v2[22] = 5;
              *v2 = 18;
              i = v7;
              v4 = v54 - 2;
              break;
            case 2u:
              v7 = v53 >> 2;
              *v2 = 15;
              i = v7;
              v4 = v54 - 2;
              break;
            case 3u:
              pArg1[6] = "invalid block type";
              *v2 = 27;
              v7 = v53 >> 2;
              i = v7;
              v4 = v54 - 2;
              break;
          }
        }
        goto LABEL_297;
      case 10:
        goto LABEL_131;
      case 11:
        goto LABEL_133;
      case 12:
        goto LABEL_134;
      case 13:
        v55 = v4 & 7;
        v7 >>= v55;
        v4 -= v55;
        for ( i = v7; v4 < 0x20; v128 = v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v56 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v56;
          ++v5;
          i = v7;
        }
        v57 = (uint16_t)v7;
        if ( (uint16_t)v7 != ~v7 >> 16 )
        {
          pArg1[6] = "invalid stored block lengths";
          goto LABEL_296;
        }
        v7 = 0;
        v2[16] = v57;
        i = 0;
        v4 = 0;
        *v2 = 14;
LABEL_150:
        v58 = v2[16];
        v132 = v58;
        if ( v58 == 0 )
          goto LABEL_228;
        if ( v58 > v6 )
        {
          v58 = v6;
          v132 = v6;
        }
        if ( v58 > v138 )
        {
          v58 = v138;
          v132 = v138;
        }
        if ( v58 == 0 )
          goto LABEL_304;
        qmemcpy(v140, v128, v58);
        v127 -= v132;
        v128 += v132;
        v59 = v2[16] - v132;
        v138 -= v132;
        v6 = v127;
        v140 += v132;
        v5 = v128;
        v2[16] = v59;
        goto LABEL_297;
      case 14:
        goto LABEL_150;
      case 15:
        for ( ; v4 < 0xE; v128 = ++v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v60 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v60;
        }
        v61 = (v7 & 0x1F) + 257;
        v62 = v7 >> 5;
        v63 = v62;
        v2[24] = v61;
        v62 >>= 5;
        v2[23] = (v62 & 0xF) + 4;
        v64 = v2[24];
        v65 = (v63 & 0x1F) + 1;
        v7 = v62 >> 4;
        v4 -= 14;
        v2[25] = v65;
        i = v7;
        if ( v64 > 0x11E || v65 > 0x1E )
        {
          pArg1[6] = "too many length or distance symbols";
          goto LABEL_296;
        }
        v2[26] = 0;
        *v2 = 16;
LABEL_163:
        if ( v2[26] < (unsigned int)v2[23] )
        {
          while ( v4 >= 3 )
          {
LABEL_167:
            v67 = v7;
            v7 >>= 3;
            v4 -= 3;
            i = v7;
            *((uint16_t *)v2 + (uint16_t)word_73FB00[v2[26]] + 56) = v67 & 7;
            v68 = v2[26] + 1;
            v2[26] = v68;
            if ( v68 >= v2[23] )
              goto LABEL_168;
          }
          while ( v6 != 0 )
          {
            v66 = *v5 << v4;
            --v6;
            v4 += 8;
            v127 = v6;
            v7 += v66;
            v128 = ++v5;
            if ( v4 >= 3 )
              goto LABEL_167;
          }
          goto LABEL_304;
        }
LABEL_168:
        if ( (unsigned int)v2[26] < 0x13 )
        {
          do
          {
            *((uint16_t *)v2 + (uint16_t)word_73FB00[v2[26]] + 56) = 0;
            v69 = v2[26] + 1;
            v2[26] = v69;
          }
          while ( v69 < 0x13 );
        }
        v2[27] = (int)(v2 + 332);
        v2[19] = (int)(v2 + 332);
        v2[21] = 7;
        v143 = sub_654F70(0, v2 + 28, 19, v2 + 27, v2 + 21, v2 + 188);
        v7 = i;
        if ( v143 != 0 )
        {
          pArg1[6] = "invalid code lengths set";
          goto LABEL_296;
        }
        v2[26] = 0;
        *v2 = 17;
LABEL_174:
        if ( v2[26] < (unsigned int)(v2[24] + v2[25]) )
        {
          while ( 1 )
          {
            v146 = *(uint32_t *)(v2[19] + 4 * (v7 & ((1 << v2[21]) - 1)));
            BYTE1(v70) = BYTE1(v146);
            if ( BYTE1(v146) > v4 )
              break;
LABEL_178:
            if ( HIWORD(v146) >= 0x10u )
            {
              if ( HIWORD(v146) == 16 )
              {
                v74 = BYTE1(v70);
                v134 = v74;
                if ( v4 < v74 + 2 )
                {
                  while ( v6 != 0 )
                  {
                    v75 = *v5 << v4;
                    v74 = v134;
                    --v6;
                    v4 += 8;
                    v7 += v75;
                    ++v5;
                    v127 = v6;
                    v128 = v5;
                    if ( v4 >= v134 + 2 )
                      goto LABEL_187;
                  }
                  goto LABEL_304;
                }
LABEL_187:
                v7 >>= v74;
                v4 -= v74;
                v76 = v2[26];
                i = v7;
                if ( v76 == 0 )
                {
                  pArg1[6] = "invalid bit length repeat";
                  goto LABEL_296;
                }
                v141 = *((uint16_t *)v2 + v76 + 55);
                v77 = (v7 & 3) + 3;
                v7 >>= 2;
                v4 -= 2;
              }
              else
              {
                v78 = BYTE1(v70);
                if ( HIWORD(v146) == 17 )
                {
                  if ( v4 < (unsigned int)BYTE1(v70) + 3 )
                  {
                    while ( v6 != 0 )
                    {
                      v79 = *v5 << v4;
                      --v6;
                      v4 += 8;
                      v127 = v6;
                      v7 += v79;
                      v78 = BYTE1(v70);
                      v128 = ++v5;
                      if ( v4 >= (unsigned int)BYTE1(v70) + 3 )
                        goto LABEL_193;
                    }
                    goto LABEL_304;
                  }
LABEL_193:
                  v80 = v7 >> v78;
                  v81 = -3;
                  v77 = (v80 & 7) + 3;
                  v7 = v80 >> 3;
                }
                else
                {
                  if ( v4 < (unsigned int)BYTE1(v70) + 7 )
                  {
                    while ( v6 != 0 )
                    {
                      v82 = *v5 << v4;
                      --v6;
                      v4 += 8;
                      v127 = v6;
                      v7 += v82;
                      v78 = BYTE1(v70);
                      v128 = ++v5;
                      if ( v4 >= (unsigned int)BYTE1(v70) + 7 )
                        goto LABEL_197;
                    }
                    goto LABEL_304;
                  }
LABEL_197:
                  v83 = v7 >> v78;
                  v81 = -7;
                  v77 = (v83 & 0x7F) + 11;
                  v7 = v83 >> 7;
                }
                v141 = 0;
                v4 += v81 - v78;
              }
              i = v7;
              if ( v77 + v2[26] > (unsigned int)(v2[24] + v2[25]) )
              {
                v6 = v127;
                pArg1[6] = "invalid bit length repeat";
                goto LABEL_296;
              }
              if ( v77 != 0 )
              {
                v84 = v141;
                do
                {
                  *((uint16_t *)v2 + v2[26] + 56) = v84;
                  --v77;
                  ++v2[26];
                }
                while ( v77 != 0 );
              }
              v6 = v127;
            }
            else
            {
              v72 = BYTE1(v70);
              v133 = v72;
              if ( v4 < v72 )
              {
                while ( v6 != 0 )
                {
                  v73 = *v5 << v4;
                  v72 = v133;
                  --v6;
                  v4 += 8;
                  v7 += v73;
                  ++v5;
                  v127 = v6;
                  v128 = v5;
                  if ( v4 >= v133 )
                    goto LABEL_182;
                }
                goto LABEL_304;
              }
LABEL_182:
              v7 >>= v72;
              v4 -= v72;
              *((uint16_t *)v2 + v2[26] + 56) = HIWORD(v146);
              i = v7;
              ++v2[26];
            }
            if ( v2[26] >= (unsigned int)(v2[24] + v2[25]) )
              goto LABEL_205;
          }
          while ( v6 != 0 )
          {
            v71 = *v5 << v4;
            --v6;
            v4 += 8;
            v7 += v71;
            ++v5;
            v127 = v6;
            v70 = *(uint32_t *)(v2[19] + 4 * (v7 & ((1 << v2[21]) - 1)));
            v128 = v5;
            v146 = v70;
            if ( BYTE1(v70) <= v4 )
              goto LABEL_178;
          }
          goto LABEL_304;
        }
LABEL_205:
        if ( *v2 == 27 )
          goto LABEL_297;
        v2[27] = (int)(v2 + 332);
        v2[19] = (int)(v2 + 332);
        v85 = v2[24];
        v2[21] = 9;
        v143 = sub_654F70(1, v2 + 28, v85, v2 + 27, v2 + 21, v2 + 188);
        if ( v143 != 0 )
        {
          v7 = i;
          pArg1[6] = "invalid literal/lengths set";
          goto LABEL_296;
        }
        v2[20] = v2[27];
        v86 = v2[24];
        v2[22] = 6;
        v143 = sub_654F70(2, (char *)v2 + 2 * v86 + 112, v2[25], v2 + 27, v2 + 22, v2 + 188);
        if ( v143 != 0 )
        {
          pArg1[6] = "invalid distances set";
          v7 = i;
          goto LABEL_296;
        }
        v7 = i;
        *v2 = 18;
LABEL_213:
        if ( v6 >= 6 && v138 >= 0x102 )
        {
          v87 = v140;
          pArg1[4] = (uint8_t *)v138;
          v88 = v142;
          pArg1[3] = (uint8_t *)v87;
          *pArg1 = v5;
          pArg1[1] = (uint8_t *)v6;
          v2[14] = i;
          v2[15] = v4;
          sub_6547D0(pArg1, v88);
          v89 = (unsigned int)pArg1[4];
          v5 = *pArg1;
          v6 = (unsigned int)pArg1[1];
          v7 = v2[14];
          v4 = v2[15];
          v140 = (char *)pArg1[3];
          v138 = v89;
          v128 = v5;
          v127 = v6;
          i = v7;
          goto LABEL_297;
        }
        v146 = *(uint32_t *)(v2[19] + 4 * (v7 & ((1 << v2[21]) - 1)));
        v90 = (uint8_t *)v146;
        if ( BYTE1(v146) > v4 )
        {
          while ( v6 != 0 )
          {
            v91 = *v5 << v4;
            --v6;
            v4 += 8;
            v7 += v91;
            ++v5;
            v127 = v6;
            v90 = *(uint8_t **)(v2[19] + 4 * (v7 & ((1 << v2[21]) - 1)));
            v128 = v5;
            v146 = (unsigned int)v90;
            if ( BYTE1(v90) <= v4 )
              goto LABEL_219;
          }
          goto LABEL_304;
        }
LABEL_219:
        if ( (uint8_t)v90 != 0 && ((uint8_t)v90 & 0xF0) == 0 )
        {
          v141 = (int)v90;
          v146 = *(uint32_t *)(v2[19] + 4
                                    * (HIWORD(v146) + ((v7 & ((1 << (BYTE1(v90) + (uint8_t)v90)) - 1)) >> SBYTE1(v90))));
          v92 = BYTE1(v90);
          v135 = BYTE1(v90);
          if ( BYTE1(v90) + (unsigned int)BYTE1(v146) > v4 )
          {
            while ( v6 != 0 )
            {
              --v6;
              v7 += *v5++ << v4;
              v4 += 8;
              v127 = v6;
              v128 = v5;
              v93 = (uint8_t)BYTE1(*(uint32_t *)(v2[19]
                                                     + 4 * (HIWORD(v141) + ((v7 & ((1 << (v135 + v141)) - 1)) >> v135))));
              v146 = *(uint32_t *)(v2[19] + 4 * (HIWORD(v141) + ((v7 & ((1 << (v135 + v141)) - 1)) >> v135)));
              v92 = v135;
              if ( v135 + v93 <= v4 )
                goto LABEL_224;
            }
            goto LABEL_304;
          }
LABEL_224:
          LOWORD(v90) = v146;
          v7 >>= v92;
          v4 -= v92;
        }
        v7 >>= SBYTE1(v90);
        v4 -= BYTE1(v90);
        i = v7;
        v2[16] = HIWORD(v146);
        if ( (uint8_t)v90 == 0 )
        {
          *v2 = 23;
          goto LABEL_297;
        }
        if ( ((uint8_t)v90 & 0x20) != 0 )
        {
LABEL_228:
          *v2 = 11;
          goto LABEL_297;
        }
        if ( ((uint8_t)v90 & 0x40) != 0 )
        {
          pArg1[6] = "invalid literal/length code";
          goto LABEL_296;
        }
        v2[18] = (uint8_t)v90 & 0xF;
        *v2 = 19;
LABEL_232:
        v94 = v2[18];
        if ( v94 != 0 )
        {
          if ( v4 < v94 )
          {
            while ( v6 != 0 )
            {
              v95 = *v5 << v4;
              --v6;
              v4 += 8;
              v7 += v95;
              ++v5;
              v127 = v6;
              v128 = v5;
              if ( v4 >= v2[18] )
                goto LABEL_236;
            }
            goto LABEL_304;
          }
LABEL_236:
          v2[16] += v7 & ((1 << v2[18]) - 1);
          v96 = v2[18];
          v7 >>= v96;
          v4 -= v96;
        }
        *v2 = 20;
LABEL_238:
        v146 = *(uint32_t *)(v2[20] + 4 * (v7 & ((1 << v2[22]) - 1)));
        v97 = (uint8_t *)v146;
        if ( BYTE1(v146) > v4 )
        {
          while ( v6 != 0 )
          {
            v98 = *v5 << v4;
            --v6;
            v4 += 8;
            v7 += v98;
            ++v5;
            v127 = v6;
            v97 = *(uint8_t **)(v2[20] + 4 * (v7 & ((1 << v2[22]) - 1)));
            v128 = v5;
            v146 = (unsigned int)v97;
            if ( BYTE1(v97) <= v4 )
              goto LABEL_241;
          }
          goto LABEL_304;
        }
LABEL_241:
        if ( ((uint8_t)v97 & 0xF0) == 0 )
        {
          v141 = (int)v97;
          v146 = *(uint32_t *)(v2[20] + 4
                                    * (HIWORD(v146) + ((v7 & ((1 << (BYTE1(v97) + (uint8_t)v97)) - 1)) >> SBYTE1(v97))));
          v99 = BYTE1(v97);
          v136 = BYTE1(v97);
          if ( BYTE1(v97) + (unsigned int)BYTE1(v146) > v4 )
          {
            while ( v6 != 0 )
            {
              --v6;
              v7 += *v5++ << v4;
              v4 += 8;
              v127 = v6;
              v128 = v5;
              v100 = (uint8_t)BYTE1(*(uint32_t *)(v2[20]
                                                      + 4 * (HIWORD(v141) + ((v7 & ((1 << (v136 + v141)) - 1)) >> v136))));
              v146 = *(uint32_t *)(v2[20] + 4 * (HIWORD(v141) + ((v7 & ((1 << (v136 + v141)) - 1)) >> v136)));
              v99 = v136;
              if ( v136 + v100 <= v4 )
                goto LABEL_245;
            }
            goto LABEL_304;
          }
LABEL_245:
          LOWORD(v97) = v146;
          v7 >>= v99;
          v4 -= v99;
        }
        v7 >>= SBYTE1(v97);
        v4 -= BYTE1(v97);
        i = v7;
        if ( ((uint8_t)v97 & 0x40) != 0 )
        {
          pArg1[6] = "invalid distance code";
          goto LABEL_296;
        }
        v2[17] = HIWORD(v146);
        v2[18] = (uint8_t)v97 & 0xF;
        *v2 = 21;
LABEL_249:
        v101 = v2[18];
        if ( v101 != 0 )
        {
          if ( v4 < v101 )
          {
            while ( v6 != 0 )
            {
              v102 = *v5 << v4;
              --v6;
              v4 += 8;
              v7 += v102;
              ++v5;
              v127 = v6;
              v128 = v5;
              if ( v4 >= v2[18] )
                goto LABEL_253;
            }
            goto LABEL_304;
          }
LABEL_253:
          v2[17] += v7 & ((1 << v2[18]) - 1);
          v103 = v2[18];
          v7 >>= v103;
          v4 -= v103;
          i = v7;
        }
        if ( v2[17] > v142 + v2[11] - v138 )
        {
          pArg1[6] = "invalid distance too far back";
          goto LABEL_296;
        }
        *v2 = 22;
LABEL_257:
        if ( v138 == 0 )
          goto LABEL_304;
        v104 = v2[17];
        if ( v104 <= v142 - v138 )
        {
          v108 = &v140[-v104];
          v105 = v2[16];
          v141 = (int)v108;
          v144 = v105;
          goto LABEL_265;
        }
        v105 = v104 - (v142 - v138);
        v106 = v2[12];
        v137 = v105;
        if ( v105 <= v106 )
        {
          v107 = v2[12] + v2[13] - v105;
        }
        else
        {
          v105 -= v106;
          v137 = v105;
          v107 = v2[10] + v2[13] - v105;
        }
        v141 = v107;
        v144 = v2[16];
        if ( v105 > v144 )
        {
          v105 = v144;
LABEL_265:
          v137 = v105;
        }
        if ( v105 > v138 )
        {
          v105 = v138;
          v137 = v138;
        }
        v138 -= v105;
        v2[16] = v144 - v105;
        do
        {
          v109 = v140;
          *v140 = *(uint8_t *)v141;
          v140 = v109 + 1;
          v110 = v137 == 1;
          ++v141;
          --v137;
        }
        while ( !v110 );
        if ( v2[16] == 0 )
          *v2 = 18;
        goto LABEL_297;
      case 16:
        goto LABEL_163;
      case 17:
        goto LABEL_174;
      case 18:
        goto LABEL_213;
      case 19:
        goto LABEL_232;
      case 20:
        goto LABEL_238;
      case 21:
        goto LABEL_249;
      case 22:
        goto LABEL_257;
      case 23:
        if ( v3 == 0 )
          goto LABEL_304;
        v111 = v140;
        *v140 = *((uint8_t *)v2 + 64);
        v140 = v111 + 1;
        --v138;
        *v2 = 18;
        goto LABEL_297;
      case 24:
        if ( v2[2] == 0 )
          goto LABEL_288;
        for ( ; v4 < 0x20; v128 = v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v112 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v112;
          ++v5;
          i = v7;
        }
        v113 = v142 - v138;
        pArg1[5] += v142 - v138;
        v114 = v113 + v2[7];
        v142 = v113;
        v2[7] = v114;
        if ( v113 != 0 )
        {
          v115 = v2[6];
          if ( v2[4] != 0 )
            v116 = sub_655990(v115, &v140[-v142], v142);
          else
            v116 = sub_655460(v115, &v140[-v142], v142);
          v2[6] = v116;
          pArg1[12] = (uint8_t *)v116;
          v7 = i;
        }
        v110 = v2[4] == 0;
        v142 = v138;
        v117 = v7;
        if ( v110 )
        {
          LOBYTE(v118) = 0;
          HIBYTE(v118) = BYTE2(i);
          v117 = HIBYTE(v7) + v118 + (((v7 << 16) + (v7 & 0xFF00)) << 8);
          v144 = v117;
        }
        if ( v117 != v2[6] )
        {
          pArg1[6] = "incorrect data check";
LABEL_296:
          *v2 = 27;
LABEL_297:
          v8 = *v2;
          if ( (unsigned int)*v2 > 0x1C )
            return -2;
          v3 = v138;
          continue;
        }
        v7 = 0;
        i = 0;
        v4 = 0;
LABEL_288:
        *v2 = 25;
LABEL_289:
        if ( v2[2] == 0 || v2[4] == 0 )
          goto LABEL_301;
        if ( v4 < 0x20 )
        {
          while ( v6 != 0 )
          {
            v119 = *v5 << v4;
            --v6;
            v4 += 8;
            v127 = v6;
            v7 += v119;
            ++v5;
            i = v7;
            v128 = v5;
            if ( v4 >= 0x20 )
              goto LABEL_294;
          }
          goto LABEL_304;
        }
LABEL_294:
        if ( v7 != v2[7] )
        {
          pArg1[6] = "incorrect length check";
          goto LABEL_296;
        }
        v7 = 0;
        v4 = 0;
LABEL_301:
        *v2 = 26;
LABEL_302:
        v143 = 1;
LABEL_304:
        pArg1[3] = (uint8_t *)v140;
        pArg1[4] = (uint8_t *)v138;
        *pArg1 = v5;
        pArg1[1] = (uint8_t *)v6;
        v2[14] = v7;
        v120 = v2[10];
        v2[15] = v4;
        if ( (v120 != 0 || *v2 < 24 && (uint8_t *)v142 != pArg1[4]) && sub_653000(pArg1) != 0 )
        {
          *v2 = 28;
          return -4;
        }
        else
        {
          v121 = v145 - (uint32_t)pArg1[1];
          v122 = v142 - (uint32_t)pArg1[4];
          v123 = &pArg1[5][v122];
          pArg1[2] += v121;
          pArg1[5] = v123;
          v124 = v2[2];
          v2[7] += v122;
          if ( v124 != 0 && v122 != 0 )
          {
            if ( v2[4] != 0 )
              v125 = sub_655990(v2[6], &pArg1[3][-v122], v122);
            else
              v125 = sub_655460(v2[6], &pArg1[3][-v122], v122);
            v2[6] = v125;
            pArg1[12] = (uint8_t *)v125;
          }
          pArg1[11] = (uint8_t *)(v2[15] + (*v2 != 11 ? 0 : 0x80) + (v2[1] != 0 ? 0x40 : 0));
          if ( (v121 != 0 || v122 != 0) && nArg2 != 4 )
          {
            return v143;
          }
          else
          {
            result = v143;
            if ( v143 == 0 )
              return -5;
          }
        }
        return result;
      case 25:
        goto LABEL_289;
      case 26:
        goto LABEL_302;
      case 27:
        v143 = -3;
        goto LABEL_304;
      case 28:
        return -4;
      default:
        return -2;
    }
  }
}


// ------------------------------------------------------------
// 0x654750 sub_654750
// ------------------------------------------------------------
// 【解读】
//   inflateEnd(): 状态非空 → zcfree（先释放 state+52 附属窗口再释放状态本体）。zlib 标准。
// ------------------------------------------------------------
int /*cdecl*/ sub_654750(uint32_t *pArg1)
{
  int v1; // eax
  void (/*cdecl*/ *v2)(uint32_t, int); // ecx
  int v3; // eax

  if ( pArg1 == nullptr )
    return -2;
  v1 = pArg1[7];
  if ( v1 == 0 )
    return -2;
  v2 = (void (/*cdecl*/ *)(uint32_t, int))pArg1[9];
  if ( v2 == nullptr )
    return -2;
  v3 = *(uint32_t *)(v1 + 52);
  if ( v3 != 0 )
    v2(pArg1[10], v3);
  ((void (/*cdecl*/ *)(uint32_t, uint32_t))pArg1[9])(pArg1[10], pArg1[7]);
  pArg1[7] = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6547A0 sub_6547A0
// ------------------------------------------------------------
// 【解读】
//   zcalloc(): malloc(items*size) —— zlib 分配器挂钩（0x652F10 挂到 stream+8/+9）。
// ------------------------------------------------------------
void */*cdecl*/ sub_6547A0(int nArg1, int nArg2, int nArg3)
{
  return malloc(nArg3 * nArg2);
}



// ------------------------------------------------------------
// 0x6547C0 sub_6547C0
// ------------------------------------------------------------
// 【解读】
//   zcfree(): free(block) —— zlib 释放挂钩。
// ------------------------------------------------------------
void /*cdecl*/ sub_6547C0(int nArg1, void *Block)
{
  free(Block);
}



// ------------------------------------------------------------
// 0x6548D8 sub_6548D8
// ------------------------------------------------------------
// 【解读】
//   ★ inflate_fast()（555 行，MMX 优化版）: __m64/_m_psrlq/_m_psllqi/_m_por/_mm_cvtsi32_si64
//     等 SIMD 内建加速的解码快路径。zlib 1.2.3 官方无 SIMD —— 发布版/Neople 定制补丁【推断】。
//     错误串 "invalid distance code"/"invalid distance too far back"/"invalid literal/length code"。
// ------------------------------------------------------------
int */*usercall*/ sub_6548D8@<eax>(__m64 uArg1@<mm0>, __m64 uArg2@<mm1>, int *pDwArg3, int nArg4)
{
  unsigned int v4; // kr00_4
  uint32_t *v5; // edi
  int v6; // edx
  int v7; // ecx
  unsigned int v8; // eax
  unsigned int v9; // ecx
  char *v10; // edx
  unsigned int v11; // ebp
  unsigned int v12; // ebx
  uint8_t *pBuf72; // esi
  unsigned int v14; // ecx
  unsigned int pBuf4; // ecx
  int v16; // eax
  char *v17; // edi
  unsigned int v18; // kr04_4
  unsigned int v19; // kr08_4
  uint16_t v30; // ax
  char v31; // cl
  unsigned int i; // eax
  unsigned int v33; // edx
  uint8_t v34; // cl
  uint8_t v35; // ch
  uint16_t v36; // ax
  char v37; // cl
  int v38; // eax
  uint16_t v39; // ax
  char v40; // cl
  unsigned int j; // eax
  unsigned int v42; // edx
  uint8_t v43; // cl
  uint8_t v44; // ch
  uint16_t v45; // ax
  char v46; // cl
  int v47; // eax
  char *v48; // esi
  char v49; // al
  char v50; // dl
  char *v51; // edi
  char *pBuf6; // edi
  char pBuf2; // al
  unsigned int v54; // ecx
  char *v55; // esi
  unsigned int pBuf32; // eax
  unsigned int v57; // ecx
  unsigned int v58; // ecx
  __m64 v59; // mm4
  __m64 v60; // mm3
  __m64 v61; // mm5
  __m64 v62; // mm2
  __m64 v63; // mm7
  __m64 v64; // mm7
  int v65; // eax
  unsigned int pBuf8; // edx
  unsigned int v67; // eax
  __m64 v68; // mm7
  __m64 v69; // mm7
  int v70; // eax
  unsigned int k; // eax
  unsigned int v72; // eax
  unsigned int v73; // ecx
  char v74; // dl
  char *v75; // esi
  char *v76; // edi
  char *pBuf5; // edi
  char pBuf; // al
  unsigned int v79; // ecx
  char *v80; // esi
  unsigned int v81; // ecx
  unsigned int v82; // ecx
  const char *v83; // ecx
  int v84; // edx
  int *result; // eax
  int v86; // edx
  int v87; // esi
  unsigned int v88; // ebx
  char *v89; // [esp+4h] [ebp-64h]
  unsigned int v90; // [esp+8h] [ebp-60h]
  unsigned int v91; // [esp+Ch] [ebp-5Ch]
  unsigned int v92; // [esp+10h] [ebp-58h]
  unsigned int v93; // [esp+14h] [ebp-54h]
  unsigned int v94; // [esp+18h] [ebp-50h]
  unsigned int v95; // [esp+1Ch] [ebp-4Ch]
  int v96; // [esp+20h] [ebp-48h]
  unsigned int v97; // [esp+24h] [ebp-44h]
  uint8_t *pBuf73; // [esp+28h] [ebp-40h]
  unsigned int pBuf3; // [esp+2Ch] [ebp-3Ch]
  uint8_t pBuf7[12]; // [esp+30h] [ebp-38h] BYREF
  char *v101; // [esp+3Ch] [ebp-2Ch]
  uint8_t *pBuf722; // [esp+40h] [ebp-28h]
  unsigned int v103; // [esp+44h] [ebp-24h]
  unsigned int v104; // [esp+48h] [ebp-20h]
  char *v105; // [esp+4Ch] [ebp-1Ch]
  char *v106; // [esp+50h] [ebp-18h]
  unsigned int v107; // [esp+54h] [ebp-14h]

  v4 = __readeflags();
  v107 = v4;
  v5 = (uint32_t *)pDwArg3[7];
  v6 = *pDwArg3 + pDwArg3[1] - 11;
  pBuf722 = (uint8_t *)*pDwArg3;
  pBuf73 = (uint8_t *)v6;
  v7 = pDwArg3[4];
  v106 = (char *)pDwArg3[3];
  v101 = &v106[v7 - nArg4];
  v97 = (unsigned int)&v106[v7 - 257];
  v95 = v5[19];
  v96 = v5[20];
  v93 = (1 << v5[21]) - 1;
  v94 = (1 << v5[22]) - 1;
  v8 = v5[10];
  v9 = v5[12];
  v10 = (char *)v5[13];
  v104 = v8;
  v103 = v9;
  v105 = v10;
  v11 = v5[14];
  v12 = v5[15];
  pBuf72 = pBuf722;
  v14 = (unsigned int)pBuf73;
  if ( pBuf73 > pBuf722 )
  {
    while ( ((uint8_t)pBuf72 & 3) != 0 )
    {
      v16 = *pBuf72++;
      v14 = v12;
      v12 += 8;
      v8 = v16 << v14;
      v11 |= v8;
    }
  }
  else
  {
    pBuf4 = pBuf73 + 11 - pBuf722;
    qmemcpy(pBuf7, pBuf722, pBuf4);
    v8 = 0;
    memset(&pBuf7[pBuf4], 0, 12 - pBuf4);
    v14 = 0;
    pBuf72 = pBuf7;
    pBuf73 = pBuf7;
  }
  v17 = v106;
  while ( dword_7960F0 != 2 )
  {
    if ( (unsigned int)dword_7960F0 > 2 )
    {
      while ( 1 )
      {
        if ( (uint8_t)v12 <= 0xFu )
        {
          v30 = *(uint16_t *)pBuf72;
          pBuf72 += 2;
          v31 = v12;
          LOBYTE(v12) = v12 + 16;
          v11 |= v30 << v31;
        }
        for ( i = *(uint32_t *)(v95 + 4 * (v11 & v93)); ; i = *(uint32_t *)(v95 + 4 * (v33 + (v11 & ((1 << i) - 1)))) )
        {
          LOBYTE(v12) = v12 - BYTE1(i);
          v11 >>= SBYTE1(i);
          if ( (uint8_t)i == 0 )
          {
            *v17++ = BYTE2(i);
            goto LABEL_22;
          }
          v33 = HIWORD(i);
          if ( (i & 0x10) != 0 )
            break;
          if ( (i & 0x40) != 0 )
            goto LABEL_97;
        }
        v34 = i & 0xF;
        if ( (i & 0xF) != 0 )
        {
          if ( (uint8_t)v12 < v34 )
          {
            v35 = i & 0xF;
            v36 = *(uint16_t *)pBuf72;
            pBuf72 += 2;
            v37 = v12;
            LOBYTE(v12) = v12 + 16;
            v11 |= v36 << v37;
            v34 = v35;
          }
          LOBYTE(v12) = v12 - v34;
          v38 = v11 & ((1 << v34) - 1);
          v11 >>= v34;
          v33 += v38;
        }
        pBuf3 = v33;
        if ( (uint8_t)v12 <= 0xFu )
        {
          v39 = *(uint16_t *)pBuf72;
          pBuf72 += 2;
          v40 = v12;
          LOBYTE(v12) = v12 + 16;
          v11 |= v39 << v40;
        }
        for ( j = *(uint32_t *)(v96 + 4 * (v11 & v94)); ; j = *(uint32_t *)(v96 + 4 * (v42 + (v11 & ((1 << j) - 1)))) )
        {
          v42 = HIWORD(j);
          LOBYTE(v12) = v12 - BYTE1(j);
          v11 >>= SBYTE1(j);
          if ( (j & 0x10) != 0 )
            break;
          if ( (j & 0x40) != 0 )
            goto LABEL_96;
        }
        v43 = j & 0xF;
        if ( (j & 0xF) != 0 )
        {
          if ( (uint8_t)v12 < v43 )
          {
            v44 = j & 0xF;
            v45 = *(uint16_t *)pBuf72;
            pBuf72 += 2;
            v46 = v12;
            LOBYTE(v12) = v12 + 16;
            v11 |= v45 << v46;
            v43 = v44;
          }
          LOBYTE(v12) = v12 - v43;
          v47 = v11 & ((1 << v43) - 1);
          v11 >>= v43;
          v42 += v47;
        }
        else if ( v42 == 1 && v101 != v17 )
        {
          pBuf6 = v17 - 1;
          pBuf2 = *pBuf6;
          pBuf6[1] = *pBuf6;
          pBuf6[2] = pBuf2;
          pBuf6[3] = pBuf2;
          pBuf6 += 4;
          memset(pBuf6, pBuf2, pBuf3 - 3);
          v17 = &pBuf6[pBuf3 - 3];
          goto LABEL_22;
        }
        pBuf722 = pBuf72;
        if ( v17 - v101 >= v42 )
        {
          v48 = &v17[-v42];
          *v17 = v17[-v42];
          v49 = v17[-v42 + 1];
          v50 = v17[-v42 + 2];
          v17[1] = v49;
          v17[2] = v50;
          v51 = v17 + 3;
          qmemcpy(v51, v48 + 3, pBuf3 - 3);
          v17 = &v51[pBuf3 - 3];
          pBuf72 = pBuf722;
          goto LABEL_22;
        }
        if ( v104 < v42 )
          goto LABEL_100;
        v54 = v42 + v101 - v17;
        if ( v103 != 0 )
        {
          if ( v54 > v103 )
          {
            v55 = &v105[v104 + v103 - v54];
            v57 = v54 - v103;
            pBuf32 = pBuf3;
            if ( pBuf3 > v57 )
            {
              pBuf32 = pBuf3 - v57;
              qmemcpy(v17, v55, v57);
              v17 += v57;
              v55 = v105;
              v58 = v103;
              if ( pBuf32 > v103 )
              {
                pBuf32 -= v103;
                qmemcpy(v17, v105, v103);
                v17 += v58;
                v55 = &v17[-v42];
              }
            }
            goto LABEL_57;
          }
          v55 = &v105[v103 - v54];
          pBuf32 = pBuf3;
          if ( pBuf3 > v54 )
          {
LABEL_56:
            pBuf32 = pBuf3 - v54;
            qmemcpy(v17, v55, v54);
            v17 += v54;
            v55 = &v17[-v42];
          }
        }
        else
        {
          v55 = &v105[v104 - v54];
          pBuf32 = pBuf3;
          if ( pBuf3 > v54 )
            goto LABEL_56;
        }
LABEL_57:
        qmemcpy(v17, v55, pBuf32);
        v17 += pBuf32;
        pBuf72 = pBuf722;
LABEL_22:
        if ( v97 <= (unsigned int)v17 || pBuf73 <= pBuf72 )
          goto LABEL_104;
      }
    }
    v92 = v8;
    v91 = v12;
    v90 = v14;
    v89 = v10;
    v18 = __readeflags();
    __writeeflags(v18 ^ 0x200000);
    v19 = __readeflags();
    if ( v18 == v19 )
      goto LABEL_15;
    _EAX = 0;
    __asm { cpuid }
    if ( _EBX != 1970169159 )
      goto LABEL_15;
    if ( _ECX != 1818588270 )
      goto LABEL_15;
    if ( _EDX != 1231384169 )
      goto LABEL_15;
    _EAX = 1;
    __asm { cpuid }
    if ( ((_EAX >> 8) & 0xF) != 6 )
      goto LABEL_15;
    if ( ((unsigned int)&unk_800000 & _EDX) != 0 )
      dword_7960F0 = 2;
    else
LABEL_15:
      dword_7960F0 = 3;
    v10 = v89;
    v14 = v90;
    v12 = v91;
    v8 = v92;
  }
  _m_empty();
  uArg1 = _mm_cvtsi32_si64(v11);
  v11 = v12;
  v59 = _mm_cvtsi32_si64(v93);
  v60 = v59;
  v61 = _mm_cvtsi32_si64(v94);
  v62 = v61;
  uArg2.m64_u64 = 0;
  v12 = v95;
LABEL_59:
  uArg1 = _m_psrlq(uArg1, uArg2);
  if ( v11 <= 0x20 )
  {
    v63 = _mm_cvtsi32_si64(*(uint32_t *)pBuf72);
    pBuf72 += 4;
    v64 = _m_psllqi(v63, v11);
    v11 += 32;
    uArg1 = _m_por(uArg1, v64);
  }
  v65 = _mm_cvtsi64_si32(_m_pand(v59, uArg1));
  v59 = v60;
  for ( i = *(uint32_t *)(v12 + 4 * v65); ; i = *(uint32_t *)(v12
                                                        + 4 * (pBuf8 + (dword_654854[i & 0xF] & _mm_cvtsi64_si32(uArg1)))) )
  {
    uArg2 = _mm_cvtsi32_si64(BYTE1(i));
    v11 -= BYTE1(i);
    if ( (uint8_t)i == 0 )
    {
      *v17++ = BYTE2(i);
LABEL_64:
      if ( v97 <= (unsigned int)v17 || pBuf73 <= pBuf72 )
        goto LABEL_104;
      goto LABEL_59;
    }
    pBuf8 = HIWORD(i);
    if ( (i & 0x10) != 0 )
    {
      v67 = i & 0xF;
      if ( v67 != 0 )
      {
        uArg1 = _m_psrlq(uArg1, uArg2);
        uArg2 = _mm_cvtsi32_si64(v67);
        v11 -= v67;
        pBuf8 += dword_654854[v67] & _mm_cvtsi64_si32(uArg1);
      }
      uArg1 = _m_psrlq(uArg1, uArg2);
      if ( v11 <= 0x20 )
      {
        v68 = _mm_cvtsi32_si64(*(uint32_t *)pBuf72);
        pBuf72 += 4;
        v69 = _m_psllqi(v68, v11);
        v11 += 32;
        uArg1 = _m_por(uArg1, v69);
      }
      v70 = _mm_cvtsi64_si32(_m_pand(v61, uArg1));
      v61 = v62;
      for ( k = *(uint32_t *)(v96 + 4 * v70);
            ;
            k = *(uint32_t *)(v96 + 4 * (v12 + (dword_654854[k & 0xF] & _mm_cvtsi64_si32(uArg1)))) )
      {
        v12 = HIWORD(k);
        v11 -= BYTE1(k);
        uArg2 = _mm_cvtsi32_si64(BYTE1(k));
        if ( (k & 0x10) != 0 )
          break;
        if ( (k & 0x40) != 0 )
        {
LABEL_96:
          v83 = "invalid distance code";
          v84 = 26;
          goto LABEL_101;
        }
        uArg1 = _m_psrlq(uArg1, uArg2);
      }
      v72 = k & 0xF;
      if ( v72 != 0 )
      {
        uArg1 = _m_psrlq(uArg1, uArg2);
        uArg2 = _mm_cvtsi32_si64(v72);
        v11 -= v72;
        v12 += dword_654854[v72] & _mm_cvtsi64_si32(uArg1);
      }
      else if ( v12 == 1 && v101 != v17 )
      {
        pBuf5 = v17 - 1;
        pBuf = *pBuf5;
        pBuf5[1] = *pBuf5;
        pBuf5[2] = pBuf;
        pBuf5[3] = pBuf;
        pBuf5 += 4;
        memset(pBuf5, pBuf, pBuf8 - 3);
        v17 = &pBuf5[pBuf8 - 3];
        v12 = v95;
        goto LABEL_64;
      }
      pBuf722 = pBuf72;
      if ( v17 - v101 >= v12 )
      {
        v73 = pBuf8 - 3;
        *v17 = v17[-v12];
        v74 = v17[-v12 + 2];
        v75 = &v17[-v12 + 3];
        v17[1] = v17[-v12 + 1];
        v17[2] = v74;
        v76 = v17 + 3;
        qmemcpy(v76, v75, v73);
        v17 = &v76[v73];
        pBuf72 = pBuf722;
        v12 = v95;
        goto LABEL_64;
      }
      if ( v104 < v12 )
      {
LABEL_100:
        pBuf72 = pBuf722;
        v83 = "invalid distance too far back";
        v84 = 26;
        goto LABEL_101;
      }
      v79 = v12 + v101 - v17;
      if ( v103 != 0 )
      {
        if ( v79 > v103 )
        {
          v80 = &v105[v104 + v103 - v79];
          v81 = v79 - v103;
          if ( pBuf8 > v81 )
          {
            pBuf8 -= v81;
            qmemcpy(v17, v80, v81);
            v17 += v81;
            v80 = v105;
            v82 = v103;
            if ( pBuf8 > v103 )
            {
              pBuf8 -= v103;
              qmemcpy(v17, v105, v103);
              v17 += v82;
              v80 = &v17[-v12];
            }
          }
          goto LABEL_95;
        }
        v80 = &v105[v103 - v79];
        if ( pBuf8 > v79 )
          goto LABEL_94;
      }
      else
      {
        v80 = &v105[v104 - v79];
        if ( pBuf8 > v79 )
        {
LABEL_94:
          pBuf8 -= v79;
          qmemcpy(v17, v80, v79);
          v17 += v79;
          v80 = &v17[-v12];
        }
      }
LABEL_95:
      qmemcpy(v17, v80, pBuf8);
      v17 += pBuf8;
      pBuf72 = pBuf722;
      v12 = v95;
      goto LABEL_64;
    }
    if ( (i & 0x40) != 0 )
      break;
    uArg1 = _m_psrlq(uArg1, uArg2);
  }
LABEL_97:
  if ( (i & 0x20) != 0 )
  {
    v83 = nullptr;
    v84 = 11;
  }
  else
  {
    v83 = "invalid literal/length code";
    v84 = 26;
  }
LABEL_101:
  if ( v83 != nullptr )
    pDwArg3[6] = (int)v83;
  *(uint32_t *)pDwArg3[7] = v84;
LABEL_104:
  if ( dword_7960F0 == 2 )
    v12 = v11;
  result = pDwArg3;
  v86 = pDwArg3[7];
  v87 = (int)&pBuf72[-(v12 >> 3)];
  v88 = v12 - 8 * (v12 >> 3);
  pDwArg3[3] = (int)v17;
  *(uint32_t *)(v86 + 60) = v88;
  if ( pBuf73 == pBuf7 )
  {
    v87 = *pDwArg3 + v87 - (uint32_t)pBuf7;
    pBuf73 = (uint8_t *)(pDwArg3[1] - 11 + *pDwArg3);
  }
  *pDwArg3 = v87;
  if ( dword_7960F0 == 2 )
  {
    v11 = _mm_cvtsi64_si32(_m_psrlq(uArg1, uArg2));
    _m_empty();
  }
  *(uint32_t *)(v86 + 56) = ((1 << v88) - 1) & v11;
  pDwArg3[1] = (int)&pBuf73[-v87 + 11];
  pDwArg3[4] = v97 - (uint32_t)v17 + 257;
  __writeeflags(v107);
  return result;
}


// ------------------------------------------------------------
// 0x654F70 sub_654F70
// ------------------------------------------------------------
// 【解读】
//   inflate_table(): Huffman 解码表构建（286 行）—— zlib 标准函数。
// ------------------------------------------------------------
int /*cdecl*/ sub_654F70(int nArg1, int pArg2, unsigned int uArg3, uint32_t **uArg4, unsigned int *pDwArg5, char *pszArg6)
{
  unsigned int v6; // eax
  unsigned int v7; // ebx
  uint32_t *v8; // edx
  unsigned int v10; // esi
  int v11; // edx
  unsigned int i; // eax
  unsigned int j; // eax
  int16_t v14; // dx
  int16_t v15; // cx
  unsigned int k; // eax
  char *pszArg62; // eax
  unsigned int v18; // ebp
  unsigned int v19; // ebx
  int v20; // eax
  int v21; // eax
  int v22; // edx
  uint32_t *v23; // ecx
  unsigned int v24; // edx
  unsigned int m; // eax
  uint16_t *v26; // esi
  int v27; // esi
  char v28; // cl
  unsigned int v29; // edx
  int v30; // eax
  uint16_t *v31; // esi
  int v32; // eax
  unsigned int v33; // edx
  uint32_t *v34; // esi
  unsigned int n; // eax
  int v36; // [esp+Ch] [ebp-7Ch]
  int v37; // [esp+Ch] [ebp-7Ch]
  unsigned int v38; // [esp+10h] [ebp-78h]
  unsigned int v39; // [esp+14h] [ebp-74h]
  unsigned int v40; // [esp+18h] [ebp-70h]
  uint32_t *v41; // [esp+1Ch] [ebp-6Ch]
  char *pszArg64; // [esp+20h] [ebp-68h]
  int v43; // [esp+24h] [ebp-64h]
  int v44; // [esp+28h] [ebp-60h]
  uint8_t *pszArg622; // [esp+2Ch] [ebp-5Ch]
  char *pszArg63; // [esp+30h] [ebp-58h]
  int v47; // [esp+34h] [ebp-54h]
  int v48; // [esp+38h] [ebp-50h]
  int v49; // [esp+3Ch] [ebp-4Ch]
  int v50; // [esp+48h] [ebp-40h] BYREF
  int v51; // [esp+4Ch] [ebp-3Ch]
  uint16_t pBuf[13]; // [esp+50h] [ebp-38h] BYREF
  uint16_t v53[15]; // [esp+6Ah] [ebp-1Eh]

  v6 = 0;
  v50 = 0;
  v51 = 0;
  memset(pBuf, 0, 24);
  if ( uArg3 != 0 )
  {
    do
      ++*((uint16_t *)&v50 + *(uint16_t *)(pArg2 + 2 * v6++));
    while ( v6 < uArg3 );
  }
  v7 = 15;
  v38 = *pDwArg5;
  do
  {
    if ( *((uint16_t *)&v50 + v7) != 0 )
      break;
    --v7;
  }
  while ( v7 != 0 );
  v40 = v7;
  if ( *pDwArg5 > v7 )
    v38 = v7;
  if ( v7 == 0 )
  {
    **uArg4 = 320;
    v8 = *uArg4 + 1;
    *uArg4 = v8;
    *v8 = 320;
    ++*uArg4;
    *pDwArg5 = 1;
    return 0;
  }
  v10 = 1;
  while ( *((uint16_t *)&v50 + v10) == 0 )
  {
    if ( *((uint16_t *)&v50 + v10 + 1) != 0 )
    {
      ++v10;
      break;
    }
    if ( pBuf[v10 - 2] != 0 )
    {
      v10 += 2;
      break;
    }
    if ( pBuf[v10 - 1] != 0 )
    {
      v10 += 3;
      break;
    }
    if ( pBuf[v10] != 0 )
    {
      v10 += 4;
      break;
    }
    v10 += 5;
    if ( v10 > 0xF )
      break;
  }
  if ( v38 < v10 )
    v38 = v10;
  v11 = 1;
  for ( i = 1; i <= 0xF; ++i )
  {
    v11 = 2 * v11 - *((uint16_t *)&v50 + i);
    if ( v11 < 0 )
      return -1;
  }
  if ( v11 > 0 && (nArg1 == 0 || v7 != 1) )
    return -1;
  v53[0] = 0;
  for ( j = 1; j < 15; j += 2 )
  {
    v14 = *(uint16_t *)((char *)&v50 + j * 2) + pBuf[j + 12];
    v15 = v14 + *(uint16_t *)((char *)&v50 + j * 2 + 2);
    v53[j] = v14;
    v53[j + 1] = v15;
  }
  for ( k = 0; k < uArg3; ++k )
  {
    if ( *(uint16_t *)(pArg2 + 2 * k) != 0 )
      *(uint16_t *)&pszArg6[2 * (uint16_t)pBuf[*(uint16_t *)(pArg2 + 2 * k) + 12]++] = k;
  }
  if ( nArg1 != 0 )
  {
    if ( nArg1 != 1 )
    {
      pszArg63 = (char *)&unk_73FE40;
      pszArg622 = &unk_73FE80;
      v44 = -1;
      goto LABEL_44;
    }
    pszArg63 = (char *)&unk_73FDC0 - 514;
    pszArg62 = (char *)&unk_73FE00 - 514;
    v44 = 256;
  }
  else
  {
    pszArg62 = pszArg6;
    pszArg63 = pszArg6;
    v44 = 19;
  }
  pszArg622 = pszArg62;
LABEL_44:
  v41 = *uArg4;
  v47 = -1;
  v18 = 0;
  v19 = 0;
  v39 = v10;
  v48 = 1 << v38;
  v43 = 1 << v38;
  v49 = (1 << v38) - 1;
  if ( nArg1 == 1 && (unsigned int)(1 << v38) >= 0x5B0 )
    return 1;
  pszArg64 = pszArg6;
  while ( 1 )
  {
    if ( *(uint16_t *)pszArg64 >= v44 )
    {
      if ( *(uint16_t *)pszArg64 <= v44 )
      {
        LOBYTE(v36) = 96;
        HIWORD(v36) = 0;
      }
      else
      {
        v20 = 2 * *(uint16_t *)pszArg64;
        LOBYTE(v36) = pszArg622[v20];
        HIWORD(v36) = *(uint16_t *)&pszArg63[v20];
      }
    }
    else
    {
      LOBYTE(v36) = 0;
      HIWORD(v36) = *(uint16_t *)pszArg64;
    }
    v21 = v48;
    v22 = 1 << (v39 - v19);
    v23 = &v41[v48 + (v18 >> v19)];
    do
    {
      v21 -= v22;
      v23 -= v22;
      BYTE1(v36) = v39 - v19;
      *v23 = v36;
    }
    while ( v21 != 0 );
    v24 = v39;
    for ( m = 1 << (v39 - 1); (m & v18) != 0; m >>= 1 )
      ;
    if ( m != 0 )
      v18 = m + (v18 & (m - 1));
    else
      v18 = 0;
    v26 = (uint16_t *)(pszArg64 + 2);
    --*((uint16_t *)&v50 + v39);
    pszArg64 += 2;
    if ( *((uint16_t *)&v50 + v39) == 0 )
    {
      if ( v39 == v40 )
        break;
      v24 = *(uint16_t *)(pArg2 + 2 * *v26);
      v39 = v24;
    }
    if ( v24 > v38 )
    {
      v27 = v18 & v49;
      if ( (v18 & v49) != v47 )
      {
        if ( v19 == 0 )
          v19 = v38;
        v28 = v39 - v19;
        v41 += v48;
        v29 = v39;
        v30 = 1 << (v39 - v19);
        if ( v39 < v40 )
        {
          v31 = (uint16_t *)&v50 + v39;
          do
          {
            v32 = v30 - *v31;
            if ( v32 <= 0 )
              break;
            ++v28;
            ++v29;
            ++v31;
            v30 = 2 * v32;
          }
          while ( v29 < v40 );
          v27 = v18 & v49;
        }
        v33 = (1 << v28) + v43;
        v48 = 1 << v28;
        v43 = v33;
        if ( nArg1 == 1 && v33 >= 0x5B0 )
          return 1;
        LOBYTE((*uArg4)[v27]) = v28;
        BYTE1((*uArg4)[v27]) = v38;
        v47 = v27;
        HIWORD((*uArg4)[v27]) = v41 - *uArg4;
      }
    }
  }
  LOBYTE(v37) = 64;
  BYTE1(v37) = v39 - v19;
  HIWORD(v37) = 0;
  if ( v18 != 0 )
  {
    v34 = v41;
    do
    {
      if ( v19 != 0 && (v18 & v49) != v47 )
      {
        v34 = *uArg4;
        v19 = 0;
        BYTE1(v37) = v38;
        LOBYTE(v24) = v38;
      }
      v34[v18 >> v19] = v37;
      for ( n = 1 << (v24 - 1); (n & v18) != 0; n >>= 1 )
        ;
      if ( n == 0 )
        break;
      v18 = n + (v18 & (n - 1));
    }
    while ( v18 != 0 );
  }
  *uArg4 += v43;
  *pDwArg5 = v38;
  return 0;
}


// ------------------------------------------------------------
// 0x655460 sub_655460
// ------------------------------------------------------------
// 【解读】
//   crc32(): zlib 标准循环校验（表驱动）。
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_655460(unsigned int uArg1, uint8_t *uArg2, unsigned int uArg3)
{
  unsigned int uArg32; // ebx
  unsigned int v4; // edi
  unsigned int v5; // ecx
  unsigned int v6; // ecx
  unsigned int v7; // edi
  uint8_t *uArg22; // esi
  unsigned int v10; // ebp
  int i; // eax
  unsigned int v12; // ecx
  unsigned int v13; // edi
  unsigned int v14; // ecx
  unsigned int v15; // edi
  unsigned int v16; // ecx
  unsigned int v17; // edi
  unsigned int v18; // ecx
  unsigned int v19; // edi
  unsigned int v20; // ecx
  unsigned int v21; // edi
  unsigned int v22; // ecx
  unsigned int v23; // edi
  unsigned int v24; // ecx
  int v25; // edi
  unsigned int v26; // ecx
  int v27; // edi
  unsigned int v28; // ecx
  int v29; // edi
  int v30; // ecx
  int v31; // edi
  int v32; // ecx
  int v33; // edi
  int v34; // ecx
  int v35; // edi
  int v36; // ecx
  int v37; // edi
  int v38; // ecx
  int v39; // edi
  int v40; // ecx
  int v41; // edi
  unsigned int v42; // eax
  unsigned int v43; // ecx
  unsigned int v44; // edi
  unsigned int v45; // ecx
  unsigned int v46; // edi
  unsigned int v47; // ecx
  unsigned int v48; // edi
  unsigned int v49; // ecx
  unsigned int v50; // edi
  unsigned int v51; // ecx
  unsigned int v52; // edi
  unsigned int v53; // ecx
  unsigned int v54; // edi
  unsigned int v55; // ecx
  int v56; // edi
  unsigned int v57; // ecx
  int v58; // edi
  unsigned int v59; // ecx
  int v60; // edi
  int v61; // ecx
  int v62; // edi
  int v63; // ecx
  int v64; // edi
  int v65; // ecx
  int v66; // edi
  int v67; // ecx
  int v68; // edi
  int v69; // ecx
  int v70; // edi
  int v71; // ecx
  int v72; // edi

  uArg32 = uArg3;
  v4 = HIWORD(uArg1);
  v5 = (uint16_t)uArg1;
  if ( uArg3 == 1 )
  {
    v6 = *uArg2 + (uint16_t)uArg1;
    if ( v6 >= 0xFFF1 )
      v6 -= 65521;
    v7 = v6 + v4;
    if ( v7 >= 0xFFF1 )
      v7 -= 65521;
    return v6 | (v7 << 16);
  }
  else
  {
    uArg22 = uArg2;
    if ( uArg2 != nullptr )
    {
      if ( uArg3 >= 0x10 )
      {
        if ( uArg3 >= 0x15B0 )
        {
          v10 = uArg3 / 0x15B0;
          do
          {
            uArg32 -= 5552;
            for ( i = 347; i != 0; --i )
            {
              v12 = *uArg22 + v5;
              v13 = v12 + v4;
              v14 = uArg22[1] + v12;
              v15 = v14 + v13;
              v16 = uArg22[2] + v14;
              v17 = v16 + v15;
              v18 = uArg22[3] + v16;
              v19 = v18 + v17;
              v20 = uArg22[4] + v18;
              v21 = v20 + v19;
              v22 = uArg22[5] + v20;
              v23 = v22 + v21;
              v24 = uArg22[6] + v22;
              v25 = v24 + v23;
              v26 = uArg22[7] + v24;
              v27 = v26 + v25;
              v28 = uArg22[8] + v26;
              v29 = v28 + v27;
              v30 = uArg22[9] + v28;
              v31 = v30 + v29;
              v32 = uArg22[10] + v30;
              v33 = v32 + v31;
              v34 = uArg22[11] + v32;
              v35 = v34 + v33;
              v36 = uArg22[12] + v34;
              v37 = v36 + v35;
              v38 = uArg22[13] + v36;
              v39 = v38 + v37;
              v40 = uArg22[14] + v38;
              v41 = v40 + v39;
              v5 = uArg22[15] + v40;
              v4 = v5 + v41;
              uArg22 += 16;
            }
            v5 %= 0xFFF1u;
            --v10;
            v4 %= 0xFFF1u;
          }
          while ( v10 != 0 );
        }
        if ( uArg32 != 0 )
        {
          if ( uArg32 >= 0x10 )
          {
            v42 = uArg32 >> 4;
            do
            {
              v43 = *uArg22 + v5;
              v44 = v43 + v4;
              v45 = uArg22[1] + v43;
              v46 = v45 + v44;
              v47 = uArg22[2] + v45;
              v48 = v47 + v46;
              v49 = uArg22[3] + v47;
              v50 = v49 + v48;
              v51 = uArg22[4] + v49;
              v52 = v51 + v50;
              v53 = uArg22[5] + v51;
              v54 = v53 + v52;
              v55 = uArg22[6] + v53;
              v56 = v55 + v54;
              v57 = uArg22[7] + v55;
              v58 = v57 + v56;
              v59 = uArg22[8] + v57;
              v60 = v59 + v58;
              v61 = uArg22[9] + v59;
              v62 = v61 + v60;
              v63 = uArg22[10] + v61;
              v64 = v63 + v62;
              v65 = uArg22[11] + v63;
              v66 = v65 + v64;
              v67 = uArg22[12] + v65;
              v68 = v67 + v66;
              v69 = uArg22[13] + v67;
              v70 = v69 + v68;
              v71 = uArg22[14] + v69;
              v72 = v71 + v70;
              v5 = uArg22[15] + v71;
              uArg32 -= 16;
              v4 = v5 + v72;
              uArg22 += 16;
              --v42;
            }
            while ( v42 != 0 );
          }
          for ( ; uArg32 != 0; --uArg32 )
          {
            v5 += *uArg22++;
            v4 += v5;
          }
          v5 %= 0xFFF1u;
          v4 %= 0xFFF1u;
        }
        return v5 | (v4 << 16);
      }
      else
      {
        if ( uArg3 != 0 )
        {
          do
          {
            v5 += *uArg22++;
            v4 += v5;
            --uArg32;
          }
          while ( uArg32 != 0 );
        }
        if ( v5 >= 0xFFF1 )
          v5 -= 65521;
        return v5 | ((v4 % 0xFFF1) << 16);
      }
    }
    else
    {
      return 1;
    }
  }
}


// ------------------------------------------------------------
// 0x6556B0 sub_6556B0
// ------------------------------------------------------------
// 【解读】
//   crc32 内部（字节序分派/表构建 usercall）。zlib 标准体。
// ------------------------------------------------------------
int /*usercall*/ sub_6556B0@<eax>(int nArg1@<eax>, unsigned int uArg2@<edx>, uint32_t *pArg3@<ecx>)
{
  unsigned int uArg22; // esi
  unsigned int i; // eax
  unsigned int v5; // edi
  unsigned int v6; // eax
  unsigned int v7; // edx
  uint32_t *v8; // ecx
  unsigned int v9; // eax
  unsigned int v10; // edx
  unsigned int v11; // eax
  unsigned int v12; // edx
  unsigned int v13; // eax
  unsigned int v14; // edx
  unsigned int v16; // [esp+8h] [ebp-4h]
  unsigned int v17; // [esp+8h] [ebp-4h]

  uArg22 = uArg2;
  for ( i = ~nArg1; uArg22 != 0; --uArg22 )
  {
    if ( ((uint8_t)pArg3 & 3) == 0 )
      break;
    i = dword_73FEC0[(uint8_t)(i ^ *(uint8_t *)pArg3)] ^ (i >> 8);
    pArg3 = (uint32_t *)((char *)pArg3 + 1);
  }
  if ( uArg22 >= 0x20 )
  {
    v5 = uArg22 >> 5;
    do
    {
      v6 = *pArg3 ^ i;
      v7 = pArg3[1]
         ^ dword_740AC0[(uint8_t)v6]
         ^ dword_73FEC0[HIBYTE(v6)]
         ^ dword_7406C0[BYTE1(v6)]
         ^ dword_7402C0[BYTE2(v6)];
      v8 = pArg3 + 1;
      v9 = v8[1]
         ^ dword_740AC0[(uint8_t)v7]
         ^ dword_73FEC0[HIBYTE(v7)]
         ^ dword_7406C0[BYTE1(v7)]
         ^ dword_7402C0[BYTE2(v7)];
      ++v8;
      v10 = v8[1]
          ^ dword_740AC0[(uint8_t)v9]
          ^ dword_73FEC0[HIBYTE(v9)]
          ^ dword_7406C0[BYTE1(v9)]
          ^ dword_7402C0[BYTE2(v9)];
      ++v8;
      v11 = v8[1]
          ^ dword_740AC0[(uint8_t)v10]
          ^ dword_73FEC0[HIBYTE(v10)]
          ^ dword_7406C0[BYTE1(v10)]
          ^ dword_7402C0[BYTE2(v10)];
      v8 += 2;
      v12 = *v8
          ^ dword_740AC0[(uint8_t)v11]
          ^ dword_73FEC0[HIBYTE(v11)]
          ^ dword_7406C0[BYTE1(v11)]
          ^ dword_7402C0[BYTE2(v11)];
      v13 = v8[1]
          ^ dword_740AC0[(uint8_t)v12]
          ^ dword_73FEC0[HIBYTE(v12)]
          ^ dword_7406C0[BYTE1(v12)]
          ^ dword_7402C0[BYTE2(v12)];
      ++v8;
      v16 = v8[1]
          ^ dword_740AC0[(uint8_t)v13]
          ^ dword_73FEC0[HIBYTE(v13)]
          ^ dword_7406C0[BYTE1(v13)]
          ^ dword_7402C0[BYTE2(v13)];
      pArg3 = v8 + 2;
      i = dword_740AC0[(uint8_t)v16]
        ^ dword_73FEC0[HIBYTE(v16)]
        ^ dword_7406C0[BYTE1(v16)]
        ^ dword_7402C0[BYTE2(v16)];
      uArg22 -= 32;
      --v5;
    }
    while ( v5 != 0 );
  }
  if ( uArg22 >= 4 )
  {
    v14 = uArg22 >> 2;
    do
    {
      v17 = *pArg3++ ^ i;
      uArg22 -= 4;
      --v14;
      i = dword_740AC0[(uint8_t)v17]
        ^ dword_73FEC0[HIBYTE(v17)]
        ^ dword_7406C0[BYTE1(v17)]
        ^ dword_7402C0[BYTE2(v17)];
    }
    while ( v14 != 0 );
  }
  for ( ; uArg22 != 0; --uArg22 )
  {
    i = dword_73FEC0[(uint8_t)(i ^ *(uint8_t *)pArg3)] ^ (i >> 8);
    pArg3 = (uint32_t *)((char *)pArg3 + 1);
  }
  return ~i;
}



// ------------------------------------------------------------
// 0x655990 sub_655990
// ------------------------------------------------------------
// 【解读】
//   crc32 包装（转 sub_6556B0）。
// ------------------------------------------------------------
int /*cdecl*/ sub_655990(int nArg1, uint32_t *uArg2, unsigned int uArg3)
{
  if ( uArg2 != nullptr )
    return sub_6556B0(nArg1, uArg3, uArg2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x6559B0 sub_6559B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6559B0(uint32_t **this, int nArg2, int nArg3)
{
  return (*(int (/*thiscall*/ **)(uint32_t, int))(**(this + 4) + 4))(*(this + 4), nArg2);
}



// ------------------------------------------------------------
// 0x6559D0 sub_6559D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6559D0(uint32_t **this, int nArg2, int nArg3)
{
  return (*(int (/*thiscall*/ **)(uint32_t, int))(**(this + 4) + 12))(*(this + 4), nArg2);
}



// ------------------------------------------------------------
// 0x6559F0 sub_6559F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6559F0(int this, int nArg2, int nArg3)
{
  return (***(int (/*thiscall*/ ****)(uint32_t, uint32_t))(this + 16))(*(uint32_t *)(this + 16), *(uint32_t *)(this + 12));
}



// ------------------------------------------------------------
// 0x655A00 sub_655A00
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_655A00(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *v4; // edi

  for ( result = uArg1; result != uArg2; v4[4] = pArg3[4] )
  {
    v4 = result;
    *result = *pArg3;
    result[1] = pArg3[1];
    result[2] = pArg3[2];
    result[3] = pArg3[3];
    result += 5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x655A40 sub_655A40
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_655A40(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *uArg22; // ecx

  result = uArg2;
  if ( uArg2 != nullptr )
  {
    uArg22 = uArg2;
    result = uArg1;
    do
    {
      if ( result != nullptr )
      {
        *result = *pArg3;
        result[1] = pArg3[1];
        result[2] = pArg3[2];
        result[3] = pArg3[3];
        result[4] = pArg3[4];
      }
      result += 5;
      uArg22 = (uint32_t *)((char *)uArg22 - 1);
    }
    while ( uArg22 != nullptr );
  }
  return result;
}



// ============================================================
// SECTION 0x655A90 — Neople 调试打印（enduranceTime/waitTime/elapsedTime 计时调试 → 0x40BE20 控制台）
// ============================================================
// ------------------------------------------------------------
// 0x655A90 sub_655A90
// ------------------------------------------------------------
// 【解读】
//   计时调试打印: "-------------%d---------------" 与
//    "%d enduranceTime_=>%f waitTime_=>%f elapsedTime=>%f" → sub_40BE20（_DEBUG 控制台）。
// ------------------------------------------------------------
void /*thiscall*/ sub_655A90(int this, float fArg2)
{
  double fld_1C; // st7
  int fld_28; // eax
  int fld_4; // eax
  int fld_C; // edi
  unsigned int v7; // ebx
  int v8; // edi
  int fld_30; // eax
  float *fld_302; // eax
  double fArg23; // st7
  int fld_307; // ecx
  int fld_308; // ecx
  double v14; // st7
  int v15; // ecx
  int fld_309; // edx
  int fld_3010; // ecx
  double fArg22; // st7
  int fld_303; // edx
  int fld_304; // ecx
  int fld_305; // ecx
  int fld_306; // ecx
  int fld_20; // eax
  int fld_3011; // ecx
  char fld_C2; // [esp+18h] [ebp-14h]
  float v26; // [esp+28h] [ebp-4h]

  fld_1C = fArg2 + *(float *)(this + 28);
  fld_28 = *(uint32_t *)(this + 40);
  v26 = 0.0;
  *(float *)(this + 28) = fld_1C;
  *(uint32_t *)(this + 32) = -1;
  if ( fld_28 < 2 )
    goto LABEL_2;
  if ( fld_1C > *(float *)(this + 24) )
  {
    fld_4 = *(uint32_t *)(this + 4) - 1;
    *(uint32_t *)(this + 28) = 0;
    if ( fld_4 != 0 )
    {
      if ( fld_4 == 1 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 16) + 8))(
          *(uint32_t *)(this + 16),
          *(uint32_t *)(this + 12));
        if ( *(uint8_t *)(this + 21) != 0 )
        {
          fld_C = *(uint32_t *)(this + 12) + 1;
          fld_C2 = *(uint8_t *)(this + 12) + 1;
          *(uint8_t *)(this + 21) = 0;
          *(uint32_t *)(this + 12) = fld_C;
          sub_40BE20("-------------%d---------------\n", fld_C2);
          *(uint32_t *)(this + 4) = 1;
        }
      }
    }
    else
    {
      (***(void (/*thiscall*/ ****)(uint32_t, uint32_t))(this + 16))(*(uint32_t *)(this + 16), *(uint32_t *)(this + 12));
    }
  }
  v7 = 0;
  v8 = 0;
  while ( 1 )
  {
    fld_30 = *(uint32_t *)(this + 48);
    if ( fld_30 == 0 || v7 >= (*(uint32_t *)(this + 52) - fld_30) / 20 )
      break;
    sub_40BE20("%d enduranceTime_=>%f waitTime_=>%f elapsedTime=>%f\n", v7);
    fld_302 = (float *)(v8 + *(uint32_t *)(this + 48));
    if ( *(uint32_t *)fld_302 == 3 )
      goto LABEL_32;
    if ( *(uint32_t *)(this + 4) == 1 )
    {
      fArg22 = fArg2;
      if ( *(uint32_t *)fld_302 == 1 )
      {
        fld_302[2] = 0.0;
        *(float *)(v8 + *(uint32_t *)(this + 48) + 12) = fArg22 + *(float *)(*(uint32_t *)(this + 48) + v8 + 12);
        fld_303 = *(uint32_t *)(this + 48);
        if ( *(float *)(this + 24) * 3.0 >= *(float *)(v8 + fld_303 + 12) )
          goto LABEL_32;
        *(float *)(v8 + fld_303 + 4) = *(float *)(this + 24) + *(float *)(v8 + fld_303 + 4);
        fld_304 = v8 + *(uint32_t *)(this + 48);
        if ( *(float *)(fld_304 + 4) > 60.0 )
          *(uint32_t *)(fld_304 + 4) = 1114636288;
        ++v7;
        *(uint32_t *)(v8 + *(uint32_t *)(this + 48) + 12) = 0;
        v8 += 20;
      }
      else
      {
        fld_302[2] = fArg22 + fld_302[2];
        fld_305 = v8 + *(uint32_t *)(this + 48);
        if ( *(float *)(this + 24) * 3.0 < *(float *)(fld_305 + 8) )
        {
          *(float *)(fld_305 + 4) = *(float *)(fld_305 + 4) - fArg2;
          fld_306 = v8 + *(uint32_t *)(this + 48);
          if ( v26 < (double)*(float *)(fld_306 + 8) )
          {
            *(uint32_t *)(this + 32) = v7;
            v26 = *(float *)(fld_306 + 8);
          }
        }
LABEL_32:
        ++v7;
        v8 += 20;
      }
    }
    else
    {
      if ( *(uint32_t *)(this + 4) != 2 )
        goto LABEL_32;
      fArg23 = fArg2;
      if ( *(uint32_t *)fld_302 == 2 )
      {
        fld_302[2] = 0.0;
        *(float *)(v8 + *(uint32_t *)(this + 48) + 12) = fArg23 + *(float *)(*(uint32_t *)(this + 48) + v8 + 12);
        fld_307 = v8 + *(uint32_t *)(this + 48);
        if ( *(float *)(this + 24) * 6.0 >= *(float *)(fld_307 + 12) )
          goto LABEL_32;
        *(float *)(fld_307 + 4) = *(float *)(fld_307 + 4) + *(float *)(this + 24);
        fld_308 = *(uint32_t *)(this + 48);
        v14 = *(float *)(fld_308 + v8 + 4);
        v15 = v8 + fld_308;
        if ( v14 > 60.0 )
          *(uint32_t *)(v15 + 4) = 1114636288;
        ++v7;
        *(uint32_t *)(v8 + *(uint32_t *)(this + 48) + 12) = 0;
        v8 += 20;
      }
      else
      {
        fld_302[2] = fArg23 + fld_302[2];
        fld_309 = *(uint32_t *)(this + 48);
        if ( *(float *)(this + 24) * 6.0 >= *(float *)(v8 + fld_309 + 8) )
          goto LABEL_32;
        *(float *)(v8 + fld_309 + 4) = *(float *)(v8 + fld_309 + 4) - fArg2;
        fld_3010 = v8 + *(uint32_t *)(this + 48);
        if ( v26 >= (double)*(float *)(fld_3010 + 8) )
          goto LABEL_32;
        *(uint32_t *)(this + 32) = v7++;
        v26 = *(float *)(fld_3010 + 8);
        v8 += 20;
      }
    }
  }
  fld_20 = *(uint32_t *)(this + 32);
  if ( fld_20 < 0 )
  {
LABEL_2:
    *(uint32_t *)(this + 8) = 3;
    return;
  }
  fld_3011 = *(uint32_t *)(this + 48) + 20 * fld_20;
  if ( *(float *)(this + 24) * 3.0 >= *(float *)(fld_3011 + 8) )
  {
    if ( *(float *)(this + 24) + *(float *)(this + 24) < *(float *)(fld_3011 + 8) )
    {
      *(uint32_t *)(this + 8) = 1;
      return;
    }
    if ( *(float *)(fld_3011 + 8) > (double)*(float *)(this + 24) )
    {
      *(uint32_t *)(this + 8) = 2;
      return;
    }
    goto LABEL_2;
  }
  *(uint32_t *)(this + 8) = 0;
  if ( *(uint8_t *)(fld_3011 + 16) == 0 )
    *(uint8_t *)(fld_3011 + 16) = 1;
}


// ------------------------------------------------------------
// 0x655DB0 sub_655DB0
// ------------------------------------------------------------
char /*thiscall*/ sub_655DB0(uint32_t *this)
{
  int fld_e12; // edi
  unsigned int v2; // esi
  int v3; // ebx
  int fld_e122; // edx

  fld_e12 = *(this + 12);
  v2 = 0;
  v3 = 0;
  while ( fld_e12 != 0 && v2 < (*(this + 13) - fld_e12) / 20 )
  {
    fld_e122 = *(uint32_t *)(*(this + 12) + v3);
    if ( fld_e122 != 3 && fld_e122 != 1 )
      return 0;
    ++v2;
    v3 += 20;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x655E10 sub_655E10
// ------------------------------------------------------------
char /*thiscall*/ sub_655E10(uint32_t *this)
{
  int fld_e12; // edi
  unsigned int v2; // esi
  int v3; // ebx
  int fld_e122; // edx

  fld_e12 = *(this + 12);
  v2 = 0;
  v3 = 0;
  while ( fld_e12 != 0 && v2 < (*(this + 13) - fld_e12) / 20 )
  {
    fld_e122 = *(uint32_t *)(*(this + 12) + v3);
    if ( fld_e122 != 3 && fld_e122 != 2 )
      return 0;
    ++v2;
    v3 += 20;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x655E70 sub_655E70
// ------------------------------------------------------------
double /*thiscall*/ sub_655E70(uint32_t *this, int nArg2)
{
  return *(float *)(*(this + 12) + 20 * nArg2 + 4);
}



// ------------------------------------------------------------
// 0x655E90 sub_655E90
// ------------------------------------------------------------
int /*thiscall*/ sub_655E90(uint32_t *this, int nArg2)
{
  int result; // eax

  result = *(this + 12) + 20 * nArg2;
  *(uint32_t *)(result + 4) = 1114636288;
  return result;
}



// ------------------------------------------------------------
// 0x655EB0 sub_655EB0
// ------------------------------------------------------------
void /*thiscall*/ sub_655EB0(uint32_t *this, int nArg2, float fArg3)
{
  int v3; // edx
  uint32_t *fld_e12; // eax
  int fld_e122; // esi

  v3 = 20 * nArg2;
  fld_e12 = (uint32_t *)(20 * nArg2 + *(this + 12));
  if ( *fld_e12 != 3 )
  {
    *fld_e12 = 0;
    *(uint32_t *)(v3 + *(this + 12) + 8) = 0;
  }
  fld_e122 = v3 + *(this + 12);
  if ( *(float *)(fld_e122 + 8) < (double)fArg3 )
  {
    *(uint32_t *)(fld_e122 + 4) = 1114636288;
    *(float *)(v3 + *(this + 12) + 8) = fArg3;
    *(uint32_t *)(v3 + *(this + 12) + 12) = 0;
    *(uint8_t *)(*(this + 12) + 20 * *(this + 8) + 16) = 1;
  }
}



// ------------------------------------------------------------
// 0x655F20 sub_655F20
// ------------------------------------------------------------
void /*thiscall*/ sub_655F20(uint32_t *this, int nArg2)
{
  uint32_t *fld_e12; // eax
  int v3; // ecx
  unsigned int v4; // edi
  int i; // esi
  int v6; // eax
  int v7; // eax
  int v8; // edx
  uint32_t *v9; // eax

  if ( *(this + 1) == 2 )
  {
    fld_e12 = (uint32_t *)(*(this + 12) + 20 * nArg2);
    if ( *fld_e12 != 3 )
      *fld_e12 = 2;
    if ( sub_655E10(this) != 0 )
    {
      v4 = 0;
      for ( i = 0; ; i += 20 )
      {
        v6 = *(uint32_t *)(v3 + 48);
        if ( v6 == 0 || v4 >= (*(uint32_t *)(v3 + 52) - v6) / 20 )
          break;
        v7 = *(uint32_t *)(v3 + 48);
        v8 = *(uint32_t *)(v7 + i);
        v9 = (uint32_t *)(i + v7);
        if ( v8 != 3 )
        {
          *v9 = 0;
          *(uint32_t *)(i + *(uint32_t *)(v3 + 48) + 8) = 0;
        }
        ++v4;
      }
      *(uint8_t *)(v3 + 21) = 1;
    }
  }
}



// ------------------------------------------------------------
// 0x655FA0 sub_655FA0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_655FA0(int this)
{
  unsigned int v1; // edi
  int i; // esi
  unsigned int result; // eax
  int fld_30; // eax
  int v5; // edx
  uint32_t *v6; // eax

  v1 = 0;
  for ( i = 0; ; i += 20 )
  {
    result = *(uint32_t *)(this + 48);
    if ( result == 0 )
      break;
    result = (int)(*(uint32_t *)(this + 52) - result) / 20;
    if ( v1 >= result )
      break;
    fld_30 = *(uint32_t *)(this + 48);
    v5 = *(uint32_t *)(fld_30 + i);
    v6 = (uint32_t *)(i + fld_30);
    if ( v5 != 3 )
    {
      *v6 = 0;
      *(uint32_t *)(i + *(uint32_t *)(this + 48) + 8) = 0;
    }
    *(uint32_t *)(i + *(uint32_t *)(this + 48) + 4) = 1114636288;
    *(uint32_t *)(i + *(uint32_t *)(this + 48) + 12) = 0;
    ++v1;
    *(uint8_t *)(i + *(uint32_t *)(this + 48) + 16) = 0;
  }
  *(uint32_t *)(this + 12) = 0;
  *(uint8_t *)(this + 20) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 8) = 3;
  *(uint32_t *)(this + 32) = -1;
  *(uint32_t *)(this + 36) = -1082130432;
  return result;
}



// ------------------------------------------------------------
// 0x656030 sub_656030
// ------------------------------------------------------------
void /*thiscall*/ sub_656030(uint32_t *this, int nArg2)
{
  uint32_t *fld_e12; // edx
  int v3; // ecx

  if ( *(this + 1) == 1 )
  {
    fld_e12 = (uint32_t *)(20 * nArg2 + *(this + 12));
    if ( *fld_e12 != 3 )
    {
      *fld_e12 = 1;
      *(uint32_t *)(20 * nArg2 + *(this + 12) + 8) = 0;
    }
    if ( sub_655DB0(this) != 0 )
      *(uint32_t *)(v3 + 4) = 2;
  }
}



// ------------------------------------------------------------
// 0x656080 sub_656080
// ------------------------------------------------------------
void /*thiscall*/ sub_656080(uint32_t *this, int nArg2)
{
  sub_655F20(this, nArg2);
}



// ------------------------------------------------------------
// 0x656090 sub_656090
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_656090(void *this)
{
  unsigned int result; // eax
  int v2; // ecx

  result = sub_655FA0((int)this);
  *(uint32_t *)(v2 + 4) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x6560A0 sub_6560A0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_6560A0(int this)
{
  unsigned int result; // eax

  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  result = sub_655FA0(this);
  *(uint32_t *)(this + 4) = 0;
  return result;
}



// ============================================================
// SECTION 0x6560D0 — 观察者/容器族（vector 工具 + 对象分配，供上层效果系统）
// ============================================================
// ------------------------------------------------------------
// 0x6560D0 sub_6560D0 [串: "vector<T> too long"]
// ------------------------------------------------------------
void /*noreturn*/ sub_6560D0()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x656140 sub_656140
// ------------------------------------------------------------
int /*thiscall*/ sub_656140(int *this, uint32_t *pArg2, unsigned int uArg3, uint32_t *Block)
{
  int v5; // edx
  int fld_e1; // ebx
  int v7; // ecx
  int v8; // edx
  int result; // eax
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v14; // ecx
  int fld_e27; // eax
  int v16; // ebx
  int fld_e13; // eax
  unsigned int v18; // edi
  void *fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-48h]
  int fld_e25; // [esp-Ch] [ebp-3Ch]
  unsigned int fld_e24; // [esp-8h] [ebp-38h]
  int v25; // [esp+0h] [ebp-30h] BYREF
  uint32_t v26[6]; // [esp+Ch] [ebp-24h] BYREF
  int v27; // [esp+2Ch] [ebp-4h]
  int v28; // [esp+38h] [ebp+8h]
  uint32_t *v29; // [esp+3Ch] [ebp+Ch]
  char *Blocka; // [esp+40h] [ebp+10h]
  void *Blockb; // [esp+40h] [ebp+10h]

  v5 = Block[1];
  fld_e1 = *(this + 1);
  v26[0] = *Block;
  v7 = Block[2];
  v26[1] = v5;
  v8 = Block[3];
  result = Block[4];
  v26[5] = &v25;
  v26[2] = v7;
  v26[3] = v8;
  v26[4] = result;
  if ( fld_e1 != 0 )
  {
    result = 1717986919 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 20;
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 20;
    else
      fld_e2 = 0;
    if ( 214748364 - fld_e2 < uArg3 )
      sub_6560D0(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 20;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);
      Blockb = fld_e23;
      if ( ((uint8_t *)fld_e23 - (uint8_t *)pArg2) / 20 >= uArg3 )
      {
        v28 = (int)fld_e23 - 20 * uArg3;
        *(this + 2) = sub_4FBDE0(v28, fld_e23, fld_e23);
        sub_57A4A0(pArg2, v28, Blockb);
        return (int)sub_655A00(pArg2, &pArg2[5 * uArg3], v26);
      }
      else
      {
        sub_4FBDE0(pArg2, fld_e23, &pArg2[5 * uArg3]);
        fld_e24 = uArg3 - (*(this + 2) - (int)pArg2) / 20;
        fld_e25 = *(this + 2);
        v27 = 2;
        sub_57A4C0(fld_e25, fld_e24, v26);
        fld_e26 = 20 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        return (int)sub_655A00(pArg2, (uint32_t *)(fld_e26 - 20 * uArg3), v26);
      }
    }
    else
    {
      if ( 214748364 - (fld_e3 >> 1) >= fld_e3 )
        v14 = (fld_e3 >> 1) + fld_e3;
      else
        v14 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 20;
      else
        fld_e27 = 0;
      if ( v14 < uArg3 + fld_e27 )
        v14 = uArg3 + sub_45E580(this);
      v16 = 20 * v14;
      Blocka = (char *)operator new(20 * v14);
      fld_e12 = *(this + 1);
      v27 = 0;
      v29 = (uint32_t *)sub_4FBDE0(fld_e12, pArg2, Blocka);
      sub_655A40(v29, (uint32_t *)uArg3, v26);
      sub_4FBDE0(pArg2, *(this + 2), &v29[5 * uArg3]);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 20;
      v18 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v16];
      *(this + 2) = (int)&Blocka[20 * v18];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x656400 sub_656400
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_656400(int *this, uint32_t *uArg2, uint32_t *uArg3, uint32_t *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 20 != 0 )
    v6 = ((int)uArg3 - fld_e1) / 20;
  else
    v6 = 0;
  sub_656140(this, uArg3, 1u, Block);
  *uArg2 = *(this + 1) + 20 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x656470 sub_656470
// ------------------------------------------------------------
void */*thiscall*/ sub_656470(void *this, int nArg2)
{
  *(uint32_t *)this = &off_741F20;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 4) = nArg2;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 1) = 0;
  *((uint32_t *)this + 8) = -1;
  *((uint8_t *)this + 21) = 0;
  *((uint32_t *)this + 2) = 3;
  if ( *((uint32_t *)this + 12) != 0 )
    j__free(*((void **)this + 12));
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x6564D0 sub_6564D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6564D0(int *this, uint32_t *Block)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  uint32_t *fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 20;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 20 )
    return sub_656400(this, &Block, (uint32_t *)*(this + 2), Block);
  fld_e22 = (uint32_t *)*(this + 2);
  result = sub_655A40(fld_e22, (uint32_t *)1, Block);
  *(this + 2) = (int)(fld_e22 + 5);
  return result;
}



// ------------------------------------------------------------
// 0x656560 sub_656560
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_656560(int *this, int pArg2)
{
  int fld_e12; // eax
  int *pThis_B; // esi
  uint32_t *fld_e122; // eax
  unsigned int v7; // edi
  unsigned int result; // eax
  uint32_t Block[5]; // [esp+Ch] [ebp-14h] BYREF
  int v10; // [esp+28h] [ebp+8h]
  int i; // [esp+28h] [ebp+8h]

  fld_e12 = *(this + 12);
  pThis_B = this + 11;
  if ( fld_e12 != 0 )
    fld_e12 = (*(this + 13) - fld_e12) / 20;
  if ( fld_e12 < pArg2 + 1 )
  {
    v10 = pArg2 + 1 - fld_e12;
    do
    {
      sub_6564D0(pThis_B, Block);
      --v10;
    }
    while ( v10 != 0 );
  }
  fld_e122 = (uint32_t *)(*(this + 12) + 20 * pArg2);
  if ( *fld_e122 != 3 )
    *fld_e122 = 3;
  sub_655FA0((int)this);
  v7 = 0;
  *(this + 10) = 0;
  for ( i = 0; ; i += 20 )
  {
    result = pThis_B[1];
    if ( result == 0 )
      break;
    result = (int)(pThis_B[2] - result) / 20;
    if ( v7 >= result )
      break;
    if ( *(uint32_t *)(*(this + 12) + i) != 3 )
      ++*(this + 10);
    ++v7;
  }
  *(this + 9) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x656630 sub_656630
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_656630(int *this, int pArg2)
{
  int fld_e12; // eax
  int *pThis_B; // ebx
  unsigned int v6; // edi
  unsigned int result; // eax
  uint32_t Block[5]; // [esp+Ch] [ebp-14h] BYREF
  int v9; // [esp+28h] [ebp+8h]
  int i; // [esp+28h] [ebp+8h]

  fld_e12 = *(this + 12);
  pThis_B = this + 11;
  if ( fld_e12 != 0 )
    fld_e12 = (*(this + 13) - fld_e12) / 20;
  if ( fld_e12 < pArg2 + 1 )
  {
    v9 = pArg2 + 1 - fld_e12;
    do
    {
      sub_6564D0(pThis_B, Block);
      --v9;
    }
    while ( v9 != 0 );
  }
  *(uint32_t *)(*(this + 12) + 20 * pArg2 + 4) = 1114636288;
  *(uint32_t *)(20 * pArg2 + *(this + 12) + 8) = 0;
  *(uint32_t *)(20 * pArg2 + *(this + 12) + 12) = 0;
  *(uint8_t *)(20 * pArg2 + *(this + 12) + 16) = 0;
  *(uint32_t *)(20 * pArg2 + *(this + 12)) = 0;
  *(uint32_t *)(20 * pArg2 + *(this + 12) + 8) = 0;
  *(this + 10) = 0;
  v6 = 0;
  for ( i = 0; ; i += 20 )
  {
    result = pThis_B[1];
    if ( result == 0 )
      break;
    result = (int)(pThis_B[2] - result) / 20;
    if ( v6 >= result )
      break;
    if ( *(uint32_t *)(*(this + 12) + i) != 3 )
      ++*(this + 10);
    ++v6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x656720 sub_656720
// ------------------------------------------------------------
char /*thiscall*/ sub_656720(uint32_t *this, const void *pArg2, int16_t uArg3)
{
  int fld_e512; // ecx
  int fld_e5122; // ecx

  fld_e512 = *(this + 512);
  if ( fld_e512 + uArg3 > *(this + 515) )
    return 0;
  *(uint16_t *)((char *)this + fld_e512) = uArg3;
  fld_e5122 = *(this + 512) + 2;
  *(this + 512) = fld_e5122;
  qmemcpy((char *)this + fld_e5122, pArg2, uArg3);
  *(this + 512) += uArg3;
  return 1;
}



// ------------------------------------------------------------
// 0x656790 sub_656790
// ------------------------------------------------------------
int /*thiscall*/ sub_656790(uint32_t *this, int nArg2)
{
  *(uint32_t *)(*(this + 8) + 1088) = nArg2;
  return 1;
}



// ------------------------------------------------------------
// 0x6567B0 sub_6567B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6567B0(int this, int nArg2)
{
  *(uint32_t *)(*(uint32_t *)(this + 32) + 1096) = nArg2;
  sub_658CB0(*(uint32_t *)(this + 32));
  sub_657970(*(LPVOID *)(this + 32));
  *(uint32_t *)(this + 44) = GetTickCount();
  return 1;
}



// ------------------------------------------------------------
// 0x6567F0 sub_6567F0
// ------------------------------------------------------------
int /*cdecl*/ sub_6567F0(int nArg1)
{
  dword_79693C = nArg1;
  return nArg1;
}



// ------------------------------------------------------------
// 0x656800 sub_656800
// ------------------------------------------------------------
int sub_656800()
{
  return dword_79693C;
}



// ============================================================
// SECTION 0x656810 — MSVC ConcRT 运行时桩（ContextBase::SweepUnstructured ×3 —— 编译器注入，非游戏逻辑）
// ============================================================
// ------------------------------------------------------------
// 0x656810 ?SweepUnstructured@ContextBase@details@Concurrency@@QAEXP6A_NPAV_UnrealizedChore@23@PAX@Z12@Z
// ------------------------------------------------------------
// 【解读】
//   MSVC ConcRT 运行时桩（Concurrency::details::ContextBase::SweepUnstructured 实例 1）—— 编译器注入。
// ------------------------------------------------------------
void /*userpurge*/ Concurrency::details::ContextBase::SweepUnstructured(
        bool (/*cdecl*/ *uArg1)(struct Concurrency::details::_UnrealizedChore *, void *),
        void *pArg2,
        bool (/*cdecl*/ *uArg3)(struct Concurrency::details::_UnrealizedChore *, void *))
{
  sub_658C80(uArg1, pArg2);
}



// ------------------------------------------------------------
// 0x656820 ?SweepUnstructured@ContextBase@details@Concurrency@@QAEXP6A_NPAV_UnrealizedChore@23@PAX@Z12@Z_0
// ------------------------------------------------------------
// 【解读】
//   同上（实例 2）。
// ------------------------------------------------------------
void /*userpurge*/ Concurrency::details::ContextBase::SweepUnstructured(
        bool (/*cdecl*/ *uArg1)(struct Concurrency::details::_UnrealizedChore *, void *),
        void *pArg2,
        bool (/*cdecl*/ *uArg3)(struct Concurrency::details::_UnrealizedChore *, void *))
{
  sub_6588B0(uArg1);
}



// ------------------------------------------------------------
// 0x656830 ?SweepUnstructured@ContextBase@details@Concurrency@@QAEXP6A_NPAV_UnrealizedChore@23@PAX@Z12@Z_1
// ------------------------------------------------------------
// 【解读】
//   同上（实例 3）。
// ------------------------------------------------------------
void /*userpurge*/ Concurrency::details::ContextBase::SweepUnstructured(
        bool (/*cdecl*/ *uArg1)(struct Concurrency::details::_UnrealizedChore *, void *),
        void *pArg2,
        bool (/*cdecl*/ *uArg3)(struct Concurrency::details::_UnrealizedChore *, void *))
{
  sub_6588C0(uArg1);
}



// ============================================================
// SECTION 0x656840 — 定时器/调度容器（GetTickCount / timeGetTime 节流链表）
// ============================================================
// ------------------------------------------------------------
// 0x656840 sub_656840
// ------------------------------------------------------------
int /*thiscall*/ sub_656840(uint32_t *this)
{
  return *(uint32_t *)(*(this + 8) + 1096);
}



// ------------------------------------------------------------
// 0x656850 sub_656850
// ------------------------------------------------------------
int /*thiscall*/ sub_656850(uint32_t *this, int pArg2)
{
  int64_t v2; // rax

  LODWORD(v2) = *(this + pArg2);
  if ( (uint32_t)v2 != -1 )
    return (uint64_t)sub_658770(v2, 1116471296);
  return v2;
}



// ------------------------------------------------------------
// 0x656880 sub_656880
// ------------------------------------------------------------
void /*thiscall*/ sub_656880(uint32_t *this, int nArg2, void *Src, int16_t uArg4, int nArg5, char pszArg6)
{
  int v7; // eax
  int *v8; // ecx

  if ( *(uint32_t *)(*(this + 8) + 1096) != nArg2 )
  {
    v7 = sub_659510(Src, uArg4, nArg2, nArg5, pszArg6);
    v8 = this + nArg2;
    *v8 = 0;
    *v8 = v7;
  }
}



// ------------------------------------------------------------
// 0x6568C0 sub_6568C0
// ------------------------------------------------------------
int /*thiscall*/ sub_6568C0(char *this, int nArg2)
{
  char *pThis_4; // esi
  int result; // eax

  pThis_4 = this + 4 * nArg2;
  result = *(uint32_t *)pThis_4;
  if ( *(uint32_t *)pThis_4 != -1 )
  {
    result = sub_659600(*(uint32_t *)pThis_4);
    *(uint32_t *)pThis_4 = 0;
    *(uint32_t *)pThis_4 = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6568F0 sub_6568F0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_6568F0(
        int a1,
        uint32_t *a2,
        uint32_t *a3,
        uint32_t *a4,
        int a5,
        int a6,
        int a7,
        uint32_t *a8,
        uint32_t *a9)
{
  *a4 = 0;
  *a3 = 0;
  *a2 = 0;
  sub_658C10(a1, a2, a3, a4, a5, a6, a7);
  *a8 = dword_796900;
  *a9 = dword_9B9D58[516 * a1];
  return a9;
}



// ------------------------------------------------------------
// 0x656950 sub_656950
// ------------------------------------------------------------
int /*stdcall*/ sub_656950(int nArg1, int nArg2)
{
  dword_9B9D5C[516 * nArg1] = nArg2;
  return 2064 * nArg1;
}



// ------------------------------------------------------------
// 0x656970 sub_656970
// ------------------------------------------------------------
int /*thiscall*/ sub_656970(uint32_t *this)
{
  int16_t *v2; // esi
  uint32_t *pThis; // edi
  int result; // eax

  v2 = &word_9B9D50;
  pThis = this;
  do
  {
    if ( *(uint32_t *)v2 != 0 )
    {
      result = sub_657FD0(v2 - 1024, (void *)(uint16_t)*v2, *pThis, *(uint8_t *)(*(this + 8) + 1096), 0);
      *((uint32_t *)v2 + 1) = 0;
      *(uint32_t *)v2 = 0;
    }
    v2 += 1032;
    ++pThis;
  }
  while ( (int)v2 < (int)word_9BDDD0 );
  return result;
}



// ------------------------------------------------------------
// 0x6569D0 sub_6569D0
// ------------------------------------------------------------
// 【解读】
//   通用双向链表清空器: free 全部节点 + 哨兵自指 + 计数清零。
//   全引擎复用（0x40/0x41 区大量析构链调用）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6569D0(uint32_t *this)
{
  uint32_t **fld_e1; // ecx
  uint32_t *result; // eax
  bool fld_e12; // zf
  uint32_t *v5; // edi

  fld_e1 = (uint32_t **)*(this + 1);
  result = *fld_e1;
  *fld_e1 = fld_e1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  fld_e12 = result == (uint32_t *)*(this + 1);
  *(this + 2) = 0;
  if ( !fld_e12 )
  {
    do
    {
      v5 = (uint32_t *)*result;
      j__free(result);
      result = v5;
    }
    while ( v5 != (uint32_t *)*(this + 1) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x656A10 sub_656A10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_656A10(uint32_t *this)
{
  uint32_t *pThis; // edi
  int16_t *v3; // esi
  uint32_t **fld_e13; // ecx
  uint32_t *result; // eax
  bool fld_e132; // zf
  uint32_t *v7; // esi

  pThis = this;
  v3 = &word_9B9D50;
  do
  {
    if ( *pThis != -1 )
    {
      sub_659600(*pThis);
      *pThis = 0;
      *pThis = -1;
    }
    *((uint32_t *)v3 + 1) = 0;
    *(uint32_t *)v3 = 0;
    v3 += 1032;
    ++pThis;
  }
  while ( (int)v3 < (int)word_9BDDD0 );
  sub_658900(*(this + 8));
  fld_e13 = (uint32_t **)*(this + 13);
  result = *fld_e13;
  *fld_e13 = fld_e13;
  *(uint32_t *)(*(this + 13) + 4) = *(this + 13);
  fld_e132 = result == (uint32_t *)*(this + 13);
  *(this + 14) = 0;
  if ( !fld_e132 )
  {
    do
    {
      v7 = (uint32_t *)*result;
      j__free(result);
      result = v7;
    }
    while ( v7 != (uint32_t *)*(this + 13) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x656AA0 sub_656AA0
// ------------------------------------------------------------
char /*thiscall*/ sub_656AA0(int this)
{
  uint32_t *fld_34; // eax
  uint32_t *v3; // edi
  int v4; // esi
  uint32_t **fld_342; // ecx
  uint32_t *v6; // eax
  bool fld_343; // zf
  uint32_t *v8; // esi
  uint16_t k; // ax
  uint16_t j; // ax
  int v11; // edx
  int dword_7968FC2; // eax
  int16_t v13; // cx
  int v14; // eax
  uint32_t *i; // [esp+Ch] [ebp-810h]
  uint8_t v17[6]; // [esp+10h] [ebp-80Ch] BYREF
  char v18; // [esp+16h] [ebp-806h] BYREF
  uint8_t v19; // [esp+17h] [ebp-805h] BYREF
  uint8_t v20[2048]; // [esp+18h] [ebp-804h] BYREF
  int dword_796E502; // [esp+818h] [ebp-4h]

  dword_796E502 = dword_796E50;
  fld_34 = *(uint32_t **)(this + 52);
  v3 = (uint32_t *)*fld_34;
  for ( i = fld_34; v3 != i; v3 = (uint32_t *)*v3 )
  {
    v4 = v3[2];
    v18 = *(uint8_t *)(v4 + 2069);
    v19 = *(uint8_t *)(v4 + 2068);
    (***(void (/*thiscall*/ ****)(uint32_t, uint32_t, int, uint32_t))(this + 36))(
      *(uint32_t *)(this + 36),
      v19,
      v4 + 4,
      *(uint16_t *)(v4 + 2052));
    (**(void (/*thiscall*/ ***)(int, int))v4)(v4, 1);
  }
  fld_342 = *(uint32_t ***)(this + 52);
  v6 = *fld_342;
  *fld_342 = fld_342;
  *(uint32_t *)(*(uint32_t *)(this + 52) + 4) = *(uint32_t *)(this + 52);
  fld_343 = v6 == *(uint32_t **)(this + 52);
  *(uint32_t *)(this + 56) = 0;
  if ( !fld_343 )
  {
    do
    {
      v8 = (uint32_t *)*v6;
      j__free(v6);
      v6 = v8;
    }
    while ( v8 != *(uint32_t **)(this + 52) );
  }
  LOBYTE(k) = *(uint8_t *)(*(uint32_t *)(this + 32) + 1120);
  if ( (uint8_t)k != 0 )
  {
    sub_6585C0();
    sub_658850(*(uint32_t *)(this + 32));
    if ( GetTickCount() - *(uint32_t *)(this + 44) > 0x3C )
    {
      sub_656970((uint32_t *)this);
      *(uint32_t *)(this + 44) = GetTickCount();
    }
    for ( j = sub_657A90(v20, 2048, v17, &v19, &v18); j != 0; j = sub_657A90(v20, 2048, v17, &v19, &v18) )
      (***(void (/*thiscall*/ ****)(uint32_t, uint32_t, uint8_t *, uint32_t))(this + 36))(*(uint32_t *)(this + 36), v19, v20, j);
    for ( k = sub_657B80(v20, 2048, v17, &v19, &v18); k != 0; k = sub_657B80(v20, 2048, v17, &v19, &v18) )
    {
      v11 = k;
      if ( k <= dword_796904 )
      {
        qmemcpy(&word_7960F8, v20, k);
        dword_7968FC2 = 0;
        dword_7968FC = 0;
        dword_7968F8 = v11;
      }
      else
      {
        dword_7968FC2 = dword_7968FC;
        dword_796900 = 1;
      }
      while ( dword_7968FC2 < dword_7968F8 )
      {
        v13 = *(int16_t *)((char *)&word_7960F8 + dword_7968FC2);
        v14 = dword_7968FC2 + 2;
        dword_7968FC = v13 + v14;
        if ( v13 == 0 )
          break;
        (***(void (/*thiscall*/ ****)(uint32_t, uint32_t, char *, uint32_t))(this + 36))(
          *(uint32_t *)(this + 36),
          v19,
          (char *)&word_7960F8 + v14,
          v13);
        dword_7968FC2 = dword_7968FC;
      }
    }
  }
  return k;
}



// ------------------------------------------------------------
// 0x656D00 sub_656D00
// ------------------------------------------------------------
void /*thiscall*/ sub_656D00(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e8)(uint32_t, int); // ecx
  uint32_t *pThis_C; // esi

  sub_656A10(this);
  fld_e8 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 8);
  if ( fld_e8 != nullptr )
    (**fld_e8)(fld_e8, 1);
  pThis_C = this + 12;
  sub_6569D0(pThis_C);
  j__free((void *)pThis_C[1]);
  pThis_C[1] = 0;
}



// ============================================================
// SECTION 0x656D70 — 链表/网络对象工具（通用双向链表清空 0x6569D0 全引擎复用）
// ============================================================
// ------------------------------------------------------------
// 0x656D70 sub_656D70
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_656D70(uint32_t *this)
{
  uint32_t *pThis_C; // edi
  void *pMem; // eax
  int v4; // eax

  pThis_C = this + 12;
  *(this + 13) = sub_425940(this + 12);
  pThis_C[2] = 0;
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *this = -1;
  *(this + 1) = -1;
  *(this + 2) = -1;
  *(this + 3) = -1;
  *(this + 4) = -1;
  *(this + 5) = -1;
  *(this + 6) = -1;
  *(this + 7) = -1;
  *(this + 10) = -1;
  pMem = operator new(0x464u);
  if ( pMem != nullptr )
    v4 = sub_6596B0(pMem);
  else
    v4 = 0;
  *(this + 8) = v4;
  return this;
}



// ------------------------------------------------------------
// 0x656E20 sub_656E20 [串: "list<T> too long"]
// ------------------------------------------------------------
int /*thiscall*/ sub_656E20(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
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
    sub_4015C0("list<T> too long", 0x10u);
    v8 = 0;
    sub_401740(v5);
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x656EB0 sub_656EB0
// ------------------------------------------------------------
int /*thiscall*/ sub_656EB0(uint32_t *this, int nArg2)
{
  int fld_e1; // edi
  int v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);
  v4 = sub_40C0F0(fld_e1, *(uint32_t *)(fld_e1 + 4), nArg2);
  result = sub_656E20(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;
  **(uint32_t **)(v4 + 4) = v4;
  return result;
}



// ------------------------------------------------------------
// 0x656EF0 sub_656EF0
// ------------------------------------------------------------
char /*thiscall*/ sub_656EF0(int *this, const void *pArg2, int nArg3, int Block, int nArg5)
{
  int fld_e10; // ebx
  void *pMem; // eax
  int v8; // eax
  int fld_e13; // esi
  int v10; // ebx
  int v11; // eax
  uint32_t *v12; // esi

  fld_e10 = Block;
  if ( Block == -1 )
    fld_e10 = *(this + 10);
  if ( *(uint32_t *)(*(this + 8) + 1096) == fld_e10 )
  {
    pMem = operator new(0x818u);
    Block = (int)pMem;
    if ( pMem != nullptr )
      v8 = sub_659790(pMem);
    else
      v8 = 0;
    Block = v8;
    sub_6597C0(0, 0, nArg3, pArg2, fld_e10, 0);
    fld_e13 = *(this + 13);
    v10 = sub_40C0F0(fld_e13, *(uint32_t *)(fld_e13 + 4), &Block);
    LOBYTE(v11) = sub_656E20(this + 12, 1u);
    *(uint32_t *)(fld_e13 + 4) = v10;
    **(uint32_t **)(v10 + 4) = v10;
  }
  else
  {
    v11 = *(this + fld_e10);
    if ( v11 != -1 )
    {
      if ( nArg5 != 0 )
      {
        Block = 2064 * fld_e10;
        v12 = (uint32_t *)((char *)&unk_9B9550 + 2064 * fld_e10);
        for ( LOBYTE(v11) = sub_656720(v12, pArg2, nArg3);
              (uint8_t)v11 == 0;
              LOBYTE(v11) = sub_656720((uint32_t *)&unk_9B9550 + 516 * fld_e10, pArg2, nArg3) )
        {
          sub_657FD0(
            (char *)&unk_9B9550 + 2064 * fld_e10,
            (void *)*(uint16_t *)((char *)&word_9B9D50 + Block),
            *(this + fld_e10),
            *(uint8_t *)(*(this + 8) + 1096),
            0);
          v12[513] = 0;
          v12[512] = 0;
        }
      }
      else
      {
        LOBYTE(v11) = sub_658350(pArg2, nArg3, v11, *(uint8_t *)(*(this + 8) + 1096), 0);
      }
    }
  }
  return v11;
}



// ------------------------------------------------------------
// 0x657070 sub_657070
// ------------------------------------------------------------
int /*thiscall*/ sub_657070(int this, const void *pArg2, int nArg3)
{
  int result; // eax
  int fld_E; // edx

  result = this;
  fld_E = *(uint16_t *)(this + 14);
  if ( (uint16_t)nArg3 + fld_E > *(uint32_t *)(this + 8) )
    _CxxThrowException((char *)&nArg3 + 3, (_ThrowInfo *)&_TI1_AVException_CMsgCell__);
  qmemcpy((void *)(fld_E + *(uint32_t *)(this + 4)), pArg2, (uint16_t)nArg3);
  *(uint16_t *)(this + 14) += nArg3;
  return result;
}



// ------------------------------------------------------------
// 0x6570D0 sub_6570D0
// ------------------------------------------------------------
char /*thiscall*/ sub_6570D0(int this)
{
  DWORD Time; // eax

  *(uint32_t *)(this + 2228) = timeGetTime();
  LOBYTE(Time) = *(uint8_t *)(this + 2224);
  if ( (uint8_t)Time == 0 )
  {
    sub_667430(1u);
    LOBYTE(Time) = sub_666F00(*(uint32_t *)(this + 4));
    if ( (uint8_t)Time != 0 )
    {
      Time = timeGetTime();
      if ( Time - *(uint32_t *)(this + 2228) > 0x32 )
        *(uint32_t *)(this + 2228) = Time;
    }
  }
  return Time;
}



// ============================================================
// SECTION 0x657120 — ★ UDP 中继客户端（startup/connected to Relayserver/Disconnected —— socket/htons/inet_addr）
// ============================================================
// ------------------------------------------------------------
// 0x657120 sub_657120
// ------------------------------------------------------------
// 【解读】
//   UDP 中继客户端启动: "\nstartup[%s] :%d" + "\ninitialize(getIP(),getPort())"
//   （ninitialize/getIP/getPort —— RTII 网络接口族）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_657120(uint32_t *this)
{
  uint32_t *pThis_22E; // edi

  pThis_22E = this + 558;
  sub_40BE20("\nstartup[%s] :%d  \n\n", (uint8_t)this - 72);
  if ( sub_667970(pThis_22E, *(this + 622)) == 0 )
    return false;
  sub_40BE20("\ninitialize(getIP(),getPort())\n\n", (char)pThis_22E);
  return sub_667670(this) == 1;
}



// ------------------------------------------------------------
// 0x6571C0 sub_6571C0
// ------------------------------------------------------------
// 【解读】
//   "\nDisconnected": closesocket 断连通知。
// ------------------------------------------------------------
int /*thiscall*/ sub_6571C0(int this, int nArg2)
{
  int result; // eax
  char v4; // [esp+0h] [ebp-4h]

  sub_40BE20("\nDisconnected\n\n", v4);
  *(uint8_t *)(this + 2224) = 1;
  sub_6676C0(this);
  result = *(uint32_t *)(this + 2492);
  if ( result != -1 )
  {
    result = closesocket(*(uint32_t *)(this + 2492));
    *(uint32_t *)(this + 2492) = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x657200 sub_657200
// ------------------------------------------------------------
int /*thiscall*/ sub_657200(int this, int pArg2)
{
  *(uint8_t *)(this + 2225) = 0;
  return (***(int (/*thiscall*/ ****)(uint32_t, uint32_t, uint32_t))(this + 2512))(
           *(uint32_t *)(this + 2512),
           *(uint32_t *)(pArg2 + 4),
           *(uint16_t *)(*(uint32_t *)(pArg2 + 4) + 2));
}



// ------------------------------------------------------------
// 0x657230 sub_657230
// ------------------------------------------------------------
int /*thiscall*/ sub_657230(int this)
{
  int result; // eax

  *(uint8_t *)(this + 2224) = 1;
  sub_6676C0(this);
  result = *(uint32_t *)(this + 2492);
  if ( result != -1 )
  {
    result = closesocket(*(uint32_t *)(this + 2492));
    *(uint32_t *)(this + 2492) = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x657260 sub_657260
// ------------------------------------------------------------
char /*thiscall*/ sub_657260(int this, int nArg2)
{
  char result; // al

  result = 0;
  *(uint32_t *)(this + 2524) = nArg2;
  if ( nArg2 <= 0 )
  {
    *(uint8_t *)(this + 2556) = 0;
    *(uint8_t *)(this + 2541) = 0;
    *(uint8_t *)(this + 2542) = 0;
    *(uint8_t *)(this + 2540) = 0;
  }
  else
  {
    *(uint8_t *)(this + 2556) = 1;
    *(uint8_t *)(this + 2541) = 0;
    *(uint8_t *)(this + 2542) = 0;
    result = sub_698F90(this + 2528, *(uint32_t *)(this + 2524), 0);
    *(uint8_t *)(this + 2540) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6572C0 sub_6572C0
// ------------------------------------------------------------
// 【解读】
//   UDP socket 建立: socket() 失败 → "\nCould not create a UDP socket : %d"；成功 →
//    "\nconnected to Relayserver"（htons/inet_addr 连中继服）。与 0x41CC80 的 @@UDP STOP/START 呼应。
// ------------------------------------------------------------
char /*thiscall*/ sub_6572C0(int this)
{
  SOCKET v2; // eax
  char LastError; // al
  char v5; // [esp+0h] [ebp-4h]

  sub_667430(0);
  if ( (uint8_t)sub_666F00(*(uint32_t *)(this + 4)) == 0 )
    return 0;
  v2 = socket(2, 2, 17);
  *(uint32_t *)(this + 2492) = v2;
  if ( v2 == -1 )
  {
    LastError = GetLastError();
    sub_40BE20("\n\nCould not create a UDP socket : %d\n", LastError);
    return 0;
  }
  *(uint32_t *)(this + 2496) = 0;
  *(uint32_t *)(this + 2500) = 0;
  *(uint32_t *)(this + 2504) = 0;
  *(uint32_t *)(this + 2508) = 0;
  *(uint16_t *)(this + 2496) = 2;
  *(uint16_t *)(this + 2498) = htons(*(uint16_t *)(this + 2488));
  *(uint32_t *)(this + 2500) = inet_addr((const char *)(this + 2232));
  *(uint8_t *)(this + 2224) = 0;
  *(uint8_t *)(this + 2225) = 1;
  sub_40BE20("\nconnected to Relayserver\n\n", v5);
  return 1;
}


