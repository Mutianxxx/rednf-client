// ============================================================
// 【40JP逆向源代码工程】parsers/item_parser.cpp
// 模块: 物品 .eqp 定义解析器族
// 来源: work/dump_parsers.txt  区块: 0x4F0000-0x4FC000
//       （深度校验用 work/dump_full_0/1/2.txt —— [tag] 词汇表按全量版提取）
// 层级: L2 转写层 → L1 精修层（会话 4 精修：标签族头注 + 分区；逻辑未改）
// 函数数: 166
//
// ★ 本文件解析器均为 [tag] 字符串驱动（与 monster_parser.cpp 同构）：
//   sub_442A10 打开 → sub_443430 逐行 → sub_40BF00/sub_423300 标签比对 →
//   sub_4423D0(整型)/sub_442480(浮点)/sub_443370(字符串)/sub_441710(属性名→id) 取值。
//
// ★ 研究 20 相关锚点：
//   - sub_4F6790 = ★ 属性解析器（研究 20 §12 "属性解析器 sub_509C90 的装备侧双胞胎"；
//     研究 20 §20-23 更正为"装备/状态百分比解析器（[stuck]/[hit recovery] 三层并存）"）。
//     含 [hit recovery]/[stuck resistance] 等 80 标签；浮点走 sub_442480→sub_432CF0，
//     整型描述符走 sub_4423D0→sub_41C150（研究 20 §12 两条属性路径的正身）。
//   - sub_4F5B90 = 可堆叠物品(stackable)定义解析器（[name]..[applying range] 39 标签）
//   - sub_4F7C60 = 装备(equipment)定义解析器（81 标签，含动作表与全套属性内联 sub_4F6790）
//   - sub_4F1A20 = 副本/世界地图(worldmap)定义解析器（53 标签，怪物生成与掉落池）
//
// 分区（按 VA 升序）：
//   §A 0x4F0000-0x4F1900  物品解析基础设施（读行/字符串/容器辅助 + 物品对象构造）
//   §B 0x4F1920-0x4F1A20  副本/世界地图定义（sub_4F1A20）
//   §C 0x4F2B90-0x4F2E80  物品对象虚函数与 RTTI 族（IRDItem__vmt*）
//   §D 0x4F32A0-0x4F43D0  物品资源/图标/动画加载族（Item/FieldImage.img 等）
//   §E 0x4F43D0-0x4F5B90  物品容器模板族（vector/list 辅助）
//   §F 0x4F5B90-0x4F7C60  ★ 物品定义解析器族（stackable sub_4F5B90 / 属性 sub_4F6790）
//   §G 0x4F7C60-0x4F8E20  ★ 装备定义解析器 sub_4F7C60（含动作表/套装）
//   §H 0x4F8E20-0x4FC000  全局表族（金限/战场/表情/等级表/时装/战场平衡）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// §A 0x4F0000-0x4F1900 物品解析基础设施
// ============================================================

// ------------------------------------------------------------
// 0x4F0600 sub_4F0600
// ------------------------------------------------------------
bool /*cdecl*/ sub_4F0600(const char *a1, int a2)
{
  strcpy(byte_9B0AB8, a1);
  if ( byte_9B0AB7[strlen(byte_9B0AB8)] != 92 && byte_9B0AB7[strlen(byte_9B0AB8)] != 47 )
    *(uint16_t *)&byte_9B0AB8[strlen(byte_9B0AB8)] = 92;
  return (uint8_t)sub_443C40((int)&unk_9B0BB8, (char)byte_9B0AB8, a2) != 0;
}



// ------------------------------------------------------------
// 0x4F0690 sub_4F0690
// ------------------------------------------------------------
void /*noreturn*/ sub_4F0690()
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
// 0x4F0700 sub_4F0700
// ------------------------------------------------------------
char /*thiscall*/ sub_4F0700(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x71C71C7 )
    sub_4F0690(this);
  v4 = (char *)operator new(36 * a2);
  *(this + 3) = &v4[36 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x4F0750 sub_4F0750
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F0750(uint32_t *this, uint32_t *a2)
{
  *this = *a2;
  sub_435020(a2 + 1);
  sub_435020(a2 + 5);
  return this;
}



// ------------------------------------------------------------
// 0x4F07B0 sub_4F07B0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F07B0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t *v4; // edi

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    *v4 = *v3;
    sub_4ED3F0((int)(v4 + 1), (int)(v3 + 1));
    sub_4ED3F0((int)(v4 + 5), (int)(v3 + 5));
    v3 += 9;
    v4 += 9;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x4F0800 sub_4F0800
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F0800(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  uint32_t *v4; // edi
  int v5; // eax

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = *(uint32_t *)(v3 - 36);
    v3 -= 36;
    v4 -= 9;
    *v4 = v5;
    sub_4ED3F0((int)(v4 + 1), v3 + 4);
    sub_4ED3F0((int)(v4 + 5), v3 + 20);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x4F0850 sub_4F0850
// ------------------------------------------------------------
void */*thiscall*/ sub_4F0850(void *this)
{
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 8) = 0;
  *(uint32_t *)this = 0;
  if ( *((uint32_t *)this + 2) != 0 )
    j__free(*((void **)this + 2));
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  if ( *((uint32_t *)this + 6) != 0 )
    j__free(*((void **)this + 6));
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 8) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4F08D0 sub_4F08D0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F08D0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_4F07B0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4F08F0 sub_4F08F0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F08F0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 9 )
  {
    *i = *a3;
    sub_4ED3F0((int)(i + 1), (int)(a3 + 1));
    sub_4ED3F0((int)(i + 5), (int)(a3 + 5));
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F0930 sub_4F0930
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F0930(int a1, int a2, uint32_t *a3)
{
  return sub_4F0800(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4F0950 sub_4F0950
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F0950(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
    {
      *v3 = *a1;
      sub_435020(a1 + 1);
      LOBYTE(v7) = 2;
      sub_435020(a1 + 5);
    }
    v3 += 9;
    LOBYTE(v7) = 0;
    a1 += 9;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x4F0A30 sub_4F0A30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F0A30(uint32_t **this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v5; // ecx
  uint32_t *v6; // eax
  uint32_t *v7; // ebx
  uint32_t *v8; // edi
  uint32_t *i; // esi
  uint32_t **v11; // [esp+4h] [ebp-4h]

  v5 = a3;
  v11 = this;
  if ( a3 != a4 )
  {
    v6 = sub_4F07B0(a4, *(this + 2), a3);
    v7 = *(this + 2);
    v8 = v6;
    for ( i = v6; i != v7; i += 9 )
      sub_472F00(i);
    v5 = a3;
    v11[2] = v8;
  }
  *a2 = v5;
  return a2;
}



// ------------------------------------------------------------
// 0x4F0A90 sub_4F0A90
// ------------------------------------------------------------
void /*cdecl*/ sub_4F0A90(uint32_t *a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t v4[6]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  v3 = a1;
  v4[5] = v4;
  v4[4] = a1;
  v5 = 0;
  while ( a2 != 0 )
  {
    v4[3] = v3;
    LOBYTE(v5) = 1;
    if ( v3 != nullptr )
    {
      *v3 = *a3;
      sub_435020(a3 + 1);
      LOBYTE(v5) = 2;
      sub_435020(a3 + 5);
    }
    v3 += 9;
    LOBYTE(v5) = 0;
    --a2;
  }
}



// ------------------------------------------------------------
// 0x4F0B70 sub_4F0B70
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4F0B70(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_4F0950(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4F0B90 sub_4F0B90
// ------------------------------------------------------------
int /*thiscall*/ sub_4F0B90(int this, int a2)
{
  int v4; // eax
  unsigned int v5; // ecx
  uint32_t *v7; // edi
  unsigned int v8; // eax
  uint32_t *v9; // eax
  int v10; // eax
  int v11; // ecx
  unsigned int v12; // eax
  unsigned int v13; // eax
  uint32_t *v14; // [esp+10h] [ebp+8h]

  if ( this == a2 )
    return this;
  v4 = *(uint32_t *)(a2 + 4);
  if ( v4 == 0 || (v5 = (*(uint32_t *)(a2 + 8) - v4) / 36) == 0 )
  {
    sub_474C60(this);
    return this;
  }
  v7 = *(uint32_t **)(this + 4);
  if ( v7 != nullptr )
    v8 = (*(uint32_t *)(this + 8) - (int)v7) / 36;
  else
    v8 = 0;
  if ( v5 > v8 )
  {
    if ( v7 != nullptr )
      v12 = (*(uint32_t *)(this + 12) - (int)v7) / 36;
    else
      v12 = 0;
    if ( v5 <= v12 )
    {
      v14 = (uint32_t *)(*(uint32_t *)(a2 + 4) + 36 * sub_504390(this));
      sub_4F08D0(*(uint32_t **)(a2 + 4), v14, v7);
      *(uint32_t *)(this + 8) = sub_4F0950(v14, *(uint32_t **)(a2 + 8), *(uint32_t **)(this + 8));
      return this;
    }
    if ( v7 != nullptr )
    {
      sub_475080(v7, *(uint32_t *)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v13 = sub_504390(a2);
    if ( sub_4F0700((uint32_t *)this, v13) != 0 )
      *(uint32_t *)(this + 8) = sub_4F0B70(*(uint32_t **)(a2 + 4), *(uint32_t **)(a2 + 8), *(uint32_t **)(this + 4));
    return this;
  }
  v9 = sub_4F07B0(*(uint32_t **)(a2 + 4), *(uint32_t **)(a2 + 8), v7);
  sub_475080(v9, *(uint32_t *)(this + 8));
  v10 = *(uint32_t *)(a2 + 4);
  if ( v10 != 0 )
    v11 = *(uint32_t *)(this + 4) + 36 * ((*(uint32_t *)(a2 + 8) - v10) / 36);
  else
    v11 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 8) = v11;
  return this;
}



// ------------------------------------------------------------
// 0x4F0D10 sub_4F0D10
// ------------------------------------------------------------
int /*thiscall*/ sub_4F0D10(void *this)
{
  int v2; // edi
  int result; // eax
  int i; // ebx

  *(uint32_t *)this = 1;
  *((uint32_t *)this + 1) = 1;
  v2 = *((uint32_t *)this + 3);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *((uint32_t *)this + 4); v2 != i; v2 += 36 )
      sub_472F00(v2);
    j__free(*((void **)this + 3));
    result = 0;
  }
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  if ( *((uint32_t *)this + 7) != 0 )
  {
    j__free(*((void **)this + 7));
    result = 0;
  }
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  if ( *((uint32_t *)this + 11) != 0 )
  {
    j__free(*((void **)this + 11));
    result = 0;
  }
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4F0D90 sub_4F0D90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F0D90(uint32_t *this)
{
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  sub_4F0D10(this);
  return this;
}



// ------------------------------------------------------------
// 0x4F0DE0 sub_4F0DE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F0DE0(uint32_t *this, int a2)
{
  unsigned int v2; // eax
  uint32_t *v5; // [esp-14h] [ebp-34h]
  uint32_t *v6; // [esp-10h] [ebp-30h]
  uint32_t *v7; // [esp-Ch] [ebp-2Ch]
  uint32_t v8[8]; // [esp+0h] [ebp-20h] BYREF

  v2 = *(uint32_t *)(a2 + 4);
  v8[4] = v8;
  v8[3] = this;
  if ( v2 != 0 )
    v2 = (int)(*(uint32_t *)(a2 + 8) - v2) / 36;
  if ( sub_4F0700(this, v2) != 0 )
  {
    v7 = (uint32_t *)*(this + 1);
    v6 = *(uint32_t **)(a2 + 8);
    v5 = *(uint32_t **)(a2 + 4);
    v8[7] = 0;
    *(this + 2) = sub_4F0950(v5, v6, v7);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4F0E80 sub_4F0E80
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4F0E80(uint32_t *a1, int a2, uint32_t *a3)
{
  sub_4F0A90(a1, a2, a3);
  return &a1[9 * a2];
}



// ------------------------------------------------------------
// 0x4F0EB0 sub_4F0EB0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F0EB0(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  uint32_t *v4; // edi
  int v5; // eax

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = *(uint32_t *)(v3 - 56);
    v3 -= 56;
    v4 -= 14;
    *v4 = v5;
    v4[1] = *(uint32_t *)(v3 + 4);
    sub_4F0B90((int)(v4 + 2), v3 + 8);
    sub_4800C0(v3 + 24);
    sub_4800C0(v3 + 40);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x4F0F10 sub_4F0F10
// ------------------------------------------------------------
void /*thiscall*/ sub_4F0F10(int *this, int a2, unsigned int a3, int a4)
{
  int v5; // ebx
  unsigned int v6; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  char *v12; // ebx
  int v13; // eax
  unsigned int v14; // edi
  int v15; // eax
  int v16; // ecx
  int v18; // edi
  int v19; // [esp-18h] [ebp-60h]
  int v20; // [esp-Ch] [ebp-54h]
  unsigned int v21; // [esp-8h] [ebp-50h]
  int v22; // [esp+0h] [ebp-48h] BYREF
  uint8_t v23[8]; // [esp+Ch] [ebp-3Ch] BYREF
  void *v24; // [esp+14h] [ebp-34h]
  void *v25; // [esp+24h] [ebp-24h]
  int v26; // [esp+28h] [ebp-20h]
  int v27; // [esp+2Ch] [ebp-1Ch]
  void *Block; // [esp+30h] [ebp-18h]
  int *v29; // [esp+34h] [ebp-14h]
  int *v30; // [esp+38h] [ebp-10h]
  int v31; // [esp+44h] [ebp-4h]
  int v32; // [esp+50h] [ebp+8h]
  int v33; // [esp+54h] [ebp+Ch]
  int v34; // [esp+58h] [ebp+10h]
  int v35; // [esp+58h] [ebp+10h]

  v30 = &v22;
  v29 = this;
  sub_4F0750(a4);
  v5 = *(this + 1);
  v6 = 0;
  v31 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 36;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - v5) / 36;
    else
      v8 = 0;
    if ( 119304647 - v8 < a3 )
      sub_4F0690(this);
    if ( v5 != 0 )
      v9 = (*(this + 2) - v5) / 36;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = *(this + 2);
      v35 = v16;
      if ( (v16 - a2) / 36 >= a3 )
      {
        v32 = v16 - 36 * a3;
        *(this + 2) = sub_4F0950(v32, v16, v16);
        sub_4F0930(a2, v32, v35);
        sub_4F08F0(a2, a2 + 36 * a3, v23);
      }
      else
      {
        sub_4F0950(a2, v16, a2 + 36 * a3);
        v21 = a3 - (*(this + 2) - a2) / 36;
        v20 = *(this + 2);
        LOBYTE(v31) = 3;
        sub_4F0E80(v20, v21, v23);
        v18 = 36 * a3 + *(this + 2);
        *(this + 2) = v18;
        v31 = 0;
        sub_4F08F0(a2, v18 - 36 * a3, v23);
      }
    }
    else
    {
      if ( 119304647 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(this + 2) - v5) / 36;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_504390(this);
      v34 = 36 * v10;
      v12 = (char *)operator new(36 * v10);
      v19 = *(this + 1);
      Block = v12;
      LOBYTE(v31) = 1;
      v33 = sub_4F0950(v19, a2, v12);
      sub_4F0A90(v33, a3, v23);
      sub_4F0950(a2, *(this + 2), v33 + 36 * a3);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 36;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_475080(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v34];
      *(this + 2) = (int)&v12[36 * v14];
      *(this + 1) = (int)v12;
    }
  }
  if ( v25 != nullptr )
    j__free(v25);
  v25 = nullptr;
  v26 = 0;
  v27 = 0;
  if ( v24 != nullptr )
    j__free(v24);
}


// ------------------------------------------------------------
// 0x4F1220 sub_4F1220
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F1220(uint32_t *this, uint32_t *a2)
{
  *this = *a2;
  *(this + 1) = a2[1];
  sub_4F0DE0(this + 2, (int)(a2 + 2));
  sub_480360(a2 + 6);
  sub_480360(a2 + 10);
  return this;
}



// ------------------------------------------------------------
// 0x4F1290 sub_4F1290
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F1290(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 14 )
  {
    *i = *a3;
    i[1] = a3[1];
    sub_4F0B90((int)(i + 2), (int)(a3 + 2));
    sub_4800C0(a3 + 6);
    sub_4800C0(a3 + 10);
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F12E0 sub_4F12E0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F12E0(int a1, int a2, uint32_t *a3)
{
  return sub_4F0EB0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4F1300 sub_4F1300
// ------------------------------------------------------------
void /*thiscall*/ sub_4F1300(
        int this,
        unsigned int a2,
        int a3,
        int a4,
        void *a5,
        int a6,
        int a7,
        int a8,
        void *Block,
        int a10,
        int a11)
{
  int v11; // esi
  unsigned int v12; // eax
  int v13; // eax

  v11 = *(uint32_t *)(this + 4);
  if ( v11 != 0 )
    v12 = (*(uint32_t *)(this + 8) - v11) / 36;
  else
    v12 = 0;
  if ( v12 >= a2 )
  {
    if ( v11 != 0 && a2 < (*(uint32_t *)(this + 8) - v11) / 36 )
      sub_4F0A30((uint32_t **)this, &a2, (uint32_t *)(v11 + 36 * a2), *(uint32_t **)(this + 8));
  }
  else
  {
    if ( v11 != 0 )
      v13 = (*(uint32_t *)(this + 8) - v11) / 36;
    else
      v13 = 0;
    sub_4F0F10((int *)this, *(char **)(this + 8), a2 - v13, &a3);
  }
  if ( Block != nullptr )
    j__free(Block);
  if ( a5 != nullptr )
    j__free(a5);
}



// ------------------------------------------------------------
// 0x4F13E0 sub_4F13E0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F13E0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
      sub_4F1220(v3, a1);
    v3 += 14;
    LOBYTE(v7) = 0;
    a1 += 14;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x4F14B0 sub_4F14B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4F14B0(void *this, unsigned int a2)
{
  uint32_t v3[11]; // [esp-24h] [ebp-2Ch] BYREF

  v3[10] = v3;
  sub_4F0850(v3);
  sub_4F1300((int)this, a2, v3[0], v3[1], (void *)v3[2], v3[3], v3[4], v3[5], (void *)v3[6], v3[7], v3[8]);
}



// ------------------------------------------------------------
// 0x4F14E0 sub_4F14E0
// ------------------------------------------------------------
void /*cdecl*/ sub_4F14E0(uint32_t *a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t v5[5]; // [esp+0h] [ebp-20h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v5[4] = v5;
  v5[3] = a1;
  v6 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v6) = 1;
    if ( v3 != nullptr )
      sub_4F1220(v3, a3);
    --a2;
    v3 += 14;
    LOBYTE(v6) = 0;
  }
}



// ------------------------------------------------------------
// 0x4F15B0 sub_4F15B0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4F15B0(uint32_t *a1, int a2, uint32_t *a3)
{
  sub_4F14E0(a1, a2, a3);
  return &a1[14 * a2];
}



// ------------------------------------------------------------
// 0x4F15E0 sub_4F15E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4F15E0(int *this, int a2, unsigned int a3, int a4)
{
  int v5; // ebx
  unsigned int v6; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  char *v12; // ebx
  int v13; // eax
  unsigned int v14; // edi
  int v15; // eax
  char *v16; // ecx
  int v18; // edx
  int v20; // [esp-18h] [ebp-74h]
  int v21; // [esp-Ch] [ebp-68h]
  unsigned int v22; // [esp-8h] [ebp-64h]
  int v23; // [esp+0h] [ebp-5Ch] BYREF
  uint8_t v24[8]; // [esp+Ch] [ebp-50h] BYREF
  char v25[20]; // [esp+14h] [ebp-48h] BYREF
  void *v26; // [esp+28h] [ebp-34h]
  int v27; // [esp+2Ch] [ebp-30h]
  int v28; // [esp+30h] [ebp-2Ch]
  void *v29; // [esp+38h] [ebp-24h]
  int v30; // [esp+3Ch] [ebp-20h]
  int v31; // [esp+40h] [ebp-1Ch]
  void *Block; // [esp+44h] [ebp-18h]
  int *v33; // [esp+48h] [ebp-14h]
  int *v34; // [esp+4Ch] [ebp-10h]
  int v35; // [esp+58h] [ebp-4h]
  char *v36; // [esp+64h] [ebp+8h]
  int v37; // [esp+68h] [ebp+Ch]
  int v38; // [esp+6Ch] [ebp+10h]

  v34 = &v23;
  v33 = this;
  sub_4F1220(a4);
  v5 = *(this + 1);
  v6 = 0;
  v35 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 56;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - *(this + 1)) / 56;
    else
      v8 = 0;
    if ( 76695844 - v8 < a3 )
      sub_4735F0(this);
    if ( *(this + 1) != 0 )
      v9 = (*(this + 2) - *(this + 1)) / 56;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = (char *)*(this + 2);
      Block = v16;
      if ( (int)&v16[-a2] / 56 >= a3 )
      {
        v36 = &v16[-56 * a3];
        *(this + 2) = sub_4F13E0(v36, v16, v16);
        sub_4F12E0(a2, v36, Block);
        sub_4F1290(a2, a2 + 56 * a3, v24);
      }
      else
      {
        sub_4F13E0(a2, v16, a2 + 56 * a3);
        v22 = a3 - (*(this + 2) - a2) / 56;
        v21 = *(this + 2);
        LOBYTE(v35) = 3;
        sub_4F15B0(v21, v22, v24);
        v18 = 56 * a3 + *(this + 2);
        *(this + 2) = v18;
        v35 = 0;
        sub_4F1290(a2, v18 - 56 * a3, v24);
      }
    }
    else
    {
      if ( 76695844 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        v11 = (*(this + 2) - *(this + 1)) / 56;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_488DD0(this);
      v38 = 56 * v10;
      v12 = (char *)operator new(56 * v10);
      v20 = *(this + 1);
      Block = v12;
      LOBYTE(v35) = 1;
      v37 = sub_4F13E0(v20, a2, v12);
      sub_4F14E0(v37, a3, v24);
      sub_4F13E0(a2, *(this + 2), 56 * a3 + v37);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 56;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_475730(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v38];
      *(this + 2) = (int)&v12[56 * v14];
      *(this + 1) = (int)v12;
    }
  }
  if ( v29 != nullptr )
    j__free(v29);
  v29 = nullptr;
  v30 = 0;
  v31 = 0;
  if ( v26 != nullptr )
    j__free(v26);
  v26 = nullptr;
  v27 = 0;
  v28 = 0;
  return sub_474C60(v25);
}


// ------------------------------------------------------------
// 0x4F1920 sub_4F1920
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F1920(int *this, uint32_t *a2, char *a3, uint32_t *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 56 != 0 )
    v6 = (int)&a3[-v5] / 56;
  else
    v6 = 0;
  sub_4F15E0(this, a3, 1u, a4);
  *a2 = *(this + 1) + 56 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4F1990 sub_4F1990
// ------------------------------------------------------------
void /*thiscall*/ sub_4F1990(int this, uint32_t *a2)
{
  int v3; // ebx
  unsigned int v4; // esi
  uint32_t *v5; // esi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 56;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) / 56 )
  {
    v5 = *(uint32_t **)(this + 8);
    sub_4F14E0(v5, 1, a2);
    *(uint32_t *)(this + 8) = v5 + 14;
  }
  else
  {
    sub_4F1920((int *)this, &a2, *(char **)(this + 8), a2);
  }
}



// ============================================================
// §B 0x4F1920-0x4F1A20 副本/世界地图定义
// ============================================================

// ------------------------------------------------------------
// 0x4F1A20 sub_4F1A20 —— 世界地图/副本(worldmap dungeon)定义解析器（53 标签，本文件最大解析器）
//   标签族：文本与资源 [name]/[explain]/[entering title]/[cutscene image]/[minimap image]/
//   [worldmap info]；准入 [minimum required level]/[required item]/[coin limit]/[join cost gold]；
//   地图结构 [basis level]/[experience increasing point]/[champion]/[item]/[pathgate object]/
//   [maze info]/[size]/[greed]/[map specification]/[boss map specification]/[start map]/
//   [boss map]/[warroom map index]/[ancient dungeon]；
//   怪物生成 [monster type spawn prob]/[monster type spawn cost]/[monster type spawn interval rate]/
//   （三组各 4 项 float/int 数组，基址 a1+612/+628/+652）
//   [monster spawn base interval]/[monster spawn random interval]/[max monster]/[player kc]/
//   [spawn common monster index]/[spawn common champion index]/[spawn super champion index]/
//   [spawn boss index]（四个索引池 a1+420/436/452/468）/[spawn step max]/[spawn step resource pool]；
//   疲劳 [fatigue]/[fatigue result]；掉落 [kill count const]/[gold drop prob]/
//   [common monster item drop prob]/[common champion item drop prob]/[super champion item drop prob]/
//   [boss item drop prob]/[common monster item drop list]/[common champion item drop list]/
//   [super champion item drop list]/[boss item drop list]；
//   经验常数 [common monster exp const]×5/[common champion exp const]×5/
//   [super champion exp const]×5/[boss exp const]×5（均 ×5 缩放后写入）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4F1A20(char *a1, int ArgList)
{
  const char *v2; // esi
  char *v3; // edi
  int *v4; // esi
  int i; // ebx
  int j; // edi
  int v7; // eax
  int v8; // eax
  int *v9; // esi
  int k; // edi
  int m; // eax
  int *v12; // esi
  int n; // edi
  int *v14; // esi
  int ii; // edi
  int *v16; // esi
  int jj; // edi
  int *v18; // esi
  int kk; // edi
  uint8_t *v20; // eax
  uint8_t *v21; // eax
  uint8_t *v22; // eax
  int i6; // edx
  uint8_t *v24; // ecx
  uint8_t *v25; // eax
  uint32_t *v26; // esi
  int v27; // eax
  int v28; // eax
  int v29; // esi
  void **v30; // esi
  int v31; // esi
  void **v32; // esi
  int nn; // eax
  int i1; // eax
  int *v35; // esi
  int i2; // edi
  int *v37; // esi
  int i3; // edi
  float *v39; // esi
  int i4; // edi
  const char *v41; // eax
  int v42; // eax
  std::_String_base *v43; // ecx
  int v44; // edx
  int v45; // ecx
  void *v46; // eax
  char *v47; // edi
  char *v48; // esi
  void **v50[4]; // [esp-1Ch] [ebp-F4h] BYREF
  uint8_t *v51; // [esp-Ch] [ebp-E4h]
  uint8_t *v52; // [esp-8h] [ebp-E0h]
  unsigned int v53; // [esp-4h] [ebp-DCh]
  uint32_t v54[2]; // [esp+Ch] [ebp-CCh] BYREF
  uint32_t v55[2]; // [esp+14h] [ebp-C4h] BYREF
  uint32_t v56[2]; // [esp+1Ch] [ebp-BCh] BYREF
  int v57; // [esp+24h] [ebp-B4h] BYREF
  int v58; // [esp+28h] [ebp-B0h]
  void *v59; // [esp+30h] [ebp-A8h]
  char *v60; // [esp+34h] [ebp-A4h]
  int v61; // [esp+38h] [ebp-A0h]
  void *v62; // [esp+3Ch] [ebp-9Ch] BYREF
  void *v63; // [esp+40h] [ebp-98h]
  int v64; // [esp+44h] [ebp-94h]
  int v65; // [esp+48h] [ebp-90h]
  void *v66; // [esp+4Ch] [ebp-8Ch] BYREF
  void *Block; // [esp+50h] [ebp-88h]
  int v68; // [esp+54h] [ebp-84h]
  int v69; // [esp+58h] [ebp-80h]
  void ***v70; // [esp+5Ch] [ebp-7Ch]
  int v71; // [esp+60h] [ebp-78h]
  int i5; // [esp+64h] [ebp-74h] BYREF
  char v73; // [esp+6Bh] [ebp-6Dh]
  int mm; // [esp+6Ch] [ebp-6Ch] BYREF
  char v75; // [esp+73h] [ebp-65h] BYREF
  char v76[4]; // [esp+74h] [ebp-64h] BYREF
  void *v77; // [esp+78h] [ebp-60h]
  int v78; // [esp+88h] [ebp-50h]
  unsigned int v79; // [esp+8Ch] [ebp-4Ch]
  char v80[4]; // [esp+90h] [ebp-48h] BYREF
  uint32_t v81[5]; // [esp+94h] [ebp-44h] BYREF
  unsigned int v82; // [esp+A8h] [ebp-30h]
  int v83; // [esp+ACh] [ebp-2Ch] BYREF
  void *v84; // [esp+B0h] [ebp-28h] BYREF
  int v85; // [esp+C0h] [ebp-18h]
  unsigned int v86; // [esp+C4h] [ebp-14h]
  int v87; // [esp+C8h] [ebp-10h]
  int v88; // [esp+D4h] [ebp-4h]

  v2 = (const char *)ArgList;
  v87 = dword_796E50;
  if ( (uint8_t)sub_442A10((char)&unk_9B0AB8, ArgList) == 0 )
    return 0;
  v3 = a1;
  sub_476000(a1);
  sub_443300((int)(a1 + 316), "%s%s", (char)&unk_9B0AB8);
  v86 = 15;
  v85 = 0;
  LOBYTE(v84) = 0;
  v88 = 1;
  v79 = 15;
  v78 = 0;
  LOBYTE(v77) = 0;
  v75 = 0;
  sub_4F0D90(&v57);
  LOBYTE(v88) = 2;
  v73 = 0;
  if ( (uint8_t)sub_443430(&v83) == 0 )
  {
LABEL_190:
    sub_4F1990(&v57);
    *(uint32_t *)v3 = sub_4A2F80(v2);
    v42 = *(uint32_t *)&v3[4 * dword_78FF38 + 400];
    v53 = -1;
    v43 = (std::_String_base *)(v3 + 4);
    v52 = nullptr;
    if ( v42 != 0 )
    {
      sub_4014D0(v43, v42, v52, v53);
      v44 = *(uint32_t *)&v3[4 * dword_78FF38 + 400];
      v53 = -1;
      v52 = nullptr;
      v51 = (uint8_t *)(v44 + 28);
    }
    else
    {
      sub_4014D0(v43, *((uint32_t *)v3 + 100), v52, v53);
      v45 = *((uint32_t *)v3 + 100);
      v53 = -1;
      v52 = nullptr;
      v51 = (uint8_t *)(v45 + 28);
    }
    sub_4014D0((std::_String_base *)(v3 + 32), v51, v52, v53);
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v68 = 0;
    v69 = 0;
    if ( v63 != nullptr )
      j__free(v63);
    v46 = v59;
    v63 = nullptr;
    v64 = 0;
    v65 = 0;
    if ( v59 != nullptr )
    {
      v47 = v60;
      if ( v59 != v60 )
      {
        v48 = (char *)v59 + 24;
        do
        {
          if ( *(uint32_t *)v48 != 0 )
            j__free(*(void **)v48);
          *(uint32_t *)v48 = 0;
          *((uint32_t *)v48 + 1) = 0;
          *((uint32_t *)v48 + 2) = 0;
          if ( *((uint32_t *)v48 - 4) != 0 )
            j__free(*((void **)v48 - 4));
          *((uint32_t *)v48 - 4) = 0;
          *((uint32_t *)v48 - 3) = 0;
          *((uint32_t *)v48 - 2) = 0;
          v48 += 36;
        }
        while ( v48 - 24 != v47 );
        v46 = v59;
      }
      j__free(v46);
    }
    v59 = nullptr;
    v60 = nullptr;
    v61 = 0;
    if ( v79 >= 0x10 )
      j__free(v77);
    v79 = 15;
    v78 = 0;
    LOBYTE(v77) = 0;
    if ( v86 >= 0x10 )
      j__free(v84);
    return 1;
  }
  while ( 1 )
  {
    sub_442B20(&v83);
    if ( sub_40BF00((std::_String_base *)&v83, 0, v85, "[name]", 6u) == 0 )
    {
      v53 = *((uint32_t *)v3 + 100);
      sub_443370();
      goto LABEL_189;
    }
    if ( sub_40BF00((std::_String_base *)&v83, 0, v85, "[explain]", 9u) == 0 )
    {
      v53 = *((uint32_t *)v3 + 100) + 28;
      sub_443370();
      goto LABEL_189;
    }
    if ( sub_40BF00((std::_String_base *)&v83, 0, v85, "[entering title]", 0x10u) == 0 )
    {
      v53 = (unsigned int)(v3 + 60);
      sub_443370();
      goto LABEL_189;
    }
    if ( sub_40BF00((std::_String_base *)&v83, 0, v85, "[cutscene image]", 0x10u) == 0 )
    {
      v53 = (unsigned int)(v3 + 88);
      sub_443370();
      *((uint32_t *)v3 + 29) = sub_4423D0(nullptr);
      goto LABEL_189;
    }
    if ( (uint8_t)sub_423300(&v83, "[minimap image]") != 0 )
    {
      v53 = (unsigned int)(v3 + 120);
      sub_443370();
      goto LABEL_189;
    }
    if ( (uint8_t)sub_423300(&v83, "[worldmap info]") != 0 )
    {
      v4 = (int *)(v3 + 148);
      for ( i = 2; i != 0; --i )
      {
        for ( j = 2; j != 0; --j )
          *v4++ = sub_4423D0(nullptr);
      }
      v53 = (unsigned int)(a1 + 164);
      sub_443370();
      v3 = a1;
      goto LABEL_189;
    }
    if ( (uint8_t)sub_423300(&v83, "[minimum required level]") != 0 )
    {
      *((uint32_t *)v3 + 48) = sub_4423D0(nullptr);
      goto LABEL_189;
    }
    if ( (uint8_t)sub_423300(&v83, "[required item]") != 0 )
    {
      v7 = sub_4423D0(nullptr);
      v52 = nullptr;
      *((uint32_t *)v3 + 49) = v7;
      v8 = sub_4423D0(v52);
      v51 = nullptr;
      *((uint32_t *)v3 + 50) = v8;
      v3[204] = sub_4423D0(v51) != 0;
      goto LABEL_189;
    }
    if ( (uint8_t)sub_423300(&v83, "[coin limit]") != 0 )
    {
      *((uint32_t *)v3 + 52) = sub_4423D0(nullptr);
      goto LABEL_189;
    }
    if ( (uint8_t)sub_423300(&v83, "[basis level]") != 0 )
    {
      *((uint32_t *)v3 + 53) = sub_4423D0(nullptr);
      goto LABEL_189;
    }
    if ( (uint8_t)sub_423300(&v83, "[experience increasing point]") != 0 )
    {
      *((float *)v3 + 54) = sub_442480(nullptr);
      goto LABEL_189;
    }
    if ( (uint8_t)sub_423300(&v83, "[champion]") == 0 )
      break;
    v9 = (int *)(a1 + 220);
    for ( k = 4; k != 0; --k )
      *v9++ = sub_4423D0(nullptr);
    v3 = a1;
LABEL_189:
    v2 = (const char *)ArgList;
    if ( (uint8_t)sub_443430(&v83) == 0 )
      goto LABEL_190;
  }
  if ( (uint8_t)sub_423300(&v83, "[item]") != 0 )
  {
    sub_5E5260((void **)v3 + 59);
    for ( m = sub_4423D0(&v75); v75 != 0; m = sub_4423D0(&v75) )
    {
      v56[0] = m;
      v56[1] = sub_4423D0(nullptr);
      sub_474950(v56);
    }
    goto LABEL_189;
  }
  if ( (uint8_t)sub_423300(&v83, "[pathgate object]") != 0 )
  {
    v12 = (int *)(a1 + 252);
    for ( n = 3; n != 0; --n )
      *v12++ = sub_4423D0(nullptr);
    v14 = (int *)(a1 + 264);
    for ( ii = 3; ii != 0; --ii )
      *v14++ = sub_4423D0(nullptr);
    v16 = (int *)(a1 + 276);
    for ( jj = 2; jj != 0; --jj )
      *v16++ = sub_4423D0(nullptr);
    v18 = (int *)(a1 + 288);
    for ( kk = 2; kk != 0; --kk )
      *v18++ = sub_4423D0(nullptr);
    v3 = a1;
    goto LABEL_189;
  }
  if ( (uint8_t)sub_423300(&v83, "[maze info]") != 0 )
  {
    if ( v73 != 0 )
    {
      sub_4F1990(&v57);
      sub_4F0D10(&v57);
    }
    else
    {
      v73 = 1;
    }
    goto LABEL_189;
  }
  if ( (uint8_t)sub_423300(&v83, "[size]") != 0 )
  {
    v57 = sub_4423D0(nullptr);
    v58 = sub_4423D0(nullptr);
    sub_4F14B0(v57 * v58);
    goto LABEL_189;
  }
  if ( (uint8_t)sub_423300(&v83, "[greed]") == 0 )
  {
    if ( (uint8_t)sub_423300(&v83, "[map specification]") != 0 )
    {
      v29 = sub_4423D0(nullptr);
      v30 = (void **)((char *)v59 + 36 * v29 + 36 * v57 * sub_4423D0(nullptr) + 4);
      sub_5E5260(v30);
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )
        sub_431230((int)v30, &mm);
    }
    else if ( (uint8_t)sub_423300(&v83, "[boss map specification]") != 0 )
    {
      v31 = sub_4423D0(nullptr);
      v32 = (void **)((char *)v59 + 36 * v31 + 36 * v57 * sub_4423D0(nullptr) + 20);
      sub_5E5260(v32);
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )
        sub_431230((int)v32, &mm);
    }
    else if ( (uint8_t)sub_423300(&v83, "[start map]") != 0 )
    {
      sub_5E5260(&v62);
      for ( nn = sub_4423D0(&v75); v75 != 0; nn = sub_4423D0(&v75) )
      {
        v55[0] = nn;
        v55[1] = sub_4423D0(nullptr);
        sub_474950(v55);
      }
    }
    else if ( (uint8_t)sub_423300(&v83, "[boss map]") != 0 )
    {
      sub_5E5260(&v66);
      for ( i1 = sub_4423D0(&v75); v75 != 0; i1 = sub_4423D0(&v75) )
      {
        v54[0] = i1;
        v54[1] = sub_4423D0(nullptr);
        sub_474950(v54);
      }
    }
    else if ( (uint8_t)sub_423300(&v83, "[warroom map index]") != 0 )
    {
      *((uint32_t *)v3 + 104) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[monster type spawn prob]") != 0 )
    {
      v35 = (int *)(a1 + 612);
      for ( i2 = 4; i2 != 0; --i2 )
        *v35++ = sub_4423D0(nullptr);
      v3 = a1;
    }
    else if ( (uint8_t)sub_423300(&v83, "[monster type spawn cost]") != 0 )
    {
      v37 = (int *)(a1 + 628);
      for ( i3 = 4; i3 != 0; --i3 )
        *v37++ = sub_4423D0(nullptr);
      v3 = a1;
    }
    else if ( (uint8_t)sub_423300(&v83, "[monster type spawn interval rate]") != 0 )
    {
      v39 = (float *)(a1 + 652);
      for ( i4 = 4; i4 != 0; --i4 )
        *v39++ = sub_442480(nullptr);
      v3 = a1;
    }
    else if ( (uint8_t)sub_423300(&v83, "[monster spawn base interval]") != 0 )
    {
      *((uint32_t *)v3 + 167) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[monster spawn random interval]") != 0 )
    {
      *((uint32_t *)v3 + 168) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[fatigue]") != 0 )
    {
      *((uint32_t *)v3 + 169) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[fatigue result]") != 0 )
    {
      *((uint32_t *)v3 + 170) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[max monster]") != 0 )
    {
      *((uint32_t *)v3 + 162) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[player kc]") != 0 )
    {
      *((uint32_t *)v3 + 161) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn common monster index]") != 0 )
    {
      sub_5E5260((void **)v3 + 105);
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )
        sub_431230((int)(v3 + 420), &mm);
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn common champion index]") != 0 )
    {
      sub_5E5260((void **)v3 + 109);
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )
        sub_431230((int)(v3 + 436), &mm);
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn super champion index]") != 0 )
    {
      sub_5E5260((void **)v3 + 113);
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )
        sub_431230((int)(v3 + 452), &mm);
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn boss index]") != 0 )
    {
      sub_5E5260((void **)v3 + 117);
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )
        sub_431230((int)(v3 + 468), &mm);
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn step max]") != 0 )
    {
      *((uint32_t *)v3 + 125) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn step resource pool]") != 0 )
    {
      sub_5E5260((void **)v3 + 121);
      for ( i5 = sub_4423D0(&v75); v75 != 0; i5 = sub_4423D0(&v75) )
        sub_431230((int)(v3 + 484), &i5);
    }
    else if ( (uint8_t)sub_423300(&v83, "[kill count const]") != 0 )
    {
      *((float *)v3 + 152) = sub_442480(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[join cost gold]") != 0 )
    {
      *((uint32_t *)v3 + 126) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[gold drop prob]") != 0 )
    {
      *((uint32_t *)v3 + 127) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[common monster item drop prob]") != 0 )
    {
      *((uint32_t *)v3 + 128) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[common champion item drop prob]") != 0 )
    {
      *((uint32_t *)v3 + 129) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[super champion item drop prob]") != 0 )
    {
      *((uint32_t *)v3 + 130) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[boss item drop prob]") != 0 )
    {
      *((uint32_t *)v3 + 131) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[common monster exp const]") != 0 )
    {
      *((uint32_t *)v3 + 148) = 5 * sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[common champion exp const]") != 0 )
    {
      *((uint32_t *)v3 + 149) = 5 * sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[super champion exp const]") != 0 )
    {
      *((uint32_t *)v3 + 150) = 5 * sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[boss exp const]") != 0 )
    {
      *((uint32_t *)v3 + 151) = 5 * sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[common monster item drop list]") != 0 )
    {
      sub_5E5260((void **)v3 + 132);
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )
        sub_431230((int)(v3 + 528), &mm);
    }
    else if ( (uint8_t)sub_423300(&v83, "[common champion item drop list]") != 0 )
    {
      sub_5E5260((void **)v3 + 136);
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )
        sub_431230((int)(v3 + 544), &mm);
    }
    else if ( (uint8_t)sub_423300(&v83, "[super champion item drop list]") != 0 )
    {
      sub_5E5260((void **)v3 + 136);
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )
        sub_431230((int)(v3 + 560), &mm);
    }
    else if ( (uint8_t)sub_423300(&v83, "[boss item drop list]") != 0 )
    {
      sub_5E5260((void **)v3 + 144);
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )
        sub_431230((int)(v3 + 576), &mm);
    }
    else if ( (uint8_t)sub_423300(&v83, "[ancient dungeon]") != 0 )
    {
      v3[684] = sub_4423D0(nullptr) != 0;
    }
    else
    {
      v70 = v50;
      sub_401690(&v83);
      if ( sub_442C80((char)v50[0], v50[1], (int)v50[2], (int)v50[3], (int)v51, (int)v52, v53) == 0 )
      {
        v41 = (const char *)v84;
        if ( v86 < 0x10 )
          v41 = (const char *)&v84;
        off_77F3FC("SCRIPT TAG ERROR! [%s] %s", v2, v41);
      }
    }
    goto LABEL_189;
  }
  v53 = (unsigned int)v76;
  sub_443370();
  v71 = 0;
  mm = 0;
  v70 = (void ***)(v78 - 1);
  if ( v78 - 1 <= 0 )
    goto LABEL_189;
  i5 = 0;
  while ( 2 )
  {
    sub_4BD650(v80, mm, 2);
    v20 = (uint8_t *)v81[0];
    if ( v82 < 0x10 )
      v20 = v81;
    if ( *v20 == 13 )
      goto LABEL_76;
    v21 = (uint8_t *)v81[0];
    if ( v82 < 0x10 )
      v21 = v81;
    if ( *v21 == 10 )
      goto LABEL_76;
    v22 = (uint8_t *)v81[0];
    if ( v82 < 0x10 )
      v22 = v81;
    if ( *v22 == 32 )
    {
LABEL_76:
      v28 = mm + 1;
    }
    else
    {
      for ( i6 = 0; i6 < 16; ++i6 )
      {
        v24 = (uint8_t *)v81[0];
        if ( v82 < 0x10 )
          v24 = v81;
        v25 = *(uint8_t **)(dword_9B0AB0 + 4 * i6);
        if ( *v24 == *v25 )
        {
          v26 = (uint32_t *)v81[0];
          if ( v82 < 0x10 )
            v26 = v81;
          if ( *((uint8_t *)v26 + 1) == v25[1] )
            break;
        }
      }
      if ( i6 == 16 )
      {
        ++mm;
        ++v71;
        goto LABEL_78;
      }
      v27 = i5;
      *(uint32_t *)((char *)v59 + i5) = i6;
      i5 = v27 + 36;
      v28 = mm + 2;
    }
    mm = v28;
LABEL_78:
    sub_501490(v80);
    if ( mm < (int)v70 )
      continue;
    break;
  }
  if ( v71 == 0 )
    goto LABEL_189;
  sub_4750B0(&v57);
  sub_501490(v76);
  sub_501490(&v83);
  return 0;
}


// ============================================================
// §C 0x4F2B90-0x4F2E80 物品对象虚函数与 RTTI 族（IRDItem__vmt* —— 物品基类 IRDItem 的方法实现）
// ============================================================

// ------------------------------------------------------------
// 0x4F2B90 sub_4F2B90
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2B90(int a1, int a2, int a3)
{
  int result; // eax

  result = a1 * dword_9B6A50 / 1000;
  if ( a3 != 0 )
    return a2 * result / a3;
  return result;
}



// ------------------------------------------------------------
// 0x4F2BC0 sub_4F2BC0
// ------------------------------------------------------------
int sub_4F2BC0()
{
  int result; // eax

  if ( dword_9B0C64 != 0 )
    result = (**(int (/*thiscall*/ ***)(int, int))dword_9B0C64)(dword_9B0C64, 1);
  dword_9B0C64 = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4F2BE0 sub_4F2BE0
// ------------------------------------------------------------
int /*fastcall*/ sub_4F2BE0(int a1, int a2)
{
  int result; // eax

  *(uint32_t *)(a1 + 4) = 0;
  *(uint32_t *)(a1 + 128) = 0;
  result = sub_41A590(a1 + 132, a2, 0);
  *(uint8_t *)(a1 + 146) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4F2C10 sub_4F2C10
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2C10(int a1, int a2, int a3, int Value)
{
  int result; // eax

  if ( a3 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)a3 + 152))(a3, a1, a2, dword_79C0B0);
  result = Value;
  if ( Value > 1 )
    return sub_69A110(a1 + 27, a2 + 1, Value, -1);
  return result;
}



// ------------------------------------------------------------
// 0x4F2C60 IRDItem__vmt14
// ------------------------------------------------------------
bool /*thiscall*/ IRDItem__vmt14(uint32_t *this, int a2)
{
  return (a2 & *(this + 1)) == a2;
}



// ------------------------------------------------------------
// 0x4F2C80 IRDItem__vmt28
// ------------------------------------------------------------
int /*thiscall*/ IRDItem__vmt28(uint32_t *this, unsigned int a2)
{
  unsigned int v3; // edi
  int v4; // edx
  uint32_t *v5; // eax
  int result; // eax

  v3 = (unsigned int)(this + 33);
  if ( a2 > sub_41A5E0((unsigned int)(this + 33)) )
  {
    v5 = (uint32_t *)*(this + 32);
    if ( v5 != nullptr && *v5 == 0 )
      sub_5473D0(this);
  }
  result = sub_41A590(v3, v4, a2);
  if ( *(this + 32) != 0 )
    return sub_484D00();
  return result;
}



// ------------------------------------------------------------
// 0x4F2CE0 sub_4F2CE0
// ------------------------------------------------------------
const char */*cdecl*/ sub_4F2CE0(int a1)
{
  int v2; // eax
  int v3; // eax

  if ( a1 == 0 )
    return (const char *)sub_422E70(868);
  v2 = sub_4CE8A0(a1);
  if ( v2 != 0 )
    return (const char *)sub_41ACF0(v2 + 4);
  v3 = sub_4CE8A0(a1);
  if ( v3 != 0 )
    return (const char *)sub_41ACF0(v3 + 2120);
  else
    return "NONE";
}



// ------------------------------------------------------------
// 0x4F2D40 sub_4F2D40
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2D40(int a1)
{
  return (sub_4CE8A0(a1) != 0) + 1;
}



// ------------------------------------------------------------
// 0x4F2D60 sub_4F2D60
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2D60(int a1)
{
  int v1; // eax
  int v3; // eax

  if ( a1 == 0 )
    return 0;
  v1 = sub_4CE8A0(a1);
  if ( v1 != 0 )
    return *(uint32_t *)(v1 + 32);
  v3 = sub_4CE8A0(a1);
  if ( v3 != 0 )
    return *(uint32_t *)(v3 + 16);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4F2DA0 sub_4F2DA0
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2DA0(int a1)
{
  int v1; // eax
  int result; // eax
  int v3; // eax

  if ( a1 == 0 )
    return 0;
  v1 = sub_4CE8A0(a1);
  if ( v1 != 0 )
    return *(uint32_t *)(v1 + 64);
  v3 = sub_4CE8A0(a1);
  if ( v3 == 0 )
    return 0;
  result = *(uint32_t *)(v3 + 48);
  if ( result < 1 )
    return 1;
  return result;
}



// ------------------------------------------------------------
// 0x4F2DF0 sub_4F2DF0
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2DF0(int a1)
{
  switch ( a1 )
  {
    case 0:
      return -1;
    case 1:
      return -1190552;
    case 2:
      return -37965;
    case 3:
      return -1048321;
    default:
      break;
  }
  return a1 != 4 ? -1 : -16731649;
}



// ------------------------------------------------------------
// 0x4F2E40 sub_4F2E40
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2E40(int a1, int a2)
{
  sub_491530(2, 0);
  if ( dword_9B0C60 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_9B0C60 + 152))(
      dword_9B0C60,
      a1 - 1,
      a2 - 1,
      dword_79C0B0);
  return sub_491630(2);
}



// ------------------------------------------------------------
// 0x4F2E80 sub_4F2E80
// ------------------------------------------------------------
void /*cdecl*/ sub_4F2E80(int a1, int a2, int a3, int a4)
{
  uint32_t *v4; // ecx
  int v5; // eax

  if ( a3 != 0 )
  {
    if ( a4 <= 0 )
    {
      if ( a4 > -450 )
      {
        sub_491530(2, 0);
        v5 = sub_418DD0(a4 / -50);
        if ( v5 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, a1, a2, dword_79C0B0);
        sub_491630(2);
      }
    }
    else
    {
      v4 = (uint32_t *)dword_79C0B0;
      *(uint32_t *)(dword_79C0B0 + 48) = 0;
      v4[13] = 0;
      v4[14] = 640;
      v4[15] = a2 + 28 * a4 / a3;
      if ( dword_9B0C68 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)dword_9B0C68 + 128))(
          dword_9B0C68,
          a1,
          a2,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          -2130706433,
          1333788672,
          1333788672);
      sub_488670(dword_79C0B0);
    }
  }
}



// ------------------------------------------------------------
// 0x4F2F70 IRDItem__vmt60
// ------------------------------------------------------------
int /*thiscall*/ IRDItem__vmt60(int *this)
{
  int v2; // eax
  int v3; // esi
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // eax

  if ( *(this + 14) == 0 || (*(uint8_t (/*thiscall*/ **)(int *))(*this + 72))(this) == 0 )
    return 0;
  v2 = __RTDynamicCast((int)this, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
  v3 = v2;
  if ( v2 == 0 )
    return dword_9B6A50 * *(this + 14) / 1000;
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 172))(v2);
  v5 = sub_41A5E0(v4 + 18);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 188))(v3);
  v7 = sub_41A5E0(v6 + 32);
  return sub_4F2B90(*(this + 14), v7, v5);
}



// ------------------------------------------------------------
// 0x4F3010 IRDItem__vmt64
// ------------------------------------------------------------
int /*thiscall*/ IRDItem__vmt64(uint32_t *this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  v3 = *(this + 18);
  if ( dword_8F7C04 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t *, int *))(*(uint32_t *)dword_8F7C04 + 1168))(dword_8F7C04, this, &v3);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 112))(this, v3);
}



// ------------------------------------------------------------
// 0x4F3050 IRDItem__vmt18
// ------------------------------------------------------------
int /*thiscall*/ IRDItem__vmt18(int *this)
{
  if ( (*(int (/*thiscall*/ **)(int *))*this)(this) != 2 )
    return sub_4F2DF0(*(this + 23));
  if ( *(int *)(*(int (/*thiscall*/ **)(int *))(*this + 172))(this) <= 7 )
    return -16731649;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 236))(this) != 0
    || (*(uint8_t (/*thiscall*/ **)(int *))(*this + 240))(this) != 0 )
  {
    return -14745736;
  }
  else
  {
    return sub_4F2DF0(*(this + 23));
  }
}



