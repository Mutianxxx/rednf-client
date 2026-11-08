// ============================================================
// 【40JP逆向源代码工程】game/skill_load_tutorial.cpp
// 模块: 技能加载 / 教程提示 / 版本串 / 调试与网络辅助
// 来源: work/dump_misca.txt  区块: 0x480000-0x490000
// 层级: L2 转写层 → L1 精修层（会话精修：解析器标签清单 + 功能族分区 + 字符串证据）
// 函数数: 305
//
// ★ 技能加载主链：sub_482A90 → sub_481720 建临时树节点 → sub_502F00（0x4F 区
//   技能定义解析器）解析 .skill → 装配槽位；失败 "SKILL CREATE FAIL! FILENAME[%s]"。
//   技能表槽位冲突报 "SKILL LIST ERROR! JOB : %d, INDEX : %d"。
//
// ★ 解析器标签清单：
//   - sub_488AB0 Etc/TutorialTip.etc（教程提示）：
//       [no] 条目索引 · [priority] A/B/C→3/2/1 · [level] · [title] · [content] ·
//       [image] · [end]；条目数→对象+4292，等级→+4036+no，优先级→+4228。
//   - sub_489800 ../DebugConfig.txt（调试配置，内嵌于全局初始化）：
//       [dungeon index][map index][path info][job][grow type][level][avatar][item]
//       [storage][mounted equipment][skill][cash][SP][test user number][user index][IP]
//
// ★ 其他锚点：sub_488970 版本串 "Ver. 200606130k0515"（2006-06-13 build）；
//   sub_48BB30 动态解析 IsDebuggerPresent 反调试；"EyeOfBeholder::open_eye" 代码区 CRC
//   自检；"Allons y"/"CruelRogue"/"WindShadow" 为调试测试角色名（sub_47B150 生成）。
//
// 分区（按 VA 升序）：
//   §A 0x480020-0x481300  技能树节点/槽位数据结构族
//   §B 0x481300-0x482A90  技能对象生命周期（ctor/dtor/字段组）
//   §C 0x482A90-0x483C60  ★技能创建主流程（SKILL CREATE FAIL）
//   §D 0x483C60-0x484470  包分发辅助（读包三元组 sub_423200/423290/423380）
//   §E 0x484470-0x485330  技能槽状态族（+44/+52/+56）
//   §F 0x485330-0x487310  技能命令/施放处理（ALERT_1）
//   §G 0x487310-0x488060  容器/字符串辅助 + 对象生成
//   §H 0x488060-0x488D90  ★版本串 + TutorialTip.etc 解析器 + 读盘画面
//   §I 0x488D90-0x489800  网络包收发基础
//   §J 0x489800-0x48B700  ★★全局初始化 + DebugConfig.txt + 测试角色
//   §K 0x48B700-0x48C070  调试控制台窗口（ID/CH/IsDebuggerPresent）
//   §L 0x48C070-0x48C500  包校验/杂项
//   §M 0x48C500-0x48CF90  技能演出联动（sub_4938F0/491D00 转发）
//   §N 0x48CF90-0x48EED0  发包族（sub_48D1E0/48E1A0 组包器）
//   §O 0x48EED0-0x48F500  资源装载包装（IMAGE/ANI）
//   §P 0x48F500-0x48FE80  宿主/Ladder 联动 + 收尾（@@SET HOST / LADDER_DOWN）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// §A 0x480020-0x481300  技能树节点/槽位数据结构族
// ============================================================
// ------------------------------------------------------------
// 0x480020 sub_480020 —— 14 字节元素容器区间赋值（技能槽内层列表）
// 元素步长 14，与 ·sub_47FA00 析构同族；先经 ·sub_47FC20 做长度守卫【推断】，再由 ·sub_47E200 按源区间 pArg2+4..+8 分配并拷贝，终点写 this+8。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_480020(uint32_t *this, int pArg2)  // 14 字节元素容器区间赋值（技能槽内层列表）
{
  int v2; // eax
  int v5; // [esp-14h] [ebp-34h]
  int v6; // [esp-10h] [ebp-30h]
  int fld_e1; // [esp-Ch] [ebp-2Ch]
  uint32_t v8[8]; // [esp+0h] [ebp-20h] BYREF

  v2 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  v8[4] = v8;
  v8[3] = this;
  if ( v2 != 0 )
    v2 = (*(uint32_t *)(pArg2 + 8) - v2) / 14;  // pArg2+8〔nSkillRec8(推断)〕
  if ( (uint8_t)sub_47FC20(v2) != 0 )  // 调 做长度守卫(推断)
  {
    fld_e1 = *(this + 1);  // this+4〔宿主对象〕
    v6 = *(uint32_t *)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    v5 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v8[7] = 0;
    *(this + 2) = sub_47E200(v5, v6, fld_e1);  // 调 按源区间 pArg2+4..+8 分配并拷贝
  }
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4800C0 sub_4800C0 —— 8 字节元素容器区间赋值（三分支容量策略）
// 容量足够时 ·sub_47E1D0 逐元素拷贝并改写 this+8 终点；容量大于需求时先拷前缀、尾段由 ·sub_44BD30 补齐；容量不足则释放旧块，经 ·sub_42D030 守卫后由 ·sub_472EA0 重新分配拷贝。
// ------------------------------------------------------------
int /*thiscall*/ sub_4800C0(int this, int pArg2)  // 实现：8 字节元素容器区间赋值（三分支容量策略）
{
  int v3; // ebx
  unsigned int v4; // ecx
  int fld_4; // eax
  unsigned int fld_8; // edx
  int v8; // eax
  int fld_42; // ecx
  unsigned int fld_C; // edx
  int fld_82; // edx
  int v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == pArg2 )
    return this;  // 返回自身指针
  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 3) == 0 )  // pArg2+8〔nSkillRec8(推断)〕
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    return this;  // 返回自身指针
  }
  fld_4 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v4 <= fld_8 )  // fld_8=this+8 nSkillRec8
  {
    sub_47E1D0(v3, *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));  // 调 逐元素拷贝并改写 this+8 终点
    v8 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v8 != 0 )
      fld_42 = *(uint32_t *)(this + 4) + 8 * ((*(uint32_t *)(pArg2 + 8) - v8) >> 3);  // this+4〔宿主对象〕等 2 字段
    else
      fld_42 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = fld_42;  // this+8〔nSkillRec8(推断)〕等 2 字段
    return this;  // 返回自身指针
  }
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    fld_C = 0;  // fld_C=this+12 nSkillRec12
  if ( v4 > fld_C )  // fld_C=this+12 nSkillRec12
  {
    if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    v13 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(pArg2 + 8) - v13) >> 3;  // pArg2+8〔nSkillRec8(推断)〕
    else
      v14 = 0;
    if ( (uint8_t)sub_42D030(v14) != 0 )  // vector 预留（8B，同构）
      *(uint32_t *)(this + 8) = sub_472EA0(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));  // this+8〔nSkillRec8(推断)〕等 4 字段
    return this;  // 返回自身指针
  }
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_82 = 0;  // fld_82=this+8 nSkillRec8
  v12 = *(uint32_t *)(pArg2 + 4) + 8 * fld_82;  // pArg2+4〔宿主对象〕
  sub_47E1D0(*(uint32_t *)(pArg2 + 4), v12, *(uint32_t *)(this + 4));  // 调 逐元素拷贝并改写 this+8 终点
  *(uint32_t *)(this + 8) = sub_44BD30(v12, *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 8));  // 8 字节元素正向拷贝
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x480210 sub_480210 —— 4 字节元素容器区间赋值（与 ·0x4800C0 同构）
// 差异仅在步长 4 与所用辅助：前段 memcpy_0、尾段补齐 ·sub_433A30，重分配由 ·sub_55E7F0 承担（守卫 ·sub_47FB20）。
// ------------------------------------------------------------
int /*thiscall*/ sub_480210(int this, int pArg2)  // 实现：4 字节元素容器区间赋值（与 ·0x4800C0 同构）
{
  int v3; // ecx
  unsigned int v4; // edx
  void *pVecEnd_13; // ecx
  unsigned int fld_8; // ebx
  int v8; // eax
  int fld_42; // ecx
  unsigned int fld_C; // eax
  int fld_82; // eax
  void *v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == pArg2 )
    return this;  // 返回自身指针
  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2) == 0 )  // pArg2+8〔nSkillRec8(推断)〕
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    return this;  // 返回自身指针
  }
  pVecEnd_13 = *(void **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  if ( pVecEnd_13 != nullptr )  // 若 fld_4 有效（非空）
    fld_8 = (*(uint32_t *)(this + 8) - (int)pVecEnd_13) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v4 <= fld_8 )  // fld_8=this+8 nSkillRec8
  {
    memcpy_0(pVecEnd_13, *(const void **)(pArg2 + 4), 4 * ((*(uint32_t *)(pArg2 + 8) - *(uint32_t *)(pArg2 + 4)) >> 2));  // pArg2+8〔nSkillRec8(推断)〕
    v8 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v8 != 0 )
      fld_42 = *(uint32_t *)(this + 4) + 4 * ((*(uint32_t *)(pArg2 + 8) - v8) >> 2);  // this+4〔宿主对象〕等 2 字段
    else
      fld_42 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = fld_42;  // this+8〔nSkillRec8(推断)〕等 2 字段
    return this;  // 返回自身指针
  }
  if ( pVecEnd_13 != nullptr )  // 若 fld_4 有效（非空）
    fld_C = (*(uint32_t *)(this + 12) - (int)pVecEnd_13) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    fld_C = 0;  // fld_C=this+12 nSkillRec12
  if ( v4 > fld_C )  // fld_C=this+12 nSkillRec12
  {
    if ( pVecEnd_13 != nullptr )  // 若 fld_4 有效（非空）
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    v13 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(pArg2 + 8) - v13) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
    else
      v14 = 0;
    if ( (uint8_t)sub_47FB20(v14) != 0 )  // 调 capEnd=块首+4×uArg2；超 0x3FFFFFFF（2^32/4 条）抛 0x47F990
      *(uint32_t *)(this + 8) = sub_55E7F0(*(void **)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(void **)(this + 4));  // 商城状态
    return this;  // 返回自身指针
  }
  if ( pVecEnd_13 != nullptr )  // 若 fld_4 有效（非空）
    fld_82 = (*(uint32_t *)(this + 8) - (int)pVecEnd_13) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_82 = 0;  // fld_82=this+8 nSkillRec8
  v12 = (void *)(*(uint32_t *)(pArg2 + 4) + 4 * fld_82);  // pArg2+4〔宿主对象〕
  sub_433A30(*(void **)(pArg2 + 4), (int)v12, *(void **)(this + 4));  // dword 区间拷贝
  *(uint32_t *)(this + 8) = sub_55E7F0(v12, *(uint32_t *)(pArg2 + 8), *(void **)(this + 8));  // 商城状态
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x480360 sub_480360 —— 8 字节元素容器区间赋值（简易构造版）
// 与 ·0x480020 同构，差异为元素步长 8：守卫 ·sub_42D030、分配拷贝 ·sub_44BD30。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_480360(uint32_t *this, int pArg2)  // 8 字节元素容器区间赋值（简易构造版）
{
  int v3; // ecx
  int v4; // eax
  int v6; // [esp-14h] [ebp-34h]
  int v7; // [esp-10h] [ebp-30h]
  int fld_e1; // [esp-Ch] [ebp-2Ch]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 3;  // pArg2+8〔nSkillRec8(推断)〕
  else
    v4 = 0;
  if ( (uint8_t)sub_42D030(v4) != 0 )  // vector 预留（8B，同构）
  {
    fld_e1 = *(this + 1);  // this+4〔宿主对象〕
    v7 = *(uint32_t *)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    v6 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v12 = 0;
    *(this + 2) = sub_44BD30(v6, v7, fld_e1);  // 8 字节元素正向拷贝
  }
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x480400 sub_480400 —— 4 字节元素容器区间赋值（简易构造版）
// 与 ·0x480020 同构，差异为元素步长 4：守卫 ·sub_47FB20、拷贝由 ·sub_497E70 完成 uint32 区间逐元素搬运。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_480400(uint32_t *this, int pArg2)  // 4 字节元素容器区间赋值（简易构造版）
{
  int v3; // ecx
  int v4; // eax
  int v6; // [esp-14h] [ebp-34h]
  int v7; // [esp-10h] [ebp-30h]
  int fld_e1; // [esp-Ch] [ebp-2Ch]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
  else
    v4 = 0;
  if ( (uint8_t)sub_47FB20(v4) != 0 )  // 调 capEnd=块首+4×uArg2；超 0x3FFFFFFF（2^32/4 条）抛 0x47F990
  {
    fld_e1 = *(this + 1);  // this+4〔宿主对象〕
    v7 = *(uint32_t *)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    v6 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, fld_e1);  // uint32 区间逐元素拷贝
  }
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4804A0 sub_4804A0 —— 12 字节三元组容器区间赋值（三分支容量策略）
// 元素数由 ·sub_4DA030 求得；前缀拷贝 ·sub_47E170、尾段补齐 ·sub_59EE30（三元组块搬移辅助）；重分配路径经 ·sub_47FB80 守卫后由 ·sub_47F790 分配拷贝。
// ------------------------------------------------------------
int /*thiscall*/ sub_4804A0(int this, int pArg2)  // 实现：12 字节三元组容器区间赋值（三分支容量策略）
{
  int v4; // eax
  unsigned int v5; // ecx
  int pVecEnd_11; // edi
  unsigned int fld_8; // eax
  int v9; // eax
  unsigned int fld_C; // eax
  int v11; // eax
  int v12; // [esp+10h] [ebp+8h]

  if ( this == pArg2 )
    return this;  // 返回自身指针
  v4 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v4 == 0 || (v5 = (*(uint32_t *)(pArg2 + 8) - v4) / 12) == 0 )  // pArg2+8〔nSkillRec8(推断)〕
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    return this;  // 返回自身指针
  }
  pVecEnd_11 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( pVecEnd_11 != 0 )  // fld_4=this+4 宿主对象
    fld_8 = (*(uint32_t *)(this + 8) - pVecEnd_11) / 12;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v5 > fld_8 )  // fld_8=this+8 nSkillRec8
  {
    if ( pVecEnd_11 != 0 )  // fld_4=this+4 宿主对象
      fld_C = (*(uint32_t *)(this + 12) - pVecEnd_11) / 12;  // this+12〔nSkillRec12(推断)〕等 2 字段
    else
      fld_C = 0;  // fld_C=this+12 nSkillRec12
    if ( v5 <= fld_C )  // fld_C=this+12 nSkillRec12
    {
      v12 = *(uint32_t *)(pArg2 + 4) + 12 * sub_4DA030(this);  // pArg2+4〔宿主对象〕
      sub_47E170(*(uint32_t *)(pArg2 + 4), v12, pVecEnd_11);  // pArg2+4〔宿主对象〕
      *(uint32_t *)(this + 8) = sub_59EE30(v12, *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 8));  // 三元组块搬移辅助
      return this;  // 返回自身指针
    }
    if ( pVecEnd_11 != 0 )  // fld_4=this+4 宿主对象
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    v11 = sub_4DA030(pArg2);  // 调 v13 = 插入数 + sub_4DA030（当前数）
    if ( (uint8_t)sub_47FB80(v11) != 0 )  // 调 守卫后由 ·sub_47F790 分配拷贝
      *(uint32_t *)(this + 8) = sub_47F790(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));  // this+8〔nSkillRec8(推断)〕等 4 字段
    return this;  // 返回自身指针
  }
  sub_47DDD0(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), pVecEnd_11);  // 调 中段删除搬移
  v9 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 12 * ((*(uint32_t *)(pArg2 + 8) - v9) / 12);  // this+8〔nSkillRec8(推断)〕等 4 字段
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);  // this+8〔nSkillRec8(推断)〕等 4 字段
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x480620 sub_480620 —— 14 字节元素容器深拷贝赋值（析构+拷贝全链路）
// 源区间为空时走 ·sub_47F6E0 清空；否则按容量三分支：前缀拷贝 ·sub_47E190、尾段构造 ·sub_47E200、旧尾先经 ·sub_47F6B0 析构；重分配守卫 ·sub_47FC20、分配拷贝 ·sub_47F7B0、区间复制 ·sub_47DE10。
// ------------------------------------------------------------
int /*thiscall*/ sub_480620(int this, int pArg2)  // 实现：14 字节元素容器深拷贝赋值（析构+拷贝全链路）
{
  int pArg22; // edi
  int v4; // eax
  unsigned int v5; // ecx
  int pVecEnd_12; // ebx
  unsigned int fld_8; // eax
  int v9; // eax
  int v10; // eax
  unsigned int fld_C; // eax
  int v12; // edi
  int v13; // eax

  pArg22 = pArg2;
  if ( this == pArg2 )
    return this;  // 返回自身指针
  v4 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v4 == 0 || (v5 = (*(uint32_t *)(pArg2 + 8) - v4) / 14) == 0 )  // pArg2+8〔nSkillRec8(推断)〕
  {
    sub_47F6E0(this);  // 调 释放临时值
    return this;  // 返回自身指针
  }
  pVecEnd_12 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( pVecEnd_12 != 0 )  // fld_4=this+4 宿主对象
  {
    pArg22 = pArg2;
    fld_8 = (*(uint32_t *)(this + 8) - pVecEnd_12) / 14;  // this+8〔nSkillRec8(推断)〕等 2 字段
  }
  else
  {
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  }
  if ( v5 > fld_8 )  // fld_8=this+8 nSkillRec8
  {
    if ( pVecEnd_12 != 0 )  // fld_4=this+4 宿主对象
    {
      pArg22 = pArg2;
      fld_C = (*(uint32_t *)(this + 12) - pVecEnd_12) / 14;  // this+12〔nSkillRec12(推断)〕等 2 字段
    }
    else
    {
      fld_C = 0;  // fld_C=this+12 nSkillRec12
    }
    if ( v5 <= fld_C )  // fld_C=this+12 nSkillRec12
    {
      v12 = *(uint32_t *)(pArg2 + 4) + 14 * sub_47DD70(this);  // pArg2+4〔宿主对象〕
      sub_47E190(*(uint32_t *)(pArg2 + 4), v12, pVecEnd_12);  // pArg2+4〔宿主对象〕
      *(uint32_t *)(this + 8) = sub_47E200(v12, *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 8));  // 调 按源区间 pArg2+4..+8 分配并拷贝
      return this;  // 返回自身指针
    }
    if ( pVecEnd_12 != 0 )  // fld_4=this+4 宿主对象
    {
      sub_47F6B0(pVecEnd_12, *(uint32_t *)(this + 8));  // this+8〔nSkillRec8(推断)〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    }
    v13 = sub_47DD70(pArg22);  // 调 14 字节条目 vector 计数 getter（this+1/2 = begin/end，条目 0x0E=14 字节）
    if ( (uint8_t)sub_47FC20(v13) != 0 )  // 调 做长度守卫(推断)
      *(uint32_t *)(this + 8) = sub_47F7B0(*(uint32_t *)(pArg22 + 4), *(uint32_t *)(pArg22 + 8), *(uint32_t *)(this + 4));  // this+8〔nSkillRec8(推断)〕等 4 字段
    return this;  // 返回自身指针
  }
  v9 = sub_47DE10(*(uint32_t *)(pArg22 + 4), *(uint32_t *)(pArg22 + 8), pVecEnd_12);  // pArg22+8〔nSkillRec8(推断)〕
  sub_47F6B0(v9, *(uint32_t *)(this + 8));  // this+8〔nSkillRec8(推断)〕等 2 字段
  v10 = *(uint32_t *)(pArg22 + 4);  // pArg22+4〔宿主对象〕
  if ( v10 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 14 * ((*(uint32_t *)(pArg22 + 8) - v10) / 14);  // this+8〔nSkillRec8(推断)〕等 4 字段
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);  // this+8〔nSkillRec8(推断)〕等 4 字段
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4807B0 sub_4807B0 —— 14 字节元素容器 resize(n, value)（与 ·0x480FB0 同族短版）
// n 小于当前项数时用 ·sub_47F720 析构截断区间 [this+4+14n, this+8)；否则经 ·sub_47FD00 尾部插入 (n-项数) 个默认值，临时值随后由 ·sub_41A580 释放。
// ------------------------------------------------------------
void /*thiscall*/ sub_4807B0(int *this, unsigned int uArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 实现：14 字节元素容器 resize(n, value)（与 ·0x480FB0 同族短版）
{
  int pVecEnd_10; // ebx
  unsigned int fld_e2; // eax
  int fld_e22; // eax

  pVecEnd_10 = *(this + 1);  // this+4〔宿主对象〕
  fld_e2 = 0;
  if ( pVecEnd_10 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - pVecEnd_10) / 14;  // this+8〔nSkillRec8(推断)〕
  if ( fld_e2 >= uArg2 )  // fld_e2=this+8 nSkillRec8
  {
    if ( pVecEnd_10 != 0 && uArg2 < (*(this + 2) - pVecEnd_10) / 14 )  // this+8〔nSkillRec8(推断)〕
      sub_47F720(&uArg2, pVecEnd_10 + 14 * uArg2, *(this + 2));  // 调 析构截断区间 [this+4+14n
  }
  else
  {
    if ( pVecEnd_10 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - pVecEnd_10) / 14;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    sub_47FD00(this, *(this + 2), uArg2 - fld_e22, (int)&nArg3);  // 调 尾部插入 (n-项数) 个默认值
  }
  sub_41A580(&nArg3);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
}



// ------------------------------------------------------------
// 0x480880 sub_480880 —— 14 字节容器指定位置单元素插入（返回元素指针）
// 先记下插入位置下标（与 this+4 的差值 /14），再由 ·sub_47FD00 在 nArg3 处插入 1 个元素；回传 this+4 + 14*下标 作为新元素地址。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_480880(int *this, uint32_t *uArg2, int nArg3, int nArg4)  // 14 字节容器指定位置单元素插入（返回元素指针）
{
  int pVecEnd_5; // esi
  int v6; // esi

  pVecEnd_5 = *(this + 1);  // this+4〔宿主对象〕
  if ( pVecEnd_5 != 0 && (*(this + 2) - pVecEnd_5) / 14 != 0 )  // this+8〔nSkillRec8(推断)〕
    v6 = (nArg3 - pVecEnd_5) / 14;  // pVecEnd_5=this+4 宿主对象
  else
    v6 = 0;
  sub_47FD00(this, nArg3, 1u, nArg4);  // 调 尾部插入 (n-项数) 个默认值
  *uArg2 = *(this + 1) + 14 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x4808F0 sub_4808F0 —— 16 字节条目数组逐项深拷贝赋值
// 条目内嵌 14 字节元素列表（见 ·0x480020 的 this+4/+8 字段）；对 [nArg1,nArg2) 每项调 ·sub_480620 以 nArg3 为源做深拷贝。
// ------------------------------------------------------------
int /*cdecl*/ sub_4808F0(int nArg1, int nArg2, int nArg3)  // 实现：16 字节条目数组逐项深拷贝赋值
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 16 )
    result = sub_480620(i, nArg3);  // 结果 = 14 字节元素容器深拷贝赋值（析构+拷贝全链路）
  return result;
}



// ------------------------------------------------------------
// 0x480920 sub_480920 —— 16 字节条目区间自前向后逐项拷贝构造
// 目标自 nArg3 起、源自 nArg1 起，步长 16、每项经 ·sub_480620 构造；与 ·0x4809C0 的反向版本配套用于插入时的重叠搬移。
// ------------------------------------------------------------
int /*cdecl*/ sub_480920(int nArg1, int nArg2, int nArg3)  // 实现：16 字节条目区间自前向后逐项拷贝构造
{
  int nArg12; // esi
  int nArg32; // edi

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    sub_480620(nArg32, nArg12);  // 14 字节元素容器深拷贝赋值（析构+拷贝全链路）
    nArg12 += 16;
    nArg32 += 16;
  }
  while ( nArg12 != nArg2 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x480960 sub_480960 —— 16 字节条目区间析构（内层对象走虚表首槽）
// 对每项先按 +4..+8、步长 14 遍历内层对象并调虚表第 0 槽析构，再 j__free 内层缓冲；随后清零 +4/+8/+12。
// ------------------------------------------------------------
int /*cdecl*/ sub_480960(int nArg1, int nArg2)  // 实现：16 字节条目区间析构（内层对象走虚表首槽）
{
  int result; // eax
  int i; // edi
  char *v4; // esi
  char *j; // ebx

  result = nArg2;
  for ( i = nArg1; i != nArg2; i += 16 )
  {
    v4 = *(char **)(i + 4);
    if ( v4 != nullptr )  // 若 v4 有效（非空）
    {
      for ( j = *(char **)(i + 8); v4 != j; v4 += 14 )
        (**(void (/*thiscall*/ ***)(char *, uint32_t))v4)(v4, 0);
      j__free(*(void **)(i + 4));  // 调 堆释放
    }
    *(uint32_t *)(i + 4) = 0;
    *(uint32_t *)(i + 8) = 0;
    *(uint32_t *)(i + 12) = 0;
    result = nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4809C0 sub_4809C0 —— 16 字节条目区间自后向前逐项深拷贝
// 与 ·0x480920 反向（源、目标指针各自回退 16 字节），供 ·0x480FB0 插入腾挪尾部区间时避免覆盖。
// ------------------------------------------------------------
int /*cdecl*/ sub_4809C0(int nArg1, int nArg2, int nArg3)  // 实现：16 字节条目区间自后向前逐项深拷贝
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
    sub_480620(nArg32, nArg22);  // 14 字节元素容器深拷贝赋值（析构+拷贝全链路）
  }
  while ( nArg22 != nArg1 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x480A00 sub_480A00 —— 16 字节条目区间构造到裸内存（返回终点）
// uArg3 为未初始化内存基址，逐项以 ·sub_480020 由源区间就地构造 16 字节条目、步进 16；定长同值版见 ·0x480C20。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_480A00(int nArg1, int nArg2, uint32_t *uArg3)  // 16 字节条目区间构造到裸内存（返回终点）
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
    if ( uArg32 != nullptr )  // 若 uArg32 有效（非空）
      sub_480020(uArg32, nArg1);  // 14 字节元素容器区间赋值（技能槽内层列表）
    uArg32 += 4;
    LOBYTE(v7) = 0;
    nArg1 += 16;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x480A90 sub_480A90 —— 44 字节技能槽条目拷贝构造（含两内嵌列表）
// +0/+4 标量直拷，+8 由 ·sub_41B0D0 复制；+12 内嵌 8 字节元素列表走 ·sub_480360、+28 内嵌 4 字节元素列表走 ·sub_480400，整体 44 字节。
// ------------------------------------------------------------
unsigned int **/*thiscall*/ sub_480A90(unsigned int **this, int pArg2)  // 44 字节技能槽条目拷贝构造（含两内嵌列表）
{
  unsigned int **pThis_2; // ecx

  *this = *(unsigned int **)pArg2;
  *(this + 1) = *(unsigned int **)(pArg2 + 4);  // this+4〔宿主对象〕
  pThis_2 = this + 2;  // this+8〔nSkillRec8〕
  *pThis_2 = nullptr;
  sub_41B0D0(pThis_2, (unsigned int **)(pArg2 + 8));  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_480360(this + 3, pArg2 + 12);  // 8 字节元素容器区间赋值（简易构造版）
  sub_480400(this + 7, pArg2 + 28);  // 4 字节元素容器区间赋值（简易构造版）
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x480B10 sub_480B10 —— 14 字节容器尾插（容量不足回落 ·0x480880 插入）
// 空间足够时在 this+8 处由 ·sub_47E920 就地构造 1 个元素并前移终点 14 字节，否则转 ·sub_480880 指定位置插入。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_480B10(int *this, int nArg2)  // 14 字节容器尾插（容量不足回落 ·0x480880 插入）
{
  int pVecEnd_6; // ebx
  unsigned int fld_e2; // esi
  int fld_e22; // esi
  uint32_t *result; // eax

  pVecEnd_6 = *(this + 1);  // this+4〔宿主对象〕
  if ( pVecEnd_6 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - pVecEnd_6) / 14;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( pVecEnd_6 == 0 || fld_e2 >= (*(this + 3) - pVecEnd_6) / 14 )  // this+12〔nSkillRec12(推断)〕
    return sub_480880(this, &nArg2, *(this + 2), nArg2);  // 14 字节容器指定位置单元素插入（返回元素指针）
  fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  result = (uint32_t *)sub_47E920(fld_e22, 1, nArg2);  // 调 就地构造 1 个元素并前移终点 14 字节
  *(this + 2) = fld_e22 + 14;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x480BA0 sub_480BA0 —— 转发 ·0x4809C0（thunk：16 字节条目区间反向深拷贝）
// 调用约定号不同（cdecl 包装 stdcall），供 ·0x480FB0 插入路径复用同一搬移实现。
// ------------------------------------------------------------
int /*cdecl*/ sub_480BA0(int nArg1, int nArg2, int nArg3)  // 实现：转发 ·0x4809C0（thunk：16 字节条目区间反向深拷贝）
{
  return sub_4809C0(nArg1, nArg2, nArg3);  // 16 字节条目区间自后向前逐项深拷贝
}



// ------------------------------------------------------------
// 0x480BC0 sub_480BC0 —— 44 字节技能槽条目区间逐个拷贝构造
// 每项复制 +0/+4 标量，+8 走 ·sub_41B0D0，+12 列表由 ·sub_4800C0、+28 列表由 ·sub_480210 各自深拷贝；步长 44。
// ------------------------------------------------------------
int /*cdecl*/ sub_480BC0(int nArg1, int nArg2, int nArg3)  // 实现：44 字节技能槽条目区间逐个拷贝构造
{
  int nArg12; // esi
  int nArg32; // edi

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    *(uint32_t *)nArg32 = *(uint32_t *)nArg12;
    *(uint32_t *)(nArg32 + 4) = *(uint32_t *)(nArg12 + 4);  // nArg32+4〔宿主对象〕
    sub_41B0D0((unsigned int **)(nArg32 + 8), (unsigned int **)(nArg12 + 8));  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
    sub_4800C0(nArg32 + 12, nArg12 + 12);  // 8 字节元素容器区间赋值（三分支容量策略）
    sub_480210(nArg32 + 28, nArg12 + 28);  // 4 字节元素容器区间赋值（与 ·0x4800C0 同构）
    nArg12 += 44;
    nArg32 += 44;
  }
  while ( nArg12 != nArg2 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x480C20 sub_480C20 —— 16 字节条目填充 n 份同值副本
// 循环 nArg2 次，以 nArg3 为源经 ·sub_480020 在连续 16 字节槽位就地构造；由 ·0x480FB0 扩容时用于填充新增段。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_480C20(uint32_t *uArg1, int nArg2, int nArg3)  // 16 字节条目填充 n 份同值副本
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
    if ( uArg12 != nullptr )  // 若 uArg12 有效（非空）
      result = sub_480020(uArg12, nArg3);  // 结果 = 14 字节元素容器区间赋值（技能槽内层列表）
    --nArg2;
    uArg12 += 4;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x480CB0 sub_480CB0 —— 转发 ·0x480960（thunk：16 字节条目区间析构）
// 调用约定差异包装，供容器析构路径统一入口。
// ------------------------------------------------------------
int /*stdcall*/ sub_480CB0(int nArg1, int nArg2)  // 实现：转发 ·0x480960（thunk：16 字节条目区间析构）
{
  return sub_480960(nArg1, nArg2);  // 16 字节条目区间析构（内层对象走虚表首槽）
}



// ------------------------------------------------------------
// 0x480CD0 sub_480CD0 —— 16 字节条目区间删除 erase(first,last)
// 先把 [nArg3,nArg4) 之后的元素经 ·sub_480920 前移到 nArg3，再用 ·sub_480960 析构尾段并改写 this+8；*pDwArg2 回传新位置。
// ------------------------------------------------------------
int */*thiscall*/ sub_480CD0(int *this, int *pDwArg2, int nArg3, int nArg4)  // 16 字节条目区间删除 erase(first,last)
{
  int fld_e2; // edi

  if ( nArg3 != nArg4 )
  {
    fld_e2 = sub_480920(nArg4, *(this + 2), nArg3);  // 结果 = 16 字节条目区间自前向后逐项拷贝构造
    sub_480960(fld_e2, *(this + 2));  // 16 字节条目区间析构（内层对象走虚表首槽）
    *(this + 2) = fld_e2;  // this+8〔nSkillRec8(推断)〕
  }
  *pDwArg2 = nArg3;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x480D20 sub_480D20 —— 转发 ·0x480BC0（thunk：44 字节条目区间拷贝构造）
// 调用约定差异包装，供 ·0x481A30 前缀拷贝路径复用。
// ------------------------------------------------------------
int /*cdecl*/ sub_480D20(int nArg1, int nArg2, int nArg3)  // 实现：转发 ·0x480BC0（thunk：44 字节条目区间拷贝构造）
{
  return sub_480BC0(nArg1, nArg2, nArg3);  // 44 字节技能槽条目区间逐个拷贝构造
}



// ------------------------------------------------------------
// 0x480D40 sub_480D40 —— 24 字节条目区间拷贝构造（clong 主体 + 两标量）
// 每项 24 字节：主体由 ·sub_435020 复制，+16/+20 两标量直拷；目标为未初始化内存，返回终点指针。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_480D40(char *pszArg1, char *pszArg2, uint32_t *uArg3)  // 24 字节条目区间拷贝构造（clong 主体 + 两标量）
{
  uint32_t *uArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v6[4] = v6;
  v6[3] = uArg3;
  v7 = 0;
  while ( pszArg1 != pszArg2 )  // 当 pszArg1 != pszArg2 循环
  {
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )  // 若 uArg32 有效（非空）
    {
      sub_435020(pszArg1);  // uint32 向量整体赋值
      uArg32[4] = *((uint32_t *)pszArg1 + 4);
      uArg32[5] = *((uint32_t *)pszArg1 + 5);
    }
    uArg32 += 6;
    LOBYTE(v7) = 0;
    pszArg1 += 24;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x480DF0 sub_480DF0 —— 16 字节条目容器析构
// 对 this{+4,+8} 区间先 ·sub_480960 析构内层对象再 j__free，末尾清零 +4/+8/+12。
// ------------------------------------------------------------
void /*thiscall*/ sub_480DF0(int *this)  // 实现：16 字节条目容器析构
{
  int fld_e1; // eax

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    sub_480960(fld_e1, *(this + 2));  // 16 字节条目区间析构（内层对象走虚表首槽）
    j__free((void *)*(this + 1));  // this+4〔宿主对象〕
  }
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
}



// ------------------------------------------------------------
// 0x480E40 sub_480E40 —— 定长填充入口（转发 ·0x480C20，返回越过末尾的指针）
// 以 nArg2 份同值填充 pArg1 起的连续条目，回传 pArg1 + 16*nArg2。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_480E40(uint32_t *pArg1, int nArg2, int nArg3)  // 定长填充入口（转发 ·0x480C20，返回越过末尾的指针）
{
  sub_480C20(pArg1, nArg2, nArg3);  // 16 字节条目填充 n 份同值副本
  return &pArg1[4 * nArg2];
}



// ------------------------------------------------------------
// 0x480E70 sub_480E70 —— 44 字节条目区间构造到裸内存
// 目标为未初始化内存，逐项 44 字节经 ·sub_480A90 构造；与 ·0x480F40 析构、·0x4813A0 thunk 同族。
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_480E70(int nArg1, int nArg2, unsigned int **pDwArg3)  // 44 字节条目区间构造到裸内存
{
  unsigned int **pDwArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pDwArg32 = pDwArg3;
  v6[4] = v6;
  v6[3] = pDwArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )  // 当 nArg1 != nArg2 循环
  {
    LOBYTE(v7) = 1;
    if ( pDwArg32 != nullptr )  // 若 pDwArg32 有效（非空）
      sub_480A90(pDwArg32, nArg1);  // 44 字节技能槽条目拷贝构造（含两内嵌列表）
    pDwArg32 += 11;
    LOBYTE(v7) = 0;
    nArg1 += 44;
  }
  return pDwArg32;
}



// ------------------------------------------------------------
// 0x480F40 sub_480F40 —— 44 字节条目区间逐项析构（转 ·sub_47FA00）
// 与 ·0x481DF0 同族（不同对象类型，析构点分别为 ·sub_47FA00 与 ·sub_437950）。
// ------------------------------------------------------------
int /*stdcall*/ sub_480F40(int nArg1, int nArg2)  // 实现：44 字节条目区间逐项析构（转 ·sub_47FA00）
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 44 )
    result = sub_47FA00(i);  // 调 析构同族
  return result;
}



// ------------------------------------------------------------
// 0x480F70 sub_480F70 —— 44 字节条目容器析构（+4/+8/+12 三字段）
// 遍历 [this+4,this+8) 每项调 ·sub_47FA00 后释放缓冲并清零；供 ·0x481860、·0x482450 等上层析构复用。
// ------------------------------------------------------------
int /*thiscall*/ sub_480F70(int *this)  // 实现：44 字节条目容器析构（+4/+8/+12 三字段）
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  result = 0;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 44 )  // this+8〔nSkillRec8(推断)〕
      sub_47FA00(fld_e1);  // 调 析构同族
    j__free((void *)*(this + 1));  // this+4〔宿主对象〕
    result = 0;
  }
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x480FB0 sub_480FB0 —— 16 字节条目容器批量插入 insert(pos, n, value)
// 三条容量路径：余量足够时 ·sub_480A00 造尾段加 ·sub_480BA0 搬移、·sub_4808F0 填补新增位；余量不足时 ·sub_480E40 填充；容量不足时 operator new 后搬旧、·sub_480C20 填充、再搬尾；超限由 ·sub_47F990 抛异常。
// ------------------------------------------------------------
int /*thiscall*/ sub_480FB0(int *this, int pArg2, unsigned int uArg3, int nArg4)  // 实现：16 字节条目容器批量插入 insert(pos, n, value)
{
  int fld_e1; // edx
  int fld_e2; // ecx
  unsigned int fld_e3; // eax
  int fld_e22; // ecx
  unsigned int v10; // eax
  int fld_e27; // ecx
  int fld_e28; // eax
  char *pMem; // ebx
  int fld_e13; // ecx
  int fld_e29; // eax
  unsigned int v16; // edi
  uint32_t *fld_e23; // eax
  int fld_e26; // edi
  int v19; // edi
  uint32_t *v20; // eax
  int fld_e12; // [esp-18h] [ebp-4Ch]
  void *Block2; // [esp-18h] [ebp-4Ch]
  int fld_e25; // [esp-Ch] [ebp-40h]
  unsigned int fld_e24; // [esp-8h] [ebp-3Ch]
  int v26; // [esp+0h] [ebp-34h] BYREF
  uint32_t v27[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+1Ch] [ebp-18h]
  int *pThis; // [esp+20h] [ebp-14h]
  int *v30; // [esp+24h] [ebp-10h]
  int v31; // [esp+30h] [ebp-4h]
  uint32_t *v32; // [esp+40h] [ebp+Ch]
  int v33; // [esp+44h] [ebp+10h]

  v30 = &v26;
  pThis = this;
  sub_480020(v27, nArg4);  // 14 字节元素容器区间赋值（技能槽内层列表）
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  fld_e2 = 0;
  v31 = 0;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - fld_e1) >> 4;  // this+12〔nSkillRec12(推断)〕
  else
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
    if ( 0xFFFFFFF - fld_e2 < uArg3 )  // fld_e2=this+8 nSkillRec8
      sub_47F990(this);  // 调 抛 std::length_error（vector<T> too long）——vector 超长的标准抛出点
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e23 = (uint32_t *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
      Block = fld_e23;  // fld_e23=this+8 nSkillRec8
      if ( ((int)fld_e23 - pArg2) >> 4 >= uArg3 )  // fld_e23=this+8 nSkillRec8
      {
        v19 = (int)&fld_e23[-4 * uArg3];  // fld_e23=this+8 nSkillRec8
        v20 = sub_480A00(v19, (int)fld_e23, fld_e23);  // 结果 = 16 字节条目区间构造到裸内存（返回终点）
        Block2 = Block;
        *(this + 2) = (int)v20;  // this+8〔nSkillRec8(推断)〕
        sub_480BA0(pArg2, v19, Block2);  // 转发 ·0x4809C0（thunk：16 字节条目区间反向深拷贝）
        sub_4808F0(pArg2, pArg2 + 16 * uArg3, v27);  // 16 字节条目数组逐项深拷贝赋值
      }
      else
      {
        sub_480A00(pArg2, (int)fld_e23, (uint32_t *)(pArg2 + 16 * uArg3));  // 16 字节条目区间构造到裸内存（返回终点）
        fld_e24 = uArg3 - ((*(this + 2) - pArg2) >> 4);  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
        LOBYTE(v31) = 3;
        sub_480E40(fld_e25, fld_e24, v27);  // 定长填充入口（转发 ·0x480C20，返回越过末尾的指针）
        fld_e26 = 16 * uArg3 + *(this + 2);  // this+8〔nSkillRec8〕
        *(this + 2) = fld_e26;  // this+8〔nSkillRec8(推断)〕
        v31 = 0;
        sub_4808F0(pArg2, fld_e26 - 16 * uArg3, v27);  // 16 字节条目数组逐项深拷贝赋值
      }
    }
    else
    {
      if ( 0xFFFFFFF - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 nSkillRec12
        v10 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 nSkillRec12
      else
        v10 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
      else
        fld_e27 = 0;  // fld_e27=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_e27 )  // fld_e27=this+8 nSkillRec8
      {
        if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
          fld_e28 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
        else
          fld_e28 = 0;  // fld_e28=this+8 nSkillRec8
        v10 = uArg3 + fld_e28;
      }
      v33 = 16 * v10;
      pMem = (char *)operator new(16 * v10);  // 分配 16 × v10 字节数组
      fld_e12 = *(this + 1);  // this+4〔宿主对象〕
      Block = pMem;
      LOBYTE(v31) = 1;
      v32 = sub_480A00(fld_e12, pArg2, pMem);  // 结果 = 16 字节条目区间构造到裸内存（返回终点）
      sub_480C20(v32, uArg3, (int)v27);  // 16 字节条目填充 n 份同值副本
      sub_480A00(pArg2, *(this + 2), &v32[4 * uArg3]);  // 16 字节条目区间构造到裸内存（返回终点）
      fld_e13 = *(this + 1);  // this+4〔宿主对象〕
      v31 = 0;
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e29 = (*(this + 2) - fld_e13) >> 4;  // this+8〔nSkillRec8(推断)〕
      else
        fld_e29 = 0;  // fld_e29=this+8 nSkillRec8
      v16 = fld_e29 + uArg3;
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
      {
        sub_480960(fld_e13, *(this + 2));  // 16 字节条目区间析构（内层对象走虚表首槽）
        j__free((void *)*(this + 1));  // this+4〔宿主对象〕
      }
      *(this + 3) = (int)&pMem[v33];  // this+12〔nSkillRec12(推断)〕
      *(this + 2) = (int)&pMem[16 * v16];  // this+8〔nSkillRec8(推断)〕
      *(this + 1) = (int)pMem;  // this+4〔宿主对象〕
    }
  }
  v31 = -1;
  return sub_47F6E0(v27);  // 调 释放临时值
}


// ------------------------------------------------------------
// 0x481260 sub_481260 —— 16 字节条目容器 resize(n, value)
// n 小于当前项数时经 ·sub_480CD0 删除 [this+4+16n, this+8)；否则由 ·sub_480FB0 在尾端插入 (n-项数) 个临时值，末尾 ·sub_47F6E0 释放临时值。
// ------------------------------------------------------------
int /*thiscall*/ sub_481260(int *this, unsigned int uArg2, char pszArg3, int nArg4, int nArg5, int nArg6)  // 实现：16 字节条目容器 resize(n, value)
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int fld_e22; // edx

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( fld_e2 >= uArg2 )  // fld_e2=this+8 nSkillRec8
  {
    if ( fld_e1 != 0 && uArg2 < (*(this + 2) - fld_e1) >> 4 )  // this+8〔nSkillRec8(推断)〕
      sub_480CD0(this, (int *)&uArg2, fld_e1 + 16 * uArg2, *(this + 2));  // 16 字节条目区间删除 erase(first,last)
  }
  else
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    sub_480FB0(this, *(this + 2), uArg2 - fld_e22, (int)&pszArg3);  // 16 字节条目容器批量插入 insert(pos, n, value)
  }
  return sub_47F6E0(&pszArg3);  // 调 释放临时值
}



// ============================================================
// §B 0x481300-0x482A90  技能对象生命周期（ctor/dtor/字段组）
// ============================================================
// ------------------------------------------------------------
// 0x481300 sub_481300 —— 24 字节元素容器区间赋值
// 与 ·0x480020 同构，差异为元素步长 24：守卫 ·sub_434950、分配拷贝由 ·sub_480D40 处理 clong 加两标量。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_481300(uint32_t *this, int pArg2)  // 24 字节元素容器区间赋值
{
  int v2; // eax
  char *v5; // [esp-14h] [ebp-34h]
  char *v6; // [esp-10h] [ebp-30h]
  uint32_t *fld_e1; // [esp-Ch] [ebp-2Ch]
  uint32_t v8[8]; // [esp+0h] [ebp-20h] BYREF

  v2 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  v8[4] = v8;
  v8[3] = this;
  if ( v2 != 0 )
    v2 = (*(uint32_t *)(pArg2 + 8) - v2) / 24;  // pArg2+8〔nSkillRec8(推断)〕
  if ( (uint8_t)sub_434950(v2) != 0 )  // 24 字节元素向量预留
  {
    fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
    v6 = *(char **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    v5 = *(char **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v8[7] = 0;
    *(this + 2) = sub_480D40(v5, v6, fld_e1);  // 24 字节条目区间拷贝构造（clong 主体 + 两标量）
  }
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4813A0 sub_4813A0 —— 转发 ·0x480E70（thunk：44 字节条目区间构造）
// 目标为裸内存区间，供 ·0x481A30 扩容路径复用。
// ------------------------------------------------------------
unsigned int **/*stdcall*/ sub_4813A0(int nArg1, int nArg2, unsigned int **pDwArg3)  // 转发 ·0x480E70（thunk：44 字节条目区间构造）
{
  return sub_480E70(nArg1, nArg2, pDwArg3);  // 44 字节条目区间构造到裸内存
}



// ------------------------------------------------------------
// 0x4813C0 sub_4813C0 —— 44 字节条目自后向前逐项拷贝构造
// 每步回退 44 字节：+0 经 ·sub_439050 复制、+16 处子对象由 ·sub_4ED3F0 复制，尾部 +32/+36/+40 直拷。
// ------------------------------------------------------------
int /*cdecl*/ sub_4813C0(int nArg1, int nArg2, int nArg3)  // 实现：44 字节条目自后向前逐项拷贝构造
{
  int nArg22; // esi
  int nArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    nArg22 -= 44;
    nArg32 -= 44;
    sub_439050((void *)nArg22);  // 条目向量赋值（24 字节元素）
    sub_4ED3F0(nArg32 + 16, nArg22 + 16);  // int 向量拷贝赋值（全容量路径）
    *(uint32_t *)(nArg32 + 32) = *(uint32_t *)(nArg22 + 32);  // nArg32+32〔nHeight(推断)〕
    *(uint32_t *)(nArg32 + 36) = *(uint32_t *)(nArg22 + 36);  // nArg32+36〔nStateWord36(推断)〕
    *(uint8_t *)(nArg32 + 40) = *(uint8_t *)(nArg22 + 40);  // nArg32+40〔bStateSub40(推断)〕
  }
  while ( nArg22 != nArg1 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x481420 sub_481420 —— 节点字段组清零（+42..59）+ sub_5E5260 容器析构
// ------------------------------------------------------------
void /*thiscall*/ sub_481420(char *this)  // 实现：节点字段组清零（+42..59）+ sub_5E5260 容器析构
{
  uint32_t *pThis_68; // eax
  int i; // ecx
  uint32_t *pThis_84; // eax
  int j; // ecx
  uint32_t *pThis_C0; // edi
  char *pThis_33; // edi
  int pThis_43; // edi
  int pThis_44; // ecx
  int pThis_47; // edi
  int k; // [esp+8h] [ebp-4h]
  char *m; // [esp+8h] [ebp-4h]
  int n; // [esp+8h] [ebp-4h]
  int ii; // [esp+8h] [ebp-4h]

  *(uint32_t *)this = 0;  // *this = 0
  sub_41BFE0(szPassword);  // 驻留字符串设置（set(const char*)）
  sub_41BFE0(szPassword);  // 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 4) = 0;  // this+16〔nChannelTypeSel(推断)〕
  sub_41BFE0(szPassword);  // 驻留字符串设置（set(const char*)）
  if ( *((uint32_t *)this + 6) != 0 )  // this+24〔nPageMax(推断)〕
    j__free(*((void **)this + 6));  // 调 堆释放
  *((uint32_t *)this + 6) = 0;  // this+24〔nPageMax(推断)〕
  *((uint32_t *)this + 7) = 0;  // this+28〔pPanelVec(推断)〕
  *((uint32_t *)this + 8) = 0;  // this+32〔nHeight(推断)〕
  *((uint32_t *)this + 9) = 1;  // this+36〔nStateWord36(推断)〕
  *((uint32_t *)this + 10) = 1;  // this+40〔bStateSub40(推断)〕
  if ( *((uint32_t *)this + 12) != 0 )  // this+48〔pCmdVecBegin48(推断)〕
    j__free(*((void **)this + 12));  // this+12 物品类型号
  *((uint32_t *)this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *((uint32_t *)this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *((uint32_t *)this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  if ( *((uint32_t *)this + 16) != 0 )  // this+64〔apServerTabBtn(推断)〕
    j__free(*((void **)this + 16));  // this+16 频道型选中索引
  *((uint32_t *)this + 16) = 0;  // this+64〔apServerTabBtn(推断)〕
  *((uint32_t *)this + 17) = 0;  // this+68〔nCharCount(推断)〕
  *((uint32_t *)this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  *((uint32_t *)this + 19) = 0;  // this+76〔pBtnActionE〕
  *((uint32_t *)this + 20) = 0;  // this+80〔nAuraStage(推断)〕
  pThis_68 = this + 104;  // this+104 插值终点 Z
  for ( i = 5; i != 0; --i )  // 循环：i 从 5 递减到 0
  {
    *(pThis_68 - 5) = 0;  // pThis_68=this+104 插值终点 Z
    *pThis_68++ = 0;  // pThis_68=this+104 插值终点 Z
  }
  pThis_84 = this + 132;  // this+132 第 3 组·+60 增量项
  for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
  {
    *(pThis_84 - 2) = 0;  // pThis_84=this+132 第 3 组·+60 增量项
    *pThis_84 = 0;  // pThis_84=this+132 第 3 组·+60 增量项
    pThis_84[6] = 0;  // pThis_84=this+132 第 3 组·+60 增量项
    ++pThis_84;  // pThis_84=this+132 第 3 组·+60 增量项
  }
  if ( *((uint32_t *)this + 36) != 0 )  // this+144〔pFrameList144(推断)〕
    j__free(*((void **)this + 36));  // this+36 物品状态字
  *((uint32_t *)this + 36) = 0;  // this+144〔pFrameList144(推断)〕
  *((uint32_t *)this + 37) = 0;  // this+148〔fAdd148(推断)〕
  *((uint32_t *)this + 38) = 0;  // this+152〔nAdd152(推断)〕
  if ( *((uint32_t *)this + 42) != 0 )  // this+168〔pAppendVec(推断)〕
    j__free(*((void **)this + 42));  // 调 堆释放
  *((uint32_t *)this + 42) = 0;  // this+168〔pAppendVec(推断)〕
  *((uint32_t *)this + 43) = 0;  // this+172〔pAppendVecEnd(推断)〕
  *((uint32_t *)this + 44) = 0;  // this+176〔pAppendVecCap(推断)〕
  *(this + 180) = 1;  // this+180 半径/计数
  pThis_C0 = this + 192;  // this+192 对话 id
  for ( k = 2; k != 0; --k )  // 循环：k 从 2 递减到 0
  {
    sub_41BFE0(szPassword);  // 驻留字符串设置（set(const char*)）
    *pThis_C0++ = 0;  // pThis_C0=this+192 对话 id
  }
  pThis_33 = *((char **)this + 51);
  if ( pThis_33 != nullptr )  // 若 pThis_33 有效（非空）
  {
    for ( m = *((char **)this + 52); pThis_33 != m; pThis_33 += 24 )  // this+52 光环状态字节
      sub_5E5260(pThis_33);  // 调 动画子对象清理临时缓冲
    j__free(*((void **)this + 51));  // 调 堆释放
  }
  *((uint32_t *)this + 51) = 0;  // this+204〔pSubAnim204(推断)〕
  *((uint32_t *)this + 52) = 0;  // this+208〔nField208(推断)〕
  *((uint32_t *)this + 53) = 0;  // this+212〔nField212(推断)〕
  if ( *((uint32_t *)this + 55) != 0 )  // this+220〔nSnapDst220(推断)〕
    j__free(*((void **)this + 55));  // 调 堆释放
  *((uint32_t *)this + 55) = 0;  // this+220〔nSnapDst220(推断)〕
  *((uint32_t *)this + 56) = 0;  // this+224〔nSnapDst224(推断)〕
  *((uint32_t *)this + 57) = 0;  // this+228〔nSnapDst228(推断)〕
  *((uint32_t *)this + 58) = 1;  // this+232〔bSyncFlag〕
  *((uint32_t *)this + 59) = 0;  // this+236〔nSyncArgA〕
  *(this + 240) = 1;  // this+960〔nBigStateMirror960(推断)〕
  sub_41BFE0(szPassword);  // 驻留字符串设置（set(const char*)）
  if ( *((uint32_t *)this + 63) != 0 )  // this+252〔nQuad2〕
    j__free(*((void **)this + 63));  // 调 堆释放
  *((uint32_t *)this + 63) = 0;  // this+252〔nQuad2〕
  *((uint32_t *)this + 64) = 0;  // this+256〔bQuad3〕
  *((uint32_t *)this + 65) = 0;  // this+260〔nQuad4〕
  pThis_43 = *((uint32_t *)this + 67);  // this+67 周期 ms
  if ( pThis_43 != 0 )
  {
    pThis_44 = *((uint32_t *)this + 68);  // this+68 角色数
    for ( n = pThis_44; pThis_43 != pThis_44; pThis_43 += 16 )
    {
      if ( *(uint32_t *)(pThis_43 + 4) != 0 )  // pThis_43+4〔宿主对象〕
      {
        j__free(*(void **)(pThis_43 + 4));  // pThis_43+4〔宿主对象〕
        pThis_44 = n;
      }
      *(uint32_t *)(pThis_43 + 4) = 0;  // pThis_43+4〔宿主对象〕
      *(uint32_t *)(pThis_43 + 8) = 0;  // pThis_43+8〔nSkillRec8(推断)〕
      *(uint32_t *)(pThis_43 + 12) = 0;  // pThis_43+12〔nSkillRec12(推断)〕
    }
    j__free(*((void **)this + 67));  // this+67〔nPeriodMs〕
  }
  *((uint32_t *)this + 67) = 0;  // this+67 周期 ms
  *((uint32_t *)this + 68) = 0;  // this+68 角色数
  *((uint32_t *)this + 69) = 0;  // this+276〔pMapEntry〕
  pThis_47 = *((uint32_t *)this + 71);  // this+284〔bBindGate284(推断)〕
  if ( pThis_47 != 0 )  // pThis_47=this+284 bBindGate284
  {
    for ( ii = *((uint32_t *)this + 72); pThis_47 != ii; pThis_47 += 44 )  // this+288〔pMaster288(推断)〕
      sub_47FA00(pThis_47);  // 调 析构同族
    j__free(*((void **)this + 71));  // this+71〔bMoveType〕
  }
  *((uint32_t *)this + 71) = 0;  // this+284〔bBindGate284(推断)〕
  *((uint32_t *)this + 72) = 0;  // this+288〔pMaster288(推断)〕
  *((uint32_t *)this + 73) = 0;  // this+292〔nOpenMode292(推断)〕
  *((uint32_t *)this + 74) = 0;  // this+296〔bInitFlag296(推断)〕
  *((uint32_t *)this + 75) = 0;  // this+300〔pAnim300〕
  *(this + 320) = 0;
  *((uint32_t *)this + 81) = 0;  // this+324〔nRandPick324〕
  *((uint32_t *)this + 82) = 0;
  *((uint32_t *)this + 83) = 0;  // this+332〔bReservedConn〕
  if ( *((uint32_t *)this + 77) != 0 )  // this+77 【推断】公会标志字节 B
    j__free(*((void **)this + 77));  // this+77〔bGuildFlagB〕
  *((uint32_t *)this + 77) = 0;  // this+77 【推断】公会标志字节 B
  *((uint32_t *)this + 78) = 0;  // this+78 【推断】公会标志字节 C
  *((uint32_t *)this + 79) = 0;
}


// ------------------------------------------------------------
// 0x481720 sub_481720 —— 技能树节点复位（+200..292 字段组：冷却/等级/树位）
// ------------------------------------------------------------
int /*thiscall*/ sub_481720(int this)  // 实现：技能树节点复位（+200..292 字段组：冷却/等级/树位）
{
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  sub_41BFE0(szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  sub_41BFE0(szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
  sub_41BFE0(szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 64) = 0;  // this+64〔apServerTabBtn(推断)〕等 2 字段
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 72) = 0;  // this+72〔nSnapshot72(推断)〕等 2 字段
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 168) = 0;  // this+168〔pAppendVec(推断)〕等 2 字段
  *(uint32_t *)(this + 172) = 0;  // this+172〔pAppendVecEnd(推断)〕等 2 字段
  *(uint32_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  `eh vector constructor iterator'((void *)(this + 184), 4u, 2, sub_432D20, sub_401060);  // 共享串槽初始化（空串）
  sub_436F50(this + 200);  // 24B 表复位
  *(uint32_t *)(this + 244) = 0;  // this+244〔fSyncTime〕
  sub_41BFE0(szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 252) = 0;  // this+252〔nQuad2〕
  *(uint32_t *)(this + 256) = 0;  // this+256〔bQuad3〕
  *(uint32_t *)(this + 260) = 0;  // this+260〔nQuad4〕
  *(uint32_t *)(this + 268) = 0;  // this+268〔field_10C〕
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;  // this+276〔pMapEntry〕
  *(uint32_t *)(this + 284) = 0;  // this+284〔bBindGate284(推断)〕
  *(uint32_t *)(this + 288) = 0;  // this+288〔pMaster288(推断)〕
  *(uint32_t *)(this + 292) = 0;  // this+292〔nOpenMode292(推断)〕
  *(uint32_t *)(this + 308) = 0;  // this+1232〔pNameTagCtrl(推断)〕
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  sub_481420((char *)this);  // 节点字段组清零（+42..59）+ sub_5E5260 容器析构
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x481860 sub_481860 —— 技能树节点析构（+244..280 容器与引用清理）
// ------------------------------------------------------------
void /*thiscall*/ sub_481860(int this)  // 实现：技能树节点析构（+244..280 容器与引用清理）
{
  void *fld_134; // eax
  int fld_10C; // eax

  fld_134 = *(void **)(this + 308);  // this+1232〔pNameTagCtrl(推断)〕
  if ( fld_134 != nullptr )  // 若 fld_134 有效（非空）
    j__free(fld_134);  // 调 堆释放
  *(uint32_t *)(this + 308) = 0;  // this+1232〔pNameTagCtrl(推断)〕
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  sub_480F70((int *)(this + 280));  // 44 字节条目容器析构（+4/+8/+12 三字段）
  fld_10C = *(uint32_t *)(this + 268);  // this+268〔field_10C〕
  if ( fld_10C != 0 )
  {
    sub_42CC00(fld_10C, *(uint32_t *)(this + 272));  // 16 字节槽组释放
    j__free(*(void **)(this + 268));  // 调 堆释放
  }
  *(uint32_t *)(this + 268) = 0;  // this+268〔field_10C〕
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;  // this+276〔pMapEntry〕
  if ( *(uint32_t *)(this + 252) != 0 )  // this+252〔nQuad2〕
    j__free(*(void **)(this + 252));  // this+252〔nQuad2〕
  *(uint32_t *)(this + 252) = 0;  // this+252〔nQuad2〕
  *(uint32_t *)(this + 256) = 0;  // this+256〔bQuad3〕
  *(uint32_t *)(this + 260) = 0;  // this+260〔nQuad4〕
  sub_41B010((void **)(this + 244));  // 驻留句柄析构（引用计数减到 0 释放）
  if ( *(uint32_t *)(this + 220) != 0 )  // this+220〔nSnapDst220(推断)〕
    j__free(*(void **)(this + 220));  // 释放 this+220〔nSnapDst220(推断)〕堆块
  *(uint32_t *)(this + 220) = 0;  // this+220〔nSnapDst220(推断)〕
  *(uint32_t *)(this + 224) = 0;  // this+224〔nSnapDst224(推断)〕
  *(uint32_t *)(this + 228) = 0;  // this+228〔nSnapDst228(推断)〕
  sub_435850(this + 200);  // 24 字节条目向量销毁
  `eh vector destructor iterator'((void *)(this + 184), 4u, 2, (void (/*thiscall*/ *)(void *))sub_401060);  // this+184〔bSingleTarget(推断)〕
  if ( *(uint32_t *)(this + 168) != 0 )  // this+168〔pAppendVec(推断)〕等 2 字段
    j__free(*(void **)(this + 168));  // 释放 this+168〔pAppendVec(推断)〕堆块
  *(uint32_t *)(this + 168) = 0;  // this+168〔pAppendVec(推断)〕等 2 字段
  *(uint32_t *)(this + 172) = 0;  // this+172〔pAppendVecEnd(推断)〕等 2 字段
  *(uint32_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 144) != 0 )  // this+144〔pFrameList144(推断)〕等 2 字段
    j__free(*(void **)(this + 144));  // 释放 this+144〔pFrameList144(推断)〕堆块
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 64) != 0 )  // this+64〔apServerTabBtn(推断)〕等 2 字段
    j__free(*(void **)(this + 64));  // 释放 this+64〔apServerTabBtn(推断)〕堆块
  *(uint32_t *)(this + 64) = 0;  // this+64〔apServerTabBtn(推断)〕等 2 字段
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 72) = 0;  // this+72〔nSnapshot72(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 48) != 0 )  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    j__free(*(void **)(this + 48));  // 释放 this+48〔pCmdVecBegin48(推断)〕堆块
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 24) != 0 )  // this+24〔nPageMax(推断)〕等 2 字段
    j__free(*(void **)(this + 24));  // 释放 this+24〔nPageMax(推断)〕堆块
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  sub_41B010((void **)(this + 12));  // 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 8));  // 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 4));  // 驻留句柄析构（引用计数减到 0 释放）
}



// ------------------------------------------------------------
// 0x481A30 sub_481A30 —— 44 字节条目容器深拷贝赋值（三分支容量策略）
// 清空 ·sub_480F70、计数 ·sub_527B90、前缀拷贝 ·sub_480D20、尾段构造 ·sub_480E70、旧尾析构 ·sub_480F40、守卫 ·sub_47FBD0；与 ·0x480620 同族但条目为 44 字节。
// ------------------------------------------------------------
int /*thiscall*/ sub_481A30(int this, int pArg2)  // 实现：44 字节条目容器深拷贝赋值（三分支容量策略）
{
  int v3; // eax
  unsigned int v4; // ecx
  int pVecEnd_12; // ebx
  unsigned int fld_8; // eax
  int v8; // eax
  int v9; // eax
  unsigned int fld_C; // eax
  int v11; // edi
  int v12; // eax

  if ( this == pArg2 )
    return this;  // 返回自身指针
  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) / 44) == 0 )  // pArg2+8〔nSkillRec8(推断)〕
  {
    sub_480F70((int *)this);  // 44 字节条目容器析构（+4/+8/+12 三字段）
    return this;  // 返回自身指针
  }
  pVecEnd_12 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( pVecEnd_12 != 0 )  // fld_4=this+4 宿主对象
    fld_8 = (*(uint32_t *)(this + 8) - pVecEnd_12) / 44;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v4 > fld_8 )  // fld_8=this+8 nSkillRec8
  {
    if ( pVecEnd_12 != 0 )  // fld_4=this+4 宿主对象
      fld_C = (*(uint32_t *)(this + 12) - pVecEnd_12) / 44;  // this+12〔nSkillRec12(推断)〕等 2 字段
    else
      fld_C = 0;  // fld_C=this+12 nSkillRec12
    if ( v4 <= fld_C )  // fld_C=this+12 nSkillRec12
    {
      v11 = *(uint32_t *)(pArg2 + 4) + 44 * sub_527B90(this);  // 调 取 size
      sub_480D20(*(uint32_t *)(pArg2 + 4), v11, pVecEnd_12);  // 转发 ·0x480BC0（thunk：44 字节条目区间拷贝构造）
      *(uint32_t *)(this + 8) = sub_480E70(v11, *(uint32_t *)(pArg2 + 8), *(unsigned int ***)(this + 8));  // 44 字节条目区间构造到裸内存
      return this;  // 返回自身指针
    }
    if ( pVecEnd_12 != 0 )  // fld_4=this+4 宿主对象
    {
      sub_480F40(pVecEnd_12, *(uint32_t *)(this + 8));  // 44 字节条目区间逐项析构（转 ·sub_47FA00）
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    }
    v12 = sub_527B90(pArg2);  // 调 取 size
    if ( (uint8_t)sub_47FBD0(v12) != 0 )  // 调 条目上限 0x5D1745D（=2^32/44），超限抛 0x47F990
      *(uint32_t *)(this + 8) = sub_4813A0(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(unsigned int ***)(this + 4));  // 转发 ·0x480E70（thunk：44 字节条目区间构造）
    return this;  // 返回自身指针
  }
  v8 = sub_480BC0(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), pVecEnd_12);  // 结果 = 44 字节技能槽条目区间逐个拷贝构造
  sub_480F40(v8, *(uint32_t *)(this + 8));  // 44 字节条目区间逐项析构（转 ·sub_47FA00）
  v9 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 44 * ((*(uint32_t *)(pArg2 + 8) - v9) / 44);  // this+8〔nSkillRec8(推断)〕等 4 字段
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);  // this+8〔nSkillRec8(推断)〕等 4 字段
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x481BB0 sub_481BB0 —— 44 字节条目拷贝构造（24 字节列表 + clong + 尾标量）
// +4..+12 的 24 字节元素列表走 ·sub_481300 深拷贝，+16 起 clong 由 ·sub_435020 复制，+32/+36/+40 标量直拷。
// ------------------------------------------------------------
int /*thiscall*/ sub_481BB0(int this, int pArg2)  // 实现：44 字节条目拷贝构造（24 字节列表 + clong + 尾标量）
{
  sub_481300((uint32_t *)this, pArg2);  // 24 字节元素容器区间赋值
  sub_435020((void *)(pArg2 + 16));  // uint32 向量整体赋值
  *(uint32_t *)(this + 32) = *(uint32_t *)(pArg2 + 32);  // this+32〔nHeight(推断)〕等 2 字段
  *(uint32_t *)(this + 36) = *(uint32_t *)(pArg2 + 36);  // this+36〔nStateWord36(推断)〕等 2 字段
  *(uint8_t *)(this + 40) = *(uint8_t *)(pArg2 + 40);  // this+40〔bStateSub40(推断)〕等 2 字段
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x481C20 sub_481C20 —— 44 字节条目区间同值赋值（源 pArg3 反复）
// 每项 +16 处子对象经 ·sub_4ED3F0、+0 处经 ·sub_439050 按源 pArg3 复制，尾标量直拷；由 ·0x482650 插入时用于填补新增位。
// ------------------------------------------------------------
int /*cdecl*/ sub_481C20(int nArg1, int nArg2, void *pArg3)  // 实现：44 字节条目区间同值赋值（源 pArg3 反复）
{
  int result; // eax
  int i; // esi

  result = nArg2;
  for ( i = nArg1; i != nArg2; i += 44 )
  {
    sub_439050(pArg3);  // 条目向量赋值（24 字节元素）
    sub_4ED3F0(i + 16, (int)pArg3 + 16);  // int 向量拷贝赋值（全容量路径）
    *(uint32_t *)(i + 32) = *((uint32_t *)pArg3 + 8);
    result = nArg2;
    *(uint32_t *)(i + 36) = *((uint32_t *)pArg3 + 9);
    *(uint8_t *)(i + 40) = *((uint8_t *)pArg3 + 40);
  }
  return result;
}



// ------------------------------------------------------------
// 0x481C70 sub_481C70 —— 转发 ·0x4813C0（thunk：44 字节条目反向前缀拷贝构造）
// 供 ·0x482650 插入路径腾挪尾部区间复用。
// ------------------------------------------------------------
int /*cdecl*/ sub_481C70(int nArg1, int nArg2, int nArg3)  // 实现：转发 ·0x4813C0（thunk：44 字节条目反向前缀拷贝构造）
{
  return sub_4813C0(nArg1, nArg2, nArg3);  // 44 字节条目自后向前逐项拷贝构造
}



// ------------------------------------------------------------
// 0x481C90 sub_481C90 —— 44 字节条目区间拷贝构造到裸内存（每项 ·0x481BB0）
// 以区间指针 nArg1..nArg2 为源逐项构造 44 字节条目，返回终点地址。
// ------------------------------------------------------------
int /*cdecl*/ sub_481C90(int nArg1, int nArg2, int nArg3)  // 实现：44 字节条目区间拷贝构造到裸内存（每项 ·0x481BB0）
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )  // 当 nArg1 != nArg2 循环
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
      sub_481BB0(nArg32, nArg1);  // 44 字节条目拷贝构造（24 字节列表 + clong + 尾标量）
    nArg32 += 44;
    LOBYTE(v7) = 0;
    nArg1 += 44;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x481D40 sub_481D40 —— 44 字节条目定长填充（nArg2 项，源 nArg3）
// 循环 nArg2 次每项经 ·sub_481BB0 以 nArg3 为源构造；由 ·0x482650 扩容时填补新增段。
// ------------------------------------------------------------
void /*cdecl*/ sub_481D40(int nArg1, int nArg2, int nArg3)  // 实现：44 字节条目定长填充（nArg2 项，源 nArg3）
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
    if ( nArg12 != 0 )
      sub_481BB0(nArg12, nArg3);  // 44 字节条目拷贝构造（24 字节列表 + clong + 尾标量）
    --nArg2;
    nArg12 += 44;
    LOBYTE(v6) = 0;
  }
}



// ------------------------------------------------------------
// 0x481DF0 sub_481DF0 —— 44 字节条目区间逐项析构（转 ·sub_437950）
// 清空路径：析构后释放缓冲并复位 +4/+8/+12（见 ·0x481E20 同源配对）。
// ------------------------------------------------------------
int /*stdcall*/ sub_481DF0(int nArg1, int nArg2)  // 实现：44 字节条目区间逐项析构（转 ·sub_437950）
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 44 )
    result = sub_437950(i);  // 结果 = 子对象析构（向量+缓冲）
  return result;
}



// ------------------------------------------------------------
// 0x481E20 sub_481E20 —— 44 字节条目容器析构（与 ·0x481DF0 配套）
// 遍历 [this+4,this+8) 每项调 ·sub_437950 后释放缓冲并清零 +4/+8/+12。
// ------------------------------------------------------------
int /*thiscall*/ sub_481E20(int *this)  // 实现：44 字节条目容器析构（与 ·0x481DF0 配套）
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  result = 0;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 44 )  // this+8〔nSkillRec8(推断)〕
      sub_437950(fld_e1);  // 子对象析构（向量+缓冲）
    j__free((void *)*(this + 1));  // this+4〔宿主对象〕
    result = 0;
  }
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x481E70 sub_481E70 —— 定长填充入口（转发 ·0x481D40，返回越过末尾的指针）
// 以 nArg2 项填充 nArg1 起区间，回传 nArg1 + 44*nArg2。
// ------------------------------------------------------------
int /*stdcall*/ sub_481E70(int nArg1, int nArg2, int nArg3)  // 实现：定长填充入口（转发 ·0x481D40，返回越过末尾的指针）
{
  sub_481D40(nArg1, nArg2, nArg3);  // 44 字节条目定长填充（nArg2 项，源 nArg3）
  return nArg1 + 44 * nArg2;
}



// ------------------------------------------------------------
// 0x481EA0 sub_481EA0 —— CNRDSkill 主体字段组复位（+16..+472）
// 字符串字段经 ·sub_41BFE0 以默认串 szPassword 清空，+44/+88/+104 走 ·sub_47F6E0，多处 14 字节列表按虚表首槽析构后释放（+296/+312/+344/+360/+408），44 字节列表走 ·sub_437950（+388/+440）、+424 走 ·sub_480960。
// ------------------------------------------------------------
void /*thiscall*/ sub_481EA0(int this)  // 实现：CNRDSkill 主体字段组复位（+16..+472）
{
  int pThis_D0; // edi
  char *fld_128; // edi
  char *fld_138; // edi
  char *fld_158; // edi
  char *fld_168; // edi
  int fld_184; // edi
  char *fld_198; // edi
  int fld_1A8; // eax
  int fld_1B8; // edi
  int i; // [esp+Ch] [ebp-4h]
  char *j; // [esp+Ch] [ebp-4h]
  char *k; // [esp+Ch] [ebp-4h]
  char *m; // [esp+Ch] [ebp-4h]
  char *n; // [esp+Ch] [ebp-4h]
  int ii; // [esp+Ch] [ebp-4h]
  char *jj; // [esp+Ch] [ebp-4h]
  int kk; // [esp+Ch] [ebp-4h]

  sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41BFE0((void **)(this + 16), szPassword);  // 驻留字符串设置（set(const char*)）
  sub_41BFE0((void **)(this + 20), szPassword);  // 驻留字符串设置（set(const char*)）
  sub_41BFE0((void **)(this + 24), szPassword);  // 驻留字符串设置（set(const char*)）
  sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_47F6E0(this + 44);  // 调 释放临时值
  sub_41A590(1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_47F6E0(this + 88);  // 调 释放临时值
  sub_47F6E0(this + 104);  // 调 释放临时值
  *(uint32_t *)(this + 120) = 0;  // this+120〔pAnimObj〕
  sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  pThis_D0 = this + 208;  // this+208 【推断】子链状态槽
  for ( i = 5; i != 0; --i )  // 循环：i 从 5 递减到 0
  {
    sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_D0 += 14;  // pThis_D0=this+208 子链状态槽
  }
  sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_128 = *(char **)(this + 296);  // this+296 【推断】打开槽初始化字节
  if ( fld_128 != nullptr )  // 若 fld_128 有效（非空）
  {
    for ( j = *(char **)(this + 300); fld_128 != j; fld_128 += 14 )  // this+300〔pAnim300〕
      (**(void (/*thiscall*/ ***)(char *, uint32_t))fld_128)(fld_128, 0);  // fld_128=this+296 打开槽初始化字节
    j__free(*(void **)(this + 296));  // 释放 this+296〔bInitFlag296(推断)〕堆块
  }
  *(uint32_t *)(this + 296) = 0;  // this+296〔bInitFlag296(推断)〕
  *(uint32_t *)(this + 300) = 0;  // this+300〔pAnim300〕
  *(uint32_t *)(this + 304) = 0;  // this+304〔pLayer304(推断)〕
  fld_138 = *(char **)(this + 312);
  if ( fld_138 != nullptr )  // 若 fld_138 有效（非空）
  {
    for ( k = *(char **)(this + 316); fld_138 != k; fld_138 += 14 )
      (**(void (/*thiscall*/ ***)(char *, uint32_t))fld_138)(fld_138, 0);
    j__free(*(void **)(this + 312));  // 调 堆释放
  }
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  if ( *(uint32_t *)(this + 328) != 0 )  // this+1312〔pRowVec1312〕
    j__free(*(void **)(this + 328));  // this+1312〔pRowVec1312〕
  *(uint32_t *)(this + 328) = 0;  // this+1312〔pRowVec1312〕
  *(uint32_t *)(this + 332) = 0;  // this+332〔bReservedConn〕
  *(uint32_t *)(this + 336) = 0;
  fld_158 = *(char **)(this + 344);  // this+344〔nReservedDelay〕
  if ( fld_158 != nullptr )  // 若 fld_158 有效（非空）
  {
    for ( m = *(char **)(this + 348); fld_158 != m; fld_158 += 14 )  // this+348〔pParamTbl348〕
      (**(void (/*thiscall*/ ***)(char *, uint32_t))fld_158)(fld_158, 0);  // fld_158=this+344 nReservedDelay
    j__free(*(void **)(this + 344));  // this+344〔nReservedDelay〕
  }
  *(uint32_t *)(this + 344) = 0;  // this+344〔nReservedDelay〕
  *(uint32_t *)(this + 348) = 0;  // this+348〔pParamTbl348〕
  *(uint32_t *)(this + 352) = 0;  // this+352〔uHitCtx352〕
  fld_168 = *(char **)(this + 360);
  if ( fld_168 != nullptr )  // 若 fld_168 有效（非空）
  {
    for ( n = *(char **)(this + 364); fld_168 != n; fld_168 += 14 )  // this+1456〔nUdpReportField(推断)〕
      (**(void (/*thiscall*/ ***)(char *, uint32_t))fld_168)(fld_168, 0);
    j__free(*(void **)(this + 360));  // 调 堆释放
  }
  *(uint32_t *)(this + 360) = 0;
  *(uint32_t *)(this + 364) = 0;  // this+364〔pAnimNameStr(推断)〕等 2 字段
  *(uint32_t *)(this + 368) = 0;  // this+368〔nBindPos368〕
  *(uint8_t *)(this + 372) = 1;  // this+372〔nBindRef372〕
  *(uint32_t *)(this + 376) = 0;  // this+376〔nBindRef376〕
  *(uint32_t *)(this + 380) = 0;  // this+380〔attackinfo 指针〕
  fld_184 = *(uint32_t *)(this + 388);  // this+388〔fAtkCtxVal(推断)〕
  if ( fld_184 != 0 )  // fld_184=this+388 fAtkCtxVal
  {
    for ( ii = *(uint32_t *)(this + 392); fld_184 != ii; fld_184 += 44 )  // fld_184=this+388 fAtkCtxVal
      sub_437950(fld_184);  // 子对象析构（向量+缓冲）
    j__free(*(void **)(this + 388));  // 释放 this+388〔fAtkCtxVal(推断)〕堆块
  }
  *(uint32_t *)(this + 388) = 0;  // this+388〔fAtkCtxVal(推断)〕
  *(uint32_t *)(this + 392) = 0;
  *(uint32_t *)(this + 396) = 0;  // this+396〔uReflectCtx(推断)〕
  sub_41BFE0((void **)(this + 400), szPassword);  // 驻留字符串设置（set(const char*)）
  fld_198 = *(char **)(this + 408);  // this+408〔uAtkLimb0〕
  if ( fld_198 != nullptr )  // 若 fld_198 有效（非空）
  {
    for ( jj = *(char **)(this + 412); fld_198 != jj; fld_198 += 14 )  // this+412〔uAtkLimb1〕
      (**(void (/*thiscall*/ ***)(char *, uint32_t))fld_198)(fld_198, 0);  // fld_198=this+408 uAtkLimb0
    j__free(*(void **)(this + 408));  // this+408〔uAtkLimb0〕
  }
  *(uint32_t *)(this + 408) = 0;  // this+408〔uAtkLimb0〕
  *(uint32_t *)(this + 412) = 0;  // this+412〔uAtkLimb1〕
  *(uint32_t *)(this + 416) = 0;
  fld_1A8 = *(uint32_t *)(this + 424);  // this+424〔f_AtkRateX10〕
  if ( fld_1A8 != 0 )  // fld_1A8=this+424 f_AtkRateX10
  {
    sub_480960(fld_1A8, *(uint32_t *)(this + 428));  // 16 字节条目区间析构（内层对象走虚表首槽）
    j__free(*(void **)(this + 424));  // this+424〔f_AtkRateX10〕
  }
  *(uint32_t *)(this + 424) = 0;  // this+424〔f_AtkRateX10〕
  *(uint32_t *)(this + 428) = 0;
  *(uint32_t *)(this + 432) = 0;  // this+1728〔nDblClickSlotA(推断)〕
  fld_1B8 = *(uint32_t *)(this + 440);  // this+440〔包围盒左界〕
  if ( fld_1B8 != 0 )
  {
    for ( kk = *(uint32_t *)(this + 444); fld_1B8 != kk; fld_1B8 += 44 )
      sub_47FA00(fld_1B8);  // 调 析构同族
    j__free(*(void **)(this + 440));  // 调 堆释放
  }
  *(uint32_t *)(this + 440) = 0;  // this+440〔包围盒左界〕
  *(uint32_t *)(this + 444) = 0;  // this+444〔包围盒右界〕
  *(uint32_t *)(this + 448) = 0;  // this+448〔uAtkStage448(推断)〕
  *(uint32_t *)(this + 452) = 0;  // this+452〔nAtkRollVal(推断)〕
  *(uint32_t *)(this + 456) = 0;  // this+456〔pKeyVecEnd(推断)〕
  *(uint8_t *)(this + 476) = 0;
  *(uint32_t *)(this + 480) = 0;
  *(uint32_t *)(this + 484) = 0;
  *(uint32_t *)(this + 488) = 0;
  if ( *(uint32_t *)(this + 464) != 0 )  // this+464 仅见复位
    j__free(*(void **)(this + 464));  // this+464 仅见复位
  *(uint32_t *)(this + 464) = 0;  // this+464 仅见复位
  *(uint32_t *)(this + 468) = 0;
  *(uint32_t *)(this + 472) = 0;
}


// ------------------------------------------------------------
// 0x482240 sub_482240 —— 技能对象构造（clong 虚表字段组 + 5×14 字节数组）
// 逐个建立 clong 字段虚表（+0/+28/+60/+74/+124/+278 等），+138 与 +208 各以 eh vector constructor iterator 构造 5 个 14 字节元素，末尾调 ·sub_481EA0 统一复位尾部字段。
// ------------------------------------------------------------
char */*thiscall*/ sub_482240(char *this)  // 技能对象构造（clong 虚表字段组 + 5×14 字节数组）
{
  sub_41A630((unsigned int)this);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)this = &clong::`vftable';  // 构造装配 vftable：clong
  *((uint32_t *)this + 4) = 0;  // this+16〔nChannelTypeSel(推断)〕
  sub_41BFE0((void **)this + 4, szPassword);  // 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 5) = 0;  // this+20〔nPage(推断)〕
  sub_41BFE0((void **)this + 5, szPassword);  // 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 6) = 0;  // this+24〔nPageMax(推断)〕
  sub_41BFE0((void **)this + 6, szPassword);  // 驻留字符串设置（set(const char*)）
  sub_41A630((unsigned int)(this + 28));  // 调 防篡改字段读校验（crypt 逆运算链）
  *((uint32_t *)this + 7) = &clong::`vftable';  // 构造装配 vftable：clong
  *((uint32_t *)this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *((uint32_t *)this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *((uint32_t *)this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  sub_41A630((unsigned int)(this + 60));  // 调 防篡改字段读校验（crypt 逆运算链）
  *((uint32_t *)this + 15) = &clong::`vftable';  // 构造装配 vftable：clong
  sub_41A630((unsigned int)(this + 74));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)(this + 74) = &clong::`vftable';  // 构造装配 vftable：clong
  *((uint32_t *)this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  *((uint32_t *)this + 24) = 0;  // this+96〔nStatusMode(推断)〕
  *((uint32_t *)this + 25) = 0;  // this+100〔bEnchantDone(推断)〕
  *((uint32_t *)this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *((uint32_t *)this + 28) = 0;  // this+112〔pHostComp112〕
  *((uint32_t *)this + 29) = 0;  // this+116〔会话上下文〕
  sub_41A630((unsigned int)(this + 124));  // 调 防篡改字段读校验（crypt 逆运算链）
  *((uint32_t *)this + 31) = &clong::`vftable';  // 构造装配 vftable：clong
  `eh vector constructor iterator'(this + 138, 0xEu, 5, (void (/*thiscall*/ *)(void *))sub_401040, sub_432D10);  // clong 构造（·sub_41A630 随机源初始化 + 挂 clong::vftable）
  `eh vector constructor iterator'(this + 208, 0xEu, 5, (void (/*thiscall*/ *)(void *))sub_401040, sub_432D10);  // clong 构造（·sub_41A630 随机源初始化 + 挂 clong::vftable）
  sub_41A630((unsigned int)(this + 278));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)(this + 278) = &clong::`vftable';  // 构造装配 vftable：clong
  *((uint32_t *)this + 74) = 0;  // this+296〔bInitFlag296(推断)〕
  *((uint32_t *)this + 75) = 0;  // this+300〔pAnim300〕
  *((uint32_t *)this + 76) = 0;  // this+304〔pLayer304(推断)〕
  *((uint32_t *)this + 78) = 0;  // this+78 【推断】公会标志字节 C
  *((uint32_t *)this + 79) = 0;
  *((uint32_t *)this + 80) = 0;  // this+80 关联角色对象
  *((uint32_t *)this + 82) = 0;
  *((uint32_t *)this + 83) = 0;  // this+332〔bReservedConn〕
  *((uint32_t *)this + 84) = 0;  // this+84 插值起点 X
  *((uint32_t *)this + 86) = 0;  // this+344〔nReservedDelay〕
  *((uint32_t *)this + 87) = 0;  // this+348〔pParamTbl348〕
  *((uint32_t *)this + 88) = 0;  // this+352〔uHitCtx352〕
  *((uint32_t *)this + 90) = 0;
  *((uint32_t *)this + 91) = 0;  // this+364〔pAnimNameStr(推断)〕
  *((uint32_t *)this + 92) = 0;  // this+368〔nBindPos368〕
  *((uint32_t *)this + 97) = 0;  // this+388〔fAtkCtxVal(推断)〕
  *((uint32_t *)this + 98) = 0;
  *((uint32_t *)this + 99) = 0;  // this+396〔uReflectCtx(推断)〕
  *((uint32_t *)this + 100) = 0;  // this+100 插值终点 Y
  sub_41BFE0((void **)this + 100, szPassword);  // 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 102) = 0;  // this+408〔uAtkLimb0〕
  *((uint32_t *)this + 103) = 0;  // this+412〔uAtkLimb1〕
  *((uint32_t *)this + 104) = 0;  // this+104 插值终点 Z
  *((uint32_t *)this + 106) = 0;  // this+424〔f_AtkRateX10〕
  *((uint32_t *)this + 107) = 0;
  *((uint32_t *)this + 108) = 0;  // this+108 第 1 组·宿主属性 +886 增量
  *((uint32_t *)this + 110) = 0;
  *((uint32_t *)this + 111) = 0;
  *((uint32_t *)this + 112) = 0;  // this+448〔uAtkStage448(推断)〕
  *((uint32_t *)this + 116) = 0;  // this+116 观察者 vector 尾针
  *((uint32_t *)this + 117) = 0;
  *((uint32_t *)this + 118) = 0;
  sub_481EA0((int)this);  // CNRDSkill 主体字段组复位（+16..+472）
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x482450 sub_482450 —— 技能对象析构（与 ·0x482240 构造对偶）
// 44 字节列表 ·sub_480F70、14 字节列表 ·sub_480960 与 eh vector destructor iterator、clong 字段 ·sub_41A580、字符串缓冲 ·sub_41B010、+464 直接 j__free。
// ------------------------------------------------------------
void /*thiscall*/ sub_482450(int this)  // 实现：技能对象析构（与 ·0x482240 构造对偶）
{
  void *fld_1D0; // eax
  int fld_1A8; // eax

  fld_1D0 = *(void **)(this + 464);  // this+464 仅见复位
  if ( fld_1D0 != nullptr )  // 若 fld_1D0 有效（非空）
    j__free(fld_1D0);  // 调 堆释放
  *(uint32_t *)(this + 464) = 0;  // this+464 仅见复位
  *(uint32_t *)(this + 468) = 0;
  *(uint32_t *)(this + 472) = 0;
  sub_480F70((int *)(this + 436));  // 44 字节条目容器析构（+4/+8/+12 三字段）
  fld_1A8 = *(uint32_t *)(this + 424);  // this+424〔f_AtkRateX10〕
  if ( fld_1A8 != 0 )  // fld_1A8=this+424 f_AtkRateX10
  {
    sub_480960(fld_1A8, *(uint32_t *)(this + 428));  // 16 字节条目区间析构（内层对象走虚表首槽）
    j__free(*(void **)(this + 424));  // this+424〔f_AtkRateX10〕
  }
  *(uint32_t *)(this + 424) = 0;  // this+424〔f_AtkRateX10〕
  *(uint32_t *)(this + 428) = 0;
  *(uint32_t *)(this + 432) = 0;  // this+1728〔nDblClickSlotA(推断)〕
  sub_47F6E0(this + 404);  // 调 释放临时值
  sub_41B010((void **)(this + 400));  // 驻留句柄析构（引用计数减到 0 释放）
  sub_481E20((int *)(this + 384));  // 44 字节条目容器析构（与 ·0x481DF0 配套）
  sub_47F6E0(this + 356);  // 调 释放临时值
  sub_47F6E0(this + 340);  // this+340〔pSlotTbl340〕
  if ( *(uint32_t *)(this + 328) != 0 )  // this+1312〔pRowVec1312〕
    j__free(*(void **)(this + 328));  // this+1312〔pRowVec1312〕
  *(uint32_t *)(this + 328) = 0;  // this+1312〔pRowVec1312〕
  *(uint32_t *)(this + 332) = 0;  // this+332〔bReservedConn〕
  *(uint32_t *)(this + 336) = 0;
  sub_47F6E0(this + 308);  // 调 释放临时值
  sub_47F6E0(this + 292);  // 调 释放临时值
  sub_41A580((uint32_t *)(this + 278));  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  `eh vector destructor iterator'((void *)(this + 208), 0xEu, 5, sub_432D10);  // 调 转发 → ·sub_41A580 挂 crypt4byte::vftable 并递
  `eh vector destructor iterator'((void *)(this + 138), 0xEu, 5, sub_432D10);  // this+138〔field_008A〕
  sub_41A580((uint32_t *)(this + 124));  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_47F6E0(this + 104);  // 调 释放临时值
  sub_47F6E0(this + 88);  // 调 释放临时值
  sub_41A580((uint32_t *)(this + 74));  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)(this + 60));  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_47F6E0(this + 44);  // 调 释放临时值
  sub_41A580((uint32_t *)(this + 28));  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41B010((void **)(this + 24));  // 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 20));  // 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 16));  // 驻留句柄析构（引用计数减到 0 释放）
  sub_41A580((uint32_t *)this);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
}



// ------------------------------------------------------------
// 0x482650 sub_482650 —— 44 字节条目容器批量插入 insert(pos, n, value)
// 与 ·0x480FB0 同构但条目 44 字节（上限常量 97612893 为元素个数）；扩容后搬旧 ·sub_481C90、前移尾部 ·sub_481C70、填充新增 ·sub_481D40（单项版 ·sub_481E70）；结尾手工释放临时条目 +0 字段。
// ------------------------------------------------------------
void /*thiscall*/ sub_482650(int *this, int pArg2, unsigned int uArg3, int nArg4)  // 实现：44 字节条目容器批量插入 insert(pos, n, value)
{
  int pVecEnd_13; // ebx
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
  void *v19; // esi
  char *v20; // edi
  char *v21; // esi
  int fld_e12; // [esp-18h] [ebp-68h]
  int fld_e25; // [esp-Ch] [ebp-5Ch]
  unsigned int fld_e24; // [esp-8h] [ebp-58h]
  int v25; // [esp+0h] [ebp-50h] BYREF
  char v26[4]; // [esp+Ch] [ebp-44h] BYREF
  void *v27; // [esp+10h] [ebp-40h]
  char *v28; // [esp+14h] [ebp-3Ch]
  void *v29; // [esp+20h] [ebp-30h]
  int v30; // [esp+24h] [ebp-2Ch]
  int v31; // [esp+28h] [ebp-28h]
  void *Block; // [esp+38h] [ebp-18h]
  int *pThis; // [esp+3Ch] [ebp-14h]
  int *v34; // [esp+40h] [ebp-10h]
  int v35; // [esp+4Ch] [ebp-4h]
  int v36; // [esp+58h] [ebp+8h]
  int v37; // [esp+5Ch] [ebp+Ch]
  int v38; // [esp+60h] [ebp+10h]
  int fld_e232; // [esp+60h] [ebp+10h]

  v34 = &v25;
  pThis = this;
  sub_481BB0((int)v26, nArg4);  // 44 字节条目拷贝构造（24 字节列表 + clong + 尾标量）
  pVecEnd_13 = *(this + 1);  // this+4〔宿主对象〕
  fld_e3 = 0;
  v35 = 0;
  if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - pVecEnd_13) / 44;  // this+12〔nSkillRec12(推断)〕
  if ( uArg3 != 0 )
  {
    if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - pVecEnd_13) / 44;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
    if ( 97612893 - fld_e2 < uArg3 )  // fld_e2=this+8 nSkillRec8
      sub_47F990(this);  // 调 抛 std::length_error（vector<T> too long）——vector 超长的标准抛出点
    if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - pVecEnd_13) / 44;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e23 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
      fld_e232 = fld_e23;  // fld_e23=this+8 nSkillRec8
      if ( (fld_e23 - pArg2) / 44 >= uArg3 )  // fld_e23=this+8 nSkillRec8
      {
        v36 = fld_e23 - 44 * uArg3;  // fld_e23=this+8 nSkillRec8
        *(this + 2) = sub_481C90(v36, fld_e23, fld_e23);  // 44 字节条目区间拷贝构造到裸内存（每项 ·0x481BB0）
        sub_481C70(pArg2, v36, fld_e232);  // 转发 ·0x4813C0（thunk：44 字节条目反向前缀拷贝构造）
        sub_481C20(pArg2, pArg2 + 44 * uArg3, v26);  // 44 字节条目区间同值赋值（源 pArg3 反复）
      }
      else
      {
        sub_481C90(pArg2, fld_e23, pArg2 + 44 * uArg3);  // 44 字节条目区间拷贝构造到裸内存（每项 ·0x481BB0）
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 44;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
        LOBYTE(v35) = 3;
        sub_481E70(fld_e25, fld_e24, v26);  // 定长填充入口（转发 ·0x481D40，返回越过末尾的指针）
        fld_e26 = 44 * uArg3 + *(this + 2);  // this+8〔nSkillRec8〕
        *(this + 2) = fld_e26;  // this+8〔nSkillRec8(推断)〕
        v35 = 0;
        sub_481C20(pArg2, fld_e26 - 44 * uArg3, v26);  // 44 字节条目区间同值赋值（源 pArg3 反复）
      }
    }
    else
    {
      if ( 97612893 - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 nSkillRec12
        v10 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 nSkillRec12
      else
        v10 = 0;
      if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - pVecEnd_13) / 44;  // this+8〔nSkillRec8(推断)〕
      else
        fld_e27 = 0;  // fld_e27=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_e27 )  // fld_e27=this+8 nSkillRec8
        v10 = uArg3 + sub_527B90(this);  // 调 取 size
      v38 = 44 * v10;
      pMem = (char *)operator new(44 * v10);  // 分配 44 × v10 字节数组
      fld_e12 = *(this + 1);  // this+4〔宿主对象〕
      Block = pMem;
      LOBYTE(v35) = 1;
      v37 = sub_481C90(fld_e12, pArg2, (int)pMem);  // 结果 = 44 字节条目区间拷贝构造到裸内存（每项 ·0x481BB0）
      sub_481D40(v37, uArg3, (int)v26);  // 44 字节条目定长填充（nArg2 项，源 nArg3）
      sub_481C90(pArg2, *(this + 2), 44 * uArg3 + v37);  // 44 字节条目区间拷贝构造到裸内存（每项 ·0x481BB0）
      fld_e13 = *(this + 1);  // this+4〔宿主对象〕
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 44;  // this+8〔nSkillRec8(推断)〕
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);  // this+4〔宿主对象〕
      if ( fld_e14 != 0 )  // fld_e14=this+4 宿主对象
      {
        sub_481DF0(fld_e14, *(this + 2));  // 44 字节条目区间逐项析构（转 ·sub_437950）
        j__free((void *)*(this + 1));  // this+4〔宿主对象〕
      }
      *(this + 3) = (int)&pMem[v38];  // this+12〔nSkillRec12(推断)〕
      *(this + 2) = (int)&pMem[44 * v14];  // this+8〔nSkillRec8(推断)〕
      *(this + 1) = (int)pMem;  // this+4〔宿主对象〕
    }
  }
  if ( v29 != nullptr )  // 若 v29 有效（非空）
    j__free(v29);  // 调 堆释放
  v19 = v27;
  v29 = nullptr;
  v30 = 0;
  v31 = 0;
  if ( v27 != nullptr )  // 若 v27 有效（非空）
  {
    v20 = v28;
    if ( v27 != v28 )
    {
      v21 = (char *)v27 + 4;
      do
      {
        if ( *(uint32_t *)v21 != 0 )
          j__free(*(void **)v21);  // 调 堆释放
        *(uint32_t *)v21 = 0;  // *v21 = 0
        *((uint32_t *)v21 + 1) = 0;
        *((uint32_t *)v21 + 2) = 0;
        v21 += 24;
      }
      while ( v21 - 4 != v20 );
      v19 = v27;
    }
    j__free(v19);  // 调 堆释放
  }
}


// ------------------------------------------------------------
// 0x482990 sub_482990 —— 44 字节条目指定位置单元素插入（返回元素指针）
// 与 ·0x480880 同构：先记下标（差值 /44）再由 ·sub_482650 插入 1 项，回传 this+4 加 44*下标。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_482990(int *this, uint32_t *uArg2, int nArg3, int nArg4)  // 44 字节条目指定位置单元素插入（返回元素指针）
{
  int pVecEnd_5; // esi
  int v6; // esi

  pVecEnd_5 = *(this + 1);  // this+4〔宿主对象〕
  if ( pVecEnd_5 != 0 && (*(this + 2) - pVecEnd_5) / 44 != 0 )  // this+8〔nSkillRec8(推断)〕
    v6 = (nArg3 - pVecEnd_5) / 44;  // pVecEnd_5=this+4 宿主对象
  else
    v6 = 0;
  sub_482650(this, nArg3, 1u, nArg4);  // 44 字节条目容器批量插入 insert(pos, n, value)
  *uArg2 = *(this + 1) + 44 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x482A00 sub_482A00 —— 44 字节条目尾插（容量不足回落 ·0x482990）
// 空间足够时在 this+8 处经 ·sub_481D40 构造 1 项并前移终点 44 字节。
// ------------------------------------------------------------
void /*thiscall*/ sub_482A00(int *this, int nArg2)  // 实现：44 字节条目尾插（容量不足回落 ·0x482990）
{
  int pVecEnd_6; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi

  pVecEnd_6 = *(this + 1);  // this+4〔宿主对象〕
  if ( pVecEnd_6 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - pVecEnd_6) / 44;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( pVecEnd_6 != 0 && fld_e2 < (*(this + 3) - pVecEnd_6) / 44 )  // this+12〔nSkillRec12(推断)〕
  {
    fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
    sub_481D40(fld_e22, 1, nArg2);  // 44 字节条目定长填充（nArg2 项，源 nArg3）
    *(this + 2) = fld_e22 + 44;  // this+8〔nSkillRec8(推断)〕
  }
  else
  {
    sub_482990(this, &nArg2, *(this + 2), nArg2);  // 44 字节条目指定位置单元素插入（返回元素指针）
  }
}



// ============================================================
// §C 0x482A90-0x483C60  ★技能创建主流程（SKILL CREATE FAIL）
// ============================================================
// ------------------------------------------------------------
// 0x482A90 sub_482A90 —— ★技能创建主流程
//   sub_481720 建临时技能树节点 → sub_502F00（0x4F 区技能定义解析器）解析技能文件 →
//   逐槽装配（sub_41A590/sub_41B0D0 容器搬运）；失败 SKILL CREATE FAIL! FILENAME[%s]。
// ------------------------------------------------------------
int /*thiscall*/ sub_482A90(uint32_t *this, const char *ArgList, int nArg3)  // 实现：技能创建主流程
{
  uint32_t *pThis; // ebx
  unsigned int v4; // edi
  int v5; // edx
  unsigned int v6; // esi
  int v7; // edx
  unsigned int v8; // esi
  int v9; // ebx
  unsigned int v10; // esi
  int v11; // ebx
  char *pThis22; // esi
  int v13; // edx
  unsigned int v14; // ecx
  int v15; // edx
  int v16; // ebx
  unsigned int v17; // esi
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int i; // esi
  int v22; // eax
  int v23; // ebx
  int v24; // edx
  int j; // esi
  int v26; // eax
  int v27; // ebx
  int v28; // edx
  int k; // esi
  int v30; // eax
  int v31; // ebx
  int v32; // edx
  int v33; // edi
  char *v34; // ebx
  unsigned int v35; // esi
  int v36; // edi
  char *pThis23; // edi
  int v38; // esi
  uint32_t *v39; // edi
  int v40; // eax
  char *pThis24; // edi
  int v42; // eax
  int v43; // esi
  char v44; // bl
  uint32_t *v45; // eax
  uint32_t *v46; // edx
  uint32_t *v47; // ecx
  bool v48; // zf
  uint32_t *v49; // ecx
  bool v50; // dl
  bool v51; // zf
  int v52; // esi
  uint32_t *v53; // eax
  uint32_t *v54; // edx
  uint32_t *v55; // ecx
  bool v56; // zf
  uint32_t *v57; // ecx
  bool v58; // dl
  bool v59; // zf
  unsigned int v60; // edx
  int v61; // eax
  unsigned int v62; // edx
  int v63; // eax
  int v64; // edi
  unsigned int v65; // esi
  int v66; // edi
  char *v67; // ecx
  int v68; // edx
  char *pThis25; // esi
  int v70; // edx
  unsigned int v71; // eax
  unsigned int v72; // ecx
  int v73; // esi
  int v74; // eax
  int v75; // ebx
  int v76; // edx
  char *v77; // ecx
  unsigned int v78; // ebx
  unsigned int v79; // esi
  int v80; // edi
  int v81; // ecx
  int v82; // edx
  int v83; // edi
  int v84; // esi
  int v85; // edx
  char v86; // al
  int v87; // edx
  int v88; // eax
  float v90; // [esp+0h] [ebp-194h] BYREF
  float v91; // [esp+4h] [ebp-190h]
  int v92; // [esp+8h] [ebp-18Ch]
  int v93; // [esp+Ch] [ebp-188h]
  int v94; // [esp+1Ch] [ebp-178h] BYREF
  char v95[4]; // [esp+20h] [ebp-174h] BYREF
  char v96[4]; // [esp+24h] [ebp-170h] BYREF
  char v97[4]; // [esp+28h] [ebp-16Ch] BYREF
  int v98; // [esp+2Ch] [ebp-168h]
  int v99; // [esp+34h] [ebp-160h]
  int v100; // [esp+38h] [ebp-15Ch]
  int v101; // [esp+40h] [ebp-154h]
  int v102; // [esp+44h] [ebp-150h]
  int v103; // [esp+4Ch] [ebp-148h]
  int v104; // [esp+50h] [ebp-144h]
  int v105; // [esp+5Ch] [ebp-138h]
  int v106; // [esp+60h] [ebp-134h]
  int v107; // [esp+68h] [ebp-12Ch]
  int v108; // [esp+6Ch] [ebp-128h]
  float v109[14]; // [esp+70h] [ebp-124h]
  char v110[16]; // [esp+A8h] [ebp-ECh] BYREF
  int v111; // [esp+B8h] [ebp-DCh]
  int v112; // [esp+BCh] [ebp-D8h]
  int v113; // [esp+C4h] [ebp-D0h]
  int v114; // [esp+C8h] [ebp-CCh]
  char v115; // [esp+D0h] [ebp-C4h]
  uint32_t v116[4]; // [esp+D4h] [ebp-C0h] BYREF
  char v117[4]; // [esp+E4h] [ebp-B0h] BYREF
  int v118; // [esp+E8h] [ebp-ACh]
  int v119; // [esp+ECh] [ebp-A8h]
  char v120[8]; // [esp+110h] [ebp-84h] BYREF
  int v121; // [esp+118h] [ebp-7Ch]
  int v122; // [esp+11Ch] [ebp-78h]
  char v123[4]; // [esp+124h] [ebp-70h] BYREF
  int v124; // [esp+128h] [ebp-6Ch]
  int v125; // [esp+12Ch] [ebp-68h]
  char v126[16]; // [esp+134h] [ebp-60h] BYREF
  int v127; // [esp+144h] [ebp-50h]
  int v128; // [esp+148h] [ebp-4Ch]
  uint8_t v129[20]; // [esp+14Ch] [ebp-48h] BYREF
  int v130; // [esp+160h] [ebp-34h]
  int v131; // [esp+164h] [ebp-30h]
  int v132; // [esp+168h] [ebp-2Ch]
  int n; // [esp+16Ch] [ebp-28h]
  float *v134; // [esp+170h] [ebp-24h]
  uint32_t v135[3]; // [esp+176h] [ebp-1Eh] BYREF
  char *pThis2; // [esp+184h] [ebp-10h]
  int v137; // [esp+190h] [ebp-4h]
  int ArgLista; // [esp+19Ch] [ebp+8h]
  const char *ArgListb; // [esp+19Ch] [ebp+8h]
  char *ArgListc; // [esp+19Ch] [ebp+8h]
  char *ArgListd; // [esp+19Ch] [ebp+8h]
  unsigned int ArgListe; // [esp+19Ch] [ebp+8h]
  int v143; // [esp+1A0h] [ebp+Ch]
  int v144; // [esp+1A0h] [ebp+Ch]
  int v145; // [esp+1A0h] [ebp+Ch]
  int v146; // [esp+1A0h] [ebp+Ch]
  int v147; // [esp+1A0h] [ebp+Ch]
  int v148; // [esp+1A0h] [ebp+Ch]
  int v149; // [esp+1A0h] [ebp+Ch]
  int m; // [esp+1A0h] [ebp+Ch]

  pThis = this;
  pThis2 = (char *)this;
  sub_481720((int)&v94);  // 技能树节点复位（+200..292 字段组：冷却/等级/树位）
  v137 = 0;
  if ( sub_502F00((int)&v94, ArgList, nArg3) == 0 )  // 玩家技能定义解析器（.skl 文件；研究 20 §13 定位为 解析器，
  {
    off_77F3FC("SKILL CREATE FAIL! FILENAME[%s]", ArgList);  // 字符串 “SKILL CREATE FAIL! FILENAME[%s]”
    goto LABEL_139;
  }
  sub_41A590((unsigned int)(pThis + 1), v94, v94);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41B0D0(v95);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(v96);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(v97);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  v4 = (unsigned int)(pThis + 8);  // pThis+8〔nSkillRec8(推断)〕
  sub_41A590((unsigned int)(pThis + 8), v5, v98);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  if ( v99 != 0 )
  {
    ArgLista = (v100 - v99) >> 2;
    if ( ArgLista != 0 )
    {
      sub_41A630((unsigned int)&v90);  // 调 防篡改字段读校验（crypt 逆运算链）
      sub_4807B0(ArgLista, (char)&clong::`vftable', LODWORD(v91), v92, v93);  // 14 字节元素容器 resize(n, value)（与 ·0x480FB0 同族短版）
      v6 = 0;
      ArgListb = nullptr;
      while ( v99 != 0 && (v100 - v99) >> 2 > v6 )  // 当 v99 != 0 && (v100 - v99) >> 2 > v6 循环
      {
        if ( v3[13] == 0 || (v3[14] - v3[13]) / 14 <= v6 )
          sub_47F920(v3 + 12);  // 调 抛 std::out_of_range（invalid vector<T> subscript）——vector 越界的标准抛出…
        sub_41A590((unsigned int)&ArgListb[v3[13]], *(uint32_t *)(v99 + 4 * v6), *(uint32_t *)(v99 + 4 * v6));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        ++v6;
        ArgListb += 14;  // ArgListb 前进 14
      }
    }
  }
  sub_41A590((unsigned int)(v3 + 16), v101, v101);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)v3 + 78, v7, v102);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  if ( v103 != 0 )
  {
    v143 = (v104 - v103) >> 2;
    if ( v143 != 0 )
    {
      sub_41A630((unsigned int)&v90);  // 调 防篡改字段读校验（crypt 逆运算链）
      ArgListc = (char *)(v3 + 23);
      sub_4807B0(v143, (char)&clong::`vftable', LODWORD(v91), v92, v93);  // 14 字节元素容器 resize(n, value)（与 ·0x480FB0 同族短版）
      v8 = 0;
      v144 = 0;
      while ( v103 != 0 && (v104 - v103) >> 2 > v8 )
      {
        v9 = *((uint32_t *)ArgListc + 1);
        if ( v9 == 0 || (*((uint32_t *)ArgListc + 2) - v9) / 14 <= v8 )
          sub_47F920(ArgListc);  // 调 抛 std::out_of_range（invalid vector<T> subscript）——vector 越界的标准抛出…
        sub_41A590(v9 + v144, v103, *(uint32_t *)(v103 + 4 * v8));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        pThis = pThis2;
        ++v8;
        v144 += 14;
      }
    }
  }
  if ( v105 != 0 )
  {
    v145 = (v106 - v105) >> 2;
    if ( v145 != 0 )
    {
      sub_41A630((unsigned int)&v90);  // 调 防篡改字段读校验（crypt 逆运算链）
      ArgListd = (char *)(pThis + 27);
      sub_4807B0(v145, (char)&clong::`vftable', LODWORD(v91), v92, v93);  // 14 字节元素容器 resize(n, value)（与 ·0x480FB0 同族短版）
      v10 = 0;
      v146 = 0;
      while ( v105 != 0 && (v106 - v105) >> 2 > v10 )
      {
        v11 = *((uint32_t *)ArgListd + 1);
        if ( v11 == 0 || (*((uint32_t *)ArgListd + 2) - v11) / 14 <= v10 )
          sub_47F920(ArgListd);  // 调 抛 std::out_of_range（invalid vector<T> subscript）——vector 越界的标准抛出…
        sub_41A590(v11 + v146, v105, *(uint32_t *)(v105 + 4 * v10++));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        v146 += 14;
      }
    }
  }
  v12 = v136;
  v13 = v107;
  v93 = v108;
  v14 = (unsigned int)(v136 + 128);
  *((uint32_t *)v136 + 31) = v107;
  sub_41A590(v14, v13, v93);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v16 = 0;
  v17 = (unsigned int)(v12 + 212);
  do
  {
    sub_41A590(v17 - 70, v15, LODWORD(v109[v16]));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(v17, v18, LODWORD(v109[v16 + 5]));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v147 = sub_41A5E0(v17);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    if ( v147 > sub_41A5E0((unsigned int)(v136 + 282)) )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v19 = sub_41A5E0(v17);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590((unsigned int)(v136 + 282), v20, v19);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
    ++v16;
    v17 += 14;
  }
  while ( v16 < 5 );
  for ( i = 1; i <= sub_41A5E0(v4); ++i )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v22 = sub_41A5E0(v4);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v23 = (uint64_t)sub_4049C0(v109[10], v109[11], i - 1, v22 - 1);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    sub_41A630((unsigned int)v135);  // 调 防篡改字段读校验（crypt 逆运算链）
    LOBYTE(v137) = 1;
    v135[0] = &clong::`vftable';  // 构造装配 vftable：clong
    sub_41A590((unsigned int)v135, v24, v23);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    LOBYTE(v137) = 2;
    sub_480B10(v135);  // 14 字节容器尾插（容量不足回落 ·0x480880 插入）
    LOBYTE(v137) = 0;
    sub_41A580(v135);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  }
  for ( j = 1; j <= sub_41A5E0(v4); ++j )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v26 = sub_41A5E0(v4);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v91 = (float)SLODWORD(v109[13]);
    v90 = (float)SLODWORD(v109[12]);
    v27 = (uint64_t)sub_4049C0(v90, v91, j - 1, v26 - 1);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    sub_41A630((unsigned int)v135);  // 调 防篡改字段读校验（crypt 逆运算链）
    LOBYTE(v137) = 3;
    v135[0] = &clong::`vftable';  // 构造装配 vftable：clong
    sub_41A590((unsigned int)v135, v28, v27);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    LOBYTE(v137) = 4;
    sub_480B10(v135);  // 14 字节容器尾插（容量不足回落 ·0x480880 插入）
    LOBYTE(v137) = 0;
    sub_41A580(v135);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  }
  sub_4804A0(v110);  // 12 字节三元组容器区间赋值（三分支容量策略）
  for ( k = 1; k <= sub_41A5E0(v4); ++k )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v30 = sub_41A5E0(v4);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v91 = (float)v112;
    v90 = (float)v111;
    v31 = (uint64_t)sub_4049C0(v90, v91, k - 1, v30 - 1);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    sub_41A630((unsigned int)v135);  // 调 防篡改字段读校验（crypt 逆运算链）
    LOBYTE(v137) = 5;
    v135[0] = &clong::`vftable';  // 构造装配 vftable：clong
    sub_41A590((unsigned int)v135, v32, v31);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    LOBYTE(v137) = 6;
    sub_480B10(v135);  // 14 字节容器尾插（容量不足回落 ·0x480880 插入）
    LOBYTE(v137) = 0;
    sub_41A580(v135);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  }
  if ( v113 != 0 )
  {
    v33 = (v114 - v113) >> 2;
    if ( v33 != 0 )
    {
      sub_41A630((unsigned int)&v90);  // 调 防篡改字段读校验（crypt 逆运算链）
      v34 = pThis2 + 360;
      sub_4807B0(v33, (char)&clong::`vftable', LODWORD(v91), v92, v93);  // 14 字节元素容器 resize(n, value)（与 ·0x480FB0 同族短版）
      v35 = 0;
      v148 = 0;
      while ( v113 != 0 && (v114 - v113) >> 2 > v35 )
      {
        v36 = *((uint32_t *)v34 + 1);
        if ( v36 == 0 || (*((uint32_t *)v34 + 2) - v36) / 14 <= v35 )
        {
LABEL_105:
          v67 = v34;
LABEL_106:
          sub_47F920(v67);  // 调 抛 std::out_of_range（invalid vector<T> subscript）——vector 越界的标准抛出…
        }
        sub_41A590(v36 + v148, v113, *(uint32_t *)(v113 + 4 * v35++));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        v148 += 14;
      }
    }
  }
  v37 = v136;
  v136[376] = v115;
  v38 = 0;
  v39 = v37 + 380;
  do
  {
    v40 = sub_41ACF0(&v116[v38]);  // 结果 = 驻留串句柄 → 字符串指针
    v93 = v116[v38 + 2];
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v40);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    *v39 = sub_418DD0(v93);  // 调 资源句柄 (101)
    ++v38;
    ++v39;
  }
  while ( v38 < 2 );
  if ( v118 != 0 && (v119 - v118) / 24 != 0 )
  {
    v41 = v136;
    sub_482A00(v117);  // 44 字节条目尾插（容量不足回落 ·0x482990）
    v42 = *((uint32_t *)v41 + 98);
    v43 = *(uint32_t *)(v42 + 4);
    v44 = 0;
    if ( v43 != *(uint32_t *)(v42 + 8) )
    {
      do
      {
        if ( v44 != 0 )
          goto LABEL_79;
        v45 = *(uint32_t **)(v43 + 4);
        v46 = *(uint32_t **)(v43 + 8);
        v47 = v45;
        v48 = v45 == v46;
        if ( v45 != v46 )
        {
          do
          {
            if ( *v47 == 2 )
              break;
            ++v47;
          }
          while ( v47 != v46 );
          v48 = v47 == v46;
        }
        v49 = *(uint32_t **)(v43 + 8);
        v50 = !v48;
        v51 = v45 == v49;
        if ( v45 != v49 )
        {
          do
          {
            if ( *v45 == 3 )
              break;
            ++v45;
          }
          while ( v45 != v49 );
          v51 = v45 == v49;
        }
        if ( v50 )
        {
          if ( v51 )
          {
LABEL_78:
            v44 = 1;
LABEL_79:
            v60 = 0;
            while ( 1 )
            {
              v61 = *(uint32_t *)(v43 + 4);
              if ( v61 == 0 || v60 >= (*(uint32_t *)(v43 + 8) - v61) >> 2 )
                break;
              if ( *(uint32_t *)(v61 + 4 * v60) == 2 )
              {
                *(uint32_t *)(v61 + 4 * v60++) = 3;
              }
              else
              {
                if ( *(uint32_t *)(v61 + 4 * v60) == 3 )
                  *(uint32_t *)(v61 + 4 * v60) = 2;
                ++v60;
              }
            }
          }
        }
        else if ( !v51 )
        {
          goto LABEL_78;
        }
        v43 += 24;
      }
      while ( v43 != *(uint32_t *)(*((uint32_t *)v41 + 98) + 8) );
    }
    v52 = *((uint32_t *)v41 + 98);
    if ( v44 != 0 )
      goto LABEL_88;
    v53 = *(uint32_t **)(v52 + 20);
    v54 = *(uint32_t **)(v52 + 24);
    v55 = v53;
    v56 = v53 == v54;
    if ( v53 != v54 )
    {
      do
      {
        if ( *v55 == 2 )
          break;
        ++v55;
      }
      while ( v55 != v54 );
      v56 = v55 == v54;
    }
    v57 = *(uint32_t **)(v52 + 24);
    v58 = !v56;
    v59 = v53 == v57;
    if ( v53 != v57 )
    {
      do
      {
        if ( *v53 == 3 )
          break;
        ++v53;
      }
      while ( v53 != v57 );
      v59 = v53 == v57;
    }
    if ( v58 )
    {
      if ( v59 )
        goto LABEL_88;
    }
    else if ( !v59 )
    {
LABEL_88:
      v62 = 0;
      while ( 1 )
      {
        v63 = *(uint32_t *)(v52 + 20);
        if ( v63 == 0 || v62 >= (*(uint32_t *)(v52 + 24) - v63) >> 2 )
          break;
        if ( *(uint32_t *)(v63 + 4 * v62) == 2 )
        {
          *(uint32_t *)(v63 + 4 * v62++) = 3;
        }
        else
        {
          if ( *(uint32_t *)(v63 + 4 * v62) == 3 )
            *(uint32_t *)(v63 + 4 * v62) = 2;
          ++v62;
        }
      }
      sub_482650(*((uint32_t *)v41 + 98), 1, v117);  // 44 字节条目容器批量插入 insert(pos, n, value)
    }
  }
  sub_41B0D0(v120);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  if ( v121 != 0 )
  {
    v64 = (v122 - v121) >> 2;
    if ( v64 != 0 )
    {
      sub_41A630((unsigned int)&v90);  // 调 防篡改字段读校验（crypt 逆运算链）
      v34 = v136 + 408;
      sub_4807B0(v64, (char)&clong::`vftable', LODWORD(v91), v92, v93);  // 14 字节元素容器 resize(n, value)（与 ·0x480FB0 同族短版）
      v65 = 0;
      v149 = 0;
      while ( v121 != 0 && (v122 - v121) >> 2 > v65 )
      {
        v66 = *((uint32_t *)v34 + 1);
        if ( v66 == 0 || (*((uint32_t *)v34 + 2) - v66) / 14 <= v65 )
          goto LABEL_105;
        sub_41A590(v66 + v149, v149, *(uint32_t *)(v121 + 4 * v65++));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        v149 += 14;
      }
    }
  }
  if ( v124 != 0 && (v68 = (v125 - v124) >> 4) != 0 )
  {
    pThis25 = pThis2;
    sub_481260(v68, SLOBYTE(v90), 0, 0, 0);  // 16 字节条目容器 resize(n, value)
    v70 = v124;
    v71 = 0;
    ArgListe = 0;
    for ( m = 0; v70 != 0; m += 16 )
    {
      v72 = (v125 - v70) >> 4;
      if ( v72 <= v71 )
        break;
      v73 = *(uint32_t *)(v70 + m + 4);
      if ( v73 != 0 && (*(uint32_t *)(v70 + m + 8) - v73) >> 2 != 0 )
      {
        if ( v72 > ArgListe )
        {
          v74 = *(uint32_t *)(v70 + m + 4);
          if ( v74 != 0 )
            v75 = (*(uint32_t *)(v70 + m + 8) - v74) >> 2;
          else
            v75 = 0;
          v76 = *((uint32_t *)pThis2 + 107);
          v77 = pThis2 + 424;  // this+424 【推断】攻击倍率 ×10 换算
          if ( v76 == 0 || (*((uint32_t *)pThis2 + 108) - v76) >> 4 <= ArgListe )  // this+108 第 1 组·宿主属性 +886 增量
LABEL_136:
            sub_47F920(v77);  // 调 抛 std::out_of_range（invalid vector<T> subscript）——vector 越界的标准抛出…
          v134 = &v90;
          sub_41A630((unsigned int)&v90);  // 调 防篡改字段读校验（crypt 逆运算链）
          sub_4807B0(v75, (char)&clong::`vftable', LODWORD(v91), v92, v93);  // 14 字节元素容器 resize(n, value)（与 ·0x480FB0 同族短版）
          v78 = 0;
          for ( n = 0; ; n = v84 + 14 )
          {
            v70 = v124;
            if ( v124 == 0 )
              break;
            v79 = (v125 - v124) >> 4;
            if ( v79 <= ArgListe )
              break;
            v80 = *(uint32_t *)(m + v124 + 4);
            v81 = v124 + m;
            if ( v80 == 0 || v78 >= (*(uint32_t *)(v81 + 8) - v80) >> 2 )
              goto LABEL_133;
            if ( v79 <= ArgListe )
              break;
            v134 = *(float **)(v81 + 4);
            if ( v134 == nullptr || (*(uint32_t *)(v81 + 8) - (int)v134) >> 2 <= v78 )
              sub_454B50();  // vector 越界抛异常
            v82 = *((uint32_t *)pThis2 + 107);
            v77 = pThis2 + 424;  // this+424 【推断】攻击倍率 ×10 换算
            if ( v82 == 0 || (*((uint32_t *)pThis2 + 108) - v82) >> 4 <= ArgListe )  // this+108 第 1 组·宿主属性 +886 增量
              goto LABEL_136;
            v83 = *(uint32_t *)(v82 + m + 4);
            v67 = (char *)(v82 + m);
            if ( v83 == 0 || (*((uint32_t *)v67 + 2) - v83) / 14 <= v78 )
              goto LABEL_106;
            v84 = n;
            sub_41A590(v83 + n, LODWORD(v134[v78]), LODWORD(v134[v78]));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
            ++v78;
          }
        }
        sub_47F920(v123);  // 调 抛 std::out_of_range（invalid vector<T> subscript）——vector 越界的标准抛出…
      }
LABEL_133:
      pThis25 = pThis2;
      v71 = ++ArgListe;
    }
  }
  else
  {
    pThis25 = pThis2;
  }
  sub_481A30(v126);  // 44 字节条目容器深拷贝赋值（三分支容量策略）
  v85 = v128;
  v86 = v129[16];
  *((uint32_t *)pThis25 + 114) = v127;
  *((uint32_t *)pThis25 + 121) = v130;
  *((uint32_t *)pThis25 + 115) = v85;
  v87 = v131;
  pThis25[480] = v86;
  v88 = v132;
  v93 = (int)v129;
  *((uint32_t *)pThis25 + 122) = v87;
  *((uint32_t *)pThis25 + 123) = v88;
  sub_4ED3F0((int)(pThis25 + 464), v93);  // int 向量拷贝赋值（全容量路径）
  v93 = 1500;
  v92 = 0;
  pThis25[601] = 0;
  pThis25[602] = 0;
  sub_698F90((int)(pThis25 + 588), v92, v93);  // 【clock_set_countdown(clk, duration=a2, star…】
LABEL_139:
  v137 = -1;
  return sub_481860(&v94);  // 技能树节点析构（+244..280 容器与引用清理）
}


// ------------------------------------------------------------
// 0x4835D0 sub_4835D0 —— 技能对象初始化包装（sub_482240 重置 → sub_482A90 创建）
// ------------------------------------------------------------
int /*thiscall*/ sub_4835D0(int this, const char *ArgList, int nArg3)  // 实现：技能对象初始化包装（sub_482240 重置 → sub_482A90 创建）
{
  *(uint32_t *)this = &CNRDSkill::`vftable';  // 构造装配 vftable：CNRDSkill
  sub_482240((char *)(this + 4));  // 技能对象构造（clong 虚表字段组 + 5×14 字节数组）
  `eh vector constructor iterator'((void *)(this + 496), 0xEu, 2, (void (/*thiscall*/ *)(void *))sub_401040, sub_432D10);  // clong 构造（·sub_41A630 随机源初始化 + 挂 clong::vftable）
  sub_41A630(this + 524);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)(this + 524) = &cfloat::`vftable';  // 构造装配 vftable：cfloat
  sub_41A630(this + 544);  // this+544〔nFaction〕
  *(uint32_t *)(this + 544) = &clong::`vftable';  // this+544〔nFaction〕
  sub_41A630(this + 558);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)(this + 558) = &clong::`vftable';  // 构造装配 vftable：clong
  sub_41A630(this + 572);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)(this + 572) = &clong::`vftable';  // 构造装配 vftable：clong
  *(uint8_t *)(this + 592) = 0;  // this+592〔位置采样时刻(副本)〕
  *(uint32_t *)(this + 588) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 596) = 0;
  *(uint8_t *)(this + 600) = 1;  // this+600〔命中列表边界〕
  *(uint8_t *)(this + 602) = 0;
  *(uint8_t *)(this + 601) = 0;
  *(uint32_t *)(this + 612) = 0;
  *(uint32_t *)(this + 608) = 0;  // this+608〔nAttackGate〕
  *(uint32_t *)(this + 604) = 0;
  sub_41A630(this + 616);  // this+616〔nReactionState〕
  *(uint32_t *)(this + 616) = &clong::`vftable';  // this+616〔nReactionState〕
  sub_41A630(this + 630);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)(this + 630) = &clong::`vftable';  // 构造装配 vftable：clong
  sub_47DC00((uint32_t *)this);  // 调 （this+124 元素起）；再依次写入 float 1.0f（1065353216=IEEE 位型）与 5 个零值字段
  sub_482A90((char *)this, ArgList, nArg3);  // 技能创建主流程
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x483720 sub_483720 —— CNRDSkill 两 clong 字段复位（+616/+630）
// 两处均转发 ·sub_41A590（clong 赋值/清零）；第二处实参取自残留寄存器 v3【推断：与第一处同义】。
// ------------------------------------------------------------
int /*fastcall*/ sub_483720(int pArg1, int nArg2)  // 实现：CNRDSkill 两 clong 字段复位（+616/+630）
{
  int v3; // edx

  sub_41A590(pArg1 + 616, nArg2, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return sub_41A590(pArg1 + 630, v3, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x483740 sub_483740 —— 计时判定（+630 时间戳晚于全局时钟）
// ·sub_41A5E0 读 +630 保存值，与 ·0x699000 clock_now(unk_99FC80) 求差并判断是否仍大于 0（冷却未到期【推断】）。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_483740(void *this)  // 计时判定（+630 时间戳晚于全局时钟）
{
  int pThis_276; // esi

  pThis_276 = sub_41A5E0((unsigned int)this + 630);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return pThis_276 - sub_699000((int)&unk_99FC80) > 0;  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x483770 sub_483770 —— CNRDSkill 删除包装（scalar deleting destructor）
// 先 ·sub_4837A0 走完整析构，再按 pszArg2 位 0 决定是否 j__free。
// ------------------------------------------------------------
void */*thiscall*/ sub_483770(void *Block, char pszArg2)  // CNRDSkill 删除包装（scalar deleting destructor）
{
  sub_4837A0();  // CNRDSkill 析构主体
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4837A0 sub_4837A0 —— CNRDSkill 析构主体
// 对应 ·0x4835D0 构造：写回 CNRDSkill 与 nengine::IObject 虚表，·sub_41A580 释放 +616/+630/+572/+558/+544 等 clong 字段，eh vector destructor iterator 收 +496 处 2 个 14 字节元素，末尾 ·sub_482450 释放内嵌技能对象。
// ------------------------------------------------------------
void /*thiscall*/ sub_4837A0(uint32_t *this)  // 实现：CNRDSkill 析构主体
{
  *this = &CNRDSkill::`vftable';  // 构造装配 vftable：CNRDSkill
  sub_41A580((uint32_t *)((char *)this + 630));  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 154);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  *(this + 147) = &nengine::IObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  *((uint8_t *)this + 592) = 0;  // this+592〔位置采样时刻(副本)〕
  sub_41A580(this + 143);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 558));  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 136);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 131);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  `eh vector destructor iterator'(this + 124, 0xEu, 2, sub_432D10);  // 调 转发 → ·sub_41A580 挂 crypt4byte::vftable 并递
  sub_482450((int)(this + 1));  // 技能对象析构（与 ·0x482240 构造对偶）
}



// ------------------------------------------------------------
// 0x483870 sub_483870 —— 技能文件加载调度（sub_47FA50/4835D0；+44/+45 状态、音效/图像回退链）
// ------------------------------------------------------------
char sub_483870()  // 技能文件加载调度（sub_47FA50/4835D0；+44/+45 状态、音效/图像回退链
{
  unsigned int v0; // edi
  uint32_t *v1; // esi
  const char *i; // ebx
  void *pMem; // eax
  int v4; // edx
  unsigned int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // edi
  void (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int **v10; // ecx
  int *k; // eax
  int *j; // eax
  uint32_t *v13; // esi
  uint8_t *pMem2; // eax
  int v15; // edi
  int dword_79C0B02; // ebx
  uint8_t *pMem3; // eax
  int v18; // edi
  uint8_t *pMem4; // eax
  int v20; // edi
  int dword_79C0B03; // ebx
  uint8_t *pMem5; // eax
  int v23; // edi
  int dword_79C0B04; // ebx
  void *Block; // [esp+Ch] [ebp-1Ch]
  void *Blocka; // [esp+Ch] [ebp-1Ch]
  void *v28; // [esp+10h] [ebp-18h]
  const char ***v29; // [esp+14h] [ebp-14h]
  int ArgList; // [esp+18h] [ebp-10h]

  v0 = 0;
  ArgList = 0;
  v29 = (const char ***)&unk_9B72D8;
  v1 = &unk_99FC30;
  do
  {
    sub_47FA50(50);  // 调 重建并搬旧数据（0x3FFFFFFF=4 字节/元素的 32 位上限）；返回新 capEnd
    for ( i = **v29; i != (const char *)*v29; v0 = 0 )
    {
      pMem = operator new(0x284u);  // 堆分配 644 字节对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
      {
        if ( *((uint32_t *)i + 10) < 0x10u )
          v28 = (void *)sub_4835D0((int)pMem, i + 20, ArgList);  // 结果 = 技能对象初始化包装（sub_482240 重置 → sub_482A90 创建）
        else
          v28 = (void *)sub_4835D0((int)pMem, *((const char **)i + 5), ArgList);  // 结果 = 技能对象初始化包装（sub_482240 重置 → sub_482A90 创建）
      }
      else
      {
        v28 = nullptr;
      }
      v4 = v1[1];
      v5 = *((uint32_t *)i + 3);
      Block = (void *)v5;
      if ( v4 == 0 || v5 >= (v1[2] - v4) >> 2 )
      {
        v6 = v1[1];
        if ( v6 != 0 )
          v0 = (v1[2] - v6) >> 2;
        sub_47FC70(v5 + 1, 0);  // 调 >uArg2 时截断 end（memcpy 0 字节的平移写法）
        while ( 1 )
        {
          v7 = v1[1];
          if ( v7 == 0 || v0 >= (v1[2] - v7) >> 2 )
            break;
          *(uint32_t *)(v7 + 4 * v0++) = 0;
        }
        v5 = (unsigned int)Block;
      }
      v8 = 4 * v5;
      if ( *(uint32_t *)(4 * v5 + v1[1]) != 0 )
      {
        off_77F3FC("SKILL LIST ERROR! JOB : %d, INDEX : %d", ArgList, v5);  // 字符串 “SKILL LIST ERROR! JOB : %d, INDEX : %d”
        v9 = *(void (/*thiscall*/ ****)(uint32_t, int))(v8 + v1[1]);
        if ( v9 != nullptr )  // 若 v9 有效（非空）
          (**v9)(v9, 1);  // 调 v9 的虚函数（vt+0）
      }
      *(uint32_t *)(v8 + v1[1]) = v28;
      if ( i[45] == 0 )
      {
        v10 = *((int ***)i + 2);
        if ( *((uint8_t *)v10 + 45) != 0 )
        {
          for ( j = *((int **)i + 1); *((uint8_t *)j + 45) == 0; j = (int *)j[1] )
          {
            if ( i != (const char *)j[2] )
              break;
            i = (const char *)j;
          }
          i = (const char *)j;
        }
        else
        {
          for ( k = *v10; *((uint8_t *)k + 45) == 0; k = (int *)*k )
            v10 = (int **)k;
          i = (const char *)v10;
        }
      }
    }
    v1 += 4;
    ++ArgList;  // ArgList 自增
    v29 += 3;
  }
  while ( (int)v1 < (int)&dword_99FC70 );
  v13 = *(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);  // nengine::CNSlider 全局实例
  dword_99FC08 = sub_418DD0(v13, 0x53u);  // 调 资源句柄 (101)
  dword_99FC0C = sub_418DD0(v13, 0x3Cu);  // 调 资源句柄 (101)
  dword_99FC10 = sub_418DD0(v13, 0x47u);  // 调 资源句柄 (101)
  dword_99FC14 = sub_418DD0(v13, 0x6Bu);  // 调 资源句柄 (101)
  pMem2 = operator new(0x2Cu);  // 堆分配 44 字节对象
  v15 = (int)pMem2;
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
  {
    dword_79C0B02 = dword_79C0B0;  // 默认字体/绘制资源
    pMem2[4] = 0;
    *(uint32_t *)pMem2 = &nengine::CNNumberSet::`vftable';  // 写 vftable 指针（对象重定位/复位）
    sub_699E20(v14);  // 调 本体初始化 + sub_699E40(a2..a5)
    sub_699E40(v16, v13, 83, 3);
  }
  else
  {
    v15 = 0;
  }
  dword_99FC18 = v15;
  v17 = operator new(0x2Cu);  // 堆分配 44 字节对象
  v18 = (int)v17;
  if ( v17 != nullptr )  // 若 v17 有效（非空）
  {
    Blocka = (void *)dword_79C0B0;  // 默认字体/绘制资源
    v17[4] = 0;
    *(uint32_t *)v17 = &nengine::CNNumberSet::`vftable';  // 写 vftable 指针（对象重定位/复位）
    sub_699E20(pMem3);  // 调 本体初始化 + sub_699E40(a2..a5)
    sub_699E40(Blocka, v13, 60, 3);
  }
  else
  {
    v18 = 0;
  }
  dword_99FC1C = v18;
  pMem4 = operator new(0x2Cu);  // 堆分配 44 字节对象
  v20 = (int)pMem4;
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
  {
    dword_79C0B03 = dword_79C0B0;  // 默认字体/绘制资源
    pMem4[4] = 0;
    *(uint32_t *)pMem4 = &nengine::CNNumberSet::`vftable';  // 写 vftable 指针（对象重定位/复位）
    sub_699E20(v19);  // 调 本体初始化 + sub_699E40(a2..a5)
    sub_699E40(v21, v13, 71, 3);
  }
  else
  {
    v20 = 0;
  }
  dword_99FC20 = v20;
  v22 = operator new(0x2Cu);  // 堆分配 44 字节对象
  v23 = (int)v22;
  if ( v22 != nullptr )  // 若 v22 有效（非空）
  {
    v24 = dword_79C0B0;  // 默认字体/绘制资源
    v22[4] = 0;
    *(uint32_t *)v22 = &nengine::CNNumberSet::`vftable';  // 写 vftable 指针（对象重定位/复位）
    sub_699E20(pMem5);  // 调 本体初始化 + sub_699E40(a2..a5)
    sub_699E40(dword_79C0B04, v13, 107, 3);  // 默认字体/绘制资源
  }
  else
  {
    v23 = 0;
  }
  dword_99FC24 = v23;
  dword_99FC28 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 12), 0x9Cu);  // 调 资源句柄 (101)
  *(uint32_t *)(dword_99FC18 + 36) = 2;
  *(uint32_t *)(dword_99FC18 + 40) = -1;
  *(uint32_t *)(dword_99FC1C + 36) = 2;
  *(uint32_t *)(dword_99FC1C + 40) = -1;
  *(uint32_t *)(dword_99FC20 + 36) = 2;
  *(uint32_t *)(dword_99FC20 + 40) = -1;
  *(uint32_t *)(dword_99FC24 + 36) = 2;
  *(uint32_t *)(dword_99FC24 + 40) = -1;
  byte_99FC8D = 0;
  byte_99FC8E = 0;
  sub_699070(1);  // 【clock_bind_domain(clk, newDomainId)】
  return sub_698F90((int)&unk_99FC80, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}


// ============================================================
// §D 0x483C60-0x484470  包分发辅助（读包三元组 sub_423200/423290/423380）
// ============================================================
// ------------------------------------------------------------
// 0x483C60 sub_483C60 —— 技能槽指针数组构建（new count 个空指针 + 首次初始化全局状态）
// 首次调用时以 byte_99FCAA 为一次性标记，清 dword_99FC9C、dword_99FCA4、word_99FCA0、word_99FCA8；这两组 6 格字节数组被 ·0x483CF0 与 ·0x4842B0 使用。
// ------------------------------------------------------------
char /*thiscall*/ sub_483C60(uint32_t *this, int nArg2)  // 实现：技能槽指针数组构建（new count 个空指针 + 首次初始化全局状态）
{
  int i; // eax
  char result; // al

  *this = nArg2;
  *(this + 1) = operator new(4 * nArg2);  // this+4〔宿主对象〕
  for ( i = 0; i < nArg2; ++i )
    *(uint32_t *)(*(this + 1) + 4 * i) = 0;  // this+4〔宿主对象〕
  result = byte_99FCAA;  // byte_99FCAA＝为一次性标记
  if ( byte_99FCAA == 0 )
  {
    dword_99FC9C = 0;
    dword_99FCA4 = 0;
    word_99FCA0 = 0;
    word_99FCA8 = 0;
    byte_99FCAA = 1;  // byte_99FCAA＝为一次性标记
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x483CD0 sub_483CD0 —— 技能槽指针数组释放（第 1 字段缓冲 j_j__free 并置空）
// this+4 即 ·0x483C60 分配的指针数组；仅释放该缓冲，与本族 ·0x483DF0 不同，不逐个解除引用。
// ------------------------------------------------------------
void /*thiscall*/ sub_483CD0(void **this)  // 实现：技能槽指针数组释放（第 1 字段缓冲 j_j__free 并置空）
{
  if ( *(this + 1) != nullptr )  // this+4〔宿主对象〕
    j_j__free(*(this + 1));  // this+4〔宿主对象〕
  *(this + 1) = nullptr;  // this+4〔宿主对象〕
}



// ------------------------------------------------------------
// 0x483CF0 sub_483CF0 —— 技能槽可用性刷新（遍历 unk_77FCD8 表，仅首个可用项置 1）
// 每项取 ·sub_4BF250 结果并写入 dword_99FCA4，同时把首个可用项的 dword_99FC9C 置 1、其余置 0；表尾 byte_77FD08。
// ------------------------------------------------------------
int sub_483CF0()  // 技能槽可用性刷新（遍历 unk_77FCD8 表，仅首个可用项置 1）
{
  char v0; // bl
  int v1; // esi
  char *v2; // edi
  int result; // eax

  v0 = 0;
  v1 = 0;
  v2 = (char *)&unk_77FCD8;
  do
  {
    result = sub_4BF250(v2);  // 结果 = 槽查询（+64 表）
    if ( *((uint8_t *)&dword_99FCA4 + v1) != 0 || (uint8_t)result == 0 || v0 != 0 )
    {
      *((uint8_t *)&dword_99FC9C + v1) = 0;
    }
    else
    {
      *((uint8_t *)&dword_99FC9C + v1) = 1;
      v0 = 1;
    }
    *((uint8_t *)&dword_99FCA4 + v1) = result;
    v2 += 8;
    ++v1;
  }
  while ( (int)v2 < (int)byte_77FD08 );
  return result;
}



// ------------------------------------------------------------
// 0x483D50 sub_483D50 —— 技能槽绑定（替换索引 nArg2 处对象，旧对象解引用）
// 旧值非空先 ·sub_47ECE0 解除、新值非空由 ·sub_47E3E0 建立引用后写回 this+4 数组；下标越界返回 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_483D50(uint32_t *this, int nArg2, int nArg3)  // 实现：技能槽绑定（替换索引 nArg2 处对象，旧对象解引用）
{
  int fld_e1; // ecx

  if ( nArg2 >= *this )
    return 0;
  fld_e1 = *(uint32_t *)(*(this + 1) + 4 * nArg2);  // this+4〔宿主对象〕
  if ( fld_e1 != nArg3 )  // fld_e1=this+4 宿主对象
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      sub_47ECE0();  // 调 到 dword_8F85A8（收集/重挂列表）
    if ( nArg3 != 0 )
      sub_47E3E0(nArg3);  // 调 （条目清理/析构）
  }
  *(uint32_t *)(*(this + 1) + 4 * nArg2) = nArg3;  // this+4〔宿主对象〕
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x483DA0 sub_483DA0 —— 技能槽交换（交换 nArg2/nArg3 两槽，计数先减 1）
// 先对 this+8 计数减 1，再校验两下标并互换 this+4 数组两项；由 ·0x483E70 在 byte_77F280 置位时本地先行交换。
// ------------------------------------------------------------
char /*thiscall*/ sub_483DA0(int *this, int nArg2, int nArg3)  // 实现：技能槽交换（交换 nArg2/nArg3 两槽，计数先减 1）
{
  int fld_e2; // eax
  int fld_e1; // eax
  int v6; // edi

  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( fld_e2 <= 0 )  // fld_e2=this+8 nSkillRec8
    return 0;
  *(this + 2) = fld_e2 - 1;  // this+8〔nSkillRec8(推断)〕
  if ( nArg2 >= *this || nArg3 >= *this )
    return 0;
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  v6 = *(uint32_t *)(fld_e1 + 4 * nArg2);  // fld_e1=this+4 宿主对象
  *(uint32_t *)(fld_e1 + 4 * nArg2) = *(uint32_t *)(fld_e1 + 4 * nArg3);  // fld_e1=this+4 宿主对象
  *(uint32_t *)(*(this + 1) + 4 * nArg3) = v6;  // this+4〔宿主对象〕
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x483DF0 sub_483DF0 —— 遍历技能槽对非空项调用 ·sub_47E440
// pszArg2 为透传参数（等级或标记【推断】），对 this+4 数组每个非空项应用一次。
// ------------------------------------------------------------
int /*thiscall*/ sub_483DF0(int *this, char pszArg2)  // 实现：遍历技能槽对非空项调用 ·sub_47E440
{
  int result; // eax
  int i; // esi

  result = *this;
  for ( i = 0; i < *this; ++i )
  {
    if ( *(uint32_t *)(*(this + 1) + 4 * i) != 0 )  // this+4〔宿主对象〕
      sub_47E440(pszArg2);  // 调 条目可见性旗标联动(推断)
    result = *this;
  }
  return result;
}



// ------------------------------------------------------------
// 0x483E30 sub_483E30 —— 技能槽数组整体清空（非空槽 ·sub_47ECE0 后置 0）
// 逐项对非空槽先 ·sub_47ECE0 解除引用再写 0；与 ·0x483DF0 的清点版本区别在于末尾不减计数。
// ------------------------------------------------------------
int /*thiscall*/ sub_483E30(int *this)  // 实现：技能槽数组整体清空（非空槽 ·sub_47ECE0 后置 0）
{
  int result; // eax
  int i; // esi

  result = *this;
  for ( i = 0; i < *this; ++i )
  {
    if ( *(uint32_t *)(*(this + 1) + 4 * i) != 0 )  // this+4〔宿主对象〕
      sub_47ECE0();  // 调 到 dword_8F85A8（收集/重挂列表）
    *(uint32_t *)(*(this + 1) + 4 * i) = 0;  // this+4〔宿主对象〕
    result = *this;
  }
  return result;
}



// ------------------------------------------------------------
// 0x483E70 sub_483E70 —— 技能槽交换请求（包 op 30，先做占用校验后本地预交换）
// 先校验计数 this+8 上限 nArg4、两下标合法，且当任一槽号小于 6 时对应槽对象 +124 必须为 0（锁定/封印标记【推断】）；包体依次写 nArg2、nArg3 各 1 字节后提交；byte_77F280 置位时另经 ·sub_483DA0 本地先行交换。
// ------------------------------------------------------------
char /*thiscall*/ sub_483E70(int *this, int nArg2, int nArg3, int nArg4)  // 实现：技能槽交换请求（包 op 30，先做占用校验后本地预交换）
{
  int fld_e1; // eax
  int fld_e12; // eax

  if ( *(this + 2) >= nArg4 )  // this+8〔nSkillRec8(推断)〕
    return 0;
  if ( nArg2 >= *this )
    return 0;
  if ( nArg3 >= *this )
    return 0;
  if ( nArg2 < 6 )
  {
    fld_e1 = *(uint32_t *)(*(this + 1) + 4 * nArg3);  // this+4〔宿主对象〕
    if ( fld_e1 != 0 && *(uint32_t *)(fld_e1 + 124) != 0 )  // fld_e1=this+4 宿主对象
      return 0;
  }
  if ( nArg3 < 6 )
  {
    fld_e12 = *(uint32_t *)(*(this + 1) + 4 * nArg2);  // this+4〔宿主对象〕
    if ( fld_e12 != 0 && *(uint32_t *)(fld_e12 + 124) != 0 )  // fld_e12=this+4 宿主对象
      return 0;
  }
  sub_423200(dword_8F7B08, 30);  // 【发送网络包API】
  HIBYTE(nArg4) = nArg2;
  sub_423290((char *)&nArg4 + 3, 1);  // 调 写 4B 长度
  HIBYTE(nArg4) = nArg3;
  sub_423290((char *)&nArg4 + 3, 1);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  ++*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( byte_77F280 != 0 )  // 调试机标志(DebugConfig.txt 校验)
    sub_483DA0(this, nArg2, nArg3);  // 技能槽交换（交换 nArg2/nArg3 两槽，计数先减 1）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x483F40 sub_483F40 —— 技能槽两步交换（依次两次 ·sub_483E70，允许数 1、2）
// 第一步 1 表示占用旧槽、第二步 2 表示占用新槽【推断：供界面交换指令复核】；任一步失败即返回 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_483F40(int *this, int nArg2, int nArg3, int nArg4)  // 实现：技能槽两步交换（依次两次 ·sub_483E70，允许数 1、2）
{
  char result; // al

  result = sub_483E70(this, nArg2, nArg3, 1);  // 结果 = 技能槽交换请求（包 op 30，先做占用校验后本地预交换）
  if ( result != 0 )  // 若结果非 0（成功）
    return sub_483E70(this, nArg3, nArg4, 2) != 0;  // 技能槽交换请求（包 op 30，先做占用校验后本地预交换）
  return result;
}



// ------------------------------------------------------------
// 0x483F80 sub_483F80 —— vector 过长异常抛出（std::length_error）
// 抛出串为 vector<T> too long（字符串证据），由 ·0x483FF0 在超出 0x1FFFFFFF 上限时调用。
// ------------------------------------------------------------
void /*noreturn*/ sub_483F80()  // vector 过长异常抛出（std::length_error）
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
  sub_401740(pExceptionObject, &v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常
}



// ------------------------------------------------------------
// 0x483FF0 sub_483FF0 —— 8 字节元素容器批量插入 insert(pos, n, value)
// 三分支扩容策略同 ·0x480FB0；新增元素经 ·sub_63A7C0（强化结果公共件）就地构造，前移与回填用 ·sub_44BD30、·sub_44BD00、·sub_41FEB0，超限时 ·sub_483F80 抛异常。
// ------------------------------------------------------------
void /*thiscall*/ sub_483FF0(int this, int nArg2, unsigned int uArg3, int pArg4)  // 实现：8 字节元素容器批量插入 insert(pos, n, value)
{
  void *v4; // edx
  int fld_4; // ecx
  unsigned int fld_C; // eax
  int fld_8; // edx
  int fld_82; // edx
  unsigned int v11; // eax
  int fld_87; // edx
  int fld_88; // eax
  char *pMem; // edi
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v17; // ebx
  int fld_83; // eax
  bool v20; // cf
  int v21; // ecx
  int fld_86; // ebx
  int v23; // ebx
  int fld_42; // [esp-18h] [ebp-40h]
  int fld_85; // [esp-Ch] [ebp-34h]
  unsigned int fld_84; // [esp-8h] [ebp-30h]
  int v27; // [esp+0h] [ebp-28h] BYREF
  void *v28[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v29; // [esp+24h] [ebp-4h]
  int v30; // [esp+30h] [ebp+8h]
  int v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int fld_832; // [esp+38h] [ebp+10h]

  v4 = *(void **)(pArg4 + 4);  // pArg4+4〔宿主对象〕
  v28[0] = *(void **)pArg4;
  fld_4 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    fld_C = 0;  // fld_C=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_8 = 0;  // fld_8=this+8 nSkillRec8
    if ( 0x1FFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_483F80(this);  // vector 过长异常抛出（std::length_error）
    if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( fld_C >= uArg3 + fld_82 )  // fld_C=this+12 nSkillRec12
    {
      fld_83 = *(uint32_t *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
      v20 = (fld_83 - nArg2) >> 3 < uArg3;  // fld_83=this+8 nSkillRec8
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;  // fld_83=this+8 nSkillRec8
      if ( v20 )
      {
        sub_44BD30(nArg2, fld_83, nArg2 + v21);  // 8 字节元素正向拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 3);  // this+8〔nSkillRec8(推断)〕等 2 字段
        fld_85 = *(uint32_t *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);  // 调 填充补足尾段
        fld_86 = v30 + *(uint32_t *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
        *(uint32_t *)(this + 8) = fld_86;  // this+8〔nSkillRec8(推断)〕等 2 字段
        sub_41FEB0(nArg2, fld_86 - v30, v28);  // 8B 元素区间拷贝
      }
      else
      {
        v23 = fld_83 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);  // 8 字节元素正向拷贝
        sub_44BD00(nArg2, v23, fld_832);  // 8 字节元素反向拷贝
        sub_41FEB0(nArg2, nArg2 + v30, v28);  // 8B 元素区间拷贝
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )  // fld_C=this+12 nSkillRec12
        v11 = (fld_C >> 1) + fld_C;  // fld_C=this+12 nSkillRec12
      else
        v11 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      if ( v11 < uArg3 + fld_87 )  // fld_87=this+8 nSkillRec8
      {
        if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else
          fld_88 = 0;  // fld_88=this+8 nSkillRec8
        v11 = uArg3 + fld_88;
      }
      v31 = 8 * v11;
      pMem = (char *)operator new(8 * v11);  // 分配 8 × v11 字节数组
      fld_42 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, nArg2, pMem);  // 结果 = 8 字节元素正向拷贝
      sub_63A7C0(v32, uArg3, v28);  // 强化结果公共件
      sub_44BD30(nArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);  // 8 字节元素正向拷贝
      fld_43 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
      if ( fld_43 != 0 )  // fld_43=this+4 宿主对象
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_89 = 0;  // fld_89=this+8 nSkillRec8
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )  // fld_43=this+4 宿主对象
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      *(uint32_t *)(this + 12) = &pMem[v31];  // this+12〔nSkillRec12(推断)〕等 2 字段
      *(uint32_t *)(this + 8) = &pMem[8 * v17];  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
    }
  }
}


// ------------------------------------------------------------
// 0x484240 sub_484240 —— 8 字节元素尾插（就地 ·sub_63A7C0，回落 ·0x483FF0）
// 空间足够时在 this+8 处就地 ·sub_63A7C0 构造 1 项并前移终点 8 字节。
// ------------------------------------------------------------
void /*thiscall*/ sub_484240(uint32_t *this, int nArg2)  // 实现：8 字节元素尾插（就地 ·sub_63A7C0，回落 ·0x483FF0）
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 3;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) >> 3 )  // this+12〔nSkillRec12(推断)〕
  {
    fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
    sub_63A7C0(fld_e22, 1, nArg2);  // 强化结果公共件
    *(this + 2) = fld_e22 + 8;  // this+8〔nSkillRec8(推断)〕
  }
  else
  {
    sub_483FF0((int)this, (uint32_t *)*(this + 2), 1u, nArg2);  // 8 字节元素容器批量插入 insert(pos, n, value)
  }
}



// ------------------------------------------------------------
// 0x4842B0 sub_4842B0 —— 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
// 匹配键为槽对象 +4（·sub_41A5E0 读值）等于 nArg2 且 +544 非 0，来源标记取 ·sub_47E340；主路径从 +392 列表项（标记为 0 时取后一项）末尾 24 字节元素的内嵌指针列表逐项 ·sub_437140 解析（哨兵 dword_8F857C 映射为 0，否则加 16）后经 ·sub_484240 追加。
// 回退路径按 dword_99FC9C 的 6 格掩码从 8*v4+0x77FCD8 表（·0x483CF0 遍历的同表）取项追加。
// ------------------------------------------------------------
int /*thiscall*/ sub_4842B0(int *this, int nArg2, void **pArg3)  // 实现：技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
{
  int v4; // edi
  int fld_e1; // eax
  int fld_e12; // esi
  void **pArg32; // ebx
  int v9; // esi
  int v10; // edi
  int v11; // eax
  int v12; // edx
  void ***v13; // esi
  void ***v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // ebx
  void **pArg33; // esi
  int v21; // [esp+Ch] [ebp-4h] BYREF
  int v22; // [esp+18h] [ebp+8h]

  v4 = 0;
  if ( *this <= 0 )
    return -1;
  while ( 1 )
  {
    fld_e1 = *(uint32_t *)(*(this + 1) + 4 * v4);  // this+4〔宿主对象〕
    if ( fld_e1 != 0 && sub_41A5E0(fld_e1 + 4) == nArg2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      break;
    if ( ++v4 >= *this )
      return -1;
  }
  fld_e12 = *(uint32_t *)(*(this + 1) + 4 * v4);  // this+4〔宿主对象〕
  if ( fld_e12 == 0 || sub_41A5E0(fld_e12 + 544) == 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    return -1;
  v22 = sub_47E340(fld_e12);  // 调 无→-1；仅 1 条→4；多条→是否第 0 条（1/0）
  if ( v22 != -1 )
  {
    pArg32 = pArg3;
    if ( pArg3 != nullptr )  // 若 pArg3 有效（非空）
    {
      if ( pArg3[1] != nullptr )
        j__free(pArg3[1]);  // 调 堆释放
      pArg32[1] = nullptr;
      pArg32[2] = nullptr;
      pArg32[3] = nullptr;
      v9 = *(uint32_t *)(fld_e12 + 392);  // fld_e12=this+4 宿主对象
      if ( v22 == 0 )
        v9 += 44;
      v10 = *(uint32_t *)(v9 + 4);
      if ( v10 != 0 )
        v11 = (*(uint32_t *)(v9 + 8) - v10) / 24;
      else
        v11 = 0;
      v12 = 3 * v11;
      v13 = *(void ****)(v10 + 24 * v11 - 20);
      v14 = *(void ****)(v10 + 24 * v11 - 16);
      v15 = v10 + 8 * v12 - 24;
      if ( v13 != v14 )
      {
        do
        {
          pArg3 = *v13;
          sub_437140(&v21, &pArg3);  // map 下界查找
          if ( v21 == dword_8F857C )
            v16 = 0;
          else
            v16 = v21 + 16;
          sub_484240(pArg32, v16);  // 8 字节元素尾插（就地 ·sub_63A7C0，回落 ·0x483FF0）
          ++v13;
        }
        while ( v13 != *(void ****)(v15 + 8) );
      }
    }
    return v22;
  }
  if ( v4 >= 6 || *((uint8_t *)&dword_99FC9C + v4) == 0 )
    return -1;
  v17 = *(uint32_t *)(fld_e12 + 392);  // fld_e12=this+4 宿主对象
  if ( v17 != 0 && (*(uint32_t *)(fld_e12 + 396) - v17) / 44 == 2 && dword_8F7C04 != 0 )  // 全局 dword_8F7C04 = 本机角色对象
  {
    v18 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1132))(dword_8F7C04, 0);  // 全局 dword_8F7C04 = 本机角色对象
    if ( v18 == 4 )
      v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 152))(dword_8F7C04);  // 全局 dword_8F7C04 = 本机角色对象
    else
      v19 = v18;
  }
  else
  {
    v19 = 4;
  }
  pArg33 = pArg3;
  if ( pArg3 != nullptr )  // 若 pArg3 有效（非空）
  {
    sub_5E5260(pArg3);  // 调 动画子对象清理临时缓冲
    if ( *((uint8_t *)&dword_99FC9C + v4) != 0 )
      sub_484240(pArg33, 8 * v4 + 7863512);  // 8 字节元素尾插（就地 ·sub_63A7C0，回落 ·0x483FF0）
  }
  return v19;
}



// ============================================================
// §E 0x484470-0x485330  技能槽状态族（+44/+52/+56）
// ============================================================
// ------------------------------------------------------------
// 0x484470 sub_484470 —— 技能槽计时器复位（+64 置 1、+52 处时钟归零）
// +52 处时钟经 ·sub_698F90 clock_set_countdown（时长与起始均为 0）重置，+52+13/+52+14 两字节清零。
// ------------------------------------------------------------
char /*thiscall*/ sub_484470(uint8_t *this)  // 实现：技能槽计时器复位（+64 置 1、+52 处时钟归零）
{
  int pThis_34; // ecx

  *(this + 64) = 1;  // this+256〔bQuad3〕
  pThis_34 = (int)(this + 52);  // this+208〔nField208(推断)〕
  *(uint8_t *)(pThis_34 + 13) = 0;  // pThis_34=this+208 nField208
  *(uint8_t *)(pThis_34 + 14) = 0;  // pThis_34=this+208 nField208
  return sub_698F90(pThis_34, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x484490 sub_484490 —— 技能槽记录清零
// +4 字写 0xFFFF 无效哨兵，+8/+12/+16/+20 清 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_484490(int this)  // 实现：技能槽记录清零
{
  *(uint16_t *)(this + 4) = -1;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
  *(uint32_t *)(this + 20) = 0;  // this+20〔nPage(推断)〕等 2 字段
  return 0;
}



// ------------------------------------------------------------
// 0x4844B0 sub_4844B0 —— 技能槽记录初始化（两内部缓冲析构）
// 转 ·sub_485020 处理 +16/+20 两处缓冲，并把 +4 置 0xFFFF、+8/+12 清零；与 ·0x4847F0 构造配套。
// ------------------------------------------------------------
int /*thiscall*/ sub_4844B0(int *this)  // 实现：技能槽记录初始化（两内部缓冲析构）
{
  int *pThis_4; // esi
  int i; // edi
  int v3; // ecx
  int result; // eax

  *((uint16_t *)this + 2) = -1;  // this+4〔宿主对象〕
  pThis_4 = this + 4;  // this+4 宿主对象
  for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
  {
    v3 = *pThis_4;  // pThis_4=this+4 宿主对象
    *(pThis_4 - 2) = 0;  // pThis_4=this+4 宿主对象
    result = sub_485020(v3);  // 结果 = 技能槽容器整体释放（模式 0/4 跳过前 3 槽）
    ++pThis_4;  // pThis_4=this+4 宿主对象
  }
  return result;
}



// ------------------------------------------------------------
// 0x4844E0 sub_4844E0 —— 技能自动施放开关切换（包 op 26，剩余冷却走提示串 419）
// +4 字为槽号（0xFFFF 无效）、+8 为当前开关；剩余冷却 = 表项 ·sub_429830 的 +176 加槽 +20 减槽 +16，为负时按 -差值*0.001 秒经 ·sub_422E70(419) 格式化并 ·sub_44E8D0(0x1B) 播报，否则发 1 字节新状态并 ·sub_540960、·sub_44AC80 刷新数量输入框。
// ------------------------------------------------------------
char /*thiscall*/ sub_4844E0(uint16_t *this, char pszArg2)  // 实现：技能自动施放开关切换（包 op 26，剩余冷却走提示串 419）
{
  char result; // al
  uint32_t *pThis; // esi
  const char *v4; // eax
  int pThis_B0; // [esp+10h] [ebp-4Ch]
  bool v6[4]; // [esp+14h] [ebp-48h] BYREF
  char Buffer[64]; // [esp+18h] [ebp-44h] BYREF
  int dword_796E502; // [esp+58h] [ebp-4h]

  result = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  pThis = this;
  LOWORD(this) = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  if ( (uint16_t)this != 0xFFFF )
  {
    result = pszArg2;
    if ( (pszArg2 != 0) != pThis[2] )
    {
      if ( pszArg2 != 0
        && *(int *)(pThis[4] + 4) > 0
        && (pThis_B0 = *(uint32_t *)(sub_429830(this) + 176) + *(uint32_t *)(pThis[5] + 4) - *(uint32_t *)(pThis[4] + 4)) < 0 )  // 表按键查找（uint16）
      {
        v4 = (const char *)sub_422E70(419);  // 调 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v4, -((double)pThis_B0 * 0.001));  // 调 格式化到缓冲
        return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);  // 对象池借出（按池号取可用对象）
      }
      else
      {
        sub_423200(dword_8F7B08, 26);  // 【发送网络包API】
        v6[0] = pszArg2 != 0;
        sub_423290(v6, 1);  // 调 写 4B 长度
        sub_423380(dword_8F7B08);  // 发包提交：Commit()
        result = pszArg2;
        if ( pszArg2 != 0 )
        {
          sub_540960(*((uint32_t *)dword_8F8528 + 29));  // 数量输入框刷新
          return sub_44AC80(dword_8F8528);  // 选中态复位
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x484600 sub_484600 —— 技能槽状态置 2 请求（包 op 26 写单字节 2）
// 槽号非 0xFFFF 时发送；用于第三态取消/停用路径【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_484600(uint16_t *this)  // 实现：技能槽状态置 2 请求（包 op 26 写单字节 2）
{
  int result; // eax
  uint16_t *pThis; // [esp+0h] [ebp-4h] BYREF

  pThis = this;
  if ( *(this + 2) != 0xFFFF )  // this+8〔nSkillRec8(推断)〕
  {
    sub_423200(dword_8F7B08, 26);  // 【发送网络包API】
    LOBYTE(pThis) = 2;
    sub_423290(&pThis, 1);  // 调 写 4B 长度
    return sub_423380(dword_8F7B08);  // 发包提交：Commit()
  }
  return result;
}



// ------------------------------------------------------------
// 0x484640 sub_484640 —— 技能槽取消/重置请求（包 op 10）
// 槽号为 0xFFFF 时发 1 字节 1、2 字节 nArg2 与 4 字节时间差（·sub_484FA0 与 dword_8F852C+4 之差），并 ·sub_43BEE0 播报 ·sub_422E70(421) 文案；否则仅播报 420。
// ------------------------------------------------------------
int /*thiscall*/ sub_484640(uint16_t *this, int nArg2)  // 实现：技能槽取消/重置请求（包 op 10）
{
  uint32_t *v2; // esi
  int v3; // eax
  int v5; // esi
  uint32_t *v6; // esi
  int v7; // eax

  if ( *(this + 2) == 0xFFFF )  // this+8〔nSkillRec8(推断)〕
  {
    sub_423200(dword_8F7B08, 10);  // 【发送网络包API】
    sub_423290(&nArg2, 2);  // 调 写 4B 长度
    HIBYTE(nArg2) = 1;
    sub_423290((char *)&nArg2 + 3, 1);  // 调 写 4B 长度
    v5 = *((uint32_t *)dword_8F852C + 1);  // 全局 dword_8F852C = 角色/物品栏管理器
    nArg2 = sub_484FA0() - v5;  // 结果 = 全局时间系数计算（+732 与 +746 相乘）
    sub_423290(&nArg2, 4);  // 调 写 4B 长度
    sub_423380(dword_8F7B08);  // 发包提交：Commit()
    v6 = *((uint32_t **)dword_8F8528 + 7);  // 全局 dword_8F8528 = 消息/弹窗管理器
    v7 = sub_422E70(421);  // 调 存 CStringManager::getStr 取本地化串
    return sub_43BEE0(v6, v7, -6567706, 0, -1);  // 调 播报 + 面板刷新 ──
  }
  else
  {
    v2 = *((uint32_t **)dword_8F8528 + 7);  // 全局 dword_8F8528 = 消息/弹窗管理器
    v3 = sub_422E70(420);  // 调 存 CStringManager::getStr 取本地化串
    return sub_43BEE0(v2, v3, -6567706, 0, -1);  // 调 播报 + 面板刷新 ──
  }
}



// ------------------------------------------------------------
// 0x484710 sub_484710 —— 技能槽状态写入（两字段组合播报）
// 写 this[+8+4*pArg2] = nArg3；pArg2 为 0 且 nArg3 为 1 时经 ·sub_540960、·sub_44AC80 刷新输入框；两状态均为 1 时播报 0x42，否则依次 ·sub_44E850(66)、·sub_44E850(27)。
// ------------------------------------------------------------
char /*thiscall*/ sub_484710(uint32_t *this, int pArg2, int nArg3)  // 实现：技能槽状态写入（两字段组合播报）
{
  *(this + pArg2 + 2) = nArg3;
  if ( pArg2 == 0 && nArg3 == 1 )  // 若 pArg2 == 0 与/或 nArg3 == 1
  {
    sub_540960(*((uint32_t *)dword_8F8528 + 29));  // 数量输入框刷新
    sub_44AC80(dword_8F8528);  // 选中态复位
  }
  if ( *(this + 2) == 1 && *(this + 3) == 1 )  // this+8〔nSkillRec8(推断)〕等 2 字段
    return sub_44E8D0((char *)dword_8F8528, (void *)0x42, 0, 0);  // 对象池借出（按池号取可用对象）
  sub_44E850(dword_8F8528, 66);  // 按池号批量回收活动对象
  return sub_44E850(dword_8F8528, 27);  // 按池号批量回收活动对象
}



// ------------------------------------------------------------
// 0x484790 sub_484790 —— 列表项数取回（+20 有效时返回 (end-begin)/4）
// this+20 为 4 字节元素列表的起始字段（+24 为终点），供 ·0x484880 与 ·0x484AF0 的占用校验。
// ------------------------------------------------------------
int /*thiscall*/ sub_484790(uint32_t *this)  // 实现：列表项数取回（+20 有效时返回 (end-begin)/4）
{
  int fld_e5; // edx

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 )  // fld_e5=this+20 nPage
    return (*(this + 6) - fld_e5) >> 2;  // this+24〔nPageMax(推断)〕
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4847B0 sub_4847B0 —— 两内部缓冲释放（+16/+20 先 ·sub_433E30 再 j__free 并清零）
// 固定两次迭代对应 ·0x4847F0 构造的 +16/+20 两对象。
// ------------------------------------------------------------
void /*thiscall*/ sub_4847B0(uint32_t *this)  // 实现：两内部缓冲释放（+16/+20 先 ·sub_433E30 再 j__free 并清零）
{
  uint32_t *pThis_4; // esi
  int i; // ebx
  void *v3; // edi

  pThis_4 = this + 4;  // this+4 宿主对象
  for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
  {
    v3 = (void *)*pThis_4;  // pThis_4=this+4 宿主对象
    if ( *pThis_4 != 0 )  // pThis_4=this+4 宿主对象
    {
      sub_433E30(*pThis_4);  // pThis_4=this+4 宿主对象
      j__free(v3);  // 调 堆释放
    }
    *pThis_4++ = 0;  // pThis_4=this+4 宿主对象
  }
}



// ------------------------------------------------------------
// 0x4847F0 sub_4847F0 —— 构造两个 32 字节内部对象
// 逐项清零 +20/+24/+28，调 ·sub_484CA0 初始化并经 ·sub_485E80(4, 27) 设定参数后写入 this+16/+20。
// ------------------------------------------------------------
int /*thiscall*/ sub_4847F0(uint32_t *this)  // 实现：构造两个 32 字节内部对象
{
  uint32_t *pThis_4; // ebx
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  int result; // eax
  int v5; // [esp+10h] [ebp-10h]

  pThis_4 = this + 4;  // this+4 宿主对象
  v5 = 2;
  do
  {
    pMem = operator new(0x20u);  // 堆分配 32 字节对象
    pMem2 = pMem;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
    {
      pMem[5] = 0;
      pMem[6] = 0;
      pMem[7] = 0;
      sub_484CA0(pMem);  // 32 字节内部对象清零（+0/+4/+8/+12，供 ·0x4847F0 构造）
      sub_485E80((void *)4, 27);  // 技能槽数组分配与默认填充
    }
    else
    {
      pMem2 = nullptr;
    }
    *pThis_4++ = pMem2;  // pThis_4=this+4 宿主对象
    result = v5 - 1;
    v5 = result;
  }
  while ( result != 0 );
  return result;
}



// ------------------------------------------------------------
// 0x484880 sub_484880 —— 4 字节列表尾插（容量不足回落 ·sub_430C80）
// 列表字段为 this+16{+20,+24}/{+28}；容量不足时转 ·sub_430C80 完成扩容与尾插。
// ------------------------------------------------------------
int /*thiscall*/ sub_484880(uint32_t *this, int nArg2)  // 实现：4 字节列表尾插（容量不足回落 ·sub_430C80）
{
  int fld_e5; // edx
  uint32_t *pThis_4; // ecx
  unsigned int v4; // esi
  int *nArg22; // eax
  int result; // eax

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  pThis_4 = this + 4;  // this+4 宿主对象
  if ( fld_e5 != 0 )  // fld_e5=this+20 nPage
    v4 = (pThis_4[2] - fld_e5) >> 2;  // pThis_4=this+4 宿主对象
  else
    v4 = 0;
  if ( fld_e5 == 0 || v4 >= (pThis_4[3] - fld_e5) >> 2 )  // fld_e5=this+20 nPage
    return sub_430C80((void *)pThis_4[2], 1, (int)&nArg2);  // uint32 vector 区间插入（同值填充）
  nArg22 = (int *)pThis_4[2];  // pThis_4=this+4 宿主对象
  *nArg22 = nArg2;
  result = (int)(nArg22 + 1);
  pThis_4[2] = result;  // pThis_4=this+4 宿主对象
  return result;
}



// ------------------------------------------------------------
// 0x4848E0 sub_4848E0 —— 技能施放请求（包 op 19：来源/槽/参数，前置等级与占用校验）
// 前置槽有效（+4 非 0xFFFF）、+8 非 1、+16 对象内 +20 列表为空；来源 uArg3 取 0 自身、1 物品、3 怪物技能，分别经 dword_8F852C 计数与 ·sub_44A980、dword_8F7C04 虚表 +792 取对象，等级校验小于 uArg5 即拒绝。
// 类型取对象虚表 +16 的 +4 字段，大于 2 时在 3..27 中寻找可施放该类型者（虚表 +60 判定），未果拒绝；包体依次写 1 字节来源、2 字节下标、4 字节参数、1 字节 4、2 字节 0；成功后向 ·sub_432F00(uArg3) 与对象 +16 列表各压入 5，来源与槽皆为 0 且参数非 0 时启动 ·sub_484470。
// ------------------------------------------------------------
char /*userpurge*/ sub_4848E0@<al>(int pArg1@<ecx>, int nArg2@<ebx>, unsigned int uArg3, int nArg4, unsigned int uArg5)  // 实现：技能施放请求（包 op 19：来源/槽/参数，前置等级与占用校验）
{
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v9; // edx
  int nArg43; // edi
  int pObj; // esi
  unsigned int v12; // eax
  unsigned int v13; // ebx
  int i; // esi
  int pObj2; // eax
  unsigned int uArg52; // esi
  uint32_t *v17; // eax
  int nArg42; // [esp-Ch] [ebp-10h]

  if ( *(uint16_t *)(pArg1 + 4) == 0xFFFF )  // pArg1+4〔宿主对象〕
    return 0;
  if ( *(uint32_t *)(pArg1 + 8) == 1 )  // pArg1+8〔nSkillRec8(推断)〕
    return 0;
  v5 = *(uint32_t *)(pArg1 + 16);  // pArg1+16〔nChannelTypeSel(推断)〕
  v6 = *(uint32_t *)(v5 + 20);
  v7 = v5 + 16;
  if ( v6 != 0 && (*(uint32_t *)(v7 + 8) - v6) >> 2 >= 1 )
    return 0;
  if ( uArg3 != 0 )
  {
    if ( uArg3 == 3 )
    {
      if ( nArg4 >= 18 || dword_8F7C04 == 0 )  // 全局 dword_8F7C04 = 本机角色对象
        return 0;
      pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, nArg4);  // 全局 dword_8F7C04 = 本机角色对象
      if ( pObj == 0 )
        return 0;
    }
    else
    {
      if ( uArg3 != 1 )
        return 0;
      nArg42 = nArg4;
      sub_432F00(1);  // 按类型取全局列表对象
      pObj = sub_44A980(nArg42);  // 结果 = 带界索引 getter
      if ( pObj == 0 )
        return 0;
    }
    nArg43 = nArg4;
    goto LABEL_21;
  }
  v9 = *((uint32_t *)dword_8F852C + 5);  // 全局 dword_8F852C = 角色/物品栏管理器
  if ( v9 != 0 && (*((uint32_t *)dword_8F852C + 6) - v9) >> 2 >= 1 )  // 全局 dword_8F852C = 角色/物品栏管理器
    return 0;
  nArg43 = nArg4;
  if ( nArg4 >= *((uint32_t *)dword_8F852C + 2) )  // 全局 dword_8F852C = 角色/物品栏管理器
    return 0;
  pObj = sub_44A980(nArg4);  // 结果 = 带界索引 getter
  if ( pObj == 0 )
    return 0;
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj);  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420…
  if ( v12 < uArg5 )
    return 0;
LABEL_21:
  v13 = *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 16))(pObj, nArg2) + 4);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
  if ( v13 > 2 )
  {
    for ( i = 3; i < 27; ++i )  // 循环：i 从 3 递增到 27
    {
      if ( sub_44A980(i) == 0 )  // 带界索引 getter
        break;
      pObj2 = sub_44A980(i);  // 结果 = 带界索引 getter
      if ( (*(uint8_t (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)pObj2 + 60))(pObj2, v13) != 0 )  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
        break;
    }
    if ( i == 27 )
      return 0;
    nArg43 = nArg4;
  }
  sub_423200(dword_8F7B08, 19);  // 【发送网络包API】
  HIBYTE(nArg4) = uArg3;
  sub_423290((char *)&nArg4 + 3, 1);  // 调 写 4B 长度
  nArg4 = nArg43;
  sub_423290(&nArg4, 2);  // 调 写 4B 长度
  uArg52 = uArg5;
  nArg4 = uArg5;
  sub_423290(&nArg4, 4);  // 调 写 4B 长度
  HIBYTE(nArg4) = 4;
  sub_423290((char *)&nArg4 + 3, 1);  // 调 写 4B 长度
  nArg4 = 0;
  sub_423290(&nArg4, 2);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  if ( uArg3 <= 1 )
  {
    v17 = (uint32_t *)sub_432F00(uArg3);  // 结果 = 按类型取全局列表对象
    sub_484880(v17, 5);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  }
  sub_484880(*(uint32_t **)(pArg1 + 16), 5);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  if ( uArg3 == 0 && nArg43 == 0 && uArg52 != 0 )  // 若 uArg3 == 0 与/或 nArg43 == 0 与/或 uArg52 != 0
    sub_484470((uint8_t *)pArg1);  // 技能槽计时器复位（+64 置 1、+52 处时钟归零）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x484AF0 sub_484AF0 —— 技能施放请求（包 op 19 变体：槽/参数/来源字段序不同）
// 对象从 +16 列表按 nArg2 取、前置 +20 列表须空；来源 uArg4 取 0、1、3 时分别要求 dword_8F852C 列表空、dword_8F8534 列表空、dword_8F7C04 虚表 +20 与 +172 校验通过。
// 包体依次写 1 字节 4、2 字节 nArg2、4 字节 uArg3、1 字节来源、2 字节 nArg5；尾部与 ·0x4848E0 一致地压入 5 并按条件启动 ·sub_484470。
// ------------------------------------------------------------
char /*thiscall*/ sub_484AF0(int this, signed int nArg2, unsigned int uArg3, unsigned int uArg4, int nArg5)  // 实现：技能施放请求（包 op 19 变体：槽/参数/来源字段序不同）
{
  uint32_t *fld_10; // ecx
  int v6; // edx
  int v8; // ecx
  int pObj; // esi
  unsigned int v10; // eax
  unsigned int uArg42; // ebx
  signed int nArg52; // edi
  uint32_t *dword_8F852C2; // esi
  signed int nArg22; // esi
  uint32_t *v15; // eax

  if ( *(uint16_t *)(this + 4) == 0xFFFF )  // this+4〔宿主对象〕等 2 字段
    return 0;
  if ( *(uint32_t *)(this + 8) == 1 )  // this+8〔nSkillRec8(推断)〕等 2 字段
    return 0;
  fld_10 = *(uint32_t **)(this + 16);  // this+64〔apServerTabBtn(推断)〕
  v6 = fld_10[5];  // fld_10=this+64 apServerTabBtn
  if ( v6 != 0 && (fld_10[6] - v6) >> 2 >= 1 )  // fld_10=this+64 apServerTabBtn
    return 0;
  if ( nArg2 >= fld_10[2] )  // fld_10=this+64 apServerTabBtn
    return 0;
  v8 = fld_10[3];  // fld_10=this+64 apServerTabBtn
  pObj = *(uint32_t *)(v8 + 4 * nArg2);
  if ( pObj == 0 )
    return 0;
  v10 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj + 44))(*(uint32_t *)(v8 + 4 * nArg2));  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420…
  if ( v10 < uArg3 )
    return 0;
  uArg42 = uArg4;
  nArg52 = nArg5;
  if ( uArg4 != 0 )
  {
    if ( uArg4 == 3 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 20))(pObj, 2) == 0 )  // 调虚槽 +20：CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认…
        return 0;
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj) != nArg52 )  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
        return 0;
    }
    else if ( uArg4 != 1 || sub_484790(dword_8F8534) > 0 )  // 列表项数取回（+20 有效时返回 (end-begin)/4）
    {
      return 0;
    }
  }
  else
  {
    dword_8F852C2 = dword_8F852C;  // 全局 dword_8F852C = 角色/物品栏管理器
    if ( sub_484790(dword_8F852C) >= 1 || nArg52 >= dword_8F852C2[2] )  // 列表项数取回（+20 有效时返回 (end-begin)/4）
      return 0;
  }
  sub_423200(dword_8F7B08, 19);  // 【发送网络包API】
  HIBYTE(uArg4) = 4;
  sub_423290((char *)&uArg4 + 3, 1);  // 调 写 4B 长度
  nArg22 = nArg2;
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  nArg2 = uArg3;
  sub_423290(&nArg2, 4);  // 调 写 4B 长度
  HIBYTE(nArg2) = uArg42;
  sub_423290((char *)&nArg2 + 3, 1);  // 调 写 4B 长度
  nArg2 = nArg52;
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  if ( uArg42 <= 1 )
  {
    v15 = (uint32_t *)sub_432F00(uArg42);  // 结果 = 按类型取全局列表对象
    sub_484880(v15, 5);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  }
  sub_484880(*(uint32_t **)(this + 16), 5);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  if ( uArg42 == 0 && nArg22 == 0 && uArg3 != 0 )  // 若 uArg42 == 0 与/或 nArg22 == 0 与/或 uArg3 != 0
    sub_484470((uint8_t *)this);  // 技能槽计时器复位（+64 置 1、+52 处时钟归零）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x484CA0 sub_484CA0 —— 32 字节内部对象清零（+0/+4/+8/+12，供 ·0x4847F0 构造）
// 对象大小 32 字节（见 ·0x4847F0 的 operator new(0x20)），+16/+20/+24/+28 为后续写入的字段区。
// ------------------------------------------------------------
int /*thiscall*/ sub_484CA0(uint32_t *this)  // 实现：32 字节内部对象清零（+0/+4/+8/+12，供 ·0x4847F0 构造）
{
  *this = 0;
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
  return 0;
}



// ------------------------------------------------------------
// 0x484CB0 sub_484CB0 —— 内部对象数组释放（+12 数组每项走虚表 +4 槽）
// 遍历 [this+12, +12+4*(this+8)) 每项经虚表 +4 槽销毁，末尾释放 this+12；由 ·0x483C60 分配的数组最终在此收尾。
// ------------------------------------------------------------
void /*thiscall*/ sub_484CB0(int this)  // 实现：内部对象数组释放（+12 数组每项走虚表 +4 槽）
{
  int i; // edi
  int fld_C; // ecx

  for ( i = 0; i < *(uint32_t *)(this + 8); ++i )  // this+8〔nSkillRec8(推断)〕等 2 字段
  {
    fld_C = *(uint32_t *)(*(uint32_t *)(this + 12) + 4 * i);  // this+12〔nSkillRec12(推断)〕等 2 字段
    if ( fld_C != 0 )  // fld_C=this+12 nSkillRec12
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_C + 4))(fld_C, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
      *(uint32_t *)(*(uint32_t *)(this + 12) + 4 * i) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    }
  }
  if ( *(uint32_t *)(this + 12) != 0 )  // this+12〔nSkillRec12(推断)〕等 2 字段
    j_j__free(*(void **)(this + 12));  // this+48〔pCmdVecBegin48(推断)〕
  *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
}



// ------------------------------------------------------------
// 0x484D00 sub_484D00 —— 槽汇总统计（累加各对象虚表 +36 值）
// 先置 *(this+1) 为 0 再累加各非空项虚表 +36 返回值；当 *this 为 0 且 dword_8F7C04 存在时追加其虚表 +796 返回值。
// ------------------------------------------------------------
int /*thiscall*/ sub_484D00(int *this)  // 实现：槽汇总统计（累加各对象虚表 +36 值）
{
  int result; // eax
  int v3; // edi
  int fld_e3; // ecx

  result = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  v3 = 0;
  for ( *(this + 1) = 0; v3 < result; ++v3 )  // this+4〔宿主对象〕
  {
    fld_e3 = *(uint32_t *)(*(this + 3) + 4 * v3);  // this+12〔nSkillRec12(推断)〕
    if ( fld_e3 != 0 )  // fld_e3=this+12 nSkillRec12
      *(this + 1) += (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e3 + 36))(fld_e3);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    result = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  }
  if ( *this == 0 && dword_8F7C04 != 0 )  // 全局 dword_8F7C04 = 本机角色对象
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 796))(dword_8F7C04);  // 全局 dword_8F7C04 = 本机角色对象
    *(this + 1) += result;  // this+4〔宿主对象〕
  }
  return result;  // result=this+8 nSkillRec8
}



// ------------------------------------------------------------
// 0x484D50 sub_484D50 —— 技能槽清空（按槽类型分流）
// 通用槽（*this 非 0 且非 4，或下标不小于 3）走虚表 +4 释放并置 0 后由 ·sub_484D00 重算；0 与 4 类的前 3 槽仅调虚表 +40 置空。
// ------------------------------------------------------------
int /*thiscall*/ sub_484D50(int *this, int nArg2)  // 实现：技能槽清空（按槽类型分流）
{
  int result; // eax
  int fld_e32; // ecx
  int fld_e3; // ecx

  result = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( nArg2 < result )  // result=this+8 nSkillRec8
  {
    if ( *this != 0 && *this != 4 || nArg2 >= 3 )
    {
      fld_e3 = *(uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
      if ( fld_e3 != 0 )  // fld_e3=this+12 nSkillRec12
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e3 + 4))(fld_e3, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
      *(uint32_t *)(*(this + 3) + 4 * nArg2) = 0;  // this+12〔nSkillRec12(推断)〕
      return sub_484D00(this);  // 槽汇总统计（累加各对象虚表 +36 值）
    }
    else
    {
      fld_e32 = *(uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
      return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e32 + 40))(fld_e32, 0);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    }
  }
  return result;  // result=this+8 nSkillRec8
}



// ------------------------------------------------------------
// 0x484DB0 sub_484DB0 —— 槽区间空位连续性检查
// 在 [nArg2, min(nArg3, 项数-1)] 内一旦出现空槽后再遇非空即返回 0，即只允许连续尾段为空。
// ------------------------------------------------------------
char /*thiscall*/ sub_484DB0(uint32_t *this, int nArg2, int nArg3)  // 实现：槽区间空位连续性检查
{
  int fld_e2; // eax
  int nArg32; // edx
  int nArg22; // eax
  char v6; // bl
  uint32_t *fld_e3; // esi

  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  nArg32 = nArg3;
  if ( nArg3 >= fld_e2 )  // fld_e2=this+8 nSkillRec8
    nArg32 = fld_e2 - 1;
  nArg22 = nArg2;
  v6 = 0;
  if ( nArg2 <= nArg32 )
  {
    fld_e3 = (uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
    do
    {
      if ( *fld_e3 != 0 )  // fld_e3=this+12 nSkillRec12
      {
        if ( v6 != 0 )
          return 0;
      }
      else
      {
        v6 = 1;
      }
      ++nArg22;
      ++fld_e3;  // fld_e3=this+12 nSkillRec12
    }
    while ( nArg22 <= nArg32 );
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x484E00 sub_484E00 —— 按类型查找并取数值（虚表 +16/+4 匹配）
// 命中条件为对象虚表 +16 的 +4 字段等于 nArg2 且虚表 +20(obj,1) 为真，命中后返回虚表 +44 值；未命中返回累计跳过计数【推断：作为失败回退值】。
// ------------------------------------------------------------
int /*thiscall*/ sub_484E00(int *this, int nArg2)  // 实现：按类型查找并取数值（虚表 +16/+4 匹配）
{
  int v3; // esi
  int fld_e3; // eax
  int fld_e32; // ecx
  int fld_e33; // ecx
  int v8; // [esp+Ch] [ebp-4h]

  v3 = 0;
  v8 = 0;
  if ( *(this + 2) <= 0 )  // this+8〔nSkillRec8(推断)〕
    return v8;
  while ( 1 )
  {
    fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
    if ( *(uint32_t *)(fld_e3 + 4 * v3) != 0  // fld_e3=this+12 nSkillRec12
      && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(fld_e3 + 4 * v3) + 16))(*(uint32_t *)(fld_e3 + 4 * v3)) + 4) == nArg2 )  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE…
    {
      fld_e32 = *(uint32_t *)(*(this + 3) + 4 * v3);  // this+12〔nSkillRec12(推断)〕
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e32 + 20))(fld_e32, 1) != 0 )  // 调虚槽 +20：CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认…
        break;
      ++v8;
    }
    if ( ++v3 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
      return v8;
  }
  fld_e33 = *(uint32_t *)(*(this + 3) + 4 * v3);  // this+12〔nSkillRec12(推断)〕
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e33 + 44))(fld_e33);  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420…
}



// ------------------------------------------------------------
// 0x484E80 sub_484E80 —— 按类型查找下标（同一匹配规则，未命中 -1）
// 与 ·0x484E00 匹配规则一致，差别在于仅定位下标而不取虚表 +44 值。
// ------------------------------------------------------------
int /*thiscall*/ sub_484E80(int *this, int nArg2)  // 实现：按类型查找下标（同一匹配规则，未命中 -1）
{
  int v3; // esi
  int fld_e3; // eax

  v3 = 0;
  if ( *(this + 2) <= 0 )  // this+8〔nSkillRec8(推断)〕
    return -1;
  while ( 1 )
  {
    fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
    if ( *(uint32_t *)(fld_e3 + 4 * v3) != 0  // fld_e3=this+12 nSkillRec12
      && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(fld_e3 + 4 * v3) + 16))(*(uint32_t *)(fld_e3 + 4 * v3)) + 4) == nArg2 )  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE…
    {
      break;
    }
    if ( ++v3 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
      return -1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x484ED0 sub_484ED0 —— 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
// 按指针相等在 this+12 数组中线性查找，本族中唯一以指针（而非类型码）为键的查找。
// ------------------------------------------------------------
int /*thiscall*/ sub_484ED0(int *this, int nArg2)  // 实现：由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
{
  int result; // eax
  int fld_e2; // edx
  uint32_t *i; // ecx

  if ( nArg2 == 0 )
    return -1;
  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  result = 0;
  if ( fld_e2 <= 0 )  // fld_e2=this+8 nSkillRec8
    return -1;
  for ( i = (uint32_t *)*(this + 3); *i != nArg2; ++i )  // this+12〔nSkillRec12(推断)〕
  {
    if ( ++result >= fld_e2 )  // fld_e2=this+8 nSkillRec8
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x484F10 sub_484F10 —— 32 字节对象列表空判定（+4 为 0 或元素数 0）
// 列表字段为 this+4{+8}，元素 4 字节；调用方以真值表示当前无有效对象。
// ------------------------------------------------------------
bool /*thiscall*/ sub_484F10(uint32_t *this)  // 实现：32 字节对象列表空判定（+4 为 0 或元素数 0）
{
  int pVecEnd_3; // edx

  pVecEnd_3 = *(this + 1);  // this+4〔宿主对象〕
  return pVecEnd_3 == 0 || (*(this + 2) - pVecEnd_3) >> 2 == 0;  // this+8〔nSkillRec8(推断)〕
}



// ------------------------------------------------------------
// 0x484F40 sub_484F40 —— 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
// 写 this+12 数组第 nArg2 项为 nArg3，并调 nArg3 虚表 +28 建立反向引用，随后 ·sub_484D00 重算；pszArg4 为 1 且 *this 为 0 且 nArg3 非空时调 ·sub_5473D0（物品栏辅助）。
// ------------------------------------------------------------
char /*thiscall*/ sub_484F40(int *this, int nArg2, int nArg3, char pszArg4)  // 实现：技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
{
  if ( nArg2 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    return 0;
  *(uint32_t *)(*(this + 3) + 4 * nArg2) = nArg3;  // this+12〔nSkillRec12(推断)〕
  if ( nArg3 != 0 )
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)nArg3 + 28))(nArg3, this);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
  sub_484D00(this);  // 槽汇总统计（累加各对象虚表 +36 值）
  if ( pszArg4 == 1 && *this == 0 && nArg3 != 0 )  // 若 pszArg4 == 1 与/或 nArg3 != 0
    sub_5473D0(nArg3);  // 物品栏辅助（484ED0）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x484FA0 sub_484FA0 —— 全局时间系数计算（+732 与 +746 相乘）
// 经 dword_8F7C04 虚表 +672(3) 取对象，读 +732 与 +746 两值（·sub_41A5E0）相乘；dword_8F7C04 为空时返回 -1；结果被 ·0x484640 用作包 op 10 的时间差字段。
// ------------------------------------------------------------
int sub_484FA0()  // 全局时间系数计算（+732 与 +746 相乘）
{
  int v0; // esi
  int64_t v1; // rax
  int v3; // [esp+4h] [ebp-4h]

  if ( dword_8F7C04 != 0 )  // 全局 dword_8F7C04 = 本机角色对象
  {
    v0 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3);  // 全局 dword_8F7C04 = 本机角色对象
    v3 = sub_41A5E0(v0 + 732);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0(v0 + 746)));  // crypt4byte 解密校验（·0x41A590 逆运算）
  }
  else
  {
    LODWORD(v1) = -1;
  }
  return v1;
}



// ------------------------------------------------------------
// 0x484FF0 sub_484FF0 —— 4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
// this+20{+24} 为 4 字节元素列表；弹出即终点减 4，仅当列表非空时生效。
// ------------------------------------------------------------
int /*thiscall*/ sub_484FF0(uint32_t *this)  // 实现：4 字节列表尾部弹出（终点回退 4，返回弹出前项数）
{
  int fld_e5; // edx
  int result; // eax

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 )  // fld_e5=this+20 nPage
  {
    result = (*(this + 6) - fld_e5) >> 2;  // this+24〔nPageMax(推断)〕
    if ( result != 0 )  // 若结果非 0（成功）
    {
      result = (*(this + 6) - fld_e5) >> 2;  // this+24〔nPageMax(推断)〕
      if ( result != 0 )  // 若结果非 0（成功）
        *(this + 6) -= 4;  // this+24〔nPageMax(推断)〕
    }
  }
  return result;  // result=this+24 nPageMax
}



// ------------------------------------------------------------
// 0x485020 sub_485020 —— 技能槽容器整体释放（模式 0/4 跳过前 3 槽）
//   模式 *this 为 0 或 4 时从下标 3 起，否则从 0 起：逐个把非空槽对象经虚表 +4 释放并置 0，+1 选中项清零。
//   模式 0/4 另对前 3 槽虚表 +40 复位，末尾 free +5 命令等待队列缓冲（+6/+7 清零）。
// ------------------------------------------------------------
void /*thiscall*/ sub_485020(int *this)  // 实现：技能槽容器整体释放（模式 0/4 跳过前 3 槽）
{
  int v2; // edi
  int fld_e3; // ecx
  int v4; // eax
  bool v5; // zf

  v2 = 0;
  if ( *this == 0 || *this == 4 )
    v2 = 3;
  for ( ; v2 < *(this + 2); ++v2 )  // this+8〔nSkillRec8(推断)〕
  {
    fld_e3 = *(uint32_t *)(*(this + 3) + 4 * v2);  // this+12〔nSkillRec12(推断)〕
    if ( fld_e3 != 0 )  // fld_e3=this+12 nSkillRec12
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e3 + 4))(fld_e3, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
      *(uint32_t *)(*(this + 3) + 4 * v2) = 0;  // this+12〔nSkillRec12(推断)〕
    }
  }
  v4 = *this;
  v5 = *this == 0;
  *(this + 1) = 0;  // this+4〔宿主对象〕
  if ( v5 || v4 == 4 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)*(this + 3) + 40))(*(uint32_t *)*(this + 3), 0);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*(this + 3) + 4) + 40))(*(uint32_t *)(*(this + 3) + 4), 0);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*(this + 3) + 8) + 40))(*(uint32_t *)(*(this + 3) + 8), 0);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  }
  if ( *(this + 5) != 0 )  // this+20〔nPage(推断)〕
    j__free((void *)*(this + 5));  // this+20〔nPage(推断)〕
  *(this + 5) = 0;  // this+20〔nPage(推断)〕
  *(this + 6) = 0;  // this+24〔nPageMax(推断)〕
  *(this + 7) = 0;  // this+28〔pPanelVec(推断)〕
}



// ------------------------------------------------------------
// 0x4850B0 sub_4850B0 —— 本地命令 0 执行：槽值设置或扣减（op 18）
//   先弹出等待队列尾项；槽有效时对象虚表 +44 剩余量 <= uArg3 即整槽清空（·sub_484D50），否则虚表 +52 把值设为 uArg3；成功返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_4850B0(int *this, int nArg2, unsigned int uArg3)  // 实现：本地命令 0 执行：槽值设置或扣减（op 18）
{
  int fld_e5; // ecx
  int fld_e52; // ecx
  int fld_e3; // eax
  int fld_e32; // ecx

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 == 0 || (*(this + 6) - fld_e5) >> 2 <= 0 )  // this+24〔nPageMax(推断)〕
    return 0;
  fld_e52 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e52 != 0 && (*(this + 6) - fld_e52) >> 2 != 0 && (*(this + 6) - *(this + 5)) >> 2 != 0 )  // this+24〔nPageMax(推断)〕等 2 字段
    *(this + 6) -= 4;  // this+24〔nPageMax(推断)〕
  if ( nArg2 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    return 0;
  fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
  if ( *(uint32_t *)(fld_e3 + 4 * nArg2) == 0 )  // fld_e3=this+12 nSkillRec12
    return 0;
  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(fld_e3 + 4 * nArg2) + 44))(*(uint32_t *)(fld_e3 + 4 * nArg2)) <= uArg3 )  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 +…
  {
    sub_484D50(this, nArg2);  // 技能槽清空（按槽类型分流）
  }
  else
  {
    fld_e32 = *(uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
    (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)fld_e32 + 52))(fld_e32, uArg3);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x485150 sub_485150 —— 本地命令 0 批量执行（op 18 槽数组）
//   pArg2 为 8 字节 (槽号, 值) 对数组：任一项槽空或虚表 +44 < 值即整批拒绝返回 0。
//   通过后逐项应用——模式 0/4 且槽号 < 3 走虚表 +40 复位，否则释放槽对象并 ·sub_484D00 汇总统计；值不足的项由虚表 +52 设置。
// ------------------------------------------------------------
char /*thiscall*/ sub_485150(int *this, int pArg2)  // 实现：本地命令 0 批量执行（op 18 槽数组）
{
  int fld_e5; // ecx
  int fld_e52; // ecx
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  uint32_t *v8; // ecx
  int v9; // edi
  unsigned int v10; // ebx
  int fld_e3; // ecx
  int fld_e34; // ecx
  int fld_e33; // ecx
  int fld_e32; // ecx
  uint32_t *v15; // [esp+4h] [ebp-4h]

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 == 0 || (*(this + 6) - fld_e5) >> 2 <= 0 )  // this+24〔nPageMax(推断)〕
    return 0;
  fld_e52 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e52 != 0 && (*(this + 6) - fld_e52) >> 2 != 0 && (*(this + 6) - *(this + 5)) >> 2 != 0 )  // this+24〔nPageMax(推断)〕等 2 字段
    *(this + 6) -= 4;  // this+24〔nPageMax(推断)〕
  v6 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  v7 = *(uint32_t **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
  v8 = v6;
  if ( v6 == v7 )
  {
LABEL_12:
    v15 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v6 != v7 )
    {
      while ( 1 )
      {
        v9 = *v6;
        v10 = v6[1];
        fld_e3 = *(uint32_t *)(*(this + 3) + 4 * *v6);  // this+12〔nSkillRec12(推断)〕
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e3 + 44))(fld_e3) <= v10 )  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420…
        {
          if ( v9 < *(this + 2) )  // this+8〔nSkillRec8(推断)〕
          {
            if ( *this != 0 && *this != 4 || v9 >= 3 )
            {
              fld_e32 = *(uint32_t *)(*(this + 3) + 4 * v9);  // this+12〔nSkillRec12(推断)〕
              if ( fld_e32 != 0 )  // fld_e32=this+12 nSkillRec12
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e32 + 4))(fld_e32, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
              *(uint32_t *)(*(this + 3) + 4 * v9) = 0;  // this+12〔nSkillRec12(推断)〕
              sub_484D00(this);  // 槽汇总统计（累加各对象虚表 +36 值）
            }
            else
            {
              fld_e33 = *(uint32_t *)(*(this + 3) + 4 * v9);  // this+12〔nSkillRec12(推断)〕
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e33 + 40))(fld_e33, 0);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
            }
          }
        }
        else
        {
          fld_e34 = *(uint32_t *)(*(this + 3) + 4 * v9);  // this+12〔nSkillRec12(推断)〕
          (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)fld_e34 + 52))(fld_e34, v10);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        }
        v15 += 2;
        if ( v15 == *(uint32_t **)(pArg2 + 8) )  // pArg2+8〔nSkillRec8(推断)〕
          break;
        v6 = v15;
      }
    }
    return 1;  // 返回 1(成功)
  }
  else
  {
    while ( *v8 < *(this + 2) && *(uint32_t *)(*(this + 3) + 4 * *v8) != 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
    {
      v8 += 2;
      if ( v8 == v7 )
        goto LABEL_12;
    }
    return 0;
  }
}



// ------------------------------------------------------------
// 0x485270 sub_485270 —— 本地命令：两槽内容交换
//   两下标须都小于槽数；目标槽非空时先经该对象虚表 +56 取值并 ·sub_432EA0 播报音效；随后互换 this+3 数组两项并返回 1。【推断：技能栏拖拽换位】
// ------------------------------------------------------------
char /*thiscall*/ sub_485270(uint32_t *this, int nArg2, int nArg3)  // 实现：本地命令：两槽内容交换
{
  int fld_e5; // ecx
  int fld_e52; // ecx
  int fld_e2; // eax
  int fld_e3; // eax
  int fld_e33; // ecx
  void *v10; // eax
  int fld_e32; // eax
  int v12; // ecx

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 == 0 || (*(this + 6) - fld_e5) >> 2 <= 0 )  // this+24〔nPageMax(推断)〕
    return 0;
  fld_e52 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e52 != 0 && (*(this + 6) - fld_e52) >> 2 != 0 && (*(this + 6) - *(this + 5)) >> 2 != 0 )  // this+24〔nPageMax(推断)〕等 2 字段
    *(this + 6) -= 4;  // this+24〔nPageMax(推断)〕
  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( nArg2 < fld_e2 && nArg3 < fld_e2 )  // 若 nArg2 < fld_e2 与/或 nArg3 < fld_e2
  {
    fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
    if ( *(uint32_t *)(fld_e3 + 4 * nArg3) != 0 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e33 = *(uint32_t *)(fld_e3 + 4 * nArg3);  // fld_e3=this+12 nSkillRec12
    }
    else
    {
      if ( *(uint32_t *)(fld_e3 + 4 * nArg2) == 0 )  // fld_e3=this+12 nSkillRec12
      {
LABEL_15:
        fld_e32 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
        v12 = *(uint32_t *)(fld_e32 + 4 * nArg2);  // fld_e32=this+12 nSkillRec12
        *(uint32_t *)(fld_e32 + 4 * nArg2) = *(uint32_t *)(fld_e32 + 4 * nArg3);  // fld_e32=this+12 nSkillRec12
        *(uint32_t *)(*(this + 3) + 4 * nArg3) = v12;  // this+12〔nSkillRec12(推断)〕
        return 1;  // 返回 1(成功)
      }
      fld_e33 = *(uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
    }
    v10 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e33 + 56))(fld_e33);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    sub_432EA0(v10, -1, 0, 0);  // 音效播放包装（非空判定）
    goto LABEL_15;
  }
  return 0;
}



// ============================================================
// §F 0x485330-0x487310  技能命令/施放处理（ALERT_1）
// ============================================================
// ------------------------------------------------------------
// 0x485330 sub_485330 —— 技能槽命令处理（+44/+48/+52/+56 槽位字段；音效 sub_432EA0）
// ------------------------------------------------------------
char /*thiscall*/ sub_485330(int *this, int nArg2, unsigned int uArg3, int *pDwArg4, int nArg5)  // 实现：技能槽命令处理（+44/+48/+52/+56 槽位字段；音效 sub_432EA0）
{
  int fld_e5; // ecx
  int v7; // edx
  int fld_e52; // edx
  int v9; // edx
  int fld_e3; // ecx
  int fld_e32; // edi
  int pObj; // eax
  void *v13; // eax
  int v14; // ebx
  int fld_e33; // ecx
  int v17; // eax
  int v18; // eax
  int fld_e34; // ecx
  int pObj2; // [esp+4h] [ebp-4h]

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 == 0 )  // fld_e5=this+20 nPage
    return 0;
  if ( (*(this + 6) - fld_e5) >> 2 <= 0 )  // this+24〔nPageMax(推断)〕
    return 0;
  v7 = pDwArg4[5];
  if ( v7 == 0 || (pDwArg4[6] - v7) >> 2 <= 0 )
    return 0;
  fld_e52 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e52 != 0 && (*(this + 6) - fld_e52) >> 2 != 0 )  // this+24〔nPageMax(推断)〕
    *(this + 6) -= 4;  // this+24〔nPageMax(推断)〕
  v9 = pDwArg4[5];
  if ( v9 != 0 && (pDwArg4[6] - v9) >> 2 != 0 && (pDwArg4[6] - pDwArg4[5]) >> 2 != 0 )
    pDwArg4[6] -= 4;
  if ( nArg2 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    return 0;
  if ( nArg5 >= pDwArg4[2] )
    return 0;
  fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
  if ( *(uint32_t *)(fld_e3 + 4 * nArg2) == 0  // fld_e3=this+12 nSkillRec12
    || (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(fld_e3 + 4 * nArg2) + 44))(*(uint32_t *)(fld_e3 + 4 * nArg2)) < uArg3 )  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 +…
  {
    return 0;
  }
  fld_e32 = *(uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
  pObj = sub_44A980(nArg5);  // 结果 = 带界索引 getter
  pObj2 = pObj;
  if ( fld_e32 != 0 )  // fld_e32=this+12 nSkillRec12
  {
    v13 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e32 + 56))(fld_e32);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    sub_432EA0(v13, -1, 0, 0);  // 音效播放包装（非空判定）
    pObj = pObj2;
  }
  if ( pObj != 0 )
  {
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e32 + 16))(fld_e32) + 4) != *(uint32_t *)(v14 + 4) )  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
      return 0;
    (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)pObj2 + 48))(pObj2, uArg3);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)fld_e32 + 52))(fld_e32, uArg3);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e32 + 44))(fld_e32) == 0 )  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420…
      sub_484D50(this, nArg2);  // 技能槽清空（按槽类型分流）
  }
  else
  {
    fld_e33 = *(uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e33 + 44))(fld_e33) == uArg3 )  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420…
    {
      sub_484F40(pDwArg4, nArg5, *(uint32_t *)(*(this + 3) + 4 * nArg2), 1);  // 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
      *(uint32_t *)(*(this + 3) + 4 * nArg2) = 0;  // this+12〔nSkillRec12(推断)〕
    }
    else
    {
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e32 + 16))(fld_e32);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
      v18 = sub_522300(*(void **)(v17 + 4), uArg3, 0, 0, -1, 1);  // 调 存 ★ PO 工厂分发器
      sub_484F40(pDwArg4, nArg5, v18, 1);  // 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
      fld_e34 = *(uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
      (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)fld_e34 + 52))(fld_e34, uArg3);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    }
  }
  sub_484D00(this);  // 槽汇总统计（累加各对象虚表 +36 值）
  sub_484D00(pDwArg4);  // 槽汇总统计（累加各对象虚表 +36 值）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x485510 sub_485510 —— 本地命令：装备技能装配（op 19 · 装备来源）
//   槽对象经 __RTDynamicCast 取 CNRDEquipment，未命中则改走本地玩家 dword_8F7C04 虚表 +792/788 从 pArg4 部位取装备。
//   与原对象不同则先虚表 +100 卸下旧装备，写回槽并 ·sub_484D00 汇总；场景 dword_8F7A24+12 == 3 且 pArg4 <= 9 时把技能 id 写入快捷栏表（·sub_429830 基址 + 4*pArg4 + 56）并通知 dword_8F7C08 虚表 +348 与 ·sub_5603E0。
// ------------------------------------------------------------
char /*userpurge*/ sub_485510@<al>(int *pDwArg1@<ecx>, int nArg2@<esi>, int nArg3, int pArg4)  // 实现：本地命令：装备技能装配（op 19 · 装备来源）
{
  int v5; // ecx
  int v7; // ecx
  int pObj2; // ebx
  int pObj; // esi
  int pObj3; // ebx
  void *v11; // eax
  void *v12; // eax
  int v13; // edi
  int v14; // eax
  int v16; // [esp+4h] [ebp-4h]

  v5 = pDwArg1[5];
  if ( v5 == 0 || (pDwArg1[6] - v5) >> 2 <= 0 )
    return 0;
  v7 = pDwArg1[5];
  if ( v7 != 0 && (pDwArg1[6] - v7) >> 2 != 0 && (pDwArg1[6] - pDwArg1[5]) >> 2 != 0 )
    pDwArg1[6] -= 4;
  pObj2 = dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
  if ( dword_8F7C04 == 0 || nArg3 >= pDwArg1[2] )  // 全局 dword_8F7C04 = 本机角色对象
    return 0;
  pObj = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
         *(uint32_t *)(pDwArg1[3] + 4 * nArg3),
         0,
         &IRDItem `RTTI Type Descriptor',
         &CNRDEquipment `RTTI Type Descriptor',
         0);
  if ( pObj == 0 && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 792))(pObj2, pArg4) == 0 )  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
    return 0;
  v16 = 0;
  if ( pObj != 0 )
  {
    pObj3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 784))(pObj2, pObj);  // 调虚槽 +784：IRDActiveObject__vmt310
    if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )  // 全局 dword_8F7A24 = 登录/选区管理器
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 100))(pObj);  // 调虚槽 +100：CNRDPrivateStoreWindow_Display__vmt64 槽（16 行）
  }
  else
  {
    if ( (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj2 + 792))(pObj2, pArg4, nArg2) != 0 )  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
      v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 788))(pObj2, pArg4);  // 调虚槽 +788：IRDActiveObject__vmt314
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 1080))(pObj2, pArg4);  // 调虚槽 +1080
    pObj3 = v16;
  }
  if ( pObj == pObj3 )
    return 0;
  if ( pObj != 0 )
  {
    v11 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 56))(pObj);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    sub_432EA0(v11, -1, 0, 0);  // 音效播放包装（非空判定）
  }
  else if ( pObj3 != 0 )
  {
    v12 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 56))(pObj3);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    sub_432EA0(v12, -1, 0, 0);  // 音效播放包装（非空判定）
  }
  *(uint32_t *)(pDwArg1[3] + 4 * nArg3) = pObj3;
  sub_484D00(pDwArg1);  // 槽汇总统计（累加各对象虚表 +36 值）
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 && pArg4 <= 9 )  // 全局 dword_8F7A24 = 登录/选区管理器
  {
    v13 = sub_429830((uint16_t)word_77F804) + 16;  // 结果 = 表按键查找（uint16）
    if ( pObj != 0 )
      v14 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 4);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
    else
      v14 = 0xFFFF;
    *(uint32_t *)(v13 + 4 * pArg4 + 56) = v14;
    if ( dword_8F7C08 != 0 )  // 副玩家/观战对象
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C08 + 348))(dword_8F7C08, v13);  // 调虚槽 +348：取坐标对象
    if ( *(uint32_t *)(*((uint32_t *)dword_8F8528 + 611) + 12) == 1 )  // 全局 dword_8F8528 = 消息/弹窗管理器
      sub_5603E0(v13);  // 商城对象更新（46C180/42B0F0/4939E0/41CBF0）
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4856E0 sub_4856E0 —— 本地命令：技能值置 1（卸下）
//   先弹队列尾项；槽有效时虚表 +44 剩余 <= 1 即整槽清空（·sub_484D50），否则虚表 +52 置 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_4856E0(int *this, int nArg2)  // 实现：本地命令：技能值置 1（卸下）
{
  int fld_e5; // ecx
  int fld_e3; // eax
  int fld_e32; // ecx

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 == 0 )  // fld_e5=this+20 nPage
    return 0;
  if ( (*(this + 6) - fld_e5) >> 2 <= 0 )  // this+24〔nPageMax(推断)〕
    return 0;
  *(this + 6) -= 4;  // this+24〔nPageMax(推断)〕
  if ( dword_8F7C04 == 0 )  // 全局 dword_8F7C04 = 本机角色对象
    return 0;
  if ( nArg2 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    return 0;
  fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
  if ( *(uint32_t *)(fld_e3 + 4 * nArg2) == 0 )  // fld_e3=this+12 nSkillRec12
    return 0;
  if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(fld_e3 + 4 * nArg2) + 44))(*(uint32_t *)(fld_e3 + 4 * nArg2)) <= 1 )  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 +…
  {
    sub_484D50(this, nArg2);  // 技能槽清空（按槽类型分流）
  }
  else
  {
    fld_e32 = *(uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e32 + 52))(fld_e32, 1);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x485790 sub_485790 —— 嵌入字符串与容器成员初始化
//   +1 与 +24..+72 区间标量清零；+8/+12/+16/+20 及 +76/+80 六处 std::string 置空串（·sub_41BFE0）；free +92 向量缓冲并把 +108..+116 清零。
// ------------------------------------------------------------
void /*thiscall*/ sub_485790(void *this)  // 实现：嵌入字符串与容器成员初始化
{
  void **pThis_1B; // edi
  void **i; // [esp+Ch] [ebp-4h]

  *((uint32_t *)this + 1) = 0;  // this+4〔宿主对象〕
  sub_41BFE0((void **)this + 2, szPassword);  // 驻留字符串设置（set(const char*)）
  sub_41BFE0((void **)this + 3, szPassword);  // 驻留字符串设置（set(const char*)）
  sub_41BFE0((void **)this + 4, szPassword);  // 驻留字符串设置（set(const char*)）
  sub_41BFE0((void **)this + 5, szPassword);  // 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 6) = 0;  // this+24〔nPageMax(推断)〕
  *((uint32_t *)this + 7) = 0;  // this+28〔pPanelVec(推断)〕
  *((uint8_t *)this + 32) = 0;  // this+32〔nHeight(推断)〕
  *((uint32_t *)this + 9) = 0;  // this+36〔nStateWord36(推断)〕
  *((uint32_t *)this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *((uint32_t *)this + 10) = 0;  // this+40〔bStateSub40(推断)〕
  *((uint32_t *)this + 11) = 0;  // this+44〔nExpireMs(推断)〕
  *((uint32_t *)this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *((uint32_t *)this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  *((uint32_t *)this + 15) = 0;  // this+60〔nFadeValue60(推断)〕
  *(uint32_t *)this = 0;  // *this = 0
  *((uint32_t *)this + 16) = 0;  // this+64〔apServerTabBtn(推断)〕
  *((uint32_t *)this + 17) = 0;  // this+68〔nCharCount(推断)〕
  *((uint32_t *)this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  sub_41BFE0((void **)this + 19, szPassword);  // 驻留字符串设置（set(const char*)）
  sub_41BFE0((void **)this + 20, szPassword);  // 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 21) = 0;  // this+84〔pFxObjA(推断)〕
  if ( *((uint32_t *)this + 23) != 0 )  // this+92〔pFxObjC(推断)〕
    j__free(*((void **)this + 23));  // 调 堆释放
  *((uint32_t *)this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  *((uint32_t *)this + 24) = 0;  // this+96〔nStatusMode(推断)〕
  *((uint32_t *)this + 25) = 0;  // this+100〔bEnchantDone(推断)〕
  pThis_1B = *((void ***)this + 27);  // pThis_1B=this+108 第 1 组·宿主属性 +886 增量
  if ( pThis_1B != nullptr )  // 若 pThis_1B 有效（非空）
  {
    for ( i = *((void ***)this + 28); pThis_1B != i; ++pThis_1B )  // this+28 【推断】逐帧驱动对象
      sub_41B010(pThis_1B);  // 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 27));  // 调 堆释放
  }
  *((uint32_t *)this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *((uint32_t *)this + 28) = 0;  // this+112〔pHostComp112〕
  *((uint32_t *)this + 29) = 0;  // this+116〔会话上下文〕
}



// ------------------------------------------------------------
// 0x485870 sub_485870 —— 子结构析构（字符串与向量族）
//   析构 +104 字符串（·sub_4017E0），free +92 缓冲（+96/+100 清零），再析构 +80/+76/+20/+16/+12/+8 六处字符串。
// ------------------------------------------------------------
void /*thiscall*/ sub_485870(int this)  // 实现：子结构析构（字符串与向量族）
{
  sub_4017E0(this + 104);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 92) != 0 )  // this+92〔pFxObjC(推断)〕等 2 字段
    j__free(*(void **)(this + 92));  // 释放 this+92〔pFxObjC(推断)〕堆块
  *(uint32_t *)(this + 92) = 0;  // this+92〔pFxObjC(推断)〕等 2 字段
  *(uint32_t *)(this + 96) = 0;  // this+96〔nStatusMode(推断)〕等 2 字段
  *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
  sub_41B010((void **)(this + 80));  // 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 76));  // 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 20));  // 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 16));  // 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 12));  // 驻留句柄析构（引用计数减到 0 释放）
  sub_41B010((void **)(this + 8));  // 驻留句柄析构（引用计数减到 0 释放）
}



// ------------------------------------------------------------
// 0x485920 sub_485920 —— IRDItem 析构（删除器与子类共用）
//   置 IRDItem 虚表、nullsub_3 后清 +132 的 clong 子对象（·sub_41A580），再经 ·sub_485870 清理 +8 起子结构。
// ------------------------------------------------------------
void /*thiscall*/ sub_485920(uint32_t *this)  // 实现：IRDItem 析构（删除器与子类共用）
{
  *this = &IRDItem::`vftable';  // 构造装配 vftable：IRDItem
  nullsub_3(this);
  sub_41A580(this + 33);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_485870((int)(this + 2));  // 子结构析构（字符串与向量族）
}



// ------------------------------------------------------------
// 0x485990 sub_485990 —— 整型字段写（+128）
//   直写 this+32（字节偏移 128）并回传参数。
// ------------------------------------------------------------
int /*thiscall*/ sub_485990(uint32_t *this, int nArg2)  // 实现：整型字段写（+128）
{
  *(this + 32) = nArg2;  // this+128〔szStatusKeyBuf(推断)〕
  return nArg2;
}



// ------------------------------------------------------------
// 0x4859B0 sub_4859B0 —— 判定：可用状态且 +12 == nArg2
//   先经虚表 +20(this, 1) 判定可用，再比对 +12 字段与参数是否相等。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4859B0(uint32_t *this, int nArg2)  // 判定：可用状态且 +12 == nArg2
{
  return (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 20))(this, 1) != 0 && *(this + 3) == nArg2;  // 虚调用 vt+20
}



// ------------------------------------------------------------
// 0x4859F0 sub_4859F0 —— 状态判定：+36 为 0 或（3 且 +40 非 0）
//   读 +36 状态字：为 0 直接通过；为 3 时还须 +40 字节标志非 0。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4859F0(int this)  // 状态判定：+36 为 0 或（3 且 +40 非 0）
{
  int nState; // eax  | +0x0024 → 物品状态字（0x4859F0: ==0 直通 / ==3 时须 +40 字节标志非 0）（IRDItem；va=004859F0）

  nState = *(uint32_t *)(this + 36);  // this+36〔nStateWord36(推断)〕等 2 字段
  return nState == 0 || nState == 3 && *(uint8_t *)(this + 40) != 0;  // this+40〔bStateSub40(推断)〕等 2 字段
}



// ------------------------------------------------------------
// 0x485A20 sub_485A20 —— 字节字段写（+146）
//   直写 this+146 字节标志并回传参数。
// ------------------------------------------------------------
char /*thiscall*/ sub_485A20(uint8_t *this, char pszArg2)  // 实现：字节字段写（+146）
{
  *(this + 146) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x485A40 sub_485A40 —— 判定：虚表 +124 计数 > 0
//   调用虚表 +124 取计数，返回值大于 0 即通过。
// ------------------------------------------------------------
bool /*thiscall*/ sub_485A40(void *this)  // 实现：判定：虚表 +124 计数 > 0
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this) > 0;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
}



// ------------------------------------------------------------
// 0x485A50 sub_485A50 —— 剩余时间：虚表 +116 到期值减当前时钟
//   虚表 +116 返回的到期时刻减去 ·sub_699000 读的全局时钟（unk_9B0C70），得剩余毫秒【推断：冷却或持续时间】。
// ------------------------------------------------------------
int /*thiscall*/ sub_485A50(void *this)  // 实现：剩余时间：虚表 +116 到期值减当前时钟
{
  int pThis_74; // esi

  pThis_74 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 116))(this);  // 调虚槽 +116：取伤害数值
  return pThis_74 - sub_699000((int)&unk_9B0C70);  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x485A70 sub_485A70 —— 值 = clong(+132) ×（+64 字段）
//   读 +132 的 clong 数值（·sub_41A5E0 防篡改取值）再乘 +16 字段。
// ------------------------------------------------------------
int /*thiscall*/ sub_485A70(uint32_t *this)  // 实现：值 = clong(+132) ×（+64 字段）
{
  return sub_41A5E0((unsigned int)(this + 33)) * *(this + 16);  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x485AA0 sub_485AA0 —— 增：虚表 +40(当前 clong 值 + nArg2)
//   与 ·0x485AD0 同构（差异：此处为加）。
// ------------------------------------------------------------
int /*thiscall*/ sub_485AA0(void *this, int nArg2)  // 实现：增：虚表 +40(当前 clong 值 + nArg2)
{
  int pThis_84; // eax

  pThis_84 = sub_41A5E0((unsigned int)this + 132);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 40))(this, nArg2 + pThis_84);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
}



// ------------------------------------------------------------
// 0x485AD0 sub_485AD0 —— 减：虚表 +40(当前 clong 值 - nArg2)
//   与 ·0x485AA0 同构（差异：此处为减）。
// ------------------------------------------------------------
int /*thiscall*/ sub_485AD0(void *this, int nArg2)  // 实现：减：虚表 +40(当前 clong 值 - nArg2)
{
  int pThis_84; // eax

  pThis_84 = sub_41A5E0((unsigned int)this + 132);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 40))(this, pThis_84 - nArg2);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
}



// ------------------------------------------------------------
// 0x485B00 sub_485B00 —— 取名字串（+84 · clong 保护字符串）
//   经 ·sub_41ACF0 取 this+21 处字符串内容并回传 const CHAR 指针。
// ------------------------------------------------------------
const CHAR */*thiscall*/ sub_485B00(unsigned int **this)  // 取名字串（+84 · clong 保护字符串）
{
  return sub_41ACF0(this + 21);  // 驻留串句柄 → 字符串指针
}



// ------------------------------------------------------------
// 0x485B10 sub_485B10 —— 取名字串（+16）
//   与 ·0x485B00 同构（差异：字符串字段位于 +16）。
// ------------------------------------------------------------
const CHAR */*thiscall*/ sub_485B10(unsigned int **this)  // 取名字串（+16）
{
  return sub_41ACF0(this + 4);  // 驻留串句柄 → 字符串指针
}



// ------------------------------------------------------------
// 0x485B20 sub_485B20 —— IRDItem 删除器（析构后按位释放）
//   调 ·sub_485920 析构，pszArg2 位 0 置位时 free 对象块。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_485B20(uint32_t *Block, char pszArg2)  // IRDItem 删除器（析构后按位释放）
{
  sub_485920(Block);  // IRDItem 析构（删除器与子类共用）
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x485B50 sub_485B50 —— CNRDStackable 析构
//   置 CNRDStackable 虚表、nullsub_3，再经 ·sub_485920 走 IRDItem 基类清理。
// ------------------------------------------------------------
void /*thiscall*/ sub_485B50(uint32_t *this)  // 实现：CNRDStackable 析构
{
  *this = &CNRDStackable::`vftable';  // 构造装配 vftable：CNRDStackable
  nullsub_3(this);
  sub_485920(this);  // IRDItem 析构（删除器与子类共用）
}



// ------------------------------------------------------------
// 0x485BA0 sub_485BA0 —— 复制 4 个 dword 到 +148（16 字节区）
//   把 pArg2 的前四个 dword 逐个写入 this+37 起（字节偏移 148），回传末字段。
// ------------------------------------------------------------
int /*thiscall*/ sub_485BA0(uint32_t *this, uint32_t *pArg2)  // 实现：复制 4 个 dword 到 +148（16 字节区）
{
  uint32_t *pThis_25; // ecx
  int result; // eax

  pThis_25 = this + 37;  // this+37〔bFadeFlag37〕
  *pThis_25 = *pArg2;  // pThis_25=this+37 bFadeFlag37
  pThis_25[1] = pArg2[1];  // pThis_25[1] = 取 pArg2[1]
  pThis_25[2] = pArg2[2];  // pThis_25[2] = 取 pArg2[2]
  result = pArg2[3];
  pThis_25[3] = result;  // pThis_25=this+37 bFadeFlag37
  return result;
}



// ------------------------------------------------------------
// 0x485BD0 sub_485BD0 —— CNRDStackable 删除器
//   与 ·0x485B20 同构（差异：析构走 ·sub_485B50）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_485BD0(uint32_t *Block, char pszArg2)  // CNRDStackable 删除器
{
  sub_485B50(Block);  // CNRDStackable 析构
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x485C00 sub_485C00 —— IRDItem 复合构造（字符串/向量/标量清零 + ·sub_485790）
//   this+8/+12/+16/+20 与 +76/+80 六处 string 置空；+92..+100 向量与 +108..+116 标量清零，末尾 ·sub_485790 初始化剩余成员。
// ------------------------------------------------------------
int /*thiscall*/ sub_485C00(int this)  // 实现：IRDItem 复合构造（字符串/向量/标量清零 + ·sub_485790）
{
  void **pThis_8; // ecx

  pThis_8 = (void **)(this + 8);  // this+32〔nHeight(推断)〕
  *pThis_8 = nullptr;  // pThis_8=this+32 nHeight
  sub_41BFE0(pThis_8, szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
  sub_41BFE0((void **)(this + 12), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  sub_41BFE0((void **)(this + 16), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 20) = 0;  // this+20〔nPage(推断)〕等 2 字段
  sub_41BFE0((void **)(this + 20), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 76) = 0;  // this+76〔pBtnActionE〕
  sub_41BFE0((void **)(this + 76), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  sub_41BFE0((void **)(this + 80), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 92) = 0;  // this+92〔pFxObjC(推断)〕等 2 字段
  *(uint32_t *)(this + 96) = 0;  // this+96〔nStatusMode(推断)〕等 2 字段
  *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 116) = 0;  // this+116〔会话上下文〕
  sub_485790((void *)this);  // 嵌入字符串与容器成员初始化
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x485CC0 sub_485CC0 —— IRDItem 核心构造（+132 转 clong 子对象）
//   置 IRDItem 虚表，·sub_485C00 初始化各成员，再经 ·sub_41A630 释放后把 +132 重挂 clong 虚表并 ·sub_4F2BE0。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_485CC0(uint32_t *this)  // IRDItem 核心构造（+132 转 clong 子对象）
{
  *this = &IRDItem::`vftable';  // 构造装配 vftable：IRDItem
  sub_485C00((int)(this + 2));  // IRDItem 复合构造（字符串/向量/标量清零 + ·sub_485790）
  sub_41A630((unsigned int)(this + 33));  // this+33〔bJobVecDirty〕
  *(this + 33) = &clong::`vftable';  // 构造装配 vftable：clong
  sub_4F2BE0(this);
  nullsub_3(this);
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x485D30 sub_485D30 —— CNRDStackable 构造（+148=8 · +152=-1）
//   先 ·sub_485CC0 构造 IRDItem 基类，改写 CNRDStackable 虚表；+148=8、+152=-1、+156=0、+160=0 后调用 ·sub_577FF0。
// ------------------------------------------------------------
int /*thiscall*/ sub_485D30(int this)  // 实现：CNRDStackable 构造（+148=8 · +152=-1）
{
  sub_485CC0((uint32_t *)this);  // IRDItem 核心构造（+132 转 clong 子对象）
  *(uint32_t *)this = &CNRDStackable::`vftable';  // 构造装配 vftable：CNRDStackable
  *(uint32_t *)(this + 148) = 8;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 152) = -1;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 156) = 0;  // this+156〔nAdd156(推断)〕
  *(uint8_t *)(this + 160) = 0;  // this+160〔fAdd160(推断)〕
  sub_577FF0(this);  // 10 行小函数
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x485DA0 sub_485DA0 —— CNRDMoney 构造（金币掉落物）
//   ·sub_485D30 构造基类后改挂 CNRDMoney 虚表，nullsub_3，并 ·sub_578680(nArg2) 初始化金币掉落表现资源（Item/FieldImage）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_485DA0(uint32_t *this, int nArg2)  // CNRDMoney 构造（金币掉落物）
{
  sub_485D30((int)this);  // CNRDStackable 构造（+148=8 · +152=-1）
  *this = &CNRDMoney::`vftable';  // 构造装配 vftable：CNRDMoney
  nullsub_3(this);
  sub_578680(nArg2);  // 金币掉落绘制：资源 Item/FieldImage.img，事件标签 GOLD_DROP1/
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x485E00 sub_485E00 —— CNRDMoney 删除器
//   与 ·0x485B20 同构（差异：析构走 ·sub_485E30）。
// ------------------------------------------------------------
void */*thiscall*/ sub_485E00(void *Block, char pszArg2)  // CNRDMoney 删除器
{
  sub_485E30();  // CNRDMoney 析构
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x485E30 sub_485E30 —— CNRDMoney 析构
//   置 CNRDMoney 虚表、nullsub_3，再经 ·sub_485B50 走 CNRDStackable 基类清理。
// ------------------------------------------------------------
void /*thiscall*/ sub_485E30(uint32_t *this)  // 实现：CNRDMoney 析构
{
  *this = &CNRDMoney::`vftable';  // 构造装配 vftable：CNRDMoney
  nullsub_3(this);
  sub_485B50(this);  // CNRDStackable 析构
}



// ------------------------------------------------------------
// 0x485E80 sub_485E80 —— 技能槽数组分配与默认填充
//   this[0] = Block、this[2] = nArg3、this[3] = new 4*nArg3 并逐项清零。
//   Block 为 0 或 4 时预置前 3 个默认槽：CNRDMoney 实例（·sub_485D30）与 ·sub_522300(1)/(2) 两个对象。
// ------------------------------------------------------------
int /*thiscall*/ sub_485E80(uint32_t *this, void *Block, int nArg3)  // 实现：技能槽数组分配与默认填充
{
  int result; // eax
  uint32_t *pMem; // eax
  uint32_t *pMem2; // edi

  *this = Block;
  *(this + 2) = nArg3;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = operator new(4 * nArg3);  // this+12〔nSkillRec12(推断)〕
  for ( result = 0; result < nArg3; ++result )
    *(uint32_t *)(*(this + 3) + 4 * result) = 0;  // this+12〔nSkillRec12(推断)〕
  if ( Block == nullptr || Block == (void *)4 )
  {
    pMem = operator new(0xA4u);  // 堆分配 164 字节对象
    pMem2 = pMem;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
    {
      sub_485D30((int)pMem);  // CNRDStackable 构造（+148=8 · +152=-1）
      *pMem2 = &CNRDMoney::`vftable';  // 构造装配 vftable：CNRDMoney
      nullsub_3(pMem2);
      sub_578680(0);  // 金币掉落绘制：资源 Item/FieldImage.img，事件标签 GOLD_DROP1/
    }
    else
    {
      pMem2 = nullptr;
    }
    *(uint32_t *)*(this + 3) = pMem2;  // this+12〔nSkillRec12(推断)〕
    *(uint32_t *)(*(this + 3) + 4) = sub_522300((void *)1, 0, 0, 0, -1, 1);  // 调 存 ★ PO 工厂分发器
    result = sub_522300((void *)2, 0, 0, 0, -1, 1);  // 调 存 ★ PO 工厂分发器
    *(uint32_t *)(*(this + 3) + 8) = result;  // this+12〔nSkillRec12(推断)〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x485F70 sub_485F70 —— 技能槽记录深拷贝
//   把 pArg2 起的记录拷入 this+8：+0/+4 标量与 +8..+84 各字段直接赋值，字符串区经 ·sub_41B0D0 深拷贝，+88 与 +104 两子容器经 ·sub_4ED3F0 与 ·sub_41DC80 复制。
// ------------------------------------------------------------
int /*thiscall*/ sub_485F70(int this, int pArg2)  // 实现：技能槽记录深拷贝
{
  int pThis_8; // esi
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  pThis_8 = this + 8;  // this+8 物品 id
  *(uint32_t *)(this + 8) = *(uint32_t *)pArg2;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 12) = *(uint32_t *)(pArg2 + 4);  // this+12〔nSkillRec12(推断)〕等 2 字段
  sub_41B0D0((unsigned int **)(this + 16), (unsigned int **)(pArg2 + 8));  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0((unsigned int **)(pThis_8 + 12), (unsigned int **)(pArg2 + 12));  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0((unsigned int **)(pThis_8 + 16), (unsigned int **)(pArg2 + 16));  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0((unsigned int **)(pThis_8 + 20), (unsigned int **)(pArg2 + 20));  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(uint32_t *)(pThis_8 + 24) = *(uint32_t *)(pArg2 + 24);  // pThis_8+24〔nPageMax(推断)〕
  *(uint32_t *)(pThis_8 + 28) = *(uint32_t *)(pArg2 + 28);  // pThis_8+28〔pPanelVec(推断)〕
  *(uint8_t *)(pThis_8 + 32) = *(uint8_t *)(pArg2 + 32);  // pThis_8+32〔nHeight(推断)〕
  *(uint32_t *)(pThis_8 + 36) = *(uint32_t *)(pArg2 + 36);  // pThis_8+36〔nStateWord36(推断)〕
  *(uint32_t *)(pThis_8 + 40) = *(uint32_t *)(pArg2 + 40);  // pThis_8+40〔bStateSub40(推断)〕
  *(uint32_t *)(pThis_8 + 44) = *(uint32_t *)(pArg2 + 44);  // pThis_8+44〔nExpireMs(推断)〕
  *(uint32_t *)(pThis_8 + 48) = *(uint32_t *)(pArg2 + 48);  // pThis_8+48〔pCmdVecBegin48(推断)〕
  *(uint32_t *)(pThis_8 + 52) = *(uint32_t *)(pArg2 + 52);  // pThis_8+52〔bAuraState(推断)〕
  *(uint32_t *)(pThis_8 + 56) = *(uint32_t *)(pArg2 + 56);  // pThis_8+56〔pCmdVecCap56(推断)〕
  *(uint8_t *)(pThis_8 + 60) = *(uint8_t *)(pArg2 + 60);  // pThis_8+60〔nFadeValue60(推断)〕
  *(uint8_t *)(pThis_8 + 61) = *(uint8_t *)(pArg2 + 61);  // pThis_8+61〔bReadyFlagA(推断)〕
  *(uint8_t *)(pThis_8 + 62) = *(uint8_t *)(pArg2 + 62);  // pThis_8+62〔bReadyFlagB(推断)〕
  *(uint8_t *)(pThis_8 + 63) = *(uint8_t *)(pArg2 + 63);  // pThis_8=this+8 nItemId
  *(uint32_t *)(pThis_8 + 64) = *(uint32_t *)(pArg2 + 64);  // pThis_8+64〔apServerTabBtn(推断)〕
  *(uint32_t *)(pThis_8 + 68) = *(uint32_t *)(pArg2 + 68);  // pThis_8+68〔nCharCount(推断)〕
  *(uint32_t *)(pThis_8 + 72) = *(uint32_t *)(pArg2 + 72);  // pThis_8+72〔nSnapshot72(推断)〕
  sub_41B0D0((unsigned int **)(pThis_8 + 76), (unsigned int **)(pArg2 + 76));  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0((unsigned int **)(pThis_8 + 80), (unsigned int **)(pArg2 + 80));  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(uint32_t *)(pThis_8 + 84) = *(uint32_t *)(pArg2 + 84);  // pThis_8+84〔pFxObjA(推断)〕
  sub_4ED3F0(pThis_8 + 88, pArg2 + 88);  // int 向量拷贝赋值（全容量路径）
  sub_41DC80(pThis_8 + 104, pArg2 + 104);  // vector<T 4B 驻留句柄> 拷贝赋值 operator=
  return pThis_8;  // pThis_8=this+8 nItemId
}



// ------------------------------------------------------------
// 0x486070 sub_486070 —— 请求 op 18：单槽技能值设置
//   前置：等待队列空、槽对象存在且虚表 +44 >= uArg3、全局占用字 dword_8F8538+4 为 0xFFFF；包体 = 模式字节 + 1 + nArg4 2 字节 + 槽号 2 字节 + 值 4 字节。
//   提交后压入本地命令 0（·sub_484880），调试机 byte_77F280 置位时本地先行 ·sub_4850B0。
// ------------------------------------------------------------
char /*thiscall*/ sub_486070(int *this, int nArg2, unsigned int uArg3, int nArg4)  // 实现：请求 op 18：单槽技能值设置
{
  int fld_e5; // ecx
  int nArg22; // edi
  int fld_e3; // eax
  unsigned int v9; // eax
  unsigned int uArg32; // ebx

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 && (*(this + 6) - fld_e5) >> 2 >= 1 )  // this+24〔nPageMax(推断)〕
    return 0;
  nArg22 = nArg2;
  if ( nArg2 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    return 0;
  fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
  if ( *(uint32_t *)(fld_e3 + 4 * nArg2) == 0 )  // fld_e3=this+12 nSkillRec12
    return 0;
  v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(fld_e3 + 4 * nArg2) + 44))(*(uint32_t *)(fld_e3 + 4 * nArg2));  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 +…
  uArg32 = uArg3;
  if ( v9 < uArg3 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  sub_423200(dword_8F7B08, 18);  // 【发送网络包API】
  HIBYTE(nArg2) = *(uint8_t *)this;
  sub_423290((char *)&nArg2 + 3, 1);  // 调 写 4B 长度
  HIBYTE(nArg2) = 1;
  sub_423290((char *)&nArg2 + 3, 1);  // 调 写 4B 长度
  nArg2 = nArg4;
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  nArg2 = nArg22;
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  nArg2 = uArg32;
  sub_423290(&nArg2, 4);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  sub_484880(this, 0);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  if ( byte_77F280 != 0 )  // 调试机标志(DebugConfig.txt 校验)
    sub_4850B0(this, nArg22, uArg32);  // 本地命令 0 执行：槽值设置或扣减（op 18）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x486190 sub_486190 —— 请求 op 18 批量版（槽数组）
//   pArg2 为 8 字节项数组（u16 槽号 + u16 + u32 值），逐项校验槽存在且虚表 +44 >= 值，任一失败即整批拒绝。
//   包体 = 模式字节 + 条目数 + 每项 2/2/4 字节；提交后压入本地命令 0，调试机时本地先行 ·sub_485150。
// ------------------------------------------------------------
char /*thiscall*/ sub_486190(int *this, int pArg2, int nArg3)  // 实现：请求 op 18 批量版（槽数组）
{
  int *pThis; // ebx
  int fld_e5; // ecx
  int pArg22; // edi
  int *v7; // esi
  int v8; // eax
  unsigned int v9; // ebx
  int v10; // edx
  int v11; // eax
  uint16_t *v12; // esi
  int nArg32; // ebx
  int v14; // edx
  unsigned int v15; // ecx
  uint32_t *v16; // eax
  int *pThis2; // [esp+4h] [ebp-4h]

  pThis = this;
  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  pThis2 = pThis;
  if ( fld_e5 != 0 && (pThis[6] - fld_e5) >> 2 >= 1 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  pArg22 = pArg2;
  v7 = *(int **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v7 == *(int **)(pArg2 + 8) )  // pArg2+8〔nSkillRec8(推断)〕
  {
LABEL_11:
    sub_423200(dword_8F7B08, 18);  // 【发送网络包API】
    HIBYTE(pArg2) = *(uint8_t *)pThis;
    sub_423290((char *)&pArg2 + 3, 1);  // 调 写 4B 长度
    v11 = *(uint32_t *)(pArg22 + 4);  // pArg22+4〔宿主对象〕
    if ( v11 != 0 )
      HIBYTE(pArg2) = (*(uint32_t *)(pArg22 + 8) - v11) >> 3;  // pArg22+8〔nSkillRec8(推断)〕
    else
      HIBYTE(pArg2) = 0;
    sub_423290((char *)&pArg2 + 3, 1);  // 调 写 4B 长度
    v12 = *(uint16_t **)(pArg22 + 4);  // pArg22+4〔宿主对象〕
    if ( v12 != *(uint16_t **)(pArg22 + 8) )  // pArg22+8〔nSkillRec8(推断)〕
    {
      nArg32 = nArg3;
      do
      {
        pArg2 = nArg32;
        sub_423290(&pArg2, 2);  // 调 写 4B 长度
        pArg2 = *v12;
        sub_423290(&pArg2, 2);  // 调 写 4B 长度
        pArg2 = *((uint32_t *)v12 + 1);
        sub_423290(&pArg2, 4);  // 调 写 4B 长度
        v12 += 4;
      }
      while ( v12 != *(uint16_t **)(pArg22 + 8) );  // pArg22+8〔nSkillRec8(推断)〕
      pThis = pThis2;
    }
    sub_423380(dword_8F7B08);  // 发包提交：Commit()
    v14 = pThis[5];
    pArg2 = 0;
    if ( v14 != 0 )
      v15 = (pThis[6] - v14) >> 2;
    else
      v15 = 0;
    if ( v14 != 0 && v15 < (pThis[7] - v14) >> 2 )
    {
      v16 = (uint32_t *)pThis[6];
      *v16 = 0;
      pThis[6] = (int)(v16 + 1);
    }
    else
    {
      sub_430C80((void *)pThis[6], 1, (int)&pArg2);  // uint32 vector 区间插入（同值填充）
    }
    if ( byte_77F280 != 0 )  // 调试机标志(DebugConfig.txt 校验)
      sub_485150(pThis, pArg22);  // 本地命令 0 批量执行（op 18 槽数组）
    return 1;  // 返回 1(成功)
  }
  else
  {
    while ( 1 )
    {
      v8 = *v7;
      if ( *v7 >= pThis2[2] )
        return 0;
      v10 = pThis2[3];
      if ( *(uint32_t *)(v10 + 4 * v8) == 0 )
        return 0;
      v9 = v7[1];
      if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v10 + 4 * v8) + 44))(*(uint32_t *)(v10 + 4 * v8)) < v9 )  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 +…
        return 0;
      v7 += 2;
      if ( v7 == *(int **)(pArg22 + 8) )  // pArg22+8〔nSkillRec8(推断)〕
      {
        pThis = pThis2;
        goto LABEL_11;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x486330 sub_486330 —— 请求 op 50（含本地玩家两字段）【推断：宠物/召唤或技能升阶】
//   前置：本地玩家 dword_8F7C04 虚表 +80 通过且 *this == 0；包体 = 玩家虚表 +120、+124 各 2 字节 + 模式字节 + 槽号 2 + 值 4；压入本地命令 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_486330(uint32_t *this, signed int nArg2, unsigned int uArg3)  // 实现：请求 op 50（含本地玩家两字段）(推断：宠物/召唤或技能升阶)
{
  int fld_e5; // ecx
  int fld_e3; // ecx
  unsigned int v6; // eax
  int pObj; // edi
  int v9; // [esp+4h] [ebp-8h] BYREF
  char v10[4]; // [esp+8h] [ebp-4h] BYREF

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 && (*(this + 6) - fld_e5) >> 2 >= 1 )  // this+24〔nPageMax(推断)〕
    return 0;
  if ( nArg2 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    return 0;
  fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
  if ( *(uint32_t *)(fld_e3 + 4 * nArg2) == 0 )  // fld_e3=this+12 nSkillRec12
    return 0;
  v6 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(fld_e3 + 4 * nArg2) + 44))(*(uint32_t *)(fld_e3 + 4 * nArg2));  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 +…
  if ( v6 < uArg3 )
    return 0;
  pObj = dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
  if ( dword_8F7C04 == 0  // 全局 dword_8F7C04 = 本机角色对象
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 80))(dword_8F7C04) == 0  // 全局 dword_8F7C04 = 本机角色对象
    || *this != 0
    || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
  {
    return 0;
  }
  sub_423200(dword_8F7B08, 50);  // 【发送网络包API】
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调虚槽 +120：动画对象
  sub_423290(&v9, 2);  // 调 写 4B 长度
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  sub_423290(&v9, 2);  // 调 写 4B 长度
  v10[0] = *(uint8_t *)this;
  sub_423290(v10, 1);  // 调 写 4B 长度
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  nArg2 = uArg3;
  sub_423290(&nArg2, 4);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  sub_484880(this, 1);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x486470 sub_486470 —— 请求 op 46（掉落表现校验后开关槽对象）
//   需 ·sub_429830(会话索引 word_77F804)+4 经 ·sub_5788B0 掉落物表现校验通过；包体 2 字节对象虚表 +52 值；随后置对象 +977 = 1 并压入本地命令 2。
// ------------------------------------------------------------
char /*thiscall*/ sub_486470(uint32_t *this, int nArg2)  // 实现：请求 op 46（掉落表现校验后开关槽对象）
{
  int fld_e5; // ecx
  uint8_t *pObj; // esi
  int v6; // eax

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 && (*(this + 6) - fld_e5) >> 2 >= 1 )  // this+24〔nPageMax(推断)〕
    return 0;
  pObj = (uint8_t *)nArg2;
  if ( nArg2 == 0 )
    return 0;
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  v6 = sub_429830((uint16_t)word_77F804);  // 结果 = 表按键查找（uint16）
  if ( (uint8_t)sub_5788B0(*(uint16_t *)(v6 + 4)) == 0 )  // 掉落物表现（41A5E0/422E70/43BEE0）
    return 0;
  sub_423200(dword_8F7B08, 46);  // 【发送网络包API】
  nArg2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 52))(pObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  pObj[977] = 1;
  sub_484880(this, 2);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x486530 sub_486530 —— 请求 op 19：两槽交换
//   前置：等待队列深度 < nArg4 且尾项 == 3、两槽至少一个非空、dword_8F7C08+648 子对象 +284/+285 标志为 0；包体 = 模式 + 槽A 2 + 0 4 字节 + 模式 + 槽B 2；压入本地命令 3。
// ------------------------------------------------------------
char /*thiscall*/ sub_486530(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：请求 op 19：两槽交换
{
  int fld_e5; // ecx
  int fld_e6; // eax
  int fld_e52; // ecx
  int fld_e2; // eax
  int fld_e3; // eax
  int v11; // eax

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 )  // fld_e5=this+20 nPage
    fld_e6 = (*(this + 6) - fld_e5) >> 2;  // this+24〔nPageMax(推断)〕
  else
    fld_e6 = 0;  // fld_e6=this+24 nPageMax
  if ( fld_e6 >= nArg4 )  // fld_e6=this+24 nPageMax
    return 0;
  fld_e52 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e52 != 0 && (*(this + 6) - fld_e52) >> 2 >= 1 && ((*(this + 6) - fld_e52) >> 2 == 0 || *(uint32_t *)(*(this + 6) - 4) != 3) )  // this+24〔nPageMax(推断)〕
    return 0;
  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( nArg2 >= fld_e2 )  // fld_e2=this+8 nSkillRec8
    return 0;
  if ( nArg3 >= fld_e2 )  // fld_e2=this+8 nSkillRec8
    return 0;
  fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
  if ( *(uint32_t *)(fld_e3 + 4 * nArg2) == 0 && *(uint32_t *)(fld_e3 + 4 * nArg3) == 0 )  // fld_e3=this+12 nSkillRec12
    return 0;
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  v11 = *(uint32_t *)(dword_8F7C08 + 648);  // 副玩家/观战对象
  if ( v11 != 0 && *(uint8_t *)(v11 + 284) != 0 && *(uint8_t *)(v11 + 285) != 0 )
    return 0;
  sub_423200(dword_8F7B08, 19);  // 【发送网络包API】
  HIBYTE(nArg4) = *(uint8_t *)this;
  sub_423290((char *)&nArg4 + 3, 1);  // 调 写 4B 长度
  nArg4 = nArg2;
  sub_423290(&nArg4, 2);  // 调 写 4B 长度
  nArg4 = 0;
  sub_423290(&nArg4, 4);  // 调 写 4B 长度
  HIBYTE(nArg4) = *(uint8_t *)this;
  sub_423290((char *)&nArg4 + 3, 1);  // 调 写 4B 长度
  nArg4 = nArg3;
  sub_423290(&nArg4, 2);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  sub_484880(this, 3);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x486690 sub_486690 —— 连续两次 op 19 交换（三槽轮换）
//   先以深度 1 交换 nArg2 与 nArg3，成功后以深度 2 交换 nArg3 与 nArg4，任一失败即返回。
// ------------------------------------------------------------
char /*thiscall*/ sub_486690(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：连续两次 op 19 交换（三槽轮换）
{
  char result; // al

  result = sub_486530(this, nArg2, nArg3, 1);  // 结果 = 请求 op 19：两槽交换
  if ( result != 0 )  // 若结果非 0（成功）
    return sub_486530(this, nArg3, nArg4, 2) != 0;  // 请求 op 19：两槽交换
  return result;
}



// ------------------------------------------------------------
// 0x4866D0 sub_4866D0 —— 请求 op 19 带来源对象（等级 + 来源容器）
//   两个容器等待队列须空且槽虚表 +44 >= uArg3；包体 = 模式 + 槽号 2 + 值 4 + 来源模式字节 + 源下标 2；本对象与来源容器各压入本地命令 4。
// ------------------------------------------------------------
char /*thiscall*/ sub_4866D0(uint32_t *this, int nArg2, unsigned int uArg3, uint32_t *pArg4, signed int nArg5)  // 实现：请求 op 19 带来源对象（等级 + 来源容器）
{
  int fld_e5; // ecx
  uint32_t *pArg42; // edi
  int v8; // ecx
  int fld_e3; // ecx
  unsigned int v10; // eax
  int v12; // eax

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 && (*(this + 6) - fld_e5) >> 2 >= 1 )  // this+24〔nPageMax(推断)〕
    return 0;
  pArg42 = pArg4;
  v8 = pArg4[5];
  if ( v8 != 0 && (pArg4[6] - v8) >> 2 >= 1 )
    return 0;
  if ( nArg2 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    return 0;
  if ( nArg5 >= pArg4[2] )
    return 0;
  fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
  if ( *(uint32_t *)(fld_e3 + 4 * nArg2) != 0 )  // fld_e3=this+12 nSkillRec12
  {
    v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(fld_e3 + 4 * nArg2) + 44))(*(uint32_t *)(fld_e3 + 4 * nArg2));  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 +…
    if ( v10 < uArg3 )
      return 0;
  }
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  v12 = *(uint32_t *)(dword_8F7C08 + 648);  // 副玩家/观战对象
  if ( v12 != 0 && *(uint8_t *)(v12 + 284) != 0 && *(uint8_t *)(v12 + 285) != 0 )
    return 0;
  sub_423200(dword_8F7B08, 19);  // 【发送网络包API】
  HIBYTE(pArg4) = *(uint8_t *)this;
  sub_423290((char *)&pArg4 + 3, 1);  // 调 写 4B 长度
  pArg4 = (uint32_t *)nArg2;
  sub_423290(&pArg4, 2);  // 调 写 4B 长度
  sub_423290(&uArg3, 4);  // 调 写 4B 长度
  HIBYTE(uArg3) = *(uint8_t *)pArg42;
  sub_423290((char *)&uArg3 + 3, 1);  // 调 写 4B 长度
  uArg3 = nArg5;
  sub_423290(&uArg3, 2);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  sub_484880(this, 4);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  sub_484880(pArg42, 4);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x486820 sub_486820 —— 施放拒绝提示（ALERT_1 音效 + sub_485510）
// ------------------------------------------------------------
char /*thiscall*/ sub_486820(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：施放拒绝提示（ALERT_1 音效 + sub_485510）
{
  int fld_e5; // ecx
  int fld_e6; // eax
  int fld_e52; // ecx
  int v8; // eax
  uint8_t *fld_e3; // eax
  int pObj2; // ebx
  uint32_t *v12; // eax
  int nArg32; // edi
  int pObj; // eax
  int v15; // edx
  uint32_t *v16; // esi
  int v17; // eax
  uint32_t *v18; // esi
  int v19; // eax
  int v20; // esi
  int v21; // eax
  uint8_t *fld_e32; // [esp+4h] [ebp-4h]

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 )  // fld_e5=this+20 nPage
    fld_e6 = (*(this + 6) - fld_e5) >> 2;  // this+24〔nPageMax(推断)〕
  else
    fld_e6 = 0;  // fld_e6=this+24 nPageMax
  if ( fld_e6 >= nArg4 )  // fld_e6=this+24 nPageMax
    return 0;
  fld_e52 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e52 != 0 && (*(this + 6) - fld_e52) >> 2 >= 1 && ((*(this + 6) - fld_e52) >> 2 == 0 || *(uint32_t *)(*(this + 6) - 4) != 7) )  // this+24〔nPageMax(推断)〕
    return 0;
  nArg4 = dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
  if ( dword_8F7C04 == 0 )  // 全局 dword_8F7C04 = 本机角色对象
    return 0;
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  v8 = *(uint32_t *)(dword_8F7C08 + 648);  // 副玩家/观战对象
  if ( v8 != 0 && *(uint8_t *)(v8 + 284) != 0 && *(uint8_t *)(v8 + 285) != 0 )
    return 0;
  if ( nArg2 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    return 0;
  fld_e3 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
          *(uint32_t **)(*(this + 3) + 4 * nArg2),  // this+12 = 技能槽记录次字
          0,
          &IRDItem `RTTI Type Descriptor',
          &CNRDEquipment `RTTI Type Descriptor',
          0);
  pObj2 = (int)fld_e3;
  if ( fld_e3 != nullptr )  // 若 fld_e3 有效（非空）
  {
    fld_e32 = fld_e3;
    v12 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)fld_e3 + 172))(fld_e3);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
    nArg32 = nArg3;
    if ( *v12 != nArg3 || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg4 + 804))(nArg4, pObj2) == 0 )  // 调虚槽 +804：★ 装备可用性检查（含 CNRDEquipment RTTI 直证）
      return 0;
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 32) != 0 )  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
    {
      sub_44E8D0((char *)dword_8F8528, (void *)0x19, pObj2, 0);  // 对象池借出（按池号取可用对象）
      return 1;  // 返回 1(成功)
    }
    pObj = (int)fld_e32;
  }
  else
  {
    if ( *(uint32_t *)(*(this + 3) + 4 * nArg2) != 0 )  // this+12〔nSkillRec12(推断)〕
      return 0;
    nArg32 = nArg3;
    if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg4 + 792))(nArg4, nArg3) == 0 )  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
      return 0;
    pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg4 + 792))(nArg4, nArg32);  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
  }
  if ( pObj == 0 )
    return 0;
  v15 = *(uint32_t *)(dword_8F7A24 + 12);  // 全局 dword_8F7A24 = 登录/选区管理器
  if ( v15 != 3 && v15 != 4 && v15 != 6 )  // 若 v15 != 3 与/或 v15 != 4 与/或 v15 != 6
    goto LABEL_35;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 104))(pObj) != 0 )  // 调虚槽 +104：CNRDPrivateStoreWindow_Display__vmt68 页绘制（114 …
  {
    v16 = *((uint32_t **)dword_8F8528 + 7);  // 全局 dword_8F8528 = 消息/弹窗管理器
    v17 = sub_422E70(414);  // 调 存 CStringManager::getStr 取本地化串
    sub_43BEE0(v16, v17, -6567706, 0, -1);  // 调 播报 + 面板刷新 ──
    sub_432EA0("ALERT_1", -1, 0, 0);  // 字符串 “ALERT_1”
    return 0;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg4 + 1100))(nArg4, nArg32) == 0 )  // 调虚槽 +1100
  {
    v18 = *((uint32_t **)dword_8F8528 + 7);  // 全局 dword_8F8528 = 消息/弹窗管理器
    v19 = sub_422E70(415);  // 调 存 CStringManager::getStr 取本地化串
    sub_43BEE0(v18, v19, -6567706, 0, -1);  // 调 播报 + 面板刷新 ──
    return 0;
  }
  else
  {
LABEL_35:
    sub_423200(dword_8F7B08, 19);  // 【发送网络包API】
    HIBYTE(nArg3) = *(uint8_t *)this;
    sub_423290((char *)&nArg3 + 3, 1);  // 调 写 4B 长度
    nArg3 = nArg2;
    sub_423290(&nArg3, 2);  // 调 写 4B 长度
    nArg3 = 1;
    sub_423290(&nArg3, 4);  // 调 写 4B 长度
    HIBYTE(nArg3) = 3;
    sub_423290((char *)&nArg3 + 3, 1);  // 调 写 4B 长度
    nArg3 = nArg32;
    sub_423290(&nArg3, 2);  // 调 写 4B 长度
    sub_423380(dword_8F7B08);  // 发包提交：Commit()
    sub_484880(7);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
    if ( byte_77F280 != 0 )  // 调试机标志(DebugConfig.txt 校验)
    {
      sub_485510(nArg2, nArg32);  // 本地命令：装备技能装配（op 19 · 装备来源）
      if ( nArg32 <= 9 )
      {
        if ( pObj2 != 0 )
          v20 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 4);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
        else
          v20 = 0xFFFF;
        *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 4 * nArg32 + 72) = v20;  // 表按键查找（uint16）
        if ( dword_8F7C08 != 0 )  // 副玩家/观战对象
        {
          v21 = sub_429830((uint16_t)word_77F804);  // 结果 = 表按键查找（uint16）
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C08 + 348))(dword_8F7C08, v21 + 16);  // 调虚槽 +348：取坐标对象
        }
      }
    }
    return 1;  // 返回 1(成功)
  }
}


// ------------------------------------------------------------
// 0x486B40 sub_486B40 —— 请求 op 47（使用槽对象）
//   调试机 byte_77F280 置位时跳过发包，直接由本地玩家虚表 +864 同步对象 id（取对象虚表 +16 → +4）。
//   否则前置队列空、槽/场景就绪后发 47 + 2 字节槽号，再以本地玩家虚表 +864 同步该对象 id，并压入本地命令 8。
// ------------------------------------------------------------
char /*thiscall*/ sub_486B40(uint32_t *this, int nArg2, int nArg3)  // 实现：请求 op 47（使用槽对象）
{
  int fld_e3; // ecx
  int v5; // eax
  int fld_e5; // ecx
  int fld_e6; // eax
  int fld_e52; // ecx
  int nArg22; // edi
  int fld_e32; // ecx
  int v12; // eax

  if ( byte_77F280 != 0 )  // 调试机标志(DebugConfig.txt 校验)
  {
    fld_e3 = *(uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e3 + 16))(fld_e3);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 864))(dword_8F7C04, *(uint32_t *)(v5 + 4));  // 全局 dword_8F7C04 = 本机角色对象
    return 1;  // 返回 1(成功)
  }
  else
  {
    fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
    if ( fld_e5 != 0 )  // fld_e5=this+20 nPage
      fld_e6 = (*(this + 6) - fld_e5) >> 2;  // this+24〔nPageMax(推断)〕
    else
      fld_e6 = 0;  // fld_e6=this+24 nPageMax
    if ( fld_e6 < nArg3  // fld_e6=this+24 nPageMax
      && ((fld_e52 = *(this + 5)) == 0  // this+20〔nPage(推断)〕
       || (*(this + 6) - fld_e52) >> 2 < 1  // this+24〔nPageMax(推断)〕
       || (*(this + 6) - fld_e52) >> 2 != 0 && *(uint32_t *)(*(this + 6) - 4) == 8)  // this+24〔nPageMax(推断)〕
      && dword_8F7C04 != 0  // 全局 dword_8F7C04 = 本机角色对象
      && *(uint16_t *)(dword_8F8538 + 4) == 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    {
      sub_423200(dword_8F7B08, 47);  // 【发送网络包API】
      nArg22 = nArg2;
      sub_423290(&nArg2, 2);  // 调 写 4B 长度
      sub_423380(dword_8F7B08);  // 发包提交：Commit()
      sub_484880(this, 8);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
      fld_e32 = *(uint32_t *)(*(this + 3) + 4 * nArg22);  // this+12〔nSkillRec12(推断)〕
      v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e32 + 16))(fld_e32);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 864))(dword_8F7C04, *(uint32_t *)(v12 + 4));  // 全局 dword_8F7C04 = 本机角色对象
      return 1;  // 返回 1(成功)
    }
    else
    {
      return 0;
    }
  }
}



// ------------------------------------------------------------
// 0x486C40 sub_486C40 —— 请求 op 20（整栏技能重置）
//   前置：管理器子对象 +108 为 0；*this 为 0 时 4 组 32 槽（9..136）须存在空位，其余模式整栏须存在空位（·sub_484DB0 空位连续性检查）；包体仅模式字节，压入命令 9。
// ------------------------------------------------------------
char /*thiscall*/ sub_486C40(uint32_t *this)  // 实现：请求 op 20（整栏技能重置）
{
  int fld_e5; // ecx
  int v3; // ebx
  int i; // esi
  int v6; // eax
  uint8_t v7[4]; // [esp+4h] [ebp-4h] BYREF

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 && (*(this + 6) - fld_e5) >> 2 >= 1 || *(uint32_t *)(*((uint32_t *)dword_8F8528 + 20) + 108) != 0 )  // 全局 dword_8F8528 = 消息/弹窗管理器
    return 0;
  if ( *this != 0 )
  {
    if ( *this != 2 && sub_484DB0(this, 0, *(this + 2) - 1) != 0 )  // 槽区间空位连续性检查
      return 0;
  }
  else
  {
    v3 = 0;
    for ( i = 9; i < 137; i += 32 )
    {
      if ( sub_484DB0(this, i, i + 31) == 0 )  // 槽区间空位连续性检查
        break;
      ++v3;
    }
    if ( v3 == 4 )
      return 0;
  }
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  v6 = *(uint32_t *)(dword_8F7C08 + 648);  // 副玩家/观战对象
  if ( v6 != 0 && *(uint8_t *)(v6 + 284) != 0 && *(uint8_t *)(v6 + 285) != 0 )
    return 0;
  sub_423200(dword_8F7B08, 20);  // 【发送网络包API】
  v7[0] = *(uint8_t *)this;
  sub_423290(v7, 1);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  sub_484880(this, 9);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x486D40 sub_486D40 —— 请求 op 44（地图技能判定【推断】）
//   前置：槽 1 有效且 *this == 0；·sub_49BE70 会话数值校验返回非 0 即播报文案 3015（·sub_422E70 取文案、·sub_43BEE0 播报）并拒绝；包体 2 字节 nArg2，压入命令 10。
// ------------------------------------------------------------
char /*thiscall*/ sub_486D40(uint32_t *this, int nArg2)  // 实现：请求 op 44（地图技能判定(推断)）
{
  int fld_e5; // ecx
  uint32_t *v4; // esi
  int v5; // eax

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 && (*(this + 6) - fld_e5) >> 2 >= 1  // this+24〔nPageMax(推断)〕
    || *this != 0
    || (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 3) + 4) + 44))(*(uint32_t *)(*(this + 3) + 4)) == 0  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 +…
    || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
  {
    return 0;
  }
  if ( (uint8_t)sub_49BE70(*((uint32_t *)dword_8F8528 + 605)) != 0 )  // 会话数值 >= 槽值判定（+134 对 +108/+108）
  {
    v4 = *((uint32_t **)dword_8F8528 + 7);  // 全局 dword_8F8528 = 消息/弹窗管理器
    v5 = sub_422E70(3015);  // 调 存 CStringManager::getStr 取本地化串
    sub_43BEE0(v4, v5, -6567706, 0, -1);  // 调 播报 + 面板刷新 ──
    return 0;
  }
  sub_423200(dword_8F7B08, 44);  // 【发送网络包API】
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  sub_484880(this, 10);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x486E00 sub_486E00 —— 请求 op 28（2 字节参数）
//   前置队列空、*this == 0、场景就绪；包体 2 字节 nArg2，压入本地命令 11。
// ------------------------------------------------------------
char /*thiscall*/ sub_486E00(uint32_t *this, int nArg2)  // 实现：请求 op 28（2 字节参数）
{
  int fld_e5; // ecx

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 && (*(this + 6) - fld_e5) >> 2 >= 1 || *this != 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  sub_423200(dword_8F7B08, 28);  // 【发送网络包API】
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  sub_484880(this, 11);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x486E80 sub_486E80 —— 请求 op 83（槽号 + 对象 id + 参数）
//   包体 = 槽号 2 + 槽对象虚表 +16 → +4 的 u16 对象 id 2 + nArg3 2，压入本地命令 12。
// ------------------------------------------------------------
char /*thiscall*/ sub_486E80(uint32_t *this, int nArg2, int nArg3)  // 实现：请求 op 83（槽号 + 对象 id + 参数）
{
  int fld_e5; // ecx
  int nArg22; // edi
  int fld_e3; // ecx

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 && (*(this + 6) - fld_e5) >> 2 >= 1 || *this != 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  sub_423200(dword_8F7B08, 83);  // 【发送网络包API】
  nArg22 = nArg2;
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  if ( nArg22 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    fld_e3 = 0;
  else
    fld_e3 = *(uint32_t *)(*(this + 3) + 4 * nArg22);  // this+12〔nSkillRec12(推断)〕
  nArg2 = *(uint16_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e3 + 16))(fld_e3) + 4);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  nArg2 = nArg3;
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  sub_484880(this, 12);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x486F40 sub_486F40 —— 请求 op 84
//   与 ·0x486E80 同构（差异：操作码 84，压入本地命令 13）。
// ------------------------------------------------------------
char /*thiscall*/ sub_486F40(uint32_t *this, int nArg2, int nArg3)  // 实现：请求 op 84
{
  int fld_e5; // ecx
  int nArg22; // edi
  int fld_e3; // ecx

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 && (*(this + 6) - fld_e5) >> 2 >= 1 || *this != 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  sub_423200(dword_8F7B08, 84);  // 【发送网络包API】
  nArg22 = nArg2;
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  if ( nArg22 >= *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    fld_e3 = 0;
  else
    fld_e3 = *(uint32_t *)(*(this + 3) + 4 * nArg22);  // this+12〔nSkillRec12(推断)〕
  nArg2 = *(uint16_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e3 + 16))(fld_e3) + 4);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  nArg2 = nArg3;
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  sub_484880(this, 13);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x487000 sub_487000 —— 请求 op 32（2 字节参数）
//   前置同 ·0x486E00；包体 2 字节 nArg2，压入本地命令 14。
// ------------------------------------------------------------
char /*thiscall*/ sub_487000(uint32_t *this, int nArg2)  // 实现：请求 op 32（2 字节参数）
{
  int fld_e5; // ecx

  fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != 0 && (*(this + 6) - fld_e5) >> 2 >= 1 || *this != 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  sub_423200(dword_8F7B08, 32);  // 【发送网络包API】
  sub_423290(&nArg2, 2);  // 调 写 4B 长度
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  sub_484880(this, 14);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x487080 sub_487080 —— 遍历技能槽收集有效技能下标
//   对每个非空槽对象，若其虚表 +16 → +52 非 0 则把槽下标经 ·sub_430C80 追加进 4 字节临时表（vector 尾插展开【推断】：结果未回写本对象，属一次性统计）。
// ------------------------------------------------------------
void /*thiscall*/ sub_487080(int *this)  // 实现：遍历技能槽收集有效技能下标
{
  int v1; // edi
  int fld_e2; // eax
  int fld_e3; // ecx
  int fld_e22; // eax
  int v6[4]; // [esp+1Ch] [ebp-10h] BYREF

  v1 = 0;
  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  v6[3] = 0;
  v6[0] = 0;
  if ( fld_e2 > 0 )  // fld_e2=this+8 nSkillRec8
  {
    do
    {
      fld_e3 = *(uint32_t *)(*(this + 3) + 4 * v1);  // this+12〔nSkillRec12(推断)〕
      if ( fld_e3 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e3 + 16))(fld_e3) + 52) != 0 )  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
        sub_430C80(nullptr, 1, (int)v6);  // uint32 vector 区间插入（同值填充）
      fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
      v6[0] = ++v1;
    }
    while ( v1 < fld_e22 );  // fld_e22=this+8 nSkillRec8
  }
}



// ------------------------------------------------------------
// 0x4871A0 sub_4871A0 —— ALERT_1 提示包装（sub_486B40）
// ------------------------------------------------------------
char /*thiscall*/ sub_4871A0(uint32_t *this, int nArg2)  // 实现：ALERT_1 提示包装（sub_486B40）
{
  int pObj; // ebx
  int fld_e3; // esi
  uint32_t *v6; // esi
  int v7; // eax
  int v8; // eax

  pObj = dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
  if ( dword_8F7C04 == 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF || nArg2 >= *(this + 2) )  // 全局 dword_8F7C04 = 本机角色对象
    return 0;
  fld_e3 = *(uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
  if ( fld_e3 == 0  // fld_e3=this+12 nSkillRec12
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e3 + 20))(fld_e3, 1) == 0  // 调虚槽 +20：CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认…
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 804))(pObj, fld_e3) == 0 )  // 调虚槽 +804：★ 装备可用性检查（含 CNRDEquipment RTTI 直证）
  {
    return 0;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e3 + 104))(fld_e3) != 0 )  // 调虚槽 +104：CNRDPrivateStoreWindow_Display__vmt68 页绘制（114 …
  {
    v6 = *((uint32_t **)dword_8F8528 + 7);  // 全局 dword_8F8528 = 消息/弹窗管理器
    v7 = sub_422E70(416);  // 调 存 CStringManager::getStr 取本地化串
    sub_43BEE0(v6, v7, -6567706, 0, -1);  // 调 播报 + 面板刷新 ──
    sub_432EA0("ALERT_1", -1, 0, 0);  // 字符串 “ALERT_1”
    return 0;
  }
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e3 + 140))(fld_e3);  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
  if ( v8 == 1 )
    return sub_486B40(this, nArg2, 1);  // 请求 op 47（使用槽对象）
  if ( v8 != 2 )
    return v8 != 0;
  if ( dword_8F7C04 != 0 )  // 全局 dword_8F7C04 = 本机角色对象
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e3 + 136))(fld_e3, dword_8F7C04, 2, -1);  // 全局 dword_8F7C04 = 本机角色对象
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4872A0 sub_4872A0 —— 槽对象使用分发（按虚表 +20 类型分流）
//   类型 2 走 ·sub_486820 装备装配路径（部位号取虚表 +172）；类型 1 走 ·sub_4871A0（op 47 使用路径）；其余返回 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_4872A0(int *this, int nArg2)  // 实现：槽对象使用分发（按虚表 +20 类型分流）
{
  int fld_e3; // esi
  int *v4; // eax

  fld_e3 = *(uint32_t *)(*(this + 3) + 4 * nArg2);  // this+12〔nSkillRec12(推断)〕
  if ( fld_e3 == 0 )  // fld_e3=this+12 nSkillRec12
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e3 + 20))(fld_e3, 2) != 0 )  // 调虚槽 +20：CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认…
  {
    v4 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e3 + 172))(fld_e3);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
    return sub_486820(this, nArg2, *v4, 1);  // 施放拒绝提示（ALERT_1 音效 + sub_485510）
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e3 + 20))(fld_e3, 1) != 0 )  // 调虚槽 +20：CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认…
    return sub_4871A0(this, nArg2);  // ALERT_1 提示包装（sub_486B40）
  else
    return 0;
}



// ============================================================
// §G 0x487310-0x488060  容器/字符串辅助 + 对象生成
// ============================================================
// ------------------------------------------------------------
// 0x487310 sub_487310 —— 红黑树迭代器后继（std::_Tree::_Inc 语义）
//   +137 为 nil 标志；当前为 nil 时后继取 +8（最右），否则按父链 +4 上溯（比较 +0 判断来向）并返回后继节点。
// ------------------------------------------------------------
int /*thiscall*/ sub_487310(void *this)  // 实现：红黑树迭代器后继（std::_Tree::_Inc 语义）
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 137) != 0 )  // this+137〔field_0089〕
  {
    result = v1[2];
    *(uint32_t *)this = result;  // *this = result
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 137) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 137) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;  // *this = result
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 137) == 0 );
        if ( *(uint8_t *)(result + 137) == 0 )
          *(uint32_t *)this = result;  // *this = result
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 137) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;  // *this = v3
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x487390 sub_487390 —— 红黑树 lower_bound（按键下行）
//   沿左 +0 / 右 +8 子指针下行，命中条件为节点键 +12 >= 查找键；返回不小于键的首节点（哨兵即无）。
// ------------------------------------------------------------
int */*thiscall*/ sub_487390(uint32_t *this, uint32_t *uArg2)  // 红黑树 lower_bound
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);  // this+4〔宿主对象〕
  v3 = (int *)result[1];  // result=this+4 宿主对象
  while ( *((uint8_t *)v3 + 137) == 0 )  // 当 *((uint8_t *)v3 + 137) == 0 循环
  {
    if ( v3[3] >= *uArg2 )
    {
      result = v3;  // result=this+4 宿主对象
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x4873D0 sub_4873D0 —— 红黑树查找定位（回传命中节点或哨兵）
//   以 ·sub_487390 定位后：命中且键相等则回传命中节点，否则回传哨兵 this+1【推断：std::_Tree::_Find 供插入定位】。
// ------------------------------------------------------------
int **/*thiscall*/ sub_4873D0(int **this, int **pDwArg2, uint32_t *uArg3)  // 红黑树查找定位（回传命中节点或哨兵）
{
  int *v5; // eax
  int *fld_e1; // esi
  int *v8; // [esp+18h] [ebp+Ch]

  v5 = sub_487390(this, uArg3);  // 结果 = 红黑树 lower_bound
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  v8 = v5;
  if ( v5 == fld_e1 || *uArg3 < v5[3] )  // fld_e1=this+4 宿主对象
  {
    *pDwArg2 = fld_e1;  // fld_e1=this+4 宿主对象
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = v8;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x487420 sub_487420 —— 按键取节点载荷（未命中返回 0）
//   ·sub_487390 定位后取节点 +16 载荷地址；落在哨兵（== this+2）时返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_487420(uint32_t *this, int nArg2)  // 实现：按键取节点载荷（未命中返回 0）
{
  uint32_t *pThis_1; // esi
  int *pThis_12; // eax
  int *v5; // esi
  int *v6; // eax
  int v7; // eax
  int *pThis_122; // [esp+8h] [ebp-4h] BYREF

  pThis_1 = this + 1;  // this+4〔宿主对象〕
  pThis_12 = sub_487390(this + 1, &nArg2);  // 结果 = 红黑树 lower_bound
  v5 = (int *)pThis_1[1];
  pThis_122 = pThis_12;
  if ( pThis_12 == v5 || nArg2 < pThis_12[3] )  // 若 pThis_12 == v5 与/或 nArg2 < pThis_12
  {
    nArg2 = (int)v5;
    v6 = &nArg2;
  }
  else
  {
    v6 = (int *)&pThis_122;
  }
  v7 = *v6;
  if ( v7 == *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    return 0;
  else
    return v7 + 16;  // 返回 v7 + 16
}



// ------------------------------------------------------------
// 0x487470 sub_487470 —— 房间记录拷贝（0x4C 字节 + 内嵌字符串 + 尾部 3 字段）
//   qmemcpy 拷 0x4C 字节后重建内嵌 std::string（+100 容量 15、+96 长度 0，经 ·sub_4014D0 从源 +76 起赋值），并复制源 +104/+108/+112 三字段。
// ------------------------------------------------------------
int /*thiscall*/ sub_487470(int this, size_t *pArg2)  // 实现：房间记录拷贝（0x4C 字节 + 内嵌字符串 + 尾部 3 字段）
{
  qmemcpy((void *)this, pArg2, 0x4Cu);  // 调 内存块拷贝(内联展开)
  *(uint32_t *)(this + 100) = 15;  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(this + 96) = 0;  // this+96〔nStatusMode(推断)〕等 2 字段
  *(uint8_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  sub_4014D0((size_t *)(this + 76), pArg2 + 19, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
  *(uint32_t *)(this + 104) = pArg2[26];  // this+104〔nTimerEnd(推断)〕
  *(uint32_t *)(this + 108) = pArg2[27];  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 112) = pArg2[28];  // this+112〔pHostComp112〕
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4874D0 sub_4874D0 —— CNPvpRoom 字段清零（8 组槽位表 + 空串）
//   +0 与 +68/+72/+108/+112 清零；+4..+32 八个 dword 置 255、+36..+64 八个 dword 置 0xFFFF；+76 字符串置空（+96=0、+100=15）并置 +104 = -1。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4874D0(uint32_t *this)  // CNPvpRoom 字段清零（8 组槽位表 + 空串）
{
  uint32_t *pThis_9; // eax
  int i; // ecx

  *this = 0;
  pThis_9 = this + 9;  // this+36〔nStateWord36〕
  for ( i = 8; i != 0; --i )  // 循环：i 从 8 递减到 0
  {
    *(pThis_9 - 8) = 255;
    *pThis_9++ = 0xFFFF;  // 常量 0xFFFF（= 0xFFFF）
  }
  *(this + 25) = 15;  // this+100〔bEnchantDone(推断)〕
  *(this + 24) = 0;  // this+96〔nStatusMode(推断)〕
  *((uint8_t *)this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  *(this + 17) = 0;  // this+68〔nCharCount(推断)〕
  *(this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  sub_4015C0(this + 19, szPassword, 0);  // 【std::string构造赋值】
  *(this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *(this + 28) = 0;  // this+112〔pHostComp112〕
  *(this + 26) = -1;  // this+104〔nTimerEnd(推断)〕
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x487560 sub_487560 —— CNPvpRoom 构造
//   置虚表、nullsub_3，经 ·sub_4874D0 初始化字段，再以 unknown_libname_7(nArg2) 传入分配/宿主参数。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_487560(uint32_t *this, int nArg2)  // CNPvpRoom 构造
{
  *this = &CNPvpRoom::`vftable';  // 构造装配 vftable：CNPvpRoom
  sub_4874D0(this + 1);  // CNPvpRoom 字段清零（8 组槽位表 + 空串）
  nullsub_3(this);
  unknown_libname_7(nArg2);
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4875C0 sub_4875C0 —— 红黑树节点分配（0x8C 字节 · 内嵌房间对象）
//   new 0x8C：+0..+12 存四个键值参数，+16 挂 CNPvpRoom 虚表、+20 起经 ·sub_487470 深拷房间记录；+136 置颜色标志、+137 哨兵标志置 0。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4875C0(int nArg1, int nArg2, int nArg3, uint32_t *uArg4, char pszArg5)  // 红黑树节点分配（0x8C 字节 · 内嵌房间对象）
{
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  pMem = operator new(0x8Cu);  // 堆分配 140 字节对象
  pMem2 = pMem;
  v8[4] = pMem;
  v8[8] = (void *)1;  // v8[8] = 转换(1)
  v8[3] = pMem;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
  {
    *pMem = nArg1;
    pMem[1] = nArg2;
    pMem[2] = nArg3;
    pMem[3] = *uArg4;
    pMem[4] = &CNPvpRoom::`vftable';  // 构造装配 vftable：CNPvpRoom
    sub_487470((int)(pMem + 5), uArg4 + 2);  // 房间记录拷贝（0x4C 字节 + 内嵌字符串 + 尾部 3 字段）
    *((uint8_t *)pMem2 + 136) = pszArg5;
    *((uint8_t *)pMem2 + 137) = 0;
  }
  return pMem2;
}



// ------------------------------------------------------------
// 0x487670 sub_487670 —— 按键取节点载荷（未命中走错误通道）
//   与 ·0x487420 同构（差异：未命中时经 off_77F3FC(aCriticalError_9, 键) 报错；命中经 ·sub_436940 取值）。
// ------------------------------------------------------------
int /*thiscall*/ sub_487670(uint32_t *this, int ArgList)  // 实现：按键取节点载荷（未命中走错误通道）
{
  uint32_t *pThis_1; // esi
  int *pThis_12; // eax
  int *v5; // ecx
  int v6; // edx
  int *p_ArgList; // eax
  int v8; // eax
  int *pThis_122; // [esp+8h] [ebp-4h] BYREF

  pThis_1 = this + 1;  // this+4〔宿主对象〕
  pThis_12 = sub_487390(this + 1, &ArgList);  // 结果 = 红黑树 lower_bound
  v5 = (int *)pThis_1[1];
  v6 = ArgList;
  pThis_122 = pThis_12;
  if ( pThis_12 == v5 || ArgList < pThis_12[3] )  // 若 pThis_12 == v5 与/或 ArgList < pThis_12
  {
    ArgList = (int)v5;
    p_ArgList = &ArgList;
  }
  else
  {
    p_ArgList = (int *)&pThis_122;
  }
  v8 = *p_ArgList;
  if ( v8 == *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    return off_77F3FC(aCriticalError_9, v6);  // 返回 调 off_77F3FC
  else
    return sub_436940(&ArgList, v8);  // std::map 节点摘除（CNPvpRoom 值版）
}



// ------------------------------------------------------------
// 0x4876E0 sub_4876E0 —— 红黑树插入与重平衡
//   长度上限 0x2108420 超出即抛 map/set too long（std::length_error）；经 ·sub_4875C0 建节点挂到 pArg4 对应侧后，循环变色与旋转（·sub_433000/·sub_4330C0）恢复红黑性质；+136 为颜色字节。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4876E0(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, uint32_t *uArg5)  // 红黑树插入与重平衡
{
  uint32_t *fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
  uint32_t *fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
  size_t v17; // [esp+34h] [ebp-28h] BYREF
  char v18; // [esp+38h] [ebp-24h]
  int v19; // [esp+48h] [ebp-14h]
  int v20; // [esp+4Ch] [ebp-10h]
  int v21; // [esp+58h] [ebp-4h]
  uint32_t *fld_e15; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0x2108420 )  // this+8〔nSkillRec8(推断)〕
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
    pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常
  }
  fld_e1 = sub_4875C0(*(this + 1), (int)pArg4, *(this + 1), uArg5, 0);  // 结果 = 红黑树节点分配（0x8C 字节 · 内嵌房间对象）
  fld_e12 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( pArg4 == fld_e12 )  // fld_e12=this+4 宿主对象
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    *(uint32_t *)*(this + 1) = fld_e1;  // this+4〔宿主对象〕
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == (uint32_t *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // fld_e14=this+4 宿主对象
  }
  v10 = fld_e1 + 1;
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(fld_e1[1] + 136) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 136) != 0 )
        {
          if ( fld_e16 == (uint32_t *)v12[2] )
          {
            fld_e16 = (uint32_t *)*v10;
            sub_433000(*v10);  // 红黑树左旋
          }
          *(uint8_t *)(fld_e16[1] + 136) = 1;
          *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 136) = 0;
          sub_4330C0(*(uint32_t *)(fld_e16[1] + 4));  // 红黑树右旋
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 136) != 0 )
      {
        if ( fld_e16 == (uint32_t *)*v12 )
        {
          fld_e16 = (uint32_t *)*v10;
          sub_4330C0(*v10);  // 红黑树右旋
        }
        *(uint8_t *)(fld_e16[1] + 136) = 1;
        *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 136) = 0;
        sub_433000(*(uint32_t *)(fld_e16[1] + 4));  // 红黑树左旋
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 136) = 1;
      *(uint8_t *)(v14 + 136) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 136) = 0;  // 虚调用 vt+4
      fld_e16 = *(uint32_t **)(*v10 + 4);
LABEL_21:
      v10 = fld_e16 + 1;
      if ( *(uint8_t *)(fld_e16[1] + 136) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 136) = 1;  // this+4〔宿主对象〕
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4878B0 sub_4878B0 —— 红黑树清空与宿主输出复位
//   经 ·sub_436CA0 递归释放全部节点，重建根/哨兵自环（+4/+8 指向自身）并清零计数，末尾 ·sub_48F890(0) 输出 @@SET HOST 0【推断：恢复宿主显示】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4878B0(uint32_t *this)  // 实现：红黑树清空与宿主输出复位
{
  uint32_t *pThis_1; // esi
  uint32_t *v2; // eax

  pThis_1 = this + 1;  // this+4〔宿主对象〕
  sub_436CA0(*(void **)(*(this + 2) + 4));  // 红黑树递归销毁（CNPvpRoom 值版）
  *(uint32_t *)(pThis_1[1] + 4) = pThis_1[1];
  v2 = (uint32_t *)pThis_1[1];
  pThis_1[2] = 0;
  *v2 = v2;
  *(uint32_t *)(pThis_1[1] + 8) = pThis_1[1];
  return sub_48F890(0);  // 宿主切换 @@SET HOST %d 输出（sub_48F5A0 槽位、sub_4529B0
}



// ------------------------------------------------------------
// 0x4878F0 sub_4878F0 —— 红黑树插入定位（_Insert 带 hint）
//   先按键下行定位插入点并记录向左/向右；命中同键直接回传，否则调 ·sub_4876E0 插入新节点，回传 (迭代器, 是否新增) 对。
// ------------------------------------------------------------
int /*thiscall*/ sub_4878F0(int *this, int pArg2, uint32_t *uArg3)  // 实现：红黑树插入定位（_Insert 带 hint）
{
  uint32_t *uArg32; // ebx
  uint32_t *fld_e1; // esi
  int *v6; // eax
  bool v7; // cl
  int v8; // edx
  uint32_t *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  uArg32 = uArg3;
  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v6 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 137) == 0 )
  {
    v8 = *uArg3;
    do
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;  // fld_e1=this+4 宿主对象
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 137) == 0 );
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  uArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )  // this+4〔宿主对象〕
    {
      v10 = *sub_4876E0(this, &uArg3, 1, fld_e1, uArg32);  // 结果 = 红黑树插入与重平衡
      *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_487310(&uArg3);  // 红黑树迭代器后继（std::_Tree::_Inc 语义）
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // pArg2+4〔宿主对象〕
    *(uint32_t *)pArg2 = fld_e12;  // *pArg2 = fld_e12
    return pArg2;
  }
  else
  {
    v12 = *sub_4876E0(this, &uArg3, v13, fld_e1, uArg32);  // 结果 = 红黑树插入与重平衡
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4879B0 sub_4879B0 —— 按键取房间对象（缺则新建）
//   ·sub_487420 命中即返回载荷；否则 new 0x78 CNPvpRoom（·sub_487560）经 ·sub_4878F0 插入树，回传新节点 +16 载荷。
// ------------------------------------------------------------
int /*thiscall*/ sub_4879B0(int *this, int nArg2)  // 实现：按键取房间对象（缺则新建）
{
  int nArg22; // ebx
  int result; // eax
  uint32_t *v5; // esi
  uint32_t *pMem; // eax
  int *pThis_1; // edi
  int *v8; // eax
  int *v9; // edi
  void **p_Block; // eax
  int nArg222; // [esp+Ch] [ebp-90h] BYREF
  void **v12; // [esp+10h] [ebp-8Ch] BYREF
  uint8_t v13[116]; // [esp+14h] [ebp-88h] BYREF
  uint8_t v14[4]; // [esp+88h] [ebp-14h] BYREF
  void *Block; // [esp+8Ch] [ebp-10h] BYREF
  int v16; // [esp+98h] [ebp-4h]

  nArg22 = nArg2;
  result = sub_487420(this, nArg2);  // 结果 = 按键取节点载荷（未命中返回 0）
  v5 = nullptr;
  if ( result == 0 )
  {
    pMem = operator new(0x78u);  // 堆分配 120 字节对象
    Block = pMem;
    v16 = 0;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v5 = sub_487560(pMem, nArg22);  // 结果 = CNPvpRoom 构造
    v16 = -1;
    nArg222 = nArg22;
    v12 = &CNPvpRoom::`vftable';  // 构造装配 vftable：CNPvpRoom
    sub_487470((int)v13, v5 + 1);  // 房间记录拷贝（0x4C 字节 + 内嵌字符串 + 尾部 3 字段）
    pThis_1 = this + 1;  // this+4〔宿主对象〕
    v16 = 1;
    sub_4878F0(pThis_1, (int)v14, &nArg222);  // 红黑树插入定位（_Insert 带 hint）
    v16 = -1;
    sub_433FB0(&v12);  // CNPvpRoom 清体
    if ( v5 != nullptr )  // 若 v5 有效（非空）
      (*(void (/*thiscall*/ **)(uint32_t *, int))*v5)(v5, 1);
    v8 = sub_487390(pThis_1, &nArg2);  // 结果 = 红黑树 lower_bound
    v9 = (int *)pThis_1[1];
    nArg2 = (int)v8;
    if ( v8 == v9 || nArg22 < v8[3] )  // 若 v8 == v9 与/或 nArg22 < v8
    {
      Block = v9;
      p_Block = &Block;
    }
    else
    {
      p_Block = (void **)&nArg2;
    }
    return (int)*p_Block + 16;
  }
  return result;
}



// ------------------------------------------------------------
// 0x487AB0 sub_487AB0 —— CNChaosModule 状态块初始化
//   +4 初始化标志为 0 时清 +12..+40 各字段并置 +44 = -1、+92 = 0、+96 = 2、+128 = 0。【推断：gfx_texture 战场模块构造尾部同址调用】
// ------------------------------------------------------------
int /*thiscall*/ sub_487AB0(int this)  // 实现：CNChaosModule 状态块初始化
{
  int result; // eax

  result = 0;
  if ( *(uint8_t *)(this + 4) == 0 )  // this+4〔宿主对象〕等 2 字段
  {
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
    *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
    *(uint32_t *)(this + 36) = 0;  // this+36〔nStateWord36(推断)〕等 2 字段
    *(uint32_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
    *(uint32_t *)(this + 44) = -1;  // this+44〔nExpireMs(推断)〕等 2 字段
    *(uint32_t *)(this + 92) = 0;  // this+92〔pFxObjC(推断)〕等 2 字段
    *(uint32_t *)(this + 96) = 2;  // this+96〔nStatusMode(推断)〕等 2 字段
    *(uint8_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
    *(uint32_t *)(this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
    *(uint32_t *)(this + 20) = 0;  // this+20〔nPage(推断)〕等 2 字段
    *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  }
  return result;
}



// ------------------------------------------------------------
// 0x487AF0 sub_487AF0 —— 内嵌 nengine::IObject 基类析构桩
//   +8 处虚表复位为 nengine::IObject 并清 +12 标志（容器析构前先降级虚表）。
// ------------------------------------------------------------
void /*thiscall*/ sub_487AF0(int this)  // 实现：内嵌 nengine::IObject 基类析构桩
{
  *(uint32_t *)(this + 8) = &nengine::IObject::`vftable';  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint8_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
}



// ------------------------------------------------------------
// 0x487B00 sub_487B00 —— 屏幕白闪淡入淡出（0↔255 插值）
//   +112 使能时按 +96 方向：1 由 0 插值到 255，0 由 255 插回 0 并在时钟越过 +124 时置 +96 = 2 并关闭；结果写 dword_8F8528+2484 供渲染【推断：转场白闪】。
// ------------------------------------------------------------
char /*thiscall*/ sub_487B00(int this)  // 实现：屏幕白闪淡入淡出（0↔255 插值）
{
  uint64_t v2; // rax
  int fld_7C; // edi
  int pThis_64; // eax
  int fld_7C2; // ebx
  int pThis_642; // eax
  uint64_t v7; // rax
  int fld_7C3; // ebx

  LOBYTE(v2) = *(uint8_t *)(this + 112);  // this+112〔pHostComp112〕
  if ( (uint8_t)v2 != 0 )
  {
    LODWORD(v2) = *(uint32_t *)(this + 96);  // this+96〔nStatusMode(推断)〕等 2 字段
    if ( (uint32_t)v2 == 1 )
    {
      fld_7C = *(uint32_t *)(this + 124);  // this+124〔pAuraAnim(推断)〕
      pThis_64 = sub_699000(this + 100);  // 【clock_now(clk)】
      v2 = (uint64_t)sub_4049C0(0.0, 255.0, pThis_64, fld_7C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      *((uint32_t *)dword_8F8528 + 621) = v2;  // 全局 dword_8F8528 = 消息/弹窗管理器
    }
    else if ( (uint32_t)v2 == 0 )
    {
      fld_7C2 = *(uint32_t *)(this + 124);  // this+124〔pAuraAnim(推断)〕
      pThis_642 = sub_699000(this + 100);  // 【clock_now(clk)】
      v7 = (uint64_t)sub_4049C0(255.0, 0.0, pThis_642, fld_7C2);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      *((uint32_t *)dword_8F8528 + 621) = v7;  // 全局 dword_8F8528 = 消息/弹窗管理器
      fld_7C3 = *(uint32_t *)(this + 124);  // this+124〔pAuraAnim(推断)〕
      LODWORD(v2) = sub_699000(this + 100);  // 【clock_now(clk)】
      if ( (int)v2 >= fld_7C3 )  // fld_7C3=this+124 pAuraAnim
      {
        *(uint32_t *)(this + 96) = 2;  // this+96〔nStatusMode(推断)〕等 2 字段
        *(uint8_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x487BA0 sub_487BA0 —— 对象/掉落物生成（+44 引用、+284、sub_45E870/45E680 场景注册）
// ------------------------------------------------------------
char /*thiscall*/ sub_487BA0(int this)  // 实现：对象/掉落物生成（+44 引用、+284、sub_45E870/45E680 场景注册）
{
  int v2; // edi
  int pSceneObj; // eax  | +0x005C → 场景对象/掉落物（CNChaosModule；va=00487BA0）
  int pThis_30; // eax
  uint8_t v5; // al
  uint8_t *v6; // eax
  int i; // ecx

  sub_4AEB30(&unk_9A02B0);  // 调 帧开始（原文参数 &unk_9A02B0）
  sub_433690();  // 【= 主帧 tick（timeGetTime 驱动；'SHUTTER_ON' 截屏音效…】
  sub_4294E0(*(uint32_t *)(this + 28));  // HUD 每帧总 tick（尾段）
  v2 = 0;
  if ( *(uint8_t *)(*((uint32_t *)dword_8F8528 + 625) + 44) != 0 )  // 全局 dword_8F8528 = 消息/弹窗管理器
    v2 = sub_45E870(pt.x, pt.y, 1);  // 结果 = 光标点选对象（倒序遍历 ·+40 表）
  pSceneObj = *(uint32_t *)(this + 92);  // this+92〔pFxObjC(推断)〕等 2 字段
  if ( pSceneObj != v2 )  // fld_5C=this+92 pFxObjC
  {
    if ( pSceneObj != 0 && (uint8_t)sub_45E680(*(uint32_t *)(this + 92)) != 0 )  // 对象表归属判定
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(**(uint32_t **)(this + 92) + 284))(  // 调虚槽 +284：四字段批量写（+248..+260）
        *(uint32_t *)(this + 92),  // this+92 场景对象/掉落物
        0,
        0,
        1,
        2);
    *(uint32_t *)(this + 92) = v2;  // this+92〔pFxObjC(推断)〕等 2 字段
  }
  if ( *(uint32_t *)(this + 92) != 0 )  // this+92〔pFxObjC(推断)〕等 2 字段
  {
    pThis_30 = sub_699000(this + 48);  // 【clock_now(clk)】
    v5 = sub_42B420(100, 255, pThis_30, 500);  // 结果 = 往返插值（三角波）
    (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, int))(**(uint32_t **)(this + 92) + 284))(  // 调虚槽 +284：四字段批量写（+248..+260）
      *(uint32_t *)(this + 92),  // this+92 场景对象/掉落物
      1,
      (v5 << 24) | 0xFF9B,
      0,
      1);
  }
  sub_487B00(this);  // 屏幕白闪淡入淡出（0↔255 插值）
  LOBYTE(v6) = *(uint8_t *)(this + 128);  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  if ( (uint8_t)v6 == 0 )
  {
    *(uint8_t *)(this + 128) = 1;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
    v6 = (uint8_t *)(dword_8F8520 + 1048692);  // 会话/UDP 管理器
    for ( i = 8; i != 0; --i )  // 循环：i 从 8 递减到 0
    {
      if ( *v6 == 0 )
      {
        *v6 = 1;
        v6[1] = 0;
        v6[2] = 0;
      }
      v6 += 28;
    }
  }
  return (char)v6;
}



// ------------------------------------------------------------
// 0x487CA0 sub_487CA0 —— 子容器析构（两子对象 + free）
//   析构字节偏移 +216 与 +160 两子对象（·sub_41A580），free +8 缓冲并把 +12/+16 清零。
// ------------------------------------------------------------
void /*thiscall*/ sub_487CA0(int this)  // 实现：子容器析构（两子对象 + free）
{
  sub_41A580((uint32_t *)(this + 54));  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)(this + 40));  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  if ( *(uint32_t *)(this + 8) != 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
    j__free(*(void **)(this + 8));  // 释放 this+8〔nSkillRec8(推断)〕堆块
  *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
  *(uint32_t *)(this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
}



// ------------------------------------------------------------
// 0x487D10 sub_487D10 —— 抛 vector too long（std::length_error）
//   构造 std::length_error 并 _CxxThrowException（文案 vector<T> too long），供 vector 扩容上限检查调用。
// ------------------------------------------------------------
void /*noreturn*/ sub_487D10()  // 抛 vector too long（std::length_error）
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
  sub_401740(pExceptionObject, &v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常
}



// ------------------------------------------------------------
// 0x487D80 sub_487D80 —— 4 字节元素 vector 区间插入（_Insert_n 扩展）
//   超长（0x3FFFFFFF）先 ·sub_487D10 抛异常；容量足够时后半段经 ·sub_55E7F0 后移、尾部经 ·sub_5DAF70 搬移，再由 ·sub_49A9D0 按值填充。
//   容量不足则 new 重分配（memcpy + ·sub_523700 构造 + ·sub_49A9D0 填充）并释放旧块。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_487D80(int this, int Src, unsigned int uArg3, int *pDwArg4)  // 实现：4 字节元素 vector 区间插入（_Insert_n 扩展）
{
  int pVecEnd_16; // edx
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

  pVecEnd_16 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  pDwArg4 = (int *)*pDwArg4;
  if ( pVecEnd_16 != 0 )  // fld_4=this+4 宿主对象
    result = (*(uint32_t *)(this + 12) - pVecEnd_16) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    result = 0;  // result=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( pVecEnd_16 != 0 )  // fld_4=this+4 宿主对象
      fld_8 = (*(uint32_t *)(this + 8) - pVecEnd_16) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_8 = 0;  // fld_8=this+8 nSkillRec8
    if ( 0x3FFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_487D10(this);  // 抛 vector too long（std::length_error）
    if ( pVecEnd_16 != 0 )  // fld_4=this+4 宿主对象
      fld_82 = (*(uint32_t *)(this + 8) - pVecEnd_16) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( result >= uArg3 + fld_82 )  // result=this+12 nSkillRec12
    {
      fld_83 = *(uint8_t **)(this + 8);  // this+32〔nHeight(推断)〕
      v21 = (int)&fld_83[-Src] >> 2;  // fld_83=this+32 nHeight
      v22 = 4 * uArg3;
      v29 = (int)fld_83;  // fld_83=this+32 nHeight
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];  // fld_83=this+32 nHeight
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // 商城状态
        sub_5DAF70((void *)Src, v24, v29);  // 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // 商城状态
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // 调 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];  // this+8〔nSkillRec8(推断)〕等 2 字段
        *(uint32_t *)(this + 8) = fld_84;  // this+8〔nSkillRec8(推断)〕等 2 字段
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )  // result=this+12 nSkillRec12
        v10 = (result >> 1) + result;  // result=this+12 nSkillRec12
      else
        v10 = 0;
      if ( pVecEnd_16 != 0 )  // fld_4=this+4 宿主对象
        fld_85 = (*(uint32_t *)(this + 8) - pVecEnd_16) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_85 = 0;  // fld_85=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_85 )  // fld_85=this+8 nSkillRec8
      {
        if ( pVecEnd_16 != 0 )  // fld_4=this+4 宿主对象
          fld_86 = (*(uint32_t *)(this + 8) - pVecEnd_16) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else
          fld_86 = 0;  // fld_86=this+8 nSkillRec8
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);  // 分配 4 × v10 字节数组
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);  // this+4〔宿主对象〕
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+16〔nChannelTypeSel(推断)〕
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // 调 填充补足尾段
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));  // this+8〔nSkillRec8(推断)〕等 2 字段
      fld_43 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
      if ( fld_43 != 0 )  // fld_43=this+4 宿主对象
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )  // fld_43=this+4 宿主对象
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      *(uint32_t *)(this + 12) = &pMem[v28];  // this+12〔nSkillRec12(推断)〕等 2 字段
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
      return (unsigned int)pMem;
    }
  }
  return result;  // result=this+12 nSkillRec12
}



// ------------------------------------------------------------
// 0x487F60 sub_487F60 —— 4 字节元素尾插
//   容量足够时直接写尾元素并推进 this+2；否则回落 ·sub_487D80 插入 1 项。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_487F60(int *this, int *pDwArg2)  // 实现：4 字节元素尾插
{
  int pVecEnd_6; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  pVecEnd_6 = *(this + 1);  // this+4〔宿主对象〕
  if ( pVecEnd_6 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - pVecEnd_6) >> 2;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( pVecEnd_6 == 0 || fld_e2 >= (*(this + 3) - pVecEnd_6) >> 2 )  // this+12〔nSkillRec12(推断)〕
    return sub_487D80((int)this, *(this + 2), 1u, pDwArg2);  // 4 字节元素 vector 区间插入（_Insert_n 扩展）
  fld_e22 = (int *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
  *fld_e22 = *pDwArg2;  // fld_e22=this+8 nSkillRec8
  result = (unsigned int)(fld_e22 + 1);  // fld_e22=this+8 nSkillRec8
  *(this + 2) = result;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x487FB0 sub_487FB0 —— 68 字节元素容器析构
//   自 this+1 到 this+2 逐条 ·sub_487CA0 析构后 free 缓冲，三个指针清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_487FB0(int *this)  // 实现：68 字节元素容器析构
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  result = 0;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 68 )  // this+8〔nSkillRec8(推断)〕
      sub_487CA0(fld_e1);  // 子容器析构（两子对象 + free）
    j__free((void *)*(this + 1));  // this+4〔宿主对象〕
    result = 0;
  }
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x487FF0 sub_487FF0 —— CNChaosModule 成员对象初始化（0x38 字节）
//   +16..+24 与 +28..+52 清零、+40 置 1；+28 = off_6C2B88（画布节点【推断】）；this[0] = pArg2 并以 this[1] = pArg2+40 回指宿主。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_487FF0(uint32_t *this, int pArg2)  // CNChaosModule 成员对象初始化（0x38 字节）
{
  *(this + 4) = 0;  // this+16〔nChannelTypeSel(推断)〕
  *(this + 5) = 0;  // this+20〔nPage(推断)〕
  *(this + 6) = 0;  // this+24〔nPageMax(推断)〕
  *((uint8_t *)this + 32) = 0;  // this+32〔nHeight(推断)〕
  *(this + 9) = 0;  // this+36〔nStateWord36(推断)〕
  *((uint8_t *)this + 42) = 0;
  *((uint8_t *)this + 41) = 0;
  *(this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *(this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *(this + 11) = 0;  // this+44〔nExpireMs(推断)〕
  *(this + 7) = &off_6C2B88;  // this+28〔pPanelVec(推断)〕
  *((uint8_t *)this + 40) = 1;  // this+40〔bStateSub40(推断)〕
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  *this = pArg2;
  *(this + 1) = *(uint32_t *)(pArg2 + 40);  // this+4〔宿主对象〕
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x488040 sub_488040 —— 成员对象析构
//   +28 虚表复位为 nengine::IObject、+32 标志清零，再经 ·sub_487FB0 释放 +12 起的 68 字节元素容器。
// ------------------------------------------------------------
int /*thiscall*/ sub_488040(int this)  // 实现：成员对象析构
{
  *(uint32_t *)(this + 28) = &nengine::IObject::`vftable';  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint8_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  return sub_487FB0((int *)(this + 12));  // 68 字节元素容器析构
}



// ============================================================
// §H 0x488060-0x488D90  ★版本串 + TutorialTip.etc 解析器 + 读盘画面
// ============================================================
// ------------------------------------------------------------
// 0x488060 sub_488060 —— 战场块（0x1F0）装载与卸载
//   Block 为 -1 时析构释放 +8 块并把 +7 → +108 置 0；否则重建 0x1F0 块（·sub_42E8F0 构造）挂到 +7 → +108，旧块统一经 ·sub_42E7F0 析构后释放。
// ------------------------------------------------------------
int /*thiscall*/ sub_488060(uint32_t *this, void *Block)  // 实现：战场块（0x1F0）装载与卸载
{
  void *fld_e8; // edi
  int result; // eax
  int fld_e7; // edx

  off_77F3FC((char *)&byte_6C8BF4, Block);  // 引擎日志输出函数(printf 风格)
  *(this + 22) = Block;  // this+88〔pFxObjB(推断)〕
  fld_e8 = (void *)*(this + 8);  // this+32〔nHeight(推断)〕
  if ( Block == (void *)-1 )
  {
    if ( fld_e8 != nullptr )  // 若 fld_e8 有效（非空）
    {
      nullsub_3(fld_e8);  // fld_e8=this+32 nHeight
      sub_42E7F0(fld_e8);  // 主体析构（0x1F0）
      j__free(fld_e8);  // 调 堆释放
    }
    result = *(this + 7);  // this+28〔pPanelVec(推断)〕
    *(this + 8) = 0;  // this+32〔nHeight(推断)〕
    *(uint32_t *)(result + 108) = 0;  // result=this+28 pPanelVec
  }
  else
  {
    if ( fld_e8 != nullptr )  // 若 fld_e8 有效（非空）
    {
      nullsub_3(fld_e8);  // fld_e8=this+32 nHeight
      sub_42E7F0(fld_e8);  // 主体析构（0x1F0）
      j__free(fld_e8);  // 调 堆释放
    }
    *(this + 8) = 0;  // this+32〔nHeight(推断)〕
    if ( operator new(0x1F0u) != nullptr )  // 堆分配 496 字节对象
      result = sub_42E8F0(*(this + 22));  // 结果 = 构造（0x1F0）
    else
      result = 0;  // result=this+28 pPanelVec
    fld_e7 = *(this + 7);  // this+28〔pPanelVec(推断)〕
    *(this + 8) = result;  // this+32〔nHeight(推断)〕
    *(uint32_t *)(fld_e7 + 108) = result;  // fld_e7=this+28 pPanelVec
  }
  return result;  // result=this+28 pPanelVec
}



// ------------------------------------------------------------
// 0x488160 sub_488160 —— 战场模块延迟初始化
//   +4 为 0 时置 1：new IControl（·sub_426BD0 0x68）与 CNRDStage（·sub_42B7E0 0x558）并回指宿主，登记 5 处资源句柄（·sub_69A840）。
//   随后 ·sub_488060(-1) 先卸战场块，再建 +16（0x24 布局）/ +20（·sub_487FF0）/ +24（8 字节回指）三个辅助对象。
// ------------------------------------------------------------
char /*thiscall*/ sub_488160(int this)  // 实现：战场模块延迟初始化
{
  int *pMem5; // eax
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  char *pMem2; // eax
  char *v6; // eax
  uint8_t *pMem3; // eax
  uint32_t *pMem4; // eax
  uint32_t *v9; // eax

  LOBYTE(pMem5) = *(uint8_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( (uint8_t)pMem5 == 0 )
  {
    *(uint8_t *)(this + 4) = 1;  // this+4〔宿主对象〕等 2 字段
    pMem = operator new(0x68u);  // 堆分配 104 字节对象
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v4 = sub_426BD0(pMem);  // 结果 = nengine::IControl 构造
    else
      v4 = nullptr;
    *(uint32_t *)(this + 12) = v4;  // this+12〔nSkillRec12(推断)〕等 2 字段
    *((uint32_t *)v4 + 17) = this + 8;  // v4[17] = this + 8
    pMem2 = (char *)operator new(0x558u);  // 堆分配 1368 字节对象
    if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
      v6 = sub_42B7E0(pMem2);  // 调 ：= 评价/横幅对象大构造器（36 字节槽组 ×N，尾调 0x423C10 复位评价值）
    else
      v6 = nullptr;
    *(uint32_t *)(this + 28) = v6;  // this+28〔pPanelVec(推断)〕等 2 字段
    sub_69A840(*((uint32_t *)v6 + 9));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));  // 主管理器(消息/弹窗)
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));  // 主管理器(消息/弹窗)
    sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 40));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));  // 主管理器(消息/弹窗)
    sub_488060((uint32_t *)this, (void *)0xFFFFFFFF);  // 战场块（0x1F0）装载与卸载
    pMem3 = operator new(0x24u);  // 堆分配 36 字节对象
    if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    {
      pMem3[12] = 0;
      *((uint32_t *)pMem3 + 2) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
      *((uint32_t *)pMem3 + 4) = 0;
      pMem3[20] = 1;
      pMem3[22] = 0;
      pMem3[21] = 0;
      *((uint32_t *)pMem3 + 8) = 0;
      *((uint32_t *)pMem3 + 7) = 0;
      *((uint32_t *)pMem3 + 6) = 0;
      *((uint32_t *)pMem3 + 1) = 0;
      *(uint32_t *)pMem3 = this;  // *pMem3 = this
      *((uint32_t *)pMem3 + 1) = *(uint32_t *)(this + 40);  // pMem3[1] = 读 this+40
    }
    else
    {
      pMem3 = nullptr;
    }
    *(uint32_t *)(this + 16) = pMem3;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
    pMem4 = operator new(0x38u);  // 堆分配 56 字节对象
    if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
      v9 = sub_487FF0(pMem4, this);  // 结果 = CNChaosModule 成员对象初始化（0x38 字节）
    else
      v9 = nullptr;
    *(uint32_t *)(this + 20) = v9;  // this+20〔nPage(推断)〕等 2 字段
    pMem5 = (int *)operator new(8u);  // 堆分配 8 字节对象
    if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    {
      pMem5[1] = 0;
      *pMem5 = this;
      pMem5[1] = *(uint32_t *)(this + 40);  // pMem5[1] = 读 this+40
      *(uint32_t *)(this + 24) = pMem5;  // this+24〔nPageMax(推断)〕等 2 字段
    }
    else
    {
      *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
      LOBYTE(pMem5) = 0;
    }
  }
  return (char)pMem5;
}



// ------------------------------------------------------------
// 0x488300 sub_488300 —— 战场模块卸载
//   +4 为 1 时置 0，按 +12/+28/+32/+36/+40/+16/+20/+24 顺序释放：IControl 虚表 +0(this,1)、CNRDStage ·sub_42BD40、·sub_42E940、战场块 ·sub_42EDE0、战斗条目 ·sub_42C770、·sub_487AF0、·sub_488040。
// ------------------------------------------------------------
void /*thiscall*/ sub_488300(int this)  // 实现：战场模块卸载
{
  void (/*thiscall*/ ***pThis_C)(uint32_t, int); // ecx
  void *fld_1C; // edi
  void *fld_20; // edi
  void *fld_24; // edi
  void *fld_28; // edi
  void *fld_10; // edi
  void *fld_14; // edi
  void *fld_18; // eax

  if ( *(uint8_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
  {
    pThis_C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
    *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
    if ( pThis_C != nullptr )  // 若 pThis_C 有效（非空）
      (**pThis_C)(pThis_C, 1);  // 调 pThis_C 的虚函数（vt+0）
    fld_1C = *(void **)(this + 28);  // this+112〔pHostComp112〕
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    if ( fld_1C != nullptr )  // 若 fld_1C 有效（非空）
    {
      sub_42BD40(fld_1C);  // CNRDStage 析构（对应 ·0x42B7E0 构造）
      j__free(fld_1C);  // 调 堆释放
    }
    fld_20 = *(void **)(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
    *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
    if ( fld_20 != nullptr )  // 若 fld_20 有效（非空）
    {
      sub_42E940(fld_20);  // 析构（0x1F0）
      j__free(fld_20);  // 调 堆释放
    }
    fld_24 = *(void **)(this + 36);  // this+144〔pFrameList144(推断)〕
    *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
    if ( fld_24 != nullptr )  // 若 fld_24 有效（非空）
    {
      sub_42EDE0(fld_24);  // 战场块析构
      j__free(fld_24);  // 调 堆释放
    }
    fld_28 = *(void **)(this + 40);  // this+160〔fAdd160(推断)〕
    *(uint32_t *)(this + 36) = 0;  // this+36〔nStateWord36(推断)〕等 2 字段
    if ( fld_28 != nullptr )  // 若 fld_28 有效（非空）
    {
      sub_42C770(fld_28);  // 战斗条目析构
      j__free(fld_28);  // 调 堆释放
    }
    fld_10 = *(void **)(this + 16);  // this+64〔apServerTabBtn(推断)〕
    *(uint32_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
    if ( fld_10 != nullptr )  // 若 fld_10 有效（非空）
    {
      sub_487AF0((int)fld_10);  // 内嵌 nengine::IObject 基类析构桩
      j__free(fld_10);  // 调 堆释放
    }
    fld_14 = *(void **)(this + 20);  // this+80〔nAuraStage(推断)〕
    *(uint32_t *)(this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
    if ( fld_14 != nullptr )  // 若 fld_14 有效（非空）
    {
      sub_488040((int)fld_14);  // 成员对象析构
      j__free(fld_14);  // 调 堆释放
    }
    fld_18 = *(void **)(this + 24);  // this+96〔nStatusMode(推断)〕
    *(uint32_t *)(this + 20) = 0;  // this+20〔nPage(推断)〕等 2 字段
    if ( fld_18 != nullptr )  // 若 fld_18 有效（非空）
      j__free(fld_18);  // 调 堆释放
    *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  }
}



// ------------------------------------------------------------
// 0x4883E0 sub_4883E0 —— 转发到 +48 对象虚表 +16
//   对 pArg1+48 的对象调用虚表 +16(nArg2) 并回传结果。
// ------------------------------------------------------------
int /*cdecl*/ sub_4883E0(int pArg1, int nArg2)  // 实现：转发到 +48 对象虚表 +16
{
  return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 48) + 16))(*(uint32_t *)(pArg1 + 48), nArg2);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE…
}



// ------------------------------------------------------------
// 0x488400 sub_488400 —— 接口桩构造（虚表 off_6C8C08）
//   +4 标志清零、虚表置 off_6C8C08（供删除器与非虚成员调用）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_488400(uint8_t *this)  // 接口桩构造（虚表 off_6C8C08）
{
  *(this + 4) = 0;  // this+16〔nChannelTypeSel(推断)〕
  *(uint32_t *)this = &off_6C8C08;  // 写 vftable 指针 off_6C8C08
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x488410 sub_488410 —— 接口桩删除器
//   经 ·sub_401000 析构桩（nengine::IObject 族）后按位释放。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_488410(uint8_t *Block, char pszArg2)  // 接口桩删除器
{
  sub_401000(Block);  // 【基础设施：nengine::IObject 构造/析构桩 + MSVC std::s…】
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x488440 sub_488440 —— 读盘画面装载（sprite/nowloading.img；失败 IMAGE LOAD ERROR）
// ------------------------------------------------------------
DWORD /*usercall*/ sub_488440@<eax>(int nArg1@<esi>)  // 实现：读盘画面装载（sprite/nowloading.img；失败 IMAGE LOAD ERROR）
{
  char *pMem; // eax
  char *v2; // eax
  char v3; // cl
  DWORD result; // eax
  int pObj; // eax
  int pObj4; // eax
  int pObj5; // eax
  int pObj3; // eax
  int pObj2; // eax
  char *Block; // [esp+0h] [ebp-54h]
  void *Blocka; // [esp+0h] [ebp-54h]
  char Buffer[64]; // [esp+4h] [ebp-50h] BYREF
  int dword_796E502; // [esp+44h] [ebp-10h]
  int v14; // [esp+50h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  SetCursor(nullptr);
  if ( dword_99FD64 == 0 )
  {
    sprintf(Buffer, "sprite/nowloading.img");  // 字符串 “sprite/nowloading.img”
    pMem = (char *)operator new(0x68u);  // 堆分配 104 字节对象
    Block = pMem;
    v14 = 0;
    v2 = pMem != nullptr ? sub_4198A0(pMem, dword_79C0A4, Buffer) : nullptr;  // 读 dword_79C0A4（全局渲染器对象）
    dword_99FD64 = (int)v2;
    v3 = v2[4];
    v14 = -1;
    if ( v3 == 0 )
      off_77F3FC("IMAGE LOAD ERROR [%s]", Buffer);  // 字符串 “IMAGE LOAD ERROR [%s]”
  }
  result = timeGetTime() - dword_99FD7C;  // result = 调 timeGetTime
  if ( result > 0x64 )  // 比较常量 0x64（= 100（百分比基数））
  {
    (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_79C0B0 + 28))(dword_79C0B0, 0, nArg1);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 84))(dword_79C0B0, Block);  // 调虚槽 +84：CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
    pObj = sub_418DD0((uint32_t *)dword_99FD64, 0);  // 调 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 152))(pObj, 0, 0, dword_79C0B0);  // 调虚槽 +152：效果通道 3
    Blocka = (void *)dword_99FD78;
    pObj4 = sub_418DD0((uint32_t *)dword_99FD64, 2u);  // 调 资源句柄 (101)
    if ( pObj4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, void *, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        pObj4,
        278,
        53,
        dword_79C0B0,  // 默认字体/绘制资源
        1065353216,  // 常量 1.0f
        1065353216,  // 常量 1.0f
        Blocka,
        -1,
        1333788672,
        1333788672);
    dword_99FD7C = timeGetTime();  // dword_99FD7C = 调 timeGetTime
    *(float *)&dword_99FD78 = *(float *)&dword_99FD78 + 0.0099999998;  // 常量 0.01f
    pObj5 = sub_418DD0((uint32_t *)dword_99FD64, 1u);  // 调 资源句柄 (101)
    if ( pObj5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, 194, 60, dword_79C0B0);  // 调虚槽 +152：效果通道 3
    pObj3 = sub_418DD0((uint32_t *)dword_99FD64, 3u);  // 调 资源句柄 (101)
    if ( pObj3 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        pObj3,
        79,
        292,
        dword_79C0B0,  // 默认字体/绘制资源
        1065353216,  // 常量 1.0f
        1065353216,  // 常量 1.0f
        0,
        -1929379841,
        1333788672,
        1333788672);
    pObj2 = sub_418DD0((uint32_t *)dword_99FD68, 0);  // 调 资源句柄 (101)
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, 79, 292, dword_79C0B0);  // 调虚槽 +152：效果通道 3
    if ( dword_99FCCC != 0 )
      sub_488970(dword_99FD6C);  // 版本串渲染 Ver. 200606130k0515（2006-06-13 · k0515）
    (*(void (/*thiscall*/ **)(int, void *))(*(uint32_t *)dword_79C0B0 + 88))(dword_79C0B0, Blocka);  // 调虚槽 +88：CNRDPrivateStoreWindow__vmt58 槽（16 行）
    return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_79C0A4 + 4))(dword_79C0A4, 0, 0);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  }
  return result;
}



// ------------------------------------------------------------
// 0x488670 sub_488670 —— 视口重置 640x480
//   pArg1[12]/[13] 置 0、[14] 置 640、[15] 置 480；全库 33 处 UI/场景初始化调用（参数多为渲染器 dword_79C0B0）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_488670(uint32_t *pArg1)  // 视口重置 640x480
{
  pArg1[12] = 0;
  pArg1[13] = 0;
  pArg1[14] = 640;
  pArg1[15] = 480;
  return pArg1;
}



// ------------------------------------------------------------
// 0x488690 sub_488690 —— 按分隔符切分字符串为 token 数组
//   从 pArg2 起反复 strstr 定界 SubStr，把每段经 ·sub_41BFE0 构造 string 后由 ·sub_4206D0/·sub_420BB0 尾插进 pArg1，非空段另经 off_77F3FC 输出。
//   nArg4 为段数上限，末段余下内容也追加。【证据：login_channel 按 ? 切分登录串】
// ------------------------------------------------------------
void /*cdecl*/ sub_488690(uint32_t *pArg1, const char *pArg2, char *SubStr, int nArg4)  // 实现：按分隔符切分字符串为 token 数组
{
  int v4; // ecx
  unsigned int v5; // eax
  const char *psz2; // ebx
  const char *psz3; // edi
  char *pFound; // eax
  size_t psz; // eax
  size_t psz4; // ebx
  int v11; // ecx
  unsigned int v12; // edx
  unsigned int **v13; // edi
  void *v14; // [esp+4h] [ebp-118h] BYREF
  int i; // [esp+8h] [ebp-114h]
  char Destination[256]; // [esp+Ch] [ebp-110h] BYREF
  int dword_796E502; // [esp+10Ch] [ebp-10h]
  int v18; // [esp+118h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  sub_4017E0((int)pArg1);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  for ( i = 0; ; i += psz4 + strlen(SubStr) )  // 调 求串长
  {
    if ( nArg4 != 0 )
    {
      v4 = pArg1[1];
      v5 = v4 != 0 ? (pArg1[2] - v4) >> 2 : 0;
      if ( v5 >= nArg4 - 1 )
        break;
    }
    psz2 = pArg2;
    psz3 = &pArg2[i];
    pFound = strstr(&pArg2[i], SubStr);  // pFound = 调 strstr
    if ( pFound == nullptr )  // 若 pFound 为空
      goto LABEL_19;
    psz = &pFound[-i] - psz2;
    psz4 = psz;
    if ( psz != 0 )
    {
      strncpy(Destination, psz3, psz);  // 调 限长串拷贝
      Destination[psz4] = 0;
      v14 = nullptr;
      sub_41BFE0(&v14, Destination);  // 驻留字符串设置（set(const char*)）
      v11 = pArg1[1];
      v18 = 0;
      if ( v11 != 0 )
        v12 = (pArg1[2] - v11) >> 2;
      else
        v12 = 0;
      if ( v11 != 0 && v12 < (pArg1[3] - v11) >> 2 )
      {
        v13 = (unsigned int **)pArg1[2];
        sub_41FFE0(v13, 1, (unsigned int **)&v14);  // 驻留句柄区间填充 nArg2 个元素
        pArg1[2] = v13 + 1;
      }
      else
      {
        sub_4206D0(pArg1[2], 1, &v14);  // vector 中间插入（4 字节元素）
      }
      v18 = -1;
      sub_41B010(&v14);  // 驻留句柄析构（引用计数减到 0 释放）
      off_77F3FC(Destination);  // 引擎日志输出函数(printf 风格)
    }
  }
  psz2 = pArg2;
LABEL_19:
  if ( strlen(&psz2[i]) != 0 )  // 调 求串长
  {
    pArg2 = nullptr;
    sub_41BFE0((void **)&pArg2, &psz2[i]);  // 驻留字符串设置（set(const char*)）
    v18 = 1;
    sub_420BB0(&pArg2);  // vector push_back（4 字节元素）
    v18 = -1;
    sub_41B010((void **)&pArg2);  // 驻留句柄析构（引用计数减到 0 释放）
  }
}



// ------------------------------------------------------------
// 0x488870 sub_488870 —— CNRDTutorialTip 计数清零
//   +4293/+4034/+4035/+4292 计数与 +1 选中下标清零（·sub_433C40 构造时调用）。
// ------------------------------------------------------------
int /*thiscall*/ sub_488870(uint32_t *this)  // 实现：CNRDTutorialTip 计数清零
{
  *(this + 4293) = 0;
  *(this + 4034) = 0;
  *(this + 4035) = 0;
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 4292) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x488890 sub_488890 —— CNRDTutorialTip 按优先级加权随机抽取条目
//   遍历条目：level（+4036 区）大于 10 的权重置 0，其余累加 priority（+4228 区）得总和；rand 取模后在累加序列中定位，返回 1 起的条目下标。
// ------------------------------------------------------------
int /*thiscall*/ sub_488890(uint32_t *this)  // 实现：CNRDTutorialTip 按优先级加权随机抽取条目
{
  int fld_e4292; // edx
  int v3; // eax
  int v4; // esi
  uint32_t *pThis_1085; // ecx
  int v6; // edx
  int fld_e42922; // edi
  int result; // eax
  int v9; // edx
  int *i; // esi
  uint32_t v11[18]; // [esp+Ch] [ebp-48h] BYREF

  fld_e4292 = *(this + 4292);
  v11[17] = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v3 = 1;
  v4 = 0;
  if ( fld_e4292 >= 1 )
  {
    pThis_1085 = this + 4229;
    do
    {
      if ( (int)*(pThis_1085 - 192) > 10 )
      {
        *((uint8_t *)&v11[1] + v3) = 0;
      }
      else
      {
        v4 += *pThis_1085;
        *((uint8_t *)&v11[1] + v3) = 1;
      }
      ++v3;
      ++pThis_1085;
    }
    while ( v3 <= fld_e4292 );
  }
  v11[0] = rand();  // v11[0] = 调 rand
  v6 = sub_4D33A0(v11) % v4;  // 调 掷 0..9999
  fld_e42922 = *(this + 4292);
  result = 1;
  v9 = v6 + 1;
  if ( fld_e42922 < 1 )
    return 0;
  for ( i = this + 4229; v9 > *i; ++i )
  {
    v9 -= *i;
    if ( ++result > fld_e42922 )
      return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x488940 sub_488940 —— CNRDTutorialTip 四组 256 项数值表清零
//   +1 与 +4036/+4100/+4164/+4228 四组各 256 个 dword 清零（level 表与 priority 表）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_488940(uint32_t *this)  // CNRDTutorialTip 四组 256 项数值表清零
{
  uint32_t *result; // eax
  int i; // ecx

  *(this + 1) = 0;  // this+4〔宿主对象〕
  result = this + 4100;
  for ( i = 64; i != 0; --i )  // 循环：i 从 64 递减到 0
  {
    *(result - 64) = 0;
    *result = 0;
    result[64] = 0;
    result[128] = 0;
    ++result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x488970 sub_488970 —— ★版本串渲染 "Ver. 200606130k0515"（2006-06-13 · k0515）
// ------------------------------------------------------------
HGDIOBJ /*thiscall*/ sub_488970(uint32_t *this)  // 版本串渲染 Ver. 200606130k0515（2006-06-13 · k0515）
{
  int v2; // edx
  int fld_e1; // ecx
  int v4; // ecx
  int fld_e12; // eax
  unsigned int v6; // ecx
  int v7; // eax
  int v8; // eax
  HGDIOBJ result; // eax
  uint8_t v10[4]; // [esp+8h] [ebp-40h] BYREF
  int v11; // [esp+Ch] [ebp-3Ch]
  int v12; // [esp+14h] [ebp-34h]
  int v13; // [esp+18h] [ebp-30h]
  int v14; // [esp+1Ch] [ebp-2Ch]
  int v15; // [esp+20h] [ebp-28h]
  int v16; // [esp+24h] [ebp-24h]
  int v17; // [esp+28h] [ebp-20h]
  int v18; // [esp+2Ch] [ebp-1Ch]
  int v19; // [esp+30h] [ebp-18h]
  HGDIOBJ ho; // [esp+34h] [ebp-14h]
  int dword_99FCCC2; // [esp+38h] [ebp-10h]
  int v22; // [esp+44h] [ebp-4h]

  dword_99FCCC2 = dword_99FCCC;  // dword_99FCCC＝与字距
  v10[0] = 0;
  v10[1] = 0;
  v10[2] = 0;
  v10[3] = 0;
  v12 = 0;
  v13 = 6;
  v14 = 12;
  v15 = 0;
  v16 = 1600;
  v17 = 0;
  v18 = 0;
  v19 = 0;
  ho = nullptr;
  v11 = -16777216;
  v2 = *(uint32_t *)dword_79C0B0;  // 默认字体/绘制资源
  v22 = 0;
  (*(void (/*thiscall*/ **)(int, uint8_t *))(v2 + 72))(dword_79C0B0, v10);  // 默认字体/绘制资源
  fld_e1 = 28 * *(this + 1);  // this+4〔宿主对象〕
  if ( *(uint32_t *)((char *)this + fld_e1 + 32) < 0x10u )
    v4 = (int)this + fld_e1 + 12;
  else
    v4 = *(uint32_t *)((char *)this + fld_e1 + 12);
  (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    dword_79C0B0,  // 默认字体/绘制资源
    245,
    309,
    -13523457,
    "%s",  // 字符串 “%s”
    v4);
  fld_e12 = 28 * *(this + 1);  // this+4〔宿主对象〕
  v6 = *(uint32_t *)((char *)this + fld_e12 + 7200);
  v7 = (int)this + fld_e12 + 7176;
  if ( v6 < 0x10 )
    v8 = v7 + 4;
  else
    v8 = *(uint32_t *)(v7 + 4);
  (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    dword_79C0B0,  // 默认字体/绘制资源
    245,
    332,
    -2428169,
    "%s",  // 字符串 “%s”
    v8);
  (*(void (/*cdecl*/ **)(int, int, int, int, const char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    dword_79C0B0,  // 默认字体/绘制资源
    525,
    421,
    -328966,
    "Ver. 200606130k0515");  // 客户端版本串（2006-06-13 · k0515）
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
  result = ho;
  if ( ho != nullptr )  // 若 ho 有效（非空）
    return (HGDIOBJ)DeleteObject(ho);  // 调 删除 GDI 对象
  return result;
}



// ------------------------------------------------------------
// 0x488AB0 sub_488AB0 —— ★TutorialTip.etc 解析器
//   标签：[no]→条目索引 v3；[priority] A/B/C → 条目+4228 = 3/2/1；[level] → 条目+4036+no；
//   [title]/[content]/[image] → 字符串字段（sub_443370）；[end] → 结束。
//   条目计数 → 对象+4292；随后 sub_488890 修正首页 id（1/26 → 25）。
// ------------------------------------------------------------
char /*thiscall*/ sub_488AB0(uint32_t *this)  // 实现：TutorialTip.etc 解析器
{
  uint32_t *pThis; // edi
  char result; // al
  int v3; // esi
  int v4; // ecx
  const char *v5; // esi
  int v6; // eax
  int v8; // [esp+8h] [ebp-4Ch]
  uint8_t v9[4]; // [esp+Ch] [ebp-48h] BYREF
  void *Block; // [esp+10h] [ebp-44h]
  unsigned int v11; // [esp+20h] [ebp-34h]
  unsigned int v12; // [esp+24h] [ebp-30h]
  uint8_t v13[4]; // [esp+28h] [ebp-2Ch] BYREF
  void *v14; // [esp+2Ch] [ebp-28h] BYREF
  unsigned int v15; // [esp+3Ch] [ebp-18h]
  unsigned int v16; // [esp+40h] [ebp-14h]
  int dword_796E502; // [esp+44h] [ebp-10h]
  int v18; // [esp+50h] [ebp-4h]

  pThis = this;
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = sub_442A10((char)szPassword, (int)"Etc/TutorialTip.etc");  // 打开教程提示定义文件
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v16 = 15;
    v15 = 0;
    LOBYTE(v14) = 0;
    v18 = 1;
    v12 = 15;
    v11 = 0;
    LOBYTE(Block) = 0;
    v3 = v8;
    if ( (uint8_t)sub_443430(v13) != 0 )  // 读 token 到 string + 国家码标记
    {
      while ( 1 )
      {
        if ( v15 == 0 )
          goto LABEL_12;
        v4 = v15;
        if ( v15 >= 4 )
          v4 = 4;
        v5 = (const char *)v14;
        if ( v16 < 0x10 )
          v5 = (const char *)&v14;
        if ( memcmp(v5, "[no]", v4) != 0 || v15 != 4 )  // [no] → 条目索引 v3
          break;
        pThis = this;
        v3 = sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
        v8 = v3;
LABEL_27:
        if ( (uint8_t)sub_443430(v13) == 0 )  // 读 token 到 string + 国家码标记
          goto LABEL_28;
      }
      v3 = v8;
      pThis = this;
LABEL_12:
      if ( sub_40BF00((std::_String_base *)v13, 0, v15, "[priority]", 0xAu) != 0 )  // [priority]：A/B/C → 条目+4228 = 3/2/1
      {
        if ( sub_40BF00((std::_String_base *)v13, 0, v15, "[level]", 7u) != 0 )  // [level] → 条目+4036+no
        {
          if ( sub_40BF00((std::_String_base *)v13, 0, v15, "[title]", 7u) != 0  // [title]/[content]/[image] → 字符串字段
            && sub_40BF00((std::_String_base *)v13, 0, v15, "[content]", 9u) != 0  // 字符串 “[content]”
            && sub_40BF00((std::_String_base *)v13, 0, v15, "[image]", 7u) != 0 )  // 字符串 “[image]”
          {
            if ( (uint8_t)sub_423300(v13, "[end]") != 0 )  // [end] → 解析结束
              goto LABEL_28;
          }
          else
          {
            sub_443370();  // 脚本 token 取串（第三入口）
          }
        }
        else
        {
          pThis[v3 + 4036] = sub_4423D0(nullptr);  // [level] 值写入
        }
      }
      else
      {
        sub_443370();  // 脚本 token 取串（第三入口）
        if ( sub_40BF00((std::_String_base *)v9, 0, v11, "A", 1u) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          if ( sub_40BF00((std::_String_base *)v9, 0, v11, "B", 1u) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
          {
            if ( sub_40BF00((std::_String_base *)v9, 0, v11, "C", 1u) == 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
              pThis[v3 + 4228] = 1;
          }
          else
          {
            pThis[v3 + 4228] = 2;
          }
        }
        else
        {
          pThis[v3 + 4228] = 3;
        }
      }
      goto LABEL_27;
    }
LABEL_28:
    pThis[4292] = v3;  // 条目总数 → +4292
    v6 = sub_488890(pThis);  // 结果 = CNRDTutorialTip 按优先级加权随机抽取条目
    pThis[1] = v6;
    if ( v6 == 1 || v6 == 26 )  // 若 v6 == 1 与/或 v6 == 26
      pThis[1] = 25;
    if ( v12 >= 0x10 )
      j__free(Block);  // 调 堆释放
    v11 = 0;
    LOBYTE(Block) = 0;
    v12 = 15;
    if ( v16 >= 0x10 )
      j__free(v14);  // 调 堆释放
    return 1;  // 返回 1(成功)
  }
  return result;
}


// ============================================================
// §I 0x488D90-0x489800  网络包收发基础
// ============================================================
// ------------------------------------------------------------
// 0x488D90 sub_488D90 —— 28 字节记录构造（6 dword + 1 字节 + 1 dword）
//   依次写 +0..+16 五个参数、+20 字节 pszArg7、+24 nArg8。【推断：技能/物品条目与包记录共用此布局】
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_488D90(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, char pszArg7, int nArg8)  // 28 字节记录构造（6 dword + 1 字节 + 1 dword）
{
  *this = nArg2;
  *(this + 1) = nArg3;  // this+4〔宿主对象〕
  *(this + 2) = nArg4;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = nArg5;  // this+12〔nSkillRec12(推断)〕
  *(this + 4) = nArg6;  // this+16〔nChannelTypeSel(推断)〕
  *((uint8_t *)this + 20) = pszArg7;  // this+20〔nPage(推断)〕
  *(this + 6) = nArg8;  // this+24〔nPageMax(推断)〕
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x488DD0 sub_488DD0 —— 56 字节元素数组长度
//   元素步长 56：返回 (this+2 减 this+1) / 56，空容器返回 0（item/monster 解析器用于追加下标）。
// ------------------------------------------------------------
int /*thiscall*/ sub_488DD0(int *this)  // 实现：56 字节元素数组长度
{
  int result; // eax

  result = *(this + 1);  // this+4〔宿主对象〕
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(this + 2) - result) / 56;  // this+8〔nSkillRec8(推断)〕
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x488E00 sub_488E00 —— 28 字节元素原位构造
//   在 nArg1 + 28*nArg2 处经 ·sub_4FF0A0 构造记录并返回其地址。
// ------------------------------------------------------------
int /*stdcall*/ sub_488E00(int nArg1, int nArg2, int nArg3)  // 实现：28 字节元素原位构造
{
  sub_4FF0A0(nArg1, nArg2, nArg3);  // 调 构造记录并返回其地址
  return nArg1 + 28 * nArg2;
}



// ------------------------------------------------------------
// 0x488E30 sub_488E30 —— 红黑树插入与重平衡（另一节点布局）
//   与 ·0x4876E0 同构（差异：节点由 ·sub_5648C0 建立、颜色字节在 +20、旋转辅助为 ·sub_433130/·sub_4296E0，长度上限 0x1FFFFFFE）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_488E30(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)  // 红黑树插入与重平衡（另一节点布局）
{
  int fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
  int fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
  size_t v17; // [esp+34h] [ebp-28h] BYREF
  char v18; // [esp+38h] [ebp-24h]
  int v19; // [esp+48h] [ebp-14h]
  int v20; // [esp+4Ch] [ebp-10h]
  int v21; // [esp+58h] [ebp-4h]
  int fld_e15; // [esp+70h] [ebp+14h]

  if ( *(this + 2) >= 0x1FFFFFFEu )  // this+8〔nSkillRec8(推断)〕
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
    pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常
  }
  fld_e1 = sub_5648C0(*(this + 1), pArg4, *(this + 1), nArg5, 0);  // 结果 = 商店文本
  fld_e12 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( pArg4 == fld_e12 )  // fld_e12=this+4 宿主对象
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    *(uint32_t *)*(this + 1) = fld_e1;  // this+4〔宿主对象〕
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == (uint32_t *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // fld_e14=this+4 宿主对象
  }
  v10 = (uint32_t *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 20) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 20) != 0 )
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_433130(*v10);  // 红黑树左旋（节点 0x18 版）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // STL 内联红黑树节点摘除重连
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(*v10);  // STL 内联红黑树节点摘除重连
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // 红黑树左旋（节点 0x18 版）
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;  // 虚调用 vt+4
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;  // this+4〔宿主对象〕
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x488FE0 sub_488FE0 —— 包发送基础（sub_4735F0/472DB0 组包 → sub_488E00 发送）
// ------------------------------------------------------------
void /*thiscall*/ sub_488FE0(int *this, int pArg2, unsigned int uArg3, void *Block)  // 实现：包发送基础（sub_4735F0/472DB0 组包 → sub_488E00 发送）
{
  int pVecEnd_6; // edi
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  int v12; // edi
  int fld_e13; // eax
  unsigned int v14; // esi
  void *fld_e23; // ecx
  int fld_e26; // edx
  int fld_e12; // [esp-18h] [ebp-50h]
  int fld_e25; // [esp-Ch] [ebp-44h]
  int fld_e24; // [esp-8h] [ebp-40h]
  int v21; // [esp+0h] [ebp-38h] BYREF
  uint32_t v22[8]; // [esp+Ch] [ebp-2Ch] BYREF
  int v23; // [esp+34h] [ebp-4h]
  int v24; // [esp+40h] [ebp+8h]
  int v25; // [esp+44h] [ebp+Ch]
  char *Blocka; // [esp+48h] [ebp+10h]
  void *Blockb; // [esp+48h] [ebp+10h]

  qmemcpy(v22, Block, 0x1Cu);  // 调 内存块拷贝(内联展开)
  pVecEnd_6 = *(this + 1);  // this+4〔宿主对象〕
  v22[7] = &v21;
  if ( pVecEnd_6 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - pVecEnd_6) / 28;  // this+12〔nSkillRec12(推断)〕
  else
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( pVecEnd_6 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - *(this + 1)) / 28;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
    if ( 153391689 - fld_e2 < uArg3 )  // fld_e2=this+8 nSkillRec8
      sub_4735F0(this);  // 调 抛 std::length_error(vector<T> too long)（vector 扩容上限辅助）
    if ( *(this + 1) != 0 )  // this+4〔宿主对象〕
      fld_e22 = (*(this + 2) - *(this + 1)) / 28;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e23 = (void *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
      Blockb = fld_e23;  // fld_e23=this+8 nSkillRec8
      if ( ((int)fld_e23 - pArg2) / 28 >= uArg3 )  // fld_e23=this+8 nSkillRec8
      {
        v24 = (int)fld_e23 - 28 * uArg3;  // fld_e23=this+8 nSkillRec8
        *(this + 2) = sub_472DB0(v24, fld_e23, fld_e23);  // this+8〔nSkillRec8(推断)〕
        sub_4FF020(pArg2, v24, Blockb);
        sub_4FEFA0(pArg2, pArg2 + 28 * uArg3, v22);
      }
      else
      {
        sub_472DB0(pArg2, fld_e23, pArg2 + 28 * uArg3);  // 调 pszArg3，返回新游标
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 28;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
        v23 = 2;
        sub_488E00(fld_e25, fld_e24, (int)v22);  // 28 字节元素原位构造
        fld_e26 = 28 * uArg3 + *(this + 2);  // this+8〔nSkillRec8〕
        *(this + 2) = fld_e26;  // this+8〔nSkillRec8(推断)〕
        sub_4FEFA0(pArg2, fld_e26 - 28 * uArg3, v22);
      }
    }
    else
    {
      if ( 153391689 - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 nSkillRec12
        v10 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 nSkillRec12
      else
        v10 = 0;
      if ( *(this + 1) != 0 )  // this+4〔宿主对象〕
        fld_e27 = (*(this + 2) - *(this + 1)) / 28;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_e27 = 0;  // fld_e27=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_e27 )  // fld_e27=this+8 nSkillRec8
        v10 = uArg3 + sub_52AEF0(this);  // 调 v10 = 插入数 + sub_52AEF0
      v12 = 28 * v10;
      Blocka = (char *)operator new(28 * v10);  // 分配 28 × v10 字节数组
      fld_e12 = *(this + 1);  // this+4〔宿主对象〕
      v23 = 0;
      v25 = sub_472DB0(fld_e12, pArg2, Blocka);  // 调 pszArg3，返回新游标
      sub_4FF0A0(v25, uArg3, v22);  // 调 构造记录并返回其地址
      sub_472DB0(pArg2, *(this + 2), 28 * uArg3 + v25);  // this+8〔nSkillRec8(推断)〕
      fld_e13 = *(this + 1);  // this+4〔宿主对象〕
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 28;  // this+8〔nSkillRec8(推断)〕
      v14 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )  // this+4〔宿主对象〕
        j__free((void *)*(this + 1));  // this+4〔宿主对象〕
      *(this + 3) = (int)&Blocka[v12];  // this+12〔nSkillRec12(推断)〕
      *(this + 2) = (int)&Blocka[28 * v14];  // this+8〔nSkillRec8(推断)〕
      *(this + 1) = (int)Blocka;  // this+4〔宿主对象〕
    }
  }
}



// ------------------------------------------------------------
// 0x4892B0 sub_4892B0 —— 包发送（sub_488E30 变体 + sub_4A3B30）
// ------------------------------------------------------------
int /*thiscall*/ sub_4892B0(uint32_t *this, int pArg2, uint32_t *uArg3)  // 实现：包发送（sub_488E30 变体 + sub_4A3B30）
{
  uint32_t *uArg32; // ebx
  uint32_t *fld_e1; // esi
  int *v6; // eax
  bool v7; // cl
  int v8; // edx
  uint32_t *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  uArg32 = uArg3;
  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v6 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )
  {
    v8 = *uArg3;
    do
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;  // fld_e1=this+4 宿主对象
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  uArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )  // this+4〔宿主对象〕
    {
      v10 = *sub_488E30(this, &uArg3, 1, fld_e1, (int)uArg32);  // 结果 = 红黑树插入与重平衡（另一节点布局）
      *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_4A3B30(&uArg3);  // 调 取后继再插
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // pArg2+4〔宿主对象〕
    *(uint32_t *)pArg2 = fld_e12;  // *pArg2 = fld_e12
    return pArg2;
  }
  else
  {
    v12 = *sub_488E30(this, &uArg3, v13, fld_e1, (int)uArg32);  // 结果 = 红黑树插入与重平衡（另一节点布局）
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x489370 sub_489370 —— 28 字节记录插入并回传地址
//   按下标换算插入位置后由 ·sub_488FE0 插入 1 条 28 字节记录，回传新记录地址。
//   【推断】·sub_488FE0 旧注记为包发送基础，但函数体实为 28 字节元素 _Insert_n（含 ·sub_4735F0 判长抛出、·sub_472DB0 搬移）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_489370(int *this, uint32_t *uArg2, int nArg3, void *Block)  // 28 字节记录插入并回传地址
{
  int pVecEnd_5; // esi
  int v6; // esi

  pVecEnd_5 = *(this + 1);  // this+4〔宿主对象〕
  if ( pVecEnd_5 != 0 && (*(this + 2) - pVecEnd_5) / 28 != 0 )  // this+8〔nSkillRec8(推断)〕
    v6 = (nArg3 - pVecEnd_5) / 28;  // pVecEnd_5=this+4 宿主对象
  else
    v6 = 0;
  sub_488FE0(this, nArg3, 1u, Block);  // 包发送基础（sub_4735F0/472DB0 组包 → sub_488E00 发送）
  *uArg2 = *(this + 1) + 28 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x4893E0 sub_4893E0 —— 红黑树按键插入定位
//   空树直接 ·sub_488E30 插入；否则按键与左右边界比较分派插入侧向（·sub_4A3B30/·sub_41C5E0 求前驱后继），必要时回落 ·sub_4892B0 复用既有节点。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4893E0(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)  // 红黑树按键插入定位
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
  {
    sub_488E30((uint32_t *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);  // 红黑树插入与重平衡（另一节点布局）
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_488E30((uint32_t *)this, uArg2, 1, pArg3, (int)pArg4);  // 红黑树插入与重平衡（另一节点布局）
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    v8 = (uint32_t *)fld_4[2];  // fld_4=this+16 nChannelTypeSel
    if ( v8[3] < *pArg4 )
    {
      sub_488E30((uint32_t *)this, uArg2, 0, v8, (int)pArg4);  // 红黑树插入与重平衡（另一节点布局）
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4A3B30(&pArg4), pArg4[3] >= *pArg42) )  // 若 pArg4 = pArg3
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_41C5E0((int *)&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )  // 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4892B0((uint32_t *)this, (int)v10, pArg42);  // 结果 = 包发送（sub_488E30 变体 + sub_4A3B30）
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 21) != 0 )
      sub_488E30((uint32_t *)this, uArg2, 0, pArg3, (int)pArg42);  // 红黑树插入与重平衡（另一节点布局）
    else
      sub_488E30((uint32_t *)this, uArg2, 1, pArg4, (int)pArg42);  // 红黑树插入与重平衡（另一节点布局）
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 21) != 0 )
      sub_488E30((uint32_t *)this, uArg2, 0, pArg4, (int)pArg42);  // 红黑树插入与重平衡（另一节点布局）
    else
      sub_488E30((uint32_t *)this, uArg2, 1, pArg3, (int)pArg42);  // 红黑树插入与重平衡（另一节点布局）
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x489540 sub_489540 —— 16 字节元素区间拷贝
//   把 [nArg1, nArg2) 逐条经 ·sub_4ED3F0 拷贝到 nArg3 起空间，返回新尾指针。
// ------------------------------------------------------------
int /*cdecl*/ sub_489540(int nArg1, int nArg2, int nArg3)  // 实现：16 字节元素区间拷贝
{
  int nArg12; // esi
  int nArg32; // edi

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    sub_4ED3F0(nArg32, nArg12);  // int 向量拷贝赋值（全容量路径）
    nArg12 += 16;
    nArg32 += 16;
  }
  while ( nArg12 != nArg2 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x489580 sub_489580 —— 28 字节元素尾插
//   容量足够时经 ·sub_4FF0A0 原位构造并推进 this+2；否则回落 ·sub_489370 插入。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_489580(int *this, void *Block)  // 28 字节元素尾插
{
  int pVecEnd_6; // ebx
  unsigned int fld_e2; // esi
  int fld_e22; // esi
  uint32_t *result; // eax

  pVecEnd_6 = *(this + 1);  // this+4〔宿主对象〕
  if ( pVecEnd_6 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - pVecEnd_6) / 28;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( pVecEnd_6 == 0 || fld_e2 >= (*(this + 3) - pVecEnd_6) / 28 )  // this+12〔nSkillRec12(推断)〕
    return sub_489370(this, &Block, *(this + 2), Block);  // 28 字节记录插入并回传地址
  fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  result = (uint32_t *)sub_4FF0A0(fld_e22, 1, Block);  // 调 构造记录并返回其地址
  *(this + 2) = fld_e22 + 28;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x489610 sub_489610 —— 红黑树按键取值（键缺则按 0 值插入）
//   按键沿红黑树下行（左子 +0、右子 +8、键 +12、哨兵位 +21）；命中回载荷 +16，
//   未命中经 ·sub_4893E0 插入 {键, 0} 后回载荷 +16；树实例 dword_99FBA4（·sub_4896B0 即其写入器）。
// ------------------------------------------------------------
int /*thiscall*/ sub_489610(uint32_t *this, uint32_t *uArg2)  // 实现：红黑树按键取值（键缺则按 0 值插入）
{
  uint32_t *fld_e1; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v3 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  while ( *((uint8_t *)v3 + 21) == 0 )  // 当 *((uint8_t *)v3 + 21) == 0 循环
  {
    if ( v3[3] >= *uArg2 )
    {
      fld_e1 = v3;  // fld_e1=this+4 宿主对象
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  if ( fld_e1 != (uint32_t *)*(this + 1) && *uArg2 >= fld_e1[3] )  // this+4〔宿主对象〕
    return (int)(fld_e1 + 4);  // fld_e1=this+4 宿主对象
  v5[0] = *uArg2;
  v5[1] = 0;
  return *sub_4893E0((int)this, &uArg2, fld_e1, v5) + 16;  // 红黑树按键插入定位
}



// ------------------------------------------------------------
// 0x489690 sub_489690 —— 16 字节元素区间拷贝·转发
//   —— 直接转发 ·sub_489540（逐条经 ·sub_4ED3F0 拷贝），无附加逻辑。
// ------------------------------------------------------------
int /*cdecl*/ sub_489690(int nArg1, int nArg2, int nArg3)  // 实现：16 字节元素区间拷贝·转发
{
  return sub_489540(nArg1, nArg2, nArg3);  // 16 字节元素区间拷贝
}



// ------------------------------------------------------------
// 0x4896B0 sub_4896B0 —— 全局键表 dword_99FBA4 建键写值
//   取键 nArg1 的载荷（缺则插入）后写值 nArg2，返回载荷指针；即该表的写入器。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4896B0(int nArg1, int nArg2)  // 全局键表 dword_99FBA4 建键写值
{
  uint32_t *result; // eax

  result = (uint32_t *)sub_489610(&dword_99FBA4, &nArg1);  // 结果 = 红黑树按键取值（键缺则按 0 值插入）
  *result = nArg2;
  return result;
}



// ------------------------------------------------------------
// 0x4896D0 sub_4896D0 —— 16 字节元素区间删除（前移覆盖后收缩）
//   把 [nArg4, 尾) 经 ·sub_489540 前移到 nArg3 起，腾出的尾段由 ·sub_42CC00 释放，尾指针回落；
//   区间起点状态回填 pDwArg2（erase 返回新尾语义）。
// ------------------------------------------------------------
int */*thiscall*/ sub_4896D0(int *this, int *pDwArg2, int nArg3, int nArg4)  // 16 字节元素区间删除（前移覆盖后收缩）
{
  int fld_e2; // edi

  if ( nArg3 != nArg4 )
  {
    fld_e2 = sub_489540(nArg4, *(this + 2), nArg3);  // 结果 = 16 字节元素区间拷贝
    sub_42CC00(fld_e2, *(this + 2));  // 16 字节槽组释放
    *(this + 2) = fld_e2;  // this+8〔nSkillRec8(推断)〕
  }
  *pDwArg2 = nArg3;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x489720 sub_489720 —— 16 字节元素容器重设长度（缩删/伸补）
//   长度已够则按 ·sub_4896D0 做区间删除；不足经 ·sub_474DE0 追加补位元素；
//   形参 Block 为移交缓冲，非空在此释放；·sub_4897D0 为以栈哑元填充的薄包装。
// ------------------------------------------------------------
void /*thiscall*/ sub_489720(int *this, unsigned int uArg2, char pszArg3, void *Block, int nArg5, int nArg6)  // 实现：16 字节元素容器重设长度（缩删/伸补）
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int fld_e22; // edx

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( fld_e2 >= uArg2 )  // fld_e2=this+8 nSkillRec8
  {
    if ( fld_e1 != 0 && uArg2 < (*(this + 2) - fld_e1) >> 4 )  // this+8〔nSkillRec8(推断)〕
      sub_4896D0(this, (int *)&uArg2, fld_e1 + 16 * uArg2, *(this + 2));  // 16 字节元素区间删除（前移覆盖后收缩）
  }
  else
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    sub_474DE0((int)this, (void *)*(this + 2), uArg2 - fld_e22, &pszArg3);  // 调 追加补位元素
  }
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 堆释放
}



// ------------------------------------------------------------
// 0x4897D0 sub_4897D0 —— 容器重设长度·薄包装
//   以栈上哑元走 ·sub_489720（Block 传空）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4897D0(int *this, unsigned int uArg2)  // 实现：容器重设长度·薄包装
{
  char v2; // [esp+0h] [ebp-14h] BYREF
  char *v3; // [esp+10h] [ebp-4h]

  v3 = &v2;
  sub_489720(this, uArg2, v2, nullptr, 0, 0);  // 16 字节元素容器重设长度（缩删/伸补）
}



// ============================================================
// §J 0x489800-0x48B700  ★★全局初始化 + DebugConfig.txt + 测试角色
// ============================================================
// ------------------------------------------------------------
// 0x489800 sub_489800 —— ★★全局初始化 + DebugConfig.txt 解析
//   ../DebugConfig.txt 标签：[dungeon index][map index][path info][job][grow type]
//   [level][avatar][item][storage][mounted equipment][skill][cash][SP]
//   [test user number][user index][IP] —— 调试开局直接落图/发装/给技能。
//   随后测试角色命令："Allons y"/"CruelRogue"/"WindShadow" → sub_47B150 生成测试角色。
// ------------------------------------------------------------
void /*thiscall*/ sub_489800(uint32_t *this)  // 实现：全局初始化 + DebugConfig.txt 解析
{
  unsigned int v1; // edx
  int v2; // ecx
  const char *p_Block; // esi
  int j; // esi
  int k; // esi
  int v6; // eax
  int m; // esi
  void *pMem; // eax
  int *v9; // eax
  int v10; // edx
  void *v11; // eax
  bool v12; // zf
  void **v13; // edi
  unsigned int n; // esi
  int v15; // eax
  void *v16; // edi
  int v17; // ebx
  int v18; // esi
  int pObj2; // ecx
  int pObj4; // esi
  struct TypeDescriptor *v21; // esi
  int v22; // edi
  uint32_t *v23; // eax
  const struct TypeDescriptor_vtbl *v24; // edx
  int v25; // eax
  int v26; // edi
  int ii; // edx
  int v28; // ebx
  int v29; // eax
  uint32_t *jj; // edx
  char *v31; // esi
  int v32; // edi
  int v33; // eax
  uint32_t *v34; // ecx
  uint32_t *v35; // edx
  uint32_t *v36; // edi
  int v37; // eax
  int v38; // edi
  int v39; // esi
  int v40; // edx
  int v41; // eax
  int kk; // eax
  int v43; // eax
  uint32_t *v44; // esi
  uint32_t *v45; // eax
  uint32_t *v46; // eax
  uint32_t *v47; // eax
  uint32_t *v48; // edi
  int v49; // eax
  unsigned int v50; // esi
  int v51; // edx
  int v52; // eax
  int v53; // esi
  int v54; // ecx
  int v55; // esi
  unsigned int v56; // edx
  uint32_t *v57; // eax
  int v58; // ecx
  int v59; // eax
  int v60; // eax
  int v61; // edx
  int v62; // ecx
  unsigned int v63; // esi
  int v64; // edx
  int v65; // ecx
  int v66; // ebx
  uint8_t *pMem22; // esi
  uint32_t *v68; // eax
  uint8_t *v69; // ecx
  unsigned int v70; // esi
  int *v71; // ebx
  int v72; // edi
  unsigned int v73; // esi
  int v74; // eax
  int v75; // eax
  char v76; // cl
  int *v77; // eax
  int v78; // edx
  int v79; // ecx
  int v80; // eax
  int v81; // eax
  void *v82; // edx
  int v83; // edi
  int v84; // ebx
  int v85; // esi
  void *v86; // eax
  unsigned int i1; // edi
  int v88; // ecx
  int v89; // eax
  unsigned int v90; // edi
  int v91; // eax
  int *v92; // eax
  int v93; // edx
  int pObj3; // ebx
  unsigned int i2; // esi
  int v96; // edx
  int v97; // edx
  int v98; // edi
  int nRand; // eax
  int v100; // eax
  int v101; // eax
  int i3; // edi
  int v103; // esi
  int v104; // eax
  int pObj; // eax
  int v106; // edx
  char *v107; // edi
  int v108; // esi
  int v109; // ecx
  int v110; // edx
  int v111; // ecx
  int v112; // esi
  int v113; // edi
  int v114; // eax
  int v115; // edi
  int v116; // eax
  int *v117; // esi
  int v118; // edx
  void *v119; // edi
  int nRand3; // eax
  int nRand2; // eax
  int v122; // edx
  int v123; // eax
  uint32_t *dword_8F853C2; // ecx
  int i4; // edi
  int v126; // esi
  int v127; // eax
  int v128; // eax
  int v129; // ebx
  int i5; // edi
  int v131; // esi
  struct TypeDescriptor *v132; // eax
  uint16_t v133; // dx
  int v134; // ebx
  int i6; // edi
  int v136; // esi
  struct TypeDescriptor *v137; // eax
  int v138; // ecx
  int v139; // eax
  uint32_t *v140; // ecx
  int v141; // eax
  int v142; // ebx
  int v143; // esi
  int i7; // edi
  struct TypeDescriptor *v145; // edi
  int i8; // esi
  int v147; // eax
  int v148; // eax
  int v149; // esi
  int v150; // esi
  int v151; // esi
  int v152; // eax
  int v153; // eax
  int v154; // eax
  int v155; // eax
  int v156; // eax
  int v157; // eax
  int v158; // eax
  int v159; // eax
  int v160; // eax
  int v161; // eax
  int v162; // eax
  int v163; // eax
  int v164; // [esp-10h] [ebp-254h] BYREF
  int v165; // [esp-Ch] [ebp-250h]
  int v166; // [esp-8h] [ebp-24Ch]
  int v167; // [esp-4h] [ebp-248h]
  uint8_t v168[64]; // [esp+Ch] [ebp-238h] BYREF
  int v169; // [esp+4Ch] [ebp-1F8h] BYREF
  char v170[14]; // [esp+50h] [ebp-1F4h] BYREF
  char v171[14]; // [esp+5Eh] [ebp-1E6h] BYREF
  char v172[14]; // [esp+6Ch] [ebp-1D8h] BYREF
  char v173[14]; // [esp+7Ah] [ebp-1CAh] BYREF
  int v174; // [esp+8Ch] [ebp-1B8h]
  int v175; // [esp+90h] [ebp-1B4h]
  int v176; // [esp+94h] [ebp-1B0h]
  uint8_t v177[64]; // [esp+98h] [ebp-1ACh] BYREF
  void *v178; // [esp+DCh] [ebp-168h]
  int v179; // [esp+E0h] [ebp-164h]
  int v180; // [esp+E4h] [ebp-160h]
  void *v181; // [esp+ECh] [ebp-158h]
  int v182; // [esp+F0h] [ebp-154h]
  int v183; // [esp+F4h] [ebp-150h]
  void *v184; // [esp+FCh] [ebp-148h]
  uint32_t *v185; // [esp+100h] [ebp-144h]
  int v186; // [esp+104h] [ebp-140h]
  void *v187; // [esp+10Ch] [ebp-138h]
  char *v188; // [esp+110h] [ebp-134h]
  int v189; // [esp+114h] [ebp-130h]
  int v190; // [esp+118h] [ebp-12Ch] BYREF
  int v191; // [esp+11Ch] [ebp-128h]
  int v192; // [esp+120h] [ebp-124h]
  int v193; // [esp+124h] [ebp-120h]
  int v194; // [esp+128h] [ebp-11Ch]
  uint32_t v195[4]; // [esp+12Ch] [ebp-118h] BYREF
  uint8_t *v196; // [esp+13Ch] [ebp-108h]
  uint32_t *v197; // [esp+140h] [ebp-104h] BYREF
  void *pMem2; // [esp+144h] [ebp-100h]
  int v199; // [esp+148h] [ebp-FCh]
  int v200; // [esp+14Ch] [ebp-F8h] BYREF
  int v201; // [esp+150h] [ebp-F4h]
  int v202; // [esp+154h] [ebp-F0h] BYREF
  int v203; // [esp+158h] [ebp-ECh] BYREF
  void *v204; // [esp+15Ch] [ebp-E8h]
  int v205; // [esp+160h] [ebp-E4h] BYREF
  uint32_t *pThis; // [esp+164h] [ebp-E0h]
  int v207; // [esp+168h] [ebp-DCh] BYREF
  int mm; // [esp+16Ch] [ebp-D8h] BYREF
  uint32_t *v209; // [esp+170h] [ebp-D4h]
  void *nn; // [esp+174h] [ebp-D0h]
  char ArgList[4]; // [esp+178h] [ebp-CCh]
  uint32_t *i; // [esp+17Ch] [ebp-C8h] BYREF
  int v213; // [esp+180h] [ebp-C4h] BYREF
  char v214; // [esp+187h] [ebp-BDh] BYREF
  uint8_t v215[28]; // [esp+188h] [ebp-BCh] BYREF
  void *v216; // [esp+1A4h] [ebp-A0h]
  uint16_t v217[39]; // [esp+1C8h] [ebp-7Ch] BYREF
  char v218; // [esp+216h] [ebp-2Eh]
  char v219; // [esp+217h] [ebp-2Dh] BYREF
  char v220[4]; // [esp+218h] [ebp-2Ch] BYREF
  void *Block; // [esp+21Ch] [ebp-28h] BYREF
  unsigned int v222; // [esp+22Ch] [ebp-18h]
  unsigned int v223; // [esp+230h] [ebp-14h]
  int dword_796E502; // [esp+234h] [ebp-10h]
  int v225; // [esp+240h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  pThis = this;
  dword_8F84B0 = 0;  // dword_8F84B0＝缺省值
  v199 = 0;
  v213 = 1;
  *(uint32_t *)ArgList = 0;  // *ArgList = 0
  nn = nullptr;
  v204 = nullptr;
  v192 = 0;
  v194 = 0;
  v181 = nullptr;
  v182 = 0;
  v183 = 0;
  v225 = 3;
  v184 = nullptr;
  v185 = nullptr;
  v186 = 0;
  v187 = nullptr;
  v188 = nullptr;
  v189 = 0;
  v174 = 0;
  v175 = 0;
  v176 = 0;
  `eh vector constructor iterator'(v177, 0x10u, 4, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);  // 指针 vector 三字段清零（起/止/容量 = 0）
  LOBYTE(v225) = 4;
  `eh vector constructor iterator'(v168, 0x10u, 4, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);  // 指针 vector 三字段清零（起/止/容量 = 0）
  v207 = 0;
  v205 = 0;
  v193 = 1;
  v200 = 0;
  v178 = nullptr;
  v179 = 0;
  v180 = 0;
  LOBYTE(v225) = 6;
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"../DebugConfig.txt") == 0 )  // 调试配置（标签族见函数头）
  {
    LOBYTE(v225) = 4;
    `eh vector destructor iterator'(v168, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
    LOBYTE(v225) = 3;
    `eh vector destructor iterator'(v177, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
    return;
  }
  v223 = 15;
  v222 = 0;
  LOBYTE(Block) = 0;
  LOBYTE(v225) = 7;
  v214 = 0;
  if ( (uint8_t)sub_443430(v220) == 0 )  // 读 token 到 string + 国家码标记
    goto LABEL_70;
  do
  {
    v1 = v222;
    if ( v222 != 0 )
    {
      v2 = v222;
      if ( v222 >= 0xF )
        v2 = 15;
      p_Block = (const char *)Block;
      if ( v223 < 0x10 )
        p_Block = (const char *)&Block;
      if ( memcmp(p_Block, "[dungeon index]", v2) == 0 && v222 == 15 )  // [dungeon index] 调试落图
      {
        v199 = sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
        continue;
      }
      v1 = v222;
    }
    if ( sub_40BF00((std::_String_base *)v220, 0, v1, "[map index]", 0xBu) != 0 )  // [map index]
    {
      if ( sub_40BF00((std::_String_base *)v220, 0, v222, "[path info]", 0xBu) != 0 )  // 字符串 “[path info]”
      {
        if ( sub_40BF00((std::_String_base *)v220, 0, v222, "[job]", 5u) != 0 )  // [job]
        {
          if ( sub_40BF00((std::_String_base *)v220, 0, v222, "[grow type]", 0xBu) != 0 )  // [grow type]
          {
            if ( sub_40BF00((std::_String_base *)v220, 0, v222, "[level]", 7u) != 0 )  // [level]
            {
              if ( (uint8_t)sub_423300(v220, "[avatar]") != 0 )  // 字符串 “[avatar]”
              {
                for ( i = (uint32_t *)sub_4423D0(&v214); v214 != 0; i = (uint32_t *)sub_4423D0(&v214) )  // 调 [LOOP] → 动画对象+160
                  sub_431230(&i);  // uint32 vector push_back
              }
              else if ( (uint8_t)sub_423300(v220, "[item]") != 0 )  // 字符串 “[item]”
              {
                for ( j = sub_4423D0(&v214); v214 != 0; j = sub_4423D0(&v214) )  // 调 [LOOP] → 动画对象+160
                {
                  pMem2 = (void *)sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
                  v197 = (uint32_t *)j;
                  sub_474950(&v197);  // 调 调用 sub_474950
                }
              }
              else if ( (uint8_t)sub_423300(v220, "[storage]") != 0 )  // 字符串 “[storage]”
              {
                for ( k = sub_4423D0(&v214); v214 != 0; k = sub_4423D0(&v214) )  // 调 [LOOP] → 动画对象+160
                {
                  v6 = sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
                  v190 = k;
                  v191 = v6;
                  sub_474950(&v190);  // 调 调用 sub_474950
                }
              }
              else if ( (uint8_t)sub_423300(v220, "[mounted equipment]") != 0 )  // 字符串 “[mounted equipment]”
              {
                sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
                for ( i = (uint32_t *)sub_4423D0(&v214); v214 != 0; i = (uint32_t *)sub_4423D0(&v214) )  // 调 [LOOP] → 动画对象+160
                  sub_431230(&i);  // uint32 vector push_back
              }
              else if ( (uint8_t)sub_423300(v220, "[skill]") != 0 )  // 字符串 “[skill]”
              {
                sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
                for ( m = sub_4423D0(&v214); v214 != 0; m = sub_4423D0(&v214) )  // 调 [LOOP] → 动画对象+160
                {
                  v203 = sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
                  v202 = m;
                  sub_474950(&v202);  // 调 调用 sub_474950
                }
              }
              else if ( (uint8_t)sub_423300(v220, "[cash]") != 0 )  // 字符串 “[cash]”
              {
                v207 = sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v220, "[SP]") != 0 )  // 字符串 “[SP]”
              {
                v205 = sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v220, "[test user number]") != 0 )  // [test user number]
              {
                v193 = sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v220, "[user index]") != 0 )  // 字符串 “[user index]”
              {
                v200 = sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
              }
              else if ( (uint8_t)sub_423300(v220, "[IP]") != 0 )  // 字符串 “[IP]”
              {
                for ( i = (uint32_t *)sub_4423D0(&v214); v214 != 0; i = (uint32_t *)sub_4423D0(&v214) )  // 调 [LOOP] → 动画对象+160
                  sub_431230(&i);  // uint32 vector push_back
              }
            }
            else
            {
              v194 = sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
            }
          }
          else
          {
            v192 = sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
          }
        }
        else
        {
          v204 = (void *)sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
        }
      }
      else
      {
        *(uint32_t *)ArgList = sub_4423D0(nullptr);  // *ArgList = 调 sub_4423D0 返回值
        nn = (void *)sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
      }
    }
    else
    {
      v213 = sub_4423D0(nullptr);  // 调 [LOOP] → 动画对象+160
    }
  }
  while ( (uint8_t)sub_443430(v220) != 0 );  // 读 token 到 string + 国家码标记
  if ( v199 == -1 )
  {
    sub_429E30(v215);  // CNUser 构造（串 + clong 初始化）
    LOBYTE(v225) = 8;
    v216 = v204;
    pMem = operator new(0x294u);  // 堆分配 660 字节对象
    pMem2 = pMem;
    LOBYTE(v225) = 9;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v9 = (int *)sub_42B0F0(pMem);  // 结果 = CNRDVirtualCharacter 构造（10×16 子对象）
    else
      v9 = nullptr;
    v10 = *v9;
    LOBYTE(v225) = 8;
    (*(void (/*thiscall*/ **)(int *, uint8_t *))(v10 + 348))(v9, v215);  // 调虚槽 +348：取坐标对象
    sub_46B150(pThis[4]);  // 频道栏选中恢复与提示文本
    LOBYTE(v225) = 7;
    sub_41CBF0(v215);  // 成员析构（两个 std::string + crypt4byte 子对象）
    if ( v223 >= 0x10 )
      j__free(Block);  // 调 堆释放
    v223 = 15;
    v222 = 0;
    LOBYTE(Block) = 0;
    if ( v178 != nullptr )  // 若 v178 有效（非空）
      j__free(v178);  // 调 堆释放
    LOBYTE(v225) = 4;
    `eh vector destructor iterator'(v168, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
    LOBYTE(v225) = 3;
    `eh vector destructor iterator'(v177, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
    if ( v187 != nullptr )  // 若 v187 有效（非空）
      j__free(v187);  // 调 堆释放
    if ( v184 != nullptr )  // 若 v184 有效（非空）
      j__free(v184);  // 调 堆释放
    v11 = v181;
    v12 = v181 == nullptr;
    goto LABEL_255;
  }
  if ( v199 != -2 )
  {
    if ( v199 != 0 )
      v167 = 3;
    else
LABEL_70:
      v167 = 1;
    sub_41D300(v167);  // 模块切换 setter → 0x41CC80(onChangeModule) 转发
  }
  v13 = (void **)v181;
  for ( n = 0; v13 != nullptr && n < (v182 - (int)v13) >> 2; ++n )
  {
    v15 = sub_522300(v13[n], 12300, 0, 0, -1, 1);  // 调 存 ★ PO 工厂分发器
    sub_484F40(n, v15, 1);  // 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
  }
  mm = 1;
  v209 = v184;
  if ( v184 != v185 )
  {
    do
    {
      v16 = (void *)*v209;
      v17 = v209[1];
      v18 = sub_484E80(*v209);  // 结果 = 按类型查找下标（同一匹配规则，未命中 -1）
      if ( v18 == -1
        || (v18 >= *((uint32_t *)dword_8F852C + 2)  // 全局 dword_8F852C = 角色/物品栏管理器
          ? (pObj2 = 0)  // ★★全局初始化 + DebugConfig.txt 解析
          : (pObj2 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v18)),  // 全局 dword_8F852C = 角色/物品栏管理器
            (*(uint8_t (/*thiscall*/ **)(int, void *))(*(uint32_t *)pObj2 + 60))(pObj2, v16) == 0) )  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      {
        v21 = (struct TypeDescriptor *)sub_522300(v16, v17, 0, 0, -1, 1);  // 调 存 ★ PO 工厂分发器
        if ( (*((uint8_t (/*thiscall*/ **)(struct TypeDescriptor *, int))v21->__vftable + 5))(v21, 2) != 0 )  // 虚函数调用 槽+5
        {
          v22 = mm;
          v23 = sub_4E9B10(&v169, 0, mm, 0, -1);  // 结果 = 与 ·0x4E9A50 同构（差异：随后按 5 参赋初值）
          v24 = v21->__vftable;
          LOBYTE(v225) = 10;
          (*((void (/*thiscall*/ **)(struct TypeDescriptor *, uint32_t *))v24 + 46))(v21, v23);  // 虚函数调用 槽+46
          mm = v22 + 1;
          LOBYTE(v225) = 7;
          sub_445150(&v169);  // 调 装备同步资源清理
        }
        v25 = sub_547350(v21);  // 结果 = 物品栏条目
        v26 = *((uint32_t *)dword_8F852C + 2);  // 全局 dword_8F852C = 角色/物品栏管理器
        for ( ii = 3; ii < 9; ++ii )  // 循环：ii 从 3 递增到 9
        {
          if ( ii < v26 )
          {
            v28 = *((uint32_t *)dword_8F852C + 3);  // 全局 dword_8F852C = 角色/物品栏管理器
            if ( *(uint32_t *)(v28 + 4 * ii) != 0 )
              continue;
          }
          v167 = 1;
          v166 = (int)v21;
          v165 = ii;
          goto LABEL_98;
        }
        v29 = 32 * v25 + 9;
        for ( jj = (uint32_t *)(v28 + 4 * v29); v29 < v26 && *jj != 0; ++jj )
          ++v29;
        v167 = 1;
        v166 = (int)v21;
        v165 = v29;
LABEL_98:
        sub_484F40(v165, v166, v167);  // 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
      }
      else if ( v18 >= *((uint32_t *)dword_8F852C + 2) )  // 全局 dword_8F852C = 角色/物品栏管理器
      {
        (*(void (/*thiscall*/ **)(uint32_t, int))(MEMORY[0] + 48))(0, v17);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
      }
      else
      {
        pObj4 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v18);  // 全局 dword_8F852C = 角色/物品栏管理器
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 48))(pObj4, v17);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
      }
      v209 += 2;
    }
    while ( v209 != v185 );
  }
  v31 = (char *)v187;
  v32 = 0;
  if ( v187 != v188 )
  {
    do
    {
      v33 = sub_522300(*(void **)v31, *((uint32_t *)v31 + 1), 0, 0, -1, 1);  // 调 存 ★ PO 工厂分发器
      sub_484F40(v32, v33, 1);  // 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
      v31 += 8;
      ++v32;
    }
    while ( v31 != v188 );
  }
  v34 = *(uint32_t **)&v168[16 * (uint32_t)v204 + 4];
  v35 = *(uint32_t **)&v168[16 * (uint32_t)v204 + 8];
  v201 = 16 * (uint32_t)v204;
  v209 = v34;
  v203 = (int)&v168[16 * (uint32_t)v204 + 8];
  if ( v34 != v35 )
  {
    do
    {
      v36 = v209;
      v37 = sub_47E720(v204, *v209);  // 调 调 sub_47E720
      v38 = v36[1];
      v39 = v37;
      if ( sub_47DCC0(v37) >= v38 )
        v41 = v38;
      else
        v41 = sub_47DCC0(v39);
      sub_41A590(v39 + 496, v40, v41);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      if ( *(uint32_t *)(v39 + 124) != 0 )
      {
LABEL_111:
        for ( kk = 42 * sub_41A5E0(v39 + 128) + 6;  // crypt4byte 解密校验（·0x41A590 逆运算）
              kk < *(uint32_t *)dword_8F853C && *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * kk) != 0;  // 容器对象指针(容量比较)
              ++kk )
        {
          ;
        }
      }
      else
      {
        kk = 0;
        while ( kk < *(uint32_t *)dword_8F853C && *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * kk) != 0 )  // 容器对象指针(容量比较)
        {
          if ( ++kk >= 6 )
            goto LABEL_111;
        }
      }
      sub_483D50(kk, v39);  // 技能槽绑定（替换索引 nArg2 处对象，旧对象解引用）
      v12 = v209 + 2 == *(uint32_t **)v203;
      v209 += 2;
    }
    while ( !v12 );
  }
  Value = v205;
  dword_8F7C0C = v207;  // 全局 dword_8F7C0C = 现金(Cash)
  word_8F7C14 = 100;  // 全局 word_8F7C14 = 疲劳上限
  LOWORD(word_77F804) = v200;  // 全局 word_77F804 = 本机身份键(ServerId)
  v43 = pThis[3];
  v44 = nullptr;
  i = nullptr;
  v203 = 0;
  if ( v43 != 1 )
  {
    if ( v43 != 3 )
    {
      if ( v199 == -2 )
      {
        v44 = *(uint32_t **)(pThis[8] + 16);
        i = v44;
      }
      goto LABEL_178;
    }
    dword_9B0AB0 = (int)&dword_9B0C08;  // dword_9B0AB0＝表基址
    i = *(uint32_t **)(pThis[7] + 16);
    v48 = (uint32_t *)sub_476B60(v199);  // 调 存 选区角色数据查找
    dword_99FB8C = 2;
    v197 = nullptr;
    v49 = v48[42];
    v207 = (int)v48;
    pMem2 = nullptr;
    if ( v49 != 0 )
    {
      v50 = (v48[43] - v49) >> 3;
      if ( v50 != 0 )
      {
        if ( v50 > 1 )
        {
          v52 = v49 + 8;
          if ( v52 != v48[43] )
            v48[43] = v52;
        }
        goto LABEL_127;
      }
      v51 = (v48[43] - v49) >> 3;
    }
    else
    {
      v51 = 0;
    }
    sub_473A80(v48[43], 1 - v51, &v197);  // 调 扩容插入
LABEL_127:
    *(uint32_t *)v48[42] = 3;
    *(uint32_t *)(v48[42] + 4) = 3;
    pMem2 = &v164;
    sub_489720(1, v164, nullptr, 0, 0);  // 16 字节元素容器重设长度（缩删/伸补）
    v53 = v48[46];
    if ( *(uint32_t *)(v53 + 4) != 0 )
      j__free(*(void **)(v53 + 4));  // 调 堆释放
    *(uint32_t *)(v53 + 4) = 0;
    *(uint32_t *)(v53 + 8) = 0;
    *(uint32_t *)(v53 + 12) = 0;
    v205 = 15;
    for ( mm = 9; mm != 0; --mm )  // 循环：mm 从 9 递减到 0
    {
      v54 = v48[46];
      v55 = *(uint32_t *)(v54 + 4);
      if ( v55 != 0 )
        v56 = (*(uint32_t *)(v54 + 8) - v55) >> 2;
      else
        v56 = 0;
      if ( v55 != 0 && v56 < (*(uint32_t *)(v54 + 12) - v55) >> 2 )
      {
        v57 = *(uint32_t **)(v54 + 8);
        *v57 = 15;
        *(uint32_t *)(v54 + 8) = v57 + 1;
      }
      else
      {
        sub_430C80(*(void **)(v54 + 8), 1, (int)&v205);  // uint32 vector 区间插入（同值填充）
      }
    }
    sub_4755F0(nullptr);  // 调 按关卡尺寸
    if ( nn == (void *)100 )
    {
      dword_99FB7C = 1;
      dword_99FB80 = 0;
    }
    else
    {
      dword_99FB7C = 2;
      dword_99FB80 = 2;
    }
    v58 = v213;
    i[27] = v48;
    v59 = dword_99FBB4 + 36;
    *(uint32_t *)(dword_99FBB4 + 36) = v58;
    mm = v59;
    v60 = sub_4CE8A0(v58);  // 调 调用 sub_4CE8A0
    v61 = *(uint32_t *)(v60 + 24);
    v213 = v60;
    if ( v61 != 0 && (*(uint32_t *)(v60 + 28) - v61) >> 3 != 0 )
    {
      v62 = *(uint32_t *)(v60 + 24);
      if ( v62 != 0 )
        v63 = (*(uint32_t *)(v60 + 28) - v62) >> 3;
      else
        v63 = 0;
      v64 = *(uint32_t *)ArgList % v63;
      v65 = *(uint32_t *)(v213 + 24);
      v66 = *(uint32_t *)(v65 + 8 * (*(uint32_t *)ArgList % v63) + 4);
      pMem22 = nullptr;
      pMem2 = nullptr;
      *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v207 + 184) + 4) + 4) = *(uint32_t *)(v65 + 8 * v64);
      v68 = nullptr;
      v69 = nullptr;
      v196 = nullptr;
      v197 = nullptr;
      LOBYTE(v225) = 11;
      if ( (v66 & 4) != 0 )  // 若 v66 位 4 测试
      {
        v203 = 0;
        sub_430C80(nullptr, 1, (int)&v203);  // uint32 vector 区间插入（同值填充）
        pMem22 = pMem2;
        v68 = v197;
        v69 = v196;
      }
      if ( (v66 & 1) != 0 )  // 若 v66 位 1 测试
      {
        v203 = 1;
        if ( v69 != nullptr && ((char *)v68 - v69) >> 2 < (unsigned int)((pMem22 - v69) >> 2) )
        {
          *v68++ = 1;
          v197 = v68;
        }
        else
        {
          sub_430C80(v68, 1, (int)&v203);  // uint32 vector 区间插入（同值填充）
          pMem22 = pMem2;
          v68 = v197;
          v69 = v196;
        }
      }
      if ( (v66 & 2) != 0 )  // 若 v66 位 2 测试
      {
        v203 = 2;
        if ( v69 != nullptr && ((char *)v68 - v69) >> 2 < (unsigned int)((pMem22 - v69) >> 2) )
        {
          *v68++ = 2;
          v197 = v68;
        }
        else
        {
          sub_430C80(v68, 1, (int)&v203);  // uint32 vector 区间插入（同值填充）
          pMem22 = pMem2;
          v68 = v197;
          v69 = v196;
        }
      }
      if ( (v66 & 8) != 0 )  // 若 v66 位 8 测试
      {
        v203 = 3;
        if ( v69 != nullptr && ((char *)v68 - v69) >> 2 < (unsigned int)((pMem22 - v69) >> 2) )
        {
          *v68++ = 3;
        }
        else
        {
          sub_430C80(v68, 1, (int)&v203);  // uint32 vector 区间插入（同值填充）
          v68 = v197;
          v69 = v196;
        }
      }
      if ( v69 != nullptr )  // 若 v69 有效（非空）
        v70 = ((char *)v68 - v69) >> 2;
      else
        v70 = 0;
      LOBYTE(v225) = 7;
      v203 = *(uint32_t *)&v69[4 * ((unsigned int)nn % v70)];
      if ( v69 != nullptr )  // 若 v69 有效（非空）
        j__free(v69);  // 调 堆释放
    }
    else
    {
      *(uint32_t *)(*(uint32_t *)(v48[46] + 4) + 4) = 15;
    }
    v71 = (int *)v207;
    v72 = v213;
    v73 = 0;
    for ( *(uint32_t *)ArgList = 0; ; *(uint32_t *)ArgList += 56 )
    {
      v74 = *(uint32_t *)(v72 + 64);
      if ( v74 == 0 || v73 >= (*(uint32_t *)(v72 + 68) - v74) / 56 )
        break;
      v75 = *(uint32_t *)(v72 + 64);
      v76 = *(uint8_t *)(v75 + *(uint32_t *)ArgList + 4);
      v77 = (int *)(*(uint32_t *)ArgList + v75);
      v78 = *v77;
      v12 = v76 == 0;
      v79 = v77[2];
      if ( !v12 )
        v79 += v71[28];
      v195[3] = v79;
      v196 = (uint8_t *)v77[9];
      v195[2] = v78;
      v195[0] = v73;
      v195[1] = v73;
      LOBYTE(v197) = 0;
      pMem2 = nullptr;
      sub_489580(v195);  // 28 字节元素尾插
      ++v73;
    }
    sub_475810(v71, v73, 1, 0);  // 调 半还原范围（前半主干），完整逻辑待 P5 专项
    v44 = i;
    sub_4284C0(1, 0);  // 场景格切换装配
    sub_425960(0, v44[11], v44[26]);  // 播放/暂停级联广播
    goto LABEL_178;
  }
  sub_45D190(ArgList[0], nn);  // 进入/切换房间（DOOR_SHUT 自证）
  v44 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
  i = v44;
  v213 = 1;
  v45 = (uint32_t *)sub_489610(&v213);  // 结果 = 红黑树按键取值（键缺则按 0 值插入）
  v167 = (int)&v213;
  *v45 = 2;
  v213 = 2;
  *(uint32_t *)sub_489610(v167) = 2;  // 红黑树按键取值（键缺则按 0 值插入）
  v213 = 3;
  v46 = (uint32_t *)sub_489610(&v213);  // 结果 = 红黑树按键取值（键缺则按 0 值插入）
  v167 = (int)&v213;
  *v46 = 3;
  v213 = 4;
  v47 = (uint32_t *)sub_489610(v167);  // 结果 = 红黑树按键取值（键缺则按 0 值插入）
  v167 = (int)&v213;
  *v47 = 3;
  v213 = 5;
  *(uint32_t *)sub_489610(v167) = 2;  // 红黑树按键取值（键缺则按 0 值插入）
  v213 = 6;
  *(uint32_t *)sub_489610(&v213) = 1;  // 红黑树按键取值（键缺则按 0 值插入）
  sub_47D1E0(1015);  // 调 按 ID uArg2 注销：sub_4CE8A0 解析出对象后经 sub_44E2F0 从表 this+5 移除
  sub_47D1E0(1011);  // 调 按 ID uArg2 注销：sub_4CE8A0 解析出对象后经 sub_44E2F0 从表 this+5 移除
  sub_47D1E0(1003);  // 调 按 ID uArg2 注销：sub_4CE8A0 解析出对象后经 sub_44E2F0 从表 this+5 移除
  sub_47D1E0(1002);  // 调 按 ID uArg2 注销：sub_4CE8A0 解析出对象后经 sub_44E2F0 从表 this+5 移除
  sub_47D1E0(1001);  // 调 按 ID uArg2 注销：sub_4CE8A0 解析出对象后经 sub_44E2F0 从表 this+5 移除
  sub_47D1E0(19);  // 调 按 ID uArg2 注销：sub_4CE8A0 解析出对象后经 sub_44E2F0 从表 this+5 移除
LABEL_178:
  v80 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
  v209 = (uint32_t *)v44[26];
  (*(void (/*thiscall*/ **)(int, uint32_t *))(v80 + 124))(dword_8F8520, v44);  // 会话/UDP 管理器
  for ( nn = nullptr; (int)nn < v193; nn = (char *)nn + 1 )
  {
    v81 = sub_42A100(nn);  // 结果 = CNUser 取或建（槽号索引）
    v82 = v204;
    v83 = v192;
    v84 = v81;
    v85 = v81 + 16;
    v167 = v194;
    v213 = v81;
    *(uint32_t *)(v81 + 44) = v204;
    *(uint32_t *)(v81 + 48) = v83;
    sub_41A590(v81 + 53, (int)v82, v167);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v86 = (void *)sub_4B0EC0(v204, v83);  // 结果 = 表记录字符串取值（28 字节/条）
    sub_4015C0(v86, strlen((const char *)v86));  // 【std::string构造赋值】
    *(uint32_t *)(v84 + 116) = 20;
    for ( i1 = 0; ; ++i1 )
    {
      v88 = *(uint32_t *)&v177[v201 + 4];
      if ( v88 == 0 || i1 >= (*(uint32_t *)&v177[v201 + 8] - v88) >> 2 )
        break;
      v89 = *(uint32_t *)(sub_4CE8A0(*(uint32_t *)(4 * i1 + *(uint32_t *)&v177[v201 + 4])) + 92);  // 调 调用 sub_4CE8A0
      if ( v89 <= 9 )
        *(uint32_t *)(v85 + 4 * v89 + 56) = *(uint32_t *)(*(uint32_t *)&v177[v201 + 4] + 4 * i1);  // 虚调用 vt+56
      v84 = v213;
    }
    v90 = (unsigned int)nn;
    sub_456300(nn, v84);  // 槽位绑定
    if ( v178 != nullptr && (v179 - (int)v178) >> 2 > v90 )
    {
      v91 = (*((uint32_t *)v178 + v90) << 24) + 43200;
      *(uint32_t *)(v84 + 160) = v91;
      *(uint32_t *)(v84 + 164) = v91;
      *(uint16_t *)(v84 + 168) = 5063;
    }
    v92 = (int *)sub_42B340(v213);  // 结果 = 虚拟角色惰性创建（0x294 字节）
    v93 = *v92;
    pMem2 = v92;
    (*(void (/*thiscall*/ **)(int *, int))(v93 + 348))(v92, v85);  // 调虚槽 +348：取坐标对象
    pObj3 = sub_579F90(v204);  // 结果 = 按职业 id 走对应后段
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 1044))(pObj3, v85);  // 调虚槽 +1044
    (*(void (/*thiscall*/ **)(int, void *))(*(uint32_t *)pObj3 + 1212))(pObj3, nn);  // 调虚槽 +1212：IRDCharacter__vmt4BC 默认虚槽桩（11 行 return）
    sub_42A3D0(pObj3);  // 本机实体绑定（dword_8F7C04）
    for ( i2 = 0; ; ++i2 )
    {
      v96 = *(uint32_t *)&v177[v201 + 4];
      if ( v96 == 0 || i2 >= (*(uint32_t *)&v177[v201 + 8] - v96) >> 2 )
        break;
      v97 = *(uint32_t *)&v177[v201 + 4];
      v98 = *(uint32_t *)pObj3;
      v167 = 0;
      v166 = (int)&CNRDEquipment `RTTI Type Descriptor';
      v165 = (int)&IRDItem `RTTI Type Descriptor';
      v164 = 0;
      v213 = v97 + 4 * i2;
      nRand = rand();  // nRand = 调 rand
      v100 = sub_522300(*(void **)v213, nRand, 0, 0, -1, 1);  // 调 存 ★ PO 工厂分发器
      v101 = __RTDynamicCast(v100, v164, (struct TypeDescriptor *)v165, (struct TypeDescriptor *)v166, v167);  // v101 = 调 __RTDynamicCast
      (*(void (/*thiscall*/ **)(int, int))(v98 + 784))(pObj3, v101);  // 虚函数调用 槽+784
    }
    for ( i3 = 0; i3 < 18; ++i3 )  // 循环：i3 从 0 递增到 18
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 1080))(pObj3, i3);  // 调虚槽 +1080
      if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 792))(pObj3, i3) != 0 )  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
      {
        v103 = sub_4E9C00(10, 0, 0, 10, 0);  // 结果 = 与 ·0x4E9A50 同构（差异：随后按 6 参逐个赋四 clong）
        v104 = *(uint32_t *)pObj3;
        LOBYTE(v225) = 12;
        pObj = (*(int (/*thiscall*/ **)(int, int))(v104 + 792))(pObj3, i3);  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 184))(pObj, v103);  // 调虚槽 +184：动画对象 z 倾斜转状态码
        LOBYTE(v225) = 15;
        sub_41A580(v173);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
        LOBYTE(v225) = 14;
        sub_41A580(v172);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
        LOBYTE(v225) = 13;
        sub_41A580(v171);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
        LOBYTE(v225) = 7;
        sub_41A580(v170);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
      }
    }
    v106 = sub_4CE8A0(v204);  // 调 调用 sub_4CE8A0
    qmemcpy(v217, (const void *)(v106 + 152), sizeof(v217));  // 调 内存块拷贝(内联展开)
    v107 = &v219;
    v108 = 0;
    v191 = v106;
    v218 = 100;
    v213 = 0;
    while ( 1 )
    {
      v109 = v194;
      if ( v108 != 0 )
      {
        if ( v194 <= 18 )
          break;
        v110 = 79 * v192 + v106 + 231;
        v111 = v194 - 18;
      }
      else
      {
        v110 = v106 + 231;
        if ( v194 > 18 )
          v109 = 18;
        v111 = v109 - 1;
      }
      *(uint32_t *)v217 += v111 * *(uint32_t *)v110;
      *(uint32_t *)&v217[2] += v111 * *(uint32_t *)(v110 + 4);
      v217[4] += v111 * *(uint16_t *)(v110 + 8);
      v217[5] += v111 * *(uint16_t *)(v110 + 10);
      v217[6] += v111 * *(uint16_t *)(v110 + 12);
      v217[7] += v111 * *(uint16_t *)(v110 + 14);
      v112 = 0;
      *(uint32_t *)ArgList = v110 + 16;  // *ArgList = v110 + 16
      do
      {
        v113 = *(uint32_t *)ArgList;
        v217[v112++ + 8] += v111 * **(uint16_t **)ArgList;
        *(uint32_t *)ArgList = v113 + 2;  // *ArgList = v113 + 2
      }
      while ( v112 < 4 );
      v114 = 0;
      *(uint32_t *)ArgList = v110 + 24;  // *ArgList = v110 + 24
      do
      {
        v115 = *(uint32_t *)ArgList;
        v217[v114++ + 12] += v111 * **(uint16_t **)ArgList;
        v107 = (char *)(v115 + 2);
        *(uint32_t *)ArgList = v107;  // *ArgList = v107
      }
      while ( v114 < 16 );
      *(uint32_t *)&v217[28] += v111 * *(uint32_t *)(v110 + 56);
      v217[30] += v111 * *(uint16_t *)(v110 + 60);
      v217[31] += v111 * *(uint16_t *)(v110 + 62);
      v217[32] += v111 * *(uint16_t *)(v110 + 64);
      v217[33] += v111 * *(uint16_t *)(v110 + 66);
      v217[34] += v111 * *(uint16_t *)(v110 + 68);
      v217[35] += v111 * *(uint16_t *)(v110 + 70);
      v217[36] += v111 * *(uint16_t *)(v110 + 72);
      *(uint32_t *)&v217[37] += v111 * *(uint32_t *)(v110 + 74);
      v108 = ++v213;
      if ( v213 >= 2 )
        break;
      v106 = v191;
    }
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)pObj3 + 1048))(pObj3, v217);  // 调虚槽 +1048
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 1056))(pObj3, 1);  // 调虚槽 +1056
    v116 = pThis[3];
    if ( v116 == 1 )
    {
      v117 = (int *)pMem2;
      sub_45FE80((int)v209, (int)v107, 18, (int)nn, (int)pMem2, 0, 0);  // 调 实体对象注册到演播层
      v118 = *v117;
      v205 = 100;
      v200 = 200;
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(v118 + 112))(v117, 100, 200, 0);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      (*(void (/*thiscall*/ **)(int *, int *, int *, int, int, int, int, int))(*v117 + 140))(  // 虚调用 vt+140
        v117,
        &v205,
        &v200,
        v205,
        v200,
        200,
        1,
        1);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(*v117 + 112))(v117, v205, v200, 0);  // 虚调用 vt+112
    }
    else if ( v116 == 3 )
    {
      v119 = nn;
      sub_45FE80((int)v209, (int)nn, 273, (int)nn, pObj3, 0, 0);  // 调 实体对象注册到演播层
      mm = 0;
      v207 = 0;
      if ( *(uint32_t *)(i[11] + 284) != 0 )
      {
        nRand2 = rand();  // nRand2 = 调 rand
        sub_48C330(&mm, &v207, pObj3, nRand2);  // 自身矩形内找落点（失败打 FIND POS FAIL）
      }
      else
      {
        nRand3 = rand();  // nRand3 = 调 rand
        sub_48C2A0(&mm, &v207, v203, pObj3, nRand3);  // 区域内找落点（失败打 FIND POS FAIL）
      }
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj3 + 112))(pObj3, mm, v207, 0);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 1120))(pObj3) != 0 )  // 调虚槽 +1120：IRDCharacter__vmt460 默认虚槽桩（10 行 return）
      {
        v122 = *(uint32_t *)pObj3;
        v167 = 0;
        v166 = 0;
        v123 = (*(int (/*thiscall*/ **)(int))(v122 + 1120))(pObj3);  // 调虚槽 +1120：IRDCharacter__vmt460 默认虚槽桩（10 行 return）
        sub_45FE80((int)v209, (int)v119, 65, (int)v119, v123, v166, v167);  // 调 实体对象注册到演播层
      }
      dword_8F853C2 = dword_8F853C;  // 容器对象指针(容量比较)
      for ( i4 = 0; i4 < *dword_8F853C2; ++i4 )
      {
        v126 = *(uint32_t *)(dword_8F853C2[1] + 4 * i4);
        if ( v126 != 0 )
        {
          pMem2 = (void *)sub_41A5E0(v126 + 496);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          v127 = sub_41A5E0(v126 + 4);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          (*(void (/*thiscall*/ **)(int, int, void *))(*(uint32_t *)pObj3 + 1136))(pObj3, v127, pMem2);  // 调虚槽 +1136
          dword_8F853C2 = dword_8F853C;  // 容器对象指针(容量比较)
        }
      }
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 1152))(pObj3);  // 调虚槽 +1152：CNSwordman__vmt480
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 1156))(pObj3);  // 调虚槽 +1156
    }
  }
  v128 = pThis[3];
  if ( v128 == 1 )
  {
    sub_45B140(pThis[5]);  // 刷新 ·+108 悬停记录
    sub_424A40(i, dword_8F7C08);  // 锚定角色 setter
    sub_47D1E0(1);  // 调 按 ID uArg2 注销：sub_4CE8A0 解析出对象后经 sub_44E2F0 从表 this+5 移除
    sub_47D9D0(dword_8F8540);  // 物品栏刷新器
    v167 = (uint16_t)word_77F804;  // 全局 word_77F804 = 本机身份键(ServerId)
    sub_656710();  // 取全局单例地址（返回 unk_9BD5D0）
    sub_6567B0(v167);  // 当前索引登记（宿主 +1096 + 缓冲刷新）
    v129 = 0;
    for ( i5 = 16; i5 < 32; i5 += 4 )
    {
      v131 = *(uint32_t *)(i5 + dword_8F850C);  // 全局 dword_8F850C = 房间/席位表
      if ( v131 != 0 && v131 != sub_429830((uint16_t)word_77F804) )  // 表按键查找（uint16）
      {
        v132 = *(struct TypeDescriptor **)(v131 + 8);
        v133 = *(uint16_t *)(v131 + 168);  // v133 = 读 v131+168 的 16 位值
        v167 = 0;
        v166 = (int)v132;
        v165 = v133;
        v164 = sub_42A380(1);  // 结果 = 四字节号格式化（四段十进制）
        sub_656710();  // 取全局单例地址（返回 unk_9BD5D0）
        sub_656880(v129, (void *)v164, v165, v166, v167);  // 通道对端登记（命令队列 opcode 1）
      }
      ++v129;
    }
    *(uint32_t *)(sub_656710() + 40) = 0;  // 取全局单例地址（返回 unk_9BD5D0）
  }
  else if ( v128 == 3 )
  {
    sub_47E4F0();  // 调 调用 sub_47E4F0
    *((uint8_t *)v209 + 152) = 1;
    v167 = (uint16_t)word_77F804;  // 全局 word_77F804 = 本机身份键(ServerId)
    sub_656710();  // 取全局单例地址（返回 unk_9BD5D0）
    sub_6567B0(v167);  // 当前索引登记（宿主 +1096 + 缓冲刷新）
    v134 = 0;
    for ( i6 = 16; i6 < 32; i6 += 4 )
    {
      v136 = *(uint32_t *)(i6 + dword_8F850C);  // 全局 dword_8F850C = 房间/席位表
      if ( v136 != 0 && v136 != sub_429830((uint16_t)word_77F804) )  // 表按键查找（uint16）
      {
        v137 = *(struct TypeDescriptor **)(v136 + 8);
        v138 = *(uint16_t *)(v136 + 168);  // v138 = 读 v136+168 的 16 位值
        v167 = 0;
        v166 = (int)v137;
        v165 = v138;
        v164 = sub_42A380(1);  // 结果 = 四字节号格式化（四段十进制）
        sub_656710();  // 取全局单例地址（返回 unk_9BD5D0）
        sub_656880(v134, (void *)v164, v165, v166, v167);  // 通道对端登记（命令队列 opcode 1）
      }
      ++v134;
    }
    v139 = sub_656710();  // 结果 = 取全局单例地址（返回 unk_9BD5D0）
    v140 = i;
    *(uint32_t *)(v139 + 40) = 0;
    sub_424A40(v140, dword_8F7C04);  // 锚定角色 setter
  }
  else if ( v199 == -2 )
  {
    v141 = sub_4879B0(1);  // 结果 = 按键取房间对象（缺则新建）
    v142 = v193;
    v143 = 0;
    for ( i7 = v141; v143 < v142; ++v143 )
      sub_48F700(v143, v143, v143 % 2 + 1);  // LADDER_DOWN 处理（梯子/下落状态、sub_452630/4529B0）
    sub_48FA30(0);  // 宿主切换·对象侧（@@SET HOST、LADDER_DOWN）
    v167 = i7;
    *(uint32_t *)(i7 + 116) = 1;
    sub_48F890(v167);  // 宿主切换 @@SET HOST %d 输出（sub_48F5A0 槽位、sub_4529B0
    sub_453050(2, 0);  // 阶段切换主控
  }
  *(uint32_t *)dword_99FB70 = 1;  // *dword_99FB70 = 1
  sub_47D060(1063, 0);  // 调 调用 sub_47D060
  sub_47D060(1062, 0);  // 调 调用 sub_47D060
  *(uint32_t *)dword_99FCD8 = -1010512201;  // *dword_99FCD8 = -1010512201
  dword_99FCE0 = -1045510470;  // 常量 0.20432f 位型
  dword_99FCDC = -1109932768;  // 常量 42.057495f 位型
  word_99FCE4 = 223;
  sub_456EB0((void *)1);  // 队伍条目取或建
  *(uint32_t *)(sub_4569F0(1) + 8) = 1;  // 队员槽查询
  v145 = nullptr;
  for ( i8 = 16; i8 < 32; i8 += 4 )
  {
    v147 = *(uint32_t *)(i8 + dword_8F850C);  // 全局 dword_8F850C = 房间/席位表
    if ( v147 != 0 )
      v148 = *(uint16_t *)(v147 + 4);  // v148 = 读 v147+4 的 16 位值
    else
      v148 = 0xFFFF;
    v167 = v148;
    v166 = (int)v145;
    sub_4569F0(1);  // 队员槽查询
    sub_56A6B0(v166, v167);  // 频道对象辅助 2（429830）
    v145 = (struct TypeDescriptor *)((char *)v145 + 1);
  }
  sub_41C270(1);  // 对 this+248 子对象做 crypt4byte 初始化
  sub_47B150(&unk_6C8D60, 13, 0, 0, 0);  // 调 写入 ──
  sub_47B150("[fighter]", 14, 1, 0, 0);  // 字符串 “[fighter]”
  sub_47B150("[gunner]", 13, 2, 0, 0);  // 字符串 “[gunner]”
  sub_47B150(&unk_6C8D58, 13, 0, 1, 0);  // 调 写入 ──
  sub_47B150(&unk_6C8D50, 14, 1, 1, 0);  // 调 写入 ──
  sub_47B150(&unk_6C8D48, 13, 2, 1, 0);  // 调 写入 ──
  sub_47B150(&unk_6C8D40, 13, 0, 2, 0);  // 调 写入 ──
  sub_47B150(&unk_6C8D38, 14, 1, 2, 0);  // 调 写入 ──
  sub_47B150(&unk_6C8D30, 13, 2, 2, 0);  // 调 写入 ──
  sub_47B150(&unk_6C8D28, 13, 0, 3, 0);  // 调 写入 ──
  sub_47B150(&unk_6C8D20, 14, 1, 3, 0);  // 调 写入 ──
  sub_47B150(&unk_6C8D18, 13, 2, 3, 0);  // 调 写入 ──
  v149 = sub_47B150(&unk_6C8D60, 13, 0, 0, 0);  // 调 写入 ──
  sprintf((char *const)(v149 + 52), &byte_6C8D10);  // 调 格式化到缓冲
  v167 = 0;
  v166 = 0;
  v165 = 1;
  v164 = 14;
  *(uint32_t *)(v149 + 40) = 12;
  v150 = sub_47B150("[fighter]", v164, v165, v166, v167);  // 字符串 “[fighter]”
  sprintf((char *const)(v150 + 52), &byte_6C8D08);  // 调 格式化到缓冲
  v167 = 0;
  v166 = 0;
  v165 = 2;
  v164 = 13;
  *(uint32_t *)(v150 + 40) = 10;
  v151 = sub_47B150("[gunner]", v164, v165, v166, v167);  // 字符串 “[gunner]”
  sprintf((char *const)(v151 + 52), &byte_6C8D08);  // 调 格式化到缓冲
  v167 = 0;
  v166 = 1;
  v165 = 0;
  v164 = 13;
  *(uint32_t *)(v151 + 40) = 5;
  v152 = sub_47B150(&unk_6C8D58, v164, v165, v166, v167);  // 调 写入 ──
  sprintf((char *const)(v152 + 52), &byte_6C8CFC);  // 调 格式化到缓冲
  v153 = sub_47B150(&unk_6C8D50, 14, 1, 1, 0);  // 调 写入 ──
  sprintf((char *const)(v153 + 52), &byte_6C8CFC);  // 调 格式化到缓冲
  v154 = sub_47B150(&unk_6C8D48, 13, 2, 1, 0);  // 调 写入 ──
  sprintf((char *const)(v154 + 52), &byte_6C8CF0);  // 调 格式化到缓冲
  v155 = sub_47B150(&unk_6C8D40, 13, 0, 2, 0);  // 调 写入 ──
  sprintf((char *const)(v155 + 52), &byte_6C8CF0);  // 调 格式化到缓冲
  v156 = sub_47B150(&unk_6C8D38, 14, 1, 2, 0);  // 调 写入 ──
  sprintf((char *const)(v156 + 52), &byte_6C8CF0);  // 调 格式化到缓冲
  v157 = sub_47B150(&unk_6C8D30, 13, 2, 2, 0);  // 调 写入 ──
  sprintf((char *const)(v157 + 52), &byte_6C8CF0);  // 调 格式化到缓冲
  v158 = sub_47B150(&unk_6C8D28, 13, 0, 3, 0);  // 调 写入 ──
  sprintf((char *const)(v158 + 52), &byte_6C8CF0);  // 调 格式化到缓冲
  v159 = sub_47B150(&unk_6C8D20, 14, 1, 3, 0);  // 调 写入 ──
  sprintf((char *const)(v159 + 52), &byte_6C8CF0);  // 调 格式化到缓冲
  v160 = sub_47B150(&unk_6C8D18, 13, 2, 3, 0);  // 调 写入 ──
  sprintf((char *const)(v160 + 52), &byte_6C8CF0);  // 调 格式化到缓冲
  sub_4015C0("Allons y", 8u);  // 调试测试角色名 → sub_47B150 生成
  v161 = sub_47B150(&unk_6C8CDC, 38, 1, 0, 0);  // 调 写入 ──
  v167 = 0;
  v166 = 0;
  v165 = 1;
  v164 = 27;
  *(uint32_t *)(v161 + 40) = 5;
  sub_47B150(&unk_6C8CD4, v164, v165, v166, v167);  // 调 写入 ──
  v162 = sub_47B150(&unk_6C8CCC, 20, 1, 0, 0);  // 调 写入 ──
  v167 = 0;
  v166 = 0;
  v165 = 1;
  v164 = 10;
  *(uint32_t *)(v162 + 40) = 12;
  sub_47B150(&unk_6C8D48, v164, v165, v166, v167);  // 调 写入 ──
  v163 = sub_47B150("CruelRogue", 5, 1, 0, 0);  // 字符串 “CruelRogue”
  v167 = 0;
  v166 = 0;
  v165 = 1;
  v164 = 2;
  *(uint32_t *)(v163 + 40) = 23;
  sub_47B150("WindShadow", v164, v165, v166, v167);  // 字符串 “WindShadow”
  (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 48))(  // 全局 dword_8F852C = 角色/物品栏管理器
    **((uint32_t **)dword_8F852C + 3),  // 全局 dword_8F852C = 角色/物品栏管理器
    100000);
  sub_50D920(0);  // 仓储栏类型设置（非法档位报错）
  if ( v223 >= 0x10 )
    j__free(Block);  // 调 堆释放
  v223 = 15;
  v222 = 0;
  LOBYTE(Block) = 0;
  if ( v178 != nullptr )  // 若 v178 有效（非空）
    j__free(v178);  // 调 堆释放
  LOBYTE(v225) = 4;
  `eh vector destructor iterator'(v168, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
  LOBYTE(v225) = 3;
  `eh vector destructor iterator'(v177, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
  if ( v187 != nullptr )  // 若 v187 有效（非空）
    j__free(v187);  // 调 堆释放
  if ( v184 != nullptr )  // 若 v184 有效（非空）
    j__free(v184);  // 调 堆释放
  v11 = v181;
  v12 = v181 == nullptr;
LABEL_255:
  if ( !v12 )
    j__free(v11);  // 调 堆释放
}


// ============================================================
// §K 0x48B700-0x48C070  调试控制台窗口（ID/CH/IsDebuggerPresent）
// ============================================================
// ------------------------------------------------------------
// 0x48B700 sub_48B700 —— 调试控制台窗口对象清零初始化
//   清 +4 关联指针、+8 名字、+40 ID 串、+104 CH 串、+168/+172 计数位（§K 调试控制台族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_48B700(int this)  // 实现：调试控制台窗口对象清零初始化
{
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint8_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint8_t *)(this + 104) = 0;  // this+104〔nTimerEnd(推断)〕
  *(uint32_t *)(this + 168) = 0;  // this+168〔pAppendVec(推断)〕等 2 字段
  *(uint32_t *)(this + 172) = 0;  // this+172〔pAppendVecEnd(推断)〕等 2 字段
  return 0;
}



// ------------------------------------------------------------
// 0x48B720 sub_48B720 —— 释放 +4 关联对象并置空
//   经其虚表首项以参数 1 析构 +4 对象（scalar deleting 形态），随后 +4 = 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_48B720(uint32_t *this)  // 实现：释放 +4 关联对象并置空
{
  int (/*thiscall*/ ***fld_e1)(uint32_t, int); // ecx
  int result; // eax

  fld_e1 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != nullptr )  // 若 fld_e1 有效（非空）
    result = (**fld_e1)(fld_e1, 1);  // 调 fld_e1 的虚函数（vt+0）
  *(this + 1) = 0;  // this+4〔宿主对象〕
  return result;
}



// ------------------------------------------------------------
// 0x48B740 sub_48B740 —— 调试配置项读取并夹取上下限
//   键值经 ·sub_57A100（CBIniFile 桩）读出，再夹到 dword_6C8ED0/6C8ED4 标定的 [下限, 上限]。
//   dword_6C8E30[项] 非 0 时短路回 0【推断：该项已屏蔽】；段按项号选（≤0 走 lpAppName、1..17 走 +40、>17 走 +104）。
// ------------------------------------------------------------
int /*thiscall*/ sub_48B740(const CHAR *this, int nArg2)  // 实现：调试配置项读取并夹取上下限
{
  int result; // eax
  const CHAR *pThis_28; // eax
  int v4; // ecx
  int v5; // edx

  if ( dword_6C8E30[nArg2] != 0 )
    return 0;
  if ( nArg2 > 0 )
  {
    pThis_28 = this + 40;  // this+40 物品状态附属标志
    if ( nArg2 > 17 )
      pThis_28 = this + 104;  // this+104 插值终点 Z
  }
  else
  {
    pThis_28 = lpAppName;  // pThis_28=this+104 插值终点 Z
  }
  result = sub_57A100(pThis_28, (&lpKeyName)[nArg2], nDefault[nArg2]);  // 结果 = CBIniFile 桩
  v4 = dword_6C8ED4[2 * nArg2];
  v5 = v4;
  if ( v4 >= result )
    v5 = result;
  if ( dword_6C8ED0[2 * nArg2] > v5 )
    return dword_6C8ED0[2 * nArg2];  // 返回 取 dword_6C8ED0[2 * nArg2]
  if ( v4 < result )
    return dword_6C8ED4[2 * nArg2];  // 返回 取 dword_6C8ED4[2 * nArg2]
  return result;
}



// ------------------------------------------------------------
// 0x48B7C0 sub_48B7C0 —— 调试配置项写入并刷新（·sub_48B830 联动）
//   经 ·sub_57A180（CBIniFile 桩）写值，返回 1 视为成功；段选同 ·sub_48B740；dword_6C8E30[项] 非 0 短路 false。
//   写毕调 ·sub_48B830(项号) 把该项落全局。
// ------------------------------------------------------------
bool /*thiscall*/ sub_48B7C0(const CHAR *this, int nArg2, int nArg3)  // 实现：调试配置项写入并刷新（·sub_48B830 联动）
{
  const CHAR *pThis_28; // eax
  bool v5; // bl

  if ( dword_6C8E30[nArg2] != 0 )
    return false;
  if ( nArg2 > 0 )
  {
    pThis_28 = this + 40;  // this+40 物品状态附属标志
    if ( nArg2 > 17 )
      pThis_28 = this + 104;  // this+104 插值终点 Z
  }
  else
  {
    pThis_28 = lpAppName;  // pThis_28=this+104 插值终点 Z
  }
  v5 = sub_57A180(pThis_28, (&lpKeyName)[nArg2], nArg3) == 1;  // 结果 = CBIniFile 桩
  sub_48B830(nArg2);  // 调试配置项应用分派（项号 → 全局开关）
  return v5;
}



// ------------------------------------------------------------
// 0x48B830 sub_48B830 —— 调试配置项应用分派（项号 → 全局开关）
//   case 0 校验 ID 文件（内容非 1 即 DeleteFileA 并回写 1）；case 1 → byte_790AD0 帧绘总开关。
//   case 7 → dword_9A0114 且 dword_9B8880 非 0 时 ·sub_69CE50；case 9/10 → 分辨率/刷新率（·sub_5621D0/·sub_5621F0）；case 8 → ·sub_657920 且 +24 = dword_79692C 乘 0.001。
// ------------------------------------------------------------
char /*thiscall*/ sub_48B830(int this, int nArg2)  // 实现：调试配置项应用分派（项号 → 全局开关）
{
  int v2; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax

  LOBYTE(v2) = nArg2;
  if ( nArg2 != 0 )
  {
    switch ( nArg2 )  // 按 nArg2 分派
    {
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        v2 = sub_48B740((const CHAR *)this, 1);  // 结果 = 调试配置项读取并夹取上下限
        byte_790AD0 = v2 != 0;  // byte_790AD0＝全局开关
        break;
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
LABEL_23:
        break;
      case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
        v2 = sub_48B740((const CHAR *)this, 7);  // 结果 = 调试配置项读取并夹取上下限
        dword_9A0114 = v2;
        if ( dword_9B8880 != 0 )
          LOBYTE(v2) = sub_69CE50(v2);
        break;
      case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
        v4 = sub_48B740((const CHAR *)this, 9);  // 结果 = 调试配置项读取并夹取上下限
        LOBYTE(v2) = sub_5621D0(v4);  // 分辨率切换（65D990）
        break;
      case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
        v5 = sub_48B740((const CHAR *)this, 10);  // 结果 = 调试配置项读取并夹取上下限
        LOBYTE(v2) = sub_5621F0(v5);  // 刷新率切换（65D8F0）
        break;
      case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
        v6 = sub_48B740((const CHAR *)this, 8);  // 结果 = 调试配置项读取并夹取上下限
        LOBYTE(v2) = sub_657920(v6);  // MTUPD 全局超时组设置：按 nArg1 分支写 dword_796934/79692C/
        *(float *)(dword_8F8548 + 24) = (double)dword_79692C * 0.001;  // 用户震动强度档
        break;
      default:
        goto LABEL_23;
    }
  }
  else
  {
    v2 = sub_48B740((const CHAR *)this, 0);  // 结果 = 调试配置项读取并夹取上下限
    if ( v2 != 1 )
    {
      DeleteFileA((LPCSTR)(*(uint32_t *)(this + 4) + 4));  // this+4〔宿主对象〕等 2 字段
      LOBYTE(v2) = sub_48B7C0((const CHAR *)this, 0, 1);  // 调试配置项写入并刷新（·sub_48B830 联动）
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x48B970 sub_48B970 —— 216 项开关表读盘并逐项下发
//   ·sub_57A120（CBIniFile 桩）把 lpszKey 键下 0xD8 = 216 字节整表读入 byte_99FDD0，
//   再对存在的项 i 调 ·sub_47E7A0(byte_99FDD0[i], 0) 下发【推断：逐项应用/重排】。
// ------------------------------------------------------------
int /*thiscall*/ sub_48B970(const CHAR *this)  // 实现：216 项开关表读盘并逐项下发
{
  int i; // esi
  int result; // eax

  sub_57A120(this + 104, lpszKey, byte_99FDD0, 0xD8u);  // CBIniFile 桩
  for ( i = 0; i < 216; ++i )  // 循环：i 从 0 递增到 216
  {
    result = sub_47DC90(i);  // 调 族写技能表 ──
    if ( result != 0 )  // 若结果非 0（成功）
      result = sub_47E7A0(byte_99FDD0[i], 0);  // 调 pszArg3 时播 SEAL_ON/SEAL_OFF（sub_432EA0）+ sub_44E850(18) + sub_48BA…
  }
  return result;
}



// ------------------------------------------------------------
// 0x48B9C0 sub_48B9C0 —— 调试配置 INI 对象装载 + 首项应用
//   新建 0x108 字节对象经 ·sub_57A0A0（桩）装入 +4，随后 ·sub_48B830(this, 0) 触发首项（ID 文件）应用。
// ------------------------------------------------------------
char /*thiscall*/ sub_48B9C0(uint32_t *this, LPCSTR lpString2)  // 实现：调试配置 INI 对象装载 + 首项应用
{
  int v3; // eax

  if ( operator new(0x108u) != nullptr )  // 堆分配 264 字节对象
    v3 = sub_57A0A0(lpString2);  // 结果 = CBIniFile 桩
  else
    v3 = 0;
  *(this + 1) = v3;  // this+4〔宿主对象〕
  return sub_48B830((int)this, 0);  // 调试配置项应用分派（项号 → 全局开关）
}



// ------------------------------------------------------------
// 0x48BA30 sub_48BA30 —— 控制台输出 "ID %s"
// ------------------------------------------------------------
char /*thiscall*/ sub_48BA30(char *this, char *pszArg2)  // 实现：控制台输出 ID %s
{
  char *pszArg22; // eax
  const char *pThis_8; // esi
  int pThis_82; // edx
  char v6; // cl
  int i; // esi
  char result; // al

  pszArg22 = pszArg2;
  pThis_8 = this + 8;  // this+8 物品 id
  pThis_82 = this + 8 - pszArg2;  // this+8 物品 id
  do
  {
    v6 = *pszArg22;
    pszArg22[pThis_82] = *pszArg22;
    ++pszArg22;
  }
  while ( v6 != 0 );
  sprintf(this + 40, "ID %s", pThis_8);  // 字符串 “ID %s”
  for ( i = 1; i <= 17; ++i )
    result = sub_48B830((int)this, i);  // 结果 = 调试配置项应用分派（项号 → 全局开关）
  return result;
}



// ------------------------------------------------------------
// 0x48BA80 sub_48BA80 —— 控制台输出 "CH %s %s %d %d"（频道/角色名调试）
// ------------------------------------------------------------
char /*thiscall*/ sub_48BA80(int this, const char *pArg2, int nArg3)  // 实现：控制台输出 CH %s %s %d %d（频道/角色名调试）
{
  int nLen; // eax

  nLen = sub_48BE40(pArg2, strlen(pArg2));  // 结果 = 包体校验和（·sub_57A220 链式累积）
  sprintf((char *const)(this + 104), "CH %s %s %d %d", (const char *)(this + 8), pArg2, nLen, nArg3);  // 字符串 “CH %s %s %d %d”
  return sub_48B830(this, 18);  // 调试配置项应用分派（项号 → 全局开关）
}



// ------------------------------------------------------------
// 0x48BAD0 sub_48BAD0 —— 216 项开关表收集并写盘
//   对每项 i 取 ·sub_47DC90(i) 对象、以 ·sub_41A5E0(对象+558) 求值置 byte_99FDD0[i]【推断】，
//   再经 ·sub_57A0D0（桩）把该表整表写回 lpszKey 键。
// ------------------------------------------------------------
int /*thiscall*/ sub_48BAD0(const CHAR *this)  // 实现：216 项开关表收集并写盘
{
  int i; // esi
  int v3; // eax
  bool v4; // al

  for ( i = 0; i < 216; ++i )  // 循环：i 从 0 递增到 216
  {
    v3 = sub_47DC90(i);  // 调 族写技能表 ──
    v4 = v3 != 0 && sub_41A5E0(v3 + 558) != 0;  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    byte_99FDD0[i] = v4;
  }
  return sub_57A0D0(this + 104, lpszKey, byte_99FDD0, 0xD8u);  // CBIniFile 桩
}



// ------------------------------------------------------------
// 0x48BB30 sub_48BB30 —— 反调试（GetProcAddress 动态取 Kernel32!IsDebuggerPresent；命中走 off_77F3FC）
// ------------------------------------------------------------
int /*thiscall*/ sub_48BB30(uint32_t *this, LPCVOID lpAddress)  // 实现：反调试（GetProcAddress 动态取 Kernel32!IsDebuggerPresent；命中走 off_77F3FC）
{
  HMODULE LibraryA; // eax
  SIZE_T RegionSize; // ecx
  bool v6; // cf
  __time32_t v7; // eax
  int nRand; // eax
  unsigned int i; // edi
  size_t fld_e3; // [esp-1Ch] [ebp-48h]
  struct _MEMORY_BASIC_INFORMATION Buffer; // [esp+10h] [ebp-1Ch] BYREF

  if ( lpAddress == nullptr )  // 若 lpAddress 为空
    return -1;
  if ( *this != 0 )
    return -2;
  if ( IsDebuggerPresent == nullptr )  // 若 IsDebuggerPresent 为空
  {
    LibraryA = LoadLibraryA("Kernel32.dll");  // 字符串 “Kernel32.dll”
    if ( LibraryA != nullptr )  // 若 LibraryA 有效（非空）
      IsDebuggerPresent = GetProcAddress(LibraryA, "IsDebuggerPresent");  // 字符串 “IsDebuggerPresent”
  }
  VirtualQuery(&loc_48BB8F, &Buffer, 0x1Cu);
  RegionSize = Buffer.RegionSize;
  v6 = Buffer.RegionSize < (unsigned int)lpAddress;
  *(this + 6) = Buffer.AllocationBase;  // this+24〔nPageMax(推断)〕
  if ( v6 )
    *(this + 2) = RegionSize;  // this+8〔nSkillRec8(推断)〕
  else
    *(this + 2) = lpAddress;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = RegionSize / *(this + 2);  // this+12〔nSkillRec12(推断)〕等 2 字段
  off_77F3FC("EyeOfBeholder::open_eye - code region size = %d", RegionSize);  // 字符串 “EyeOfBeholder::open_eye - code region size =”
  off_77F3FC("EyeOfBeholder::open_eye - CRC block size = %d", lpAddress);  // 字符串 “EyeOfBeholder::open_eye - CRC block size = %”
  off_77F3FC("EyeOfBeholder::open_eye - number of CRC blocks = %d", *(this + 3));  // 字符串 “EyeOfBeholder::open_eye - number of CRC bloc”
  v7 = time(nullptr);  // v7 = 调 time
  srand(v7);  // 调 设置随机种子
  nRand = rand();  // nRand = 调 rand
  fld_e3 = 4 * *(this + 3);  // this+12〔nSkillRec12〕
  *(this + 1) = nRand;  // this+4〔宿主对象〕
  *(this + 4) = malloc(fld_e3);  // this+16〔nChannelTypeSel(推断)〕
  for ( i = 0; i < *(this + 3); ++i )  // this+12〔nSkillRec12(推断)〕
    *(uint32_t *)(*(this + 4) + 4 * i) = sub_57A220(*(this + 1), *(this + 6) + i * *(this + 2), *(this + 2));  // INI 取值（转发 57A1C0）
  *this = 1;
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x48BC60 sub_48BC60 —— 反调试状态对象清零构造
//   7 个字段全清（+0 已开标志、+4 CRC 缓冲、+8/12/16 区间参数、+20/+24 计数），供 ·sub_48BB30 逐块填充。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_48BC60(uint32_t *this)  // 反调试状态对象清零构造
{
  *this = 0;
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 4) = 0;  // this+16〔nChannelTypeSel(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  *(this + 5) = 0;  // this+20〔nPage(推断)〕
  *(this + 6) = 0;  // this+24〔nPageMax(推断)〕
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x48BC90 sub_48BC90 —— 读流游标取 4 字节长度并拷贝其载荷
//   ·sub_404AD0 从读游标 dword_79D060 读 4 字节长度，·sub_404AF0 再拷同样多字节到 pArg1，返回长度。
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_48BC90(void *pArg1)  // 实现：读流游标取 4 字节长度并拷贝其载荷
{
  unsigned int v2; // [esp+0h] [ebp-4h] BYREF

  v2 = 0;
  sub_404AD0(&v2);  // 游标读 4 字节
  sub_404AF0(pArg1, v2);  // 游标读 n 字节到目标缓冲（qmemcpy 批量版）
  return v2;
}



// ------------------------------------------------------------
// 0x48BCC0 sub_48BCC0 —— 限量串读入或 strncpy 回退
//   先探读游标长度 v4（0 < v4 < uArg2 时）拷 v4 字节并补 0；Source 为空写空串，非空回落 strncpy 截到 uArg2-1。
// ------------------------------------------------------------
char */*cdecl*/ sub_48BCC0(char *Destination, unsigned int uArg2, char *Source)  // 限量串读入或 strncpy 回退
{
  char *result; // eax
  unsigned int v4; // [esp+4h] [ebp-4h] BYREF

  v4 = 0;
  if ( uArg2 != 0 )
  {
    sub_404AD0(&v4);  // 游标读 4 字节
    if ( v4 < uArg2 && v4 != 0 )  // 若 v4 < uArg2 与/或 v4 != 0
    {
      sub_404AF0(Destination, v4);  // 游标读 n 字节到目标缓冲（qmemcpy 批量版）
      Destination[v4] = 0;
      return (char *)v4;
    }
    result = Source;
    if ( Source == nullptr )  // 若 Source 为空
    {
      *Destination = 0;
      return result;
    }
    strncpy(Destination, Source, uArg2 - 1);  // 调 限长串拷贝
    Destination[uArg2 - 1] = 0;
  }
  return nullptr;
}



// ------------------------------------------------------------
// 0x48BD40 sub_48BD40 —— 包体加扰（左旋 k 位再异或掩码）
//   掩码/轮转位数取自 ·sub_4D33A0（LCG 取参；nArg3 非 0 作种子，否则常量 16053）高字节与 7；逐字节左旋再异或。
//   与 ·sub_48BDC0 互为逆变换【推断：发送前加扰、接收后还原】。
// ------------------------------------------------------------
int /*cdecl*/ sub_48BD40(int nArg1, int nArg2, int nArg3)  // 实现：包体加扰（左旋 k 位再异或掩码）
{
  int16_t v3; // ax
  int v4; // ebx
  int result; // eax
  int v6; // esi
  char v7; // al

  v3 = 16053;
  if ( nArg3 != 0 )
    v3 = sub_4D33A0(nArg3);  // 调 掷 0..9999
  v4 = HIBYTE(v3) & 7;  // v4 = 调 HIBYTE
  byte_99FEAC = v3;
  result = nArg2;
  v6 = 0;
  dword_99FEB0 = v4;
  if ( nArg2 > 0 )
  {
    while ( 1 )
    {
      v7 = __ROL1__(*(uint8_t *)(v6 + nArg1), v4);  // v7 = 调 __ROL1__
      *(uint8_t *)(v6 + nArg1) = v7;
      *(uint8_t *)(v6 + nArg1) = byte_99FEAC ^ v7;
      result = nArg2;
      if ( ++v6 >= nArg2 )
        break;
      LOBYTE(v4) = dword_99FEB0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x48BDC0 sub_48BDC0 —— 包体解扰（·sub_48BD40 的逆）
//   逐字节先与掩码异或再右旋 k 位，键路同 ·sub_48BD40；供包体还原/预处理【推断】。
// ------------------------------------------------------------
int /*cdecl*/ sub_48BDC0(int nArg1, int nArg2, int nArg3)  // 实现：包体解扰（·sub_48BD40 的逆）
{
  int16_t v3; // ax
  int result; // eax
  int i; // esi
  char v6; // al
  char v7; // bl

  v3 = 16053;
  if ( nArg3 != 0 )
    v3 = sub_4D33A0(nArg3);  // 调 掷 0..9999
  byte_99FEAC = v3;
  dword_99FEB0 = HIBYTE(v3) & 7;  // dword_99FEB0 = 调 HIBYTE
  result = nArg2;
  for ( i = 0; i < nArg2; ++i )
  {
    v6 = byte_99FEAC ^ *(uint8_t *)(i + nArg1);
    *(uint8_t *)(i + nArg1) = v6;
    v7 = __ROR1__(v6, dword_99FEB0);  // v7 = 调 __ROR1__
    result = nArg2;
    *(uint8_t *)(i + nArg1) = v7;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48BE40 sub_48BE40 —— 包体校验和（·sub_57A220 链式累积）
//   初值经 ·sub_57A220(0, 0, 0) 取得，再对 [nArg1, nArg1+nArg2) 累积求值；nArg2 为负回 0。
//   消费见 ·sub_4471E0 系（与包内 +3 校验和 DWORD 比对）。
// ------------------------------------------------------------
int /*cdecl*/ sub_48BE40(int nArg1, int nArg2)  // 实现：包体校验和（·sub_57A220 链式累积）
{
  int v3; // eax

  if ( nArg2 < 0 )
    return 0;
  v3 = sub_57A220(0, 0, 0);  // 结果 = INI 取值（转发 57A1C0）
  return sub_57A220(v3, nArg1, nArg2);  // INI 取值（转发 57A1C0）
}



// ------------------------------------------------------------
// 0x48BE70 sub_48BE70 —— Socket Error 处理（sub_698C50 → UI sub_583B90/57A980）
// ------------------------------------------------------------
int /*thiscall*/ sub_48BE70(int this, int pArg2, int nArg3)  // 实现：Socket Error 处理（sub_698C50 → UI sub_583B90/57A980）
{
  char fld_4; // al
  uint8_t *v5; // eax
  char v6; // cl
  uint8_t *v7; // esi
  struct tm *v8; // eax
  struct tm *v9; // eax
  struct tm *v10; // eax
  struct tm *v11; // eax
  struct tm *v12; // eax
  int tm_sec; // ebx
  unsigned int v14; // edi
  const char *v15; // eax
  uint32_t *pThis2; // ebx
  int v17; // edx
  int v18; // eax
  __time64_t Time; // [esp+0h] [ebp-1Ch] BYREF
  int v20; // [esp+8h] [ebp-14h]
  int tm_mday; // [esp+Ch] [ebp-10h]
  int tm_hour; // [esp+10h] [ebp-Ch]
  int tm_min; // [esp+14h] [ebp-8h]
  uint32_t *pThis; // [esp+18h] [ebp-4h]

  fld_4 = *(uint8_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  pThis = (uint32_t *)this;
  if ( fld_4 == 0 )  // fld_4=this+4 宿主对象
    return -2147483647;  // 返回 0x80000001(未就绪)
  v5 = (uint8_t *)sub_698C50(*(uint32_t *)(pArg2 + 2));  // 调 取包(sub_69DF70 Read)
  v7 = v5;
  if ( v5 == nullptr )  // 若 v5 为空
  {
    off_77F3F8(v6, "Socket Error");  // 字符串 “Socket Error”
    return 0x80000000;  // 返回 失败码
  }
  sub_48BDC0(v5 + 6, *(uint32_t *)(v5 + 2) - 6, 0);  // 包体解扰（·sub_48BD40 的逆）
  sub_404A80(v7 + 6);  // 流读取游标设置（dword_79D060 = nArg1）
  Time = _time64(nullptr);  // Time = 调 _time64
  v8 = _localtime64(&Time);  // v8 = 调 _localtime64
  if ( v8 != nullptr )  // 若 v8 有效（非空）
    v20 = v8->tm_mon + 1;
  else
    v20 = 0;
  v9 = _localtime64(&Time);  // v9 = 调 _localtime64
  if ( v9 != nullptr )  // 若 v9 有效（非空）
    tm_mday = v9->tm_mday;
  else
    tm_mday = 0;
  v10 = _localtime64(&Time);  // v10 = 调 _localtime64
  if ( v10 != nullptr )  // 若 v10 有效（非空）
    tm_hour = v10->tm_hour;
  else
    tm_hour = -1;
  v11 = _localtime64(&Time);  // v11 = 调 _localtime64
  if ( v11 != nullptr )  // 若 v11 有效（非空）
    tm_min = v11->tm_min;
  else
    tm_min = -1;
  v12 = _localtime64(&Time);  // v12 = 调 _localtime64
  if ( v12 != nullptr )  // 若 v12 有效（非空）
    tm_sec = v12->tm_sec;
  else
    tm_sec = -1;
  LOBYTE(pArg2) = 0;
  v14 = 1;
  if ( *v7 != 0 )
  {
    if ( *v7 == 1 )
    {
      sub_404A90(&pArg2);  // 游标读 1 字节（*uArg1 取值，游标 +1）
      v15 = "Ok";  // 字符串 “Ok”
      if ( (uint8_t)pArg2 == 0 )
        v15 = "Error";  // 字符串 “Error”
      off_77F3FC(  // 引擎日志输出函数(printf 风格)
        "\n[<- COMMAND PACKET] Packet : %s, Size : %d, Return : %s (%2d%2d-%2d:%2d:%2d)",  // 字符串 “\n[<- COMMAND PACKET] Packet : %s, Size : %d”
        *(const char **)&off_790928[4 * v7[1]],  // 读 off_790928（包名表（按 type 索引））
        *(uint32_t *)(v7 + 2) - 6,
        v15,
        v20,
        tm_mday,
        tm_hour,
        tm_min,
        tm_sec);
      pThis2 = pThis;
      v14 = sub_583B90(pThis, v7, pArg2);  // 结果 = size=27453
      goto LABEL_28;
    }
    off_77F3FC("Type Error! Type is %d", *v7);  // 字符串 “Type Error! Type is %d”
  }
  else
  {
    off_77F3FC(  // 引擎日志输出函数(printf 风格)
      "\n[<- NOTIFY PACKET] Packet : %s, Size : %d (%2d%2d-%2d:%2d:%2d)",  // 字符串 “\n[<- NOTIFY PACKET] Packet : %s, Size : %d ”
      *(const char **)&off_790790[4 * v7[1]],
      *(uint32_t *)(v7 + 2) - 6,
      v20,
      tm_mday,
      tm_hour,
      tm_min,
      tm_sec);
    v14 = sub_57A980(pThis, v17, (int)v7);  // 结果 = size=36584
  }
  pThis2 = pThis;
LABEL_28:
  v18 = pThis2[3];
  if ( v18 != 8 )
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint8_t *, uint32_t))(*(uint32_t *)pThis2[v18 + 4] + 12))(  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
      pThis2[v18 + 4],
      v7[1],
      v7,
      *(uint32_t *)(v7 + 2));
  return v14;
}


// ============================================================
// §L 0x48C070-0x48C500  包校验/杂项
// ============================================================
// ------------------------------------------------------------
// 0x48C070 sub_48C070 —— 像素坐标 → 格子行列换算
//   横向 16 像素/格、纵向 12 像素/格取整除，即地牢图块坐标系。
// ------------------------------------------------------------
int /*stdcall*/ sub_48C070(int *pDwArg1, int *pDwArg2, int nArg3, int nArg4)  // 实现：像素坐标 → 格子行列换算
{
  *pDwArg1 = nArg3 / 16;
  *pDwArg2 = nArg4 / 12;
  return nArg4 / 12;  // 返回 nArg4 / 12
}



// ------------------------------------------------------------
// 0x48C0A0 sub_48C0A0 —— 点是否落在 {x, y, 宽, 高} 矩形内
//   pDwArg3 为 {x, y, 宽, 高} 四元组；横纵双区间包含判断。
// ------------------------------------------------------------
bool /*cdecl*/ sub_48C0A0(int nArg1, int nArg2, int *pDwArg3)  // 实现：点是否落在 {x, y, 宽, 高} 矩形内
{
  bool result; // al
  int v4; // ecx

  result = nArg1 >= *pDwArg3 && nArg1 < *pDwArg3 + pDwArg3[2] && (v4 = pDwArg3[1], nArg2 >= v4) && nArg2 < v4 + pDwArg3[3];
  return result;
}



// ------------------------------------------------------------
// 0x48C0E0 sub_48C0E0 —— 矩形区域内取随机格（内缩后掷点回中）
//   vt+40(1)（带占位宿主）时按 vt+428/+432 尺寸内缩，经 ·sub_4D33A0（LCG，以 nArg5 为状态）掷点并加半宽半高回中。
//   否则在矩形宽高内均匀掷点；供 ·sub_48C2A0/·sub_48C330/·sub_48C3A0 落点查找反复调用。
// ------------------------------------------------------------
int /*cdecl*/ sub_48C0E0(uint32_t *uArg1, int *pDwArg2, uint32_t *pArg3, int nArg4, int nArg5)  // 实现：矩形区域内取随机格（内缩后掷点回中）
{
  int v6; // ebx
  int v7; // ebx
  int v8; // ebx
  int result; // eax
  int v10; // edx
  int v11; // [esp+20h] [ebp+14h]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg4 + 40))(nArg4, 1) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    v6 = pArg3[2] - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 428))(nArg4) + 1;  // 调虚槽 +428
    v11 = sub_4D33A0(nArg5) % v6;  // 调 掷 0..9999
    v7 = pArg3[3] - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 432))(nArg4) + 1;  // 调虚槽 +432
    v8 = sub_4D33A0(nArg5) % v7;  // 调 掷 0..9999
    *uArg1 = v11 + *pArg3 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 428))(nArg4) / 2;  // 调虚槽 +428
    result = v8 + pArg3[1] + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 432))(nArg4) / 2;  // 调虚槽 +432
    *pDwArg2 = result;
  }
  else
  {
    *uArg1 = *pArg3 + sub_4D33A0(nArg5) % pArg3[2];  // 调 掷 0..9999
    v10 = sub_4D33A0(nArg5) % pArg3[3];  // 调 掷 0..9999
    result = pArg3[1];
    *pDwArg2 = result + v10;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48C1C0 sub_48C1C0 —— 演出层纵向基线换算（按类型取字段乘百分位）
//   类型 5/4/0 分别取 this+2/+3/+4 与 +116 求积除 100，其余直接回 +116；·sub_48C730 以其减去图层基准 +192。
// ------------------------------------------------------------
int /*thiscall*/ sub_48C1C0(uint32_t *this, int nArg2)  // 实现：演出层纵向基线换算（按类型取字段乘百分位）
{
  int fld_e2; // edx

  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      fld_e2 = *(this + 2) * *(this + 116);  // this+8〔nSkillRec8(推断)〕
      return fld_e2 / 100;  // 返回 fld_e2 / 100
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      fld_e2 = *(this + 3) * *(this + 116);  // this+12〔nSkillRec12(推断)〕
      return fld_e2 / 100;  // 返回 fld_e2 / 100
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      fld_e2 = *(this + 4) * *(this + 116);  // this+16〔nChannelTypeSel(推断)〕
      return fld_e2 / 100;  // 返回 fld_e2 / 100
    default:
      break;
  }
  return *(this + 116);  // this+116 观察者 vector 尾针
}



// ------------------------------------------------------------
// 0x48C220 sub_48C220 —— 可动位查询（+396 的 4/1/2/8 位）
//   类型 0..3 依次测 +396 的位 4/1/2/8（四向可动位）【推断】；供 ·sub_48C440/·sub_48C680 移动前判定。
// ------------------------------------------------------------
bool /*thiscall*/ sub_48C220(uint8_t *this, int nArg2)  // 实现：可动位查询（+396 的 4/1/2/8 位）
{
  bool result; // al

  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(this + 396) & 4) == 4;  // this+396 【推断】技能参数索引槽
      break;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(this + 396) & 1) == 1;  // this+396 【推断】技能参数索引槽
      break;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      result = (*(this + 396) & 2) == 2;  // this+396 【推断】技能参数索引槽
      break;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      result = (*(this + 396) & 8) == 8;  // this+396 【推断】技能参数索引槽
      break;
    default:
      result = false;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48C2A0 sub_48C2A0 —— 区域内找落点（失败打 FIND POS FAIL）
//   按索引 pArg4 取 this + 4 乘 pArg4 + 100 矩形记录，·sub_48C0E0 掷点后交宿主 vt+140（pArg4<2 折算标志位）；
//   失败打 FIND POS FAIL! %d %d %d。
// ------------------------------------------------------------
int /*thiscall*/ sub_48C2A0(uint32_t *this, uint32_t *uArg2, int *pDwArg3, unsigned int pArg4, int nArg5, int nArg6)  // 实现：区域内找落点（失败打 FIND POS FAIL）
{
  int pArg42; // eax
  int result; // eax

  sub_48C0E0(uArg2, pDwArg3, this + 4 * pArg4 + 100, nArg5, (int)&nArg6);  // 矩形区域内取随机格（内缩后掷点回中）
  pArg42 = pArg4;
  if ( pArg4 < 2 )
    pArg42 = 1;
  else
    LOBYTE(pArg42) = 0;
  result = (*(int (/*thiscall*/ **)(int, uint32_t *, int *, uint32_t, int, int, int, int))(*(uint32_t *)nArg5 + 140))(  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
             nArg5,
             uArg2,
             pDwArg3,
             *uArg2,
             *pDwArg3,
             200,
             pArg42,
             1);
  if ( (uint8_t)result == 0 )
    return off_77F3FC("FIND POS FAIL! %d %d %d", *this, pArg4, nArg6);  // 字符串 “FIND POS FAIL! %d %d %d”
  return result;
}



// ------------------------------------------------------------
// 0x48C330 sub_48C330 —— 自身矩形内找落点（失败打 FIND POS FAIL）
//   矩形固定取内嵌 this+69 记录；宿主 vt+140 以第 7 参 1 调用；失败打 FIND POS FAIL! %d %d。
// ------------------------------------------------------------
int /*thiscall*/ sub_48C330(uint32_t *this, uint32_t *uArg2, int *pDwArg3, int nArg4, int nArg5)  // 实现：自身矩形内找落点（失败打 FIND POS FAIL）
{
  int result; // eax

  sub_48C0E0(uArg2, pDwArg3, this + 69, nArg4, (int)&nArg5);  // 矩形区域内取随机格（内缩后掷点回中）
  result = (*(int (/*thiscall*/ **)(int, uint32_t *, int *, uint32_t, int, int, int, int))(*(uint32_t *)nArg4 + 140))(  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
             nArg4,
             uArg2,
             pDwArg3,
             *uArg2,
             *pDwArg3,
             200,
             1,
             1);
  if ( (uint8_t)result == 0 )
    return off_77F3FC("FIND POS FAIL! %d %d", *this, nArg5);  // 字符串 “FIND POS FAIL! %d %d”
  return result;
}



// ------------------------------------------------------------
// 0x48C3A0 sub_48C3A0 —— 重试找落点（上限 1000 次）
//   循环掷点并以宿主 vt+136 验证（返回 1 即命中停止；至多 1000 次）；尾部 ·off_77F3FC 打 aPvp_1 记录 4 值。
// ------------------------------------------------------------
int /*thiscall*/ sub_48C3A0(uint32_t *this, int pArg2, uint32_t *uArg3, int *pDwArg4, int nArg5, char pszArg6)  // 实现：重试找落点（上限 1000 次）
{
  uint32_t *pThis_4; // [esp+Ch] [ebp-10h]
  uint32_t *v9; // [esp+14h] [ebp-8h]
  int v10; // [esp+18h] [ebp-4h]

  pThis_4 = this + 4 * pArg2;  // this+4 宿主对象
  v10 = 1000;
  v9 = pThis_4 + 77;  // this+77 【推断】公会标志字节 B
  do
  {
    sub_48C0E0(uArg3, pDwArg4, v9, nArg5, (int)&pszArg6);  // 矩形区域内取随机格（内缩后掷点回中）
    if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t, int, uint32_t))(*(uint32_t *)nArg5 + 136))(nArg5, *uArg3, *pDwArg4, 0) == 1 )  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
      break;
    --v10;
  }
  while ( v10 != 0 );
  return off_77F3FC(aPvp_1, *v9, pThis_4[78], pThis_4[79], *(this + 4 * pArg2 + 80));  // 返回 调 off_77F3FC
}



// ------------------------------------------------------------
// 0x48C440 sub_48C440 —— 相邻方向码换算并查可动
//   与 this+392 对象的当前格（+112/+116）比较给出方向码 0..3【推断：横减/横增/纵减/纵增】，再交 ·sub_48C220 位掩码判定。
// ------------------------------------------------------------
bool /*thiscall*/ sub_48C440(int this, int nArg2, int nArg3)  // 实现：相邻方向码换算并查可动
{
  int fld_188; // eax
  int v5; // edx
  int v6; // eax
  int v7; // eax

  fld_188 = *(uint32_t *)(this + 392);
  if ( fld_188 == 0 )
    return false;
  v5 = *(uint32_t *)(fld_188 + 112);
  v6 = *(uint32_t *)(fld_188 + 116);
  if ( nArg3 == v6 )
  {
    if ( nArg2 == v5 - 1 )
    {
      v7 = 0;
    }
    else
    {
      if ( nArg2 != v5 + 1 )
        return false;
      v7 = 1;
    }
  }
  else
  {
    if ( nArg2 != v5 )
      return false;
    if ( nArg3 == v6 - 1 )
    {
      v7 = 2;
    }
    else
    {
      if ( nArg3 != v6 + 1 )
        return false;
      v7 = 3;
    }
  }
  return sub_48C220((uint8_t *)this, v7);  // 可动位查询（+396 的 4/1/2/8 位）
}



// ------------------------------------------------------------
// 0x48C4B0 sub_48C4B0 —— 24 字节元素区间拷贝（6 dword 一组）
//   [uArg1, uArg2) 逐条 6 dword 抄到 uArg3 起，回尾指针；·sub_48D290 截断分支的底层搬运件。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48C4B0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 24 字节元素区间拷贝（6 dword 一组）
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax
  uint32_t *v5; // edi
  int v6; // esi

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; v5[5] = v6 )
  {
    v5 = result;
    *result = *uArg12;
    result[1] = uArg12[1];  // result[1] = 取 uArg12[1]
    result[2] = uArg12[2];  // result[2] = 取 uArg12[2]
    result[3] = uArg12[3];  // result[3] = 取 uArg12[3]
    result[4] = uArg12[4];  // result[4] = 取 uArg12[4]
    v6 = uArg12[5];
    uArg12 += 6;
    result += 6;
  }
  return result;
}



// ============================================================
// §M 0x48C500-0x48CF90  技能演出联动（sub_4938F0/491D00 转发）
// ============================================================
// ------------------------------------------------------------
// 0x48C500 sub_48C500 —— 跟踪目标登记（坐标差折进 +116/+117 并夹界）
//   目标 vt+120/+124 与自身 +116/+117 的差分按死区窗口（横 270..370、纵 160..240）折进 +116/+117 并夹界
//   （横 [0, ·sub_425080]、纵 [0, 120 乘 ·sub_424FF0]）；+116/+117 即地牢图铺绘偏移，·sub_48CA20 绘制与 ·sub_48C730 共用。
//   【推断：镜头/视野跟随登记。】
// ------------------------------------------------------------
void /*thiscall*/ sub_48C500(uint32_t *this, int nArg2)  // 实现：跟踪目标登记（坐标差折进 +116/+117 并夹界）
{
  int fld_e116; // edi
  int fld_e117; // ebx
  int fld_e1163; // edx
  int fld_e11622; // edi
  int fld_e116222; // eax
  int fld_e116223; // eax
  int fld_e1162; // edx
  int fld_e1173; // edx
  int fld_e11722; // edi
  int fld_e117222; // eax
  int fld_e1172; // edx

  if ( nArg2 != 0 )
  {
    fld_e116 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2) - *(this + 116);  // 调虚槽 +120：动画对象
    fld_e117 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2) - *(this + 117);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    if ( fld_e116 >= 270 )
    {
      if ( fld_e116 < 370 )
        goto LABEL_15;
      fld_e1162 = fld_e116 - 370 + *(this + 116);  // this+116 观察者 vector 尾针
      *(this + 116) = fld_e1162;  // this+116 观察者 vector 尾针
      fld_e11622 = fld_e1162;
      if ( sub_425080(this) >= fld_e1162 )  // 横向溢出
        fld_e116222 = fld_e11622;
      else
        fld_e116222 = sub_425080(this);  // 结果 = 横向溢出
    }
    else
    {
      fld_e1163 = fld_e116 - 270 + *(this + 116);  // this+116 观察者 vector 尾针
      *(this + 116) = fld_e1163;  // this+116 观察者 vector 尾针
      fld_e11622 = fld_e1163;
      if ( sub_425080(this) >= fld_e1163 )  // 横向溢出
        fld_e116222 = fld_e11622;
      else
        fld_e116222 = sub_425080(this);  // 结果 = 横向溢出
    }
    if ( fld_e116222 >= 0 )
    {
      if ( sub_425080(this) >= fld_e11622 )  // 横向溢出
        fld_e116223 = fld_e11622;
      else
        fld_e116223 = sub_425080(this);  // 结果 = 横向溢出
    }
    else
    {
      fld_e116223 = 0;
    }
    *(this + 116) = fld_e116223;  // this+116 观察者 vector 尾针
LABEL_15:
    if ( fld_e117 >= 160 )
    {
      if ( fld_e117 < 240 )
        return;
      fld_e1172 = fld_e117 - 240 + *(this + 117);
      *(this + 117) = fld_e1172;
      fld_e11722 = fld_e1172;
      if ( 120 * sub_424FF0(this) < fld_e1172 )  // 列数换算
        goto LABEL_17;
    }
    else
    {
      fld_e1173 = fld_e117 - 160 + *(this + 117);
      *(this + 117) = fld_e1173;
      fld_e11722 = fld_e1173;
      if ( 120 * sub_424FF0(this) < fld_e1173 )  // 列数换算
      {
LABEL_17:
        fld_e117222 = 120 * sub_424FF0(this);  // 结果 = 列数换算
        goto LABEL_19;
      }
    }
    fld_e117222 = fld_e11722;
LABEL_19:
    if ( fld_e117222 >= 0 )
    {
      if ( 120 * sub_424FF0(this) >= fld_e11722 )  // 列数换算
        *(this + 117) = fld_e11722;
      else
        *(this + 117) = 120 * sub_424FF0(this);  // 列数换算
    }
    else
    {
      *(this + 117) = 0;
    }
  }
}



// ------------------------------------------------------------
// 0x48C680 sub_48C680 —— 移动请求发包（op 48，目标格 X/Y）
//   可动检查通过且 +472 单次闸未置时：按方向码对 this+392 对象当前格（+112/+116）增删（横减/横增/纵减/纵增四路）【推断】，
//   经 ·sub_423200(48) 起包、·sub_423290 两字节载荷、·sub_423380 提交，发毕置 +472。
// ------------------------------------------------------------
char /*thiscall*/ sub_48C680(int this, int nArg2)  // 实现：移动请求发包（op 48，目标格 X/Y）
{
  char result; // al
  int v4; // edx
  int fld_188; // eax
  int v6; // ebx

  result = *(uint8_t *)(this + 472);
  if ( result == 0 )
  {
    result = sub_48C220((uint8_t *)this, nArg2);  // 结果 = 可动位查询（+396 的 4/1/2/8 位）
    if ( result != 0 )  // 若结果非 0（成功）
    {
      fld_188 = *(uint32_t *)(this + 392);
      v6 = *(uint32_t *)(fld_188 + 116);
      nArg2 = *(uint32_t *)(fld_188 + 112);
      switch ( v4 )  // 按 v4 分派
      {
        case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
          --nArg2;
          break;
        case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
          ++nArg2;
          break;
        case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
          LOBYTE(v6) = v6 - 1;
          break;
        case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
          LOBYTE(v6) = v6 + 1;
          break;
        default:
          break;
      }
      sub_423200(dword_8F7B08, 48);  // 【发送网络包API】
      HIBYTE(nArg2) = nArg2;
      sub_423290((char *)&nArg2 + 3, 1);  // 调 写 4B 长度
      HIBYTE(nArg2) = v6;
      sub_423290((char *)&nArg2 + 3, 1);  // 调 写 4B 长度
      result = sub_423380(dword_8F7B08);  // 结果 = 发包提交：Commit()
      *(uint8_t *)(this + 472) = 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x48C730 sub_48C730 —— 技能演出驱动转发（sub_4938F0 帧推进 / sub_491D00 子链属性）
// ------------------------------------------------------------
int */*thiscall*/ sub_48C730(uint32_t *this, int nArg2, char pszArg3)  // 技能演出驱动转发（sub_4938F0 帧推进 / sub_491D00 子链属性）
{
  int v4; // eax
  int *v5; // edi
  int *result; // eax
  int fld_e98; // esi
  int v8; // ecx
  int v9; // ebx
  int v10; // esi
  int v11; // edi
  int v12; // ebx
  int i; // esi
  int *v14; // [esp+8h] [ebp-Ch]
  int v15; // [esp+Ch] [ebp-8h]
  int v16; // [esp+10h] [ebp-4h]
  int v17; // [esp+1Ch] [ebp+8h]
  int *v18; // [esp+20h] [ebp+Ch]

  v4 = 16 * ((pszArg3 != 0) + 2 * nArg2);
  v5 = *(int **)((char *)this + v4 + 24);
  result = (uint32_t *)((char *)this + v4 + 20);
  v14 = result;
  if ( v5 != nullptr )  // 若 v5 有效（非空）
  {
    v17 = result[2];
    result = (int *)((v17 - (int)v5) >> 3);
    if ( result != nullptr )  // 若 result 有效（非空）
    {
      fld_e98 = *(this + 98);
      v9 = sub_48C1C0(this, nArg2) - *(uint32_t *)(fld_e98 + 192);  // 结果 = 演出层纵向基线换算（按类型取字段乘百分位）
      result = v5;
      v16 = v9;
      v15 = *(uint32_t *)(fld_e98 + 196) - *(uint32_t *)(v8 + 468);
      v18 = v5;
      if ( v5 != (int *)v17 )
      {
        while ( 1 )
        {
          v10 = *result;
          v11 = result[1];
          sub_4938F0(*result);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
          v12 = -((v11 + v9) % v11);  // v12 = 调 -
          if ( *(uint32_t *)(v10 + 148) == -1 )
          {
            sub_4938F0(v10);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
            if ( *(uint32_t *)(v10 + 148) == -1 )
              sub_4938F0(v10);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
          }
          for ( i = v12 + (uint64_t)((double)*(int *)(v10 + 72) * *(float *)(v10 + 80)); i > 0; v12 -= v11 )
            i -= v11;
          for ( ; i < 640; v12 += v11 )
          {
            sub_491D00(dword_79C0B0, v12, v15, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            i += v11;
          }
          result = v18 + 2;
          v18 += 2;
          if ( v18 == (int *)v14[2] )
            break;
          v9 = v16;
          result = v18;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x48C860 sub_48C860 —— 按坐标查覆盖矩形记录（this+54 表）
//   逐条 6 dword（x, y, 宽, 高 与两键）测目标 vt+120/+124 是否落入矩形，返回记录地址或空。
// ------------------------------------------------------------
int */*thiscall*/ sub_48C860(int **this, int nArg2)  // 按坐标查覆盖矩形记录（this+54 表）
{
  int *fld_e54; // esi
  int v3; // ebx
  int v4; // eax
  int v5; // eax

  fld_e54 = *(this + 54);  // this+216〔bField216(推断)〕
  if ( fld_e54 == *(this + 55) )  // this+220〔nSnapDst220(推断)〕
    return nullptr;
  while ( 1 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);  // 调虚槽 +120：动画对象
    if ( v4 >= *fld_e54 && v4 < *fld_e54 + fld_e54[2] )  // fld_e54=this+216 bField216
    {
      v5 = fld_e54[1];  // fld_e54=this+216 bField216
      if ( v3 >= v5 && v3 < v5 + fld_e54[3] )  // 若 v3 >= v5 与/或 v3 < v5
        break;
    }
    fld_e54 += 6;  // fld_e54=this+216 bField216
    if ( fld_e54 == *(this + 55) )  // this+220〔nSnapDst220(推断)〕
      return nullptr;
  }
  return fld_e54;  // fld_e54=this+216 bField216
}



// ------------------------------------------------------------
// 0x48C8E0 sub_48C8E0 —— 遍历 +74 表取件并 ·sub_432EA0 收尾
//   对 this+74 起每元素经 ·sub_41ACF0（资源管理器）取件后 ·sub_432EA0(件, -1, 0, 0) 收尾【推断：-1 为停播/默认参】。
// ------------------------------------------------------------
void /*thiscall*/ sub_48C8E0(uint32_t *this)  // 实现：遍历 +74 表取件并 ·sub_432EA0 收尾
{
  unsigned int i; // esi
  int fld_e74; // ecx
  void *v4; // eax

  for ( i = 0; ; ++i )
  {
    fld_e74 = *(this + 74);  // this+296〔bInitFlag296(推断)〕
    if ( fld_e74 == 0 || i >= (*(this + 75) - fld_e74) >> 2 )  // this+300〔pAnim300〕
      break;
    v4 = (void *)sub_41ACF0(fld_e74 + 4 * i);  // 结果 = 驻留串句柄 → 字符串指针
    sub_432EA0(v4, -1, 0, 0);  // 音效播放包装（非空判定）
  }
}



// ------------------------------------------------------------
// 0x48C920 sub_48C920 —— 按键对查矩形记录并回填中心（未中打 aCriticalError_10）
//   记录 = {x, y, 宽, 高, 键 A, 键 B}（6 dword）；命中回中心 (x + 宽/2, y + 高/2) 到 uArg2/uArg3，未中打 aCriticalError_10。
// ------------------------------------------------------------
int /*thiscall*/ sub_48C920(uint32_t *this, uint32_t *uArg2, uint32_t *uArg3, int nArg4, int ArgList, int nArg6)  // 实现：按键对查矩形记录并回填中心（未中打 aCriticalError_10）
{
  uint32_t *fld_e54; // esi
  uint32_t *fld_e55; // ecx
  int result; // eax

  fld_e54 = (uint32_t *)*(this + 54);  // this+216〔bField216(推断)〕
  fld_e55 = (uint32_t *)*(this + 55);  // this+220〔nSnapDst220(推断)〕
  if ( fld_e54 == fld_e55 )  // fld_e54=this+216 bField216
    return off_77F3FC(aCriticalError_10, ArgList, nArg6);  // 返回 调 off_77F3FC
  while ( fld_e54[4] != ArgList || fld_e54[5] != nArg6 )  // fld_e54=this+216 bField216
  {
    fld_e54 += 6;  // fld_e54=this+216 bField216
    if ( fld_e54 == fld_e55 )  // fld_e54=this+216 bField216
      return off_77F3FC(aCriticalError_10, ArgList, nArg6);  // 返回 调 off_77F3FC
  }
  *uArg2 = *fld_e54 + fld_e54[2] / 2;  // fld_e54=this+216 bField216
  result = fld_e54[1] + fld_e54[3] / 2;  // fld_e54=this+216 bField216
  *uArg3 = result;
  return result;
}



// ------------------------------------------------------------
// 0x48C990 sub_48C990 —— 键对存在性查找（this+123 表）
//   逐条 2 dword 比对 (nArg2, nArg3)，存在回 1 否则 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_48C990(uint32_t *this, int nArg2, int nArg3)  // 实现：键对存在性查找（this+123 表）
{
  uint32_t *fld_e123; // eax
  uint32_t *fld_e124; // ecx

  fld_e123 = (uint32_t *)*(this + 123);
  fld_e124 = (uint32_t *)*(this + 124);  // this+124 第 2 组·+858/+1292 增量
  if ( fld_e123 == fld_e124 )
    return 0;
  while ( *fld_e123 != nArg2 || fld_e123[1] != nArg3 )
  {
    fld_e123 += 2;
    if ( fld_e123 == fld_e124 )
      return 0;
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x48C9D0 sub_48C9D0 —— 地图行结构定位（this+95 表 32B 每行）
//   列数门 ·sub_424FF0；行数取 (this+92 减 this+91) 右移 5，返回 this+95 + 32 乘 (pArg3 + nArg2 乘 行数)，越界回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_48C9D0(uint32_t *this, int nArg2, int pArg3)  // 实现：地图行结构定位（this+95 表 32B 每行）
{
  int fld_e91; // ecx
  int fld_e92; // eax

  if ( nArg2 >= sub_424FF0(this) )  // 列数换算
    return 0;
  fld_e91 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
  if ( fld_e91 != 0 )  // fld_e91=this+364 pAnimNameStr
    fld_e92 = (*(this + 92) - fld_e91) >> 5;  // this+368〔nBindPos368〕
  else
    fld_e92 = 0;  // fld_e92=this+368 nBindPos368
  return *(this + 95) + 32 * (pArg3 + nArg2 * fld_e92);  // fld_e92=this+368 nBindPos368
}



// ------------------------------------------------------------
// 0x48CA20 sub_48CA20 —— 技能演出装载（+56 图像槽 → sub_418DD0/sub_424760）
// ------------------------------------------------------------
int */*thiscall*/ sub_48CA20(uint32_t *this, int nArg2, char pszArg3)  // 技能演出装载（+56 图像槽 → sub_418DD0/sub_424760）
{
  int *result; // eax
  unsigned int fld_e116; // ebx
  int fld_e1162; // edi
  int v7; // ecx
  int fld_e91; // edx
  int fld_e98; // ebx
  int fld_e912; // eax
  int v11; // edx
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  int v14; // ebx
  int fld_e913; // ecx
  int v16; // eax
  int fld_e95; // ecx
  unsigned int fld_e96; // eax
  int fld_e914; // edx
  unsigned int fld_e92; // ecx
  int fld_e915; // ecx
  int fld_e922; // eax
  uint32_t *fld_e952; // edi
  uint32_t *v24; // eax
  unsigned int v25; // [esp-4h] [ebp-1Ch]
  unsigned int v26; // [esp-4h] [ebp-1Ch]
  int v27; // [esp+Ch] [ebp-Ch]
  int fld_e11622; // [esp+10h] [ebp-8h]
  uint32_t *v29; // [esp+14h] [ebp-4h]
  int v30; // [esp+14h] [ebp-4h]
  int i; // [esp+20h] [ebp+8h]
  unsigned int fld_e1163; // [esp+24h] [ebp+Ch]

  result = sub_48C730(this, nArg2, pszArg3);  // 结果 = 技能演出驱动转发（sub_4938F0 帧推进 / sub_491D00 子链属性）
  if ( nArg2 == 3 && pszArg3 == 0 )  // 若 nArg2 == 3 与/或 pszArg3 == 0
  {
    fld_e116 = (*(this + 116) - *(uint32_t *)(*(this + 98) + 192)) / 224;  // this+116 观察者 vector 尾针
    fld_e1162 = -((*(this + 116) - *(uint32_t *)(*(this + 98) + 192)) % 224);  // fld_e1162 = 调 -
    fld_e1163 = fld_e116;
    fld_e11622 = fld_e1162;
    result = (int *)sub_424FF0(this);  // 结果 = 列数换算
    v27 = (int)result;
    if ( fld_e1162 < 640 )
    {
      v7 = 32 * fld_e116;
      for ( i = 32 * fld_e116; ; v7 = i )
      {
        fld_e91 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
        if ( fld_e91 == 0 )  // fld_e91=this+364 pAnimNameStr
          break;
        result = (int *)((*(this + 92) - fld_e91) >> 5);  // this+368〔nBindPos368〕
        if ( fld_e116 >= (unsigned int)result )  // result=this+368 nBindPos368
          break;
        fld_e98 = *(uint32_t *)(*(this + 98) + 196) - *(this + 117);
        fld_e912 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
        v11 = *(uint32_t *)(fld_e912 + v7);  // fld_e912=this+364 pAnimNameStr
        v12 = (uint32_t *)(v7 + fld_e912);  // fld_e912=this+364 pAnimNameStr
        v29 = v12;
        if ( v11 != -1 )
        {
          v25 = v12[1];
          v13 = (uint32_t *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, *v12);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
          v29[2] = sub_418DD0(v13, v25);  // v29[2] = 调 sub_418DD0 返回值
          v7 = i;
        }
        sub_424760(dword_79C0B0, fld_e1162, fld_e98, *(uint32_t *)(*(this + 91) + v7 + 8), 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
        result = (int *)v27;  // result=this+368 nBindPos368
        v14 = fld_e98 + 480;
        v30 = 0;
        if ( v27 > 0 )
        {
          do
          {
            fld_e913 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
            if ( fld_e913 != 0 && (*(this + 92) - fld_e913) >> 5 != 0 )  // this+368〔nBindPos368〕
            {
              fld_e95 = *(this + 95);  // this+380〔attackinfo 指针〕
              if ( fld_e95 != 0 )
                fld_e96 = (*(this + 96) - fld_e95) >> 5;  // this+384〔nAnimNameCap(推断)〕
              else
                fld_e96 = 0;  // fld_e96=this+384 nAnimNameCap
              fld_e914 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
              if ( fld_e914 != 0 )  // fld_e914=this+364 pAnimNameStr
                fld_e92 = (*(this + 92) - fld_e914) >> 5;  // this+368〔nBindPos368〕
              else
                fld_e92 = 0;  // fld_e92=this+368 nBindPos368
              v16 = fld_e96 / fld_e92;
            }
            else
            {
              v16 = 0;
            }
            if ( v30 >= v16 )
            {
              fld_e952 = nullptr;
            }
            else
            {
              fld_e915 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
              if ( fld_e915 != 0 )  // fld_e915=this+364 pAnimNameStr
                fld_e922 = (*(this + 92) - fld_e915) >> 5;  // this+368〔nBindPos368〕
              else
                fld_e922 = 0;  // fld_e922=this+368 nBindPos368
              fld_e952 = (uint32_t *)(*(this + 95) + 32 * (fld_e1163 + v30 * fld_e922));  // fld_e922=this+368 nBindPos368
            }
            if ( *fld_e952 != -1 )
            {
              v26 = fld_e952[1];
              v24 = (uint32_t *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, *fld_e952);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
              fld_e952[2] = sub_418DD0(v24, v26);  // fld_e952[2] = 调 sub_418DD0 返回值
            }
            sub_424760(dword_79C0B0, fld_e11622, v14, fld_e952[2], 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
            v14 += 120;
            result = (int *)++v30;  // result=this+368 nBindPos368
          }
          while ( v30 < v27 );
          fld_e1162 = fld_e11622;
        }
        fld_e1162 += 224;
        ++fld_e1163;
        i += 32;
        fld_e11622 = fld_e1162;
        if ( fld_e1162 >= 640 )
          break;
        fld_e116 = fld_e1163;
      }
    }
  }
  return result;  // result=this+368 nBindPos368
}


// ------------------------------------------------------------
// 0x48CC70 sub_48CC70 —— 取地牢格值（14 列折行、层分块）
//   格号 nArg2 按 14 折行、nArg3 为层：层 < 30 用 this+91 行表；≥30 走 ·sub_48C9D0（块 (nArg3-30)/10、块内行 (nArg3-30)%10）。
//   值取自行记录 +20 的 16 字节条目组第 nArg32 条 +4 指针所指数组第 nArg2%14 项；越界回 2。
// ------------------------------------------------------------
int /*thiscall*/ sub_48CC70(uint32_t *this, int nArg2, int nArg3)  // 实现：取地牢格值（14 列折行、层分块）
{
  int nArg32; // esi
  unsigned int v4; // edi
  int fld_e91; // edx
  int v6; // eax

  nArg32 = nArg3;
  v4 = nArg2 / 14;
  if ( nArg3 >= 30 )
  {
    nArg32 = (nArg3 - 30) % 10;
    v6 = sub_48C9D0(this, (nArg3 - 30) / 10, nArg2 / 14);  // 结果 = 地图行结构定位
  }
  else
  {
    fld_e91 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
    if ( fld_e91 == 0 || v4 >= (*(this + 92) - fld_e91) >> 5 )  // this+368〔nBindPos368〕
      return 2;
    v6 = fld_e91 + 32 * v4;  // fld_e91=this+364 pAnimNameStr
  }
  if ( v6 == 0 )
    return 2;
  return *(uint32_t *)(*(uint32_t *)(16 * nArg32 + *(uint32_t *)(v6 + 20) + 4) + 4 * (nArg2 % 14));
}



// ------------------------------------------------------------
// 0x48CCF0 sub_48CCF0 —— 写地牢格值（同 ·sub_48CC70 索引）
//   定位同 ·sub_48CC70，把 nArg4 写进该格单元；层/行列越界直接返回。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_48CCF0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：写地牢格值（同 ·sub_48CC70 索引）
{
  unsigned int result; // eax
  int nArg32; // esi
  unsigned int v6; // edi
  int fld_e91; // edx

  result = nArg2 / 14;
  nArg32 = nArg3;
  v6 = nArg2 / 14;
  if ( nArg3 >= 30 )
  {
    nArg32 = (nArg3 - 30) % 10;
    result = sub_48C9D0(this, (nArg3 - 30) / 10, nArg2 / 14);  // 结果 = 地图行结构定位
LABEL_6:
    if ( result != 0 )  // 若结果非 0（成功）
    {
      result = *(uint32_t *)(16 * nArg32 + *(uint32_t *)(result + 20) + 4) + 4 * (nArg2 % 14);
      *(uint32_t *)result = nArg4;  // *result = nArg4
    }
    return result;
  }
  fld_e91 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
  if ( fld_e91 != 0 )  // fld_e91=this+364 pAnimNameStr
  {
    result = (*(this + 92) - fld_e91) >> 5;  // this+368〔nBindPos368〕
    if ( v6 < result )  // result=this+368 nBindPos368
    {
      result = fld_e91 + 32 * v6;  // result=this+368 nBindPos368
      goto LABEL_6;
    }
  }
  return result;  // result=this+368 nBindPos368
}



// ------------------------------------------------------------
// 0x48CD70 sub_48CD70 —— 目标区域可达性检查（格值 2 阻挡、1 需消耗）
//   宿主门 vt+40(17)、或 vt+40(33) 且 +672+21 非 0；坐标门 +120/+124 对 640 与 行高乘 120。
//   矩形由 vt+440/448/444/452 按 16/12 换算成格后逐格 ·sub_48CC70：值 2 直接回 0，值 1 还需 vt+436 大于 0【推断：跨格消耗】。
// ------------------------------------------------------------
char /*thiscall*/ sub_48CD70(uint32_t *this, int nArg2)  // 实现：目标区域可达性检查（格值 2 阻挡、1 需消耗）
{
  int fld_e91; // eax
  int fld_e92; // edi
  int pThis_3; // edi
  int v7; // edi
  int v8; // ebx
  int v9; // ecx
  int v10; // edx
  uint32_t *pThis; // ebx
  int fld_e912; // eax
  int fld_e922; // edx
  int fld_e913; // ecx
  int fld_e923; // eax
  int j; // edi
  int v17; // eax
  int v19; // [esp+Ch] [ebp-10h]
  int v20; // [esp+10h] [ebp-Ch]
  int v21; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]
  int v24; // [esp+24h] [ebp+8h]
  int pThis_1D; // [esp+24h] [ebp+8h]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 33) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 672))(nArg2) + 21) != 0 )  // 调虚槽 +672：自身 HP
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2) < 0 )  // 调虚槽 +120：动画对象
      return 0;
    fld_e91 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
    fld_e92 = fld_e91 != 0 ? (*(this + 92) - fld_e91) >> 5 : 0;  // this+368〔nBindPos368〕
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2) >= 224 * fld_e92 )  // 调虚槽 +120：动画对象
      return 0;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2) < 0 )  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      return 0;
    pThis_3 = 120 * (sub_424FF0(this) + 3);  // 结果 = 列数换算
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2) >= pThis_3 )  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      return 0;
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 428))(nArg2) != 0  // 调虚槽 +428
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 432))(nArg2) != 0 )  // 调虚槽 +432
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 448))(nArg2);  // 调虚槽 +448：包围盒上界 = 中心y − 高/2（cnrd 头同上族级覆盖）
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 440))(nArg2) / 16;  // 调虚槽 +440：包围盒左界 = 中心x − 宽/2（AABB 边界族 1B8/1BC/1C0/1C4 之首）
    v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 452))(nArg2);  // 调虚槽 +452：包围盒下界 = 高 + vt+448（cnrd 头同上族级覆盖）
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 444))(nArg2) / 16;  // 调虚槽 +444：包围盒右界 = 宽 + vt+440（cnrd 头以 1B8 1B8/1BC/1C0/1C4…
    pThis_1D = v24 / 12;
    v21 = v9;
    v10 = v8 < 0 ? 0 : v8;
    pThis = this;
    v19 = v10;
    v20 = v7 / 12 < 0 ? 0 : v7 / 12;
    fld_e912 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
    if ( fld_e912 != 0 )  // fld_e912=this+364 pAnimNameStr
      fld_e922 = (*(this + 92) - fld_e912) >> 5;  // this+368〔nBindPos368〕
    else
      fld_e922 = 0;  // fld_e922=this+368 nBindPos368
    if ( 14 * fld_e922 - 1 < v9 )  // fld_e922=this+368 nBindPos368
    {
      fld_e913 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
      if ( fld_e913 != 0 )  // fld_e913=this+364 pAnimNameStr
        fld_e923 = (*(this + 92) - fld_e913) >> 5;  // this+368〔nBindPos368〕
      else
        fld_e923 = 0;  // fld_e923=this+368 nBindPos368
      v21 = 14 * fld_e923 - 1;
    }
    if ( 10 * sub_424FF0(this) + 29 < pThis_1D )  // 列数换算
      pThis_1D = 10 * sub_424FF0(this) + 29;  // 结果 = 列数换算
    for ( i = v19; i <= v21; ++i )
    {
      for ( j = v20; j <= pThis_1D; ++j )
      {
        v17 = sub_48CC70(pThis, i, j) - 1;  // 结果 = 取地牢格值
        if ( v17 != 0 )
        {
          if ( v17 == 1 )
            return 0;
        }
        else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 436))(nArg2) <= 0 )  // 调虚槽 +436
        {
          return 0;
        }
      }
    }
  }
  return 1;  // 返回 1(成功)
}



// ============================================================
// §N 0x48CF90-0x48EED0  发包族（sub_48D1E0/48E1A0 组包器）
// ============================================================
// ------------------------------------------------------------
// 0x48CF90 sub_48CF90 —— 8 字节元素区间插入 n 条（三分支 + 溢出守卫）
//   uArg3 条 8 字节对【推断：id + 值】插到 nArg2 处：尾有容则原位右移，否则 1.5 倍扩容重建
//   （容量上限 0x1FFFFFFF，越界经 ·sub_42CB90）；分支搬运由 ·sub_44BD30/·sub_63A7C0/·sub_5E51F0/·sub_41FEB0 分担；见 ·sub_48D630/·sub_48EED0。
// ------------------------------------------------------------
void /*thiscall*/ sub_48CF90(int this, int nArg2, unsigned int uArg3, int pArg4)  // 实现：8 字节元素区间插入 n 条（三分支 + 溢出守卫）
{
  void *v4; // edx
  int fld_4; // ecx
  unsigned int fld_C; // eax
  int fld_8; // edx
  int fld_82; // edx
  unsigned int v11; // eax
  int fld_87; // edx
  int fld_88; // eax
  char *pMem; // edi
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v17; // ebx
  int fld_83; // eax
  bool v20; // cf
  int v21; // ecx
  int fld_86; // ebx
  int v23; // ebx
  int fld_42; // [esp-18h] [ebp-40h]
  int fld_85; // [esp-Ch] [ebp-34h]
  unsigned int fld_84; // [esp-8h] [ebp-30h]
  int v27; // [esp+0h] [ebp-28h] BYREF
  void *v28[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v29; // [esp+24h] [ebp-4h]
  int v30; // [esp+30h] [ebp+8h]
  int v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int fld_832; // [esp+38h] [ebp+10h]

  v4 = *(void **)(pArg4 + 4);  // pArg4+4〔宿主对象〕
  v28[0] = *(void **)pArg4;
  fld_4 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    fld_C = 0;  // fld_C=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_8 = 0;  // fld_8=this+8 nSkillRec8
    if ( 0x1FFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_42CB90(this);  // CRT 桩（vector 长度异常）
    if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( fld_C >= uArg3 + fld_82 )  // fld_C=this+12 nSkillRec12
    {
      fld_83 = *(uint32_t *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
      v20 = (fld_83 - nArg2) >> 3 < uArg3;  // fld_83=this+8 nSkillRec8
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;  // fld_83=this+8 nSkillRec8
      if ( v20 )
      {
        sub_44BD30(nArg2, fld_83, nArg2 + v21);  // 8 字节元素正向拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 3);  // this+8〔nSkillRec8(推断)〕等 2 字段
        fld_85 = *(uint32_t *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);  // 调 填充补足尾段
        fld_86 = v30 + *(uint32_t *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
        *(uint32_t *)(this + 8) = fld_86;  // this+8〔nSkillRec8(推断)〕等 2 字段
        sub_41FEB0(nArg2, fld_86 - v30, v28);  // 8B 元素区间拷贝
      }
      else
      {
        v23 = fld_83 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);  // 8 字节元素正向拷贝
        sub_44BD00(nArg2, v23, fld_832);  // 8 字节元素反向拷贝
        sub_41FEB0(nArg2, nArg2 + v30, v28);  // 8B 元素区间拷贝
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )  // fld_C=this+12 nSkillRec12
        v11 = (fld_C >> 1) + fld_C;  // fld_C=this+12 nSkillRec12
      else
        v11 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      if ( v11 < uArg3 + fld_87 )  // fld_87=this+8 nSkillRec8
      {
        if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else
          fld_88 = 0;  // fld_88=this+8 nSkillRec8
        v11 = uArg3 + fld_88;
      }
      v31 = 8 * v11;
      pMem = (char *)operator new(8 * v11);  // 分配 8 × v11 字节数组
      fld_42 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, nArg2, pMem);  // 结果 = 8 字节元素正向拷贝
      sub_63A7C0(v32, uArg3, v28);  // 强化结果公共件
      sub_44BD30(nArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);  // 8 字节元素正向拷贝
      fld_43 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
      if ( fld_43 != 0 )  // fld_43=this+4 宿主对象
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_89 = 0;  // fld_89=this+8 nSkillRec8
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )  // fld_43=this+4 宿主对象
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      *(uint32_t *)(this + 12) = &pMem[v31];  // this+12〔nSkillRec12(推断)〕等 2 字段
      *(uint32_t *)(this + 8) = &pMem[8 * v17];  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
    }
  }
}


// ------------------------------------------------------------
// 0x48D1E0 sub_48D1E0 —— 字节缓冲深拷贝构造（this+1/+2/+3 三指针）
//   源区间取 pArg2+4..+8，new 同样大后经 ·sub_4460D0 逐字节拷入，写 this+1 起 begin/end/cap。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_48D1E0(uint32_t *this, int pArg2)  // 字节缓冲深拷贝构造（this+1/+2/+3 三指针）
{
  int v2; // eax
  size_t v4; // edi
  char *pMem; // eax
  int v7; // [esp-18h] [ebp-38h]
  int v8; // [esp-14h] [ebp-34h]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  v11 = &v9;
  pThis = this;
  if ( v2 != 0 )
    v4 = *(uint32_t *)(pArg2 + 8) - v2;  // pArg2+8〔nSkillRec8(推断)〕
  else
    v4 = 0;
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
  if ( v4 != 0 )
  {
    pMem = (char *)operator new(v4);
    *(this + 1) = pMem;  // this+4〔宿主对象〕
    *(this + 2) = pMem;  // this+8〔nSkillRec8(推断)〕
    *(this + 3) = &pMem[v4];  // this+12〔nSkillRec12(推断)〕
    v8 = *(uint32_t *)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    v7 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v12 = 0;
    *(this + 2) = sub_4460D0(v7, v8, pMem);  // 带空判区间拷贝
  }
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x48D290 sub_48D290 —— 24 字节元素容器赋值（截断/扩容/原位三路）
//   尾部截断用 ·sub_48C4B0 覆写；扩容经 ·sub_4FEF30 计数 + ·sub_42D0E0 预留 + ·sub_492530（转发 ·sub_4FF050）；源空则整体释放。
// ------------------------------------------------------------
int /*thiscall*/ sub_48D290(int this, int pArg2)  // 实现：24 字节元素容器赋值（截断/扩容/原位三路）
{
  int v4; // eax
  unsigned int v5; // ecx
  uint32_t *pVecEnd_11; // edi
  unsigned int fld_8; // eax
  int v9; // eax
  unsigned int fld_C; // eax
  int v11; // eax
  int v12; // [esp+10h] [ebp+8h]

  if ( this == pArg2 )
    return this;  // 返回自身指针
  v4 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v4 == 0 || (v5 = (*(uint32_t *)(pArg2 + 8) - v4) / 24) == 0 )  // pArg2+8〔nSkillRec8(推断)〕
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    return this;  // 返回自身指针
  }
  pVecEnd_11 = *(uint32_t **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  if ( pVecEnd_11 != nullptr )  // 若 fld_4 有效（非空）
    fld_8 = (*(uint32_t *)(this + 8) - (int)pVecEnd_11) / 24;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v5 > fld_8 )  // fld_8=this+8 nSkillRec8
  {
    if ( pVecEnd_11 != nullptr )  // 若 fld_4 有效（非空）
      fld_C = (*(uint32_t *)(this + 12) - (int)pVecEnd_11) / 24;  // this+12〔nSkillRec12(推断)〕等 2 字段
    else
      fld_C = 0;  // fld_C=this+12 nSkillRec12
    if ( v5 <= fld_C )  // fld_C=this+12 nSkillRec12
    {
      v12 = *(uint32_t *)(pArg2 + 4) + 24 * sub_4FEF30(this);  // pArg2+4〔宿主对象〕
      sub_4919B0(*(uint32_t *)(pArg2 + 4), v12, pVecEnd_11);  // 转发 sub_48C4B0（24 字节元素区间深拷贝，6 dword 一组）
      *(uint32_t *)(this + 8) = sub_4FF050(v12, *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 8));  // this+8〔nSkillRec8(推断)〕等 2 字段
      return this;  // 返回自身指针
    }
    if ( pVecEnd_11 != nullptr )  // 若 fld_4 有效（非空）
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    v11 = sub_4FEF30(pArg2);  // 调 pArg2+4〔宿主对象〕
    if ( (uint8_t)sub_42D0E0(v11) != 0 )  // vector 预留（24B，同构）
      *(uint32_t *)(this + 8) = sub_492530(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));  // 转发 sub_4FF050（24 字节元素区间拷贝，6 dword 一组）
    return this;  // 返回自身指针
  }
  sub_48C4B0(*(uint32_t **)(pArg2 + 4), *(uint32_t **)(pArg2 + 8), pVecEnd_11);  // 24 字节元素区间拷贝（6 dword 一组）
  v9 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 24 * ((*(uint32_t *)(pArg2 + 8) - v9) / 24);  // this+8〔nSkillRec8(推断)〕等 4 字段
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);  // this+8〔nSkillRec8(推断)〕等 4 字段
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x48D410 sub_48D410 —— 16 字节元素容器赋值（54E 系拷贝）
//   三路与 ·sub_48D290 同构：截断 ·sub_54E1B0、扩容 ·sub_42D090 预留 + ·sub_54E680（转发 ·sub_602460）、原位 ·sub_54E660。
// ------------------------------------------------------------
int /*thiscall*/ sub_48D410(int this, int pArg2)  // 实现：16 字节元素容器赋值（54E 系拷贝）
{
  int v3; // ebx
  unsigned int v4; // eax
  int fld_4; // ecx
  unsigned int fld_8; // edx
  int v8; // eax
  int fld_42; // edi
  unsigned int fld_C; // edx
  int fld_82; // eax
  int v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == pArg2 )
    return this;  // 返回自身指针
  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 4) == 0 )  // pArg2+8〔nSkillRec8(推断)〕
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    return this;  // 返回自身指针
  }
  fld_4 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v4 <= fld_8 )  // fld_8=this+8 nSkillRec8
  {
    sub_54E1B0(v3, *(uint32_t *)(pArg2 + 8), fld_4);  // 结算辅助 2
    v8 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v8 != 0 )
      fld_42 = *(uint32_t *)(this + 4) + 16 * ((*(uint32_t *)(pArg2 + 8) - v8) >> 4);  // this+4〔宿主对象〕等 2 字段
    else
      fld_42 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = fld_42;  // this+8〔nSkillRec8(推断)〕等 2 字段
    return this;  // 返回自身指针
  }
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 4;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    fld_C = 0;  // fld_C=this+12 nSkillRec12
  if ( v4 > fld_C )  // fld_C=this+12 nSkillRec12
  {
    if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    v13 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(pArg2 + 8) - v13) >> 4;  // pArg2+8〔nSkillRec8(推断)〕
    else
      v14 = 0;
    if ( (uint8_t)sub_42D090(v14) != 0 )  // vector 预留（16B，同构）
      *(uint32_t *)(this + 8) = sub_54E680(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));  // 结算转发 2（602460）
    return this;  // 返回自身指针
  }
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_82 = 0;  // fld_82=this+8 nSkillRec8
  v12 = *(uint32_t *)(pArg2 + 4) + 16 * fld_82;  // pArg2+4〔宿主对象〕
  sub_54E660(*(uint32_t *)(pArg2 + 4), v12, *(uint32_t *)(this + 4));  // 结算转发（54E1B0）
  *(uint32_t *)(this + 8) = sub_602460(v12, *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 8));  // 16 字节批量拷贝
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x48D570 sub_48D570 —— 44 字节元素区间拷贝（内层经 ·sub_446AB0 容器赋值）
//   逐条 11 dword：首两 dword 直抄，+8 内层缓冲经 ·sub_446AB0 复制，尾 5 dword 直抄。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48D570(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 44 字节元素区间拷贝（内层经 ·sub_446AB0 容器赋值）
{
  uint32_t *uArg12; // esi
  uint32_t *uArg32; // edi

  uArg12 = uArg1;
  if ( uArg1 == uArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    *uArg32 = *uArg12;
    uArg32[1] = uArg12[1];  // uArg32[1] = 取 uArg12[1]
    sub_446AB0(uArg12 + 2);  // 调 分发器 case 5 配套：填充 3 float 向量结构（sub_4E7DA0 取数）(推断)
    uArg32[6] = uArg12[6];  // uArg32[6] = 取 uArg12[6]
    uArg32[7] = uArg12[7];  // uArg32[7] = 取 uArg12[7]
    uArg32[8] = uArg12[8];  // uArg32[8] = 取 uArg12[8]
    uArg32[9] = uArg12[9];  // uArg32[9] = 取 uArg12[9]
    uArg32[10] = uArg12[10];  // uArg32[10] = 取 uArg12[10]
    uArg12 += 11;
    uArg32 += 11;
  }
  while ( uArg12 != uArg2 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x48D5D0 sub_48D5D0 —— 44 字节元素区间拷贝·反向
//   —— 与 ·sub_48D570 同构（差异：自尾向头递减，供删除前移回路）；·sub_48D700 为其转发。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48D5D0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 44 字节元素区间拷贝·反向
{
  uint32_t *uArg22; // esi
  uint32_t *uArg32; // edi
  int v5; // eax

  uArg22 = uArg2;
  if ( uArg1 == uArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    v5 = *(uArg22 - 11);
    uArg22 -= 11;
    uArg32 -= 11;
    *uArg32 = v5;
    uArg32[1] = uArg22[1];  // uArg32[1] = 取 uArg22[1]
    sub_446AB0(uArg22 + 2);  // 调 分发器 case 5 配套：填充 3 float 向量结构（sub_4E7DA0 取数）(推断)
    uArg32[6] = uArg22[6];  // uArg32[6] = 取 uArg22[6]
    uArg32[7] = uArg22[7];  // uArg32[7] = 取 uArg22[7]
    uArg32[8] = uArg22[8];  // uArg32[8] = 取 uArg22[8]
    uArg32[9] = uArg22[9];  // uArg32[9] = 取 uArg22[9]
    uArg32[10] = uArg22[10];  // uArg32[10] = 取 uArg22[10]
  }
  while ( uArg22 != uArg1 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x48D630 sub_48D630 —— 8 字节元素尾插（原位构造或回落插入器）
//   尾部有空位经 ·sub_63A7C0 原位造 1 条 8 字节对并推进尾指针；否则回落 ·sub_48CF90 扩容插入。
// ------------------------------------------------------------
void /*thiscall*/ sub_48D630(uint32_t *this, int nArg2)  // 实现：8 字节元素尾插（原位构造或回落插入器）
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 3;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) >> 3 )  // this+12〔nSkillRec12(推断)〕
  {
    fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
    sub_63A7C0(fld_e22, 1, nArg2);  // 强化结果公共件
    *(this + 2) = fld_e22 + 8;  // this+8〔nSkillRec8(推断)〕
  }
  else
  {
    sub_48CF90((int)this, (uint32_t *)*(this + 2), 1u, nArg2);  // 8 字节元素区间插入 n 条（三分支 + 溢出守卫）
  }
}



// ------------------------------------------------------------
// 0x48D6A0 sub_48D6A0 —— 44 字节元素区间填充（同源覆写）
//   把 pArg3 模板逐条构造进 [uArg1, uArg2)。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48D6A0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // 44 字节元素区间填充（同源覆写）
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 11 )
  {
    *i = *pArg3;
    i[1] = pArg3[1];  // i[1] = 取 pArg3[1]
    sub_446AB0(pArg3 + 2);  // 调 分发器 case 5 配套：填充 3 float 向量结构（sub_4E7DA0 取数）(推断)
    i[6] = pArg3[6];  // i[6] = 取 pArg3[6]
    i[7] = pArg3[7];  // i[7] = 取 pArg3[7]
    i[8] = pArg3[8];  // i[8] = 取 pArg3[8]
    i[9] = pArg3[9];  // i[9] = 取 pArg3[9]
    i[10] = pArg3[10];  // i[10] = 取 pArg3[10]
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48D700 sub_48D700 —— 44 字节元素拷贝·转发
//   —— 直接转发 ·sub_48D5D0，无附加逻辑。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48D700(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 44 字节元素拷贝·转发
{
  return sub_48D5D0(uArg1, uArg2, uArg3);  // 44 字节元素区间拷贝·反向
}



// ------------------------------------------------------------
// 0x48D720 sub_48D720 —— 44 字节元素区间拷贝·构造（内层新建）
//   与 ·sub_48D570 同形，但内层缓冲经 ·sub_48D1E0 逐条新建（构造语义，非赋值复用）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48D720(uint32_t *pArg1, uint32_t *uArg2, uint32_t *uArg3)  // 44 字节元素区间拷贝·构造（内层新建）
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
    if ( uArg32 != nullptr )  // 若 uArg32 有效（非空）
    {
      *uArg32 = *pArg1;
      uArg32[1] = pArg1[1];  // uArg32[1] = 取 pArg1[1]
      sub_48D1E0(uArg32 + 2, (int)(pArg1 + 2));  // 字节缓冲深拷贝构造（this+1/+2/+3 三指针）
      uArg32[6] = pArg1[6];  // uArg32[6] = 取 pArg1[6]
      uArg32[7] = pArg1[7];  // uArg32[7] = 取 pArg1[7]
      uArg32[8] = pArg1[8];  // uArg32[8] = 取 pArg1[8]
      uArg32[9] = pArg1[9];  // uArg32[9] = 取 pArg1[9]
      uArg32[10] = pArg1[10];  // uArg32[10] = 取 pArg1[10]
    }
    uArg32 += 11;
    LOBYTE(v7) = 0;
    pArg1 += 11;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x48D800 sub_48D800 —— 44 字节元素单条删除
//   ·sub_48D570 把其后区间前移 1 条，尾条内层经 ·sub_42C220 释清，尾指针减 11 dword；新尾回填 uArg2。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_48D800(uint32_t **this, uint32_t *uArg2, uint32_t *pArg3)  // 44 字节元素单条删除
{
  int fld_e2; // edi
  int v5; // esi

  sub_48D570(pArg3 + 11, *(this + 2), pArg3);  // 44 字节元素区间拷贝（内层经 ·sub_446AB0 容器赋值）
  fld_e2 = (int)*(this + 2);  // this+8〔nSkillRec8(推断)〕
  v5 = fld_e2 - 44;
  do
  {
    sub_42C220(v5);  // 缓冲释清（+12 组）
    v5 += 44;
  }
  while ( v5 != fld_e2 );  // fld_e2=this+8 nSkillRec8
  *(this + 2) -= 11;  // this+8〔nSkillRec8(推断)〕
  *uArg2 = pArg3;
  return uArg2;
}



// ------------------------------------------------------------
// 0x48D860 sub_48D860 —— 44 字节元素 n 条填充构造（内层深拷贝）
//   每条经 ·sub_48D1E0 新建内层缓冲后抄字段；·sub_48DC80 为回尾指针转发。
// ------------------------------------------------------------
void /*cdecl*/ sub_48D860(uint32_t *uArg1, int nArg2, uint32_t *pArg3)  // 实现：44 字节元素 n 条填充构造（内层深拷贝）
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
    if ( uArg12 != nullptr )  // 若 uArg12 有效（非空）
    {
      *uArg12 = *pArg3;
      uArg12[1] = pArg3[1];  // uArg12[1] = 取 pArg3[1]
      sub_48D1E0(uArg12 + 2, (int)(pArg3 + 2));  // 字节缓冲深拷贝构造（this+1/+2/+3 三指针）
      uArg12[6] = pArg3[6];  // uArg12[6] = 取 pArg3[6]
      uArg12[7] = pArg3[7];  // uArg12[7] = 取 pArg3[7]
      uArg12[8] = pArg3[8];  // uArg12[8] = 取 pArg3[8]
      uArg12[9] = pArg3[9];  // uArg12[9] = 取 pArg3[9]
      uArg12[10] = pArg3[10];  // uArg12[10] = 取 pArg3[10]
    }
    uArg12 += 11;
    LOBYTE(v5) = 0;
    --nArg2;
  }
}



// ------------------------------------------------------------
// 0x48D940 sub_48D940 —— 16 字节元素区间构造（内层 ·sub_435020）
//   逐条交 ·sub_435020 深拷贝（含内层 int 容器）构造，回尾指针；·sub_48E1A0 容器拷贝构造的底层。
// ------------------------------------------------------------
char */*cdecl*/ sub_48D940(char *pszArg1, char *pszArg2, char *pszArg3)  // 16 字节元素区间构造（内层 ·sub_435020）
{
  char *pszArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pszArg32 = pszArg3;
  v6[4] = v6;
  v6[3] = pszArg3;
  v7 = 0;
  while ( pszArg1 != pszArg2 )  // 当 pszArg1 != pszArg2 循环
  {
    LOBYTE(v7) = 1;
    if ( pszArg32 != nullptr )  // 若 pszArg32 有效（非空）
      sub_435020(pszArg1);  // uint32 向量整体赋值
    pszArg32 += 16;
    LOBYTE(v7) = 0;
    pszArg1 += 16;
  }
  return pszArg32;
}



// ------------------------------------------------------------
// 0x48D9D0 sub_48D9D0 —— 战场块字段复位与缓冲释放
//   清 +392/+396/+464..+500 字段并释放 +492 缓冲；尾部落 ·sub_42E620（+504 的 44 字节条目表）。
// ------------------------------------------------------------
int /*thiscall*/ sub_48D9D0(int this)  // 实现：战场块字段复位与缓冲释放
{
  *(uint32_t *)(this + 392) = 0;
  *(uint8_t *)(this + 396) = 0;  // this+396〔uReflectCtx(推断)〕
  *(uint32_t *)(this + 464) = 0;  // this+464 仅见复位
  *(uint32_t *)(this + 468) = 0;
  *(uint8_t *)(this + 472) = 0;
  *(uint32_t *)(this + 476) = 0;
  *(uint32_t *)(this + 480) = 0;
  *(uint32_t *)(this + 484) = 0;
  if ( *(uint32_t *)(this + 492) != 0 )
    j__free(*(void **)(this + 492));  // 调 堆释放
  *(uint32_t *)(this + 492) = 0;
  *(uint32_t *)(this + 496) = 0;
  *(uint32_t *)(this + 500) = 0;
  return sub_42E620(this + 504);  // 释放 +4 缓冲（44B 条目）
}



// ------------------------------------------------------------
// 0x48DA40 sub_48DA40 —— 地图阻挡掩码刷新（快照 → 活缓冲，再叠记录矩形）
//   +484 快照 qmemcpy 覆盖 +480 活缓冲（行长 14 乘 行数、高 10 乘 (列数 + 3)）。
//   遍历 +127 表 44 字节记录（首两 dword 为键对，先删命中项 ·sub_48D800）：无坐标记录按对象 vt+440/448/444/452 现算矩形，再把标志字节铺满矩形格。
//   ·sub_45EBE0 按 (nArg2, nArg3) 取对象并 RTDynamicCast 到 CNRDPassiveObject 取掩码。
// ------------------------------------------------------------
char /*thiscall*/ sub_48DA40(int *this, int nArg2, int nArg3, char pszArg4)  // 实现：地图阻挡掩码刷新（快照 → 活缓冲，再叠记录矩形）
{
  int *pThis; // ebx
  int fld_e120; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // esi
  int v9; // ecx
  uint32_t *v10; // edi
  uint32_t *v11; // eax
  uint8_t *pObj2; // eax
  uint8_t *pObj; // esi
  int v14; // edx
  bool v15; // cc
  int v16; // esi
  int v17; // ecx
  int i; // eax
  int v19; // eax
  int fld_e1202; // [esp+8h] [ebp-10h]
  int v23; // [esp+10h] [ebp-8h] BYREF
  int v24; // [esp+14h] [ebp-4h]

  pThis = this;
  fld_e120 = *(this + 120);  // this+120 动画对象指针
  if ( fld_e120 != 0 )
  {
    fld_e120 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
    if ( fld_e120 != 0 )
    {
      fld_e120 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
      if ( *(uint32_t *)(fld_e120 + 104) != 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
        v6 = pThis[91];
        if ( v6 != 0 )
          v7 = (pThis[92] - v6) >> 5;
        else
          v7 = 0;
        v8 = 14 * v7;
        v24 = 14 * v7;
        fld_e120 = 10 * (sub_424FF0(pThis) + 3);  // 结果 = 列数换算
        qmemcpy((void *)pThis[120], (const void *)pThis[121], v8 * fld_e120);  // 调 内存块拷贝(内联展开)
        fld_e1202 = fld_e120;
        LOBYTE(fld_e120) = pszArg4;
        if ( pszArg4 != 0 )
        {
          fld_e120 = pThis[127];
          v9 = pThis[128];
          if ( fld_e120 != v9 )
          {
            while ( *(uint32_t *)fld_e120 != nArg2 || *(uint32_t *)(fld_e120 + 4) != nArg3 )
            {
              fld_e120 += 44;
              if ( fld_e120 == v9 )
                goto LABEL_14;
            }
            LOBYTE(fld_e120) = sub_48D800(&v23, fld_e120);  // 44 字节元素单条删除
          }
        }
LABEL_14:
        v10 = (uint32_t *)pThis[127];
        if ( v10 != (uint32_t *)pThis[128] )
        {
          do
          {
            if ( *v10 == nArg2 && v10[1] == nArg3 && pszArg4 == 0 )
            {
              v11 = (uint32_t *)sub_45EBE0(nArg2, nArg3);  // 调 对象查找
              pObj2 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                      v11,
                      0,
                      &CNRDObject `RTTI Type Descriptor',
                      &CNRDPassiveObject `RTTI Type Descriptor',
                      0);
              pObj = pObj2;
              if ( pObj2 != nullptr )  // 若 pObj2 有效（非空）
              {
                v10[6] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj2 + 440))(pObj2) / 16 - 1;  // 调虚槽 +440：包围盒左界 = 中心x − 宽/2（AABB 边界族 1B8/1BC/1C0/1C4 之首）
                v10[7] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 448))(pObj) / 12 - 1;  // 调虚槽 +448：包围盒上界 = 中心y − 高/2（cnrd 头同上族级覆盖）
                v10[8] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 444))(pObj) / 16 + 1;  // 调虚槽 +444：包围盒右界 = 宽 + vt+440（cnrd 头以 1B8 1B8/1BC/1C0/1C4…
                v10[9] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 452))(pObj) / 12;  // 调虚槽 +452：包围盒下界 = 高 + vt+448（cnrd 头同上族级覆盖）
                v10[10] = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 672))(pObj) + 8);  // 调虚槽 +672：自身 HP
              }
            }
            v14 = v10[7];
            v15 = v14 <= v10[9];
            v23 = v14;
            if ( v15 )
            {
              v16 = v24;
              v17 = v24 * v14;
              do
              {
                if ( v14 >= 0 && v14 < fld_e1202 )  // 若 v14 >= 0 与/或 v14 < fld_e1202
                {
                  for ( i = v10[6]; i <= v10[8]; ++i )
                  {
                    if ( i >= 0 && i < v16 )  // 若 i >= 0 与/或 i < v16
                    {
                      *(uint8_t *)(v17 + i + pThis[120]) = *((uint8_t *)v10 + 40);
                      pThis = this;
                      v14 = v23;
                      v16 = v24;
                    }
                  }
                }
                v19 = v10[9];
                ++v14;
                v17 += v16;
                v23 = v14;
              }
              while ( v14 <= v19 );
            }
            fld_e120 = pThis[128];
            v10 += 11;
          }
          while ( v10 != (uint32_t *)fld_e120 );
        }
      }
    }
  }
  return fld_e120;
}


// ------------------------------------------------------------
// 0x48DC80 sub_48DC80 —— 44 字节元素填充·转发（回尾指针）
//   —— 转发 ·sub_48D860 后返回 pArg1 + 11 乘 nArg2。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_48DC80(uint32_t *pArg1, int nArg2, uint32_t *uArg3)  // 44 字节元素填充·转发（回尾指针）
{
  sub_48D860(pArg1, nArg2, uArg3);  // 44 字节元素 n 条填充构造（内层深拷贝）
  return &pArg1[11 * nArg2];
}



// ------------------------------------------------------------
// 0x48DCB0 sub_48DCB0 —— 大型发包（sub_48D1E0 组包器：sub_48D570/48D6A0 字段族 + sub_527B90 提交）
// ------------------------------------------------------------
void /*thiscall*/ sub_48DCB0(int *this, char *pszArg2, unsigned int uArg3, int *pDwArg4)  // 实现：大型发包（sub_48D1E0 组包器：sub_48D570/48D6A0 字段族 + sub_527B90 提交）
{
  int v4; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int pVecEnd_13; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v16; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v20; // edi
  int fld_e14; // eax
  uint32_t *fld_e23; // ecx
  int fld_e26; // edi
  uint32_t *fld_e12; // [esp-18h] [ebp-68h]
  uint32_t *fld_e25; // [esp-Ch] [ebp-5Ch]
  int fld_e24; // [esp-8h] [ebp-58h]
  int v28; // [esp+0h] [ebp-50h] BYREF
  uint32_t v29[2]; // [esp+Ch] [ebp-44h] BYREF
  int v30; // [esp+14h] [ebp-3Ch] BYREF
  void *v31; // [esp+18h] [ebp-38h]
  int v32; // [esp+24h] [ebp-2Ch]
  int v33; // [esp+28h] [ebp-28h]
  int v34; // [esp+2Ch] [ebp-24h]
  int v35; // [esp+30h] [ebp-20h]
  int v36; // [esp+34h] [ebp-1Ch]
  void *Block; // [esp+38h] [ebp-18h]
  int *pThis; // [esp+3Ch] [ebp-14h]
  int *v39; // [esp+40h] [ebp-10h]
  int v40; // [esp+4Ch] [ebp-4h]
  uint32_t *v41; // [esp+58h] [ebp+8h]
  uint32_t *v42; // [esp+5Ch] [ebp+Ch]
  int v43; // [esp+60h] [ebp+10h]
  uint32_t *fld_e232; // [esp+60h] [ebp+10h]

  v4 = *pDwArg4;
  v6 = pDwArg4[1];
  v39 = &v28;
  v29[1] = v6;
  pThis = this;
  v29[0] = v4;
  sub_48D1E0(&v30, (int)(pDwArg4 + 2));  // 字节缓冲深拷贝构造（this+1/+2/+3 三指针）
  v7 = pDwArg4[7];
  v8 = pDwArg4[8];
  v32 = pDwArg4[6];
  v9 = pDwArg4[9];
  v33 = v7;
  v10 = pDwArg4[10];
  v34 = v8;
  v35 = v9;
  v36 = v10;
  pVecEnd_13 = *(this + 1);  // this+4〔宿主对象〕
  fld_e3 = 0;
  v40 = 0;
  if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - pVecEnd_13) / 44;  // this+12〔nSkillRec12(推断)〕
  if ( uArg3 != 0 )
  {
    if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - pVecEnd_13) / 44;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
    if ( 97612893 - fld_e2 < uArg3 )  // fld_e2=this+8 nSkillRec8
      sub_42CB90(this);  // CRT 桩（vector 长度异常）
    if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - pVecEnd_13) / 44;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e23 = (uint32_t *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
      fld_e232 = fld_e23;  // fld_e23=this+8 nSkillRec8
      if ( ((char *)fld_e23 - pszArg2) / 44 >= uArg3 )  // fld_e23=this+8 nSkillRec8
      {
        v41 = &fld_e23[-11 * uArg3];  // fld_e23=this+8 nSkillRec8
        *(this + 2) = (int)sub_48D720(v41, fld_e23, fld_e23);  // 44 字节元素区间拷贝·构造（内层新建）
        sub_48D700(pszArg2, v41, fld_e232);  // 44 字节元素拷贝·转发
        sub_48D6A0(pszArg2, &pszArg2[44 * uArg3], v29);  // 44 字节元素区间填充（同源覆写）
      }
      else
      {
        sub_48D720(pszArg2, fld_e23, &pszArg2[44 * uArg3]);  // 44 字节元素区间拷贝·构造（内层新建）
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 44;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = (uint32_t *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
        LOBYTE(v40) = 3;
        sub_48DC80(fld_e25, fld_e24, v29);  // 44 字节元素填充·转发（回尾指针）
        fld_e26 = 44 * uArg3 + *(this + 2);  // this+8〔nSkillRec8〕
        *(this + 2) = fld_e26;  // this+8〔nSkillRec8(推断)〕
        v40 = 0;
        sub_48D6A0(pszArg2, (uint32_t *)(fld_e26 - 44 * uArg3), v29);  // 44 字节元素区间填充（同源覆写）
      }
    }
    else
    {
      if ( 97612893 - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 nSkillRec12
        v16 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 nSkillRec12
      else
        v16 = 0;
      if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - pVecEnd_13) / 44;  // this+8〔nSkillRec8(推断)〕
      else
        fld_e27 = 0;  // fld_e27=this+8 nSkillRec8
      if ( v16 < uArg3 + fld_e27 )  // fld_e27=this+8 nSkillRec8
        v16 = uArg3 + sub_527B90(this);  // 调 取 size
      v43 = 44 * v16;
      pMem = (char *)operator new(44 * v16);  // 分配 44 × v16 字节数组
      fld_e12 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
      Block = pMem;
      LOBYTE(v40) = 1;
      v42 = sub_48D720(fld_e12, pszArg2, pMem);  // 结果 = 44 字节元素区间拷贝·构造（内层新建）
      sub_48D860(v42, uArg3, v29);  // 44 字节元素 n 条填充构造（内层深拷贝）
      sub_48D720(pszArg2, (uint32_t *)*(this + 2), &v42[11 * uArg3]);  // 44 字节元素区间拷贝·构造（内层新建）
      fld_e13 = *(this + 1);  // this+4〔宿主对象〕
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 44;  // this+8〔nSkillRec8(推断)〕
      v20 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);  // this+4〔宿主对象〕
      if ( fld_e14 != 0 )  // fld_e14=this+4 宿主对象
      {
        sub_42DDA0(fld_e14, *(this + 2));  // 44 字节条目组析构
        j__free((void *)*(this + 1));  // this+4〔宿主对象〕
      }
      *(this + 3) = (int)&pMem[v43];  // this+12〔nSkillRec12(推断)〕
      *(this + 2) = (int)&pMem[44 * v20];  // this+8〔nSkillRec8(推断)〕
      *(this + 1) = (int)pMem;  // this+4〔宿主对象〕
    }
  }
  if ( v31 != nullptr )  // 若 v31 有效（非空）
    j__free(v31);  // 调 堆释放
}


// ------------------------------------------------------------
// 0x48DFD0 sub_48DFD0 —— 16 字节元素容器赋值（·sub_474CA0/·sub_474680 深拷贝）
//   截断用 ·sub_489540 + ·sub_42CC00；扩容先 ·sub_42D520/·sub_42D540 释放再 ·sub_42D090 预留 + ·sub_474CA0 拷；原位用 ·sub_489690 + ·sub_474680。
// ------------------------------------------------------------
int /*thiscall*/ sub_48DFD0(int this, int pArg2)  // 实现：16 字节元素容器赋值（·sub_474CA0/·sub_474680 深拷贝）
{
  int v3; // ebx
  unsigned int v4; // eax
  int fld_4; // ecx
  unsigned int fld_8; // edx
  int v8; // eax
  int v9; // eax
  int fld_42; // edi
  unsigned int fld_C; // edx
  int fld_82; // eax
  void *v13; // ebx
  int v14; // ecx
  int v15; // eax

  if ( this == pArg2 )
    return this;  // 返回自身指针
  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 4) == 0 )  // pArg2+8〔nSkillRec8(推断)〕
  {
    sub_42D540(this);  // 释放 +4 缓冲（16B 条目）
    return this;  // 返回自身指针
  }
  fld_4 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v4 <= fld_8 )  // fld_8=this+8 nSkillRec8
  {
    v8 = sub_489540(v3, *(uint32_t *)(pArg2 + 8), fld_4);  // 结果 = 16 字节元素区间拷贝
    sub_42CC00(v8, *(uint32_t *)(this + 8));  // 16 字节槽组释放
    v9 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v9 != 0 )
      fld_42 = *(uint32_t *)(this + 4) + 16 * ((*(uint32_t *)(pArg2 + 8) - v9) >> 4);  // this+4〔宿主对象〕等 2 字段
    else
      fld_42 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = fld_42;  // this+8〔nSkillRec8(推断)〕等 2 字段
    return this;  // 返回自身指针
  }
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 4;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    fld_C = 0;  // fld_C=this+12 nSkillRec12
  if ( v4 > fld_C )  // fld_C=this+12 nSkillRec12
  {
    if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    {
      sub_42D520(fld_4, *(uint32_t *)(this + 8));  // 转发 ·0x42CC00
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    }
    v14 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v14 != 0 )
      v15 = (*(uint32_t *)(pArg2 + 8) - v14) >> 4;  // pArg2+8〔nSkillRec8(推断)〕
    else
      v15 = 0;
    if ( (uint8_t)sub_42D090(v15) != 0 )  // vector 预留（16B，同构）
      *(uint32_t *)(this + 8) = sub_474CA0(this, *(void **)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(void **)(this + 4));  // this+8〔nSkillRec8(推断)〕等 3 字段
    return this;  // 返回自身指针
  }
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_82 = 0;  // fld_82=this+8 nSkillRec8
  v13 = (void *)(*(uint32_t *)(pArg2 + 4) + 16 * fld_82);  // pArg2+4〔宿主对象〕
  sub_489690(*(uint32_t *)(pArg2 + 4), (int)v13, *(uint32_t *)(this + 4));  // 16 字节元素区间拷贝·转发
  *(uint32_t *)(this + 8) = sub_474680(v13, *(uint32_t *)(pArg2 + 8), *(void **)(this + 8), this);  // this+8〔nSkillRec8(推断)〕等 2 字段
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x48E130 sub_48E130 —— 44 字节元素尾插并回传位置
//   ·sub_48DCB0 扩容插入 1 条，回填插入点绝对地址到 uArg2（pszArg3 为旧基址折算下标）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_48E130(int *this, uint32_t *uArg2, char *pszArg3, int *pDwArg4)  // 44 字节元素尾插并回传位置
{
  int pVecEnd_5; // esi
  int v6; // esi

  pVecEnd_5 = *(this + 1);  // this+4〔宿主对象〕
  if ( pVecEnd_5 != 0 && (*(this + 2) - pVecEnd_5) / 44 != 0 )  // this+8〔nSkillRec8(推断)〕
    v6 = (int)&pszArg3[-pVecEnd_5] / 44;  // pVecEnd_5=this+4 宿主对象
  else
    v6 = 0;
  sub_48DCB0(this, pszArg3, 1u, pDwArg4);  // 大型发包（sub_48D1E0 组包器：sub_48D570/48D6A0 字段族 + su
  *uArg2 = *(this + 1) + 44 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x48E1A0 sub_48E1A0 —— 16 字节元素容器拷贝构造（预留 + ·sub_48D940）
//   按源条数 ·sub_42D090 预留，再 ·sub_48D940 逐条深拷贝并把尾写 this+2。
// ------------------------------------------------------------
char **/*thiscall*/ sub_48E1A0(char **this, int pArg2)  // 16 字节元素容器拷贝构造（预留 + ·sub_48D940）
{
  int v3; // ecx
  int v4; // eax
  char *v6; // [esp-14h] [ebp-34h]
  char *v7; // [esp-10h] [ebp-30h]
  char *fld_e1; // [esp-Ch] [ebp-2Ch]
  uint32_t v9[8]; // [esp+0h] [ebp-20h] BYREF

  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  v9[4] = v9;
  v9[3] = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 4;  // pArg2+8〔nSkillRec8(推断)〕
  else
    v4 = 0;
  if ( (uint8_t)sub_42D090(v4) != 0 )  // vector 预留（16B，同构）
  {
    fld_e1 = *(this + 1);  // this+4〔宿主对象〕
    v7 = *(char **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    v6 = *(char **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v9[7] = 0;
    *(this + 2) = sub_48D940(v6, v7, fld_e1);  // 16 字节元素区间构造（内层 ·sub_435020）
  }
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x48E240 sub_48E240 —— 32 字节元素区间拷贝·正向
//   前 3 dword 与 1 字节标志直抄，+16 内层 16 字节容器经 ·sub_48DFD0 深拷贝。
// ------------------------------------------------------------
int /*cdecl*/ sub_48E240(int nArg1, int nArg2, int nArg3)  // 实现：32 字节元素区间拷贝·正向
{
  int nArg12; // esi
  int nArg32; // edi

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    *(uint32_t *)nArg32 = *(uint32_t *)nArg12;
    *(uint32_t *)(nArg32 + 4) = *(uint32_t *)(nArg12 + 4);  // nArg32+4〔宿主对象〕
    *(uint32_t *)(nArg32 + 8) = *(uint32_t *)(nArg12 + 8);  // nArg32+8〔nSkillRec8(推断)〕
    *(uint8_t *)(nArg32 + 12) = *(uint8_t *)(nArg12 + 12);  // nArg32+12〔nSkillRec12(推断)〕
    sub_48DFD0(nArg32 + 16, nArg12 + 16);  // 16 字节元素容器赋值（·sub_474CA0/·sub_474680 深拷贝）
    nArg12 += 32;
    nArg32 += 32;
  }
  while ( nArg12 != nArg2 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x48E290 sub_48E290 —— 32 字节元素区间拷贝·反向
//   —— 与 ·sub_48E240 同构（差异：自尾向头递减，供区间删除回路）；·sub_48E460 为其转发。
// ------------------------------------------------------------
int /*cdecl*/ sub_48E290(int nArg1, int nArg2, int nArg3)  // 实现：32 字节元素区间拷贝·反向
{
  int nArg22; // esi
  int nArg32; // edi
  int v5; // eax

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    v5 = *(uint32_t *)(nArg22 - 32);
    nArg22 -= 32;
    nArg32 -= 32;
    *(uint32_t *)nArg32 = v5;  // *nArg32 = v5
    *(uint32_t *)(nArg32 + 4) = *(uint32_t *)(nArg22 + 4);  // nArg32+4〔宿主对象〕
    *(uint32_t *)(nArg32 + 8) = *(uint32_t *)(nArg22 + 8);  // nArg32+8〔nSkillRec8(推断)〕
    *(uint8_t *)(nArg32 + 12) = *(uint8_t *)(nArg22 + 12);  // nArg32+12〔nSkillRec12(推断)〕
    sub_48DFD0(nArg32 + 16, nArg22 + 16);  // 16 字节元素容器赋值（·sub_474CA0/·sub_474680 深拷贝）
  }
  while ( nArg22 != nArg1 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x48E2E0 sub_48E2E0 —— 地砖记录装载（路径拼接 + 资源 id/图像句柄）
//   vt+12 拼 目录与文件 路径（格式 %s%s）→ ·sub_40BF00 解码（szPassword）→ ·sub_4BC700 部件路径转资源 id → ·sub_418DD0 取图像句柄。
//   失败打 TILE CREATE FAIL! FILENAME[%s]；尾部 ·sub_48DFD0 深拷贝记录内层 16 字节容器（+36 起）。
// ------------------------------------------------------------
int /*stdcall*/ sub_48E2E0(int pArg1, int nArg2, const char *ArgList)  // 实现：地砖记录装载（路径拼接 + 资源 id/图像句柄）
{
  unsigned int *v3; // eax
  int v4; // esi
  int v6; // eax
  uint32_t *v7; // eax
  unsigned int v8; // [esp-4h] [ebp-Ch]

  v3 = (unsigned int *)(*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84D8 + 12))(  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
                         dword_8F84D8,
                         "%s%s",  // 字符串 “%s%s”
                         nArg2,
                         ArgList);
  v4 = (int)v3;
  if ( v3 == nullptr )  // 若 v3 为空
    return off_77F3FC("TILE CREATE FAIL! FILENAME[%s]", ArgList);  // 字符串 “TILE CREATE FAIL! FILENAME[%s]”
  if ( sub_40BF00((std::_String_base *)v3, 0, v3[5], szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    v6 = sub_4BC700((uint32_t *)dword_8F84BC, v4);  // 部件路径 → 资源 id
    *(uint32_t *)pArg1 = v6;  // *pArg1 = v6
    *(uint32_t *)(pArg1 + 4) = *(uint32_t *)(v4 + 28);  // pArg1+4〔宿主对象〕
    v8 = *(uint32_t *)(v4 + 28);
    v7 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v6);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    *(uint32_t *)(pArg1 + 8) = sub_418DD0(v7, v8);  // 调 资源句柄 (101)
  }
  *(uint8_t *)(pArg1 + 12) = *(uint8_t *)(v4 + 32);  // pArg1+12〔nSkillRec12(推断)〕
  return sub_48DFD0(pArg1 + 16, v4 + 36);  // 16 字节元素容器赋值（·sub_474CA0/·sub_474680 深拷贝）
}



// ------------------------------------------------------------
// 0x48E380 sub_48E380 —— 44 字节元素尾插（原位填充或回落插入器）
//   尾部空位经 ·sub_48D860 原位造 1 条；否则回落 ·sub_48E130 扩容插入。
// ------------------------------------------------------------
void /*thiscall*/ sub_48E380(int this, int *pDwArg2)  // 实现：44 字节元素尾插（原位填充或回落插入器）
{
  int pVecEnd_6; // edi
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi

  pVecEnd_6 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( pVecEnd_6 != 0 )  // fld_4=this+4 宿主对象
    fld_8 = (*(uint32_t *)(this + 8) - pVecEnd_6) / 44;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( pVecEnd_6 != 0 && fld_8 < (*(uint32_t *)(this + 12) - pVecEnd_6) / 44 )  // this+12〔nSkillRec12(推断)〕等 2 字段
  {
    fld_82 = *(uint32_t **)(this + 8);  // this+32〔nHeight(推断)〕
    sub_48D860(fld_82, 1, pDwArg2);  // 44 字节元素 n 条填充构造（内层深拷贝）
    *(uint32_t *)(this + 8) = fld_82 + 11;  // this+8〔nSkillRec8(推断)〕等 2 字段
  }
  else
  {
    sub_48E130((int *)this, &pDwArg2, *(char **)(this + 8), pDwArg2);  // 44 字节元素尾插并回传位置
  }
}



// ------------------------------------------------------------
// 0x48E410 sub_48E410 —— 32 字节元素区间填充（同源覆写）
//   把 pArg3 模板逐条构造（含内层 ·sub_48DFD0 深拷贝）进 [nArg1, nArg2)。
// ------------------------------------------------------------
int /*cdecl*/ sub_48E410(int nArg1, int nArg2, int pArg3)  // 实现：32 字节元素区间填充（同源覆写）
{
  int result; // eax
  int i; // esi

  result = nArg2;
  for ( i = nArg1; i != nArg2; i += 32 )
  {
    *(uint32_t *)i = *(uint32_t *)pArg3;
    *(uint32_t *)(i + 4) = *(uint32_t *)(pArg3 + 4);  // pArg3+4〔宿主对象〕
    *(uint32_t *)(i + 8) = *(uint32_t *)(pArg3 + 8);  // pArg3+8〔nSkillRec8(推断)〕
    *(uint8_t *)(i + 12) = *(uint8_t *)(pArg3 + 12);  // pArg3+12〔nSkillRec12(推断)〕
    sub_48DFD0(i + 16, pArg3 + 16);  // 16 字节元素容器赋值（·sub_474CA0/·sub_474680 深拷贝）
    result = nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48E460 sub_48E460 —— 32 字节元素拷贝·转发
//   —— 直接转发 ·sub_48E290，无附加逻辑。
// ------------------------------------------------------------
int /*cdecl*/ sub_48E460(int nArg1, int nArg2, int nArg3)  // 实现：32 字节元素拷贝·转发
{
  return sub_48E290(nArg1, nArg2, nArg3);  // 32 字节元素区间拷贝·反向
}



// ------------------------------------------------------------
// 0x48E480 sub_48E480 —— 动态对象阻挡登记（掩码铺格 + 记录追加）
//   遍历对象表 +120（指针数组，上限 +124），筛 vt+40(33) 且 vt+428/+432 非 0 且 +672+8 有掩码者。
//   按 16/12 换算矩形把掩码字节铺入 +480 地牢格；键对经 ·sub_474950 入 8 字节表，44 字节记录经 ·sub_48E380 追加到 +127 表。
// ------------------------------------------------------------
int /*thiscall*/ sub_48E480(int this, int pArg2)  // 实现：动态对象阻挡登记（掩码铺格 + 记录追加）
{
  int result; // eax
  int pArg22; // esi
  int v5; // ecx
  int fld_16C; // ecx
  int fld_170; // eax
  unsigned int v8; // ebx
  int v9; // ecx
  int *v10; // esi
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // edi
  int v15; // edx
  int v16; // eax
  int v17; // ebx
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // ecx
  int i; // edi
  int v23; // eax
  uint32_t v24[3]; // [esp+8h] [ebp-64h] BYREF
  int v25; // [esp+14h] [ebp-58h]
  int v26; // [esp+18h] [ebp-54h]
  int v27; // [esp+1Ch] [ebp-50h]
  int v28; // [esp+20h] [ebp-4Ch]
  int v29; // [esp+24h] [ebp-48h]
  int v30; // [esp+28h] [ebp-44h]
  int v31; // [esp+2Ch] [ebp-40h]
  int v32; // [esp+30h] [ebp-3Ch]
  uint32_t v33[2]; // [esp+34h] [ebp-38h] BYREF
  int pThis_3; // [esp+3Ch] [ebp-30h]
  unsigned int v35; // [esp+40h] [ebp-2Ch]
  int v36; // [esp+44h] [ebp-28h]
  int v37; // [esp+48h] [ebp-24h]
  int v38; // [esp+4Ch] [ebp-20h]
  int pThis; // [esp+50h] [ebp-1Ch]
  int v40; // [esp+54h] [ebp-18h]
  int v41; // [esp+58h] [ebp-14h]
  int v42; // [esp+5Ch] [ebp-10h]
  int v43; // [esp+68h] [ebp-4h]

  result = *(uint32_t *)(this + 480);
  pThis = this;
  if ( result != 0 )  // 若结果非 0（成功）
  {
    if ( *(uint32_t *)(this + 492) != 0 )
      j__free(*(void **)(this + 492));  // 调 堆释放
    pArg22 = pArg2;
    *(uint32_t *)(this + 492) = 0;
    *(uint32_t *)(this + 496) = 0;
    *(uint32_t *)(this + 500) = 0;
    v5 = *(uint32_t *)(pArg2 + 120);  // pArg2+120〔pAnimObj〕
    if ( v5 != 0 )
      v38 = (*(uint32_t *)(pArg2 + 124) - v5) >> 2;  // pArg2+124〔pAuraAnim(推断)〕
    else
      v38 = 0;
    fld_16C = *(uint32_t *)(this + 364);  // this+364〔pAnimNameStr(推断)〕等 2 字段
    if ( fld_16C != 0 )  // fld_16C=this+364 pAnimNameStr
      fld_170 = (*(uint32_t *)(this + 368) - fld_16C) >> 5;  // this+368〔nBindPos368〕
    else
      fld_170 = 0;  // fld_170=this+368 nBindPos368
    v37 = 14 * fld_170;
    pThis_3 = 10 * (sub_424FF0(this) + 3);  // 结果 = 列数换算
    result = v38;
    v8 = 0;
    v35 = 0;
    if ( v38 > 0 )
    {
      while ( 1 )
      {
        v9 = *(uint32_t *)(pArg22 + 120);  // pArg22+120〔pAnimObj〕
        if ( v9 != 0 && v8 < (*(uint32_t *)(pArg22 + 124) - v9) >> 2 )  // pArg22+124〔pAuraAnim(推断)〕
          v10 = *(int **)(v9 + 4 * v8);
        else
          v10 = nullptr;
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v10 + 40))(v10, 33) != 0  // 虚调用 vt+40
          && (*(int (/*thiscall*/ **)(int *))(*v10 + 428))(v10) != 0  // 虚调用 vt+428
          && (*(int (/*thiscall*/ **)(int *))(*v10 + 432))(v10) != 0  // 虚调用 vt+432
          && *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*v10 + 672))(v10) + 8) != 0 )  // 虚调用 vt+672
        {
          v25 = 0;
          v26 = 0;
          v27 = 0;
          v11 = *v10;
          v43 = 0;
          v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 440))(v10);  // 调虚槽 +440：包围盒左界 = 中心x − 宽/2（AABB 边界族 1B8/1BC/1C0/1C4 之首）
          v13 = *v10;
          v42 = v12 / 16 - 1;
          v14 = (*(int (/*thiscall*/ **)(int *))(v13 + 448))(v10) / 12 - 1;  // 调虚槽 +448：包围盒上界 = 中心y − 高/2（cnrd 头同上族级覆盖）
          v41 = (*(int (/*thiscall*/ **)(int *))(*v10 + 444))(v10) / 16 + 1;  // 结果 = 虚调用 vt+444
          v15 = (uint64_t)(715827883LL * (*(int (/*thiscall*/ **)(int *))(*v10 + 452))(v10)) >> 32;  // 结果 = 虚调用 vt+452
          v16 = *v10;
          v17 = (v15 >> 1) + ((unsigned int)v15 >> 31);
          v28 = v42;
          v29 = v14;
          v30 = v41;
          v31 = v17;
          v18 = (*(int (/*thiscall*/ **)(int *))(v16 + 672))(v10);  // 调虚槽 +672：自身 HP
          v19 = *v10;
          v32 = *(uint32_t *)(v18 + 8);
          v24[0] = (*(int (/*thiscall*/ **)(int *))(v19 + 48))(v10);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
          v24[1] = (*(int (/*thiscall*/ **)(int *))(*v10 + 52))(v10);  // 结果 = 虚调用 vt+52
          v20 = v14;
          v36 = v14;
          if ( v14 <= v17 )
          {
            v21 = v37;
            v40 = v37 * v14;
            do
            {
              if ( v20 >= 0 && v20 < pThis_3 )  // 若 v20 >= 0 与/或 v20 < pThis_3
              {
                for ( i = v42; i <= v41; ++i )
                {
                  if ( i >= 0 && i < v21 )  // 若 i >= 0 与/或 i < v21
                  {
                    v23 = (*(int (/*thiscall*/ **)(int *))(*v10 + 672))(v10);  // 结果 = 虚调用 vt+672
                    *(uint8_t *)(i + v40 + *(uint32_t *)(pThis + 480)) = *(uint8_t *)(v23 + 8);
                    v20 = v36;
                    v21 = v37;
                  }
                }
              }
              v36 = ++v20;
              v40 += v21;
            }
            while ( v20 <= v17 );
          }
          v33[0] = (*(int (/*thiscall*/ **)(int *))(*v10 + 48))(v10);  // 结果 = 虚调用 vt+48
          v33[1] = (*(int (/*thiscall*/ **)(int *))(*v10 + 52))(v10);  // 结果 = 虚调用 vt+52
          sub_474950(v33);  // 调 调用 sub_474950
          sub_48E380(v24);  // 44 字节元素尾插（原位填充或回落插入器）
          v8 = v35;
          v43 = -1;
          v25 = 0;
          v26 = 0;
          v27 = 0;
        }
        result = v38;
        v35 = ++v8;
        if ( (int)v8 >= v38 )
          break;
        pArg22 = pArg2;
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x48E730 sub_48E730 —— 32 字节元素区间删除（前移 + 尾部释清）
//   ·sub_48E240 前移后区间，尾段经 ·sub_42DDD0 逐条释清（内层 16 字节容器），尾指针回落并回填新尾。
// ------------------------------------------------------------
int */*thiscall*/ sub_48E730(int *this, int *pDwArg2, int nArg3, int nArg4)  // 32 字节元素区间删除（前移 + 尾部释清）
{
  int nArg32; // ecx
  int fld_e2; // eax
  int fld_e22; // ebx
  int fld_e23; // edi
  int i; // esi
  int *pThis; // [esp+4h] [ebp-4h]

  nArg32 = nArg3;
  pThis = this;
  if ( nArg3 != nArg4 )
  {
    fld_e2 = sub_48E240(nArg4, *(this + 2), nArg3);  // 结果 = 32 字节元素区间拷贝·正向
    fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
    fld_e23 = fld_e2;
    for ( i = fld_e2; i != fld_e22; i += 32 )  // fld_e22=this+8 nSkillRec8
      sub_42DDD0(i);  // 缓冲释清（+20 组）
    nArg32 = nArg3;
    pThis[2] = fld_e23;
  }
  *pDwArg2 = nArg32;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x48E790 sub_48E790 —— 32 字节元素区间构造（内层深拷贝）
//   逐条抄 3 dword 与 1 字节标志，内层经 ·sub_48E1A0 容器深拷贝。
// ------------------------------------------------------------
int /*cdecl*/ sub_48E790(int pArg1, int nArg2, int nArg3)  // 实现：32 字节元素区间构造（内层深拷贝）
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != nArg2 )  // 当 pArg1 != nArg2 循环
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
    {
      *(uint32_t *)nArg32 = *(uint32_t *)pArg1;
      *(uint32_t *)(nArg32 + 4) = *(uint32_t *)(pArg1 + 4);  // nArg32+4〔宿主对象〕
      *(uint32_t *)(nArg32 + 8) = *(uint32_t *)(pArg1 + 8);  // nArg32+8〔nSkillRec8(推断)〕
      *(uint8_t *)(nArg32 + 12) = *(uint8_t *)(pArg1 + 12);  // nArg32+12〔nSkillRec12(推断)〕
      sub_48E1A0((char **)(nArg32 + 16), pArg1 + 16);  // 16 字节元素容器拷贝构造（预留 + ·sub_48D940）
    }
    nArg32 += 32;
    LOBYTE(v7) = 0;
    pArg1 += 32;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x48E870 sub_48E870 —— 地牢格快照与寻路网格重建
//   释放 +480/+484/+492 后按 14 乘 (10 乘 (列数 + 3)) 逐格 ·sub_48CC70 取值填 +480，整块复制到 +484 快照。
//   ·sub_48E480 叠加动态对象阻挡；·sub_58A9D0 设寻路网格（+16420 数据指针、+16418 宽、+16419 高）。
// ------------------------------------------------------------
int /*thiscall*/ sub_48E870(int this, int nArg2)  // 实现：地牢格快照与寻路网格重建
{
  void *fld_1E0; // eax
  uint32_t *pThis_1E0; // esi
  void *fld_1E4; // eax
  int fld_16C; // ecx
  int fld_170; // eax
  int v8; // edi
  int pThis_3; // eax
  size_t v10; // esi
  int v11; // edi
  int v12; // esi
  int v14; // [esp+Ch] [ebp-14h]
  int pThis_32; // [esp+10h] [ebp-10h]
  int v16; // [esp+14h] [ebp-Ch]
  const void **pThis_1E02; // [esp+18h] [ebp-8h]
  int v18; // [esp+1Ch] [ebp-4h]

  fld_1E0 = *(void **)(this + 480);
  pThis_1E0 = (uint32_t *)(this + 480);
  pThis_1E02 = (const void **)(this + 480);
  if ( fld_1E0 != nullptr )  // 若 fld_1E0 有效（非空）
    j_j__free(fld_1E0);
  fld_1E4 = *(void **)(this + 484);
  *pThis_1E0 = 0;
  if ( fld_1E4 != nullptr )  // 若 fld_1E4 有效（非空）
    j_j__free(fld_1E4);
  *(uint32_t *)(this + 484) = 0;
  if ( *(uint32_t *)(this + 492) != 0 )
    j__free(*(void **)(this + 492));  // 调 堆释放
  *(uint32_t *)(this + 492) = 0;
  *(uint32_t *)(this + 496) = 0;
  *(uint32_t *)(this + 500) = 0;
  fld_16C = *(uint32_t *)(this + 364);  // this+364〔pAnimNameStr(推断)〕等 2 字段
  if ( fld_16C != 0 )  // fld_16C=this+364 pAnimNameStr
    fld_170 = (*(uint32_t *)(this + 368) - fld_16C) >> 5;  // this+368〔nBindPos368〕
  else
    fld_170 = 0;  // fld_170=this+368 nBindPos368
  v8 = 14 * fld_170;
  v18 = 14 * fld_170;
  pThis_3 = 10 * (sub_424FF0(this) + 3);  // 结果 = 列数换算
  v10 = v8 * pThis_3;
  pThis_32 = pThis_3;
  v14 = v8 * pThis_3;
  *pThis_1E02 = operator new(v8 * pThis_3);
  *(uint32_t *)(this + 484) = operator new(v10);
  v11 = 0;
  if ( v18 > 0 )
  {
    do
    {
      v12 = 0;
      if ( pThis_32 > 0 )
      {
        v16 = 0;
        do
        {
          *((uint8_t *)*pThis_1E02 + v11 + v16) = sub_48CC70((uint32_t *)this, v11, v12++);  // 取地牢格值
          v16 += v18;
        }
        while ( v12 < pThis_32 );
      }
      ++v11;
    }
    while ( v11 < v18 );
    v10 = v14;
  }
  qmemcpy(*(void **)(this + 484), *pThis_1E02, v10);  // 调 内存块拷贝(内联展开)
  sub_48E480(this, nArg2);  // 动态对象阻挡登记（掩码铺格 + 记录追加）
  return sub_58A9D0(pThis_1E02, v18, pThis_32);  // 设置寻路网格：+16420=数据指针、+16418=宽 a3、+16419=高 a4
}



// ------------------------------------------------------------
// 0x48E9C0 sub_48E9C0 —— 32 字节元素 n 条填充构造
//   —— 与 ·sub_48D860 同构（差异：元素 32 字节、内层拷件换 ·sub_48E1A0、按条数计数）。
// ------------------------------------------------------------
void /*cdecl*/ sub_48E9C0(int nArg1, int nArg2, int pArg3)  // 实现：32 字节元素 n 条填充构造
{
  int nArg12; // esi
  uint32_t v4[6]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v4[5] = v4;
  v4[4] = nArg1;
  v5 = 0;
  while ( nArg2 != 0 )  // 当 nArg2 != 0 循环
  {
    v4[3] = nArg12;
    LOBYTE(v5) = 1;
    if ( nArg12 != 0 )
    {
      *(uint32_t *)nArg12 = *(uint32_t *)pArg3;
      *(uint32_t *)(nArg12 + 4) = *(uint32_t *)(pArg3 + 4);  // nArg12+4〔宿主对象〕
      *(uint32_t *)(nArg12 + 8) = *(uint32_t *)(pArg3 + 8);  // nArg12+8〔nSkillRec8(推断)〕
      *(uint8_t *)(nArg12 + 12) = *(uint8_t *)(pArg3 + 12);  // nArg12+12〔nSkillRec12(推断)〕
      sub_48E1A0((char **)(nArg12 + 16), pArg3 + 16);  // 16 字节元素容器拷贝构造（预留 + ·sub_48D940）
    }
    nArg12 += 32;
    LOBYTE(v5) = 0;
    --nArg2;
  }
}



// ------------------------------------------------------------
// 0x48EAA0 sub_48EAA0 —— 战场块全释放
//   ·sub_42EB90 释 +360/+376 的 32 字节条目表，+480/+484/+492 缓冲逐个 free，尾部落 ·sub_42E620（+504 表）。
// ------------------------------------------------------------
int /*thiscall*/ sub_48EAA0(int this)  // 实现：战场块全释放
{
  void *fld_1E4; // eax

  sub_42EB90(this + 360);  // 释放 +4 缓冲（32B 条目）
  sub_42EB90(this + 376);  // 释放 +4 缓冲（32B 条目）
  if ( *(uint32_t *)(this + 480) != 0 )
    j_j__free(*(void **)(this + 480));
  fld_1E4 = *(void **)(this + 484);
  *(uint32_t *)(this + 480) = 0;
  if ( fld_1E4 != nullptr )  // 若 fld_1E4 有效（非空）
    j_j__free(fld_1E4);
  *(uint32_t *)(this + 484) = 0;
  if ( *(uint32_t *)(this + 492) != 0 )
    j__free(*(void **)(this + 492));  // 调 堆释放
  *(uint32_t *)(this + 492) = 0;
  *(uint32_t *)(this + 496) = 0;
  *(uint32_t *)(this + 500) = 0;
  return sub_42E620(this + 504);  // 释放 +4 缓冲（44B 条目）
}



// ------------------------------------------------------------
// 0x48EB20 sub_48EB20 —— 32 字节元素填充·转发（回尾指针）
//   —— 转发 ·sub_48E9C0 后返回 nArg1 + 32 乘 nArg2。
// ------------------------------------------------------------
int /*stdcall*/ sub_48EB20(int nArg1, int nArg2, int nArg3)  // 实现：32 字节元素填充·转发（回尾指针）
{
  sub_48E9C0(nArg1, nArg2, nArg3);  // 32 字节元素 n 条填充构造
  return nArg1 + 32 * nArg2;
}



// ------------------------------------------------------------
// 0x48EB50 sub_48EB50 —— 大型发包·变体（sub_48E1A0 组包器）
// ------------------------------------------------------------
void /*thiscall*/ sub_48EB50(int this, int pArg2, unsigned int uArg3, int pArg4)  // 实现：大型发包·变体（sub_48E1A0 组包器）
{
  int v4; // edx
  int v6; // ecx
  int fld_4; // ecx
  int fld_8; // edx
  unsigned int fld_C; // eax
  int fld_82; // edx
  unsigned int v12; // eax
  int fld_87; // edx
  int fld_88; // eax
  char *pMem; // ebx
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v18; // edi
  char *fld_83; // eax
  int fld_86; // edi
  char *v21; // edi
  int v22; // eax
  void *v23; // esi
  int fld_42; // [esp-18h] [ebp-5Ch]
  void *Block2; // [esp-18h] [ebp-5Ch]
  int fld_85; // [esp-Ch] [ebp-50h]
  unsigned int fld_84; // [esp-8h] [ebp-4Ch]
  int v28; // [esp+0h] [ebp-44h] BYREF
  uint32_t v29[3]; // [esp+Ch] [ebp-38h] BYREF
  char v30; // [esp+18h] [ebp-2Ch]
  int v31; // [esp+1Ch] [ebp-28h] BYREF
  void *v32; // [esp+20h] [ebp-24h]
  int v33; // [esp+24h] [ebp-20h]
  void *Block; // [esp+2Ch] [ebp-18h]
  int pThis; // [esp+30h] [ebp-14h]
  int *v36; // [esp+34h] [ebp-10h]
  int v37; // [esp+40h] [ebp-4h]
  int v38; // [esp+50h] [ebp+Ch]
  int v39; // [esp+54h] [ebp+10h]

  v4 = *(uint32_t *)(pArg4 + 4);  // pArg4+4〔宿主对象〕
  v29[0] = *(uint32_t *)pArg4;
  v6 = *(uint32_t *)(pArg4 + 8);  // pArg4+8〔nSkillRec8(推断)〕
  v29[1] = v4;
  LOBYTE(v4) = *(uint8_t *)(pArg4 + 12);  // pArg4+12〔nSkillRec12(推断)〕
  v36 = &v28;
  v29[2] = v6;
  pThis = this;
  v30 = v4;
  sub_48E1A0((int)&v31, pArg4 + 16);  // 16 字节元素容器拷贝构造（预留 + ·sub_48D940）
  fld_4 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  fld_8 = 0;
  v37 = 0;
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 5;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    fld_C = 0;  // fld_C=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
    if ( 0x7FFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_42CB90(this);  // CRT 桩（vector 长度异常）
    if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( fld_C >= uArg3 + fld_82 )  // fld_C=this+12 nSkillRec12
    {
      fld_83 = *(char **)(this + 8);  // this+32〔nHeight(推断)〕
      Block = fld_83;  // fld_83=this+32 nHeight
      if ( (int)&fld_83[-pArg2] >> 5 >= uArg3 )  // fld_83=this+32 nHeight
      {
        v21 = &fld_83[-32 * uArg3];  // fld_83=this+32 nHeight
        v22 = sub_48E790(v21, fld_83, fld_83);  // 结果 = 32 字节元素区间构造（内层深拷贝）
        Block2 = Block;
        *(uint32_t *)(this + 8) = v22;  // this+8〔nSkillRec8(推断)〕等 2 字段
        sub_48E460(pArg2, v21, Block2);  // 32 字节元素拷贝·转发
        sub_48E410(pArg2, pArg2 + 32 * uArg3, v29);  // 32 字节元素区间填充（同源覆写）
      }
      else
      {
        sub_48E790(pArg2, fld_83, pArg2 + 32 * uArg3);  // 32 字节元素区间构造（内层深拷贝）
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 5);  // this+8〔nSkillRec8(推断)〕等 2 字段
        fld_85 = *(uint32_t *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
        LOBYTE(v37) = 3;
        sub_48EB20(fld_85, fld_84, v29);  // 32 字节元素填充·转发（回尾指针）
        fld_86 = 32 * uArg3 + *(uint32_t *)(this + 8);  // this+8〔nSkillRec8〕
        *(uint32_t *)(this + 8) = fld_86;  // this+8〔nSkillRec8(推断)〕等 2 字段
        v37 = 0;
        sub_48E410(pArg2, fld_86 - 32 * uArg3, v29);  // 32 字节元素区间填充（同源覆写）
      }
    }
    else
    {
      if ( 0x7FFFFFF - (fld_C >> 1) >= fld_C )  // fld_C=this+12 nSkillRec12
        v12 = (fld_C >> 1) + fld_C;  // fld_C=this+12 nSkillRec12
      else
        v12 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      if ( v12 < uArg3 + fld_87 )  // fld_87=this+8 nSkillRec8
      {
        if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else
          fld_88 = 0;  // fld_88=this+8 nSkillRec8
        v12 = uArg3 + fld_88;
      }
      v39 = 32 * v12;
      pMem = (char *)operator new(32 * v12);  // 分配 32 × v12 字节数组
      fld_42 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
      Block = pMem;
      LOBYTE(v37) = 1;
      v38 = sub_48E790(fld_42, pArg2, pMem);  // 结果 = 32 字节元素区间构造（内层深拷贝）
      sub_48E9C0(v38, uArg3, v29);  // 32 字节元素 n 条填充构造
      sub_48E790(pArg2, *(uint32_t *)(this + 8), 32 * uArg3 + v38);  // 32 字节元素区间构造（内层深拷贝）
      fld_43 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
      if ( fld_43 != 0 )  // fld_43=this+4 宿主对象
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_89 = 0;  // fld_89=this+8 nSkillRec8
      v18 = fld_89 + uArg3;
      if ( fld_43 != 0 )  // fld_43=this+4 宿主对象
      {
        sub_42E7C0(fld_43, *(uint32_t *)(this + 8));  // 32 字节条目组析构
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      }
      *(uint32_t *)(this + 12) = &pMem[v39];  // this+12〔nSkillRec12(推断)〕等 2 字段
      *(uint32_t *)(this + 8) = &pMem[32 * v18];  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
    }
  }
  v23 = v32;
  if ( v32 != nullptr )  // 若 v32 有效（非空）
  {
    sub_42CC00(v32, v33);  // 16 字节槽组释放
    j__free(v23);  // 调 堆释放
  }
}


// ------------------------------------------------------------
// 0x48EE10 sub_48EE10 —— 32 字节元素容器重设长度（增删 + 内层释清）
//   长度已够则区间删除（·sub_48E730）；不足经 ·sub_48EB50 扩容插入；移交的临时记录 Block 内层经 ·sub_42CC00 释清再 free。
// ------------------------------------------------------------
void /*thiscall*/ sub_48EE10(  // 32 字节元素容器重设长度（增删 + 内层释清）
        int *this,
        unsigned int a2,
        char a3,
        int a4,
        int a5,
        int a6,
        char a7,
        void *Block,
        int a9,
        int a10)
{
  int v10; // esi
  unsigned int v11; // edx
  int v12; // edx
  void *v13; // esi

  v10 = *(this + 1);  // this+4〔宿主对象〕
  if ( v10 != 0 )  // v10=this+4 宿主对象
    v11 = (*(this + 2) - v10) >> 5;  // this+8〔nSkillRec8(推断)〕
  else
    v11 = 0;  // v11=this+8 nSkillRec8
  if ( v11 >= a2 )  // v11=this+8 nSkillRec8
  {
    if ( v10 != 0 && a2 < (*(this + 2) - v10) >> 5 )  // this+8〔nSkillRec8(推断)〕
      sub_48E730(this, (int *)&a2, v10 + 32 * a2, *(this + 2));  // 32 字节元素区间删除（前移 + 尾部释清）
  }
  else
  {
    if ( v10 != 0 )  // v10=this+4 宿主对象
      v12 = (*(this + 2) - v10) >> 5;  // this+8〔nSkillRec8(推断)〕
    else
      v12 = 0;  // v12=this+8 nSkillRec8
    sub_48EB50(this, *(this + 2), a2 - v12, (int)&a3);  // 大型发包·变体（sub_48E1A0 组包器）
  }
  v13 = Block;
  if ( Block != nullptr )  // 若 Block 有效（非空）
  {
    sub_42CC00(Block, a9);  // 16 字节槽组释放
    j__free(v13);  // 调 堆释放
  }
}



// ============================================================
// §O 0x48EED0-0x48F500  资源装载包装（IMAGE/ANI）
// ============================================================
// ------------------------------------------------------------
// 0x48EED0 sub_48EED0 —— 图像/动画装载包装（+53/+57/+50 槽位；sub_48E2E0 "%s%s" 拼路径；IMAGE/ANI 一体化）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_48EED0(uint32_t *this, const char *ArgList, char pszArg3)  // 实现：图像/动画装载包装（+53/+57/+50 槽位；sub_48E2E0 %s%s 拼路径；IMAGE/ANI 一体化）
{
  uint32_t *v4; // eax
  uint32_t *v5; // ebx
  unsigned int result; // eax
  uint32_t *pThis_2; // ecx
  uint32_t *v8; // eax
  int i; // edx
  const char *v10; // edi
  int v11; // edi
  float *pObj; // eax
  int v13; // eax
  int v14; // ecx
  int v15; // edi
  unsigned int v16; // edx
  uint32_t *v17; // eax
  uint32_t *pThis_3D; // ecx
  int j; // edx
  uint32_t *v20; // eax
  bool v21; // zf
  int v22; // ecx
  unsigned int **v23; // ecx
  int fld_e91; // edi
  const char *v25; // eax
  int v26; // edx
  unsigned int **v27; // ecx
  int fld_e95; // edi
  const char *v29; // eax
  uint32_t *pThis_4; // ecx
  int pThis_23; // edx
  int pThis_22; // edx
  int v33; // [esp-14h] [ebp-38h]
  int v34; // [esp-14h] [ebp-38h]
  char v35; // [esp-10h] [ebp-34h]
  char v36; // [esp-10h] [ebp-34h]
  int v37; // [esp+Ch] [ebp-18h] BYREF
  int v38; // [esp+10h] [ebp-14h]
  int v39; // [esp+14h] [ebp-10h]
  int v40; // [esp+20h] [ebp-4h]
  const char *ArgLista; // [esp+2Ch] [ebp+8h]
  int ArgListb; // [esp+2Ch] [ebp+8h]
  char *ArgListc; // [esp+2Ch] [ebp+8h]
  unsigned int ArgListd; // [esp+2Ch] [ebp+8h]
  const char *ArgListe; // [esp+2Ch] [ebp+8h]
  unsigned int ArgListf; // [esp+2Ch] [ebp+8h]
  const char *ArgListg; // [esp+2Ch] [ebp+8h]
  int v48; // [esp+30h] [ebp+Ch]
  int v49; // [esp+30h] [ebp+Ch]

  v4 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84DC + 4))(dword_8F84DC, ArgList);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  v5 = v4;
  if ( v4 == nullptr )  // 若 v4 为空
    return off_77F3FC("MAP CREATE FAIL! FILENAME[%s]", ArgList);  // 字符串 “MAP CREATE FAIL! FILENAME[%s]”
  *this = *v4;
  *(this + 1) = v4[30];  // this+4〔宿主对象〕
  pThis_2 = this + 2;  // this+8〔nSkillRec8〕
  v8 = v4 + 39;
  for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
    *pThis_2++ = *v8++;
  v10 = (const char *)v5[43];
  ArgLista = v10;
  if ( v10 != (const char *)v5[44] )
  {
    while ( 1 )
    {
      v39 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
      v40 = 0;
      if ( v39 != 0 )
      {
        if ( *((uint32_t *)v10 + 6) < 0x10u )
          LOBYTE(v10) = (uint8_t)v10 + 4;
        else
          v10 = *((const char **)v10 + 1);
        if ( v5[76] < 0x10u )
          v11 = sub_431920((uint8_t)v5 + 28, (char)v10, 1);  // 结果 = 动画件构造（文件名版）
        else
          v11 = sub_431920(v5[71], (char)v10, 1);  // 结果 = 动画件构造（文件名版）
      }
      else
      {
        v11 = 0;
      }
      v40 = -1;
      v37 = v11;
      sub_699070(2);  // 【clock_bind_domain(clk, newDomainId)】
      pObj = (float *)sub_4924C0(0);  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
      v38 = (uint64_t)((double)*(unsigned int *)(*(uint32_t *)pObj + 36) * pObj[5]);
      if ( v38 > 0 )
      {
        v13 = 16 * ((ArgLista[32] != 0) + 2 * *((uint32_t *)ArgLista + 7));
        v14 = *(uint32_t *)((char *)this + v13 + 24);
        v15 = (int)this + v13 + 20;
        if ( v14 != 0 )
          v16 = (*(uint32_t *)((char *)this + v13 + 28) - v14) >> 3;
        else
          v16 = 0;
        if ( v14 != 0 && v16 < (*(uint32_t *)((char *)this + v13 + 32) - v14) >> 3 )
        {
          v39 = *(uint32_t *)((char *)this + v13 + 28);
          sub_63A7C0(v39, 1, &v37);  // 强化结果公共件
          *(uint32_t *)(v15 + 8) = v39 + 8;
        }
        else
        {
          sub_48CF90((int)this + v13 + 20, *(uint32_t **)((char *)this + v13 + 28), 1u, (int)&v37);  // 8 字节元素区间插入 n 条（三分支 + 溢出守卫）
        }
      }
      ArgLista += 36;  // ArgLista 前进 36
      if ( ArgLista == (const char *)v5[44] )
        break;
      v10 = ArgLista;
    }
  }
  sub_48D290((int)(this + 53), (int)(v5 + 46));  // 24 字节元素容器赋值（截断/扩容/原位三路）
  sub_48D410((int)(this + 57), (int)(v5 + 50));  // 16 字节元素容器赋值（54E 系拷贝）
  v17 = v5 + 54;
  pThis_3D = this + 61;  // this+61〔bReadyFlagA〕
  for ( ArgListb = 4; ArgListb != 0; --ArgListb )  // 循环：ArgListb 从 4 递减到 0
  {
    for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
      *pThis_3D++ = *v17++;  // pThis_3D=this+61 bReadyFlagA
  }
  *(this + 69) = v5[62];  // this+276〔pMapEntry〕
  *(this + 70) = v5[63];  // this+280〔pMapEntryVecEnd〕
  *(this + 71) = v5[64];  // this+284〔bBindGate284(推断)〕
  *(this + 72) = v5[65];  // this+288〔pMaster288(推断)〕
  sub_41DC80((int)(this + 73), (int)(v5 + 66));  // vector<T 4B 驻留句柄> 拷贝赋值 operator=
  ArgListc = (char *)(this + 77);  // this+77〔bGuildFlagB〕
  v20 = v5 + 86;
  v39 = 3;
  do
  {
    *(uint32_t *)ArgListc = *v20;  // ArgListc=this+77 bGuildFlagB
    *((uint32_t *)ArgListc + 1) = v20[1];  // ArgListc[1] = 取 v20[1]
    *((uint32_t *)ArgListc + 2) = v20[2];  // ArgListc[2] = 取 v20[2]
    *((uint32_t *)ArgListc + 3) = v20[3];  // ArgListc[3] = 取 v20[3]
    v20 += 4;
    v21 = v39 == 1;
    ArgListc += 16;  // ArgListc 前进 16
    --v39;
  }
  while ( !v21 );
  *(this + 89) = v5[98];  // this+89 寿命上限门
  *((uint8_t *)this + 396) = pszArg3;  // this+396〔uReflectCtx(推断)〕
  v22 = v5[32];
  if ( v22 != 0 )
    ArgListd = (v5[33] - v22) >> 2;
  else
    ArgListd = 0;
  LOBYTE(v33) = 0;
  sub_48EE10(this + 90, ArgListd, -1, 0, 0, v33, v35, nullptr, 0, 0);  // 32 字节元素容器重设长度（增删 + 内层释清）
  v23 = (unsigned int **)v5[32];
  v48 = (int)v23;
  if ( v23 != (unsigned int **)v5[33] )
  {
    ArgListe = nullptr;
    while ( 1 )
    {
      v39 = v5[76] < 0x10u ? (int)(v5 + 71) : v5[71];
      fld_e91 = (int)&ArgListe[*(this + 91)];  // this+364〔pAnimNameStr(推断)〕
      v25 = sub_41ACF0(v23);  // 结果 = 驻留串句柄 → 字符串指针
      sub_48E2E0(fld_e91, v39, v25);  // 地砖记录装载（路径拼接 + 资源 id/图像句柄）
      v21 = v48 + 4 == v5[33];
      v48 += 4;
      ArgListe += 32;  // ArgListe 前进 32
      if ( v21 )
        break;
      v23 = (unsigned int **)v48;
    }
  }
  v26 = v5[36];
  if ( v26 != 0 )
    ArgListf = (v5[37] - v26) >> 2;
  else
    ArgListf = 0;
  LOBYTE(v34) = 0;
  sub_48EE10(this + 94, ArgListf, -1, 0, 0, v34, v36, nullptr, 0, 0);  // 32 字节元素容器重设长度（增删 + 内层释清）
  v27 = (unsigned int **)v5[36];
  v49 = (int)v27;
  if ( v27 != (unsigned int **)v5[37] )
  {
    ArgListg = nullptr;
    while ( 1 )
    {
      v39 = v5[76] < 0x10u ? (int)(v5 + 71) : v5[71];
      fld_e95 = (int)&ArgListg[*(this + 95)];  // this+380〔attackinfo 指针〕
      v29 = sub_41ACF0(v27);  // 结果 = 驻留串句柄 → 字符串指针
      sub_48E2E0(fld_e95, v39, v29);  // 地砖记录装载（路径拼接 + 资源 id/图像句柄）
      v21 = v49 + 4 == v5[37];
      v49 += 4;
      ArgListg += 32;  // ArgListg 前进 32
      if ( v21 )
        break;
      v27 = (unsigned int **)v49;
    }
  }
  result = 0;
  *(this + 116) = 0;  // this+116 观察者 vector 尾针
  *(this + 117) = 0;
  do
  {
    if ( result < 2 )
    {
      pThis_4 = this + 4 * result;  // this+4 宿主对象
      pThis_4[102] = 120;
      pThis_4[103] = 106;
      if ( result != 0 )  // 若结果非 0（成功）
        *(this + 4 * result + 100) = *(this + 2 * result + 61) - 120;  // this+4 宿主对象
      else
        *(this + 100) = *(this + 61);  // this+244〔fSyncTime〕
      pThis_22 = *(this + 2 * result + 62) - 53;
    }
    else
    {
      pThis_4 = this + 4 * result;  // this+4 宿主对象
      *(this + 4 * result + 100) = *(this + 2 * result + 61) - 70;  // this+4 宿主对象
      pThis_23 = *(this + 2 * result + 62);
      pThis_4[102] = 140;
      pThis_4[103] = 40;
      pThis_22 = pThis_23 - 20;
    }
    ++result;
    pThis_4[101] = pThis_22;
  }
  while ( (int)result < 4 );
  *(this + 119) = v5;
  return result;
}


// ------------------------------------------------------------
// 0x48F470 sub_48F470 —— 按地图 id 查名并装载（·sub_48EED0）
//   ·sub_442D00 按 id 查表得记录（对哨兵 dword_9B740C 判空）后取名字（SSO：小于 16 取 +20 否则解引用）交 ·sub_48EED0 装载。
// ------------------------------------------------------------
const char */*thiscall*/ sub_48F470(uint32_t *this, int nArg2, char pszArg3)  // 按地图 id 查名并装载（·sub_48EED0）
{
  const char *result; // eax
  int v5; // [esp+4h] [ebp-4h] BYREF

  sub_442D00(&v5, &nArg2);  // 红黑树等键查找（_Find）
  result = (const char *)v5;
  if ( v5 != dword_9B740C )
  {
    if ( *(uint32_t *)(v5 + 40) < 0x10u )
      result = (const char *)(v5 + 20);
    else
      result = *(const char **)(v5 + 20);
    if ( result != nullptr )  // 若 result 有效（非空）
      return (const char *)sub_48EED0(this, result, pszArg3);  // 图像/动画装载包装（+53/+57/+50 槽位；sub_48E2E0 ”%s%s” 拼路径
  }
  return result;
}



// ------------------------------------------------------------
// 0x48F4C0 sub_48F4C0 —— 槽表计数（+8..+36 中不等于 254 的字段数）
//   —— 与 ·sub_48FBB0/·sub_48FBF0 同族（差异：字节区 +8..+36、判据 不等于 254）；消费点见 anim 解析 ·sub_49EF60。
// ------------------------------------------------------------
int /*thiscall*/ sub_48F4C0(uint32_t *this)  // 实现：槽表计数（+8..+36 中不等于 254 的字段数）
{
  int result; // eax

  result = *(this + 2) != 254;  // this+8〔nSkillRec8(推断)〕
  if ( *(this + 3) != 254 )  // this+12〔nSkillRec12(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 4) != 254 )  // this+16〔nChannelTypeSel(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 5) != 254 )  // this+20〔nPage(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 6) != 254 )  // this+24〔nPageMax(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 7) != 254 )  // this+28〔pPanelVec(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 8) != 254 )  // this+32〔nHeight(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 9) != 254 )  // this+36〔nStateWord36(推断)〕
    ++result;  // result=this+8 nSkillRec8
  return result;  // result=this+8 nSkillRec8
}



// ============================================================
// §P 0x48F500-0x48FE80  宿主/Ladder 联动 + 收尾（@@SET HOST / LADDER_DOWN）
// ============================================================
// ------------------------------------------------------------
// 0x48F500 sub_48F500 —— 座位状态上报发包（op 55）
//   槽 pArg1 状态（+8 + 4 乘 pArg1）与 nArg2 不同且该槽或自身槽（+108 索引）房间号匹配 word_77F804 时发包 55（槽/状态）。
// ------------------------------------------------------------
int /*cdecl*/ sub_48F500(int pArg1, int nArg2)  // 实现：座位状态上报发包（op 55）
{
  int v2; // ecx
  int result; // eax
  int v4; // [esp+0h] [ebp-4h] BYREF

  v4 = v2;
  result = dword_99FEC0;  // PVP 对局进行中标志
  if ( dword_99FEC0 != 0  // PVP 对局进行中标志
    && *(uint32_t *)(dword_99FEC0 + 4 * pArg1 + 8) != nArg2  // PVP 对局进行中标志
    && (*(uint32_t *)(dword_99FEC0 + 4 * pArg1 + 40) == (uint16_t)word_77F804  // 虚调用 vt+40
     || *(uint32_t *)(dword_99FEC0 + 4 * *(uint32_t *)(dword_99FEC0 + 108) + 40) == (uint16_t)word_77F804) )  // 本机身份键(ServerId)
  {
    sub_423200(dword_8F7B08, 55);  // 【发送网络包API】
    LOBYTE(v4) = pArg1;
    sub_423290(&v4, 1);  // 调 写 4B 长度
    LOBYTE(v4) = nArg2;
    sub_423290(&v4, 1);  // 调 写 4B 长度
    return sub_423380(dword_8F7B08);  // 发包提交：Commit()
  }
  return result;
}



// ------------------------------------------------------------
// 0x48F580 sub_48F580 —— 座位/就绪表置位并刷新房间列表
//   写座位/就绪字节表 dword_99FEB8 加 槽号 = 值，随后 ·sub_52AF20(dword_8F8528[8]) 刷新房间列表。
// ------------------------------------------------------------
int /*cdecl*/ sub_48F580(int nArg1, char pszArg2)  // 实现：座位/就绪表置位并刷新房间列表
{
  uint32_t *dword_8F85282; // edx

  dword_8F85282 = dword_8F8528;  // 全局 dword_8F8528 = 消息/弹窗管理器
  *((uint8_t *)&dword_99FEB8 + nArg1) = pszArg2;
  return sub_52AF20(dword_8F85282[8]);  // 主管理器(消息/弹窗)
}



// ------------------------------------------------------------
// 0x48F5A0 sub_48F5A0 —— 自身座位下标查找（房间号比对）
//   在 dword_99FEC0 + 40 起 8 槽找等于 word_77F804（自身房间号）者，回槽号；无命中回 -1。
// ------------------------------------------------------------
int sub_48F5A0()  // 自身座位下标查找（房间号比对）
{
  int result; // eax
  uint32_t *i; // ecx

  if ( dword_99FEC0 == 0 )  // PVP 对局进行中标志
    return -1;
  result = 0;
  for ( i = (uint32_t *)(dword_99FEC0 + 40); *i != (uint16_t)word_77F804; ++i )  // 本机身份键(ServerId)
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48F5E0 sub_48F5E0 —— 座位下标按 id 查找
//   —— 与 ·sub_48F5A0 同构（差异：匹配值改为入参 nArg1）。
// ------------------------------------------------------------
int /*cdecl*/ sub_48F5E0(int nArg1)  // 实现：座位下标按 id 查找
{
  int result; // eax
  uint32_t *i; // ecx

  if ( dword_99FEC0 == 0 )  // PVP 对局进行中标志
    return -1;
  result = 0;
  for ( i = (uint32_t *)(dword_99FEC0 + 40); *i != nArg1; ++i )  // PVP 对局进行中标志
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48F620 sub_48F620 —— 对局中标志查询
//   跳过 254/255 取首个槽值，非 0 且非 4 时回 true【推断：对局有效标志】；·sub_54DA50 结算背景等消费。
// ------------------------------------------------------------
bool /*thiscall*/ sub_48F620(uint32_t *this)  // 实现：对局中标志查询
{
  int v1; // eax
  uint32_t *i; // esi
  int v4; // eax

  v1 = 0;
  for ( i = this + 2; *i == 255 || *i == 254; ++i )
  {
    if ( ++v1 >= 8 )
      return false;
  }
  v4 = *(this + v1 + 2);
  return v4 != 0 && v4 != 4;
}



// ------------------------------------------------------------
// 0x48F660 sub_48F660 —— 槽 id 解析（·sub_429830 查对象）
//   取 this + pArg2 + 9 处 id（0xFFFF 为空）回 0，否则 ·sub_429830 解析对象。
// ------------------------------------------------------------
int /*thiscall*/ sub_48F660(uint32_t *this, int pArg2)  // 实现：槽 id 解析（·sub_429830 查对象）
{
  int v2; // eax

  v2 = *(this + pArg2 + 9);
  if ( v2 == 0xFFFF )
    return 0;
  else
    return sub_429830(v2);  // 表按键查找（uint16）
}



// ------------------------------------------------------------
// 0x48F690 sub_48F690 —— 槽 id 解析·第二组（偏移 +10）
//   —— 与 ·sub_48F660 同构（差异：字段偏移 +10）。
// ------------------------------------------------------------
int /*thiscall*/ sub_48F690(uint32_t *this, int pArg2)  // 实现：槽 id 解析·第二组（偏移 +10）
{
  int v2; // eax

  v2 = *(this + pArg2 + 10);
  if ( v2 == 0xFFFF )
    return 0;
  else
    return sub_429830(v2);  // 表按键查找（uint16）
}



// ------------------------------------------------------------
// 0x48F6C0 sub_48F6C0 —— 未装载槽计数
//   8 槽遍历：状态字段（+8 起）不等于 254 且槽 id（+40 起）为空或 ·sub_429830 解析 0 时计数【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_48F6C0(uint32_t *this)  // 实现：未装载槽计数
{
  int v1; // ebx
  uint32_t *pThis_A; // esi
  int i; // edi

  v1 = 0;
  pThis_A = this + 10;  // this+40〔条件位掩码测试〕
  for ( i = 8; i != 0; --i )  // 循环：i 从 8 递减到 0
  {
    if ( *(pThis_A - 8) != 254 && (*pThis_A == 0xFFFF || sub_429830(*pThis_A) == 0) )  // 表按键查找（uint16）
      ++v1;
    ++pThis_A;
  }
  return v1;
}



// ------------------------------------------------------------
// 0x48F700 sub_48F700 —— LADDER_DOWN 处理（梯子/下落状态、sub_452630/4529B0）
// ------------------------------------------------------------
int /*thiscall*/ sub_48F700(uint32_t *this, int ArgList, int nArg3, int nArg4)  // 实现：LADDER_DOWN 处理（梯子/下落状态、sub_452630/4529B0）
{
  int result; // eax
  int nArg42; // ebx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // ebx
  int v12; // ebx
  int v13; // ebx
  int v14; // esi
  int v15; // eax
  int pObj; // ecx
  int ArgLista; // [esp+14h] [ebp+8h]
  char v18; // [esp+1Ch] [ebp+10h]

  result = nArg3;
  nArg42 = nArg4;
  v8 = *(this + ArgList + 10);
  if ( v8 != nArg3 || *(this + ArgList + 2) != nArg4 )
  {
    v9 = *(this + ArgList + 2);
    *(this + ArgList + 10) = nArg3;
    ArgLista = v9;
    *(this + ArgList + 2) = nArg4;
    if ( (uint32_t *)dword_99FEC0 == this )  // PVP 对局进行中标志
    {
      if ( v8 != nArg3 )
      {
        if ( nArg3 == 0xFFFF )
        {
          v10 = sub_429830(v8);  // 结果 = 表按键查找（uint16）
          v11 = v10;
          if ( v10 != 0 && *(uint32_t *)(v10 + 196) != 0 )
            sub_4B05C0(0);  // 置隐藏/屏蔽位 +8052
          sub_452630(*(uint32_t *)(dword_8F7A24 + 32), ArgList, v11);  // 成员移除广播
        }
        else
        {
          v12 = sub_429830(nArg3);  // 结果 = 表按键查找（uint16）
          sub_4529B0(ArgList, v12, 1);  // 对象入场装配
          v13 = *(uint32_t *)(v12 + 196);
          if ( v13 != 0 )
            sub_4B05B0(v13);  // 置状态标志 +8004
          sub_432EA0("LADDER_DOWN", -1, 0, 0);  // 字符串 “LADDER_DOWN”
        }
        nArg42 = nArg4;
      }
      if ( ArgLista != nArg42 )
      {
        sub_52AF20(*((uint32_t *)dword_8F8528 + 8));  // 主管理器(消息/弹窗)
        sub_52A950(*((uint32_t *)dword_8F8528 + 8));  // 主管理器(消息/弹窗)
      }
      v14 = *(this + ArgList + 10);
      if ( v14 != 0xFFFF )
      {
        v15 = sub_429830(v14);  // 结果 = 表按键查找（uint16）
        if ( v15 != 0 )
        {
          pObj = *(uint32_t *)(v15 + 196);
          if ( pObj != 0 )
          {
            v18 = 0;
            switch ( nArg42 )  // 按 nArg42 分派
            {
              case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, ArgList + 3);  // 调虚槽 +372：目标点写入
                break;
              case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 372))(pObj, 0);  // 调虚槽 +372：目标点写入
                break;
              case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, 1);  // 调虚槽 +372：目标点写入
                break;
              case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
              case 4:  // case 4 = ENUM_CMDPACKET_EXIT
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, 2);  // 调虚槽 +372：目标点写入
                v18 = 1;
                break;
              default:
                break;
            }
            sub_4B12B0(v18);  // 事件分发（音效 sub_422E70/43BEE0、sub_4BF300）
          }
        }
      }
      return sub_52ADA0(*((uint32_t *)dword_8F8528 + 8));  // 主管理器(消息/弹窗)
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x48F890 sub_48F890 —— 宿主切换 @@SET HOST %d 输出（sub_48F5A0 槽位、sub_4529B0 转移）
// ------------------------------------------------------------
int /*cdecl*/ sub_48F890(int pArg1)  // 实现：宿主切换 @@SET HOST %d 输出（sub_48F5A0 槽位、sub_4529B0 转移）
{
  int result; // eax
  int v2; // esi
  uint32_t *dword_8F85282; // eax
  int v4; // eax
  int dword_8F85202; // esi
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  uint32_t *v9; // edi
  int v10; // eax
  int v11; // esi
  int pObj; // ecx
  char v13; // [esp+Ch] [ebp+8h]

  result = dword_99FEC0;  // PVP 对局进行中标志
  if ( dword_99FEC0 != pArg1 )  // PVP 对局进行中标志
  {
    dword_99FEC0 = pArg1;  // PVP 对局进行中标志
    if ( pArg1 != 0 )
    {
      v2 = *(uint32_t *)(pArg1 + 108);  // pArg1+108〔nAdd108(推断)〕
      if ( v2 != -1 )
      {
        dword_8F85282 = dword_8F8528;  // 全局 dword_8F8528 = 消息/弹窗管理器
        *((uint8_t *)&dword_99FEB8 + v2) = 0;
        sub_52AF20(dword_8F85282[8]);  // 主管理器(消息/弹窗)
        *(uint32_t *)(sub_656710() + 40) = v2;  // 取全局单例地址（返回 unk_9BD5D0）
        off_77F3FC("@@SET HOST %d", v2);  // 字符串 “@@SET HOST %d”
      }
      sub_41D300((int *)dword_8F7A24, 4);  // 模块切换 setter → 0x41CC80(onChangeModule) 转发
      v4 = sub_48F5A0();  // 结果 = 自身座位下标查找（房间号比对）
      off_77F3FC("@@UDP START - CNPvpRoom::setMyRoom() seatIndex %d /// 1", v4);
      dword_8F85202 = dword_8F8520;  // 会话/UDP 管理器
      v6 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      v7 = sub_48F5A0();  // 结果 = 自身座位下标查找（房间号比对）
      (*(void (/*thiscall*/ **)(int, int))(v6 + 148))(dword_8F85202, v7);  // 会话/UDP 管理器
      v8 = 0;
      v9 = (uint32_t *)(pArg1 + 8);  // pArg1+8〔nSkillRec8(推断)〕
      do
      {
        if ( v9[8] != 0xFFFF )
        {
          v10 = sub_429830(v9[8]);  // 结果 = 表按键查找（uint16）
          v11 = v10;
          if ( v10 != 0 && *(uint32_t *)(v10 + 196) != 0 )
          {
            sub_4529B0(v8, v10, 0);  // 对象入场装配
            sub_4B05B0(*(uint32_t *)(v11 + 196));  // 置状态标志 +8004
            pObj = *(uint32_t *)(v11 + 196);
            if ( pObj != 0 )
            {
              v13 = 0;
              switch ( *v9 )  // 按 *v9 分派
              {
                case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, v8 + 3);  // 调虚槽 +372：目标点写入
                  break;
                case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 372))(pObj, 0);  // 调虚槽 +372：目标点写入
                  break;
                case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, 1);  // 调虚槽 +372：目标点写入
                  break;
                case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
                case 4:  // case 4 = ENUM_CMDPACKET_EXIT
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, 2);  // 调虚槽 +372：目标点写入
                  v13 = 1;
                  break;
                default:
                  break;
              }
              sub_4B12B0(v13);  // 事件分发（音效 sub_422E70/43BEE0、sub_4BF300）
            }
          }
        }
        ++v8;
        ++v9;
      }
      while ( v8 < 8 );
      return sub_52ADA0(*((uint32_t *)dword_8F8528 + 8));  // 主管理器(消息/弹窗)
    }
    else
    {
      dword_99FEB8 = 0;
      dword_99FEBC = 0;
      off_77F3FC("@@UDP STOP - CNPvpRoom::setMyRoom 1");  // 字符串 “@@UDP STOP - CNPvpRoom::setMyRoom 1”
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 152))(dword_8F8520);  // 调虚槽 +152：效果通道 3
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x48FA30 sub_48FA30 —— 宿主切换·对象侧（@@SET HOST、LADDER_DOWN）
// ------------------------------------------------------------
char /*thiscall*/ sub_48FA30(uint32_t *this, int ArgList)  // 实现：宿主切换·对象侧（@@SET HOST、LADDER_DOWN）
{
  int dword_796E502; // eax
  int fld_e27; // edx
  char result; // al
  int v6; // eax
  int fld_e272; // eax
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // eax
  const char *v13; // eax
  uint32_t *dword_8F85282; // eax
  int v15; // [esp-4h] [ebp-210h]
  char Buffer[512]; // [esp+8h] [ebp-204h] BYREF
  int dword_796E5022; // [esp+208h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  fld_e27 = *(this + 27);  // this+108〔nAdd108(推断)〕
  *(this + 27) = ArgList;  // this+108〔nAdd108(推断)〕
  dword_796E5022 = dword_796E502;  // dword_796E502＝dword_796E50
  result = fld_e27 != ArgList;  // fld_e27=this+108 nAdd108
  if ( (uint32_t *)dword_99FEC0 == this )  // PVP 对局进行中标志
  {
    if ( fld_e27 != ArgList )  // fld_e27=this+108 nAdd108
    {
      v6 = 0xFFFF;
      if ( ArgList != -1 )
        v6 = *(this + ArgList + 10);
      if ( *(uint32_t *)(sub_429830(v6) + 196) != 0 )  // 表按键查找（uint16）
      {
        fld_e272 = *(this + 27);  // this+108〔nAdd108(推断)〕
        if ( fld_e272 == -1 )  // fld_e272=this+108 nAdd108
          v8 = 0xFFFF;
        else
          v8 = *(this + fld_e272 + 10);  // fld_e272=this+108 nAdd108
        v9 = *(uint32_t *)(sub_429830(v8) + 196);  // 结果 = 表按键查找（uint16）
        v10 = *(uint32_t *)(v9 + 312);
        v11 = v9 + 288;
        if ( v10 < 0x10 )
          v12 = v11 + 4;
        else
          v12 = *(uint32_t *)(v11 + 4);
        v15 = v12;
        v13 = (const char *)sub_422E70(1607);  // 调 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v13, v15);  // 调 格式化到缓冲
        sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 主管理器(消息/弹窗)
      }
    }
    dword_8F85282 = dword_8F8528;  // 全局 dword_8F8528 = 消息/弹窗管理器
    *((uint8_t *)&dword_99FEB8 + ArgList) = 0;
    sub_52AF20(dword_8F85282[8]);  // 主管理器(消息/弹窗)
    sub_52AF20(*((uint32_t *)dword_8F8528 + 8));  // 主管理器(消息/弹窗)
    sub_52A950(*((uint32_t *)dword_8F8528 + 8));  // 主管理器(消息/弹窗)
    *(uint32_t *)(sub_656710() + 40) = ArgList;  // 取全局单例地址（返回 unk_9BD5D0）
    return off_77F3FC("@@SET HOST %d", ArgList);  // 字符串 “@@SET HOST %d”
  }
  return result;
}



// ------------------------------------------------------------
// 0x48FB60 sub_48FB60 —— 槽按键查找（回填槽号）
//   8 槽内 ·sub_48F660(this+1, 槽) 取槽对象，比对 +4 处 int16 等于 nArg2；命中回槽地址并可回填槽号，未中回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_48FB60(uint32_t *this, int nArg2, int *pDwArg3)  // 实现：槽按键查找（回填槽号）
{
  int v3; // esi
  uint32_t *pThis_1; // edi
  int result; // eax

  v3 = 0;
  pThis_1 = this + 1;  // this+4〔宿主对象〕
  while ( 1 )
  {
    result = sub_48F660(pThis_1, v3);  // 结果 = 槽 id 解析（·sub_429830 查对象）
    if ( result != 0 && *(uint16_t *)(result + 4) == nArg2 )
      break;
    if ( ++v3 >= 8 )
      return 0;
  }
  if ( pDwArg3 != nullptr )  // 若 pDwArg3 有效（非空）
    *pDwArg3 = v3;
  return result;
}



// ------------------------------------------------------------
// 0x48FBB0 sub_48FBB0 —— 槽表计数（+40..+68 中不等于 0xFFFF 的字段数）
//   8 槽遍历 this+10..17，统计非 0xFFFF 者；anim 解析 ·sub_49EEE0 槽表求和同族。
// ------------------------------------------------------------
int /*thiscall*/ sub_48FBB0(uint32_t *this)  // 实现：槽表计数（+40..+68 中不等于 0xFFFF 的字段数）
{
  int result; // eax

  result = *(this + 10) != 0xFFFF;  // this+40〔bStateSub40(推断)〕
  if ( *(this + 11) != 0xFFFF )  // this+44〔nExpireMs(推断)〕
    ++result;  // result=this+40 bStateSub40
  if ( *(this + 12) != 0xFFFF )  // this+48〔pCmdVecBegin48(推断)〕
    ++result;  // result=this+40 bStateSub40
  if ( *(this + 13) != 0xFFFF )  // this+52〔bAuraState(推断)〕
    ++result;  // result=this+40 bStateSub40
  if ( *(this + 14) != 0xFFFF )  // this+56〔pCmdVecCap56(推断)〕
    ++result;  // result=this+40 bStateSub40
  if ( *(this + 15) != 0xFFFF )  // this+60〔nFadeValue60(推断)〕
    ++result;  // result=this+40 bStateSub40
  if ( *(this + 16) != 0xFFFF )  // this+64〔apServerTabBtn(推断)〕
    ++result;  // result=this+40 bStateSub40
  if ( *(this + 17) != 0xFFFF )  // this+68〔nCharCount(推断)〕
    ++result;  // result=this+40 bStateSub40
  return result;  // result=this+40 bStateSub40
}



// ------------------------------------------------------------
// 0x48FBF0 sub_48FBF0 —— 槽表计数（+8..+36 中等于 255 的字段数）
//   —— 与 ·sub_48FBB0 同构（差异：区 this+2..9、判据 等于 255）；战争房间 UI（·sub_63CAC0）复用。
// ------------------------------------------------------------
int /*thiscall*/ sub_48FBF0(uint32_t *this)  // 实现：槽表计数（+8..+36 中等于 255 的字段数）
{
  int result; // eax

  result = *(this + 2) == 255;  // this+8〔nSkillRec8(推断)〕
  if ( *(this + 3) == 255 )  // this+12〔nSkillRec12(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 4) == 255 )  // this+16〔nChannelTypeSel(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 5) == 255 )  // this+20〔nPage(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 6) == 255 )  // this+24〔nPageMax(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 7) == 255 )  // this+28〔pPanelVec(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 8) == 255 )  // this+32〔nHeight(推断)〕
    ++result;  // result=this+8 nSkillRec8
  if ( *(this + 9) == 255 )  // this+36〔nStateWord36(推断)〕
    ++result;  // result=this+8 nSkillRec8
  return result;  // result=this+8 nSkillRec8
}



// ------------------------------------------------------------
// 0x48FC30 sub_48FC30 —— 座位状态上报发包（op 94，表 dword_99FF08）
//   —— 与 ·sub_48F500 同构（差异：表换 dword_99FF08、包号 94、无房间号匹配门）。
// ------------------------------------------------------------
int /*cdecl*/ sub_48FC30(int pArg1, int nArg2)  // 实现：座位状态上报发包（op 94，表 dword_99FF08）
{
  int v2; // ecx
  int result; // eax
  int v4; // [esp+0h] [ebp-4h] BYREF

  v4 = v2;
  result = dword_99FF08;
  if ( dword_99FF08 != 0 && *(uint32_t *)(dword_99FF08 + 4 * pArg1 + 8) != nArg2 )
  {
    sub_423200(dword_8F7B08, 94);  // 【发送网络包API】
    LOBYTE(v4) = pArg1;
    sub_423290(&v4, 1);  // 调 写 4B 长度
    LOBYTE(v4) = nArg2;
    sub_423290(&v4, 1);  // 调 写 4B 长度
    return sub_423380(dword_8F7B08);  // 发包提交：Commit()
  }
  return result;
}



// ------------------------------------------------------------
// 0x48FCA0 sub_48FCA0 —— 自身座位下标查找（表 dword_99FF08）
//   —— 与 ·sub_48F5A0 同构（差异：表换 dword_99FF08）。
// ------------------------------------------------------------
int sub_48FCA0()  // 自身座位下标查找（表 dword_99FF08）
{
  int result; // eax
  uint32_t *i; // ecx

  if ( dword_99FF08 == 0 )
    return -1;
  result = 0;
  for ( i = (uint32_t *)(dword_99FF08 + 40); *i != (uint16_t)word_77F804; ++i )  // 本机身份键(ServerId)
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48FCE0 sub_48FCE0 —— 座位下标按 id 查找（表 dword_99FF08）
//   —— 与 ·sub_48F5E0 同构（差异：表换 dword_99FF08）。
// ------------------------------------------------------------
int /*cdecl*/ sub_48FCE0(int nArg1)  // 实现：座位下标按 id 查找（表 dword_99FF08）
{
  int result; // eax
  uint32_t *i; // ecx

  if ( dword_99FF08 == 0 )
    return -1;
  result = 0;
  for ( i = (uint32_t *)(dword_99FF08 + 40); *i != nArg1; ++i )
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48FD20 sub_48FD20 —— 槽占用查询（跳过 255 取首槽）
//   跳过 255 空槽取首个槽值，非 0 即占用；8 槽全空回 false。
// ------------------------------------------------------------
bool /*thiscall*/ sub_48FD20(uint32_t *this)  // 实现：槽占用查询（跳过 255 取首槽）
{
  int v1; // eax
  uint32_t *i; // edx

  v1 = 0;
  for ( i = this + 2; *i == 255; ++i )
  {
    if ( ++v1 >= 8 )
      return false;
  }
  return *(this + v1 + 2) != 0;
}



// ------------------------------------------------------------
// 0x48FD50 sub_48FD50 —— 状态位查询（+72 不等于 -1）
//   单字段判非空哨兵。
// ------------------------------------------------------------
bool /*thiscall*/ sub_48FD50(uint32_t *this)  // 实现：状态位查询（+72 不等于 -1）
{
  return *(this + 18) != -1;  // this+72〔nSnapshot72(推断)〕
}



// ------------------------------------------------------------
// 0x48FD60 sub_48FD60 —— 槽字段读取（+80 起）
//   按 pArg2 取 +80 + 4 乘 pArg2 字段。
// ------------------------------------------------------------
int /*thiscall*/ sub_48FD60(uint32_t *this, int pArg2)  // 实现：槽字段读取（+80 起）
{
  return *(this + pArg2 + 20);
}



// ------------------------------------------------------------
// 0x48FD70 sub_48FD70 —— 槽字段读取·第二组（基址 +112）
//   —— 与 ·sub_48FD60 同构（差异：基址 +112）。
// ------------------------------------------------------------
int /*thiscall*/ sub_48FD70(uint32_t *this, int pArg2)  // 实现：槽字段读取·第二组（基址 +112）
{
  return *(this + pArg2 + 28);
}



// ------------------------------------------------------------
// 0x48FD80 sub_48FD80 —— 空槽计数（+144..+151 中为 0 的字节数）
//   8 字节槽区（+144..+151）统计为 0 的槽数；COUNT_DOWN 事件（·sub_49BEF0）与退场复位族消费【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_48FD80(uint8_t *this)  // 实现：空槽计数（+144..+151 中为 0 的字节数）
{
  int result; // eax

  result = *(this + 144) == 0;  // this+576〔uOffset576〕
  if ( *(this + 145) == 0 )  // this+580〔uOffset580〕
    ++result;  // result=this+576 uOffset576
  if ( *(this + 146) == 0 )
    ++result;  // result=this+576 uOffset576
  if ( *(this + 147) == 0 )  // 若 this+588〔位置采样时刻〕 == 0
    ++result;  // result=this+576 uOffset576
  if ( *(this + 148) == 0 )  // this+148 第 4 组·+802 增量子倍率
    ++result;  // result=this+576 uOffset576
  if ( *(this + 149) == 0 )
    ++result;  // result=this+576 uOffset576
  if ( *(this + 150) == 0 )  // 若 this+600〔命中列表边界〕 == 0
    ++result;  // result=this+576 uOffset576
  if ( *(this + 151) == 0 )
    ++result;  // result=this+576 uOffset576
  return result;  // result=this+576 uOffset576
}



// ------------------------------------------------------------
// 0x48FDE0 sub_48FDE0 —— 座位区清零并刷新关联名单
//   +80..+148 清零后 ·sub_4632D0(dword_8F8528[4]) 重算关联名单。
// ------------------------------------------------------------
int /*thiscall*/ sub_48FDE0(uint32_t *this)  // 实现：座位区清零并刷新关联名单
{
  uint32_t *pThis_24; // ecx

  *(this + 20) = 0;  // this+80〔nAuraStage(推断)〕
  *(this + 21) = 0;  // this+84〔pFxObjA(推断)〕
  *(this + 22) = 0;  // this+88〔pFxObjB(推断)〕
  *(this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  *(this + 24) = 0;  // this+96〔nStatusMode(推断)〕
  *(this + 25) = 0;  // this+100〔bEnchantDone(推断)〕
  *(this + 26) = 0;  // this+104〔nTimerEnd(推断)〕
  *(this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *(this + 28) = 0;  // this+112〔pHostComp112〕
  *(this + 29) = 0;  // this+116〔会话上下文〕
  *(this + 30) = 0;  // this+120〔pAnimObj〕
  *(this + 31) = 0;  // this+124〔pAuraAnim(推断)〕
  *(this + 32) = 0;  // this+128〔szStatusKeyBuf(推断)〕
  *(this + 33) = 0;  // this+132〔nAgeTicks〕
  *(this + 34) = 0;  // this+136〔nCtx136(推断)〕
  *(this + 35) = 0;  // this+140〔nAdd140(推断)〕
  pThis_24 = this + 36;  // this+36 物品状态字
  *pThis_24 = 0;  // pThis_24=this+36 物品状态字
  pThis_24[1] = 0;  // pThis_24=this+36 物品状态字
  return sub_4632D0(*((uint32_t *)dword_8F8528 + 4));  // 席位表快照与排序
}



// ------------------------------------------------------------
// 0x48FE30 sub_48FE30 —— 组装显示串（串表名 + 表项串 #编号）
//   ·sub_422E70(1900) 取名加 ·sub_42C540(+152 字节索引) 取表项串，sprintf %s %s #%d 到 byte_99FF10 返回。
// ------------------------------------------------------------
char */*thiscall*/ sub_48FE30(int this)  // 组装显示串（串表名 + 表项串 #编号）
{
  const char *v2; // edi
  const char *fld_98; // eax

  v2 = (const char *)sub_422E70(1900);  // 调 存 CStringManager::getStr 取本地化串
  fld_98 = (const char *)sub_42C540(*(char *)(this + 152));  // 结果 = 字符串项取指针（SSO）
  sprintf(byte_99FF10, "%s %s #%d", v2, fld_98, *(uint32_t *)(this + 4));  // 字符串 “%s %s #%d”
  return byte_99FF10;
}



// ------------------------------------------------------------
// 0x48FE80 sub_48FE80 —— 宿主/UDP 联动收尾（@@SET HOST、sub_42F160）
// ------------------------------------------------------------
int /*usercall*/ sub_48FE80@<eax>(int nArg1@<edi>, int pArg2)  // 实现：宿主/UDP 联动收尾（@@SET HOST、sub_42F160）
{
  int result; // eax
  int v3; // esi
  uint32_t *v4; // eax
  int v5; // eax
  uint32_t *v6; // ecx
  int v7; // eax
  uint32_t *v8; // ecx
  int v9; // edi
  uint32_t *v10; // ebx
  int v11; // eax
  int v12; // esi
  int pObj; // ecx
  char v14; // [esp+10h] [ebp+8h]

  result = dword_99FF08;
  if ( dword_99FF08 != pArg2 )
  {
    dword_99FF08 = pArg2;
    if ( pArg2 != 0 )
    {
      v3 = 0;
      v4 = (uint32_t *)(pArg2 + 40);  // pArg2+40〔bStateSub40(推断)〕
      while ( *v4 == 0xFFFF )  // 当 *v4 == 0xFFFF 循环
      {
        ++v3;
        ++v4;
        if ( v3 >= 8 )
        {
          MessageBoxA(*(HWND *)(dword_79C0A0 + 16), &byte_6CAE90, szPassword, 0);
          goto LABEL_8;
        }
      }
      *(uint32_t *)(sub_656710(nArg1) + 40) = v3;  // 取全局单例地址（返回 unk_9BD5D0）
      off_77F3FC("@@SET HOST %d", v3);  // 字符串 “@@SET HOST %d”
LABEL_8:
      off_77F3FC((char *)&byte_6CAE5C, *(uint32_t *)(pArg2 + 72), *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 32));  // 登录/选区管理器
      sub_41D300(6);  // 模块切换 setter → 0x41CC80(onChangeModule) 转发
      sub_42F160(*(uint32_t *)(pArg2 + 72), 0);  // 决斗场状态机
      off_77F3FC((char *)&byte_6CAE28, *(uint32_t *)(pArg2 + 72), *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 32));  // 登录/选区管理器
      if ( dword_99FF08 != 0 )
      {
        v5 = 0;
        v6 = (uint32_t *)(dword_99FF08 + 40);
        while ( *v6 != (uint16_t)word_77F804 )  // 本机身份键(ServerId)
        {
          ++v5;
          ++v6;
          if ( v5 >= 8 )
            goto LABEL_12;
        }
      }
      else
      {
LABEL_12:
        v5 = -1;
      }
      off_77F3FC("@@UDP START - CNWarRoom::setMyRoom() seatIndex %d /// 1", v5);
      if ( dword_99FF08 != 0 )
      {
        v7 = 0;
        v8 = (uint32_t *)(dword_99FF08 + 40);
        while ( *v8 != (uint16_t)word_77F804 )  // 本机身份键(ServerId)
        {
          ++v7;
          ++v8;
          if ( v7 >= 8 )
            goto LABEL_17;
        }
      }
      else
      {
LABEL_17:
        v7 = -1;
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 148))(dword_8F8520, v7);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
      v9 = 0;
      v10 = (uint32_t *)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
      do
      {
        v11 = sub_48F660(v9);  // 结果 = 槽 id 解析（·sub_429830 查对象）
        v12 = v11;
        if ( v11 != 0 && *(uint32_t *)(v11 + 196) != 0 )
        {
          sub_42E120(v9, v11, 0);  // 观战对象换装演出（273 层）
          sub_4B05B0(*(uint32_t *)(v12 + 196));  // 置状态标志 +8004
          pObj = *(uint32_t *)(v12 + 196);
          if ( pObj != 0 )
          {
            v14 = 0;
            switch ( *v10 )  // 按 *v10 分派
            {
              case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, v9 + 3);  // 调虚槽 +372：目标点写入
                break;
              case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 372))(pObj, 0);  // 调虚槽 +372：目标点写入
                break;
              case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, 1);  // 调虚槽 +372：目标点写入
                break;
              case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
              case 4:  // case 4 = ENUM_CMDPACKET_EXIT
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, 2);  // 调虚槽 +372：目标点写入
                v14 = 1;
                break;
              default:
                break;
            }
            sub_4B12B0(v14);  // 事件分发（音效 sub_422E70/43BEE0、sub_4BF300）
          }
        }
        ++v9;
        ++v10;
      }
      while ( v9 < 8 );
      return sub_49CA80(*((uint32_t *)dword_8F8528 + 9));  // 窗口状态查询（+58/+59 → sub_48FCA0/sub_578E80）
    }
    else
    {
      off_77F3FC("@@UDP STOP - CNWarRoom::setMyRoom 1");  // 字符串 “@@UDP STOP - CNWarRoom::setMyRoom 1”
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 152))(dword_8F8520);  // 调虚槽 +152：效果通道 3
      return sub_42EA90(*(uint32_t *)(dword_8F7A24 + 40));  // 退场复位
    }
  }
  return result;
}

