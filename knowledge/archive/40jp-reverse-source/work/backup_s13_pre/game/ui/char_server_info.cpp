// ============================================================
// 【40JP逆向源代码工程】ui/char_server_info.cpp
// 模块: 0x58 区块 —— 角色流程辅助 + A* 寻路引擎 + 食尸鬼族怪物 AI
// 来源: work/dump_uilogin.txt  区块: 0x580000-0x590000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 88
// ------------------------------------------------------------
// ★ 内容勘正（L1 精修确认）：原分区表把本文件记作"角色数据/服务器信息"，
//   但 0x583B90 角色创建/服务器数据主流程（MyServerId/Fatigue/CHARACTER_CREATED/
//   QuestTrigger 等字符串宿主）已作为巨函数拆出到
//   src/combat/bigfunc_583B90_sub_583B90.cpp；本文件实为五大块：
//   ① 0x583A40-0x583B50  角色主流程的配套小辅助（7 个）；
//   ② 0x58A9D0-0x58B380  A* 寻路引擎：1024 节点池 + 有序开链表 +
//      曼哈顿启发式(|dx|+|dy|) + 8 邻域扩展 + 可行走判定（网格值 2=阻挡、1=对角阻挡）；
//   ③ 0x58B380-0x58B570  定时指令时间线调度器（CNTimer + 0xFA0 指令缓冲）；
//   ④ 0x58B5F0-0x58B750  怪物友好度判定族（FriendShip，RTTI 判定目标怪物种类）；
//   ⑤ 0x58B750-0x58FC30 食尸鬼族怪物 AI（Ghoul/Thrower/Morgan/NoMercy/
//      OilSellerOlrek/MagmaGhoul + ThrowNoMercyGrabEnemy 抓投）与
//      IRDActiveObject 共享覆写（vmt148 2D 绘制 / vmt1D8 主状态机 874 行 /
//      vmt14C 行走动画 505 行：G_WALK_FLOOR_LOOP 等按地面材质分标签）。
// ------------------------------------------------------------
// 交叉引用：src/combat/bigfunc_583B90_sub_583B90.cpp（角色创建主流程，含
//   "CHARACTER CREATED" 事件）、docs/03_类与RTTI总表.md（IRDActiveObject vmt200
//   = 命中主处理器定案）、dump_skills.txt 0x63/0x64 区块。
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】角色创建/服务器数据主流程配套辅助（0x583A40-0x583B50）
// 主流程 0x583B90 在 src/combat/bigfunc_583B90_sub_583B90.cpp；
// 本区是它的字符串槽清理 / 数据槽 setter / 结构拷贝 / 查表 / 全局缓冲释放。
// ============================================================
// ------------------------------------------------------------
// 0x583A40 sub_583A40 —— 清空对象 +588 起的字符串槽（+601/+602 字节置 0，尾调 698F90 析构字符串）
// ------------------------------------------------------------
char /*thiscall*/ sub_583A40(void *this)  // 函数: 清空对象 +588 起的字符串槽（+601/+602 字节置 0，尾调 698F90 析构字符串）
{
  int pThis_24C; // ecx

  pThis_24C = (int)this + 588;
  *(uint8_t *)(pThis_24C + 13) = 0;  // pThis_24C+13 = 0
  *(uint8_t *)(pThis_24C + 14) = 0;  // pThis_24C+14 = 0
  return sub_698F90(pThis_24C, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x583A60 sub_583A60 —— 读取 this+79 槽位（非 0 时调 0x5512D0 = 任务文本设置），0x583B90 流程取任务名用
// ------------------------------------------------------------
int /*thiscall*/ sub_583A60(int *this)  // 函数: 读取 this+79 槽位（非 0 时调 0x5512D0 = 任务文本设置），0x583B90 流程取任务名用
{
  int result; // eax

  result = *(this + 79);  // result = this+79
  if ( result != 0 )  // 若 result != 0
    return sub_5512D0(this, *(this + 79));  // 调 任务名/文本设置（152 行：47E720 + 41A5E0/565EE0 + 44AB90=TAB_SELECT）
  return result;
}



// ------------------------------------------------------------
// 0x583A80 sub_583A80 —— 数值槽 setter：+50 标志为真直写 +56，否则写 +52 = a2 - 基址表 dword_79D100[+44]
// ------------------------------------------------------------
int /*thiscall*/ sub_583A80(int this, int nArg2)  // 函数: 数值槽 setter：+50 标志为真直写 +56，否则写 +52 = a2 - 基址表 dword_79D100[+44]
{
  int result; // eax

  result = nArg2;
  if ( *(uint8_t *)(this + 50) != 0 )  // 若 *(uint8_t *)(this + 50) != 0
  {
    *(uint32_t *)(this + 56) = nArg2;  // this+56 = nArg2
  }
  else
  {
    result = nArg2 - dword_79D100[*(uint32_t *)(this + 44)];
    *(uint32_t *)(this + 52) = result;  // this+52 = result
  }
  return result;
}



// ------------------------------------------------------------
// 0x583AB0 sub_583AB0 —— 4 段缓冲拷贝构造（this+0/+18/+8/+46 ← a2 同偏移，46B080=内存复制）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_583AB0(uint32_t *this, uint32_t *pArg2)  // 函数: 4 段缓冲拷贝构造（this+0/+18/+8/+46 ← a2 同偏移，46B080=内存复制）
{
  *this = *pArg2;  // *this 写入 *pArg2
  sub_46B080(this + 1, (unsigned int)(pArg2 + 1));  // 调 clong 构造与初值写入
  sub_46B080((uint32_t *)((char *)this + 18), (unsigned int)pArg2 + 18);  // 调 clong 构造与初值写入
  sub_46B080(this + 8, (unsigned int)(pArg2 + 8));  // 调 clong 构造与初值写入
  sub_46B080((uint32_t *)((char *)this + 46), (unsigned int)pArg2 + 46);  // 调 clong 构造与初值写入
  return this;
}



// ------------------------------------------------------------
// 0x583B30 sub_583B30 —— 按 this+72 下标查 this+69 表（16字节/项），-1 则返回 -1
// ------------------------------------------------------------
int /*thiscall*/ sub_583B30(uint32_t *this)  // 函数: 按 this+72 下标查 this+69 表（16字节/项），-1 则返回 -1
{
  int result; // eax

  result = *(this + 72);  // result = this+72
  if ( result != -1 )  // 若 result != -1
    return *(uint32_t *)(*(this + 69) + 16 * result);
  return result;
}



// ------------------------------------------------------------
// 0x583B50 sub_583B50 —— 释放全局缓冲 dword_9B9468 并清零 9B946C/9B9470（服务器列表缓存）【推断】
// ------------------------------------------------------------
void sub_583B50()  // 函数: 释放全局缓冲 dword_9B9468 并清零 9B946C/9B9470（服务器列表缓存）【推断】
{
  if ( dword_9B9468 != nullptr )  // 若 dword_9B9468 非空
    j__free(dword_9B9468);  // 调 堆释放
  dword_9B9468 = nullptr;  // dword_9B9468 = nullptr 空指针
  dword_9B946C = 0;
  dword_9B9470 = 0;
}



// ============================================================
// 【分区 2】A* 寻路引擎（0x58A9D0-0x58B380）
// 结构还原：this+16418/16419=网格宽/高，this+16420=网格数据（0=可走 1=对角阻挡
// 2=阻挡），this+16417=节点池游标，this+16=开链表头（按 f 值升序），
// this+31=闭链表头，this+1056=松弛环形缓冲游标（1024 环）。
// 节点 15 dword：[0]=f、[1]=h、[2]=g、[3]=x、[4]=y、[5]=父、[14]=链表 next。
// 搜索上限 500 次迭代（sub_58B140）；启发式 = |dx|+|dy|（曼哈顿距离）。
// ============================================================
// ------------------------------------------------------------
// 0x58A9D0 sub_58A9D0 —— 设置寻路网格：+16420=数据指针、+16418=宽 a3、+16419=高 a4
// ------------------------------------------------------------
int /*thiscall*/ sub_58A9D0(uint32_t *this, uint32_t *uArg2, int nArg3, int nArg4)  // 函数: 设置寻路网格：+16420=数据指针、+16418=宽 a3、+16419=高 a4
{
  *(this + 16420) = *uArg2;  // this+65680 = *uArg2
  *(this + 16418) = nArg3;  // this+65672 = nArg3
  *(this + 16419) = nArg4;  // this+65676 = nArg4
  return nArg3;
}



// ------------------------------------------------------------
// 0x58AA00 sub_58AA00 —— 寻路器复位：节点池游标清零、memset 网格缓存(0x1000/0xF000×2)、开/闭链表头清空
// ------------------------------------------------------------
int /*thiscall*/ sub_58AA00(uint32_t *this)  // 函数: 寻路器复位：节点池游标清零、memset 网格缓存(0x1000/0xF000×2)、开/闭链表头清空
{
  *(this + 16417) = 0;  // this+65668 = 0
  memset(this + 32, 0, 0x1000u);  // 调 内存按字节填充
  memset(this + 1057, 0, 0xF000u);  // 调 内存按字节填充
  memset(this + 1057, 0, 0xF000u);  // 调 内存按字节填充
  *(this + 16) = 0;  // this+64 = 0
  *(this + 7) = 0;  // this+28 = 0
  *(this + 31) = 0;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 8) = 0;  // this+32 = 0
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 24) = 0;  // this+96 = 0
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 25) = 0;  // this+100 = 0
  *(this + 11) = 0;  // this+44 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 27) = 0;  // this+108 = 0
  *(this + 13) = 0;  // this+52 = bAuraState
  *(this + 28) = 0;  // this+112 = pHostComp
  *(this + 14) = 0;  // this+56 = 0
  *(this + 29) = 0;  // this+116 = 0
  *(this + 15) = 0;  // this+60 = 0
  *(this + 30) = 0;  // this+120 = 动画对象指针
  *(this + 1056) = 0;  // this+4224 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x58AA80 sub_58AA80 —— 开链表按 f 值升序插入节点（+16 头插遍历）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_58AA80(uint32_t *this, uint32_t *pArg2)  // 函数: 开链表按 f 值升序插入节点（+16 头插遍历）
{
  uint32_t *result; // eax
  uint32_t *pThis_2; // ecx

  result = (uint32_t *)*(this + 16);
  if ( result != nullptr )  // 若 result 非空
  {
    pThis_2 = this + 2;
    do
    {
      if ( *result > *pArg2 )  // 若 *result > *pArg2
        break;
      pThis_2 = result;
      result = (uint32_t *)result[14];
    }
    while ( result != nullptr );  // 当 result 非空 循环
    pArg2[14] = result;
    pThis_2[14] = pArg2;
  }
  else
  {
    *(this + 16) = pArg2;  // this+64 = pArg2
    return pArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x58AAC0 sub_58AAC0 —— A* 松弛主循环：取开链表最优节点，8 邻居 g 改善者更新并压入 1024 环形松弛缓冲
// ------------------------------------------------------------
int /*thiscall*/ sub_58AAC0(int *this, int pArg2)  // 函数: A* 松弛主循环：取开链表最优节点，8 邻居 g 改善者更新并压入 1024 环形松弛缓冲
{
  int **v2; // edi
  int *v3; // eax
  int v4; // edx
  int v5; // ebx
  int fld_e1056; // edx
  bool fld_e10562; // sf
  int result; // eax
  int fld_e10563; // eax
  int v10; // edx
  int v11; // eax
  int **v12; // edi
  int *v13; // eax
  int v14; // esi
  int v15; // ebx
  int fld_e10564; // eax
  int *v17; // eax
  int v18; // esi
  int v19; // ebx
  int fld_e10565; // eax
  int *v21; // eax
  int v22; // esi
  int v23; // ebx
  int fld_e10566; // eax
  int *v25; // eax
  int v26; // esi
  int v27; // ebx
  int fld_e10567; // eax
  int v29; // [esp+Ch] [ebp-4h]
  int v30; // [esp+Ch] [ebp-4h]

  v29 = 0;
  v2 = (int **)(pArg2 + 24);
  do
  {
    v3 = *v2;
    if ( *v2 == nullptr )  // 若 *v2 == nullptr
      break;
    v4 = *(uint32_t *)(pArg2 + 8) + 1;
    if ( v3[2] > v4 )  // 若 v3[2] > v4
    {
      v5 = v4 + v3[1];
      v3[2] = v4;
      *v3 = v5;  // *v3 写入 v5
      v3[5] = pArg2;
      *(this + *(this + 1056) + 32) = (int)v3;
      fld_e1056 = *(this + 1056) + 1;
      fld_e10562 = *(this + 1056) - 1023 < 0;
      *(this + 1056) = fld_e1056;  // this+4224 = fld_e1056
      if ( fld_e10562 == __OFSUB__(fld_e1056, 1024) )  // 若 fld_e10562 == __OFSUB__(fld_e1056, 1024)
        *(this + 1056) = 0;  // this+4224 = 0
    }
    ++v2;  // 自增v2
    ++v29;  // 自增v29
  }
  while ( v29 < 8 );  // 当 v29 < 8 循环
  for ( result = *(this + 1056); result > 0; result = *(this + 1056) )  // 循环：result = *(this + 1056); result > 0; result = *(this + 1056)
  {
    fld_e10563 = *(this + 1056);  // fld_e10563 = this+1056
    if ( fld_e10563 > 0 )  // 若 fld_e10563 > 0
    {
      v11 = fld_e10563 - 1;
      *(this + 1056) = v11;  // this+4224 = v11
      v10 = *(this + v11 + 32);
    }
    else
    {
      v10 = 0;
    }
    v30 = 0;
    v12 = (int **)(v10 + 28);
    do
    {
      v13 = *(v12 - 1);
      if ( v13 == nullptr )  // 若 v13 为空
        break;
      v14 = *(uint32_t *)(v10 + 8) + 1;
      if ( v13[2] > v14 )  // 若 v13[2] > v14
      {
        v15 = v14 + v13[1];
        v13[2] = v14;
        *v13 = v15;  // *v13 写入 v15
        v13[5] = v10;
        *(this + *(this + 1056) + 32) = (int)v13;
        fld_e10564 = *(this + 1056) + 1;
        fld_e10562 = *(this + 1056) - 1023 < 0;
        *(this + 1056) = fld_e10564;  // this+4224 = fld_e10564
        if ( fld_e10562 == __OFSUB__(fld_e10564, 1024) )  // 若 fld_e10562 == __OFSUB__(fld_e10564, 1024)
          *(this + 1056) = 0;  // this+4224 = 0
      }
      v17 = *v12;
      if ( *v12 == nullptr )  // 若 *v12 == nullptr
        break;
      v18 = *(uint32_t *)(v10 + 8) + 1;
      if ( v17[2] > v18 )  // 若 v17[2] > v18
      {
        v19 = v18 + v17[1];
        v17[2] = v18;
        *v17 = v19;  // *v17 写入 v19
        v17[5] = v10;
        *(this + *(this + 1056) + 32) = (int)v17;
        fld_e10565 = *(this + 1056) + 1;
        fld_e10562 = *(this + 1056) - 1023 < 0;
        *(this + 1056) = fld_e10565;  // this+4224 = fld_e10565
        if ( fld_e10562 == __OFSUB__(fld_e10565, 1024) )  // 若 fld_e10562 == __OFSUB__(fld_e10565, 1024)
          *(this + 1056) = 0;  // this+4224 = 0
      }
      v21 = v12[1];
      if ( v21 == nullptr )  // 若 v21 为空
        break;
      v22 = *(uint32_t *)(v10 + 8) + 1;
      if ( v21[2] > v22 )  // 若 v21[2] > v22
      {
        v23 = v22 + v21[1];
        v21[2] = v22;
        *v21 = v23;  // *v21 写入 v23
        v21[5] = v10;
        *(this + *(this + 1056) + 32) = (int)v21;
        fld_e10566 = *(this + 1056) + 1;
        fld_e10562 = *(this + 1056) - 1023 < 0;
        *(this + 1056) = fld_e10566;  // this+4224 = fld_e10566
        if ( fld_e10562 == __OFSUB__(fld_e10566, 1024) )  // 若 fld_e10562 == __OFSUB__(fld_e10566, 1024)
          *(this + 1056) = 0;  // this+4224 = 0
      }
      v25 = v12[2];
      if ( v25 == nullptr )  // 若 v25 为空
        break;
      v26 = *(uint32_t *)(v10 + 8) + 1;
      if ( v25[2] > v26 )  // 若 v25[2] > v26
      {
        v27 = v26 + v25[1];
        v25[2] = v26;
        *v25 = v27;  // *v25 写入 v27
        v25[5] = v10;
        *(this + *(this + 1056) + 32) = (int)v25;
        fld_e10567 = *(this + 1056) + 1;
        fld_e10562 = *(this + 1056) - 1023 < 0;
        *(this + 1056) = fld_e10567;  // this+4224 = fld_e10567
        if ( fld_e10562 == __OFSUB__(fld_e10567, 1024) )  // 若 fld_e10562 == __OFSUB__(fld_e10567, 1024)
          *(this + 1056) = 0;  // this+4224 = 0
      }
      v12 += 4;
      v30 += 4;
    }
    while ( v30 < 8 );  // 当 v30 < 8 循环
  }
  return result;
}


// ------------------------------------------------------------
// 0x58ACE0 sub_58ACE0 —— 从 1024×15-dword 节点池分配节点（游标 +16417 环形推进，60 字节清零）
// ------------------------------------------------------------
int /*thiscall*/ sub_58ACE0(uint32_t *this)  // 函数: 从 1024×15-dword 节点池分配节点（游标 +16417 环形推进，60 字节清零）
{
  if ( (int)*(this + 16417) >= 1024 )  // 若 (int)*(this + 16417) >= 1024
    *(this + 16417) = 0;  // this+65668 = 0
  memset(this + 15 * *(this + 16417) + 1057, 0, 0x3Cu);  // 调 内存按字节填充
  return (int)(this + 15 * (*(this + 16417))++ + 1057);
}



// ------------------------------------------------------------
// 0x58AD30 sub_58AD30 —— 可行走判定：网格值≠2 且（允许对角 或 网格值≠1）→ true
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_58AD30(int *this, int nArg2, int nArg3, char pszArg4)  // 函数: 可行走判定：网格值≠2 且（允许对角 或 网格值≠1）→ true
{
  int fld_e16418; // eax
  char fld_e16420; // al
  BOOL result; // eax

  result = false;
  if ( nArg2 >= 0 && nArg3 >= 0 )  // 若 nArg2 >= 0 && nArg3 >= 0
  {
    fld_e16418 = *(this + 16418);  // fld_e16418 = this+16418
    if ( nArg2 < fld_e16418 && nArg3 < *(this + 16419) )  // 若 nArg2 < fld_e16418 && nArg3 < *(this + 16419)
    {
      fld_e16420 = *(uint8_t *)(*(this + 16420) + nArg3 * fld_e16418 + nArg2);
      if ( fld_e16420 != 2 && (pszArg4 != 0 || fld_e16420 != 1) )  // 若 fld_e16420 != 2 && (pszArg4 != 0 || fld_e16420 != 1)
        return true;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58AD80 sub_58AD80 —— 邻居松弛：g+1 更新、h=|dx|+|dy| 曼哈顿、回写父指针 +20、f=g+h、入开链表
// ------------------------------------------------------------
int /*thiscall*/ sub_58AD80(int *this, int pArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数: 邻居松弛：g+1 更新、h=|dx|+|dy| 曼哈顿、回写父指针 +20、f=g+h、入开链表
{
  int result; // eax
  int v7; // esi
  int nArg32; // edx
  int v9; // ecx
  uint32_t *v10; // edx
  int v11; // ecx
  uint32_t *v12; // ecx
  unsigned int v13; // eax
  uint32_t *v14; // edi
  int v15; // edx
  uint32_t *v16; // ebx
  int v17; // edx

  result = *(this + 16);  // result = this+16
  v7 = *(uint32_t *)(pArg2 + 8) + 1;
  if ( result != 0 )  // 若 result != 0
  {
    while ( 1 )  // 无限循环
    {
      nArg32 = nArg3;
      if ( *(uint32_t *)(result + 12) == nArg3 && *(uint32_t *)(result + 16) == nArg4 )  // 若 *(uint32_t *)(result + 12) == nArg3 && *(uint32_t *)(result + ..
        break;
      result = *(uint32_t *)(result + 56);  // result = result+56
      if ( result == 0 )  // 若 result == 0
        goto LABEL_12;  // 跳转 LABEL_12
    }
    v9 = 0;
    v10 = (uint32_t *)(pArg2 + 24);
    do
    {
      if ( *v10 == 0 )  // 若 *v10 == 0
        break;
      ++v9;  // 自增v9
      ++v10;  // 自增v10
    }
    while ( v9 < 8 );  // 当 v9 < 8 循环
    *(uint32_t *)(pArg2 + 4 * v9 + 24) = result;
    if ( v7 < *(uint32_t *)(result + 8) )  // 若 v7 < *(uint32_t *)(result + 8)
    {
      v11 = *(uint32_t *)(result + 4);  // v11 = result+4
      *(uint32_t *)(result + 20) = pArg2;  // result+20 = pArg2
      *(uint32_t *)(result + 8) = v7;  // result+8 = v7
      *(uint32_t *)result = v7 + v11;
    }
  }
  else
  {
    nArg32 = nArg3;
LABEL_12:
    result = *(this + 31);  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
    if ( result != 0 )  // 若 result != 0
    {
      while ( *(uint32_t *)(result + 12) != nArg32 || *(uint32_t *)(result + 16) != nArg4 )  // 当 *(uint32_t *)(result + 12) != nArg32 || *(uint32_t *)(result +.. 循环
      {
        result = *(uint32_t *)(result + 56);  // result = result+56
        if ( result == 0 )  // 若 result == 0
          goto LABEL_16;  // 跳转 LABEL_16
      }
      v15 = 0;
      v16 = (uint32_t *)(pArg2 + 24);
      do
      {
        if ( *v16 == 0 )  // 若 *v16 == 0
          break;
        ++v15;  // 自增v15
        ++v16;  // 自增v16
      }
      while ( v15 < 8 );  // 当 v15 < 8 循环
      *(uint32_t *)(pArg2 + 4 * v15 + 24) = result;
      if ( v7 < *(uint32_t *)(result + 8) )  // 若 v7 < *(uint32_t *)(result + 8)
      {
        v17 = v7 + *(uint32_t *)(result + 4);
        *(uint32_t *)(result + 8) = v7;  // result+8 = v7
        *(uint32_t *)result = v17;
        *(uint32_t *)(result + 20) = pArg2;  // result+20 = pArg2
        return sub_58AAC0(this, result);  // 调 A* 松弛主循环：取开链表最优节点，8 邻居 g 改善者更新并压入 1024 环形松弛缓冲
      }
    }
    else
    {
LABEL_16:
      v12 = (uint32_t *)sub_58ACE0(this);  // 调 从 1024×15-dword 节点池分配节点（游标 +16417 环形推进，60 字节清零）
      v12[3] = nArg3;
      v13 = abs32(nArg3 - nArg5) + abs32(nArg4 - nArg6);
      v12[1] = v13;
      v12[4] = nArg4;
      v12[2] = v7;
      *v12 = v7 + v13;  // *v12 写入 v7 + v13
      v12[5] = pArg2;
      sub_58AA80(this, v12);  // 调 开链表按 f 值升序插入节点（+16 头插遍历）
      result = 0;
      v14 = (uint32_t *)(pArg2 + 24);
      do
      {
        if ( *v14 == 0 )  // 若 *v14 == 0
          break;
        ++result;  // 自增result
        ++v14;  // 自增v14
      }
      while ( result < 8 );  // 当 result < 8 循环
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58AEC0 sub_58AEC0 —— 8 方向邻域扩展（右/下/左下/左/左上/上/右上/右下 顺序逐方向可行走检查+松弛）
// ------------------------------------------------------------
void /*thiscall*/ sub_58AEC0(int *this, int pArg2, int nArg3, int nArg4, char pszArg5)  // 函数: 8 方向邻域扩展（右/下/左下/左/左上/上/右上/右下 顺序逐方向可行走检查+松弛）
{
  int pArg22; // ecx
  int v7; // esi
  int v8; // edi
  int fld_e16418; // eax
  char fld_e16420; // al
  int v11; // edi
  int fld_e164182; // eax
  char fld_e164202; // al
  int v14; // esi
  int fld_e164183; // eax
  char fld_e164203; // al
  int v17; // esi
  int fld_e164184; // eax
  char fld_e164204; // al
  int v20; // edi
  int fld_e164185; // eax
  char fld_e164205; // al
  int v23; // edi
  int fld_e164186; // eax
  char fld_e164206; // al
  int v26; // esi
  int fld_e164187; // eax
  char fld_e164207; // al
  int v29; // esi
  int fld_e164188; // eax
  char fld_e164208; // al

  pArg22 = pArg2;
  v7 = *(uint32_t *)(pArg2 + 12) + 1;
  v8 = *(uint32_t *)(pArg2 + 16);  // v8 = pArg2+16
  if ( v7 >= 0 && v8 >= 0 )  // 若 v7 >= 0 && v8 >= 0
  {
    fld_e16418 = *(this + 16418);  // fld_e16418 = this+16418
    if ( v7 < fld_e16418 && v8 < *(this + 16419) )  // 若 v7 < fld_e16418 && v8 < *(this + 16419)
    {
      fld_e16420 = *(uint8_t *)(*(this + 16420) + v8 * fld_e16418 + v7);
      if ( fld_e16420 != 2 && (pszArg5 != 0 || fld_e16420 != 1) )  // 若 fld_e16420 != 2 && (pszArg5 != 0 || fld_e16420 != 1)
      {
        sub_58AD80(pArg2, v7, v8, nArg3, nArg4);  // 调 邻居松弛：g+1 更新、h=|dx|+|dy| 曼哈顿、回写父指针 +20、f=g+h、入开链表
        pArg22 = pArg2;
      }
    }
  }
  v11 = v8 + 1;
  if ( v7 >= 0 && v11 >= 0 )  // 若 v7 >= 0 && v11 >= 0
  {
    fld_e164182 = *(this + 16418);  // fld_e164182 = this+16418
    if ( v7 < fld_e164182 && v11 < *(this + 16419) )  // 若 v7 < fld_e164182 && v11 < *(this + 16419)
    {
      fld_e164202 = *(uint8_t *)(*(this + 16420) + v11 * fld_e164182 + v7);
      if ( fld_e164202 != 2 && (pszArg5 != 0 || fld_e164202 != 1) )  // 若 fld_e164202 != 2 && (pszArg5 != 0 || fld_e164202 != 1)
      {
        sub_58AD80(pArg22, v7, v11, nArg3, nArg4);  // 调 邻居松弛：g+1 更新、h=|dx|+|dy| 曼哈顿、回写父指针 +20、f=g+h、入开链表
        pArg22 = pArg2;
      }
    }
  }
  v14 = v7 - 1;
  if ( v14 >= 0 && v11 >= 0 )  // 若 v14 >= 0 && v11 >= 0
  {
    fld_e164183 = *(this + 16418);  // fld_e164183 = this+16418
    if ( v14 < fld_e164183 && v11 < *(this + 16419) )  // 若 v14 < fld_e164183 && v11 < *(this + 16419)
    {
      fld_e164203 = *(uint8_t *)(*(this + 16420) + v11 * fld_e164183 + v14);
      if ( fld_e164203 != 2 && (pszArg5 != 0 || fld_e164203 != 1) )  // 若 fld_e164203 != 2 && (pszArg5 != 0 || fld_e164203 != 1)
      {
        sub_58AD80(pArg22, v14, v11, nArg3, nArg4);  // 调 邻居松弛：g+1 更新、h=|dx|+|dy| 曼哈顿、回写父指针 +20、f=g+h、入开链表
        pArg22 = pArg2;
      }
    }
  }
  v17 = v14 - 1;
  if ( v17 >= 0 && v11 >= 0 )  // 若 v17 >= 0 && v11 >= 0
  {
    fld_e164184 = *(this + 16418);  // fld_e164184 = this+16418
    if ( v17 < fld_e164184 && v11 < *(this + 16419) )  // 若 v17 < fld_e164184 && v11 < *(this + 16419)
    {
      fld_e164204 = *(uint8_t *)(*(this + 16420) + v11 * fld_e164184 + v17);
      if ( fld_e164204 != 2 && (pszArg5 != 0 || fld_e164204 != 1) )  // 若 fld_e164204 != 2 && (pszArg5 != 0 || fld_e164204 != 1)
      {
        sub_58AD80(pArg22, v17, v11, nArg3, nArg4);  // 调 邻居松弛：g+1 更新、h=|dx|+|dy| 曼哈顿、回写父指针 +20、f=g+h、入开链表
        pArg22 = pArg2;
      }
    }
  }
  v20 = v11 - 1;
  if ( v17 >= 0 && v20 >= 0 )  // 若 v17 >= 0 && v20 >= 0
  {
    fld_e164185 = *(this + 16418);  // fld_e164185 = this+16418
    if ( v17 < fld_e164185 && v20 < *(this + 16419) )  // 若 v17 < fld_e164185 && v20 < *(this + 16419)
    {
      fld_e164205 = *(uint8_t *)(*(this + 16420) + v20 * fld_e164185 + v17);
      if ( fld_e164205 != 2 && (pszArg5 != 0 || fld_e164205 != 1) )  // 若 fld_e164205 != 2 && (pszArg5 != 0 || fld_e164205 != 1)
      {
        sub_58AD80(pArg22, v17, v20, nArg3, nArg4);  // 调 邻居松弛：g+1 更新、h=|dx|+|dy| 曼哈顿、回写父指针 +20、f=g+h、入开链表
        pArg22 = pArg2;
      }
    }
  }
  v23 = v20 - 1;
  if ( v17 >= 0 && v23 >= 0 )  // 若 v17 >= 0 && v23 >= 0
  {
    fld_e164186 = *(this + 16418);  // fld_e164186 = this+16418
    if ( v17 < fld_e164186 && v23 < *(this + 16419) )  // 若 v17 < fld_e164186 && v23 < *(this + 16419)
    {
      fld_e164206 = *(uint8_t *)(*(this + 16420) + v23 * fld_e164186 + v17);
      if ( fld_e164206 != 2 && (pszArg5 != 0 || fld_e164206 != 1) )  // 若 fld_e164206 != 2 && (pszArg5 != 0 || fld_e164206 != 1)
      {
        sub_58AD80(pArg22, v17, v23, nArg3, nArg4);  // 调 邻居松弛：g+1 更新、h=|dx|+|dy| 曼哈顿、回写父指针 +20、f=g+h、入开链表
        pArg22 = pArg2;
      }
    }
  }
  v26 = v17 + 1;
  if ( v26 >= 0 && v23 >= 0 )  // 若 v26 >= 0 && v23 >= 0
  {
    fld_e164187 = *(this + 16418);  // fld_e164187 = this+16418
    if ( v26 < fld_e164187 && v23 < *(this + 16419) )  // 若 v26 < fld_e164187 && v23 < *(this + 16419)
    {
      fld_e164207 = *(uint8_t *)(*(this + 16420) + v23 * fld_e164187 + v26);
      if ( fld_e164207 != 2 && (pszArg5 != 0 || fld_e164207 != 1) )  // 若 fld_e164207 != 2 && (pszArg5 != 0 || fld_e164207 != 1)
      {
        sub_58AD80(pArg22, v26, v23, nArg3, nArg4);  // 调 邻居松弛：g+1 更新、h=|dx|+|dy| 曼哈顿、回写父指针 +20、f=g+h、入开链表
        pArg22 = pArg2;
      }
    }
  }
  v29 = v26 + 1;
  if ( v29 >= 0 && v23 >= 0 )  // 若 v29 >= 0 && v23 >= 0
  {
    fld_e164188 = *(this + 16418);  // fld_e164188 = this+16418
    if ( v29 < fld_e164188 && v23 < *(this + 16419) )  // 若 v29 < fld_e164188 && v23 < *(this + 16419)
    {
      fld_e164208 = *(uint8_t *)(*(this + 16420) + v23 * fld_e164188 + v29);
      if ( fld_e164208 != 2 && (pszArg5 != 0 || fld_e164208 != 1) )  // 若 fld_e164208 != 2 && (pszArg5 != 0 || fld_e164208 != 1)
        sub_58AD80(pArg22, v29, v23, nArg3, nArg4);  // 调 邻居松弛：g+1 更新、h=|dx|+|dy| 曼哈顿、回写父指针 +20、f=g+h、入开链表
    }
  }
}


// ------------------------------------------------------------
// 0x58B140 sub_58B140 —— A* 搜索主循环：上限 500 次迭代，命中目标(x,y)或 f≥截断值即返回当前节点
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_58B140(int *this, unsigned int uArg2, unsigned int uArg3, int nArg4, int nArg5, char pszArg6)  // 函数: A* 搜索主循环：上限 500 次迭代，命中目标(x,y)或 f≥截断值即返回当前节点
{
  unsigned int v7; // edi
  unsigned int v8; // ebx
  unsigned int *v9; // eax
  unsigned int v10; // edi
  int i; // edi
  uint32_t *result; // eax
  int fld_e16418; // [esp+Ch] [ebp-4h]

  v7 = abs32(uArg2 - nArg4);
  v8 = abs32(uArg3 - nArg5);
  fld_e16418 = *(this + 16418) * (v7 + 1) + *(this + 16419) * (v8 + 1);
  v9 = (unsigned int *)sub_58ACE0(this);  // 调 从 1024×15-dword 节点池分配节点（游标 +16417 环形推进，60 字节清零）
  v10 = v8 + v7;
  v9[1] = v10;
  *v9 = v10;  // *v9 写入 v10
  v9[2] = 0;
  v9[3] = uArg2;
  v9[4] = uArg3;
  *(this + 16) = (int)v9;  // this+64 = (int)v9
  for ( i = 0; i < 500; ++i )  // 循环：i = 0; i < 500; ++i
  {
    result = (uint32_t *)*(this + 16);
    if ( result == nullptr )  // 若 result 为空
      break;
    if ( fld_e16418 < result[2] || result[3] == nArg4 && result[4] == nArg5 )  // 若 fld_e16418 < result[2] || result[3] == nArg4 && result[4] == n..
      return result;
    *(this + 16) = result[14];  // this+64 = result[14]
    result[14] = *(this + 31);  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
    *(this + 31) = (int)result;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
    sub_58AEC0(this, (int)result, nArg4, nArg5, pszArg6);  // 调 8 方向邻域扩展（右/下/左下/左/左上/上/右上/右下 顺序逐方向可行走检查+松弛）
  }
  return nullptr;
}



// ------------------------------------------------------------
// 0x58B200 sub_58B200 —— 寻路总入口：复位→58B140 搜索→沿父链回溯到第 1 步→输出目标格 (a6,a7)→复位
// ------------------------------------------------------------
int /*thiscall*/ sub_58B200(int *this, unsigned int uArg2, unsigned int uArg3, int nArg4, int nArg5, uint32_t *uArg6, uint32_t *uArg7, char pszArg8)  // 函数: 寻路总入口：复位→58B140 搜索→沿父链回溯到第 1 步→输出目标格 (a6,a7)→复位
{
  int *v10; // eax

  sub_58AA00(this);  // 调 寻路器复位：节点池游标清零、memset 网格缓存(0x1000/0xF000×2)、开/闭链表头清空
  *(this + 1) = 0;  // this+4 = pHostObj
  if ( uArg3 == nArg5 && uArg2 == nArg4 )  // 若 uArg3 == nArg5 && uArg2 == nArg4
    return 1;
  v10 = sub_58B140(this, uArg2, uArg3, nArg4, nArg5, pszArg8);  // 调 A* 搜索主循环：上限 500 次迭代，命中目标(x,y)或 f≥截断值即返回当前节点
  if ( v10 != nullptr )  // 若 v10 非空
  {
    for ( ; v10[2] > 1; v10 = (int *)v10[5] )  // 循环：; v10[2] > 1; v10 = (int *)v10[5]
      ;
    *uArg6 = v10[3];  // *uArg6 写入 v10[3]
    *uArg7 = v10[4];  // *uArg7 写入 v10[4]
    *(this + 1) = *(this + 16417);  // this+4 = pHostObj
    sub_58AA00(this);  // 调 寻路器复位：节点池游标清零、memset 网格缓存(0x1000/0xF000×2)、开/闭链表头清空
    return 1;
  }
  else
  {
    sub_58AA00(this);  // 调 寻路器复位：节点池游标清零、memset 网格缓存(0x1000/0xF000×2)、开/闭链表头清空
    return 0;
  }
}



// ------------------------------------------------------------
// 0x58B2A0 sub_58B2A0 —— dword 动态数组 push（容量按 +100 步长扩容，operator new(4n+400) 迁移）
// ------------------------------------------------------------
int /*thiscall*/ sub_58B2A0(int this, int nArg2)  // 函数: dword 动态数组 push（容量按 +100 步长扩容，operator new(4n+400) 迁移）
{
  int fld_4; // eax
  uint32_t *pMem; // edi
  int i; // eax
  int fld_42; // eax

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( *(uint32_t *)(this + 8) >= fld_4 )  // 若 *(uint32_t *)(this + 8) >= fld_4
  {
    pMem = operator new(4 * fld_4 + 400);
    for ( i = 0; i < *(uint32_t *)(this + 4); ++i )  // 循环：i = 0; i < *(uint32_t *)(this + 4); ++i
      pMem[i] = *(uint32_t *)(*(uint32_t *)this + 4 * i);  // pMem[i] 写入 *(uint32_t *)(*(uint32_t *)this + 4 * i)
    j_j__free(*(void **)this);  // 调 j__free
    fld_42 = *(uint32_t *)(this + 4);  // fld_42 = this+4
    *(uint32_t *)this = pMem;
    *(uint32_t *)(this + 4) = fld_42 + 100;  // this+4 = fld_42 + 100
  }
  *(uint32_t *)(*(uint32_t *)this + 4 * (*(uint32_t *)(this + 8))++) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x58B310 sub_58B310 —— dword 动态数组 push（另一实例布局：+8 计数/+4 容量，扩容策略同 58B2A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58B310(int this, int nArg2)  // 函数: dword 动态数组 push（另一实例布局：+8 计数/+4 容量，扩容策略同 58B2A0）
{
  int fld_4; // eax
  uint32_t *pMem; // edi
  int i; // eax
  int fld_42; // eax

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( *(uint32_t *)(this + 12) >= fld_4 )  // 若 *(uint32_t *)(this + 12) >= fld_4
  {
    pMem = operator new(4 * fld_4 + 400);
    for ( i = 0; i < *(uint32_t *)(this + 4); ++i )  // 循环：i = 0; i < *(uint32_t *)(this + 4); ++i
      pMem[i] = *(uint32_t *)(*(uint32_t *)this + 4 * i);  // pMem[i] 写入 *(uint32_t *)(*(uint32_t *)this + 4 * i)
    j_j__free(*(void **)this);  // 调 j__free
    fld_42 = *(uint32_t *)(this + 4);  // fld_42 = this+4
    *(uint32_t *)this = pMem;
    *(uint32_t *)(this + 4) = fld_42 + 100;  // this+4 = fld_42 + 100
  }
  *(uint32_t *)(*(uint32_t *)this + 4 * (*(uint32_t *)(this + 12))++) = nArg2;
  return nArg2;
}



// ============================================================
// 【分区 3】定时指令时间线调度器（0x58B380-0x58B570）
// 指令流布局（dword 数组）：[函数指针][调度时刻][参数个数][参数...]；
// sub_58B380 逐条取出：当前时钟(699000)≥调度时刻则执行，否则回填延迟队列；
// sub_58B450 构造 = nengine::CNTimer + operator new(0xFA0) 指令缓冲。
// ============================================================
// ------------------------------------------------------------
// 0x58B380 sub_58B380 —— 时间线解释器主循环：读[函数指针][时刻][参数个数][参数...]，到点执行否则重排队
// ------------------------------------------------------------
int /*thiscall*/ sub_58B380(int *this)  // 函数: 时间线解释器主循环：读[函数指针][时刻][参数个数][参数...]，到点执行否则重排队
{
  int fld_e2; // ecx
  int result; // eax
  int fld_e4; // eax
  int v5; // ecx
  void (*v6)(void); // edx
  int v7; // edi
  int pThis_5; // eax
  int fld_e42; // ecx
  int v10; // edx
  int v11; // ebx
  int v12; // edi
  int fld_e43; // eax
  int v14; // ecx
  int v15; // [esp+4h] [ebp-8h]
  void (*v16)(void); // [esp+8h] [ebp-4h]

  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  result = 0;
  *(this + 4) = 0;  // this+16 = 0
  *(this + 3) = 0;  // this+12 = 技能槽记录次字
  if ( fld_e2 <= 0 )  // 若 fld_e2 <= 0
  {
    *(this + 2) = *(this + 3);  // this+8 = 技能槽记录首字
  }
  else
  {
    do
    {
      fld_e4 = *(this + 4);  // fld_e4 = this+4
      v5 = *this;
      v6 = *(void (**)(void))(*this + 4 * fld_e4++);
      *(this + 4) = fld_e4;  // this+16 = fld_e4
      v7 = *(uint32_t *)(v5 + 4 * fld_e4);
      v16 = v6;
      *(this + 4) = fld_e4 + 1;  // this+16 = fld_e4 + 1
      pThis_5 = sub_699000((int)(this + 5));  // 【clock_now(clk)】
      fld_e42 = *(this + 4);  // fld_e42 = this+4
      v10 = *this;
      v11 = *(uint32_t *)(*this + 4 * fld_e42++);
      *(this + 4) = fld_e42;  // this+16 = fld_e42
      v15 = *(uint32_t *)(v10 + 4 * fld_e42);
      *(this + 4) = fld_e42 + 1;  // this+16 = fld_e42 + 1
      if ( pThis_5 - v7 >= v11 )  // 若 pThis_5 - v7 >= v11
      {
        v16();
      }
      else
      {
        sub_58B310((int)this, (int)v16);  // 调 dword 动态数组 push（另一实例布局：+8 计数/+4 容量，扩容策略同 58B2A0）
        sub_58B310((int)this, v7);  // 调 dword 动态数组 push（另一实例布局：+8 计数/+4 容量，扩容策略同 58B2A0）
        sub_58B310((int)this, v11);  // 调 dword 动态数组 push（另一实例布局：+8 计数/+4 容量，扩容策略同 58B2A0）
        v12 = v15;
        sub_58B310((int)this, v15);  // 调 dword 动态数组 push（另一实例布局：+8 计数/+4 容量，扩容策略同 58B2A0）
        if ( *(this + 3) < *(this + 2) && v15 > 0 )  // this+12 = 技能槽记录次字
        {
          do
          {
            fld_e43 = *(this + 4);  // fld_e43 = this+4
            v14 = *(uint32_t *)(*this + 4 * fld_e43);
            *(this + 4) = fld_e43 + 1;  // this+16 = fld_e43 + 1
            sub_58B310((int)this, v14);  // 调 dword 动态数组 push（另一实例布局：+8 计数/+4 容量，扩容策略同 58B2A0）
            --v12;  // 自减v12
          }
          while ( v12 != 0 );  // 当 v12 != 0 循环
        }
      }
      result = *(this + 4);  // result = this+4
    }
    while ( result < *(this + 2) );  // this+8 = 技能槽记录首字
    *(this + 2) = *(this + 3);  // this+8 = 技能槽记录首字
  }
  return result;
}



// ------------------------------------------------------------
// 0x58B450 sub_58B450 —— 时间线构造：CNTimer 虚表装配 + operator new(0xFA0) 指令缓冲 + 时标 1000
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_58B450(uint8_t *this)  // 函数: 时间线构造：CNTimer 虚表装配 + operator new(0xFA0) 指令缓冲 + 时标 1000
{
  int pThis_14; // esi

  pThis_14 = (int)(this + 20);
  *(this + 24) = 0;  // this+96 = 0
  *((uint32_t *)this + 5) = &vftbl_nengine__CNTimer;  // this+20 = &vftbl_nengine__CNTimer
  *((uint32_t *)this + 7) = 0;  // this+28 = 0
  *(this + 32) = 1;  // this+128 = 1
  *(this + 34) = 0;  // this+136 = 0
  *(this + 33) = 0;  // this+132 = 0
  *((uint32_t *)this + 11) = 0;  // this+44 = 0
  *((uint32_t *)this + 10) = 0;  // this+40 = 状态子标志
  *((uint32_t *)this + 9) = 0;  // this+36 = 状态字
  *(uint32_t *)this = operator new(0xFA0u);  // operator new 分配 4000 字节
  *((uint32_t *)this + 1) = 1000;  // this+4 = pHostObj
  *((uint32_t *)this + 2) = 0;  // this+8 = 技能槽记录首字
  sub_698F90(pThis_14, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  return this;
}



// ------------------------------------------------------------
// 0x58B4D0 sub_58B4D0 —— 时间线析构：释放指令缓冲，+20 恢复 nengine::IObject 虚表
// ------------------------------------------------------------
void /*thiscall*/ sub_58B4D0(int this)  // 函数: 时间线析构：释放指令缓冲，+20 恢复 nengine::IObject 虚表
{
  j_j__free(*(void **)this);  // 调 j__free
  *(uint32_t *)(this + 20) = &vftbl_nengine__IObject;  // this+80 = nAuraStage
  *(uint8_t *)(this + 24) = 0;  // this+24 = 0
}



// ------------------------------------------------------------
// 0x58B570 sub_58B570 —— 列表头/上下文结构初始化（+0 指针、+2..+5 清零）
// ------------------------------------------------------------
size_t */*thiscall*/ sub_58B570(size_t *this, void *pArg2)  // 函数: 列表头/上下文结构初始化（+0 指针、+2..+5 清零）
{
  int i; // ebx

  *this = (size_t)pArg2;  // *this 写入 (size_t)pArg2
  *(this + 2) = 0;  // this+8 = 技能槽记录首字
  *(this + 3) = 0;  // this+12 = 技能槽记录次字
  *(this + 4) = 0;  // this+16 = 0
  *(this + 5) = 0;  // this+20 = 0
  for ( i = 512; i != 0; --i )  // 循环：i = 512; i != 0; --i
  {
    pArg2 = operator new(*this);
    sub_49C800(&pArg2);  // 调 deque 尾格写入（4 格一块按需 new(0x10)，+16 计数自增）
  }
  return this;
}



// ============================================================
// 【分区 4】怪物友好度判定族 FriendShip（0x58B5F0-0x58B750）
// 虚方法 vmt8 = RTTI 判定"目标是否本族友好怪物"（Zealot 狂信者/StarFish 海星/
// Tau 牛头怪 +332 列表含 20）；vmt4 = 好感交互触发（取双 word 参数→
// __RTDynamicCast 到 IRDActiveObject→设为追踪目标→sub_4DB200(23,-1) 播报）。
// ============================================================
// ------------------------------------------------------------
// 0x58B5F0 CNMonsterFriendShip__vmt4 —— FriendShip 好感交互触发：取双 word 参数→RTCast 到 IRDActiveObject→设为追踪目标→4DB200(23,-1)
// ------------------------------------------------------------
int /*stdcall*/ CNMonsterFriendShip__vmt4(int nArg1)  // 函数: FriendShip 好感交互触发：取双 word 参数→RTCast 到 IRDActiveObject→设为追踪目标→4DB200(23,-1)
{
  int result; // eax
  uint32_t *v2; // eax
  int v3; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // [esp-1Ch] [ebp-28h]
  int v7; // [esp-18h] [ebp-24h]
  uint16_t v8; // [esp+4h] [ebp-8h] BYREF
  uint16_t v9; // [esp+8h] [ebp-4h] BYREF

  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v8);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v9);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 1108))(nArg1);  // 调用虚函数（虚表槽 +1108）
  if ( (uint8_t)result == 0 )  // 若 (uint8_t)result == 0
  {
    v7 = v9;
    v6 = v8;
    v2 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 80))(nArg1);  // 调用虚函数（虚表槽 +80）
    v3 = sub_45EBE0(v2, v6, v7);  // 调 sub_45EBE0
    result = __RTDynamicCast(v3, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    v4 = result;
    if ( result != 0 )  // 若 result != 0
    {
      v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 1032))(nArg1) + 20);  // 调用虚函数（虚表槽 +1032）
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg1 + 1148))(nArg1, v4);  // 调用虚函数（虚表槽 +1148）
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 1132))(nArg1);  // 调用虚函数（虚表槽 +1132）
      if ( v5 != *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 1032))(nArg1) + 20) )  // 调用虚函数（虚表槽 +1032）
        sub_4D84F0(0, 0);
      return sub_4DB200(23, -1);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58B6C0 CNZealotFriendShip__vmt8 —— RTTI 判定目标是否 CNZealot（狂信者）
