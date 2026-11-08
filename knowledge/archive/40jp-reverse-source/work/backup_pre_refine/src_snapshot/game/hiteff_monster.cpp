// ============================================================
// 【40JP逆向源代码工程】game/hiteff_monster.cpp
// 模块: 命中特效/怪物状态机
// 来源: work/dump_misca.txt  区块: 0x4E0000-0x4F0000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
//        语义与 IDA Hex-Rays 逐字对应; 逐行精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 165
// ------------------------------------------------------------
// ★ 本文件是本工程"打击感/hit stop"链路的**主战场** —— 研究 20 定案锚点最密集的区块：
//   0x4E5DC0 表现壳（hit stop 施加点，研究 §3 全文定案）
//   0x4E88A0 HITEFF 通用命中特效生成器 vt+640（研究 §5.2 全文定案）
//   0x4E4710 攻方表现载荷（★ 双向卡肉，研究 §8 全文定案）
//   0x4E6770 伤害流水线 vt+628（研究 P14 九步公式）
//   0x4E7A80 受击反应 setState vt+560（研究 §1.2/§15 三层状态只升不降仲裁）
//   0x4E85E0 CRITHIT / 0x4E8770 UNIONHIT（研究 §5.3/§5.4）
//   0x4E5B50 暴击/有效命中判定（研究 §5.1）、0x4E9760 格挡特效 vt+644（研究 §3 格挡分支）
//   0x4E82B0 本地扫掠 vt+476（研究 §1.2/§11 第 11 轮）
//   0x4E4DE0 位置化动作 / 0x4E4F20 动作数据包（本工程会话 3 定案）
//   0x4E54D0 AABB 重叠 / 0x4E5560 动画盒重叠（已 L1 精修，见 src/cnrd/IRDCollisionObject.cpp）
//   0x4E62B0 攻击盒 vs 受击盒碰撞（研究 P29 盒模型，会话 3 交叉引用）
//   0x4E4430 HP 受击处理器含 Boss 终局（研究 P35 第 31 轮）
//   0x4E7160/0x4E73B0 出生/复活重置（研究 P35）
// ------------------------------------------------------------
// 交叉引用：已被 L1 逐行精修的重复函数（以 cnrd/ 版为准，此处保留 L2 转写体）：
//   0x4E5410/0x4E54D0/0x4E5560/0x4E57E0/0x4E5920 → src/cnrd/IRDCollisionObject.cpp:330/27/50/125/167
//   0x4E7040/0x4E7440/0x4E7480/0x4E8080 → src/cnrd/IRDCollisionObject.cpp:269/213/226/249
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 A】怪物状态机 / 行为定义族（0x4E0000 - 0x4E4430）
//   怪物大状态 tick、行为表驱动、无敌/受击盒门、动作队列。
//   研究依据：P35 第 31 轮（无敌开关 = this+641 受击盒使能，setter sub_4A2D70
//   向附属物广播 vt+604）；三层状态（this+200 主状态 / +616 反应态 +636 优先级 /
//   +6556 大状态）。
// ============================================================

// ------------------------------------------------------------
// 0x4E0000 sub_4E0000 —— 大状态行为表项应用（按 a2 索引取 32 字节记录 + 附加盒）
// this+1550/1551 = 行为 vector（4 字节 id 数组）；this+1905/1906 = 32 字节属性数组。
// 目标索引越界时先 sub_4DFF40 扩容（this+1904 为容量字段）。
// 属性记录经 vt+1216(表项, 行为id) 应用；若 this+1625 非空（有技能对象），
// 逐条 vt+248 取技能属性表（124 字节步距）→ 每项再 vt+1216 应用。
// ------------------------------------------------------------
void /*thiscall*/ sub_4E0000(uint32_t *this, unsigned int a2)
{
  int v3; // ecx
  int v4; // edx
  int v5; // edx
  unsigned int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ebx
  uint32_t *v10; // edx
  int v11; // ecx
  int v12; // [esp+4h] [ebp-10h]
  uint32_t *v13; // [esp+Ch] [ebp-8h]
  int v14; // [esp+10h] [ebp-4h]

  v3 = *(this + 1550);
  if ( v3 != 0 && (*(this + 1551) - v3) >> 2 > a2 )
  {
    v4 = *(this + 1905);
    if ( v4 == 0 || (*(this + 1906) - v4) >> 5 <= a2 )
    {
      v5 = *(this + 1550);
      if ( v5 != 0 )
        v6 = (*(this + 1551) - v5) >> 2;
      else
        v6 = 0;
      sub_4DFF40(this + 1904, v6);
    }
    (*(void (/*thiscall*/ **)(uint32_t *, unsigned int, uint32_t))(*this + 1216))(
      this,
      32 * a2 + *(this + 1905),
      *(uint32_t *)(4 * a2 + *(this + 1550)));
    v7 = *(this + 1625);
    if ( v7 != 0 )
    {
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 248))(v7);
      v9 = *(uint32_t *)(v8 + 4);
      v12 = v8;
      v14 = v9;
      if ( v9 != *(uint32_t *)(v8 + 8) )
      {
        v10 = (uint32_t *)(v9 + 44);
        v13 = (uint32_t *)(v9 + 44);
        do
        {
          v11 = *v10;
          if ( *v10 != 0 && (v10[1] - v11) >> 2 > a2 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, unsigned int, uint32_t))(*this + 1216))(
              this,
              32 * a2 + *(this + 1905),
              *(uint32_t *)(v11 + 4 * a2));
            v9 = v14;
            v10 = v13;
          }
          v9 += 124;
          v10 += 31;
          v14 = v9;
          v13 = v10;
        }
        while ( v9 != *(uint32_t *)(v12 + 8) );
      }
    }
  }
}



// ------------------------------------------------------------
// 0x4E0120 sub_4E0120
// ------------------------------------------------------------
void /*thiscall*/ sub_4E0120(uint32_t *this)
{
  int v2; // eax
  double v3; // st7
  int v4; // edi
  bool v5; // cc
  uint32_t *v6; // edi
  unsigned int v7; // eax
  uint32_t *v8; // eax
  unsigned int v9; // esi
  uint32_t *v10; // ecx
  uint32_t *v11; // edx
  int v12; // [esp-8h] [ebp-30h]
  void *v13[4]; // [esp+8h] [ebp-20h] BYREF
  int v14; // [esp+18h] [ebp-10h] BYREF
  int v15; // [esp+24h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 0
    || *(this + 1813) != 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 0
    || *(this + 1787) == 24
    || (v2 = *(this + 1812)) == 0
    || (v3 = (double)(*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, v2, 0),
        (double)(v14 = sub_4D8FE0(this)) * 0.5 >= v3) )
  {
    switch ( *(this + 1787) )
    {
      case 2:
        if ( *(this + 1813) != 0 )
        {
          if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 188))(this) == 2
            && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) <= *(this + 1918)
            || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 188))(this) == 3
            && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) >= *(this + 1918) )
          {
            memset(&v13[1], 0, 12);
            v15 = 0;
            v14 = 0;
            sub_431230((int)v13, &v14);
            (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, v13, 0, 0);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 1);
            v15 = -1;
            sub_5E5260(v13);
          }
        }
        else
        {
          (*(void (/*stdcall*/ **)(int))(*this + 1104))(1);
        }
        break;
      case 3:
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this) == 0
          && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) <= *(this + 1919)
          || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this) == 1
          && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) >= *(this + 1919) )
        {
          goto LABEL_14;
        }
        break;
      case 6:
        if ( sub_699000((int)(this + 1910)) - *(this + 1926) > 5000 )
        {
          if ( *(this + 1813) == 0 )
            goto LABEL_17;
          goto LABEL_48;
        }
        break;
      case 9:
      case 0xA:
        v5 = sub_699000((int)(this + 1910)) - *(this + 1926) <= 10000;
        goto LABEL_16;
      case 0xB:
        if ( *(this + 1813) != 0 )
        {
          if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this) == 0
            && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) <= *(this + 1919)
            || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this) == 1
            && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) >= *(this + 1919) )
          {
            if ( sub_4DAB60(this, 10) )
            {
              (*(void (/*stdcall*/ **)(int))(*this + 1104))(9);
            }
            else if ( sub_4DAB60(this, 11) )
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 10);
            }
          }
        }
        else
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
        }
        break;
      case 0xC:
        v4 = *(this + 1813);
        if ( v4 != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1244))(this, *(this + 1813)) != 0 )
          {
            if ( sub_4DAB60(this, 10) )
            {
              *(this + 1919) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 120))(v4);
              *(this + 1918) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 124))(v4);
            }
            else if ( sub_4DAB60(this, 11) )
            {
LABEL_14:
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 1);
            }
          }
        }
        else
        {
          v5 = sub_699000((int)(this + 1910)) - *(this + 1926) <= 5000;
LABEL_16:
          if ( !v5 )
          {
LABEL_17:
            v12 = 13;
LABEL_18:
            (*(void (/*stdcall*/ **)(int))(*this + 1104))(v12);
          }
        }
        break;
      case 0x15:
        if ( sub_699000((int)(this + 1910)) - *(this + 1926) <= 500 )
          break;
        v12 = 4;
        if ( *(this + 1813) != 0 )
          goto LABEL_18;
LABEL_48:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
        break;
      default:
        break;
    }
    if ( *(this + 1939) != 0 && *(this + 1813) != 0 )
    {
      v6 = this + 1934;
      v7 = *(this + 1940);
      if ( *(this + 1943) == 3 )
      {
        if ( v7 < 0x10 )
          sub_432EA0(this + 1935, -1, 0, 0);
        else
          sub_432EA0((void *)*(this + 1935), -1, 0, 0);
      }
      else
      {
        if ( v7 < 0x10 )
          v8 = this + 1935;
        else
          v8 = (uint32_t *)*(this + 1935);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, v8, -1, 0, 0);
      }
      v9 = *(this + 1940);
      v10 = v6 + 1;
      if ( v9 < 0x10 )
        v11 = v6 + 1;
      else
        v11 = (uint32_t *)*v10;
      if ( v9 >= 0x10 )
        v10 = (uint32_t *)*v10;
      sub_406D00(v6, &v14, (int)v10, (unsigned int)v11 + v6[5]);
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 24);
  }
}


// ------------------------------------------------------------
// 0x4E0560 sub_4E0560
// ------------------------------------------------------------
void /*thiscall*/ sub_4E0560(uint32_t *this)
{
  int v2; // ecx
  int v3; // ebx
  int v4; // edi
  unsigned int v5; // edi
  int i; // ebx
  int v7; // ecx
  void *v8[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v9[4]; // [esp+14h] [ebp-10h] BYREF

  v2 = *(this + 1550);
  if ( v2 != 0
    && (*(this + 1551) - v2) >> 2 != 0
    && *(this + 1639) == 0
    && sub_699000((int)(this + 1910)) >= 3000
    && sub_699000((int)(this + 1910)) >= *(this + 1817) )
  {
    sub_432FA0();
    v3 = (uint64_t)((double)(int)*(this + 1900) * 0.2);
    v4 = *(this + 1900) + rand() % v3 - v3 / 2;
    *(this + 1817) = v4 + sub_699000((int)(this + 1910));
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      v5 = 0;
      v9[0] = 0;
      for ( i = 0; ; i += 32 )
      {
        v7 = *(this + 1905);
        if ( v7 == 0 || v5 >= (*(this + 1906) - v7) >> 5 )
          break;
        if ( *(uint8_t *)(i + v7) != 0 && sub_4DB810(this, v5) )
        {
          v9[0] = v5;
          memset(&v8[1], 0, 12);
          v9[3] = 0;
          sub_431230((int)v8, v9);
          (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, v8, 0, 0);
          sub_5E5260(v8);
          return;
        }
        ++v5;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x4E06D0 sub_4E06D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4E06D0(uint32_t *this)
{
  int v1; // eax
  int v2; // eax
  int v3; // edi
  int i; // esi
  int v5; // eax
  int v6; // eax
  int j; // esi
  int v8; // eax
  int v9; // eax
  unsigned int k; // edi
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // edx
  uint32_t *v15; // esi
  void **v16; // eax
  uint32_t *v17; // eax
  int *v18; // ecx
  int *v19; // edi
  int v20; // esi
  int v21; // ebx
  int v22; // ebx
  int **v23; // eax
  int *n; // eax
  int *m; // eax
  int v26; // edi
  uint32_t *v27; // esi
  int v28; // eax
  int v29; // ecx
  int v30; // ebx
  int v31; // eax
  int v32; // ebx
  int v33; // eax
  int *v34; // [esp-10h] [ebp-44h]
  int *v35; // [esp-10h] [ebp-44h]
  int v36; // [esp-10h] [ebp-44h]
  char v37[4]; // [esp+4h] [ebp-30h] BYREF
  void *Block; // [esp+8h] [ebp-2Ch]
  int v39; // [esp+Ch] [ebp-28h]
  char v40[4]; // [esp+10h] [ebp-24h] BYREF
  int v41; // [esp+14h] [ebp-20h]
  int v42; // [esp+18h] [ebp-1Ch]
  int v43; // [esp+1Ch] [ebp-18h] BYREF
  int v44; // [esp+20h] [ebp-14h]
  uint32_t *v45; // [esp+24h] [ebp-10h]
  int v46; // [esp+30h] [ebp-4h]

  v1 = *(this + 29);
  v45 = this;
  if ( v1 == 0 )
    return;
  v44 = -1;
  v42 = 0;
  v41 = 0;
  Block = (void *)sub_433AC0(v37);
  *((uint8_t *)Block + 21) = 1;
  *((uint32_t *)Block + 1) = Block;
  *(uint32_t *)Block = Block;
  *((uint32_t *)Block + 2) = Block;
  v39 = 0;
  v2 = *(uint32_t *)(dword_8F7A24 + 12);
  v46 = 0;
  if ( v2 == 4 && dword_99FEC0 != 0 )
  {
    v3 = dword_99FEC0 + 4;
  }
  else
  {
    if ( v2 != 6 || dword_99FF08 == 0 )
      goto LABEL_15;
    v3 = dword_99FF08 + 4;
  }
  if ( v3 != 0 )
  {
    for ( i = 0; i < 8; ++i )
    {
      v5 = sub_48F660(i);
      if ( v5 != 0 )
      {
        v6 = *(uint32_t *)(v5 + 196);
        if ( v6 != 0 )
        {
          v43 = v6;
          *(uint32_t *)sub_42D430(&v43) = 0;
        }
      }
    }
    goto LABEL_20;
  }
LABEL_15:
  for ( j = 16; j < 32; j += 4 )
  {
    v8 = *(uint32_t *)(j + dword_8F850C);
    if ( v8 != 0 )
    {
      v9 = *(uint32_t *)(v8 + 196);
      if ( v9 != 0 )
      {
        v43 = v9;
        *(uint32_t *)sub_42D430(&v43) = 0;
      }
    }
  }
LABEL_20:
  for ( k = 0; ; ++k )
  {
    v11 = v45[29];
    v12 = *(uint32_t *)(v11 + 120);
    v13 = v12 != 0 ? (*(uint32_t *)(v11 + 124) - v12) >> 2 : 0;
    if ( (int)k >= v13 )
      break;
    v14 = *(uint32_t *)(v11 + 120);
    if ( v14 != 0 && k < (*(uint32_t *)(v11 + 124) - v14) >> 2 )
      v15 = *(uint32_t **)(v14 + 4 * k);
    else
      v15 = nullptr;
    if ( v15 != v45 && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v15 + 40))(v15, 529) != 0 )
    {
      v43 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v15 + 1032))(v15) + 28);
      if ( v43 != 0 )
      {
        v16 = (void **)sub_4BE520(v40, &v43);
        if ( *v16 != Block )
        {
          v17 = (uint32_t *)sub_42D430(&v43);
          ++*v17;
        }
      }
    }
  }
  v18 = (int *)Block;
  v19 = *(int **)Block;
  if ( *(void **)Block == Block )
    goto LABEL_63;
  do
  {
    v20 = v19[3];
    if ( (uint8_t)sub_45E680(v20) != 0 )
      v21 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*v45 + 8))(v45, v20, 0);
    else
      v21 = 640;
    if ( v20 == v45[1814] )
      v21 -= 50;
    if ( v20 == v45[1813] )
      v21 -= 50;
    v22 = 100 * v19[4] + v21;
    if ( v44 == -1 || v22 < v42 )
    {
      v44 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 52))(v20);
      v42 = v22;
      v41 = v20;
    }
    if ( *((uint8_t *)v19 + 21) == 0 )
    {
      v23 = (int **)v19[2];
      if ( *((uint8_t *)v23 + 21) != 0 )
      {
        for ( m = (int *)v19[1]; *((uint8_t *)m + 21) == 0; m = (int *)m[1] )
        {
          if ( v19 != (int *)m[2] )
            break;
          v19 = m;
        }
        v19 = m;
      }
      else
      {
        v19 = (int *)v19[2];
        for ( n = *v23; *((uint8_t *)n + 21) == 0; n = (int *)*n )
          v19 = n;
      }
    }
  }
  while ( v19 != Block );
  v26 = v44;
  if ( v44 == -1 || v41 == 0 )
  {
    v18 = (int *)Block;
LABEL_63:
    v36 = *v18;
    v46 = -1;
    sub_41DA40(v40, v36, v18);
    j__free(Block);
    return;
  }
  v27 = v45;
  v28 = sub_699000((int)(v45 + 2));
  v29 = v27[1815];
  v27[1917] = v28 + 2000;
  if ( v29 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v29 + 52))(v29) == v26 )
  {
    v34 = *(int **)Block;
    v46 = -1;
    sub_41DA40(v40, v34, Block);
    j__free(Block);
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 6, 2);
    v30 = *(uint32_t *)dword_8F8520;
    v31 = (*(int (/*thiscall*/ **)(uint32_t *))(*v27 + 48))(v27);
    (*(void (/*thiscall*/ **)(int, int))(v30 + 36))(dword_8F8520, v31);
    v32 = *(uint32_t *)dword_8F8520;
    v33 = (*(int (/*thiscall*/ **)(uint32_t *))(*v27 + 52))(v27);
    (*(void (/*thiscall*/ **)(int, int))(v32 + 36))(dword_8F8520, v33);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v26);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    v35 = *(int **)Block;
    v46 = -1;
    sub_41DA40(v40, v35, Block);
    j__free(Block);
  }
}


// ------------------------------------------------------------
// 0x4E0A40 sub_4E0A40
// ------------------------------------------------------------
void /*thiscall*/ sub_4E0A40(uint32_t *this, int a2, int a3)
{
  unsigned int v3; // edi
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // esi
  uint32_t v13[11]; // [esp+1Ch] [ebp-2Ch] BYREF

  v3 = 0;
  v13[3] = this;
  v13[5] = 0;
  v13[4] = 0;
  v13[2] = 1;
  v13[10] = 0;
  while ( 1 )
  {
    v5 = *(this + 29);
    v6 = *(uint32_t *)(v5 + 120);
    v7 = v6 != 0 ? (*(uint32_t *)(v5 + 124) - v6) >> 2 : 0;
    if ( (int)v3 >= v7 )
      break;
    v8 = *(uint32_t *)(v5 + 120);
    if ( v8 != 0 && v3 < (*(uint32_t *)(v5 + 124) - v8) >> 2 )
      v9 = *(uint32_t *)(v8 + 4 * v3);
    else
      v9 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 40))(v9, 17) != 0 )
    {
      v10 = *(this + 29);
      v11 = *(uint32_t *)(v10 + 120);
      if ( v11 != 0 && v3 < (*(uint32_t *)(v10 + 124) - v11) >> 2 )
        v12 = *(uint32_t *)(v11 + 4 * v3);
      else
        v12 = 0;
      if ( (uint8_t)sub_4E4630(v12) != 0
        && (uint8_t)sub_4E5CA0(v12) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, v12) != 0 )
      {
        v13[0] = v12;
        v13[1] = 0;
        sub_4DFF90(v13);
      }
    }
    ++v3;
  }
}


// ------------------------------------------------------------
// 0x4E0CD0 sub_4E0CD0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E0CD0(uint32_t *this, int a2, char a3, int a4, int a5)
{
  uint32_t *v5; // ebx
  unsigned int v6; // edi
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // ecx
  int v12; // eax
  int v13; // edx
  uint32_t *v14; // ecx
  int v15; // edx
  int v16; // esi
  int v17; // ebx
  bool v18; // zf
  int v21; // [esp+10h] [ebp-8h] BYREF
  int v22; // [esp+14h] [ebp-4h]

  v5 = this;
  v6 = 0;
  v22 = 0;
  while ( 1 )
  {
    v7 = v5[29];
    v8 = *(uint32_t *)(v7 + 8);
    v9 = v8 != 0 ? (*(uint32_t *)(v7 + 12) - v8) >> 2 : 0;
    if ( (int)v6 >= v9 )
      return v22;
    v10 = *(uint32_t *)(v7 + 8);
    if ( v10 != 0 && v6 < (*(uint32_t *)(v7 + 12) - v10) >> 2 )
      v11 = *(uint32_t *)(v10 + 4 * v6);
    else
      v11 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 40))(v11, a2) != 0 )
    {
      v12 = v5[29];
      v13 = *(uint32_t *)(v12 + 8);
      if ( v13 != 0 && v6 < (*(uint32_t *)(v12 + 12) - v13) >> 2 )
        v14 = *(uint32_t **)(v13 + 4 * v6);
      else
        v14 = nullptr;
      if ( v14 != v5 )
      {
        v15 = *(uint32_t *)(v12 + 8);
        if ( v15 != 0 && v6 < (*(uint32_t *)(v12 + 12) - v15) >> 2 )
          v16 = *(uint32_t *)(v15 + 4 * v6);
        else
          v16 = 0;
        v21 = v16;
        if ( a3 == 1 )
        {
          v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 376))(v5);
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 376))(v16) == v17;
          v5 = this;
          if ( !v18 )
            goto LABEL_35;
        }
        else if ( a3 == 0 && (uint8_t)sub_4E4630(v16) == 0 )
        {
          goto LABEL_35;
        }
        if ( (uint8_t)sub_4E5CA0(v16) != 0 )
          goto LABEL_35;
        if ( a5 == -1 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v5 + 1244))(v5, v16) == 0 )
            goto LABEL_35;
        }
        else if ( (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*v5 + 8))(v5, v16, 0) > a5 )
        {
          goto LABEL_35;
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v16 + 40))(v16, 17) == 0
          || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 940))(v16) != 1
          && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 724))(v16) == 0 )
        {
          ++v22;
          if ( a4 != 0 )
            sub_428430(&v21);
        }
      }
    }
LABEL_35:
    ++v6;
  }
}



// ------------------------------------------------------------
// 0x4E0E30 sub_4E0E30
// ------------------------------------------------------------
bool /*thiscall*/ sub_4E0E30(int *this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // ebx
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // ebx
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v19; // ebx
  int v20; // eax
  int v21; // edx
  int v22; // ebx
  int v23; // ebx
  int v24; // eax
  bool v25; // zf
  signed int v26; // eax
  int v27; // eax
  bool v28; // zf
  signed int v29; // eax
  int v30; // edx
  int v31; // eax
  int v32; // edx
  int v33; // edi
  int v34; // eax
  int v36; // [esp+Ch] [ebp-28h] BYREF
  int v37; // [esp+10h] [ebp-24h] BYREF
  int v38; // [esp+14h] [ebp-20h] BYREF
  int v39; // [esp+18h] [ebp-1Ch] BYREF
  int v40; // [esp+1Ch] [ebp-18h] BYREF
  int v41; // [esp+20h] [ebp-14h] BYREF
  int v42; // [esp+24h] [ebp-10h] BYREF
  int v43; // [esp+28h] [ebp-Ch] BYREF
  int v44; // [esp+2Ch] [ebp-8h] BYREF
  int v45; // [esp+30h] [ebp-4h] BYREF

  if ( a2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2) != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 40))(v3, 17) != 0
      && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      v4 = *(this + 1787);
      if ( v4 != 12 && v4 != 7 )
      {
        v5 = *this;
        v6 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a2 + 576))(a2, 0);
        if ( (*(int (/*thiscall*/ **)(int *, int))(v5 + 8))(this, v6) >= 150 )
        {
          v7 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
          v8 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v7;
          v9 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
          srand(v9 + v8);
          if ( *(this + 1813) == 0 )
            goto LABEL_16;
          v10 = *(this + 1891);
          v37 = 0;
          v38 = 0;
          v39 = 0;
          v40 = 0;
          v43 = 0;
          v42 = 0;
          v36 = 0;
          v41 = 0;
          if ( v10 != 0 )
            sub_4DC920(this, &v36, &v37);
          if ( *(this + 1892) != 0 )
            sub_4DCAB0(this, &v38, &v39);
          if ( *(this + 1893) != 0 )
            sub_4E0A40(this, &v40, &v41);
          sub_4DCCB0(this, (int)&v43, *(this + 1813), COERCE_FLOAT(&v36));
          v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
          sub_4DCCB0(this, (int)&v42, v11, COERCE_FLOAT(&v36));
          if ( v43 <= v42 )
          {
LABEL_16:
            v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
            v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 120))(v12);
            v42 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < v13;
            if ( sub_4DAB60(this, 12) || sub_4DAB60(this, 13) )
            {
              v19 = 10 - (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
              v42 = (int)abs32(v19 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 120))(v12)) / 2;
              v43 = 1;
              if ( v42 / 2 >= 1 )
                v43 = v42 / 2;
              v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 120))(v12);
              v21 = *this;
              v44 = v20;
              v22 = (*(int (/*thiscall*/ **)(int *))(v21 + 124))(this);
              v23 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v22;
              v24 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
              srand(v24 + v23);
              v26 = rand() & 0x80000001;
              v25 = v26 == 0;
              if ( v26 < 0 )
                v25 = (((uint8_t)v26 - 1) | 0xFFFFFFFE) == -1;
              v27 = v42;
              if ( v25 )
                v27 = -v42;
              v44 += v27;
              v45 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 124))(v12);
              v29 = rand() & 0x80000001;
              v28 = v29 == 0;
              if ( v29 < 0 )
                v28 = (((uint8_t)v29 - 1) | 0xFFFFFFFE) == -1;
              if ( v28 )
                v30 = -(rand() % v43);
              else
                v30 = rand() % v43;
              v14 = v30 + v45;
            }
            else if ( sub_4DAB60(this, 14) )
            {
              v44 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 120))(v12);
              v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 124))(v12);
            }
            else
            {
              if ( !sub_4DAB60(this, 15) )
              {
LABEL_40:
                (*(void (/*thiscall*/ **)(int *, int *, int *, int, int, int, uint32_t, int))(*this + 140))(
                  this,
                  &v44,
                  &v45,
                  v44,
                  v45,
                  100,
                  0,
                  1);
                v31 = v45;
                *(this + 1919) = v44;
                v32 = *this;
                *(this + 1918) = v31;
                (*(void (/*thiscall*/ **)(int *, int))(v32 + 1104))(this, 12);
                v33 = *this;
                v34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
                return (*(uint8_t (/*thiscall*/ **)(int *, int))(v33 + 1244))(this, v34) != 0;
              }
              v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 120))(v12);
              v16 = (int)abs32(v15 - (*(int (/*thiscall*/ **)(int *))(*this + 120))(this)) / 5;
              v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 120))(v12);
              if ( v42 != 0 )
                v18 = v17 - v16;
              else
                v18 = v16 + v17;
              v44 = v18;
              v45 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 124))(v12);
              if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 124))(v12) <= 230 )
                v14 = v45 + 50;
              else
                v14 = v45 - 50;
            }
            v45 = v14;
            goto LABEL_40;
          }
        }
      }
    }
  }
  return false;
}


// ------------------------------------------------------------
// 0x4E11A0 sub_4E11A0
// ------------------------------------------------------------
void /*stdcall*/ sub_4E11A0(int a1)
{
  unsigned int v1; // edi
  uint32_t *v2; // ebx
  unsigned int v3; // edx
  uint32_t *v4; // ecx
  char v5; // al
  int v6; // ecx
  int v7; // ecx
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v19; // ebx
  int v20; // eax
  uint8_t v21[4]; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-20h]
  int v23; // [esp+10h] [ebp-1Ch]
  int v24; // [esp+14h] [ebp-18h]
  unsigned int v25; // [esp+18h] [ebp-14h]
  int v26; // [esp+1Ch] [ebp-10h]
  int v27; // [esp+28h] [ebp-4h]

  v1 = 0;
  Block = nullptr;
  v23 = 0;
  v24 = 0;
  v27 = 0;
  sub_4E0CD0(529, 1, v21, -1);
  v2 = Block;
  if ( Block != nullptr )
  {
    v3 = (v23 - (int)Block) >> 2;
    v25 = v3;
    if ( v3 != 0 )
    {
      v26 = 0;
      switch ( dword_99FB8C )
      {
        case 0:
          v26 = 1;
          break;
        case 1:
          v26 = 2;
          break;
        case 2:
          v26 = 3;
          break;
        case 3:
          v26 = 4;
          break;
        default:
          goto LABEL_8;
      }
      while ( 1 )
      {
LABEL_8:
        if ( v1 >= v3 )
          goto LABEL_17;
        v4 = (uint32_t *)v2[v1];
        if ( v4[1787] != 12 )
          break;
LABEL_16:
        ++v1;
      }
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 308))(v4);
      v6 = v2[v1];
      if ( v5 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 1136))(v6, a1);
      }
      else
      {
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 304))(v6) == 0 )
        {
LABEL_15:
          v3 = v25;
          goto LABEL_16;
        }
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
        v7 = v2[v1];
        v8 = *(uint32_t *)dword_8F8520;
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 48))(v7);
        (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);
        v10 = *(uint32_t *)dword_8F8520;
        v11 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v1) + 52))(*((uint32_t *)Block + v1));
        (*(void (/*thiscall*/ **)(int, int))(v10 + 36))(dword_8F8520, v11);
        v12 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v1) + 304))(*((uint32_t *)Block + v1));
        v13 = *(uint32_t *)dword_8F8520;
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 52))(v12);
        (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 12);
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 576))(a1);
        v16 = *(uint32_t *)dword_8F8520;
        v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 48))(v15);
        (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 576))(a1);
        v19 = *(uint32_t *)dword_8F8520;
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 52))(v18);
        (*(void (/*thiscall*/ **)(int, int))(v19 + 36))(dword_8F8520, v20);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        v2 = Block;
      }
      if ( --v26 == 0 )
        goto LABEL_17;
      goto LABEL_15;
    }
LABEL_17:
    j__free(v2);
  }
}


// ------------------------------------------------------------
// 0x4E1390 sub_4E1390
// ------------------------------------------------------------
int /*thiscall*/ sub_4E1390(int *this, uint32_t *a2, uint32_t *a3)
{
  int *v3; // edi
  int result; // eax
  unsigned int v5; // esi
  uint32_t *v6; // ecx
  int v7; // edx
  uint32_t *v8; // edi
  int v9; // esi
  unsigned int v10; // edx
  uint32_t *v11; // eax
  int v12; // eax

  v3 = this;
  result = *(this + 1943);
  if ( result == 1 || result == 2 )
  {
    v5 = 0;
    v6 = this + 1951;
    while ( 1 )
    {
      v7 = v6[1];
      if ( v7 == 0 || v5 >= (v6[2] - v7) >> 2 )
        break;
      result = (uint8_t)BYTE1(*(uint32_t *)(v3[1952] + 4 * v5));
      if ( result == 255 && ((uint16_t)a2 & 0xFF00) == 0xFF00 )
        return result;
      if ( result == 254 && ((uint16_t)a2 & 0xFF00) == 0xFE00 )
        return result;
      if ( result == 253 )
      {
        result = (uint16_t)a2 & 0xFF00;
        if ( result == 64768 )
          return result;
      }
      if ( *(uint32_t **)(v3[1952] + 4 * v5) == a2 )
        return result;
      v3 = this;
      ++v5;
    }
    result = BYTE2(a2);
    v8 = a3;
    if ( *a3 >= dword_6F89AC[BYTE2(a2)] )
    {
      v9 = v6[1];
      a3 = a2;
      if ( v9 != 0 )
        v10 = (v6[2] - v9) >> 2;
      else
        v10 = 0;
      if ( v9 != 0 && v10 < (v6[3] - v9) >> 2 )
      {
        v11 = (uint32_t *)v6[2];
        *v11 = a2;
        v6[2] = v11 + 1;
      }
      else
      {
        sub_430C80((void *)v6[2], 1, (int)&a3);
      }
      *v8 -= dword_6F89AC[BYTE2(a2)];
      v12 = sub_422E70((uint8_t)a2 + 1256);
      return off_77F3FC((char *)&byte_6F929C, v12, (uint8_t)a2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E14E0 sub_4E14E0
// ------------------------------------------------------------
void /*thiscall*/ sub_4E14E0(int *this, int a2, int *a3)
{
  int v4; // edi
  int v5; // edx

  v4 = 13500;
  while ( *a3 >= 2 )
  {
    v5 = dword_6F8940[rand() % 27];
    if ( v5 > 131091 )
    {
      if ( v5 <= 261644 && (v5 >= 261641 || v5 >= 196612 && v5 <= 196615) )
        goto LABEL_13;
    }
    else if ( v5 == 131091 || v5 == 65281 || v5 == 130816 )
    {
      goto LABEL_13;
    }
    sub_4E1390(this, (uint32_t *)v5, a3);
LABEL_13:
    if ( --v4 <= 0 )
      return;
  }
}



// ------------------------------------------------------------
// 0x4E1560 sub_4E1560
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4E1560(int *this, int a2, uint32_t *a3)
{
  unsigned int i; // esi
  int v5; // ecx
  unsigned int result; // eax

  for ( i = 0; ; ++i )
  {
    v5 = *(uint32_t *)(a2 + 4);
    if ( v5 == 0 )
      break;
    result = (*(uint32_t *)(a2 + 8) - v5) >> 2;
    if ( i >= result )
      break;
    result = sub_4E1390(this, *(uint32_t **)(v5 + 4 * i), a3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E15A0 sub_4E15A0
// ------------------------------------------------------------
void /*userpurge*/ sub_4E15A0(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>, int a4)
{
  int v5; // ecx
  unsigned int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  unsigned int v10; // eax
  unsigned int v11; // edi
  int v12; // edx
  int v13; // edi
  int v14; // eax
  int v15; // ebx
  unsigned int v16; // edi
  int v17; // ebx
  void *v20; // [esp+4h] [ebp-1Ch] BYREF
  int v21; // [esp+8h] [ebp-18h]
  int v22; // [esp+Ch] [ebp-14h]
  int v23; // [esp+10h] [ebp-10h]
  int v24; // [esp+1Ch] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1) == 0
    && rand() % 100 < a1[2118] )
  {
    v5 = a1[1905];
    v6 = v5 != 0 ? (a1[1906] - v5) >> 5 : 0;
    if ( a1[2119] < v6 )
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 688))(a1);
      v8 = *(uint32_t *)(v7 + 40);
      v9 = v7 + 36;
      v10 = v8 != 0 ? (*(uint32_t *)(v9 + 8) - v8) >> 2 : 0;
      v11 = a1[2119];
      if ( v11 < v10 && *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 688))(a1) + 40) + 4 * v11) != 0 )
      {
        v12 = a1[1905];
        if ( *(uint8_t *)(v12 + 32 * a1[2119]) == 1 )
        {
          v13 = *(uint32_t *)(32 * a1[2119] + v12 + 16);
          v14 = a1[1813];
          v15 = 0;
          if ( v14 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*a1 + 8))(a1, v14, 0) < v13 )
          {
            v15 = a1[1813];
          }
          else
          {
            v21 = 0;
            v22 = 0;
            v23 = 0;
            v24 = 0;
            sub_4E0CD0(a1, 17, 0, (int)&v20, v13);
            if ( v21 != 0 )
            {
              v16 = (v22 - v21) >> 2;
              if ( v16 != 0 )
              {
                sub_432FA0();
                v15 = *(uint32_t *)(v21 + 4 * (rand() % v16));
              }
            }
            v24 = -1;
            sub_5E5260(&v20);
          }
          if ( v15 != 0 )
          {
            v17 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v15 + 120))(v15, a2, a3);
            if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1) >= v17 )
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 144))(a1, 0);
            else
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*a1 + 144))(a1, 1);
            v21 = 0;
            v22 = 0;
            v23 = 0;
            v24 = 1;
            sub_431230((int)&v20, a1 + 2119);
            (*(void (/*thiscall*/ **)(uint32_t *, int, void **))(*a1 + 560))(a1, 8, &v20);
            sub_5E5260(&v20);
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x4E1780 sub_4E1780
// ------------------------------------------------------------
char /*thiscall*/ sub_4E1780(uint32_t *this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // edi
  unsigned int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v15; // [esp-4h] [ebp-10h]

  sub_58FC30();
  if ( *(this + 1813) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1264))(this);
  if ( (*(uint8_t *)(this + 162) & 1) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1220))(this);
  v2 = sub_4E0CD0(273, 0, 0, -1);
  if ( v2 != 0 )
  {
    if ( v2 > 0 && *((uint8_t *)this + 8296) == 0 )
    {
      if ( rand() % 100 < 15 )
        sub_4DB130(25, -1);
      *((uint8_t *)this + 8296) = 1;
    }
  }
  else if ( *((uint8_t *)this + 8296) == 1 )
  {
    *((uint8_t *)this + 8296) = 0;
    if ( rand() % 100 < 15 )
      sub_4DB130(26, -1);
  }
  v3 = *(this + 2088);
  if ( v3 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 724))(v3) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1164))(this, 0);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1176))(this) != 0 )
  {
    v4 = sub_699000((int)(this + 16));
    if ( v4 >= (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1176))(this) )
    {
      v5 = *(this + 1639);
      if ( v5 < 4 || v5 == 9 )
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t))(*this + 560))(this, 13, 0, 2, 0);
    }
  }
  if ( dword_8F7C04 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 144))(dword_8F8520)
    && (*(this + 1815) == 0 || sub_699000((int)(this + 2)) >= *(this + 1917) && ((v6 = *(this + 1639)) == 0 || v6 == 2)) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1252))(this);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 936))(this) != 0 )
  {
    *((uint8_t *)this + 7092) = 0;
  }
  v7 = *(this + 1639);
  switch ( v7 )
  {
    case 0:
      LOBYTE(v7) = sub_4DA730(this);
      break;
    case 5:
      if ( *(this + 30) != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 1020))(this) != 0 )
        {
          v12 = sub_699000((int)(this + 1640));
          v13 = sub_423A80(255, 100, 100 - *(this + 1942) + v12, 100);
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 252))(this, 0, v13);
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 252))(this, 1, v13);
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 252))(this, 2, v13);
        }
        else if ( *(uint32_t *)(dword_8F7A24 + 244) == 2 )
        {
          if ( (double)(int)*(this + 1942) * 0.40000001 < (double)sub_699000((int)(this + 1640)) )
          {
            v10 = *(this + 1942);
            if ( sub_699000((int)(this + 1640)) < v10 && sub_460550((uint64_t)((double)v10 * 0.30000001)) != 0 )
              (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 252))(this, 3, 0);
            else
              (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 252))(this, 3, -1);
            sub_494F20(0, 0.0);
            sub_494F20(1, 0.0);
            sub_494F20(2, 0.0);
          }
        }
        else
        {
          v11 = sub_699000((int)(this + 1640));
          v15 = sub_423A80(255, 0, 100 - *(this + 1942) + v11, 100);
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 252))(this, 3, v15);
        }
      }
      v7 = sub_699000((int)(this + 1640));
      if ( v7 >= *(this + 1942) )
      {
        LOBYTE(v7) = *((uint8_t *)this + 264);
        if ( (uint8_t)v7 == 0 )
          LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1256))(this);
      }
      break;
    case 10:
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
      if ( v7 != 0 )
      {
        v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
        if ( *(uint8_t *)(v7 + 170) != 0 )
        {
          LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
          if ( (uint8_t)v7 != 0 )
            LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(
                           this,
                           0,
                           0,
                           0,
                           0);
        }
      }
      break;
    case 11:
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      if ( v7 == 0 )
        LOBYTE(v7) = sub_49C970(5, 0, 0);
      break;
    case 13:
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
        && sub_699000((int)(this + 1640)) >= 850 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1256))(this);
      }
      v7 = sub_699000((int)(this + 1640));
      if ( v7 >= 300 )
      {
        v8 = sub_699000((int)(this + 1640));
        v9 = sub_423A80(255, 0, v8 - 300, 550);
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 252))(this, 3, v9);
      }
      break;
    default:
      return v7;
  }
  return v7;
}


// ------------------------------------------------------------
// 0x4E1BE0 sub_4E1BE0
// ------------------------------------------------------------
char /*thiscall*/ sub_4E1BE0(uint32_t *this)
{
  char result; // al
  int v3; // eax
  unsigned int v4; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // ecx
  int v12; // ecx
  int v13; // edx
  int v14; // edi
  int v15; // ebx
  int v16; // edx
  int v17; // [esp+4h] [ebp-2Ch] BYREF
  int v18; // [esp+8h] [ebp-28h] BYREF
  int v19; // [esp+Ch] [ebp-24h] BYREF
  int v20; // [esp+10h] [ebp-20h] BYREF
  int v21; // [esp+14h] [ebp-1Ch] BYREF
  int v22; // [esp+18h] [ebp-18h] BYREF
  int v23; // [esp+1Ch] [ebp-14h]
  int v24; // [esp+20h] [ebp-10h]
  int v25; // [esp+24h] [ebp-Ch] BYREF
  int v26; // [esp+28h] [ebp-8h]
  unsigned int v27; // [esp+2Ch] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( result != 0 )
  {
    result = *((uint8_t *)this + 7528);
    if ( result != 0 )
    {
      v3 = *(this + 1787);
      v4 = 0;
      v5 = *(this + 1813);
      v23 = v5;
      v26 = 0;
      *(this + 1813) = 0;
      v24 = 0;
      if ( (v3 == 9 || v3 == 10 || v3 == 11)
        && v5 != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, v5) == 1 )
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1152))(this, v5);
      }
      else
      {
        v6 = *(this + 1891);
        v18 = 0;
        v19 = 0;
        v20 = 0;
        v21 = 0;
        v17 = 0;
        v22 = 0;
        if ( v6 != 0 )
          sub_4DC920(this, &v17, &v18);
        if ( *(this + 1892) != 0 )
          sub_4DCAB0(this, &v19, &v20);
        if ( *(this + 1893) != 0 )
          sub_4E0A40(this, &v21, &v22);
        while ( 1 )
        {
          v7 = *(this + 29);
          v8 = *(uint32_t *)(v7 + 120);
          v27 = v4;
          v9 = v8 != 0 ? (*(uint32_t *)(v7 + 124) - v8) >> 2 : 0;
          if ( (int)v4 >= v9 )
            break;
          v10 = *(uint32_t *)(v7 + 120);
          if ( v10 != 0 && v4 < (*(uint32_t *)(v7 + 124) - v10) >> 2 )
            v11 = *(uint32_t *)(v10 + 4 * v4);
          else
            v11 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 40))(v11, 17) != 0 )
          {
            v12 = *(this + 29);
            v13 = *(uint32_t *)(v12 + 120);
            if ( v13 != 0 && v4 < (*(uint32_t *)(v12 + 124) - v13) >> 2 )
              v14 = *(uint32_t *)(v13 + 4 * v4);
            else
              v14 = 0;
            if ( (uint8_t)sub_4E4630(v14) != 0
              && (uint8_t)sub_4E5CA0(v14) == 0
              && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, v14) != 0 )
            {
              v25 = 0;
              sub_4DCCB0(this, (int)&v25, v14, COERCE_FLOAT(&v17));
              v15 = v25;
              if ( (v25 > v24 || v26 == 0) && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 724))(v14) == 0 )
              {
                v26 = v14;
                v24 = v15;
              }
              v4 = v27;
            }
          }
          v5 = v23;
          ++v4;
        }
        v16 = *this;
        if ( v5 == v26 )
        {
          return (*(int (/*thiscall*/ **)(uint32_t *, int))(v16 + 1152))(this, v5);
        }
        else
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(v16 + 1152))(this, v26);
          return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1260))(this);
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4E1DD0 sub_4E1DD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E1DD0(uint32_t *this, uint32_t *a2, uint32_t *a3)
{
  int v4; // edi
  int v5; // esi
  uint32_t *result; // eax

  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) / 2;
  *a2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) <= v4 ? 0 : 2;
  v5 = sub_4E0CD0(this, 529, 1, 0, -1);
  if ( v5 != 0 )
  {
    result = (uint32_t *)sub_456390(0);
    if ( v5 <= (int)result )
    {
      *a3 = v5 == sub_456390(0);
      return a3;
    }
    else
    {
      *a3 = 2;
    }
  }
  else
  {
    *a3 = 0;
    return a3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E1E70 sub_4E1E70
// ------------------------------------------------------------
int /*thiscall*/ sub_4E1E70(int this)
{
  sub_4A4430((uint32_t *)this);
  *(uint32_t *)this = &CNRDPassiveObject::`vftable';
  sub_4DF060((uint32_t *)(this + 680));
  *(uint32_t *)(this + 840) = 15;
  *(uint32_t *)(this + 836) = 0;
  *(uint8_t *)(this + 820) = 0;
  sub_4A3450((uint32_t *)(this + 724));
  *(uint32_t *)(this + 940) = 15;
  *(uint32_t *)(this + 936) = 0;
  *(uint8_t *)(this + 920) = 0;
  sub_5FF8E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4E1FC0 sub_4E1FC0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E1FC0(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 173);
  if ( v1 != 0 )
    return (*(int (**)(void))(*(uint32_t *)v1 + 576))();
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4E1FE0 sub_4E1FE0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E1FE0(int this, int a2)
{
  int v2; // esi
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  v2 = this + 680;
  *(uint32_t *)(this + 680) = *(uint32_t *)a2;
  *(uint32_t *)(this + 684) = *(uint32_t *)(a2 + 4);
  *(uint32_t *)(this + 688) = *(uint32_t *)(a2 + 8);
  *(uint32_t *)(this + 692) = *(uint32_t *)(a2 + 12);
  *(uint32_t *)(this + 696) = *(uint32_t *)(a2 + 16);
  *(uint8_t *)(this + 700) = *(uint8_t *)(a2 + 20);
  *(uint8_t *)(this + 701) = *(uint8_t *)(a2 + 21);
  *(uint32_t *)(this + 704) = *(uint32_t *)(a2 + 24);
  sub_41DC80(this + 708, a2 + 28);
  return v2;
}



// ------------------------------------------------------------
// 0x4E2040 sub_4E2040
// ------------------------------------------------------------
int /*thiscall*/ sub_4E2040(void **this)
{
  *this = &CNRDPassiveObject::`vftable';
  sub_5FF980();
  if ( (unsigned int)*(this + 235) >= 0x10 )
    j__free(*(this + 230));
  *(this + 235) = (void *)15;
  *(this + 234) = nullptr;
  *((uint8_t *)this + 920) = 0;
  if ( (unsigned int)*(this + 210) >= 0x10 )
    j__free(*(this + 205));
  *(this + 210) = (void *)15;
  *(this + 209) = nullptr;
  *((uint8_t *)this + 820) = 0;
  sub_4017E0(this + 177);
  return sub_4A4590(this);
}



// ------------------------------------------------------------
// 0x4E2100 sub_4E2100
// ------------------------------------------------------------
void **/*thiscall*/ sub_4E2100(void **Block, char a2)
{
  sub_4E2040(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4E2130 sub_4E2130
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4E2130(uint8_t *this, int a2, int a3, int a4)
{
  sub_4E1E70((int)this);
  *(uint32_t *)this = &CNRDItemObject::`vftable';
  *(this + 992) = 0;
  *((uint32_t *)this + 247) = &off_6C2B88;
  *((uint32_t *)this + 249) = 0;
  *(this + 1000) = 1;
  *(this + 1002) = 0;
  *(this + 1001) = 0;
  *((uint32_t *)this + 253) = 0;
  *((uint32_t *)this + 252) = 0;
  *((uint32_t *)this + 251) = 0;
  sub_41A630((unsigned int)(this + 1016));
  *((uint32_t *)this + 254) = &clong::`vftable';
  *(this + 1036) = 0;
  *((uint32_t *)this + 258) = &off_6C2B88;
  *((uint32_t *)this + 260) = 0;
  *(this + 1044) = 1;
  *(this + 1046) = 0;
  *(this + 1045) = 0;
  *((uint32_t *)this + 264) = 0;
  *((uint32_t *)this + 263) = 0;
  *((uint32_t *)this + 262) = 0;
  sub_578740(this);
  sub_578D50(a2, a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x4E2230 sub_4E2230
// ------------------------------------------------------------
void */*thiscall*/ sub_4E2230(void *Block, char a2)
{
  sub_4E2260();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4E2260 sub_4E2260
// ------------------------------------------------------------
int /*thiscall*/ sub_4E2260(int this)
{
  *(uint32_t *)this = &CNRDItemObject::`vftable';
  sub_578780();
  *(uint32_t *)(this + 1032) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 1036) = 0;
  sub_41A580((uint32_t *)(this + 1016));
  *(uint32_t *)(this + 988) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 992) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x4E22E0 sub_4E22E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E22E0(int *this, int a2, void *a3, int a4, int a5, void *Block, int a7)
{
  uint8_t *v10; // ecx
  uint8_t *v11; // edi
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v16; // [esp+0h] [ebp-24h]
  int v17; // [esp+4h] [ebp-20h]
  int v18; // [esp+8h] [ebp-1Ch]
  unsigned int v19; // [esp+Ch] [ebp-18h] BYREF
  int v20; // [esp+10h] [ebp-14h] BYREF
  int v21; // [esp+14h] [ebp-10h] BYREF
  int v22; // [esp+20h] [ebp-4h]
  int v23; // [esp+30h] [ebp+Ch]
  int v24; // [esp+38h] [ebp+14h]

  v19 = (unsigned int)a3 + 10 * (*(int (/*thiscall*/ **)(int *))(*this + 52))(this) + a2 + a5;
  srand(v19);
  v23 = rand() % 360;
  v24 = sub_522300(a3, a4, 0, 0, (int)Block, 1);
  v10 = operator new(0x424u);
  v11 = nullptr;
  v22 = 0;
  if ( v10 != nullptr )
    v11 = sub_4E2130(v10, v24, (int)&v19, v23 + 360 / a2);
  v12 = *this;
  v22 = -1;
  v20 = (*(int (/*thiscall*/ **)(int *))(v12 + 120))(this);
  v21 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  off_77F3FC((char *)&byte_6F9858, 289, a5);
  v13 = (*(int (/*thiscall*/ **)(int *, int, int, uint8_t *, uint32_t, uint32_t))(*this + 80))(this, 289, a5, v11, 0, 0);
  sub_45FE80(v13, (int)v11, v16, v17, v18, v19, v20);
  v14 = *(uint32_t *)v11;
  v20 = 1;
  v19 = 0;
  (*(void (/*thiscall*/ **)(uint8_t *, int *, int *))(v14 + 140))(v11, &v20, &v21);
  (*(void (/*thiscall*/ **)(uint8_t *, int, int, int))(*(uint32_t *)v11 + 112))(v11, v20, v21, 60);
  return sub_578870(a7, 10000);
}



// ------------------------------------------------------------
// 0x4E2420 sub_4E2420
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4E2420(char *this, void *Src, int a3)
{
  int v4; // ecx
  int v5; // esi
  unsigned int result; // eax
  int v7; // eax
  char *v8; // edi
  int v9; // eax
  uint32_t *v10; // ecx
  uint32_t *v11; // eax
  uint32_t *v12; // ecx
  uint32_t *v13; // eax
  int v14; // edi
  int v15; // edi
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // edi
  int v20; // eax
  int *v21; // edi
  int v22; // ecx
  int v23; // eax
  bool v24; // zf
  int v25; // edi
  int v26; // eax
  int v27; // edi
  int v28; // eax
  int v29; // edi
  int v30; // eax
  int v31; // edi
  int v32; // eax
  int v33; // edi
  char v34; // al
  int v35; // eax
  int v36; // esi
  int v37; // ecx
  unsigned int v38; // edi
  int *v39; // edx
  int v40; // esi
  unsigned int v41; // edx
  uint32_t *v42; // eax
  int v43; // edi
  char v44; // al
  int v45; // eax
  int v46; // esi
  int v47; // ecx
  unsigned int v48; // edi
  int *v49; // edx
  int v50; // esi
  unsigned int v51; // edx
  uint32_t *v52; // eax
  uint32_t *v53; // edx
  char *v54; // ecx
  int v55; // eax
  char *v56; // esi
  int v57; // edi
  int v58; // eax
  int v59; // eax
  char *v60; // esi
  int v61; // edi
  int v62; // eax
  int v63; // eax
  uint32_t *v64; // esi
  int v65; // eax
  char *v66; // edi
  uint32_t *v67; // esi
  int *v68; // eax
  int *v69; // esi
  int *v70; // ecx
  int v71; // eax
  int *v72; // eax
  int *v73; // esi
  int *v74; // ecx
  int v75; // edx
  unsigned int i; // esi
  int v77; // ecx
  int v78; // [esp-4h] [ebp-C0h]
  int v79; // [esp-4h] [ebp-C0h]
  uint32_t v80[23]; // [esp+Ch] [ebp-B0h] BYREF
  void *Block; // [esp+6Ch] [ebp-50h]
  int v82; // [esp+7Ch] [ebp-40h]
  unsigned int v83; // [esp+80h] [ebp-3Ch]
  int v84; // [esp+A4h] [ebp-18h]
  int v85; // [esp+A8h] [ebp-14h] BYREF
  uint32_t *v86; // [esp+ACh] [ebp-10h]
  int v87; // [esp+B8h] [ebp-4h]
  uint32_t *Srca; // [esp+C4h] [ebp+8h]
  char *Srcb; // [esp+C4h] [ebp+8h]
  char *Srcc; // [esp+C4h] [ebp+8h]
  char *Srcd; // [esp+C4h] [ebp+8h]
  char *Srce; // [esp+C4h] [ebp+8h]
  int Srcf; // [esp+C4h] [ebp+8h]

  v4 = (int)(this + 7640);
  *(uint8_t *)(v4 + 13) = 0;
  *(uint8_t *)(v4 + 14) = 0;
  sub_698F90(v4, 0, 0);
  *(this + 8501) = 0;
  *(this + 8502) = 0;
  sub_698F90((int)(this + 8488), 0, 0);
  *((uint32_t *)this + 2120) = 0;
  *((uint32_t *)this + 2121) = 3000;
  sub_4015C0(Src, strlen((const char *)Src));
  *(this + 7180) = 0;
  *(this + 7181) = 0;
  *(this + 7182) = 0;
  *(this + 7183) = 0;
  *((uint32_t *)this + 1798) = 0;
  *((uint32_t *)this + 1799) = 6;
  *((uint32_t *)this + 1800) = 12;
  *((uint32_t *)this + 1801) = 0;
  *((uint32_t *)this + 1802) = 1600;
  *((uint32_t *)this + 1803) = 0;
  *((uint32_t *)this + 1804) = 0;
  *((uint32_t *)this + 1805) = 0;
  *((uint32_t *)this + 1806) = 0;
  *((uint32_t *)this + 1807) = 0;
  *((uint32_t *)this + 1807) = dword_99FCCC;
  *((uint32_t *)this + 1802) = 180;
  *((uint32_t *)this + 1798) = 1;
  *(this + 7182) = 1;
  *((uint32_t *)this + 1796) = -16777216;
  v5 = (*(int (/*thiscall*/ **)(int, void *))(*(uint32_t *)dword_8F84C4 + 4))(dword_8F84C4, Src);
  v86 = (uint32_t *)v5;
  if ( v5 == 0 )
    return off_77F3FC("MONSTER CREATE FAIL! FILENAME[%s]", (const char *)Src);
  sub_4014D0((std::_String_base *)(this + 360), v5 + 928, 0, -1);
  *(uint32_t *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this) = *(uint32_t *)v5;
  v7 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this);
  sub_4014D0((std::_String_base *)(v7 + 4), v5 + 4, 0, -1);
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this) + 32) = *(uint32_t *)(v5 + 32);
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this) + 36) = *(uint32_t *)(v5 + 36);
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this) + 40) = *(uint32_t *)(v5 + 40);
  *((uint32_t *)this + 27) = *(uint32_t *)(v5 + 44);
  if ( *((uint32_t *)this + 78) < 0x10u )
    v8 = this + 292;
  else
    v8 = *((char **)this + 73);
  v9 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);
  off_77F3FC(aSD_2, v8, v9);
  sub_4ED3F0((int)(this + 328), v5 + 48);
  sub_4A3F80(v5 + 128);
  v10 = *((uint32_t **)this + 84);
  v11 = *((uint32_t **)this + 83);
  if ( v11 == v10 )
    goto LABEL_11;
  do
  {
    if ( *v11 == 10 )
      break;
    ++v11;
  }
  while ( v11 != v10 );
  if ( v11 == v10 )
  {
LABEL_11:
    if ( (uint8_t)sub_4DAB60(11) == 0 )
      (*(void (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 456))(this, 10, 0);
  }
  v12 = *((uint32_t **)this + 84);
  v13 = *((uint32_t **)this + 83);
  if ( v13 == v12 )
    goto LABEL_19;
  do
  {
    if ( *v13 == 12 )
      break;
    ++v13;
  }
  while ( v13 != v12 );
  if ( v13 == v12 )
  {
LABEL_19:
    if ( (uint8_t)sub_4DAB60(13) == 0
      && (uint8_t)sub_4DAB60(14) == 0
      && (uint8_t)sub_4DAB60(15) == 0 )
    {
      (*(void (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 456))(this, 13, 0);
    }
  }
  *((uint32_t *)this + 1880) = *(uint32_t *)(v5 + 444);
  *((uint32_t *)this + 1881) = *(uint32_t *)(v5 + 448);
  *(this + 7529) = *(uint8_t *)(v5 + 452);
  *(this + 7530) = *(uint8_t *)(v5 + 453);
  *(this + 7531) = *(uint8_t *)(v5 + 468);
  *(this + 7532) = *(uint8_t *)(v5 + 469);
  *(this + 7533) = *(uint8_t *)(v5 + 470);
  *((uint32_t *)this + 1898) = *(uint32_t *)(v5 + 492);
  *((uint32_t *)this + 1900) = *(uint32_t *)(v5 + 496);
  *(this + 7559) = *(uint8_t *)(v5 + 500);
  *((uint32_t *)this + 1890) = *(uint32_t *)(v5 + 504);
  *((uint32_t *)this + 1894) = *(uint32_t *)(v5 + 472);
  *((uint32_t *)this + 1895) = *(uint32_t *)(v5 + 476);
  *((uint32_t *)this + 1896) = *(uint32_t *)(v5 + 480);
  *((uint32_t *)this + 1897) = *(uint32_t *)(v5 + 484);
  *((uint32_t *)this + 1891) = *(uint32_t *)(v5 + 456);
  *((uint32_t *)this + 1892) = *(uint32_t *)(v5 + 460);
  sub_4DEEA0(v5 + 900);
  *((uint32_t *)this + 1822) = *(uint32_t *)(v5 + 916);
  *((uint32_t *)this + 1823) = *(uint32_t *)(v5 + 920);
  *((uint32_t *)this + 1824) = *(uint32_t *)(v5 + 924);
  if ( sub_40BF00((std::_String_base *)(v5 + 508), 0, *(uint32_t *)(v5 + 528), szPassword, 0) != 0 )
  {
    if ( *(uint32_t *)(v5 + 532) < 0x10u )
      v14 = v5 + 512;
    else
      v14 = *(uint32_t *)(v5 + 512);
    v78 = *(uint32_t *)(v5 + 536);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v14);
    *((uint32_t *)this + 1825) = sub_418DD0(v78);
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 540), 0, *(uint32_t *)(v5 + 560), szPassword, 0) != 0 )
  {
    v87 = 0;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( *(uint32_t *)(v5 + 564) < 0x10u )
        LOBYTE(v15) = v5 + 32;
      else
        v15 = *(uint32_t *)(v5 + 544);
      if ( *((uint32_t *)this + 96) < 0x10u )
        v16 = sub_431920((uint8_t)this + 108, v15, 1);
      else
        v16 = sub_431920(*((uint32_t *)this + 91), v15, 1);
    }
    else
    {
      v16 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1540) = v16;
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 568), 0, *(uint32_t *)(v5 + 588), szPassword, 0) != 0 )
  {
    v87 = 1;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( *(uint32_t *)(v5 + 592) < 0x10u )
        LOBYTE(v17) = v5 + 60;
      else
        v17 = *(uint32_t *)(v5 + 572);
      if ( *((uint32_t *)this + 96) < 0x10u )
        v18 = sub_431920((uint8_t)this + 108, v17, 1);
      else
        v18 = sub_431920(*((uint32_t *)this + 91), v17, 1);
    }
    else
    {
      v18 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1541) = v18;
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 596), 0, *(uint32_t *)(v5 + 616), szPassword, 0) != 0 )
  {
    v87 = 2;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( *(uint32_t *)(v5 + 620) < 0x10u )
        LOBYTE(v19) = v5 + 88;
      else
        v19 = *(uint32_t *)(v5 + 600);
      if ( *((uint32_t *)this + 96) < 0x10u )
        v20 = sub_431920((uint8_t)this + 108, v19, 1);
      else
        v20 = sub_431920(*((uint32_t *)this + 91), v19, 1);
    }
    else
    {
      v20 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1542) = v20;
  }
  Srca = this + 6172;
  v21 = (int *)(v5 + 628);
  v85 = 2;
  do
  {
    if ( sub_40BF00((std::_String_base *)(v21 - 1), 0, v21[4], szPassword, 0) != 0 )
    {
      v84 = sub_42FCB0(228);
      v87 = 3;
      if ( v84 != 0 )
      {
        if ( (unsigned int)v21[5] < 0x10 )
          LOBYTE(v22) = (uint8_t)v21;
        else
          v22 = *v21;
        if ( *((uint32_t *)this + 96) < 0x10u )
          v23 = sub_431920((uint8_t)this + 108, v22, 1);
        else
          v23 = sub_431920(*((uint32_t *)this + 91), v22, 1);
      }
      else
      {
        v23 = 0;
      }
      v87 = -1;
      *Srca = v23;
    }
    v21 += 7;
    v24 = v85 == 1;
    ++Srca;
    --v85;
  }
  while ( !v24 );
  if ( sub_40BF00((std::_String_base *)(v5 + 680), 0, *(uint32_t *)(v5 + 700), szPassword, 0) != 0 )
  {
    v87 = 4;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( *(uint32_t *)(v5 + 704) < 0x10u )
        LOBYTE(v25) = v5 - 84;
      else
        v25 = *(uint32_t *)(v5 + 684);
      if ( *((uint32_t *)this + 96) < 0x10u )
        v26 = sub_431920((uint8_t)this + 108, v25, 1);
      else
        v26 = sub_431920(*((uint32_t *)this + 91), v25, 1);
    }
    else
    {
      v26 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1545) = v26;
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 708), 0, *(uint32_t *)(v5 + 728), szPassword, 0) != 0 )
  {
    v87 = 5;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( *(uint32_t *)(v5 + 732) < 0x10u )
        LOBYTE(v27) = v5 - 56;
      else
        v27 = *(uint32_t *)(v5 + 712);
      if ( *((uint32_t *)this + 96) < 0x10u )
        v28 = sub_431920((uint8_t)this + 108, v27, 1);
      else
        v28 = sub_431920(*((uint32_t *)this + 91), v27, 1);
    }
    else
    {
      v28 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1546) = v28;
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 736), 0, *(uint32_t *)(v5 + 756), szPassword, 0) != 0 )
  {
    v87 = 6;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( *(uint32_t *)(v5 + 760) < 0x10u )
        LOBYTE(v29) = v5 - 28;
      else
        v29 = *(uint32_t *)(v5 + 740);
      if ( *((uint32_t *)this + 96) < 0x10u )
        v30 = sub_431920((uint8_t)this + 108, v29, 1);
      else
        v30 = sub_431920(*((uint32_t *)this + 91), v29, 1);
    }
    else
    {
      v30 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1547) = v30;
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 764), 0, *(uint32_t *)(v5 + 784), szPassword, 0) != 0 )
  {
    v87 = 7;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( *(uint32_t *)(v5 + 788) < 0x10u )
        LOBYTE(v31) = v5;
      else
        v31 = *(uint32_t *)(v5 + 768);
      if ( *((uint32_t *)this + 96) < 0x10u )
        v32 = sub_431920((uint8_t)this + 108, v31, 1);
      else
        v32 = sub_431920(*((uint32_t *)this + 91), v31, 1);
    }
    else
    {
      v32 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1548) = v32;
  }
  Srcb = *(char **)(v5 + 796);
  if ( Srcb != *(char **)(v5 + 800) )
  {
    do
    {
      if ( strcmp((const char *)sub_41ACF0(Srcb), szPassword) == 0 )
      {
        v40 = *((uint32_t *)this + 1550);
        v37 = (int)(this + 6196);
        v85 = 0;
        if ( v40 != 0 )
          v41 = (*((uint32_t *)this + 1551) - v40) >> 2;
        else
          v41 = 0;
        if ( v40 == 0 || v41 >= (*((uint32_t *)this + 1552) - v40) >> 2 )
          goto LABEL_128;
        v42 = *((uint32_t **)this + 1551);
        *v42 = 0;
        *((uint32_t *)this + 1551) = v42 + 1;
      }
      else
      {
        v84 = sub_42FCB0(228);
        v87 = 8;
        if ( v84 != 0 )
        {
          if ( *((uint32_t *)this + 96) < 0x10u )
            LOBYTE(v33) = (uint8_t)this + 108;
          else
            v33 = *((uint32_t *)this + 91);
          v34 = sub_41ACF0(Srcb);
          v35 = sub_431920(v33, v34, 1);
        }
        else
        {
          v35 = 0;
        }
        v36 = *((uint32_t *)this + 1550);
        v37 = (int)(this + 6196);
        v87 = -1;
        v85 = v35;
        if ( v36 != 0 )
          v38 = (*((uint32_t *)this + 1551) - v36) >> 2;
        else
          v38 = 0;
        if ( v36 == 0 || v38 >= (*((uint32_t *)this + 1552) - v36) >> 2 )
        {
LABEL_128:
          sub_42AC90(v37, *(char **)(v37 + 8), 1u, &v85);
          goto LABEL_129;
        }
        v39 = *((int **)this + 1551);
        *v39 = v35;
        *((uint32_t *)this + 1551) = v39 + 1;
      }
LABEL_129:
      Srcb += 4;
    }
    while ( Srcb != (char *)v86[200] );
  }
  for ( Srcc = (char *)v86[203]; Srcc != (char *)v86[204]; Srcc += 4 )
  {
    if ( strcmp((const char *)sub_41ACF0(Srcc), szPassword) == 0 )
    {
      v50 = *((uint32_t *)this + 1554);
      v47 = (int)(this + 6212);
      v85 = 0;
      if ( v50 != 0 )
        v51 = (*((uint32_t *)this + 1555) - v50) >> 2;
      else
        v51 = 0;
      if ( v50 == 0 || v51 >= (*((uint32_t *)this + 1556) - v50) >> 2 )
        goto LABEL_150;
      v52 = *((uint32_t **)this + 1555);
      *v52 = 0;
      *((uint32_t *)this + 1555) = v52 + 1;
    }
    else
    {
      v84 = sub_42FCB0(228);
      v87 = 9;
      if ( v84 != 0 )
      {
        if ( *((uint32_t *)this + 96) < 0x10u )
          LOBYTE(v43) = (uint8_t)this + 108;
        else
          v43 = *((uint32_t *)this + 91);
        v44 = sub_41ACF0(Srcc);
        v45 = sub_431920(v43, v44, 1);
      }
      else
      {
        v45 = 0;
      }
      v46 = *((uint32_t *)this + 1554);
      v47 = (int)(this + 6212);
      v87 = -1;
      v85 = v45;
      if ( v46 != 0 )
        v48 = (*((uint32_t *)this + 1555) - v46) >> 2;
      else
        v48 = 0;
      if ( v46 == 0 || v48 >= (*((uint32_t *)this + 1556) - v46) >> 2 )
      {
LABEL_150:
        sub_42AC90(v47, *(char **)(v47 + 8), 1u, &v85);
        continue;
      }
      v49 = *((int **)this + 1555);
      *v49 = v45;
      *((uint32_t *)this + 1555) = v49 + 1;
    }
  }
  if ( v86[211] != 0 )
  {
    if ( v86[212] < 0x10u )
      v53 = v86 + 207;
    else
      v53 = (uint32_t *)v86[207];
    if ( *((uint32_t *)this + 96) < 0x10u )
      v54 = this + 364;
    else
      v54 = *((char **)this + 91);
    v55 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E0 + 12))(dword_8F84E0, "%s%s", v54, v53);
    sub_4B2970((uint32_t *)this + 1579, v55);
  }
  for ( Srcd = (char *)v86[214]; Srcd != (char *)v86[215]; Srcd += 4 )
  {
    if ( strcmp((const char *)sub_41ACF0(Srcd), szPassword) == 0 )
    {
      v83 = 15;
      v82 = 0;
      LOBYTE(Block) = 0;
      v87 = 10;
      sub_4A3450(v80);
      v87 = 11;
      sub_4B52F0(v80);
      v87 = -1;
      if ( v83 >= 0x10 )
        j__free(Block);
      v83 = 15;
      v82 = 0;
      LOBYTE(Block) = 0;
    }
    else
    {
      if ( *((uint32_t *)this + 96) < 0x10u )
        v56 = this + 364;
      else
        v56 = *((char **)this + 91);
      v57 = *(uint32_t *)dword_8F84E0;
      v58 = sub_41ACF0(Srcd);
      v59 = (*(int (**)(int, const char *, ...))(v57 + 12))(dword_8F84E0, "%s%s", v56, v58);
      sub_4B52F0(v59);
    }
  }
  for ( Srce = (char *)v86[218]; Srce != (char *)v86[219]; Srce += 4 )
  {
    if ( strcmp((const char *)sub_41ACF0(Srce), szPassword) == 0 )
    {
      v83 = 15;
      v82 = 0;
      LOBYTE(Block) = 0;
      v87 = 12;
      sub_4A3450(v80);
      v87 = 13;
      sub_4B52F0(v80);
      v87 = -1;
      if ( v83 >= 0x10 )
        j__free(Block);
      v83 = 15;
      v82 = 0;
      LOBYTE(Block) = 0;
    }
    else
    {
      if ( *((uint32_t *)this + 96) < 0x10u )
        v60 = this + 364;
      else
        v60 = *((char **)this + 91);
      v61 = *(uint32_t *)dword_8F84E0;
      v62 = sub_41ACF0(Srce);
      v63 = (*(int (**)(int, const char *, ...))(v61 + 12))(dword_8F84E0, "%s%s", v60, v62);
      sub_4B52F0(v63);
    }
  }
  v64 = v86;
  v79 = (int)(v86 + 221);
  v65 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this);
  sub_4ED3F0(v65 + 60, v79);
  v66 = this + 7824;
  v67 = v64 + 239;
  for ( Srcf = 29; Srcf != 0; --Srcf )
  {
    sub_41DC80(v67);
    v67 += 4;
    v66 += 16;
  }
  *(uint32_t *)(*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) = a3;
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  *((uint32_t *)this + 162) |= 1u;
  v68 = (int *)operator new(0x58u);
  v69 = v68;
  v87 = 14;
  if ( v68 != nullptr )
  {
    *v68 = (int)&IRDAppendage::`vftable';
    sub_4B0D60((uint8_t *)v68 + 4);
    LOBYTE(v87) = 15;
    sub_5F6610(v69);
    sub_5F6750(v69);
    LOBYTE(v87) = 16;
    *v69 = (int)&CNSpeedControl::`vftable';
    sub_5FE160(v69);
    nullsub_3(v69);
    v70 = v69;
  }
  else
  {
    v70 = nullptr;
  }
  *((uint32_t *)this + 1931) = v70;
  v71 = *v70;
  v87 = -1;
  (*(void (/*thiscall*/ **)(int *, char *, char *, uint32_t, uint32_t, uint32_t, int))(v71 + 56))(v70, this, this, 0, 0, 0, -1);
  v72 = (int *)operator new(0x60u);
  v73 = v72;
  v87 = 17;
  if ( v72 != nullptr )
  {
    *v72 = (int)&IRDAppendage::`vftable';
    sub_4B0D60((uint8_t *)v72 + 4);
    LOBYTE(v87) = 18;
    sub_5F6610(v73);
    sub_5F6750(v73);
    LOBYTE(v87) = 19;
    *v73 = (int)&CNMovementController::`vftable';
    nullsub_3(v73);
    nullsub_3(v73);
    v74 = v73;
  }
  else
  {
    v74 = nullptr;
  }
  *((uint32_t *)this + 1932) = v74;
  v75 = *v74;
  v87 = -1;
  result = (*(int (/*thiscall*/ **)(int *, char *, char *, uint32_t, uint32_t, uint32_t, int))(v75 + 56))(
             v74,
             this,
             this,
             0,
             0,
             0,
             -1);
  *((uint32_t *)this + 1837) = 100;
  qmemcpy(this + 8368, unk_6F8B68, 104);
  for ( i = 0; ; ++i )
  {
    v77 = *((uint32_t *)this + 83);
    if ( v77 == 0 )
      break;
    result = (*((uint32_t *)this + 84) - v77) >> 2;
    if ( i >= result )
      break;
    result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 464))(this, *(uint32_t *)(v77 + 4 * i));
  }
  return result;
}


// ------------------------------------------------------------
// 0x4E3360 sub_4E3360
// ------------------------------------------------------------
int /*thiscall*/ sub_4E3360(int this)
{
  void *v2; // eax
  void **v3; // edi

  if ( *(uint32_t *)(this + 7820) != 0 )
    j__free(*(void **)(this + 7820));
  v2 = *(void **)(this + 8360);
  *(uint32_t *)(this + 7820) = 0;
  if ( v2 != nullptr )
    j__free(v2);
  v3 = *(void ***)(this + 8364);
  *(uint32_t *)(this + 8360) = 0;
  if ( v3 != nullptr )
  {
    sub_42AF90(v3);
    sub_657740(v3, 228);
  }
  *(uint32_t *)(this + 8364) = 0;
  return --dword_9A05D4;
}



// ------------------------------------------------------------
// 0x4E33D0 sub_4E33D0
// ------------------------------------------------------------
void /*userpurge*/ sub_4E33D0(int *a1@<ecx>, int a2@<ebx>, int ArgList, int a4, float a5, float a6)
{
  int v7; // edi
  uint32_t *v8; // edi
  uint32_t *v9; // eax
  int v10; // ebx
  int v11; // eax
  void *v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int *v19; // edi
  int v20; // ebx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // [esp-10h] [ebp-30h]
  int v25; // [esp-Ch] [ebp-2Ch]
  void *v27; // [esp+Ch] [ebp-14h]
  int v28; // [esp+10h] [ebp-10h]
  float v29; // [esp+2Ch] [ebp+Ch]

  v7 = a1[1639];
  v28 = v7;
  if ( v7 != 11 || ArgList == 12 )
  {
    switch ( v7 )
    {
      case 2:
        sub_4D83E0(0, 0);
        goto LABEL_11;
      case 4:
        if ( ArgList == 1 )
        {
          sub_4DB200(28, -1);
          (*(void (/*thiscall*/ **)(int *))(*a1 + 1068))(a1);
        }
        goto LABEL_11;
      case 5:
        v8 = *(uint32_t **)(*(uint32_t *)(a1[29] + 132) + 44);
        v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*a1 + 340))(a1);
        off_77F3FC(aCriticalErrorI, ArgList, *v9, *v8);
        return;
      case 8:
        if ( *((uint8_t *)a1 + 7559) == 1 )
          sub_4D93D0(a1);
        goto LABEL_11;
      case 10:
        a1[2072] = -1;
        goto LABEL_11;
      default:
LABEL_11:
        v10 = a4;
        switch ( ArgList )
        {
          case 3:
            sub_4DB200(21, -1);
            break;
          case 5:
            sub_4DB200(22, -1);
            v12 = **(void ***)(a4 + 4);
            v27 = v12;
            if ( *(uint32_t *)(dword_8F7A24 + 244) == 2 )
            {
              a1[1942] = 1000;
            }
            else
            {
              v13 = (*(int (/*thiscall*/ **)(int *))(*a1 + 740))(a1);
              v14 = (*(int (/*thiscall*/ **)(int *))(*a1 + 52))(a1);
              srand(v14 * v13);
              v15 = rand();
              v10 = a4;
              a1[1942] = sub_423A80(100, 250, v15 % 101, 100);
            }
            if ( v12 != nullptr )
            {
              if ( *(uint32_t *)(dword_8F7A24 + 244) != 2 && a1[1822] == 0 )
              {
                v16 = ~a1[1824];
                if ( operator new(0x148u) != nullptr )
                {
                  v25 = a1[1942];
                  v24 = a1[1823];
                  v17 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 672))(a1, 3);
                  v18 = sub_4B0D20(v17);
                  v19 = (int *)sub_4DF0C0(v27, v18, v24, v25, v16);
                }
                else
                {
                  v19 = nullptr;
                }
                sub_45FE80(a1[29], (int)v19, 2, 0, (int)v19, (int)a1, 0);
                v20 = *v19;
                v21 = (*(int (/*thiscall*/ **)(int *))(*a1 + 128))(a1);
                v22 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 124))(a1, a1[40] / 2 + v21);
                v23 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 120))(a1, v22);
                (*(void (/*thiscall*/ **)(int *, int))(v20 + 112))(v19, v23);
                v10 = a4;
              }
              if ( *(uint32_t *)(dword_8F7A24 + 244) != 2
                && (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 1020))(a1) == 0 )
              {
                (*(void (/*thiscall*/ **)(int *, int, int, int))(*a1 + 260))(a1, 1, 5, -1);
              }
            }
            else
            {
              (*(void (/*thiscall*/ **)(int *))(*a1 + 1256))(a1);
            }
            v7 = v28;
            break;
          case 8:
            if ( *((uint8_t *)a1 + 7559) == 1 )
              sub_4D9360(a1);
            sub_4DB200(**(uint32_t **)(a4 + 4), -1);
            break;
          case 10:
            a1[2072] = **(uint32_t **)(a4 + 4);
            break;
          case 13:
            if ( a1[30] == a1[1540] )
              LOBYTE(a6) = 0;
            else
              (*(void (/*thiscall*/ **)(int *, int))(*a1 + 196))(a1, a1[1540]);
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*a1 + 876))(
              a1,
              0,
              0,
              0,
              0,
              0,
              0,
              a2);
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 876))(
              a1,
              1,
              0,
              0,
              0,
              0,
              0);
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*a1 + 888))(a1, 0, 0, 1000, 1000);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*a1 + 596))(a1, 0);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*a1 + 604))(a1, 0);
            (*(void (/*thiscall*/ **)(int *, int, int))(*a1 + 612))(a1, 1, 2);
            if ( a1[2091] == 0 )
            {
              if ( sub_42FCB0(228) != 0 )
                v11 = sub_431860((char)"Monster/Common/Animation/Unsummon.ani", 1);
              else
                v11 = 0;
              a1[2091] = v11;
            }
            v29 = (double)(*(int (/*thiscall*/ **)(int *))(*a1 + 192))(a1) * 0.0080000004;
            sub_4920E0((uint32_t *)a1[2091], v29, v29);
            (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, int, uint32_t))(*a1 + 204))(
              a1,
              1,
              a1[2091],
              0,
              0,
              1,
              0);
            break;
          default:
            break;
        }
        sub_58E920(a1, ArgList, v10, a5, a6);
        if ( v7 == 3 || v7 == 8 )
          (*(void (/*thiscall*/ **)(int *))(*a1 + 1240))(a1);
        break;
    }
  }
}


// ------------------------------------------------------------
// 0x4E3820 sub_4E3820
// ------------------------------------------------------------
int /*thiscall*/ sub_4E3820(int *this, float *a2)
{
  int v3; // edi
  char *v4; // eax
  int v5; // esi

  v3 = 0;
  if ( sub_42FCB0(228) != 0 )
    v3 = sub_431860((char)"Common/CommonEffect/Animation/LastStrikeForKillBoss.ani", 1);
  v4 = (char *)sub_44B6C0(284);
  v5 = (int)v4;
  if ( v4 != nullptr )
  {
    sub_44E0D0(v4, v3, 1);
    *(uint32_t *)v5 = &CNRDPooledObject::`vftable';
  }
  else
  {
    v5 = 0;
  }
  sub_45FE80(*(this + 29), v3, 2, 0, v5, (int)this, 0);
  return (*(int (/*fastcall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v5 + 112))(
           v5,
           (uint64_t)*a2 >> 32,
           (uint64_t)*a2,
           (uint64_t)a2[1],
           (uint64_t)a2[2]);
}



// ------------------------------------------------------------
// 0x4E38F0 sub_4E38F0
// ------------------------------------------------------------
char /*thiscall*/ sub_4E38F0(int *this, int a2, int a3, int a4)
{
  unsigned int v4; // edi
  int v6; // eax
  int v7; // edx
  int v8; // ebx
  int v9; // ebx
  int v10; // ebx
  int *v11; // eax
  int v12; // eax
  int v13; // ebx
  int v14; // ecx
  int v15; // eax
  char *v16; // ebx
  int v17; // edx
  int **v18; // eax
  int **v19; // eax
  int v20; // eax
  int v21; // ecx
  double v22; // st7
  char *v23; // eax
  int v24; // edi
  int v25; // eax
  int v26; // ebx
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // edx
  unsigned int v33; // edi
  int v34; // edx
  unsigned int v35; // edi
  void *v36; // eax
  int v37; // edi
  int v38; // eax
  int v39; // edi
  int v40; // eax
  uint32_t *v41; // eax
  uint64_t v42; // rax
  int v43; // edi
  int v44; // ebx
  int64_t v45; // rax
  int v46; // ecx
  unsigned int v47; // edi
  int v48; // eax
  int v49; // edx
  const char *v50; // edi
  const char *v51; // ecx
  const char *v52; // eax
  size_t *v53; // eax
  int v54; // ebx
  unsigned int v55; // edi
  uint64_t v56; // rax
  int v57; // edi
  int v58; // eax
  int v59; // eax
  int *v60; // eax
  int v61; // edx
  unsigned int v62; // edi
  uint64_t v63; // rax
  unsigned int v64; // edi
  unsigned int v65; // edi
  uint64_t v66; // rax
  unsigned int v67; // edi
  uint64_t v68; // rax
  unsigned int v69; // edi
  void *v70; // eax
  int v71; // edi
  int v72; // eax
  void *v73; // eax
  int v74; // edi
  int v75; // eax
  void *v76; // eax
  int v77; // edi
  int v78; // eax
  void *v79; // eax
  int v80; // edi
  int v81; // eax
  int v82; // eax
  int *v83; // esi
  int v84; // eax
  int v85; // eax
  const char *v87; // [esp-4h] [ebp-338h]
  uint32_t v88[5]; // [esp+Ch] [ebp-328h]
  uint32_t v89[4]; // [esp+20h] [ebp-314h]
  char *Format[4]; // [esp+30h] [ebp-304h]
  uint32_t v91[4]; // [esp+40h] [ebp-2F4h]
  uint32_t v92[4]; // [esp+50h] [ebp-2E4h]
  uint32_t v93[4]; // [esp+60h] [ebp-2D4h]
  uint32_t v94[4]; // [esp+70h] [ebp-2C4h]
  uint32_t v95[4]; // [esp+80h] [ebp-2B4h]
  float v96; // [esp+90h] [ebp-2A4h]
  float v97; // [esp+94h] [ebp-2A0h]
  void *v98; // [esp+98h] [ebp-29Ch] BYREF
  float v99; // [esp+9Ch] [ebp-298h]
  void *Block; // [esp+A0h] [ebp-294h]
  char Buffer[512]; // [esp+A4h] [ebp-290h] BYREF
  char Src[128]; // [esp+2A4h] [ebp-90h] BYREF
  int v103; // [esp+324h] [ebp-10h]
  int v104; // [esp+330h] [ebp-4h]
  unsigned int v105; // [esp+33Ch] [ebp+8h]
  float v106; // [esp+33Ch] [ebp+8h]
  int v107; // [esp+344h] [ebp+10h]
  int v108; // [esp+344h] [ebp+10h]

  v4 = 0;
  v103 = dword_796E50;
  v6 = *this;
  v92[0] = 0;
  v92[1] = 10;
  v92[2] = 20;
  v92[3] = 0;
  v91[0] = 0;
  v91[1] = 1050253722;
  v91[2] = 1056964608;
  v91[3] = 0;
  v93[0] = 0;
  v93[1] = 1069547520;
  v93[2] = 0x40000000;
  v93[3] = 0;
  v94[0] = 0;
  v94[1] = 1069547520;
  v94[2] = 1077936128;
  v94[3] = 0;
  v98 = (void *)(*(uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(v6 + 672))(this, 3) - 1);
  v7 = *this;
  v98 = (void *)(uint64_t)((double)(int)v98 * 0.2 + 2.0);
  v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 128))(this);
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) + v8;
  v10 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v9;
  v105 = v10 + a2 + (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
  srand(v105);
  *(this + 1943) = a4;
  if ( (unsigned int)*(this + 1794) < 0x10 )
    v11 = this + 1789;
  else
    v11 = (int *)*(this + 1789);
  v12 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F84C4 + 4))(dword_8F84C4, v11);
  v13 = v12;
  v14 = *(uint32_t *)(v12 + 1424);
  if ( v14 != 0 && (*(uint32_t *)(v12 + 1428) - v14) >> 2 != 0 )
  {
    v15 = *(uint32_t *)(v12 + 1424);
    if ( v15 != 0 )
      v4 = (*(uint32_t *)(v13 + 1428) - v15) >> 2;
    *(this + 2148) = *(uint32_t *)(*(uint32_t *)(v13 + 1424) + 4 * (rand() % v4));
  }
  else
  {
    *(this + 2148) = rand() % 4 + 1;
  }
  v16 = nullptr;
  v88[0] = "fire";
  v88[1] = "water";
  v88[2] = "dark";
  v88[3] = "light";
  v88[4] = "none";
  Format[0] = "Monster/Common/Animation/Champion/%sBottomB.ani";
  Format[1] = "Monster/Common/Animation/Champion/%sBottomF.ani";
  Format[2] = "Monster/Common/Animation/Champion/%sBackB.ani";
  Format[3] = "Monster/Common/Animation/Champion/%sBackF.ani";
  v95[0] = 0;
  v95[1] = 0;
  v95[2] = -1;
  v95[3] = 1;
  v89[0] = 2;
  v89[1] = 2;
  v89[2] = 1;
  v89[3] = 1;
  for ( Block = nullptr; (int)Block < 16; Block = (char *)Block + 4 )
  {
    sprintf(Buffer, *(const char *const *)((char *)Format + (uint32_t)v16), v88[*(this + 2148)]);
    v99 = COERCE_FLOAT(sub_42FCB0(228));
    v104 = 0;
    if ( v99 == 0.0 )
      v99 = 0.0;
    else
      v99 = COERCE_FLOAT(sub_431860((char)Buffer, 1));
    v17 = *this;
    v104 = -1;
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(v17 + 688))(this) != 0 )
    {
      v18 = (int **)(*(int (/*thiscall*/ **)(int *))(*this + 688))(this);
      if ( sub_4924C0(*v18, 0) != 0 )
      {
        v19 = (int **)(*(int (/*thiscall*/ **)(int *))(*this + 688))(this);
        v20 = sub_4924C0(*v19, 0);
        v21 = *(uint32_t *)v20;
        if ( *(uint32_t *)v20 != 0 )
        {
          v22 = (double)*(unsigned int *)(v21 + 20);
          v96 = *(float *)(v21 + 24);
          v97 = v22 * 1.5 * *(float *)(v20 + 20) * 0.0052910051;
          v96 = (double)LODWORD(v96) * 1.5 * *(float *)(v20 + 24) * 0.0047846888;
          if ( v97 > 1.0 )
            v97 = 1.0;
          if ( v96 > 1.0 )
            v96 = 1.0;
          sub_4920E0((uint32_t *)LODWORD(v99), v97, v96);
        }
      }
    }
    v23 = (char *)sub_44B6C0(284);
    v24 = (int)v23;
    v97 = *(float *)&v23;
    v104 = 1;
    if ( v23 != nullptr )
    {
      sub_44E0D0(v23, SLODWORD(v99), 1);
      *(uint32_t *)v24 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v24 = 0;
    }
    v25 = *(uint32_t *)v24;
    v104 = -1;
    (*(void (/*thiscall*/ **)(int))(v25 + 72))(v24);
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v24 + 36))(v24) + 8) = *(uint32_t *)((char *)v89 + (uint32_t)v16);
    sub_45FE80(*(this + 29), v24, 2, 0, v24, (int)this, 0);
    v26 = *(uint32_t *)v24;
    v27 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v28 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v27);
    v29 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, *(uint32_t *)((char *)v95 + (uint32_t)Block) + v28);
    (*(void (/*thiscall*/ **)(int, int))(v26 + 112))(v24, v29);
    v30 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)v24 + 60))(v24, this);
    sub_4A06D0(v30, 2);
    v16 = (char *)Block + 4;
  }
  v31 = *(this + 2148);
  if ( v31 >= 0 )
  {
    if ( v31 <= 3 )
    {
      v36 = operator new(0x84u);
      Block = v36;
      v104 = 2;
      if ( v36 != nullptr )
        v37 = sub_4DF1B0((int)v36, v92[a4], *(this + 2148), 0, -1);
      else
        v37 = 0;
      v38 = *(uint32_t *)v37;
      v104 = -1;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v38 + 64))(v37) + 40) = 0;
      (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v37 + 56))(
        v37,
        this,
        this,
        0,
        0,
        0,
        -1);
      v39 = *(this + 2148);
      v40 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0);
      v41 = (uint32_t *)sub_41A5E0(v40 + 14 * v39 + 172);
      Block = (void *)(150 - (uint32_t)v41);
      v99 = *(float *)&v41;
      v42 = (uint64_t)((double)(150 - (int)v41) * *(float *)&v91[a4] + (double)(int)v41);
      v43 = *(this + 2148);
      v44 = v42;
      v45 = ((int64_t (/*fastcall*/ *)(int *, uint32_t, uint32_t))*(uint32_t *)(*this + 672))(this, HIDWORD(v42), 0);
      sub_41A590(v45 + 14 * v43 + 172, SHIDWORD(v45), v44);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
    }
    else if ( v31 == 4 )
    {
      v32 = *this;
      v99 = *(float *)&v93[a4];
      v33 = (*(int (/*thiscall*/ **)(int *, uint32_t))(v32 + 672))(this, 0) + 60;
      Block = (void *)sub_41A5E0(v33);
      sub_41A590(v33, (uint64_t)((double)(int)Block * v99) >> 32, (uint64_t)((double)(int)Block * v99));
      v34 = *this;
      v99 = *(float *)&v93[a4];
      v35 = (*(int (/*thiscall*/ **)(int *, uint32_t))(v34 + 672))(this, 0) + 88;
      Block = (void *)sub_41A5E0(v35);
      sub_41A590(v35, (uint64_t)((double)(int)Block * v99) >> 32, (uint64_t)((double)(int)Block * v99));
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
    }
  }
  v46 = *(uint32_t *)(a3 + 4);
  if ( v46 != 0 && (*(uint32_t *)(a3 + 8) - v46) >> 2 != 0 )
    sub_4E1560(this, a3, &v98);
  else
    sub_4E14E0(this, v105, (int *)&v98);
  v47 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 466;
  v48 = sub_41A5E0(v47);
  sub_41A590(v47, v49, v48 + 50);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
  if ( *(this + 1943) == 2 )
    v50 = (const char *)sub_422E70(1605);
  else
    v50 = szPassword;
  if ( (unsigned int)*(this + 78) < 0x10 )
    v51 = (const char *)(this + 73);
  else
    v51 = (const char *)*(this + 73);
  v87 = v51;
  v52 = (const char *)sub_422E70(*(this + 2148) + 1600);
  sprintf(Src, "%s%s%s", v50, v52, v87);
  v53 = (size_t *)((*(int (/*thiscall*/ **)(int *))(*this + 340))(this) + 4);
  sub_4015C0(v53, Src, strlen(Src));
  v54 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);
  v106 = *(float *)&v94[a4];
  v55 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 4;
  v56 = (uint64_t)((double)sub_41A5E0(v55) * v106);
  sub_41A590(v55, SHIDWORD(v56), v56);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
  v57 = *this;
  v58 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 740))(this, 0, 1);
  (*(void (/*thiscall*/ **)(int *, int))(v57 + 732))(this, v58);
  v59 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);
  off_77F3FC(aApplychamp, v54, v59);
  if ( *(this + 1943) == 2 )
  {
    v98 = operator new(0x84u);
    v104 = 3;
    if ( v98 != nullptr )
      v60 = (int *)sub_5FE2C0(1120403456);
    else
      v60 = nullptr;
    v61 = *v60;
    v104 = -1;
    (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t, int))(v61 + 56))(v60, this, this, 0, 0, 0, -1);
  }
  if ( sub_4DB0E0(this, 196621) != 0 )
  {
    v62 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 816;
    v63 = (uint64_t)((double)sub_41A5E0(v62) * 1.5);
    sub_41A590(v62, SHIDWORD(v63), v63);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
  }
  if ( sub_4DB0E0(this, 196622) != 0 )
  {
    v64 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 844;
    v107 = sub_41A5E0(v64);
    sub_41A590(
      v64,
      (uint64_t)((double)v107 + (double)v107) >> 32,
      (uint64_t)((double)v107 + (double)v107));
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
  }
  if ( sub_4DB0E0(this, 196354) != 0 )
  {
    v65 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 88;
    v66 = (uint64_t)((double)sub_41A5E0(v65) * 2.5);
    sub_41A590(v65, SHIDWORD(v66), v66);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
  }
  if ( sub_4DB0E0(this, 196355) != 0 )
  {
    v67 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 144;
    v68 = (uint64_t)((double)sub_41A5E0(v67) * 2.5);
    sub_41A590(v67, SHIDWORD(v68), v68);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
  }
  if ( sub_4DB0E0(this, 262159) != 0 )
  {
    v69 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 900;
    v108 = sub_41A5E0(v69);
    sub_41A590(
      v69,
      (uint64_t)((double)v108 + (double)v108) >> 32,
      (uint64_t)((double)v108 + (double)v108));
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
  }
  if ( sub_4DB0E0(this, 261641) != 0 )
  {
    v70 = operator new(0x84u);
    v98 = v70;
    v104 = 4;
    if ( v70 != nullptr )
      v71 = sub_4DF1B0((int)v70, 5, 0, 0, -1);
    else
      v71 = 0;
    v72 = *(uint32_t *)v71;
    v104 = -1;
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v72 + 64))(v71) + 40) = 0;
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v71 + 56))(
      v71,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  if ( sub_4DB0E0(this, 261642) != 0 )
  {
    v73 = operator new(0x84u);
    v98 = v73;
    v104 = 5;
    if ( v73 != nullptr )
      v74 = sub_4DF1B0((int)v73, 5, 1, 0, -1);
    else
      v74 = 0;
    v75 = *(uint32_t *)v74;
    v104 = -1;
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v75 + 64))(v74) + 40) = 0;
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v74 + 56))(
      v74,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  if ( sub_4DB0E0(this, 261643) != 0 )
  {
    v76 = operator new(0x84u);
    v98 = v76;
    v104 = 6;
    if ( v76 != nullptr )
      v77 = sub_4DF1B0((int)v76, 5, 3, 0, -1);
    else
      v77 = 0;
    v78 = *(uint32_t *)v77;
    v104 = -1;
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v78 + 64))(v77) + 40) = 0;
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v77 + 56))(
      v77,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  if ( sub_4DB0E0(this, 261644) != 0 )
  {
    v79 = operator new(0x84u);
    v98 = v79;
    v104 = 7;
    if ( v79 != nullptr )
      v80 = sub_4DF1B0((int)v79, 5, 2, 0, -1);
    else
      v80 = 0;
    v81 = *(uint32_t *)v80;
    v104 = -1;
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v81 + 64))(v80) + 40) = 0;
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v80 + 56))(
      v80,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  LOBYTE(v82) = sub_4DB0E0(this, 262160);
  if ( (uint8_t)v82 != 0 )
  {
    v83 = (int *)*(this + 1545);
    if ( v83 != nullptr )
    {
      v84 = v83[11];
      if ( v84 != 0 )
        v85 = (v83[12] - v84) / 88;
      else
        v85 = 0;
      v82 = sub_4924C0(v83, v85 - 1);
      *(uint32_t *)(v82 + 48) = 0;
    }
  }
  return v82;
}


// ============================================================
// 【分区 B】HP 受击处理器 + 攻方表现载荷 + 动作数据包（0x4E4430 - 0x4E5030）
//   ★ 本区是研究 20 §8「双向卡肉」与 P35「HP 受击/Boss 终局」的落点。
// ============================================================

// ------------------------------------------------------------
// 0x4E4430 sub_4E4430 —— ★ HP 受击处理器（含 Boss 终局；研究 P35 第 31 轮定案）
// 结构：取 vt+684（HP 读取）与 a2（新 HP）比较，不等时算 v9 = 旧HP − 新HP（本次伤害）。
//   ★ Boss/精怪终局分支（a2 == 0 即"归零 = 死亡"）：
//     sub_4DB0E0(131091) 持有该标签（研究 P35：131091 = 死亡终局技能/被动 id）
//     且 this 的 vt+80 容器 +153 字节为 0（非演出中）→
//       v7 = vt+740（最大 HP，作为"最终一击伤害值"）
//       vt+308 门（本地玩家对象）→ vt+580(this, 48001, 3, …, 4, …) 发包
//       → sub_4DE0E0(131091) 移除标签 + sub_49C970(8,0,0)/sub_49C5F0(9,0,0,2000) 表现
//   ★ 落地：sub_4D5900(v7, a3, a4)（HP setter 家族）
//   ★ 击杀归属：a3（攻击者）vt+576 车主非空且 v9 > 0 → sub_4DEE20(a3, v9) 记录伤害
//   ★ 终极演出（PVP 场景 3 且 this 大状态 == 3）：vt+724 门 → 全局计数 dword_9A05CC 递减，
//     归零时：+153 = 1 演出标志 + sub_424BB0(6000, 30, …)（★ 6 秒三相位长震，
//     P35 定案 "Boss 终局 = 6 秒三相位长震"）+ sub_432EA0("R_STAGE_FINALE") BGM 切换
//     + sub_4E3820 表现 + sub_4DC4D0 + vt+604(0) 死亡无敌 + sub_426820(…, 4, 0) 播报。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E4430(char *this, int a2, int a3, char a4)
{
  int v5; // eax
  int result; // eax
  int v7; // edi
  int v8; // eax
  int v9; // ebx

  v5 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 684))(this);
  result = sub_41A5E0(v5);
  v7 = a2;
  if ( result != a2 )
  {
    v8 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 684))(this);
    v9 = sub_41A5E0(v8) - a2;
    if ( a2 == 0
      && (uint8_t)sub_4DB0E0(131091) != 0
      && *(uint8_t *)((*(int (**)(void))(*(uint32_t *)this + 80))() + 153) == 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 740))(this);
      if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
          this,
          48001,
          3,
          0,
          0,
          0,
          0,
          0,
          4,
          0,
          0,
          0);
      sub_4DE0E0(131091);
      sub_49C970(8, 0, 0);
      sub_49C5F0(9, 0, 0, 2000);
    }
    sub_4D5900(v7, a3, a4);
    if ( a3 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 576))(a3) != 0 && v9 > 0 )
      sub_4DEE20(a3, v9);
    result = 3;
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 && *((uint32_t *)this + 1943) == 3 )
    {
      result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 724))(this);
      if ( (uint8_t)result != 0 )
      {
        off_77F3FC((char *)&byte_6F9AA4, dword_9A05CC[0]);
        result = --*(uint32_t *)dword_9A05CC;
        if ( *(int *)dword_9A05CC <= 0 )
        {
          *(uint8_t *)(*((uint32_t *)this + 29) + 153) = 1;
          sub_424BB0(6000, 30, *((uint32_t *)this + 1814) == dword_8F7C04);
          sub_432EA0("R_STAGE_FINALE", -1, 0, 0);
          sub_4E3820(this + 7777);
          sub_4DC4D0(this);
          (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 604))(this, 0);
          return sub_426820(*(uint32_t *)(*((uint32_t *)this + 29) + 132), 4, 0);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E4610 sub_4E4610 —— ★ 距上次受击毫秒（研究 §15 第 15 轮定案：vt+632）
// `this+1673 != −1` 时返回 当前时钟(this+16) − this+1673；否则 −1。
// 研究 §15 更正记录："vt+632 = 距上次受击毫秒（更正'连击数'误读）"——
// 写入点 = 0x4D9F20 / 0x4D8730（把时钟当前时刻存入 this+1673）。
// 消费点 = 连击/受击窗口判定（研究 §9 连击 1500ms 窗口的读侧之一）、0x4E5C10 等。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E4610(uint32_t *this)
{
  int result; // eax

  result = -1;
  if ( *(this + 1673) != -1 )
    return sub_699000((int)(this + 16)) - *(this + 1673);
  return result;
}



// ------------------------------------------------------------
// 0x4E4630 sub_4E4630 —— ★ 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
// 语义：true = "是敌人/不同阵营"。两段：
//   ① 若场景 == 6（战场）且双方 vt+376（阵营/队伍号）均落在 0..11 →
//      沿车主链 vt+576 上溯（条件 529 时取 v4[2088]，即"召唤主/变形主"链）跳过非战斗宿主；
//      终宿主条件 273（受击态）成立且 sub_4B09A0(v4) == 0 → 返回 **false**（同阵营判定为友）
//   ② 兜底：`this->vt+376 != a2->vt+376`（阵营号不同 = 敌人）
// 研究 §8 定案："vt+360 = 敌我关系判定（阵营比较 vs this+544）—— 攻方冻结豁免：
// 打队友不卡肉"；本函数是 vt+360 实现族的辅助（PVP/战场场景特化 + 召唤主上溯）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4E4630(void *this, int a2)
{
  uint32_t *v4; // esi
  int v5; // esi

  if ( a2 == 0 )
    return false;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 6
    && (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 376))(this) >= 0
    && (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 376))(this) <= 11
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2) >= 0
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2) <= 11 )
  {
    v4 = (uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 576))(this);
    if ( v4 != nullptr )
    {
      while ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v4 + 40))(v4, 529) != 0 )
      {
        v4 = (uint32_t *)v4[2088];
        if ( v4 == nullptr )
          goto LABEL_11;
      }
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v4 + 40))(v4, 273) != 0 && sub_4B09A0(v4) == 0 )
        return false;
    }
  }
LABEL_11:
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2);
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 376))(this) != v5;
}



// ------------------------------------------------------------
// 0x4E4710 sub_4E4710 —— ★★ 攻方表现载荷（研究 20 §8 全文定案；★ 双向卡肉）
// this = 攻击者，a2 = 受击者，a3 = 命中盒，a4 = 格挡/暴击位。
// 反编译体与 §8 定案清单逐条对应（以 a2 为"受方"，this 为"攻方"）：
//   ① ★★★ 三重豁免门 + 攻方自我冻结：
//        `(受方 vt+308 != 0) || (攻方 vt+308 == 0) || (攻方 vt+360(攻,受) == 0)`
//        —— 研究 §8 定案："受方是玩家对象 或 攻方非玩家对象 或 受方是敌人"
//        等价于 **打敌人才卡肉、打队友不卡**；
//        v6 = this+130（= +520 字节偏移 → word 下标 130 = 字节 +520 ★ 攻方自身卡肉时长）
//        主状态 v7 = this+50（= 字节 +200）∈ {0} 或 {1 且 vt+248 剩余硬直 < v6} →
//        **vt+228(this, 1, v6, 0)** = 攻击者冻结自己 —— 与受击者同一入口、同一延长逻辑
//   ② vt+356(this, a2) —— 攻方自身命中特效（记录当前命中目标，研究 §1.2 vt+356）
//   ③ 无表现类判定：a2 条件 529 且 a2+7148 == 22（v18）；vt+648 伤害类型 → 3 或
//      （2 且伤 <= 0）→ v8 = 1（无表现）—— 研究 §8 "kind==3 或（==2 且伤≤0）= 无表现类"
//   ④ 可表现门：(this+404 标志 或 this+388 float > 0) 且 RTDynamicCast(受→IRDActiveObject)
//      成功 → v12 = 受方 vt+128(X) > 0 且 vt+840 大状态 == 4（**= 本次为击杀**）
//   ⑤ 本地玩家出手门：`dword_8F7C04 == 攻方 vt+576` 且 this+116 != 0 →
//      **sub_428050(v12, a4, a3)** = ★ 连击/击杀处理（研究 §9；宿主 ECX = 技能对象+132）
//   ⑥ 技能钩子：技能对象(this+116 → +132 → +52) == 攻方车主 → sub_4684F0(受)
//      （研究 §8：目标 HUD 更新，怪物血条宽 = 等级比 × 160/300、上限 475px）
//   ⑦ a4 == 0 → vt+540(this, 受) 攻方收尾（命中语音，研究 §1.2/§8）
// 研究 §8 第 10 轮补充的豁免门完整语义：投射物/使魔不卡肉的机制不在门上，
// 而是它们 this+520 基础值为 0（vt+1184 取空，见 sub_4AF8E0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E4710(int *this, uint32_t *a2, int a3, char a4)
{
  int v6; // ebx
  int v7; // eax
  char v8; // bl
  int v9; // edx
  int v10; // eax
  int v11; // ecx
  BOOL v12; // ebx
  int v13; // eax
  int v14; // ebx
  int v16; // [esp+Ch] [ebp-8h]
  int v17; // [esp+10h] [ebp-4h] BYREF
  bool v18; // [esp+1Fh] [ebp+Bh]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a2 + 308))(a2) != 0
    || (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 0
    || (*(uint8_t (/*thiscall*/ **)(int *, uint32_t *))(*this + 360))(this, a2) == 0 )
  {
    v6 = *(this + 130);
    if ( v6 > 0 )
    {
      v7 = *(this + 50);
      if ( v7 == 0 || v7 == 1 && (*(int (/*thiscall*/ **)(int *))(*this + 248))(this) < v6 )
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(*this + 228))(this, 1, v6, 0);
    }
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t *))(*this + 356))(this, a2);
  v18 = false;
  v8 = 0;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 529) != 0 )
    v18 = a2[1787] == 22;
  v9 = *a2;
  v17 = 0;
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, int *, int *))(v9 + 648))(a2, &v17, this);
  if ( v10 == 3 || v10 == 2 && v17 <= 0 )
    v8 = 1;
  v11 = __RTDynamicCast(
          (int)a2,
          0,
          &IRDCollisionObject `RTTI Type Descriptor',
          &IRDActiveObject `RTTI Type Descriptor',
          0);
  v16 = v11;
  if ( v8 == 0 && !v18 && (*((uint8_t *)this + 404) != 0 || *((float *)this + 97) > 0.0) && v11 != 0 )
  {
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 128))(v11) > 0
       && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 840))(v16) == 4;
    if ( dword_8F7C04 == (*(int (/*thiscall*/ **)(int *))(*this + 576))(this) && *(this + 29) != 0 )
      sub_428050(v12, a4, a3);
    v13 = *(this + 29);
    if ( v13 != 0 )
    {
      v14 = *(uint32_t *)(*(uint32_t *)(v13 + 132) + 52);
      if ( v14 == (*(int (/*thiscall*/ **)(int *))(*this + 576))(this) )
        sub_4684F0(v16);
    }
  }
  if ( a4 == 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t *))(*this + 540))(this, a2);
  return 0;
}



// ------------------------------------------------------------
// 0x4E48D0 sub_4E48D0 —— ★ 记录最后受击时刻 + 仇人 id（研究 §1.1/§2 字段表定案）
// 由受方回调 vt+516（0x4D4A80）尾调（研究 §1.1："sub_4E48D0（受击者记录最后受击时刻
// this+568 + 仇人 id this+572——击杀归属数据）"）。
// 流程：取 a2（攻击者）attackinfo，须有伤害或反应（+16 != 0 或 float+0 > 0），
// 且 a4 == 0；先把临时 a4 = 100 作为 vt+648 的输出槽调用，结果 a4 > 0 才记录：
//   `this+142 = sub_699000(this+2)`（word 下标 142 = **字节 +568 = 最后受击时刻**）
//   `this+143 = a2->vt+576()`（word 下标 143 = **字节 +572 = 仇人 id（击杀归属）**）
// 🔴 与反编译体字面核对：源码为 `a4 = 100; vt+648(this, &a4, a2); if (a4 > 0)`
//    —— 与 4D71B0 内 `v44 = 100` 的用法同形（vt+648 第二参为"伤害/类型输出槽"）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E48D0(int *this, int a2, int a3, int a4)
{
  int v5; // eax
  int v6; // edx

  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
  if ( (*(uint8_t *)(v5 + 16) != 0 || *(float *)v5 > 0.0) && (uint8_t)a4 == 0 )
  {
    v6 = *this;
    a4 = 100;
    (*(void (/*thiscall*/ **)(int *, int *, int))(v6 + 648))(this, &a4, a2);
    if ( a4 > 0 )
    {
      *(this + 142) = sub_699000((int)(this + 2));
      *(this + 143) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4E4950 sub_4E4950 —— 朝向/位置偏移判定（研究 §1.2 vt+688 骨架的消费侧）
// 流程：备份 vt+28 容器三字段 → vt+112(受, a2, a3, vt+128) 取位 → 清 +108 标志 →
//   sub_45E7D0（取对方对象）→ 若可 RTDynamicCast 到 CNRDPassiveObject 且其属性块 +8 非 0
//   → v9 = false 并回填 *a4 = 对方；否则用 this+28 技能容器 (+132 → +44) 走 sub_48CD70
// 还原备份字段 + +108 = 1。返回 v9（"本次为瞬移/位移类"？【待验证】）。
// 与 0x4D5890（同样调 sub_4E4950）配套使用。
// ------------------------------------------------------------
char /*thiscall*/ sub_4E4950(uint32_t *this, int a2, int a3, int *a4)
{
  uint32_t *v6; // eax
  int v7; // edi
  int v8; // eax
  bool v9; // bl
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // eax
  uint32_t *v14; // eax
  int v15; // [esp+4h] [ebp-Ch]
  int v16; // [esp+8h] [ebp-8h]
  int v17; // [esp+Ch] [ebp-4h]

  if ( a4 != nullptr )
    *a4 = 0;
  if ( *(this + 29) == 0 )
    return 1;
  v6 = (uint32_t *)*(this + 28);
  v7 = *this;
  v15 = v6[1];
  v16 = v6[2];
  v17 = v6[3];
  v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(v7 + 112))(this, a2, a3, v8);
  *(uint8_t *)(*(this + 28) + 108) = 0;
  v9 = true;
  v10 = sub_45E7D0(this);
  v11 = v10;
  if ( v10 != 0 )
  {
    v12 = __RTDynamicCast(
            v10,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &CNRDPassiveObject `RTTI Type Descriptor',
            0);
    if ( v12 == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 672))(v12) + 8) != 0 )
    {
      v9 = false;
      if ( a4 != nullptr )
        *a4 = v11;
    }
  }
  else
  {
    v13 = *(uint32_t *)(*(this + 29) + 132);
    if ( v13 != 0 )
    {
      v14 = *(uint32_t **)(v13 + 44);
      if ( v14 != nullptr )
        v9 = sub_48CD70(v14, (int)this) != 0;
    }
  }
  *(uint32_t *)(*(this + 28) + 4) = v15;
  *(uint32_t *)(*(this + 28) + 8) = v16;
  *(uint32_t *)(*(this + 28) + 12) = v17;
  *(uint8_t *)(*(this + 28) + 108) = 1;
  return v9;
}



// ------------------------------------------------------------
// 0x4E4A50 sub_4E4A50
// ------------------------------------------------------------
int /*usercall*/ sub_4E4A50@<eax>(
        int a1@<edi>,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11)
{
  int v12; // edi
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // esi
  int v21; // eax
  int v22; // eax
  int v23; // esi

  if ( a2 != 0
    && ((*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 316))(a2) != 0
     || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 88))(a2) == 0) )
  {
    return 0xFFFF;
  }
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 21, 2, a1);
  if ( a2 != 0 )
  {
    v12 = *(uint32_t *)dword_8F8520;
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 48))(a2);
    (*(void (/*thiscall*/ **)(int, int))(v12 + 36))(dword_8F8520, v13);
    v14 = *(uint32_t *)dword_8F8520;
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 52))(a2);
    (*(void (/*thiscall*/ **)(int, int))(v14 + 36))(dword_8F8520, v15);
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0xFFFF);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);
  }
  if ( a9 != 0 )
  {
    v16 = *(uint32_t *)dword_8F8520;
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a9 + 48))(a9);
    (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);
    v18 = *(uint32_t *)dword_8F8520;
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a9 + 52))(a9);
    (*(void (/*thiscall*/ **)(int, int))(v18 + 36))(dword_8F8520, v19);
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0xFFFF);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 1);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a3);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, a4);
  v20 = *(uint32_t *)dword_8F8520;
  v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);
  (*(void (/*thiscall*/ **)(int, int))(v20 + 36))(dword_8F8520, v21);
  v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  v23 = sub_460230(*(uint32_t *)(v22 + 104));
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v23);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 0);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, a8);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a5);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a6);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a7);
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 52))(dword_8F8520, a11, a10);
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
  return v23;
}



// ------------------------------------------------------------
// 0x4E4C10 sub_4E4C10
// ------------------------------------------------------------
int /*usercall*/ sub_4E4C10@<eax>(int a1@<edi>, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
  int v9; // esi
  int v11; // edi
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // esi
  int v16; // edi
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // esi
  int v21; // eax
  int v22; // eax
  int v23; // esi
  int v24; // eax

  v9 = a2;
  if ( a2 != 0
    && ((*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 316))(a2) != 0
     || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 88))(v9) == 0) )
  {
    return 0xFFFF;
  }
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 21, 2, a1);
  if ( v9 != 0 )
  {
    v11 = *(uint32_t *)dword_8F8520;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 48))(v9);
    (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
    v13 = *(uint32_t *)dword_8F8520;
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 52))(v9);
    (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0xFFFF);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);
  }
  v15 = a7;
  if ( a7 != 0 )
  {
    v16 = *(uint32_t *)dword_8F8520;
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a7 + 48))(a7);
    (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);
    v18 = *(uint32_t *)dword_8F8520;
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 52))(v15);
    (*(void (/*thiscall*/ **)(int, int))(v18 + 36))(dword_8F8520, v19);
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0xFFFF);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 1);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a3);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, a4);
  v20 = *(uint32_t *)dword_8F8520;
  v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);
  (*(void (/*thiscall*/ **)(int, int))(v20 + 36))(dword_8F8520, v21);
  v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  v23 = sub_460230(*(uint32_t *)(v22 + 104));
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v23);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
  v24 = sub_529A80(&unk_9A0630, &a2);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v24);
  (*(void (/*thiscall*/ **)(int, void *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &unk_9A0630, a2);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, a6);
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 52))(dword_8F8520, a9, a8);
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
  return v23;
}



// ------------------------------------------------------------
// 0x4E4DE0 sub_4E4DE0 —— ★ 位置化动作发布（会话 3 定案：位置化动作）
// 门：vt+316（禁用）为 0 且 vt+88（动作使能）非 0 且 vt+308（本地玩家对象）非 0，
//     否则返回 0xFFFF（无效 id）。
// 定位：a9 == 4 时取 vt+152（当前朝向）作方向码；a9 == 1 时 x = 本体 x + a6，
//       否则 x = 本体 x − a6（左右镜像）；y = 本体 y + a7；z = 本体 z + a8。
// 分发：a4 == 0 → 直接 sub_4E4A50(this, this, 动作id a2, a3, x, y, z, 方向 a9, …)
//       否则把 a4（上下文对象）的 x/y/z 三坐标 + +84 朝向字节**临时改写**为本次值，
//       走 sub_4E4C10（带上下文版）后**还原**原值 —— 上下文复用模式。
// 与 0x4E4F20（动作数据包）同为会话 3/16 文档的"位置化动作/动作数据包"对偶：
//   本函数 = 位置偏移版；0x4E4F20 = 数据块版（类型 48012 + 0x6E 字节结构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E4DE0(
        void *this,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12)
{
  int v13; // esi
  int v14; // ebx
  int v15; // eax
  int v16; // esi
  int v17; // eax
  int v18; // ebx
  int result; // eax
  int v20; // [esp+4h] [ebp-10h]
  int v21; // [esp+8h] [ebp-Ch]
  int v22; // [esp+Ch] [ebp-8h]
  char v23; // [esp+2Fh] [ebp+1Bh]

  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 316))(this) != 0
    || (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 88))(this) == 0
    || (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) == 0 )
  {
    return 0xFFFF;
  }
  if ( a9 == 4 )
    a9 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this);
  v13 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
  v14 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
  v15 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 128))(this);
  if ( a9 == 1 )
    v16 = a6 + v13;
  else
    v16 = v13 - a6;
  v17 = a8 + v15;
  v18 = a7 + v14;
  if ( a4 == 0 )
    return sub_4E4A50((int)this, (int)this, a2, a3, v16, v18, v17, a9, a10, a11, a12);
  v20 = *(uint32_t *)a4;
  v21 = *(uint32_t *)(a4 + 4);
  v22 = *(uint32_t *)(a4 + 8);
  v23 = *(uint8_t *)(a4 + 84);
  *(uint32_t *)(a4 + 4) = v18;
  *(uint32_t *)(a4 + 8) = v17;
  *(uint32_t *)a4 = v16;
  *(uint8_t *)(a4 + 84) = a9 != 1;
  result = sub_4E4C10((int)this, (int)this, a2, a3, a4, a5, a10, a11, a12);
  *(uint32_t *)a4 = v20;
  *(uint32_t *)(a4 + 4) = v21;
  *(uint32_t *)(a4 + 8) = v22;
  *(uint8_t *)(a4 + 84) = v23;
  return result;
}



// ------------------------------------------------------------
// 0x4E4F20 sub_4E4F20 —— ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6E 字节结构）
// 打包流程（全局暂存区 dword_9A06D0 起）：
//   头 18 字节 = 六个 16 位字段（a3/a4/a8/a9/a5/a11/a12/a14 的高低位拼接）
//   + a10 != nullptr 时 qmemcpy 0x62 字节（= 98）→ 头段升为 116 字节，a2 指向 unk_9A0744
//   + a14 > 0 时按 4 字节块 + 余数字节追加 a15（变长载荷）—— 总长 = v21（= v16 累计）
//   尾调 sub_4E4A50(a2, a1, **48012**, a13, a6, a7, 0, vt+152(朝向), 0, v21, 数据区)
// 与 0x4E4DE0（位置化动作）成对：本函数 = 携带 0x62 字节数据块的动作型
// （研究 P29/P30 的"动作数据包"；会话 3 已定案"类型 48012 + 0x6E 字节结构 → sub_4E4A50"）。
// 注：0x6E = 110 = 18 + 98 − 6？ [待验证：0x6E 与 116 的口径差 — 研究记录 0x6E 系
// 会话 3 结论，此处实测头段为 116(0x74) 字节；可能 0x6E 指的是定长载荷 |
// 0x62=98 而不含 18 字节头 —— 标注差异，不改代码]
// ------------------------------------------------------------
int /*userpurge*/ sub_4E4F20@<eax>(
        int a1@<ecx>,
        char *a2@<edi>,
        int16_t a3,
        int16_t a4,
        int16_t a5,
        int a6,
        int a7,
        int16_t a8,
        int16_t a9,
        const void *a10,
        char a11,
        int16_t a12,
        int a13,
        unsigned int a14,
        char *a15)
{
  int v16; // eax
  char *v17; // edi
  unsigned int v18; // ecx
  int v19; // eax
  int v21; // [esp-8h] [ebp-28h]
  int v22; // [esp+Ch] [ebp-14h]
  int v23; // [esp+10h] [ebp-10h]
  int v24; // [esp+14h] [ebp-Ch]
  int v25; // [esp+18h] [ebp-8h]

  LOWORD(v23) = a3;
  LOWORD(v22) = a8;
  HIBYTE(v24) = a11;
  HIWORD(v22) = a9;
  HIWORD(v23) = a4;
  dword_9A06D0[0] = v22;
  LOWORD(v25) = a12;
  dword_9A06D4 = v23;
  LOWORD(v24) = a5;
  BYTE2(v24) = a10 != nullptr;
  dword_9A06D8 = v24;
  HIWORD(v25) = a14;
  dword_9A06DC = v25;
  word_9A06E0 = HIWORD(a14);
  v16 = 18;
  if ( a10 != nullptr )
  {
    qmemcpy(&unk_9A06E2, a10, 0x62u);
    a2 = (char *)&unk_9A0744;
    v16 = 116;
  }
  if ( (int)a14 > 0 )
  {
    qmemcpy((char *)dword_9A06D0 + v16, a15, 4 * (a14 >> 2));
    v17 = (char *)&dword_9A06D0[a14 >> 2] + v16;
    v18 = a14 & 3;
    qmemcpy(v17, &a15[4 * (a14 >> 2)], v18);
    a2 = &v17[v18];
    v16 += a14;
  }
  v21 = v16;
  v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
  return sub_4E4A50((int)a2, a1, 48012, a13, a6, a7, 0, v19, 0, v21, (int)dword_9A06D0);
}



// ------------------------------------------------------------
// 0x4E5030 sub_4E5030
// ------------------------------------------------------------
void /*userpurge*/ sub_4E5030(
        uint32_t *a1@<ecx>,
        int a2@<ebx>,
        int a3@<esi>,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        uint8_t *a12,
        int a13,
        int a14,
        char a15,
        char a16,
        int a17,
        int a18)
{
  int v19; // eax
  int v20; // eax
  int v21; // esi
  int v22; // eax
  int v23; // ebx
  char *v24; // esi
  int v25; // eax
  int v26; // edi
  int v27; // eax
  int v28; // esi
  int v29; // eax
  int v30; // esi
  int v31; // eax
  int v32; // edi
  int v33; // eax
  int v34; // eax
  int64_t v37; // [esp+4h] [ebp-10h] BYREF
  int16_t v38; // [esp+Ch] [ebp-8h]
  uint32_t *v39; // [esp+10h] [ebp-4h]
  int v40; // [esp+24h] [ebp+10h]

  v19 = a1[29];
  v39 = a1;
  if ( v19 == 0 || *(uint32_t *)(v19 + 132) == 0 )
    return;
  if ( a16 != 0 )
  {
    v23 = a6;
    goto LABEL_11;
  }
  v20 = __RTDynamicCast(
          (int)a1,
          0,
          &IRDCollisionObject `RTTI Type Descriptor',
          &IRDActiveObject `RTTI Type Descriptor',
          0);
  v21 = v20;
  if ( v20 == 0 )
  {
    v23 = a6;
LABEL_9:
    a16 = 1;
    goto LABEL_11;
  }
  v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v20 + 672))(v20, 3);
  v23 = sub_4D5E00(v22) / 30 + a6;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v21 + 40))(v21, 529) == 0
    || *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v21 + 672))(v21, 3) >= v23 )
  {
    goto LABEL_9;
  }
  v23 = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v21 + 672))(v21, 3);
  a16 = 1;
LABEL_11:
  if ( v23 <= 1 )
  {
    v23 = 1;
  }
  else if ( v23 > 99 )
  {
    v23 = 99;
  }
  if ( a11 == 2 )
  {
    LOBYTE(v37) = 0;
    if ( a13 > 0 )
      LOBYTE(v37) = *a12;
    BYTE5(v37) = v23;
    *(uint16_t *)((char *)&v37 + 1) = a4;
    *(uint16_t *)((char *)&v37 + 3) = a5;
    HIWORD(v37) = a14;
    LOBYTE(v38) = a15;
    HIBYTE(v38) = a16;
    if ( a17 != 0 )
    {
      v24 = (char *)operator new(0x11u);
      *(uint64_t *)v24 = v37;
      *((uint16_t *)v24 + 4) = v38;
      *(uint32_t *)(v24 + 10) = *(uint32_t *)a17;
      *((uint16_t *)v24 + 7) = *(uint16_t *)(a17 + 4);
      v24[16] = *(uint8_t *)(a17 + 6);
      sub_4E4A50(a1, 48024, 0, a7, a8, a9, a10, 0, 17, v24);
      if ( v24 != nullptr )
        j__free(v24);
    }
    else
    {
      sub_4E4A50(a1, 48024, 0, a7, a8, a9, a10, 0, 10, &v37);
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 22, 2, a3, a2);
    if ( a14 == 0xFFFF || a15 != 1 )
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 0);
    else
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
    v40 = *(uint32_t *)dword_8F8520;
    v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 48))(a1);
    (*(void (/*thiscall*/ **)(int, int))(v40 + 36))(dword_8F8520, v25);
    v26 = *(uint32_t *)dword_8F8520;
    v27 = (*(int (/*thiscall*/ **)(uint32_t *))(*v39 + 52))(v39);
    (*(void (/*thiscall*/ **)(int, int))(v26 + 36))(dword_8F8520, v27);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a5);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a4);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v23);
    if ( a14 == 0xFFFF )
    {
      v28 = *(uint32_t *)dword_8F8520;
      v29 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);
      (*(void (/*thiscall*/ **)(int, int))(v28 + 36))(dword_8F8520, v29);
      v30 = *(uint32_t *)dword_8F8520;
      v31 = sub_460230(v39[29]);
      (*(void (/*thiscall*/ **)(int, int))(v30 + 36))(dword_8F8520, v31);
    }
    else
    {
      if ( a15 == 1 )
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 529);
      }
      else
      {
        v32 = *(uint32_t *)dword_8F8520;
        v33 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);
        (*(void (/*thiscall*/ **)(int, int))(v32 + 36))(dword_8F8520, v33);
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a14);
    }
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, a10);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a7);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a8);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a9);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, a11);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a13);
    if ( a13 > 0 )
      (*(void (/*thiscall*/ **)(int, uint8_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, a12, a13);
    v34 = *(uint32_t *)dword_8F8520;
    if ( a17 != 0 )
    {
      (*(void (/*stdcall*/ **)(int))(v34 + 32))(1);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, a17, 7);
    }
    else
    {
      (*(void (/*stdcall*/ **)(uint32_t))(v34 + 32))(0);
    }
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, a18);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
  }
}


// ============================================================
// 【分区 C】碰撞 / 命中判定几何族（0x4E5410 - 0x4E6770）
//   研究 P29（第 24/25 轮）：命中判定 = O(n²) 全对象配对 → 攻防门 → 1000ms 节流 →
//   多盒 → 3D AABB（命中区域 = 交集盒）；盒挂在帧数据上。
//   本区含攻击盒提取 / AABB 重叠 / 动画盒重叠 / 帧推进 / 伤害流水线。
// ------------------------------------------------------------

// ------------------------------------------------------------
// 0x4E5410 sub_4E5410 —— ★ 位置采样 vt+14C（每 100ms 节流，双缓冲）
// 已精修版见 src/cnrd/IRDCollisionObject.cpp:330（0x4E5410 vmt14C）。
// 逻辑：首查 dword_79C0B4 的 86/87 通道（输入采样）；a1[148] == −1（未初始化）时
// 两路 (x, now) 直接填充 this+145..148；否则若 now >= 上次 + ≥100 → 双缓冲推进
// （+145 ← +146、+147 ← 旧时刻、+146 ← 当前 x、+148 ← now）。
// 配套读取器 = 0x4E59C0（速度 = Δx×1000 / Δt）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5410(int *this)
{
  int *v2; // edi
  int i; // ebx
  int result; // eax
  int v5; // ebx
  int v6; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 86) != 1
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 87) != 1 )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 88);
  }
  nullsub_3(this);
  if ( *(this + 148) == -1 )
  {
    v2 = this + 147;
    for ( i = 2; i != 0; --i )
    {
      *(v2 - 2) = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      result = sub_699000((int)(this + 2));
      *v2++ = result;
    }
  }
  else
  {
    v5 = *(this + 148);
    result = sub_699000((int)(this + 2));
    if ( result >= v5 + 100 )
    {
      v6 = *this;
      *(this + 145) = *(this + 146);
      *(this + 147) = v5;
      *(this + 146) = (*(int (/*thiscall*/ **)(int *))(v6 + 120))(this);
      result = sub_699000((int)(this + 2));
      *(this + 148) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E54D0 sub_4E54D0 —— ★ 3D AABB 重叠测试（vm t1E8，无 z 轴；俯视平面）
// ⚠ 已精修版见 src/cnrd/IRDCollisionObject.cpp:27（同一函数的两份转写；以 L1 版为准）
// 判据：A.min ≤ B.max 且 B.min ≤ A.max 在 x/y 两轴同时成立。
// 四边取法：vt+440/444/448/452 = x 左右 / y 上下边界族（研究 P29 盒模型）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4E54D0(void *this, int a2)
{
  int v3; // ebx
  int v5; // ebx
  int v6; // ebx
  int v7; // edi

  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 440))(a2);
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 444))(this) < v3 )
    return false;
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 444))(a2);
  if ( v5 < (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 440))(this) )
    return false;
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 448))(a2);
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 452))(this) < v6 )
    return false;
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 452))(a2);
  return v7 >= (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 448))(this);
}



// ------------------------------------------------------------
// 0x4E5560 sub_4E5560 —— ★ 动画盒世界坐标重叠测试（vm t1EC）
// ⚠ 已精修版见 src/cnrd/IRDCollisionObject.cpp:50（同一函数的两份转写；以 L1 版为准）
// 双方各自的动画对象（sub_4918E0 obj+60，边界槽 0..3）给出四边界；判据 = 目标 y 区间
// 与本体 y 区间相交 且 x 区间相交（含"完全包含"分支）—— 研究 P29 盒迭代的下层实现。
// ------------------------------------------------------------
char /*thiscall*/ sub_4E5560(int *this, int *a2)
{
  int v3; // edi
  int v4; // edi
  int v5; // edi
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // edi
  int v10; // edi
  int v11; // edi
  int v12; // eax
  int v14; // edi
  int v15; // edi
  int v16; // eax
  int v17; // edi
  int v18; // edi
  int v19; // edi
  int v20; // edi
  int v21; // edi
  int v22; // edi
  int v23; // edi
  bool v24; // cc
  int v26; // [esp+Ch] [ebp-14h]
  int v27; // [esp+10h] [ebp-10h]
  int v28; // [esp+14h] [ebp-Ch]
  int v29; // [esp+18h] [ebp-8h]
  int v30; // [esp+1Ch] [ebp-4h]
  int v31; // [esp+28h] [ebp+8h]

  v3 = *(this + 30);
  if ( *(uint32_t *)(v3 + 148) == -1 )
    sub_4938F0(*(this + 30));
  v4 = 15 - sub_4918E0((int *)(v3 + 60), 0);
  v27 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v4;
  v5 = *(this + 30);
  if ( *(uint32_t *)(v5 + 148) == -1 )
    sub_4938F0(*(this + 30));
  v6 = sub_4918E0((int *)(v5 + 60), 1);
  v7 = v6 + (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 15;
  v8 = *(this + 30);
  v30 = v7;
  if ( *(uint32_t *)(v8 + 148) == -1 )
    sub_4938F0(v8);
  v9 = 15 - sub_4918E0((int *)(v8 + 60), 2);
  v29 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) + v9;
  v10 = *(this + 30);
  if ( *(uint32_t *)(v10 + 148) == -1 )
    sub_4938F0(*(this + 30));
  v11 = sub_4918E0((int *)(v10 + 60), 3);
  v12 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v28 = v12 + v11;
  v14 = a2[30];
  if ( *(uint32_t *)(v14 + 148) == -1 )
    sub_4938F0(a2[30]);
  v15 = sub_4918E0((int *)(v14 + 60), 0);
  v16 = (*(int (/*thiscall*/ **)(int *))(*a2 + 120))(a2) - v15;
  v17 = a2[30];
  v26 = v16;
  if ( *(uint32_t *)(v17 + 148) == -1 )
    sub_4938F0(v17);
  v18 = sub_4918E0((int *)(v17 + 60), 1);
  v31 = (*(int (/*thiscall*/ **)(int *))(*a2 + 120))(a2) + v18;
  v19 = a2[30];
  if ( *(uint32_t *)(v19 + 148) == -1 )
    sub_4938F0(a2[30]);
  sub_4918E0((int *)(v19 + 60), 2);
  (*(void (/*thiscall*/ **)(int *))(*a2 + 124))(a2);
  (*(void (/*thiscall*/ **)(int *))(*a2 + 128))(a2);
  v20 = a2[30];
  if ( *(uint32_t *)(v20 + 148) == -1 )
    sub_4938F0(a2[30]);
  v21 = sub_4918E0((int *)(v20 + 60), 3);
  v22 = (*(int (/*thiscall*/ **)(int *))(*a2 + 128))(a2) + v21;
  v23 = (*(int (/*thiscall*/ **)(int *))(*a2 + 124))(a2) + v22;
  if ( v23 > v29 && v23 < v28 )
  {
    if ( v31 > v27 && v31 < v30 )
      return 1;
    v24 = v26 < v27;
    if ( v26 > v27 )
    {
      if ( v26 < v30 )
        return 1;
      v24 = v26 < v27;
    }
    if ( v24 && v31 > v30 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4E5740 sub_4E5740 —— 概率判定（rand%10000 < 率×100；a3 为"抗性来源"）
// 结构 = 研究 §5.1 掷法同构：a3（对象）条件 17（有血）时从其属性块 (+284/+508，14 字节步距)
// 经 sub_4D5E40(v4, 12) 扣抵抗；sub_432FA0()（随机种机）后 `v5×100 > rand()%10000`。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4E5740(void *this, int a2, void *a3)
{
  char *v4; // eax
  float v5; // [esp+Ch] [ebp+8h]

  if ( this == a3 )
    return true;
  if ( a2 == 0 )
    return false;
  v5 = (float)a2;
  if ( a3 != nullptr && (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)a3 + 40))(a3, 17) != 0 )
  {
    v4 = (char *)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)a3 + 672))(a3, 3);
    v5 = v5 - (double)(int)sub_4D5E40(v4, 12);
  }
  sub_432FA0();
  return v5 * 100.0 > (double)(rand() % 10000);
}



// ------------------------------------------------------------
// 0x4E57E0 sub_4E57E0
// ------------------------------------------------------------
double /*thiscall*/ sub_4E57E0(void *this, int a2, int a3)
{
  double v4; // st7
  int v5; // eax
  double v6; // st7
  int v7; // eax
  double v8; // st7
  int v9; // esi
  double v10; // st7
  float v12; // [esp+10h] [ebp+8h]
  float v13; // [esp+10h] [ebp+8h]
  float v14; // [esp+14h] [ebp+Ch]
  float v15; // [esp+14h] [ebp+Ch]

  if ( a3 == 0 )
  {
    sub_699000((int)this + 36);
    sub_699000((int)this + 8);
  }
  v4 = *(float *)a2;
  v14 = *(float *)a2;
  if ( *(uint8_t *)(a2 + 16) != 0 )
  {
    v5 = *(uint32_t *)(a2 + 12);
    if ( v5 == 0 || v5 == 2 )
    {
      v6 = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 396))(this);
    }
    else
    {
      if ( v5 != 1 )
        goto LABEL_10;
      v6 = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 412))(this);
    }
    v4 = v6 + v14;
  }
LABEL_10:
  v7 = *(uint32_t *)(a2 + 12);
  v15 = ((double)*(int *)(a2 + 8) * 0.0099999998 + 1.0) * v4;
  if ( v7 != 0 )
  {
    if ( v7 != 1 )
      goto LABEL_15;
    v8 = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 416))(this);
  }
  else
  {
    v8 = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 400))(this);
  }
  v15 = (v8 * 0.0099999998 + 1.0) * v15;
LABEL_15:
  v9 = *(uint32_t *)(a2 + 12);
  if ( v9 == 0 )
  {
    v12 = (float)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 392))(this);
    v10 = sub_433F60((int)this, 3) * v12 / flt_9A05F4;
LABEL_19:
    v15 = (v10 + 1.0) * v15;
    return sub_433F60((int)this, 0) * v15;
  }
  if ( v9 == 1 )
  {
    v13 = (float)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 408))(this);
    v10 = sub_433F60((int)this, 5) * v13 / flt_9A060C;
    goto LABEL_19;
  }
  return sub_433F60((int)this, 0) * v15;
}



// ------------------------------------------------------------
// 0x4E5920 sub_4E5920
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5920(int *this)
{
  int result; // eax
  int v3; // edi
  int v4; // edi

  result = *(this + 29);
  if ( result != 0 )
  {
    result = *(uint32_t *)(result + 132);
    if ( result != 0 && *(uint32_t *)(result + 108) != 0 )
    {
      v3 = *(uint32_t *)(result + 1316);
      if ( v3 < 4 )
      {
        result = sub_472D40(*(uint32_t *)(result + 1316));
        if ( result != 0 )
        {
          switch ( v3 )
          {
            case 0:
              goto LABEL_7;
            case 1:
              goto LABEL_9;
            case 2:
            case 3:
              v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 120))(result);
              if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > v4 )
              {
LABEL_7:
                result = (*(int (/*thiscall*/ **)(int *))(*this + 60))(this);
                *(uint8_t *)(result + 52) = 0;
              }
              else
              {
LABEL_9:
                result = (*(int (/*thiscall*/ **)(int *))(*this + 60))(this);
                *(uint8_t *)(result + 52) = 1;
              }
              break;
            default:
              return result;
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E59C0 sub_4E59C0 —— 位置采样速度计算（0x4E5410 采样对读取器）
// `1000 × (当前 x − this+145) / (now − this+147)` —— 单位 x/秒（×1000 换算）。
// 未初始化（this+147 == −1）或时刻相同 → 0（防除零）。
// 消费点：击退/位移速度派生（研究 §15"受击位移=动画帧驱动"的量化侧）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E59C0(uint32_t *this)
{
  int v2; // ebx

  if ( *(this + 147) == -1 || *(this + 147) == sub_699000((int)(this + 2)) )
    return 0;
  v2 = 1000 * ((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - *(this + 145));
  return v2 / (sub_699000((int)(this + 2)) - *(this + 147));
}



// ------------------------------------------------------------
// 0x4E5A20 sub_4E5A20 —— 朝向/背向判定（a2 相对 this 的"左/右/背后"）
// 先比 vt+664（朝向码）：不等且 x 距离 < 50 → 返回 v9 <= 0（近身用朝向码定左右）。
// 否则比 x：相等时用 a2->vt+152（自身朝向）；否则返回 this.x >= a2.x。
// 研究 §14 的"背击判定"消费侧之一（[critical hit] + 宿主/背击加成，研究 §5.1）；
// 背击加成字段 = attackinfo+144（研究 §3 字段表）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5A20(void *this, int a2)
{
  int v4; // ebx
  int v5; // ebx
  int v7; // ebx
  int v8; // edi
  int v9; // [esp+14h] [ebp+8h]

  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 664))(a2);
  v9 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 664))(this) - v4;
  if ( v9 != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
    if ( (int)abs32(v5 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this)) < 50 )
      return v9 <= 0;
  }
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) == v7 )
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 152))(a2);
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) >= v8;
}



// ------------------------------------------------------------
// 0x4E5AC0 sub_4E5AC0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4E5AC0(uint32_t *this)
{
  return (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 33) != 0
      && *(uint32_t *)(*(this + 28) + 104) != 0;
}



// ------------------------------------------------------------
// 0x4E5AF0 sub_4E5AF0 —— ★ 背击判定（研究 §3 定案：背击暴击加成 attackinfo+144）
// "attackinfo 有伤害或反应（+16/+0）且 a1 的朝向 != a2->vt+660(a1)" → true（背后）。
// 研究 §3 字段表："+144 背击暴击加成（背击判定 sub_4E5AF0 时加进暴击率）【第 14 轮】"。
// 调用点：0x4E5CE0（攻方收尾语音：按背击/暴击两轴播音）、0x4E5B50 附近的暴击链。
// ------------------------------------------------------------
bool /*cdecl*/ sub_4E5AF0(int a1, int a2)
{
  int v2; // eax
  int v3; // esi
  bool result; // al

  v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
  result = false;
  if ( *(uint8_t *)(v2 + 16) != 0 || *(float *)v2 > 0.0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 660))(a2, a1);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1) != v3 )
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E5B50 sub_4E5B50 —— ★★ 暴击/有效命中判定（研究 20 §5.1 全文定案）
// 签名：__cdecl(a1 = 受击者, a2 = 攻击者)（与 §5.1 "sub_4E5B50（受击者, 攻击者）"一致）。
// 流程与 §5.1 定案清单逐条对应：
//   ① RTDynamicCast(a1 → IRDActiveObject) 失败 → false
//   ② 攻击信息须有伤害或反应：`attackinfo+16 == 0 && float+0 <= 0 && +60 == 0` → false
//      （研究原文："攻击信息须有伤害或反应"）
//   ③ v5 = 受击者大状态 ID（vt+840 = this+6556）
//   ④ 排除链（研究原文："状态 ∈ {0,1,3,4,6,9} 直接 false；11 仅当条件 273；
//      22 仅当条件 529"）—— 转写体为 `(条件273==0 || v5!=11) && v5!=0 && v5!=6
//      && v5!=4 && v5!=1 && v5!=3 && v5!=9 && (条件529==0 || a1+7148!=22)` 全合取，
//      **与排除表逐项吻合**（注意：研究写 "11 仅当条件 273"，即 273 假 → 非 11 才算通过）
//   ⑤ 返回 true = 本次为暴击（伤害 ×1.5 + 震屏 + 特效强化，研究 §5.1 第 14 轮更正）
// 逐项核对：排除值实测 = {0, 1, 3, 4, 6, 9}（研究 §5.1 表列六值，**完全吻合**）；
//   11 门 = `条件273 || v5!=11`；22 门 = `条件529==0 || v2[1787(+7148)] != 22`。
// ------------------------------------------------------------
bool /*cdecl*/ sub_4E5B50(int a1, int a2)
{
  uint32_t *v2; // edi
  int v3; // ecx
  int v5; // esi

  v2 = (uint32_t *)__RTDynamicCast(
                   a1,
                   0,
                   &IRDCollisionObject `RTTI Type Descriptor',
                   &IRDActiveObject `RTTI Type Descriptor',
                   0);
  if ( v2 == nullptr )
    return false;
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
  if ( *(uint8_t *)(v3 + 16) == 0 && *(float *)v3 <= 0.0 && *(uint32_t *)(v3 + 60) == 0 )
    return false;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*v2 + 840))(v2);
  return ((*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v2 + 40))(v2, 273) == 0 || v5 != 11)
      && v5 != 0
      && v5 != 6
      && v5 != 4
      && v5 != 1
      && v5 != 3
      && v5 != 9
      && ((*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v2 + 40))(v2, 529) == 0 || v2[1787] != 22);
}



// ------------------------------------------------------------
// 0x4E5C10 sub_4E5C10
// ------------------------------------------------------------
char /*thiscall*/ sub_4E5C10(int this, char a2, int a3)
{
  char result; // al
  int v5; // edi

  result = *(uint8_t *)(this + 642);
  if ( result != 0 )
  {
    if ( a2 != 0 )
    {
      *(uint8_t *)(this + 642) = a2;
      *(uint32_t *)(this + 644) = a3;
      return a3;
    }
    else
    {
      v5 = *(uint32_t *)(this + 120);
      if ( v5 != 0 )
      {
        sub_4910E0(*(uint32_t *)(this + 120));
        result = sub_493A60(v5, *(uint32_t *)(v5 + 32));
        *(uint8_t *)(this + 642) = 0;
        *(uint32_t *)(this + 644) = a3;
      }
      else
      {
        *(uint8_t *)(this + 642) = 0;
        *(uint32_t *)(this + 644) = a3;
      }
    }
  }
  else
  {
    *(uint8_t *)(this + 642) = a2;
    *(uint32_t *)(this + 644) = a3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E5CA0 sub_4E5CA0
// ------------------------------------------------------------
char /*thiscall*/ sub_4E5CA0(void *this)
{
  int v2; // esi

  v2 = 200;
  while ( v2 != (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 376))(this) )
  {
    if ( ++v2 >= 205 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x4E5CE0 sub_4E5CE0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5CE0(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // edi
  int result; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax

  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);
  v4 = __RTDynamicCast(v3, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
  result = __RTDynamicCast(
             a2,
             0,
             &IRDCollisionObject `RTTI Type Descriptor',
             &IRDActiveObject `RTTI Type Descriptor',
             0);
  v6 = result;
  if ( v4 != 0 && result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 308))(v4);
    if ( (uint8_t)result != 0 )
    {
      if ( (uint8_t)sub_4E5AF0(v6, this) != 0 )
      {
        sub_426820(*(uint32_t *)(*(this + 29) + 132), 1, 0);
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 52))(v4);
        sub_495A70(1, 5, v7);
      }
      result = sub_4E5B50(v6, this);
      if ( (uint8_t)result != 0 )
      {
        sub_426820(*(uint32_t *)(*(this + 29) + 132), 2, 0);
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 52))(v4);
        return sub_495A70(1, 4, v8);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E5DC0 sub_4E5DC0 —— ★★★ 表现壳 / hit stop 施加点（研究 20 §3 全文定案）
// __thiscall(this=受击者, a2=攻击者, a3=命中盒, a4=格挡标志)
// 研究 §3 伪码 → 转写体逐行对照：
//   v6 = vt+648(this, &v16(初值100), a2)        伤害类型（0/1 正常，2 = 落空）
//   if (a4 != 0)（格挡）:
//       v6 != 2 → vt+644(this, a2, a3)          ★ 格挡特效：GuardSpark.ani +
//                                               GuardCircle.ani + Stuck.ani（0x4E9760）
//       读攻击定义 attackinfo+128 → 非 0 → 广播 **"STUCK_BLADE"** 否则 **"STUCK_BLUNT"**
//                                               ★ 刀剑/钝器两种"卡肉"音效（研究 §3 要点二）
//   else if (v6 != 2):
//       受击者当前"伤害态" = (this+642 标志 ? this+161 盒快照 : 动画对象(this+30)+112)
//       —— 当该值为 2 时**跳过** stuck 施加，直接走 HITEFF（研究 §3 原文"若受击者伤害态 != 2"）
//       否则:
//           v9 = attackinfo+132                ★★ 本次命中的硬直时长（毫秒）= hit stop 时长
//           若 v9 > 0 且（主状态(this+50=字节+200)=0 或（==1 且 vt+248 剩余硬直 < v9））:
//               vt+228(this, 1, v9, 0)          ★★★ 施加/延长 stuck 状态
//                                               （= 主状态写入器，研究 §4.2 —— hit stop 本体）
//       vt+640(this, a2, a3)                    ★ HITEFF 通用命中特效（0x4E88A0，研究 §5.2）
//       读 attackinfo+92（VC6 std::string）→ 非空 → vt+212 播自定义 wav
// 核验结论：反编译体**逐条吻合**研究 §3 伪码（含 attackinfo+132 → vt+228 直连实证，
// 研究第 14 轮"表现壳全文（attackinfo+132→vt+228 直连实证）"）。
// 研究 §15 复用价值 #1：本函数一次调用同时携带 受击者/攻击者/硬直时长/格挡位
// —— 比 HP 锚点更上游；硬直时长 attackinfo+132 可直接读出。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5DC0(uint32_t *this, int a2, int a3, char a4)
{
  int v5; // eax
  int v6; // eax
  int v7; // ebx
  int v8; // ebx
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // eax
  char v15; // cl
  int v16; // [esp+8h] [ebp-4h] BYREF

  v5 = *this;
  v16 = 100;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int *, int))(v5 + 648))(this, &v16, a2);
  if ( a4 != 0 )
  {
    if ( v6 != 2 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 644))(this, a2, a3);
      v15 = *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 128);
      v16 = 0;
      if ( v15 != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, const char *))(*this + 212))(this, "STUCK_BLADE");
        return 0;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, const char *))(*this + 212))(this, "STUCK_BLUNT");
    }
  }
  else if ( v6 != 2 )
  {
    if ( *((uint8_t *)this + 642) != 0 )
    {
      v7 = *(this + 161);
    }
    else
    {
      v8 = *(this + 30);
      if ( v8 == 0 )
      {
LABEL_10:
        v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 132);
        if ( v9 > 0 )
        {
          v10 = *(this + 50);
          if ( v10 == 0 || v10 == 1 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 248))(this) < v9 )
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 228))(this, 1, v9, 0);
        }
        goto LABEL_15;
      }
      if ( *(uint32_t *)(v8 + 148) == -1 )
        sub_4938F0(*(this + 30));
      v7 = *(uint32_t *)(v8 + 112);
    }
    if ( v7 != 2 )
      goto LABEL_10;
LABEL_15:
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 640))(this, a2, a3);
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
    v12 = *(uint32_t *)(v11 + 116);
    v13 = v11 + 92;
    if ( v12 < 0x10 )
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t))(*this + 212))(this, v13 + 4, -1, 0, 0);
    else
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t))(*this + 212))(
        this,
        *(uint32_t *)(v13 + 4),
        -1,
        0,
        0);
    return 0;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4E5F30 sub_4E5F30
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5F30(uint32_t *this, int a2)
{
  uint32_t *v2; // eax

  if ( *(this + 96) < 0x10u )
    v2 = this + 91;
  else
    v2 = (uint32_t *)*(this + 91);
  return (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, "%s%s", v2, a2);
}



// ------------------------------------------------------------
// 0x4E5F70 sub_4E5F70 —— ★ 硬直率掷（研究 §5.1 第 14 轮定案：同构于暴击掷）
// 研究 §5.1 原文："硬直率掷（sub_4E5F70）同构（rand()%10000 < 率×100），
//   掷完把结果+rand 种机打包发服务器背书"。
// 调用点：本地扫掠 sub_4E82B0 命中后（`sub_4E5F70(a1, v5, v27, 1, 1)`）——
//   即本地命中即刻把"硬直掷结果"上报服务端（客户端信任伤害架构，研究 §11 第 14 轮）。
// ------------------------------------------------------------
void /*usercall*/ sub_4E5F70(int a1@<ebx>, int a2, int a3, float *a4, char a5, char a6)
{
  int v6; // esi
  int v7; // edi
  int v8; // esi
  int v9; // edi
  int v10; // eax
  int v11; // eax
  char v12; // cl
  int v13; // ecx
  int v14; // ebx
  int v15; // eax
  int v16; // eax
  double v17; // st7
  int v18; // eax
  int v19; // eax
  double v20; // st7
  int v21; // ebx
  int v22; // eax
  int v23; // ebx
  int v24; // eax
  int v25; // esi
  int v26; // eax
  int v27; // esi
  int v28; // eax
  float *v29; // esi
  int v30; // eax
  int v31; // esi
  int v32; // eax
  float v33; // [esp+4h] [ebp-Ch]
  float v34; // [esp+4h] [ebp-Ch]
  int v35; // [esp+8h] [ebp-8h] BYREF
  float v36; // [esp+Ch] [ebp-4h]

  v6 = a2;
  if ( a2 != 0 )
  {
    v7 = a3;
    if ( a3 != 0 )
    {
      sub_432FA0();
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 380))(v6);
      v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 380))(v7);
      if ( a5 == 0
        || (v10 = *(uint32_t *)v9, a2 = 100, (*(int (/*thiscall*/ **)(int, int *, int))(v10 + 648))(v9, &a2, v8) != 3) )
      {
        HIBYTE(a2) = 0;
        if ( a6 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 40))(v9, 17) != 0 )
        {
          v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 348))(v8, a1);
          v12 = *(uint8_t *)(v11 + 80);
          v36 = *(float *)(v11 + 76) + 3.0;
          if ( v12 != 0 )
          {
            v13 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 364))(v8) + 8);
            if ( v13 > 1 )
              v36 = (double)(v13 * (v13 + 1) / 2 - 1) + v36;
          }
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 632))(v9) < 50 )
          {
            v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 576))(v8);
            if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 636))(v9) != v14 )
              v36 = v36 - 5.0;
          }
          if ( (uint8_t)sub_4E5AF0(v9, v8) != 0 )
            v36 = v36 - 5.0;
          v33 = 0.0;
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 576))(v8) != 0 )
          {
            v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 576))(v8);
            v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 672))(v15, 3);
            v33 = sub_43B5A0(v16 + 1264);
          }
          v17 = ((double (/*thiscall*/ *)(int, int))*(uint32_t *)(*(uint32_t *)v9 + 704))(v9, v8) + v33;
          v18 = *(uint32_t *)(dword_8F7A24 + 12);
          v34 = v17;
          if ( v18 == 4 || v18 == 6 )
          {
            v19 = sub_4E4610(v9);
            if ( v19 != -1 && v19 < 10000 )
            {
              sub_4049C0(0.0, 1.0, v19, 10000);
              v34 = v17 * v34;
            }
          }
          v20 = v34 + v36;
          v36 = v20;
          if ( v20 > 0.0 && v36 * 100.0 > (double)(rand() % 10000) )
          {
            sub_4D8730(v9);
            HIBYTE(a2) = 1;
          }
        }
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 19, 2);
        v21 = *(uint32_t *)dword_8F8520;
        v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 48))(v8);
        (*(void (/*thiscall*/ **)(int, int))(v21 + 36))(dword_8F8520, v22);
        v23 = *(uint32_t *)dword_8F8520;
        v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 52))(v8);
        (*(void (/*thiscall*/ **)(int, int))(v23 + 36))(dword_8F8520, v24);
        v25 = *(uint32_t *)dword_8F8520;
        v26 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 48))(v9);
        (*(void (/*thiscall*/ **)(int, int))(v25 + 36))(dword_8F8520, v26);
        v27 = *(uint32_t *)dword_8F8520;
        v28 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 52))(v9);
        (*(void (/*thiscall*/ **)(int, int))(v27 + 36))(dword_8F8520, v28);
        v29 = a4;
        (*(void (/*thiscall*/ **)(int, float *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, a4, 4);
        v35 = (uint64_t)v29[1];
        (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &v35, 2);
        v35 = (uint64_t)v29[2];
        (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &v35, 2);
        v35 = (uint64_t)v29[3];
        (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &v35, 2);
        v35 = (uint64_t)v29[4];
        (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &v35, 2);
        v35 = (uint64_t)v29[5];
        v30 = (*(int (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &v35, 2);
        LOBYTE(v30) = HIBYTE(a2) != 0;
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v30);
        v31 = *(uint32_t *)dword_8F8520;
        v32 = rand();
        (*(void (/*thiscall*/ **)(int, int))(v31 + 36))(dword_8F8520, v32);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
      }
    }
  }
}


// ------------------------------------------------------------
// 0x4E62B0 sub_4E62B0 —— ★★★ 攻击盒 vs 受击盒碰撞判定（研究 P29 盒模型，第 24/25 轮）
// 签名：__cdecl(a1 = 攻击者, a2 = 攻击动画对象, a3 = 受击者, a4 = 受击动画对象, a5 = ？)
// 门：a2/a4 非空；`a1->vt+600 != 0` 且 `a3->vt+608 != 0`
//     —— ★ 攻/防使能门（研究 P29：`vt+600/608 = this+640/641 攻防使能门`；
//        研究 P35：this+641 = 受击盒使能 = 无敌开关）。
// 盒提取：`v7 = a2 + 116`（★ 攻击盒 = 动画对象+116）、`v38 = a4 + 132`
//         （★ 受击盒 = 动画对象+132）—— 研究 P29 原文"攻击盒=动画+116/受击盒=动画+132，24B/盒"，
//         且先 sub_4FEF30(盒) 校验（空 vector 返回 0）。
// 迭代：v8 遍历攻击盒（24 字节步距：4 float 边界 + 2 个 int），每盒：
//   `vt+152()` 为 0（朝左）→ **盒 x 镜像 `v23 = -v23 - v26`**（研究 P29：
//      "朝左镜像 x=−x−w"）；再加本体的 x/y/z（vt+120/124/128）→ 世界坐标
//   内层 while 遍历受击盒数组（v38+4..v38+8，同样 24 字节步距）逐盒镜像化后
//     调 **sub_491130(&攻击盒, &受击盒世界坐标, a5)** —— ★ 研究 P29 定案的
//     3D AABB 分离轴测试本体（"尺寸0=禁用"），返回非 0 → 本函数返回 1（命中）
// 调用者：0x4D6A80（多命中盒 vt+480）/ 0x4E6570（单盒包装）——
//   研究 §1.2 "主盒 + this+120+204 附加盒链表逐盒 sub_4E62B0"。
// 研究 P29 补充：命中区域 = 两盒交集 AABB（由 sub_491130 输出）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4E62B0(int *a1, int a2, int *a3, int a4, int a5)
{
  int v5; // ecx
  int v6; // eax
  int v7; // edi
  int v8; // eax
  bool v9; // zf
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // edi
  int v17; // eax
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int v22; // ecx
  float v23; // [esp+4h] [ebp-3Ch] BYREF
  float v24; // [esp+8h] [ebp-38h]
  float v25; // [esp+Ch] [ebp-34h]
  float v26; // [esp+10h] [ebp-30h]
  int v27; // [esp+14h] [ebp-2Ch]
  int v28; // [esp+18h] [ebp-28h]
  float v29; // [esp+1Ch] [ebp-24h] BYREF
  float v30; // [esp+20h] [ebp-20h]
  float v31; // [esp+24h] [ebp-1Ch]
  float v32; // [esp+28h] [ebp-18h]
  int v33; // [esp+2Ch] [ebp-14h]
  int v34; // [esp+30h] [ebp-10h]
  int v35; // [esp+34h] [ebp-Ch]
  int v36; // [esp+38h] [ebp-8h]
  int v37; // [esp+3Ch] [ebp-4h]
  int v38; // [esp+4Ch] [ebp+Ch]

  if ( a2 == 0 || a4 == 0 )
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 600))(a1) == 0
    || (*(uint8_t (/*thiscall*/ **)(int *))(*a3 + 608))(a3) == 0 )
  {
    return 0;
  }
  if ( *(uint32_t *)(a2 + 148) == -1 )
    sub_4938F0(a2);
  v5 = a4;
  v6 = *(uint32_t *)(a4 + 148);
  v7 = a2 + 116;
  v35 = a2 + 116;
  if ( v6 == -1 )
  {
    sub_4938F0(a4);
    v5 = a4;
  }
  v38 = v5 + 132;
  if ( sub_4FEF30(v7) == 0 )
    return 0;
  if ( sub_4FEF30(v38) == 0 )
    return 0;
  v8 = *(uint32_t *)(v7 + 4);
  v9 = v8 == *(uint32_t *)(v7 + 8);
  v23 = 0.0;
  v24 = 0.0;
  v25 = 0.0;
  v26 = 0.0;
  v27 = 0;
  v28 = 0;
  v29 = 0.0;
  v30 = 0.0;
  v31 = 0.0;
  v32 = 0.0;
  v33 = 0;
  v34 = 0;
  v37 = v8;
  if ( v9 )
    return 0;
  while ( 1 )
  {
    v23 = *(float *)v8;
    v24 = *(float *)(v8 + 4);
    v25 = *(float *)(v8 + 8);
    v26 = *(float *)(v8 + 12);
    v27 = *(uint32_t *)(v8 + 16);
    v11 = *(uint32_t *)(v8 + 20);
    v12 = *a1;
    v28 = v11;
    if ( (*(int (/*thiscall*/ **)(int *))(v12 + 152))(a1) == 0 )
      v23 = -v23 - v26;
    v36 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1);
    v13 = *a1;
    v23 = (double)v36 + v23;
    v14 = (*(int (/*thiscall*/ **)(int *))(v13 + 124))(a1);
    v15 = *a1;
    v36 = v14;
    v24 = (double)v14 + v24;
    v36 = (*(int (/*thiscall*/ **)(int *))(v15 + 128))(a1);
    v16 = *(uint32_t *)(v38 + 4);
    v17 = *(uint32_t *)(v38 + 8);
    v25 = (double)v36 + v25;
    if ( v16 != v17 )
      break;
LABEL_21:
    v22 = *(uint32_t *)(v35 + 8);
    v37 += 24;
    if ( v37 == v22 )
      return 0;
    v8 = v37;
  }
  while ( 1 )
  {
    v29 = *(float *)v16;
    v30 = *(float *)(v16 + 4);
    v31 = *(float *)(v16 + 8);
    v32 = *(float *)(v16 + 12);
    v33 = *(uint32_t *)(v16 + 16);
    v18 = *a3;
    v34 = *(uint32_t *)(v16 + 20);
    if ( (*(int (/*thiscall*/ **)(int *))(v18 + 152))(a3) == 0 )
      v29 = -v29 - v32;
    v19 = (*(int (/*thiscall*/ **)(int *))(*a3 + 120))(a3);
    v20 = *a3;
    v36 = v19;
    v29 = (double)v19 + v29;
    v36 = (*(int (/*thiscall*/ **)(int *))(v20 + 124))(a3);
    v21 = *a3;
    v30 = (double)v36 + v30;
    v36 = (*(int (/*thiscall*/ **)(int *))(v21 + 128))(a3);
    v31 = (double)v36 + v31;
    if ( (uint8_t)sub_491130(&v23, &v29, a5) != 0 )
      return 1;
    v16 += 24;
    if ( v16 == *(uint32_t *)(v38 + 8) )
      goto LABEL_21;
  }
}


// ------------------------------------------------------------
// 0x4E6520 sub_4E6520 —— 命中目标列表成员查询（this+164 vector，4 字节 id 数组）
// 与 0x4E6FD0（链表摘除）/ 0x4E7040（移除 + vt+468 回调）成族 ——
// 目标记忆列表（研究 §1.2 vt+356 "记录当前命中目标（目标记忆，锁定连打用）"的后端）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4E6520(uint32_t *this, int a2)
{
  int v2; // esi
  unsigned int i; // edx

  v2 = *(this + 164);
  for ( i = 0; v2 != 0 && i < (*(this + 165) - v2) >> 2; ++i )
  {
    if ( *(uint32_t *)(*(this + 164) + 4 * i) == a2 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4E6570 sub_4E6570
// ------------------------------------------------------------
char /*thiscall*/ sub_4E6570(int *this, int *a2, int a3)
{
  int v4; // eax

  v4 = (*(int (/*thiscall*/ **)(int *))(*a2 + 200))(a2);
  return sub_4E62B0(this, *(this + 30), a2, v4, a3);
}



// ------------------------------------------------------------
// 0x4E65A0 sub_4E65A0
// ------------------------------------------------------------
bool /*thiscall*/ sub_4E65A0(uint32_t *this, uint32_t *a2)
{
  int v3; // eax
  int v5; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 33) == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 33) == 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 428))(this) == 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 432))(this) == 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 428))(a2) == 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 432))(a2) == 0
    || (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t *))(*this + 488))(this, a2) == 0 )
  {
    return false;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 33) != 0 )
  {
    v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 672))(this) + 8) - 1;
    if ( v3 != 0 )
    {
      if ( v3 == 1 && sub_4E6520(this, (int)a2) == 0 )
        return true;
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 436))(a2) <= 0 )
    {
      return true;
    }
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 33) == 0 )
    return false;
  v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 672))(a2) + 8) - 1;
  if ( v5 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this) <= 0;
  return v5 == 1 && sub_4E6520(a2, (int)this) == 0;
}



// ------------------------------------------------------------
// 0x4E66B0 sub_4E66B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E66B0(void *this, char a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // esi
  int v6; // eax

  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
    return 50;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 6 )
    return *((int16_t *)dword_8F7C48 + 10 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76) + 1);
  if ( a2 == 0 )
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
  v3 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 576))(this);
  v4 = __RTDynamicCast(v3, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
  v5 = v4;
  if ( v4 == 0 )
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
  if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 792))(v4, 8) == 0 )
    return 1;
  v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 792))(v5, 8);
  return *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 16))(v6) + 24);
}



// ------------------------------------------------------------
// 0x4E6770 sub_4E6770 —— ★★★ 伤害流水线 / vt+628（研究 P14 九步公式全文定案）
// 签名：__thiscall(this = 攻击者, a2 = 输出标志槽, a3 = 输出槽, a4 = ？, a5 = 受击者, a6 = 命中盒,
//                   a7 = float 位（!=0 时作为固定伤害值覆盖）)
// 调用点 = 命中主处理器 0x4D71B0 ⑥（研究 §2：vt+648(类型) → vt+628(伤害)）。
// 反编译体与研究 P14 九步及《21 速查》P14-P16 的对应：
//   ⓪ **时间/随机基准**：`*(float*)&a7 == 0` 时 v8 = clock(this+9)*7 + clock(this+2)
//      + a6[2]*3 + a6[1]*2 + a6[0]（命中盒 + 时钟的复合"hash 种子"，用于后续 ± 方差）
//      否则 v8 = 传入的固定伤害值（整数化）
//   ① 取攻击定义 v12 = a5->vt+348(attackinfo)
//   ② **基础门**：`a4 <= 0 || (attackinfo+16 == 0 && float+0 <= 0)` → 返回 0（无伤害）
//   ③ **属性一致 ×1.05**：`attackinfo+20`（属性攻击位）非 4 且 == 攻击者属性块 +4 的
//      属性 id → **伤害 × 1.05**（研究 P14 九步第 2 步"属性一致×1.05"）
//   ④ **抗性减免**：`v86+20 != 4` 且 RTDynamicCast 成功 → 取 sub_4DA0F0(属性id)
//      → `伤害 × (flt_9A0624 − 抗性 × flt_9A0628) × 0.0099999998`
//      （研究 P14 九步第 3 步"抗性"；flt_9A06xx = 运行时加载的平衡系数，PE 内全 0，
//       研究 §11"防御/抗性平衡系数运行时从数据文件加载"）
//   ⑤ **伤害大类初值**：v20 = attackinfo+12（0 物理 / 1 魔法 / 2 忽略防御）
//      —— 魔法(1) 用 flt_9A061C + sub_4E66B0(**角色特性/属性抗** 查询) × flt_9A0620
//   ★ **± 方差**（研究 P14 九步第 4 步）：`sub_4049C0(-v85, v85, sub_4D33A0(&v83)%1000, 999)`
//      —— LCG 取值 %1000 作插值 t，在 [−v85, +v85] 内线性取值（± 方差），并加到伤害
//   ★ **防御×(1−减伤)**（第 5 步）：受击者 vt+716 取二路减伤 (v85, v82) →
//      `伤害 ×= (1.0 − v85 − v82)`；再按压/魔 (-子 8 或 10) 从属性块 (+1138/+1180)
//      经 PVE/PVP 系数 sub_433F60 扣防御
//   ★ **攻击力**（第 6 步）：物理走受击者 vt+392 + flt_9A05F8，魔法走 vt+408 + flt_9A0610，
//      均 `经 sub_433F60(场景) × 值 ÷ flt` 后加到伤害
//   ★ **武器/技能项**（第 7 步）：attackinfo+4/+8 双格 × (1 + attackinfo+16 加成 与
//      受方 vt+400/vt+404 或 vt+416/vt+420 的百分比项) ÷ 100，再 × sub_433F60(场景) 加算
//   ★ **暴击率组装**（第 8 步）：`v85 = attackinfo+72 + 3.0`（基础暴击率 + 3.0）
//      + 宿主加成（受->vt+576 → 其属性块 +1222 或 +1208 经 sub_41A5E0 防篡读）
//      + **背击加成 attackinfo+144**（若 sub_4E5AF0 判定为背击）+
//        车主链项 (+1250 或 +1236 经防篡浮点壳 sub_43B5A0)
//      − 受方抗性（v18 → 属性块 +1278）
//   ★★ **暴击掷 + ×1.5**（第 9 步，研究 §5.1 第 14 轮实证点）：
//      `v80 = sub_4D33A0(&v83); % 10000`；`v85*100 > roll` 成立 → `*a2 = 1`（暴击位）
//      **且 `a7 = a7 * 1.5`**；否则 `*a2 = 0`（非暴击）
//      —— 与《21 速查》P14 "掷 hash%10000 < 率×100" 逐字吻合（率×100 即 v85×100）。
//   ★ **快速连打加伤**（研究 §5.1 第 14 轮："≥20 连 ×1.02-1.6，<20 连 1% 翻倍"）：
//      v60 = vt+632（★ 距上次受击毫秒，研究第 15 轮更正语义）；v60 >= 50 或
//      受方车主 == 攻方[143]（刚打过）→ *a3 = 0、攻方[144] = 1（连击计数复位）
//      否则车主条件 273 成立且 v60 >= 20 → sub_4049C0(200.0, 100.0, v60, 50) 插值
//      （50→200ms 区间内 200→100 线性递减 = **1.02..1.6 的加伤倍率来源**）；
//      v60 < 20 → `rand()%100 < 1` 即 **1% 概率伤害翻倍**（v62 = a7 + a7）
//      + 连击计数攻方[144] 递增夹取 4 + sub_4278D0(1, 级) + 受方为玩家时 sub_495A70 播音
//   ★ **终段**：`a7 × attackinfo+148 × 0.01 × a4 × 0.01`（技能倍率）；
//      vt+16 持有标签 16/17 → 再 × attackinfo+84/+88 × 0.01（[human damage rate]/
//      [fort damage rate] 对人型/城械倍率，研究 §3 字段表）；下限夹取 1.0；
//      最后遍历攻方 18 观察者 ->vt+164(受, 盒, *a2 暴击位, &a7) —— 观察者侧收尾修饰。
// ✅ 与研究 P14 九步**逐条吻合**（含"属性一致×1.05 / 抗性 / ±方差 / 防御×(1−减伤) /
//    攻击力 / 武器 / 暴击掷 / 快速连打加伤 / 技能倍率"全部九步）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E6770(uint32_t *this, uint8_t *a2, uint32_t *a3, int a4, int *a5, float *a6, int a7)
{
  uint32_t *v7; // ebx
  double v8; // st7
  int v9; // esi
  int v11; // edx
  int v12; // edi
  int64_t v13; // rax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // ecx
  int v18; // edi
  int v19; // eax
  int v20; // eax
  double v21; // st7
  char v22; // al
  int v23; // eax
  double v24; // st7
  int v25; // ebx
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
  double v30; // st7
  int v31; // eax
  int v32; // eax
  double v33; // st7
  int v34; // eax
  double v35; // st7
  int v36; // eax
  double v37; // st7
  int v38; // eax
  int v39; // edx
  double v40; // st7
  int v41; // eax
  int v42; // eax
  double v43; // st7
  char v44; // al
  int v45; // edx
  double v46; // st7
  int v47; // eax
  double v48; // st7
  int v49; // edx
  int v50; // eax
  int v51; // eax
  int v52; // eax
  int v53; // edx
  int v54; // eax
  int v55; // ecx
  int v56; // eax
  double v57; // st7
  int v58; // eax
  double v59; // st7
  int v60; // edi
  int v61; // eax
  double v62; // st7
  double v63; // st7
  int v64; // eax
  bool v65; // sf
  int v66; // eax
  int v67; // eax
  int v68; // edi
  int v69; // eax
  int v70; // eax
  int v71; // edi
  int i; // ebx
  int v73; // eax
  float v75; // [esp+Ch] [ebp-34h]
  int v76; // [esp+14h] [ebp-2Ch]
  int v77; // [esp+18h] [ebp-28h]
  char v78; // [esp+18h] [ebp-28h]
  int v79; // [esp+18h] [ebp-28h]
  int v80; // [esp+28h] [ebp-18h] BYREF
  float v81; // [esp+2Ch] [ebp-14h]
  float v82; // [esp+30h] [ebp-10h] BYREF
  int v83; // [esp+34h] [ebp-Ch] BYREF
  uint32_t *v84; // [esp+38h] [ebp-8h]
  float v85; // [esp+3Ch] [ebp-4h] BYREF
  int v86; // [esp+54h] [ebp+14h]

  v7 = this;
  v84 = this;
  if ( *(float *)&a7 == 0.0 )
  {
    v9 = 7 * sub_699000((int)(this + 9));
    LODWORD(v82) = sub_699000((int)(v7 + 2)) + v9;
    v8 = (double)SLODWORD(v82) + a6[2] * 3.0 + a6[1] + a6[1] + *a6;
  }
  else
  {
    a7 = *(int *)a7;
    v8 = (double)(unsigned int)a7;
  }
  v11 = *a5;
  v83 = (uint64_t)v8;
  v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 348))(a5);
  v86 = v12;
  if ( a4 <= 0 || *(uint8_t *)(v12 + 16) == 0 && *(float *)v12 <= 0.0 )
  {
    LODWORD(v13) = 0;
    return v13;
  }
  *(float *)&a7 = ((double (/*thiscall*/ *)(int *, int, int *))*(uint32_t *)(*a5 + 424))(a5, v12, &v83);
  v14 = v7[29];
  if ( v14 != 0 )
  {
    v15 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v14 + 132) + 44) + 4);
    if ( v15 != 4 && v15 == *(uint32_t *)(v12 + 20) )
      *(float *)&a7 = *(float *)&a7 * 1.05;
  }
  v16 = __RTDynamicCast(
          (int)v7,
          0,
          &IRDCollisionObject `RTTI Type Descriptor',
          &IRDActiveObject `RTTI Type Descriptor',
          0);
  v17 = v12;
  v18 = v16;
  if ( *(uint32_t *)(v86 + 20) != 4 && v16 != 0 )
  {
    v77 = *(uint32_t *)(v86 + 20);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v16 + 672))(v16, 3);
    v19 = sub_4DA0F0(v77);
    v17 = v86;
    v82 = *(float *)&v19;
    *(float *)&a7 = (flt_9A0624 - (double)v19 * flt_9A0628) * *(float *)&a7 * 0.0099999998;
  }
  v20 = *(uint32_t *)(v17 + 12);
  v85 = 0.0;
  if ( v20 != 0 )
  {
    if ( v20 == 1 )
    {
      v22 = *(uint8_t *)(v17 + 16);
      v85 = flt_9A061C;
      v82 = COERCE_FLOAT(sub_4E66B0(v22));
      v21 = (double)SLODWORD(v82) * flt_9A0620 + v85;
    }
    else
    {
      if ( v20 != 2 )
        goto LABEL_22;
      v21 = *(float *)&a7 * 0.07000000000000001;
    }
  }
  else
  {
    v78 = *(uint8_t *)(v17 + 16);
    v85 = flt_9A0604;
    v82 = COERCE_FLOAT(sub_4E66B0(v78));
    v21 = (double)SLODWORD(v82) * flt_9A0608 + v85;
  }
  v85 = v21;
LABEL_22:
  if ( byte_9A05F0 != 0 )
    v85 = 0.0;
  v23 = sub_4D33A0(&v83);
  v24 = -v85;
  v75 = v24;
  sub_4049C0(v75, v85, v23 % 1000, 999);
  *(float *)&a7 = v24 + *(float *)&a7;
  if ( v18 != 0 && *(uint32_t *)(v86 + 12) != 2 && *(uint8_t *)(v86 + 82) == 0 )
  {
    v25 = *(uint32_t *)v18;
    v76 = *(uint32_t *)(v86 + 12);
    v85 = 0.0;
    v82 = 0.0;
    v26 = sub_4E66B0(0);
    (*(void (/*thiscall*/ **)(int, float *, float *, int, int, int))(v25 + 716))(v18, &v85, &v82, v26, v76, 3);
    *(float *)&a7 = (1.0 - v85 - v82) * *(float *)&a7;
    v27 = *(uint32_t *)(v86 + 12);
    if ( v27 != 0 )
    {
      if ( v27 == 1 )
      {
        v31 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 672))(v18, 3);
        v32 = sub_4DA0B0(v31);
        v7 = v84;
        v81 = (float)v32;
        v33 = sub_433F60(v84, 6);
        *(float *)&a7 = *(float *)&a7 - v33 * v81 / flt_9A0618;
      }
      else
      {
        v7 = v84;
      }
    }
    else
    {
      v28 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 672))(v18, 3);
      v29 = sub_4DA080(v28);
      v7 = v84;
      v81 = (float)v29;
      v30 = sub_433F60(v84, 4);
      *(float *)&a7 = *(float *)&a7 - v30 * v81 / flt_9A0600;
    }
  }
  v34 = *(uint32_t *)(v86 + 12);
  if ( v34 != 0 )
  {
    if ( v34 != 1 )
      goto LABEL_37;
    v81 = (float)(*(int (/*thiscall*/ **)(int *))(*a5 + 408))(a5);
    v35 = sub_433F60(a5, 5) * v81 / flt_9A0610;
  }
  else
  {
    v81 = (float)(*(int (/*thiscall*/ **)(int *))(*a5 + 392))(a5);
    v35 = sub_433F60(a5, 3) * v81 / flt_9A05F8;
  }
  *(float *)&a7 = v35 + *(float *)&a7;
LABEL_37:
  v36 = *(uint32_t *)(v86 + 12);
  if ( v36 != 0 )
  {
    if ( v36 != 1 )
      goto LABEL_50;
    v43 = (double)*(int *)(v86 + 4);
    v44 = *(uint8_t *)(v86 + 16);
    v85 = v43;
    if ( v44 != 0 )
    {
      v81 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(*a5 + 420))(a5));
      v43 = (double)SLODWORD(v81) + v85;
    }
    v45 = *a5;
    v85 = ((double)*(int *)(v86 + 8) * 0.0099999998 + 1.0) * v43;
    v81 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(v45 + 416))(a5));
    v85 = ((double)SLODWORD(v81) * 0.0099999998 + 1.0) * v85;
    v46 = sub_433F60(a5, 9);
    *(float *)&a7 = v46 * v85 + *(float *)&a7;
    if ( v18 == 0 || *(uint8_t *)(v86 + 82) != 0 )
      goto LABEL_50;
    v47 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 672))(v18, 3);
    v42 = sub_41A5E0(v47 + 1180);
    v79 = 10;
  }
  else
  {
    v37 = (double)*(int *)(v86 + 4);
    v38 = *(uint8_t *)(v86 + 16);
    v85 = v37;
    if ( (uint8_t)v38 != 0 )
    {
      v81 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(*a5 + 404))(a5));
      v37 = (double)SLODWORD(v81) + v85;
    }
    v39 = *a5;
    v85 = ((double)*(int *)(v86 + 8) * 0.0099999998 + 1.0) * v37;
    v81 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(v39 + 400))(a5));
    v85 = ((double)SLODWORD(v81) * 0.0099999998 + 1.0) * v85;
    v40 = sub_433F60(a5, 7);
    *(float *)&a7 = v40 * v85 + *(float *)&a7;
    if ( v18 == 0 || *(uint8_t *)(v86 + 82) != 0 )
      goto LABEL_50;
    v41 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 672))(v18, 3);
    v42 = sub_41A5E0(v41 + 1138);
    v79 = 8;
  }
  v81 = *(float *)&v42;
  v48 = sub_433F60(v7, v79);
  *(float *)&a7 = *(float *)&a7 - v48 * (double)SLODWORD(v81);
LABEL_50:
  if ( *(float *)&a7 < 0.0 )
    *(float *)&a7 = 0.0;
  v49 = *a5;
  v85 = *(float *)(v86 + 72) + 3.0;
  if ( (*(int (/*thiscall*/ **)(int *))(v49 + 576))(a5) != 0 )
  {
    if ( *(uint32_t *)(v86 + 12) != 0 )
    {
      v52 = (*(int (/*thiscall*/ **)(int *))(*a5 + 576))(a5);
      v51 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v52 + 672))(v52, 3) + 1222;
    }
    else
    {
      v50 = (*(int (/*thiscall*/ **)(int *))(*a5 + 576))(a5);
      v51 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v50 + 672))(v50, 3) + 1208;
    }
    v81 = COERCE_FLOAT(sub_41A5E0(v51));
    v85 = v81 + v85;
  }
  if ( (uint8_t)sub_4E5AF0(v7, a5) != 0 )
  {
    v53 = *a5;
    v85 = v85 + *(float *)(v86 + 144);
    if ( (*(int (/*thiscall*/ **)(int *))(v53 + 576))(a5) != 0 )
    {
      if ( *(uint32_t *)(v86 + 12) != 0 )
      {
        v56 = (*(int (/*thiscall*/ **)(int *))(*a5 + 576))(a5);
        v55 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v56 + 672))(v56, 3) + 1250;
      }
      else
      {
        v54 = (*(int (/*thiscall*/ **)(int *))(*a5 + 576))(a5);
        v55 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v54 + 672))(v54, 3) + 1236;
      }
      v57 = sub_43B5A0(v55);
      v85 = v57 + v85;
    }
  }
  if ( v18 != 0 )
  {
    v58 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 672))(v18, 3);
    v81 = COERCE_FLOAT(sub_41A5E0(v58 + 1278));
    v85 = v85 - v81;
  }
  v80 = sub_4D33A0(&v83);
  LODWORD(v81) = sub_4D33A0(&v80) % 10000;
  v59 = (double)SLODWORD(v81);
  if ( v85 * 100.0 <= v59 )
  {
    *a2 = 0;
  }
  else
  {
    v59 = *(float *)&a7 * 1.5;
    *a2 = 1;
    *(float *)&a7 = v59;
  }
  v60 = (*(int (/*thiscall*/ **)(uint32_t *))(*v7 + 632))(v7);
  if ( v60 >= 50 || (*(int (/*thiscall*/ **)(int *))(*a5 + 576))(a5) == v7[143] )
  {
    *a3 = 0;
    v7[144] = 1;
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*a5 + 576))(a5) != 0 )
  {
    v61 = (*(int (/*thiscall*/ **)(int *))(*a5 + 576))(a5);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v61 + 40))(v61, 273) == 1 )
    {
      if ( v60 >= 20 )
      {
        sub_4049C0(200.0, 100.0, v60, 50);
        v63 = v59 * 0.0099999998;
        *(float *)&a7 = *(float *)&a7 * v63;
        *a3 = (uint64_t)(v63 * *(float *)&a7 - *(float *)&a7);
      }
      else if ( rand() % 100 < 1 )
      {
        v62 = *(float *)&a7 + *(float *)&a7;
        *(float *)&a7 = v62;
        *a3 = (uint64_t)v62;
      }
      v64 = v7[144] + 1;
      v65 = v7[144] - 3 < 0;
      v7[144] = v64;
      if ( v65 == __OFSUB__(v64, 4) )
        v64 = 4;
      v7[144] = v64;
      sub_4278D0(1, v64);
      v66 = (*(int (/*thiscall*/ **)(int *))(*a5 + 576))(a5);
      v67 = __RTDynamicCast(v66, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
      v68 = v67;
      if ( v67 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v67 + 308))(v67) != 0 )
      {
        v69 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v68 + 52))(v68);
        sub_495A70(dword_99FD58, 1, 1, v69);
      }
    }
  }
  *(float *)&a7 = *(float *)&a7 * *(float *)(v86 + 148) * 0.0099999998 * (double)a4 * 0.0099999998;
  if ( (uint8_t)sub_4DAB60(16) != 0 )
    *(float *)&a7 = *(float *)&a7 * *(float *)(v86 + 84) * 0.0099999998;
  if ( (uint8_t)sub_4DAB60(17) != 0 )
    *(float *)&a7 = *(float *)&a7 * *(float *)(v86 + 88) * 0.0099999998;
  if ( *(float *)&a7 < 1.0 )
    *(float *)&a7 = 1.0;
  v70 = (*(int (/*thiscall*/ **)(uint32_t *))(*v7 + 576))(v7);
  v71 = __RTDynamicCast(v70, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
  if ( v71 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v71 + 308))(v71) != 0 )
  {
    for ( i = 0; i < 18; ++i )
    {
      if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v71 + 792))(v71, i) != 0 )
      {
        v73 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v71 + 792))(v71, i);
        (*(void (/*thiscall*/ **)(int, int *, float *, uint32_t, int *))(*(uint32_t *)v73 + 164))(
          v73,
          a5,
          a6,
          (uint8_t)*a2,
          &a7);
      }
    }
  }
  return (uint64_t)*(float *)&a7;
}


// ------------------------------------------------------------
// 0x4E6FD0 sub_4E6FD0
// ------------------------------------------------------------
void /*thiscall*/ sub_4E6FD0(uint32_t *this, int a2)
{
  unsigned int i; // edi
  int v4; // ecx

  for ( i = 0; ; ++i )
  {
    v4 = *(this + 164);
    if ( v4 == 0 || i >= (*(this + 165) - v4) >> 2 )
      break;
    if ( *(uint32_t *)(v4 + 4 * i) == a2 )
    {
      memcpy_0(
        (void *)(*(this + 164) + 4 * i),
        (const void *)(*(this + 164) + 4 * i + 4),
        4 * ((int)(*(this + 165) - (*(this + 164) + 4 * i + 4)) >> 2));
      *(this + 165) -= 4;
    }
  }
}



// ------------------------------------------------------------
// 0x4E7040 sub_4E7040
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E7040(uint32_t *this, int a2)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax

  v3 = (uint32_t *)*(this + 84);
  result = (uint32_t *)*(this + 83);
  if ( result != v3 )
  {
    do
    {
      if ( *result == a2 )
        break;
      ++result;
    }
    while ( result != v3 );
    if ( result != v3 )
    {
      memcpy_0(result, result + 1, 4 * ((*(this + 84) - (int)(result + 1)) >> 2));
      *(this + 84) -= 4;
      return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 468))(this, a2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E70B0 sub_4E70B0
// ------------------------------------------------------------
int /*cdecl*/ sub_4E70B0(int a1, size_t *a2, char *a3)
{
  size_t *v3; // eax
  size_t v5; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  int v7; // [esp+1Ch] [ebp-18h]
  unsigned int v8; // [esp+20h] [ebp-14h]
  int v9; // [esp+24h] [ebp-10h]
  int v10; // [esp+30h] [ebp-4h]

  v9 = 0;
  v8 = 15;
  v7 = 0;
  LOBYTE(Block) = 0;
  sub_4014D0(&v5, a2, 0, 0xFFFFFFFF);
  v10 = 0;
  v3 = sub_4022F0((std::_String_base *)&v5, (int)a3, a3, strlen(a3));
  *(uint32_t *)(a1 + 24) = 15;
  *(uint32_t *)(a1 + 20) = 0;
  *(uint8_t *)(a1 + 4) = 0;
  sub_4014D0((size_t *)a1, v3, 0, 0xFFFFFFFF);
  if ( v8 >= 0x10 )
    j__free(Block);
  return a1;
}



// ------------------------------------------------------------
// 0x4E7160 sub_4E7160 —— 受击/动作字段复位（研究 §1.2 字段表坐标逐个可读）
// 置位分布（本工程研究文档字段表交叉验证）：
//   this+96 = 1（动作子对象存在标志）
//   this+572 = 0 / **this+568 = −1（★ 最后受击时刻复位 —— 研究 §1.1 字段表 +568）**
//   this+576 = 1（车主/归属 id 哨兵）/ +580/+584 = 0 / +588/+592 = −1
//   this+608 = 0（**受击盒使能** —— 研究 P35：this+641 是另一路；+608 见 P29 攻防门）
//   **this+636 = 0（★ 反应优先级复位 —— 研究 §15 三层状态的优先级字段）**
//   **this+642 = 0（★ 碰撞盒快照标志，§1.2 表现壳的 this+642/644）** / +644 = 0（盒快照槽）
//   this+668/+672 = 0
//   **this+612 = 1（★ 动作使能字节 —— 研究 §1.2 vt+556 = 该字节 setter、setState 门）**
//   **this+616 = −1（★ 反应态复位为 −1 哨兵 —— 研究 §15 反应态字段）**
//   **this+640 = 1（★ 攻击盒使能 —— 研究 P29 攻/防使能门 vt+600/608 = this+640/641）**
//   **this+641 = 1（★ 受击盒使能 = 无敌开关 —— 研究 P35 vt+604 广播目标）**
// 返回 −1（"未初始化/无参照"哨兵）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7160(int this)
{
  *(uint32_t *)(this + 96) = 1;
  sub_4015C0((void *)szPassword, 0);
  *(uint32_t *)(this + 572) = 0;
  *(uint32_t *)(this + 568) = -1;
  *(uint32_t *)(this + 576) = 1;
  *(uint32_t *)(this + 580) = 0;
  *(uint32_t *)(this + 584) = 0;
  *(uint32_t *)(this + 588) = -1;
  *(uint32_t *)(this + 592) = -1;
  *(uint32_t *)(this + 608) = 0;
  *(uint32_t *)(this + 636) = 0;
  *(uint8_t *)(this + 642) = 0;
  *(uint32_t *)(this + 644) = 0;
  *(uint32_t *)(this + 668) = 0;
  *(uint32_t *)(this + 672) = 0;
  *(uint8_t *)(this + 612) = 1;
  *(uint32_t *)(this + 616) = -1;
  *(uint8_t *)(this + 640) = 1;
  *(uint8_t *)(this + 641) = 1;
  return -1;
}



// ------------------------------------------------------------
// 0x4E7200 sub_4E7200
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E7200(uint32_t *this, uint32_t *a2, char a3, uint32_t *a4, int a5)
{
  int v6; // ecx
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  uint32_t *v10; // eax
  int v11; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  void **pExceptionObject; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v17[20]; // [esp+34h] [ebp-28h] BYREF
  int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]
  int v21; // [esp+70h] [ebp+14h]

  if ( *(this + 2) >= 0x1FFFFFFEu )
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);
    v20 = 0;
    sub_401740(v17);
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  v6 = sub_5648C0(*(this + 1), a4, *(this + 1), a5, 0);
  v7 = (uint32_t *)*(this + 1);
  v21 = v6;
  ++*(this + 2);
  if ( a4 == v7 )
  {
    v7[1] = v6;
    *(uint32_t *)*(this + 1) = v6;
    *(uint32_t *)(*(this + 1) + 8) = v6;
  }
  else if ( a3 != 0 )
  {
    *a4 = v6;
    v8 = (uint32_t *)*(this + 1);
    if ( a4 == (uint32_t *)*v8 )
      *v8 = v6;
  }
  else
  {
    a4[2] = v6;
    v9 = *(this + 1);
    if ( a4 == *(uint32_t **)(v9 + 8) )
      *(uint32_t *)(v9 + 8) = v6;
  }
  v10 = (uint32_t *)(v6 + 4);
  v11 = v6;
  if ( *(uint8_t *)(*(uint32_t *)(v6 + 4) + 20) == 0 )
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
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_433130(*v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 20) = 0;
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_4296E0(*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 20) = 0;
        sub_433130(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 20) != 0 )
      {
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4E73B0 sub_4E73B0 —— ★ 出生/复活重置（研究 P35 第 31 轮定案）
// 研究原文："0x4E7160/4E73B0 = 出生/复活重置（**全状态归零 + 双盒使能**）"。
// 反编译体逐条对应：
//   sub_498C40(this)（基类复位）+ **sub_4A3450(this+97)（★ 攻击上下文默认值，研究 P29：
//     "sub_4B2970/4A3450 = 攻击上下文拷贝/默认值（盒半宽17、量程100.0f）"）**
//   vt+352（动作状态复位）/ **+612 = 1（动作使能）** / vt+572（？）/ **vt+596(this, 1)**
//   / **vt+604(this, 1)（★ 双盒使能之一 —— 与 P35 "死亡无敌 vt+604(0)" 对照，
//     复活时置 1 = 恢复受击）** / vt+612(this, 0, 0)
//   +142 = −1 / +143 = 0（**★ 最后受击时刻 +568 / 仇人 id +572 复位，
//     与 0x4D4A80/0x4E48D0 写入点成对**）
//   +145/+146/+147/+148 = 0/0/−1/−1（★ 位置采样双缓冲复位，与 0x4E5410 采样对成对）
// 调用点 = 0x4D6970（角色出生/复活初始化，本工程 combat_core.cpp）
//   与 0x4E4430 的 Boss 终局（vt+604(0) 死亡无敌）互为对偶 ✅
// ------------------------------------------------------------
int /*thiscall*/ sub_4E73B0(int *this)
{
  int v2; // edx

  sub_498C40(this);
  sub_4A3450(this + 97);
  (*(void (/*thiscall*/ **)(int *))(*this + 352))(this);
  v2 = *this;
  *((uint8_t *)this + 612) = 1;
  (*(void (/*thiscall*/ **)(int *))(v2 + 572))(this);
  (*(void (/*thiscall*/ **)(int *, int))(*this + 596))(this, 1);
  (*(void (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);
  *(this + 142) = -1;
  *(this + 143) = 0;
  *(this + 145) = 0;
  *(this + 147) = -1;
  *(this + 146) = 0;
  *(this + 148) = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x4E7440 sub_4E7440 —— ★ 攻击上下文设置 vmt158（研究 P29 定案）
// 已精修版见 src/cnrd/IRDCollisionObject.cpp:213（0x4E7440 vmt158）。
// 研究 P29 原文："sub_4B2970/4A3450 = 攻击上下文拷贝/默认值（盒半宽17、量程100.0f）"
// —— 本函数即该族入口：a2 非空 → sub_4B2970（拷贝）；否则 sub_4A3450(this+388)（取默认）
// → 尾调 vt+352（动作状态复位）。this+388 = 攻击上下文结构（研究 §13 观察者接口
// "+128 攻击开始（收攻击上下文 this+388）"）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7440(char *this, int a2)
{
  char *v3; // ecx

  v3 = this + 388;
  if ( a2 != 0 )
    sub_4B2970(a2);
  else
    sub_4A3450(v3);
  return (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 352))(this);
}



// ------------------------------------------------------------
// 0x4E7480 sub_4E7480
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7480(int this, int a2)
{
  int v2; // ebx
  int result; // eax
  int *v5; // [esp+8h] [ebp-4h] BYREF

  v2 = a2;
  sub_499190((uint32_t *)this, a2);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 40))(v2, 1) != 0 )
    sub_4E6FD0((uint32_t *)this, v2);
  sub_4BE520((int **)(this + 540), &v5, &a2);
  if ( v5 != *(int **)(this + 544) )
    sub_4A3130((uint32_t *)(this + 540), (int ***)&v5, (int **)v5);
  sub_4BE520((int **)(this + 596), &v5, &a2);
  if ( v5 != *(int **)(this + 600) )
    sub_4A3130((uint32_t *)(this + 596), (int ***)&a2, (int **)v5);
  result = 0;
  if ( *(uint32_t *)(this + 572) == v2 )
    *(uint32_t *)(this + 572) = 0;
  if ( *(uint32_t *)(this + 668) == v2 )
    *(uint32_t *)(this + 668) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4E7530 sub_4E7530
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7530(uint32_t *this, int a2, uint32_t *a3)
{
  uint32_t *v3; // ebx
  uint32_t *v5; // esi
  int *v6; // eax
  bool v7; // cl
  unsigned int v8; // edx
  uint32_t *v9; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  v3 = a3;
  v5 = (uint32_t *)*(this + 1);
  v6 = (int *)v5[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )
  {
    v8 = *a3;
    do
    {
      v7 = v8 < v6[3];
      v5 = v6;
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 21) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_4E7200(this, &a3, 1, v5, (int)v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_4A3B30(&a3);
    v9 = a3;
  }
  if ( v9[3] >= *v3 )
  {
    *(uint8_t *)(a2 + 4) = 0;
    *(uint32_t *)a2 = v9;
    return a2;
  }
  else
  {
    v12 = *sub_4E7200(this, &a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4E75F0 sub_4E75F0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4E75F0(int this, int Src, unsigned int a3, int *a4)
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
      sub_4A30C0(this);
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
// 0x4E77D0 sub_4E77D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E77D0(int this, int a2)
{
  int v3; // ecx
  unsigned int v4; // edx
  void *v6; // ecx
  unsigned int v7; // ebx
  int v8; // eax
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // eax
  void *v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t *)(a2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(a2 + 8) - v3) >> 2) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  v6 = *(void **)(this + 4);
  if ( v6 != nullptr )
    v7 = (*(uint32_t *)(this + 8) - (int)v6) >> 2;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    memcpy_0(v6, *(const void **)(a2 + 4), 4 * ((*(uint32_t *)(a2 + 8) - *(uint32_t *)(a2 + 4)) >> 2));
    v8 = *(uint32_t *)(a2 + 4);
    if ( v8 != 0 )
      v9 = *(uint32_t *)(this + 4) + 4 * ((*(uint32_t *)(a2 + 8) - v8) >> 2);
    else
      v9 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = v9;
    return this;
  }
  if ( v6 != nullptr )
    v10 = (*(uint32_t *)(this + 12) - (int)v6) >> 2;
  else
    v10 = 0;
  if ( v4 > v10 )
  {
    if ( v6 != nullptr )
      j__free(*(void **)(this + 4));
    v13 = *(uint32_t *)(a2 + 4);
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(a2 + 8) - v13) >> 2;
    else
      v14 = 0;
    if ( (uint8_t)sub_42CFD0(v14) != 0 )
      *(uint32_t *)(this + 8) = sub_55E7F0(*(void **)(a2 + 4), *(uint32_t *)(a2 + 8), *(void **)(this + 4));
    return this;
  }
  if ( v6 != nullptr )
    v11 = (*(uint32_t *)(this + 8) - (int)v6) >> 2;
  else
    v11 = 0;
  v12 = (void *)(*(uint32_t *)(a2 + 4) + 4 * v11);
  sub_433A30(*(void **)(a2 + 4), (int)v12, *(void **)(this + 4));
  *(uint32_t *)(this + 8) = sub_55E7F0(v12, *(uint32_t *)(a2 + 8), *(void **)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x4E7920 sub_4E7920
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E7920(int this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v6; // eax
  uint32_t *v7; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_4E7200((uint32_t *)this, a2, 1, *(uint32_t **)(this + 4), (int)a4);
    return a2;
  }
  v6 = *(uint32_t **)(this + 4);
  v7 = a4;
  if ( a3 == (uint32_t *)*v6 )
  {
    if ( *a4 < a3[3] )
    {
      sub_4E7200((uint32_t *)this, a2, 1, a3, (int)a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( a3 == v6 )
  {
    v8 = (uint32_t *)v6[2];
    if ( v8[3] < *a4 )
    {
      sub_4E7200((uint32_t *)this, a2, 0, v8, (int)a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( *a4 >= a3[3] || (a4 = a3, sub_4A3B30(&a4), a4[3] >= *v7) )
  {
    if ( a3[3] >= *v7 || (a4 = a3, sub_41C5E0(&a4), a4 != *(uint32_t **)(this + 4)) && *v7 >= a4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4E7530(v10, v7);
      *a2 = v9;
      return a2;
    }
    if ( *(uint8_t *)(a3[2] + 21) != 0 )
      sub_4E7200((uint32_t *)this, a2, 0, a3, (int)v7);
    else
      sub_4E7200((uint32_t *)this, a2, 1, a4, (int)v7);
    return a2;
  }
  else
  {
    if ( *(uint8_t *)(a4[2] + 21) != 0 )
      sub_4E7200((uint32_t *)this, a2, 0, a4, (int)v7);
    else
      sub_4E7200((uint32_t *)this, a2, 1, a3, (int)v7);
    return a2;
  }
}



// ============================================================
// 【分区 D】受击反应 / 命中特效生成 / 本地扫掠（0x4E7A80 - 0x4E9760）
//   ★ 研究 20 三条主链的落点：setState（三层状态）→ 本地扫掠（先于服务端包）
//   → HITEFF/CRITHIT/UNIONHIT（表现层全要素）。
// ============================================================

// ------------------------------------------------------------
// 0x4E7A80 sub_4E7A80 —— ★★★ 受击反应 setState / vt+560（研究 20 §1.2/§15 定案）
// 签名：__thiscall(this = 受击者, a2 = 反应态 id, a3 = 打包参数对象, a4 = 优先级, a5 = 强制位)
// 研究 §15 定案（三层状态架构）：`this+616` = 反应态、`this+636` = 优先级，
//   **"反应优先级仲裁 vt+560 sub_4E7A80（只升不降）"**。
// 转写体与研究定案的逐条对应：
//   门① `this[612] != 0`（动作使能字节，研究 §1.2 vt+556 = 该字节的 setter（setState 门））
//   门② `vt+308 != 0 || a5 != 0`（本地玩家对象 或 强制）
//   门③ `(条件 529 == 0) || (this+616 != 5)` —— 研究 §15/§14：529 与状态 5（击倒）特例
//   门④ `*(this+154) == -1 || *(this+159) <= a4` —— ★ **只升不降仲裁本体**
//        （word 下标 154 = 字节 +616 当前反应态；159 = 字节 +636 当前优先级）
//   命中后：`this[154] = a2`（写反应态）+ `this[613] = 0`（清"已上报"标志，
//        配合 0x4E8130 的位移同步包）+ a3 非空 → sub_4ED3F0(this+620, a3) 装载参数
//        （否则 sub_5E5260 清空）+ `this[159] = a4`（写优先级）
// 调用点（研究 §2⑧ 受击反应三档，全部走本函数）：
//   state 3 受击硬直动作（左右方向随机、动作速度 = attackinfo+136，-1→1.0，
//           attackinfo+12==1 时 ×0.7）
//   state 4 击退（距离 = attackinfo+64，浮空 = attackinfo+68 + 暴击加成 +50/+250）
//   state 5 击倒（档位：距离 < 150 时看浮空（< 400 → 2 否则 5）；否则按相对站位 3）
// ⚠ 参数对应注（研究 §2⑧ 的写法 → 本转写体形参）：
//    研究写 `vt+560(this, 3, 打包参数, 优先级2)`，其中第 2 实参 3 = 反应态 → 本处 **a2**，
//    第 3 实参 = 打包参数 → 本处 **a3**，第 4 实参 = 优先级 → 本处 **a4**。
//    转写体实测：`*(this+154)=a2`（写反应态）、`*(this+159)=a4`（写优先级）—— 吻合。
// ------------------------------------------------------------
void /*thiscall*/ sub_4E7A80(uint32_t *this, int a2, int a3, int a4, char a5)
{
  void *v6; // ecx

  if ( *((uint8_t *)this + 612) != 0
    && ((*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 || a5 != 0)
    && ((*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 529) == 0 || *(this + 154) != 5)
    && (*(this + 154) == -1 || *(this + 159) <= a4) )
  {
    *(this + 154) = a2;
    *((uint8_t *)this + 613) = 0;
    v6 = this + 155;
    if ( a3 != 0 )
      sub_4ED3F0((int)v6, a3);
    else
      sub_5E5260(v6);
    *(this + 159) = a4;
  }
}



// ------------------------------------------------------------
// 0x4E7B20 sub_4E7B20
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7B20(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  v2 = (uint32_t *)*(this + 1);
  v3 = (int *)v2[1];
  while ( *((uint8_t *)v3 + 21) == 0 )
  {
    if ( (unsigned int)v3[3] >= *a2 )
    {
      v2 = v3;
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  if ( v2 != (uint32_t *)*(this + 1) && *a2 >= v2[3] )
    return (int)(v2 + 4);
  v5[0] = *a2;
  v5[1] = 0;
  return *sub_4E7920((int)this, &a2, v2, v5) + 16;
}



// ------------------------------------------------------------
// 0x4E7BA0 sub_4E7BA0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4E7BA0(int *this, int *a2)
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
    return sub_4E75F0((int)this, *(this + 2), 1u, a2);
  v4 = (int *)*(this + 2);
  *v4 = *a2;
  result = (unsigned int)(v4 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4E7BF0 sub_4E7BF0 —— ★ 变长整数编码器（VLQ / 7 bit × n；网络序列化基元）
// 结构：`< 0x80` → 单字节直接写（或 sub_446710 追加）；`>= 0x80` 逐段：
//   每 7 bit 一组，低位组尾或 0x80 续位标志，从高到低 sub_446BE0 逐字节写出
//   （0x4000 / 0x200000 / 0x10000000 三段阈值 → 2/3/4/5 字节编码）。
// 研究 P31/P35 的 UDP 包序列化族基元（与位移序列化 sub_4E80E0 → sub_48D1E0 配合）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7BF0(int this, unsigned int a2)
{
  int result; // eax
  int v4; // edx
  unsigned int v5; // edi
  uint8_t *v6; // ecx
  unsigned int v7; // ecx
  unsigned int v8; // edx
  unsigned int v9; // ecx
  unsigned int v10; // edx
  char v11; // [esp+4h] [ebp-4h] BYREF
  char v12; // [esp+5h] [ebp-3h] BYREF
  char v13; // [esp+6h] [ebp-2h] BYREF
  char v14; // [esp+7h] [ebp-1h] BYREF

  result = a2;
  if ( a2 >= 0x80 )
  {
    if ( a2 >= 0x4000 )
    {
      if ( a2 >= 0x200000 )
      {
        if ( a2 >= 0x10000000 )
        {
          v11 = a2 & 0x7F;
          v9 = a2;
          v14 = (a2 >> 7) | 0x80;
          v10 = a2 >> 21;
          HIBYTE(a2) = (a2 >> 28) | 0x80;
          v13 = (v9 >> 14) | 0x80;
          v12 = v10 | 0x80;
          sub_446BE0((char *)&a2 + 3);
          sub_446BE0(&v12);
          sub_446BE0(&v13);
          sub_446BE0(&v14);
          return sub_446BE0(&v11);
        }
        else
        {
          v12 = a2 & 0x7F;
          v7 = a2;
          v8 = a2 >> 14;
          HIBYTE(a2) = (a2 >> 21) | 0x80;
          v14 = (v7 >> 7) | 0x80;
          v13 = v8 | 0x80;
          sub_446BE0((char *)&a2 + 3);
          sub_446BE0(&v13);
          sub_446BE0(&v14);
          return sub_446BE0(&v12);
        }
      }
      else
      {
        v13 = a2 & 0x7F;
        v14 = (a2 >> 7) | 0x80;
        HIBYTE(a2) = (a2 >> 14) | 0x80;
        sub_446BE0((char *)&a2 + 3);
        sub_446BE0(&v14);
        return sub_446BE0(&v13);
      }
    }
    else
    {
      HIBYTE(a2) = (a2 >> 7) | 0x80;
      v14 = a2 & 0x7F;
      sub_446BE0((char *)&a2 + 3);
      return sub_446BE0(&v14);
    }
  }
  else
  {
    v4 = *(uint32_t *)(this + 4);
    HIBYTE(a2) = a2;
    if ( v4 != 0 )
      v5 = *(uint32_t *)(this + 8) - v4;
    else
      v5 = 0;
    if ( v4 != 0 && v5 < *(uint32_t *)(this + 12) - v4 )
    {
      v6 = *(uint8_t **)(this + 8);
      *v6 = result;
      *(uint32_t *)(this + 8) = v6 + 1;
    }
    else
    {
      return sub_446710(*(void **)(this + 8), 1, (int)&a2 + 3);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E7DA0 sub_4E7DA0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7DA0(uint32_t *this, int a2)
{
  int result; // eax
  int v3; // ebx
  int v4; // edi
  int v5; // esi
  char v6; // al
  int v7; // edx
  unsigned int v8; // ecx
  int *v9; // eax
  uint32_t *v10; // [esp+8h] [ebp-8h]
  int v11; // [esp+Ch] [ebp-4h]

  result = *(this + 1);
  v3 = 0;
  v4 = 0;
  v10 = this;
  if ( result != 0 )
    v11 = *(this + 2) - result;
  else
    v11 = 0;
  if ( v11 > 0 )
  {
    v5 = a2;
    do
    {
      v6 = *(uint8_t *)(v3 + *(this + 1));
      v4 = (v6 & 0x7F) + (v4 << 7);
      if ( v6 >= 0 )
      {
        v7 = *(uint32_t *)(v5 + 4);
        a2 = v4;
        if ( v7 != 0 )
          v8 = (*(uint32_t *)(v5 + 8) - v7) >> 2;
        else
          v8 = 0;
        if ( v7 != 0 && v8 < (*(uint32_t *)(v5 + 12) - v7) >> 2 )
        {
          v9 = *(int **)(v5 + 8);
          *v9 = v4;
          *(uint32_t *)(v5 + 8) = v9 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v5 + 8), 1, (int)&a2);
        }
        this = v10;
        v4 = 0;
      }
      result = v11;
      ++v3;
    }
    while ( v3 < v11 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E7E40 sub_4E7E40
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7E40(char *this, int a2)
{
  char *v2; // ecx
  int v3; // esi
  unsigned int v4; // edx
  int *v5; // eax
  int result; // eax

  v2 = this + 652;
  v3 = *((uint32_t *)v2 + 1);
  if ( v3 != 0 )
    v4 = (*((uint32_t *)v2 + 2) - v3) >> 2;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*((uint32_t *)v2 + 3) - v3) >> 2 )
    return sub_428220(*((void **)v2 + 2), 1, (int)&a2);
  v5 = *((int **)v2 + 2);
  *v5 = a2;
  result = (int)(v5 + 1);
  *((uint32_t *)v2 + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4E7EA0 sub_4E7EA0 —— ★★ 1000ms 重复命中节流（研究 P29 第 24/25 轮定案）
// 研究 P29 原文："**sub_4E7EA0 = 1000ms 重复命中节流（同一挥击不重复打）**"。
// 转写体与定案逐条对应：
//   若 `*a2 != 0`（a2 为"节流表节点"指针，指向命中记录）：
//     先 sub_4BE520(&a2, &a3)（表内查找/定位）；
//     若 a2 != 表首（this+150）
//        且 `now − *(node+4) >= 1000`（★ 距上次记录 ≥ 1000ms）→
//           `*v3 = 0`（清调用方标志）+ 更新 `*(node+4) = now`（★ 刷新节流时间戳）
//   否则（首次）→ `sub_4E7B20(&a3)` 查/建节点 → `*node = now`
// 调用点：本地扫掠 0x4E82B0（`sub_4E7EA0((char*)&a3+3, v5)`）——
//   研究 §11 第 11 轮的"命中不重复"门 ✅
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7EA0(uint32_t *this, uint8_t *a2, int a3)
{
  uint8_t *v3; // ebx
  int *v5; // edi
  int result; // eax
  uint8_t *v7; // edi
  int v8; // esi

  v3 = a2;
  if ( *a2 != 0 )
  {
    result = sub_4BE520(&a2, &a3);
    v7 = a2;
    if ( a2 != (uint8_t *)*(this + 150) )
    {
      v8 = (int)(this + 9);
      result = sub_699000(v8) - *((uint32_t *)v7 + 4);
      if ( result >= 1000 )
      {
        *v3 = 0;
        result = sub_699000(v8);
        *((uint32_t *)v7 + 4) = result;
      }
    }
  }
  else
  {
    v5 = (int *)sub_4E7B20(&a3);
    result = sub_699000((int)(this + 9));
    *v5 = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E7F30 sub_4E7F30
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7F30(uint32_t *this, signed int a2, signed int a3, int a4)
{
  unsigned int i; // edi
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // esi
  int j; // edi
  int v15; // edi
  int v16; // edi
  int v18; // ecx
  int v19; // [esp+Ch] [ebp-8h] BYREF
  unsigned int v20; // [esp+10h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    v6 = *(this + 29);
    v7 = *(uint32_t *)(v6 + 120);
    v20 = i;
    if ( v7 != 0 )
      v8 = (*(uint32_t *)(v6 + 124) - v7) >> 2;
    else
      v8 = 0;
    if ( (int)i >= v8 )
    {
      if ( a4 != 0 && (v18 = *(uint32_t *)(a4 + 4)) != 0 && (*(uint32_t *)(a4 + 8) - v18) >> 2 != 0 )
        return *(uint32_t *)v18;
      else
        return 0;
    }
    v9 = *(uint32_t *)(v6 + 120);
    if ( v9 != 0 && i < (*(uint32_t *)(v6 + 124) - v9) >> 2 )
      v10 = *(uint32_t *)(v9 + 4 * i);
    else
      v10 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 40))(v10, 17) != 0 )
    {
      v11 = *(this + 29);
      v12 = *(uint32_t *)(v11 + 120);
      if ( v12 != 0 && i < (*(uint32_t *)(v11 + 124) - v12) >> 2 )
        v13 = *(uint32_t *)(v12 + 4 * i);
      else
        v13 = 0;
      v19 = v13;
      if ( (uint8_t)sub_4E4630(v13) != 0 )
        break;
    }
LABEL_25:
    ;
  }
  for ( j = 200; j < 205; ++j )
  {
    if ( j == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 376))(v13) )
      goto LABEL_24;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 940))(v13) != 0
    || (v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 120))(v13),
        (int)abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v15) > a2)
    || (v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 124))(v13),
        (int)abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - v16) > a3) )
  {
LABEL_24:
    i = v20;
    goto LABEL_25;
  }
  if ( a4 != 0 )
  {
    sub_4E7BA0(&v19);
    goto LABEL_24;
  }
  return v13;
}



// ------------------------------------------------------------
// 0x4E8080 sub_4E8080
// ------------------------------------------------------------
char /*thiscall*/ sub_4E8080(uint32_t *this, int a2, char a3)
{
  uint32_t *v4; // ecx
  uint32_t *v5; // eax
  int v6; // edi

  v4 = (uint32_t *)*(this + 84);
  v5 = (uint32_t *)*(this + 83);
  v6 = a2;
  if ( v5 == v4 )
    goto LABEL_5;
  do
  {
    if ( *v5 == a2 )
      break;
    ++v5;
  }
  while ( v5 != v4 );
  if ( v5 == v4 )
  {
LABEL_5:
    sub_431230((int)(this + 82), &a2);
    LOBYTE(v5) = a3;
    if ( a3 != 0 )
      LOBYTE(v5) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 464))(this, v6);
  }
  return (char)v5;
}



// ------------------------------------------------------------
// 0x4E80E0 sub_4E80E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E80E0(void *this, int a2)
{
  int result; // eax
  int v3; // edi
  int i; // esi

  result = *(uint32_t *)(a2 + 4);
  if ( result != 0 )
    v3 = (*(uint32_t *)(a2 + 8) - result) >> 2;
  else
    v3 = 0;
  for ( i = 0; i < v3; ++i )
    result = sub_4E7BF0((int)this, *(uint32_t *)(*(uint32_t *)(a2 + 4) + 4 * i));
  return result;
}



// ------------------------------------------------------------
// 0x4E8130 sub_4E8130 —— ★ 位移同步包 vt+234（会话 3 定案：UDP type=5）
// 已精修版见 src/cnrd/IRDCollisionObject.cpp（vmt234 位移同步包段落）。
// 会话 3 定案原文："vmt234 位移同步包（0x4E8130）：**UDP type=5**，双 id +
//   位移序列化（sub_4E80E0）"。
// 转写体逐条对应：
//   门：`a1[613] == 0`（未上报）且 `a1+616(反应态) != −1`
//   → 打包站 `type 5, 2 子字段`；写 本体 id（vt+48/vt+52 即子 id 对）
//     + **本地玩家 dword_8F7C04 的 id 对**（对端） + `a1[616]` 反应态
//   → **sub_4E80E0(v18, a1+620)**（★ 位移序列化，会话 3 定案）→ sub_48D1E0 取缓冲长度
//   → 逐字节 vt+32 压入 → 提交 vt+60(1, −1) → `a1[613] = 1`（置已上报）
// ✅ 与 0x4E7A80 的 `this[613] = 0`（清已上报）成对 —— 反应态一变就补发位移。
// ------------------------------------------------------------
void /*usercall*/ sub_4E8130(uint8_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // edi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int v11; // eax
  unsigned int v12; // ebx
  uint8_t *v13; // edi
  int v14; // eax
  int v15; // [esp+4h] [ebp-2Ch] BYREF
  void *Block; // [esp+8h] [ebp-28h]
  int v17; // [esp+Ch] [ebp-24h]
  uint8_t v18[4]; // [esp+14h] [ebp-1Ch] BYREF
  void *v19; // [esp+18h] [ebp-18h]
  int v20; // [esp+1Ch] [ebp-14h]
  int v21; // [esp+20h] [ebp-10h]
  int v22; // [esp+2Ch] [ebp-4h]

  if ( a1[613] == 0 && *((uint32_t *)a1 + 154) != -1 )
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 5, 2, a3, a2);
    v4 = *(uint32_t *)dword_8F8520;
    v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 48))(a1);
    (*(void (/*thiscall*/ **)(int, int))(v4 + 36))(dword_8F8520, v5);
    v6 = *(uint32_t *)dword_8F8520;
    v7 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 52))(a1);
    (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, v7);
    v8 = *(uint32_t *)dword_8F8520;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 48))(dword_8F7C04);
    (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);
    v10 = *(uint32_t *)dword_8F8520;
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
    (*(void (/*thiscall*/ **)(int, int))(v10 + 36))(dword_8F8520, v11);
    (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 32))((uint8_t)a1[616]);
    v12 = 0;
    v19 = nullptr;
    v20 = 0;
    v21 = 0;
    v22 = 0;
    sub_4E80E0(v18, (int)(a1 + 620));
    sub_48D1E0(&v15, (int)v18);
    v13 = (uint8_t *)Block;
    LOBYTE(v22) = 1;
    if ( Block != nullptr )
      v14 = v17 - (uint32_t)Block;
    else
      v14 = 0;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v14);
    while ( v13 != nullptr && v12 < v17 - (int)v13 )
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 32))(v13[v12++]);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    a1[613] = 1;
    if ( v13 != nullptr )
      j__free(v13);
    if ( v19 != nullptr )
      j__free(v19);
  }
}



// ------------------------------------------------------------
// 0x4E82B0 sub_4E82B0 —— ★★★ 本地扫掠 / vt+476（研究 20 §1.2/§11 第 11 轮定案）
// 签名：__thiscall(this = 攻击者, a3 = 目标对象)（userpurge 寄存器形式）
// 研究 §1.2/§11 原文："**vt+476 槽** 在攻击动作活动帧做**客户端本地多命中盒碰撞**
//   （vt+480 = sub_4D6A80 主盒+附加盒链表），命中即播 KnockSmall.ani 并冻结攻方
//   ——**先于服务端包的即时反馈**；友敌选择门 +405/406/407 对应攻击定义的
//   `[attack myself/friend/enemy]` 开关。"
// 转写体与定案的逐条对应：
//   门① `vt+308(攻) == 0 && vt+308(受) == 0` → return 0（双方都不是本地玩家对象）
//   门② `hae = vt+360(攻, 受)`（敌我关系）—— 写入 HIBYTE(a3) 备用
//        `a1[128](= 字节 +512) == 2` 为"无视敌我"模式（攻击定义 [attack myself] 族？）
//        否则 hae == 0 → return 0
//   门③ **友敌选择门（研究 §11 直证）**：
//        `*((uint8_t*)a1 + 405) == 0` 且 双方车主相同 → return 0
//        `+406 == 0` 且 sub_4E4630(受) == 0 且 车主不同 → return 0
//        `+407 == 0` 且 sub_4E4630(受) != 0 → return 0
//        —— 即研究上述 "+405/406/407 对应 [attack myself/friend/enemy]"（**逐条吻合**）
//   ④ **盒碰撞**：`v33 = vt+480(a1, 受, v27)` —— ★ vt+480 = sub_4D6A80（多命中盒），
//        v27 为 6 float 输出槽（命中点）
//   ⑤ 命中后：
//        `+512 == 2` 但本地节流未通过（sub_4E7EA0，1000ms 重复命中节流，
//          研究 P29 "sub_4E7EA0 = 1000ms 重复命中节流"）→ 走冻结分支
//        查受方 vt+648(类型, &v32=100, vt+380) == 3（落空）→ 跳过
//        否则 **vt+356(a1, 受)**（记录命中目标）+ 若受方为本地玩家对象
//          → **sub_4E5F70(a1, 受, v27, 1, 1)**（★ 硬直率掷 + 上报服务端背书，§5.1 第 14 轮）
//        随后命中特效：按区域码 `dword_8F7A24+244` 三值分支
//          0..1 → **"Common/HitEffect/Animation/KnockSmall.ani"**（研究 §11 原文
//                 "命中即播 KnockSmall.ani" —— **直证**）
//          2    → "Common/HitEffect/Animation/Age12/KnockSmall.ani"（日区和谐分支，
//                 研究 §5.2 的 Age12 族同一区域码机制）
//          → sub_4922F0(0.5)（帧率缩放 0.5）+ 池化对象 sub_44B6C0(284)
//          + sub_45FE80 入演播层 2 + 定位（受方 x + v31*0.5+v28、v29*0.5+v27[0]）
//        + **冻结攻方**（回此前的 LABEL_37 分支）：`v23 = a1[130]`（**字节 +520 =
//          攻方自身卡肉时长**，研究 §8 定案字段）> 0 且
//          （主状态 a1[50]（字节 +200）== 0 或（==1 且 vt+248 剩余硬直 < v23））→
//          **vt+228(a1, 1, v23, 0)**（与 §8 攻方自我冻结**同一入口、同一延长逻辑**）
//          —— 研究 §11 "并冻结攻方" 在此**直证**，且读的正是 this+520 ✅
// ✅ 与 §11 第 11 轮定案**逐条吻合**（含"先于服务端包的即时反馈"的时序语义）。
// 研究 §15 复用价值 #7：本地扫掠是"出招即震"的理想读点（不等服务器往返）。
// ------------------------------------------------------------
char /*userpurge*/ sub_4E82B0@<al>(uint32_t *a1@<ecx>, int a2@<ebx>, int a3)
{
  char v4; // al
  int v5; // edi
  char v6; // al
  bool v7; // zf
  int v9; // ebx
  int v10; // ebx
  int v11; // edx
  int v12; // edx
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  int v18; // ebx
  int v19; // ecx
  int v20; // ebx
  uint64_t v21; // rax
  uint64_t v22; // rax
  int v23; // edi
  int v24; // eax
  int v25; // [esp-8h] [ebp-3Ch]
  float v27[2]; // [esp+8h] [ebp-2Ch] BYREF
  float v28; // [esp+10h] [ebp-24h]
  float v29; // [esp+14h] [ebp-20h]
  int v30; // [esp+18h] [ebp-1Ch]
  float v31; // [esp+1Ch] [ebp-18h]
  int v32; // [esp+20h] [ebp-14h] BYREF
  char v33; // [esp+27h] [ebp-Dh]
  int v34; // [esp+30h] [ebp-4h]

  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
  v5 = a3;
  if ( v4 == 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 308))(a3) == 0 )
    return 0;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 360))(a1, v5);
  v7 = a1[128] == 2;
  HIBYTE(a3) = v6;
  if ( !v7 && v6 != 0 )
    return 0;
  if ( *((uint8_t *)a1 + 405) == 0 )
  {
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 576))(v5);
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 576))(a1) == v9 )
      return 0;
  }
  if ( *((uint8_t *)a1 + 406) == 0 && (uint8_t)sub_4E4630(v5) == 0 )
  {
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 576))(v5);
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 576))(a1) != v10 )
      return 0;
  }
  if ( *((uint8_t *)a1 + 407) == 0 && (uint8_t)sub_4E4630(v5) != 0 )
    return 0;
  v11 = *a1;
  v27[0] = 0.0;
  v27[1] = 0.0;
  v28 = 0.0;
  v29 = 0.0;
  v30 = 0;
  v31 = 0.0;
  v33 = (*(int (/*thiscall*/ **)(uint32_t *, int, float *))(v11 + 480))(a1, v5, v27);
  if ( v33 != 0 )
  {
    if ( a1[128] != 2 || (sub_4E7EA0((char *)&a3 + 3, v5), HIBYTE(a3) == 0) )
    {
      v12 = *a1;
      v13 = *(uint32_t *)v5;
      v32 = 100;
      v14 = (*(int (/*thiscall*/ **)(uint32_t *))(v12 + 380))(a1);
      if ( (*(int (/*thiscall*/ **)(int, int *, int))(v13 + 648))(v5, &v32, v14) != 3 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*a1 + 356))(a1, v5);
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 308))(v5) != 0 )
        {
          sub_4E5F70(a1, v5, v27, 1, 1);
          return v33;
        }
        if ( (uint8_t)sub_4AED00(a1 + 97) == 0 && a1[112] == 0 )
        {
LABEL_37:
          v23 = a1[130];
          if ( v23 > 0 )
          {
            v24 = a1[50];
            if ( v24 == 0 || v24 == 1 && (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 248))(a1) < v23 )
              (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*a1 + 228))(a1, 1, v23, 0);
          }
          return v33;
        }
        v15 = *(uint32_t *)(dword_8F7A24 + 244);
        v16 = 0;
        if ( v15 >= 0 )
        {
          if ( v15 <= 1 )
          {
            a3 = sub_42FCB0(228);
            v34 = 1;
            if ( a3 != 0 )
            {
              v17 = sub_431860((char)"Common/HitEffect/Animation/KnockSmall.ani", 1);
              goto LABEL_30;
            }
LABEL_29:
            v17 = 0;
            goto LABEL_30;
          }
          if ( v15 == 2 )
          {
            a3 = sub_42FCB0(228);
            v34 = 0;
            if ( a3 != 0 )
            {
              v17 = sub_431860((char)"Common/HitEffect/Animation/Age12/KnockSmall.ani", 1);
LABEL_30:
              v34 = -1;
              v16 = v17;
              goto LABEL_31;
            }
            goto LABEL_29;
          }
        }
LABEL_31:
        sub_4922F0(0.5);
        a3 = sub_44B6C0(284);
        v34 = 2;
        if ( a3 != 0 )
          v18 = sub_44E1F0(v16, 1);
        else
          v18 = 0;
        v19 = a1[29];
        a3 = v18;
        v34 = -1;
        sub_45FE80(v19, v5, 2, 0, v18, v5, 0);
        if ( (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 660))(a1, v5, a2) == 1 )
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v18 + 148))(v18, 0);
        v20 = *(uint32_t *)v18;
        v21 = (uint64_t)(v31 * 0.5 + v28);
        v25 = (*(int (/*fastcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)v5 + 124))(v5, HIDWORD(v21), v21);
        v22 = (uint64_t)(v29 * 0.5 + v27[0]);
        (*(void (/*fastcall*/ **)(int, uint32_t, uint32_t, int))(v20 + 112))(a3, HIDWORD(v22), v22, v25);
        goto LABEL_37;
      }
    }
    return 0;
  }
  return v33;
}


// ------------------------------------------------------------
// 0x4E85E0 sub_4E85E0 —— ★★ CRITHIT / 暴击特效 vt+520（研究 20 §5.3 全文定案）
// 触发：命中包 case 0x14 的**暴击位**（研究 §1.1："暴击位=1 → vt+520 = CRITHIT"）。
// 反编译体与 §5.3 逐条对应：
//   ① 命中点 = 盒中心：`v13 = a5[3]*0.5 + a5[0]`（x）、v14 = 受方 vt+124(盒中心 y)、
//      `v16 = a5[5]*0.5 + a5[2] + 30.0`（z 抬高 30）
//   ② **"Common/HitEffect/Animation/CriticalHit.ani"** 池化生成于命中点
//      （sub_431860 取资源 → sub_44B6C0(284) 池化对象 → sub_45FE80 入演播层 2）
//   ③ ★ **若受击者 == 玩家（dword_8F7C04）**：
//      `dword_8F8528 + 2468/2469/2470 = 1/0/0` 三个标志字节（研究 §14#5 的
//      "被暴击标志管理器 +2468 三字节在'玩家被暴击'时置位" —— **直证**）
//      + **sub_424530(1069547520=**1.5f**, 100, 150, 盒中心 x/y/z, 1)** =
//        ★ 镜头 1.5 倍缩放特写（研究 §5.3："调 sub_424530(1.5f, 100, 150, x, y, z, 1)
//        = 镜头 1.5 倍缩放特写（写相机 +1168=倍率、+1180..1188=焦点坐标；
//        系统关闭时复位 1.0）"）—— 常量 1069547520 实测 = 0x3FC00000 = 1.5f ✅
// 常量核验：1069547520 = 0x3FC00000 = **1.5f** ✅（IEEE754 单精度）；100/150 为
// 时长/缓动参数（研究 §9 提到 sub_424530(2.0f, 300, 1000, …) 用于连击二档冲击，
// 与本次 (1.5f, 100, 150, …) 同函数不同参数 —— 研究 §5.3/§9 已定案该函数为
// "镜头缩放 + 焦点"通用入口）。
// ------------------------------------------------------------
int /*userpurge*/ sub_4E85E0@<eax>(int a1@<ecx>, int a2@<ebx>, int a3@<esi>, int a4, float *a5)
{
  int result; // eax
  int v8; // edi
  uint8_t *v9; // eax
  int v12; // [esp+4h] [ebp-1Ch]
  int v13; // [esp+8h] [ebp-18h]
  int v14; // [esp+Ch] [ebp-14h]
  int v16; // [esp+28h] [ebp+8h]
  int v17; // [esp+2Ch] [ebp+Ch]

  result = *(uint32_t *)(a1 + 116);
  if ( result != 0 )
  {
    v13 = (uint64_t)(a5[3] * 0.5 + *a5);
    v14 = (*(int (/*fastcall*/ **)(int, uint32_t, int, int))(*(uint32_t *)a4 + 124))(
            a4,
            (uint64_t)(a5[3] * 0.5 + *a5) >> 32,
            a3,
            a2);
    v16 = (uint64_t)(a5[5] * 0.5 + a5[2] + 30.0);
    if ( sub_42FCB0(228) != 0 )
      v17 = sub_431860((char)"Common/HitEffect/Animation/CriticalHit.ani", 1);
    else
      v17 = 0;
    v8 = sub_44B6C0(284);
    v12 = v8;
    if ( v8 != 0 )
    {
      sub_44E0D0(v17, 1);
      *(uint32_t *)v8 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v8 = 0;
    }
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 72))(v8, 2);
    sub_45FE80(*(uint32_t *)(a1 + 116), v8, 2, 0, v8, a4, 0);
    result = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v8 + 112))(v8, v13, v14, v16, v12);
    if ( dword_8F7C04 == a1 )
    {
      v9 = dword_8F8528;
      *((uint8_t *)dword_8F8528 + 2468) = 1;
      v9[2469] = 0;
      v9[2470] = 0;
      return sub_424530(
               1069547520,
               100,
               150,
               (uint64_t)(a5[3] * 0.5 + *a5),
               (uint64_t)(a5[4] * 0.5 + a5[1]),
               (uint64_t)(a5[5] * 0.5 + a5[2]),
               1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E8770 sub_4E8770 —— ★★ UNIONHIT / 合击特效 vt+524（研究 20 §5.4 全文定案）
// 触发：命中包 case 0x14 的**合击位**（研究 §1.1："合击位 → vt+524 = UNIONHIT"）。
// 反编译体与 §5.4 逐条对应：
//   ① `v8 = a5[3]*0.5 + a5[0]` = 盒中心 x；受方 vt+124 取 y
//   ② **"Common/HitEffect/Animation/UnionHit.ani"** 池化生成 + 入演播层 2
//   ③ 尾调 **vt+212(a1, "GROUP_EFFECT", −1, 0, 0)** —— ★ 广播 `"GROUP_EFFECT"`
//      （研究 §5.4："UnionHit.ani + 广播 \"GROUP_EFFECT\"（连击系统视觉）"）—— **直证**
// ------------------------------------------------------------
int /*userpurge*/ sub_4E8770@<eax>(int *a1@<ecx>, int a2@<edi>, int a3@<esi>, int a4, float *a5)
{
  int result; // eax
  int v7; // esi
  int v8; // [esp+8h] [ebp-14h]
  int v9; // [esp+28h] [ebp+Ch]

  result = a1[29];
  if ( result != 0 )
  {
    v8 = (uint64_t)(a5[3] * 0.5 + *a5);
    (*(void (/*fastcall*/ **)(int, uint32_t, int, int))(*(uint32_t *)a4 + 124))(
      a4,
      (uint64_t)(a5[3] * 0.5 + *a5) >> 32,
      a2,
      a3);
    if ( sub_42FCB0(228) != 0 )
      v9 = sub_431860((char)"Common/HitEffect/Animation/UnionHit.ani", 1);
    else
      v9 = 0;
    v7 = sub_44B6C0(284);
    if ( v7 != 0 )
    {
      sub_44E0D0(v9, 1);
      *(uint32_t *)v7 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v7 = 0;
    }
    sub_45FE80(a1[29], a4, 2, 0, v7, a4, 0);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 112))(v7, v8);
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(a1, "GROUP_EFFECT", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E88A0 sub_4E88A0 —— ★★★ HITEFF / 通用命中特效生成器 vt+640（研究 20 §5.2 全文定案）
// 签名：__userpurge(a1 = 受击者, a2/a3 寄存器, a4 = 攻击者, a5 = 命中盒 6 float)
// 调用点 = 表现壳 0x4E5DC0 的 `vt+640(this, a2, a3)`（研究 §3 伪码末段）。
// 反编译体与 §5.2 逐条对应：
//   ⓪ 命中点 = 交集盒中心：`v84 = a5[3]*0.5 + a5[0]`（x）、受方 vt+124 取 y、
//      `v82 = a5[5]*0.5 + a5[2]`（z）；v85 = 方向/镜像标志（攻方 vt+660 朝向比对）
//   ① **攻击特效四类型 switch（attackinfo+20 = v79+20）** —— 研究 §5.2 原文
//      "按 attackinfo+20 选特效系"：
//        case 0/1 → **两组预置模板**：dword_8F8278/8F827C（case 0）与
//                     dword_8F8280/8F8284（case 1）—— 池化单例三角组（研究 §5.2
//                     "0/1 = 两组预置模板"；§29b "刀/钝器 = 池化双火花"）✅
//        case 2    → **"Common/HitEffect/Animation/DarkHit2.ani" + DarkHit1.ani**
//                     三层叠放（研究 §5.2 "2=DarkHit1/2.ani" ✅）
//        case 3    → **"Common/HitEffect/Animation/LightHit.ani"**（§5.2 "3=LightHit.ani" ✅）
//      随后的 `if (attackinfo+12 == 1)`（★ 魔法大类 [magic]）→
//        **"Common/HitEffect/Animation/MagicHit3.ani"**（§5.2 "魔法=MagicHit3.ani" ✅）
//   ② **命中火花路径组**（研究 §5.2 原文三段，v43 = attackinfo+124 [hit info]）：
//        == 0（**钝击 Knock**）：前缀 "Knock"，区域码 dword_8F7A24+244
//           0..1 → "Knock"；== 2 → "Age12/Knock"；再按 **v15 = rand()%2** 追加
//           "Large.ani" 或 "Small.ani"（★ §5.2 "随机 Large.ani/Small.ani" ✅）
//        == 1（**斩击 Slash**）：前缀 "Slash"，区域码同上（"Slash"/"Age12/Slash"）；
//           按 **attackinfo+120 武器种类 v76** 选：Large3/2/1.ani 或 Small3/2/1.ani
//           （★ §5.2 "按 attackinfo+120 武器种类 Large1/2/3 或 Small1/2/3" ✅）
//        == 3：攻方 **vt+652** 给自定义路径（★ §5.2 "攻击者 vt+652 给自定义路径" ✅）
//      （区域码 == 1 的分支在转写体不追加前缀 —— 即"日区/Young 变体"由拼接层决定，见 ④）
//   ③ ★★ **暴击 → 火花 1.5 倍**：`if (sub_4E5B50(a1, a4) != 0) sub_4920E0(1.5, 1.5)`
//      —— §5.2 原文"火花创建后：**暴击 → sub_4920E0(1.5, 1.5) = 批量改写特效帧的
//      IMAGE RATE（帧 +20/+24，88 字节帧距）—— 火花动画整体放大 1.5 倍**" **直证** ✅
//   ④ ★ **血溅**：`attackinfo+128 != 0`（[blood] 标志）且 受方条件 17（有血）→
//      "SplashBloodLarge"（v15）/ "SplashBloodSmall1-3"（按 v76 武器类）+
//      **区域码 != 1 时追加 "Young"**（★ §5.2 "+Young 和谐"）；
//      再拼 "Monster/Common/Animation/MonsterDieBlood"（★ §5.2 "+ MonsterDieBlood"）
//      其朝向偏移 = `v85 ? +10 : −10`（★ §5.2 "（朝向偏移 ±10 取决于攻击方向）" ✅）
//   ⑤ ★ **伤害倍率特效**：循环 i∈{0,1}，`attackinfo+84/88 > 100` 时（[human damage rate]/
//      [fort damage rate]）且持有标签 16/17 → **"OptionalDamageRateHuman.ani"/
//      "OptionalDamageRateFort.ani"**，缩放 = sub_4049C0(0.69999999, 1.5, 值−100, 100)
//      （★ §5.2 "attackinfo+84/+88 > 100 → OptionalDamageRateHuman/Fort.ani（克制标记）" ✅，
//      且 L1 补出缩放公式：0.7..1.5 线性插值）
// 研究 §5.2 第 9 轮更正注记："此函数作用于特效帧数组，非场景节点树" —— 与 sub_4920E0 一致。
// ✅ 与 §5.2 定案**逐条吻合**（含全部资源名/随机/区域码/暴击 1.5×/血溅/克制标记）。
// ------------------------------------------------------------
void /*userpurge*/ sub_4E88A0(int a1@<ecx>, int a2@<ebx>, int a3@<esi>, int a4, float *a5)
{
  unsigned int v6; // esi
  int v7; // esi
  int v8; // ecx
  char v9; // al
  bool v10; // zf
  double v11; // st7
  uint64_t v12; // rax
  int v13; // eax
  double v14; // st7
  bool v15; // bl
  int v16; // eax
  int v17; // esi
  int v18; // esi
  int v19; // eax
  int v20; // eax
  int v21; // esi
  int v22; // esi
  int v23; // eax
  int v24; // eax
  uint32_t *v25; // ecx
  int v26; // eax
  int v27; // esi
  uint32_t *v28; // ecx
  int v29; // eax
  int v30; // esi
  int v31; // esi
  uint32_t *v32; // ecx
  int v33; // eax
  int v34; // esi
  int v35; // esi
  uint32_t *v36; // ecx
  int v37; // eax
  int v38; // esi
  int v39; // esi
  int v40; // esi
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  void *v48; // eax
  void **v49; // ecx
  int v50; // esi
  int v51; // esi
  int v52; // esi
  int v53; // eax
  void **v54; // ecx
  int v55; // eax
  int v56; // esi
  void **v57; // ecx
  int v58; // eax
  int *v59; // esi
  int v60; // eax
  int v61; // eax
  int i; // ebx
  int v63; // eax
  void **v64; // ecx
  int v65; // eax
  int v66; // esi
  double v67; // st7
  float v68; // [esp-Ch] [ebp-B8h]
  int v69; // [esp-8h] [ebp-B4h]
  int v71; // [esp-4h] [ebp-B0h]
  char v72[4]; // [esp+4h] [ebp-A8h] BYREF
  void *Block; // [esp+8h] [ebp-A4h]
  int v74; // [esp+Ch] [ebp-A0h]
  int v75; // [esp+10h] [ebp-9Ch]
  int v76; // [esp+14h] [ebp-98h]
  uint8_t v77[16]; // [esp+18h] [ebp-94h] BYREF
  int v78; // [esp+28h] [ebp-84h]
  int v79; // [esp+2Ch] [ebp-80h]
  int v80; // [esp+30h] [ebp-7Ch]
  char v81; // [esp+37h] [ebp-75h] BYREF
  float v82; // [esp+38h] [ebp-74h]
  int v83; // [esp+3Ch] [ebp-70h]
  int v84; // [esp+40h] [ebp-6Ch]
  char v85; // [esp+47h] [ebp-65h]
  char v86[4]; // [esp+48h] [ebp-64h] BYREF
  uint32_t v87[6]; // [esp+4Ch] [ebp-60h] BYREF
  char v88[4]; // [esp+64h] [ebp-48h] BYREF
  uint8_t v89[8]; // [esp+68h] [ebp-44h] BYREF
  uint8_t v90[8]; // [esp+70h] [ebp-3Ch] BYREF
  int v91; // [esp+78h] [ebp-34h]
  unsigned int v92; // [esp+7Ch] [ebp-30h]
  char v93[4]; // [esp+80h] [ebp-2Ch] BYREF
  void *v94[4]; // [esp+84h] [ebp-28h] BYREF
  int v95; // [esp+94h] [ebp-18h]
  unsigned int v96; // [esp+98h] [ebp-14h]
  int v97; // [esp+9Ch] [ebp-10h]
  int v98; // [esp+A8h] [ebp-4h]
  float v99; // [esp+B4h] [ebp+8h]

  v97 = dword_796E50;
  if ( *(uint32_t *)(a1 + 116) == 0 )
    return;
  if ( *(uint8_t *)(a1 + 642) != 0 )
  {
    v6 = *(uint32_t *)(a1 + 644);
  }
  else
  {
    v7 = *(uint32_t *)(a1 + 120);
    if ( v7 == 0 )
      goto LABEL_9;
    if ( *(uint32_t *)(v7 + 148) == -1 )
      sub_4938F0(*(uint32_t *)(a1 + 120));
    v6 = *(uint32_t *)(v7 + 112);
  }
  if ( v6 > 1 )
    return;
LABEL_9:
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 348))(a4);
  v9 = *(uint8_t *)(v8 + 16);
  v79 = v8;
  if ( v9 == 0 && *(float *)v8 <= 0.0 )
    return;
  v10 = *(uint32_t *)(v8 + 124) == 1;
  v85 = 0;
  if ( v10 )
    v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a4 + 152))(a4, a3) == 0;
  else
    v10 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a4 + 660))(a4, a1, a3) == 1;
  if ( v10 )
    v85 = 1;
  v11 = a5[3] * 0.5;
  v76 = *(uint32_t *)(v79 + 120);
  v12 = (uint64_t)(v11 + *a5);
  v84 = v12;
  v13 = (*(int (/*fastcall*/ **)(int, uint32_t, int))(*(uint32_t *)a1 + 124))(a1, HIDWORD(v12), a2);
  v14 = a5[5] * 0.5;
  v83 = v13;
  LODWORD(v82) = (uint64_t)(v14 + a5[2]);
  v15 = rand() % 2 == 0;
  v96 = 15;
  v95 = 0;
  LOBYTE(v94[0]) = 0;
  v16 = *(uint32_t *)(v79 + 20);
  v98 = 0;
  switch ( v16 )
  {
    case 0:
      v17 = dword_8F8278;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8278 + 12))(dword_8F8278, 0);
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v17 + 40))(v17, v84, v83, COERCE_FLOAT(LODWORD(v82)));
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 28))(v17) + 84) = v85;
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v17 + 92))(v17, v77);
      LOBYTE(v98) = 1;
      sub_4600B0(2, 0, v77);
      v18 = dword_8F827C;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F827C + 12))(dword_8F827C, 0);
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v18 + 40))(v18, v84, v83, COERCE_FLOAT(LODWORD(v82)));
      v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 28))(v18);
      *(uint8_t *)(v19 + 84) = v85;
      v20 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v18 + 92))(v18, v90);
      LOBYTE(v98) = 2;
      sub_4E77D0(v20);
      LOBYTE(v98) = 1;
LABEL_18:
      sub_5E5260(v90);
      sub_4600B0(2, 0, v77);
      LOBYTE(v98) = 0;
      sub_5E5260(v77);
      goto LABEL_68;
    case 1:
      v21 = dword_8F8280;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8280 + 12))(dword_8F8280, 0);
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v21 + 40))(v21, v84, v83, COERCE_FLOAT(LODWORD(v82)));
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 28))(v21) + 84) = v85;
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v21 + 92))(v21, v77);
      LOBYTE(v98) = 3;
      sub_4600B0(2, 0, v77);
      v22 = dword_8F8284;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8284 + 12))(dword_8F8284, 0);
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v22 + 40))(v22, v84, v83, COERCE_FLOAT(LODWORD(v82)));
      v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v22 + 28))(v22);
      *(uint8_t *)(v23 + 84) = v85;
      v24 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v22 + 92))(v22, v90);
      LOBYTE(v98) = 4;
      sub_4E77D0(v24);
      LOBYTE(v98) = 3;
      goto LABEL_18;
    case 2:
      sub_401710("Common/HitEffect/Animation/DarkHit2.ani");
      v78 = sub_44B6C0(284);
      LOBYTE(v98) = 6;
      if ( v78 != 0 )
      {
        v80 = sub_42FCB0(228);
        LOBYTE(v98) = 7;
        if ( v80 != 0 )
        {
          LOBYTE(v25) = v89[0];
          if ( v92 < 0x10 )
            v25 = v89;
          v26 = sub_431860((char)v25, 1);
        }
        else
        {
          v26 = 0;
        }
        LOBYTE(v98) = 6;
        v27 = sub_44E1F0(v26, 1);
      }
      else
      {
        v27 = 0;
      }
      LOBYTE(v98) = 5;
      sub_45FE80(2, 0, v27, a1, 0);
      if ( v85 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v27 + 148))(v27, 0);
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v27 + 112))(v27, v84, v83, COERCE_FLOAT(LODWORD(v82)));
      sub_406D60("Common/HitEffect/Animation/DarkHit1.ani");
      v80 = sub_44B6C0(284);
      LOBYTE(v98) = 8;
      if ( v80 != 0 )
      {
        v78 = sub_42FCB0(228);
        LOBYTE(v98) = 9;
        if ( v78 != 0 )
        {
          LOBYTE(v28) = v89[0];
          if ( v92 < 0x10 )
            v28 = v89;
          v29 = sub_431860((char)v28, 1);
        }
        else
        {
          v29 = 0;
        }
        LOBYTE(v98) = 8;
        v30 = sub_44E1F0(v29, 1);
      }
      else
      {
        v30 = 0;
      }
      LOBYTE(v98) = 5;
      sub_45FE80(2, 0, v30, a1, 0);
      if ( v85 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v30 + 148))(v30, 0);
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v30 + 112))(v30, v84, v83, COERCE_FLOAT(LODWORD(v82)));
      v31 = dword_8F8288;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8288 + 12))(dword_8F8288, 0);
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v31 + 40))(v31, v84, v83, COERCE_FLOAT(LODWORD(v82)));
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v31 + 28))(v31) + 84) = v85;
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v31 + 92))(v31, v77);
      LOBYTE(v98) = 10;
LABEL_43:
      sub_4600B0(2, 0, v77);
      sub_5E5260(v77);
      LOBYTE(v98) = 0;
      sub_501490(v88);
      goto LABEL_68;
    case 3:
      sub_401710("Common/HitEffect/Animation/LightHit.ani");
      v80 = sub_44B6C0(284);
      LOBYTE(v98) = 12;
      if ( v80 != 0 )
      {
        v78 = sub_42FCB0(228);
        LOBYTE(v98) = 13;
        if ( v78 != 0 )
        {
          LOBYTE(v32) = v89[0];
          if ( v92 < 0x10 )
            v32 = v89;
          v33 = sub_431860((char)v32, 1);
        }
        else
        {
          v33 = 0;
        }
        LOBYTE(v98) = 12;
        v34 = sub_44E1F0(v33, 1);
      }
      else
      {
        v34 = 0;
      }
      LOBYTE(v98) = 11;
      sub_45FE80(2, 0, v34, a1, 0);
      if ( v85 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v34 + 148))(v34, 0);
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v34 + 112))(v34, v84, v83, COERCE_FLOAT(LODWORD(v82)));
      v35 = dword_8F828C;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F828C + 12))(dword_8F828C, 0);
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v35 + 40))(v35, v84, v83, COERCE_FLOAT(LODWORD(v82)));
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v35 + 28))(v35) + 84) = v85;
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v35 + 92))(v35, v77);
      LOBYTE(v98) = 14;
      goto LABEL_43;
    default:
      break;
  }
  if ( *(uint32_t *)(v79 + 12) == 1 )
  {
    sub_401710("Common/HitEffect/Animation/MagicHit3.ani");
    v80 = sub_44B6C0(284);
    LOBYTE(v98) = 16;
    if ( v80 != 0 )
    {
      v78 = sub_42FCB0(228);
      LOBYTE(v98) = 17;
      if ( v78 != 0 )
      {
        LOBYTE(v36) = v87[0];
        if ( v87[5] < 0x10u )
          v36 = v87;
        v37 = sub_431860((char)v36, 1);
      }
      else
      {
        v37 = 0;
      }
      LOBYTE(v98) = 16;
      v38 = sub_44E1F0(v37, 1);
    }
    else
    {
      v38 = 0;
    }
    LOBYTE(v98) = 15;
    sub_45FE80(2, 0, v38, a1, 0);
    if ( v85 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v38 + 148))(v38, 0);
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v38 + 112))(v38, v84, v83, COERCE_FLOAT(LODWORD(v82)));
    v39 = dword_8F8290;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8290 + 12))(dword_8F8290, 0);
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v39 + 40))(v39, v84, v83, COERCE_FLOAT(LODWORD(v82)));
    *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v39 + 28))(v39) + 84) = v85;
    (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v39 + 92))(v39, v77);
    LOBYTE(v98) = 18;
    sub_4600B0(2, 0, v77);
    v40 = dword_8F8294;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8294 + 12))(dword_8F8294, 0);
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v40 + 40))(v40, v84, v83, COERCE_FLOAT(LODWORD(v82)));
    v41 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v40 + 28))(v40);
    *(uint8_t *)(v41 + 84) = v85;
    v42 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v40 + 92))(v40, v90);
    LOBYTE(v98) = 19;
    sub_4E77D0(v42);
    LOBYTE(v98) = 18;
    sub_5E5260(v90);
    sub_4600B0(2, 0, v77);
    sub_5E5260(v77);
    LOBYTE(v98) = 0;
    sub_501490(v86);
  }
LABEL_68:
  sub_4015C0("Common/HitEffect/Animation/", 0x1Bu);
  v81 = 0;
  v43 = *(uint32_t *)(v79 + 124);
  if ( v43 == 0 )
  {
    v92 = 15;
    v91 = 0;
    v89[0] = 0;
    v44 = *(uint32_t *)(dword_8F7A24 + 244);
    LOBYTE(v98) = 20;
    if ( v44 >= 0 )
    {
      if ( v44 <= 1 )
      {
        sub_406D60("Knock");
      }
      else if ( v44 == 2 )
      {
        sub_406D60("Age12/Knock");
      }
    }
    if ( v15 )
    {
      v45 = sub_4E70B0(v86, v88, "Large.ani");
      LOBYTE(v98) = 21;
    }
    else
    {
      v45 = sub_4E70B0(v86, v88, "Small.ani");
      LOBYTE(v98) = 22;
    }
    sub_4021F0((std::_String_base *)v93, v45, 0, -1);
    sub_501490(v86);
    LOBYTE(v98) = 0;
    sub_501490(v88);
    goto LABEL_103;
  }
  if ( v43 != 1 )
  {
    if ( v43 == 3 && (v48 = (void *)(*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)a4 + 652))(a4, &v81)) != nullptr )
      sub_406D60(v48);
    else
      sub_406D60((void *)szPassword);
    goto LABEL_103;
  }
  v92 = 15;
  v91 = 0;
  v89[0] = 0;
  v46 = *(uint32_t *)(dword_8F7A24 + 244);
  LOBYTE(v98) = 23;
  if ( v46 >= 0 )
  {
    if ( v46 <= 1 )
    {
      sub_406D60("Slash");
    }
    else if ( v46 == 2 )
    {
      sub_406D60("Age12/Slash");
    }
  }
  if ( v15 )
  {
    switch ( v76 )
    {
      case 0:
        v47 = sub_4E70B0(v86, v88, "Large3.ani");
        LOBYTE(v98) = 24;
LABEL_97:
        sub_4021F0((std::_String_base *)v93, v47, 0, -1);
        sub_501490(v86);
        break;
      case 1:
        v47 = sub_4E70B0(v86, v88, "Large2.ani");
        LOBYTE(v98) = 25;
        goto LABEL_97;
      case 2:
        v47 = sub_4E70B0(v86, v88, "Large1.ani");
        LOBYTE(v98) = 26;
        goto LABEL_97;
      default:
        break;
    }
  }
  else
  {
    switch ( v76 )
    {
      case 0:
        v47 = sub_4E70B0(v86, v88, "Small3.ani");
        LOBYTE(v98) = 27;
        goto LABEL_97;
      case 1:
        v47 = sub_4E70B0(v86, v88, "Small2.ani");
        LOBYTE(v98) = 28;
        goto LABEL_97;
      case 2:
        v47 = sub_4E70B0(v86, v88, "Small1.ani");
        LOBYTE(v98) = 29;
        goto LABEL_97;
      default:
        break;
    }
  }
  LOBYTE(v98) = 0;
  sub_501490(v88);
LABEL_103:
  if ( sub_40BF00(0, v95, szPassword, 0) != 0 )
  {
    v80 = sub_42FCB0(228);
    LOBYTE(v98) = 30;
    if ( v80 != 0 )
    {
      LOBYTE(v49) = v94[0];
      if ( v96 < 0x10 )
        v49 = v94;
      v50 = sub_431860((char)v49, 1);
    }
    else
    {
      v50 = 0;
    }
    LOBYTE(v98) = 0;
    if ( (uint8_t)sub_4E5B50(a1, a4) != 0 )
      sub_4920E0(1.5, 1.5);
    v80 = sub_44B6C0(284);
    LOBYTE(v98) = 31;
    if ( v80 != 0 )
      v51 = sub_44E1F0(v50, 1);
    else
      v51 = 0;
    LOBYTE(v98) = 0;
    sub_45FE80(2, 0, v51, a1, 0);
    if ( v85 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v51 + 148))(v51, 0);
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v51 + 112))(v51, v84, v83, COERCE_FLOAT(LODWORD(v82)));
    if ( v81 != 0 )
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v51 + 60))(v51);
      sub_4A06D0(a1);
    }
  }
  v52 = dword_8F8270[!v15];
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v52 + 12))(v52, 0);
  (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)v52 + 40))(v52, v84, v83, COERCE_FLOAT(LODWORD(v82)));
  v53 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v52 + 28))(v52);
  *(uint8_t *)(v53 + 84) = v85;
  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v52 + 92))(v52, v72);
  LOBYTE(v98) = 32;
  sub_4600B0(2, 0, v72);
  if ( *(uint8_t *)(v79 + 128) != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 40))(a1, 17) != 0 )
  {
    if ( *(uint32_t *)(dword_8F7A24 + 244) == 2
      || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 40))(a1, 529) != 0
      && (*(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 1032))(a1) + 64) & 2) != 0 )
    {
      sub_5E5260(v72);
      sub_501490(v93);
      return;
    }
    sub_406D60("Common/HitEffect/Animation/");
    if ( v15 )
    {
      sub_402410("SplashBloodLarge");
    }
    else if ( v76 != 0 )
    {
      if ( v76 == 1 )
      {
        sub_402410("SplashBloodSmall2");
      }
      else if ( v76 == 2 )
      {
        sub_402410("SplashBloodSmall3");
      }
    }
    else
    {
      sub_402410("SplashBloodSmall1");
    }
    if ( *(uint32_t *)(dword_8F7A24 + 244) != 1 )
      sub_402410("Young");
    sub_402410(".ani");
    v80 = sub_44B6C0(284);
    LOBYTE(v98) = 33;
    if ( v80 != 0 )
    {
      v78 = sub_42FCB0(228);
      LOBYTE(v98) = 34;
      if ( v78 != 0 )
      {
        LOBYTE(v54) = v94[0];
        if ( v96 < 0x10 )
          v54 = v94;
        v55 = sub_431860((char)v54, 1);
        LOBYTE(v98) = 33;
        v56 = sub_44E1F0(v55, 1);
      }
      else
      {
        LOBYTE(v98) = 33;
        v56 = sub_44E1F0(0, 1);
      }
    }
    else
    {
      v56 = 0;
    }
    LOBYTE(v98) = 32;
    sub_45FE80(2, 0, v56, a1, 0);
    if ( v85 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v56 + 148))(v56, 0);
    (*(void (/*thiscall*/ **)(int, int, int, float, int, int))(*(uint32_t *)v56 + 112))(
      v56,
      v84,
      v83,
      COERCE_FLOAT(LODWORD(v82)),
      v69,
      v71);
    sub_406D60("Monster/Common/Animation/MonsterDieBlood");
    if ( *(uint32_t *)(dword_8F7A24 + 244) != 1 )
      sub_402410("Young");
    sub_402410(".ani");
    v80 = sub_44B6C0(284);
    LOBYTE(v98) = 35;
    if ( v80 != 0 )
    {
      v78 = sub_42FCB0(228);
      LOBYTE(v98) = 36;
      if ( v78 != 0 )
      {
        LOBYTE(v57) = v94[0];
        if ( v96 < 0x10 )
          v57 = v94;
        v58 = sub_431860((char)v57, 1);
        LOBYTE(v98) = 35;
        v59 = (int *)sub_44E1F0(v58, 1);
      }
      else
      {
        LOBYTE(v98) = 35;
        v59 = (int *)sub_44E1F0(0, 1);
      }
    }
    else
    {
      v59 = nullptr;
    }
    v60 = *v59;
    LOBYTE(v98) = 32;
    *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v60 + 36))(v59) + 8) = 2;
    sub_45FE80(2, 0, v59, 0, 0);
    if ( v85 != 0 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*v59 + 148))(v59, 0);
      v61 = v84 + 10;
    }
    else
    {
      v61 = v84 - 10;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*v59 + 112))(v59, v61);
  }
  for ( i = 0; i < 2; ++i )
  {
    if ( *(float *)(v79 + 4 * i + 84) <= 100.0 )
      continue;
    if ( i != 0 )
    {
      if ( i != 1 )
        continue;
      v63 = 17;
    }
    else
    {
      v63 = 16;
    }
    if ( (uint8_t)sub_4DAB60(v63) != 0 )
    {
      sub_4015C0("Common/HitEffect/Animation/", 0x1Bu);
      if ( i != 0 )
        sub_402410("OptionalDamageRateFort.ani");
      else
        sub_402410("OptionalDamageRateHuman.ani");
      v80 = sub_44B6C0(284);
      LOBYTE(v98) = 37;
      if ( v80 != 0 )
      {
        v78 = sub_42FCB0(228);
        LOBYTE(v98) = 38;
        if ( v78 != 0 )
        {
          LOBYTE(v64) = v94[0];
          if ( v96 < 0x10 )
            v64 = v94;
          v65 = sub_431860((char)v64, 1);
        }
        else
        {
          v65 = 0;
        }
        LOBYTE(v98) = 37;
        v66 = sub_44E1F0(v65, 1);
      }
      else
      {
        v66 = 0;
      }
      LOBYTE(v98) = 32;
      sub_45FE80(2, 0, v66, a1, 0);
      if ( v85 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v66 + 148))(v66, 0);
      v68 = v82;
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v66 + 112))(v66, v84, v83);
      v67 = *(float *)(v79 + 4 * i + 84) - 100.0;
      sub_4049C0(0.69999999, 1.5, (uint64_t)v67, 100);
      v99 = v67;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v66 + 200))(v66, LODWORD(v99));
      sub_4922F0(v68);
    }
  }
  if ( Block != nullptr )
    j__free(Block);
  Block = nullptr;
  v74 = 0;
  v75 = 0;
  if ( v96 >= 0x10 )
    j__free(v94[0]);
}


// ------------------------------------------------------------
// 0x4E9760 sub_4E9760 —— ★ 格挡特效 vt+644（研究 20 §3 格挡分支定案）
// 调用点 = 表现壳 0x4E5DC0 的 `a4 != 0`（格挡）分支：vt+644(this, a2, a3)。
// 反编译体与 §3 原文逐条对应："vt+644(this, 攻击者, 盒) 格挡特效：
//   **GuardSpark.ani + GuardCircle.ani + Stuck.ani**（Character/Swordman/Effect +
//   Common/HitEffect）"：
//     ① "Character/Swordman/Effect/Animation/**GuardSpark.ani**" 池化 →
//        vt+148(攻方 vt+660 取朝向) 设镜像 → vt+112 定位（盒中心 x/y/z）
//     ② "Character/Swordman/Effect/Animation/**GuardCircle.ani**" 同上
//     ③ "Common/HitEffect/Animation/**Stuck.ani**" → vt+72(2) 后定位（z + 30.0 抬高）
//   —— 三条资源名**逐字吻合**研究 §3 ✅
// ------------------------------------------------------------
int /*thiscall*/ sub_4E9760(int *this, int a2, float *a3)
{
  int v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // edi
  int v9; // [esp+10h] [ebp-14h]
  int v10; // [esp+14h] [ebp-10h]
  int v11; // [esp+2Ch] [ebp+8h]
  int v12; // [esp+2Ch] [ebp+8h]
  int v13; // [esp+2Ch] [ebp+8h]
  int v14; // [esp+30h] [ebp+Ch]

  v4 = (uint64_t)(a3[3] * 0.5 + *a3);
  v10 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*this + 124))(this, (uint64_t)(a3[3] * 0.5 + *a3) >> 32);
  v14 = (uint64_t)(a3[5] * 0.5 + a3[2]);
  v9 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)a2 + 660))(a2, this);
  if ( sub_42FCB0(228) != 0 )
    v11 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardSpark.ani", 1);
  else
    v11 = 0;
  v5 = sub_44B6C0(284);
  if ( v5 != 0 )
  {
    sub_44E0D0(v11, 1);
    *(uint32_t *)v5 = &CNRDPooledObject::`vftable';
  }
  else
  {
    v5 = 0;
  }
  sub_45FE80(*(this + 29), v5, 2, 0, v5, (int)this, 0);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 148))(v5, v9);
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 112))(v5, v4, v10, v14);
  if ( sub_42FCB0(228) != 0 )
    v12 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardCircle.ani", 1);
  else
    v12 = 0;
  v6 = sub_44B6C0(284);
  if ( v6 != 0 )
  {
    sub_44E0D0(v12, 1);
    *(uint32_t *)v6 = &CNRDPooledObject::`vftable';
  }
  else
  {
    v6 = 0;
  }
  sub_45FE80(*(this + 29), v6, 2, 0, v6, (int)this, 0);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 148))(v6, v9);
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 112))(v6, v4, v10, v14);
  if ( sub_42FCB0(228) != 0 )
    v13 = sub_431860((char)"Common/HitEffect/Animation/Stuck.ani", 1);
  else
    v13 = 0;
  v7 = sub_44B6C0(284);
  if ( v7 != 0 )
  {
    sub_44E0D0(v13, 1);
    *(uint32_t *)v7 = &CNRDPooledObject::`vftable';
  }
  else
  {
    v7 = 0;
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 72))(v7, 2);
  sub_45FE80(*(this + 29), v7, 2, 0, v7, (int)this, 0);
  return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 112))(v7, v4, v10, v14 + 30);
}



// ============================================================
// 【分区 E】特效对象类 / 反作弊属性内核（0x4E99C0 - 0x4EA220）
//   本组 = 命中特效 CNRDObject 派生类共同基座 + ★ **防篡读写全套**
//   （研究 P20-23 / P27 定案：sub_41A590 = 每次写随机换 128 密钥表密钥 + 双通道 XOR；
//     sub_41A5E0 = 数值防篡改校验读取（指针自带 XOR 交叉校验，失败 → 0 +
//     清全局标志 byte_77F48C）—— 伤害/属性读取全部走这一对）。
//   0x4E99C0 = 防篡浮点减；0x4E99F0/0x4E9A10/0x4E9A50/0x4E9B10/0x4E9C00 = clong 类构造族
//   （四个内嵌 clong + 五种参数装载变体）；0x4E9CF0 = 区间随机数（sub_4049C0 插值）
//   ============================================================

// ------------------------------------------------------------
// 0x4E99C0 sub_4E99C0 —— 防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
// `sub_41A590(this, cur − a2)` —— 写入走防篡写通道（研究 P20-23：每次写随机换密钥）。
// ------------------------------------------------------------
double /*thiscall*/ sub_4E99C0(void *this, float a2)
{
  int v3; // edx
  int v5; // [esp+10h] [ebp+8h]

  *(float *)&v5 = COERCE_FLOAT(sub_41A5E0((unsigned int)this)) - a2;
  sub_41A590((unsigned int)this, v3, v5);
  return *(float *)&v5;
}



// ------------------------------------------------------------
// 0x4E99F0 sub_4E99F0
// ------------------------------------------------------------
int /*fastcall*/ sub_4E99F0(uint32_t *a1, int a2)
{
  int v3; // edx

  *a1 = 4;
  sub_41A590((unsigned int)(a1 + 1), a2, 0);
  return sub_41A590((unsigned int)a1 + 18, v3, 0);
}



// ------------------------------------------------------------
// 0x4E9A10 sub_4E9A10
// ------------------------------------------------------------
int /*thiscall*/ sub_4E9A10(uint32_t *this)
{
  int v2; // eax
  int result; // eax

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this) != 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
    result = sub_699000(v2 + 36);
    *(this + 334) = result;
  }
  else
  {
    *(this + 334) = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E9A50 sub_4E9A50
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E9A50(uint32_t *this)
{
  uint32_t *v2; // edi
  int v3; // edx
  int v4; // edx
  int v5; // edx
  int v6; // edx

  v2 = this + 1;
  sub_41A630((unsigned int)(this + 1));
  *v2 = &clong::`vftable';
  sub_41A630((unsigned int)this + 18);
  *(uint32_t *)((char *)this + 18) = &clong::`vftable';
  sub_41A630((unsigned int)(this + 8));
  *(this + 8) = &clong::`vftable';
  sub_41A630((unsigned int)this + 46);
  *(uint32_t *)((char *)this + 46) = &clong::`vftable';
  *this = 0;
  sub_41A590((unsigned int)v2, v3, 0);
  sub_41A590((unsigned int)this + 18, v4, 0);
  sub_41A590((unsigned int)(this + 8), v5, -1);
  sub_41A590((unsigned int)this + 46, v6, 0);
  return this;
}



// ------------------------------------------------------------
// 0x4E9B10 sub_4E9B10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E9B10(uint32_t *this, int a2, uint8_t a3, int a4, int a5)
{
  uint32_t *v6; // edi

  v6 = this + 1;
  sub_41A630(this + 1);
  *v6 = &clong::`vftable';
  sub_41A630((char *)this + 18);
  *(uint32_t *)((char *)this + 18) = &clong::`vftable';
  sub_41A630(this + 8);
  *(this + 8) = &clong::`vftable';
  sub_41A630((char *)this + 46);
  *(uint32_t *)((char *)this + 46) = &clong::`vftable';
  *this = 0;
  sub_41A590(0);
  sub_41A590(0);
  sub_41A590(-1);
  sub_41A590(0);
  *this = a2;
  sub_41A590(a3 & 0x1F);
  sub_41A590(0);
  sub_41A590(a5);
  sub_41A590(a3 >> 5);
  return this;
}



// ------------------------------------------------------------
// 0x4E9C00 sub_4E9C00
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E9C00(uint32_t *this, int a2, int a3, int a4, int a5, int a6)
{
  uint32_t *v7; // edi
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  int v14; // edx

  v7 = this + 1;
  sub_41A630((unsigned int)(this + 1));
  *v7 = &clong::`vftable';
  sub_41A630((unsigned int)this + 18);
  *(uint32_t *)((char *)this + 18) = &clong::`vftable';
  sub_41A630((unsigned int)(this + 8));
  *(this + 8) = &clong::`vftable';
  sub_41A630((unsigned int)this + 46);
  *(uint32_t *)((char *)this + 46) = &clong::`vftable';
  *this = 0;
  sub_41A590((unsigned int)v7, v8, 0);
  sub_41A590((unsigned int)this + 18, v9, 0);
  sub_41A590((unsigned int)(this + 8), v10, -1);
  sub_41A590((unsigned int)this + 46, v11, 0);
  *this = a2;
  sub_41A590((unsigned int)v7, v12, a3);
  sub_41A590((unsigned int)this + 18, a4, a4);
  sub_41A590((unsigned int)(this + 8), v13, a5);
  sub_41A590((unsigned int)this + 46, v14, a6);
  return this;
}



// ------------------------------------------------------------
// 0x4E9CF0 sub_4E9CF0 —— 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
// `v8 = 传入值 × 乘数 × 0.0099999998`；v10 = sub_432F40(上限夹取 到 a4)；
// `sub_4049C0(-v10, +v10, sub_4D33A0(随机种机) % 1000, 999)` —— 与 0x4E6770 内的
// ± 方差同一手法（LCG %1000 作插值 t，在 [−v10, +v10] 内线性取值）。
// 返回 `原值 + sub_432F40(插值结果)` —— 供调用方直接落地。
// ------------------------------------------------------------
int /*cdecl*/ sub_4E9CF0(int a1, unsigned int *a2, int a3, int a4)
{
  unsigned int v6; // eax
  float v7; // [esp+0h] [ebp-14h]
  float v8; // [esp+Ch] [ebp-8h]
  float v9; // [esp+Ch] [ebp-8h]
  int v10; // [esp+1Ch] [ebp+8h]
  float v11; // [esp+1Ch] [ebp+8h]

  if ( *(float *)&a1 == 0.0 )
    return 0;
  v8 = (double)a1 * (double)a3 * 0.0099999998;
  v10 = sub_432F40(v8);
  if ( v10 >= a4 )
    v10 = a4;
  v11 = (float)v10;
  v6 = sub_4D33A0(a2);
  v7 = -v11;
  v9 = sub_4049C0(v7, v11, v6 % 0x3E8, 999);
  return a1 + sub_432F40(v9);
}



// ------------------------------------------------------------
// 0x4E9D70 sub_4E9D70
// ------------------------------------------------------------
void /*thiscall*/ sub_4E9D70(int this)
{
  *(uint32_t *)(this + 4) = 2;
  *(uint8_t *)(this + 1248) = 0;
  *(uint32_t *)(this + 1268) = 0;
  sub_41BFE0((void **)(this + 1272), szPassword);
  *(uint8_t *)(this + 1276) = 0;
  *(uint32_t *)(this + 1284) = 0;
  *(uint8_t *)(this + 1320) = 0;
  *(uint32_t *)(this + 1332) = 0;
  *(uint32_t *)(this + 1324) = 0;
  *(uint32_t *)(this + 1328) = 0;
  *(uint32_t *)(this + 1344) = 1065353216;
}



// ------------------------------------------------------------
// 0x4E9DD0 sub_4E9DD0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E9DD0(char *this, int a2)
{
  char *v2; // ebx
  int result; // eax
  int v4; // esi
  char *v6; // edi
  int v7; // ecx
  int v8; // ebx
  uint32_t *v9; // eax
  float v10; // eax
  float *v11; // ebx
  unsigned int v12; // edi
  double v13; // st7
  bool v14; // zf
  int v16; // [esp+10h] [ebp-4h]
  int v17; // [esp+1Ch] [ebp+8h]

  v2 = this;
  if ( (*(uint8_t (/*fastcall*/ **)(char *))(*(uint32_t *)this + 200))(this) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)v2 + 321) + 40))(*((uint32_t *)v2 + 321), 273);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)v2 + 321) + 1084))(
                 *((uint32_t *)v2 + 321),
                 *((uint32_t *)v2 + 37));
      v4 = result;
      if ( result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 200))(result);
        if ( (uint8_t)result == 0 )
          return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 128))(v4, a2);
      }
    }
  }
  else
  {
    v16 = 0;
    while ( 1 )
    {
      if ( v16 != 0 )
      {
        result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v2 + 224))(v2);
        if ( (uint8_t)result == 0 )
          return result;
        v6 = *((char **)v2 + 317);
      }
      else
      {
        v6 = v2 + 212;
      }
      if ( *((uint32_t *)v2 + 37) == 8 && *(uint8_t *)(a2 + 16) != 0 )
      {
        if ( *(uint32_t *)(a2 + 20) == 4 )
          *(uint32_t *)(a2 + 20) = *((uint32_t *)v6 + 193);
        v7 = *((uint32_t *)v6 + 194);
        if ( v7 != 17 )
        {
          v8 = 0;
          v9 = (uint32_t *)(a2 + 24);
          while ( *v9 != 17 )
          {
            ++v8;
            ++v9;
            if ( v8 >= 3 )
              goto LABEL_22;
          }
          *(uint32_t *)(a2 + 4 * v8 + 24) = v7;
          *(uint32_t *)(a2 + 4 * v8 + 48) = sub_41A5E0((unsigned int)(v6 + 794));
          *(float *)(a2 + 4 * v8 + 36) = COERCE_FLOAT(sub_41A5E0((unsigned int)(v6 + 780)));
        }
LABEL_22:
        if ( v6[850] != 0 )
          *(uint8_t *)(a2 + 82) = 1;
        if ( v6[879] != 0 )
          *(uint8_t *)(a2 + 140) = 1;
        if ( v6[880] != 0 )
          *(uint8_t *)(a2 + 141) = 1;
      }
      *(uint32_t *)(a2 + 64) += sub_41A5E0((unsigned int)(v6 + 808));
      *(uint32_t *)(a2 + 68) += sub_41A5E0((unsigned int)(v6 + 822));
      v10 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v6 + 836)));
      v11 = (float *)(a2 + 84);
      v12 = (unsigned int)(v6 + 851);
      v17 = 2;
      *(float *)(a2 + 76) = v10 + *(float *)(a2 + 76);
      do
      {
        v13 = COERCE_FLOAT(sub_41A5E0(v12)) + *v11++;
        v12 += 14;
        v14 = v17 == 1;
        *(v11 - 1) = v13;
        --v17;
      }
      while ( !v14 );
      result = ++v16;
      if ( v16 >= 2 )
        break;
      v2 = this;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E9FA0 sub_4E9FA0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E9FA0(uint32_t *this, uint32_t *a2)
{
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx

  *this = *a2;
  v3 = sub_41A5E0((unsigned int)(a2 + 1));
  sub_41A590((unsigned int)(this + 1), v4, v3);
  v5 = sub_41A5E0((unsigned int)a2 + 18);
  sub_41A590((unsigned int)this + 18, v6, v5);
  v7 = sub_41A5E0((unsigned int)(a2 + 8));
  sub_41A590((unsigned int)(this + 8), v8, v7);
  v9 = sub_41A5E0((unsigned int)a2 + 46);
  sub_41A590((unsigned int)this + 46, v10, v9);
  return this;
}



// ------------------------------------------------------------
// 0x4EA000 sub_4EA000
// ------------------------------------------------------------
int /*thiscall*/ sub_4EA000(uint32_t *this)
{
  int result; // eax
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // et2
  uint8_t v8[4]; // [esp+4h] [ebp-4h] BYREF

  result = dword_8F7C04;
  if ( dword_8F7C04 != 0 )
  {
    result = sub_41A5E0((unsigned int)(this + 298));
    if ( result != 0 )
    {
      result = sub_41A5E0((unsigned int)this + 166);
      if ( result != 0 )
      {
        result = *(this + 37);
        if ( result > 7 )
        {
          if ( result == 8 )
            v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1108))(dword_8F7C04);
          else
            v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1112))(dword_8F7C04);
          v4 = v3;
          v5 = *(uint32_t *)(dword_8F7A24 + 12);
          if ( v5 == 4 || v5 == 6 )
            v4 /= 4;
          sub_432FA0();
          v6 = rand();
          v7 = v6 % 1000;
          result = v6 / 1000;
          if ( v7 < v4 )
          {
            sub_423200(dword_8F7B08, 51);
            v8[0] = *((uint8_t *)this + 148);
            sub_423290(v8, 1);
            return sub_423380(dword_8F7B08);
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EA0E0 sub_4EA0E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4EA0E0(uint32_t *this, int a2)
{
  unsigned int v3; // ebx
  int v4; // eax
  int v5; // edx
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // edx
  int v13; // eax
  int v14; // esi
  int v15; // [esp+Ch] [ebp-48h] BYREF
  uint8_t v16[14]; // [esp+10h] [ebp-44h] BYREF
  uint8_t v17[14]; // [esp+1Eh] [ebp-36h] BYREF
  uint8_t v18[28]; // [esp+2Ch] [ebp-28h] BYREF
  int v19; // [esp+50h] [ebp-4h]

  v3 = (unsigned int)(this + 298);
  v4 = sub_41A5E0((unsigned int)(this + 298));
  if ( v4 == a2 )
    return 0;
  if ( v4 != 0 && a2 != 0 )
  {
    sub_41A590(v3, v5, a2);
    return 0;
  }
  sub_4E9A50(&v15);
  v7 = *(this + 290);
  v19 = 0;
  v15 = v7;
  v8 = sub_41A5E0((unsigned int)this + 1178);
  sub_41A590((unsigned int)v17, v9, v8);
  v10 = sub_41A5E0((unsigned int)(this + 291));
  sub_41A590((unsigned int)v16, v11, v10);
  sub_41A590((unsigned int)v18, v12, a2);
  (*(void (/*thiscall*/ **)(uint32_t *, int *))(*this + 184))(this, &v15);
  v13 = *(this + 321);
  if ( v13 != 0 )
  {
    (*(void (**)(void))(*(uint32_t *)v13 + 800))();
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 321) + 676))(*(this + 321), 0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 321) + 40))(*(this + 321), 273) != 0 )
    {
      v14 = *(this + 321);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 1152))(v14);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 1156))(v14);
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 308))(v14) != 0 )
        sub_47E4F0();
    }
  }
  v19 = -1;
  sub_445150(&v15);
  return 1;
}



// ------------------------------------------------------------
// 0x4EA220 sub_4EA220
// ------------------------------------------------------------
int /*cdecl*/ sub_4EA220(int a1, int a2)
{
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // edx
  int v27; // eax
  unsigned int v28; // ebx
  int v29; // eax
  int v30; // edx
  unsigned int v31; // ebx
  int v32; // eax
  int v33; // edx
  int v34; // eax
  int v35; // eax
  int v36; // edx
  int v37; // eax
  int v38; // edx
  int v39; // eax
  int v40; // edx
  int v41; // eax
  int v42; // eax
  int v43; // edx
  int v44; // eax
  int v45; // eax
  int v46; // edx
  int v47; // eax
  int v48; // eax
  int v49; // edx
  int v50; // edx
  int v51; // edx
  unsigned int v52; // esi
  int j; // edi
  int v54; // edx
  int result; // eax
  int v56; // [esp+Ch] [ebp-4h]
  int v57; // [esp+Ch] [ebp-4h]
  float v58; // [esp+Ch] [ebp-4h]
  float v59; // [esp+Ch] [ebp-4h]
  float v60; // [esp+Ch] [ebp-4h]
  float v61; // [esp+Ch] [ebp-4h]
  float v62; // [esp+Ch] [ebp-4h]
  float v63; // [esp+18h] [ebp+8h]
  float v64; // [esp+18h] [ebp+8h]
  int v65; // [esp+18h] [ebp+8h]
  int i; // [esp+18h] [ebp+8h]
  int v67; // [esp+18h] [ebp+8h]
  int v68; // [esp+18h] [ebp+8h]
  int v69; // [esp+18h] [ebp+8h]
  int v70; // [esp+18h] [ebp+8h]
  int v71; // [esp+18h] [ebp+8h]
  int v72; // [esp+18h] [ebp+8h]
  int v73; // [esp+18h] [ebp+8h]
  int v74; // [esp+18h] [ebp+8h]
  int v75; // [esp+18h] [ebp+8h]
  int v76; // [esp+18h] [ebp+8h]
  int v77; // [esp+18h] [ebp+8h]
  int v78; // [esp+18h] [ebp+8h]
  int v79; // [esp+18h] [ebp+8h]
  int v80; // [esp+18h] [ebp+8h]
  int v81; // [esp+18h] [ebp+8h]
  int v82; // [esp+1Ch] [ebp+Ch]
  int v83; // [esp+1Ch] [ebp+Ch]
  int v84; // [esp+1Ch] [ebp+Ch]
  int v85; // [esp+1Ch] [ebp+Ch]
  int v86; // [esp+1Ch] [ebp+Ch]
  int v87; // [esp+1Ch] [ebp+Ch]
  int v88; // [esp+1Ch] [ebp+Ch]
  int v89; // [esp+1Ch] [ebp+Ch]
  int v90; // [esp+1Ch] [ebp+Ch]
  int v91; // [esp+1Ch] [ebp+Ch]
  int v92; // [esp+1Ch] [ebp+Ch]
  int v93; // [esp+1Ch] [ebp+Ch]
  int v94; // [esp+1Ch] [ebp+Ch]
  int v95; // [esp+1Ch] [ebp+Ch]
  int v96; // [esp+1Ch] [ebp+Ch]
  int v97; // [esp+1Ch] [ebp+Ch]
  int v98; // [esp+1Ch] [ebp+Ch]

  v82 = sub_41A5E0(a2 + 14);
  v4 = sub_41A5E0(a1 + 14);
  sub_41A590(a1 + 14, v5, v82 + v4);
  v83 = sub_41A5E0(a2 + 28);
  v6 = sub_41A5E0(a1 + 28);
  sub_41A590(a1 + 28, v83, v83 + v6);
  v84 = sub_41A5E0(a2 + 42);
  v7 = sub_41A5E0(a1 + 42);
  sub_41A590(a1 + 42, v8, v84 + v7);
  v85 = sub_41A5E0(a2 + 56);
  v9 = sub_41A5E0(a1 + 56);
  sub_41A590(a1 + 56, v85, v85 + v9);
  v86 = sub_41A5E0(a2 + 70);
  v10 = sub_41A5E0(a1 + 70);
  sub_41A590(a1 + 70, v11, v86 + v10);
  v87 = sub_41A5E0(a2 + 98);
  v12 = sub_41A5E0(a1 + 98);
  sub_41A590(a1 + 98, v87, v87 + v12);
  v88 = sub_41A5E0(a2 + 112);
  v13 = sub_41A5E0(a1 + 112);
  sub_41A590(a1 + 112, v14, v88 + v13);
  v89 = sub_41A5E0(a2 + 126);
  v15 = sub_41A5E0(a1 + 126);
  sub_41A590(a1 + 126, v89, v89 + v15);
  v90 = sub_41A5E0(a2 + 140);
  v16 = sub_41A5E0(a1 + 140);
  sub_41A590(a1 + 140, v17, v90 + v16);
  v91 = sub_41A5E0(a2 + 154);
  v18 = sub_41A5E0(a1 + 154);
  sub_41A590(a1 + 154, v91, v91 + v18);
  v92 = sub_41A5E0(a2 + 224);
  v19 = sub_41A5E0(a1 + 224);
  sub_41A590(a1 + 224, v20, v92 + v19);
  v93 = sub_41A5E0(a2 + 238);
  v21 = sub_41A5E0(a1 + 238);
  sub_41A590(a1 + 238, v93, v93 + v21);
  v63 = COERCE_FLOAT(sub_41A5E0(a2 + 252));
  *(float *)&v94 = COERCE_FLOAT(sub_41A5E0(a1 + 252)) + v63;
  sub_41A590(a1 + 252, v22, v94);
  v95 = sub_41A5E0(a2 + 266);
  v23 = sub_41A5E0(a1 + 266);
  sub_41A590(a1 + 266, v24, v95 + v23);
  v96 = sub_41A5E0(a2 + 280);
  v25 = sub_41A5E0(a1 + 280);
  sub_41A590(a1 + 280, v96, v96 + v25);
  v64 = COERCE_FLOAT(sub_41A5E0(a2 + 294));
  *(float *)&v97 = COERCE_FLOAT(sub_41A5E0(a1 + 294)) + v64;
  sub_41A590(a1 + 294, v26, v97);
  v27 = a2 - a1;
  v28 = a1 + 308;
  v98 = a2 - a1;
  v65 = 4;
  while ( 1 )
  {
    v56 = sub_41A5E0(v27 + v28);
    v29 = sub_41A5E0(v28);
    sub_41A590(v28, v30, v56 + v29);
    v28 += 14;
    if ( --v65 == 0 )
      break;
    v27 = a2 - a1;
  }
  v31 = a1 + 378;
  for ( i = 16; i != 0; --i )
  {
    v57 = sub_41A5E0(v31 + v98);
    v32 = sub_41A5E0(v31);
    sub_41A590(v31, v33, v57 + v32);
    v31 += 14;
  }
  v67 = sub_41A5E0(a2 + 616);
  v34 = sub_41A5E0(a1 + 616);
  sub_41A590(a1 + 616, v67, v67 + v34);
  v68 = sub_41A5E0(a2 + 630);
  v35 = sub_41A5E0(a1 + 630);
  sub_41A590(a1 + 630, v36, v68 + v35);
  v69 = sub_41A5E0(a2 + 644);
  v37 = sub_41A5E0(a1 + 644);
  sub_41A590(a1 + 644, v69, v69 + v37);
  v58 = COERCE_FLOAT(sub_41A5E0(a2 + 658));
  *(float *)&v70 = COERCE_FLOAT(sub_41A5E0(a1 + 658)) + v58;
  sub_41A590(a1 + 658, v38, v70);
  v71 = sub_41A5E0(a2 + 672);
  v39 = sub_41A5E0(a1 + 672);
  sub_41A590(a1 + 672, v40, v71 + v39);
  v72 = sub_41A5E0(a2 + 686);
  v41 = sub_41A5E0(a1 + 686);
  sub_41A590(a1 + 686, v72, v72 + v41);
  v73 = sub_41A5E0(a2 + 700);
  v42 = sub_41A5E0(a1 + 700);
  sub_41A590(a1 + 700, v43, v73 + v42);
  v74 = sub_41A5E0(a2 + 714);
  v44 = sub_41A5E0(a1 + 714);
  sub_41A590(a1 + 714, v74, v74 + v44);
  v75 = sub_41A5E0(a2 + 728);
  v45 = sub_41A5E0(a1 + 728);
  sub_41A590(a1 + 728, v46, v75 + v45);
  v76 = sub_41A5E0(a2 + 808);
  v47 = sub_41A5E0(a1 + 808);
  sub_41A590(a1 + 808, v76, v76 + v47);
  v77 = sub_41A5E0(a2 + 822);
  v48 = sub_41A5E0(a1 + 822);
  sub_41A590(a1 + 822, v49, v77 + v48);
  v59 = COERCE_FLOAT(sub_41A5E0(a2 + 742));
  *(float *)&v78 = COERCE_FLOAT(sub_41A5E0(a1 + 742)) + v59;
  sub_41A590(a1 + 742, v78, v78);
  v60 = COERCE_FLOAT(sub_41A5E0(a2 + 756));
  *(float *)&v79 = COERCE_FLOAT(sub_41A5E0(a1 + 756)) + v60;
  sub_41A590(a1 + 756, v50, v79);
  v61 = COERCE_FLOAT(sub_41A5E0(a2 + 836));
  *(float *)&v80 = COERCE_FLOAT(sub_41A5E0(a1 + 836)) + v61;
  sub_41A590(a1 + 836, v51, v80);
  v52 = a1 + 851;
  for ( j = 2; j != 0; --j )
  {
    v62 = COERCE_FLOAT(sub_41A5E0(v52 + v98));
    *(float *)&v81 = COERCE_FLOAT(sub_41A5E0(v52)) + v62;
    result = sub_41A590(v52, v54, v81);
    v52 += 14;
  }
  return result;
}


// ============================================================
// 【分区 F】怪物自身表现 / 装备挂件 / 剩余杂项族（0x4EA7C0 - 文件末）
//   含：怪物血条与状态图标 HUD（研究 §8 sub_4684F0 的怪物侧）、
//   装备/称号挂件（IRDAppendage 族）、数值防篡写接口、以及若干定点数/字符串工具。
//   研究第 31 轮 P35：无敌开关 this+641 的三类调用点（战斗核心/怪物 58xxx AI/反应族）
//   在本区以 vt+604 广播形式出现。
// ============================================================

// ------------------------------------------------------------
// 0x4EA7C0 sub_4EA7C0 —— 定点数/浮点转换工具（cdecl 双参；逐位拆解）
// 与 0x4E9CF0/0x4EB010 同族 —— 属性数值的定点↔浮点桥接【待验证：具体定标】
// ------------------------------------------------------------
int /*cdecl*/ sub_4EA7C0(int a1, int a2)
{
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // edx
  int v26; // eax
  int v27; // edx
  int v28; // edx
  int v29; // eax
  int v30; // edx
  int v31; // eax
  int v32; // edx
  int v33; // edx
  int v34; // eax
  unsigned int v35; // ebx
  int v36; // eax
  int v37; // edx
  unsigned int v38; // ebx
  int v39; // eax
  int v40; // edx
  int v41; // eax
  int v42; // edx
  int v43; // eax
  int v44; // edx
  int v45; // eax
  int v46; // edx
  int v47; // edx
  int v48; // eax
  int v49; // edx
  int v50; // eax
  int v51; // edx
  int v52; // eax
  int v53; // edx
  int v54; // eax
  int v55; // edx
  int v56; // eax
  int v57; // edx
  int v58; // eax
  int v59; // edx
  int v60; // eax
  int v61; // edx
  int v62; // edx
  int v63; // edx
  unsigned int v64; // esi
  int j; // edi
  int result; // eax
  int v67; // [esp+Ch] [ebp-4h]
  int v68; // [esp+Ch] [ebp-4h]
  float v69; // [esp+Ch] [ebp-4h]
  float v70; // [esp+Ch] [ebp-4h]
  float v71; // [esp+Ch] [ebp-4h]
  float v72; // [esp+Ch] [ebp-4h]
  float v73; // [esp+Ch] [ebp-4h]
  float v74; // [esp+18h] [ebp+8h]
  float v75; // [esp+18h] [ebp+8h]
  int v76; // [esp+18h] [ebp+8h]
  int i; // [esp+18h] [ebp+8h]
  int v78; // [esp+18h] [ebp+8h]
  int v79; // [esp+18h] [ebp+8h]
  int v80; // [esp+18h] [ebp+8h]
  int v81; // [esp+18h] [ebp+8h]
  int v82; // [esp+18h] [ebp+8h]
  int v83; // [esp+18h] [ebp+8h]
  int v84; // [esp+18h] [ebp+8h]
  int v85; // [esp+18h] [ebp+8h]
  int v86; // [esp+18h] [ebp+8h]
  int v87; // [esp+18h] [ebp+8h]
  int v88; // [esp+18h] [ebp+8h]
  int v89; // [esp+18h] [ebp+8h]
  int v90; // [esp+18h] [ebp+8h]
  int v91; // [esp+18h] [ebp+8h]
  int v92; // [esp+18h] [ebp+8h]
  int v93; // [esp+1Ch] [ebp+Ch]
  int v94; // [esp+1Ch] [ebp+Ch]
  int v95; // [esp+1Ch] [ebp+Ch]
  int v96; // [esp+1Ch] [ebp+Ch]
  int v97; // [esp+1Ch] [ebp+Ch]
  int v98; // [esp+1Ch] [ebp+Ch]
  int v99; // [esp+1Ch] [ebp+Ch]
  int v100; // [esp+1Ch] [ebp+Ch]
  int v101; // [esp+1Ch] [ebp+Ch]
  int v102; // [esp+1Ch] [ebp+Ch]
  int v103; // [esp+1Ch] [ebp+Ch]
  int v104; // [esp+1Ch] [ebp+Ch]
  int v105; // [esp+1Ch] [ebp+Ch]
  int v106; // [esp+1Ch] [ebp+Ch]
  int v107; // [esp+1Ch] [ebp+Ch]
  int v108; // [esp+1Ch] [ebp+Ch]
  int v109; // [esp+1Ch] [ebp+Ch]

  v93 = sub_41A5E0(a2 + 14);
  v4 = sub_41A5E0(a1 + 14);
  sub_41A590(a1 + 14, v5, v4 - v93);
  v94 = sub_41A5E0(a2 + 28);
  v6 = sub_41A5E0(a1 + 28);
  sub_41A590(a1 + 28, v7, v6 - v94);
  v95 = sub_41A5E0(a2 + 42);
  v8 = sub_41A5E0(a1 + 42);
  sub_41A590(a1 + 42, v9, v8 - v95);
  v96 = sub_41A5E0(a2 + 56);
  v10 = sub_41A5E0(a1 + 56);
  sub_41A590(a1 + 56, v11, v10 - v96);
  v97 = sub_41A5E0(a2 + 70);
  v12 = sub_41A5E0(a1 + 70);
  sub_41A590(a1 + 70, v13, v12 - v97);
  v98 = sub_41A5E0(a2 + 98);
  v14 = sub_41A5E0(a1 + 98);
  sub_41A590(a1 + 98, v15, v14 - v98);
  v99 = sub_41A5E0(a2 + 112);
  v16 = sub_41A5E0(a1 + 112);
  sub_41A590(a1 + 112, v17, v16 - v99);
  v100 = sub_41A5E0(a2 + 126);
  v18 = sub_41A5E0(a1 + 126);
  sub_41A590(a1 + 126, v19, v18 - v100);
  v101 = sub_41A5E0(a2 + 140);
  v20 = sub_41A5E0(a1 + 140);
  sub_41A590(a1 + 140, v21, v20 - v101);
  v102 = sub_41A5E0(a2 + 154);
  v22 = sub_41A5E0(a1 + 154);
  sub_41A590(a1 + 154, v23, v22 - v102);
  v103 = sub_41A5E0(a2 + 224);
  v24 = sub_41A5E0(a1 + 224);
  sub_41A590(a1 + 224, v25, v24 - v103);
  v104 = sub_41A5E0(a2 + 238);
  v26 = sub_41A5E0(a1 + 238);
  sub_41A590(a1 + 238, v27, v26 - v104);
  v74 = COERCE_FLOAT(sub_41A5E0(a2 + 252));
  *(float *)&v105 = COERCE_FLOAT(sub_41A5E0(a1 + 252)) - v74;
  sub_41A590(a1 + 252, v28, v105);
  v106 = sub_41A5E0(a2 + 266);
  v29 = sub_41A5E0(a1 + 266);
  sub_41A590(a1 + 266, v30, v29 - v106);
  v107 = sub_41A5E0(a2 + 280);
  v31 = sub_41A5E0(a1 + 280);
  sub_41A590(a1 + 280, v32, v31 - v107);
  v75 = COERCE_FLOAT(sub_41A5E0(a2 + 294));
  *(float *)&v108 = COERCE_FLOAT(sub_41A5E0(a1 + 294)) - v75;
  sub_41A590(a1 + 294, v33, v108);
  v34 = a2 - a1;
  v35 = a1 + 308;
  v109 = a2 - a1;
  v76 = 4;
  while ( 1 )
  {
    v67 = sub_41A5E0(v34 + v35);
    v36 = sub_41A5E0(v35);
    sub_41A590(v35, v37, v36 - v67);
    v35 += 14;
    if ( --v76 == 0 )
      break;
    v34 = a2 - a1;
  }
  v38 = a1 + 378;
  for ( i = 16; i != 0; --i )
  {
    v68 = sub_41A5E0(v38 + v109);
    v39 = sub_41A5E0(v38);
    sub_41A590(v38, v40, v39 - v68);
    v38 += 14;
  }
  v78 = sub_41A5E0(a2 + 616);
  v41 = sub_41A5E0(a1 + 616);
  sub_41A590(a1 + 616, v42, v41 - v78);
  v79 = sub_41A5E0(a2 + 630);
  v43 = sub_41A5E0(a1 + 630);
  sub_41A590(a1 + 630, v44, v43 - v79);
  v80 = sub_41A5E0(a2 + 644);
  v45 = sub_41A5E0(a1 + 644);
  sub_41A590(a1 + 644, v46, v45 - v80);
  v69 = COERCE_FLOAT(sub_41A5E0(a2 + 658));
  *(float *)&v81 = COERCE_FLOAT(sub_41A5E0(a1 + 658)) - v69;
  sub_41A590(a1 + 658, v47, v81);
  v82 = sub_41A5E0(a2 + 672);
  v48 = sub_41A5E0(a1 + 672);
  sub_41A590(a1 + 672, v49, v48 - v82);
  v83 = sub_41A5E0(a2 + 686);
  v50 = sub_41A5E0(a1 + 686);
  sub_41A590(a1 + 686, v51, v50 - v83);
  v84 = sub_41A5E0(a2 + 700);
  v52 = sub_41A5E0(a1 + 700);
  sub_41A590(a1 + 700, v53, v52 - v84);
  v85 = sub_41A5E0(a2 + 714);
  v54 = sub_41A5E0(a1 + 714);
  sub_41A590(a1 + 714, v55, v54 - v85);
  v86 = sub_41A5E0(a2 + 728);
  v56 = sub_41A5E0(a1 + 728);
  sub_41A590(a1 + 728, v57, v56 - v86);
  v87 = sub_41A5E0(a2 + 808);
  v58 = sub_41A5E0(a1 + 808);
  sub_41A590(a1 + 808, v59, v58 - v87);
  v88 = sub_41A5E0(a2 + 822);
  v60 = sub_41A5E0(a1 + 822);
  sub_41A590(a1 + 822, v61, v60 - v88);
  v70 = COERCE_FLOAT(sub_41A5E0(a2 + 742));
  *(float *)&v89 = COERCE_FLOAT(sub_41A5E0(a1 + 742)) - v70;
  sub_41A590(a1 + 742, v62, v89);
  v71 = COERCE_FLOAT(sub_41A5E0(a2 + 756));
  *(float *)&v90 = COERCE_FLOAT(sub_41A5E0(a1 + 756)) - v71;
  sub_41A590(a1 + 756, v90, v90);
  v72 = COERCE_FLOAT(sub_41A5E0(a2 + 836));
  *(float *)&v91 = COERCE_FLOAT(sub_41A5E0(a1 + 836)) - v72;
  sub_41A590(a1 + 836, v63, v91);
  v64 = a1 + 851;
  for ( j = 2; j != 0; --j )
  {
    v73 = COERCE_FLOAT(sub_41A5E0(v64 + v109));
    *(float *)&v92 = COERCE_FLOAT(sub_41A5E0(v64)) - v73;
    result = sub_41A590(v64, v92, v92);
    v64 += 14;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4EAD30 sub_4EAD30
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4EAD30(unsigned int *this)
{
  unsigned int result; // eax
  int v3; // eax

  result = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
  if ( result != 0 )
  {
    result = *(this + 335);
    if ( result != 0 )
    {
      v3 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
      result = sub_699000(v3 + 36);
      if ( *(this + 335) + *(this + 334) <= result )
      {
        sub_4E9A10(this);
        return (*(int (/*thiscall*/ **)(unsigned int *))(*this + 300))(this);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EAD80 sub_4EAD80
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4EAD80(int *this)
{
  float v3; // [esp+8h] [ebp-8h]
  float v4; // [esp+Ch] [ebp-4h]

  v3 = (float)*(this + 14);
  v4 = (float)sub_41A5E0((unsigned int)this + 166);
  return (uint64_t)(((double)*(this + 8) + 5.0)
                          * v3
                          * 0.0099999998
                          / v4
                          * (v4 - (double)sub_41A5E0((unsigned int)(this + 298))));
}



// ------------------------------------------------------------
// 0x4EADE0 sub_4EADE0
// ------------------------------------------------------------
char /*thiscall*/ sub_4EADE0(int *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // edi
  int v6; // eax
  const char *v7; // eax
  const CHAR *v9; // [esp-Ch] [ebp-418h]
  char Buffer[1028]; // [esp+4h] [ebp-408h] BYREF
  int v11; // [esp+408h] [ebp-4h]

  v11 = dword_796E50;
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  if ( v2 != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
    LOBYTE(v2) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 308))(v3);
    if ( (uint8_t)v2 != 0 )
    {
      LOBYTE(v2) = sub_41C590((uint32_t *)dword_8F7A24);
      if ( (uint8_t)v2 == 0 && *(this + 37) <= 7 )
      {
        v2 = *(this + 290);
        if ( v2 != 0 )
        {
          LOBYTE(v2) = dword_8F7A24;
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
          {
            v4 = (*(int (/*thiscall*/ **)(int *))(*this + 204))(this);
            LOBYTE(v2) = -59 * v4;
            v5 = v4 / 3600;
            if ( v4 / 3600 < 24 && v4 != 0 )
            {
              v6 = (*(int (/*thiscall*/ **)(int *))(*this + 16))(this);
              v9 = sub_41ACF0((unsigned int **)(v6 + 8));
              v7 = (const char *)sub_422E70(395);
              sprintf(Buffer, v7, v9, v5 + 1);
              LOBYTE(v2) = sub_44E8D0((char *)dword_8F8528, (void *)0x24, (int)Buffer, 0);
            }
          }
        }
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x4EAEE0 sub_4EAEE0
// ------------------------------------------------------------
int /*thiscall*/ sub_4EAEE0(void *this)
{
  unsigned int v1; // eax

  v1 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 176))(this);
  return dword_9B0978[sub_41A5E0(v1)];
}



// ------------------------------------------------------------
// 0x4EAF00 sub_4EAF00
// ------------------------------------------------------------
int /*thiscall*/ sub_4EAF00(void *this)
{
  unsigned int v1; // eax
  int v2; // eax

  v1 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 176))(this);
  v2 = sub_41A5E0(v1);
  if ( v2 < 5 )
    return dword_6FA248[v2];
  else
    return -16776961;
}



// ------------------------------------------------------------
// 0x4EAF30 sub_4EAF30
// ------------------------------------------------------------
int /*thiscall*/ sub_4EAF30(uint32_t *this, int a2)
{
  *(this + 331) = *(uint32_t *)(a2 + 1092);
  *(this + 332) = *(uint32_t *)(a2 + 1096);
  *(this + 333) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4EAF60 sub_4EAF60
// ------------------------------------------------------------
int /*thiscall*/ sub_4EAF60(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 80;
  return result;
}



// ------------------------------------------------------------
// 0x4EAF80 sub_4EAF80
// ------------------------------------------------------------
int /*thiscall*/ sub_4EAF80(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 124;
  return result;
}



// ------------------------------------------------------------
// 0x4EAFB0 sub_4EAFB0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EAFB0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    *v4 = *v3;
    v5 = sub_41A5E0((unsigned int)(v3 + 1));
    sub_41A590((unsigned int)(v4 + 1), v6, v5);
    v7 = sub_41A5E0((unsigned int)v3 + 18);
    sub_41A590((unsigned int)v4 + 18, v8, v7);
    v3 += 8;
    v4 += 8;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x4EB010 sub_4EB010
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EB010(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = *(uint32_t *)(v3 - 32);
    v3 -= 32;
    v4 -= 8;
    *v4 = v5;
    v6 = sub_41A5E0(v3 + 4);
    sub_41A590((unsigned int)(v4 + 1), v7, v6);
    v8 = sub_41A5E0(v3 + 18);
    sub_41A590((unsigned int)v4 + 18, v9, v8);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x4EB070 sub_4EB070
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4EB070(uint32_t *this, unsigned int a2)
{
  int v3; // eax
  int v4; // edx

  sub_41A630((unsigned int)this);
  *this = &cfloat::`vftable';
  v3 = sub_41A5E0(a2);
  sub_41A590((unsigned int)this, v4, v3);
  return this;
}



// ------------------------------------------------------------
// 0x4EB0D0 sub_4EB0D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4EB0D0(uint32_t *this, uint32_t *a2)
{
  *this = *a2;
  sub_46B080(a2 + 1);
  sub_46B080((char *)a2 + 18);
  return this;
}



// ------------------------------------------------------------
// 0x4EB130 sub_4EB130
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EB130(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_4EAFB0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4EB150 sub_4EB150
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EB150(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx

  result = a2;
  for ( i = a1; i != a2; i += 8 )
  {
    *i = *a3;
    v5 = sub_41A5E0((unsigned int)(a3 + 1));
    sub_41A590((unsigned int)(i + 1), v6, v5);
    v7 = sub_41A5E0((unsigned int)a3 + 18);
    sub_41A590((unsigned int)i + 18, v8, v7);
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EB1A0 sub_4EB1A0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EB1A0(int a1, int a2, uint32_t *a3)
{
  return sub_4EB010(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4EB1C0 sub_4EB1C0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EB1C0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v10; // [esp+0h] [ebp-24h] BYREF
  uint32_t *v11; // [esp+Ch] [ebp-18h]
  uint32_t *v12; // [esp+10h] [ebp-14h]
  int *v13; // [esp+14h] [ebp-10h]
  int v14; // [esp+20h] [ebp-4h]

  v3 = a3;
  v13 = &v10;
  v12 = a3;
  v14 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v14) = 1;
    if ( v3 != nullptr )
    {
      *v3 = *a1;
      v11 = v3 + 1;
      sub_41A630((unsigned int)(v3 + 1));
      LOBYTE(v14) = 2;
      v3[1] = &clong::`vftable';
      v5 = sub_41A5E0((unsigned int)(a1 + 1));
      sub_41A590((unsigned int)(v3 + 1), v6, v5);
      LOBYTE(v14) = 3;
      v11 = (uint32_t *)((char *)v3 + 18);
      sub_41A630((unsigned int)v3 + 18);
      LOBYTE(v14) = 4;
      *(uint32_t *)((char *)v3 + 18) = &clong::`vftable';
      v7 = sub_41A5E0((unsigned int)a1 + 18);
      sub_41A590((unsigned int)v3 + 18, v8, v7);
    }
    v3 += 8;
    LOBYTE(v14) = 0;
    a1 += 8;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x4EB2C0 sub_4EB2C0
// ------------------------------------------------------------
char /*thiscall*/ sub_4EB2C0(int *this, float a2)
{
  uint32_t *v3; // ecx
  float v4; // edi
  int v5; // ebx
  uint32_t *v6; // ecx
  int v7; // ebx
  uint32_t *v8; // ecx
  int v9; // ebx
  int *v10; // ebx
  int v11; // edi
  unsigned int v12; // eax
  uint32_t *v13; // ecx
  int v14; // ebx
  uint32_t *v15; // ecx
  int v16; // ebx
  uint32_t *v17; // ecx
  int v18; // ebx
  uint32_t *v19; // ecx
  int v20; // edi
  unsigned int j; // ebx
  int v22; // ecx
  int v23; // edi
  unsigned int k; // ebx
  int v25; // ecx
  int v26; // edi
  int i; // [esp+Ch] [ebp-4h]

  v3 = (uint32_t *)*this;
  v4 = a2;
  if ( v3 != nullptr )
  {
    sub_4922F0(v3, a2);
    v5 = *this;
    sub_4910E0(*this);
    sub_493A60(v5, *(uint32_t *)(v5 + 32));
  }
  v6 = (uint32_t *)*(this + 1);
  if ( v6 != nullptr )
  {
    sub_4922F0(v6, a2);
    v7 = *(this + 1);
    sub_4910E0(v7);
    sub_493A60(v7, *(uint32_t *)(v7 + 32));
  }
  v8 = (uint32_t *)*(this + 2);
  if ( v8 != nullptr )
  {
    sub_4922F0(v8, a2);
    v9 = *(this + 2);
    sub_4910E0(v9);
    sub_493A60(v9, *(uint32_t *)(v9 + 32));
  }
  v10 = this + 3;
  for ( i = 2; i != 0; --i )
  {
    if ( *v10 != 0 )
    {
      sub_4922F0((uint32_t *)*v10, v4);
      v11 = *v10;
      sub_4910E0(*v10);
      sub_493A60(v11, *(uint32_t *)(v11 + 32));
      v4 = a2;
    }
    ++v10;
    LOBYTE(v12) = i - 1;
  }
  v13 = (uint32_t *)*(this + 5);
  if ( v13 != nullptr )
  {
    sub_4922F0(v13, v4);
    v14 = *(this + 5);
    sub_4910E0(v14);
    LOBYTE(v12) = sub_493A60(v14, *(uint32_t *)(v14 + 32));
  }
  v15 = (uint32_t *)*(this + 6);
  if ( v15 != nullptr )
  {
    sub_4922F0(v15, v4);
    v16 = *(this + 6);
    sub_4910E0(v16);
    LOBYTE(v12) = sub_493A60(v16, *(uint32_t *)(v16 + 32));
  }
  v17 = (uint32_t *)*(this + 7);
  if ( v17 != nullptr )
  {
    sub_4922F0(v17, v4);
    v18 = *(this + 7);
    sub_4910E0(v18);
    LOBYTE(v12) = sub_493A60(v18, *(uint32_t *)(v18 + 32));
  }
  v19 = (uint32_t *)*(this + 8);
  if ( v19 != nullptr )
  {
    sub_4922F0(v19, v4);
    v20 = *(this + 8);
    sub_4910E0(v20);
    LOBYTE(v12) = sub_493A60(v20, *(uint32_t *)(v20 + 32));
  }
  for ( j = 0; ; ++j )
  {
    v22 = *(this + 10);
    if ( v22 == 0 )
      break;
    v12 = (*(this + 11) - v22) >> 2;
    if ( j >= v12 )
      break;
    v12 = *(this + 10) + 4 * j;
    if ( *(uint32_t *)(v22 + 4 * j) != 0 )
    {
      sub_4922F0(*(uint32_t **)v12, a2);
      v23 = *(uint32_t *)(4 * j + *(this + 10));
      sub_4910E0(v23);
      LOBYTE(v12) = sub_493A60(v23, *(uint32_t *)(v23 + 32));
    }
  }
  for ( k = 0; ; ++k )
  {
    v25 = *(this + 14);
    if ( v25 == 0 )
      break;
    v12 = (*(this + 15) - v25) >> 2;
    if ( k >= v12 )
      break;
    v12 = 4 * k + *(this + 14);
    if ( *(uint32_t *)(v25 + 4 * k) != 0 )
    {
      sub_4922F0(*(uint32_t **)v12, a2);
      v26 = *(uint32_t *)(4 * k + *(this + 14));
      sub_4910E0(v26);
      LOBYTE(v12) = sub_493A60(v26, *(uint32_t *)(v26 + 32));
    }
  }
  return v12;
}


// ------------------------------------------------------------
// 0x4EB4B0 sub_4EB4B0
// ------------------------------------------------------------
char /*thiscall*/ sub_4EB4B0(int *this, float a2)
{
  float v3; // edi
  int v4; // ebx
  int v5; // ebx
  int v6; // ebx
  int *v7; // ebx
  int v8; // edi
  unsigned int v9; // eax
  int v10; // ebx
  int v11; // ebx
  int v12; // ebx
  int v13; // edi
  unsigned int j; // ebx
  int v15; // ecx
  int v16; // edi
  unsigned int k; // ebx
  int v18; // ecx
  int v19; // edi
  int i; // [esp+Ch] [ebp-4h]

  v3 = a2;
  if ( *this != 0 )
  {
    sub_4923F0(a2);
    v4 = *this;
    sub_4910E0(*this);
    sub_493A60(v4, *(uint32_t *)(v4 + 32));
  }
  if ( *(this + 1) != 0 )
  {
    sub_4923F0(a2);
    v5 = *(this + 1);
    sub_4910E0(v5);
    sub_493A60(v5, *(uint32_t *)(v5 + 32));
  }
  if ( *(this + 2) != 0 )
  {
    sub_4923F0(a2);
    v6 = *(this + 2);
    sub_4910E0(v6);
    sub_493A60(v6, *(uint32_t *)(v6 + 32));
  }
  v7 = this + 3;
  for ( i = 2; i != 0; --i )
  {
    if ( *v7 != 0 )
    {
      sub_4923F0(v3);
      v8 = *v7;
      sub_4910E0(*v7);
      sub_493A60(v8, *(uint32_t *)(v8 + 32));
      v3 = a2;
    }
    ++v7;
    LOBYTE(v9) = i - 1;
  }
  if ( *(this + 5) != 0 )
  {
    sub_4923F0(v3);
    v10 = *(this + 5);
    sub_4910E0(v10);
    LOBYTE(v9) = sub_493A60(v10, *(uint32_t *)(v10 + 32));
  }
  if ( *(this + 6) != 0 )
  {
    sub_4923F0(v3);
    v11 = *(this + 6);
    sub_4910E0(v11);
    LOBYTE(v9) = sub_493A60(v11, *(uint32_t *)(v11 + 32));
  }
  if ( *(this + 7) != 0 )
  {
    sub_4923F0(v3);
    v12 = *(this + 7);
    sub_4910E0(v12);
    LOBYTE(v9) = sub_493A60(v12, *(uint32_t *)(v12 + 32));
  }
  if ( *(this + 8) != 0 )
  {
    sub_4923F0(v3);
    v13 = *(this + 8);
    sub_4910E0(v13);
    LOBYTE(v9) = sub_493A60(v13, *(uint32_t *)(v13 + 32));
  }
  for ( j = 0; ; ++j )
  {
    v15 = *(this + 10);
    if ( v15 == 0 )
      break;
    v9 = (*(this + 11) - v15) >> 2;
    if ( j >= v9 )
      break;
    v9 = *(this + 10) + 4 * j;
    if ( *(uint32_t *)(v15 + 4 * j) != 0 )
    {
      sub_4923F0(a2);
      v16 = *(uint32_t *)(4 * j + *(this + 10));
      sub_4910E0(v16);
      LOBYTE(v9) = sub_493A60(v16, *(uint32_t *)(v16 + 32));
    }
  }
  for ( k = 0; ; ++k )
  {
    v18 = *(this + 14);
    if ( v18 == 0 )
      break;
    v9 = (*(this + 15) - v18) >> 2;
    if ( k >= v9 )
      break;
    v9 = 4 * k + *(this + 14);
    if ( *(uint32_t *)(v18 + 4 * k) != 0 )
    {
      sub_4923F0(a2);
      v19 = *(uint32_t *)(4 * k + *(this + 14));
      sub_4910E0(v19);
      LOBYTE(v9) = sub_493A60(v19, *(uint32_t *)(v19 + 32));
    }
  }
  return v9;
}


// ------------------------------------------------------------
// 0x4EB6A0 sub_4EB6A0
// ------------------------------------------------------------
char /*thiscall*/ sub_4EB6A0(uint32_t *this, float a2)
{
  int v2; // esi
  int i; // edi
  char result; // al

  v2 = *(this + 323);
  for ( i = *(this + 324); v2 != i; v2 += 124 )
    result = sub_4EB2C0((int *)(v2 + 4), a2);
  return result;
}



// ------------------------------------------------------------
// 0x4EB6E0 sub_4EB6E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4EB6E0(uint32_t *this, float a2)
{
  int v2; // esi
  int i; // edi
  char result; // al

  v2 = *(this + 323);
  for ( i = *(this + 324); v2 != i; v2 += 124 )
    result = sub_4EB4B0((int *)(v2 + 4), a2);
  return result;
}



// ------------------------------------------------------------
// 0x4EB720 sub_4EB720
// ------------------------------------------------------------
int /*thiscall*/ sub_4EB720(uint32_t *this)
{
  int result; // eax
  int i; // edi
  int v4; // esi
  uint32_t *v5; // [esp+4h] [ebp-4h]

  result = *(this + 321);
  if ( result != 0
    && (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 236))(this)) != 0
    && (result = *(this + 317)) != 0
    && (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this)) == 0 )
  {
    result = *(this + 314);
    v5 = (uint32_t *)result;
    if ( result == *(this + 315) )
    {
LABEL_13:
      *((uint8_t *)this + 1276) = 1;
    }
    else
    {
      while ( 1 )
      {
        for ( i = 0; i < 18; ++i )
        {
          result = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 321) + 792))(*(this + 321), i);
          v4 = result;
          if ( result != 0 )
          {
            result = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 16))(result) + 4);
            if ( result == *v5 )
            {
              result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 200))(v4);
              if ( (uint8_t)result == 0 )
                break;
            }
          }
        }
        if ( i == 18 )
          break;
        result = (int)++v5;
        if ( v5 == (uint32_t *)*(this + 315) )
          goto LABEL_13;
      }
      *((uint8_t *)this + 1276) = 0;
    }
  }
  else
  {
    *((uint8_t *)this + 1276) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EB800 sub_4EB800
// ------------------------------------------------------------
int /*cdecl*/ sub_4EB800(uint32_t *a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  int result; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // [esp+0h] [ebp-28h] BYREF
  uint32_t *v10; // [esp+Ch] [ebp-1Ch]
  uint32_t *v11; // [esp+10h] [ebp-18h]
  uint32_t *v12; // [esp+14h] [ebp-14h]
  int *v13; // [esp+18h] [ebp-10h]
  int v14; // [esp+24h] [ebp-4h]

  v3 = a1;
  v13 = &v9;
  v12 = a1;
  v14 = 0;
  while ( 1 )
  {
    result = a2;
    if ( a2 == 0 )
      break;
    v11 = v3;
    LOBYTE(v14) = 1;
    if ( v3 != nullptr )
    {
      *v3 = *a3;
      v10 = v3 + 1;
      sub_41A630((unsigned int)(v3 + 1));
      LOBYTE(v14) = 2;
      v3[1] = &clong::`vftable';
      v5 = sub_41A5E0((unsigned int)(a3 + 1));
      sub_41A590((unsigned int)(v3 + 1), v6, v5);
      LOBYTE(v14) = 3;
      v10 = (uint32_t *)((char *)v3 + 18);
      sub_41A630((unsigned int)v3 + 18);
      LOBYTE(v14) = 4;
      *(uint32_t *)((char *)v3 + 18) = &clong::`vftable';
      v7 = sub_41A5E0((unsigned int)a3 + 18);
      sub_41A590((unsigned int)v3 + 18, v8, v7);
    }
    v3 += 8;
    LOBYTE(v14) = 0;
    --a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EB900 sub_4EB900
// ------------------------------------------------------------
char */*thiscall*/ sub_4EB900(uint32_t *this, unsigned int a2)
{
  int v2; // eax
  int v3; // esi
  unsigned int v4; // ecx
  const char *v5; // eax
  const char *v6; // eax
  int v7; // ebx
  const char *v8; // eax
  char *result; // eax
  const char *v10; // eax
  const char *v11; // eax
  const char *v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  double v17; // [esp+0h] [ebp-18h]
  int v18; // [esp+0h] [ebp-18h]
  int v19; // [esp+0h] [ebp-18h]
  double v20; // [esp+4h] [ebp-14h]
  const char *v21; // [esp+8h] [ebp-10h]
  const char *v22; // [esp+8h] [ebp-10h]
  int v23; // [esp+8h] [ebp-10h]
  int v24; // [esp+8h] [ebp-10h]

  if ( a2 == -1 )
    return (char *)sub_422E70(378);
  v2 = *(this + 230);
  if ( v2 == 0 || a2 >= (*(this + 231) - v2) / 80 )
    return (char *)sub_422E70(378);
  v3 = *(this + 230) + 80 * a2;
  if ( *(uint32_t *)v3 == 0 )
    return (char *)sub_422E70(394);
  v4 = v3 + 5;
  if ( *(uint8_t *)(v3 + 4) != 0 )
  {
    if ( COERCE_FLOAT(sub_41A5E0(v4)) < 1.0 )
      v5 = (const char *)sub_422E70(380);
    else
      v5 = (const char *)sub_422E70(379);
    v21 = v5;
    v17 = COERCE_FLOAT(sub_41A5E0(v3 + 5));
    v6 = (const char *)sub_422E70(*(uint32_t *)v3 + 1276);
LABEL_15:
    sprintf(byte_9B0990, "%s %.1f%%%% %s", v6, v17, v21);
    return byte_9B0990;
  }
  else
  {
    v7 = (uint64_t)COERCE_FLOAT(sub_41A5E0(v4));
    switch ( *(uint32_t *)v3 )
    {
      case 0x1D:
        if ( sub_43B5A0((void *)(v3 + 5)) < 0.0 )
          v15 = sub_422E70(391);
        else
          v15 = sub_422E70(390);
        v23 = v15;
        v18 = sub_422E70(*(uint32_t *)v3 + 1276);
        sprintf(byte_9B0990, "%s %d%%%% %s", v18, v7 / 10, v23);
        goto LABEL_35;
      case 0x21:
        if ( sub_43B5A0((void *)(v3 + 5)) < 0.0 )
          v10 = (const char *)sub_422E70(384);
        else
          v10 = (const char *)sub_422E70(383);
        v22 = v10;
        v11 = (const char *)sub_422E70(*(uint32_t *)v3 + 1276);
        sprintf(byte_9B0990, "%s %d.%03dkg %s", v11, v7 / 1000, abs32(v7 % 1000), v22);
        return byte_9B0990;
      case 0x22:
        v20 = sub_43B5A0((void *)(v3 + 5)) * 0.59999996;
        v12 = (const char *)sub_422E70(385);
        goto LABEL_21;
      case 0x23:
        v20 = sub_43B5A0((void *)(v3 + 5)) * 3.0;
        v12 = (const char *)sub_422E70(386);
        goto LABEL_21;
      case 0x24:
        v20 = sub_43B5A0((void *)(v3 + 5));
        v12 = (const char *)sub_422E70(387);
        goto LABEL_21;
      case 0x25:
      case 0x26:
      case 0x27:
        if ( sub_43B5A0((void *)(v3 + 5)) < 0.0 )
          v8 = (const char *)sub_422E70(382);
        else
          v8 = (const char *)sub_422E70(381);
        v21 = v8;
        v17 = sub_43B5A0((void *)(v3 + 5)) * 0.1;
        v6 = (const char *)sub_422E70(*(uint32_t *)v3 + 1276);
        goto LABEL_15;
      case 0x2B:
        v13 = sub_41A5E0(v3 + 24);
        v14 = sub_47E720(*(uint32_t *)(v3 + 20), v13);
        if ( v14 != 0 )
        {
          HIDWORD(v20) = sub_41A5E0(v3 + 38);
          LODWORD(v20) = sub_41ACF0(v14 + 20);
          v12 = (const char *)sub_422E70(389);
LABEL_21:
          sprintf(byte_9B0990, v12, v20);
          result = byte_9B0990;
        }
        else
        {
          result = (char *)sub_422E70(388);
        }
        break;
      default:
        if ( sub_43B5A0((void *)(v3 + 5)) < 0.0 )
          v16 = sub_422E70(393);
        else
          v16 = sub_422E70(392);
        v24 = v16;
        v19 = sub_422E70(*(uint32_t *)v3 + 1276);
        sprintf(byte_9B0990, "%s %d %s", v19, v7, v24);
LABEL_35:
        result = byte_9B0990;
        break;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4EBC70 sub_4EBC70
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4EBC70(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_4EB1C0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4EBC90 sub_4EBC90
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4EBC90(uint32_t *a1, int a2, uint32_t *a3)
{
  sub_4EB800(a1, a2, a3);
  return &a1[8 * a2];
}



// ------------------------------------------------------------
// 0x4EBCC0 sub_4EBCC0
// ------------------------------------------------------------
char */*thiscall*/ sub_4EBCC0(char *this, int a2)
{
  *(uint32_t *)this = *(uint32_t *)a2;
  *(this + 4) = *(uint8_t *)(a2 + 4);
  sub_4EB070(this + 5, a2 + 5);
  sub_4EB0D0((uint32_t *)this + 5, (uint32_t *)(a2 + 20));
  *((uint32_t *)this + 19) = 15;
  *((uint32_t *)this + 18) = 0;
  *(this + 56) = 0;
  sub_4014D0((size_t *)this + 13, (size_t *)(a2 + 52), 0, 0xFFFFFFFF);
  return this;
}



// ------------------------------------------------------------
// 0x4EBD50 sub_4EBD50
// ------------------------------------------------------------
int /*fastcall*/ sub_4EBD50(int a1, int a2)
{
  int v3; // edx
  int v4; // edx

  *(uint32_t *)a1 = 0;
  *(uint8_t *)(a1 + 4) = 0;
  sub_41A590(a1 + 5, a2, 0);
  sub_4015C0((size_t *)(a1 + 52), szPassword, 0);
  *(uint32_t *)(a1 + 20) = 4;
  sub_41A590(a1 + 24, v3, 0);
  return sub_41A590(a1 + 38, v4, 0);
}



// ------------------------------------------------------------
// 0x4EBDB0 sub_4EBDB0
// ------------------------------------------------------------
void /*thiscall*/ sub_4EBDB0(uint32_t *this, int a2, int a3)
{
  unsigned int v4; // esi
  unsigned int v5; // ebx
  int v6; // eax
  int v7; // esi
  float v8; // eax
  int v9; // edx
  double v10; // st7
  float v11; // [esp+0h] [ebp-14h]
  float v12; // [esp+0h] [ebp-14h]
  float v13; // [esp+0h] [ebp-14h]

  v4 = (unsigned int)(this + 233);
  if ( sub_41A5E0((unsigned int)(this + 233)) != -1 )
  {
    v5 = sub_41A5E0(v4);
    v6 = *(this + 230);
    if ( v6 != 0 && v5 < (*(this + 231) - v6) / 80 )
    {
      v7 = *(this + 230) + 80 * sub_41A5E0(v4);
      v8 = COERCE_FLOAT(sub_41A5E0(v7 + 5));
      switch ( *(uint32_t *)v7 )
      {
        case 1:
          if ( *(uint8_t *)(v7 + 4) != 0 )
          {
            sub_4AED60((void *)(a3 + 18), v8);
          }
          else
          {
            v10 = sub_433F60(a2, 2) * v8;
            sub_4450B0((uint64_t)v10);
          }
          return;
        case 2:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 46), v8);
          return;
        case 3:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 74), v8);
          return;
        case 4:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 102), v8);
          return;
        case 5:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 130), v8);
          return;
        case 6:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 158), v8);
          return;
        case 7:
          if ( *(uint8_t *)(v7 + 4) != 0 )
            goto LABEL_94;
          goto LABEL_93;
        case 8:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          goto LABEL_94;
        case 9:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          goto LABEL_94;
        case 0xA:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          goto LABEL_94;
        case 0xB:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 228), v8);
          break;
        case 0xC:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 242), v8);
          break;
        case 0xD:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 256), v8);
          break;
        case 0xE:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 270), v8);
          break;
        case 0x10:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 508), v8);
          break;
        case 0x11:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 522), v8);
          break;
        case 0x12:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 536), v8);
          break;
        case 0x13:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 550), v8);
          break;
        case 0x14:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 564), v8);
          break;
        case 0x15:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 578), v8);
          break;
        case 0x16:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 592), v8);
          break;
        case 0x17:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 606), v8);
          break;
        case 0x18:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 620), v8);
          break;
        case 0x19:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 634), v8);
          break;
        case 0x1A:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 648), v8);
          break;
        case 0x1B:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 662), v8);
          break;
        case 0x1C:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 676), v8);
          break;
        case 0x1D:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 690), v8);
          break;
        case 0x1E:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 704), v8);
          break;
        case 0x1F:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 718), v8);
          break;
        case 0x21:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 746), v8);
          break;
        case 0x22:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          goto LABEL_94;
        case 0x23:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          goto LABEL_94;
        case 0x25:
          if ( *(uint8_t *)(v7 + 4) != 0 )
            goto LABEL_94;
          v11 = v8 * 0.001;
          sub_4AED60((void *)(a3 + 830), v11);
          break;
        case 0x26:
          if ( *(uint8_t *)(v7 + 4) != 0 )
            goto LABEL_94;
          v12 = v8 * 0.001;
          sub_4AED60((void *)(a3 + 858), v12);
          break;
        case 0x27:
          if ( *(uint8_t *)(v7 + 4) != 0 )
            goto LABEL_94;
          v13 = v8 * 0.001;
          sub_4AED60((void *)(a3 + 886), v13);
          break;
        case 0x28:
          if ( *(uint8_t *)(v7 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(a3 + 914), v8);
          break;
        case 0x29:
          if ( *(uint8_t *)(v7 + 4) != 0 )
LABEL_94:
            sub_4EBD50(v7, v9);
          else
LABEL_93:
            sub_4450B0((uint64_t)v8);
          break;
        default:
          return;
      }
    }
  }
}


// ------------------------------------------------------------
// 0x4EC7C0 sub_4EC7C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4EC7C0(int *this, int a2)
{
  int *v2; // ebx
  int result; // eax
  int v4; // esi
  int *v6; // esi
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // eax
  int v18; // edx
  int v19; // eax
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // edx
  int v27; // eax
  int v28; // edx
  int v29; // eax
  int v30; // edx
  unsigned int v31; // ebx
  int v32; // eax
  int v33; // eax
  int v34; // edx
  bool v35; // zf
  unsigned int v36; // ebx
  int v37; // eax
  int v38; // edx
  int v39; // eax
  int v40; // edx
  bool v41; // cc
  int v42; // eax
  int v43; // eax
  int v44; // edx
  int v45; // eax
  int v46; // edx
  int v47; // edx
  int v48; // edx
  int v49; // eax
  int v50; // edx
  int v51; // eax
  int v52; // edx
  float v53; // eax
  int v54; // edx
  int v55; // eax
  int v56; // eax
  int v57; // edx
  int v58; // eax
  int v59; // [esp+8h] [ebp-10h]
  int v60; // [esp+8h] [ebp-10h]
  int v61; // [esp+8h] [ebp-10h]
  int v62; // [esp+8h] [ebp-10h]
  float v63; // [esp+8h] [ebp-10h]
  int i; // [esp+10h] [ebp-8h]
  float v66; // [esp+14h] [ebp-4h]
  float v67; // [esp+14h] [ebp-4h]
  int v68; // [esp+14h] [ebp-4h]
  unsigned int v69; // [esp+14h] [ebp-4h]
  int v70; // [esp+20h] [ebp+8h]
  int v71; // [esp+20h] [ebp+8h]
  int v72; // [esp+20h] [ebp+8h]
  int v73; // [esp+20h] [ebp+8h]
  int v74; // [esp+20h] [ebp+8h]
  int v75; // [esp+20h] [ebp+8h]
  int v76; // [esp+20h] [ebp+8h]
  int v77; // [esp+20h] [ebp+8h]
  int v78; // [esp+20h] [ebp+8h]
  int v79; // [esp+20h] [ebp+8h]
  int v80; // [esp+20h] [ebp+8h]
  int v81; // [esp+20h] [ebp+8h]
  int v82; // [esp+20h] [ebp+8h]
  int v83; // [esp+20h] [ebp+8h]
  int v84; // [esp+20h] [ebp+8h]
  int v85; // [esp+20h] [ebp+8h]
  int v86; // [esp+20h] [ebp+8h]
  unsigned int v87; // [esp+20h] [ebp+8h]
  int v88; // [esp+20h] [ebp+8h]
  int v89; // [esp+20h] [ebp+8h]
  int v90; // [esp+20h] [ebp+8h]
  int v91; // [esp+20h] [ebp+8h]
  float v92; // [esp+20h] [ebp+8h]
  int v93; // [esp+20h] [ebp+8h]
  int v94; // [esp+20h] [ebp+8h]
  int v95; // [esp+20h] [ebp+8h]
  int v96; // [esp+20h] [ebp+8h]
  int v97; // [esp+20h] [ebp+8h]
  int v98; // [esp+20h] [ebp+8h]
  int v99; // [esp+20h] [ebp+8h]
  int v100; // [esp+20h] [ebp+8h]
  int v101; // [esp+20h] [ebp+8h]
  int v102; // [esp+20h] [ebp+8h]
  int v103; // [esp+20h] [ebp+8h]
  int v104; // [esp+20h] [ebp+8h]
  int v105; // [esp+20h] [ebp+8h]
  int v106; // [esp+20h] [ebp+8h]
  int v107; // [esp+20h] [ebp+8h]

  v2 = this;
  if ( (*(uint8_t (/*fastcall*/ **)(int *))(*this + 200))(this) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2[321] + 40))(v2[321], 273);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2[321] + 1084))(v2[321], v2[37]);
      v4 = result;
      if ( result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 200))(result);
        if ( (uint8_t)result == 0 )
          return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 132))(v4, a2);
      }
    }
  }
  else
  {
    for ( i = 0; i < 2; ++i )
    {
      if ( i != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*v2 + 224))(v2) == 0 )
          break;
        v6 = (int *)v2[317];
      }
      else
      {
        v6 = v2 + 53;
      }
      v70 = sub_41A5E0((unsigned int)v6 + 14);
      v7 = (*(int (/*thiscall*/ **)(int *))(*v2 + 212))(v2);
      v71 = (uint64_t)(sub_433F60(v7, 2) * (double)v70);
      v8 = sub_41A5E0(a2 + 4);
      sub_41A590(a2 + 4, v9, v71 + v8);
      v72 = sub_41A5E0((unsigned int)(v6 + 7));
      v10 = sub_41A5E0(a2 + 32);
      sub_41A590(a2 + 32, v72, v72 + v10);
      v73 = sub_41A5E0((unsigned int)v6 + 42);
      v11 = sub_41A5E0(a2 + 60);
      sub_41A590(a2 + 60, v12, v73 + v11);
      v74 = sub_41A5E0((unsigned int)(v6 + 14));
      v13 = sub_41A5E0(a2 + 88);
      sub_41A590(a2 + 88, v74, v74 + v13);
      v75 = sub_41A5E0((unsigned int)v6 + 70);
      v14 = sub_41A5E0(a2 + 116);
      sub_41A590(a2 + 116, v15, v75 + v14);
      v76 = sub_41A5E0((unsigned int)v6 + 98);
      v16 = sub_41A5E0(a2 + 144);
      sub_41A590(a2 + 144, v76, v76 + v16);
      v77 = sub_41A5E0((unsigned int)(v6 + 28));
      v17 = sub_41A5E0(a2 + 1012);
      sub_41A590(a2 + 1012, v18, v77 + v17);
      v78 = sub_41A5E0((unsigned int)v6 + 126);
      v19 = sub_41A5E0(a2 + 1040);
      sub_41A590(a2 + 1040, v78, v78 + v19);
      v79 = sub_41A5E0((unsigned int)(v6 + 35));
      v20 = sub_41A5E0(a2 + 1068);
      sub_41A590(a2 + 1068, v21, v79 + v20);
      v80 = sub_41A5E0((unsigned int)v6 + 154);
      v22 = sub_41A5E0(a2 + 1096);
      sub_41A590(a2 + 1096, v80, v80 + v22);
      v81 = sub_41A5E0((unsigned int)(v6 + 56));
      v23 = sub_41A5E0(a2 + 1124);
      sub_41A590(a2 + 1124, v24, v81 + v23);
      v82 = sub_41A5E0((unsigned int)v6 + 238);
      v25 = sub_41A5E0(a2 + 1138);
      sub_41A590(a2 + 1138, v82, v82 + v25);
      v66 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v6 + 63)));
      *(float *)&v83 = COERCE_FLOAT(sub_41A5E0(a2 + 1152)) + v66;
      sub_41A590(a2 + 1152, v26, v83);
      v84 = sub_41A5E0((unsigned int)v6 + 266);
      v27 = sub_41A5E0(a2 + 1166);
      sub_41A590(a2 + 1166, v28, v84 + v27);
      v85 = sub_41A5E0((unsigned int)(v6 + 70));
      v29 = sub_41A5E0(a2 + 1180);
      sub_41A590(a2 + 1180, v85, v85 + v29);
      v67 = COERCE_FLOAT(sub_41A5E0((unsigned int)v6 + 294));
      *(float *)&v86 = COERCE_FLOAT(sub_41A5E0(a2 + 1194)) + v67;
      sub_41A590(a2 + 1194, v30, v86);
      v31 = a2 + 172;
      v87 = (unsigned int)(v6 + 77);
      v68 = 4;
      do
      {
        v59 = sub_41A5E0(v87);
        v32 = sub_41A5E0(v31);
        sub_41A590(v31, v59, v59 + v32);
        v60 = sub_41A5E0((unsigned int)(v6 + 91));
        v33 = sub_41A5E0(v31);
        sub_41A590(v31, v34, v60 + v33);
        v31 += 14;
        v35 = v68 == 1;
        v87 += 14;
        --v68;
      }
      while ( !v35 );
      v88 = 0;
      v36 = a2 + 284;
      v69 = (unsigned int)v6 + 378;
      do
      {
        v61 = sub_41A5E0(v69);
        v37 = sub_41A5E0(v36);
        sub_41A590(v36, v38, v61 + v37);
        if ( sub_497040(v88) != 17 )
        {
          v62 = sub_41A5E0((unsigned int)v6 + 602);
          v39 = sub_41A5E0(v36);
          sub_41A590(v36, v40, v62 + v39);
        }
        v36 += 14;
        v41 = ++v88 < 16;
        v69 += 14;
      }
      while ( v41 );
      v89 = sub_41A5E0((unsigned int)(v6 + 154));
      v42 = sub_41A5E0(a2 + 732);
      sub_41A590(a2 + 732, v89, v89 + v42);
      v90 = sub_41A5E0((unsigned int)v6 + 630);
      v43 = sub_41A5E0(a2 + 760);
      sub_41A590(a2 + 760, v44, v90 + v43);
      v91 = sub_41A5E0((unsigned int)(v6 + 161));
      v45 = sub_41A5E0(a2 + 788);
      sub_41A590(a2 + 788, v91, v91 + v45);
      v92 = COERCE_FLOAT(sub_41A5E0((unsigned int)v6 + 658));
      *(float *)&v93 = v92 * 0.0099999998 + COERCE_FLOAT(sub_41A5E0(a2 + 802));
      sub_41A590(a2 + 802, v46, v93);
      v94 = sub_41A5E0((unsigned int)(v6 + 168));
      *(float *)&v95 = (double)v94 * 0.001 + COERCE_FLOAT(sub_41A5E0(a2 + 830));
      sub_41A590(a2 + 830, v47, v95);
      v96 = sub_41A5E0((unsigned int)v6 + 686);
      *(float *)&v97 = (double)v96 * 0.001 + COERCE_FLOAT(sub_41A5E0(a2 + 858));
      sub_41A590(a2 + 858, v97, v97);
      if ( *(this + 37) != 8 )
      {
        v98 = sub_41A5E0((unsigned int)v6 + 686);
        *(float *)&v99 = (double)v98 * 0.001 + COERCE_FLOAT(sub_41A5E0(a2 + 1292));
        sub_41A590(a2 + 1292, v48, v99);
      }
      v100 = sub_41A5E0((unsigned int)(v6 + 175));
      *(float *)&v101 = (double)v100 * 0.001 + COERCE_FLOAT(sub_41A5E0(a2 + 886));
      sub_41A590(a2 + 886, v101, v101);
      v102 = sub_41A5E0((unsigned int)v6 + 714);
      v49 = sub_41A5E0(a2 + 900);
      sub_41A590(a2 + 900, v50, v102 + v49);
      v103 = sub_41A5E0((unsigned int)(v6 + 182));
      v51 = sub_41A5E0(a2 + 928);
      sub_41A590(a2 + 928, v103, v103 + v51);
      v63 = COERCE_FLOAT(sub_41A5E0((unsigned int)v6 + 742));
      *(float *)&v104 = COERCE_FLOAT(sub_41A5E0(a2 + 1208)) + v63;
      sub_41A590(a2 + 1208, v52, v104);
      v53 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v6 + 189)));
      *(float *)&v105 = COERCE_FLOAT(sub_41A5E0(a2 + 1222)) + v53;
      sub_41A590(a2 + 1222, v54, v105);
      v2 = this;
    }
    v106 = (uint64_t)((double)v2[16] * flt_791E20);
    v55 = sub_41A5E0(a2 + 984);
    sub_41A590(a2 + 984, v106, v106 + v55);
    v107 = (uint64_t)((double)v2[16] * flt_9B06D0 * flt_791E20 * 0.001);
    v56 = sub_41A5E0(a2 + 816);
    sub_41A590(a2 + 816, v57, v56 - v107);
    v58 = (*(int (/*thiscall*/ **)(int *))(*v2 + 212))(v2);
    return sub_4EBDB0(v58, a2);
  }
  return result;
}


// ------------------------------------------------------------
// 0x4ECED0 sub_4ECED0
// ------------------------------------------------------------
void **/*thiscall*/ sub_4ECED0(unsigned int **this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edi
  const char *v5; // eax
  CHAR *v6; // eax
  void **result; // eax
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int v9; // [esp+84h] [ebp-4h]

  v9 = dword_796E50;
  if ( (dword_9B0AAC & 1) == 0 )
  {
    dword_9B0AAC |= 1u;
    dword_9B0AA8 = 15;
    dword_9B0AA4 = 0;
    LOBYTE(dword_9B0A94) = 0;
    atexit(sub_6BFBA0);
  }
  v2 = ((int (/*thiscall*/ *)(unsigned int **))(*this)[47])(this);
  if ( sub_41A5E0(v2 + 4) != 0 )
  {
    v3 = ((int (/*thiscall*/ *)(unsigned int **))(*this)[47])(this);
    v4 = sub_41A5E0(v3 + 4);
    v5 = sub_41ACF0(this + 4);
    sprintf(Buffer, "+%d %s", v4, v5);
    sub_4015C0(&dword_9B0A90, Buffer, strlen(Buffer));
  }
  else
  {
    v6 = (CHAR *)sub_41ACF0(this + 4);
    sub_4015C0(&dword_9B0A90, v6, strlen(v6));
  }
  result = (void **)dword_9B0A94;
  if ( (unsigned int)dword_9B0AA8 < 0x10 )
    return &dword_9B0A94;
  return result;
}



// ------------------------------------------------------------
// 0x4ECFE0 sub_4ECFE0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4ECFE0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ebx
  unsigned int v4; // esi
  unsigned int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx

  v3 = a1;
  if ( a1 != a2 )
  {
    v4 = (unsigned int)a3 + 38;
    v5 = (unsigned int)a1 + 38;
    do
    {
      *a3 = *v3;
      *(uint8_t *)(v4 - 34) = *(uint8_t *)(v5 - 34);
      v6 = sub_41A5E0(v5 - 33);
      sub_41A590(v4 - 33, v7, v6);
      *(uint32_t *)(v4 - 18) = *(uint32_t *)(v5 - 18);
      v8 = sub_41A5E0(v5 - 14);
      sub_41A590(v4 - 14, v9, v8);
      v10 = sub_41A5E0(v5);
      sub_41A590(v4, v11, v10);
      sub_4014D0((size_t *)(v4 + 14), (size_t *)(v5 + 14), 0, 0xFFFFFFFF);
      v3 += 20;
      v4 += 80;
      v5 += 80;
      a3 += 20;
    }
    while ( v3 != a2 );
  }
  return a3;
}



// ------------------------------------------------------------
// 0x4ED080 sub_4ED080
// ------------------------------------------------------------
int /*thiscall*/ sub_4ED080(int this, int a2, unsigned int a3, int a4)
{
  int v5; // edx
  int v6; // ecx
  unsigned int v7; // eax
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // eax
  char *v13; // ebx
  int v14; // ecx
  int v15; // eax
  unsigned int v16; // edi
  char *v17; // eax
  int v18; // edi
  char *v19; // edi
  int v20; // eax
  int v22; // [esp-18h] [ebp-5Ch]
  void *v23; // [esp-18h] [ebp-5Ch]
  int v24; // [esp-Ch] [ebp-50h]
  unsigned int v25; // [esp-8h] [ebp-4Ch]
  int v26; // [esp+0h] [ebp-44h] BYREF
  char v27[4]; // [esp+Ch] [ebp-38h] BYREF
  char v28[14]; // [esp+10h] [ebp-34h] BYREF
  char v29[14]; // [esp+1Eh] [ebp-26h] BYREF
  void *Block; // [esp+2Ch] [ebp-18h]
  int v31; // [esp+30h] [ebp-14h]
  int *v32; // [esp+34h] [ebp-10h]
  int v33; // [esp+40h] [ebp-4h]
  int v34; // [esp+50h] [ebp+Ch]
  int v35; // [esp+54h] [ebp+10h]

  v32 = &v26;
  v31 = this;
  sub_4EB0D0(a4);
  v5 = *(uint32_t *)(this + 4);
  v6 = 0;
  v33 = 0;
  if ( v5 != 0 )
    v7 = (*(uint32_t *)(this + 12) - v5) >> 5;
  else
    v7 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v6 = (*(uint32_t *)(this + 8) - v5) >> 5;
    if ( 0x7FFFFFF - v6 < a3 )
      sub_434730(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 5;
    else
      v9 = 0;
    if ( v7 >= a3 + v9 )
    {
      v17 = *(char **)(this + 8);
      Block = v17;
      if ( (int)&v17[-a2] >> 5 >= a3 )
      {
        v19 = &v17[-32 * a3];
        v20 = sub_4EB1C0(v19, v17, v17);
        v23 = Block;
        *(uint32_t *)(this + 8) = v20;
        sub_4EB1A0(a2, v19, v23);
        sub_4EB150(a2, a2 + 32 * a3, v27);
      }
      else
      {
        sub_4EB1C0(a2, v17, a2 + 32 * a3);
        v25 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 5);
        v24 = *(uint32_t *)(this + 8);
        LOBYTE(v33) = 3;
        sub_4EBC90(v24, v25, v27);
        v18 = 32 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v18;
        v33 = 0;
        sub_4EB150(a2, v18 - 32 * a3, v27);
      }
    }
    else
    {
      if ( 0x7FFFFFF - (v7 >> 1) >= v7 )
        v10 = (v7 >> 1) + v7;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) >> 5;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(uint32_t *)(this + 8) - v5) >> 5;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v35 = 32 * v10;
      v13 = (char *)operator new(32 * v10);
      v22 = *(uint32_t *)(this + 4);
      Block = v13;
      LOBYTE(v33) = 1;
      v34 = sub_4EB1C0(v22, a2, v13);
      sub_4EB800(v34, a3, v27);
      sub_4EB1C0(a2, *(uint32_t *)(this + 8), 32 * a3 + v34);
      v14 = *(uint32_t *)(this + 4);
      v33 = 0;
      if ( v14 != 0 )
        v15 = (*(uint32_t *)(this + 8) - v14) >> 5;
      else
        v15 = 0;
      v16 = v15 + a3;
      if ( v14 != 0 )
      {
        sub_434100(v14, *(uint32_t *)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &v13[v35];
      *(uint32_t *)(this + 8) = &v13[32 * v16];
      *(uint32_t *)(this + 4) = v13;
    }
  }
  v33 = 5;
  sub_41A580(v29);
  v33 = -1;
  return sub_41A580(v28);
}


// ------------------------------------------------------------
// 0x4ED330 sub_4ED330
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ED330(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // eax
  uint32_t *v6; // [esp-14h] [ebp-34h]
  uint32_t *v7; // [esp-10h] [ebp-30h]
  uint32_t *v8; // [esp-Ch] [ebp-2Ch]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *v10; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v3 = *(uint32_t *)(a2 + 4);
  v11 = &v9;
  v10 = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(a2 + 8) - v3) >> 2;
  else
    v4 = 0;
  if ( (uint8_t)sub_42AA50(v4) != 0 )
  {
    v8 = (uint32_t *)*(this + 1);
    v7 = *(uint32_t **)(a2 + 8);
    v6 = *(uint32_t **)(a2 + 4);
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, v8);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4ED3D0 sub_4ED3D0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4ED3D0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_4ECFE0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4ED3F0 sub_4ED3F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4ED3F0(int this, int a2)
{
  int v3; // ecx
  unsigned int v4; // edx
  void *v6; // ecx
  unsigned int v7; // ebx
  int v8; // eax
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // eax
  void *v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t *)(a2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(a2 + 8) - v3) >> 2) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  v6 = *(void **)(this + 4);
  if ( v6 != nullptr )
    v7 = (*(uint32_t *)(this + 8) - (int)v6) >> 2;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    memcpy_0(v6, *(const void **)(a2 + 4), 4 * ((*(uint32_t *)(a2 + 8) - *(uint32_t *)(a2 + 4)) >> 2));
    v8 = *(uint32_t *)(a2 + 4);
    if ( v8 != 0 )
      v9 = *(uint32_t *)(this + 4) + 4 * ((*(uint32_t *)(a2 + 8) - v8) >> 2);
    else
      v9 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = v9;
    return this;
  }
  if ( v6 != nullptr )
    v10 = (*(uint32_t *)(this + 12) - (int)v6) >> 2;
  else
    v10 = 0;
  if ( v4 > v10 )
  {
    if ( v6 != nullptr )
      j__free(*(void **)(this + 4));
    v13 = *(uint32_t *)(a2 + 4);
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(a2 + 8) - v13) >> 2;
    else
      v14 = 0;
    if ( (uint8_t)sub_42AA50(v14) != 0 )
      *(uint32_t *)(this + 8) = sub_55E7F0(*(void **)(a2 + 4), *(uint32_t *)(a2 + 8), *(void **)(this + 4));
    return this;
  }
  if ( v6 != nullptr )
    v11 = (*(uint32_t *)(this + 8) - (int)v6) >> 2;
  else
    v11 = 0;
  v12 = (void *)(*(uint32_t *)(a2 + 4) + 4 * v11);
  sub_433A30(*(void **)(a2 + 4), (int)v12, *(void **)(this + 4));
  *(uint32_t *)(this + 8) = sub_55E7F0(v12, *(uint32_t *)(a2 + 8), *(void **)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x4ED540 sub_4ED540
// ------------------------------------------------------------
int */*thiscall*/ sub_4ED540(int *this, int *a2)
{
  uint32_t *v3; // ebx
  unsigned int v4; // eax
  uint32_t *v6; // ecx
  unsigned int v7; // edx
  uint32_t *v8; // eax
  int v9; // eax
  int v10; // edi
  unsigned int v11; // edx
  int v12; // eax
  uint32_t *v13; // ebx
  int v14; // ecx
  int v15; // eax

  if ( this == a2 )
    return this;
  v3 = (uint32_t *)a2[1];
  if ( v3 == nullptr || (v4 = (a2[2] - (int)v3) >> 5) == 0 )
  {
    sub_434140(this);
    return this;
  }
  v6 = (uint32_t *)*(this + 1);
  if ( v6 != nullptr )
    v7 = (*(this + 2) - (int)v6) >> 5;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    v8 = sub_4EAFB0(v3, (uint32_t *)a2[2], v6);
    sub_434100(v8, *(this + 2));
    v9 = a2[1];
    if ( v9 != 0 )
      v10 = *(this + 1) + 32 * ((a2[2] - v9) >> 5);
    else
      v10 = *(this + 1);
    *(this + 2) = v10;
    return this;
  }
  if ( v6 != nullptr )
    v11 = (*(this + 3) - (int)v6) >> 5;
  else
    v11 = 0;
  if ( v4 > v11 )
  {
    if ( v6 != nullptr )
    {
      sub_434100(v6, *(this + 2));
      j__free((void *)*(this + 1));
    }
    v14 = a2[1];
    if ( v14 != 0 )
      v15 = (a2[2] - v14) >> 5;
    else
      v15 = 0;
    if ( (uint8_t)sub_434A40(v15) != 0 )
      *(this + 2) = (int)sub_4EBC70((uint32_t *)a2[1], (uint32_t *)a2[2], (uint32_t *)*(this + 1));
    return this;
  }
  if ( v6 != nullptr )
    v12 = (*(this + 2) - (int)v6) >> 5;
  else
    v12 = 0;
  v13 = (uint32_t *)(a2[1] + 32 * v12);
  sub_4EB130((uint32_t *)a2[1], v13, (uint32_t *)*(this + 1));
  *(this + 2) = (int)sub_4EB1C0(v13, (uint32_t *)a2[2], (uint32_t *)*(this + 2));
  return this;
}



// ------------------------------------------------------------
// 0x4ED6A0 sub_4ED6A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ED6A0(uint32_t *this, uint32_t *a2)
{
  *this = *a2;
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  *(this + 3) = a2[3];
  *(this + 4) = a2[4];
  *(this + 5) = a2[5];
  *(this + 6) = a2[6];
  *(this + 7) = a2[7];
  *(this + 8) = a2[8];
  sub_4ED330(this + 9, (int)(a2 + 9));
  sub_4ED330(this + 13, (int)(a2 + 13));
  return this;
}



// ------------------------------------------------------------
// 0x4ED730 sub_4ED730
// ------------------------------------------------------------
char */*cdecl*/ sub_4ED730(int a1, int a2, char *a3)
{
  char *v3; // esi
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
      sub_4EBCC0(v3, a1);
    v3 += 80;
    LOBYTE(v7) = 0;
    a1 += 80;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x4ED7C0 sub_4ED7C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4ED7C0(int *this, int a2, unsigned int a3, int a4, int a5, int a6)
{
  int v7; // eax
  int v8; // eax
  int v10; // edx
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // eax
  int v16; // edx
  int v17; // eax
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int v24; // eax
  int v25; // edx
  int v26; // eax
  int v27; // eax
  int v28; // edx
  int v29; // eax
  int v30; // eax
  int v31; // edx
  int v32; // eax
  int v33; // eax
  int v34; // edx
  int v35; // eax
  int v36; // eax
  int v37; // edx
  int v38; // eax
  int v39; // edx
  int v40; // eax
  int v41; // edx
  int v42; // eax
  int v43; // edx
  int v44; // eax
  int v45; // edx
  int v46; // eax
  int v47; // edx
  int v48; // eax
  int v49; // edx
  unsigned int v50; // ebx
  int v51; // eax
  int v52; // eax
  int v53; // edx
  int v54; // eax
  int v55; // eax
  int v56; // edx
  int v57; // ebx
  int v58; // eax
  int v59; // edx
  int v60; // ebx
  uint64_t v61; // rax
  unsigned int v62; // eax
  uint64_t v63; // rax
  int v64; // ebx
  unsigned int v65; // eax
  int v66; // eax
  int v67; // edx
  int v68; // eax
  int v69; // edx
  int v70; // eax
  int v71; // edx
  int v72; // eax
  int v73; // edx
  int v74; // eax
  int v75; // edx
  int v76; // eax
  int v77; // edx
  int v78; // eax
  int v79; // edx
  int v80; // eax
  int v81; // edx
  int v82; // eax
  int v83; // edx
  int v84; // eax
  int v85; // edx
  int v86; // eax
  int v87; // edx
  int v88; // eax
  int v89; // edx
  int v90; // eax
  int v91; // edx
  int v92; // eax
  int v93; // edx
  int v94; // eax
  int v95; // edx
  int v96; // eax
  int v97; // edx
  unsigned int v98; // ebx
  int v99; // eax
  int v100; // edx
  int v101; // edx
  int v102; // edi
  int v103; // ebx
  int v104; // edi
  int v105; // eax
  int v106; // edx
  int v107; // eax
  int v108; // eax
  int v109; // eax
  int v110; // eax
  unsigned int v111; // ecx
  int v112; // eax
  int v113; // eax
  int v114; // eax
  int v115; // eax
  int v116; // edi
  int v117; // eax
  int v118; // eax
  int v119; // eax
  int v120; // eax
  int v121; // eax
  int v122; // edx
  int v123; // eax
  int result; // eax
  int v125; // ebx
  int v126; // eax
  int v127; // edx
  int v128; // edx
  int v129; // ebx
  int v130; // eax
  int v131; // edx
  int v132; // edx
  int v133; // ebx
  int v134; // eax
  int v135; // edx
  int v136; // ebx
  int v137; // eax
  int v138; // edx
  int v139; // edx
  int v140; // edx
  int v141; // edx
  float v142; // [esp+0h] [ebp-74h]
  float v143; // [esp+0h] [ebp-74h]
  char v144; // [esp+8h] [ebp-6Ch]
  float v145; // [esp+Ch] [ebp-68h]
  float v146; // [esp+Ch] [ebp-68h]
  float v147; // [esp+Ch] [ebp-68h]
  float v148; // [esp+Ch] [ebp-68h]
  int v149; // [esp+1Ch] [ebp-58h] BYREF
  int v150; // [esp+20h] [ebp-54h]
  int v151; // [esp+24h] [ebp-50h]
  int v152; // [esp+34h] [ebp-40h]
  char v153; // [esp+38h] [ebp-3Ch]
  int v154; // [esp+3Ch] [ebp-38h]
  int v155; // [esp+40h] [ebp-34h]
  int v156; // [esp+44h] [ebp-30h]
  unsigned int v157; // [esp+48h] [ebp-2Ch]
  unsigned int v158; // [esp+4Ch] [ebp-28h]
  unsigned int v159; // [esp+50h] [ebp-24h]
  unsigned int v160; // [esp+54h] [ebp-20h]
  int *v161; // [esp+58h] [ebp-1Ch]
  unsigned int v162; // [esp+5Ch] [ebp-18h]
  unsigned int v163; // [esp+60h] [ebp-14h]
  int v164; // [esp+64h] [ebp-10h]
  int v165; // [esp+68h] [ebp-Ch]
  int v166; // [esp+6Ch] [ebp-8h]
  unsigned int v167; // [esp+70h] [ebp-4h]
  int i; // [esp+80h] [ebp+Ch]
  int v169; // [esp+80h] [ebp+Ch]
  int v170; // [esp+80h] [ebp+Ch]
  float v171; // [esp+80h] [ebp+Ch]
  int j; // [esp+80h] [ebp+Ch]
  unsigned int v173; // [esp+84h] [ebp+10h]
  int v174; // [esp+84h] [ebp+10h]

  v161 = this;
  v7 = sub_41A5E0(a4 + 14);
  v8 = sub_4E9CF0(v7, (unsigned int *)&a5, 10, 10);
  sub_41A590(a3 + 14, v10, v8);
  v11 = sub_41A5E0(a4 + 28);
  v12 = sub_4E9CF0(v11, (unsigned int *)&a5, 10, 10);
  sub_41A590(a3 + 28, v13, v12);
  v14 = sub_41A5E0(a4 + 42);
  v15 = sub_4E9CF0(v14, (unsigned int *)&a5, 20, 5);
  sub_41A590(a3 + 42, v16, v15);
  v17 = sub_41A5E0(a4 + 56);
  v18 = sub_4E9CF0(v17, (unsigned int *)&a5, 20, 5);
  sub_41A590(a3 + 56, v19, v18);
  v20 = sub_41A5E0(a4 + 70);
  v21 = sub_4E9CF0(v20, (unsigned int *)&a5, 20, 5);
  sub_41A590(a3 + 70, v22, v21);
  v23 = sub_41A5E0(a4 + 98);
  v24 = sub_4E9CF0(v23, (unsigned int *)&a5, 20, 5);
  sub_41A590(a3 + 98, v25, v24);
  v173 = a4 + 112;
  v26 = sub_41A5E0(v173);
  v27 = sub_4E9CF0(v26, (unsigned int *)&a5, 5, 8);
  sub_41A590(a3 + 112, v28, v27);
  v163 = a4 + 126;
  v29 = sub_41A5E0(a4 + 126);
  v30 = sub_4E9CF0(v29, (unsigned int *)&a5, 5, 8);
  sub_41A590(a3 + 126, v31, v30);
  v167 = a4 + 140;
  v32 = sub_41A5E0(a4 + 140);
  v33 = sub_4E9CF0(v32, (unsigned int *)&a5, 5, 8);
  sub_41A590(a3 + 140, v34, v33);
  v162 = a4 + 154;
  v35 = sub_41A5E0(a4 + 154);
  v36 = sub_4E9CF0(v35, (unsigned int *)&a5, 5, 8);
  sub_41A590(a3 + 154, v37, v36);
  v38 = sub_41A5E0(a4 + 224);
  v160 = a3 + 224;
  sub_41A590(a3 + 224, v39, v38);
  v40 = sub_41A5E0(a4 + 238);
  sub_41A590(a3 + 238, v41, v40);
  v42 = sub_41A5E0(a4 + 252);
  v158 = a3 + 252;
  sub_41A590(a3 + 252, v43, v42);
  v44 = sub_41A5E0(a4 + 266);
  v159 = a3 + 266;
  sub_41A590(a3 + 266, v45, v44);
  v46 = sub_41A5E0(a4 + 280);
  sub_41A590(a3 + 280, v47, v46);
  v48 = sub_41A5E0(a4 + 294);
  v157 = a3 + 294;
  sub_41A590(a3 + 294, v49, v48);
  v50 = a3 + 308;
  v164 = a4 - a3;
  for ( i = 4; i != 0; --i )
  {
    v51 = sub_41A5E0(v164 + v50);
    v52 = sub_4E9CF0(v51, (unsigned int *)&a5, 20, 5);
    sub_41A590(v50, v53, v52);
    v50 += 14;
  }
  v54 = sub_41A5E0(a4 + 364);
  v55 = sub_4E9CF0(v54, (unsigned int *)&a5, 20, 5);
  sub_41A590(a3 + 364, v56, v55);
  v57 = 0;
  v169 = 0;
  do
  {
    if ( v57 == 13 )
    {
      v58 = sub_41A5E0(a4 + 560);
      sub_41A590(a3 + 560, v59, v58);
    }
    else
    {
      v60 = 14 * (v169 + 27);
      LODWORD(v61) = sub_41A5E0(v60 + a4);
      v165 = v61;
      if ( (uint32_t)v61 != 0 )
      {
        v145 = (double)v165 * 0.2;
        v166 = sub_432F40(v145);
        if ( v166 >= 5 )
          v166 = 5;
        *(float *)&v166 = (float)v166;
        v62 = sub_4D33A0((unsigned int *)&a5);
        v142 = -*(float *)&v166;
        v146 = sub_4049C0(v142, *(float *)&v166, v62 % 0x3E8, 999);
        v61 = sub_432F40(v146);
        LODWORD(v61) = v165 + v61;
      }
      sub_41A590(v60 + a3, SHIDWORD(v61), v61);
      v57 = v169;
    }
    v169 = ++v57;
  }
  while ( v57 < 16 );
  LODWORD(v63) = sub_41A5E0(a4 + 602);
  v64 = v63;
  if ( (uint32_t)v63 != 0 )
  {
    v147 = (double)(int)v63 * 0.2;
    v170 = sub_432F40(v147);
    if ( v170 >= 5 )
      v170 = 5;
    v171 = (float)v170;
    v65 = sub_4D33A0((unsigned int *)&a5);
    v143 = -v171;
    v148 = sub_4049C0(v143, v171, v65 % 0x3E8, 999);
    v63 = sub_432F40(v148);
    LODWORD(v63) = v64 + v63;
  }
  sub_41A590(a3 + 602, SHIDWORD(v63), v63);
  v66 = sub_41A5E0(a4 + 616);
  sub_41A590(a3 + 616, v67, v66);
  v68 = sub_41A5E0(a4 + 630);
  sub_41A590(a3 + 630, v69, v68);
  v70 = sub_41A5E0(a4 + 644);
  sub_41A590(a3 + 644, v71, v70);
  v72 = sub_41A5E0(a4 + 658);
  sub_41A590(a3 + 658, v73, v72);
  v74 = sub_41A5E0(a4 + 672);
  sub_41A590(a3 + 672, v75, v74);
  v76 = sub_41A5E0(a4 + 686);
  sub_41A590(a3 + 686, v77, v76);
  v78 = sub_41A5E0(a4 + 700);
  sub_41A590(a3 + 700, v79, v78);
  v80 = sub_41A5E0(a4 + 714);
  sub_41A590(a3 + 714, v81, v80);
  v82 = sub_41A5E0(a4 + 728);
  sub_41A590(a3 + 728, v83, v82);
  *(uint32_t *)(a3 + 772) = *(uint32_t *)(a4 + 772);
  *(uint32_t *)(a3 + 776) = *(uint32_t *)(a4 + 776);
  v84 = sub_41A5E0(a4 + 780);
  sub_41A590(a3 + 780, v85, v84);
  v86 = sub_41A5E0(a4 + 794);
  sub_41A590(a3 + 794, v87, v86);
  v88 = sub_41A5E0(a4 + 808);
  sub_41A590(a3 + 808, v89, v88);
  v90 = sub_41A5E0(a4 + 822);
  sub_41A590(a3 + 822, v91, v90);
  v92 = sub_41A5E0(a4 + 742);
  sub_41A590(a3 + 742, v93, v92);
  v94 = sub_41A5E0(a4 + 756);
  sub_41A590(a3 + 756, v95, v94);
  v96 = sub_41A5E0(a4 + 836);
  sub_41A590(a3 + 836, v97, v96);
  *(uint8_t *)(a3 + 850) = *(uint8_t *)(a4 + 850);
  v98 = a3 + 851;
  for ( j = 2; j != 0; --j )
  {
    v99 = sub_41A5E0(v98 + v164);
    sub_41A590(v98, v100, v99);
    v98 += 14;
  }
  *(uint8_t *)(a3 + 879) = *(uint8_t *)(a4 + 879);
  *(uint8_t *)(a3 + 880) = *(uint8_t *)(a4 + 880);
  sub_4ED540((int *)(a3 + 884), (int *)(a4 + 884));
  switch ( a2 )
  {
    case 8:
      if ( sub_41A5E0(v173) != 0 && sub_41A5E0(v167) != 0 )
      {
        v102 = sub_41A5E0(a3 + 112);
        v103 = sub_41A5E0(a3 + 140);
        v174 = sub_41A5E0(v173);
        v104 = v103 + v102;
        v105 = v174 + sub_41A5E0(v167);
        if ( v104 <= 5 || v105 < 16 )
          goto LABEL_42;
        v107 = v105 - 14;
        if ( v104 >= v107 )
          goto LABEL_25;
        v108 = 0;
        goto LABEL_58;
      }
      if ( sub_41A5E0(v173) != 0 )
      {
        v110 = sub_41A5E0(a3 + 112);
        v111 = v173;
        goto LABEL_41;
      }
      if ( sub_41A5E0(v167) != 0 )
      {
        v104 = sub_41A5E0(a3 + 140);
        v112 = sub_41A5E0(v167);
        if ( v104 <= 5 )
        {
          v108 = 2;
          goto LABEL_58;
        }
        if ( v112 < 8 )
        {
          v108 = 2;
          goto LABEL_58;
        }
        v113 = v112 - 6;
        if ( v104 < v113 )
        {
          v108 = 0;
          goto LABEL_58;
        }
        v114 = v113 + 4;
        if ( v104 < v114 )
        {
          v108 = 1;
          goto LABEL_58;
        }
        v115 = v114 + 5;
        if ( v104 < v115 )
        {
          v108 = 2;
          goto LABEL_58;
        }
        goto LABEL_57;
      }
      goto LABEL_59;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
      v110 = sub_41A5E0(a3 + 126);
      v111 = v163;
LABEL_41:
      v116 = v110;
      v117 = sub_41A5E0(v111);
      if ( v116 <= 5 )
        goto LABEL_42;
      if ( v117 >= 8 )
      {
        v118 = v117 - 6;
        if ( v116 >= v118 )
        {
          v119 = v118 + 4;
          if ( v116 >= v119 )
          {
            v120 = v119 + 5;
            if ( v116 >= v120 )
              v108 = (v116 >= v120 + 4) + 3;
            else
              v108 = 2;
          }
          else
          {
            v108 = 1;
          }
        }
        else
        {
          v108 = 0;
        }
      }
      else
      {
        v108 = 2;
      }
      goto LABEL_58;
    case 15:
    case 16:
    case 17:
      v104 = sub_41A5E0(a3 + 154);
      v121 = sub_41A5E0(v162);
      if ( v104 <= 5 || v121 < 8 )
        goto LABEL_42;
      v107 = v121 - 6;
      if ( v104 >= v107 )
      {
LABEL_25:
        v109 = v107 + 4;
        if ( v104 >= v109 )
        {
          v115 = v109 + 5;
          if ( v104 < v115 )
          {
LABEL_42:
            v108 = 2;
          }
          else
          {
LABEL_57:
            v106 = (v104 >= v115 + 4) + 3;
            v108 = v106;
          }
        }
        else
        {
          v108 = 1;
        }
      }
      else
      {
        v108 = 0;
      }
LABEL_58:
      sub_41A590(a3, v106, v108);
LABEL_59:
      if ( (uint8_t)a6 != 0 )
      {
        v122 = *v161;
        v149 = 0;
        v150 = 0;
        v151 = 0;
        v144 = a6 - 1;
        v152 = 0;
        v153 = 0;
        v154 = 0;
        v155 = 0;
        v156 = 0;
        v123 = (*(int (/*thiscall*/ **)(int *))(v122 + 16))(v161);
        result = sub_4F9F40(&v149, 0, *(uint8_t *)(v123 + 24), v144, a2);
        if ( (uint8_t)result != 0 )
        {
          result = a2 - 8;
          switch ( a2 )
          {
            case 8:
              if ( sub_41A5E0(a3 + 112) != 0 )
              {
                v125 = v149;
                v126 = sub_41A5E0(a3 + 112);
                sub_41A590(a3 + 112, v127, v125 + v126);
                sub_41A590(a3 + 168, v128, v149);
              }
              result = sub_41A5E0(a3 + 140);
              if ( result != 0 )
              {
                v129 = v149;
                v130 = sub_41A5E0(a3 + 140);
                sub_41A590(a3 + 140, v131, v129 + v130);
                result = sub_41A590(a3 + 196, v132, v149);
              }
              break;
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
              v133 = v150;
              v134 = sub_41A5E0(a3 + 126);
              sub_41A590(a3 + 126, v135, v133 + v134);
              result = sub_41A590(a3 + 182, v150, v150);
              break;
            case 15:
            case 16:
            case 17:
              v136 = v150;
              v137 = sub_41A5E0(a3 + 154);
              sub_41A590(a3 + 154, v138, v136 + v137);
              result = sub_41A590(a3 + 210, v139, v150);
              break;
            default:
              return result;
          }
        }
      }
      else
      {
        sub_41A590(v160, v101, 0);
        sub_41A590(v159, v140, 0);
        a6 = 0;
        sub_41A590(v158, v141, 0);
        a6 = 0;
        return sub_41A590(v157, 0, 0);
      }
      return result;
    default:
      goto LABEL_59;
  }
}


// ------------------------------------------------------------
// 0x4EE120 sub_4EE120
// ------------------------------------------------------------
void /*thiscall*/ sub_4EE120(int this, uint32_t *a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  uint32_t *v5; // edi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 5;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) >> 5 )
  {
    v5 = *(uint32_t **)(this + 8);
    sub_4EB800(v5, 1, a2);
    *(uint32_t *)(this + 8) = v5 + 8;
  }
  else
  {
    sub_4ED080(this, *(char **)(this + 8), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x4EE190 sub_4EE190
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EE190(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // eax
  uint32_t *v4; // esi
  uint32_t *v5; // ebx
  bool v6; // zf
  uint32_t *i; // [esp+0h] [ebp-4h]

  v3 = a1;
  if ( a1 != a2 )
  {
    v4 = a1 + 3;
    v5 = a3 + 3;
    for ( i = a1 + 3; ; v4 = i )
    {
      *a3 = *v3;
      *(v5 - 2) = *(v4 - 2);
      *(v5 - 1) = *(v4 - 1);
      *v5 = *v4;
      v5[1] = v4[1];
      v5[2] = v4[2];
      v5[3] = v4[3];
      v5[4] = v4[4];
      v5[5] = v4[5];
      v5[6] = v4[6];
      sub_4ED3F0((int)(v5 + 7), (int)(v4 + 7));
      sub_4ED3F0((int)(v5 + 11), (int)(v4 + 11));
      qmemcpy(v5 + 15, v4 + 15, 0x34u);
      a3 += 31;
      v5 += 31;
      v6 = a1 + 31 == a2;
      a1 += 31;
      i += 31;
      if ( v6 )
        break;
      v3 = a1;
    }
  }
  return a3;
}



// ------------------------------------------------------------
// 0x4EE250 sub_4EE250
// ------------------------------------------------------------
int /*cdecl*/ sub_4EE250(int a1, int a2, int a3)
{
  int v3; // eax
  uint32_t *v4; // edi
  uint32_t *v5; // ebx
  int v7; // [esp+10h] [ebp+Ch]

  v3 = a2;
  if ( a1 != a2 )
  {
    v4 = (uint32_t *)(a3 + 12);
    v5 = (uint32_t *)(a2 + 12);
    while ( 1 )
    {
      v5 -= 31;
      v4 -= 31;
      v7 = v3 - 124;
      *(uint32_t *)(a3 - 124) = *(uint32_t *)(v3 - 124);
      a3 -= 124;
      *(v4 - 2) = *(v5 - 2);
      *(v4 - 1) = *(v5 - 1);
      *v4 = *v5;
      v4[1] = v5[1];
      v4[2] = v5[2];
      v4[3] = v5[3];
      v4[4] = v5[4];
      v4[5] = v5[5];
      v4[6] = v5[6];
      sub_4ED3F0((int)(v4 + 7), (int)(v5 + 7));
      sub_4ED3F0((int)(v4 + 11), (int)(v5 + 11));
      qmemcpy(v4 + 15, v5 + 15, 0x34u);
      if ( v7 == a1 )
        break;
      v3 = v7;
    }
  }
  return a3;
}



// ------------------------------------------------------------
// 0x4EE300 sub_4EE300
// ------------------------------------------------------------
void /*thiscall*/ sub_4EE300(uint32_t *this)
{
  unsigned int v2; // esi
  unsigned int v3; // ebx
  int v4; // eax
  int v5; // esi
  int v6; // edx
  float v7; // [esp+0h] [ebp-14h]
  float v8; // [esp+0h] [ebp-14h]
  float v9; // [esp+10h] [ebp-4h]

  v2 = (unsigned int)(this + 233);
  if ( sub_41A5E0((unsigned int)(this + 233)) != -1 )
  {
    v3 = sub_41A5E0(v2);
    v4 = *(this + 230);
    if ( v4 != 0 && v3 < (*(this + 231) - v4) / 80 )
    {
      v5 = *(this + 230) + 80 * sub_41A5E0(v2);
      v9 = COERCE_FLOAT(sub_41A5E0(v5 + 5));
      switch ( *(uint32_t *)v5 )
      {
        case 0xF:
          if ( *(uint8_t *)(v5 + 4) != 0 )
            goto LABEL_15;
          goto LABEL_6;
        case 0x20:
          if ( *(uint8_t *)(v5 + 4) != 0 )
            goto LABEL_15;
LABEL_6:
          sub_4450B0((uint64_t)v9);
          break;
        case 0x24:
          if ( *(uint8_t *)(v5 + 4) != 0 )
            goto LABEL_15;
          v7 = (float)(int)(uint64_t)v9;
          sub_4AED60((char *)this + 658, v7);
          break;
        case 0x2A:
          if ( *(uint8_t *)(v5 + 4) != 0 )
            goto LABEL_15;
          v8 = (float)(int)(uint64_t)v9;
          sub_4AED60((char *)this + 742, v8);
          break;
        case 0x2B:
          if ( *(uint8_t *)(v5 + 4) != 0 )
LABEL_15:
            sub_4EBD50(v5, v6);
          else
            sub_4EE120((int)(this + 225), (uint32_t *)(v5 + 20));
          break;
        default:
          return;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x4EE4A0 sub_4EE4A0
// ------------------------------------------------------------
char */*stdcall*/ sub_4EE4A0(int a1, int a2, char *a3)
{
  return sub_4ED730(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4EE4C0 sub_4EE4C0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EE4C0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *v4; // ebx

  result = a1;
  if ( a1 != a2 )
  {
    v4 = a1 + 3;
    do
    {
      *result = *a3;
      *(v4 - 2) = a3[1];
      *(v4 - 1) = a3[2];
      *v4 = a3[3];
      v4[1] = a3[4];
      v4[2] = a3[5];
      v4[3] = a3[6];
      v4[4] = a3[7];
      v4[5] = a3[8];
      v4[6] = a3[9];
      sub_4ED3F0((int)(v4 + 7), (int)(a3 + 10));
      sub_4ED3F0((int)(v4 + 11), (int)(a3 + 14));
      qmemcpy(v4 + 15, a3 + 18, 0x34u);
      result = a1 + 31;
      v4 += 31;
      a1 = result;
    }
    while ( result != a2 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EE560 sub_4EE560
// ------------------------------------------------------------
int /*cdecl*/ sub_4EE560(int a1, int a2, int a3)
{
  return sub_4EE250(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4EE580 sub_4EE580
// ------------------------------------------------------------
int /*thiscall*/ sub_4EE580(uint32_t *this, const char *Block, int a3, int a4, int a5)
{
  uint32_t *v6; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  unsigned int v13; // edi
  int v14; // ecx
  int v15; // edx
  int v16; // eax
  unsigned int v17; // edx
  uint32_t *v18; // edi
  int v19; // eax
  int v20; // edx
  int v21; // edx
  int v22; // edx
  int v23; // edx
  int v24; // eax
  int v25; // ecx
  int v26; // eax
  uint32_t *v27; // eax
  uint32_t *v28; // eax
  uint32_t *v29; // eax
  int v30; // edx
  int v31; // [esp-8h] [ebp-5Ch]
  int v32; // [esp-8h] [ebp-5Ch]
  int v33; // [esp-4h] [ebp-58h]
  int v34; // [esp+8h] [ebp-4Ch] BYREF
  uint8_t v35[14]; // [esp+Ch] [ebp-48h] BYREF
  uint8_t v36[14]; // [esp+1Ah] [ebp-3Ah] BYREF
  uint8_t v37[14]; // [esp+28h] [ebp-2Ch] BYREF
  uint8_t v38[14]; // [esp+36h] [ebp-1Eh] BYREF
  int v39; // [esp+44h] [ebp-10h]
  int v40; // [esp+50h] [ebp-4h]
  void *Blocka; // [esp+5Ch] [ebp+8h]
  int v42; // [esp+64h] [ebp+10h]

  if ( dword_9B06DC == 0 || (v39 = (dword_9B06E0 - dword_9B06DC) / 44) == 0 )
    sub_4FAC40("etc/upgrade.etc", &unk_9B06D8);
  v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84D0 + 4))(dword_8F84D0, Block);
  *(this + 333) = v6;
  if ( v6 == nullptr )
    return off_77F3FC("EQUIPMENT CREATE FAIL! FILENAME[%s]", Block);
  if ( a4 == -1 || a5 == -1 )
  {
    *(this + 331) = v6[273];
    *(this + 332) = v6[274];
  }
  else
  {
    *(this + 331) = a4;
    *(this + 332) = a5;
  }
  *(this + 3) = *v6;
  sub_41B0D0(v6 + 530);
  sub_41B0D0(*(this + 333) + 2124);
  sub_41B0D0(*(this + 333) + 2128);
  sub_41B0D0(*(this + 333) + 2136);
  v8 = *(this + 333);
  *(this + 8) = *(uint32_t *)(v8 + 4);
  *(this + 9) = *(uint32_t *)(v8 + 8);
  *(this + 11) = *(uint32_t *)(v8 + 20);
  *(this + 15) = *(uint32_t *)(v8 + 32);
  *(this + 12) = *(uint32_t *)(v8 + 24);
  *(this + 13) = *(uint32_t *)(v8 + 28);
  *(this + 14) = *(uint32_t *)(v8 + 36);
  *(this + 16) = *(uint32_t *)(v8 + 40);
  *((uint8_t *)this + 68) = *(uint8_t *)(v8 + 44);
  *((uint8_t *)this + 69) = *(uint8_t *)(*(this + 333) + 45);
  *((uint8_t *)this + 70) = *(uint8_t *)(*(this + 333) + 46);
  *((uint8_t *)this + 71) = *(uint8_t *)(*(this + 333) + 47);
  v9 = *(this + 333);
  *(this + 2) = *(uint32_t *)(v9 + 48);
  *(this + 18) = *(uint32_t *)(v9 + 56);
  if ( strcmp((const char *)sub_41ACF0(v9 + 60), szPassword) != 0 )
  {
    v10 = sub_41ACF0(*(this + 333) + 60);
    v31 = *(uint32_t *)(*(this + 333) + 64);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v10);
    *(this + 19) = sub_418DD0(v31);
  }
  if ( strcmp((const char *)sub_41ACF0(*(this + 333) + 68), szPassword) != 0 )
  {
    v11 = sub_41ACF0(*(this + 333) + 68);
    v32 = *(uint32_t *)(*(this + 333) + 72);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v11);
    *(this + 20) = sub_418DD0(v32);
  }
  sub_41B0D0(*(this + 333) + 1068);
  v12 = *(this + 333);
  *(this + 23) = *(uint32_t *)(v12 + 16);
  sub_4ED3F0((int)(this + 24), v12 + 2076);
  v13 = 0;
  while ( 1 )
  {
    v14 = *(this + 333);
    v15 = *(uint32_t *)(v14 + 2096);
    v42 = v13;
    if ( v15 == 0 || v13 >= (*(uint32_t *)(v14 + 2100) - v15) >> 2 )
      break;
    Blocka = (void *)(v15 + 4 * v13);
    v16 = *(this + 29);
    if ( v16 != 0 )
      v17 = (*(this + 30) - v16) >> 2;
    else
      v17 = 0;
    if ( v16 != 0 && v17 < (*(this + 31) - v16) >> 2 )
    {
      v18 = (uint32_t *)*(this + 30);
      sub_41FFE0(v18, 1, (int)Blocka);
      *(this + 30) = v18 + 1;
      v13 = v42 + 1;
    }
    else
    {
      sub_4206D0(this + 28, *(this + 30), 1u, (int)Blocka);
      ++v13;
    }
  }
  v19 = *(this + 333);
  v20 = *(uint32_t *)(v19 + 92);
  *(this + 37) = v20;
  sub_41A590((unsigned int)(this + 38), v20, *(uint32_t *)(v19 + 96));
  sub_41A590((unsigned int)this + 166, v21, *(uint32_t *)(*(this + 333) + 100));
  sub_41A590((unsigned int)(this + 45), v22, *(uint32_t *)(*(this + 333) + 52));
  sub_41DC80(*(this + 333) + 1072);
  v24 = *(this + 333);
  v25 = *(uint32_t *)(v24 + 1112);
  v26 = v24 + 1108;
  if ( v25 != 0 )
  {
    v23 = (*(uint32_t *)(v26 + 8) - v25) >> 2;
    if ( v23 != 0 )
    {
      sub_4ED3F0((int)(this + 313), v26);
      v27 = operator new(0x3B4u);
      v40 = 0;
      if ( v27 != nullptr )
        v28 = sub_437E70(v27);
      else
        v28 = nullptr;
      *(this + 317) = v28;
      v33 = *(this + 333) + 2132;
      v40 = -1;
      sub_41B0D0(v33);
    }
  }
  *(this + 320) = *(uint32_t *)(*(this + 333) + 2072);
  sub_41A590((unsigned int)(this + 33), v23, 1);
  if ( a3 != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 184))(this, a3);
  v29 = sub_4E9A50(&v34);
  v30 = *this;
  v40 = 1;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(v30 + 184))(this, v29);
  v40 = 4;
  sub_41A580(v38);
  LOBYTE(v40) = 3;
  sub_41A580(v37);
  LOBYTE(v40) = 2;
  sub_41A580(v36);
  v40 = -1;
  return sub_41A580(v35);
}


// ------------------------------------------------------------
// 0x4EE9E0 sub_4EE9E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4EE9E0(int this, int *a2)
{
  int v3; // eax
  unsigned int v4; // ecx
  uint32_t *v6; // ebx
  unsigned int v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int v10; // edx
  unsigned int v11; // eax
  uint32_t *v12; // edi
  int v13; // eax

  if ( (int *)this == a2 )
    return this;
  v3 = a2[1];
  if ( v3 == 0 || (v4 = (a2[2] - v3) / 80) == 0 )
  {
    sub_436840(this);
    return this;
  }
  v6 = *(uint32_t **)(this + 4);
  if ( v6 != nullptr )
    v7 = (*(uint32_t *)(this + 8) - (int)v6) / 80;
  else
    v7 = 0;
  if ( v4 > v7 )
  {
    if ( v6 != nullptr )
      v11 = (*(uint32_t *)(this + 12) - (int)v6) / 80;
    else
      v11 = 0;
    if ( v4 <= v11 )
    {
      v12 = (uint32_t *)(a2[1] + 80 * sub_4EAF60((int *)this));
      sub_4ED3D0((uint32_t *)a2[1], v12, v6);
      *(uint32_t *)(this + 8) = sub_4ED730((int)v12, a2[2], *(char **)(this + 8));
      return this;
    }
    if ( v6 != nullptr )
    {
      sub_435890(v6, *(uint32_t *)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v13 = sub_4EAF60(a2);
    if ( (uint8_t)sub_434A90(v13) != 0 )
      *(uint32_t *)(this + 8) = sub_4EE4A0(a2[1], a2[2], *(char **)(this + 4));
    return this;
  }
  v8 = sub_4ECFE0((uint32_t *)a2[1], (uint32_t *)a2[2], v6);
  sub_435890(v8, *(uint32_t *)(this + 8));
  v9 = a2[1];
  if ( v9 != 0 )
    v10 = *(uint32_t *)(this + 4) + 80 * ((a2[2] - v9) / 80);
  else
    v10 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 8) = v10;
  return this;
}



// ------------------------------------------------------------
// 0x4EEB70 sub_4EEB70
// ------------------------------------------------------------
void /*thiscall*/ sub_4EEB70(int *this, int ArgList, int a3)
{
  int v3; // ebx
  const char *v5; // eax
  int v6; // [esp+Ch] [ebp-4h] BYREF

  v3 = ArgList;
  sub_442D00(&v6, &ArgList);
  if ( v6 == dword_9B6C70
    || (*(uint32_t *)(v6 + 40) < 0x10u ? (v5 = (const char *)(v6 + 20)) : (v5 = *(const char **)(v6 + 20)), v5 == nullptr) )
  {
    off_77F3FC("EQUIPMENT CREATE FAIL! INDEX %d", v3);
  }
  else
  {
    sub_4EE580(this, v5, a3, -1, -1);
  }
  *(this + 335) = 0;
  *(this + 334) = 0;
}



// ------------------------------------------------------------
// 0x4EEBF0 sub_4EEBF0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4EEBF0(unsigned int this, unsigned int a2)
{
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // edx
  int v26; // eax
  int v27; // edx
  int v28; // eax
  int v29; // edx
  int v30; // eax
  int v31; // edx
  int v32; // eax
  int v33; // edx
  int v34; // eax
  int v35; // edx
  int v36; // eax
  int v37; // edx
  int v38; // eax
  int v39; // edx
  int v40; // eax
  int v41; // edx
  int v42; // eax
  int v43; // edx
  int v44; // eax
  int v45; // edx
  int v46; // eax
  int v47; // edx
  unsigned int v48; // ebx
  int v49; // eax
  int v50; // edx
  bool v51; // zf
  int v52; // eax
  int v53; // edx
  int v54; // eax
  int v55; // edx
  int v56; // eax
  int v57; // edx
  int v58; // eax
  int v59; // edx
  int v60; // eax
  int v61; // edx
  int v62; // eax
  int v63; // edx
  int v64; // eax
  int v65; // edx
  int v66; // eax
  int v67; // edx
  int v68; // eax
  int v69; // edx
  int v70; // eax
  int v71; // edx
  int v72; // eax
  int v73; // edx
  int v74; // eax
  int v75; // edx
  int v76; // eax
  int v77; // edx
  int v78; // eax
  int v79; // edx
  int v80; // eax
  int v81; // edx
  int v82; // eax
  int v83; // edx
  int v84; // eax
  int v85; // edx
  int v86; // eax
  int v87; // edx
  int v88; // eax
  int v89; // edx
  int v90; // eax
  int v91; // edx
  unsigned int v92; // ecx
  int v93; // eax
  int v94; // edx
  int v96; // [esp+Ch] [ebp-4h]
  int v97; // [esp+Ch] [ebp-4h]
  int v98; // [esp+Ch] [ebp-4h]
  int v99; // [esp+Ch] [ebp-4h]
  unsigned int v100; // [esp+18h] [ebp+8h]
  unsigned int v101; // [esp+18h] [ebp+8h]
  unsigned int v102; // [esp+18h] [ebp+8h]
  unsigned int v103; // [esp+18h] [ebp+8h]

  v4 = sub_41A5E0(a2);
  sub_41A590(this, v5, v4);
  v6 = sub_41A5E0(a2 + 14);
  sub_41A590(this + 14, v7, v6);
  v8 = sub_41A5E0(a2 + 28);
  sub_41A590(this + 28, v9, v8);
  v10 = sub_41A5E0(a2 + 42);
  sub_41A590(this + 42, v11, v10);
  v12 = sub_41A5E0(a2 + 56);
  sub_41A590(this + 56, v13, v12);
  v14 = sub_41A5E0(a2 + 70);
  sub_41A590(this + 70, v15, v14);
  v16 = sub_41A5E0(a2 + 84);
  sub_41A590(this + 84, v17, v16);
  v18 = sub_41A5E0(a2 + 98);
  sub_41A590(this + 98, v19, v18);
  v20 = sub_41A5E0(a2 + 112);
  sub_41A590(this + 112, v21, v20);
  v22 = sub_41A5E0(a2 + 126);
  sub_41A590(this + 126, v23, v22);
  v24 = sub_41A5E0(a2 + 140);
  sub_41A590(this + 140, v25, v24);
  v26 = sub_41A5E0(a2 + 154);
  sub_41A590(this + 154, v27, v26);
  v28 = sub_41A5E0(a2 + 168);
  sub_41A590(this + 168, v29, v28);
  v30 = sub_41A5E0(a2 + 182);
  sub_41A590(this + 182, v31, v30);
  v32 = sub_41A5E0(a2 + 196);
  sub_41A590(this + 196, v33, v32);
  v34 = sub_41A5E0(a2 + 210);
  sub_41A590(this + 210, v35, v34);
  v36 = sub_41A5E0(a2 + 224);
  sub_41A590(this + 224, v37, v36);
  v38 = sub_41A5E0(a2 + 238);
  sub_41A590(this + 238, v39, v38);
  v40 = sub_41A5E0(a2 + 252);
  sub_41A590(this + 252, v41, v40);
  v42 = sub_41A5E0(a2 + 266);
  sub_41A590(this + 266, v43, v42);
  v44 = sub_41A5E0(a2 + 280);
  sub_41A590(this + 280, v45, v44);
  v46 = sub_41A5E0(a2 + 294);
  sub_41A590(this + 294, v47, v46);
  v100 = this + 308;
  v48 = a2 - this;
  v96 = 4;
  do
  {
    v49 = sub_41A5E0(v48 + v100);
    sub_41A590(v100, v50, v49);
    v51 = v96 == 1;
    v100 += 14;
    --v96;
  }
  while ( !v51 );
  v52 = sub_41A5E0(a2 + 364);
  sub_41A590(this + 364, v53, v52);
  v101 = this + 378;
  v97 = 16;
  do
  {
    v54 = sub_41A5E0(v101 + v48);
    sub_41A590(v101, v55, v54);
    v51 = v97 == 1;
    v101 += 14;
    --v97;
  }
  while ( !v51 );
  v56 = sub_41A5E0(a2 + 602);
  sub_41A590(this + 602, v57, v56);
  v58 = sub_41A5E0(a2 + 616);
  sub_41A590(this + 616, v59, v58);
  v60 = sub_41A5E0(a2 + 630);
  sub_41A590(this + 630, v61, v60);
  v62 = sub_41A5E0(a2 + 644);
  sub_41A590(this + 644, v63, v62);
  v64 = sub_41A5E0(a2 + 658);
  sub_41A590(this + 658, v65, v64);
  v66 = sub_41A5E0(a2 + 672);
  sub_41A590(this + 672, v67, v66);
  v68 = sub_41A5E0(a2 + 686);
  sub_41A590(this + 686, v69, v68);
  v70 = sub_41A5E0(a2 + 700);
  sub_41A590(this + 700, v71, v70);
  v72 = sub_41A5E0(a2 + 714);
  sub_41A590(this + 714, v73, v72);
  v74 = sub_41A5E0(a2 + 728);
  sub_41A590(this + 728, v75, v74);
  v76 = sub_41A5E0(a2 + 742);
  sub_41A590(this + 742, v77, v76);
  v78 = sub_41A5E0(a2 + 756);
  sub_41A590(this + 756, v79, v78);
  *(uint32_t *)(this + 772) = *(uint32_t *)(a2 + 772);
  *(uint32_t *)(this + 776) = *(uint32_t *)(a2 + 776);
  v80 = sub_41A5E0(a2 + 780);
  sub_41A590(this + 780, v81, v80);
  v82 = sub_41A5E0(a2 + 794);
  sub_41A590(this + 794, v83, v82);
  v84 = sub_41A5E0(a2 + 808);
  sub_41A590(this + 808, v85, v84);
  v86 = sub_41A5E0(a2 + 822);
  sub_41A590(this + 822, v87, v86);
  v88 = sub_41A5E0(a2 + 836);
  sub_41A590(this + 836, v89, v88);
  *(uint8_t *)(this + 850) = *(uint8_t *)(a2 + 850);
  v102 = this + 851;
  v98 = 2;
  do
  {
    v90 = sub_41A5E0(v102 + v48);
    sub_41A590(v102, v91, v90);
    v51 = v98 == 1;
    v102 += 14;
    --v98;
  }
  while ( !v51 );
  *(uint8_t *)(this + 879) = *(uint8_t *)(a2 + 879);
  *(uint8_t *)(this + 880) = *(uint8_t *)(a2 + 880);
  v92 = this + 884;
  v103 = this + 884;
  v99 = 2;
  while ( 1 )
  {
    sub_4ED540(v92 + v48);
    v51 = v99 == 1;
    v103 += 16;
    --v99;
    if ( v51 )
      break;
    v92 = v103;
  }
  sub_4EE9E0(a2 + 916);
  v93 = sub_41A5E0(a2 + 932);
  sub_41A590(this + 932, v94, v93);
  return this;
}


// ------------------------------------------------------------
// 0x4EF0B0 sub_4EF0B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4EF0B0(int *this, int *a2)
{
  int result; // eax
  int v4; // ebx
  int v5; // ebx
  unsigned int v6; // ecx
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  int *v10; // eax
  unsigned int v11; // eax
  int v12; // eax
  int v13; // edx
  uint32_t v14[4]; // [esp+4h] [ebp-1Ch] BYREF
  int v15; // [esp+1Ch] [ebp-4h]

  result = *(this + 333);
  if ( result != 0 )
  {
    if ( *((uint8_t *)this + 1248) == 0
      || *(this + 290) != *a2
      || (v4 = sub_41A5E0((unsigned int)(this + 291))) != sub_41A5E0((unsigned int)(a2 + 1))
      || (v5 = sub_41A5E0((unsigned int)this + 1178)) != sub_41A5E0((unsigned int)a2 + 18) )
    {
      if ( *(this + 37) > 7 )
      {
        v9 = sub_41A5E0((unsigned int)(a2 + 1));
        v10 = (int *)(*(int (/*thiscall*/ **)(int *))(*this + 172))(this);
        sub_4ED7C0(this, *v10, (unsigned int)(this + 53), *(this + 333) + 104, *a2, v9);
        v11 = *(this + 317);
        if ( v11 != 0 )
          sub_4ED7C0(this, 18, v11, *(this + 333) + 1124, *a2, 0);
      }
      else
      {
        *((uint8_t *)this + 1233) = 0;
        *((uint8_t *)this + 1234) = 0;
        sub_698F90((int)(this + 305), 0, 0);
        sub_4EEBF0((unsigned int)(this + 53), *(this + 333) + 104);
        v6 = *(this + 317);
        if ( v6 != 0 )
          sub_4EEBF0(v6, *(this + 333) + 1124);
        sub_46B080(a2 + 8);
        v15 = 0;
        v7 = sub_41A5E0((unsigned int)v14);
        sub_41A590((unsigned int)(this + 286), v8, v7);
        sub_4EE300(this + 53);
        v15 = -1;
        sub_41A580(v14);
      }
      *((uint8_t *)this + 1248) = 1;
    }
    sub_4E9FA0(this + 290, a2);
    result = sub_41A5E0((unsigned int)(this + 298));
    if ( result == -1 )
    {
      v12 = sub_41A5E0((unsigned int)this + 166);
      return sub_41A590((unsigned int)(this + 298), v13, v12);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EF270 sub_4EF270
// ------------------------------------------------------------
void /*thiscall*/ sub_4EF270(void ****this)
{
  void *v2; // esi
  void ***v3; // esi
  bool v4; // zf
  void **v5; // edi

  v2 = *(this + 317);
  if ( v2 != nullptr )
  {
    sub_4382D0(*(this + 317));
    j__free(v2);
  }
  v3 = *(this + 327);
  v4 = v3 == *(this + 328);
  *(this + 317) = nullptr;
  if ( !v4 )
  {
    do
    {
      v5 = *v3;
      if ( *v3 != nullptr )
      {
        sub_42AF90(*v3);
        sub_657740(v5, 228);
      }
      *v3++ = nullptr;
    }
    while ( v3 != *(this + 328) );
  }
}



// ------------------------------------------------------------
// 0x4EF2E0 sub_4EF2E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4EF2E0(uint32_t *this)
{
  void *v2; // ebx

  v2 = this + 1;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0;
  sub_4A2FF0(this + 1);
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 23) = 0;
  *(this + 20) = 0;
  *(this + 24) = 0;
  *(this + 21) = 0;
  *(this + 25) = 0;
  *(this + 22) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *this = 0;
  sub_4A2FF0(v2);
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 23) = 0;
  *(this + 20) = 0;
  *(this + 24) = 0;
  *(this + 21) = 0;
  *(this + 25) = 0;
  *(this + 22) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4EF390 sub_4EF390
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EF390(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ebx
  uint32_t *v4; // esi
  uint32_t v6[6]; // [esp+0h] [ebp-24h] BYREF
  int v7; // [esp+20h] [ebp-4h]

  v3 = a3;
  v6[5] = v6;
  v6[4] = a3;
  v7 = 0;
  while ( 1 )
  {
    v4 = a1;
    if ( a1 == a2 )
      break;
    v6[3] = v3;
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
    {
      *v3 = *a1;
      sub_4ED6A0(v3 + 1, a1 + 1);
      qmemcpy(v3 + 18, a1 + 18, 0x34u);
      v4 = a1;
    }
    v3 += 31;
    LOBYTE(v7) = 0;
    a1 = v4 + 31;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x4EF450 sub_4EF450
// ------------------------------------------------------------
int /*cdecl*/ sub_4EF450(uint32_t *a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // ebx
  int result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  v3 = a1;
  v5[5] = v5;
  v5[4] = a1;
  v6 = 0;
  while ( 1 )
  {
    result = a2;
    if ( a2 == 0 )
      break;
    v5[3] = v3;
    LOBYTE(v6) = 1;
    if ( v3 != nullptr )
    {
      *v3 = *a3;
      sub_4ED6A0(v3 + 1, a3 + 1);
      qmemcpy(v3 + 18, a3 + 18, 0x34u);
    }
    v3 += 31;
    LOBYTE(v6) = 0;
    --a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EF510 sub_4EF510
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4EF510(uint32_t *a1, int a2, uint32_t *a3)
{
  sub_4EF450(a1, a2, a3);
  return &a1[31 * a2];
}



// ------------------------------------------------------------
// 0x4EF540 sub_4EF540
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4EF540(uint32_t **this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v5; // ecx
  void ***v6; // eax
  void ***v7; // ebx
  void ***v8; // edi
  void ***i; // esi
  uint32_t **v11; // [esp+4h] [ebp-4h]

  v5 = a3;
  v11 = this;
  if ( a3 != a4 )
  {
    v6 = (void ***)sub_4EE190(a4, *(this + 2), a3);
    v7 = (void ***)*(this + 2);
    v8 = v6;
    for ( i = v6; i != v7; i += 31 )
      sub_4BA910(i);
    v5 = a3;
    v11[2] = v8;
  }
  *a2 = v5;
  return a2;
}



// ------------------------------------------------------------
// 0x4EF5A0 sub_4EF5A0
// ------------------------------------------------------------
void /*thiscall*/ sub_4EF5A0(int this, char *a2, unsigned int a3, int *a4)
{
  int v4; // eax
  int v6; // edi
  unsigned int v7; // ecx
  int v9; // eax
  int v10; // eax
  unsigned int v11; // ecx
  int v12; // eax
  char *v13; // edi
  int v14; // eax
  unsigned int v15; // esi
  void ***v16; // eax
  uint32_t *v17; // ecx
  int v19; // edx
  uint32_t *v20; // [esp-18h] [ebp-B8h]
  uint32_t *v21; // [esp-Ch] [ebp-ACh]
  int v22; // [esp-8h] [ebp-A8h]
  int v23; // [esp+0h] [ebp-A0h] BYREF
  int v24; // [esp+Ch] [ebp-94h] BYREF
  uint32_t v25[17]; // [esp+10h] [ebp-90h] BYREF
  void **v26[14]; // [esp+54h] [ebp-4Ch] BYREF
  void *Block; // [esp+8Ch] [ebp-14h]
  int *v28; // [esp+90h] [ebp-10h]
  int v29; // [esp+9Ch] [ebp-4h]
  uint32_t *v30; // [esp+A8h] [ebp+8h]
  uint32_t *v31; // [esp+ACh] [ebp+Ch]
  int v32; // [esp+B0h] [ebp+10h]

  v4 = *a4;
  v28 = &v23;
  v26[13] = (void **)this;
  v24 = v4;
  sub_4ED6A0(v25, a4 + 1);
  qmemcpy(v26, a4 + 18, 0x34u);
  v6 = *(uint32_t *)(this + 4);
  v7 = 0;
  v29 = 0;
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(this + 12) - v6) / 124;
  if ( a3 != 0 )
  {
    if ( v6 != 0 )
      v9 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 124;
    else
      v9 = 0;
    if ( 34636833 - v9 < a3 )
      sub_4B2F20(this);
    if ( *(uint32_t *)(this + 4) != 0 )
      v10 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 124;
    else
      v10 = 0;
    if ( v7 >= a3 + v10 )
    {
      v17 = *(uint32_t **)(this + 8);
      Block = v17;
      if ( ((char *)v17 - a2) / 124 >= a3 )
      {
        v30 = &v17[-31 * a3];
        *(uint32_t *)(this + 8) = sub_4EF390(v30, v17, v17);
        sub_4EE560((int)a2, (int)v30, (int)Block);
        sub_4EE4C0(a2, &a2[124 * a3], &v24);
      }
      else
      {
        sub_4EF390(a2, v17, &a2[124 * a3]);
        v22 = a3 - (*(uint32_t *)(this + 8) - (int)a2) / 124;
        v21 = *(uint32_t **)(this + 8);
        LOBYTE(v29) = 3;
        sub_4EF510(v21, v22, &v24);
        v19 = 124 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v19;
        v29 = 0;
        sub_4EE4C0(a2, (uint32_t *)(v19 - 124 * a3), &v24);
      }
    }
    else
    {
      if ( 34636833 - (v7 >> 1) >= v7 )
        v11 = (v7 >> 1) + v7;
      else
        v11 = 0;
      if ( *(uint32_t *)(this + 4) != 0 )
        v12 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 124;
      else
        v12 = 0;
      if ( v11 < a3 + v12 )
        v11 = a3 + sub_4EAF80((int *)this);
      v32 = 124 * v11;
      v13 = (char *)operator new(124 * v11);
      v20 = *(uint32_t **)(this + 4);
      Block = v13;
      LOBYTE(v29) = 1;
      v31 = sub_4EF390(v20, a2, v13);
      sub_4EF450(v31, a3, &v24);
      sub_4EF390(a2, *(uint32_t **)(this + 8), &v31[31 * a3]);
      v14 = *(uint32_t *)(this + 4);
      v29 = 0;
      if ( v14 != 0 )
        v14 = (*(uint32_t *)(this + 8) - v14) / 124;
      v15 = v14 + a3;
      v16 = *(void ****)(this + 4);
      if ( v16 != nullptr )
      {
        sub_4BA960(v16, *(void ****)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &v13[v32];
      *(uint32_t *)(this + 8) = &v13[124 * v15];
      *(uint32_t *)(this + 4) = v13;
    }
  }
  v29 = 5;
  sub_4B5A50(v26);
  v29 = -1;
  sub_4A4940((int)v25);
}


// ------------------------------------------------------------
// 0x4EF8F0 sub_4EF8F0
// ------------------------------------------------------------
void /*thiscall*/ sub_4EF8F0(
        int this,
        unsigned int a2,
        int a3,
        char a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13,
        int a14,
        int a15,
        int a16,
        int a17,
        int a18,
        int a19,
        int a20,
        void **a21,
        int a22,
        int a23,
        int a24,
        int a25,
        int a26,
        int a27,
        int a28,
        int a29,
        int a30,
        int a31,
        int a32,
        int a33)
{
  int v33; // ebx
  unsigned int v34; // eax
  int v35; // eax

  v33 = *(uint32_t *)(this + 4);
  v34 = 0;
  if ( v33 != 0 )
    v34 = (*(uint32_t *)(this + 8) - v33) / 124;
  if ( v34 >= a2 )
  {
    if ( v33 != 0 && a2 < (*(uint32_t *)(this + 8) - v33) / 124 )
      sub_4EF540((uint32_t **)this, &a2, (uint32_t *)(v33 + 124 * a2), *(uint32_t **)(this + 8));
  }
  else
  {
    if ( v33 != 0 )
      v35 = (*(uint32_t *)(this + 8) - v33) / 124;
    else
      v35 = 0;
    sub_4EF5A0(this, *(char **)(this + 8), a2 - v35, &a3);
  }
  sub_4B5A50(&a21);
  sub_4A4940((int)&a4);
}



// ------------------------------------------------------------
// 0x4EF9D0 sub_4EF9D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4EF9D0(int this)
{
  int *v2; // eax
  int v3; // edx
  int v4; // esi
  unsigned int v5; // edx
  char *v6; // edx
  uint32_t *v7; // edi
  int v8; // eax
  int v9; // eax
  const char *v10; // eax
  int v11; // eax
  int v12; // eax
  const char *v13; // esi
  const char *v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // eax
  const char *v18; // esi
  const char *v19; // eax
  int v20; // eax
  int v21; // edi
  int v22; // eax
  const char *v23; // esi
  const char *v24; // eax
  int v25; // eax
  bool v26; // zf
  int v27; // edi
  int v28; // eax
  const char *v29; // esi
  const char *v30; // eax
  int v31; // eax
  int v32; // edi
  int v33; // eax
  const char *v34; // esi
  const char *v35; // eax
  int v36; // eax
  int v37; // edi
  int v38; // eax
  const char *v39; // esi
  const char *v40; // eax
  int v41; // eax
  int v42; // edi
  int v43; // eax
  const char *v44; // esi
  const char *v45; // eax
  int v46; // eax
  int v47; // edi
  int v48; // eax
  const char *v49; // esi
  const char *v50; // eax
  int v51; // eax
  int v52; // edi
  int v53; // eax
  const char *v54; // esi
  const char *v55; // eax
  int v56; // eax
  int v57; // edi
  int v58; // eax
  const char *v59; // esi
  const char *v60; // eax
  int v61; // eax
  int v62; // edi
  int v63; // eax
  const char *v64; // esi
  const char *v65; // eax
  int v66; // eax
  int v67; // edi
  int v68; // eax
  const char *v69; // esi
  const char *v70; // eax
  int v71; // eax
  int v72; // edi
  int v73; // eax
  const char *v74; // esi
  const char *v75; // eax
  int v76; // eax
  int v77; // edi
  int v78; // eax
  const char *v79; // esi
  const char *v80; // eax
  int v81; // eax
  int v82; // edi
  int v83; // eax
  const char *v84; // esi
  const char *v85; // eax
  int v86; // eax
  int v87; // esi
  int v88; // ecx
  unsigned int v89; // edi
  int *v90; // edx
  int v91; // esi
  unsigned int v92; // edx
  uint32_t *v93; // eax
  uint32_t *v94; // edx
  int v95; // edi
  int v96; // eax
  const char *v97; // esi
  const char *v98; // eax
  int v99; // esi
  int v100; // ecx
  int v101; // edx
  unsigned int v102; // edi
  int *v103; // eax
  int v104; // esi
  unsigned int v105; // edx
  uint32_t *v106; // eax
  uint32_t *v107; // edx
  char v108; // al
  char v109; // si
  char v110; // al
  int v111; // eax
  int v112; // esi
  unsigned int v113; // edi
  int *v114; // edx
  int v115; // edx
  int v117[30]; // [esp-7Ch] [ebp-B4h] BYREF
  int v118; // [esp-4h] [ebp-3Ch]
  int v119; // [esp+Ch] [ebp-2Ch]
  int v120; // [esp+10h] [ebp-28h] BYREF
  int v121; // [esp+14h] [ebp-24h] BYREF
  int v122; // [esp+18h] [ebp-20h]
  int v123; // [esp+1Ch] [ebp-1Ch] BYREF
  uint32_t *v124; // [esp+20h] [ebp-18h]
  char *v125; // [esp+24h] [ebp-14h]
  uint32_t *v126; // [esp+28h] [ebp-10h]
  int v127; // [esp+34h] [ebp-4h]

  LOBYTE(v2) = *(uint8_t *)(this + 1320);
  if ( (uint8_t)v2 == 0 )
  {
    v2 = *(int **)(this + 1332);
    if ( v2 != nullptr )
    {
      v3 = v2[264];
      if ( v3 != 0 )
      {
        v5 = (int)((uint64_t)(2216757315LL * (v2[265] - v3)) >> 32) >> 6;
        v4 = v5 + (v5 >> 31);
      }
      else
      {
        v4 = 0;
      }
      v120 = v4;
      v121 = (int)v117;
      sub_4EF2E0(v117);
      sub_4EF8F0(
        this + 1288,
        v4,
        v117[0],
        v117[1],
        v117[2],
        v117[3],
        v117[4],
        v117[5],
        v117[6],
        v117[7],
        v117[8],
        v117[9],
        v117[10],
        v117[11],
        v117[12],
        v117[13],
        v117[14],
        v117[15],
        v117[16],
        v117[17],
        v117[18],
        v117[19],
        v117[20],
        v117[21],
        v117[22],
        v117[23],
        v117[24],
        v117[25],
        v117[26],
        v117[27],
        v117[28],
        v117[29],
        v118);
      v122 = 0;
      if ( v4 > 0 )
      {
        while ( 1 )
        {
          v6 = (char *)(124 * v122 + *(uint32_t *)(this + 1292));
          v7 = (uint32_t *)(124 * v122 + *(uint32_t *)(*(uint32_t *)(this + 1332) + 1056));
          v8 = *v7;
          v118 = (int)szPassword;
          v125 = v6;
          v126 = v7;
          *(uint32_t *)v6 = v8;
          if ( (uint8_t)sub_42FD40(v118) != 0 )
          {
            v123 = sub_42FCB0(228);
            v127 = 0;
            if ( v123 != 0 )
            {
              v9 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v121 = v9;
              v10 = (const char *)sub_41ACF0(v7 + 1);
              v11 = sub_4319E0(v123, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), (const char *)v121, v10, v118);
            }
            else
            {
              v11 = 0;
            }
            v127 = -1;
            *((uint32_t *)v125 + 1) = v11;
          }
          if ( (uint8_t)sub_42FD40(szPassword) != 0 )
          {
            v121 = sub_42FCB0(228);
            v127 = 1;
            if ( v121 != 0 )
            {
              v12 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v13 = (const char *)v12;
              v14 = (const char *)sub_41ACF0(v7 + 2);
              v15 = sub_4319E0(v121, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v13, v14, v118);
            }
            else
            {
              v15 = 0;
            }
            v127 = -1;
            *((uint32_t *)v125 + 2) = v15;
          }
          if ( (uint8_t)sub_42FD40(szPassword) != 0 )
          {
            v16 = sub_42FCB0(228);
            v121 = v16;
            v127 = 2;
            if ( v16 != 0 )
            {
              v17 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v18 = (const char *)v17;
              v19 = (const char *)sub_41ACF0(v126 + 3);
              v20 = sub_4319E0(v16, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v18, v19, v118);
            }
            else
            {
              v20 = 0;
            }
            v7 = v126;
            v127 = -1;
            *((uint32_t *)v125 + 3) = v20;
          }
          v124 = v7 + 4;
          v121 = v125 - (char *)v7;
          v123 = 2;
          do
          {
            if ( strcmp((const char *)sub_41ACF0(v124), szPassword) != 0 )
            {
              v21 = sub_42FCB0(228);
              v119 = v21;
              v127 = 3;
              if ( v21 != 0 )
              {
                v22 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
                v118 = 1;
                v23 = (const char *)v22;
                v24 = (const char *)sub_41ACF0(v124);
                v25 = sub_4319E0(v21, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v23, v24, v118);
              }
              else
              {
                v25 = 0;
              }
              v127 = -1;
              *(uint32_t *)((char *)v124 + v121) = v25;
            }
            v26 = v123 == 1;
            ++v124;
            --v123;
          }
          while ( !v26 );
          if ( strcmp((const char *)sub_41ACF0(v126 + 6), szPassword) != 0 )
          {
            v27 = sub_42FCB0(228);
            v119 = v27;
            v127 = 4;
            if ( v27 != 0 )
            {
              v28 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v29 = (const char *)v28;
              v30 = (const char *)sub_41ACF0(v126 + 6);
              v31 = sub_4319E0(v27, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v29, v30, v118);
            }
            else
            {
              v31 = 0;
            }
            v127 = -1;
            *((uint32_t *)v125 + 6) = v31;
          }
          if ( strcmp((const char *)sub_41ACF0(v126 + 7), szPassword) != 0 )
          {
            v32 = sub_42FCB0(228);
            v119 = v32;
            v127 = 5;
            if ( v32 != 0 )
            {
              v33 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v34 = (const char *)v33;
              v35 = (const char *)sub_41ACF0(v126 + 7);
              v36 = sub_4319E0(v32, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v34, v35, v118);
            }
            else
            {
              v36 = 0;
            }
            v127 = -1;
            *((uint32_t *)v125 + 7) = v36;
          }
          if ( strcmp((const char *)sub_41ACF0(v126 + 8), szPassword) != 0 )
          {
            v37 = sub_42FCB0(228);
            v119 = v37;
            v127 = 6;
            if ( v37 != 0 )
            {
              v38 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v39 = (const char *)v38;
              v40 = (const char *)sub_41ACF0(v126 + 8);
              v41 = sub_4319E0(v37, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v39, v40, v118);
            }
            else
            {
              v41 = 0;
            }
            v127 = -1;
            *((uint32_t *)v125 + 8) = v41;
          }
          if ( strcmp((const char *)sub_41ACF0(v126 + 9), szPassword) != 0 )
          {
            v42 = sub_42FCB0(228);
            v119 = v42;
            v127 = 7;
            if ( v42 != 0 )
            {
              v43 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v44 = (const char *)v43;
              v45 = (const char *)sub_41ACF0(v126 + 9);
              v46 = sub_4319E0(v42, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v44, v45, v118);
            }
            else
            {
              v46 = 0;
            }
            v127 = -1;
            *((uint32_t *)v125 + 9) = v46;
          }
          if ( strcmp((const char *)sub_41ACF0(v126 + 10), szPassword) != 0 )
          {
            v47 = sub_42FCB0(228);
            v119 = v47;
            v127 = 8;
            if ( v47 != 0 )
            {
              v48 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v49 = (const char *)v48;
              v50 = (const char *)sub_41ACF0(v126 + 10);
              v51 = sub_4319E0(v47, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v49, v50, v118);
            }
            else
            {
              v51 = 0;
            }
            v127 = -1;
            *((uint32_t *)v125 + 18) = v51;
          }
          v123 = (int)(v125 + 92);
          v124 = v126 + 15;
          v121 = 4;
          do
          {
            if ( strcmp((const char *)sub_41ACF0(v124 - 4), szPassword) != 0 )
            {
              v52 = sub_42FCB0(228);
              v119 = v52;
              v127 = 9;
              if ( v52 != 0 )
              {
                v53 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
                v118 = 1;
                v54 = (const char *)v53;
                v55 = (const char *)sub_41ACF0(v124 - 4);
                v56 = sub_4319E0(v52, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v54, v55, v118);
              }
              else
              {
                v56 = 0;
              }
              v127 = -1;
              *(uint32_t *)(v123 - 16) = v56;
            }
            if ( strcmp((const char *)sub_41ACF0(v124), szPassword) != 0 )
            {
              v57 = sub_42FCB0(228);
              v119 = v57;
              v127 = 10;
              if ( v57 != 0 )
              {
                v58 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
                v118 = 1;
                v59 = (const char *)v58;
                v60 = (const char *)sub_41ACF0(v124);
                v61 = sub_4319E0(v57, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v59, v60, v118);
              }
              else
              {
                v61 = 0;
              }
              v127 = -1;
              *(uint32_t *)v123 = v61;
            }
            v26 = v121 == 1;
            ++v124;
            v123 += 4;
            --v121;
          }
          while ( !v26 );
          if ( strcmp((const char *)sub_41ACF0(v126 + 19), szPassword) != 0 )
          {
            v62 = sub_42FCB0(228);
            v119 = v62;
            v127 = 11;
            if ( v62 != 0 )
            {
              v63 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v64 = (const char *)v63;
              v65 = (const char *)sub_41ACF0(v126 + 19);
              v66 = sub_4319E0(v62, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v64, v65, v118);
            }
            else
            {
              v66 = 0;
            }
            v127 = -1;
            *((uint32_t *)v125 + 27) = v66;
          }
          if ( strcmp((const char *)sub_41ACF0(v126 + 20), szPassword) != 0 )
          {
            v67 = sub_42FCB0(228);
            v119 = v67;
            v127 = 12;
            if ( v67 != 0 )
            {
              v68 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v69 = (const char *)v68;
              v70 = (const char *)sub_41ACF0(v126 + 20);
              v71 = sub_4319E0(v67, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v69, v70, v118);
            }
            else
            {
              v71 = 0;
            }
            v127 = -1;
            *((uint32_t *)v125 + 28) = v71;
          }
          if ( strcmp((const char *)sub_41ACF0(v126 + 21), szPassword) != 0 )
          {
            v72 = sub_42FCB0(228);
            v119 = v72;
            v127 = 13;
            if ( v72 != 0 )
            {
              v73 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v74 = (const char *)v73;
              v75 = (const char *)sub_41ACF0(v126 + 21);
              v76 = sub_4319E0(v72, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v74, v75, v118);
            }
            else
            {
              v76 = 0;
            }
            v127 = -1;
            *((uint32_t *)v125 + 29) = v76;
          }
          if ( strcmp((const char *)sub_41ACF0(v126 + 22), szPassword) != 0 )
          {
            v77 = sub_42FCB0(228);
            v119 = v77;
            v127 = 14;
            if ( v77 != 0 )
            {
              v78 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v79 = (const char *)v78;
              v80 = (const char *)sub_41ACF0(v126 + 22);
              v81 = sub_4319E0(v77, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v79, v80, v118);
            }
            else
            {
              v81 = 0;
            }
            v127 = -1;
            *((uint32_t *)v125 + 30) = v81;
          }
          v26 = v126[24] == v126[25];
          v124 = (uint32_t *)v126[24];
          if ( !v26 )
          {
            do
            {
              if ( strcmp((const char *)sub_41ACF0(v124), szPassword) == 0 )
              {
                v91 = *((uint32_t *)v125 + 11);
                v88 = (int)(v125 + 40);
                v121 = 0;
                if ( v91 != 0 )
                  v92 = (*((uint32_t *)v125 + 12) - v91) >> 2;
                else
                  v92 = 0;
                if ( v91 == 0 || v92 >= (*((uint32_t *)v125 + 13) - v91) >> 2 )
                {
LABEL_103:
                  sub_42AC90(v88, *(char **)(v88 + 8), 1u, &v121);
                  goto LABEL_104;
                }
                v93 = *((uint32_t **)v125 + 12);
                *v93 = 0;
                *(uint32_t *)(v88 + 8) = v93 + 1;
              }
              else
              {
                v82 = sub_42FCB0(228);
                v119 = v82;
                v127 = 15;
                if ( v82 != 0 )
                {
                  v83 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
                  v118 = 1;
                  v84 = (const char *)v83;
                  v85 = (const char *)sub_41ACF0(v124);
                  v86 = sub_4319E0(v82, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v84, v85, v118);
                }
                else
                {
                  v86 = 0;
                }
                v87 = *((uint32_t *)v125 + 11);
                v88 = (int)(v125 + 40);
                v127 = -1;
                v121 = v86;
                if ( v87 != 0 )
                  v89 = (*((uint32_t *)v125 + 12) - v87) >> 2;
                else
                  v89 = 0;
                if ( v87 == 0 || v89 >= (*((uint32_t *)v125 + 13) - v87) >> 2 )
                  goto LABEL_103;
                v90 = *((int **)v125 + 12);
                *v90 = v86;
                *(uint32_t *)(v88 + 8) = v90 + 1;
              }
LABEL_104:
              v94 = (uint32_t *)v126[25];
              ++v124;
            }
            while ( v124 != v94 );
          }
          v26 = v126[28] == v126[29];
          v124 = (uint32_t *)v126[28];
          if ( !v26 )
            break;
LABEL_125:
          if ( ++v122 >= v120 )
            goto LABEL_126;
        }
        v121 = (int)(v125 + 56);
        while ( 1 )
        {
          if ( strcmp((const char *)sub_41ACF0(v124), szPassword) == 0 )
          {
            v100 = v121;
            v104 = *(uint32_t *)(v121 + 4);
            v123 = 0;
            if ( v104 != 0 )
              v105 = (*(uint32_t *)(v121 + 8) - v104) >> 2;
            else
              v105 = 0;
            if ( v104 == 0 || v105 >= (*(uint32_t *)(v121 + 12) - v104) >> 2 )
            {
LABEL_123:
              sub_42AC90(v100, *(char **)(v100 + 8), 1u, &v123);
              goto LABEL_124;
            }
            v106 = *(uint32_t **)(v121 + 8);
            *v106 = 0;
            *(uint32_t *)(v100 + 8) = v106 + 1;
          }
          else
          {
            v95 = sub_42FCB0(228);
            v119 = v95;
            v127 = 16;
            if ( v95 != 0 )
            {
              v96 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v97 = (const char *)v96;
              v98 = (const char *)sub_41ACF0(v124);
              v99 = sub_4319E0(v95, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v97, v98, v118);
            }
            else
            {
              v99 = 0;
            }
            v127 = -1;
            v123 = v99;
            sub_699070(2);
            v100 = v121;
            v101 = *(uint32_t *)(v121 + 4);
            if ( v101 != 0 )
              v102 = (*(uint32_t *)(v121 + 8) - v101) >> 2;
            else
              v102 = 0;
            if ( v101 == 0 || v102 >= (*(uint32_t *)(v121 + 12) - v101) >> 2 )
              goto LABEL_123;
            v103 = *(int **)(v121 + 8);
            *v103 = v99;
            *(uint32_t *)(v100 + 8) = v103 + 1;
          }
LABEL_124:
          v107 = (uint32_t *)v126[29];
          if ( ++v124 == v107 )
            goto LABEL_125;
        }
      }
LABEL_126:
      v2 = *(int **)(this + 1332);
      v26 = v2[20] == v2[21];
      v123 = v2[20];
      if ( !v26 )
      {
        do
        {
          if ( strcmp((const char *)sub_41ACF0(v123), szPassword) != 0 )
          {
            v119 = sub_42FCB0(228);
            v127 = 17;
            if ( v119 != 0 )
            {
              v108 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);
              v118 = 1;
              v109 = v108;
              v110 = sub_41ACF0(v123);
              v111 = sub_431920(v109, v110, v118);
            }
            else
            {
              v111 = 0;
            }
            v112 = *(uint32_t *)(this + 1308);
            v127 = -1;
            v120 = v111;
            if ( v112 != 0 )
              v113 = (*(uint32_t *)(this + 1312) - v112) >> 2;
            else
              v113 = 0;
            if ( v112 != 0 && v113 < (*(uint32_t *)(this + 1316) - v112) >> 2 )
            {
              v114 = *(int **)(this + 1312);
              *v114 = v111;
              *(uint32_t *)(this + 1312) = v114 + 1;
            }
            else
            {
              sub_42AC90(this + 1304, *(char **)(this + 1312), 1u, &v120);
            }
          }
          v115 = *(uint32_t *)(*(uint32_t *)(this + 1332) + 84);
          LOBYTE(v2) = v123 + 4;
          v123 += 4;
        }
        while ( v123 != v115 );
      }
      *(uint8_t *)(this + 1320) = 1;
    }
  }
  return (char)v2;
}

