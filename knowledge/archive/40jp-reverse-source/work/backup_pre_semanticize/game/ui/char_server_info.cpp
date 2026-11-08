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
char /*thiscall*/ sub_583A40(void *this)
{
  int v1; // ecx

  v1 = (int)this + 588;
  *(uint8_t *)(v1 + 13) = 0;
  *(uint8_t *)(v1 + 14) = 0;
  return sub_698F90(v1, 0, 0);
}



// ------------------------------------------------------------
// 0x583A60 sub_583A60 —— 读取 this+79 槽位（非 0 时调 0x5512D0 = 任务文本设置），0x583B90 流程取任务名用
// ------------------------------------------------------------
int /*thiscall*/ sub_583A60(int *this)
{
  int result; // eax

  result = *(this + 79);
  if ( result != 0 )
    return sub_5512D0(this, *(this + 79));
  return result;
}



// ------------------------------------------------------------
// 0x583A80 sub_583A80 —— 数值槽 setter：+50 标志为真直写 +56，否则写 +52 = a2 - 基址表 dword_79D100[+44]
// ------------------------------------------------------------
int /*thiscall*/ sub_583A80(int this, int a2)
{
  int result; // eax

  result = a2;
  if ( *(uint8_t *)(this + 50) != 0 )
  {
    *(uint32_t *)(this + 56) = a2;
  }
  else
  {
    result = a2 - dword_79D100[*(uint32_t *)(this + 44)];
    *(uint32_t *)(this + 52) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x583AB0 sub_583AB0 —— 4 段缓冲拷贝构造（this+0/+18/+8/+46 ← a2 同偏移，46B080=内存复制）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_583AB0(uint32_t *this, uint32_t *a2)
{
  *this = *a2;
  sub_46B080(this + 1, (unsigned int)(a2 + 1));
  sub_46B080((uint32_t *)((char *)this + 18), (unsigned int)a2 + 18);
  sub_46B080(this + 8, (unsigned int)(a2 + 8));
  sub_46B080((uint32_t *)((char *)this + 46), (unsigned int)a2 + 46);
  return this;
}



// ------------------------------------------------------------
// 0x583B30 sub_583B30 —— 按 this+72 下标查 this+69 表（16字节/项），-1 则返回 -1
// ------------------------------------------------------------
int /*thiscall*/ sub_583B30(uint32_t *this)
{
  int result; // eax

  result = *(this + 72);
  if ( result != -1 )
    return *(uint32_t *)(*(this + 69) + 16 * result);
  return result;
}



// ------------------------------------------------------------
// 0x583B50 sub_583B50 —— 释放全局缓冲 dword_9B9468 并清零 9B946C/9B9470（服务器列表缓存）【推断】
// ------------------------------------------------------------
void sub_583B50()
{
  if ( dword_9B9468 != nullptr )
    j__free(dword_9B9468);
  dword_9B9468 = nullptr;
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
int /*thiscall*/ sub_58A9D0(uint32_t *this, uint32_t *a2, int a3, int a4)
{
  *(this + 16420) = *a2;
  *(this + 16418) = a3;
  *(this + 16419) = a4;
  return a3;
}



// ------------------------------------------------------------
// 0x58AA00 sub_58AA00 —— 寻路器复位：节点池游标清零、memset 网格缓存(0x1000/0xF000×2)、开/闭链表头清空
// ------------------------------------------------------------
int /*thiscall*/ sub_58AA00(uint32_t *this)
{
  *(this + 16417) = 0;
  memset(this + 32, 0, 0x1000u);
  memset(this + 1057, 0, 0xF000u);
  memset(this + 1057, 0, 0xF000u);
  *(this + 16) = 0;
  *(this + 7) = 0;
  *(this + 31) = 0;
  *(this + 22) = 0;
  *(this + 8) = 0;
  *(this + 23) = 0;
  *(this + 9) = 0;
  *(this + 24) = 0;
  *(this + 10) = 0;
  *(this + 25) = 0;
  *(this + 11) = 0;
  *(this + 26) = 0;
  *(this + 12) = 0;
  *(this + 27) = 0;
  *(this + 13) = 0;
  *(this + 28) = 0;
  *(this + 14) = 0;
  *(this + 29) = 0;
  *(this + 15) = 0;
  *(this + 30) = 0;
  *(this + 1056) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x58AA80 sub_58AA80 —— 开链表按 f 值升序插入节点（+16 头插遍历）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_58AA80(uint32_t *this, uint32_t *a2)
{
  uint32_t *result; // eax
  uint32_t *v3; // ecx

  result = (uint32_t *)*(this + 16);
  if ( result != nullptr )
  {
    v3 = this + 2;
    do
    {
      if ( *result > *a2 )
        break;
      v3 = result;
      result = (uint32_t *)result[14];
    }
    while ( result != nullptr );
    a2[14] = result;
    v3[14] = a2;
  }
  else
  {
    *(this + 16) = a2;
    return a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x58AAC0 sub_58AAC0 —— A* 松弛主循环：取开链表最优节点，8 邻居 g 改善者更新并压入 1024 环形松弛缓冲
// ------------------------------------------------------------
int /*thiscall*/ sub_58AAC0(int *this, int a2)
{
  int **v2; // edi
  int *v3; // eax
  int v4; // edx
  int v5; // ebx
  int v6; // edx
  bool v7; // sf
  int result; // eax
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int **v12; // edi
  int *v13; // eax
  int v14; // esi
  int v15; // ebx
  int v16; // eax
  int *v17; // eax
  int v18; // esi
  int v19; // ebx
  int v20; // eax
  int *v21; // eax
  int v22; // esi
  int v23; // ebx
  int v24; // eax
  int *v25; // eax
  int v26; // esi
  int v27; // ebx
  int v28; // eax
  int v29; // [esp+Ch] [ebp-4h]
  int v30; // [esp+Ch] [ebp-4h]

  v29 = 0;
  v2 = (int **)(a2 + 24);
  do
  {
    v3 = *v2;
    if ( *v2 == nullptr )
      break;
    v4 = *(uint32_t *)(a2 + 8) + 1;
    if ( v3[2] > v4 )
    {
      v5 = v4 + v3[1];
      v3[2] = v4;
      *v3 = v5;
      v3[5] = a2;
      *(this + *(this + 1056) + 32) = (int)v3;
      v6 = *(this + 1056) + 1;
      v7 = *(this + 1056) - 1023 < 0;
      *(this + 1056) = v6;
      if ( v7 == __OFSUB__(v6, 1024) )
        *(this + 1056) = 0;
    }
    ++v2;
    ++v29;
  }
  while ( v29 < 8 );
  for ( result = *(this + 1056); result > 0; result = *(this + 1056) )
  {
    v9 = *(this + 1056);
    if ( v9 > 0 )
    {
      v11 = v9 - 1;
      *(this + 1056) = v11;
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
      if ( v13 == nullptr )
        break;
      v14 = *(uint32_t *)(v10 + 8) + 1;
      if ( v13[2] > v14 )
      {
        v15 = v14 + v13[1];
        v13[2] = v14;
        *v13 = v15;
        v13[5] = v10;
        *(this + *(this + 1056) + 32) = (int)v13;
        v16 = *(this + 1056) + 1;
        v7 = *(this + 1056) - 1023 < 0;
        *(this + 1056) = v16;
        if ( v7 == __OFSUB__(v16, 1024) )
          *(this + 1056) = 0;
      }
      v17 = *v12;
      if ( *v12 == nullptr )
        break;
      v18 = *(uint32_t *)(v10 + 8) + 1;
      if ( v17[2] > v18 )
      {
        v19 = v18 + v17[1];
        v17[2] = v18;
        *v17 = v19;
        v17[5] = v10;
        *(this + *(this + 1056) + 32) = (int)v17;
        v20 = *(this + 1056) + 1;
        v7 = *(this + 1056) - 1023 < 0;
        *(this + 1056) = v20;
        if ( v7 == __OFSUB__(v20, 1024) )
          *(this + 1056) = 0;
      }
      v21 = v12[1];
      if ( v21 == nullptr )
        break;
      v22 = *(uint32_t *)(v10 + 8) + 1;
      if ( v21[2] > v22 )
      {
        v23 = v22 + v21[1];
        v21[2] = v22;
        *v21 = v23;
        v21[5] = v10;
        *(this + *(this + 1056) + 32) = (int)v21;
        v24 = *(this + 1056) + 1;
        v7 = *(this + 1056) - 1023 < 0;
        *(this + 1056) = v24;
        if ( v7 == __OFSUB__(v24, 1024) )
          *(this + 1056) = 0;
      }
      v25 = v12[2];
      if ( v25 == nullptr )
        break;
      v26 = *(uint32_t *)(v10 + 8) + 1;
      if ( v25[2] > v26 )
      {
        v27 = v26 + v25[1];
        v25[2] = v26;
        *v25 = v27;
        v25[5] = v10;
        *(this + *(this + 1056) + 32) = (int)v25;
        v28 = *(this + 1056) + 1;
        v7 = *(this + 1056) - 1023 < 0;
        *(this + 1056) = v28;
        if ( v7 == __OFSUB__(v28, 1024) )
          *(this + 1056) = 0;
      }
      v12 += 4;
      v30 += 4;
    }
    while ( v30 < 8 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x58ACE0 sub_58ACE0 —— 从 1024×15-dword 节点池分配节点（游标 +16417 环形推进，60 字节清零）
// ------------------------------------------------------------
int /*thiscall*/ sub_58ACE0(uint32_t *this)
{
  if ( (int)*(this + 16417) >= 1024 )
    *(this + 16417) = 0;
  memset(this + 15 * *(this + 16417) + 1057, 0, 0x3Cu);
  return (int)(this + 15 * (*(this + 16417))++ + 1057);
}



// ------------------------------------------------------------
// 0x58AD30 sub_58AD30 —— 可行走判定：网格值≠2 且（允许对角 或 网格值≠1）→ true
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_58AD30(int *this, int a2, int a3, char a4)
{
  int v4; // eax
  char v5; // al
  BOOL result; // eax

  result = false;
  if ( a2 >= 0 && a3 >= 0 )
  {
    v4 = *(this + 16418);
    if ( a2 < v4 && a3 < *(this + 16419) )
    {
      v5 = *(uint8_t *)(*(this + 16420) + a3 * v4 + a2);
      if ( v5 != 2 && (a4 != 0 || v5 != 1) )
        return true;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58AD80 sub_58AD80 —— 邻居松弛：g+1 更新、h=|dx|+|dy| 曼哈顿、回写父指针 +20、f=g+h、入开链表
// ------------------------------------------------------------
int /*thiscall*/ sub_58AD80(int *this, int a2, int a3, int a4, int a5, int a6)
{
  int result; // eax
  int v7; // esi
  int v8; // edx
  int v9; // ecx
  uint32_t *v10; // edx
  int v11; // ecx
  uint32_t *v12; // ecx
  unsigned int v13; // eax
  uint32_t *v14; // edi
  int v15; // edx
  uint32_t *v16; // ebx
  int v17; // edx

  result = *(this + 16);
  v7 = *(uint32_t *)(a2 + 8) + 1;
  if ( result != 0 )
  {
    while ( 1 )
    {
      v8 = a3;
      if ( *(uint32_t *)(result + 12) == a3 && *(uint32_t *)(result + 16) == a4 )
        break;
      result = *(uint32_t *)(result + 56);
      if ( result == 0 )
        goto LABEL_12;
    }
    v9 = 0;
    v10 = (uint32_t *)(a2 + 24);
    do
    {
      if ( *v10 == 0 )
        break;
      ++v9;
      ++v10;
    }
    while ( v9 < 8 );
    *(uint32_t *)(a2 + 4 * v9 + 24) = result;
    if ( v7 < *(uint32_t *)(result + 8) )
    {
      v11 = *(uint32_t *)(result + 4);
      *(uint32_t *)(result + 20) = a2;
      *(uint32_t *)(result + 8) = v7;
      *(uint32_t *)result = v7 + v11;
    }
  }
  else
  {
    v8 = a3;
LABEL_12:
    result = *(this + 31);
    if ( result != 0 )
    {
      while ( *(uint32_t *)(result + 12) != v8 || *(uint32_t *)(result + 16) != a4 )
      {
        result = *(uint32_t *)(result + 56);
        if ( result == 0 )
          goto LABEL_16;
      }
      v15 = 0;
      v16 = (uint32_t *)(a2 + 24);
      do
      {
        if ( *v16 == 0 )
          break;
        ++v15;
        ++v16;
      }
      while ( v15 < 8 );
      *(uint32_t *)(a2 + 4 * v15 + 24) = result;
      if ( v7 < *(uint32_t *)(result + 8) )
      {
        v17 = v7 + *(uint32_t *)(result + 4);
        *(uint32_t *)(result + 8) = v7;
        *(uint32_t *)result = v17;
        *(uint32_t *)(result + 20) = a2;
        return sub_58AAC0(this, result);
      }
    }
    else
    {
LABEL_16:
      v12 = (uint32_t *)sub_58ACE0(this);
      v12[3] = a3;
      v13 = abs32(a3 - a5) + abs32(a4 - a6);
      v12[1] = v13;
      v12[4] = a4;
      v12[2] = v7;
      *v12 = v7 + v13;
      v12[5] = a2;
      sub_58AA80(this, v12);
      result = 0;
      v14 = (uint32_t *)(a2 + 24);
      do
      {
        if ( *v14 == 0 )
          break;
        ++result;
        ++v14;
      }
      while ( result < 8 );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58AEC0 sub_58AEC0 —— 8 方向邻域扩展（右/下/左下/左/左上/上/右上/右下 顺序逐方向可行走检查+松弛）
// ------------------------------------------------------------
void /*thiscall*/ sub_58AEC0(int *this, int a2, int a3, int a4, char a5)
{
  int v6; // ecx
  int v7; // esi
  int v8; // edi
  int v9; // eax
  char v10; // al
  int v11; // edi
  int v12; // eax
  char v13; // al
  int v14; // esi
  int v15; // eax
  char v16; // al
  int v17; // esi
  int v18; // eax
  char v19; // al
  int v20; // edi
  int v21; // eax
  char v22; // al
  int v23; // edi
  int v24; // eax
  char v25; // al
  int v26; // esi
  int v27; // eax
  char v28; // al
  int v29; // esi
  int v30; // eax
  char v31; // al

  v6 = a2;
  v7 = *(uint32_t *)(a2 + 12) + 1;
  v8 = *(uint32_t *)(a2 + 16);
  if ( v7 >= 0 && v8 >= 0 )
  {
    v9 = *(this + 16418);
    if ( v7 < v9 && v8 < *(this + 16419) )
    {
      v10 = *(uint8_t *)(*(this + 16420) + v8 * v9 + v7);
      if ( v10 != 2 && (a5 != 0 || v10 != 1) )
      {
        sub_58AD80(a2, v7, v8, a3, a4);
        v6 = a2;
      }
    }
  }
  v11 = v8 + 1;
  if ( v7 >= 0 && v11 >= 0 )
  {
    v12 = *(this + 16418);
    if ( v7 < v12 && v11 < *(this + 16419) )
    {
      v13 = *(uint8_t *)(*(this + 16420) + v11 * v12 + v7);
      if ( v13 != 2 && (a5 != 0 || v13 != 1) )
      {
        sub_58AD80(v6, v7, v11, a3, a4);
        v6 = a2;
      }
    }
  }
  v14 = v7 - 1;
  if ( v14 >= 0 && v11 >= 0 )
  {
    v15 = *(this + 16418);
    if ( v14 < v15 && v11 < *(this + 16419) )
    {
      v16 = *(uint8_t *)(*(this + 16420) + v11 * v15 + v14);
      if ( v16 != 2 && (a5 != 0 || v16 != 1) )
      {
        sub_58AD80(v6, v14, v11, a3, a4);
        v6 = a2;
      }
    }
  }
  v17 = v14 - 1;
  if ( v17 >= 0 && v11 >= 0 )
  {
    v18 = *(this + 16418);
    if ( v17 < v18 && v11 < *(this + 16419) )
    {
      v19 = *(uint8_t *)(*(this + 16420) + v11 * v18 + v17);
      if ( v19 != 2 && (a5 != 0 || v19 != 1) )
      {
        sub_58AD80(v6, v17, v11, a3, a4);
        v6 = a2;
      }
    }
  }
  v20 = v11 - 1;
  if ( v17 >= 0 && v20 >= 0 )
  {
    v21 = *(this + 16418);
    if ( v17 < v21 && v20 < *(this + 16419) )
    {
      v22 = *(uint8_t *)(*(this + 16420) + v20 * v21 + v17);
      if ( v22 != 2 && (a5 != 0 || v22 != 1) )
      {
        sub_58AD80(v6, v17, v20, a3, a4);
        v6 = a2;
      }
    }
  }
  v23 = v20 - 1;
  if ( v17 >= 0 && v23 >= 0 )
  {
    v24 = *(this + 16418);
    if ( v17 < v24 && v23 < *(this + 16419) )
    {
      v25 = *(uint8_t *)(*(this + 16420) + v23 * v24 + v17);
      if ( v25 != 2 && (a5 != 0 || v25 != 1) )
      {
        sub_58AD80(v6, v17, v23, a3, a4);
        v6 = a2;
      }
    }
  }
  v26 = v17 + 1;
  if ( v26 >= 0 && v23 >= 0 )
  {
    v27 = *(this + 16418);
    if ( v26 < v27 && v23 < *(this + 16419) )
    {
      v28 = *(uint8_t *)(*(this + 16420) + v23 * v27 + v26);
      if ( v28 != 2 && (a5 != 0 || v28 != 1) )
      {
        sub_58AD80(v6, v26, v23, a3, a4);
        v6 = a2;
      }
    }
  }
  v29 = v26 + 1;
  if ( v29 >= 0 && v23 >= 0 )
  {
    v30 = *(this + 16418);
    if ( v29 < v30 && v23 < *(this + 16419) )
    {
      v31 = *(uint8_t *)(*(this + 16420) + v23 * v30 + v29);
      if ( v31 != 2 && (a5 != 0 || v31 != 1) )
        sub_58AD80(v6, v29, v23, a3, a4);
    }
  }
}


// ------------------------------------------------------------
// 0x58B140 sub_58B140 —— A* 搜索主循环：上限 500 次迭代，命中目标(x,y)或 f≥截断值即返回当前节点
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_58B140(int *this, unsigned int a2, unsigned int a3, int a4, int a5, char a6)
{
  unsigned int v7; // edi
  unsigned int v8; // ebx
  unsigned int *v9; // eax
  unsigned int v10; // edi
  int i; // edi
  uint32_t *result; // eax
  int v13; // [esp+Ch] [ebp-4h]

  v7 = abs32(a2 - a4);
  v8 = abs32(a3 - a5);
  v13 = *(this + 16418) * (v7 + 1) + *(this + 16419) * (v8 + 1);
  v9 = (unsigned int *)sub_58ACE0(this);
  v10 = v8 + v7;
  v9[1] = v10;
  *v9 = v10;
  v9[2] = 0;
  v9[3] = a2;
  v9[4] = a3;
  *(this + 16) = (int)v9;
  for ( i = 0; i < 500; ++i )
  {
    result = (uint32_t *)*(this + 16);
    if ( result == nullptr )
      break;
    if ( v13 < result[2] || result[3] == a4 && result[4] == a5 )
      return result;
    *(this + 16) = result[14];
    result[14] = *(this + 31);
    *(this + 31) = (int)result;
    sub_58AEC0(this, (int)result, a4, a5, a6);
  }
  return nullptr;
}



// ------------------------------------------------------------
// 0x58B200 sub_58B200 —— 寻路总入口：复位→58B140 搜索→沿父链回溯到第 1 步→输出目标格 (a6,a7)→复位
// ------------------------------------------------------------
int /*thiscall*/ sub_58B200(int *this, unsigned int a2, unsigned int a3, int a4, int a5, uint32_t *a6, uint32_t *a7, char a8)
{
  int *v10; // eax

  sub_58AA00(this);
  *(this + 1) = 0;
  if ( a3 == a5 && a2 == a4 )
    return 1;
  v10 = sub_58B140(this, a2, a3, a4, a5, a8);
  if ( v10 != nullptr )
  {
    for ( ; v10[2] > 1; v10 = (int *)v10[5] )
      ;
    *a6 = v10[3];
    *a7 = v10[4];
    *(this + 1) = *(this + 16417);
    sub_58AA00(this);
    return 1;
  }
  else
  {
    sub_58AA00(this);
    return 0;
  }
}



// ------------------------------------------------------------
// 0x58B2A0 sub_58B2A0 —— dword 动态数组 push（容量按 +100 步长扩容，operator new(4n+400) 迁移）
// ------------------------------------------------------------
int /*thiscall*/ sub_58B2A0(int this, int a2)
{
  int v3; // eax
  uint32_t *v4; // edi
  int i; // eax
  int v6; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( *(uint32_t *)(this + 8) >= v3 )
  {
    v4 = operator new(4 * v3 + 400);
    for ( i = 0; i < *(uint32_t *)(this + 4); ++i )
      v4[i] = *(uint32_t *)(*(uint32_t *)this + 4 * i);
    j_j__free(*(void **)this);
    v6 = *(uint32_t *)(this + 4);
    *(uint32_t *)this = v4;
    *(uint32_t *)(this + 4) = v6 + 100;
  }
  *(uint32_t *)(*(uint32_t *)this + 4 * (*(uint32_t *)(this + 8))++) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x58B310 sub_58B310 —— dword 动态数组 push（另一实例布局：+8 计数/+4 容量，扩容策略同 58B2A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58B310(int this, int a2)
{
  int v3; // eax
  uint32_t *v4; // edi
  int i; // eax
  int v6; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( *(uint32_t *)(this + 12) >= v3 )
  {
    v4 = operator new(4 * v3 + 400);
    for ( i = 0; i < *(uint32_t *)(this + 4); ++i )
      v4[i] = *(uint32_t *)(*(uint32_t *)this + 4 * i);
    j_j__free(*(void **)this);
    v6 = *(uint32_t *)(this + 4);
    *(uint32_t *)this = v4;
    *(uint32_t *)(this + 4) = v6 + 100;
  }
  *(uint32_t *)(*(uint32_t *)this + 4 * (*(uint32_t *)(this + 12))++) = a2;
  return a2;
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
int /*thiscall*/ sub_58B380(int *this)
{
  int v2; // ecx
  int result; // eax
  int v4; // eax
  int v5; // ecx
  void (*v6)(void); // edx
  int v7; // edi
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // ebx
  int v12; // edi
  int v13; // eax
  int v14; // ecx
  int v15; // [esp+4h] [ebp-8h]
  void (*v16)(void); // [esp+8h] [ebp-4h]

  v2 = *(this + 2);
  result = 0;
  *(this + 4) = 0;
  *(this + 3) = 0;
  if ( v2 <= 0 )
  {
    *(this + 2) = *(this + 3);
  }
  else
  {
    do
    {
      v4 = *(this + 4);
      v5 = *this;
      v6 = *(void (**)(void))(*this + 4 * v4++);
      *(this + 4) = v4;
      v7 = *(uint32_t *)(v5 + 4 * v4);
      v16 = v6;
      *(this + 4) = v4 + 1;
      v8 = sub_699000((int)(this + 5));
      v9 = *(this + 4);
      v10 = *this;
      v11 = *(uint32_t *)(*this + 4 * v9++);
      *(this + 4) = v9;
      v15 = *(uint32_t *)(v10 + 4 * v9);
      *(this + 4) = v9 + 1;
      if ( v8 - v7 >= v11 )
      {
        v16();
      }
      else
      {
        sub_58B310((int)this, (int)v16);
        sub_58B310((int)this, v7);
        sub_58B310((int)this, v11);
        v12 = v15;
        sub_58B310((int)this, v15);
        if ( *(this + 3) < *(this + 2) && v15 > 0 )
        {
          do
          {
            v13 = *(this + 4);
            v14 = *(uint32_t *)(*this + 4 * v13);
            *(this + 4) = v13 + 1;
            sub_58B310((int)this, v14);
            --v12;
          }
          while ( v12 != 0 );
        }
      }
      result = *(this + 4);
    }
    while ( result < *(this + 2) );
    *(this + 2) = *(this + 3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x58B450 sub_58B450 —— 时间线构造：CNTimer 虚表装配 + operator new(0xFA0) 指令缓冲 + 时标 1000
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_58B450(uint8_t *this)
{
  int v2; // esi

  v2 = (int)(this + 20);
  *(this + 24) = 0;
  *((uint32_t *)this + 5) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 7) = 0;
  *(this + 32) = 1;
  *(this + 34) = 0;
  *(this + 33) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 9) = 0;
  *(uint32_t *)this = operator new(0xFA0u);
  *((uint32_t *)this + 1) = 1000;
  *((uint32_t *)this + 2) = 0;
  sub_698F90(v2, 0, 0);
  return this;
}



// ------------------------------------------------------------
// 0x58B4D0 sub_58B4D0 —— 时间线析构：释放指令缓冲，+20 恢复 nengine::IObject 虚表
// ------------------------------------------------------------
void /*thiscall*/ sub_58B4D0(int this)
{
  j_j__free(*(void **)this);
  *(uint32_t *)(this + 20) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 24) = 0;
}



// ------------------------------------------------------------
// 0x58B570 sub_58B570 —— 列表头/上下文结构初始化（+0 指针、+2..+5 清零）
// ------------------------------------------------------------
size_t */*thiscall*/ sub_58B570(size_t *this, void *a2)
{
  int i; // ebx

  *this = (size_t)a2;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  for ( i = 512; i != 0; --i )
  {
    a2 = operator new(*this);
    sub_49C800(&a2);
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
int /*stdcall*/ CNMonsterFriendShip__vmt4(int a1)
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

  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v8);
  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v9);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 1108))(a1);
  if ( (uint8_t)result == 0 )
  {
    v7 = v9;
    v6 = v8;
    v2 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 80))(a1);
    v3 = sub_45EBE0(v2, v6, v7);
    result = __RTDynamicCast(v3, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    v4 = result;
    if ( result != 0 )
    {
      v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 1032))(a1) + 20);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1148))(a1, v4);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 1132))(a1);
      if ( v5 != *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 1032))(a1) + 20) )
        sub_4D84F0(0, 0);
      return sub_4DB200(23, -1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58B6C0 CNZealotFriendShip__vmt8 —— RTTI 判定目标是否 CNZealot（狂信者）
// ------------------------------------------------------------
bool /*stdcall*/ CNZealotFriendShip__vmt8(int a1)
{
  return __RTDynamicCast(a1, 0, &IRDMonster `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0) != 0;
}



// ------------------------------------------------------------
// 0x58B6F0 CNStarFishFriendShip__vmt8 —— RTTI 判定目标是否 CNStarFish（海星怪）
// ------------------------------------------------------------
bool /*stdcall*/ CNStarFishFriendShip__vmt8(int a1)
{
  return __RTDynamicCast(a1, 0, &IRDMonster `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0) != 0;
}



// ------------------------------------------------------------
// 0x58B720 CNTauFriendShip__vmt8 —— 判定 +332..+336 列表中是否含怪物族代码 20（Tau 牛头怪族）
// ------------------------------------------------------------
bool /*stdcall*/ CNTauFriendShip__vmt8(int a1)
{
  uint32_t *v1; // ecx
  uint32_t *v2; // eax
  bool v3; // zf

  v1 = *(uint32_t **)(a1 + 336);
  v2 = *(uint32_t **)(a1 + 332);
  v3 = v2 == v1;
  if ( v2 != v1 )
  {
    do
    {
      if ( *v2 == 20 )
        break;
      ++v2;
    }
    while ( v2 != v1 );
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
void /*userpurge*/ sub_58B750(int a1@<ecx>, int a2@<edi>, uint32_t *a3, int a4)
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
  int v21; // ecx
  int v22; // eax
  int v23; // edx
  uint32_t *v24; // edi
  int v25; // ebx
  int v26; // ebx
  int v27; // eax
  int v28; // ebx
  int v29; // eax
  int v30; // eax
  int v31; // edi
  int v32; // eax
  int v33; // ebx
  int v34; // eax
  int v35; // ebx
  int v36; // eax
  int v38; // [esp+0h] [ebp-10h]
  int v39; // [esp+4h] [ebp-Ch]
  int v40; // [esp+8h] [ebp-8h]
  int v42; // [esp+18h] [ebp+8h]
  unsigned int v43; // [esp+1Ch] [ebp+Ch]

  if ( a4 != 0 )
  {
    v39 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 576))(a4);
    if ( v39 != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 1032))(a3);
      v6 = *(uint32_t *)(v5 + 52) - *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 1032))(a3) + 48);
      v7 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*a3 + 672))(a3, 3);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 1032))(a3);
      v40 = (uint64_t)sub_4049C0(800.0, 1200.0, *v7 - *(uint32_t *)(v8 + 48), v6);
      v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 1032))(a3);
      v10 = *(uint32_t *)(v9 + 52) - *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 1032))(a3) + 48);
      v11 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*a3 + 672))(a3, 3);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 1032))(a3);
      v13 = (uint64_t)sub_4049C0(4.0, 8.0, *v11 - *(uint32_t *)(v12 + 48), v10);
      v14 = 0;
      v38 = v13;
      v42 = 0;
      while ( 1 )
      {
        v43 = v14;
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 80))(a3);
        v16 = *(uint32_t *)(v15 + 8);
        v17 = v15 + 4;
        v18 = v16 != 0 ? (*(uint32_t *)(v17 + 8) - v16) >> 2 : 0;
        if ( (int)v14 >= v18 )
          break;
        v19 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a3 + 80))(a3, a2);
        v20 = *(uint32_t *)(v19 + 8);
        if ( v20 != 0 && v14 < (*(uint32_t *)(v19 + 12) - v20) >> 2 )
          v21 = *(uint32_t *)(v20 + 4 * v14);
        else
          v21 = 0;
        a2 = 529;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 40))(v21) != 0 )
        {
          v22 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 80))(a3);
          v23 = *(uint32_t *)(v22 + 8);
          if ( v23 != 0 && v14 < (*(uint32_t *)(v22 + 12) - v23) >> 2 )
            v24 = *(uint32_t **)(v23 + 4 * v14);
          else
            v24 = nullptr;
          if ( v24[1943] != 3 )
          {
            v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 376))(a3);
            if ( v25 == (*(int (/*thiscall*/ **)(uint32_t *))(*v24 + 376))(v24)
              && a3 != v24
              && (*(uint8_t (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)a1 + 8))(a1, v24) != 0
              && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t))(*a3 + 8))(a3, v24, 0) <= v40
              && (*(int (/*thiscall*/ **)(uint32_t *))(*v24 + 304))(v24) != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
              v26 = *(uint32_t *)dword_8F8520;
              v27 = (*(int (/*thiscall*/ **)(uint32_t *))(*v24 + 48))(v24);
              (*(void (/*thiscall*/ **)(int, int))(v26 + 36))(dword_8F8520, v27);
              v28 = *(uint32_t *)dword_8F8520;
              v29 = (*(int (/*thiscall*/ **)(uint32_t *))(*v24 + 52))(v24);
              (*(void (/*thiscall*/ **)(int, int))(v28 + 36))(dword_8F8520, v29);
              v30 = (*(int (/*thiscall*/ **)(uint32_t *))(*v24 + 304))(v24);
              v31 = *(uint32_t *)dword_8F8520;
              v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 52))(v30);
              (*(void (/*thiscall*/ **)(int, int))(v31 + 36))(dword_8F8520, v32);
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 14);
              v33 = *(uint32_t *)dword_8F8520;
              v34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v39 + 48))(v39);
              (*(void (/*thiscall*/ **)(int, int))(v33 + 36))(dword_8F8520, v34);
              v35 = *(uint32_t *)dword_8F8520;
              v36 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v39 + 52))(v39);
              (*(void (/*thiscall*/ **)(int, int))(v35 + 36))(dword_8F8520, v36);
              (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
              if ( ++v42 > v38 )
                return;
            }
            v14 = v43;
          }
        }
        ++v14;
      }
    }
  }
}