// ------------------------------------------------------------
bool /*stdcall*/ CNZealotFriendShip__vmt8(int nArg1)  // 函数: RTTI 判定目标是否 CNZealot（狂信者）
{
  return __RTDynamicCast(nArg1, 0, &IRDMonster `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0) != 0;  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
}



// ------------------------------------------------------------
// 0x58B6F0 CNStarFishFriendShip__vmt8 —— RTTI 判定目标是否 CNStarFish（海星怪）
// ------------------------------------------------------------
bool /*stdcall*/ CNStarFishFriendShip__vmt8(int nArg1)  // 函数: RTTI 判定目标是否 CNStarFish（海星怪）
{
  return __RTDynamicCast(nArg1, 0, &IRDMonster `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0) != 0;  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
}



// ------------------------------------------------------------
// 0x58B720 CNTauFriendShip__vmt8 —— 判定 +332..+336 列表中是否含怪物族代码 20（Tau 牛头怪族）
// ------------------------------------------------------------
bool /*stdcall*/ CNTauFriendShip__vmt8(int pArg1)  // 函数: 判定 +332..+336 列表中是否含怪物族代码 20（Tau 牛头怪族）
{
  uint32_t *v1; // ecx
  uint32_t *v2; // eax
  bool v3; // zf

  v1 = *(uint32_t **)(pArg1 + 336);
  v2 = *(uint32_t **)(pArg1 + 332);
  v3 = v2 == v1;
  if ( v2 != v1 )  // 若 v2 != v1
  {
    do
    {
      if ( *v2 == 20 )  // 若 *v2 == 20
        break;
      ++v2;  // 自增v2
    }
    while ( v2 != v1 );  // 当 v2 != v1 循环
    v3 = v2 == v1;
  }
  return !v3;
}