// ------------------------------------------------------------
// 0x4F30B0 IRDItem__vmt48
// ------------------------------------------------------------
BOOL /*thiscall*/ IRDItem__vmt48(void *this)
{
  return (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 84))(this) != 0
      && *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 16))(this) + 52) == 0;
}



// ------------------------------------------------------------
// 0x4F30E0 IRDItem__vmt8
// ------------------------------------------------------------
void /*thiscall*/ IRDItem__vmt8(uint32_t *this, int a2, int a3, char a4, char a5)
{
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // [esp-Ch] [ebp-10h]
  int v11; // [esp+14h] [ebp+10h]

  if ( *((uint8_t *)this + 146) != 0 && a4 == 0 )
  {
    if ( *((uint32_t *)dword_8F8528 + 626) == 2 && *((uint32_t *)dword_8F8528 + 628) == *(this + 3) )
      return;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 88))(this, 0);
  }
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 44))(this);
  v7 = *(this + 19);
  v11 = v6;
  if ( v7 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, a2, a3, dword_79C0B0);
    v6 = v11;
  }
  if ( v6 > 1 )
    sub_69A110(a2 + 27, a3 + 1, v6, -1);
  if ( *((uint8_t *)this + 40) != 0 )
  {
    if ( dword_9B0C48 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_9B0C48 + 152))(dword_9B0C48, a2, a3, dword_79C0B0);
    sub_491530(2, 0);
    if ( dword_9B0C4C != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_9B0C4C + 152))(
        dword_9B0C4C,
        a2 + 1,
        a3 + 1,
        dword_79C0B0);
    sub_491630(2);
  }
  else if ( *(this + 15) != 0 )
  {
    if ( dword_9B0C58 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_9B0C58 + 152))(dword_9B0C58, a2, a3, dword_79C0B0);
  }
  else
  {
    v8 = *(this + 9);
    if ( v8 == 1 || v8 == 3 )
    {
      if ( dword_9B0C50 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_9B0C50 + 152))(dword_9B0C50, a2, a3, dword_79C0B0);
    }
    else if ( v8 == 2 )
    {
      sub_40FC80(a2, a3, dword_9B0C54);
    }
  }
  if ( dword_8F7C04 != 0
    && (*(uint8_t (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F7C04 + 804))(dword_8F7C04, this) == 0
    && dword_9B0C5C != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)dword_9B0C5C + 128))(
      dword_9B0C5C,
      a2,
      a3,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      1308622847,
      1333788672,
      1333788672);
  }
  if ( a5 != 0 )
  {
    v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    sub_4F2E80(a2, a3, v9, v10);
  }
}



// ============================================================
// §D 0x4F32A0-0x4F43D0 物品资源/图标/动画加载族（Item/FieldImage.img、Item/AttachIcon.img、Etc/Disjoint.etc）
// ============================================================