// ------------------------------------------------------------
// 0x58BA00 sub_58BA00 —— 食尸鬼部件参数初始化：+1698..+1702 状态组（1/1/3/4/4）、+2152..54=-1、+4185 起 26×50
// ------------------------------------------------------------
uint16_t */*thiscall*/ sub_58BA00(uint32_t *this)
{
  uint16_t *result; // eax
  int i; // ecx

  *(this + 1698) = 1;
  *(this + 1699) = 1;
  *(this + 1700) = 3;
  *(this + 1701) = 4;
  *(this + 1702) = 4;
  *(this + 2152) = -1;
  *(this + 2153) = -1;
  *(this + 2154) = -1;
  result = (uint16_t *)this + 4185;
  for ( i = 26; i != 0; --i )
  {
    *result = 50;
    result += 2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x58BA60 CNGhoul__vmt200 —— CNGhoul 命中处理器：受击者状态 17 且 10% 概率→vt+580 播 48003 吼叫（±30 随机）→尾调 IRDMonster__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNGhoul__vmt200(int *this, int a2, int a3, int a4)
{
  int v5; // edi
  int v6; // edi
  int v7; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17) == 1 && rand() % 100 < 10 )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 152))(a2);
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == v5
      && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      v6 = *this;
      v7 = (*(int (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 152))(
             this,
             0,
             30,
             4,
             0,
             0,
             0);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, int))(v6 + 580))(
        this,
        48003,
        10,
        0,
        0,
        v7 != 1 ? -30 : 30);
    }
  }
  return IRDMonster__vmt200(a2, a3, a4);
}



