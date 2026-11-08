// ============================================================
// 【40JP逆向源代码工程】src/nengine/sound_script.cpp
// 模块: 0x66 区尾段（0x668000-0x670000）—— GetMessageBuffer 缓冲池 / flex 风格分块扫描 / CRT 支撑
// 来源: work/dump_tail.txt 系  区块: 0x660000-0x670000（本文件仅含尾段 9 函数）
// 层级: L2 转写层（Hex-Rays 逐字对应）+【L1 精修层】
//
// 【L1 精修内容】（注释级，函数体与 L2 逐字一致，零改动）:
//   ① 文件头重写（含下方 .str 标签全表）+ 1 个 SECTION 横幅
//   ② 9/9 函数全部带【解读】注释块（本文件函数少，逐函数全量精修）
//
// ★★★ 声音脚本 .str 格式 —— 标签全表（本区关键产出）
//   .str 为 XML 属性式脚本（解析器在本文件之外的 0x66 前段，位于
//   src/platform/missing_tail.cpp）:
//     · 0x663910 = 属性 getter（节点+13 属性表查名，命中返回 [+8] 串，否则 szPassword 空串）
//     · 0x663BB0 = 节点序列化器（"<tag attr=…>…</tag>" 输出 —— XML 格式直证）
//     · 数值经 VARIANT（vt=8 BSTR → sub_660F50 取 int / sub_660FF0 取 float）
//   标签 → 解析函数 → 存储槽（全表由 work/dump_missing_0/1/2.txt 直证）:
//     ┌──────────────────────┬────────────┬──────────────────────────────────┐
//     │ 标签                  │ 解析函数    │ 语义 / 存储                      │
//     ├──────────────────────┼────────────┼──────────────────────────────────┤
//     │ PRIORITY             │ 0x6611E0   │ 播放优先级 → int this[1]          │
//     │ VOLUME_ADJUST        │ 0x6611E0   │ 音量增幅 %×100 → int this[2]      │
//     │ VOLUME_ADJUST_RANGE  │ 0x6611E0   │ 音量随机幅度 %×100 → int this[3]  │
//     │ LOOP_TIMES           │ 0x6611E0   │ 循环次数 → int this[6]            │
//     │ LOOP_DELAY           │ 0x6611E0   │ 循环间隔 ×1000(ms) → this[4]      │
//     │ LOOP_DELAY_RANGE     │ 0x6611E0   │ 间隔随机量 ×1000(ms) → this[5]    │
//     │ FILE                 │ 0x661A20   │ 声音文件路径 → CString this[9]    │
//     │                      │ 0x662270   │ （第二处 FILE 型节点）            │
//     │ MINDIST              │ 0x661A20   │ 3D 最小距离 → float this+64       │
//     │ MAXDIST              │ 0x661A20   │ 3D 最大距离 → float this+68       │
//     │ CASCADENUM           │ 0x661A20   │ 级联声道数 → int this[18]         │
//     │ CASCADETAG           │ 0x661A20   │ 级联标签 → CString                │
//     │ NPCNO                │ 0x661CE0   │ NPC 编号过滤 → int                │
//     │ X / Y / Z            │ 0x661CE0   │ 触发坐标 → int ×3                 │
//     │ XRANGE/YRANGE/ZRANGE │ 0x661CE0   │ 触发范围半径 → int ×3             │
//     │ IN / OUT             │ 0x661F50   │ BGM 淡入/淡出时长                 │
//     │ LOOP                 │ 0x661F50   │ BGM 循环开关                      │
//     │ CROSSFADE_TO_OUT_TIME│ 0x661F50   │ 交叉淡出到下一曲的时长            │
//     │ PROB                 │ 0x662A40   │ 触发概率                          │
//     │ DELAY / DELAY_RANGE  │ 0x662CA0   │ 播放延迟 / 延迟随机量             │
//     └──────────────────────┴────────────┴──────────────────────────────────┘
//   解析链: 0x661A20(3D 声音源) 首行调 0x6611E0(基础属性) —— 层叠式属性继承。
//   背景定案（docs/04）: 0x66 = 声音脚本/PAK/XML 区，声音后端 FMOD 3.x；
//   演出侧消费点: 0x41CC80 onChangeModule（@@UDP STOP/START）与主帧循环声音延迟队列
//   （docs/13 §研究 P32 调用点直证 sub_65FAF0）。
//   ※ 本文件 9 函数为 0x66 区尾段的 CRT/网络/缓冲支撑（GetMessageBuffer 缓冲池、
//     WSAStartup、operator new、std::_Xran/_Xlen、_Init_locks），非 .str 解析本体。
//
// 函数数: 9（L1 覆盖 9：解读 9 / 分区 1）
// ============================================================