// ------------------------------------------------------------
// 0x4F32A0 sub_4F32A0
// ------------------------------------------------------------
int /*cdecl*/ sub_4F32A0(int a1)
{
  int v2; // esi
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // [esp-8h] [ebp-Ch]
  int v7; // [esp-8h] [ebp-Ch]

  if ( a1 == 0 )
  {
    (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Item/FieldImage.img");
    return sub_418DD0(26);
  }
  v2 = sub_4CE8A0(a1);
  if ( v2 != 0 )
  {
    if ( (uint8_t)sub_42FD40(szPassword) != 0 )
    {
      v3 = sub_41ACF0(v2 + 88);
      v6 = *(uint32_t *)(v2 + 92);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v3);
      return sub_418DD0(v6);
    }
  }
  else
  {
    v4 = sub_4CE8A0(a1);
    if ( v4 != 0 && (uint8_t)sub_42FD40(szPassword) != 0 )
    {
      v5 = sub_41ACF0(v4 + 68);
      v7 = *(uint32_t *)(v4 + 72);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v5);
      return sub_418DD0(v7);
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4F3360 sub_4F3360
// ------------------------------------------------------------
char /*stdcall*/ sub_4F3360(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 25);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_4F3360(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 25);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F33A0 sub_4F33A0
// ------------------------------------------------------------
int /*cdecl*/ sub_4F33A0(int a1)
{
  int v2; // esi
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // [esp-8h] [ebp-Ch]
  int v7; // [esp-8h] [ebp-Ch]

  if ( a1 == 0 )
    return sub_418DD0(10);
  v2 = sub_4CE8A0(a1);
  if ( v2 != 0 )
  {
    if ( (uint8_t)sub_42FD40(szPassword) != 0 )
    {
      v3 = sub_41ACF0(v2 + 80);
      v6 = *(uint32_t *)(v2 + 84);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v3);
      return sub_418DD0(v6);
    }
  }
  else
  {
    v4 = sub_4CE8A0(a1);
    if ( v4 != 0 && (uint8_t)sub_42FD40(szPassword) != 0 )
    {
      v5 = sub_41ACF0(v4 + 60);
      v7 = *(uint32_t *)(v4 + 64);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v5);
      return sub_418DD0(v7);
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4F3460 sub_4F3460
// ------------------------------------------------------------
int *sub_4F3460()
{
  int *result; // eax

  sub_4F3360(*(void ***)(dword_9B8DBC + 4));
  *(uint32_t *)(dword_9B8DBC + 4) = dword_9B8DBC;
  dword_9B8DC0 = 0;
  *(uint32_t *)dword_9B8DBC = dword_9B8DBC;
  *(uint32_t *)(dword_9B8DBC + 8) = dword_9B8DBC;
  sub_4F3360(*(void ***)(dword_9B8DC8 + 4));
  *(uint32_t *)(dword_9B8DC8 + 4) = dword_9B8DC8;
  dword_9B8DCC = 0;
  *(uint32_t *)dword_9B8DC8 = dword_9B8DC8;
  *(uint32_t *)(dword_9B8DC8 + 8) = dword_9B8DC8;
  result = &dword_9B08EC;
  do
  {
    *(result - 1) = 0;
    *result = 0;
    result += 2;
  }
  while ( (int)result < (int)&dword_9B097C );
  return result;
}



// ------------------------------------------------------------
// 0x4F34F0 sub_4F34F0
// ------------------------------------------------------------
void /*noreturn*/ sub_4F34F0()
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
// 0x4F3560 sub_4F3560
// ------------------------------------------------------------
void /*thiscall*/ sub_4F3560(int this)
{
  int v2; // esi
  int v3; // esi
  int i; // [esp+Ch] [ebp-4h]
  int j; // [esp+Ch] [ebp-4h]

  v2 = this + 4;
  for ( i = 5; i != 0; --i )
  {
    if ( *(uint32_t *)v2 != 0 )
      j__free(*(void **)v2);
    *(uint32_t *)v2 = 0;
    *(uint32_t *)(v2 + 4) = 0;
    *(uint32_t *)(v2 + 8) = 0;
    v2 += 16;
  }
  v3 = this + 88;
  for ( j = 4; j != 0; --j )
  {
    *(uint32_t *)(v3 - 8) = 0;
    if ( *(uint32_t *)v3 != 0 )
      j__free(*(void **)v3);
    *(uint32_t *)v3 = 0;
    *(uint32_t *)(v3 + 4) = 0;
    *(uint32_t *)(v3 + 8) = 0;
    v3 += 20;
  }
  *(uint32_t *)(this + 160) = -1;
  if ( *(uint32_t *)(this + 168) != 0 )
    j__free(*(void **)(this + 168));
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
}



// ------------------------------------------------------------
// 0x4F3610 sub_4F3610
// ------------------------------------------------------------
void /*thiscall*/ sub_4F3610(void **this)
{
  `eh vector destructor iterator'(this + 68, 0x14u, 4, sub_42D400);
  if ( *(this + 42) != nullptr )
    j__free(*(this + 42));
  *(this + 42) = nullptr;
  *(this + 43) = nullptr;
  *(this + 44) = nullptr;
  `eh vector destructor iterator'(this + 20, 0x14u, 4, sub_42D400);
  `eh vector destructor iterator'(this, 0x10u, 5, (void (/*thiscall*/ *)(void *))sub_5E5260);
}



// ------------------------------------------------------------
// 0x4F36B0 sub_4F36B0
// ------------------------------------------------------------
int /*cdecl*/ sub_4F36B0(int a1, int a2, int a3, int a4, int a5)
{
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  const char *v8; // eax
  const char *v9; // eax
  char Buffer[64]; // [esp+Ch] [ebp-6Ch] BYREF
  uint8_t v12[4]; // [esp+4Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+50h] [ebp-28h]
  int v14; // [esp+60h] [ebp-18h]
  unsigned int v15; // [esp+64h] [ebp-14h]
  int v16; // [esp+68h] [ebp-10h]
  int v17; // [esp+74h] [ebp-4h]

  v16 = dword_796E50;
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0((void *)szPassword, 0);
  v17 = 0;
  if ( a2 != 0 )
  {
    v5 = (const char *)sub_5486B0(a2);
    sub_4022F0((std::_String_base *)v12, v5, strlen(v5));
    v6 = (const char *)sub_422E70(424);
    sub_4022F0((std::_String_base *)v12, v6, strlen(v6));
  }
  if ( a3 != 0 )
  {
    if ( v14 != 0 )
      sub_4022F0((std::_String_base *)v12, " ", 1);
    v7 = (const char *)sub_422E70(870);
    sprintf(Buffer, v7, a3);
    sub_4022F0((std::_String_base *)v12, Buffer, strlen(Buffer));
  }
  if ( a4 != 0 )
  {
    if ( v14 != 0 )
      sub_4022F0((std::_String_base *)v12, " ", 1);
    v8 = (const char *)sub_422E70(871);
    sprintf(Buffer, v8, a4);
    sub_4022F0((std::_String_base *)v12, Buffer, strlen(Buffer));
  }
  if ( a5 != 0 )
  {
    v9 = (const char *)sub_422E70(425);
    sprintf(Buffer, "%d%s", a5, v9);
    sub_4022F0((std::_String_base *)v12, Buffer, strlen(Buffer));
  }
  *(uint32_t *)(a1 + 24) = 15;
  *(uint32_t *)(a1 + 20) = 0;
  *(uint8_t *)(a1 + 4) = 0;
  sub_4014D0((std::_String_base *)a1, v12, 0, -1);
  if ( v15 >= 0x10 )
    j__free(Block);
  return a1;
}



// ------------------------------------------------------------
// 0x4F3880 sub_4F3880
// ------------------------------------------------------------
void /*thiscall*/ sub_4F3880(void *this)
{
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *(uint32_t *)this = 0;
  if ( *((uint32_t *)this + 2) != 0 )
    j__free(*((void **)this + 2));
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
}



// ------------------------------------------------------------
// 0x4F38C0 sub_4F38C0
// ------------------------------------------------------------
char */*thiscall*/ sub_4F38C0(char *this)
{
  `eh vector constructor iterator'(this, 0x10u, 5, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  `eh vector constructor iterator'(this + 80, 0x14u, 4, sub_4F3880, sub_42D400);
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 43) = 0;
  *((uint32_t *)this + 44) = 0;
  `eh vector constructor iterator'(this + 272, 0x14u, 4, sub_4F38B0, sub_42D400);
  sub_4F3560((int)this);
  return this;
}



// ------------------------------------------------------------
// 0x4F3960 sub_4F3960
// ------------------------------------------------------------
void sub_4F3960()
{
  int v0; // eax
  int v1[88]; // [esp+4h] [ebp-170h] BYREF
  void *Block; // [esp+164h] [ebp-10h]
  int v3; // [esp+170h] [ebp-4h]

  dword_9B0C48 = sub_418DD0(119);
  dword_9B0C4C = sub_418DD0(118);
  (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Item/AttachIcon.img");
  dword_9B0C50 = sub_418DD0(0);
  dword_9B0C54 = sub_418DD0(1);
  dword_9B0C58 = sub_418DD0(2);
  dword_9B0C5C = sub_418DD0(4);
  dword_9B0C60 = sub_418DD0(6);
  Block = operator new(0x2Cu);
  v3 = 0;
  if ( Block != nullptr )
    v0 = sub_423B30(dword_79C0B0, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 13, 12);
  else
    v0 = 0;
  dword_9B0C64 = v0;
  v3 = -1;
  *(uint32_t *)(v0 + 36) = 2;
  sub_699070((int)&unk_9B0C70, 1u);
  byte_9B0C7D = 0;
  byte_9B0C7E = 0;
  sub_698F90((int)&unk_9B0C70, 0, 0);
  dword_9B0C68 = sub_418DD0(84);
  dword_9B0C6C = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 124);
  sub_4F38C0((char *)v1);
  v3 = 1;
  sub_6014F0((int)v1, (char)"Etc/Disjoint.etc");
  dword_791ED8 = v1[40];
  v3 = -1;
  sub_4F3610((void **)v1);
}



// ------------------------------------------------------------
// 0x4F3B10 sub_4F3B10
// ------------------------------------------------------------
int /*stdcall*/ sub_4F3B10(char *Buffer, int a2, char *Format, va_list ArgList)
{
  int result; // eax
  unsigned int v5; // esi
  int v6; // eax
  bool v7; // zf

  if ( a2 == 0 )
    return -2147024809;
  v5 = a2 - 1;
  v6 = _vsnprintf(Buffer, a2 - 1, Format, ArgList);
  if ( v6 < 0 || (v7 = v6 == v5, v6 > v5) )
  {
    Buffer[v5] = 0;
    return -2147024774;
  }
  else
  {
    result = 0;
    if ( v7 )
      Buffer[v5] = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F3B70 sub_4F3B70
// ------------------------------------------------------------
int sub_4F3B70(char *Buffer, unsigned int a2, char *Format, ...)
{
  va_list va; // [esp+14h] [ebp+14h] BYREF

  va_start(va, Format);
  if ( a2 <= 0x7FFFFFFF )
    return sub_4F3B10(Buffer, a2, Format, va);
  else
    return -2147024809;
}



// ------------------------------------------------------------
// 0x4F3BA0 sub_4F3BA0
// ------------------------------------------------------------
int /*thiscall*/ sub_4F3BA0(void *this, int a2, char a3, int a4, int a5)
{
  int result; // eax
  uint32_t *v6; // esi
  int v7; // ecx
  int v8; // eax
  int v9; // ebx
  int v10; // edi
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // [esp-8h] [ebp-13Ch]
  char Buffer[256]; // [esp+8h] [ebp-12Ch] BYREF
  uint8_t v16[4]; // [esp+108h] [ebp-2Ch] BYREF
  void *Block; // [esp+10Ch] [ebp-28h]
  int v18; // [esp+11Ch] [ebp-18h]
  unsigned int v19; // [esp+120h] [ebp-14h]
  int v20; // [esp+124h] [ebp-10h]
  int v21; // [esp+130h] [ebp-4h]
  int v22; // [esp+13Ch] [ebp+8h]
  int v23; // [esp+13Ch] [ebp+8h]
  int i; // [esp+140h] [ebp+Ch]

  v20 = dword_796E50;
  result = (*(int (/*thiscall*/ **)(void *, bool, int))(*(uint32_t *)this + 8))(this, a3 != 0, a2);
  v6 = (uint32_t *)result;
  if ( result != 0 )
  {
    if ( a3 != 0 )
    {
      v7 = *(uint32_t *)(result + 8);
      v8 = v7 != 0 ? (*(uint32_t *)(result + 12) - v7) >> 5 : 0;
      if ( v8 > 0 )
      {
        v9 = 0;
        v10 = 0;
        for ( i = v8; i != 0; --i )
        {
          if ( sub_40BF00((std::_String_base *)(v10 + v6[2]), 0, *(uint32_t *)(v10 + v6[2] + 20), szPassword, 0) != 0 )
          {
            v11 = v6[2];
            if ( *(uint32_t *)(v10 + v11 + 24) < 0x10u )
              sprintf(Buffer, (const char *const)(v10 + v11 + 4), a4, a5);
            else
              sprintf(Buffer, *(const char *const *)(v10 + v11 + 4), a4, a5);
            v19 = 15;
            v18 = 0;
            LOBYTE(Block) = 0;
            sub_4015C0(Buffer, strlen(Buffer));
            v12 = *(uint32_t *)(*v6 + 44);
            v21 = 0;
            v22 = v12;
            v13 = sub_4BC700((uint32_t *)dword_8F84BC, (int)v16);
            *(uint32_t *)(v9 + v22 + 4) = v13;
            *(uint32_t *)(v9 + *(uint32_t *)(*v6 + 44) + 8) = *(uint32_t *)(v10 + v6[2] + 28);
            v23 = *(uint32_t *)(*v6 + 44);
            v14 = *(uint32_t *)(v10 + v6[2] + 28);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v13);
            *(uint32_t *)(v9 + v23) = sub_418DD0(v14);
            v21 = -1;
            if ( v19 >= 0x10 )
              j__free(Block);
            v19 = 15;
            v18 = 0;
            LOBYTE(Block) = 0;
          }
          v10 += 32;
          v9 += 88;
        }
      }
    }
    return *v6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F3D60 sub_4F3D60
// ------------------------------------------------------------
int /*thiscall*/ sub_4F3D60(void *this, const char *ArgList, const char *a3, char a4, int a5, int a6)
{
  char Buffer[512]; // [esp+4h] [ebp-204h] BYREF
  int v9; // [esp+204h] [ebp-4h]

  v9 = dword_796E50;
  sub_4F3B70(Buffer, 0x200u, "%s%s", ArgList, a3);
  return sub_4F3BA0(this, (int)Buffer, a4, a5, a6);
}



// ------------------------------------------------------------
// 0x4F3DD0 sub_4F3DD0
// ------------------------------------------------------------
int /*thiscall*/ sub_4F3DD0(int this, const char *ArgList, int a3, int a4)
{
  uint32_t *v5; // ecx

  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 8) = 0;
  *(uint8_t *)(this + 12) = 1;
  *(uint8_t *)(this + 14) = 0;
  *(uint8_t *)(this + 13) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  v5 = (uint32_t *)(this + 60);
  v5[15] = 0;
  v5[16] = 0;
  v5[17] = 0;
  v5[19] = 0;
  v5[20] = 0;
  v5[21] = 0;
  sub_430B70(v5);
  *(uint32_t *)(this + 204) = sub_4A2CF0(this + 200);
  *(uint32_t *)(this + 208) = 0;
  sub_493BD0(this);
  sub_494E40((uint8_t *)this, szPassword, ArgList, 0, a3, a4, 0, 0);
  return this;
}



// ------------------------------------------------------------
// 0x4F3E90 CNAnimationLoader__vmt30
// ------------------------------------------------------------
int */*stdcall*/ CNAnimationLoader__vmt30(const char *ArgList, int a2)
{
  int *v2; // eax
  int *v3; // esi
  int v4; // eax
  int v5; // edx
  int v6; // eax

  v2 = (int *)operator new(0x14u);
  if ( v2 != nullptr )
  {
    *v2 = 0;
    v2[2] = 0;
    v2[3] = 0;
    v2[4] = 0;
    v3 = v2;
  }
  else
  {
    v3 = nullptr;
  }
  v4 = sub_42FCB0(228);
  if ( v4 != 0 )
  {
    v5 = a2;
    LOBYTE(v5) = a2 != 0;
    v6 = sub_4F3DD0(v4, ArgList, v5, (int)(v3 + 1));
  }
  else
  {
    v6 = 0;
  }
  *v3 = v6;
  return v3;
}



// ------------------------------------------------------------
// 0x4F3F30 CNAnimationLoader__vmt34
// ------------------------------------------------------------
void /*stdcall*/ CNAnimationLoader__vmt34(void ***Block)
{
  void **v1; // edi

  v1 = *Block;
  if ( *Block != nullptr )
  {
    sub_42AF90(*Block);
    sub_657740(v1, 228);
  }
  *Block = nullptr;
  sub_4F3DC0(Block);
  j__free(Block);
}



// ------------------------------------------------------------
// 0x4F3F80 HttpFileJob__vmt18
// ------------------------------------------------------------
int /*stdcall*/ HttpFileJob__vmt18(uint32_t *a1, int a2, int a3, int a4, int a5)
{
  int v5; // eax
  bool v7; // cc
  int v8; // eax

  if ( *(uint32_t *)(a1[1] + 4) == 1 )
  {
    v5 = a1[2];
    if ( v5 != 0 )
      (*(void (**)(void))(*(uint32_t *)v5 + 8))();
    return -2147467260;
  }
  else
  {
    v7 = timeGetTime() <= a1[10];
    v8 = a1[2];
    if ( v7 )
    {
      if ( v8 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)a1[2] + 12))(a1[2], a2, a3);
      return 0;
    }
    else
    {
      if ( v8 != 0 )
        (*(void (**)(void))(*(uint32_t *)v8 + 8))();
      return -2147467260;
    }
  }
}



// ------------------------------------------------------------
// 0x4F3FF0 sub_4F3FF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4F3FF0(void **this)
{
  *this = &vftbl_HttpFileJob;
  if ( (unsigned int)*(this + 9) >= 0x10 )
    j__free(*(this + 4));
  *(this + 9) = (void *)15;
  *(this + 8) = nullptr;
  *((uint8_t *)this + 16) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4F4030 sub_4F4030
// ------------------------------------------------------------
int /*thiscall*/ sub_4F4030(char *this)
{
  uint32_t *v2; // ecx
  int v3; // eax
  int v4; // eax

  v2 = this + 132;
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = 0;
  *((uint32_t *)this + 2) = 0;
  *v2 = 0;
  v2[1] = 0;
  if ( *((uint32_t *)this + 19) != 0 )
  {
    while ( 1 )
      ;
  }
  while ( *((uint32_t *)this + 24) != 0 )
  {
    v3 = *((uint32_t *)this + 24);
    if ( v3 != 0 )
    {
      v4 = v3 - 1;
      *((uint32_t *)this + 24) = v4;
      if ( v4 == 0 )
        *((uint32_t *)this + 23) = 0;
    }
  }
  if ( *((uint32_t *)this + 26) != 0 )
    j__free(*((void **)this + 26));
  *((uint32_t *)this + 26) = 0;
  *((uint32_t *)this + 27) = 0;
  *((uint32_t *)this + 28) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4F40A0 sub_4F40A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4F40A0(int this)
{
  HANDLE *v3; // eax
  HANDLE *v4; // esi
  void ***i; // esi
  void **v6; // ebx

  if ( *(uint32_t *)this == 0 )
    return 1;
  v3 = *(HANDLE **)(this + 124);
  v4 = *(HANDLE **)(this + 120);
  *(uint32_t *)(this + 4) = 1;
  if ( v4 != v3 )
  {
    do
    {
      TerminateThread(*v4, 0);
      CloseHandle(*v4++);
    }
    while ( v4 != *(HANDLE **)(this + 124) );
  }
  for ( i = *(void ****)(this + 104); i != *(void ****)(this + 108); ++i )
  {
    v6 = *i;
    if ( *i != nullptr )
    {
      sub_4F3FF0(*i);
      j__free(v6);
    }
  }
  DeleteCriticalSection((LPCRITICAL_SECTION)(this + 12));
  DeleteCriticalSection((LPCRITICAL_SECTION)(this + 36));
  sub_4F4030((char *)this);
  *(uint32_t *)this = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4F41A0 sub_4F41A0
// ------------------------------------------------------------
void /*noreturn*/ sub_4F41A0()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0("deque<T> too long", 0x11u);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4F4210 sub_4F4210
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F4210(uint32_t *this, int a2)
{
  uint32_t *v3; // ecx

  v3 = this + 3;
  *this = &vftbl_HttpFileJob;
  v3[6] = 15;
  v3[5] = 0;
  *((uint8_t *)v3 + 4) = 0;
  *(this + 1) = a2;
  *(this + 2) = 0;
  sub_4015C0((void *)szPassword, 0);
  *(this + 10) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4F4280 sub_4F4280
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4F4280(int this, unsigned int a2)
{
  unsigned int v2; // edx
  unsigned int v4; // eax
  unsigned int v5; // ecx
  unsigned int v6; // edi
  int v7; // esi
  char *v8; // eax
  const void *v9; // ecx
  char *v10; // eax
  char *v11; // edx
  unsigned int v12; // ecx
  char *v13; // edi
  size_t v14; // esi
  char *v15; // eax
  unsigned int result; // eax
  size_t v17; // [esp+8h] [ebp-Ch]
  char *v18; // [esp+10h] [ebp-4h]

  v2 = a2;
  v4 = *(uint32_t *)(this + 8);
  if ( 0xFFFFFFF - v4 < a2 )
    sub_4F41A0(this);
  v5 = v4 >> 1;
  if ( v4 >> 1 < 8 )
    v5 = 8;
  if ( a2 < v5 && v4 <= 0xFFFFFFF - v5 )
  {
    a2 = v5;
    v2 = v5;
  }
  v6 = *(uint32_t *)(this + 12) >> 2;
  v7 = 4 * v6;
  v18 = (char *)operator new(4 * (v2 + v4));
  v17 = 4 * ((int)(4 * *(uint32_t *)(this + 8) - 4 * v6) >> 2);
  v8 = (char *)memcpy_0(&v18[4 * v6], (const void *)(4 * v6 + *(uint32_t *)(this + 4)), v17);
  v9 = *(const void **)(this + 4);
  v10 = &v8[v17];
  if ( v6 > a2 )
  {
    memcpy_0(v10, v9, 4 * ((int)(4 * a2) >> 2));
    v14 = 4 * ((int)(v7 - 4 * a2) >> 2);
    v15 = (char *)memcpy_0(v18, (const void *)(4 * a2 + *(uint32_t *)(this + 4)), v14);
    v12 = a2;
    v13 = &v15[v14];
    if ( a2 == 0 )
      goto LABEL_15;
    goto LABEL_14;
  }
  v11 = (char *)memcpy_0(v10, v9, 4 * (v7 >> 2)) + 4 * (v7 >> 2);
  if ( a2 != v6 )
    memset(v11, 0, 4 * (a2 - v6));
  if ( v6 != 0 )
  {
    v12 = v6;
    v13 = v18;
LABEL_14:
    memset(v13, 0, 4 * v12);
  }
LABEL_15:
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  result = a2 + *(uint32_t *)(this + 8);
  *(uint32_t *)(this + 4) = v18;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ============================================================
// §E 0x4F43D0-0x4F5B90 物品容器模板族（vector/list/deque 辅助 —— "vector<T> too long"/"deque<T> too long" 系 CRT 实例）
// ============================================================

// ------------------------------------------------------------
// 0x4F43D0 sub_4F43D0
// ------------------------------------------------------------
void /*noreturn*/ sub_4F43D0()
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
// 0x4F4440 sub_4F4440
// ------------------------------------------------------------
int /*thiscall*/ sub_4F4440(int this, uint32_t *a2)
{
  int v3; // eax
  unsigned int v4; // eax
  unsigned int v5; // edi
  unsigned int v6; // ebx
  uint32_t *v7; // edi
  int result; // eax

  v3 = *(uint32_t *)(this + 16);
  if ( (((uint8_t)v3 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(v3 + 4) >> 2 )
    sub_4F4280(this, 1u);
  v4 = *(uint32_t *)(this + 8);
  v5 = *(uint32_t *)(this + 16) + *(uint32_t *)(this + 12);
  v6 = v5 >> 2;
  if ( v4 <= v5 >> 2 )
    v6 -= v4;
  if ( *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0 )
    *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) = operator new(0x10u);
  v7 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) + 4 * (v5 & 3));
  if ( v7 != nullptr )
    *v7 = *a2;
  result = *(uint32_t *)(this + 16) + 1;
  *(uint32_t *)(this + 16) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4F44C0 sub_4F44C0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4F44C0(int this, int Src, unsigned int a3, int *a4)
{
  int v5; // edx
  unsigned int result; // eax
  int v8; // ecx
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // eax
  char *v14; // eax
  void *v15; // eax
  int v16; // eax
  int v17; // ecx
  unsigned int v18; // edi
  uint8_t *v19; // eax
  unsigned int v21; // edx
  int v22; // ecx
  char *v23; // edi
  int v24; // edi
  char *v25; // [esp+8h] [ebp-4h]
  int Srcb; // [esp+14h] [ebp+8h]
  char *Srca; // [esp+14h] [ebp+8h]
  int v28; // [esp+18h] [ebp+Ch]
  int v29; // [esp+18h] [ebp+Ch]

  v5 = *(uint32_t *)(this + 4);
  a4 = (int *)*a4;
  if ( v5 != 0 )
    result = (*(uint32_t *)(this + 12) - v5) >> 2;
  else
    result = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v8 = 0;
    if ( 0x3FFFFFFF - v8 < a3 )
      sub_4F43D0(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v9 = 0;
    if ( result >= a3 + v9 )
    {
      v19 = *(uint8_t **)(this + 8);
      v21 = (int)&v19[-Src] >> 2;
      v22 = 4 * a3;
      v29 = (int)v19;
      Srca = (char *)(4 * a3);
      if ( v21 >= a3 )
      {
        v24 = (int)&v19[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&v19[-v22], (int)v19, v19);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &a4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)v19, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), a3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &a4);
        v23 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = v23;
        return sub_49A9D0(Src, v23 - Srca, &a4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) >> 2;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(uint32_t *)(this + 8) - v5) >> 2;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v28 = 4 * v10;
      v25 = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      v14 = (char *)memcpy_0(v25, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&v14[Srcb], a3, &a4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
      v16 = *(uint32_t *)(this + 4);
      if ( v16 != 0 )
        v17 = (*(uint32_t *)(this + 8) - v16) >> 2;
      else
        v17 = 0;
      v18 = v17 + a3;
      if ( v16 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v25[v28];
      *(uint32_t *)(this + 8) = &v25[4 * v18];
      *(uint32_t *)(this + 4) = v25;
      return (unsigned int)v25;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4F46A0 sub_4F46A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4F46A0(int this)
{
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  sub_4F4030((char *)this);
  return this;
}



// ------------------------------------------------------------
// 0x4F4710 sub_4F4710
// ------------------------------------------------------------
int /*thiscall*/ sub_4F4710(char *this, void *Src, int a3, int a4)
{
  unsigned int v6; // edx
  unsigned int v7; // eax
  unsigned int v8; // edx
  unsigned int v9; // edi
  int v10; // esi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // [esp+4h] [ebp-4h] BYREF

  if ( *(uint32_t *)this == 0 )
    return 1;
  EnterCriticalSection((LPCRITICAL_SECTION)(this + 36));
  if ( *((uint32_t *)this + 24) != 0 )
  {
    v6 = *((uint32_t *)this + 23) + *((uint32_t *)this + 24) - 1;
    v7 = v6 >> 2;
    v8 = v6 - 4 * (v6 >> 2);
    v9 = *((uint32_t *)this + 22);
    if ( v9 <= v7 )
      v7 -= v9;
    v10 = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)this + 21) + 4 * v7) + 4 * v8);
    v11 = *((uint32_t *)this + 24);
    v14 = v10;
    if ( v11 != 0 )
    {
      v12 = v11 - 1;
      *((uint32_t *)this + 24) = v12;
      if ( v12 == 0 )
        *((uint32_t *)this + 23) = 0;
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 36));
    sub_4015C0(Src, strlen((const char *)Src));
    v13 = a4;
    *(uint32_t *)(v10 + 8) = a3;
    if ( a4 == 0 )
      v13 = *((uint32_t *)this + 34);
    *(uint32_t *)(v10 + 40) = v13;
    EnterCriticalSection((LPCRITICAL_SECTION)(this + 12));
    sub_4F4440((int)(this + 60), &v14);
    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 12));
    return 0;
  }
  else
  {
    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 36));
    return 1;
  }
}



// ------------------------------------------------------------
// 0x4F4800 sub_4F4800
// ------------------------------------------------------------
DWORD /*stdcall*/ sub_4F4800(char *lpThreadParameter)
{
  DWORD result; // eax
  IBindStatusCallback *v2; // edi
  unsigned int v3; // eax
  int v4; // ecx
  unsigned int v5; // edx
  int v6; // eax
  unsigned int v7; // ecx
  unsigned int v8; // edx
  int v9; // eax
  struct IBindStatusCallbackVtbl *lpVtbl; // ecx
  const CHAR *v11; // eax
  struct IBindStatusCallbackVtbl *v12; // eax
  struct IBindStatusCallbackVtbl *v13; // eax
  IBindStatusCallback *i; // [esp+Ch] [ebp-10Ch] BYREF
  CHAR v15[260]; // [esp+10h] [ebp-108h] BYREF
  int v16; // [esp+114h] [ebp-4h]

  v16 = dword_796E50;
  result = *((uint32_t *)lpThreadParameter + 1);
  v2 = nullptr;
  for ( i = nullptr; result != 1; i = nullptr )
  {
    EnterCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 12));
    if ( *((uint32_t *)lpThreadParameter + 19) != 0 )
    {
      v3 = *((uint32_t *)lpThreadParameter + 18) >> 2;
      v4 = *((uint32_t *)lpThreadParameter + 18) - 4 * v3;
      v5 = *((uint32_t *)lpThreadParameter + 17);
      if ( v5 <= v3 )
        v3 -= v5;
      v2 = *(IBindStatusCallback **)(*(uint32_t *)(*((uint32_t *)lpThreadParameter + 16) + 4 * v3) + 4 * v4);
      v6 = *((uint32_t *)lpThreadParameter + 19);
      i = v2;
      if ( v6 != 0 )
      {
        v7 = *((uint32_t *)lpThreadParameter + 18) + 1;
        v8 = 4 * *((uint32_t *)lpThreadParameter + 17);
        *((uint32_t *)lpThreadParameter + 18) = v7;
        if ( v8 <= v7 )
          *((uint32_t *)lpThreadParameter + 18) = 0;
        v9 = v6 - 1;
        *((uint32_t *)lpThreadParameter + 19) = v9;
        if ( v9 == 0 )
          *((uint32_t *)lpThreadParameter + 18) = 0;
      }
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 12));
    if ( v2 != nullptr )
    {
      lpVtbl = v2[2].lpVtbl;
      if ( lpVtbl != nullptr )
        (*(void (/*thiscall*/ **)(struct IBindStatusCallbackVtbl *))lpVtbl->QueryInterface)(lpVtbl);
      v2[10].lpVtbl = (struct IBindStatusCallbackVtbl *)((char *)v2[10].lpVtbl + timeGetTime());
      v15[0] = 0;
      if ( v2[9].lpVtbl < (struct IBindStatusCallbackVtbl *)0x10 )
        v11 = (const CHAR *)&v2[4];
      else
        v11 = (const CHAR *)v2[4].lpVtbl;
      if ( URLDownloadToCacheFileA(nullptr, v11, v15, 0x104u, 0, v2) != 0 || strlen(v15) == 0 )
      {
        v13 = v2[2].lpVtbl;
        if ( v13 != nullptr )
          (*((void (**)(void))v13->QueryInterface + 2))();
      }
      else
      {
        v12 = v2[2].lpVtbl;
        if ( v12 != nullptr )
          (*((void (/*stdcall*/ **)(CHAR *))v12->QueryInterface + 1))(v15);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 36));
      sub_4F4440((int)(lpThreadParameter + 80), &i);
      LeaveCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 36));
    }
    else
    {
      Sleep(0x1F4u);
    }
    result = *((uint32_t *)lpThreadParameter + 1);
    v2 = nullptr;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F4970 sub_4F4970
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4F4970(int *this, int *a2)
{
  int v2; // esi
  unsigned int v3; // edx
  int *v4; // eax
  unsigned int result; // eax

  v2 = *(this + 1);
  if ( v2 != 0 )
    v3 = (*(this + 2) - v2) >> 2;
  else
    v3 = 0;
  if ( v2 == 0 || v3 >= (*(this + 3) - v2) >> 2 )
    return sub_4F44C0((int)this, *(this + 2), 1u, a2);
  v4 = (int *)*(this + 2);
  *v4 = *a2;
  result = (unsigned int)(v4 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4F49C0 sub_4F49C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4F49C0(char *lpParameter, uint16_t *Block)
{
  uint16_t *v3; // eax
  int v4; // eax
  int v5; // edi
  uint16_t *v6; // eax
  uint32_t *v7; // eax
  bool v8; // zf
  HANDLE v9; // ebx
  int v10; // eax
  unsigned int v11; // edi
  uint32_t *v12; // eax
  int v13; // ecx
  DWORD ThreadId; // [esp+4h] [ebp-14h] BYREF
  int v16; // [esp+8h] [ebp-10h] BYREF
  int v17; // [esp+14h] [ebp-4h]

  if ( *(uint32_t *)lpParameter == 1 )
    return 1;
  v3 = Block;
  if ( *Block == 0 || Block[1] == 0 )
    return 1;
  *((uint32_t *)lpParameter + 33) = *(uint32_t *)Block;
  v4 = *((uint32_t *)v3 + 1);
  *((uint32_t *)lpParameter + 34) = v4;
  if ( v4 == 0 )
    *((uint32_t *)lpParameter + 34) = 15000;
  InitializeCriticalSection((LPCRITICAL_SECTION)(lpParameter + 12));
  InitializeCriticalSection((LPCRITICAL_SECTION)(lpParameter + 36));
  v5 = 0;
  if ( *((uint16_t *)lpParameter + 66) != 0 )
  {
    do
    {
      v6 = operator new(0x2Cu);
      Block = v6;
      v17 = 0;
      if ( v6 != nullptr )
        v7 = sub_4F4210(v6, (int)lpParameter);
      else
        v7 = nullptr;
      v17 = -1;
      Block = v7;
      sub_4F4970((int *)lpParameter + 25, (int *)&Block);
      sub_4F4440((int)(lpParameter + 80), &Block);
      ++v5;
    }
    while ( v5 < *((uint16_t *)lpParameter + 66) );
  }
  v8 = *((uint16_t *)lpParameter + 67) == 0;
  Block = nullptr;
  if ( v8 )
  {
LABEL_21:
    *(uint32_t *)lpParameter = 1;
    return 0;
  }
  else
  {
    while ( 1 )
    {
      v9 = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)sub_4F4800, lpParameter, 0, &ThreadId);
      v16 = (int)v9;
      if ( v9 == nullptr )
        return 1;
      v10 = *((uint32_t *)lpParameter + 30);
      if ( v10 != 0 )
        v11 = (*((uint32_t *)lpParameter + 31) - v10) >> 2;
      else
        v11 = 0;
      if ( v10 != 0 && v11 < (*((uint32_t *)lpParameter + 32) - v10) >> 2 )
      {
        v12 = *((uint32_t **)lpParameter + 31);
        *v12 = v9;
        *((uint32_t *)lpParameter + 31) = v12 + 1;
      }
      else
      {
        sub_4F44C0((int)(lpParameter + 116), *((uint32_t *)lpParameter + 31), 1u, &v16);
      }
      v13 = *((uint16_t *)lpParameter + 67);
      Block = (uint16_t *)((char *)Block + 1);
      if ( (int)Block >= v13 )
        goto LABEL_21;
    }
  }
}



// ------------------------------------------------------------
// 0x4F4B60 sub_4F4B60
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F4B60(uint32_t *this)
{
  uint32_t *v2; // edi
  int v3; // edx
  int v4; // edx

  v2 = this + 1;
  sub_41A630((unsigned int)(this + 1));
  *v2 = &vftbl_clong;
  sub_41A630((unsigned int)this + 18);
  *(uint32_t *)((char *)this + 18) = &vftbl_clong;
  *this = 4;
  sub_41A590((unsigned int)v2, v3, 0);
  sub_41A590((unsigned int)this + 18, v4, 0);
  return this;
}



// ------------------------------------------------------------
// 0x4F4BE0 sub_4F4BE0
// ------------------------------------------------------------
char /*cdecl*/ sub_4F4BE0(const char *a1, int a2, int a3)
{
  int *v4; // esi
  int *v5; // esi
  int i; // edi
  char v7[4]; // [esp+0h] [ebp-2Ch] BYREF
  void *Block; // [esp+4h] [ebp-28h]
  int v9; // [esp+14h] [ebp-18h]
  unsigned int v10; // [esp+18h] [ebp-14h]
  int v11; // [esp+1Ch] [ebp-10h]
  int v12; // [esp+28h] [ebp-4h]

  v11 = dword_796E50;
  strcpy(byte_9B6A60, a1);
  if ( byte_9B6A5F[strlen(byte_9B6A60)] != 92 && byte_9B6A5F[strlen(byte_9B6A60)] != 47 )
    *(uint16_t *)&byte_9B6A60[strlen(byte_9B6A60)] = 92;
  if ( (uint8_t)sub_443C40((int)&unk_9B6C6C, (char)byte_9B6A60, a2) == 0
    || (uint8_t)sub_442A10((char)byte_9B6A60, a3) == 0 )
  {
    return 0;
  }
  memset(&unk_9B0C90, 0, 0x2EE0u);
  v10 = 15;
  v9 = 0;
  LOBYTE(Block) = 0;
  v12 = 0;
  sub_443430(v7);
  v4 = &dword_9B6A50;
  do
    *v4++ = sub_4423D0(nullptr);
  while ( (int)v4 < (int)&unk_9B6A5C );
  v5 = (int *)&unk_9B0C90;
  do
  {
    if ( (uint8_t)sub_443430(v7) == 0 )
      break;
    for ( i = 100; i != 0; --i )
      *v5++ = sub_4423D0(nullptr);
  }
  while ( (int)v5 < (int)dword_9B3B70 );
  if ( v10 >= 0x10 )
    j__free(Block);
  return 1;
}



// ------------------------------------------------------------
// 0x4F4D50 sub_4F4D50
// ------------------------------------------------------------
char /*cdecl*/ sub_4F4D50(const char *a1, int a2, int a3)
{
  int *v4; // esi
  int i; // edi
  uint8_t v6[4]; // [esp+0h] [ebp-2Ch] BYREF
  void *Block; // [esp+4h] [ebp-28h]
  int v8; // [esp+14h] [ebp-18h]
  unsigned int v9; // [esp+18h] [ebp-14h]
  int v10; // [esp+1Ch] [ebp-10h]
  int v11; // [esp+28h] [ebp-4h]

  v10 = dword_796E50;
  strcpy(byte_9B6B60, a1);
  if ( byte_9B6B5F[strlen(byte_9B6B60)] != 92 && byte_9B6B5F[strlen(byte_9B6B60)] != 47 )
    *(uint16_t *)&byte_9B6B60[strlen(byte_9B6B60)] = 92;
  if ( (uint8_t)sub_443C40((int)&unk_9B6C60, (char)byte_9B6B60, a2) == 0
    || (uint8_t)sub_442A10((char)byte_9B6B60, a3) == 0 )
  {
    return 0;
  }
  memset(dword_9B3B70, 0, sizeof(dword_9B3B70));
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  v11 = 0;
  v4 = dword_9B3B70;
  do
  {
    if ( (uint8_t)sub_443430(v6) == 0 )
      break;
    for ( i = 100; i != 0; --i )
      *v4++ = sub_4423D0(nullptr);
  }
  while ( (int)v4 < (int)&dword_9B6A50 );
  if ( v9 >= 0x10 )
    j__free(Block);
  return 1;
}



// ------------------------------------------------------------
// 0x4F4E90 sub_4F4E90
// ------------------------------------------------------------
int /*cdecl*/ sub_4F4E90(int a1, int a2, int a3)
{
  int v3; // ebx
  unsigned int v4; // edi
  unsigned int v5; // esi
  int v6; // ecx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // edx

  v3 = a2;
  if ( a1 != a2 )
  {
    v4 = a3 + 38;
    v5 = a2 + 38;
    do
    {
      v6 = *(uint32_t *)(v3 - 80);
      v3 -= 80;
      v5 -= 80;
      *(uint32_t *)(a3 - 80) = v6;
      v4 -= 80;
      a3 -= 80;
      *(uint8_t *)(v4 - 34) = *(uint8_t *)(v5 - 34);
      v7 = sub_41A5E0(v5 - 33);
      sub_41A590(v4 - 33, v8, v7);
      *(uint32_t *)(v4 - 18) = *(uint32_t *)(v5 - 18);
      v9 = sub_41A5E0(v5 - 14);
      sub_41A590(v4 - 14, v10, v9);
      v11 = sub_41A5E0(v5);
      sub_41A590(v4, v12, v11);
      sub_4014D0((std::_String_base *)(v4 + 14), v5 + 14, 0, -1);
    }
    while ( v3 != a1 );
  }
  return a3;
}



// ------------------------------------------------------------
// 0x4F4F30 sub_4F4F30
// ------------------------------------------------------------
int /*thiscall*/ sub_4F4F30(char *this)
{
  void **v2; // edi
  int i; // ebx
  void **v4; // edi
  int j; // ebx
  void **v6; // edi
  int result; // eax
  void **k; // ebx
  void **v9; // edi
  void **m; // ebx

  *(uint32_t *)this = 0;
  sub_41BFE0((void **)this + 1, szPassword);
  sub_41BFE0((void **)this + 2, szPassword);
  sub_41BFE0((void **)this + 3, szPassword);
  v2 = (void **)(this + 16);
  for ( i = 2; i != 0; --i )
    sub_41BFE0(v2++, szPassword);
  sub_41BFE0((void **)this + 6, szPassword);
  sub_41BFE0((void **)this + 7, szPassword);
  sub_41BFE0((void **)this + 8, szPassword);
  sub_41BFE0((void **)this + 9, szPassword);
  sub_41BFE0((void **)this + 10, szPassword);
  v4 = (void **)(this + 60);
  for ( j = 4; j != 0; --j )
  {
    sub_41BFE0(v4 - 4, szPassword);
    sub_41BFE0(v4++, szPassword);
  }
  sub_41BFE0((void **)this + 19, szPassword);
  sub_41BFE0((void **)this + 20, szPassword);
  sub_41BFE0((void **)this + 21, szPassword);
  sub_41BFE0((void **)this + 22, szPassword);
  v6 = *((void ***)this + 24);
  result = 0;
  if ( v6 != nullptr )
  {
    for ( k = *((void ***)this + 25); v6 != k; ++v6 )
      sub_41B010(v6);
    j__free(*((void **)this + 24));
    result = 0;
  }
  *((uint32_t *)this + 24) = 0;
  *((uint32_t *)this + 25) = 0;
  *((uint32_t *)this + 26) = 0;
  v9 = *((void ***)this + 28);
  if ( v9 != nullptr )
  {
    for ( m = *((void ***)this + 29); v9 != m; ++v9 )
      sub_41B010(v9);
    j__free(*((void **)this + 28));
    result = 0;
  }
  *((uint32_t *)this + 28) = 0;
  *((uint32_t *)this + 29) = 0;
  *((uint32_t *)this + 30) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4F5090 sub_4F5090
// ------------------------------------------------------------
void /*thiscall*/ sub_4F5090(int this)
{
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  if ( *(uint32_t *)(this + 20) != 0 )
    j__free(*(void **)(this + 20));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  if ( *(uint32_t *)(this + 36) != 0 )
    j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint8_t *)(this + 48) = 0;
}



// ------------------------------------------------------------
// 0x4F50F0 sub_4F50F0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F50F0(uint32_t *a1, uint32_t *a2, int a3)
{
  uint32_t *result; // eax
  uint32_t *v4; // ebx
  unsigned int v5; // esi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx

  result = a2;
  v4 = a1;
  if ( a1 != a2 )
  {
    v5 = (unsigned int)a1 + 38;
    do
    {
      *v4 = *(uint32_t *)a3;
      *(uint8_t *)(v5 - 34) = *(uint8_t *)(a3 + 4);
      v6 = sub_41A5E0(a3 + 5);
      sub_41A590(v5 - 33, v7, v6);
      *(uint32_t *)(v5 - 18) = *(uint32_t *)(a3 + 20);
      v8 = sub_41A5E0(a3 + 24);
      sub_41A590(v5 - 14, v9, v8);
      v10 = sub_41A5E0(a3 + 38);
      sub_41A590(v5, v11, v10);
      sub_4014D0((std::_String_base *)(v5 + 14), a3 + 52, 0, -1);
      result = a2;
      v4 += 20;
      v5 += 80;
    }
    while ( v4 != a2 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F5170 sub_4F5170
// ------------------------------------------------------------
int /*cdecl*/ sub_4F5170(int a1, int a2, int a3)
{
  return sub_4F4E90(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4F5190 sub_4F5190
// ------------------------------------------------------------
int /*cdecl*/ sub_4F5190(int a1, int a2, int a3)
{
  int v3; // esi
  int result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v7 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != 0 )
      result = sub_4EBCC0(a3);
    --a2;
    v3 += 80;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F5220 sub_4F5220
// ------------------------------------------------------------
int /*thiscall*/ sub_4F5220(int this)
{
  uint32_t *v2; // edi

  v2 = (uint32_t *)(this + 5);
  sub_41A630(this + 5);
  *v2 = &vftbl_cfloat;
  sub_4F4B60((uint32_t *)(this + 20));
  *(uint32_t *)(this + 76) = 15;
  *(uint32_t *)(this + 72) = 0;
  *(uint8_t *)(this + 56) = 0;
  sub_4EBD50(this);
  return this;
}



// ------------------------------------------------------------
// 0x4F5290 sub_4F5290
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F5290(uint32_t *this, uint32_t *a2)
{
  *this = *a2;
  *(this + 1) = 0;
  sub_41B0D0(a2 + 1);
  *(this + 2) = 0;
  sub_41B0D0(a2 + 2);
  *(this + 3) = 0;
  sub_41B0D0(a2 + 3);
  `eh vector copy constructor iterator'(
    this + 4,
    a2 + 4,
    4u,
    2,
    (void (/*thiscall*/ *)(void *, void *))sub_41C170,
    sub_401060);
  *(this + 6) = 0;
  sub_41B0D0(a2 + 6);
  *(this + 7) = 0;
  sub_41B0D0(a2 + 7);
  *(this + 8) = 0;
  sub_41B0D0(a2 + 8);
  *(this + 9) = 0;
  sub_41B0D0(a2 + 9);
  *(this + 10) = 0;
  sub_41B0D0(a2 + 10);
  `eh vector copy constructor iterator'(
    this + 11,
    a2 + 11,
    4u,
    4,
    (void (/*thiscall*/ *)(void *, void *))sub_41C170,
    sub_401060);
  `eh vector copy constructor iterator'(
    this + 15,
    a2 + 15,
    4u,
    4,
    (void (/*thiscall*/ *)(void *, void *))sub_41C170,
    sub_401060);
  *(this + 19) = 0;
  sub_41B0D0(a2 + 19);
  *(this + 20) = 0;
  sub_41B0D0(a2 + 20);
  *(this + 21) = 0;
  sub_41B0D0(a2 + 21);
  *(this + 22) = 0;
  sub_41B0D0(a2 + 22);
  sub_4B3600(a2 + 23);
  sub_4B3600(a2 + 27);
  return this;
}