// ------------------------------------------------------------
// 0x58BB00 CNGhoul__vmt444 —— CNGhoul AI 决策周期：+8600==1 时按 +1787 状态 switch→vt+1104 切换状态 4/5/13（10% 概率）
// ------------------------------------------------------------
void /*thiscall*/ CNGhoul__vmt444(uint32_t *this)
{
  uint32_t *v2; // ecx

  if ( *((uint8_t *)this + 8600) == 1 )
  {
    IRDMonster__vmt444();
    switch ( *(this + 1787) )
    {
      case 0:
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
        break;
      case 4:
        v2 = this;
        if ( *(this + 1813) == 0 )
          goto LABEL_5;
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && rand() % 100 < 10 )
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);
        break;
      case 5:
        v2 = this;
        if ( *(this + 1813) != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && rand() % 100 < 10 )
            goto LABEL_14;
        }
        else
        {
LABEL_5:
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(v2, 13);
        }
        break;
      case 0xD:
      case 0xE:
      case 0xF:
        if ( *(this + 1813) != 0 )
LABEL_14:
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
        break;
      default:
        return;
    }
  }
}



// ------------------------------------------------------------
// 0x58BC10 CNGhoul__vmt520 —— CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施法与目标链）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoul__vmt520(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // edx

  result = *(this + 2151);
  if ( result == 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 144))(this);
    v3 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 200))(this, 0);
    sub_493400(v3, 1);
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
    sub_4939E0(v4, 1);
    result = sub_4E7F30(this, 200, 200, 0);
    if ( result != 0 )
    {
      v5 = *this;
      *(this + 2151) = 1;
      v6 = (*(int (/*thiscall*/ **)(int *))(v5 + 200))(this);
      sub_4926A0(v6);
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
      sub_4939E0(v7, 0);
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1316))(this);
    }
  }
  if ( *(this + 2151) == 1 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
    if ( *(uint8_t *)(result + 170) == 1 )
    {
      v8 = *this;
      *(this + 1639) = 0;
      *((uint8_t *)this + 8600) = 1;
      *(this + 2151) = -1;
      (*(void (/*thiscall*/ **)(int *))(v8 + 1320))(this);
      sub_4926A0(*(this + 1540));
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1540));
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58BD00 CNGhoul__vmt14C —— CNGhoul 移动/受击表现槽 vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNGhoul__vmt14C(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // ebx
  int i; // edi

  if ( *((uint8_t *)this + 8600) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1312))(this);
    v2 = *(this + 2152);
    v3 = this + 2152;
    if ( v2 == -1 && *(this + 2153) == -1 && *(this + 2154) == -1 )
    {
      for ( i = 0; i < 3; ++i )
        *v3++ = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 116))(this, i);
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*this + 108))(this, v2, *(this + 2153), *(this + 2154));
    }
  }
  return IRDMonster__vmt14C(this);
}



// ------------------------------------------------------------
// 0x58BD80 CNGhoul__vmt1D8 —— CNGhoul 周期状态槽 vmt1D8（14 行轻量实现）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoul__vmt1D8(uint8_t *this, char a2, float a3, int a4, int a5)
{
  int result; // eax

  if ( *(this + 8600) == 1 )
    return IRDMonster__vmt1D8(a2, a3, a4, a5);
  return result;
}



// ------------------------------------------------------------
// 0x58BDA0 CNGhoulThrower__vmt4A8 —— CNGhoulThrower 技能槽 vmt4A8（16 行）——投掷头骨入口
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulThrower__vmt4A8(uint32_t *this)
{
  *(this + 2155) = 1;
  *(this + 1698) = 1;
  *(this + 1699) = 1;
  *(this + 1700) = 3;
  *(this + 1701) = 4;
  *(this + 1702) = 4;
  return 4;
}



// ------------------------------------------------------------
// 0x58BDE0 sub_58BDE0 —— 发射投掷物 GhoulThrowerSkull.ptl（423A20=投掷物生成，按 this 参数定弹道）
// ------------------------------------------------------------
int /*thiscall*/ sub_58BDE0(int *this)
{
  int result; // eax
  uint64_t v3; // rax
  int v4; // esi
  uint64_t v5; // rax
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // edx
  uint32_t v13[26]; // [esp+8h] [ebp-68h] BYREF

  v13[25] = dword_796E50;
  sub_423A20((int)v13);
  result = *(this + 1813);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1244))(this, *(this + 1813));
    if ( (uint8_t)result != 0 )
    {
      qmemcpy(
        v13,
        (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/GhoulThrowerSkull.ptl"),
        0x62u);
      v3 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v13[7] + 3)) / (double)v13[17] * 1000.0);
      v4 = 2 * v3;
      v5 = (uint64_t)((double (/*fastcall*/ *)(int *, uint32_t, uint32_t, uint32_t))*(uint32_t *)(*this + 164))(
                               this,
                               HIDWORD(v3),
                               *(this + 1813),
                               0);
      HIDWORD(v5) = *this;
      v13[18] = v5;
      v6 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(HIDWORD(v5) + 8))(this, *(this + 1813), 0);
      v7 = *this;
      *(uint32_t *)((char *)&v13[3] + 3) = 1000 * v6 / v4;
      v8 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v7 + 8))(this, *(this + 1813), 0);
      v9 = *this;
      *(uint32_t *)((char *)&v13[4] + 3) = 1000 * v8 / v4;
      v10 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v9 + 8))(this, *(this + 1813), 0);
      if ( v10 >= 100 )
        v11 = v10 >= 200 ? 300 : 200;
      else
        v11 = 100;
      v12 = *this;
      *(uint32_t *)((char *)&v13[7] + 3) = v11;
      result = (*(int (/*thiscall*/ **)(int *))(v12 + 308))(this);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
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
void /*thiscall*/ CNGhoulMorgan__vmt4A8(uint32_t *this)
{
  *(this + 2155) = 1;
}



// ------------------------------------------------------------
// 0x58BF40 sub_58BF40 —— 发射投掷物 GhoulMorganSkullBomb.ptl（ Morgan 头颅炸弹弹道）
// ------------------------------------------------------------
int /*thiscall*/ sub_58BF40(int *this)
{
  int result; // eax
  uint64_t v3; // rax
  int v4; // esi
  uint64_t v5; // rax
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // edx
  uint32_t v13[26]; // [esp+8h] [ebp-68h] BYREF

  v13[25] = dword_796E50;
  sub_423A20((int)v13);
  result = *(this + 1813);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1244))(this, *(this + 1813));
    if ( (uint8_t)result != 0 )
    {
      qmemcpy(
        v13,
        (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(
                        this,
                        "Particle/GhoulMorganSkullBomb.ptl"),
        0x62u);
      v3 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v13[7] + 3)) / (double)v13[17] * 1000.0);
      v4 = 2 * v3;
      v5 = (uint64_t)((double (/*fastcall*/ *)(int *, uint32_t, uint32_t, uint32_t))*(uint32_t *)(*this + 164))(
                               this,
                               HIDWORD(v3),
                               *(this + 1813),
                               0);
      HIDWORD(v5) = *this;
      v13[18] = v5;
      v6 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(HIDWORD(v5) + 8))(this, *(this + 1813), 0);
      v7 = *this;
      *(uint32_t *)((char *)&v13[3] + 3) = 1000 * v6 / v4;
      v8 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v7 + 8))(this, *(this + 1813), 0);
      v9 = *this;
      *(uint32_t *)((char *)&v13[4] + 3) = 1000 * v8 / v4;
      v10 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v9 + 8))(this, *(this + 1813), 0);
      if ( v10 >= 150 )
        v11 = v10 >= 300 ? 450 : 300;
      else
        v11 = 150;
      v12 = *this;
      *(uint32_t *)((char *)&v13[7] + 3) = v11;
      result = (*(int (/*thiscall*/ **)(int *))(v12 + 308))(this);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
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
int /*thiscall*/ CNGhoulNoMercy__vmt4A8(int this)
{
  *(uint32_t *)(this + 6792) = 1;
  *(uint32_t *)(this + 6796) = 1;
  *(uint32_t *)(this + 6804) = 4;
  *(uint32_t *)(this + 6808) = 4;
  *(uint32_t *)(this + 6800) = 3;
  *(uint32_t *)(this + 8656) = 0;
  *(uint8_t *)(this + 8620) = 0;
  *(uint32_t *)(this + 8672) = 0;
  *(uint32_t *)(this + 8676) = 0;
  *(uint32_t *)(this + 8680) = 0;
  *(uint32_t *)(this + 8624) = 0;
  *(uint8_t *)(this + 8641) = 0;
  *(uint8_t *)(this + 8642) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x58C0F0 CNGhoulNoMercy__vmt12C —— CNGhoulNoMercy 受击属性槽 vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulNoMercy__vmt12C(uint32_t *this, uint32_t *a2)
{
  int v3; // ecx
  int v4; // ecx

  if ( a2 == (uint32_t *)*(this + 2164) )
  {
    *(this + 2164) = 0;
  }
  else if ( a2 == (uint32_t *)*(this + 2169) )
  {
    *(this + 2169) = 0;
  }
  if ( a2 == this )
  {
    v3 = *(this + 2164);
    if ( v3 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v3 + 560))(v3, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 564))(*(this + 2164));
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2164) + 604))(*(this + 2164), 1);
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t))(*(uint32_t *)*(this + 2164) + 612))(*(this + 2164), 1, 0);
    }
    v4 = *(this + 2169);
    if ( v4 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v4 + 560))(v4, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2169) + 564))(*(this + 2169));
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2169) + 604))(*(this + 2169), 1);
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t))(*(uint32_t *)*(this + 2169) + 612))(*(this + 2169), 1, 0);
    }
  }
  return IRDMonster__vmt12C(a2);
}



// ------------------------------------------------------------
// 0x58C1D0 sub_58C1D0 —— 抓投敌人姿态/碰撞初始化（4924C0/4918E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58C1D0(int *this, int *a2, uint32_t *a3, int *a4)
{
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int result; // eax
  int v12; // edi
  int v13; // ebx
  int v14; // ebx
  int v15; // ebx
  int v16; // [esp-4h] [ebp-Ch]

  v5 = *(this + 2164);
  if ( v5 != 0 && (*(uint8_t (/*stdcall*/ **)(int))(*(uint32_t *)v5 + 40))(273) != 0 )
  {
    __RTDynamicCast(*(this + 2164), 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
    v16 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);
    v6 = sub_4924C0(0);
    v7 = sub_4918E0(v6, v16) / 2;
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    v9 = *(this + 2164);
    if ( v8 == 1 )
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 120))(v9) - v7;
    else
      v10 = v7 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 120))(v9);
    *a2 = v10;
    *a3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 124))(*(this + 2164)) + 1;
    result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 128))(*(this + 2164)) + 12;
    *a4 = result;
  }
  else
  {
    *a2 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 120))(*(this + 2164));
    *a3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 124))(*(this + 2164)) + 1;
    v12 = *(this + 2164);
    v13 = (*(int (**)(void))(*(uint32_t *)v12 + 128))();
    v14 = v13 - (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 192))(v12) + v14;
    *a4 = v15;
    return (int)a4;
  }
  return result;
}



// ------------------------------------------------------------
// 0x58C300 j_CNGhoul__vmt444 —— j_CNGhoul__vmt444 尾调用桩（jmp CNGhoul__vmt444）
// ------------------------------------------------------------
// attributes: thunk
void /*thiscall*/ j_CNGhoul__vmt444(uint32_t *this)
{
  CNGhoul__vmt444(this);
}



// ------------------------------------------------------------
// 0x58C310 CNThrowNoMercyGrabEnemy__vmt10 —— ThrowNoMercyGrabEnemy 抓取执行：4938F0 目标绑定 + 432E50 播报（101 行抓取流程）
// ------------------------------------------------------------
void /*thiscall*/ CNThrowNoMercyGrabEnemy__vmt10(int **this)
{
  int v2; // ecx
  int *v3; // esi
  int v4; // eax
  int v5; // ebx
  int *v6; // eax
  uint32_t *v7; // ecx
  int *v8; // ebx
  int v9; // eax
  int v10; // eax
  char v11; // bl
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int *v17; // [esp+4h] [ebp-4h]
  int v18; // [esp+4h] [ebp-4h]

  v2 = (int)*(this + 20);
  if ( v2 != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 840))(v2) == 18 )
    {
      v3 = *(this + 1);
      if ( (*(int (/*thiscall*/ **)(int *))(*v3 + 840))(v3) == 9 )
      {
        v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 20) + 200))(*(this + 20));
        v5 = v4;
        if ( v4 != 0 )
        {
          sub_4938F0(v4);
          v6 = *(int **)(v5 + 148);
          v7 = *(this + 20);
          v8 = (int *)v7[2168];
          v17 = v6;
          if ( v8 != *(this + 21) || v6 != *(this + 22) )
          {
            if ( v8 != nullptr )
            {
              *(this + 23) = nullptr;
              *(this + 24) = (int *)1;
              if ( 93 - (*(int (/*thiscall*/ **)(int *))(*v3 + 192))(v3) / 2 >= 40 )
                v9 = 40;
              else
                v9 = 93 - (*(int (/*thiscall*/ **)(int *))(*v3 + 192))(v3) / 2;
              *(this + 25) = (int *)v9;
            }
            else
            {
              *(this + 23) = (int *)((*(int (/*thiscall*/ **)(uint32_t *))(*v7 + 152))(v7) != 0 ? 60 : -60);
              *(this + 24) = (int *)-1;
              if ( 65 - (*(int (/*thiscall*/ **)(int *))(*v3 + 192))(v3) <= 0 )
                *(this + 25) = nullptr;
              else
                *(this + 25) = (int *)(65 - (*(int (/*thiscall*/ **)(int *))(*v3 + 192))(v3));
            }
            if ( v17 != nullptr )
            {
              if ( v17 == (int *)1 )
                *(this + 23) = (int *)40;
            }
            else
            {
              *(this + 23) = (int *)30;
            }
            *(this + 21) = v8;
            *(this + 22) = v17;
          }
          v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 20) + 152))(*(this + 20));
          v11 = sub_432E50(v10);
          *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v3 + 60))(v3) + 52) = v11;
          v12 = *v3;
          v18 = (int)*(this + 20);
          v13 = (*(int (**)(void))(*(uint32_t *)v18 + 128))();
          v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 124))(v18, (int)*(this + 25) + v13);
          v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 120))(v18, (int)*(this + 24) + v14);
          (*(void (/*thiscall*/ **)(int *, int))(v12 + 112))(v3, (int)*(this + 23) + v15);
          (*(void (/*thiscall*/ **)(int *, int, int))(*v3 + 612))(v3, 1, 1);
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*v3 + 820))(v3, 0);
          if ( (*(int (/*thiscall*/ **)(int *))(*v3 + 200))(v3) != 0 )
          {
            v16 = (*(int (/*thiscall*/ **)(int *))(*v3 + 200))(v3);
            sub_4938F0(v16);
          }
        }
      }
    }
    else
    {
      *(this + 20) = nullptr;
    }
  }
}



// ------------------------------------------------------------
// 0x58C4E0 CNThrowNoMercyGrabEnemy__vmt1C —— ThrowNoMercyGrabEnemy 落地/释放槽 vmt1C
// ------------------------------------------------------------
int /*thiscall*/ CNThrowNoMercyGrabEnemy__vmt1C(uint32_t *this)
{
  int v2; // ecx
  int result; // eax

  v2 = *(this + 1);
  *(this + 21) = -1;
  *(this + 22) = -1;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 776))(v2, 3);
  if ( (uint8_t)result != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 556))(*(this + 1), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 768))(*(this + 1), 3, 0, 0);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 556))(*(this + 1), 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x58C540 CNGhoulOilSellerOlrek__vmt444 —— CNGhoulOilSellerOlrek 技能槽 vmt444（转发 4DB200 播报）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulOilSellerOlrek__vmt444(uint32_t *this)
{
  int v1; // eax
  int result; // eax
  int v3; // et2

  CNGhoul__vmt444(this);
  v1 = rand();
  v3 = v1 % 100;
  result = v1 / 100;
  if ( v3 < 2 )
    return sub_4DB200(24, 0);
  return result;
}



// ------------------------------------------------------------
// 0x58C570 CNGhoulOilSellerOlrek__vmt52C —— Olrek 卖油摊位交互：加载 RedRock.ptl/RedOilFlask.ptl（41A5E0 粒子挂载）
// ------------------------------------------------------------
int /*usercall*/ CNGhoulOilSellerOlrek__vmt52C@<eax>(uint32_t *a1@<ecx>, int a2@<edi>, int a3@<esi>)
{
  int result; // eax
  uint16_t *v5; // eax
  uint16_t *v6; // eax
  int v7; // edx
  uint32_t v8[24]; // [esp+8h] [ebp-68h] BYREF
  int16_t v9; // [esp+68h] [ebp-8h]
  int v10; // [esp+6Ch] [ebp-4h]

  v10 = dword_796E50;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1);
    if ( result == 8 )
    {
      if ( sub_41A5E0((unsigned int)(a1 + 1757)) == 0
        && *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) + 148) >= 3
        && a1[2155] == 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int))(*a1 + 384))(a1, 0, a2, a3);
        v5 = (uint16_t *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*a1 + 588))(
                        a1,
                        "../../PassiveObject/Monster/Magma/Particle/RedRock.ptl");
        qmemcpy(v8, v5, sizeof(v8));
        v8[1] = 0;
        v8[0] = 20;
        v9 = v5[48];