#include "../../common/arad_types.h"
// ============================================================
// SECTION 索引（按 VA 升序）
// ============================================================
//   0x6680B0 — 0x66 区尾段：GetMessageBuffer 2 的幂缓冲池 / flex 风格分块扫描 / WSAStartup / CRT 支撑（operator new、std::_Xran/_Xlen、_Init_locks）
// ============================================================

// ============================================================
// SECTION 0x6680B0 — 0x66 区尾段：GetMessageBuffer 2 的幂缓冲池 / flex 风格分块扫描 / WSAStartup / CRT 支撑（operator new、std::_Xran/_Xlen、_Init_locks）
// ============================================================
// ------------------------------------------------------------
// 0x6680B0 sub_6680B0
// ------------------------------------------------------------
// 【解读】
//   ★ GetMessageBuffer 2 的幂级缓冲池分配器（异常串自证 "GetMessageBuffer"）:
//     请求 n 字节 → 升档到 16/32/64/.../0x80000（2 的幂 ×15 档，二分判断链）；
//     每档 operator new(档位 + 0x14) —— 对象头 0x14(20B):
//       [+0] vftable（0x8000 档用 0x741FD8，其余 0x743ED8）
//       [+4] 数据指针 = this+10（即 0x14 偏移处缓冲）
//       [+8] 档位容量；[+12..] 游标/状态清零；小档（16/32）逐 DWORD 清零展开；
//     n > 0x80000 → 以字符串 "GetMessageBuffer" 抛异常（拒绝超额）。
//     消费者 = 0x668340 分块扫描循环。
// ------------------------------------------------------------
uint16_t */*cdecl*/ sub_6680B0(int pExceptionObject)
{
  uint16_t *result; // eax

  if ( (unsigned int)pExceptionObject > 0x80000 )
  {
    pExceptionObject = (int)"GetMessageBuffer";
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&PA.deinit);
  }
  if ( pExceptionObject > 16 )
  {
    if ( pExceptionObject > 32 )
    {
      if ( pExceptionObject > 64 )
      {
        if ( pExceptionObject > 128 )
        {
          if ( pExceptionObject > 256 )
          {
            if ( pExceptionObject > 512 )
            {
              if ( pExceptionObject > 1024 )
              {
                if ( pExceptionObject > 2048 )
                {
                  if ( pExceptionObject > 4096 )
                  {
                    if ( pExceptionObject > 0x2000 )
                    {
                      if ( pExceptionObject > 0x4000 )
                      {
                        if ( pExceptionObject > 0x8000 )
                        {
                          if ( pExceptionObject > 0x10000 )
                          {
                            if ( pExceptionObject > 0x20000 )
                            {
                              if ( pExceptionObject > 0x40000 )
                              {
                                result = operator new(0x80014u);
                                if ( result != nullptr )
                                {
                                  result[6] = 0;
                                  result[7] = 0;
                                  *((uint32_t *)result + 4) = 0;
                                  *(uint32_t *)result = &off_743ED8;
                                  *((uint32_t *)result + 2) = 0x80000;
                                  memset(result + 10, 0, 0x80000u);
                                  *((uint32_t *)result + 1) = result + 10;
                                  return result;
                                }
                              }
                              else
                              {
                                result = operator new(0x40014u);
                                if ( result != nullptr )
                                {
                                  result[6] = 0;
                                  result[7] = 0;
                                  *((uint32_t *)result + 4) = 0;
                                  *(uint32_t *)result = &off_743ED8;
                                  *((uint32_t *)result + 2) = 0x40000;
                                  memset(result + 10, 0, 0x40000u);
                                  *((uint32_t *)result + 1) = result + 10;
                                  return result;
                                }
                              }
                            }
                            else
                            {
                              result = operator new(0x20014u);
                              if ( result != nullptr )
                              {
                                result[6] = 0;
                                result[7] = 0;
                                *((uint32_t *)result + 4) = 0;
                                *(uint32_t *)result = &off_743ED8;
                                *((uint32_t *)result + 2) = 0x20000;
                                memset(result + 10, 0, 0x20000u);
                                *((uint32_t *)result + 1) = result + 10;
                                return result;
                              }
                            }
                          }
                          else
                          {
                            result = operator new(0x10014u);
                            if ( result != nullptr )
                            {
                              result[6] = 0;
                              result[7] = 0;
                              *((uint32_t *)result + 4) = 0;
                              *(uint32_t *)result = &off_743ED8;
                              *((uint32_t *)result + 2) = 0x10000;
                              memset(result + 10, 0, 0x10000u);
                              *((uint32_t *)result + 1) = result + 10;
                              return result;
                            }
                          }
                        }
                        else
                        {
                          result = operator new(0x8014u);
                          if ( result != nullptr )
                          {
                            result[6] = 0;
                            result[7] = 0;
                            *((uint32_t *)result + 4) = 0;
                            *(uint32_t *)result = &off_743ED8;
                            *((uint32_t *)result + 2) = 0x8000;
                            memset(result + 10, 0, 0x8000u);
                            *((uint32_t *)result + 1) = result + 10;
                            return result;
                          }
                        }
                      }
                      else
                      {
                        result = operator new(0x4014u);
                        if ( result != nullptr )
                        {
                          result[6] = 0;
                          result[7] = 0;
                          *((uint32_t *)result + 4) = 0;
                          *(uint32_t *)result = &off_743ED8;
                          *((uint32_t *)result + 2) = 0x4000;
                          memset(result + 10, 0, 0x4000u);
                          *((uint32_t *)result + 1) = result + 10;
                          return result;
                        }
                      }
                    }
                    else
                    {
                      result = operator new(0x2014u);
                      if ( result != nullptr )
                      {
                        result[6] = 0;
                        result[7] = 0;
                        *((uint32_t *)result + 4) = 0;
                        *(uint32_t *)result = &off_741FD8;
                        *((uint32_t *)result + 2) = 0x2000;
                        memset(result + 10, 0, 0x2000u);
                        *((uint32_t *)result + 1) = result + 10;
                        return result;
                      }
                    }
                  }
                  else
                  {
                    result = operator new(0x1014u);
                    if ( result != nullptr )
                    {
                      result[6] = 0;
                      result[7] = 0;
                      *((uint32_t *)result + 4) = 0;
                      *(uint32_t *)result = &off_743ED8;
                      *((uint32_t *)result + 2) = 4096;
                      memset(result + 10, 0, 0x1000u);
                      *((uint32_t *)result + 1) = result + 10;
                      return result;
                    }
                  }
                }
                else
                {
                  result = operator new(0x814u);
                  if ( result != nullptr )
                  {
                    result[6] = 0;
                    result[7] = 0;
                    *((uint32_t *)result + 4) = 0;
                    *(uint32_t *)result = &off_743ED8;
                    *((uint32_t *)result + 2) = 2048;
                    memset(result + 10, 0, 0x800u);
                    *((uint32_t *)result + 1) = result + 10;
                    return result;
                  }
                }
              }
              else
              {
                result = operator new(0x414u);
                if ( result != nullptr )
                {
                  result[6] = 0;
                  result[7] = 0;
                  *((uint32_t *)result + 4) = 0;
                  *(uint32_t *)result = &off_743ED8;
                  *((uint32_t *)result + 2) = 1024;
                  memset(result + 10, 0, 0x400u);
                  *((uint32_t *)result + 1) = result + 10;
                  return result;
                }
              }
            }
            else
            {
              result = operator new(0x214u);
              if ( result != nullptr )
              {
                result[6] = 0;
                result[7] = 0;
                *((uint32_t *)result + 4) = 0;
                *(uint32_t *)result = &off_743ED8;
                *((uint32_t *)result + 2) = 512;
                memset(result + 10, 0, 0x200u);
                *((uint32_t *)result + 1) = result + 10;
                return result;
              }
            }
          }
          else
          {
            result = operator new(0x114u);
            if ( result != nullptr )
            {
              result[6] = 0;
              result[7] = 0;
              *((uint32_t *)result + 4) = 0;
              *(uint32_t *)result = &off_743ED8;
              *((uint32_t *)result + 2) = 256;
              memset(result + 10, 0, 0x100u);
              *((uint32_t *)result + 1) = result + 10;
              return result;
            }
          }
        }
        else
        {
          result = operator new(0x94u);
          if ( result != nullptr )
          {
            result[6] = 0;
            result[7] = 0;
            *((uint32_t *)result + 4) = 0;
            *(uint32_t *)result = &off_743ED8;
            *((uint32_t *)result + 2) = 128;
            memset(result + 10, 0, 0x80u);
            *((uint32_t *)result + 1) = result + 10;
            return result;
          }
        }
      }
      else
      {
        result = operator new(0x54u);
        if ( result != nullptr )
        {
          result[6] = 0;
          result[7] = 0;
          *((uint32_t *)result + 4) = 0;
          *(uint32_t *)result = &off_743ED8;
          *((uint32_t *)result + 2) = 64;
          memset(result + 10, 0, 0x40u);
          *((uint32_t *)result + 1) = result + 10;
          return result;
        }
      }
    }
    else
    {
      result = operator new(0x34u);
      if ( result != nullptr )
      {
        result[6] = 0;
        result[7] = 0;
        *((uint32_t *)result + 4) = 0;
        *(uint32_t *)result = &off_743ED8;
        *((uint32_t *)result + 2) = 32;
        *((uint32_t *)result + 5) = 0;
        *((uint32_t *)result + 6) = 0;
        *((uint32_t *)result + 7) = 0;
        *((uint32_t *)result + 8) = 0;
        *((uint32_t *)result + 9) = 0;
        *((uint32_t *)result + 10) = 0;
        *((uint32_t *)result + 11) = 0;
        *((uint32_t *)result + 12) = 0;
        *((uint32_t *)result + 1) = result + 10;
        return result;
      }
    }
  }
  else
  {
    result = operator new(0x24u);
    if ( result != nullptr )
    {
      result[6] = 0;
      result[7] = 0;
      *((uint32_t *)result + 4) = 0;
      *(uint32_t *)result = &off_743ED8;
      *((uint32_t *)result + 2) = 16;
      *((uint32_t *)result + 5) = 0;
      *((uint32_t *)result + 6) = 0;
      *((uint32_t *)result + 7) = 0;
      *((uint32_t *)result + 8) = 0;
      *((uint32_t *)result + 1) = result + 10;
      return result;
    }
  }
  return nullptr;
}