// ------------------------------------------------------------
// 0x4F5450 sub_4F5450
// ------------------------------------------------------------
char */*thiscall*/ sub_4F5450(char *this, char *a2)
{
  int v4; // eax
  uint32_t *v5; // ebx
  uint32_t *v6; // ebx
  uint32_t *v7; // ebx
  int v9; // [esp+Ch] [ebp-4h]
  int i; // [esp+Ch] [ebp-4h]
  int j; // [esp+Ch] [ebp-4h]
  int v12; // [esp+18h] [ebp+8h]

  *(uint32_t *)this = *(uint32_t *)a2;
  sub_41B0D0(a2 + 4);
  sub_41B0D0(a2 + 8);
  sub_41B0D0(a2 + 12);
  v4 = a2 - this;
  v5 = this + 16;
  v12 = a2 - this;
  v9 = 2;
  while ( 1 )
  {
    sub_41B0D0((char *)v5++ + v4);
    if ( --v9 == 0 )
      break;
    v4 = v12;
  }
  sub_41B0D0(a2 + 24);
  sub_41B0D0(a2 + 28);
  sub_41B0D0(a2 + 32);
  sub_41B0D0(a2 + 36);
  sub_41B0D0(a2 + 40);
  v6 = this + 44;
  for ( i = 4; i != 0; --i )
    sub_41B0D0((char *)v6++ + v12);
  v7 = this + 60;
  for ( j = 4; j != 0; --j )
    sub_41B0D0((char *)v7++ + v12);
  sub_41B0D0(a2 + 76);
  sub_41B0D0(a2 + 80);
  sub_41B0D0(a2 + 84);
  sub_41B0D0(a2 + 88);
  sub_41DC80(a2 + 92);
  sub_41DC80(a2 + 108);
  return this;
}