LABEL_11:
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 580))(a1);
        a1[2155] = 1;
        return result;
      }
      result = sub_41A5E0((unsigned int)(a1 + 1757));
      if ( result == 1 )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1);
        if ( *(int *)(result + 148) >= 3 )
        {
          result = a1[2155];
          if ( result == 0 )
          {
            v6 = (uint16_t *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int, int))(*a1 + 588))(
                            a1,
                            "../../PassiveObject/Monster/Magma/Particle/RedOilFlask.ptl",
                            a2,
                            a3);
            v7 = *a1;
            qmemcpy(v8, v6, sizeof(v8));
            v8[6] = 1;
            v9 = v6[48];
            (*(void (/*thiscall*/ **)(uint32_t *, int))(v7 + 384))(a1, 1);
            memset(&v8[4], 0, 12);
            v8[3] = 4;
            v8[2] = 50;
            v8[1] = 0;
            v8[0] = 20;
            goto LABEL_11;
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
char /*thiscall*/ CNMagmaGhoul__vmt4A8(uint8_t *this)
{
  int v2; // eax
  int v3; // eax

  v2 = *(uint32_t *)this;
  *(this + 8656) = 0;
  v3 = (*(int (**)(void))(v2 + 52))();
  *((uint32_t *)this + 2156) = v3;
  *((uint32_t *)this + 2155) = v3;
  *(this + 8641) = 0;
  *(this + 8642) = 0;
  return sub_698F90((int)(this + 8628), 10000, 0);
}



// ------------------------------------------------------------
// 0x58C6F0 CNMagmaGhoul__vmt200 —— CNMagmaGhoul 命中处理器 vmt200（转发 4DB130）
// ------------------------------------------------------------
int /*stdcall*/ CNMagmaGhoul__vmt200(int a1, int a2, int a3)
{
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 348))(a1) + 20) == 0 )
    sub_4DB130(24, 2);
  return IRDMonster__vmt200(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x58C730 CNMagmaGhoul__vmt1D8 —— CNMagmaGhoul 周期状态槽 vmt1D8（转发 4DB200）
// ------------------------------------------------------------
void /*thiscall*/ CNMagmaGhoul__vmt1D8(uint8_t *this, char ArgList, float a3, int a4, int a5)
{
  int v5; // eax

  if ( *(this + 8600) == 1 )
  {
    v5 = rand() % 2;
    sub_4DB200(24, v5 == 0);
    IRDMonster__vmt1D8(ArgList, a3, a4, a5);
  }
}



// ------------------------------------------------------------
// 0x58C780 sub_58C780 —— NoMercy 状态辅助（4B1030 目标查询）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_58C780(uint32_t *this, int a2)
{
  sub_4B1030(this);
  *(this + 21) = -1;
  *(this + 22) = -1;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *((uint8_t *)this + 40) = 0;
  *this = &vftbl_CNThrowNoMercyGrabEnemy;
  *(this + 20) = a2;
  return this;
}



// ------------------------------------------------------------
// 0x58C7C0 CNThrowNoMercyGrabEnemy__vmt0 —— ThrowNoMercyGrabEnemy 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNThrowNoMercyGrabEnemy__vmt0(void *Block, char a2)
{
  sub_58C7F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x58C7F0 sub_58C7F0 —— 析构成员清理（5F6640 投掷物/粒子释放）
// ------------------------------------------------------------
int /*thiscall*/ sub_58C7F0(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x58C840 sub_58C840 —— NoMercy 抓取发起（45EBE0 对象查找 + 58C1D0 姿态初始化，79 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_58C840(int this, int a2, int a3)
{
  int v4; // eax
  int v5; // edi
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // edi
  int v12; // ebx
  int v14; // [esp+Ch] [ebp-Ch] BYREF
  int v15; // [esp+10h] [ebp-8h] BYREF
  int v16; // [esp+14h] [ebp-4h] BYREF

  v4 = sub_45EBE0(*(uint32_t **)(this + 116), **(uint32_t **)(a3 + 4), *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4));
  v5 = v4;
  if ( v4 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 40))(v4, 17) == 0
    || (*(uint32_t *)(this + 8656) = v5, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 128))(v5) > 0) )
  {
    *(uint32_t *)(this + 8656) = 0;
  }
  v6 = *(uint32_t *)(this + 8656);
  if ( v6 != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 120))(v6);
    v8 = *(uint32_t *)(this + 8656);
    *(uint32_t *)(this + 8660) = v7;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 124))(v8);
    v10 = *(uint32_t *)(this + 8656);
    *(uint32_t *)(this + 8664) = v9;
    *(uint32_t *)(this + 8668) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 128))(v10);
    sub_58C1D0((int *)this, &v14, &v15, &v16);
    v11 = v14;
    v12 = v15;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 8656) + 136))(
           *(uint32_t *)(this + 8656),
           v14,
           v15,
           0) == 0
      || (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 8656) + 132))(
           *(uint32_t *)(this + 8656),
           v16) == 0 )
    {
      v11 = *(uint32_t *)(this + 8660);
      v12 = *(uint32_t *)(this + 8664);
    }
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(this + 8656) + 112))(
      *(uint32_t *)(this + 8656),
      v11,
      v12,
      v16);
  }
  (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
    this,
    1,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 2, 1000, 1000);
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
}



// ------------------------------------------------------------
// 0x58C990 CNGhoul__vmt524 —— CNGhoul 技能槽 vmt524（4926A0 目标链）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoul__vmt524(uint32_t *this)
{
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -100,
    *(uint32_t *)(*(this + 1554) + 4),
    0,
    0,
    0,
    0);
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
           this,
           100,
           *(uint32_t *)(*(this + 1554) + 8),
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x58CA00 CNGhoul__vmt528 —— CNGhoul 技能槽 vmt528（11 行轻量）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoul__vmt528(uint32_t *this)
{
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 4));
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 8));
}



// ------------------------------------------------------------
// 0x58CA30 CNGhoulThrower__vmt1D8 —— CNGhoulThrower 周期状态槽 vmt1D8（45 行）
// ------------------------------------------------------------
void /*thiscall*/ CNGhoulThrower__vmt1D8(uint32_t *this, int ArgList, float a3, int a4, int a5)
{
  uint32_t *v6; // eax
  uint32_t *v7; // eax

  if ( *((uint8_t *)this + 8600) == 1 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));
    if ( ArgList == 8 )
    {
      v6 = *(uint32_t **)(LODWORD(a3) + 4);
      if ( *v6 != 0 )
      {
        if ( *v6 != 1 )
          goto LABEL_8;
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 16));
        v7 = (uint32_t *)(*(this + 1554) + 16);
      }
      else
      {
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));
        v7 = (uint32_t *)(*(this + 1554) + 12);
      }
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        100,
        *v7,
        0,
        0,
        0,
        0);
      *(this + 2155) = 0;
    }
LABEL_8:
    if ( *((uint8_t *)this + 8600) == 1 )
      IRDMonster__vmt1D8(ArgList, a3, a4, a5);
  }
}



// ------------------------------------------------------------
// 0x58CB00 CNGhoulThrower__vmt14C —— CNGhoulThrower 移动/受击表现槽 vmt14C（41A5E0 粒子挂载）
// ------------------------------------------------------------
char /*thiscall*/ CNGhoulThrower__vmt14C(uint32_t *this)
{
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 8
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 8 && sub_41A5E0((unsigned int)(this + 1757)) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));
  }
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1324))(this);
  return CNGhoul__vmt14C(this);
}



// ------------------------------------------------------------
// 0x58CB70 CNGhoulThrower__vmt52C —— CNGhoulThrower 技能槽 vmt52C：投掷头骨（转发 58BDE0 发射）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulThrower__vmt52C(int *this)
{
  int result; // eax
  uint32_t *v3; // eax
  int v4; // ecx

  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( result == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result != 1 )
        return result;
      v4 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148);
      result = *(this + 2155);
      if ( result == 0 && v4 >= 3 )
        goto LABEL_13;
      if ( result == 1 && v4 >= 9 )
      {
        v3 = (uint32_t *)(*(this + 1554) + 16);
        goto LABEL_12;
      }
    }
    else
    {
      result = *(this + 2155);
      if ( result == 0 )
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
        if ( *(int *)(result + 148) >= 3 )
        {
          v3 = (uint32_t *)(*(this + 1554) + 12);
LABEL_12:
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *v3);
LABEL_13:
          result = sub_58BDE0(this);
          ++*(this + 2155);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58CC20 CNGhoulMorgan__vmt1D8 —— CNGhoulMorgan 周期状态槽 vmt1D8：GHOUL_ARM_ATK 攻击判定（53F6A0/649E40/4926A0）
// ------------------------------------------------------------
void /*thiscall*/ CNGhoulMorgan__vmt1D8(uint32_t *this, int ArgList, float a3, int a4, int a5)
{
  uint32_t *v6; // eax
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // eax

  if ( *((uint8_t *)this + 8600) == 1 )
  {
    if ( *((uint8_t *)this + 8624) == 0 )
    {
      v6 = (uint32_t *)(*(int (**)(void))(*this + 700))();
      sub_53F6A0(v6, (int)this);
      v7 = operator new(0xA8u);
      if ( v7 != nullptr )
        v8 = sub_649E40(v7, 400, 5000, 300);
      else
        v8 = nullptr;
      (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v8 + 56))(
        v8,
        this,
        this,
        0,
        0,
        0,
        -1);
      *((uint8_t *)this + 8624) = 1;
    }
    if ( ArgList == 8 )
    {
      v9 = *(uint32_t **)(LODWORD(a3) + 4);
      if ( *v9 == 2 )
      {
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 16));
        v10 = (uint32_t *)(*(this + 1554) + 16);
      }
      else
      {
        if ( *v9 != 3 )
        {
          if ( *v9 == 1 )
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
              this,
              "GHOUL_ARM_ATK",
              -1,
              0,
              0);
          goto LABEL_15;
        }
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 20));
        v10 = (uint32_t *)(*(this + 1554) + 20);
      }
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        100,
        *v10,
        0,
        0,
        0,
        0);
      *(this + 2155) = 0;
    }
LABEL_15:
    if ( *((uint8_t *)this + 8600) == 1 )
      IRDMonster__vmt1D8(ArgList, a3, a4, a5);
  }
}



// ------------------------------------------------------------
// 0x58CD80 CNGhoulMorgan__vmt14C —— CNGhoulMorgan 移动/受击表现槽 vmt14C（含 58BF40 炸弹发射分支）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulMorgan__vmt14C(int *this)
{
  int result; // eax
  int v3; // ebx
  uint32_t *v4; // eax

  CNGhoul__vmt14C(this);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 8
    || (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) != 2
    && sub_41A5E0((unsigned int)(this + 1757)) != 3 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));
  }
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( result == 8 )
  {
    v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148);
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )
    {
      result = *(this + 2155);
      if ( result == 0 && v3 >= 3 )
      {
        v4 = (uint32_t *)(*(this + 1554) + 16);
LABEL_17:
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *v4);
LABEL_18:
        result = sub_58BF40(this);
        ++*(this + 2155);
      }
    }
    else
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result != 3 )
        return result;
      result = *(this + 2155);
      if ( result == 0 && v3 >= 3 )
        goto LABEL_18;
      if ( result == 1 && v3 >= 9 )
      {
        v4 = (uint32_t *)(*(this + 1554) + 20);
        goto LABEL_17;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58CE90 CNGhoulMorgan__vmt524 —— CNGhoulMorgan 技能槽 vmt524
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulMorgan__vmt524(uint32_t *this)
{
  CNGhoul__vmt524(this);
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
           this,
           200,
           *(uint32_t *)(*(this + 1554) + 12),
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x58CED0 CNGhoulNoMercy__vmt1D8 —— CNGhoulNoMercy AI 主状态机 vmt1D8（135 行：状态 4/5/13 切换 + 抓取发起 58C840）
// ------------------------------------------------------------
void /*userpurge*/ sub_58CED0(uint32_t *a1@<ecx>, double a2@<st0>, void *Block, int a4, int a5, int a6)
{
  int v7; // eax
  int v8; // ecx
  void *v9; // edi
  int v10; // ebx
  int v11; // ecx
  int *v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // ebx
  int v20; // edi
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax

  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1);
  if ( v7 == 18 )
  {
    v8 = a1[2169];
    if ( v8 != 0 )
    {
      a1[2168] = 1;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 604))(v8, 1);
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t))(*(uint32_t *)a1[2169] + 612))(a1[2169], 1, 0);
      (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 352))(a1);
    }
    v9 = Block;
  }
  else
  {
    v9 = Block;
    if ( (Block == (void *)3 || Block == (void *)5 || Block == (void *)4 || Block == (void *)9) && v7 == 16 )
    {
      v11 = a1[2164];
      if ( v11 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v11 + 560))(v11, 0, 0, 0, 0);
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[2164] + 564))(a1[2164]);
      }
    }
  }
  v10 = a4;
  if ( v9 == (void *)15 )
  {
    sub_4926A0(*(uint32_t *)(a1[1554] + 12));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)(a1[1554] + 12));
  }
  else if ( a1[2164] != 0 || v9 != (void *)16 )
  {
    if ( v9 == (void *)17 )
    {
      v13 = *a1;
      v14 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 124))(a1, 0);
      v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, v14);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v13 + 136))(a1, v15) == 0
        || (v16 = *a1,
            v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1),
            (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v16 + 132))(a1, v17) == 0) )
      {
        v18 = a1[2164];
        if ( v18 != 0 )
        {
          v19 = *a1;
          v20 = a1[2164];
          v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 128))(v20);
          v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v20 + 124))(v20, v21);
          v23 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v20 + 120))(v20, v22);
          (*(void (/*thiscall*/ **)(uint32_t *, int))(v19 + 112))(a1, v23);
          v10 = a4;
        }
      }
      v24 = *a1;
      a1[2164] = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(v24 + 560))(a1, 0, 0, 0, 0);
      v9 = Block;
    }
    else if ( v9 == (void *)18 )
    {
      *((uint8_t *)a1 + 8620) = 1;
      v25 = sub_45EBE0(**(uint32_t **)(a4 + 4), *(uint32_t *)(*(uint32_t *)(a4 + 4) + 4));
      v26 = __RTDynamicCast(v25, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
      a1[2169] = v26;
      if ( v26 != 0 )
      {
        if ( a1[2170] == 0 )
        {
          if ( operator new(0x68u) != nullptr )
            v27 = sub_58C780(a1);
          else
            v27 = 0;
          a1[2170] = v27;
        }
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)a1[2170] + 56))(
          a1[2170],
          a1[2169],
          a1,
          0,
          0,
          0,
          -1);
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)(a1[1554] + 20));
    }
    else if ( v9 == nullptr )
    {
      a1[2156] = 0;
    }
  }
  else
  {
    v12 = (int *)(a1[1554] + 16);
    *((uint8_t *)a1 + 8620) = 1;
    sub_4926A0(*v12);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)(a1[1554] + 16));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 344))(a1, a1[139]);
    sub_58C840(16, a4);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(a1, "GHOUL_ARM_ATK", -1, 0, 0);
  }
  if ( *((uint8_t *)a1 + 8600) == 1 )
    sub_4E33D0(a1, v10, a2, (int)v9, v10, *(float *)&a5, *(float *)&a6);
}


// ------------------------------------------------------------
// 0x58D1A0 CNGhoulOilSellerOlrek__vmt1D8 —— CNGhoulOilSellerOlrek 周期状态槽 vmt1D8（4DB200 播报）
// ------------------------------------------------------------
void /*thiscall*/ CNGhoulOilSellerOlrek__vmt1D8(int this, int ArgList, float a3, int a4, int a5)
{
  if ( *(uint8_t *)(this + 8600) == 1 )
  {
    if ( ArgList == 5 )
      sub_4DB200(24, 1);
    CNGhoulThrower__vmt1D8((uint32_t *)this, ArgList, a3, a4, a5);
  }
}