// ============================================================
// 【分区 5】食尸鬼族怪物 AI（0x58B750-0x58E550）
// 覆写槽语义（IRDMonster 基链）：vmt0=标量删除析构；vmt200=命中主处理器
// （尾调 IRDMonster__vmt200，前置 10% 概率 vt+580 反击吼叫 48003）；
// vmt444=AI 决策周期（+1787 状态 switch→vt+1104 切状态 4/5/13/14/15）；
// vmt4A8=投掷物发射（ThrowerSkull.ptl/MorganSkullBomb.ptl）；
// vmt1D8=AI 主状态机；vmt14C=移动/受击表现；vmt520/524/528/52C/51C=技能/
// 掉落/对话槽；vmt12C=受击属性。Olrek 卖油商（RedOilFlask.ptl/RedRock.ptl）、
// MagmaGhoul 熔岩食尸鬼、NoMercy 无慈悲（GHOUL_ARM_ATK）、
// ThrowNoMercyGrabEnemy=无慈悲抓投敌人载体（vmt10 抓取/vmt1C 落地）。
// ============================================================
// ------------------------------------------------------------
// 0x58B750 CNMonsterFriendShip__vmt0 —— CNMonsterFriendShip 标量删除析构（4049C0=成员清理）
// ------------------------------------------------------------
void /*userpurge*/ sub_58B750(int nArg1@<ecx>, int nArg2@<edi>, uint32_t *pArg3, int nArg4)  // 【CNMonsterFriendShip__vmt0】
{
  int v5; // edi
  int v6; // edi
  uint32_t *v7; // ebx
  int v8; // eax
  int v9; // edi
  int v10; // edi
  uint32_t *v11; // ebx
  int v12; // eax
  uint64_t v13; // rax
  unsigned int v14; // ebx
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // edx
  int pObj; // ecx
  int v22; // eax
  int v23; // edx
  uint32_t *v24; // edi
  int v25; // ebx
  int v26; // ebx
  int v27; // eax
  int v28; // ebx
  int v29; // eax
  int pObj2; // eax
  int v31; // edi
  int v32; // eax
  int v33; // ebx
  int v34; // eax
  int v35; // ebx
  int v36; // eax
  int v38; // [esp+0h] [ebp-10h]
  int pObj3; // [esp+4h] [ebp-Ch]
  int v40; // [esp+8h] [ebp-8h]
  int v42; // [esp+18h] [ebp+8h]
  unsigned int v43; // [esp+1Ch] [ebp+Ch]

  if ( nArg4 != 0 )  // 若 nArg4 != 0
  {
    pObj3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 576))(nArg4);  // 调用虚函数（虚表槽 +576）
    if ( pObj3 != 0 )  // 若 pObj3 != 0
    {
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 1032))(pArg3);  // 调用虚函数（虚表槽 +1032）
      v6 = *(uint32_t *)(v5 + 52) - *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 1032))(pArg3) + 48);  // 调用虚函数（虚表槽 +1032）
      v7 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 672))(pArg3, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 1032))(pArg3);  // 调用虚函数（虚表槽 +1032）
      v40 = (uint64_t)sub_4049C0(800.0, 1200.0, *v7 - *(uint32_t *)(v8 + 48), v6);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 1032))(pArg3);  // 调用虚函数（虚表槽 +1032）
      v10 = *(uint32_t *)(v9 + 52) - *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 1032))(pArg3) + 48);  // 调用虚函数（虚表槽 +1032）
      v11 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 672))(pArg3, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 1032))(pArg3);  // 调用虚函数（虚表槽 +1032）
      v13 = (uint64_t)sub_4049C0(4.0, 8.0, *v11 - *(uint32_t *)(v12 + 48), v10);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v14 = 0;
      v38 = v13;
      v42 = 0;
      while ( 1 )  // 无限循环
      {
        v43 = v14;
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 80))(pArg3);  // 调用虚函数（虚表槽 +80）
        v16 = *(uint32_t *)(v15 + 8);  // v16 = v15+8
        v17 = v15 + 4;
        v18 = v16 != 0 ? (*(uint32_t *)(v17 + 8) - v16) >> 2 : 0;
        if ( (int)v14 >= v18 )  // 若 (int)v14 >= v18
          break;
        v19 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 80))(pArg3, nArg2);  // 调用虚函数（虚表槽 +80）
        v20 = *(uint32_t *)(v19 + 8);  // v20 = v19+8
        if ( v20 != 0 && v14 < (*(uint32_t *)(v19 + 12) - v20) >> 2 )  // 若 v20 != 0 && v14 < (*(uint32_t *)(v19 + 12) - v20) >> 2
          pObj = *(uint32_t *)(v20 + 4 * v14);
        else
          pObj = 0;
        nArg2 = 529;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 40))(pObj) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
        {
          v22 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 80))(pArg3);  // 调用虚函数（虚表槽 +80）
          v23 = *(uint32_t *)(v22 + 8);  // v23 = v22+8
          if ( v23 != 0 && v14 < (*(uint32_t *)(v22 + 12) - v23) >> 2 )  // 若 v23 != 0 && v14 < (*(uint32_t *)(v22 + 12) - v23) >> 2
            v24 = *(uint32_t **)(v23 + 4 * v14);
          else
            v24 = nullptr;  // v24 = nullptr 空指针
          if ( v24[1943] != 3 )  // 若 v24[1943] != 3
          {
            v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 376))(pArg3);  // 调用虚函数（虚表槽 +376）
            if ( v25 == (*(int (/*thiscall*/ **)(uint32_t *))(*v24 + 376))(v24)  // 调用虚函数（虚表槽 +376）
              && pArg3 != v24
              && (*(uint8_t (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)nArg1 + 8))(nArg1, v24) != 0  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
              && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t))(*pArg3 + 8))(pArg3, v24, 0) <= v40  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
              && (*(int (/*thiscall*/ **)(uint32_t *))(*v24 + 304))(v24) != 0 )  // 调用虚函数（虚表槽 +304）
            {
              (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
              v26 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
              v27 = (*(int (/*thiscall*/ **)(uint32_t *))(*v24 + 48))(v24);  // 调用虚函数（虚表槽 +48）
              (*(void (/*thiscall*/ **)(int, int))(v26 + 36))(dword_8F8520, v27);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
              v28 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
              v29 = (*(int (/*thiscall*/ **)(uint32_t *))(*v24 + 52))(v24);  // 调用虚函数（虚表槽 +52）
              (*(void (/*thiscall*/ **)(int, int))(v28 + 36))(dword_8F8520, v29);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
              pObj2 = (*(int (/*thiscall*/ **)(uint32_t *))(*v24 + 304))(v24);  // 调用虚函数（虚表槽 +304）
              v31 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
              v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);  // 调用虚函数（虚表槽 +52）
              (*(void (/*thiscall*/ **)(int, int))(v31 + 36))(dword_8F8520, v32);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 14);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
              v33 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
              v34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 48))(pObj3);  // 调用虚函数（虚表槽 +48）
              (*(void (/*thiscall*/ **)(int, int))(v33 + 36))(dword_8F8520, v34);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
              v35 = *(uint32_t *)dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
              v36 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 52))(pObj3);  // 调用虚函数（虚表槽 +52）
              (*(void (/*thiscall*/ **)(int, int))(v35 + 36))(dword_8F8520, v36);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
              (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
              if ( ++v42 > v38 )  // 若 ++v42 > v38
                return;
            }
            v14 = v43;
          }
        }
        ++v14;  // 自增v14
      }
    }
  }
}


// ------------------------------------------------------------
// 0x58BA00 sub_58BA00 —— 食尸鬼部件参数初始化：+1698..+1702 状态组（1/1/3/4/4）、+2152..54=-1、+4185 起 26×50
// ------------------------------------------------------------
uint16_t */*thiscall*/ sub_58BA00(uint32_t *this)  // 函数: 食尸鬼部件参数初始化：+1698..+1702 状态组（1/1/3/4/4）、+2152..54=-1、+4185 起 26…
{
  uint16_t *result; // eax
  int i; // ecx

  *(this + 1698) = 1;  // this+6792 = 炮车/子类参数面槽 1
  *(this + 1699) = 1;  // this+6796 = 炮车/子类参数面槽 2
  *(this + 1700) = 3;  // this+6800 = 炮车/子类参数面槽 3
  *(this + 1701) = 4;  // this+6804 = 炮车/子类参数面槽 4
  *(this + 1702) = 4;  // this+6808 = 炮车/子类参数面槽 5
  *(this + 2152) = -1;  // this+8608 = uAI8608
  *(this + 2153) = -1;  // this+8612 = uAI8612
  *(this + 2154) = -1;  // this+8616 = uAI8616
  result = (uint16_t *)this + 4185;
  for ( i = 26; i != 0; --i )  // 循环：i = 26; i != 0; --i
  {
    *result = 50;  // *result 写入 50
    result += 2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x58BA60 CNGhoul__vmt200 —— CNGhoul 命中处理器：受击者状态 17 且 10% 概率→vt+580 播 48003 吼叫（±30 随机）→尾调 IRDMonster__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNGhoul__vmt200(int *this, int nArg2, int nArg3, int nArg4)  // 函数: CNGhoul 命中处理器：受击者状态 17 且 10% 概率→vt+580 播 48003 吼叫（±30 随机）→尾调 IRDMonster__vmt200
{
  int v5; // edi
  int v6; // edi
  int v7; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 1 && rand() % 100 < 10 )  // 调 以 16 位种子状态递推并返回 15 位结果
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 152))(nArg2);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == v5  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    {
      v6 = *this;
      v7 = (*(int (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
             this,
             0,
             30,
             4,
             0,
             0,
             0);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, int))(v6 + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
        this,
        48003,
        10,
        0,
        0,
        v7 != 1 ? -30 : 30);
    }
  }
  return IRDMonster__vmt200(nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x58BB00 CNGhoul__vmt444 —— CNGhoul AI 决策周期：+8600==1 时按 +1787 状态 switch→vt+1104 切换状态 4/5/13（10% 概率）
// ------------------------------------------------------------
void /*thiscall*/ CNGhoul__vmt444(uint32_t *this)  // 函数: CNGhoul AI 决策周期：+8600==1 时按 +1787 状态 switch→vt+1104 切换状态 4/5/13（10% 概率）
{
  uint32_t *pThis; // ecx

  if ( *((uint8_t *)this + 8600) == 1 )  // this+8600 = uAI8600
  {
    IRDMonster__vmt444();
    switch ( *(this + 1787) )  // this+7148 = nBigState
    {
      case 0:
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);  // 调用虚函数（虚表槽 +1284）
        break;
      case 4:
        pThis = this;
        if ( *(this + 1813) == 0 )  // this+7252 = pTarget7252
          goto LABEL_5;  // 跳转 LABEL_5
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && rand() % 100 < 10 )  // 调 以 16 位种子状态递推并返回 15 位结果
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);  // 调用虚函数（虚表槽 +1104）
        break;
      case 5:
        pThis = this;
        if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && rand() % 100 < 10 )  // 调 以 16 位种子状态递推并返回 15 位结果
            goto LABEL_14;  // 跳转 LABEL_14
        }
        else
        {
LABEL_5:
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(pThis, 13);  // 调用虚函数（虚表槽 +1104）
        }
        break;
      case 0xD:  // case 13
      case 0xE:  // case 14
      case 0xF:  // case 15
        if ( *(this + 1813) != 0 )  // this+7252 = pTarget7252
LABEL_14:
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 调用虚函数（虚表槽 +1104）
        break;
      default:
        return;
    }
  }
}



// ------------------------------------------------------------
// 0x58BC10 CNGhoul__vmt520 —— CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施法与目标链）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoul__vmt520(int *this)  // 函数: CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施法与目标链）
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // edx

  result = *(this + 2151);  // this+8604 = bAI8604
  if ( result == 0 )  // 若 result == 0
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 144))(this);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
    v3 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 200))(this, 0);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    sub_493400(v3, 1);  // 调 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    sub_4939E0(v4, 1);  // 调 播放/暂停级联（递归子链 +204）
    result = sub_4E7F30(this, 200, 200, 0);  // 调 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
    if ( result != 0 )  // 若 result != 0
    {
      v5 = *this;
      *(this + 2151) = 1;  // this+8604 = bAI8604
      v6 = (*(int (/*thiscall*/ **)(int *))(v5 + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      sub_4926A0(v6);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      sub_4939E0(v7, 0);  // 调 播放/暂停级联（递归子链 +204）
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1316))(this);  // 调用虚函数（虚表槽 +1316）
    }
  }
  if ( *(this + 2151) == 1 )  // this+8604 = bAI8604
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    if ( *(uint8_t *)(result + 170) == 1 )  // 若 *(uint8_t *)(result + 170) == 1
    {
      v8 = *this;
      *(this + 1639) = 0;  // this+6556 = 主状态镜像
      *((uint8_t *)this + 8600) = 1;  // this+8600 = uAI8600
      *(this + 2151) = -1;  // this+8604 = bAI8604
      (*(void (/*thiscall*/ **)(int *))(v8 + 1320))(this);  // 调用虚函数（虚表槽 +1320）
      sub_4926A0(*(this + 1540));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1540));  // 调用虚函数（虚表槽 +196）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58BD00 CNGhoul__vmt14C —— CNGhoul 移动/受击表现槽 vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNGhoul__vmt14C(uint32_t *this)  // 函数: CNGhoul 移动/受击表现槽 vmt14C
{
  int fld_e2152; // eax
  uint32_t *pThis_868; // ebx
  int i; // edi

  if ( *((uint8_t *)this + 8600) == 0 )  // this+8600 = uAI8600
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1312))(this);  // 调用虚函数（虚表槽 +1312）
    fld_e2152 = *(this + 2152);  // this+8608 = uAI8608
    pThis_868 = this + 2152;
    if ( fld_e2152 == -1 && *(this + 2153) == -1 && *(this + 2154) == -1 )  // this+8612 = uAI8612
    {
      for ( i = 0; i < 3; ++i )  // 循环：i = 0; i < 3; ++i
        *pThis_868++ = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 116))(this, i);  // 调用虚函数（虚表槽 +116）
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*this + 108))(this, fld_e2152, *(this + 2153), *(this + 2154));  // this+8612 = uAI8612
    }
  }
  return IRDMonster__vmt14C(this);
}



// ------------------------------------------------------------
// 0x58BD80 CNGhoul__vmt1D8 —— CNGhoul 周期状态槽 vmt1D8（14 行轻量实现）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoul__vmt1D8(uint8_t *this, char pszArg2, float fArg3, int nArg4, int nArg5)  // 函数: CNGhoul 周期状态槽 vmt1D8（14 行轻量实现）
{
  int result; // eax

  if ( *(this + 8600) == 1 )  // 若 *(this + 8600) == 1
    return IRDMonster__vmt1D8(pszArg2, fArg3, nArg4, nArg5);
  return result;
}



// ------------------------------------------------------------
// 0x58BDA0 CNGhoulThrower__vmt4A8 —— CNGhoulThrower 技能槽 vmt4A8（16 行）——投掷头骨入口
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulThrower__vmt4A8(uint32_t *this)  // 函数: CNGhoulThrower 技能槽 vmt4A8（16 行）——投掷头骨入口
{
  *(this + 2155) = 1;  // this+8620 = uAI8620
  *(this + 1698) = 1;  // this+6792 = 炮车/子类参数面槽 1
  *(this + 1699) = 1;  // this+6796 = 炮车/子类参数面槽 2
  *(this + 1700) = 3;  // this+6800 = 炮车/子类参数面槽 3
  *(this + 1701) = 4;  // this+6804 = 炮车/子类参数面槽 4
  *(this + 1702) = 4;  // this+6808 = 炮车/子类参数面槽 5
  return 4;
}



// ------------------------------------------------------------
// 0x58BDE0 sub_58BDE0 —— 发射投掷物 GhoulThrowerSkull.ptl（423A20=投掷物生成，按 this 参数定弹道）
// ------------------------------------------------------------
int /*thiscall*/ sub_58BDE0(int *this)  // 函数: 发射投掷物 GhoulThrowerSkull.ptl（423A20=投掷物生成，按 this 参数定弹道）
{
  int result; // eax
  uint64_t v3; // rax
  int v4; // esi
  uint64_t fld_e1813; // rax
  int fld_e18132; // eax
  int v7; // edx
  int fld_e18133; // eax
  int v9; // edx
  int fld_e18134; // eax
  int v11; // eax
  int v12; // edx
  uint32_t v13[26]; // [esp+8h] [ebp-68h] BYREF

  v13[25] = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  sub_423A20((int)v13);  // 调 小结构初始化（0-100 刻度）
  result = *(this + 1813);  // this+7252 = pTarget7252
  if ( result != 0 )  // 若 result != 0
  {
    result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1244))(this, *(this + 1813));  // this+7252 = pTarget7252
    if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
    {
      qmemcpy(  // 调 内存块拷贝(内联展开)
        v13,
        (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/GhoulThrowerSkull.ptl"),  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
        0x62u);
      v3 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v13[7] + 3)) / (double)v13[17] * 1000.0);
      v4 = 2 * v3;
      fld_e1813 = (uint64_t)((double (/*fastcall*/ *)(int *, uint32_t, uint32_t, uint32_t))*(uint32_t *)(*this + 164))(  // 调用虚函数（虚表槽 +164）【推断: ★ 与目标朝向角度（atan2 角度制；3D 俯视判定）】
                               this,
                               HIDWORD(v3),  // 调 取 64 位值高 32 位
                               *(this + 1813),  // this+7252 = pTarget7252
                               0);
      HIDWORD(fld_e1813) = *this;  // 调 取 64 位值高 32 位
      v13[18] = fld_e1813;
      fld_e18132 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(HIDWORD(fld_e1813) + 8))(this, *(this + 1813), 0);  // this+7252 = pTarget7252
      v7 = *this;
      *(uint32_t *)((char *)&v13[3] + 3) = 1000 * fld_e18132 / v4;
      fld_e18133 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v7 + 8))(this, *(this + 1813), 0);  // this+7252 = pTarget7252
      v9 = *this;
      *(uint32_t *)((char *)&v13[4] + 3) = 1000 * fld_e18133 / v4;
      fld_e18134 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v9 + 8))(this, *(this + 1813), 0);  // this+7252 = pTarget7252
      if ( fld_e18134 >= 100 )  // 若 fld_e18134 >= 100
        v11 = fld_e18134 >= 200 ? 300 : 200;
      else
        v11 = 100;
      v12 = *this;
      *(uint32_t *)((char *)&v13[7] + 3) = v11;
      result = (*(int (/*thiscall*/ **)(int *))(v12 + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
        return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
                 this,
                 30089,
                 0,
                 v13,
                 0,
                 20,
                 0,
                 40,
                 1,
                 0,
                 0,
                 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58BF30 CNGhoulMorgan__vmt4A8 —— CNGhoulMorgan 技能槽 vmt4A8（10 行转发）
// ------------------------------------------------------------
void /*thiscall*/ CNGhoulMorgan__vmt4A8(uint32_t *this)  // 函数: CNGhoulMorgan 技能槽 vmt4A8（10 行转发）
{
  *(this + 2155) = 1;  // this+8620 = uAI8620
}



// ------------------------------------------------------------
// 0x58BF40 sub_58BF40 —— 发射投掷物 GhoulMorganSkullBomb.ptl（ Morgan 头颅炸弹弹道）
// ------------------------------------------------------------
int /*thiscall*/ sub_58BF40(int *this)  // 函数: 发射投掷物 GhoulMorganSkullBomb.ptl（ Morgan 头颅炸弹弹道）
{
  int result; // eax
  uint64_t v3; // rax
  int v4; // esi
  uint64_t fld_e1813; // rax
  int fld_e18132; // eax
  int v7; // edx
  int fld_e18133; // eax
  int v9; // edx
  int fld_e18134; // eax
  int v11; // eax
  int v12; // edx
  uint32_t v13[26]; // [esp+8h] [ebp-68h] BYREF

  v13[25] = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  sub_423A20((int)v13);  // 调 小结构初始化（0-100 刻度）
  result = *(this + 1813);  // this+7252 = pTarget7252
  if ( result != 0 )  // 若 result != 0
  {
    result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1244))(this, *(this + 1813));  // this+7252 = pTarget7252
    if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
    {
      qmemcpy(  // 调 内存块拷贝(内联展开)
        v13,
        (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
                        this,
                        "Particle/GhoulMorganSkullBomb.ptl"),
        0x62u);
      v3 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v13[7] + 3)) / (double)v13[17] * 1000.0);
      v4 = 2 * v3;
      fld_e1813 = (uint64_t)((double (/*fastcall*/ *)(int *, uint32_t, uint32_t, uint32_t))*(uint32_t *)(*this + 164))(  // 调用虚函数（虚表槽 +164）【推断: ★ 与目标朝向角度（atan2 角度制；3D 俯视判定）】
                               this,
                               HIDWORD(v3),  // 调 取 64 位值高 32 位
                               *(this + 1813),  // this+7252 = pTarget7252
                               0);
      HIDWORD(fld_e1813) = *this;  // 调 取 64 位值高 32 位
      v13[18] = fld_e1813;
      fld_e18132 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(HIDWORD(fld_e1813) + 8))(this, *(this + 1813), 0);  // this+7252 = pTarget7252
      v7 = *this;
      *(uint32_t *)((char *)&v13[3] + 3) = 1000 * fld_e18132 / v4;
      fld_e18133 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v7 + 8))(this, *(this + 1813), 0);  // this+7252 = pTarget7252
      v9 = *this;
      *(uint32_t *)((char *)&v13[4] + 3) = 1000 * fld_e18133 / v4;
      fld_e18134 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v9 + 8))(this, *(this + 1813), 0);  // this+7252 = pTarget7252
      if ( fld_e18134 >= 150 )  // 若 fld_e18134 >= 150
        v11 = fld_e18134 >= 300 ? 450 : 300;
      else
        v11 = 150;
      v12 = *this;
      *(uint32_t *)((char *)&v13[7] + 3) = v11;
      result = (*(int (/*thiscall*/ **)(int *))(v12 + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
        return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
                 this,
                 30090,
                 0,
                 v13,
                 0,
                 20,
                 0,
                 40,
                 1,
                 0,
                 0,
                 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58C090 CNGhoulNoMercy__vmt4A8 —— CNGhoulNoMercy 技能槽 vmt4A8（23 行）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulNoMercy__vmt4A8(int this)  // 函数: CNGhoulNoMercy 技能槽 vmt4A8（23 行）
{
  *(uint32_t *)(this + 6792) = 1;  // this+6792 = 1
  *(uint32_t *)(this + 6796) = 1;  // this+6796 = 1
  *(uint32_t *)(this + 6804) = 4;  // this+6804 = 4
  *(uint32_t *)(this + 6808) = 4;  // this+6808 = 4
  *(uint32_t *)(this + 6800) = 3;  // this+6800 = 3
  *(uint32_t *)(this + 8656) = 0;  // this+8656 = 0
  *(uint8_t *)(this + 8620) = 0;  // this+8620 = 0
  *(uint32_t *)(this + 8672) = 0;  // this+8672 = 0
  *(uint32_t *)(this + 8676) = 0;  // this+8676 = 0
  *(uint32_t *)(this + 8680) = 0;  // this+8680 = 0
  *(uint32_t *)(this + 8624) = 0;  // this+8624 = 0
  *(uint8_t *)(this + 8641) = 0;  // this+8641 = 0
  *(uint8_t *)(this + 8642) = 0;  // this+8642 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x58C0F0 CNGhoulNoMercy__vmt12C —— CNGhoulNoMercy 受击属性槽 vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulNoMercy__vmt12C(uint32_t *this, uint32_t *uArg2)  // 函数: CNGhoulNoMercy 受击属性槽 vmt12C
{
  int fld_e2164; // ecx  | +0x21D0 → 子类 AI 相位槽（0x58C090 复位清 0）【推断】（证据: va=0058C090）（CNGhoulNoMercy；va=0058C090）
  int fld_e2169; // ecx  | +0x21E4 → 子类 AI 相位槽（0x58C090 复位清 0）【推断】（证据: va=0058C090）（CNGhoulNoMercy；va=0058C090）

  if ( uArg2 == (uint32_t *)*(this + 2164) )  // this+8656 = 事件 16/17 配对槽
  {
    *(this + 2164) = 0;  // this+8656 = 事件 16/17 配对槽
  }
  else if ( uArg2 == (uint32_t *)*(this + 2169) )  // 否则若 uArg2 == (uint32_t *)*(this + 2169)
  {
    *(this + 2169) = 0;  // this+8676 = 0
  }
  if ( uArg2 == this )  // 若 uArg2 == this
  {
    fld_e2164 = *(this + 2164);  // this+8656 = 事件 16/17 配对槽
    if ( fld_e2164 != 0 )  // 若 fld_e2164 != 0
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)fld_e2164 + 560))(fld_e2164, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 564))(*(this + 2164));  // this+8656 = 事件 16/17 配对槽
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2164) + 604))(*(this + 2164), 1);  // this+8656 = 事件 16/17 配对槽
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t))(*(uint32_t *)*(this + 2164) + 612))(*(this + 2164), 1, 0);  // this+8656 = 事件 16/17 配对槽
    }
    fld_e2169 = *(this + 2169);  // fld_e2169 = this+2169
    if ( fld_e2169 != 0 )  // 若 fld_e2169 != 0
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)fld_e2169 + 560))(fld_e2169, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2169) + 564))(*(this + 2169));  // 调用虚函数（虚表槽 +564）【推断: ★ 位移同步包 vt+234（会话 3 定案：UDP type=…】
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2169) + 604))(*(this + 2169), 1);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t))(*(uint32_t *)*(this + 2169) + 612))(*(this + 2169), 1, 0);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
    }
  }
  return IRDMonster__vmt12C(uArg2);
}



// ------------------------------------------------------------
// 0x58C1D0 sub_58C1D0 —— 抓投敌人姿态/碰撞初始化（4924C0/4918E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58C1D0(int *this, int *pDwArg2, uint32_t *uArg3, int *pDwArg4)  // 函数: 抓投敌人姿态/碰撞初始化（4924C0/4918E0）
{
  int fld_e2164; // eax
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int fld_e21642; // ecx
  int v10; // eax
  int result; // eax
  int fld_e21643; // edi
  int v13; // ebx
  int v14; // ebx
  int v15; // ebx
  int v16; // [esp-4h] [ebp-Ch]

  fld_e2164 = *(this + 2164);  // this+8656 = 事件 16/17 配对槽
  if ( fld_e2164 != 0 && (*(uint8_t (/*stdcall*/ **)(int))(*(uint32_t *)fld_e2164 + 40))(273) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
  {
    __RTDynamicCast(*(this + 2164), 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);  // this+8656 = 事件 16/17 配对槽
    v16 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    v6 = sub_4924C0(0);  // 调 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
    v7 = sub_4918E0(v6, v16) / 2;  // 调 动画盒四边界提取（研究 P29 族）
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    fld_e21642 = *(this + 2164);  // this+8656 = 事件 16/17 配对槽
    if ( v8 == 1 )  // 若 v8 == 1
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21642 + 120))(fld_e21642) - v7;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    else
      v10 = v7 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21642 + 120))(fld_e21642);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    *pDwArg2 = v10;  // *pDwArg2 写入 v10
    *uArg3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 124))(*(this + 2164)) + 1;  // this+8656 = 事件 16/17 配对槽
    result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 128))(*(this + 2164)) + 12;  // this+8656 = 事件 16/17 配对槽
    *pDwArg4 = result;  // *pDwArg4 写入 result
  }
  else
  {
    *pDwArg2 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 120))(*(this + 2164));  // this+8656 = 事件 16/17 配对槽
    *uArg3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 124))(*(this + 2164)) + 1;  // this+8656 = 事件 16/17 配对槽
    fld_e21643 = *(this + 2164);  // this+8656 = 事件 16/17 配对槽
    v13 = (*(int (**)(void))(*(uint32_t *)fld_e21643 + 128))();  // 调用虚函数（虚表槽 +128）
    v14 = v13 - (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);  // 调用虚函数（虚表槽 +192）
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21643 + 192))(fld_e21643) + v14;  // 调用虚函数（虚表槽 +192）
    *pDwArg4 = v15;  // *pDwArg4 写入 v15
    return (int)pDwArg4;
  }
  return result;
}



// ------------------------------------------------------------
// 0x58C300 j_CNGhoul__vmt444 —— j_CNGhoul__vmt444 尾调用桩（jmp CNGhoul__vmt444）
// ------------------------------------------------------------
// attributes: thunk
void /*thiscall*/ j_CNGhoul__vmt444(uint32_t *this)  // 函数: j_CNGhoul__vmt444 尾调用桩（jmp CNGhoul__vmt444）
{
  CNGhoul__vmt444(this);  // 调 CNGhoul AI 决策周期：+8600==1 时按 +1787 状态 switch→vt+1104 切换状态 4/5/13
}