// ------------------------------------------------------------
// 0x668320 sub_668320
// ------------------------------------------------------------
// 【解读】
//   缓冲对象析构（vftable → off_743ED0 + a2&1 → free）。与 0x6680B0 配对。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_668320(uint32_t *Block, char a2)
{
  *Block = &off_743ED0;
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x668340 sub_668340
// ------------------------------------------------------------
// 【解读】
//   分块扫描/refill 驱动循环（flex 风格，userpurge）:
//     vt+4 取余量 → 循环: vt+8 取当前指针 → 读 [+2] 处 2B 块长 →
//     余量 < 块长 → break；块长 0 → vt+16(余量) 提交返回；
//     否则 vt+12 保存回溯点 → sub_6680B0(块长) 申请缓冲 → qmemcpy 拷入 → vt+16 提交 →
//     缓冲对象 vt+0(a2) 交给处理器（yylex 式逐块消费）→ vt+4 再取余量继续。
//     【推断】.str/. PAK 词法驱动的缓冲 refill 骨架（flex yy_create_buffer 同构）。
// ------------------------------------------------------------
unsigned int /*userpurge*/ sub_668340@<eax>(signed int a1@<esi>, int a2, int a3)
{
  unsigned int result; // eax
  signed int i; // edi
  signed int v5; // ebp
  const void *v6; // esi
  void **v8; // [esp+10h] [ebp+8h]

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 4))(a2);
  for ( i = result; result >= 0xA; i = result )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 8))(a2);
    v5 = *(uint16_t *)(result + 2);
    if ( i < v5 )
      break;
    if ( *(uint16_t *)(result + 2) == 0 )
      return (*(int (/*thiscall*/ **)(int, signed int))(*(uint32_t *)a2 + 16))(a2, i);
    (*(void (/*thiscall*/ **)(int, signed int))(*(uint32_t *)a2 + 12))(a2, a1);
    v6 = (const void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 8))(a2);
    v8 = (void **)sub_6680B0(v5);
    qmemcpy(v8[1], v6, v5);
    a1 = v5;
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2);
    (*(void (/*thiscall*/ **)(void **, int))*v8)(v8, a2);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 4))(a2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x668410 sub_668410
// ------------------------------------------------------------
// 【解读】
//   WSAStartup(2.0) 惰性初始化（dword_9D21E0 保证仅一次；失败返回 0）。0x66 区网络/上报侧依赖。
// ------------------------------------------------------------
int sub_668410()
{
  if ( dword_9D21E0 == 0 )
  {
    if ( WSAStartup(2u, &WSAData) != 0 )
      return 0;
    dword_9D21E0 = 1;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x668444 ??2@YAPAXI@Z
// ------------------------------------------------------------
// 【解读】
//   operator new（CRT）: malloc 循环 + _callnewh(new_handler) + std::_Nomemory。
// ------------------------------------------------------------
void */*cdecl*/ operator new(size_t Size)
{
  void *result; // eax

  while ( 1 )
  {
    result = malloc(Size);
    if ( result != nullptr )
      break;
    if ( _callnewh(Size) == 0 )
      std::_Nomemory();
  }
  return result;
}



// ------------------------------------------------------------
// 0x668468 ?_Xran@_String_base@std@@QBEXXZ
// ------------------------------------------------------------
// 【解读】
//   std::_String_base::_Xran → 抛 std::out_of_range("invalid string position")。
// ------------------------------------------------------------
void /*thiscall*/ /*noreturn*/ std::_String_base::_Xran(std::_String_base *this)
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v2[36]; // [esp+28h] [ebp-28h] BYREF
  int v3; // [esp+4Ch] [ebp-4h]

  sub_401710("invalid string position");
  v3 = 0;
  sub_401740(v2);
  pExceptionObject = &std::out_of_range::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// ------------------------------------------------------------
// 0x6684A8 ?_Xlen@_String_base@std@@QBEXXZ
// ------------------------------------------------------------
// 【解读】
//   std::_String_base::_Xlen → 抛 std::length_error("string too long")。
// ------------------------------------------------------------
void /*thiscall*/ /*noreturn*/ std::_String_base::_Xlen(std::_String_base *this)
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v2[36]; // [esp+28h] [ebp-28h] BYREF
  int v3; // [esp+4Ch] [ebp-4h]

  sub_401710("string too long");
  v3 = 0;
  sub_401740(v2);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x6684E8 j_??2@YAPAXI@Z
// ------------------------------------------------------------
// 【解读】
//   operator new thunk（j_ 前缀跳转壳 → 0x668444）。
// ------------------------------------------------------------
// attributes: thunk
void */*cdecl*/ operator new(size_t Size)
{
  return ??2@YAPAXI@Z(Size);
}



// ------------------------------------------------------------
// 0x6684ED ??0_Init_locks@std@@QAE@XZ
// ------------------------------------------------------------
// 【解读】
//   std::_Init_locks 构造: InterlockedIncrement(&Addend) == 0（首次）→
//     对 stru_9D21E8..9D2248 锁数组逐个 unknown_libname_14 初始化 —— CRT 流锁自举。
// ------------------------------------------------------------
std::_Init_locks */*thiscall*/ std::_Init_locks::_Init_locks(std::_Init_locks *this)
{
  struct _RTL_CRITICAL_SECTION *v2; // esi

  if ( InterlockedIncrement(&Addend) == 0 )
  {
    v2 = &stru_9D21E8;
    do
      unknown_libname_14(v2++);
    while ( (int)v2 < (int)&unk_9D2248 );
  }
  return this;
}