// ------------------------------------------------------------
// 0x58D1E0 sub_58D1E0 —— MagmaGhoul 状态辅助：熔岩喷吐参数计算
// ------------------------------------------------------------
int /*thiscall*/ sub_58D1E0(uint32_t *this)
{
  unsigned int i; // esi
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax

  for ( i = 0; ; ++i )
  {
    v3 = *(this + 29);
    v4 = *(uint32_t *)(v3 + 8);
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * i);
    else
      v7 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 529) != 0 )
    {
      v8 = *(this + 29);
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      v11 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &CNMagmaGhoul `RTTI Type Descriptor', 0);
      if ( v11 != 0 )
        *(uint8_t *)(v11 + 8656) = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58D280 sub_58D280 —— MagmaGhoul 状态辅助：受击/死亡表现参数
// ------------------------------------------------------------
int /*thiscall*/ sub_58D280(uint32_t *this)
{
  unsigned int v1; // edi
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // esi
  int v14; // [esp+Ch] [ebp-8h]
  int v15; // [esp+10h] [ebp-4h]

  v1 = 0;
  v15 = 99999;
  v14 = 0;
  while ( 1 )
  {
    v3 = *(this + 29);
    v4 = *(uint32_t *)(v3 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)v1 >= v5 )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && v1 < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * v1);
    else
      v7 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 529) != 0 )
    {
      v8 = *(this + 29);
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && v1 < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * v1);
      else
        v10 = 0;
      v11 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &CNMagmaGhoul `RTTI Type Descriptor', 0);
      v12 = v11;
      if ( v11 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 120))(v11) < v15 )
      {
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 120))(v12);
        v14 = v12;
      }
    }
    ++v1;
  }
  return v14;
}



// ------------------------------------------------------------
// 0x58D350 sub_58D350 —— MagmaGhoul 状态机辅助主入口（699000 时钟 + 58D1E0/58D280 分支）
// ------------------------------------------------------------
char /*thiscall*/ sub_58D350(int *this)
{
  int v2; // esi
  int v3; // edi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // esi
  unsigned int v12; // edi
  int v13; // ecx
  int v14; // edx
  int v15; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int v19; // edx
  uint32_t *v20; // eax
  uint8_t *v21; // esi
  int v22; // edx
  int v23; // [esp+Ch] [ebp-10h]
  uint8_t *v24; // [esp+10h] [ebp-Ch]
  int v25; // [esp+14h] [ebp-8h]
  int v26; // [esp+18h] [ebp-4h]

  v2 = (int)(this + 2157);
  v3 = *(this + 2163);
  if ( sub_699000((int)(this + 2157)) < v3 )
    return 0;
  sub_58D1E0(this);
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  sub_698F90(v2, 10000, 0);
  v5 = sub_58D280(this);
  v6 = v5;
  v24 = (uint8_t *)v5;
  if ( v5 != 0 && (int *)v5 == this )
  {
    v7 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
    v8 = *(uint32_t *)(v7 + 364);
    v9 = v7 + 360;
    v10 = v8 != 0 ? (*(uint32_t *)(v9 + 8) - v8) >> 5 : 0;
    v11 = 224 * v10;
    v23 = 224 * v10;
    v25 = 48 * ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 120))(v6) / 48);
    if ( v25 < v11 )
    {
LABEL_9:
      v26 = 0;
      while ( 1 )
      {
        v12 = 0;
        while ( 1 )
        {
          v13 = *(this + 29);
          v14 = *(uint32_t *)(v13 + 8);
          v15 = v14 != 0 ? (*(uint32_t *)(v13 + 12) - v14) >> 2 : 0;
          if ( (int)v12 >= v15 )
            break;
          v16 = *(uint32_t *)(v13 + 8);
          if ( v16 != 0 && v12 < (*(uint32_t *)(v13 + 12) - v16) >> 2 )
            v17 = *(uint32_t *)(v16 + 4 * v12);
          else
            v17 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 40))(v17, 529) == 0 )
            goto LABEL_31;
          v18 = *(this + 29);
          v19 = *(uint32_t *)(v18 + 8);
          if ( v19 != 0 && v12 < (*(uint32_t *)(v18 + 12) - v19) >> 2 )
            v20 = *(uint32_t **)(v19 + 4 * v12);
          else
            v20 = nullptr;
          v21 = __RTDynamicCast(v20, 0, &CNRDObject `RTTI Type Descriptor', &CNMagmaGhoul `RTTI Type Descriptor', 0);
          if ( v24 == v21 )
          {
            (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);
            ++v12;
          }
          else
          {
            if ( v21 != nullptr
              && v21[8656] == 0
              && *((uint32_t *)v21 + 2155) != v25
              && *((uint32_t *)v21 + 2156) != v26
              && (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(*this + 136))(this, v25, v26, 0) != 0 )
            {
              v22 = *(uint32_t *)v21;
              *((uint32_t *)v21 + 2156) = v26;
              *((uint32_t *)v21 + 2155) = v25;
              v21[8656] = 1;
              (*(void (/*thiscall*/ **)(uint8_t *, int, int))(v22 + 1144))(v21, v25, v26);
              break;
            }
LABEL_31:
            ++v12;
          }
        }
        v26 += 48;
        if ( v26 >= 480 )
        {
          v25 += 48;
          if ( v25 >= v23 )
            return 1;
          goto LABEL_9;
        }
      }
    }
  }
  return 1;
}


// ------------------------------------------------------------
// 0x58D560 CNMagmaGhoul__vmt14C —— CNMagmaGhoul 移动/受击表现槽 vmt14C（转发 58D350）
// ------------------------------------------------------------
char /*thiscall*/ CNMagmaGhoul__vmt14C(int *this)
{
  sub_58D350(this);
  return CNGhoul__vmt14C(this);
}



// ------------------------------------------------------------
// 0x58D570 sub_58D570 —— NoMercy 表现辅助（4E0CD0 目标特效）
// ------------------------------------------------------------
void /*thiscall*/ sub_58D570(int *this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // eax
  void *v5; // ecx
  char v6[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v8; // [esp+10h] [ebp-14h]
  int v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = nullptr;
  v8 = 0;
  v9 = 0;
  v2 = *this;
  v10 = 0;
  if ( (*(int (/*thiscall*/ **)(int *))(v2 + 840))(this) == 0 )
  {
    v3 = *(this + 2163);
    if ( sub_699000((int)(this + 2157)) >= v3 )
    {
      if ( *(this + 2156) == 0 )
      {
        v4 = *(this + 1813);
        if ( v4 != 0
          && (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, v4, 0) > 200
          && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
        {
          *(this + 2156) = 1;
        }
      }
      *((uint8_t *)this + 8641) = 0;
      *((uint8_t *)this + 8642) = 0;
      sub_698F90((int)(this + 2157), 5000, 0);
    }
  }
  if ( *(this + 2156) != 1 )
    goto LABEL_13;
  *(this + 2156) = 2;
  sub_4E0CD0(273, 0, v6, 300);
  v5 = Block;
  if ( Block == nullptr )
    return;
  if ( (v8 - (int)Block) >> 2 != 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 352))(this);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 15, 0, 0, 0);
LABEL_13:
    v5 = Block;
  }
  if ( v5 != nullptr )
    j__free(v5);
}



// ------------------------------------------------------------
// 0x58D690 sub_58D690 —— NoMercy 表现辅助 2（4E5F70/431230 粒子与动画）
// ------------------------------------------------------------
void /*thiscall*/ sub_58D690(int *this, int a2)
{
  int v2; // esi
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

  v2 = a2;
  if ( a2 != 0 )
  {
    v4 = *this;
    v8 = 0.0;
    v9 = 0.0;
    v10 = 0.0;
    v11 = 0;
    v12 = 0;
    v13 = 0;
    if ( (*(int (/*thiscall*/ **)(int *))(v4 + 152))(this) == 1 )
      v5 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    else
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 120))(v2);
    v6 = *this;
    a2 = v5 + 20;
    v8 = (float)(v5 + 20);
    a2 = (*(int (/*thiscall*/ **)(int *))(v6 + 124))(this) + 1;
    v7 = *this;
    v9 = (float)a2;
    a2 = (*(int (/*thiscall*/ **)(int *))(v7 + 128))(this) + 80;
    v10 = (float)a2;
    sub_4E5F70(0, (int)this, v2, &v8, 1, 1);
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 308))(v2) != 0 )
    {
      Block = nullptr;
      v16 = 0;
      v17 = 0;
      v18 = 0;
      a2 = 4;
      sub_431230((int)v14, &a2);
      a2 = 0;
      sub_431230((int)v14, &a2);
      a2 = 1;
      sub_431230((int)v14, &a2);
      a2 = 500;
      sub_431230((int)v14, &a2);
      a2 = 300;
      sub_431230((int)v14, &a2);
      (*(void (/*thiscall*/ **)(int, int, uint8_t *, int, uint32_t))(*(uint32_t *)v2 + 560))(v2, 4, v14, 2, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 564))(v2);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// ------------------------------------------------------------
// 0x58D7F0 sub_58D7F0 —— NoMercy 移动/受击表现主函数（117 行，58D690 调用 + 432E50 播报）
// ------------------------------------------------------------
int /*usercall*/ sub_58D7F0@<eax>(int *a1@<ecx>, int a2@<ebx>)
{
  int v3; // eax
  int v4; // edx
  int v5; // eax
  uint64_t v6; // rax
  int v7; // edi
  int v8; // eax
  int result; // eax
  int v10; // ecx
  int v11; // ebx
  int v12; // edi
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // ecx
  unsigned int v17; // eax
  int v18; // ecx
  int v19; // [esp+8h] [ebp-4h]

  v3 = (*(int (/*thiscall*/ **)(int *))(*a1 + 840))(a1);
  v4 = *a1;
  if ( v3 == 15 )
  {
    v5 = (*(int (/*thiscall*/ **)(int *))(v4 + 200))(a1);
    v6 = (uint64_t)sub_4049C0(800.0, 0.0, *(uint32_t *)(v5 + 148), 5);
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(*a1 + 876))(a1, 0, v6, v6, 0, 100, 1);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 876))(a1, 1, 0, 0, 0, 0, 0);
    v7 = *a1;
    v8 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 152))(a1, 4);
    (*(void (/*thiscall*/ **)(int *, int))(v7 + 896))(a1, v8);
    (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*a1 + 888))(a1, 2, 2, 1000, 1000);
    result = (*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1);
    if ( *(uint8_t *)(result + 170) != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*a1 + 308))(a1);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 0, 0, 0, 0);
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(int *))(v4 + 840))(a1);
    if ( result == 16 )
    {
      v10 = a1[2164];
      if ( v10 != 0 )
      {
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 840))(v10) == 9 )
        {
          if ( *(int *)((*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1) + 148) >= 2 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 308))(a1) != 0 && *((uint8_t *)a1 + 8620) != 0 )
              sub_58D690(a1[2164]);
            *((uint8_t *)a1 + 8620) = 0;
          }
          (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)a1[2164] + 604))(a1[2164], 0, a2);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1[2164] + 612))(a1[2164], 1, 1);
          if ( (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1) != 0 )
            v11 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1) + 100;
          else
            v11 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1) - 100;
          v12 = (*(int (/*thiscall*/ **)(int *))(*a1 + 124))(a1) - 1;
          v19 = (*(int (/*thiscall*/ **)(int *))(*a1 + 128))(a1);
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)a1[2164] + 136))(
                 a1[2164],
                 v11,
                 v12,
                 0) != 0
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[2164] + 132))(a1[2164], v19) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1[2164] + 112))(a1[2164], v11, v12);
          }
          else
          {
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1[2164] + 112))(a1[2164], a1[2165], a1[2166]);
          }
        }
        else if ( *((uint8_t *)a1 + 8620) == 1
               && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[2164] + 840))(a1[2164]) != 5
               && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1[2164] + 308))(a1[2164]) != 0 )
        {
          v13 = *(uint32_t *)a1[2164];
          v14 = (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1);
          v15 = sub_432E50(v14);
          (*(void (/*thiscall*/ **)(int, int))(v13 + 144))(a1[2164], v15);
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)a1[2164] + 560))(a1[2164], 9, 0, 2, 0);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a1[2164] + 564))(a1[2164]);
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 0, 0, 0, 0);
      }
      result = (*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1);
      if ( *(uint8_t *)(result + 170) != 0
        || (v16 = a1[2164]) != 0
        && (v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 684))(v16), (result = sub_41A5E0(v17)) <= 0) )
      {
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 17, 0, 0, 0);
        v18 = a1[2164];
        if ( v18 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 604))(v18, 1);
          (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)a1[2164] + 612))(a1[2164], 1, 0);
        }
        return (*(int (/*thiscall*/ **)(int *))(*a1 + 352))(a1);
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x58DB10 CNGhoulNoMercy__vmt14C —— CNGhoulNoMercy 移动/受击表现槽 vmt14C（111 行：58D7F0/58D570/58D690 分支）
// ------------------------------------------------------------
char /*usercall*/ CNGhoulNoMercy__vmt14C@<al>(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
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
  int v18; // ecx
  unsigned int v19; // eax
  int v21; // [esp+4h] [ebp-4h] BYREF

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 840))(a1) == 15
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 840))(a1) == 16 )
  {
    sub_58D7F0((int *)a1, a2);
  }
  else
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 840))(a1) == 0 )
    {
      sub_58D570((int *)a1);
      return CNGhoul__vmt14C((uint32_t *)a1);
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 840))(a1) == 18 )
    {
      v5 = *(uint32_t *)(a1 + 8676);
      if ( v5 != 0 )
      {
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 840))(v5) == 9 )
        {
          if ( *(int *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 200))(a1, a3) + 148) >= 2 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0 )
            {
              sub_58D690((int *)a1, *(uint32_t *)(a1 + 8676));
              v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 340))(a1);
              v7 = *(uint32_t *)(a1 + 8676);
              v8 = *(uint32_t *)a1;
              v21 = **(uint32_t **)(v6 + 64);
              v9 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int *))(*(uint32_t *)v7 + 56))(
                     v7,
                     0,
                     0,
                     0,
                     0,
                     0,
                     4,
                     0,
                     4,
                     &v21);
              (*(void (/*thiscall*/ **)(int, int, int))(v8 + 580))(a1, 30202, v9);
            }
            *(uint8_t *)(a1 + 8620) = 0;
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 8676) + 604))(*(uint32_t *)(a1 + 8676), 0);
          (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(a1 + 8676) + 612))(*(uint32_t *)(a1 + 8676), 1, 1);
          v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1) != 0
              ? (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 100
              : (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 100;
          v11 = *(int **)(a1 + 8676);
          v12 = *v11;
          v13 = (*(int (/*thiscall*/ **)(int *, int))(*v11 + 128))(v11, a2);
          v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v13);
          (*(void (/*thiscall*/ **)(uint32_t, int, int))(v12 + 112))(*(uint32_t *)(a1 + 8676), v10, v14 - 1);
        }
        else if ( *(uint8_t *)(a1 + 8620) == 1
               && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8676) + 840))(*(uint32_t *)(a1 + 8676)) != 5
               && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8676) + 308))(*(uint32_t *)(a1 + 8676)) != 0 )
        {
          v15 = **(uint32_t **)(a1 + 8676);
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
          v17 = sub_432E50(v16);
          (*(void (/*thiscall*/ **)(uint32_t, int))(v15 + 144))(*(uint32_t *)(a1 + 8676), v17);
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(a1 + 8676) + 560))(
            *(uint32_t *)(a1 + 8676),
            9,
            0,
            2,
            0);
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8676) + 564))(*(uint32_t *)(a1 + 8676));
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
      }
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1) + 170) != 0
        || (v18 = *(uint32_t *)(a1 + 8676)) != 0
        && (v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 684))(v18), sub_41A5E0(v19) <= 0) )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
        return CNGhoul__vmt14C((uint32_t *)a1);
      }
    }
  }
  return CNGhoul__vmt14C((uint32_t *)a1);
}