// ------------------------------------------------------------
// 0x58C310 CNThrowNoMercyGrabEnemy__vmt10 —— ThrowNoMercyGrabEnemy 抓取执行：4938F0 目标绑定 + 432E50 播报（101 行抓取流程）
// ------------------------------------------------------------
void /*thiscall*/ CNThrowNoMercyGrabEnemy__vmt10(int **this)  // 函数: ThrowNoMercyGrabEnemy 抓取执行：4938F0 目标绑定 + 432E50 播报（101 行抓取流程）
{
  int fld_e20; // ecx
  int *fld_e1; // esi
  int fld_e202; // eax
  int fld_e2022; // ebx
  int *v6; // eax
  uint32_t *fld_e203; // ecx
  int *v8; // ebx
  int v9; // eax
  int fld_e204; // eax
  char v11; // bl
  int v12; // ebx
  int v13; // eax
  int fld_e25; // eax
  int fld_e24; // eax
  int v16; // eax
  int *v17; // [esp+4h] [ebp-4h]
  int fld_e205; // [esp+4h] [ebp-4h]

  fld_e20 = (int)*(this + 20);  // this+80 = nAuraStage
  if ( fld_e20 != 0 )  // 若 fld_e20 != 0
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e20 + 840))(fld_e20) == 18 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    {
      fld_e1 = *(this + 1);  // this+4 = pHostObj
      if ( (*(int (/*thiscall*/ **)(int *))(*fld_e1 + 840))(fld_e1) == 9 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      {
        fld_e202 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 20) + 200))(*(this + 20));  // this+80 = nAuraStage
        fld_e2022 = fld_e202;
        if ( fld_e202 != 0 )  // 若 fld_e202 != 0
        {
          sub_4938F0(fld_e202);  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
          v6 = *(int **)(fld_e2022 + 148);
          fld_e203 = *(this + 20);  // this+80 = nAuraStage
          v8 = (int *)fld_e203[2168];
          v17 = v6;
          if ( v8 != *(this + 21) || v6 != *(this + 22) )  // this+84 = pFxObjA
          {
            if ( v8 != nullptr )  // 若 v8 非空
            {
              *(this + 23) = nullptr;  // this+92 = pFxObjC
              *(this + 24) = (int *)1;  // this+96 = (int *)1
              if ( 93 - (*(int (/*thiscall*/ **)(int *))(*fld_e1 + 192))(fld_e1) / 2 >= 40 )  // 调用虚函数（虚表槽 +192）
                v9 = 40;
              else
                v9 = 93 - (*(int (/*thiscall*/ **)(int *))(*fld_e1 + 192))(fld_e1) / 2;  // 调用虚函数（虚表槽 +192）
              *(this + 25) = (int *)v9;  // this+100 = (int *)v9
            }
            else
            {
              *(this + 23) = (int *)((*(int (/*thiscall*/ **)(uint32_t *))(*fld_e203 + 152))(fld_e203) != 0 ? 60 : -60);  // this+92 = pFxObjC
              *(this + 24) = (int *)-1;  // this+96 = (int *)-1
              if ( 65 - (*(int (/*thiscall*/ **)(int *))(*fld_e1 + 192))(fld_e1) <= 0 )  // 调用虚函数（虚表槽 +192）
                *(this + 25) = nullptr;  // this+100 = nullptr
              else
                *(this + 25) = (int *)(65 - (*(int (/*thiscall*/ **)(int *))(*fld_e1 + 192))(fld_e1));  // 调用虚函数（虚表槽 +192）
            }
            if ( v17 != nullptr )  // 若 v17 非空
            {
              if ( v17 == (int *)1 )  // 若 v17 == (int *)1
                *(this + 23) = (int *)40;  // this+92 = pFxObjC
            }
            else
            {
              *(this + 23) = (int *)30;  // this+92 = pFxObjC
            }
            *(this + 21) = v8;  // this+84 = pFxObjA
            *(this + 22) = v17;  // this+88 = pFxObjB
          }
          fld_e204 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 20) + 152))(*(this + 20));  // this+80 = nAuraStage
          v11 = sub_432E50(fld_e204);  // 调 关系码对调映射
          *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*fld_e1 + 60))(fld_e1) + 52) = v11;  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
          v12 = *fld_e1;
          fld_e205 = (int)*(this + 20);  // this+80 = nAuraStage
          v13 = (*(int (**)(void))(*(uint32_t *)fld_e205 + 128))();  // 调用虚函数（虚表槽 +128）
          fld_e25 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e205 + 124))(fld_e205, (int)*(this + 25) + v13);  // 调用虚函数（虚表槽 +124）
          fld_e24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e205 + 120))(fld_e205, (int)*(this + 24) + fld_e25);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          (*(void (/*thiscall*/ **)(int *, int))(v12 + 112))(fld_e1, (int)*(this + 23) + fld_e24);  // this+92 = pFxObjC
          (*(void (/*thiscall*/ **)(int *, int, int))(*fld_e1 + 612))(fld_e1, 1, 1);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*fld_e1 + 820))(fld_e1, 0);  // 调用虚函数（虚表槽 +820）【推断: [RTTI: IRDActiveObject__vmt334 ·…】
          if ( (*(int (/*thiscall*/ **)(int *))(*fld_e1 + 200))(fld_e1) != 0 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          {
            v16 = (*(int (/*thiscall*/ **)(int *))(*fld_e1 + 200))(fld_e1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
            sub_4938F0(v16);  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
          }
        }
      }
    }
    else
    {
      *(this + 20) = nullptr;  // this+80 = nAuraStage
    }
  }
}



// ------------------------------------------------------------
// 0x58C4E0 CNThrowNoMercyGrabEnemy__vmt1C —— ThrowNoMercyGrabEnemy 落地/释放槽 vmt1C
// ------------------------------------------------------------
int /*thiscall*/ CNThrowNoMercyGrabEnemy__vmt1C(uint32_t *this)  // 函数: ThrowNoMercyGrabEnemy 落地/释放槽 vmt1C
{
  int fld_e1; // ecx
  int result; // eax

  fld_e1 = *(this + 1);  // this+4 = pHostObj
  *(this + 21) = -1;  // this+84 = pFxObjA
  *(this + 22) = -1;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 25) = 0;  // this+100 = 0
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1 + 776))(fld_e1, 3);  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 556))(*(this + 1), 0);  // this+4 = pHostObj
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 768))(*(this + 1), 3, 0, 0);  // this+4 = pHostObj
    return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 556))(*(this + 1), 1);  // this+4 = pHostObj
  }
  return result;
}



// ------------------------------------------------------------
// 0x58C540 CNGhoulOilSellerOlrek__vmt444 —— CNGhoulOilSellerOlrek 技能槽 vmt444（转发 4DB200 播报）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulOilSellerOlrek__vmt444(uint32_t *this)  // 函数: CNGhoulOilSellerOlrek 技能槽 vmt444（转发 4DB200 播报）
{
  int nRand; // eax
  int result; // eax
  int v3; // et2

  CNGhoul__vmt444(this);  // 调 CNGhoul AI 决策周期：+8600==1 时按 +1787 状态 switch→vt+1104 切换状态 4/5/13
  nRand = rand();  // 调 以 16 位种子状态递推并返回 15 位结果
  v3 = nRand % 100;
  result = nRand / 100;
  if ( v3 < 2 )  // 若 v3 < 2
    return sub_4DB200(24, 0);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
  return result;
}



// ------------------------------------------------------------
// 0x58C570 CNGhoulOilSellerOlrek__vmt52C —— Olrek 卖油摊位交互：加载 RedRock.ptl/RedOilFlask.ptl（41A5E0 粒子挂载）
// ------------------------------------------------------------
int /*usercall*/ CNGhoulOilSellerOlrek__vmt52C@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>)  // 函数: Olrek 卖油摊位交互：加载 RedRock.ptl/RedOilFlask.ptl（41A5E0 粒子挂载）
{
  int result; // eax
  uint16_t *v5; // eax
  uint16_t *v6; // eax
  int v7; // edx
  uint32_t pBuf[24]; // [esp+8h] [ebp-68h] BYREF
  int16_t v9; // [esp+68h] [ebp-8h]
  int dword_796E502; // [esp+6Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    if ( result == 8 )  // 若 result == 8
    {
      if ( sub_41A5E0((unsigned int)(pArg1 + 1757)) == 0  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        && *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 148) >= 3  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        && pArg1[2155] == 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int))(*pArg1 + 384))(pArg1, 0, nArg2, nArg3);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        v5 = (uint16_t *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*pArg1 + 588))(  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
                        pArg1,
                        "../../PassiveObject/Monster/Magma/Particle/RedRock.ptl");
        qmemcpy(pBuf, v5, sizeof(pBuf));  // 调 内存块拷贝(内联展开)
        pBuf[1] = 0;
        pBuf[0] = 20;
        v9 = v5[48];
LABEL_11:
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 580))(pArg1);  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
        pArg1[2155] = 1;
        return result;
      }
      result = sub_41A5E0((unsigned int)(pArg1 + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result == 1 )  // 若 result == 1
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        if ( *(int *)(result + 148) >= 3 )  // 若 *(int *)(result + 148) >= 3
        {
          result = pArg1[2155];
          if ( result == 0 )  // 若 result == 0
          {
            v6 = (uint16_t *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int, int))(*pArg1 + 588))(  // 调用虚函数（虚表槽 +588）【推断: 路径/名称拼接（%s%s，左 = ·this+364 内联 st…】
                            pArg1,
                            "../../PassiveObject/Monster/Magma/Particle/RedOilFlask.ptl",
                            nArg2,
                            nArg3);
            v7 = *pArg1;
            qmemcpy(pBuf, v6, sizeof(pBuf));  // 调 内存块拷贝(内联展开)
            pBuf[6] = 1;
            v9 = v6[48];
            (*(void (/*thiscall*/ **)(uint32_t *, int))(v7 + 384))(pArg1, 1);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
            memset(&pBuf[4], 0, 12);  // 调 内存按字节填充
            pBuf[3] = 4;
            pBuf[2] = 50;
            pBuf[1] = 0;
            pBuf[0] = 20;
            goto LABEL_11;  // 跳转 LABEL_11
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58C6B0 CNMagmaGhoul__vmt4A8 —— CNMagmaGhoul 技能槽 vmt4A8（698F90 参数串清空后转发）
// ------------------------------------------------------------
char /*thiscall*/ CNMagmaGhoul__vmt4A8(uint8_t *this)  // 函数: CNMagmaGhoul 技能槽 vmt4A8（698F90 参数串清空后转发）
{
  int v2; // eax
  int v3; // eax

  v2 = *(uint32_t *)this;  // v2 = this
  *(this + 8656) = 0;  // this+34624 = 0
  v3 = (*(int (**)(void))(v2 + 52))();  // 调用虚函数（虚表槽 +52）
  *((uint32_t *)this + 2156) = v3;  // this+8624 = uAI8624
  *((uint32_t *)this + 2155) = v3;  // this+8620 = uAI8620
  *(this + 8641) = 0;  // this+34564 = 0
  *(this + 8642) = 0;  // this+34568 = 0
  return sub_698F90((int)(this + 8628), 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x58C6F0 CNMagmaGhoul__vmt200 —— CNMagmaGhoul 命中处理器 vmt200（转发 4DB130）
// ------------------------------------------------------------
int /*stdcall*/ CNMagmaGhoul__vmt200(int nArg1, int nArg2, int nArg3)  // 函数: CNMagmaGhoul 命中处理器 vmt200（转发 4DB130）
{
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 348))(nArg1) + 20) == 0 )  // 调用虚函数（虚表槽 +348）
    sub_4DB130(24, 2);  // 调 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
  return IRDMonster__vmt200(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x58C730 CNMagmaGhoul__vmt1D8 —— CNMagmaGhoul 周期状态槽 vmt1D8（转发 4DB200）
// ------------------------------------------------------------
void /*thiscall*/ CNMagmaGhoul__vmt1D8(uint8_t *this, char ArgList, float fArg3, int nArg4, int nArg5)  // 函数: CNMagmaGhoul 周期状态槽 vmt1D8（转发 4DB200）
{
  int nRand; // eax

  if ( *(this + 8600) == 1 )  // 若 *(this + 8600) == 1
  {
    nRand = rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
    sub_4DB200(24, nRand == 0);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
    IRDMonster__vmt1D8(ArgList, fArg3, nArg4, nArg5);
  }
}



// ------------------------------------------------------------
// 0x58C780 sub_58C780 —— NoMercy 状态辅助（4B1030 目标查询）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_58C780(uint32_t *this, int nArg2)  // 函数: NoMercy 状态辅助（4B1030 目标查询）
{
  sub_4B1030(this);  // 调 IRDAppendage 基类构造
  *(this + 21) = -1;  // this+84 = pFxObjA
  *(this + 22) = -1;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 25) = 0;  // this+100 = 0
  *((uint8_t *)this + 40) = 0;  // this+40 = 状态子标志
  *this = &vftbl_CNThrowNoMercyGrabEnemy;  // *this 写入 &vftbl_CNThrowNoMercyGrabEnemy
  *(this + 20) = nArg2;  // this+80 = nAuraStage
  return this;
}



// ------------------------------------------------------------
// 0x58C7C0 CNThrowNoMercyGrabEnemy__vmt0 —— ThrowNoMercyGrabEnemy 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNThrowNoMercyGrabEnemy__vmt0(void *Block, char pszArg2)
{
  sub_58C7F0();  // 调 析构成员清理（5F6640 投掷物/粒子释放）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x58C7F0 sub_58C7F0 —— 析构成员清理（5F6640 投掷物/粒子释放）
// ------------------------------------------------------------
int /*thiscall*/ sub_58C7F0(int this)  // 函数: 析构成员清理（5F6640 投掷物/粒子释放）
{
  int result; // eax

  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);  // 调 sub_5F6640
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;  // this+8 = &vftbl_nengine__IObject
  *(uint8_t *)(this + 12) = 0;  // this+12 = 0
  return result;
}



// ------------------------------------------------------------
// 0x58C840 sub_58C840 —— NoMercy 抓取发起（45EBE0 对象查找 + 58C1D0 姿态初始化，79 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_58C840(int this, int nArg2, int pArg3)  // 函数: NoMercy 抓取发起（45EBE0 对象查找 + 58C1D0 姿态初始化，79 行）
{
  int fld_74; // eax
  int pObj; // edi
  int fld_21D0; // ecx
  int v7; // eax
  int fld_21D02; // ecx
  int v9; // eax
  int fld_21D03; // ecx
  int fld_21D4; // edi
  int fld_21D8; // ebx
  int v14; // [esp+Ch] [ebp-Ch] BYREF
  int v15; // [esp+10h] [ebp-8h] BYREF
  int v16; // [esp+14h] [ebp-4h] BYREF

  fld_74 = sub_45EBE0(*(uint32_t **)(this + 116), **(uint32_t **)(pArg3 + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4));  // 调 sub_45EBE0
  pObj = fld_74;
  if ( fld_74 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_74 + 40))(fld_74, 17) == 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    || (*(uint32_t *)(this + 8656) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )  // 调用虚函数（虚表槽 +128）
  {
    *(uint32_t *)(this + 8656) = 0;  // this+8656 = 0
  }
  fld_21D0 = *(uint32_t *)(this + 8656);  // fld_21D0 = this+8656
  if ( fld_21D0 != 0 )  // 若 fld_21D0 != 0
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_21D0 + 120))(fld_21D0);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    fld_21D02 = *(uint32_t *)(this + 8656);  // fld_21D02 = this+8656
    *(uint32_t *)(this + 8660) = v7;  // this+8660 = v7
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_21D02 + 124))(fld_21D02);  // 调用虚函数（虚表槽 +124）
    fld_21D03 = *(uint32_t *)(this + 8656);  // fld_21D03 = this+8656
    *(uint32_t *)(this + 8664) = v9;  // this+8664 = v9
    *(uint32_t *)(this + 8668) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_21D03 + 128))(fld_21D03);  // 调用虚函数（虚表槽 +128）
    sub_58C1D0((int *)this, &v14, &v15, &v16);  // 调 抓投敌人姿态/碰撞初始化（4924C0/4918E0）
    fld_21D4 = v14;
    fld_21D8 = v15;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 8656) + 136))(  // 调用虚函数（虚表槽 +136）
           *(uint32_t *)(this + 8656),
           v14,
           v15,
           0) == 0
      || (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 8656) + 132))(  // 调用虚函数（虚表槽 +132）
           *(uint32_t *)(this + 8656),
           v16) == 0 )
    {
      fld_21D4 = *(uint32_t *)(this + 8660);  // fld_21D4 = this+8660
      fld_21D8 = *(uint32_t *)(this + 8664);  // fld_21D8 = this+8664
    }
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(this + 8656) + 112))(  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      *(uint32_t *)(this + 8656),
      fld_21D4,
      fld_21D8,
      v16);
  }
  (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
    this,
    1,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 2, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
}



// ------------------------------------------------------------
// 0x58C990 CNGhoul__vmt524 —— CNGhoul 技能槽 vmt524（4926A0 目标链）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoul__vmt524(uint32_t *this)  // 函数: CNGhoul 技能槽 vmt524（4926A0 目标链）
{
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
    this,
    -100,
    *(uint32_t *)(*(this + 1554) + 4),  // this+6216 = 资源/帧游标表
    0,
    0,
    0,
    0);
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
           this,
           100,
           *(uint32_t *)(*(this + 1554) + 8),  // this+6216 = 资源/帧游标表
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x58CA00 CNGhoul__vmt528 —— CNGhoul 技能槽 vmt528（11 行轻量）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoul__vmt528(uint32_t *this)  // 函数: CNGhoul 技能槽 vmt528（11 行轻量）
{
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 4));  // this+6216 = 资源/帧游标表
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 8));  // this+6216 = 资源/帧游标表
}



// ------------------------------------------------------------
// 0x58CA30 CNGhoulThrower__vmt1D8 —— CNGhoulThrower 周期状态槽 vmt1D8（45 行）
// ------------------------------------------------------------
void /*thiscall*/ CNGhoulThrower__vmt1D8(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: CNGhoulThrower 周期状态槽 vmt1D8（45 行）
{
  uint32_t *v6; // eax
  uint32_t *fld_e1554; // eax

  if ( *((uint8_t *)this + 8600) == 1 )  // this+8600 = uAI8600
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));  // this+6216 = 资源/帧游标表
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));  // this+6216 = 资源/帧游标表
    if ( ArgList == 8 )  // 若 ArgList == 8
    {
      v6 = *(uint32_t **)(LODWORD(fArg3) + 4);  // 调 取 64 位值低 32 位
      if ( *v6 != 0 )  // 若 *v6 != 0
      {
        if ( *v6 != 1 )  // 若 *v6 != 1
          goto LABEL_8;  // 跳转 LABEL_8
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 16));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
        fld_e1554 = (uint32_t *)(*(this + 1554) + 16);  // this+6216 = 资源/帧游标表
      }
      else
      {
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
        fld_e1554 = (uint32_t *)(*(this + 1554) + 12);  // this+6216 = 资源/帧游标表
      }
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        100,
        *fld_e1554,
        0,
        0,
        0,
        0);
      *(this + 2155) = 0;  // this+8620 = uAI8620
    }
LABEL_8:
    if ( *((uint8_t *)this + 8600) == 1 )  // this+8600 = uAI8600
      IRDMonster__vmt1D8(ArgList, fArg3, nArg4, nArg5);
  }
}



// ------------------------------------------------------------
// 0x58CB00 CNGhoulThrower__vmt14C —— CNGhoulThrower 移动/受击表现槽 vmt14C（41A5E0 粒子挂载）
// ------------------------------------------------------------
char /*thiscall*/ CNGhoulThrower__vmt14C(uint32_t *this)  // 函数: CNGhoulThrower 移动/受击表现槽 vmt14C（41A5E0 粒子挂载）
{
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 8 && sub_41A5E0((unsigned int)(this + 1757)) != 0 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));  // this+6216 = 资源/帧游标表
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));  // this+6216 = 资源/帧游标表
  }
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1324))(this);  // 调用虚函数（虚表槽 +1324）
  return CNGhoul__vmt14C(this);
}



// ------------------------------------------------------------
// 0x58CB70 CNGhoulThrower__vmt52C —— CNGhoulThrower 技能槽 vmt52C：投掷头骨（转发 58BDE0 发射）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulThrower__vmt52C(int *this)  // 函数: CNGhoulThrower 技能槽 vmt52C：投掷头骨（转发 58BDE0 发射）
{
  int result; // eax
  uint32_t *fld_e1554; // eax
  int v4; // ecx

  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( result == 8 )  // 若 result == 8
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result != 1 )  // 若 result != 1
        return result;
      v4 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      result = *(this + 2155);  // this+8620 = uAI8620
      if ( result == 0 && v4 >= 3 )  // 若 result == 0 && v4 >= 3
        goto LABEL_13;  // 跳转 LABEL_13
      if ( result == 1 && v4 >= 9 )  // 若 result == 1 && v4 >= 9
      {
        fld_e1554 = (uint32_t *)(*(this + 1554) + 16);  // this+6216 = 资源/帧游标表
        goto LABEL_12;  // 跳转 LABEL_12
      }
    }
    else
    {
      result = *(this + 2155);  // this+8620 = uAI8620
      if ( result == 0 )  // 若 result == 0
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        if ( *(int *)(result + 148) >= 3 )  // 若 *(int *)(result + 148) >= 3
        {
          fld_e1554 = (uint32_t *)(*(this + 1554) + 12);  // this+6216 = 资源/帧游标表
LABEL_12:
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *fld_e1554);  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
LABEL_13:
          result = sub_58BDE0(this);  // 调 发射投掷物 GhoulThrowerSkull.ptl（423A20=投掷物生成，按 this 参数定弹道）
          ++*(this + 2155);  // this+8620 = uAI8620
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58CC20 CNGhoulMorgan__vmt1D8 —— CNGhoulMorgan 周期状态槽 vmt1D8：GHOUL_ARM_ATK 攻击判定（53F6A0/649E40/4926A0）
// ------------------------------------------------------------
void /*thiscall*/ CNGhoulMorgan__vmt1D8(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: CNGhoulMorgan 周期状态槽 vmt1D8：GHOUL_ARM_ATK 攻击判定（53F6A0/649E40/4926A0）
{
  uint32_t *v6; // eax
  uint8_t *pMem; // eax
  uint8_t *pObj; // eax
  uint32_t *v9; // eax
  uint32_t *fld_e1554; // eax

  if ( *((uint8_t *)this + 8600) == 1 )  // this+8600 = uAI8600
  {
    if ( *((uint8_t *)this + 8624) == 0 )  // this+8624 = uAI8624
    {
      v6 = (uint32_t *)(*(int (**)(void))(*this + 700))();  // 调用虚函数（虚表槽 +700）【推断: [RTTI: IRDActiveObject__vmt2BC ·…】
      sub_53F6A0(v6, (int)this);  // 调 sub_53F6A0
      pMem = operator new(0xA8u);  // operator new 分配 168 字节
      if ( pMem != nullptr )  // 若 pMem 非空
        pObj = sub_649E40(pMem, 400, 5000, 300);  // 调 诅咒动画查询 2（5910D0 + 698F90）
      else
        pObj = nullptr;  // pObj = nullptr 空指针
      (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
        pObj,
        this,
        this,
        0,
        0,
        0,
        -1);
      *((uint8_t *)this + 8624) = 1;  // this+8624 = uAI8624
    }
    if ( ArgList == 8 )  // 若 ArgList == 8
    {
      v9 = *(uint32_t **)(LODWORD(fArg3) + 4);  // 调 取 64 位值低 32 位
      if ( *v9 == 2 )  // 若 *v9 == 2
      {
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 16));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
        fld_e1554 = (uint32_t *)(*(this + 1554) + 16);  // this+6216 = 资源/帧游标表
      }
      else
      {
        if ( *v9 != 3 )  // 若 *v9 != 3
        {
          if ( *v9 == 1 )  // 若 *v9 == 1
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
              this,
              "GHOUL_ARM_ATK",
              -1,
              0,
              0);
          goto LABEL_15;  // 跳转 LABEL_15
        }
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 20));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
        fld_e1554 = (uint32_t *)(*(this + 1554) + 20);  // this+6216 = 资源/帧游标表
      }
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
        this,
        100,
        *fld_e1554,
        0,
        0,
        0,
        0);
      *(this + 2155) = 0;  // this+8620 = uAI8620
    }
LABEL_15:
    if ( *((uint8_t *)this + 8600) == 1 )  // this+8600 = uAI8600
      IRDMonster__vmt1D8(ArgList, fArg3, nArg4, nArg5);
  }
}



