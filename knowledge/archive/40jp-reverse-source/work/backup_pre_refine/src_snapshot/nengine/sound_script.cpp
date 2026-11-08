// ============================================================
// 【40JP逆向源代码工程】nengine/sound_script.cpp
// 模块: 声音脚本 .str/PAK/XML 解析
// 来源: work/dump_tail.txt  区块: 0x660000-0x670000
// 层级: L2 转写层 —— 反编译输出的规范化重排(类型名清洗/VA标记/分模块),
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 9
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x6680B0 sub_6680B0
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
// attributes: thunk
void */*cdecl*/ operator new(size_t Size)
{
  return ??2@YAPAXI@Z(Size);
}



// ------------------------------------------------------------
// 0x6684ED ??0_Init_locks@std@@QAE@XZ
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