// ------------------------------------------------------------
// 0x58DD70 CNGhoulNoMercy__vmt1F4 —— CNGhoulNoMercy 技能槽 vmt1F4（92 行：431230 动作 + 5E5260 成员清理）
// ------------------------------------------------------------
int /*userpurge*/ CNGhoulNoMercy__vmt1F4@<eax>(int a1@<ecx>, int a2@<ebx>, int a3, int a4, int a5)
{
  char v6; // al
  int v7; // esi
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // eax
  void *v18; // [esp+8h] [ebp-1Ch] BYREF
  int v19; // [esp+Ch] [ebp-18h]
  int v20; // [esp+10h] [ebp-14h]
  int v21; // [esp+14h] [ebp-10h]
  int v22; // [esp+20h] [ebp-4h]

  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1);
  v7 = a3;
  if ( v6 != 0 && (uint8_t)a5 == 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 840))(a1) == 15
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 273) != 0 )
    {
      v8 = __RTDynamicCast(
             v7,
             0,
             &IRDCollisionObject `RTTI Type Descriptor',
             &IRDActiveObject `RTTI Type Descriptor',
             0);
      v9 = v8;
      if ( v8 != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 948))(v8, a2) != 0
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 840))(v9) == 0
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 568))(a1) != 16 )
        {
          v19 = 0;
          v20 = 0;
          v21 = 0;
          v10 = *(uint32_t *)v7;
          v22 = 0;
          a3 = (*(int (/*thiscall*/ **)(int))(v10 + 48))(v7);
          sub_431230((int)&v18, &a3);
          a3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 52))(v7);
          sub_431230((int)&v18, &a3);
          (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 16, &v18, 0, 0);
          v22 = -1;
          sub_5E5260(&v18);
        }
        v11 = *(uint32_t *)v7;
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
        v13 = sub_432E50(v12);
        (*(void (/*thiscall*/ **)(int, int))(v11 + 144))(v7, v13);
      }
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 840))(a1) == 8
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 908))(a1) == 1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 529) != 0
      && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 340))(v7) != 405
      && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 340))(v7) != 406
      && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 340))(v7) != 422 )
    {
      v14 = __RTDynamicCast(v7, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      if ( v14 != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 948))(v14) != 0
        && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 840))(v14) == 0 )
      {
        v19 = 0;
        v20 = 0;
        v21 = 0;
        v15 = *(uint32_t *)v7;
        v22 = 1;
        a3 = (*(int (/*thiscall*/ **)(int))(v15 + 48))(v7);
        sub_431230((int)&v18, &a3);
        a3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 52))(v7);
        sub_431230((int)&v18, &a3);
        (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 18, &v18, 0, 0);
        v22 = -1;
        sub_5E5260(&v18);
      }
    }
  }
  return IRDMonster__vmt1F4(v7, a4, a5);
}



// ------------------------------------------------------------
// 0x58DFE0 sub_58DFE0 —— R_GHOUL 部件标签注册：R_GHOUL/R_GHOUL_ATK/R_GHOUL_DIE/R_GHOUL_DMG（4A4EA0）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_58DFE0(uint8_t *this, char ArgList, int a3, char a4)
{
  uint32_t *v5; // eax

  sub_4A4EA0(ArgList, a3);
  *(uint32_t *)this = &vftbl_CNGhoul;
  *(this + 8600) = 0;
  *((uint32_t *)this + 2151) = 0;
  sub_58BA00(this);
  if ( a4 == 1 )
  {
    *((uint32_t *)this + 1639) = 0;
    *((uint32_t *)this + 2151) = -1;
    *(this + 8600) = 1;
  }
  else
  {
    v5 = *((uint32_t **)this + 1554);
    *((uint32_t *)this + 1639) = 14;
    IRDActiveObject__vmtC4(*v5);
  }
  sub_4015C0("R_GHOUL_ATK", 0xBu);
  sub_4015C0("R_GHOUL_DMG", 0xBu);
  sub_4015C0("R_GHOUL_DIE", 0xBu);
  sub_4015C0("R_GHOUL", 7u);
  return this;
}



// ------------------------------------------------------------
// 0x58E0D0 sub_58E0D0 —— CNGhoul 析构成员清理（4A50F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58E0D0(uint32_t *this)
{
  *this = &vftbl_CNGhoul;
  return sub_4A50F0();
}



// ------------------------------------------------------------
// 0x58E0E0 sub_58E0E0 —— CNGhoul 构造：调用 58DFE0 注册部件标签
// ------------------------------------------------------------
int /*thiscall*/ sub_58E0E0(int this, char ArgList, int a3, char a4)
{
  uint16_t *v5; // eax
  int i; // ecx
  uint32_t *v8; // eax

  sub_58DFE0((uint8_t *)this, ArgList, a3, a4);
  *(uint32_t *)this = &vftbl_CNGhoulThrower;
  *(uint32_t *)(this + 8620) = 1;
  *(uint32_t *)(this + 6792) = 1;
  *(uint32_t *)(this + 6796) = 1;
  *(uint32_t *)(this + 6800) = 3;
  *(uint32_t *)(this + 6804) = 4;
  *(uint32_t *)(this + 6808) = 4;
  v5 = (uint16_t *)(this + 8370);
  for ( i = 26; i != 0; --i )
  {
    *v5 = 50;
    v5 += 2;
  }
  if ( a4 == 1 )
  {
    *(uint32_t *)(this + 6556) = 0;
    *(uint32_t *)(this + 8604) = -1;
    *(uint8_t *)(this + 8600) = 1;
  }
  else
  {
    v8 = *(uint32_t **)(this + 6216);
    *(uint32_t *)(this + 6556) = 14;
    IRDActiveObject__vmtC4(*v8);
  }
  return this;
}



// ------------------------------------------------------------
// 0x58E1D0 sub_58E1D0 —— CNGhoul 派生构造共用：部件标签注册（58DFE0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58E1D0(int this, char ArgList, int a3, char a4)
{
  char v5; // dl
  uint32_t *v7; // eax

  sub_58DFE0((uint8_t *)this, ArgList, a3, 0);
  *(uint32_t *)this = &vftbl_CNGhoulNoMercy;
  *(uint8_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8628) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 8636) = 0;
  *(uint8_t *)(this + 8640) = 1;
  *(uint8_t *)(this + 8642) = 0;
  *(uint8_t *)(this + 8641) = 0;
  *(uint32_t *)(this + 8652) = 0;
  *(uint32_t *)(this + 8648) = 0;
  *(uint32_t *)(this + 8644) = 0;
  CNGhoulNoMercy__vmt4A8(this);
  if ( a4 == v5 )
  {
    *(uint32_t *)(this + 6556) = 0;
    *(uint32_t *)(this + 8604) = -1;
    *(uint8_t *)(this + 8600) = v5;
  }
  else
  {
    v7 = *(uint32_t **)(this + 6216);
    *(uint32_t *)(this + 6556) = 14;
    IRDActiveObject__vmtC4(*v7);
  }
  return this;
}



// ------------------------------------------------------------
// 0x58E2B0 sub_58E2B0 —— CNGhoulNoMercy 析构成员清理（4A50F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58E2B0(uint32_t *this)
{
  *(this + 2157) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 8632) = 0;
  *this = &vftbl_CNGhoul;
  return sub_4A50F0();
}



// ------------------------------------------------------------
// 0x58E2D0 CNGhoul__vmt0 —— CNGhoul 标量删除析构（vmt0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNGhoul__vmt0(uint32_t *Block, char a2)
{
  sub_58E0D0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x58E300 CNGhoulNoMercy__vmt0 —— CNGhoulNoMercy 标量删除析构（vmt0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNGhoulNoMercy__vmt0(uint32_t *Block, char a2)
{
  sub_58E2B0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x58E330 CNGhoulMorgan__vmt51C —— CNGhoulMorgan 技能槽 vmt51C（4BA9E0）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulMorgan__vmt51C(void *this)
{
  char *v2; // eax
  char *v3; // eax
  int result; // eax

  v2 = (char *)operator new(0x544u);
  if ( v2 != nullptr )
    v3 = sub_4BA9E0(v2, "Monster/Ghoul/GhoulMorgan/GhoulThrowerClothes.equ", 0);
  else
    v3 = nullptr;
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// ------------------------------------------------------------
// 0x58E3B0 CNGhoulOilSellerOlrek__vmt51C —— CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulOilSellerOlrek__vmt51C(void *this)
{
  char *v2; // eax
  char *v3; // eax
  int v4; // eax
  char *v5; // eax
  char *v6; // eax
  int result; // eax

  v2 = (char *)operator new(0x544u);
  if ( v2 != nullptr )
    v3 = sub_4BA9E0(v2, "monster/Ghoul/GhoulOilSellerOlrek/backpack_-100.equ", 0);
  else
    v3 = nullptr;
  v4 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 4))(v4, 1);
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v6 = sub_4BA9E0(v5, "monster/Ghoul/GhoulOilSellerOlrek/backpack_100.equ", 0);
  else
    v6 = nullptr;
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// ------------------------------------------------------------
// 0x58E480 sub_58E480 —— CNGhoul 派生构造共用 2（部件标签注册 58DFE0）
// ------------------------------------------------------------
int /*thiscall*/ sub_58E480(int this, char ArgList, int a3)
{
  uint16_t *v4; // eax
  int i; // ecx
  uint32_t *v6; // eax

  sub_58DFE0((uint8_t *)this, ArgList, a3, 0);
  *(uint32_t *)this = &vftbl_CNGhoulMorgan;
  v4 = (uint16_t *)(this + 8370);
  for ( i = 26; i != 0; --i )
  {
    *v4 = 50;
    v4 += 2;
  }
  CNGhoulMorgan__vmt51C(this);
  v6 = *(uint32_t **)(this + 6216);
  *(uint8_t *)(this + 8624) = 0;
  *(uint32_t *)(this + 6556) = 14;
  IRDActiveObject__vmtC4(*v6);
  *(uint32_t *)(this + 6792) = 1;
  *(uint32_t *)(this + 6796) = 1;
  *(uint32_t *)(this + 6800) = 3;
  *(uint32_t *)(this + 6804) = 4;
  *(uint32_t *)(this + 6808) = 4;
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
void /*thiscall*/ IRDActiveObject__vmt144(uint32_t *this, int a2, int a3, int a4, int a5)
{
  uint32_t *v7; // edi
  uint32_t *v8; // edi
  int j; // [esp+14h] [ebp+8h]
  int i; // [esp+20h] [ebp+14h]

  if ( (uint8_t)a2 != 0 )
  {
    nullsub_2(a2, a3, a4, a5);
    v8 = this + 1557;
    for ( i = 17; i != 0; --i )
    {
      if ( *v8 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)*v8 + 24))() != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(*(uint32_t *)*v8 + 52))(*v8, a2, a3, a4, a5);
      ++v8;
    }
    sub_53F9D0(a2, a3, a4, a5);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 872))(this, a3, a4, a5);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1016))(this);
  }
  else
  {
    sub_53F9D0(0, a3, a4, a5);
    v7 = this + 1573;
    for ( j = 17; j != 0; --j )
    {
      if ( *v7 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)*v7 + 24))() != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, int, int))(*(uint32_t *)*v7 + 52))(*v7, 0, a3, a4, a5);
      --v7;
    }
    nullsub_2(0, a3, a4, a5);
  }
}



// ------------------------------------------------------------
// 0x58E660 sub_58E660 —— 食尸鬼族通用：粒子/部件参数复位（供 vmt1D8/vmt14C 调用）
// ------------------------------------------------------------
int /*thiscall*/ sub_58E660(uint32_t *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 988))(this) != 0 )
    {
      if ( *(this + 1542) != 0 )
        return (*(int (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t))(*this + 560))(1, 0, 0, 0);
      else
        return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(0, 0, 0, 0);
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 3);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t))(*this + 560))(this, 9, 0, 2, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58E6D0 sub_58E6D0 —— 食尸鬼族通用：41A5E0 粒子挂载（状态表现）
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_58E6D0(void *this)
{
  int v3; // [esp+8h] [ebp-4h]

  v3 = sub_41A5E0((unsigned int)this + 900);
  return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 914)));
}



// ------------------------------------------------------------
// 0x58E710 sub_58E710 —— 食尸鬼族通用：41A5E0 粒子挂载（第二变体）
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_58E710(void *this)
{
  int v3; // [esp+8h] [ebp-4h]

  v3 = sub_41A5E0((unsigned int)this + 928);
  return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 942)));
}



// ------------------------------------------------------------
// 0x58E750 IRDActiveObject__vmt148 —— IRDActiveObject__vmt148 2D 精灵绘制：491530/491630 批次对 + 418DD0 取精灵 + 424760 贴图
// ------------------------------------------------------------
int /*thiscall*/ IRDActiveObject__vmt148(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int v7; // eax
  int v8; // ebx
  int v9; // ebx
  bool v10; // zf
  int v11; // eax
  uint32_t *v12; // esi
  int result; // eax
  uint32_t *v14; // edi
  int i; // [esp+14h] [ebp+8h]
  unsigned int v16; // [esp+18h] [ebp+Ch]
  int j; // [esp+18h] [ebp+Ch]

  if ( (uint8_t)a2 != 0 )
  {
    CNRDObject__vmt148(this, a2, a3, a4, a5);
    v14 = this + 1557;
    for ( i = 17; i != 0; --i )
    {
      if ( *v14 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v14 + 24))(*v14) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(*(uint32_t *)*v14 + 56))(*v14, a2, a3, a4, a5);
      ++v14;
    }
    return sub_53FAB0(a2, a3, a4, a5);
  }
  else
  {
    v7 = *(uint32_t *)(dword_8F7A24 + 12);
    v8 = a3;
    if ( (v7 == 4 || v7 == 6) && dword_99FEC0 != 0 && (uint8_t)sub_48F620(dword_99FEC0) != 0 )
    {
      if ( this == (uint32_t *)dword_8F7C04
        || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 940))(this) == 0
        || (v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this),
            v10 = v9 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04),
            v8 = a3,
            v10) )
      {
        v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this);
        if ( v16 < 4 )
        {
          sub_491530(2, 0);
          v11 = sub_418DD0(v16 + 39);
          sub_424760(dword_79C0B0, v8 - 63, a4 - 21, v11, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);
          sub_491630(2);
        }
      }
    }
    CNRDObject__vmt148(this, 0, v8, a4, a5);
    sub_53FAB0(0, v8, a4, a5);
    v12 = this + 1573;
    for ( j = 17; j != 0; --j )
    {
      if ( *v12 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)*v12 + 24))() != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, int, int))(*(uint32_t *)*v12 + 56))(*v12, 0, v8, a4, a5);
      --v12;
      result = j - 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x58E920 IRDActiveObject__vmt1D8 —— IRDActiveObject__vmt1D8 主状态机（874 行）：CONDITION_STUN/DOWN_HEAVY/DOWN_LIGHT/DOWN_MIDDLE/JUMP_START/JUMP_END 状态动画与物理分支