// ------------------------------------------------------------
// 0x58CD80 CNGhoulMorgan__vmt14C —— CNGhoulMorgan 移动/受击表现槽 vmt14C（含 58BF40 炸弹发射分支）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulMorgan__vmt14C(int *this)  // 函数: CNGhoulMorgan 移动/受击表现槽 vmt14C（含 58BF40 炸弹发射分支）
{
  int result; // eax
  int v3; // ebx
  uint32_t *fld_e1554; // eax

  CNGhoul__vmt14C(this);  // 调 CNGhoul 移动/受击表现槽 vmt14C
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    || (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    && sub_41A5E0((unsigned int)(this + 1757)) != 2  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    && sub_41A5E0((unsigned int)(this + 1757)) != 3 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));  // this+6216 = 资源/帧游标表
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));  // this+6216 = 资源/帧游标表
  }
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( result == 8 )  // 若 result == 8
  {
    v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      result = *(this + 2155);  // this+8620 = uAI8620
      if ( result == 0 && v3 >= 3 )  // 若 result == 0 && v3 >= 3
      {
        fld_e1554 = (uint32_t *)(*(this + 1554) + 16);  // this+6216 = 资源/帧游标表
LABEL_17:
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *fld_e1554);  // 调用虚函数（虚表槽 +208）【推断: 定时器移除（链表摘除 + 释放）】
LABEL_18:
        result = sub_58BF40(this);  // 调 发射投掷物 GhoulMorganSkullBomb.ptl（ Morgan 头颅炸弹弹道）
        ++*(this + 2155);  // this+8620 = uAI8620
      }
    }
    else
    {
      result = sub_41A5E0((unsigned int)(this + 1757));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result != 3 )  // 若 result != 3
        return result;
      result = *(this + 2155);  // this+8620 = uAI8620
      if ( result == 0 && v3 >= 3 )  // 若 result == 0 && v3 >= 3
        goto LABEL_18;  // 跳转 LABEL_18
      if ( result == 1 && v3 >= 9 )  // 若 result == 1 && v3 >= 9
      {
        fld_e1554 = (uint32_t *)(*(this + 1554) + 20);  // this+6216 = 资源/帧游标表
        goto LABEL_17;  // 跳转 LABEL_17
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58CE90 CNGhoulMorgan__vmt524 —— CNGhoulMorgan 技能槽 vmt524
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulMorgan__vmt524(uint32_t *this)  // 函数: CNGhoulMorgan 技能槽 vmt524
{
  CNGhoul__vmt524(this);  // 调 CNGhoul 技能槽 vmt524
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调用虚函数（虚表槽 +204）
           this,
           200,
           *(uint32_t *)(*(this + 1554) + 12),  // this+6216 = 资源/帧游标表
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x58CED0 CNGhoulNoMercy__vmt1D8 —— CNGhoulNoMercy AI 主状态机 vmt1D8（135 行：状态 4/5/13 切换 + 抓取发起 58C840）
// ------------------------------------------------------------
void /*userpurge*/ sub_58CED0(uint32_t *pArg1@<ecx>, double fArg2@<st0>, void *Block, int pArg4, int nArg5, int nArg6)  // 【CNGhoulNoMercy__vmt1D8】
{
  int v7; // eax
  int pObj; // ecx
  void *Block2; // edi
  int pArg42; // ebx
  int pObj3; // ecx
  int *v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int pObj2; // eax
  int v19; // ebx
  int pObj4; // edi
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax

  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  if ( v7 == 18 )  // 若 v7 == 18
  {
    pObj = pArg1[2169];
    if ( pObj != 0 )  // 若 pObj != 0
    {
      pArg1[2168] = 1;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 604))(pObj, 1);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t))(*(uint32_t *)pArg1[2169] + 612))(pArg1[2169], 1, 0);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
      (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 352))(pArg1);  // 调用虚函数（虚表槽 +352）【推断: [RTTI: IRDCollisionObject__vmt16…】
    }
    Block2 = Block;
  }
  else
  {
    Block2 = Block;
    if ( (Block == (void *)3 || Block == (void *)5 || Block == (void *)4 || Block == (void *)9) && v7 == 16 )  // 若 (Block == (void *)3 || Block == (void *)5 || Block == (void *)..
    {
      pObj3 = pArg1[2164];
      if ( pObj3 != 0 )  // 若 pObj3 != 0
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj3 + 560))(pObj3, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2164] + 564))(pArg1[2164]);  // 调用虚函数（虚表槽 +564）【推断: ★ 位移同步包 vt+234（会话 3 定案：UDP type=…】
      }
    }
  }
  pArg42 = pArg4;
  if ( Block2 == (void *)15 )  // 若 Block2 == (void *)15
  {
    sub_4926A0(*(uint32_t *)(pArg1[1554] + 12));  // 调 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 12));  // 调用虚函数（虚表槽 +196）
  }
  else if ( pArg1[2164] != 0 || Block2 != (void *)16 )  // 否则若 pArg1[2164] != 0 || Block2 != (void *)16
  {
    if ( Block2 == (void *)17 )  // 若 Block2 == (void *)17
    {
      v13 = *pArg1;
      v14 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 124))(pArg1, 0);  // 调用虚函数（虚表槽 +124）
      v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v14);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v13 + 136))(pArg1, v15) == 0  // 调用虚函数（虚表槽 +136）
        || (v16 = *pArg1,
            v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1),  // 调用虚函数（虚表槽 +128）
            (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v16 + 132))(pArg1, v17) == 0) )  // 调用虚函数（虚表槽 +132）
      {
        pObj2 = pArg1[2164];
        if ( pObj2 != 0 )  // 若 pObj2 != 0
        {
          v19 = *pArg1;
          pObj4 = pArg1[2164];
          v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj4);  // 调用虚函数（虚表槽 +128）
          v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 124))(pObj4, v21);  // 调用虚函数（虚表槽 +124）
          v23 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 120))(pObj4, v22);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          (*(void (/*thiscall*/ **)(uint32_t *, int))(v19 + 112))(pArg1, v23);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
          pArg42 = pArg4;
        }
      }
      v24 = *pArg1;
      pArg1[2164] = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(v24 + 560))(pArg1, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      Block2 = Block;
    }
    else if ( Block2 == (void *)18 )  // 否则若 Block2 == (void *)18
    {
      *((uint8_t *)pArg1 + 8620) = 1;
      v25 = sub_45EBE0(**(uint32_t **)(pArg4 + 4), *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4));  // 调 sub_45EBE0
      v26 = __RTDynamicCast(v25, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      pArg1[2169] = v26;
      if ( v26 != 0 )  // 若 v26 != 0
      {
        if ( pArg1[2170] == 0 )  // 若 pArg1[2170] == 0
        {
          if ( operator new(0x68u) != nullptr )  // operator new 分配 104 字节
            v27 = sub_58C780(pArg1);  // 调 NoMercy 状态辅助（4B1030 目标查询）
          else
            v27 = 0;
          pArg1[2170] = v27;
        }
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pArg1[2170] + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
          pArg1[2170],
          pArg1[2169],
          pArg1,
          0,
          0,
          0,
          -1);
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 20));  // 调用虚函数（虚表槽 +196）
    }
    else if ( Block2 == nullptr )  // 否则若 Block2 为空
    {
      pArg1[2156] = 0;
    }
  }
  else
  {
    v12 = (int *)(pArg1[1554] + 16);
    *((uint8_t *)pArg1 + 8620) = 1;
    sub_4926A0(*v12);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 16));  // 调用虚函数（虚表槽 +196）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 344))(pArg1, pArg1[139]);  // 调用虚函数（虚表槽 +344）
    sub_58C840(16, pArg4);  // 调 NoMercy 抓取发起（45EBE0 对象查找 + 58C1D0 姿态初始化，79 行）
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "GHOUL_ARM_ATK", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
  }
  if ( *((uint8_t *)pArg1 + 8600) == 1 )  // 若 *((uint8_t *)pArg1 + 8600) == 1
    sub_4E33D0(pArg1, pArg42, fArg2, (int)Block2, pArg42, *(float *)&nArg5, *(float *)&nArg6);  // 调 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
}


// ------------------------------------------------------------
// 0x58D1A0 CNGhoulOilSellerOlrek__vmt1D8 —— CNGhoulOilSellerOlrek 周期状态槽 vmt1D8（4DB200 播报）
// ------------------------------------------------------------
void /*thiscall*/ CNGhoulOilSellerOlrek__vmt1D8(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 函数: CNGhoulOilSellerOlrek 周期状态槽 vmt1D8（4DB200 播报）
{
  if ( *(uint8_t *)(this + 8600) == 1 )  // 若 *(uint8_t *)(this + 8600) == 1
  {
    if ( ArgList == 5 )  // 若 ArgList == 5
      sub_4DB200(24, 1);  // 调 15% 概率随机文案触发（0x4DB130 的门包装）
    CNGhoulThrower__vmt1D8((uint32_t *)this, ArgList, fArg3, nArg4, nArg5);  // 调 CNGhoulThrower 周期状态槽 vmt1D8
  }
}



// ------------------------------------------------------------
// 0x58D1E0 sub_58D1E0 —— MagmaGhoul 状态辅助：熔岩喷吐参数计算
// ------------------------------------------------------------
int /*thiscall*/ sub_58D1E0(uint32_t *this)  // 函数: MagmaGhoul 状态辅助：熔岩喷吐参数计算
{
  unsigned int i; // esi
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax

  for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
  {
    fld_e29 = *(this + 29);  // fld_e29 = this+29
    v4 = *(uint32_t *)(fld_e29 + 8);  // v4 = fld_e29+8
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )  // 若 (int)i >= result
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);  // v6 = fld_e29+8
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 若 v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2
      pObj = *(uint32_t *)(v6 + 4 * i);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      fld_e292 = *(this + 29);  // fld_e292 = this+29
      v9 = *(uint32_t *)(fld_e292 + 8);  // v9 = fld_e292+8
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 若 v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      v11 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &CNMagmaGhoul `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      if ( v11 != 0 )  // 若 v11 != 0
        *(uint8_t *)(v11 + 8656) = 0;  // v11+8656 = 0
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58D280 sub_58D280 —— MagmaGhoul 状态辅助：受击/死亡表现参数
// ------------------------------------------------------------
int /*thiscall*/ sub_58D280(uint32_t *this)  // 函数: MagmaGhoul 状态辅助：受击/死亡表现参数
{
  unsigned int v1; // edi
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj3; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int v10; // eax
  int pObj2; // eax
  int pObj; // esi
  int pObj4; // [esp+Ch] [ebp-8h]
  int v15; // [esp+10h] [ebp-4h]

  v1 = 0;
  v15 = 99999;
  pObj4 = 0;
  while ( 1 )  // 无限循环
  {
    fld_e29 = *(this + 29);  // fld_e29 = this+29
    v4 = *(uint32_t *)(fld_e29 + 8);  // v4 = fld_e29+8
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)v1 >= v5 )  // 若 (int)v1 >= v5
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);  // v6 = fld_e29+8
    if ( v6 != 0 && v1 < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )  // 若 v6 != 0 && v1 < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2
      pObj3 = *(uint32_t *)(v6 + 4 * v1);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 529) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      fld_e292 = *(this + 29);  // fld_e292 = this+29
      v9 = *(uint32_t *)(fld_e292 + 8);  // v9 = fld_e292+8
      if ( v9 != 0 && v1 < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )  // 若 v9 != 0 && v1 < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2
        v10 = *(uint32_t *)(v9 + 4 * v1);
      else
        v10 = 0;
      pObj2 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &CNMagmaGhoul `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      pObj = pObj2;
      if ( pObj2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2) < v15 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      {
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        pObj4 = pObj;
      }
    }
    ++v1;  // 自增v1
  }
  return pObj4;
}



// ------------------------------------------------------------
// 0x58D350 sub_58D350 —— MagmaGhoul 状态机辅助主入口（699000 时钟 + 58D1E0/58D280 分支）
// ------------------------------------------------------------
char /*thiscall*/ sub_58D350(int *this)  // 函数: MagmaGhoul 状态机辅助主入口（699000 时钟 + 58D1E0/58D280 分支）
{
  int pThis_86D; // esi
  int fld_e2163; // edi
  int v5; // eax
  int pObj2; // edx
  int fld_e29; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // esi
  unsigned int v12; // edi
  int fld_e292; // ecx
  int v14; // edx
  int v15; // eax
  int v16; // edx
  int pObj; // ecx
  int fld_e293; // ecx
  int v19; // edx
  uint32_t *v20; // eax
  uint8_t *v21; // esi
  int v22; // edx
  int v23; // [esp+Ch] [ebp-10h]
  uint8_t *v24; // [esp+10h] [ebp-Ch]
  int v25; // [esp+14h] [ebp-8h]
  int v26; // [esp+18h] [ebp-4h]

  pThis_86D = (int)(this + 2157);  // this+8628 = 指挥计时戳
  fld_e2163 = *(this + 2163);  // this+8652 = 相位槽
  if ( sub_699000((int)(this + 2157)) < fld_e2163 )  // 【clock_now(clk)】
    return 0;
  sub_58D1E0(this);  // 调 MagmaGhoul 状态辅助：熔岩喷吐参数计算
  *(uint8_t *)(pThis_86D + 13) = 0;  // pThis_86D+13 = 0
  *(uint8_t *)(pThis_86D + 14) = 0;  // pThis_86D+14 = 0
  sub_698F90(pThis_86D, 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  v5 = sub_58D280(this);  // 调 MagmaGhoul 状态辅助：受击/死亡表现参数
  pObj2 = v5;
  v24 = (uint8_t *)v5;
  if ( v5 != 0 && (int *)v5 == this )  // 若 v5 != 0 && (int *)v5 == this
  {
    fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
    v8 = *(uint32_t *)(fld_e29 + 364);  // v8 = fld_e29+364
    v9 = fld_e29 + 360;
    v10 = v8 != 0 ? (*(uint32_t *)(v9 + 8) - v8) >> 5 : 0;
    v11 = 224 * v10;
    v23 = 224 * v10;
    v25 = 48 * ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2) / 48);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    if ( v25 < v11 )  // 若 v25 < v11
    {
LABEL_9:
      v26 = 0;
      while ( 1 )  // 无限循环
      {
        v12 = 0;
        while ( 1 )  // 无限循环
        {
          fld_e292 = *(this + 29);  // fld_e292 = this+29
          v14 = *(uint32_t *)(fld_e292 + 8);  // v14 = fld_e292+8
          v15 = v14 != 0 ? (*(uint32_t *)(fld_e292 + 12) - v14) >> 2 : 0;
          if ( (int)v12 >= v15 )  // 若 (int)v12 >= v15
            break;
          v16 = *(uint32_t *)(fld_e292 + 8);  // v16 = fld_e292+8
          if ( v16 != 0 && v12 < (*(uint32_t *)(fld_e292 + 12) - v16) >> 2 )  // 若 v16 != 0 && v12 < (*(uint32_t *)(fld_e292 + 12) - v16) >> 2
            pObj = *(uint32_t *)(v16 + 4 * v12);
          else
            pObj = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) == 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
            goto LABEL_31;  // 跳转 LABEL_31
          fld_e293 = *(this + 29);  // fld_e293 = this+29
          v19 = *(uint32_t *)(fld_e293 + 8);  // v19 = fld_e293+8
          if ( v19 != 0 && v12 < (*(uint32_t *)(fld_e293 + 12) - v19) >> 2 )  // 若 v19 != 0 && v12 < (*(uint32_t *)(fld_e293 + 12) - v19) >> 2
            v20 = *(uint32_t **)(v19 + 4 * v12);
          else
            v20 = nullptr;  // v20 = nullptr 空指针
          v21 = __RTDynamicCast(v20, 0, &CNRDObject `RTTI Type Descriptor', &CNMagmaGhoul `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
          if ( v24 == v21 )  // 若 v24 == v21
          {
            (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);  // 调用虚函数（虚表槽 +1104）
            ++v12;  // 自增v12
          }
          else
          {
            if ( v21 != nullptr
              && v21[8656] == 0
              && *((uint32_t *)v21 + 2155) != v25
              && *((uint32_t *)v21 + 2156) != v26
              && (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(*this + 136))(this, v25, v26, 0) != 0 )  // 调用虚函数（虚表槽 +136）
            {
              v22 = *(uint32_t *)v21;  // v22 = v21
              *((uint32_t *)v21 + 2156) = v26;
              *((uint32_t *)v21 + 2155) = v25;
              v21[8656] = 1;
              (*(void (/*thiscall*/ **)(uint8_t *, int, int))(v22 + 1144))(v21, v25, v26);  // 调用虚函数（虚表槽 +1144）
              break;
            }
LABEL_31:
            ++v12;  // 自增v12
          }
        }
        v26 += 48;
        if ( v26 >= 480 )  // 若 v26 >= 480
        {
          v25 += 48;
          if ( v25 >= v23 )  // 若 v25 >= v23
            return 1;
          goto LABEL_9;  // 跳转 LABEL_9
        }
      }
    }
  }
  return 1;
}


// ------------------------------------------------------------
// 0x58D560 CNMagmaGhoul__vmt14C —— CNMagmaGhoul 移动/受击表现槽 vmt14C（转发 58D350）
// ------------------------------------------------------------
char /*thiscall*/ CNMagmaGhoul__vmt14C(int *this)  // 函数: CNMagmaGhoul 移动/受击表现槽 vmt14C（转发 58D350）
{
  sub_58D350(this);  // 调 MagmaGhoul 状态机辅助主入口（699000 时钟 + 58D1E0/58D280 分支）
  return CNGhoul__vmt14C(this);
}



// ------------------------------------------------------------
// 0x58D570 sub_58D570 —— NoMercy 表现辅助（4E0CD0 目标特效）
// ------------------------------------------------------------
void /*thiscall*/ sub_58D570(int *this)  // 函数: NoMercy 表现辅助（4E0CD0 目标特效）
{
  int v2; // eax
  int fld_e2163; // ebx
  int fld_e1813; // eax
  void *Block2; // ecx
  char v6[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v8; // [esp+10h] [ebp-14h]
  int v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = nullptr;  // Block = nullptr 空指针
  v8 = 0;
  v9 = 0;
  v2 = *this;
  v10 = 0;
  if ( (*(int (/*thiscall*/ **)(int *))(v2 + 840))(this) == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    fld_e2163 = *(this + 2163);  // this+8652 = 相位槽
    if ( sub_699000((int)(this + 2157)) >= fld_e2163 )  // 【clock_now(clk)】
    {
      if ( *(this + 2156) == 0 )  // this+8624 = uAI8624
      {
        fld_e1813 = *(this + 1813);  // this+7252 = pTarget7252
        if ( fld_e1813 != 0
          && (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, fld_e1813, 0) > 200  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
          && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        {
          *(this + 2156) = 1;  // this+8624 = uAI8624
        }
      }
      *((uint8_t *)this + 8641) = 0;
      *((uint8_t *)this + 8642) = 0;
      sub_698F90((int)(this + 2157), 5000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
  }
  if ( *(this + 2156) != 1 )  // this+8624 = uAI8624
    goto LABEL_13;  // 跳转 LABEL_13
  *(this + 2156) = 2;  // this+8624 = uAI8624
  sub_4E0CD0(273, 0, v6, 300);  // 调 按条件号收集对象（阵营/距离/归属过滤，返回计数）
  Block2 = Block;
  if ( Block == nullptr )  // 若 Block 为空
    return;
  if ( (v8 - (int)Block) >> 2 != 0 )  // 若 (v8 - (int)Block) >> 2 != 0
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 352))(this);  // 调用虚函数（虚表槽 +352）【推断: [RTTI: IRDCollisionObject__vmt16…】
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 15, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
LABEL_13:
    Block2 = Block;
  }
  if ( Block2 != nullptr )  // 若 Block2 非空
    j__free(Block2);  // 调 堆释放
}



// ------------------------------------------------------------
// 0x58D690 sub_58D690 —— NoMercy 表现辅助 2（4E5F70/431230 粒子与动画）
// ------------------------------------------------------------
void /*thiscall*/ sub_58D690(int *this, int nArg2)  // 函数: NoMercy 表现辅助 2（4E5F70/431230 粒子与动画）
{
  int pObj; // esi
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  float v8; // [esp+Ch] [ebp-34h] BYREF
  float v9; // [esp+10h] [ebp-30h]
  float v10; // [esp+14h] [ebp-2Ch]
  int v11; // [esp+18h] [ebp-28h]
  int v12; // [esp+1Ch] [ebp-24h]
  int v13; // [esp+20h] [ebp-20h]
  uint8_t v14[4]; // [esp+24h] [ebp-1Ch] BYREF
  void *Block; // [esp+28h] [ebp-18h]
  int v16; // [esp+2Ch] [ebp-14h]
  int v17; // [esp+30h] [ebp-10h]
  int v18; // [esp+3Ch] [ebp-4h]

  pObj = nArg2;
  if ( nArg2 != 0 )  // 若 nArg2 != 0
  {
    v4 = *this;
    v8 = 0.0;
    v9 = 0.0;
    v10 = 0.0;
    v11 = 0;
    v12 = 0;
    v13 = 0;
    if ( (*(int (/*thiscall*/ **)(int *))(v4 + 152))(this) == 1 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      v5 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    else
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v6 = *this;
    nArg2 = v5 + 20;
    v8 = (float)(v5 + 20);
    nArg2 = (*(int (/*thiscall*/ **)(int *))(v6 + 124))(this) + 1;  // 调用虚函数（虚表槽 +124）
    v7 = *this;
    v9 = (float)nArg2;
    nArg2 = (*(int (/*thiscall*/ **)(int *))(v7 + 128))(this) + 80;  // 调用虚函数（虚表槽 +128）
    v10 = (float)nArg2;
    sub_4E5F70(0, (int)this, pObj, &v8, 1, 1);  // 调 ★ 硬直率掷（研究 §5.1 第 14 轮定案：同构于暴击掷）
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    {
      Block = nullptr;  // Block = nullptr 空指针
      v16 = 0;
      v17 = 0;
      v18 = 0;
      nArg2 = 4;
      sub_431230((int)v14, &nArg2);  // 调 uint32 vector push_back
      nArg2 = 0;
      sub_431230((int)v14, &nArg2);  // 调 uint32 vector push_back
      nArg2 = 1;
      sub_431230((int)v14, &nArg2);  // 调 uint32 vector push_back
      nArg2 = 500;
      sub_431230((int)v14, &nArg2);  // 调 uint32 vector push_back
      nArg2 = 300;
      sub_431230((int)v14, &nArg2);  // 调 uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, uint8_t *, int, uint32_t))(*(uint32_t *)pObj + 560))(pObj, 4, v14, 2, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 564))(pObj);  // 调用虚函数（虚表槽 +564）【推断: ★ 位移同步包 vt+234（会话 3 定案：UDP type=…】
      if ( Block != nullptr )  // 若 Block 非空
        j__free(Block);  // 调 堆释放
    }
  }
}



// ------------------------------------------------------------
// 0x58D7F0 sub_58D7F0 —— NoMercy 移动/受击表现主函数（117 行，58D690 调用 + 432E50 播报）
// ------------------------------------------------------------
int /*usercall*/ sub_58D7F0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 函数: NoMercy 移动/受击表现主函数（117 行，58D690 调用 + 432E50 播报）
{
  int v3; // eax
  int v4; // edx
  int v5; // eax
  uint64_t v6; // rax
  int v7; // edi
  int v8; // eax
  int result; // eax
  int pObj2; // ecx
  int v11; // ebx
  int v12; // edi
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int pObj3; // ecx
  unsigned int v17; // eax
  int pObj; // ecx
  int v19; // [esp+8h] [ebp-4h]

  v3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  v4 = *pDwArg1;
  if ( v3 == 15 )  // 若 v3 == 15
  {
    v5 = (*(int (/*thiscall*/ **)(int *))(v4 + 200))(pDwArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    v6 = (uint64_t)sub_4049C0(800.0, 0.0, *(uint32_t *)(v5 + 148), 5);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(*pDwArg1 + 876))(pDwArg1, 0, v6, v6, 0, 100, 1);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
    v7 = *pDwArg1;
    v8 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(int *, int))(v7 + 896))(pDwArg1, v8);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
    (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*pDwArg1 + 888))(pDwArg1, 2, 2, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
    result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
    if ( *(uint8_t *)(result + 170) != 0 )  // 若 *(uint8_t *)(result + 170) != 0
    {
      result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
        return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(int *))(v4 + 840))(pDwArg1);  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    if ( result == 16 )  // 若 result == 16
    {
      pObj2 = pDwArg1[2164];
      if ( pObj2 != 0 )  // 若 pObj2 != 0
      {
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 840))(pObj2) == 9 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
        {
          if ( *(int *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) + 148) >= 2 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 && *((uint8_t *)pDwArg1 + 8620) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
              sub_58D690(pDwArg1[2164]);  // 调 NoMercy 表现辅助 2（4E5F70/431230 粒子与动画）
            *((uint8_t *)pDwArg1 + 8620) = 0;
          }
          (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pDwArg1[2164] + 604))(pDwArg1[2164], 0, nArg2);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pDwArg1[2164] + 612))(pDwArg1[2164], 1, 1);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
          if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1) != 0 )  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) + 100;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          else
            v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) - 100;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          v12 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1) - 1;  // 调用虚函数（虚表槽 +124）
          v19 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调用虚函数（虚表槽 +128）
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2164] + 136))(  // 调用虚函数（虚表槽 +136）
                 pDwArg1[2164],
                 v11,
                 v12,
                 0) != 0
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[2164] + 132))(pDwArg1[2164], v19) != 0 )  // 调用虚函数（虚表槽 +132）
          {
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pDwArg1[2164] + 112))(pDwArg1[2164], v11, v12);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
          }
          else
          {
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pDwArg1[2164] + 112))(pDwArg1[2164], pDwArg1[2165], pDwArg1[2166]);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
          }
        }
        else if ( *((uint8_t *)pDwArg1 + 8620) == 1
               && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2164] + 840))(pDwArg1[2164]) != 5  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
               && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2164] + 308))(pDwArg1[2164]) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        {
          v13 = *(uint32_t *)pDwArg1[2164];
          v14 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          v15 = sub_432E50(v14);  // 调 关系码对调映射
          (*(void (/*thiscall*/ **)(int, int))(v13 + 144))(pDwArg1[2164], v15);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)pDwArg1[2164] + 560))(pDwArg1[2164], 9, 0, 2, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2164] + 564))(pDwArg1[2164]);  // 调用虚函数（虚表槽 +564）【推断: ★ 位移同步包 vt+234（会话 3 定案：UDP type=…】
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      }
      result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
      if ( *(uint8_t *)(result + 170) != 0
        || (pObj3 = pDwArg1[2164]) != 0
        && (v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 684))(pObj3), (result = sub_41A5E0(v17)) <= 0) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      {
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 17, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        pObj = pDwArg1[2164];
        if ( pObj != 0 )  // 若 pObj != 0
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 604))(pObj, 1);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
          (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)pDwArg1[2164] + 612))(pDwArg1[2164], 1, 0);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
        }
        return (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 352))(pDwArg1);  // 调用虚函数（虚表槽 +352）【推断: [RTTI: IRDCollisionObject__vmt16…】
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x58DB10 CNGhoulNoMercy__vmt14C —— CNGhoulNoMercy 移动/受击表现槽 vmt14C（111 行：58D7F0/58D570/58D690 分支）
// ------------------------------------------------------------
char /*usercall*/ CNGhoulNoMercy__vmt14C@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 函数: CNGhoulNoMercy 移动/受击表现槽 vmt14C（111 行：58D7F0/58D570/58D690 分支）
{
  int pObj2; // ecx
  int v6; // eax
  int pObj; // ecx
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int *v11; // ecx
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // eax
  int pObj3; // ecx
  unsigned int v19; // eax
  int v21; // [esp+4h] [ebp-4h] BYREF

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 15  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 16 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
  {
    sub_58D7F0((int *)pArg1, nArg2);  // 调 NoMercy 移动/受击表现主函数（117 行，58D690 调用 + 432E50 播报）
  }
  else
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    {
      sub_58D570((int *)pArg1);  // 调 NoMercy 表现辅助（4E0CD0 目标特效）
      return CNGhoul__vmt14C((uint32_t *)pArg1);
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 18 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
    {
      pObj2 = *(uint32_t *)(pArg1 + 8676);  // pObj2 = pArg1+8676
      if ( pObj2 != 0 )  // 若 pObj2 != 0
      {
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 840))(pObj2) == 9 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
        {
          if ( *(int *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 200))(pArg1, nArg3) + 148) >= 2 )  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
            {
              sub_58D690((int *)pArg1, *(uint32_t *)(pArg1 + 8676));  // 调 NoMercy 表现辅助 2（4E5F70/431230 粒子与动画）
              v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 340))(pArg1);  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
              pObj = *(uint32_t *)(pArg1 + 8676);  // pObj = pArg1+8676
              v8 = *(uint32_t *)pArg1;  // v8 = pArg1
              v21 = **(uint32_t **)(v6 + 64);
              v9 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int *))(*(uint32_t *)pObj + 56))(  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
                     pObj,
                     0,
                     0,
                     0,
                     0,
                     0,
                     4,
                     0,
                     4,
                     &v21);
              (*(void (/*thiscall*/ **)(int, int, int))(v8 + 580))(pArg1, 30202, v9);  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
            }
            *(uint8_t *)(pArg1 + 8620) = 0;  // pArg1+8620 = 0
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8676) + 604))(*(uint32_t *)(pArg1 + 8676), 0);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
          (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(pArg1 + 8676) + 612))(*(uint32_t *)(pArg1 + 8676), 1, 1);  // 调用虚函数（虚表槽 +612）【推断: 帧时刻覆盖开关（this+642 标志 / this+644 时…】
          v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 0  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              ? (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 100  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              : (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 100;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          v11 = *(int **)(pArg1 + 8676);
          v12 = *v11;
          v13 = (*(int (/*thiscall*/ **)(int *, int))(*v11 + 128))(v11, nArg2);  // 调用虚函数（虚表槽 +128）
          v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v13);  // 调用虚函数（虚表槽 +124）
          (*(void (/*thiscall*/ **)(uint32_t, int, int))(v12 + 112))(*(uint32_t *)(pArg1 + 8676), v10, v14 - 1);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
        }
        else if ( *(uint8_t *)(pArg1 + 8620) == 1
               && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8676) + 840))(*(uint32_t *)(pArg1 + 8676)) != 5  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
               && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8676) + 308))(*(uint32_t *)(pArg1 + 8676)) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        {
          v15 = **(uint32_t **)(pArg1 + 8676);
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          v17 = sub_432E50(v16);  // 调 关系码对调映射
          (*(void (/*thiscall*/ **)(uint32_t, int))(v15 + 144))(*(uint32_t *)(pArg1 + 8676), v17);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(pArg1 + 8676) + 560))(  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
            *(uint32_t *)(pArg1 + 8676),
            9,
            0,
            2,
            0);
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8676) + 564))(*(uint32_t *)(pArg1 + 8676));  // 调用虚函数（虚表槽 +564）【推断: ★ 位移同步包 vt+234（会话 3 定案：UDP type=…】
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      }
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 170) != 0  // 调用虚函数（虚表槽 +200）【推断: 取动画对象】
        || (pObj3 = *(uint32_t *)(pArg1 + 8676)) != 0
        && (v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 684))(pObj3), sub_41A5E0(v19) <= 0) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        return CNGhoul__vmt14C((uint32_t *)pArg1);
      }
    }
  }
  return CNGhoul__vmt14C((uint32_t *)pArg1);
}