// ------------------------------------------------------------
// 0x4F55A0 sub_4F55A0
// ------------------------------------------------------------
char */*cdecl*/ sub_4F55A0(char *a1, char *a2, char *a3)
{
  char *v3; // esi
  char *v4; // edi

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 124;
    v4 -= 124;
    sub_4F5450(v4, v3);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x4F55E0 sub_4F55E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4F55E0(int this)
{
  void **v2; // ecx

  v2 = (void **)(this + 4);
  *v2 = nullptr;
  sub_41BFE0(v2, szPassword);
  *(uint32_t *)(this + 8) = 0;
  sub_41BFE0((void **)(this + 8), szPassword);
  *(uint32_t *)(this + 12) = 0;
  sub_41BFE0((void **)(this + 12), szPassword);
  `eh vector constructor iterator'((void *)(this + 16), 4u, 2, sub_432D20, sub_401060);
  *(uint32_t *)(this + 24) = 0;
  sub_41BFE0((void **)(this + 24), szPassword);
  *(uint32_t *)(this + 28) = 0;
  sub_41BFE0((void **)(this + 28), szPassword);
  *(uint32_t *)(this + 32) = 0;
  sub_41BFE0((void **)(this + 32), szPassword);
  *(uint32_t *)(this + 36) = 0;
  sub_41BFE0((void **)(this + 36), szPassword);
  *(uint32_t *)(this + 40) = 0;
  sub_41BFE0((void **)(this + 40), szPassword);
  `eh vector constructor iterator'((void *)(this + 44), 4u, 4, sub_432D20, sub_401060);
  `eh vector constructor iterator'((void *)(this + 60), 4u, 4, sub_432D20, sub_401060);
  *(uint32_t *)(this + 76) = 0;
  sub_41BFE0((void **)(this + 76), szPassword);
  *(uint32_t *)(this + 80) = 0;
  sub_41BFE0((void **)(this + 80), szPassword);
  *(uint32_t *)(this + 84) = 0;
  sub_41BFE0((void **)(this + 84), szPassword);
  *(uint32_t *)(this + 88) = 0;
  sub_41BFE0((void **)(this + 88), szPassword);
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  sub_4F4F30((char *)this);
  return this;
}



// ------------------------------------------------------------
// 0x4F5770 sub_4F5770
// ------------------------------------------------------------
int /*stdcall*/ sub_4F5770(int a1, int a2, int a3)
{
  sub_4F5190(a1, a2, a3);
  return a1 + 80 * a2;
}



// ------------------------------------------------------------
// 0x4F57A0 sub_4F57A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4F57A0(int this, int a2, unsigned int a3, int a4)
{
  int v5; // ebx
  unsigned int v6; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  char *v12; // ebx
  int v13; // eax
  unsigned int v14; // edi
  int v15; // eax
  char *v16; // ecx
  int v18; // edi
  int v20; // [esp-18h] [ebp-94h]
  int v21; // [esp-10h] [ebp-8Ch]
  int v22; // [esp-Ch] [ebp-88h]
  unsigned int v23; // [esp-8h] [ebp-84h]
  int v24; // [esp+0h] [ebp-7Ch] BYREF
  void *Block; // [esp+Ch] [ebp-70h]
  int v26; // [esp+10h] [ebp-6Ch]
  char *v27; // [esp+14h] [ebp-68h]
  char v28[80]; // [esp+18h] [ebp-64h] BYREF
  int v29; // [esp+68h] [ebp-14h]
  int *v30; // [esp+6Ch] [ebp-10h]
  int v31; // [esp+78h] [ebp-4h]
  int v32; // [esp+84h] [ebp+8h]
  int v33; // [esp+88h] [ebp+Ch]
  char *v34; // [esp+8Ch] [ebp+10h]

  v29 = dword_796E50;
  v30 = &v24;
  v26 = this;
  sub_4EBCC0(v28, a4);
  v5 = *(uint32_t *)(this + 4);
  v6 = 0;
  v31 = 0;
  if ( v5 != 0 )
    v6 = (*(uint32_t *)(this + 12) - v5) / 80;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(uint32_t *)(this + 8) - v5) / 80;
    else
      v8 = 0;
    if ( 53687091 - v8 < a3 )
      sub_434730(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) / 80;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = *(char **)(this + 8);
      v34 = v16;
      if ( (int)&v16[-a2] / 80 >= a3 )
      {
        v32 = (int)&v16[-80 * a3];
        *(uint32_t *)(this + 8) = sub_4ED730(v32, (int)v16, v16);
        sub_4F5170(a2, v32, v34);
        sub_4F50F0(a2, a2 + 80 * a3, v28);
      }
      else
      {
        sub_4ED730(a2, (int)v16, (char *)(a2 + 80 * a3));
        v23 = a3 - (*(uint32_t *)(this + 8) - a2) / 80;
        v22 = *(uint32_t *)(this + 8);
        LOBYTE(v31) = 3;
        sub_4F5770(v22, v23, v28);
        v18 = 80 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v18;
        v31 = 0;
        sub_4F50F0(a2, v18 - 80 * a3, v28);
      }
    }
    else
    {
      if ( 53687091 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) / 80;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_4EAF60((int *)this);
      v33 = 80 * v10;
      v12 = (char *)operator new(80 * v10);
      v20 = *(uint32_t *)(this + 4);
      Block = v12;
      v27 = v12;
      LOBYTE(v31) = 1;
      v27 = sub_4ED730(v20, a2, v12);
      sub_4F5190(v27, a3, v28);
      v21 = *(uint32_t *)(this + 8);
      v27 += 80 * a3;
      sub_4ED730(a2, v21, v27);
      v13 = *(uint32_t *)(this + 4);
      v31 = 0;
      if ( v13 != 0 )
        v13 = (*(uint32_t *)(this + 8) - v13) / 80;
      v14 = v13 + a3;
      v15 = *(uint32_t *)(this + 4);
      if ( v15 != 0 )
      {
        sub_435890(v15, *(uint32_t *)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &v12[v33];
      *(uint32_t *)(this + 8) = &v12[80 * v14];
      *(uint32_t *)(this + 4) = v12;
    }
  }
  v31 = -1;
  return sub_433D10(v28);
}


// ------------------------------------------------------------
// 0x4F5AB0 sub_4F5AB0
// ------------------------------------------------------------
char */*cdecl*/ sub_4F5AB0(char *a1, char *a2, char *a3)
{
  char *i; // esi
  char *result; // eax

  for ( i = a1; i != a2; i += 124 )
    result = sub_4F5450(i, a3);
  return result;
}



// ------------------------------------------------------------
// 0x4F5AE0 sub_4F5AE0
// ------------------------------------------------------------
char */*cdecl*/ sub_4F5AE0(char *a1, char *a2, char *a3)
{
  return sub_4F55A0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4F5B00 sub_4F5B00
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F5B00(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
      sub_4F5290(v3, a1);
    v3 += 31;
    LOBYTE(v7) = 0;
    a1 += 31;
  }
  return v3;
}



// ============================================================
// §F 0x4F5B90-0x4F7C60 ★ 物品定义解析器族
// ============================================================

// ------------------------------------------------------------
// 0x4F5B90 sub_4F5B90 —— ★ 可堆叠物品(stackable)定义解析器（39 标签）
//   标签族：文本 [name]/[name2]/[explain]/[flavor text]；品级 [grade]（+20）；
//   绑定 [attach type] 子枚举 [free]=0/[trade]=1/[trade delete]=2/[sealing]=3（+24）；
//   [creation rate]（+28）/[rarity]（+32）/[weight]（+56）；
//   职业 [usable job]（子串查表 → 每职业一字节 a1+60 起；全职业 4 → a1+60=0x01010101 且 +152=1）；
//   [stackable type]；使用限制 [minimum level]（+64）/[cool time]（+68）/[cooltime group]（+72）/
//   [party cooltime]（+76）；资源 [icon]（+80）/[field image]（+88）；
//   价值 [price]（+36）/[value]（+52）/[finish point price]（+40）/[cash]（+44）/[medal]（+48）；
//   音效 [move wav]（+104）/[use wav]（+116）；[int data]（+120 表）/[string data]（+136 表）；
//   [applying range]（+96）；物品大类枚举子串 [waste]/[material]/[recipe]/[throw]/[set]/[legacy]/
//   [quest]/[etc]。
// ------------------------------------------------------------
char /*cdecl*/ sub_4F5B90(int a1, int ArgList)
{
  const char *v2; // edi
  char result; // al
  int v4; // eax
  int v5; // eax
  const char *p_Block; // eax
  int v7; // edx
  void **v8[6]; // [esp-1Ch] [ebp-60h] BYREF
  void **j; // [esp-4h] [ebp-48h]
  void ***k; // [esp+Ch] [ebp-38h] BYREF
  char i; // [esp+13h] [ebp-31h] BYREF
  void *v12; // [esp+14h] [ebp-30h] BYREF
  int v13; // [esp+18h] [ebp-2Ch] BYREF
  void *Block; // [esp+1Ch] [ebp-28h] BYREF
  int v15; // [esp+2Ch] [ebp-18h]
  unsigned int v16; // [esp+30h] [ebp-14h]
  int v17; // [esp+34h] [ebp-10h]
  int v18; // [esp+40h] [ebp-4h]

  v2 = (const char *)ArgList;
  v17 = dword_796E50;
  result = sub_442A10((char)&unk_9B6B60, ArgList);
  if ( result != 0 )
  {
    sub_4CF480(a1);
    v16 = 15;
    v15 = 0;
    LOBYTE(Block) = 0;
    v18 = 0;
    v12 = nullptr;
    sub_41BFE0(&v12, szPassword);
    LOBYTE(v18) = 1;
    for ( i = 0; (uint8_t)sub_443430(&v13) != 0; v2 = (const char *)ArgList )
    {
      if ( (uint8_t)sub_442BC0(&v13) != 0 )
        off_77F3FC((char *)&byte_6FA9F8, v2);
      if ( sub_40BF00((std::_String_base *)&v13, 0, v15, "[name]", 6u) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)&v13, 0, v15, "[name2]", 7u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)&v13, 0, v15, "[explain]", 9u) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)&v13, 0, v15, "[flavor text]", 0xDu) != 0 )
            {
              if ( (uint8_t)sub_423300(&v13, "[grade]") != 0 )
              {
                *(uint32_t *)(a1 + 20) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[attach type]") != 0 )
              {
                j = &v12;
                sub_442E10();
                if ( sub_43BCF0(&v12, "[free]") )
                {
                  *(uint32_t *)(a1 + 24) = 0;
                }
                else if ( sub_43BCF0(&v12, "[trade]") )
                {
                  *(uint32_t *)(a1 + 24) = 1;
                }
                else if ( sub_43BCF0(&v12, "[trade delete]") )
                {
                  *(uint32_t *)(a1 + 24) = 2;
                }
                else if ( sub_43BCF0(&v12, "[sealing]") )
                {
                  *(uint32_t *)(a1 + 24) = 3;
                }
              }
              else if ( (uint8_t)sub_423300(&v13, "[creation rate]") != 0 )
              {
                *(uint32_t *)(a1 + 28) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[rarity]") != 0 )
              {
                *(uint32_t *)(a1 + 32) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[weight]") != 0 )
              {
                *(uint32_t *)(a1 + 56) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[usable job]") != 0 )
              {
                for ( j = &v12; sub_442E10() != 0; j = &v12 )
                {
                  v4 = sub_41ACF0(&v12);
                  v5 = sub_4426A0(v4);
                  if ( v5 == 4 )
                  {
                    *(uint32_t *)(a1 + 60) = 16843009;
                    *(uint8_t *)(a1 + 152) = 1;
                  }
                  else
                  {
                    *(uint8_t *)(a1 + v5 + 60) = 1;
                  }
                }
              }
              else if ( (uint8_t)sub_423300(&v13, "[stackable type]") != 0 )
              {
                j = &v12;
                sub_442E10();
                if ( sub_43BCF0(&v12, "[waste]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 100) = 0;
                  *(uint32_t *)(a1 + 156) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v12, "[material]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 100) = 1;
                  *(uint32_t *)(a1 + 156) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v12, "[recipe]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 100) = 2;
                  *(uint32_t *)(a1 + 156) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v12, "[throw]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 100) = 3;
                  *(uint32_t *)(a1 + 156) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v12, "[set]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 100) = 4;
                  *(uint32_t *)(a1 + 156) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v12, "[legacy]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 100) = 5;
                  *(uint32_t *)(a1 + 156) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v12, "[quest]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 100) = 6;
                  *(uint32_t *)(a1 + 156) = sub_4423D0(j);
                }
                else
                {
                  if ( sub_43BCF0(&v12, "[etc]") )
                    *(uint32_t *)(a1 + 100) = 7;
                  *(uint32_t *)(a1 + 156) = sub_4423D0(nullptr);
                }
              }
              else if ( (uint8_t)sub_423300(&v13, "[minimum level]") != 0 )
              {
                *(uint32_t *)(a1 + 64) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[cool time]") != 0 )
              {
                *(uint32_t *)(a1 + 68) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[cooltime group]") != 0 )
              {
                *(uint32_t *)(a1 + 72) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[party cooltime]") != 0 )
              {
                *(uint8_t *)(a1 + 76) = sub_4423D0(nullptr) != 0;
              }
              else if ( (uint8_t)sub_423300(&v13, "[icon]") != 0 )
              {
                j = (void **)(a1 + 80);
                sub_442E10();
                *(uint32_t *)(a1 + 84) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[field image]") != 0 )
              {
                j = (void **)(a1 + 88);
                sub_442E10();
                *(uint32_t *)(a1 + 92) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[price]") != 0 )
              {
                *(uint32_t *)(a1 + 36) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[value]") != 0 )
              {
                *(uint32_t *)(a1 + 52) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[finish point price]") != 0 )
              {
                *(uint32_t *)(a1 + 40) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[cash]") != 0 )
              {
                *(uint32_t *)(a1 + 44) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[medal]") != 0 )
              {
                *(uint32_t *)(a1 + 48) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v13, "[move wav]") != 0 )
              {
                j = (void **)(a1 + 104);
                sub_442E10();
              }
              else if ( (uint8_t)sub_423300(&v13, "[use wav]") != 0 )
              {
                j = (void **)(a1 + 116);
                sub_442E10();
              }
              else if ( (uint8_t)sub_423300(&v13, "[int data]") != 0 )
              {
                sub_5E5260((void **)(a1 + 120));
                for ( k = (void ***)sub_4423D0(&i); i != 0; k = (void ***)sub_4423D0(&i) )
                  sub_431230(a1 + 120, &k);
              }
              else if ( (uint8_t)sub_423300(&v13, "[string data]") != 0 )
              {
                sub_4017E0(a1 + 136);
                for ( j = &v12; sub_442E10() != 0; j = &v12 )
                  sub_420BB0(&v12);
              }
              else if ( (uint8_t)sub_423300(&v13, "[applying range]") != 0 )
              {
                *(uint32_t *)(a1 + 96) = sub_4423D0(nullptr);
              }
              else
              {
                k = v8;
                sub_401690(&v13);
                if ( sub_442C80((char)v8[0], v8[1], (int)v8[2], (int)v8[3], (int)v8[4], (int)v8[5], (unsigned int)j) == 0 )
                {
                  p_Block = (const char *)Block;
                  if ( v16 < 0x10 )
                    p_Block = (const char *)&Block;
                  off_77F3FC("SCRIPT TAG ERROR! [%s] %s", v2, p_Block);
                }
              }
            }
            else
            {
              j = (void **)(a1 + 16);
              sub_442E10();
            }
          }
          else
          {
            j = (void **)(a1 + 12);
            sub_442E10();
          }
        }
        else
        {
          j = (void **)(a1 + 8);
          sub_442E10();
        }
      }
      else
      {
        j = (void **)(a1 + 4);
        sub_442E10();
      }
    }
    if ( *(uint32_t *)(a1 + 52) == -1 )
      *(uint32_t *)(a1 + 52) = *(uint32_t *)(a1 + 36);
    v7 = 10 * *(uint32_t *)(a1 + 44) + *(uint32_t *)(a1 + 36);
    j = (void **)v2;
    *(uint32_t *)(a1 + 36) = v7;
    *(uint32_t *)(a1 + 44) = 0;
    *(uint32_t *)a1 = sub_4A2F80(j);
    LOBYTE(v18) = 0;
    sub_41B010(&v12);
    if ( v16 >= 0x10 )
      j__free(Block);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4F6390 sub_4F6390
// ------------------------------------------------------------
char /*cdecl*/ sub_4F6390(uint32_t *a1, int a2)
{
  uint32_t *v2; // ebx
  int *v3; // esi
  int v4; // eax
  int *v5; // esi
  int v6; // edx
  int v7; // ecx
  unsigned int v8; // edx
  int v9; // edi
  int v10; // eax
  int *v11; // esi
  int v12; // eax
  int v13; // ecx
  unsigned int v14; // edx
  int v15; // ebx
  int v16; // eax
  int *v17; // esi
  uint32_t *v18; // edi
  int v19; // edx
  int v20; // eax
  int v21; // ecx
  unsigned int v22; // edx
  int v23; // ebx
  int v25; // [esp+Ch] [ebp-Ch] BYREF
  int v26; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  v2 = a1;
  sub_4F5090(a1);
  v3 = *(int **)(a2 + 4);
  v4 = *v3;
  v5 = v3 + 1;
  if ( v4 > 0 )
  {
    for ( i = v4; i != 0; --i )
    {
      v6 = v5[1];
      v25 = *v5;
      v7 = a1[1];
      v5 += 2;
      v26 = v6;
      if ( v7 != 0 )
        v8 = (a1[2] - v7) >> 3;
      else
        v8 = 0;
      if ( v7 != 0 && v8 < (a1[3] - v7) >> 3 )
      {
        v9 = a1[2];
        sub_63A7C0(v9, 1, &v25);
        a1[2] = v9 + 8;
      }
      else
      {
        sub_473A80(a1[2], 1, &v25);
      }
    }
  }
  v10 = *v5;
  v11 = v5 + 1;
  if ( v10 > 0 )
  {
    for ( i = v10; i != 0; --i )
    {
      v12 = *v11;
      v26 = v11[1];
      v13 = a1[5];
      v11 += 2;
      v25 = v12;
      if ( v13 != 0 )
        v14 = (a1[6] - v13) >> 3;
      else
        v14 = 0;
      if ( v13 != 0 && v14 < (a1[7] - v13) >> 3 )
      {
        v15 = a1[6];
        sub_63A7C0(v15, 1, &v25);
        a1[6] = v15 + 8;
        v2 = a1;
      }
      else
      {
        sub_473A80(a1[6], 1, &v25);
      }
    }
  }
  v16 = *v11;
  v17 = v11 + 1;
  if ( v16 > 0 )
  {
    v18 = v2 + 8;
    for ( i = v16; i != 0; --i )
    {
      v19 = *v17;
      v20 = v17[1];
      v21 = v18[1];
      v17 += 2;
      v25 = v19;
      v26 = v20;
      if ( v21 != 0 )
        v22 = (v18[2] - v21) >> 3;
      else
        v22 = 0;
      if ( v21 != 0 && v22 < (v18[3] - v21) >> 3 )
      {
        v23 = v18[2];
        LOBYTE(v16) = sub_63A7C0(v23, 1, &v25);
        v18[2] = v23 + 8;
        v2 = a1;
      }
      else
      {
        LOBYTE(v16) = sub_473A80(v18[2], 1, &v25);
      }
    }
  }
  if ( v17 != *(int **)(a2 + 8) )
  {
    LOBYTE(v16) = *v17 == 1;
    *((uint8_t *)v2 + 48) = v16;
  }
  return v16;
}


// ------------------------------------------------------------
// 0x4F6540 sub_4F6540
// ------------------------------------------------------------
int */*cdecl*/ sub_4F6540(int a1, int a2)
{
  uint32_t *v2; // edi
  int *result; // eax
  int *i; // edi
  int v5; // edx
  int *v6; // edi
  int v7; // eax
  int v8; // ecx
  unsigned int v9; // edx
  int v10; // ebx
  int v11; // [esp+Ch] [ebp-8h] BYREF
  int v12; // [esp+10h] [ebp-4h]

  *(uint32_t *)a1 = 0;
  if ( *(uint32_t *)(a1 + 8) != 0 )
    j__free(*(void **)(a1 + 8));
  *(uint32_t *)(a1 + 8) = 0;
  *(uint32_t *)(a1 + 12) = 0;
  *(uint32_t *)(a1 + 16) = 0;
  v2 = *(uint32_t **)(a2 + 4);
  *(uint32_t *)a1 = *v2;
  result = *(int **)(a2 + 8);
  for ( i = v2 + 1; i != result; result = *(int **)(a2 + 8) )
  {
    v5 = *i;
    v6 = i + 1;
    v12 = 0;
    v11 = v5;
    if ( v6 == result )
      break;
    v7 = *v6;
    v8 = *(uint32_t *)(a1 + 8);
    i = v6 + 1;
    v12 = v7;
    v9 = v8 != 0 ? (*(uint32_t *)(a1 + 12) - v8) >> 3 : 0;
    if ( v8 != 0 && v9 < (*(uint32_t *)(a1 + 16) - v8) >> 3 )
    {
      v10 = *(uint32_t *)(a1 + 12);
      sub_63A7C0(v10, 1, &v11);
      *(uint32_t *)(a1 + 12) = v10 + 8;
    }
    else
    {
      sub_473A80(*(uint32_t *)(a1 + 12), 1, &v11);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F6600 sub_4F6600
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F6600(int *this, uint32_t *a2, uint32_t *a3, int a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 80 != 0 )
    v6 = ((int)a3 - v5) / 80;
  else
    v6 = 0;
  sub_4F57A0(this, a3, 1u, a4);
  *a2 = *(this + 1) + 80 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4F6670 sub_4F6670
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F6670(uint32_t *a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v7 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
      result = sub_4F5290(v3, a3);
    --a2;
    v3 += 31;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F6700 sub_4F6700
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F6700(int *this, int a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  uint32_t *result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 80;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) / 80 )
    return sub_4F6600(this, &a2, (uint32_t *)*(this + 2), a2);
  v5 = *(this + 2);
  result = (uint32_t *)sub_4F5190(v5, 1, a2);
  *(this + 2) = v5 + 80;
  return result;
}



// ------------------------------------------------------------
// 0x4F6790 sub_4F6790 —— ★★ 属性解析器（装备/状态百分比解析器；80 标签；研究 20 §12/§20-23 的锚点）
//   a1 = 目标对象（装备/技能/职业数据块），a2 = 当前行字符串，ArgList = 文件路径（报错用）。
//   【研究 20 §12 定位】"属性解析器 sub_509C90（技能/属性块通用）的固定字段对" —— 本函数是
//   装备侧的同族实现；【研究 20 §20-23 更正】实为"装备/状态百分比解析器"，[stuck] 与
//   [hit recovery] 在此 **三层并存**（整型描述符路径 / 浮点路径 / 属性名路径）。
//
//   两条属性写路径（研究 20 §12 定案）：
//     - 浮点路径：sub_442480 读 float → sub_432CF0 写入（LABEL_125 分支）
//       —— 例：[stuck]/[physical critical hit]/[magical critical hit]/[human damage rate]/
//       [fort damage rate] 等"攻击定义里的浮点属性"
//     - 整型描述符路径：sub_4423D0 读 int → sub_41C150 写入（LABEL_115 分支）
//       —— 例：[hit recovery]/[stuck resistance]/抗性族/速度族等"通用整型描述符"
//
//   标签族（80 个，分类）：
//   基础属性 [HP MAX]/[MP MAX]/[physical attack]/[physical defense]/[magical attack]/[magical defense]
//   装备属性 [equipment physical/magical attack/defense]（4）
//   绝对量 [physical/magical absolute damage/defense]、[physical/magical damage reduce]
//   元素抗性 [fire/water/dark/light resistance]、[all elemental resistance]
//   状态抗性 [slow/freeze/poison/stun/curse/blind/lightning/stone/sleep/burn/deadlystrike/bleeding/
//           all activestatus/piercing/stuck/confuse/hold resistance]（17 —— 与 17 槽状态枚举一一对应）
//   速度 [move speed]/[attack speed]/[cast speed]/[hit recovery]（§12 固定字段对）
//   其它 [inventory limit]/[HP regen speed]/[MP regen speed]/[MP regen speed rate]/[jump power]
//   属性/状态 [elemental property]（写 a1+772）/[active status]（17 槽枚举，写 a1+776）
//     —— 子枚举：[none]=17/[slow]=0/[freeze]=1/[poison]=2/[stun]=3/[curse]=4/[blind]=5/
//        [lightning]=6/[stone]=7/[sleep]=8/[burn]=9/[deadlystrike]=10/[bleeding]=11/[haste]=12/
//        [bless]=13/[element]=14/[hold]=16/[confuse]=15（★ 与 研究 20 §10 的 17 槽枚举完全一致）
//   攻击属性 [push aside]/[lift up]（走整型描述符 LABEL_115）/[physical critical hit]/
//     [magical critical hit]/[stuck]（走浮点 LABEL_125）/[ignore defense]（写 a1+850 开关）/
//     [human damage rate]/[fort damage rate]（浮点）/[HP drain]（a1+879）/[MP drain]（a1+880）
//   技能 [skill levelup]（子枚举 [common]=4 = 通用技能槽）/[avatar select ability]（44 项 off_791E28 表）
// ------------------------------------------------------------
char /*cdecl*/ sub_4F6790(int a1, unsigned int *a2, const char *ArgList)
{
  int v4; // eax
  int v5; // eax
  void **v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // esi
  void **v10; // eax
  int v11; // eax
  int v12; // eax
  void **v13; // eax
  unsigned int v14; // [esp-8h] [ebp-B4h]
  int v15; // [esp+0h] [ebp-ACh]
  float v16; // [esp+0h] [ebp-ACh]
  float v17; // [esp+0h] [ebp-ACh]
  int v18; // [esp+0h] [ebp-ACh]
  int v19; // [esp+10h] [ebp-9Ch] BYREF
  int v20; // [esp+30h] [ebp-7Ch] BYREF
  char v21; // [esp+34h] [ebp-78h]
  int v22; // [esp+44h] [ebp-68h]
  uint8_t v23[4]; // [esp+80h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+84h] [ebp-28h] BYREF
  unsigned int v25; // [esp+98h] [ebp-14h]
  int v26; // [esp+9Ch] [ebp-10h]
  int v27; // [esp+A8h] [ebp-4h]
  float v28; // [esp+B8h] [ebp+Ch]

  v26 = dword_796E50;
  v25 = 15;
  Block[4] = nullptr;
  LOBYTE(Block[0]) = 0;
  v14 = a2[5];
  v27 = 0;
  if ( sub_40BF00((std::_String_base *)a2, 0, v14, "[HP MAX]", 8u) != 0
    && sub_40BF00((std::_String_base *)a2, 0, a2[5], "[MP MAX]", 8u) != 0
    && sub_40BF00((std::_String_base *)a2, 0, a2[5], "[physical attack]", 0x11u) != 0
    && (uint8_t)sub_423300(a2, "[physical defense]") == 0 )
  {
    if ( (uint8_t)sub_423300(a2, "[magical attack]") != 0
      || (uint8_t)sub_423300(a2, "[magical defense]") != 0
      || (uint8_t)sub_423300(a2, "[equipment physical attack]") != 0
      || (uint8_t)sub_423300(a2, "[equipment physical defense]") != 0
      || (uint8_t)sub_423300(a2, "[equipment magical attack]") != 0
      || (uint8_t)sub_423300(a2, "[equipment magical defense]") != 0
      || (uint8_t)sub_423300(a2, "[physical absolute damage]") != 0
      || (uint8_t)sub_423300(a2, "[physical damage reduce]") != 0 )
    {
      goto LABEL_115;
    }
    if ( (uint8_t)sub_423300(a2, "[physical absolute defense]") != 0 )
    {
LABEL_125:                                   // ↑ 浮点属性路径：sub_442480 读 float → sub_432CF0 写入
      v17 = sub_442480(0);                       //   （研究 20 §12："[stuck]/暴击率等走浮点属性路径"）
      sub_432CF0(LODWORD(v17));
      goto LABEL_3;
    }
    if ( (uint8_t)sub_423300(a2, "[magical absolute damage]") != 0
      || (uint8_t)sub_423300(a2, "[magical damage reduce]") != 0 )
    {
      goto LABEL_115;
    }
    if ( (uint8_t)sub_423300(a2, "[magical absolute defense]") != 0 )
      goto LABEL_125;
    if ( (uint8_t)sub_423300(a2, "[fire resistance]") != 0
      || (uint8_t)sub_423300(a2, "[water resistance]") != 0
      || (uint8_t)sub_423300(a2, "[dark resistance]") != 0
      || (uint8_t)sub_423300(a2, "[light resistance]") != 0
      || (uint8_t)sub_423300(a2, "[all elemental resistance]") != 0
      || (uint8_t)sub_423300(a2, "[slow resistance]") != 0
      || (uint8_t)sub_423300(a2, "[freeze resistance]") != 0
      || (uint8_t)sub_423300(a2, "[poison resistance]") != 0
      || (uint8_t)sub_423300(a2, "[stun resistance]") != 0
      || (uint8_t)sub_423300(a2, "[curse resistance]") != 0
      || (uint8_t)sub_423300(a2, "[blind resistance]") != 0
      || (uint8_t)sub_423300(a2, "[lightning resistance]") != 0
      || (uint8_t)sub_423300(a2, "[stone resistance]") != 0
      || (uint8_t)sub_423300(a2, "[sleep resistance]") != 0
      || (uint8_t)sub_423300(a2, "[burn resistance]") != 0
      || (uint8_t)sub_423300(a2, "[deadlystrike resistance]") != 0
      || (uint8_t)sub_423300(a2, "[bleeding resistance]") != 0
      || (uint8_t)sub_423300(a2, "[all activestatus resistance]") != 0
      || (uint8_t)sub_423300(a2, "[piercing resistance]") != 0
      || (uint8_t)sub_423300(a2, "[stuck resistance]") != 0
      || (uint8_t)sub_423300(a2, "[confuse resistance]") != 0
      || (uint8_t)sub_423300(a2, "[hold resistance]") != 0
      || (uint8_t)sub_423300(a2, "[inventory limit]") != 0
      || (uint8_t)sub_423300(a2, "[HP regen speed]") != 0
      || (uint8_t)sub_423300(a2, "[MP regen speed]") != 0 )
    {
      goto LABEL_115;
    }
    if ( (uint8_t)sub_423300(a2, "[MP regen speed rate]") != 0 )
      goto LABEL_125;
    if ( (uint8_t)sub_423300(a2, "[move speed]") != 0
      || (uint8_t)sub_423300(a2, "[attack speed]") != 0
      || (uint8_t)sub_423300(a2, "[cast speed]") != 0
      || (uint8_t)sub_423300(a2, "[hit recovery]") != 0    // ★ §12 固定字段对之一（受方硬直恢复）
      || (uint8_t)sub_423300(a2, "[jump power]") != 0 )
    {
LABEL_115:                                 // ↑ 整型描述符路径：sub_4423D0 读 int → sub_41C150 写入
      v5 = sub_4423D0(0);                      //   （研究 20 §12："[hit recovery]/[stuck resistance] 等
      sub_41C150(v5);                          //    走通用整型描述符"；全段落类标签共用此出口，
      goto LABEL_3;                            //    故此处注释代表其上方全部抗性/速度/上限标签）
    }
    if ( (uint8_t)sub_423300(a2, "[elemental property]") != 0 )
    {
      sub_443370();
      *(uint32_t *)(a1 + 772) = sub_442710(Block);   // +772 [elemental property] 属性（名字查表）
    }
    else
    {
      if ( (uint8_t)sub_423300(a2, "[active status]") != 0 )
      {
        sub_443370();
        // +776 [active status] 状态槽 —— 17 槽枚举，与 研究 20 §10 定案逐一吻合：
        if ( (uint8_t)sub_423300(v23, "[none]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 17;         // 17 = none
        }
        else if ( (uint8_t)sub_423300(v23, "[slow]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 0;          // 0 = slow
        }
        else if ( (uint8_t)sub_423300(v23, "[freeze]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 1;
        }
        else if ( (uint8_t)sub_423300(v23, "[poison]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 2;
        }
        else if ( (uint8_t)sub_423300(v23, "[stun]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 3;
        }
        else if ( (uint8_t)sub_423300(v23, "[curse]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 4;
        }
        else if ( (uint8_t)sub_423300(v23, "[blind]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 5;
        }
        else if ( (uint8_t)sub_423300(v23, "[lightning]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 6;
        }
        else if ( (uint8_t)sub_423300(v23, "[stone]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 7;
        }
        else if ( (uint8_t)sub_423300(v23, "[sleep]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 8;
        }
        else if ( (uint8_t)sub_423300(v23, "[burn]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 9;
        }
        else if ( (uint8_t)sub_423300(v23, "[deadlystrike]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 10;
        }
        else if ( (uint8_t)sub_423300(v23, "[bleeding]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 11;
        }
        else if ( (uint8_t)sub_423300(v23, "[haste]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 12;
        }
        else if ( (uint8_t)sub_423300(v23, "[bless]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 13;
        }
        else if ( (uint8_t)sub_423300(v23, "[element]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 14;
        }
        else if ( (uint8_t)sub_423300(v23, "[hold]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 16;
        }
        else if ( (uint8_t)sub_423300(v23, "[confuse]") != 0 )
        {
          *(uint32_t *)(a1 + 776) = 15;
        }
        v16 = sub_442480(0);
        sub_432CF0(LODWORD(v16));
        v4 = sub_4423D0(0);
        sub_41C150(v4);
        goto LABEL_3;
      }
      if ( (uint8_t)sub_423300(a2, "[push aside]") != 0 || (uint8_t)sub_423300(a2, "[lift up]") != 0 )
        goto LABEL_115;
      if ( (uint8_t)sub_423300(a2, "[physical critical hit]") != 0
        || (uint8_t)sub_423300(a2, "[magical critical hit]") != 0
        || (uint8_t)sub_423300(a2, "[stuck]") != 0 )
      {
        goto LABEL_125;
      }
      if ( (uint8_t)sub_423300(a2, "[ignore defense]") != 0 )
      {
        *(uint8_t *)(a1 + 850) = sub_4423D0(0) != 0;
        goto LABEL_3;
      }
      if ( (uint8_t)sub_423300(a2, "[human damage rate]") != 0
        || (uint8_t)sub_423300(a2, "[fort damage rate]") != 0 )
      {
        goto LABEL_125;
      }
      if ( (uint8_t)sub_423300(a2, "[HP drain]") != 0 )
      {
        *(uint8_t *)(a1 + 879) = sub_4423D0(0) != 0;
      }
      else if ( (uint8_t)sub_423300(a2, "[MP drain]") != 0 )
      {
        *(uint8_t *)(a1 + 880) = sub_4423D0(0) != 0;
      }
      else if ( (uint8_t)sub_423300(a2, "[skill levelup]") != 0 )
      {
        sub_434140(a1 + 884);
        sub_4F4B60(&v19);
        LOBYTE(v27) = 1;
        while ( sub_443370() != 0 )
        {
          sub_4E99F0(&v19);
          if ( (uint8_t)sub_423300(v23, "[common]") != 0 )
          {
            v19 = 4;
          }
          else
          {
            v6 = (void **)Block[0];
            if ( v25 < 0x10 )
              v6 = Block;
            v19 = sub_4426A0(v6);
          }
          v7 = sub_4423D0(0);
          sub_41A590(v7);
          v8 = sub_4423D0(0);
          sub_41A590(v8);
          sub_4EE120(&v19);
        }
        LOBYTE(v27) = 0;
        sub_432DC0(&v19);
      }
      else
      {
        if ( (uint8_t)sub_423300(a2, "[avatar select ability]") == 0 )
        {
LABEL_165:
          sub_501490(v23);
          return 0;
        }
        sub_436840(a1 + 916);
        if ( sub_443370() != 0 )
        {
          while ( 2 )
          {
            sub_4F5220(&v20);
            LOBYTE(v27) = 2;
            v9 = 0;
            while ( (uint8_t)sub_423300(v23, off_791E28[v9]) == 0 )
            {
              if ( ++v9 >= 44 )
                goto LABEL_158;
            }
            v20 = v9;
            if ( v9 == 43 )
            {
              v21 = 0;
              sub_443370();
              if ( (uint8_t)sub_423300(v23, "[common]") != 0 )
              {
                v22 = 4;
              }
              else
              {
                v10 = (void **)Block[0];
                if ( v25 < 0x10 )
                  v10 = Block;
                v11 = sub_4426A0(v10);
                if ( v11 == 4 )
                {
                  v13 = (void **)Block[0];
                  if ( v25 < 0x10 )
                    v13 = Block;
                  off_77F3FC("ImportEquipmentScript - file %s, invalid job tag %s", ArgList, (const char *)v13);
                  LOBYTE(v27) = 0;
                  sub_433D10(&v20);
                  goto LABEL_165;
                }
                v22 = v11;
              }
              v12 = sub_4423D0(0);
              sub_41A590(v12);
              v18 = sub_4423D0(0);
              sub_41A590(v18);
            }
            else
            {
              sub_443370();
              if ( (uint8_t)sub_423300(v23, &asc_6FA81C) != 0 )
              {
                v21 = 0;
              }
              else if ( (uint8_t)sub_423300(v23, "*") != 0 )
              {
                v21 = 1;
              }
              v28 = sub_442480(0);
              sub_41A590(LODWORD(v28));
            }
LABEL_158:
            if ( (unsigned int)sub_4EAF60(a1 + 916) < 0x3C )
              sub_4F6700(&v20);
            LOBYTE(v27) = 0;
            sub_433D10(&v20);
            if ( sub_443370() != 0 )
              continue;
            break;
          }
        }
      }
    }
  }
  else
  {
    v15 = sub_4423D0(0);
    sub_41A590(v15);
  }
LABEL_3:
  if ( v25 >= 0x10 )
    j__free(Block[0]);
  return 1;
}


// ------------------------------------------------------------
// 0x4F7800 sub_4F7800
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4F7800(uint32_t *a1, int a2, uint32_t *a3)
{
  sub_4F6670(a1, a2, a3);
  return &a1[31 * a2];
}



// ------------------------------------------------------------
// 0x4F7830 sub_4F7830
// ------------------------------------------------------------
void /*thiscall*/ sub_4F7830(int *this, char *a2, unsigned int a3, uint32_t *a4)
{
  int v5; // ebx
  unsigned int v6; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  char *v12; // ebx
  int v13; // eax
  unsigned int v14; // edi
  int v15; // eax
  uint32_t *v16; // ecx
  int v18; // edx
  uint32_t *v19; // [esp-18h] [ebp-B8h]
  int v20; // [esp-Ch] [ebp-ACh]
  unsigned int v21; // [esp-8h] [ebp-A8h]
  int v22; // [esp+0h] [ebp-A0h] BYREF
  void *v23[32]; // [esp+Ch] [ebp-94h] BYREF
  void *Block; // [esp+8Ch] [ebp-14h]
  int *v25; // [esp+90h] [ebp-10h]
  int v26; // [esp+9Ch] [ebp-4h]
  uint32_t *v27; // [esp+A8h] [ebp+8h]
  uint32_t *v28; // [esp+ACh] [ebp+Ch]
  int v29; // [esp+B0h] [ebp+10h]

  v25 = &v22;
  v23[31] = this;
  sub_4F5290(v23, a4);
  v5 = *(this + 1);
  v6 = 0;
  v26 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 124;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - *(this + 1)) / 124;
    else
      v8 = 0;
    if ( 34636833 - v8 < a3 )
      sub_434730(this);
    if ( *(this + 1) != 0 )
      v9 = (*(this + 2) - *(this + 1)) / 124;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = (uint32_t *)*(this + 2);
      Block = v16;
      if ( ((char *)v16 - a2) / 124 >= a3 )
      {
        v27 = &v16[-31 * a3];
        *(this + 2) = (int)sub_4F5B00(v27, v16, v16);
        sub_4F5AE0(a2, v27, Block);
        sub_4F5AB0(a2, &a2[124 * a3], v23);
      }
      else
      {
        sub_4F5B00(a2, v16, &a2[124 * a3]);
        v21 = a3 - (*(this + 2) - (int)a2) / 124;
        v20 = *(this + 2);
        LOBYTE(v26) = 3;
        sub_4F7800(v20, v21, v23);
        v18 = 124 * a3 + *(this + 2);
        *(this + 2) = v18;
        v26 = 0;
        sub_4F5AB0(a2, v18 - 124 * a3, v23);
      }
    }
    else
    {
      if ( 34636833 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        v11 = (*(this + 2) - *(this + 1)) / 124;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_4EAF80(this);
      v29 = 124 * v10;
      v12 = (char *)operator new(124 * v10);
      v19 = (uint32_t *)*(this + 1);
      Block = v12;
      LOBYTE(v26) = 1;
      v28 = sub_4F5B00(v19, a2, v12);
      sub_4F6670(v28, a3, v23);
      sub_4F5B00(a2, (uint32_t *)*(this + 2), &v28[31 * a3]);
      v13 = *(this + 1);
      v26 = 0;
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 124;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_4388A0(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v29];
      *(this + 2) = (int)&v12[124 * v14];
      *(this + 1) = (int)v12;
    }
  }
  v26 = -1;
  sub_4347B0(v23);
}


// ------------------------------------------------------------
// 0x4F7B60 sub_4F7B60
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F7B60(int *this, uint32_t *a2, char *a3, uint32_t *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 124 != 0 )
    v6 = (int)&a3[-v5] / 124;
  else
    v6 = 0;
  sub_4F7830(this, a3, 1u, a4);
  *a2 = *(this + 1) + 124 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4F7BD0 sub_4F7BD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F7BD0(int this, uint32_t *a2)
{
  int v3; // ebx
  unsigned int v4; // esi
  uint32_t *v5; // esi
  uint32_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 124;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 124 )
    return sub_4F7B60((int *)this, &a2, *(char **)(this + 8), a2);
  v5 = *(uint32_t **)(this + 8);
  result = sub_4F6670(v5, 1, a2);
  *(uint32_t *)(this + 8) = v5 + 31;
  return result;
}



// ============================================================
// §G 0x4F7C60-0x4F8E20 ★ 装备定义解析器 sub_4F7C60（含动作表/套装/内联属性解析）
// ============================================================

// ------------------------------------------------------------
// 0x4F7C60 sub_4F7C60 —— ★★ 装备(equipment/avatar)定义解析器（81 标签，全库单函数标签数第一）
//   本体属性块：文本 [name]/[name2]/[explain]/[flavor text]/[fullset explain]/[set name]；
//   品级绑定 [grade]（+4）/[attach type]（+8 起，同 [free]/[trade]/[trade delete]/[sealing] 枚举）/
//   [creation rate]（+12）/[rarity]（+16）/[weight]（+40）；
//   资源 [icon]（+60）/[field image]（+68）/[custom animation]（+76 表）；
//   准入 [usable job]/[minimum level]（+48）/[required skill]（+52）/[cool time]（+56）；
//   部位枚举 [equipment type]（子串：[weapon]/[coat]/[shoulder]/[pants]/[shoes]/[waist]/[amulet]/
//   [wrist]/[ring]/[title name]）；时装部位 [hat/hair/face/coat/pants/shoes/breast/waist avatar]（8）；
//   [sub type]（+96）/[durability]（+100）；价值 [price]（+20）/[value]（+36）/
//   [finish point price]（+32）/[cash]（+24）/[medal]（+28）；
//   ★ 属性内联：其余标签直接转发 sub_4F6790(i, &v53, v2) —— 装备属性表复用属性解析器；
//   动作表 [LAYER] 与 23 项动作（[waiting motion]/[move motion]/[sit motion]/[damage motion 1-2]/
//   [down motion]/[overturn motion]/[jump motion]/[jumpattack motion]/[rest motion]/
//   [throw motion 1-1..4-2]（8）/  [dash motion]/[dashattack motion]/[getitem motion]/[buff motion]/
//   [attack motion]/[etc motion]）；
//   音效 [move wav]（+1068）/[custom wav]（+1072 表）；[variation]；
//   套装 [set item]（+1108 表）/[set ability]（+1124）/ [set item master]（+2072）；
//   [int data]（+2076 表）/[string data]（+2092 表）。
//   调用者：sub_4D2D60 工厂（装备类，0x1D8+ 大对象）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4F7C60(int a1, char *ArgList)
{
  const char *v2; // edi
  char result; // al
  void **v4; // eax
  int v5; // eax
  int v6; // eax
  void **v7; // edi
  void **v8; // ebx
  void **v9; // edi
  void **v10; // ebx
  int v11; // eax
  const char *v12; // eax
  int v13; // edx
  void *v14[5]; // [esp-1Ch] [ebp-FCh] BYREF
  uint8_t *v15; // [esp-8h] [ebp-E8h]
  void **j; // [esp-4h] [ebp-E4h]
  int v17; // [esp+Ch] [ebp-D4h] BYREF
  char v18; // [esp+10h] [ebp-D0h] BYREF
  char v19; // [esp+14h] [ebp-CCh] BYREF
  char v20; // [esp+18h] [ebp-C8h] BYREF
  char v21; // [esp+1Ch] [ebp-C4h] BYREF
  char v22; // [esp+20h] [ebp-C0h] BYREF
  char v23; // [esp+24h] [ebp-BCh] BYREF
  char v24; // [esp+28h] [ebp-B8h] BYREF
  char v25; // [esp+2Ch] [ebp-B4h] BYREF
  char v26; // [esp+30h] [ebp-B0h] BYREF
  char v27; // [esp+34h] [ebp-ACh] BYREF
  char v28; // [esp+38h] [ebp-A8h] BYREF
  char v29; // [esp+3Ch] [ebp-A4h] BYREF
  char v30; // [esp+40h] [ebp-A0h] BYREF
  char v31; // [esp+44h] [ebp-9Ch] BYREF
  char v32; // [esp+48h] [ebp-98h] BYREF
  char v33; // [esp+4Ch] [ebp-94h] BYREF
  char v34; // [esp+50h] [ebp-90h] BYREF
  char v35; // [esp+54h] [ebp-8Ch] BYREF
  char v36; // [esp+58h] [ebp-88h] BYREF
  char v37; // [esp+5Ch] [ebp-84h] BYREF
  char v38; // [esp+60h] [ebp-80h] BYREF
  char v39; // [esp+64h] [ebp-7Ch] BYREF
  void *Block; // [esp+6Ch] [ebp-74h]
  void **v41; // [esp+70h] [ebp-70h]
  int k; // [esp+74h] [ebp-6Ch]
  void *v43; // [esp+7Ch] [ebp-64h]
  void **v44; // [esp+80h] [ebp-60h]
  int m; // [esp+84h] [ebp-5Ch]
  int i; // [esp+88h] [ebp-58h]
  void **n; // [esp+8Ch] [ebp-54h] BYREF
  char v48; // [esp+93h] [ebp-4Dh] BYREF
  void *v49; // [esp+94h] [ebp-4Ch] BYREF
  int v50; // [esp+98h] [ebp-48h] BYREF
  void *v51[5]; // [esp+9Ch] [ebp-44h] BYREF
  unsigned int v52; // [esp+B0h] [ebp-30h]
  int v53; // [esp+B4h] [ebp-2Ch] BYREF
  void *v54; // [esp+B8h] [ebp-28h] BYREF
  unsigned int v55; // [esp+C8h] [ebp-18h]
  unsigned int v56; // [esp+CCh] [ebp-14h]
  int v57; // [esp+D0h] [ebp-10h]
  int v58; // [esp+DCh] [ebp-4h]

  v2 = ArgList;
  v57 = dword_796E50;
  result = sub_442A10((char)&unk_9B6A60, (int)ArgList);
  if ( result != 0 )
  {
    sub_4393E0((char *)a1);
    v52 = 15;
    v51[4] = nullptr;
    LOBYTE(v51[0]) = 0;
    j = (void **)ArgList;
    v58 = 0;
    sub_443300((int)&v50, "%s%s", (char)&unk_9B6A60);
    v4 = (void **)v51[0];
    if ( v52 < 0x10 )
      v4 = v51;
    sub_41BFE0((void **)(a1 + 1088), (const char *)v4);
    v56 = 15;
    v55 = 0;
    LOBYTE(v54) = 0;
    LOBYTE(v58) = 1;
    v49 = nullptr;
    sub_41BFE0(&v49, szPassword);
    LOBYTE(v58) = 2;
    sub_4F55E0(&v17);
    LOBYTE(v58) = 3;
    v48 = 0;
    for ( i = a1 + 104; (uint8_t)sub_443430(&v53) != 0; v2 = ArgList )
    {
      if ( (uint8_t)sub_442BC0(&v53) != 0 )
        off_77F3FC((char *)&byte_6FA9F8, v2);
      if ( sub_40BF00((std::_String_base *)&v53, 0, v55, "[name]", 6u) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)&v53, 0, v55, "[name2]", 7u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)&v53, 0, v55, "[explain]", 9u) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)&v53, 0, v55, "[flavor text]", 0xDu) != 0 )
            {
              if ( (uint8_t)sub_423300(&v53, "[fullset explain]") != 0 )
              {
                j = (void **)(a1 + 2132);
                sub_442E10();
              }
              else if ( (uint8_t)sub_423300(&v53, "[set name]") != 0 )
              {
                j = (void **)(a1 + 1104);
                sub_442E10();
              }
              else if ( (uint8_t)sub_423300(&v53, "[grade]") != 0 )
              {
                *(uint32_t *)(a1 + 4) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[attach type]") != 0 )
              {
                j = &v49;
                sub_442E10();
                if ( sub_43BCF0(&v49, "[free]") )
                {
                  *(uint32_t *)(a1 + 8) = 0;
                }
                else if ( sub_43BCF0(&v49, "[trade]") )
                {
                  *(uint32_t *)(a1 + 8) = 1;
                }
                else if ( sub_43BCF0(&v49, "[trade delete]") )
                {
                  *(uint32_t *)(a1 + 8) = 2;
                }
                else if ( sub_43BCF0(&v49, "[sealing]") )
                {
                  *(uint32_t *)(a1 + 8) = 3;
                }
              }
              else if ( (uint8_t)sub_423300(&v53, "[creation rate]") != 0 )
              {
                *(uint32_t *)(a1 + 12) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[rarity]") != 0 )
              {
                *(uint32_t *)(a1 + 16) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[weight]") != 0 )
              {
                *(uint32_t *)(a1 + 40) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[icon]") != 0 )
              {
                j = (void **)(a1 + 60);
                sub_442E10();
                *(uint32_t *)(a1 + 64) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[field image]") != 0 )
              {
                j = (void **)(a1 + 68);
                sub_442E10();
                *(uint32_t *)(a1 + 72) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[custom animation]") != 0 )
              {
                sub_4017E0(a1 + 76);
                for ( j = &v49; sub_442E10() != 0; j = &v49 )
                  sub_420BB0(&v49);
              }
              else if ( (uint8_t)sub_423300(&v53, "[usable job]") != 0 )
              {
                for ( j = &v49; sub_442E10() != 0; j = &v49 )
                {
                  v5 = sub_41ACF0(&v49);
                  v6 = sub_4426A0(v5);
                  if ( v6 == 4 )
                  {
                    *(uint32_t *)(a1 + 44) = 16843009;
                    *(uint8_t *)(a1 + 2108) = 1;
                  }
                  else
                  {
                    *(uint8_t *)(a1 + v6 + 44) = 1;
                  }
                }
              }
              else if ( (uint8_t)sub_423300(&v53, "[minimum level]") != 0 )
              {
                *(uint32_t *)(a1 + 48) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[required skill]") != 0 )
              {
                *(uint32_t *)(a1 + 52) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[cool time]") != 0 )
              {
                *(uint32_t *)(a1 + 56) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[equipment type]") != 0 )
              {
                j = &v49;
                sub_442E10();
                if ( sub_43BCF0(&v49, "[hat avatar]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 0;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[hair avatar]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 1;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[face avatar]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 2;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[coat avatar]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 3;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[pants avatar]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 4;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[shoes avatar]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 5;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[breast avatar]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 6;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[waist avatar]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 7;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[weapon]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 8;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[title name]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 9;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[coat]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 10;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[shoulder]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 11;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[pants]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 12;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[shoes]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 13;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[waist]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 14;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[amulet]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 15;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else if ( sub_43BCF0(&v49, "[wrist]") )
                {
                  j = nullptr;
                  *(uint32_t *)(a1 + 92) = 16;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(j);
                }
                else
                {
                  if ( sub_43BCF0(&v49, "[ring]") )
                    *(uint32_t *)(a1 + 92) = 17;
                  *(uint32_t *)(a1 + 2112) = sub_4423D0(nullptr);
                }
              }
              else if ( (uint8_t)sub_423300(&v53, "[sub type]") != 0 )
              {
                *(uint32_t *)(a1 + 96) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[durability]") != 0 )
              {
                *(uint32_t *)(a1 + 100) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[price]") != 0 )
              {
                *(uint32_t *)(a1 + 20) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[value]") != 0 )
              {
                *(uint32_t *)(a1 + 36) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[finish point price]") != 0 )
              {
                *(uint32_t *)(a1 + 32) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[cash]") != 0 )
              {
                *(uint32_t *)(a1 + 24) = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(&v53, "[medal]") != 0 )
              {
                *(uint32_t *)(a1 + 28) = sub_4423D0(nullptr);
              }
              else if ( sub_4F6790(i, (unsigned int *)&v53, v2) == 0 )
              {
                if ( (uint8_t)sub_423300(&v53, "[LAYER]") != 0 )
                {
                  if ( v17 != 0 )
                    sub_4F7BD0(&v17);
                  sub_4F4F30(&v17);
                  v17 = sub_4423D0(nullptr);
                }
                else if ( (uint8_t)sub_423300(&v53, "[waiting motion]") != 0 )
                {
                  j = (void **)&v18;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[move motion]") != 0 )
                {
                  j = (void **)&v19;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[sit motion]") != 0 )
                {
                  j = (void **)&v20;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[damage motion 1]") != 0 )
                {
                  j = (void **)&v21;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[damage motion 2]") != 0 )
                {
                  j = (void **)&v22;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[down motion]") != 0 )
                {
                  j = (void **)&v23;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[overturn motion]") != 0 )
                {
                  j = (void **)&v24;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[jump motion]") != 0 )
                {
                  j = (void **)&v25;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[jumpattack motion]") != 0 )
                {
                  j = (void **)&v26;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[rest motion]") != 0 )
                {
                  j = (void **)&v27;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 1-1]") != 0 )
                {
                  j = (void **)&v28;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 1-2]") != 0 )
                {
                  j = (void **)&v32;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 2-1]") != 0 )
                {
                  j = (void **)&v29;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 2-2]") != 0 )
                {
                  j = (void **)&v33;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 3-1]") != 0 )
                {
                  j = (void **)&v30;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 3-2]") != 0 )
                {
                  j = (void **)&v34;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 4-1]") != 0 )
                {
                  j = (void **)&v31;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 4-2]") != 0 )
                {
                  j = (void **)&v35;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[dash motion]") != 0 )
                {
                  j = (void **)&v36;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[dashattack motion]") != 0 )
                {
                  j = (void **)&v37;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[getitem motion]") != 0 )
                {
                  j = (void **)&v38;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[buff motion]") != 0 )
                {
                  j = (void **)&v39;
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[attack motion]") != 0 )
                {
                  v7 = (void **)Block;
                  if ( Block != nullptr )
                  {
                    v8 = v41;
                    if ( Block != v41 )
                    {
                      do
                        sub_41B010(v7++);
                      while ( v7 != v8 );
                      v7 = (void **)Block;
                    }
                    j__free(v7);
                  }
                  j = &v49;
                  Block = nullptr;
                  v41 = nullptr;
                  for ( k = 0; sub_442E10() != 0; j = &v49 )
                    sub_420BB0(&v49);
                }
                else if ( (uint8_t)sub_423300(&v53, "[etc motion]") != 0 )
                {
                  v9 = (void **)v43;
                  if ( v43 != nullptr )
                  {
                    v10 = v44;
                    if ( v43 != v44 )
                    {
                      do
                        sub_41B010(v9++);
                      while ( v9 != v10 );
                      v9 = (void **)v43;
                    }
                    j__free(v9);
                  }
                  j = &v49;
                  v43 = nullptr;
                  v44 = nullptr;
                  for ( m = 0; sub_442E10() != 0; j = &v49 )
                    sub_420BB0(&v49);
                }
                else if ( (uint8_t)sub_423300(&v53, "[move wav]") != 0 )
                {
                  j = (void **)(a1 + 1068);
                  sub_442E10();
                }
                else if ( (uint8_t)sub_423300(&v53, "[custom wav]") != 0 )
                {
                  sub_4017E0(a1 + 1072);
                  for ( j = &v49; sub_442E10() != 0; j = &v49 )
                    sub_420BB0(&v49);
                }
                else if ( (uint8_t)sub_423300(&v53, "[variation]") != 0 )
                {
                  v11 = sub_4423D0(nullptr);
                  v15 = nullptr;
                  *(uint32_t *)(a1 + 1092) = v11;
                  *(uint32_t *)(a1 + 1096) = sub_4423D0(v15);
                  *(uint8_t *)(a1 + 1100) = 1;
                }
                else if ( (uint8_t)sub_423300(&v53, "[set item]") != 0 )
                {
                  sub_5E5260((void **)(a1 + 1108));
                  for ( n = (void **)sub_4423D0(&v48); v48 != 0; n = (void **)sub_4423D0(&v48) )
                    sub_431230(a1 + 1108, &n);
                }
                else if ( (uint8_t)sub_423300(&v53, "[set ability]") != 0 )
                {
                  i = a1 + 1124;
                }
                else if ( (uint8_t)sub_423300(&v53, "[set item master]") != 0 )
                {
                  *(uint32_t *)(a1 + 2072) = sub_4423D0(nullptr);
                }
                else if ( (uint8_t)sub_423300(&v53, "[int data]") != 0 )
                {
                  sub_5E5260((void **)(a1 + 2076));
                  for ( n = (void **)sub_4423D0(&v48); v48 != 0; n = (void **)sub_4423D0(&v48) )
                    sub_431230(a1 + 2076, &n);
                }
                else if ( (uint8_t)sub_423300(&v53, "[string data]") != 0 )
                {
                  sub_4017E0(a1 + 2092);
                  for ( j = &v49; sub_442E10() != 0; j = &v49 )
                    sub_420BB0(&v49);
                }
                else
                {
                  n = v14;
                  sub_401690(&v53);
                  if ( (uint8_t)sub_442C80(
                                          (char)v14[0],
                                          v14[1],
                                          (int)v14[2],
                                          (int)v14[3],
                                          (int)v14[4],
                                          (int)v15,
                                          (int)j) == 0 )
                  {
                    v12 = (const char *)v54;
                    if ( v56 < 0x10 )
                      v12 = (const char *)&v54;
                    off_77F3FC("SCRIPT TAG ERROR! [%s] %s", v2, v12);
                  }
                }
              }
            }
            else
            {
              j = (void **)(a1 + 2136);
              sub_442E10();
            }
          }
          else
          {
            j = (void **)(a1 + 2128);
            sub_442E10();
          }
        }
        else
        {
          j = (void **)(a1 + 2124);
          sub_442E10();
        }
      }
      else
      {
        j = (void **)(a1 + 2120);
        sub_442E10();
      }
    }
    if ( v17 != 0 )
      sub_4F7BD0(&v17);
    if ( *(uint32_t *)(a1 + 36) == -1 )
      *(uint32_t *)(a1 + 36) = *(uint32_t *)(a1 + 20);
    v13 = 10 * *(uint32_t *)(a1 + 24) + *(uint32_t *)(a1 + 20);
    j = (void **)v2;
    *(uint32_t *)(a1 + 20) = v13;
    *(uint32_t *)(a1 + 24) = 0;
    *(uint32_t *)a1 = sub_4A2F80(j);
    LOBYTE(v58) = 2;
    sub_4347B0(&v17);
    LOBYTE(v58) = 1;
    sub_41B010(&v49);
    if ( v56 >= 0x10 )
      j__free(v54);
    v56 = 15;
    v55 = 0;
    LOBYTE(v54) = 0;
    if ( v52 >= 0x10 )
      j__free(v51[0]);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4F8D70 sub_4F8D70
// ------------------------------------------------------------
int /*thiscall*/ sub_4F8D70(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 84;
  return result;
}



// ------------------------------------------------------------
// 0x4F8D90 sub_4F8D90
// ------------------------------------------------------------
char */*cdecl*/ sub_4F8D90(char *a1, char *a2, char *a3)
{
  char *v3; // edx
  char *result; // eax

  v3 = a2;
  result = a3;
  while ( v3 != a1 )
  {
    v3 -= 44;
    result -= 44;
    qmemcpy(result, v3, 0x2Cu);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F8DC0 sub_4F8DC0
// ------------------------------------------------------------
char */*cdecl*/ sub_4F8DC0(char *a1, char *a2, char *a3)
{
  char *v3; // edx
  char *result; // eax
  const void *v5; // esi
  void *v6; // edi

  v3 = a1;
  result = a3;
  while ( v3 != a2 )
  {
    v5 = v3;
    v6 = result;
    v3 += 44;
    result += 44;
    qmemcpy(v6, v5, 0x2Cu);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F8DF0 sub_4F8DF0
// ------------------------------------------------------------
char */*cdecl*/ sub_4F8DF0(char *a1, char *a2, const void *a3)
{
  char *result; // eax
  char *v4; // edx

  result = a2;
  if ( a2 != nullptr )
  {
    v4 = a2;
    result = a1;
    do
    {
      if ( result != nullptr )
        qmemcpy(result, a3, 0x2Cu);
      result += 44;
      --v4;
    }
    while ( v4 != nullptr );
  }
  return result;
}



// ============================================================
// §H 0x4F8E20-0x4FC000 全局表族（金限/战场/表情/等级表/时装/战场平衡）
// ============================================================

// ------------------------------------------------------------
// 0x4F8E20 sub_4F8E20 —— 等级金限表解析器（Etc/GoldLimitByLevel.etc）
//   标签族：[gold limit from level]（最多 100 条：等级索引 → 金额 ×10）。
//   加载失败 → off_77F3FC(aCriticalError_13)。
// ------------------------------------------------------------
char /*cdecl*/ sub_4F8E20(void *a1)
{
  int i; // esi
  int v3; // edi
  uint8_t v4[21]; // [esp+Bh] [ebp-49h] BYREF
  int v5; // [esp+20h] [ebp-34h]
  int v6; // [esp+24h] [ebp-30h]
  uint8_t v7[4]; // [esp+28h] [ebp-2Ch] BYREF
  void *Block; // [esp+2Ch] [ebp-28h]
  unsigned int v9; // [esp+3Ch] [ebp-18h]
  unsigned int v10; // [esp+40h] [ebp-14h]
  int v11; // [esp+44h] [ebp-10h]
  int v12; // [esp+50h] [ebp-4h]

  v11 = dword_796E50;
  memset(a1, 0, 0x190u);
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"Etc/GoldLimitByLevel.etc") != 0 )
  {
    v10 = 15;
    v9 = 0;
    LOBYTE(Block) = 0;
    v12 = 1;
    v6 = 15;
    v5 = 0;
    v4[5] = 0;
    v4[0] = 0;
    while ( (uint8_t)sub_443430(v7) != 0 )
    {
      if ( sub_40BF00((std::_String_base *)v7, 0, v9, "[gold limit from level]", 0x17u) == 0 )
      {
        for ( i = 0; i < 100; ++i )
        {
          v3 = sub_4423D0(v4);
          if ( v4[0] == 0 )
            break;
          *((uint32_t *)a1 + v3) = 10 * sub_4423D0(nullptr);
        }
      }
    }
    if ( v10 >= 0x10 )
      j__free(Block);
    return 1;
  }
  else
  {
    off_77F3FC(aCriticalError_13);
    return 0;
  }
}



// ------------------------------------------------------------
// 0x4F8F40 sub_4F8F40
// ------------------------------------------------------------
int /*thiscall*/ sub_4F8F40(uint32_t *this, uint8_t a2, uint8_t a3, uint8_t a4)
{
  int v6; // edi
  unsigned int v7; // ecx

  if ( a3 == 0 )
    return -1;
  if ( a2 > 4u )
    return -2;
  if ( a3 > 0x63u )
    return -3;
  if ( a4 >= 7u )
    return -4;
  v6 = *(this + 1);
  v7 = (a3 - 1) / 10;
  if ( v6 == 0 || v7 >= (*(this + 2) - v6) >> 2 )
    v7 = sub_41C5A0(this) - 1;
  return *(uint32_t *)(v6 + 4 * v7) * *(this + a2 + 4) + *(this + a2 + 9) * a4;
}



// ------------------------------------------------------------
// 0x4F8FE0 sub_4F8FE0 —— PVP 频道信息表解析器
//   标签族：[PVP CHANNEL INFO]（每频道 140 字节：名称 + 3 字节 + 104 字节槽位记录）。
//   未识别标签 → off_77F3FC(aPvp_3)。
// ------------------------------------------------------------
char /*cdecl*/ sub_4F8FE0(int ArgList, int a2, int a3)
{
  char result; // al
  unsigned int v4; // esi
  int i; // eax
  int v6; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // esi
  const char *p_Block; // eax
  int v11; // eax
  char v12; // [esp+0h] [ebp-60h]
  int v13; // [esp+4h] [ebp-5Ch]
  char v14; // [esp+8h] [ebp-58h]
  char v15; // [esp+Ch] [ebp-54h]
  unsigned int v16; // [esp+10h] [ebp-50h]
  char v17; // [esp+17h] [ebp-49h] BYREF
  uint8_t v18[4]; // [esp+18h] [ebp-48h] BYREF
  void *v19; // [esp+1Ch] [ebp-44h]
  unsigned int v20; // [esp+2Ch] [ebp-34h]
  unsigned int v21; // [esp+30h] [ebp-30h]
  void *Block; // [esp+38h] [ebp-28h] BYREF
  int v23; // [esp+48h] [ebp-18h]
  unsigned int v24; // [esp+4Ch] [ebp-14h]
  int v25; // [esp+50h] [ebp-10h]
  int v26; // [esp+5Ch] [ebp-4h]

  v25 = dword_796E50;
  result = sub_442A10((char)szPassword, ArgList);
  if ( result != 0 )
  {
    v4 = 0;
    v21 = 15;
    v20 = 0;
    LOBYTE(v19) = 0;
    v26 = 0;
    v17 = 0;
    while ( (uint8_t)sub_443430(v18) != 0 )
    {
      if ( (uint8_t)sub_442BC0(v18) != 0 )
        off_77F3FC((char *)&byte_6FA9F8, ArgList);
      if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[PVP CHANNEL INFO]", 0x12u) == 0 )
      {
        for ( i = sub_4423D0(&v17); v17 != 0; i = sub_4423D0(&v17) )
        {
          if ( --a3 >= 0 )
          {
            v24 = 15;
            v23 = 0;
            LOBYTE(Block) = 0;
            LOBYTE(v26) = 1;
            v6 = 140 * i + a2 - 140;
            v13 = sub_4423D0(nullptr);
            v16 = 0;
            if ( v13 > 0 )
            {
              v7 = 0;
              do
              {
                sub_443370();
                v14 = sub_4423D0(nullptr);
                v15 = sub_4423D0(nullptr);
                v12 = sub_4423D0(nullptr);
                v8 = *(uint32_t *)(v6 + 128);
                if ( v8 != 0 && v4 < (*(uint32_t *)(v6 + 132) - v8) / 104 )
                {
                  v9 = *(uint32_t *)(v6 + 128);
                  p_Block = (const char *)Block;
                  if ( v24 < 0x10 )
                    p_Block = (const char *)&Block;
                  strncpy((char *)(v7 + v9 + 4), p_Block, 0x32u);
                  *(uint8_t *)(v7 + v9 + 98) = v14;
                  *(uint8_t *)(v7 + v9 + 99) = v15;
                  *(uint8_t *)(v7 + v9 + 100) = v12;
                  v4 = v16;
                }
                else
                {
                  v11 = *(uint32_t *)(v6 + 128);
                  if ( v11 != 0 )
                    v11 = (*(uint32_t *)(v6 + 132) - v11) / 104;
                  off_77F3FC(aPvp_3, v4 + 1, v11);
                }
                ++v4;
                v7 += 104;
                v16 = v4;
              }
              while ( (int)v4 < v13 );
              v4 = 0;
            }
            LOBYTE(v26) = 0;
            if ( v24 >= 0x10 )
              j__free(Block);
            v24 = 15;
            v23 = 0;
            LOBYTE(Block) = 0;
          }
        }
      }
    }
    if ( v21 >= 0x10 )
      j__free(v19);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4F9240 sub_4F9240 —— 战场区域表解析器（Etc/WarArea.etc）
//   标签族：[time table]（时段表）/[door fee]（入场费）/[counter]。
//   加载失败 → off_77F3FC(aCriticalError_14)。
// ------------------------------------------------------------
char /*cdecl*/ sub_4F9240(int a1)
{
  int v2; // ebx
  unsigned int v3; // edx
  int v4; // ecx
  void **v5; // esi
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int *v9; // esi
  int v10; // ecx
  void **v11; // esi
  int v12; // eax
  int v13; // eax
  int *v14; // esi
  int i; // eax
  int v16; // [esp+0h] [ebp-38h]
  int v17; // [esp+4h] [ebp-34h]
  char v18; // [esp+Bh] [ebp-2Dh] BYREF
  uint8_t v19[4]; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block[4]; // [esp+10h] [ebp-28h] BYREF
  unsigned int v21; // [esp+20h] [ebp-18h]
  unsigned int v22; // [esp+24h] [ebp-14h]
  int v23; // [esp+28h] [ebp-10h]
  int v24; // [esp+34h] [ebp-4h]

  v23 = dword_796E50;
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"Etc/WarArea.etc") == 0 )
  {
    off_77F3FC(aCriticalError_14);
    return 0;
  }
  v2 = 0;
  v22 = 15;
  v21 = 0;
  LOBYTE(Block[0]) = 0;
  v24 = 0;
  v18 = 0;
  v17 = 0;
  v16 = -1;
  if ( (uint8_t)sub_443430(v19) != 0 )
  {
    while ( 1 )
    {
      v3 = v21;
      if ( v21 != 0 )
      {
        v4 = v21;
        if ( v21 >= 0xC )
          v4 = 12;
        v5 = (void **)Block[0];
        if ( v22 < 0x10 )
          v5 = Block;
        v6 = memcmp((const char *)v5, "[time table]", v4);
        if ( v6 != 0 || v21 < 0xC || (LOBYTE(v6) = v21 != 12, v6 != 0) )
        {
          v8 = a1;
        }
        else
        {
          v7 = sub_4423D0(&v18);
          v8 = a1;
          if ( v18 != 0 )
          {
            v9 = (int *)(a1 + 4 * v2 + 96);
            do
            {
              *v9 = v7;
              ++v2;
              ++v9;
              v7 = sub_4423D0(&v18);
            }
            while ( v18 != 0 );
          }
        }
        v3 = v21;
      }
      else
      {
        v8 = a1;
      }
      if ( v3 == 0 )
        goto LABEL_32;
      v10 = v3;
      if ( v3 >= 0xA )
        v10 = 10;
      v11 = (void **)Block[0];
      if ( v22 < 0x10 )
        v11 = Block;
      v12 = memcmp((const char *)v11, "[door fee]", v10);
      if ( v12 != 0 )
        break;
      if ( v3 < 0xA )
        break;
      LOBYTE(v12) = v3 != 10;
      if ( v12 != 0 )
        break;
      v13 = sub_4423D0(&v18);
      if ( v18 != 0 )
      {
        v14 = (int *)(a1 + 192);
        do
        {
          *v14++ = v13;
          v13 = sub_4423D0(&v18);
        }
        while ( v18 != 0 );
      }
LABEL_39:
      if ( (uint8_t)sub_443430(v19) == 0 )
        goto LABEL_40;
    }
    v8 = a1;
    v3 = v21;
LABEL_32:
    if ( sub_40BF00((std::_String_base *)v19, 0, v3, "[counter]", 9u) == 0 )
    {
      *(uint32_t *)(v8 + 236) = v2;
      v2 = 0;
      for ( i = sub_4423D0(&v18); v18 != 0; i = sub_4423D0(&v18) )
      {
        if ( i > v17 )
        {
          v17 = i;
          v16 = v2;
        }
        *(uint32_t *)(v8 + 4 * v2++) = i;
        if ( *(uint32_t *)(v8 + 236) == v2 )
          break;
      }
      *(uint32_t *)(v8 + 232) = v16;
    }
    goto LABEL_39;
  }
LABEL_40:
  if ( v22 >= 0x10 )
    j__free(Block[0]);
  return 1;
}


// ------------------------------------------------------------
// 0x4F9470 sub_4F9470
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F9470(uint32_t *this, int a2)
{
  char *v3; // ecx

  *this = *(uint32_t *)a2;
  *(this + 1) = *(uint32_t *)(a2 + 4);
  *(this + 2) = *(uint32_t *)(a2 + 8);
  *(this + 3) = *(uint32_t *)(a2 + 12);
  *((uint8_t *)this + 16) = *(uint8_t *)(a2 + 16);
  *(this + 5) = *(uint32_t *)(a2 + 20);
  *((uint8_t *)this + 24) = *(uint8_t *)(a2 + 24);
  *((uint16_t *)this + 13) = *(uint16_t *)(a2 + 26);
  *(this + 7) = *(uint32_t *)(a2 + 28);
  *(this + 8) = *(uint32_t *)(a2 + 32);
  *(this + 9) = *(uint32_t *)(a2 + 36);
  *(this + 10) = *(uint32_t *)(a2 + 40);
  *((uint8_t *)this + 44) = *(uint8_t *)(a2 + 44);
  v3 = (char *)(this + 12);
  *((uint32_t *)v3 + 6) = 15;
  *((uint32_t *)v3 + 5) = 0;
  v3[4] = 0;
  sub_4014D0((std::_String_base *)v3, a2 + 48, 0, -1);
  *(this + 19) = *(uint32_t *)(a2 + 76);
  *((uint8_t *)this + 80) = *(uint8_t *)(a2 + 80);
  return this;
}



// ------------------------------------------------------------
// 0x4F9500 sub_4F9500
// ------------------------------------------------------------
void /*noreturn*/ sub_4F9500()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0("invalid vector<T> subscript", 0x1Bu);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::out_of_range::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// ------------------------------------------------------------
// 0x4F9570 sub_4F9570
// ------------------------------------------------------------
void /*noreturn*/ sub_4F9570()
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
// 0x4F95E0 sub_4F95E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F95E0(uint32_t *this, int a2)
{
  *this = *(uint32_t *)a2;
  *(this + 1) = *(uint32_t *)(a2 + 4);
  *(this + 2) = *(uint32_t *)(a2 + 8);
  *(this + 3) = *(uint32_t *)(a2 + 12);
  *((uint8_t *)this + 16) = *(uint8_t *)(a2 + 16);
  *(this + 5) = *(uint32_t *)(a2 + 20);
  *((uint8_t *)this + 24) = *(uint8_t *)(a2 + 24);
  *((uint16_t *)this + 13) = *(uint16_t *)(a2 + 26);
  *(this + 7) = *(uint32_t *)(a2 + 28);
  *(this + 8) = *(uint32_t *)(a2 + 32);
  *(this + 9) = *(uint32_t *)(a2 + 36);
  *(this + 10) = *(uint32_t *)(a2 + 40);
  *((uint8_t *)this + 44) = *(uint8_t *)(a2 + 44);
  sub_4014D0((std::_String_base *)(this + 12), a2 + 48, 0, -1);
  *(this + 19) = *(uint32_t *)(a2 + 76);
  *((uint8_t *)this + 80) = *(uint8_t *)(a2 + 80);
  return this;
}



// ------------------------------------------------------------
// 0x4F9660 sub_4F9660
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F9660(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  uint32_t *v4; // edi

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 84;
    v4 -= 21;
    sub_4F95E0(v4, v3);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x4F96A0 sub_4F96A0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F96A0(int a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
      sub_4F9470(v3, a1);
    v3 += 21;
    LOBYTE(v7) = 0;
    a1 += 84;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x4F9750 sub_4F9750
// ------------------------------------------------------------
int /*thiscall*/ sub_4F9750(uint32_t *this, unsigned int a2)
{
  int v2; // esi

  v2 = *(this + 1);
  if ( v2 == 0 || (*(this + 2) - v2) / 44 <= a2 )
    sub_4F9500();
  return v2 + 44 * a2;
}



// ------------------------------------------------------------
// 0x4F9790 sub_4F9790
// ------------------------------------------------------------
void /*thiscall*/ sub_4F9790(int *this, char *a2, unsigned int a3, void *Block)
{
  int v5; // edi
  unsigned int v6; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // edi
  int v13; // eax
  unsigned int v14; // esi
  char *v15; // ecx
  int v17; // esi
  int v18; // [esp-18h] [ebp-60h]
  int v19; // [esp-Ch] [ebp-54h]
  unsigned int v20; // [esp-8h] [ebp-50h]
  int v21; // [esp+0h] [ebp-48h] BYREF
  uint32_t v22[12]; // [esp+Ch] [ebp-3Ch] BYREF
  int v23; // [esp+44h] [ebp-4h]
  char *v24; // [esp+50h] [ebp+8h]
  char *v25; // [esp+54h] [ebp+Ch]
  char *Blocka; // [esp+58h] [ebp+10h]
  char *Blockb; // [esp+58h] [ebp+10h]

  qmemcpy(v22, Block, 0x2Cu);
  v5 = *(this + 1);
  v22[11] = &v21;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 44;
  else
    v6 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - v5) / 44;
    else
      v8 = 0;
    if ( 97612893 - v8 < a3 )
      sub_4F9570(this);
    if ( v5 != 0 )
      v9 = (*(this + 2) - v5) / 44;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v15 = (char *)*(this + 2);
      Blockb = v15;
      if ( (v15 - a2) / 44 >= a3 )
      {
        v24 = &v15[-44 * a3];
        *(this + 2) = sub_508EA0(v24, v15, v15);
        sub_4F8D90(a2, v24, Blockb);
        sub_508E70(a2, &a2[44 * a3], v22);
      }
      else
      {
        sub_508EA0(a2, v15, &a2[44 * a3]);
        v20 = a3 - (*(this + 2) - (int)a2) / 44;
        v19 = *(this + 2);
        v23 = 2;
        sub_508EE0(v19, v20, v22);
        v17 = 44 * a3 + *(this + 2);
        *(this + 2) = v17;
        sub_508E70(a2, v17 - 44 * a3, v22);
      }
    }
    else
    {
      if ( 97612893 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(this + 2) - v5) / 44;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_527B90(this);
      v12 = 44 * v10;
      Blocka = (char *)operator new(44 * v10);
      v18 = *(this + 1);
      v23 = 0;
      v25 = (char *)sub_508EA0(v18, a2, Blocka);
      sub_4F8DF0(v25, (char *)a3, v22);
      sub_508EA0(a2, *(this + 2), &v25[44 * a3]);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 44;
      v14 = v13 + a3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v12];
      *(this + 2) = (int)&Blocka[44 * v14];
      *(this + 1) = (int)Blocka;
    }
  }
}



// ------------------------------------------------------------
// 0x4F9A40 sub_4F9A40
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4F9A40(int this, int Src, unsigned int a3, int *a4)
{
  int v5; // edx
  unsigned int result; // eax
  int v8; // ecx
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // eax
  char *v14; // eax
  void *v15; // eax
  int v16; // eax
  int v17; // ecx
  unsigned int v18; // edi
  uint8_t *v19; // eax
  unsigned int v21; // edx
  int v22; // ecx
  char *v23; // edi
  int v24; // edi
  char *v25; // [esp+8h] [ebp-4h]
  int Srcb; // [esp+14h] [ebp+8h]
  char *Srca; // [esp+14h] [ebp+8h]
  int v28; // [esp+18h] [ebp+Ch]
  int v29; // [esp+18h] [ebp+Ch]

  v5 = *(uint32_t *)(this + 4);
  a4 = (int *)*a4;
  if ( v5 != 0 )
    result = (*(uint32_t *)(this + 12) - v5) >> 2;
  else
    result = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v8 = 0;
    if ( 0x3FFFFFFF - v8 < a3 )
      sub_4F9570(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v9 = 0;
    if ( result >= a3 + v9 )
    {
      v19 = *(uint8_t **)(this + 8);
      v21 = (int)&v19[-Src] >> 2;
      v22 = 4 * a3;
      v29 = (int)v19;
      Srca = (char *)(4 * a3);
      if ( v21 >= a3 )
      {
        v24 = (int)&v19[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&v19[-v22], (int)v19, v19);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &a4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)v19, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), a3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &a4);
        v23 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = v23;
        return sub_49A9D0(Src, v23 - Srca, &a4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) >> 2;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(uint32_t *)(this + 8) - v5) >> 2;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v28 = 4 * v10;
      v25 = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      v14 = (char *)memcpy_0(v25, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&v14[Srcb], a3, &a4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
      v16 = *(uint32_t *)(this + 4);
      if ( v16 != 0 )
        v17 = (*(uint32_t *)(this + 8) - v16) >> 2;
      else
        v17 = 0;
      v18 = v17 + a3;
      if ( v16 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v25[v28];
      *(uint32_t *)(this + 8) = &v25[4 * v18];
      *(uint32_t *)(this + 4) = v25;
      return (unsigned int)v25;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4F9C20 sub_4F9C20
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F9C20(uint32_t *this, int a2)
{
  int v2; // eax
  int v5; // [esp-14h] [ebp-34h]
  int v6; // [esp-10h] [ebp-30h]
  int v7; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *v9; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(a2 + 4);
  v10 = &v8;
  v9 = this;
  if ( v2 != 0 )
    v2 = (*(uint32_t *)(a2 + 8) - v2) / 44;
  if ( (uint8_t)sub_452830(v2) != 0 )
  {
    v7 = *(this + 1);
    v6 = *(uint32_t *)(a2 + 8);
    v5 = *(uint32_t *)(a2 + 4);
    v11 = 0;
    *(this + 2) = sub_508EA0(v5, v6, v7);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4F9CC0 sub_4F9CC0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F9CC0(uint32_t *a1, uint32_t *a2, int a3)
{
  uint32_t *i; // esi
  uint32_t *result; // eax

  for ( i = a1; i != a2; i += 21 )
    result = sub_4F95E0(i, a3);
  return result;
}



// ------------------------------------------------------------
// 0x4F9CF0 sub_4F9CF0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F9CF0(int a1, int a2, uint32_t *a3)
{
  return sub_4F9660(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4F9D10 sub_4F9D10
// ------------------------------------------------------------
int /*thiscall*/ sub_4F9D10(int this, int a2)
{
  int v3; // eax
  unsigned int v4; // ecx
  char *v6; // ebx
  unsigned int v7; // eax
  int v8; // eax
  unsigned int v9; // eax
  char *v10; // edi
  int v11; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t *)(a2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(a2 + 8) - v3) / 44) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  v6 = *(char **)(this + 4);
  if ( v6 != nullptr )
    v7 = (*(uint32_t *)(this + 8) - (int)v6) / 44;
  else
    v7 = 0;
  if ( v4 > v7 )
  {
    if ( v6 != nullptr )
      v9 = (*(uint32_t *)(this + 12) - (int)v6) / 44;
    else
      v9 = 0;
    if ( v4 <= v9 )
    {
      v10 = (char *)(*(uint32_t *)(a2 + 4) + 44 * sub_527B90(this));
      sub_4F8DC0(*(char **)(a2 + 4), v10, v6);
      *(uint32_t *)(this + 8) = sub_508EA0(v10, *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 8));
      return this;
    }
    if ( v6 != nullptr )
      j__free(*(void **)(this + 4));
    v11 = sub_527B90(a2);
    if ( (uint8_t)sub_452830(v11) != 0 )
      *(uint32_t *)(this + 8) = sub_433CF0(*(uint32_t *)(a2 + 4), *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  sub_4F8DC0(*(char **)(a2 + 4), *(char **)(a2 + 8), *(char **)(this + 4));
  v8 = *(uint32_t *)(a2 + 4);
  if ( v8 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 44 * ((*(uint32_t *)(a2 + 8) - v8) / 44);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x4F9E90 sub_4F9E90
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F9E90(uint32_t *a1, int a2, int a3)
{
  uint32_t *v3; // esi
  uint32_t *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v7 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
      result = sub_4F9470(v3, a3);
    --a2;
    v3 += 21;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F9F40 sub_4F9F40
// ------------------------------------------------------------
char /*thiscall*/ sub_4F9F40(
        uint32_t *this,
        uint32_t *a2,
        uint8_t a3,
        uint8_t a4,
        uint8_t a5,
        int a6)
{
  unsigned int v7; // eax
  unsigned int v9; // eax
  uint64_t v10; // rax

  v7 = *(this + 1);
  if ( v7 != 0 )
    v7 = (int)(*(this + 2) - v7) / 44;
  if ( a5 >= v7 || a3 >= 5u || a6 >= 18 || a6 < 8 || a4 >= 0x64u )
    return 0;
  qmemcpy(a2, (const void *)sub_4F9750(this, a5), 0x2Cu);
  v9 = *(this + a4 + 30);
  a2[10] = v9;
  v10 = (uint64_t)((double)v9 * *((float *)this + a6 + 7));
  a2[10] = v10;
  a2[10] = (uint64_t)((double)(unsigned int)v10 * *((float *)this + a3 + 25));
  return 1;
}



// ------------------------------------------------------------
// 0x4FA000 sub_4FA000
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FA000(int *this, uint32_t *a2, char *a3, void *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 44 != 0 )
    v6 = (int)&a3[-v5] / 44;
  else
    v6 = 0;
  sub_4F9790(this, a3, 1u, Block);
  *a2 = *(this + 1) + 44 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4FA070 sub_4FA070
// ------------------------------------------------------------
uint16_t */*cdecl*/ sub_4FA070(int a1, int a2, uint16_t *a3)
{
  int v3; // esi
  uint16_t *v4; // edi
  int16_t v5; // ax

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = *(uint16_t *)(v3 - 20);
    v3 -= 20;
    v4 -= 10;
    *v4 = v5;
    v4[1] = *(uint16_t *)(v3 + 2);
    sub_4F9D10((int)(v4 + 2), v3 + 4);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x4FA0C0 sub_4FA0C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FA0C0(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 7) = 1065353216;
  *(this + 8) = 1065353216;
  *(this + 9) = 1065353216;
  *(this + 10) = 1065353216;
  *(this + 11) = 1065353216;
  *(this + 12) = 1065353216;
  *(this + 13) = 1065353216;
  *(this + 14) = 1065353216;
  *(this + 15) = 1065353216;
  *(this + 16) = 1065353216;
  *(this + 17) = 1065353216;
  *(this + 18) = 1065353216;
  *(this + 19) = 1065353216;
  *(this + 20) = 1065353216;
  *(this + 21) = 1065353216;
  *(this + 22) = 1065353216;
  *(this + 23) = 1065353216;
  *(this + 24) = 1065353216;
  *(this + 25) = 1065353216;
  *(this + 26) = 1065353216;
  *(this + 27) = 1065353216;
  *(this + 28) = 1065353216;
  *(this + 29) = 1065353216;
  return this;
}



// ------------------------------------------------------------
// 0x4FA120 sub_4FA120
// ------------------------------------------------------------
char */*thiscall*/ sub_4FA120(int this, void *Block)
{
  int v3; // edi
  unsigned int v4; // ecx
  char *v5; // edi
  char *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 44;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 44 )
    return (char *)sub_4FA000((int *)this, &Block, *(char **)(this + 8), Block);
  v5 = *(char **)(this + 8);
  result = sub_4F8DF0(v5, (char *)1, Block);
  *(uint32_t *)(this + 8) = v5 + 44;
  return result;
}



// ------------------------------------------------------------
// 0x4FA1B0 sub_4FA1B0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4FA1B0(uint32_t *a1, int a2, int a3)
{
  sub_4F9E90(a1, a2, a3);
  return &a1[21 * a2];
}



// ------------------------------------------------------------
// 0x4FA1E0 sub_4FA1E0
// ------------------------------------------------------------
int /*stdcall*/ sub_4FA1E0(int a1, int a2)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 84 )
    result = sub_44C0C0(i);
  return result;
}



// ------------------------------------------------------------
// 0x4FA210 sub_4FA210
// ------------------------------------------------------------
void /*thiscall*/ sub_4FA210(int *this, int a2, unsigned int a3, int a4)
{
  int v5; // ebx
  unsigned int v6; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  char *v12; // ebx
  int v13; // eax
  unsigned int v14; // edi
  int v15; // eax
  int v16; // ecx
  int v18; // edi
  int v19; // [esp-18h] [ebp-98h]
  int v20; // [esp-10h] [ebp-90h]
  int v21; // [esp-Ch] [ebp-8Ch]
  unsigned int v22; // [esp-8h] [ebp-88h]
  int v23; // [esp+0h] [ebp-80h] BYREF
  void *Block; // [esp+Ch] [ebp-74h]
  int *v25; // [esp+10h] [ebp-70h]
  char *v26; // [esp+14h] [ebp-6Ch]
  uint8_t v27[52]; // [esp+18h] [ebp-68h] BYREF
  void *v28; // [esp+4Ch] [ebp-34h]
  unsigned int v29; // [esp+60h] [ebp-20h]
  int v30; // [esp+6Ch] [ebp-14h]
  int *v31; // [esp+70h] [ebp-10h]
  int v32; // [esp+7Ch] [ebp-4h]
  int v33; // [esp+88h] [ebp+8h]
  int v34; // [esp+8Ch] [ebp+Ch]
  int v35; // [esp+90h] [ebp+10h]

  v30 = dword_796E50;
  v31 = &v23;
  v25 = this;
  sub_4F9470(a4);
  v5 = *(this + 1);
  v6 = 0;
  v32 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 84;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - v5) / 84;
    else
      v8 = 0;
    if ( 51130563 - v8 < a3 )
      sub_4F9570(this);
    if ( v5 != 0 )
      v9 = (*(this + 2) - v5) / 84;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = *(this + 2);
      v35 = v16;
      if ( (v16 - a2) / 84 >= a3 )
      {
        v33 = v16 - 84 * a3;
        *(this + 2) = sub_4F96A0(v33, v16, v16);
        sub_4F9CF0(a2, v33, v35);
        sub_4F9CC0(a2, a2 + 84 * a3, v27);
      }
      else
      {
        sub_4F96A0(a2, v16, a2 + 84 * a3);
        v22 = a3 - (*(this + 2) - a2) / 84;
        v21 = *(this + 2);
        LOBYTE(v32) = 3;
        sub_4FA1B0(v21, v22, v27);
        v18 = 84 * a3 + *(this + 2);
        *(this + 2) = v18;
        v32 = 0;
        sub_4F9CC0(a2, v18 - 84 * a3, v27);
      }
    }
    else
    {
      if ( 51130563 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(this + 2) - v5) / 84;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_4F8D70(this);
      v34 = 84 * v10;
      v12 = (char *)operator new(84 * v10);
      v19 = *(this + 1);
      Block = v12;
      v26 = v12;
      LOBYTE(v32) = 1;
      v26 = (char *)sub_4F96A0(v19, a2, v12);
      sub_4F9E90(v26, a3, v27);
      v20 = *(this + 2);
      v26 += 84 * a3;
      sub_4F96A0(a2, v20, v26);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 84;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_4FA1E0(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v34];
      *(this + 2) = (int)&v12[84 * v14];
      *(this + 1) = (int)v12;
    }
  }
  if ( v29 >= 0x10 )
    j__free(v28);
}


// ------------------------------------------------------------
// 0x4FA510 sub_4FA510
// ------------------------------------------------------------
uint16_t */*cdecl*/ sub_4FA510(uint16_t *a1, uint16_t *a2, uint16_t *a3)
{
  uint16_t *result; // eax
  uint16_t *i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 10 )
  {
    *i = *a3;
    i[1] = a3[1];
    sub_4F9D10((int)(i + 2), (int)(a3 + 2));
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FA550 sub_4FA550
// ------------------------------------------------------------
uint16_t */*cdecl*/ sub_4FA550(int a1, int a2, uint16_t *a3)
{
  return sub_4FA070(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4FA570 sub_4FA570
// ------------------------------------------------------------
int /*cdecl*/ sub_4FA570(uint16_t *a1, uint16_t *a2, int a3)
{
  int v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != 0 )
    {
      *(uint16_t *)v3 = *a1;
      *(uint16_t *)(v3 + 2) = a1[1];
      sub_4F9C20((uint32_t *)(v3 + 4), (int)(a1 + 2));
    }
    v3 += 20;
    LOBYTE(v7) = 0;
    a1 += 10;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x4FA630 sub_4FA630 —— 表情(emoticon)标签表解析器
//   标签族：[EMOTICON TAG]（$END 结尾的标签映射表）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FA630(int a1)
{
  char result; // al
  void ***v2; // edi
  void **v3; // esi
  void ***v4; // ebx
  void **v5; // edx
  unsigned int v6; // ecx
  void **v7; // esi
  void **i; // [esp+0h] [ebp-38h]
  void ***v9; // [esp+4h] [ebp-34h]
  void *v10; // [esp+8h] [ebp-30h] BYREF
  char v11[4]; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+10h] [ebp-28h]
  unsigned int v13; // [esp+20h] [ebp-18h]
  unsigned int v14; // [esp+24h] [ebp-14h]
  int v15; // [esp+28h] [ebp-10h]
  int v16; // [esp+34h] [ebp-4h]

  v15 = dword_796E50;
  result = sub_442A10((char)szPassword, a1);
  if ( result != 0 )
  {
    v14 = 15;
    v13 = 0;
    LOBYTE(Block) = 0;
    v16 = 0;
    v10 = nullptr;
    sub_41BFE0(&v10, szPassword);
    LOBYTE(v16) = 1;
    while ( (uint8_t)sub_443430(v11) != 0 )
    {
      if ( sub_40BF00((std::_String_base *)v11, 0, v13, "[EMOTICON TAG]", 0xEu) == 0 )
      {
        v2 = (void ***)&unk_9B7D24;
        v9 = (void ***)&unk_9B7D24;
        do
        {
          v3 = *v2;
          v4 = v2 - 1;
          if ( *v2 != nullptr )
          {
            for ( i = v2[1]; v3 != i; ++v3 )
              sub_41B010(v3);
            j__free(*v2);
          }
          *v2 = nullptr;
          v4[2] = nullptr;
          v4[3] = nullptr;
          if ( sub_442E10() != 0 )
          {
            while ( 1 )
            {
              v5 = *v2;
              v6 = *v2 != nullptr ? v4[2] - v5 : 0;
              if ( v5 != nullptr && v6 < v4[3] - v5 )
              {
                v7 = v4[2];
                sub_41FFE0(v7, 1, &v10);
                v4[2] = v7 + 1;
              }
              else
              {
                sub_4206D0(v4[2], 1, &v10);
              }
              if ( strcmp((const char *)sub_41ACF0(&v10), "$END") == 0 || sub_442E10() == 0 )
                break;
              v2 = v9;
            }
            v2 = v9;
          }
          v2 += 4;
          v9 = v2;
        }
        while ( (int)v2 < (int)&dword_9B7E94 );
      }
    }
    LOBYTE(v16) = 0;
    sub_41B010(&v10);
    if ( v14 >= 0x10 )
      j__free(Block);
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FA820 sub_4FA820 —— 玩家俚语/屏蔽词表解析器
//   标签族：[SLANG]。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FA820(int a1, uint32_t *a2)
{
  char result; // al
  int v3; // ecx
  const char *p_Block; // esi
  int v5; // eax
  int v6; // edx
  unsigned int v7; // ecx
  int v8; // esi
  int v9; // edx
  unsigned int v10; // ecx
  int v11; // esi
  void *v12; // [esp+0h] [ebp-34h] BYREF
  void *v13; // [esp+4h] [ebp-30h] BYREF
  uint8_t v14[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h] BYREF
  unsigned int v16; // [esp+1Ch] [ebp-18h]
  unsigned int v17; // [esp+20h] [ebp-14h]
  int v18; // [esp+24h] [ebp-10h]
  int v19; // [esp+30h] [ebp-4h]

  v18 = dword_796E50;
  result = sub_442A10((char)szPassword, a1);
  if ( result != 0 )
  {
    v17 = 15;
    v16 = 0;
    LOBYTE(Block) = 0;
    v19 = 0;
    v12 = nullptr;
    sub_41BFE0(&v12, szPassword);
    LOBYTE(v19) = 1;
    v13 = nullptr;
    sub_41BFE0(&v13, szPassword);
    LOBYTE(v19) = 2;
    while ( (uint8_t)sub_443430(v14) != 0 )
    {
      if ( v16 != 0 )
      {
        v3 = v16;
        if ( v16 >= 7 )
          v3 = 7;
        p_Block = (const char *)Block;
        if ( v17 < 0x10 )
          p_Block = (const char *)&Block;
        v5 = memcmp(p_Block, "[SLANG]", v3);
        if ( v5 == 0 && v16 >= 7 )
        {
          LOBYTE(v5) = v16 != 7;
          if ( v5 == 0 && sub_442E10() != 0 )
          {
            do
            {
              if ( sub_442E10() == 0 )
                break;
              v6 = a2[1];
              v7 = v6 != 0 ? (a2[2] - v6) >> 2 : 0;
              if ( v6 != 0 && v7 < (a2[3] - v6) >> 2 )
              {
                v8 = a2[2];
                sub_41FFE0(v8, 1, &v12);
                a2[2] = v8 + 4;
              }
              else
              {
                sub_4206D0(a2[2], 1, &v12);
              }
              v9 = a2[1];
              v10 = v9 != 0 ? (a2[2] - v9) >> 2 : 0;
              if ( v9 != 0 && v10 < (a2[3] - v9) >> 2 )
              {
                v11 = a2[2];
                sub_41FFE0(v11, 1, &v13);
                a2[2] = v11 + 4;
              }
              else
              {
                sub_4206D0(a2[2], 1, &v13);
              }
            }
            while ( sub_442E10() != 0 );
          }
        }
      }
    }
    LOBYTE(v19) = 1;
    sub_41B010(&v13);
    LOBYTE(v19) = 0;
    sub_41B010(&v12);
    if ( v17 >= 0x10 )
      j__free(Block);
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FAA40 sub_4FAA40 —— 封印(解封)概率表解析器（importResealTable）
//   标签族：[rarity weight]（稀有度权重表）/[extended rarity weight]（扩展表）/[grade]。
//   校验失败 → "importResealTable - invalid extended rarity table"/"... rarity table"。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FAA40(int a1, int a2)
{
  char result; // al
  int *v3; // esi
  int v4; // ebx
  int v5; // eax
  int *v6; // esi
  int v7; // ebx
  int v8; // eax
  int i; // eax
  int v10; // esi
  unsigned int v11; // edx
  int *v12; // ecx
  char v13; // [esp+2h] [ebp-6Eh] BYREF
  char v14; // [esp+3h] [ebp-6Dh] BYREF
  int v15; // [esp+4h] [ebp-6Ch] BYREF
  uint8_t v16[21]; // [esp+Bh] [ebp-65h] BYREF
  int v17; // [esp+20h] [ebp-50h]
  int v18; // [esp+24h] [ebp-4Ch]
  char v19; // [esp+2Ch] [ebp-44h]
  int v20; // [esp+3Ch] [ebp-34h]
  int v21; // [esp+40h] [ebp-30h]
  uint8_t v22[4]; // [esp+44h] [ebp-2Ch] BYREF
  void *Block; // [esp+48h] [ebp-28h]
  unsigned int v24; // [esp+58h] [ebp-18h]
  unsigned int v25; // [esp+5Ch] [ebp-14h]
  int v26; // [esp+60h] [ebp-10h]
  int v27; // [esp+6Ch] [ebp-4h]

  v26 = dword_796E50;
  result = sub_442A10((char)szPassword, a1);
  if ( result != 0 )
  {
    v25 = 15;
    v24 = 0;
    LOBYTE(Block) = 0;
    v27 = 2;
    v18 = 15;
    v17 = 0;
    v16[5] = 0;
    v21 = 15;
    v20 = 0;
    v19 = 0;
    while ( (uint8_t)sub_443430(v22) != 0 )
    {
      if ( sub_40BF00((std::_String_base *)v22, 0, v24, "[rarity weight]", 0xFu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v22, 0, v24, "[extended rarity weight]", 0x18u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)v22, 0, v24, "[grade]", 7u) == 0 )
          {
            for ( i = sub_4423D0(v16); v16[0] != 0; i = sub_4423D0(v16) )
            {
              v10 = *(uint32_t *)(a2 + 4);
              v15 = i;
              if ( v10 != 0 )
                v11 = (*(uint32_t *)(a2 + 8) - v10) >> 2;
              else
                v11 = 0;
              if ( v10 != 0 && v11 < (*(uint32_t *)(a2 + 12) - v10) >> 2 )
              {
                v12 = *(int **)(a2 + 8);
                *v12 = i;
                *(uint32_t *)(a2 + 8) = v12 + 1;
              }
              else
              {
                sub_4F9A40(*(void **)(a2 + 8), 1, (int)&v15);
              }
            }
          }
        }
        else
        {
          v6 = (int *)(a2 + 36);
          v15 = 5;
          do
          {
            v7 = sub_4423D0(&v13);
            if ( v13 == 0 )
              off_77F3FC("importResealTable - invalid extended rarity table");
            v8 = v15;
            *v6++ = v7;
            v15 = v8 - 1;
          }
          while ( v8 != 1 );
        }
      }
      else
      {
        v3 = (int *)(a2 + 16);
        v15 = 5;
        do
        {
          v4 = sub_4423D0(&v14);
          if ( v14 == 0 )
            off_77F3FC("importResealTable - invalid rarity table");
          v5 = v15;
          *v3++ = v4;
          v15 = v5 - 1;
        }
        while ( v5 != 1 );
      }
    }
    if ( v25 >= 0x10 )
      j__free(Block);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FAC40 sub_4FAC40 —— 强化(upgrade)费用表解析器（importUpgradeTable）
//   标签族：[table]（费用表本体）/[rarity]（稀有度分组）/[type]（类型分组）/[cost]/[notice]。
//   校验失败 → "importUpgradeTable - invalid notice tag"/"... gold table"/"... type table"。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FAC40(int a1, int a2)
{
  char result; // al
  float *v3; // esi
  int k; // edi
  float *v5; // esi
  int j; // edi
  int *v7; // esi
  int i; // ebx
  int v9; // edi
  int v10; // [esp+0h] [ebp-9Ch] BYREF
  int v11; // [esp+4h] [ebp-98h]
  int v12; // [esp+8h] [ebp-94h]
  int v13; // [esp+Ch] [ebp-90h]
  int v14; // [esp+10h] [ebp-8Ch]
  int v15; // [esp+14h] [ebp-88h]
  int v16; // [esp+18h] [ebp-84h]
  char v17; // [esp+1Ch] [ebp-80h]
  char v18; // [esp+1Dh] [ebp-7Fh]
  int v19; // [esp+20h] [ebp-7Ch]
  int v20; // [esp+24h] [ebp-78h]
  int v21; // [esp+28h] [ebp-74h]
  float v22; // [esp+2Ch] [ebp-70h]
  char v23; // [esp+33h] [ebp-69h] BYREF
  char v24; // [esp+34h] [ebp-68h] BYREF
  char v25; // [esp+35h] [ebp-67h] BYREF
  char v26; // [esp+36h] [ebp-66h] BYREF
  uint8_t v27[21]; // [esp+37h] [ebp-65h] BYREF
  int v28; // [esp+4Ch] [ebp-50h]
  int v29; // [esp+50h] [ebp-4Ch]
  char v30; // [esp+58h] [ebp-44h]
  int v31; // [esp+68h] [ebp-34h]
  int v32; // [esp+6Ch] [ebp-30h]
  uint8_t v33[4]; // [esp+70h] [ebp-2Ch] BYREF
  void *Block; // [esp+74h] [ebp-28h]
  unsigned int v35; // [esp+84h] [ebp-18h]
  unsigned int v36; // [esp+88h] [ebp-14h]
  int v37; // [esp+8Ch] [ebp-10h]
  int v38; // [esp+98h] [ebp-4h]

  v37 = dword_796E50;
  result = sub_442A10((char)szPassword, a1);
  if ( result != 0 )
  {
    v36 = 15;
    v35 = 0;
    LOBYTE(Block) = 0;
    v38 = 2;
    v29 = 15;
    v28 = 0;
    v27[5] = 0;
    v32 = 15;
    v31 = 0;
    v30 = 0;
    while ( (uint8_t)sub_443430(v33) != 0 )
    {
      if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[table]", 7u) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[rarity]", 8u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[type]", 6u) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[cost]", 6u) != 0 )
            {
              if ( (uint8_t)sub_423300(v33, "[notice]") != 0 )
              {
                v22 = COERCE_FLOAT(sub_4423D0(&v26));
                if ( v26 == 0 )
                  off_77F3FC("importUpgradeTable - invalid notice tag");
                *(uint8_t *)(a2 + 520) = LOBYTE(v22);
              }
            }
            else
            {
              v7 = (int *)(a2 + 120);
              for ( i = 100; i != 0; --i )
              {
                v9 = sub_4423D0(&v25);
                if ( v25 == 0 )
                  off_77F3FC("importUpgradeTable - invalid gold table");
                *v7++ = v9;
              }
            }
          }
          else
          {
            v5 = (float *)(a2 + 60);
            for ( j = 10; j != 0; --j )
            {
              v22 = sub_442480(&v23);
              if ( v23 == 0 )
                off_77F3FC("importUpgradeTable - invalid type table");
              *v5++ = v22;
            }
          }
        }
        else
        {
          v3 = (float *)(a2 + 100);
          for ( k = 5; k != 0; --k )
          {
            v22 = sub_442480(&v24);
            if ( v24 == 0 )
              off_77F3FC("importUpgradeTable - invalid rarity table");
            *v3++ = v22;
          }
        }
      }
      else
      {
        if ( *(uint32_t *)(a2 + 4) != 0 )
          j__free(*(void **)(a2 + 4));
        *(uint32_t *)(a2 + 4) = 0;
        *(uint32_t *)(a2 + 8) = 0;
        *(uint32_t *)(a2 + 12) = 0;
        while ( 1 )
        {
          v11 = 0;
          v12 = 0;
          v16 = 0;
          v17 = 0;
          v19 = 0;
          v20 = 0;
          v21 = 0;
          v10 = sub_4423D0(v27);
          if ( v27[0] == 0 )
            break;
          v13 = 0;
          v11 = sub_4423D0(v27);
          if ( v27[0] == 0 )
            break;
          v14 = 0;
          v12 = sub_4423D0(v27);
          if ( v27[0] == 0 )
            break;
          v15 = 0;
          v16 = sub_4423D0(v27);
          v17 = sub_4423D0(v27);
          v18 = sub_4423D0(v27);
          v19 = sub_4423D0(v27);
          v20 = sub_4423D0(v27);
          v21 = 0;
          sub_4FA120(&v10);
        }
      }
    }
    if ( v36 >= 0x10 )
      j__free(Block);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FAF80 sub_4FAF80
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FAF80(int *this, uint32_t *a2, char *a3, int a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 84 != 0 )
    v6 = (int)&a3[-v5] / 84;
  else
    v6 = 0;
  sub_4FA210(this, a3, 1u, a4);
  *a2 = *(this + 1) + 84 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4FAFF0 sub_4FAFF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4FAFF0(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 84 )
      sub_44C0C0(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4FB030 sub_4FB030
// ------------------------------------------------------------
void /*cdecl*/ sub_4FB030(int a1, int a2, uint16_t *a3)
{
  int v3; // esi
  uint32_t v5[5]; // [esp+0h] [ebp-20h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v5[4] = v5;
  v5[3] = a1;
  v6 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v6) = 1;
    if ( v3 != 0 )
    {
      *(uint16_t *)v3 = *a3;
      *(uint16_t *)(v3 + 2) = a3[1];
      sub_4F9C20((uint32_t *)(v3 + 4), (int)(a3 + 2));
    }
    --a2;
    v3 += 20;
    LOBYTE(v6) = 0;
  }
}



// ------------------------------------------------------------
// 0x4FB0F0 sub_4FB0F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FB0F0(int this, int a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  uint32_t *v5; // edi
  uint32_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 84;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 84 )
    return sub_4FAF80((int *)this, &a2, *(char **)(this + 8), a2);
  v5 = *(uint32_t **)(this + 8);
  result = sub_4F9E90(v5, 1, a2);
  *(uint32_t *)(this + 8) = v5 + 21;
  return result;
}



// ------------------------------------------------------------
// 0x4FB180 sub_4FB180 —— 时装(avatar)分配表解析器
//   标签族：部位分配 [npc info]/[avatar]/[coin]/[item]。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FB180(int a1, int a2)
{
  char result; // al
  int m; // esi
  int k; // esi
  int j; // esi
  int i; // esi
  char v7; // [esp+3h] [ebp-145h] BYREF
  uint32_t v8[6]; // [esp+4h] [ebp-144h] BYREF
  char v9; // [esp+1Ch] [ebp-12Ch]
  int16_t v10; // [esp+1Eh] [ebp-12Ah]
  char v11; // [esp+30h] [ebp-118h]
  void *Block; // [esp+38h] [ebp-110h]
  int v13; // [esp+48h] [ebp-100h]
  unsigned int v14; // [esp+4Ch] [ebp-FCh]
  uint32_t v15[8]; // [esp+58h] [ebp-F0h] BYREF
  int v16; // [esp+78h] [ebp-D0h]
  int v17; // [esp+7Ch] [ebp-CCh]
  int v18; // [esp+80h] [ebp-C8h]
  void *v19; // [esp+8Ch] [ebp-BCh]
  int v20; // [esp+9Ch] [ebp-ACh]
  unsigned int v21; // [esp+A0h] [ebp-A8h]
  uint32_t v22[6]; // [esp+ACh] [ebp-9Ch] BYREF
  char v23; // [esp+C4h] [ebp-84h]
  int v24; // [esp+CCh] [ebp-7Ch]
  int v25; // [esp+D0h] [ebp-78h]
  int v26; // [esp+D4h] [ebp-74h]
  void *v27; // [esp+E0h] [ebp-68h]
  int v28; // [esp+F0h] [ebp-58h]
  unsigned int v29; // [esp+F4h] [ebp-54h]
  void *v30; // [esp+104h] [ebp-44h]
  int v31; // [esp+114h] [ebp-34h]
  unsigned int v32; // [esp+118h] [ebp-30h]
  uint8_t v33[4]; // [esp+11Ch] [ebp-2Ch] BYREF
  void *v34; // [esp+120h] [ebp-28h]
  unsigned int v35; // [esp+130h] [ebp-18h]
  unsigned int v36; // [esp+134h] [ebp-14h]
  int v37; // [esp+138h] [ebp-10h]
  int v38; // [esp+144h] [ebp-4h]

  v37 = dword_796E50;
  result = sub_442A10((char)szPassword, a1);
  if ( result != 0 )
  {
    v36 = 15;
    v35 = 0;
    LOBYTE(v34) = 0;
    v38 = 1;
    v32 = 15;
    v31 = 0;
    LOBYTE(v30) = 0;
    v7 = 0;
    while ( (uint8_t)sub_443430(v33) != 0 )
    {
      sub_442B20(v33);
      if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[npc info]", 0xAu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[avatar]", 8u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[coin]", 6u) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[item]", 6u) == 0 )
            {
              sub_4FAFF0(a2 + 32);
              for ( i = sub_4423D0(&v7); v7 != 0; i = sub_4423D0(&v7) )
              {
                sub_44CEA0(v22);
                LOBYTE(v38) = 4;
                v22[0] = i;
                v22[3] = sub_4423D0(nullptr);
                v22[5] = sub_4423D0(nullptr);
                v24 = sub_4423D0(nullptr);
                v25 = sub_4423D0(nullptr);
                v26 = sub_4423D0(nullptr);
                sub_443370();
                v23 = sub_4423D0(nullptr);
                v22[2] = sub_4423D0(nullptr);
                v24 += 10 * v26;
                v26 = 0;
                v22[1] = 2;
                sub_4FB0F0(v22);
                LOBYTE(v38) = 1;
                if ( v29 >= 0x10 )
                  j__free(v27);
                v29 = 15;
                v28 = 0;
                LOBYTE(v27) = 0;
              }
            }
          }
          else
          {
            sub_4FAFF0(a2 + 16);
            for ( j = sub_4423D0(&v7); v7 != 0; j = sub_4423D0(&v7) )
            {
              sub_44CEA0(v15);
              LOBYTE(v38) = 3;
              v15[0] = j;
              v15[3] = sub_4423D0(nullptr);
              v15[5] = sub_4423D0(nullptr);
              v16 = sub_4423D0(nullptr);
              v17 = sub_4423D0(nullptr);
              v18 = sub_4423D0(nullptr);
              sub_443370();
              v15[2] = sub_4423D0(nullptr);
              v16 += 10 * v18;
              v18 = 0;
              v15[1] = 1;
              sub_4FB0F0(v15);
              LOBYTE(v38) = 1;
              if ( v21 >= 0x10 )
                j__free(v19);
              v21 = 15;
              v20 = 0;
              LOBYTE(v19) = 0;
            }
          }
        }
        else
        {
          sub_4FAFF0(a2);
          for ( k = sub_4423D0(&v7); v7 != 0; k = sub_4423D0(&v7) )
          {
            sub_44CEA0(v8);
            LOBYTE(v38) = 2;
            v8[0] = k;
            v8[3] = sub_4423D0(nullptr);
            v10 = sub_4423D0(nullptr);
            v9 = sub_4423D0(nullptr);
            v8[2] = sub_4423D0(nullptr);
            v11 = sub_4423D0(nullptr);
            v8[1] = 0;
            v8[5] = 1;
            sub_4FB0F0(v8);
            LOBYTE(v38) = 1;
            if ( v14 >= 0x10 )
              j__free(Block);
            v14 = 15;
            v13 = 0;
            LOBYTE(Block) = 0;
          }
        }
      }
      else
      {
        for ( m = 4; m != 0; --m )
        {
          sub_443370();
          sub_4423D0(nullptr);
        }
      }
    }
    if ( v32 >= 0x10 )
      j__free(v30);
    v32 = 15;
    v31 = 0;
    LOBYTE(v30) = 0;
    if ( v36 >= 0x10 )
      j__free(v34);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FB630 sub_4FB630
// ------------------------------------------------------------
int /*stdcall*/ sub_4FB630(int a1, int a2, uint16_t *a3)
{
  sub_4FB030(a1, a2, a3);
  return a1 + 20 * a2;
}



// ------------------------------------------------------------
// 0x4FB660 sub_4FB660
// ------------------------------------------------------------
void /*thiscall*/ sub_4FB660(int *this, char *a2, unsigned int a3, int16_t *a4)
{
  int16_t v4; // dx
  int16_t v6; // cx
  int v7; // ebx
  unsigned int v8; // ecx
  int v10; // eax
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // eax
  char *v14; // ebx
  int v15; // eax
  unsigned int v16; // edi
  void *v17; // eax
  char *v18; // ecx
  int v20; // edi
  uint16_t *v21; // [esp-18h] [ebp-50h]
  int v22; // [esp-Ch] [ebp-44h]
  unsigned int v23; // [esp-8h] [ebp-40h]
  int v24; // [esp+0h] [ebp-38h] BYREF
  uint16_t v25[2]; // [esp+Ch] [ebp-2Ch] BYREF
  int v26; // [esp+10h] [ebp-28h] BYREF
  void *v27; // [esp+14h] [ebp-24h]
  void *Block; // [esp+20h] [ebp-18h]
  int *v29; // [esp+24h] [ebp-14h]
  int *v30; // [esp+28h] [ebp-10h]
  int v31; // [esp+34h] [ebp-4h]
  char *v32; // [esp+40h] [ebp+8h]
  int v33; // [esp+44h] [ebp+Ch]
  int v34; // [esp+48h] [ebp+10h]
  char *v35; // [esp+48h] [ebp+10h]

  v4 = a4[1];
  v6 = *a4;
  v30 = &v24;
  v25[0] = v6;
  v29 = this;
  v25[1] = v4;
  sub_4F9C20(&v26, (int)(a4 + 2));
  v7 = *(this + 1);
  v8 = 0;
  v31 = 0;
  if ( v7 != 0 )
    v8 = (*(this + 3) - v7) / 20;
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v10 = (*(this + 2) - v7) / 20;
    else
      v10 = 0;
    if ( 214748364 - v10 < a3 )
      sub_42CB90(this);
    if ( v7 != 0 )
      v11 = (*(this + 2) - v7) / 20;
    else
      v11 = 0;
    if ( v8 >= a3 + v11 )
    {
      v18 = (char *)*(this + 2);
      v35 = v18;
      if ( (v18 - a2) / 20 >= a3 )
      {
        v32 = &v18[-20 * a3];
        *(this + 2) = sub_4FA570(v32, v18, (int)v18);
        sub_4FA550(a2, v32, v35);
        sub_4FA510(a2, &a2[20 * a3], v25);
      }
      else
      {
        sub_4FA570(a2, v18, (int)&a2[20 * a3]);
        v23 = a3 - (*(this + 2) - (int)a2) / 20;
        v22 = *(this + 2);
        LOBYTE(v31) = 3;
        sub_4FB630(v22, v23, v25);
        v20 = 20 * a3 + *(this + 2);
        *(this + 2) = v20;
        v31 = 0;
        sub_4FA510(a2, v20 - 20 * a3, v25);
      }
    }
    else
    {
      if ( 214748364 - (v8 >> 1) >= v8 )
        v12 = (v8 >> 1) + v8;
      else
        v12 = 0;
      if ( v7 != 0 )
        v13 = (*(this + 2) - v7) / 20;
      else
        v13 = 0;
      if ( v12 < a3 + v13 )
        v12 = a3 + sub_45E580(this);
      v34 = 20 * v12;
      v14 = (char *)operator new(20 * v12);
      v21 = (uint16_t *)*(this + 1);
      Block = v14;
      LOBYTE(v31) = 1;
      v33 = sub_4FA570(v21, a2, (int)v14);
      sub_4FB030(v33, a3, v25);
      sub_4FA570(a2, (uint16_t *)*(this + 2), v33 + 20 * a3);
      v15 = *(this + 1);
      if ( v15 != 0 )
        v15 = (*(this + 2) - v15) / 20;
      v16 = v15 + a3;
      v17 = (void *)*(this + 1);
      if ( v17 != nullptr )
      {
        sub_42E670(v17, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v14[v34];
      *(this + 2) = (int)&v14[20 * v16];
      *(this + 1) = (int)v14;
    }
  }
  if ( v27 != nullptr )
    j__free(v27);
}


// ------------------------------------------------------------
// 0x4FB970 sub_4FB970
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FB970(int *this, uint32_t *a2, char *a3, int16_t *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 20 != 0 )
    v6 = (int)&a3[-v5] / 20;
  else
    v6 = 0;
  sub_4FB660(this, a3, 1u, a4);
  *a2 = *(this + 1) + 20 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4FB9E0 sub_4FB9E0
// ------------------------------------------------------------
void /*thiscall*/ sub_4FB9E0(int *this, int16_t *a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 20;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(this + 3) - v3) / 20 )
  {
    v5 = *(this + 2);
    sub_4FB030(v5, 1, a2);
    *(this + 2) = v5 + 20;
  }
  else
  {
    sub_4FB970(this, &a2, (char *)*(this + 2), a2);
  }
}



// ------------------------------------------------------------
// 0x4FBA70 sub_4FBA70 —— 战场平衡表解析器（etc/WarRoomEqualize.tbl）
//   标签族：[warroom equalization]（战场平衡）/[warroom slave hp equalization]（从者 HP 平衡）。
// ------------------------------------------------------------
char sub_4FBA70()
{
  void *v1; // eax
  int v2; // edi
  char *v3; // esi
  int v4; // eax
  int i; // edi
  int j; // esi
  bool v7; // zf
  uint32_t v8[11]; // [esp+0h] [ebp-8Ch] BYREF
  uint16_t v9[2]; // [esp+2Ch] [ebp-60h] BYREF
  void *Block; // [esp+34h] [ebp-58h]
  int v11; // [esp+38h] [ebp-54h]
  int v12; // [esp+3Ch] [ebp-50h]
  int v13; // [esp+40h] [ebp-4Ch]
  uint8_t v14[4]; // [esp+44h] [ebp-48h] BYREF
  void *v15; // [esp+48h] [ebp-44h]
  int v16; // [esp+58h] [ebp-34h]
  unsigned int v17; // [esp+5Ch] [ebp-30h]
  uint8_t v18[4]; // [esp+60h] [ebp-2Ch] BYREF
  void *v19; // [esp+64h] [ebp-28h]
  unsigned int v20; // [esp+74h] [ebp-18h]
  unsigned int v21; // [esp+78h] [ebp-14h]
  int v22; // [esp+7Ch] [ebp-10h]
  int v23; // [esp+88h] [ebp-4h]

  v22 = dword_796E50;
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"etc/WarRoomEqualize.tbl") != 0 )
  {
    v21 = 15;
    v20 = 0;
    LOBYTE(v19) = 0;
    v23 = 1;
    v17 = 15;
    v16 = 0;
    LOBYTE(v15) = 0;
    while ( (uint8_t)sub_443430(v18) != 0 )
    {
      sub_442BC0(v18);
      if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[warroom equalization]", 0x16u) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[warroom slave hp equalization]", 0x1Fu) == 0 )
          *(float *)&dword_77F884 = sub_442480(nullptr);
      }
      else
      {
        v1 = dword_8F7C48;
        if ( dword_8F7C48 != nullptr )
        {
          v2 = dword_8F7C4C;
          if ( dword_8F7C48 != (void *)dword_8F7C4C )
          {
            v3 = (char *)dword_8F7C48 + 8;
            do
            {
              if ( *(uint32_t *)v3 != 0 )
                j__free(*(void **)v3);
              *(uint32_t *)v3 = 0;
              *((uint32_t *)v3 + 1) = 0;
              *((uint32_t *)v3 + 2) = 0;
              v3 += 20;
            }
            while ( v3 - 8 != (char *)v2 );
            v1 = dword_8F7C48;
          }
          j__free(v1);
        }
        dword_8F7C48 = nullptr;
        dword_8F7C4C = 0;
        dword_8F7C50 = 0;
        if ( dword_8F7C58 != nullptr )
        {
          sub_4166A0(dword_8F7C58, dword_8F7C5C);
          j__free(dword_8F7C58);
        }
        dword_8F7C58 = nullptr;
        dword_8F7C5C = 0;
        dword_8F7C60 = 0;
        v4 = sub_4423D0(nullptr);
        if ( v4 > 0 )
        {
          v13 = v4;
          do
          {
            Block = nullptr;
            v11 = 0;
            v12 = 0;
            LOBYTE(v23) = 2;
            v9[0] = sub_4423D0(nullptr);
            v9[1] = sub_4423D0(nullptr);
            sub_443370();
            sub_416C40(v14);
            for ( i = 99; i != 0; --i )
            {
              v8[0] = 1065353216;
              v8[1] = 1065353216;
              v8[2] = 1065353216;
              v8[3] = 1065353216;
              v8[4] = 1065353216;
              v8[5] = 1065353216;
              v8[6] = 1065353216;
              v8[7] = 1065353216;
              v8[8] = 1065353216;
              v8[9] = 1065353216;
              v8[10] = 1065353216;
              for ( j = 0; j < 11; ++j )
                *(float *)&v8[j] = sub_442480(nullptr);
              sub_435790(v8);
            }
            sub_4FB9E0(v9);
            LOBYTE(v23) = 1;
            if ( Block != nullptr )
              j__free(Block);
            v7 = v13 == 1;
            Block = nullptr;
            v11 = 0;
            v12 = 0;
            --v13;
          }
          while ( !v7 );
        }
      }
    }
    if ( v17 >= 0x10 )
      j__free(v15);
    v17 = 15;
    v16 = 0;
    LOBYTE(v15) = 0;
    if ( v21 >= 0x10 )
      j__free(v19);
    return 1;
  }
  else
  {
    off_77F3FC(aCriticalError_15);
    return 0;
  }
}


// ------------------------------------------------------------
// 0x4FBD40 sub_4FBD40
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FBD40(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax
  uint32_t *v5; // edi
  int v6; // esi

  v3 = a1;
  for ( result = a3; v3 != a2; v5[4] = v6 )
  {
    v5 = result;
    *result = *v3;
    result[1] = v3[1];
    result[2] = v3[2];
    result[3] = v3[3];
    v6 = v3[4];
    v3 += 5;
    result += 5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FBD90 sub_4FBD90
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FBD90(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax

  v3 = a2;
  for ( result = a3; v3 != a1; result[4] = v3[4] )
  {
    v3 -= 5;
    result -= 5;
    *result = *v3;
    result[1] = v3[1];
    result[2] = v3[2];
    result[3] = v3[3];
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FBDE0 sub_4FBDE0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FBDE0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax

  v3 = a1;
  for ( result = a3; v3 != a2; result += 5 )
  {
    if ( result != nullptr )
    {
      *result = *v3;
      result[1] = v3[1];
      result[2] = v3[2];
      result[3] = v3[3];
      result[4] = v3[4];
    }
    v3 += 5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FBE30 sub_4FBE30
// ------------------------------------------------------------
int /*thiscall*/ sub_4FBE30(int *this, uint32_t *a2, unsigned int a3, uint32_t *Block)
{
  int v5; // edx
  int v6; // ebx
  int v7; // ecx
  int v8; // edx
  int result; // eax
  unsigned int v10; // ecx
  int v12; // eax
  int v13; // eax
  unsigned int v14; // ecx
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  unsigned int v18; // edi
  void *v19; // ecx
  int v21; // edi
  int v22; // [esp-18h] [ebp-48h]
  int v23; // [esp-Ch] [ebp-3Ch]
  unsigned int v24; // [esp-8h] [ebp-38h]
  int v25; // [esp+0h] [ebp-30h] BYREF
  uint32_t v26[6]; // [esp+Ch] [ebp-24h] BYREF
  int v27; // [esp+2Ch] [ebp-4h]
  int v28; // [esp+38h] [ebp+8h]
  uint32_t *v29; // [esp+3Ch] [ebp+Ch]
  char *Blocka; // [esp+40h] [ebp+10h]
  void *Blockb; // [esp+40h] [ebp+10h]

  v5 = Block[1];
  v6 = *(this + 1);
  v26[0] = *Block;
  v7 = Block[2];
  v26[1] = v5;
  v8 = Block[3];
  result = Block[4];
  v26[5] = &v25;
  v26[2] = v7;
  v26[3] = v8;
  v26[4] = result;
  if ( v6 != 0 )
  {
    result = 1717986919 * (*(this + 3) - v6);
    v10 = (*(this + 3) - v6) / 20;
  }
  else
  {
    v10 = 0;
  }
  if ( a3 != 0 )
  {
    if ( v6 != 0 )
      v12 = (*(this + 2) - v6) / 20;
    else
      v12 = 0;
    if ( 214748364 - v12 < a3 )
      sub_434730(this);
    if ( v6 != 0 )
      v13 = (*(this + 2) - v6) / 20;
    else
      v13 = 0;
    if ( v10 >= a3 + v13 )
    {
      v19 = (void *)*(this + 2);
      Blockb = v19;
      if ( ((uint8_t *)v19 - (uint8_t *)a2) / 20 >= a3 )
      {
        v28 = (int)v19 - 20 * a3;
        *(this + 2) = sub_4FBDE0(v28, v19, v19);
        sub_57A4A0(a2, v28, Blockb);
        return (int)sub_655A00(a2, &a2[5 * a3], v26);
      }
      else
      {
        sub_4FBDE0(a2, v19, &a2[5 * a3]);
        v24 = a3 - (*(this + 2) - (int)a2) / 20;
        v23 = *(this + 2);
        v27 = 2;
        sub_57A4C0(v23, v24, v26);
        v21 = 20 * a3 + *(this + 2);
        *(this + 2) = v21;
        return (int)sub_655A00(a2, (uint32_t *)(v21 - 20 * a3), v26);
      }
    }
    else
    {
      if ( 214748364 - (v10 >> 1) >= v10 )
        v14 = (v10 >> 1) + v10;
      else
        v14 = 0;
      if ( v6 != 0 )
        v15 = (*(this + 2) - v6) / 20;
      else
        v15 = 0;
      if ( v14 < a3 + v15 )
        v14 = a3 + sub_45E580(this);
      v16 = 20 * v14;
      Blocka = (char *)operator new(20 * v14);
      v22 = *(this + 1);
      v27 = 0;
      v29 = (uint32_t *)sub_4FBDE0(v22, a2, Blocka);
      sub_655A40(v29, (uint32_t *)a3, v26);
      sub_4FBDE0(a2, *(this + 2), &v29[5 * a3]);
      v17 = *(this + 1);
      if ( v17 != 0 )
        v17 = (*(this + 2) - v17) / 20;
      v18 = v17 + a3;
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