// ------------------------------------------------------------
char /*thiscall*/ sub_58E920(int *this, int a2, int a3, float a4, float a5)
{
  int v6; // ebx
  int v7; // eax
  int v9; // eax
  int v10; // edx
  int v11; // edi
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
  int v29; // edx
  int v30; // ebx
  int v31; // eax
  int v32; // ecx
  int v33; // eax
  int v34; // edi
  int v35; // eax
  int v36; // edi
  int v37; // edi
  int v38; // eax
  int v39; // eax
  int v40; // edx
  int v41; // ebx
  bool v42; // zf
  int v43; // eax
  int v44; // eax
  int v45; // eax
  int v46; // edi
  bool v47; // bl
  int v48; // ebx
  int v49; // eax
  int v50; // eax
  int v51; // eax
  void *v52; // ecx
  int v53; // eax
  int v54; // edi
  int v55; // ebx
  int v56; // eax
  int v57; // eax
  int v58; // ecx
  int v59; // eax
  uint32_t *v60; // eax
  int v61; // ecx
  int v62; // edx
  int v63; // eax
  int v64; // eax
  int v65; // edx
  int v66; // ebx
  int v67; // edx
  uint32_t *v68; // eax
  int v69; // eax
  int v70; // eax
  int v71; // edi
  int v72; // eax
  int v73; // eax
  int v74; // eax
  uint32_t *v75; // eax
  int v76; // eax
  int v77; // eax
  int v78; // eax
  int v79; // eax
  int v80; // eax
  int v81; // ecx
  int v82; // eax
  uint32_t *v83; // eax
  int v84; // edi
  bool v85; // bl
  int v86; // ebx
  int v87; // eax
  int v88; // eax
  int v89; // eax
  void *v90; // ecx
  uint32_t *v91; // eax
  uint32_t *v92; // eax
  unsigned int v93; // ebx
  int v94; // eax
  int v95; // eax
  int v96; // ecx
  int v97; // ecx
  uint32_t *v98; // edi
  int i; // ebx
  int v100; // eax
  int v101; // edi
  int v102; // ebx
  int v104; // [esp+70h] [ebp-50h]
  int v105; // [esp+70h] [ebp-50h]
  int v106; // [esp+74h] [ebp-4Ch]
  float v107; // [esp+74h] [ebp-4Ch]
  uint8_t v108[16]; // [esp+84h] [ebp-3Ch] BYREF
  uint8_t v109[8]; // [esp+94h] [ebp-2Ch] BYREF
  double v110; // [esp+9Ch] [ebp-24h]
  int v111; // [esp+A4h] [ebp-1Ch]
  int v112; // [esp+A8h] [ebp-18h]
  int v113; // [esp+ACh] [ebp-14h]
  int v114; // [esp+B0h] [ebp-10h]
  int v115; // [esp+BCh] [ebp-4h]
  int v116; // [esp+CCh] [ebp+Ch]
  bool v117; // [esp+CFh] [ebp+Fh]
  float v118; // [esp+D0h] [ebp+10h]
  float v119; // [esp+D4h] [ebp+14h]
  float v120; // [esp+D4h] [ebp+14h]

  v6 = *(this + 1639);
  v7 = *this;
  v112 = v6;
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v7 + 776))(this, 16) == 0
    || a2 != 6
    || *(uint32_t *)(v9 = *(uint32_t *)(a3 + 4)) != 0 )
  {
    if ( v6 != 0 )
    {
      if ( v6 == 4 )
        (*(void (/*thiscall*/ **)(int *, int))(*this + 776))(this, 3);
    }
    else
    {
      (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 1);
    }
    switch ( a2 )
    {
      case 0:
        v10 = *this;
        v106 = *(this + 1540);
        *((uint8_t *)this + 6752) = 1;
        (*(void (/*thiscall*/ **)(int *, int))(v10 + 196))(this, v106);
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 0, 143, 119, 1, 0, 0);
        (*(void (/*thiscall*/ **)(int *, int, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 1, 114, 95, 1, 0, 0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
        if ( *(this + 81) != 0 && (v11 = *(this + 81) - (*(int (/*thiscall*/ **)(int *))(*this + 128))(this)) != 0 )
        {
          sub_495890(0, v11 <= 0 ? 1000 : -1000);
          sub_4A0550(v11);
          sub_4A0600(2);
        }
        else
        {
          sub_494F20(2, 0.0);
          sub_495890(2, 0);
        }
        if ( v112 != 4 || (*(uint8_t *)(this + 162) & 2) == 0 )
          goto LABEL_152;
        goto LABEL_15;
      case 1:
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1542));
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
        sub_494F20(2, 0.0);
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
        sub_495890(2, 0);
        if ( v112 == 4 && (*(uint8_t *)(this + 162) & 2) != 0 )
        {
LABEL_15:
          sub_49C620(0, 1, 0);
          sub_49C5F0(0, 0, 0, 500);
        }
        goto LABEL_152;
      case 2:
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1542));
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
        sub_494F20(2, 0.0);
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
        sub_495890(2, 0);
        goto LABEL_152;
      case 3:
        v12 = *this;
        *(this + 1689) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8);
        v13 = *(int **)(a3 + 4);
        v14 = v13[3];
        v15 = *v13;
        v112 = v15;
        if ( v15 == 4 )
          v112 = (*(int (/*thiscall*/ **)(int *))(v12 + 152))(this);
        else
          (*(void (/*thiscall*/ **)(int *, int))(v12 + 144))(this, v15);
        v113 = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4);
        if ( v113 == -1 )
        {
          v16 = 333;
          v17 = 800;
          *(this + 1690) = 333;
        }
        else
        {
          if ( v14 == 2 )
          {
            v17 = 1;
            v16 = 1;
          }
          else
          {
            v17 = 400;
            v16 = 150;
          }
          v18 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
          if ( 2000 - sub_58E6D0(v18) <= 0 )
          {
            v116 = 0;
          }
          else
          {
            v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
            v116 = 2000 - sub_58E6D0(v19);
          }
          v20 = (uint64_t)((double)v116 * 0.25);
          *(this + 1690) = v20;
          v21 = v113 * (int)v20 / 100;
          if ( v21 <= 1 )
            v21 = 1;
          *(this + 1690) = v21;
          if ( v16 > v21 )
            v16 = v21;
        }
        v22 = -1000 * v17 / v16;
        if ( *((uint8_t *)this + 7144) == 0 )
        {
          v17 = 0;
          v22 = 0;
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(this, 0, v17, v17, 0, v22, 1);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
        sub_494F20(2, 0.0);
        v23 = *this;
        v24 = sub_432E50(v112);
        (*(void (/*thiscall*/ **)(int *, int, int))(v23 + 896))(this, v24, 4);
        sub_495890(2, 0);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + *(this + 1689) + 1543));
        goto LABEL_152;
      case 4:
        v113 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
        if ( **(uint32_t **)(a3 + 4) != 4 )
          v113 = **(uint32_t **)(a3 + 4);
        v25 = *this;
        *(this + 1706) = 0;
        *(this + 1707) = (*(int (/*thiscall*/ **)(int *))(v25 + 120))(this);
        v26 = *this;
        *(this + 1705) = 0;
        v27 = (*(int (/*thiscall*/ **)(int *, int))(v26 + 672))(this, 3);
        v28 = sub_4B0D20(v27);
        v29 = *(this + 1708);
        v30 = v28;
        v31 = *(uint32_t *)(a3 + 4);
        v32 = *(uint32_t *)(v31 + 8);
        v33 = *(uint32_t *)(v31 + 4);
        HIDWORD(v110) = v30;
        v117 = v32 == 1;
        v111 = v29;
        *(this + 1708) = v33;
        if ( v32 == 1 )
        {
          v34 = *(uint32_t *)(a3 + 4);
          v35 = *(uint32_t *)(v34 + 12);
          v36 = *(uint32_t *)(v34 + 16);
          *(this + 1705) = (uint64_t)sub_495430(v35, v30);
          v37 = (uint64_t)sub_495430(v36, v30);
          v38 = *(this + 1705) / 2;
          *(this + 1705) = v38;
          if ( v38 < 0 )
          {
            v39 = sub_432E50(v113);
            v40 = -*(this + 1705);
            v113 = v39;
            *(this + 1705) = v40;
          }
          v41 = v37 * v37 / (-2 * sub_4957F0(1));
          v114 = v41;
          if ( v37 < 0 )
          {
            v41 = -v41;
            v114 = v41;
          }
          (*(void (/*thiscall*/ **)(int *, int))(*this + 144))(this, v113);
          if ( *(this + 1708) == 1 && v37 > 0 && v41 < 1 )
          {
            v41 = 1;
            v114 = 1;
          }
        }
        else
        {
          *(this + 1705) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 12) / 2;
          v42 = *(this + 1708) == 1;
          v41 = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 16);
          v114 = v41;
          if ( v42 && v41 <= 0 && (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) <= 0 )
          {
            *(this + 1708) = 2;
            byte_9B9324 = 1;
          }
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1545));
        v43 = *(this + 1708);
        if ( v43 == 0 )
          goto LABEL_66;
        if ( v43 == 1 )
        {
          if ( v112 == 4 && v111 >= 1 )
            v114 = v41 / 4;
          if ( !v117 )
          {
            if ( SHIDWORD(v110) > 60000 )
            {
              if ( SHIDWORD(v110) > 100000 )
                (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(*this + 212))("DOWN_HEAVY", -1, 0, 0);
              else
                (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(*this + 212))("DOWN_MIDDLE", -1, 0, 0);
            }
            else
            {
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                this,
                "DOWN_LIGHT",
                -1,
                0,
                0);
            }
LABEL_67:
            v44 = *(this + 1708);
            if ( (v44 == 1 || v44 == 2) && *(this + 29) != 0 )
            {
              if ( v44 == 1 )
                v45 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 924))(this, 0);
              else
                v45 = (*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 1);
              v46 = dword_8F8270[v45];
              v47 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0;
              *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v46 + 28))(v46) + 84) = v47;
              v48 = *(uint32_t *)v46;
              v49 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
              v50 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v49);
              v51 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v50);
              (*(void (/*thiscall*/ **)(int, int))(v48 + 40))(v46, v51);
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v46 + 12))(v46, 0);
              (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v46 + 92))(v46, v109);
              v52 = (void *)*(this + 29);
              v115 = 0;
              sub_4600B0(v52, 2, 0, (int)v109);
              v115 = -1;
              sub_5E5260(v109);
            }
          }
        }
        else
        {
          if ( v43 == 2 )
          {
            *(this + 1705) = 0;
            v114 = 0;
          }
LABEL_66:
          if ( !v117 )
            goto LABEL_67;
        }
        sub_432FA0();
        v110 = (double)*(this + 1705);
        v104 = rand() % 1000;
        v53 = sub_423A80((uint64_t)(v110 * 0.8), (uint64_t)(v110 * 1.2), v104, 999);
        v110 = (double)v114;
        *(this + 1705) = v53;
        v105 = rand() % 1000;
        v54 = sub_423A80((uint64_t)(v110 * 0.9), (uint64_t)(v110 * 1.1), v105, 999);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          *(this + 1705),
          *(this + 1705),
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
        v55 = *this;
        v56 = sub_432E50(v113);
        (*(void (/*thiscall*/ **)(int *, int, int))(v55 + 896))(this, v56, 4);
        sub_495890(1, 0);
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 40))(this, 529) != 0
          && (uint8_t)sub_4DB0E0(196626) != 0 )
        {
          v54 = 0;
        }
        sub_4A0550(v54);
        v57 = *(this + 1708);
        if ( v57 == 1 || v57 == 2 )
        {
          v58 = *(this + 30);
          if ( v58 == 0 )
            goto LABEL_84;
          sub_4939E0(v58, 0);
          v59 = *(this + 1708);
          if ( v59 == 1 )
          {
            sub_4AECE0(*(this + 1700));
            LOBYTE(a5) = 0;
          }
          else
          {
            if ( v59 == 2 )
              sub_4AECE0(*(this + 1702));
LABEL_84:
            LOBYTE(a5) = 0;
          }
        }
LABEL_152:
        if ( LOBYTE(a4) != 0 )
        {
          *((uint8_t *)this + 6573) = 0;
          *((uint8_t *)this + 6574) = 0;
          sub_698F90((int)(this + 1640), 0, 0);
        }
LABEL_154:
        if ( LOBYTE(a5) != 0 )
        {
          v97 = *(this + 30);
          if ( v97 != 0 )
          {
            sub_4926A0(v97);
            sub_4910E0(*(this + 30));
          }
        }
LABEL_157:
        *(this + 1639) = a2;
        v98 = this + 1617;
        for ( i = 18; i != 0; --i )
        {
          if ( *v98 != 0 )
            (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*v98 + 156))(*v98, a2);
          ++v98;
        }
        LOBYTE(v9) = *((uint8_t *)this + 6681);
        if ( (uint8_t)v9 != 0 )
        {
          if ( *(this + 1639) == 4 && *(this + 1708) == 2 )
          {
            if ( *((uint8_t *)this + 6682) == 0 )
            {
              *(this + 1671) = 0;
              *(this + 1672) = -1;
              *((uint8_t *)this + 6682) = 1;
            }
            v118 = (double)*(this + 1671) * 100.0;
            if ( v118 / (double)(*(int (/*thiscall*/ **)(int *))(*this + 740))(this) > 15.0 && *(this + 1672) == -1 )
            {
              v100 = *(this + 30);
              if ( *(uint32_t *)(v100 + 212) != 0 )
                v101 = sub_4910A0();
              else
                v101 = *(uint32_t *)(v100 + 32);
              v102 = sub_699000((int)(this + 16)) - v101;
              *(this + 1672) = sub_491C10(*(this + 30)) + v102;
            }
          }
          v9 = *(this + 1639);
          if ( v9 != 4 && v9 != 9 )
          {
            LOBYTE(v9) = *((uint8_t *)this + 6682);
            if ( (uint8_t)v9 != 0 )
            {
              *(this + 1671) = 0;
              *(this + 1672) = -1;
              *((uint8_t *)this + 6682) = 0;
            }
          }
        }
        break;
      case 5:
        sub_53FC90(*(this + 1574));
        if ( (unsigned int)*(this + 1715) < 0x10 )
          v60 = this + 1710;
        else
          v60 = (uint32_t *)*(this + 1710);
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, v60, -1, 0, 0);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 216))(this, 0);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);
        v61 = *(this + 30);
        LOBYTE(a5) = 0;
        if ( v61 != 0 )
          sub_4939E0(v61, 1);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 40))(this, 529) != 0
          && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1020))(this) == 0 )
        {
          if ( *(uint32_t *)(dword_8F7A24 + 244) == 2 )
          {
            if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 688))(this) + 20) != 0
              && *(this + 81) <= 0
              && ((*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 4 || byte_9B9324 == 1) )
            {
              (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1545));
              if ( **(uint32_t **)(a3 + 4) == 4 )
                (*(void (/*thiscall*/ **)(int *, int))(*this + 144))(this, 4);
              else
                (*(void (/*thiscall*/ **)(int *))(*this + 152))(this);
              v107 = (float)(200 * ((*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 ? -1 : 1));
              sub_494F20(0, v107);
              sub_494F20(2, 400.0);
              byte_9B9324 = 0;
            }
          }
          else
          {
            sub_494F20(2, 0.0);
            sub_495890(0, 0);
          }
        }
        goto LABEL_152;
      case 6:
        if ( v112 != 6 )
          sub_495470(0);
        v62 = *this;
        *(this + 1723) = **(uint32_t **)(a3 + 4);
        v63 = *(this + 1547);
        *((uint8_t *)this + 6988) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4) != 0;
        (*(void (/*thiscall*/ **)(int *, int))(v62 + 196))(this, v63);
        v64 = *(this + 1723);
        if ( v64 == 0 )
        {
          v65 = *this;
          *(this + 1719) = 143;
          *(this + 1720) = 119;
          *(this + 1721) = 114;
          *(this + 1722) = 95;
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v65 + 876))(
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
            this,
            1,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);
          (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
          sub_495890(2, 0);
          *((uint8_t *)this + 6996) = 0;
          goto LABEL_152;
        }
        if ( v64 == 1 )
        {
          v66 = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8);
          v67 = *this;
          if ( *((uint8_t *)this + 6988) != 0 )
          {
            (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v67 + 212))(this, "JUMP_START", -1, 0, 0);
            if ( (unsigned int)*(this + 1746) < 0x10 )
              v68 = this + 1741;
            else
              v68 = (uint32_t *)*(this + 1741);
            (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, v68, -1, 0, 0);
            v69 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 672))(this, 3, 100);
            v70 = sub_4B0D20(v69);
            v119 = sub_495430(v66, v70);
            sub_494F20(2, v119);
            (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t))(*this + 876))(this, 0, 286, 286, 0, 0);
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
              this,
              1,
              0,
              0,
              0,
              0,
              0);
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);
            v71 = *this;
            v72 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);
            v73 = sub_432E50(v72);
            (*(void (/*thiscall*/ **)(int *, int))(v71 + 896))(this, v73);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1547));
            sub_4939E0(*(this + 30), 1);
            v74 = *(this + 1718) - 1;
            if ( *(this + 1717) > v74 )
              v74 = *(this + 1717);
            sub_4AECE0(v74);
          }
          else
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t))(v67 + 876))(
              this,
              0,
              *(this + 1719),
              *(this + 1720),
              1,
              0,
              0);
            (*(void (/*thiscall*/ **)(int *, int, int, int, int, uint32_t, uint32_t))(*this + 876))(
              this,
              1,
              *(this + 1721) / 2,
              *(this + 1722) / 2,
              1,
              0,
              0);
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);
            if ( v66 != 0 )
            {
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                this,
                "JUMP_START",
                -1,
                0,
                0);
              if ( (unsigned int)*(this + 1732) < 0x10 )
                v75 = this + 1727;
              else
                v75 = (uint32_t *)*(this + 1727);
              (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t))(*this + 212))(this, v75, -1, 0);
              v76 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
              v77 = sub_495580(v76);
              v78 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 672))(this, 3, v77);
              v79 = sub_4B0D20(v78);
              v120 = sub_495430(v66, v79);
              sub_494F20(2, v120);
              sub_4939E0(*(this + 30), 0);
              sub_4AECE0(*(this + 1716));
            }
            else
            {
              sub_4939E0(*(this + 30), 0);
              if ( *(float *)(*(this + 28) + 24) <= 0.0 )
              {
                v80 = *(this + 1718);
                v81 = *(this + 1717);
              }
              else
              {
                v80 = *(this + 1717);
                v81 = *(this + 1716);
              }
              v82 = v80 - 1;
              if ( v81 > v82 )
                v82 = v81;
              sub_4AECE0(v82);
            }
            LOBYTE(a4) = 0;
          }
          LOBYTE(a5) = 0;
          if ( *((uint8_t *)this + 6988) != 0 )
            sub_495890(1, 0);
          else
            sub_495890(2, 0);
          if ( v66 > 0 )
          {
            *(this + 1724) = 0;
            *(this + 1725) = 1;
          }
          goto LABEL_152;
        }
        if ( v64 != 2 )
          goto LABEL_152;
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "JUMP_END", -1, 0, 0);
        if ( (unsigned int)*(this + 1739) < 0x10 )
          v83 = this + 1734;
        else
          v83 = (uint32_t *)*(this + 1734);
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, v83, -1, 0, 0);
        if ( *(this + 29) != 0 )
        {
          v84 = dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 1)];
          v85 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0;
          *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v84 + 28))(v84) + 84) = v85;
          v86 = *(uint32_t *)v84;
          v87 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
          v88 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v87);
          v89 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v88);
          (*(void (/*thiscall*/ **)(int, int))(v86 + 40))(v84, v89);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v84 + 12))(v84, 0);
          (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v84 + 92))(v84, v108);
          v90 = (void *)*(this + 29);
          v115 = 1;
          sub_4600B0(v90, 2, 0, (int)v108);
          v115 = -1;
          sub_5E5260(v108);
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
        sub_495890(2, 0);
        sub_4939E0(*(this + 30), 0);
        sub_4AECE0(*(this + 1718));
        goto LABEL_157;
      case 7:
        if ( (unsigned int)*(this + 1756) < 0x10 )
          v91 = this + 1751;
        else
          v91 = (uint32_t *)*(this + 1751);
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, v91, -1, 0, 0);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1548));
        (*(void (/*thiscall*/ **)(int *, int *))(*this + 344))(this, this + 1579);
        (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, 1, 3, 1000, 1000);
        ++*(this + 1724);
        goto LABEL_154;
      case 8:
        if ( (unsigned int)*(this + 1767) < 0x10 )
          v92 = this + 1762;
        else
          v92 = (uint32_t *)*(this + 1762);
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, v92, -1, 0, 0);
        sub_41A590(**(uint32_t **)(a3 + 4));
        v93 = sub_41A5E0(this + 1757);
        if ( sub_4B0BC0(this + 1575) > v93 )
        {
          v94 = sub_41A5E0(this + 1757);
          (*(void (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 1576) + 152 * v94);
        }
        v95 = sub_41A5E0(this + 1757);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1550) + 4 * v95));
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);
        sub_494F20(2, 0.0);
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
        sub_495890(2, 0);
        goto LABEL_152;
      case 9:
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1543));
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
        v96 = *(this + 30);
        if ( v96 != 0 )
        {
          sub_4926A0(v96);
          sub_4939E0(*(this + 30), 1);
        }
        LOBYTE(a5) = 0;
        sub_495890(2, 0);
        sub_494F20(2, 0.0);
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, 16) != 0 )
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
            this,
            "CONDITION_STUN",
            -1,
            0,
            0);
        goto LABEL_152;
      default:
        goto LABEL_152;
    }
  }
  return v9;
}