// ------------------------------------------------------------
// 0x58DD70 CNGhoulNoMercy__vmt1F4 —— CNGhoulNoMercy 技能槽 vmt1F4（92 行：431230 动作 + 5E5260 成员清理）
// ------------------------------------------------------------
int /*userpurge*/ CNGhoulNoMercy__vmt1F4@<eax>(int nArg1@<ecx>, int nArg2@<ebx>, int nArg3, int nArg4, int nArg5)  // 函数: CNGhoulNoMercy 技能槽 vmt1F4（92 行：431230 动作 + 5E5260 成员清理）
{
  char v6; // al
  int pObj2; // esi
  int pObj3; // eax
  int pObj; // ebx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int pObj4; // ebx
  int v15; // eax
  void *v18; // [esp+8h] [ebp-1Ch] BYREF
  int v19; // [esp+Ch] [ebp-18h]
  int v20; // [esp+10h] [ebp-14h]
  int v21; // [esp+14h] [ebp-10h]
  int v22; // [esp+20h] [ebp-4h]

  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 308))(nArg1);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  pObj2 = nArg3;
  if ( v6 != 0 && (uint8_t)nArg5 == 0 )  // 若 v6 != 0 && (uint8_t)nArg5 == 0
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 840))(nArg1) == 15  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      pObj3 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
             pObj2,
             0,
             &IRDCollisionObject `RTTI Type Descriptor',
             &IRDActiveObject `RTTI Type Descriptor',
             0);
      pObj = pObj3;
      if ( pObj3 != 0 )  // 若 pObj3 != 0
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 948))(pObj3, nArg2) != 0  // 调用虚函数（虚表槽 +948）
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 0  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 568))(nArg1) != 16 )  // 调用虚函数（虚表槽 +568）
        {
          v19 = 0;
          v20 = 0;
          v21 = 0;
          v10 = *(uint32_t *)pObj2;  // v10 = pObj2
          v22 = 0;
          nArg3 = (*(int (/*thiscall*/ **)(int))(v10 + 48))(pObj2);  // 调用虚函数（虚表槽 +48）
          sub_431230((int)&v18, &nArg3);  // 调 uint32 vector push_back
          nArg3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);  // 调用虚函数（虚表槽 +52）
          sub_431230((int)&v18, &nArg3);  // 调 uint32 vector push_back
          (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)nArg1 + 560))(nArg1, 16, &v18, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
          v22 = -1;
          sub_5E5260(&v18);  // 调 sub_5E5260
        }
        v11 = *(uint32_t *)pObj2;  // v11 = pObj2
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 152))(nArg1);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        v13 = sub_432E50(v12);  // 调 关系码对调映射
        (*(void (/*thiscall*/ **)(int, int))(v11 + 144))(pObj2, v13);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
      }
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 840))(nArg1) == 8  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 908))(nArg1) == 1  // 调用虚函数（虚表槽 +908）
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
      && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) != 405  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
      && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) != 406  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
      && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) != 422 )  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
    {
      pObj4 = __RTDynamicCast(pObj2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      if ( pObj4 != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 948))(pObj4) != 0  // 调用虚函数（虚表槽 +948）
        && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 840))(pObj4) == 0 )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
      {
        v19 = 0;
        v20 = 0;
        v21 = 0;
        v15 = *(uint32_t *)pObj2;  // v15 = pObj2
        v22 = 1;
        nArg3 = (*(int (/*thiscall*/ **)(int))(v15 + 48))(pObj2);  // 调用虚函数（虚表槽 +48）
        sub_431230((int)&v18, &nArg3);  // 调 uint32 vector push_back
        nArg3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);  // 调用虚函数（虚表槽 +52）
        sub_431230((int)&v18, &nArg3);  // 调 uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)nArg1 + 560))(nArg1, 18, &v18, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        v22 = -1;
        sub_5E5260(&v18);  // 调 sub_5E5260
      }
    }
  }
  return IRDMonster__vmt1F4(pObj2, nArg4, nArg5);
}



// ------------------------------------------------------------
// 0x58DFE0 sub_58DFE0 —— R_GHOUL 部件标签注册：R_GHOUL/R_GHOUL_ATK/R_GHOUL_DIE/R_GHOUL_DMG（4A4EA0）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_58DFE0(uint8_t *this, char ArgList, int nArg3, char pszArg4)  // 函数: R_GHOUL 部件标签注册：R_GHOUL/R_GHOUL_ATK/R_GHOUL_DIE/R_GHOUL_DMG（4A4…
{
  uint32_t *pThis_612; // eax

  sub_4A4EA0(ArgList, nArg3);  // 调 sub_4A4EA0
  *(uint32_t *)this = &vftbl_CNGhoul;
  *(this + 8600) = 0;  // this+34400 = 0
  *((uint32_t *)this + 2151) = 0;  // this+8604 = bAI8604
  sub_58BA00(this);  // 调 食尸鬼部件参数初始化：+1698..+1702 状态组（1/1/3/4/4）、+2152..54=-1、+4185 起 26…
  if ( pszArg4 == 1 )  // 若 pszArg4 == 1
  {
    *((uint32_t *)this + 1639) = 0;  // this+6556 = 主状态镜像
    *((uint32_t *)this + 2151) = -1;  // this+8604 = bAI8604
    *(this + 8600) = 1;  // this+34400 = 1
  }
  else
  {
    pThis_612 = *((uint32_t **)this + 1554);
    *((uint32_t *)this + 1639) = 14;  // this+6556 = 主状态镜像
    IRDActiveObject__vmtC4(*pThis_612);
  }
  sub_4015C0("R_GHOUL_ATK", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("R_GHOUL_DMG", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("R_GHOUL_DIE", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("R_GHOUL", 7u);  // 【std::string构造赋值】
  return this;
}



// ------------------------------------------------------------
// 0x58E0D0 sub_58E0D0 —— CNGhoul 析构成员清理（4A50F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58E0D0(uint32_t *this)  // 函数: CNGhoul 析构成员清理（4A50F0）
{
  *this = &vftbl_CNGhoul;  // *this 写入 &vftbl_CNGhoul
  return sub_4A50F0();  // 调 sub_4A50F0
}



// ------------------------------------------------------------
// 0x58E0E0 sub_58E0E0 —— CNGhoul 构造：调用 58DFE0 注册部件标签
// ------------------------------------------------------------
int /*thiscall*/ sub_58E0E0(int this, char ArgList, int nArg3, char pszArg4)  // 函数: CNGhoul 构造：调用 58DFE0 注册部件标签
{
  uint16_t *pThis_20B2; // eax
  int i; // ecx
  uint32_t *fld_1848; // eax

  sub_58DFE0((uint8_t *)this, ArgList, nArg3, pszArg4);  // 调 R_GHOUL 部件标签注册：R_GHOUL/R_GHOUL_ATK/R_GHOUL_DIE/R_GHOUL_DMG（4A4…
  *(uint32_t *)this = &vftbl_CNGhoulThrower;
  *(uint32_t *)(this + 8620) = 1;  // this+8620 = 1
  *(uint32_t *)(this + 6792) = 1;  // this+6792 = 1
  *(uint32_t *)(this + 6796) = 1;  // this+6796 = 1
  *(uint32_t *)(this + 6800) = 3;  // this+6800 = 3
  *(uint32_t *)(this + 6804) = 4;  // this+6804 = 4
  *(uint32_t *)(this + 6808) = 4;  // this+6808 = 4
  pThis_20B2 = (uint16_t *)(this + 8370);
  for ( i = 26; i != 0; --i )  // 循环：i = 26; i != 0; --i
  {
    *pThis_20B2 = 50;  // *pThis_20B2 写入 50
    pThis_20B2 += 2;
  }
  if ( pszArg4 == 1 )  // 若 pszArg4 == 1
  {
    *(uint32_t *)(this + 6556) = 0;  // this+6556 = 0
    *(uint32_t *)(this + 8604) = -1;  // this+8604 = -1
    *(uint8_t *)(this + 8600) = 1;  // this+8600 = 1
  }
  else
  {
    fld_1848 = *(uint32_t **)(this + 6216);
    *(uint32_t *)(this + 6556) = 14;  // this+6556 = 14
    IRDActiveObject__vmtC4(*fld_1848);
  }
  return this;
}



// ------------------------------------------------------------
// 0x58E1D0 sub_58E1D0 —— CNGhoul 派生构造共用：部件标签注册（58DFE0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58E1D0(int this, char ArgList, int nArg3, char pszArg4)  // 函数: CNGhoul 派生构造共用：部件标签注册（58DFE0）
{
  char v5; // dl
  uint32_t *fld_1848; // eax

  sub_58DFE0((uint8_t *)this, ArgList, nArg3, 0);  // 调 R_GHOUL 部件标签注册：R_GHOUL/R_GHOUL_ATK/R_GHOUL_DIE/R_GHOUL_DMG（4A4…
  *(uint32_t *)this = &vftbl_CNGhoulNoMercy;
  *(uint8_t *)(this + 8632) = 0;  // this+8632 = 0
  *(uint32_t *)(this + 8628) = &vftbl_nengine__CNTimer;  // this+8628 = &vftbl_nengine__CNTimer
  *(uint32_t *)(this + 8636) = 0;  // this+8636 = 0
  *(uint8_t *)(this + 8640) = 1;  // this+8640 = 1
  *(uint8_t *)(this + 8642) = 0;  // this+8642 = 0
  *(uint8_t *)(this + 8641) = 0;  // this+8641 = 0
  *(uint32_t *)(this + 8652) = 0;  // this+8652 = 0
  *(uint32_t *)(this + 8648) = 0;  // this+8648 = 0
  *(uint32_t *)(this + 8644) = 0;  // this+8644 = 0
  CNGhoulNoMercy__vmt4A8(this);  // 调 CNGhoulNoMercy 技能槽 vmt4A8
  if ( pszArg4 == v5 )  // 若 pszArg4 == v5
  {
    *(uint32_t *)(this + 6556) = 0;  // this+6556 = 0
    *(uint32_t *)(this + 8604) = -1;  // this+8604 = -1
    *(uint8_t *)(this + 8600) = v5;  // this+8600 = v5
  }
  else
  {
    fld_1848 = *(uint32_t **)(this + 6216);
    *(uint32_t *)(this + 6556) = 14;  // this+6556 = 14
    IRDActiveObject__vmtC4(*fld_1848);
  }
  return this;
}



// ------------------------------------------------------------
// 0x58E2B0 sub_58E2B0 —— CNGhoulNoMercy 析构成员清理（4A50F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58E2B0(uint32_t *this)  // 函数: CNGhoulNoMercy 析构成员清理（4A50F0）
{
  *(this + 2157) = &vftbl_nengine__IObject;  // this+8628 = 指挥计时戳
  *((uint8_t *)this + 8632) = 0;
  *this = &vftbl_CNGhoul;  // *this 写入 &vftbl_CNGhoul
  return sub_4A50F0();  // 调 sub_4A50F0
}



// ------------------------------------------------------------
// 0x58E2D0 CNGhoul__vmt0 —— CNGhoul 标量删除析构（vmt0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNGhoul__vmt0(uint32_t *Block, char pszArg2)
{
  sub_58E0D0(Block);  // 调 CNGhoul 析构成员清理（4A50F0）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x58E300 CNGhoulNoMercy__vmt0 —— CNGhoulNoMercy 标量删除析构（vmt0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNGhoulNoMercy__vmt0(uint32_t *Block, char pszArg2)
{
  sub_58E2B0(Block);  // 调 CNGhoulNoMercy 析构成员清理（4A50F0）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x58E330 CNGhoulMorgan__vmt51C —— CNGhoulMorgan 技能槽 vmt51C（4BA9E0）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulMorgan__vmt51C(void *this)  // 函数: CNGhoulMorgan 技能槽 vmt51C（4BA9E0）
{
  char *pMem; // eax
  char *v3; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_4BA9E0(pMem, "Monster/Ghoul/GhoulMorgan/GhoulThrowerClothes.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若 result != 0
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  return result;
}



// ------------------------------------------------------------
// 0x58E3B0 CNGhoulOilSellerOlrek__vmt51C —— CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulOilSellerOlrek__vmt51C(void *this)  // 函数: CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
{
  char *pMem; // eax
  char *v3; // eax
  int pThis_310; // eax
  char *pMem2; // eax
  char *v6; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_4BA9E0(pMem, "monster/Ghoul/GhoulOilSellerOlrek/backpack_-100.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);  // 调用虚函数（虚表槽 +784）
  if ( pThis_310 != 0 )  // 若 pThis_310 != 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);  // 调用虚函数（虚表槽 +4）
  pMem2 = (char *)operator new(0x544u);  // operator new 分配 1348 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v6 = sub_4BA9E0(pMem2, "monster/Ghoul/GhoulOilSellerOlrek/backpack_100.equ", 0);  // 调 CNRDEquipment 构造（.equ 外观对象公共工厂）
  else
    v6 = nullptr;  // v6 = nullptr 空指针
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);  // 调用虚函数（虚表槽 +784）
  if ( result != 0 )  // 若 result != 0
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调用虚函数（虚表槽 +4）
  return result;
}



// ------------------------------------------------------------
// 0x58E480 sub_58E480 —— CNGhoul 派生构造共用 2（部件标签注册 58DFE0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58E480(int this, char ArgList, int nArg3)  // 函数: CNGhoul 派生构造共用 2（部件标签注册 58DFE0）
{
  uint16_t *pThis_20B2; // eax
  int i; // ecx
  uint32_t *fld_1848; // eax

  sub_58DFE0((uint8_t *)this, ArgList, nArg3, 0);  // 调 R_GHOUL 部件标签注册：R_GHOUL/R_GHOUL_ATK/R_GHOUL_DIE/R_GHOUL_DMG（4A4…
  *(uint32_t *)this = &vftbl_CNGhoulMorgan;
  pThis_20B2 = (uint16_t *)(this + 8370);
  for ( i = 26; i != 0; --i )  // 循环：i = 26; i != 0; --i
  {
    *pThis_20B2 = 50;  // *pThis_20B2 写入 50
    pThis_20B2 += 2;
  }
  CNGhoulMorgan__vmt51C(this);  // 调 CNGhoulMorgan 技能槽 vmt51C
  fld_1848 = *(uint32_t **)(this + 6216);
  *(uint8_t *)(this + 8624) = 0;  // this+8624 = 0
  *(uint32_t *)(this + 6556) = 14;  // this+6556 = 14
  IRDActiveObject__vmtC4(*fld_1848);
  *(uint32_t *)(this + 6792) = 1;  // this+6792 = 1
  *(uint32_t *)(this + 6796) = 1;  // this+6796 = 1
  *(uint32_t *)(this + 6800) = 3;  // this+6800 = 3
  *(uint32_t *)(this + 6804) = 4;  // this+6804 = 4
  *(uint32_t *)(this + 6808) = 4;  // this+6808 = 4
  return this;
}



// ============================================================
// 【分区 6】IRDActiveObject 共享覆写（0x58E550-0x58FC30）
// vmt144=绘制前置；vmt148=2D 精灵绘制（491530/491630 批次对）；
// vmt1D8=主状态机 874 行（CONDITION_STUN/DOWN_HEAVY/DOWN_LIGHT/DOWN_MIDDLE/
// JUMP_START/JUMP_END 状态动画标签，落点均在 0x58E920）；
// vmt14C=行走动画 505 行（G_WALK_FLOOR_LOOP/WALK_SOIL_LOOP/WALK_STONE_LOOP
// 按地面材质分标签）；sub_58DFE0=R_GHOUL 系部件标签注册（4A4EA0）。
// ============================================================
// ------------------------------------------------------------
// 0x58E550 IRDActiveObject__vmt144 —— IRDActiveObject__vmt144 绘制前置槽（53F9D0）
// ------------------------------------------------------------
void /*thiscall*/ IRDActiveObject__vmt144(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 函数: IRDActiveObject__vmt144 绘制前置槽（53F9D0）
{
  uint32_t *pThis_625; // edi
  uint32_t *pThis_615; // edi
  int j; // [esp+14h] [ebp+8h]
  int i; // [esp+20h] [ebp+14h]

  if ( (uint8_t)nArg2 != 0 )  // 若 (uint8_t)nArg2 != 0
  {
    nullsub_2(nArg2, nArg3, nArg4, nArg5);
    pThis_615 = this + 1557;
    for ( i = 17; i != 0; --i )  // 循环：i = 17; i != 0; --i
    {
      if ( *pThis_615 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)*pThis_615 + 24))() != 0 )  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(*(uint32_t *)*pThis_615 + 52))(*pThis_615, nArg2, nArg3, nArg4, nArg5);  // 调用虚函数（虚表槽 +52）
      ++pThis_615;  // 自增pThis_615
    }
    sub_53F9D0(nArg2, nArg3, nArg4, nArg5);  // 调 sub_53F9D0
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 872))(this, nArg3, nArg4, nArg5);  // 调用虚函数（虚表槽 +872）【推断: ★ 1 秒窗特效链逐帧推进】
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1016))(this);  // 调用虚函数（虚表槽 +1016）
  }
  else
  {
    sub_53F9D0(0, nArg3, nArg4, nArg5);  // 调 sub_53F9D0
    pThis_625 = this + 1573;
    for ( j = 17; j != 0; --j )  // 循环：j = 17; j != 0; --j
    {
      if ( *pThis_625 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)*pThis_625 + 24))() != 0 )  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, int, int))(*(uint32_t *)*pThis_625 + 52))(*pThis_625, 0, nArg3, nArg4, nArg5);  // 调用虚函数（虚表槽 +52）
      --pThis_625;  // 自减pThis_625
    }
    nullsub_2(0, nArg3, nArg4, nArg5);
  }
}



// ------------------------------------------------------------
// 0x58E660 sub_58E660 —— 食尸鬼族通用：粒子/部件参数复位（供 vmt1D8/vmt14C 调用）
// ------------------------------------------------------------
int /*thiscall*/ sub_58E660(uint32_t *this)  // 函数: 食尸鬼族通用：粒子/部件参数复位（供 vmt1D8/vmt14C 调用）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 988))(this) != 0 )  // 调用虚函数（虚表槽 +988）
    {
      if ( *(this + 1542) != 0 )  // 若 *(this + 1542) != 0
        return (*(int (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t))(*this + 560))(1, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      else
        return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 3);  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
      if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
        return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t))(*this + 560))(this, 9, 0, 2, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58E6D0 sub_58E6D0 —— 食尸鬼族通用：41A5E0 粒子挂载（状态表现）
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_58E6D0(void *this)  // 函数: 食尸鬼族通用：41A5E0 粒子挂载（状态表现）
{
  int pThis_384; // [esp+8h] [ebp-4h]

  pThis_384 = sub_41A5E0((unsigned int)this + 900);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)pThis_384 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 914)));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x58E710 sub_58E710 —— 食尸鬼族通用：41A5E0 粒子挂载（第二变体）
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_58E710(void *this)  // 函数: 食尸鬼族通用：41A5E0 粒子挂载（第二变体）
{
  int pThis_3A0; // [esp+8h] [ebp-4h]

  pThis_3A0 = sub_41A5E0((unsigned int)this + 928);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)pThis_3A0 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 942)));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x58E750 IRDActiveObject__vmt148 —— IRDActiveObject__vmt148 2D 精灵绘制：491530/491630 批次对 + 418DD0 取精灵 + 424760 贴图
// ------------------------------------------------------------
int /*thiscall*/ IRDActiveObject__vmt148(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 函数: IRDActiveObject__vmt148 2D 精灵绘制：491530/491630 批次对 + 418DD0 取精灵 + 424760 贴图
{
  int v7; // eax
  int nArg32; // ebx
  int v9; // ebx
  bool v10; // zf
  int v11; // eax
  uint32_t *pThis_625; // esi
  int result; // eax
  uint32_t *pThis_615; // edi
  int i; // [esp+14h] [ebp+8h]
  unsigned int v16; // [esp+18h] [ebp+Ch]
  int j; // [esp+18h] [ebp+Ch]

  if ( (uint8_t)nArg2 != 0 )  // 若 (uint8_t)nArg2 != 0
  {
    CNRDObject__vmt148(this, nArg2, nArg3, nArg4, nArg5);
    pThis_615 = this + 1557;
    for ( i = 17; i != 0; --i )  // 循环：i = 17; i != 0; --i
    {
      if ( *pThis_615 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_615 + 24))(*pThis_615) != 0 )  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(*(uint32_t *)*pThis_615 + 56))(*pThis_615, nArg2, nArg3, nArg4, nArg5);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
      ++pThis_615;  // 自增pThis_615
    }
    return sub_53FAB0(nArg2, nArg3, nArg4, nArg5);  // 调 sub_53FAB0
  }
  else
  {
    v7 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 = 当前场景状态对象
    nArg32 = nArg3;
    if ( (v7 == 4 || v7 == 6) && dword_99FEC0 != 0 && (uint8_t)sub_48F620(dword_99FEC0) != 0 )  // 调 对局中标志查询
    {
      if ( this == (uint32_t *)dword_8F7C04  // dword_8F7C04 = 本地玩家对象
        || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 940))(this) == 0  // 调用虚函数（虚表槽 +940）
        || (v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this),  // 调用虚函数（虚表槽 +376）
            v10 = v9 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04),  // 调用虚函数（虚表槽 +376）
            nArg32 = nArg3,
            v10) )
      {
        v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this);  // 调用虚函数（虚表槽 +376）
        if ( v16 < 4 )  // 若 v16 < 4
        {
          sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          v11 = sub_418DD0(v16 + 39);  // 调 sub_418DD0
          sub_424760(dword_79C0B0, nArg32 - 63, nArg4 - 21, v11, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
          sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
        }
      }
    }
    CNRDObject__vmt148(this, 0, nArg32, nArg4, nArg5);
    sub_53FAB0(0, nArg32, nArg4, nArg5);  // 调 sub_53FAB0
    pThis_625 = this + 1573;
    for ( j = 17; j != 0; --j )  // 循环：j = 17; j != 0; --j
    {
      if ( *pThis_625 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)*pThis_625 + 24))() != 0 )  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, int, int))(*(uint32_t *)*pThis_625 + 56))(*pThis_625, 0, nArg32, nArg4, nArg5);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
      --pThis_625;  // 自减pThis_625
      result = j - 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58E920 IRDActiveObject__vmt1D8 —— IRDActiveObject__vmt1D8 主状态机（874 行）：CONDITION_STUN/DOWN_HEAVY/DOWN_LIGHT/DOWN_MIDDLE/JUMP_START/JUMP_END 状态动画与物理分支
