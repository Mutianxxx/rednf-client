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
//   设定物品脚本根目录（全局 byte_9B0AB8，补 '\' 或 '/' 结尾）后加载文件表到
//   unk_9B0BB8（sub_443C40）。物品定义解析器族经 &unk_9B0BB8 使用该目录。
// ------------------------------------------------------------
bool /*cdecl*/ sub_4F0600(const char *pArg1, int nArg2)
{
  strcpy(byte_9B0AB8, pArg1);  // 调 strcpy 串拷贝
  if ( byte_9B0AB7[strlen(byte_9B0AB8)] != 92 && byte_9B0AB7[strlen(byte_9B0AB8)] != 47 )  // 若 byte_9B0AB7[strlen(byte_9B0AB8)] != 92 && byte_9B0AB7[strlen(b..
    *(uint16_t *)&byte_9B0AB8[strlen(byte_9B0AB8)] = 92;
  return (uint8_t)sub_443C40((int)&unk_9B0BB8, (char)byte_9B0AB8, nArg2) != 0;  // 脚本文件列表装表
}



// ------------------------------------------------------------
// 0x4F0690 sub_4F0690
//   "vector<T> too long" 异常抛出（length_error），永不返回。
// ------------------------------------------------------------
void /*noreturn*/ sub_4F0690()  // 函数: 条件抛异常
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4F0700 sub_4F0700
//   std::vector<36字节条目>::reserve/分配：+4 begin/+8 end/+12 capEnd，
//   超上限抛错（sub_4F0690）。返回是否分配成功。
// ------------------------------------------------------------
char /*thiscall*/ sub_4F0700(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;  // this+4 = 0
  *(this + 2) = 0;  // this+8 = 0
  *(this + 3) = 0;  // this+12 = 0
  if ( uArg2 == 0 )  // 若 uArg2 == 0
    return 0;
  if ( uArg2 > 0x71C71C7 )  // 若 uArg2 > 0x71C71C7
    sub_4F0690(this);  // 调 sub_4F0690
  pMem = (char *)operator new(36 * uArg2);
  *(this + 3) = &pMem[36 * uArg2];  // this+12 = &pMem[36 * uArg2]
  *(this + 1) = pMem;  // this+4 = pMem
  *(this + 2) = pMem;  // this+8 = pMem
  return 1;
}



// ------------------------------------------------------------
// 0x4F0750 sub_4F0750
//   36 字节条目拷贝构造：{int@+0, 成员@+4 与 +20（sub_435020 逐个深拷贝）}。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F0750(uint32_t *this, uint32_t *pArg2)
{
  *this = *pArg2;  // *this 写入 *pArg2
  sub_435020(pArg2 + 1);  // uint32 向量整体赋值
  sub_435020(pArg2 + 5);  // uint32 向量整体赋值
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F07B0 sub_4F07B0
//   std::copy（36 字节条目版，正向）：逐元素 {int, 两个 sub_4ED3F0 深拷贝成员}。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F07B0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // esi
  uint32_t *uArg32; // edi

  uArg12 = uArg1;
  if ( uArg1 == uArg2 )  // 若 uArg1 == uArg2
    return uArg3;
  uArg32 = uArg3;
  do
  {
    *uArg32 = *uArg12;  // *uArg32 写入 *uArg12
    sub_4ED3F0((int)(uArg32 + 1), (int)(uArg12 + 1));  // int 向量拷贝赋值（全容量路径）
    sub_4ED3F0((int)(uArg32 + 5), (int)(uArg12 + 5));  // int 向量拷贝赋值（全容量路径）
    uArg12 += 9;
    uArg32 += 9;
  }
  while ( uArg12 != uArg2 );  // 当 uArg12 != uArg2 循环
  return uArg32;
}



// ------------------------------------------------------------
// 0x4F0800 sub_4F0800
//   std::copy_backward（36 字节条目版）：从尾往头逐 0x24 字节搬移
//   （两个成员经 sub_4ED3F0 深拷贝）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F0800(int nArg1, int nArg2, uint32_t *uArg3)
{
  int nArg22; // esi
  uint32_t *uArg32; // edi
  int v5; // eax

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )  // 若 nArg1 == nArg2
    return uArg3;
  uArg32 = uArg3;
  do
  {
    v5 = *(uint32_t *)(nArg22 - 36);
    nArg22 -= 36;
    uArg32 -= 9;
    *uArg32 = v5;  // *uArg32 写入 v5
    sub_4ED3F0((int)(uArg32 + 1), nArg22 + 4);  // int 向量拷贝赋值（全容量路径）
    sub_4ED3F0((int)(uArg32 + 5), nArg22 + 20);  // int 向量拷贝赋值（全容量路径）
  }
  while ( nArg22 != nArg1 );  // 当 nArg22 != nArg1 循环
  return uArg32;
}



// ------------------------------------------------------------
// 0x4F0850 sub_4F0850
//   条目重置（{int@0, 两个三指针容器@+8/+24}）：全部清零并释放旧缓冲。
// ------------------------------------------------------------
void */*thiscall*/ sub_4F0850(void *this)
{
  *((uint32_t *)this + 2) = 0;  // this+8 = 0
  *((uint32_t *)this + 3) = 0;  // this+12 = 0
  *((uint32_t *)this + 4) = 0;  // this+16 = 0
  *((uint32_t *)this + 6) = 0;  // this+24 = 0
  *((uint32_t *)this + 7) = 0;  // this+28 = 0
  *((uint32_t *)this + 8) = 0;  // this+32 = 0
  *(uint32_t *)this = 0;
  if ( *((uint32_t *)this + 2) != 0 )  // 若 *((uint32_t *)this + 2) != 0
    j__free(*((void **)this + 2));  // 调 j__free
  *((uint32_t *)this + 2) = 0;  // this+8 = 0
  *((uint32_t *)this + 3) = 0;  // this+12 = 0
  *((uint32_t *)this + 4) = 0;  // this+16 = 0
  if ( *((uint32_t *)this + 6) != 0 )  // 若 *((uint32_t *)this + 6) != 0
    j__free(*((void **)this + 6));  // 调 j__free
  *((uint32_t *)this + 6) = 0;  // this+24 = 0
  *((uint32_t *)this + 7) = 0;  // this+28 = 0
  *((uint32_t *)this + 8) = 0;  // this+32 = 0
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F08D0 sub_4F08D0
//   std::copy（36 字节条目版）：转调 sub_4F07B0。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F08D0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  return sub_4F07B0(uArg1, uArg2, uArg3);  // 调 sub_4F07B0
}



// ------------------------------------------------------------
// 0x4F08F0 sub_4F08F0
//   std::fill（36 字节条目版）：[uArg1,uArg2) 区间逐元素用 pArg3 模板覆盖
//   （两个成员经 sub_4ED3F0 深拷贝）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F08F0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 9 )  // 循环：i = uArg1; i != uArg2; i += 9
  {
    *i = *pArg3;  // *i 写入 *pArg3
    sub_4ED3F0((int)(i + 1), (int)(pArg3 + 1));  // int 向量拷贝赋值（全容量路径）
    sub_4ED3F0((int)(i + 5), (int)(pArg3 + 5));  // int 向量拷贝赋值（全容量路径）
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F0930 sub_4F0930
//   std::copy_backward（36 字节条目版）：转调 sub_4F0800。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F0930(int nArg1, int nArg2, uint32_t *uArg3)
{
  return sub_4F0800(nArg1, nArg2, uArg3);  // 调 sub_4F0800
}



// ------------------------------------------------------------
// 0x4F0950 sub_4F0950
//   std::_Fill_n 未初始化构造（36 字节条目版）：从 uArg3 模板逐元素拷贝构造
//   {int@0, 两个 sub_435020 拷贝成员}，返回尾地址。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F0950(uint32_t *pArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v6[4] = v6;
  v6[3] = uArg3;
  v7 = 0;
  while ( pArg1 != uArg2 )  // 当 pArg1 != uArg2 循环
  {
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )  // 若 uArg32 非空
    {
      *uArg32 = *pArg1;  // *uArg32 写入 *pArg1
      sub_435020(pArg1 + 1);  // uint32 向量整体赋值
      LOBYTE(v7) = 2;
      sub_435020(pArg1 + 5);  // uint32 向量整体赋值
    }
    uArg32 += 9;
    LOBYTE(v7) = 0;
    pArg1 += 9;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x4F0A30 sub_4F0A30
//   std::vector<36字节条目>::erase(iterator)：把 [uArg4, end) 前移
//   （sub_4F07B0），余量逐个析构（sub_472F00），end 回退；*uArg2 返回新 end。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F0A30(uint32_t **this, uint32_t *uArg2, uint32_t *uArg3, uint32_t *uArg4)
{
  uint32_t *uArg32; // ecx
  uint32_t *fld_e2; // eax
  uint32_t *fld_e22; // ebx
  uint32_t *fld_e23; // edi
  uint32_t *i; // esi
  uint32_t **pThis; // [esp+4h] [ebp-4h]

  uArg32 = uArg3;
  pThis = this;
  if ( uArg3 != uArg4 )  // 若 uArg3 != uArg4
  {
    fld_e2 = sub_4F07B0(uArg4, *(this + 2), uArg3);  // 调 sub_4F07B0
    fld_e22 = *(this + 2);  // fld_e22 = this+2
    fld_e23 = fld_e2;
    for ( i = fld_e2; i != fld_e22; i += 9 )  // 循环：i = fld_e2; i != fld_e22; i += 9
      sub_472F00(i);  // 调 sub_472F00
    uArg32 = uArg3;
    pThis[2] = fld_e23;
  }
  *uArg2 = uArg32;  // *uArg2 写入 uArg32
  return uArg2;
}



// ------------------------------------------------------------
// 0x4F0A90 sub_4F0A90
//   std::_Fill_n（36 字节条目版，赋值式）：从 uArg1 起连续 nArg2 个元素用
//   pArg3 模板覆盖（两个 sub_435020 拷贝成员）。
// ------------------------------------------------------------
void /*cdecl*/ sub_4F0A90(uint32_t *uArg1, int nArg2, uint32_t *pArg3)
{
  uint32_t *uArg12; // esi
  uint32_t v4[6]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  uArg12 = uArg1;
  v4[5] = v4;
  v4[4] = uArg1;
  v5 = 0;
  while ( nArg2 != 0 )  // 当 nArg2 != 0 循环
  {
    v4[3] = uArg12;
    LOBYTE(v5) = 1;
    if ( uArg12 != nullptr )  // 若 uArg12 非空
    {
      *uArg12 = *pArg3;  // *uArg12 写入 *pArg3
      sub_435020(pArg3 + 1);  // uint32 向量整体赋值
      LOBYTE(v5) = 2;
      sub_435020(pArg3 + 5);  // uint32 向量整体赋值
    }
    uArg12 += 9;
    LOBYTE(v5) = 0;
    --nArg2;  // 自减nArg2
  }
}



// ------------------------------------------------------------
// 0x4F0B70 sub_4F0B70
//   std::_Fill_n（36 字节条目版）：转调 sub_4F0950。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4F0B70(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  return sub_4F0950(uArg1, uArg2, uArg3);  // 调 sub_4F0950
}



// ------------------------------------------------------------
// 0x4F0B90 sub_4F0B90
//   std::vector<36字节条目>::operator=：按源大小收缩/扩容后整段覆盖
//   （余量析构 475080；不够则重建 sub_4F0700+4F0B70）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F0B90(int this, int pArg2)  // 函数: 释放后返回
{
  int v4; // eax
  unsigned int v5; // ecx
  uint32_t *fld_4; // edi
  unsigned int fld_8; // eax
  uint32_t *v9; // eax
  int v10; // eax
  int fld_42; // ecx
  unsigned int fld_C; // eax
  unsigned int v13; // eax
  uint32_t *v14; // [esp+10h] [ebp+8h]

  if ( this == pArg2 )  // 若 this == pArg2
    return this;  // 返回自身指针
  v4 = *(uint32_t *)(pArg2 + 4);  // v4 = pArg2+4
  if ( v4 == 0 || (v5 = (*(uint32_t *)(pArg2 + 8) - v4) / 36) == 0 )  // 若 v4 == 0 || (v5 = (*(uint32_t *)(pArg2 + 8) - v4) / 36) == 0
  {
    sub_474C60(this);  // 调 sub_474C60
    return this;  // 返回自身指针
  }
  fld_4 = *(uint32_t **)(this + 4);
  if ( fld_4 != nullptr )  // 若 fld_4 非空
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 36;
  else
    fld_8 = 0;
  if ( v5 > fld_8 )  // 若 v5 > fld_8
  {
    if ( fld_4 != nullptr )  // 若 fld_4 非空
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 36;
    else
      fld_C = 0;
    if ( v5 <= fld_C )  // 若 v5 <= fld_C
    {
      v14 = (uint32_t *)(*(uint32_t *)(pArg2 + 4) + 36 * sub_504390(this));
      sub_4F08D0(*(uint32_t **)(pArg2 + 4), v14, fld_4);  // 调 sub_4F08D0
      *(uint32_t *)(this + 8) = sub_4F0950(v14, *(uint32_t **)(pArg2 + 8), *(uint32_t **)(this + 8));  // this+8 = sub_4F0950(v14, *(uint32_t **)(pArg2 + 8),..
      return this;  // 返回自身指针
    }
    if ( fld_4 != nullptr )  // 若 fld_4 非空
    {
      sub_475080(fld_4, *(uint32_t *)(this + 8));  // 调 sub_475080
      j__free(*(void **)(this + 4));  // 调 j__free
    }
    v13 = sub_504390(pArg2);  // 调 sub_504390
    if ( sub_4F0700((uint32_t *)this, v13) != 0 )  // 若 sub_4F0700((uint32_t *)this, v13) != 0
      *(uint32_t *)(this + 8) = sub_4F0B70(*(uint32_t **)(pArg2 + 4), *(uint32_t **)(pArg2 + 8), *(uint32_t **)(this + 4));  // this+8 = sub_4F0B70(*(uint32_t **)(pArg2 + 4), *(ui..
    return this;  // 返回自身指针
  }
  v9 = sub_4F07B0(*(uint32_t **)(pArg2 + 4), *(uint32_t **)(pArg2 + 8), fld_4);  // 调 sub_4F07B0
  sub_475080(v9, *(uint32_t *)(this + 8));  // 调 sub_475080
  v10 = *(uint32_t *)(pArg2 + 4);  // v10 = pArg2+4
  if ( v10 != 0 )  // 若 v10 != 0
    fld_42 = *(uint32_t *)(this + 4) + 36 * ((*(uint32_t *)(pArg2 + 8) - v10) / 36);
  else
    fld_42 = *(uint32_t *)(this + 4);  // fld_42 = this+4
  *(uint32_t *)(this + 8) = fld_42;  // this+8 = fld_42
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F0D10 sub_4F0D10
//   装备解析容器重置：+0/+4 标志置 1，+0x0C 起三个 vector<36字节条目>
//   （+0x0C/+0x1C/+0x2C）逐元素析构（sub_472F00）并释放缓冲。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F0D10(void *this)  // 函数: 释放后返回
{
  int pThis_3; // edi
  int result; // eax
  int i; // ebx

  *(uint32_t *)this = 1;
  *((uint32_t *)this + 1) = 1;  // this+4 = 1
  pThis_3 = *((uint32_t *)this + 3);
  result = 0;
  if ( pThis_3 != 0 )  // 若 pThis_3 != 0
  {
    for ( i = *((uint32_t *)this + 4); pThis_3 != i; pThis_3 += 36 )  // 循环：i = *((uint32_t *)this + 4); pThis_3 != i; pThis_3 += 36
      sub_472F00(pThis_3);  // 调 sub_472F00
    j__free(*((void **)this + 3));  // 调 j__free
    result = 0;
  }
  *((uint32_t *)this + 3) = 0;  // this+12 = 0
  *((uint32_t *)this + 4) = 0;  // this+16 = 0
  *((uint32_t *)this + 5) = 0;  // this+20 = 0
  if ( *((uint32_t *)this + 7) != 0 )  // 若 *((uint32_t *)this + 7) != 0
  {
    j__free(*((void **)this + 7));  // 调 j__free
    result = 0;
  }
  *((uint32_t *)this + 7) = 0;  // this+28 = 0
  *((uint32_t *)this + 8) = 0;  // this+32 = 0
  *((uint32_t *)this + 9) = 0;  // this+36 = 0
  if ( *((uint32_t *)this + 11) != 0 )  // 若 *((uint32_t *)this + 11) != 0
  {
    j__free(*((void **)this + 11));  // 调 j__free
    result = 0;
  }
  *((uint32_t *)this + 11) = 0;  // this+44 = 0
  *((uint32_t *)this + 12) = 0;  // this+48 = 0
  *((uint32_t *)this + 13) = 0;  // this+52 = 0
  return result;
}



// ------------------------------------------------------------
// 0x4F0D90 sub_4F0D90
//   装备解析容器重置外壳：先把 +0x0C/+0x1C/+0x2C 三个 vector 指针清零，
//   再转调 sub_4F0D10。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F0D90(uint32_t *this)
{
  *(this + 3) = 0;  // this+12 = 0
  *(this + 4) = 0;  // this+16 = 0
  *(this + 5) = 0;  // this+20 = 0
  *(this + 7) = 0;  // this+28 = 0
  *(this + 8) = 0;  // this+32 = 0
  *(this + 9) = 0;  // this+36 = 0
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = 0
  sub_4F0D10(this);  // 调 sub_4F0D10
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F0DE0 sub_4F0DE0
//   std::vector<36字节条目> 复制构造辅助：按源 vector 大小 reserve（sub_4F0700）
//   后整段拷贝构造（sub_4F0950）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F0DE0(uint32_t *this, int pArg2)
{
  unsigned int v2; // eax
  uint32_t *v5; // [esp-14h] [ebp-34h]
  uint32_t *v6; // [esp-10h] [ebp-30h]
  uint32_t *fld_e1; // [esp-Ch] [ebp-2Ch]
  uint32_t v8[8]; // [esp+0h] [ebp-20h] BYREF

  v2 = *(uint32_t *)(pArg2 + 4);  // v2 = pArg2+4
  v8[4] = v8;
  v8[3] = this;
  if ( v2 != 0 )  // 若 v2 != 0
    v2 = (int)(*(uint32_t *)(pArg2 + 8) - v2) / 36;
  if ( sub_4F0700(this, v2) != 0 )  // 若 sub_4F0700(this, v2) != 0
  {
    fld_e1 = (uint32_t *)*(this + 1);
    v6 = *(uint32_t **)(pArg2 + 8);
    v5 = *(uint32_t **)(pArg2 + 4);
    v8[7] = 0;
    *(this + 2) = sub_4F0950(v5, v6, fld_e1);  // this+8 = sub_4F0950(v5, v6, fld_e1)
  }
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F0E80 sub_4F0E80
//   std::_Fill_n（36 字节条目版）：转调 sub_4F0A90 后返回 &pArg1[9*nArg2] 尾地址。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4F0E80(uint32_t *pArg1, int nArg2, uint32_t *uArg3)
{
  sub_4F0A90(pArg1, nArg2, uArg3);  // 调 sub_4F0A90
  return &pArg1[9 * nArg2];
}



// ------------------------------------------------------------
// 0x4F0EB0 sub_4F0EB0
//   std::copy_backward（56 字节条目版）：{int@0, int@4, vector<36B>@+8
//   （sub_4F0B90 整段赋值）, 成员@+24/+40（sub_4800C0 拷贝）}。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F0EB0(int nArg1, int nArg2, uint32_t *uArg3)
{
  int nArg22; // esi
  uint32_t *uArg32; // edi
  int v5; // eax

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )  // 若 nArg1 == nArg2
    return uArg3;
  uArg32 = uArg3;
  do
  {
    v5 = *(uint32_t *)(nArg22 - 56);
    nArg22 -= 56;
    uArg32 -= 14;
    *uArg32 = v5;  // *uArg32 写入 v5
    uArg32[1] = *(uint32_t *)(nArg22 + 4);  // uArg32[1] 写入 *(uint32_t *)(nArg22 + 4)
    sub_4F0B90((int)(uArg32 + 2), nArg22 + 8);  // 调 sub_4F0B90
    sub_4800C0(nArg22 + 24);  // 8 字节元素容器区间赋值（三分支容量策略）
    sub_4800C0(nArg22 + 40);  // 8 字节元素容器区间赋值（三分支容量策略）
  }
  while ( nArg22 != nArg1 );  // 当 nArg22 != nArg1 循环
  return uArg32;
}



// ------------------------------------------------------------
// 0x4F0F10 sub_4F0F10
//   std::vector<36字节条目>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位（4F0950/4F0930/4F08F0/4F0E80）；不足 → 扩容三段拷贝重建
//   （上限检查 sub_4F0690；旧缓冲析构 475080）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4F0F10(int *this, int pArg2, unsigned int uArg3, int nArg4)  // 函数: 释放后返回
{
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v14; // edi
  int fld_e14; // eax
  int fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-60h]
  int fld_e25; // [esp-Ch] [ebp-54h]
  unsigned int fld_e24; // [esp-8h] [ebp-50h]
  int v22; // [esp+0h] [ebp-48h] BYREF
  uint8_t v23[8]; // [esp+Ch] [ebp-3Ch] BYREF
  void *v24; // [esp+14h] [ebp-34h]
  void *v25; // [esp+24h] [ebp-24h]
  int v26; // [esp+28h] [ebp-20h]
  int v27; // [esp+2Ch] [ebp-1Ch]
  void *Block; // [esp+30h] [ebp-18h]
  int *pThis; // [esp+34h] [ebp-14h]
  int *v30; // [esp+38h] [ebp-10h]
  int v31; // [esp+44h] [ebp-4h]
  int v32; // [esp+50h] [ebp+8h]
  int v33; // [esp+54h] [ebp+Ch]
  int v34; // [esp+58h] [ebp+10h]
  int fld_e232; // [esp+58h] [ebp+10h]

  v30 = &v22;
  pThis = this;
  sub_4F0750(nArg4);  // 调 sub_4F0750
  fld_e1 = *(this + 1);  // fld_e1 = this+1
  fld_e3 = 0;
  v31 = 0;
  if ( fld_e1 != 0 )  // 若 fld_e1 != 0
    fld_e3 = (*(this + 3) - fld_e1) / 36;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e2 = (*(this + 2) - fld_e1) / 36;
    else
      fld_e2 = 0;
    if ( 119304647 - fld_e2 < uArg3 )  // 若 119304647 - fld_e2 < uArg3
      sub_4F0690(this);  // 调 sub_4F0690
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e22 = (*(this + 2) - fld_e1) / 36;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )  // 若 fld_e3 >= uArg3 + fld_e22
    {
      fld_e23 = *(this + 2);  // fld_e23 = this+2
      fld_e232 = fld_e23;
      if ( (fld_e23 - pArg2) / 36 >= uArg3 )  // 若 (fld_e23 - pArg2) / 36 >= uArg3
      {
        v32 = fld_e23 - 36 * uArg3;
        *(this + 2) = sub_4F0950(v32, fld_e23, fld_e23);  // this+8 = sub_4F0950(v32, fld_e23, fld_e23)
        sub_4F0930(pArg2, v32, fld_e232);  // 调 sub_4F0930
        sub_4F08F0(pArg2, pArg2 + 36 * uArg3, v23);  // 调 sub_4F08F0
      }
      else
      {
        sub_4F0950(pArg2, fld_e23, pArg2 + 36 * uArg3);  // 调 sub_4F0950
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 36;
        fld_e25 = *(this + 2);  // fld_e25 = this+2
        LOBYTE(v31) = 3;
        sub_4F0E80(fld_e25, fld_e24, v23);  // 调 sub_4F0E80
        fld_e26 = 36 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8 = fld_e26
        v31 = 0;
        sub_4F08F0(pArg2, fld_e26 - 36 * uArg3, v23);  // 调 sub_4F08F0
      }
    }
    else
    {
      if ( 119304647 - (fld_e3 >> 1) >= fld_e3 )  // 若 119304647 - (fld_e3 >> 1) >= fld_e3
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )  // 若 fld_e1 != 0
        fld_e27 = (*(this + 2) - fld_e1) / 36;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )  // 若 v10 < uArg3 + fld_e27
        v10 = uArg3 + sub_504390(this);
      v34 = 36 * v10;
      pMem = (char *)operator new(36 * v10);
      fld_e12 = *(this + 1);  // fld_e12 = this+1
      Block = pMem;
      LOBYTE(v31) = 1;
      v33 = sub_4F0950(fld_e12, pArg2, pMem);  // 调 sub_4F0950
      sub_4F0A90(v33, uArg3, v23);  // 调 sub_4F0A90
      sub_4F0950(pArg2, *(this + 2), v33 + 36 * uArg3);  // 调 sub_4F0950
      fld_e13 = *(this + 1);  // fld_e13 = this+1
      if ( fld_e13 != 0 )  // 若 fld_e13 != 0
        fld_e13 = (*(this + 2) - fld_e13) / 36;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);  // fld_e14 = this+1
      if ( fld_e14 != 0 )  // 若 fld_e14 != 0
      {
        sub_475080(fld_e14, *(this + 2));  // 调 sub_475080
        j__free((void *)*(this + 1));  // 调 j__free
      }
      *(this + 3) = (int)&pMem[v34];  // this+12 = (int)&pMem[v34]
      *(this + 2) = (int)&pMem[36 * v14];  // this+8 = (int)&pMem[36 * v14]
      *(this + 1) = (int)pMem;  // this+4 = (int)pMem
    }
  }
  if ( v25 != nullptr )  // 若 v25 非空
    j__free(v25);  // 调 j__free
  v25 = nullptr;  // v25 = nullptr 空指针
  v26 = 0;
  v27 = 0;
  if ( v24 != nullptr )  // 若 v24 非空
    j__free(v24);  // 调 j__free
}


// ------------------------------------------------------------
// 0x4F1220 sub_4F1220
//   56 字节条目拷贝构造：{int@0, int@4, vector<36B> 整段复制（sub_4F0DE0）,
//   +24/+40 成员（sub_480360 拷贝）}。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F1220(uint32_t *this, uint32_t *pArg2)
{
  *this = *pArg2;  // *this 写入 *pArg2
  *(this + 1) = pArg2[1];  // this+4 = pArg2[1]
  sub_4F0DE0(this + 2, (int)(pArg2 + 2));  // 调 sub_4F0DE0
  sub_480360(pArg2 + 6);  // 8 字节元素容器区间赋值（简易构造版）
  sub_480360(pArg2 + 10);  // 8 字节元素容器区间赋值（简易构造版）
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F1290 sub_4F1290
//   std::fill（56 字节条目版）：[uArg1,uArg2) 逐元素用 pArg3 模板覆盖
//   （vector<36B> 赋值 4F0B90 + 4800C0 拷贝）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F1290(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 14 )  // 循环：i = uArg1; i != uArg2; i += 14
  {
    *i = *pArg3;  // *i 写入 *pArg3
    i[1] = pArg3[1];  // i[1] 写入 pArg3[1]
    sub_4F0B90((int)(i + 2), (int)(pArg3 + 2));  // 调 sub_4F0B90
    sub_4800C0(pArg3 + 6);  // 8 字节元素容器区间赋值（三分支容量策略）
    sub_4800C0(pArg3 + 10);  // 8 字节元素容器区间赋值（三分支容量策略）
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F12E0 sub_4F12E0
//   std::copy_backward（56 字节条目版）：转调 sub_4F0EB0。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F12E0(int nArg1, int nArg2, uint32_t *uArg3)
{
  return sub_4F0EB0(nArg1, nArg2, uArg3);  // 调 sub_4F0EB0
}



// ------------------------------------------------------------
// 0x4F1300 sub_4F1300
//   std::vector<36字节条目>::resize(n)：n ≤ 现有 → 尾部截断（sub_4F0A30）；
//   n > 现有 → 从 end 补构造（sub_4F0F10，值 = 栈上 Block 模板）。
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

  v11 = *(uint32_t *)(this + 4);  // v11 = this+4
  if ( v11 != 0 )  // 若 v11 != 0
    v12 = (*(uint32_t *)(this + 8) - v11) / 36;
  else
    v12 = 0;
  if ( v12 >= a2 )  // 若 v12 >= a2
  {
    if ( v11 != 0 && a2 < (*(uint32_t *)(this + 8) - v11) / 36 )  // 若 v11 != 0 && a2 < (*(uint32_t *)(this + 8) - v11) / 36
      sub_4F0A30((uint32_t **)this, &a2, (uint32_t *)(v11 + 36 * a2), *(uint32_t **)(this + 8));  // 调 sub_4F0A30
  }
  else
  {
    if ( v11 != 0 )  // 若 v11 != 0
      v13 = (*(uint32_t *)(this + 8) - v11) / 36;
    else
      v13 = 0;
    sub_4F0F10((int *)this, *(char **)(this + 8), a2 - v13, &a3);  // 调 sub_4F0F10
  }
  if ( Block != nullptr )  // 若 Block 非空
    j__free(Block);  // 调 j__free
  if ( a5 != nullptr )  // 若 a5 非空
    j__free(a5);  // 调 j__free
}



// ------------------------------------------------------------
// 0x4F13E0 sub_4F13E0
//   std::copy（56 字节条目版，正向）：逐元素 sub_4F1220 拷贝构造。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F13E0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v6[4] = v6;
  v6[3] = uArg3;
  v7 = 0;
  while ( uArg1 != uArg2 )  // 当 uArg1 != uArg2 循环
  {
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )  // 若 uArg32 非空
      sub_4F1220(uArg32, uArg1);  // 调 sub_4F1220
    uArg32 += 14;
    LOBYTE(v7) = 0;
    uArg1 += 14;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x4F14B0 sub_4F14B0
//   std::vector<36字节条目>::resize(n) 外壳：栈上构造模板条目（sub_4F0850）
//   后转调 sub_4F1300。
// ------------------------------------------------------------
void /*thiscall*/ sub_4F14B0(void *this, unsigned int uArg2)
{
  uint32_t v3[11]; // [esp-24h] [ebp-2Ch] BYREF

  v3[10] = v3;
  sub_4F0850(v3);  // 调 sub_4F0850
  sub_4F1300((int)this, uArg2, v3[0], v3[1], (void *)v3[2], v3[3], v3[4], v3[5], (void *)v3[6], v3[7], v3[8]);  // 调 sub_4F1300
}



// ------------------------------------------------------------
// 0x4F14E0 sub_4F14E0
//   std::_Fill_n 未初始化构造（56 字节条目版）：从 uArg3 模板逐元素
//   sub_4F1220 拷贝构造。
// ------------------------------------------------------------
void /*cdecl*/ sub_4F14E0(uint32_t *uArg1, int nArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // esi
  uint32_t v5[5]; // [esp+0h] [ebp-20h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  uArg12 = uArg1;
  v5[4] = v5;
  v5[3] = uArg1;
  v6 = 0;
  while ( nArg2 != 0 )  // 当 nArg2 != 0 循环
  {
    LOBYTE(v6) = 1;
    if ( uArg12 != nullptr )  // 若 uArg12 非空
      sub_4F1220(uArg12, uArg3);  // 调 sub_4F1220
    --nArg2;  // 自减nArg2
    uArg12 += 14;
    LOBYTE(v6) = 0;
  }
}



// ------------------------------------------------------------
// 0x4F15B0 sub_4F15B0
//   std::_Fill_n（56 字节条目版）：转调 sub_4F14E0 后返回 &pArg1[14*nArg2] 尾地址。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4F15B0(uint32_t *pArg1, int nArg2, uint32_t *uArg3)
{
  sub_4F14E0(pArg1, nArg2, uArg3);  // 调 sub_4F14E0
  return &pArg1[14 * nArg2];
}



// ------------------------------------------------------------
// 0x4F15E0 sub_4F15E0
//   std::vector<56字节条目>::insert(pos, n, val)：+4 begin/+8 end/+12 capEnd。
//   容量够 → 尾部腾位（4F13E0/4F12E0/4F1290/4F15B0）；不足 → 扩容三段拷贝重建
//   （上限检查 sub_4735F0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F15E0(int *this, int pArg2, unsigned int uArg3, int nArg4)  // 函数: 释放后返回
{
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v14; // edi
  int fld_e14; // eax
  char *fld_e23; // ecx
  int fld_e26; // edx
  int fld_e12; // [esp-18h] [ebp-74h]
  int fld_e25; // [esp-Ch] [ebp-68h]
  unsigned int fld_e24; // [esp-8h] [ebp-64h]
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
  int *pThis; // [esp+48h] [ebp-14h]
  int *v34; // [esp+4Ch] [ebp-10h]
  int v35; // [esp+58h] [ebp-4h]
  char *v36; // [esp+64h] [ebp+8h]
  int v37; // [esp+68h] [ebp+Ch]
  int v38; // [esp+6Ch] [ebp+10h]

  v34 = &v23;
  pThis = this;
  sub_4F1220(nArg4);  // 调 sub_4F1220
  fld_e1 = *(this + 1);  // fld_e1 = this+1
  fld_e3 = 0;
  v35 = 0;
  if ( fld_e1 != 0 )  // 若 fld_e1 != 0
    fld_e3 = (*(this + 3) - fld_e1) / 56;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e2 = (*(this + 2) - *(this + 1)) / 56;
    else
      fld_e2 = 0;
    if ( 76695844 - fld_e2 < uArg3 )  // 若 76695844 - fld_e2 < uArg3
      sub_4735F0(this);  // 调 sub_4735F0
    if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
      fld_e22 = (*(this + 2) - *(this + 1)) / 56;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )  // 若 fld_e3 >= uArg3 + fld_e22
    {
      fld_e23 = (char *)*(this + 2);
      Block = fld_e23;
      if ( (int)&fld_e23[-pArg2] / 56 >= uArg3 )  // 若 (int)&fld_e23[-pArg2] / 56 >= uArg3
      {
        v36 = &fld_e23[-56 * uArg3];
        *(this + 2) = sub_4F13E0(v36, fld_e23, fld_e23);  // this+8 = sub_4F13E0(v36, fld_e23, fld_e23)
        sub_4F12E0(pArg2, v36, Block);  // 调 sub_4F12E0
        sub_4F1290(pArg2, pArg2 + 56 * uArg3, v24);  // 调 sub_4F1290
      }
      else
      {
        sub_4F13E0(pArg2, fld_e23, pArg2 + 56 * uArg3);  // 调 sub_4F13E0
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 56;
        fld_e25 = *(this + 2);  // fld_e25 = this+2
        LOBYTE(v35) = 3;
        sub_4F15B0(fld_e25, fld_e24, v24);  // 调 sub_4F15B0
        fld_e26 = 56 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8 = fld_e26
        v35 = 0;
        sub_4F1290(pArg2, fld_e26 - 56 * uArg3, v24);  // 调 sub_4F1290
      }
    }
    else
    {
      if ( 76695844 - (fld_e3 >> 1) >= fld_e3 )  // 若 76695844 - (fld_e3 >> 1) >= fld_e3
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        fld_e27 = (*(this + 2) - *(this + 1)) / 56;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )  // 若 v10 < uArg3 + fld_e27
        v10 = uArg3 + sub_488DD0(this);  // 结果 = 56 字节元素数组长度
      v38 = 56 * v10;
      pMem = (char *)operator new(56 * v10);
      fld_e12 = *(this + 1);  // fld_e12 = this+1
      Block = pMem;
      LOBYTE(v35) = 1;
      v37 = sub_4F13E0(fld_e12, pArg2, pMem);  // 调 sub_4F13E0
      sub_4F14E0(v37, uArg3, v24);  // 调 sub_4F14E0
      sub_4F13E0(pArg2, *(this + 2), 56 * uArg3 + v37);  // 调 sub_4F13E0
      fld_e13 = *(this + 1);  // fld_e13 = this+1
      if ( fld_e13 != 0 )  // 若 fld_e13 != 0
        fld_e13 = (*(this + 2) - fld_e13) / 56;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);  // fld_e14 = this+1
      if ( fld_e14 != 0 )  // 若 fld_e14 != 0
      {
        sub_475730(fld_e14, *(this + 2));  // 调 sub_475730
        j__free((void *)*(this + 1));  // 调 j__free
      }
      *(this + 3) = (int)&pMem[v38];  // this+12 = (int)&pMem[v38]
      *(this + 2) = (int)&pMem[56 * v14];  // this+8 = (int)&pMem[56 * v14]
      *(this + 1) = (int)pMem;  // this+4 = (int)pMem
    }
  }
  if ( v29 != nullptr )  // 若 v29 非空
    j__free(v29);  // 调 j__free
  v29 = nullptr;  // v29 = nullptr 空指针
  v30 = 0;
  v31 = 0;
  if ( v26 != nullptr )  // 若 v26 非空
    j__free(v26);  // 调 j__free
  v26 = nullptr;  // v26 = nullptr 空指针
  v27 = 0;
  v28 = 0;
  return sub_474C60(v25);  // 调 sub_474C60
}


// ------------------------------------------------------------
// 0x4F1920 sub_4F1920
//   std::vector<56字节条目>::insert(pos, 1, val) 外壳：先算 pos 下标防失效，
//   转调 sub_4F15E0 后按旧下标重取迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F1920(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *uArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 56 != 0 )  // 若 fld_e1 != 0 && (*(this + 2) - fld_e1) / 56 != 0
    v6 = (int)&pszArg3[-fld_e1] / 56;
  else
    v6 = 0;
  sub_4F15E0(this, pszArg3, 1u, uArg4);  // 调 sub_4F15E0
  *uArg2 = *(this + 1) + 56 * v6;  // *uArg2 写入 *(this + 1) + 56 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x4F1990 sub_4F1990
//   std::vector<56字节条目>::push_back：容量够 → 在 end 构造（sub_4F14E0）；
//   不够 → 转调 sub_4F1920 插入路径扩容。
// ------------------------------------------------------------
void /*thiscall*/ sub_4F1990(int this, uint32_t *uArg2)
{
  int fld_4; // ebx
  unsigned int fld_8; // esi
  uint32_t *fld_82; // esi

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 56;
  else
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) / 56 )  // 若 fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) / 56
  {
    fld_82 = *(uint32_t **)(this + 8);
    sub_4F14E0(fld_82, 1, uArg2);  // 调 sub_4F14E0
    *(uint32_t *)(this + 8) = fld_82 + 14;  // this+8 = fld_82 + 14
  }
  else
  {
    sub_4F1920((int *)this, &uArg2, *(char **)(this + 8), uArg2);  // 调 sub_4F1920
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
char /*cdecl*/ sub_4F1A20(char *pszArg1, int ArgList)  // 函数: 释放后返回
{
  const char *v2; // esi
  char *pszArg12; // edi
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
  int dword_796E502; // [esp+C8h] [ebp-10h]
  int v88; // [esp+D4h] [ebp-4h]

  v2 = (const char *)ArgList;
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  if ( (uint8_t)sub_442A10((char)&unk_9B0AB8, ArgList) == 0 )  // 脚本载入调度（PVF 或磁盘）
    return 0;
  pszArg12 = pszArg1;
  sub_476000(pszArg1);  // 调 sub_476000
  sub_443300((int)(pszArg1 + 316), "%s%s", (char)&unk_9B0AB8);  // 字符串 “%s%s”
  v86 = 15;
  v85 = 0;
  LOBYTE(v84) = 0;
  v88 = 1;
  v79 = 15;
  v78 = 0;
  LOBYTE(v77) = 0;
  v75 = 0;
  sub_4F0D90(&v57);  // 调 sub_4F0D90
  LOBYTE(v88) = 2;
  v73 = 0;
  if ( (uint8_t)sub_443430(&v83) == 0 )  // 读 token 到 string + 国家码标记
  {
LABEL_190:
    sub_4F1990(&v57);  // 调 sub_4F1990
    *(uint32_t *)pszArg12 = sub_4A2F80(v2);
    v42 = *(uint32_t *)&pszArg12[4 * dword_78FF38 + 400];
    v53 = -1;
    v43 = (std::_String_base *)(pszArg12 + 4);
    v52 = nullptr;  // v52 = nullptr 空指针
    if ( v42 != 0 )  // 若 v42 != 0
    {
      sub_4014D0(v43, v42, v52, v53);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
      v44 = *(uint32_t *)&pszArg12[4 * dword_78FF38 + 400];
      v53 = -1;
      v52 = nullptr;  // v52 = nullptr 空指针
      v51 = (uint8_t *)(v44 + 28);
    }
    else
    {
      sub_4014D0(v43, *((uint32_t *)pszArg12 + 100), v52, v53);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
      v45 = *((uint32_t *)pszArg12 + 100);
      v53 = -1;
      v52 = nullptr;  // v52 = nullptr 空指针
      v51 = (uint8_t *)(v45 + 28);
    }
    sub_4014D0((std::_String_base *)(pszArg12 + 32), v51, v52, v53);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
    if ( Block != nullptr )  // 若 Block 非空
      j__free(Block);  // 调 j__free
    Block = nullptr;  // Block = nullptr 空指针
    v68 = 0;
    v69 = 0;
    if ( v63 != nullptr )  // 若 v63 非空
      j__free(v63);  // 调 j__free
    v46 = v59;
    v63 = nullptr;  // v63 = nullptr 空指针
    v64 = 0;
    v65 = 0;
    if ( v59 != nullptr )  // 若 v59 非空
    {
      v47 = v60;
      if ( v59 != v60 )  // 若 v59 != v60
      {
        v48 = (char *)v59 + 24;
        do
        {
          if ( *(uint32_t *)v48 != 0 )  // 若 *(uint32_t *)v48 != 0
            j__free(*(void **)v48);  // 调 j__free
          *(uint32_t *)v48 = 0;
          *((uint32_t *)v48 + 1) = 0;
          *((uint32_t *)v48 + 2) = 0;
          if ( *((uint32_t *)v48 - 4) != 0 )  // 若 *((uint32_t *)v48 - 4) != 0
            j__free(*((void **)v48 - 4));  // 调 j__free
          *((uint32_t *)v48 - 4) = 0;
          *((uint32_t *)v48 - 3) = 0;
          *((uint32_t *)v48 - 2) = 0;
          v48 += 36;
        }
        while ( v48 - 24 != v47 );  // 当 v48 - 24 != v47 循环
        v46 = v59;
      }
      j__free(v46);  // 调 j__free
    }
    v59 = nullptr;  // v59 = nullptr 空指针
    v60 = nullptr;  // v60 = nullptr 空指针
    v61 = 0;
    if ( v79 >= 0x10 )  // 若 v79 >= 0x10
      j__free(v77);  // 调 j__free
    v79 = 15;
    v78 = 0;
    LOBYTE(v77) = 0;
    if ( v86 >= 0x10 )  // 若 v86 >= 0x10
      j__free(v84);  // 调 j__free
    return 1;
  }
  while ( 1 )  // 当 1 循环
  {
    sub_442B20(&v83);  // 国家码标签配对校验（void）
    if ( sub_40BF00((std::_String_base *)&v83, 0, v85, "[name]", 6u) == 0 )  // 字符串 “[name]”
    {
      v53 = *((uint32_t *)pszArg12 + 100);
      sub_443370();  // 脚本 token 取串（第三入口）
      goto LABEL_189;  // 跳转 LABEL_189
    }
    if ( sub_40BF00((std::_String_base *)&v83, 0, v85, "[explain]", 9u) == 0 )  // 字符串 “[explain]”
    {
      v53 = *((uint32_t *)pszArg12 + 100) + 28;
      sub_443370();  // 脚本 token 取串（第三入口）
      goto LABEL_189;  // 跳转 LABEL_189
    }
    if ( sub_40BF00((std::_String_base *)&v83, 0, v85, "[entering title]", 0x10u) == 0 )  // 字符串 “[entering title]”
    {
      v53 = (unsigned int)(pszArg12 + 60);
      sub_443370();  // 脚本 token 取串（第三入口）
      goto LABEL_189;  // 跳转 LABEL_189
    }
    if ( sub_40BF00((std::_String_base *)&v83, 0, v85, "[cutscene image]", 0x10u) == 0 )  // 字符串 “[cutscene image]”
    {
      v53 = (unsigned int)(pszArg12 + 88);
      sub_443370();  // 脚本 token 取串（第三入口）
      *((uint32_t *)pszArg12 + 29) = sub_4423D0(nullptr);
      goto LABEL_189;  // 跳转 LABEL_189
    }
    if ( (uint8_t)sub_423300(&v83, "[minimap image]") != 0 )  // 字符串 “[minimap image]”
    {
      v53 = (unsigned int)(pszArg12 + 120);
      sub_443370();  // 脚本 token 取串（第三入口）
      goto LABEL_189;  // 跳转 LABEL_189
    }
    if ( (uint8_t)sub_423300(&v83, "[worldmap info]") != 0 )  // 字符串 “[worldmap info]”
    {
      v4 = (int *)(pszArg12 + 148);
      for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
      {
        for ( j = 2; j != 0; --j )  // 循环：j = 2; j != 0; --j
          *v4++ = sub_4423D0(nullptr);  // *v4++ 写入 sub_4423D0(nullptr)
      }
      v53 = (unsigned int)(pszArg1 + 164);
      sub_443370();  // 脚本 token 取串（第三入口）
      pszArg12 = pszArg1;
      goto LABEL_189;  // 跳转 LABEL_189
    }
    if ( (uint8_t)sub_423300(&v83, "[minimum required level]") != 0 )  // 字符串 “[minimum required level]”
    {
      *((uint32_t *)pszArg12 + 48) = sub_4423D0(nullptr);
      goto LABEL_189;  // 跳转 LABEL_189
    }
    if ( (uint8_t)sub_423300(&v83, "[required item]") != 0 )  // 字符串 “[required item]”
    {
      v7 = sub_4423D0(nullptr);  // 调 sub_4423D0
      v52 = nullptr;  // v52 = nullptr 空指针
      *((uint32_t *)pszArg12 + 49) = v7;
      v8 = sub_4423D0(v52);  // 调 sub_4423D0
      v51 = nullptr;  // v51 = nullptr 空指针
      *((uint32_t *)pszArg12 + 50) = v8;
      pszArg12[204] = sub_4423D0(v51) != 0;  // pszArg12[204] 写入 sub_4423D0(v51) != 0
      goto LABEL_189;  // 跳转 LABEL_189
    }
    if ( (uint8_t)sub_423300(&v83, "[coin limit]") != 0 )  // 字符串 “[coin limit]”
    {
      *((uint32_t *)pszArg12 + 52) = sub_4423D0(nullptr);
      goto LABEL_189;  // 跳转 LABEL_189
    }
    if ( (uint8_t)sub_423300(&v83, "[basis level]") != 0 )  // 字符串 “[basis level]”
    {
      *((uint32_t *)pszArg12 + 53) = sub_4423D0(nullptr);
      goto LABEL_189;  // 跳转 LABEL_189
    }
    if ( (uint8_t)sub_423300(&v83, "[experience increasing point]") != 0 )  // 字符串 “[experience increasing point]”
    {
      *((float *)pszArg12 + 54) = sub_442480(nullptr);  // 脚本 token 数值解析（double 版）
      goto LABEL_189;  // 跳转 LABEL_189
    }
    if ( (uint8_t)sub_423300(&v83, "[champion]") == 0 )  // 字符串 “[champion]”
      break;
    v9 = (int *)(pszArg1 + 220);
    for ( k = 4; k != 0; --k )  // 循环：k = 4; k != 0; --k
      *v9++ = sub_4423D0(nullptr);  // *v9++ 写入 sub_4423D0(nullptr)
    pszArg12 = pszArg1;
LABEL_189:
    v2 = (const char *)ArgList;
    if ( (uint8_t)sub_443430(&v83) == 0 )  // 读 token 到 string + 国家码标记
      goto LABEL_190;  // 跳转 LABEL_190
  }
  if ( (uint8_t)sub_423300(&v83, "[item]") != 0 )  // 字符串 “[item]”
  {
    sub_5E5260((void **)pszArg12 + 59);  // 调 sub_5E5260
    for ( m = sub_4423D0(&v75); v75 != 0; m = sub_4423D0(&v75) )  // 循环：m = sub_4423D0(&v75); v75 != 0; m = sub_4423D0(&v75)
    {
      v56[0] = m;
      v56[1] = sub_4423D0(nullptr);  // 调 sub_4423D0
      sub_474950(v56);  // 调 sub_474950
    }
    goto LABEL_189;  // 跳转 LABEL_189
  }
  if ( (uint8_t)sub_423300(&v83, "[pathgate object]") != 0 )  // 字符串 “[pathgate object]”
  {
    v12 = (int *)(pszArg1 + 252);
    for ( n = 3; n != 0; --n )  // 循环：n = 3; n != 0; --n
      *v12++ = sub_4423D0(nullptr);  // *v12++ 写入 sub_4423D0(nullptr)
    v14 = (int *)(pszArg1 + 264);
    for ( ii = 3; ii != 0; --ii )  // 循环：ii = 3; ii != 0; --ii
      *v14++ = sub_4423D0(nullptr);  // *v14++ 写入 sub_4423D0(nullptr)
    v16 = (int *)(pszArg1 + 276);
    for ( jj = 2; jj != 0; --jj )  // 循环：jj = 2; jj != 0; --jj
      *v16++ = sub_4423D0(nullptr);  // *v16++ 写入 sub_4423D0(nullptr)
    v18 = (int *)(pszArg1 + 288);
    for ( kk = 2; kk != 0; --kk )  // 循环：kk = 2; kk != 0; --kk
      *v18++ = sub_4423D0(nullptr);  // *v18++ 写入 sub_4423D0(nullptr)
    pszArg12 = pszArg1;
    goto LABEL_189;  // 跳转 LABEL_189
  }
  if ( (uint8_t)sub_423300(&v83, "[maze info]") != 0 )  // 字符串 “[maze info]”
  {
    if ( v73 != 0 )  // 若 v73 != 0
    {
      sub_4F1990(&v57);  // 调 sub_4F1990
      sub_4F0D10(&v57);  // 调 sub_4F0D10
    }
    else
    {
      v73 = 1;
    }
    goto LABEL_189;  // 跳转 LABEL_189
  }
  if ( (uint8_t)sub_423300(&v83, "[size]") != 0 )  // 字符串 “[size]”
  {
    v57 = sub_4423D0(nullptr);  // 调 sub_4423D0
    v58 = sub_4423D0(nullptr);  // 调 sub_4423D0
    sub_4F14B0(v57 * v58);  // 调 sub_4F14B0
    goto LABEL_189;  // 跳转 LABEL_189
  }
  if ( (uint8_t)sub_423300(&v83, "[greed]") == 0 )  // 字符串 “[greed]”
  {
    if ( (uint8_t)sub_423300(&v83, "[map specification]") != 0 )  // 字符串 “[map specification]”
    {
      v29 = sub_4423D0(nullptr);  // 调 sub_4423D0
      v30 = (void **)((char *)v59 + 36 * v29 + 36 * v57 * sub_4423D0(nullptr) + 4);
      sub_5E5260(v30);  // 调 sub_5E5260
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )  // 循环：mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75)
        sub_431230((int)v30, &mm);  // uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(&v83, "[boss map specification]") != 0 )  // 字符串 “[boss map specification]”
    {
      v31 = sub_4423D0(nullptr);  // 调 sub_4423D0
      v32 = (void **)((char *)v59 + 36 * v31 + 36 * v57 * sub_4423D0(nullptr) + 20);
      sub_5E5260(v32);  // 调 sub_5E5260
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )  // 循环：mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75)
        sub_431230((int)v32, &mm);  // uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(&v83, "[start map]") != 0 )  // 字符串 “[start map]”
    {
      sub_5E5260(&v62);  // 调 sub_5E5260
      for ( nn = sub_4423D0(&v75); v75 != 0; nn = sub_4423D0(&v75) )  // 循环：nn = sub_4423D0(&v75); v75 != 0; nn = sub_4423D0(&v75)
      {
        v55[0] = nn;
        v55[1] = sub_4423D0(nullptr);  // 调 sub_4423D0
        sub_474950(v55);  // 调 sub_474950
      }
    }
    else if ( (uint8_t)sub_423300(&v83, "[boss map]") != 0 )  // 字符串 “[boss map]”
    {
      sub_5E5260(&v66);  // 调 sub_5E5260
      for ( i1 = sub_4423D0(&v75); v75 != 0; i1 = sub_4423D0(&v75) )  // 循环：i1 = sub_4423D0(&v75); v75 != 0; i1 = sub_4423D0(&v75)
      {
        v54[0] = i1;
        v54[1] = sub_4423D0(nullptr);  // 调 sub_4423D0
        sub_474950(v54);  // 调 sub_474950
      }
    }
    else if ( (uint8_t)sub_423300(&v83, "[warroom map index]") != 0 )  // 字符串 “[warroom map index]”
    {
      *((uint32_t *)pszArg12 + 104) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[monster type spawn prob]") != 0 )  // 字符串 “[monster type spawn prob]”
    {
      v35 = (int *)(pszArg1 + 612);
      for ( i2 = 4; i2 != 0; --i2 )  // 循环：i2 = 4; i2 != 0; --i2
        *v35++ = sub_4423D0(nullptr);  // *v35++ 写入 sub_4423D0(nullptr)
      pszArg12 = pszArg1;
    }
    else if ( (uint8_t)sub_423300(&v83, "[monster type spawn cost]") != 0 )  // 字符串 “[monster type spawn cost]”
    {
      v37 = (int *)(pszArg1 + 628);
      for ( i3 = 4; i3 != 0; --i3 )  // 循环：i3 = 4; i3 != 0; --i3
        *v37++ = sub_4423D0(nullptr);  // *v37++ 写入 sub_4423D0(nullptr)
      pszArg12 = pszArg1;
    }
    else if ( (uint8_t)sub_423300(&v83, "[monster type spawn interval rate]") != 0 )  // 字符串 “[monster type spawn interval rate]”
    {
      v39 = (float *)(pszArg1 + 652);
      for ( i4 = 4; i4 != 0; --i4 )  // 循环：i4 = 4; i4 != 0; --i4
        *v39++ = sub_442480(nullptr);  // 脚本 token 数值解析（double 版）
      pszArg12 = pszArg1;
    }
    else if ( (uint8_t)sub_423300(&v83, "[monster spawn base interval]") != 0 )  // 字符串 “[monster spawn base interval]”
    {
      *((uint32_t *)pszArg12 + 167) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[monster spawn random interval]") != 0 )  // 字符串 “[monster spawn random interval]”
    {
      *((uint32_t *)pszArg12 + 168) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[fatigue]") != 0 )  // 字符串 “[fatigue]”
    {
      *((uint32_t *)pszArg12 + 169) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[fatigue result]") != 0 )  // 字符串 “[fatigue result]”
    {
      *((uint32_t *)pszArg12 + 170) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[max monster]") != 0 )  // 字符串 “[max monster]”
    {
      *((uint32_t *)pszArg12 + 162) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[player kc]") != 0 )  // 字符串 “[player kc]”
    {
      *((uint32_t *)pszArg12 + 161) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn common monster index]") != 0 )  // 字符串 “[spawn common monster index]”
    {
      sub_5E5260((void **)pszArg12 + 105);  // 调 sub_5E5260
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )  // 循环：mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75)
        sub_431230((int)(pszArg12 + 420), &mm);  // uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn common champion index]") != 0 )  // 字符串 “[spawn common champion index]”
    {
      sub_5E5260((void **)pszArg12 + 109);  // 调 sub_5E5260
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )  // 循环：mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75)
        sub_431230((int)(pszArg12 + 436), &mm);  // uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn super champion index]") != 0 )  // 字符串 “[spawn super champion index]”
    {
      sub_5E5260((void **)pszArg12 + 113);  // 调 sub_5E5260
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )  // 循环：mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75)
        sub_431230((int)(pszArg12 + 452), &mm);  // uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn boss index]") != 0 )  // 字符串 “[spawn boss index]”
    {
      sub_5E5260((void **)pszArg12 + 117);  // 调 sub_5E5260
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )  // 循环：mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75)
        sub_431230((int)(pszArg12 + 468), &mm);  // uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn step max]") != 0 )  // 字符串 “[spawn step max]”
    {
      *((uint32_t *)pszArg12 + 125) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[spawn step resource pool]") != 0 )  // 字符串 “[spawn step resource pool]”
    {
      sub_5E5260((void **)pszArg12 + 121);  // 调 sub_5E5260
      for ( i5 = sub_4423D0(&v75); v75 != 0; i5 = sub_4423D0(&v75) )  // 循环：i5 = sub_4423D0(&v75); v75 != 0; i5 = sub_4423D0(&v75)
        sub_431230((int)(pszArg12 + 484), &i5);  // uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(&v83, "[kill count const]") != 0 )  // 字符串 “[kill count const]”
    {
      *((float *)pszArg12 + 152) = sub_442480(nullptr);  // 脚本 token 数值解析（double 版）
    }
    else if ( (uint8_t)sub_423300(&v83, "[join cost gold]") != 0 )  // 字符串 “[join cost gold]”
    {
      *((uint32_t *)pszArg12 + 126) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[gold drop prob]") != 0 )  // 字符串 “[gold drop prob]”
    {
      *((uint32_t *)pszArg12 + 127) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[common monster item drop prob]") != 0 )  // 字符串 “[common monster item drop prob]”
    {
      *((uint32_t *)pszArg12 + 128) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[common champion item drop prob]") != 0 )  // 字符串 “[common champion item drop prob]”
    {
      *((uint32_t *)pszArg12 + 129) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[super champion item drop prob]") != 0 )  // 字符串 “[super champion item drop prob]”
    {
      *((uint32_t *)pszArg12 + 130) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[boss item drop prob]") != 0 )  // 字符串 “[boss item drop prob]”
    {
      *((uint32_t *)pszArg12 + 131) = sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[common monster exp const]") != 0 )  // 字符串 “[common monster exp const]”
    {
      *((uint32_t *)pszArg12 + 148) = 5 * sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[common champion exp const]") != 0 )  // 字符串 “[common champion exp const]”
    {
      *((uint32_t *)pszArg12 + 149) = 5 * sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[super champion exp const]") != 0 )  // 字符串 “[super champion exp const]”
    {
      *((uint32_t *)pszArg12 + 150) = 5 * sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[boss exp const]") != 0 )  // 字符串 “[boss exp const]”
    {
      *((uint32_t *)pszArg12 + 151) = 5 * sub_4423D0(nullptr);
    }
    else if ( (uint8_t)sub_423300(&v83, "[common monster item drop list]") != 0 )  // 字符串 “[common monster item drop list]”
    {
      sub_5E5260((void **)pszArg12 + 132);  // 调 sub_5E5260
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )  // 循环：mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75)
        sub_431230((int)(pszArg12 + 528), &mm);  // uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(&v83, "[common champion item drop list]") != 0 )  // 字符串 “[common champion item drop list]”
    {
      sub_5E5260((void **)pszArg12 + 136);  // 调 sub_5E5260
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )  // 循环：mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75)
        sub_431230((int)(pszArg12 + 544), &mm);  // uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(&v83, "[super champion item drop list]") != 0 )  // 字符串 “[super champion item drop list]”
    {
      sub_5E5260((void **)pszArg12 + 136);  // 调 sub_5E5260
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )  // 循环：mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75)
        sub_431230((int)(pszArg12 + 560), &mm);  // uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(&v83, "[boss item drop list]") != 0 )  // 字符串 “[boss item drop list]”
    {
      sub_5E5260((void **)pszArg12 + 144);  // 调 sub_5E5260
      for ( mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75) )  // 循环：mm = sub_4423D0(&v75); v75 != 0; mm = sub_4423D0(&v75)
        sub_431230((int)(pszArg12 + 576), &mm);  // uint32 vector push_back
    }
    else if ( (uint8_t)sub_423300(&v83, "[ancient dungeon]") != 0 )  // 字符串 “[ancient dungeon]”
    {
      pszArg12[684] = sub_4423D0(nullptr) != 0;  // pszArg12[684] 写入 sub_4423D0(nullptr) != 0
    }
    else
    {
      v70 = v50;
      sub_401690(&v83);  // std::string 拷贝构造（复位 +20/+24/+4 后 ·sub_4014D0 全
      if ( sub_442C80((char)v50[0], v50[1], (int)v50[2], (int)v50[3], (int)v51, (int)v52, v53) == 0 )  // 判首字符方括号并析构
      {
        v41 = (const char *)v84;
        if ( v86 < 0x10 )  // 若 v86 < 0x10
          v41 = (const char *)&v84;
        off_77F3FC("SCRIPT TAG ERROR! [%s] %s", v2, v41);  // 字符串 “SCRIPT TAG ERROR! [%s] %s”
      }
    }
    goto LABEL_189;  // 跳转 LABEL_189
  }
  v53 = (unsigned int)v76;
  sub_443370();  // 脚本 token 取串（第三入口）
  v71 = 0;
  mm = 0;
  v70 = (void ***)(v78 - 1);
  if ( v78 - 1 <= 0 )  // 若 v78 - 1 <= 0
    goto LABEL_189;  // 跳转 LABEL_189
  i5 = 0;
  while ( 2 )  // 当 2 循环
  {
    sub_4BD650(v80, mm, 2);  // std::string 拷贝构造到 pArg2
    v20 = (uint8_t *)v81[0];
    if ( v82 < 0x10 )  // 若 v82 < 0x10
      v20 = v81;
    if ( *v20 == 13 )  // 若 *v20 == 13
      goto LABEL_76;  // 跳转 LABEL_76
    v21 = (uint8_t *)v81[0];
    if ( v82 < 0x10 )  // 若 v82 < 0x10
      v21 = v81;
    if ( *v21 == 10 )  // 若 *v21 == 10
      goto LABEL_76;  // 跳转 LABEL_76
    v22 = (uint8_t *)v81[0];
    if ( v82 < 0x10 )  // 若 v82 < 0x10
      v22 = v81;
    if ( *v22 == 32 )  // 若 *v22 == 32
    {
LABEL_76:
      v28 = mm + 1;
    }
    else
    {
      for ( i6 = 0; i6 < 16; ++i6 )  // 循环：i6 = 0; i6 < 16; ++i6
      {
        v24 = (uint8_t *)v81[0];
        if ( v82 < 0x10 )  // 若 v82 < 0x10
          v24 = v81;
        v25 = *(uint8_t **)(dword_9B0AB0 + 4 * i6);
        if ( *v24 == *v25 )  // 若 *v24 == *v25
        {
          v26 = (uint32_t *)v81[0];
          if ( v82 < 0x10 )  // 若 v82 < 0x10
            v26 = v81;
          if ( *((uint8_t *)v26 + 1) == v25[1] )  // 若 *((uint8_t *)v26 + 1) == v25[1]
            break;
        }
      }
      if ( i6 == 16 )  // 若 i6 == 16
      {
        ++mm;  // 自增mm
        ++v71;  // 自增v71
        goto LABEL_78;  // 跳转 LABEL_78
      }
      v27 = i5;
      *(uint32_t *)((char *)v59 + i5) = i6;
      i5 = v27 + 36;
      v28 = mm + 2;
    }
    mm = v28;
LABEL_78:
    sub_501490(v80);  // 调 sub_501490
    if ( mm < (int)v70 )  // 若 mm < (int)v70
      continue;
    break;
  }
  if ( v71 == 0 )  // 若 v71 == 0
    goto LABEL_189;  // 跳转 LABEL_189
  sub_4750B0(&v57);  // 调 sub_4750B0
  sub_501490(v76);  // 调 sub_501490
  sub_501490(&v83);  // 调 sub_501490
  return 0;
}


// ============================================================
// §C 0x4F2B90-0x4F2E80 物品对象虚函数与 RTTI 族（IRDItem__vmt* —— 物品基类 IRDItem 的方法实现）
// ============================================================

// ------------------------------------------------------------
// 0x4F2B90 sub_4F2B90
//   售价公式：nArg1 × 全局系数 dword_9B6A50 / 1000；nArg3 非 0 时再 ×nArg2/nArg3。
//   IRDItem__vmt60（售价虚方法）用它算最终售价。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2B90(int nArg1, int nArg2, int nArg3)
{
  int result; // eax

  result = nArg1 * dword_9B6A50 / 1000;
  if ( nArg3 != 0 )  // 若 nArg3 != 0
    return nArg2 * result / nArg3;
  return result;
}



// ------------------------------------------------------------
// 0x4F2BC0 sub_4F2BC0
//   释放全局精炼特效精灵 dword_9B0C64：先虚调用清理再置空。
// ------------------------------------------------------------
int sub_4F2BC0()
{
  int result; // eax

  if ( dword_9B0C64 != 0 )  // 若 dword_9B0C64 != 0
    result = (**(int (/*thiscall*/ ***)(int, int))dword_9B0C64)(dword_9B0C64, 1);
  dword_9B0C64 = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4F2BE0 sub_4F2BE0
//   物品条目重置：+0x04/+0x80 清零、名称串（+0x84，sub_41A590）置空、+0x92 标志清零。
// ------------------------------------------------------------
int /*fastcall*/ sub_4F2BE0(int pArg1, int nArg2)
{
  int result; // eax

  *(uint32_t *)(pArg1 + 4) = 0;  // pArg1+4 = 0
  *(uint32_t *)(pArg1 + 128) = 0;  // pArg1+128 = 0
  result = sub_41A590(pArg1 + 132, nArg2, 0);  // 结果 = crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(uint8_t *)(pArg1 + 146) = 0;  // pArg1+146 = 0
  return result;
}



// ------------------------------------------------------------
// 0x4F2C10 sub_4F2C10
//   地面物品绘制：精灵绘制（vt+152）后数量 Value>1 时在 (x+27,y+1) 叠加
//   数量文本（sub_69A110 文本渲染）。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2C10(int pArg1, int pArg2, int nArg3, int Value)
{
  int result; // eax

  if ( nArg3 != 0 )  // 若 nArg3 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)nArg3 + 152))(nArg3, pArg1, pArg2, dword_79C0B0);  // 调用虚函数槽 +152
  result = Value;
  if ( Value > 1 )  // 若 Value > 1
    return sub_69A110(pArg1 + 27, pArg2 + 1, Value, -1);  // 调 sub_69A110
  return result;
}



// ------------------------------------------------------------
// 0x4F2C60 IRDItem__vmt14 —— 物品标记位包含判定（UI 过滤谓词）
//   返回 (nArg2 位 & 物品标记字 this+4) == nArg2：查询置位须全部命中。
// ------------------------------------------------------------
bool /*thiscall*/ IRDItem__vmt14(uint32_t *this, int nArg2)  // 函数: 物品标记位包含判定（UI 过滤谓词）
{
  return (nArg2 & *(this + 1)) == nArg2;
}



// ------------------------------------------------------------
// 0x4F2C80 IRDItem__vmt28 —— 物品计数设置与槽汇总刷新
//   uArg2 超过当前计数（sub_41A5E0(this+132)）时先 sub_5473D0 刷新物品栏，再 sub_41A590 写计数；
//   对象 +128 存在时末尾 sub_484D00 重算槽汇总统计（累加各对象虚表 +36）。
// ------------------------------------------------------------
int /*thiscall*/ IRDItem__vmt28(uint32_t *this, unsigned int uArg2)  // 函数: 物品计数设置与槽汇总刷新
{
  unsigned int pThis_21; // edi
  int v4; // edx
  uint32_t *fld_e32; // eax
  int result; // eax

  pThis_21 = (unsigned int)(this + 33);
  if ( uArg2 > sub_41A5E0((unsigned int)(this + 33)) )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    fld_e32 = (uint32_t *)*(this + 32);
    if ( fld_e32 != nullptr && *fld_e32 == 0 )  // 若 fld_e32 != nullptr && *fld_e32 == 0
      sub_5473D0(this);  // 物品栏辅助（484ED0）
  }
  result = sub_41A590(pThis_21, v4, uArg2);  // 结果 = crypt4byte 加密初始化（随机密钥 + 双校验字）
  if ( *(this + 32) != 0 )  // 若 *(this + 32) != 0
    return sub_484D00();  // 槽汇总统计（累加各对象虚表 +36 值）
  return result;
}



// ------------------------------------------------------------
// 0x4F2CE0 sub_4F2CE0
//   按物品 id 取名称串：查模板表（sub_4CE8A0）取 +4/+2120 处串；
//   id=0 → 全局串 868；未登记 → "NONE"。
// ------------------------------------------------------------
const char */*cdecl*/ sub_4F2CE0(int nArg1)
{
  int v2; // eax
  int v3; // eax

  if ( nArg1 == 0 )  // 若 nArg1 == 0
    return (const char *)sub_422E70(868);
  v2 = sub_4CE8A0(nArg1);  // 调 sub_4CE8A0
  if ( v2 != 0 )  // 若 v2 != 0
    return (const char *)sub_41ACF0(v2 + 4);  // 驻留串句柄 → 字符串指针
  v3 = sub_4CE8A0(nArg1);  // 调 sub_4CE8A0
  if ( v3 != 0 )  // 若 v3 != 0
    return (const char *)sub_41ACF0(v3 + 2120);  // 驻留串句柄 → 字符串指针
  else
    return "NONE";  // 字符串 “NONE”
}



// ------------------------------------------------------------
// 0x4F2D40 sub_4F2D40
//   模板登记判定：物品 id 在模板表（sub_4CE8A0）命中 → 2，否则 1。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2D40(int nArg1)
{
  return (sub_4CE8A0(nArg1) != 0) + 1;
}



// ------------------------------------------------------------
// 0x4F2D60 sub_4F2D60
//   取模板字段：命中 → 模板+32；否则模板+16；id 无效 → 0【推断：图标/等级字段】。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2D60(int nArg1)
{
  int v1; // eax
  int v3; // eax

  if ( nArg1 == 0 )  // 若 nArg1 == 0
    return 0;
  v1 = sub_4CE8A0(nArg1);  // 调 sub_4CE8A0
  if ( v1 != 0 )  // 若 v1 != 0
    return *(uint32_t *)(v1 + 32);
  v3 = sub_4CE8A0(nArg1);  // 调 sub_4CE8A0
  if ( v3 != 0 )  // 若 v3 != 0
    return *(uint32_t *)(v3 + 16);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4F2DA0 sub_4F2DA0
//   取模板字段：命中 → 模板+64；否则模板+48（<1 时夹到 1）；id 无效 → 0
//   【推断：堆叠/价格字段】。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2DA0(int nArg1)
{
  int v1; // eax
  int result; // eax
  int v3; // eax

  if ( nArg1 == 0 )  // 若 nArg1 == 0
    return 0;
  v1 = sub_4CE8A0(nArg1);  // 调 sub_4CE8A0
  if ( v1 != 0 )  // 若 v1 != 0
    return *(uint32_t *)(v1 + 64);
  v3 = sub_4CE8A0(nArg1);  // 调 sub_4CE8A0
  if ( v3 == 0 )  // 若 v3 == 0
    return 0;
  result = *(uint32_t *)(v3 + 48);  // result = v3+48
  if ( result < 1 )  // 若 result < 1
    return 1;
  return result;
}



// ------------------------------------------------------------
// 0x4F2DF0 sub_4F2DF0
//   物品名称颜色（按稀有度 0-4）：0→-1（无）, 1→-1190552, 2→-37965,
//   3→-1048321, 4→-16731649；其余 → -16731649（IRDItem__vmt18 用）。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2DF0(int nArg1)
{
  switch ( nArg1 )  // 分支：按 nArg1 分派
  {
    case 0:
      return -1;  // 返回 -1（0xFFFFFFFF）
    case 1:
      return -1190552;  // 返回 -1190552（0xFFEDD568）
    case 2:
      return -37965;  // 返回 -37965（0xFFFF6BB3）
    case 3:
      return -1048321;  // 返回 -1048321（0xFFF000FF）
    default:
      break;
  }
  return nArg1 != 4 ? -1 : -16731649;
}



// ------------------------------------------------------------
// 0x4F2E40 sub_4F2E40
//   掉落图标绘制：渲染状态进出（sub_491530/491630）中经掉落物精灵
//   dword_9B0C60（vt+152）绘制到 (nArg1-1, nArg2-1)。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F2E40(int nArg1, int nArg2)
{
  sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
  if ( dword_9B0C60 != 0 )  // 若 dword_9B0C60 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_9B0C60 + 152))(
      dword_9B0C60,
      nArg1 - 1,
      nArg2 - 1,
      dword_79C0B0);
  return sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
}



// ------------------------------------------------------------
// 0x4F2E80 sub_4F2E80
//   掉落物阴影绘制：高度 nArg4<0 → 按落点帧（418DD0(nArg4/-50)）画贴图阴影；
//   否则地面椭圆阴影（精灵 dword_9B0C68 vt+128，半透明 0x81000001），
//   高度换算 28*nArg4/nArg3。
// ------------------------------------------------------------
void /*cdecl*/ sub_4F2E80(int nArg1, int nArg2, int nArg3, int nArg4)
{
  uint32_t *v4; // ecx
  int pObj; // eax

  if ( nArg3 != 0 )  // 若 nArg3 != 0
  {
    if ( nArg4 <= 0 )  // 若 nArg4 <= 0
    {
      if ( nArg4 > -450 )  // 若 nArg4 > -450
      {
        sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
        pObj = sub_418DD0(nArg4 / -50);  // 调 sub_418DD0
        if ( pObj != 0 )  // 若 pObj != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, nArg1, nArg2, dword_79C0B0);  // 调用虚函数槽 +152
        sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
      }
    }
    else
    {
      v4 = (uint32_t *)dword_79C0B0;
      *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0+48 = 0
      v4[13] = 0;
      v4[14] = 640;
      v4[15] = nArg2 + 28 * nArg4 / nArg3;  // v4[15] 写入 nArg2 + 28 * nArg4 / nArg3
      if ( dword_9B0C68 != 0 )  // 若 dword_9B0C68 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)dword_9B0C68 + 128))(
          dword_9B0C68,
          nArg1,
          nArg2,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          -2130706433,
          1333788672,
          1333788672);
      sub_488670(dword_79C0B0);  // 视口重置 640x480
    }
  }
}



// ------------------------------------------------------------
// 0x4F2F70 IRDItem__vmt60 —— 物品数值派生（装备/非装备双路径）【推断】
//   非装备分支 = dword_9B6A50（全局系数首项）× 堆叠数 this+56 / 1000；装备分支经 vmt172/vmt188
//   取强化附加计数（sub_41A5E0）后转 sub_4F2B90 合成【推断：耐久/价格系】。
// ------------------------------------------------------------
int /*thiscall*/ IRDItem__vmt60(int *this)  // 函数: 物品数值派生（装备/非装备双路径）【推断】
{
  int pObj; // eax
  int pObj2; // esi
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // eax

  if ( *(this + 14) == 0 || (*(uint8_t (/*thiscall*/ **)(int *))(*this + 72))(this) == 0 )  // 虚调用 vt+72
    return 0;
  pObj = __RTDynamicCast((int)this, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
  pObj2 = pObj;
  if ( pObj == 0 )  // 若 pObj == 0
    return dword_9B6A50 * *(this + 14) / 1000;
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj);  // 调用虚函数槽 +172
  v5 = sub_41A5E0(v4 + 18);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 188))(pObj2);  // 调用虚函数槽 +188
  v7 = sub_41A5E0(v6 + 32);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_4F2B90(*(this + 14), v7, v5);  // 调 sub_4F2B90
}



// ------------------------------------------------------------
// 0x4F3010 IRDItem__vmt64 —— 显示数量经本地玩家钩子修正后取 vmt112
//   先取 this+72 初值；dword_8F7C04（本地玩家）存在时经其 vt+1168 二次修正，再委托 vmt112。
// ------------------------------------------------------------
int /*thiscall*/ IRDItem__vmt64(uint32_t *this)  // 函数: 显示数量经本地玩家钩子修正后取 vmt112
{
  int fld_e18; // [esp+4h] [ebp-4h] BYREF

  fld_e18 = *(this + 18);  // fld_e18 = this+18
  if ( dword_8F7C04 != 0 )  // 全局 dword_8F7C04 = 本机角色对象
    (*(void (/*thiscall*/ **)(int, uint32_t *, int *))(*(uint32_t *)dword_8F7C04 + 1168))(dword_8F7C04, this, &fld_e18);  // 全局 dword_8F7C04 = 本机角色对象
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 112))(this, fld_e18);  // 虚调用 vt+112
}



// ------------------------------------------------------------
// 0x4F3050 IRDItem__vmt18 —— 物品名称颜色选择（类型 2 走品级/状态分支）
//   类型非 2 → sub_4F2DF0(稀有度 this+92)；类型 2 时校验 vmt172 品级与 vmt236/vmt240 状态
//   标志，命中发白光 -14745736，否则回品级色。
// ------------------------------------------------------------
int /*thiscall*/ IRDItem__vmt18(int *this)  // 函数: 物品名称颜色选择（类型 2 走品级/状态分支）
{
  if ( (*(int (/*thiscall*/ **)(int *))*this)(this) != 2 )
    return sub_4F2DF0(*(this + 23));  // 调 sub_4F2DF0
  if ( *(int *)(*(int (/*thiscall*/ **)(int *))(*this + 172))(this) <= 7 )  // 虚调用 vt+172
    return -16731649;  // 返回 -16731649（0xFF00B1FF）
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 236))(this) != 0  // 虚调用 vt+236
    || (*(uint8_t (/*thiscall*/ **)(int *))(*this + 240))(this) != 0 )  // 虚调用 vt+240
  {
    return -14745736;  // 返回 -14745736（0xFF1EFF78）
  }
  else
  {
    return sub_4F2DF0(*(this + 23));  // 调 sub_4F2DF0
  }
}



// ------------------------------------------------------------
// 0x4F30B0 IRDItem__vmt48 —— 可交互谓词（vmt84 为真且 vmt16 +52 为空）
//   两段虚调用组合的布尔判定，供 UI 选中/可用性过滤。
// ------------------------------------------------------------
BOOL /*thiscall*/ IRDItem__vmt48(void *this)  // 函数: 可交互谓词（vmt84 为真且 vmt16 +52 为空）
{
  return (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 84))(this) != 0
      && *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 16))(this) + 52) == 0;
}



// ------------------------------------------------------------
// 0x4F30E0 IRDItem__vmt8 —— 物品地面绘制主例程（图标/数量/阴影/商城态）
//   按 this+40（→ dword_9B0C48/0C4C）、this+60（→ 0C58）、this+36 状态 {1,3}→0C50、==2→0C54
//   选精灵绘制；数量 vmt44>1 时 sub_69A110 画计数；pszArg5 非零经 vmt120/vmt124 转 sub_4F2E80
//   画阴影；全局态 dword_8F8528+2504 == 2 且 +2512 匹配 this+12 时提前返回。
// ------------------------------------------------------------
void /*thiscall*/ IRDItem__vmt8(uint32_t *this, int pArg2, int pArg3, char pszArg4, char pszArg5)  // 函数: 物品地面绘制主例程（图标/数量/阴影/商城态）
{
  int v6; // eax
  int fld_e19; // ecx
  int fld_e9; // eax  | +0x0024 → 物品状态字（0x4859F0: ==0 直通 / ==3 时须 +40 字节标志非 0）（IRDItem；va=004859F0）
  int v9; // eax
  int v10; // [esp-Ch] [ebp-10h]
  int v11; // [esp+14h] [ebp+10h]

  if ( *((uint8_t *)this + 146) != 0 && pszArg4 == 0 )  // 若 *((uint8_t *)this + 146) != 0 && pszArg4 == 0
  {
    if ( *((uint32_t *)dword_8F8528 + 626) == 2 && *((uint32_t *)dword_8F8528 + 628) == *(this + 3) )  // 全局 dword_8F8528 = 消息/弹窗管理器
      return;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 88))(this, 0);  // 虚调用 vt+88
  }
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 44))(this);  // 结果 = 虚调用 vt+44
  fld_e19 = *(this + 19);  // fld_e19 = this+19
  v11 = v6;
  if ( fld_e19 != 0 )  // 若 fld_e19 != 0
  {
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e19 + 152))(fld_e19, pArg2, pArg3, dword_79C0B0);  // 调用虚函数槽 +152
    v6 = v11;
  }
  if ( v6 > 1 )  // 若 v6 > 1
    sub_69A110(pArg2 + 27, pArg3 + 1, v6, -1);  // 调 sub_69A110
  if ( *((uint8_t *)this + 40) != 0 )  // 若 *((uint8_t *)this + 40) != 0
  {
    if ( dword_9B0C48 != 0 )  // 若 dword_9B0C48 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_9B0C48 + 152))(dword_9B0C48, pArg2, pArg3, dword_79C0B0);  // 调用虚函数槽 +152
    sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    if ( dword_9B0C4C != 0 )  // 若 dword_9B0C4C != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_9B0C4C + 152))(
        dword_9B0C4C,
        pArg2 + 1,
        pArg3 + 1,
        dword_79C0B0);
    sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
  }
  else if ( *(this + 15) != 0 )  // 否则若 *(this + 15) != 0
  {
    if ( dword_9B0C58 != 0 )  // 若 dword_9B0C58 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_9B0C58 + 152))(dword_9B0C58, pArg2, pArg3, dword_79C0B0);  // 调用虚函数槽 +152
  }
  else
  {
    fld_e9 = *(this + 9);  // 读 fld_e9 = this+36（物品状态字）
    if ( fld_e9 == 1 || fld_e9 == 3 )  // 若 fld_e9 == 1 || fld_e9 == 3
    {
      if ( dword_9B0C50 != 0 )  // 若 dword_9B0C50 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_9B0C50 + 152))(dword_9B0C50, pArg2, pArg3, dword_79C0B0);  // 调用虚函数槽 +152
    }
    else if ( fld_e9 == 2 )  // 否则若 fld_e9 == 2
    {
      sub_40FC80(pArg2, pArg3, dword_9B0C54);  // 贴图转发（目标对象虚发 +152(this, x, y)）
    }
  }
  if ( dword_8F7C04 != 0  // 全局 dword_8F7C04 = 本机角色对象
    && (*(uint8_t (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F7C04 + 804))(dword_8F7C04, this) == 0  // 全局 dword_8F7C04 = 本机角色对象
    && dword_9B0C5C != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)dword_9B0C5C + 128))(
      dword_9B0C5C,
      pArg2,
      pArg3,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      1308622847,
      1333788672,
      1333788672);
  }
  if ( pszArg5 != 0 )  // 若 pszArg5 != 0
  {
    v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
    sub_4F2E80(pArg2, pArg3, v9, v10);  // 调 sub_4F2E80
  }
}



// ============================================================
// §D 0x4F32A0-0x4F43D0 物品资源/图标/动画加载族（Item/FieldImage.img、Item/AttachIcon.img、Etc/Disjoint.etc）
// ============================================================

// ------------------------------------------------------------
// 0x4F32A0 sub_4F32A0
//   加载物品地面图标：id=0 → Item/FieldImage.img 索引 26；否则按模板 +88/92
//   （未登记时 +68/72）的 (包名, 索引) 从 img 管理器 dword_8F84B8 加载（418DD0）。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F32A0(int nArg1)
{
  int v2; // esi
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // [esp-8h] [ebp-Ch]
  int v7; // [esp-8h] [ebp-Ch]

  if ( nArg1 == 0 )  // 若 nArg1 == 0
  {
    (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Item/FieldImage.img");  // 字符串 “Item/FieldImage.img”
    return sub_418DD0(26);  // 调 sub_418DD0
  }
  v2 = sub_4CE8A0(nArg1);  // 调 sub_4CE8A0
  if ( v2 != 0 )  // 若 v2 != 0
  {
    if ( (uint8_t)sub_42FD40(szPassword) != 0 )  // 字符串不等判定
    {
      v3 = sub_41ACF0(v2 + 88);  // 结果 = 驻留串句柄 → 字符串指针
      v6 = *(uint32_t *)(v2 + 92);  // v6 = v2+92
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v3);  // 调用虚函数槽 +60
      return sub_418DD0(v6);  // 调 sub_418DD0
    }
  }
  else
  {
    v4 = sub_4CE8A0(nArg1);  // 调 sub_4CE8A0
    if ( v4 != 0 && (uint8_t)sub_42FD40(szPassword) != 0 )  // 字符串不等判定
    {
      v5 = sub_41ACF0(v4 + 68);  // 结果 = 驻留串句柄 → 字符串指针
      v7 = *(uint32_t *)(v4 + 72);  // v7 = v4+72
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v5);  // 调用虚函数槽 +60
      return sub_418DD0(v7);  // 调 sub_418DD0
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4F3360 sub_4F3360
//   递归释放物品资源树（_Isnil @+25）：先递归右子树再 free 节点。
// ------------------------------------------------------------
char /*stdcall*/ sub_4F3360(void **Block)  // 函数: 释放后返回
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 25);
  for ( i = Block; result == 0; Block2 = i )  // 循环：i = Block; result == 0; Block2 = i
  {
    sub_4F3360(i[2]);  // 调 sub_4F3360
    i = (void **)*i;
    j__free(Block2);  // 调 j__free
    result = *((uint8_t *)i + 25);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F33A0 sub_4F33A0
//   加载物品 picked/旋转图标：id=0 → 索引 10；模板 +80/84（未登记 +60/64）。
//   同 4F32A0 的另一图集分支。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F33A0(int nArg1)
{
  int v2; // esi
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // [esp-8h] [ebp-Ch]
  int v7; // [esp-8h] [ebp-Ch]

  if ( nArg1 == 0 )  // 若 nArg1 == 0
    return sub_418DD0(10);  // 调 sub_418DD0
  v2 = sub_4CE8A0(nArg1);  // 调 sub_4CE8A0
  if ( v2 != 0 )  // 若 v2 != 0
  {
    if ( (uint8_t)sub_42FD40(szPassword) != 0 )  // 字符串不等判定
    {
      v3 = sub_41ACF0(v2 + 80);  // 结果 = 驻留串句柄 → 字符串指针
      v6 = *(uint32_t *)(v2 + 84);  // v6 = v2+84
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v3);  // 调用虚函数槽 +60
      return sub_418DD0(v6);  // 调 sub_418DD0
    }
  }
  else
  {
    v4 = sub_4CE8A0(nArg1);  // 调 sub_4CE8A0
    if ( v4 != 0 && (uint8_t)sub_42FD40(szPassword) != 0 )  // 字符串不等判定
    {
      v5 = sub_41ACF0(v4 + 60);  // 结果 = 驻留串句柄 → 字符串指针
      v7 = *(uint32_t *)(v4 + 64);  // v7 = v4+64
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v5);  // 调用虚函数槽 +60
      return sub_418DD0(v7);  // 调 sub_418DD0
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4F3460 sub_4F3460
//   物品资源管理全局重置：dword_9B8DBC/9B8DC8 两棵树清空（sub_4F3360）+
//   dword_9B08EC 起的配对表清零。
// ------------------------------------------------------------
int *sub_4F3460()
{
  int *result; // eax

  sub_4F3360(*(void ***)(dword_9B8DBC + 4));  // 调 sub_4F3360
  *(uint32_t *)(dword_9B8DBC + 4) = dword_9B8DBC;  // dword_9B8DBC+4 = dword_9B8DBC
  dword_9B8DC0 = 0;
  *(uint32_t *)dword_9B8DBC = dword_9B8DBC;
  *(uint32_t *)(dword_9B8DBC + 8) = dword_9B8DBC;  // dword_9B8DBC+8 = dword_9B8DBC
  sub_4F3360(*(void ***)(dword_9B8DC8 + 4));  // 调 sub_4F3360
  *(uint32_t *)(dword_9B8DC8 + 4) = dword_9B8DC8;  // dword_9B8DC8+4 = dword_9B8DC8
  dword_9B8DCC = 0;
  *(uint32_t *)dword_9B8DC8 = dword_9B8DC8;
  *(uint32_t *)(dword_9B8DC8 + 8) = dword_9B8DC8;  // dword_9B8DC8+8 = dword_9B8DC8
  result = &dword_9B08EC;
  do
  {
    *(result - 1) = 0;
    *result = 0;  // *result 写入 0
    result += 2;
  }
  while ( (int)result < (int)&dword_9B097C );  // 当 (int)result < (int)&dword_9B097C 循环
  return result;
}



// ------------------------------------------------------------
// 0x4F34F0 sub_4F34F0
//   "vector<T> too long" 异常抛出（length_error），永不返回。
// ------------------------------------------------------------
void /*noreturn*/ sub_4F34F0()  // 函数: 条件抛异常
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4F3560 sub_4F3560
//   物品渲染状态对象清空：+4 起 5 个 16 字节容器、+80 起 4 个 20 字节容器
//   逐个释放，+160 = -1，+168 容器释放归零。
// ------------------------------------------------------------
void /*thiscall*/ sub_4F3560(int this)  // 函数: 释放后返回
{
  int pThis_4; // esi
  int pThis_58; // esi
  int i; // [esp+Ch] [ebp-4h]
  int j; // [esp+Ch] [ebp-4h]

  pThis_4 = this + 4;
  for ( i = 5; i != 0; --i )  // 循环：i = 5; i != 0; --i
  {
    if ( *(uint32_t *)pThis_4 != 0 )  // 若 *(uint32_t *)pThis_4 != 0
      j__free(*(void **)pThis_4);  // 调 j__free
    *(uint32_t *)pThis_4 = 0;
    *(uint32_t *)(pThis_4 + 4) = 0;  // pThis_4+4 = 0
    *(uint32_t *)(pThis_4 + 8) = 0;  // pThis_4+8 = 0
    pThis_4 += 16;
  }
  pThis_58 = this + 88;
  for ( j = 4; j != 0; --j )  // 循环：j = 4; j != 0; --j
  {
    *(uint32_t *)(pThis_58 - 8) = 0;
    if ( *(uint32_t *)pThis_58 != 0 )  // 若 *(uint32_t *)pThis_58 != 0
      j__free(*(void **)pThis_58);  // 调 j__free
    *(uint32_t *)pThis_58 = 0;
    *(uint32_t *)(pThis_58 + 4) = 0;  // pThis_58+4 = 0
    *(uint32_t *)(pThis_58 + 8) = 0;  // pThis_58+8 = 0
    pThis_58 += 20;
  }
  *(uint32_t *)(this + 160) = -1;  // this+160 = -1
  if ( *(uint32_t *)(this + 168) != 0 )  // 若 *(uint32_t *)(this + 168) != 0
    j__free(*(void **)(this + 168));  // 调 j__free
  *(uint32_t *)(this + 168) = 0;  // this+168 = 0
  *(uint32_t *)(this + 172) = 0;  // this+172 = 0
  *(uint32_t *)(this + 176) = 0;  // this+176 = 0
  *(uint32_t *)(this + 180) = 0;  // this+180 = 0
  *(uint32_t *)(this + 184) = 0;  // this+184 = 0
}



// ------------------------------------------------------------
// 0x4F3610 sub_4F3610
//   物品渲染状态对象析构：eh vector destructor 迭代析构三组内嵌数组
//   （+68:0x14×4、+20:0x14×4、+0:0x10×5）并释放 +168 容器。
// ------------------------------------------------------------
void /*thiscall*/ sub_4F3610(void **this)  // 函数: 释放后返回
{
  `eh vector destructor iterator'(this + 68, 0x14u, 4, sub_42D400);
  if ( *(this + 42) != nullptr )  // 若 *(this + 42) != nullptr
    j__free(*(this + 42));  // 调 j__free
  *(this + 42) = nullptr;  // this+168 = nullptr
  *(this + 43) = nullptr;  // this+172 = nullptr
  *(this + 44) = nullptr;  // this+176 = nullptr
  `eh vector destructor iterator'(this + 20, 0x14u, 4, sub_42D400);
  `eh vector destructor iterator'(this, 0x10u, 5, (void (/*thiscall*/ *)(void *))sub_5E5260);
}



// ------------------------------------------------------------
// 0x4F36B0 sub_4F36B0
//   拼接物品属性附加串（空格分隔）：重量段（5486B0 名字 + 全局串 424）、
//   424/870/871 两段 sprintf、425 尾段；结果写入 pArg1 的 std::string。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F36B0(int pArg1, int nArg2, int nArg3, int nArg4, int nArg5)  // 函数: 释放后返回
{
  const char *psz; // eax
  const char *psz2; // eax
  const char *v7; // eax
  const char *v8; // eax
  const char *v9; // eax
  char Buffer[64]; // [esp+Ch] [ebp-6Ch] BYREF
  uint8_t v12[4]; // [esp+4Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+50h] [ebp-28h]
  int v14; // [esp+60h] [ebp-18h]
  unsigned int v15; // [esp+64h] [ebp-14h]
  int dword_796E502; // [esp+68h] [ebp-10h]
  int v17; // [esp+74h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  v17 = 0;
  if ( nArg2 != 0 )  // 若 nArg2 != 0
  {
    psz = (const char *)sub_5486B0(nArg2);  // 结果 = 物品栏标题组装
    sub_4022F0((std::_String_base *)v12, psz, strlen(psz));  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qme
    psz2 = (const char *)sub_422E70(424);
    sub_4022F0((std::_String_base *)v12, psz2, strlen(psz2));  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qme
  }
  if ( nArg3 != 0 )  // 若 nArg3 != 0
  {
    if ( v14 != 0 )  // 若 v14 != 0
      sub_4022F0((std::_String_base *)v12, " ", 1);  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qme
    v7 = (const char *)sub_422E70(870);
    sprintf(Buffer, v7, nArg3);  // 调 sprintf 格式化
    sub_4022F0((std::_String_base *)v12, Buffer, strlen(Buffer));  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qme
  }
  if ( nArg4 != 0 )  // 若 nArg4 != 0
  {
    if ( v14 != 0 )  // 若 v14 != 0
      sub_4022F0((std::_String_base *)v12, " ", 1);  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qme
    v8 = (const char *)sub_422E70(871);
    sprintf(Buffer, v8, nArg4);  // 调 sprintf 格式化
    sub_4022F0((std::_String_base *)v12, Buffer, strlen(Buffer));  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qme
  }
  if ( nArg5 != 0 )  // 若 nArg5 != 0
  {
    v9 = (const char *)sub_422E70(425);
    sprintf(Buffer, "%d%s", nArg5, v9);  // 字符串 “%d%s”
    sub_4022F0((std::_String_base *)v12, Buffer, strlen(Buffer));  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qme
  }
  *(uint32_t *)(pArg1 + 24) = 15;  // pArg1+24 = 15
  *(uint32_t *)(pArg1 + 20) = 0;  // pArg1+20 = 0
  *(uint8_t *)(pArg1 + 4) = 0;  // pArg1+4 = 0
  sub_4014D0((std::_String_base *)pArg1, v12, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
  if ( v15 >= 0x10 )  // 若 v15 >= 0x10
    j__free(Block);  // 调 j__free
  return pArg1;
}



// ------------------------------------------------------------
// 0x4F3880 sub_4F3880
//   提示条目清空（{int@0, 三指针容器@+8}）：清零并释放旧缓冲。
// ------------------------------------------------------------
void /*thiscall*/ sub_4F3880(void *this)  // 函数: 释放后返回
{
  *((uint32_t *)this + 2) = 0;  // this+8 = 0
  *((uint32_t *)this + 3) = 0;  // this+12 = 0
  *((uint32_t *)this + 4) = 0;  // this+16 = 0
  *(uint32_t *)this = 0;
  if ( *((uint32_t *)this + 2) != 0 )  // 若 *((uint32_t *)this + 2) != 0
    j__free(*((void **)this + 2));  // 调 j__free
  *((uint32_t *)this + 2) = 0;  // this+8 = 0
  *((uint32_t *)this + 3) = 0;  // this+12 = 0
  *((uint32_t *)this + 4) = 0;  // this+16 = 0
}



// ------------------------------------------------------------
// 0x4F38C0 sub_4F38C0
//   物品渲染状态对象构造：eh vector constructor 迭代构造三组内嵌数组
//   （+0:0x10×5、+80:0x14×4、+272:0x14×4）后转 sub_4F3560 清状态。
// ------------------------------------------------------------
char */*thiscall*/ sub_4F38C0(char *this)
{
  `eh vector constructor iterator'(this, 0x10u, 5, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  `eh vector constructor iterator'(this + 80, 0x14u, 4, sub_4F3880, sub_42D400);
  *((uint32_t *)this + 42) = 0;  // this+168 = 0
  *((uint32_t *)this + 43) = 0;  // this+172 = 0
  *((uint32_t *)this + 44) = 0;  // this+176 = 0
  `eh vector constructor iterator'(this + 272, 0x14u, 4, sub_4F38B0, sub_42D400);
  sub_4F3560((int)this);  // 调 sub_4F3560
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F3960 sub_4F3960
//   物品表现资源全局初始化：加载掉落图标/阴影/精炼特效等精灵槽
//   （dword_9B0C48..9B0C60，Item/AttachIcon.img），新建精炼特效精灵
//   dword_9B0C64 并绑倒计时时钟（sub_699070/sub_698F90），最后解析
//   Etc/Disjoint.etc（精炼炉 cube 脚本，sub_6014F0）取 dword_791ED8。
// ------------------------------------------------------------
void sub_4F3960()
{
  int v0; // eax
  int v1[88]; // [esp+4h] [ebp-170h] BYREF
  void *Block; // [esp+164h] [ebp-10h]
  int v3; // [esp+170h] [ebp-4h]

  dword_9B0C48 = sub_418DD0(119);  // 调 sub_418DD0
  dword_9B0C4C = sub_418DD0(118);  // 调 sub_418DD0
  (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Item/AttachIcon.img");  // 字符串 “Item/AttachIcon.img”
  dword_9B0C50 = sub_418DD0(0);  // 调 sub_418DD0
  dword_9B0C54 = sub_418DD0(1);  // 调 sub_418DD0
  dword_9B0C58 = sub_418DD0(2);  // 调 sub_418DD0
  dword_9B0C5C = sub_418DD0(4);  // 调 sub_418DD0
  dword_9B0C60 = sub_418DD0(6);  // 调 sub_418DD0
  Block = operator new(0x2Cu);  // 堆分配 44 字节对象
  v3 = 0;
  if ( Block != nullptr )  // 若 Block 非空
    v0 = sub_423B30(dword_79C0B0, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 13, 12);  // 结果 = CNNumberSet 构造
  else
    v0 = 0;
  dword_9B0C64 = v0;
  v3 = -1;
  *(uint32_t *)(v0 + 36) = 2;  // v0+36 = 2
  sub_699070((int)&unk_9B0C70, 1u);  // 【clock_bind_domain(clk, newDomainId)】
  byte_9B0C7D = 0;
  byte_9B0C7E = 0;
  sub_698F90((int)&unk_9B0C70, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  dword_9B0C68 = sub_418DD0(84);  // 调 sub_418DD0
  dword_9B0C6C = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 124);
  sub_4F38C0((char *)v1);  // 调 sub_4F38C0
  v3 = 1;
  sub_6014F0((int)v1, (char)"Etc/Disjoint.etc");  // 【精炼炉 cube 脚本解析器（[cube index]/[legacy info]/…】
  dword_791ED8 = v1[40];
  v3 = -1;
  sub_4F3610((void **)v1);  // 调 sub_4F3610
}



// ------------------------------------------------------------
// 0x4F3B10 sub_4F3B10
//   安全 _vsnprintf 封装（HRESULT 风格返回）：0 成功；-2147024809 = 参数无效；
//   -2147024774 = 缓冲区不足（截断并补 NUL）。
// ------------------------------------------------------------
int /*stdcall*/ sub_4F3B10(char *Buffer, int nArg2, char *Format, va_list ArgList)
{
  int result; // eax
  unsigned int v5; // esi
  int v6; // eax
  bool v7; // zf

  if ( nArg2 == 0 )  // 若 nArg2 == 0
    return -2147024809;  // 返回 -2147024809（0x80070057）
  v5 = nArg2 - 1;
  v6 = _vsnprintf(Buffer, nArg2 - 1, Format, ArgList);
  if ( v6 < 0 || (v7 = v6 == v5, v6 > v5) )  // 若 v6 < 0 || (v7 = v6 == v5, v6 > v5)
  {
    Buffer[v5] = 0;
    return -2147024774;  // 返回 -2147024774（0x8007007A）
  }
  else
  {
    result = 0;
    if ( v7 )  // 若 v7
      Buffer[v5] = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F3B70 sub_4F3B70
//   snprintf 封装：va_list 收拢后转调 sub_4F3B10（长度超 0x7FFFFFFF 视为参数无效）。
// ------------------------------------------------------------
int sub_4F3B70(char *Buffer, unsigned int uArg2, char *Format, ...)
{
  va_list va; // [esp+14h] [ebp+14h] BYREF

  va_start(va, Format);
  if ( uArg2 <= 0x7FFFFFFF )  // 若 uArg2 <= 0x7FFFFFFF
    return sub_4F3B10(Buffer, uArg2, Format, va);  // 调 sub_4F3B10
  else
    return -2147024809;  // 返回 -2147024809（0x80070057）
}



// ------------------------------------------------------------
// 0x4F3BA0 sub_4F3BA0
//   物品提示条目构建：this→vt+8 按 pszArg3 取模板条目，在 32 字节步进的
//   名称表中前缀匹配（sub_40BF00），sprintf(格式串, nArg4, nArg5) 生成文本，
//   经 dword_8F84BC 取图（4BC700/418DD0）写入 88 字节步进的提示条目
//   {图, 颜色, 文本}；返回文本缓冲指针。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F3BA0(void *this, int nArg2, char pszArg3, int nArg4, int nArg5)  // 函数: 释放后返回
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
  int dword_796E502; // [esp+124h] [ebp-10h]
  int v21; // [esp+130h] [ebp-4h]
  int v22; // [esp+13Ch] [ebp+8h]
  int v23; // [esp+13Ch] [ebp+8h]
  int i; // [esp+140h] [ebp+Ch]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = (*(int (/*thiscall*/ **)(void *, bool, int))(*(uint32_t *)this + 8))(this, pszArg3 != 0, nArg2);  // 调用虚函数槽 +8
  v6 = (uint32_t *)result;
  if ( result != 0 )  // 若 result != 0
  {
    if ( pszArg3 != 0 )  // 若 pszArg3 != 0
    {
      v7 = *(uint32_t *)(result + 8);  // v7 = result+8
      v8 = v7 != 0 ? (*(uint32_t *)(result + 12) - v7) >> 5 : 0;
      if ( v8 > 0 )  // 若 v8 > 0
      {
        v9 = 0;
        v10 = 0;
        for ( i = v8; i != 0; --i )  // 循环：i = v8; i != 0; --i
        {
          if ( sub_40BF00((std::_String_base *)(v10 + v6[2]), 0, *(uint32_t *)(v10 + v6[2] + 20), szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            v11 = v6[2];
            if ( *(uint32_t *)(v10 + v11 + 24) < 0x10u )  // 若 *(uint32_t *)(v10 + v11 + 24) < 0x10u
              sprintf(Buffer, (const char *const)(v10 + v11 + 4), nArg4, nArg5);  // 调 sprintf 格式化
            else
              sprintf(Buffer, *(const char *const *)(v10 + v11 + 4), nArg4, nArg5);  // 调 sprintf 格式化
            v19 = 15;
            v18 = 0;
            LOBYTE(Block) = 0;
            sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
            v12 = *(uint32_t *)(*v6 + 44);
            v21 = 0;
            v22 = v12;
            v13 = sub_4BC700((uint32_t *)dword_8F84BC, (int)v16);  // 调 部件路径 → 资源 id
            *(uint32_t *)(v9 + v22 + 4) = v13;
            *(uint32_t *)(v9 + *(uint32_t *)(*v6 + 44) + 8) = *(uint32_t *)(v10 + v6[2] + 28);
            v23 = *(uint32_t *)(*v6 + 44);
            v14 = *(uint32_t *)(v10 + v6[2] + 28);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v13);  // 调用虚函数槽 +56
            *(uint32_t *)(v9 + v23) = sub_418DD0(v14);
            v21 = -1;
            if ( v19 >= 0x10 )  // 若 v19 >= 0x10
              j__free(Block);  // 调 j__free
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
//   提示文本封装：snprintf("%s%s", ArgList, pArg3) 拼全名后转调 sub_4F3BA0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F3D60(void *this, const char *ArgList, const char *pArg3, char pszArg4, int nArg5, int nArg6)
{
  char Buffer[512]; // [esp+4h] [ebp-204h] BYREF
  int dword_796E502; // [esp+204h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  sub_4F3B70(Buffer, 0x200u, "%s%s", ArgList, pArg3);  // 字符串 “%s%s”
  return sub_4F3BA0(this, (int)Buffer, pszArg4, nArg5, nArg6);  // 调 sub_4F3BA0
}



// ------------------------------------------------------------
// 0x4F3DD0 sub_4F3DD0
//   CNTimer 派生的物品动画加载器构造：复位基类字段后初始化内部对象
//   （430B70/4A2CF0/493BD0），最后 sub_494E40 启动动画加载（ArgList = 资源名）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F3DD0(int this, const char *ArgList, int nArg3, int nArg4)
{
  uint32_t *pThis_3C; // ecx

  *(uint8_t *)(this + 4) = 0;  // this+4 = 0
  *(uint32_t *)this = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 8) = 0;  // this+8 = 0
  *(uint8_t *)(this + 12) = 1;  // this+12 = 1
  *(uint8_t *)(this + 14) = 0;  // this+14 = 0
  *(uint8_t *)(this + 13) = 0;  // this+13 = 0
  *(uint32_t *)(this + 24) = 0;  // this+24 = 0
  *(uint32_t *)(this + 20) = 0;  // this+20 = 0
  *(uint32_t *)(this + 16) = 0;  // this+16 = 0
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  *(uint32_t *)(this + 52) = 0;  // this+52 = 0
  pThis_3C = (uint32_t *)(this + 60);
  pThis_3C[15] = 0;
  pThis_3C[16] = 0;
  pThis_3C[17] = 0;
  pThis_3C[19] = 0;
  pThis_3C[20] = 0;
  pThis_3C[21] = 0;
  sub_430B70(pThis_3C);  // 88B 帧条目复位
  *(uint32_t *)(this + 204) = sub_4A2CF0(this + 200);  // this+204 = sub_4A2CF0(this + 200)
  *(uint32_t *)(this + 208) = 0;  // this+208 = 0
  sub_493BD0(this);  // 动画对象复位
  sub_494E40((uint8_t *)this, szPassword, ArgList, 0, nArg3, nArg4, 0, 0);  // 动画创建入口
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F3E90 CNAnimationLoader__vmt30 —— 动画加载器工厂（0x14 包装 + 228 字节本体）
//   分配 0x14 包装块，sub_42FCB0(228) 实配后以 sub_4F3DD0 构造 CNTimer 派生加载器并挂 +4；
//   资源名 ArgList 与标志 nArg2 透传。
// ------------------------------------------------------------
int */*stdcall*/ CNAnimationLoader__vmt30(const char *ArgList, int nArg2)
{
  int *pMem; // eax
  int *pMem2; // esi
  int v4; // eax
  int nArg22; // edx
  int v6; // eax

  pMem = (int *)operator new(0x14u);  // 堆分配 20 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
  {
    *pMem = 0;  // *pMem 写入 0
    pMem[2] = 0;
    pMem[3] = 0;
    pMem[4] = 0;
    pMem2 = pMem;
  }
  else
  {
    pMem2 = nullptr;  // pMem2 = nullptr 空指针
  }
  v4 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v4 != 0 )  // 若 v4 != 0
  {
    nArg22 = nArg2;
    LOBYTE(nArg22) = nArg2 != 0;
    v6 = sub_4F3DD0(v4, ArgList, nArg22, (int)(pMem2 + 1));  // 调 sub_4F3DD0
  }
  else
  {
    v6 = 0;
  }
  *pMem2 = v6;  // *pMem2 写入 v6
  return pMem2;
}



// ------------------------------------------------------------
// 0x4F3F30 CNAnimationLoader__vmt34 —— 加载器销毁（帧析构 + 释放本体 + 清壳）
//   sub_42AF90 析构帧对象、sub_657740(228) 释放本体，sub_4F3DC0 复位包装块后 free。
// ------------------------------------------------------------
void /*stdcall*/ CNAnimationLoader__vmt34(void ***Block)  // 函数: 加载器销毁（帧析构 + 释放本体 + 清壳）
{
  void **v1; // edi

  v1 = *Block;
  if ( *Block != nullptr )  // 若 *Block != nullptr
  {
    sub_42AF90(*Block);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(v1, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  *Block = nullptr;  // *Block 写入 nullptr
  sub_4F3DC0(Block);  // 调 sub_4F3DC0
  j__free(Block);  // 调 j__free
}



// ------------------------------------------------------------
// 0x4F3F80 HttpFileJob__vmt18 —— 作业超时/取消判定（E_ABORT = -2147467260）
//   状态块 pArg1[1]+4 为 1 或已过截止时间 pArg1[10] → 调 vt+8 通知取消返回 -2147467260；
//   否则 vt+12 报告进度返回 0。
// ------------------------------------------------------------
int /*stdcall*/ HttpFileJob__vmt18(uint32_t *pArg1, int nArg2, int nArg3, int nArg4, int nArg5)  // 函数: 作业超时/取消判定（E_ABORT = -2147467260）
{
  int pObj; // eax
  bool dwNow; // cc
  int pObj2; // eax

  if ( *(uint32_t *)(pArg1[1] + 4) == 1 )  // 若 *(uint32_t *)(pArg1[1] + 4) == 1
  {
    pObj = pArg1[2];
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (**)(void))(*(uint32_t *)pObj + 8))();  // 调用虚函数槽 +8
    return -2147467260;  // 返回 -2147467260（0x80004004）
  }
  else
  {
    dwNow = timeGetTime() <= pArg1[10];
    pObj2 = pArg1[2];
    if ( dwNow )  // 若 dwNow
    {
      if ( pObj2 != 0 )  // 若 pObj2 != 0
        (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[2] + 12))(pArg1[2], nArg2, nArg3);  // 调用虚函数槽 +12
      return 0;
    }
    else
    {
      if ( pObj2 != 0 )  // 若 pObj2 != 0
        (*(void (**)(void))(*(uint32_t *)pObj2 + 8))();  // 调用虚函数槽 +8
      return -2147467260;  // 返回 -2147467260（0x80004004）
    }
  }
}



// ------------------------------------------------------------
// 0x4F3FF0 sub_4F3FF0
//   HttpFileJob 析构体：重置虚表后释放 +4 字符串（容量 ≥0x10 时 free 堆缓冲）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F3FF0(void **this)  // 函数: 释放后返回
{
  *this = &vftbl_HttpFileJob;  // *this 写入 &vftbl_HttpFileJob
  if ( (unsigned int)*(this + 9) >= 0x10 )  // 若 (unsigned int)*(this + 9) >= 0x10
    j__free(*(this + 4));  // 调 j__free
  *(this + 9) = (void *)15;  // this+36 = (void *)15
  *(this + 8) = nullptr;  // this+32 = nullptr
  *((uint8_t *)this + 16) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4F4030 sub_4F4030
//   HttpFileJob 管理器状态重置：+0/+4/+8 清零、+132 计数清零、等待计数
//   归零循环、+104 起容器释放（重入等待 while(1) 为原样保留的死循环结构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F4030(char *this)  // 函数: 释放后返回
{
  uint32_t *pThis_84; // ecx
  int pThis_18; // eax
  int v4; // eax

  pThis_84 = this + 132;
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = 0;  // this+4 = 0
  *((uint32_t *)this + 2) = 0;  // this+8 = 0
  *pThis_84 = 0;  // *pThis_84 写入 0
  pThis_84[1] = 0;
  if ( *((uint32_t *)this + 19) != 0 )  // 若 *((uint32_t *)this + 19) != 0
  {
    while ( 1 )  // 当 1 循环
      ;
  }
  while ( *((uint32_t *)this + 24) != 0 )  // 当 *((uint32_t *)this + 24) != 0 循环
  {
    pThis_18 = *((uint32_t *)this + 24);
    if ( pThis_18 != 0 )  // 若 pThis_18 != 0
    {
      v4 = pThis_18 - 1;
      *((uint32_t *)this + 24) = v4;  // this+96 = v4
      if ( v4 == 0 )  // 若 v4 == 0
        *((uint32_t *)this + 23) = 0;  // this+92 = 0
    }
  }
  if ( *((uint32_t *)this + 26) != 0 )  // 若 *((uint32_t *)this + 26) != 0
    j__free(*((void **)this + 26));  // 调 j__free
  *((uint32_t *)this + 26) = 0;  // this+104 = 0
  *((uint32_t *)this + 27) = 0;  // this+108 = 0
  *((uint32_t *)this + 28) = 0;  // this+112 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x4F40A0 sub_4F40A0
//   异步加载器销毁：TerminateThread/CloseHandle 全部工作线程（+120..+124），
//   清作业队列（+104..+108，作业经 4F3FF0+free），DeleteCriticalSection×2
//   （+12/+36），最后 sub_4F4030 复位。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F40A0(int this)  // 函数: 释放后返回
{
  HANDLE *fld_7C; // eax
  HANDLE *fld_78; // esi
  void ***i; // esi
  void **v6; // ebx

  if ( *(uint32_t *)this == 0 )  // 若 *(uint32_t *)this == 0
    return 1;
  fld_7C = *(HANDLE **)(this + 124);
  fld_78 = *(HANDLE **)(this + 120);
  *(uint32_t *)(this + 4) = 1;  // this+4 = 1
  if ( fld_78 != fld_7C )  // 若 fld_78 != fld_7C
  {
    do
    {
      TerminateThread(*fld_78, 0);
      CloseHandle(*fld_78++);  // 调 CloseHandle 关闭句柄
    }
    while ( fld_78 != *(HANDLE **)(this + 124) );  // 当 fld_78 != *(HANDLE **)(this + 124) 循环
  }
  for ( i = *(void ****)(this + 104); i != *(void ****)(this + 108); ++i )  // 循环：i = *(void ****)(this + 104); i != *(void ****)(this + 108);
  {
    v6 = *i;
    if ( *i != nullptr )  // 若 *i != nullptr
    {
      sub_4F3FF0(*i);  // 调 sub_4F3FF0
      j__free(v6);  // 调 j__free
    }
  }
  DeleteCriticalSection((LPCRITICAL_SECTION)(this + 12));  // 调 DeleteCriticalSection 删除临界区
  DeleteCriticalSection((LPCRITICAL_SECTION)(this + 36));  // 调 DeleteCriticalSection 删除临界区
  sub_4F4030((char *)this);  // 调 sub_4F4030
  *(uint32_t *)this = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4F41A0 sub_4F41A0
//   "deque<T> too long" 异常抛出（length_error），永不返回。
// ------------------------------------------------------------
void /*noreturn*/ sub_4F41A0()  // 函数: 条件抛异常
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0("deque<T> too long", 0x11u);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4F4210 sub_4F4210
//   HttpFileJob 构造：+1 = 作业类型 nArg2，+4 字符串空串初始化（SSO 容量 15）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F4210(uint32_t *this, int nArg2)
{
  uint32_t *pThis_3; // ecx

  pThis_3 = this + 3;
  *this = &vftbl_HttpFileJob;  // *this 写入 &vftbl_HttpFileJob
  pThis_3[6] = 15;
  pThis_3[5] = 0;
  *((uint8_t *)pThis_3 + 4) = 0;
  *(this + 1) = nArg2;  // this+4 = nArg2
  *(this + 2) = 0;  // this+8 = 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 10) = 0;  // this+40 = 0
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F4280 sub_4F4280 —— deque<uint32> 扩容搬移（块 16 字节双端队列）
//   新容量取 fld_8>>1 与 8 较大者（0xFFFFFFF 上限校验），memcpy 三段落搬移后返回新长度；
//   由 ·0x4F4440 满块时调用。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4F4280(int this, unsigned int uArg2)  // 函数: deque<uint32> 扩容搬移（块 16 字节双端队列）
{
  unsigned int uArg22; // edx
  unsigned int fld_8; // eax
  unsigned int v5; // ecx
  unsigned int fld_C; // edi
  int v7; // esi
  char *fld_4; // eax
  const void *fld_42; // ecx
  char *v10; // eax
  char *pBuf3; // edx
  unsigned int pBuf; // ecx
  char *pBuf2; // edi
  size_t v14; // esi
  char *fld_43; // eax
  unsigned int result; // eax
  size_t fld_82; // [esp+8h] [ebp-Ch]
  char *pMem; // [esp+10h] [ebp-4h]

  uArg22 = uArg2;
  fld_8 = *(uint32_t *)(this + 8);  // fld_8 = this+8
  if ( 0xFFFFFFF - fld_8 < uArg2 )  // 若 0xFFFFFFF - fld_8 < uArg2
    sub_4F41A0(this);  // 调 sub_4F41A0
  v5 = fld_8 >> 1;
  if ( fld_8 >> 1 < 8 )  // 若 fld_8 >> 1 < 8
    v5 = 8;
  if ( uArg2 < v5 && fld_8 <= 0xFFFFFFF - v5 )  // 若 uArg2 < v5 && fld_8 <= 0xFFFFFFF - v5
  {
    uArg2 = v5;
    uArg22 = v5;
  }
  fld_C = *(uint32_t *)(this + 12) >> 2;
  v7 = 4 * fld_C;
  pMem = (char *)operator new(4 * (uArg22 + fld_8));
  fld_82 = 4 * ((int)(4 * *(uint32_t *)(this + 8) - 4 * fld_C) >> 2);
  fld_4 = (char *)memcpy_0(&pMem[4 * fld_C], (const void *)(4 * fld_C + *(uint32_t *)(this + 4)), fld_82);
  fld_42 = *(const void **)(this + 4);
  v10 = &fld_4[fld_82];
  if ( fld_C > uArg2 )  // 若 fld_C > uArg2
  {
    memcpy_0(v10, fld_42, 4 * ((int)(4 * uArg2) >> 2));
    v14 = 4 * ((int)(v7 - 4 * uArg2) >> 2);
    fld_43 = (char *)memcpy_0(pMem, (const void *)(4 * uArg2 + *(uint32_t *)(this + 4)), v14);
    pBuf = uArg2;
    pBuf2 = &fld_43[v14];
    if ( uArg2 == 0 )  // 若 uArg2 == 0
      goto LABEL_15;  // 跳转 LABEL_15
    goto LABEL_14;  // 跳转 LABEL_14
  }
  pBuf3 = (char *)memcpy_0(v10, fld_42, 4 * (v7 >> 2)) + 4 * (v7 >> 2);
  if ( uArg2 != fld_C )  // 若 uArg2 != fld_C
    memset(pBuf3, 0, 4 * (uArg2 - fld_C));  // 调 memset 按字节填充
  if ( fld_C != 0 )  // 若 fld_C != 0
  {
    pBuf = fld_C;
    pBuf2 = pMem;
LABEL_14:
    memset(pBuf2, 0, 4 * pBuf);  // 清零 字节块
  }
LABEL_15:
  if ( *(uint32_t *)(this + 4) != 0 )  // 若 *(uint32_t *)(this + 4) != 0
    j__free(*(void **)(this + 4));  // 调 j__free
  result = uArg2 + *(uint32_t *)(this + 8);
  *(uint32_t *)(this + 4) = pMem;  // this+4 = pMem
  *(uint32_t *)(this + 8) = result;  // this+8 = result
  return result;
}



// ============================================================
// §E 0x4F43D0-0x4F5B90 物品容器模板族（vector/list/deque 辅助 —— "vector<T> too long"/"deque<T> too long" 系 CRT 实例）
// ============================================================

// ------------------------------------------------------------
// 0x4F43D0 sub_4F43D0 —— vector 超长异常抛出（length_error，不返回）
//   vector<T> too long 文案经 sub_4015C0/sub_401740 构造后抛出；供 §E 容器模板族消费。
// ------------------------------------------------------------
void /*noreturn*/ sub_4F43D0()  // vector 超长异常抛出（length_error，不返回）
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4F4440 sub_4F4440 —— deque<uint32> 尾部压入（16 字节块惰性分配）
//   满块先 ·0x4F4280 扩一；按块号定位 16 字节块（空则 operator new(0x10)），写元素后 +16
//   计数递增。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F4440(int this, uint32_t *uArg2)  // 函数: deque<uint32> 尾部压入（16 字节块惰性分配）
{
  int fld_10; // eax
  unsigned int fld_8; // eax
  unsigned int fld_102; // edi
  unsigned int v6; // ebx
  uint32_t *fld_4; // edi
  int result; // eax

  fld_10 = *(uint32_t *)(this + 16);  // fld_10 = this+16
  if ( (((uint8_t)fld_10 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(fld_10 + 4) >> 2 )  // 若 (((uint8_t)fld_10 + *(uint8_t *)(this + 12)) & 3) == 0 && *(ui..
    sub_4F4280(this, 1u);  // deque<uint32> 扩容搬移（块 16 字节双端队列）
  fld_8 = *(uint32_t *)(this + 8);  // fld_8 = this+8
  fld_102 = *(uint32_t *)(this + 16) + *(uint32_t *)(this + 12);
  v6 = fld_102 >> 2;
  if ( fld_8 <= fld_102 >> 2 )  // 若 fld_8 <= fld_102 >> 2
    v6 -= fld_8;  // v6 累减 fld_8
  if ( *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0 )  // 若 *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0
    *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) = operator new(0x10u);  // 堆分配 16 字节对象
  fld_4 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) + 4 * (fld_102 & 3));
  if ( fld_4 != nullptr )  // 若 fld_4 非空
    *fld_4 = *uArg2;  // *fld_4 写入 *uArg2
  result = *(uint32_t *)(this + 16) + 1;
  *(uint32_t *)(this + 16) = result;  // this+16 = result
  return result;
}



// ------------------------------------------------------------
// 0x4F44C0 sub_4F44C0 —— vector<uint32> 批量插入（0x3FFFFFFF 上限）
//   尾部富余就地 sub_5DAF70/sub_49A9D0，间隙足经 sub_55E7F0/sub_523700 前缀填充，否则 1.5 倍
//   扩容重建（operator new + 三段 memcpy）；超限转 ·0x4F43D0。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4F44C0(int this, int Src, unsigned int uArg3, int *pDwArg4)  // 函数: vector<uint32> 批量插入（0x3FFFFFFF 上限）
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

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    result = 0;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )  // 若 0x3FFFFFFF - fld_8 < uArg3
      sub_4F43D0(this);  // vector 超长异常抛出（length_error，不返回）
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )  // 若 result >= uArg3 + fld_82
    {
      fld_83 = *(uint8_t **)(this + 8);
      v21 = (int)&fld_83[-Src] >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )  // 若 v21 >= uArg3
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // 商城状态
        sub_5DAF70((void *)Src, v24, v29);  // 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // 商城状态
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // 调 sub_523700
        fld_84 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = fld_84;  // this+8 = fld_84
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )  // 若 0x3FFFFFFF - (result >> 1) >= result
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 != 0
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )  // 若 v10 < uArg3 + fld_85
      {
        if ( fld_4 != 0 )  // 若 fld_4 != 0
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
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = this+4
      if ( fld_43 != 0 )  // 若 fld_43 != 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;
      else
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )  // 若 fld_43 != 0
        j__free(*(void **)(this + 4));  // 调 j__free
      *(uint32_t *)(this + 12) = &pMem[v28];  // this+12 = &pMem[v28]
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // this+8 = &pMem[4 * v18]
      *(uint32_t *)(this + 4) = pMem;  // this+4 = pMem
      return (unsigned int)pMem;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4F46A0 sub_4F46A0 —— HTTP 加载管理器清理（清零登记段 + 4F4030 复位）
//   清零 +64..+128 登记字段后 sub_4F4030 复位作业队列（与 ·0x4F40A0 销毁配对）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F46A0(int this)  // 函数: HTTP 加载管理器清理（清零登记段 + 4F4030 复位）
{
  *(uint32_t *)(this + 64) = 0;  // this+64 = 0
  *(uint32_t *)(this + 68) = 0;  // this+68 = 0
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint32_t *)(this + 76) = 0;  // this+76 = 0
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 96) = 0;  // this+96 = 0
  *(uint32_t *)(this + 104) = 0;  // this+104 = 0
  *(uint32_t *)(this + 108) = 0;  // this+108 = 0
  *(uint32_t *)(this + 112) = 0;  // this+112 = 0
  *(uint32_t *)(this + 120) = 0;  // this+120 = 0
  *(uint32_t *)(this + 124) = 0;  // this+124 = 0
  *(uint32_t *)(this + 128) = 0;  // this+128 = 0
  sub_4F4030((char *)this);  // 调 sub_4F4030
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F4710 sub_4F4710 —— HTTP 完成结果回填（弹出作业 → 写结果 → 入完成队列）
//   临界区 this+36 弹出 this+84 环形队列首作业，写作业 +8/+40 与路径串（sub_4015C0），再临界区
//   this+12 经 sub_4F4440 压入 this+60 完成队列；队空/未就绪返回 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F4710(char *this, void *Src, int nArg3, int nArg4)  // 函数: HTTP 完成结果回填（弹出作业 → 写结果 → 入完成队列）
{
  unsigned int pThis_17; // edx
  unsigned int v7; // eax
  unsigned int v8; // edx
  unsigned int pThis_16; // edi
  int pThis_15; // esi
  int pThis_18; // eax
  int v12; // eax
  int pThis_22; // eax
  int pThis_152; // [esp+4h] [ebp-4h] BYREF

  if ( *(uint32_t *)this == 0 )  // 若 *(uint32_t *)this == 0
    return 1;
  EnterCriticalSection((LPCRITICAL_SECTION)(this + 36));  // 调 EnterCriticalSection 进临界区
  if ( *((uint32_t *)this + 24) != 0 )  // 若 *((uint32_t *)this + 24) != 0
  {
    pThis_17 = *((uint32_t *)this + 23) + *((uint32_t *)this + 24) - 1;
    v7 = pThis_17 >> 2;
    v8 = pThis_17 - 4 * (pThis_17 >> 2);
    pThis_16 = *((uint32_t *)this + 22);
    if ( pThis_16 <= v7 )  // 若 pThis_16 <= v7
      v7 -= pThis_16;  // v7 累减 pThis_16
    pThis_15 = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)this + 21) + 4 * v7) + 4 * v8);
    pThis_18 = *((uint32_t *)this + 24);
    pThis_152 = pThis_15;
    if ( pThis_18 != 0 )  // 若 pThis_18 != 0
    {
      v12 = pThis_18 - 1;
      *((uint32_t *)this + 24) = v12;  // this+96 = v12
      if ( v12 == 0 )  // 若 v12 == 0
        *((uint32_t *)this + 23) = 0;  // this+92 = 0
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 36));  // 调 LeaveCriticalSection 出临界区
    sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
    pThis_22 = nArg4;
    *(uint32_t *)(pThis_15 + 8) = nArg3;  // pThis_15+8 = nArg3
    if ( nArg4 == 0 )  // 若 nArg4 == 0
      pThis_22 = *((uint32_t *)this + 34);
    *(uint32_t *)(pThis_15 + 40) = pThis_22;  // pThis_15+40 = pThis_22
    EnterCriticalSection((LPCRITICAL_SECTION)(this + 12));  // 调 EnterCriticalSection 进临界区
    sub_4F4440((int)(this + 60), &pThis_152);  // deque<uint32> 尾部压入（16 字节块惰性分配）
    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 12));  // 调 LeaveCriticalSection 出临界区
    return 0;
  }
  else
  {
    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 36));  // 调 LeaveCriticalSection 出临界区
    return 1;
  }
}



// ------------------------------------------------------------
// 0x4F4800 sub_4F4800 —— HTTP 下载工作线程（URLDownloadToCacheFileA 循环）
//   循环取 this+16 队列作业，以作业内嵌串（+16，SSO）经 URLDownloadToCacheFileA 下载到 260 字节
//   缓存路径；失败回调作业 vt+2、成功回调 vt+1(路径)，结果经 sub_4F4440 入 this+80 队列；空转 Sleep(500)。
// ------------------------------------------------------------
DWORD /*stdcall*/ sub_4F4800(char *lpThreadParameter)  // 函数: HTTP 下载工作线程（URLDownloadToCacheFileA 循环）
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
  CHAR psz[260]; // [esp+10h] [ebp-108h] BYREF
  int dword_796E502; // [esp+114h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = *((uint32_t *)lpThreadParameter + 1);
  v2 = nullptr;  // v2 = nullptr 空指针
  for ( i = nullptr; result != 1; i = nullptr )  // 循环：i = nullptr; result != 1; i = nullptr
  {
    EnterCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 12));  // 调 EnterCriticalSection 进临界区
    if ( *((uint32_t *)lpThreadParameter + 19) != 0 )  // 若 *((uint32_t *)lpThreadParameter + 19) != 0
    {
      v3 = *((uint32_t *)lpThreadParameter + 18) >> 2;
      v4 = *((uint32_t *)lpThreadParameter + 18) - 4 * v3;
      v5 = *((uint32_t *)lpThreadParameter + 17);
      if ( v5 <= v3 )  // 若 v5 <= v3
        v3 -= v5;  // v3 累减 v5
      v2 = *(IBindStatusCallback **)(*(uint32_t *)(*((uint32_t *)lpThreadParameter + 16) + 4 * v3) + 4 * v4);
      v6 = *((uint32_t *)lpThreadParameter + 19);
      i = v2;
      if ( v6 != 0 )  // 若 v6 != 0
      {
        v7 = *((uint32_t *)lpThreadParameter + 18) + 1;
        v8 = 4 * *((uint32_t *)lpThreadParameter + 17);
        *((uint32_t *)lpThreadParameter + 18) = v7;
        if ( v8 <= v7 )  // 若 v8 <= v7
          *((uint32_t *)lpThreadParameter + 18) = 0;
        v9 = v6 - 1;
        *((uint32_t *)lpThreadParameter + 19) = v9;
        if ( v9 == 0 )  // 若 v9 == 0
          *((uint32_t *)lpThreadParameter + 18) = 0;
      }
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 12));  // 调 LeaveCriticalSection 出临界区
    if ( v2 != nullptr )  // 若 v2 非空
    {
      lpVtbl = v2[2].lpVtbl;
      if ( lpVtbl != nullptr )  // 若 lpVtbl 非空
        (*(void (/*thiscall*/ **)(struct IBindStatusCallbackVtbl *))lpVtbl->QueryInterface)(lpVtbl);
      v2[10].lpVtbl = (struct IBindStatusCallbackVtbl *)((char *)v2[10].lpVtbl + timeGetTime());
      psz[0] = 0;
      if ( v2[9].lpVtbl < (struct IBindStatusCallbackVtbl *)0x10 )  // 若 v2[9].lpVtbl < (struct IBindStatusCallbackVtbl *)0x10
        v11 = (const CHAR *)&v2[4];
      else
        v11 = (const CHAR *)v2[4].lpVtbl;
      if ( URLDownloadToCacheFileA(nullptr, v11, psz, 0x104u, 0, v2) != 0 || strlen(psz) == 0 )  // 若 URLDownloadToCacheFileA(nullptr, v11, psz, 0x104u, 0, v2) != 0..
      {
        v13 = v2[2].lpVtbl;
        if ( v13 != nullptr )  // 若 v13 非空
          (*((void (**)(void))v13->QueryInterface + 2))();  // 调用虚函数槽 +2
      }
      else
      {
        v12 = v2[2].lpVtbl;
        if ( v12 != nullptr )  // 若 v12 非空
          (*((void (/*stdcall*/ **)(CHAR *))v12->QueryInterface + 1))(psz);  // 调用虚函数槽 +1
      }
      EnterCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 36));  // 调 EnterCriticalSection 进临界区
      sub_4F4440((int)(lpThreadParameter + 80), &i);  // deque<uint32> 尾部压入（16 字节块惰性分配）
      LeaveCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 36));  // 调 LeaveCriticalSection 出临界区
    }
    else
    {
      Sleep(0x1F4u);  // 调 Sleep 睡眠
    }
    result = *((uint32_t *)lpThreadParameter + 1);
    v2 = nullptr;  // v2 = nullptr 空指针
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F4970 sub_4F4970 —— vector<uint32> 尾部压入（满则 4F44C0）
//   有余量直接写 *end 再 +4；否则 sub_4F44C0(this, end, 1, val) 扩容追加。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4F4970(int *this, int *pDwArg2)  // 函数: vector<uint32> 尾部压入（满则 4F44C0）
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( fld_e1 != 0 )  // 若 fld_e1 != 0
    fld_e2 = (*(this + 2) - fld_e1) >> 2;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 2 )  // 若 fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 2
    return sub_4F44C0((int)this, *(this + 2), 1u, pDwArg2);  // vector<uint32> 批量插入（0x3FFFFFFF 上限）
  fld_e22 = (int *)*(this + 2);
  *fld_e22 = *pDwArg2;  // *fld_e22 写入 *pDwArg2
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = result;  // this+8 = result
  return result;
}



// ------------------------------------------------------------
// 0x4F49C0 sub_4F49C0 —— HTTP 加载管理器启动（临界区 + 作业槽 + 工作线程）
//   Block = {u16 作业槽数, u16 线程数, u32 超时(0→15000ms)}：双临界区初始化后按槽数 sub_4F4210
//   建作业并入队，CreateThread(sub_4F4800)×线程数 句柄存 this+120 向量，末置 this[0]=1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F49C0(char *lpParameter, uint16_t *Block)  // 函数: HTTP 加载管理器启动（临界区 + 作业槽 + 工作线程）
{
  uint16_t *Block2; // eax
  int v4; // eax
  int v5; // edi
  uint16_t *pMem; // eax
  uint32_t *v7; // eax
  bool v8; // zf
  HANDLE hThread; // ebx
  int v10; // eax
  unsigned int v11; // edi
  uint32_t *hThread2; // eax
  int v13; // ecx
  DWORD ThreadId; // [esp+4h] [ebp-14h] BYREF
  int v16; // [esp+8h] [ebp-10h] BYREF
  int v17; // [esp+14h] [ebp-4h]

  if ( *(uint32_t *)lpParameter == 1 )  // 若 *(uint32_t *)lpParameter == 1
    return 1;
  Block2 = Block;
  if ( *Block == 0 || Block[1] == 0 )  // 若 *Block == 0 || Block[1] == 0
    return 1;
  *((uint32_t *)lpParameter + 33) = *(uint32_t *)Block;
  v4 = *((uint32_t *)Block2 + 1);
  *((uint32_t *)lpParameter + 34) = v4;
  if ( v4 == 0 )  // 若 v4 == 0
    *((uint32_t *)lpParameter + 34) = 15000;
  InitializeCriticalSection((LPCRITICAL_SECTION)(lpParameter + 12));  // 调 InitializeCriticalSection 初始化临界区
  InitializeCriticalSection((LPCRITICAL_SECTION)(lpParameter + 36));  // 调 InitializeCriticalSection 初始化临界区
  v5 = 0;
  if ( *((uint16_t *)lpParameter + 66) != 0 )  // 若 *((uint16_t *)lpParameter + 66) != 0
  {
    do
    {
      pMem = operator new(0x2Cu);  // 堆分配 44 字节对象
      Block = pMem;
      v17 = 0;
      if ( pMem != nullptr )  // 若 pMem 非空
        v7 = sub_4F4210(pMem, (int)lpParameter);  // 调 sub_4F4210
      else
        v7 = nullptr;  // v7 = nullptr 空指针
      v17 = -1;
      Block = v7;
      sub_4F4970((int *)lpParameter + 25, (int *)&Block);  // vector<uint32> 尾部压入（满则 4F44C0）
      sub_4F4440((int)(lpParameter + 80), &Block);  // deque<uint32> 尾部压入（16 字节块惰性分配）
      ++v5;  // 自增v5
    }
    while ( v5 < *((uint16_t *)lpParameter + 66) );  // 当 v5 < *((uint16_t *)lpParameter + 66) 循环
  }
  v8 = *((uint16_t *)lpParameter + 67) == 0;
  Block = nullptr;  // Block = nullptr 空指针
  if ( v8 )  // 若 v8
  {
LABEL_21:
    *(uint32_t *)lpParameter = 1;
    return 0;
  }
  else
  {
    while ( 1 )  // 当 1 循环
    {
      hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)sub_4F4800, lpParameter, 0, &ThreadId);
      v16 = (int)hThread;
      if ( hThread == nullptr )  // 若 hThread 为空
        return 1;
      v10 = *((uint32_t *)lpParameter + 30);
      if ( v10 != 0 )  // 若 v10 != 0
        v11 = (*((uint32_t *)lpParameter + 31) - v10) >> 2;
      else
        v11 = 0;
      if ( v10 != 0 && v11 < (*((uint32_t *)lpParameter + 32) - v10) >> 2 )  // 若 v10 != 0 && v11 < (*((uint32_t *)lpParameter + 32) - v10) >> 2
      {
        hThread2 = *((uint32_t **)lpParameter + 31);
        *hThread2 = hThread;  // *hThread2 写入 hThread
        *((uint32_t *)lpParameter + 31) = hThread2 + 1;
      }
      else
      {
        sub_4F44C0((int)(lpParameter + 116), *((uint32_t *)lpParameter + 31), 1u, &v16);  // vector<uint32> 批量插入（0x3FFFFFFF 上限）
      }
      v13 = *((uint16_t *)lpParameter + 67);
      Block = (uint16_t *)((char *)Block + 1);
      if ( (int)Block >= v13 )  // 若 (int)Block >= v13
        goto LABEL_21;  // 跳转 LABEL_21
    }
  }
}



// ------------------------------------------------------------
// 0x4F4B60 sub_4F4B60 —— clong 双槽快速构造（类型字 4）
//   对 +4 与 +18 两处 clong 槽经 sub_41A630 挂 vftbl_clong、sub_41A590 清 0，this[0]=4。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F4B60(uint32_t *this)  // clong 双槽快速构造（类型字 4）
{
  uint32_t *pThis_1; // edi
  int v3; // edx
  int v4; // edx

  pThis_1 = this + 1;
  sub_41A630((unsigned int)(this + 1));  // 调 sub_41A630
  *pThis_1 = &vftbl_clong;  // *pThis_1 写入 &vftbl_clong
  sub_41A630((unsigned int)this + 18);  // 调 sub_41A630
  *(uint32_t *)((char *)this + 18) = &vftbl_clong;
  *this = 4;  // *this 写入 4
  sub_41A590((unsigned int)pThis_1, v3, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)this + 18, v4, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F4BE0 sub_4F4BE0 —— 全局整型表加载（3 首值 + 30×100 表段）【推断：物品系数表】
//   pArg1 作数据目录（byte_9B6A60，补 92 反斜杠结尾）；sub_443C40/sub_442A10 装表加载后，3 个
//   首值入 dword_9B6A50，表体按行读 100 整型写入 unk_9B0C90 区（0x2EE0 字节清底）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4F4BE0(const char *pArg1, int nArg2, int nArg3)  // 函数: 全局整型表加载（3 首值 + 30×100 表段）【推断：物品系数表】
{
  int *v4; // esi
  int *v5; // esi
  int i; // edi
  char v7[4]; // [esp+0h] [ebp-2Ch] BYREF
  void *Block; // [esp+4h] [ebp-28h]
  int v9; // [esp+14h] [ebp-18h]
  unsigned int v10; // [esp+18h] [ebp-14h]
  int dword_796E502; // [esp+1Ch] [ebp-10h]
  int v12; // [esp+28h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  strcpy(byte_9B6A60, pArg1);  // 调 strcpy 串拷贝
  if ( byte_9B6A5F[strlen(byte_9B6A60)] != 92 && byte_9B6A5F[strlen(byte_9B6A60)] != 47 )  // 若 byte_9B6A5F[strlen(byte_9B6A60)] != 92 && byte_9B6A5F[strlen(b..
    *(uint16_t *)&byte_9B6A60[strlen(byte_9B6A60)] = 92;
  if ( (uint8_t)sub_443C40((int)&unk_9B6C6C, (char)byte_9B6A60, nArg2) == 0  // 脚本文件列表装表
    || (uint8_t)sub_442A10((char)byte_9B6A60, nArg3) == 0 )  // 脚本载入调度（PVF 或磁盘）
  {
    return 0;
  }
  memset(&unk_9B0C90, 0, 0x2EE0u);  // 清零 12000 字节块
  v10 = 15;
  v9 = 0;
  LOBYTE(Block) = 0;
  v12 = 0;
  sub_443430(v7);  // 读 token 到 string + 国家码标记
  v4 = &dword_9B6A50;
  do
    *v4++ = sub_4423D0(nullptr);  // *v4++ 写入 sub_4423D0(nullptr)
  while ( (int)v4 < (int)&unk_9B6A5C );  // 当 (int)v4 < (int)&unk_9B6A5C 循环
  v5 = (int *)&unk_9B0C90;
  do
  {
    if ( (uint8_t)sub_443430(v7) == 0 )  // 读 token 到 string + 国家码标记
      break;
    for ( i = 100; i != 0; --i )  // 循环：i = 100; i != 0; --i
      *v5++ = sub_4423D0(nullptr);  // *v5++ 写入 sub_4423D0(nullptr)
  }
  while ( (int)v5 < (int)dword_9B3B70 );  // 当 (int)v5 < (int)dword_9B3B70 循环
  if ( v10 >= 0x10 )  // 若 v10 >= 0x10
    j__free(Block);  // 调 j__free
  return 1;
}



// ------------------------------------------------------------
// 0x4F4D50 sub_4F4D50 —— 全局整型表后半段加载
//   —— 与 ·0x4F4BE0 同构（差异：根目录 byte_9B6B60 / 表句柄 unk_9B6C60 / 表体落 dword_9B3B70 区）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4F4D50(const char *pArg1, int nArg2, int nArg3)  // 函数: 全局整型表后半段加载
{
  int *dword_9B3B702; // esi
  int i; // edi
  uint8_t v6[4]; // [esp+0h] [ebp-2Ch] BYREF
  void *Block; // [esp+4h] [ebp-28h]
  int v8; // [esp+14h] [ebp-18h]
  unsigned int v9; // [esp+18h] [ebp-14h]
  int dword_796E502; // [esp+1Ch] [ebp-10h]
  int v11; // [esp+28h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  strcpy(byte_9B6B60, pArg1);  // 调 strcpy 串拷贝
  if ( byte_9B6B5F[strlen(byte_9B6B60)] != 92 && byte_9B6B5F[strlen(byte_9B6B60)] != 47 )  // 若 byte_9B6B5F[strlen(byte_9B6B60)] != 92 && byte_9B6B5F[strlen(b..
    *(uint16_t *)&byte_9B6B60[strlen(byte_9B6B60)] = 92;
  if ( (uint8_t)sub_443C40((int)&unk_9B6C60, (char)byte_9B6B60, nArg2) == 0  // 脚本文件列表装表
    || (uint8_t)sub_442A10((char)byte_9B6B60, nArg3) == 0 )  // 脚本载入调度（PVF 或磁盘）
  {
    return 0;
  }
  memset(dword_9B3B70, 0, sizeof(dword_9B3B70));  // 调 memset 按字节填充
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  v11 = 0;
  dword_9B3B702 = dword_9B3B70;
  do
  {
    if ( (uint8_t)sub_443430(v6) == 0 )  // 读 token 到 string + 国家码标记
      break;
    for ( i = 100; i != 0; --i )  // 循环：i = 100; i != 0; --i
      *dword_9B3B702++ = sub_4423D0(nullptr);  // *dword_9B3B702++ 写入 sub_4423D0(nullptr)
  }
  while ( (int)dword_9B3B702 < (int)&dword_9B6A50 );  // 当 (int)dword_9B3B702 < (int)&dword_9B6A50 循环
  if ( v9 >= 0x10 )  // 若 v9 >= 0x10
    j__free(Block);  // 调 j__free
  return 1;
}



// ------------------------------------------------------------
// 0x4F4E90 sub_4F4E90 —— 80 字节元素向量反向搬移（串槽深拷贝）
//   从尾向前逐元素 -80：int 直拷、+4 标志字节与 +5/+24/+38 串槽经 sub_41A590、+52 串经
//   sub_4014D0 赋值；返回目标首址。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F4E90(int nArg1, int nArg2, int nArg3)  // 函数: 80 字节元素向量反向搬移（串槽深拷贝）
{
  int nArg22; // ebx
  unsigned int v4; // edi
  unsigned int v5; // esi
  int v6; // ecx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // edx

  nArg22 = nArg2;
  if ( nArg1 != nArg2 )  // 若 nArg1 != nArg2
  {
    v4 = nArg3 + 38;
    v5 = nArg2 + 38;
    do
    {
      v6 = *(uint32_t *)(nArg22 - 80);
      nArg22 -= 80;
      v5 -= 80;
      *(uint32_t *)(nArg3 - 80) = v6;
      v4 -= 80;
      nArg3 -= 80;
      *(uint8_t *)(v4 - 34) = *(uint8_t *)(v5 - 34);
      v7 = sub_41A5E0(v5 - 33);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v4 - 33, v8, v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      *(uint32_t *)(v4 - 18) = *(uint32_t *)(v5 - 18);
      v9 = sub_41A5E0(v5 - 14);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v4 - 14, v10, v9);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v11 = sub_41A5E0(v5);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v4, v12, v11);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      sub_4014D0((std::_String_base *)(v4 + 14), v5 + 14, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
    }
    while ( nArg22 != nArg1 );  // 当 nArg22 != nArg1 循环
  }
  return nArg3;
}



// ------------------------------------------------------------
// 0x4F4F30 sub_4F4F30 —— 80 字节元素数组销毁（串槽清空 + 两段堆回收）
//   逐槽 sub_41BFE0 置空串后，释放 +96/+112 两段指针数组（sub_41B010 + free）并清计数。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F4F30(char *this)  // 函数: 80 字节元素数组销毁（串槽清空 + 两段堆回收）
{
  void **pThis_10; // edi
  int i; // ebx
  void **pThis_3C; // edi
  int j; // ebx
  void **pThis_18; // edi
  int result; // eax
  void **k; // ebx
  void **pThis_1C; // edi
  void **m; // ebx

  *(uint32_t *)this = 0;
  sub_41BFE0((void **)this + 1, szPassword);  // 调 驻留字符串设置
  sub_41BFE0((void **)this + 2, szPassword);  // 调 驻留字符串设置
  sub_41BFE0((void **)this + 3, szPassword);  // 调 驻留字符串设置
  pThis_10 = (void **)(this + 16);
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
    sub_41BFE0(pThis_10++, szPassword);  // 调 驻留字符串设置
  sub_41BFE0((void **)this + 6, szPassword);  // 调 驻留字符串设置
  sub_41BFE0((void **)this + 7, szPassword);  // 调 驻留字符串设置
  sub_41BFE0((void **)this + 8, szPassword);  // 调 驻留字符串设置
  sub_41BFE0((void **)this + 9, szPassword);  // 调 驻留字符串设置
  sub_41BFE0((void **)this + 10, szPassword);  // 调 驻留字符串设置
  pThis_3C = (void **)(this + 60);
  for ( j = 4; j != 0; --j )  // 循环：j = 4; j != 0; --j
  {
    sub_41BFE0(pThis_3C - 4, szPassword);  // 调 驻留字符串设置
    sub_41BFE0(pThis_3C++, szPassword);  // 调 驻留字符串设置
  }
  sub_41BFE0((void **)this + 19, szPassword);  // 调 驻留字符串设置
  sub_41BFE0((void **)this + 20, szPassword);  // 调 驻留字符串设置
  sub_41BFE0((void **)this + 21, szPassword);  // 调 驻留字符串设置
  sub_41BFE0((void **)this + 22, szPassword);  // 调 驻留字符串设置
  pThis_18 = *((void ***)this + 24);
  result = 0;
  if ( pThis_18 != nullptr )  // 若 pThis_18 非空
  {
    for ( k = *((void ***)this + 25); pThis_18 != k; ++pThis_18 )  // 循环：k = *((void ***)this + 25); pThis_18 != k; ++pThis_18
      sub_41B010(pThis_18);  // 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 24));  // 调 j__free
    result = 0;
  }
  *((uint32_t *)this + 24) = 0;  // this+96 = 0
  *((uint32_t *)this + 25) = 0;  // this+100 = 0
  *((uint32_t *)this + 26) = 0;  // this+104 = 0
  pThis_1C = *((void ***)this + 28);
  if ( pThis_1C != nullptr )  // 若 pThis_1C 非空
  {
    for ( m = *((void ***)this + 29); pThis_1C != m; ++pThis_1C )  // 循环：m = *((void ***)this + 29); pThis_1C != m; ++pThis_1C
      sub_41B010(pThis_1C);  // 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 28));  // 调 j__free
    result = 0;
  }
  *((uint32_t *)this + 28) = 0;  // this+112 = 0
  *((uint32_t *)this + 29) = 0;  // this+116 = 0
  *((uint32_t *)this + 30) = 0;  // this+120 = 0
  return result;
}



// ------------------------------------------------------------
// 0x4F5090 sub_4F5090 —— 强化结果对象三段容器释放（+4/+20/+36）
//   分别 free 三段堆并清零 begin/end/cap，末置 +48 标志为 0。
// ------------------------------------------------------------
void /*thiscall*/ sub_4F5090(int this)  // 函数: 强化结果对象三段容器释放（+4/+20/+36）
{
  if ( *(uint32_t *)(this + 4) != 0 )  // 若 *(uint32_t *)(this + 4) != 0
    j__free(*(void **)(this + 4));  // 调 j__free
  *(uint32_t *)(this + 4) = 0;  // this+4 = 0
  *(uint32_t *)(this + 8) = 0;  // this+8 = 0
  *(uint32_t *)(this + 12) = 0;  // this+12 = 0
  if ( *(uint32_t *)(this + 20) != 0 )  // 若 *(uint32_t *)(this + 20) != 0
    j__free(*(void **)(this + 20));  // 调 j__free
  *(uint32_t *)(this + 20) = 0;  // this+20 = 0
  *(uint32_t *)(this + 24) = 0;  // this+24 = 0
  *(uint32_t *)(this + 28) = 0;  // this+28 = 0
  if ( *(uint32_t *)(this + 36) != 0 )  // 若 *(uint32_t *)(this + 36) != 0
    j__free(*(void **)(this + 36));  // 调 j__free
  *(uint32_t *)(this + 36) = 0;  // this+36 = 0
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  *(uint8_t *)(this + 48) = 0;  // this+48 = 0
}



// ------------------------------------------------------------
// 0x4F50F0 sub_4F50F0 —— 80 字节元素正向批量构造（同源复制）
//   以 pArg3 为源向 [uArg1, uArg2) 逐槽 +80 复制（串经 sub_4014D0），vector 扩容填充用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F50F0(uint32_t *uArg1, uint32_t *uArg2, int pArg3)  // 80 字节元素正向批量构造（同源复制）
{
  uint32_t *result; // eax
  uint32_t *uArg12; // ebx
  unsigned int v5; // esi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx

  result = uArg2;
  uArg12 = uArg1;
  if ( uArg1 != uArg2 )  // 若 uArg1 != uArg2
  {
    v5 = (unsigned int)uArg1 + 38;
    do
    {
      *uArg12 = *(uint32_t *)pArg3;  // *uArg12 写入 *(uint32_t *)pArg3
      *(uint8_t *)(v5 - 34) = *(uint8_t *)(pArg3 + 4);
      v6 = sub_41A5E0(pArg3 + 5);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v5 - 33, v7, v6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      *(uint32_t *)(v5 - 18) = *(uint32_t *)(pArg3 + 20);
      v8 = sub_41A5E0(pArg3 + 24);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v5 - 14, v9, v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v10 = sub_41A5E0(pArg3 + 38);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v5, v11, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      sub_4014D0((std::_String_base *)(v5 + 14), pArg3 + 52, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
      result = uArg2;
      uArg12 += 20;
      v5 += 80;
    }
    while ( uArg12 != uArg2 );  // 当 uArg12 != uArg2 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F5170 sub_4F5170 —— 薄封装（转 4F4E90 反向搬移）
//   参数直通 sub_4F4E90，供插入路径统一入口。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F5170(int nArg1, int nArg2, int nArg3)  // 函数: 薄封装（转 4F4E90 反向搬移）
{
  return sub_4F4E90(nArg1, nArg2, nArg3);  // 80 字节元素向量反向搬移（串槽深拷贝）
}



// ------------------------------------------------------------
// 0x4F5190 sub_4F5190 —— 80 字节元素填充构造（nArg2 个）
//   循环经 sub_4EBCC0 从单元素 nArg3 复制构造（步长 80），异常展开标记 v7。
// ------------------------------------------------------------
int /*cdecl*/ sub_4F5190(int nArg1, int nArg2, int nArg3)  // 函数: 80 字节元素填充构造（nArg2 个）
{
  int nArg12; // esi
  int result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg12 = nArg1;
  v6[4] = v6;
  v6[3] = nArg1;
  v7 = 0;
  while ( nArg2 != 0 )  // 当 nArg2 != 0 循环
  {
    LOBYTE(v7) = 1;
    if ( nArg12 != 0 )  // 若 nArg12 != 0
      result = sub_4EBCC0(nArg3);  // 结果 = 属性条目拷贝构造（80 字节条目）
    --nArg2;  // 自减nArg2
    nArg12 += 80;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F5220 sub_4F5220 —— cfloat 复合对象构造（clong×2 + 串槽 + 收尾）
//   +20 起 sub_41A630/vftbl_cfloat 与 ·0x4F4B60（clong×2），+72 串槽 SSO 置空，末调 sub_4EBD50。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F5220(int this)  // 函数: cfloat 复合对象构造（clong×2 + 串槽 + 收尾）
{
  uint32_t *pThis_5; // edi

  pThis_5 = (uint32_t *)(this + 5);
  sub_41A630(this + 5);  // 调 sub_41A630
  *pThis_5 = &vftbl_cfloat;  // *pThis_5 写入 &vftbl_cfloat
  sub_4F4B60((uint32_t *)(this + 20));  // clong 双槽快速构造（类型字 4）
  *(uint32_t *)(this + 76) = 15;  // this+76 = 15
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint8_t *)(this + 56) = 0;  // this+56 = 0
  sub_4EBD50(this);  // 属性条目默认构造（清零 + 空串 + +20 = 4）
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F5290 sub_4F5290 —— 124 字节元素深拷贝构造（串容器 + 4×4 双段）
//   逐字段复制（sub_41B0D0 串、sub_41C170 元素、sub_4B3600 指针容器）后两组 eh 向量拷贝
//   迭代（4×4）；装备/属性元素搬运核心。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F5290(uint32_t *this, uint32_t *pArg2)  // 124 字节元素深拷贝构造（串容器 + 4×4 双段）
{
  *this = *pArg2;  // *this 写入 *pArg2
  *(this + 1) = 0;  // this+4 = 0
  sub_41B0D0(pArg2 + 1);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(this + 2) = 0;  // this+8 = 0
  sub_41B0D0(pArg2 + 2);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(this + 3) = 0;  // this+12 = 0
  sub_41B0D0(pArg2 + 3);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  `eh vector copy constructor iterator'(
    this + 4,
    a2 + 4,
    4u,
    2,
    (void (/*thiscall*/ *)(void *, void *))sub_41C170,
    sub_401060);
  *(this + 6) = 0;  // this+24 = 0
  sub_41B0D0(a2 + 6);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(this + 7) = 0;  // this+28 = 0
  sub_41B0D0(a2 + 7);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(this + 8) = 0;  // this+32 = 0
  sub_41B0D0(a2 + 8);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(this + 9) = 0;  // this+36 = 0
  sub_41B0D0(a2 + 9);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(this + 10) = 0;  // this+40 = 0
  sub_41B0D0(a2 + 10);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  `eh vector copy constructor iterator'(
    this + 11,
    pArg2 + 11,
    4u,
    4,
    (void (/*thiscall*/ *)(void *, void *))sub_41C170,
    sub_401060);
  `eh vector copy constructor iterator'(
    this + 15,
    pArg2 + 15,
    4u,
    4,
    (void (/*thiscall*/ *)(void *, void *))sub_41C170,
    sub_401060);
  *(this + 19) = 0;  // this+76 = 0
  sub_41B0D0(pArg2 + 19);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(this + 20) = 0;  // this+80 = 0
  sub_41B0D0(pArg2 + 20);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(this + 21) = 0;  // this+84 = 0
  sub_41B0D0(pArg2 + 21);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(this + 22) = 0;  // this+88 = 0
  sub_41B0D0(pArg2 + 22);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_4B3600(pArg2 + 23);  // 指针容器拷贝赋值
  sub_4B3600(pArg2 + 27);  // 指针容器拷贝赋值
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F5450 sub_4F5450 —— 124 字节元素赋值拷贝（串替身重建）
//   由源 pszArg2 逐字段 sub_41B0D0 重建全部串引用与 2+4+4 组容器，末 sub_41DC80 处理两处
//   指针容器；返回 this。
// ------------------------------------------------------------
char */*thiscall*/ sub_4F5450(char *this, char *pszArg2)  // 124 字节元素赋值拷贝（串替身重建）
{
  int v4; // eax
  uint32_t *pThis_10; // ebx
  uint32_t *pThis_2C; // ebx
  uint32_t *pThis_3C; // ebx
  int v9; // [esp+Ch] [ebp-4h]
  int i; // [esp+Ch] [ebp-4h]
  int j; // [esp+Ch] [ebp-4h]
  int v12; // [esp+18h] [ebp+8h]

  *(uint32_t *)this = *(uint32_t *)pszArg2;
  sub_41B0D0(pszArg2 + 4);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(pszArg2 + 8);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(pszArg2 + 12);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  v4 = pszArg2 - this;
  pThis_10 = this + 16;
  v12 = pszArg2 - this;
  v9 = 2;
  while ( 1 )  // 当 1 循环
  {
    sub_41B0D0((char *)pThis_10++ + v4);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
    if ( --v9 == 0 )  // 若 --v9 == 0
      break;
    v4 = v12;
  }
  sub_41B0D0(pszArg2 + 24);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(pszArg2 + 28);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(pszArg2 + 32);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(pszArg2 + 36);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(pszArg2 + 40);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  pThis_2C = this + 44;
  for ( i = 4; i != 0; --i )  // 循环：i = 4; i != 0; --i
    sub_41B0D0((char *)pThis_2C++ + v12);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  pThis_3C = this + 60;
  for ( j = 4; j != 0; --j )  // 循环：j = 4; j != 0; --j
    sub_41B0D0((char *)pThis_3C++ + v12);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(pszArg2 + 76);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(pszArg2 + 80);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(pszArg2 + 84);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(pszArg2 + 88);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41DC80(pszArg2 + 92);  // vector<T 4B 驻留句柄> 拷贝赋值 operator=
  sub_41DC80(pszArg2 + 108);  // vector<T 4B 驻留句柄> 拷贝赋值 operator=
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F55A0 sub_4F55A0 —— 124 字节元素反向搬移赋值
//   从尾向前按 124 步长逐元素 sub_4F5450，返回目标首址；供 ·0x4F57A0 插入。
// ------------------------------------------------------------
char */*cdecl*/ sub_4F55A0(char *pszArg1, char *pszArg2, char *pszArg3)  // 124 字节元素反向搬移赋值
{
  char *pszArg22; // esi
  char *pszArg32; // edi

  pszArg22 = pszArg2;
  if ( pszArg1 == pszArg2 )  // 若 pszArg1 == pszArg2
    return pszArg3;
  pszArg32 = pszArg3;
  do
  {
    pszArg22 -= 124;
    pszArg32 -= 124;
    sub_4F5450(pszArg32, pszArg22);  // 124 字节元素赋值拷贝（串替身重建）
  }
  while ( pszArg22 != pszArg1 );  // 当 pszArg22 != pszArg1 循环
  return pszArg32;
}



// ------------------------------------------------------------
// 0x4F55E0 sub_4F55E0 —— 物品解析结果块构造
//   逐槽 sub_41BFE0 置空串（+4..+88），3 组 eh 向量构造（2/4/4，sub_432D20），尾部计数清零
//   后 sub_4F4F30 收尾。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F55E0(int this)  // 函数: 物品解析结果块构造
{
  void **pThis_4; // ecx

  pThis_4 = (void **)(this + 4);
  *pThis_4 = nullptr;  // *pThis_4 写入 nullptr
  sub_41BFE0(pThis_4, szPassword);  // 调 驻留字符串设置
  *(uint32_t *)(this + 8) = 0;  // this+8 = 0
  sub_41BFE0((void **)(this + 8), szPassword);  // 调 驻留字符串设置
  *(uint32_t *)(this + 12) = 0;  // this+12 = 0
  sub_41BFE0((void **)(this + 12), szPassword);  // 调 驻留字符串设置
  `eh vector constructor iterator'((void *)(this + 16), 4u, 2, sub_432D20, sub_401060);
  *(uint32_t *)(this + 24) = 0;  // this+24 = 0
  sub_41BFE0((void **)(this + 24), szPassword);  // 调 驻留字符串设置
  *(uint32_t *)(this + 28) = 0;  // this+28 = 0
  sub_41BFE0((void **)(this + 28), szPassword);  // 调 驻留字符串设置
  *(uint32_t *)(this + 32) = 0;  // this+32 = 0
  sub_41BFE0((void **)(this + 32), szPassword);  // 调 驻留字符串设置
  *(uint32_t *)(this + 36) = 0;  // this+36 = 0
  sub_41BFE0((void **)(this + 36), szPassword);  // 调 驻留字符串设置
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  sub_41BFE0((void **)(this + 40), szPassword);  // 调 驻留字符串设置
  `eh vector constructor iterator'((void *)(this + 44), 4u, 4, sub_432D20, sub_401060);
  `eh vector constructor iterator'((void *)(this + 60), 4u, 4, sub_432D20, sub_401060);
  *(uint32_t *)(this + 76) = 0;  // this+76 = 0
  sub_41BFE0((void **)(this + 76), szPassword);  // 调 驻留字符串设置
  *(uint32_t *)(this + 80) = 0;  // this+80 = 0
  sub_41BFE0((void **)(this + 80), szPassword);  // 调 驻留字符串设置
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  sub_41BFE0((void **)(this + 84), szPassword);  // 调 驻留字符串设置
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  sub_41BFE0((void **)(this + 88), szPassword);  // 调 驻留字符串设置
  *(uint32_t *)(this + 96) = 0;  // this+96 = 0
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  *(uint32_t *)(this + 104) = 0;  // this+104 = 0
  *(uint32_t *)(this + 112) = 0;  // this+112 = 0
  *(uint32_t *)(this + 116) = 0;  // this+116 = 0
  *(uint32_t *)(this + 120) = 0;  // this+120 = 0
  sub_4F4F30((char *)this);  // 80 字节元素数组销毁（串槽清空 + 两段堆回收）
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F5770 sub_4F5770 —— 80 字节元素填充 + 返回尾址（组合器）
//   sub_4F5190 填充后返回 nArg1 + 80×nArg2。
// ------------------------------------------------------------
int /*stdcall*/ sub_4F5770(int nArg1, int nArg2, int nArg3)  // 函数: 80 字节元素填充 + 返回尾址（组合器）
{
  sub_4F5190(nArg1, nArg2, nArg3);  // 80 字节元素填充构造（nArg2 个）
  return nArg1 + 80 * nArg2;
}



// ------------------------------------------------------------
// 0x4F57A0 sub_4F57A0 —— 80 字节元素向量插入（三路分支 + 1.5 倍扩容）
//   就地分支 sub_4ED730/sub_4F5170/sub_4F50F0；重建经 operator new + sub_4F5190 填洞与
//   sub_4F5770，旧段 sub_435890 析构；超限 sub_434730；首元素先 sub_4EBCC0 构临时。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F57A0(int this, int pArg2, unsigned int uArg3, int nArg4)  // 函数: 80 字节元素向量插入（三路分支 + 1.5 倍扩容）
{
  int fld_4; // ebx
  unsigned int fld_C; // ecx
  int fld_8; // eax
  int fld_82; // eax
  unsigned int v10; // ecx
  int fld_87; // eax
  char *pMem; // ebx
  int fld_43; // eax
  unsigned int v14; // edi
  int fld_44; // eax
  char *fld_83; // ecx
  int fld_86; // edi
  int fld_42; // [esp-18h] [ebp-94h]
  int fld_88; // [esp-10h] [ebp-8Ch]
  int fld_85; // [esp-Ch] [ebp-88h]
  unsigned int fld_84; // [esp-8h] [ebp-84h]
  int v24; // [esp+0h] [ebp-7Ch] BYREF
  void *Block; // [esp+Ch] [ebp-70h]
  int pThis; // [esp+10h] [ebp-6Ch]
  char *pMem2; // [esp+14h] [ebp-68h]
  char v28[80]; // [esp+18h] [ebp-64h] BYREF
  int dword_796E502; // [esp+68h] [ebp-14h]
  int *v30; // [esp+6Ch] [ebp-10h]
  int v31; // [esp+78h] [ebp-4h]
  int v32; // [esp+84h] [ebp+8h]
  int v33; // [esp+88h] [ebp+Ch]
  char *fld_832; // [esp+8Ch] [ebp+10h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v30 = &v24;
  pThis = this;
  sub_4EBCC0(v28, nArg4);  // 属性条目拷贝构造（80 字节条目）
  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  fld_C = 0;
  v31 = 0;
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    fld_C = (*(uint32_t *)(this + 12) - fld_4) / 80;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 80;
    else
      fld_8 = 0;
    if ( 53687091 - fld_8 < uArg3 )  // 若 53687091 - fld_8 < uArg3
      sub_434730(this);  // vector 超长抛 length_error
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) / 80;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )  // 若 fld_C >= uArg3 + fld_82
    {
      fld_83 = *(char **)(this + 8);
      fld_832 = fld_83;
      if ( (int)&fld_83[-pArg2] / 80 >= uArg3 )  // 若 (int)&fld_83[-pArg2] / 80 >= uArg3
      {
        v32 = (int)&fld_83[-80 * uArg3];
        *(uint32_t *)(this + 8) = sub_4ED730(v32, (int)fld_83, fld_83);  // 80B 条目区间拷构
        sub_4F5170(pArg2, v32, fld_832);  // 薄封装（转 4F4E90 反向搬移）
        sub_4F50F0(pArg2, pArg2 + 80 * uArg3, v28);  // 80 字节元素正向批量构造（同源复制）
      }
      else
      {
        sub_4ED730(pArg2, (int)fld_83, (char *)(pArg2 + 80 * uArg3));  // 80B 条目区间拷构
        fld_84 = uArg3 - (*(uint32_t *)(this + 8) - pArg2) / 80;
        fld_85 = *(uint32_t *)(this + 8);  // fld_85 = this+8
        LOBYTE(v31) = 3;
        sub_4F5770(fld_85, fld_84, v28);  // 80 字节元素填充 + 返回尾址（组合器）
        fld_86 = 80 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;  // this+8 = fld_86
        v31 = 0;
        sub_4F50F0(pArg2, fld_86 - 80 * uArg3, v28);  // 80 字节元素正向批量构造（同源复制）
      }
    }
    else
    {
      if ( 53687091 - (fld_C >> 1) >= fld_C )  // 若 53687091 - (fld_C >> 1) >= fld_C
        v10 = (fld_C >> 1) + fld_C;
      else
        v10 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 != 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) / 80;
      else
        fld_87 = 0;
      if ( v10 < uArg3 + fld_87 )  // 若 v10 < uArg3 + fld_87
        v10 = uArg3 + sub_4EAF60((int *)this);  // 结果 = 元素个数 =（+8 − +4）/80
      v33 = 80 * v10;
      pMem = (char *)operator new(80 * v10);
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = this+4
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v31) = 1;
      pMem2 = sub_4ED730(fld_42, pArg2, pMem);  // 结果 = 80B 条目区间拷构
      sub_4F5190(pMem2, uArg3, v28);  // 80 字节元素填充构造（nArg2 个）
      fld_88 = *(uint32_t *)(this + 8);  // fld_88 = this+8
      pMem2 += 80 * uArg3;
      sub_4ED730(pArg2, fld_88, pMem2);  // 80B 条目区间拷构
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = this+4
      v31 = 0;
      if ( fld_43 != 0 )  // 若 fld_43 != 0
        fld_43 = (*(uint32_t *)(this + 8) - fld_43) / 80;
      v14 = fld_43 + uArg3;
      fld_44 = *(uint32_t *)(this + 4);  // fld_44 = this+4
      if ( fld_44 != 0 )  // 若 fld_44 != 0
      {
        sub_435890(fld_44, *(uint32_t *)(this + 8));  // 80 字节条目区间析构
        j__free(*(void **)(this + 4));  // 调 j__free
      }
      *(uint32_t *)(this + 12) = &pMem[v33];  // this+12 = &pMem[v33]
      *(uint32_t *)(this + 8) = &pMem[80 * v14];  // this+8 = &pMem[80 * v14]
      *(uint32_t *)(this + 4) = pMem;  // this+4 = pMem
    }
  }
  v31 = -1;
  return sub_433D10(v28);  // 条目析构（串与三防篡改槽）
}


// ------------------------------------------------------------
// 0x4F5AB0 sub_4F5AB0 —— 124 字节元素正向批量赋值（同源复制）
//   由 pszArg3 单元素逐槽 sub_4F5450 赋值（步长 124）；对应 80 字节族 ·0x4F50F0。
// ------------------------------------------------------------
char */*cdecl*/ sub_4F5AB0(char *pszArg1, char *pszArg2, char *pszArg3)  // 124 字节元素正向批量赋值（同源复制）
{
  char *i; // esi
  char *result; // eax

  for ( i = pszArg1; i != pszArg2; i += 124 )  // 循环：i = pszArg1; i != pszArg2; i += 124
    result = sub_4F5450(i, pszArg3);  // 结果 = 124 字节元素赋值拷贝（串替身重建）
  return result;
}



// ------------------------------------------------------------
// 0x4F5AE0 sub_4F5AE0 —— 薄封装（转 4F55A0 反向搬移）
//   参数直通 sub_4F55A0，供插入路径统一入口。
// ------------------------------------------------------------
char */*cdecl*/ sub_4F5AE0(char *pszArg1, char *pszArg2, char *pszArg3)  // 薄封装（转 4F55A0 反向搬移）
{
  return sub_4F55A0(pszArg1, pszArg2, pszArg3);  // 124 字节元素反向搬移赋值
}



// ------------------------------------------------------------
// 0x4F5B00 sub_4F5B00 —— 124 字节元素反向搬移深拷贝
//   从尾向前逐元素 sub_4F5290 深拷贝到目标区，返回目标尾址。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F5B00(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 124 字节元素反向搬移深拷贝
{
  uint32_t *uArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v6[4] = v6;
  v6[3] = uArg3;
  v7 = 0;
  while ( uArg1 != uArg2 )  // 当 uArg1 != uArg2 循环
  {
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )  // 若 uArg32 非空
      sub_4F5290(uArg32, uArg1);  // 124 字节元素深拷贝构造（串容器 + 4×4 双段）
    uArg32 += 31;
    LOBYTE(v7) = 0;
    uArg1 += 31;
  }
  return uArg32;
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
char /*cdecl*/ sub_4F5B90(int pArg1, int ArgList)  // 函数: 释放后返回
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
  int dword_796E502; // [esp+34h] [ebp-10h]
  int v18; // [esp+40h] [ebp-4h]

  v2 = (const char *)ArgList;
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = sub_442A10((char)&unk_9B6B60, ArgList);  // 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result != 0 )  // 若 result != 0
  {
    sub_4CF480(pArg1);  // 调 sub_4CF480
    v16 = 15;
    v15 = 0;
    LOBYTE(Block) = 0;
    v18 = 0;
    v12 = nullptr;  // v12 = nullptr 空指针
    sub_41BFE0(&v12, szPassword);  // 调 驻留字符串设置
    LOBYTE(v18) = 1;
    for ( i = 0; (uint8_t)sub_443430(&v13) != 0; v2 = (const char *)ArgList )  // 循环：i = 0; (uint8_t)sub_443430(&v13) != 0; v2 = (const char *)Ar
    {
      if ( (uint8_t)sub_442BC0(&v13) != 0 )  // 国家码标签配对校验（bool）
        off_77F3FC((char *)&byte_6FA9F8, v2);
      if ( sub_40BF00((std::_String_base *)&v13, 0, v15, "[name]", 6u) != 0 )  // 字符串 “[name]”
      {
        if ( sub_40BF00((std::_String_base *)&v13, 0, v15, "[name2]", 7u) != 0 )  // 字符串 “[name2]”
        {
          if ( sub_40BF00((std::_String_base *)&v13, 0, v15, "[explain]", 9u) != 0 )  // 字符串 “[explain]”
          {
            if ( sub_40BF00((std::_String_base *)&v13, 0, v15, "[flavor text]", 0xDu) != 0 )  // 字符串 “[flavor text]”
            {
              if ( (uint8_t)sub_423300(&v13, "[grade]") != 0 )  // 字符串 “[grade]”
              {
                *(uint32_t *)(pArg1 + 20) = sub_4423D0(nullptr);  // pArg1+20 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[attach type]") != 0 )  // 字符串 “[attach type]”
              {
                j = &v12;
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                if ( sub_43BCF0(&v12, "[free]") )  // 字符串 “[free]”
                {
                  *(uint32_t *)(pArg1 + 24) = 0;  // pArg1+24 = 0
                }
                else if ( sub_43BCF0(&v12, "[trade]") )  // 字符串 “[trade]”
                {
                  *(uint32_t *)(pArg1 + 24) = 1;  // pArg1+24 = 1
                }
                else if ( sub_43BCF0(&v12, "[trade delete]") )  // 字符串 “[trade delete]”
                {
                  *(uint32_t *)(pArg1 + 24) = 2;  // pArg1+24 = 2
                }
                else if ( sub_43BCF0(&v12, "[sealing]") )  // 字符串 “[sealing]”
                {
                  *(uint32_t *)(pArg1 + 24) = 3;  // pArg1+24 = 3
                }
              }
              else if ( (uint8_t)sub_423300(&v13, "[creation rate]") != 0 )  // 字符串 “[creation rate]”
              {
                *(uint32_t *)(pArg1 + 28) = sub_4423D0(nullptr);  // pArg1+28 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[rarity]") != 0 )  // 字符串 “[rarity]”
              {
                *(uint32_t *)(pArg1 + 32) = sub_4423D0(nullptr);  // pArg1+32 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[weight]") != 0 )  // 字符串 “[weight]”
              {
                *(uint32_t *)(pArg1 + 56) = sub_4423D0(nullptr);  // pArg1+56 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[usable job]") != 0 )  // 字符串 “[usable job]”
              {
                for ( j = &v12; sub_442E10() != 0; j = &v12 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                {
                  v4 = sub_41ACF0(&v12);  // 结果 = 驻留串句柄 → 字符串指针
                  v5 = sub_4426A0(v4);  // 【职业标签→索引（[swordman]/[fighter]/[gunner]/[mag…】
                  if ( v5 == 4 )  // 若 v5 == 4
                  {
                    *(uint32_t *)(pArg1 + 60) = 16843009;  // pArg1+60 = 16843009
                    *(uint8_t *)(pArg1 + 152) = 1;  // pArg1+152 = 1
                  }
                  else
                  {
                    *(uint8_t *)(pArg1 + v5 + 60) = 1;
                  }
                }
              }
              else if ( (uint8_t)sub_423300(&v13, "[stackable type]") != 0 )  // 字符串 “[stackable type]”
              {
                j = &v12;
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                if ( sub_43BCF0(&v12, "[waste]") )  // 字符串 “[waste]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 100) = 0;  // pArg1+100 = 0
                  *(uint32_t *)(pArg1 + 156) = sub_4423D0(j);  // pArg1+156 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v12, "[material]") )  // 字符串 “[material]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 100) = 1;  // pArg1+100 = 1
                  *(uint32_t *)(pArg1 + 156) = sub_4423D0(j);  // pArg1+156 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v12, "[recipe]") )  // 字符串 “[recipe]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 100) = 2;  // pArg1+100 = 2
                  *(uint32_t *)(pArg1 + 156) = sub_4423D0(j);  // pArg1+156 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v12, "[throw]") )  // 字符串 “[throw]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 100) = 3;  // pArg1+100 = 3
                  *(uint32_t *)(pArg1 + 156) = sub_4423D0(j);  // pArg1+156 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v12, "[set]") )  // 字符串 “[set]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 100) = 4;  // pArg1+100 = 4
                  *(uint32_t *)(pArg1 + 156) = sub_4423D0(j);  // pArg1+156 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v12, "[legacy]") )  // 字符串 “[legacy]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 100) = 5;  // pArg1+100 = 5
                  *(uint32_t *)(pArg1 + 156) = sub_4423D0(j);  // pArg1+156 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v12, "[quest]") )  // 字符串 “[quest]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 100) = 6;  // pArg1+100 = 6
                  *(uint32_t *)(pArg1 + 156) = sub_4423D0(j);  // pArg1+156 = sub_4423D0(j)
                }
                else
                {
                  if ( sub_43BCF0(&v12, "[etc]") )  // 字符串 “[etc]”
                    *(uint32_t *)(pArg1 + 100) = 7;  // pArg1+100 = 7
                  *(uint32_t *)(pArg1 + 156) = sub_4423D0(nullptr);  // pArg1+156 = sub_4423D0(nullptr)
                }
              }
              else if ( (uint8_t)sub_423300(&v13, "[minimum level]") != 0 )  // 字符串 “[minimum level]”
              {
                *(uint32_t *)(pArg1 + 64) = sub_4423D0(nullptr);  // pArg1+64 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[cool time]") != 0 )  // 字符串 “[cool time]”
              {
                *(uint32_t *)(pArg1 + 68) = sub_4423D0(nullptr);  // pArg1+68 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[cooltime group]") != 0 )  // 字符串 “[cooltime group]”
              {
                *(uint32_t *)(pArg1 + 72) = sub_4423D0(nullptr);  // pArg1+72 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[party cooltime]") != 0 )  // 字符串 “[party cooltime]”
              {
                *(uint8_t *)(pArg1 + 76) = sub_4423D0(nullptr) != 0;  // pArg1+76 = sub_4423D0(nullptr) != 0
              }
              else if ( (uint8_t)sub_423300(&v13, "[icon]") != 0 )  // 字符串 “[icon]”
              {
                j = (void **)(pArg1 + 80);
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                *(uint32_t *)(pArg1 + 84) = sub_4423D0(nullptr);  // pArg1+84 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[field image]") != 0 )  // 字符串 “[field image]”
              {
                j = (void **)(pArg1 + 88);
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                *(uint32_t *)(pArg1 + 92) = sub_4423D0(nullptr);  // pArg1+92 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[price]") != 0 )  // 字符串 “[price]”
              {
                *(uint32_t *)(pArg1 + 36) = sub_4423D0(nullptr);  // pArg1+36 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[value]") != 0 )  // 字符串 “[value]”
              {
                *(uint32_t *)(pArg1 + 52) = sub_4423D0(nullptr);  // pArg1+52 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[finish point price]") != 0 )  // 字符串 “[finish point price]”
              {
                *(uint32_t *)(pArg1 + 40) = sub_4423D0(nullptr);  // pArg1+40 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[cash]") != 0 )  // 字符串 “[cash]”
              {
                *(uint32_t *)(pArg1 + 44) = sub_4423D0(nullptr);  // pArg1+44 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[medal]") != 0 )  // 字符串 “[medal]”
              {
                *(uint32_t *)(pArg1 + 48) = sub_4423D0(nullptr);  // pArg1+48 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v13, "[move wav]") != 0 )  // 字符串 “[move wav]”
              {
                j = (void **)(pArg1 + 104);
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
              }
              else if ( (uint8_t)sub_423300(&v13, "[use wav]") != 0 )  // 字符串 “[use wav]”
              {
                j = (void **)(pArg1 + 116);
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
              }
              else if ( (uint8_t)sub_423300(&v13, "[int data]") != 0 )  // 字符串 “[int data]”
              {
                sub_5E5260((void **)(pArg1 + 120));  // 调 sub_5E5260
                for ( k = (void ***)sub_4423D0(&i); i != 0; k = (void ***)sub_4423D0(&i) )  // 循环：k = (void ***)sub_4423D0(&i); i != 0; k = (void ***)sub_4423
                  sub_431230(pArg1 + 120, &k);  // uint32 vector push_back
              }
              else if ( (uint8_t)sub_423300(&v13, "[string data]") != 0 )  // 字符串 “[string data]”
              {
                sub_4017E0(pArg1 + 136);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                for ( j = &v12; sub_442E10() != 0; j = &v12 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                  sub_420BB0(&v12);  // vector push_back（4 字节元素）
              }
              else if ( (uint8_t)sub_423300(&v13, "[applying range]") != 0 )  // 字符串 “[applying range]”
              {
                *(uint32_t *)(pArg1 + 96) = sub_4423D0(nullptr);  // pArg1+96 = sub_4423D0(nullptr)
              }
              else
              {
                k = v8;
                sub_401690(&v13);  // std::string 拷贝构造（复位 +20/+24/+4 后 ·sub_4014D0 全
                if ( sub_442C80((char)v8[0], v8[1], (int)v8[2], (int)v8[3], (int)v8[4], (int)v8[5], (unsigned int)j) == 0 )  // 判首字符方括号并析构
                {
                  p_Block = (const char *)Block;
                  if ( v16 < 0x10 )  // 若 v16 < 0x10
                    p_Block = (const char *)&Block;
                  off_77F3FC("SCRIPT TAG ERROR! [%s] %s", v2, p_Block);  // 字符串 “SCRIPT TAG ERROR! [%s] %s”
                }
              }
            }
            else
            {
              j = (void **)(pArg1 + 16);
              sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
            }
          }
          else
          {
            j = (void **)(pArg1 + 12);
            sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
          }
        }
        else
        {
          j = (void **)(pArg1 + 8);
          sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
        }
      }
      else
      {
        j = (void **)(pArg1 + 4);
        sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      }
    }
    if ( *(uint32_t *)(pArg1 + 52) == -1 )  // 若 *(uint32_t *)(pArg1 + 52) == -1
      *(uint32_t *)(pArg1 + 52) = *(uint32_t *)(pArg1 + 36);  // pArg1+52 = *(uint32_t *)(pArg1 + 36)
    v7 = 10 * *(uint32_t *)(pArg1 + 44) + *(uint32_t *)(pArg1 + 36);
    j = (void **)v2;
    *(uint32_t *)(pArg1 + 36) = v7;  // pArg1+36 = v7
    *(uint32_t *)(pArg1 + 44) = 0;  // pArg1+44 = 0
    *(uint32_t *)pArg1 = sub_4A2F80(j);
    LOBYTE(v18) = 0;
    sub_41B010(&v12);  // 驻留句柄析构（引用计数减到 0 释放）
    if ( v16 >= 0x10 )  // 若 v16 >= 0x10
      j__free(Block);  // 调 j__free
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4F6390 sub_4F6390 —— 强化结果三段 8 字节对表填充（+4/+20/+36）
//   以 pArg2 头依次读三组计数，逐对 (u32,u32) 追加：留有余量 sub_63A7C0 就地、否则 sub_473A80
//   扩容；末位 +48 置标志。
// ------------------------------------------------------------
char /*cdecl*/ sub_4F6390(uint32_t *pArg1, int pArg2)  // 函数: 强化结果三段 8 字节对表填充（+4/+20/+36）
{
  uint32_t *pArg12; // ebx
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

  pArg12 = pArg1;
  sub_4F5090(pArg1);  // 强化结果对象三段容器释放（+4/+20/+36）
  v3 = *(int **)(pArg2 + 4);
  v4 = *v3;
  v5 = v3 + 1;
  if ( v4 > 0 )  // 若 v4 > 0
  {
    for ( i = v4; i != 0; --i )  // 循环：i = v4; i != 0; --i
    {
      v6 = v5[1];
      v25 = *v5;
      v7 = pArg1[1];
      v5 += 2;
      v26 = v6;
      if ( v7 != 0 )  // 若 v7 != 0
        v8 = (pArg1[2] - v7) >> 3;
      else
        v8 = 0;
      if ( v7 != 0 && v8 < (pArg1[3] - v7) >> 3 )  // 若 v7 != 0 && v8 < (pArg1[3] - v7) >> 3
      {
        v9 = pArg1[2];
        sub_63A7C0(v9, 1, &v25);  // 强化结果公共件
        pArg1[2] = v9 + 8;  // pArg1[2] 写入 v9 + 8
      }
      else
      {
        sub_473A80(pArg1[2], 1, &v25);  // 调 sub_473A80
      }
    }
  }
  v10 = *v5;
  v11 = v5 + 1;
  if ( v10 > 0 )  // 若 v10 > 0
  {
    for ( i = v10; i != 0; --i )  // 循环：i = v10; i != 0; --i
    {
      v12 = *v11;
      v26 = v11[1];
      v13 = pArg1[5];
      v11 += 2;
      v25 = v12;
      if ( v13 != 0 )  // 若 v13 != 0
        v14 = (pArg1[6] - v13) >> 3;
      else
        v14 = 0;
      if ( v13 != 0 && v14 < (pArg1[7] - v13) >> 3 )  // 若 v13 != 0 && v14 < (pArg1[7] - v13) >> 3
      {
        v15 = pArg1[6];
        sub_63A7C0(v15, 1, &v25);  // 强化结果公共件
        pArg1[6] = v15 + 8;  // pArg1[6] 写入 v15 + 8
        pArg12 = pArg1;
      }
      else
      {
        sub_473A80(pArg1[6], 1, &v25);  // 调 sub_473A80
      }
    }
  }
  v16 = *v11;
  v17 = v11 + 1;
  if ( v16 > 0 )  // 若 v16 > 0
  {
    v18 = pArg12 + 8;
    for ( i = v16; i != 0; --i )  // 循环：i = v16; i != 0; --i
    {
      v19 = *v17;
      v20 = v17[1];
      v21 = v18[1];
      v17 += 2;
      v25 = v19;
      v26 = v20;
      if ( v21 != 0 )  // 若 v21 != 0
        v22 = (v18[2] - v21) >> 3;
      else
        v22 = 0;
      if ( v21 != 0 && v22 < (v18[3] - v21) >> 3 )  // 若 v21 != 0 && v22 < (v18[3] - v21) >> 3
      {
        v23 = v18[2];
        LOBYTE(v16) = sub_63A7C0(v23, 1, &v25);  // 强化结果公共件
        v18[2] = v23 + 8;  // v18[2] 写入 v23 + 8
        pArg12 = pArg1;
      }
      else
      {
        LOBYTE(v16) = sub_473A80(v18[2], 1, &v25);
      }
    }
  }
  if ( v17 != *(int **)(pArg2 + 8) )  // 若 v17 != *(int **)(pArg2 + 8)
  {
    LOBYTE(v16) = *v17 == 1;
    *((uint8_t *)pArg12 + 48) = v16;
  }
  return v16;
}


// ------------------------------------------------------------
// 0x4F6540 sub_4F6540 —— 强化结果单向量 8 字节对表填充
//   先释放旧 +8 段，再以源首 u32 写 +0，随后逐对追加至 +8 向量（sub_63A7C0/sub_473A80）。
// ------------------------------------------------------------
int */*cdecl*/ sub_4F6540(int pArg1, int pArg2)  // 强化结果单向量 8 字节对表填充
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

  *(uint32_t *)pArg1 = 0;
  if ( *(uint32_t *)(pArg1 + 8) != 0 )  // 若 *(uint32_t *)(pArg1 + 8) != 0
    j__free(*(void **)(pArg1 + 8));  // 调 j__free
  *(uint32_t *)(pArg1 + 8) = 0;  // pArg1+8 = 0
  *(uint32_t *)(pArg1 + 12) = 0;  // pArg1+12 = 0
  *(uint32_t *)(pArg1 + 16) = 0;  // pArg1+16 = 0
  v2 = *(uint32_t **)(pArg2 + 4);
  *(uint32_t *)pArg1 = *v2;
  result = *(int **)(pArg2 + 8);
  for ( i = v2 + 1; i != result; result = *(int **)(pArg2 + 8) )  // 循环：i = v2 + 1; i != result; result = *(int **)(pArg2 + 8)
  {
    v5 = *i;
    v6 = i + 1;
    v12 = 0;
    v11 = v5;
    if ( v6 == result )  // 若 v6 == result
      break;
    v7 = *v6;
    v8 = *(uint32_t *)(pArg1 + 8);  // v8 = pArg1+8
    i = v6 + 1;
    v12 = v7;
    v9 = v8 != 0 ? (*(uint32_t *)(pArg1 + 12) - v8) >> 3 : 0;
    if ( v8 != 0 && v9 < (*(uint32_t *)(pArg1 + 16) - v8) >> 3 )  // 若 v8 != 0 && v9 < (*(uint32_t *)(pArg1 + 16) - v8) >> 3
    {
      v10 = *(uint32_t *)(pArg1 + 12);  // v10 = pArg1+12
      sub_63A7C0(v10, 1, &v11);  // 强化结果公共件
      *(uint32_t *)(pArg1 + 12) = v10 + 8;  // pArg1+12 = v10 + 8
    }
    else
    {
      sub_473A80(*(uint32_t *)(pArg1 + 12), 1, &v11);  // 调 sub_473A80
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F6600 sub_4F6600 —— 80 字节元素单点插入（返回新址）
//   记录索引 → ·0x4F57A0 扩一 → 重分配后新址回写 uArg2。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F6600(int *this, uint32_t *uArg2, uint32_t *uArg3, int nArg4)  // 80 字节元素单点插入（返回新址）
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 80 != 0 )  // 若 fld_e1 != 0 && (*(this + 2) - fld_e1) / 80 != 0
    v6 = ((int)uArg3 - fld_e1) / 80;
  else
    v6 = 0;
  sub_4F57A0(this, uArg3, 1u, nArg4);  // 80 字节元素向量插入（三路分支 + 1.5 倍扩容）
  *uArg2 = *(this + 1) + 80 * v6;  // *uArg2 写入 *(this + 1) + 80 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x4F6670 sub_4F6670 —— 124 字节元素填充构造（nArg2 个副本自 uArg3）
//   逐次 sub_4F5290 深拷贝构造（步长 31 双字），异常展开标记 v7。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F6670(uint32_t *uArg1, int nArg2, uint32_t *uArg3)  // 124 字节元素填充构造（nArg2 个副本自 uArg3）
{
  uint32_t *uArg12; // esi
  uint32_t *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg12 = uArg1;
  v6[4] = v6;
  v6[3] = uArg1;
  v7 = 0;
  while ( nArg2 != 0 )  // 当 nArg2 != 0 循环
  {
    LOBYTE(v7) = 1;
    if ( uArg12 != nullptr )  // 若 uArg12 非空
      result = sub_4F5290(uArg12, uArg3);  // 结果 = 124 字节元素深拷贝构造（串容器 + 4×4 双段）
    --nArg2;  // 自减nArg2
    uArg12 += 31;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F6700 sub_4F6700 —— 80 字节元素尾插（满则 4F6600）
//   有余量 sub_4F5190 就地构造 +80 递增，否则 ·0x4F6600 走插入路径。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F6700(int *this, int nArg2)  // 80 字节元素尾插（满则 4F6600）
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( fld_e1 != 0 )  // 若 fld_e1 != 0
    fld_e2 = (*(this + 2) - fld_e1) / 80;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 80 )  // 若 fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 80
    return sub_4F6600(this, &nArg2, (uint32_t *)*(this + 2), nArg2);  // 80 字节元素单点插入（返回新址）
  fld_e22 = *(this + 2);  // fld_e22 = this+2
  result = (uint32_t *)sub_4F5190(fld_e22, 1, nArg2);  // 结果 = 80 字节元素填充构造（nArg2 个）
  *(this + 2) = fld_e22 + 80;  // this+8 = fld_e22 + 80
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
char /*cdecl*/ sub_4F6790(int pArg1, unsigned int *pDwArg2, const char *ArgList)  // 函数: 释放后返回
{
  int v4; // eax
  int v5; // eax
  void **Block2; // eax
  int v7; // eax
  int v8; // eax
  int v9; // esi
  void **Block3; // eax
  int v11; // eax
  int v12; // eax
  void **Block4; // eax
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
  int dword_796E502; // [esp+9Ch] [ebp-10h]
  int v27; // [esp+A8h] [ebp-4h]
  float v28; // [esp+B8h] [ebp+Ch]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v25 = 15;
  Block[4] = nullptr;  // Block[4] = nullptr 空指针
  LOBYTE(Block[0]) = 0;
  v14 = pDwArg2[5];
  v27 = 0;
  if ( sub_40BF00((std::_String_base *)pDwArg2, 0, v14, "[HP MAX]", 8u) != 0  // 字符串 “[HP MAX]”
    && sub_40BF00((std::_String_base *)pDwArg2, 0, pDwArg2[5], "[MP MAX]", 8u) != 0  // 字符串 “[MP MAX]”
    && sub_40BF00((std::_String_base *)pDwArg2, 0, pDwArg2[5], "[physical attack]", 0x11u) != 0  // 字符串 “[physical attack]”
    && (uint8_t)sub_423300(pDwArg2, "[physical defense]") == 0 )  // 字符串 “[physical defense]”
  {
    if ( (uint8_t)sub_423300(pDwArg2, "[magical attack]") != 0  // 字符串 “[magical attack]”
      || (uint8_t)sub_423300(pDwArg2, "[magical defense]") != 0  // 字符串 “[magical defense]”
      || (uint8_t)sub_423300(pDwArg2, "[equipment physical attack]") != 0  // 字符串 “[equipment physical attack]”
      || (uint8_t)sub_423300(pDwArg2, "[equipment physical defense]") != 0  // 字符串 “[equipment physical defense]”
      || (uint8_t)sub_423300(pDwArg2, "[equipment magical attack]") != 0  // 字符串 “[equipment magical attack]”
      || (uint8_t)sub_423300(pDwArg2, "[equipment magical defense]") != 0  // 字符串 “[equipment magical defense]”
      || (uint8_t)sub_423300(pDwArg2, "[physical absolute damage]") != 0  // 字符串 “[physical absolute damage]”
      || (uint8_t)sub_423300(pDwArg2, "[physical damage reduce]") != 0 )  // 字符串 “[physical damage reduce]”
    {
      goto LABEL_115;  // 跳转 LABEL_115
    }
    if ( (uint8_t)sub_423300(pDwArg2, "[physical absolute defense]") != 0 )  // 字符串 “[physical absolute defense]”
    {
LABEL_125:                                   // ↑ 浮点属性路径：sub_442480 读 float → sub_432CF0 写入
      v17 = sub_442480(0);                       //   （研究 20 §12："[stuck]/暴击率等走浮点属性路径"）
      sub_432CF0(LODWORD(v17));  // cfloat 写入（float）
      goto LABEL_3;  // 跳转 LABEL_3
    }
    if ( (uint8_t)sub_423300(pDwArg2, "[magical absolute damage]") != 0  // 字符串 “[magical absolute damage]”
      || (uint8_t)sub_423300(pDwArg2, "[magical damage reduce]") != 0 )  // 字符串 “[magical damage reduce]”
    {
      goto LABEL_115;  // 跳转 LABEL_115
    }
    if ( (uint8_t)sub_423300(pDwArg2, "[magical absolute defense]") != 0 )  // 字符串 “[magical absolute defense]”
      goto LABEL_125;  // 跳转 LABEL_125
    if ( (uint8_t)sub_423300(pDwArg2, "[fire resistance]") != 0  // 字符串 “[fire resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[water resistance]") != 0  // 字符串 “[water resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[dark resistance]") != 0  // 字符串 “[dark resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[light resistance]") != 0  // 字符串 “[light resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[all elemental resistance]") != 0  // 字符串 “[all elemental resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[slow resistance]") != 0  // 字符串 “[slow resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[freeze resistance]") != 0  // 字符串 “[freeze resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[poison resistance]") != 0  // 字符串 “[poison resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[stun resistance]") != 0  // 字符串 “[stun resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[curse resistance]") != 0  // 字符串 “[curse resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[blind resistance]") != 0  // 字符串 “[blind resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[lightning resistance]") != 0  // 字符串 “[lightning resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[stone resistance]") != 0  // 字符串 “[stone resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[sleep resistance]") != 0  // 字符串 “[sleep resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[burn resistance]") != 0  // 字符串 “[burn resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[deadlystrike resistance]") != 0  // 字符串 “[deadlystrike resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[bleeding resistance]") != 0  // 字符串 “[bleeding resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[all activestatus resistance]") != 0  // 字符串 “[all activestatus resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[piercing resistance]") != 0  // 字符串 “[piercing resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[stuck resistance]") != 0  // 字符串 “[stuck resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[confuse resistance]") != 0  // 字符串 “[confuse resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[hold resistance]") != 0  // 字符串 “[hold resistance]”
      || (uint8_t)sub_423300(pDwArg2, "[inventory limit]") != 0  // 字符串 “[inventory limit]”
      || (uint8_t)sub_423300(pDwArg2, "[HP regen speed]") != 0  // 字符串 “[HP regen speed]”
      || (uint8_t)sub_423300(pDwArg2, "[MP regen speed]") != 0 )  // 字符串 “[MP regen speed]”
    {
      goto LABEL_115;  // 跳转 LABEL_115
    }
    if ( (uint8_t)sub_423300(pDwArg2, "[MP regen speed rate]") != 0 )  // 字符串 “[MP regen speed rate]”
      goto LABEL_125;  // 跳转 LABEL_125
    if ( (uint8_t)sub_423300(pDwArg2, "[move speed]") != 0  // 字符串 “[move speed]”
      || (uint8_t)sub_423300(pDwArg2, "[attack speed]") != 0  // 字符串 “[attack speed]”
      || (uint8_t)sub_423300(pDwArg2, "[cast speed]") != 0  // 字符串 “[cast speed]”
      || (uint8_t)sub_423300(pDwArg2, "[hit recovery]") != 0    // ★ §12 固定字段对之一（受方硬直恢复）
      || (uint8_t)sub_423300(pDwArg2, "[jump power]") != 0 )  // 字符串 “[jump power]”
    {
LABEL_115:                                 // ↑ 整型描述符路径：sub_4423D0 读 int → sub_41C150 写入
      v5 = sub_4423D0(0);                      //   （研究 20 §12："[hit recovery]/[stuck resistance] 等
      sub_41C150(v5);                          //    走通用整型描述符"；全段落类标签共用此出口，
      goto LABEL_3;                            //    故此处注释代表其上方全部抗性/速度/上限标签）
    }
    if ( (uint8_t)sub_423300(pDwArg2, "[elemental property]") != 0 )  // 字符串 “[elemental property]”
    {
      sub_443370();  // 脚本 token 取串（第三入口）
      *(uint32_t *)(pArg1 + 772) = sub_442710(Block);   // +772 [elemental property] 属性（名字查表）
    }
    else
    {
      if ( (uint8_t)sub_423300(pDwArg2, "[active status]") != 0 )  // 字符串 “[active status]”
      {
        sub_443370();  // 脚本 token 取串（第三入口）
        // +776 [active status] 状态槽 —— 17 槽枚举，与 研究 20 §10 定案逐一吻合：
        if ( (uint8_t)sub_423300(v23, "[none]") != 0 )  // 字符串 “[none]”
        {
          *(uint32_t *)(pArg1 + 776) = 17;         // 17 = none
        }
        else if ( (uint8_t)sub_423300(v23, "[slow]") != 0 )  // 字符串 “[slow]”
        {
          *(uint32_t *)(pArg1 + 776) = 0;          // 0 = slow
        }
        else if ( (uint8_t)sub_423300(v23, "[freeze]") != 0 )  // 字符串 “[freeze]”
        {
          *(uint32_t *)(pArg1 + 776) = 1;  // pArg1+776 = 1
        }
        else if ( (uint8_t)sub_423300(v23, "[poison]") != 0 )  // 字符串 “[poison]”
        {
          *(uint32_t *)(pArg1 + 776) = 2;  // pArg1+776 = 2
        }
        else if ( (uint8_t)sub_423300(v23, "[stun]") != 0 )  // 字符串 “[stun]”
        {
          *(uint32_t *)(pArg1 + 776) = 3;  // pArg1+776 = 3
        }
        else if ( (uint8_t)sub_423300(v23, "[curse]") != 0 )  // 字符串 “[curse]”
        {
          *(uint32_t *)(pArg1 + 776) = 4;  // pArg1+776 = 4
        }
        else if ( (uint8_t)sub_423300(v23, "[blind]") != 0 )  // 字符串 “[blind]”
        {
          *(uint32_t *)(pArg1 + 776) = 5;  // pArg1+776 = 5
        }
        else if ( (uint8_t)sub_423300(v23, "[lightning]") != 0 )  // 字符串 “[lightning]”
        {
          *(uint32_t *)(pArg1 + 776) = 6;  // pArg1+776 = 6
        }
        else if ( (uint8_t)sub_423300(v23, "[stone]") != 0 )  // 字符串 “[stone]”
        {
          *(uint32_t *)(pArg1 + 776) = 7;  // pArg1+776 = 7
        }
        else if ( (uint8_t)sub_423300(v23, "[sleep]") != 0 )  // 字符串 “[sleep]”
        {
          *(uint32_t *)(pArg1 + 776) = 8;  // pArg1+776 = 8
        }
        else if ( (uint8_t)sub_423300(v23, "[burn]") != 0 )  // 字符串 “[burn]”
        {
          *(uint32_t *)(pArg1 + 776) = 9;  // pArg1+776 = 9
        }
        else if ( (uint8_t)sub_423300(v23, "[deadlystrike]") != 0 )  // 字符串 “[deadlystrike]”
        {
          *(uint32_t *)(pArg1 + 776) = 10;  // pArg1+776 = 10
        }
        else if ( (uint8_t)sub_423300(v23, "[bleeding]") != 0 )  // 字符串 “[bleeding]”
        {
          *(uint32_t *)(pArg1 + 776) = 11;  // pArg1+776 = 11
        }
        else if ( (uint8_t)sub_423300(v23, "[haste]") != 0 )  // 字符串 “[haste]”
        {
          *(uint32_t *)(pArg1 + 776) = 12;  // pArg1+776 = 12
        }
        else if ( (uint8_t)sub_423300(v23, "[bless]") != 0 )  // 字符串 “[bless]”
        {
          *(uint32_t *)(pArg1 + 776) = 13;  // pArg1+776 = 13
        }
        else if ( (uint8_t)sub_423300(v23, "[element]") != 0 )  // 字符串 “[element]”
        {
          *(uint32_t *)(pArg1 + 776) = 14;  // pArg1+776 = 14
        }
        else if ( (uint8_t)sub_423300(v23, "[hold]") != 0 )  // 字符串 “[hold]”
        {
          *(uint32_t *)(pArg1 + 776) = 16;  // pArg1+776 = 16
        }
        else if ( (uint8_t)sub_423300(v23, "[confuse]") != 0 )  // 字符串 “[confuse]”
        {
          *(uint32_t *)(pArg1 + 776) = 15;  // pArg1+776 = 15
        }
        v16 = sub_442480(0);  // 结果 = 脚本 token 数值解析（double 版）
        sub_432CF0(LODWORD(v16));  // cfloat 写入（float）
        v4 = sub_4423D0(0);  // 调 sub_4423D0
        sub_41C150(v4);  // crypt4byte 初始化转发（0x41A590）
        goto LABEL_3;  // 跳转 LABEL_3
      }
      if ( (uint8_t)sub_423300(pDwArg2, "[push aside]") != 0 || (uint8_t)sub_423300(pDwArg2, "[lift up]") != 0 )  // 字符串 “[push aside]”
        goto LABEL_115;  // 跳转 LABEL_115
      if ( (uint8_t)sub_423300(pDwArg2, "[physical critical hit]") != 0  // 字符串 “[physical critical hit]”
        || (uint8_t)sub_423300(pDwArg2, "[magical critical hit]") != 0  // 字符串 “[magical critical hit]”
        || (uint8_t)sub_423300(pDwArg2, "[stuck]") != 0 )  // 字符串 “[stuck]”
      {
        goto LABEL_125;  // 跳转 LABEL_125
      }
      if ( (uint8_t)sub_423300(pDwArg2, "[ignore defense]") != 0 )  // 字符串 “[ignore defense]”
      {
        *(uint8_t *)(pArg1 + 850) = sub_4423D0(0) != 0;  // pArg1+850 = sub_4423D0(0) != 0
        goto LABEL_3;  // 跳转 LABEL_3
      }
      if ( (uint8_t)sub_423300(pDwArg2, "[human damage rate]") != 0  // 字符串 “[human damage rate]”
        || (uint8_t)sub_423300(pDwArg2, "[fort damage rate]") != 0 )  // 字符串 “[fort damage rate]”
      {
        goto LABEL_125;  // 跳转 LABEL_125
      }
      if ( (uint8_t)sub_423300(pDwArg2, "[HP drain]") != 0 )  // 字符串 “[HP drain]”
      {
        *(uint8_t *)(pArg1 + 879) = sub_4423D0(0) != 0;  // pArg1+879 = sub_4423D0(0) != 0
      }
      else if ( (uint8_t)sub_423300(pDwArg2, "[MP drain]") != 0 )  // 字符串 “[MP drain]”
      {
        *(uint8_t *)(pArg1 + 880) = sub_4423D0(0) != 0;  // pArg1+880 = sub_4423D0(0) != 0
      }
      else if ( (uint8_t)sub_423300(pDwArg2, "[skill levelup]") != 0 )  // 字符串 “[skill levelup]”
      {
        sub_434140(pArg1 + 884);  // 条目向量销毁（32B 步进）
        sub_4F4B60(&v19);  // clong 双槽快速构造（类型字 4）
        LOBYTE(v27) = 1;
        while ( sub_443370() != 0 )  // 当 sub_443370() != 0 循环
        {
          sub_4E99F0(&v19);  // clong 初始化（*this = 4；+4 = a2；+18 = 0）
          if ( (uint8_t)sub_423300(v23, "[common]") != 0 )  // 字符串 “[common]”
          {
            v19 = 4;
          }
          else
          {
            Block2 = (void **)Block[0];
            if ( v25 < 0x10 )  // 若 v25 < 0x10
              Block2 = Block;
            v19 = sub_4426A0(Block2);  // 【职业标签→索引（[swordman]/[fighter]/[gunner]/[mag…】
          }
          v7 = sub_4423D0(0);  // 调 sub_4423D0
          sub_41A590(v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          v8 = sub_4423D0(0);  // 调 sub_4423D0
          sub_41A590(v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          sub_4EE120(&v19);  // 32B 条目尾部推入
        }
        LOBYTE(v27) = 0;
        sub_432DC0(&v19);  // clong 双槽析构
      }
      else
      {
        if ( (uint8_t)sub_423300(pDwArg2, "[avatar select ability]") == 0 )  // 字符串 “[avatar select ability]”
        {
LABEL_165:
          sub_501490(v23);  // 调 sub_501490
          return 0;
        }
        sub_436840(pArg1 + 916);  // 80 字节条目向量销毁
        if ( sub_443370() != 0 )  // 脚本 token 取串（第三入口）
        {
          while ( 2 )  // 当 2 循环
          {
            sub_4F5220(&v20);  // cfloat 复合对象构造（clong×2 + 串槽 + 收尾）
            LOBYTE(v27) = 2;
            v9 = 0;
            while ( (uint8_t)sub_423300(v23, off_791E28[v9]) == 0 )  // 当 (uint8_t)sub_423300(v23, off_791E28[v9]) == 0 循环
            {
              if ( ++v9 >= 44 )  // 若 ++v9 >= 44
                goto LABEL_158;  // 跳转 LABEL_158
            }
            v20 = v9;
            if ( v9 == 43 )  // 若 v9 == 43
            {
              v21 = 0;
              sub_443370();  // 脚本 token 取串（第三入口）
              if ( (uint8_t)sub_423300(v23, "[common]") != 0 )  // 字符串 “[common]”
              {
                v22 = 4;
              }
              else
              {
                Block3 = (void **)Block[0];
                if ( v25 < 0x10 )  // 若 v25 < 0x10
                  Block3 = Block;
                v11 = sub_4426A0(Block3);  // 【职业标签→索引（[swordman]/[fighter]/[gunner]/[mag…】
                if ( v11 == 4 )  // 若 v11 == 4
                {
                  Block4 = (void **)Block[0];
                  if ( v25 < 0x10 )  // 若 v25 < 0x10
                    Block4 = Block;
                  off_77F3FC("ImportEquipmentScript - file %s, invalid job tag %s", ArgList, (const char *)Block4);  // 字符串 “ImportEquipmentScript - file %s, invalid job”
                  LOBYTE(v27) = 0;
                  sub_433D10(&v20);  // 条目析构（串与三防篡改槽）
                  goto LABEL_165;  // 跳转 LABEL_165
                }
                v22 = v11;
              }
              v12 = sub_4423D0(0);  // 调 sub_4423D0
              sub_41A590(v12);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
              v18 = sub_4423D0(0);  // 调 sub_4423D0
              sub_41A590(v18);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
            }
            else
            {
              sub_443370();  // 脚本 token 取串（第三入口）
              if ( (uint8_t)sub_423300(v23, &asc_6FA81C) != 0 )  // 串首比较判定（相等）
              {
                v21 = 0;
              }
              else if ( (uint8_t)sub_423300(v23, "*") != 0 )  // 串首比较判定（相等）
              {
                v21 = 1;
              }
              v28 = sub_442480(0);  // 结果 = 脚本 token 数值解析（double 版）
              sub_41A590(LODWORD(v28));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
            }
LABEL_158:
            if ( (unsigned int)sub_4EAF60(pArg1 + 916) < 0x3C )  // 元素个数 =（+8 − +4）/80
              sub_4F6700(&v20);  // 80 字节元素尾插（满则 4F6600）
            LOBYTE(v27) = 0;
            sub_433D10(&v20);  // 条目析构（串与三防篡改槽）
            if ( sub_443370() != 0 )  // 脚本 token 取串（第三入口）
              continue;
            break;
          }
        }
      }
    }
  }
  else
  {
    v15 = sub_4423D0(0);  // 调 sub_4423D0
    sub_41A590(v15);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
LABEL_3:
  if ( v25 >= 0x10 )  // 若 v25 >= 0x10
    j__free(Block[0]);  // 调 j__free
  return 1;
}


// ------------------------------------------------------------
// 0x4F7800 sub_4F7800 —— 124 字节元素填充 + 返回尾址（组合器）
//   sub_4F6670 填充后返回 &pArg1[31×nArg2]（31 双字 = 124 字节）。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4F7800(uint32_t *pArg1, int nArg2, uint32_t *uArg3)  // 124 字节元素填充 + 返回尾址（组合器）
{
  sub_4F6670(pArg1, nArg2, uArg3);  // 124 字节元素填充构造（nArg2 个副本自 uArg3）
  return &pArg1[31 * nArg2];
}



// ------------------------------------------------------------
// 0x4F7830 sub_4F7830 —— 124 字节元素向量插入（三路分支 + 1.5 倍扩容）
//   就地 sub_4F5B00/sub_4F5AE0/sub_4F5AB0；重建经 operator new + sub_4F6670/sub_4F7800，
//   旧段 sub_4388A0 析构；超限 sub_434730；首元素 temp 经 ·0x4F5290 构造。
// ------------------------------------------------------------
void /*thiscall*/ sub_4F7830(int *this, char *pszArg2, unsigned int uArg3, uint32_t *uArg4)  // 函数: 124 字节元素向量插入（三路分支 + 1.5 倍扩容）
{
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v14; // edi
  int fld_e14; // eax
  uint32_t *fld_e23; // ecx
  int fld_e26; // edx
  uint32_t *fld_e12; // [esp-18h] [ebp-B8h]
  int fld_e25; // [esp-Ch] [ebp-ACh]
  unsigned int fld_e24; // [esp-8h] [ebp-A8h]
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
  sub_4F5290(v23, uArg4);  // 124 字节元素深拷贝构造（串容器 + 4×4 双段）
  fld_e1 = *(this + 1);  // fld_e1 = this+1
  fld_e3 = 0;
  v26 = 0;
  if ( fld_e1 != 0 )  // 若 fld_e1 != 0
    fld_e3 = (*(this + 3) - fld_e1) / 124;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e2 = (*(this + 2) - *(this + 1)) / 124;
    else
      fld_e2 = 0;
    if ( 34636833 - fld_e2 < uArg3 )  // 若 34636833 - fld_e2 < uArg3
      sub_434730(this);  // vector 超长抛 length_error
    if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
      fld_e22 = (*(this + 2) - *(this + 1)) / 124;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )  // 若 fld_e3 >= uArg3 + fld_e22
    {
      fld_e23 = (uint32_t *)*(this + 2);
      Block = fld_e23;
      if ( ((char *)fld_e23 - pszArg2) / 124 >= uArg3 )  // 若 ((char *)fld_e23 - pszArg2) / 124 >= uArg3
      {
        v27 = &fld_e23[-31 * uArg3];
        *(this + 2) = (int)sub_4F5B00(v27, fld_e23, fld_e23);  // 124 字节元素反向搬移深拷贝
        sub_4F5AE0(pszArg2, v27, Block);  // 薄封装（转 4F55A0 反向搬移）
        sub_4F5AB0(pszArg2, &pszArg2[124 * uArg3], v23);  // 124 字节元素正向批量赋值（同源复制）
      }
      else
      {
        sub_4F5B00(pszArg2, fld_e23, &pszArg2[124 * uArg3]);  // 124 字节元素反向搬移深拷贝
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 124;
        fld_e25 = *(this + 2);  // fld_e25 = this+2
        LOBYTE(v26) = 3;
        sub_4F7800(fld_e25, fld_e24, v23);  // 124 字节元素填充 + 返回尾址（组合器）
        fld_e26 = 124 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8 = fld_e26
        v26 = 0;
        sub_4F5AB0(pszArg2, fld_e26 - 124 * uArg3, v23);  // 124 字节元素正向批量赋值（同源复制）
      }
    }
    else
    {
      if ( 34636833 - (fld_e3 >> 1) >= fld_e3 )  // 若 34636833 - (fld_e3 >> 1) >= fld_e3
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        fld_e27 = (*(this + 2) - *(this + 1)) / 124;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )  // 若 v10 < uArg3 + fld_e27
        v10 = uArg3 + sub_4EAF80(this);  // 结果 = 元素个数 =（+8 − +4）/124
      v29 = 124 * v10;
      pMem = (char *)operator new(124 * v10);
      fld_e12 = (uint32_t *)*(this + 1);
      Block = pMem;
      LOBYTE(v26) = 1;
      v28 = sub_4F5B00(fld_e12, pszArg2, pMem);  // 结果 = 124 字节元素反向搬移深拷贝
      sub_4F6670(v28, uArg3, v23);  // 124 字节元素填充构造（nArg2 个副本自 uArg3）
      sub_4F5B00(pszArg2, (uint32_t *)*(this + 2), &v28[31 * uArg3]);  // 124 字节元素反向搬移深拷贝
      fld_e13 = *(this + 1);  // fld_e13 = this+1
      v26 = 0;
      if ( fld_e13 != 0 )  // 若 fld_e13 != 0
        fld_e13 = (*(this + 2) - fld_e13) / 124;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);  // fld_e14 = this+1
      if ( fld_e14 != 0 )  // 若 fld_e14 != 0
      {
        sub_4388A0(fld_e14, *(this + 2));  // 124 字节条目区间析构
        j__free((void *)*(this + 1));  // 调 j__free
      }
      *(this + 3) = (int)&pMem[v29];  // this+12 = (int)&pMem[v29]
      *(this + 2) = (int)&pMem[124 * v14];  // this+8 = (int)&pMem[124 * v14]
      *(this + 1) = (int)pMem;  // this+4 = (int)pMem
    }
  }
  v26 = -1;
  sub_4347B0(v23);  // 124 字节条目析构
}


// ------------------------------------------------------------
// 0x4F7B60 sub_4F7B60 —— 124 字节元素单点插入（返回新址）
//   记录索引 → ·0x4F7830 扩一 → 新址回写 uArg2。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F7B60(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *uArg4)  // 124 字节元素单点插入（返回新址）
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 124 != 0 )  // 若 fld_e1 != 0 && (*(this + 2) - fld_e1) / 124 != 0
    v6 = (int)&pszArg3[-fld_e1] / 124;
  else
    v6 = 0;
  sub_4F7830(this, pszArg3, 1u, uArg4);  // 124 字节元素向量插入（三路分支 + 1.5 倍扩容）
  *uArg2 = *(this + 1) + 124 * v6;  // *uArg2 写入 *(this + 1) + 124 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x4F7BD0 sub_4F7BD0 —— 124 字节元素尾插（满则 4F7B60）
//   有余量 sub_4F6670 就地构造 +124 递增，否则 ·0x4F7B60。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F7BD0(int this, uint32_t *uArg2)  // 124 字节元素尾插（满则 4F7B60）
{
  int fld_4; // ebx
  unsigned int fld_8; // esi
  uint32_t *fld_82; // esi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 124;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 124 )  // 若 fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 124
    return sub_4F7B60((int *)this, &uArg2, *(char **)(this + 8), uArg2);  // 124 字节元素单点插入（返回新址）
  fld_82 = *(uint32_t **)(this + 8);
  result = sub_4F6670(fld_82, 1, uArg2);  // 结果 = 124 字节元素填充构造（nArg2 个副本自 uArg3）
  *(uint32_t *)(this + 8) = fld_82 + 31;  // this+8 = fld_82 + 31
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
char /*cdecl*/ sub_4F7C60(int pArg1, char *ArgList)  // 函数: 释放后返回
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
  int dword_796E502; // [esp+D0h] [ebp-10h]
  int v58; // [esp+DCh] [ebp-4h]

  v2 = ArgList;
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = sub_442A10((char)&unk_9B6A60, (int)ArgList);  // 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result != 0 )  // 若 result != 0
  {
    sub_4393E0((char *)pArg1);  // 装备数据对象复位（0x85C）
    v52 = 15;
    v51[4] = nullptr;  // v51[4] = nullptr 空指针
    LOBYTE(v51[0]) = 0;
    j = (void **)ArgList;
    v58 = 0;
    sub_443300((int)&v50, "%s%s", (char)&unk_9B6A60);  // 字符串 “%s%s”
    v4 = (void **)v51[0];
    if ( v52 < 0x10 )  // 若 v52 < 0x10
      v4 = v51;
    sub_41BFE0((void **)(pArg1 + 1088), (const char *)v4);  // 调 驻留字符串设置
    v56 = 15;
    v55 = 0;
    LOBYTE(v54) = 0;
    LOBYTE(v58) = 1;
    v49 = nullptr;  // v49 = nullptr 空指针
    sub_41BFE0(&v49, szPassword);  // 调 驻留字符串设置
    LOBYTE(v58) = 2;
    sub_4F55E0(&v17);  // 物品解析结果块构造
    LOBYTE(v58) = 3;
    v48 = 0;
    for ( i = pArg1 + 104; (uint8_t)sub_443430(&v53) != 0; v2 = ArgList )  // 循环：i = pArg1 + 104; (uint8_t)sub_443430(&v53) != 0; v2 = ArgLis
    {
      if ( (uint8_t)sub_442BC0(&v53) != 0 )  // 国家码标签配对校验（bool）
        off_77F3FC((char *)&byte_6FA9F8, v2);
      if ( sub_40BF00((std::_String_base *)&v53, 0, v55, "[name]", 6u) != 0 )  // 字符串 “[name]”
      {
        if ( sub_40BF00((std::_String_base *)&v53, 0, v55, "[name2]", 7u) != 0 )  // 字符串 “[name2]”
        {
          if ( sub_40BF00((std::_String_base *)&v53, 0, v55, "[explain]", 9u) != 0 )  // 字符串 “[explain]”
          {
            if ( sub_40BF00((std::_String_base *)&v53, 0, v55, "[flavor text]", 0xDu) != 0 )  // 字符串 “[flavor text]”
            {
              if ( (uint8_t)sub_423300(&v53, "[fullset explain]") != 0 )  // 字符串 “[fullset explain]”
              {
                j = (void **)(pArg1 + 2132);
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
              }
              else if ( (uint8_t)sub_423300(&v53, "[set name]") != 0 )  // 字符串 “[set name]”
              {
                j = (void **)(pArg1 + 1104);
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
              }
              else if ( (uint8_t)sub_423300(&v53, "[grade]") != 0 )  // 字符串 “[grade]”
              {
                *(uint32_t *)(pArg1 + 4) = sub_4423D0(nullptr);  // pArg1+4 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[attach type]") != 0 )  // 字符串 “[attach type]”
              {
                j = &v49;
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                if ( sub_43BCF0(&v49, "[free]") )  // 字符串 “[free]”
                {
                  *(uint32_t *)(pArg1 + 8) = 0;  // pArg1+8 = 0
                }
                else if ( sub_43BCF0(&v49, "[trade]") )  // 字符串 “[trade]”
                {
                  *(uint32_t *)(pArg1 + 8) = 1;  // pArg1+8 = 1
                }
                else if ( sub_43BCF0(&v49, "[trade delete]") )  // 字符串 “[trade delete]”
                {
                  *(uint32_t *)(pArg1 + 8) = 2;  // pArg1+8 = 2
                }
                else if ( sub_43BCF0(&v49, "[sealing]") )  // 字符串 “[sealing]”
                {
                  *(uint32_t *)(pArg1 + 8) = 3;  // pArg1+8 = 3
                }
              }
              else if ( (uint8_t)sub_423300(&v53, "[creation rate]") != 0 )  // 字符串 “[creation rate]”
              {
                *(uint32_t *)(pArg1 + 12) = sub_4423D0(nullptr);  // pArg1+12 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[rarity]") != 0 )  // 字符串 “[rarity]”
              {
                *(uint32_t *)(pArg1 + 16) = sub_4423D0(nullptr);  // pArg1+16 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[weight]") != 0 )  // 字符串 “[weight]”
              {
                *(uint32_t *)(pArg1 + 40) = sub_4423D0(nullptr);  // pArg1+40 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[icon]") != 0 )  // 字符串 “[icon]”
              {
                j = (void **)(pArg1 + 60);
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                *(uint32_t *)(pArg1 + 64) = sub_4423D0(nullptr);  // pArg1+64 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[field image]") != 0 )  // 字符串 “[field image]”
              {
                j = (void **)(pArg1 + 68);
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                *(uint32_t *)(pArg1 + 72) = sub_4423D0(nullptr);  // pArg1+72 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[custom animation]") != 0 )  // 字符串 “[custom animation]”
              {
                sub_4017E0(pArg1 + 76);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                for ( j = &v49; sub_442E10() != 0; j = &v49 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                  sub_420BB0(&v49);  // vector push_back（4 字节元素）
              }
              else if ( (uint8_t)sub_423300(&v53, "[usable job]") != 0 )  // 字符串 “[usable job]”
              {
                for ( j = &v49; sub_442E10() != 0; j = &v49 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                {
                  v5 = sub_41ACF0(&v49);  // 结果 = 驻留串句柄 → 字符串指针
                  v6 = sub_4426A0(v5);  // 【职业标签→索引（[swordman]/[fighter]/[gunner]/[mag…】
                  if ( v6 == 4 )  // 若 v6 == 4
                  {
                    *(uint32_t *)(pArg1 + 44) = 16843009;  // pArg1+44 = 16843009
                    *(uint8_t *)(pArg1 + 2108) = 1;  // pArg1+2108 = 1
                  }
                  else
                  {
                    *(uint8_t *)(pArg1 + v6 + 44) = 1;
                  }
                }
              }
              else if ( (uint8_t)sub_423300(&v53, "[minimum level]") != 0 )  // 字符串 “[minimum level]”
              {
                *(uint32_t *)(pArg1 + 48) = sub_4423D0(nullptr);  // pArg1+48 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[required skill]") != 0 )  // 字符串 “[required skill]”
              {
                *(uint32_t *)(pArg1 + 52) = sub_4423D0(nullptr);  // pArg1+52 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[cool time]") != 0 )  // 字符串 “[cool time]”
              {
                *(uint32_t *)(pArg1 + 56) = sub_4423D0(nullptr);  // pArg1+56 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[equipment type]") != 0 )  // 字符串 “[equipment type]”
              {
                j = &v49;
                sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                if ( sub_43BCF0(&v49, "[hat avatar]") )  // 字符串 “[hat avatar]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 0;  // pArg1+92 = 0
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[hair avatar]") )  // 字符串 “[hair avatar]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 1;  // pArg1+92 = 1
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[face avatar]") )  // 字符串 “[face avatar]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 2;  // pArg1+92 = 2
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[coat avatar]") )  // 字符串 “[coat avatar]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 3;  // pArg1+92 = 3
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[pants avatar]") )  // 字符串 “[pants avatar]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 4;  // pArg1+92 = 4
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[shoes avatar]") )  // 字符串 “[shoes avatar]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 5;  // pArg1+92 = 5
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[breast avatar]") )  // 字符串 “[breast avatar]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 6;  // pArg1+92 = 6
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[waist avatar]") )  // 字符串 “[waist avatar]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 7;  // pArg1+92 = 7
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[weapon]") )  // 字符串 “[weapon]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 8;  // pArg1+92 = 8
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[title name]") )  // 字符串 “[title name]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 9;  // pArg1+92 = 9
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[coat]") )  // 字符串 “[coat]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 10;  // pArg1+92 = 10
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[shoulder]") )  // 字符串 “[shoulder]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 11;  // pArg1+92 = 11
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[pants]") )  // 字符串 “[pants]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 12;  // pArg1+92 = 12
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[shoes]") )  // 字符串 “[shoes]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 13;  // pArg1+92 = 13
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[waist]") )  // 字符串 “[waist]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 14;  // pArg1+92 = 14
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[amulet]") )  // 字符串 “[amulet]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 15;  // pArg1+92 = 15
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else if ( sub_43BCF0(&v49, "[wrist]") )  // 字符串 “[wrist]”
                {
                  j = nullptr;  // j = nullptr 空指针
                  *(uint32_t *)(pArg1 + 92) = 16;  // pArg1+92 = 16
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(j);  // pArg1+2112 = sub_4423D0(j)
                }
                else
                {
                  if ( sub_43BCF0(&v49, "[ring]") )  // 字符串 “[ring]”
                    *(uint32_t *)(pArg1 + 92) = 17;  // pArg1+92 = 17
                  *(uint32_t *)(pArg1 + 2112) = sub_4423D0(nullptr);  // pArg1+2112 = sub_4423D0(nullptr)
                }
              }
              else if ( (uint8_t)sub_423300(&v53, "[sub type]") != 0 )  // 字符串 “[sub type]”
              {
                *(uint32_t *)(pArg1 + 96) = sub_4423D0(nullptr);  // pArg1+96 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[durability]") != 0 )  // 字符串 “[durability]”
              {
                *(uint32_t *)(pArg1 + 100) = sub_4423D0(nullptr);  // pArg1+100 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[price]") != 0 )  // 字符串 “[price]”
              {
                *(uint32_t *)(pArg1 + 20) = sub_4423D0(nullptr);  // pArg1+20 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[value]") != 0 )  // 字符串 “[value]”
              {
                *(uint32_t *)(pArg1 + 36) = sub_4423D0(nullptr);  // pArg1+36 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[finish point price]") != 0 )  // 字符串 “[finish point price]”
              {
                *(uint32_t *)(pArg1 + 32) = sub_4423D0(nullptr);  // pArg1+32 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[cash]") != 0 )  // 字符串 “[cash]”
              {
                *(uint32_t *)(pArg1 + 24) = sub_4423D0(nullptr);  // pArg1+24 = sub_4423D0(nullptr)
              }
              else if ( (uint8_t)sub_423300(&v53, "[medal]") != 0 )  // 字符串 “[medal]”
              {
                *(uint32_t *)(pArg1 + 28) = sub_4423D0(nullptr);  // pArg1+28 = sub_4423D0(nullptr)
              }
              else if ( sub_4F6790(i, (unsigned int *)&v53, v2) == 0 )  // 否则若 sub_4F6790(i, (unsigned int *)&v53, v2) == 0
              {
                if ( (uint8_t)sub_423300(&v53, "[LAYER]") != 0 )  // 字符串 “[LAYER]”
                {
                  if ( v17 != 0 )  // 若 v17 != 0
                    sub_4F7BD0(&v17);  // 124 字节元素尾插（满则 4F7B60）
                  sub_4F4F30(&v17);  // 80 字节元素数组销毁（串槽清空 + 两段堆回收）
                  v17 = sub_4423D0(nullptr);  // 调 sub_4423D0
                }
                else if ( (uint8_t)sub_423300(&v53, "[waiting motion]") != 0 )  // 字符串 “[waiting motion]”
                {
                  j = (void **)&v18;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[move motion]") != 0 )  // 字符串 “[move motion]”
                {
                  j = (void **)&v19;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[sit motion]") != 0 )  // 字符串 “[sit motion]”
                {
                  j = (void **)&v20;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[damage motion 1]") != 0 )  // 字符串 “[damage motion 1]”
                {
                  j = (void **)&v21;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[damage motion 2]") != 0 )  // 字符串 “[damage motion 2]”
                {
                  j = (void **)&v22;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[down motion]") != 0 )  // 字符串 “[down motion]”
                {
                  j = (void **)&v23;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[overturn motion]") != 0 )  // 字符串 “[overturn motion]”
                {
                  j = (void **)&v24;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[jump motion]") != 0 )  // 字符串 “[jump motion]”
                {
                  j = (void **)&v25;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[jumpattack motion]") != 0 )  // 字符串 “[jumpattack motion]”
                {
                  j = (void **)&v26;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[rest motion]") != 0 )  // 字符串 “[rest motion]”
                {
                  j = (void **)&v27;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 1-1]") != 0 )  // 字符串 “[throw motion 1-1]”
                {
                  j = (void **)&v28;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 1-2]") != 0 )  // 字符串 “[throw motion 1-2]”
                {
                  j = (void **)&v32;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 2-1]") != 0 )  // 字符串 “[throw motion 2-1]”
                {
                  j = (void **)&v29;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 2-2]") != 0 )  // 字符串 “[throw motion 2-2]”
                {
                  j = (void **)&v33;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 3-1]") != 0 )  // 字符串 “[throw motion 3-1]”
                {
                  j = (void **)&v30;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 3-2]") != 0 )  // 字符串 “[throw motion 3-2]”
                {
                  j = (void **)&v34;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 4-1]") != 0 )  // 字符串 “[throw motion 4-1]”
                {
                  j = (void **)&v31;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[throw motion 4-2]") != 0 )  // 字符串 “[throw motion 4-2]”
                {
                  j = (void **)&v35;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[dash motion]") != 0 )  // 字符串 “[dash motion]”
                {
                  j = (void **)&v36;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[dashattack motion]") != 0 )  // 字符串 “[dashattack motion]”
                {
                  j = (void **)&v37;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[getitem motion]") != 0 )  // 字符串 “[getitem motion]”
                {
                  j = (void **)&v38;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[buff motion]") != 0 )  // 字符串 “[buff motion]”
                {
                  j = (void **)&v39;
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[attack motion]") != 0 )  // 字符串 “[attack motion]”
                {
                  v7 = (void **)Block;
                  if ( Block != nullptr )  // 若 Block 非空
                  {
                    v8 = v41;
                    if ( Block != v41 )  // 若 Block != v41
                    {
                      do
                        sub_41B010(v7++);  // 驻留句柄析构（引用计数减到 0 释放）
                      while ( v7 != v8 );  // 当 v7 != v8 循环
                      v7 = (void **)Block;
                    }
                    j__free(v7);  // 调 j__free
                  }
                  j = &v49;
                  Block = nullptr;  // Block = nullptr 空指针
                  v41 = nullptr;  // v41 = nullptr 空指针
                  for ( k = 0; sub_442E10() != 0; j = &v49 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    sub_420BB0(&v49);  // vector push_back（4 字节元素）
                }
                else if ( (uint8_t)sub_423300(&v53, "[etc motion]") != 0 )  // 字符串 “[etc motion]”
                {
                  v9 = (void **)v43;
                  if ( v43 != nullptr )  // 若 v43 非空
                  {
                    v10 = v44;
                    if ( v43 != v44 )  // 若 v43 != v44
                    {
                      do
                        sub_41B010(v9++);  // 驻留句柄析构（引用计数减到 0 释放）
                      while ( v9 != v10 );  // 当 v9 != v10 循环
                      v9 = (void **)v43;
                    }
                    j__free(v9);  // 调 j__free
                  }
                  j = &v49;
                  v43 = nullptr;  // v43 = nullptr 空指针
                  v44 = nullptr;  // v44 = nullptr 空指针
                  for ( m = 0; sub_442E10() != 0; j = &v49 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    sub_420BB0(&v49);  // vector push_back（4 字节元素）
                }
                else if ( (uint8_t)sub_423300(&v53, "[move wav]") != 0 )  // 字符串 “[move wav]”
                {
                  j = (void **)(pArg1 + 1068);
                  sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
                }
                else if ( (uint8_t)sub_423300(&v53, "[custom wav]") != 0 )  // 字符串 “[custom wav]”
                {
                  sub_4017E0(pArg1 + 1072);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                  for ( j = &v49; sub_442E10() != 0; j = &v49 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    sub_420BB0(&v49);  // vector push_back（4 字节元素）
                }
                else if ( (uint8_t)sub_423300(&v53, "[variation]") != 0 )  // 字符串 “[variation]”
                {
                  v11 = sub_4423D0(nullptr);  // 调 sub_4423D0
                  v15 = nullptr;  // v15 = nullptr 空指针
                  *(uint32_t *)(pArg1 + 1092) = v11;  // pArg1+1092 = v11
                  *(uint32_t *)(pArg1 + 1096) = sub_4423D0(v15);  // pArg1+1096 = sub_4423D0(v15)
                  *(uint8_t *)(pArg1 + 1100) = 1;  // pArg1+1100 = 1
                }
                else if ( (uint8_t)sub_423300(&v53, "[set item]") != 0 )  // 字符串 “[set item]”
                {
                  sub_5E5260((void **)(pArg1 + 1108));  // 调 sub_5E5260
                  for ( n = (void **)sub_4423D0(&v48); v48 != 0; n = (void **)sub_4423D0(&v48) )  // 循环：n = (void **)sub_4423D0(&v48); v48 != 0; n = (void **)sub_44
                    sub_431230(pArg1 + 1108, &n);  // uint32 vector push_back
                }
                else if ( (uint8_t)sub_423300(&v53, "[set ability]") != 0 )  // 字符串 “[set ability]”
                {
                  i = pArg1 + 1124;
                }
                else if ( (uint8_t)sub_423300(&v53, "[set item master]") != 0 )  // 字符串 “[set item master]”
                {
                  *(uint32_t *)(pArg1 + 2072) = sub_4423D0(nullptr);  // pArg1+2072 = sub_4423D0(nullptr)
                }
                else if ( (uint8_t)sub_423300(&v53, "[int data]") != 0 )  // 字符串 “[int data]”
                {
                  sub_5E5260((void **)(pArg1 + 2076));  // 调 sub_5E5260
                  for ( n = (void **)sub_4423D0(&v48); v48 != 0; n = (void **)sub_4423D0(&v48) )  // 循环：n = (void **)sub_4423D0(&v48); v48 != 0; n = (void **)sub_44
                    sub_431230(pArg1 + 2076, &n);  // uint32 vector push_back
                }
                else if ( (uint8_t)sub_423300(&v53, "[string data]") != 0 )  // 字符串 “[string data]”
                {
                  sub_4017E0(pArg1 + 2092);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
                  for ( j = &v49; sub_442E10() != 0; j = &v49 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                    sub_420BB0(&v49);  // vector push_back（4 字节元素）
                }
                else
                {
                  n = v14;
                  sub_401690(&v53);  // std::string 拷贝构造（复位 +20/+24/+4 后 ·sub_4014D0 全
                  if ( (uint8_t)sub_442C80(  // 判首字符方括号并析构
                                          (char)v14[0],
                                          v14[1],
                                          (int)v14[2],
                                          (int)v14[3],
                                          (int)v14[4],
                                          (int)v15,
                                          (int)j) == 0 )
                  {
                    v12 = (const char *)v54;
                    if ( v56 < 0x10 )  // 若 v56 < 0x10
                      v12 = (const char *)&v54;
                    off_77F3FC("SCRIPT TAG ERROR! [%s] %s", v2, v12);  // 字符串 “SCRIPT TAG ERROR! [%s] %s”
                  }
                }
              }
            }
            else
            {
              j = (void **)(pArg1 + 2136);
              sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
            }
          }
          else
          {
            j = (void **)(pArg1 + 2128);
            sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
          }
        }
        else
        {
          j = (void **)(pArg1 + 2124);
          sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
        }
      }
      else
      {
        j = (void **)(pArg1 + 2120);
        sub_442E10();  // 【RDARScriptStringManager 入口（::ERROR::input…】
      }
    }
    if ( v17 != 0 )  // 若 v17 != 0
      sub_4F7BD0(&v17);  // 124 字节元素尾插（满则 4F7B60）
    if ( *(uint32_t *)(pArg1 + 36) == -1 )  // 若 *(uint32_t *)(pArg1 + 36) == -1
      *(uint32_t *)(pArg1 + 36) = *(uint32_t *)(pArg1 + 20);  // pArg1+36 = *(uint32_t *)(pArg1 + 20)
    v13 = 10 * *(uint32_t *)(pArg1 + 24) + *(uint32_t *)(pArg1 + 20);
    j = (void **)v2;
    *(uint32_t *)(pArg1 + 20) = v13;  // pArg1+20 = v13
    *(uint32_t *)(pArg1 + 24) = 0;  // pArg1+24 = 0
    *(uint32_t *)pArg1 = sub_4A2F80(j);
    LOBYTE(v58) = 2;
    sub_4347B0(&v17);  // 124 字节条目析构
    LOBYTE(v58) = 1;
    sub_41B010(&v49);  // 驻留句柄析构（引用计数减到 0 释放）
    if ( v56 >= 0x10 )  // 若 v56 >= 0x10
      j__free(v54);  // 调 j__free
    v56 = 15;
    v55 = 0;
    LOBYTE(v54) = 0;
    if ( v52 >= 0x10 )  // 若 v52 >= 0x10
      j__free(v51[0]);  // 调 j__free
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4F8D70 sub_4F8D70 —— 84 字节元素向量长度（(end−begin)/84）
//   空向量返回 0；由 ·0x4FA210 系扩容取当前元素数。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F8D70(int *this)  // 函数: 84 字节元素向量长度（(end−begin)/84）
{
  int result; // eax

  result = *(this + 1);  // result = this+1
  if ( result != 0 )  // 若 result != 0
    return (*(this + 2) - result) / 84;
  return result;
}



// ------------------------------------------------------------
// 0x4F8D90 sub_4F8D90 —— 44 字节元素反向搬移（qmemcpy 0x2C 每步）
//   从尾向前逐槽 qmemcpy 0x2C，返回目标首址；配 ·0x4F8DC0 正向版。
// ------------------------------------------------------------
char */*cdecl*/ sub_4F8D90(char *pszArg1, char *pszArg2, char *pszArg3)  // 44 字节元素反向搬移（qmemcpy 0x2C 每步）
{
  char *pszArg22; // edx
  char *result; // eax

  pszArg22 = pszArg2;
  result = pszArg3;
  while ( pszArg22 != pszArg1 )  // 当 pszArg22 != pszArg1 循环
  {
    pszArg22 -= 44;
    result -= 44;
    qmemcpy(result, pszArg22, 0x2Cu);  // 调 qmemcpy 内联块拷贝
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F8DC0 sub_4F8DC0 —— 44 字节元素正向搬移（qmemcpy 0x2C 每步）
//   自首向尾逐槽 qmemcpy 0x2C，返回目标尾址。
// ------------------------------------------------------------
char */*cdecl*/ sub_4F8DC0(char *pszArg1, char *pszArg2, char *pszArg3)  // 44 字节元素正向搬移（qmemcpy 0x2C 每步）
{
  char *pszArg12; // edx
  char *result; // eax
  const void *pszArg122; // esi
  void *v6; // edi

  pszArg12 = pszArg1;
  result = pszArg3;
  while ( pszArg12 != pszArg2 )  // 当 pszArg12 != pszArg2 循环
  {
    pszArg122 = pszArg12;
    v6 = result;
    pszArg12 += 44;
    result += 44;
    qmemcpy(v6, pszArg122, 0x2Cu);  // 调 qmemcpy 内联块拷贝
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F8DF0 sub_4F8DF0 —— 44 字节元素填充拷贝（nArg2 个副本自 pArg3）
//   循环 qmemcpy 同值填充（逐槽空目标防御），配套 44 字节向量族（·0x4F9D10 系）。
// ------------------------------------------------------------
char */*cdecl*/ sub_4F8DF0(char *pszArg1, char *pszArg2, const void *pArg3)  // 44 字节元素填充拷贝（nArg2 个副本自 pArg3）
{
  char *result; // eax
  char *pszArg22; // edx

  result = pszArg2;
  if ( pszArg2 != nullptr )  // 若 pszArg2 非空
  {
    pszArg22 = pszArg2;
    result = pszArg1;
    do
    {
      if ( result != nullptr )  // 若 result 非空
        qmemcpy(result, pArg3, 0x2Cu);  // 调 qmemcpy 内联块拷贝
      result += 44;
      --pszArg22;  // 自减pszArg22
    }
    while ( pszArg22 != nullptr );  // 当 pszArg22 非空 循环
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
char /*cdecl*/ sub_4F8E20(void *pArg1)  // 函数: 等级金限表解析器（Etc/GoldLimitByLevel.etc）
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
  int dword_796E502; // [esp+44h] [ebp-10h]
  int v12; // [esp+50h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  memset(pArg1, 0, 0x190u);  // 清零 400 字节块
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"Etc/GoldLimitByLevel.etc") != 0 )  // 字符串 “Etc/GoldLimitByLevel.etc”
  {
    v10 = 15;
    v9 = 0;
    LOBYTE(Block) = 0;
    v12 = 1;
    v6 = 15;
    v5 = 0;
    v4[5] = 0;
    v4[0] = 0;
    while ( (uint8_t)sub_443430(v7) != 0 )  // 当 (uint8_t)sub_443430(v7) != 0 循环
    {
      if ( sub_40BF00((std::_String_base *)v7, 0, v9, "[gold limit from level]", 0x17u) == 0 )  // 字符串 “[gold limit from level]”
      {
        for ( i = 0; i < 100; ++i )  // 循环：i = 0; i < 100; ++i
        {
          v3 = sub_4423D0(v4);  // 调 sub_4423D0
          if ( v4[0] == 0 )  // 若 v4[0] == 0
            break;
          *((uint32_t *)pArg1 + v3) = 10 * sub_4423D0(nullptr);
        }
      }
    }
    if ( v10 >= 0x10 )  // 若 v10 >= 0x10
      j__free(Block);  // 调 j__free
    return 1;
  }
  else
  {
    off_77F3FC(aCriticalError_13);
    return 0;
  }
}



// ------------------------------------------------------------
// 0x4F8F40 sub_4F8F40 —— 等级分段查表（1..99 × 5 档系数）【推断】
//   uArg3=等级、pArg2=档位 0..4、uArg4=阶 0..6：行号 (uArg3-1)/10 取表值 × this[pArg2+4] 再
//   + this[pArg2+9]×uArg4；参数非法依次返回 -1..-4【推断：金限/费用表消费侧】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F8F40(uint32_t *this, uint8_t pArg2, uint8_t uArg3, uint8_t uArg4)  // 函数: 等级分段查表（1..99 × 5 档系数）【推断】
{
  int fld_e1; // edi
  unsigned int v7; // ecx

  if ( uArg3 == 0 )  // 若 uArg3 == 0
    return -1;  // 返回 -1（0xFFFFFFFF）
  if ( pArg2 > 4u )  // 若 pArg2 > 4u
    return -2;  // 返回 -2（0xFFFFFFFE）
  if ( uArg3 > 0x63u )  // 若 uArg3 > 0x63u
    return -3;  // 返回 -3（0xFFFFFFFD）
  if ( uArg4 >= 7u )  // 若 uArg4 >= 7u
    return -4;  // 返回 -4（0xFFFFFFFC）
  fld_e1 = *(this + 1);  // fld_e1 = this+1
  v7 = (uArg3 - 1) / 10;
  if ( fld_e1 == 0 || v7 >= (*(this + 2) - fld_e1) >> 2 )  // 若 fld_e1 == 0 || v7 >= (*(this + 2) - fld_e1) >> 2
    v7 = sub_41C5A0(this) - 1;  // 结果 = vector<T 4B> 大小查询（空返回 0）
  return *(uint32_t *)(fld_e1 + 4 * v7) * *(this + pArg2 + 4) + *(this + pArg2 + 9) * uArg4;
}



// ------------------------------------------------------------
// 0x4F8FE0 sub_4F8FE0 —— PVP 频道信息表解析器
//   标签族：[PVP CHANNEL INFO]（每频道 140 字节：名称 + 3 字节 + 104 字节槽位记录）。
//   未识别标签 → off_77F3FC(aPvp_3)。
// ------------------------------------------------------------
char /*cdecl*/ sub_4F8FE0(int ArgList, int nArg2, int nArg3)  // 函数: PVP 频道信息表解析器
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
  int dword_796E502; // [esp+50h] [ebp-10h]
  int v26; // [esp+5Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = sub_442A10((char)szPassword, ArgList);  // 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result != 0 )  // 若 result != 0
  {
    v4 = 0;
    v21 = 15;
    v20 = 0;
    LOBYTE(v19) = 0;
    v26 = 0;
    v17 = 0;
    while ( (uint8_t)sub_443430(v18) != 0 )  // 当 (uint8_t)sub_443430(v18) != 0 循环
    {
      if ( (uint8_t)sub_442BC0(v18) != 0 )  // 国家码标签配对校验（bool）
        off_77F3FC((char *)&byte_6FA9F8, ArgList);
      if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[PVP CHANNEL INFO]", 0x12u) == 0 )  // 字符串 “[PVP CHANNEL INFO]”
      {
        for ( i = sub_4423D0(&v17); v17 != 0; i = sub_4423D0(&v17) )  // 循环：i = sub_4423D0(&v17); v17 != 0; i = sub_4423D0(&v17)
        {
          if ( --nArg3 >= 0 )  // 若 --nArg3 >= 0
          {
            v24 = 15;
            v23 = 0;
            LOBYTE(Block) = 0;
            LOBYTE(v26) = 1;
            v6 = 140 * i + nArg2 - 140;
            v13 = sub_4423D0(nullptr);  // 调 sub_4423D0
            v16 = 0;
            if ( v13 > 0 )  // 若 v13 > 0
            {
              v7 = 0;
              do
              {
                sub_443370();  // 脚本 token 取串（第三入口）
                v14 = sub_4423D0(nullptr);  // 调 sub_4423D0
                v15 = sub_4423D0(nullptr);  // 调 sub_4423D0
                v12 = sub_4423D0(nullptr);  // 调 sub_4423D0
                v8 = *(uint32_t *)(v6 + 128);  // v8 = v6+128
                if ( v8 != 0 && v4 < (*(uint32_t *)(v6 + 132) - v8) / 104 )  // 若 v8 != 0 && v4 < (*(uint32_t *)(v6 + 132) - v8) / 104
                {
                  v9 = *(uint32_t *)(v6 + 128);  // v9 = v6+128
                  p_Block = (const char *)Block;
                  if ( v24 < 0x10 )  // 若 v24 < 0x10
                    p_Block = (const char *)&Block;
                  strncpy((char *)(v7 + v9 + 4), p_Block, 0x32u);  // 调 strncpy 限长串拷贝
                  *(uint8_t *)(v7 + v9 + 98) = v14;
                  *(uint8_t *)(v7 + v9 + 99) = v15;
                  *(uint8_t *)(v7 + v9 + 100) = v12;
                  v4 = v16;
                }
                else
                {
                  v11 = *(uint32_t *)(v6 + 128);  // v11 = v6+128
                  if ( v11 != 0 )  // 若 v11 != 0
                    v11 = (*(uint32_t *)(v6 + 132) - v11) / 104;
                  off_77F3FC(aPvp_3, v4 + 1, v11);
                }
                ++v4;  // 自增v4
                v7 += 104;
                v16 = v4;
              }
              while ( (int)v4 < v13 );  // 当 (int)v4 < v13 循环
              v4 = 0;
            }
            LOBYTE(v26) = 0;
            if ( v24 >= 0x10 )  // 若 v24 >= 0x10
              j__free(Block);  // 调 j__free
            v24 = 15;
            v23 = 0;
            LOBYTE(Block) = 0;
          }
        }
      }
    }
    if ( v21 >= 0x10 )  // 若 v21 >= 0x10
      j__free(v19);  // 调 j__free
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4F9240 sub_4F9240 —— 战场区域表解析器（Etc/WarArea.etc）
//   标签族：[time table]（时段表）/[door fee]（入场费）/[counter]。
//   加载失败 → off_77F3FC(aCriticalError_14)。
// ------------------------------------------------------------
char /*cdecl*/ sub_4F9240(int pArg1)  // 函数: 战场区域表解析器（Etc/WarArea.etc）
{
  int v2; // ebx
  unsigned int v3; // edx
  int v4; // ecx
  void **Block2; // esi
  int nCmp; // eax
  int v7; // eax
  int pArg12; // edi
  int *v9; // esi
  int v10; // ecx
  void **Block3; // esi
  int nCmp2; // eax
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
  int dword_796E502; // [esp+28h] [ebp-10h]
  int v24; // [esp+34h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"Etc/WarArea.etc") == 0 )  // 字符串 “Etc/WarArea.etc”
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
  if ( (uint8_t)sub_443430(v19) != 0 )  // 读 token 到 string + 国家码标记
  {
    while ( 1 )  // 当 1 循环
    {
      v3 = v21;
      if ( v21 != 0 )  // 若 v21 != 0
      {
        v4 = v21;
        if ( v21 >= 0xC )  // 若 v21 >= 0xC
          v4 = 12;
        Block2 = (void **)Block[0];
        if ( v22 < 0x10 )  // 若 v22 < 0x10
          Block2 = Block;
        nCmp = memcmp((const char *)Block2, "[time table]", v4);  // 字符串 “[time table]”
        if ( nCmp != 0 || v21 < 0xC || (LOBYTE(nCmp) = v21 != 12, nCmp != 0) )  // 若 nCmp != 0 || v21 < 0xC || (LOBYTE(nCmp) = v21 != 12, nCmp != 0)
        {
          pArg12 = pArg1;
        }
        else
        {
          v7 = sub_4423D0(&v18);  // 调 sub_4423D0
          pArg12 = pArg1;
          if ( v18 != 0 )  // 若 v18 != 0
          {
            v9 = (int *)(pArg1 + 4 * v2 + 96);
            do
            {
              *v9 = v7;  // *v9 写入 v7
              ++v2;  // 自增v2
              ++v9;  // 自增v9
              v7 = sub_4423D0(&v18);  // 调 sub_4423D0
            }
            while ( v18 != 0 );  // 当 v18 != 0 循环
          }
        }
        v3 = v21;
      }
      else
      {
        pArg12 = pArg1;
      }
      if ( v3 == 0 )  // 若 v3 == 0
        goto LABEL_32;  // 跳转 LABEL_32
      v10 = v3;
      if ( v3 >= 0xA )  // 若 v3 >= 0xA
        v10 = 10;
      Block3 = (void **)Block[0];
      if ( v22 < 0x10 )  // 若 v22 < 0x10
        Block3 = Block;
      nCmp2 = memcmp((const char *)Block3, "[door fee]", v10);  // 字符串 “[door fee]”
      if ( nCmp2 != 0 )  // 若 nCmp2 != 0
        break;
      if ( v3 < 0xA )  // 若 v3 < 0xA
        break;
      LOBYTE(nCmp2) = v3 != 10;
      if ( nCmp2 != 0 )  // 若 nCmp2 != 0
        break;
      v13 = sub_4423D0(&v18);  // 调 sub_4423D0
      if ( v18 != 0 )  // 若 v18 != 0
      {
        v14 = (int *)(pArg1 + 192);
        do
        {
          *v14++ = v13;  // *v14++ 写入 v13
          v13 = sub_4423D0(&v18);  // 调 sub_4423D0
        }
        while ( v18 != 0 );  // 当 v18 != 0 循环
      }
LABEL_39:
      if ( (uint8_t)sub_443430(v19) == 0 )  // 读 token 到 string + 国家码标记
        goto LABEL_40;  // 跳转 LABEL_40
    }
    pArg12 = pArg1;
    v3 = v21;
LABEL_32:
    if ( sub_40BF00((std::_String_base *)v19, 0, v3, "[counter]", 9u) == 0 )  // 字符串 “[counter]”
    {
      *(uint32_t *)(pArg12 + 236) = v2;  // pArg12+236 = v2
      v2 = 0;
      for ( i = sub_4423D0(&v18); v18 != 0; i = sub_4423D0(&v18) )  // 循环：i = sub_4423D0(&v18); v18 != 0; i = sub_4423D0(&v18)
      {
        if ( i > v17 )  // 若 i > v17
        {
          v17 = i;
          v16 = v2;
        }
        *(uint32_t *)(pArg12 + 4 * v2++) = i;
        if ( *(uint32_t *)(pArg12 + 236) == v2 )  // 若 *(uint32_t *)(pArg12 + 236) == v2
          break;
      }
      *(uint32_t *)(pArg12 + 232) = v16;  // pArg12+232 = v16
    }
    goto LABEL_39;  // 跳转 LABEL_39
  }
LABEL_40:
  if ( v22 >= 0x10 )  // 若 v22 >= 0x10
    j__free(Block[0]);  // 调 j__free
  return 1;
}


// ------------------------------------------------------------
// 0x4F9470 sub_4F9470 —— 84 字节元素拷贝构造（+48 串槽深拷贝）
//   前 48 字节直拷，+48 串槽 SSO 初始化后 sub_4014D0 赋值，+76/+80 尾字段直拷。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F9470(uint32_t *this, int pArg2)  // 84 字节元素拷贝构造（+48 串槽深拷贝）
{
  char *pThis_C; // ecx

  *this = *(uint32_t *)pArg2;  // *this 写入 *(uint32_t *)pArg2
  *(this + 1) = *(uint32_t *)(pArg2 + 4);  // this+4 = *(uint32_t *)(pArg2 + 4)
  *(this + 2) = *(uint32_t *)(pArg2 + 8);  // this+8 = *(uint32_t *)(pArg2 + 8)
  *(this + 3) = *(uint32_t *)(pArg2 + 12);  // this+12 = *(uint32_t *)(pArg2 + 12)
  *((uint8_t *)this + 16) = *(uint8_t *)(pArg2 + 16);
  *(this + 5) = *(uint32_t *)(pArg2 + 20);  // this+20 = *(uint32_t *)(pArg2 + 20)
  *((uint8_t *)this + 24) = *(uint8_t *)(pArg2 + 24);
  *((uint16_t *)this + 13) = *(uint16_t *)(pArg2 + 26);
  *(this + 7) = *(uint32_t *)(pArg2 + 28);  // this+28 = *(uint32_t *)(pArg2 + 28)
  *(this + 8) = *(uint32_t *)(pArg2 + 32);  // this+32 = *(uint32_t *)(pArg2 + 32)
  *(this + 9) = *(uint32_t *)(pArg2 + 36);  // this+36 = *(uint32_t *)(pArg2 + 36)
  *(this + 10) = *(uint32_t *)(pArg2 + 40);  // this+40 = *(uint32_t *)(pArg2 + 40)
  *((uint8_t *)this + 44) = *(uint8_t *)(pArg2 + 44);
  pThis_C = (char *)(this + 12);
  *((uint32_t *)pThis_C + 6) = 15;
  *((uint32_t *)pThis_C + 5) = 0;
  pThis_C[4] = 0;
  sub_4014D0((std::_String_base *)pThis_C, pArg2 + 48, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
  *(this + 19) = *(uint32_t *)(pArg2 + 76);  // this+76 = *(uint32_t *)(pArg2 + 76)
  *((uint8_t *)this + 80) = *(uint8_t *)(pArg2 + 80);
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F9500 sub_4F9500 —— vector 下标越界异常（out_of_range，不返回）
//   invalid vector<T> subscript 文案构造后抛出（std::out_of_range）；由 ·0x4F9750 边界检查触发。
// ------------------------------------------------------------
void /*noreturn*/ sub_4F9500()  // vector 下标越界异常（out_of_range，不返回）
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0("invalid vector<T> subscript", 0x1Bu);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject = &std::out_of_range::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// ------------------------------------------------------------
// 0x4F9570 sub_4F9570 —— vector 超长异常（length_error，不返回）
//   vector<T> too long 文案与 ·0x4F43D0 同构造路径；本块 84/44 字节向量扩容的抛出点。
// ------------------------------------------------------------
void /*noreturn*/ sub_4F9570()  // vector 超长异常（length_error，不返回）
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4F95E0 sub_4F95E0 —— 84 字节元素赋值拷贝（+48 串替身）
//   与 ·0x4F9470 同构、省略串槽重建（目标已构造），+48 经 sub_4014D0 直接赋值。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F95E0(uint32_t *this, int pArg2)  // 84 字节元素赋值拷贝（+48 串替身）
{
  *this = *(uint32_t *)pArg2;  // *this 写入 *(uint32_t *)pArg2
  *(this + 1) = *(uint32_t *)(pArg2 + 4);  // this+4 = *(uint32_t *)(pArg2 + 4)
  *(this + 2) = *(uint32_t *)(pArg2 + 8);  // this+8 = *(uint32_t *)(pArg2 + 8)
  *(this + 3) = *(uint32_t *)(pArg2 + 12);  // this+12 = *(uint32_t *)(pArg2 + 12)
  *((uint8_t *)this + 16) = *(uint8_t *)(pArg2 + 16);
  *(this + 5) = *(uint32_t *)(pArg2 + 20);  // this+20 = *(uint32_t *)(pArg2 + 20)
  *((uint8_t *)this + 24) = *(uint8_t *)(pArg2 + 24);
  *((uint16_t *)this + 13) = *(uint16_t *)(pArg2 + 26);
  *(this + 7) = *(uint32_t *)(pArg2 + 28);  // this+28 = *(uint32_t *)(pArg2 + 28)
  *(this + 8) = *(uint32_t *)(pArg2 + 32);  // this+32 = *(uint32_t *)(pArg2 + 32)
  *(this + 9) = *(uint32_t *)(pArg2 + 36);  // this+36 = *(uint32_t *)(pArg2 + 36)
  *(this + 10) = *(uint32_t *)(pArg2 + 40);  // this+40 = *(uint32_t *)(pArg2 + 40)
  *((uint8_t *)this + 44) = *(uint8_t *)(pArg2 + 44);
  sub_4014D0((std::_String_base *)(this + 12), pArg2 + 48, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
  *(this + 19) = *(uint32_t *)(pArg2 + 76);  // this+76 = *(uint32_t *)(pArg2 + 76)
  *((uint8_t *)this + 80) = *(uint8_t *)(pArg2 + 80);
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F9660 sub_4F9660 —— 84 字节元素反向搬移赋值（插入用）
//   从尾向前 84 字节每步 sub_4F95E0 赋值（目标 -=21 双字），返回目标首址。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F9660(int nArg1, int nArg2, uint32_t *uArg3)  // 84 字节元素反向搬移赋值（插入用）
{
  int nArg22; // esi
  uint32_t *uArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )  // 若 nArg1 == nArg2
    return uArg3;
  uArg32 = uArg3;
  do
  {
    nArg22 -= 84;
    uArg32 -= 21;
    sub_4F95E0(uArg32, nArg22);  // 84 字节元素赋值拷贝（+48 串替身）
  }
  while ( nArg22 != nArg1 );  // 当 nArg22 != nArg1 循环
  return uArg32;
}



// ------------------------------------------------------------
// 0x4F96A0 sub_4F96A0 —— 84 字节元素正向拷贝构造（源区间 → 新缓冲）
//   逐槽 sub_4F9470 拷贝构造（步长 21 双字），异常展开标记；vector 扩容搬移用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F96A0(int nArg1, int nArg2, uint32_t *uArg3)  // 84 字节元素正向拷贝构造（源区间 → 新缓冲）
{
  uint32_t *uArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v6[4] = v6;
  v6[3] = uArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )  // 当 nArg1 != nArg2 循环
  {
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )  // 若 uArg32 非空
      sub_4F9470(uArg32, nArg1);  // 84 字节元素拷贝构造（+48 串槽深拷贝）
    uArg32 += 21;
    LOBYTE(v7) = 0;
    nArg1 += 84;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x4F9750 sub_4F9750 —— 44 字节元素带界取址（越界抛 out_of_range）
//   返回 this[1] + 44×uArg2；空或下标 ≥ 元素数时转 ·0x4F9500。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F9750(uint32_t *this, unsigned int uArg2)  // 函数: 44 字节元素带界取址（越界抛 out_of_range）
{
  int fld_e1; // esi

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( fld_e1 == 0 || (*(this + 2) - fld_e1) / 44 <= uArg2 )  // 若 fld_e1 == 0 || (*(this + 2) - fld_e1) / 44 <= uArg2
    sub_4F9500();  // vector 下标越界异常（out_of_range，不返回）
  return fld_e1 + 44 * uArg2;
}



// ------------------------------------------------------------
// 0x4F9790 sub_4F9790 —— 44 字节元素向量插入（三路分支 + 1.5 倍扩容）
//   就地 sub_508EA0/sub_4F8D90/sub_508E70；重建经 operator new + sub_508EE0 填洞、sub_4F8DF0，
//   容量取 sub_527B90；超限 sub_4F9570。
// ------------------------------------------------------------
void /*thiscall*/ sub_4F9790(int *this, char *pszArg2, unsigned int uArg3, void *Block)  // 函数: 44 字节元素向量插入（三路分支 + 1.5 倍扩容）
{
  int fld_e1; // edi
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  int v12; // edi
  int fld_e13; // eax
  unsigned int v14; // esi
  char *fld_e23; // ecx
  int fld_e26; // esi
  int fld_e12; // [esp-18h] [ebp-60h]
  int fld_e25; // [esp-Ch] [ebp-54h]
  unsigned int fld_e24; // [esp-8h] [ebp-50h]
  int v21; // [esp+0h] [ebp-48h] BYREF
  uint32_t v22[12]; // [esp+Ch] [ebp-3Ch] BYREF
  int v23; // [esp+44h] [ebp-4h]
  char *v24; // [esp+50h] [ebp+8h]
  char *v25; // [esp+54h] [ebp+Ch]
  char *Blocka; // [esp+58h] [ebp+10h]
  char *Blockb; // [esp+58h] [ebp+10h]

  qmemcpy(v22, Block, 0x2Cu);  // 调 qmemcpy 内联块拷贝
  fld_e1 = *(this + 1);  // fld_e1 = this+1
  v22[11] = &v21;
  if ( fld_e1 != 0 )  // 若 fld_e1 != 0
    fld_e3 = (*(this + 3) - fld_e1) / 44;
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e2 = (*(this + 2) - fld_e1) / 44;
    else
      fld_e2 = 0;
    if ( 97612893 - fld_e2 < uArg3 )  // 若 97612893 - fld_e2 < uArg3
      sub_4F9570(this);  // vector 超长异常（length_error，不返回）
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e22 = (*(this + 2) - fld_e1) / 44;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )  // 若 fld_e3 >= uArg3 + fld_e22
    {
      fld_e23 = (char *)*(this + 2);
      Blockb = fld_e23;
      if ( (fld_e23 - pszArg2) / 44 >= uArg3 )  // 若 (fld_e23 - pszArg2) / 44 >= uArg3
      {
        v24 = &fld_e23[-44 * uArg3];
        *(this + 2) = sub_508EA0(v24, fld_e23, fld_e23);  // this+8 = sub_508EA0(v24, fld_e23, fld_e23)
        sub_4F8D90(pszArg2, v24, Blockb);  // 44 字节元素反向搬移（qmemcpy 0x2C 每步）
        sub_508E70(pszArg2, &pszArg2[44 * uArg3], v22);  // 调 sub_508E70
      }
      else
      {
        sub_508EA0(pszArg2, fld_e23, &pszArg2[44 * uArg3]);  // 调 sub_508EA0
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 44;
        fld_e25 = *(this + 2);  // fld_e25 = this+2
        v23 = 2;
        sub_508EE0(fld_e25, fld_e24, v22);  // 调 sub_508EE0
        fld_e26 = 44 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8 = fld_e26
        sub_508E70(pszArg2, fld_e26 - 44 * uArg3, v22);  // 调 sub_508E70
      }
    }
    else
    {
      if ( 97612893 - (fld_e3 >> 1) >= fld_e3 )  // 若 97612893 - (fld_e3 >> 1) >= fld_e3
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )  // 若 fld_e1 != 0
        fld_e27 = (*(this + 2) - fld_e1) / 44;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )  // 若 v10 < uArg3 + fld_e27
        v10 = uArg3 + sub_527B90(this);
      v12 = 44 * v10;
      Blocka = (char *)operator new(44 * v10);
      fld_e12 = *(this + 1);  // fld_e12 = this+1
      v23 = 0;
      v25 = (char *)sub_508EA0(fld_e12, pszArg2, Blocka);
      sub_4F8DF0(v25, (char *)uArg3, v22);  // 44 字节元素填充拷贝（nArg2 个副本自 pArg3）
      sub_508EA0(pszArg2, *(this + 2), &v25[44 * uArg3]);  // 调 sub_508EA0
      fld_e13 = *(this + 1);  // fld_e13 = this+1
      if ( fld_e13 != 0 )  // 若 fld_e13 != 0
        fld_e13 = (*(this + 2) - fld_e13) / 44;
      v14 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        j__free((void *)*(this + 1));  // 调 j__free
      *(this + 3) = (int)&Blocka[v12];  // this+12 = (int)&Blocka[v12]
      *(this + 2) = (int)&Blocka[44 * v14];  // this+8 = (int)&Blocka[44 * v14]
      *(this + 1) = (int)Blocka;  // this+4 = (int)Blocka
    }
  }
}



// ------------------------------------------------------------
// 0x4F9A40 sub_4F9A40 —— 与 ·0x4F44C0 同构（差异：超长抛 sub_4F9570 而非 4F43D0）
//   vector<uint32> 批量插入的异常路径变体。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4F9A40(int this, int Src, unsigned int uArg3, int *pDwArg4)  // 函数: 与 ·0x4F44C0 同构（差异：超长抛 sub_4F9570 而非 4F43D0）
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

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    result = 0;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )  // 若 0x3FFFFFFF - fld_8 < uArg3
      sub_4F9570(this);  // vector 超长异常（length_error，不返回）
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )  // 若 result >= uArg3 + fld_82
    {
      fld_83 = *(uint8_t **)(this + 8);
      v21 = (int)&fld_83[-Src] >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )  // 若 v21 >= uArg3
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // 商城状态
        sub_5DAF70((void *)Src, v24, v29);  // 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // 商城状态
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // 调 sub_523700
        fld_84 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = fld_84;  // this+8 = fld_84
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )  // 若 0x3FFFFFFF - (result >> 1) >= result
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 != 0
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )  // 若 v10 < uArg3 + fld_85
      {
        if ( fld_4 != 0 )  // 若 fld_4 != 0
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
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = this+4
      if ( fld_43 != 0 )  // 若 fld_43 != 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;
      else
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )  // 若 fld_43 != 0
        j__free(*(void **)(this + 4));  // 调 j__free
      *(uint32_t *)(this + 12) = &pMem[v28];  // this+12 = &pMem[v28]
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // this+8 = &pMem[4 * v18]
      *(uint32_t *)(this + 4) = pMem;  // this+4 = pMem
      return (unsigned int)pMem;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4F9C20 sub_4F9C20 —— 44 字节元素向量区间拷贝赋值
//   源元素数经 sub_452830 分配检查后 sub_508EA0 搬入 this[1]；返回 this。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4F9C20(uint32_t *this, int pArg2)  // 44 字节元素向量区间拷贝赋值
{
  int v2; // eax
  int v5; // [esp-14h] [ebp-34h]
  int v6; // [esp-10h] [ebp-30h]
  int fld_e1; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(pArg2 + 4);  // v2 = pArg2+4
  v10 = &v8;
  pThis = this;
  if ( v2 != 0 )  // 若 v2 != 0
    v2 = (*(uint32_t *)(pArg2 + 8) - v2) / 44;
  if ( (uint8_t)sub_452830(v2) != 0 )  // 44 字节元素表分配
  {
    fld_e1 = *(this + 1);  // fld_e1 = this+1
    v6 = *(uint32_t *)(pArg2 + 8);  // v6 = pArg2+8
    v5 = *(uint32_t *)(pArg2 + 4);  // v5 = pArg2+4
    v11 = 0;
    *(this + 2) = sub_508EA0(v5, v6, fld_e1);  // this+8 = sub_508EA0(v5, v6, fld_e1)
  }
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F9CC0 sub_4F9CC0 —— 84 字节元素正向批量赋值（同源复制）
//   由 nArg3 单元素逐槽 sub_4F95E0 赋值（步长 21 双字），配 ·0x4F9CF0 反向版。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F9CC0(uint32_t *uArg1, uint32_t *uArg2, int nArg3)  // 84 字节元素正向批量赋值（同源复制）
{
  uint32_t *i; // esi
  uint32_t *result; // eax

  for ( i = uArg1; i != uArg2; i += 21 )  // 循环：i = uArg1; i != uArg2; i += 21
    result = sub_4F95E0(i, nArg3);  // 结果 = 84 字节元素赋值拷贝（+48 串替身）
  return result;
}



// ------------------------------------------------------------
// 0x4F9CF0 sub_4F9CF0 —— 薄封装（转 4F9660 反向搬移）
//   参数直通 sub_4F9660，供插入路径统一入口。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F9CF0(int nArg1, int nArg2, uint32_t *uArg3)  // 薄封装（转 4F9660 反向搬移）
{
  return sub_4F9660(nArg1, nArg2, uArg3);  // 84 字节元素反向搬移赋值（插入用）
}



// ------------------------------------------------------------
// 0x4F9D10 sub_4F9D10 —— 44 字节元素向量赋值（容量三路分支）
//   源空则释放清零；容量足够 sub_4F8DC0 覆盖，不足经 sub_527B90/sub_452830/sub_433CF0 重建；
//   44B 元素区间拷贝公共件。
// ------------------------------------------------------------
int /*thiscall*/ sub_4F9D10(int this, int pArg2)  // 函数: 44 字节元素向量赋值（容量三路分支）
{
  int v3; // eax
  unsigned int v4; // ecx
  char *fld_4; // ebx
  unsigned int fld_8; // eax
  int v8; // eax
  unsigned int fld_C; // eax
  char *v10; // edi
  int v11; // eax

  if ( this == pArg2 )  // 若 this == pArg2
    return this;  // 返回自身指针
  v3 = *(uint32_t *)(pArg2 + 4);  // v3 = pArg2+4
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) / 44) == 0 )  // 若 v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) / 44) == 0
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // 若 *(uint32_t *)(this + 4) != 0
      j__free(*(void **)(this + 4));  // 调 j__free
    *(uint32_t *)(this + 4) = 0;  // this+4 = 0
    *(uint32_t *)(this + 8) = 0;  // this+8 = 0
    *(uint32_t *)(this + 12) = 0;  // this+12 = 0
    return this;  // 返回自身指针
  }
  fld_4 = *(char **)(this + 4);
  if ( fld_4 != nullptr )  // 若 fld_4 非空
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 44;
  else
    fld_8 = 0;
  if ( v4 > fld_8 )  // 若 v4 > fld_8
  {
    if ( fld_4 != nullptr )  // 若 fld_4 非空
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 44;
    else
      fld_C = 0;
    if ( v4 <= fld_C )  // 若 v4 <= fld_C
    {
      v10 = (char *)(*(uint32_t *)(pArg2 + 4) + 44 * sub_527B90(this));
      sub_4F8DC0(*(char **)(pArg2 + 4), v10, fld_4);  // 44 字节元素正向搬移（qmemcpy 0x2C 每步）
      *(uint32_t *)(this + 8) = sub_508EA0(v10, *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 8));  // this+8 = sub_508EA0(v10, *(uint32_t *)(pArg2 + 8), ..
      return this;  // 返回自身指针
    }
    if ( fld_4 != nullptr )  // 若 fld_4 非空
      j__free(*(void **)(this + 4));  // 调 j__free
    v11 = sub_527B90(pArg2);  // 调 sub_527B90
    if ( (uint8_t)sub_452830(v11) != 0 )  // 44 字节元素表分配
      *(uint32_t *)(this + 8) = sub_433CF0(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));  // 44B 元素区间拷贝
    return this;  // 返回自身指针
  }
  sub_4F8DC0(*(char **)(pArg2 + 4), *(char **)(pArg2 + 8), *(char **)(this + 4));  // 44 字节元素正向搬移（qmemcpy 0x2C 每步）
  v8 = *(uint32_t *)(pArg2 + 4);  // v8 = pArg2+4
  if ( v8 != 0 )  // 若 v8 != 0
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 44 * ((*(uint32_t *)(pArg2 + 8) - v8) / 44);  // this+8 = *(uint32_t *)(this + 4) + 44 * ((*(uint32_..
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);  // this+8 = *(uint32_t *)(this + 4)
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4F9E90 sub_4F9E90 —— 84 字节元素填充构造（nArg2 个副本自 nArg3）
//   逐次 sub_4F9470 拷贝构造（步长 21 双字），异常展开标记。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4F9E90(uint32_t *uArg1, int nArg2, int nArg3)  // 84 字节元素填充构造（nArg2 个副本自 nArg3）
{
  uint32_t *uArg12; // esi
  uint32_t *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg12 = uArg1;
  v6[4] = v6;
  v6[3] = uArg1;
  v7 = 0;
  while ( nArg2 != 0 )  // 当 nArg2 != 0 循环
  {
    LOBYTE(v7) = 1;
    if ( uArg12 != nullptr )  // 若 uArg12 非空
      result = sub_4F9470(uArg12, nArg3);  // 结果 = 84 字节元素拷贝构造（+48 串槽深拷贝）
    --nArg2;  // 自减nArg2
    uArg12 += 21;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4F9F40 sub_4F9F40 —— 强化数值重算（44B 行 × 三层浮点系数）【推断】
//   校验（a5<行数、a3<5、8≤a6<18、a4<100）失败返 0；qmemcpy 行 a5 后 a2[10] 先取 this[a4+30]，
//   再依次乘 this[a6+7] 与 this[a3+25] 两个 float 系数。
// ------------------------------------------------------------
char /*thiscall*/ sub_4F9F40(  // 强化数值重算（44B 行 × 三层浮点系数）【推断】
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

  v7 = *(this + 1);  // v7 = this+1
  if ( v7 != 0 )  // 若 v7 != 0
    v7 = (int)(*(this + 2) - v7) / 44;
  if ( a5 >= v7 || a3 >= 5u || a6 >= 18 || a6 < 8 || a4 >= 0x64u )  // 若 a5 >= v7 || a3 >= 5u || a6 >= 18 || a6 < 8 || a4 >= 0x64u
    return 0;
  qmemcpy(a2, (const void *)sub_4F9750(this, a5), 0x2Cu);  // 44 字节元素带界取址（越界抛 out_of_range）
  v9 = *(this + a4 + 30);
  a2[10] = v9;
  v10 = (uint64_t)((double)v9 * *((float *)this + a6 + 7));
  a2[10] = v10;
  a2[10] = (uint64_t)((double)(unsigned int)v10 * *((float *)this + a3 + 25));  // a2[10] 写入 (uint64_t)((double)(unsigned int)v10 * *((..
  return 1;
}



// ------------------------------------------------------------
// 0x4FA000 sub_4FA000 —— 44 字节元素单点插入（返回新址）
//   记录索引 → ·0x4F9790 扩一 → 新址回写 uArg2。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FA000(int *this, uint32_t *uArg2, char *pszArg3, void *Block)  // 44 字节元素单点插入（返回新址）
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 44 != 0 )  // 若 fld_e1 != 0 && (*(this + 2) - fld_e1) / 44 != 0
    v6 = (int)&pszArg3[-fld_e1] / 44;
  else
    v6 = 0;
  sub_4F9790(this, pszArg3, 1u, Block);  // 44 字节元素向量插入（三路分支 + 1.5 倍扩容）
  *uArg2 = *(this + 1) + 44 * v6;  // *uArg2 写入 *(this + 1) + 44 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x4FA070 sub_4FA070 —— 20 字节元素反向搬移（双半字 + 44B 子向量）
//   每步 -20：头两半字直拷、+4 子向量经 ·0x4F9D10 赋值；20 字节族（4FB660 系）。
// ------------------------------------------------------------
uint16_t */*cdecl*/ sub_4FA070(int nArg1, int nArg2, uint16_t *uArg3)  // 20 字节元素反向搬移（双半字 + 44B 子向量）
{
  int nArg22; // esi
  uint16_t *uArg32; // edi
  int16_t v5; // ax

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )  // 若 nArg1 == nArg2
    return uArg3;
  uArg32 = uArg3;
  do
  {
    v5 = *(uint16_t *)(nArg22 - 20);
    nArg22 -= 20;
    uArg32 -= 10;
    *uArg32 = v5;  // *uArg32 写入 v5
    uArg32[1] = *(uint16_t *)(nArg22 + 2);  // uArg32[1] 写入 *(uint16_t *)(nArg22 + 2)
    sub_4F9D10((int)(uArg32 + 2), nArg22 + 4);  // 44 字节元素向量赋值（容量三路分支）
  }
  while ( nArg22 != nArg1 );  // 当 nArg22 != nArg1 循环
  return uArg32;
}



// ------------------------------------------------------------
// 0x4FA0C0 sub_4FA0C0 —— 系数表对象构造（向量清零 + 23 项 float 置 1.0）
//   this[1..3] 清零，+28..+116 的 23 个 float 全置 1065353216（1.0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FA0C0(uint32_t *this)  // 系数表对象构造（向量清零 + 23 项 float 置 1.0）
{
  *(this + 1) = 0;  // this+4 = 0
  *(this + 2) = 0;  // this+8 = 0
  *(this + 3) = 0;  // this+12 = 0
  *(this + 7) = 1065353216;  // this+28 = 1065353216
  *(this + 8) = 1065353216;  // this+32 = 1065353216
  *(this + 9) = 1065353216;  // this+36 = 1065353216
  *(this + 10) = 1065353216;  // this+40 = 1065353216
  *(this + 11) = 1065353216;  // this+44 = 1065353216
  *(this + 12) = 1065353216;  // this+48 = 1065353216
  *(this + 13) = 1065353216;  // this+52 = 1065353216
  *(this + 14) = 1065353216;  // this+56 = 1065353216
  *(this + 15) = 1065353216;  // this+60 = 1065353216
  *(this + 16) = 1065353216;  // this+64 = 1065353216
  *(this + 17) = 1065353216;  // this+68 = 1065353216
  *(this + 18) = 1065353216;  // this+72 = 1065353216
  *(this + 19) = 1065353216;  // this+76 = 1065353216
  *(this + 20) = 1065353216;  // this+80 = 1065353216
  *(this + 21) = 1065353216;  // this+84 = 1065353216
  *(this + 22) = 1065353216;  // this+88 = 1065353216
  *(this + 23) = 1065353216;  // this+92 = 1065353216
  *(this + 24) = 1065353216;  // this+96 = 1065353216
  *(this + 25) = 1065353216;  // this+100 = 1065353216
  *(this + 26) = 1065353216;  // this+104 = 1065353216
  *(this + 27) = 1065353216;  // this+108 = 1065353216
  *(this + 28) = 1065353216;  // this+112 = 1065353216
  *(this + 29) = 1065353216;  // this+116 = 1065353216
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4FA120 sub_4FA120 —— 44 字节元素尾插（满则 4FA000）
//   有余量 sub_4F8DF0 就地填充 +44 递增，否则 ·0x4FA000。
// ------------------------------------------------------------
char */*thiscall*/ sub_4FA120(int this, void *Block)  // 44 字节元素尾插（满则 4FA000）
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  char *fld_82; // edi
  char *result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 44;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 44 )  // 若 fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 44
    return (char *)sub_4FA000((int *)this, &Block, *(char **)(this + 8), Block);  // 44 字节元素单点插入（返回新址）
  fld_82 = *(char **)(this + 8);
  result = sub_4F8DF0(fld_82, (char *)1, Block);  // 结果 = 44 字节元素填充拷贝（nArg2 个副本自 pArg3）
  *(uint32_t *)(this + 8) = fld_82 + 44;  // this+8 = fld_82 + 44
  return result;
}



// ------------------------------------------------------------
// 0x4FA1B0 sub_4FA1B0 —— 84 字节元素填充 + 返回尾址（组合器）
//   sub_4F9E90 填充后返回 &pArg1[21×nArg2]。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4FA1B0(uint32_t *pArg1, int nArg2, int nArg3)  // 84 字节元素填充 + 返回尾址（组合器）
{
  sub_4F9E90(pArg1, nArg2, nArg3);  // 84 字节元素填充构造（nArg2 个副本自 nArg3）
  return &pArg1[21 * nArg2];
}



// ------------------------------------------------------------
// 0x4FA1E0 sub_4FA1E0 —— 84 字节元素区间析构（逐槽 44C0C0）
//   按 84 步长逐元素 sub_44C0C0 析构（内嵌单串），供 ·0x4FA210 重建前清理。
// ------------------------------------------------------------
int /*stdcall*/ sub_4FA1E0(int nArg1, int nArg2)  // 函数: 84 字节元素区间析构（逐槽 44C0C0）
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 84 )  // 循环：i = nArg1; i != nArg2; i += 84
    result = sub_44C0C0(i);  // 结果 = 单字符串元素析构
  return result;
}



// ------------------------------------------------------------
// 0x4FA210 sub_4FA210 —— 84 字节元素向量插入（三路分支 + 1.5 倍扩容）
//   就地 sub_4F96A0/sub_4F9CF0/sub_4F9CC0；重建经 operator new + sub_4F96A0/sub_4F9E90 与
//   sub_4FA1E0 析构旧段；超限 sub_4F9570；首元素经 ·0x4F9470 构造临时。
// ------------------------------------------------------------
void /*thiscall*/ sub_4FA210(int *this, int pArg2, unsigned int uArg3, int nArg4)  // 函数: 84 字节元素向量插入（三路分支 + 1.5 倍扩容）
{
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v14; // edi
  int fld_e14; // eax
  int fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-98h]
  int fld_e28; // [esp-10h] [ebp-90h]
  int fld_e25; // [esp-Ch] [ebp-8Ch]
  unsigned int fld_e24; // [esp-8h] [ebp-88h]
  int v23; // [esp+0h] [ebp-80h] BYREF
  void *Block; // [esp+Ch] [ebp-74h]
  int *pThis; // [esp+10h] [ebp-70h]
  char *pMem2; // [esp+14h] [ebp-6Ch]
  uint8_t v27[52]; // [esp+18h] [ebp-68h] BYREF
  void *v28; // [esp+4Ch] [ebp-34h]
  unsigned int v29; // [esp+60h] [ebp-20h]
  int dword_796E502; // [esp+6Ch] [ebp-14h]
  int *v31; // [esp+70h] [ebp-10h]
  int v32; // [esp+7Ch] [ebp-4h]
  int v33; // [esp+88h] [ebp+8h]
  int v34; // [esp+8Ch] [ebp+Ch]
  int fld_e232; // [esp+90h] [ebp+10h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v31 = &v23;
  pThis = this;
  sub_4F9470(nArg4);  // 84 字节元素拷贝构造（+48 串槽深拷贝）
  fld_e1 = *(this + 1);  // fld_e1 = this+1
  fld_e3 = 0;
  v32 = 0;
  if ( fld_e1 != 0 )  // 若 fld_e1 != 0
    fld_e3 = (*(this + 3) - fld_e1) / 84;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e2 = (*(this + 2) - fld_e1) / 84;
    else
      fld_e2 = 0;
    if ( 51130563 - fld_e2 < uArg3 )  // 若 51130563 - fld_e2 < uArg3
      sub_4F9570(this);  // vector 超长异常（length_error，不返回）
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e22 = (*(this + 2) - fld_e1) / 84;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )  // 若 fld_e3 >= uArg3 + fld_e22
    {
      fld_e23 = *(this + 2);  // fld_e23 = this+2
      fld_e232 = fld_e23;
      if ( (fld_e23 - pArg2) / 84 >= uArg3 )  // 若 (fld_e23 - pArg2) / 84 >= uArg3
      {
        v33 = fld_e23 - 84 * uArg3;
        *(this + 2) = sub_4F96A0(v33, fld_e23, fld_e23);  // 84 字节元素正向拷贝构造（源区间 → 新缓冲）
        sub_4F9CF0(pArg2, v33, fld_e232);  // 薄封装（转 4F9660 反向搬移）
        sub_4F9CC0(pArg2, pArg2 + 84 * uArg3, v27);  // 84 字节元素正向批量赋值（同源复制）
      }
      else
      {
        sub_4F96A0(pArg2, fld_e23, pArg2 + 84 * uArg3);  // 84 字节元素正向拷贝构造（源区间 → 新缓冲）
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 84;
        fld_e25 = *(this + 2);  // fld_e25 = this+2
        LOBYTE(v32) = 3;
        sub_4FA1B0(fld_e25, fld_e24, v27);  // 84 字节元素填充 + 返回尾址（组合器）
        fld_e26 = 84 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8 = fld_e26
        v32 = 0;
        sub_4F9CC0(pArg2, fld_e26 - 84 * uArg3, v27);  // 84 字节元素正向批量赋值（同源复制）
      }
    }
    else
    {
      if ( 51130563 - (fld_e3 >> 1) >= fld_e3 )  // 若 51130563 - (fld_e3 >> 1) >= fld_e3
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )  // 若 fld_e1 != 0
        fld_e27 = (*(this + 2) - fld_e1) / 84;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )  // 若 v10 < uArg3 + fld_e27
        v10 = uArg3 + sub_4F8D70(this);  // 结果 = 84 字节元素向量长度（(end−begin)/84）
      v34 = 84 * v10;
      pMem = (char *)operator new(84 * v10);
      fld_e12 = *(this + 1);  // fld_e12 = this+1
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v32) = 1;
      pMem2 = (char *)sub_4F96A0(fld_e12, pArg2, pMem);  // 结果 = 84 字节元素正向拷贝构造（源区间 → 新缓冲）
      sub_4F9E90(pMem2, uArg3, v27);  // 84 字节元素填充构造（nArg2 个副本自 nArg3）
      fld_e28 = *(this + 2);  // fld_e28 = this+2
      pMem2 += 84 * uArg3;
      sub_4F96A0(pArg2, fld_e28, pMem2);  // 84 字节元素正向拷贝构造（源区间 → 新缓冲）
      fld_e13 = *(this + 1);  // fld_e13 = this+1
      if ( fld_e13 != 0 )  // 若 fld_e13 != 0
        fld_e13 = (*(this + 2) - fld_e13) / 84;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);  // fld_e14 = this+1
      if ( fld_e14 != 0 )  // 若 fld_e14 != 0
      {
        sub_4FA1E0(fld_e14, *(this + 2));  // 84 字节元素区间析构（逐槽 44C0C0）
        j__free((void *)*(this + 1));  // 调 j__free
      }
      *(this + 3) = (int)&pMem[v34];  // this+12 = (int)&pMem[v34]
      *(this + 2) = (int)&pMem[84 * v14];  // this+8 = (int)&pMem[84 * v14]
      *(this + 1) = (int)pMem;  // this+4 = (int)pMem
    }
  }
  if ( v29 >= 0x10 )  // 若 v29 >= 0x10
    j__free(v28);  // 调 j__free
}


// ------------------------------------------------------------
// 0x4FA510 sub_4FA510 —— 20 字节元素正向填充（同源复制）
//   每步 +20：两半字直拷、+4 子向量经 ·0x4F9D10；配 ·0x4FA070 反向版。
// ------------------------------------------------------------
uint16_t */*cdecl*/ sub_4FA510(uint16_t *uArg1, uint16_t *uArg2, uint16_t *pArg3)  // 20 字节元素正向填充（同源复制）
{
  uint16_t *result; // eax
  uint16_t *i; // esi

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 10 )  // 循环：i = uArg1; i != uArg2; i += 10
  {
    *i = *pArg3;  // *i 写入 *pArg3
    i[1] = pArg3[1];  // i[1] 写入 pArg3[1]
    sub_4F9D10((int)(i + 2), (int)(pArg3 + 2));  // 44 字节元素向量赋值（容量三路分支）
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FA550 sub_4FA550 —— 薄封装（转 4FA070 反向搬移）
//   参数直通 sub_4FA070，供插入路径统一入口。
// ------------------------------------------------------------
uint16_t */*cdecl*/ sub_4FA550(int nArg1, int nArg2, uint16_t *uArg3)  // 薄封装（转 4FA070 反向搬移）
{
  return sub_4FA070(nArg1, nArg2, uArg3);  // 20 字节元素反向搬移（双半字 + 44B 子向量）
}



// ------------------------------------------------------------
// 0x4FA570 sub_4FA570 —— 20 字节元素反向搬移构造（子向量 4F9C20）
//   每步 -20：两半字直拷、+4 子向量经 sub_4F9C20 拷贝构造；异常展开标记。
// ------------------------------------------------------------
int /*cdecl*/ sub_4FA570(uint16_t *pArg1, uint16_t *uArg2, int nArg3)  // 函数: 20 字节元素反向搬移构造（子向量 4F9C20）
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != uArg2 )  // 当 pArg1 != uArg2 循环
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )  // 若 nArg32 != 0
    {
      *(uint16_t *)nArg32 = *pArg1;
      *(uint16_t *)(nArg32 + 2) = pArg1[1];  // nArg32+2 = pArg1[1]
      sub_4F9C20((uint32_t *)(nArg32 + 4), (int)(pArg1 + 2));  // 44 字节元素向量区间拷贝赋值
    }
    nArg32 += 20;
    LOBYTE(v7) = 0;
    pArg1 += 10;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x4FA630 sub_4FA630 —— 表情(emoticon)标签表解析器
//   标签族：[EMOTICON TAG]（$END 结尾的标签映射表）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FA630(int nArg1)  // 函数: 表情(emoticon)标签表解析器
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
  int dword_796E502; // [esp+28h] [ebp-10h]
  int v16; // [esp+34h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = sub_442A10((char)szPassword, nArg1);  // 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result != 0 )  // 若 result != 0
  {
    v14 = 15;
    v13 = 0;
    LOBYTE(Block) = 0;
    v16 = 0;
    v10 = nullptr;  // v10 = nullptr 空指针
    sub_41BFE0(&v10, szPassword);  // 调 驻留字符串设置
    LOBYTE(v16) = 1;
    while ( (uint8_t)sub_443430(v11) != 0 )  // 当 (uint8_t)sub_443430(v11) != 0 循环
    {
      if ( sub_40BF00((std::_String_base *)v11, 0, v13, "[EMOTICON TAG]", 0xEu) == 0 )  // 字符串 “[EMOTICON TAG]”
      {
        v2 = (void ***)&unk_9B7D24;
        v9 = (void ***)&unk_9B7D24;
        do
        {
          v3 = *v2;
          v4 = v2 - 1;
          if ( *v2 != nullptr )  // 若 *v2 != nullptr
          {
            for ( i = v2[1]; v3 != i; ++v3 )  // 循环：i = v2[1]; v3 != i; ++v3
              sub_41B010(v3);  // 驻留句柄析构（引用计数减到 0 释放）
            j__free(*v2);  // 调 j__free
          }
          *v2 = nullptr;  // *v2 写入 nullptr
          v4[2] = nullptr;  // v4[2] = nullptr 空指针
          v4[3] = nullptr;  // v4[3] = nullptr 空指针
          if ( sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
          {
            while ( 1 )  // 当 1 循环
            {
              v5 = *v2;
              v6 = *v2 != nullptr ? v4[2] - v5 : 0;
              if ( v5 != nullptr && v6 < v4[3] - v5 )  // 若 v5 != nullptr && v6 < v4[3] - v5
              {
                v7 = v4[2];
                sub_41FFE0(v7, 1, &v10);  // 驻留句柄区间填充 nArg2 个元素
                v4[2] = v7 + 1;  // v4[2] 写入 v7 + 1
              }
              else
              {
                sub_4206D0(v4[2], 1, &v10);  // vector 中间插入（4 字节元素）
              }
              if ( strcmp((const char *)sub_41ACF0(&v10), "$END") == 0 || sub_442E10() == 0 )  // 字符串 “$END”
                break;
              v2 = v9;
            }
            v2 = v9;
          }
          v2 += 4;
          v9 = v2;
        }
        while ( (int)v2 < (int)&dword_9B7E94 );  // 当 (int)v2 < (int)&dword_9B7E94 循环
      }
    }
    LOBYTE(v16) = 0;
    sub_41B010(&v10);  // 驻留句柄析构（引用计数减到 0 释放）
    if ( v14 >= 0x10 )  // 若 v14 >= 0x10
      j__free(Block);  // 调 j__free
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FA820 sub_4FA820 —— 玩家俚语/屏蔽词表解析器
//   标签族：[SLANG]。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FA820(int nArg1, uint32_t *pArg2)  // 函数: 玩家俚语/屏蔽词表解析器
{
  char result; // al
  int v3; // ecx
  const char *p_Block; // esi
  int nCmp; // eax
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
  int dword_796E502; // [esp+24h] [ebp-10h]
  int v19; // [esp+30h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = sub_442A10((char)szPassword, nArg1);  // 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result != 0 )  // 若 result != 0
  {
    v17 = 15;
    v16 = 0;
    LOBYTE(Block) = 0;
    v19 = 0;
    v12 = nullptr;  // v12 = nullptr 空指针
    sub_41BFE0(&v12, szPassword);  // 调 驻留字符串设置
    LOBYTE(v19) = 1;
    v13 = nullptr;  // v13 = nullptr 空指针
    sub_41BFE0(&v13, szPassword);  // 调 驻留字符串设置
    LOBYTE(v19) = 2;
    while ( (uint8_t)sub_443430(v14) != 0 )  // 当 (uint8_t)sub_443430(v14) != 0 循环
    {
      if ( v16 != 0 )  // 若 v16 != 0
      {
        v3 = v16;
        if ( v16 >= 7 )  // 若 v16 >= 7
          v3 = 7;
        p_Block = (const char *)Block;
        if ( v17 < 0x10 )  // 若 v17 < 0x10
          p_Block = (const char *)&Block;
        nCmp = memcmp(p_Block, "[SLANG]", v3);  // 字符串 “[SLANG]”
        if ( nCmp == 0 && v16 >= 7 )  // 若 nCmp == 0 && v16 >= 7
        {
          LOBYTE(nCmp) = v16 != 7;
          if ( nCmp == 0 && sub_442E10() != 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
          {
            do
            {
              if ( sub_442E10() == 0 )  // 【RDARScriptStringManager 入口（::ERROR::input…】
                break;
              v6 = pArg2[1];
              v7 = v6 != 0 ? (pArg2[2] - v6) >> 2 : 0;
              if ( v6 != 0 && v7 < (pArg2[3] - v6) >> 2 )  // 若 v6 != 0 && v7 < (pArg2[3] - v6) >> 2
              {
                v8 = pArg2[2];
                sub_41FFE0(v8, 1, &v12);  // 驻留句柄区间填充 nArg2 个元素
                pArg2[2] = v8 + 4;  // pArg2[2] 写入 v8 + 4
              }
              else
              {
                sub_4206D0(pArg2[2], 1, &v12);  // vector 中间插入（4 字节元素）
              }
              v9 = pArg2[1];
              v10 = v9 != 0 ? (pArg2[2] - v9) >> 2 : 0;
              if ( v9 != 0 && v10 < (pArg2[3] - v9) >> 2 )  // 若 v9 != 0 && v10 < (pArg2[3] - v9) >> 2
              {
                v11 = pArg2[2];
                sub_41FFE0(v11, 1, &v13);  // 驻留句柄区间填充 nArg2 个元素
                pArg2[2] = v11 + 4;  // pArg2[2] 写入 v11 + 4
              }
              else
              {
                sub_4206D0(pArg2[2], 1, &v13);  // vector 中间插入（4 字节元素）
              }
            }
            while ( sub_442E10() != 0 );  // 【RDARScriptStringManager 入口（::ERROR::input…】
          }
        }
      }
    }
    LOBYTE(v19) = 1;
    sub_41B010(&v13);  // 驻留句柄析构（引用计数减到 0 释放）
    LOBYTE(v19) = 0;
    sub_41B010(&v12);  // 驻留句柄析构（引用计数减到 0 释放）
    if ( v17 >= 0x10 )  // 若 v17 >= 0x10
      j__free(Block);  // 调 j__free
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FAA40 sub_4FAA40 —— 封印(解封)概率表解析器（importResealTable）
//   标签族：[rarity weight]（稀有度权重表）/[extended rarity weight]（扩展表）/[grade]。
//   校验失败 → "importResealTable - invalid extended rarity table"/"... rarity table"。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FAA40(int nArg1, int pArg2)  // 函数: 封印(解封)概率表解析器（importResealTable）
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
  int dword_796E502; // [esp+60h] [ebp-10h]
  int v27; // [esp+6Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = sub_442A10((char)szPassword, nArg1);  // 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result != 0 )  // 若 result != 0
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
    while ( (uint8_t)sub_443430(v22) != 0 )  // 当 (uint8_t)sub_443430(v22) != 0 循环
    {
      if ( sub_40BF00((std::_String_base *)v22, 0, v24, "[rarity weight]", 0xFu) != 0 )  // 字符串 “[rarity weight]”
      {
        if ( sub_40BF00((std::_String_base *)v22, 0, v24, "[extended rarity weight]", 0x18u) != 0 )  // 字符串 “[extended rarity weight]”
        {
          if ( sub_40BF00((std::_String_base *)v22, 0, v24, "[grade]", 7u) == 0 )  // 字符串 “[grade]”
          {
            for ( i = sub_4423D0(v16); v16[0] != 0; i = sub_4423D0(v16) )  // 循环：i = sub_4423D0(v16); v16[0] != 0; i = sub_4423D0(v16)
            {
              v10 = *(uint32_t *)(pArg2 + 4);  // v10 = pArg2+4
              v15 = i;
              if ( v10 != 0 )  // 若 v10 != 0
                v11 = (*(uint32_t *)(pArg2 + 8) - v10) >> 2;
              else
                v11 = 0;
              if ( v10 != 0 && v11 < (*(uint32_t *)(pArg2 + 12) - v10) >> 2 )  // 若 v10 != 0 && v11 < (*(uint32_t *)(pArg2 + 12) - v10) >> 2
              {
                v12 = *(int **)(pArg2 + 8);
                *v12 = i;  // *v12 写入 i
                *(uint32_t *)(pArg2 + 8) = v12 + 1;  // pArg2+8 = v12 + 1
              }
              else
              {
                sub_4F9A40(*(void **)(pArg2 + 8), 1, (int)&v15);  // 与 ·0x4F44C0 同构（差异：超长抛 sub_4F9570 而非 4F43D0）
              }
            }
          }
        }
        else
        {
          v6 = (int *)(pArg2 + 36);
          v15 = 5;
          do
          {
            v7 = sub_4423D0(&v13);  // 调 sub_4423D0
            if ( v13 == 0 )  // 若 v13 == 0
              off_77F3FC("importResealTable - invalid extended rarity table");  // 字符串 “importResealTable - invalid extended rarity ”
            v8 = v15;
            *v6++ = v7;  // *v6++ 写入 v7
            v15 = v8 - 1;
          }
          while ( v8 != 1 );  // 当 v8 != 1 循环
        }
      }
      else
      {
        v3 = (int *)(pArg2 + 16);
        v15 = 5;
        do
        {
          v4 = sub_4423D0(&v14);  // 调 sub_4423D0
          if ( v14 == 0 )  // 若 v14 == 0
            off_77F3FC("importResealTable - invalid rarity table");  // 字符串 “importResealTable - invalid rarity table”
          v5 = v15;
          *v3++ = v4;  // *v3++ 写入 v4
          v15 = v5 - 1;
        }
        while ( v5 != 1 );  // 当 v5 != 1 循环
      }
    }
    if ( v25 >= 0x10 )  // 若 v25 >= 0x10
      j__free(Block);  // 调 j__free
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FAC40 sub_4FAC40 —— 强化(upgrade)费用表解析器（importUpgradeTable）
//   标签族：[table]（费用表本体）/[rarity]（稀有度分组）/[type]（类型分组）/[cost]/[notice]。
//   校验失败 → "importUpgradeTable - invalid notice tag"/"... gold table"/"... type table"。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FAC40(int nArg1, int pArg2)  // 函数: 强化(upgrade)费用表解析器（importUpgradeTable）
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
  int dword_796E502; // [esp+8Ch] [ebp-10h]
  int v38; // [esp+98h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = sub_442A10((char)szPassword, nArg1);  // 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result != 0 )  // 若 result != 0
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
    while ( (uint8_t)sub_443430(v33) != 0 )  // 当 (uint8_t)sub_443430(v33) != 0 循环
    {
      if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[table]", 7u) != 0 )  // 字符串 “[table]”
      {
        if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[rarity]", 8u) != 0 )  // 字符串 “[rarity]”
        {
          if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[type]", 6u) != 0 )  // 字符串 “[type]”
          {
            if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[cost]", 6u) != 0 )  // 字符串 “[cost]”
            {
              if ( (uint8_t)sub_423300(v33, "[notice]") != 0 )  // 字符串 “[notice]”
              {
                v22 = COERCE_FLOAT(sub_4423D0(&v26));
                if ( v26 == 0 )  // 若 v26 == 0
                  off_77F3FC("importUpgradeTable - invalid notice tag");  // 字符串 “importUpgradeTable - invalid notice tag”
                *(uint8_t *)(pArg2 + 520) = LOBYTE(v22);  // pArg2+520 = LOBYTE(v22)
              }
            }
            else
            {
              v7 = (int *)(pArg2 + 120);
              for ( i = 100; i != 0; --i )  // 循环：i = 100; i != 0; --i
              {
                v9 = sub_4423D0(&v25);  // 调 sub_4423D0
                if ( v25 == 0 )  // 若 v25 == 0
                  off_77F3FC("importUpgradeTable - invalid gold table");  // 字符串 “importUpgradeTable - invalid gold table”
                *v7++ = v9;  // *v7++ 写入 v9
              }
            }
          }
          else
          {
            v5 = (float *)(pArg2 + 60);
            for ( j = 10; j != 0; --j )  // 循环：j = 10; j != 0; --j
            {
              v22 = sub_442480(&v23);  // 结果 = 脚本 token 数值解析（double 版）
              if ( v23 == 0 )  // 若 v23 == 0
                off_77F3FC("importUpgradeTable - invalid type table");  // 字符串 “importUpgradeTable - invalid type table”
              *v5++ = v22;  // *v5++ 写入 v22
            }
          }
        }
        else
        {
          v3 = (float *)(pArg2 + 100);
          for ( k = 5; k != 0; --k )  // 循环：k = 5; k != 0; --k
          {
            v22 = sub_442480(&v24);  // 结果 = 脚本 token 数值解析（double 版）
            if ( v24 == 0 )  // 若 v24 == 0
              off_77F3FC("importUpgradeTable - invalid rarity table");  // 字符串 “importUpgradeTable - invalid rarity table”
            *v3++ = v22;  // *v3++ 写入 v22
          }
        }
      }
      else
      {
        if ( *(uint32_t *)(pArg2 + 4) != 0 )  // 若 *(uint32_t *)(pArg2 + 4) != 0
          j__free(*(void **)(pArg2 + 4));  // 调 j__free
        *(uint32_t *)(pArg2 + 4) = 0;  // pArg2+4 = 0
        *(uint32_t *)(pArg2 + 8) = 0;  // pArg2+8 = 0
        *(uint32_t *)(pArg2 + 12) = 0;  // pArg2+12 = 0
        while ( 1 )  // 当 1 循环
        {
          v11 = 0;
          v12 = 0;
          v16 = 0;
          v17 = 0;
          v19 = 0;
          v20 = 0;
          v21 = 0;
          v10 = sub_4423D0(v27);  // 调 sub_4423D0
          if ( v27[0] == 0 )  // 若 v27[0] == 0
            break;
          v13 = 0;
          v11 = sub_4423D0(v27);  // 调 sub_4423D0
          if ( v27[0] == 0 )  // 若 v27[0] == 0
            break;
          v14 = 0;
          v12 = sub_4423D0(v27);  // 调 sub_4423D0
          if ( v27[0] == 0 )  // 若 v27[0] == 0
            break;
          v15 = 0;
          v16 = sub_4423D0(v27);  // 调 sub_4423D0
          v17 = sub_4423D0(v27);  // 调 sub_4423D0
          v18 = sub_4423D0(v27);  // 调 sub_4423D0
          v19 = sub_4423D0(v27);  // 调 sub_4423D0
          v20 = sub_4423D0(v27);  // 调 sub_4423D0
          v21 = 0;
          sub_4FA120(&v10);  // 44 字节元素尾插（满则 4FA000）
        }
      }
    }
    if ( v36 >= 0x10 )  // 若 v36 >= 0x10
      j__free(Block);  // 调 j__free
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FAF80 sub_4FAF80 —— 84 字节元素单点插入（返回新址）
//   记录索引 → ·0x4FA210 扩一 → 新址回写 uArg2。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FAF80(int *this, uint32_t *uArg2, char *pszArg3, int nArg4)  // 84 字节元素单点插入（返回新址）
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 84 != 0 )  // 若 fld_e1 != 0 && (*(this + 2) - fld_e1) / 84 != 0
    v6 = (int)&pszArg3[-fld_e1] / 84;
  else
    v6 = 0;
  sub_4FA210(this, pszArg3, 1u, nArg4);  // 84 字节元素向量插入（三路分支 + 1.5 倍扩容）
  *uArg2 = *(this + 1) + 84 * v6;  // *uArg2 写入 *(this + 1) + 84 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x4FAFF0 sub_4FAFF0 —— 84 字节元素向量析构（44C0C0 逐槽 + 释放）
//   逐槽 sub_44C0C0 后 free this[1] 并清零三字段。
// ------------------------------------------------------------
int /*thiscall*/ sub_4FAFF0(int *this)  // 函数: 84 字节元素向量析构（44C0C0 逐槽 + 释放）
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  result = 0;
  if ( fld_e1 != 0 )  // 若 fld_e1 != 0
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 84 )  // 循环：i = *(this + 2); fld_e1 != i; fld_e1 += 84
      sub_44C0C0(fld_e1);  // 单字符串元素析构
    j__free((void *)*(this + 1));  // 调 j__free
    result = 0;
  }
  *(this + 1) = 0;  // this+4 = 0
  *(this + 2) = 0;  // this+8 = 0
  *(this + 3) = 0;  // this+12 = 0
  return result;
}



// ------------------------------------------------------------
// 0x4FB030 sub_4FB030 —— 20 字节元素填充构造（nArg2 个副本自 pArg3）
//   逐次构造：两半字直拷、+4 子向量经 sub_4F9C20；异常展开标记。
// ------------------------------------------------------------
void /*cdecl*/ sub_4FB030(int nArg1, int nArg2, uint16_t *pArg3)  // 函数: 20 字节元素填充构造（nArg2 个副本自 pArg3）
{
  int nArg12; // esi
  uint32_t v5[5]; // [esp+0h] [ebp-20h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  nArg12 = nArg1;
  v5[4] = v5;
  v5[3] = nArg1;
  v6 = 0;
  while ( nArg2 != 0 )  // 当 nArg2 != 0 循环
  {
    LOBYTE(v6) = 1;
    if ( nArg12 != 0 )  // 若 nArg12 != 0
    {
      *(uint16_t *)nArg12 = *pArg3;
      *(uint16_t *)(nArg12 + 2) = pArg3[1];  // nArg12+2 = pArg3[1]
      sub_4F9C20((uint32_t *)(nArg12 + 4), (int)(pArg3 + 2));  // 44 字节元素向量区间拷贝赋值
    }
    --nArg2;  // 自减nArg2
    nArg12 += 20;
    LOBYTE(v6) = 0;
  }
}



// ------------------------------------------------------------
// 0x4FB0F0 sub_4FB0F0 —— 84 字节元素尾插（满则 4FAF80）
//   有余量 sub_4F9E90 就地构造 +84 递增，否则 ·0x4FAF80。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FB0F0(int this, int nArg2)  // 84 字节元素尾插（满则 4FAF80）
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 84;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 84 )  // 若 fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 84
    return sub_4FAF80((int *)this, &nArg2, *(char **)(this + 8), nArg2);  // 84 字节元素单点插入（返回新址）
  fld_82 = *(uint32_t **)(this + 8);
  result = sub_4F9E90(fld_82, 1, nArg2);  // 结果 = 84 字节元素填充构造（nArg2 个副本自 nArg3）
  *(uint32_t *)(this + 8) = fld_82 + 21;  // this+8 = fld_82 + 21
  return result;
}



// ------------------------------------------------------------
// 0x4FB180 sub_4FB180 —— 时装(avatar)分配表解析器
//   标签族：部位分配 [npc info]/[avatar]/[coin]/[item]。
// ------------------------------------------------------------
char /*cdecl*/ sub_4FB180(int nArg1, int pArg2)  // 函数: 时装(avatar)分配表解析器
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
  int dword_796E502; // [esp+138h] [ebp-10h]
  int v38; // [esp+144h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = sub_442A10((char)szPassword, nArg1);  // 结果 = 脚本载入调度（PVF 或磁盘）
  if ( result != 0 )  // 若 result != 0
  {
    v36 = 15;
    v35 = 0;
    LOBYTE(v34) = 0;
    v38 = 1;
    v32 = 15;
    v31 = 0;
    LOBYTE(v30) = 0;
    v7 = 0;
    while ( (uint8_t)sub_443430(v33) != 0 )  // 当 (uint8_t)sub_443430(v33) != 0 循环
    {
      sub_442B20(v33);  // 国家码标签配对校验（void）
      if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[npc info]", 0xAu) != 0 )  // 字符串 “[npc info]”
      {
        if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[avatar]", 8u) != 0 )  // 字符串 “[avatar]”
        {
          if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[coin]", 6u) != 0 )  // 字符串 “[coin]”
          {
            if ( sub_40BF00((std::_String_base *)v33, 0, v35, "[item]", 6u) == 0 )  // 字符串 “[item]”
            {
              sub_4FAFF0(pArg2 + 32);  // 84 字节元素向量析构（44C0C0 逐槽 + 释放）
              for ( i = sub_4423D0(&v7); v7 != 0; i = sub_4423D0(&v7) )  // 循环：i = sub_4423D0(&v7); v7 != 0; i = sub_4423D0(&v7)
              {
                sub_44CEA0(v22);  // 槽位记录全量初始化（含内嵌 std::string 置空）
                LOBYTE(v38) = 4;
                v22[0] = i;
                v22[3] = sub_4423D0(nullptr);  // 调 sub_4423D0
                v22[5] = sub_4423D0(nullptr);  // 调 sub_4423D0
                v24 = sub_4423D0(nullptr);  // 调 sub_4423D0
                v25 = sub_4423D0(nullptr);  // 调 sub_4423D0
                v26 = sub_4423D0(nullptr);  // 调 sub_4423D0
                sub_443370();  // 脚本 token 取串（第三入口）
                v23 = sub_4423D0(nullptr);  // 调 sub_4423D0
                v22[2] = sub_4423D0(nullptr);  // 调 sub_4423D0
                v24 += 10 * v26;
                v26 = 0;
                v22[1] = 2;
                sub_4FB0F0(v22);  // 84 字节元素尾插（满则 4FAF80）
                LOBYTE(v38) = 1;
                if ( v29 >= 0x10 )  // 若 v29 >= 0x10
                  j__free(v27);  // 调 j__free
                v29 = 15;
                v28 = 0;
                LOBYTE(v27) = 0;
              }
            }
          }
          else
          {
            sub_4FAFF0(pArg2 + 16);  // 84 字节元素向量析构（44C0C0 逐槽 + 释放）
            for ( j = sub_4423D0(&v7); v7 != 0; j = sub_4423D0(&v7) )  // 循环：j = sub_4423D0(&v7); v7 != 0; j = sub_4423D0(&v7)
            {
              sub_44CEA0(v15);  // 槽位记录全量初始化（含内嵌 std::string 置空）
              LOBYTE(v38) = 3;
              v15[0] = j;
              v15[3] = sub_4423D0(nullptr);  // 调 sub_4423D0
              v15[5] = sub_4423D0(nullptr);  // 调 sub_4423D0
              v16 = sub_4423D0(nullptr);  // 调 sub_4423D0
              v17 = sub_4423D0(nullptr);  // 调 sub_4423D0
              v18 = sub_4423D0(nullptr);  // 调 sub_4423D0
              sub_443370();  // 脚本 token 取串（第三入口）
              v15[2] = sub_4423D0(nullptr);  // 调 sub_4423D0
              v16 += 10 * v18;
              v18 = 0;
              v15[1] = 1;
              sub_4FB0F0(v15);  // 84 字节元素尾插（满则 4FAF80）
              LOBYTE(v38) = 1;
              if ( v21 >= 0x10 )  // 若 v21 >= 0x10
                j__free(v19);  // 调 j__free
              v21 = 15;
              v20 = 0;
              LOBYTE(v19) = 0;
            }
          }
        }
        else
        {
          sub_4FAFF0(pArg2);  // 84 字节元素向量析构（44C0C0 逐槽 + 释放）
          for ( k = sub_4423D0(&v7); v7 != 0; k = sub_4423D0(&v7) )  // 循环：k = sub_4423D0(&v7); v7 != 0; k = sub_4423D0(&v7)
          {
            sub_44CEA0(v8);  // 槽位记录全量初始化（含内嵌 std::string 置空）
            LOBYTE(v38) = 2;
            v8[0] = k;
            v8[3] = sub_4423D0(nullptr);  // 调 sub_4423D0
            v10 = sub_4423D0(nullptr);  // 调 sub_4423D0
            v9 = sub_4423D0(nullptr);  // 调 sub_4423D0
            v8[2] = sub_4423D0(nullptr);  // 调 sub_4423D0
            v11 = sub_4423D0(nullptr);  // 调 sub_4423D0
            v8[1] = 0;
            v8[5] = 1;
            sub_4FB0F0(v8);  // 84 字节元素尾插（满则 4FAF80）
            LOBYTE(v38) = 1;
            if ( v14 >= 0x10 )  // 若 v14 >= 0x10
              j__free(Block);  // 调 j__free
            v14 = 15;
            v13 = 0;
            LOBYTE(Block) = 0;
          }
        }
      }
      else
      {
        for ( m = 4; m != 0; --m )  // 循环：m = 4; m != 0; --m
        {
          sub_443370();  // 脚本 token 取串（第三入口）
          sub_4423D0(nullptr);  // 调 sub_4423D0
        }
      }
    }
    if ( v32 >= 0x10 )  // 若 v32 >= 0x10
      j__free(v30);  // 调 j__free
    v32 = 15;
    v31 = 0;
    LOBYTE(v30) = 0;
    if ( v36 >= 0x10 )  // 若 v36 >= 0x10
      j__free(v34);  // 调 j__free
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4FB630 sub_4FB630 —— 20 字节元素填充 + 返回尾址（组合器）
//   sub_4FB030 填充后返回 nArg1 + 20×nArg2。
// ------------------------------------------------------------
int /*stdcall*/ sub_4FB630(int nArg1, int nArg2, uint16_t *uArg3)  // 函数: 20 字节元素填充 + 返回尾址（组合器）
{
  sub_4FB030(nArg1, nArg2, uArg3);  // 20 字节元素填充构造（nArg2 个副本自 pArg3）
  return nArg1 + 20 * nArg2;
}



// ------------------------------------------------------------
// 0x4FB660 sub_4FB660 —— 20 字节元素向量插入（三路分支 + 1.5 倍扩容）
//   就地 sub_4FA570/sub_4FA550/sub_4FA510；重建经 operator new + sub_4FA570/sub_4FB030 与
//   sub_42E670 析构旧段；超限 sub_42CB90。
// ------------------------------------------------------------
void /*thiscall*/ sub_4FB660(int *this, char *pszArg2, unsigned int uArg3, int16_t *pArg4)  // 函数: 20 字节元素向量插入（三路分支 + 1.5 倍扩容）
{
  int16_t v4; // dx
  int16_t v6; // cx
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v12; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v16; // edi
  void *fld_e14; // eax
  char *fld_e23; // ecx
  int fld_e26; // edi
  uint16_t *fld_e12; // [esp-18h] [ebp-50h]
  int fld_e25; // [esp-Ch] [ebp-44h]
  unsigned int fld_e24; // [esp-8h] [ebp-40h]
  int v24; // [esp+0h] [ebp-38h] BYREF
  uint16_t v25[2]; // [esp+Ch] [ebp-2Ch] BYREF
  int v26; // [esp+10h] [ebp-28h] BYREF
  void *v27; // [esp+14h] [ebp-24h]
  void *Block; // [esp+20h] [ebp-18h]
  int *pThis; // [esp+24h] [ebp-14h]
  int *v30; // [esp+28h] [ebp-10h]
  int v31; // [esp+34h] [ebp-4h]
  char *v32; // [esp+40h] [ebp+8h]
  int v33; // [esp+44h] [ebp+Ch]
  int v34; // [esp+48h] [ebp+10h]
  char *fld_e232; // [esp+48h] [ebp+10h]

  v4 = pArg4[1];
  v6 = *pArg4;
  v30 = &v24;
  v25[0] = v6;
  pThis = this;
  v25[1] = v4;
  sub_4F9C20(&v26, (int)(pArg4 + 2));  // 44 字节元素向量区间拷贝赋值
  fld_e1 = *(this + 1);  // fld_e1 = this+1
  fld_e3 = 0;
  v31 = 0;
  if ( fld_e1 != 0 )  // 若 fld_e1 != 0
    fld_e3 = (*(this + 3) - fld_e1) / 20;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e2 = (*(this + 2) - fld_e1) / 20;
    else
      fld_e2 = 0;
    if ( 214748364 - fld_e2 < uArg3 )  // 若 214748364 - fld_e2 < uArg3
      sub_42CB90(this);  // CRT 桩（vector 长度异常）
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e22 = (*(this + 2) - fld_e1) / 20;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )  // 若 fld_e3 >= uArg3 + fld_e22
    {
      fld_e23 = (char *)*(this + 2);
      fld_e232 = fld_e23;
      if ( (fld_e23 - pszArg2) / 20 >= uArg3 )  // 若 (fld_e23 - pszArg2) / 20 >= uArg3
      {
        v32 = &fld_e23[-20 * uArg3];
        *(this + 2) = sub_4FA570(v32, fld_e23, (int)fld_e23);  // 20 字节元素反向搬移构造（子向量 4F9C20）
        sub_4FA550(pszArg2, v32, fld_e232);  // 薄封装（转 4FA070 反向搬移）
        sub_4FA510(pszArg2, &pszArg2[20 * uArg3], v25);  // 20 字节元素正向填充（同源复制）
      }
      else
      {
        sub_4FA570(pszArg2, fld_e23, (int)&pszArg2[20 * uArg3]);  // 20 字节元素反向搬移构造（子向量 4F9C20）
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 20;
        fld_e25 = *(this + 2);  // fld_e25 = this+2
        LOBYTE(v31) = 3;
        sub_4FB630(fld_e25, fld_e24, v25);  // 20 字节元素填充 + 返回尾址（组合器）
        fld_e26 = 20 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8 = fld_e26
        v31 = 0;
        sub_4FA510(pszArg2, fld_e26 - 20 * uArg3, v25);  // 20 字节元素正向填充（同源复制）
      }
    }
    else
    {
      if ( 214748364 - (fld_e3 >> 1) >= fld_e3 )  // 若 214748364 - (fld_e3 >> 1) >= fld_e3
        v12 = (fld_e3 >> 1) + fld_e3;
      else
        v12 = 0;
      if ( fld_e1 != 0 )  // 若 fld_e1 != 0
        fld_e27 = (*(this + 2) - fld_e1) / 20;
      else
        fld_e27 = 0;
      if ( v12 < uArg3 + fld_e27 )  // 若 v12 < uArg3 + fld_e27
        v12 = uArg3 + sub_45E580(this);  // 结果 = 容器计数（跨度 / 20）
      v34 = 20 * v12;
      pMem = (char *)operator new(20 * v12);
      fld_e12 = (uint16_t *)*(this + 1);
      Block = pMem;
      LOBYTE(v31) = 1;
      v33 = sub_4FA570(fld_e12, pszArg2, (int)pMem);  // 结果 = 20 字节元素反向搬移构造（子向量 4F9C20）
      sub_4FB030(v33, uArg3, v25);  // 20 字节元素填充构造（nArg2 个副本自 pArg3）
      sub_4FA570(pszArg2, (uint16_t *)*(this + 2), v33 + 20 * uArg3);  // 20 字节元素反向搬移构造（子向量 4F9C20）
      fld_e13 = *(this + 1);  // fld_e13 = this+1
      if ( fld_e13 != 0 )  // 若 fld_e13 != 0
        fld_e13 = (*(this + 2) - fld_e13) / 20;
      v16 = fld_e13 + uArg3;
      fld_e14 = (void *)*(this + 1);
      if ( fld_e14 != nullptr )  // 若 fld_e14 非空
      {
        sub_42E670(fld_e14, *(this + 2));  // 20 字节条目组析构
        j__free((void *)*(this + 1));  // 调 j__free
      }
      *(this + 3) = (int)&pMem[v34];  // this+12 = (int)&pMem[v34]
      *(this + 2) = (int)&pMem[20 * v16];  // this+8 = (int)&pMem[20 * v16]
      *(this + 1) = (int)pMem;  // this+4 = (int)pMem
    }
  }
  if ( v27 != nullptr )  // 若 v27 非空
    j__free(v27);  // 调 j__free
}


// ------------------------------------------------------------
// 0x4FB970 sub_4FB970 —— 20 字节元素单点插入（返回新址）
//   记录索引 → ·0x4FB660 扩一 → 新址回写 uArg2。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4FB970(int *this, uint32_t *uArg2, char *pszArg3, int16_t *uArg4)  // 20 字节元素单点插入（返回新址）
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 20 != 0 )  // 若 fld_e1 != 0 && (*(this + 2) - fld_e1) / 20 != 0
    v6 = (int)&pszArg3[-fld_e1] / 20;
  else
    v6 = 0;
  sub_4FB660(this, pszArg3, 1u, uArg4);  // 20 字节元素向量插入（三路分支 + 1.5 倍扩容）
  *uArg2 = *(this + 1) + 20 * v6;  // *uArg2 写入 *(this + 1) + 20 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x4FB9E0 sub_4FB9E0 —— 20 字节元素尾插（满则 4FB970）
//   有余量 sub_4FB030 就地 +20 递增，否则 ·0x4FB970。
// ------------------------------------------------------------
void /*thiscall*/ sub_4FB9E0(int *this, int16_t *uArg2)  // 函数: 20 字节元素尾插（满则 4FB970）
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( fld_e1 != 0 )  // 若 fld_e1 != 0
    fld_e2 = (*(this + 2) - fld_e1) / 20;
  else
    fld_e2 = 0;
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) / 20 )  // 若 fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) / 20
  {
    fld_e22 = *(this + 2);  // fld_e22 = this+2
    sub_4FB030(fld_e22, 1, uArg2);  // 20 字节元素填充构造（nArg2 个副本自 pArg3）
    *(this + 2) = fld_e22 + 20;  // this+8 = fld_e22 + 20
  }
  else
  {
    sub_4FB970(this, &uArg2, (char *)*(this + 2), uArg2);  // 20 字节元素单点插入（返回新址）
  }
}



// ------------------------------------------------------------
// 0x4FBA70 sub_4FBA70 —— 战场平衡表解析器（etc/WarRoomEqualize.tbl）
//   标签族：[warroom equalization]（战场平衡）/[warroom slave hp equalization]（从者 HP 平衡）。
// ------------------------------------------------------------
char sub_4FBA70()  // 战场平衡表解析器（etc/WarRoomEqualize.tbl）
{
  void *dword_8F7C482; // eax
  int dword_8F7C4C2; // edi
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
  int dword_796E502; // [esp+7Ch] [ebp-10h]
  int v23; // [esp+88h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"etc/WarRoomEqualize.tbl") != 0 )  // 字符串 “etc/WarRoomEqualize.tbl”
  {
    v21 = 15;
    v20 = 0;
    LOBYTE(v19) = 0;
    v23 = 1;
    v17 = 15;
    v16 = 0;
    LOBYTE(v15) = 0;
    while ( (uint8_t)sub_443430(v18) != 0 )  // 当 (uint8_t)sub_443430(v18) != 0 循环
    {
      sub_442BC0(v18);  // 国家码标签配对校验（bool）
      if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[warroom equalization]", 0x16u) != 0 )  // 字符串 “[warroom equalization]”
      {
        if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[warroom slave hp equalization]", 0x1Fu) == 0 )  // 字符串 “[warroom slave hp equalization]”
          *(float *)&dword_77F884 = sub_442480(nullptr);  // 脚本 token 数值解析（double 版）
      }
      else
      {
        dword_8F7C482 = dword_8F7C48;
        if ( dword_8F7C48 != nullptr )  // 若 dword_8F7C48 非空
        {
          dword_8F7C4C2 = dword_8F7C4C;
          if ( dword_8F7C48 != (void *)dword_8F7C4C )  // 若 dword_8F7C48 != (void *)dword_8F7C4C
          {
            v3 = (char *)dword_8F7C48 + 8;
            do
            {
              if ( *(uint32_t *)v3 != 0 )  // 若 *(uint32_t *)v3 != 0
                j__free(*(void **)v3);  // 调 j__free
              *(uint32_t *)v3 = 0;
              *((uint32_t *)v3 + 1) = 0;
              *((uint32_t *)v3 + 2) = 0;
              v3 += 20;
            }
            while ( v3 - 8 != (char *)dword_8F7C4C2 );  // 当 v3 - 8 != (char *)dword_8F7C4C2 循环
            dword_8F7C482 = dword_8F7C48;
          }
          j__free(dword_8F7C482);  // 调 j__free
        }
        dword_8F7C48 = nullptr;  // dword_8F7C48 = nullptr 空指针
        dword_8F7C4C = 0;
        dword_8F7C50 = 0;
        if ( dword_8F7C58 != nullptr )  // 若 dword_8F7C58 非空
        {
          sub_4166A0(dword_8F7C58, dword_8F7C5C);  // 析构区间内 28B string 元素
          j__free(dword_8F7C58);  // 调 j__free
        }
        dword_8F7C58 = nullptr;  // dword_8F7C58 = nullptr 空指针
        dword_8F7C5C = 0;
        dword_8F7C60 = 0;
        v4 = sub_4423D0(nullptr);  // 调 sub_4423D0
        if ( v4 > 0 )  // 若 v4 > 0
        {
          v13 = v4;
          do
          {
            Block = nullptr;  // Block = nullptr 空指针
            v11 = 0;
            v12 = 0;
            LOBYTE(v23) = 2;
            v9[0] = sub_4423D0(nullptr);  // 调 sub_4423D0
            v9[1] = sub_4423D0(nullptr);  // 调 sub_4423D0
            sub_443370();  // 脚本 token 取串（第三入口）
            sub_416C40(v14);  // 尾插一条 28B 记录（满则走插入路径）
            for ( i = 99; i != 0; --i )  // 循环：i = 99; i != 0; --i
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
              for ( j = 0; j < 11; ++j )  // 循环：j = 0; j < 11; ++j
                *(float *)&v8[j] = sub_442480(nullptr);  // 脚本 token 数值解析（double 版）
              sub_435790(v8);  // 44 字节元素表 push_back
            }
            sub_4FB9E0(v9);  // 20 字节元素尾插（满则 4FB970）
            LOBYTE(v23) = 1;
            if ( Block != nullptr )  // 若 Block 非空
              j__free(Block);  // 调 j__free
            v7 = v13 == 1;
            Block = nullptr;  // Block = nullptr 空指针
            v11 = 0;
            v12 = 0;
            --v13;  // 自减v13
          }
          while ( !v7 );  // 当 !v7 循环
        }
      }
    }
    if ( v17 >= 0x10 )  // 若 v17 >= 0x10
      j__free(v15);  // 调 j__free
    v17 = 15;
    v16 = 0;
    LOBYTE(v15) = 0;
    if ( v21 >= 0x10 )  // 若 v21 >= 0x10
      j__free(v19);  // 调 j__free
    return 1;
  }
  else
  {
    off_77F3FC(aCriticalError_15);
    return 0;
  }
}


// ------------------------------------------------------------
// 0x4FBD40 sub_4FBD40 —— 20 字节元素正向搬移（5 双字直拷）
//   每步 5 双字复制，返回目标尾址；·0x4FBE30 扩容搬移用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FBD40(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 20 字节元素正向搬移（5 双字直拷）
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax
  uint32_t *v5; // edi
  int v6; // esi

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; v5[4] = v6 )  // 循环：result = uArg3; uArg12 != uArg2; v5[4] = v6
  {
    v5 = result;
    *result = *uArg12;  // *result 写入 *uArg12
    result[1] = uArg12[1];  // result[1] 写入 uArg12[1]
    result[2] = uArg12[2];  // result[2] 写入 uArg12[2]
    result[3] = uArg12[3];  // result[3] 写入 uArg12[3]
    v6 = uArg12[4];
    uArg12 += 5;
    result += 5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FBD90 sub_4FBD90 —— 20 字节元素反向搬移（5 双字直拷）
//   每步 -5 双字复制，返回目标首址；4FBE30 插入路径用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FBD90(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 20 字节元素反向搬移（5 双字直拷）
{
  uint32_t *uArg22; // ecx
  uint32_t *result; // eax

  uArg22 = uArg2;
  for ( result = uArg3; uArg22 != uArg1; result[4] = uArg22[4] )  // 循环：result = uArg3; uArg22 != uArg1; result[4] = uArg22[4]
  {
    uArg22 -= 5;
    result -= 5;
    *result = *uArg22;  // *result 写入 *uArg22
    result[1] = uArg22[1];  // result[1] 写入 uArg22[1]
    result[2] = uArg22[2];  // result[2] 写入 uArg22[2]
    result[3] = uArg22[3];  // result[3] 写入 uArg22[3]
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FBDE0 sub_4FBDE0 —— 20 字节元素正向区间拷贝（逐槽空目标防御）
//   每步 5 双字、空目标跳过；作为 20 字节族搬移原语被 4FBE30 复用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4FBDE0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 20 字节元素正向区间拷贝（逐槽空目标防御）
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; result += 5 )  // 循环：result = uArg3; uArg12 != uArg2; result += 5
  {
    if ( result != nullptr )  // 若 result 非空
    {
      *result = *uArg12;  // *result 写入 *uArg12
      result[1] = uArg12[1];  // result[1] 写入 uArg12[1]
      result[2] = uArg12[2];  // result[2] 写入 uArg12[2]
      result[3] = uArg12[3];  // result[3] 写入 uArg12[3]
      result[4] = uArg12[4];  // result[4] 写入 uArg12[4]
    }
    uArg12 += 5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4FBE30 sub_4FBE30 —— 20 字节元素向量插入（三路分支 + 1.5 倍扩容）
//   就地 sub_4FBDE0/sub_57A4A0/sub_655A00；重建经 operator new + sub_4FBDE0/sub_655A40 与
//   sub_45E580 容量；超限 sub_434730；首元素 temp 由 Block 5 双字构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4FBE30(int *this, uint32_t *pArg2, unsigned int uArg3, uint32_t *Block)  // 函数: 20 字节元素向量插入（三路分支 + 1.5 倍扩容）
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
  fld_e1 = *(this + 1);  // fld_e1 = this+1
  v26[0] = *Block;  // v26[0] 写入 *Block
  v7 = Block[2];
  v26[1] = v5;
  v8 = Block[3];
  result = Block[4];
  v26[5] = &v25;
  v26[2] = v7;
  v26[3] = v8;
  v26[4] = result;
  if ( fld_e1 != 0 )  // 若 fld_e1 != 0
  {
    result = 1717986919 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 20;
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e2 = (*(this + 2) - fld_e1) / 20;
    else
      fld_e2 = 0;
    if ( 214748364 - fld_e2 < uArg3 )  // 若 214748364 - fld_e2 < uArg3
      sub_434730(this);  // vector 超长抛 length_error
    if ( fld_e1 != 0 )  // 若 fld_e1 != 0
      fld_e22 = (*(this + 2) - fld_e1) / 20;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )  // 若 fld_e3 >= uArg3 + fld_e22
    {
      fld_e23 = (void *)*(this + 2);
      Blockb = fld_e23;
      if ( ((uint8_t *)fld_e23 - (uint8_t *)pArg2) / 20 >= uArg3 )  // 若 ((uint8_t *)fld_e23 - (uint8_t *)pArg2) / 20 >= uArg3
      {
        v28 = (int)fld_e23 - 20 * uArg3;
        *(this + 2) = sub_4FBDE0(v28, fld_e23, fld_e23);  // 20 字节元素正向区间拷贝（逐槽空目标防御）
        sub_57A4A0(pArg2, v28, Blockb);  // 辅助（4FBD90）
        return (int)sub_655A00(pArg2, &pArg2[5 * uArg3], v26);  // 20 字节记录正向区间拷贝
      }
      else
      {
        sub_4FBDE0(pArg2, fld_e23, &pArg2[5 * uArg3]);  // 20 字节元素正向区间拷贝（逐槽空目标防御）
        fld_e24 = uArg3 - (*(this + 2) - (int)pArg2) / 20;
        fld_e25 = *(this + 2);  // fld_e25 = this+2
        v27 = 2;
        sub_57A4C0(fld_e25, fld_e24, v26);  // 辅助（655A40）
        fld_e26 = 20 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8 = fld_e26
        return (int)sub_655A00(pArg2, (uint32_t *)(fld_e26 - 20 * uArg3), v26);  // 20 字节记录正向区间拷贝
      }
    }
    else
    {
      if ( 214748364 - (fld_e3 >> 1) >= fld_e3 )  // 若 214748364 - (fld_e3 >> 1) >= fld_e3
        v14 = (fld_e3 >> 1) + fld_e3;
      else
        v14 = 0;
      if ( fld_e1 != 0 )  // 若 fld_e1 != 0
        fld_e27 = (*(this + 2) - fld_e1) / 20;
      else
        fld_e27 = 0;
      if ( v14 < uArg3 + fld_e27 )  // 若 v14 < uArg3 + fld_e27
        v14 = uArg3 + sub_45E580(this);  // 结果 = 容器计数（跨度 / 20）
      v16 = 20 * v14;
      Blocka = (char *)operator new(20 * v14);
      fld_e12 = *(this + 1);  // fld_e12 = this+1
      v27 = 0;
      v29 = (uint32_t *)sub_4FBDE0(fld_e12, pArg2, Blocka);  // 结果 = 20 字节元素正向区间拷贝（逐槽空目标防御）
      sub_655A40(v29, (uint32_t *)uArg3, v26);  // 20 字节记录逐元素填充
      sub_4FBDE0(pArg2, *(this + 2), &v29[5 * uArg3]);  // 20 字节元素正向区间拷贝（逐槽空目标防御）
      fld_e13 = *(this + 1);  // fld_e13 = this+1
      if ( fld_e13 != 0 )  // 若 fld_e13 != 0
        fld_e13 = (*(this + 2) - fld_e13) / 20;
      v18 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        j__free((void *)*(this + 1));  // 调 j__free
      *(this + 3) = (int)&Blocka[v16];  // this+12 = (int)&Blocka[v16]
      *(this + 2) = (int)&Blocka[20 * v18];  // this+8 = (int)&Blocka[20 * v18]
      *(this + 1) = (int)Blocka;  // this+4 = (int)Blocka
      return (int)Blocka;
    }
  }
  return result;
}