// ------------------------------------------------------------
// 0x58FC30 IRDActiveObject__vmt14C —— IRDActiveObject__vmt14C 行走动画（505 行）：G_WALK_FLOOR_LOOP/WALK_SOIL_LOOP/WALK_STONE_LOOP 按地面材质分支
// ------------------------------------------------------------
void /*thiscall*/ sub_58FC30(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // eax
  int v4; // ecx
  int v5; // eax
  bool v6; // zf
  int v7; // eax
  int v8; // eax
  uint32_t *v9; // edi
  int i; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // edi
  bool v21; // bl
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  void *v26; // ecx
  int v27; // ecx
  int v28; // eax
  uint32_t *v29; // ecx
  int v30; // eax
  double v31; // st7
  int v32; // ecx
  uint32_t *v33; // ecx
  int v34; // eax
  int v35; // ecx
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // eax
  uint32_t *v41; // ecx
  int v42; // ecx
  int v43; // eax
  int v44; // eax
  int v45; // eax
  float v46; // [esp+44h] [ebp-40h]
  void *v47[4]; // [esp+54h] [ebp-30h] BYREF
  void *v48; // [esp+64h] [ebp-20h] BYREF
  int v49; // [esp+68h] [ebp-1Ch]
  int v50; // [esp+6Ch] [ebp-18h]
  int v51; // [esp+70h] [ebp-14h]
  int v52; // [esp+74h] [ebp-10h] BYREF
  int v53; // [esp+80h] [ebp-4h]

  sub_4E5410();
  if ( *(this + 40) == -1 )
  {
    if ( *(this + 1540) != 0 )
    {
      v2 = sub_4924C0(0);
      *(this + 40) = sub_4918E0(v2, 2);
    }
    else
    {
      if ( *(this + 78) < 0x10u )
        v3 = this + 73;
      else
        v3 = (uint32_t *)*(this + 73);
      off_77F3FC(aStay, v3);
      *(this + 40) = 0;
    }
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 0 )
    goto LABEL_25;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0 )
    goto LABEL_25;
  v4 = *(this + 1639);
  if ( v4 == 4 )
    goto LABEL_25;
  v5 = *(this + 154);
  if ( v5 == 4 || v4 == 5 || v5 == 5 || v4 == 9 || v5 == 9 )
    goto LABEL_25;
  v49 = 0;
  v50 = 0;
  v51 = 0;
  v6 = *(this + 1545) == 0;
  v53 = 0;
  if ( v6 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 529) != 0 )
    {
      v52 = 2;
    }
    else
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 273) == 0 )
      {
LABEL_23:
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 5, &v48, 2, 0);
        goto LABEL_24;
      }
      v52 = 0;
    }
    sub_431230((int)&v48, &v52);
    goto LABEL_23;
  }
  v52 = 4;
  sub_431230((int)&v48, &v52);
  v52 = 0;
  sub_431230((int)&v48, &v52);
  v52 = 1;
  sub_431230((int)&v48, &v52);
  sub_431230((int)&v48, &dword_72D3FC);
  sub_431230((int)&v48, &dword_72D400);
  (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 4, &v48, 2, 0);
LABEL_24:
  v53 = -1;
  sub_5E5260(&v48);
LABEL_25:
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);
  sub_495920(this);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 960))(this);
  if ( *(this + 1650) != -1 && sub_699000((int)(this + 2)) > *(this + 1650) + 1000 )
  {
    v7 = sub_41A5E0((unsigned int)(this + 1533));
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 728))(this, v7, 1, 0);
  }
  if ( *(this + 1651) != -1 && sub_699000((int)(this + 2)) > *(this + 1651) + 1000 )
  {
    v8 = sub_41A5E0((unsigned int)this + 6146);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 744))(this, v8, 1);
  }
  v9 = this + 1557;
  for ( i = 17; i != 0; --i )
  {
    if ( *v9 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)*v9 + 24))() != 0 )
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v9 + 44))(*v9);
    ++v9;
  }
  sub_53FF00(*(this + 1574));
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 676))(this, 2);
  if ( *(this + 1661) != 0 )
  {
    v11 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 976))(this, *(this + 1661));
    if ( v11 != *(this + 1663) )
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 980))(this, v11);
  }
  if ( *(this + 1662) != 0 )
  {
    v12 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 976))(this, *(this + 1662));
    if ( v12 != *(this + 1664) )
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 984))(this, v12);
  }
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 972))(this);
  v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this);
  v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 188))(this);
  switch ( *(this + 1639) )
  {
    case 0:
      if ( *(this + 50) == 0 )
      {
        if ( v13 == 4 && v14 == 4 )
        {
          if ( *((uint8_t *)this + 6752) == 0 )
          {
            v15 = *this;
            *((uint8_t *)this + 6752) = 1;
            (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, int))(v15 + 888))(this, 1, 0, 1000, 1000);
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(this + 1540));
            v16 = *(this + 30);
            if ( v16 != 0 )
              sub_4926A0(v16);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 1);
          }
        }
        else
        {
          if ( *((uint8_t *)this + 6752) != 0 )
          {
            v17 = *this;
            *((uint8_t *)this + 6752) = 0;
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(v17 + 888))(this, 1, 1, 1000, 1000);
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(this + 1541));
            v18 = *(this + 30);
            if ( v18 != 0 )
              sub_4926A0(v18);
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 273) != 0 )
            {
              if ( dword_9A012C != 0 )
              {
                (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                  this,
                  "G_WALK_FLOOR_LOOP",
                  1,
                  0,
                  0);
              }
              else
              {
                v19 = **(uint32_t **)(*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 80))(this) + 132) + 108);
                if ( v19 < 11 || v19 > 26 )
                  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                    this,
                    "WALK_SOIL_LOOP",
                    1,
                    0,
                    0);
                else
                  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                    this,
                    "WALK_STONE_LOOP",
                    1,
                    0,
                    0);
              }
            }
          }
          if ( *(this + 1772) == 7 && *(this + 29) != 0 )
          {
            v52 = (int)(this + 1779);
            if ( (uint8_t)sub_41C6E0(this + 1779) != 0 )
            {
              v20 = dword_8F8270[(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 924))(this, 2)];
              v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0;
              *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 28))(v20) + 84) = v21;
              v22 = *(uint32_t *)v20;
              v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
              v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v23);
              v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v24);
              (*(void (/*thiscall*/ **)(int, int))(v22 + 40))(v20, v25);
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v20 + 12))(v20, 0);
              (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)v20 + 92))(v20, v47);
              v26 = (void *)*(this + 29);
              v53 = 1;
              sub_4600B0(v26, 2, 0, (int)v47);
              v27 = v52;
              *(uint8_t *)(v52 + 13) = 0;
              *(uint8_t *)(v27 + 14) = 0;
              sub_698F90(v27, 200, 0);
              sub_5E5260(v47);
            }
          }
        }
      }
      return;
    case 1:
    case 8:
      v45 = *(this + 30);
      if ( v45 != 0 && *(uint8_t *)(v45 + 170) != 0 )
        goto LABEL_156;
      return;
    case 3:
      if ( sub_699000((int)(this + 1640)) >= *(this + 1690) )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 3) == 0 )
          goto LABEL_145;
        (*(void (/*stdcall*/ **)(int, uint32_t, int, uint32_t))(*this + 560))(9, 0, 2, 0);
      }
      return;
    case 4:
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) > *(this + 1706) )
        *(this + 1706) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v28 = *(this + 1708);
      if ( v28 != 0 )
      {
        if ( v28 == 1 )
        {
          v33 = (uint32_t *)*(this + 30);
          if ( v33 != nullptr && *(float *)(*(this + 28) + 24) <= 0.0 )
          {
            v34 = *(this + 1700);
            if ( v33[37] == v34 && v34 != *(this + 1701) )
              sub_4AECE0(v33, v34 + 1);
          }
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
          {
            v35 = *(this + 28);
            if ( *(float *)(v35 + 24) < 0.0 && *(uint32_t *)(v35 + 192) == 4 && *(this + 50) == 0 )
            {
              if ( *(this + 1672) == -1
                || sub_699000((int)(this + 16)) < *(this + 1672)
                || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) != 0 )
              {
                v49 = 0;
                v50 = 0;
                v51 = 0;
                v53 = 3;
                v52 = 4;
                sub_431230((int)&v48, &v52);
                v52 = 2;
                sub_431230((int)&v48, &v52);
                v52 = 0;
                sub_431230((int)&v48, &v52);
                v52 = 0;
                sub_431230((int)&v48, &v52);
                v52 = 0;
                sub_431230((int)&v48, &v52);
                (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 4, &v48, 2, 0);
                sub_5E5260(&v48);
                return;
              }
              goto LABEL_115;
            }
          }
        }
        else if ( v28 == 2 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) != 0 )
          {
            v36 = *(this + 154);
            if ( v36 != 5 && v36 != 4 && *(this + 50) == 0 )
            {
              v49 = 0;
              v50 = 0;
              v51 = 0;
              v53 = 4;
              v52 = 1;
              sub_431230((int)&v48, &v52);
              (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 5, &v48, 2, 0);
              goto LABEL_151;
            }
          }
          v37 = *(this + 30);
          if ( v37 != 0 && *(uint8_t *)(v37 + 170) != 0 )
            goto LABEL_115;
          if ( *(this + 1672) != -1 && sub_699000((int)(this + 16)) >= *(this + 1672) )
            goto LABEL_115;
        }
      }
      else
      {
        v29 = (uint32_t *)*(this + 30);
        if ( v29 != nullptr && *(float *)(*(this + 28) + 24) <= 0.0 )
        {
          v30 = *(this + 1698);
          if ( v29[37] == v30 && v30 != *(this + 1699) )
            sub_4AECE0(v29, v30 + 1);
        }
        if ( *(uint32_t *)(*(this + 28) + 184) == 4
          && *(this + 1707) != -1
          && *(this + 1707) != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) )
        {
          v52 = *(this + 1705) / -5;
          v31 = (double)v52;
          *(this + 1705) = v52;
          v46 = v31;
          sub_494F20(0, v46);
          *(this + 1707) = -1;
        }
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        {
          v32 = *(this + 28);
          if ( *(float *)(v32 + 24) < 0.0 && *(uint32_t *)(v32 + 192) == 4 && *(this + 50) == 0 )
          {
            if ( *(this + 1672) == -1
              || sub_699000((int)(this + 16)) < *(this + 1672)
              || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) != 0 )
            {
              v49 = 0;
              v50 = 0;
              v51 = 0;
              v53 = 2;
              v52 = 4;
              sub_431230((int)&v48, &v52);
              v52 = 1;
              sub_431230((int)&v48, &v52);
              v52 = 0;
              sub_431230((int)&v48, &v52);
              sub_431230((int)&v48, this + 1705);
              v52 = *(this + 1706) / 5;
              sub_431230((int)&v48, &v52);
              (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 4, &v48, 2, 0);
              goto LABEL_151;
            }
LABEL_115:
            sub_58E660(this);
            return;
          }
        }
      }
      return;
    case 5:
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 529) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 1020))(this) == 0
        && *(uint32_t *)(dword_8F7A24 + 244) != 2 )
      {
        sub_494F20(2, 0.0);
      }
      return;
    case 6:
      v38 = *(this + 1723);
      if ( v38 != 0 )
      {
        if ( v38 == 1 )
        {
          if ( *((uint8_t *)this + 6988) == 0
            && v13 != 4
            && v13 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this)
            && *(this + 1724) == 0
            && *((uint8_t *)this + 6996) == 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 148))(this, v13);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 144))(this, v13);
          }
          v41 = (uint32_t *)*(this + 30);
          if ( v41 != nullptr
            && v41 == (uint32_t *)*(this + 1547)
            && *(float *)(*(this + 28) + 24) <= 0.0
            && v41[37] < *(this + 1717) )
          {
            sub_4AECE0(v41, *(this + 1717));
          }
          v42 = *(this + 28);
          if ( *(float *)(v42 + 24) < 0.0 && *(uint32_t *)(v42 + 192) == 4 )
          {
            v49 = 0;
            v50 = 0;
            v51 = 0;
            v53 = 6;
            v52 = 2;
            goto LABEL_149;
          }
        }
        else if ( v38 == 2 )
        {
          if ( *((uint8_t *)this + 6988) != 0 )
          {
            if ( sub_699000((int)(this + 1640)) >= *(this + 1748) )
LABEL_156:
              (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(0, 0, 0, 0);
          }
          else
          {
            v43 = *(this + 30);
            if ( v43 != 0 && *(uint8_t *)(v43 + 170) != 0 )
LABEL_145:
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
          }
        }
      }
      else
      {
        v39 = *(this + 30);
        if ( v39 != 0 && *(uint32_t *)(v39 + 148) >= *(this + 1716) )
        {
          v49 = 0;
          v50 = 0;
          v51 = 0;
          v53 = 5;
          v52 = 1;
          sub_431230((int)&v48, &v52);
          v52 = 0;
          sub_431230((int)&v48, &v52);
          v40 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
          v52 = sub_58E710(v40);
          sub_431230((int)&v48, &v52);
          goto LABEL_150;
        }
      }
      return;
    case 7:
      v44 = *(this + 30);
      if ( v44 != 0 && *(uint8_t *)(v44 + 170) != 0 )
      {
        v49 = 0;
        v50 = 0;
        v51 = 0;
        v53 = 7;
        v52 = 1;
LABEL_149:
        sub_431230((int)&v48, &v52);
        v52 = *((uint8_t *)this + 6988) != 0;
        sub_431230((int)&v48, &v52);
        v52 = 0;
        sub_431230((int)&v48, &v52);
LABEL_150:
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 6, &v48, 0, 0);
        goto LABEL_151;
      }
      if ( *(uint32_t *)(*(this + 28) + 192) == 4 )
      {
        v49 = 0;
        v50 = 0;
        v51 = 0;
        v53 = 8;
        v52 = 2;
        sub_431230((int)&v48, &v52);
        v52 = *((uint8_t *)this + 6988) != 0;
        sub_431230((int)&v48, &v52);
        v52 = 0;
        sub_431230((int)&v48, &v52);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 6, &v48, 0, 0);
LABEL_151:
        sub_5E5260(&v48);
      }
      return;
    default:
      return;
  }
}