// ------------------------------------------------------------
char /*thiscall*/ sub_58E920(int *this, int nArg2, int pArg3, float fArg4, float fArg5)  // 【IRDActiveObject__vmt1D8】
{
  int fld_e1639; // ebx  | +0x199C → nMainState6556〔族字典〕（族字典）
  int v7; // eax
  int fld_e16392; // eax  | +0x199C → nMainState6556〔族字典〕（族字典）
  int v10; // edx
  int fld_e81; // edi  | +0x0144 → 随机/拾取编号槽（IRDActiveObject；va=004D6970）
  int v12; // edx
  int *v13; // eax
  int v14; // ebx
  int v15; // eax
  int v16; // ebx
  int v17; // edi
  int v18; // eax
  int v19; // eax
  uint64_t v20; // rax
  int v21; // eax
  int v22; // eax
  int v23; // edi
  int v24; // eax
  int v25; // edx
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int fld_e1708; // edx
  int v30; // ebx
  int v31; // eax
  int v32; // ecx
  int v33; // eax
  int v34; // edi
  int v35; // eax
  int v36; // edi
  int v37; // edi
  int fld_e1705; // eax
  int v39; // eax
  int fld_e17052; // edx
  int v41; // ebx
  bool fld_e17082; // zf
  int fld_e17083; // eax
  int fld_e17084; // eax
  int v45; // eax
  int pObj; // edi
  bool v47; // bl
  int v48; // ebx
  int v49; // eax
  int v50; // eax
  int v51; // eax
  void *fld_e29; // ecx
  int v53; // eax
  int v54; // edi
  int v55; // ebx
  int v56; // eax
  int fld_e17085; // eax
  int fld_e30; // ecx  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  int fld_e17086; // eax
  uint32_t *pThis_6AE; // eax
  int fld_e304; // ecx  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  int v62; // edx
  int fld_e1547; // eax
  int fld_e1723; // eax
  int v65; // edx
  int v66; // ebx
  int v67; // edx
  uint32_t *pThis_6CD; // eax
  int v69; // eax
  int v70; // eax
  int v71; // edi
  int v72; // eax
  int v73; // eax
  int fld_e1718; // eax
  uint32_t *pThis_6BF; // eax
  int v76; // eax
  int v77; // eax
  int v78; // eax
  int v79; // eax
  int fld_e17182; // eax
  int fld_e1717; // ecx
  int fld_e17172; // eax
  uint32_t *pThis_6C6; // eax
  int pObj2; // edi
  bool v85; // bl
  int v86; // ebx
  int v87; // eax
  int v88; // eax
  int v89; // eax
  void *fld_e292; // ecx
  uint32_t *pThis_6D7; // eax
  uint32_t *pThis_6E2; // eax
  unsigned int pThis_6DD; // ebx
  int pThis_6DD2; // eax
  int pThis_6DD3; // eax
  int fld_e305; // ecx  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  int fld_e302; // ecx  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  uint32_t *pThis_651; // edi
  int i; // ebx
  int fld_e303; // eax  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  int v101; // edi
  int pThis_10; // ebx
  int nRand; // [esp+70h] [ebp-50h]
  int nRand2; // [esp+70h] [ebp-50h]
  int fld_e1540; // [esp+74h] [ebp-4Ch]
  float v107; // [esp+74h] [ebp-4Ch]
  uint8_t v108[16]; // [esp+84h] [ebp-3Ch] BYREF
  uint8_t v109[8]; // [esp+94h] [ebp-2Ch] BYREF
  double fld_e17053; // [esp+9Ch] [ebp-24h]
  int fld_e17087; // [esp+A4h] [ebp-1Ch]
  int fld_e16393; // [esp+A8h] [ebp-18h]
  int v113; // [esp+ACh] [ebp-14h]
  int v114; // [esp+B0h] [ebp-10h]
  int v115; // [esp+BCh] [ebp-4h]
  int v116; // [esp+CCh] [ebp+Ch]
  bool v117; // [esp+CFh] [ebp+Fh]
  float fld_e1671; // [esp+D0h] [ebp+10h]  | +0x1A1C → 出生复位槽（0x4D6970 清零）（证据 va=004D6970）（IRDActiveObject；va=004D6970）
  float v119; // [esp+D4h] [ebp+14h]
  float v120; // [esp+D4h] [ebp+14h]

  fld_e1639 = *(this + 1639);  // this+6556 = 主状态镜像
  v7 = *this;
  fld_e16393 = fld_e1639;
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v7 + 776))(this, 16) == 0  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
    || nArg2 != 6
    || *(uint32_t *)(fld_e16392 = *(uint32_t *)(pArg3 + 4)) != 0 )
  {
    if ( fld_e1639 != 0 )  // 若 fld_e1639 != 0
    {
      if ( fld_e1639 == 4 )  // 若 fld_e1639 == 4
        (*(void (/*thiscall*/ **)(int *, int))(*this + 776))(this, 3);  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
    }
    else
    {
      (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 1);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
    }
    switch ( nArg2 )  // 分支：按 nArg2 分派
    {
      case 0:
        v10 = *this;
        fld_e1540 = *(this + 1540);  // fld_e1540 = this+1540
        *((uint8_t *)this + 6752) = 1;
        (*(void (/*thiscall*/ **)(int *, int))(v10 + 196))(this, fld_e1540);  // 调用虚函数（虚表槽 +196）
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 0, 143, 119, 1, 0, 0);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
        (*(void (/*thiscall*/ **)(int *, int, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 1, 114, 95, 1, 0, 0);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        if ( *(this + 81) != 0 && (fld_e81 = *(this + 81) - (*(int (/*thiscall*/ **)(int *))(*this + 128))(this)) != 0 )  // this+324 = 购买上下文 id（0x550480: dword
        {
          sub_495890(0, fld_e81 <= 0 ? 1000 : -1000);  // 调 模式选择式方位设置（1/2/其他 三分支）
          sub_4A0550(fld_e81);  // 调 sub_4A0550
          sub_4A0600(2);  // 调 sub_4A0600
        }
        else
        {
          sub_494F20(2, 0.0);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
          sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
        }
        if ( fld_e16393 != 4 || (*(uint8_t *)(this + 162) & 2) == 0 )  // 若 fld_e16393 != 4 || (*(uint8_t *)(this + 162) & 2) == 0
          goto LABEL_152;  // 跳转 LABEL_152
        goto LABEL_15;  // 跳转 LABEL_15
      case 1:
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1542));  // 调用虚函数（虚表槽 +196）
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        sub_494F20(2, 0.0);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
        if ( fld_e16393 == 4 && (*(uint8_t *)(this + 162) & 2) != 0 )  // 若 fld_e16393 == 4 && (*(uint8_t *)(this + 162) & 2) != 0
        {
LABEL_15:
          sub_49C620(0, 1, 0);  // 调 命令下发包装（组 id = this+4，值重复两遍）
          sub_49C5F0(0, 0, 0, 500);  // 调 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
        }
        goto LABEL_152;  // 跳转 LABEL_152
      case 2:
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1542));  // 调用虚函数（虚表槽 +196）
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        sub_494F20(2, 0.0);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
        goto LABEL_152;  // 跳转 LABEL_152
      case 3:
        v12 = *this;
        *(this + 1689) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);  // this+6756 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8)
        v13 = *(int **)(pArg3 + 4);
        v14 = v13[3];
        v15 = *v13;
        fld_e16393 = v15;
        if ( v15 == 4 )  // 若 v15 == 4
          fld_e16393 = (*(int (/*thiscall*/ **)(int *))(v12 + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        else
          (*(void (/*thiscall*/ **)(int *, int))(v12 + 144))(this, v15);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
        v113 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
        if ( v113 == -1 )  // 若 v113 == -1
        {
          v16 = 333;
          v17 = 800;
          *(this + 1690) = 333;  // this+6760 = 333
        }
        else
        {
          if ( v14 == 2 )  // 若 v14 == 2
          {
            v17 = 1;
            v16 = 1;
          }
          else
          {
            v17 = 400;
            v16 = 150;
          }
          v18 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
          if ( 2000 - sub_58E6D0(v18) <= 0 )  // 调 食尸鬼族通用：41A5E0 粒子挂载（状态表现）
          {
            v116 = 0;
          }
          else
          {
            v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
            v116 = 2000 - sub_58E6D0(v19);  // 调 食尸鬼族通用：41A5E0 粒子挂载（状态表现）
          }
          v20 = (uint64_t)((double)v116 * 0.25);
          *(this + 1690) = v20;  // this+6760 = v20
          v21 = v113 * (int)v20 / 100;
          if ( v21 <= 1 )  // 若 v21 <= 1
            v21 = 1;
          *(this + 1690) = v21;  // this+6760 = v21
          if ( v16 > v21 )  // 若 v16 > v21
            v16 = v21;
        }
        v22 = -1000 * v17 / v16;
        if ( *((uint8_t *)this + 7144) == 0 )  // 若 *((uint8_t *)this + 7144) == 0
        {
          v17 = 0;
          v22 = 0;
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(this, 0, v17, v17, 0, v22, 1);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        sub_494F20(2, 0.0);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
        v23 = *this;
        v24 = sub_432E50(fld_e16393);  // 调 关系码对调映射
        (*(void (/*thiscall*/ **)(int *, int, int))(v23 + 896))(this, v24, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + *(this + 1689) + 1543));  // 调用虚函数（虚表槽 +196）
        goto LABEL_152;  // 跳转 LABEL_152
      case 4:
        v113 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        if ( **(uint32_t **)(pArg3 + 4) != 4 )  // 若 **(uint32_t **)(pArg3 + 4) != 4
          v113 = **(uint32_t **)(pArg3 + 4);
        v25 = *this;
        *(this + 1706) = 0;  // this+6824 = 0
        *(this + 1707) = (*(int (/*thiscall*/ **)(int *))(v25 + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        v26 = *this;
        *(this + 1705) = 0;  // this+6820 = 0
        v27 = (*(int (/*thiscall*/ **)(int *, int))(v26 + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
        v28 = sub_4B0D20(v27);  // 调 双字段乘积取值
        fld_e1708 = *(this + 1708);  // fld_e1708 = this+1708
        v30 = v28;
        v31 = *(uint32_t *)(pArg3 + 4);  // v31 = pArg3+4
        v32 = *(uint32_t *)(v31 + 8);  // v32 = v31+8
        v33 = *(uint32_t *)(v31 + 4);  // v33 = v31+4
        HIDWORD(fld_e17053) = v30;  // 调 取 64 位值高 32 位
        v117 = v32 == 1;
        fld_e17087 = fld_e1708;
        *(this + 1708) = v33;  // this+6832 = v33
        if ( v32 == 1 )  // 若 v32 == 1
        {
          v34 = *(uint32_t *)(pArg3 + 4);  // v34 = pArg3+4
          v35 = *(uint32_t *)(v34 + 12);  // v35 = v34+12
          v36 = *(uint32_t *)(v34 + 16);  // v36 = v34+16
          *(this + 1705) = (uint64_t)sub_495430(v35, v30);  // 调 时间轴坐标换算（毫秒 → 刻度）
          v37 = (uint64_t)sub_495430(v36, v30);  // 调 时间轴坐标换算（毫秒 → 刻度）
          fld_e1705 = *(this + 1705) / 2;
          *(this + 1705) = fld_e1705;  // this+6820 = fld_e1705
          if ( fld_e1705 < 0 )  // 若 fld_e1705 < 0
          {
            v39 = sub_432E50(v113);  // 调 关系码对调映射
            fld_e17052 = -*(this + 1705);
            v113 = v39;
            *(this + 1705) = fld_e17052;  // this+6820 = fld_e17052
          }
          v41 = v37 * v37 / (-2 * sub_4957F0(1));  // 调 方位基数求解（-1500 基准 + 956×970 比例折算）
          v114 = v41;
          if ( v37 < 0 )  // 若 v37 < 0
          {
            v41 = -v41;
            v114 = v41;
          }
          (*(void (/*thiscall*/ **)(int *, int))(*this + 144))(this, v113);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
          if ( *(this + 1708) == 1 && v37 > 0 && v41 < 1 )  // 若 *(this + 1708) == 1 && v37 > 0 && v41 < 1
          {
            v41 = 1;
            v114 = 1;
          }
        }
        else
        {
          *(this + 1705) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12) / 2;  // this+6820 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 1..
          fld_e17082 = *(this + 1708) == 1;
          v41 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 16);
          v114 = v41;
          if ( fld_e17082 && v41 <= 0 && (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) <= 0 )  // 调用虚函数（虚表槽 +128）
          {
            *(this + 1708) = 2;  // this+6832 = 2
            byte_9B9324 = 1;
          }
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1545));  // 调用虚函数（虚表槽 +196）
        fld_e17083 = *(this + 1708);  // fld_e17083 = this+1708
        if ( fld_e17083 == 0 )  // 若 fld_e17083 == 0
          goto LABEL_66;  // 跳转 LABEL_66
        if ( fld_e17083 == 1 )  // 若 fld_e17083 == 1
        {
          if ( fld_e16393 == 4 && fld_e17087 >= 1 )  // 若 fld_e16393 == 4 && fld_e17087 >= 1
            v114 = v41 / 4;
          if ( !v117 )  // 若 !v117
          {
            if ( SHIDWORD(fld_e17053) > 60000 )  // 调 取 64 位值高 32 位(带符号)
            {
              if ( SHIDWORD(fld_e17053) > 100000 )  // 调 取 64 位值高 32 位(带符号)
                (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(*this + 212))("DOWN_HEAVY", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
              else
                (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(*this + 212))("DOWN_MIDDLE", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
            }
            else
            {
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                this,
                "DOWN_LIGHT",
                -1,
                0,
                0);
            }
LABEL_67:
            fld_e17084 = *(this + 1708);  // fld_e17084 = this+1708
            if ( (fld_e17084 == 1 || fld_e17084 == 2) && *(this + 29) != 0 )  // 若 (fld_e17084 == 1 || fld_e17084 == 2) && *(this + 29) != 0
            {
              if ( fld_e17084 == 1 )  // 若 fld_e17084 == 1
                v45 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 924))(this, 0);  // 调用虚函数（虚表槽 +924）
              else
                v45 = (*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 1);  // 调用虚函数（虚表槽 +924）
              pObj = dword_8F8270[v45];  // dword_8F8270 = 全局效果管理器
              v47 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj) + 84) = v47;  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
              v48 = *(uint32_t *)pObj;  // v48 = pObj
              v49 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
              v50 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v49);  // 调用虚函数（虚表槽 +124）
              v51 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v50);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              (*(void (/*thiscall*/ **)(int, int))(v48 + 40))(pObj, v51);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);  // 调用虚函数（虚表槽 +12）
              (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj + 92))(pObj, v109);  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
              fld_e29 = (void *)*(this + 29);
              v115 = 0;
              sub_4600B0(fld_e29, 2, 0, (int)v109);  // 调 sub_4600B0
              v115 = -1;
              sub_5E5260(v109);  // 调 sub_5E5260
            }
          }
        }
        else
        {
          if ( fld_e17083 == 2 )  // 若 fld_e17083 == 2
          {
            *(this + 1705) = 0;  // this+6820 = 0
            v114 = 0;
          }
LABEL_66:
          if ( !v117 )  // 若 !v117
            goto LABEL_67;  // 跳转 LABEL_67
        }
        sub_432FA0();  // 调 srand 播种
        fld_e17053 = (double)*(this + 1705);
        nRand = rand() % 1000;  // 调 以 16 位种子状态递推并返回 15 位结果
        v53 = sub_423A80((uint64_t)(fld_e17053 * 0.8), (uint64_t)(fld_e17053 * 1.2), nRand, 999);  // 调 区间线性插值取整
        fld_e17053 = (double)v114;
        *(this + 1705) = v53;  // this+6820 = v53
        nRand2 = rand() % 1000;  // 调 以 16 位种子状态递推并返回 15 位结果
        v54 = sub_423A80((uint64_t)(fld_e17053 * 0.9), (uint64_t)(fld_e17053 * 1.1), nRand2, 999);  // 调 区间线性插值取整
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          *(this + 1705),
          *(this + 1705),
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        v55 = *this;
        v56 = sub_432E50(v113);  // 调 关系码对调映射
        (*(void (/*thiscall*/ **)(int *, int, int))(v55 + 896))(this, v56, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        sub_495890(1, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 40))(this, 529) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
          && (uint8_t)sub_4DB0E0(196626) != 0 )
        {
          v54 = 0;
        }
        sub_4A0550(v54);  // 调 sub_4A0550
        fld_e17085 = *(this + 1708);  // fld_e17085 = this+1708
        if ( fld_e17085 == 1 || fld_e17085 == 2 )  // 若 fld_e17085 == 1 || fld_e17085 == 2
        {
          fld_e30 = *(this + 30);  // this+120 = 动画对象指针
          if ( fld_e30 == 0 )  // 若 fld_e30 == 0
            goto LABEL_84;  // 跳转 LABEL_84
          sub_4939E0(fld_e30, 0);  // 调 播放/暂停级联（递归子链 +204）
          fld_e17086 = *(this + 1708);  // fld_e17086 = this+1708
          if ( fld_e17086 == 1 )  // 若 fld_e17086 == 1
          {
            sub_4AECE0(*(this + 1700));  // this+6800 = 炮车/子类参数面槽 3
            LOBYTE(fArg5) = 0;  // 调 取 16 位值低 8 位
          }
          else
          {
            if ( fld_e17086 == 2 )  // 若 fld_e17086 == 2
              sub_4AECE0(*(this + 1702));  // this+6808 = 炮车/子类参数面槽 5
LABEL_84:
            LOBYTE(fArg5) = 0;  // 调 取 16 位值低 8 位
          }
        }
LABEL_152:
        if ( LOBYTE(fArg4) != 0 )  // 调 取 16 位值低 8 位
        {
          *((uint8_t *)this + 6573) = 0;
          *((uint8_t *)this + 6574) = 0;
          sub_698F90((int)(this + 1640), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        }
LABEL_154:
        if ( LOBYTE(fArg5) != 0 )  // 调 取 16 位值低 8 位
        {
          fld_e302 = *(this + 30);  // this+120 = 动画对象指针
          if ( fld_e302 != 0 )  // 若 fld_e302 != 0
          {
            sub_4926A0(fld_e302);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
            sub_4910E0(*(this + 30));  // 调 帧时刻推进（返回 1 表示时刻发生位移）
          }
        }
LABEL_157:
        *(this + 1639) = nArg2;  // this+6556 = 主状态镜像
        pThis_651 = this + 1617;
        for ( i = 18; i != 0; --i )  // 循环：i = 18; i != 0; --i
        {
          if ( *pThis_651 != 0 )  // 若 *pThis_651 != 0
            (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*pThis_651 + 156))(*pThis_651, nArg2);  // 调用虚函数（虚表槽 +156）【推断: 与目标 x/y 距离绝对值】
          ++pThis_651;  // 自增pThis_651
        }
        LOBYTE(fld_e16392) = *((uint8_t *)this + 6681);  // 调 取 16 位值低 8 位
        if ( (uint8_t)fld_e16392 != 0 )  // 若 (uint8_t)fld_e16392 != 0
        {
          if ( *(this + 1639) == 4 && *(this + 1708) == 2 )  // this+6556 = 主状态镜像
          {
            if ( *((uint8_t *)this + 6682) == 0 )  // 若 *((uint8_t *)this + 6682) == 0
            {
              *(this + 1671) = 0;  // this+6684 = 0
              *(this + 1672) = -1;  // this+6688 = -1
              *((uint8_t *)this + 6682) = 1;
            }
            fld_e1671 = (double)*(this + 1671) * 100.0;
            if ( fld_e1671 / (double)(*(int (/*thiscall*/ **)(int *))(*this + 740))(this) > 15.0 && *(this + 1672) == -1 )  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
            {
              fld_e303 = *(this + 30);  // this+120 = 动画对象指针
              if ( *(uint32_t *)(fld_e303 + 212) != 0 )  // 若 *(uint32_t *)(fld_e303 + 212) != 0
                v101 = sub_4910A0();  // 调 沿 +212 同步源链上溯，返回链尾对象的累计播放时刻（+32）
              else
                v101 = *(uint32_t *)(fld_e303 + 32);  // v101 = fld_e303+32
              pThis_10 = sub_699000((int)(this + 16)) - v101;  // 【clock_now(clk)】
              *(this + 1672) = sub_491C10(*(this + 30)) + pThis_10;  // 调 遍历帧数组（首+44/尾+48，步长 88）
            }
          }
          fld_e16392 = *(this + 1639);  // this+6556 = 主状态镜像
          if ( fld_e16392 != 4 && fld_e16392 != 9 )  // 若 fld_e16392 != 4 && fld_e16392 != 9
          {
            LOBYTE(fld_e16392) = *((uint8_t *)this + 6682);  // 调 取 16 位值低 8 位
            if ( (uint8_t)fld_e16392 != 0 )  // 若 (uint8_t)fld_e16392 != 0
            {
              *(this + 1671) = 0;  // this+6684 = 0
              *(this + 1672) = -1;  // this+6688 = -1
              *((uint8_t *)this + 6682) = 0;
            }
          }
        }
        break;
      case 5:
        sub_53FC90(*(this + 1574));  // 调 sub_53FC90
        if ( (unsigned int)*(this + 1715) < 0x10 )  // 若 (unsigned int)*(this + 1715) < 0x10
          pThis_6AE = this + 1710;
        else
          pThis_6AE = (uint32_t *)*(this + 1710);
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_6AE, -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 216))(this, 0);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);  // 调用虚函数（虚表槽 +596）【推断: [RTTI: IRDCollisionObject__vmt25…】
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
        fld_e304 = *(this + 30);  // this+120 = 动画对象指针
        LOBYTE(fArg5) = 0;  // 调 取 16 位值低 8 位
        if ( fld_e304 != 0 )  // 若 fld_e304 != 0
          sub_4939E0(fld_e304, 1);  // 调 播放/暂停级联（递归子链 +204）
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 40))(this, 529) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
          && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1020))(this) == 0 )  // 调用虚函数（虚表槽 +1020）
        {
          if ( *(uint32_t *)(dword_8F7A24 + 244) == 2 )  // dword_8F7A24 = 当前场景状态对象
          {
            if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 688))(this) + 20) != 0  // 调用虚函数（虚表槽 +688）【推断: [RTTI: IRDActiveObject__vmt2B0 ·…】
              && *(this + 81) <= 0  // this+324 = 购买上下文 id（0x550480: dword
              && ((*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 4 || byte_9B9324 == 1) )  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
            {
              (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1545));  // 调用虚函数（虚表槽 +196）
              if ( **(uint32_t **)(pArg3 + 4) == 4 )  // 若 **(uint32_t **)(pArg3 + 4) == 4
                (*(void (/*thiscall*/ **)(int *, int))(*this + 144))(this, 4);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
              else
                (*(void (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              v107 = (float)(200 * ((*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 ? -1 : 1));  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              sub_494F20(0, v107);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
              sub_494F20(2, 400.0);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
              byte_9B9324 = 0;
            }
          }
          else
          {
            sub_494F20(2, 0.0);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
            sub_495890(0, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
          }
        }
        goto LABEL_152;  // 跳转 LABEL_152
      case 6:
        if ( fld_e16393 != 6 )  // 若 fld_e16393 != 6
          sub_495470(0);  // 调 条件写时间槽（+6668 开关为真才写 +6672）
        v62 = *this;
        *(this + 1723) = **(uint32_t **)(pArg3 + 4);  // this+6892 = **(uint32_t **)(pArg3 + 4)
        fld_e1547 = *(this + 1547);  // fld_e1547 = this+1547
        *((uint8_t *)this + 6988) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4) != 0;
        (*(void (/*thiscall*/ **)(int *, int))(v62 + 196))(this, fld_e1547);  // 调用虚函数（虚表槽 +196）
        fld_e1723 = *(this + 1723);  // fld_e1723 = this+1723
        if ( fld_e1723 == 0 )  // 若 fld_e1723 == 0
        {
          v65 = *this;
          *(this + 1719) = 143;  // this+6876 = 143
          *(this + 1720) = 119;  // this+6880 = 119
          *(this + 1721) = 114;  // this+6884 = 114
          *(this + 1722) = 95;  // this+6888 = 95
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v65 + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
            this,
            1,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
          (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
          sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
          *((uint8_t *)this + 6996) = 0;
          goto LABEL_152;  // 跳转 LABEL_152
        }
        if ( fld_e1723 == 1 )  // 若 fld_e1723 == 1
        {
          v66 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);
          v67 = *this;
          if ( *((uint8_t *)this + 6988) != 0 )  // 若 *((uint8_t *)this + 6988) != 0
          {
            (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v67 + 212))(this, "JUMP_START", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
            if ( (unsigned int)*(this + 1746) < 0x10 )  // 若 (unsigned int)*(this + 1746) < 0x10
              pThis_6CD = this + 1741;
            else
              pThis_6CD = (uint32_t *)*(this + 1741);
            (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_6CD, -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
            v69 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 672))(this, 3, 100);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
            v70 = sub_4B0D20(v69);  // 调 双字段乘积取值
            v119 = sub_495430(v66, v70);  // 调 时间轴坐标换算（毫秒 → 刻度）
            sub_494F20(2, v119);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
            (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t))(*this + 876))(this, 0, 286, 286, 0, 0);  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
              this,
              1,
              0,
              0,
              0,
              0,
              0);
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
            v71 = *this;
            v72 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            v73 = sub_432E50(v72);  // 调 关系码对调映射
            (*(void (/*thiscall*/ **)(int *, int))(v71 + 896))(this, v73);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1547));  // 调用虚函数（虚表槽 +196）
            sub_4939E0(*(this + 30), 1);  // 调 播放/暂停级联（递归子链 +204）
            fld_e1718 = *(this + 1718) - 1;
            if ( *(this + 1717) > fld_e1718 )  // 若 *(this + 1717) > fld_e1718
              fld_e1718 = *(this + 1717);  // fld_e1718 = this+1717
            sub_4AECE0(fld_e1718);  // 调 sub_4AECE0
          }
          else
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t))(v67 + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
              this,
              0,
              *(this + 1719),
              *(this + 1720),
              1,
              0,
              0);
            (*(void (/*thiscall*/ **)(int *, int, int, int, int, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
              this,
              1,
              *(this + 1721) / 2,
              *(this + 1722) / 2,
              1,
              0,
              0);
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
            if ( v66 != 0 )  // 若 v66 != 0
            {
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                this,
                "JUMP_START",
                -1,
                0,
                0);
              if ( (unsigned int)*(this + 1732) < 0x10 )  // 若 (unsigned int)*(this + 1732) < 0x10
                pThis_6BF = this + 1727;
              else
                pThis_6BF = (uint32_t *)*(this + 1727);
              (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t))(*this + 212))(this, pThis_6BF, -1, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
              v76 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
              v77 = sub_495580(v76);  // 调 槽对乘积读取（+956/+970）
              v78 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 672))(this, 3, v77);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
              v79 = sub_4B0D20(v78);  // 调 双字段乘积取值
              v120 = sub_495430(v66, v79);  // 调 时间轴坐标换算（毫秒 → 刻度）
              sub_494F20(2, v120);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
              sub_4939E0(*(this + 30), 0);  // 调 播放/暂停级联（递归子链 +204）
              sub_4AECE0(*(this + 1716));  // 调 sub_4AECE0
            }
            else
            {
              sub_4939E0(*(this + 30), 0);  // 调 播放/暂停级联（递归子链 +204）
              if ( *(float *)(*(this + 28) + 24) <= 0.0 )  // this+112 = pHostComp
              {
                fld_e17182 = *(this + 1718);  // fld_e17182 = this+1718
                fld_e1717 = *(this + 1717);  // fld_e1717 = this+1717
              }
              else
              {
                fld_e17182 = *(this + 1717);  // fld_e17182 = this+1717
                fld_e1717 = *(this + 1716);  // fld_e1717 = this+1716
              }
              fld_e17172 = fld_e17182 - 1;
              if ( fld_e1717 > fld_e17172 )  // 若 fld_e1717 > fld_e17172
                fld_e17172 = fld_e1717;
              sub_4AECE0(fld_e17172);  // 调 sub_4AECE0
            }
            LOBYTE(fArg4) = 0;  // 调 取 16 位值低 8 位
          }
          LOBYTE(fArg5) = 0;  // 调 取 16 位值低 8 位
          if ( *((uint8_t *)this + 6988) != 0 )  // 若 *((uint8_t *)this + 6988) != 0
            sub_495890(1, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
          else
            sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
          if ( v66 > 0 )  // 若 v66 > 0
          {
            *(this + 1724) = 0;  // this+6896 = 0
            *(this + 1725) = 1;  // this+6900 = 1
          }
          goto LABEL_152;  // 跳转 LABEL_152
        }
        if ( fld_e1723 != 2 )  // 若 fld_e1723 != 2
          goto LABEL_152;  // 跳转 LABEL_152
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "JUMP_END", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        if ( (unsigned int)*(this + 1739) < 0x10 )  // 若 (unsigned int)*(this + 1739) < 0x10
          pThis_6C6 = this + 1734;
        else
          pThis_6C6 = (uint32_t *)*(this + 1734);
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_6C6, -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        if ( *(this + 29) != 0 )  // 若 *(this + 29) != 0
        {
          pObj2 = dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 1)];  // 调用虚函数（虚表槽 +924）
          v85 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 28))(pObj2) + 84) = v85;  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
          v86 = *(uint32_t *)pObj2;  // v86 = pObj2
          v87 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
          v88 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v87);  // 调用虚函数（虚表槽 +124）
          v89 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v88);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          (*(void (/*thiscall*/ **)(int, int))(v86 + 40))(pObj2, v89);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);  // 调用虚函数（虚表槽 +12）
          (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj2 + 92))(pObj2, v108);  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
          fld_e292 = (void *)*(this + 29);
          v115 = 1;
          sub_4600B0(fld_e292, 2, 0, (int)v108);  // 调 sub_4600B0
          v115 = -1;
          sub_5E5260(v108);  // 调 sub_5E5260
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
        sub_4939E0(*(this + 30), 0);  // 调 播放/暂停级联（递归子链 +204）
        sub_4AECE0(*(this + 1718));  // 调 sub_4AECE0
        goto LABEL_157;  // 跳转 LABEL_157
      case 7:
        if ( (unsigned int)*(this + 1756) < 0x10 )  // 若 (unsigned int)*(this + 1756) < 0x10
          pThis_6D7 = this + 1751;
        else
          pThis_6D7 = (uint32_t *)*(this + 1751);
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_6D7, -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1548));  // 调用虚函数（虚表槽 +196）
        (*(void (/*thiscall*/ **)(int *, int *))(*this + 344))(this, this + 1579);  // 调用虚函数（虚表槽 +344）
        (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, 1, 3, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        ++*(this + 1724);
        goto LABEL_154;  // 跳转 LABEL_154
      case 8:
        if ( (unsigned int)*(this + 1767) < 0x10 )  // 若 (unsigned int)*(this + 1767) < 0x10
          pThis_6E2 = this + 1762;
        else
          pThis_6E2 = (uint32_t *)*(this + 1762);
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_6E2, -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
        sub_41A590(**(uint32_t **)(pArg3 + 4));  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
        pThis_6DD = sub_41A5E0(this + 1757);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        if ( sub_4B0BC0(this + 1575) > pThis_6DD )  // 调 记录数统计（152 字节/条）
        {
          pThis_6DD2 = sub_41A5E0(this + 1757);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
          (*(void (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 1576) + 152 * pThis_6DD2);  // 调用虚函数（虚表槽 +344）
        }
        pThis_6DD3 = sub_41A5E0(this + 1757);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1550) + 4 * pThis_6DD3));  // 调用虚函数（虚表槽 +196）
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        sub_494F20(2, 0.0);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
        goto LABEL_152;  // 跳转 LABEL_152
      case 9:
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1543));  // 调用虚函数（虚表槽 +196）
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调用虚函数（虚表槽 +876）【推断: 参数组写入（+6608 族 5 元组 + 转发 vt+892）】
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调用虚函数（虚表槽 +896）【推断: IRDCharacter__vmt380 默认虚槽桩（11 行 …】
        fld_e305 = *(this + 30);  // this+120 = 动画对象指针
        if ( fld_e305 != 0 )  // 若 fld_e305 != 0
        {
          sub_4926A0(fld_e305);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
          sub_4939E0(*(this + 30), 1);  // 调 播放/暂停级联（递归子链 +204）
        }
        LOBYTE(fArg5) = 0;  // 调 取 16 位值低 8 位
        sub_495890(2, 0);  // 调 模式选择式方位设置（1/2/其他 三分支）
        sub_494F20(2, 0.0);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, 16) != 0 )  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
            this,
            "CONDITION_STUN",
            -1,
            0,
            0);
        goto LABEL_152;  // 跳转 LABEL_152
      default:
        goto LABEL_152;  // 跳转 LABEL_152
    }
  }
  return fld_e16392;  // | +0x199C → nMainState6556〔族字典〕（族字典）
}


