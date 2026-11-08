// ============================================================
// 【40JP逆向源代码工程】combat/passive_object.cpp
// 模块: PassiveObject 生成/召唤/精炼 + 第三类对象大家族（PO/附加器/对话窗/弹幕）
// 来源: work/dump_skills.txt  区块: 0x600000-0x620000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
//        语义与 IDA Hex-Rays 逐字对应; 逐行精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 621
// ------------------------------------------------------------
// ★ 本文件已按《21_打击感公式算法速查》P32/P36 与研究 20（§1.1/§5.1/§10、P24/29/33/35/36/37/38/41）锚点升级注释：
//   0x6000E0/0x6183A0 PO 受击表现槽 vmt1D8 → 调 sub_4D7960 飘字咽喉（§1.1 case 0x14）
//   0x6001C0 PO 攻击判定槽 vmt214 → 消费 [ATTACK BOX] float×6 帧表（P37-2）+ vt+600/608 无敌门（P35）→ sub_4E5F70 硬直率掷（§5.1）
//   0x600C20/0x6011B0 PO 生成工厂（「PASSIVEOBJECT CREATE FAIL!」双路径）+ sub_4A3450/sub_4B2970 attackinfo（P29）
//   0x6014F0 精炼炉 cube 脚本解析器（[cube index]/[legacy info]/[skill info]/[skill prob]/[cube creation const]）
//   0x610C00 召唤阵三段动画 + 四属性 Spirit 召唤（0x60 区字符串证据本体）
//   0x6004B0 PO 数量自适应透明度【新发现】；0x60E900 死亡衍生 PO 基类【新发现】；0x60C8C0 粒子工厂 PO【新发现】
//   全文件：出生/循环/命中音效 TAG 走 vt+212 播音链（P32）；.ptl 发射器经 sub_428F30（P36）；
//           演出经 sub_4600B0→sub_45FE80 演播层（P33）；震屏经 sub_424120（P41）；
//           状态槽写入经目标 vt+760（§10 17 槽异常状态）；防篡改读写 sub_41A590/41A5E0（P24）
// ------------------------------------------------------------
// 分区总览（11 区，横幅见正文）：
//   1 PO 基类核心与生成工厂  2 掉落搬运与 MP 恢复  3 附加器(IRDAppendage)道具/装备族
//   4 临时判定与霸体  5 NPC 对话窗  6 神枪手子弹系  7 连接体/草丛/地图物件
//   8 元素与自然现象 PO  9 召唤/投技/鬼神/气功 PO  10 法师投射物与陷阱  11 怪物 PO 弹幕/陷阱大全
// ------------------------------------------------------------
// 字符串证据总类（详见各函数头注释）：PO 生成失败双串、cube 脚本五标签、四属性 Spirit 召唤动画、
//   SummonCircle 三段法阵、SuperArmor 双动画、ForceField 四段资源、Ghost 三鬼神 TAG、
//   TRAP_OCTOPUS 三段陷阱 TAG、冰浪 ICEWAVE_CREATE 三形态、NapalmBomb 燃烧四件套、
//   Gunner 弹种×枪种动画矩阵、MarchingFortress 无 —— 各资源路径均标注归属（PassiveObject/Common|Monster|Character 系）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】PO 基类核心与生成工厂（0x6000B0-0x601A50）
// CNRDPassiveObject 虚槽族（生成/受击飘字/攻击判定/主循环/表现壳）+ 工厂双路径
// （按文件名 0x600C20 / 按索引 0x6011B0，失败串 PASSIVEOBJECT CREATE FAIL!）
// + 精炼炉 cube 脚本解析器 0x6014F0（[cube index]/[skill info] 等五标签唯一定义点）
// ============================================================
// ------------------------------------------------------------
// 0x6000B0 CNRDPassiveObject__vmtC
// ------------------------------------------------------------
// PO 生成槽（vmtC）：先调 IRDCollisionObject__vmtC 基类行为，再做『宿主增伤档位』初始化。
// 证据：条件号 261641/261642/261643/261644 经 sub_4DB0E0 条件查询互斥命中，把攻击上下文(+20)设为 0/1/3/2 档并 ×1.05（+5% 浮动增伤）【推断：装备/称号按条件加成的 PO 化载体】。
float */*thiscall*/ CNRDPassiveObject__vmtC(int *this)
{
  float *result; // eax
  int pObj; // eax
  int v4; // [esp-4h] [ebp-8h]

  IRDCollisionObject__vmtC(this);
  (*(void (/*thiscall*/ **)(int *, int *))(*this + 344))(this, this + 181);
  result = (float *)(*(int (/*thiscall*/ **)(int *, int))(*this + 684))(this, v4);
  if ( result != nullptr )
  {
    pObj = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
    result = (float *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529);
    if ( (uint8_t)result != 0 )
    {
      result = *(float **)((*(int (/*thiscall*/ **)(int *))(*this + 684))(this) + 7772);
      if ( result == (float *)1 || result == (float *)2 )
      {
        if ( (uint8_t)sub_4DB0E0(261641) != 0 )
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 348))(this) + 20) = 0;
        if ( (uint8_t)sub_4DB0E0(261642) != 0 )
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 348))(this) + 20) = 1;
        if ( (uint8_t)sub_4DB0E0(261643) != 0 )
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 348))(this) + 20) = 3;
        if ( (uint8_t)sub_4DB0E0(261644) != 0 )
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 348))(this) + 20) = 2;
        result = (float *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this);
        *result = *result * 1.05;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6000E0 CNRDPassiveObject__vmt1D8
// ------------------------------------------------------------
// PO 受击表现槽（vmt1D8）：读自身 HP（vt+672）与来伤比较选飘字样式（打满=0 普通白字 / 未打满=2 黄字，受方 dword_8F7C04==本体时再叠加标志），
// 随后调 sub_4D7960 —— 即研究 20 §1.1 case 0x14 定案的『飘字咽喉』；再经 vt+80 取伤害数值 → sub_45EBE0 构建飘字参数 → vt+692 回写。
// 对应研究：飘字层（盒中心+50 / 5 层精灵）。
int /*userpurge*/ CNRDPassiveObject__vmt1D8@<eax>(
        uint32_t *a1@<ecx>,
        int a2@<ebx>,
        int a3@<edi>,
        int a4,
        int a5,
        int a6,
        int a7)
{
  int result; // eax
  int *v9; // eax
  int v10; // ebx
  int v11; // edi
  int v12; // eax
  uint32_t *v13; // eax
  int v14; // eax
  int v15; // [esp-Ch] [ebp-20h]
  char v18; // [esp-4h] [ebp-18h]
  int v19; // [esp+8h] [ebp-Ch]
  int v20; // [esp+Ch] [ebp-8h]
  int v21; // [esp+10h] [ebp-4h]
  int v22; // [esp+1Ch] [ebp+8h]
  int v23; // [esp+20h] [ebp+Ch]

  result = a4 - 1;
  if ( a4 != 1 )
  {
    a1[240] = a4;
    return result;
  }
  v9 = *(int **)(a5 + 4);
  v10 = *v9;
  v23 = v9[2];
  v11 = v9[1];
  v22 = v9[4];
  v19 = v9[5];
  v20 = v9[6];
  v21 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 672))(a1, a3, a2);
  *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 672))(a1) = v11;
  if ( v21 > v11 )
  {
    v18 = dword_8F7C04 == a1[143];
    v15 = 0;
LABEL_7:
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 124))(a1);
    sub_4D7960(v10, v11, (int)a1, v23, v12 + 1, v22, v10, v15, 0, v18);  // 【飘字咽喉（§1.1 case 0x14；第 14/39 轮 5 层精灵）】
    goto LABEL_8;
  }
  if ( v21 < v11 )
  {
    v18 = 0;
    v15 = 2;
    goto LABEL_7;
  }
LABEL_8:
  v13 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 80))(a1);
  v14 = sub_45EBE0(v13, v19, v20);
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*a1 + 692))(a1, v14, v10, v23);
}



// ------------------------------------------------------------
// 0x6001C0 CNRDPassiveObject__vmt214
// ------------------------------------------------------------
// PO 攻击判定槽（vmt214）：门 = +700 使能 → vt+308 激活 → 目标 vt+200/vt+608（受击盒使能 = 研究 20 P35 的无敌门 this+640/641）→ vt+360 判重。
// 判定体：sub_4FEF30 取双方动画攻击盒列表（float×6/条 步进 6 —— 与研究 20 P37-2 的 [ATTACK BOX]/[DAMAGE BOX] 帧表布局互证），
// 手工展开 AABB 求交（x 区间重叠即命中），命中则调 sub_4E5F70 = 硬直率掷/伤害输入管道（研究 21 §5.1 第 14 轮定案）。
// 角度翻转：vt+152==0 时 x 取负（镜像盒）。
char /*thiscall*/ sub_6001C0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 【PO 攻击判定槽 vmt214 → 消费 [ATTACK BOX] float×6…】
{
  char result; // al
  int v7; // eax
  int fld_e30; // eax
  int v9; // eax
  int v10; // eax
  int fld_e302; // ecx
  int v12; // esi
  int v13; // eax
  int v14; // eax
  float *v15; // esi
  double v16; // st7
  int v17; // eax
  float *v18; // esi
  double v19; // st7
  int v20; // eax
  int v21; // edx
  int v22; // esi
  int fld_e303; // eax
  float v24; // edx
  int v25; // eax
  int v26; // eax
  double v27; // st7
  float v28; // [esp+4h] [ebp-2Ch] BYREF
  float v29; // [esp+8h] [ebp-28h]
  float v30; // [esp+Ch] [ebp-24h]
  float v31; // [esp+10h] [ebp-20h]
  int v32; // [esp+14h] [ebp-1Ch]
  float v33; // [esp+18h] [ebp-18h]
  int v34; // [esp+1Ch] [ebp-14h]
  int i; // [esp+20h] [ebp-10h]
  int v36; // [esp+24h] [ebp-Ch]
  int v37; // [esp+28h] [ebp-8h]
  int v38; // [esp+2Ch] [ebp-4h]
  int v39; // [esp+40h] [ebp+10h]
  int v40; // [esp+40h] [ebp+10h]
  int v41; // [esp+40h] [ebp+10h]

  result = *((uint8_t *)this + 700);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
    if ( result != 0 )
    {
      if ( *(this + 30) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 600))(this) != 0
        && nArg4 != 0
        && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 200))(nArg4) != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 608))(nArg4) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 360))(this, nArg4) == 0 )
      {
        sub_4938F0(*(this + 30));
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 200))(nArg4);
        sub_4938F0(v7);
        fld_e30 = sub_42F220(*(this + 30));
        if ( (uint8_t)sub_600070(fld_e30 + 56) == 0 )
        {
          v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 200))(nArg4);
          v10 = sub_42F220(v9);
          if ( (uint8_t)sub_600070(v10 + 72) == 0 )
          {
            fld_e302 = *(this + 30);
            v38 = 0;
            v39 = 0xFFFF;
            v37 = 0;
            v36 = 0xFFFF;
            v12 = sub_42F220(fld_e302) + 56;
            v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 200))(nArg4);
            v34 = sub_42F220(v13) + 72;
            v14 = sub_4FEF30(v12);
            if ( v14 != 0 )
            {
              v15 = (float *)(*(uint32_t *)(v12 + 4) + 8);
              for ( i = v14; i != 0; --i )
              {
                if ( (double)v39 > *v15 )
                  v39 = (uint64_t)*v15;
                v16 = v15[3] + *v15;
                if ( v16 > (double)v38 )
                  v38 = (uint64_t)v16;
                v15 += 6;
              }
            }
            v17 = sub_4FEF30(v34);
            if ( v17 != 0 )
            {
              v18 = (float *)(*(uint32_t *)(v34 + 4) + 8);
              for ( i = v17; i != 0; --i )
              {
                if ( (double)v36 > *v18 )
                  v36 = (uint64_t)*v18;
                v19 = v18[3] + *v18;
                if ( v19 > (double)v37 )
                  v37 = (uint64_t)v19;
                v18 += 6;
              }
            }
            v20 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
            v21 = *this;
            v38 += v20;
            v40 = (*(int (/*thiscall*/ **)(uint32_t *))(v21 + 128))(this) + v39;
            v37 += (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 128))(nArg4);
            v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 128))(nArg4) + v36;
            if ( v38 >= v22 && v37 >= v40 )
            {
              fld_e303 = *(uint32_t *)(sub_42F220(*(this + 30)) + 60);
              v28 = *(float *)fld_e303;
              v29 = *(float *)(fld_e303 + 4);
              v30 = *(float *)(fld_e303 + 8);
              v31 = *(float *)(fld_e303 + 12);
              v32 = *(uint32_t *)(fld_e303 + 16);
              v24 = *(float *)(fld_e303 + 20);
              v25 = *this;
              v33 = v24;
              if ( (*(int (/*thiscall*/ **)(uint32_t *))(v25 + 152))(this) == 0 )
                v28 = -v28 - v31;
              v34 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
              v26 = *this;
              v28 = (double)v34 + v28;
              v34 = (*(int (/*thiscall*/ **)(uint32_t *))(v26 + 124))(this);
              v29 = (double)v34 + v29;
              if ( v40 <= v22 )
                v40 = v22;
              v27 = (double)v40 + v30;
              v41 = v38;
              v30 = v27;
              if ( v38 >= v37 )
                v41 = v37;
              v33 = (double)v41 - v30;
              sub_4E5F70(nArg4, (int)this, nArg4, &v28, 1, 1);
            }
          }
        }
      }
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6004B0 sub_6004B0
// ------------------------------------------------------------
// ★ PO 数量自适应透明度（vmt10 实体）：以 vt+80 容器遍历同类 PO，统计满足条件 33 且可见(+945)的个数 dword_9B9358，
// 目标 alpha = 100 − 15×n（下限 5）——同类 PO 挤在同一屏时逐个调暗防杂乱；
// alpha 经 sub_4049C0（P30/P36 同款 lerp）在 255↔目标间 200ms 渐变（GetTickCount 计时，+237 状态 0/1/2/3 往返），
// 末尾 sub_491F80(-1,-1,-1,alpha,1) 写动画顶点色（研究 20 P37 [RGBA] 调制）。
// 【新发现】这是 PO 层的『防堆叠淡出』机制：数量越多整体越透明，200ms 渐变保证无跳变。
char /*thiscall*/ sub_6004B0(uint8_t *this)
{
  int pThis_50; // eax
  void **v3; // edx
  unsigned int v4; // ebx
  uint8_t *v5; // eax
  int pThis_502; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int pThis_503; // eax
  int v11; // edx
  int pObj; // ecx
  int pThis_504; // eax
  int v14; // edx
  int pObj2; // esi
  bool v16; // zf
  int v17; // eax
  int pThis_C8; // eax
  int v19; // esi
  int pThis_ED; // eax
  DWORD dwNow; // eax
  uint64_t pThis_EE2; // rax
  DWORD TickCount; // eax
  uint64_t pThis_EE; // rax
  int pThis_C82; // eax
  float v27; // [esp+0h] [ebp-20h]
  float v28; // [esp+4h] [ebp-1Ch]
  int pThis_EF; // [esp+8h] [ebp-18h]
  int v30; // [esp+1Ch] [ebp-4h]

  pThis_50 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);
  v3 = *(void ***)(pThis_50 + 120);
  v4 = 0;
  if ( v3 != nullptr && (*(uint32_t *)(pThis_50 + 124) - (int)v3) >> 2 != 0 )
    v5 = *v3;
  else
    v5 = nullptr;
  if ( this == v5 )
  {
    dword_9B9358 = 0;
    while ( 1 )
    {
      while ( 1 )
      {
        pThis_502 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);
        v7 = *(uint32_t *)(pThis_502 + 120);
        v8 = pThis_502 + 116;
        if ( v7 != 0 )
          v9 = (*(uint32_t *)(v8 + 8) - v7) >> 2;
        else
          v9 = 0;
        if ( (int)v4 >= v9 )
          goto LABEL_29;
        pThis_503 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);
        v11 = *(uint32_t *)(pThis_503 + 120);
        if ( v11 != 0 && v4 < (*(uint32_t *)(pThis_503 + 124) - v11) >> 2 )
          pObj = *(uint32_t *)(v11 + 4 * v4);
        else
          pObj = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 33) != 0 )
        {
          pThis_504 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);
          v14 = *(uint32_t *)(pThis_504 + 120);
          if ( v14 != 0 && v4 < (*(uint32_t *)(pThis_504 + 124) - v14) >> 2 )
            pObj2 = *(uint32_t *)(v14 + 4 * v4);
          else
            pObj2 = 0;
          if ( *(uint8_t *)(pObj2 + 945) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 200))(pObj2) != 0 )
            break;
        }
LABEL_28:
        ++v4;
      }
      v16 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 492))(pObj2, dword_8F7C04) == 1;
      v17 = *(uint32_t *)(pObj2 + 948);
      if ( !v16 )
      {
        if ( v17 == 2 )
        {
          *(uint32_t *)(pObj2 + 952) = GetTickCount();
          *(uint32_t *)(pObj2 + 948) = 1;
        }
        goto LABEL_28;
      }
      if ( v17 == 3 )
      {
        *(uint32_t *)(pObj2 + 952) = GetTickCount();
        *(uint32_t *)(pObj2 + 948) = 0;
      }
      ++dword_9B9358;
      ++v4;
    }
  }
LABEL_29:
  LOBYTE(pThis_C8) = *(this + 945);
  if ( (uint8_t)pThis_C8 != 0 )
  {
    pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
    if ( pThis_C8 != 0 )
    {
      v19 = 100 - 15 * dword_9B9358;
      v30 = v19;
      if ( v19 < 5 )
      {
        v19 = 5;
        v30 = 5;
      }
      pThis_ED = *((uint32_t *)this + 237);
      if ( pThis_ED != 0 )
      {
        if ( pThis_ED == 1 )
        {
          TickCount = GetTickCount();
          v27 = (float)v30;
          pThis_EE = (uint64_t)sub_4049C0(v27, 255.0, TickCount - *((uint32_t *)this + 238), 200);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          *((uint32_t *)this + 239) = pThis_EE;
          if ( (uint32_t)pThis_EE == 255 )
            *((uint32_t *)this + 237) = 3;
        }
      }
      else
      {
        dwNow = GetTickCount();
        v28 = (float)v30;
        pThis_EE2 = (uint64_t)sub_4049C0(255.0, v28, dwNow - *((uint32_t *)this + 238), 200);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        *((uint32_t *)this + 239) = pThis_EE2;
        if ( (uint32_t)pThis_EE2 == v19 )
          *((uint32_t *)this + 237) = 2;
      }
      pThis_C82 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
      sub_4938F0(pThis_C82);
      pThis_EF = *((uint32_t *)this + 239);
      (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
      LOBYTE(pThis_C8) = sub_491F80(-1, -1, -1, pThis_EF, 1);
    }
  }
  return pThis_C8;
}


// ------------------------------------------------------------
// 0x600700 sub_600700
// ------------------------------------------------------------
// PVP 清旗：场景 dword_8F7A24+12==4（P42 定案场景 4/6 = PVP）且 dword_9A012C 时，遍历 dword_8F8500 对象链表，
// 对 +196 与本 PO 匹配者（vt+696）清 +161 标志位【推断：PO 仇恨/可见旗复位】。被基类 vmt14C 尾部调用。
int */*thiscall*/ sub_600700(void *this)
{
  int *result; // eax
  int v2; // esi
  bool v3; // zf
  int v5; // eax
  int v6; // [esp+8h] [ebp-4h] BYREF

  result = *(int **)(dword_8F8500 + 8);
  v2 = *result;
  v3 = *result == (uint32_t)result;
  v6 = *result;
  if ( !v3 )
  {
    do
    {
      v5 = *(uint32_t *)(v2 + 16);
      if ( v5 != 0
        && (*(uint8_t (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 696))(this, *(uint32_t *)(v5 + 196)) == 1
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(uint32_t *)(v2 + 16) + 196) + 200))(*(uint32_t *)(*(uint32_t *)(v2 + 16) + 196)) != 0 )
      {
        *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(uint32_t *)(v2 + 16) + 196) + 200))(*(uint32_t *)(*(uint32_t *)(v2 + 16) + 196))
                 + 161) = 0;
      }
      sub_41C5E0(&v6);
      result = (int *)dword_8F8500;
      v2 = v6;
    }
    while ( v6 != *(uint32_t *)(dword_8F8500 + 8) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x600790 CNRDPassiveObject__vmt12C
// ------------------------------------------------------------
// PO 移除联动槽（vmt12C）：基类 IRDCollisionObject__vmt12C（目标移除/观察者通知）之后：
// a2==+173 记录的宿主且满足条件 33 → vt+680 回填宿主字段（否则清 0）；
// a2==自身（PO 死亡）→ 取死亡坐标（vt+128/124/120）播放 +219 动画对象并 sub_4600B0 演播层入列（层 2 = 命中特效层，P33）。
// 对应研究：P33 演播层分桶 / 死亡演出。
void /*thiscall*/ CNRDPassiveObject__vmt12C(uint32_t *this, int nArg2)
{
  int v3; // ebx
  int v4; // eax
  int fld_e219; // eax
  int fld_e2192; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *fld_e29; // ecx
  uint8_t v11[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v13; // [esp+20h] [ebp-4h]

  IRDCollisionObject__vmt12C(this, nArg2);
  if ( nArg2 == *(this + 173) )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 33) != 0 )
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 672))(nArg2);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 680))(this, *(uint32_t *)(v4 + 12));
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 680))(this, 0);
    }
  }
  if ( (uint32_t *)nArg2 == this )
  {
    fld_e219 = *(this + 219);
    if ( fld_e219 != 0 )
    {
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_e219 + 12))(0);
      fld_e2192 = *(uint32_t *)*(this + 219);
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v7);
      v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v8);
      (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2192 + 40))(*(this + 219), v9);
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 219) + 92))(*(this + 219), v11);
      fld_e29 = (void *)*(this + 29);
      v13 = 0;
      sub_4600B0(fld_e29, 2, 0, (int)v11);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// ------------------------------------------------------------
// 0x600880 CNRDPassiveObject__vmt10
// ------------------------------------------------------------
// vmt10 thunk → sub_6004B0（PO 数量自适应透明度 tick）。
// attributes: thunk
char /*thiscall*/ CNRDPassiveObject__vmt10(uint8_t *this)
{
  return sub_6004B0(this);
}



// ------------------------------------------------------------
// 0x600890 CNRDPassiveObject__vmt14C
// ------------------------------------------------------------
// PO 每帧主循环槽（vmt14C）：基类位置采样后三件事——
// ① 首帧门（+944）：把 PO 名字串经 vt+212 播出（vt+212 = sub_499110 播音槽，研究 20 P32 音效层链路）——PO 出生配音只播一次；
// ② 生命周期：vt+308 激活检查，宿主组件(+112→+104)未激活则 vt+312(0) 自毁；
// ③ PVP 分支：场景==4 时调 sub_600700 清旗。
int */*thiscall*/ CNRDPassiveObject__vmt14C(int this)
{
  int pThis_398; // eax
  int *result; // eax
  int fld_70; // ecx

  IRDCollisionObject__vmt14C((int *)this);
  if ( *(uint8_t *)(this + 944) == 0 )
  {
    if ( *(uint32_t *)(this + 940) < 0x10u )
      pThis_398 = this + 920;
    else
      pThis_398 = *(uint32_t *)(this + 920);
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, pThis_398, -1, 0, 0);
    *(uint8_t *)(this + 944) = 1;
  }
  result = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    fld_70 = *(uint32_t *)(*(uint32_t *)(this + 112) + 104);
    if ( fld_70 != 0 )
    {
      result = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_70 + 52))(fld_70);
      if ( (uint8_t)result == 0 )
        result = (int *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    }
  }
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
  {
    result = (int *)dword_9A012C;
    if ( dword_9A012C != 0 )
      return sub_600700((void *)this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x600920 sub_600920
// ------------------------------------------------------------
// 表现包序列化（vmt200 的载荷构建器）：清空 vector(+4/+8/+12) 后依次压入 a4..a7 四个 int，
// 再向宿主 a2 取 vt+576/vt+48/vt+52（宿主无效则压 0xFFFF 占位）——生成 PO 攻击命中表现包，
// 由 0x600AF0 在栈上组包后经 vt+560 发送。
int /*stdcall*/ sub_600920(int pArg1, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7)
{
  int v7; // ecx
  unsigned int v8; // edx
  int *nArg42; // eax
  int v10; // edx
  unsigned int v11; // ecx
  int *nArg52; // eax
  int v13; // edx
  unsigned int v14; // ecx
  int *nArg62; // eax
  int v16; // edx
  unsigned int v17; // ecx
  int *nArg72; // eax
  int pObj; // edi

  if ( *(uint32_t *)(pArg1 + 4) != 0 )
    j__free(*(void **)(pArg1 + 4));
  *(uint32_t *)(pArg1 + 4) = 0;
  *(uint32_t *)(pArg1 + 8) = 0;
  *(uint32_t *)(pArg1 + 12) = 0;
  sub_430C80(pArg1, 0, 1u, &nArg3);
  v7 = *(uint32_t *)(pArg1 + 4);
  if ( v7 != 0 )
    v8 = (*(uint32_t *)(pArg1 + 8) - v7) >> 2;
  else
    v8 = 0;
  if ( v7 != 0 && v8 < (*(uint32_t *)(pArg1 + 12) - v7) >> 2 )
  {
    nArg42 = *(int **)(pArg1 + 8);
    *nArg42 = nArg4;
    *(uint32_t *)(pArg1 + 8) = nArg42 + 1;
  }
  else
  {
    sub_430C80(pArg1, *(uint32_t *)(pArg1 + 8), 1u, &nArg4);
  }
  v10 = *(uint32_t *)(pArg1 + 4);
  if ( v10 != 0 )
    v11 = (*(uint32_t *)(pArg1 + 8) - v10) >> 2;
  else
    v11 = 0;
  if ( v10 != 0 && v11 < (*(uint32_t *)(pArg1 + 12) - v10) >> 2 )
  {
    nArg52 = *(int **)(pArg1 + 8);
    *nArg52 = nArg5;
    *(uint32_t *)(pArg1 + 8) = nArg52 + 1;
  }
  else
  {
    sub_430C80(pArg1, *(uint32_t *)(pArg1 + 8), 1u, &nArg5);
  }
  v13 = *(uint32_t *)(pArg1 + 4);
  if ( v13 != 0 )
    v14 = (*(uint32_t *)(pArg1 + 8) - v13) >> 2;
  else
    v14 = 0;
  if ( v13 != 0 && v14 < (*(uint32_t *)(pArg1 + 12) - v13) >> 2 )
  {
    nArg62 = *(int **)(pArg1 + 8);
    *nArg62 = nArg6;
    *(uint32_t *)(pArg1 + 8) = nArg62 + 1;
  }
  else
  {
    sub_430C80(pArg1, *(uint32_t *)(pArg1 + 8), 1u, &nArg6);
  }
  v16 = *(uint32_t *)(pArg1 + 4);
  if ( v16 != 0 )
    v17 = (*(uint32_t *)(pArg1 + 8) - v16) >> 2;
  else
    v17 = 0;
  if ( v16 != 0 && v17 < (*(uint32_t *)(pArg1 + 12) - v16) >> 2 )
  {
    nArg72 = *(int **)(pArg1 + 8);
    *nArg72 = nArg7;
    *(uint32_t *)(pArg1 + 8) = nArg72 + 1;
  }
  else
  {
    sub_430C80(pArg1, *(uint32_t *)(pArg1 + 8), 1u, &nArg7);
  }
  pObj = nArg2;
  if ( nArg2 != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )
      pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);
    nArg4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);
    sub_431230(pArg1, &nArg4);
    nArg4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);
    return sub_431230(pArg1, &nArg4);
  }
  else
  {
    nArg4 = 0xFFFF;
    sub_431230(pArg1, &nArg4);
    nArg4 = 0xFFFF;
    return sub_431230(pArg1, &nArg4);
  }
}



// ------------------------------------------------------------
// 0x600AF0 CNRDPassiveObject__vmt200
// ------------------------------------------------------------
// PO 表现壳槽（vmt200）：门 = +171>0（剩余作用量）且 a4==0 且 vt+308 激活 →
// vt+648（格挡方向查询）→ vt+628 计算实际伤害 v8，与 +170 相减得溢出 v16；
// 用 sub_600920 组表现包 → vt+560 发送（播报层）→ 尾调 IRDCollisionObject__vmt200 基类表现壳。
// 对应研究：docs/90 发现 2 —— vmt200 在 IRDCollisionObject 侧即表现壳 0x4E5DC0 同槽位。
int /*thiscall*/ CNRDPassiveObject__vmt200(int *this, int nArg2, float *pArg3, char pszArg4)
{
  int nArg22; // ebx
  float *pArg32; // edi
  int v7; // edx
  int v8; // eax
  double v9; // st7
  uint8_t v11[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int v13; // [esp+14h] [ebp-20h]
  int v14; // [esp+18h] [ebp-1Ch]
  int v15; // [esp+1Ch] [ebp-18h]
  int fld_e170; // [esp+20h] [ebp-14h]
  int v17; // [esp+24h] [ebp-10h] BYREF
  int v18; // [esp+30h] [ebp-4h]

  nArg22 = nArg2;
  pArg32 = pArg3;
  if ( *(this + 171) > 0 && pszArg4 == 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    v7 = *this;
    HIBYTE(pArg3) = 0;
    nArg2 = 100;
    v17 = 0;
    (*(void (/*thiscall*/ **)(int *, int *, int))(v7 + 648))(this, &nArg2, nArg22);
    v8 = (*(int (/*thiscall*/ **)(int *, char *, int *, int, int, float *, uint32_t))(*this + 628))(
           this,
           (char *)&pArg3 + 3,
           &v17,
           nArg2,
           nArg22,
           pArg32,
           0);
    fld_e170 = *(this + 170) - v8;
    v15 = v8;
    Block = nullptr;
    v13 = 0;
    v14 = 0;
    v9 = pArg32[2];
    v18 = 0;
    sub_600920((int)v11, nArg22, v8, fld_e170, (uint64_t)*pArg32, (uint64_t)pArg32[1], (uint64_t)v9);
    (*(void (/*thiscall*/ **)(int *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 1, v11, 0, 0);
    v18 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v13 = 0;
    v14 = 0;
  }
  return IRDCollisionObject__vmt200(this, nArg22, (int)pArg32, pszArg4);
}



// ------------------------------------------------------------
// 0x600C20 sub_600C20
// ------------------------------------------------------------
// ★★ PO 生成工厂主体（按文件名）：从 dword_8F84C8（PO 定义档案管理器）取记录，缺失即打
// 「PASSIVEOBJECT CREATE FAIL! FILENAME[%s]」——0x60 区字符串证据的本体。
// 流程：① 搬运定义块（+72 名字串、+79..81 三坐标、+27、+172/+174）与 sub_4ED3F0 批量字段；
// ② sub_40BF00（std::string 比较，哨兵 szPassword=P32 同款历史遗留空串分支）命中则 sub_431920 挂主动画（资源号 228 门）；
// ③ 遍历动画列表逐条 strcmp 哨兵 → sub_42AC90 vector 推入；
// ④ vt+34 已有动画时 sub_4924C0/sub_4918E0 取第 2 号动画盒（P37-2 obj+60 边界族）；
// ⑤ 「%s%s」拼接 dword_8F84E0 路径根 + 子路径 → sub_4B2970 攻击上下文拷贝（P29 定案），空哨兵条目用 sub_4A3450 默认 attackinfo 填充；
// ⑥ +86/+177 批量字段；⑦ v5[34] 时 operator new(0x12C=300B) → sub_4C3640 生成伴随动画对象存 +219；
// ⑧ vt+472 初始化 + dword_8F8520 vt+120 取宿主 → 逐条 vt+464 触发。
// 是本文件所有 PO 子类生成的总入口。
unsigned int /*thiscall*/ sub_600C20(size_t *this, const char *pArg2, size_t uArg3)
{
  size_t *pThis; // esi
  int v4; // eax
  size_t *v5; // ebx
  unsigned int result; // eax
  size_t v7; // edi
  int v8; // eax
  size_t v9; // edx
  unsigned int **v10; // ecx
  size_t v11; // edi
  char v12; // al
  int v13; // eax
  size_t v14; // esi
  uint32_t *v15; // ecx
  unsigned int v16; // edi
  int *v17; // edx
  size_t v18; // esi
  unsigned int v19; // edx
  uint32_t *v20; // eax
  int *v21; // ecx
  int *v22; // eax
  uint32_t *v23; // edi
  uint32_t *v24; // ecx
  int v25; // eax
  unsigned int **v26; // ecx
  int v27; // esi
  int v28; // edi
  const CHAR *v29; // eax
  int v30; // eax
  void *pMem; // eax
  int v32; // ebx
  int v33; // eax
  unsigned int i; // edi
  size_t v35; // ecx
  uint32_t v36[23]; // [esp+Ch] [ebp-A8h] BYREF
  void *Block; // [esp+6Ch] [ebp-48h]
  int v38; // [esp+7Ch] [ebp-38h]
  unsigned int v39; // [esp+80h] [ebp-34h]
  size_t *pThis2; // [esp+A4h] [ebp-10h]
  int v41; // [esp+B0h] [ebp-4h]
  unsigned int **v42; // [esp+BCh] [ebp+8h]
  unsigned int **v43; // [esp+BCh] [ebp+8h]

  pThis = this;
  v4 = *(uint32_t *)dword_8F84C8;
  pThis2 = this;
  v5 = (size_t *)(*(int (/*thiscall*/ **)(int, const char *))(v4 + 4))(dword_8F84C8, pArg2);
  if ( v5 == nullptr )
    return off_77F3FC("PASSIVEOBJECT CREATE FAIL! FILENAME[%s]", pArg2);
  sub_4014D0(pThis + 90, v5 + 55, 0, 0xFFFFFFFF);
  pThis[176] = uArg3;
  pThis[71] = *v5;
  sub_4014D0(pThis + 72, v5 + 1, 0, 0xFFFFFFFF);
  pThis[79] = v5[8];
  pThis[80] = v5[9];
  pThis[81] = v5[10];
  pThis[27] = v5[11];
  pThis[172] = v5[12];
  pThis[174] = v5[13];
  sub_4ED3F0((int)(pThis + 82), (int)(v5 + 14));
  if ( sub_40BF00((std::_String_base *)(v5 + 18), 0, v5[23], szPassword, 0) != 0 )
  {
    v41 = 0;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( v5[24] < 0x10 )
        LOBYTE(v7) = (uint8_t)v5 + 76;
      else
        v7 = v5[19];
      if ( v5[61] < 0x10 )
        v8 = sub_431920((uint8_t)v5 - 32, v7, 1);
      else
        v8 = sub_431920(v5[56], v7, 1);
    }
    else
    {
      v8 = 0;
    }
    v9 = *pThis;
    v41 = -1;
    (*(void (/*thiscall*/ **)(size_t *, int))(v9 + 92))(pThis, v8);
  }
  v10 = (unsigned int **)v5[26];
  v42 = v10;
  if ( v10 != (unsigned int **)v5[27] )
  {
    while ( 1 )
    {
      if ( strcmp(sub_41ACF0(v10), szPassword) == 0 )
      {
        v18 = pThis2[36];
        v15 = pThis2 + 35;
        uArg3 = 0;
        if ( v18 != 0 )
          v19 = (int)(pThis2[37] - v18) >> 2;
        else
          v19 = 0;
        if ( v18 != 0 && v19 < (int)(pThis2[38] - v18) >> 2 )
        {
          v20 = (uint32_t *)pThis2[37];
          *v20 = 0;
          v15[2] = v20 + 1;
          goto LABEL_37;
        }
      }
      else
      {
        uArg3 = sub_42FCB0(228);
        v41 = 1;
        if ( uArg3 != 0 )
        {
          if ( v5[61] < 0x10 )
            LOBYTE(v11) = (uint8_t)v5 - 32;
          else
            v11 = v5[56];
          v12 = (uint8_t)sub_41ACF0(v42);
          v13 = sub_431920(v11, v12, 1);
        }
        else
        {
          v13 = 0;
        }
        v14 = pThis2[36];
        v15 = pThis2 + 35;
        v41 = -1;
        uArg3 = v13;
        if ( v14 != 0 )
          v16 = (int)(pThis2[37] - v14) >> 2;
        else
          v16 = 0;
        if ( v14 != 0 && v16 < (int)(pThis2[38] - v14) >> 2 )
        {
          v17 = (int *)pThis2[37];
          *v17 = v13;
          v15[2] = v17 + 1;
          goto LABEL_37;
        }
      }
      sub_42AC90((void *)v15[2], 1, (int)&uArg3);
LABEL_37:
      if ( ++v42 == (unsigned int **)v5[27] )
      {
        pThis = pThis2;
        break;
      }
      v10 = v42;
    }
  }
  v21 = (int *)pThis[34];
  if ( v21 != nullptr )
  {
    v22 = (int *)sub_4924C0(v21, 0);
    pThis[40] = sub_4918E0(v22, 2);
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 36), 0, v5[41], szPassword, 0) != 0 )
  {
    if ( v5[42] < 0x10 )
      v23 = v5 + 37;
    else
      v23 = (uint32_t *)v5[37];
    if ( v5[61] < 0x10 )
      v24 = v5 + 56;
    else
      v24 = (uint32_t *)v5[56];
    v25 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E0 + 12))(dword_8F84E0, "%s%s", v24, v23);
    sub_4B2970(pThis + 181, v25);
  }
  v26 = (unsigned int **)v5[44];
  v43 = v26;
  if ( v26 != (unsigned int **)v5[45] )
  {
    while ( 1 )
    {
      if ( strcmp(sub_41ACF0(v26), szPassword) == 0 )
      {
        v39 = 15;
        v38 = 0;
        LOBYTE(Block) = 0;
        v41 = 2;
        sub_4A3450(v36);
        v41 = 3;
        sub_4B52F0((int)(pThis2 + 138), (int)v36);
        v41 = -1;
        if ( v39 >= 0x10 )
          j__free(Block);
        v39 = 15;
        v38 = 0;
        LOBYTE(Block) = 0;
      }
      else
      {
        v27 = v5[61] < 0x10 ? (int)(v5 + 56) : v5[56];
        v28 = *(uint32_t *)dword_8F84E0;
        v29 = sub_41ACF0(v43);
        v30 = (*(int (**)(int, const char *, ...))(v28 + 12))(dword_8F84E0, "%s%s", v27, v29);
        sub_4B52F0((int)(pThis2 + 138), v30);
      }
      if ( ++v43 == (unsigned int **)v5[45] )
        break;
      v26 = v43;
    }
    pThis = pThis2;
  }
  sub_4ED3F0((int)(pThis + 86), (int)(v5 + 47));
  sub_41DC80((int)(pThis + 177), (int)(v5 + 51));
  if ( v5[34] != 0 )
  {
    pThis = pThis2;
    pMem = operator new(0x12Cu);
    v41 = 4;
    if ( pMem != nullptr )
    {
      if ( v5[35] < 0x10 )
        v32 = (int)(v5 + 30);
      else
        v32 = v5[30];
      if ( pThis[96] < 0x10 )
        v33 = sub_4C3640((int)pMem, (int)(pThis + 91), v32, (int)pThis);
      else
        v33 = sub_4C3640((int)pMem, pThis[91], v32, (int)pThis);
    }
    else
    {
      v33 = 0;
    }
    v41 = -1;
    pThis[219] = v33;
  }
  (*(void (/*thiscall*/ **)(size_t *, uint32_t, uint32_t, int, int))(*pThis + 472))(pThis, 0, 0, 1, 1);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    pThis[220] = *(uint32_t *)(*(uint32_t *)(result + 108) + 112);
  }
  else
  {
    result = off_77F3FC((char *)&byte_73ABD4);
  }
  for ( i = 0; ; ++i )
  {
    v35 = pThis[83];
    if ( v35 == 0 )
      break;
    result = (int)(pThis[84] - v35) >> 2;
    if ( i >= result )
      break;
    result = (*(int (/*thiscall*/ **)(size_t *, uint32_t))(*pThis + 464))(pThis, *(uint32_t *)(v35 + 4 * i));
  }
  return result;
}


// ------------------------------------------------------------
// 0x6011B0 sub_6011B0
// ------------------------------------------------------------
// PO 生成工厂（按索引）：查 dword_9B7C48 map（sub_442D00），未命中或名字为空即打
// 「PASSIVEOBJECT CREATE FAIL! INDEX %d」→ 转调 sub_600C20 按文件名生成。与 0x600C20 构成两条工厂路径。
unsigned int /*thiscall*/ sub_6011B0(uint32_t *this, int ArgList, int nArg3)
{
  int v3; // edi
  const char *v5; // eax
  int *v7; // [esp+8h] [ebp-4h] BYREF

  v3 = ArgList;
  sub_442D00(&dword_9B7C48, &v7, &ArgList);
  if ( v7 == (int *)dword_9B7C4C )
    return off_77F3FC("PASSIVEOBJECT CREATE FAIL! INDEX %d", v3);
  v5 = (unsigned int)v7[10] < 0x10 ? (const char *)(v7 + 5) : (const char *)v7[5];
  if ( v5 == nullptr )
    return off_77F3FC("PASSIVEOBJECT CREATE FAIL! INDEX %d", v3);
  else
    return sub_600C20(this, v5, nArg3);
}



// ------------------------------------------------------------
// 0x601220 sub_601220
// ------------------------------------------------------------
// 16 字节/条记录 vector 的中间插入（std::vector::insert 手工展开）：容量翻倍策略（(old>>1)+old），
// 容量上限 0xFFFFFFF 溢出保护 → sub_4F34F0 抛长异常；元素搬移 sub_602460、尾段构造 sub_504650、记录构造 sub_453C20/sub_4BF320（equ_buff 记录族）。
// 供 PO 定义表/附加器记录表复用。
unsigned int /*thiscall*/ sub_601220(int this, int pArg2, unsigned int uArg3, uint32_t *Block)
{
  int v5; // edx
  int v6; // ecx
  int fld_4; // edx
  unsigned int result; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v12; // eax
  int fld_87; // ecx
  int fld_88; // eax
  int v15; // ebx
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v18; // edi
  char *fld_83; // eax
  int fld_86; // edi
  char *v21; // edi
  int fld_42; // [esp-18h] [ebp-44h]
  int fld_85; // [esp-Ch] [ebp-38h]
  unsigned int fld_84; // [esp-8h] [ebp-34h]
  int v25; // [esp+0h] [ebp-2Ch] BYREF
  uint32_t v26[5]; // [esp+Ch] [ebp-20h] BYREF
  int v27; // [esp+28h] [ebp-4h]
  int v28; // [esp+38h] [ebp+Ch]
  char *Blocka; // [esp+3Ch] [ebp+10h]
  void *Blockb; // [esp+3Ch] [ebp+10h]

  v5 = Block[1];
  v26[0] = *Block;
  v6 = Block[2];
  v26[1] = v5;
  v26[3] = Block[3];
  fld_4 = *(uint32_t *)(this + 4);
  v26[4] = &v25;
  v26[2] = v6;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 4;
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
    else
      fld_8 = 0;
    if ( 0xFFFFFFF - fld_8 < uArg3 )
      sub_4F34F0(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(char **)(this + 8);
      Blockb = fld_83;
      if ( (int)&fld_83[-pArg2] >> 4 >= uArg3 )
      {
        v21 = &fld_83[-16 * uArg3];
        *(uint32_t *)(this + 8) = sub_602460(v21, fld_83, fld_83);
        sub_4BF320(pArg2, v21, Blockb);
        return sub_453C20(pArg2, pArg2 + 16 * uArg3, v26);
      }
      else
      {
        sub_602460(pArg2, fld_83, pArg2 + 16 * uArg3);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 4);
        fld_85 = *(uint32_t *)(this + 8);
        v27 = 2;
        sub_504650(fld_85, fld_84, v26);
        fld_86 = 16 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        return sub_453C20(pArg2, fld_86 - 16 * uArg3, v26);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (result >> 1) >= result )
        v12 = (result >> 1) + result;
      else
        v12 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
      else
        fld_87 = 0;
      if ( v12 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
        else
          fld_88 = 0;
        v12 = uArg3 + fld_88;
      }
      v28 = 16 * v12;
      Blocka = (char *)operator new(16 * v12);
      fld_42 = *(uint32_t *)(this + 4);
      v27 = 0;
      v15 = sub_602460(fld_42, pArg2, Blocka);
      sub_4BF340(v15, uArg3, v26);
      sub_602460(pArg2, *(uint32_t *)(this + 8), 16 * uArg3 + v15);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 4;
      else
        fld_89 = 0;
      v18 = fld_89 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &Blocka[v28];
      *(uint32_t *)(this + 8) = &Blocka[16 * v18];
      *(uint32_t *)(this + 4) = Blocka;
      return (unsigned int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x601480 sub_601480
// ------------------------------------------------------------
// 记录 vector 尾部追加：未满时原地 sub_4BF340 构造 +16B 推进，满则转 sub_601220 扩容插入（被 0x6014F0 的 [skill info] 循环调用）。
unsigned int /*thiscall*/ sub_601480(int this, uint32_t *Block)
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi
  unsigned int result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) >> 4 )
    return sub_601220(this, *(char **)(this + 8), 1u, Block);
  fld_82 = *(uint32_t *)(this + 8);
  result = sub_4BF340(fld_82, 1, Block);
  *(uint32_t *)(this + 8) = fld_82 + 16;
  return result;
}



// ------------------------------------------------------------
// 0x6014F0 sub_6014F0
// ------------------------------------------------------------
// ★★ 精炼炉（cube）脚本解析器 —— 0x60 区 [cube index]/[legacy info]/[skill info]/[skill prob]/[cube creation const]
// 字符串证据的唯一定义点。逐标签解析：
// · [cube index]：16 组×16B 记录表重建（free + 重挂，sub_443370 逐词读取）；
// · [legacy info]：v10 组号（0..4）→ sub_4F6540 定位 +9*5+15 槽，随后 int 向量入组；
// · [skill info]：重置 +168 向量与 +160 计数，循环读「字符串/int/int/字符串」四元组经 sub_601480 入库（技能→成品映射表）；
// · [skill prob]：+180/+184 两个 float（技能触发概率对）；
// · [cube creation const]：+188 int + 4×float（生成常数）；
// · [additional result]：4 组（int 计数 + int 向量）于 +272 起每 20B；
// · [additional result const]：4 组（float 权重 + int×2）于 +208 起，权重 0 时整组清零；
// 未知标签打「SCRIPT TAG ERROR! [%s] %s」。
// 语义对应：副本精炼/分解炉的『输入 cube → 按概率产出附加结果』配置表【推断：方块精炼产物概率表】。
char /*cdecl*/ sub_6014F0(int nArg1, const char *ArgList)  // 【精炼炉 cube 脚本解析器（[cube index]/[legacy info]/…】
{
  char result; // al
  int nArg12; // ebx
  void **v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // ebx
  unsigned int v8; // edx
  int *v9; // ecx
  int v10; // edi
  int v11; // eax
  char *v12; // esi
  void **v13; // eax
  int v14; // eax
  void **v15; // eax
  float *v16; // esi
  int i; // ebx
  int v18; // esi
  int j; // edi
  int *v20; // esi
  float *v21; // ebx
  int k; // edi
  double v23; // st7
  int v24; // eax
  const char *v25; // eax
  void *v26[3]; // [esp-1Ch] [ebp-9Ch] BYREF
  char *v27; // [esp-10h] [ebp-90h]
  int v28; // [esp-Ch] [ebp-8Ch]
  char *v29; // [esp-8h] [ebp-88h]
  char *v30; // [esp-4h] [ebp-84h]
  int v31; // [esp+Ch] [ebp-74h] BYREF
  int v32; // [esp+10h] [ebp-70h]
  int v33; // [esp+14h] [ebp-6Ch]
  int v34; // [esp+18h] [ebp-68h]
  void **v35; // [esp+1Ch] [ebp-64h] BYREF
  uint8_t v36[4]; // [esp+20h] [ebp-60h] BYREF
  void *Block; // [esp+24h] [ebp-5Ch]
  void *Src; // [esp+28h] [ebp-58h]
  int v39; // [esp+2Ch] [ebp-54h]
  int v40; // [esp+30h] [ebp-50h] BYREF
  char v41; // [esp+37h] [ebp-49h] BYREF
  char v42; // [esp+38h] [ebp-48h] BYREF
  void *v43[4]; // [esp+3Ch] [ebp-44h] BYREF
  int v44; // [esp+4Ch] [ebp-34h]
  unsigned int v45; // [esp+50h] [ebp-30h]
  int v46; // [esp+54h] [ebp-2Ch] BYREF
  void *v47; // [esp+58h] [ebp-28h] BYREF
  int v48; // [esp+68h] [ebp-18h]
  unsigned int v49; // [esp+6Ch] [ebp-14h]
  int dword_796E502; // [esp+70h] [ebp-10h]
  int v51; // [esp+7Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10((char)szPassword, (int)ArgList);
  if ( result != 0 )
  {
    nArg12 = nArg1;
    sub_4F3560(nArg1);
    v49 = 15;
    v48 = 0;
    LOBYTE(v47) = 0;
    v51 = 1;
    v45 = 15;
    v44 = 0;
    LOBYTE(v43[0]) = 0;
    v41 = 0;
    while ( (uint8_t)sub_443430(&v46) != 0 )
    {
      sub_442B20(&v46);
      if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[cube index]", 0xCu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[legacy info]", 0xDu) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[skill info]", 0xCu) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[skill prob]", 0xCu) != 0 )
            {
              if ( (uint8_t)sub_423300(&v46, "[cube creation const]") != 0 )
              {
                *(uint32_t *)(nArg12 + 188) = sub_4423D0(nullptr);
                v16 = (float *)(nArg12 + 192);
                for ( i = 4; i != 0; --i )
                  *v16++ = sub_442480(nullptr);
                nArg12 = nArg1;
              }
              else if ( (uint8_t)sub_423300(&v46, "[additional result]") != 0 )
              {
                v40 = 0;
                v18 = nArg12 + 272;
                do
                {
                  *(uint32_t *)v18 = sub_4423D0(&v41);
                  if ( v41 == 0 )
                    break;
                  sub_5E5260((void **)(v18 + 4));
                  for ( j = 0; j < *(uint32_t *)v18; ++j )
                  {
                    v35 = (void **)sub_4423D0(nullptr);
                    sub_431230(v18 + 4, &v35);
                  }
                  nArg12 = nArg1;
                  v18 += 20;
                  ++v40;
                }
                while ( v40 < 4 );
              }
              else if ( (uint8_t)sub_423300(&v46, "[additional result const]") != 0 )
              {
                v20 = (int *)(nArg12 + 232);
                v21 = (float *)(nArg12 + 208);
                for ( k = 4; k != 0; --k )
                {
                  v23 = sub_442480(nullptr);
                  *v21 = v23;
                  if ( v23 == 0.0 )
                  {
                    *(v20 - 1) = 0;
                    *v20 = 0;
                  }
                  else
                  {
                    v24 = sub_4423D0(nullptr);
                    v29 = nullptr;
                    *(v20 - 1) = v24;
                    *v20 = sub_4423D0(v29);
                  }
                  ++v21;
                  v20 += 3;
                }
                nArg12 = nArg1;
              }
              else
              {
                v35 = v26;
                sub_401690(&v46);
                if ( (uint8_t)sub_442C80((char)v26[0], v26[1], (int)v26[2], (int)v27, v28, (int)v29, (int)v30) == 0 )
                {
                  v25 = (const char *)v47;
                  if ( v49 < 0x10 )
                    v25 = (const char *)&v47;
                  off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, v25);
                }
              }
            }
            else
            {
              *(float *)(nArg12 + 180) = sub_442480(nullptr);
              *(float *)(nArg12 + 184) = sub_442480(nullptr);
            }
          }
          else
          {
            if ( *(uint32_t *)(nArg12 + 168) != 0 )
              j__free(*(void **)(nArg12 + 168));
            v30 = nullptr;
            *(uint32_t *)(nArg12 + 168) = 0;
            *(uint32_t *)(nArg12 + 172) = 0;
            *(uint32_t *)(nArg12 + 176) = 0;
            *(uint32_t *)(nArg12 + 160) = sub_4423D0(v30);
            v31 = 4;
            v34 = 4;
            v29 = &v42;
            v32 = 0;
            v33 = 0;
            if ( sub_443370() != 0 )
            {
              do
              {
                v13 = (void **)v43[0];
                if ( v45 < 0x10 )
                  v13 = v43;
                v31 = sub_4426A0(v13);  // 【职业标签→索引（[swordman]/[fighter]/[gunner]/[mag…】
                v32 = sub_4423D0(nullptr);
                v14 = sub_4423D0(nullptr);
                v27 = &v42;
                v33 = v14;
                sub_443370();
                v15 = (void **)v43[0];
                if ( v45 < 0x10 )
                  v15 = v43;
                v34 = sub_442710(v15);  // 【元素标签→索引（[fire/water/dark/light element]）】
                sub_601480(&v31);
                v30 = &v42;
              }
              while ( sub_443370() != 0 );
              nArg12 = nArg1;
            }
          }
        }
        else
        {
          v10 = sub_4423D0(nullptr);
          Block = nullptr;
          Src = nullptr;
          v39 = 0;
          LOBYTE(v51) = 2;
          v11 = sub_4423D0(&v41);
          v40 = v11;
          if ( v41 != 0 )
          {
            do
            {
              v12 = (char *)Src;
              if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v39 - (int)Block) >> 2) )
              {
                *(uint32_t *)Src = v11;
                Src = v12 + 4;
              }
              else
              {
                sub_430C80(Src, 1, (int)&v40);
              }
              v11 = sub_4423D0(&v41);
              v40 = v11;
            }
            while ( v41 != 0 );
            nArg12 = nArg1;
          }
          if ( v10 - 1 < 4 )
            sub_4F6540(nArg12 + 4 * (5 * v10 + 15), v36);
          LOBYTE(v51) = 1;
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          Src = nullptr;
          v39 = 0;
        }
      }
      else
      {
        v30 = &v42;
        sub_443370();
        v4 = (void **)v43[0];
        if ( v45 < 0x10 )
          v4 = v43;
        v5 = 16 * sub_442710(v4) + nArg12;  // 【元素标签→索引（[fire/water/dark/light element]）】
        if ( *(uint32_t *)(v5 + 4) != 0 )
          j__free(*(void **)(v5 + 4));
        v30 = &v41;
        *(uint32_t *)(v5 + 4) = 0;
        *(uint32_t *)(v5 + 8) = 0;
        *(uint32_t *)(v5 + 12) = 0;
        v6 = sub_4423D0(v30);
        v40 = v6;
        if ( v41 != 0 )
        {
          do
          {
            v7 = *(uint32_t *)(v5 + 4);
            if ( v7 != 0 )
              v8 = (*(uint32_t *)(v5 + 8) - v7) >> 2;
            else
              v8 = 0;
            if ( v7 != 0 && v8 < (*(uint32_t *)(v5 + 12) - v7) >> 2 )
            {
              v9 = *(int **)(v5 + 8);
              *v9 = v6;
              *(uint32_t *)(v5 + 8) = v9 + 1;
            }
            else
            {
              sub_430C80(*(void **)(v5 + 8), 1, (int)&v40);
            }
            v6 = sub_4423D0(&v41);
            v40 = v6;
          }
          while ( v41 != 0 );
          nArg12 = nArg1;
        }
      }
    }
    if ( v45 >= 0x10 )
      j__free(v43[0]);
    v45 = 15;
    v44 = 0;
    LOBYTE(v43[0]) = 0;
    if ( v49 >= 0x10 )
      j__free(v47);
    return 1;
  }
  return result;
}


// ============================================================
// 【分区 2】掉落/搬运 PO 与 MP 恢复（0x601A50-0x602380）
// CNStorageBird（搬运鸟）/ CNFallingStorage（落宝箱）/ CNStorageSub / CNChangeMp（MP 恢复精灵）
// 协议证据：动作包 51201（0x601E40）—— PO 专有包号
// ============================================================
// ------------------------------------------------------------
// 0x601A50 sub_601A50
// ------------------------------------------------------------
void /*thiscall*/ sub_601A50(uint32_t *this)
{
  *(this + 243) = 0;
  *(this + 244) = 0xFFFF;
}



// ------------------------------------------------------------
// 0x601A70 CNStorageBird__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNStorageBird__vmtC(int this)
{
  int fld_70; // edi
  int v3; // eax
  int result; // eax

  CNRDPassiveObject__vmtC((int *)this);
  fld_70 = *(uint32_t *)(this + 112);
  v3 = *(uint32_t *)this;
  *(uint32_t *)(this + 972) = 1;
  result = -(*(int (/*thiscall*/ **)(int, uint32_t))(v3 + 384))(this, 0);
  *(uint32_t *)(fld_70 + 36) = result;
  *(uint32_t *)(*(uint32_t *)(this + 112) + 112) = 2;
  *(uint8_t *)(this + 700) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x601AB0 sub_601AB0
// ------------------------------------------------------------
char /*thiscall*/ sub_601AB0(uint8_t *this)
{
  int pThis_80; // eax

  pThis_80 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
  if ( pThis_80 >= 900 )
  {
    LOBYTE(pThis_80) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( (uint8_t)pThis_80 != 0 )
    {
      LOBYTE(pThis_80) = *(this + 264);
      if ( (uint8_t)pThis_80 == 0 )
        LOBYTE(pThis_80) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    }
  }
  return pThis_80;
}



// ------------------------------------------------------------
// 0x601AF0 CNFallingStorage__vmt138
// ------------------------------------------------------------
char /*thiscall*/ CNFallingStorage__vmt138(char *this, int nArg2)
{
  return CNRDObject__vmt138(this, 1);
}



// ------------------------------------------------------------
// 0x601B00 sub_601B00
// ------------------------------------------------------------
char /*thiscall*/ sub_601B00(uint8_t *this)
{
  int pThis_C8; // eax

  pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( *(uint8_t *)(pThis_C8 + 170) != 0 )
  {
    pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 684))(this);
    if ( pThis_C8 == dword_8F7C04 )
    {
      LOBYTE(pThis_C8) = *(this + 264);
      if ( (uint8_t)pThis_C8 == 0 )
        LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 312))(this, 1);
    }
  }
  return pThis_C8;
}



// ------------------------------------------------------------
// 0x601B40 CNFallingStorage__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNFallingStorage__vmt12C(uint32_t *this, int nArg2)
{
  if ( (uint32_t *)nArg2 == this )
    dword_9B7C88 = 0;
  CNRDPassiveObject__vmt12C(this, nArg2);
}



// ------------------------------------------------------------
// 0x601B60 sub_601B60
// ------------------------------------------------------------
int /*thiscall*/ sub_601B60(uint32_t *this, int nArg2)
{
  *(this + 245) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x601B70 sub_601B70
// ------------------------------------------------------------
char /*thiscall*/ sub_601B70(void *this, int nArg2)
{
  int *pThis_24; // ecx

  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    -100,
    *(uint32_t *)(*((uint32_t *)this + 36) + 4),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    -200,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  pThis_24 = *((int **)this + 36);
  *((uint32_t *)this + 245) = nArg2;
  sub_493400(*pThis_24, nArg2);
  return sub_4939E0(**((uint32_t **)this + 36), 1);
}



// ------------------------------------------------------------
// 0x601BE0 sub_601BE0
// ------------------------------------------------------------
char /*thiscall*/ sub_601BE0(uint32_t **this, uint32_t *uArg2)
{
  uint32_t *v3; // edx
  int v4; // eax
  int v5; // eax

  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(this, 100, **(this + 36), 0, 0, 0);
  v3 = *this;
  *(this + 244) = uArg2;
  v4 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t *))v3[50])(this, uArg2);
  sub_493400(v4, 0);
  v5 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[50])(this);
  return sub_4939E0(v5, 1);
}



// ------------------------------------------------------------
// 0x601C40 sub_601C40
// ------------------------------------------------------------
// 掉落物着陆（Storage 系状态 1→2）：x<=0 触地时设 z（vt+112）、绑定动画（vt+208）、vt+204 以 100ms 弹跳、+243 状态=2；
// 宿主为本地玩家（dword_8F7C04）时记 dword_9B7C88 全局并 sub_44E8D0(dword_8F8528, 0xF,...) UI 通知【推断：拾取提示】；
// 激活则 sub_4E4A50 发动作包（研究：vmt248 动作数据包序列化器）。
int /*thiscall*/ sub_601C40(uint32_t *this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int fld_e28; // ecx
  int v7; // eax
  int v8; // [esp-24h] [ebp-28h]
  int fld_e244; // [esp-1Ch] [ebp-20h]
  int v10; // [esp-18h] [ebp-1Ch]
  int v11; // [esp-14h] [ebp-18h]
  int v12; // [esp-Ch] [ebp-10h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  if ( result <= 0 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v4);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v3 + 112))(this, v5);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 36));
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 36) + 4),
      0,
      0,
      0,
      0);
    fld_e28 = *(this + 28);
    *(this + 243) = 2;
    *(uint32_t *)(fld_e28 + 36) = 0;
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) == dword_8F7C04 )
    {
      dword_9B7C88 = (int)this;
      sub_44E8D0((char *)dword_8F8528, (void *)0xF, 0, 0);
    }
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 152))(this, 0);
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      fld_e244 = *(this + 244);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
      return sub_4E4A50(v7, v8, 2, fld_e244, v10, v11, 0, v12, 0, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x601D40 sub_601D40
// ------------------------------------------------------------
int /*thiscall*/ sub_601D40(int *this)
{
  int result; // eax
  int v3; // ecx

  result = *(this + 36);
  *(this + 243) = 3;
  v3 = *(uint32_t *)(result + 8);
  if ( v3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 196))(this, v3);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 4));
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
             this,
             100,
             *(uint32_t *)(*(this + 36) + 12),
             0,
             0,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x601DA0 CNStorageSub__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNStorageSub__vmtC(int *this)
{
  int result; // eax

  CNRDPassiveObject__vmtC(this);
  switch ( *(this + 245) )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
      break;
    case 1:
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 152);
      break;
    case 2:
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 304);
      break;
    case 3:
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 456);
      break;
    default:
      result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, 0);
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x601E40 sub_601E40
// ------------------------------------------------------------
// 搬运鸟装载检查：载量 vt+128 < 容量 vt+384(1) 时着地（vt+112）、+243=2、计算 10×vt+384(0) 存宿主+36；
// 本地玩家则发 51201 号包（sub_4E4A50，包号直证 PO 专有协议），否则两次 vt+208 绑定动画。【推断：金币/物品搬运鸟的装载演出】
int /*thiscall*/ sub_601E40(uint32_t *this)
{
  int v2; // edi
  int result; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int fld_e28; // edi
  int v9; // eax
  int v10; // eax
  int fld_e245; // [esp-20h] [ebp-28h]
  int v12; // [esp-1Ch] [ebp-24h]
  int v13; // [esp-18h] [ebp-20h]
  int v14; // [esp-14h] [ebp-1Ch]
  int v15; // [esp-Ch] [ebp-14h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  if ( result < v2 )
  {
    v4 = *this;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v5);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v6);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 112))(this, v7);
    fld_e28 = *(this + 28);
    v9 = *this;
    *(this + 243) = 2;
    *(uint32_t *)(fld_e28 + 36) = 10 * (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v9 + 384))(this, 0);
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) == dword_8F7C04 )
    {
      v15 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 152))(this, 0);
      v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this) - 79;
      v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      fld_e245 = *(this + 245);
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
      result = sub_4E4A50(v10, 51201, fld_e245, v12, v13, v14, 1, v15, 0, 0);
      *(this + 244) = result;
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 4));
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 36));
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x601F40 CNStorageBird__vmt128
// ------------------------------------------------------------
int /*thiscall*/ CNStorageBird__vmt128(uint32_t *this, int nArg2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 33);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2);
    if ( result == *(this + 244) )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 4));
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 36));
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x601FA0 CNFallingStorage__vmt10
// ------------------------------------------------------------
// 落宝箱每帧 tick（vmt10）：基类调用后按 +243 状态机调 sub_601B00（玩家接近判定）与 sub_601C40（着陆）。
int /*thiscall*/ CNFallingStorage__vmt10(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax

  CNRDPassiveObject__vmt10(this);
  result = *(this + 243);
  if ( result != 0 )
  {
    v3 = result - 1;
    if ( v3 != 0 )
    {
      if ( v3 == 2 )
        sub_601B00(this);
    }
    else
    {
      sub_601C40(this);
    }
    result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    if ( result <= 0 )
    {
      v4 = *this;
      v5 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
      v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);
      return (*(int (/*thiscall*/ **)(int *, int))(v4 + 112))(this, v6);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602000 CNStorageBird__vmt10
// ------------------------------------------------------------
// 搬运鸟每帧 tick（vmt10）：基类调用后按 +243 状态机调 sub_601AB0（超时自毁）与 sub_601E40（装载检查）。
int /*thiscall*/ CNStorageBird__vmt10(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // edi
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax

  CNRDPassiveObject__vmt10(this);
  result = *(this + 243);
  if ( result != 0 )
  {
    v3 = result - 1;
    if ( v3 != 0 )
    {
      if ( v3 == 1 )
        sub_601AB0(this);
    }
    else
    {
      sub_601E40(this);
    }
    v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);
    result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    if ( result < v4 )
    {
      v5 = *this;
      v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);
      v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v7);
      return (*(int (/*thiscall*/ **)(int *, int))(v5 + 112))(this, v8);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602070 sub_602070
// ------------------------------------------------------------
int /*thiscall*/ sub_602070(int this)
{
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint8_t *)(this + 96) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x602090 CNChangeMp__vmt1C
// ------------------------------------------------------------
// MP 恢复 PO 周期槽（vmt1C）：sub_496010 周期检查到点 → sub_4D7960 飘出恢复数字（飘字咽喉，§1.1）。
// 对应资源：Common/CommonEffect/Animation/MpUp.ani（出生动画，在 0x602380 构造群）+ MP_RECOVERED 音效 TAG（0x602200）。
int /*thiscall*/ CNChangeMp__vmt1C(uint32_t *this)
{
  int fld_e1; // ecx
  int fld_e12; // eax
  int fld_e13; // edi
  int v5; // ebx
  int v6; // eax
  int result; // eax
  int v8; // eax
  int v9; // eax
  int fld_e14; // ecx
  int v11; // eax
  int v12; // [esp+4h] [ebp-8h]
  int fld_e122; // [esp+8h] [ebp-4h]

  fld_e1 = *(this + 1);
  *(this + 22) = 0;
  if ( fld_e1 != 0 && (*(uint32_t *)(dword_8F7A24 + 12) != 4 || fld_e1 == dword_8F7C04) )
  {
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 120))(fld_e1);
    fld_e12 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 124))(*(this + 1));
    fld_e13 = *(this + 1);
    fld_e122 = fld_e12;
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 192))(fld_e13);
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 128))(fld_e13);
    sub_4D7960(v6 + v5, fld_e13, (int)this, v12, fld_e122, v6 + v5, *(this + 20), 3, 0, 0);  // 【飘字咽喉（§1.1 case 0x14；第 14/39 轮 5 层精灵）】
  }
  *((uint8_t *)this + 96) = 0;
  result = *(uint32_t *)(dword_8F7A24 + 12);
  if ( result == 4 || result == 6 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 64))(this);
    v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v8 + 32) + 576))(*(uint32_t *)(v8 + 32));
    result = __RTDynamicCast(v9, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
    if ( result == dword_8F7C04 )
    {
      fld_e14 = *(this + 1);
      if ( fld_e14 != dword_8F7C04 )
      {
        result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e14 + 40))(fld_e14, 273);
        if ( (uint8_t)result != 0 )
        {
          v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
          return sub_496010((int)dword_99FD58, v11, 11, 1);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602190 CNChangeMp__vmt54
// ------------------------------------------------------------
char /*thiscall*/ CNChangeMp__vmt54(int this, char pszArg2)
{
  char result; // al
  int fld_5C; // ecx

  result = IRDAppendage__vmt54((uint8_t *)this, pszArg2);
  fld_5C = *(uint32_t *)(this + 92);
  if ( fld_5C != 0 )
    return sub_4939E0(fld_5C, pszArg2);
  return result;
}



// ------------------------------------------------------------
// 0x6021C0 CNChangeMp__vmt14
// ------------------------------------------------------------
char /*thiscall*/ CNChangeMp__vmt14(int *this, char pszArg2, int nArg3, int nArg4, int nArg5)
{
  char result; // al
  int fld_e23; // ecx

  result = pszArg2;
  if ( pszArg2 != 0 )
  {
    fld_e23 = *(this + 23);
    if ( fld_e23 != 0 )
    {
      sub_4938F0(fld_e23);
      return sub_491D00(dword_79C0B0, nArg3, nArg4 - 60, 0.0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602200 CNChangeMp__vmt4
// ------------------------------------------------------------
// MP 恢复 PO 激活/生成（vmt4）：字符串证据「MP_RECOVERED」（音效 TAG，走 vt+212 播音链）。
// 流程：lerp 渐变（sub_4049C0）+ sub_4600B0 演播层入列 + sub_699000 clock_now 计时（P9 时间域）+ sub_5E5260 字符串释放。
// 语义：蓝色 MP 精灵拾取后的恢复演出编排。
int /*thiscall*/ CNChangeMp__vmt4(int this)
{
  int fld_54; // edi
  int pThis_8; // eax
  uint64_t v4; // rax
  int fld_58; // ecx
  int v6; // edi
  int *fld_4; // ecx
  int v8; // ebx
  int v9; // eax
  int fld_5C; // eax
  int pObj; // edi
  int fld_42; // edx
  int v13; // ebx
  int v14; // eax
  int *fld_43; // ecx
  int v16; // eax
  void *v17; // eax
  int fld_44; // ecx
  int result; // eax
  float v20; // [esp+0h] [ebp-38h]
  int v21; // [esp+0h] [ebp-38h]
  int v22; // [esp+4h] [ebp-34h]
  void *v23[4]; // [esp+18h] [ebp-20h] BYREF
  int fld_50; // [esp+28h] [ebp-10h]
  int v25; // [esp+34h] [ebp-4h]

  IRDAppendage__vmt4((int *)this);
  fld_54 = *(uint32_t *)(this + 84);
  pThis_8 = sub_699000(this + 8);  // 【clock_now(clk)】
  fld_50 = *(uint32_t *)(this + 80);
  v20 = (float)fld_50;
  v4 = (uint64_t)sub_4049C0(0.0, v20, pThis_8, fld_54);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  fld_58 = *(uint32_t *)(this + 88);
  if ( (uint32_t)v4 != fld_58 )
  {
    v6 = v4 - fld_58;
    fld_4 = *(int **)(this + 4);
    *(uint32_t *)(this + 88) = v4;
    v8 = *fld_4;
    v9 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*fld_4 + 752))(fld_4, 0);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v8 + 744))(*(uint32_t *)(this + 4), v6 + v9);
  }
  fld_5C = *(uint32_t *)(this + 92);
  if ( fld_5C != 0 && *(int *)(fld_5C + 148) >= 4 && *(uint8_t *)(this + 96) == 0 )
  {
    if ( *(uint32_t *)(dword_8F7A24 + 12) != 4 || *(uint32_t *)(this + 4) == dword_8F7C04 )
    {
      pObj = dword_8F82B4;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F82B4 + 12))(dword_8F82B4);
      fld_42 = **(uint32_t **)(this + 4);
      v13 = *(uint32_t *)pObj;
      fld_50 = *(uint32_t *)(this + 4);
      v22 = (*(int (**)(void))(fld_42 + 128))() + 60;
      v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_50 + 124))(fld_50);
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_50 + 120))(fld_50);
      (*(void (/*thiscall*/ **)(int, int))(v13 + 40))(pObj, v14);
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj + 92))(pObj, v23);
      fld_43 = *(int **)(this + 4);
      v16 = *fld_43;
      v25 = 0;
      v17 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(v16 + 80))(fld_43, 2, 0, v23);
      sub_4600B0(v17, v21, v22, 0);
      v25 = -1;
      sub_5E5260(v23);
    }
    fld_44 = *(uint32_t *)(this + 4);
    *(uint8_t *)(this + 96) = 1;
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)fld_44 + 212))(
      fld_44,
      "MP_RECOVERED",
      -1,
      0,
      0);
  }
  result = *(uint32_t *)(this + 88);
  if ( result == *(uint32_t *)(this + 80) )
  {
    result = *(uint32_t *)(this + 92);
    if ( result == 0 || *(uint8_t *)(result + 170) != 0 )
      return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 76))(this, 0);
  }
  return result;
}



// ============================================================
// 【分区 3】附加器（IRDAppendage）道具/装备族（0x602380-0x6056B0）
// 注意：本区并非 PO 本体 —— 0x602810 析构链直证 vftbl_IRDAppendage 基类。
// CNRemoveActiveStatus / CNActiveStatusStackable / CNOmozzaOfWorld / CNLotteryStackable /
// CNAntiFreezePotion / CNSpecificEnemyEquipment / CNEventEquipment 等 Stackable 族：
// 激活入口统一为 vmt88 → 记录逐条写入目标 vt+760（研究 20 §10 17 状态槽写入器）。
// 音效/UI 证据：RECIPE_NOTICE、USE_DEBUFF、ALERT_1、RemoveActiveStatus.ptl
// ============================================================
// ------------------------------------------------------------
// 0x602380 sub_602380
// ------------------------------------------------------------
int /*thiscall*/ sub_602380(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int v5; // eax

  result = nArg2;
  *(this + 20) = nArg2;
  *(this + 21) = nArg3;
  if ( nArg2 > 0 )
  {
    v5 = sub_42FCB0(228);
    if ( v5 != 0 )
    {
      result = sub_431860(v5, "Common/CommonEffect/Animation/MpUp.ani", 1);
      *(this + 23) = result;
    }
    else
    {
      *(this + 23) = 0;
      return 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602400 sub_602400
// ------------------------------------------------------------
int /*thiscall*/ sub_602400(void ***this)
{
  int fld_e23; // esi
  int result; // eax

  fld_e23 = (int)*(this + 23);
  if ( fld_e23 != 0 )
  {
    sub_42AF90(*(this + 23));
    result = sub_657740(fld_e23, 228);
  }
  *(this + 23) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x602430 sub_602430
// ------------------------------------------------------------
int /*thiscall*/ sub_602430(int this)
{
  *(uint32_t *)(this + 180) = 0;
  *(uint8_t *)(this + 184) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x602440 sub_602440
// ------------------------------------------------------------
int /*thiscall*/ sub_602440(int this, int nArg2, char pszArg3)
{
  *(uint32_t *)(this + 180) = nArg2;
  *(uint8_t *)(this + 184) = pszArg3;
  return nArg2;
}



// ------------------------------------------------------------
// 0x602460 sub_602460
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_602460(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; result += 4 )
  {
    if ( result != nullptr )
    {
      *result = *uArg12;
      result[1] = uArg12[1];
      result[2] = uArg12[2];
      result[3] = uArg12[3];
    }
    uArg12 += 4;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6024A0 sub_6024A0
// ------------------------------------------------------------
void /*noreturn*/ sub_6024A0()
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
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x602510 sub_602510
// ------------------------------------------------------------
// 附加器记录 vector 中间插入（与 0x601220 同族手工展开，16B/条）：容量翻倍 + sub_50F360 尾段构造 + sub_602460 搬移。
// 附加器（Appendage）记录表的扩容内核。
unsigned int /*thiscall*/ sub_602510(int this, int pArg2, unsigned int uArg3, uint32_t *Block)
{
  int v5; // edx
  int v6; // ecx
  int fld_4; // edx
  unsigned int result; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v12; // eax
  int fld_87; // ecx
  int fld_88; // eax
  uint32_t *v15; // ebx
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v18; // edi
  void *fld_83; // eax
  int fld_86; // edi
  int v21; // edi
  int fld_42; // [esp-18h] [ebp-44h]
  int fld_85; // [esp-Ch] [ebp-38h]
  unsigned int fld_84; // [esp-8h] [ebp-34h]
  int v25; // [esp+0h] [ebp-2Ch] BYREF
  uint32_t v26[5]; // [esp+Ch] [ebp-20h] BYREF
  int v27; // [esp+28h] [ebp-4h]
  int v28; // [esp+38h] [ebp+Ch]
  char *Blocka; // [esp+3Ch] [ebp+10h]
  void *Blockb; // [esp+3Ch] [ebp+10h]

  v5 = Block[1];
  v26[0] = *Block;
  v6 = Block[2];
  v26[1] = v5;
  v26[3] = Block[3];
  fld_4 = *(uint32_t *)(this + 4);
  v26[4] = &v25;
  v26[2] = v6;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 4;
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
    else
      fld_8 = 0;
    if ( 0xFFFFFFF - fld_8 < uArg3 )
      sub_50F360(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(void **)(this + 8);
      Blockb = fld_83;
      if ( ((int)fld_83 - pArg2) >> 4 >= uArg3 )
      {
        v21 = (int)fld_83 - 16 * uArg3;
        *(uint32_t *)(this + 8) = sub_602460(v21, fld_83, fld_83);
        sub_4BF320(pArg2, v21, (int)Blockb);
        return sub_453C20(pArg2, pArg2 + 16 * uArg3, v26);
      }
      else
      {
        sub_602460(pArg2, fld_83, pArg2 + 16 * uArg3);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 4);
        fld_85 = *(uint32_t *)(this + 8);
        v27 = 2;
        sub_504650(fld_85, fld_84, v26);
        fld_86 = 16 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        return sub_453C20(pArg2, fld_86 - 16 * uArg3, v26);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (result >> 1) >= result )
        v12 = (result >> 1) + result;
      else
        v12 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
      else
        fld_87 = 0;
      if ( v12 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
        else
          fld_88 = 0;
        v12 = uArg3 + fld_88;
      }
      v28 = 16 * v12;
      Blocka = (char *)operator new(16 * v12);
      fld_42 = *(uint32_t *)(this + 4);
      v27 = 0;
      v15 = (uint32_t *)sub_602460(fld_42, pArg2, Blocka);
      sub_4BF340(v15, (uint32_t *)uArg3, v26);
      sub_602460(pArg2, *(uint32_t *)(this + 8), &v15[4 * uArg3]);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 4;
      else
        fld_89 = 0;
      v18 = fld_89 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &Blocka[v28];
      *(uint32_t *)(this + 8) = &Blocka[16 * v18];
      *(uint32_t *)(this + 4) = Blocka;
      return (unsigned int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x602770 sub_602770
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_602770(uint32_t *this, char pszArg2, void *Block)
{
  sub_4B1030(this);
  *this = &vftbl_CNRemoveActiveStatus;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  sub_651AE0(this);
  sub_651F70(pszArg2, Block);
  return this;
}



// ------------------------------------------------------------
// 0x6027E0 CNRemoveActiveStatus__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRemoveActiveStatus__vmt0(void *Block, char pszArg2)
{
  sub_602810();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x602810 sub_602810
// ------------------------------------------------------------
// 析构链：本类 vtable → 释放 +88 向量 → 降级 vftbl_IRDAppendage（sub_5F6640 基类析构）→ nengine::IObject。
// 直证本族类层次：CNRemoveActiveStatus 等 Stackable 族派生自 IRDAppendage（装备附加器），并非 PassiveObject 本体。
int /*thiscall*/ sub_602810(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNRemoveActiveStatus;
  sub_651AF0();
  if ( *(uint32_t *)(this + 88) != 0 )
    j__free(*(void **)(this + 88));
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint8_t *)(this + 12) = 0;
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  return result;
}



// ------------------------------------------------------------
// 0x602890 sub_602890
// ------------------------------------------------------------
// 附加器状态分发：对激活的目标（vt+308 检查）遍历 +42..+43 的 16B 记录表（id/值/组三字段）：
// 组 == -1 时 new 0x68B 附属对象（sub_602770）经 vt+56 挂载；否则直接调目标 vt+760 —— 即研究 20 §10 的 17 状态槽写入器（IRDActiveObject vt+760）。
// 是『装备/道具给角色上状态』的统一咽喉。
int /*thiscall*/ sub_602890(uint32_t *this, void *Block)
{
  int result; // eax
  int i; // esi
  int v5; // eax
  uint32_t *pMem; // eax
  uint32_t *v7; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 308))(Block);
  if ( (uint8_t)result != 0 )
  {
    result = *(this + 43);
    for ( i = *(this + 42); i != result; i += 16 )
    {
      v5 = *(uint32_t *)(i + 8);
      if ( v5 == -1 )
      {
        pMem = operator new(0x68u);
        if ( pMem != nullptr )
          v7 = sub_602770(pMem, *(uint32_t *)i, (void *)*(uint8_t *)(i + 12));
        else
          v7 = nullptr;
        (*(void (/*thiscall*/ **)(uint32_t *, void *, void *, uint32_t, uint32_t, uint32_t, int))(*v7 + 56))(
          v7,
          Block,
          Block,
          0,
          0,
          0,
          -1);
      }
      else
      {
        (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, int, void *, uint32_t))(*(uint32_t *)Block + 760))(
          Block,
          *(uint32_t *)i,
          *(uint32_t *)(i + 4),
          v5,
          Block,
          0);
      }
      result = *(this + 43);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602960 sub_602960
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_602960(int this, uint32_t *Block)
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi
  unsigned int result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) >> 4 )
    return sub_602510(this, *(char **)(this + 8), 1u, Block);
  fld_82 = *(uint32_t *)(this + 8);
  result = sub_4BF340(fld_82, 1, Block);
  *(uint32_t *)(this + 8) = fld_82 + 16;
  return result;
}



// ------------------------------------------------------------
// 0x6029D0 CNActiveStatusStackable__vmt88
// ------------------------------------------------------------
// 主动状态附加器激活入口（vmt88）：目标激活检查后调 sub_602890 分发状态记录到 vt+760 槽；
// sub_48C0A0/sub_578100 = 状态应用/聚合【推断：把记录折算进 17 槽异常状态体系，研究 20 §10】。
// 对应研究：CNRemoveActiveStatus/CNActiveStatusStackable 共用此管线。
int /*thiscall*/ sub_6029D0(int this, int *Block, int nArg3, int nArg4)  // 【CNActiveStatusStackable__vmt88】
{
  int *v6; // esi
  int result; // eax
  int v8; // edx
  int v9; // edi
  int v10; // eax
  unsigned int v11; // edx
  int v12; // ecx
  int v13; // edi
  int pThis2; // eax
  int v15; // edi
  uint64_t v16; // rax
  double v17; // st7
  double v18; // st7
  double v19; // st7
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // eax
  int v24; // [esp-8h] [ebp-2Ch]
  int v25; // [esp+Ch] [ebp-18h] BYREF
  int v26; // [esp+10h] [ebp-14h]
  int v27; // [esp+14h] [ebp-10h]
  int v28; // [esp+18h] [ebp-Ch]
  int v29; // [esp+1Ch] [ebp-8h]
  int pThis; // [esp+20h] [ebp-4h]
  int Blocka; // [esp+2Ch] [ebp+8h]
  int v32; // [esp+30h] [ebp+Ch]
  int v33; // [esp+34h] [ebp+10h]

  pThis = this;
  sub_578100(Block, nArg3, nArg4);  // 【CNRDStackable__vmt88】
  v6 = nullptr;
  if ( *(uint32_t *)(this + 180) == 0 )
  {
    result = *(uint8_t *)(this + 184);
    if ( (uint8_t)result == 0 )
      return sub_602890(Block);
    return result;
  }
  v8 = *Block;
  v25 = 0;
  v26 = 0;
  v27 = 0;
  v28 = 0;
  v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 80))(Block);
  v10 = *(uint32_t *)(v9 + 120);
  v33 = v9;
  if ( v10 != 0 )
    Blocka = (*(uint32_t *)(v9 + 124) - v10) >> 2;
  else
    Blocka = 0;
  result = Blocka;
  v11 = 0;
  v32 = 0;
  if ( Blocka > 0 )
  {
    while ( 1 )
    {
      v12 = *(uint32_t *)(v9 + 120);
      if ( v12 != 0 && v11 < (*(uint32_t *)(v9 + 124) - v12) >> 2 )
        v6 = *(int **)(v12 + 4 * v11);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v6 + 40))(v6, 17) != 0 )
      {
        v13 = (*(int (/*thiscall*/ **)(int *))(*Block + 376))(Block);
        if ( (*(int (/*thiscall*/ **)(int *))(*v6 + 376))(v6) == v13 )
        {
          pThis2 = pThis;
          if ( *(uint8_t *)(pThis + 184) == 0 || v6 != Block )
          {
            v15 = 0;
            while ( 1 )
            {
              if ( v15 != 0 )
              {
                if ( v15 == 1 )
                {
                  v29 = 2 * *(uint32_t *)(pThis2 + 180);
                  v18 = (double)v29;
                  v16 = (uint64_t)(0.88 * v18);
                  v17 = v18 * 0.2552;
                }
                else
                {
                  if ( v15 != 2 )
                    goto LABEL_26;
                  v29 = 2 * *(uint32_t *)(pThis2 + 180);
                  v19 = (double)v29;
                  v16 = (uint64_t)(0.60000002 * v19);
                  v17 = v19 * 0.28999999;
                }
              }
              else
              {
                LODWORD(v16) = 2 * *(uint32_t *)(pThis2 + 180);
                v29 = v16;
                v17 = (double)(int)v16 * 0.17399999;
              }
              v27 = v16;
              v28 = (uint64_t)v17;
LABEL_26:
              v20 = (*(int (/*thiscall*/ **)(int *))(*Block + 120))(Block);
              v21 = *Block;
              v25 = v20 - v27 / 2;
              v22 = (*(int (/*thiscall*/ **)(int *))(v21 + 124))(Block);
              v26 = v22 - v28 / 2;
              v24 = (*(int (/*thiscall*/ **)(int *))(*v6 + 124))(v6);
              v23 = (*(int (/*thiscall*/ **)(int *))(*v6 + 120))(v6);
              if ( (uint8_t)sub_48C0A0(v23, v24, &v25) != 0 )
              {
                sub_602890(v6);
                break;
              }
              if ( ++v15 >= 3 )
                break;
              pThis2 = pThis;
            }
          }
        }
        v9 = v33;
      }
      result = ++v32;
      if ( v32 >= Blocka )
        return result;
      v11 = v32;
      v6 = nullptr;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x602BC0 sub_602BC0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_602BC0(void *this, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  uint32_t Block[3]; // [esp+0h] [ebp-10h] BYREF
  char pszArg52; // [esp+Ch] [ebp-4h]

  Block[0] = nArg2;
  Block[2] = nArg4;
  Block[1] = nArg3;
  pszArg52 = pszArg5;
  return sub_602960((int)this + 164, Block);
}



// ------------------------------------------------------------
// 0x602C00 sub_602C00
// ------------------------------------------------------------
int /*thiscall*/ sub_602C00(uint32_t *this, int nArg2)
{
  CNRDStackable__vmt88(*(this + 41), *(this + 42), *(this + 43));
  return sub_487000(nArg2);
}



// ------------------------------------------------------------
// 0x602C40 CNIncreaseStatusStackable__vmt88
// ------------------------------------------------------------
// CNIncreaseStatusStackable 激活（vmt88）：字符串证据「RECIPE_NOTICE」（UI 通知 TAG）。
// sub_422E70/sub_432EA0/sub_43BEE0 = 消息广播三件套 + sub_44E8D0（UI 通知，宿主 dword_8F8528）→ 合成/配方提示 + sub_602C00 基类调用。
void */*thiscall*/ CNIncreaseStatusStackable__vmt88(int *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // edi
  void *result; // eax
  uint32_t *v7; // esi
  char *v8; // eax
  int fld_e3; // eax
  int v10; // edx
  uint32_t v11[3]; // [esp+8h] [ebp-Ch] BYREF

  *(this + 41) = nArg2;
  *(this + 42) = nArg3;
  *(this + 43) = nArg4;
  v5 = -1;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 308))(nArg2) == 0
    || *(this + 32) == 0
    || (result = (void *)sub_484E80(*(this + 3)), v5 = (int)result, result != (void *)-1) )
  {
    if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
    {
      v7 = *((uint32_t **)dword_8F8528 + 7);
      v8 = sub_422E70(1201);
      sub_43BEE0(v7, (int)v8, -6567706, 0, -1);
      return sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
    }
    fld_e3 = *(this + 3);
    if ( fld_e3 > 4082 )
    {
      if ( fld_e3 < 4087 || fld_e3 > 4102 )
        return (void *)sub_602C00(this, v5);
    }
    else if ( fld_e3 < 4079 && fld_e3 != 3 && (fld_e3 <= 4040 || fld_e3 > 4052) )
    {
      return (void *)sub_602C00(this, v5);
    }
    v10 = *this;
    v11[0] = this;
    v11[2] = v5;
    v11[1] = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v10 + 16))(this) + 4);
    return (void *)sub_44E8D0((char *)dword_8F8528, (void *)0x31, (int)v11, v5);
  }
  return result;
}



// ------------------------------------------------------------
// 0x602D50 CNItemScreamOfHysma__vmt88
// ------------------------------------------------------------
int /*stdcall*/ CNItemScreamOfHysma__vmt88(int nArg1, int nArg2, int nArg3)
{
  int result; // eax

  CNRDStackable__vmt88(nArg1, nArg2, nArg3);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 308))(nArg1);
  if ( (uint8_t)result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)nArg1 + 580))(
             nArg1,
             48001,
             2,
             0,
             0,
             0,
             0,
             0,
             4,
             0,
             0,
             0);
  return result;
}



// ------------------------------------------------------------
// 0x602DA0 sub_602DA0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_602DA0(int this, int nArg2, float fArg3, int nArg4)
{
  uint64_t result; // rax

  *(uint32_t *)(this + 180) = nArg2;
  result = (uint64_t)(fArg3 * 100.0);
  *(uint32_t *)(this + 188) = nArg4;
  *(float *)(this + 184) = (float)(int)result;
  return result;
}



// ------------------------------------------------------------
// 0x602DE0 sub_602DE0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_602DE0(uint32_t *this)
{
  unsigned int i; // ebx
  int fld_e42; // ecx
  unsigned int result; // eax
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  for ( i = 0; ; ++i )
  {
    fld_e42 = *(this + 42);
    if ( fld_e42 == 0 )
      break;
    result = (*(this + 43) - fld_e42) >> 3;
    if ( i >= result )
      break;
    v5 = *(void (/*thiscall*/ ****)(uint32_t, int))(fld_e42 + 8 * i);
    if ( v5 != nullptr )
      (**v5)(v5, 1);
    result = 8 * i + *(this + 42);
    *(uint32_t *)result = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x602E40 sub_602E40
// ------------------------------------------------------------
void /*thiscall*/ sub_602E40(int this)
{
  if ( *(uint32_t *)(this + 168) != 0 )
    j__free(*(void **)(this + 168));
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
}



// ------------------------------------------------------------
// 0x602E80 sub_602E80
// ------------------------------------------------------------
// 附加器记录表重建（配方/材料列表解析）：sub_41FEB0 容器清空 → sub_44BD00/44BD30 逐词读取 → sub_50F360 入表 → sub_5E51F0/sub_63A7C0 收尾。
// 与 0x606650（对话文本表）/0x609FF0（草丛表）同一解析族。
void /*thiscall*/ sub_602E80(int this, int nArg2, unsigned int uArg3, int pArg4)
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

  v4 = *(void **)(pArg4 + 4);
  v28[0] = *(void **)pArg4;
  fld_4 = *(uint32_t *)(this + 4);
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
    else
      fld_8 = 0;
    if ( 0x1FFFFFFF - fld_8 < uArg3 )
      sub_50F360(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);
      v20 = (fld_83 - nArg2) >> 3 < uArg3;
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;
      if ( v20 )
      {
        sub_44BD30(nArg2, fld_83, nArg2 + v21);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 3);
        fld_85 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);
        fld_86 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        sub_41FEB0(nArg2, fld_86 - v30, v28);
      }
      else
      {
        v23 = fld_83 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);
        sub_44BD00(nArg2, v23, fld_832);
        sub_41FEB0(nArg2, nArg2 + v30, v28);
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )
        v11 = (fld_C >> 1) + fld_C;
      else
        v11 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
      else
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
        else
          fld_88 = 0;
        v11 = uArg3 + fld_88;
      }
      v31 = 8 * v11;
      pMem = (char *)operator new(8 * v11);
      fld_42 = *(uint32_t *)(this + 4);
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, nArg2, pMem);
      sub_63A7C0(v32, uArg3, v28);
      sub_44BD30(nArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;
      else
        fld_89 = 0;
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &pMem[v31];
      *(uint32_t *)(this + 8) = &pMem[8 * v17];
      *(uint32_t *)(this + 4) = pMem;
    }
  }
}


// ------------------------------------------------------------
// 0x6030D0 CNAppendageStackable__vmt88
// ------------------------------------------------------------
// CNAppendageStackable 激活（vmt88）：把记录经 sub_602770 构造成 0x68B 附属对象挂载（602890 的 -1 组路径）。
// 语义：『附带物』类道具（小精灵/随行装置）【推断】。
void /*thiscall*/ CNAppendageStackable__vmt88(int this, int nArg2, int nArg3, unsigned int Seed)
{
  int fld_A8; // ecx
  unsigned int i; // ebx
  int fld_A82; // ecx
  int fld_BC; // eax
  uint32_t *pMem; // eax
  uint32_t *fld_B4; // eax

  CNRDStackable__vmt88(nArg2, nArg3, Seed);
  fld_A8 = *(uint32_t *)(this + 168);
  if ( fld_A8 != 0 && (*(uint32_t *)(this + 172) - fld_A8) >> 3 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      fld_A82 = *(uint32_t *)(this + 168);
      if ( fld_A82 == 0 || i >= (*(uint32_t *)(this + 172) - fld_A82) >> 3 )
        break;
      (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(fld_A82 + 8 * i) + 56))(
        *(uint32_t *)(fld_A82 + 8 * i),
        nArg2,
        nArg2,
        0,
        0,
        *(uint32_t *)(*(uint32_t *)(this + 168) + 8 * i + 4),
        -1);
    }
    if ( *(uint32_t *)(this + 168) != 0 )
      j__free(*(void **)(this + 168));
    *(uint32_t *)(this + 168) = 0;
    *(uint32_t *)(this + 172) = 0;
    *(uint32_t *)(this + 176) = 0;
  }
  srand(Seed);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 308))(nArg2) != 0
    && *(uint32_t *)(this + 180) != 17
    && (double)(rand() % 10000) < *(float *)(this + 184) )
  {
    fld_BC = *(uint32_t *)(this + 188);
    if ( fld_BC == -1 )
    {
      pMem = operator new(0x68u);
      if ( pMem != nullptr )
        fld_B4 = sub_602770(pMem, *(uint32_t *)(this + 180), (void *)1);
      else
        fld_B4 = nullptr;
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*fld_B4 + 56))(fld_B4, nArg2, nArg2, 0, 0, 0, -1);
    }
    else
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int, uint32_t))(*(uint32_t *)nArg2 + 760))(
        nArg2,
        *(uint32_t *)(this + 180),
        1120403456,
        fld_BC,
        nArg2,
        0);
    }
  }
}



// ------------------------------------------------------------
// 0x603260 sub_603260
// ------------------------------------------------------------
void /*thiscall*/ sub_603260(int this, int nArg2)
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
  else
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 3 )
  {
    fld_82 = *(uint32_t *)(this + 8);
    sub_63A7C0(fld_82, 1, nArg2);
    *(uint32_t *)(this + 8) = fld_82 + 8;
  }
  else
  {
    sub_602E80(this, *(char **)(this + 8), 1u, nArg2);
  }
}



// ------------------------------------------------------------
// 0x6032D0 sub_6032D0
// ------------------------------------------------------------
void /*thiscall*/ sub_6032D0(void *this, int nArg2, int nArg3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = nArg2;
  v3[1] = nArg3;
  sub_603260((int)this + 164, (int)v3);
}



// ------------------------------------------------------------
// 0x603300 sub_603300
// ------------------------------------------------------------
// 记录表重建变体：sub_602E80 全量重建 + sub_63A7C0 追加处理 —— 双表联动的附加器装载。
int /*thiscall*/ sub_603300(void *this, int nArg2, uint32_t *uArg3, int nArg4)
{
  int v4; // edi
  int pThis_A4; // esi
  uint32_t *uArg32; // ebx
  int v7; // eax
  int v8; // ecx
  unsigned int v9; // edx
  int v10; // edi
  int result; // eax
  uint32_t v12[2]; // [esp+0h] [ebp-8h] BYREF
  int v13; // [esp+14h] [ebp+Ch]

  if ( nArg4 > 0 )
  {
    v4 = nArg2 - (uint32_t)uArg3;
    pThis_A4 = (int)this + 164;
    uArg32 = uArg3;
    v13 = nArg2 - (uint32_t)uArg3;
    do
    {
      v7 = *(uint32_t *)((char *)uArg32 + v4);
      v12[1] = *uArg32;
      v8 = *(uint32_t *)(pThis_A4 + 4);
      v12[0] = v7;
      if ( v8 != 0 )
        v9 = (*(uint32_t *)(pThis_A4 + 8) - v8) >> 3;
      else
        v9 = 0;
      if ( v8 != 0 && v9 < (*(uint32_t *)(pThis_A4 + 12) - v8) >> 3 )
      {
        v10 = *(uint32_t *)(pThis_A4 + 8);
        sub_63A7C0(v10, 1, v12);
        *(uint32_t *)(pThis_A4 + 8) = v10 + 8;
        v4 = v13;
      }
      else
      {
        sub_602E80(pThis_A4, *(char **)(pThis_A4 + 8), 1u, (int)v12);
      }
      ++uArg32;
      result = --nArg4;
    }
    while ( nArg4 != 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x6033B0 sub_6033B0
// ------------------------------------------------------------
// CNOmozzaOfWorld 前置装载：纯数据表操作（无外部调用）——记录 vector 的重排/去重【推断：世界树果实的 debuff 参数表】。
int /*thiscall*/ sub_6033B0(int *this, int nArg2, int nArg3)
{
  int i; // esi
  int pObj2; // eax
  int v6; // edi
  int result; // eax
  unsigned int v8; // esi
  int v9; // ecx
  int pObj3; // ecx
  int v11; // ecx
  int pObj; // ecx
  int fld_e41; // eax
  int v14; // edx
  int v16; // [esp+18h] [ebp+8h]
  int v17; // [esp+1Ch] [ebp+Ch]

  for ( i = 0; i < 17; ++i )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 776))(nArg2, i) != 0 )
    {
      pObj2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 772))(nArg2, i);
      (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj2 + 4))(pObj2, 0, nArg3);
    }
  }
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
  result = *(uint32_t *)(v6 + 4);
  v8 = 0;
  if ( result != 0 )
    v16 = (*(uint32_t *)(v6 + 8) - result) >> 2;
  else
    v16 = 0;
  v17 = 0;
  if ( v16 > 0 )
  {
    do
    {
      v9 = *(uint32_t *)(v6 + 4);
      if ( v9 != 0 && v8 < (*(uint32_t *)(v6 + 8) - v9) >> 2 )
        pObj3 = *(uint32_t *)(v9 + 4 * v8);
      else
        pObj3 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 92))(pObj3) != 0 )
      {
        v11 = *(uint32_t *)(v6 + 4);
        if ( v11 != 0 && v8 < (*(uint32_t *)(v6 + 8) - v11) >> 2 )
          pObj = *(uint32_t *)(v11 + 4 * v8);
        else
          pObj = 0;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);
        fld_e41 = *(this + 41);
        v14 = ++v17;
        if ( fld_e41 > 0 && v14 >= fld_e41 )
          break;
      }
      ++v8;
    }
    while ( (int)v8 < v16 );
    result = v17;
    if ( v17 > 0 )
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 956))(nArg2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6034A0 CNOmozzaOfWorld__vmt88
// ------------------------------------------------------------
// CNOmozzaOfWorld 激活（vmt88）：字符串证据「USE_DEBUFF」—— 使用时给自身上 DEBUFF 的道具（世界之实?）。
// sub_48C0A0/sub_578100 状态应用 + sub_6033B0 参数表 → 『强力道具附带惩罚』的载体。
char /*thiscall*/ sub_6034A0(int this, int *pDwArg2, int nArg3, int nArg4)  // 【CNOmozzaOfWorld__vmt88】
{
  int *v6; // esi
  char result; // al
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // ecx
  unsigned int v12; // edx
  int v13; // ecx
  int v14; // edi
  int pThis2; // eax
  int v16; // edi
  uint64_t v17; // rax
  double v18; // st7
  double v19; // st7
  double v20; // st7
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int v24; // eax
  int v25; // [esp-8h] [ebp-2Ch]
  int v26; // [esp+Ch] [ebp-18h] BYREF
  int v27; // [esp+10h] [ebp-14h]
  int v28; // [esp+14h] [ebp-10h]
  int v29; // [esp+18h] [ebp-Ch]
  int v30; // [esp+1Ch] [ebp-8h]
  int pThis; // [esp+20h] [ebp-4h]
  int v32; // [esp+2Ch] [ebp+8h]
  signed int v33; // [esp+30h] [ebp+Ch]
  int v34; // [esp+34h] [ebp+10h]

  pThis = this;
  sub_578100(pDwArg2, nArg3, nArg4);  // 【CNRDStackable__vmt88】
  v6 = nullptr;
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg2 + 212))(pDwArg2, "USE_DEBUFF", -1, 0, 0);
  if ( *(uint32_t *)(this + 168) == 0 )
  {
    result = *(uint8_t *)(this + 172);
    if ( result == 0 )
      return sub_6033B0(pDwArg2, pDwArg2);
    return result;
  }
  v8 = *pDwArg2;
  v26 = 0;
  v27 = 0;
  v28 = 0;
  v29 = 0;
  v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 80))(pDwArg2);
  v10 = v9;
  v11 = *(uint32_t *)(v9 + 120);
  v34 = v9;
  if ( v11 != 0 )
    v32 = (*(uint32_t *)(v9 + 124) - v11) >> 2;
  else
    v32 = 0;
  result = v32;
  v12 = 0;
  v33 = 0;
  if ( v32 > 0 )
  {
    while ( 1 )
    {
      v13 = *(uint32_t *)(v10 + 120);
      if ( v13 != 0 && v12 < (*(uint32_t *)(v10 + 124) - v13) >> 2 )
        v6 = *(int **)(v13 + 4 * v12);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v6 + 40))(v6, 17) != 0 )
      {
        v14 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 376))(pDwArg2);
        if ( (*(int (/*thiscall*/ **)(int *))(*v6 + 376))(v6) == v14 )
        {
          pThis2 = pThis;
          if ( *(uint8_t *)(pThis + 172) == 0 || v6 != pDwArg2 )
          {
            v16 = 0;
            while ( 1 )
            {
              if ( v16 != 0 )
              {
                if ( v16 == 1 )
                {
                  v30 = 2 * *(uint32_t *)(pThis2 + 168);
                  v19 = (double)v30;
                  v17 = (uint64_t)(0.88 * v19);
                  v18 = v19 * 0.2552;
                }
                else
                {
                  if ( v16 != 2 )
                    goto LABEL_26;
                  v30 = 2 * *(uint32_t *)(pThis2 + 168);
                  v20 = (double)v30;
                  v17 = (uint64_t)(0.60000002 * v20);
                  v18 = v20 * 0.28999999;
                }
              }
              else
              {
                LODWORD(v17) = 2 * *(uint32_t *)(pThis2 + 168);
                v30 = v17;
                v18 = (double)(int)v17 * 0.17399999;
              }
              v28 = v17;
              v29 = (uint64_t)v18;
LABEL_26:
              v21 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 120))(pDwArg2);
              v22 = *pDwArg2;
              v26 = v21 - v28 / 2;
              v23 = (*(int (/*thiscall*/ **)(int *))(v22 + 124))(pDwArg2);
              v27 = v23 - v29 / 2;
              v25 = (*(int (/*thiscall*/ **)(int *))(*v6 + 124))(v6);
              v24 = (*(int (/*thiscall*/ **)(int *))(*v6 + 120))(v6);
              if ( sub_48C0A0(v24, v25, &v26) )
              {
                sub_6033B0(v6, pDwArg2);
                break;
              }
              if ( ++v16 >= 3 )
                break;
              pThis2 = pThis;
            }
          }
        }
        v10 = v34;
      }
      result = ++v33;
      if ( v33 >= v32 )
        return result;
      v12 = v33;
      v6 = nullptr;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6036B0 CNUsableStackable__vmt88
// ------------------------------------------------------------
// CNUsableStackable 激活（vmt88）：字符串证据「RECIPE_NOTICE」；广播三件套（sub_422E70/432EA0/43BEE0）+ sub_44E8D0 UI 通知。
// 可用类道具的通用激活路径。
int /*thiscall*/ CNUsableStackable__vmt88(int *this, int nArg2, int nArg3, int nArg4)
{
  int fld_e3; // eax
  uint32_t *v5; // esi
  char *v6; // eax
  int result; // eax
  uint32_t *v8; // esi
  char *v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // edx

  fld_e3 = *(this + 3);
  if ( fld_e3 < 14 || fld_e3 > 15 )
    goto LABEL_7;
  if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
  {
    v5 = *((uint32_t **)dword_8F8528 + 7);
    v6 = sub_422E70(1201);
    sub_43BEE0(v5, (int)v6, -6567706, 0, -1);
    return (int)sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
  }
  if ( *((uint32_t *)dword_8F8528 + 26) == 9 )
  {
    v8 = *((uint32_t **)dword_8F8528 + 7);
    v9 = sub_422E70(2000);
    sub_43BEE0(v8, (int)v9, -6567706, 0, -1);
    return (int)sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
  }
  else
  {
LABEL_7:
    v10 = fld_e3 - 14;
    if ( v10 != 0 )
    {
      result = v10 - 1;
      if ( result == 0 )
      {
        v11 = *((uint32_t *)dword_8F8528 + 90);
        if ( v11 == 0 )
          return sub_44E8D0((char *)dword_8F8528, (void *)0xE, 0, 0);
        result = (*((uint32_t *)dword_8F8528 + 91) - v11) >> 2;
        if ( result == 0 )
          return sub_44E8D0((char *)dword_8F8528, (void *)0xE, 0, 0);
      }
    }
    else
    {
      v12 = *((uint32_t *)dword_8F8528 + 90);
      if ( v12 == 0 )
        return sub_44E8D0((char *)dword_8F8528, (void *)0xE, 0, 1);
      result = (*((uint32_t *)dword_8F8528 + 91) - v12) >> 2;
      if ( result == 0 )
        return sub_44E8D0((char *)dword_8F8528, (void *)0xE, 0, 1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6037B0 sub_6037B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6037B0(uint32_t *this, int nArg2)
{
  *(this + 11) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x6037C0 CNChangeActiveProperty__vmtC
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNChangeActiveProperty__vmtC(uint32_t *this, int nArg2)
{
  uint32_t *result; // eax
  uint32_t *i; // esi
  int v4; // ebx
  unsigned int v5; // edi
  int v6; // eax
  int v7; // edx

  result = (uint32_t *)*(this + 22);
  for ( i = (uint32_t *)*(this + 21); i != result; i += 2 )
  {
    v4 = i[1];
    v5 = 14 * *i + nArg2 + 284;
    v6 = sub_41A5E0(v5);
    sub_41A590(v5, v7, v4 + v6);
    result = (uint32_t *)*(this + 22);
  }
  return result;
}



// ------------------------------------------------------------
// 0x603810 CNChangeActiveProperty__vmt1C
// ------------------------------------------------------------
// CNChangeActiveProperty 周期槽（vmt1C）：sub_41A5E0 = 研究 20 P24 防篡改读写闭环的写侧直证 + sub_497040 属性重算。
// 活动属性（力量/智力等）变更的周期结算。
int /*thiscall*/ CNChangeActiveProperty__vmt1C(int this)
{
  int result; // eax
  uint32_t *fld_54; // esi
  int v4; // edi
  int v5; // [esp+4h] [ebp-10h]
  int v6; // [esp+Ch] [ebp-8h]
  int v7; // [esp+10h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 3);
    fld_54 = *(uint32_t **)(this + 84);
    v7 = result;
    if ( fld_54 != *(uint32_t **)(this + 88) )
    {
      do
      {
        v5 = sub_497040(*fld_54);
        if ( v5 != 17 )
        {
          v4 = 14 * *fld_54 + v7;
          v6 = sub_41A5E0(v4 + 284);
          if ( (int)(fld_54[1] + (uint64_t)((double)v6 * COERCE_FLOAT(sub_41A5E0(v4 + 508)))) >= 100
            && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 776))(
                 *(uint32_t *)(this + 4),
                 v5) != 0 )
          {
            (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 764))(
              v5,
              0,
              *(uint32_t *)(this + 4),
              0);
          }
        }
        result = *(uint32_t *)(this + 88);
        fld_54 += 2;
      }
      while ( fld_54 != (uint32_t *)result );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6038D0 sub_6038D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6038D0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  uint32_t v6[2]; // [esp+4h] [ebp-8h] BYREF

  v6[1] = nArg3;
  v6[0] = nArg2;
  sub_5E5E60((int)(this + 20), (int)v6);
  *(this + 11) = nArg4;
  return nArg4;
}



// ------------------------------------------------------------
// 0x603910 sub_603910
// ------------------------------------------------------------
int /*thiscall*/ sub_603910(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e20)(uint32_t, int); // ecx
  int result; // eax

  fld_e20 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 20);
  if ( fld_e20 != nullptr )
    result = (**fld_e20)(fld_e20, 1);
  *(this + 20) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x603930 CNChangeElementTolerance__vmtC
// ------------------------------------------------------------
// CNChangeElementTolerance 生成槽（vmtC）：sub_41A590/sub_41A5E0 成对出现 = P24 防篡改读/写闭环直证 ——
// 属性抗性变更 PO 在生成时即走防篡改通道读写抗性槽。
uint32_t */*thiscall*/ CNChangeElementTolerance__vmtC(uint32_t *this, int nArg2)
{
  uint32_t *result; // eax
  int *v3; // edi
  int v4; // eax
  unsigned int v5; // esi
  int i; // ebx
  int v7; // edx
  unsigned int v8; // esi
  unsigned int v9; // esi
  int v10; // ebx
  int v11; // eax
  int v12; // edx
  int v13; // ebx
  unsigned int v14; // esi
  int v15; // edx
  int v16; // [esp-10h] [ebp-20h]
  float v18; // [esp+4h] [ebp-Ch]
  int v19; // [esp+4h] [ebp-Ch]
  int v20; // [esp+4h] [ebp-Ch]
  float v21; // [esp+8h] [ebp-8h]
  int j; // [esp+8h] [ebp-8h]
  uint32_t *v23; // [esp+Ch] [ebp-4h]

  result = (uint32_t *)*(this + 22);
  v23 = result;
  if ( result != (uint32_t *)*(this + 23) )
  {
    v3 = result + 2;
    while ( 1 )
    {
      v4 = *result;
      if ( *((uint8_t *)v3 - 4) != 0 )
      {
        if ( v4 == 4 )
        {
          v5 = nArg2 + 228;
          for ( i = 4; i != 0; --i )
          {
            v18 = (double)*v3 * 0.0099999998;
            *(float *)&v19 = COERCE_FLOAT(sub_41A5E0(v5)) + v18;
            sub_41A590(v5, v7, v19);
            v5 += 14;
          }
        }
        else
        {
          v21 = (double)*v3 * 0.0099999998;
          v8 = 14 * v4 + nArg2 + 228;
          *(float *)&v20 = COERCE_FLOAT(sub_41A5E0(v8)) + v21;
          sub_41A590(v8, v20, v20);
        }
      }
      else if ( v4 == 4 )
      {
        v9 = nArg2 + 172;
        for ( j = 4; j != 0; --j )
        {
          v10 = *v3;
          v11 = sub_41A5E0(v9);
          sub_41A590(v9, v12, v10 + v11);
          v9 += 14;
        }
      }
      else
      {
        v13 = *v3;
        v14 = 14 * v4 + nArg2 + 172;
        v16 = v13 + sub_41A5E0(v14);
        sub_41A590(v14, v15, v16);
      }
      result = v23 + 3;
      v3 += 3;
      v23 += 3;
      if ( v23 == (uint32_t *)*(this + 23) )
        break;
      result = v23;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x603A50 sub_603A50
// ------------------------------------------------------------
int /*thiscall*/ sub_603A50(int this, int nArg2, char pszArg3, void *Src)
{
  int result; // eax

  result = nArg2;
  *(uint32_t *)(this + 44) = nArg2;
  *(uint8_t *)(this + 100) = pszArg3;
  if ( Src != nullptr )
    return sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  return result;
}



// ------------------------------------------------------------
// 0x603A90 sub_603A90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_603A90(int this, int nArg2, char pszArg3, int nArg4, int nArg5, char pszArg6, void *Src)
{
  int Block; // [esp+4h] [ebp-Ch] BYREF
  char pszArg32; // [esp+8h] [ebp-8h]
  int nArg42; // [esp+Ch] [ebp-4h]

  *(uint32_t *)(this + 44) = nArg5;
  *(uint8_t *)(this + 100) = pszArg6;
  if ( Src != nullptr )
    sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  Block = nArg2;
  nArg42 = nArg4;
  pszArg32 = pszArg3;
  return sub_5E5DE0((int *)(this + 84), &Block);
}



// ------------------------------------------------------------
// 0x603AF0 CNChangeElementTolerance__vmt4
// ------------------------------------------------------------
// CNChangeElementTolerance 激活（vmt4）：字符串证据「Common/CommonEffect/Particle/RemoveActiveStatus.ptl」
// （研究 20 P36 粒子资源）+ sub_428F30 发射器生成 + sub_4600B0 演播层 —— 抗性变更生效/解除时的粒子演出。
char /*thiscall*/ CNChangeElementTolerance__vmt4(int this)
{
  int fld_58; // eax
  uint32_t *pMem; // eax
  int *fld_4; // eax
  int fld_42; // ecx
  int v6; // edx
  int fld_50; // ebx
  int *fld_43; // edi
  int v9; // edx
  void *v10; // eax
  char result; // al
  int pThis_6C; // eax
  int v13; // [esp-14h] [ebp-38h]
  int v14; // [esp-10h] [ebp-34h]
  int v15; // [esp-Ch] [ebp-30h]
  void *v16[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+14h] [ebp-10h]
  int v18; // [esp+20h] [ebp-4h]

  IRDAppendage__vmt4((int *)this);
  fld_58 = *(uint32_t *)(this + 88);
  if ( fld_58 != 0 )
  {
    Block = (void *)((*(uint32_t *)(this + 92) - fld_58) / 12);
    if ( Block != nullptr
      && *(int *)(*(uint32_t *)(this + 88) + 8) > 0
      && *(uint8_t *)(this + 100) != 0
      && (*(uint32_t *)(dword_8F7A24 + 12) != 4 || *(uint32_t *)(this + 4) == dword_8F7C04) )
    {
      if ( *(uint32_t *)(this + 80) == 0 )
      {
        pMem = operator new(0x12Cu);
        Block = pMem;
        v18 = 0;
        if ( pMem != nullptr )
          fld_4 = sub_428F30(pMem, (int)"Common/CommonEffect/Particle/RemoveActiveStatus.ptl", *(uint32_t *)(this + 4));
        else
          fld_4 = nullptr;
        fld_42 = *(uint32_t *)(this + 4);
        *(uint32_t *)(this + 80) = fld_4;
        v6 = *fld_4;
        v18 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v6 + 112))(fld_4, fld_42);
      }
      fld_50 = **(uint32_t **)(this + 80);
      fld_43 = *(int **)(this + 4);
      v15 = (*(int (/*thiscall*/ **)(int *))(*fld_43 + 128))(fld_43) + 90;
      v14 = (*(int (/*thiscall*/ **)(int *))(*fld_43 + 124))(fld_43) + 30;
      v13 = (*(int (/*thiscall*/ **)(int *))(*fld_43 + 120))(fld_43);
      (*(void (/*thiscall*/ **)(uint32_t))(fld_50 + 40))(*(uint32_t *)(this + 80));
      (*(void (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(this + 80) + 92))(*(uint32_t *)(this + 80), v16);
      v9 = *fld_43;
      v18 = 1;
      v10 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(v9 + 80))(fld_43, 2, 0, v16);
      sub_4600B0(v10, v13, v14, v15);
      v18 = -1;
      sub_5E5260(v16);
    }
  }
  result = *(uint8_t *)(this + 101);
  if ( result == 0 )
  {
    if ( *(uint32_t *)(this + 128) < 0x10u )
      pThis_6C = this + 108;
    else
      pThis_6C = *(uint32_t *)(this + 108);
    result = (*(int (/*thiscall*/ **)(uint32_t, int, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
               *(uint32_t *)(this + 4),
               pThis_6C,
               -1,
               0,
               0);
    *(uint8_t *)(this + 101) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x603C70 CNThrowStackable__vmt88
// ------------------------------------------------------------
// CNThrowStackable 激活（vmt88）：字符串证据「ALERT_1」（警告音 TAG）——投掷道具使用警告。
// 广播三件套 + sub_495540（速度链，P38 vt+888 族）+ sub_431230 字符串入表。【推断：投掷物起手广播】
void /*thiscall*/ CNThrowStackable__vmt88(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int nArg32; // ebx
  uint32_t *v6; // esi
  char *v7; // eax
  int v8; // eax
  int fld_e25; // edx
  int v10; // eax
  int fld_e252; // edx
  unsigned int v12; // edx
  int fld_e37; // eax
  int fld_e253; // ecx
  int fld_e254; // ecx
  void *pBuf[7]; // [esp+Ch] [ebp-1Ch] BYREF

  nArg32 = nArg3;
  CNRDStackable__vmt88(nArg2, nArg3, nArg4);
  if ( nArg32 == 2
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 308))(nArg2) != 0
    && __RTDynamicCast(nArg2, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0) != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 104))(this) != 0 )
    {
      v6 = *((uint32_t **)dword_8F8528 + 7);
      v7 = sub_422E70(1204);
      sub_43BEE0(v6, (int)v7, -6567706, 0, -1);
      sub_432EA0("ALERT_1", -1, 0, 0);
    }
    else
    {
      v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 900))(nArg2, 3);
      fld_e25 = *(this + 25);
      nArg4 = v8;
      if ( fld_e25 != 0 && (unsigned int)((*(this + 26) - fld_e25) >> 2) > 4 && *(uint32_t *)(fld_e25 + 16) == 1 )
      {
        v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 672))(nArg2, 3);
        v8 = sub_495540(v10);
        nArg4 = v8;
      }
      fld_e252 = *(this + 25);
      if ( fld_e252 != 0 && (unsigned int)((*(this + 26) - fld_e252) >> 2) > 5 )
      {
        v12 = (int)((uint64_t)(1374389535LL * v8 * *(uint32_t *)(fld_e252 + 20)) >> 32) >> 5;
        nArg4 = v12 + (v12 >> 31);
      }
      memset(&pBuf[1], 0, 12);
      pBuf[6] = nullptr;
      nArg3 = 0;
      sub_431230((int)pBuf, &nArg3);
      fld_e37 = *(this + 37);
      if ( fld_e37 == 3 )
      {
        nArg3 = 1;
        sub_431230((int)pBuf, &nArg3);
      }
      else if ( fld_e37 == 4 )
      {
        nArg3 = 2;
        sub_431230((int)pBuf, &nArg3);
      }
      sub_431230((int)pBuf, this + 3);
      fld_e253 = *(this + 25);
      if ( fld_e253 != 0 && (unsigned int)((*(this + 26) - fld_e253) >> 2) > 2 )
        nArg3 = *(uint32_t *)(fld_e253 + 8);
      else
        nArg3 = 0;
      sub_431230((int)pBuf, &nArg3);
      fld_e254 = *(this + 25);
      if ( fld_e254 != 0 && (unsigned int)((*(this + 26) - fld_e254) >> 2) > 3 )
        nArg3 = *(uint32_t *)(fld_e254 + 12);
      else
        nArg3 = 500;
      sub_431230((int)pBuf, &nArg3);
      nArg3 = 0;
      sub_431230((int)pBuf, &nArg3);
      nArg3 = 0;
      sub_431230((int)pBuf, &nArg3);
      nArg3 = 0;
      sub_431230((int)pBuf, &nArg3);
      sub_431230((int)pBuf, &nArg4);
      sub_431230((int)pBuf, &nArg4);
      (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 560))(nArg2, 10, pBuf, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 564))(nArg2);
      sub_5E5260(pBuf);
    }
  }
}



// ------------------------------------------------------------
// 0x603EE0 sub_603EE0
// ------------------------------------------------------------
void /*thiscall*/ sub_603EE0(uint32_t *this)
{
  *(this + 41) = 4;
}



// ------------------------------------------------------------
// 0x603EF0 CNRecipeStackable__vmt88
// ------------------------------------------------------------
int /*thiscall*/ CNRecipeStackable__vmt88(void *this, int nArg2, int nArg3, int nArg4)
{
  int result; // eax

  result = CNRDStackable__vmt88(nArg2, nArg3, nArg4);
  if ( nArg3 == 2 )
    return sub_44E8D0((char *)dword_8F8528, (void *)0x21, (int)this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x603F30 sub_603F30
// ------------------------------------------------------------
// 副职业四系标签解析：字符串证据「[craftmanship] [weaving] [machinary] [chemistry]」——
// 锻造/纺织/机械/化学四系熟练度参数（设计图/副职业材料的 0x60 区证据）。经 sub_43BCF0 入表。【推断】
bool /*thiscall*/ sub_603F30(int this)
{
  bool result; // al

  result = sub_43BCF0(*(void **)(this + 116), "[craftmanship]");
  if ( result )
  {
    *(uint32_t *)(this + 164) = 0;
  }
  else
  {
    result = sub_43BCF0(*(void **)(this + 116), "[weaving]");
    if ( result )
    {
      *(uint32_t *)(this + 164) = 1;
    }
    else
    {
      result = sub_43BCF0(*(void **)(this + 116), "[machinary]");
      if ( result )
      {
        *(uint32_t *)(this + 164) = 2;
      }
      else
      {
        result = sub_43BCF0(*(void **)(this + 116), "[chemistry]");
        if ( result )
          *(uint32_t *)(this + 164) = 3;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x603FB0 CNLotteryStackable__vmt88
// ------------------------------------------------------------
// CNLotteryStackable 激活（vmt88）：字符串证据「RECIPE_NOTICE」+ sub_484FA0（抽取器）。
// 罐头/盒子类抽取道具的激活与公告。
void */*thiscall*/ CNLotteryStackable__vmt88(void *this, int nArg2, int nArg3, int nArg4)
{
  void *result; // eax
  uint32_t *v6; // esi
  char *v7; // eax
  int v8; // esi
  uint32_t *v9; // esi
  char *v10; // eax

  result = (void *)CNRDStackable__vmt88(nArg2, nArg3, nArg4);
  if ( nArg3 == 2 )
  {
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
    {
      v8 = *((uint32_t *)dword_8F852C + 1);
      if ( v8 < sub_484FA0() )
      {
        return (void *)sub_44E8D0((char *)dword_8F8528, (void *)0x23, (int)this, 0);
      }
      else
      {
        v9 = *((uint32_t **)dword_8F8528 + 7);
        v10 = sub_422E70(1203);
        sub_43BEE0(v9, (int)v10, -6567706, 0, -1);
        return sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
      }
    }
    else
    {
      v6 = *((uint32_t **)dword_8F8528 + 7);
      v7 = sub_422E70(1202);
      sub_43BEE0(v6, (int)v7, -6567706, 0, -1);
      return sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x604080 CNAntiFreezePotion__vmt88
// ------------------------------------------------------------
// CNAntiFreezePotion 激活（vmt88，157 行）：sub_48C0A0 状态应用 + sub_510230（解冻判定【推断】）+ sub_6029D0
// （复用 CNActiveStatusStackable 的分发管线）——解冻药即『以道具激活路径驱动状态槽写入』的实例。
int /*thiscall*/ sub_604080(int this, int *pDwArg2, int nArg3, void *Block)  // 【CNAntiFreezePotion__vmt88】
{
  int *v6; // esi
  int result; // eax
  int *v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edi
  int v12; // eax
  unsigned int v13; // edx
  int v14; // ecx
  int v15; // edi
  int pThis2; // eax
  int v17; // edi
  uint64_t v18; // rax
  double v19; // st7
  double v20; // st7
  double v21; // st7
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // eax
  int *v26; // eax
  int v27; // edx
  int v28; // [esp-8h] [ebp-38h]
  int v29; // [esp+Ch] [ebp-24h] BYREF
  int v30; // [esp+10h] [ebp-20h]
  int v31; // [esp+14h] [ebp-1Ch]
  int v32; // [esp+18h] [ebp-18h]
  void *pMem; // [esp+1Ch] [ebp-14h]
  int pThis; // [esp+20h] [ebp-10h]
  int v35; // [esp+2Ch] [ebp-4h]
  int v36; // [esp+38h] [ebp+8h]
  int v37; // [esp+3Ch] [ebp+Ch]
  void *Blocka; // [esp+40h] [ebp+10h]

  pThis = this;
  sub_6029D0(this, pDwArg2, nArg3, (int)Block);  // 【CNActiveStatusStackable__vmt88】
  v6 = nullptr;
  if ( *(uint32_t *)(this + 180) == 0 )
  {
    result = *(uint8_t *)(this + 184);
    if ( (uint8_t)result == 0 )
    {
      v35 = 0;
      if ( operator new(0x60u) != nullptr )
        v8 = (int *)sub_510230(1, 1000, 3000);
      else
        v8 = nullptr;
      v9 = *v8;
      v35 = -1;
      return (*(int (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t, int))(v9 + 56))(
               v8,
               pDwArg2,
               pDwArg2,
               0,
               0,
               0,
               -1);
    }
    return result;
  }
  v10 = *pDwArg2;
  v29 = 0;
  v30 = 0;
  v31 = 0;
  v32 = 0;
  v11 = (*(int (/*thiscall*/ **)(int *))(v10 + 80))(pDwArg2);
  v12 = *(uint32_t *)(v11 + 120);
  Blocka = (void *)v11;
  if ( v12 != 0 )
    v36 = (*(uint32_t *)(v11 + 124) - v12) >> 2;
  else
    v36 = 0;
  result = v36;
  v13 = 0;
  v37 = 0;
  if ( v36 <= 0 )
    return result;
  while ( 2 )
  {
    v14 = *(uint32_t *)(v11 + 120);
    if ( v14 != 0 && v13 < (*(uint32_t *)(v11 + 124) - v14) >> 2 )
      v6 = *(int **)(v14 + 4 * v13);
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v6 + 40))(v6, 17) == 0 )
      goto LABEL_37;
    v15 = (*(int (/*thiscall*/ **)(int *))(*v6 + 376))(v6);
    if ( v15 != (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 376))(pDwArg2) )
      goto LABEL_36;
    pThis2 = pThis;
    if ( *(uint8_t *)(pThis + 184) != 0 && v6 == pDwArg2 )
      goto LABEL_36;
    v17 = 0;
    while ( 1 )
    {
      if ( v17 != 0 )
      {
        if ( v17 == 1 )
        {
          pMem = (void *)(2 * *(uint32_t *)(pThis2 + 180));
          v20 = (double)(int)pMem;
          v18 = (uint64_t)(0.88 * v20);
          v19 = v20 * 0.2552;
        }
        else
        {
          if ( v17 != 2 )
            goto LABEL_29;
          pMem = (void *)(2 * *(uint32_t *)(pThis2 + 180));
          v21 = (double)(int)pMem;
          v18 = (uint64_t)(0.60000002 * v21);
          v19 = v21 * 0.28999999;
        }
      }
      else
      {
        LODWORD(v18) = 2 * *(uint32_t *)(pThis2 + 180);
        pMem = (void *)v18;
        v19 = (double)(int)v18 * 0.17399999;
      }
      v31 = v18;
      v32 = (uint64_t)v19;
LABEL_29:
      v22 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 120))(pDwArg2);
      v23 = *pDwArg2;
      v29 = v22 - v31 / 2;
      v24 = (*(int (/*thiscall*/ **)(int *))(v23 + 124))(pDwArg2);
      v30 = v24 - v32 / 2;
      v28 = (*(int (/*thiscall*/ **)(int *))(*v6 + 124))(v6);
      v25 = (*(int (/*thiscall*/ **)(int *))(*v6 + 120))(v6);
      if ( (uint8_t)sub_48C0A0(v25, v28, &v29) != 0 )
        break;
      if ( ++v17 >= 3 )
        goto LABEL_36;
      pThis2 = pThis;
    }
    pMem = operator new(0x60u);
    v35 = 1;
    if ( pMem != nullptr )
      v26 = (int *)sub_510230(1, 1000, 3000);
    else
      v26 = nullptr;
    v27 = *v26;
    v35 = -1;
    (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t, int))(v27 + 56))(v26, v6, pDwArg2, 0, 0, 0, -1);
LABEL_36:
    v11 = (int)Blocka;
LABEL_37:
    result = ++v37;
    if ( v37 < v36 )
    {
      v13 = v37;
      v6 = nullptr;
      continue;
    }
    return result;
  }
}


// ------------------------------------------------------------
// 0x604310 sub_604310
// ------------------------------------------------------------
char /*thiscall*/ sub_604310(uint8_t *this)
{
  *(this + 3276) = 0;
  *(this + 3277) = 0;
  *(this + 3278) = 0;
  *(this + 3279) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x604330 sub_604330
// ------------------------------------------------------------
char /*thiscall*/ sub_604330(uint8_t *this, char pszArg2, char pszArg3)
{
  *(this + 3276) = pszArg2;
  *(this + 3277) = pszArg3;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x604350 CNSpecificEnemyEquipment__vmt88
// ------------------------------------------------------------
// CNSpecificEnemyEquipment 激活（vmt88）：sub_41A5E0（P24 防篡改写）+ sub_4EA220/sub_4EA7C0（怪物定义查询族）。
// 『对指定敌人加成』装备的生效路径【推断：按怪物 id 查表修正】。
char /*thiscall*/ CNSpecificEnemyEquipment__vmt88(char *this, int nArg2, int nArg3, int nArg4, char pszArg5, int pArg6)
{
  char result; // al

  result = *(this + 3276);
  if ( result != 0 )
  {
    if ( *(this + 3278) != 0 )
    {
      sub_4EA7C0(this + 212, this + 1380);
      if ( pArg6 != 0 )
      {
        *(uint32_t *)(pArg6 + 68) -= sub_41A5E0((unsigned int)(this + 2202));
        *(uint32_t *)(pArg6 + 64) -= sub_41A5E0((unsigned int)(this + 2188));
      }
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 321) + 676))(*((uint32_t *)this + 321), 0);
      *(this + 3278) = 0;
    }
    result = pszArg5;
    if ( pszArg5 != 0 )
    {
      result = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 304))(this, nArg2);
      if ( result != 0 )
      {
        sub_4EA220(this + 212, this + 1380);
        if ( pArg6 != 0 )
        {
          *(uint32_t *)(pArg6 + 68) += sub_41A5E0((unsigned int)(this + 2202));
          *(uint32_t *)(pArg6 + 64) += sub_41A5E0((unsigned int)(this + 2188));
        }
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 321) + 676))(*((uint32_t *)this + 321), 0);
        *(this + 3278) = 1;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x604440 CNSpecificEnemyEquipment__vmt8C
// ------------------------------------------------------------
// CNSpecificEnemyEquipment 查询槽（vmt8C）：sub_4EA220/sub_4EA7C0 同族 —— 装备条件的即时查询侧。
char /*thiscall*/ CNSpecificEnemyEquipment__vmt8C(char *this, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  char result; // al

  result = *(this + 3277);
  if ( result != 0 )
  {
    if ( *(this + 3279) != 0 )
    {
      sub_4EA7C0(this + 212, this + 2328);
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 321) + 676))(*((uint32_t *)this + 321), 0);
      *(this + 3279) = 0;
    }
    result = pszArg5;
    if ( pszArg5 != 0 )
    {
      result = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 304))(this, nArg2);
      if ( result != 0 )
      {
        sub_4EA220(this + 212, this + 2328);
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 321) + 676))(*((uint32_t *)this + 321), 0);
        *(this + 3279) = 1;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6044E0 sub_6044E0
// ------------------------------------------------------------
// 指定敌装备修正计算：sub_4B0D20/sub_4DAB60（combat_core 家族）——按目标类型折算伤害/命中修正【推断】。
// 被 vmt130（0x6045C0）每帧消费。
bool /*cdecl*/ sub_6044E0(int nArg1, int nArg2, int nArg3)
{
  bool result; // al
  int v4; // eax
  int v5; // eax

  switch ( nArg1 )
  {
    case 0:
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 40))(nArg3, nArg2) == 0 )
        goto LABEL_14;
      return true;
    case 1:
      if ( (uint8_t)sub_4DAB60(nArg2) == 0 )
        goto LABEL_14;
      return true;
    case 2:
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 368))(nArg3) != 0 )
        return nArg2 == 1;
      else
        return nArg2 == 0;
    case 3:
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 40))(nArg3, 17) == 0 )
        goto LABEL_14;
      v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 672))(nArg3, 3);
      if ( sub_4B0D20(v4) < nArg2 )
        goto LABEL_14;
      goto LABEL_11;
    case 4:
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 40))(nArg3, 17) == 0 )
        goto LABEL_14;
      v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 672))(nArg3, 3);
      if ( sub_4B0D20(v5) > nArg2 )
        goto LABEL_14;
LABEL_11:
      result = true;
      break;
    default:
LABEL_14:
      result = false;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6045C0 CNSpecificEnemyEquipment__vmt130
// ------------------------------------------------------------
// CNSpecificEnemyEquipment 周期槽（vmt130）→ 转调 sub_6044E0 修正计算。
char /*thiscall*/ CNSpecificEnemyEquipment__vmt130(int **this, int nArg2)
{
  int *fld_e338; // edi
  int *fld_e342; // ecx
  int *fld_e3422; // edi

  fld_e338 = *(this + 338);
  if ( fld_e338 != *(this + 339) )
  {
    while ( sub_6044E0(*fld_e338, fld_e338[1], nArg2) )
    {
      fld_e338 += 2;
      if ( fld_e338 == *(this + 339) )
        goto LABEL_4;
    }
    return 0;
  }
LABEL_4:
  fld_e342 = *(this + 342);
  if ( fld_e342 != nullptr && ((char *)*(this + 343) - (char *)fld_e342) >> 3 != 0 )
  {
    fld_e3422 = *(this + 342);
    if ( fld_e342 == *(this + 343) )
      return 0;
    while ( !sub_6044E0(*fld_e3422, fld_e3422[1], nArg2) )
    {
      fld_e3422 += 2;
      if ( fld_e3422 == *(this + 343) )
        return 0;
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x604670 CNSpecificStateEquipment__vmt9C
// ------------------------------------------------------------
// CNSpecificStateEquipment 条件槽（vmt9C）：sub_4EA220/sub_4EA7C0 —— 按『状态』而非敌人查表的装备变体。
char /*thiscall*/ CNSpecificStateEquipment__vmt9C(uint32_t *this, int nArg2)
{
  int fld_e314; // ecx
  char result; // al
  uint32_t *fld_e338; // edi
  char v6; // bl

  fld_e314 = *(this + 314);
  if ( fld_e314 == 0
    || (*(this + 315) - fld_e314) >> 2 == 0
    || (result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 224))(this)) != 0 )
  {
    fld_e338 = (uint32_t *)*(this + 338);
    v6 = 0;
    if ( fld_e338 == (uint32_t *)*(this + 339) )
    {
LABEL_15:
      result = *((uint8_t *)this + 2312);
      if ( result != 0 )
      {
        sub_4EA7C0(this + 53, this + 341);
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 321) + 676))(*(this + 321), 0);
        *((uint8_t *)this + 2312) = 0;
      }
    }
    else
    {
      while ( v6 == 0 )
      {
        if ( *fld_e338 == nArg2
          && (nArg2 != 8
           || fld_e338[1] == -1
           || fld_e338[1] == (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 321) + 908))(*(this + 321))) )
        {
          v6 = 1;
        }
        fld_e338 += 2;
        if ( fld_e338 == (uint32_t *)*(this + 339) )
        {
          if ( v6 == 0 )
            goto LABEL_15;
          break;
        }
      }
      result = *((uint8_t *)this + 2312);
      if ( result == 0 )
      {
        sub_4EA220(this + 53, this + 341);
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 321) + 676))(*(this + 321), 0);
        *((uint8_t *)this + 2312) = 1;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x604770 sub_604770
// ------------------------------------------------------------
void /*thiscall*/ sub_604770(void *this, int nArg2, int nArg3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = nArg2;
  v3[1] = nArg3;
  sub_474950((int)this + 1348, (int)v3);
}



// ------------------------------------------------------------
// 0x6047A0 sub_6047A0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_6047A0(int *this)
{
  int pObj3; // eax
  int pObj4; // eax
  int pObj2; // edi
  int pObj; // eax
  int v6; // ebx
  int pObj5; // eax
  float v9; // [esp+Ch] [ebp-1Ch]
  float v10; // [esp+10h] [ebp-18h]
  float v11; // [esp+14h] [ebp-14h]

  pObj3 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  v9 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 120))(pObj3);
  pObj4 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  v10 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 124))(pObj4);
  pObj2 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  pObj = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 192))(pObj) / 2;
  v11 = (float)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj2) + v6);
  pObj5 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  return (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 52))(pObj5) * (v11 + v10 + v9)
                          + (double)*(this + 338));
}



// ------------------------------------------------------------
// 0x604850 CNEventEquipment__vmtA0
// ------------------------------------------------------------
// CNEventEquipment 条件槽（vmtA0）：sub_6047A0 + dword_8F7A24+12（场景类型，P42）+ dword_8F8520 ——
// 活动装备的『场景条件』检查【推断：特定副本/活动期间生效】。
int /*thiscall*/ CNEventEquipment__vmtA0(int *this)
{
  unsigned int v2; // eax
  int result; // eax
  int *pThis; // ecx
  int v5; // edi
  int v6; // eax
  int v7; // eax

  nullsub_3();
  v2 = sub_6047A0(this);
  srand(v2);
  result = *(uint32_t *)(dword_8F7A24 + 12);
  if ( result == 2 )
    goto LABEL_2;
  if ( result == 4 || result == 6 || result == 3 )
  {
    if ( *(this + 359) != 4 )
    {
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
      pThis = this;
      if ( *(this + 359) != *(uint32_t *)(*(uint32_t *)(v7 + 44) + 4) )
        return (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      goto LABEL_3;
    }
LABEL_2:
    pThis = this;
LABEL_3:
    v5 = *this;
    v6 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 212))(pThis, 0, 0, 0, 0);
    return (*(int (/*thiscall*/ **)(int *, int, int))(v5 + 304))(this, 2, v6);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6048E0 sub_6048E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6048E0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  char *pThis_3; // edx
  int result; // eax

  pThis_3 = (char *)(this + 3 * nArg2);
  *((uint32_t *)pThis_3 + 343) = nArg3;
  *((uint32_t *)pThis_3 + 344) = nArg4;
  result = 3 * nArg2 + 345;
  *(this + result) = nArg5;
  return result;
}



// ------------------------------------------------------------
// 0x604920 CNEventEquipment__vmt138
// ------------------------------------------------------------
// CNEventEquipment 受击槽（vmt138 = 基类濒死/受击表现槽位）：sub_432FA0（UDP 广播）+ sub_4E4A50（动作包）+
// sub_605840（dword_9B9358..9B937C 全局块写入 = 活动装备的客户端聚合缓存【推断】）——活动装备触发时的全服广播编排。
int /*thiscall*/ CNEventEquipment__vmt138(uint32_t *this, int nArg2, int nArg3)
{
  int v4; // eax
  int pObj; // eax
  int result; // eax
  float *v7; // esi
  int *pThis_158; // ebx
  int v9; // ecx
  int v10; // edi
  int v11; // eax
  int v12; // [esp-2Ch] [ebp-50h]
  int v13; // [esp-24h] [ebp-48h]
  int v14; // [esp-20h] [ebp-44h]
  int v15; // [esp-1Ch] [ebp-40h]
  int nArg32; // [esp-10h] [ebp-34h]
  int v17; // [esp-Ch] [ebp-30h]
  uint32_t v18[5]; // [esp+4h] [ebp-20h]
  uint32_t *pThis; // [esp+18h] [ebp-Ch]
  int v20; // [esp+1Ch] [ebp-8h]
  int v21; // [esp+20h] [ebp-4h]

  v4 = *this;
  pThis = this;
  pObj = (*(int (/*fastcall*/ **)(uint32_t *))(v4 + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj);
  if ( (uint8_t)result != 0 )
  {
    v7 = (float *)nArg3;
    v18[0] = 42004;
    v18[1] = 42003;
    v18[2] = 42005;
    v18[3] = 42006;
    v18[4] = 48011;
    v21 = 0;
    pThis_158 = this + 344;
    do
    {
      v9 = pThis_158[1];
      v10 = *(pThis_158 - 1);
      v20 = *pThis_158;
      nArg3 = v9;
      sub_432FA0();
      if ( v10 != -1 && rand() % nArg3 < v20 )
      {
        nArg3 = 0;
        v17 = sub_605840(&nArg3, nArg2, v7, 1);
        nArg32 = nArg3;
        v15 = (uint64_t)v7[2];
        v14 = (uint64_t)v7[1];
        v13 = (uint64_t)*v7;
        v12 = v18[v21];
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 212))(pThis);
        sub_4E4A50(v11, v12, v10, v13, v14, v15, 1, 0, nArg32, v17);
      }
      result = v21 + 1;
      pThis_158 += 3;
      ++v21;
    }
    while ( v21 < 5 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x604A20 sub_604A20
// ------------------------------------------------------------
char */*cdecl*/ sub_604A20(char *pszArg1, char *pszArg2, const void *pArg3)
{
  char *result; // eax
  void *v4; // edi

  for ( result = pszArg1; result != pszArg2; result += 40 )
  {
    v4 = result;
    qmemcpy(v4, pArg3, 0x28u);
  }
  return result;
}



// ------------------------------------------------------------
// 0x604A50 CNEventEquipment__vmt94
// ------------------------------------------------------------
// CNEventEquipment 条件槽（vmt94 = 基类『不检查玩家』条件字节写，CNRDObject.h 定案）：sub_6047A0 同 0x604850。
char /*thiscall*/ CNEventEquipment__vmt94(int this)
{
  int fld_4E8; // ecx
  int fld_59C; // eax
  unsigned int v4; // eax
  int v5; // edi
  int pThis_D4; // eax

  fld_4E8 = *(uint32_t *)(this + 1256);
  if ( fld_4E8 == 0
    || (*(uint32_t *)(this + 1260) - fld_4E8) >> 2 == 0
    || (LOBYTE(fld_59C) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 224))(this), (uint8_t)fld_59C != 0) )
  {
    fld_59C = *(uint32_t *)(dword_8F7A24 + 12);
    if ( fld_59C == 4 || fld_59C == 6 || fld_59C == 3 )
    {
      LOBYTE(fld_59C) = *(uint8_t *)(this + 1432);
      if ( (uint8_t)fld_59C == 0 )
      {
        v4 = sub_6047A0((int *)this);
        srand(v4);
        if ( *(uint32_t *)(this + 1436) == 4
          || (fld_59C = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 44),
              *(uint32_t *)(this + 1436) == *(uint32_t *)(fld_59C + 4)) )
        {
          v5 = *(uint32_t *)this;
          pThis_D4 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, 0, 0, 0, 0);
          LOBYTE(fld_59C) = (*(int (/*thiscall*/ **)(int, int, int))(v5 + 304))(this, 2, pThis_D4);
          *(uint8_t *)(this + 1432) = 1;
          *(uint8_t *)(this + 1433) = 0;
        }
      }
    }
  }
  return fld_59C;
}



// ------------------------------------------------------------
// 0x604B10 CNEventEquipment__vmt88
// ------------------------------------------------------------
int /*thiscall*/ CNEventEquipment__vmt88(uint32_t *this, int nArg2, float *pArg3, int nArg4, int nArg5, int nArg6)
{
  int fld_e314; // ecx
  int result; // eax
  double fld_e337; // st7

  fld_e314 = *(this + 314);
  if ( fld_e314 == 0
    || (*(this + 315) - fld_e314) >> 2 == 0
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 224))(this)) != 0 )
  {
    fld_e337 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2) * (pArg3[2] + pArg3[1] + *pArg3)
       + (double)(int)*(this + 337);
    srand((uint64_t)fld_e337);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, float *, int, int, int))(*this + 304))(this, 0, nArg2, pArg3, nArg4, nArg5, nArg6);
    (*(void (/*thiscall*/ **)(uint32_t *, int, float *))(*this + 312))(this, nArg2, pArg3);
    result = *(this + 337) + 1;
    *(this + 337) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x604BB0 CNEventEquipment__vmt8C
// ------------------------------------------------------------
void /*thiscall*/ CNEventEquipment__vmt8C(uint32_t *this, int nArg2, float *pArg3, int nArg4, int nArg5)
{
  int fld_e314; // ecx
  int v7; // eax
  double fld_e338; // st7

  fld_e314 = *(this + 314);
  if ( fld_e314 == 0
    || (*(this + 315) - fld_e314) >> 2 == 0
    || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 224))(this) != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
    if ( *(uint8_t *)(v7 + 16) != 0 || *(float *)v7 > 0.0 )
    {
      fld_e338 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2) * (pArg3[2] + pArg3[1] + *pArg3)
         + (double)(int)*(this + 338);
      srand((uint64_t)fld_e338);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, float *, int, int, uint32_t))(*this + 304))(this, 1, nArg2, pArg3, nArg4, nArg5, 0);
      ++*(this + 338);
    }
  }
}



// ------------------------------------------------------------
// 0x604C60 sub_604C60
// ------------------------------------------------------------
char */*cdecl*/ sub_604C60(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg22; // edx
  char *result; // eax

  pszArg22 = pszArg2;
  result = pszArg3;
  while ( pszArg22 != pszArg1 )
  {
    pszArg22 -= 40;
    result -= 40;
    qmemcpy(result, pszArg22, 0x28u);
  }
  return result;
}



// ------------------------------------------------------------
// 0x604C90 sub_604C90
// ------------------------------------------------------------
char */*cdecl*/ sub_604C90(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg12; // edx
  char *result; // eax

  pszArg12 = pszArg1;
  for ( result = pszArg3; pszArg12 != pszArg2; result += 40 )
  {
    if ( result != nullptr )
      qmemcpy(result, pszArg12, 0x28u);
    pszArg12 += 40;
  }
  return result;
}



// ------------------------------------------------------------
// 0x604CD0 sub_604CD0
// ------------------------------------------------------------
char */*cdecl*/ sub_604CD0(char *pszArg1, char *pszArg2, const void *pArg3)
{
  char *result; // eax
  char *pszArg22; // edx

  result = pszArg2;
  if ( pszArg2 != nullptr )
  {
    pszArg22 = pszArg2;
    result = pszArg1;
    do
    {
      if ( result != nullptr )
        qmemcpy(result, pArg3, 0x28u);
      result += 40;
      --pszArg22;
    }
    while ( pszArg22 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x604D00 sub_604D00
// ------------------------------------------------------------
char /*thiscall*/ sub_604D00(uint32_t *this, int nArg2)
{
  uint32_t *fld_e361; // eax
  uint32_t *fld_e362; // ecx

  fld_e361 = (uint32_t *)*(this + 361);
  fld_e362 = (uint32_t *)*(this + 362);
  if ( fld_e361 == fld_e362 )
    return 0;
  while ( *fld_e361 != nArg2 )
  {
    if ( ++fld_e361 == fld_e362 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x604D30 CNEventEquipment__vmt90
// ------------------------------------------------------------
// CNEventEquipment 条件编排槽（vmt90 = 基类条件字节写 0x498F00 家族）：对多组条件做开关编排
// （无被调函数，纯字段操作 69 行）——活动装备多条件开关的位编排体。
uint32_t */*thiscall*/ CNEventEquipment__vmt90(int *this, uint32_t *uArg2, int nArg3)
{
  uint32_t *result; // eax
  uint32_t *fld_e362; // ecx
  int v6; // edx
  int pObj; // eax
  double v8; // st7
  int v9; // eax
  int pObj3; // eax
  double v11; // st7
  int v12; // eax
  int pObj2; // edi
  int pObj5; // eax
  int v15; // ebx
  int v16; // eax
  int v17; // edx
  int pObj4; // eax
  double fld_e338; // st7
  int v20; // edi
  int v21; // eax
  float v22; // [esp+4h] [ebp-18h] BYREF
  float v23; // [esp+8h] [ebp-14h]
  float v24; // [esp+Ch] [ebp-10h]
  int v25; // [esp+10h] [ebp-Ch]
  int v26; // [esp+14h] [ebp-8h]
  int v27; // [esp+18h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  if ( result != nullptr )
  {
    result = (uint32_t *)*(this + 361);
    fld_e362 = (uint32_t *)*(this + 362);
    if ( result != fld_e362 )
    {
      while ( *result != *uArg2 )
      {
        if ( ++result == fld_e362 )
          return result;
      }
      v6 = *this;
      v22 = 0.0;
      v23 = 0.0;
      v24 = 0.0;
      v25 = 0;
      v26 = 0;
      v27 = 0;
      pObj = (*(int (/*thiscall*/ **)(int *))(v6 + 212))(this);
      v8 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
      v9 = *this;
      v22 = v8;
      pObj3 = (*(int (/*thiscall*/ **)(int *))(v9 + 212))(this);
      v11 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 124))(pObj3);
      v12 = *this;
      v23 = v11;
      pObj2 = (*(int (/*thiscall*/ **)(int *))(v12 + 212))(this);
      pObj5 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 192))(pObj5) / 2;
      v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj2);
      v17 = *this;
      v24 = (float)(v16 + v15);
      pObj4 = (*(int (/*thiscall*/ **)(int *))(v17 + 212))(this);
      fld_e338 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 52))(pObj4) * (v24 + v23 + v22) + (double)*(this + 338);
      srand((uint64_t)fld_e338);
      v20 = *this;
      v21 = (*(int (/*thiscall*/ **)(int *, float *, uint32_t, uint32_t, uint32_t))(*this + 212))(this, &v22, 0, 0, 0);
      return (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int))(v20 + 304))(this, 4, v21);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x604E70 CNEventEquipment__vmt130
// ------------------------------------------------------------
// CNEventEquipment 触发槽（vmt130，139 行）：sub_4D6750（combat_core 反应族）+ sub_4E4A50（动作包）——
// 活动装备触发时的表现/广播主流程【推断：活动装备特效+发包】。
unsigned int /*thiscall*/ sub_604E70(unsigned int *this, int nArg2, int nArg3, float *pArg4, int nArg5, char pszArg6, int nArg7)  // 【CNEventEquipment__vmt130】
{
  int v7; // ebx
  unsigned int result; // eax
  int fld_e340; // edi
  int fld_e3402; // eax
  int fld_e3403; // ecx
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  int nRand; // edi
  int nRand2; // eax
  int v18; // edx
  int fld_e3404; // edi
  int v20; // ebx
  int v21; // eax
  int fld_e3405; // ecx
  int *fld_e3406; // edi
  int v24; // ebx
  int v25; // eax
  int pObj; // eax
  int pObj2; // eax
  int fld_e3407; // edi
  int v29; // eax
  int v30; // [esp-24h] [ebp-48h]
  int v31; // [esp-20h] [ebp-44h]
  int v32; // [esp-1Ch] [ebp-40h]
  int v33; // [esp-18h] [ebp-3Ch]
  int v34; // [esp-14h] [ebp-38h]
  int v35; // [esp-10h] [ebp-34h]
  int nRand22; // [esp+Ch] [ebp-18h] BYREF
  int nRand3; // [esp+10h] [ebp-14h]
  int v38; // [esp+14h] [ebp-10h]
  unsigned int v39; // [esp+18h] [ebp-Ch]
  int v40; // [esp+1Ch] [ebp-8h]
  int pObj3; // [esp+20h] [ebp-4h]

  v7 = 0;
  pObj3 = 0;
  v39 = 0;
  while ( 1 )
  {
    result = *(this + 340);
    v38 = v7;
    if ( result == 0 )
      return result;
    result = (int)(*(this + 341) - result) / 40;
    if ( v39 >= result )
      return result;
    fld_e340 = *(this + 340) + v7;
    if ( pszArg6 == *(uint8_t *)(fld_e340 + 24) && *(uint32_t *)fld_e340 == nArg2 )
    {
      LOBYTE(v40) = 0;
      if ( nArg2 != 2 && nArg2 != 3 && rand() % *(uint32_t *)(fld_e340 + 16) >= *(uint32_t *)(fld_e340 + 12) )
        goto LABEL_30;
      fld_e3402 = *(uint32_t *)(v7 + *(this + 340) + 8);
      if ( fld_e3402 != 0 )
      {
        if ( fld_e3402 > 0 && fld_e3402 <= 2 )
          pObj3 = nArg3;
      }
      else
      {
        pObj3 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
      }
      fld_e3403 = *(this + 340);
      v13 = *(uint32_t *)(fld_e3403 + v7 + 4);
      v14 = v7 + fld_e3403;
      if ( v13 != 0 )
      {
        v15 = v13 - 1;
        if ( v15 != 0 )
        {
          if ( v15 == 1 )
          {
            nRand3 = *(uint32_t *)(v14 + 32);
            nRand = nRand3;
            if ( nRand3 == -1 )
            {
              nRand = rand() % 17;
              nRand3 = nRand;
            }
            nRand2 = rand();
            v18 = *(uint32_t *)pObj3;
            nRand22 = nRand2;
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(v18 + 40))(pObj3, 17) != 0
              && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 776))(pObj3, nRand) == 0
              && (uint8_t)sub_4D6750(nRand, 100.0, (int)&nRand22) != 0 )
            {
              fld_e3404 = v7 + *(this + 340);
              v20 = *(uint32_t *)pObj3;
              v21 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
              (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(v20 + 768))(pObj3, nRand3, *(uint32_t *)(fld_e3404 + 20), v21);
              v7 = v38;
              goto LABEL_29;
            }
LABEL_26:
            LOBYTE(v40) = 0;
          }
LABEL_30:
          (*(void (/*thiscall*/ **)(unsigned int *, unsigned int, int))(*this + 308))(this, v39, v40);
          goto LABEL_31;
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 17) == 0 )
          goto LABEL_26;
        fld_e3405 = *(uint32_t *)(v7 + *(this + 340) + 28);
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e3405 + 80))(fld_e3405) != 0 )
          goto LABEL_26;
        fld_e3406 = *(int **)(*(this + 340) + v7 + 28);
        v24 = *fld_e3406;
        v25 = (*(int (/*thiscall*/ **)(unsigned int *, uint32_t, uint32_t, uint32_t, int))(*this + 212))(this, 0, 0, 0, -1);
        (*(void (/*thiscall*/ **)(int *, int, int))(v24 + 56))(fld_e3406, pObj3, v25);
        v7 = v38;
      }
      else
      {
        pObj = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )
        {
          pObj2 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
          fld_e3407 = *(this + 340) + v7;
          v35 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 152))(pObj2);
          v34 = (uint64_t)pArg4[2];
          v33 = (uint64_t)pArg4[1];
          v32 = (uint64_t)*pArg4;
          v31 = *(uint32_t *)(fld_e3407 + 20);
          v30 = *(uint32_t *)(fld_e3407 + 36);
          v29 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
          sub_4E4A50(v29, v30, v31, v32, v33, v34, v35, 0, 0, 0);
        }
      }
LABEL_29:
      LOBYTE(v40) = 1;
      goto LABEL_30;
    }
LABEL_31:
    ++v39;
    v7 += 40;
  }
}


// ------------------------------------------------------------
// 0x6050F0 sub_6050F0
// ------------------------------------------------------------
// 活动装备全局块读取：dword_9B9360..9B937C（word_9B935C/E）10 字段聚合返回 —— sub_605840 写入侧的读出侧。
unsigned int /*thiscall*/ sub_6050F0(unsigned int *this)
{
  unsigned int v1; // edi
  int i; // ebx
  unsigned int result; // eax
  int fld_e340; // eax
  int v6; // ecx
  int v7; // eax

  v1 = 0;
  for ( i = 0; ; i += 40 )
  {
    result = *(this + 340);
    if ( result == 0 )
      break;
    result = (int)(*(this + 341) - result) / 40;
    if ( v1 >= result )
      break;
    fld_e340 = *(this + 340);
    v6 = *(uint32_t *)(fld_e340 + i + 4);
    v7 = i + fld_e340;
    if ( v6 == 1 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v7 + 28) + 76))(*(uint32_t *)(v7 + 28), 0);
    ++v1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x605150 sub_605150
// ------------------------------------------------------------
char */*stdcall*/ sub_605150(char *pszArg1, char *pszArg2, const void *pArg3)
{
  sub_604CD0(pszArg1, pszArg2, pArg3);
  return &pszArg1[40 * (uint32_t)pszArg2];
}



// ------------------------------------------------------------
// 0x605180 CNEventEquipment__vmt98
// ------------------------------------------------------------
char /*thiscall*/ CNEventEquipment__vmt98(int this)
{
  int v1; // eax
  unsigned int v3; // eax
  int v4; // edi
  int pThis_D4; // eax

  v1 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v1 == 4 || v1 == 6 || v1 == 3 )
  {
    LOBYTE(v1) = *(uint8_t *)(this + 1433);
    if ( (uint8_t)v1 == 0 )
    {
      v3 = sub_6047A0((int *)this);
      srand(v3);
      v4 = *(uint32_t *)this;
      pThis_D4 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int, int, int))(v4 + 304))(this, 3, pThis_D4);
      LOBYTE(v1) = sub_6050F0((unsigned int *)this);
      *(uint8_t *)(this + 1432) = 0;
      *(uint8_t *)(this + 1433) = 1;
    }
  }
  return v1;
}



// ------------------------------------------------------------
// 0x6051F0 sub_6051F0
// ------------------------------------------------------------
// 活动装备注册表重建：sub_50F360/sub_5721D0 + sub_604A20/604C60/604C90/604CD0/605150 五个装载器 ——
// 启动/换图时重建 dword_9B93xx 全局装备聚合缓存【推断】。
void /*thiscall*/ sub_6051F0(int this, char *pszArg2, unsigned int uArg3, void *Block)
{
  int fld_4; // edi
  unsigned int fld_C; // ecx
  int fld_8; // eax
  int fld_82; // eax
  unsigned int v10; // ecx
  int fld_87; // eax
  int v12; // edi
  int fld_43; // eax
  unsigned int v14; // esi
  char *fld_83; // ecx
  int fld_86; // esi
  char *fld_42; // [esp-18h] [ebp-5Ch]
  char *fld_85; // [esp-Ch] [ebp-50h]
  char *fld_84; // [esp-8h] [ebp-4Ch]
  int v21; // [esp+0h] [ebp-44h] BYREF
  uint32_t v22[11]; // [esp+Ch] [ebp-38h] BYREF
  int v23; // [esp+40h] [ebp-4h]
  char *v24; // [esp+4Ch] [ebp+8h]
  char *v25; // [esp+50h] [ebp+Ch]
  char *Blocka; // [esp+54h] [ebp+10h]
  char *Blockb; // [esp+54h] [ebp+10h]

  qmemcpy(v22, Block, 0x28u);
  fld_4 = *(uint32_t *)(this + 4);
  v22[10] = &v21;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) / 40;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 40;
    else
      fld_8 = 0;
    if ( 107374182 - fld_8 < uArg3 )
      sub_50F360(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) / 40;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(char **)(this + 8);
      Blockb = fld_83;
      if ( (fld_83 - pszArg2) / 40 >= uArg3 )
      {
        v24 = &fld_83[-40 * uArg3];
        *(uint32_t *)(this + 8) = sub_604C90(v24, fld_83, fld_83);
        sub_604C60(pszArg2, v24, Blockb);
        sub_604A20(pszArg2, &pszArg2[40 * uArg3], v22);
      }
      else
      {
        sub_604C90(pszArg2, fld_83, &pszArg2[40 * uArg3]);
        fld_84 = (char *)(uArg3 - (*(uint32_t *)(this + 8) - (int)pszArg2) / 40);
        fld_85 = *(char **)(this + 8);
        v23 = 2;
        sub_605150(fld_85, fld_84, v22);
        fld_86 = 40 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        sub_604A20(pszArg2, (char *)(fld_86 - 40 * uArg3), v22);
      }
    }
    else
    {
      if ( 107374182 - (fld_C >> 1) >= fld_C )
        v10 = (fld_C >> 1) + fld_C;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) / 40;
      else
        fld_87 = 0;
      if ( v10 < uArg3 + fld_87 )
        v10 = uArg3 + sub_5721D0(this);
      v12 = 40 * v10;
      Blocka = (char *)operator new(40 * v10);
      fld_42 = *(char **)(this + 4);
      v23 = 0;
      v25 = sub_604C90(fld_42, pszArg2, Blocka);
      sub_604CD0(v25, (char *)uArg3, v22);
      sub_604C90(pszArg2, *(char **)(this + 8), &v25[40 * uArg3]);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_43 = (*(uint32_t *)(this + 8) - fld_43) / 40;
      v14 = fld_43 + uArg3;
      if ( *(uint32_t *)(this + 4) != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &Blocka[v12];
      *(uint32_t *)(this + 8) = &Blocka[40 * v14];
      *(uint32_t *)(this + 4) = Blocka;
    }
  }
}



// ------------------------------------------------------------
// 0x6054A0 sub_6054A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6054A0(uint32_t *this, uint32_t *uArg2, char *pszArg3, void *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 40 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 40;
  else
    v6 = 0;
  sub_6051F0((int)this, pszArg3, 1u, Block);
  *uArg2 = *(this + 1) + 40 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x605510 sub_605510
// ------------------------------------------------------------
char */*thiscall*/ sub_605510(int this, void *Block)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  char *fld_82; // edi
  char *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 40;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 40 )
    return (char *)sub_6054A0((uint32_t *)this, &Block, *(char **)(this + 8), Block);
  fld_82 = *(char **)(this + 8);
  result = sub_604CD0(fld_82, (char *)1, Block);
  *(uint32_t *)(this + 8) = fld_82 + 40;
  return result;
}



// ------------------------------------------------------------
// 0x6055A0 sub_6055A0
// ------------------------------------------------------------
char */*thiscall*/ sub_6055A0(void *this, int nArg2, int nArg3, int nArg4, int nArg5, char pszArg6, int nArg7)
{
  uint32_t Block[6]; // [esp+0h] [ebp-28h] BYREF
  char pszArg62; // [esp+18h] [ebp-10h]
  int nArg72; // [esp+24h] [ebp-4h]

  Block[0] = nArg2;
  Block[4] = nArg4;
  Block[3] = nArg3;
  pszArg62 = pszArg6;
  Block[5] = nArg5;
  Block[1] = 0;
  nArg72 = nArg7;
  return sub_605510((int)this + 1356, Block);
}



// ------------------------------------------------------------
// 0x6055F0 sub_6055F0
// ------------------------------------------------------------
char */*thiscall*/ sub_6055F0(void *this, int nArg2, int nArg3, int nArg4, char pszArg5, uint32_t *uArg6, int nArg7)
{
  int v8; // edx
  uint32_t Block[6]; // [esp+4h] [ebp-28h] BYREF
  char pszArg52; // [esp+1Ch] [ebp-10h]
  uint32_t *uArg62; // [esp+20h] [ebp-Ch]

  Block[2] = nArg7;
  pszArg52 = pszArg5;
  Block[0] = nArg2;
  Block[3] = nArg3;
  v8 = *uArg6;
  Block[1] = 1;
  Block[4] = nArg4;
  uArg62 = uArg6;
  *(uint8_t *)((*(int (**)(void))(v8 + 64))() + 36) = 0;
  return sub_605510((int)this + 1356, Block);
}



// ------------------------------------------------------------
// 0x605650 sub_605650
// ------------------------------------------------------------
char */*thiscall*/ sub_605650(void *this, int nArg2, int nArg3, int nArg4, int nArg5, char pszArg6, int nArg7, int nArg8)
{
  uint32_t Block[6]; // [esp+0h] [ebp-28h] BYREF
  char pszArg62; // [esp+18h] [ebp-10h]
  int nArg72; // [esp+20h] [ebp-8h]

  Block[2] = nArg8;
  Block[0] = nArg2;
  Block[4] = nArg4;
  Block[3] = nArg3;
  pszArg62 = pszArg6;
  Block[5] = nArg5;
  Block[1] = 2;
  nArg72 = nArg7;
  return sub_605510((int)this + 1356, Block);
}



// ------------------------------------------------------------
// 0x6056A0 sub_6056A0
// ------------------------------------------------------------
void /*thiscall*/ sub_6056A0(float *this, int nArg2)
{
  *(this + 181) = (float)nArg2;
}



// ============================================================
// 【分区 4】临时判定与霸体 PO（0x6056B0-0x605FD0）
// CNTemporaryHit（一次性 hitbox）/ CNSuperArmor（霸体光环，SuperArmorEffect/SuperArmorBody 双动画）
// ============================================================
// ------------------------------------------------------------
// 0x6056B0 CNTemporaryHit__vmt2BC
// ------------------------------------------------------------
// CNTemporaryHit 命中结算槽（vmt2BC）：sub_45EBE0（飘字/伤害参数）+ sub_4E5F70（硬直率掷，§5.1），
// 消费全局攻击上下文 dword_78FE30/78FE34【推断：伤害倍率对】。
// 语义：『打一下即消失』的临时判定体（一次性 hitbox PO）的结算出口。
int /*thiscall*/ CNTemporaryHit__vmt2BC(uint32_t *this, const void *pArg2, int Size)
{
  int fld_e29; // eax
  int v5; // eax
  char v6; // cl
  int16_t v7; // cx
  float v9[8]; // [esp+Ch] [ebp-20h] BYREF

  CNRDPassiveObject__vmt2BC((int)pArg2, Size);
  dword_78FE30 = (int)pArg2;
  dword_78FE34 = 0;
  if ( Size > 0 )
  {
    qmemcpy(v9, pArg2, 0x1Eu);
    dword_78FE34 = 30;
    if ( LOBYTE(v9[7]) == 0 )
      *(this + 196) = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      fld_e29 = sub_45EBE0((uint32_t *)*(this + 29), LOWORD(v9[0]), HIWORD(v9[0]));
      v5 = __RTDynamicCast(fld_e29, 0, &CNRDObject `RTTI Type Descriptor', &IRDCollisionObject `RTTI Type Descriptor', 0);
      if ( v5 != 0 )
        sub_4E5F70((int)this, (int)this, v5, &v9[1], 1, 1);
      else
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
    if ( dword_78FE34 < Size )
    {
      v6 = *(uint8_t *)(dword_78FE34 + dword_78FE30);
      ++dword_78FE34;
      *((uint8_t *)this + 740) = v6 == 1;
      if ( dword_78FE34 < Size )
      {
        v7 = *(uint16_t *)(dword_78FE34 + dword_78FE30);
        dword_78FE34 += 2;
        *(this + 183) = v7;
        if ( dword_78FE34 < Size )
        {
          *(this + 218) = *(uint32_t *)(dword_78FE34 + dword_78FE30);
          dword_78FE34 += 4;
        }
      }
    }
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*this + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x605800 CNTemporaryHit__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNTemporaryHit__vmt1F4(int *this, uint32_t *uArg2, float *pArg3, char pszArg4)
{
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  return CNRDPassiveObject__vmt1F4(this, uArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x605840 sub_605840
// ------------------------------------------------------------
int16_t */*cdecl*/ sub_605840(uint32_t *uArg1, int nArg2, int *pDwArg3, char pszArg4)
{
  int v4; // edx

  if ( (dword_9B937C & 1) == 0 )
  {
    dword_9B937C |= 1u;
    dword_9B9360 = 0;
    dword_9B9364 = 0;
    dword_9B9368 = 0;
    dword_9B936C = 0;
    dword_9B9370 = 0;
    dword_9B9374 = 0;
  }
  word_9B935C = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 48))(nArg2);
  word_9B935E = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2);
  dword_9B9360 = *pDwArg3;
  dword_9B9364 = pDwArg3[1];
  dword_9B9368 = pDwArg3[2];
  dword_9B936C = pDwArg3[3];
  dword_9B9370 = pDwArg3[4];
  v4 = pDwArg3[5];
  byte_9B9378 = pszArg4;
  dword_9B9374 = v4;
  *uArg1 = 30;
  return &word_9B935C;
}



// ------------------------------------------------------------
// 0x605910 sub_605910
// ------------------------------------------------------------
void /*thiscall*/ sub_605910(uint32_t *this)
{
  *(this + 20) = 0;
}



// ------------------------------------------------------------
// 0x605920 CNSuperArmor__vmt4
// ------------------------------------------------------------
int /*thiscall*/ CNSuperArmor__vmt4(int *this)
{
  int fld_e1; // esi
  int result; // eax

  IRDAppendage__vmt4(this);
  fld_e1 = *(this + 1);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 616))(fld_e1) == 0
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 620))(fld_e1) != 1 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)fld_e1 + 612))(fld_e1, 1, 1);
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 724))(fld_e1);
  if ( (uint8_t)result == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 288))(fld_e1) == 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)fld_e1 + 284))(fld_e1, 1, -16776961, 1, 2);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 292))(fld_e1);
    if ( result != -16776961 )
      return (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)fld_e1 + 284))(fld_e1, 1, -16776961, 1, 2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6059A0 CNSuperArmor__vmt20
// ------------------------------------------------------------
char /*thiscall*/ CNSuperArmor__vmt20(uint32_t **this, char pszArg2)
{
  char result; // al

  result = pszArg2;
  if ( pszArg2 == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(**(this + 1) + 612))(*(this + 1), 0, 0);
    return (*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(**(this + 1) + 284))(*(this + 1), 0, 0, 1, 2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6059E0 CNSuperArmor__vmt14
// ------------------------------------------------------------
char /*thiscall*/ CNSuperArmor__vmt14(int *this, char pszArg2, int nArg3, int nArg4, float fArg5)
{
  char result; // al
  int *i; // esi

  result = pszArg2;
  if ( pszArg2 != 0 )
  {
    for ( i = (int *)*(this + 22); i != (int *)*(this + 23); ++i )
    {
      sub_4938F0(*i);
      if ( *(uint8_t *)(*i + 170) == 0 )
        sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);
    }
    sub_4938F0(*(this + 20));
    result = *(uint8_t *)(*(this + 20) + 170);
    if ( result == 0 )
      return sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);
  }
  return result;
}



// ------------------------------------------------------------
// 0x605A70 CNSuperArmor__vmt54
// ------------------------------------------------------------
char /*thiscall*/ CNSuperArmor__vmt54(int this, char pszArg2)
{
  int *i; // esi

  IRDAppendage__vmt54((uint8_t *)this, pszArg2);
  for ( i = *(int **)(this + 88); i != *(int **)(this + 92); ++i )
    sub_4939E0(*i, pszArg2);
  return sub_4939E0(*(uint32_t *)(this + 80), pszArg2);
}



// ------------------------------------------------------------
// 0x605AC0 sub_605AC0
// ------------------------------------------------------------
int /*thiscall*/ sub_605AC0(uint32_t *this)
{
  int v2; // eax
  int result; // eax

  v2 = sub_42FCB0(228);
  if ( v2 != 0 )
  {
    result = sub_431860(v2, "Common/CommonEffect/Animation/SuperArmorEffect.ani", 1);
    *(this + 20) = result;
  }
  else
  {
    *(this + 20) = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x605B30 sub_605B30
// ------------------------------------------------------------
// 霸体状态辅助：sub_42AF90（动画对象操作）+ sub_657740（资源/音效释放【推断】）——
// CNSuperArmor 状态切换的公共收尾（被 vmt1C/vmt20/vmt14 多处调用）。
void /*thiscall*/ sub_605B30(int this)
{
  int fld_50; // esi
  void ***fld_58; // esi
  bool fld_5C; // zf
  void **v5; // ebx

  fld_50 = *(uint32_t *)(this + 80);
  if ( fld_50 != 0 )
  {
    sub_42AF90(*(void ***)(this + 80));
    sub_657740(fld_50, 228);
  }
  fld_58 = *(void ****)(this + 88);
  fld_5C = fld_58 == *(void ****)(this + 92);
  *(uint32_t *)(this + 80) = 0;
  if ( !fld_5C )
  {
    do
    {
      v5 = *fld_58;
      if ( *fld_58 != nullptr )
      {
        sub_42AF90(*fld_58);
        sub_657740(v5, 228);
      }
      *fld_58++ = nullptr;
    }
    while ( fld_58 != *(void ****)(this + 92) );
  }
  if ( *(uint32_t *)(this + 88) != 0 )
    j__free(*(void **)(this + 88));
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
}



// ------------------------------------------------------------
// 0x605BB0 CNSuperArmor__vmt1C
// ------------------------------------------------------------
// CNSuperArmor 周期槽（vmt1C）：字符串证据「SUPERARMOR」（音效 TAG）。
// sub_4920E0/sub_4926A0（定时器复位，vmtCC 族）/sub_4938F0（动画复位）——霸体光环的周期维持与超时解除。
int /*thiscall*/ CNSuperArmor__vmt1C(void *this)
{
  void ***i; // edi
  void **v3; // ebx
  int pThis_1; // eax
  int pThis_13; // ebx
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  int v8; // ecx
  int v9; // ecx
  int v11; // [esp+Ch] [ebp-4h]
  int v12; // [esp+Ch] [ebp-4h]
  float pThis_12; // [esp+Ch] [ebp-4h]

  for ( i = *((void ****)this + 22); i != *((void ****)this + 23); ++i )
  {
    v3 = *i;
    if ( *i != nullptr )
    {
      sub_42AF90(*i);
      sub_657740(v3, 228);
    }
    *i = nullptr;
  }
  if ( *((uint32_t *)this + 22) != 0 )
    j__free(*((void **)this + 22));
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 24) = 0;
  pThis_1 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1) + 200))(*((uint32_t *)this + 1));
  pThis_13 = pThis_1;
  if ( pThis_1 != 0 )
  {
    v6 = *(uint32_t **)(pThis_1 + 204);
    v7 = (uint32_t *)*v6;
    if ( (uint32_t *)*v6 != v6 )
    {
      do
      {
        if ( (int)v7[2] >= 0 )
          break;
        v8 = v7[3];
        v11 = v8;
        if ( *(uint32_t *)(v8 + 148) == -1 )
        {
          sub_4938F0(v8);
          v8 = v11;
        }
        (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 120))(this, v8 + 60);
        v7 = (uint32_t *)*v7;
      }
      while ( v7 != *(uint32_t **)(pThis_13 + 204) );
    }
    if ( *(uint32_t *)(pThis_13 + 148) == -1 )
      sub_4938F0(pThis_13);
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 120))(this, pThis_13 + 60);
    for ( ; v7 != *(uint32_t **)(pThis_13 + 204); v7 = (uint32_t *)*v7 )
    {
      v9 = v7[3];
      v12 = v9;
      if ( *(uint32_t *)(v9 + 148) == -1 )
      {
        sub_4938F0(v9);
        v9 = v12;
      }
      (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 120))(this, v9 + 60);
    }
  }
  pThis_12 = (double)(*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1) + 192))(*((uint32_t *)this + 1)) * 0.0071428572;
  sub_4920E0(*((uint32_t **)this + 20), pThis_12, pThis_12);
  sub_4926A0(*((uint32_t *)this + 20));
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**((uint32_t **)this + 1) + 212))(
           *((uint32_t *)this + 1),
           "SUPERARMOR",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x605D10 CNSuperArmor__vmt78
// ------------------------------------------------------------
// CNSuperArmor 表现槽（vmt78 = 基类调 vt+116(0) 槽位）：字符串证据「Common/CommonEffect/Animation/SuperArmorBody.ani」。
// sub_42AC90/sub_42FCB0（资源 228 门）/sub_431860（.ani 生成，P41）/sub_4924C0 —— 霸体躯体附体动画的生成与绑定。
// SuperArmorEffect.ani（0x6059A0 侧）+ 本体两层动画构成霸体双表现。
void /*thiscall*/ CNSuperArmor__vmt78(uint32_t **this, int pArg2)
{
  int v3; // ebx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // esi
  bool v8; // cc
  uint32_t *v9; // edi
  char *v10; // eax
  unsigned int v11; // esi
  int *v12; // edx
  int v13; // [esp+8h] [ebp-1Ch] BYREF
  int v14; // [esp+Ch] [ebp-18h]
  uint32_t **pThis; // [esp+10h] [ebp-14h]
  int v16; // [esp+14h] [ebp-10h]
  int v17; // [esp+20h] [ebp-4h]
  int v18; // [esp+2Ch] [ebp+8h]

  v3 = 0;
  pThis = this;
  if ( pArg2 != 0 )
  {
    v4 = sub_42FCB0(228);
    v17 = 0;
    if ( v4 != 0 )
    {
      v5 = sub_431860(v4, "Common/CommonEffect/Animation/SuperArmorBody.ani", 1);
      v18 = v5;
    }
    else
    {
      v18 = 0;
      v5 = 0;
    }
    v6 = *(uint32_t *)(v5 + 44);
    v17 = -1;
    v13 = v5;
    if ( v6 != 0 )
      v16 = (*(uint32_t *)(v5 + 48) - v6) / 88;
    else
      v16 = 0;
    if ( v16 > 0 )
    {
      do
      {
        v7 = sub_4924C0(v3);
        *(uint32_t *)v7 = *(uint32_t *)pArg2;
        *(uint32_t *)(v7 + 12) = *(uint32_t *)(pArg2 + 12);
        *(uint32_t *)(v7 + 16) = *(uint32_t *)(pArg2 + 16);
        if ( v3 < 2 )
        {
          v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis[1] + 192))(pThis[1]);
          *(uint32_t *)(v7 + 16) += (uint64_t)((double)v14
                                                   * ((*(float *)(v7 + 24) - 1.0)
                                                    / *(float *)(pArg2 + 24))
                                                   * 0.40000001);
        }
        v5 = v18;
        v8 = ++v3 < v16;
        *(float *)(v7 + 20) = *(float *)(v7 + 20) * *(float *)(pArg2 + 20);
        *(float *)(v7 + 24) = *(float *)(v7 + 24) * *(float *)(pArg2 + 24);
      }
      while ( v8 );
    }
    v9 = pThis[22];
    v10 = (char *)(pThis + 21);
    if ( v9 != nullptr )
      v11 = pThis[23] - v9;
    else
      v11 = 0;
    if ( v9 != nullptr && v11 < pThis[24] - v9 )
    {
      v12 = pThis[23];
      *v12 = v5;
      *((uint32_t *)v10 + 2) = v12 + 1;
    }
    else
    {
      sub_42AC90((int)(pThis + 21), (char *)pThis[23], 1u, &v13);
    }
  }
}



// ------------------------------------------------------------
// 0x605E80 sub_605E80
// ------------------------------------------------------------
int /*thiscall*/ sub_605E80(int this)
{
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint8_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x605EB0 sub_605EB0
// ------------------------------------------------------------
// 霸体数值辅助（纯字段操作 40 行）：霸体剩余量/层次计数的多槽位读写【推断：霸体叠加层数管理】。
int /*thiscall*/ sub_605EB0(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e9)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  uint32_t *pThis_C; // edi
  int i; // ebx
  void (/*thiscall*/ ***fld_e14)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e15)(uint32_t, int); // ecx
  int result; // eax

  fld_e9 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( fld_e9 != nullptr )
    (**fld_e9)(fld_e9, 1);
  fld_e10 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 9) = 0;
  if ( fld_e10 != nullptr )
    (**fld_e10)(fld_e10, 1);
  fld_e11 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( fld_e11 != nullptr )
    (**fld_e11)(fld_e11, 1);
  *(this + 11) = 0;
  pThis_C = this + 12;
  for ( i = 2; i != 0; --i )
  {
    if ( *pThis_C != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_C)(*pThis_C, 1);
    *pThis_C++ = 0;
  }
  fld_e14 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  if ( fld_e14 != nullptr )
    (**fld_e14)(fld_e14, 1);
  fld_e15 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  result = 0;
  *(this + 14) = 0;
  if ( fld_e15 != nullptr )
    result = (**fld_e15)(fld_e15, 1);
  *(this + 15) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x605F40 sub_605F40
// ------------------------------------------------------------
int /*thiscall*/ sub_605F40(uint32_t *this)
{
  int fld_e2; // eax
  LONG v2; // ecx
  LONG v3; // edx
  int result; // eax
  LONG i; // esi

  fld_e2 = *(this + 2);
  v2 = *(uint32_t *)(fld_e2 + 24) + 31;
  v3 = *(uint32_t *)(fld_e2 + 20) + 7;
  result = 0;
  for ( i = v2 + 18; pt.x < v3 || pt.x >= v3 + 177 || pt.y < v2 || pt.y >= i; i += 19 )
  {
    ++result;
    v2 += 19;
    if ( result >= 10 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x605FA0 sub_605FA0
// ------------------------------------------------------------
bool /*thiscall*/ sub_605FA0(uint32_t *this)
{
  int fld_e1; // edx

  fld_e1 = *(this + 1);
  return fld_e1 == 0 || (*(this + 2) - fld_e1) >> 3 == 0;
}



// ============================================================
// 【分区 5】NPC 对话窗 CNRDDialogueWindow（0x605FD0-0x607420）
// UI 类混入本区：控件树重建/对话树遍历/按钮处理。
// 字符串证据：调试断言「if (g_userManager->getMyUser() == NULL)」、音效 TAG CLICK_BUTTON2
// ============================================================
// ------------------------------------------------------------
// 0x605FD0 CNRDDialogueWindow__vmt0
// ------------------------------------------------------------
// CNRDDialogueWindow 析构（vmt0 标量删除析构）：sub_491530 = 研究 20 P37-5 定案的渲染状态消费点
// （枚举→D3D 渲染状态映射表）+ sub_491630 + sub_605F40/sub_69C690（UI 控件释放）——对话窗关闭时恢复渲染状态并析构控件树。
char /*thiscall*/ CNRDDialogueWindow__vmt0(int this, int pArg2)
{
  unsigned int fld_B4; // eax
  int v4; // edi
  int v5; // ebx
  int pObj; // eax
  int pThis_84; // ecx
  unsigned int fld_3C; // edi
  int fld_B0; // ecx
  int v10; // edi
  int fld_B02; // eax
  int fld_B03; // eax
  unsigned int v13; // ecx
  int v14; // eax
  int v15; // eax
  int pObj2; // eax
  bool v17; // cc
  unsigned int fld_B42; // [esp+8h] [ebp-10h]
  int v20; // [esp+Ch] [ebp-Ch]
  int v21; // [esp+10h] [ebp-8h]
  unsigned int fld_3C2; // [esp+14h] [ebp-4h]
  int v23; // [esp+20h] [ebp+8h]

  LOBYTE(fld_B4) = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(uint32_t *)(this + 8) )
  {
    v4 = *(uint32_t *)(pArg2 + 20);
    v5 = *(uint32_t *)(pArg2 + 24);
    pObj = sub_418DD0(109);
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v4 + 5, v5 + 5, dword_79C0B0);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 68);
    if ( *(uint32_t *)(this + 152) < 0x10u )
      pThis_84 = this + 132;
    else
      pThis_84 = *(uint32_t *)(this + 132);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v4 + 34,
      v5 + 11,
      -6632219,
      pThis_84);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    LOBYTE(fld_B4) = *(uint8_t *)(this + 188);
    if ( (uint8_t)fld_B4 == 0 )
    {
      v20 = v4 + 7;
      v21 = v5 + 31;
      fld_3C = sub_69C690(*(uint32_t *)(this + 60));
      fld_3C2 = fld_3C;
      fld_B4 = sub_605F40((uint32_t *)this);
      fld_B42 = fld_B4;
      v23 = 0;
      while ( 1 )
      {
        fld_B0 = *(uint32_t *)(this + 176);
        if ( fld_B0 == 0 )
          break;
        fld_B4 = (*(uint32_t *)(this + 180) - fld_B0) >> 3;
        if ( fld_3C >= fld_B4 )
          break;
        v10 = 8 * fld_3C;
        fld_B02 = sub_418DD0(120 - (*(uint32_t *)(v10 + *(uint32_t *)(this + 176) + 4) != 0));
        if ( fld_B02 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_B02 + 152))(fld_B02, v20 + 3, v21 + 3, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
        fld_B03 = *(uint32_t *)(v10 + *(uint32_t *)(this + 176));
        v13 = *(uint32_t *)(fld_B03 + 36);
        v14 = fld_B03 + 12;
        if ( v13 < 0x10 )
          v15 = v14 + 4;
        else
          v15 = *(uint32_t *)(v14 + 4);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v20 + 19,
          v21 + 4,
          -1,
          v15);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        if ( v23 == fld_B42 )
        {
          sub_491530(2, 0);
          pObj2 = sub_418DD0(121);
          if ( pObj2 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v20, v21, dword_79C0B0);
          sub_491630(2);
        }
        LOBYTE(fld_B4) = v23 + 1;
        v17 = ++v23 < 10;
        ++fld_3C2;
        v21 += 19;
        if ( !v17 )
          break;
        fld_3C = fld_3C2;
      }
    }
  }
  return fld_B4;
}



// ------------------------------------------------------------
// 0x6061D0 sub_6061D0
// ------------------------------------------------------------
// 对话窗辅助：无外部调用的字段操作（29 行）——【推断：当前选项/页索引推进】。
int **/*thiscall*/ sub_6061D0(int **this, int **pDwArg2, uint32_t *uArg3)
{
  int *fld_e1; // edx
  int *v4; // eax

  fld_e1 = *(this + 1);
  v4 = (int *)fld_e1[1];
  while ( *((uint8_t *)v4 + 101) == 0 )
  {
    if ( v4[3] >= *uArg3 )
    {
      fld_e1 = v4;
      v4 = (int *)*v4;
    }
    else
    {
      v4 = (int *)v4[2];
    }
  }
  if ( fld_e1 == *(this + 1) || *uArg3 < fld_e1[3] )
  {
    *pDwArg2 = *(this + 1);
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = fld_e1;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x606240 CNRDDialogueWindow__vmt14
// ------------------------------------------------------------
// CNRDDialogueWindow 每帧表现槽（vmt14）：dword_8F8520（主管理器）联动 ——
// 【推断：对话窗跟随 NPC/打字机刷新 tick】。
char /*usercall*/ CNRDDialogueWindow__vmt14@<al>(uint32_t *pArg1@<ecx>, int nArg2@<esi>)
{
  int v2; // edi
  unsigned int v3; // ebx
  int v4; // ecx
  int v5; // ecx
  int v6; // eax
  int pObj2; // eax
  int pObj; // esi
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v16; // [esp+Ch] [ebp-4h]

  v2 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);
  v3 = 0;
  if ( v2 != 0 )
  {
    v4 = *(uint32_t *)(v2 + 8);
    v16 = v4 != 0 ? (*(uint32_t *)(v2 + 12) - v4) >> 2 : 0;
    if ( v16 > 0 )
    {
      while ( 1 )
      {
        v5 = *(uint32_t *)(v2 + 8);
        if ( v5 != 0 && v3 < (*(uint32_t *)(v2 + 12) - v5) >> 2 )
          v6 = *(uint32_t *)(v5 + 4 * v3);
        else
          v6 = 0;
        pObj2 = __RTDynamicCast(v6, 0, &CNRDObject `RTTI Type Descriptor', &CNRDNpc `RTTI Type Descriptor', 0);
        pObj = pObj2;
        if ( pObj2 != 0 && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == pArg1[48] )
          break;
        if ( (int)++v3 >= v16 )
          goto LABEL_18;
      }
      v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 340))(pObj, nArg2);
      v10 = *(uint32_t *)(v9 + 180);
      v11 = v9 + 156;
      if ( v10 < 0x10 )
        v12 = v11 + 4;
      else
        v12 = *(uint32_t *)(v11 + 4);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 212))(pObj, v12, -1, 0);
    }
  }
LABEL_18:
  (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 32))(pArg1);
  return 1;
}



// ------------------------------------------------------------
// 0x606340 sub_606340
// ------------------------------------------------------------
// 对话窗控件批量操作（114 行）：sub_69A5F0/69A840/69C3E0/69C420/69C440/69C780/69C7B0/69CA20/69CA50（UI 控件族九连调）+
// dword_99FCC8/99FCCC（对话 UI 状态全局）——【推断：选项按钮构建与文本装配】。
int /*thiscall*/ sub_606340(uint32_t *this)
{
  int v2; // edx
  uint32_t *pMem; // eax
  uint32_t *fld_e16; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e162; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_e163; // eax
  int v9; // ebx
  uint8_t *pMem4; // edi
  uint8_t *pMem5; // eax
  uint32_t *pMem52; // edi
  int fld_e164; // ebx
  uint32_t *fld_e12; // eax
  int result; // eax
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *pThis_C; // [esp+14h] [ebp-10h]

  v2 = *this;
  *(this + 16) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 24))(16, 18);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 168, 4096);
  sub_69A5F0((uint32_t *)*(this + 3), 8, 37);
  sub_69C3E0(10);
  sub_69C440(-1);
  sub_69C420(6);
  pMem = operator new(0x84u);
  if ( pMem != nullptr )
    fld_e16 = sub_43C410(pMem, *(this + 16), 110, 111, 112, 110, 0, 0);
  else
    fld_e16 = nullptr;
  *(this + 9) = fld_e16;
  sub_69A5F0(fld_e16, 179, 8);
  sub_69A840(*(this + 9));
  pMem2 = operator new(0x84u);
  if ( pMem2 != nullptr )
    fld_e162 = sub_43C410(pMem2, *(this + 16), 113, 114, 115, 113, 0, 0);
  else
    fld_e162 = nullptr;
  *(this + 10) = fld_e162;
  sub_69A5F0(fld_e162, 9, 226);
  sub_69A840(*(this + 10));
  pMem3 = operator new(0x84u);
  if ( pMem3 != nullptr )
    fld_e163 = sub_43C410(pMem3, *(this + 16), 116, 117, 118, 116, 0, 0);
  else
    fld_e163 = nullptr;
  *(this + 11) = fld_e163;
  sub_69A5F0(fld_e163, 25, 226);
  sub_69A840(*(this + 11));
  v9 = 4;
  pThis_C = this + 12;
  do
  {
    pMem4 = operator new(0x84u);
    if ( pMem4 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(pMem4);
      *(uint32_t *)pMem4 = &nengine::CNButton::`vftable';
      sub_69C780(v10);
      sub_69C7B0(Block, v9, v9, v9 + 1, v9, 0, 0);
    }
    else
    {
      v10 = nullptr;
    }
    *v17 = v10;
    v9 += 2;
    ++v17;
  }
  while ( v9 < 8 );
  v11 = operator new(0x88u);
  v12 = v11;
  if ( v11 != nullptr )
  {
    v13 = *(this + 16);
    sub_426BD0(v11);
    *v12 = &nengine::CNSlider::`vftable';
    sub_69CA20(pMem52);
    sub_69CA50(fld_e164, 122, 88);
    *pMem52 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    pMem52 = nullptr;
  }
  *(this + 14) = pMem52;
  if ( operator new(0x74u) != nullptr )
    fld_e12 = (uint32_t *)sub_43C630(*(this + 12), *(this + 13), *(this + 14));
  else
    fld_e12 = nullptr;
  *(this + 15) = fld_e12;
  sub_69A5F0(fld_e12, 186, 31);
  sub_69A840(*(this + 15));
  *(this + 20) = 0;
  *(this + 23) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *((uint8_t *)this + 68) = 0;
  *((uint8_t *)this + 69) = 0;
  *((uint8_t *)this + 70) = 0;
  *((uint8_t *)this + 71) = 0;
  *(this + 21) = 6;
  *(this + 22) = 12;
  *(this + 24) = 1600;
  result = dword_99FCCC;
  *(this + 29) = dword_99FCCC;
  *(this + 18) = -14405058;
  return result;
}


// ------------------------------------------------------------
// 0x606650 sub_606650
// ------------------------------------------------------------
// 对话文本表重建（与 0x602E80 同族）：sub_41FEB0 清空 + sub_44BD00/44BD30 逐词读取 + sub_558090（对话表查询）+
// sub_5E51F0/sub_63A7C0 —— NPC 对话脚本的文本装载。
void /*thiscall*/ sub_606650(int this, int nArg2, unsigned int uArg3, int pArg4)
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

  v4 = *(void **)(pArg4 + 4);
  v28[0] = *(void **)pArg4;
  fld_4 = *(uint32_t *)(this + 4);
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
    else
      fld_8 = 0;
    if ( 0x1FFFFFFF - fld_8 < uArg3 )
      sub_558090(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);
      v20 = (fld_83 - nArg2) >> 3 < uArg3;
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;
      if ( v20 )
      {
        sub_44BD30(nArg2, fld_83, nArg2 + v21);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 3);
        fld_85 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);
        fld_86 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        sub_41FEB0(nArg2, fld_86 - v30, v28);
      }
      else
      {
        v23 = fld_83 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);
        sub_44BD00(nArg2, v23, fld_832);
        sub_41FEB0(nArg2, nArg2 + v30, v28);
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )
        v11 = (fld_C >> 1) + fld_C;
      else
        v11 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
      else
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
        else
          fld_88 = 0;
        v11 = uArg3 + fld_88;
      }
      v31 = 8 * v11;
      pMem = (char *)operator new(8 * v11);
      fld_42 = *(uint32_t *)(this + 4);
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, nArg2, pMem);
      sub_63A7C0(v32, uArg3, v28);
      sub_44BD30(nArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;
      else
        fld_89 = 0;
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &pMem[v31];
      *(uint32_t *)(this + 8) = &pMem[8 * v17];
      *(uint32_t *)(this + 4) = pMem;
    }
  }
}


// ------------------------------------------------------------
// 0x6068A0 sub_6068A0
// ------------------------------------------------------------
// 对话表项读取：sub_44BD30 + sub_558520 —— 单条对话文本取出。
uint32_t */*thiscall*/ sub_6068A0(uint32_t *this, int pArg2)
{
  int v3; // ecx
  int v4; // eax
  uint32_t *v6; // [esp-14h] [ebp-34h]
  uint32_t *v7; // [esp-10h] [ebp-30h]
  uint32_t *fld_e1; // [esp-Ch] [ebp-2Ch]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v3 = *(uint32_t *)(pArg2 + 4);
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( (uint8_t)sub_558520(v4) != 0 )
  {
    fld_e1 = (uint32_t *)*(this + 1);
    v7 = *(uint32_t **)(pArg2 + 8);
    v6 = *(uint32_t **)(pArg2 + 4);
    v12 = 0;
    *(this + 2) = sub_44BD30(v6, v7, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x606940 sub_606940
// ------------------------------------------------------------
// 对话脚本读取（67 行）：sub_558520 表项 + sub_472EA0/sub_47E1D0（脚本执行族）——
// 【推断：条件分支对话的脚本求值】。
int /*thiscall*/ sub_606940(int this, int pArg2)
{
  uint32_t *v3; // ebx
  unsigned int v4; // ecx
  int fld_4; // eax
  unsigned int fld_8; // edx
  int v8; // eax
  int fld_42; // ecx
  unsigned int fld_C; // edx
  int fld_82; // edx
  uint32_t *v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == pArg2 )
    return this;
  v3 = *(uint32_t **)(pArg2 + 4);
  if ( v3 == nullptr || (v4 = (*(uint32_t *)(pArg2 + 8) - (int)v3) >> 3) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
  else
    fld_8 = 0;
  if ( v4 <= fld_8 )
  {
    sub_47E1D0(v3, *(uint32_t **)(pArg2 + 8), *(uint32_t **)(this + 4));
    v8 = *(uint32_t *)(pArg2 + 4);
    if ( v8 != 0 )
      fld_42 = *(uint32_t *)(this + 4) + 8 * ((*(uint32_t *)(pArg2 + 8) - v8) >> 3);
    else
      fld_42 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = fld_42;
    return this;
  }
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;
  else
    fld_C = 0;
  if ( v4 > fld_C )
  {
    if ( fld_4 != 0 )
      j__free(*(void **)(this + 4));
    v13 = *(uint32_t *)(pArg2 + 4);
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(pArg2 + 8) - v13) >> 3;
    else
      v14 = 0;
    if ( (uint8_t)sub_558520(v14) != 0 )
      *(uint32_t *)(this + 8) = sub_472EA0(*(uint32_t **)(pArg2 + 4), *(uint32_t **)(pArg2 + 8), *(uint32_t **)(this + 4));
    return this;
  }
  if ( fld_4 != 0 )
    fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
  else
    fld_82 = 0;
  v12 = (uint32_t *)(*(uint32_t *)(pArg2 + 4) + 8 * fld_82);
  sub_47E1D0(*(uint32_t **)(pArg2 + 4), v12, *(uint32_t **)(this + 4));
  *(uint32_t *)(this + 8) = sub_44BD30(v12, *(uint32_t **)(pArg2 + 8), *(uint32_t **)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x606A90 sub_606A90
// ------------------------------------------------------------
void /*thiscall*/ sub_606A90(int this, int nArg2)
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
  else
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 3 )
  {
    fld_82 = *(uint32_t *)(this + 8);
    sub_63A7C0(fld_82, 1, nArg2);
    *(uint32_t *)(this + 8) = fld_82 + 8;
  }
  else
  {
    sub_606650(this, *(char **)(this + 8), 1u, nArg2);
  }
}



// ------------------------------------------------------------
// 0x606B00 sub_606B00
// ------------------------------------------------------------
// 对话树遍历（103 行，含递归调用自身）：sub_41A5E0（P24 防篡改写）+ sub_429830 + sub_606A90/6068A0/6061D0 +
// word_77F804（配置字）——【推断：对话分支条件求值与跳转】。
uint32_t */*cdecl*/ sub_606B00(uint32_t *uArg1, int **pDwArg2, int pArg3)
{
  void *v3; // ebx
  int pArg32; // esi
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // esi
  int *v11; // esi
  int v12; // eax
  int v13; // ecx
  int v14; // edi
  int v15; // ecx
  char v16[4]; // [esp+8h] [ebp-48h] BYREF
  void *Block; // [esp+Ch] [ebp-44h]
  int v18; // [esp+10h] [ebp-40h]
  int v19; // [esp+14h] [ebp-3Ch]
  char v20[4]; // [esp+18h] [ebp-38h] BYREF
  void *v21; // [esp+1Ch] [ebp-34h]
  int v22; // [esp+20h] [ebp-30h]
  int v23; // [esp+24h] [ebp-2Ch]
  uint32_t v24[2]; // [esp+28h] [ebp-28h] BYREF
  int *v25; // [esp+30h] [ebp-20h] BYREF
  int v26; // [esp+34h] [ebp-1Ch] BYREF
  int v27; // [esp+38h] [ebp-18h]
  int v28; // [esp+3Ch] [ebp-14h]
  int v29; // [esp+40h] [ebp-10h]
  int v30; // [esp+4Ch] [ebp-4h]

  v3 = nullptr;
  v25 = nullptr;
  v21 = nullptr;
  v22 = 0;
  v23 = 0;
  pArg32 = pArg3;
  v30 = 0;
  if ( pArg3 != 0 )
  {
    v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    v7 = sub_41A5E0(v6 + 53);
    v8 = *(uint32_t *)(pArg3 + 72);
    v27 = v7;
    if ( v8 != 0 )
      v29 = (*(uint32_t *)(pArg3 + 76) - v8) >> 2;
    else
      v29 = 0;
    v9 = 0;
    v28 = 0;
    if ( v29 > 0 )
    {
      while ( 1 )
      {
        v10 = *(uint32_t *)(*(uint32_t *)(pArg32 + 72) + 4 * v9);
        v26 = v10;
        sub_6061D0(pDwArg2, &v25, &v26);
        if ( v25 == pDwArg2[1] )
        {
          off_77F3FC(aCriticalErrorN, v10);
        }
        else
        {
          v11 = v25 + 4;
          if ( v25 != (int *)-16 && v7 >= v25[5] && v7 <= v25[6] )
          {
            v12 = sub_606B00(v16, pDwArg2, v25 + 4);
            v13 = *(uint32_t *)(v12 + 4);
            if ( v13 != 0 )
              v14 = (*(uint32_t *)(v12 + 8) - v13) >> 3;
            else
              v14 = 0;
            if ( Block != nullptr )
              j__free(Block);
            v15 = v11[18];
            Block = nullptr;
            v18 = 0;
            v19 = 0;
            if ( v15 == 0 || (v11[19] - v15) >> 2 == 0 || v14 != 0 )
            {
              v24[0] = v11;
              v24[1] = v14;
              sub_606A90((int)v20, (int)v24);
            }
          }
        }
        v9 = ++v28;
        if ( v28 >= v29 )
          break;
        pArg32 = pArg3;
        v7 = v27;
      }
      v3 = v21;
    }
    sub_6068A0(uArg1, (int)v20);
    if ( v3 != nullptr )
      j__free(v3);
    return uArg1;
  }
  else
  {
    sub_6068A0(uArg1, (int)v20);
    return uArg1;
  }
}



// ------------------------------------------------------------
// 0x606CA0 sub_606CA0
// ------------------------------------------------------------
// 对话窗关闭路径：内嵌调试断言串「if (g_userManager->getMyUser() == NULL)」（IDA 反编译内联的调试表达式直证）+
// sub_484F10（用户管理器查询）+ sub_605FA0/6061D0/606B00（树收尾）+ sub_5E5260（字符串析构）。
char /*cdecl*/ sub_606CA0(int **pDwArg1)
{
  char v1; // bl
  int **pDwArg12; // edi
  int **pDwArg13; // esi
  int v5; // esi
  int v6; // eax
  int v7; // eax
  uint32_t *v8; // eax
  bool v9; // al
  void *v10[4]; // [esp+Ch] [ebp-14h] BYREF
  int v11; // [esp+1Ch] [ebp-4h] BYREF

  v1 = 0;
  pDwArg12 = pDwArg1;
  v11 = 1;
  sub_6061D0(pDwArg1, (int **)&pDwArg1, &v11);
  pDwArg13 = pDwArg1;
  if ( pDwArg1 == (int **)pDwArg12[1] )
  {
    off_77F3FC(aNpc1);
    return 0;
  }
  else if ( sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0 )
  {
    v5 = (int)(pDwArg13 + 4);
    v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    v7 = sub_41A5E0(v6 + 53);
    if ( v7 < *(uint32_t *)(v5 + 4) || v7 > *(uint32_t *)(v5 + 8) )
    {
      off_77F3FC((char *)&byte_73B05C);
      return 0;
    }
    else
    {
      if ( (uint8_t)sub_484F10(v5 + 68) != 0
        || (v8 = sub_606B00(v10, pDwArg12, v5), v1 = 1, v9 = sub_605FA0(v8), HIBYTE(pDwArg1) = 1, !v9) )
      {
        HIBYTE(pDwArg1) = 0;
      }
      if ( (v1 & 1) != 0 )
        sub_5E5260(v10);
      if ( HIBYTE(pDwArg1) != 0 )
      {
        off_77F3FC(asc_73B06C);
        return 0;
      }
      else
      {
        return 1;
      }
    }
  }
  else
  {
    off_77F3FC("if (g_userManager->getMyUser() == NULL)");
    return 0;
  }
}



// ------------------------------------------------------------
// 0x606DC0 sub_606DC0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_606DC0(int ***this, uint32_t *uArg2, int nArg3)
{
  sub_606B00(uArg2, *(this + 30), nArg3);
  return uArg2;
}



// ------------------------------------------------------------
// 0x606DF0 sub_606DF0
// ------------------------------------------------------------
// 对话窗布局重建（125 行）：sub_69C340/69C360/69C3A0/69C400/69C500/69C680（控件族）+ sub_606940（脚本读取）——
// NPC 对话窗的控件树重建主流程。
char /*thiscall*/ sub_606DF0(int this, int ArgList, char pszArg3)
{
  int v3; // ebx
  int fld_78; // edi
  int v7; // edi
  int v8; // eax
  int v9; // edi
  int fld_C; // edi
  int fld_C2; // edi
  int fld_C3; // eax
  int fld_B0; // ecx
  int fld_B4; // eax
  int v15; // eax
  int fld_B02; // ecx
  int fld_B42; // eax
  int fld_A0; // ecx
  int fld_A4; // eax
  char pszArg32; // dl
  bool v21; // zf
  int fld_B03; // ecx
  bool v23; // al
  uint8_t v24[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v26; // [esp+14h] [ebp-18h]
  int v27; // [esp+18h] [ebp-14h]
  int v28; // [esp+1Ch] [ebp-10h] BYREF
  int v29; // [esp+28h] [ebp-4h]

  v3 = ArgList;
  fld_78 = *(uint32_t *)(this + 120);
  sub_6061D0(&v28, &ArgList);
  if ( v28 == *(uint32_t *)(fld_78 + 4) )
  {
    off_77F3FC(aCriticalErrorN, v3);
    return 0;
  }
  else
  {
    v7 = v28 + 16;
    ArgList = v28 + 16;
    if ( v28 == -16 )
    {
      return 0;
    }
    else
    {
      if ( pszArg3 != 0 && sub_40BF00((std::_String_base *)(v28 + 56), 0, *(uint32_t *)(v28 + 76), szPassword, 0) == 0 )
        pszArg3 = 0;
      v8 = sub_606DC0(v24, v7);
      v29 = 0;
      sub_606940(v8);
      v29 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v26 = 0;
      v27 = 0;
      if ( pszArg3 != 0 )
      {
        sub_69C340(-1);
        if ( *(uint32_t *)(v7 + 64) < 0x10u )
          v9 = v7 + 44;
        else
          v9 = *(uint32_t *)(v7 + 44);
        sub_69C360(v9, 0);
        sub_69C400(0);
        fld_C = sub_69C500(*(uint32_t *)(this + 12));
        if ( fld_C - sub_69C3A0(*(uint32_t *)(this + 12)) >= 0 )
        {
          fld_C2 = sub_69C500(*(uint32_t *)(this + 12));
          fld_C3 = sub_69C3A0(*(uint32_t *)(this + 12));
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 60) + 32))(*(uint32_t *)(this + 60), fld_C2 - fld_C3);
        }
        else
        {
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 60) + 32))(*(uint32_t *)(this + 60), 0);
        }
        v7 = ArgList;
      }
      else
      {
        fld_B0 = *(uint32_t *)(this + 176);
        if ( fld_B0 != 0 )
          fld_B4 = (*(uint32_t *)(this + 180) - fld_B0) >> 3;
        else
          fld_B4 = 0;
        if ( fld_B4 - 10 >= 0 )
        {
          fld_B02 = *(uint32_t *)(this + 176);
          if ( fld_B02 != 0 )
            fld_B42 = (*(uint32_t *)(this + 180) - fld_B02) >> 3;
          else
            fld_B42 = 0;
          v15 = fld_B42 - 10;
        }
        else
        {
          v15 = 0;
        }
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 60) + 32))(*(uint32_t *)(this + 60), v15);
      }
      fld_A0 = *(uint32_t *)(this + 160);
      if ( fld_A0 != 0 )
        fld_A4 = (*(uint32_t *)(this + 164) - fld_A0) >> 2;
      else
        fld_A4 = 0;
      pszArg32 = pszArg3;
      v21 = pszArg3 == 0;
      *(uint8_t *)(*(uint32_t *)(this + 40) + 16) = fld_A4 != 0;
      v23 = false;
      if ( !v21 )
      {
        fld_B03 = *(uint32_t *)(this + 176);
        if ( fld_B03 != 0 && (*(uint32_t *)(this + 180) - fld_B03) >> 3 != 0 )
          v23 = true;
      }
      *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = v23;
      *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = pszArg32;
      sub_69C680(0);
      *(uint32_t *)(this + 124) = v7;
      sub_4014D0((std::_String_base *)(this + 128), v7 + 12, 0, -1);
      *(uint8_t *)(this + 188) = pszArg3;
      return 1;
    }
  }
}


// ------------------------------------------------------------
// 0x607020 CNRDDialogueWindow__vmt8
// ------------------------------------------------------------
// CNRDDialogueWindow 点击槽（vmt8）：字符串证据「CLICK_BUTTON2」（音效 TAG）+ sub_505FF0 + sub_69A650 +
// sub_606DF0（布局重建）——按钮点击 → 播音 → 下一页刷新。【推断：对话推进按钮处理】
uint8_t */*thiscall*/ CNRDDialogueWindow__vmt8(int this)
{
  int fld_3C; // eax
  int fld_8; // eax
  int v4; // ebx
  int fld_B0; // eax
  unsigned int fld_B4; // edi
  int fld_3C2; // eax
  int fld_28; // eax
  int fld_A0; // edx
  int *fld_A4; // edi
  int fld_A42; // eax
  int fld_2C; // eax
  uint8_t *result; // eax

  sub_69A650(*(uint32_t *)(this + 8));
  if ( *(uint8_t *)(this + 188) != 0 )
  {
    fld_3C = sub_69C690(*(uint32_t *)(this + 60));
    sub_69C400(fld_3C);
  }
  else
  {
    fld_8 = *(uint32_t *)(this + 8);
    if ( *(uint8_t *)(fld_8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_8 + 12) )
    {
      v4 = sub_605F40((uint32_t *)this);
      if ( v4 != -1 )
      {
        fld_B0 = *(uint32_t *)(this + 176);
        fld_B4 = fld_B0 != 0 ? (*(uint32_t *)(this + 180) - fld_B0) >> 3 : 0;
        if ( v4 + sub_69C690(*(uint32_t *)(this + 60)) < fld_B4 )
        {
          sub_431230(this + 156, *(uint32_t **)(this + 124));
          fld_3C2 = sub_69C690(*(uint32_t *)(this + 60));
          sub_606DF0(this, **(int ***)(*(uint32_t *)(this + 176) + 8 * (v4 + fld_3C2)), 1);
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        }
      }
    }
  }
  fld_28 = *(uint32_t *)(this + 40);
  if ( *(uint8_t *)(fld_28 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_28 + 12) )
  {
    fld_A0 = *(uint32_t *)(this + 160);
    fld_A4 = *(int **)(*(uint32_t *)(this + 164) - 4);
    if ( fld_A0 != 0 )
      fld_A42 = (*(uint32_t *)(this + 164) - fld_A0) >> 2;
    else
      fld_A42 = 0;
    sub_505FF0(fld_A42 - 1, 0);
    sub_606DF0(this, fld_A4, 0);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  fld_2C = *(uint32_t *)(this + 44);
  if ( *(uint8_t *)(fld_2C + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_2C + 12) )
  {
    sub_606DF0(this, **(int ***)(this + 124), 0);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = *(uint8_t **)(this + 36);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 20))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6071B0 CNRDDialogueWindow__vmtC
// ------------------------------------------------------------
char /*thiscall*/ CNRDDialogueWindow__vmtC(int this, uint32_t *uArg2, int nArg3)
{
  *(uint32_t *)(this + 120) = uArg2 + 74;
  if ( uArg2 == (uint32_t *)-296 )
    return 0;
  *(uint32_t *)(this + 192) = *uArg2;
  if ( *(uint32_t *)(this + 160) != 0 )
    j__free(*(void **)(this + 160));
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  sub_606DF0(this, (int *)1, 1);
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) / 2,
    (480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) / 2);
  return 1;
}



// ------------------------------------------------------------
// 0x607240 sub_607240
// ------------------------------------------------------------
int /*thiscall*/ sub_607240(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 0;
  *((uint8_t *)this + 8) = 1;
  *((uint8_t *)this + 9) = 1;
  *((uint8_t *)this + 10) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x607260 sub_607260
// ------------------------------------------------------------
char /*thiscall*/ sub_607260(uint32_t *this, int nArg2, int nArg3, char pszArg4, char pszArg5)
{
  *this = nArg2;
  *(this + 1) = nArg3;
  *((uint8_t *)this + 8) = pszArg4;
  *((uint8_t *)this + 9) = pszArg5;
  return pszArg4;
}



// ------------------------------------------------------------
// 0x607290 sub_607290
// ------------------------------------------------------------
char /*thiscall*/ sub_607290(uint8_t *this, int nArg2)
{
  int v2; // eax

  LOBYTE(v2) = *(this + 9);
  *(this + 10) = 1;
  *((uint32_t *)this + 4) = 0;
  if ( (uint8_t)v2 != 0 )
  {
    v2 = nArg2 - *(uint32_t *)this;
    *((uint32_t *)this + 3) = v2;
  }
  else
  {
    *((uint32_t *)this + 3) = nArg2;
  }
  return v2;
}



// ------------------------------------------------------------
// 0x6072C0 sub_6072C0
// ------------------------------------------------------------
// 子弹静态辅助（33 行，无外部调用）——【推断：枪种/弹种参数快查表】。
char /*thiscall*/ sub_6072C0(uint8_t *this, int nArg2)
{
  char fld_e9; // al
  int pThis_1; // eax
  int pThis_3; // eax

  if ( *(this + 10) == 0 )
  {
    fld_e9 = *(this + 9);
    *(this + 10) = 1;
    *((uint32_t *)this + 4) = 0;
    if ( fld_e9 != 0 )
      *((uint32_t *)this + 3) = nArg2 - *(uint32_t *)this;
    else
      *((uint32_t *)this + 3) = nArg2;
  }
  pThis_1 = *((uint32_t *)this + 1);
  if ( pThis_1 != -1 && *((uint32_t *)this + 4) >= pThis_1 )
    return 0;
  pThis_3 = *(uint32_t *)this + *((uint32_t *)this + 3);
  if ( nArg2 < pThis_3 )
    return 0;
  if ( *(this + 8) != 0 )
  {
    ++*((uint32_t *)this + 4);
    *((uint32_t *)this + 3) = nArg2;
  }
  else
  {
    *((uint32_t *)this + 3) = pThis_3;
    ++*((uint32_t *)this + 4);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x607330 sub_607330
// ------------------------------------------------------------
int /*thiscall*/ sub_607330(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = -1;
  *(uint32_t *)(this + 984) = -1;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = -1;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 1004) = 0;
  *(uint32_t *)(this + 1008) = 0;
  *(uint32_t *)(this + 1012) = 0;
  *(uint32_t *)(this + 1016) = -1;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1028) = 0;
  *(uint32_t *)(this + 1032) = 0;
  *(uint8_t *)(this + 1036) = 0;
  *(uint8_t *)(this + 1037) = 0;
  *(uint8_t *)(this + 1038) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6073C0 sub_6073C0
// ------------------------------------------------------------
int /*thiscall*/ sub_6073C0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e253)(uint32_t, int); // ecx
  int result; // eax

  fld_e253 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 253);
  if ( fld_e253 != nullptr )
    result = (**fld_e253)(fld_e253, 1);
  *(this + 253) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6073E0 sub_6073E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6073E0(uint32_t *this, int pArg2, int nArg3)
{
  int result; // eax

  result = sub_41A5E0(pArg2 + 4);
  *(this + 246) = result;
  *(this + 247) = nArg3;
  if ( result == 6 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, 0);
    *(this + 174) = 1000;
  }
  return result;
}



// ============================================================
// 【分区 6】神枪手子弹系（0x607420-0x609720）
// CNGunnerBullet（主武器弹）+ CNGunnerSubWeaponBullet（Musket/BowGun 副武器弹）。
// 资源矩阵直证：属性（Flame/Freeze/Silver）× 枪种（Pistol/Musket/BowGun）的
//   弹体动画 0x6081B0 与命中特效 0x6083 查表；银弹拖尾 SilverBulletParticle.ptl；
//   散弹枪 EX 音效三 TAG（DIFFUSION_GUN_EX/CHARGE、R_DIFFUSION_GUNA）
// ============================================================
// ------------------------------------------------------------
// 0x607420 CNGunnerBullet__vmt158
// ------------------------------------------------------------
// CNGunnerBullet 攻击上下文装配槽（vmt158 = IRDCollisionObject 攻击上下文设置，研究 P29 已引 sub_4E7440）：
// sub_47E720/47EF20/47EFD0（0x47 区命中几何扫描族【推断：攻击盒迭代/重叠测试】）+ sub_4C0FD0/sub_53F7A0。
// 子弹出膛时装配 attackinfo 上下文的主流程（187 行）。
int /*thiscall*/ sub_607420(int this, int nArg2)  // 【CNGunnerBullet__vmt158】
{
  int fld_3E0; // eax
  int v4; // edi
  char *v5; // ebx
  uint32_t *pThis_19C; // eax
  double fld_3E4; // st7
  char *v8; // eax
  int fld_3D8; // eax
  char *v10; // eax
  int fld_3DC; // eax
  char *v12; // eax
  char *v13; // edi
  int fld_3DC5; // eax
  int fld_3DC6; // ecx
  char *v16; // eax
  char *fld_3D82; // eax
  double fld_3DC3; // st7
  int fld_3D83; // eax
  int result; // eax
  uint32_t *v21; // edi
  int fld_3D84; // eax
  int i; // ebx
  int pObj; // eax
  int v25; // eax
  int fld_3DC2; // [esp-10h] [ebp-1Ch]
  int fld_3DC4; // [esp-10h] [ebp-1Ch]

  sub_4E7440((char *)this, nArg2);
  fld_3E0 = *(uint32_t *)(this + 992);
  v4 = 0;
  *(uint32_t *)(this + 508) = (*(uint32_t *)(this + 972) != 0) + 1;
  switch ( fld_3E0 )
  {
    case 1:
      *(uint32_t *)(this + 408) = 0;
      goto LABEL_13;
    case 2:
      v5 = (char *)sub_47E720(2, 2);
      *(uint32_t *)(this + 408) = 1;
      pThis_19C = (uint32_t *)(this + 412);
      while ( *pThis_19C != 17 )
      {
        ++v4;
        ++pThis_19C;
        if ( v4 >= 3 )
          goto LABEL_9;
      }
      *(uint32_t *)(this + 4 * v4 + 412) = 1;
      *(uint32_t *)(this + 4 * v4 + 436) = sub_47EF20(1, *(uint32_t *)(this + 996), -1, -1, 11);
      *(float *)(this + 4 * v4 + 424) = (double)(int)sub_47EF20(2, *(uint32_t *)(this + 996), -1, -1, 11) * 0.1;
LABEL_9:
      fld_3E4 = (double)sub_47EFD0(
                     v5,
                     COERCE_FLOAT(3),
                     *(uint32_t *)(this + 996),
                     *(uint32_t *)(this + 980),
                     *(uint32_t *)(this + 980),
                     0);
      break;
    case 30:
      *(uint32_t *)(this + 408) = 3;
      v8 = (char *)sub_47E720(2, 30);
      fld_3E4 = (double)sub_47EFD0(
                     v8,
                     COERCE_FLOAT(1),
                     *(uint32_t *)(this + 996),
                     *(uint32_t *)(this + 980),
                     *(uint32_t *)(this + 980),
                     0);
      break;
    default:
      goto LABEL_13;
  }
  *(float *)(this + 388) = fld_3E4 + *(float *)(this + 388);
LABEL_13:
  fld_3D8 = *(uint32_t *)(this + 984);
  switch ( fld_3D8 )
  {
    case 5:
      *(uint32_t *)(this + 464) = -998637568;
      v10 = (char *)sub_47E720(2, 5);
      fld_3DC = sub_47EFD0(v10, 0.0, *(uint32_t *)(this + 988), *(uint32_t *)(this + 980), *(uint32_t *)(this + 980), 0);
      fld_3DC2 = *(uint32_t *)(this + 988);
      *(float *)(this + 388) = (double)fld_3DC + *(float *)(this + 388);
      *(float *)(this + 460) = (double)(int)sub_47EF20(2, fld_3DC2, -1, -1, 11) * 0.1 + *(float *)(this + 460);
      break;
    case 6:
    case 9:
    case 15:
      fld_3D82 = (char *)sub_47E720(2, *(uint32_t *)(this + 984));
      fld_3DC3 = (double)sub_47EFD0(fld_3D82, 0.0, *(uint32_t *)(this + 988), *(uint32_t *)(this + 980), *(uint32_t *)(this + 980), 0);
      fld_3D83 = *(uint32_t *)(this + 984);
      *(float *)(this + 388) = fld_3DC3 + *(float *)(this + 388);
      if ( fld_3D83 == 15 )
      {
        *(float *)(this + 464) = (double)(int)sub_47EF20(4, *(uint32_t *)(this + 988), -1, -1, 11)
                               + *(float *)(this + 464);
        *(float *)(this + 524) = *(float *)(this + 524) * 0.5;
      }
      break;
    case 48:
      v12 = (char *)sub_47E720(2, 48);
      *(float *)(this + 388) = (double)sub_47EFD0(
                                         v12,
                                         0.0,
                                         *(uint32_t *)(this + 988),
                                         *(uint32_t *)(this + 980),
                                         *(uint32_t *)(this + 980),
                                         0)
                             + *(float *)(this + 388);
      break;
    case 47:
      v13 = (char *)sub_47E720(2, 47);
      fld_3DC4 = *(uint32_t *)(this + 988);
      *(uint32_t *)(this + 448) = 2;
      *(uint32_t *)(this + 456) = sub_47EF20(0, fld_3DC4, -1, -1, 11);
      fld_3DC5 = sub_47EF20(1, *(uint32_t *)(this + 988), -1, -1, 11);
      fld_3DC6 = *(uint32_t *)(this + 988);
      *(uint32_t *)(this + 452) = fld_3DC5;
      *(float *)(this + 388) = (double)sub_47EFD0(
                                         v13,
                                         COERCE_FLOAT(2),
                                         fld_3DC6,
                                         *(uint32_t *)(this + 980),
                                         *(uint32_t *)(this + 980),
                                         0)
                             + *(float *)(this + 388);
      break;
    case 26:
      v16 = (char *)sub_47E720(2, 26);
      *(float *)(this + 388) = (double)sub_47EFD0(
                                         v16,
                                         COERCE_FLOAT(2),
                                         *(uint32_t *)(this + 988),
                                         *(uint32_t *)(this + 980),
                                         *(uint32_t *)(this + 980),
                                         0)
                             + *(float *)(this + 388);
      break;
    default:
      break;
  }
  result = __RTDynamicCast(
             *(uint32_t *)(this + 692),
             0,
             &IRDCollisionObject `RTTI Type Descriptor',
             &CNGunner `RTTI Type Descriptor',
             0);
  v21 = (uint32_t *)result;
  if ( result != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 840))(result) == 8
      && (*(int (/*thiscall*/ **)(uint32_t *))(*v21 + 908))(v21) == 1 )
    {
      fld_3D84 = *(uint32_t *)(this + 984);
      if ( fld_3D84 != 47 && fld_3D84 != 5 )
      {
        *(uint32_t *)(this + 396) += 200;
        *(uint32_t *)(this + 448) = 2;
      }
    }
    for ( i = 0; i < 18; ++i )
    {
      pObj = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v21 + 792))(v21, i);
      if ( pObj == 0 )
      {
        pObj = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v21 + 1084))(v21, i);
        if ( pObj == 0 )
          continue;
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 128))(pObj, this + 388);
    }
    (*(void (/*thiscall*/ **)(uint32_t *))(*v21 + 700))(v21);
    sub_53F7A0(this + 388);
    if ( *(uint32_t *)(this + 972) == 2 )
      *(float *)(this + 388) = (double)sub_4C0FD0(v21) + *(float *)(this + 388);
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v21 + 1140))(v21, 38);
    if ( result > 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v21 + 1160))(v21, 38);
      v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v21 + 1140))(v21, 38);
      result = sub_47EF20(0, v25, -1, -1, 11);
      *(float *)(this + 524) = ((double)result * 0.0099999998 + 1.0) * *(float *)(this + 524);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6078B0 sub_6078B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6078B0(uint32_t *this)
{
  int v2; // eax
  int result; // eax
  int pObj; // esi
  int v5; // ebx
  uint32_t *v6; // eax

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
  result = __RTDynamicCast(v2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);
  pObj = result;
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 1140))(result, 31);
    v5 = result;
    if ( result > 0 )
    {
      v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1160))(pObj, 31);
      result = sub_47EF20(v6, 0, v5, -1, -1, 11);
      *(this + 174) += result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x607920 CNGunnerBullet__vmt214
// ------------------------------------------------------------
char /*thiscall*/ CNGunnerBullet__vmt214(int *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // eax
  int *pThis_100; // ebx
  int i; // edi

  LOBYTE(v5) = CNRDPassiveObject__vmt214(this, nArg2, nArg3, nArg4);
  if ( *(this + 254) == -1 )
  {
    pThis_100 = this + 256;
    *(this + 254) = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) > 0 ? 0 : 2;
    for ( i = 0; i < 3; ++i )
    {
      v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 116))(this, i);
      *pThis_100++ = v5;
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x607990 sub_607990
// ------------------------------------------------------------
int /*thiscall*/ sub_607990(uint32_t *this)
{
  int fld_e28; // esi
  int v2; // edi

  fld_e28 = *(uint32_t *)(*(this + 28) + 104);
  v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e28 + 16))(fld_e28);
  return *(uint32_t *)(v2 + 15) * (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e28 + 44))(fld_e28) / 1000;
}



// ------------------------------------------------------------
// 0x6079D0 CNGunnerBullet__vmt1F0
// ------------------------------------------------------------
int /*thiscall*/ CNGunnerBullet__vmt1F0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int pObj; // eax
  int pObj2; // esi
  int pObj3; // eax
  int v8; // eax

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this) == 0 )
    return 0;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273) == 0 )
    return 0;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);
  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 1032))(pObj2) == 2 )
  {
    pObj3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 792))(pObj2, 8);
    if ( pObj3 != 0 )
    {
      v8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 16))(pObj3) + 4);
      if ( (v8 == 31941 || v8 == 31967) && (uint8_t)sub_4DAB60(6) != 0 )
        *(this + 99) += 20;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x607A70 sub_607A70
// ------------------------------------------------------------
// 子弹命中盒扫描变体：sub_47E720/sub_47EFD0 —— 判定盒迭代（0x607420 同族精简版）。
char /*thiscall*/ sub_607A70(int this, int pArg2, char pszArg3)
{
  uint32_t *v4; // ecx
  uint32_t *v5; // eax
  char *v6; // eax
  double v7; // st7
  int fld_3E4; // [esp+Ch] [ebp+8h]

  v4 = *(uint32_t **)(pArg2 + 336);
  v5 = *(uint32_t **)(pArg2 + 332);
  if ( v5 != v4 )
  {
    do
    {
      if ( *v5 == 6 )
        break;
      ++v5;
    }
    while ( v5 != v4 );
    if ( v5 != v4 )
    {
      v6 = (char *)sub_47E720(2, 0x1Eu);
      fld_3E4 = sub_47EFD0(v6, COERCE_FLOAT(2), *(uint32_t *)(this + 996), *(uint32_t *)(this + 980), *(uint32_t *)(this + 980), 0);
      LOBYTE(v5) = pszArg3;
      v7 = (double)fld_3E4;
      if ( pszArg3 == 1 )
        *(float *)(this + 388) = v7 + *(float *)(this + 388);
      else
        *(float *)(this + 388) = *(float *)(this + 388) - v7;
    }
  }
  return (char)v5;
}



// ------------------------------------------------------------
// 0x607B00 CNGunnerBullet__vmt10
// ------------------------------------------------------------
// CNGunnerBullet 每帧 tick（vmt10）：sub_491F80/492080/4938F0（动画对象复位/绑定族）+ sub_699000（clock_now，P9 时间域）+
// dword_7930D4（时间域 y 压缩系数，与 vmtA4 朝向角同源）——【推断：弹道位移的时间域积分】。
char /*usercall*/ CNGunnerBullet__vmt10@<al>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // eax
  bool v5; // zf
  int nRand; // eax
  int v7; // et2
  int pObj; // ecx
  int v9; // edi
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  uint32_t *v13; // edi
  int v15; // [esp+4h] [ebp-4h]
  float v16; // [esp+4h] [ebp-4h]

  CNRDPassiveObject__vmt10(pDwArg1);
  v4 = pDwArg1[246];
  if ( v4 == 6 )
  {
    LOBYTE(v4) = *((uint8_t *)pDwArg1 + 1037);
    if ( (uint8_t)v4 == 0 )
    {
      pDwArg1[252] = -1081794888;
      *((uint8_t *)pDwArg1 + 1037) = 1;
    }
  }
  else
  {
    v5 = v4 == 9;
    LOBYTE(v4) = *((uint8_t *)pDwArg1 + 1037);
    if ( v5 )
    {
      if ( (uint8_t)v4 == 0 )
      {
        nRand = rand();
        v7 = nRand % 628;
        v4 = nRand / 628;
        *((uint8_t *)pDwArg1 + 1037) = 1;
        *((float *)pDwArg1 + 252) = (double)v7 * 0.0099999998;
      }
    }
    else
    {
      if ( (uint8_t)v4 == 0 )
      {
        pObj = *(uint32_t *)(pDwArg1[28] + 104);
        if ( pObj != 0 && pDwArg1[30] != 0 )
        {
          v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 16))(pObj, nArg3, nArg2) + 76);
          v10 = dword_7930D4[0]
              * *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pDwArg1[28] + 104) + 16))(*(uint32_t *)(pDwArg1[28] + 104))
                          + 72)
              / 100;
          if ( (int)abs32(v9) <= (int)abs32(v10) )
            v15 = -v10;
          else
            v15 = v9;
          v11 = *pDwArg1;
          v16 = (double)v15 * 0.0174532925199433;
          *((float *)pDwArg1 + 252) = v16;
          (*(void (/*thiscall*/ **)(int *, int, uint32_t))(v11 + 272))(pDwArg1, 1, LODWORD(v16));
        }
        *((uint8_t *)pDwArg1 + 1037) = 1;
      }
      v12 = pDwArg1[248];
      if ( v12 == 1 || v12 == 2 || v12 == 30 )
      {
        v4 = pDwArg1[32];
        v13 = *(uint32_t **)v4;
        if ( *(uint32_t *)v4 != v4 )
        {
          do
          {
            sub_4938F0(v13[3]);
            if ( *((float *)pDwArg1 + 252) != 0.0 )
              sub_492080(*((float *)pDwArg1 + 252));
            if ( sub_699000((int)(pDwArg1 + 9)) <= 70 )  // 【clock_now(clk)】
              LOBYTE(v4) = sub_491F80(-1, -1, -1, 0, 1);
            else
              LOBYTE(v4) = sub_491F80(-1, -1, -1, 255, 1);
            v13 = (uint32_t *)*v13;
          }
          while ( v13 != (uint32_t *)pDwArg1[32] );
        }
      }
      else if ( sub_699000((int)(pDwArg1 + 9)) <= 70 )  // 【clock_now(clk)】
      {
        LOBYTE(v4) = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*pDwArg1 + 252))(pDwArg1, 3, 0);
      }
      else
      {
        LOBYTE(v4) = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 252))(pDwArg1, 3, 255);
      }
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x607CD0 CNGunnerBullet__vmt1F8
// ------------------------------------------------------------
// CNGunnerBullet 观察者通知槽（vmt1F8 = 基类 18 观察者通知族，IRDActiveObject.h 定案）：
// sub_4DAB60（combat_core 播报族）+ sub_607A70 —— 子弹命中/消亡时的观察者播报。
int /*thiscall*/ CNGunnerBullet__vmt1F8(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int pObj; // eax
  int pObj4; // esi
  int i; // ebx
  int pObj3; // eax
  int pObj2; // eax
  int v10; // eax

  if ( *(this + 248) == 30 )
    sub_607A70((int)this, nArg2, 0);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this) == 0 )
    return 0;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273) == 0 )
    return 0;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);
  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 1032))(pObj4) == 2 )
  {
    for ( i = 0; i < 18; ++i )
    {
      if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 792))(pObj4, i) != 0 )
      {
        pObj3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 792))(pObj4, i);
        (*(void (/*thiscall*/ **)(int, int, int, int, uint32_t, uint32_t *))(*(uint32_t *)pObj3 + 136))(
          pObj3,
          nArg2,
          nArg3,
          nArg4,
          0,
          this + 97);
      }
    }
    pObj2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 792))(pObj4, 8);
    if ( pObj2 != 0 )
    {
      v10 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 4);
      if ( (v10 == 31941 || v10 == 31967) && (uint8_t)sub_4DAB60(6) != 0 )
        *(this + 99) -= 20;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x607DD0 CNGunnerBullet__vmt28C
// ------------------------------------------------------------
void **/*thiscall*/ CNGunnerBullet__vmt28C(uint32_t *this, int nArg2)
{
  void **result; // eax

  if ( (dword_9B93A0 & 1) == 0 )
  {
    dword_9B93A0 |= 1u;
    dword_9B939C = 15;
    dword_9B9398 = 0;
    LOBYTE(dword_9B9388) = 0;
    atexit(sub_6BFF00);
  }
  if ( *(this + 244) > 2u )
    return nullptr;
  if ( *(this + 243) != 0 )
    sub_4015C0("Character/Gunner/Effect/Animation/HitEffect/DownDefault.ani", 0x3Bu);  // 【std::string构造赋值】
  else
    sub_4015C0("Character/Gunner/Effect/Animation/HitEffect/UpDefault.ani", 0x39u);  // 【std::string构造赋值】
  result = (void **)dword_9B9388;
  if ( (unsigned int)dword_9B939C < 0x10 )
    return &dword_9B9388;
  return result;
}



// ------------------------------------------------------------
// 0x607E70 CNGunnerBullet__vmt14C
// ------------------------------------------------------------
// CNGunnerBullet 主循环槽（vmt14C，169 行）：字符串证据「Character/Gunner/Effect/Animation/Bullet/RandomShoot.ani」
// （随机弹射动画）。sub_431860 动画生成 + sub_4600B0 演播层 + sub_600890（基类出生播音，P32）+ sub_4A0B60/sub_607990 ——
// 子弹飞行中的动画/演出编排。【推断：弹道动画随机化】
void /*thiscall*/ sub_607E70(int *this)  // 【CNGunnerBullet__vmt14C】
{
  uint32_t *fld_e173; // eax
  uint32_t *fld_e1732; // edi
  int v4; // edx
  int v5; // eax
  double v6; // st7
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edi
  int fld_e246; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  int *fld_e28; // ecx
  int v18; // edx
  int *v19; // edi
  int *fld_e282; // edi
  int v21; // ebx
  int v22; // eax
  int fld_e248; // eax
  int *fld_e253; // eax
  int v25; // edi
  int v26; // eax
  int v27; // eax
  int v28; // eax
  void *fld_e29; // ecx
  int fld_e2462; // eax
  int fld_e247; // [esp-10h] [ebp-54h]
  float v32; // [esp+Ch] [ebp-38h] BYREF
  float v33; // [esp+10h] [ebp-34h]
  float v34; // [esp+14h] [ebp-30h]
  int v35; // [esp+18h] [ebp-2Ch]
  int v36; // [esp+1Ch] [ebp-28h]
  int v37; // [esp+20h] [ebp-24h]
  uint8_t v38[4]; // [esp+24h] [ebp-20h] BYREF
  void *Block; // [esp+28h] [ebp-1Ch]
  int v40; // [esp+2Ch] [ebp-18h]
  int v41; // [esp+30h] [ebp-14h]
  int v42; // [esp+34h] [ebp-10h]
  int v43; // [esp+40h] [ebp-4h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  if ( *((uint8_t *)this + 1036) == 0 )
  {
    if ( *(this + 246) == 6 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      fld_e173 = (uint32_t *)__RTDynamicCast(
                       *(this + 173),
                       0,
                       &IRDCollisionObject `RTTI Type Descriptor',
                       &CNGunner `RTTI Type Descriptor',
                       0);
      fld_e1732 = fld_e173;
      if ( fld_e173 != nullptr && fld_e173[2175] != 0 )
      {
        v4 = *fld_e173;
        v32 = 0.0;
        v33 = 0.0;
        v34 = 0.0;
        v35 = 0;
        v36 = 0;
        v37 = 0;
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 152))(fld_e173) != 0 )
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*fld_e1732 + 120))(fld_e1732) + 94;
        else
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*fld_e1732 + 120))(fld_e1732) - 94;
        v42 = v5;
        v6 = (double)v5;
        v7 = *fld_e1732;
        v32 = v6;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 124))(fld_e1732);
        v9 = *fld_e1732;
        v42 = v8;
        v33 = (float)v8;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 128))(fld_e1732);
        v11 = fld_e1732[2175];
        v42 = v10 + 16;
        v34 = (float)(v10 + 16);
        sub_4E5F70(0, (int)this, v11, &v32, 1, 1);
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    }
    else
    {
      fld_e246 = *(this + 246);
      if ( fld_e246 == 9 )
      {
        sub_4A0B60(0);
        v13 = sub_42FCB0(228);
        v42 = v13;
        v43 = 0;
        if ( v13 != 0 )
          v14 = sub_431860(v13, "Character/Gunner/Effect/Animation/Bullet/RandomShoot.ani", 1);
        else
          v14 = 0;
        v15 = *this;
        v43 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v15 + 196))(this, v14);
        (*(void (/*thiscall*/ **)(int *, int))(*this + 100))(this, v14);
      }
      else if ( fld_e246 == 48 && *(this + 244) != 3 )
      {
        fld_e247 = *(this + 247);
        sub_47E720(2, 48);
        v16 = sub_47EF20(1, fld_e247, -1, -1, 11);
        fld_e28 = *(int **)(*(this + 28) + 104);
        v18 = *fld_e28;
        *(float *)&v42 = (double)v16 * 0.0099999998;
        v19 = (int *)((*(int (/*thiscall*/ **)(int *))(v18 + 16))(fld_e28) + 85);
        *v19 = (uint64_t)((double)*v19 * *(float *)&v42);
        fld_e282 = *(int **)(*(this + 28) + 104);
        v21 = *fld_e282;
        v22 = (*(int (/*thiscall*/ **)(int *))(*fld_e282 + 44))(fld_e282);
        (*(void (/*thiscall*/ **)(int *, int))(v21 + 4))(fld_e282, v22);
      }
    }
    *((uint8_t *)this + 1036) = 1;
  }
  fld_e248 = *(this + 248);
  if ( fld_e248 == 1 || fld_e248 == 2 || fld_e248 == 30 )
  {
    (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*this + 252))(this, 3, 0);
    if ( *(this + 248) == 30 )
    {
      fld_e253 = (int *)*(this + 253);
      if ( fld_e253 != nullptr )
      {
        v25 = *fld_e253;
        v26 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        v27 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v26);
        v28 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v27);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v25 + 40))(*(this + 253), v28);
        (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 253) + 92))(*(this + 253), v38);
        fld_e29 = (void *)*(this + 29);
        v43 = 1;
        sub_4600B0(fld_e29, 2, 0, (int)v38);
        v43 = -1;
        if ( Block != nullptr )
          j__free(Block);
        Block = nullptr;
        v40 = 0;
        v41 = 0;
      }
    }
  }
  if ( *(this + 246) == 9
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && sub_699000((int)(this + 9)) >= 200 )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  if ( *(this + 244) != 3 )
  {
    fld_e2462 = *(this + 246);
    if ( fld_e2462 != 6 && fld_e2462 != 9 && fld_e2462 != 5 )
    {
      *((float *)this + 116) = *((float *)this + 116) - *((float *)this + 251);
      v42 = sub_607990(this) - 200;
      if ( v42 > 0 )
        *((float *)this + 251) = (double)v42 * 0.0175;
      else
        *(this + 251) = 0;
      *((float *)this + 116) = *((float *)this + 116) + *((float *)this + 251);
    }
  }
}


// ------------------------------------------------------------
// 0x6081B0 sub_6081B0
// ------------------------------------------------------------
// 弹种×枪种动画路径拼接：字符串证据「Character/Gunner/Effect/Animation/Bullet/」+ 属性名
// 「Flame | Freeze | Silver」× 枪名「Pistol.ani | Musket.ani | BowGun.ani」——
// 九种组合的路径查表（dword_796E50 = 路径根）。属性弹与枪种的二维矩阵直证。
int /*cdecl*/ sub_6081B0(int nArg1, int nArg2)
{
  int v2; // eax
  void **Block2; // ecx
  int v4; // esi
  uint8_t v6[4]; // [esp+4h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+8h] [ebp-28h] BYREF
  unsigned int v8; // [esp+1Ch] [ebp-14h]
  int dword_796E502; // [esp+20h] [ebp-10h]
  int v10; // [esp+2Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  v8 = 15;
  Block[4] = nullptr;
  LOBYTE(Block[0]) = 0;
  sub_4015C0("Character/Gunner/Effect/Animation/Bullet/", 0x29u);  // 【std::string构造赋值】
  v10 = 0;
  switch ( nArg1 )
  {
    case 1:
      sub_4022F0((std::_String_base *)v6, "Flame", 5);
      break;
    case 2:
      sub_4022F0((std::_String_base *)v6, "Freeze", 6);
      break;
    case 30:
      sub_4022F0((std::_String_base *)v6, "Silver", 6);
      break;
    default:
      return 0;
  }
  switch ( nArg2 )
  {
    case 0:
    case 1:
      sub_4022F0((std::_String_base *)v6, "Pistol.ani", 10);
      break;
    case 2:
      sub_4022F0((std::_String_base *)v6, "Musket.ani", 10);
      break;
    case 4:
      sub_4022F0((std::_String_base *)v6, "BowGun.ani", 10);
      break;
    default:
      if ( v8 >= 0x10 )
        j__free(Block[0]);
      return 0;
  }
  v2 = sub_42FCB0(228);
  LOBYTE(v10) = 1;
  if ( v2 != 0 )
  {
    Block2 = (void **)Block[0];
    if ( v8 < 0x10 )
      Block2 = Block;
    v4 = sub_431860(v2, (const char *)Block2, 1);
  }
  else
  {
    v4 = 0;
  }
  if ( v8 >= 0x10 )
    j__free(Block[0]);
  return v4;
}



// ------------------------------------------------------------
// 0x608300 sub_608300
// ------------------------------------------------------------
// 命中特效路径拼接（与 0x6081B0 同构）：字符串证据「Character/Gunner/Effect/Animation/HitEffect/」+
// 「Flame | Freeze | Silver | Normal」×「BowGun.ani」族 —— 子弹命中特效的属性×枪种查表。
int /*cdecl*/ sub_608300(int nArg1, int nArg2, int nArg3)
{
  int v3; // eax
  void **Block2; // ecx
  int v5; // esi
  int i; // edi
  int v7; // eax
  int v8; // eax
  uint8_t v10[4]; // [esp+10h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+14h] [ebp-28h] BYREF
  unsigned int v12; // [esp+28h] [ebp-14h]
  int dword_796E502; // [esp+2Ch] [ebp-10h]
  int v14; // [esp+38h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v12 = 15;
  Block[4] = nullptr;
  LOBYTE(Block[0]) = 0;
  sub_4015C0("Character/Gunner/Effect/Animation/HitEffect/", 0x2Cu);  // 【std::string构造赋值】
  v14 = 0;
  switch ( nArg1 )
  {
    case 1:
      sub_4022F0((std::_String_base *)v10, "Flame", 5);
      break;
    case 2:
      sub_4022F0((std::_String_base *)v10, "Freeze", 6);
      break;
    case 30:
      sub_4022F0((std::_String_base *)v10, "Silver", 6);
      break;
    default:
      sub_4022F0((std::_String_base *)v10, "Normal", 6);
      break;
  }
  sub_4022F0((std::_String_base *)v10, "BowGun.ani", 10);
  v3 = sub_42FCB0(228);
  LOBYTE(v14) = 1;
  if ( v3 != 0 )
  {
    Block2 = (void **)Block[0];
    if ( v12 < 0x10 )
      Block2 = Block;
    v5 = sub_431860(v3, (const char *)Block2, 1);
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v14) = 0;
  for ( i = 0; ; ++i )
  {
    v7 = *(uint32_t *)(v5 + 44);
    v8 = v7 != 0 ? (*(uint32_t *)(v5 + 48) - v7) / 88 : 0;
    if ( i >= v8 )
      break;
    *(uint32_t *)(sub_4924C0(i) + 28) = nArg3;
  }
  if ( v12 >= 0x10 )
    j__free(Block[0]);
  return v5;
}



// ------------------------------------------------------------
// 0x608430 CNGunnerBullet__vmt12C
// ------------------------------------------------------------
// CNGunnerBullet 消亡联动槽（vmt12C，124 行）：字符串证据
// 「Character/Gunner/Effect/Animation/HitEffect/CollisionFloor.ani | CollisionWall.ani」——撞地/撞墙两种消亡特效。
// sub_45FE80 演播层 + sub_600790（基类移除联动）+ sub_608300（命中特效查表）+ sub_4E4A50（动作包）——
// 子弹寿命终结的完整演出链。
uint32_t */*thiscall*/ sub_608430(uint32_t *this, uint32_t *uArg2)  // 【CNGunnerBullet__vmt12C】
{
  int fld_e246; // eax
  int fld_e28; // edi
  int v5; // ebx
  unsigned int fld_e244; // eax
  int v7; // edi
  int fld_e248; // edi
  int pObj2; // edi
  int fld_e292; // ecx
  int v11; // ebx
  int v12; // eax
  int fld_e254; // eax
  bool v14; // zf
  char *v15; // eax
  uint32_t *v16; // ecx
  int pObj; // edi
  int fld_e29; // ecx
  int v19; // ebx
  int v20; // eax
  int fld_e249; // edi
  int fld_e258; // ebx
  int v23; // eax
  uint32_t *result; // eax
  int fld_e255; // [esp-8h] [ebp-40h]
  int v26; // [esp+8h] [ebp-30h]
  char v27[4]; // [esp+Ch] [ebp-2Ch] BYREF
  uint32_t v28[7]; // [esp+10h] [ebp-28h] BYREF
  int v29; // [esp+34h] [ebp-4h]

  v28[6] = dword_796E50;
  sub_600790(uArg2);  // 【CNRDPassiveObject__vmt12C】
  if ( uArg2 == this )
  {
    fld_e246 = *(this + 246);
    if ( fld_e246 != 9 && fld_e246 != 6 )
    {
      fld_e28 = *(uint32_t *)(*(this + 28) + 104);
      if ( fld_e28 == 0
        || (v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e28 + 16))(fld_e28),
            (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e28 + 44))(fld_e28) < *(uint32_t *)(v5 + 85)) )
      {
        fld_e244 = *(this + 244);
        v7 = 0;
        if ( fld_e244 <= 2 )
        {
          fld_e254 = *(this + 254);
          if ( fld_e254 != -1 )
          {
            v14 = fld_e254 == 2;
            v15 = "Character/Gunner/Effect/Animation/HitEffect/CollisionFloor.ani";
            if ( !v14 )
              v15 = "Character/Gunner/Effect/Animation/HitEffect/CollisionWall.ani";
            sub_401710(v15);
            v29 = 1;
            if ( sub_42FCB0(228) != 0 )
            {
              LOBYTE(v16) = v28[0];
              if ( v28[5] < 0x10u )
                v16 = v28;
              v7 = sub_431860((char)v16, 1);
            }
            LOBYTE(v29) = 0;
            v26 = sub_44B6C0(284);
            LOBYTE(v29) = 2;
            if ( v26 != 0 )
              pObj = sub_44E1F0(v7, 1);
            else
              pObj = 0;
            fld_e29 = *(this + 29);
            LOBYTE(v29) = 0;
            sub_45FE80(fld_e29, pObj, 2, 0, pObj, 0, 0);
            v19 = *(uint32_t *)pObj;
            v20 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
            (*(void (/*thiscall*/ **)(int, int))(v19 + 148))(pObj, v20);
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj + 112))(
              pObj,
              *(this + 256),
              *(this + 257),
              *(this + 258));
            v29 = -1;
            sub_501490(v27);
          }
        }
        else if ( fld_e244 == 4 )
        {
          fld_e248 = sub_608300(*(this + 248), *(this + 243), *(this + 252));
          v29 = 3;
          pObj2 = sub_44B6C0(284) != 0 ? sub_44E1F0(fld_e248, 1) : 0;
          fld_e292 = *(this + 29);
          v29 = -1;
          sub_45FE80(fld_e292, pObj2, 2, 0, pObj2, 0, 0);
          v11 = *(uint32_t *)pObj2;
          v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
          (*(void (/*thiscall*/ **)(int, int))(v11 + 148))(pObj2, v12);
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 112))(
            pObj2,
            *(this + 256),
            *(this + 257),
            *(this + 258));
          if ( *(this + 254) == -1 && *(this + 255) != 0 )
          {
            fld_e255 = *(this + 255);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 60))(pObj2);
            sub_4A06D0(fld_e255);
          }
        }
        if ( *(this + 248) == 1
          && *(this + 254) != -1
          && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        {
          sub_47E720(2, *(this + 248));
          fld_e249 = sub_47EF20(1, *(this + 249), -1, -1, 11);
          fld_e258 = *(this + 258) <= 0 ? 0 : *(this + 258);
          v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
          sub_4E4A50(*(this + 173), 40002, fld_e249, *(this + 256), *(this + 257), fld_e258, v23, 0, 0, 0);
        }
      }
    }
  }
  result = uArg2;
  if ( uArg2 == (uint32_t *)*(this + 255) )
    *(this + 255) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x608730 sub_608730
// ------------------------------------------------------------
// 银弹拖尾粒子：字符串证据「Character/Gunner/Effect/Particle/SilverBulletParticle.ptl」（研究 20 P36 .ptl 资源）+
// sub_428F30 发射器生成 + sub_6081B0（弹种动画）+ sub_41A5E0（P24 写）——银弹专属粒子拖尾的装载。
int /*thiscall*/ sub_608730(int *this, void *Block, int nArg3)
{
  int result; // eax
  int fld_e246; // ecx
  int v6; // edi
  uint32_t *pMem; // eax
  uint32_t *v8; // eax
  int fld_e253; // eax
  int v10; // edi

  result = sub_41A5E0((unsigned int)Block + 4);
  *(this + 248) = result;
  *(this + 249) = nArg3;
  if ( result == 1 || result == 2 || result == 30 )
  {
    fld_e246 = *(this + 246);
    if ( fld_e246 != 6 && fld_e246 != 9 )
    {
      result = sub_6081B0(result, *(this + 244));
      v6 = result;
      if ( result != 0 )
      {
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
          this,
          1,
          result,
          0,
          0,
          0,
          0);
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 100))(this, v6);
      }
      if ( *(this + 248) == 30 )
      {
        result = *(this + 253);
        if ( result == 0 && *(this + 244) != 3 )
        {
          pMem = operator new(0x12Cu);
          if ( pMem != nullptr )
            v8 = sub_428F30(pMem, (int)"Character/Gunner/Effect/Particle/SilverBulletParticle.ptl", (int)this);
          else
            v8 = nullptr;
          *(this + 253) = (int)v8;
          (*(void (/*thiscall*/ **)(uint32_t *, int *))(*v8 + 112))(v8, this);
          result = *(this + 243);
          if ( result == 1 )
          {
            fld_e253 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 253) + 28))(*(this + 253));
            v10 = -30;
          }
          else
          {
            if ( result != 2 )
              return result;
            fld_e253 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 253) + 28))(*(this + 253));
            v10 = -45;
          }
          *(uint32_t *)(fld_e253 + 76) = v10;
          result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 253) + 36))(*(this + 253));
          *(uint32_t *)(result + 28) = v10;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x608890 CNGunnerBullet__vmt1F4
// ------------------------------------------------------------
// CNGunnerBullet 命中表现槽（vmt1F4，174 行）：sub_45FE80 演播层 + sub_608300（命中特效查表）+
// sub_44B6C0/sub_44E0D0（帧事件族，P26）/sub_4A06D0（挂点跟随族）/sub_5FF9C0/sub_607990/607A70 ——
// 子弹命中目标的特效+帧事件装配主流程。
int /*thiscall*/ sub_608890(int *this, int nArg2, float *pArg3, int nArg4)  // 【CNGunnerBullet__vmt1F4】
{
  int nArg22; // ebx
  int v5; // eax
  int fld_e173; // eax
  int fld_e246; // eax
  void *v9; // eax
  int fld_e248; // eax
  float *pArg32; // edi
  char *fld_e2482; // eax
  int v13; // eax
  int fld_e2462; // eax
  char *v15; // edi
  int fld_e29; // ecx
  int v17; // edi
  int v18; // ebx
  int nRand2; // eax
  int v20; // eax
  int fld_e2463; // eax
  int fld_e250; // eax
  int v23; // eax
  bool v24; // cc
  int pObj2; // eax
  int pObj; // eax
  int nRand; // [esp-8h] [ebp-38h]
  BOOL v29; // [esp-4h] [ebp-34h]
  int v30; // [esp+Ch] [ebp-24h]
  int fld_e249; // [esp+10h] [ebp-20h]
  int fld_e2483; // [esp+10h] [ebp-20h]
  int v33; // [esp+10h] [ebp-20h]
  int v34; // [esp+14h] [ebp-1Ch]
  int v35; // [esp+14h] [ebp-1Ch]
  int v36; // [esp+18h] [ebp-18h]
  int v37; // [esp+18h] [ebp-18h]
  int v38; // [esp+1Ch] [ebp-14h]
  char *pObj3; // [esp+1Ch] [ebp-14h]
  int v40; // [esp+20h] [ebp-10h] BYREF
  int v41; // [esp+2Ch] [ebp-4h]
  int v42; // [esp+38h] [ebp+8h]
  int i; // [esp+38h] [ebp+8h]
  uint32_t *pThis_100; // [esp+3Ch] [ebp+Ch]
  int pObj4; // [esp+3Ch] [ebp+Ch]

  nArg22 = nArg2;
  v5 = *(uint32_t *)nArg2;
  v40 = 100;
  (*(void (/*thiscall*/ **)(int, int *, int *))(v5 + 648))(nArg2, &v40, this);
  if ( (uint8_t)nArg4 == 0 )
  {
    fld_e173 = __RTDynamicCast(
           *(this + 173),
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &CNGunner `RTTI Type Descriptor',
           0);
    if ( fld_e173 != 0 )
    {
      fld_e246 = 28 * (*(this + 246) == 5) + fld_e173 + 8404;
      if ( *(uint32_t *)(fld_e246 + 24) < 0x10u )
        v9 = (void *)(fld_e246 + 4);
      else
        v9 = *(void **)(fld_e246 + 4);
      sub_432EA0(v9, -1, 0, 0);
    }
  }
  fld_e248 = *(this + 248);
  pArg32 = pArg3;
  if ( fld_e248 == 1 )
  {
    if ( (uint8_t)nArg4 == 0 && v40 > 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 308))(nArg2) != 0 )
    {
      fld_e2482 = (char *)sub_47E720(2, *(this + 248));
      fld_e249 = sub_47EFD0(fld_e2482, COERCE_FLOAT(1), *(this + 249), *(this + 245), *(this + 245), 0);
      v34 = (uint64_t)(pArg3[3] * 0.5 + *pArg3);
      v36 = (uint64_t)(pArg3[4] * 0.5 + pArg3[1]);
      v38 = (uint64_t)(pArg3[5] * 0.5 + pArg3[2]);
      v13 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      sub_4E4A50((int)pArg3, *(this + 173), 40002, fld_e249, v34, v36, v38, v13, 0, 0, 0);
    }
  }
  else if ( fld_e248 == 30 )
  {
    sub_607A70(nArg2, 1);
  }
  if ( *(this + 244) == 4 )
  {
    fld_e2462 = *(this + 246);
    if ( fld_e2462 == 9 || fld_e2462 == 6 )
    {
      v30 = (uint64_t)(pArg3[3] * 0.5 + *pArg3);
      v37 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);
      v35 = (uint64_t)(pArg3[5] * 0.5 + pArg3[2]);
      fld_e2483 = sub_608300(*(this + 248), *(this + 243), *(this + 252));
      v15 = (char *)sub_44B6C0(284);
      v41 = 0;
      if ( v15 != nullptr )
      {
        sub_44E0D0(v15, fld_e2483, 1);
        *(uint32_t *)v15 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v15 = nullptr;
      }
      fld_e29 = *(this + 29);
      pObj3 = v15;
      v41 = -1;
      sub_45FE80(fld_e29, (int)v15, 2, 0, (int)v15, nArg2, 0);
      v33 = *(uint32_t *)v15;
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);
      v29 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < v17;
      (*(void (/*thiscall*/ **)(char *))(v33 + 148))(pObj3);
      v18 = *(uint32_t *)pObj3;
      nRand = rand() % 6 + v35 - 3;
      nRand2 = rand();
      (*(void (/*thiscall*/ **)(char *, int, int, int))(v18 + 112))(pObj3, nRand2 % 6 + v30 - 3, v37, nRand);
      nArg22 = nArg2;
      v20 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj3 + 60))(pObj3, nArg2);
      sub_4A06D0(v20, v29);
      pArg32 = pArg3;
    }
  }
  if ( *(this + 244) != 3 )
  {
    fld_e2463 = *(this + 246);
    if ( fld_e2463 != 6 && fld_e2463 != 9 )
    {
      fld_e250 = *(this + 250);
      if ( fld_e250 != 0 )
        *(this + 99) -= fld_e250;
      v23 = sub_607990(this) - 200;
      if ( v23 > 0 )
        *(this + 250) = -60 * v23 * (*(this + 99) + 100) / 400 / 100;
      else
        *(this + 250) = 0;
      *(this + 99) += *(this + 250);
    }
  }
  *(this + 255) = nArg22;
  v42 = 0;
  pThis_100 = this + 256;
  do
  {
    *pThis_100 = (*(int (/*thiscall*/ **)(int *, int))(*this + 116))(this, v42);
    v24 = ++v42 < 3;
    ++pThis_100;
  }
  while ( v24 );
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 576))(this) != 0 )
  {
    pObj2 = (*(int (/*thiscall*/ **)(int *))(*this + 576))(this);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) != 0 )
    {
      pObj4 = (*(int (/*thiscall*/ **)(int *))(*this + 576))(this);
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 1032))(pObj4) == 2 )
      {
        for ( i = 0; i < 18; ++i )
        {
          if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 792))(pObj4, i) != 0 )
          {
            pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 792))(pObj4, i);
            (*(void (/*thiscall*/ **)(int, int, float *, int, int, int *))(*(uint32_t *)pObj + 136))(
              pObj,
              nArg22,
              pArg32,
              nArg4,
              1,
              this + 97);
          }
        }
      }
    }
  }
  return sub_5FF9C0(nArg22, pArg32, nArg4);  // 【CNRDPassiveObject__vmt1F4】
}


// ------------------------------------------------------------
// 0x608CD0 CNGunnerBullet__vmt2A8
// ------------------------------------------------------------
// CNGunnerBullet 碰撞响应槽（vmt2A8，70 行）：sub_6073E0/sub_6078B0（弹道反弹族【推断】）+ sub_608730（银弹粒子）+
// sub_41A5E0（P24 写）——子弹撞墙反弹并残留拖尾。
void /*thiscall*/ CNGunnerBullet__vmt2A8(int this, int nArg2)
{
  int fld_2B4; // ebx
  int pObj; // esi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int pObj2; // ebx
  void *v9; // eax
  int v10; // [esp-4h] [ebp-10h]
  int v11; // [esp+14h] [ebp+8h]

  fld_2B4 = *(uint32_t *)(this + 692);
  CNRDPassiveObject__vmt2A8((uint32_t *)this, nArg2);
  if ( fld_2B4 != nArg2 && *(uint8_t *)(this + 1038) == 0 )
  {
    pObj = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);
    if ( pObj != 0 )
    {
      *(uint32_t *)(this + 980) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 8 )
      {
        *(uint32_t *)(this + 972) = *(uint8_t *)(pObj + 8596) != 0;
      }
      else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 7 )
      {
        *(uint32_t *)(this + 972) = 2;
      }
      else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 18 )
      {
        *(uint32_t *)(this + 972) = 3;
      }
      else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 20 )
      {
        *(uint32_t *)(this + 972) = rand() % 4;
      }
      else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 27 )
      {
        *(uint32_t *)(this + 972) = 0;
      }
      *(uint32_t *)(this + 976) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1096))(pObj);
      *(uint32_t *)(this + 696) = sub_41A5E0(pObj + 8502);
      sub_6078B0((uint32_t *)this);
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1332))(pObj);
      v6 = v5;
      if ( v5 != -1 )
      {
        v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1160))(pObj, v5);
        if ( v11 != 0 )
        {
          v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, v6);
          sub_6073E0((uint32_t *)this, v11, v7);
        }
        else
        {
          off_77F3FC(aCriticalError_43, v6);
        }
      }
      pObj2 = *(uint32_t *)(pObj + 8656);
      if ( pObj2 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj2 + 136))(*(uint32_t *)(pObj + 8656)) != 0 )
      {
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 132))(pObj2);
        v9 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj2);
        sub_608730((int *)this, v9, v10);
      }
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1104))(pObj, 8);
      *(uint8_t *)(this + 1038) = 1;
    }
  }
}



// ------------------------------------------------------------
// 0x608EA0 sub_608EA0
// ------------------------------------------------------------
int /*thiscall*/ sub_608EA0(int this)
{
  int fld_2144; // eax
  int result; // eax

  if ( *(uint32_t *)(this + 6556) != 22 )
    return 0;
  fld_2144 = *(uint32_t *)(this + 8516);
  if ( fld_2144 != 13 && fld_2144 != 36 )
    return 0;
  result = 1;
  if ( *(uint32_t *)(this + 8968) != 1 || *(uint8_t *)(this + 9301) != 0 )
    return 0;
  return result;
}



// ------------------------------------------------------------
// 0x608EE0 sub_608EE0
// ------------------------------------------------------------
int /*thiscall*/ sub_608EE0(int this)
{
  *(uint32_t *)(this + 972) = -1;
  *(uint32_t *)(this + 976) = -1;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint8_t *)(this + 984) = 0;
  *(uint8_t *)(this + 985) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x608F10 sub_608F10
// ------------------------------------------------------------
char /*thiscall*/ sub_608F10(uint32_t *this, uint32_t *pArg2, int nArg3)
{
  int v4; // eax
  int v5; // eax

  v4 = sub_41A5E0((unsigned int)(pArg2 + 1));
  *(this + 244) = v4;
  *(this + 245) = nArg3;
  if ( v4 == 13 || v4 == 36 )
  {
    v5 = sub_47EF20(pArg2, 2u, nArg3, -1, -1, 11);
    LOBYTE(v4) = sub_607260(this + 248, v5, -1, 0, 0);
  }
  return v4;
}



// ------------------------------------------------------------
// 0x608F70 CNGunnerSubWeaponBullet__vmt158
// ------------------------------------------------------------
int /*thiscall*/ CNGunnerSubWeaponBullet__vmt158(int this, int nArg2)
{
  int result; // eax
  char *fld_3D0; // eax

  IRDCollisionObject__vmt158((char *)this, nArg2);
  result = *(uint32_t *)(this + 976);
  if ( result == 12 || result == 13 || result == 36 || result == 14 || result == 40 )
  {
    fld_3D0 = (char *)sub_47E720(2, *(uint32_t *)(this + 976));
    result = sub_47EFD0(fld_3D0, 0.0, *(uint32_t *)(this + 980), *(uint32_t *)(this + 972), *(uint32_t *)(this + 972), 0);
    *(float *)(this + 388) = (float)result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x608FE0 CNGunnerSubWeaponBullet__vmt14C
// ------------------------------------------------------------
// CNGunnerSubWeaponBullet 主循环槽（vmt14C，101 行）：sub_608EA0/6072C0 + sub_4E5F70（硬直率掷）+ sub_699000 ——
// 副武器（Musket/BowGun）子弹的飞行/命中编排，与主武器 CNGunnerBullet 共享几何族。
char /*usercall*/ CNGunnerSubWeaponBullet__vmt14C@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // eax
  int pObj2; // edi
  int pObj; // ecx
  char v7; // bl
  int v8; // edx
  int v9; // eax
  double v10; // st7
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  float v21; // [esp+4h] [ebp-1Ch] BYREF
  float v22; // [esp+8h] [ebp-18h]
  float v23; // [esp+Ch] [ebp-14h]
  int v24; // [esp+10h] [ebp-10h]
  int v25; // [esp+14h] [ebp-Ch]
  int v26; // [esp+18h] [ebp-8h]
  int v27; // [esp+1Ch] [ebp-4h]

  CNRDPassiveObject__vmt14C(pArg1);
  v4 = *(uint32_t *)(pArg1 + 976);
  if ( v4 == 14 )
  {
    pObj2 = __RTDynamicCast(
           *(uint32_t *)(pArg1 + 692),
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &CNGunner `RTTI Type Descriptor',
           0);
    LOBYTE(v4) = *(uint8_t *)(pArg1 + 985);
    if ( (uint8_t)v4 == 0 && pObj2 != 0 )
    {
      LOBYTE(v4) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 308))(pObj2);
      if ( (uint8_t)v4 != 0 )
      {
        pObj = *(uint32_t *)(pObj2 + 9344);
        if ( pObj != 0 )
        {
          LOBYTE(v4) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 724))(pObj);
          if ( (uint8_t)v4 == 0 )
          {
            v7 = *(uint8_t *)(pObj2 + 9368);
            v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(uint32_t *)(pArg1 + 112) + 104) + 44))(*(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 104));
            if ( v4 >= (uint8_t)(v7 != 0 ? 0 : 0x5A) )
            {
              v8 = *(uint32_t *)pArg1;
              v21 = 0.0;
              v22 = 0.0;
              v23 = 0.0;
              v24 = 0;
              v25 = 0;
              v26 = 0;
              if ( (*(int (/*thiscall*/ **)(int, int))(v8 + 152))(pArg1, nArg3) != 0 )
                v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 3;
              else
                v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 3;
              v27 = v9;
              v10 = (double)v9;
              v11 = *(uint32_t *)pArg1;
              v21 = v10;
              v12 = (*(int (/*thiscall*/ **)(int))(v11 + 124))(pArg1);
              v13 = *(uint32_t *)pArg1;
              v27 = v12;
              v22 = (float)v12;
              v14 = (*(int (/*thiscall*/ **)(int))(v13 + 128))(pArg1);
              v15 = *(uint32_t *)(pObj2 + 9344);
              v27 = v14 + 3;
              v23 = (float)(v14 + 3);
              sub_4E5F70(nArg2, pArg1, v15, &v21, 1, 1);
              LOBYTE(v4) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 312))(pArg1, 1);
              *(uint8_t *)(pArg1 + 985) = 1;
            }
          }
        }
      }
    }
  }
  else if ( v4 == 13 || v4 == 36 )
  {
    v16 = sub_699000(pArg1 + 64);  // 【clock_now(clk)】
    if ( sub_6072C0((uint8_t *)(pArg1 + 992), v16) != 0 )
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 352))(pArg1);
    LOBYTE(v4) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1);
    if ( (uint8_t)v4 != 0 )
    {
      v17 = __RTDynamicCast(
              *(uint32_t *)(pArg1 + 692),
              0,
              &IRDCollisionObject `RTTI Type Descriptor',
              &CNGunner `RTTI Type Descriptor',
              0);
      if ( v17 == 0 || (LOBYTE(v4) = sub_608EA0(v17), (uint8_t)v4 == 0) )
        LOBYTE(v4) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 312))(pArg1, 0);
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x6091B0 CNGunnerSubWeaponBullet__vmt12C
// ------------------------------------------------------------
// CNGunnerSubWeaponBullet 消亡联动槽（vmt12C）：字符串证据「DIFFUSION_GUN_EX」（音效 TAG —— 散弹枪 EX）。
// sub_42F220 + sub_4918E0（动画盒世界坐标，P37-2 obj+60 边界族）——散弹 EX 的消亡演出。
void /*userpurge*/ CNGunnerSubWeaponBullet__vmt12C(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3)
{
  int pObj; // eax
  int pObj4; // eax
  int nArg32; // edi
  char *v7; // eax
  int v8; // eax
  int pObj2; // ecx
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  int v12; // eax
  int pObj3; // edi
  int v14; // eax
  int v15; // edx
  int v16; // [esp-20h] [ebp-30h]
  int v17; // [esp-1Ch] [ebp-2Ch]
  int v18; // [esp-18h] [ebp-28h]
  int v19; // [esp-14h] [ebp-24h]
  int v21; // [esp+8h] [ebp-8h]
  int v22; // [esp+Ch] [ebp-4h]

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 684))(pArg1) != 0
    && (pObj = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 684))(pArg1),
        (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273) != 0)
    && (pObj4 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 684))(pArg1),
        *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 1032))(pObj4) == 2) )
  {
    nArg32 = nArg3;
    if ( pArg1[244] == 40 && ((uint32_t *)nArg3 == pArg1 || pArg1[247] == nArg3) )
    {
      if ( pArg1[247] != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 308))(pArg1, nArg2) != 0 )
        {
          v7 = (char *)sub_47E720(2, pArg1[244]);
          v21 = sub_47EFD0(v7, COERCE_FLOAT(1), pArg1[245], pArg1[243], pArg1[243], 0);
          v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[247] + 200))(pArg1[247]);
          pObj2 = pArg1[247];
          if ( v8 != 0 )
          {
            v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 200))(pObj2);
            v11 = sub_42F220(v10);
            v12 = sub_4918E0(v11, 2);
          }
          else
          {
            v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 192))(pObj2);
          }
          v22 = v12;
          pObj3 = pArg1[247];
          v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 128))(pObj3) - (uint64_t)((double)v22 * -0.69999999);
          v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 124))(pObj3) + 1;
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 120))(pObj3);
          v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 684))(pArg1);
          sub_4E4A50(v14, 40002, v21, v16, v17, v18, v19, 0, 0, 0);
          nArg32 = nArg3;
        }
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*pArg1 + 212))(pArg1, "DIFFUSION_GUN_EX", -1, 0);
      }
      if ( pArg1[247] == nArg32 )
      {
        v15 = *pArg1;
        pArg1[247] = 0;
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v15 + 312))(pArg1, 0);
      }
    }
    CNRDPassiveObject__vmt12C(pArg1, nArg32);
  }
  else
  {
    CNRDPassiveObject__vmt12C(pArg1, nArg3);
  }
}



// ------------------------------------------------------------
// 0x609380 CNGunnerSubWeaponBullet__vmt28C
// ------------------------------------------------------------
int /*thiscall*/ CNGunnerSubWeaponBullet__vmt28C(uint32_t *this, bool *pArg2)
{
  uint32_t *fld_e87; // edx
  int fld_e178; // edx

  fld_e87 = (uint32_t *)*(this + 87);
  *pArg2 = fld_e87 != nullptr && (*(this + 88) - (int)fld_e87) >> 2 != 0 && *fld_e87 == 1;
  fld_e178 = *(this + 178);
  if ( fld_e178 != 0 && (*(this + 179) - fld_e178) >> 2 != 0 )
    return sub_41ACF0(*(this + 178));
  else
    return 0;
}



// ------------------------------------------------------------
// 0x6093E0 CNGunnerSubWeaponBullet__vmt1F4
// ------------------------------------------------------------
// CNGunnerSubWeaponBullet 命中表现槽（vmt1F4）：字符串证据「DIFFUSION_GUN_CHARGE」（蓄力音 TAG）+ sub_4A06D0（挂点跟随）。
int /*thiscall*/ CNGunnerSubWeaponBullet__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int v5; // eax
  float *pArg32; // ebx
  uint32_t *pArg22; // edi
  uint32_t *fld_e36; // eax
  int v9; // edx
  int v10; // eax
  uint32_t *v11; // eax
  int v12; // eax
  int fld_e2472; // edi
  double v14; // st7
  int v15; // ebx
  int nRand2; // eax
  int nRand; // [esp-4h] [ebp-18h]
  int v19; // [esp+0h] [ebp-14h]
  int fld_e247; // [esp+Ch] [ebp-8h]

  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
  pArg32 = pArg3;
  pArg22 = pArg2;
  if ( __RTDynamicCast(v5, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0) != 0
    && *(this + 244) == 40
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0
    && *(this + 247) == 0 )
  {
    fld_e36 = (uint32_t *)*(this + 36);
    v9 = *this;
    *(this + 247) = (int)pArg2;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v9 + 196))(this, *fld_e36);
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 60))(this);
    v11 = (uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v10 + 104) + 16))(*(uint32_t *)(v10 + 104)) + 15);
    *v11 = 0;
    v11[1] = 0;
    v11[2] = 0;
    v11[3] = 0;
    v11[4] = 0;
    v11[5] = 0;
    v12 = (*(int (/*thiscall*/ **)(int *))(*this + 60))(this);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v12 + 104) + 4))(*(uint32_t *)(v12 + 104), 0);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);
    fld_e247 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 247) + 120))(*(this + 247));
    fld_e2472 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 247) + 124))(*(this + 247)) + 1;
    v14 = pArg3[5] * 0.5 + pArg3[2];
    v15 = *this;
    nRand = rand() % 6 + (uint64_t)v14 - 3;
    nRand2 = rand();
    (*(void (/*thiscall*/ **)(int *, int, int, int))(v15 + 112))(this, nRand2 % 6 + fld_e247 - 3, fld_e2472, nRand);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 60))(this, *(this + 247));
    sub_4A06D0(v19);
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t))(*this + 212))(this, "DIFFUSION_GUN_CHARGE", -1, 0);
    pArg22 = pArg2;
    pArg32 = pArg3;
  }
  return CNRDPassiveObject__vmt1F4(this, pArg22, pArg32, pszArg4);
}



// ------------------------------------------------------------
// 0x609550 CNGunnerSubWeaponBullet__vmt2A8
// ------------------------------------------------------------
// CNGunnerSubWeaponBullet 碰撞响应槽（vmt2A8）：字符串证据「R_DIFFUSION_GUNA」（音效 TAG）+ sub_608F10。
void /*thiscall*/ CNGunnerSubWeaponBullet__vmt2A8(int this, int nArg2)
{
  int fld_2B4; // ebx
  int pObj; // esi
  int v5; // ebx
  int v6; // eax
  uint32_t *v7; // eax

  fld_2B4 = *(uint32_t *)(this + 692);
  CNRDPassiveObject__vmt2A8((uint32_t *)this, nArg2);
  if ( fld_2B4 != nArg2 && *(uint8_t *)(this + 984) == 0 )
  {
    pObj = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);
    if ( pObj != 0 )
    {
      *(uint32_t *)(this + 972) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1332))(pObj);
      if ( v5 != -1 )
      {
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1140))(pObj);
        v7 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 1160))(pObj, v5, v6);
        sub_608F10((uint32_t *)this, v7, v5);
      }
      if ( *(uint32_t *)(this + 976) == 40 )
        sub_406D60("R_DIFFUSION_GUNA");
    }
    *(uint8_t *)(this + 984) = 1;
  }
}



// ------------------------------------------------------------
// 0x609600 sub_609600
// ------------------------------------------------------------
int /*thiscall*/ sub_609600(uint32_t *this, int nArg2)
{
  *(this + 243) = 0;
  *(this + 244) = 0;
  *(this + 249) = 0;
  *(this + 248) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 724))(this);
}



// ------------------------------------------------------------
// 0x609630 sub_609630
// ------------------------------------------------------------
// 蓄力参数插值：sub_4049C0（P30/P36 同款 lerp）——【推断：散弹枪 EX 蓄力 0→1 进度的插值】。
int /*thiscall*/ sub_609630(float *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // ebx
  int pThis_74; // ecx
  int v7; // eax
  int v8; // edi
  double fld_e250; // st7
  int result; // eax
  int pThis_1C; // ecx
  uint32_t v12[3]; // [esp+Ch] [ebp-18h] BYREF
  int v13; // [esp+18h] [ebp-Ch]
  int pThis_742; // [esp+1Ch] [ebp-8h]
  int v15; // [esp+20h] [ebp-4h]

  v12[0] = nArg2;
  v12[1] = nArg3;
  v5 = 0;
  v12[2] = nArg4;
  v13 = 16 - (uint32_t)v12;
  while ( 1 )
  {
    pThis_74 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 116))(this, v5);
    v15 = v12[v5];
    v7 = *(uint32_t *)this;
    pThis_742 = pThis_74;
    v8 = abs32(v15 - pThis_74);
    if ( v8 > 3 * (*(int (/*thiscall*/ **)(float *))(v7 + 708))(this) )
      break;
    fld_e250 = sub_4049C0(0.0, *(this + 250), v8, *((uint32_t *)this + 251));  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    if ( v15 >= pThis_742 )
    {
      if ( v15 == pThis_742 )
        fld_e250 = 0.0;
    }
    else
    {
      fld_e250 = fld_e250 * -1.0;
    }
    result = 4 * v5;
    pThis_1C = 4 * v5++ + v13 + *((uint32_t *)this + 28);
    *(float *)((char *)v12 + pThis_1C) = fld_e250;
    if ( v5 >= 3 )
      return result;
  }
  (*(void (/*thiscall*/ **)(float *, int, int, int))(*(uint32_t *)this + 112))(this, nArg2, nArg3, nArg4);
  *(uint32_t *)(*((uint32_t *)this + 28) + 16) = 0;
  *(uint32_t *)(*((uint32_t *)this + 28) + 20) = 0;
  *(uint32_t *)(*((uint32_t *)this + 28) + 24) = 0;
  return 0;
}



// ============================================================
// 【分区 7】连接体/可割草丛/地图物件（0x609720-0x60B920）
// CNRDJoint（连接体）/ CNCutableGrass（可割草丛）/ CNMapObject（可破坏地图物件，
//   定义表装载与 monster_parser 同族）—— 地图可破坏生态的 PO 侧
// ============================================================
// ------------------------------------------------------------
// 0x609720 CNRDJoint__vmt2C8
// ------------------------------------------------------------
int /*thiscall*/ CNRDJoint__vmt2C8(uint32_t *this, int nArg2)
{
  int result; // eax

  if ( *(this + 243) == 2 )
    return off_77F3FC(aCriticalError_44);
  *(this + 243) = nArg2;
  *(this + 248) = sub_699000((int)(this + 2));
  result = *(this + 243) - 2;
  if ( *(this + 243) == 2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x609790 CNRDJoint__vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNRDJoint__vmt12C(uint32_t *this, int nArg2)
{
  int result; // eax

  CNRDPassiveObject__vmt12C(this, nArg2);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
  if ( nArg2 == result )
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*this + 680))(this, this);
  if ( nArg2 == *(this + 244) )
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 728))(this);
  return result;
}



// ------------------------------------------------------------
// 0x6097E0 CNRDJoint__vmt2D8
// ------------------------------------------------------------
void /*thiscall*/ CNRDJoint__vmt2D8(uint32_t *this)
{
  *(this + 244) = 0;
}



// ------------------------------------------------------------
// 0x6097F0 CNRDJoint__vmt2CC
// ------------------------------------------------------------
int /*thiscall*/ CNRDJoint__vmt2CC(uint8_t *this)
{
  int result; // eax

  if ( *(this + 264) != 1 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 196))(this, 0);
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x609820 sub_609820
// ------------------------------------------------------------
// 蓄力辅助（35 行）→ 转调 sub_609630 —— 蓄力曲线消费侧。
int /*thiscall*/ sub_609820(int this)
{
  int fld_3D0; // eax
  int fld_3D02; // ecx
  int v4; // eax
  int fld_3D03; // ecx
  int v6; // eax
  float v7; // edi
  int v8; // eax
  int fld_3D04; // edi
  int v11; // [esp+8h] [ebp-8h] BYREF
  int v12; // [esp+Ch] [ebp-4h] BYREF

  fld_3D0 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 976) + 120))(*(uint32_t *)(this + 976));
  fld_3D02 = *(uint32_t *)(this + 976);
  *(uint32_t *)(this + 980) = fld_3D0;
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_3D02 + 124))(fld_3D02);
  fld_3D03 = *(uint32_t *)(this + 976);
  *(uint32_t *)(this + 984) = v4;
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_3D03 + 128))(fld_3D03);
  v7 = *(float *)this;
  *(uint32_t *)(this + 988) = v6;
  v8 = (*(int (/*thiscall*/ **)(int))(LODWORD(v7) + 708))(this);
  (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, int))(LODWORD(v7) + 172))(
    this,
    &v11,
    &v12,
    *(uint32_t *)(this + 976),
    v8);
  sub_609630((float *)this, v11, v12, *(uint32_t *)(this + 988));
  fld_3D04 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 976) + 120))(*(uint32_t *)(this + 976));
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) < fld_3D04 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 148))(this, 1);
  else
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 148))(this, 0);
}



// ------------------------------------------------------------
// 0x6098E0 CNRDJoint__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNRDJoint__vmt14C(uint32_t *this)
{
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 244) != 0 )
    sub_609820((int)this);
  if ( *(this + 243) == 1 )
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 720))(this);
  result = *(this + 243) - 2;
  if ( *(this + 243) == 2 )
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 716))(this);
  return result;
}



// ------------------------------------------------------------
// 0x609920 sub_609920
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_609920(uint32_t *this, int nArg2)
{
  uint32_t *pThis_6E8; // ecx
  int v3; // esi
  unsigned int v4; // edx
  int *nArg22; // eax
  unsigned int result; // eax

  pThis_6E8 = this + 1768;
  v3 = pThis_6E8[1];
  if ( v3 != 0 )
    v4 = (pThis_6E8[2] - v3) >> 2;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (pThis_6E8[3] - v3) >> 2 )
    return sub_4E75F0((int)pThis_6E8, pThis_6E8[2], 1u, &nArg2);
  nArg22 = (int *)pThis_6E8[2];
  *nArg22 = nArg2;
  result = (unsigned int)(nArg22 + 1);
  pThis_6E8[2] = result;
  return result;
}



// ------------------------------------------------------------
// 0x609980 CNRDJoint__vmt2BC
// ------------------------------------------------------------
// CNRDJoint 命中结算槽（vmt2BC）：sub_45EBE0（飘字参数）+ sub_609920 ——
// 连接体（Joint，链条/绳索类 PO【推断】）被攻击时的结算。
unsigned int /*thiscall*/ CNRDJoint__vmt2BC(float *this, const void *pArg2, size_t Size)
{
  int pThis_1D; // esi
  int pThis_1D2; // eax
  unsigned int result; // eax
  int pThis_2C4; // edi
  size_t v8; // eax
  float v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // edi
  int v13; // eax
  uint16_t v14[4]; // [esp+Ch] [ebp-10h] BYREF
  int v15; // [esp+14h] [ebp-8h]
  uint32_t *v16; // [esp+24h] [ebp+8h]
  size_t Sizea; // [esp+28h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)pArg2, Size);
  qmemcpy(v14, pArg2, Size);
  pThis_1D = sub_45EBE0(*((uint32_t **)this + 29), v14[2], v14[3]);
  pThis_1D2 = sub_45EBE0(*((uint32_t **)this + 29), v14[0], v14[1]);
  result = __RTDynamicCast(pThis_1D2, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  v16 = (uint32_t *)result;
  if ( pThis_1D != 0 && result != 0 )
  {
    pThis_2C4 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 708))(this);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_1D + 152))(pThis_1D) != 0 )
      pThis_2C4 = -pThis_2C4;
    v8 = pThis_2C4 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_1D + 120))(pThis_1D);
    v9 = *this;
    Sizea = v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_1D + 128))(pThis_1D);
    v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_1D + 124))(pThis_1D, v10);
    (*(void (/*thiscall*/ **)(float *, size_t, int))(LODWORD(v9) + 112))(this, Sizea, v11);
    v12 = *(uint32_t *)this;
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_1D + 152))(pThis_1D);
    (*(void (/*thiscall*/ **)(float *, int))(v12 + 148))(this, v13);
    (*(void (/*thiscall*/ **)(float *, uint32_t *))(*(uint32_t *)this + 680))(this, v16);
    *(this + 250) = (float)v15;
    *((uint32_t *)this + 244) = pThis_1D;
    return sub_609920(v16, (int)this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x609A90 sub_609A90
// ------------------------------------------------------------
int /*thiscall*/ sub_609A90(int this)
{
  *(uint32_t *)(this + 96) = 1057;
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint8_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 4;
  *(uint8_t *)(this + 1000) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x609AD0 CNCutableGrass__vmtC
// ------------------------------------------------------------
char /*thiscall*/ CNCutableGrass__vmtC(int this)
{
  char result; // al

  CNRDPassiveObject__vmtC((int *)this);
  result = *(uint8_t *)(this + 972);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 604))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x609AF0 sub_609AF0
// ------------------------------------------------------------
int /*thiscall*/ sub_609AF0(uint32_t *this, uint32_t *pArg2)
{
  if ( pArg2 == this
    || (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t *))(*this + 488))(this, pArg2) == 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 128))(pArg2) > *(this + 40) )
  {
    return 4;
  }
  if ( *(float *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 60))(pArg2) + 16) > 0.0 )
    return 1;
  if ( *(float *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 60))(pArg2) + 16) < 0.0 )
    return 0;
  if ( *(float *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 60))(pArg2) + 20) == 0.0 )
    return 4;
  else
    return (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 152))(pArg2);
}



// ------------------------------------------------------------
// 0x609BA0 sub_609BA0
// ------------------------------------------------------------
// 连接体/草丛辅助（28 行，无外部调用）——【推断：状态字段复位】。
int /*thiscall*/ sub_609BA0(int *this)
{
  int (/*thiscall*/ ***fld_e246)(uint32_t, int); // ecx
  int result; // eax
  int fld_e252; // esi
  bool fld_e253; // zf
  int pObj; // ecx

  fld_e246 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 246);
  if ( fld_e246 != nullptr )
    result = (**fld_e246)(fld_e246, 1);
  fld_e252 = *(this + 252);
  fld_e253 = fld_e252 == *(this + 253);
  *(this + 246) = 0;
  if ( !fld_e253 )
  {
    do
    {
      pObj = *(uint32_t *)(fld_e252 + 4);
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
      *(uint32_t *)(fld_e252 + 4) = 0;
      result = *(this + 253);
      fld_e252 += 8;
    }
    while ( fld_e252 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x609C00 CNCutableGrass__vmt2D0
// ------------------------------------------------------------
int /*thiscall*/ CNCutableGrass__vmt2D0(uint32_t **this)
{
  return ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, **(this + 36));
}



// ------------------------------------------------------------
// 0x609C20 sub_609C20
// ------------------------------------------------------------
// 定时器复位辅助：sub_4926A0（vmtCC 定时器链表复位，CNRDObject.h 定案）——草丛摇摆计时复位。
char /*thiscall*/ sub_609C20(int *this, int nArg2)
{
  int fld_e249; // eax
  int fld_e36; // eax
  uint32_t *v5; // eax

  fld_e249 = *(this + 249);
  if ( nArg2 != fld_e249 )
  {
    LOBYTE(fld_e249) = *((uint8_t *)this + 988);
    if ( (uint8_t)fld_e249 != 0 )
    {
      if ( nArg2 == 4 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 34));
        LOBYTE(fld_e249) = sub_4926A0(*(this + 30));
        *(this + 249) = 4;
      }
      else
      {
        fld_e36 = *(this + 36);
        if ( nArg2 != 0 )
          v5 = (uint32_t *)(fld_e36 + 8);
        else
          v5 = (uint32_t *)(fld_e36 + 4);
        (*(void (/*stdcall*/ **)(uint32_t))(*this + 196))(*v5);
        LOBYTE(fld_e249) = sub_4926A0(*(this + 30));
        *(this + 249) = nArg2;
      }
    }
  }
  return fld_e249;
}



// ------------------------------------------------------------
// 0x609CA0 sub_609CA0
// ------------------------------------------------------------
void /*thiscall*/ sub_609CA0(int *this)
{
  int i; // edi
  int fld_e178; // ecx
  int v4; // ebx
  int v5; // eax

  for ( i = 1; i < 3; ++i )
  {
    fld_e178 = *(this + 178);
    if ( fld_e178 != 0 && (*(this + 179) - fld_e178) >> 2 > (unsigned int)i )
    {
      v4 = *this;
      v5 = sub_41ACF0(fld_e178 + 4 * i);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v4 + 212))(this, v5, -1, 0, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x609CF0 CNCutableGrass__vmt200
// ------------------------------------------------------------
// CNCutableGrass 表现壳槽（vmt200）：sub_609CA0 + sub_4600B0（演播层）——
// 草丛被攻击时的受击表现（可割草 PO）。
int /*thiscall*/ CNCutableGrass__vmt200(int this, int nArg2, float *pArg3, char pszArg4)
{
  int *fld_3D8; // edx
  int *fld_15C; // ecx
  int v7; // eax
  int v8; // edi
  int pThis_7C; // eax
  int pThis_78; // eax
  void *fld_74; // ecx
  uint8_t v13[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v15; // [esp+10h] [ebp-14h]
  int v16; // [esp+14h] [ebp-10h]
  int v17; // [esp+20h] [ebp-4h]
  int v18; // [esp+34h] [ebp+10h]

  v18 = CNRDPassiveObject__vmt200((int *)this, nArg2, pArg3, pszArg4);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 716))(this);
  if ( *(uint32_t *)(this + 976) >= *(uint32_t *)(this + 980) )
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, *(uint8_t *)(this + 972));
  else
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 720))(this);
  fld_3D8 = *(int **)(this + 984);
  if ( fld_3D8 != nullptr )
  {
    fld_15C = *(int **)(this + 348);
    if ( fld_15C != nullptr && (*(uint32_t *)(this + 352) - (int)fld_15C) >> 2 != 0 )
      v7 = *fld_15C;
    else
      v7 = 0;
    v8 = *fld_3D8;
    pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v7);
    pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v8 + 40))(*(uint32_t *)(this + 984), pThis_78);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 984) + 12))(*(uint32_t *)(this + 984), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 984) + 92))(*(uint32_t *)(this + 984), v13);
    fld_74 = *(void **)(this + 116);
    v17 = 0;
    sub_4600B0(fld_74, 2, 0, (int)v13);
    v17 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v15 = 0;
    v16 = 0;
  }
  sub_609CA0((int *)this);
  *(uint8_t *)(this + 988) = 0;
  return v18;
}



// ------------------------------------------------------------
// 0x609E20 CNCutableGrass__vmt14C
// ------------------------------------------------------------
// CNCutableGrass 主循环槽（vmt14C，104 行）：sub_609AF0/sub_609C20 ——
// 【推断：风中摇摆 + 被割状态机（割草小游戏的 PO 载体）】。
char /*thiscall*/ CNCutableGrass__vmt14C(int this)
{
  unsigned int v2; // ebx
  int fld_3E0; // eax
  int fld_74; // eax
  int v5; // ecx
  int v6; // eax
  int fld_742; // ecx
  int v8; // edx
  uint32_t *v9; // edi
  int v10; // eax
  char result; // al
  int fld_743; // eax
  int v13; // ecx
  int v14; // eax
  unsigned int v15; // ebx
  int fld_744; // ecx
  int v17; // edx
  int pObj; // edi
  uint32_t pBuf[6]; // [esp+Ch] [ebp-1Ch] BYREF
  int v20; // [esp+24h] [ebp-4h]

  CNRDPassiveObject__vmt14C(this);
  if ( *(uint8_t *)(this + 988) != 0 )
  {
    v2 = 0;
    if ( *(uint32_t *)(this + 992) != 0 )
    {
      fld_3E0 = sub_609AF0((uint32_t *)this, *(uint32_t **)(this + 992));
      if ( fld_3E0 == 4 )
        *(uint32_t *)(this + 992) = 0;
      sub_609C20((int *)this, fld_3E0);
    }
    if ( *(uint32_t *)(this + 992) == 0 )
    {
      fld_74 = *(uint32_t *)(this + 116);
      v5 = *(uint32_t *)(fld_74 + 120);
      v6 = fld_74 + 116;
      v20 = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 2 : 0;
      if ( v20 > 0 )
      {
        while ( 1 )
        {
          fld_742 = *(uint32_t *)(this + 116);
          v8 = *(uint32_t *)(fld_742 + 120);
          if ( v8 != 0 && v2 < (*(uint32_t *)(fld_742 + 124) - v8) >> 2 )
            v9 = *(uint32_t **)(v8 + 4 * v2);
          else
            v9 = nullptr;
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v9 + 40))(v9, 17) != 0 )
          {
            v10 = sub_609AF0((uint32_t *)this, v9);
            if ( v10 != 4 )
              break;
          }
          if ( (int)++v2 >= v20 )
            goto LABEL_20;
        }
        *(uint32_t *)(this + 992) = v9;
        sub_609C20((int *)this, v10);
      }
    }
  }
LABEL_20:
  result = *(uint8_t *)(this + 972);
  if ( result != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 604))(this, 1);
    fld_743 = *(uint32_t *)(this + 116);
    v13 = *(uint32_t *)(fld_743 + 120);
    v14 = fld_743 + 116;
    v15 = 0;
    if ( v13 != 0 )
      v20 = (*(uint32_t *)(v14 + 8) - v13) >> 2;
    else
      v20 = 0;
    if ( v20 > 0 )
    {
      do
      {
        fld_744 = *(uint32_t *)(this + 116);
        v17 = *(uint32_t *)(fld_744 + 120);
        if ( v17 != 0 && v15 < (*(uint32_t *)(fld_744 + 124) - v17) >> 2 )
          pObj = *(uint32_t *)(v17 + 4 * v15);
        else
          pObj = 0;
        if ( (*(uint8_t *)(this + 1000) == 0
           || *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj) + 128) != 0)
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 360))(pObj, this) == 0 )
        {
          memset(pBuf, 0, sizeof(pBuf));
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, uint32_t *))(*(uint32_t *)pObj + 480))(pObj, this, pBuf) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 356))(pObj, this);
            (*(void (/*thiscall*/ **)(int, int, uint32_t *, uint32_t))(*(uint32_t *)this + 512))(this, pObj, pBuf, 0);
          }
        }
        ++v15;
      }
      while ( (int)v15 < v20 );
    }
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 604))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x609FF0 sub_609FF0
// ------------------------------------------------------------
// 草丛定义表重建（与 0x602E80/0x606650 同族）：sub_41FEB0/44BD00/44BD30 逐词读取 + sub_52E630 +
// sub_5E51F0/sub_63A7C0 —— 地图可割草丛的参数装载。
void /*thiscall*/ sub_609FF0(int this, int nArg2, unsigned int uArg3, int pArg4)
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

  v4 = *(void **)(pArg4 + 4);
  v28[0] = *(void **)pArg4;
  fld_4 = *(uint32_t *)(this + 4);
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
    else
      fld_8 = 0;
    if ( 0x1FFFFFFF - fld_8 < uArg3 )
      sub_52E630(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);
      v20 = (fld_83 - nArg2) >> 3 < uArg3;
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;
      if ( v20 )
      {
        sub_44BD30(nArg2, fld_83, nArg2 + v21);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 3);
        fld_85 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);
        fld_86 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        sub_41FEB0(nArg2, fld_86 - v30, v28);
      }
      else
      {
        v23 = fld_83 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);
        sub_44BD00(nArg2, v23, fld_832);
        sub_41FEB0(nArg2, nArg2 + v30, v28);
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )
        v11 = (fld_C >> 1) + fld_C;
      else
        v11 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
      else
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
        else
          fld_88 = 0;
        v11 = uArg3 + fld_88;
      }
      v31 = 8 * v11;
      pMem = (char *)operator new(8 * v11);
      fld_42 = *(uint32_t *)(this + 4);
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, nArg2, pMem);
      sub_63A7C0(v32, uArg3, v28);
      sub_44BD30(nArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;
      else
        fld_89 = 0;
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &pMem[v31];
      *(uint32_t *)(this + 8) = &pMem[8 * v17];
      *(uint32_t *)(this + 4) = pMem;
    }
  }
}


// ------------------------------------------------------------
// 0x60A240 sub_60A240
// ------------------------------------------------------------
void /*thiscall*/ sub_60A240(int this, int nArg2)
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
  else
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 3 )
  {
    fld_82 = *(uint32_t *)(this + 8);
    sub_63A7C0(fld_82, 1, nArg2);
    *(uint32_t *)(this + 8) = fld_82 + 8;
  }
  else
  {
    sub_609FF0(this, *(char **)(this + 8), 1u, nArg2);
  }
}



// ------------------------------------------------------------
// 0x60A2B0 CNCutableGrass__vmt2C4
// ------------------------------------------------------------
void /*thiscall*/ CNCutableGrass__vmt2C4(void *this, int nArg2, int nArg3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = nArg2;
  v3[1] = nArg3;
  sub_60A240((int)this + 1004, (int)v3);
}



// ------------------------------------------------------------
// 0x60A2E0 CNCutableGrass__vmt2C8
// ------------------------------------------------------------
void /*thiscall*/ CNCutableGrass__vmt2C8(void *this, int nArg2, int nArg3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = nArg2;
  v3[1] = nArg3;
  sub_474950((int)this + 1020, (int)v3);
}



// ------------------------------------------------------------
// 0x60A310 sub_60A310
// ------------------------------------------------------------
// 草丛/物件资源装载（72 行）：sub_41ACF0（资源管理器）+ sub_42FD40 + sub_493A60 + sub_4C3640（动画对象构造，
// 与 0x600C20 生成工厂同款的 0x12C 构造）——【推断：草丛动画实例化】。
int /*thiscall*/ sub_60A310(uint32_t *this)
{
  void *fld_e178; // ecx
  int fld_e1782; // ecx
  int fld_e91; // edi
  int v5; // eax
  int pThis_5B; // eax
  int v7; // eax
  int fld_e36; // ecx
  int nRand; // eax
  int fld_e87; // ecx
  uint32_t *fld_e362; // ecx
  int result; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // eax

  fld_e178 = (void *)*(this + 178);
  if ( fld_e178 != nullptr && (*(this + 179) - (int)fld_e178) >> 2 != 0 && sub_42FD40(fld_e178, szPassword) )
  {
    if ( operator new(0x12Cu) != nullptr )
    {
      fld_e1782 = *(this + 178);
      if ( *(this + 96) < 0x10u )
      {
        v7 = sub_41ACF0(fld_e1782);
        pThis_5B = sub_4C3640(this + 91, v7, this);
      }
      else
      {
        fld_e91 = *(this + 91);
        v5 = sub_41ACF0(fld_e1782);
        pThis_5B = sub_4C3640(fld_e91, v5, this);
      }
    }
    else
    {
      pThis_5B = 0;
    }
    *(this + 246) = pThis_5B;
  }
  fld_e36 = *(this + 36);
  if ( fld_e36 != 0
    && (unsigned int)((*(this + 37) - fld_e36) >> 2) > 2
    && *(uint32_t *)(fld_e36 + 4) != 0
    && *(uint32_t *)(*(this + 36) + 8) != 0 )
  {
    *((uint8_t *)this + 988) = 1;
  }
  nRand = rand();
  sub_493A60(*(this + 34), nRand % 1000);
  if ( *(this + 172) == 0 )
    *((uint8_t *)this + 972) = 1;
  fld_e87 = *(this + 87);
  if ( fld_e87 != 0 && (unsigned int)((*(this + 88) - fld_e87) >> 2) > 1 && *(uint32_t *)(fld_e87 + 4) == 1 )
    *((uint8_t *)this + 1000) = 1;
  fld_e362 = (uint32_t *)*(this + 36);
  if ( fld_e362 != nullptr && (*(this + 37) - (int)fld_e362) >> 2 != 0 && *fld_e362 != 0 )
    *(this + 245) = 2;
  else
    *(this + 245) = 1;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this);
  if ( result > 0 )
  {
    v13 = *this;
    v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this);
    v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v14);
    v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v15);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v13 + 112))(this, v16);
  }
  return result;
}



// ------------------------------------------------------------
// 0x60A4C0 sub_60A4C0
// ------------------------------------------------------------
// 草丛被割表现（87 行）：sub_45FE80（演播层）+ sub_4E2130 —— 割断瞬间的叶片飞散演出【推断】。
void /*thiscall*/ sub_60A4C0(int *this)
{
  int fld_e252; // ecx
  int *fld_e2522; // edi
  bool fld_e253; // zf
  int *v5; // edi
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int *fld_e252222; // edi
  int fld_e2523; // eax
  unsigned int fld_e2532; // ecx
  int fld_e256; // ecx
  unsigned int j; // edi
  int fld_e2562; // ecx
  int v16; // [esp-Ch] [ebp-34h]
  void *Block; // [esp+Ch] [ebp-1Ch]
  unsigned int v18; // [esp+10h] [ebp-18h] BYREF
  int *fld_e25222; // [esp+14h] [ebp-14h]
  unsigned int i; // [esp+18h] [ebp-10h]
  int v21; // [esp+24h] [ebp-4h]

  fld_e252 = *(this + 252);
  if ( fld_e252 != 0 && (*(this + 253) - fld_e252) >> 3 != 0 )
  {
    v18 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
    fld_e2522 = (int *)*(this + 252);
    fld_e253 = fld_e2522 == (int *)*(this + 253);
    fld_e25222 = fld_e2522;
    for ( i = v18 % 0x168; !fld_e253; i += 0x168 / fld_e2532 )
    {
      Block = operator new(0x424u);
      v21 = 0;
      if ( Block != nullptr )
        v5 = (int *)sub_4E2130(fld_e2522[1], &v18, i);
      else
        v5 = nullptr;
      v6 = *this;
      v7 = *v5;
      v21 = -1;
      v8 = (*(int (/*thiscall*/ **)(int *, int))(v6 + 124))(this, 60);
      v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
      (*(void (/*thiscall*/ **)(int *, int))(v7 + 112))(v5, v9);
      v16 = (int)v5;
      fld_e252222 = fld_e25222;
      sub_45FE80(*(this + 29), (int)fld_e25222, 289, *fld_e25222, v16, 0, 0);
      fld_e2523 = *(this + 252);
      if ( fld_e2523 != 0 )
        fld_e2532 = (*(this + 253) - fld_e2523) >> 3;
      else
        fld_e2532 = 0;
      fld_e2522 = fld_e252222 + 2;
      fld_e25222 = fld_e2522;
      fld_e253 = fld_e2522 == (int *)*(this + 253);
    }
    if ( *(this + 252) != 0 )
      j__free((void *)*(this + 252));
    *(this + 252) = 0;
    *(this + 253) = 0;
    *(this + 254) = 0;
  }
  fld_e256 = *(this + 256);
  if ( fld_e256 != 0
    && (*(this + 257) - fld_e256) >> 3 != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    for ( j = 0; ; ++j )
    {
      fld_e2562 = *(this + 256);
      if ( fld_e2562 == 0 || j >= (*(this + 257) - fld_e2562) >> 3 )
        break;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        *(uint32_t *)(fld_e2562 + 8 * j),
        *(uint32_t *)(fld_e2562 + 8 * j + 4),
        0,
        0,
        0,
        0,
        0,
        4,
        0,
        0,
        0);
    }
  }
}



// ------------------------------------------------------------
// 0x60A670 CNCutableGrass__vmt12C
// ------------------------------------------------------------
// CNCutableGrass 消亡联动槽（vmt12C）：sub_609CA0 + sub_60A4C0（被割表现）+ sub_4600B0 —— 草丛消失演出链。
void /*thiscall*/ CNCutableGrass__vmt12C(int *this, int nArg2)
{
  int nArg22; // ebx
  int *fld_e246; // edx
  int *fld_e87; // ecx
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  void *fld_e29; // ecx
  uint8_t v11[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v13; // [esp+14h] [ebp-14h]
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]

  nArg22 = nArg2;
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (int *)nArg2 == this )
  {
    if ( *(this + 244) < *(this + 245) )
    {
      fld_e246 = (int *)*(this + 246);
      if ( fld_e246 != nullptr )
      {
        fld_e87 = (int *)*(this + 87);
        if ( fld_e87 != nullptr && (*(this + 88) - (int)fld_e87) >> 2 != 0 )
          v6 = *fld_e87;
        else
          v6 = 0;
        v7 = *fld_e246;
        v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v6);
        v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v7 + 40))(*(this + 246), v9);
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 246) + 12))(*(this + 246), 0);
        (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 246) + 92))(*(this + 246), v11);
        fld_e29 = (void *)*(this + 29);
        v15 = 0;
        sub_4600B0(fld_e29, 2, 0, (int)v11);
        v15 = -1;
        if ( Block != nullptr )
          j__free(Block);
        nArg22 = nArg2;
        Block = nullptr;
        v13 = 0;
        v14 = 0;
      }
      sub_609CA0(this);
      *(this + 244) = *(this + 245);
    }
    sub_60A4C0(this);
  }
  if ( *(this + 248) == nArg22 )
    *(this + 248) = 0;
}



// ------------------------------------------------------------
// 0x60A790 CNMapObject__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNMapObject__vmtC(int *this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax

  CNRDPassiveObject__vmtC(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);
  if ( result > 0 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v4);
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);
    return (*(int (/*thiscall*/ **)(int *, int))(v3 + 112))(this, v6);
  }
  return result;
}



// ------------------------------------------------------------
// 0x60A7D0 sub_60A7D0
// ------------------------------------------------------------
bool /*thiscall*/ sub_60A7D0(void *this, void *pArg2)
{
  return pArg2 != this && (*(uint8_t (/*thiscall*/ **)(void *, void *))(*(uint32_t *)this + 488))(this, pArg2) != 0;
}



// ------------------------------------------------------------
// 0x60A800 sub_60A800
// ------------------------------------------------------------
// 地图物件状态广播：sub_432FA0（UDP 广播）+ byte_73B39C（状态字）——
// CNMapObject（可破坏地图物件）的破坏状态同步包【推断】。
void /*thiscall*/ sub_60A800(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // eax
  bool v6; // zf
  signed int nRand; // eax
  int nRand2; // edx
  int v9; // eax
  int v10; // eax
  int v11; // [esp-2Ch] [ebp-40h]
  int v12; // [esp-28h] [ebp-3Ch]
  int v13; // [esp-24h] [ebp-38h]
  int v14; // [esp-20h] [ebp-34h]
  uint8_t *v15; // [esp-1Ch] [ebp-30h]
  int v16; // [esp-18h] [ebp-2Ch]
  int nArg42; // [esp-14h] [ebp-28h]
  uint16_t v18[2]; // [esp+Ch] [ebp-8h] BYREF
  char ArgList[4]; // [esp+10h] [ebp-4h]

  if ( *(this + 78) < 0x10u )
    *(uint32_t *)ArgList = this + 73;
  else
    *(uint32_t *)ArgList = *(this + 73);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 52))(this, nArg2, nArg3, nArg4);
  off_77F3FC((char *)&byte_73B39C, *(uint32_t *)ArgList, v5);
  sub_432FA0();
  nRand = rand() & 0x80000001;
  v6 = nRand == 0;
  if ( nRand < 0 )
    v6 = (((uint8_t)nRand - 1) | 0xFFFFFFFE) == -1;
  if ( v6 )
  {
    nArg42 = nArg4;
    v16 = 0;
    v15 = nullptr;
    v14 = 0;
    v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v12 = 0;
  }
  else
  {
    v18[0] = rand() % 100 + 50;
    v18[1] = rand() % 50 + 25;
    ArgList[2] = rand() % 2 == 0;
    ArgList[3] = 3 - (rand() % 2 != 0);
    nRand2 = rand() % 60;
    v9 = *this;
    nArg42 = nArg4;
    v16 = 8;
    *(uint16_t *)ArgList = nRand2 + 40;
    v15 = v18;
    v14 = 1;
    v13 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 152))(this);
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) + 10;
  }
  v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  IRDCollisionObject__vmt250(this, nArg3, (int)this, nArg2, 100, nArg3, v10, v11, v12, v13, v14, v15, v16, nArg42, 1, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x60A950 sub_60A950
// ------------------------------------------------------------
// 地图物件状态机片段（30 行，无外部调用）——【推断：破坏阶段推进】。
int /*thiscall*/ sub_60A950(uint32_t *this)
{
  uint32_t *pThis_FF; // esi
  int i; // edi
  int result; // eax
  int fld_e262; // esi
  int pObj; // ecx

  pThis_FF = this + 255;
  for ( i = 3; i != 0; --i )
  {
    if ( *pThis_FF != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_FF)(*pThis_FF, 1);
    *pThis_FF++ = 0;
  }
  fld_e262 = *(this + 262);
  if ( fld_e262 != *(this + 263) )
  {
    do
    {
      pObj = *(uint32_t *)(fld_e262 + 4);
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
      *(uint32_t *)(fld_e262 + 4) = 0;
      result = *(this + 263);
      fld_e262 += 8;
    }
    while ( fld_e262 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x60A9B0 sub_60A9B0
// ------------------------------------------------------------
char /*thiscall*/ sub_60A9B0(uint32_t *this, int nArg2)
{
  int fld_e251; // esi
  unsigned int i; // edx

  fld_e251 = *(this + 251);
  for ( i = 0; fld_e251 != 0 && i < (*(this + 252) - fld_e251) >> 2; ++i )
  {
    if ( *(uint32_t *)(*(this + 251) + 4 * i) == nArg2 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x60AA00 sub_60AA00
// ------------------------------------------------------------
// 地图物件辅助：sub_41BFE0 ——【推断：物件资源/属性查询】。
void /*thiscall*/ sub_60AA00(int this)
{
  void **pThis_408; // edi
  int i; // [esp+Ch] [ebp-4h]

  *(uint32_t *)(this + 96) = 1057;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1028) = 0;
  pThis_408 = (void **)(this + 1032);
  for ( i = 3; i != 0; --i )
    sub_41BFE0(pThis_408++, nullptr);
  if ( *(uint32_t *)(this + 1004) != 0 )
    j__free(*(void **)(this + 1004));
  *(uint32_t *)(this + 1004) = 0;
  *(uint32_t *)(this + 1008) = 0;
  *(uint32_t *)(this + 1012) = 0;
  *(uint8_t *)(this + 996) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 1092) = 0;
  *(uint8_t *)(this + 1096) = 0;
  *(uint32_t *)(this + 1016) = 4;
}



// ------------------------------------------------------------
// 0x60AAB0 sub_60AAB0
// ------------------------------------------------------------
char /*thiscall*/ sub_60AAB0(uint32_t *this, int nArg2)
{
  int fld_e251; // edx
  unsigned int i; // ecx

  fld_e251 = *(this + 251);
  for ( i = 0; fld_e251 != 0 && i < (*(this + 252) - fld_e251) >> 2; ++i )
  {
    if ( *(uint32_t *)(*(this + 251) + 4 * i) == nArg2 )
    {
      memcpy_0(
        (void *)(*(this + 251) + 4 * i),
        (const void *)(*(this + 251) + 4 * i + 4),
        4 * ((int)(*(this + 252) - (*(this + 251) + 4 * i + 4)) >> 2));
      *(this + 252) -= 4;
      return 1;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x60AB30 CNMapObject__vmt12C
// ------------------------------------------------------------
char /*thiscall*/ CNMapObject__vmt12C(uint32_t *this, int nArg2)
{
  char result; // al

  CNRDPassiveObject__vmt12C(this, nArg2);
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 1);
  if ( result != 0 )
    return sub_60AAB0(this, nArg2);
  return result;
}



// ------------------------------------------------------------
// 0x60AB60 sub_60AB60
// ------------------------------------------------------------
// 地图物件辅助（31 行，无外部调用）——【推断：破坏掉落参数】。
void /*thiscall*/ sub_60AB60(uint32_t *this)
{
  int fld_e266; // ecx
  unsigned int i; // edi
  int fld_e2662; // ecx

  fld_e266 = *(this + 266);
  if ( fld_e266 != 0
    && (*(this + 267) - fld_e266) >> 3 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    for ( i = 0; ; ++i )
    {
      fld_e2662 = *(this + 266);
      if ( fld_e2662 == 0 || i >= (*(this + 267) - fld_e2662) >> 3 )
        break;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        *(uint32_t *)(fld_e2662 + 8 * i),
        *(uint32_t *)(fld_e2662 + 8 * i + 4),
        0,
        0,
        0,
        0,
        0,
        4,
        0,
        0,
        0);
    }
  }
}



// ------------------------------------------------------------
// 0x60ABE0 sub_60ABE0
// ------------------------------------------------------------
// 状态广播包装（35 行）→ 转调 sub_60A800 —— 物件破坏广播的对外入口。
unsigned int /*thiscall*/ sub_60ABE0(unsigned int *this)
{
  unsigned int result; // eax
  unsigned int v3; // edi
  int i; // ebx

  result = *(this + 270);
  if ( result != 0 )
  {
    result = (int)(*(this + 271) - result) / 12;
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 308))(this);
      if ( (uint8_t)result != 0 )
      {
        v3 = 0;
        for ( i = 0; ; i += 12 )
        {
          result = *(this + 270);
          if ( result == 0 )
            break;
          result = (int)(*(this + 271) - result) / 12;
          if ( v3 >= result )
            break;
          sub_60A800(
            this,
            *(uint32_t *)(i + *(this + 270)),
            *(uint32_t *)(*(this + 270) + i + 4),
            *(uint32_t *)(*(this + 270) + i + 8));
          ++v3;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60AC80 CNMapObject__vmt2DC
// ------------------------------------------------------------
// CNMapObject 表现槽（vmt2DC）：sub_41ACF0（资源管理器）+ sub_4600B0（演播层）——
// 物件破坏时的碎块/烟尘演出【推断】。
int /*thiscall*/ CNMapObject__vmt2DC(int **this)
{
  int *v2; // edx
  int *fld_e36; // ecx
  int v4; // ecx
  int *fld_e256; // eax
  int v6; // edi
  int v7; // eax
  int fld_e245; // eax
  int fld_e244; // eax
  void *fld_e29; // ecx
  int result; // eax
  int pThis_103; // eax
  uint8_t v13[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v15; // [esp+Ch] [ebp-18h]
  int v16; // [esp+10h] [ebp-14h]
  int *v17; // [esp+14h] [ebp-10h]
  int v18; // [esp+20h] [ebp-4h]

  v2 = *this;
  if ( *(this + 246) != *(this + 247) )
    return ((int (/*thiscall*/ *)(int **))v2[187])(this);
  ((void (/*thiscall*/ *)(int **))v2[186])(this);
  fld_e36 = *(this + 36);
  if ( fld_e36 != nullptr && *(this + 37) - fld_e36 != 0 )
  {
    v4 = *fld_e36;
    if ( v4 != 0 )
      ((void (/*thiscall*/ *)(int **, int))(*this)[49])(this, v4);
  }
  fld_e256 = *(this + 256);
  if ( fld_e256 != nullptr )
  {
    v6 = *fld_e256;
    v7 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
    fld_e245 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, (int)*(this + 245) + v7);
    fld_e244 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, (int)*(this + 244) + fld_e245);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v6 + 40))(*(this + 256), (int)*(this + 243) + fld_e244);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 256) + 12))(*(this + 256), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 256) + 92))(*(this + 256), v13);
    fld_e29 = *(this + 29);
    v18 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v13);
    v18 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v15 = 0;
    v16 = 0;
  }
  result = sub_41ACF0(this + 259);
  if ( result != 0 )
  {
    v17 = *this;
    pThis_103 = sub_41ACF0(this + 259);
    return ((int (/*thiscall*/ *)(int **, int, int, uint32_t, uint32_t))v17[53])(this, pThis_103, -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x60ADE0 CNMapObject__vmt2B4
// ------------------------------------------------------------
// CNMapObject 槽（vmt2B4）：sub_4926A0（定时器复位）——物件受击计时复位。
int /*thiscall*/ CNMapObject__vmt2B4(int *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int result; // eax
  int fld_e36; // ecx

  result = *(this + 170);
  if ( result > 0 )
  {
    fld_e36 = *(this + 36);
    if ( fld_e36 != 0 )
    {
      result = (*(this + 37) - fld_e36) >> 2;
      if ( (unsigned int)result > 1 )
      {
        result = *(this + 36);
        if ( *(uint32_t *)(fld_e36 + 4) != 0 )
        {
          *(this + 273) = 1;
          sub_4926A0(*(uint32_t *)(result + 4));
          result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
        }
      }
    }
  }
  else
  {
    ++*(this + 246);
    result = (*(int (/*thiscall*/ **)(int *))(*this + 732))(this);
    *(this + 170) = *(this + 171);
  }
  if ( *(this + 246) >= *(this + 248) && *((uint8_t *)this + 996) == 1 )
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 736))(this, nArg2);
  return result;
}



// ------------------------------------------------------------
// 0x60AE90 CNMapObject__vmt2E0
// ------------------------------------------------------------
// CNMapObject 表现槽（vmt2E0）：sub_41ACF0 + sub_4600B0 —— 物件另一表现分支（与 0x60AC80 成对）。
int /*thiscall*/ CNMapObject__vmt2E0(int **this, int nArg2)
{
  int *fld_e257; // eax
  int v4; // edi
  int v5; // eax
  int fld_e245; // eax
  int fld_e244; // eax
  void *fld_e29; // ecx
  int pThis_104; // eax
  int result; // eax
  uint8_t v11[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v13; // [esp+14h] [ebp-18h]
  int v14; // [esp+18h] [ebp-14h]
  int *v15; // [esp+1Ch] [ebp-10h]
  int v16; // [esp+28h] [ebp-4h]

  fld_e257 = *(this + 257);
  if ( fld_e257 != nullptr )
  {
    v4 = *fld_e257;
    v5 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
    fld_e245 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, (int)*(this + 245) + v5);
    fld_e244 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, (int)*(this + 244) + fld_e245);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v4 + 40))(*(this + 257), (int)*(this + 243) + fld_e244);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 257) + 12))(*(this + 257), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 257) + 92))(*(this + 257), v11);
    fld_e29 = *(this + 29);
    v16 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v11);
    v16 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v13 = 0;
    v14 = 0;
  }
  if ( sub_41ACF0(this + 260) != 0 )
  {
    v15 = *this;
    pThis_104 = sub_41ACF0(this + 260);
    ((void (/*thiscall*/ *)(int **, int, int, uint32_t, uint32_t))v15[53])(this, pThis_104, -1, 0, 0);
  }
  result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
  if ( (uint8_t)result != 0 )
    return ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x60AFA0 sub_60AFA0
// ------------------------------------------------------------
// 地图物件定义表装载（111 行）：sub_4DA030/sub_5043B0/sub_504450（表驱动族）+ sub_52E630 + sub_59EE30 +
// sub_5E51C0/sub_623C10 —— 与怪物解析器（monster_parser）同族的表装载管线。【推断：物件 hp/掉落/破坏形态配置】
int /*thiscall*/ sub_60AFA0(int *this, char *pszArg2, unsigned int uArg3, int *Block)
{
  int v5; // ecx
  int v6; // edx
  int fld_e1; // ebx
  int result; // eax
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v13; // ecx
  int fld_e27; // eax
  int v15; // ebx
  int fld_e13; // eax
  unsigned int v17; // edi
  uint32_t *fld_e23; // ecx
  int fld_e26; // edi
  uint32_t *fld_e12; // [esp-18h] [ebp-40h]
  int fld_e25; // [esp-Ch] [ebp-34h]
  unsigned int fld_e24; // [esp-8h] [ebp-30h]
  int v24; // [esp+0h] [ebp-28h] BYREF
  uint32_t v25[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v26; // [esp+24h] [ebp-4h]
  uint32_t *v27; // [esp+30h] [ebp+8h]
  uint32_t *v28; // [esp+34h] [ebp+Ch]
  uint32_t *Blocka; // [esp+38h] [ebp+10h]
  void *Blockb; // [esp+38h] [ebp+10h]

  v5 = *Block;
  v6 = Block[1];
  fld_e1 = *(this + 1);
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 12;
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_52E630(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (uint32_t *)*(this + 2);
      Blockb = fld_e23;
      if ( ((char *)fld_e23 - pszArg2) / 12 >= uArg3 )
      {
        v27 = &fld_e23[-3 * uArg3];
        *(this + 2) = (int)sub_59EE30(v27, fld_e23, fld_e23);
        sub_504450(pszArg2, v27, Blockb);
        return sub_5043B0(pszArg2, &pszArg2[12 * uArg3], v25);
      }
      else
      {
        sub_59EE30(pszArg2, fld_e23, &pszArg2[12 * uArg3]);
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 12;
        fld_e25 = *(this + 2);
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);
        fld_e26 = 12 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        return sub_5043B0(pszArg2, fld_e26 - 12 * uArg3, v25);
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 12;
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);
      v15 = 3 * v13;
      Blocka = operator new(12 * v13);
      fld_e12 = (uint32_t *)*(this + 1);
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pszArg2, Blocka);
      sub_623C10(v28, uArg3, v25);
      sub_59EE30(pszArg2, (uint32_t *)*(this + 2), &v28[3 * uArg3]);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 12;
      v17 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v15];
      *(this + 2) = (int)&Blocka[3 * v17];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x60B250 sub_60B250
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_60B250(int *this, uint32_t *uArg2, int nArg3, int *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 12 != 0 )
    v6 = (nArg3 - fld_e1) / 12;
  else
    v6 = 0;
  sub_60AFA0(this, nArg3, 1u, Block);
  *uArg2 = *(this + 1) + 12 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x60B2C0 sub_60B2C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_60B2C0(int *this, int *Block)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 12;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 12 )
    return sub_60B250(this, &Block, *(this + 2), Block);
  fld_e22 = *(this + 2);
  result = (uint32_t *)sub_623C10(fld_e22, 1, Block);
  *(this + 2) = fld_e22 + 12;
  return result;
}



// ------------------------------------------------------------
// 0x60B340 CNMapObject__vmt2D0
// ------------------------------------------------------------
void /*thiscall*/ CNMapObject__vmt2D0(void *this, int nArg2, int nArg3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = nArg2;
  v3[1] = nArg3;
  sub_60A240((int)this + 1044, (int)v3);
}



// ------------------------------------------------------------
// 0x60B370 CNMapObject__vmt2D4
// ------------------------------------------------------------
void /*thiscall*/ CNMapObject__vmt2D4(void *this, int nArg2, int nArg3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = nArg2;
  v3[1] = nArg3;
  sub_474950((int)this + 1060, (int)v3);
}



// ------------------------------------------------------------
// 0x60B3A0 CNMapObject__vmt2D8
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNMapObject__vmt2D8(int *this, int nArg2, int nArg3, int nArg4)
{
  int Block[3]; // [esp+0h] [ebp-Ch] BYREF

  Block[1] = nArg3;
  Block[0] = nArg2;
  Block[2] = nArg4;
  return sub_60B2C0(this + 269, Block);
}



// ------------------------------------------------------------
// 0x60B3D0 CNMapObject__vmt2E4
// ------------------------------------------------------------
// CNMapObject 装载槽（vmt2E4）：sub_41ACF0/sub_41B0D0（资源管理器双查）+ sub_4C3640（动画对象构造）——
// 物件动画实例化。
uint32_t */*thiscall*/ CNMapObject__vmt2E4(int this)
{
  int v2; // ebx
  int fld_2C8; // eax
  int pThis_16C; // edi
  int fld_2C82; // eax
  int v6; // eax
  int v7; // edi
  int pThis_408; // ebx
  int fld_2C83; // edx
  int v10; // eax
  uint32_t *result; // eax
  uint32_t *pThis_3FC; // [esp+10h] [ebp-10h]

  v2 = 0;
  pThis_3FC = (uint32_t *)(this + 1020);
  do
  {
    fld_2C8 = *(uint32_t *)(v2 + *(uint32_t *)(this + 712));
    if ( fld_2C8 != 0 && *(uint32_t *)(fld_2C8 + 4) != 0 )
    {
      if ( operator new(0x12Cu) != nullptr )
      {
        if ( *(uint32_t *)(this + 384) < 0x10u )
          pThis_16C = this + 364;
        else
          pThis_16C = *(uint32_t *)(this + 364);
        fld_2C82 = sub_41ACF0(v2 + *(uint32_t *)(this + 712));
        v6 = sub_4C3640(pThis_16C, fld_2C82, this);
      }
      else
      {
        v6 = 0;
      }
      *pThis_3FC = v6;
    }
    v2 += 4;
    ++pThis_3FC;
  }
  while ( v2 < 12 );
  v7 = 12;
  pThis_408 = this + 1032;
  do
  {
    fld_2C83 = *(uint32_t *)(this + 712);
    v10 = *(uint32_t *)(v7 + fld_2C83);
    if ( v10 != 0 && *(uint32_t *)(v10 + 4) != 0 )
      sub_41B0D0(v7 + fld_2C83);
    v7 += 4;
    pThis_408 += 4;
  }
  while ( v7 < 24 );
  result = *(uint32_t **)(this + 348);
  *(uint32_t *)(this + 988) = *result;
  *(uint32_t *)(this + 992) = result[1];
  *(uint8_t *)(this + 996) = result[2] != 0;
  *(uint32_t *)(this + 972) = result[3];
  *(uint32_t *)(this + 976) = result[4];
  *(uint32_t *)(this + 980) = result[5];
  *(uint32_t *)(this + 680) = result[6];
  *(uint32_t *)(this + 684) = result[6];
  return result;
}



// ------------------------------------------------------------
// 0x60B520 sub_60B520
// ------------------------------------------------------------
// 物件破坏分发（93 行）：sub_428220 + sub_60A9B0/60AAB0 ——
// 【推断：按破坏形态分发碎块/掉落/广播】。
int /*thiscall*/ sub_60B520(int *this)
{
  int fld_e251; // ecx
  unsigned int v3; // edi
  int fld_e2512; // ecx
  int fld_e29; // eax
  int v6; // ecx
  int v7; // eax
  int result; // eax
  unsigned int v9; // edi
  int fld_e292; // ecx
  int v11; // edx
  int v12; // edi
  int fld_e2513; // edx
  unsigned int fld_e252; // ecx
  int *fld_e2522; // eax
  int v16; // [esp+Ch] [ebp-Ch] BYREF
  int v17; // [esp+10h] [ebp-8h]
  signed int v18; // [esp+14h] [ebp-4h]

  fld_e251 = *(this + 251);
  if ( fld_e251 != 0 && (*(this + 252) - fld_e251) >> 2 != 0 )
  {
    v3 = 0;
    while ( 1 )
    {
      fld_e2512 = *(this + 251);
      if ( fld_e2512 == 0 || v3 >= (*(this + 252) - fld_e2512) >> 2 )
        break;
      if ( *(int **)(*(this + 251) + 4 * v3) != this
        && (*(uint8_t (/*thiscall*/ **)(int *, uint32_t))(*this + 488))(this, *(uint32_t *)(*(this + 251) + 4 * v3)) != 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 712))(this, *(uint32_t *)(*(this + 251) + 4 * v3++));
      }
      else
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 716))(this, *(uint32_t *)(*(this + 251) + 4 * v3));
        sub_60AAB0(this, *(uint32_t *)(*(this + 251) + 4 * v3++));
      }
    }
  }
  fld_e29 = *(this + 29);
  v6 = *(uint32_t *)(fld_e29 + 120);
  v7 = fld_e29 + 116;
  if ( v6 != 0 )
    v17 = (*(uint32_t *)(v7 + 8) - v6) >> 2;
  else
    v17 = 0;
  result = v17;
  v9 = 0;
  v18 = 0;
  if ( v17 > 0 )
  {
    while ( 1 )
    {
      fld_e292 = *(this + 29);
      v11 = *(uint32_t *)(fld_e292 + 120);
      if ( v11 != 0 && v9 < (*(uint32_t *)(fld_e292 + 124) - v11) >> 2 )
        v12 = *(uint32_t *)(v11 + 4 * v9);
      else
        v12 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 752))(this, v12) != 0
        && (int *)v12 != this
        && (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 488))(this, v12) != 0 )
      {
        v16 = v12;
        if ( sub_60A9B0(this, v12) == 0 )
        {
          fld_e2513 = *(this + 251);
          if ( fld_e2513 != 0 )
            fld_e252 = (*(this + 252) - fld_e2513) >> 2;
          else
            fld_e252 = 0;
          if ( fld_e2513 != 0 && fld_e252 < (*(this + 253) - fld_e2513) >> 2 )
          {
            fld_e2522 = (int *)*(this + 252);
            *fld_e2522 = v12;
            *(this + 252) = (int)(fld_e2522 + 1);
          }
          else
          {
            sub_428220((int)(this + 250), *(this + 252), 1u, &v16);
          }
          (*(void (/*thiscall*/ **)(int *, int))(*this + 708))(this, v12);
        }
      }
      result = ++v18;
      if ( v18 >= v17 )
        break;
      v9 = v18;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60B6B0 CNMapObject__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNMapObject__vmt14C(int *this)
{
  int fld_e34; // ecx
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 273) != 0 && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) == 1 )
  {
    fld_e34 = *(this + 34);
    *(this + 273) = 0;
    sub_4926A0(fld_e34);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 34));
  }
  result = *((uint8_t *)this + 1096);
  if ( result != 0 )
    return sub_60B520(this);
  return result;
}



// ------------------------------------------------------------
// 0x60B710 sub_60B710
// ------------------------------------------------------------
// 物件破坏表现（70 行）：sub_45FE80（演播层）+ sub_4E2130 + sub_4E7E40 ——
// 破坏瞬间的演出与位移同步【推断】。
void /*thiscall*/ sub_60B710(int *this)
{
  int fld_e262; // ecx
  int fld_e263; // ebx
  int fld_e29; // edi
  int *fld_e2622; // ebx
  bool fld_e2632; // zf
  int *v7; // edi
  int v8; // eax
  int v9; // ebx
  uint64_t v10; // rax
  int v11; // eax
  int v12; // eax
  int *fld_e262222; // ebx
  int fld_e2623; // eax
  unsigned int fld_e2633; // ecx
  int *fld_e2634; // eax
  void *Block; // [esp+4h] [ebp-1Ch]
  unsigned int v18; // [esp+8h] [ebp-18h] BYREF
  int *fld_e26222; // [esp+Ch] [ebp-14h]
  unsigned int v20; // [esp+10h] [ebp-10h]
  int v21; // [esp+1Ch] [ebp-4h]

  fld_e262 = *(this + 262);
  if ( fld_e262 != 0 && (*(this + 263) - fld_e262) >> 3 != 0 )
  {
    fld_e263 = (*(this + 263) - fld_e262) >> 3;
    fld_e29 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 108) + 492);
    v18 = fld_e29 + fld_e263 + (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
    fld_e2622 = (int *)*(this + 262);
    fld_e2632 = fld_e2622 == (int *)*(this + 263);
    fld_e26222 = fld_e2622;
    v20 = v18 % 0x168;
    if ( !fld_e2632 )
    {
      do
      {
        Block = operator new(0x424u);
        v7 = nullptr;
        v21 = 0;
        if ( Block != nullptr )
          v7 = (int *)sub_4E2130(fld_e2622[1], &v18, v20);
        v8 = *this;
        v9 = *v7;
        v21 = -1;
        v10 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(v8 + 192))(this) * 0.69999999);
        v11 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, v10);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11);
        (*(void (/*thiscall*/ **)(int *, int))(v9 + 112))(v7, v12);
        fld_e262222 = fld_e26222;
        sub_45FE80(*(this + 29), (int)v7, 289, *fld_e26222, (int)v7, 0, 0);
        fld_e2623 = *(this + 262);
        if ( fld_e2623 != 0 )
          fld_e2633 = (*(this + 263) - fld_e2623) >> 3;
        else
          fld_e2633 = 0;
        v20 += 0x168 / fld_e2633;
        sub_4E7E40(v7);
        fld_e2634 = (int *)*(this + 263);
        fld_e2622 = fld_e262222 + 2;
        fld_e26222 = fld_e2622;
      }
      while ( fld_e2622 != fld_e2634 );
    }
    if ( *(this + 262) != 0 )
      j__free((void *)*(this + 262));
    *(this + 262) = 0;
    *(this + 263) = 0;
    *(this + 264) = 0;
  }
}



// ------------------------------------------------------------
// 0x60B8B0 CNMapObject__vmt2E8
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNMapObject__vmt2E8(int *this)
{
  sub_60B710(this);
  sub_60AB60(this);
  return sub_60ABE0((unsigned int *)this);
}



// ------------------------------------------------------------
// 0x60B8D0 sub_60B8D0
// ------------------------------------------------------------
int /*thiscall*/ sub_60B8D0(uint32_t *this)
{
  *(this + 243) = 0;
  *(this + 244) = 0;
  *(this + 245) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60B8F0 sub_60B8F0
// ------------------------------------------------------------
int /*thiscall*/ sub_60B8F0(uint32_t *this)
{
  uint32_t *pThis_F3; // esi
  int i; // edi
  int result; // eax

  pThis_F3 = this + 243;
  for ( i = 2; i != 0; --i )
  {
    if ( *pThis_F3 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_F3)(*pThis_F3, 1);
    *pThis_F3++ = 0;
  }
  return result;
}



// ============================================================
// 【分区 8】元素与自然现象 PO（0x60B920-0x610320）
// 火弹/火爆/冰弹/落雷/粒子工厂/爆风/地震/毒瓦斯/冰针群/地火/流星/回旋镖/弹跳体/
// 死亡衍生基类/陷阱石/火轮/黏土泡泡/预警圈/念气罩/附属圈 —— 地图机关与元素演出层
// 粒子证据：FireMissile/IceMissile/ShootingStar/NapalmBomb 各 .ptl 族（P36）
// ============================================================
// ------------------------------------------------------------
// 0x60B920 CNFireMissile__vmt14C
// ------------------------------------------------------------
// CNFireMissile 主循环槽（vmt14C，109 行）：sub_4600B0（演播层）+ sub_600890（基类出生播音）——
// 火焰导弹（FireMissile）的飞行编排；出生粒子与音效见 0x60BA80（FireMissileParticle.ptl + SIZZLE_CREATE）。
char /*thiscall*/ sub_60B920(uint32_t *this)  // 【CNFireMissile__vmt14C】
{
  int **pThis_F3; // edi
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *fld_e29; // ecx
  bool v8; // zf
  char result; // al
  int fld_e71; // eax
  int v11; // edx
  int fld_e245; // [esp-28h] [ebp-4Ch]
  uint8_t v13[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v15; // [esp+Ch] [ebp-18h]
  int v16; // [esp+10h] [ebp-14h]
  int v17; // [esp+14h] [ebp-10h]
  int v18; // [esp+20h] [ebp-4h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) <= 0 )
  {
    result = *((uint8_t *)this + 264);
    if ( result == 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      {
        fld_e71 = *(this + 71);
        if ( fld_e71 == 30047 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
            this,
            30048,
            *(this + 245),
            0,
            0,
            0,
            0,
            0,
            4,
            0,
            0,
            0);
        }
        else
        {
          v11 = *this;
          fld_e245 = *(this + 245);
          if ( fld_e71 == 30049 )
            (*(void (/*stdcall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(v11 + 580))(
              30050,
              fld_e245,
              0,
              0,
              0,
              0,
              0,
              4,
              0,
              0,
              0);
          else
            (*(void (/*stdcall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(v11 + 580))(
              40003,
              fld_e245,
              0,
              0,
              0,
              0,
              0,
              4,
              0,
              0,
              0);
        }
      }
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
  }
  else
  {
    pThis_F3 = (int **)(this + 243);
    v17 = 2;
    do
    {
      v3 = **pThis_F3;
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v4);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);
      (*(void (/*thiscall*/ **)(int *, int))(v3 + 40))(*pThis_F3, v6);
      (*(void (/*thiscall*/ **)(int *, uint8_t *))(**pThis_F3 + 92))(*pThis_F3, v13);
      fld_e29 = (void *)*(this + 29);
      v18 = 0;
      sub_4600B0(fld_e29, 2, 0, (int)v13);
      v18 = -1;
      if ( Block != nullptr )
        j__free(Block);
      ++pThis_F3;
      result = v17 - 1;
      v8 = v17 == 1;
      Block = nullptr;
      v15 = 0;
      v16 = 0;
      --v17;
    }
    while ( !v8 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x60BA80 sub_60BA80
// ------------------------------------------------------------
// 火弹出生粒子：字符串证据「PassiveObject/Common/Particle/FireMissileParticle.ptl |
// FireMissileParticleLight.ptl」（双发射器：本体+光晕）+「SIZZLE_CREATE」（音效 TAG）+ sub_4049C0（P36 出场 lerp 插值）。
// 对应研究：P36 发射器资源生态直证。
int /*thiscall*/ sub_60BA80(float *this, int nArg2)
{
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  uint32_t *pMem2; // eax
  uint32_t *v6; // eax
  int pThis_180; // edi
  float v9; // [esp+Ch] [ebp-2Ch]
  float pThis_1802; // [esp+10h] [ebp-28h]
  void *Block; // [esp+24h] [ebp-14h]

  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    v4 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/FireMissileParticle.ptl", (int)this);
  else
    v4 = nullptr;
  *((uint32_t *)this + 243) = v4;
  pMem2 = operator new(0x12Cu);
  if ( pMem2 != nullptr )
    v6 = sub_428F30(pMem2, (int)"PassiveObject/Common/Particle/FireMissileParticleLight.ptl", (int)this);
  else
    v6 = nullptr;
  *((uint32_t *)this + 244) = v6;
  pThis_180 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  Block = (void *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  pThis_1802 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  v9 = (float)(int)Block;
  *(this + 181) = sub_4049C0(v9, pThis_1802, nArg2 - 1, pThis_180 - 1);
  *((uint32_t *)this + 245) = nArg2;
  return sub_4015C0("SIZZLE_CREATE", 0xDu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x60BB90 sub_60BB90
// ------------------------------------------------------------
void /*thiscall*/ sub_60BB90(uint32_t *this)
{
  *(this + 247) = 0;
  *(this + 248) = 100;
}



// ------------------------------------------------------------
// 0x60BBB0 CNFireExplosion__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNFireExplosion__vmt12C(uint32_t *this, int nArg2)
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( *(this + 247) == nArg2 )
    *(this + 247) = 0;
}



// ------------------------------------------------------------
// 0x60BBE0 CNFireExplosion__vmt1F0
// ------------------------------------------------------------
int /*thiscall*/ CNFireExplosion__vmt1F0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  if ( nArg2 == *(this + 247) )
    *(this + 112) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60BC00 CNFireExplosion__vmt1F8
// ------------------------------------------------------------
int /*thiscall*/ CNFireExplosion__vmt1F8(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  if ( nArg2 == *(this + 247) )
    *(this + 112) = 2;
  return 0;
}



// ------------------------------------------------------------
// 0x60BC20 sub_60BC20
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_60BC20(uint32_t *this)
{
  uint32_t *fld_e244; // esi
  uint32_t *result; // eax

  fld_e244 = (uint32_t *)*(this + 244);
  if ( fld_e244 != (uint32_t *)*(this + 245) )
  {
    do
    {
      if ( *fld_e244 != 0 )
        (**(void (/*thiscall*/ ***)(uint32_t, int))*fld_e244)(*fld_e244, 1);
      result = (uint32_t *)*(this + 245);
      ++fld_e244;
    }
    while ( fld_e244 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x60BC50 CNFireExplosion__vmt2BC
// ------------------------------------------------------------
// CNFireExplosion 命中结算槽（vmt2BC，103 行）：sub_4922F0（动画定位）+ sub_4E5F70（硬直率掷）+
// dword_78FE30/34（全局攻击上下文【推断：伤害倍率对】）——火焰爆炸对命中目标的结算。
void /*thiscall*/ CNFireExplosion__vmt2BC(void *this, float *pArg2, int Size)
{
  int v3; // esi
  int pThis_1D; // eax
  int v6; // eax
  uint16_t v7; // di
  uint32_t *pThis_F5; // eax
  int v9; // ecx
  uint32_t *pThis_F4; // edi
  int v11; // esi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edx
  uint32_t *v17; // eax
  int dword_78FE342; // eax
  uint8_t v19; // cl
  int v20; // edx
  uint64_t v21; // rax
  float pThis_F8; // [esp+0h] [ebp-10h]
  int i; // [esp+18h] [ebp+8h]
  int v24; // [esp+18h] [ebp+8h]

  v3 = Size;
  CNRDPassiveObject__vmt2BC((int)pArg2, Size);
  if ( Size == 30 )
  {
    pThis_1D = sub_45EBE0(*((uint32_t **)this + 29), *(uint16_t *)pArg2, *((uint16_t *)pArg2 + 1));
    v6 = __RTDynamicCast(pThis_1D, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    *((uint32_t *)this + 247) = v6;
    if ( v6 != 0 && (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0 )
      sub_4E5F70((int)this, (int)this, *((uint32_t *)this + 247), pArg2 + 1, 1, 0);
  }
  else
  {
    dword_78FE30 = (int)pArg2;
    dword_78FE34 = 0;
    if ( Size > 0 )
    {
      v7 = *(uint16_t *)pArg2;
      dword_78FE34 = 2;
      pThis_F5 = *((uint32_t **)this + 245);
      v9 = v7;
      pThis_F4 = *((uint32_t **)this + 244);
      *((uint32_t *)this + 248) = v9;
      if ( pThis_F4 != pThis_F5 )
      {
        do
        {
          v11 = 0;
          do
          {
            for ( i = 2; i != 0; --i )
            {
              v12 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_F4 + 28))(*pThis_F4);
              *(uint32_t *)(v12 + v11 + 15) *= *((uint32_t *)this + 248);
              v13 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_F4 + 28))(*pThis_F4);
              *(int *)(v13 + v11 + 15) /= 100;
              v14 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_F4 + 28))(*pThis_F4);
              *(uint32_t *)(v14 + v11 + 39) *= *((uint32_t *)this + 248);
              v15 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_F4 + 28))(*pThis_F4);
              *(int *)(v15 + v11 + 39) /= 100;
              v11 += 4;
            }
          }
          while ( v11 < 24 );
          ++pThis_F4;
        }
        while ( pThis_F4 != *((uint32_t **)this + 245) );
        v3 = Size;
      }
      pThis_F8 = (double)*((int *)this + 248) * 0.0099999998;
      sub_4922F0(pThis_F8);
      if ( dword_78FE34 < v3 )
      {
        v16 = *(int16_t *)(dword_78FE34 + dword_78FE30);
        dword_78FE34 += 2;
        v17 = *(uint32_t **)this;
        *((uint32_t *)this + 183) = v16;
        ((void (/*thiscall*/ *)(void *, int))v17[86])(this, (int)this + 724);
        dword_78FE342 = dword_78FE34;
        if ( dword_78FE34 < v3 )
        {
          v19 = *(uint8_t *)(dword_78FE34 + dword_78FE30);
          ++dword_78FE34;
          v20 = *(uint32_t *)(dword_78FE342 + 1 + dword_78FE30);
          dword_78FE34 = dword_78FE342 + 5;
          v24 = *(int *)(dword_78FE342 + 5 + dword_78FE30);
          dword_78FE34 = dword_78FE342 + 9;
          if ( v19 != 17 )
          {
            *((uint32_t *)this + 187) = v19;
            *((uint32_t *)this + 190) = v20;
            v21 = (uint64_t)*(float *)&v24;
            HIDWORD(v21) = *(uint32_t *)this;
            *((uint32_t *)this + 193) = v21;
            (*(void (/*thiscall*/ **)(void *, int))(HIDWORD(v21) + 344))(this, (int)this + 724);
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x60BE80 CNFireExplosion__vmt14C
// ------------------------------------------------------------
// CNFireExplosion 主循环槽（vmt14C）：sub_4600B0 + sub_4922F0 + sub_4E77D0 ——
// 爆炸扩散的动画推进【推断：火焰圈半径随帧扩张】。
void /*thiscall*/ CNFireExplosion__vmt14C(int *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edx
  int v5; // eax
  uint32_t *fld_e244; // edi
  int v7; // eax
  uint32_t *v8; // ebx
  float fld_e248; // [esp+10h] [ebp-48h]
  uint8_t v10[4]; // [esp+20h] [ebp-38h] BYREF
  void *Block; // [esp+24h] [ebp-34h]
  int v12; // [esp+28h] [ebp-30h]
  int v13; // [esp+2Ch] [ebp-2Ch]
  uint8_t v14[4]; // [esp+30h] [ebp-28h] BYREF
  void *v15; // [esp+34h] [ebp-24h]
  uint32_t *v16; // [esp+38h] [ebp-20h]
  int v17; // [esp+3Ch] [ebp-1Ch]
  int v18; // [esp+40h] [ebp-18h]
  int v19; // [esp+44h] [ebp-14h]
  int i; // [esp+48h] [ebp-10h]
  int v21; // [esp+54h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  v15 = nullptr;
  v16 = nullptr;
  v17 = 0;
  v2 = *this;
  v21 = 0;
  v3 = (*(int (/*thiscall*/ **)(int *))(v2 + 120))(this);
  v4 = *this;
  v18 = v3;
  v19 = (*(int (/*thiscall*/ **)(int *))(v4 + 124))(this);
  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  fld_e244 = (uint32_t *)*(this + 244);
  for ( i = v5; fld_e244 != (uint32_t *)*(this + 245); ++fld_e244 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*fld_e244 + 40))(*fld_e244, v18, v19, i);
    v7 = (*(int (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*fld_e244 + 92))(*fld_e244, v10);
    LOBYTE(v21) = 1;
    sub_4E77D0((int)v14, v7);
    LOBYTE(v21) = 0;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v12 = 0;
    v13 = 0;
    v8 = v15;
    if ( v15 != v16 )
    {
      do
      {
        if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v8 + 200))(*v8) != 0 )
        {
          fld_e248 = (double)*(this + 248) * 0.0099999998;
          (*(void (**)(void))(*(uint32_t *)*v8 + 200))();
          sub_4922F0(fld_e248);
        }
        ++v8;
      }
      while ( v8 != v16 );
    }
    sub_4600B0((void *)*(this + 29), 2, 0, (int)v14);
  }
  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  if ( *(this + 50) == 1 )
    (*(void (/*thiscall*/ **)(int *))(*this + 232))(this);
  if ( v15 != nullptr )
    j__free(v15);
}



// ------------------------------------------------------------
// 0x60BFF0 sub_60BFF0
// ------------------------------------------------------------
// 火爆生成辅助：字符串证据「NAPALM_EXPLOSION | FIRE_EXPLOSION_CREATE」（双音效 TAG：凝固弹爆+火爆生成）。
// sub_5CC5A0 + sub_41ACF0/sub_4C3640（动画对象）——火爆体的实例化。
int /*thiscall*/ sub_60BFF0(int this, int nArg2)
{
  uint32_t *pThis; // esi
  int fld_11C; // eax
  int result; // eax
  uint32_t *v5; // edi
  void *v6; // eax
  uint32_t *v7; // esi
  int v8; // eax
  int v9; // edx
  unsigned int v10; // esi
  uint32_t *v11; // ecx
  uint32_t *pThis22; // [esp-10h] [ebp-24h]
  void *Block; // [esp+0h] [ebp-14h] BYREF
  uint32_t *pThis2; // [esp+4h] [ebp-10h]
  int v15; // [esp+10h] [ebp-4h]
  int v16; // [esp+1Ch] [ebp+8h]

  pThis = (uint32_t *)this;
  fld_11C = *(uint32_t *)(this + 284);
  *(float *)(this + 724) = (float)nArg2;
  pThis2 = (uint32_t *)this;
  if ( fld_11C == 22210 )
    sub_4015C0("NAPALM_EXPLOSION", 0x10u);  // 【std::string构造赋值】
  else
    sub_4015C0("FIRE_EXPLOSION_CREATE", 0x15u);  // 【std::string构造赋值】
  result = pThis[178];
  v16 = result;
  if ( result != pThis[179] )
  {
    v5 = pThis + 243;
    while ( 1 )
    {
      Block = operator new(0x12Cu);
      v6 = nullptr;
      v15 = 0;
      if ( Block != nullptr )
      {
        if ( pThis[96] < 0x10u )
          v7 = pThis + 91;
        else
          v7 = (uint32_t *)pThis[91];
        pThis22 = pThis2;
        v8 = sub_41ACF0(v16);
        v6 = (void *)sub_4C3640(v7, v8, pThis22);
      }
      v9 = v5[1];
      v15 = -1;
      Block = v6;
      v10 = v9 != 0 ? (v5[2] - v9) >> 2 : 0;
      if ( v9 != 0 && v10 < (v5[3] - v9) >> 2 )
      {
        v11 = (uint32_t *)v5[2];
        *v11 = v6;
        v5[2] = v11 + 1;
      }
      else
      {
        sub_5CC5A0((void *)v5[2], 1, (int)&Block);
      }
      result = v16 + 4;
      v16 += 4;
      if ( v16 == pThis2[179] )
        break;
      pThis = pThis2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60C130 sub_60C130
// ------------------------------------------------------------
int /*thiscall*/ sub_60C130(uint32_t *this)
{
  *(this + 243) = 0;
  *(this + 244) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60C140 CNIceMissile__vmt14C
// ------------------------------------------------------------
// CNIceMissile 主循环槽（vmt14C）：sub_4600B0 —— 冰弹飞行编排；出生粒子见 0x60C230（IceMissileParticle 族 + ICICLE_CREATE）。
int /*thiscall*/ CNIceMissile__vmt14C(int **this)
{
  int **pThis_F3; // ebx
  int v3; // edi
  int *v4; // edx
  int v5; // eax
  int v6; // eax
  int **pThis_F322; // ebx
  void *fld_e29; // ecx
  bool v9; // zf
  int result; // eax
  uint8_t v11[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int v13; // [esp+14h] [ebp-20h]
  int v14; // [esp+18h] [ebp-1Ch]
  int v15; // [esp+1Ch] [ebp-18h]
  int v16; // [esp+20h] [ebp-14h]
  int **pThis_F32; // [esp+24h] [ebp-10h]
  int v18; // [esp+30h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  pThis_F3 = this + 243;
  pThis_F32 = this + 243;
  v16 = 2;
  do
  {
    if ( ((int (/*thiscall*/ *)(int **))(*this)[38])(this) != 0 )
      v3 = ((int (/*thiscall*/ *)(int **))(*this)[30])(this) - 15;
    else
      v3 = ((int (/*thiscall*/ *)(int **))(*this)[30])(this) + 15;
    v4 = *this;
    v15 = **pThis_F3;
    v5 = ((int (/*thiscall*/ *)(int **))v4[32])(this);
    v6 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v5);
    pThis_F322 = pThis_F32;
    (*(void (/*thiscall*/ **)(int *, int, int))(v15 + 40))(*pThis_F32, v3, v6);
    (*(void (/*thiscall*/ **)(int *, uint8_t *))(**pThis_F322 + 92))(*pThis_F322, v11);
    fld_e29 = *(this + 29);
    v18 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v11);
    v18 = -1;
    if ( Block != nullptr )
      j__free(Block);
    pThis_F3 = pThis_F322 + 1;
    result = v16 - 1;
    v9 = v16 == 1;
    Block = nullptr;
    v13 = 0;
    v14 = 0;
    pThis_F32 = pThis_F3;
    --v16;
  }
  while ( !v9 );
  return result;
}



// ------------------------------------------------------------
// 0x60C230 sub_60C230
// ------------------------------------------------------------
// 冰弹出生粒子：字符串证据「PassiveObject/Common/Particle/IceMissileParticleLight.ptl |
// IceMissileParticleTail.ptl」（光晕+拖尾双发射器）+「ICICLE_CREATE」（音效 TAG）+ sub_4049C0 lerp。
int /*thiscall*/ sub_60C230(float *this, int nArg2)
{
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  uint32_t *pMem2; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // edx
  int v8; // edi
  double v9; // st7
  uint32_t *v10; // eax
  double v11; // st7
  uint32_t *v12; // eax
  float v14; // [esp+34h] [ebp-30h]
  float v15; // [esp+34h] [ebp-30h]
  float v16; // [esp+34h] [ebp-30h]
  float pThis_180; // [esp+38h] [ebp-2Ch]
  float pThis_1802; // [esp+38h] [ebp-2Ch]
  float pThis_1803; // [esp+38h] [ebp-2Ch]
  void *Block; // [esp+50h] [ebp-14h]
  void *Blocka; // [esp+50h] [ebp-14h]
  void *Blockb; // [esp+50h] [ebp-14h]

  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    1,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    v4 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/IceMissileParticleLight.ptl", (int)this);
  else
    v4 = nullptr;
  *((uint32_t *)this + 243) = v4;
  pMem2 = operator new(0x12Cu);
  if ( pMem2 != nullptr )
    v6 = sub_428F30(pMem2, (int)"PassiveObject/Common/Particle/IceMissileParticleTail.ptl", (int)this);
  else
    v6 = nullptr;
  v7 = *(uint32_t **)this;
  *((uint32_t *)this + 244) = v6;
  v8 = ((int (/*thiscall*/ *)(float *, uint32_t))v7[96])(this, 0);
  Block = (void *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  --v8;
  pThis_180 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  v14 = (float)(int)Block;
  v9 = sub_4049C0(v14, pThis_180, nArg2 - 1, v8);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v10 = *(uint32_t **)this;
  *(this + 181) = v9;
  Blocka = (void *)((int (/*thiscall*/ *)(float *, int))v10[96])(this, 3);
  pThis_1802 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 4);
  v15 = (float)(int)Blocka;
  v11 = sub_4049C0(v15, pThis_1802, nArg2 - 1, v8);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v12 = *(uint32_t **)this;
  *(this + 190) = v11;
  Blockb = (void *)((int (/*thiscall*/ *)(float *, int))v12[96])(this, 5);
  pThis_1803 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 6);
  v16 = (float)(int)Blockb;
  *((uint32_t *)this + 193) = (uint64_t)sub_4049C0(v16, pThis_1803, nArg2 - 1, v8);
  return sub_4015C0("ICICLE_CREATE", 0xDu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x60C3D0 sub_60C3D0
// ------------------------------------------------------------
int /*thiscall*/ sub_60C3D0(int this)
{
  *(uint8_t *)(this + 976) = 0;
  *(uint32_t *)(this + 972) = 0;
  *(uint8_t *)(this + 977) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60C3F0 CNThunderBolt__vmt2A8
// ------------------------------------------------------------
// CNThunderBolt 碰撞响应槽（vmt2A8）：sub_47E720/47EF20/47EFD0（命中几何扫描族）——
// 落雷（ThunderBolt）对目标的判定；落地震屏与 EarthQuake.ani 在 0x60C6A0。
char /*thiscall*/ CNThunderBolt__vmt2A8(int *this, int nArg2)
{
  int fld_e243; // eax
  char *v4; // eax
  int fld_e176; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // edx
  int v9; // eax
  char *v10; // eax
  int fld_e1762; // ebx
  char *v12; // edi
  int v13; // eax

  CNRDPassiveObject__vmt2A8(this, nArg2);
  LOBYTE(fld_e243) = *((uint8_t *)this + 977);
  if ( (uint8_t)fld_e243 == 0 )
  {
    fld_e243 = *(this + 243);
    if ( fld_e243 == 1 )
    {
      v4 = (char *)sub_47E720(1, 0xBu);
      fld_e176 = *(this + 176);
      v6 = v4;
      *((float *)this + 190) = (double)sub_47EF20(v4, 1u, fld_e176, -1, -1, 11) * 0.1;
      v7 = sub_47EF20(v6, 2u, fld_e176, -1, -1, 11);
      v8 = *this;
      *(this + 193) = v7;
      v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 388))(this);
      fld_e243 = sub_47EFD0(v6, 0.0, fld_e176, v9, v9, 0);
      *((uint8_t *)this + 977) = 1;
      *((float *)this + 181) = (float)fld_e243;
    }
    else
    {
      if ( fld_e243 == 3 )
      {
        v10 = (char *)sub_47E720(3, 0x36u);
        fld_e1762 = *(this + 176);
        v12 = v10;
        *((float *)this + 190) = (double)sub_47EF20(v10, 2u, fld_e1762, -1, -1, 11) * 0.1;
        *(this + 193) = sub_47EF20(v12, 3u, fld_e1762, -1, -1, 11);
        v13 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
        fld_e243 = sub_47EFD0(v12, COERCE_FLOAT(1), fld_e1762, v13, v13, 0);
        *((float *)this + 181) = (float)fld_e243;
      }
      *((uint8_t *)this + 977) = 1;
    }
  }
  return fld_e243;
}



// ------------------------------------------------------------
// 0x60C520 CNThunderBolt__vmt2BC
// ------------------------------------------------------------
void /*userpurge*/ CNThunderBolt__vmt2BC(uint32_t **pArg1@<ecx>, int nArg2@<ebx>, float *pArg3, size_t Size)
{
  int v5; // eax
  int v6; // eax

  CNRDPassiveObject__vmt2BC((int)pArg3, Size);
  if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*pArg1)[77])(pArg1) != 0 )
  {
    v5 = sub_45EBE0(pArg1[29], *(uint16_t *)pArg3, *((uint16_t *)pArg3 + 1));
    v6 = __RTDynamicCast(v5, 0, &CNRDObject `RTTI Type Descriptor', &IRDCollisionObject `RTTI Type Descriptor', 0);
    if ( v6 != 0 )
      sub_4E5F70(nArg2, (int)pArg1, v6, pArg3 + 1, 1, 1);
  }
}



// ------------------------------------------------------------
// 0x60C590 sub_60C590
// ------------------------------------------------------------
// 落雷生成辅助：字符串证据「THUNDER_STRIKE」（音效 TAG）+ sub_4049C0 lerp —— 雷击参数插值。
int /*thiscall*/ sub_60C590(float *this, int nArg2, int nArg3)
{
  int pThis_180; // edi
  int v5; // ebx
  double v6; // st7
  int v7; // edx
  double v8; // st7
  float v9; // edx
  float v11; // [esp+1Ch] [ebp-20h]
  float v12; // [esp+1Ch] [ebp-20h]
  float v13; // [esp+1Ch] [ebp-20h]
  float pThis_1803; // [esp+20h] [ebp-1Ch]
  float pThis_1804; // [esp+20h] [ebp-1Ch]
  float pThis_1805; // [esp+20h] [ebp-1Ch]
  int pThis_1802; // [esp+38h] [ebp-4h]
  int v18; // [esp+38h] [ebp-4h]
  int v19; // [esp+44h] [ebp+8h]

  *((uint32_t *)this + 243) = nArg3;
  if ( nArg3 == 0 )
  {
    pThis_180 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
    pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
    --pThis_180;
    v5 = nArg2 - 1;
    pThis_1803 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
    v11 = (float)pThis_1802;
    v6 = sub_4049C0(v11, pThis_1803, nArg2 - 1, pThis_180);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v7 = *(uint32_t *)this;
    *(this + 181) = v6;
    v19 = (*(int (/*thiscall*/ **)(float *, int))(v7 + 384))(this, 3);
    pThis_1804 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 4);
    v12 = (float)v19;
    v8 = sub_4049C0(v12, pThis_1804, v5, pThis_180);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v9 = *this;
    *(this + 190) = v8;
    v18 = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v9) + 384))(this, 5);
    pThis_1805 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 6);
    v13 = (float)v18;
    *((uint32_t *)this + 193) = (uint64_t)sub_4049C0(v13, pThis_1805, v5, pThis_180);
  }
  *((uint8_t *)this + 976) = 0;
  return sub_4015C0("THUNDER_STRIKE", 0xEu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x60C6A0 CNThunderBolt__vmt14C
// ------------------------------------------------------------
// CNThunderBolt 主循环槽（vmt14C）：字符串证据「PassiveObject/Common/Animation/EarthQuake.ani」+
// sub_424120（研究 20 P41 定案：[shake screen] 震屏入口）+ dword_8F82B0 —— 落雷落地时的震屏与余波。
int /*thiscall*/ CNThunderBolt__vmt14C(int *this)
{
  int pObj; // edi
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *fld_e29; // ecx
  char *v8; // edi
  int v9; // eax
  int v10; // eax
  char *v11; // edi
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  void *Block2; // eax
  bool v18; // zf
  int result; // eax
  char v20[4]; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-20h]
  int v22; // [esp+10h] [ebp-1Ch]
  int v23; // [esp+14h] [ebp-18h]
  int v24; // [esp+18h] [ebp-14h]
  char *v25; // [esp+1Ch] [ebp-10h]
  int v26; // [esp+28h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(int *)(*(this + 30) + 148) >= 1 && *((uint8_t *)this + 976) == 0 )
  {
    pObj = dword_8F82B0;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F82B0 + 12))(dword_8F82B0, 0);
    v3 = *(uint32_t *)pObj;
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v4);
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);
    (*(void (/*thiscall*/ **)(int, int))(v3 + 40))(pObj, v6);
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj + 92))(pObj, v20);
    fld_e29 = (void *)*(this + 29);
    v26 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v20);
    sub_424120(*(uint32_t **)(*(this + 29) + 132), 2, 150);
    if ( *(this + 243) == 2 )
    {
      v8 = (char *)sub_44B6C0(284);
      v25 = v8;
      LOBYTE(v26) = 1;
      if ( v8 != nullptr )
      {
        v9 = sub_42FCB0(228);
        v24 = v9;
        LOBYTE(v26) = 2;
        if ( v9 != 0 )
          v10 = sub_431860(v9, "PassiveObject/Common/Animation/EarthQuake.ani", 1);
        else
          v10 = 0;
        LOBYTE(v26) = 1;
        v11 = sub_44E1F0(v8, v10, 1);
      }
      else
      {
        v11 = nullptr;
      }
      v12 = *(uint32_t *)v11;
      LOBYTE(v26) = 0;
      (*(void (/*thiscall*/ **)(char *, int))(v12 + 72))(v11, 2);
      sub_45FE80(*(this + 29), (int)v11, 2, 0, (int)v11, (int)this, 0);
      v13 = *(uint32_t *)v11;
      v14 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v15 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v14);
      v16 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v15 - 1);
      (*(void (/*thiscall*/ **)(char *, int))(v13 + 112))(v11, v16);
    }
    Block2 = Block;
    v18 = Block == nullptr;
    *((uint8_t *)this + 976) = 1;
    v26 = -1;
    if ( !v18 )
      j__free(Block2);
    Block = nullptr;
    v22 = 0;
    v23 = 0;
  }
  result = *(this + 30);
  if ( *(uint8_t *)(result + 170) != 0 && *((uint8_t *)this + 264) == 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x60C850 sub_60C850
// ------------------------------------------------------------
int /*thiscall*/ sub_60C850(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint8_t *)(this + 980) = 1;
  *(uint8_t *)(this + 981) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60C870 sub_60C870
// ------------------------------------------------------------
int /*thiscall*/ sub_60C870(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e243)(uint32_t, int); // ecx
  int result; // eax

  fld_e243 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 243);
  if ( fld_e243 != nullptr )
    result = (**fld_e243)(fld_e243, 1);
  *(this + 243) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60C890 CNParticleFactory__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNParticleFactory__vmtC(int this)
{
  int result; // eax

  CNRDPassiveObject__vmtC((int *)this);
  result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 972) + 12))(
             *(uint32_t *)(this + 972),
             *(uint32_t *)(this + 976));
  *(uint8_t *)(this + 981) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60C8C0 CNParticleFactory__vmt14C
// ------------------------------------------------------------
// CNParticleFactory 主循环槽（vmt14C，82 行）：sub_425050 + sub_4600B0 ——
// 【新发现】『粒子工厂 PO』：以 PO 形态周期性发射粒子（P36 发射器的对象化封装，地图机关的喷泉/毒雾源）。
void /*thiscall*/ CNParticleFactory__vmt14C(int **this)
{
  int fld_e87; // ecx
  int fld_e29; // eax
  int v4; // eax
  int *fld_e243; // ecx
  int v6; // edi
  int v7; // eax
  float *v8; // eax
  float *v9; // ecx
  bool v10; // zf
  int v11; // ebx
  int v12; // eax
  int v13; // edx
  int *v14; // ebx
  int v15; // eax
  int v16; // eax
  int fld_e2432; // edi
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int fld_e2433; // edi
  int v22; // eax
  void *fld_e292; // ecx
  uint8_t v24[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  int v26; // [esp+1Ch] [ebp-14h]
  int v27; // [esp+20h] [ebp-10h]
  int v28; // [esp+2Ch] [ebp-4h]

  if ( *((uint8_t *)this + 981) == 0 )
  {
    fld_e87 = (int)*(this + 87);
    if ( fld_e87 != 0 && (unsigned int)(((int)*(this + 88) - fld_e87) >> 2) > 2 && *(uint32_t *)(fld_e87 + 8) == 1 )
    {
      fld_e29 = (int)*(this + 29);
      if ( fld_e29 != 0 )
      {
        v4 = sub_425050(*(uint32_t **)(*(uint32_t *)(fld_e29 + 132) + 44));
        fld_e243 = *(this + 243);
        v6 = v4;
        v7 = *fld_e243;
        v27 = v6;
        v8 = (float *)(*(int (/*thiscall*/ **)(int *))(v7 + 36))(fld_e243);
        v9 = v8;
        v10 = *(uint32_t *)v8 == -1082130432;
        v11 = *((uint32_t *)v8 + 3);
        v26 = v11;
        if ( !v10 )
          *v8 = (double)v27 * *v8 / (double)v26;
        v12 = v6 * *((uint32_t *)v8 + 1) / v11;
        v13 = v6 * *((uint32_t *)v9 + 1) % v11;
        *((uint32_t *)v9 + 3) = v6;
        *((uint32_t *)v9 + 1) = v12;
        v14 = *this;
        v15 = ((int (/*fastcall*/ *)(int **, int))(*this)[32])(this, v13);
        v16 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v15);
        ((void (/*thiscall*/ *)(int **, int, int))v14[28])(this, v6 / 2, v16);
      }
    }
    *((uint8_t *)this + 981) = 1;
  }
  CNRDPassiveObject__vmt14C((int)this);
  fld_e2432 = **(this + 243);
  v18 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
  v19 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v18);
  v20 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v19);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2432 + 40))(*(this + 243), v20);
  fld_e2433 = (int)*(this + 243);
  v22 = ((int (/*thiscall*/ *)(int **))(*this)[38])(this);
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2433 + 28))(fld_e2433) + 84) = v22 == 0;
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 243) + 92))(*(this + 243), v24);
  fld_e292 = *(this + 29);
  v28 = 0;
  sub_4600B0(fld_e292, 2, 0, (int)v24);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(this + 243) + 68))(*(this + 243)) != 0
    && *((uint8_t *)this + 980) != 0 )
  {
    ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[21])(this, 0);
  }
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x60CA50 sub_60CA50
// ------------------------------------------------------------
// 粒子工厂装载：sub_41ACF0 + sub_4C3640 —— 工厂体的动画/伴随对象实例化。
unsigned int /*thiscall*/ sub_60CA50(int this, int nArg2)
{
  int pObj; // eax
  int pThis_16C; // edi
  int fld_2C8; // eax
  uint32_t *fld_15C; // ecx
  unsigned int result; // eax
  int fld_15C2; // ecx
  void *Block; // [esp+8h] [ebp-10h]

  Block = operator new(0x12Cu);
  pObj = 0;
  if ( Block != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      pThis_16C = this + 364;
    else
      pThis_16C = *(uint32_t *)(this + 364);
    fld_2C8 = sub_41ACF0(*(uint32_t *)(this + 712));
    pObj = sub_4C3640(pThis_16C, fld_2C8, this);
  }
  *(uint32_t *)(this + 972) = pObj;
  fld_15C = *(uint32_t **)(this + 348);
  if ( fld_15C != nullptr && (*(uint32_t *)(this + 352) - (int)fld_15C) >> 2 != 0 )
    *(uint32_t *)(this + 976) = *fld_15C;
  result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, *(uint32_t *)(this + 976));
  fld_15C2 = *(uint32_t *)(this + 348);
  if ( fld_15C2 != 0 )
  {
    result = (*(uint32_t *)(this + 352) - fld_15C2) >> 2;
    if ( result > 1 )
    {
      result = *(uint32_t *)(this + 348) + 4;
      if ( *(uint32_t *)(fld_15C2 + 4) == 0 )
        *(uint8_t *)(this + 980) = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60CB40 sub_60CB40
// ------------------------------------------------------------
int /*thiscall*/ sub_60CB40(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint8_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60CB70 sub_60CB70
// ------------------------------------------------------------
int /*thiscall*/ sub_60CB70(uint32_t *this, int nArg2)
{
  *(this + 247) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x60CB80 CNBlast__vmt10
// ------------------------------------------------------------
// CNBlast 初始化（vmt10）：爆风（冲击波）PO 的初值装配。
int /*thiscall*/ CNBlast__vmt10(int this)
{
  int result; // eax
  int v3; // edi
  int fld_2B4; // ebx
  uint32_t *pThis_3CC; // esi
  int i; // [esp+4h] [ebp-4h]

  CNRDPassiveObject__vmt10((uint8_t *)this);
  result = *(uint32_t *)(this + 692);
  if ( result != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 120))(result);
    fld_2B4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 692) + 124))(*(uint32_t *)(this + 692));
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)this + 112))(this, v3, fld_2B4, 0);
    pThis_3CC = (uint32_t *)(this + 972);
    for ( i = 3; i != 0; --i )
    {
      if ( *pThis_3CC != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*pThis_3CC + 112))(*pThis_3CC, v3, fld_2B4, 0);
      ++pThis_3CC;
      result = i - 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60CBF0 CNBlast__vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNBlast__vmt12C(uint32_t *this, int nArg2)
{
  int result; // eax

  CNRDPassiveObject__vmt12C(this, nArg2);
  result = 0;
  if ( nArg2 == *(this + 243) )
    *(this + 243) = 0;
  if ( nArg2 == *(this + 244) )
    *(this + 244) = 0;
  if ( nArg2 == *(this + 245) )
    *(this + 245) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60CC40 CNBlast__vmt14C
// ------------------------------------------------------------
// CNBlast 主循环槽（vmt14C，156 行）：字符串证据「Common/CommonEffect/Animation/LevelUp.ani |
// Blast1.ani | Blast2.ani」+「LEVEL_UP | SHOUTING」（双音效 TAG：升级/怒吼）。
// sub_44B6C0/44E0D0/44E1F0（帧事件族，P26）+ sub_4910A0/49C5F0/49C620 + sub_600890 ——
// 升级冲击波/怒吼冲击波的扩散演出（双动画层 Blast1/2 叠放，P33 叠放风格）。
int /*usercall*/ sub_60CC40@<eax>(int pArg1@<ecx>, int nArg2@<ebx>)
{
  int pObj; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  char *v9; // ebx
  int v10; // eax
  int v11; // ecx
  uint32_t *v12; // ebx
  int v13; // eax
  char *v14; // eax
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // eax
  int result; // eax
  int v22; // [esp-8h] [ebp-30h]
  char *v24; // [esp+8h] [ebp-20h]
  int v25; // [esp+Ch] [ebp-1Ch]
  int v26; // [esp+Ch] [ebp-1Ch]
  int i; // [esp+Ch] [ebp-1Ch]
  int v28; // [esp+10h] [ebp-18h]
  int v29; // [esp+14h] [ebp-14h]
  int v30; // [esp+18h] [ebp-10h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  pObj = *(uint32_t *)(pArg1 + 692);
  if ( *(uint8_t *)(pArg1 + 984) == 0 )
  {
    v4 = 0;
    if ( pObj != 0 )
    {
      v28 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, nArg2);
      v29 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
      v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
      if ( *(uint32_t *)(pArg1 + 988) == 0 )
      {
        v5 = sub_42FCB0(228);
        if ( v5 != 0 )
          v4 = sub_431860(v5, "Common/CommonEffect/Animation/LevelUp.ani", 1);
        if ( sub_44B6C0(284) != 0 )
          v6 = sub_44E1F0(v4, 1);
        else
          v6 = 0;
        v7 = *(uint32_t *)(pArg1 + 116);
        *(uint32_t *)(pArg1 + 980) = v6;
        sub_45FE80(v7, pObj, 2, 0, v6, pObj, 0);
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(pArg1 + 980) + 112))(
          *(uint32_t *)(pArg1 + 980),
          v28,
          v29,
          v30);
      }
      v8 = sub_42FCB0(228);
      if ( v8 != 0 )
        v25 = sub_431860(v8, "Common/CommonEffect/Animation/Blast1.ani", 1);
      else
        v25 = 0;
      v9 = (char *)sub_44B6C0(284);
      if ( v9 != nullptr )
      {
        sub_44E0D0(v9, v25, 1);
        *(uint32_t *)v9 = &CNRDPooledObject::`vftable';
        v10 = (int)v9;
      }
      else
      {
        v10 = 0;
      }
      v11 = *(uint32_t *)(a1 + 116);
      v12 = (uint32_t *)(a1 + 972);
      *(uint32_t *)(a1 + 972) = v10;
      sub_45FE80(v11, v3, 2, 0, v10, v3, 1);
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*v12 + 112))(*v12, v28, v29, v30);
      v13 = sub_42FCB0(228);
      if ( v13 != 0 )
        v26 = sub_431860(v13, "Common/CommonEffect/Animation/Blast2.ani", 1);
      else
        v26 = 0;
      v14 = (char *)sub_44B6C0(284);
      v24 = v14;
      if ( v14 != nullptr )
      {
        sub_44E0D0(v14, v26, 1);
        v15 = (int)v24;
        *(uint32_t *)v24 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v15 = 0;
      }
      v16 = *(uint32_t *)(pArg1 + 116);
      *(uint32_t *)(pArg1 + 976) = v15;
      sub_45FE80(v16, pObj, 2, 0, v15, pObj, 0);
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(pArg1 + 976) + 112))(*(uint32_t *)(pArg1 + 976), v28, v29);
      for ( i = 2; i != 0; --i )
      {
        v17 = *(uint32_t *)(pArg1 + 120);
        v18 = *(uint32_t *)(v17 + 212);
        if ( v18 != 0 )
          v19 = sub_4910A0(v18);
        else
          v19 = *(uint32_t *)(v17 + 32);
        v22 = v19;
        v20 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v12 + 200))(*v12);
        sub_493A60(v20, v22);
        ++v12;
      }
      sub_49C620(0, 1, 0);
      sub_49C5F0(0, 0, 0, 2000);
      switch ( *(uint32_t *)(pArg1 + 988) )
      {
        case 0:
        case 1:
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "LEVEL_UP",
            -1,
            0,
            0);
          break;
        case 2:
          goto LABEL_31;
        case 3:
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 596))(pArg1, 0);
LABEL_31:
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "SHOUTING",
            -1,
            0,
            0);
          break;
        default:
          break;
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 312))(pArg1, 0);
    }
    *(uint8_t *)(pArg1 + 984) = 1;
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    result = *(uint32_t *)(pArg1 + 972);
    if ( result == 0 )
      return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 312))(pArg1, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x60CF90 CNEarthQuake__vmt14C
// ------------------------------------------------------------
// CNEarthQuake 主循环槽（vmt14C）：字符串证据「TAU_EQUAKE | TAU_STONEDROP」（音效 TAG —— ToU 氏族地震/落石）+
// sub_424120（震屏）——地图机关地震 PO。
char /*thiscall*/ CNEarthQuake__vmt14C(uint32_t *this)
{
  int v2; // edx
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(int *)(*(this + 30) + 148) >= 1 && *((uint8_t *)this + 972) == 0 )
  {
    sub_424120(
      *(uint32_t **)(*(this + 29) + 132),
      (uint64_t)((double)(int)*(this + 247) * 7.5),
      750 * *(this + 247));
    v2 = *this;
    *((uint8_t *)this + 972) = 1;
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v2 + 212))(this, "TAU_EQUAKE", -1, 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "TAU_STONEDROP", -1, 0, 0);
  }
  result = *(uint8_t *)(*(this + 30) + 170);
  if ( result != 0 )
  {
    result = *((uint8_t *)this + 264);
    if ( result == 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x60D040 sub_60D040
// ------------------------------------------------------------
int /*thiscall*/ sub_60D040(uint8_t *this, int nArg2)
{
  int v3; // eax
  int v4; // eax
  int v5; // edx

  *(this + 972) = 0;
  v3 = sub_42FCB0(228);
  if ( v3 != 0 )
    v4 = sub_431860(v3, "PassiveObject/Common/Animation/EarthQuakeRing.ani", 1);
  else
    v4 = 0;
  v5 = *(uint32_t *)this;
  *((uint32_t *)this + 244) = v4;
  (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(v5 + 204))(this, -1, v4, 0, 0, 0, 0);
  sub_4015C0("TAU_CRASH", 9u);  // 【std::string构造赋值】
  *((uint32_t *)this + 247) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x60D0E0 sub_60D0E0
// ------------------------------------------------------------
int /*thiscall*/ sub_60D0E0(void ***this)
{
  int fld_e244; // esi
  int result; // eax

  fld_e244 = (int)*(this + 244);
  if ( fld_e244 != 0 )
  {
    sub_42AF90(*(this + 244));
    result = sub_657740(fld_e244, 228);
  }
  *(this + 244) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x60D120 sub_60D120
// ------------------------------------------------------------
int /*thiscall*/ sub_60D120(int this)
{
  *(uint8_t *)(this + 976) = 0;
  *(uint8_t *)(this + 264) = 0;
  *(uint32_t *)(this + 984) = 1;
  *(uint32_t *)(this + 972) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60D140 CNDangerousGas__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNDangerousGas__vmt12C(uint32_t *this, int nArg2)
{
  if ( (uint32_t *)nArg2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
  CNRDPassiveObject__vmt12C(this, nArg2);
}



// ------------------------------------------------------------
// 0x60D170 CNDangerousGas__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNDangerousGas__vmt1F4(int *this, uint32_t *uArg2, float *pArg3, char pszArg4)
{
  uint32_t *v5; // eax

  v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this);
  if ( v5[6] != 17 )
    v5[12] = *(this + 246);
  if ( v5[7] != 17 )
    v5[13] = *(this + 246);
  if ( v5[8] != 17 )
    v5[14] = *(this + 246);
  return CNRDPassiveObject__vmt1F4(this, uArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x60D1D0 sub_60D1D0
// ------------------------------------------------------------
int /*thiscall*/ sub_60D1D0(float *this, int nArg2, int nArg3)
{
  int v4; // eax
  int v5; // edi
  float v7; // [esp+Ch] [ebp-20h]
  float pThis_1802; // [esp+10h] [ebp-1Ch]
  int pThis_180; // [esp+24h] [ebp-8h]

  v4 = *(uint32_t *)this;
  *((uint8_t *)this + 976) = 0;
  v5 = (*(int (/*stdcall*/ **)(uint32_t))(v4 + 384))(0);
  pThis_180 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  pThis_1802 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  v7 = (float)pThis_180;
  *(this + 181) = sub_4049C0(v7, pThis_1802, nArg2 - 1, v5 - 1);
  *((uint32_t *)this + 246) = nArg2;
  *((uint32_t *)this + 245) = nArg3;
  return sub_4015C0("THUNDERBOLT_CREATE", 0x12u);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x60D260 CNDangerousGas__vmt14C
// ------------------------------------------------------------
// CNDangerousGas 主循环槽（vmt14C，91 行）：字符串证据「PassiveObject/Common/%s」（路径模板格式化）+
// 「CLOUD_KILL_LOOP」（音效 TAG —— 毒云循环）。sub_428F30（粒子发射器）+ dword_796E50 ——
// 毒瓦斯云的周期喷发（云杀 = 猛毒地带机关）。
void /*thiscall*/ CNDangerousGas__vmt14C(uint32_t *this)
{
  int v2; // eax
  const char *v3; // eax
  uint32_t *pMem; // eax
  uint32_t *v5; // eax
  int v6; // eax
  int v7; // edx
  int pObj; // eax
  int v9; // eax
  double v10; // st7
  int fld_e243; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  void *fld_e29; // ecx
  uint8_t v16[4]; // [esp+4h] [ebp-228h] BYREF
  void *Block; // [esp+8h] [ebp-224h]
  int v18; // [esp+14h] [ebp-218h]
  void *pMem2; // [esp+18h] [ebp-214h]
  char Buffer[512]; // [esp+1Ch] [ebp-210h] BYREF
  int dword_796E502; // [esp+21Ch] [ebp-10h]
  int v22; // [esp+228h] [ebp-4h]

  dword_796E502 = dword_796E50;
  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 976) == 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 672))(this);
    v3 = (const char *)sub_41ACF0(*(uint32_t *)(v2 + 32));
    sprintf(Buffer, "PassiveObject/Common/%s", v3);
    pMem = operator new(0x12Cu);
    pMem2 = pMem;
    v22 = 0;
    if ( pMem != nullptr )
      v5 = sub_428F30(pMem, (int)Buffer, 0);
    else
      v5 = nullptr;
    v22 = -1;
    *(this + 243) = v5;
    if ( v5 != nullptr )
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
      v7 = *this;
      if ( v6 != 0 )
      {
        pObj = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 684))(this);
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 192))(pObj);
        v9 = *this;
        *(float *)&pMem2 = (double)v18 * 0.5;
        v18 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 128))(this);
        v10 = (double)v18 + *(float *)&pMem2;
      }
      else
      {
        *(float *)&pMem2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(v7 + 128))(this));
        v10 = (double)(int)pMem2;
      }
      fld_e243 = *(uint32_t *)*(this + 243);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)v10);
      v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v12);
      (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e243 + 40))(*(this + 243), v13);
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 243) + 12))(*(this + 243), 0);
    }
    v14 = *this;
    *((uint8_t *)this + 976) = 1;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v14 + 216))(this, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, uint32_t, uint32_t))(*this + 212))(
      this,
      "CLOUD_KILL_LOOP",
      0,
      0,
      0);
  }
  if ( *(uint8_t *)(*(this + 30) + 170) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 68))(*(this + 243)) == 0
    || *((uint8_t *)this + 264) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v16);
    fld_e29 = (void *)*(this + 29);
    v22 = 1;
    sub_4600B0(fld_e29, 2, 0, (int)v16);
    if ( Block != nullptr )
      j__free(Block);
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  }
}



// ------------------------------------------------------------
// 0x60D480 CNIceNiddleGroup__vmt288
// ------------------------------------------------------------
int /*stdcall*/ CNIceNiddleGroup__vmt288(uint32_t *uArg1, int nArg2)
{
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 20) == 1 )
  {
    *uArg1 = 0;
    return 2;
  }
  else
  {
    *uArg1 = 100;
    return 0;
  }
}



// ------------------------------------------------------------
// 0x60D4C0 CNIceNiddleGroup__vmt14C
// ------------------------------------------------------------
// CNIceNiddleGroup 主循环槽（vmt14C）：sub_4E4A50（动作包）+ sub_699000（clock_now）——
// 冰针群（IceNiddleGroup）的齐射调度；命中溅射见 0x60D5A0（WaterHitParticleLIght.ptl）。
unsigned int /*thiscall*/ CNIceNiddleGroup__vmt14C(uint32_t *this)
{
  int i; // edi
  int v3; // eax
  unsigned int result; // eax
  int v5; // [esp-18h] [ebp-20h]
  int v6; // [esp-14h] [ebp-1Ch]
  int v7; // [esp-10h] [ebp-18h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) == 0 )
  {
    for ( i = 0; i < 4; ++i )
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      sub_4E4A50(*(this + 173), *(this + 71) + i + 1, *(this + 249), v3, v5, v6, v7, 0, 0, 0);
    }
    *((uint8_t *)this + 972) = 1;
  }
  if ( *(uint8_t *)(*(this + 30) + 170) == 0 || *((uint8_t *)this + 264) != 0 )
  {
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( *(this + 247) + 2000 < result )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      *(this + 247) = result;
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x60D5A0 CNIceNiddleGroup__vmt2B4
// ------------------------------------------------------------
// 冰针命中溅射槽（vmt2B4）：寿命检查（+170<=0 → vt+312 自毁）+ 惰性创建粒子发射器
// （首次才 operator new(0x12C=300B) → sub_428F30，字符串证据「Common/HitEffect/Particle/WaterHitParticleLIght.ptl」）
// → vt+12 复位 / vt+40 设位 / vt+92 取名 → sub_4600B0 演播层（层 2）。与 0x61EC80（AraclothoMissile）同构。
void /*thiscall*/ CNIceNiddleGroup__vmt2B4(int *this, int nArg2, void *pArg3, int nArg4, int nArg5, int nArg6)
{
  uint32_t *pMem; // eax
  uint32_t *v8; // eax
  void *fld_e29; // ecx
  uint8_t v10[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v12; // [esp+1Ch] [ebp-4h]

  if ( *(this + 170) <= 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  if ( (int)pArg3 > 0 )
  {
    if ( *(this + 248) == 0 )
    {
      pMem = operator new(0x12Cu);
      v12 = 0;
      if ( pMem != nullptr )
        v8 = sub_428F30(pMem, (int)"Common/HitEffect/Particle/WaterHitParticleLIght.ptl", (int)this);
      else
        v8 = nullptr;
      v12 = -1;
      *(this + 248) = (int)v8;
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 248) + 12))(*(this + 248), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 248) + 40))(*(this + 248), nArg4, nArg5, nArg6);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 248) + 92))(*(this + 248), v10);
    fld_e29 = (void *)*(this + 29);
    v12 = 1;
    sub_4600B0(fld_e29, 2, 0, (int)v10);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x60D6A0 sub_60D6A0
// ------------------------------------------------------------
// 冰针光晕装载：字符串证据「PassiveObject/Common/Animation/IceNiddleGlow.ani」+「ICE_NIDDLE_HIT」（音效 TAG）。
// sub_42FCB0（资源 228 门）→ sub_431860 生成 → vt+204 绑定；波次参数 sub_4049C0 按波号插值（+181）。
void /*thiscall*/ sub_60D6A0(uint8_t *this, int nArg2)
{
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int pThis_57; // eax
  int pThis_180; // edi
  float v8; // [esp+24h] [ebp-2Ch]
  float pThis_1803; // [esp+28h] [ebp-28h]
  int pThis_1802; // [esp+3Ch] [ebp-14h]

  *(this + 972) = 0;
  *((uint32_t *)this + 248) = 0;
  v3 = sub_42FCB0(228);
  if ( v3 != 0 )
    v4 = sub_431860(v3, "PassiveObject/Common/Animation/IceNiddleGlow.ani", 1);
  else
    v4 = 0;
  v5 = *(uint32_t *)this;
  *((uint32_t *)this + 244) = v4;
  (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(v5 + 204))(this, 1, v4, 0, 0, 0, 0);
  sub_4015C0("ICE_NIDDLE_HIT", 0xEu);  // 【std::string构造赋值】
  pThis_57 = **((uint32_t **)this + 87);
  *((uint32_t *)this + 170) = pThis_57;
  *((uint32_t *)this + 171) = pThis_57;
  *((uint32_t *)this + 247) = sub_699000((int)(this + 36));
  pThis_180 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 1);
  pThis_1802 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 2);
  pThis_1803 = (float)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 3);
  v8 = (float)pThis_1802;
  *((float *)this + 181) = sub_4049C0(v8, pThis_1803, nArg2 - 1, pThis_180 - 1);
  *((uint32_t *)this + 249) = nArg2;
}



// ------------------------------------------------------------
// 0x60D7C0 sub_60D7C0
// ------------------------------------------------------------
int /*thiscall*/ sub_60D7C0(int this)
{
  int fld_3D0; // edi
  int result; // eax
  int (/*thiscall*/ ***pThis_3E0)(uint32_t, int); // ecx

  fld_3D0 = *(uint32_t *)(this + 976);
  if ( fld_3D0 != 0 )
  {
    sub_42AF90(*(void ***)(this + 976));
    result = sub_657740(fld_3D0, 228);
  }
  *(uint32_t *)(this + 976) = 0;
  pThis_3E0 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 992);
  if ( pThis_3E0 != nullptr )
    result = (**pThis_3E0)(pThis_3E0, 1);
  *(uint32_t *)(this + 992) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60D810 sub_60D810
// ------------------------------------------------------------
int /*thiscall*/ sub_60D810(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint8_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x60D840 sub_60D840
// ------------------------------------------------------------
// 冰针参数插值：sub_4049C0 ——【推断：波次间冰针尺寸/间隔插值】。
int /*thiscall*/ sub_60D840(float *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int pThis_180; // edi
  int v7; // edi
  float v9; // [esp+14h] [ebp-24h]
  float v10; // [esp+14h] [ebp-24h]
  float pThis_1803; // [esp+18h] [ebp-20h]
  float pThis_1805; // [esp+18h] [ebp-20h]
  int pThis_1802; // [esp+30h] [ebp-8h]
  int pThis_1804; // [esp+48h] [ebp+10h]
  float v15; // [esp+48h] [ebp+10h]

  pThis_180 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v7 = pThis_180 - 1;
  pThis_1803 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  v9 = (float)pThis_1802;
  *(this + 181) = sub_4049C0(v9, pThis_1803, nArg2 - 1, v7);
  if ( nArg4 == 1 )
  {
    pThis_1804 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
    pThis_1805 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 4);
    v10 = (float)pThis_1804;
    v15 = sub_4049C0(v10, pThis_1805, nArg2 - 1, v7);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *((uint32_t *)this + 249) = (uint64_t)((double)(rand() % 2000) + v15 - 1000.0);
  }
  else
  {
    *(this + 249) = 8.670878e-37;
  }
  *((uint8_t *)this + 984) = 0;
  *((uint32_t *)this + 250) = nArg5;
  *((uint32_t *)this + 251) = nArg3;
  return nArg3;
}



// ------------------------------------------------------------
// 0x60D940 sub_60D940
// ------------------------------------------------------------
int /*thiscall*/ sub_60D940(uint32_t *this)
{
  uint32_t *pThis_F3; // esi
  int i; // edi
  int result; // eax

  pThis_F3 = this + 243;
  for ( i = 3; i != 0; --i )
  {
    if ( *pThis_F3 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_F3)(*pThis_F3, 1);
    *pThis_F3++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x60D970 CNEarthFire__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNEarthFire__vmt12C(uint32_t *this, int nArg2)
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
}



// ------------------------------------------------------------
// 0x60D9A0 CNEarthFire__vmt14C
// ------------------------------------------------------------
// CNEarthFire 主循环槽（vmt14C）：字符串证据「EARTHFIRE_LOOP」（音效 TAG —— 地火循环）+
// 「PassiveObject/Common/Particle/FireMissileParticleFloor.ptl」（地面火粒子，复用火弹地面层）。
// sub_428F30 发射器 + sub_699000 —— 地面持续燃烧带（地火机关）。
void /*thiscall*/ CNEarthFire__vmt14C(uint32_t *this)
{
  int fld_e250; // eax
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  int fld_e243; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int pThis_10; // eax
  int v10; // edx
  void *fld_e29; // ecx
  uint8_t v12[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  void *pMem2; // [esp+14h] [ebp-10h]
  int v15; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 984) == 0 )
  {
    fld_e250 = *(this + 250);
    if ( fld_e250 != 0 )
    {
      if ( fld_e250 != 1 )
      {
LABEL_10:
        fld_e243 = *(uint32_t *)*(this + 243);
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
        v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v6);
        v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v7);
        (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e243 + 40))(*(this + 243), v8);
        pThis_10 = sub_699000((int)(this + 16));  // 【clock_now(clk)】
        v10 = *this;
        *(this + 247) = pThis_10;
        *(this + 248) = *(this + 251);
        *((uint8_t *)this + 984) = 1;
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, uint32_t, uint32_t))(v10 + 212))(
          this,
          "EARTHFIRE_LOOP",
          0,
          0,
          0);
        goto LABEL_11;
      }
      pMem = operator new(0x12Cu);
      pMem2 = pMem;
      v15 = 1;
    }
    else
    {
      pMem = operator new(0x12Cu);
      pMem2 = pMem;
      v15 = 0;
    }
    if ( pMem != nullptr )
      v4 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/FireMissileParticleFloor.ptl", (int)this);
    else
      v4 = nullptr;
    v15 = -1;
    *(this + 243) = v4;
    goto LABEL_10;
  }
LABEL_11:
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v12);
  fld_e29 = (void *)*(this + 29);
  v15 = 2;
  sub_4600B0(fld_e29, 2, 0, (int)v12);
  if ( sub_699000((int)(this + 9)) > *(this + 249) + 100 && *((uint8_t *)this + 264) == 0 )  // 【clock_now(clk)】
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x60DB10 sub_60DB10
// ------------------------------------------------------------
void /*thiscall*/ sub_60DB10(uint32_t *this)
{
  *(this + 245) = 0;
}



// ------------------------------------------------------------
// 0x60DB20 CNShootingStar__vmt14C
// ------------------------------------------------------------
// CNShootingStar 主循环槽（vmt14C）：sub_424120（震屏）+ sub_4600B0 ——
// 流星（ShootingStar）坠落演出；出生粒子见 0x60DC60（ShootingStarFire.ptl + SSTAR_DROP）。
void /*thiscall*/ CNShootingStar__vmt14C(int *this)
{
  int fld_e245; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  void *fld_e29; // ecx
  int fld_e244; // ebx
  int v8; // edi
  int v9; // eax
  char v10[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v12; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) <= 30 )
  {
    if ( *((uint8_t *)this + 264) == 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
      {
        fld_e244 = *(this + 244);
        if ( fld_e244 < 0 )
          fld_e244 = *(this + 243);
        v8 = *this;
        v9 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 128))(this, 4, 0, 0, 0);
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(v8 + 580))(
          this,
          *(this + 71) + 1,
          fld_e244,
          0,
          0,
          0,
          0,
          -v9);
      }
      sub_424120(*(uint32_t **)(*(this + 29) + 132), 8, 500);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    }
  }
  else
  {
    fld_e245 = *(uint32_t *)*(this + 245);
    v3 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v3);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v4);
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e245 + 40))(*(this + 245), v5);
    (*(void (/*thiscall*/ **)(uint32_t, char *))(*(uint32_t *)*(this + 245) + 92))(*(this + 245), v10);
    fld_e29 = (void *)*(this + 29);
    v12 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v10);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x60DC60 sub_60DC60
// ------------------------------------------------------------
// 流星出生粒子：字符串证据「PassiveObject/Common/Particle/ShootingStarFire.ptl」+「SSTAR_DROP」（音效 TAG）+
// sub_4049C0 lerp —— 流星火尾的出场插值。
int /*thiscall*/ sub_60DC60(float *this, uint32_t *uArg2)
{
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  int pThis_180; // edi
  float v7; // [esp+30h] [ebp-2Ch]
  float pThis_1802; // [esp+34h] [ebp-28h]
  void *Block; // [esp+48h] [ebp-14h]

  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    -1,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    v4 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/ShootingStarFire.ptl", (int)this);
  else
    v4 = nullptr;
  *((uint32_t *)this + 245) = v4;
  (*(void (/*thiscall*/ **)(uint32_t *, float *))(*v4 + 112))(v4, this);
  (*(void (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)this + 245) + 12))(*((uint32_t *)this + 245), 500);
  pThis_180 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  Block = (void *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  pThis_1802 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  *((uint32_t *)this + 244) = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  v7 = (float)(int)Block;
  *(this + 181) = sub_4049C0(v7, pThis_1802, (int)uArg2 - 1, pThis_180 - 1);
  *((uint32_t *)this + 243) = uArg2;
  return sub_4015C0("SSTAR_DROP", 0xAu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x60DD80 sub_60DD80
// ------------------------------------------------------------
int /*thiscall*/ sub_60DD80(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 984) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60DD90 sub_60DD90
// ------------------------------------------------------------
int /*thiscall*/ sub_60DD90(uint32_t *this)
{
  uint32_t *pThis_F7; // esi
  int i; // edi
  int result; // eax

  pThis_F7 = this + 247;
  for ( i = 3; i != 0; --i )
  {
    if ( *pThis_F7 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_F7)(*pThis_F7, 1);
    *pThis_F7++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x60DDC0 CNShootingStarExp__vmt14C
// ------------------------------------------------------------
// CNShootingStarExp 主循环槽（vmt14C）：sub_432FA0（UDP 广播）+ sub_4600B0 ——
// 流星爆的落点广播与爆炸演出；粒子三件套见 0x60DFA0。
int /*thiscall*/ CNShootingStarExp__vmt14C(char *this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // edi
  int pThis_98; // eax
  int nRand2; // eax
  int **pThis_3DC; // edi
  int v8; // ebx
  int pThis_802; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  void *pThis_1D; // ecx
  bool v13; // zf
  int result; // eax
  int nRand; // [esp-8h] [ebp-34h]
  int pThis_80; // [esp-4h] [ebp-30h]
  char v17[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v19; // [esp+14h] [ebp-18h]
  int v20; // [esp+18h] [ebp-14h]
  int i; // [esp+1Ch] [ebp-10h]
  int v22; // [esp+28h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 972) == 0 )
  {
    v2 = *(uint32_t *)this;
    *(this + 972) = 1;
    if ( (*(uint8_t (/*thiscall*/ **)(char *))(v2 + 308))(this) != 0 && *((uint32_t *)this + 246) != 1 )
    {
      sub_432FA0();
      for ( i = 0; i < rand() % 4 + 2; ++i )
      {
        v3 = 40003;
        if ( *((uint32_t *)this + 71) == 30067 )
          v3 = 30091;
        if ( *((int *)this + 245) > 0 )
        {
          v4 = *(uint32_t *)this;
          pThis_98 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(this, 4, 0, 0, 0);
          pThis_80 = -(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 128))(this, pThis_98);
          nRand = rand() % 100 - 50;
          nRand2 = rand();
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int, int, int))(v4 + 580))(
            this,
            v3,
            *((uint32_t *)this + 244),
            0,
            nRand2 % 200 - 100,
            nRand,
            pThis_80);
        }
      }
    }
  }
  pThis_3DC = (int **)(this + 988);
  i = 3;
  do
  {
    v8 = **pThis_3DC;
    pThis_802 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);
    pThis_7C = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, pThis_802);
    pThis_78 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 120))(this, pThis_7C);
    (*(void (/*thiscall*/ **)(int *, int))(v8 + 40))(*pThis_3DC, pThis_78);
    (*(void (/*thiscall*/ **)(int *, char *))(**pThis_3DC + 92))(*pThis_3DC, v17);
    pThis_1D = *((void **)this + 29);
    v22 = 0;
    sub_4600B0(pThis_1D, 2, 0, (int)v17);
    v22 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++pThis_3DC;
    result = i - 1;
    v13 = i == 1;
    Block = nullptr;
    v19 = 0;
    v20 = 0;
    --i;
  }
  while ( !v13 );
  if ( *(uint8_t *)(*((uint32_t *)this + 30) + 170) != 0 && *(this + 264) == 0 )
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x60DFA0 sub_60DFA0
// ------------------------------------------------------------
// 流星爆粒子三件套：字符串证据「PassiveObject/Common/Particle/ShootingStarExpSmoke.ptl |
// ShootingStarExp.ptl | ShootingStarExpEtc.ptl」+「SSTAR_HIT」（音效 TAG）+ sub_4049C0 lerp ——
// 烟/爆心/飞散三层粒子（P36 资源生态直证）。
int /*thiscall*/ sub_60DFA0(float *this, int nArg2, int nArg3)
{
  uint32_t *pMem; // eax
  uint32_t *v5; // eax
  uint32_t *pMem2; // eax
  uint32_t *v7; // eax
  uint32_t *pMem3; // eax
  uint32_t *v9; // eax
  int pThis_180; // edi
  float v12; // [esp+10h] [ebp-2Ch]
  float v13; // [esp+14h] [ebp-28h]
  void *Block; // [esp+28h] [ebp-14h]
  int pThis_1802; // [esp+2Ch] [ebp-10h]

  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    v5 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/ShootingStarExpSmoke.ptl", (int)this);
  else
    v5 = nullptr;
  *((uint32_t *)this + 247) = v5;
  pMem2 = operator new(0x12Cu);
  if ( pMem2 != nullptr )
    v7 = sub_428F30(pMem2, (int)"PassiveObject/Common/Particle/ShootingStarExp.ptl", (int)this);
  else
    v7 = nullptr;
  *((uint32_t *)this + 248) = v7;
  pMem3 = operator new(0x12Cu);
  if ( pMem3 != nullptr )
    v9 = sub_428F30(pMem3, (int)"PassiveObject/Common/Particle/ShootingStarExpEtc.ptl", (int)this);
  else
    v9 = nullptr;
  *((uint32_t *)this + 249) = v9;
  pThis_180 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  Block = (void *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  *((uint32_t *)this + 245) = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  v13 = (float)pThis_1802;
  v12 = (float)(int)Block;
  *(this + 181) = sub_4049C0(v12, v13, nArg2 - 1, pThis_180 - 1);
  *((uint32_t *)this + 246) = nArg3;
  *((uint8_t *)this + 972) = 0;
  *((uint32_t *)this + 244) = nArg2;
  return sub_4015C0("SSTAR_HIT", 9u);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x60E100 sub_60E100
// ------------------------------------------------------------
int /*thiscall*/ sub_60E100(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = -1;
  *(uint8_t *)(this + 980) = 0;
  *(uint8_t *)(this + 981) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60E120 CNBoomerang__vmt14C
// ------------------------------------------------------------
// CNBoomerang 主循环槽（vmt14C）：字符串证据「BOOMERANG_SHOOT_LOOP | BOOMERANG_BACK_LOOP」
// （去程/回程双循环音效 TAG —— 掷出与折返各挂一个循环音）。sub_4910A0 —— 回旋镖往返的音画同步。
char /*thiscall*/ CNBoomerang__vmt14C(uint32_t *this)
{
  int fld_e30; // eax
  int v3; // ecx
  int v4; // eax
  int fld_e173; // ecx
  int fld_e28; // eax
  char result; // al
  int v8; // [esp+4h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  fld_e30 = *(this + 30);
  v3 = *(uint32_t *)(fld_e30 + 212);
  if ( v3 != 0 )
    v4 = sub_4910A0(v3);
  else
    v4 = *(uint32_t *)(fld_e30 + 32);
  if ( v4 >= *(this + 244) + *(this + 243) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
    *(this + 243) += *(this + 244);
  }
  fld_e173 = *(this + 173);
  if ( fld_e173 != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e173 + 124))(fld_e173);
    fld_e28 = *(this + 28);
    *(uint8_t *)(fld_e28 + 124) = 1;
    *(float *)(fld_e28 + 8) = (float)v8;
  }
  if ( *((uint8_t *)this + 980) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, uint32_t, uint32_t))(*this + 212))(
      this,
      "BOOMERANG_SHOOT_LOOP",
      0,
      0,
      0);
    *((uint8_t *)this + 980) = 1;
  }
  result = *((uint8_t *)this + 981);
  if ( result == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
    result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
               this,
               "BOOMERANG_BACK_LOOP",
               1,
               0,
               0);
    *((uint8_t *)this + 981) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x60E1F0 CNBoomerang__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNBoomerang__vmt12C(int this, int nArg2)
{
  CNRDPassiveObject__vmt12C((uint32_t *)this, nArg2);
  if ( nArg2 == this )
  {
    if ( *(uint8_t *)(this + 981) != 0 )
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 1);
    else
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 216))(this, 0);
  }
}



// ------------------------------------------------------------
// 0x60E230 sub_60E230
// ------------------------------------------------------------
int /*thiscall*/ sub_60E230(int **this)
{
  int *fld_e87; // edx
  int result; // eax

  fld_e87 = *(this + 87);
  if ( fld_e87 != nullptr )
  {
    result = *(this + 88) - fld_e87;
    if ( result != 0 )
    {
      result = *fld_e87;
      *(this + 244) = (int *)*fld_e87;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60E260 sub_60E260
// ------------------------------------------------------------
int /*thiscall*/ sub_60E260(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint8_t *)(this + 980) = 0;
  *(uint8_t *)(this + 981) = 1;
  return 0;
}



// ------------------------------------------------------------
// 0x60E280 CNBouncer__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNBouncer__vmt14C(void *this)
{
  int pThis_1E; // eax

  CNRDPassiveObject__vmt14C((int)this);
  LOBYTE(pThis_1E) = *((uint8_t *)this + 980);
  if ( (uint8_t)pThis_1E != 0 )
  {
    pThis_1E = *((uint32_t *)this + 30);
    if ( *(uint8_t *)(pThis_1E + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, *((uint32_t *)this + 34));
      LOBYTE(pThis_1E) = sub_4926A0(*((uint32_t *)this + 30));
      *((uint8_t *)this + 980) = 0;
    }
  }
  return pThis_1E;
}



// ------------------------------------------------------------
// 0x60E2D0 sub_60E2D0
// ------------------------------------------------------------
// 弹跳体参数装载（93 行）：sub_423A20（UDP 广播）+ sub_432FA0 + sub_4926A0（定时器复位）+ dword_796E50 ——
// 【推断：刺猬弹（HEDGEHOG，见 0x60E790）的弹跳参数与路径装载】。
int /*usercall*/ sub_60E2D0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>)
{
  int result; // eax
  int v5; // eax
  const void *v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int nRand; // edx
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // esi
  int v15; // esi
  int v16; // eax
  int v17; // esi
  int v18; // eax
  int v19; // [esp+4h] [ebp-70h] BYREF
  int v20; // [esp+8h] [ebp-6Ch] BYREF
  uint32_t v21[26]; // [esp+Ch] [ebp-68h] BYREF

  v21[25] = dword_796E50;
  (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 352))(pArg1);
  if ( *((uint8_t *)pArg1 + 981) == 1 && *((uint8_t *)pArg1 + 980) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)pArg1[36]);
    *((uint8_t *)pArg1 + 980) = 1;
  }
  sub_4926A0(pArg1[30]);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 88))(pArg1);
    if ( (uint8_t)result != 0 )
    {
      sub_432FA0();
      sub_423A20((int)v21);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 60))(pArg1, nArg2);
      v6 = (const void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v5 + 104) + 16))(*(uint32_t *)(v5 + 104));
      v7 = *pArg1;
      qmemcpy(v21, v6, 0x62u);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 60))(pArg1);
      v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v8 + 104) + 44))(*(uint32_t *)(v8 + 104));
      *(uint32_t *)((char *)&v21[21] + 1) += -50 - v9;
      if ( *(uint32_t *)((char *)&v21[21] + 1) > 0 )
      {
        nRand = (rand() % 181 + v21[18] + 90) % 360;
        v11 = pArg1[243];
        v21[18] = nRand;
        if ( v11 + *(uint32_t *)((char *)&v21[3] + 3) <= pArg1[244] )
        {
          *(uint32_t *)((char *)&v21[3] + 3) += v11;
          *(uint32_t *)((char *)&v21[4] + 3) += v11;
        }
        v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg3);
        v13 = *pArg1;
        v19 = v12;
        v20 = (*(int (/*thiscall*/ **)(uint32_t *))(v13 + 124))(pArg1);
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*pArg1 + 136))(pArg1, v19, v20, 0) != 0
          || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *, int *, int *, int, int, int, int, int))(*pArg1 + 140))(
                                pArg1,
                                &v19,
                                &v20,
                                v19,
                                v20,
                                100,
                                1,
                                1)) != 0 )
        {
          v21[0] = v19;
          v21[1] = v20;
          v21[2] = v14;
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
          v15 = *(uint32_t *)dword_8F8520;
          v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 48))(pArg1);
          (*(void (/*thiscall*/ **)(int, int))(v15 + 36))(dword_8F8520, v16);
          v17 = *(uint32_t *)dword_8F8520;
          v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);
          (*(void (/*thiscall*/ **)(int, int))(v17 + 36))(dword_8F8520, v18);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
          (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v21, 98);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
          return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        }
      }
      else
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60E4E0 CNBouncerLooseSerimalion__vmt14C
// ------------------------------------------------------------
// CNBouncerLooseSerimalion 主循环槽（vmt14C）：sub_4926A0 —— 弹跳计时复位。
// 【推断：LooseSerimalion = 松脱弹跳体变体】。
char /*thiscall*/ CNBouncerLooseSerimalion__vmt14C(void *this)
{
  int pThis_1E; // eax

  CNRDPassiveObject__vmt14C((int)this);
  LOBYTE(pThis_1E) = *((uint8_t *)this + 980);
  if ( (uint8_t)pThis_1E != 0 )
  {
    pThis_1E = *((uint32_t *)this + 30);
    if ( *(uint8_t *)(pThis_1E + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, *((uint32_t *)this + 34));
      LOBYTE(pThis_1E) = sub_4926A0(*((uint32_t *)this + 30));
      *((uint8_t *)this + 980) = 0;
    }
  }
  if ( *((uint8_t *)this + 984) == 1 )
  {
    LOBYTE(pThis_1E) = (*(int (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                   this,
                   100,
                   *(uint32_t *)(*((uint32_t *)this + 36) + 4),
                   0,
                   0,
                   0,
                   0);
    *((uint8_t *)this + 984) = 0;
  }
  return pThis_1E;
}



// ------------------------------------------------------------
// 0x60E560 CNBouncer__vmt1F4
// ------------------------------------------------------------
int /*userpurge*/ CNBouncer__vmt1F4@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>, uint32_t *uArg3, float *pArg4, char pszArg5)
{
  sub_60E2D0(pDwArg1, nArg2, (int)pDwArg1);
  return CNRDPassiveObject__vmt1F4(pDwArg1, uArg3, pArg4, pszArg5);
}



// ------------------------------------------------------------
// 0x60E590 CNBouncer__vmt214
// ------------------------------------------------------------
char /*userpurge*/ CNBouncer__vmt214@<al>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4, int nArg5)
{
  sub_60E2D0(pArg1, nArg2, (int)pArg1);
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "HEDGEHOG_BUMP", -1, 0, 0);
  return CNRDPassiveObject__vmt214(pArg1, nArg3, nArg4, nArg5);
}



// ------------------------------------------------------------
// 0x60E5D0 sub_60E5D0
// ------------------------------------------------------------
int /*thiscall*/ sub_60E5D0(int this)
{
  uint32_t *fld_15C; // edx
  int fld_15C2; // edx

  *(uint8_t *)(this + 700) = 0;
  *(uint8_t *)(this + 701) = 1;
  fld_15C = *(uint32_t **)(this + 348);
  if ( fld_15C != nullptr && (*(uint32_t *)(this + 352) - (int)fld_15C) >> 2 != 0 )
    *(uint32_t *)(this + 972) = *fld_15C;
  fld_15C2 = *(uint32_t *)(this + 348);
  if ( fld_15C2 != 0 && (unsigned int)((*(uint32_t *)(this + 352) - fld_15C2) >> 2) > 1 )
    *(uint32_t *)(this + 976) = *(uint32_t *)(fld_15C2 + 4);
  return sub_4015C0("HEDGEHOG_SHOOT", 0xEu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x60E640 CNBouncerLooseSerimalion__vmt12C
// ------------------------------------------------------------
// CNBouncerLooseSerimalion 消亡联动槽（vmt12C）：sub_4600B0（演播层）+ sub_4E77D0 +
// dword_8F82A8/8F82AC（弹跳体池化槽）——弹跳体消失演出。
void /*thiscall*/ CNBouncerLooseSerimalion__vmt12C(uint32_t *this, int nArg2)
{
  int pObj2; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int pObj; // edi
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  uint8_t v17[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  uint8_t v19[4]; // [esp+18h] [ebp-1Ch] BYREF
  void *v20; // [esp+1Ch] [ebp-18h]
  int v21; // [esp+30h] [ebp-4h]

  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
  {
    pObj2 = dword_8F82A8;
    v4 = *(uint32_t *)dword_8F82A8;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v5);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v6);
    (*(void (/*thiscall*/ **)(int, int))(v4 + 40))(pObj2, v7);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);
    (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj2 + 92))(pObj2, v19);
    v8 = *(uint32_t *)dword_8F8520;
    v21 = 0;
    v9 = (*(int (/*thiscall*/ **)(int))(v8 + 120))(dword_8F8520);
    sub_4600B0(*(void **)(v9 + 104), 2, 0, (int)v19);
    pObj = dword_8F82AC;
    v11 = *(uint32_t *)dword_8F82AC;
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v12);
    v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v13);
    (*(void (/*thiscall*/ **)(int, int))(v11 + 40))(pObj, v14);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);
    v15 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj + 92))(pObj, v17);
    LOBYTE(v21) = 1;
    sub_4E77D0((int)v19, v15);
    LOBYTE(v21) = 0;
    if ( Block != nullptr )
      j__free(Block);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    sub_4600B0(*(void **)(v16 + 104), 2, 0, (int)v19);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 4));
    if ( v20 != nullptr )
      j__free(v20);
  }
}



// ------------------------------------------------------------
// 0x60E790 CNBouncerLooseSerimalion__vmt214
// ------------------------------------------------------------
// CNBouncerLooseSerimalion 攻击判定槽（vmt214）：字符串证据「HEDGEHOG_BUMP」（音效 TAG —— 刺猬碰撞）+
// dword_8F8280/8F8284（研究 20 P33 定案的池化火花槽 8F8280/84 = 钝器双层火花）——
// 弹跳体碰撞时复用池化火花演出（零分配，P33 池化机制直证）。
void /*userpurge*/ CNBouncerLooseSerimalion__vmt214(int pArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4, int nArg5)
{
  int pObj; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  void *v11; // ecx
  int pObj2; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  uint8_t v18[4]; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+10h] [ebp-28h]
  uint8_t v20[4]; // [esp+1Ch] [ebp-1Ch] BYREF
  void *v21; // [esp+20h] [ebp-18h]
  int v22; // [esp+34h] [ebp-4h]

  sub_60E2D0((uint32_t *)pArg1, nArg2, pArg1);
  (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, "HEDGEHOG_BUMP", -1, 0, 0);
  CNRDPassiveObject__vmt214((uint32_t *)pArg1, nArg3, nArg4, nArg5);
  pObj = dword_8F8280;
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8280 + 12))(dword_8F8280, 0);
  v7 = *(uint32_t *)pObj;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);
  v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v8);
  v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v9);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 40))(pObj, v10);
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj) + 84) = 0;
  (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj + 92))(pObj, v20);
  v11 = *(void **)(pArg1 + 116);
  v22 = 0;
  sub_4600B0(v11, 2, 0, (int)v20);
  pObj2 = dword_8F8284;
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8284 + 12))(dword_8F8284, 0);
  v13 = *(uint32_t *)pObj2;
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);
  v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v14);
  v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v15);
  (*(void (/*thiscall*/ **)(int, int))(v13 + 40))(pObj2, v16);
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 28))(pObj2) + 84) = 0;
  v17 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj2 + 92))(pObj2, v18);
  LOBYTE(v22) = 1;
  sub_4E77D0((int)v20, v17);
  LOBYTE(v22) = 0;
  if ( Block != nullptr )
    j__free(Block);
  sub_4600B0(*(void **)(pArg1 + 116), 2, 0, (int)v20);
  if ( v21 != nullptr )
    j__free(v21);
}



// ------------------------------------------------------------
// 0x60E8D0 sub_60E8D0
// ------------------------------------------------------------
int /*thiscall*/ sub_60E8D0(void **this)
{
  *this = &vftbl_CNThrowItemDestroyable;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x60E8E0 sub_60E8E0
// ------------------------------------------------------------
void /*thiscall*/ sub_60E8E0(uint32_t *this)
{
  *(this + 243) = 0xFFFF;
  *(this + 244) = 0;
}



// ------------------------------------------------------------
// 0x60E900 CNCreateOnDestroyObject__vmt12C
// ------------------------------------------------------------
// CNCreateOnDestroyObject 消亡联动槽（vmt12C）：自身消亡时生成后继 PO 的包装器（sub_4E4A50 发包收尾）——
// 【新发现】『死亡衍生』机制的基类：爆炸物→残留火海等链式生成的设计。
void /*thiscall*/ CNCreateOnDestroyObject__vmt12C(uint32_t *this, int nArg2)
{
  int v3; // ebx
  uint32_t *fld_e173; // edi
  int v5; // eax
  int v6; // [esp-1Ch] [ebp-24h]
  int v7; // [esp-14h] [ebp-1Ch]

  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this
    && *(this + 243) != 0xFFFF
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) <= 0 )
      v3 = 0;
    else
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    fld_e173 = (uint32_t *)*(this + 173);
    if ( fld_e173 == nullptr )
      fld_e173 = this;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    sub_4E4A50(fld_e173, *(this + 243), *(this + 244), v5, v6, v3, v7, 0, 0, 0);
  }
}



// ------------------------------------------------------------
// 0x60E9A0 sub_60E9A0
// ------------------------------------------------------------
// 死亡衍生辅助（27 行）：后继 PO 的参数转抄【推断】。
unsigned int /*thiscall*/ sub_60E9A0(unsigned int **this)
{
  unsigned int *fld_e87; // edx
  unsigned int result; // eax
  int fld_e872; // edx

  fld_e87 = *(this + 87);
  if ( fld_e87 != nullptr )
  {
    result = *(this + 88) - fld_e87;
    if ( result != 0 )
    {
      result = *fld_e87;
      *(this + 243) = (unsigned int *)*fld_e87;
    }
  }
  fld_e872 = (int)*(this + 87);
  if ( fld_e872 != 0 )
  {
    result = ((int)*(this + 88) - fld_e872) >> 2;
    if ( result > 1 )
    {
      result = (unsigned int)(*(this + 87) + 1);
      *(this + 244) = *(unsigned int **)(fld_e872 + 4);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60E9F0 CNSunkenRock__vmt144
// ------------------------------------------------------------
char /*thiscall*/ CNSunkenRock__vmt144(void *this, char pszArg2, int nArg3, int nArg4, float fArg5)
{
  int pThis_C8; // eax
  int pThis_2AC; // eax
  int dword_79C0B02; // [esp-20h] [ebp-24h]

  LOBYTE(pThis_C8) = pszArg2;
  if ( pszArg2 != 0 )
  {
    pThis_2AC = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 684))(this);
    pThis_C8 = __RTDynamicCast(pThis_2AC, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMasterDogri `RTTI Type Descriptor', 0);
    if ( pThis_C8 != 0 )
    {
      pThis_C8 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 200))(this);
      if ( pThis_C8 != 0 )
      {
        dword_79C0B02 = dword_79C0B0;
        (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 200))(this);
        LOBYTE(pThis_C8) = sub_491DE0(dword_79C0B02, nArg3, nArg4, fArg5, 2, 1, 255, 1358954495);
      }
    }
  }
  return pThis_C8;
}



// ------------------------------------------------------------
// 0x60EA70 CNSunkenRock__vmt14C
// ------------------------------------------------------------
// CNSunkenRock 主循环槽（vmt14C，101 行）：字符串证据「DOLL_STONE | TRAP_STONE_BREAK」（音效 TAG ——
// 人偶石/陷阱石破裂）。sub_4E4A50（动作包）——沉陷岩石陷阱的破裂状态机。
char /*thiscall*/ CNSunkenRock__vmt14C(int *this)
{
  int v2; // eax
  int fld_e139; // eax
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int i; // edi
  int v11; // eax
  int v13; // [esp-20h] [ebp-24h]
  int v14; // [esp-1Ch] [ebp-20h]
  int v15; // [esp-18h] [ebp-1Ch]
  int v16; // [esp-14h] [ebp-18h]

  if ( *((uint8_t *)this + 973) == 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
    if ( __RTDynamicCast(v2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSteelMaster `RTTI Type Descriptor', 0) != 0 )
    {
      fld_e139 = *(this + 139);
    }
    else
    {
      v4 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
      if ( __RTDynamicCast(v4, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNClayMaster `RTTI Type Descriptor', 0) != 0 )
      {
        fld_e139 = *(this + 139) + 152;
      }
      else
      {
        v5 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
        if ( __RTDynamicCast(
               v5,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &CNMasterDogri `RTTI Type Descriptor',
               0) == 0 )
        {
LABEL_9:
          *((uint8_t *)this + 973) = 1;
          goto LABEL_10;
        }
        fld_e139 = *(this + 139) + 304;
      }
    }
    (*(void (/*stdcall*/ **)(int))(*this + 344))(fld_e139);
    goto LABEL_9;
  }
LABEL_10:
  CNRDPassiveObject__vmt14C((int)this);
  if ( *(int *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) >= 7 && *((uint8_t *)this + 972) == 0 )
  {
    v6 = *this;
    *((uint8_t *)this + 972) = 1;
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v6 + 212))(this, "DOLL_STONE", -1, 0, 0);
  }
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
  if ( *(uint8_t *)(v7 + 170) != 0 )
  {
    LOBYTE(v7) = *((uint8_t *)this + 264);
    if ( (uint8_t)v7 == 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 684))(this) != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
        v9 = __RTDynamicCast(
               v8,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &CNMasterDogri `RTTI Type Descriptor',
               0);
        if ( v9 != 0
          && *(uint32_t *)(v9 + 7772) == 3
          && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
        {
          for ( i = 30; i < 150; i += 30 )
          {
            v16 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            v15 = i + (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
            v14 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
            v13 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
            v11 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
            sub_4E4A50(v11, 30056, 0, v13, v14, v15, v16, 0, 0, 0);
          }
        }
      }
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "TRAP_STONE_BREAK",
        -1,
        0,
        0);
      LOBYTE(v7) = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
      if ( (uint8_t)v7 != 0 )
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    }
  }
  return v7;
}



// ------------------------------------------------------------
// 0x60EC70 sub_60EC70
// ------------------------------------------------------------
// 人偶石就绪辅助：字符串证据「DOLL_STONE_READY」（音效 TAG）+ sub_4049C0 lerp —— 石块升起动画参数。
int /*thiscall*/ sub_60EC70(uint8_t *this, int nArg2)
{
  int pThis_180; // edi
  double v4; // st7
  uint32_t *pThis_24; // eax
  int result; // eax
  float v7; // [esp+Ch] [ebp-20h]
  float pThis_1803; // [esp+10h] [ebp-1Ch]
  int pThis_1802; // [esp+24h] [ebp-8h]

  pThis_180 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  pThis_1802 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 1);
  pThis_1803 = (float)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 2);
  v7 = (float)pThis_1802;
  v4 = sub_4049C0(v7, pThis_1803, nArg2 - 1, pThis_180 - 1);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  pThis_24 = *((uint32_t **)this + 36);
  *((float *)this + 181) = v4;
  (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    -101,
    *pThis_24,
    0,
    0,
    0,
    0);
  result = sub_4015C0("DOLL_STONE_READY", 0x10u);  // 【std::string构造赋值】
  *(this + 972) = 0;
  *(this + 973) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60ED10 CNRedRock__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNRedRock__vmt12C(uint32_t *this, int nArg2)
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 37111);
}



// ------------------------------------------------------------
// 0x60ED40 CNRedRock__vmt14C
// ------------------------------------------------------------
// CNRedRock 主循环槽（vmt14C）：字符串证据「FIRELOCK_ROLLING_LOOP」（音效 TAG —— 火轮滚动循环）+
// dword_8F8520 —— 红石（火轮）滚动机关的循环维持。
char /*thiscall*/ CNRedRock__vmt14C(uint8_t *this)
{
  int pThis_80; // eax
  int pThis_3C; // eax
  uint32_t *pThis_78; // edi
  int v5; // ebx
  int pThis_30; // eax
  int v7; // ebx
  int pThis_34; // eax
  int v9; // eax

  CNRDPassiveObject__vmt14C((int)this);
  pThis_80 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
  if ( pThis_80 <= 0 )
  {
    LOBYTE(pThis_80) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( (uint8_t)pThis_80 != 0 )
    {
      LOBYTE(pThis_80) = *(this + 972);
      if ( (uint8_t)pThis_80 == 0 )
      {
        pThis_3C = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 60))(this);
        pThis_78 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pThis_3C + 104) + 16))(*(uint32_t *)(pThis_3C + 104));
        *pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this);
        pThis_78[1] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this);
        pThis_78[2] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
        pThis_78[18] = 0;
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
        v5 = *(uint32_t *)dword_8F8520;
        pThis_30 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 48))(this);
        (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_30);
        v7 = *(uint32_t *)dword_8F8520;
        pThis_34 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 52))(this);
        (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, pThis_34);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, pThis_78, 98);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        v9 = *(uint32_t *)this;
        *(this + 972) = 1;
        LOBYTE(pThis_80) = (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(v9 + 212))(
                       this,
                       "FIRELOCK_ROLLING_LOOP",
                       37111,
                       0,
                       0);
      }
    }
  }
  return pThis_80;
}



// ------------------------------------------------------------
// 0x60EE50 CNRedRock__vmt1F4
// ------------------------------------------------------------
// CNRedRock 命中表现槽（vmt1F4）：sub_4600B0 —— 火轮碾压目标的演出。
int /*thiscall*/ CNRedRock__vmt1F4(int *this, uint32_t *uArg2, float *pArg3, char pszArg4)
{
  int fld_e244; // ecx
  int fld_e2442; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *fld_e29; // ecx
  void *Block2; // eax
  bool v12; // zf
  uint8_t v14[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v16; // [esp+10h] [ebp-14h]
  int v17; // [esp+14h] [ebp-10h]
  int v18; // [esp+20h] [ebp-4h]

  fld_e244 = *(this + 244);
  if ( fld_e244 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e244 + 12))(fld_e244, 0);
    fld_e2442 = *(uint32_t *)*(this + 244);
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v7);
    v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2442 + 40))(*(this + 244), v9);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 244) + 92))(*(this + 244), v14);
    fld_e29 = (void *)*(this + 29);
    v18 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v14);
    Block2 = Block;
    v12 = Block == nullptr;
    *(this + 244) = 0;
    v18 = -1;
    if ( !v12 )
      j__free(Block2);
    Block = nullptr;
    v16 = 0;
    v17 = 0;
  }
  return CNRDPassiveObject__vmt1F4(this, uArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x60EF20 sub_60EF20
// ------------------------------------------------------------
// 火轮投掷辅助：字符串证据「THROW_FIRELOCK」（音效 TAG）+ sub_4049C0 lerp —— 投掷初速参数。
int /*thiscall*/ sub_60EF20(float *this, int nArg2)
{
  int pThis_180; // edi
  double v4; // st7
  uint32_t *pThis_24; // eax
  float v7; // [esp+Ch] [ebp-20h]
  float pThis_1803; // [esp+10h] [ebp-1Ch]
  int pThis_1802; // [esp+24h] [ebp-8h]

  pThis_180 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  pThis_1803 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  v7 = (float)pThis_1802;
  v4 = sub_4049C0(v7, pThis_1803, nArg2 - 1, pThis_180 - 1);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  pThis_24 = *((uint32_t **)this + 36);
  *(this + 181) = v4;
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    1,
    *pThis_24,
    0,
    0,
    0,
    0);
  *(this + 244) = *(this + 219);
  *((uint8_t *)this + 972) = 0;
  *(this + 219) = 0.0;
  return sub_4015C0("THROW_FIRELOCK", 0xEu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x60EFD0 sub_60EFD0
// ------------------------------------------------------------
int /*stdcall*/ sub_60EFD0(int nArg1)
{
  return sub_4015C0("CLAY_SHOOT", 0xAu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x60EFF0 CNDollMasterBubble__vmt1F4
// ------------------------------------------------------------
// CNDollMasterBubble 命中表现槽（vmt1F4）：字符串证据「CLAY_HIT」（音效 TAG —— 黏土命中）。
// sub_44B6C0/44E0D0（帧事件）+ sub_45FE80（演播层）——人偶师黏土泡泡被击破的演出。
int /*thiscall*/ CNDollMasterBubble__vmt1F4(int *this, uint32_t *uArg2, float *pArg3, char pszArg4)
{
  int v5; // edi
  int v6; // ebx
  const char *fld_e178; // eax
  char *v8; // eax
  char *v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax

  v5 = sub_42FCB0(228);
  v6 = 0;
  if ( v5 != 0 )
  {
    fld_e178 = (const char *)sub_41ACF0(*(this + 178));
    v6 = sub_431860(v5, fld_e178, 1);
  }
  v8 = (char *)sub_44B6C0(284);
  v9 = v8;
  if ( v8 != nullptr )
  {
    sub_44E0D0(v8, v6, 1);
    *(uint32_t *)v9 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v9 = nullptr;
  }
  sub_45FE80(*(this + 29), (int)v9, 2, 0, (int)v9, (int)this, 0);
  v10 = *(uint32_t *)v9;
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(char *, int))(v10 + 148))(v9, v11);
  v12 = *(uint32_t *)v9;
  v13 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v13);
  v15 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v14);
  (*(void (/*thiscall*/ **)(char *, int))(v12 + 112))(v9, v15);
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "CLAY_HIT", -1, 0, 0);
  return CNRDPassiveObject__vmt1F4(this, uArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x60F110 CNMagicTargetWarning__vmt2BC
// ------------------------------------------------------------
// CNMagicTargetWarning 命中结算槽（vmt2BC）：sub_493D00（研究 20 P38-2 定案的动画速率写者）——
// 警示圈以速率控制收缩节奏（魔法瞄准 AOE 预警圈的 PO 载体【推断】）。
void /*thiscall*/ CNMagicTargetWarning__vmt2BC(uint32_t *this, int pArg2, size_t Size)
{
  int pArg22; // esi
  void *fld_e242; // edx
  int v6; // eax
  signed int pThis_3DA; // ecx
  int v8; // eax
  float pThis_1EC; // [esp+0h] [ebp-10h]

  pArg22 = pArg2;
  CNRDPassiveObject__vmt2BC(pArg2, Size);
  fld_e242 = (void *)*(this + 242);
  if ( fld_e242 != nullptr )
  {
    *(this + 243) = *(uint32_t *)pArg2;
    *(this + 244) = *(uint32_t *)(pArg2 + 4);
    *(this + 245) = *(uint32_t *)(pArg2 + 8);
    *(this + 246) = *(uint32_t *)(pArg2 + 12);
    *((uint16_t *)this + 494) = *(uint16_t *)(pArg2 + 16);
    v6 = 18;
    if ( *((uint8_t *)this + 982) != 0 )
    {
      qmemcpy((char *)this + 990, (const void *)(pArg2 + 18), 0x62u);
      pArg22 = pArg2;
      v6 = 116;
    }
    pThis_3DA = *(uint32_t *)((char *)this + 986);
    *(this + 241) = pThis_3DA;
    if ( pThis_3DA > 0 )
      qmemcpy(fld_e242, (const void *)(v6 + pArg22), pThis_3DA);
    pThis_1EC = (float)*((int16_t *)this + 492);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
    sub_493D00(v8, pThis_1EC);
  }
  else
  {
    off_77F3FC(aErrorCnmagicta);
  }
}



// ------------------------------------------------------------
// 0x60F1E0 CNMagicTargetWarning__vmt10
// ------------------------------------------------------------
// CNMagicTargetWarning 初始化（vmt10）：警示圈初值装配。
int */*thiscall*/ CNMagicTargetWarning__vmt10(int this)
{
  int *result; // eax
  int v3; // edi

  CNRDPassiveObject__vmt10((uint8_t *)this);
  result = *(int **)(this + 1088);
  if ( result == (int *)3 || result == (int *)4 )
  {
    result = *(int **)(this + 116);
    if ( result != nullptr )
    {
      result = (int *)result[33];
      if ( result != nullptr )
      {
        result = (int *)__RTDynamicCast(
                          result[13],
                          0,
                          &CNRDObject `RTTI Type Descriptor',
                          &IRDCollisionObject `RTTI Type Descriptor',
                          0);
        if ( result != nullptr )
        {
          v3 = (*(int (/*thiscall*/ **)(int *))(*result + 376))(result);
          if ( v3 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 376))(this) )
            return (int *)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 252))(this, 3, -1);
          else
            return (int *)(*(int (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)this + 252))(this, 3, 0);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60F270 CNMagicTargetWarning__vmt14C
// ------------------------------------------------------------
// CNMagicTargetWarning 主循环槽（vmt14C）：sub_4E4A50（动作包）+ sub_4E4C10 ——
// 预警圈的同步与收缩推进【推断】。
char /*thiscall*/ CNMagicTargetWarning__vmt14C(uint8_t *this)
{
  int pThis_C8; // eax
  uint8_t *pThis_AD; // edi
  int fld_e983; // eax
  int pThis_1E6; // edx
  int pThis_F2; // [esp-8h] [ebp-Ch]

  pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( *(uint8_t *)(pThis_C8 + 170) != 0 )
  {
    LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( (uint8_t)pThis_C8 != 0 )
    {
      LOBYTE(pThis_C8) = *(this + 264);
      if ( (uint8_t)pThis_C8 == 0 )
      {
        pThis_AD = *((uint8_t **)this + 173);
        if ( pThis_AD == nullptr )
          pThis_AD = this;
        fld_e983 = *(this + 983);
        if ( fld_e983 == 4 )
          fld_e983 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this);
        if ( *(this + 982) != 0 )
        {
          *(uint32_t *)(this + 990) = *((int16_t *)this + 488);
          *(uint32_t *)(this + 994) = *((int16_t *)this + 489);
          *(uint32_t *)(this + 998) = *((int16_t *)this + 490);
          pThis_F2 = *((uint32_t *)this + 242);
          pThis_1E6 = *((uint16_t *)this + 486);
          *(this + 1074) = fld_e983 == 0;
          sub_4E4C10(pThis_AD, pThis_1E6, *((uint16_t *)this + 487), this + 990, 0, 0, *((uint32_t *)this + 241), pThis_F2);
        }
        else
        {
          sub_4E4A50(
            pThis_AD,
            *((uint16_t *)this + 486),
            *((uint16_t *)this + 487),
            *((int16_t *)this + 488),
            *((int16_t *)this + 489),
            *((int16_t *)this + 490),
            fld_e983,
            0,
            *((uint32_t *)this + 241),
            *((uint32_t *)this + 242));
        }
        LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
      }
    }
  }
  return pThis_C8;
}



// ------------------------------------------------------------
// 0x60F3A0 sub_60F3A0
// ------------------------------------------------------------
int /*thiscall*/ sub_60F3A0(uint32_t *this, int nArg2)
{
  int nArg22; // eax

  nArg22 = nArg2;
  *(this + 272) = nArg2;
  if ( nArg2 == 3 )
  {
    nArg22 = 1;
  }
  else if ( nArg2 == 4 )
  {
    nArg22 = 2;
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4 * nArg22));
}



// ------------------------------------------------------------
// 0x60F3E0 sub_60F3E0
// ------------------------------------------------------------
int /*thiscall*/ sub_60F3E0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint8_t *)(this + 988) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60F410 CNForceField__vmt10
// ------------------------------------------------------------
// CNForceField 初始化（vmt10）：念气罩初值装配。
int /*thiscall*/ CNForceField__vmt10(int this)
{
  int result; // eax
  int v3; // edi
  int fld_2B4; // ebx
  uint32_t *pThis_3CC; // esi
  int i; // [esp+4h] [ebp-4h]

  CNRDPassiveObject__vmt10((uint8_t *)this);
  result = *(uint32_t *)(this + 692);
  if ( result != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 120))(result);
    fld_2B4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 692) + 124))(*(uint32_t *)(this + 692));
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)this + 112))(this, v3, fld_2B4, 0);
    pThis_3CC = (uint32_t *)(this + 972);
    for ( i = 4; i != 0; --i )
    {
      if ( *pThis_3CC != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*pThis_3CC + 112))(*pThis_3CC, v3, fld_2B4, 0);
      ++pThis_3CC;
      result = i - 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60F480 CNForceField__vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNForceField__vmt12C(uint32_t *this, int nArg2)
{
  int result; // eax

  CNRDPassiveObject__vmt12C(this, nArg2);
  result = 0;
  if ( nArg2 == *(this + 243) )
    *(this + 243) = 0;
  if ( nArg2 == *(this + 244) )
    *(this + 244) = 0;
  if ( nArg2 == *(this + 245) )
    *(this + 245) = 0;
  if ( nArg2 == *(this + 246) )
    *(this + 246) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60F4E0 sub_60F4E0
// ------------------------------------------------------------
int sub_60F4E0()
{
  sub_4015C0("FORCE_FIELD_CIRCLE", 0x12u);  // 【std::string构造赋值】
  return sub_4015C0("FORCE_FIELD_FIRE", 0x10u);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x60F510 CNForceField__vmt14C
// ------------------------------------------------------------
// CNForceField 主循环槽（vmt14C，143 行）：字符串证据「PassiveObject/Common/Animation/ForceField/
// dirt.ani | blast.ani | chargecircle.ani | Field.ani」——蓄力圈→罩体→碎裂四段资源全套。
// sub_44B6C0/44E0D0（帧事件）+ sub_45FE80（演播层）+ sub_600890 —— 念气罩全生命周期演出。
// 音效 TAG 见 0x60F510 区（FORCE_FIELD_CIRCLE / FORCE_FIELD_FIRE）。
int /*usercall*/ sub_60F510@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int pObj; // edi
  char *v4; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // ebx
  char *v8; // eax
  int v9; // eax
  int v10; // ecx
  char *v11; // eax
  int v12; // eax
  int v13; // ecx
  char *v14; // eax
  int v15; // eax
  int v16; // ecx
  uint32_t *v17; // eax
  int result; // eax
  int v19; // [esp+Ch] [ebp-1Ch]
  char *v20; // [esp+Ch] [ebp-1Ch]
  char *v21; // [esp+Ch] [ebp-1Ch]
  char *v22; // [esp+Ch] [ebp-1Ch]
  int v23; // [esp+10h] [ebp-18h]
  int v24; // [esp+10h] [ebp-18h]
  int v25; // [esp+10h] [ebp-18h]
  int v26; // [esp+10h] [ebp-18h]
  int v27; // [esp+14h] [ebp-14h]
  int v28; // [esp+18h] [ebp-10h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  pObj = pArg1[173];
  if ( *((uint8_t *)pArg1 + 988) != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 148) == 1 && pArg1[253] != 0 )
    {
      if ( pArg1[254] < 0x10u )
        v17 = pArg1 + 249;
      else
        v17 = (uint32_t *)pArg1[249];
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, v17, -1, 0, 0);
      sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    }
  }
  else if ( pObj != 0 )
  {
    v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, nArg2);
    v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
    v28 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
    if ( sub_42FCB0(228) != 0 )
      v23 = sub_431860((char)"PassiveObject/Common/Animation/ForceField/dirt.ani", 1);
    else
      v23 = 0;
    v4 = (char *)sub_44B6C0(284);
    if ( v4 != nullptr )
    {
      sub_44E0D0(v4, v23, 1);
      *(uint32_t *)v4 = &CNRDPooledObject::`vftable';
      v5 = (int)v4;
    }
    else
    {
      v5 = 0;
    }
    v6 = a1[29];
    a1[243] = v5;
    sub_45FE80(v6, v3, 2, 0, v5, v3, 1);
    v7 = v19;
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)a1[243] + 112))(a1[243], v19, v27, v28);
    if ( sub_42FCB0(228) != 0 )
      v24 = sub_431860((char)"PassiveObject/Common/Animation/ForceField/blast.ani", 1);
    else
      v24 = 0;
    v8 = (char *)sub_44B6C0(284);
    v20 = v8;
    if ( v8 != nullptr )
    {
      sub_44E0D0(v8, v24, 1);
      v9 = (int)v20;
      *(uint32_t *)v20 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v9 = 0;
    }
    v10 = pArg1[29];
    pArg1[244] = v9;
    sub_45FE80(v10, pObj, 2, 0, v9, pObj, 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)pArg1[244] + 112))(pArg1[244], v7, v27, v28);
    if ( sub_42FCB0(228) != 0 )
      v25 = sub_431860((char)"PassiveObject/Common/Animation/ForceField/chargecircle.ani", 1);
    else
      v25 = 0;
    v11 = (char *)sub_44B6C0(284);
    v21 = v11;
    if ( v11 != nullptr )
    {
      sub_44E0D0(v11, v25, 1);
      v12 = (int)v21;
      *(uint32_t *)v21 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v12 = 0;
    }
    v13 = a1[29];
    a1[245] = v12;
    sub_45FE80(v13, v3, 2, 0, v12, v3, 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)a1[245] + 112))(a1[245], v7, v27, v28);
    if ( sub_42FCB0(228) != 0 )
      v26 = sub_431860((char)"PassiveObject/Common/Animation/ForceField/Field.ani", 1);
    else
      v26 = 0;
    v14 = (char *)sub_44B6C0(284);
    v22 = v14;
    if ( v14 != nullptr )
    {
      sub_44E0D0(v14, v26, 1);
      v15 = (int)v22;
      *(uint32_t *)v22 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v15 = 0;
    }
    v16 = pArg1[29];
    pArg1[246] = v15;
    sub_45FE80(v16, pObj, 2, 0, v15, pObj, 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[246] + 112))(pArg1[246], v7, v27);
    *((uint8_t *)pArg1 + 988) = 1;
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);
    *((uint8_t *)pArg1 + 988) = 1;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    result = pArg1[243];
    if ( result == 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x60F8A0 sub_60F8A0
// ------------------------------------------------------------
int /*thiscall*/ sub_60F8A0(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60F8C0 sub_60F8C0
// ------------------------------------------------------------
int /*thiscall*/ sub_60F8C0(int this, int nArg2, int nArg3)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 980) = nArg2;
  *(uint32_t *)(this + 976) = nArg3;
  return nArg2;
}



// ------------------------------------------------------------
// 0x60F8E0 CNCircleAppendageMaker__vmt2C8
// ------------------------------------------------------------
// CNCircleAppendageMaker 碰撞槽（vmt2C8）：sub_47E720/47EF20（命中几何扫描族）——
// 圆环附属生成器的范围判定【推断：抓取圈扫描】。
int /*thiscall*/ CNCircleAppendageMaker__vmt2C8(uint32_t *this, int *pDwArg2, uint32_t *uArg3)
{
  int result; // eax
  int pObj; // esi
  int *v6; // eax
  int v7; // ebx
  uint32_t *fld_e245; // edi
  int fld_e2452; // ecx

  result = *(this + 244);
  if ( result == 0 )
  {
    result = __RTDynamicCast(
               *(this + 173),
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDCharacter `RTTI Type Descriptor',
               0);
    pObj = result;
    if ( result != 0 )
    {
      v6 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 1032))(result);
      v7 = *v6;
      fld_e245 = (uint32_t *)sub_47E720(*v6, *(this + 245));
      result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 1140))(pObj, *(this + 245));
      if ( v7 != 0 )
      {
        if ( v7 == 1 )
        {
          fld_e2452 = *(this + 245);
          switch ( fld_e2452 )
          {
            case 30:
              result = sub_47EF20(fld_e245, 1u, result, -1, -1, 11);
LABEL_7:
              *pDwArg2 = result;
              *uArg3 = 0;
              return result;
            case 31:
              result = sub_47EF20(fld_e245, 2u, result, -1, -1, 11);
              goto LABEL_7;
            case 39:
              result = sub_47EF20(fld_e245, 2u, result, -1, -1, 11);
LABEL_12:
              *pDwArg2 = result;
              *uArg3 = 1;
              return result;
            case 44:
              result = sub_47EF20(fld_e245, 1u, result, -1, -1, 11);
              goto LABEL_12;
            default:
              break;
          }
        }
        else if ( v7 == 2 )
        {
          if ( *(this + 245) == 50 )
          {
            *pDwArg2 = sub_47EF20(fld_e245, 0, result, -1, -1, 11);
            *uArg3 = 0;
            return (int)uArg3;
          }
        }
        else if ( v7 == 3 && *(this + 245) == 28 )
        {
          *pDwArg2 = sub_47EF20(fld_e245, 0, result, -1, -1, 11);
          *uArg3 = 1;
          return (int)uArg3;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60FA60 sub_60FA60
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_60FA60(uint32_t *this, int nArg2, int nArg3)
{
  sub_4B1030(this);
  *this = &vftbl_CNProvocationed;
  sub_652010(nArg2, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x60FAC0 CNProvocationed__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNProvocationed__vmt0(void *Block, char pszArg2)
{
  sub_60FAF0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x60FAF0 sub_60FAF0
// ------------------------------------------------------------
int /*thiscall*/ sub_60FAF0(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60FB40 sub_60FB40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_60FB40(uint32_t *this, int nArg2)
{
  sub_4B1030(this);
  *this = &vftbl_CNAimVitalPoint;
  sub_652220(this);
  sub_652230(nArg2);
  return this;
}



// ------------------------------------------------------------
// 0x60FBA0 CNAimVitalPoint__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNAimVitalPoint__vmt0(void *Block, char pszArg2)
{
  sub_60FBD0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x60FBD0 sub_60FBD0
// ------------------------------------------------------------
int /*thiscall*/ sub_60FBD0(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNAimVitalPoint;
  sub_652350();
  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60FC30 sub_60FC30
// ------------------------------------------------------------
// 附属伤害输入（68 行）：sub_4E4630 + sub_4E5F70（硬直率掷）——
// 附属圈对圈内目标的持续伤害输入【推断：DOT 圈】。
int /*thiscall*/ sub_60FC30(int *this, int nArg2, int nArg3)
{
  int result; // eax
  int i; // ebx
  int fld_e29; // ecx
  int v7; // edx
  int v8; // edx
  int pObj; // esi
  int pObj2; // eax
  int v11; // ebx
  bool v12; // zf
  float pBuf[6]; // [esp+4h] [ebp-1Ch] BYREF
  int v14; // [esp+1Ch] [ebp-4h]

  result = nArg2;
  if ( nArg2 != 0 )
  {
    result = *(this + 29);
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
      if ( result != 0 )
      {
        for ( i = 0; ; ++i )
        {
          fld_e29 = *(this + 29);
          v7 = *(uint32_t *)(fld_e29 + 120);
          v14 = i;
          if ( v7 != 0 )
            result = (*(uint32_t *)(fld_e29 + 124) - v7) >> 2;
          else
            result = 0;
          if ( i >= result )
            return result;
          v8 = *(uint32_t *)(fld_e29 + 120);
          if ( v8 != 0 && i < (unsigned int)((*(uint32_t *)(fld_e29 + 124) - v8) >> 2) )
            pObj = *(uint32_t *)(v8 + 4 * i);
          else
            pObj = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )
          {
            if ( nArg3 == 0 )
            {
              pObj2 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
              v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);
              v12 = v11 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
              i = v14;
              if ( !v12 )
                continue;
LABEL_19:
              if ( (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, pObj, 0) <= nArg2 / 2 )
              {
                memset(pBuf, 0, sizeof(pBuf));
                sub_4E5F70(i, (int)this, pObj, pBuf, 0, 0);
              }
              continue;
            }
            if ( nArg3 != 1 )
              goto LABEL_19;
            (*(void (/*thiscall*/ **)(int *))(*this + 684))(this);
            if ( (uint8_t)sub_4E4630(pObj) != 0 )
              goto LABEL_19;
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60FD70 CNCircleAppendageMaker__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNCircleAppendageMaker__vmt14C(int *this)
{
  char result; // al
  int v3; // edx
  int v4; // [esp+4h] [ebp-8h] BYREF
  int v5; // [esp+8h] [ebp-4h] BYREF

  CNRDPassiveObject__vmt14C((int)this);
  result = *((uint8_t *)this + 972);
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( result != 0 )
    {
      v3 = *this;
      v4 = 0;
      v5 = 0;
      (*(void (/*thiscall*/ **)(int *, int *, int *))(v3 + 712))(this, &v4, &v5);
      sub_60FC30(this, v4, v5);
      result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    }
    *((uint8_t *)this + 972) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x60FDE0 CNCircleAppendageMaker__vmt1F4
// ------------------------------------------------------------
// ★ CNCircleAppendageMaker 命中表现槽（vmt1F4，250 行）：字符串证据「Common/CommonEffect/BuffIcon.img」（buff 图标图集）+
// 「BUFF_FASTFIST | BUFF_FATAL_POINT」（音效 TAG —— 快拳/要害）。
// sub_517740/sub_5C24B0/sub_5C2D60（buff 应用族）+ sub_4B3C90/sub_4C0400 + sub_60FA60/60FB40 ——
// 给命中目标挂 buff 图标与状态的双分支（快拳/要害二选一）。
// 【推断：气功师/武神的范围增益圈——圈内队友获增益状态的 PO 载体】。
int /*thiscall*/ sub_60FDE0(int *this, int nArg2, int nArg3, int nArg4)  // 【CNCircleAppendageMaker__vmt1F4】
{
  int v5; // ebx
  int pObj4; // ecx
  int fld_e244; // eax
  int fld_e173; // esi
  uint32_t *v9; // eax
  int v10; // ebx
  int fld_e245; // esi
  int fld_e2452; // eax
  void *pMem; // edi
  int v14; // eax
  int v15; // eax
  uint32_t *v16; // eax
  int v17; // esi
  void *pMem2; // eax
  int pObj6; // esi
  uint32_t *v20; // eax
  int v21; // eax
  int v22; // eax
  uint32_t *v23; // eax
  int v24; // eax
  int v25; // ebx
  int v26; // eax
  uint32_t *v27; // eax
  uint32_t *v28; // esi
  int *v29; // eax
  uint32_t *v30; // edi
  int v31; // esi
  int pObj; // eax
  int pObj2; // eax
  uint32_t *v34; // edi
  int v35; // ebx
  unsigned int i; // esi
  int v37; // ecx
  int pObj7; // ecx
  int pObj5; // eax
  float v41; // [esp+10h] [ebp-2Ch]
  unsigned int v42; // [esp+14h] [ebp-28h]
  void *Block; // [esp+20h] [ebp-1Ch]
  int v44; // [esp+24h] [ebp-18h]
  int v45; // [esp+28h] [ebp-14h]
  int v46; // [esp+28h] [ebp-14h]
  float v47; // [esp+28h] [ebp-14h]
  float v48; // [esp+28h] [ebp-14h]
  int pObj3; // [esp+44h] [ebp+8h]

  v5 = sub_5FF9C0(nArg2, nArg3, nArg4);  // 【CNRDPassiveObject__vmt1F4】
  v44 = v5;
  pObj4 = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  pObj3 = pObj4;
  if ( pObj4 != 0 )
  {
    fld_e244 = *(this + 244);
    nArg4 = 0;
    v45 = 0;
    nArg3 = 0;
    if ( fld_e244 != 0 )
    {
      if ( fld_e244 == 1 )
      {
        (*(void (/*thiscall*/ **)(int *, int *, int *))(*this + 708))(this, &nArg4, &nArg3);
      }
      else
      {
        if ( fld_e244 != 2 || *(this + 245) != 0 )
          return v5;
        v34 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 700))(pObj4);
        v35 = sub_41C5A0(v34);
        for ( i = 0; (int)i < v35; ++i )
        {
          v37 = v34[1];
          if ( v37 != 0 && i < (v34[2] - v37) >> 2 )
            pObj7 = *(uint32_t *)(v37 + 4 * i);
          else
            pObj7 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj7 + 92))(pObj7) != 0 )
          {
            pObj5 = sub_517740(i);
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj5 + 76))(pObj5, 0);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 956))(pObj3);
          }
        }
      }
    }
    else
    {
      fld_e173 = __RTDynamicCast(
             *(this + 173),
             0,
             &IRDCollisionObject `RTTI Type Descriptor',
             &IRDCharacter `RTTI Type Descriptor',
             0);
      if ( fld_e173 == 0 )
        return v5;
      v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e173 + 1032))(fld_e173);
      v10 = *v9;
      sub_47E720(*v9, *(this + 245));
      fld_e245 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e173 + 1140))(fld_e173, *(this + 245));
      if ( v10 != 0 )
      {
        if ( v10 == 1 )
        {
          fld_e2452 = *(this + 245);
          switch ( fld_e2452 )
          {
            case 30:
              pMem = operator new(0x84u);
              v14 = 0;
              if ( pMem != nullptr )
              {
                v15 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
                v14 = sub_4DF1B0((int)pMem, fld_e245, 3, 1, v15);
              }
              nArg4 = v14;
              v16 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                                dword_8F84B8,
                                "Common/CommonEffect/BuffIcon.img");
              v45 = sub_418DD0(v16, 2u);
              nArg3 = 1;
              break;
            case 31:
              v46 = sub_47EF20(0, fld_e245, -1, -1, 11);
              v17 = sub_47EF20(1, fld_e245, -1, -1, 11);
              pMem2 = operator new(0x7Cu);
              if ( pMem2 != nullptr )
                pObj6 = sub_4B3C90((int)pMem2, v17, 1);
              else
                pObj6 = 0;
              v47 = (float)v46;
              (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)pObj6 + 120))(pObj6, 7, 0, LODWORD(v47));
              v41 = v47 * 0.001;
              (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)pObj6 + 120))(pObj6, 24, 0, LODWORD(v41));
              nArg4 = pObj6;
              v20 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int))(*(uint32_t *)dword_8F84B8 + 60))(
                                dword_8F84B8,
                                "Common/CommonEffect/BuffIcon.img",
                                3);
              v21 = sub_418DD0(v20, v42);
              nArg3 = 2;
              v45 = v21;
              (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t))(*(uint32_t *)pObj3 + 212))(
                pObj3,
                "BUFF_FASTFIST",
                -1,
                0);
              break;
            case 39:
              if ( operator new(0x5Cu) != nullptr )
                v22 = sub_60FB40(fld_e245);
              else
                v22 = 0;
              nArg4 = v22;
              v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int))(*(uint32_t *)dword_8F84B8 + 60))(
                                dword_8F84B8,
                                "Common/CommonEffect/BuffIcon.img",
                                10);
              v24 = sub_418DD0(v23, v42);
              nArg3 = 7;
              v45 = v24;
              (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t))(*(uint32_t *)pObj3 + 212))(
                pObj3,
                "BUFF_FATAL_POINT",
                -1,
                0);
              break;
            case 44:
              v25 = sub_47EF20(0, fld_e245, -1, -1, 11);
              v48 = (double)(int)sub_47EF20(2, fld_e245, -1, -1, 11) * 0.1;
              if ( operator new(0x54u) != nullptr )
                v26 = sub_60FA60(v25, LODWORD(v48));
              else
                v26 = 0;
              nArg4 = v26;
              v27 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                                dword_8F84B8,
                                "Common/CommonEffect/BuffIcon.img");
              v45 = sub_418DD0(v27, 0x17u);
              nArg3 = 8;
              break;
            default:
              break;
          }
        }
        else if ( v10 == 2 )
        {
          if ( *(this + 245) == 50 )
          {
            v28 = (uint32_t *)__RTDynamicCast(
                              pObj3,
                              0,
                              &IRDActiveObject `RTTI Type Descriptor',
                              &IRDMonster `RTTI Type Descriptor',
                              0);
            if ( v28 != nullptr && v28[2088] == *(this + 173) )
            {
              v29 = (int *)(*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 340))(v28);
              if ( sub_4C0400(*v29) != 0 )
              {
                if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 340))(v28) == 60002 )
                {
                  sub_5C24B0(v28);
                }
                else if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 340))(v28) == 60003 )
                {
                  sub_5C2D60(v28);
                }
                else if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 340))(v28) == 60004 )
                {
                  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*v28 + 732))(v28, 0, 0, 1);
                }
              }
            }
          }
        }
        else if ( v10 == 3 && *(this + 245) == 28 )
        {
          v30 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 700))(pObj3);
          v31 = 0;
          Block = (void *)sub_41C5A0(v30);
          if ( (int)Block > 0 )
          {
            do
            {
              pObj = sub_517740(v31);
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 92))(pObj) != 0 )
              {
                pObj2 = sub_517740(v31);
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 76))(pObj2, 0);
              }
              ++v31;
            }
            while ( v31 < (int)Block );
          }
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 956))(pObj3);
        }
      }
    }
    if ( nArg4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int, int, int))(*(uint32_t *)nArg4 + 56))(
        nArg4,
        pObj3,
        *(this + 173),
        1,
        v45,
        nArg3,
        -1);
    return v44;
  }
  return v5;
}


// ============================================================
// 【分区 9】召唤/诅咒/投技/鬼神/气功 PO（0x610320-0x616390）
// ★ 0x610C00 = SummonCircle 三段法阵 + 四属性 Spirit（火/水/暗/光）召唤动画本体；
// CNBodyHit/CNSuplexSub 投技判定；冰浪三形态（追踪/多段/上升）；CNGhost 三鬼神
// （GHOST_KAJAN/SAYA/BREMEN 音效 TAG）；CNSpiralNen/CNNenGuard 念气系
// ============================================================
// ------------------------------------------------------------
// 0x610320 CNToothSFish__vmt1F4
// ------------------------------------------------------------
// CNToothSFish 命中表现槽（vmt1F4，71 行）：食人鱼齿（ToothSFish）咬合目标的演出【推断：地图水道食人鱼陷阱】。
int /*thiscall*/ CNToothSFish__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  uint32_t *pArg22; // ebx
  int v5; // esi
  int v6; // eax
  int v7; // edi
  int v8; // ecx
  unsigned int v9; // esi
  int v10; // ecx
  int pObj2; // ecx
  int v12; // ecx
  int pObj; // ecx
  int i; // edi
  int *v15; // esi
  int v16; // ebx
  int v17; // eax
  int v19; // [esp+8h] [ebp-8h]
  int v21; // [esp+1Ch] [ebp+Ch]
  char v22; // [esp+23h] [ebp+13h]

  pArg22 = pArg2;
  v5 = CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
  v19 = v5;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg22 + 40))(pArg22, 17) == 0 )
    return v5;
  v22 = 0;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 700))(pArg2);
  v7 = v6;
  v8 = *(uint32_t *)(v6 + 4);
  v9 = 0;
  if ( v8 != 0 )
    v21 = (*(uint32_t *)(v6 + 8) - v8) >> 2;
  else
    v21 = 0;
  if ( v21 > 0 )
  {
    do
    {
      v10 = *(uint32_t *)(v7 + 4);
      if ( v10 != 0 && v9 < (*(uint32_t *)(v7 + 8) - v10) >> 2 )
        pObj2 = *(uint32_t *)(v10 + 4 * v9);
      else
        pObj2 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 92))(pObj2) != 0 )
      {
        v12 = *(uint32_t *)(v7 + 4);
        if ( v12 != 0 && v9 < (*(uint32_t *)(v7 + 8) - v12) >> 2 )
          pObj = *(uint32_t *)(v12 + 4 * v9);
        else
          pObj = 0;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);
        v22 = 1;
      }
      ++v9;
    }
    while ( (int)v9 < v21 );
    if ( v22 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t *))(*pArg2 + 956))(pArg2);
  }
  for ( i = 0; i < 17; ++i )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg22 + 776))(pArg22, i) != 0 )
    {
      v15 = (int *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg22 + 772))(pArg22, i);
      v16 = *v15;
      v17 = (*(int (/*thiscall*/ **)(int *))(*this + 576))(this);
      (*(void (/*thiscall*/ **)(int *, uint32_t, int))(v16 + 4))(v15, 0, v17);
      pArg22 = pArg2;
    }
  }
  return v19;
}



// ------------------------------------------------------------
// 0x610440 CNToothKurokuta__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNToothKurokuta__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int v5; // ebx
  int v6; // ebx
  int v7; // eax
  int v9; // [esp+18h] [ebp+Ch]
  int v10; // [esp+1Ch] [ebp+10h]

  v5 = CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
  v9 = v5;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) == 0 )
    return v5;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  v6 = sub_445870((uint32_t *)dword_8F8520, 37992, 17);
  v10 = *pArg2;
  v7 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 576))(this, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(v10 + 760))(pArg2, v6, 1120403456, 3, v7);
  return v9;
}



// ------------------------------------------------------------
// 0x6106B0 CNCurseBomb__vmt14C
// ------------------------------------------------------------
// CNCurseBomb 主循环槽（vmt14C）：sub_4E4A50（动作包）——诅咒炸弹的滞空/引信推进；爆炸音 BOMB_EXPLOSION 见 0x610740。
char /*thiscall*/ CNCurseBomb__vmt14C(uint32_t *this)
{
  uint32_t *fld_e173; // edi
  int v2; // eax
  int v4; // eax
  uint32_t *fld_e36; // edi
  int v6; // eax
  int v7; // edx
  int v9; // [esp-1Ch] [ebp-20h]
  int v10; // [esp-18h] [ebp-1Ch]
  int v11; // [esp-14h] [ebp-18h]
  uint32_t *fld_e362; // [esp-4h] [ebp-8h]

  CNRDPassiveObject__vmt14C((int)this);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  if ( v4 <= 0 )
  {
    fld_e36 = (uint32_t *)*(this + 36);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
    v7 = *this;
    if ( v6 == *fld_e36 )
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 200))(this);
      if ( *(uint8_t *)(v4 + 170) != 0 )
      {
        LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
        if ( (uint8_t)v4 != 0 )
        {
          LOBYTE(v4) = *((uint8_t *)this + 264);
          if ( (uint8_t)v4 == 0 )
          {
            fld_e362 = fld_e36;
            fld_e173 = (uint32_t *)*(this + 173);
            if ( fld_e173 == nullptr )
              fld_e173 = this;
            v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
            v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
            v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
            v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
            sub_4E4A50(fld_e173, *(this + 243), 0, v2, v9, v10, v11, 0, 0, 0);
            LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t *))(*this + 312))(this, 0, fld_e362);
          }
        }
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v7 + 196))(this, *(uint32_t *)*(this + 36));
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this) + 60) = 0;
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this);
      *(uint32_t *)v4 = 0;
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x610740 sub_610740
// ------------------------------------------------------------
// 诅咒炸弹爆炸辅助：字符串证据「BOMB_EXPLOSION」（音效 TAG）+ sub_4015C0（字符串构造）——爆炸播音的 TAG 装配。
int /*thiscall*/ sub_610740(uint32_t **this)
{
  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) == 0 )
  {
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      0,
      **(this + 36),
      0,
      0,
      0,
      0);
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      1,
      (*(this + 36))[1],
      0,
      0,
      0,
      0);
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      2,
      (*(this + 36))[2],
      0,
      0,
      0,
      0);
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      3,
      (*(this + 36))[3],
      0,
      0,
      0,
      0);
  }
  return sub_4015C0("BOMB_EXPLOSION", 0xEu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x6107E0 CNCurseBombSub__vmt14C
// ------------------------------------------------------------
// CNCurseBombSub 主循环槽（vmt14C，80 行）：sub_41ACF0 + sub_428F30（粒子发射器）+ sub_4600B0 ——
// 诅咒炸弹子体（分裂弹）的飞行/爆炸演出。
char /*thiscall*/ CNCurseBombSub__vmt14C(int **this)
{
  uint32_t *pMem; // edi
  int *v3; // eax
  int fld_e178; // eax
  uint32_t *pMem2; // edi
  int fld_e1782; // eax
  int *v7; // eax
  int **pThis_F3; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  void *fld_e29; // ecx
  bool v14; // zf
  char result; // al
  uint8_t v16[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]
  int v19; // [esp+14h] [ebp-14h]
  void *pMem3; // [esp+18h] [ebp-10h]
  int v21; // [esp+24h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 243) == nullptr && *(this + 244) == nullptr )
  {
    pMem = operator new(0x12Cu);
    pMem3 = pMem;
    v3 = nullptr;
    v21 = 0;
    if ( pMem != nullptr )
    {
      fld_e178 = sub_41ACF0(*(this + 178));
      v3 = sub_428F30(pMem, fld_e178, (int)this);
    }
    *(this + 243) = v3;
    pMem2 = operator new(0x12Cu);
    pMem3 = pMem2;
    v21 = 1;
    if ( pMem2 != nullptr )
    {
      fld_e1782 = sub_41ACF0(*(this + 178) + 1);
      v7 = sub_428F30(pMem2, fld_e1782, (int)this);
    }
    else
    {
      v7 = nullptr;
    }
    v21 = -1;
    *(this + 244) = v7;
    pThis_F3 = this + 243;
    pMem3 = (void *)2;
    do
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(**pThis_F3 + 12))(*pThis_F3, 0);
      v9 = **pThis_F3;
      v10 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
      v11 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v10);
      v12 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v11);
      (*(void (/*thiscall*/ **)(int *, int))(v9 + 40))(*pThis_F3, v12);
      (*(void (/*thiscall*/ **)(int *, uint8_t *))(**pThis_F3 + 92))(*pThis_F3, v16);
      fld_e29 = *(this + 29);
      v21 = 2;
      sub_4600B0(fld_e29, 2, 0, (int)v16);
      v21 = -1;
      if ( Block != nullptr )
        j__free(Block);
      ++pThis_F3;
      v14 = pMem3 == (void *)1;
      Block = nullptr;
      v18 = 0;
      v19 = 0;
      pMem3 = (char *)pMem3 - 1;
    }
    while ( !v14 );
  }
  result = *((uint8_t *)*(this + 30) + 170);
  if ( result != 0 )
    return ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x610960 sub_610960
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_610960(uint32_t *this, char pszArg2, int nArg3)
{
  sub_52EA60(this, pszArg2, nArg3);
  *this = &vftbl_CNCurseBomb;
  *(this + 243) = nArg3;
  sub_5FF8E0((int)this);
  return this;
}



// ------------------------------------------------------------
// 0x6109C0 CNCurseBomb__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNCurseBomb__vmt0(void *Block, char pszArg2)
{
  sub_6109F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x6109F0 sub_6109F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6109F0(void **this)
{
  *this = &vftbl_CNCurseBomb;
  sub_5FF980(this);
  *this = &vftbl_CNThrowItemDestroyable;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x610A50 sub_610A50
// ------------------------------------------------------------
int /*thiscall*/ sub_610A50(int this)
{
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = -1;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint8_t *)(this + 1004) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x610A80 sub_610A80
// ------------------------------------------------------------
void /*thiscall*/ sub_610A80(void **this)
{
  if ( *(this + 246) != nullptr )
    j__free(*(this + 246));
  *(this + 246) = nullptr;
}



// ------------------------------------------------------------
// 0x610AB0 CNSummonMonsterWithEffect__vmt14C
// ------------------------------------------------------------
// CNSummonMonsterWithEffect 主循环槽（vmt14C）：召唤兽带特效生成（SummonMonsterWithEffect）的存活推进；
// 三段法阵+四属性召唤动画在其 vmt2BC（0x610C00）。
int /*thiscall*/ CNSummonMonsterWithEffect__vmt14C(uint32_t *this)
{
  int fld_e247; // eax
  int *v3; // edi
  int v4; // ebx
  int fld_e246; // eax
  int v6; // eax
  int fld_e250; // eax
  int fld_e249; // eax
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) != 0 && *((uint8_t *)this + 1004) == 0 )
  {
    fld_e247 = *(this + 247);
    if ( fld_e247 == -1 )
    {
      if ( *(uint8_t *)(*(this + 30) + 170) == 0 )
        goto LABEL_12;
    }
    else if ( *(uint32_t *)(*(this + 30) + 148) < fld_e247 )
    {
      goto LABEL_12;
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0 )
        *(this + 248) = -*(this + 248);
      v3 = (int *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
      v4 = *v3;
      fld_e246 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 152))(
             this,
             0,
             0,
             0,
             *((uint16_t *)this + 489),
             *((uint8_t *)this + 980),
             *((uint8_t *)this + 981),
             *(this + 246),
             0);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 128))(this, fld_e246);
      fld_e250 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, *(this + 250) + v6);
      fld_e249 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, *(this + 249) + fld_e250);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, int))(v4 + 592))(
        v3,
        *(uint16_t *)((char *)this + 973),
        *(uint16_t *)((char *)this + 975),
        *((uint8_t *)this + 977),
        *(this + 248) + fld_e249);
    }
    *((uint8_t *)this + 1004) = 1;
  }
LABEL_12:
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  result = *(this + 30);
  if ( *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x610C00 CNSummonMonsterWithEffect__vmt2BC
// ------------------------------------------------------------
// ★★ 召唤阵演出槽（vmt2BC，138 行）—— 0x60 区字符串证据的『SummonCircle 三段动画 + 四属性 Spirit 召唤』本体：
// 字符串证据「Common/CommonEffect/Animation/SummonCircleBack.ani | SummonCircle.ani | SummonCircleFront.ani」
// （法阵背景/中景/前景三段叠层，P33 叠放风格）+「Monster/Spirit/FireAnimation/Summon.ani |
// WaterAnimation/Summon.ani | DarkAnimation/Summon.ani | LightAnimation/Summon.ani」（火/水/暗/光四属性精灵召唤动画）。
// sub_42ABE0 + sub_42FCB0（资源 228 门）→ sub_431860 批量生成 + sub_5FFF80 ——
// 召唤兽出场：法阵三层 + 按属性选精灵动画的完整演出管线。
int /*thiscall*/ sub_610C00(uint32_t *this, uint32_t *pArg2, size_t Size)  // 【召唤阵三段动画 + 四属性 Spirit 召唤（0x60 区字符串证据本体）】
{
  size_t v3; // edi
  char *pMem; // eax
  int fld_e246; // edx
  int result; // eax
  size_t v8; // eax
  int v9; // eax
  size_t v10; // eax
  int v11; // eax
  size_t v12; // eax
  int v13; // eax
  size_t v14; // eax
  int v15; // eax
  size_t v16; // eax
  int v17; // eax
  size_t v18; // eax
  size_t v19; // eax

  v3 = Size;
  sub_5FFF80((int)this, pArg2, Size);
  *(this + 243) = *pArg2;
  *(this + 244) = pArg2[1];
  *((uint16_t *)this + 490) = *((uint16_t *)pArg2 + 4);
  if ( v3 > 0xA )
  {
    if ( *(this + 246) == 0 )
    {
      pMem = (char *)operator new(7u);
      if ( pMem != nullptr )
      {
        *pMem = 0;
        pMem[1] = 0;
        pMem[2] = 0;
        *(uint32_t *)(pMem + 3) = 0;
      }
      else
      {
        pMem = nullptr;
      }
      *(this + 246) = pMem;
    }
    fld_e246 = *(this + 246);
    *(uint32_t *)fld_e246 = *(uint32_t *)((char *)pArg2 + 10);
    *(uint16_t *)(fld_e246 + 4) = *((uint16_t *)pArg2 + 7);
    *(uint8_t *)(fld_e246 + 6) = *((uint8_t *)pArg2 + 16);
  }
  result = *((uint8_t *)this + 972);
  switch ( *((uint8_t *)this + 972) )
  {
    case 0:
      v8 = sub_42FCB0(228);
      Size = v8;
      if ( v8 != 0 )
        v9 = sub_431860(v8, "Common/CommonEffect/Animation/SummonCircleBack.ani", 1);
      else
        v9 = 0;
      Size = v9;
      sub_42ABE0(&Size);
      v10 = sub_42FCB0(228);
      Size = v10;
      if ( v10 != 0 )
        v11 = sub_431860(v10, "Common/CommonEffect/Animation/SummonCircle.ani", 1);
      else
        v11 = 0;
      Size = v11;
      sub_42ABE0(&Size);
      v12 = sub_42FCB0(228);
      Size = v12;
      if ( v12 != 0 )
        v13 = sub_431860(v12, "Common/CommonEffect/Animation/SummonCircleFront.ani", 1);
      else
        v13 = 0;
      Size = v13;
      sub_42ABE0(&Size);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -100,
        *(uint32_t *)*(this + 36),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                 this,
                 100,
                 *(uint32_t *)(*(this + 36) + 8),
                 0,
                 0,
                 0,
                 0);
      *(this + 247) = 9;
      return result;
    case 1:
      v14 = sub_42FCB0(228);
      Size = v14;
      if ( v14 == 0 )
        goto LABEL_25;
      v15 = sub_431860(v14, "Monster/Spirit/FireAnimation/Summon.ani", 1);
      goto LABEL_26;
    case 2:
      v16 = sub_42FCB0(228);
      Size = v16;
      if ( v16 == 0 )
        goto LABEL_29;
      v17 = sub_431860(v16, "Monster/Spirit/WaterAnimation/Summon.ani", 1);
      goto LABEL_30;
    case 3:
      v18 = sub_42FCB0(228);
      Size = v18;
      if ( v18 != 0 )
        v15 = sub_431860(v18, "Monster/Spirit/DarkAnimation/Summon.ani", 1);
      else
LABEL_25:
        v15 = 0;
LABEL_26:
      Size = v15;
      sub_42ABE0(&Size);
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
    case 4:
      v19 = sub_42FCB0(228);
      Size = v19;
      if ( v19 != 0 )
        v17 = sub_431860(v19, "Monster/Spirit/LightAnimation/Summon.ani", 1);
      else
LABEL_29:
        v17 = 0;
LABEL_30:
      Size = v17;
      sub_42ABE0(&Size);
      result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
      *(this + 250) = 40;
      break;
    default:
      return result;
  }
  return result;
}


// ------------------------------------------------------------
// 0x610F40 sub_610F40
// ------------------------------------------------------------
int /*thiscall*/ sub_610F40(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = -1;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint8_t *)(this + 996) = 0;
  *(uint8_t *)(this + 997) = 0;
  *(uint32_t *)(this + 1000) = -1;
  *(uint32_t *)(this + 1004) = 0;
  *(uint32_t *)(this + 1008) = 4;
  return 0;
}



// ------------------------------------------------------------
// 0x610F90 sub_610F90
// ------------------------------------------------------------
int /*thiscall*/ sub_610F90(int this, int nArg2)
{
  int v3; // eax
  int v4; // eax
  int result; // eax

  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  v4 = sub_45EBE0(*(uint32_t **)(v3 + 104), HIWORD(nArg2), (uint16_t)nArg2);
  result = __RTDynamicCast(v4, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  *(uint32_t *)(this + 972) = result;
  *(uint8_t *)(this + 701) = 0;
  *(uint8_t *)(this + 700) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x610FF0 CNBodyHit__vmt2BC
// ------------------------------------------------------------
// CNBodyHit 命中结算槽（vmt2BC）：sub_41A5E0（P24 防篡改写）——
// 投技身体判定（BodyHit）命中时直写属性槽【推断：投技伤害按目标属性折算】。
int /*thiscall*/ CNBodyHit__vmt2BC(float *this, int *pDwArg2, int Size)
{
  int v6; // eax
  int pThis_F3; // ecx
  int v8; // edi
  int v9; // ebx
  int pThis_F32; // edi
  int v12; // [esp+10h] [ebp-4h]
  int16_t v13; // [esp+1Ch] [ebp+8h]
  int16_t Sizea; // [esp+20h] [ebp+Ch]
  signed int Sizeb; // [esp+20h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)pDwArg2, Size);
  v6 = 0;
  if ( Size >= 4 )
  {
    v6 = 4;
    *(this + 181) = (float)*pDwArg2;
  }
  if ( Size - v6 >= 2 )
  {
    *((uint32_t *)this + 244) = *(int16_t *)((char *)pDwArg2 + v6);
    v6 += 2;
  }
  if ( Size - v6 >= 2 )
  {
    *((uint32_t *)this + 245) = *(int16_t *)((char *)pDwArg2 + v6);
    v6 += 2;
  }
  if ( Size - v6 >= 2 )
  {
    *((uint32_t *)this + 246) = *(int16_t *)((char *)pDwArg2 + v6);
    v6 += 2;
  }
  if ( Size - v6 >= 4 )
  {
    *((uint32_t *)this + 247) = *(int *)((char *)pDwArg2 + v6);
    v6 += 4;
  }
  if ( Size - v6 >= 4 )
  {
    *((uint32_t *)this + 248) = *(int *)((char *)pDwArg2 + v6);
    v6 += 4;
  }
  Sizea = -31072;
  v13 = 5;
  if ( Size - v6 >= 2 )
  {
    Sizea = *(uint16_t *)((char *)pDwArg2 + v6);
    v6 += 2;
  }
  if ( Size - v6 >= 1 )
    v13 = *((uint8_t *)pDwArg2 + v6);
  pThis_F3 = *((uint32_t *)this + 243);
  if ( pThis_F3 != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_F3 + 672))(pThis_F3, 3);
    v12 = sub_41A5E0(v8 + 984);
    v9 = Sizea;
    if ( (int)(uint64_t)((double)v12 * COERCE_FLOAT(sub_41A5E0(v8 + 998))) > Sizea )
    {
      pThis_F32 = (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)this + 243) + 672))(*((uint32_t *)this + 243), 3);
      Sizeb = sub_41A5E0(pThis_F32 + 984);
      *(this + 181) = ((double)(int)((uint64_t)((double)Sizeb * COERCE_FLOAT(sub_41A5E0(pThis_F32 + 998))) - v9)
                     * (double)v13
                     * 0.000001
                     + 1.0)
                    * *(this + 181);
    }
  }
  return (*(int (/*thiscall*/ **)(float *, float *))(*(uint32_t *)this + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x611180 CNBodyHit__vmt160
// ------------------------------------------------------------
int /*thiscall*/ CNBodyHit__vmt160(int *this)
{
  int result; // eax

  IRDCollisionObject__vmt160(this);
  result = *(this + 243);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 356))(this, *(this + 243));
  return result;
}



// ------------------------------------------------------------
// 0x6111A0 sub_6111A0
// ------------------------------------------------------------
void /*thiscall*/ sub_6111A0(int *this, int nArg2)
{
  int fld_e30; // esi

  *(this + 251) = nArg2;
  if ( nArg2 == 1 )
  {
    fld_e30 = *(this + 30);
    if ( *(uint32_t *)(fld_e30 + 148) == -1 )
      sub_4938F0(*(this + 30));
    if ( *(uint32_t *)(fld_e30 + 120) != 0 )
      j__free(*(void **)(fld_e30 + 120));
    *(uint32_t *)(fld_e30 + 120) = 0;
    *(uint32_t *)(fld_e30 + 124) = 0;
    *(uint32_t *)(fld_e30 + 128) = 0;
  }
}



// ------------------------------------------------------------
// 0x611200 sub_611200
// ------------------------------------------------------------
// 投技摔击动画选择：字符串证据「Wall | Floor」+「Character/Fighter/Effect/Animation/ThrowEnemy%s%d.ani」——
// 摔墙/摔地二分支 × 动画编号（格式化路径拼接）——柔道家投技的落点动画矩阵（dword_796E50 路径根）。
int /*userpurge*/ sub_611200@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>, char pszArg4)
{
  int *pDwArg12; // edi
  int result; // eax
  const char *v6; // eax
  int v7; // eax
  int v8; // ebx
  char *v9; // eax
  int pObj; // esi
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  float v16; // [esp+4h] [ebp-A0h]
  int v18; // [esp+Ch] [ebp-98h]
  int v19; // [esp+10h] [ebp-94h]
  char Buffer[128]; // [esp+14h] [ebp-90h] BYREF
  int dword_796E502; // [esp+94h] [ebp-10h]
  int v22; // [esp+A0h] [ebp-4h]

  pDwArg12 = pDwArg1;
  dword_796E502 = dword_796E50;
  result = pDwArg1[243];
  if ( result != 0 )
  {
    v19 = 0;
    v16 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 192))(result) * 0.0062500001;
    do
    {
      v6 = "Wall";
      if ( pszArg4 == 0 )
        v6 = "Floor";
      sprintf(Buffer, "Character/Fighter/Effect/Animation/ThrowEnemy%s%d.ani", v6, v19);
      v7 = sub_42FCB0(228);
      v8 = 0;
      v22 = 0;
      if ( v7 != 0 )
        v8 = sub_431860(v7, Buffer, 1);
      v22 = -1;
      sub_4922F0(v16);
      v9 = (char *)sub_44B6C0(284);
      pObj = (int)v9;
      v22 = 1;
      if ( v9 != nullptr )
      {
        sub_44E0D0(v9, v8, 1);
        *(uint32_t *)pObj = &vftbl_CNRDPooledObject;
      }
      else
      {
        pObj = 0;
      }
      v22 = -1;
      if ( pszArg4 != 0 || v19 == 0 )
      {
        sub_45FE80(pDwArg12[29], (int)pDwArg12, 2, 0, pObj, pDwArg12[243], 1);
      }
      else
      {
        *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 36))(pObj) + 8) = 2;
        sub_45FE80(pDwArg12[29], (int)pDwArg12, 2, 0, pObj, 0, 0);
      }
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 148))(pObj, pDwArg12[252], nArg3, nArg2);
      v11 = *(uint32_t *)pObj;
      if ( pszArg4 != 0 )
      {
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg12[243] + 192))(pDwArg12[243]) / 2;
        v12 = (*(int (/*thiscall*/ **)(int *))(*pDwArg12 + 128))(pDwArg12);
        pDwArg12 = pDwArg1;
        nArg2 = v12 + v18;
        v13 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);
      }
      else
      {
        nArg2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg12 + 128))(pDwArg12);
        v13 = (*(int (/*thiscall*/ **)(int *))(*pDwArg12 + 124))(pDwArg12);
      }
      nArg3 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg12 + 120))(pDwArg12, v13);
      (*(void (/*thiscall*/ **)(int))(v11 + 112))(pObj);
      result = ++v19;
    }
    while ( v19 < 3 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x611400 CNBodyHit__vmt14C
// ------------------------------------------------------------
// CNBodyHit 主循环槽（vmt14C，219 行）：sub_492E80/sub_4938F0（动画族）+ sub_4E5F70（硬直率掷）+
// sub_6111A0/611200（摔击动画选择）+ sub_600890（出生播音）——
// 抓投过程中身体判定盒的跟随与伤害结算主流程（柔道/摔技系共用）。
void /*thiscall*/ sub_611400(uint32_t *this)  // 【CNBodyHit__vmt14C】
{
  int fld_e243; // ecx
  int v3; // ebx
  int fld_e2432; // edi
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int fld_e2433; // eax
  int fld_e2434; // edi
  char v12; // bl
  double fld_e247; // st7
  int fld_e2435; // ecx
  int v15; // eax
  int fld_e2436; // ecx
  int v17; // eax
  int fld_e2437; // edi
  int v19; // ebx
  int v20; // eax
  int fld_e2438; // ecx
  int v22; // edx
  int v23; // eax
  double fld_e248; // st7
  int fld_e2439; // ecx
  int v26; // eax
  int fld_e24310; // ecx
  int v28; // eax
  int fld_e24311; // ecx
  int v30; // eax
  int fld_e24312; // edx
  int v32; // [esp-Ch] [ebp-50h]
  float v33; // [esp+4h] [ebp-40h] BYREF
  float v34; // [esp+8h] [ebp-3Ch]
  float v35; // [esp+Ch] [ebp-38h]
  int v36; // [esp+10h] [ebp-34h]
  int v37; // [esp+14h] [ebp-30h]
  int v38; // [esp+18h] [ebp-2Ch]
  float v39; // [esp+1Ch] [ebp-28h] BYREF
  float v40; // [esp+20h] [ebp-24h]
  float v41; // [esp+24h] [ebp-20h] BYREF
  int v42; // [esp+28h] [ebp-1Ch]
  int v43; // [esp+2Ch] [ebp-18h]
  int v44; // [esp+30h] [ebp-14h]
  int fld_e24322; // [esp+34h] [ebp-10h] BYREF
  int v46; // [esp+40h] [ebp-4h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  fld_e243 = *(this + 243);
  if ( fld_e243 == 0 )
    goto LABEL_46;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e243 + 840))(fld_e243) != 4
    || (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 952))(*(this + 243)) == 2 )
  {
    if ( *((uint8_t *)this + 996) == 0 )
      return;
LABEL_46:
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    return;
  }
  if ( *(this + 251) != 0 )
    return;
  v3 = *this;
  fld_e2432 = *(this + 243);
  v5 = *(uint32_t *)fld_e2432;
  fld_e24322 = fld_e2432;
  v6 = (*(int (**)(void))(v5 + 128))();
  v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e2432 + 124))(fld_e2432, v6);
  v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e2432 + 120))(fld_e2432, v7);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v3 + 112))(this, v8);
  v9 = *this;
  fld_e2433 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 152))(*(this + 243));
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 148))(this, fld_e2433);
  if ( *((uint8_t *)this + 996) == 0 )
  {
    *(this + 252) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    if ( *(this + 246) == -1 )
      *(this + 246) = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243));
    *((uint8_t *)this + 996) = 1;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243)) > 0 )
    *((uint8_t *)this + 997) = 1;
  if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 200))(*(this + 243)) != 0 )
  {
    fld_e2434 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 200))(*(this + 243));
    if ( *(uint32_t *)(fld_e2434 + 148) != *(this + 250) )
    {
      sub_4938F0(*(this + 30));
      v32 = sub_42F220(fld_e2434) + 72;
      sub_42F220(*(this + 30));
      sub_492E80(v32);
      *(this + 250) = *(uint32_t *)(fld_e2434 + 148);
    }
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 308))(*(this + 243)) != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 60))(*(this + 243)) + 184) == 4
      && (*(this + 244) != 0 || *(this + 247) != 0) )
    {
      sub_6111A0(1);
      v12 = 0;
      if ( *(this + 247) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));
        fld_e247 = (double)(int)*(this + 247);
        fld_e2435 = *(this + 243);
        v39 = 0.0;
        *((float *)this + 97) = fld_e247;
        v40 = 0.0;
        v41 = 0.0;
        v42 = 0;
        v43 = 0;
        v44 = 0;
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2435 + 120))(fld_e2435);
        fld_e2436 = *(this + 243);
        fld_e24322 = v15;
        v39 = (float)v15;
        v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2436 + 124))(fld_e2436);
        fld_e2437 = *(this + 243);
        fld_e24322 = v17;
        v40 = (float)v17;
        v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2437 + 192))(fld_e2437) / 2;
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2437 + 128))(fld_e2437);
        fld_e2438 = *(this + 243);
        fld_e24322 = v20 + v19;
        v41 = (float)(v20 + v19);
        sub_4E5F70(v20 + v19, (int)this, fld_e2438, &v39, 1, 0);
        v12 = 1;
      }
      if ( *(this + 244) != 0
        && ((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243)) >= *(this + 246)
         || *(float *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 60))(*(this + 243)) + 24) >= 0.0) )
      {
        v42 = 0;
        v43 = 0;
        v44 = 0;
        v22 = *this;
        v46 = 0;
        v23 = (*(int (/*thiscall*/ **)(uint32_t *))(v22 + 152))(this);
        fld_e24322 = sub_432E50(v23);
        sub_431230((int)&v41, &fld_e24322);
        fld_e24322 = 0;
        sub_431230((int)&v41, &fld_e24322);
        fld_e24322 = 1;
        sub_431230((int)&v41, &fld_e24322);
        sub_431230((int)&v41, this + 245);
        sub_431230((int)&v41, this + 244);
        (*(void (/*thiscall*/ **)(uint32_t, int, float *, int, uint32_t))(*(uint32_t *)*(this + 243) + 560))(
          *(this + 243),
          4,
          &v41,
          2,
          0);
        v46 = -1;
        sub_5E5260((void **)&v41);
LABEL_24:
        sub_611200(1);
        return;
      }
      if ( v12 != 0 )
        goto LABEL_24;
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243)) == 0
           && *(this + 248) != 0
           && *((uint8_t *)this + 997) != 0 )
    {
      sub_6111A0(1);
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152);
      fld_e248 = (double)(int)*(this + 248);
      fld_e2439 = *(this + 243);
      v33 = 0.0;
      *((float *)this + 97) = fld_e248;
      v34 = 0.0;
      v35 = 0.0;
      v36 = 0;
      v37 = 0;
      v38 = 0;
      v26 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2439 + 120))(fld_e2439);
      fld_e24310 = *(this + 243);
      fld_e24322 = v26;
      v33 = (float)v26;
      v28 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e24310 + 124))(fld_e24310);
      fld_e24311 = *(this + 243);
      fld_e24322 = v28;
      v34 = (float)v28;
      v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e24311 + 128))(fld_e24311);
      fld_e24312 = *(this + 243);
      fld_e24322 = v30;
      v35 = (float)v30;
      sub_4E5F70(v3, (int)this, fld_e24312, &v33, 1, 0);
      sub_611200(0);
    }
  }
  else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != *(this + 252)
         && (*(this + 244) != 0 || *(this + 247) != 0) )
  {
    sub_6111A0(1);
    if ( *(this + 247) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));
      *((float *)this + 97) = (float)(int)*(this + 247);
    }
    if ( *(this + 244) != 0
      && ((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243)) >= *(this + 246)
       || *(float *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 60))(*(this + 243)) + 24) >= 0.0) )
    {
      goto LABEL_24;
    }
  }
  else if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243)) == 0
         && *(this + 248) != 0
         && *((uint8_t *)this + 997) != 0 )
  {
    sub_6111A0(1);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152);
    *((float *)this + 97) = (float)(int)*(this + 248);
    sub_611200(0);
  }
}


// ------------------------------------------------------------
// 0x611980 sub_611980
// ------------------------------------------------------------
int /*thiscall*/ sub_611980(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint8_t *)(this + 993) = 0;
  *(uint8_t *)(this + 994) = 0;
  *(uint8_t *)(this + 1021) = 0;
  *(uint8_t *)(this + 1022) = 0;
  *(uint8_t *)(this + 1049) = 0;
  *(uint8_t *)(this + 1050) = 0;
  *(uint8_t *)(this + 1077) = 0;
  *(uint8_t *)(this + 1078) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6119C0 sub_6119C0
// ------------------------------------------------------------
void /*thiscall*/ sub_6119C0(void **this)
{
  if ( *(this + 244) != nullptr )
    j__free(*(this + 244));
  *(this + 244) = nullptr;
}



// ------------------------------------------------------------
// 0x6119F0 sub_6119F0
// ------------------------------------------------------------
// 投技表现参数装载（92 行）：sub_423A20（UDP 广播）+ sub_45EBE0（飘字参数）+ dword_796E50 ——
// 【推断：投技命中点的广播与飘字装配】。
int /*thiscall*/ sub_6119F0(uint8_t *this)
{
  int result; // eax
  int pThis_1D; // eax
  int v4; // eax
  int v5; // edx
  int v6; // eax
  const void *v7; // eax
  int v8; // edx
  int pThis_7C; // eax
  int v10; // edx
  int v11; // esi
  int v12; // esi
  int pThis_30; // eax
  int v14; // esi
  int pThis_34; // eax
  int v16; // eax
  int pThis_3C; // eax
  int v18; // [esp+4h] [ebp-74h]
  int v19; // [esp+8h] [ebp-70h] BYREF
  int pThis_7C2; // [esp+Ch] [ebp-6Ch] BYREF
  uint32_t v21[26]; // [esp+10h] [ebp-68h] BYREF

  v21[25] = dword_796E50;
  sub_423A20((int)v21);
  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 88))(this);
    if ( (uint8_t)result != 0 && *(this + 264) != 1 )
    {
      pThis_1D = sub_45EBE0(*((uint32_t **)this + 29), *((uint32_t *)this + 273), *((uint32_t *)this + 274));
      v4 = __RTDynamicCast(pThis_1D, 0, &CNRDObject `RTTI Type Descriptor', &IRDCollisionObject `RTTI Type Descriptor', 0);
      v5 = *(uint32_t *)this;
      v18 = v4;
      if ( v4 != 0 )
      {
        v6 = (*(int (/*thiscall*/ **)(uint8_t *))(v5 + 60))(this);
        v7 = (const void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v6 + 104) + 16))(*(uint32_t *)(v6 + 104));
        v8 = *(uint32_t *)this;
        qmemcpy(v21, v7, 0x62u);
        v19 = (*(int (/*thiscall*/ **)(uint8_t *))(v8 + 120))(this);
        pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this);
        v10 = *(uint32_t *)this;
        pThis_7C2 = pThis_7C;
        v11 = (*(int (/*thiscall*/ **)(uint8_t *))(v10 + 128))(this);
        if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)this + 136))(this, v19, pThis_7C2, 0) != 0
          || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint8_t *, int *, int *, int, int, int, int, int))(*(uint32_t *)this + 140))(
                                this,
                                &v19,
                                &pThis_7C2,
                                v19,
                                pThis_7C2,
                                100,
                                1,
                                1)) != 0 )
        {
          v21[18] = (uint64_t)((double (/*thiscall*/ *)(uint8_t *, int, uint32_t))*(uint32_t *)(*(uint32_t *)this + 164))(
                                        this,
                                        v18,
                                        0);
          *(uint32_t *)((char *)&v21[3] + 3) = *((uint32_t *)this + 276);
          *(uint32_t *)((char *)&v21[4] + 3) = *(uint32_t *)((char *)&v21[3] + 3);
          v21[0] = v19;
          v21[1] = pThis_7C2;
          v21[2] = v11;
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
          v12 = *(uint32_t *)dword_8F8520;
          pThis_30 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 48))(this);
          (*(void (/*thiscall*/ **)(int, int))(v12 + 36))(dword_8F8520, pThis_30);
          v14 = *(uint32_t *)dword_8F8520;
          pThis_34 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 52))(this);
          (*(void (/*thiscall*/ **)(int, int))(v14 + 36))(dword_8F8520, pThis_34);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
          (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v21, 98);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
          return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        }
      }
      else
      {
        v16 = (*(int (/*thiscall*/ **)(uint8_t *))(v5 + 60))(this);
        *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v16 + 104) + 16))(*(uint32_t *)(v16 + 104)) + 15) = 0;
        pThis_3C = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 60))(this);
        *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pThis_3C + 104) + 16))(*(uint32_t *)(pThis_3C + 104)) + 19) = 0;
        result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
        if ( (uint8_t)result == 1 )
          return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x611BF0 CNTrackingIceWave__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ CNTrackingIceWave__vmt2BC(int *this, const void *pArg2, size_t Size)
{
  CNRDPassiveObject__vmt2BC((int)pArg2, Size);
  qmemcpy(this + 273, pArg2, 0x1Cu);
  sub_698F90((int)(this + 245), *(this + 275), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  return (*(int (/*thiscall*/ **)(int *, int *))(*this + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x611C40 CNTrackingIceWave__vmt214
// ------------------------------------------------------------
char /*thiscall*/ CNTrackingIceWave__vmt214(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  sub_6119F0(this);
  return CNRDPassiveObject__vmt214(this, nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x611C70 CNTrackingIceWave__vmt14C
// ------------------------------------------------------------
// CNTrackingIceWave 主循环槽（vmt14C，234 行）：字符串证据「ICEWAVE_CREATE」（音效 TAG）。
// sub_4923C0/4926A0（定时器）+ sub_6119F0 + dword_8F82A4/8F82A8/8F82AC（冰浪池化槽三连）+ sub_698F90（时钟复位，P36）——
// 追踪型冰浪（自动寻敌）的推进与池化复用。
void /*usercall*/ sub_611C70(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 【CNTrackingIceWave__vmt14C】
{
  int v4; // edi
  unsigned int v5; // eax
  int v6; // ecx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int pObj2; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  unsigned int i; // edi
  int v19; // ecx
  int pObj3; // edi
  int v21; // eax
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  void *v27; // ecx
  uint32_t *Block2; // edi
  int v29; // ebx
  uint32_t *v30; // eax
  int pObj; // edi
  int v32; // ebx
  int v33; // eax
  int v34; // eax
  int v35; // eax
  void *v36; // ecx
  int v37; // eax
  int v38; // eax
  void *v41; // [esp+4h] [ebp-44h] BYREF
  void *v42; // [esp+8h] [ebp-40h]
  int v43; // [esp+Ch] [ebp-3Ch]
  int v44; // [esp+10h] [ebp-38h]
  uint8_t v45[4]; // [esp+14h] [ebp-34h] BYREF
  void *v46; // [esp+18h] [ebp-30h]
  int v47; // [esp+1Ch] [ebp-2Ch]
  int v48; // [esp+20h] [ebp-28h]
  uint8_t v49[4]; // [esp+24h] [ebp-24h] BYREF
  void *Block; // [esp+28h] [ebp-20h]
  uint32_t *v51; // [esp+2Ch] [ebp-1Ch]
  int v52; // [esp+30h] [ebp-18h]
  int v53; // [esp+34h] [ebp-14h]
  float v54; // [esp+38h] [ebp-10h]
  int v55; // [esp+44h] [ebp-4h]

  if ( *((uint8_t *)pArg1 + 264) != 1 )
  {
    sub_600890();  // 【CNRDPassiveObject__vmt14C】
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) == 1
      && (v4 = pArg1[251], sub_699000((int)(pArg1 + 245)) >= v4) )  // 【clock_now(clk)】
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);
    }
    else
    {
      v5 = sub_699000((int)(pArg1 + 245));  // 【clock_now(clk)】
      if ( v5 >= 0x1F4 )
      {
        v6 = pArg1[275];
        if ( v5 <= v6 - 3000 )
        {
          v54 = 0.5;
        }
        else
        {
          v53 = v6 - v5;
          v54 = (double)(v6 - v5) * 0.00016666666;
        }
      }
      else
      {
        v53 = v5;
        v54 = (double)v5 * 0.001;
      }
      v7 = pArg1[258];
      if ( sub_699000((int)(pArg1 + 252)) >= v7 )  // 【clock_now(clk)】
      {
        Block = nullptr;
        v51 = nullptr;
        v52 = 0;
        v8 = pArg1[36];
        v55 = 0;
        if ( v8 != 0 )
          v9 = (pArg1[37] - v8) >> 2;
        else
          v9 = 0;
        if ( pArg1[243] == v9 )
        {
          v10 = *pArg1;
          pArg1[243] = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v10 + 212))(
            pArg1,
            "ICEWAVE_CREATE",
            -1,
            0,
            0);
        }
        v11 = pArg1[243];
        if ( *(uint32_t *)(pArg1[244] + 4 * v11) == 0 )
        {
          sub_4926A0(*(uint32_t *)(pArg1[36] + 4 * v11));
          sub_4923C0(*(uint32_t **)(pArg1[36] + 4 * pArg1[243]), SLODWORD(v54));
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*pArg1 + 204))(
            pArg1,
            0,
            *(uint32_t *)(pArg1[36] + 4 * pArg1[243]),
            0,
            0,
            0,
            1);
          *(uint32_t *)(pArg1[244] + 4 * pArg1[243]) = 1;
          pObj2 = dword_8F82A4;
          v13 = *(uint32_t *)dword_8F82A4;
          v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
          v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v14);
          v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v15);
          (*(void (/*thiscall*/ **)(int, int))(v13 + 40))(pObj2, v16);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);
          v17 = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj2 + 92))(pObj2, &v41);
          LOBYTE(v55) = 1;
          sub_4E77D0((int)v49, v17);
          LOBYTE(v55) = 0;
          sub_5E5260(&v41);
          sub_4600B0((void *)pArg1[29], 2, 0, (int)v49);
          ++pArg1[243];
          *((uint8_t *)pArg1 + 1021) = 0;
          *((uint8_t *)pArg1 + 1022) = 0;
          sub_698F90((int)(pArg1 + 252), pArg1[277], 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        }
        v55 = -1;
        if ( Block != nullptr )
          j__free(Block);
      }
      for ( i = 0; ; ++i )
      {
        v19 = pArg1[36];
        v53 = i;
        if ( v19 == 0 || i >= (pArg1[37] - v19) >> 2 )
          break;
        if ( *(uint32_t *)(pArg1[244] + 4 * i) == 1 && *(uint8_t *)(*(uint32_t *)(pArg1[36] + 4 * i) + 170) == 1 )
        {
          Block = nullptr;
          v51 = nullptr;
          v52 = 0;
          pObj3 = dword_8F82A8;
          v21 = *pArg1;
          v22 = *(uint32_t *)dword_8F82A8;
          v55 = 2;
          v23 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v21 + 128))(pArg1, nArg2, nArg3);
          v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v23 + 20);
          v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v24);
          (*(void (/*thiscall*/ **)(int, int))(v22 + 40))(pObj3, v25);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj3 + 12))(pObj3, 0);
          v26 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj3 + 92))(pObj3, v45);
          LOBYTE(v55) = 3;
          sub_4E77D0((int)v49, v26);
          LOBYTE(v55) = 2;
          if ( v46 != nullptr )
            j__free(v46);
          v27 = (void *)pArg1[29];
          v46 = nullptr;
          v47 = 0;
          v48 = 0;
          sub_4600B0(v27, 2, 0, (int)v49);
          Block2 = Block;
          if ( Block != v51 )
          {
            v29 = LODWORD(v54);
            do
            {
              v30 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 200))(*Block2);
              sub_4923C0(v30, v29);
              ++Block2;
            }
            while ( Block2 != v51 );
          }
          pObj = dword_8F82AC;
          v32 = *(uint32_t *)dword_8F82AC;
          nArg3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1) + 20;
          v33 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);
          v34 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v33);
          (*(void (/*thiscall*/ **)(int, int))(v32 + 40))(pObj, v34);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);
          v35 = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj + 92))(pObj, &v41);
          LOBYTE(v55) = 4;
          sub_4E77D0((int)v49, v35);
          LOBYTE(v55) = 2;
          if ( v42 != nullptr )
            j__free(v42);
          v36 = (void *)pArg1[29];
          v42 = nullptr;
          v43 = 0;
          v44 = 0;
          sub_4600B0(v36, 2, 0, (int)v49);
          i = v53;
          nArg2 = *(uint32_t *)(pArg1[36] + 4 * v53);
          (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 208))(pArg1);
          *(uint32_t *)(pArg1[244] + 4 * i) = 0;
          v55 = -1;
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          v51 = nullptr;
          v52 = 0;
        }
      }
      v53 = pArg1[272];
      v37 = sub_699000((int)(pArg1 + 266));  // 【clock_now(clk)】
      if ( v37 >= v53 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 352))(pArg1);
        *((uint8_t *)pArg1 + 1077) = 0;
        *((uint8_t *)pArg1 + 1078) = 0;
        sub_698F90((int)(pArg1 + 266), pArg1[278], 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
      v53 = pArg1[265];
      v38 = sub_699000((int)(pArg1 + 259));  // 【clock_now(clk)】
      if ( v38 >= v53 )
      {
        sub_6119F0(pArg1);
        *((uint8_t *)pArg1 + 1049) = 0;
        *((uint8_t *)pArg1 + 1050) = 0;
        sub_698F90((int)(pArg1 + 259), pArg1[279], 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
    }
  }
}


// ------------------------------------------------------------
// 0x6120F0 sub_6120F0
// ------------------------------------------------------------
// 冰浪路径粒子：字符串证据「PassiveObject/Monster/Soldier/Particle/IceWaveMovePath.ptl」
// （资源路径直证：冰浪 PO 归属 Monster/Soldier 系）+ sub_445B90/sub_445D00（156B 粒子分配，研究 20 P36 ⑤ 直证）+
// sub_4A0B60 —— 冰浪移动轨迹的粒子铺设。
int /*thiscall*/ sub_6120F0(int this, int nArg2)
{
  int fld_90; // ecx
  char *pObj2; // ebx
  int fld_94; // eax
  unsigned int pBuf; // edi
  void *pMem; // eax
  uint32_t *pMem2; // eax
  int (/*thiscall*/ ***v9)(void *, int); // esi
  char *v10; // eax
  const void *v11; // esi
  int pObj; // esi
  uint32_t *v13; // edi
  int v14; // edi
  int v15; // edi
  int v17; // [esp+0h] [ebp-24h]
  int pThis; // [esp+10h] [ebp-14h]
  int (/*thiscall*/ ***Block)(void *, int); // [esp+14h] [ebp-10h]

  *(uint8_t *)(this + 700) = 0;
  *(uint8_t *)(this + 701) = 1;
  fld_90 = *(uint32_t *)(this + 144);
  pObj2 = nullptr;
  pThis = this;
  if ( fld_90 != 0 )
    fld_94 = (*(uint32_t *)(this + 148) - fld_90) >> 2;
  else
    fld_94 = 0;
  pBuf = 4 * fld_94;
  pMem = operator new(4 * fld_94);
  *(uint32_t *)(this + 976) = pMem;
  memset(pMem, 0, pBuf);
  pMem2 = operator new(0x12Cu);
  if ( pMem2 != nullptr )
  {
    v9 = (int (/*thiscall*/ ***)(void *, int))sub_428F30(
                                              pMem2,
                                              (int)"PassiveObject/Monster/Soldier/Particle/IceWaveMovePath.ptl",
                                              0);
    Block = v9;
  }
  else
  {
    Block = nullptr;
    v9 = nullptr;
  }
  v10 = (char *)sub_445D00(156);
  if ( v10 != nullptr )
    pObj2 = sub_445B90(v10);
  v11 = (const void *)((int (/*thiscall*/ *)(int (/*thiscall*/ ***)(void *, int)))(*v9)[7])(v9);
  qmemcpy((void *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj2 + 16))(pObj2), v11, 0x62u);
  pObj = pThis;
  v13 = (uint32_t *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj2 + 16))(pObj2);
  *v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis + 120))(pThis);
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj2 + 16))(pObj2) + 4) = v14;
  v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj2 + 16))(pObj2) + 8) = v15;
  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj + 60))(pObj, pObj2);
  sub_4A0B60(v17);
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pObj2 + 4))(pObj2, 0);
  return (**Block)(Block, 1);
}



// ------------------------------------------------------------
// 0x612250 sub_612250
// ------------------------------------------------------------
int /*thiscall*/ sub_612250(uint32_t *this)
{
  *(this + 253) = 1065353216;
  *(this + 254) = 1065353216;
  return 1065353216;
}



// ------------------------------------------------------------
// 0x612270 sub_612270
// ------------------------------------------------------------
char /*thiscall*/ sub_612270(int this, int nArg2)
{
  *(float *)(this + 724) = (float)nArg2;
  return sub_607260((uint32_t *)(this + 992), 300, -1, 1, 1);
}



// ------------------------------------------------------------
// 0x6122A0 CNSingleIceWave__vmt2BC
// ------------------------------------------------------------
// CNSingleIceWave 命中结算槽（vmt2BC）：sub_4922F0 + dword_78FE30/34（全局攻击上下文）——
// 单体冰浪的命中结算。
int /*thiscall*/ CNSingleIceWave__vmt2BC(float *this, uint16_t *uArg2, int Size)
{
  int result; // eax
  uint16_t v6; // di
  unsigned int i; // edi
  int pThis_24; // ecx
  int v9; // edx
  double v10; // st7
  float Sizea; // [esp+18h] [ebp+Ch]

  result = CNRDPassiveObject__vmt2BC((int)uArg2, Size);
  dword_78FE30 = (int)uArg2;
  dword_78FE34 = 0;
  if ( Size > 0 )
  {
    v6 = *uArg2;
    dword_78FE34 = 2;
    Sizea = (double)v6 * 0.0099999998;
    *(this + 253) = Sizea;
    sub_4922F0(Sizea);
    for ( i = 0; ; ++i )
    {
      pThis_24 = *((uint32_t *)this + 36);
      if ( pThis_24 == 0 || i >= (*((uint32_t *)this + 37) - pThis_24) >> 2 )
        break;
      sub_4922F0(*(this + 253));
    }
    result = dword_78FE34;
    if ( dword_78FE34 < Size )
    {
      v9 = *(uint32_t *)(dword_78FE34 + dword_78FE30);
      dword_78FE34 += 4;
      v10 = *(float *)(result + 4 + dword_78FE30);
      dword_78FE34 = result + 8;
      *((uint32_t *)this + 190) = v9;
      *((uint32_t *)this + 193) = (uint64_t)v10;
      return (*(int (/*fastcall*/ **)(float *, uint32_t, float *))(*(uint32_t *)this + 344))(
               this,
               (uint64_t)v10 >> 32,
               this + 181);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x612390 CNSingleIceWave__vmt14C
// ------------------------------------------------------------
// CNSingleIceWave 主循环槽（vmt14C，161 行）：字符串证据「ICEWAVE_CREATE」。
// sub_4922F0/sub_493D00（速率写者，P38）+ sub_4E77D0 + sub_607260/6072C0 + dword_8F82A4/A8/AC ——
// 单体冰浪的推进（速率控制浪宽）。
uint32_t */*thiscall*/ sub_612390(int *this)  // 【CNSingleIceWave__vmt14C】
{
  int fld_e28; // ecx
  int v3; // edi
  int v4; // eax
  int pThis_9; // eax
  int fld_e36; // edx
  unsigned int fld_e37; // ecx
  int fld_e362; // edi
  int pObj; // edi
  float v10; // edx
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int pObj3; // edi
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  uint32_t *v22; // edi
  int pObj2; // edi
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  void *fld_e29; // ecx
  int pThis_92; // eax
  uint32_t *fld_e32; // ecx
  uint32_t *result; // eax
  float pThis_FE; // [esp+0h] [ebp-40h]
  float pThis_FD; // [esp+0h] [ebp-40h]
  uint8_t v35[4]; // [esp+10h] [ebp-30h] BYREF
  void *Block; // [esp+14h] [ebp-2Ch]
  int v37; // [esp+18h] [ebp-28h]
  int v38; // [esp+1Ch] [ebp-24h]
  uint8_t v39[4]; // [esp+20h] [ebp-20h] BYREF
  void *v40; // [esp+24h] [ebp-1Ch]
  uint32_t *v41; // [esp+28h] [ebp-18h]
  int v42; // [esp+2Ch] [ebp-14h]
  int v43; // [esp+30h] [ebp-10h]
  int v44; // [esp+3Ch] [ebp-4h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  if ( *(this + 247) == 0 )
  {
    fld_e28 = *(uint32_t *)(*(this + 28) + 104);
    v3 = 100;
    if ( fld_e28 != 0 )
    {
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e28 + 16))(fld_e28);
      v3 = (uint64_t)sub_4049C0(200.0, 50.0, *(uint32_t *)(v4 + 15) - 100, 900);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v43 = 200 / v3;
      *((float *)this + 254) = (float)(200 / v3);
    }
    sub_607260(v3, -1, 1, 1);
  }
  pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  if ( (uint8_t)sub_6072C0(pThis_9) != 0 )
  {
    fld_e36 = *(this + 36);
    if ( fld_e36 != 0 )
      fld_e37 = (*(this + 37) - fld_e36) >> 2;
    else
      fld_e37 = 0;
    pThis_FE = *((float *)this + 254) * 100.0;
    fld_e362 = *(uint32_t *)(*(this + 36) + 4 * (*(this + 247) % fld_e37));
    sub_493D00(fld_e362, pThis_FE);
    (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(this, 1, fld_e362, 0, 0, 0, 0);
    v40 = nullptr;
    v41 = nullptr;
    v42 = 0;
    pObj = dword_8F82A4;
    v10 = *(float *)this;
    v44 = 0;
    v11 = *(uint32_t *)dword_8F82A4;
    v12 = (*(int (/*thiscall*/ **)(int *))(LODWORD(v10) + 128))(this);
    v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v12);
    v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13);
    (*(void (/*thiscall*/ **)(int, int))(v11 + 40))(pObj, v14);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);
    v15 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj + 92))(pObj, v35);
    LOBYTE(v44) = 1;
    sub_4E77D0((int)v39, v15);
    LOBYTE(v44) = 0;
    if ( Block != nullptr )
      j__free(Block);
    sub_4600B0((void *)*(this + 29), 2, 0, (int)v39);
    if ( *(this + 247) != 0 )
    {
      pObj3 = dword_8F82A8;
      v17 = *(uint32_t *)dword_8F82A8;
      v18 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v18 + 20);
      v20 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v19);
      (*(void (/*thiscall*/ **)(int, int))(v17 + 40))(pObj3, v20);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj3 + 12))(pObj3, 0);
      v21 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj3 + 92))(pObj3, v35);
      LOBYTE(v44) = 2;
      sub_4E77D0((int)v39, v21);
      LOBYTE(v44) = 0;
      if ( Block != nullptr )
        j__free(Block);
      sub_4600B0((void *)*(this + 29), 2, 0, (int)v39);
      v22 = v40;
      if ( v40 != v41 )
      {
        do
        {
          pThis_FD = *((float *)this + 253);
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v22 + 200))(*v22);
          sub_4922F0(pThis_FD);
          ++v22;
        }
        while ( v22 != v41 );
      }
      pObj2 = dword_8F82AC;
      v24 = *(uint32_t *)dword_8F82AC;
      v25 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v26 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v25 + 20);
      v27 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v26);
      (*(void (/*thiscall*/ **)(int, int))(v24 + 40))(pObj2, v27);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);
      v28 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj2 + 92))(pObj2, v35);
      LOBYTE(v44) = 3;
      sub_4E77D0((int)v39, v28);
      LOBYTE(v44) = 0;
      if ( Block != nullptr )
        j__free(Block);
      fld_e29 = (void *)*(this + 29);
      Block = nullptr;
      v37 = 0;
      v38 = 0;
      sub_4600B0(fld_e29, 2, 0, (int)v39);
    }
    v44 = -1;
    if ( v40 != nullptr )
      j__free(v40);
    v40 = nullptr;
    v41 = nullptr;
    v42 = 0;
  }
  pThis_92 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  if ( (uint8_t)sub_6072C0(pThis_92) != 0 )
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ICEWAVE_CREATE", -1, 0, 0);
  fld_e32 = (uint32_t *)*(this + 32);
  result = (uint32_t *)*fld_e32;
  if ( (uint32_t *)*fld_e32 != fld_e32 )
  {
    while ( *(uint8_t *)(result[3] + 170) == 0 )
    {
      result = (uint32_t *)*result;
      if ( result == (uint32_t *)*(this + 32) )
        return result;
    }
    return (uint32_t *)(*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, result[3]);
  }
  return result;
}


// ------------------------------------------------------------
// 0x6126D0 sub_6126D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6126D0(int this)
{
  *(uint32_t *)(this + 1100) = 0;
  *(uint32_t *)(this + 1104) = 0;
  *(uint32_t *)(this + 1108) = 0;
  *(uint8_t *)(this + 1125) = 0;
  *(uint8_t *)(this + 1126) = 0;
  *(uint8_t *)(this + 1140) = 1;
  return 0;
}



// ------------------------------------------------------------
// 0x612700 sub_612700
// ------------------------------------------------------------
int /*thiscall*/ sub_612700(int *this, int nArg2)
{
  int v3; // eax
  int result; // eax

  if ( nArg2 == 833 )
  {
    v3 = *this;
    *(this + 275) = 1;
    result = (*(int (/*stdcall*/ **)(int))(v3 + 384))(8);
    *(this + 277) = result;
  }
  else
  {
    *(this + 275) = 0;
    *(this + 277) = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x612750 CNEventBarrier__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNEventBarrier__vmt200(int *this, int nArg2, float *pArg3, char pszArg4)
{
  return CNRDPassiveObject__vmt200(this, nArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x612770 CNEventBarrier__vmt14C
// ------------------------------------------------------------
// CNEventBarrier 主循环槽（vmt14C，118 行）：sub_60B6B0（物件族，与 CNMapObject 共享）+ sub_4E4A50 +
// sub_698F90/699000（时钟复位/读数）——事件屏障（副本机关墙）的开合状态机。
char /*usercall*/ sub_612770@<al>(uint8_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // eax
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // edi
  unsigned int i; // edi
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edx
  uint32_t *v15; // eax
  uint8_t *pObj; // eax
  int v17; // edi
  int v18; // eax
  int v20; // [esp-20h] [ebp-24h]
  int v21; // [esp-1Ch] [ebp-20h]
  int v22; // [esp-18h] [ebp-1Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 316))(pArg1) == 1 )
  {
    LOBYTE(v3) = sub_60B6B0(pArg1);  // 【CNMapObject__vmt14C】
    return v3;
  }
  if ( pArg1[1140] == 1 )
  {
    if ( *((uint32_t *)pArg1 + 275) == 1 )
      v4 = 500;
    else
      v4 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 8);
    sub_698F90((int)(pArg1 + 1112), v4, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    pArg1[1140] = 0;
  }
  v3 = *((uint32_t *)pArg1 + 276);
  if ( v3 != 0 )
  {
    if ( v3 == 1 )
    {
      v17 = *((uint32_t *)pArg1 + 284);
      v3 = sub_699000((int)(pArg1 + 1112));  // 【clock_now(clk)】
      if ( v3 >= v17 )
      {
        LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1);
        if ( (uint8_t)v3 == 1 )
        {
          v22 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 128))(pArg1) - 10;
          v21 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 124))(pArg1);
          v20 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 120))(pArg1);
          v18 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 384))(pArg1);
          sub_4E4A50(pArg1, 40008, v18, 9, v20, v21, v22, 4, 0, 0);
          LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 312))(pArg1, 0, 0);
          *((uint32_t *)pArg1 + 276) = 2;
        }
      }
    }
  }
  else
  {
    v3 = *((uint32_t *)pArg1 + 275);
    if ( v3 == 0 )
    {
      v5 = *((uint32_t *)pArg1 + 284);
      v3 = sub_699000((int)(pArg1 + 1112));  // 【clock_now(clk)】
      if ( v3 < v5 )
        return v3;
LABEL_11:
      *((uint32_t *)pArg1 + 276) = 1;
      pArg1[1125] = 0;
      pArg1[1126] = 0;
      v6 = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t))(*(uint32_t *)pArg1 + 384))(pArg1, 7, 0);
      sub_698F90((int)(pArg1 + 1112), v6, nArg2);  // 【clock_set_countdown(clk, duration=a2, star…】
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, **((uint32_t **)pArg1 + 36));
      return v3;
    }
    if ( v3 == 1 )
    {
      v7 = *((uint32_t *)pArg1 + 284);
      v3 = sub_699000((int)(pArg1 + 1112));  // 【clock_now(clk)】
      if ( v3 >= v7 )
      {
        for ( i = 0; ; ++i )
        {
          v9 = *((uint32_t *)pArg1 + 29);
          v10 = *(uint32_t *)(v9 + 8);
          v11 = v9 + 4;
          v12 = v10 != 0 ? (*(uint32_t *)(v11 + 8) - v10) >> 2 : 0;
          if ( (int)i >= v12 )
            break;
          v13 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 80))(pArg1);
          v14 = *(uint32_t *)(v13 + 8);
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 12) - v14) >> 2 )
            v15 = *(uint32_t **)(v14 + 4 * i);
          else
            v15 = nullptr;
          pObj = __RTDynamicCast(
                  v15,
                  0,
                  &CNRDObject `RTTI Type Descriptor',
                  &CNRDPassiveObject `RTTI Type Descriptor',
                  0);
          if ( pObj != pArg1
            && pObj != nullptr
            && *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 340))(pObj) == *((uint32_t *)pArg1 + 277) )
          {
            pArg1[1125] = 0;
            pArg1[1126] = 0;
            LOBYTE(v3) = sub_698F90((int)(pArg1 + 1112), 500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
            return v3;
          }
        }
        goto LABEL_11;
      }
    }
  }
  return v3;
}


// ------------------------------------------------------------
// 0x6129A0 sub_6129A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6129A0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint8_t *)(this + 980) = 0;
  *(uint8_t *)(this + 981) = 0;
  *(uint8_t *)(this + 982) = 0;
  *(uint32_t *)(this + 984) = 1065353216;
  *(uint8_t *)(this + 988) = 0;
  *(uint8_t *)(this + 989) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6129E0 CNIceWave__vmt2A8
// ------------------------------------------------------------
// CNIceWave 碰撞响应槽（vmt2A8）：sub_47E720/47E9D0/47EF20/47EFD0（命中几何族）+ sub_4924C0 +
// dword_795BE0 —— 冰浪对目标的推移判定【推断：浪推位移】。
char /*thiscall*/ CNIceWave__vmt2A8(int this, int nArg2)
{
  int fld_3D04; // eax
  char *v4; // edi
  int fld_3D0; // ebx
  int v6; // ebx
  int fld_3D02; // eax
  int pThis_184; // eax
  int fld_3D03; // [esp-18h] [ebp-1Ch]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, nArg2);
  LOBYTE(fld_3D04) = *(uint8_t *)(this + 989);
  if ( (uint8_t)fld_3D04 == 0 )
  {
    v4 = (char *)sub_47E720(0, 0x15u);
    fld_3D0 = sub_47EF20(v4, 0, *(uint32_t *)(this + 976), -1, -1, 11);
    v6 = fld_3D0 - *(uint32_t *)(sub_4924C0(0) + 48);
    *(uint32_t *)(sub_4924C0(1) + 48) = v6;
    if ( *(uint32_t *)(this + 972) >= sub_47EF20(v4, 1u, *(uint32_t *)(this + 976), -1, -1, 11) - 1 )
      *(uint8_t *)(this + 980) = 1;
    fld_3D02 = sub_47EF20(v4, 4u, *(uint32_t *)(this + 976), -1, -1, 11);
    fld_3D03 = *(uint32_t *)(this + 976);
    *(float *)(this + 760) = (double)fld_3D02 * 0.1;
    *(uint32_t *)(this + 772) = (uint64_t)(double)sub_47EF20(v4, 5u, fld_3D03, -1, -1, 11);
    if ( dword_795BE0 == -1 )
      dword_795BE0 = sub_47E9D0(v4, 0);
    pThis_184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
    fld_3D04 = sub_47EFD0(v4, COERCE_FLOAT(3), *(uint32_t *)(this + 976), pThis_184, pThis_184, 0);
    *(uint8_t *)(this + 989) = 1;
    *(float *)(this + 724) = (float)fld_3D04;
  }
  return fld_3D04;
}



// ------------------------------------------------------------
// 0x612B10 sub_612B10
// ------------------------------------------------------------
int /*thiscall*/ sub_612B10(int this, int nArg2)
{
  uint16_t nArg22; // cx
  int v5; // [esp+Ch] [ebp+8h]
  float v6; // [esp+Ch] [ebp+8h]

  nArg22 = nArg2;
  v5 = nArg2 >> 16;
  *(uint32_t *)(this + 972) = v5;
  *(uint32_t *)(this + 976) = nArg22;
  v6 = (double)v5 * 0.050000001 + 1.0;
  *(float *)(this + 984) = v6;
  sub_4922F0(v6);
  return sub_4015C0("G_ICEWAVE_MOVING", 0x10u);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x612B70 CNIceWave__vmt14C
// ------------------------------------------------------------
// CNIceWave 主循环槽（vmt14C，198 行）：字符串证据「ICEWAVE_CREATE」。
// sub_4E4A50 + sub_4E77D0 + dword_795BE0 + dword_8F82A4/A8/AC —— 多段冰浪的推进/消亡主流程。
int /*thiscall*/ sub_612B70(int *this)  // 【CNIceWave__vmt14C】
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int pObj3; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *fld_e29; // ecx
  uint32_t *Block2; // edi
  uint32_t *v12; // eax
  double fld_e243; // st7
  int v14; // ebx
  int v15; // edi
  int v16; // ebx
  int v17; // eax
  int fld_e30; // eax
  float v19; // edx
  int v20; // ebx
  int v21; // edi
  int fld_e2432; // eax
  int v23; // eax
  int pObj2; // edi
  void *fld_e292; // ecx
  uint32_t *v26; // edi
  uint32_t *v27; // eax
  int v28; // ebx
  int v29; // edi
  int fld_e2433; // eax
  int v31; // eax
  int pObj; // edi
  int v33; // eax
  void *fld_e293; // ecx
  void *v35; // eax
  bool v36; // zf
  int result; // eax
  float pThis_F6; // [esp-4h] [ebp-58h]
  float pThis_F62; // [esp-4h] [ebp-58h]
  uint8_t v40[4]; // [esp+Ch] [ebp-48h] BYREF
  void *v41; // [esp+10h] [ebp-44h]
  int v42; // [esp+14h] [ebp-40h]
  int v43; // [esp+18h] [ebp-3Ch]
  uint8_t v44[4]; // [esp+1Ch] [ebp-38h] BYREF
  void *Block; // [esp+20h] [ebp-34h]
  uint32_t *v46; // [esp+24h] [ebp-30h]
  uint8_t v47[4]; // [esp+2Ch] [ebp-28h] BYREF
  void *v48; // [esp+30h] [ebp-24h]
  uint32_t *v49; // [esp+34h] [ebp-20h]
  int v50; // [esp+38h] [ebp-1Ch]
  int fld_e244; // [esp+3Ch] [ebp-18h]
  int v52; // [esp+40h] [ebp-14h]
  int fld_e71; // [esp+44h] [ebp-10h]
  int v54; // [esp+50h] [ebp-4h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v3);
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v2 + 136))(this, v4) != 0 )
  {
    if ( *((uint8_t *)this + 981) == 0 )
    {
      pObj3 = dword_8F82A4;
      v6 = *(uint32_t *)dword_8F82A4;
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v7);
      v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
      (*(void (/*thiscall*/ **)(int, int))(v6 + 40))(pObj3, v9);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj3 + 12))(pObj3, 0);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj3 + 92))(pObj3, v44);
      fld_e29 = (void *)*(this + 29);
      v54 = 0;
      sub_4600B0(fld_e29, 2, 0, (int)v44);
      Block2 = Block;
      if ( Block != v46 )
      {
        do
        {
          pThis_F6 = *((float *)this + 246);
          v12 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 200))(*Block2);
          sub_4922F0(v12, pThis_F6);
          ++Block2;
        }
        while ( Block2 != v46 );
        Block2 = Block;
      }
      *((uint8_t *)this + 981) = 1;
      v54 = -1;
      if ( Block2 != nullptr )
        j__free(Block2);
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, 0);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    *((uint8_t *)this + 988) = 1;
  }
  if ( *((uint8_t *)this + 988) == 0 )
  {
    if ( *(this + 243) == 0 )
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ICEWAVE_CREATE", -1, 0, 0);
    *((uint8_t *)this + 988) = 1;
  }
  if ( *((uint8_t *)this + 980) == 0 && sub_699000((int)(this + 16)) >= dword_795BE0 )  // 【clock_now(clk)】
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      fld_e71 = *(this + 71) + 1;
      if ( fld_e71 == 20008 )
        fld_e71 = 20002;
      fld_e243 = (double)*(this + 243) * -0.80000001;
      fld_e244 = *(this + 244) | ((uint16_t)(*((uint16_t *)this + 486) + 1) << 16);
      v14 = 14 - (uint64_t)fld_e243;
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )
        v15 = v14 + (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      else
        v15 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - v14;
      if ( *(this + 243) % 2 != 0 )
        v16 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - 8;
      else
        v16 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) + 8;
      v52 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v17 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      sub_4E4A50(v15, *(this + 173), fld_e71, fld_e244, v15, v16, v52, v17, 0, 0, 0);
    }
    *((uint8_t *)this + 980) = 1;
  }
  if ( *((uint8_t *)this + 982) == 0 )
  {
    fld_e30 = *(this + 30);
    if ( fld_e30 != 0 && *(int *)(fld_e30 + 148) >= 3 )
    {
      v19 = *(float *)this;
      v20 = *(uint32_t *)dword_8F82A8;
      fld_e71 = dword_8F82A8;
      v21 = (*(int (/*thiscall*/ **)(int *))(LODWORD(v19) + 128))(this);
      fld_e2432 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(
              this,
              20 - (uint64_t)((double)*(this + 243) * -1.5) + v21);
      v23 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, fld_e2432);
      pObj2 = fld_e71;
      (*(void (/*thiscall*/ **)(int, int))(v20 + 40))(fld_e71, v23);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj2 + 92))(pObj2, v47);
      fld_e292 = (void *)*(this + 29);
      v54 = 1;
      sub_4600B0(fld_e292, 2, 0, (int)v47);
      v26 = v48;
      if ( v48 != v49 )
      {
        do
        {
          pThis_F62 = *((float *)this + 246);
          v27 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v26 + 200))(*v26);
          sub_4922F0(v27, pThis_F62);
          ++v26;
        }
        while ( v26 != v49 );
      }
      v28 = *(uint32_t *)dword_8F82AC;
      fld_e71 = dword_8F82AC;
      v29 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      fld_e2433 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(
              this,
              20 - (uint64_t)((double)*(this + 243) * -1.5) + v29);
      v31 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, fld_e2433);
      pObj = fld_e71;
      (*(void (/*thiscall*/ **)(int, int))(v28 + 40))(fld_e71, v31);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);
      v33 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj + 92))(pObj, v40);
      LOBYTE(v54) = 2;
      sub_4E77D0((int)v47, v33);
      LOBYTE(v54) = 1;
      if ( v41 != nullptr )
        j__free(v41);
      fld_e293 = (void *)*(this + 29);
      v41 = nullptr;
      v42 = 0;
      v43 = 0;
      sub_4600B0(fld_e293, 2, 0, (int)v47);
      v35 = v48;
      v36 = v48 == nullptr;
      *((uint8_t *)this + 982) = 1;
      v54 = -1;
      if ( !v36 )
        j__free(v35);
      v48 = nullptr;
      v49 = nullptr;
      v50 = 0;
    }
  }
  result = *(this + 30);
  if ( result != 0 && *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  return result;
}


// ------------------------------------------------------------
// 0x612F70 sub_612F70
// ------------------------------------------------------------
int /*thiscall*/ sub_612F70(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint8_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 1065353216;
  *(uint8_t *)(this + 984) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x612F90 CNBodyHit__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNBodyHit__vmt12C(uint32_t *this, int nArg2)
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( nArg2 == *(this + 243) )
    *(this + 243) = 0;
}



// ------------------------------------------------------------
// 0x612FC0 CNSuplexSub__vmt2BC
// ------------------------------------------------------------
// CNSuplexSub 命中结算槽（vmt2BC）：sub_47EF20/47EFD0 + sub_4922F0 —— 背摔子判定的结算。
char /*thiscall*/ CNSuplexSub__vmt2BC(uint8_t *this, uint8_t *uArg2, size_t Size)
{
  int v4; // edx
  int v5; // eax
  int pObj; // eax
  int pObj2; // edi
  int v8; // eax
  int v9; // edx
  char *v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v15; // [esp+10h] [ebp+8h]
  float Sizea; // [esp+14h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)uArg2, Size);
  v4 = *(uint32_t *)this;
  *(this + 976) = *uArg2;
  v5 = (*(int (/*thiscall*/ **)(uint8_t *))(v4 + 684))(this);
  pObj = __RTDynamicCast(v5, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNFighter `RTTI Type Descriptor', 0);
  pObj2 = pObj;
  if ( pObj != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1332))(pObj);
    v9 = *(uint32_t *)this;
    *((uint32_t *)this + 243) = v8;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v9 + 356))(this, v8);
    LOBYTE(pObj) = *(this + 976);
    if ( (uint8_t)pObj != 0 )
    {
      v10 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 1160))(pObj2, 22);
      v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 1140))(pObj2, 22);
      Sizea = (double)sub_47EF20(v10, 0, v15, -1, -1, 11) * 0.0099999998;
      *((float *)this + 245) = Sizea;
      sub_4922F0(Sizea);
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 388))(pObj2);
      v12 = sub_47EFD0(v10, COERCE_FLOAT(1), v15, v11, v11, 0);
      v13 = *(uint32_t *)this;
      *((float *)this + 181) = (double)v12 + *((float *)this + 181);
      LOBYTE(pObj) = (*(int (/*thiscall*/ **)(uint8_t *, uint8_t *))(v13 + 344))(this, this + 724);
    }
  }
  return pObj;
}



// ------------------------------------------------------------
// 0x6130C0 CNSuplexSub__vmt14C
// ------------------------------------------------------------
// CNSuplexSub 主循环槽（vmt14C，182 行）：字符串证据「Character/Fighter/Effect/Animation/SuplexDust.ani |
// JumpSuplexCrashUnder.ani | JumpSuplexCrashOver.ani | Animation/PoweredSuplexSub.ani」+ 调试格式串「SIZE RATE %f」
// （运行时尺寸缩放输出直证）——柔道家背摔/跳背摔的全套动画（尘土+落地下/上层双画）。
// sub_4924C0（尺寸缩放）+ sub_600890。
int /*usercall*/ sub_6130C0@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // eax
  int v5; // ebx
  char *v6; // eax
  char *v7; // edi
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  char *v17; // eax
  char *v18; // edi
  int v19; // ebx
  int v20; // eax
  uint64_t v21; // rax
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // ebx
  char *v28; // eax
  int v29; // ebx
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // ebx
  int v34; // ecx
  int v35; // ebx
  char *v36; // eax
  int pObj; // edi
  int v38; // ebx
  int v39; // eax
  int v40; // ebx
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int result; // eax
  int v47; // [esp+18h] [ebp-10h]
  float v48; // [esp+18h] [ebp-10h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  if ( *(uint8_t *)(pArg1 + 984) == 0 )
  {
    if ( *(uint32_t *)(pArg1 + 284) == 21001 )
    {
      v4 = sub_42FCB0(228);
      v5 = 0;
      if ( v4 != 0 )
        v5 = sub_431860(v4, "Character/Fighter/Effect/Animation/SuplexDust.ani", 1);
      sub_4922F0(*(float *)(pArg1 + 980));
      off_77F3FC("SIZE RATE %f", *(float *)(pArg1 + 980));
      v6 = (char *)sub_44B6C0(284);
      v7 = v6;
      if ( v6 != nullptr )
      {
        sub_44E0D0(v6, v5, 1);
        *(uint32_t *)v7 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v7 = nullptr;
      }
      v8 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 684))(a1, 0);
      sub_45FE80(*(uint32_t *)(a1 + 116), (int)v7, 2, 0, (int)v7, v8, a3);
      v9 = *(uint32_t *)v7;
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
      (*(void (/*thiscall*/ **)(char *, int))(v9 + 148))(v7, v10);
      v11 = *(uint32_t *)v7;
      v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
      v13 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v12);
      v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 120))(a1, v13);
    }
    else
    {
      v15 = sub_42FCB0(228);
      if ( v15 != 0 )
        v16 = sub_431860(v15, "Character/Fighter/Effect/Animation/JumpSuplexCrashUnder.ani", 1);
      else
        v16 = 0;
      sub_4922F0(*(float *)(a1 + 980));
      v17 = (char *)sub_44B6C0(284);
      v18 = v17;
      if ( v17 != nullptr )
      {
        sub_44E0D0(v17, v16, 1);
        *(uint32_t *)v18 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v18 = nullptr;
      }
      sub_45FE80(*(uint32_t *)(pArg1 + 116), (int)v18, 2, 0, (int)v18, 0, 0);
      v19 = *(uint32_t *)v18;
      v20 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 152))(pArg1, nArg3, nArg2);
      (*(void (/*thiscall*/ **)(char *, int))(v19 + 148))(v18, v20);
      v21 = (uint64_t)(*(float *)(sub_4924C0(0) + 24) * 10.0);
      v22 = *(uint32_t *)v18;
      v47 = v21;
      v23 = (*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 128))(pArg1, HIDWORD(v21));
      v24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v23);
      v25 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v24 - v47);
      (*(void (/*thiscall*/ **)(char *, int))(v22 + 112))(v18, v25);
      v26 = sub_42FCB0(228);
      if ( v26 != 0 )
        v27 = sub_431860(v26, "Character/Fighter/Effect/Animation/JumpSuplexCrashOver.ani", 1);
      else
        v27 = 0;
      sub_4922F0(*(float *)(pArg1 + 980));
      v28 = (char *)sub_44B6C0(284);
      v7 = v28;
      if ( v28 != nullptr )
      {
        sub_44E0D0(v28, v27, 1);
        *(uint32_t *)v7 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v7 = nullptr;
      }
      sub_45FE80(*(uint32_t *)(a1 + 116), (int)v7, 2, 0, (int)v7, 0, 0);
      v29 = *(uint32_t *)v7;
      v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
      (*(void (/*thiscall*/ **)(char *, int))(v29 + 148))(v7, v30);
      v11 = *(uint32_t *)v7;
      v31 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
      v32 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v31);
      v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 120))(a1, v47 + v32);
    }
    (*(void (/*thiscall*/ **)(char *, int))(v11 + 112))(v7, v14);
    if ( *(uint8_t *)(a1 + 976) != 0 )
    {
      v33 = *(uint32_t *)(a1 + 120);
      if ( *(uint32_t *)(v33 + 148) == -1 )
        sub_4938F0(*(uint32_t *)(a1 + 120));
      v48 = *(float *)(*(uint32_t *)(v33 + 120) + 12) * 0.0024999999;
      if ( sub_42FCB0(228) != 0 )
      {
        if ( *(uint32_t *)(a1 + 384) < 0x10u )
          LOBYTE(v34) = a1 + 108;
        else
          v34 = *(uint32_t *)(a1 + 364);
        v35 = sub_431920(v34, (char)"Animation/PoweredSuplexSub.ani", 1);
      }
      else
      {
        v35 = 0;
      }
      sub_4922F0(v48);
      v36 = (char *)sub_44B6C0(284);
      v37 = (int)v36;
      if ( v36 != nullptr )
      {
        sub_44E0D0(v36, v35, 1);
        *(uint32_t *)v37 = &CNRDPooledObject::`vftable';
      }
      else
      {
        pObj = 0;
      }
      *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 36))(pObj) + 8) = 2;
      sub_45FE80(*(uint32_t *)(pArg1 + 116), pObj, 2, 0, pObj, 0, 0);
      v38 = *(uint32_t *)pObj;
      v39 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);
      (*(void (/*thiscall*/ **)(int, int))(v38 + 148))(pObj, v39);
      v40 = *(uint32_t *)pObj;
      v41 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);
      v42 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v41);
      v43 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v42);
      (*(void (/*thiscall*/ **)(int, int))(v40 + 112))(pObj, v43);
    }
    *(uint8_t *)(pArg1 + 984) = 1;
  }
  result = *(uint32_t *)(pArg1 + 120);
  if ( *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 312))(pArg1, 0);
  return result;
}


// ------------------------------------------------------------
// 0x6134D0 CNEnergyBall__vmt1F4
// ------------------------------------------------------------
// CNEnergyBall 命中表现槽（vmt1F4）：sub_4E4A50 —— 能量球（EnergyBall）命中表现【推断：念弹系】。
int /*thiscall*/ CNEnergyBall__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int v4; // eax
  int *pThis; // edi
  int v7; // eax
  int v9; // [esp-1Ch] [ebp-28h]
  int v10; // [esp-18h] [ebp-24h]
  int v11; // [esp-14h] [ebp-20h]
  int v12; // [esp+8h] [ebp-4h] BYREF

  v4 = *pArg2;
  v12 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v4 + 648))(pArg2, &v12, this);
  if ( pszArg4 == 0 && v12 > 0 && *((uint8_t *)this + 972) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg2 + 308))(pArg2) != 0 )
    {
      pThis = this;
      if ( *(this + 173) != 0 )
        pThis = (int *)*(this + 173);
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v9 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      sub_4E4A50(pThis, 21003, *(this + 176), v7, v9, v10, v11, 0, 0, 0);
    }
    *((uint8_t *)this + 972) = 1;
  }
  return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x613590 sub_613590
// ------------------------------------------------------------
int /*stdcall*/ sub_613590(int nArg1)
{
  uint32_t *v1; // eax
  float v3; // [esp+Ch] [ebp+8h]

  v1 = (uint32_t *)sub_47E720(1, 0xCu);
  v3 = (double)sub_47EF20(v1, 4u, nArg1, -1, -1, 11) * 0.0099999998;
  sub_4922F0(v3);
  return sub_4015C0("NEN_BEGIN", 9u);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x6135F0 CNThrowSand__vmt2A8
// ------------------------------------------------------------
// CNThrowSand 碰撞响应槽（vmt2A8）：sub_47E720/47EF20/47EFD0 —— 撒沙（ThrowSand）致盲判定【推断】。
char /*thiscall*/ CNThrowSand__vmt2A8(int *this, int nArg2)
{
  int v3; // eax
  char *v4; // eax
  int fld_e176; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // edx
  int v9; // eax

  CNRDPassiveObject__vmt2A8(this, nArg2);
  LOBYTE(v3) = *((uint8_t *)this + 973);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = (char *)sub_47E720(1, 0xDu);
    fld_e176 = *(this + 176);
    v6 = v4;
    *((float *)this + 190) = (double)sub_47EF20(v4, 0, fld_e176, -1, -1, 11) * 0.1;
    v7 = sub_47EF20(v6, 1u, fld_e176, -1, -1, 11);
    v8 = *this;
    *(this + 193) = v7;
    v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 388))(this);
    v3 = sub_47EFD0(v6, COERCE_FLOAT(2), fld_e176, v9, v9, 0);
    *((uint8_t *)this + 973) = 1;
    *((float *)this + 181) = (float)v3;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x613690 CNThrowSand__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNThrowSand__vmt12C(uint32_t *this, int nArg2)
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SAND_DROP", -1, 0, 0);
}



// ------------------------------------------------------------
// 0x6136C0 CNThrowSand__vmt14C
// ------------------------------------------------------------
// CNThrowSand 主循环槽（vmt14C）：sub_4600B0 + dword_8F82C0 —— 撒沙尘土演出与池化槽。
char /*thiscall*/ CNThrowSand__vmt14C(uint8_t *this)
{
  char result; // al
  int pObj; // edi
  int v4; // ebx
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  void *pThis_1D; // ecx
  bool v9; // cc
  uint8_t v10[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v12; // [esp+10h] [ebp-18h]
  int v13; // [esp+14h] [ebp-14h]
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]

  result = *(this + 972);
  if ( result == 0 )
  {
    v14 = 0;
    do
    {
      pObj = dword_8F82C0[v14 != 0];
      v4 = *(uint32_t *)pObj;
      pThis_80 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
      pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, pThis_80);
      pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, pThis_7C);
      (*(void (/*thiscall*/ **)(int, int))(v4 + 40))(pObj, pThis_78);
      LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this) == 0;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj) + 84) = v4;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj + 92))(pObj, v10);
      pThis_1D = *((void **)this + 29);
      v15 = 0;
      sub_4600B0(pThis_1D, 2, 0, (int)v10);
      v15 = -1;
      if ( Block != nullptr )
        j__free(Block);
      result = v14 + 1;
      v9 = v14 + 1 < 2;
      Block = nullptr;
      v12 = 0;
      v13 = 0;
      ++v14;
    }
    while ( v9 );
    *(this + 972) = 1;
  }
  if ( *(uint8_t *)(*((uint32_t *)this + 30) + 170) != 0 )
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x6137D0 sub_6137D0
// ------------------------------------------------------------
int sub_6137D0()
{
  return sub_4015C0("SAND_SPREAD", 0xBu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x6137F0 sub_6137F0
// ------------------------------------------------------------
void /*thiscall*/ sub_6137F0(uint8_t *this)
{
  *(this + 992) = 0;
}



// ------------------------------------------------------------
// 0x613800 CNEnergyField__vmt2A8
// ------------------------------------------------------------
// CNEnergyField 碰撞响应槽（vmt2A8）：sub_491C70/4920E0/4921E0（动画属性族）+ sub_607260/607290 ——
// 能量场（EnergyField，ENERGY_EXPLOTION TAG 见 0x6139F0 区）对场内目标的判定。
char /*thiscall*/ CNEnergyField__vmt2A8(int this, int nArg2)
{
  char result; // al
  int v4; // eax
  int fld_2C0; // ebx
  char *v6; // edi
  int pThis_184; // eax
  int fld_882; // eax
  int v9; // [esp+4h] [ebp-4h]
  int fld_88; // [esp+10h] [ebp+8h]
  float v11; // [esp+10h] [ebp+8h]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, nArg2);
  result = *(uint8_t *)(this + 992);
  if ( result == 0 )
  {
    v4 = sub_47E720(1, 0x10u);
    fld_2C0 = *(uint32_t *)(this + 704);
    v6 = (char *)v4;
    pThis_184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
    *(float *)(this + 724) = (float)sub_47EFD0(v6, 0.0, fld_2C0, pThis_184, pThis_184, 0);
    *(float *)(this + 760) = (double)sub_47EF20(v6, 1u, fld_2C0, -1, -1, 11) * 0.1;
    *(uint32_t *)(this + 772) = sub_47EF20(v6, 2u, fld_2C0, -1, -1, 11);
    v9 = sub_47EF20(v6, 3u, fld_2C0, -1, -1, 11);
    if ( v9 <= 1 )
    {
      sub_607260((uint32_t *)(this + 972), 0, 0, 1, 1);
    }
    else
    {
      fld_88 = sub_491C70(*(uint32_t *)(this + 136), 2);
      fld_882 = sub_491C70(*(uint32_t *)(this + 136), 13);
      sub_607260((uint32_t *)(this + 972), (fld_882 - fld_88) / v9, v9 - 1, 0, 0);
      sub_607290((uint8_t *)(this + 972), fld_88);
    }
    v11 = (double)sub_47EF20(v6, 4u, fld_2C0, -1, -1, 11) * 0.0099999998;
    sub_4920E0(*(uint32_t **)(this + 136), v11, v11);
    result = sub_4921E0(v11);
    *(uint8_t *)(this + 992) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x613960 CNEnergyField__vmt14C
// ------------------------------------------------------------
// CNEnergyField 主循环槽（vmt14C）：sub_4910A0 + sub_6072C0 —— 能量场的维持 tick。
char /*thiscall*/ CNEnergyField__vmt14C(uint32_t *this)
{
  int fld_e30; // eax
  int v3; // ecx
  int v4; // eax
  int fld_e173; // eax
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  fld_e30 = *(this + 30);
  v3 = *(uint32_t *)(fld_e30 + 212);
  if ( v3 != 0 )
    v4 = sub_4910A0(v3);
  else
    v4 = *(uint32_t *)(fld_e30 + 32);
  if ( sub_6072C0((uint8_t *)this + 972, v4) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
  fld_e173 = __RTDynamicCast(
         *(this + 173),
         0,
         &IRDCollisionObject `RTTI Type Descriptor',
         &CNFighter `RTTI Type Descriptor',
         0);
  if ( fld_e173 == 0 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e173 + 840))(fld_e173) != 10 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  result = *(uint8_t *)(*(this + 30) + 170);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x6139F0 sub_6139F0
// ------------------------------------------------------------
int sub_6139F0()
{
  return sub_4015C0("ENERGY_EXPLOTION", 0x10u);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x613A10 sub_613A10
// ------------------------------------------------------------
int /*thiscall*/ sub_613A10(int this)
{
  *(uint8_t *)(this + 992) = 0;
  *(uint8_t *)(this + 993) = 0;
  *(uint32_t *)(this + 996) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x613A30 CNBlastBlood__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNBlastBlood__vmt12C(int *this, int nArg2)
{
  int fld_e249; // ecx
  int fld_e2492; // [esp-4h] [ebp-Ch]

  fld_e249 = *(this + 249);
  if ( nArg2 == fld_e249 )
  {
    fld_e2492 = fld_e249;
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_e249 + 1160))(24);
    sub_47DD30(fld_e2492);
    *(this + 249) = 0;
  }
  CNRDPassiveObject__vmt12C(this, nArg2);
}



// ------------------------------------------------------------
// 0x613A70 CNBlastBlood__vmt14C
// ------------------------------------------------------------
// CNBlastBlood 主循环槽（vmt14C）：字符串证据「FIRE_PILLAR_UP」（音效 TAG —— 血爆升起的火柱）。
// sub_47DCD0/47DD30 + sub_4910A0 —— 狂战士系血爆（BlastBlood）的火柱升起演出。
int /*thiscall*/ CNBlastBlood__vmt14C(uint8_t *this)
{
  int pThis_2AC; // eax
  int pObj; // eax
  int *v4; // eax
  int pThis_1E; // eax
  int v6; // ecx
  int v7; // eax
  int result; // eax
  int pThis_F9; // ecx
  int pObj2; // [esp-8h] [ebp-Ch]
  int pThis_F92; // [esp-4h] [ebp-8h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 993) == 0 )
  {
    pThis_2AC = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 684))(this);
    pObj = __RTDynamicCast(pThis_2AC, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSwordman `RTTI Type Descriptor', 0);
    *((uint32_t *)this + 249) = pObj;
    if ( pObj != 0 )
    {
      pObj2 = pObj;
      v4 = (int *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1160))(pObj, 24);
      sub_47DCD0(v4, pObj2, 20000);
    }
    *(this + 993) = 1;
  }
  pThis_1E = *((uint32_t *)this + 30);
  v6 = *(uint32_t *)(pThis_1E + 212);
  if ( v6 != 0 )
    v7 = sub_4910A0(v6);
  else
    v7 = *(uint32_t *)(pThis_1E + 32);
  if ( sub_6072C0(this + 972, v7) != 0 )
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 352))(this);
  if ( *(int *)(**((uint32_t **)this + 36) + 148) >= 8 && *(this + 992) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "FIRE_PILLAR_UP",
      -1,
      0,
      0);
    *(this + 992) = 1;
  }
  result = *((uint32_t *)this + 30);
  if ( *(uint8_t *)(result + 170) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    pThis_F9 = *((uint32_t *)this + 249);
    if ( pThis_F9 != 0 )
    {
      pThis_F92 = *((uint32_t *)this + 249);
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)pThis_F9 + 1160))(24);
      return sub_47DD30(pThis_F92);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x613B70 sub_613B70
// ------------------------------------------------------------
// 血爆生成辅助：字符串证据「BLOOD_CIRCLE_CREATE」（音效 TAG —— 血圈生成）+ sub_491C70 + sub_607260/607290 ——
// 血爆中心的血圈演出装配。
int /*thiscall*/ sub_613B70(void *this, int nArg2)
{
  uint32_t *v3; // ebx
  int v4; // edi
  int pThis_22; // ebx
  int pThis_222; // eax
  int v7; // eax
  float v8; // edx
  int result; // eax
  uint32_t *v10; // [esp+8h] [ebp+8h]

  *((float *)this + 181) = (float)nArg2;
  v3 = (uint32_t *)sub_47E720(0, 0x18u);
  v10 = v3;
  v4 = sub_47E9D0(v3, 0);
  if ( v4 > 1 )
  {
    pThis_22 = sub_491C70(*((uint32_t *)this + 34), 1);
    pThis_222 = sub_491C70(*((uint32_t *)this + 34), 4);
    sub_607260((uint32_t *)this + 243, (pThis_222 - pThis_22) / v4, v4 - 1, 0, 0);
    sub_607290((uint8_t *)this + 972, pThis_22);
    v3 = v10;
  }
  v7 = sub_47E9D0(v3, 1u);
  v8 = *(float *)this;
  *((uint32_t *)this + 198) = v7;
  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(LODWORD(v8) + 204))(
    this,
    1,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    1);
  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 204))(
    this,
    2,
    *(uint32_t *)(*((uint32_t *)this + 36) + 4),
    0,
    0,
    0,
    1);
  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    -1,
    *(uint32_t *)(*((uint32_t *)this + 36) + 8),
    0,
    0,
    0,
    0);
  result = sub_4015C0("BLOOD_CIRCLE_CREATE", 0x13u);  // 【std::string构造赋值】
  *((uint8_t *)this + 992) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x613C80 CNBlastBloodSub__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNBlastBloodSub__vmt14C(uint32_t *this)
{
  int fld_e30; // eax
  int v3; // ecx
  int v4; // eax
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  fld_e30 = *(this + 30);
  v3 = *(uint32_t *)(fld_e30 + 212);
  if ( v3 != 0 )
    v4 = sub_4910A0(v3);
  else
    v4 = *(uint32_t *)(fld_e30 + 32);
  if ( sub_6072C0((uint8_t *)this + 972, v4) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
  result = *(uint8_t *)(*(this + 30) + 170);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x613CE0 sub_613CE0
// ------------------------------------------------------------
int /*thiscall*/ sub_613CE0(int this, int nArg2)
{
  uint32_t *v3; // ebx
  int v4; // edi
  int fld_88; // ebx
  int fld_882; // eax
  int result; // eax
  uint32_t *v8; // [esp+8h] [ebp+8h]

  *(float *)(this + 724) = (float)nArg2;
  v3 = (uint32_t *)sub_47E720(0, 0x18u);
  v8 = v3;
  v4 = sub_47E9D0(v3, 0);
  if ( v4 > 1 )
  {
    fld_88 = sub_491C70(*(uint32_t *)(this + 136), 1);
    fld_882 = sub_491C70(*(uint32_t *)(this + 136), 4);
    sub_607260((uint32_t *)(this + 972), (fld_882 - fld_88) / v4, v4 - 1, 0, 0);
    sub_607290((uint8_t *)(this + 972), fld_88);
    v3 = v8;
  }
  result = sub_47E9D0(v3, 2u);
  *(uint32_t *)(this + 792) = result;
  return result;
}



// ------------------------------------------------------------
// 0x613D70 CNBlastBloodSub__vmt1F4
// ------------------------------------------------------------
// CNBlastBloodSub 命中表现槽（vmt1F4，74 行）：字符串证据「Animation/BlastBloodHit1.ani | BlastBloodHit2.ani」
// （双层命中动画叠放）。sub_44B6C0 + sub_45FE80（演播层）——血爆子体的飞溅演出。
int /*userpurge*/ CNBlastBloodSub__vmt1F4@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, uint32_t *pArg3, float *pArg4, char pszArg5)
{
  uint32_t *pArg32; // esi
  int v7; // eax
  int v8; // ebx
  const char *v9; // ecx
  char *v10; // eax
  int pObj; // esi
  int v12; // eax
  const char *v13; // ecx
  int v14; // ebx
  char *v15; // eax
  int pObj2; // esi
  int v18; // [esp+Ch] [ebp-14h]
  int v19; // [esp+10h] [ebp-10h]

  pArg32 = pArg3;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 128))(pArg3) == 0 && pszArg5 == 0 )
  {
    v18 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 120))(pArg3, nArg2);
    v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 124))(pArg3);
    v7 = sub_42FCB0(228);
    v8 = 0;
    if ( v7 != 0 )
    {
      if ( (unsigned int)pDwArg1[96] < 0x10 )
        v9 = (const char *)(pDwArg1 + 91);
      else
        v9 = (const char *)pDwArg1[91];
      v8 = sub_431920(v7, v9, "Animation/BlastBloodHit1.ani", 1);
    }
    v10 = (char *)sub_44B6C0(284);
    pObj = (int)v10;
    if ( v10 != nullptr )
    {
      sub_44E0D0(v10, v8, 1);
      *(uint32_t *)pObj = &vftbl_CNRDPooledObject;
    }
    else
    {
      pObj = 0;
    }
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 36))(pObj) + 8) = 2;
    sub_45FE80(pDwArg1[29], (int)pDwArg1, 2, 0, pObj, 0, 0);
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 112))(pObj, v18, v19, 0);
    v12 = sub_42FCB0(228);
    if ( v12 != 0 )
    {
      if ( (unsigned int)pDwArg1[96] < 0x10 )
        v13 = (const char *)(pDwArg1 + 91);
      else
        v13 = (const char *)pDwArg1[91];
      v14 = sub_431920(v12, v13, "Animation/BlastBloodHit2.ani", 1);
    }
    else
    {
      v14 = 0;
    }
    v15 = (char *)sub_44B6C0(284);
    pObj2 = (int)v15;
    if ( v15 != nullptr )
    {
      sub_44E0D0(v15, v14, 1);
      *(uint32_t *)pObj2 = &vftbl_CNRDPooledObject;
    }
    else
    {
      pObj2 = 0;
    }
    sub_45FE80(pDwArg1[29], (int)pDwArg1, 2, 0, pObj2, (int)pDwArg1, 0);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, v18, v19);
    pArg32 = pArg3;
  }
  return CNRDPassiveObject__vmt1F4(pDwArg1, pArg32, pArg4, pszArg5);
}



// ------------------------------------------------------------
// 0x613F40 sub_613F40
// ------------------------------------------------------------
int /*thiscall*/ sub_613F40(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint8_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1028) = 0;
  *(uint32_t *)(this + 1032) = 0;
  *(uint32_t *)(this + 1048) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x613F90 CNGhost__vmtC
// ------------------------------------------------------------
float */*thiscall*/ CNGhost__vmtC(int *this)
{
  float *result; // eax

  result = CNRDPassiveObject__vmtC(this);
  if ( *(this + 243) == 36 )
    return (float *)(*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x613FB0 sub_613FB0
// ------------------------------------------------------------
// 鬼神辅助：sub_4E4630 ——【推断：鬼神附加体的位移/朝向同步】。
char /*thiscall*/ sub_613FB0(uint32_t *this, int nArg2)
{
  int fld_e243; // eax
  int v4; // ebx
  char result; // al

  fld_e243 = *(this + 243);
  if ( fld_e243 == 25 )
  {
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);
    if ( v4 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )
      return 0;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, nArg2, 0) < *(this + 248);
  }
  if ( fld_e243 != 41 )
  {
    if ( fld_e243 == 36
      && ((uint8_t)sub_4E4630(nArg2) == 0
       || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 624))(nArg2) == 0
       || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 128))(nArg2) > *(this + 262)) )
    {
      return 0;
    }
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, nArg2, 0) < *(this + 248);
  }
  result = sub_4E4630(nArg2);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, nArg2, 0) < *(this + 248);
  return result;
}



// ------------------------------------------------------------
// 0x614050 sub_614050
// ------------------------------------------------------------
bool /*thiscall*/ sub_614050(uint32_t *this, int pArg2)
{
  int v2; // edx
  int fld_e243; // eax

  v2 = *(uint32_t *)(pArg2 + 64);
  fld_e243 = *(this + 243);
  if ( fld_e243 == 25 )
    return v2 == 13;
  else
    return v2 == (fld_e243 != 41 ? 56 : 14);
}



// ------------------------------------------------------------
// 0x614090 sub_614090
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_614090(uint32_t *this, int nArg2, int nArg3)
{
  sub_4B1030(this);
  *this = &vftbl_CNBremenAppendage;
  sub_652220(this);
  sub_652400(nArg2, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x6140F0 CNBremenAppendage__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNBremenAppendage__vmt0(void *Block, char pszArg2)
{
  sub_614120();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x614120 sub_614120
// ------------------------------------------------------------
int /*thiscall*/ sub_614120(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNBremenAppendage;
  sub_603910((uint32_t *)this);
  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x614180 sub_614180
// ------------------------------------------------------------
// 鬼神数据辅助（38 行，无外部调用）——【推断：鬼神等级/持续时间的字段折算】。
uint32_t */*thiscall*/ sub_614180(uint32_t *this, uint32_t *pArg2, uint32_t *uArg3)
{
  int *fld_e1; // edx
  int *v4; // eax
  int *fld_e12; // ecx
  int *v6; // eax

  fld_e1 = (int *)*(this + 1);
  v4 = (int *)fld_e1[1];
  while ( *((uint8_t *)v4 + 21) == 0 )
  {
    if ( *uArg3 >= (unsigned int)v4[3] )
    {
      v4 = (int *)v4[2];
    }
    else
    {
      fld_e1 = v4;
      v4 = (int *)*v4;
    }
  }
  fld_e12 = (int *)*(this + 1);
  v6 = (int *)fld_e12[1];
  while ( *((uint8_t *)v6 + 21) == 0 )
  {
    if ( (unsigned int)v6[3] >= *uArg3 )
    {
      fld_e12 = v6;
      v6 = (int *)*v6;
    }
    else
    {
      v6 = (int *)v6[2];
    }
  }
  *pArg2 = fld_e12;
  pArg2[1] = fld_e1;
  return pArg2;
}



// ------------------------------------------------------------
// 0x6141F0 CNGhost__vmt10
// ------------------------------------------------------------
// CNGhost 初始化（vmt10）：sub_4049C0 lerp + sub_491F80/4938F0（动画复位）+ sub_699000 ——
// 鬼神（Ghost）出场参数插值。
int /*thiscall*/ CNGhost__vmt10(int this)
{
  int fld_3DC; // eax
  int v3; // ebx
  int fld_3D0; // edi
  double v5; // st7
  int fld_3D8; // edi
  int i; // edi
  int result; // eax
  int pThis_24; // [esp-8h] [ebp-14h]
  int fld_3D4; // [esp-8h] [ebp-14h]

  CNRDPassiveObject__vmt10((uint8_t *)this);
  fld_3DC = *(uint32_t *)(this + 988);
  v3 = 180;
  if ( fld_3DC == 0 )
  {
    fld_3D0 = *(uint32_t *)(this + 976);
    pThis_24 = sub_699000(this + 36);  // 【clock_now(clk)】
    v5 = sub_4049C0(0.0, 180.0, pThis_24, fld_3D0);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
LABEL_5:
    v3 = (uint64_t)v5;
    goto LABEL_6;
  }
  if ( fld_3DC == 2 )
  {
    fld_3D8 = *(uint32_t *)(this + 984) - *(uint32_t *)(this + 980);
    fld_3D4 = sub_699000(this + 36) - *(uint32_t *)(this + 980);  // 【clock_now(clk)】
    v5 = sub_4049C0(180.0, 0.0, fld_3D4, fld_3D8);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    goto LABEL_5;
  }
LABEL_6:
  for ( i = 0; i < 8; i += 4 )
  {
    sub_4938F0(*(uint32_t *)(*(uint32_t *)(this + 144) + i));
    result = sub_491F80(-1, -1, -1, v3, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6142A0 sub_6142A0
// ------------------------------------------------------------
// 鬼神选型辅助（60 行，无外部调用）——【推断：卡赞/萨亚/布雷门三鬼神的分支参数】。
int /*thiscall*/ sub_6142A0(int *this, int nArg2)
{
  int result; // eax
  int v3; // ebx
  unsigned int i; // edi
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int pObj; // ecx
  int v13; // eax
  int v14; // ecx
  uint32_t *v15; // ecx

  result = *(this + 243);
  if ( result == 25 || result == 41 )
  {
    v3 = result == 25 ? 13 : result != 41 ? 56 : 14;
    if ( nArg2 != 0 )
    {
      for ( i = 0; ; ++i )
      {
        v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
        v6 = *(uint32_t *)(v5 + 4);
        result = v6 != 0 ? (*(uint32_t *)(v5 + 8) - v6) >> 2 : 0;
        if ( (int)i >= result )
          break;
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
        v8 = *(uint32_t *)(v7 + 4);
        if ( v8 != 0 && i < (*(uint32_t *)(v7 + 8) - v8) >> 2 )
          v9 = *(uint32_t *)(v8 + 4 * i);
        else
          v9 = 0;
        if ( *(uint32_t *)(v9 + 4) == nArg2 )
        {
          v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
          v11 = *(uint32_t *)(v10 + 4);
          if ( v11 != 0 && i < (*(uint32_t *)(v10 + 8) - v11) >> 2 )
            pObj = *(uint32_t *)(v11 + 4 * i);
          else
            pObj = 0;
          if ( *(int **)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 32) == this )
          {
            v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
            v14 = *(uint32_t *)(v13 + 4);
            if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )
            {
              v15 = *(uint32_t **)(v14 + 4 * i);
              if ( v15 != nullptr && v15[16] == v3 )
                return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*v15 + 76))(v15, 0);
            }
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6143B0 sub_6143B0
// ------------------------------------------------------------
// 鬼神辅助（31 行，无外部调用）——【推断：鬼神光环半径参数】。
char /*thiscall*/ sub_6143B0(uint32_t *this, int nArg2)
{
  int fld_e243; // eax
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // esi
  int v9; // eax

  fld_e243 = *(this + 243);
  if ( fld_e243 == 25 )
  {
    v4 = __RTDynamicCast(nArg2, 0, &IRDAppendage `RTTI Type Descriptor', &CNChangeStatus `RTTI Type Descriptor', 0);
    v5 = v4;
    if ( v4 == 0 )
      return 0;
    v6 = *(uint32_t *)(v4 + 84);
    if ( v6 != 0 && (*(uint32_t *)(v5 + 88) - v6) / 12 != 0 )
      v7 = *(uint32_t *)(v5 + 84);
    else
      v7 = 0;
    if ( (double)(int)*(this + 255) > *(float *)(v7 + 8) )
      return 0;
  }
  else if ( fld_e243 == 41 )
  {
    v9 = __RTDynamicCast(nArg2, 0, &IRDAppendage `RTTI Type Descriptor', &CNBremenAppendage `RTTI Type Descriptor', 0);
    if ( v9 == 0 || *(uint32_t *)(v9 + 84) < *(this + 257) )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x614460 sub_614460
// ------------------------------------------------------------
// 鬼神阵生成辅助：字符串证据「G_GHOST_CIRCLE」（音效 TAG —— 鬼神阵）。
// sub_491C10 + sub_607260 —— 鬼泣召唤阵的演出装配。
int /*thiscall*/ sub_614460(float *this, unsigned int uArg2, int nArg3)
{
  uint32_t *v4; // eax
  uint32_t *v5; // edi
  int pThis_24; // eax
  float v7; // edx
  int pThis_F6; // ecx
  uint32_t *pThis_242; // eax
  int v11; // [esp+Ch] [ebp-4h]

  *((uint32_t *)this + 243) = uArg2;
  v4 = (uint32_t *)sub_47E720(0, uArg2);
  v5 = v4;
  if ( uArg2 == 25 )
  {
    *((uint32_t *)this + 255) = sub_47EF20(v4, 0, nArg3, -1, -1, 11);
    *((uint32_t *)this + 256) = sub_47EF20(v5, 2u, nArg3, -1, -1, 11);
    sub_607260((uint32_t *)this + 250, 100, -1, 1, 1);
  }
  else if ( uArg2 == 36 )
  {
    *(this + 190) = (double)sub_47EF20(v4, 2u, nArg3, -1, -1, 11) * 0.1;
    *((uint32_t *)this + 193) = sub_47EF20(v5, 3u, nArg3, -1, -1, 11);
    v11 = sub_47E9D0(v5, 3u);
    *((uint32_t *)this + 262) = sub_47E9D0(v5, 2u);
    sub_607260((uint32_t *)this + 250, v11, -1, 1, 1);
  }
  else
  {
    if ( uArg2 == 41 )
    {
      *((uint32_t *)this + 257) = sub_47EF20(v4, 0, nArg3, -1, -1, 11);
      *((uint32_t *)this + 258) = sub_47EF20(v5, 2u, nArg3, -1, -1, 11);
    }
    sub_607260((uint32_t *)this + 250, 250, -1, 1, 1);
  }
  *((uint32_t *)this + 248) = sub_47E9D0(v5, 1u);
  *((uint32_t *)this + 246) = sub_47EF20(v5, 1u, nArg3, -1, -1, 11);
  *((uint32_t *)this + 244) = sub_491C10(*(uint32_t *)(*((uint32_t *)this + 36) + 12));
  pThis_24 = sub_491C10(*(uint32_t *)(*((uint32_t *)this + 36) + 20));
  v7 = *this;
  pThis_F6 = *((uint32_t *)this + 246) - pThis_24;
  pThis_242 = *((uint32_t **)this + 36);
  *((uint32_t *)this + 245) = pThis_F6;
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(LODWORD(v7) + 204))(
    this,
    2,
    *pThis_242,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    1,
    *(uint32_t *)(*((uint32_t *)this + 36) + 4),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 204))(
    this,
    1,
    *(uint32_t *)(*((uint32_t *)this + 36) + 8),
    0,
    0,
    0,
    1);
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 204))(
    this,
    2,
    *(uint32_t *)(*((uint32_t *)this + 36) + 12),
    0,
    0,
    0,
    1);
  return sub_4015C0("G_GHOST_CIRCLE", 0xEu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x614660 sub_614660
// ------------------------------------------------------------
// 鬼神目标 map 管理（106 行）：STL 异常串「map/set<T> too long」直证 std::map 使用 +
// sub_4296E0/sub_433130/sub_5648C0 —— 鬼神作用目标的有序表维护（插入/查重）。
int */*thiscall*/ sub_614660(int **this, int *pDwArg2, char pszArg3, int *pDwArg4, int nArg5)
{
  int fld_e1; // ecx
  int *fld_e12; // eax
  int *fld_e13; // eax
  int fld_e14; // eax
  int *v10; // eax
  int fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  void **pExceptionObject; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v17[20]; // [esp+34h] [ebp-28h] BYREF
  int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]
  int fld_e15; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0x1FFFFFFE )
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(v17);
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_5648C0(*(this + 1), pDwArg4, *(this + 1), nArg5, 0);
  fld_e12 = *(this + 1);
  fld_e15 = fld_e1;
  *(this + 2) = (int *)((char *)*(this + 2) + 1);
  if ( pDwArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    **(this + 1) = fld_e1;
    (*(this + 1))[2] = fld_e1;
  }
  else if ( pszArg3 != 0 )
  {
    *pDwArg4 = fld_e1;
    fld_e13 = *(this + 1);
    if ( pDwArg4 == (int *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pDwArg4[2] = fld_e1;
    fld_e14 = (int)*(this + 1);
    if ( pDwArg4 == *(int **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = (int *)(fld_e1 + 4);
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
            sub_433130(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(this, *(uint32_t **)(*(uint32_t *)(fld_e16 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(this, *(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)((*(this + 1))[1] + 20) = 1;
  *pDwArg2 = fld_e1;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x614810 sub_614810
// ------------------------------------------------------------
// 鬼神目标表消费（59 行）：sub_4A3B30 + sub_614660 —— 遍历目标表施加鬼神效果【推断】。
int /*thiscall*/ sub_614810(int **this, int pArg2, int *pDwArg3)
{
  int *pDwArg32; // ebx
  int *fld_e1; // esi
  int v6; // eax
  bool v7; // cl
  unsigned int v8; // edx
  int *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  pDwArg32 = pDwArg3;
  fld_e1 = *(this + 1);
  v6 = fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *(uint8_t *)(v6 + 21) == 0 )
  {
    v8 = *pDwArg3;
    do
    {
      v7 = v8 < *(uint32_t *)(v6 + 12);
      fld_e1 = (int *)v6;
      v13 = v7;
      if ( v8 >= *(uint32_t *)(v6 + 12) )
        v6 = *(uint32_t *)(v6 + 8);
      else
        v6 = *(uint32_t *)v6;
    }
    while ( *(uint8_t *)(v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;
  pDwArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == (int *)**(this + 1) )
    {
      v10 = *sub_614660(this, (int *)&pDwArg3, 1, fld_e1, (int)pDwArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4A3B30(&pDwArg3);
    fld_e12 = pDwArg3;
  }
  if ( fld_e12[3] >= (unsigned int)*pDwArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else
  {
    v12 = *sub_614660(this, (int *)&pDwArg3, v13, fld_e1, (int)pDwArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x6148D0 sub_6148D0
// ------------------------------------------------------------
// 鬼神辅助：sub_41C5E0 + sub_52E960 + sub_614180 —— 目标效果施加的收尾【推断】。
int /*thiscall*/ sub_6148D0(uint32_t *this, uint32_t *uArg2)
{
  uint32_t *v2; // eax
  uint32_t *v3; // edi
  int v4; // esi
  uint32_t *v6; // [esp+Ch] [ebp-8h] BYREF
  uint32_t *v7; // [esp+10h] [ebp-4h]

  sub_614180(this, &v6, uArg2);
  v2 = v6;
  v3 = v7;
  v4 = 0;
  uArg2 = v6;
  if ( v6 != v7 )
  {
    do
    {
      ++v4;
      sub_41C5E0(&uArg2);
    }
    while ( uArg2 != v3 );
    v2 = v6;
  }
  sub_52E960(&uArg2, v2, v3);
  return v4;
}



// ------------------------------------------------------------
// 0x614930 sub_614930
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_614930(int *this, int nArg2)
{
  uint32_t *result; // eax
  uint8_t v4[4]; // [esp+4h] [ebp-4h] BYREF

  result = (uint32_t *)*(this + 243);
  if ( result == (uint32_t *)25 || result == (uint32_t *)41 )
  {
    result = (uint32_t *)sub_4BE520(v4, &nArg2);
    if ( *result != *(this + 260) )
    {
      sub_6142A0(this, nArg2);
      return (uint32_t *)sub_6148D0(this + 259, &nArg2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x614990 sub_614990
// ------------------------------------------------------------
// 鬼神目标表预处理（52 行）：sub_4B3C90 + sub_614090 ——【推断：目标过滤/优先级】。
uint32_t */*thiscall*/ sub_614990(int *this, int nArg2)
{
  uint32_t *result; // eax
  uint32_t *v4; // esi
  uint32_t *v5; // ecx
  uint32_t *pMem; // eax
  int fld_e243; // eax
  int v8; // eax
  float fld_e255; // [esp+Ch] [ebp-1Ch]
  float fld_e256; // [esp+Ch] [ebp-1Ch]

  result = (uint32_t *)*(this + 243);
  if ( result == (uint32_t *)25 )
  {
    if ( operator new(0x7Cu) != nullptr )
      v4 = (uint32_t *)sub_4B3C90(0, 1);
    else
      v4 = nullptr;
    fld_e255 = (float)*(this + 255);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t))(*v4 + 120))(v4, 0, 0, LODWORD(fld_e255));
    fld_e256 = (float)*(this + 256);
    result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*v4 + 120))(v4, 1, 0, LODWORD(fld_e256));
    v5 = v4;
  }
  else
  {
    if ( result != (uint32_t *)41 )
      return result;
    pMem = operator new(0x5Cu);
    if ( pMem != nullptr )
      result = sub_614090(pMem, *(this + 257), *(this + 258));
    else
      result = nullptr;
    v5 = result;
  }
  if ( v5 != nullptr )
  {
    fld_e243 = *(this + 243);
    if ( fld_e243 == 25 )
      v8 = 13;
    else
      v8 = fld_e243 != 41 ? 56 : 14;
    return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int *, uint32_t, uint32_t, int, int))(*v5 + 56))(
                       v5,
                       nArg2,
                       this,
                       0,
                       0,
                       v8,
                       -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x614AB0 CNGhost__vmt12C
// ------------------------------------------------------------
// CNGhost 消亡联动槽（vmt12C）：sub_6142A0/614930 —— 鬼神消散时的状态回滚【推断】。
uint32_t */*thiscall*/ CNGhost__vmt12C(int *this, int nArg2)
{
  int pObj; // edi
  uint32_t *result; // eax
  int *fld_e260; // ecx

  pObj = nArg2;
  CNRDPassiveObject__vmt12C(this, nArg2);
  result = (uint32_t *)*(this + 243);
  if ( result == (uint32_t *)25 || result == (uint32_t *)41 )
  {
    if ( (int *)pObj == this )
    {
      fld_e260 = (int *)*(this + 260);
      result = (uint32_t *)*fld_e260;
      nArg2 = *fld_e260;
      if ( (int *)nArg2 != fld_e260 )
      {
        do
        {
          sub_6142A0(this, result[3]);
          sub_41C5E0(&nArg2);
          result = (uint32_t *)nArg2;
        }
        while ( nArg2 != *(this + 260) );
      }
    }
    else
    {
      result = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17);
      if ( (uint8_t)result != 0 )
        return sub_614930(this, pObj);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x614B30 sub_614B30
// ------------------------------------------------------------
// 鬼神主体装配（99 行）：sub_4BE520 + sub_614050/6143B0/614810/614990 ——
// 卡赞（力）/萨亚（冰）/布雷门（束缚）三鬼神共用的装配管线（分支在 6142A0）。
char /*thiscall*/ sub_614B30(int **this, int nArg2)
{
  int **pThis; // ebx
  int fld_e243; // eax
  int **v4; // eax
  int pObj; // edi
  unsigned int v6; // ebx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int pObj2; // esi
  int v16; // eax
  char v18[8]; // [esp+4h] [ebp-18h] BYREF
  int nArg22; // [esp+Ch] [ebp-10h] BYREF
  int nArg23; // [esp+10h] [ebp-Ch] BYREF
  int **pThis2; // [esp+14h] [ebp-8h]
  char v22; // [esp+1Bh] [ebp-1h]

  pThis = this;
  fld_e243 = (int)*(this + 243);
  pThis2 = this;
  if ( fld_e243 != 25 && fld_e243 != 41 )
    return fld_e243;
  v4 = (int **)sub_4BE520(&nArg23, &nArg2);
  pObj = nArg2;
  if ( *v4 == pThis[260] )
  {
    nArg22 = nArg2;
    nArg23 = nArg2;
    sub_614810(pThis + 259, (int)v18, &nArg22);
  }
  HIBYTE(nArg2) = 0;
  v22 = 0;
  if ( pObj == 0 )
  {
LABEL_30:
    LOBYTE(fld_e243) = (uint8_t)sub_614990((int *)pThis, pObj);
    return fld_e243;
  }
  v6 = 0;
  while ( 1 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
    v8 = *(uint32_t *)(v7 + 4);
    v9 = v8 != 0 ? (*(uint32_t *)(v7 + 8) - v8) >> 2 : 0;
    if ( (int)v6 >= v9 )
      break;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
    v11 = *(uint32_t *)(v10 + 4);
    if ( v11 != 0 && v6 < (*(uint32_t *)(v10 + 8) - v11) >> 2 )
      v12 = *(uint32_t *)(v11 + 4 * v6);
    else
      v12 = 0;
    if ( *(uint32_t *)(v12 + 4) == pObj
      && (v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj), (v14 = *(uint32_t *)(v13 + 4)) != 0)
      && v6 < (*(uint32_t *)(v13 + 8) - v14) >> 2
      && (pObj2 = *(uint32_t *)(v14 + 4 * v6)) != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj2 + 80))(*(uint32_t *)(v14 + 4 * v6)) != 0
      && sub_614050(pThis2, pObj2) )
    {
      v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2);
      if ( *(int ***)(v16 + 32) == pThis2 )
      {
        HIBYTE(nArg2) = 1;
        ++v6;
      }
      else
      {
        if ( sub_6143B0(pThis2, pObj2) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 76))(pObj2, 0);
          goto LABEL_26;
        }
        v22 = 1;
        ++v6;
      }
    }
    else
    {
LABEL_26:
      ++v6;
    }
  }
  LOBYTE(fld_e243) = HIBYTE(nArg2);
  if ( HIBYTE(nArg2) == 0 )
  {
    LOBYTE(fld_e243) = v22;
    if ( v22 == 0 )
    {
      pThis = pThis2;
      goto LABEL_30;
    }
  }
  return fld_e243;
}



// ------------------------------------------------------------
// 0x614C90 CNGhost__vmt14C
// ------------------------------------------------------------
// ★ CNGhost 主循环槽（vmt14C，150 行）：字符串证据「GHOST_KAJAN | GHOST_SAYA | GHOST_BREMEN」
// （音效 TAG —— 鬼泣三鬼神：卡赞/萨亚/布雷门，研究 20 系外的独立音效证据）。
// sub_47E720/47EFD0（命中几何）+ sub_4E5F70（硬直率掷）+ sub_613FB0/614B30 ——
// 鬼神持续期间的周期判定与效果施加。
int /*thiscall*/ sub_614C90(int *this)  // 【CNGhost__vmt14C】
{
  int fld_e243; // eax
  char *v3; // edi
  int v4; // eax
  int fld_e247; // eax
  unsigned int v6; // edi
  int pThis_10; // eax
  int fld_e29; // eax
  int v9; // ecx
  int v10; // eax
  int fld_e292; // ecx
  int v12; // edx
  int pObj; // edi
  char v14; // bl
  int fld_e2432; // eax
  int v16; // eax
  int v17; // eax
  int v18; // edx
  int v19; // eax
  int result; // eax
  float v21; // [esp+8h] [ebp-24h] BYREF
  float v22; // [esp+Ch] [ebp-20h]
  float v23; // [esp+10h] [ebp-1Ch]
  int v24; // [esp+14h] [ebp-18h]
  int v25; // [esp+18h] [ebp-14h]
  int v26; // [esp+1Ch] [ebp-10h]
  int fld_e262; // [esp+20h] [ebp-Ch]
  int fld_e176; // [esp+24h] [ebp-8h]
  unsigned int v29; // [esp+28h] [ebp-4h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  if ( *((uint8_t *)this + 996) == 0 )
  {
    fld_e243 = *(this + 243);
    switch ( fld_e243 )
    {
      case 25:
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GHOST_KAJAN", -1, 0, 0);
        break;
      case 36:
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GHOST_SAYA", -1, 0, 0);
        break;
      case 41:
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GHOST_BREMEN", -1, 0, 0);
        break;
      default:
        break;
    }
    if ( *(this + 243) == 36 )
    {
      v3 = (char *)sub_47E720(0, 36);
      v4 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
      fld_e176 = sub_47EFD0(v3, 0.0, *(this + 176), v4, v4, 0);
      *((float *)this + 97) = (float)fld_e176;
    }
    *((uint8_t *)this + 996) = 1;
  }
  fld_e247 = *(this + 247);
  v6 = 0;
  if ( fld_e247 != 0 )
  {
    if ( fld_e247 == 1 && sub_699000((int)(this + 9)) >= *(this + 245) )  // 【clock_now(clk)】
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(
        this,
        2,
        *(uint32_t *)(*(this + 36) + 20),
        0,
        0,
        0,
        1);
      *(this + 247) = 2;
    }
  }
  else if ( sub_699000((int)(this + 9)) >= *(this + 244) )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8));
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 12));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(
      this,
      2,
      *(uint32_t *)(*(this + 36) + 16),
      0,
      0,
      0,
      1);
    *(this + 247) = 1;
  }
  pThis_10 = sub_699000((int)(this + 16));  // 【clock_now(clk)】
  if ( (uint8_t)sub_6072C0(pThis_10) != 0 )
  {
    fld_e29 = *(this + 29);
    v9 = *(uint32_t *)(fld_e29 + 120);
    v10 = fld_e29 + 116;
    fld_e176 = v9 != 0 ? (*(uint32_t *)(v10 + 8) - v9) >> 2 : 0;
    v29 = 0;
    if ( fld_e176 > 0 )
    {
      while ( 1 )
      {
        fld_e292 = *(this + 29);
        v12 = *(uint32_t *)(fld_e292 + 120);
        if ( v12 != 0 && v6 < (*(uint32_t *)(fld_e292 + 124) - v12) >> 2 )
          pObj = *(uint32_t *)(v12 + 4 * v6);
        else
          pObj = 0;
        v14 = sub_613FB0(pObj);
        fld_e2432 = *(this + 243);
        if ( fld_e2432 == 25 || fld_e2432 == 41 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )
          {
            if ( v14 != 0 )
              sub_614B30(pObj);
            else
              sub_614930(pObj);
          }
        }
        else if ( fld_e2432 == 36 && v14 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )
        {
          v16 = *(uint32_t *)pObj;
          v21 = 0.0;
          v22 = 0.0;
          v23 = 0.0;
          v24 = 0;
          v25 = 0;
          v26 = 0;
          v17 = (*(int (/*thiscall*/ **)(int))(v16 + 120))(pObj);
          v18 = *(uint32_t *)pObj;
          fld_e262 = v17;
          v21 = (float)v17;
          fld_e262 = (*(int (/*thiscall*/ **)(int))(v18 + 124))(pObj);
          v19 = *(uint32_t *)pObj;
          v22 = (float)fld_e262;
          fld_e262 = (*(this + 262) - (*(int (/*thiscall*/ **)(int))(v19 + 128))(pObj)) / 2;
          v23 = (float)fld_e262;
          sub_4E5F70(v14, (int)this, pObj, &v21, 1, 1);
        }
        if ( (int)++v29 >= fld_e176 )
          break;
        v6 = v29;
      }
    }
  }
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  if ( result >= *(this + 246) )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  return result;
}


// ------------------------------------------------------------
// 0x614F90 sub_614F90
// ------------------------------------------------------------
int /*thiscall*/ sub_614F90(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 1065353216;
  *(uint8_t *)(this + 996) = 0;
  *(uint8_t *)(this + 997) = 0;
  *(uint8_t *)(this + 998) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x614FD0 sub_614FD0
// ------------------------------------------------------------
int /*thiscall*/ sub_614FD0(uint32_t *this)
{
  uint32_t *pThis_F4; // esi
  int i; // edi
  int result; // eax

  pThis_F4 = this + 244;
  for ( i = 4; i != 0; --i )
  {
    if ( *pThis_F4 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_F4)(*pThis_F4, 1);
    *pThis_F4++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x615000 CNFireWave__vmt2A8
// ------------------------------------------------------------
// CNFireWave 碰撞响应槽（vmt2A8）：sub_47E720/47EF20/47EFD0 + sub_4921E0 —— 火浪（FireWave）推移判定。
char /*thiscall*/ CNFireWave__vmt2A8(int this, int nArg2)
{
  int v3; // eax
  char *v4; // eax
  int fld_2C0; // ebx
  char *v6; // edi
  int pThis_184; // eax
  float v9; // [esp+Ch] [ebp+8h]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, nArg2);
  LOBYTE(v3) = *(uint8_t *)(this + 996);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = (char *)sub_47E720(0, 0x16u);
    fld_2C0 = *(uint32_t *)(this + 704);
    v6 = v4;
    v9 = (double)sub_47EF20(v4, 2u, fld_2C0, -1, -1, 11) * 0.0099999998;
    *(float *)(this + 992) = v9;
    sub_4921E0(v9);
    pThis_184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
    v3 = sub_47EFD0(v6, COERCE_FLOAT(1), fld_2C0, pThis_184, pThis_184, 0);
    *(uint32_t *)(this + 972) = v3;
    *(uint8_t *)(this + 996) = 1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x615090 CNFireWave__vmt1F4
// ------------------------------------------------------------
// CNFireWave 命中表现槽（vmt1F4）：sub_4E4A50 —— 火浪命中发包。
int /*thiscall*/ CNFireWave__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int v4; // eax
  int v6; // edi
  int v7; // eax
  int v9; // [esp-18h] [ebp-24h]
  int v10; // [esp-14h] [ebp-20h]
  int v11; // [esp+8h] [ebp-4h] BYREF

  v4 = *pArg2;
  v11 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v4 + 648))(pArg2, &v11, this);
  if ( pszArg4 == 0
    && v11 > 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0
    && *((uint8_t *)this + 998) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg2 + 308))(pArg2) != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )
        v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + 55;
      else
        v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 55;
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + 50;
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      sub_4E4A50(*(this + 173), 40002, *(this + 243), v6, v7, v9, v10, 0, 0, 0);
    }
    *((uint8_t *)this + 998) = 1;
  }
  return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x615180 CNFireWave__vmt14C
// ------------------------------------------------------------
// CNFireWave 主循环槽（vmt14C）：字符串证据「FIREWAVE_MOVING」（音效 TAG —— 火浪推进循环）。
// sub_4600B0 + sub_4920E0 —— 火浪推进演出；出生粒子四件套见 0x6152E0。
void /*thiscall*/ CNFireWave__vmt14C(uint8_t *this)
{
  int v2; // ebx
  int pThis_23; // edi
  int pThis_7C; // eax
  int v5; // edx
  uint32_t *Block2; // edi
  uint32_t *v7; // eax
  float pThis_F8; // [esp-4h] [ebp-34h]
  uint8_t v9[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  uint32_t *v11; // [esp+14h] [ebp-1Ch]
  int v12; // [esp+18h] [ebp-18h]
  int pThis_7C2; // [esp+1Ch] [ebp-14h]
  int v14; // [esp+20h] [ebp-10h]
  int v15; // [esp+2Ch] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 996) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "FIREWAVE_MOVING",
      0,
      0,
      0);
    *(this + 996) = 1;
  }
  v2 = 0;
  do
  {
    if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this) != 0 )
      pThis_23 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) + 35;
    else
      pThis_23 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) - 35;
    pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this);
    v5 = *(uint32_t *)this;
    pThis_7C2 = pThis_7C;
    v14 = (*(int (/*thiscall*/ **)(uint8_t *))(v5 + 128))(this);
    if ( v2 == 2 )
    {
      if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this) != 0 )
        pThis_23 -= 40;
      else
        pThis_23 += 40;
      v14 += 40;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**((uint32_t **)this + v2 + 244) + 40))(
      *((uint32_t *)this + v2 + 244),
      pThis_23,
      pThis_7C2,
      v14);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**((uint32_t **)this + v2 + 244) + 92))(*((uint32_t *)this + v2 + 244), v9);
    Block2 = Block;
    v15 = 0;
    if ( Block != v11 )
    {
      do
      {
        pThis_F8 = *((float *)this + 248);
        v7 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 200))(*Block2);
        sub_4920E0(v7, pThis_F8, pThis_F8);
        ++Block2;
      }
      while ( Block2 != v11 );
    }
    sub_4600B0(*((void **)this + 29), 2, 0, (int)v9);
    v15 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++v2;
    Block = nullptr;
    v11 = nullptr;
    v12 = 0;
  }
  while ( v2 < 4 );
}



// ------------------------------------------------------------
// 0x6152E0 sub_6152E0
// ------------------------------------------------------------
// 火浪粒子四件套：字符串证据「Particle/FireWaveParticle.ptl | FireWaveParticleTail.ptl |
// FireWaveParticleLight.ptl | FireWaveParticleFloor.ptl」+「FIREWAVE_CREATE」（音效 TAG）——
// 本体/拖尾/光晕/地面层四发射器（P36 发射器组合的典型布局）。
int /*thiscall*/ sub_6152E0(uint32_t *this)
{
  int pThis_5B; // eax
  int pThis_5B2; // eax
  int pThis_5B3; // eax
  int pThis_5B4; // eax

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      pThis_5B = sub_4C3640(this + 91, "Particle/FireWaveParticle.ptl", this);
    else
      pThis_5B = sub_4C3640(*(this + 91), "Particle/FireWaveParticle.ptl", this);
  }
  else
  {
    pThis_5B = 0;
  }
  *(this + 244) = pThis_5B;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      pThis_5B2 = sub_4C3640(this + 91, "Particle/FireWaveParticleTail.ptl", this);
    else
      pThis_5B2 = sub_4C3640(*(this + 91), "Particle/FireWaveParticleTail.ptl", this);
  }
  else
  {
    pThis_5B2 = 0;
  }
  *(this + 245) = pThis_5B2;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      pThis_5B3 = sub_4C3640(this + 91, "Particle/FireWaveParticleLight.ptl", this);
    else
      pThis_5B3 = sub_4C3640(*(this + 91), "Particle/FireWaveParticleLight.ptl", this);
  }
  else
  {
    pThis_5B3 = 0;
  }
  *(this + 246) = pThis_5B3;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      pThis_5B4 = sub_4C3640(this + 91, "Particle/FireWaveParticleFloor.ptl", this);
    else
      pThis_5B4 = sub_4C3640(*(this + 91), "Particle/FireWaveParticleFloor.ptl", this);
  }
  else
  {
    pThis_5B4 = 0;
  }
  *(this + 247) = pThis_5B4;
  return sub_4015C0("FIREWAVE_CREATE", 0xFu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x6154A0 sub_6154A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6154A0(int this)
{
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint8_t *)(this + 1000) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6154C0 sub_6154C0
// ------------------------------------------------------------
void /*thiscall*/ sub_6154C0(uint32_t *this)
{
  *(this + 168) = 3;
}



// ------------------------------------------------------------
// 0x6154D0 CNSpiralNen__vmt14C
// ------------------------------------------------------------
// CNSpiralNen 主循环槽（vmt14C）：sub_6072C0 + sub_699000 —— 螺旋念气（SpiralNen，气功师念气系【推断】）推进。
int /*thiscall*/ CNSpiralNen__vmt14C(uint32_t *this)
{
  int pThis_10; // eax
  int fld_e173; // eax
  int fld_e1732; // edi
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  pThis_10 = sub_699000((int)(this + 16));  // 【clock_now(clk)】
  if ( sub_6072C0((uint8_t *)this + 972, pThis_10) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
  if ( (int)*(this + 170) <= 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  fld_e173 = __RTDynamicCast(
         *(this + 173),
         0,
         &IRDCollisionObject `RTTI Type Descriptor',
         &CNFighter `RTTI Type Descriptor',
         0);
  fld_e1732 = fld_e173;
  if ( fld_e173 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e173 + 840))(fld_e173);
  if ( result == 5 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  if ( *(this + 167) != fld_e1732 )
    *(this + 167) = fld_e1732;
  return result;
}



// ------------------------------------------------------------
// 0x615570 CNSpiralNen__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNSpiralNen__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int fld_e249; // ecx
  int fld_e248; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0 )
  {
    fld_e249 = *(this + 249);
    fld_e248 = *(this + 248) + 1;
    *(this + 248) = fld_e248;
    if ( fld_e249 == fld_e248 )
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x6155D0 CNSpiralNen__vmt2A8
// ------------------------------------------------------------
// CNSpiralNen 碰撞响应槽（vmt2A8）：sub_47E720/47E9D0/47EF20/47EFD0 + sub_607260 —— 螺旋念气命中判定。
char /*thiscall*/ CNSpiralNen__vmt2A8(int this, int nArg2)
{
  int v3; // eax
  int v4; // eax
  int fld_2C0; // ebx
  char *v6; // edi
  int pThis_184; // eax
  int v8; // eax

  CNRDPassiveObject__vmt2A8((uint32_t *)this, nArg2);
  LOBYTE(v3) = *(uint8_t *)(this + 1000);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = sub_47E720(1, 0x28u);
    fld_2C0 = *(uint32_t *)(this + 704);
    v6 = (char *)v4;
    pThis_184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
    *(float *)(this + 724) = (float)sub_47EFD0(v6, 0.0, fld_2C0, pThis_184, pThis_184, 0);
    *(float *)(this + 760) = (double)sub_47EF20(v6, 4u, fld_2C0, -1, -1, 11) * 0.1;
    *(uint32_t *)(this + 772) = sub_47EF20(v6, 5u, fld_2C0, -1, -1, 11);
    *(uint32_t *)(this + 996) = sub_47EF20(v6, 2u, fld_2C0, -1, -1, 11);
    v8 = sub_47E9D0(v6, 0);
    sub_607260((uint32_t *)(this + 972), v8, -1, 0, 0);
    *(uint32_t *)(this + 992) = 0;
    v3 = sub_47EF20(v6, 3u, fld_2C0, -1, -1, 11);
    *(uint32_t *)(this + 684) = v3;
    *(uint32_t *)(this + 680) = v3;
    *(uint8_t *)(this + 1000) = 1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x6156D0 sub_6156D0
// ------------------------------------------------------------
void /*thiscall*/ sub_6156D0(int this)
{
  if ( *(uint32_t *)(this + 976) != 0 )
    j__free(*(void **)(this + 976));
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
}



// ------------------------------------------------------------
// 0x615710 CNClosePunchSub__vmt160
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNClosePunchSub__vmt160(uint32_t *this)
{
  unsigned int result; // eax
  unsigned int i; // edi
  int fld_e244; // ecx

  result = (unsigned int)IRDCollisionObject__vmt160(this);
  for ( i = 0; ; ++i )
  {
    fld_e244 = *(this + 244);
    if ( fld_e244 == 0 )
      break;
    result = (*(this + 245) - fld_e244) >> 2;
    if ( i >= result )
      break;
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 356))(this, *(uint32_t *)(fld_e244 + 4 * i));
  }
  return result;
}



// ------------------------------------------------------------
// 0x615760 CNClosePunchSub__vmt12C
// ------------------------------------------------------------
// CNClosePunchSub 消亡联动槽（vmt12C）：近身拳子判定（ClosePunchSub）的收尾。
uint32_t */*thiscall*/ CNClosePunchSub__vmt12C(uint32_t *this, int nArg2)
{
  uint32_t *fld_e245; // ecx
  uint32_t *result; // eax

  CNRDPassiveObject__vmt12C(this, nArg2);
  fld_e245 = (uint32_t *)*(this + 245);
  result = (uint32_t *)*(this + 244);
  if ( result != fld_e245 )
  {
    do
    {
      if ( *result == nArg2 )
        break;
      ++result;
    }
    while ( result != fld_e245 );
    if ( result != fld_e245 )
    {
      memcpy_0(result, result + 1, 4 * ((*(this + 245) - (int)(result + 1)) >> 2));
      result = (uint32_t *)(*(this + 245) - 4);
      *(this + 245) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6157C0 CNClosePunchSub__vmt2A8
// ------------------------------------------------------------
// CNClosePunchSub 碰撞响应槽（vmt2A8）：sub_428220 —— 近身拳（贴身打击）判定响应。
unsigned int /*thiscall*/ CNClosePunchSub__vmt2A8(uint32_t *this, int nArg2)
{
  unsigned int v3; // ebx
  unsigned int result; // eax
  unsigned int pObj; // edi
  void *fld_e244; // eax
  uint32_t *pThis_F3; // esi
  int v8; // ecx
  int *v9; // edi
  int v10; // ecx
  unsigned int v11; // edx
  int *v12; // eax
  int v13; // [esp+14h] [ebp+8h]

  CNRDPassiveObject__vmt2A8(this, nArg2);
  v3 = 0;
  result = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNFighter `RTTI Type Descriptor', 0);
  pObj = result;
  if ( result != 0 )
  {
    fld_e244 = (void *)*(this + 244);
    pThis_F3 = this + 243;
    if ( fld_e244 != nullptr )
      j__free(fld_e244);
    pThis_F3[1] = 0;
    pThis_F3[2] = 0;
    pThis_F3[3] = 0;
    result = (*(int (/*thiscall*/ **)(unsigned int))(*(uint32_t *)pObj + 1336))(pObj);
    v13 = result;
    while ( 1 )
    {
      v8 = *(uint32_t *)(result + 4);
      if ( v8 == 0 )
        break;
      result = (*(uint32_t *)(result + 8) - v8) >> 3;
      if ( v3 >= result )
        break;
      v9 = (int *)(v8 + 8 * v3);
      v10 = pThis_F3[1];
      if ( v10 != 0 )
        v11 = (pThis_F3[2] - v10) >> 2;
      else
        v11 = 0;
      if ( v10 != 0 && v11 < (pThis_F3[3] - v10) >> 2 )
      {
        v12 = (int *)pThis_F3[2];
        *v12 = *v9;
        pThis_F3[2] = v12 + 1;
        result = v13;
        ++v3;
      }
      else
      {
        sub_428220((int)pThis_F3, pThis_F3[2], 1u, v9);
        result = v13;
        ++v3;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x615890 sub_615890
// ------------------------------------------------------------
int /*thiscall*/ sub_615890(int this, int nArg2)
{
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = nArg2;
  *(uint8_t *)(this + 988) = 0;
  *(uint8_t *)(this + 701) = 0;
  *(uint8_t *)(this + 700) = 0;
  *(uint32_t *)(this + 972) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6158C0 CNGunnerLaser__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNGunnerLaser__vmt12C(int *this, int nArg2)
{
  int fld_e243; // ecx
  int fld_e2432; // ecx
  int fld_e2433; // [esp-4h] [ebp-Ch]

  fld_e243 = *(this + 243);
  if ( nArg2 == fld_e243 )
  {
    fld_e2433 = fld_e243;
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_e243 + 1160))(39);
    sub_47DD30(fld_e2433);
    *(this + 243) = 0;
  }
  if ( (int *)nArg2 == this )
  {
    fld_e2432 = *(this + 243);
    if ( fld_e2432 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2432 + 840))(fld_e2432) == 22 )
      sub_4C34F0(*(this + 245));
  }
  CNRDPassiveObject__vmt12C(this, nArg2);
}



// ------------------------------------------------------------
// 0x615930 CNGunnerLaser__vmt14C
// ------------------------------------------------------------
// CNGunnerLaser 主循环槽（vmt14C，148 行）：字符串证据「G_LASERGUNB | G_LASERGUNA」（音效 TAG ——
// 激光枪 B/A 双版本）。sub_4926A0/sub_4938F0 + sub_600890 —— 激光束的持续照射编排（激光 PO 化直证）。
int /*usercall*/ sub_615930@<eax>(float *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // eax
  int pObj4; // eax
  int pObj3; // edi
  unsigned int v7; // eax
  int64_t v8; // rax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edi
  unsigned int v13; // edx
  int v14; // edi
  unsigned int v15; // ebx
  int v16; // edi
  char *v17; // ebx
  int v18; // eax
  int v19; // eax
  int pObj6; // ecx
  int v21; // edi
  char *v22; // ebx
  int v23; // eax
  unsigned int v24; // eax
  int pObj5; // eax
  unsigned int v26; // eax
  int pObj; // ecx
  int result; // eax
  int v29; // [esp-Ch] [ebp-14h]
  int pObj2; // [esp-4h] [ebp-Ch]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  if ( *((uint8_t *)pArg1 + 988) == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 684))(pArg1);
    pObj4 = __RTDynamicCast(v4, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);
    *((uint32_t *)pArg1 + 243) = pObj4;
    if ( pObj4 != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 1140))(pObj4, 41, nArg3, nArg2) > 0 )
      {
        pObj3 = *((uint32_t *)pArg1 + 243);
        v29 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 1140))(pObj3, 41, -1);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 1160))(pObj3);
        *((uint32_t *)pArg1 + 244) = sub_47EF20(41, 0, v29, -1, 11);
      }
      v7 = *((uint32_t *)pArg1 + 244);
      if ( v7 != 0 && *((uint32_t *)pArg1 + 245) >= v7 )
      {
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*((uint32_t *)pArg1 + 36) + 8));
        pArg1[246] = *(float *)(*((uint32_t *)pArg1 + 36) + 12);
        pObj2 = *((uint32_t *)pArg1 + 243);
        (*(void (**)(void))(*(uint32_t *)pObj2 + 1160))();
        sub_47DCD0(39, pObj2);
      }
      else
      {
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, **((uint32_t **)pArg1 + 36));
        pArg1[246] = *(float *)(*((uint32_t *)pArg1 + 36) + 4);
      }
      if ( (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 152))(pArg1) != 0 )
      {
        v9 = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)pArg1 + 29) + 132) + 44);
        v10 = *(uint32_t *)(v9 + 364);
        v11 = v9 + 360;
        if ( v10 != 0 )
          v12 = (*(uint32_t *)(v11 + 8) - v10) >> 5;
        else
          v12 = 0;
        v8 = 1374389535LL * (224 * v12 - (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 120))(pArg1));
      }
      else
      {
        v8 = 1374389535LL * (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 120))(pArg1);
      }
      v13 = SHIDWORD(v8) >> 4;
      if ( (int)(v13 + (v13 >> 31)) > 0 )
      {
        v14 = 0;
        v15 = v13 + (v13 >> 31);
        do
        {
          (*(void (/*thiscall*/ **)(float *, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
            pArg1,
            0,
            *((uint32_t *)pArg1 + 246),
            v14,
            0,
            0,
            0);
          v14 += 50;
          --v15;
        }
        while ( v15 != 0 );
      }
      sub_4926A0(*((uint32_t *)pArg1 + 30));
      sub_4938F0(*((uint32_t *)pArg1 + 246));
      sub_4938F0(*((uint32_t *)pArg1 + 30));
      v16 = (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)pArg1 + 243) + 1140))(*((uint32_t *)pArg1 + 243), 39);
      v17 = (char *)sub_47E720(2, 39);
      v18 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)pArg1 + 243) + 388))(*((uint32_t *)pArg1 + 243));
      v19 = sub_47EFD0(v17, 0.0, v16, v18, v18, 0);
      pObj6 = *((uint32_t *)pArg1 + 243);
      pArg1[97] = (float)v19;
      v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 1140))(pObj6, 41);
      if ( v21 > 0 )
      {
        v22 = (char *)sub_47E720(2, 41);
        v23 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 388))(pArg1);
        pArg1[97] = (double)((unsigned int)(sub_47EFD0(v22, COERCE_FLOAT(1), v21, v23, v23, 0) * *((uint32_t *)pArg1 + 245))
                        / *((uint32_t *)pArg1 + 244))
               + pArg1[97];
      }
      v24 = *((uint32_t *)pArg1 + 244);
      if ( v24 != 0
        && *((uint32_t *)pArg1 + 245) >= v24
        && (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)pArg1 + 243) + 792))(*((uint32_t *)pArg1 + 243), 8) != 0 )
      {
        pObj5 = (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)pArg1 + 243) + 792))(*((uint32_t *)pArg1 + 243), 8);
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 16))(pObj5) + 4) == 32239 )
          pArg1[97] = pArg1[97] * 1.2;
      }
      v26 = *((uint32_t *)pArg1 + 244);
      if ( v26 != 0 && *((uint32_t *)pArg1 + 245) >= v26 )
        (*(void (/*thiscall*/ **)(float *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
          pArg1,
          "G_LASERGUNB",
          -1,
          0,
          0);
      else
        (*(void (/*thiscall*/ **)(float *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
          pArg1,
          "G_LASERGUNA",
          -1,
          0,
          0);
    }
    *((uint8_t *)pArg1 + 988) = 1;
  }
  pObj = *((uint32_t *)pArg1 + 243);
  if ( pObj == 0 )
    return (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)pArg1 + 312))(pArg1, 0);
  if ( *(uint8_t *)(*((uint32_t *)pArg1 + 30) + 170) != 0 )
    return (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)pArg1 + 312))(pArg1, 0);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj);
  if ( result != 22 )
    return (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)pArg1 + 312))(pArg1, 0);
  return result;
}


// ------------------------------------------------------------
// 0x615C90 sub_615C90
// ------------------------------------------------------------
int /*thiscall*/ sub_615C90(uint32_t *this)
{
  *(this + 250) = 0;
  *(this + 251) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x615CA0 sub_615CA0
// ------------------------------------------------------------
bool /*thiscall*/ sub_615CA0(uint32_t *this, int nArg2)
{
  int v3; // ebx

  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);
  return v3 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 128))(nArg2) <= 3 * *(this + 251) / 2
      && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, nArg2, 0) <= *(this + 251);
}



// ------------------------------------------------------------
// 0x615D10 sub_615D10
// ------------------------------------------------------------
// 激光辅助（41 行）：sub_47E720/47EF20（命中几何）+ sub_4922F0 + sub_698F90（时钟复位）——
// 激光束扫描的时钟重置【推断：束宽帧同步】。
int /*thiscall*/ sub_615D10(uint8_t *this, int nArg2)
{
  uint32_t *v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // ebx
  float v9; // [esp+14h] [ebp+8h]

  v3 = (uint32_t *)sub_47E720(1, 0x2Au);
  v4 = sub_47EF20(v3, 0, nArg2, -1, -1, 11);
  *(this + 985) = 0;
  *(this + 986) = 0;
  sub_698F90((int)(this + 972), v4 + 400, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  v5 = sub_47EF20(v3, 2u, nArg2, -1, -1, 11);
  v6 = *(uint32_t *)this;
  *((uint32_t *)this + 171) = v5;
  *((uint32_t *)this + 170) = v5;
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(v6 + 204))(
    this,
    0,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    1);
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    0,
    *(uint32_t *)(*((uint32_t *)this + 36) + 4),
    0,
    0,
    0,
    0);
  v7 = sub_47EF20(v3, 1u, nArg2, -1, -1, 11);
  v9 = (double)v7 * 0.0041666669;
  sub_4922F0(v9);
  sub_4922F0(v9);
  sub_4922F0(v9);
  *((uint32_t *)this + 251) = v7 / 2;
  return v7 / 2;
}



// ------------------------------------------------------------
// 0x615E20 CNNenGuard__vmt12C
// ------------------------------------------------------------
// CNNenGuard 消亡联动槽（vmt12C）：sub_41C5E0 + sub_4BE520 + sub_52E6A0 ——
// 念气护盾（NenGuard，气功师念气罩的护盾侧）消散时的状态回收。
int /*thiscall*/ CNNenGuard__vmt12C(int **this, int nArg2)
{
  int **v2; // edi
  int *fld_e253; // ecx
  int result; // eax
  int v6; // ebx
  int v7; // [esp+8h] [ebp-4h] BYREF

  v2 = (int **)nArg2;
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( v2 == this )
  {
    fld_e253 = *(this + 253);
    result = *fld_e253;
    nArg2 = *fld_e253;
    if ( (int *)nArg2 != fld_e253 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(**(uint32_t **)(result + 16) + 612))(
          *(uint32_t *)(result + 16),
          0,
          0);
        sub_41C5E0(&nArg2);
        result = nArg2;
      }
      while ( (int *)nArg2 != *(this + 253) );
    }
  }
  else
  {
    result = ((int (/*thiscall*/ *)(int **, int))(*v2)[10])(v2, 17);
    if ( (uint8_t)result != 0 )
    {
      nArg2 = (int)v2;
      result = sub_4BE520(&v7, &nArg2);
      v6 = v7;
      if ( (int *)v7 != *(this + 253) )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(**(uint32_t **)(v7 + 16) + 612))(*(uint32_t *)(v7 + 16), 0, 0);
        return sub_52E6A0(&nArg2, v6);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x615ED0 CNNenGuard__vmt14C
// ------------------------------------------------------------
// CNNenGuard 主循环槽（vmt14C，136 行）：sub_491C70/493A60（动画族）+ sub_52E6A0 + sub_614810（鬼神目标表复用）+
// sub_615CA0 + sub_698F90/699000（时钟）—— 护盾持续期间的吸收/反弹编排【推断】。
int /*thiscall*/ sub_615ED0(void *this)  // 【CNNenGuard__vmt14C】
{
  int pThis_F9; // ebx
  unsigned int v3; // edi
  int pThis_1D; // eax
  int v5; // ecx
  int v6; // eax
  int pThis_1D2; // ecx
  int v8; // edx
  int v9; // eax
  int **v10; // edi
  int pThis_FA; // eax
  int pThis_1E; // edi
  int v13; // ecx
  int v14; // eax
  int pThis_F92; // edi
  int pThis_1E2; // edi
  int v17; // eax
  int pThis_24; // edi
  int v19; // eax
  uint32_t *pThis_FD; // ecx
  uint32_t *v21; // eax
  int pThis_F93; // edi
  int result; // eax
  uint32_t v24[2]; // [esp+Ch] [ebp-1Ch] BYREF
  char v25[4]; // [esp+14h] [ebp-14h] BYREF
  int **v26; // [esp+18h] [ebp-10h] BYREF
  uint32_t *i; // [esp+1Ch] [ebp-Ch] BYREF
  int v28; // [esp+20h] [ebp-8h]
  int **v29; // [esp+24h] [ebp-4h] BYREF

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  if ( *((int *)this + 170) <= 0 )
  {
    pThis_F9 = *((uint32_t *)this + 249);
    if ( sub_699000((int)this + 972) < pThis_F9 - 400 )  // 【clock_now(clk)】
    {
      *((uint8_t *)this + 985) = 0;
      *((uint8_t *)this + 986) = 0;
      sub_698F90((int)this + 972, 400, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
  }
  v3 = 0;
  if ( *((uint32_t *)this + 250) <= 1u )
  {
    pThis_1D = *((uint32_t *)this + 29);
    v5 = *(uint32_t *)(pThis_1D + 120);
    v6 = pThis_1D + 116;
    v28 = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 2 : 0;
    for ( i = nullptr; (int)i < v28; i = (uint32_t *)((char *)i + 1) )
    {
      pThis_1D2 = *((uint32_t *)this + 29);
      v8 = *(uint32_t *)(pThis_1D2 + 120);
      if ( v8 != 0 && v3 < (*(uint32_t *)(pThis_1D2 + 124) - v8) >> 2 )
        v9 = *(uint32_t *)(v8 + 4 * v3);
      else
        v9 = 0;
      v10 = (int **)__RTDynamicCast(
                      v9,
                      0,
                      &IRDCollisionObject `RTTI Type Descriptor',
                      &IRDActiveObject `RTTI Type Descriptor',
                      0);
      v26 = v10;
      if ( v10 != nullptr )
      {
        sub_4BE520(&v29, &v26);
        if ( (uint8_t)sub_615CA0(v10) != 0 )
        {
          if ( v29 == *((int ***)this + 253) )
          {
            v24[0] = v10;
            v24[1] = v10;
            sub_614810(v25, v24);
          }
          ((void (/*thiscall*/ *)(int **, int, int))(*v10)[153])(v10, 1, 2);
        }
        else if ( v29 != *((int ***)this + 253) )
        {
          ((void (/*thiscall*/ *)(int **, uint32_t, uint32_t))(*v10)[153])(v10, 0, 0);
          sub_52E6A0((uint32_t *)this + 252, &v26, v29);
        }
      }
      v3 = (unsigned int)i + 1;
    }
  }
  pThis_FA = *((uint32_t *)this + 250);
  pThis_1E = *((uint32_t *)this + 30);
  v13 = *(uint32_t *)(pThis_1E + 148);
  if ( pThis_FA != 0 )
  {
    if ( pThis_FA == 1 )
    {
      if ( v13 < 9 )
      {
        pThis_F92 = *((uint32_t *)this + 249);
        if ( sub_699000((int)this + 972) > pThis_F92 - 400 )  // 【clock_now(clk)】
        {
          pThis_1E2 = *((uint32_t *)this + 30);
          *((uint32_t *)this + 250) = 2;
          v17 = sub_491C70(pThis_1E2, 10);
          sub_493A60(pThis_1E2, v17);
          pThis_24 = **((uint32_t **)this + 36);
          v19 = sub_491C70(pThis_24, 5);
          sub_493A60(pThis_24, v19);
          pThis_FD = *((uint32_t **)this + 253);
          v21 = (uint32_t *)*pThis_FD;
          i = (uint32_t *)*pThis_FD;
          if ( i != pThis_FD )
          {
            do
            {
              (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)v21[4] + 612))(v21[4], 0, 0);
              sub_41C5E0(&i);
              v21 = i;
            }
            while ( i != *((uint32_t **)this + 253) );
          }
        }
      }
      else
      {
        v14 = sub_491C70(pThis_1E, 4);
        sub_493A60(pThis_1E, v14);
      }
    }
  }
  else if ( v13 >= 4 )
  {
    *((uint32_t *)this + 250) = 1;
  }
  pThis_F93 = *((uint32_t *)this + 249);
  result = sub_699000((int)this + 972);  // 【clock_now(clk)】
  if ( result >= pThis_F93 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}


// ------------------------------------------------------------
// 0x616130 sub_616130
// ------------------------------------------------------------
int /*thiscall*/ sub_616130(uint32_t *this)
{
  *(this + 243) = 0;
  *(this + 244) = 0;
  *(this + 245) = 0;
  *(this + 246) = 0;
  *(this + 247) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x616160 sub_616160
// ------------------------------------------------------------
int /*thiscall*/ sub_616160(uint32_t *this, int nArg2)
{
  uint32_t *v3; // edi
  uint64_t v4; // rax
  int result; // eax

  v3 = (uint32_t *)sub_47E720(0, 0x2Cu);
  *(this + 247) = nArg2;
  *(this + 243) = sub_47EF20(v3, 0, nArg2, -1, -1, 11);
  *(this + 244) = sub_47EF20(v3, 1u, nArg2, -1, -1, 11);
  v4 = (uint64_t)(1000.0 / (double)sub_47EF20(v3, 2u, nArg2, -1, -1, 11));
  *(this + 245) = v4;
  result = -(int)v4;
  *(this + 246) = result;
  return result;
}



// ------------------------------------------------------------
// 0x6161F0 sub_6161F0
// ------------------------------------------------------------
// 落点调度器（71 行）：消费 dword_7930D0（研究 20 P36 ⑤ 直证的 P9 全局时间域 tick 基址）+ unk_9B93A8 参数块 +
// sub_490410/sub_6BFF30 —— 墓碑雨（TombStoneRain，下一分区）落点的时间域插值调度【推断】。
uint64_t /*cdecl*/ sub_6161F0(uint32_t *uArg1, uint32_t *uArg2, float fArg3)
{
  int v3; // ecx
  float fArg32; // ebx
  float *i; // eax
  unsigned int v6; // ecx
  float v7; // edi
  uint32_t *v8; // esi
  int nRand; // eax
  int v10; // ecx
  void *dword_9B93AC2; // esi
  int nRand2; // eax
  int v13; // esi
  double v14; // st7
  uint64_t result; // rax
  uint32_t v16[4]; // [esp+0h] [ebp-10h] BYREF

  v16[0] = v3;
  if ( (dword_9B93B8 & 1) == 0 )
  {
    dword_9B93B8 |= 1u;
    dword_9B93AC = nullptr;
    dword_9B93B0 = nullptr;
    dword_9B93B4 = 0;
    atexit(sub_6BFF30);
    v16[3] = -1;
  }
  fArg32 = fArg3;
LABEL_4:
  for ( i = (float *)dword_9B93B0; ; dword_9B93B0 = i )
  {
    while ( dword_9B93AC == nullptr )
    {
LABEL_8:
      fArg3 = 0.0;
      if ( dword_9B93AC == nullptr
        || ((char *)i - (uint8_t *)dword_9B93AC) >> 2 >= (unsigned int)((dword_9B93B4 - (int)dword_9B93AC) >> 2) )
      {
LABEL_14:
        sub_430C80((int)&unk_9B93A8, (int)i, 1u, (int *)&fArg3);
        goto LABEL_4;
      }
      *i++ = 0.0;
      dword_9B93B0 = i;
    }
    v6 = ((char *)i - (uint8_t *)dword_9B93AC) >> 2;
    if ( v6 > LODWORD(fArg32) )
      break;
    if ( v6 == 0 )
      goto LABEL_8;
    LODWORD(v7) = v6 + *((uint32_t *)i - 1);
    fArg3 = v7;
    if ( v6 >= (dword_9B93B4 - (int)dword_9B93AC) >> 2 )
      goto LABEL_14;
    *i++ = v7;
  }
  v8 = (char *)dword_9B93AC + 4 * LODWORD(fArg32);
  nRand = rand();
  v10 = *v8 + 1;
  dword_9B93AC2 = dword_9B93AC;
  LODWORD(fArg3) = nRand % v10;
  sub_490410(v16, dword_9B93AC, (char *)dword_9B93AC + 4 * LODWORD(fArg32), &fArg3);
  LODWORD(fArg3) = (v16[0] - (int)dword_9B93AC2) >> 2;
  nRand2 = rand();
  fArg3 = (float)SLODWORD(fArg3);
  v13 = nRand2 % 360;
  *uArg1 = (uint64_t)(sub_405400(nRand2 % 360) * (double)dword_7930D0[0] * fArg3 * 0.0099999998);
  v14 = sub_4053E0(v13);
  result = (uint64_t)(v14 * (double)dword_7930D4[0] * fArg3 * 0.0099999998);
  *uArg2 = result;
  return result;
}



// ============================================================
// 【分区 10】法师投射物与陷阱（0x616390-0x61AE90）
// 墓碑雨/空投炸弹/大波动/诱饵/变换珠 CNChaser（含可被打的珠体 0x6183A0）/
// 魔法飞弹/南瓜灯/冰霜魔偶头/黑猫/万圣破坏者 —— 魔道与召唤技能的 PO 投射物
// ============================================================
// ------------------------------------------------------------
// 0x616390 CNTombStoneRain__vmt14C
// ------------------------------------------------------------
// CNTombStoneRain 主循环槽（vmt14C）：sub_432FA0（UDP 广播）+ sub_6161F0（落点调度，消费 P9 时间域）——
// 墓碑雨（鬼泣「墓碑」大招的落石阵列）的落点时间域编排。
int /*thiscall*/ CNTombStoneRain__vmt14C(int *this)
{
  int v2; // edx
  int v3; // edi
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // edi
  int nRand; // eax
  int fld_e173; // ecx
  int result; // eax
  int fld_e1732; // eax
  int pObj; // edi
  float pThis_F3; // [esp-8h] [ebp-18h]
  int v14; // [esp+8h] [ebp-8h] BYREF
  int v15; // [esp+Ch] [ebp-4h] BYREF

  CNRDPassiveObject__vmt14C((int)this);
  if ( sub_699000((int)(this + 9)) >= *(this + 246) + *(this + 245) )  // 【clock_now(clk)】
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      sub_432FA0();
      pThis_F3 = *((float *)this + 243);
      v15 = 0;
      v14 = 0;
      v2 = sub_6161F0(&v15, &v14, pThis_F3) >> 32;
      v3 = *this;
      v4 = (*(int (/*fastcall*/ **)(int *, int, uint32_t))(*this + 124))(this, v2, 0);
      v5 = v14;
      v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v14 + v4);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v3 + 136))(this, v15 + v6) != 0 )
      {
        v7 = *this;
        nRand = rand() % 2;
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, int, int, uint32_t, bool, uint32_t, uint32_t, uint32_t))(v7 + 580))(
          this,
          20015,
          *(this + 247),
          0,
          0,
          v15,
          v5,
          0,
          nRand != 0,
          0,
          0,
          0);
      }
    }
    *(this + 246) += *(this + 245);
  }
  if ( sub_699000((int)(this + 9)) >= *(this + 244) )  // 【clock_now(clk)】
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  fld_e173 = *(this + 173);
  if ( fld_e173 == 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e173 + 40))(fld_e173, 529);
  if ( (uint8_t)result == 0 )
  {
    fld_e1732 = __RTDynamicCast(
            *(this + 173),
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &CNSwordman `RTTI Type Descriptor',
            0);
    pObj = fld_e1732;
    if ( fld_e1732 == 0 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1732 + 840))(fld_e1732) != 10 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1280))(pObj) != 0 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1284))(pObj);
    if ( result != 44 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x616500 sub_616500
// ------------------------------------------------------------
char /*thiscall*/ sub_616500(uint8_t *this)
{
  *(this + 972) = 0;
  *(this + 973) = 0;
  *(this + 974) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x616520 CNTombStone__vmt2A8
// ------------------------------------------------------------
// CNTombStone 碰撞响应槽（vmt2A8）：sub_47E720/47EF20/47EFD0 —— 单块墓碑的砸落判定。
char /*thiscall*/ CNTombStone__vmt2A8(int *this, int nArg2)
{
  int v3; // eax
  char *v4; // eax
  int fld_e176; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // edx
  int v9; // eax

  CNRDPassiveObject__vmt2A8(this, nArg2);
  LOBYTE(v3) = *((uint8_t *)this + 972);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = (char *)sub_47E720(0, 0x2Cu);
    fld_e176 = *(this + 176);
    v6 = v4;
    *(this + 193) = sub_47EF20(v4, 4u, fld_e176, -1, -1, 11);
    v7 = sub_47EF20(v6, 5u, fld_e176, -1, -1, 11);
    v8 = *this;
    *((float *)this + 190) = (double)v7 * 0.1;
    v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 388))(this);
    v3 = sub_47EFD0(v6, COERCE_FLOAT(3), fld_e176, v9, v9, 0);
    *((uint8_t *)this + 972) = 1;
    *((float *)this + 181) = (float)v3;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x6165C0 CNTombStone__vmt14C
// ------------------------------------------------------------
// CNTombStone 主循环槽（vmt14C）：字符串证据「TOMBTONE_STUCK | TOMBSTONE_DIG」（音效 TAG —— 插地/挖掘，
// TOMBTONE 为原版拼写）+ sub_424120（震屏）—— 墓碑落地插地的震屏演出。
int /*thiscall*/ CNTombStone__vmt14C(void *this)
{
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 973) == 0 && *(int *)(*((uint32_t *)this + 30) + 148) >= 2 )
  {
    sub_424120(
      *(uint32_t **)(*((uint32_t *)this + 29) + 132),
      **((uint32_t **)this + 87),
      *(uint32_t *)(*((uint32_t *)this + 87) + 4));
    (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "TOMBTONE_STUCK",
      -1,
      0,
      0);
    *((uint8_t *)this + 973) = 1;
  }
  if ( *((uint8_t *)this + 974) == 0 && *(int *)(*((uint32_t *)this + 30) + 148) >= 4 )
  {
    (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "TOMBSTONE_DIG",
      -1,
      0,
      0);
    *((uint8_t *)this + 974) = 1;
  }
  result = *((uint32_t *)this + 30);
  if ( *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x616670 sub_616670
// ------------------------------------------------------------
int /*thiscall*/ sub_616670(uint32_t *this)
{
  unsigned int i; // ecx
  int fld_e36; // edx
  unsigned int v4; // edi

  for ( i = 0; ; i = v4 )
  {
    fld_e36 = *(this + 36);
    if ( fld_e36 == 0 || i >= (*(this + 37) - fld_e36) >> 2 )
      break;
    v4 = i + 1;
    (*(void (/*thiscall*/ **)(uint32_t *, unsigned int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      i + 1,
      *(uint32_t *)(fld_e36 + 4 * i),
      0,
      0,
      0,
      0);
  }
  return sub_4015C0("TOMBSTONE_DROP", 0xEu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x6166D0 sub_6166D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6166D0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint8_t *)(this + 976) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6166E0 CNDropBomb__vmt12C
// ------------------------------------------------------------
// CNDropBomb 消亡联动槽（vmt12C，88 行）：字符串证据「%s/%s」（路径拼接模板）。
// sub_5C6A50/5C6A90/5DAE20 + sub_47E720 族 + sub_4E4A50 —— 落弹（空投炸弹）的爆炸分发【推断：弹坑/残留物生成】。
void /*userpurge*/ CNDropBomb__vmt12C(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3)
{
  int v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // ebx
  int v13; // eax
  int v14; // edi
  int v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  void *v19; // ecx
  int v20; // [esp-10h] [ebp-44h]
  int v21; // [esp-Ch] [ebp-40h]
  int v22; // [esp-8h] [ebp-3Ch]
  float v23; // [esp+4h] [ebp-30h]
  float v24; // [esp+4h] [ebp-30h]
  char v25[4]; // [esp+10h] [ebp-24h] BYREF
  void *Block; // [esp+14h] [ebp-20h]
  int dword_78FE2C2; // [esp+20h] [ebp-14h]
  int dword_78FE282; // [esp+24h] [ebp-10h]
  int v29; // [esp+30h] [ebp-4h]
  int pArg12; // [esp+3Ch] [ebp+8h]

  CNRDPassiveObject__vmt12C((uint32_t *)pArg1, nArg3);
  if ( nArg3 == pArg1 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 308))(pArg1, nArg2) != 0
      && *(uint32_t *)(pArg1 + 284) == 22206 )
    {
      v4 = sub_47E720(2, 0x2Du);
      v5 = *(uint32_t *)(pArg1 + 704);
      v6 = (char *)v4;
      dword_78FE2C = 0;
      sub_5C6A90(100);
      sub_5C6A90(0);
      sub_5C6A50(6);
      v23 = (double)sub_47EF20(v6, 1u, v5, -1, -1, 11) * 0.1;
      sub_5DAE20(LODWORD(v23));
      v24 = (float)sub_47EF20(v6, 2u, v5, -1, -1, 11);
      sub_5DAE20(LODWORD(v24));
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 684))(pArg1) != 0 )
        pArg12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 684))(pArg1);
      else
        pArg12 = pArg1;
      v7 = *(uint32_t *)pArg1;
      dword_78FE282 = dword_78FE28;
      dword_78FE2C2 = dword_78FE2C;
      v8 = (*(int (/*thiscall*/ **)(int))(v7 + 388))(pArg1);
      v9 = sub_47EFD0(v6, 0.0, v5, v8, v8, 0);
      v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);
      v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1) + 20;
      v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1);
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1);
      sub_4E4A50(pArg12, 22208, v9, v10, v20, v21, v22, 0, dword_78FE2C2, dword_78FE282);
    }
    if ( *(uint32_t *)(pArg1 + 384) < 0x10u )
      v11 = pArg1 + 364;
    else
      v11 = *(uint32_t *)(pArg1 + 364);
    v12 = *(uint32_t *)dword_8F84E4;
    v13 = sub_41ACF0(*(uint32_t *)(pArg1 + 712));
    v14 = (*(int (**)(int, const char *, ...))(v12 + 12))(dword_8F84E4, "%s/%s", v11, v13);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 972) + 112))(*(uint32_t *)(pArg1 + 972), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 972) + 8))(*(uint32_t *)(pArg1 + 972), v14);
    v15 = **(uint32_t **)(pArg1 + 972);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);
    v17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v16 + 40);
    v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v17);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v15 + 40))(*(uint32_t *)(pArg1 + 972), v18);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 972) + 12))(*(uint32_t *)(pArg1 + 972), 0);
    (*(void (/*thiscall*/ **)(uint32_t, char *))(**(uint32_t **)(pArg1 + 972) + 92))(*(uint32_t *)(pArg1 + 972), v25);
    v19 = *(void **)(pArg1 + 116);
    v29 = 0;
    sub_4600B0(v19, 2, 0, (int)v25);
    sub_424120(
      *(uint32_t **)(*(uint32_t *)(pArg1 + 116) + 132),
      *(uint32_t *)(*(uint32_t *)(pArg1 + 348) + 8),
      *(uint32_t *)(*(uint32_t *)(pArg1 + 348) + 12));
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x616950 CNDropBomb__vmt14C
// ------------------------------------------------------------
// CNDropBomb 主循环槽（vmt14C）：字符串证据「BOMB_DROP」（音效 TAG）+ sub_4600B0 —— 空投炸弹下落演出。
void /*thiscall*/ CNDropBomb__vmt14C(uint32_t *this)
{
  int fld_e243; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  void *fld_e29; // ecx
  uint8_t v7[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v9; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 976) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BOMB_DROP", -1, 0, 0);
    *((uint8_t *)this + 976) = 1;
  }
  fld_e243 = *(uint32_t *)*(this + 243);
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v3 + 70);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v4);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e243 + 40))(*(this + 243), v5);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v7);
  fld_e29 = (void *)*(this + 29);
  v9 = 0;
  sub_4600B0(fld_e29, 2, 0, (int)v7);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x616A10 sub_616A10
// ------------------------------------------------------------
int /*thiscall*/ sub_616A10(int this)
{
  int pThis_16C; // eax
  int fld_15C; // eax
  int v4; // edx

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      pThis_16C = sub_4C3640(this + 364, "Particle/DropBombTail.ptl", this);
    else
      pThis_16C = sub_4C3640(*(uint32_t *)(this + 364), "Particle/DropBombTail.ptl", this);
  }
  else
  {
    pThis_16C = 0;
  }
  *(uint32_t *)(this + 972) = pThis_16C;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_16C + 112))(pThis_16C, this);
  *(float *)(*(uint32_t *)(this + 112) + 24) = (float)**(int **)(this + 348);
  fld_15C = *(uint32_t *)(this + 348);
  v4 = *(uint32_t *)(fld_15C + 4);
  *(uint32_t *)(*(uint32_t *)(this + 112) + 36) = v4;
  return fld_15C + 4;
}



// ------------------------------------------------------------
// 0x616AD0 sub_616AD0
// ------------------------------------------------------------
char /*thiscall*/ sub_616AD0(void *this, int nArg2)
{
  int pThis_3D0; // ecx

  pThis_3D0 = (int)this + 976;
  *(float *)(pThis_3D0 - 252) = (float)nArg2;
  *(uint8_t *)(pThis_3D0 + 13) = 0;
  *(uint8_t *)(pThis_3D0 + 14) = 0;
  return sub_698F90(pThis_3D0, 300, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x616B00 CNTreadShootSub__vmt2A8
// ------------------------------------------------------------
int /*thiscall*/ CNTreadShootSub__vmt2A8(uint32_t *this, int nArg2)
{
  int result; // eax

  CNRDPassiveObject__vmt2A8(this, nArg2);
  result = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);
  if ( result != 0 )
  {
    result = *(uint32_t *)(result + 8700);
    *(this + 243) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x616B40 CNTreadShootSub__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNTreadShootSub__vmt14C(void *this)
{
  int pThis_3D0; // ecx
  int v3; // edi
  int result; // eax

  pThis_3D0 = (int)this + 976;
  v3 = *(uint32_t *)(pThis_3D0 + 24);
  result = sub_699000(pThis_3D0);  // 【clock_now(clk)】
  if ( result >= v3 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x616B70 CNIceNiddle__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNIceNiddle__vmt14C(int *this)
{
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  result = *(this + 30);
  if ( *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x616BA0 CNAshenForkSub__vmt2A8
// ------------------------------------------------------------
// CNAshenForkSub 碰撞响应槽（vmt2A8）：sub_47E9D0/47EFD0 —— 灰烬叉子判定（SAJAHU_SPREAD TAG 见 0x616C60）。
char /*thiscall*/ CNAshenForkSub__vmt2A8(int this, int nArg2)
{
  int pObj2; // eax
  int pObj; // esi
  char *v5; // ebx
  int v6; // eax
  int v8; // [esp+10h] [ebp+8h]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, nArg2);
  LOBYTE(pObj2) = *(uint8_t *)(this + 976);
  if ( (uint8_t)pObj2 == 0 )
  {
    pObj2 = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSwordman `RTTI Type Descriptor', 0);
    pObj = pObj2;
    if ( pObj2 != 0 )
    {
      v5 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 1160))(pObj2, 16);
      v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, 16);
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);
      *(float *)(this + 724) = (float)sub_47EFD0(v5, COERCE_FLOAT(1), v8, v6, v6, 0);
      pObj2 = sub_47E9D0(v5, 3u);
      *(float *)(this + 724) = ((double)pObj2 * (double)*(int *)(this + 972) * 0.000099999997 + 1.0)
                             * *(float *)(this + 724);
    }
    *(uint8_t *)(this + 976) = 1;
  }
  return pObj2;
}



// ------------------------------------------------------------
// 0x616C60 sub_616C60
// ------------------------------------------------------------
// 灰烬辅助：字符串证据「SAJAHU_SPREAD」（音效 TAG —— 萨朱扩散【推断：灰烬散布】）。
// sub_4922F0 + sub_4015C0 —— 散布参数装配。
unsigned int /*thiscall*/ sub_616C60(float *this, float fArg2)
{
  uint32_t *pThis_24; // eax
  float v4; // edx
  int pThis_242; // eax
  uint32_t *v6; // edi
  int v7; // ebx
  unsigned int result; // eax
  unsigned int i; // edi
  int pThis_243; // ecx
  float v11; // [esp+14h] [ebp+8h]

  pThis_24 = *((uint32_t **)this + 36);
  v4 = *this;
  *(this + 243) = fArg2;
  (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int))(LODWORD(v4) + 204))(2, *pThis_24, 0, 0, 0, 1);
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 204))(
    this,
    1,
    *(uint32_t *)(*((uint32_t *)this + 36) + 4),
    0,
    0,
    0,
    1);
  pThis_242 = *((uint32_t *)this + 36);
  if ( pThis_242 != 0 && (unsigned int)((*((uint32_t *)this + 37) - pThis_242) >> 2) > 2 )
    (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
      this,
      1,
      *(uint32_t *)(pThis_242 + 8),
      0,
      0,
      0,
      0);
  sub_4015C0("SAJAHU_SPREAD", 0xDu);  // 【std::string构造赋值】
  v6 = (uint32_t *)sub_47E720(0, 0x10u);
  v7 = LODWORD(fArg2) * sub_47E9D0(v6, 5u) / 100;
  v11 = (double)(sub_47E9D0(v6, 4u) + v7) * 0.0099999998;
  result = sub_4922F0(v11);
  for ( i = 0; ; ++i )
  {
    pThis_243 = *((uint32_t *)this + 36);
    if ( pThis_243 == 0 )
      break;
    result = (*((uint32_t *)this + 37) - pThis_243) >> 2;
    if ( i >= result )
      break;
    result = sub_4922F0(v11);
  }
  return result;
}



// ------------------------------------------------------------
// 0x616D90 CNGrabBlastBlood__vmt2BC
// ------------------------------------------------------------
void /*userpurge*/ CNGrabBlastBlood__vmt2BC(int pArg1@<ecx>, int nArg2@<ebx>, float *pArg3, size_t Size)
{
  int v5; // eax
  int v6; // eax

  CNRDPassiveObject__vmt2BC((int)pArg3, Size);
  v5 = sub_45EBE0(*(uint32_t **)(pArg1 + 116), *(uint16_t *)pArg3, *((uint16_t *)pArg3 + 1));
  v6 = __RTDynamicCast(v5, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  *(uint32_t *)(pArg1 + 972) = v6;
  if ( v6 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )
    sub_4E5F70(nArg2, pArg1, *(uint32_t *)(pArg1 + 972), pArg3 + 1, 1, 0);
}



// ------------------------------------------------------------
// 0x616E10 CNGrabBlastBlood__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNGrabBlastBlood__vmt12C(uint32_t *this, int nArg2)
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( *(this + 243) == nArg2 )
    *(this + 243) = 0;
}



// ------------------------------------------------------------
// 0x616E40 CNGrabBlastBlood__vmt1F0
// ------------------------------------------------------------
int /*thiscall*/ CNGrabBlastBlood__vmt1F0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  if ( nArg2 == *(this + 243) )
    *(this + 112) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x616E60 CNGrabBlastBlood__vmt1F8
// ------------------------------------------------------------
int /*thiscall*/ CNGrabBlastBlood__vmt1F8(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  if ( nArg2 == *(this + 243) )
    *(this + 112) = 2;
  return 0;
}



// ------------------------------------------------------------
// 0x616E80 sub_616E80
// ------------------------------------------------------------
int /*thiscall*/ sub_616E80(float *this, int nArg2)
{
  uint32_t *pThis_24; // eax
  float v3; // edx

  pThis_24 = *((uint32_t **)this + 36);
  v3 = *this;
  *(this + 181) = (float)nArg2;
  return (*(int (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(LODWORD(v3) + 204))(1, *pThis_24, 0, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x616EB0 sub_616EB0
// ------------------------------------------------------------
int /*thiscall*/ sub_616EB0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint8_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x616ED0 CNGrandWave__vmt2A8
// ------------------------------------------------------------
// CNGrandWave 碰撞响应槽（vmt2A8）：sub_4049C0（lerp）+ dword_795A0C ——
// 大波动（GrandWave）的浪高插值与判定。
void /*thiscall*/ CNGrandWave__vmt2A8(int this, int nArg2)
{
  int pObj2; // eax
  int pObj; // esi
  char *v5; // ebx
  int v6; // eax
  double v7; // st7
  int fld_3CC; // eax
  char *v9; // ebx
  int v10; // eax
  float v11; // [esp+10h] [ebp-18h]
  int v12; // [esp+30h] [ebp+8h]
  int v13; // [esp+30h] [ebp+8h]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, nArg2);
  if ( *(uint8_t *)(this + 976) == 0 )
  {
    pObj2 = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSwordman `RTTI Type Descriptor', 0);
    pObj = pObj2;
    if ( pObj2 != 0 )
    {
      v5 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 1160))(pObj2, 50);
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, 50);
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);
      v7 = (double)sub_47EFD0(v5, COERCE_FLOAT(1), v12, v6, v6, 0);
      fld_3CC = *(uint32_t *)(this + 972);
      *(float *)(this + 724) = v7;
      if ( fld_3CC > 0 )
      {
        v9 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1160))(pObj, 51);
        v13 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, 51);
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);
        v11 = (float)sub_47EFD0(v9, 0.0, v13, v10, v10, 0);
        *(float *)(this + 724) = sub_4049C0(0.0, v11, *(uint32_t *)(this + 972), dword_795A0C) + *(float *)(this + 724);
      }
    }
    *(uint8_t *)(this + 976) = 1;
  }
}



// ------------------------------------------------------------
// 0x616FE0 CNGrandWave__vmt14C
// ------------------------------------------------------------
// CNGrandWave 主循环槽（vmt14C）：sub_4600B0 + sub_699000 + dword_8F82A0 —— 大波动推进与池化槽。
void /*usercall*/ CNGrandWave__vmt14C(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int pObj; // edi
  bool v5; // bl
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  uint8_t v12[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v14; // [esp+14h] [ebp-10h]
  int v15; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)pArg1);
  if ( sub_699000((int)(pArg1 + 9)) >= pArg1[245] + 100 )  // 【clock_now(clk)】
  {
    pObj = dword_8F82A0;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 152))(pArg1, nArg3, nArg2) == 0;
    *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj) + 84) = v5;
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1) != 0 )
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - 40;
    else
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) + 40;
    v7 = *(uint32_t *)pObj;
    v14 = v6;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v8);
    (*(void (/*thiscall*/ **)(int, int, int))(v7 + 40))(pObj, v14, v9);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);
    (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj + 92))(pObj, v12);
    v10 = (void *)pArg1[29];
    v15 = 0;
    sub_4600B0(v10, 2, 0, (int)v12);
    pArg1[245] = sub_699000((int)(pArg1 + 9));  // 【clock_now(clk)】
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x6170E0 sub_6170E0
// ------------------------------------------------------------
// 大波动生成辅助：字符串证据「AIR_SWORD」（音效 TAG —— 空中剑气）。sub_47E720/47E9D0 + sub_4922F0 ——
// 剑气浪的生成判定（上挑系剑气 PO 化【推断】）。
int /*thiscall*/ sub_6170E0(void *this, float fArg2)
{
  float v3; // edx
  uint32_t *v4; // eax
  float v6; // [esp+18h] [ebp-14h]
  int pThis_F3; // [esp+1Ch] [ebp-10h]
  int dword_795A0C2; // [esp+20h] [ebp-Ch]
  float v9; // [esp+34h] [ebp+8h]

  v3 = *(float *)this;
  *((float *)this + 243) = fArg2;
  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(LODWORD(v3) + 204))(
    this,
    2,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  if ( *((int *)this + 243) > 0 )
  {
    v4 = (uint32_t *)sub_47E720(0, 0x33u);
    dword_795A0C2 = dword_795A0C;
    pThis_F3 = *((uint32_t *)this + 243);
    v6 = (double)sub_47E9D0(v4, 1u) * 0.0099999998;
    v9 = sub_4049C0(1.0, v6, pThis_F3, dword_795A0C2);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    sub_4922F0(v9);
    sub_4922F0(v9);
    if ( *((uint32_t *)this + 243) >= dword_795A0C )
    {
      (*(void (/*thiscall*/ **)(void *, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        1,
        *((uint32_t *)this + 34),
        -20,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        3,
        **((uint32_t **)this + 36),
        -20,
        0,
        0,
        0);
      *((uint32_t *)this + 196) = 2;
    }
  }
  return sub_4015C0("AIR_SWORD", 9u);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x6171F0 sub_6171F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6171F0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 1;
  *(uint8_t *)(this + 980) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x617210 CNDecoy__vmt10
// ------------------------------------------------------------
char /*thiscall*/ CNDecoy__vmt10(int this)
{
  char result; // al
  int fld_78; // edi
  int fld_3CC; // eax

  CNRDPassiveObject__vmt10((uint8_t *)this);
  result = *(uint8_t *)(this + 980);
  if ( result == 0 )
  {
    fld_78 = *(uint32_t *)(this + 120);
    fld_3CC = sub_491C70(fld_78, *(uint32_t *)(this + 972));
    sub_493A60(fld_78, fld_3CC);
    result = sub_4939E0(*(uint32_t *)(this + 120), 1);
    *(uint8_t *)(this + 980) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x617250 CNDecoy__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNDecoy__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int v5; // edi
  uint32_t *v6; // eax
  int fld_e244; // edi
  int v8; // eax
  int v10; // [esp+Ch] [ebp-4h]

  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 376))(pArg2);
  if ( v5 == (*(int (/*thiscall*/ **)(int *))(*this + 376))(this)
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 273) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg2 + 308))(pArg2) != 0 )
  {
    v6 = (uint32_t *)sub_47E720(3, 3u);
    fld_e244 = sub_47EF20(v6, 6u, *(this + 244), -1, -1, 11);
    if ( fld_e244 > 0 )
    {
      v10 = *pArg2;
      v8 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 684))(this, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(v10 + 760))(pArg2, 12, 1120403456, fld_e244, v8);
      (*(void (/*thiscall*/ **)(int *, int))(*this + 312))(this, 1);
    }
  }
  return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x617310 sub_617310
// ------------------------------------------------------------
int /*thiscall*/ sub_617310(int this, int nArg2)
{
  int nRand; // edx
  int fld_70; // eax

  nRand = rand() % 3;
  fld_70 = *(uint32_t *)(this + 112);
  *(uint32_t *)(this + 972) = nRand;
  *(uint32_t *)(this + 976) = nArg2;
  *(uint32_t *)(fld_70 + 24) = 1128792064;
  *(uint32_t *)(*(uint32_t *)(this + 112) + 36) = -800;
  *(uint8_t *)(this + 700) = 0;
  return sub_4015C0("PHASE_SHIFT", 0xBu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x617370 sub_617370
// ------------------------------------------------------------
// CNDecoy 命中判定：字符串证据「PHASE_SHIFT」（音效 TAG —— 相位转移）。
// sub_47E720/47EF20 + sub_4B3C90 —— 诱饵（Decoy）受击触发的相位闪避判定【推断：机械师诱饵被打时隐身】。
int /*thiscall*/ sub_617370(int *this, int nArg2)
{
  int result; // eax
  uint32_t *v4; // ebx
  int fld_e244; // eax
  int pObj; // esi
  void *v7; // ebx
  void *v8; // ebx
  void *v9; // ebx
  float fld_e2442; // [esp+24h] [ebp-28h]
  float fld_e2443; // [esp+24h] [ebp-28h]
  float fld_e2444; // [esp+24h] [ebp-28h]
  float fld_e2445; // [esp+24h] [ebp-28h]
  void *Block; // [esp+34h] [ebp-18h]
  uint32_t *v15; // [esp+3Ch] [ebp-10h]

  result = nArg2;
  if ( nArg2 != 0 )
  {
    v4 = (uint32_t *)sub_47E720(3, 3u);
    v15 = v4;
    if ( operator new(0x7Cu) != nullptr )
    {
      fld_e244 = sub_47EF20(v4, 1u, *(this + 244), -1, -1, 11);
      pObj = sub_4B3C90(fld_e244, 1);
    }
    else
    {
      pObj = 0;
    }
    Block = *(void **)pObj;
    fld_e2442 = (float)sub_47EF20(v4, 2u, *(this + 244), -1, -1, 11);
    (*((void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))Block + 30))(pObj, 8, 0, LODWORD(fld_e2442));
    v7 = *(void **)pObj;
    fld_e2443 = (float)sub_47EF20(v15, 3u, *(this + 244), -1, -1, 11);
    (*((void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))v7 + 30))(pObj, 7, 0, LODWORD(fld_e2443));
    v8 = *(void **)pObj;
    fld_e2444 = (float)sub_47EF20(v15, 4u, *(this + 244), -1, -1, 11);
    (*((void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))v8 + 30))(pObj, 0, 0, LODWORD(fld_e2444));
    v9 = *(void **)pObj;
    fld_e2445 = (float)sub_47EF20(v15, 5u, *(this + 244), -1, -1, 11);
    (*((void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))v9 + 30))(pObj, 1, 0, LODWORD(fld_e2445));
    return (*(int (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t, int, int))(*(uint32_t *)pObj + 56))(
             pObj,
             nArg2,
             *(this + 173),
             1,
             0,
             10,
             -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6174E0 sub_6174E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6174E0(uint32_t *this)
{
  if ( sub_699000((int)(this + 9)) < *(this + 244) )  // 【clock_now(clk)】
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 2, 0, 0, 0);
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 5, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x617520 sub_617520
// ------------------------------------------------------------
int /*thiscall*/ sub_617520(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 4;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint8_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 1004) = 0;
  *(uint8_t *)(this + 1008) = 0;
  *(uint32_t *)(this + 1012) = 0;
  *(uint32_t *)(this + 1016) = 0;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1028) = 0;
  *(uint32_t *)(this + 1032) = 0;
  *(uint32_t *)(this + 1036) = 0;
  *(uint8_t *)(this + 1040) = 0;
  *(uint32_t *)(this + 1044) = -1;
  *(uint32_t *)(this + 960) = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x6175B0 CNChaser__vmt2A8
// ------------------------------------------------------------
// CNChaser 碰撞响应槽（vmt2A8）：sub_47EF20/47EFD0 + dword_73C3CC ——
// 追击者/变换珠（Chaser，法师光/暗/冰/火珠）的环绕判定。
char /*userpurge*/ CNChaser__vmt2A8@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3)
{
  int pObj2; // eax
  int pObj; // ebx
  char *v6; // edi
  int v7; // ebx
  int v8; // eax
  double v9; // st7
  char v10; // al
  int v11; // eax
  int pObj3; // [esp+10h] [ebp+8h]

  CNRDPassiveObject__vmt2A8((uint32_t *)pArg1, nArg3);
  LOBYTE(pObj2) = *(uint8_t *)(pArg1 + 972);
  if ( (uint8_t)pObj2 == 0 )
  {
    pObj2 = __RTDynamicCast(nArg3, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
    pObj = pObj2;
    pObj3 = pObj2;
    if ( pObj2 == 0 )
    {
LABEL_12:
      *(uint8_t *)(pArg1 + 972) = 1;
      return pObj2;
    }
    v6 = (char *)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj2 + 1160))(
                   pObj2,
                   dword_73C3CC[*(uint32_t *)(pArg1 + 980)],
                   nArg2);
    v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, dword_73C3CC[*(uint32_t *)(pArg1 + 980)]);
    *(uint32_t *)(pArg1 + 976) = sub_47EF20(v6, 0, v7, -1, -1, 11);
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 388))(pObj3);
    v9 = (double)sub_47EFD0(v6, COERCE_FLOAT(1), v7, v8, v8, 0);
    v10 = *(uint8_t *)(pArg1 + 1008);
    *(float *)(pArg1 + 724) = v9;
    if ( v10 != 0 )
      *(float *)(pArg1 + 724) = v9 + v9;
    v11 = *(uint32_t *)(pArg1 + 980);
    if ( v11 != 0 )
    {
      if ( v11 == 1 )
      {
        *(float *)(pArg1 + 760) = (double)sub_47EF20(v6, 2u, v7, -1, -1, 11) * 0.1;
        *(uint32_t *)(pArg1 + 772) = sub_47EF20(v6, 3u, v7, -1, -1, 11);
LABEL_11:
        LOBYTE(pObj2) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 344))(pArg1, pArg1 + 724);
        goto LABEL_12;
      }
      if ( v11 != 2 && v11 != 3 )
        goto LABEL_11;
    }
    *(uint32_t *)(pArg1 + 788) = sub_47EF20(v6, 2u, v7, -1, -1, 11);
    *(uint32_t *)(pArg1 + 792) = sub_47EF20(v6, 3u, v7, -1, -1, 11);
    goto LABEL_11;
  }
  return pObj2;
}



// ------------------------------------------------------------
// 0x617720 sub_617720
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_617720(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3, int nArg4)
{
  int v4; // edx

  *uArg1 = -30 - 8 * nArg4;
  *uArg2 = (uint64_t)(sub_405400(110 * nArg4 % 360) * (double)dword_7930D4[0] * 0.2);
  v4 = 60 - (uint64_t)(sub_4053E0(110 * nArg4 % 360) * -20.0);
  *uArg3 = v4;
  return uArg3;
}



// ------------------------------------------------------------
// 0x617790 CNChaser__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNChaser__vmt12C(uint32_t *this, int nArg2)
{
  int v3; // eax
  int v4; // eax

  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( nArg2 == *(this + 254) )
    *(this + 254) = 0;
  if ( (uint32_t *)nArg2 == this )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    v4 = __RTDynamicCast(v3, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
    if ( v4 != 0 )
      sub_5DC290(v4);
  }
}



// ------------------------------------------------------------
// 0x6177F0 sub_6177F0
// ------------------------------------------------------------
// 珠体辅助：sub_42B420 + sub_699000 ——【推断：珠体环绕角速度的时间域积分】。
int /*thiscall*/ sub_6177F0(uint32_t *this, int nArg2, int pArg3, char pszArg4)
{
  int v4; // esi
  uint32_t *pThis; // eax
  int fld_e246; // esi
  int v7; // eax
  int v9; // [esp-8h] [ebp-18h]
  int v10; // [esp-8h] [ebp-18h]

  v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 116))(nArg2, pArg3);
  if ( pArg3 != 0 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 152))(nArg2) != 0 )
  {
    pThis = this;
    fld_e246 = *(this + pArg3 + 246) + v4;
  }
  else
  {
    pThis = this;
    fld_e246 = v4 - *(this + 246);
  }
  if ( pszArg4 != 0 )
  {
    if ( pArg3 == 0 )
    {
      v9 = sub_699000((int)(pThis + 9));  // 【clock_now(clk)】
      v7 = sub_42B420(-3, 3, v9, 400);
LABEL_10:
      fld_e246 += v7;
      return fld_e246;
    }
    if ( pArg3 == 2 )
    {
      v10 = sub_699000((int)(pThis + 9));  // 【clock_now(clk)】
      v7 = sub_42B420(-5, 5, v10, 70);
      goto LABEL_10;
    }
  }
  return fld_e246;
}



// ------------------------------------------------------------
// 0x617880 sub_617880
// ------------------------------------------------------------
int /*thiscall*/ sub_617880(int *this, int nArg2)
{
  int result; // eax

  if ( *(this + 249) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 249));
  result = nArg2;
  *(this + 249) = nArg2;
  if ( nArg2 != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(this, 1, nArg2, 0, 0, 0, 0);
    return sub_4926A0(*(this + 249));
  }
  return result;
}



// ------------------------------------------------------------
// 0x6178D0 CNChaser__vmt10
// ------------------------------------------------------------
// CNChaser 初始化（vmt10）：珠体初值装配。
char /*usercall*/ CNChaser__vmt10@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>)
{
  char result; // al
  int pObj; // esi
  int v6; // eax
  int v8; // [esp+8h] [ebp-4h]

  CNRDPassiveObject__vmt10((uint8_t *)pArg1);
  result = *(uint8_t *)(pArg1 + 1000);
  if ( result == 0 )
  {
    pObj = *(uint32_t *)(pArg1 + 692);
    if ( pObj != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 116))(pObj, 2, nArg2, nArg3);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 116))(pObj, 1);
      v8 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 116))(pObj, 0);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 152))(pObj) != 0 )
        v6 = *(uint32_t *)(pArg1 + 984) + v8;
      else
        v6 = v8 - *(uint32_t *)(pArg1 + 984);
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 112))(pArg1, v6);
    }
    *(uint8_t *)(pArg1 + 1000) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x617970 sub_617970
// ------------------------------------------------------------
// 珠体发射辅助（111 行）：字符串证据「CHASER_LAUNCH」（音效 TAG —— 珠体发射）。
// sub_4049C0/4049F0（lerp 对）+ dword_73C3AC —— 珠体从环绕切向发射的参数插值。
int /*thiscall*/ sub_617970(int *this)
{
  int result; // eax
  int i; // edi
  int v4; // ebx
  int fld_e173; // eax
  int v6; // ecx
  uint8_t *fld_e28; // ebx
  int v8; // edi
  int fld_e254; // ebx
  int fld_e256; // ebx
  int pThis_9; // eax
  int fld_e255; // edx
  double v13; // st7
  float v14; // [esp+14h] [ebp-34h]
  float v15; // [esp+18h] [ebp-30h]
  int v16; // [esp+34h] [ebp-14h]
  int v17; // [esp+38h] [ebp-10h]
  int v18; // [esp+3Ch] [ebp-Ch]
  int fld_e1732; // [esp+40h] [ebp-8h]
  float v20; // [esp+44h] [ebp-4h]

  result = *(this + 240);
  if ( result == 2 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( result >= *(this + 253) + 100 )
      {
        result = *(this + 173);
        if ( result != 0 )
        {
          for ( i = 0; i < 3; ++i )
          {
            v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 116))(this, i);
            fld_e173 = sub_6177F0(*(this + 173), i, 1);
            v6 = dword_73C3AC[i];
            fld_e1732 = fld_e173;
            v20 = sub_4049C0(0.0, flt_73C3B8[i], abs32(fld_e173 - v4), v6);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            if ( fld_e1732 >= v4 )
            {
              if ( fld_e1732 == v4 )
                v20 = 0.0;
            }
            else
            {
              v20 = v20 * -1.0;
            }
            fld_e28 = (uint8_t *)*(this + 28);
            if ( *(uint32_t *)fld_e28 != 0
              && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)fld_e28 + 308))(*(uint32_t *)fld_e28) != 0
              && *(float *)&fld_e28[4 * i + 16] != v20 )
            {
              *(float *)&fld_e28[4 * i + 16] = v20;
              fld_e28[196] = 1;
            }
          }
          result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
          *(this + 253) = result;
        }
      }
    }
  }
  else if ( result == 3 )
  {
    result = *(this + 254);
    v8 = 0;
    if ( result != 0 )
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( result > *(this + 255) )
      {
        if ( *((uint8_t *)this + 1040) == 0 )
        {
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
            this,
            "CHASER_LAUNCH",
            -1,
            0,
            0);
          *((uint8_t *)this + 1040) = 1;
        }
        v16 = 0;
        v17 = 0;
        v18 = 0;
        do
        {
          fld_e254 = *(this + 254);
          v20 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e254 + 116))(fld_e254, v8));
          if ( v8 != 0 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e254 + 152))(fld_e254) != 0 )
            LODWORD(v20) += *(this + v8 + 246);
          else
            LODWORD(v20) -= *(this + 246);
          fld_e256 = *(this + 256);
          pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
          fld_e255 = *(this + 255);
          v15 = (float)SLODWORD(v20);
          fld_e1732 = *(this + v8 + 257);
          v13 = (double)fld_e1732;
          v14 = v13;
          sub_4049F0(v14, v15, pThis_9 - fld_e255, fld_e256, 0);
          *(&v16 + v8++) = (uint64_t)v13;
        }
        while ( v8 < 3 );
        return (*(int (/*thiscall*/ **)(int *, int, int, int))(*this + 112))(this, v16, v17, v18);
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x617B80 sub_617B80
// ------------------------------------------------------------
// 珠体参数块读取：dword_9B93C4/9B93C8 ——【推断：珠体全局参数（与 9B93xx 活动装备块相邻）】。
unsigned int sub_617B80()
{
  int i; // esi
  unsigned int j; // ebx
  int v2; // ecx
  unsigned int result; // eax
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  for ( i = 0; i < 20; i += 4 )
  {
    for ( j = 0; ; ++j )
    {
      v2 = dword_9B93C4[i];
      if ( v2 == 0 )
        break;
      result = (dword_9B93C8[i] - v2) >> 2;
      if ( j >= result )
        break;
      v4 = *(void (/*thiscall*/ ****)(uint32_t, int))(dword_9B93C4[i] + 4 * j);
      if ( v4 != nullptr )
        (**v4)(v4, 1);
      result = 4 * j + dword_9B93C4[i];
      *(uint32_t *)result = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x617BF0 CNChaser__vmtC
// ------------------------------------------------------------
float */*thiscall*/ CNChaser__vmtC(int *this)
{
  float *result; // eax

  result = CNRDPassiveObject__vmtC(this);
  if ( *(this + 245) == 2 )
    return (float *)sub_617880(this, *(uint32_t *)(*(this + 36) + 16));
  return result;
}



// ------------------------------------------------------------
// 0x617C20 sub_617C20
// ------------------------------------------------------------
// 珠体辅助：sub_4015C0 + sub_4922F0 ——【推断：珠体动画定位】。
char /*thiscall*/ sub_617C20(uint8_t *this, int nArg2, int nArg3)
{
  int nArg22; // eax
  int v5; // edx
  int pThis_F5; // eax
  unsigned int pThis_25; // eax
  unsigned int i; // edi
  int pThis_24; // ecx

  nArg22 = nArg2;
  if ( nArg2 >= 10000 )
  {
    *(this + 1008) = 1;
    nArg22 = nArg2 - 10000;
  }
  v5 = *(uint32_t *)this;
  *((uint32_t *)this + 251) = nArg22;
  *((uint32_t *)this + 245) = nArg3;
  *(this + 701) = 0;
  *(this + 700) = 0;
  (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, int, int))(v5 + 472))(this, 2, 0, 1, 1);
  pThis_F5 = *((uint32_t *)this + 245);
  *((uint32_t *)this + 168) = 3;
  sub_4015C0(*(&off_795C18 + pThis_F5), strlen((const char *)*(&off_795C18 + pThis_F5)));  // 【std::string构造赋值】
  LOBYTE(pThis_25) = *(this + 1008);
  if ( (uint8_t)pThis_25 != 0 )
  {
    if ( *((uint32_t *)this + 34) != 0 )
      LOBYTE(pThis_25) = sub_4922F0(1.7);
    for ( i = 0; ; ++i )
    {
      pThis_24 = *((uint32_t *)this + 36);
      if ( pThis_24 == 0 )
        break;
      pThis_25 = (*((uint32_t *)this + 37) - pThis_24) >> 2;
      if ( i >= pThis_25 )
        break;
      LOBYTE(pThis_25) = sub_4922F0(1.7);
    }
  }
  return pThis_25;
}



// ------------------------------------------------------------
// 0x617D00 sub_617D00
// ------------------------------------------------------------
// 珠体粒子装载（112 行）：字符串证据「Character/Mage/Effect/Particle/Chaser%s%d.ptl」——
// 按属性+等级格式化的粒子路径模板（光/暗/冰/火 × 编号）。
// sub_428F30（发射器）+ sub_5CC5A0 + dword_73C3E0 —— 变换珠四属性粒子矩阵（dword_796E50 路径根）。
char */*thiscall*/ sub_617D00(int this, int nArg2, int nArg3, int nArg4)
{
  int fld_3D4; // edx
  char *v6; // eax
  int v7; // ecx
  int fld_3D43; // eax
  int v9; // ecx
  uint32_t *pMem; // eax
  uint32_t *v11; // eax
  char *fld_3D42; // ecx
  int v13; // edx
  unsigned int v14; // edi
  uint32_t *v15; // edx
  unsigned int i; // edi
  int fld_3D44; // eax
  int v18; // edx
  char *result; // eax
  int pObj; // esi
  char fld_3F0; // al
  uint32_t *Block2; // esi
  uint32_t *v23; // eax
  int v24; // [esp+Ch] [ebp-128h]
  char v25[4]; // [esp+10h] [ebp-124h] BYREF
  void *Block; // [esp+14h] [ebp-120h]
  uint32_t *v27; // [esp+18h] [ebp-11Ch]
  int v28; // [esp+1Ch] [ebp-118h]
  void *pMem2; // [esp+20h] [ebp-114h] BYREF
  char Buffer[256]; // [esp+24h] [ebp-110h] BYREF
  int dword_796E502; // [esp+124h] [ebp-10h]
  int v32; // [esp+130h] [ebp-4h]

  fld_3D4 = *(uint32_t *)(this + 980);
  dword_796E502 = dword_796E50;
  v6 = (char *)&unk_9B93C0 + 16 * fld_3D4;
  v7 = *((uint32_t *)v6 + 1);
  if ( v7 == 0 || (*((uint32_t *)v6 + 2) - v7) >> 2 == 0 )
  {
    fld_3D43 = fld_3D4;
    v9 = 0;
    if ( dword_73C3E0[fld_3D4] > 0 )
    {
      do
      {
        v24 = v9 + 1;
        sprintf(Buffer, "Character/Mage/Effect/Particle/Chaser%s%d.ptl", off_795C04[fld_3D43], v9 + 1);
        pMem = operator new(0x12Cu);
        pMem2 = pMem;
        v32 = 0;
        if ( pMem != nullptr )
          v11 = sub_428F30(pMem, (int)Buffer, 0);
        else
          v11 = nullptr;
        fld_3D42 = (char *)&unk_9B93C0 + 16 * *(uint32_t *)(this + 980);
        v13 = *((uint32_t *)fld_3D42 + 1);
        v32 = -1;
        pMem2 = v11;
        if ( v13 != 0 )
          v14 = (*((uint32_t *)fld_3D42 + 2) - v13) >> 2;
        else
          v14 = 0;
        if ( v13 != 0 && v14 < (*((uint32_t *)fld_3D42 + 3) - v13) >> 2 )
        {
          v15 = *((uint32_t **)fld_3D42 + 2);
          *v15 = v11;
          *((uint32_t *)fld_3D42 + 2) = v15 + 1;
        }
        else
        {
          sub_5CC5A0(*((void **)fld_3D42 + 2), 1, (int)&pMem2);
        }
        v9 = v24;
        fld_3D43 = *(uint32_t *)(this + 980);
      }
      while ( v24 < dword_73C3E0[fld_3D43] );
    }
  }
  for ( i = 0; ; ++i )
  {
    fld_3D44 = 4 * *(uint32_t *)(this + 980);
    v18 = dword_9B93C4[fld_3D44];
    result = (char *)&unk_9B93C0 + fld_3D44 * 4;
    if ( v18 == 0 || i >= (*((uint32_t *)result + 2) - v18) >> 2 )
      break;
    pObj = *(uint32_t *)(v18 + 4 * i);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 40))(pObj, nArg2, nArg3, nArg4);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj + 92))(pObj, v25);
    fld_3F0 = *(uint8_t *)(this + 1008);
    v32 = 1;
    if ( fld_3F0 != 0 )
    {
      Block2 = Block;
      if ( Block != v27 )
      {
        do
        {
          v23 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 96))(*Block2);
          sub_4922F0(v23, 1.7);
          ++Block2;
        }
        while ( Block2 != v27 );
      }
    }
    sub_4600B0(*(void **)(this + 116), 2, 0, (int)v25);
    v32 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v27 = nullptr;
    v28 = 0;
  }
  return result;
}


// ------------------------------------------------------------
// 0x617F50 CNChaser__vmt14C
// ------------------------------------------------------------
// CNChaser 主循环槽（vmt14C，148 行）：sub_42F220（动画取值）+ sub_4E5F70（硬直率掷）+ sub_600070 +
// sub_617970（发射）/617D00（粒子）+ sub_699000 —— 珠体环绕→锁定→发射的全状态机。
// 动画资源见 0x6183A0（Chaser/StartAttack.ani | Target.ani）。
char /*usercall*/ sub_617F50@<al>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // eax
  int v4; // eax
  int pObj2; // edi
  int v6; // eax
  uint32_t *pArg12; // ecx
  int v8; // eax
  int v9; // eax
  int pObj; // edi
  int v11; // ebx
  int v12; // eax
  int v13; // ebx
  int pObj3; // ecx
  int pObj4; // ecx
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  bool v19; // zf
  int v21; // [esp-Ch] [ebp-30h]
  int v22; // [esp-8h] [ebp-2Ch]
  float v23; // [esp+8h] [ebp-1Ch] BYREF
  float v24; // [esp+Ch] [ebp-18h]
  float v25; // [esp+10h] [ebp-14h]
  int v26; // [esp+14h] [ebp-10h]
  int v27; // [esp+18h] [ebp-Ch]
  int v28; // [esp+1Ch] [ebp-8h]
  int v29; // [esp+20h] [ebp-4h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  v3 = pArg1[240];
  if ( v3 == 2 )
  {
    v4 = pArg1[30];
    if ( v4 == pArg1[34] && *(uint8_t *)(v4 + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)pArg1[36]);
      if ( pArg1[245] == 2 )
        sub_617880(*(uint32_t *)(pArg1[36] + 20));
    }
    pObj2 = __RTDynamicCast(pArg1[173], 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
    if ( pObj2 == 0 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 840))(pObj2) == 5 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);
    }
    else if ( pArg1[167] != pObj2 )
    {
      pArg1[167] = pObj2;
    }
    v3 = sub_699000((int)(pArg1 + 9));  // 【clock_now(clk)】
    if ( v3 >= pArg1[244] )
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 5, 0, 0, 0);
    goto LABEL_40;
  }
  if ( v3 == 3 )
  {
    LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
    if ( (uint8_t)v3 == 0 )
      goto LABEL_40;
    v6 = pArg1[254];
    pArg12 = pArg1;
    if ( v6 != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, v6, 0) <= 480 )
      {
        v3 = sub_699000((int)(pArg1 + 9));  // 【clock_now(clk)】
        if ( v3 < pArg1[255] + pArg1[256] )
          goto LABEL_40;
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[254] + 608))(pArg1[254]) != 0
          && (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[254] + 200))(pArg1[254]) != 0 )
        {
          v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[254] + 200))(pArg1[254]);
          v9 = sub_42F220(v8);
          if ( (uint8_t)sub_600070(v9 + 72) == 0 )
          {
            pObj = pArg1[254];
            v23 = 0.0;
            v24 = 0.0;
            v25 = 0.0;
            v26 = 0;
            v27 = 0;
            v28 = 0;
            v11 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 116))(pObj, 0, nArg2);
            v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 152))(pObj) == 0;
            v12 = pArg1[246];
            if ( v19 )
              v13 = v11 - v12;
            else
              v13 = v12 + v11;
            pObj3 = pArg1[254];
            v29 = v13;
            v23 = (float)v13;
            v29 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 116))(pObj3, 1) + pArg1[247];
            pObj4 = pArg1[254];
            v24 = (float)v29;
            v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 116))(pObj4, 2) + pArg1[248];
            v17 = pArg1[254];
            v29 = v16;
            v25 = (float)v16;
            sub_4E5F70(v13, (int)pArg1, v17, &v23, 1, 1);
LABEL_39:
            LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);
            goto LABEL_40;
          }
        }
      }
      pArg12 = pArg1;
    }
    LOBYTE(v3) = sub_6174E0(pArg12);
    goto LABEL_40;
  }
  if ( v3 != 4 )
  {
    if ( v3 != 5 )
      goto LABEL_40;
    v3 = pArg1[30];
    v19 = *(uint8_t *)(v3 + 170) == 0;
LABEL_38:
    if ( v19 )
      goto LABEL_40;
    goto LABEL_39;
  }
  if ( pArg1[261] == -1 )
  {
    LOBYTE(v3) = *(uint8_t *)(pArg1[30] + 170);
    v19 = (uint8_t)v3 == 0;
    goto LABEL_38;
  }
  v3 = sub_699000((int)(pArg1 + 9));  // 【clock_now(clk)】
  if ( v3 >= pArg1[261] )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[36] + 12));
    if ( pArg1[245] == 2 )
    {
      if ( pArg1[249] != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, pArg1[249]);
      pArg1[249] = 0;
    }
    v22 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
    v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);
    v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
    LOBYTE(v3) = sub_617D00(v18, v21, v22);
    pArg1[261] = -1;
  }
LABEL_40:
  if ( pArg1[154] == -1 )
    LOBYTE(v3) = sub_617970(pArg1);
  return v3;
}


// ------------------------------------------------------------
// 0x618260 CNChaser__vmt1F4
// ------------------------------------------------------------
// CNChaser 命中表现槽（vmt1F4）：sub_431230（字符串入表）+ sub_617D00（粒子）—— 珠体命中演出。
int /*userpurge*/ CNChaser__vmt1F4@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3, float *pArg4, char pszArg5)
{
  uint32_t *v6; // edi
  int v8; // [esp-8h] [ebp-2Ch]
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v10; // [esp+20h] [ebp-4h]

  v6 = (uint32_t *)nArg3;
  if ( pDwArg1[240] == 3 )
  {
    if ( pszArg5 == 0 )
    {
      if ( pDwArg1[245] != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)nArg3 + 124))(nArg3, (uint64_t)pArg4[2]) + 1;
        sub_617D00((int)pDwArg1, (uint64_t)*pArg4, v8, nArg2);
      }
      else if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*pDwArg1 + 308))(pDwArg1, nArg2) != 0 )
      {
        memset(&pBuf[1], 0, 12);
        v10 = 0;
        nArg3 = 0;
        sub_431230((int)pBuf, &nArg3);
        nArg3 = (*(int (/*thiscall*/ **)(uint32_t *))(*v6 + 48))(v6);
        sub_431230((int)pBuf, &nArg3);
        nArg3 = (*(int (/*thiscall*/ **)(uint32_t *))(*v6 + 52))(v6);
        sub_431230((int)pBuf, &nArg3);
        (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 4, pBuf, 0, 0);
        v10 = -1;
        sub_5E5260(pBuf);
      }
      (*(void (/*thiscall*/ **)(int *, char *, int, uint32_t))(*pDwArg1 + 212))(pDwArg1, off_795C2C[pDwArg1[245]], -1, 0);
    }
    if ( v6 == (uint32_t *)pDwArg1[254] )
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 312))(pDwArg1, 0);
  }
  return CNRDPassiveObject__vmt1F4(pDwArg1, v6, pArg4, pszArg5);
}



// ------------------------------------------------------------
// 0x6183A0 CNChaser__vmt1D8
// ------------------------------------------------------------
// ★ CNChaser 受击表现槽（vmt1D8，222 行）：字符串证据「Character/Mage/Effect/Animation/Chaser/
// StartAttack.ani | Target.ani」——珠体被攻击时播放的攻击/锁定动画。
// sub_45EBE0（飘字）+ sub_5DC290 + sub_6000E0（基类飘字）+ sub_4A06D0（挂点跟随）——
// 【新发现】珠体是可以被打的（破坏敌方珠子的机制载体），受击走完整飘字链。
uint32_t */*thiscall*/ sub_6183A0(uint32_t *this, int nArg2, int pArg3, int nArg4, int nArg5)  // 【CNChaser__vmt1D8】
{
  uint32_t *v6; // eax
  uint8_t *v7; // eax
  uint32_t *fld_e36; // eax
  uint32_t *v9; // eax
  int v10; // ebx
  int v11; // edi
  int fld_e254; // ecx
  int v13; // ebx
  char *v14; // eax
  char *v15; // edi
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // ebx
  char *v21; // eax
  char *v22; // edi
  int fld_e248; // ebx
  int fld_e2542; // eax
  int fld_e2543; // edi
  int fld_e246; // eax
  uint32_t *v27; // eax
  uint8_t *v28; // eax
  uint32_t *v29; // ebx
  int i; // eax
  int v31; // eax
  uint32_t *v32; // eax
  uint8_t *v33; // eax
  int j; // ebx
  uint8_t *fld_e28; // edi
  uint32_t *result; // eax
  uint32_t *v37; // edi
  int fld_e240; // [esp+Ch] [ebp-10h]
  uint32_t *pThis_101; // [esp+24h] [ebp+8h]
  int v40; // [esp+24h] [ebp+8h]
  int fld_e247; // [esp+2Ch] [ebp+10h]
  int pObj; // [esp+30h] [ebp+14h]

  fld_e240 = *(this + 240);
  if ( fld_e240 == 2 )
  {
    if ( nArg2 != 2 )
      *(this + 167) = 0;
  }
  else if ( fld_e240 == 3 )
  {
    *(this + 254) = 0;
  }
  sub_6000E0(nArg2, pArg3, nArg4, nArg5);  // 【CNRDPassiveObject__vmt1D8】
  switch ( nArg2 )
  {
    case 2:
      sub_617720(this + 246, this + 247, this + 248, *(this + 251));
      if ( fld_e240 == 3 )
      {
        v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
        v7 = __RTDynamicCast(v6, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
        if ( v7 != nullptr )
        {
          *(this + 251) = -1;
          sub_5DC290(v7);
        }
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
        if ( *(this + 245) == 2 )
        {
          fld_e36 = (uint32_t *)(*(this + 36) + 20);
          goto LABEL_51;
        }
      }
      break;
    case 3:
      v9 = (uint32_t *)sub_45EBE0(**(uint32_t **)(pArg3 + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4));
      *(this + 254) = __RTDynamicCast(
                        v9,
                        0,
                        &CNRDObject `RTTI Type Descriptor',
                        &IRDActiveObject `RTTI Type Descriptor',
                        0);
      *(this + 255) = sub_699000((int)(this + 9)) + 100;
      *(this + 256) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8) - 100;
      *((uint8_t *)this + 1040) = 0;
      v10 = 0;
      v11 = 16;
      pThis_101 = this + 257;
      do
      {
        *(uint32_t *)(v11 + *(this + 28)) = 0;
        *pThis_101 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 116))(this, v10);
        v11 += 4;
        ++v10;
        ++pThis_101;
      }
      while ( v11 < 28 );
      fld_e254 = *(this + 254);
      v13 = 0;
      if ( fld_e254 != 0 )
      {
        *(this + 246) = 0;
        *(this + 247) = 0;
        *(this + 248) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e254 + 192))(fld_e254) / 2;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 8));
      if ( *(this + 245) == 2 )
        sub_617880(*(uint32_t *)(*(this + 36) + 28));
      if ( sub_42FCB0(228) != 0 )
        v13 = sub_431860((char)"Character/Mage/Effect/Animation/Chaser/StartAttack.ani", 1);
      v14 = (char *)sub_44B6C0(284);
      v15 = v14;
      if ( v14 != nullptr )
      {
        sub_44E0D0(v14, v13, 1);
        *(uint32_t *)v15 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v15 = nullptr;
      }
      sub_45FE80(*(this + 29), (int)v15, 2, 0, (int)v15, (int)this, 0);
      v16 = *(uint32_t *)v15;
      v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v18 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v17);
      v19 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v18);
      (*(void (/*thiscall*/ **)(char *, int))(v16 + 112))(v15, v19);
      if ( *(this + 254) != 0 )
      {
        if ( sub_42FCB0(228) != 0 )
          v20 = sub_431860((char)"Character/Mage/Effect/Animation/Chaser/Target.ani", 1);
        else
          v20 = 0;
        v21 = (char *)sub_44B6C0(284);
        v22 = v21;
        if ( v21 != nullptr )
        {
          sub_44E0D0(v21, v20, 1);
          *(uint32_t *)v22 = &CNRDPooledObject::`vftable';
          pObj = (int)v22;
        }
        else
        {
          pObj = 0;
        }
        sub_45FE80(*(this + 29), (int)v22, 2, 0, pObj, *(this + 254), 0);
        fld_e248 = *(this + 248) + (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 254) + 116))(*(this + 254), 2);
        fld_e2542 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 254) + 116))(*(this + 254), 1);
        fld_e2543 = *(this + 254);
        fld_e247 = *(this + 247) + fld_e2542;
        v40 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e2543 + 116))(fld_e2543, 0);
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2543 + 152))(fld_e2543) != 0 )
          fld_e246 = *(this + 246) + v40;
        else
          fld_e246 = v40 - *(this + 246);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 112))(pObj, fld_e246, fld_e247 + 1);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 60))(pObj, *(this + 254));
        sub_4A06D0(fld_e248);
      }
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 356))(this, *(this + 254));
      v27 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
      v28 = __RTDynamicCast(v27, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
      if ( v28 != nullptr )
        sub_5DC290(v28);
      (*(void (/*thiscall*/ **)(uint32_t *, char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        off_795C40[*(this + 245)],
        -1,
        0,
        0);
      break;
    case 4:
      v29 = *(uint32_t **)(pArg3 + 4);
      *(this + 261) = *v29 + sub_699000((int)(this + 9));
      for ( i = 16; i < 28; i += 4 )
        *(uint32_t *)(i + *(this + 28)) = 0;
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
      *(this + 174) = 1000;
      v31 = *(uint32_t *)(pArg3 + 4);
      if ( v31 != 0 && (unsigned int)((*(uint32_t *)(pArg3 + 8) - v31) >> 2) >= 3 )
      {
        v32 = (uint32_t *)sub_45EBE0(*(uint32_t *)(v31 + 4), *(uint32_t *)(v31 + 8));
        v33 = __RTDynamicCast(v32, 0, &CNRDObject `RTTI Type Descriptor', &IRDCollisionObject `RTTI Type Descriptor', 0);
        if ( v33 != nullptr )
          (*(void (/*thiscall*/ **)(uint32_t *, uint8_t *))(*this + 356))(this, v33);
      }
      break;
    case 5:
      for ( j = 16; j < 28; j += 4 )
      {
        fld_e28 = (uint8_t *)*(this + 28);
        if ( *(uint32_t *)fld_e28 != 0
          && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)fld_e28 + 308))(*(uint32_t *)fld_e28) != 0
          && *(float *)&fld_e28[j] != 0.0 )
        {
          *(uint32_t *)&fld_e28[j] = 0;
          fld_e28[196] = 1;
        }
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
      if ( *(this + 245) == 2 )
      {
        fld_e36 = (uint32_t *)(*(this + 36) + 24);
LABEL_51:
        sub_617880(*fld_e36);
      }
      break;
    default:
      break;
  }
  sub_4926A0(*(this + 30));
  result = (uint32_t *)*(this + 32);
  v37 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)sub_4926A0(v37[3]);
      v37 = (uint32_t *)*v37;
    }
    while ( v37 != (uint32_t *)*(this + 32) );
  }
  return result;
}


// ------------------------------------------------------------
// 0x618920 sub_618920
// ------------------------------------------------------------
int /*thiscall*/ sub_618920(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x618930 sub_618930
// ------------------------------------------------------------
int /*thiscall*/ sub_618930(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e244)(uint32_t, int); // ecx
  int result; // eax

  fld_e244 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 244);
  if ( fld_e244 != nullptr )
    result = (**fld_e244)(fld_e244, 1);
  *(this + 244) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x618950 CNMagicMissile__vmt2BC
// ------------------------------------------------------------
// CNMagicMissile 命中结算槽（vmt2BC）：sub_47E720/47EFD0 + sub_4049C0 —— 魔法飞弹（MAGIC_MISSILE TAG 见 0x618B60 区）结算。
int /*thiscall*/ CNMagicMissile__vmt2BC(int *this, uint16_t *uArg2, size_t Size)
{
  int v4; // eax
  int fld_e176; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  uint64_t v9; // rax
  float v11; // [esp+0h] [ebp-24h]
  float v12; // [esp+0h] [ebp-24h]
  float v13; // [esp+4h] [ebp-20h]
  float v14; // [esp+4h] [ebp-20h]
  int v15; // [esp+1Ch] [ebp-8h]
  int v16; // [esp+20h] [ebp-4h]
  int v17; // [esp+20h] [ebp-4h]
  uint16_t v18; // [esp+2Ch] [ebp+8h]
  size_t Sizea; // [esp+30h] [ebp+Ch]
  size_t Sizeb; // [esp+30h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)uArg2, Size);
  v18 = *uArg2;
  v4 = sub_47E720(3, 0xBu);
  fld_e176 = *(this + 176);
  v6 = (char *)v4;
  Sizea = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v16 = sub_47EFD0(v6, 0.0, fld_e176, v7, v7, 11);
  v13 = (float)sub_47EFD0(v6, COERCE_FLOAT(1), fld_e176, Sizea, Sizea, 11);
  v11 = (float)v16;
  v15 = (uint64_t)sub_4049C0(v11, v13, v18, 1000) - 100;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  Sizeb = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v17 = sub_47EFD0(v6, COERCE_FLOAT(4), fld_e176, v8, v8, 0);
  v14 = (float)sub_47EFD0(v6, COERCE_FLOAT(5), fld_e176, Sizeb, Sizeb, 0);
  v12 = (float)v17;
  v9 = (uint64_t)sub_4049C0(v12, v14, v18, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 183) += v15;
  HIDWORD(v9) = *this;
  *((float *)this + 181) = (double)(100 * (int)v9 / (v15 + 100)) + *((float *)this + 181);
  return (*(int (/*thiscall*/ **)(int *, int *))(HIDWORD(v9) + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x618A90 CNMagicMissile__vmt14C
// ------------------------------------------------------------
// CNMagicMissile 主循环槽（vmt14C）：sub_4600B0 —— 飞弹飞行演出；粒子见 0x618B60 区
// 「PassiveObject/Character/Mage/Particle/MagicMissileParticle.ptl」。
void /*thiscall*/ CNMagicMissile__vmt14C(uint32_t *this)
{
  int fld_e244; // edi
  int fld_e28; // ebx
  int fld_e2442; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  void *fld_e29; // ecx
  uint8_t v9[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v11; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) == 0 )
  {
    fld_e244 = *(this + 244);
    fld_e28 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 28) + 104) + 16))(*(uint32_t *)(*(this + 28) + 104));
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e244 + 28))(fld_e244) + 72) = *(uint32_t *)(fld_e28 + 72);
    *((uint8_t *)this + 972) = 1;
  }
  fld_e2442 = *(uint32_t *)*(this + 244);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v5);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v6);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2442 + 40))(*(this + 244), v7);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 244) + 92))(*(this + 244), v9);
  fld_e29 = (void *)*(this + 29);
  v11 = 0;
  sub_4600B0(fld_e29, 2, 0, (int)v9);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x618B60 sub_618B60
// ------------------------------------------------------------
int /*thiscall*/ sub_618B60(uint32_t *this)
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax

  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    v3 = sub_428F30(pMem, (int)"PassiveObject/Character/Mage/Particle/MagicMissileParticle.ptl", (int)this);
  else
    v3 = nullptr;
  *(this + 244) = v3;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v3 + 112))(v3, this);
  return sub_4015C0("MAGIC_MISSILE", 0xDu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x618BE0 sub_618BE0
// ------------------------------------------------------------
int /*thiscall*/ sub_618BE0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 1000;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint8_t *)(this + 996) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x618C20 sub_618C20
// ------------------------------------------------------------
// 魔法飞弹辅助：sub_4E4A50（动作包）+ dword_78FE24/78FE28/78FE2C（攻击上下文邻块）——
// 【推断：飞弹伤害三参数（攻击/防御/修正）的装配】。
char /*thiscall*/ sub_618C20(int *this)
{
  char result; // al
  int *pThis; // edi
  int fld_e244; // ebx
  int v5; // eax
  int v6; // [esp-20h] [ebp-24h]
  int v7; // [esp-1Ch] [ebp-20h]
  int v8; // [esp-18h] [ebp-1Ch]
  int dword_78FE2C2; // [esp-10h] [ebp-14h]
  int dword_78FE282; // [esp-Ch] [ebp-10h]

  result = *((uint8_t *)this + 996);
  if ( result == 0 )
  {
    dword_78FE2C = 0;
    *(uint16_t *)dword_78FE28 = (uint64_t)((double)*(this + 246) * 0.060000002);
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    *(uint16_t *)(dword_78FE28 + dword_78FE2C) = *((uint16_t *)this + 490);
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    pThis = this;
    fld_e244 = 100 * *(this + 244) / (*(this + 245) + 100);
    if ( *(this + 173) != 0 )
      pThis = (int *)*(this + 173);
    dword_78FE282 = dword_78FE28;
    dword_78FE2C2 = dword_78FE2C;
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    result = sub_4E4A50(pThis, 23016, fld_e244, v5, v6, v7, v8, 0, dword_78FE2C2, dword_78FE282);
    *((uint8_t *)this + 996) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x618D30 CNLaunchJOL__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNLaunchJOL__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int v4; // eax
  int v7; // [esp+Ch] [ebp-4h] BYREF

  v4 = *pArg2;
  v7 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v4 + 648))(pArg2, &v7, this);
  if ( pszArg4 == 0 && v7 > 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg2 + 308))(pArg2) != 0 )
    sub_618C20(this);
  return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x618D90 CNLaunchJOL__vmt214
// ------------------------------------------------------------
char /*thiscall*/ CNLaunchJOL__vmt214(int *this, int nArg2, int nArg3, int nArg4)
{
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    sub_618C20(this);
  return CNRDPassiveObject__vmt214(this, nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x618DD0 CNLaunchJOL__vmt10
// ------------------------------------------------------------
void /*thiscall*/ CNLaunchJOL__vmt10(int this)
{
  uint32_t *fld_80; // eax
  uint32_t *v3; // esi

  CNRDPassiveObject__vmt10((uint8_t *)this);
  if ( *(float *)(this + 992) != 0.0 )
  {
    sub_4938F0(*(uint32_t *)(this + 120));
    sub_492080(*(float *)(this + 992));
    fld_80 = *(uint32_t **)(this + 128);
    v3 = (uint32_t *)*fld_80;
    if ( (uint32_t *)*fld_80 != fld_80 )
    {
      do
      {
        sub_4938F0(v3[3]);
        sub_492080(*(float *)(this + 992));
        v3 = (uint32_t *)*v3;
      }
      while ( v3 != *(uint32_t **)(this + 128) );
    }
  }
}



// ------------------------------------------------------------
// 0x618E40 CNLaunchJOL__vmt14C
// ------------------------------------------------------------
// CNLaunchJOL 主循环槽（vmt14C，114 行）：字符串证据「Character/Mage/Particle/LaunchJOL.ptl」
// （JOL = Jack-O-Lantern 南瓜灯【推断】）+ dword_8F84E4 —— sub_4A0650/sub_4B2580 ——
// 南瓜灯抛射体的飞行编排；音效 LANTURN_FIRE 见 0x6193B0 区。
signed int /*thiscall*/ sub_618E40(int *this)  // 【CNLaunchJOL__vmt14C】
{
  int v2; // edi
  int i; // ebx
  int v4; // edx
  int pObj; // eax
  float *fld_e36; // ebx
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  signed int result; // eax
  int fld_e28; // edi
  int fld_e282; // ecx
  int v17; // [esp-30h] [ebp-44h]
  int v18; // [esp-2Ch] [ebp-40h]
  int v19; // [esp-28h] [ebp-3Ch]
  int v20; // [esp-24h] [ebp-38h]
  int v21; // [esp-20h] [ebp-34h]
  int fld_e247; // [esp-18h] [ebp-2Ch]
  int v23; // [esp-10h] [ebp-24h]
  int v24; // [esp-Ch] [ebp-20h]
  int v25; // [esp-8h] [ebp-1Ch]
  int v26; // [esp-4h] [ebp-18h]
  int fld_e283; // [esp+Ch] [ebp-8h] BYREF
  int v28; // [esp+10h] [ebp-4h] BYREF

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && *(uint32_t *)(*(this + 28) + 104) == 0
    && *(uint8_t *)(*(this + 30) + 170) != 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
           dword_8F84E4,
           "Character/Mage/Particle/LaunchJOL.ptl");
    *(uint8_t *)(v2 + 84) = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0;
    for ( i = 0; i < 3; ++i )
      *(uint32_t *)(v2 + 4 * i) = sub_4A0650(*(this + 28), i);
    *(uint32_t *)(v2 + 85) = *(this + 243);
    *(uint32_t *)(v2 + 76) = *(this + 247);
    v4 = *this;
    v28 = 0;
    fld_e283 = 0;
    if ( (*(int (/*thiscall*/ **)(int *))(v4 + 684))(this) != 0 )
    {
      pObj = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )
      {
        fld_e36 = *(float **)(sub_4924C0(*(int **)*(this + 36), 0) + 60);
        v26 = (uint64_t)(fld_e36[5] * 1.5);
        v25 = (uint64_t)(fld_e36[4] * 1.5);
        v24 = (uint64_t)(fld_e36[3] * 1.5);
        v23 = *(uint32_t *)(v2 + 85) * *(uint32_t *)(v2 + 15) / 1000;
        fld_e247 = *(this + 247) != 0 ? 0xF : 0;
        v21 = *(uint32_t *)(v2 + 76);
        v20 = *(uint32_t *)(v2 + 72);
        v19 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        v18 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
        v17 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
        v7 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
        sub_4B2580(&v28, &fld_e283, v7, v17, v18, v19, v20, v21, 15, fld_e247, -1, v23, v24, v25, v26);
      }
    }
    v8 = *(uint32_t *)(v2 + 76);
    *(uint32_t *)(v2 + 72) += v28;
    *(uint32_t *)(v2 + 76) = fld_e283 + v8;
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
    v9 = *(uint32_t *)dword_8F8520;
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
    (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
    v11 = *(uint32_t *)dword_8F8520;
    v12 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
    (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v2, 98);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    v13 = *(uint32_t *)(v2 + 76);
    *(uint32_t *)(v2 + 72) -= v28;
    *(uint32_t *)(v2 + 76) = v13 - fld_e283;
  }
  result = *(uint32_t *)(*(this + 28) + 104);
  if ( result != 0 )
  {
    result = *(this + 30);
    if ( result == *(this + 34) )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -1,
        *(uint32_t *)(*(this + 36) + 8),
        0,
        0,
        0,
        0);
      fld_e28 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 28) + 104) + 16))(*(uint32_t *)(*(this + 28) + 104))
                      + 76);
      fld_e282 = dword_7930D4[0]
          * *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 28) + 104) + 16))(*(uint32_t *)(*(this + 28) + 104))
                      + 72)
          / 100;
      result = abs32(fld_e28);
      if ( result <= (int)abs32(fld_e282) )
        fld_e283 = -fld_e282;
      else
        fld_e283 = fld_e28;
      *((float *)this + 248) = (double)fld_e283 * 0.0174532925199433;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x619110 CNLaunchJOL__vmt2BC
// ------------------------------------------------------------
// CNLaunchJOL 命中结算槽（vmt2BC，90 行）：sub_47E720/47EF20/47EFD0 + sub_4922F0 +
// dword_78FE30/34 —— 南瓜灯落地爆炸的结算。
int /*thiscall*/ CNLaunchJOL__vmt2BC(int *this, uint16_t *uArg2, int Size)
{
  char *v4; // eax
  int fld_e176; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  uint64_t v10; // rax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int result; // eax
  int v16; // ecx
  float v17; // [esp+0h] [ebp-24h]
  float v18; // [esp+0h] [ebp-24h]
  float v19; // [esp+0h] [ebp-24h]
  float v20; // [esp+0h] [ebp-24h]
  float v21; // [esp+0h] [ebp-24h]
  float v22; // [esp+4h] [ebp-20h]
  float v23; // [esp+4h] [ebp-20h]
  float v24; // [esp+4h] [ebp-20h]
  float v25; // [esp+4h] [ebp-20h]
  float v26; // [esp+4h] [ebp-20h]
  int v27; // [esp+1Ch] [ebp-8h]
  int v28; // [esp+20h] [ebp-4h]
  uint16_t v29; // [esp+2Ch] [ebp+8h]
  float v30; // [esp+2Ch] [ebp+8h]
  int v31; // [esp+2Ch] [ebp+8h]
  int v32; // [esp+2Ch] [ebp+8h]
  int v33; // [esp+2Ch] [ebp+8h]
  int v34; // [esp+2Ch] [ebp+8h]

  CNRDPassiveObject__vmt2BC((int)uArg2, Size);
  dword_78FE34 = 0;
  dword_78FE30 = (int)uArg2;
  v29 = *uArg2;
  dword_78FE34 = 2;
  v4 = (char *)sub_47E720(3, 0xFu);
  fld_e176 = *(this + 176);
  v6 = v4;
  v28 = v29;
  v22 = (float)sub_47EF20(v4, 5u, fld_e176, -1, -1, 11);
  v17 = (float)sub_47EF20(v6, 4u, fld_e176, -1, -1, 11);
  v30 = sub_4049C0(v17, v22, v29, 1000) * 0.001;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  sub_4922F0(v30);
  sub_4922F0(v30);
  sub_4922F0(v30);
  sub_4922F0(v30);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v31 = sub_47EFD0(v6, COERCE_FLOAT(1), fld_e176, v7, v7, 11);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v9 = sub_47EFD0(v6, 0.0, fld_e176, v8, v8, 11);
  v23 = (float)v31;
  v18 = (float)v9;
  v10 = (uint64_t)sub_4049C0(v18, v23, v28, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(v10) = *this;
  *(this + 245) = v10 - 100;
  v11 = (*(int (/*thiscall*/ **)(int *))(HIDWORD(v10) + 388))(this);
  v32 = sub_47EFD0(v6, COERCE_FLOAT(9), fld_e176, v11, v11, 0);
  v12 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v13 = sub_47EFD0(v6, COERCE_FLOAT(8), fld_e176, v12, v12, 0);
  v24 = (float)v32;
  v19 = (float)v13;
  *(this + 244) = (uint64_t)sub_4049C0(v19, v24, v28, 1000);
  v33 = sub_47EF20(v6, 3u, fld_e176, -1, -1, 11);
  v14 = sub_47EF20(v6, 2u, fld_e176, -1, -1, 11);
  v25 = (float)v33;
  v20 = (float)v14;
  *(this + 243) = (uint64_t)sub_4049C0(v20, v25, v28, 1000);
  v34 = sub_47EF20(v6, 7u, fld_e176, -1, -1, 11);
  v27 = sub_47EF20(v6, 6u, fld_e176, -1, -1, 11);
  v26 = (float)v34;
  v21 = (float)v27;
  *(this + 246) = (uint64_t)sub_4049C0(v21, v26, v28, 1000);
  result = dword_78FE34;
  if ( dword_78FE34 >= Size )
  {
    *(this + 247) = 0;
  }
  else
  {
    v16 = *(uint32_t *)(dword_78FE34 + dword_78FE30);
    result = dword_78FE34 + 4;
    dword_78FE34 += 4;
    *(this + 247) = v16;
  }
  *((float *)this + 248) = (double)*(this + 247) * 0.017444445;
  return result;
}



// ------------------------------------------------------------
// 0x6193B0 sub_6193B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6193B0(uint32_t *this)
{
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -2,
    *(uint32_t *)(*(this + 36) + 4),
    0,
    0,
    0,
    0);
  return sub_4015C0("LANTURN_FIRE", 0xCu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x6193F0 sub_6193F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6193F0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 1065353216;
  *(uint8_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x619410 sub_619410
// ------------------------------------------------------------
int /*stdcall*/ sub_619410(int nArg1, int nArg2)
{
  int64_t v2; // rax
  int v3; // edx

  v2 = (nArg1 % 360 + 360) % 360 - (nArg2 % 360 + 360) % 360;
  v3 = (int)((HIDWORD(v2) ^ v2) - HIDWORD(v2)) % 360;
  if ( v3 <= 180 )
    return v3;
  else
    return 360 - v3;
}



// ------------------------------------------------------------
// 0x619460 sub_619460
// ------------------------------------------------------------
// 冰霜魔偶头参数装载（137 行）：sub_423A20（UDP 广播）+ sub_4E4630 + sub_619410 + dword_796E50 ——
// 【推断：FrostHead 的弹跳/滚动参数】。
int /*usercall*/ sub_619460@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>)
{
  int result; // eax
  int pObj; // esi
  int v6; // eax
  int v7; // eax
  unsigned int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // esi
  int v14; // ecx
  int v15; // edx
  int pObj2; // esi
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // esi
  int v21; // eax
  int v22; // esi
  int v23; // eax
  int v25; // [esp+4h] [ebp-80h]
  int v26; // [esp+8h] [ebp-7Ch]
  unsigned int v27; // [esp+Ch] [ebp-78h]
  int v28; // [esp+10h] [ebp-74h]
  int v29; // [esp+14h] [ebp-70h]
  int v30; // [esp+18h] [ebp-6Ch]
  uint32_t v31[26]; // [esp+1Ch] [ebp-68h] BYREF

  v31[25] = dword_796E50;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    result = pArg1[29];
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 60))(pArg1);
      pObj = *(uint32_t *)(result + 104);
      if ( pObj != 0 )
      {
        sub_423A20(v31);
        qmemcpy(v31, (const void *)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 16))(pObj, nArg2, nArg3), 0x62u);
        v31[0] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 24))(pObj);
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj);
        *(uint32_t *)((char *)&v31[7] + 3) = pArg1[246];
        v31[1] = v6;
        v31[2] = 1;
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj);
        if ( *(uint32_t *)((char *)&v31[21] + 1) - v7 >= 0 )
        {
          v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj);
          *(uint32_t *)((char *)&v31[21] + 1) -= v9;
          v8 = 0;
        }
        else
        {
          v8 = 0;
          *(uint32_t *)((char *)&v31[21] + 1) = 0;
        }
        v10 = pArg1[29];
        v11 = *(uint32_t *)(v10 + 120);
        v12 = v10 + 116;
        if ( v11 != 0 )
          v28 = (*(uint32_t *)(v12 + 8) - v11) >> 2;
        else
          v28 = 0;
        v13 = v31[18];
        v30 = -1;
        v29 = 0;
        v26 = v31[18];
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1) == 0 )
          v26 = 180 - v13;
        v25 = 9 * *(uint32_t *)((char *)&v31[21] + 1) * *(uint32_t *)((char *)&v31[3] + 3) / 10;
        v27 = 0;
        if ( v28 > 0 )
        {
          do
          {
            v14 = pArg1[29];
            v15 = *(uint32_t *)(v14 + 120);
            if ( v15 != 0 && v8 < (*(uint32_t *)(v14 + 124) - v15) >> 2 )
            {
              pObj2 = *(uint32_t *)(v15 + 4 * v8);
              if ( pObj2 != 0
                && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0
                && (uint8_t)sub_4E4630(pObj2) != 0 )
              {
                v17 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(*pArg1 + 164))(
                                          pArg1,
                                          pObj2,
                                          0);
                if ( sub_619410(v17, v26) <= pArg1[243] / 2 )
                {
                  v18 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, pObj2, 0);
                  if ( (v30 == -1 || v18 < v29) && v18 < v25 )
                  {
                    v30 = v17;
                    v29 = v18;
                  }
                }
                v8 = v27;
              }
            }
            v27 = ++v8;
          }
          while ( (int)v8 < v28 );
          v19 = v30;
          if ( v30 != -1 )
          {
            if ( v30 <= 90 || v30 >= 270 )
            {
              LOBYTE(v31[21]) = 0;
            }
            else
            {
              LOBYTE(v31[21]) = 1;
              v19 = 180 - v30;
            }
            v31[18] = v19;
          }
        }
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
        v20 = *(uint32_t *)dword_8F8520;
        v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 48))(pArg1);
        (*(void (/*thiscall*/ **)(int, int))(v20 + 36))(dword_8F8520, v21);
        v22 = *(uint32_t *)dword_8F8520;
        v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);
        (*(void (/*thiscall*/ **)(int, int))(v22 + 36))(dword_8F8520, v23);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v31, 98);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
        return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6196E0 CNLaunchFrostHead__vmt2BC
// ------------------------------------------------------------
// CNLaunchFrostHead 命中结算槽（vmt2BC，91 行）：sub_47E720/47E9D0/47EF20/47EFD0 + sub_4922F0 +
// sub_4049C0 —— 冰霜魔偶头的撞击结算。
int /*thiscall*/ CNLaunchFrostHead__vmt2BC(char *this, uint16_t *uArg2, size_t Size)
{
  int v4; // eax
  int pThis_B0; // ebx
  char *v6; // edi
  int pThis_184; // eax
  uint64_t v8; // rax
  int pThis_1842; // eax
  int v10; // ecx
  uint32_t *pThis_2EC; // eax
  int v12; // eax
  uint32_t *pThis_2EC2; // ecx
  int v14; // eax
  int v15; // edx
  float v17; // [esp+0h] [ebp-24h]
  float v18; // [esp+0h] [ebp-24h]
  float v19; // [esp+0h] [ebp-24h]
  float v20; // [esp+4h] [ebp-20h]
  float v21; // [esp+4h] [ebp-20h]
  float v22; // [esp+4h] [ebp-20h]
  int v23; // [esp+1Ch] [ebp-8h]
  int v24; // [esp+1Ch] [ebp-8h]
  int v25; // [esp+20h] [ebp-4h]
  uint16_t v26; // [esp+2Ch] [ebp+8h]
  int v27; // [esp+2Ch] [ebp+8h]
  size_t Sizea; // [esp+30h] [ebp+Ch]
  size_t Sizeb; // [esp+30h] [ebp+Ch]
  float Sizec; // [esp+30h] [ebp+Ch]
  size_t Sized; // [esp+30h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)uArg2, Size);
  v26 = *uArg2;
  v4 = sub_47E720(3, 0x10u);
  pThis_B0 = *((uint32_t *)this + 176);
  v6 = (char *)v4;
  Sizea = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
  pThis_184 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
  v23 = sub_47EFD0(v6, 0.0, pThis_B0, pThis_184, pThis_184, 11);
  v25 = sub_47EFD0(v6, COERCE_FLOAT(1), pThis_B0, Sizea, Sizea, 11);
  Sizeb = v26;
  v20 = (float)v25;
  v17 = (float)v23;
  v8 = (uint64_t)sub_4049C0(v17, v20, v26, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(v8) = *(uint32_t *)this;
  *((uint32_t *)this + 183) = v8 - 100;
  v27 = (*(int (/*thiscall*/ **)(char *))(HIDWORD(v8) + 388))(this);
  pThis_1842 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
  v24 = sub_47EFD0(v6, COERCE_FLOAT(10), pThis_B0, pThis_1842, pThis_1842, 0);
  v21 = (float)sub_47EFD0(v6, COERCE_FLOAT(11), pThis_B0, v27, v27, 0);
  v18 = (float)v24;
  *((float *)this + 181) = (double)((int)(100 * (uint64_t)sub_4049C0(v18, v21, Sizeb, 1000))
                                  / (*((uint32_t *)this + 183) + 100))
                         + *((float *)this + 181);
  *((uint32_t *)this + 243) = sub_47EF20(v6, 4u, pThis_B0, -1, -1, 11);
  v22 = (float)sub_47EF20(v6, 6u, pThis_B0, -1, -1, 11);
  v19 = (float)sub_47EF20(v6, 5u, pThis_B0, -1, -1, 11);
  Sizec = sub_4049C0(v19, v22, Sizeb, 1000) * 0.001;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *((float *)this + 244) = Sizec;
  sub_4922F0(Sizec);
  sub_4922F0(*((float *)this + 244));
  v10 = 0;
  pThis_2EC = this + 748;
  while ( *pThis_2EC != 17 )
  {
    ++v10;
    ++pThis_2EC;
    if ( v10 >= 3 )
      goto LABEL_6;
  }
  *((uint32_t *)this + v10 + 187) = 0;
  *((uint32_t *)this + v10 + 190) = 1120403456;
  *((uint32_t *)this + v10 + 193) = sub_47EF20(v6, 7u, pThis_B0, -1, -1, 11);
LABEL_6:
  v12 = 0;
  pThis_2EC2 = this + 748;
  while ( *pThis_2EC2 != 17 )
  {
    ++v12;
    ++pThis_2EC2;
    if ( v12 >= 3 )
      goto LABEL_11;
  }
  Sized = v12;
  *((uint32_t *)this + v12 + 187) = 1;
  *((float *)this + v12 + 190) = (double)sub_47EF20(v6, 8u, pThis_B0, -1, -1, 11) * 0.1;
  *((uint32_t *)this + Sized + 193) = sub_47EF20(v6, 9u, pThis_B0, -1, -1, 11);
LABEL_11:
  v14 = sub_47E9D0(v6, 4u);
  v15 = *(uint32_t *)this;
  *((uint32_t *)this + 246) = v14;
  return (*(int (/*thiscall*/ **)(char *, char *))(v15 + 344))(this, this + 724);
}



// ------------------------------------------------------------
// 0x619980 CNLaunchFrostHead__vmt1F4
// ------------------------------------------------------------
// CNLaunchFrostHead 命中表现槽（vmt1F4）：字符串证据「Animation/LaunchFrostHeadHit.ani」。
// sub_44B6C0 + sub_45FE80 —— 撞击碎裂演出。
int /*thiscall*/ CNLaunchFrostHead__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int v5; // eax
  int v6; // ebx
  const char *pThis_5B; // ecx
  char *v8; // eax
  char *v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // eax

  v5 = sub_42FCB0(228);
  v6 = 0;
  if ( v5 != 0 )
  {
    if ( (unsigned int)*(this + 96) < 0x10 )
      pThis_5B = (const char *)(this + 91);
    else
      pThis_5B = (const char *)*(this + 91);
    v6 = sub_431920(v5, pThis_5B, "Animation/LaunchFrostHeadHit.ani", 1);
  }
  sub_4922F0(*((float *)this + 244));
  v8 = (char *)sub_44B6C0(284);
  v9 = v8;
  if ( v8 != nullptr )
  {
    sub_44E0D0(v8, v6, 1);
    *(uint32_t *)v9 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v9 = nullptr;
  }
  sub_45FE80(*(this + 29), (int)v9, 2, 0, (int)v9, 0, 0);
  v10 = *(uint32_t *)v9;
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 124))(pArg2, v11);
  v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v12 + 1);
  (*(void (/*thiscall*/ **)(char *, int))(v10 + 112))(v9, v13);
  v14 = *(uint32_t *)v9;
  v15 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(char *, int))(v14 + 148))(v9, v15);
  *((uint8_t *)this + 980) = 1;
  return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x619AB0 CNLaunchFrostHead__vmt14C
// ------------------------------------------------------------
// CNLaunchFrostHead 主循环槽（vmt14C）：字符串证据「Animation/LaunchFrostHeadJumpEffect.ani」+
// 「FROSTHEAD」（音效 TAG）。sub_4926A0（定时器）+ sub_619460 —— 魔偶头弹跳推进。
int /*usercall*/ CNLaunchFrostHead__vmt14C@<eax>(char *pszArg1@<ecx>, int nArg2@<edi>)
{
  int pObj; // ecx
  int v4; // ebx
  int result; // eax
  int v6; // eax
  const char *v7; // ecx
  char *v8; // eax
  char *v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // eax

  CNRDPassiveObject__vmt14C((int)pszArg1);
  pObj = *(uint32_t *)(*((uint32_t *)pszArg1 + 28) + 104);
  v4 = 0;
  if ( pObj != 0 )
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 84) != 0 )
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pszArg1 + 148))(pszArg1, 0);
    else
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)pszArg1 + 148))(pszArg1, 1);
  }
  if ( (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pszArg1 + 128))(pszArg1) <= 0 )
  {
    result = *((uint32_t *)pszArg1 + 30);
    if ( result == *((uint32_t *)pszArg1 + 34) )
    {
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pszArg1 + 196))(pszArg1, **((uint32_t **)pszArg1 + 36));
      sub_4926A0(*((uint32_t *)pszArg1 + 30));
      v6 = sub_42FCB0(228);
      if ( v6 != 0 )
      {
        if ( *((uint32_t *)pszArg1 + 96) < 0x10u )
          v7 = pszArg1 + 364;
        else
          v7 = *((const char **)pszArg1 + 91);
        v4 = sub_431920(v6, v7, "Animation/LaunchFrostHeadJumpEffect.ani", 1);
      }
      v8 = (char *)sub_44B6C0(284);
      v9 = v8;
      if ( v8 != nullptr )
      {
        sub_44E0D0(v8, v4, 1);
        *(uint32_t *)v9 = &vftbl_CNRDPooledObject;
      }
      else
      {
        v9 = nullptr;
      }
      sub_45FE80(*((uint32_t *)pszArg1 + 29), (int)v9, 2, 0, (int)v9, (int)pszArg1, 0);
      v10 = *(uint32_t *)v9;
      v11 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pszArg1 + 128))(pszArg1);
      v12 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)pszArg1 + 124))(pszArg1, v11);
      v13 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)pszArg1 + 120))(pszArg1, v12);
      (*(void (/*thiscall*/ **)(char *, int))(v10 + 112))(v9, v13);
      v14 = *(uint32_t *)v9;
      v15 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pszArg1 + 152))(pszArg1);
      return (*(int (/*thiscall*/ **)(char *, int))(v14 + 148))(v9, v15);
    }
    else if ( *(uint8_t *)(result + 170) != 0 )
    {
      return sub_619460(pszArg1, nArg2, (int)pszArg1);
    }
  }
  else
  {
    result = *((uint32_t *)pszArg1 + 34);
    if ( *((uint32_t *)pszArg1 + 30) != result )
    {
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pszArg1 + 196))(pszArg1, *((uint32_t *)pszArg1 + 34));
      sub_4926A0(*((uint32_t *)pszArg1 + 30));
      return (*(int (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pszArg1 + 212))(
               pszArg1,
               "FROSTHEAD",
               -1,
               0,
               0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x619C80 CNLaunchFrostHead__vmt12C
// ------------------------------------------------------------
// CNLaunchFrostHead 消亡联动槽（vmt12C）：字符串证据「Animation/LaunchFrostHeadDisappear.ani」——
// 魔偶头消失动画。
void /*thiscall*/ CNLaunchFrostHead__vmt12C(uint8_t *this, int nArg2)
{
  int v3; // eax
  int v4; // ebx
  const char *pThis_16C; // edx
  char *v6; // eax
  char *v7; // edi
  int v8; // ebx
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  int v12; // ebx
  int pThis_98; // eax

  if ( (uint8_t *)nArg2 == this && *(this + 980) == 0 )
  {
    v3 = sub_42FCB0(228);
    v4 = 0;
    if ( v3 != 0 )
    {
      if ( *((uint32_t *)this + 96) < 0x10u )
        pThis_16C = this + 364;
      else
        pThis_16C = *((const char **)this + 91);
      v4 = sub_431920(v3, pThis_16C, "Animation/LaunchFrostHeadDisappear.ani", 1);
    }
    sub_4922F0(*((float *)this + 244));
    v6 = (char *)sub_44B6C0(284);
    v7 = v6;
    if ( v6 != nullptr )
    {
      sub_44E0D0(v6, v4, 1);
      *(uint32_t *)v7 = &vftbl_CNRDPooledObject;
    }
    else
    {
      v7 = nullptr;
    }
    sub_45FE80(*((uint32_t *)this + 29), (int)v7, 2, 0, (int)v7, 0, 0);
    v8 = *(uint32_t *)v7;
    pThis_80 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
    pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, pThis_80);
    pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, pThis_7C);
    (*(void (/*thiscall*/ **)(char *, int))(v8 + 112))(v7, pThis_78);
    v12 = *(uint32_t *)v7;
    pThis_98 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this);
    (*(void (/*thiscall*/ **)(char *, int))(v12 + 148))(v7, pThis_98);
  }
  CNRDPassiveObject__vmt12C(this, nArg2);
}



// ------------------------------------------------------------
// 0x619DB0 sub_619DB0
// ------------------------------------------------------------
int /*thiscall*/ sub_619DB0(int this)
{
  *(uint32_t *)(this + 972) = 5;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 1065353216;
  *(uint8_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 1004) = 0;
  *(uint8_t *)(this + 1008) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x619E00 sub_619E00
// ------------------------------------------------------------
int /*thiscall*/ sub_619E00(uint32_t *this, int nArg2, int nArg3)
{
  int pObj; // eax
  int v5; // eax
  int v6; // edi
  bool v7; // zf
  int fld_e249; // eax
  int v9; // eax

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) != 0 )
  {
    pObj = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
  }
  else
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  }
  v6 = v5;
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0;
  fld_e249 = *(this + 249);
  if ( v7 )
    v9 = fld_e249 - nArg2;
  else
    v9 = nArg2 + fld_e249;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 112))(this, v9, v6, nArg3 + *(this + 251));
}



// ------------------------------------------------------------
// 0x619E70 CNLaunchBlackCat__vmt2BC
// ------------------------------------------------------------
// CNLaunchBlackCat 命中结算槽（vmt2BC）：sub_47E720/47EF20/47EFD0 + sub_4049C0 ——
// 黑猫（LaunchBlackCat，魔道学者黑猫【推断】）撞击结算。
int /*thiscall*/ CNLaunchBlackCat__vmt2BC(int *this, uint16_t *uArg2, size_t Size)
{
  int v4; // eax
  int fld_e176; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  uint64_t v9; // rax
  float v11; // [esp+0h] [ebp-24h]
  float v12; // [esp+0h] [ebp-24h]
  float v13; // [esp+0h] [ebp-24h]
  float v14; // [esp+0h] [ebp-24h]
  float v15; // [esp+4h] [ebp-20h]
  float v16; // [esp+4h] [ebp-20h]
  float v17; // [esp+4h] [ebp-20h]
  float v18; // [esp+4h] [ebp-20h]
  int v19; // [esp+1Ch] [ebp-8h]
  int v20; // [esp+1Ch] [ebp-8h]
  int v21; // [esp+1Ch] [ebp-8h]
  int v22; // [esp+20h] [ebp-4h]
  uint16_t v23; // [esp+2Ch] [ebp+8h]
  int v24; // [esp+2Ch] [ebp+8h]
  int v25; // [esp+2Ch] [ebp+8h]
  size_t Sizea; // [esp+30h] [ebp+Ch]
  size_t Sizeb; // [esp+30h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)uArg2, Size);
  v23 = *uArg2;
  v4 = sub_47E720(3, 0x12u);
  fld_e176 = *(this + 176);
  v6 = (char *)v4;
  Sizea = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v19 = sub_47EFD0(v6, 0.0, fld_e176, v7, v7, 11);
  v22 = sub_47EFD0(v6, COERCE_FLOAT(1), fld_e176, Sizea, Sizea, 11);
  Sizeb = v23;
  v15 = (float)v22;
  v11 = (float)v19;
  *(this + 183) += (uint64_t)sub_4049C0(v11, v15, v23, 1000) - 100;
  v24 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v20 = sub_47EFD0(v6, COERCE_FLOAT(6), fld_e176, v8, v8, 0);
  v16 = (float)sub_47EFD0(v6, COERCE_FLOAT(7), fld_e176, v24, v24, 0);
  v12 = (float)v20;
  *((float *)this + 181) = (double)((int)(100 * (uint64_t)sub_4049C0(v12, v16, Sizeb, 1000))
                                  / (*(this + 183) + 100))
                         + *((float *)this + 181);
  v17 = (float)sub_47EF20(v6, 3u, fld_e176, -1, -1, 11);
  v13 = (float)sub_47EF20(v6, 2u, fld_e176, -1, -1, 11);
  *((float *)this + 247) = sub_4049C0(v13, v17, Sizeb, 1000) * 0.001 + 1.0;
  v25 = sub_47EF20(v6, 5u, fld_e176, -1, -1, 11);
  v21 = sub_47EF20(v6, 4u, fld_e176, -1, -1, 11);
  v18 = (float)v25;
  v14 = (float)v21;
  v9 = (uint64_t)sub_4049C0(v14, v18, Sizeb, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(v9) = *this;
  *(this + 246) = v9 - 140;
  return (*(int (/*thiscall*/ **)(int *, int *))(HIDWORD(v9) + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x61A070 sub_61A070
// ------------------------------------------------------------
// 黑猫辅助：sub_493D00（研究 20 P38-2 速率写者直证）+ dword_73C5A4 ——
// 黑猫运动速率的动态改写【推断：猫跳节奏控制】。
int /*thiscall*/ sub_61A070(int *this, int nArg2)
{
  int result; // eax
  float pThis_F7; // [esp+20h] [ebp-10h]
  float pThis_F72; // [esp+20h] [ebp-10h]
  int fld_e246; // [esp+20h] [ebp-10h]
  int fld_e2462; // [esp+20h] [ebp-10h]
  int fld_e251; // [esp+24h] [ebp-Ch]

  result = *(this + 243);
  *(this + 243) = nArg2;
  if ( result != 5 )
  {
    result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8 * result + 4));
    *(this + 244) = *(this + 245);
  }
  if ( nArg2 != 5 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(8 * nArg2 + *(this + 36)));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      1,
      *(uint32_t *)(8 * nArg2 + *(this + 36) + 4),
      0,
      0,
      0,
      0);
    pThis_F7 = *((float *)this + 247) * 100.0;
    sub_493D00(*(uint32_t *)(8 * nArg2 + *(this + 36)), pThis_F7);
    pThis_F72 = *((float *)this + 247) * 100.0;
    sub_493D00(*(uint32_t *)(8 * nArg2 + *(this + 36) + 4), pThis_F72);
    result = dword_73C5A4[nArg2];
    if ( nArg2 == 1 || nArg2 == 3 )
      result = 2 * *(this + 246);
    *(this + 245) += result;
  }
  switch ( nArg2 )
  {
    case 1:
      result = sub_619E00(40, 0);
      break;
    case 2:
      fld_e251 = -*(this + 251);
      fld_e246 = *(this + 246) + 135;
      *(this + 81) = 0;
      result = sub_619E00(fld_e246, fld_e251);
      break;
    case 3:
      fld_e2462 = *(this + 246) + 40;
      *(this + 81) = 1;
      result = sub_619E00(fld_e2462, -10);
      break;
    case 4:
      result = sub_619E00(0, 0);
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x61A1F0 CNLaunchBlackCat__vmt14C
// ------------------------------------------------------------
// CNLaunchBlackCat 主循环槽（vmt14C，96 行）：sub_4A0650 + sub_619E00/61A070 + sub_699000 ——
// 黑猫往返跳跃的状态机。
char /*thiscall*/ CNLaunchBlackCat__vmt14C(int this)
{
  int v2; // edi
  int *pThis_3E4; // ebx
  int fld_3CC; // eax
  int fld_3CC2; // eax
  int fld_3D0; // ebx
  int fld_3DC; // edi
  int fld_3D4; // ebx
  uint64_t v9; // rax
  int fld_3D02; // ebx
  int fld_3DC2; // edi
  int fld_3D42; // ebx
  double v13; // st7
  int pThis_2AC; // eax
  int v15; // ebx
  int pObj; // edi
  int pThis_80; // eax
  int v18; // eax
  int pThis_78; // eax
  int fld_3CC3; // eax
  bool v21; // cc
  float fld_3D82; // [esp+0h] [ebp-24h]
  float fld_3D8; // [esp+4h] [ebp-20h]
  int v25; // [esp+1Ch] [ebp-8h]
  int v26; // [esp+1Ch] [ebp-8h]

  CNRDPassiveObject__vmt14C(this);
  if ( *(uint8_t *)(this + 992) == 0 )
  {
    *(uint8_t *)(this + 992) = 1;
    v2 = 0;
    pThis_3E4 = (int *)(this + 996);
    do
      *pThis_3E4++ = sub_4A0650(*(uint32_t *)(this + 112), v2++);
    while ( v2 < 3 );
  }
  if ( (int)(uint64_t)((double)sub_699000(this + 36) * *(float *)(this + 988)) >= *(uint32_t *)(this + 980) )  // 【clock_now(clk)】
  {
    fld_3CC = *(uint32_t *)(this + 972);
    if ( fld_3CC == 4 )
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    else
      sub_61A070((int *)this, fld_3CC + 1);
  }
  fld_3CC2 = *(uint32_t *)(this + 972);
  if ( fld_3CC2 == 1 )
  {
    fld_3D0 = *(uint32_t *)(this + 976);
    fld_3DC = (uint64_t)((double)sub_699000(this + 36) * *(float *)(this + 988)) - fld_3D0;  // 【clock_now(clk)】
    fld_3D4 = *(uint32_t *)(this + 980) - fld_3D0;
    fld_3D8 = (float)*(int *)(this + 984);
    v25 = (uint64_t)sub_4049C0(0.0, fld_3D8, fld_3DC, fld_3D4);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v9 = (uint64_t)sub_4049C0(0.0, -10.0, fld_3DC, fld_3D4);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    sub_619E00((uint32_t *)this, v25 + 40, v9);
  }
  else if ( fld_3CC2 == 3 )
  {
    fld_3D02 = *(uint32_t *)(this + 976);
    fld_3DC2 = (uint64_t)((double)sub_699000(this + 36) * *(float *)(this + 988)) - fld_3D02;  // 【clock_now(clk)】
    fld_3D42 = *(uint32_t *)(this + 980) - fld_3D02;
    fld_3D82 = (float)*(int *)(this + 984);
    v26 = (uint64_t)sub_4049C0(fld_3D82, 0.0, fld_3DC2, fld_3D42);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v13 = sub_4049C0(-10.0, 0.0, fld_3DC2, fld_3D42);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    sub_619E00((uint32_t *)this, v26 + 40, (uint64_t)v13);
  }
  else if ( fld_3CC2 != 2 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this) != 0 )
  {
    pThis_2AC = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this);
    v15 = *(uint32_t *)this;
    pObj = pThis_2AC;
    pThis_80 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
    v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 124))(pObj, pThis_80);
    pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v18);
    (*(void (/*thiscall*/ **)(int, int))(v15 + 112))(this, pThis_78);
  }
  LOBYTE(fld_3CC3) = *(uint8_t *)(this + 1008);
  if ( (uint8_t)fld_3CC3 == 0 )
  {
    fld_3CC3 = *(uint32_t *)(this + 972);
    v21 = fld_3CC3 <= 2;
    if ( fld_3CC3 == 2 )
    {
      if ( *(int *)(*(uint32_t *)(this + 120) + 148) >= 3 )
      {
LABEL_20:
        LOBYTE(fld_3CC3) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);
        *(uint8_t *)(this + 1008) = 1;
        return fld_3CC3;
      }
      v21 = true;
    }
    if ( !v21 )
      goto LABEL_20;
  }
  return fld_3CC3;
}



// ------------------------------------------------------------
// 0x61A400 sub_61A400
// ------------------------------------------------------------
// 黑猫辅助：字符串证据「LAUNCH_PLUTO」（音效 TAG —— 冥王星/普鲁托）+ sub_493D00（速率写者）——
// 黑猫发射播音与速率装配。
int /*thiscall*/ sub_61A400(uint32_t *this)
{
  int fld_e243; // eax
  float pThis_F7; // [esp+20h] [ebp-8h]
  float pThis_F72; // [esp+20h] [ebp-8h]

  fld_e243 = *(this + 243);
  *(this + 243) = 0;
  if ( fld_e243 != 5 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8 * fld_e243 + 4));
    *(this + 244) = *(this + 245);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    1,
    *(uint32_t *)(*(this + 36) + 4),
    0,
    0,
    0,
    0);
  pThis_F7 = *((float *)this + 247) * 100.0;
  sub_493D00(*(uint32_t *)*(this + 36), pThis_F7);
  pThis_F72 = *((float *)this + 247) * 100.0;
  sub_493D00(*(uint32_t *)(*(this + 36) + 4), pThis_F72);
  *(this + 245) += 80;
  *((uint8_t *)this + 701) = 0;
  *((uint8_t *)this + 700) = 0;
  return sub_4015C0("LAUNCH_PLUTO", 0xCu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x61A4E0 sub_61A4E0
// ------------------------------------------------------------
int /*thiscall*/ sub_61A4E0(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 1065353216;
  *(uint32_t *)(this + 980) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x61A500 sub_61A500
// ------------------------------------------------------------
int /*thiscall*/ sub_61A500(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e245)(uint32_t, int); // ecx
  int result; // eax

  fld_e245 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 245);
  if ( fld_e245 != nullptr )
    result = (**fld_e245)(fld_e245, 1);
  *(this + 245) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x61A520 sub_61A520
// ------------------------------------------------------------
int /*thiscall*/ sub_61A520(uint32_t *this)
{
  *(this + 243) = 1065353216;
  *(this + 244) = 0;
  *(this + 245) = 0;
  *(this + 246) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x61A540 sub_61A540
// ------------------------------------------------------------
int /*thiscall*/ sub_61A540(uint32_t *this)
{
  uint32_t *pThis_F4; // esi
  int i; // edi
  int result; // eax

  pThis_F4 = this + 244;
  for ( i = 3; i != 0; --i )
  {
    if ( *pThis_F4 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_F4)(*pThis_F4, 1);
    *pThis_F4++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x61A570 CNHalloweenBusterSub__vmt2BC
// ------------------------------------------------------------
// CNHalloweenBusterSub 命中结算槽（vmt2BC，74 行）：sub_47E720/47EF20/47EFD0 + sub_4049C0 ——
// 万圣破坏者子体的追踪判定。
int /*thiscall*/ CNHalloweenBusterSub__vmt2BC(int *this, uint16_t *uArg2, size_t Size)
{
  int v4; // eax
  int fld_e176; // ebx
  char *v6; // edi
  int v7; // eax
  uint64_t v8; // rax
  int v9; // eax
  uint64_t v10; // rax
  double v11; // st7
  int i; // edi
  int *pThis_F3; // ebx
  bool v14; // zf
  float v16; // [esp+0h] [ebp-24h]
  float v17; // [esp+0h] [ebp-24h]
  float v18; // [esp+0h] [ebp-24h]
  float v19; // [esp+4h] [ebp-20h]
  float v20; // [esp+4h] [ebp-20h]
  float v21; // [esp+4h] [ebp-20h]
  int v22; // [esp+1Ch] [ebp-8h]
  int v23; // [esp+1Ch] [ebp-8h]
  int v24; // [esp+1Ch] [ebp-8h]
  int v25; // [esp+20h] [ebp-4h]
  uint16_t v26; // [esp+2Ch] [ebp+8h]
  int v27; // [esp+2Ch] [ebp+8h]
  int v28; // [esp+2Ch] [ebp+8h]
  size_t Sizeb; // [esp+30h] [ebp+Ch]
  size_t Sizec; // [esp+30h] [ebp+Ch]
  uint32_t *Sizea; // [esp+30h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)uArg2, Size);
  v26 = *uArg2;
  v4 = sub_47E720(3, 0x1Bu);
  fld_e176 = *(this + 176);
  v6 = (char *)v4;
  Sizeb = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v22 = sub_47EFD0(v6, COERCE_FLOAT(2), fld_e176, v7, v7, 11);
  v25 = sub_47EFD0(v6, COERCE_FLOAT(3), fld_e176, Sizeb, Sizeb, 11);
  Sizec = v26;
  v19 = (float)v25;
  v16 = (float)v22;
  v8 = (uint64_t)sub_4049C0(v16, v19, v26, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(v8) = *this;
  *(this + 183) = v8 - 100;
  v27 = (*(int (/*thiscall*/ **)(int *))(HIDWORD(v8) + 388))(this);
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v23 = sub_47EFD0(v6, COERCE_FLOAT(10), fld_e176, v9, v9, 0);
  v20 = (float)sub_47EFD0(v6, COERCE_FLOAT(11), fld_e176, v27, v27, 0);
  v17 = (float)v23;
  *((float *)this + 181) = (double)((int)(100 * (uint64_t)sub_4049C0(v17, v20, Sizec, 1000))
                                  / (*(this + 183) + 100))
                         + *((float *)this + 181);
  v24 = (uint64_t)(double)sub_47EF20(v6, 7u, fld_e176, -1, -1, 11);
  v10 = (uint64_t)(double)sub_47EF20(v6, 6u, fld_e176, -1, -1, 11);
  v21 = (float)v24;
  v18 = (float)(int)v10;
  v11 = (double)(int)(uint64_t)sub_4049C0(v18, v21, Sizec, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  Sizea = this + 244;
  v28 = 3;
  *((float *)this + 243) = v11 * 0.001;
  do
  {
    for ( i = 12; i < 20; i += 4 )
    {
      pThis_F3 = (int *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Sizea + 36))(*Sizea) + i);
      *pThis_F3 = (uint64_t)((double)*pThis_F3 * *((float *)this + 243));
    }
    v14 = v28 == 1;
    ++Sizea;
    --v28;
  }
  while ( !v14 );
  return (*(int (/*thiscall*/ **)(int *, int *))(*this + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x61A780 CNHalloweenBuster__vmt2BC
// ------------------------------------------------------------
// CNHalloweenBuster 命中结算槽（vmt2BC）：sub_4922F0 + sub_4049C0 —— 万圣破坏者本体的撞击结算。
int /*thiscall*/ CNHalloweenBuster__vmt2BC(void *this, uint16_t *uArg2, size_t Size)
{
  int v4; // eax
  int pThis_B0; // ebx
  char *v6; // edi
  int pThis_184; // eax
  int pThis_1843; // eax
  float v10; // [esp+0h] [ebp-24h]
  float v11; // [esp+0h] [ebp-24h]
  float v12; // [esp+0h] [ebp-24h]
  float v13; // [esp+4h] [ebp-20h]
  float v14; // [esp+4h] [ebp-20h]
  float v15; // [esp+4h] [ebp-20h]
  int v16; // [esp+1Ch] [ebp-8h]
  int v17; // [esp+1Ch] [ebp-8h]
  int v18; // [esp+20h] [ebp-4h]
  uint16_t v19; // [esp+2Ch] [ebp+8h]
  int pThis_1842; // [esp+2Ch] [ebp+8h]
  size_t Sizea; // [esp+30h] [ebp+Ch]
  size_t Sizeb; // [esp+30h] [ebp+Ch]
  float Sizec; // [esp+30h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)uArg2, Size);
  v19 = *uArg2;
  v4 = sub_47E720(3, 0x1Bu);
  pThis_B0 = *((uint32_t *)this + 176);
  v6 = (char *)v4;
  Sizea = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
  pThis_184 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
  v16 = sub_47EFD0(v6, 0.0, pThis_B0, pThis_184, pThis_184, 11);
  v18 = sub_47EFD0(v6, COERCE_FLOAT(1), pThis_B0, Sizea, Sizea, 11);
  Sizeb = v19;
  v13 = (float)v18;
  v10 = (float)v16;
  *((uint32_t *)this + 183) += (uint64_t)sub_4049C0(v10, v13, v19, 1000) - 100;
  pThis_1842 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
  pThis_1843 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
  v17 = sub_47EFD0(v6, COERCE_FLOAT(8), pThis_B0, pThis_1843, pThis_1843, 0);
  v14 = (float)sub_47EFD0(v6, COERCE_FLOAT(9), pThis_B0, pThis_1842, pThis_1842, 0);
  v11 = (float)v17;
  *((float *)this + 181) = (double)((int)(100 * (uint64_t)sub_4049C0(v11, v14, Sizeb, 1000))
                                  / (*((uint32_t *)this + 183) + 100))
                         + *((float *)this + 181);
  v15 = (float)sub_47EF20(v6, 5u, pThis_B0, -1, -1, 11);
  v12 = (float)sub_47EF20(v6, 4u, pThis_B0, -1, -1, 11);
  Sizec = sub_4049C0(v12, v15, Sizeb, 1000) * 0.001;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *((float *)this + 244) = Sizec;
  sub_4922F0(Sizec);
  sub_4922F0(*((float *)this + 244));
  sub_4922F0(*((float *)this + 244));
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 344))(this, (int)this + 724);
}



// ------------------------------------------------------------
// 0x61A960 CNHalloweenBuster__vmt14C
// ------------------------------------------------------------
// CNHalloweenBuster 主循环槽（vmt14C）：sub_424120（震屏）+ sub_4922F0 —— 万圣破坏者（HalloweenBuster，
// 万圣节南瓜炮【推断】）的爆炸震屏。
int /*thiscall*/ CNHalloweenBuster__vmt14C(uint32_t **this)
{
  int fld_e245; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  uint32_t *Block2; // edi
  int result; // eax
  float v8; // edi
  int fld_e241; // eax
  float pThis_F4; // [esp-4h] [ebp-2Ch]
  uint8_t v11[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  uint32_t *v13; // [esp+14h] [ebp-14h]
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) > 30 )
  {
    fld_e245 = **(this + 245);
    v3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
    v4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v3);
    v5 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v4);
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e245 + 40))(*(this + 245), v5);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 245) + 92))(*(this + 245), v11);
    Block2 = Block;
    v15 = 0;
    if ( Block != v13 )
    {
      do
      {
        pThis_F4 = *((float *)this + 244);
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 200))(*Block2);
        sub_4922F0(pThis_F4);
        ++Block2;
      }
      while ( Block2 != v13 );
    }
    sub_4600B0(*(this + 29), 2, 0, (int)v11);
    v15 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v13 = nullptr;
    v14 = 0;
  }
  result = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
  if ( result <= 0 && *((uint8_t *)this + 972) == 0 )
  {
    sub_424120((uint32_t *)(*(this + 29))[33], 4, 400);
    if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
    {
      v8 = *(float *)this;
      fld_e241 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*this)[32])(
             this,
             4,
             0,
             *(this + 241),
             *(this + 242));
      (*(void (/*thiscall*/ **)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(LODWORD(v8) + 580))(
        this,
        23014,
        *(this + 176),
        0,
        0,
        0,
        0,
        -fld_e241);
    }
    result = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[78])(this, 0);
    *((uint8_t *)this + 972) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x61AAD0 CNHalloweenBusterSub__vmt14C
// ------------------------------------------------------------
// CNHalloweenBusterSub 主循环槽（vmt14C）：sub_4600B0 + sub_4922F0 —— 子体飞行演出。
char /*thiscall*/ CNHalloweenBusterSub__vmt14C(float *this)
{
  int **pThis_F4; // ebx
  int v3; // edi
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  uint32_t *Block2; // edi
  bool v8; // zf
  char result; // al
  float fld_e243; // [esp-4h] [ebp-30h]
  uint8_t v11[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  uint32_t *v13; // [esp+14h] [ebp-18h]
  int v14; // [esp+18h] [ebp-14h]
  int v15; // [esp+1Ch] [ebp-10h]
  int v16; // [esp+28h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  pThis_F4 = (int **)(this + 244);
  v15 = 3;
  do
  {
    v3 = **pThis_F4;
    pThis_80 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 128))(this);
    pThis_7C = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 124))(this, pThis_80);
    pThis_78 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 120))(this, pThis_7C);
    (*(void (/*thiscall*/ **)(int *, int))(v3 + 40))(*pThis_F4, pThis_78);
    (*(void (/*thiscall*/ **)(int *, uint8_t *))(**pThis_F4 + 92))(*pThis_F4, v11);
    Block2 = Block;
    v16 = 0;
    if ( Block != v13 )
    {
      do
      {
        fld_e243 = *(this + 243);
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 200))(*Block2);
        sub_4922F0(fld_e243);
        ++Block2;
      }
      while ( Block2 != v13 );
    }
    sub_4600B0(*((void **)this + 29), 2, 0, (int)v11);
    v16 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++pThis_F4;
    v8 = v15 == 1;
    Block = nullptr;
    v13 = nullptr;
    v14 = 0;
    --v15;
  }
  while ( !v8 );
  result = *(uint8_t *)(*((uint32_t *)this + 30) + 170);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x61ABD0 sub_61ABD0
// ------------------------------------------------------------
// 万圣流星粒子：字符串证据「PassiveObject/Common/Particle/ShootingStarFire.ptl」+「SSTAR_DROP」（音效 TAG）+
// sub_428F30 —— 万圣破坏者复用流星系粒子（资源复用直证）。
int /*thiscall*/ sub_61ABD0(uint32_t **this)
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax

  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -1,
    **(this + 36),
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    1,
    (*(this + 36))[1],
    0,
    0,
    0,
    0);
  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    v3 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/ShootingStarFire.ptl", (int)this);
  else
    v3 = nullptr;
  *(this + 245) = v3;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t **))(*v3 + 112))(v3, this);
  (*(void (/*thiscall*/ **)(uint32_t, int))(**(this + 245) + 12))(*(this + 245), 500);
  return sub_4015C0("SSTAR_DROP", 0xAu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x61ACA0 sub_61ACA0
// ------------------------------------------------------------
// 万圣流星爆粒子：字符串证据「ShootingStarExpSmoke.ptl | ShootingStarExp.ptl | ShootingStarExpEtc.ptl」+
// 「SSTAR_HIT」—— 与 0x60DFA0（ShootingStarExp）完全同款的粒子三件套复用。
int /*thiscall*/ sub_61ACA0(uint32_t *this)
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax
  uint32_t *pMem3; // eax
  uint32_t *v7; // eax

  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    v3 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/ShootingStarExpSmoke.ptl", (int)this);
  else
    v3 = nullptr;
  *(this + 244) = v3;
  pMem2 = operator new(0x12Cu);
  if ( pMem2 != nullptr )
    v5 = sub_428F30(pMem2, (int)"PassiveObject/Common/Particle/ShootingStarExp.ptl", (int)this);
  else
    v5 = nullptr;
  *(this + 245) = v5;
  pMem3 = operator new(0x12Cu);
  if ( pMem3 != nullptr )
    v7 = sub_428F30(pMem3, (int)"PassiveObject/Common/Particle/ShootingStarExpEtc.ptl", (int)this);
  else
    v7 = nullptr;
  *(this + 246) = v7;
  return sub_4015C0("SSTAR_HIT", 9u);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x61AD90 sub_61AD90
// ------------------------------------------------------------
int /*thiscall*/ sub_61AD90(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint8_t *)(this + 973) = 0;
  *(uint32_t *)(this + 976) = -1;
  *(uint8_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 1016) = 0;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1040) = 0;
  *(uint32_t *)(this + 1044) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x61ADE0 sub_61ADE0
// ------------------------------------------------------------
int /*thiscall*/ sub_61ADE0(uint32_t *this)
{
  uint32_t *pThis_104; // esi
  int i; // edi
  int result; // eax

  pThis_104 = this + 260;
  for ( i = 2; i != 0; --i )
  {
    if ( *pThis_104 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_104)(*pThis_104, 1);
    *pThis_104++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x61AE10 sub_61AE10
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_61AE10(uint8_t *this, const char *ArgList, const char *pArg3)
{
  *(uint32_t *)this = &vftbl_CNRDParticle;
  sub_423A20((int)(this + 4));
  *(this + 108) = 0;
  *((uint32_t *)this + 26) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 28) = 0;
  *(this + 116) = 1;
  *(this + 118) = 0;
  *(this + 117) = 0;
  *((uint32_t *)this + 32) = 0;
  *((uint32_t *)this + 31) = 0;
  *((uint32_t *)this + 30) = 0;
  sub_529CE0((int)this);
  sub_529D20(this, ArgList, pArg3);
  return this;
}



// ============================================================
// 【分区 11】怪物 PO 弹幕/陷阱大全（0x61AE90-0x620000）
// 凝固弹/标记球/蜘蛛毒网/僵尸眼/卡格弹/莲花腿章鱼陷阱（TRAP_OCTOPUS 三段）/
// 手里剑/食尸鬼头骨/蛛网/蝙蝠/邪眼/地雷 —— 怪物技能 PO 的名录制
// ============================================================
// ------------------------------------------------------------
// 0x61AE90 CNNapalmBomb__vmt2A8
// ------------------------------------------------------------
// CNNapalmBomb 碰撞响应槽（vmt2A8）：sub_47E720/47E9D0/47EF20/47EFD0 + sub_607260 ——
// 凝固汽油弹（NapalmBomb）的落点判定。
char /*thiscall*/ CNNapalmBomb__vmt2A8(int this, int nArg2)
{
  int v3; // eax
  char *v4; // eax
  int fld_2C0; // ebx
  char *v6; // edi
  int v7; // eax
  float v9; // [esp+8h] [ebp-4h]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, nArg2);
  LOBYTE(v3) = *(uint8_t *)(this + 973);
  if ( (uint8_t)v3 == 0 )
  {
    if ( nArg2 != 0 )
      *(uint32_t *)(this + 976) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 388))(nArg2);
    v4 = (char *)sub_47E720(2, 0x35u);
    fld_2C0 = *(uint32_t *)(this + 704);
    v6 = v4;
    v9 = (float)sub_47EF20(v4, 1u, fld_2C0, -1, -1, 11);
    *(float *)(this + 988) = v9 / (double)sub_47EF20(v6, 1u, 1, -1, -1, 11);
    *(uint32_t *)(this + 992) = sub_47EF20(v6, 2u, fld_2C0, -1, -1, 11) / 2;
    *(float *)(this + 724) = (float)sub_47EFD0(
                                      v6,
                                      COERCE_FLOAT(5),
                                      fld_2C0,
                                      *(uint32_t *)(this + 976),
                                      *(uint32_t *)(this + 976),
                                      0);
    v7 = sub_47E9D0(v6, 0);
    sub_607260((uint32_t *)(this + 996), v7, -1, 1, 0);
    *(float *)(this + 1020) = (double)sub_47EF20(v6, 3u, fld_2C0, -1, -1, 11) * 0.1;
    v3 = sub_47EF20(v6, 4u, fld_2C0, -1, -1, 11);
    *(float *)(this + 1024) = (double)v3 * 0.1;
    *(uint8_t *)(this + 973) = 1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x61AFC0 CNNapalmBomb__vmt10
// ------------------------------------------------------------
// CNNapalmBomb 初始化（vmt10）：sub_4049C0 lerp + sub_42B420 + sub_491F80/4938F0 + sub_699000 ——
// 凝固弹的燃烧起值插值。
int /*thiscall*/ CNNapalmBomb__vmt10(int this)
{
  bool fld_3F8; // cc
  int pThis_24; // ecx
  double v4; // st7
  int pThis_242; // ecx
  uint64_t v6; // rax
  int v7; // eax
  int i; // esi
  int result; // eax
  int fld_3F82; // [esp-8h] [ebp-18h]
  int fld_3D8; // [esp-8h] [ebp-18h]
  uint32_t v12[2]; // [esp+8h] [ebp-8h]

  CNRDPassiveObject__vmt10((uint8_t *)this);
  v12[0] = 255;
  fld_3F8 = sub_699000(this + 36) < *(uint32_t *)(this + 1016) - 1000;  // 【clock_now(clk)】
  pThis_24 = this + 36;
  if ( fld_3F8 )
  {
    fld_3F8 = sub_699000(pThis_24) <= *(uint32_t *)(this + 984) + 1000;  // 【clock_now(clk)】
    pThis_242 = this + 36;
    if ( !fld_3F8 )
    {
      v7 = sub_699000(pThis_242);  // 【clock_now(clk)】
      LODWORD(v6) = sub_42B420(255, 128, -1000 - *(uint32_t *)(this + 984) + v7, 500);
      goto LABEL_7;
    }
    fld_3D8 = sub_699000(pThis_242) - *(uint32_t *)(this + 984);  // 【clock_now(clk)】
    v4 = sub_4049C0(0.0, 255.0, fld_3D8, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  }
  else
  {
    fld_3F82 = 1000 - *(uint32_t *)(this + 1016) + sub_699000(pThis_24);  // 【clock_now(clk)】
    v4 = sub_4049C0(255.0, 0.0, fld_3F82, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  }
  v6 = (uint64_t)v4;
  v12[0] = (uint64_t)v4;
LABEL_7:
  v12[1] = v6;
  for ( i = 0; i < 2; ++i )
  {
    sub_4938F0(*(uint32_t *)(*(uint32_t *)(this + 144) + i * 4));
    result = sub_491F80(-1, -1, -1, v12[i], 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61B0D0 sub_61B0D0
// ------------------------------------------------------------
// 凝固弹辅助（63 行）：sub_41C5E0 + sub_4E5F70（硬直率掷）+ sub_6072C0 ——【推断：燃烧 DOT 的结算】。
char /*usercall*/ sub_61B0D0@<al>(int pArg1@<ecx>, int nArg2@<ebx>)
{
  uint32_t *v3; // eax
  int v4; // eax
  uint32_t *v5; // ecx
  int pObj; // esi
  int v7; // eax
  int v8; // eax
  int v9; // edx
  float v11; // [esp+4h] [ebp-20h] BYREF
  float v12; // [esp+8h] [ebp-1Ch]
  int v13; // [esp+Ch] [ebp-18h]
  int v14; // [esp+10h] [ebp-14h]
  int v15; // [esp+14h] [ebp-10h]
  int v16; // [esp+18h] [ebp-Ch]
  int v17; // [esp+1Ch] [ebp-8h]
  uint32_t *v18; // [esp+20h] [ebp-4h] BYREF

  LOBYTE(v3) = *(uint8_t *)(pArg1 + 980);
  if ( (uint8_t)v3 != 0 )
  {
    LOBYTE(v3) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1);
    if ( (uint8_t)v3 != 0 )
    {
      v4 = sub_699000(pArg1 + 36);  // 【clock_now(clk)】
      LOBYTE(v3) = sub_6072C0((uint8_t *)(pArg1 + 996), v4);
      if ( (uint8_t)v3 != 0 )
      {
        v5 = *(uint32_t **)(pArg1 + 1032);
        v3 = (uint32_t *)*v5;
        v18 = (uint32_t *)*v5;
        if ( v18 != v5 )
        {
          do
          {
            pObj = v3[3];
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 624))(pObj) != 0 )
            {
              v7 = *(uint32_t *)pObj;
              v11 = 0.0;
              v12 = 0.0;
              v13 = 0;
              v14 = 0;
              v15 = 0;
              v16 = 0;
              v8 = (*(int (/*thiscall*/ **)(int))(v7 + 120))(pObj);
              v9 = *(uint32_t *)pObj;
              v17 = v8;
              v11 = (float)v8;
              v17 = (*(int (/*thiscall*/ **)(int))(v9 + 124))(pObj);
              v12 = (float)v17;
              v13 = 0;
              sub_4E5F70(nArg2, pArg1, pObj, &v11, 1, 1);
            }
            sub_41C5E0(&v18);
            v3 = v18;
          }
          while ( v18 != *(uint32_t **)(pArg1 + 1032) );
        }
      }
    }
  }
  return (char)v3;
}



// ------------------------------------------------------------
// 0x61B1C0 CNNapalmBomb__vmt12C
// ------------------------------------------------------------
// CNNapalmBomb 消亡联动槽（vmt12C）：sub_41C5E0 + sub_4BE520 + sub_4C20A0 ——
// 凝固弹熄灭/转燃烧区域的状态交接【推断】。
int /*thiscall*/ CNNapalmBomb__vmt12C(int **this, int nArg2)
{
  int **v2; // edi
  int *fld_e258; // ecx
  int nArg22; // eax
  int result; // eax
  int v7; // ebx
  int v8; // [esp+8h] [ebp-4h] BYREF

  v2 = (int **)nArg2;
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( v2 == this )
  {
    fld_e258 = *(this + 258);
    nArg22 = *fld_e258;
    nArg2 = *fld_e258;
    if ( (int *)nArg2 != fld_e258 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(nArg22 + 16) + 76))(*(uint32_t *)(nArg22 + 16), 0);
        sub_41C5E0(&nArg2);
        nArg22 = nArg2;
      }
      while ( (int *)nArg2 != *(this + 258) );
    }
    return ((int (/*thiscall*/ *)(int **, int))(*this)[54])(this, 10000);
  }
  else
  {
    result = sub_4BE520(&v8, &nArg2);
    v7 = v8;
    if ( (int *)v8 != *(this + 258) )
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v8 + 16) + 76))(*(uint32_t *)(v8 + 16), 0);
      return sub_4C20A0(&nArg2, v7);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61B260 sub_61B260
// ------------------------------------------------------------
// 燃烧区域调度（110 行）：sub_4B3DF0/4BE520/4C20A0 + sub_4E4630 + sub_5FA510 ——
// 地面火海的持续燃烧与蔓延编排【推断】。
char /*thiscall*/ sub_61B260(uint8_t *this)
{
  int v2; // eax
  int pThis_1D; // eax
  int v4; // ecx
  unsigned int v5; // esi
  int pThis_1D2; // ecx
  int v7; // edx
  uint32_t *v8; // eax
  int **v9; // esi
  uint32_t *pMem; // eax
  void **v11; // esi
  void (/*thiscall*/ **v12)(void **, int, int, uint32_t); // edx
  int v13; // edx
  int v14; // eax
  int **v15; // ebx
  int **v16; // esi
  int pThis_FF; // [esp+8h] [ebp-44h]
  float pThis_100; // [esp+10h] [ebp-3Ch]
  uint32_t v20[2]; // [esp+20h] [ebp-2Ch] BYREF
  char v21[4]; // [esp+28h] [ebp-24h] BYREF
  int **v22; // [esp+2Ch] [ebp-20h] BYREF
  void *Block; // [esp+30h] [ebp-1Ch] BYREF
  int i; // [esp+34h] [ebp-18h]
  int **v25; // [esp+38h] [ebp-14h] BYREF
  int v26; // [esp+3Ch] [ebp-10h]
  int v27; // [esp+48h] [ebp-4h]

  LOBYTE(v2) = *(this + 980);
  if ( (uint8_t)v2 != 0 )
  {
    pThis_1D = *((uint32_t *)this + 29);
    v4 = *(uint32_t *)(pThis_1D + 120);
    v2 = pThis_1D + 116;
    v5 = 0;
    if ( v4 != 0 )
    {
      v2 = (*(uint32_t *)(v2 + 8) - v4) >> 2;
      v26 = v2;
    }
    else
    {
      v26 = 0;
    }
    for ( i = 0; i < v26; ++i )
    {
      pThis_1D2 = *((uint32_t *)this + 29);
      v7 = *(uint32_t *)(pThis_1D2 + 120);
      if ( v7 != 0 && v5 < (*(uint32_t *)(pThis_1D2 + 124) - v7) >> 2 )
        v8 = *(uint32_t **)(v7 + 4 * v5);
      else
        v8 = nullptr;
      v9 = (int **)__RTDynamicCast(
                     v8,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &IRDActiveObject `RTTI Type Descriptor',
                     0);
      v22 = v9;
      if ( v9 != nullptr )
      {
        Block = v9;
        sub_4BE520(&v25, &Block);
        if ( (*(int (/*thiscall*/ **)(uint8_t *, int **, uint32_t))(*(uint32_t *)this + 8))(this, v9, 0) <= *((uint32_t *)this + 248)
          && (uint8_t)sub_4E4630(v9) != 0
          && ((int (/*thiscall*/ *)(int **))(*v9)[32])(v9) <= 0 )
        {
          if ( v25 == *((int ***)this + 258) )
          {
            pMem = operator new(0x7Cu);
            Block = pMem;
            v27 = 0;
            if ( pMem != nullptr )
            {
              *(float *)&pThis_FF = -*((float *)this + 255);
              v11 = (void **)sub_4B3DF0(pMem, 8, 1, pThis_FF, 0, 0);
            }
            else
            {
              v11 = nullptr;
            }
            v12 = (void (/*thiscall*/ **)(void **, int, int, uint32_t))*v11;
            pThis_100 = -*((float *)this + 256);
            v27 = -1;
            v12[30](v11, 6, 1, LODWORD(pThis_100));
            v13 = *(uint32_t *)this;
            Block = *v11;
            v14 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, int))(v13 + 576))(this, 0, 0, 0, -1);
            v15 = v22;
            (*((void (/*thiscall*/ **)(void **, int **, int))Block + 14))(v11, v22, v14);
            v20[0] = v15;
            v20[1] = v11;
            sub_5FA510(v21, v20);
          }
        }
        else
        {
          v16 = v25;
          if ( v25 != *((int ***)this + 258) )
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*v25[4] + 76))(v25[4], 0);
            sub_4C20A0((uint32_t *)this + 257, &v22, v16);
          }
        }
      }
      LOBYTE(v2) = v26;
      v5 = i + 1;
    }
  }
  return v2;
}


// ------------------------------------------------------------
// 0x61B440 sub_61B440
// ------------------------------------------------------------
// 凝固弹粒子：字符串证据「Particle/NapalmBombFire.ptl | NapalmBombFireLight.ptl」（本体火+光晕双发射器）+
// sub_4C3640 —— 弹体燃烧尾焰。
int /*thiscall*/ sub_61B440(int this)
{
  int pThis_16C; // eax
  int pThis_16C2; // eax
  int i; // esi
  int *fld_3DC; // edi
  bool v6; // zf
  int result; // eax
  int Block; // [esp+Ch] [ebp-14h]
  uint32_t *pThis_410; // [esp+10h] [ebp-10h]

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      pThis_16C = sub_4C3640(this + 364, "Particle/NapalmBombFire.ptl", this);
    else
      pThis_16C = sub_4C3640(*(uint32_t *)(this + 364), "Particle/NapalmBombFire.ptl", this);
  }
  else
  {
    pThis_16C = 0;
  }
  *(uint32_t *)(this + 1040) = pThis_16C;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      pThis_16C2 = sub_4C3640(this + 364, "Particle/NapalmBombFireLight.ptl", this);
    else
      pThis_16C2 = sub_4C3640(*(uint32_t *)(this + 364), "Particle/NapalmBombFireLight.ptl", this);
  }
  else
  {
    pThis_16C2 = 0;
  }
  *(uint32_t *)(this + 1044) = pThis_16C2;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_16C2 + 12))(pThis_16C2, 500);
  pThis_410 = (uint32_t *)(this + 1040);
  Block = 2;
  do
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*pThis_410 + 112))(*pThis_410, this);
    for ( i = 12; i < 24; i += 4 )
    {
      fld_3DC = (int *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_410 + 36))(*pThis_410) + i);
      *fld_3DC = (uint64_t)((double)*fld_3DC * *(float *)(this + 988));
    }
    result = Block - 1;
    v6 = Block == 1;
    ++pThis_410;
    --Block;
  }
  while ( !v6 );
  return result;
}



// ------------------------------------------------------------
// 0x61B590 sub_61B590
// ------------------------------------------------------------
// 地面火海四件套（157 行）：字符串证据「Animation/NapalmBombAreaFire1.ani | AreaFire2.ani | %s%d.ani |
// Animation/NapalmBombFireLight | Particle/NapalmBombAreaFireLight.ptl」——双动画层 + 编号动画模板 + 光粒子。
// sub_445D00（156B 粒子分配，P36 直证）+ sub_499240（vmt8 方向/邻近计算）+ sub_4924C0 ——
// 落点周围按方向铺设火海（方向性燃烧圈）。
void /*thiscall*/ sub_61B590(int *this, int nArg2, float fArg3, int nArg4, int nArg5)
{
  int v6; // eax
  int nRand3; // eax
  int v8; // edi
  int fld_e913; // ecx
  char *v10; // eax
  int pObj3; // ebx
  int pThis_6C; // edi
  int v13; // eax
  int v14; // eax
  int nRand; // eax
  int nRand2; // eax
  int v17; // eax
  int v18; // ebx
  int fld_e91; // ecx
  int *v20; // edi
  int pObj2; // edi
  int v22; // eax
  uint32_t *v23; // eax
  int fld_e912; // ecx
  int *v25; // edi
  int pObj; // edi
  int v27; // edx
  uint32_t *v28; // eax
  int v29; // [esp-10h] [ebp-130h]
  int v30; // [esp-10h] [ebp-130h]
  float v31; // [esp+0h] [ebp-120h]
  float v32; // [esp+4h] [ebp-11Ch]
  int v33; // [esp+Ch] [ebp-114h]
  int v34; // [esp+Ch] [ebp-114h]
  char Buffer[256]; // [esp+10h] [ebp-110h] BYREF
  int dword_796E502; // [esp+110h] [ebp-10h]
  int v37; // [esp+11Ch] [ebp-4h]
  int v38; // [esp+130h] [ebp+10h]
  int v39; // [esp+134h] [ebp+14h]

  dword_796E502 = dword_796E50;
  v29 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
  if ( (int)sub_499240(v6, v29, nArg2, SLODWORD(fArg3), 0) <= nArg5 )
  {
    if ( nArg4 != 0 )
    {
      if ( nArg4 == 1 )
      {
        nRand = rand();
        *(float *)&v38 = sub_4049C0(0.69999999, 1.0, nRand % 100, 99);
        nRand2 = rand();
        *(float *)&v39 = sub_4049C0(0.69999999, 1.0, nRand2 % 100, 99);
        v30 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
        v17 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
        v18 = 2 * sub_499240(v17, v30, nArg2, SLODWORD(fArg3), 0);
        v37 = 3;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( (unsigned int)*(this + 96) < 0x10 )
            LOBYTE(fld_e91) = (uint8_t)this + 108;
          else
            fld_e91 = *(this + 91);
          v20 = (int *)sub_431920(fld_e91, (char)"Animation/NapalmBombAreaFire1.ani", 1);
        }
        else
        {
          v20 = nullptr;
        }
        *(uint32_t *)(sub_4924C0(v20, 0) + 48) = v18;
        v37 = 4;
        if ( sub_44B6C0(284) != 0 )
          pObj2 = sub_44E1F0(v20, 1);
        else
          pObj2 = 0;
        v22 = *(uint32_t *)pObj2;
        v37 = -1;
        v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int, int))(v22 + 200))(pObj2, v38, v39);
        sub_4920E0(v23, v31, v32);
        sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, 0, 0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 112))(pObj2, nArg2);
        v37 = 5;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( (unsigned int)*(this + 96) < 0x10 )
            LOBYTE(fld_e912) = (uint8_t)this + 108;
          else
            fld_e912 = *(this + 91);
          v25 = (int *)sub_431920(fld_e912, (char)"Animation/NapalmBombAreaFire2.ani", 1);
        }
        else
        {
          v25 = nullptr;
        }
        *(uint32_t *)(sub_4924C0(v25, 0) + 48) = v18;
        v37 = 6;
        if ( sub_44B6C0(284) != 0 )
          pObj = sub_44E1F0(v25, 1);
        else
          pObj = 0;
        v27 = *(uint32_t *)pObj;
        v37 = -1;
        v28 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int, int))(v27 + 200))(pObj, v38, v39);
        sub_4920E0(v28, fArg3, 0.0);
        sub_45FE80(*(this + 29), pObj, 2, 0, pObj, 0, 0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 112))(pObj, nArg2);
      }
    }
    else
    {
      nRand3 = rand() % 2;
      sprintf(Buffer, "%s%d.ani", "Animation/NapalmBombFireLight", nRand3 + 1);
      v33 = sub_42FCB0(228);
      v8 = 0;
      v37 = 0;
      if ( v33 != 0 )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          LOBYTE(fld_e913) = (uint8_t)this + 108;
        else
          fld_e913 = *(this + 91);
        v8 = sub_431920(fld_e913, (char)Buffer, 1);
      }
      v37 = -1;
      v10 = (char *)sub_44B6C0(284);
      pObj3 = (int)v10;
      v37 = 1;
      if ( v10 != nullptr )
      {
        sub_44E0D0(v10, v8, 0);
        *(uint32_t *)pObj3 = &CNRDPooledObject::`vftable';
      }
      else
      {
        pObj3 = 0;
      }
      v37 = -1;
      v34 = sub_445D00(156);
      v37 = 2;
      if ( v34 != 0 )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          pThis_6C = sub_61AE10((uint8_t)this + 108, (int)"Particle/NapalmBombAreaFireLight.ptl");
        else
          pThis_6C = sub_61AE10(*(this + 91), (int)"Particle/NapalmBombAreaFireLight.ptl");
      }
      else
      {
        pThis_6C = 0;
      }
      v13 = *(uint32_t *)pThis_6C;
      v37 = -1;
      *(uint32_t *)(*(int (/*thiscall*/ **)(int))(v13 + 16))(pThis_6C) = nArg2;
      *(float *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_6C + 16))(pThis_6C) + 4) = fArg3;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_6C + 16))(pThis_6C) + 8) = 0;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 60))(pObj3);
      sub_4A0B60(v14, pThis_6C);
      sub_45FE80(*(this + 29), pThis_6C, 2, 0, pObj3, 0, 0);
    }
  }
}


// ------------------------------------------------------------
// 0x61B980 CNNapalmBomb__vmt14C
// ------------------------------------------------------------
// ★ CNNapalmBomb 主循环槽（vmt14C，220 行）：字符串证据「SIZZLE_LOOP」（音效 TAG —— 咝咝燃烧循环）。
// sub_424120（震屏）+ sub_47E720 族（判定）+ sub_4A0B60 + dword_9A0114（研究 20 P36 ⑤ 直证：全局粒子类型表）+
// sub_61B260/61B590（火海调度/铺设）—— 弹道→落地→火海蔓延的完整编排，
// 是本文件对 P36 粒子系统消费最重的函数之一。
char /*thiscall*/ sub_61B980(uint32_t *this)  // 【CNNapalmBomb__vmt14C】
{
  uint32_t *pThis_104; // edi
  int i; // ebx
  int v4; // eax
  int **pThis_1042; // ebx
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  uint32_t *Block2; // edi
  bool v11; // zf
  char *v12; // eax
  int fld_e176; // ebx
  char *v14; // edi
  int v15; // edi
  int pThis_9; // eax
  int fld_e248; // ecx
  int v18; // eax
  int fld_e2482; // edi
  int v20; // ebx
  int nRand; // eax
  int v22; // edx
  int nRand2; // ebx
  int v24; // eax
  int v25; // edx
  int pThis_94; // eax
  int pThis_92; // eax
  int fld_e2484; // ebx
  int v29; // edi
  int nRand3; // eax
  int v31; // edx
  int v32; // eax
  int nRand4; // edi
  int v34; // eax
  int pThis_93; // eax
  float v37; // [esp-Ch] [ebp-40h]
  float v38; // [esp-Ch] [ebp-40h]
  float pThis_F7; // [esp-4h] [ebp-38h]
  char v40[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  uint32_t *v42; // [esp+14h] [ebp-20h]
  int v43; // [esp+18h] [ebp-1Ch]
  int fld_e2483; // [esp+1Ch] [ebp-18h]
  int v45; // [esp+20h] [ebp-14h] BYREF
  int fld_e28; // [esp+24h] [ebp-10h]
  int v47; // [esp+30h] [ebp-4h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  if ( *((uint8_t *)this + 972) == 0 )
  {
    fld_e28 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 28) + 104) + 16))(*(uint32_t *)(*(this + 28) + 104))
                    + 76);
    pThis_104 = this + 260;
    for ( i = 2; i != 0; --i )
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_104 + 28))(*pThis_104);
      ++pThis_104;
      *(uint32_t *)(v4 + 76) = fld_e28;
    }
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);
    *((uint8_t *)this + 972) = 1;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) <= 0 )
  {
    if ( *((uint8_t *)this + 980) == 0 )
    {
      v12 = (char *)sub_47E720(2, 53);
      fld_e176 = *(this + 176);
      v14 = v12;
      sub_424120(*(uint32_t **)(*(this + 29) + 132), 4, 400);
      sub_4A0B60(0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      {
        fld_e28 = sub_47EFD0(v14, 0.0, fld_e176, *(this + 244), *(this + 244), 0);
        v45 = sub_47EF20(1, fld_e176, -1, -1, 11);
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int *))(*this + 580))(
          this,
          22210,
          fld_e28,
          0,
          0,
          0,
          0,
          0,
          4,
          0,
          2,
          &v45);
      }
      sub_607280(this + 249);
      v15 = sub_47EF20(6, fld_e176, -1, -1, 11);
      pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      fld_e248 = *(this + 248) * *(this + 248);
      *(this + 254) = pThis_9 + v15;
      sub_607260((int)sub_4C4B40 / (4 * dword_7930D4[0] * fld_e248 / 100), -1, 0, 1);
      sub_607280(this + 262);
      v18 = dword_73C5C8[dword_9A0114];
      fld_e28 = 0;
      if ( v18 > 0 )
      {
        do
        {
          fld_e2482 = *(this + 248) - 20;
          v20 = fld_e2482 * dword_7930D4[0] / 100;
          nRand = rand();
          v22 = *this;
          fld_e2483 = nRand % (2 * v20 + 1) - v20;
          LODWORD(v37) = (*(int (/*thiscall*/ **)(uint32_t *))(v22 + 124))(this) + fld_e2483;
          nRand2 = rand() % (2 * fld_e2482 + 1) - fld_e2482;
          v24 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
          sub_61B590(v24 + nRand2, v37, 1, fld_e2482);
          v25 = dword_73C5C8[dword_9A0114];
          ++fld_e28;
        }
        while ( fld_e28 < v25 );
      }
      *(float *)&fld_e2483 = (double)(int)*(this + 248) * 0.0044444446;
      sub_4922F0(*(float *)&fld_e2483);
      sub_4922F0(*(float *)&fld_e2483);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(
        this,
        0,
        *(uint32_t *)*(this + 36),
        0,
        0,
        0,
        1);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(
        this,
        1,
        *(uint32_t *)(*(this + 36) + 4),
        0,
        0,
        0,
        1);
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "SIZZLE_LOOP",
        10000,
        0,
        0);
      *((uint8_t *)this + 980) = 1;
      *(this + 246) = sub_699000((int)(this + 9));
    }
  }
  else
  {
    pThis_1042 = (int **)(this + 260);
    fld_e28 = 2;
    do
    {
      v6 = **pThis_1042;
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v7);
      v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v8);
      (*(void (/*thiscall*/ **)(int *, int))(v6 + 40))(*pThis_1042, v9);
      (*(void (/*thiscall*/ **)(int *, char *))(**pThis_1042 + 92))(*pThis_1042, v40);
      Block2 = Block;
      v47 = 0;
      if ( Block != v42 )
      {
        do
        {
          pThis_F7 = *((float *)this + 247);
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 200))(*Block2);
          sub_4922F0(pThis_F7);
          ++Block2;
        }
        while ( Block2 != v42 );
      }
      sub_4600B0((void *)*(this + 29), 2, 0, (int)v40);
      v47 = -1;
      if ( Block != nullptr )
        j__free(Block);
      ++pThis_1042;
      v11 = fld_e28 == 1;
      Block = nullptr;
      v42 = nullptr;
      v43 = 0;
      --fld_e28;
    }
    while ( !v11 );
  }
  sub_61B260(this);
  sub_61B0D0(this);
  LOBYTE(pThis_94) = *((uint8_t *)this + 980);
  if ( (uint8_t)pThis_94 != 0 )
  {
    if ( sub_699000((int)(this + 9)) < *(this + 254) - 1500 )  // 【clock_now(clk)】
    {
      pThis_92 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( (uint8_t)sub_6072C0(pThis_92) != 0 )
      {
        do
        {
          fld_e2484 = *(this + 248);
          v29 = fld_e2484 * dword_7930D4[0] / 100;
          nRand3 = rand();
          v31 = *this;
          fld_e2483 = nRand3 % (2 * v29 + 1) - v29;
          v32 = (*(int (/*thiscall*/ **)(uint32_t *))(v31 + 124))(this);
          LODWORD(v38) = v32 + fld_e2483;
          nRand4 = rand() % (2 * fld_e2484 + 1) - fld_e2484;
          v34 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
          sub_61B590(v34 + nRand4, v38, 0, fld_e2484);
          pThis_93 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
        }
        while ( (uint8_t)sub_6072C0(pThis_93) != 0 );
      }
    }
    LOBYTE(pThis_94) = *((uint8_t *)this + 980);
    if ( (uint8_t)pThis_94 != 0 )
    {
      pThis_94 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( pThis_94 >= *(this + 254) )
        LOBYTE(pThis_94) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
  }
  return pThis_94;
}


// ------------------------------------------------------------
// 0x61BE30 sub_61BE30
// ------------------------------------------------------------
void /*thiscall*/ sub_61BE30(uint8_t *this)
{
  *(this + 972) = 0;
}



// ------------------------------------------------------------
// 0x61BE50 CNTargetItBall__vmt1F4
// ------------------------------------------------------------
// CNTargetItBall 命中表现槽（vmt1F4）：字符串证据「Particle/TargetItBallPaint.ptl」（涂装粒子）+
// sub_5DDBA0 + dword_9B9410 —— 标记球（TargetItBall）命中目标时的涂色标记【推断：标记类 PO】。
int /*thiscall*/ CNTargetItBall__vmt1F4(int *this, uint32_t *Block, float *pArg3, char pszArg4)
{
  int v6; // eax
  int pThis_5B; // eax
  bool v8; // bl
  double v9; // st7
  int v10; // eax
  void *fld_e29; // ecx
  void *v13[4]; // [esp+8h] [ebp-20h] BYREF
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]
  void *Blocka; // [esp+30h] [ebp+8h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*Block + 40))(Block, 17) != 0
    && *((uint8_t *)this + 972) == 0
    && pszArg4 == 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
    if ( __RTDynamicCast(v6, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0) != 0 )
    {
      sub_5DDBA0(Block);
      if ( dword_9B9410 == 0 )
      {
        v15 = 0;
        if ( operator new(0x12Cu) != nullptr )
        {
          if ( (unsigned int)*(this + 96) < 0x10 )
            pThis_5B = sub_4C3640(this + 91, "Particle/TargetItBallPaint.ptl", 0);
          else
            pThis_5B = sub_4C3640(*(this + 91), "Particle/TargetItBallPaint.ptl", 0);
        }
        else
        {
          pThis_5B = 0;
        }
        v15 = -1;
        dword_9B9410 = pThis_5B;
      }
      v8 = (*(int (/*thiscall*/ **)(int *, uint32_t *))(*this + 660))(this, Block) == 1;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_9B9410 + 28))(dword_9B9410) + 84) = v8;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_9B9410 + 12))(dword_9B9410, 0);
      Blocka = (void *)(uint64_t)(pArg3[3] * 0.5 + *pArg3);
      v9 = pArg3[5] * 0.5 + pArg3[2];
      v14 = *(uint32_t *)dword_9B9410;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*Block + 124))(Block, (uint64_t)v9);
      (*(void (/*thiscall*/ **)(int, void *, int))(v14 + 40))(dword_9B9410, Blocka, v10 + 1);
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)dword_9B9410 + 92))(dword_9B9410, v13);
      fld_e29 = (void *)*(this + 29);
      v15 = 1;
      sub_4600B0(fld_e29, 2, 0, (int)v13);
      v15 = -1;
      sub_5E5260(v13);
    }
    *((uint8_t *)this + 972) = 1;
  }
  return CNRDPassiveObject__vmt1F4(this, Block, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61C020 CNHunterSpittle__vmt14C
// ------------------------------------------------------------
// CNHunterSpittle 主循环槽（vmt14C）：猎人唾液（HunterSpittle，蜘蛛吐弹【推断】）的飞行推进。
char /*thiscall*/ CNHunterSpittle__vmt14C(uint32_t *this)
{
  int v2; // eax
  int v3; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) == 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    if ( __RTDynamicCast(v2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNHunterMaster `RTTI Type Descriptor', 0) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));
    *((uint8_t *)this + 972) = 1;
  }
  if ( *(this + 30) == *(uint32_t *)*(this + 36) )
  {
    LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
    if ( (uint8_t)v3 != 0 )
    {
      LOBYTE(v3) = *(uint8_t *)(*(this + 30) + 170);
      if ( (uint8_t)v3 != 0 )
      {
        LOBYTE(v3) = *((uint8_t *)this + 264);
        if ( (uint8_t)v3 == 0 )
          LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
      }
    }
  }
  else
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    if ( v3 <= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 672))(this);
      *(uint32_t *)(v3 + 16) = 1000;
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x61C0F0 CNHunterSpittle__vmt1F4
// ------------------------------------------------------------
// CNHunterSpittle 命中表现槽（vmt1F4）：字符串证据「PassiveObject/Monster/Spider/Ani/PoisonWebLand.ani」
// （资源路径直证：蜘蛛族毒网）+ sub_44B6C0/44E0D0 + sub_45FE80 —— 唾液落地的毒网铺设。
int /*thiscall*/ CNHunterSpittle__vmt1F4(int *this, uint32_t *uArg2, float *pArg3, char pszArg4)
{
  int v5; // eax
  int v6; // ebx
  char *v7; // eax
  char *v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // ebx
  int v14; // eax

  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 340))(this) == 30017 )
  {
    v5 = sub_42FCB0(228);
    v6 = v5 != 0 ? sub_431860(v5, "PassiveObject/Monster/Spider/Ani/PoisonWebLand.ani", 1) : 0;
    if ( v6 != 0 )
    {
      v7 = (char *)sub_44B6C0(284);
      v8 = v7;
      if ( v7 != nullptr )
      {
        sub_44E0D0(v7, v6, 1);
        *(uint32_t *)v8 = &vftbl_CNRDPooledObject;
      }
      else
      {
        v8 = nullptr;
      }
      sub_45FE80(*(this + 29), (int)v8, 2, 0, (int)v8, (int)this, 0);
      v9 = *(uint32_t *)v8;
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v10);
      v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11);
      (*(void (/*thiscall*/ **)(char *, int))(v9 + 112))(v8, v12);
      v13 = *(uint32_t *)v8;
      v14 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      (*(void (/*thiscall*/ **)(char *, int))(v13 + 144))(v8, v14);
    }
  }
  return CNRDPassiveObject__vmt1F4(this, uArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61C210 CNZombieEye__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNZombieEye__vmt12C(uint32_t *this, int nArg2)
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 43739);
}



// ------------------------------------------------------------
// 0x61C240 CNZombieEye__vmt1F4
// ------------------------------------------------------------
// CNZombieEye 命中表现槽（vmt1F4）：sub_4E4A50 —— 僵尸眼球（ZombieEye）命中发包。
int /*thiscall*/ CNZombieEye__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int v4; // eax
  int v6; // eax
  int v8; // [esp-18h] [ebp-28h]
  int v9; // [esp-14h] [ebp-24h]
  int v10; // [esp-10h] [ebp-20h]
  int v11; // [esp+Ch] [ebp-4h] BYREF

  v4 = *pArg2;
  v11 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v4 + 648))(pArg2, &v11, this);
  if ( ((*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 44))(pArg2) == 273
     || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 44))(pArg2) == 529)
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg2 + 308))(pArg2) != 0
    && pszArg4 == 0
    && v11 > 0 )
  {
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    sub_4E4A50(*(this + 173), 30005, 0, v6, v8, v9, v10, 0, 0, 0);
  }
  return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61C300 CNZombieEyeExplode__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNZombieEyeExplode__vmt14C(uint8_t *this)
{
  int result; // eax

  if ( *(this + 972) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "ZOMBIE_EYEEXPLOTION",
      -1,
      0,
      0);
    *(this + 972) = 1;
  }
  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( *(uint8_t *)(result + 170) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61C360 sub_61C360
// ------------------------------------------------------------
int /*thiscall*/ sub_61C360(float *this, int nArg2)
{
  uint32_t *pThis_24; // eax
  int result; // eax

  pThis_24 = *((uint32_t **)this + 36);
  *(this + 181) = (float)nArg2;
  result = (*(int (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
             this,
             1,
             *pThis_24,
             0,
             0,
             0,
             0);
  *((uint8_t *)this + 972) = 0;
  *((uint8_t *)this + 973) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x61C3A0 CNZombieEye__vmt14C
// ------------------------------------------------------------
// CNZombieEye 主循环槽（vmt14C）：字符串证据「ZOMBIE_EYEROLLING_LOOP」（音效 TAG —— 眼球滚动循环）——
// 悬浮眼球机关的循环维持。
char /*thiscall*/ CNZombieEye__vmt14C(int *this)
{
  int v2; // eax
  int fld_e139; // eax
  int v4; // eax
  int v5; // eax
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) != 0 )
    goto LABEL_10;
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
  if ( __RTDynamicCast(v2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNZombieHollowEye `RTTI Type Descriptor', 0) != 0 )
  {
    fld_e139 = *(this + 139);
LABEL_8:
    (*(void (/*stdcall*/ **)(int))(*this + 344))(fld_e139);
    goto LABEL_9;
  }
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
  if ( __RTDynamicCast(v4, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNZombieGhoulgwish `RTTI Type Descriptor', 0) != 0 )
  {
    fld_e139 = *(this + 139) + 152;
    goto LABEL_8;
  }
  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
  if ( __RTDynamicCast(v5, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNKalkazak `RTTI Type Descriptor', 0) != 0 )
  {
    fld_e139 = *(this + 139) + 304;
    goto LABEL_8;
  }
LABEL_9:
  *((uint8_t *)this + 972) = 1;
LABEL_10:
  result = *((uint8_t *)this + 973);
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
               this,
               "ZOMBIE_EYEROLLING_LOOP",
               43739,
               0,
               0);
    *((uint8_t *)this + 973) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x61C490 sub_61C490
// ------------------------------------------------------------
int /*thiscall*/ sub_61C490(uint32_t *this)
{
  uint32_t *fld_e36; // eax
  int v3; // edx
  int result; // eax

  fld_e36 = (uint32_t *)*(this + 36);
  v3 = *this;
  *(this + 181) = 0;
  result = (*(int (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v3 + 204))(1, *fld_e36, 0, 0, 0, 0);
  *((uint8_t *)this + 972) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x61C4D0 CNKagelBomb__vmt200
// ------------------------------------------------------------
// CNKagelBomb 表现壳槽（vmt200，91 行）：sub_423A20（UDP 广播）+ dword_796E50 ——
// 卡格炸弹（KagelBomb）的状态表现与广播。
int /*thiscall*/ CNKagelBomb__vmt200(int *this, int nArg2, float *pArg3, int nArg4)
{
  int pObj; // edi
  int v7; // eax
  uint16_t *v8; // eax
  uint16_t *v9; // esi
  int v10; // eax
  int v11; // esi
  int nRand; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int pThis_1; // esi
  int v17; // esi
  int v18; // eax
  int v19; // esi
  int v20; // eax
  int *v22; // [esp+Ch] [ebp-6Ch]
  uint32_t v23[26]; // [esp+10h] [ebp-68h] BYREF
  int v24; // [esp+80h] [ebp+8h]

  v23[25] = dword_796E50;
  v24 = CNRDPassiveObject__vmt200(this, nArg2, pArg3, nArg4);
  if ( nArg2 != 0 )
  {
    pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);
    v22 = (int *)pObj;
  }
  else
  {
    v22 = nullptr;
    pObj = 0;
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
  if ( pObj != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 88))(this) == 1
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
  {
    sub_423A20((int)v23);
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 60))(this);
    v8 = (uint16_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v7 + 104) + 16))(*(uint32_t *)(v7 + 104));
    qmemcpy(v23, v8, 0x60u);
    v9 = v8 + 48;
    v10 = *v22;
    LOWORD(v23[24]) = *v9;
    v11 = (*(int (/*thiscall*/ **)(int *))(v10 + 120))(v22);
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < v11 )
      nRand = 135 - rand() % 20;
    else
      nRand = rand() % 20 + 45;
    v13 = *this;
    *(uint32_t *)((char *)&v23[3] + 3) = 300;
    *(uint32_t *)((char *)&v23[4] + 3) = 300;
    *(uint32_t *)((char *)&v23[7] + 3) = 0;
    *(uint32_t *)((char *)&v23[8] + 3) = 0;
    v23[18] = 0;
    v23[19] = nRand;
    nArg4 = (*(int (/*thiscall*/ **)(int *))(v13 + 120))(this);
    v14 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v15 = *this;
    pArg3 = (float *)v14;
    pThis_1 = (*(int (/*thiscall*/ **)(int *))(v15 + 128))(this) + 1;
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int, float *, uint32_t))(*this + 136))(this, nArg4, pArg3, 0) != 0
      || (*(uint8_t (/*thiscall*/ **)(int *, int *, float **, int, float *, int, int, int))(*this + 140))(
           this,
           &nArg4,
           &pArg3,
           nArg4,
           pArg3,
           100,
           1,
           1) != 0 )
    {
      v23[1] = pArg3;
      v23[0] = nArg4;
      v23[2] = pThis_1;
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
      v17 = *(uint32_t *)dword_8F8520;
      v18 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
      (*(void (/*thiscall*/ **)(int, int))(v17 + 36))(dword_8F8520, v18);
      v19 = *(uint32_t *)dword_8F8520;
      v20 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
      (*(void (/*thiscall*/ **)(int, int))(v19 + 36))(dword_8F8520, v20);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v23, 98);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    }
  }
  return v24;
}



// ------------------------------------------------------------
// 0x61C7A0 CNKagelBomb__vmt14C
// ------------------------------------------------------------
// CNKagelBomb 主循环槽（vmt14C）：sub_4E4A50 —— 卡格炸弹引信推进；爆炸音 BOMB_EXPLOSION 见 0x61C860。
int /*thiscall*/ CNKagelBomb__vmt14C(uint32_t *this)
{
  uint32_t *fld_e173; // edi
  int v2; // eax
  uint32_t *fld_e36; // edi
  int v5; // eax
  int v6; // edx
  int result; // eax
  int v8; // [esp-18h] [ebp-20h]
  int v9; // [esp-14h] [ebp-1Ch]
  int v10; // [esp-10h] [ebp-18h]

  CNRDPassiveObject__vmt14C((int)this);
  fld_e36 = (uint32_t *)*(this + 36);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  v6 = *this;
  if ( v5 == *fld_e36 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 200))(this);
    if ( *(uint8_t *)(result + 170) != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)result != 0 && *((uint8_t *)this + 264) != 1 )
      {
        fld_e173 = (uint32_t *)*(this + 173);
        if ( fld_e173 == nullptr )
          fld_e173 = this;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
        v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
        v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
        sub_4E4A50(fld_e173, *(this + 243), 0, v2, v8, v9, v10, 0, 0, 0);
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
      }
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 128))(this);
    if ( result <= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this) + 60) = 0;
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this);
      *(uint32_t *)result = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61C830 sub_61C830
// ------------------------------------------------------------
int /*thiscall*/ sub_61C830(uint32_t *this, int nArg2)
{
  sub_4015C0("THROW_BOMB", 0xAu);  // 【std::string构造赋值】
  *(this + 243) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x61C860 sub_61C860
// ------------------------------------------------------------
// 卡格弹爆炸辅助：字符串证据「BOMB_EXPLOSION」（音效 TAG）+ sub_4015C0 —— 播音 TAG 装配。
int /*thiscall*/ sub_61C860(uint32_t **this)
{
  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) == 0 )
  {
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this)[51])(
      this,
      2,
      **(this + 36),
      0,
      0,
      0,
      1);
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this)[51])(
      this,
      1,
      (*(this + 36))[1],
      0,
      0,
      0,
      1);
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      1,
      (*(this + 36))[2],
      0,
      0,
      0,
      0);
  }
  return sub_4015C0("BOMB_EXPLOSION", 0xEu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x61C8E0 CNKagelBombSub__vmt14C
// ------------------------------------------------------------
// CNKagelBombSub 主循环槽（vmt14C，84 行）：sub_41ACF0 + sub_428F30（发射器）+ sub_4600B0 ——
// 卡格弹子体的分裂/爆炸演出（与 0x6107E0 CurseBombSub 同构）。
int /*thiscall*/ CNKagelBombSub__vmt14C(int **this)
{
  uint32_t *pMem; // edi
  int *v3; // eax
  int fld_e178; // eax
  uint32_t *pMem2; // edi
  int fld_e1782; // eax
  int *v7; // eax
  int **pThis_F3; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  void *fld_e29; // ecx
  bool v14; // zf
  int result; // eax
  uint8_t v16[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]
  int v19; // [esp+14h] [ebp-14h]
  void *pMem3; // [esp+18h] [ebp-10h]
  int v21; // [esp+24h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 243) == nullptr && *(this + 244) == nullptr )
  {
    pMem = operator new(0x12Cu);
    pMem3 = pMem;
    v3 = nullptr;
    v21 = 0;
    if ( pMem != nullptr )
    {
      fld_e178 = sub_41ACF0(*(this + 178));
      v3 = sub_428F30(pMem, fld_e178, (int)this);
    }
    *(this + 243) = v3;
    pMem2 = operator new(0x12Cu);
    pMem3 = pMem2;
    v21 = 1;
    if ( pMem2 != nullptr )
    {
      fld_e1782 = sub_41ACF0(*(this + 178) + 1);
      v7 = sub_428F30(pMem2, fld_e1782, (int)this);
    }
    else
    {
      v7 = nullptr;
    }
    v21 = -1;
    *(this + 244) = v7;
    pThis_F3 = this + 243;
    pMem3 = (void *)2;
    do
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(**pThis_F3 + 12))(*pThis_F3, 0);
      v9 = **pThis_F3;
      v10 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
      v11 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v10);
      v12 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v11);
      (*(void (/*thiscall*/ **)(int *, int))(v9 + 40))(*pThis_F3, v12);
      (*(void (/*thiscall*/ **)(int *, uint8_t *))(**pThis_F3 + 92))(*pThis_F3, v16);
      fld_e29 = *(this + 29);
      v21 = 2;
      sub_4600B0(fld_e29, 2, 0, (int)v16);
      v21 = -1;
      if ( Block != nullptr )
        j__free(Block);
      ++pThis_F3;
      v14 = pMem3 == (void *)1;
      Block = nullptr;
      v18 = 0;
      v19 = 0;
      pMem3 = (char *)pMem3 - 1;
    }
    while ( !v14 );
  }
  result = ((int (/*thiscall*/ *)(int **))(*this)[50])(this);
  if ( *(uint8_t *)(result + 170) != 0 )
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
    if ( (uint8_t)result == 1 )
      return ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61CA80 CNSpaceFishBug__vmt1F4
// ------------------------------------------------------------
// CNSpaceFishBug 命中表现槽（vmt1F4）：sub_432FA0（UDP 广播）+ sub_496F80 ——
// 太空鱼虫（SpaceFishBug）命中广播。
int /*thiscall*/ CNSpaceFishBug__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int v5; // eax
  int i; // ebx
  int v8; // ebx
  int v9; // eax
  int v11; // [esp+8h] [ebp-4h] BYREF
  int nRand; // [esp+14h] [ebp+8h]

  v5 = *pArg2;
  v11 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v5 + 648))(pArg2, &v11, this);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0
    && rand() % 100 < 40
    && pszArg4 == 0
    && v11 > 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg2 + 308))(pArg2) != 0 )
  {
    sub_432FA0();
    for ( i = 170; i > 0; --i )
    {
      nRand = rand() % 17;
      if ( sub_496F80(nRand) != 16 )
        break;
    }
    v8 = *pArg2;
    v9 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 684))(this, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, int))(v8 + 760))(pArg2, nRand, 1120403456, *(this + 243), v9);
  }
  return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61CB60 sub_61CB60
// ------------------------------------------------------------
// 太空鱼虫辅助：字符串证据「SFISH_CAST」（音效 TAG —— 鱼虫抛出）+ sub_4049C0 lerp —— 抛射参数插值。
int /*thiscall*/ sub_61CB60(int **this, int *pDwArg2)
{
  int v3; // eax
  int v4; // ecx
  int *fld_e87; // eax
  uint64_t v6; // rax
  int result; // eax
  float v8; // [esp+0h] [ebp-1Ch]
  float v9; // [esp+4h] [ebp-18h]

  v3 = 0;
  switch ( *(uint32_t *)(dword_8F7A24 + 12) )
  {
    case 3:
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);
      break;
    case 4:
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 16) + 108);
      break;
    case 6:
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108);
      break;
    default:
      break;
  }
  v4 = *(uint32_t *)(v3 + 112);
  fld_e87 = *(this + 87);
  v9 = (float)fld_e87[1];
  v8 = (float)*fld_e87;
  v6 = (uint64_t)sub_4049C0(v8, v9, v4 - 1, 98);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 170) = (int *)v6;
  *(this + 171) = (int *)v6;
  result = sub_4015C0("SFISH_CAST", 0xAu);  // 【std::string构造赋值】
  *(this + 243) = pDwArg2;
  return result;
}



// ------------------------------------------------------------
// 0x61CC10 CNLOLLaser__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNLOLLaser__vmt14C(uint32_t *this)
{
  int fld_e30; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 980) != 0 && *(this + 243) + *(this + 244) < (unsigned int)sub_699000((int)(this + 9)) )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
    *(this + 243) = sub_699000((int)(this + 9));
  }
  fld_e30 = *(this + 30);
  if ( *(uint8_t *)(fld_e30 + 170) != 0 )
  {
    LOBYTE(fld_e30) = *((uint8_t *)this + 264);
    if ( (uint8_t)fld_e30 == 0 )
    {
      LOBYTE(fld_e30) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)fld_e30 != 0 )
        LOBYTE(fld_e30) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
  }
  return fld_e30;
}



// ------------------------------------------------------------
// 0x61CC90 CNLOLLaser__vmtC
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNLOLLaser__vmtC(int *this)
{
  uint32_t *result; // eax
  uint32_t *v3; // esi

  CNRDPassiveObject__vmtC(this);
  sub_4926A0(*(this + 30));
  sub_4938F0(*(this + 30));
  result = (uint32_t *)*(this + 32);
  v3 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      sub_4926A0(v3[3]);
      result = sub_4938F0(v3[3]);
      v3 = (uint32_t *)*v3;
    }
    while ( v3 != (uint32_t *)*(this + 32) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x61CCE0 CNLOLLaser__vmt2C4
// ------------------------------------------------------------
// CNLOLLaser tick 槽（vmt2C4）：sub_699000 —— LOL 激光（LOL = LegOfLotus 莲花腿【推断】，
// 与 CNLegOfLotus 类族配套）的持续照射推进。
uint32_t */*thiscall*/ CNLOLLaser__vmt2C4(uint32_t **this, int nArg2)
{
  int nArg22; // ebx
  int v4; // edi
  int pThis_9; // eax
  uint32_t *v6; // edx
  uint32_t *result; // eax

  nArg22 = nArg2;
  if ( nArg2 > 0 )
  {
    v4 = 0;
    do
    {
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this)[51])(
        this,
        0,
        **(this + 36),
        v4,
        0,
        0,
        0);
      v4 += 100;
      --nArg22;
    }
    while ( nArg22 != 0 );
  }
  pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  v6 = *this;
  *(this + 243) = (uint32_t *)pThis_9;
  *((uint8_t *)this + 980) = 0;
  result = **(uint32_t ***)(((int (/*thiscall*/ *)(uint32_t **))v6[85])(this) + 64);
  *(this + 244) = result;
  return result;
}



// ------------------------------------------------------------
// 0x61CD50 sub_61CD50
// ------------------------------------------------------------
int /*thiscall*/ sub_61CD50(uint32_t *this, int nArg2)
{
  *(this + 243) = 0;
  *(this + 244) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x61CD70 CNBronzeGolemBullets__vmt12C
// ------------------------------------------------------------
// CNBronzeGolemBullets 消亡联动槽（vmt12C）：sub_4E4A50 —— 青铜魔像弹幕（BronzeGolemBullets）消亡发包。
void /*thiscall*/ CNBronzeGolemBullets__vmt12C(uint32_t *this, int nArg2)
{
  int v3; // eax
  int v4; // eax
  int fld_e244; // [esp-20h] [ebp-28h]
  int v6; // [esp-1Ch] [ebp-24h]
  int v7; // [esp-18h] [ebp-20h]
  int v8; // [esp-14h] [ebp-1Ch]
  int v9; // [esp-10h] [ebp-18h]

  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this
    && *(this + 243) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    fld_e244 = *(this + 244);
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    sub_4E4A50(v3, 30045, fld_e244, v6, v7, v8, v9, 0, 0, 0);
  }
  if ( *(this + 243) == nArg2 )
  {
    v4 = *this;
    *(this + 243) = 0;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 84))(this, 0);
  }
}



// ------------------------------------------------------------
// 0x61CE10 CNBronzeGolemBullets__vmt1F4
// ------------------------------------------------------------
// CNBronzeGolemBullets 命中表现槽（vmt1F4）：sub_4A06D0（挂点跟随族）—— 魔像弹命中演出。
int /*thiscall*/ CNBronzeGolemBullets__vmt1F4(int this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int v5; // edx
  int v6; // eax
  uint32_t *v7; // eax
  int pThis_3C; // eax
  int fld_3CC; // edi
  int v10; // ebx
  int nRand2; // eax
  int nRand; // [esp-4h] [ebp-10h]
  int v14; // [esp+0h] [ebp-Ch]
  int v15; // [esp+18h] [ebp+Ch]
  int fld_3CC2; // [esp+1Ch] [ebp+10h]

  if ( pszArg4 != 0 || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) == 0 )
    return CNRDPassiveObject__vmt1F4((int *)this, pArg2, pArg3, pszArg4);
  v5 = *(uint32_t *)this;
  *(uint32_t *)(this + 972) = pArg2;
  v6 = (*(int (/*thiscall*/ **)(int))(v5 + 60))(this);
  v7 = (uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v6 + 104) + 16))(*(uint32_t *)(v6 + 104)) + 15);
  *v7 = 0;
  v7[1] = 0;
  v7[2] = 0;
  v7[3] = 0;
  v7[4] = 0;
  v7[5] = 0;
  pThis_3C = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 60))(this);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pThis_3C + 104) + 4))(*(uint32_t *)(pThis_3C + 104), 0);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 144));
  fld_3CC = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 972) + 120))(*(uint32_t *)(this + 972));
  fld_3CC2 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 972) + 124))(*(uint32_t *)(this + 972));
  v10 = *(uint32_t *)this;
  v15 = (uint64_t)(pArg3[5] * 0.5 + pArg3[2]);
  nRand = rand() % 6 + v15 - 3;
  nRand2 = rand();
  (*(void (/*thiscall*/ **)(int, int, int, int))(v10 + 112))(this, nRand2 % 6 + fld_3CC - 3, fld_3CC2, nRand);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 60))(this, *(uint32_t *)(this + 972));
  sub_4A06D0(v14);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 596))(this, 0);
  return 0;
}



// ------------------------------------------------------------
// 0x61CF30 sub_61CF30
// ------------------------------------------------------------
int /*thiscall*/ sub_61CF30(uint8_t *this)
{
  *(this + 974) = 0;
  return sub_4015C0("G_ICEWAVE_MOVING", 0x10u);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x61CF50 CNIceWaveUp__vmt14C
// ------------------------------------------------------------
// CNIceWaveUp 主循环槽（vmt14C，141 行）：字符串证据「ICEWAVE_CREATE」（音效 TAG，冰浪系同款）。
// sub_4DB200 + sub_4E77D0 + dword_8F82A4/A8/AC（冰浪池化槽）—— 上升冰浪（IceWaveUp）的推进；
// 与 0x611C70/0x612B70 构成冰浪三形态（追踪/多段/上升）。
int /*thiscall*/ sub_61CF50(uint32_t *this)  // 【CNIceWaveUp__vmt14C】
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int pObj; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *fld_e29; // ecx
  int v11; // edx
  uint32_t *v12; // eax
  int fld_e30; // eax
  int pObj2; // edi
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  void *fld_e292; // ecx
  int pObj3; // edi
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  void *fld_e293; // ecx
  void *v27; // eax
  bool v28; // zf
  int result; // eax
  uint8_t v30[4]; // [esp+Ch] [ebp-3Ch] BYREF
  void *Block; // [esp+10h] [ebp-38h]
  uint8_t v32[4]; // [esp+1Ch] [ebp-2Ch] BYREF
  void *v33; // [esp+20h] [ebp-28h]
  int v34; // [esp+24h] [ebp-24h]
  int v35; // [esp+28h] [ebp-20h]
  uint8_t v36[4]; // [esp+2Ch] [ebp-1Ch] BYREF
  void *v37; // [esp+30h] [ebp-18h]
  int v38; // [esp+34h] [ebp-14h]
  int v39; // [esp+38h] [ebp-10h]
  int v40; // [esp+44h] [ebp-4h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v3);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v2 + 136))(this, v4) != 0 )
  {
    if ( *((uint8_t *)this + 973) == 0 )
    {
      pObj = dword_8F82A4;
      v6 = *(uint32_t *)dword_8F82A4;
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v7);
      v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v8);
      (*(void (/*thiscall*/ **)(int, int))(v6 + 40))(pObj, v9);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj + 92))(pObj, v30);
      fld_e29 = (void *)*(this + 29);
      v40 = 0;
      sub_4600B0(fld_e29, 2, 0, (int)v30);
      v11 = *this;
      *((uint8_t *)this + 973) = 1;
      v12 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(v11 + 576))(this);
      if ( __RTDynamicCast(
             v12,
             0,
             &IRDActiveObject `RTTI Type Descriptor',
             &CNIceDoll_Sharedo `RTTI Type Descriptor',
             0) != nullptr )
        sub_4DB200(24, 0);
      v40 = -1;
      if ( Block != nullptr )
        j__free(Block);
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    *((uint8_t *)this + 974) = 1;
  }
  if ( *((uint8_t *)this + 972) == 0 )
  {
    fld_e30 = *(this + 30);
    if ( fld_e30 != 0 && *(int *)(fld_e30 + 148) >= 6 )
    {
      pObj2 = dword_8F82A8;
      v15 = *(uint32_t *)dword_8F82A8;
      v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v17 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v16 + 20);
      v18 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v17);
      (*(void (/*thiscall*/ **)(int, int))(v15 + 40))(pObj2, v18);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj2 + 92))(pObj2, v36);
      fld_e292 = (void *)*(this + 29);
      v40 = 1;
      sub_4600B0(fld_e292, 2, 0, (int)v36);
      pObj3 = dword_8F82AC;
      v21 = *(uint32_t *)dword_8F82AC;
      v22 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v23 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v22 + 20);
      v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v23);
      (*(void (/*thiscall*/ **)(int, int))(v21 + 40))(pObj3, v24);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj3 + 12))(pObj3, 0);
      v25 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj3 + 92))(pObj3, v32);
      LOBYTE(v40) = 2;
      sub_4E77D0((int)v36, v25);
      LOBYTE(v40) = 1;
      if ( v33 != nullptr )
        j__free(v33);
      fld_e293 = (void *)*(this + 29);
      v33 = nullptr;
      v34 = 0;
      v35 = 0;
      sub_4600B0(fld_e293, 2, 0, (int)v36);
      v27 = v37;
      v28 = v37 == nullptr;
      *((uint8_t *)this + 972) = 1;
      v40 = -1;
      if ( !v28 )
        j__free(v27);
      v37 = nullptr;
      v38 = 0;
      v39 = 0;
    }
  }
  result = *(this + 30);
  if ( result != 0 && *(uint8_t *)(result + 170) != 0 )
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  if ( *((uint8_t *)this + 974) == 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
               this,
               "ICEWAVE_CREATE",
               -1,
               0,
               0);
    *((uint8_t *)this + 974) = 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x61D1D0 sub_61D1D0
// ------------------------------------------------------------
int /*thiscall*/ sub_61D1D0(uint8_t *this, int nArg2)
{
  int result; // eax

  result = nArg2;
  *(this + 972) = 0;
  *((uint32_t *)this + 244) = nArg2;
  if ( nArg2 != 0xFFFF )
  {
    result = dword_9B9418;
    if ( dword_9B9418 <= dword_795C54 )
    {
      ++dword_9B9418;
      *(this + 972) = 1;
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 84))(this, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61D220 CNLegOfLotus__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNLegOfLotus__vmt12C(uint32_t *this, int nArg2)
{
  int v3; // eax
  int v4; // eax

  if ( (uint32_t *)nArg2 == this && *(this + 244) != 0xFFFF && dword_9B9418 == 1 )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);
    v4 = __RTDynamicCast(v3, 0, &IRDActiveObject `RTTI Type Descriptor', &CNLotus `RTTI Type Descriptor', 0);
    sub_5C9A00(v4);
  }
  CNRDPassiveObject__vmt12C(this, nArg2);
}



// ------------------------------------------------------------
// 0x61D280 sub_61D280
// ------------------------------------------------------------
int /*thiscall*/ sub_61D280(uint8_t *this)
{
  int v1; // eax
  int result; // eax

  v1 = *(uint32_t *)this;
  *(this + 984) = 0;
  result = (*(int (**)(void))(v1 + 672))();
  *(uint8_t *)(result + 20) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x61D2A0 CNPierceHeadLegOfLotus__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNPierceHeadLegOfLotus__vmt12C(uint32_t *this, int nArg2)
{
  CNLegOfLotus__vmt12C(this, nArg2);
}



// ------------------------------------------------------------
// 0x61D2B0 CNPierceHeadLegOfLotus__vmt14C
// ------------------------------------------------------------
// CNPierceHeadLegOfLotus 主循环槽（vmt14C）：字符串证据「LOTUS_THRUST」（音效 TAG —— 莲花腿突进）——
// 莲花腿穿头（PierceHead）的突进推进。
char /*thiscall*/ CNPierceHeadLegOfLotus__vmt14C(uint32_t *this)
{
  int v2; // eax
  int fld_e28; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 984) == 0 )
  {
    *(uint32_t *)(*(this + 28) + 36) = -3000;
    *(this + 245) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v2 = *this;
    *((uint8_t *)this + 984) = 1;
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v2 + 212))(this, "LOTUS_THRUST", -1, 0, 0);
  }
  if ( *(int *)(*(this + 28) + 36) < 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) <= 50 )
    *(uint32_t *)(*(this + 28) + 36) = (uint64_t)((double)1500 * 3.0);
  fld_e28 = *(uint32_t *)(*(this + 28) + 36);
  if ( fld_e28 >= 0 )
  {
    fld_e28 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    if ( fld_e28 > *(this + 245) )
    {
      LOBYTE(fld_e28) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)fld_e28 != 0 )
      {
        LOBYTE(fld_e28) = *((uint8_t *)this + 264);
        if ( (uint8_t)fld_e28 == 0 )
          LOBYTE(fld_e28) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
      }
    }
  }
  return fld_e28;
}



// ------------------------------------------------------------
// 0x61D380 sub_61D380
// ------------------------------------------------------------
int /*thiscall*/ sub_61D380(uint32_t **this)
{
  int fld_e252; // edi
  int v3; // eax

  fld_e252 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 252) + 192))(*(this + 252)) / 2;
  v3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
  return v3 - fld_e252 <= 0 ? 0 : v3 - fld_e252;
}



// ------------------------------------------------------------
// 0x61D3C0 CNGrabbingLegOfLotus__vmt10
// ------------------------------------------------------------
int /*thiscall*/ CNGrabbingLegOfLotus__vmt10(int *this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  if ( result < 40 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, 40);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v4);
    return (*(int (/*thiscall*/ **)(int *, int))(v3 + 112))(this, v5);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61D3F0 sub_61D3F0
// ------------------------------------------------------------
int /*thiscall*/ sub_61D3F0(uint32_t *this)
{
  uint32_t *pThis; // esi
  uint32_t *fld_e87; // eax
  int v3; // edx

  pThis = this;
  fld_e87 = (uint32_t *)*(this + 87);
  v3 = *this;
  *((uint8_t *)this + 984) = 0;
  *((uint8_t *)this + 985) = 0;
  *(this + 252) = 0;
  *(this + 247) = *fld_e87;
  *(uint8_t *)((*(int (**)(void))(v3 + 672))() + 20) = 0;
  pThis += 253;
  *pThis = 0;
  pThis[1] = 0;
  pThis[2] = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x61D440 sub_61D440
// ------------------------------------------------------------
// 莲花腿辅助：sub_4926A0/4939E0（定时器/动画）+ dword_9B941C ——【推断：抓取计时与目标缓存】。
int /*thiscall*/ sub_61D440(uint32_t *this)
{
  int fld_e252; // ecx

  if ( (int)*(this + 251) <= 150 )
    *(uint32_t *)(*(this + 28) + 24) = dword_9B941C;
  else
    *(uint32_t *)(*(this + 28) + 24) = -1002733568;
  sub_4926A0(*(uint32_t *)(*(this + 36) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
  sub_4926A0(*(uint32_t *)(*(this + 36) + 8));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this + 204))(
    this,
    -100,
    *(uint32_t *)(*(this + 36) + 8),
    0,
    -2,
    0,
    0);
  sub_4939E0(*(uint32_t *)(*(this + 36) + 4), 1);
  sub_4939E0(*(uint32_t *)(*(this + 36) + 8), 1);
  *(this + 248) = *(this + 247);
  fld_e252 = *(this + 252);
  *(this + 249) = 0;
  *(this + 250) = 0;
  (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)fld_e252 + 472))(fld_e252, 9, 0, 1, 1);
  (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 564))(*(this + 252));
  return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 252) + 848))(*(this + 252), 1);
}



// ------------------------------------------------------------
// 0x61D540 sub_61D540
// ------------------------------------------------------------
char /*thiscall*/ sub_61D540(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax

  *(uint32_t *)(*(this + 28) + 24) = 0;
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, 150);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v3);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v2 + 112))(this, v4);
  sub_4939E0(*(uint32_t *)(*(this + 36) + 4), 0);
  return sub_4939E0(*(uint32_t *)(*(this + 36) + 8), 0);
}



// ------------------------------------------------------------
// 0x61D590 CNGrabbingLegOfLotus__vmt218
// ------------------------------------------------------------
// CNGrabbingLegOfLotus 槽（vmt218）：sub_491C10 ——【推断：抓取动画绑定】。
int /*thiscall*/ CNGrabbingLegOfLotus__vmt218(int *this, int nArg2)
{
  int result; // eax
  int fld_e36; // eax
  int fld_e250; // ecx
  int fld_e252; // edi
  int fld_e2522; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = nArg2;
  if ( nArg2 == *(this + 252) && *(this + 248) > 1 )
  {
    fld_e36 = sub_491C10(*(uint32_t *)(*(this + 36) + 4));
    fld_e250 = *(this + 250) + 1;
    *(this + 250) = fld_e250;
    if ( fld_e250 >= 5 * fld_e36 / 1000 )
    {
      --*(this + 248);
      *(this + 250) = 0;
    }
    fld_e252 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 120))(*(this + 252));
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 916))(*(this + 252));
    fld_e2522 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 120))(*(this + 252));
    v8 = *this;
    v9 = fld_e252 - fld_e2522;
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v10);
    v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11);
    return (*(int (/*thiscall*/ **)(int *, int))(v8 + 112))(this, v12 - v9);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61D650 CNGrabbingLegOfLotus__vmt1F4
// ------------------------------------------------------------
// CNGrabbingLegOfLotus 命中表现槽（vmt1F4）：字符串证据「TRAP_OCTOPUS_CATCH」（音效 TAG —— 章鱼陷阱捕获）+
// sub_61D440 —— 抓取腿（GrabbingLegOfLotus）捕获目标。
int /*thiscall*/ CNGrabbingLegOfLotus__vmt1F4(int this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int v5; // eax
  int fld_3F0; // ecx
  int v7; // eax
  int fld_3F02; // ecx

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 44))(pArg2) == 273
    && *(uint8_t *)(this + 985) == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg2 + 948))(pArg2) != 0 )
  {
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "TRAP_OCTOPUS_CATCH",
      -1,
      0,
      0);
    *(uint32_t *)(this + 1004) = (uint64_t)pArg3[2];
    *(uint32_t *)(this + 1008) = pArg2;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 120))(pArg2);
    fld_3F0 = *(uint32_t *)(this + 1008);
    *(uint32_t *)(this + 1012) = v5;
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_3F0 + 124))(fld_3F0);
    fld_3F02 = *(uint32_t *)(this + 1008);
    *(uint32_t *)(this + 1016) = v7;
    *(uint32_t *)(this + 1020) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_3F02 + 128))(fld_3F02);
    *(uint8_t *)(this + 985) = 1;
    sub_61D440((uint32_t *)this);
  }
  return CNRDPassiveObject__vmt1F4((int *)this, pArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61D710 sub_61D710
// ------------------------------------------------------------
// 莲花腿辅助（68 行）：sub_431230 ——【推断：抓取参数入表】。
void /*thiscall*/ sub_61D710(uint32_t *this)
{
  int fld_e252; // ecx
  int fld_e2522; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int fld_e2523; // edi
  int v8; // eax
  char v9[4]; // [esp+4h] [ebp-28h] BYREF
  void *Block; // [esp+8h] [ebp-24h]
  int v11; // [esp+Ch] [ebp-20h]
  int v12; // [esp+10h] [ebp-1Ch]
  int v13; // [esp+14h] [ebp-18h] BYREF
  int v14; // [esp+18h] [ebp-14h] BYREF
  uint32_t v15[4]; // [esp+1Ch] [ebp-10h] BYREF

  fld_e252 = *(this + 252);
  if ( fld_e252 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e252 + 604))(fld_e252, 1);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 252) + 612))(*(this + 252), 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 252) + 848))(*(this + 252), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 252) + 112))(
      *(this + 252),
      *(this + 253),
      *(this + 254),
      *(this + 255));
    fld_e2522 = *(this + 252);
    v4 = *this;
    v5 = (*(int (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)fld_e2522 + 124))(fld_e2522, 50, 0, 1);
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e2522 + 120))(fld_e2522, v5);
    (*(void (/*thiscall*/ **)(uint32_t *, int *, uint32_t *, int))(v4 + 140))(this, &v14, v15, v6);
    fld_e2523 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 192))(*(this + 252)) / 2;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) - fld_e2523;
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int))(*(uint32_t *)*(this + 252) + 112))(
      *(this + 252),
      v14,
      v15[0],
      v8 <= 0 ? 0 : v8);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 308))(*(this + 252)) != 0 )
    {
      Block = nullptr;
      v11 = 0;
      v12 = 0;
      v15[3] = 0;
      v13 = 4;
      sub_431230((int)v9, &v13);
      v13 = 0;
      sub_431230((int)v9, &v13);
      v13 = 1;
      sub_431230((int)v9, &v13);
      v13 = 200;
      sub_431230((int)v9, &v13);
      v13 = 200;
      sub_431230((int)v9, &v13);
      (*(void (/*thiscall*/ **)(uint32_t, int, char *, uint32_t, uint32_t))(*(uint32_t *)*(this + 252) + 560))(
        *(this + 252),
        4,
        v9,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 564))(*(this + 252));
      if ( Block != nullptr )
        j__free(Block);
    }
    *(this + 252) = 0;
  }
}



// ------------------------------------------------------------
// 0x61D8C0 sub_61D8C0
// ------------------------------------------------------------
int /*thiscall*/ sub_61D8C0(int this)
{
  sub_61D710((uint32_t *)this);
  *(uint32_t *)(*(uint32_t *)(this + 112) + 24) = dword_9B941C;
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 144));
  return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 8));
}



// ------------------------------------------------------------
// 0x61D900 sub_61D900
// ------------------------------------------------------------
// 抓取收紧辅助（107 行）：字符串证据「TRAP_OCTOPUS_TIGHTEN」（音效 TAG —— 收紧）。
// sub_4926A0 + sub_4E5F70（硬直率掷）+ sub_61D380/61D540/61D8C0 ——
// 捕获后的绞紧状态机（持续伤害【推断】）。
char /*usercall*/ sub_61D900@<al>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int pObj; // ecx
  int v14; // edi
  int v15; // eax
  int v16; // eax
  int v17; // eax
  bool v18; // cc
  float v20; // [esp+8h] [ebp-1Ch] BYREF
  float v21; // [esp+Ch] [ebp-18h]
  float v22; // [esp+10h] [ebp-14h]
  int v23; // [esp+14h] [ebp-10h]
  int v24; // [esp+18h] [ebp-Ch]
  int v25; // [esp+1Ch] [ebp-8h]
  int v26; // [esp+20h] [ebp-4h]

  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
  if ( v3 != 150 )
  {
    v18 = pArg1[251] <= 150;
    if ( (int)pArg1[251] < 150 )
    {
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
      if ( v3 > 150 )
        goto LABEL_17;
      v18 = pArg1[251] <= 150;
    }
    if ( v18 )
      return v3;
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
    if ( v3 >= 150 )
      return v3;
LABEL_17:
    LOBYTE(v3) = sub_61D540(pArg1);
    return v3;
  }
  v3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[252] + 840))(pArg1[252]);
  if ( v3 == 9 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 344))(pArg1, pArg1[139]);
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);
    if ( *(uint8_t *)(v3 + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(
        pArg1,
        "TRAP_OCTOPUS_TIGHTEN",
        -1,
        0,
        0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )
      {
        v4 = *pArg1;
        v20 = 0.0;
        v21 = 0.0;
        v22 = 0.0;
        v23 = 0;
        v24 = 0;
        v25 = 0;
        v26 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 120))(pArg1);
        v5 = *pArg1;
        v20 = (float)v26;
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 124))(pArg1);
        v7 = *pArg1;
        v26 = v6;
        v21 = (float)v6;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 128))(pArg1);
        v9 = pArg1[252];
        v26 = v8;
        v22 = (float)v8;
        sub_4E5F70(nArg2, (int)pArg1, v9, &v20, 1, 1);
      }
      v10 = pArg1[248];
      v11 = pArg1[249] + 1;
      pArg1[249] = v11;
      if ( v11 >= v10 || (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[252] + 724))(pArg1[252]) != 0 )
      {
        LOBYTE(v3) = sub_61D8C0((int)pArg1);
      }
      else
      {
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);
        LOBYTE(v3) = sub_4926A0(v12);
      }
    }
    pObj = pArg1[252];
    if ( pObj != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 604))(pObj, 0);
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[252] + 612))(pArg1[252], 1, 1);
      v14 = *(uint32_t *)pArg1[252];
      v15 = sub_61D380((uint32_t **)pArg1);
      v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v15);
      v17 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v16 - 1);
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t, int))(v14 + 112))(pArg1[252], v17);
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x61DAD0 CNGrabbingLegOfLotus__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNGrabbingLegOfLotus__vmt12C(int this, int nArg2)
{
  CNLegOfLotus__vmt12C((uint32_t *)this, nArg2);
  if ( nArg2 == *(uint32_t *)(this + 1008) )
  {
    sub_61D710((uint32_t *)this);
    *(uint32_t *)(*(uint32_t *)(this + 112) + 24) = dword_9B941C;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 144));
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 8));
    *(uint32_t *)(this + 1008) = 0;
  }
  if ( nArg2 == this && *(uint32_t *)(this + 1008) != 0 )
    sub_61D710((uint32_t *)this);
}



// ------------------------------------------------------------
// 0x61DB50 CNGrabbingLegOfLotus__vmt14C
// ------------------------------------------------------------
// CNGrabbingLegOfLotus 主循环槽（vmt14C）：字符串证据「TRAP_OCTOPUS_SWING」（音效 TAG —— 甩动）+
// sub_61D8C0/61D900 —— 捕获→绞紧→甩动的三段陷阱链（TRAP_OCTOPUS 三 TAG 齐全）。
void /*usercall*/ CNGrabbingLegOfLotus__vmt14C(int pArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // eax

  CNRDPassiveObject__vmt14C(pArg1);
  if ( *(uint8_t *)(pArg1 + 984) == 0 )
  {
    *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 24) = -1002733568;
    *(uint32_t *)(pArg1 + 980) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);
    v3 = *(uint32_t *)pArg1;
    *(uint8_t *)(pArg1 + 984) = 1;
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v3 + 212))(pArg1, "TRAP_OCTOPUS_SWING", -1, 0, 0);
  }
  if ( *(uint32_t *)(pArg1 + 1008) != 0 )
  {
    sub_61D900((uint32_t *)pArg1, nArg2);
  }
  else
  {
    if ( *(float *)(*(uint32_t *)(pArg1 + 112) + 24) < 0.0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1) <= 40 )
      sub_61D8C0(pArg1);
    if ( *(float *)(*(uint32_t *)(pArg1 + 112) + 24) >= 0.0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1) > *(uint32_t *)(pArg1 + 980)
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0
      && *(uint8_t *)(pArg1 + 264) == 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 312))(pArg1, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x61DC20 CNGrabbingLegOfLotus__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNGrabbingLegOfLotus__vmt200(int this, int nArg2, float *pArg3, char pszArg4)
{
  int v5; // eax

  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
  if ( *(uint8_t *)(v5 + 16) != 0 || *(float *)v5 > 0.0 )
  {
    sub_61D710((uint32_t *)this);
    *(uint32_t *)(*(uint32_t *)(this + 112) + 24) = dword_9B941C;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 144));
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 8));
  }
  return CNRDPassiveObject__vmt200((int *)this, nArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61DCA0 CNRisingShuriken__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNRisingShuriken__vmtC(int *this)
{
  int result; // eax

  CNRDPassiveObject__vmtC(this);
  result = *(this + 28);
  *(uint32_t *)(result + 36) = 2000;
  return result;
}



// ------------------------------------------------------------
// 0x61DCC0 CNRisingShuriken__vmt14C
// ------------------------------------------------------------
// CNRisingShuriken 主循环槽（vmt14C，80 行）：sub_423A20（UDP 广播）+ sub_45EBE0（飘字）——
// 升手里剑（RisingShuriken）的升空编排。
char /*usercall*/ CNRisingShuriken__vmt14C@<al>(uint8_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int v3; // eax
  DWORD TickCount; // eax
  int v5; // ebx
  int pObj; // edi
  int v7; // edi
  int v8; // edx
  int v10; // [esp+4h] [ebp-70h]
  int nRand; // [esp+8h] [ebp-6Ch]
  uint8_t v12[68]; // [esp+Ch] [ebp-68h] BYREF
  int v13; // [esp+50h] [ebp-24h]
  int v14; // [esp+61h] [ebp-13h]
  char v15; // [esp+65h] [ebp-Fh]
  int dword_796E502; // [esp+70h] [ebp-4h]

  dword_796E502 = dword_796E50;
  CNRDPassiveObject__vmt14C((int)pArg1);
  v3 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 128))(pArg1);
  if ( v3 >= 500 )
  {
    LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1);
    if ( (uint8_t)v3 != 0 )
    {
      LOBYTE(v3) = pArg1[264];
      if ( (uint8_t)v3 == 0 )
      {
        TickCount = GetTickCount();
        srand(TickCount);
        nRand = 2 * (rand() % 100 < 10) + 1;
        v10 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 120))(pArg1, nArg2);
        v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 124))(pArg1);
        if ( *((int *)pArg1 + 243) > -1 )
        {
          pObj = sub_45EBE0(*((uint32_t **)pArg1 + 29), 273, *((uint32_t *)pArg1 + 243));
          if ( pObj != 0 || (pObj = sub_45EBE0(*((uint32_t **)pArg1 + 29), 529, *((uint32_t *)pArg1 + 243))) != 0 )
          {
            v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
            v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
          }
        }
        if ( nRand > 0 )
        {
          v7 = v10;
          do
          {
            sub_423A20((int)v12);
            sub_423A20((int)v12);
            v8 = *(uint32_t *)pArg1;
            v13 = 2000;
            v14 = 10000;
            v15 = 2;
            v12[12] = 1;
            v12[13] = 1;
            v12[15] = 1;
            (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int, int, int, uint32_t, uint8_t *, int, int, int, uint32_t, uint32_t))(v8 + 584))(
              pArg1,
              v7,
              v5,
              500,
              v7,
              v5,
              30081,
              0,
              v12,
              4,
              100,
              1,
              0,
              0);
            v7 += 35;
            --nRand;
          }
          while ( nRand != 0 );
        }
        LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)pArg1 + 312))(pArg1, 0);
      }
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x61DE30 CNFallingShuriken__vmt200
// ------------------------------------------------------------
// CNFallingShuriken 表现壳槽（vmt200，93 行）：sub_423A20 + dword_796E50 ——
// 落手里剑（FallingShuriken）的状态广播【推断：升/落手里剑的空地联动】。
int /*thiscall*/ CNFallingShuriken__vmt200(int *this, int nArg2, float *pArg3, int nArg4)
{
  int pObj; // ebx
  int v7; // eax
  int v8; // edi
  int nRand; // eax
  int v10; // edx
  int v11; // eax
  int v12; // edx
  int pThis_1; // edi
  int v14; // edi
  int v15; // eax
  int v16; // edi
  int v17; // eax
  uint32_t v19[3]; // [esp+Ch] [ebp-68h] BYREF
  char v20; // [esp+18h] [ebp-5Ch]
  char v21; // [esp+19h] [ebp-5Bh]
  int v22; // [esp+1Bh] [ebp-59h]
  int v23; // [esp+1Fh] [ebp-55h]
  int v24; // [esp+50h] [ebp-24h]
  int v25; // [esp+54h] [ebp-20h]
  int nRand2; // [esp+58h] [ebp-1Ch]
  int v27; // [esp+61h] [ebp-13h]
  char v28; // [esp+65h] [ebp-Fh]
  int dword_796E502; // [esp+70h] [ebp-4h]
  int v30; // [esp+7Ch] [ebp+8h]

  dword_796E502 = dword_796E50;
  v30 = CNRDPassiveObject__vmt200(this, nArg2, pArg3, nArg4);
  if ( nArg2 != 0 )
    pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);
  else
    pObj = 0;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
  if ( pObj == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273) == 0
    || (*(uint8_t (/*thiscall*/ **)(int *))(*this + 88))(this) != 1
    || (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 1 )
  {
    goto LABEL_14;
  }
  sub_423A20((int)v19);
  sub_423A20((int)v19);
  v7 = *(uint32_t *)pObj;
  v24 = 600;
  v27 = 10000;
  v28 = 2;
  v20 = 1;
  v21 = 1;
  v8 = (*(int (/*thiscall*/ **)(int))(v7 + 120))(pObj);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < v8 )
    nRand = 135 - rand() % 20;
  else
    nRand = rand() % 20 + 45;
  v10 = *this;
  v22 = 300;
  v23 = 300;
  v25 = 0;
  nRand2 = nRand;
  nArg4 = (*(int (/*thiscall*/ **)(int *))(v10 + 120))(this);
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v12 = *this;
  pArg3 = (float *)v11;
  pThis_1 = (*(int (/*thiscall*/ **)(int *))(v12 + 128))(this) + 1;
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int, float *, uint32_t))(*this + 136))(this, nArg4, pArg3, 0) != 0
    || (*(uint8_t (/*thiscall*/ **)(int *, int *, float **, int, float *, int, int, int))(*this + 140))(
         this,
         &nArg4,
         &pArg3,
         nArg4,
         pArg3,
         100,
         1,
         1) != 0 )
  {
    v19[1] = pArg3;
    v19[0] = nArg4;
    v19[2] = pThis_1;
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
    v14 = *(uint32_t *)dword_8F8520;
    v15 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
    (*(void (/*thiscall*/ **)(int, int))(v14 + 36))(dword_8F8520, v15);
    v16 = *(uint32_t *)dword_8F8520;
    v17 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
    (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
    (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v19, 98);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
LABEL_14:
    *(uint32_t *)(*(this + 28) + 36) = 0;
  }
  return v30;
}



// ------------------------------------------------------------
// 0x61E040 CNFallingShuriken__vmt14C
// ------------------------------------------------------------
// CNFallingShuriken 主循环槽（vmt14C）：字符串证据「JEWEL_HIT」（音效 TAG —— 宝石命中）+ sub_4939E0 +
// sub_698F90/699000（时钟复位/读数）—— 落手里剑的落点编排。
char /*thiscall*/ CNFallingShuriken__vmt14C(int *this)
{
  int v2; // eax
  int pThis_F4; // eax
  int fld_e30; // ecx
  int fld_e250; // edi

  CNRDPassiveObject__vmt14C((int)this);
  v2 = *this;
  if ( *((uint8_t *)this + 972) != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(v2 + 128))(this) <= 0 )
    {
      fld_e250 = *(this + 250);
      pThis_F4 = sub_699000((int)(this + 244));  // 【clock_now(clk)】
      if ( pThis_F4 >= fld_e250 )
        LOBYTE(pThis_F4) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 84))(this, 0);
    }
    else
    {
      LOBYTE(pThis_F4) = sub_4939E0(*(this + 30), 0);
      *((uint8_t *)this + 972) = 0;
    }
  }
  else
  {
    pThis_F4 = (*(int (/*thiscall*/ **)(int *))(v2 + 128))(this);
    if ( pThis_F4 <= 0 )
    {
      *((uint8_t *)this + 989) = 0;
      *((uint8_t *)this + 990) = 0;
      sub_698F90((int)(this + 244), 2000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      fld_e30 = *(this + 30);
      *((uint8_t *)this + 972) = 1;
      sub_4939E0(fld_e30, 1);
      LOBYTE(pThis_F4) = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                     this,
                     "JEWEL_HIT",
                     -1,
                     0,
                     0);
    }
  }
  return pThis_F4;
}



// ------------------------------------------------------------
// 0x61E0E0 sub_61E0E0
// ------------------------------------------------------------
int /*thiscall*/ sub_61E0E0(uint32_t *this)
{
  uint32_t *fld_e173; // edi
  int result; // eax
  int v4; // eax
  int v5; // [esp-18h] [ebp-20h]
  int v6; // [esp-14h] [ebp-1Ch]
  int v7; // [esp-10h] [ebp-18h]

  fld_e173 = (uint32_t *)*(this + 173);
  if ( fld_e173 == nullptr )
    fld_e173 = this;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    return sub_4E4A50(fld_e173, 30093, 0, v4, v5, v6, v7, 0, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61E150 CNGhoulSkullBomb__vmt14C
// ------------------------------------------------------------
int */*thiscall*/ CNGhoulSkullBomb__vmt14C(uint8_t *this)
{
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this) <= 0 )
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 596))(this, 0);
  if ( *(this + 976) == 1
    && *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 170) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0
    && *(this + 264) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  }
  return CNRDPassiveObject__vmt14C((int)this);
}



// ------------------------------------------------------------
// 0x61E1C0 CNGhoulSkullBomb__vmt144
// ------------------------------------------------------------
// CNGhoulSkullBomb 槽（vmt144）：sub_491690 + sub_4049C0 lerp + sub_699000 ——
// 食尸鬼头骨炸弹（GhoulSkullBomb）的抛物线参数插值。
void /*thiscall*/ CNGhoulSkullBomb__vmt144(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  unsigned int fld_e243; // eax
  unsigned int v7; // eax
  uint64_t v8; // rax

  nullsub_2(nArg2, nArg3, nArg4, nArg5);
  if ( (uint8_t)nArg2 == 0 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) != 0 )
    {
      fld_e243 = sub_699000((int)(this + 9)) - *(this + 243);  // 【clock_now(clk)】
      if ( fld_e243 > 0xBB8 )
      {
        v7 = fld_e243 - 3000;
        if ( v7 >= 0x2BC )
        {
          LOBYTE(v8) = -36;
          *((uint8_t *)this + 976) = 1;
        }
        else
        {
          v8 = (uint64_t)sub_4049C0(100.0, 220.0, v7, 700);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        }
        sub_491690(1, 2, 1, -16776961, ((uint8_t)v8 << 24) | 0xFFFFFF, 1);
      }
    }
    nullsub_2(0, nArg3, nArg4, nArg5);
  }
}



// ------------------------------------------------------------
// 0x61E280 CNGhoulSkullBomb__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNGhoulSkullBomb__vmt12C(uint32_t *this, int nArg2)
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
    sub_61E0E0(this);
}



// ------------------------------------------------------------
// 0x61E2B0 CNGhoulSkull__vmt1E4
// ------------------------------------------------------------
// CNGhoulSkull 状态槽（vmt1E4，35 行，无外部调用）——【推断：头骨滞空/爆散状态折算】。
bool /*thiscall*/ CNGhoulSkull__vmt1E4(void *this, int nArg2)
{
  int pThis_50; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // ebx
  unsigned int v7; // esi
  int pThis_502; // eax
  int v9; // edx
  int pObj; // ecx

  pThis_50 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);
  v4 = *(uint32_t *)(pThis_50 + 120);
  v5 = pThis_50 + 116;
  if ( v4 != 0 )
    v6 = (*(uint32_t *)(v5 + 8) - v4) >> 2;
  else
    v6 = 0;
  v7 = 0;
  if ( v6 <= 0 )
    return IRDCollisionObject__vmt1E4(this, nArg2);
  while ( 1 )
  {
    pThis_502 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);
    v9 = *(uint32_t *)(pThis_502 + 120);
    if ( v9 != 0 && v7 < (*(uint32_t *)(pThis_502 + 124) - v9) >> 2 )
      pObj = *(uint32_t *)(v9 + 4 * v7);
    else
      pObj = 0;
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 818 )
      break;
    if ( (int)++v7 >= v6 )
      return IRDCollisionObject__vmt1E4(this, nArg2);
  }
  return false;
}



// ------------------------------------------------------------
// 0x61E340 CNGhoulSkullSub__vmt14C
// ------------------------------------------------------------
// CNGhoulSkullSub 主循环槽（vmt14C，84 行）：sub_41ACF0 + sub_428F30（发射器）+ sub_4600B0 ——
// 头骨子体的飞散演出（与 0x61C8E0/0x6107E0 同构的子体三兄弟）。
char /*thiscall*/ CNGhoulSkullSub__vmt14C(int **this)
{
  uint32_t *pMem; // edi
  int *v3; // eax
  int fld_e178; // eax
  uint32_t *pMem2; // edi
  int fld_e1782; // eax
  int *v7; // eax
  int **pThis_F3; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  void *fld_e29; // ecx
  bool v14; // zf
  char result; // al
  uint8_t v16[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]
  int v19; // [esp+14h] [ebp-14h]
  void *pMem3; // [esp+18h] [ebp-10h]
  int v21; // [esp+24h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 243) == nullptr && *(this + 244) == nullptr )
  {
    pMem = operator new(0x12Cu);
    pMem3 = pMem;
    v3 = nullptr;
    v21 = 0;
    if ( pMem != nullptr )
    {
      fld_e178 = sub_41ACF0(*(this + 178));
      v3 = sub_428F30(pMem, fld_e178, (int)this);
    }
    *(this + 243) = v3;
    pMem2 = operator new(0x12Cu);
    pMem3 = pMem2;
    v21 = 1;
    if ( pMem2 != nullptr )
    {
      fld_e1782 = sub_41ACF0(*(this + 178) + 1);
      v7 = sub_428F30(pMem2, fld_e1782, (int)this);
    }
    else
    {
      v7 = nullptr;
    }
    v21 = -1;
    *(this + 244) = v7;
    pThis_F3 = this + 243;
    pMem3 = (void *)2;
    do
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(**pThis_F3 + 12))(*pThis_F3, 0);
      v9 = **pThis_F3;
      v10 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
      v11 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v10);
      v12 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v11);
      (*(void (/*thiscall*/ **)(int *, int))(v9 + 40))(*pThis_F3, v12);
      (*(void (/*thiscall*/ **)(int *, uint8_t *))(**pThis_F3 + 92))(*pThis_F3, v16);
      fld_e29 = *(this + 29);
      v21 = 2;
      sub_4600B0(fld_e29, 2, 0, (int)v16);
      v21 = -1;
      if ( Block != nullptr )
        j__free(Block);
      ++pThis_F3;
      v14 = pMem3 == (void *)1;
      Block = nullptr;
      v18 = 0;
      v19 = 0;
      pMem3 = (char *)pMem3 - 1;
    }
    while ( !v14 );
  }
  result = *((uint8_t *)*(this + 30) + 170);
  if ( result != 0 )
  {
    result = *((uint8_t *)this + 264);
    if ( result == 0 )
      return ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61E4C0 sub_61E4C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_61E4C0(uint32_t *this, char pszArg2, int nArg3)
{
  sub_52EA60(this, pszArg2, nArg3);
  *this = &vftbl_CNGhoulSkullSub;
  *(this + 244) = 0;
  *(this + 243) = 0;
  sub_61C860((uint32_t **)this);
  return this;
}



// ------------------------------------------------------------
// 0x61E520 CNGhoulSkullSub__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNGhoulSkullSub__vmt0(void *Block, char pszArg2)
{
  sub_61E550();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x61E550 sub_61E550
// ------------------------------------------------------------
int /*thiscall*/ sub_61E550(int this)
{
  void (/*thiscall*/ ***pThis_3CC)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_3D0)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNGhoulSkullSub;
  pThis_3CC = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 972);
  if ( pThis_3CC != nullptr )
    (**pThis_3CC)(pThis_3CC, 1);
  pThis_3D0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 976);
  *(uint32_t *)(this + 972) = 0;
  if ( pThis_3D0 != nullptr )
    (**pThis_3D0)(pThis_3D0, 1);
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)this = &vftbl_CNThrowItemDestroyable;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x61E5E0 sub_61E5E0
// ------------------------------------------------------------
// 头骨子体演出：字符串证据「PassiveObject/Monster/Ghoul/Animation/SkullSub.ani」+「SKULL_BREAK」
// （音效 TAG —— 碎裂）。sub_44B6C0/44E0D0 + sub_45FE80 —— 头骨碎裂演出（资源路径直证 Ghoul 族）。
char /*thiscall*/ sub_61E5E0(void *this)
{
  char result; // al
  int v3; // eax
  int v4; // ebx
  char *v5; // eax
  char *v6; // edi
  int v7; // ebx
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_78; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( result != 0 )
  {
    result = *((uint8_t *)this + 264);
    if ( result == 0 )
    {
      v3 = sub_42FCB0(228);
      v4 = 0;
      if ( v3 != 0 )
        v4 = sub_431860(v3, "PassiveObject/Monster/Ghoul/Animation/SkullSub.ani", 1);
      v5 = (char *)sub_44B6C0(284);
      v6 = v5;
      if ( v5 != nullptr )
      {
        sub_44E0D0(v5, v4, 1);
        *(uint32_t *)v6 = &vftbl_CNRDPooledObject;
      }
      else
      {
        v6 = nullptr;
      }
      sub_45FE80(*((uint32_t *)this + 29), (int)v6, 2, 0, (int)v6, (int)this, 0);
      v7 = *(uint32_t *)v6;
      pThis_80 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 128))(this);
      pThis_7C = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 124))(this, pThis_80);
      pThis_78 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 120))(this, pThis_7C);
      (*(void (/*thiscall*/ **)(char *, int))(v7 + 112))(v6, pThis_78);
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
      return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "SKULL_BREAK",
               -1,
               0,
               0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61E6F0 CNGhoulSkull__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulSkull__vmt1F4(void *this, uint32_t *uArg2, float *pArg3, char pszArg4)
{
  sub_61E5E0(this);
  return CNRDPassiveObject__vmt1F4((int *)this, uArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61E720 sub_61E720
// ------------------------------------------------------------
// 头骨爆散调度（71 行）：sub_423A20（广播）+ dword_8F82A0/8F8520 + sub_61E5E0 ——
// 爆散子体的分布生成【推断：环形爆散】。
void /*thiscall*/ sub_61E720(int *this)
{
  int v2; // esi
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int pObj2; // esi
  int v7; // eax
  int v8; // edx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  void *fld_e29; // ecx
  void *v14[4]; // [esp+4h] [ebp-8Ch] BYREF
  int pObj; // [esp+14h] [ebp-7Ch]
  bool v16; // [esp+1Bh] [ebp-75h]
  uint32_t v17[26]; // [esp+1Ch] [ebp-74h] BYREF
  int v18; // [esp+8Ch] [ebp-4h]

  v17[25] = dword_796E50;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 88))(this) != 0
    && (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) <= 0 )
  {
    if ( *(this + 243) >= 3 )
      goto LABEL_8;
    sub_423A20((int)v17);
    pObj = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 60))(this) + 104);
    if ( pObj != 0 )
    {
      qmemcpy(v17, (const void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj), 0x62u);
      v17[0] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 24))(pObj);
      v17[1] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj);
      v17[2] = 1;
      *(uint32_t *)((char *)&v17[7] + 3) = (uint64_t)((double)*(uint32_t *)((char *)&v17[7] + 3) * 0.69999999);
      *(uint32_t *)((char *)&v17[8] + 3) = (uint64_t)((double)*(uint32_t *)((char *)&v17[8] + 3) * 0.69999999);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
      v2 = *(uint32_t *)dword_8F8520;
      v3 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
      (*(void (/*thiscall*/ **)(int, int))(v2 + 36))(dword_8F8520, v3);
      v4 = *(uint32_t *)dword_8F8520;
      v5 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
      (*(void (/*thiscall*/ **)(int, int))(v4 + 36))(dword_8F8520, v5);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v17, 98);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
      pObj2 = dword_8F82A0;
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      v8 = *(uint32_t *)pObj2;
      v16 = v7 == 0;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(v8 + 28))(pObj2) + 84) = v7 == 0;
      v9 = *(uint32_t *)pObj2;
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v10);
      v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11);
      (*(void (/*thiscall*/ **)(int, int))(v9 + 40))(pObj2, v12);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj2 + 92))(pObj2, v14);
      fld_e29 = (void *)*(this + 29);
      v18 = 0;
      sub_4600B0(fld_e29, 2, 0, (int)v14);
      v18 = -1;
      sub_5E5260(v14);
    }
    if ( *(this + 243) >= 3 )
LABEL_8:
      sub_61E5E0(this);
    ++*(this + 243);
  }
}



// ------------------------------------------------------------
// 0x61E930 CNGhoulSkull__vmt14C
// ------------------------------------------------------------
int */*thiscall*/ CNGhoulSkull__vmt14C(int *this)
{
  sub_61E720(this);
  return CNRDPassiveObject__vmt14C((int)this);
}



// ------------------------------------------------------------
// 0x61E940 CNGhoulSkull__vmt214
// ------------------------------------------------------------
char /*thiscall*/ CNGhoulSkull__vmt214(int *this, int nArg2, int nArg3, int nArg4)
{
  sub_61E720(this);
  return CNRDPassiveObject__vmt214(this, nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x61E970 CNAraclothoMissile__vmt1F4
// ------------------------------------------------------------
// CNAraclothoMissile 命中表现槽（vmt1F4）：阿拉克洛（Araclotho，蛛网夫人系【推断】）飞弹命中。
int /*thiscall*/ CNAraclothoMissile__vmt1F4(int *this, int nArg2, float *pArg3, char pszArg4)
{
  uint32_t *v4; // ebx
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax

  v4 = (uint32_t *)nArg2;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 273) != 0 )
  {
    v6 = (uint32_t *)__RTDynamicCast(
                     nArg2,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &IRDCharacter `RTTI Type Descriptor',
                     0);
    v7 = v6;
    if ( v6 != nullptr )
    {
      v8 = *v6;
      v9 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 128))(this, 4, 0, 0, 0);
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v9);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v10);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int))(v8 + 580))(v7, 40002, 0, 0, 0, v11);
      v4 = (uint32_t *)nArg2;
    }
  }
  return CNRDPassiveObject__vmt1F4(this, v4, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61EA00 sub_61EA00
// ------------------------------------------------------------
// 阿拉克洛辅助：sub_494F20 + sub_4049C0 lerp + sub_699000 ——【推断：丝线弹道的时间域插值】。
unsigned int /*thiscall*/ sub_61EA00(unsigned int *this)
{
  unsigned int result; // eax
  int v3; // eax
  int fld_e243; // ebx
  int v5; // edi
  float v6; // [esp+4h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( result >= *(this + 253) + 100 )
    {
      result = *(this + 173);
      if ( result != 0 )
      {
        v3 = (*(int (/*thiscall*/ **)(unsigned int *, int))(*this + 116))(this, 1);
        fld_e243 = *(this + 243);
        v5 = v3;
        v6 = sub_4049C0(0.0, 400.0, abs32(fld_e243 - v3), 100);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        if ( fld_e243 >= v5 )
        {
          if ( fld_e243 == v5 )
            v6 = 0.0;
        }
        else
        {
          v6 = v6 * -1.0;
        }
        sub_494F20(1, v6);
        result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
        *(this + 253) = result;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61EAB0 CNAraclothoSpark__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNAraclothoSpark__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  int pObj; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 273) != 0 )
  {
    pObj = __RTDynamicCast(
           (int)pArg2,
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &IRDCharacter `RTTI Type Descriptor',
           0);
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int *, uint32_t))(*(uint32_t *)pObj + 760))(pObj, 6, 1112014848, 8, this, 0);
  }
  return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61EB20 CNAraclothoSpark__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNAraclothoSpark__vmt14C(uint8_t *this)
{
  int pThis_C8; // eax

  CNRDPassiveObject__vmt14C((int)this);
  pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( *(uint8_t *)(pThis_C8 + 170) != 0 )
  {
    LOBYTE(pThis_C8) = *(this + 264);
    if ( (uint8_t)pThis_C8 == 0 )
      LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  }
  return pThis_C8;
}



// ------------------------------------------------------------
// 0x61EB60 CNAraclothoMissile__vmt14C
// ------------------------------------------------------------
// CNAraclothoMissile 主循环槽（vmt14C）：sub_61EA00 + sub_698F90/699000 —— 飞弹推进；溅射见 0x61EC80。
unsigned int /*thiscall*/ CNAraclothoMissile__vmt14C(unsigned int *this)
{
  int fld_e252; // edi
  int v3; // edi
  int v4; // edi
  int fld_e244; // ebx
  int v6; // eax
  unsigned int v7; // edx
  int pObj; // eax
  void *v9; // eax
  int v11; // [esp-10h] [ebp-34h]
  uint8_t v12[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v14; // [esp+10h] [ebp-14h]
  int v15; // [esp+14h] [ebp-10h]
  int v16; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  fld_e252 = *(this + 252);
  if ( sub_699000((int)(this + 246)) >= fld_e252 )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 244) + 12))(*(this + 244));
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 244) + 112))(*(this + 244));
    v3 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this) != 0 ? -24 : 24;
    v4 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 120))(this) + v3;
    fld_e244 = *(uint32_t *)*(this + 244);
    v11 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 128))(this);
    v6 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 124))(this);
    (*(void (/*thiscall*/ **)(uint32_t, int, int))(fld_e244 + 40))(*(this + 244), v4, v6);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 244) + 92))(*(this + 244), v12);
    v7 = *this;
    v16 = 0;
    pObj = (*(int (/*thiscall*/ **)(unsigned int *))(v7 + 684))(this);
    v9 = (void *)(*(int (/*thiscall*/ **)(int, int, uint32_t, uint8_t *))(*(uint32_t *)pObj + 80))(pObj, 2, 0, v12);
    sub_4600B0(v9, v11, 0, 0);
    *((uint8_t *)this + 997) = 0;
    *((uint8_t *)this + 998) = 0;
    sub_698F90((int)(this + 246), 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    v16 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v14 = 0;
    v15 = 0;
  }
  return sub_61EA00(this);
}



// ------------------------------------------------------------
// 0x61EC80 CNAraclothoMissile__vmt2B4
// ------------------------------------------------------------
// CNAraclothoMissile 溅射槽（vmt2B4）：字符串证据「Common/HitEffect/Particle/SmallHitParticle.ptl」——
// 惰性创建小型命中粒子发射器（与 0x60D5A0 IceNiddleGroup 同构的 0x12C 惰性发射器模式）。
void /*thiscall*/ CNAraclothoMissile__vmt2B4(int *this, int nArg2, void *pArg3, int nArg4, int nArg5, int nArg6)
{
  uint32_t *pMem; // eax
  uint32_t *v8; // eax
  void *fld_e29; // ecx
  uint8_t v10[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v12; // [esp+1Ch] [ebp-4h]

  if ( *(this + 170) <= 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  if ( (int)pArg3 > 0 )
  {
    if ( *(this + 245) == 0 )
    {
      pMem = operator new(0x12Cu);
      v12 = 0;
      if ( pMem != nullptr )
        v8 = sub_428F30(pMem, (int)"Common/HitEffect/Particle/SmallHitParticle.ptl", (int)this);
      else
        v8 = nullptr;
      v12 = -1;
      *(this + 245) = (int)v8;
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 245) + 12))(*(this + 245), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 245) + 40))(*(this + 245), nArg4, nArg5, nArg6);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 245) + 92))(*(this + 245), v10);
    fld_e29 = (void *)*(this + 29);
    v12 = 1;
    sub_4600B0(fld_e29, 2, 0, (int)v10);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x61ED80 CNCobWeb__vmt1F4
// ------------------------------------------------------------
// CNCobWeb 命中表现槽（vmt1F4，91 行）：字符串证据「PassiveObject/Monster/Spider/Ani/
// BossSlowWebLand.ani | BossSlowWebEffect.ani」—— Boss 减速蛛网（CobWeb）的双动画。
// sub_44B6C0/44E0D0/44E1F0（帧事件）+ sub_45FE80 —— 蛛网着陆+持续减速场演出（资源路径直证蜘蛛族）。
int /*thiscall*/ CNCobWeb__vmt1F4(int *this, int nArg2, float *pArg3, char pszArg4)
{
  uint32_t *v4; // ebx
  int v6; // eax
  char *v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int pObj; // eax
  int v15; // eax
  int v16; // edi
  char *v17; // eax
  char *v18; // edi
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // ebx
  int v23; // eax
  int v25; // [esp+Ch] [ebp-10h]
  int v26; // [esp+Ch] [ebp-10h]

  v4 = (uint32_t *)nArg2;
  if ( *((uint8_t *)this + 264) == 0 )
  {
    v6 = sub_42FCB0(228);
    if ( v6 != 0 )
      v25 = sub_431860(v6, "PassiveObject/Monster/Spider/Ani/BossSlowWebLand.ani", 1);
    else
      v25 = 0;
    if ( v25 != 0 )
    {
      v7 = (char *)sub_44B6C0(284);
      if ( v7 != nullptr )
      {
        sub_44E0D0(v7, v25, 1);
        *(uint32_t *)v7 = &vftbl_CNRDPooledObject;
      }
      else
      {
        v7 = nullptr;
      }
      sub_45FE80(*(this + 29), (int)v7, 2, 0, (int)v7, (int)this, 0);
      v8 = *(uint32_t *)v7;
      v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v9);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v10);
      (*(void (/*thiscall*/ **)(char *, int))(v8 + 112))(v7, v11);
      v12 = *(uint32_t *)v7;
      v13 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      (*(void (/*thiscall*/ **)(char *, int))(v12 + 144))(v7, v13);
      v4 = (uint32_t *)nArg2;
    }
    if ( rand() % 100 < 50 && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v4 + 40))(v4, 273) != 0 )
    {
      pObj = __RTDynamicCast(
              (int)v4,
              0,
              &IRDCollisionObject `RTTI Type Descriptor',
              &IRDCharacter `RTTI Type Descriptor',
              0);
      if ( pObj != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)pObj + 764))(pObj, 16, 1, 0, 0);
        v15 = sub_42FCB0(228);
        v16 = v15 != 0 ? sub_431860(v15, "PassiveObject/Monster/Spider/Ani/BossSlowWebEffect.ani", 1) : 0;
        if ( v25 != 0 )
        {
          v17 = (char *)sub_44B6C0(284);
          if ( v17 != nullptr )
            v18 = sub_44E1F0(v17, v16, 1);
          else
            v18 = nullptr;
          sub_45FE80(*(this + 29), (int)v18, 2, 0, (int)v18, (int)v4, 0);
          v26 = *(uint32_t *)v18;
          v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 128))(v4);
          v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 124))(nArg2, v19);
          v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v20);
          (*(void (/*thiscall*/ **)(char *, int))(v26 + 112))(v18, v21);
          v22 = *(uint32_t *)v18;
          v23 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
          (*(void (/*thiscall*/ **)(char *, int))(v22 + 144))(v18, v23);
          v4 = (uint32_t *)nArg2;
        }
      }
    }
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  return CNRDPassiveObject__vmt1F4(this, v4, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61EFD0 sub_61EFD0
// ------------------------------------------------------------
int /*thiscall*/ sub_61EFD0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e243)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e244)(uint32_t, int); // ecx

  fld_e243 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 243);
  if ( fld_e243 != nullptr )
    result = (**fld_e243)(fld_e243, 1);
  fld_e244 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 244);
  *(this + 243) = 0;
  if ( fld_e244 != nullptr )
    result = (**fld_e244)(fld_e244, 1);
  *(this + 244) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x61F010 CNSpectressBat__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNSpectressBat__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)
{
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 273) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int *, uint32_t))(*pArg2 + 760))(pArg2, 5, 1103626240, 5, this, 0);
  return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61F060 CNSpectressBat__vmt12C
// ------------------------------------------------------------
// CNSpectressBat 消亡联动槽（vmt12C）：sub_4600B0 —— 幽魂蝙蝠（SpectressBat）消散演出。
void /*thiscall*/ CNSpectressBat__vmt12C(uint32_t *this, int nArg2)
{
  int fld_e244; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *fld_e29; // ecx
  bool v8; // zf
  uint8_t v9[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v11; // [esp+Ch] [ebp-18h]
  int v12; // [esp+10h] [ebp-14h]
  int v13; // [esp+14h] [ebp-10h]
  int v14; // [esp+20h] [ebp-4h]

  if ( this == (uint32_t *)nArg2 )
  {
    v13 = 3;
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 244) + 12))(*(this + 244), 0);
      fld_e244 = *(uint32_t *)*(this + 244);
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v4);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);
      (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e244 + 40))(*(this + 244), v6);
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 244) + 92))(*(this + 244), v9);
      fld_e29 = (void *)*(this + 29);
      v14 = 0;
      sub_4600B0(fld_e29, 2, 0, (int)v9);
      v14 = -1;
      if ( Block != nullptr )
        j__free(Block);
      v8 = v13 == 1;
      Block = nullptr;
      v11 = 0;
      v12 = 0;
      --v13;
    }
    while ( !v8 );
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 20202);
  }
  CNRDPassiveObject__vmt12C(this, nArg2);
}



// ------------------------------------------------------------
// 0x61F150 CNSpectressBat__vmt14C
// ------------------------------------------------------------
// CNSpectressBat 主循环槽（vmt14C）：sub_4600B0 + sub_698F90/699000 —— 蝙蝠群飞行推进。
int */*thiscall*/ CNSpectressBat__vmt14C(int *this)
{
  int fld_e251; // ebx
  int pThis_F5; // edi
  int fld_e243; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  void *fld_e29; // ecx
  uint8_t v10[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v12; // [esp+14h] [ebp-14h]
  int v13; // [esp+18h] [ebp-10h]
  int v14; // [esp+24h] [ebp-4h]

  fld_e251 = *(this + 251);
  pThis_F5 = (int)(this + 245);
  if ( sub_699000((int)(this + 245)) >= fld_e251 )  // 【clock_now(clk)】
  {
    *(uint8_t *)(pThis_F5 + 13) = 0;
    *(uint8_t *)(pThis_F5 + 14) = 0;
    sub_698F90(pThis_F5, 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 243) + 12))(*(this + 243), 0);
    fld_e243 = *(uint32_t *)*(this + 243);
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v5);
    v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v6);
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e243 + 40))(*(this + 243), v7);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 243) + 104))(*(this + 243), *(this + 252));
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v10);
    fld_e29 = (void *)*(this + 29);
    v14 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v10);
    v14 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v12 = 0;
    v13 = 0;
  }
  return CNRDPassiveObject__vmt14C((int)this);
}



// ------------------------------------------------------------
// 0x61F240 sub_61F240
// ------------------------------------------------------------
// 蝙蝠粒子：字符串证据「PassiveObject/Monster/Wraith/Particle/FlyBat.ptl | FlyBatParticle.ptl」+
// 「BAT_FLAP」（音效 TAG —— 振翅）。sub_428F30 + sub_698F90 —— 蝙蝠群粒子（资源路径直证 Wraith 族）。
int /*thiscall*/ sub_61F240(uint32_t *this)
{
  int pThis_F5; // ecx
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  uint32_t *pMem2; // eax
  uint32_t *v6; // eax

  pThis_F5 = (int)(this + 245);
  *(uint8_t *)(pThis_F5 + 13) = 0;
  *(uint8_t *)(pThis_F5 + 14) = 0;
  sub_698F90(pThis_F5, 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    v4 = sub_428F30(pMem, (int)"PassiveObject/Monster/Wraith/Particle/FlyBat.ptl", 0);
  else
    v4 = nullptr;
  *(this + 243) = v4;
  pMem2 = operator new(0x12Cu);
  if ( pMem2 != nullptr )
    v6 = sub_428F30(pMem2, (int)"PassiveObject/Monster/Wraith/Particle/FlyBatParticle.ptl", 0);
  else
    v6 = nullptr;
  *(this + 244) = v6;
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
           this,
           "BAT_FLAP",
           20202,
           0,
           0);
}



// ------------------------------------------------------------
// 0x61F310 CNLOLLaser__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNLOLLaser__vmt1F4(int *this, uint32_t *uArg2, float *pArg3, char pszArg4)
{
  *((uint8_t *)this + 980) = 1;
  return CNRDPassiveObject__vmt1F4(this, uArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61F320 CNEvilEyeMissile__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNEvilEyeMissile__vmt1F4(int *this, uint32_t *uArg2, float *pArg3, char pszArg4)
{
  if ( pszArg4 == 0 )
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SHAKE_WAVE", -1, 0, 0);
  return CNRDPassiveObject__vmt1F4(this, uArg2, pArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x61F360 CNEvilEyeLOLLaser__vmt2C4
// ------------------------------------------------------------
// CNEvilEyeLOLLaser tick 槽（vmt2C4）：sub_4926A0/699000 —— 邪眼（EvilEye）激光的持续照射推进
// （STONE_LASER_FIRE TAG 见 0x61F410）。
int /*thiscall*/ CNEvilEyeLOLLaser__vmt2C4(void *this, int nArg2)
{
  int nArg22; // ebx
  int v4; // edi
  int pThis_24; // eax
  uint32_t *v6; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    0,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  nArg22 = nArg2;
  if ( nArg2 > 0 )
  {
    v4 = 0;
    do
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        0,
        *(uint32_t *)(*((uint32_t *)this + 36) + 4),
        v4,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        0,
        *(uint32_t *)(*((uint32_t *)this + 36) + 8),
        v4,
        0,
        0,
        0);
      v4 += 100;
      --nArg22;
    }
    while ( nArg22 != 0 );
  }
  sub_4926A0(*((uint32_t *)this + 30));
  pThis_24 = sub_699000((int)this + 36);  // 【clock_now(clk)】
  v6 = *(uint32_t **)this;
  *((uint32_t *)this + 243) = pThis_24;
  *((uint8_t *)this + 980) = 0;
  result = **(uint32_t **)(((int (/*thiscall*/ *)(void *))v6[85])(this) + 64);
  *((uint32_t *)this + 244) = result;
  return result;
}



// ------------------------------------------------------------
// 0x61F410 CNEvilEyeSmallLaser__vmt14C
// ------------------------------------------------------------
// CNEvilEyeSmallLaser 主循环槽（vmt14C）：字符串证据「STONE_LASER_FIRE」（音效 TAG —— 石像激光）——
// 邪眼小激光的照射推进。
int */*thiscall*/ CNEvilEyeSmallLaser__vmt14C(uint32_t *this)
{
  uint32_t *fld_e36; // edi
  int v3; // eax
  int v4; // edx

  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0 )
  {
    fld_e36 = (uint32_t *)*(this + 36);
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
    v4 = *this;
    if ( v3 == *fld_e36 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 84))(this, 0);
    else
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 196))(this, *(uint32_t *)*(this + 36));
  }
  if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) >= 3 && *((uint8_t *)this + 972) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
      this,
      30304,
      10,
      0,
      0,
      0,
      0,
      0,
      1,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "STONE_LASER_FIRE",
      -1,
      0,
      0);
    *((uint8_t *)this + 972) = 1;
  }
  return CNRDPassiveObject__vmt14C((int)this);
}



// ------------------------------------------------------------
// 0x61F4C0 sub_61F4C0
// ------------------------------------------------------------
// 邪眼辅助（51 行）：sub_4926A0 + sub_699000 ——【推断：激光扫描计时】。
int /*thiscall*/ sub_61F4C0(void *this, int nArg2)
{
  int nArg22; // ebx
  int v4; // edi
  int pThis_24; // eax
  uint32_t *v6; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    0,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  nArg22 = nArg2;
  if ( nArg2 > 0 )
  {
    v4 = 0;
    do
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        0,
        *(uint32_t *)(*((uint32_t *)this + 36) + 4),
        0,
        v4,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        0,
        *(uint32_t *)(*((uint32_t *)this + 36) + 8),
        0,
        v4,
        0,
        0);
      v4 -= 30;
      --nArg22;
    }
    while ( nArg22 != 0 );
  }
  sub_4926A0(*((uint32_t *)this + 30));
  pThis_24 = sub_699000((int)this + 36);  // 【clock_now(clk)】
  v6 = *(uint32_t **)this;
  *((uint32_t *)this + 243) = pThis_24;
  *((uint8_t *)this + 980) = 0;
  result = **(uint32_t **)(((int (/*thiscall*/ *)(void *))v6[85])(this) + 64);
  *((uint32_t *)this + 244) = result;
  return result;
}



// ------------------------------------------------------------
// 0x61F570 sub_61F570
// ------------------------------------------------------------
int /*thiscall*/ sub_61F570(uint32_t **this)
{
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 36));
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 36))[1]);
  return ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 36))[2]);
}



// ------------------------------------------------------------
// 0x61F5C0 CNEvilEyeQuake__vmt14C
// ------------------------------------------------------------
// CNEvilEyeQuake 主循环槽（vmt14C）：sub_4600B0 + sub_699000 —— 邪眼震地（EvilEyeQuake，
// Vib_dust/Vib_rock 粒子见 0x61F830 区）的推进。
void /*thiscall*/ CNEvilEyeQuake__vmt14C(uint32_t **this)
{
  int fld_e243; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // eax
  void *fld_e29; // ecx
  int fld_e244; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  void *fld_e292; // ecx
  uint8_t v12[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *v13; // [esp+Ch] [ebp-28h]
  uint8_t v14[4]; // [esp+18h] [ebp-1Ch] BYREF
  void *Block; // [esp+1Ch] [ebp-18h]
  int v16; // [esp+20h] [ebp-14h]
  int v17; // [esp+24h] [ebp-10h]
  int v18; // [esp+30h] [ebp-4h]

  if ( *(uint8_t *)(((int (/*thiscall*/ *)(uint32_t **))(*this)[50])(this) + 170) != 0 )
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[21])(this, 0);
  if ( (unsigned int)(sub_699000((int)(this + 9)) - (uint32_t)*(this + 245)) >= 0x3C )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 243) + 12))(*(this + 243), 0);
    fld_e243 = **(this + 243);
    v3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
    v4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v3);
    v5 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v4);
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e243 + 40))(*(this + 243), v5);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 243) + 92))(*(this + 243), v12);
    fld_e29 = *(this + 29);
    v18 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v12);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 244) + 12))(*(this + 244), 0);
    fld_e244 = **(this + 244);
    v8 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
    v9 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v8);
    v10 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v9);
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e244 + 40))(*(this + 244), v10);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 244) + 92))(*(this + 244), v14);
    fld_e292 = *(this + 29);
    LOBYTE(v18) = 1;
    sub_4600B0(fld_e292, 2, 0, (int)v14);
    *(this + 245) = (uint32_t *)sub_699000((int)(this + 9));
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v16 = 0;
    v17 = 0;
    if ( v13 != nullptr )
      j__free(v13);
  }
}



// ------------------------------------------------------------
// 0x61F720 sub_61F720
// ------------------------------------------------------------
int /*thiscall*/ sub_61F720(uint32_t *this)
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax
  int result; // eax

  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    v3 = sub_428F30(pMem, (int)"PassiveObject/Monster/EvilEye/Particle/Vib_dust.ptl", (int)this);
  else
    v3 = nullptr;
  *(this + 243) = v3;
  pMem2 = operator new(0x12Cu);
  if ( pMem2 != nullptr )
    v5 = sub_428F30(pMem2, (int)"PassiveObject/Monster/EvilEye/Particle/Vib_rock.ptl", (int)this);
  else
    v5 = nullptr;
  *(this + 244) = v5;
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  *(this + 245) = result;
  return result;
}



// ------------------------------------------------------------
// 0x61F7D0 sub_61F7D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_61F7D0(uint32_t *this, char pszArg2, int nArg3)
{
  sub_52EA60(this, pszArg2, nArg3);
  *this = &vftbl_CNEvilEyeLOLLaser;
  sub_5FF8E0((int)this);
  CNEvilEyeLOLLaser__vmt2C4(this, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x61F830 sub_61F830
// ------------------------------------------------------------
int /*thiscall*/ sub_61F830(void ***this)
{
  *this = (void **)&vftbl_CNEvilEyeLOLLaser;
  CNRDObject__vmtD0(this, **(this + 36));
  ((void (/*thiscall*/ *)(void ***, void *))(*this)[52])(this, (*(this + 36))[1]);
  ((void (/*thiscall*/ *)(void ***, void *))(*this)[52])(this, (*(this + 36))[2]);
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x61F8B0 sub_61F8B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_61F8B0(uint32_t *this, char pszArg2, int nArg3)
{
  sub_52EA60(this, pszArg2, nArg3);
  *this = &vftbl_CNEvilEyeMissile;
  sub_5FF8E0((int)this);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -1,
    *(uint32_t *)(*(this + 36) + 4),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    1,
    *(uint32_t *)*(this + 36),
    0,
    0,
    0,
    0);
  return this;
}



// ------------------------------------------------------------
// 0x61F950 CNEvilEyeMissile__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNEvilEyeMissile__vmt0(void *Block, char pszArg2)
{
  sub_61F980();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x61F980 sub_61F980
// ------------------------------------------------------------
int /*thiscall*/ sub_61F980(void ***this)
{
  *this = (void **)&vftbl_CNEvilEyeMissile;
  CNRDObject__vmtD0(this, **(this + 36));
  ((void (/*thiscall*/ *)(void ***, void *))(*this)[52])(this, (*(this + 36))[1]);
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x61F9F0 sub_61F9F0
// ------------------------------------------------------------
int /*thiscall*/ sub_61F9F0(int this, char pszArg2, int nArg3)
{
  int fld_90; // eax

  sub_52EA60((uint32_t *)this, pszArg2, nArg3);
  fld_90 = *(uint32_t *)(this + 144);
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)this = &vftbl_CNEvilEyeSmallLaser;
  CNRDObject__vmtCC((unsigned int *)this, 0, *(uint32_t *)(fld_90 + 4), 0, 0, 0, 0);
  return this;
}



// ------------------------------------------------------------
// 0x61FA60 sub_61FA60
// ------------------------------------------------------------
int /*thiscall*/ sub_61FA60(void ***this)
{
  *this = (void **)&vftbl_CNEvilEyeSmallLaser;
  CNRDObject__vmtD0(this, **(this + 36));
  ((void (/*thiscall*/ *)(void ***, void *))(*this)[52])(this, (*(this + 36))[1]);
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x61FAD0 sub_61FAD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_61FAD0(uint32_t *this, char pszArg2, int nArg3)
{
  sub_52EA60(this, pszArg2, nArg3);
  *this = &vftbl_CNEvilEyeQuake;
  sub_5FF8E0((int)this);
  sub_61F720(this);
  return this;
}



// ------------------------------------------------------------
// 0x61FB30 CNEvilEyeQuake__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNEvilEyeQuake__vmt0(void *Block, char pszArg2)
{
  sub_61FB60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x61FB60 sub_61FB60
// ------------------------------------------------------------
int /*thiscall*/ sub_61FB60(int this)
{
  void (/*thiscall*/ ***pThis_3CC)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_3D0)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNEvilEyeQuake;
  pThis_3CC = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 972);
  if ( pThis_3CC != nullptr )
    (**pThis_3CC)(pThis_3CC, 1);
  pThis_3D0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 976);
  *(uint32_t *)(this + 972) = 0;
  if ( pThis_3D0 != nullptr )
    (**pThis_3D0)(pThis_3D0, 1);
  *(uint32_t *)(this + 976) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x61FBE0 CNEvilEyeLOLLaser__vmt0
// ------------------------------------------------------------
void ***/*thiscall*/ CNEvilEyeLOLLaser__vmt0(void ***Block, char pszArg2)
{
  sub_61F830(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x61FC10 CNEvilEyeSmallLaser__vmt0
// ------------------------------------------------------------
void ***/*thiscall*/ CNEvilEyeSmallLaser__vmt0(void ***Block, char pszArg2)
{
  sub_61FA60(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x61FC40 sub_61FC40
// ------------------------------------------------------------
int /*thiscall*/ sub_61FC40(int this)
{
  *(uint32_t *)(this + 96) = 545;
  *(uint8_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint8_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 1004) = 4;
  return 0;
}



// ------------------------------------------------------------
// 0x61FC70 CNMineTrap__vmt288
// ------------------------------------------------------------
int /*thiscall*/ CNMineTrap__vmt288(int this, uint32_t *uArg2, int nArg3)
{
  if ( *(uint8_t *)(this + 1000) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 20) != *(uint32_t *)(this + 1004) )
  {
    return 3;
  }
  *uArg2 = 100;
  return 0;
}



// ------------------------------------------------------------
// 0x61FCB0 CNMineTrap__vmtC
// ------------------------------------------------------------
// CNMineTrap 生成槽（vmtC）：sub_4049C0 lerp + dword_8F8520 —— 地雷陷阱（MineTrap）的布雷初值。
int /*thiscall*/ CNMineTrap__vmtC(int this)
{
  int *fld_15C; // eax
  int v3; // eax
  double v4; // st7
  int v5; // edx
  float v7; // [esp+0h] [ebp-20h]
  float v8; // [esp+4h] [ebp-1Ch]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  CNRDPassiveObject__vmtC((int *)this);
  if ( *(uint32_t *)(this + 116) != 0 )
  {
    fld_15C = *(int **)(this + 348);
    v9 = *fld_15C;
    v10 = fld_15C[1];
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    v8 = (float)v10;
    v7 = (float)v9;
    v4 = sub_4049C0(v7, v8, *(uint32_t *)(*(uint32_t *)(v3 + 108) + 112) - 1, 98);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v5 = *(uint32_t *)this;
    *(float *)(this + 724) = v4;
    (*(void (/*thiscall*/ **)(int, int))(v5 + 344))(this, this + 724);
  }
  return (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 2, 0, 1, 1);
}



// ------------------------------------------------------------
// 0x61FD30 CNMineTrap__vmt14C
// ------------------------------------------------------------
// CNMineTrap 主循环槽（vmt14C，76 行）：sub_699000 —— 地雷待机/触发推进【推断：踩踏检测计时】。
int /*thiscall*/ CNMineTrap__vmt14C(int *this)
{
  int result; // eax
  int fld_e29; // eax
  int v4; // ecx
  unsigned int v5; // edi
  int fld_e292; // ecx
  int v7; // edx
  int pObj; // esi
  uint32_t *v9; // eax
  uint8_t (/*thiscall*/ **fld_e243)(char *, uint32_t); // [esp+4h] [ebp-Ch]
  unsigned int v11; // [esp+8h] [ebp-8h]
  int v12; // [esp+Ch] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    if ( *((uint8_t *)this + 992) != 0 )
    {
      result = *(this + 30);
      if ( result != 0 && *(uint8_t *)(result + 170) != 0 )
        return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 2, 0, 2, 0);
    }
    else
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( result >= *(this + 249) )
      {
        fld_e29 = *(this + 29);
        v4 = *(uint32_t *)(fld_e29 + 120);
        result = fld_e29 + 116;
        v5 = 0;
        if ( v4 != 0 )
        {
          result = (*(uint32_t *)(result + 8) - v4) >> 2;
          v12 = result;
        }
        else
        {
          v12 = 0;
        }
        v11 = 0;
        if ( v12 > 0 )
        {
          do
          {
            fld_e292 = *(this + 29);
            v7 = *(uint32_t *)(fld_e292 + 120);
            if ( v7 != 0 && v5 < (*(uint32_t *)(fld_e292 + 124) - v7) >> 2 )
              pObj = *(uint32_t *)(v7 + 4 * v5);
            else
              pObj = 0;
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )
            {
              fld_e243 = (uint8_t (/*thiscall*/ **)(char *, uint32_t))*(this + 243);
              v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj);
              if ( (*fld_e243)((char *)this + 972, *v9) == 0
                && ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 428))(pObj) != 0
                 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 432))(pObj) != 0)
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) == 0
                && (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 488))(this, pObj) != 0 )
              {
                return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 3, 0, 2, 0);
              }
              v5 = v11;
            }
            result = v12;
            v11 = ++v5;
          }
          while ( (int)v5 < v12 );
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61FEA0 CNMineTrap__vmt1D8
// ------------------------------------------------------------
// CNMineTrap 受击表现槽（vmt1D8）：sub_4926A0/699000 —— 地雷被触发时的引爆链启动【推断】。
int /*userpurge*/ CNMineTrap__vmt1D8@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3, int nArg4, int nArg5, int nArg6)
{
  uint32_t *v7; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // edi
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // edi
  int v15; // ecx
  int v17; // [esp-4h] [ebp-Ch]

  CNRDPassiveObject__vmt1D8(pDwArg1, nArg2, nArg3, nArg3, nArg4, nArg5, nArg6);
  if ( nArg3 == 2 )
  {
    v12 = *pDwArg1;
    v17 = pDwArg1[34];
    *((uint8_t *)pDwArg1 + 992) = 0;
    (*(void (/*thiscall*/ **)(int *, int))(v12 + 196))(pDwArg1, v17);
    v13 = pDwArg1[87];
    if ( v13 != 0 && (unsigned int)((pDwArg1[88] - v13) >> 2) > 2 )
      v14 = *(uint32_t *)(v13 + 8);
    else
      v14 = 0;
    pDwArg1[249] = v14 + sub_699000((int)(pDwArg1 + 9));  // 【clock_now(clk)】
  }
  else if ( nArg3 == 3 )
  {
    v7 = (uint32_t *)pDwArg1[36];
    v8 = *pDwArg1;
    *((uint8_t *)pDwArg1 + 992) = 1;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v8 + 196))(pDwArg1, *v7);
    v9 = pDwArg1[178];
    if ( v9 != 0 && (pDwArg1[179] - v9) >> 2 != 0 )
    {
      v10 = *pDwArg1;
      v11 = sub_41ACF0(v9);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v10 + 212))(pDwArg1, v11, -1, 0, 0);
    }
  }
  v15 = pDwArg1[30];
  if ( v15 != 0 )
    sub_4926A0(v15);
  return (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 352))(pDwArg1);
}



// ------------------------------------------------------------
// 0x61FF90 CNMineTrap__vmt200
// ------------------------------------------------------------
// CNMineTrap 表现壳槽（vmt200）：sub_4049C0 + sub_41ACF0 —— 地雷的伪装/显形表现【推断】。
int /*thiscall*/ CNMineTrap__vmt200(int *this, int nArg2, float *pArg3, char pszArg4)
{
  int fld_e178; // ecx
  int v6; // edi
  int v7; // eax
  int fld_e87; // ecx
  uint64_t fld_e29; // rax
  float v11; // [esp+10h] [ebp-1Ch]
  float fld_e872; // [esp+14h] [ebp-18h]

  fld_e178 = *(this + 178);
  if ( fld_e178 != 0 && (unsigned int)((*(this + 179) - fld_e178) >> 2) > 1 )
  {
    v6 = *this;
    v7 = sub_41ACF0(fld_e178 + 4);
    (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v6 + 212))(this, v7, -1, 0, 0);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    fld_e87 = *(this + 87);
    if ( fld_e87 != 0 && (unsigned int)((*(this + 88) - fld_e87) >> 2) > 4 && *(uint32_t *)(fld_e87 + 16) != -1 )
    {
      fld_e872 = (float)*(int *)(*(this + 87) + 24);
      v11 = (float)*(int *)(fld_e87 + 20);
      fld_e29 = (uint64_t)sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
                               v11,
                               fld_e872,
                               *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 108) + 112) - 1,
                               98);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        *(uint32_t *)(*(this + 87) + 16),
        fld_e29,
        0,
        0,
        0,
        0,
        0,
        4,
        0,
        0,
        0);
    }
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  return CNRDPassiveObject__vmt200(this, nArg2, pArg3, pszArg4);
}