// ------------------------------------------------------------
// 0x58FC30 IRDActiveObject__vmt14C —— IRDActiveObject__vmt14C 行走动画（505 行）：G_WALK_FLOOR_LOOP/WALK_SOIL_LOOP/WALK_STONE_LOOP 按地面材质分支
// ------------------------------------------------------------
void /*thiscall*/ sub_58FC30(uint32_t *this)  // 【IRDActiveObject__vmt14C】
{
  int v2; // eax
  uint32_t *pThis_49; // eax
  int fld_e1639; // ecx  | +0x199C → nMainState6556〔族字典〕（族字典）
  int fld_e154; // eax  | +0x0268 → 受击反应态（IRDActiveObject）
  bool fld_e1545; // zf  | +0x1824 → 攻击上下文三连槽 C（0x4D6970）（证据 va=004D6970）（IRDActiveObject；va=004D6970）
  int pThis_5FD; // eax
  int pThis_1802; // eax
  uint32_t *pThis_615; // edi
  int i; // ebx
  int fld_e1661; // eax
  int fld_e1662; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edx
  int fld_e30; // ecx  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  int v17; // eax
  int fld_e302; // ecx  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  int v19; // eax
  int pObj; // edi
  bool v21; // bl
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  void *fld_e29; // ecx
  int pThis_6F32; // ecx
  int fld_e1708; // eax
  uint32_t *fld_e306; // ecx
  int fld_e1698; // eax  | +0x1A88 → nVoiceParam0〔族字典〕（族字典）
  double v31; // st7
  int fld_e282; // ecx  | +0x0070 → 宿主对象指针（IRDActiveObject；va=004D6970）
  uint32_t *fld_e304; // ecx
  int fld_e1700; // eax  | +0x1A90 → nVoiceParam2〔族字典〕（族字典）
  int fld_e28; // ecx  | +0x0070 → 宿主对象指针（IRDActiveObject；va=004D6970）
  int fld_e1542; // eax  | +0x0268 → 受击反应态（IRDActiveObject）
  int fld_e305; // eax  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  int fld_e1723; // eax
  int fld_e309; // eax  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  int v40; // eax
  uint32_t *fld_e307; // ecx
  int fld_e283; // ecx  | +0x0070 → 宿主对象指针（IRDActiveObject；va=004D6970）
  int fld_e308; // eax  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  int fld_e3010; // eax  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  int fld_e303; // eax  | +0x0078 → 基类动画对象指针（IRDActiveObject；va=00499020）
  float v46; // [esp+44h] [ebp-40h]
  void *v47[4]; // [esp+54h] [ebp-30h] BYREF
  void *v48; // [esp+64h] [ebp-20h] BYREF
  int v49; // [esp+68h] [ebp-1Ch]
  int v50; // [esp+6Ch] [ebp-18h]
  int v51; // [esp+70h] [ebp-14h]
  int pThis_6F3; // [esp+74h] [ebp-10h] BYREF
  int v53; // [esp+80h] [ebp-4h]

  sub_4E5410();  // 调 ★ 位置采样 vt+14C（每 100ms 节流，双缓冲）
  if ( *(this + 40) == -1 )  // 若 *(this + 40) == -1
  {
    if ( *(this + 1540) != 0 )  // 若 *(this + 1540) != 0
    {
      v2 = sub_4924C0(0);  // 调 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      *(this + 40) = sub_4918E0(v2, 2);  // 调 动画盒四边界提取（研究 P29 族）
    }
    else
    {
      if ( *(this + 78) < 0x10u )  // 若 *(this + 78) < 0x10u
        pThis_49 = this + 73;
      else
        pThis_49 = (uint32_t *)*(this + 73);
      off_77F3FC(aStay, pThis_49);  // 调 off_77F3FC（引擎日志输出函数）
      *(this + 40) = 0;  // this+160 = 0
    }
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    goto LABEL_25;  // 跳转 LABEL_25
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
    goto LABEL_25;  // 跳转 LABEL_25
  fld_e1639 = *(this + 1639);  // this+6556 = 主状态镜像
  if ( fld_e1639 == 4 )  // 若 fld_e1639 == 4
    goto LABEL_25;  // 跳转 LABEL_25
  fld_e154 = *(this + 154);  // fld_e154 = this+154
  if ( fld_e154 == 4 || fld_e1639 == 5 || fld_e154 == 5 || fld_e1639 == 9 || fld_e154 == 9 )  // 若 fld_e154 == 4 || fld_e1639 == 5 || fld_e154 == 5 || fld_e1639 ..
    goto LABEL_25;  // 跳转 LABEL_25
  v49 = 0;
  v50 = 0;
  v51 = 0;
  fld_e1545 = *(this + 1545) == 0;
  v53 = 0;
  if ( fld_e1545 )  // 若 fld_e1545
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 529) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      pThis_6F3 = 2;
    }
    else
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 273) == 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
      {
LABEL_23:
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 5, &v48, 2, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        goto LABEL_24;  // 跳转 LABEL_24
      }
      pThis_6F3 = 0;
    }
    sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
    goto LABEL_23;  // 跳转 LABEL_23
  }
  pThis_6F3 = 4;
  sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
  pThis_6F3 = 0;
  sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
  pThis_6F3 = 1;
  sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
  sub_431230((int)&v48, &dword_72D3FC);  // 调 uint32 vector push_back
  sub_431230((int)&v48, &dword_72D400);  // 调 uint32 vector push_back
  (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 4, &v48, 2, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
LABEL_24:
  v53 = -1;
  sub_5E5260(&v48);  // 调 sub_5E5260
LABEL_25:
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) != 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);  // 调用虚函数（虚表槽 +596）【推断: [RTTI: IRDCollisionObject__vmt25…】
  sub_495920(this);  // 调 状态 4/9 超时偏移重算（+1639 门控 → +1669）
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 960))(this);  // 调用虚函数（虚表槽 +960）
  if ( *(this + 1650) != -1 && sub_699000((int)(this + 2)) > *(this + 1650) + 1000 )  // 【clock_now(clk)】
  {
    pThis_5FD = sub_41A5E0((unsigned int)(this + 1533));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 728))(this, pThis_5FD, 1, 0);  // 调用虚函数（虚表槽 +728）【推断: ★★ HP setter / DMGAPPLY vt+728（研…】
  }
  if ( *(this + 1651) != -1 && sub_699000((int)(this + 2)) > *(this + 1651) + 1000 )  // 【clock_now(clk)】
  {
    pThis_1802 = sub_41A5E0((unsigned int)this + 6146);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 744))(this, pThis_1802, 1);  // 调用虚函数（虚表槽 +744）【推断: MP setter vt+748（HP setter 0x4D4…】
  }
  pThis_615 = this + 1557;
  for ( i = 17; i != 0; --i )  // 循环：i = 17; i != 0; --i
  {
    if ( *pThis_615 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)*pThis_615 + 24))() != 0 )  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_615 + 44))(*pThis_615);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
    ++pThis_615;  // 自增pThis_615
  }
  sub_53FF00(*(this + 1574));  // 调 sub_53FF00
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 676))(this, 2);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  if ( *(this + 1661) != 0 )  // 若 *(this + 1661) != 0
  {
    fld_e1661 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 976))(this, *(this + 1661));  // 调用虚函数（虚表槽 +976）
    if ( fld_e1661 != *(this + 1663) )  // 若 fld_e1661 != *(this + 1663)
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 980))(this, fld_e1661);  // 调用虚函数（虚表槽 +980）
  }
  if ( *(this + 1662) != 0 )  // 若 *(this + 1662) != 0
  {
    fld_e1662 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 976))(this, *(this + 1662));  // 调用虚函数（虚表槽 +976）
    if ( fld_e1662 != *(this + 1664) )  // 若 fld_e1662 != *(this + 1664)
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 984))(this, fld_e1662);  // 调用虚函数（虚表槽 +984）
  }
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 972))(this);  // 调用虚函数（虚表槽 +972）
  v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this);  // 调用虚函数（虚表槽 +184）【推断: 动画对象 z 倾斜转状态码】
  v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 188))(this);  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
  switch ( *(this + 1639) )  // this+6556 = 主状态镜像
  {
    case 0:
      if ( *(this + 50) == 0 )  // 若 *(this + 50) == 0
      {
        if ( v13 == 4 && v14 == 4 )  // 若 v13 == 4 && v14 == 4
        {
          if ( *((uint8_t *)this + 6752) == 0 )  // 若 *((uint8_t *)this + 6752) == 0
          {
            v15 = *this;
            *((uint8_t *)this + 6752) = 1;
            (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, int))(v15 + 888))(this, 1, 0, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(this + 1540));  // 调用虚函数（虚表槽 +196）
            fld_e30 = *(this + 30);  // this+120 = 动画对象指针
            if ( fld_e30 != 0 )  // 若 fld_e30 != 0
              sub_4926A0(fld_e30);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 1);  // 调用虚函数（虚表槽 +216）【推断: 音效 TAG 查询】
          }
        }
        else
        {
          if ( *((uint8_t *)this + 6752) != 0 )  // 若 *((uint8_t *)this + 6752) != 0
          {
            v17 = *this;
            *((uint8_t *)this + 6752) = 0;
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(v17 + 888))(this, 1, 1, 1000, 1000);  // 调用虚函数（虚表槽 +888）【推断: 速率设置链: a2/a3 经 vt+976 换算 → vt+98…】
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(this + 1541));  // this+6164 = 帧游标对象槽
            fld_e302 = *(this + 30);  // this+120 = 动画对象指针
            if ( fld_e302 != 0 )  // 若 fld_e302 != 0
              sub_4926A0(fld_e302);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 273) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
            {
              if ( dword_9A012C != 0 )  // 若 dword_9A012C != 0
              {
                (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                  this,
                  "G_WALK_FLOOR_LOOP",
                  1,
                  0,
                  0);
              }
              else
              {
                v19 = **(uint32_t **)(*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 80))(this) + 132) + 108);  // 调用虚函数（虚表槽 +80）
                if ( v19 < 11 || v19 > 26 )  // 若 v19 < 11 || v19 > 26
                  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                    this,
                    "WALK_SOIL_LOOP",
                    1,
                    0,
                    0);
                else
                  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
                    this,
                    "WALK_STONE_LOOP",
                    1,
                    0,
                    0);
              }
            }
          }
          if ( *(this + 1772) == 7 && *(this + 29) != 0 )  // 若 *(this + 1772) == 7 && *(this + 29) != 0
          {
            pThis_6F3 = (int)(this + 1779);
            if ( (uint8_t)sub_41C6E0(this + 1779) != 0 )  // 调 超时判定（clock_now(clk) >= this+24 截止时刻）
            {
              pObj = dword_8F8270[(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 924))(this, 2)];  // 调用虚函数（虚表槽 +924）
              v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0;  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj) + 84) = v21;  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
              v22 = *(uint32_t *)pObj;  // v22 = pObj
              v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
              v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v23);  // 调用虚函数（虚表槽 +124）
              v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v24);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
              (*(void (/*thiscall*/ **)(int, int))(v22 + 40))(pObj, v25);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);  // 调用虚函数（虚表槽 +12）
              (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj + 92))(pObj, v47);  // 调用虚函数（虚表槽 +92）【推断: 设置伤害数值；上次值非 0 时转发 vt+196】
              fld_e29 = (void *)*(this + 29);
              v53 = 1;
              sub_4600B0(fld_e29, 2, 0, (int)v47);  // 调 sub_4600B0
              pThis_6F32 = pThis_6F3;
              *(uint8_t *)(pThis_6F3 + 13) = 0;  // pThis_6F3+13 = 0
              *(uint8_t *)(pThis_6F32 + 14) = 0;  // pThis_6F32+14 = 0
              sub_698F90(pThis_6F32, 200, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
              sub_5E5260(v47);  // 调 sub_5E5260
            }
          }
        }
      }
      return;
    case 1:
    case 8:
      fld_e303 = *(this + 30);  // this+120 = 动画对象指针
      if ( fld_e303 != 0 && *(uint8_t *)(fld_e303 + 170) != 0 )  // 若 fld_e303 != 0 && *(uint8_t *)(fld_e303 + 170) != 0
        goto LABEL_156;  // 跳转 LABEL_156
      return;
    case 3:
      if ( sub_699000((int)(this + 1640)) >= *(this + 1690) )  // 【clock_now(clk)】
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 3) == 0 )  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
          goto LABEL_145;  // 跳转 LABEL_145
        (*(void (/*stdcall*/ **)(int, uint32_t, int, uint32_t))(*this + 560))(9, 0, 2, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
      }
      return;
    case 4:
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) > *(this + 1706) )  // 调用虚函数（虚表槽 +128）
        *(this + 1706) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调用虚函数（虚表槽 +128）
      fld_e1708 = *(this + 1708);  // fld_e1708 = this+1708
      if ( fld_e1708 != 0 )  // 若 fld_e1708 != 0
      {
        if ( fld_e1708 == 1 )  // 若 fld_e1708 == 1
        {
          fld_e304 = (uint32_t *)*(this + 30);  // this+120 = 动画对象指针
          if ( fld_e304 != nullptr && *(float *)(*(this + 28) + 24) <= 0.0 )  // this+112 = pHostComp
          {
            fld_e1700 = *(this + 1700);  // this+6800 = 炮车/子类参数面槽 3
            if ( fld_e304[37] == fld_e1700 && fld_e1700 != *(this + 1701) )  // this+6804 = 炮车/子类参数面槽 4
              sub_4AECE0(fld_e304, fld_e1700 + 1);  // 调 sub_4AECE0
          }
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
          {
            fld_e28 = *(this + 28);  // this+112 = pHostComp
            if ( *(float *)(fld_e28 + 24) < 0.0 && *(uint32_t *)(fld_e28 + 192) == 4 && *(this + 50) == 0 )  // 若 *(float *)(fld_e28 + 24) < 0.0 && *(uint32_t *)(fld_e28 + 192)..
            {
              if ( *(this + 1672) == -1
                || sub_699000((int)(this + 16)) < *(this + 1672)  // 【clock_now(clk)】
                || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) != 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
              {
                v49 = 0;
                v50 = 0;
                v51 = 0;
                v53 = 3;
                pThis_6F3 = 4;
                sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
                pThis_6F3 = 2;
                sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
                pThis_6F3 = 0;
                sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
                pThis_6F3 = 0;
                sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
                pThis_6F3 = 0;
                sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
                (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 4, &v48, 2, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
                sub_5E5260(&v48);  // 调 sub_5E5260
                return;
              }
              goto LABEL_115;  // 跳转 LABEL_115
            }
          }
        }
        else if ( fld_e1708 == 2 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) != 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
          {
            fld_e1542 = *(this + 154);  // fld_e1542 = this+154
            if ( fld_e1542 != 5 && fld_e1542 != 4 && *(this + 50) == 0 )  // 若 fld_e1542 != 5 && fld_e1542 != 4 && *(this + 50) == 0
            {
              v49 = 0;
              v50 = 0;
              v51 = 0;
              v53 = 4;
              pThis_6F3 = 1;
              sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
              (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 5, &v48, 2, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
              goto LABEL_151;  // 跳转 LABEL_151
            }
          }
          fld_e305 = *(this + 30);  // this+120 = 动画对象指针
          if ( fld_e305 != 0 && *(uint8_t *)(fld_e305 + 170) != 0 )  // 若 fld_e305 != 0 && *(uint8_t *)(fld_e305 + 170) != 0
            goto LABEL_115;  // 跳转 LABEL_115
          if ( *(this + 1672) != -1 && sub_699000((int)(this + 16)) >= *(this + 1672) )  // 【clock_now(clk)】
            goto LABEL_115;  // 跳转 LABEL_115
        }
      }
      else
      {
        fld_e306 = (uint32_t *)*(this + 30);  // this+120 = 动画对象指针
        if ( fld_e306 != nullptr && *(float *)(*(this + 28) + 24) <= 0.0 )  // this+112 = pHostComp
        {
          fld_e1698 = *(this + 1698);  // this+6792 = 炮车/子类参数面槽 1
          if ( fld_e306[37] == fld_e1698 && fld_e1698 != *(this + 1699) )  // this+6796 = 炮车/子类参数面槽 2
            sub_4AECE0(fld_e306, fld_e1698 + 1);  // 调 sub_4AECE0
        }
        if ( *(uint32_t *)(*(this + 28) + 184) == 4  // this+112 = pHostComp
          && *(this + 1707) != -1
          && *(this + 1707) != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        {
          pThis_6F3 = *(this + 1705) / -5;
          v31 = (double)pThis_6F3;
          *(this + 1705) = pThis_6F3;  // this+6820 = pThis_6F3
          v46 = v31;
          sub_494F20(0, v46);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
          *(this + 1707) = -1;  // this+6828 = -1
        }
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        {
          fld_e282 = *(this + 28);  // this+112 = pHostComp
          if ( *(float *)(fld_e282 + 24) < 0.0 && *(uint32_t *)(fld_e282 + 192) == 4 && *(this + 50) == 0 )  // 若 *(float *)(fld_e282 + 24) < 0.0 && *(uint32_t *)(fld_e282 + 19..
          {
            if ( *(this + 1672) == -1
              || sub_699000((int)(this + 16)) < *(this + 1672)  // 【clock_now(clk)】
              || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) != 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
            {
              v49 = 0;
              v50 = 0;
              v51 = 0;
              v53 = 2;
              pThis_6F3 = 4;
              sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
              pThis_6F3 = 1;
              sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
              pThis_6F3 = 0;
              sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
              sub_431230((int)&v48, this + 1705);  // 调 uint32 vector push_back
              pThis_6F3 = *(this + 1706) / 5;
              sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
              (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 4, &v48, 2, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
              goto LABEL_151;  // 跳转 LABEL_151
            }
LABEL_115:
            sub_58E660(this);  // 调 食尸鬼族通用：粒子/部件参数复位（供 vmt1D8/vmt14C 调用）
            return;
          }
        }
      }
      return;
    case 5:
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 529) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 1020))(this) == 0  // 调用虚函数（虚表槽 +1020）
        && *(uint32_t *)(dword_8F7A24 + 244) != 2 )  // dword_8F7A24 = 当前场景状态对象
      {
        sub_494F20(2, 0.0);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
      }
      return;
    case 6:
      fld_e1723 = *(this + 1723);  // fld_e1723 = this+1723
      if ( fld_e1723 != 0 )  // 若 fld_e1723 != 0
      {
        if ( fld_e1723 == 1 )  // 若 fld_e1723 == 1
        {
          if ( *((uint8_t *)this + 6988) == 0
            && v13 != 4
            && v13 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this)  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            && *(this + 1724) == 0
            && *((uint8_t *)this + 6996) == 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 148))(this, v13);  // 调用虚函数（虚表槽 +148）【推断: 同 vmt90 但不检查（直接写）】
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 144))(this, v13);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
          }
          fld_e307 = (uint32_t *)*(this + 30);  // this+120 = 动画对象指针
          if ( fld_e307 != nullptr
            && fld_e307 == (uint32_t *)*(this + 1547)
            && *(float *)(*(this + 28) + 24) <= 0.0  // this+112 = pHostComp
            && fld_e307[37] < *(this + 1717) )
          {
            sub_4AECE0(fld_e307, *(this + 1717));  // 调 sub_4AECE0
          }
          fld_e283 = *(this + 28);  // this+112 = pHostComp
          if ( *(float *)(fld_e283 + 24) < 0.0 && *(uint32_t *)(fld_e283 + 192) == 4 )  // 若 *(float *)(fld_e283 + 24) < 0.0 && *(uint32_t *)(fld_e283 + 19..
          {
            v49 = 0;
            v50 = 0;
            v51 = 0;
            v53 = 6;
            pThis_6F3 = 2;
            goto LABEL_149;  // 跳转 LABEL_149
          }
        }
        else if ( fld_e1723 == 2 )  // 否则若 fld_e1723 == 2
        {
          if ( *((uint8_t *)this + 6988) != 0 )  // 若 *((uint8_t *)this + 6988) != 0
          {
            if ( sub_699000((int)(this + 1640)) >= *(this + 1748) )  // 【clock_now(clk)】
LABEL_156:
              (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
          }
          else
          {
            fld_e308 = *(this + 30);  // this+120 = 动画对象指针
            if ( fld_e308 != 0 && *(uint8_t *)(fld_e308 + 170) != 0 )  // 若 fld_e308 != 0 && *(uint8_t *)(fld_e308 + 170) != 0
LABEL_145:
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
          }
        }
      }
      else
      {
        fld_e309 = *(this + 30);  // this+120 = 动画对象指针
        if ( fld_e309 != 0 && *(uint32_t *)(fld_e309 + 148) >= *(this + 1716) )  // 若 fld_e309 != 0 && *(uint32_t *)(fld_e309 + 148) >= *(this + 1716)
        {
          v49 = 0;
          v50 = 0;
          v51 = 0;
          v53 = 5;
          pThis_6F3 = 1;
          sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
          pThis_6F3 = 0;
          sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
          v40 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
          pThis_6F3 = sub_58E710(v40);  // 调 食尸鬼族通用：41A5E0 粒子挂载（第二变体）
          sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
          goto LABEL_150;  // 跳转 LABEL_150
        }
      }
      return;
    case 7:
      fld_e3010 = *(this + 30);  // this+120 = 动画对象指针
      if ( fld_e3010 != 0 && *(uint8_t *)(fld_e3010 + 170) != 0 )  // 若 fld_e3010 != 0 && *(uint8_t *)(fld_e3010 + 170) != 0
      {
        v49 = 0;
        v50 = 0;
        v51 = 0;
        v53 = 7;
        pThis_6F3 = 1;
LABEL_149:
        sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
        pThis_6F3 = *((uint8_t *)this + 6988) != 0;
        sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
        pThis_6F3 = 0;
        sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
LABEL_150:
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 6, &v48, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
        goto LABEL_151;  // 跳转 LABEL_151
      }
      if ( *(uint32_t *)(*(this + 28) + 192) == 4 )  // this+112 = pHostComp
      {
        v49 = 0;
        v50 = 0;
        v51 = 0;
        v53 = 8;
        pThis_6F3 = 2;
        sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
        pThis_6F3 = *((uint8_t *)this + 6988) != 0;
        sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
        pThis_6F3 = 0;
        sub_431230((int)&v48, &pThis_6F3);  // 调 uint32 vector push_back
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 6, &v48, 0, 0);  // 调用虚函数（虚表槽 +560）【推断: ★★★ 受击反应 setState / vt+560（研究 20…】
LABEL_151:
        sub_5E5260(&v48);  // 调 sub_5E5260
      }
      return;
    default:
      return;
  }
}

