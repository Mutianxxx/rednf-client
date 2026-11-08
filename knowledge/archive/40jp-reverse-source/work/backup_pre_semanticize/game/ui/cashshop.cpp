// ============================================================
// 【40JP逆向源代码工程】ui/cashshop.cpp
// 模块: 0x55-0x56 区块 —— 商城/任务/NPC/频道/社区/选项/弹窗析构表
// 来源: work/dump_uilogin.txt  区块: 0x550000-0x570000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 518
// ------------------------------------------------------------
// ★ 全文件最重要的结构性发现 —— IRDPopupWindow 弹窗基类与"vmt4 析构三件套"
//   注册表（0x554320-0x55B070）：
//     0x554320-0x554970 = IRDPopupWindow 基类虚方法（vmt18/vmt34/vmt1C/vmt0/
//     vmt2C：位置/尺寸/文案/事件统一实现）；
//     0x5544E0-0x55A010 = 每个窗口类一组"vmt4 删除析构 + 数据清理 + 关闭回调"
//     三件套（与 window_party.cpp 0x63 区块的各窗口 vmt 实现一一配对）；
//     0x55B070（408 行）= 全部弹窗关闭回调的集中装配表（程序初始化时调用）。
// ------------------------------------------------------------
// ★ 资源/协议证据：
//   CNRDCashShop 商城主类（0x55E700）+ CNRDCashShopBuyWindow（aura_create.cpp
//   0x648770）；Etc/NewCashShop.etc（新版商城配置 0x560D10，778 行）；
//   interface/cashshop/cashshopdoubleevent.img（双倍活动 0x55DA50）；
//   SERA_SHOP 赛丽亚商店（0x560610）/SELECT_CHARACTER 事件；
//   CNRDItemShopWindow 道具商店（DISSOLVE_ITEM）/CNRDItemProductWindow 商品橱窗
//   （WRITE_CHAR_LOOP 打字机）；CNRDSkillBuyWindow 技能购买（RECIPE_NOTICE）；
//   CNRDQuestInfoWindow/CNRDQuestListWindow 任务（LETTER_FADE_IN/WRITE_CHAR_LOOP、
//   MOUSE_OVER）；CNRDNpc 头顶任务标记（Common/Etc/NpcQuest.img）；
//   0x569F40 频道信息装载 Etc/channel_info.etc（日志 "importChannelScript -
//   can't find channel_info.etc"——[dungeon]/[server] 段解析）；
//   CNRDOptionWindow 设置、CNRDCommunityWindow 社区、CNRDTutorialWindow 教程。
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】PVP 结算联动与技能购买窗（0x550020-0x550420）
// 结算入队 0x550020（→trade_shop 0x54FFB0）；结算应用 0x5500B0（108 行）；
// 结果应用（108 行）；0x550300=PVP 结果数据。
// ============================================================
// ------------------------------------------------------------
// 0x550020 sub_550020 —— PVP 结算入队转发：按对象槽 8052 过滤后 54FFB0 入队（遍历 48F690 对象池 8 槽）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_550020(void *this, int a2, int a3)
{
  int v4; // esi
  unsigned int result; // eax
  int v6; // edx
  uint32_t Block[4]; // [esp+Ch] [ebp-10h] BYREF

  v4 = 0;
  while ( 1 )
  {
    result = sub_48F690(v4);
    if ( result != 0 && *(uint16_t *)(result + 4) == a2 && *(uint32_t *)(result + 196) != 0 )
      break;
    if ( ++v4 >= 8 )
      return result;
  }
  result = *(uint32_t *)(result + 196);
  if ( *(uint8_t *)(result + 8052) == 0 )
  {
    Block[1] = a3;
    v6 = *(uint32_t *)result;
    Block[0] = a2;
    Block[2] = v4;
    Block[3] = (*(int (/*thiscall*/ **)(unsigned int))(v6 + 376))(result);
    return sub_54FFB0((int)this + 152, Block);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5500B0 sub_5500B0 —— PVP 结算结果应用（48F690 对象 + 4BF340/54F610/54FE50，108 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_5500B0(uint32_t *this, int a2)
{
  int v3; // eax
  char *v4; // esi
  int v5; // ecx
  uint8_t *v6; // edi
  unsigned int v7; // ebx
  uint32_t *v8; // edx
  int v9; // ecx
  uint32_t *v10; // edx
  unsigned int v11; // ebx
  int v12; // ecx
  int v13; // edx
  int v14; // edx
  char v15[4]; // [esp+Ch] [ebp-20h] BYREF
  uint8_t *v16; // [esp+10h] [ebp-1Ch]
  char *v17; // [esp+14h] [ebp-18h]
  int v18; // [esp+18h] [ebp-14h]
  uint32_t *v19; // [esp+1Ch] [ebp-10h]
  int v20; // [esp+28h] [ebp-4h]
  int v21; // [esp+34h] [ebp+8h]
  int v22; // [esp+34h] [ebp+8h]

  v19 = this;
  v3 = sub_48F690(a2);
  v4 = nullptr;
  if ( v3 != 0 )
    v5 = *(uint32_t *)(v3 + 196);
  else
    v5 = 0;
  if ( v3 != 0 && v5 != 0 )
  {
    *(this + 33) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 376))(v5);
    v4 = nullptr;
  }
  v6 = nullptr;
  v16 = nullptr;
  v17 = nullptr;
  v18 = 0;
  v20 = 0;
  v7 = 0;
  v21 = 0;
  while ( 1 )
  {
    v8 = v19;
    v9 = v19[39];
    if ( v9 == 0 || v7 >= (v19[40] - v9) >> 4 )
      break;
    v10 = (uint32_t *)(v9 + v21);
    if ( *(uint32_t *)(v9 + v21 + 12) != v19[33] )
      goto LABEL_15;
    if ( v6 != nullptr && (v4 - v6) >> 4 < (unsigned int)((v18 - (int)v6) >> 4) )
    {
      sub_4BF340(v4, 1, v10);
      v4 += 16;
      ++v7;
      v17 = v4;
      v21 += 16;
    }
    else
    {
      sub_54F610((int)v15, v4, 1u, v10);
      v4 = v17;
      v6 = v16;
LABEL_15:
      ++v7;
      v21 += 16;
    }
  }
  v11 = 0;
  v22 = 0;
  while ( 1 )
  {
    v12 = v8[39];
    v13 = (int)(v8 + 38);
    if ( v12 == 0 || v11 >= (*(uint32_t *)(v13 + 8) - v12) >> 4 )
      break;
    v14 = v19[39] + v22;
    if ( *(uint32_t *)(v14 + 12) == v19[33] )
      goto LABEL_24;
    if ( v6 == nullptr || (v4 - v6) >> 4 >= (unsigned int)((v18 - (int)v6) >> 4) )
    {
      sub_54F610((int)v15, v4, 1u, (uint32_t *)(v19[39] + v22));
      v4 = v17;
      v6 = v16;
LABEL_24:
      v8 = v19;
      ++v11;
      v22 += 16;
      continue;
    }
    sub_4BF340(v4, 1, v14);
    v8 = v19;
    v4 += 16;
    ++v11;
    v17 = v4;
    v22 += 16;
  }
  sub_54FE50(v13, (int)v15);
  if ( v6 != nullptr )
    j__free(v6);
}



// ------------------------------------------------------------
// 0x5502A0 sub_5502A0 —— 结算数据（29 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5502A0(uint32_t *this)
{
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  *(this + 78) = 0;
  *(this + 79) = 0;
  *(this + 80) = 0;
  *(this + 81) = 2;
  return 0;
}



// ------------------------------------------------------------
// 0x550300 sub_550300 —— PVP 结果数据准备（64 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_550300(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  uint32_t *v5; // edi
  int i; // ebx
  uint32_t *v7; // edi
  int j; // ebx
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v10)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v11)(uint32_t, int); // ecx
  uint32_t *v12; // esi
  int k; // edi

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 1) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 5) = 0;
  v5 = this + 6;
  for ( i = 5; i != 0; --i )
  {
    if ( *v5 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v5)(*v5, 1);
    *v5++ = 0;
  }
  v7 = this + 11;
  for ( j = 2; j != 0; --j )
  {
    if ( *v7 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v7)(*v7, 1);
    *v7++ = 0;
  }
  v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  v10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( v10 != nullptr )
    result = (**v10)(v10, 1);
  v11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  *(this + 14) = 0;
  if ( v11 != nullptr )
    result = (**v11)(v11, 1);
  *(this + 15) = 0;
  v12 = this + 36;
  for ( k = 3; k != 0; --k )
  {
    if ( *v12 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v12)(*v12, 1);
    *v12++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5503D0 sub_5503D0 —— 技能购买窗辅助（23 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5503D0(uint32_t *this)
{
  int v1; // ecx
  int result; // eax
  LONG v3; // edx
  LONG i; // ecx

  v1 = *(this + 1);
  result = 0;
  v3 = *(uint32_t *)(v1 + 20) + 24;
  for ( i = *(uint32_t *)(v1 + 24) + 46; pt.x < v3 || pt.x >= v3 + 228 || pt.y < i || pt.y >= i + 38; i += 39 )
  {
    if ( ++result >= 7 )
      return -1;
  }
  return result;
}



// ============================================================
// 【分区 2】技能购买窗 CNRDSkillBuyWindow（0x550420-0x550C40）
// vmt8 Update（99 行悬停+翻页）、vmt0 绘制（136 行技能格子）、
// vmtC 打开（RECIPE_NOTICE 配方提示事件）、vmt1C 刷新（47F7D0/47EB10）。
// ============================================================
// ------------------------------------------------------------
// 0x550420 CNRDSkillBuyWindow__vmt10 —— CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + dword_9B88CC/dword_795374 购买上下文）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillBuyWindow__vmt10(uint32_t *this)
{
  uint32_t *v2; // ecx
  char result; // al

  v2 = (uint32_t *)*(this + 2);
  if ( v2[626] == 3 )
    sub_44ABE0(v2, 0);
  sub_44E850((uint32_t *)*(this + 2), 17);
  result = dword_9B88CC;
  if ( dword_9B88CC != 0 )
  {
    result = dword_795374;
    if ( dword_795374 == *(this + 81) )
      return sub_44E850((uint32_t *)*(this + 2), 18);
  }
  return result;
}



// ------------------------------------------------------------
// 0x550470 sub_550470 —— 判定 dword_9B88CC==3（购买上下文查询）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_550470(uint32_t *this)
{
  return *(this + 81) == 3;
}



// ------------------------------------------------------------
// 0x550480 CNRDSkillBuyWindow__vmt8 —— CNRDSkillBuyWindow__vmt8 Update（99 行：鼠标悬停格子高亮 44E8D0/0x12 + CLICK_BUTTON2 翻页音 + 69C680/69C690 滚动）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillBuyWindow__vmt8(int this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  uint32_t *v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // edi
  int v11; // ebx
  int v12; // edi
  int v13; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  unsigned int v17; // eax
  int v18; // eax

  if ( *(uint8_t *)(*(uint32_t *)(this + 20) + 108) != 0 )
  {
    sub_69C680(0);
    v2 = 16 * (*(uint32_t *)(*(uint32_t *)(this + 20) + 104) + 4);
    v3 = *(uint32_t *)(v2 + this + 4);
    v4 = this + v2;
    if ( v3 != 0 )
      v5 = (*(uint32_t *)(v4 + 8) - v3) >> 2;
    else
      v5 = 0;
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(
      *(uint32_t *)(this + 56),
      (v5 - 7) & ((v5 - 7 <= 0) - 1));
  }
  v6 = *(uint32_t *)(this + 60);
  if ( *(uint8_t *)(v6 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v6 + 12) )
  {
    v7 = *(uint32_t **)(this + 8);
    if ( v7[626] == 3 )
      sub_44ABE0(v7, 0);
    else
      sub_44ABE0(v7, 3);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v8 = *(uint32_t *)(*(uint32_t *)(this + 8) + 2504);
  if ( v8 == 1 )
    goto LABEL_22;
  if ( v8 == 2 )
    goto LABEL_22;
  v9 = *(uint32_t *)(this + 4);
  if ( *(uint8_t *)(v9 + 17) == 0 )
    goto LABEL_22;
  v10 = *(uint32_t *)(v9 + 12);
  if ( dword_79BE3C != v10 && dword_79BE34 != v10 && dword_79BE38 != v10 )
    goto LABEL_22;
  v11 = sub_5503D0((uint32_t *)this);
  if ( v11 == -1 )
    goto LABEL_22;
  v12 = *(uint32_t *)(*(uint32_t *)(this + 20) + 104);
  v13 = sub_69C690(*(uint32_t *)(this + 56));
  v14 = 16 * (v12 + 4);
  v15 = *(uint32_t *)(v14 + this + 4);
  v16 = this + v14;
  v17 = v11 + v13;
  if ( v15 != 0
    && v17 < (*(uint32_t *)(v16 + 8) - v15) >> 2
    && (v18 = *(uint32_t *)(*(uint32_t *)(16 * v12 + this + 68) + 4 * v17)) != 0 )
  {
    if ( dword_9B88CC != v18 || dword_795374 != *(uint32_t *)(this + 324) )
    {
      v18 = sub_44E8D0(*(char **)(this + 8), (void *)0x12, v18, *(uint32_t *)(this + 324));
      if ( v18 != 0 )
        LOBYTE(v18) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v18 + 48))(
                        v18,
                        *(uint32_t *)(*(uint32_t *)(this + 4) + 20) + 24,
                        *(uint32_t *)(*(uint32_t *)(this + 4) + 24) + 39 * v11 + 46,
                        32,
                        32);
    }
  }
  else
  {
LABEL_22:
    LOBYTE(v18) = dword_9B88CC;
    if ( dword_9B88CC != 0 )
    {
      LOBYTE(v18) = dword_795374;
      if ( dword_795374 == *(uint32_t *)(this + 324) )
        LOBYTE(v18) = sub_44E850(*(uint32_t **)(this + 8), 18);
    }
  }
  return v18;
}



// ------------------------------------------------------------
// 0x550620 CNRDSkillBuyWindow__vmt0 —— CNRDSkillBuyWindow__vmt0 绘制（136 行：491530/491630 批次 + 418DD0 精灵 + 47EB10/5013F0/501420 技能数据 + 47DCC0/47DF50）
// ------------------------------------------------------------
int /*userpurge*/ sub_550620@<eax>(uint32_t *a1@<ecx>, uint32_t *a2@<esi>, int a3)
{
  int result; // eax
  int v5; // ebx
  int v6; // eax
  uint32_t *v7; // ebx
  int v8; // ecx
  int v9; // eax
  int v10; // esi
  int v11; // eax
  int v12; // ecx
  int v13; // esi
  int v14; // ebx
  int v15; // eax
  bool v16; // bl
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  bool v22; // cc
  int v24; // [esp+4h] [ebp-30h]
  int v25; // [esp+4h] [ebp-30h]
  int v26; // [esp+8h] [ebp-2Ch]
  int v27; // [esp+Ch] [ebp-28h]
  int v28; // [esp+10h] [ebp-24h]
  uint32_t *v29; // [esp+14h] [ebp-20h]
  int v30; // [esp+18h] [ebp-1Ch]
  int v31; // [esp+18h] [ebp-1Ch]
  int Value; // [esp+1Ch] [ebp-18h]
  int v33; // [esp+20h] [ebp-14h]
  unsigned int v34; // [esp+24h] [ebp-10h]
  int v35; // [esp+28h] [ebp-Ch]
  int v36; // [esp+2Ch] [ebp-8h]
  int v37; // [esp+3Ch] [ebp+8h]

  result = a3;
  if ( a3 == a1[1] )
  {
    v5 = *(uint32_t *)(a1[5] + 104);
    v26 = v5;
    v27 = sub_5503D0(a1);
    v35 = 0;
    v6 = sub_69C690(a1[14]);
    v7 = &a1[4 * v5 + 16];
    v8 = 0;
    v34 = v6;
    v29 = v7;
    v28 = 0;
    do
    {
      v9 = a1[1];
      v10 = *(uint32_t *)(v9 + 20) + 24;
      v36 = *(uint32_t *)(v9 + 24) + v8 + 46;
      v33 = v10;
      if ( v27 == v35 )
      {
        sub_491530(2, 0);
        v11 = sub_418DD0(1);
        if ( v11 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(v11, v10, v36, dword_79C0B0);
        sub_491630(2);
      }
      v12 = v7[1];
      if ( v12 != 0 && v34 < (v7[2] - v12) >> 2 )
      {
        v13 = *(uint32_t *)(a1[4 * v26 + 17] + 4 * v34);
        v37 = sub_41A5E0(v13 + 496);
        v30 = sub_41A5E0(v13 + 64);
        v14 = v30 + v37 * sub_41A5E0(v13 + 78);
        v31 = v14;
        v15 = sub_47EB10(v13);
        Value = v15;
        if ( a1[81] == 3 && *(uint8_t *)(v13 + 480) != 0 )
        {
          Value = sub_5013F0(v15, *(uint32_t *)(v13 + 488));
          v14 = sub_501420(v14, *(uint32_t *)(v13 + 492));
          v31 = v14;
        }
        v16 = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int, uint32_t *))(*(uint32_t *)dword_8F7C04 + 672))(
                           dword_8F7C04,
                           3,
                           a2) < v14;
        v24 = sub_41A5E0(v13 + 496);
        if ( v24 + 1 >= sub_47DCC0(v13) )
          v17 = sub_47DCC0(v13);
        else
          v17 = sub_41A5E0(v13 + 496) + 1;
        sub_47DF50(v33 + 5, v36 + 4, v17, v16 ? 2 : 0, 1, 0, 0);
        if ( v16 )
          v18 = 2;
        else
          v18 = v27 == v35;
        a2 = &a1[13 * v18 + 39];
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);
        v25 = *(uint32_t *)dword_79C0B0;
        v19 = sub_41ACF0(v13 + 20);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v25 + 80))(
          dword_79C0B0,
          v33 + 47,
          v36 + 5,
          v16 ? -13487361 : -1,
          v19);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        sub_69A110(v33 + 70, v36 + 24, Value, -1);
        if ( v16 )
        {
          v20 = sub_418DD0(82);
          if ( v20 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v20 + 152))(v20, v33 + 92, v36 + 21, dword_79C0B0);
          sub_69A110(v33 + 132, v36 + 24, v31, -1);
        }
        if ( (uint8_t)sub_47EB90(v13) == 0 )
        {
          v21 = sub_418DD0(96);
          if ( v21 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v21 + 152))(v21, v33 + 163, v36 + 21, dword_79C0B0);
        }
        v7 = v29;
      }
      result = v35 + 1;
      v8 = v28 + 39;
      v22 = v28 + 39 < 273;
      ++v35;
      v28 += 39;
      ++v34;
    }
    while ( v22 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x550960 CNRDSkillBuyWindow__vmtC —— CNRDSkillBuyWindow__vmtC 打开槽：RECIPE_NOTICE 配方提示事件（43BEE0/432EA0 + 69C980/69A5F0 + 44BBA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillBuyWindow__vmtC(uint32_t *this)
{
  uint32_t *v1; // ebx
  uint32_t *v2; // esi
  char *v3; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // esi
  uint32_t *v8; // ebx
  int v9; // esi
  uint32_t *v10; // ebx
  int v11; // esi
  uint32_t *v12; // ebx
  int v13; // esi
  uint32_t *v14; // ebx
  int v15; // esi
  uint32_t **v16; // edi
  int i; // [esp+8h] [ebp-4h]

  v1 = this;
  if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
  {
    v2 = *(uint32_t **)(*(this + 2) + 28);
    v3 = sub_422E70(491);
    sub_43BEE0(v2, (int)v3, -6567706, 0, -1);
    sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
    return 0;
  }
  if ( dword_8F7C04 == 0 )
    return 0;
  v5 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);
  v6 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
  if ( v5 != 0 )
  {
    switch ( v5 )
    {
      case 1:
        v9 = 33;
        v10 = v1 + 6;
        do
        {
          sub_69C980(v6, v9, v9, v9 - 1, -1, 0, 0);
          v9 += 2;
          ++v10;
        }
        while ( v9 < 41 );
        break;
      case 2:
        v11 = 98;
        v12 = v1 + 6;
        do
        {
          sub_69C980(v6, v11, v11, v11 - 1, -1, 0, 0);
          v11 += 2;
          ++v12;
        }
        while ( v11 < 108 );
        goto LABEL_21;
      case 3:
        v13 = 119;
        v14 = v1 + 6;
        do
        {
          sub_69C980(v6, v13, v13, v13 - 1, -1, 0, 0);
          v13 += 2;
          ++v14;
        }
        while ( v13 < 127 );
        break;
      default:
        goto LABEL_22;
    }
  }
  else
  {
    v7 = 25;
    v8 = v1 + 6;
    do
    {
      sub_69C980(v6, v7, v7, v7 - 1, -1, 0, 0);
      v7 += 2;
      ++v8;
    }
    while ( v7 < 33 );
  }
  sub_69C980(v6, 95, 95, 94, -1, 0, 0);
LABEL_21:
  v1 = this;
LABEL_22:
  v15 = 45;
  v16 = (uint32_t **)(v1 + 6);
  for ( i = 5; i != 0; --i )
  {
    sub_69A5F0(*v16, v15, 80);
    v15 += (*v16++)[7];
  }
  sub_44BBA0((uint32_t *)v1[2], 4, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x550B00 CNRDSkillBuyWindow__vmt1C —— CNRDSkillBuyWindow__vmt1C 刷新槽（69 行：47F7D0 + 44ACC0/47DE90/47EB10/5013F0/501420 + 44E8D0/44ABE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillBuyWindow__vmt1C(uint32_t *this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // esi
  int v5; // eax
  int v6; // ecx
  int v7; // edx
  char *v8; // ecx
  unsigned int v9; // eax
  int v10; // esi
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // ebx
  int v15; // ecx
  int v16; // eax
  int v18; // [esp+Ch] [ebp-8h]
  bool v19; // [esp+13h] [ebp-1h]

  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0 )
    return 0;
  if ( dword_79BE34 != *(uint32_t *)(v2 + 12) )
    return 0;
  v3 = sub_5503D0(this);
  if ( v3 == -1 )
    return 0;
  v4 = *(uint32_t *)(*(this + 5) + 104);
  v5 = sub_69C690(*(this + 14));
  v6 = 16 * (v4 + 4);
  v7 = *(uint32_t *)((char *)this + v6 + 4);
  v8 = (char *)this + v6;
  v9 = v3 + v5;
  if ( v7 == 0 || v9 >= (*((uint32_t *)v8 + 2) - v7) >> 2 )
    return 0;
  v10 = *(uint32_t *)(*(this + 4 * v4 + 17) + 4 * v9);
  v19 = sub_47F7D0((uint32_t *)v10);
  if ( *(this + 81) != 3 || *(uint8_t *)(v10 + 480) == 0 )
    goto LABEL_13;
  v11 = sub_44ACC0((void *)v10, 0);
  v12 = sub_47DE90((void *)v10, v11 + 1);
  v13 = sub_47EB10((uint32_t *)v10);
  v18 = sub_5013F0(v13, *(uint32_t *)(v10 + 488));
  v14 = sub_501420(v12, *(uint32_t *)(v10 + 492));
  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) < v14 )
    v19 = false;
  if ( Value >= v18 )
  {
LABEL_13:
    if ( v19 )
    {
      v15 = *(this + 2);
      v16 = *(uint32_t *)(v15 + 2504);
      if ( v16 == 0 || v16 == 3 )
      {
        sub_44E8D0((char *)v15, (void *)0x11, v10, v16 == 3);
        sub_44ABE0((uint32_t *)*(this + 2), 0);
      }
    }
  }
  return 1;
}



// ============================================================
// 【分区 3】任务系统辅助与文本（0x550C40-0x5517A0）
// 任务列表绘制在 0x550D20（238 行）；任务名设置在 0x5512D0（152 行，被
// char_server_info.cpp 0x583A60 调用）；任务文本辅助在 0x5515A0。
// ============================================================
// ------------------------------------------------------------
// 0x550C40 sub_550C40 —— 技能购买数据收尾（66 行）
// ------------------------------------------------------------
int /*usercall*/ sub_550C40@<eax>(int a1@<ecx>, int a2@<esi>)
{
  int result; // eax
  int v3; // edi
  unsigned int v4; // ebx
  int v5; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // eax
  unsigned int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v16; // [esp+Ch] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  v3 = *(uint32_t *)(result + 104);
  v4 = 0;
  if ( v3 != 0 )
  {
    v5 = *(uint32_t *)(v3 + 8);
    if ( v5 != 0 )
    {
      result = (*(uint32_t *)(v3 + 12) - v5) >> 2;
      v16 = result;
    }
    else
    {
      v16 = 0;
    }
    if ( v16 > 0 )
    {
      while ( 1 )
      {
        v6 = *(uint32_t *)(v3 + 8);
        if ( v6 != 0 && v4 < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
          v7 = *(uint32_t *)(v6 + 4 * v4);
        else
          v7 = 0;
        v8 = __RTDynamicCast(v7, 0, &CNRDObject `RTTI Type Descriptor', &CNRDNpc `RTTI Type Descriptor', 0);
        v9 = v8;
        if ( v8 != 0 && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 340))(v8) == *(uint32_t *)(a1 + 320) )
          break;
        result = v16;
        if ( (int)++v4 >= v16 )
          return result;
      }
      v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 340))(v9, a2);
      v11 = *(uint32_t *)(v10 + 180);
      v12 = v10 + 156;
      if ( v11 < 0x10 )
        v13 = v12 + 4;
      else
        v13 = *(uint32_t *)(v12 + 4);
      return (*(int (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v9 + 212))(v9, v13, -1, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x550D20 sub_550D20 —— 任务列表绘制（238 行：43C250/46F7A0/46F880 + 69A840/69CE50 + 426BD0/69C780/69C7B0/69CA20/69CA50/69C5D0/69CD70）
// ------------------------------------------------------------
int /*thiscall*/ sub_550D20(int this)
{
  int v2; // eax
  int v3; // eax
  uint32_t *v4; // edi
  int v5; // eax
  uint32_t *v6; // edi
  uint32_t *v7; // eax
  uint32_t *v8; // edi
  uint32_t *v9; // edi
  uint32_t *v10; // ecx
  uint32_t *v11; // eax
  uint32_t *v12; // edi
  uint32_t *v13; // ecx
  uint8_t *v14; // edi
  uint8_t *v15; // edi
  uint8_t *v16; // eax
  uint8_t *v17; // edi
  void *Block; // [esp+10h] [ebp-18h]
  void *Blocka; // [esp+10h] [ebp-18h]
  void *Blockb; // [esp+10h] [ebp-18h]
  void *Blockc; // [esp+10h] [ebp-18h]
  void *Blockd; // [esp+10h] [ebp-18h]
  void *Blocke; // [esp+10h] [ebp-18h]
  void *Blockf; // [esp+10h] [ebp-18h]
  uint32_t *v26; // [esp+14h] [ebp-14h]
  int v27; // [esp+14h] [ebp-14h]
  int v28; // [esp+14h] [ebp-14h]
  int v29; // [esp+14h] [ebp-14h]
  int v30; // [esp+14h] [ebp-14h]
  int i; // [esp+18h] [ebp-10h]
  int v32; // [esp+18h] [ebp-10h]
  int v33; // [esp+18h] [ebp-10h]

  *(uint32_t *)(this + 312) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
  if ( operator new(0x6Cu) != nullptr )
    v2 = sub_43C250(*(uint32_t *)(this + 312), 0);
  else
    v2 = 0;
  *(uint32_t *)(this + 4) = v2;
  *(uint32_t *)(v2 + 28) = *(uint32_t *)(v2 + 28);
  *(uint32_t *)(v2 + 32) = 353;
  *(uint32_t *)(*(uint32_t *)(this + 4) + 68) = this;
  if ( operator new(0x70u) != nullptr )
    v3 = sub_46F7A0(0);
  else
    v3 = 0;
  *(uint32_t *)(this + 20) = v3;
  v4 = (uint32_t *)(this + 24);
  for ( i = 5; i != 0; --i )
  {
    if ( operator new(0x88u) != nullptr )
      v5 = sub_46F880(*(uint32_t *)(this + 312), 95, 95, 94, -1, 0, 0);
    else
      v5 = 0;
    *v4 = v5;
    sub_69A840(v5);
    ++v4;
  }
  sub_69CE50(0);
  sub_69A840(*(uint32_t *)(this + 20));
  v32 = 4;
  v26 = (uint32_t *)(this + 44);
  do
  {
    v6 = operator new(0x84u);
    if ( v6 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v6);
      *v6 = &nengine::CNButton::`vftable';
      sub_69C780(v6);
      sub_69C7B0(Block, v32, v32, v32 + 1, v32, 0, 0);
    }
    else
    {
      v6 = nullptr;
    }
    *v26++ = v6;
    v32 += 2;
  }
  while ( v32 < 8 );
  v7 = operator new(0x88u);
  v8 = v7;
  if ( v7 != nullptr )
  {
    Blocka = *(void **)(this + 312);
    sub_426BD0(v7);
    *v8 = &nengine::CNSlider::`vftable';
    sub_69CA20(v8);
    sub_69CA50(Blocka, 2, 3);
    *v8 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v8 = nullptr;
  }
  *(uint32_t *)(this + 52) = v8;
  v9 = operator new(0x74u);
  if ( v9 != nullptr )
  {
    v27 = *(uint32_t *)(this + 48);
    Blockb = *(void **)(this + 52);
    v33 = *(uint32_t *)(this + 44);
    sub_426BD0(v9);
    *v9 = &nengine::CNScroll::`vftable';
    sub_69C5D0(v9);
    *v9 = &nengine::CNVScroll::`vftable';
    sub_69C5D0(v9);
    sub_69CD70(v33, v27, Blockb);
    v10 = v9;
  }
  else
  {
    v10 = nullptr;
  }
  *(uint32_t *)(this + 56) = v10;
  sub_69A5F0(255, 51);
  sub_69A840(*(uint32_t *)(this + 56));
  v11 = operator new(0x84u);
  v12 = v11;
  if ( v11 != nullptr )
  {
    Blockc = *(void **)(this + 312);
    sub_426BD0(v11);
    *v12 = &nengine::CNButton::`vftable';
    sub_69C780(v12);
    sub_69C7B0(Blockc, 8, 9, 10, 8, 0, 0);
    v13 = v12;
  }
  else
  {
    v13 = nullptr;
  }
  *(uint32_t *)(this + 60) = v13;
  sub_69A5F0(112, 332);
  sub_69A840(*(uint32_t *)(this + 60));
  sub_69A5F0(29, 63);
  v14 = operator new(0x2Cu);
  if ( v14 != nullptr )
  {
    Blockd = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 12);
    v28 = dword_79C0B0;
    v14[4] = 0;
    *(uint32_t *)v14 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v14);
    sub_699E40(v28, Blockd, 25, 4);
  }
  else
  {
    v14 = nullptr;
  }
  *(uint32_t *)(this + 144) = v14;
  v15 = operator new(0x2Cu);
  if ( v15 != nullptr )
  {
    Blocke = *(void **)(this + 312);
    v29 = dword_79C0B0;
    v15[4] = 0;
    *(uint32_t *)v15 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v15);
    sub_699E40(v29, Blocke, 13, 4);
  }
  else
  {
    v15 = nullptr;
  }
  *(uint32_t *)(this + 148) = v15;
  v16 = operator new(0x2Cu);
  v17 = v16;
  if ( v16 != nullptr )
  {
    Blockf = *(void **)(this + 312);
    v30 = dword_79C0B0;
    v16[4] = 0;
    *(uint32_t *)v16 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v16);
    sub_699E40(v30, Blockf, 39, 4);
  }
  else
  {
    v17 = nullptr;
  }
  *(uint32_t *)(this + 152) = v17;
  *(uint8_t *)(this + 156) = 0;
  *(uint8_t *)(this + 157) = 0;
  *(uint8_t *)(this + 158) = 0;
  *(uint8_t *)(this + 159) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 172) = 6;
  *(uint32_t *)(this + 176) = 12;
  *(uint32_t *)(this + 184) = 1600;
  *(uint32_t *)(this + 204) = dword_99FCCC;
  *(uint8_t *)(this + 208) = 0;
  *(uint8_t *)(this + 209) = 0;
  *(uint8_t *)(this + 210) = 0;
  *(uint8_t *)(this + 211) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 228) = 12;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 252) = 0;
  *(uint32_t *)(this + 256) = 0;
  *(uint32_t *)(this + 224) = 6;
  *(uint32_t *)(this + 236) = 1600;
  *(uint32_t *)(this + 256) = dword_99FCCC;
  *(uint8_t *)(this + 260) = 0;
  *(uint8_t *)(this + 261) = 0;
  *(uint8_t *)(this + 262) = 0;
  *(uint8_t *)(this + 263) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 280) = 12;
  *(uint32_t *)(this + 284) = 0;
  *(uint32_t *)(this + 292) = 0;
  *(uint32_t *)(this + 296) = 0;
  *(uint32_t *)(this + 300) = 0;
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 276) = 6;
  *(uint32_t *)(this + 288) = 1600;
  *(uint32_t *)(this + 308) = dword_99FCCC;
  *(uint8_t *)(this + 210) = 1;
  *(uint32_t *)(this + 212) = -13484731;
  return 1600;
}


// ------------------------------------------------------------
// 0x5512D0 sub_5512D0 —— 任务名/文本设置（152 行：47E720 + 41A5E0/565EE0 + 44AB90=TAB_SELECT）
// ------------------------------------------------------------
int /*thiscall*/ sub_5512D0(uint32_t *this, int a2)
{
  int result; // eax
  uint32_t *v3; // ebx
  int *v4; // esi
  int *v5; // eax
  int v6; // edx
  void **v7; // esi
  int i; // edi
  uint32_t *v9; // eax
  int v10; // esi
  int v11; // eax
  int v12; // edx
  char v13; // bl
  unsigned int j; // ecx
  bool v15; // zf
  int v16; // edi
  int v17; // eax
  uint32_t *v18; // eax
  int v19; // edx
  unsigned int v20; // edi
  int *v21; // ecx
  uint32_t *v22; // edx
  int v23; // eax
  int v24; // ecx
  uint32_t *v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // ecx
  int v29; // esi
  uint32_t *k; // ecx
  int v31; // [esp+8h] [ebp-18h] BYREF
  int v32; // [esp+Ch] [ebp-14h]
  int v33; // [esp+10h] [ebp-10h]
  uint32_t *v34; // [esp+14h] [ebp-Ch]
  int v35; // [esp+18h] [ebp-8h]
  uint32_t *v36; // [esp+1Ch] [ebp-4h]

  result = a2;
  v3 = this;
  *(this + 79) = a2;
  v4 = (int *)dword_8F7C04;
  v36 = this;
  if ( dword_8F7C04 != 0 )
  {
    v5 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);
    v6 = *v4;
    v33 = *v5;
    v35 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v6 + 1032))(v4) + 4);
    v7 = (void **)(v3 + 17);
    for ( i = 5; i != 0; --i )
    {
      if ( *v7 != nullptr )
        j__free(*v7);
      *v7 = nullptr;
      v7[1] = nullptr;
      v7[2] = nullptr;
      v7 += 4;
    }
    v9 = *(uint32_t **)(a2 + 4);
    v15 = v9 == *(uint32_t **)(a2 + 8);
    v34 = v9;
    if ( !v15 )
    {
      do
      {
        v10 = sub_47E720(v33, *v9);
        v31 = v10;
        if ( v10 != 0 )
        {
          v11 = sub_41A5E0(14 * v35 + v10 + 212);
          v12 = *(uint32_t *)(v10 + 468);
          v13 = 0;
          v32 = v11;
          for ( j = 0; v12 != 0 && j < (*(uint32_t *)(v10 + 472) - v12) >> 2; ++j )
          {
            if ( v35 == *(uint32_t *)(*(uint32_t *)(v10 + 468) + 4 * j) )
            {
              v13 = 1;
              break;
            }
          }
          if ( v36[81] == 3 && *(uint8_t *)(v10 + 480) != 0 )
            v15 = v13 == 1;
          else
            v15 = v13 == 0;
          if ( !v15 )
          {
            v16 = v32;
            if ( v32 != 0 && sub_41A5E0(v10 + 496) < v16 )
            {
              v17 = sub_41A5E0(v10 + 128);
              v18 = &v36[4 * v17 + 16];
              v19 = v18[1];
              if ( v19 != 0 )
                v20 = (v18[2] - v19) >> 2;
              else
                v20 = 0;
              if ( v19 != 0 && v20 < (v18[3] - v19) >> 2 )
              {
                v21 = (int *)v18[2];
                *v21 = v10;
                v18[2] = v21 + 1;
              }
              else
              {
                sub_565EE0((void *)v18[2], 1, (int)&v31);
              }
            }
          }
          v3 = v36;
        }
        v22 = *(uint32_t **)(a2 + 8);
        v9 = ++v34;
      }
      while ( v34 != v22 );
    }
    v23 = 4 * (*(uint32_t *)(v3[5] + 104) + 4);
    v24 = v3[v23 + 1];
    v25 = &v3[v23];
    if ( v24 != 0 )
      v26 = (v25[2] - v24) >> 2;
    else
      v26 = 0;
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)v3[14] + 32))(v3[14], (v26 - 7) & ((v26 - 7 <= 0) - 1));
    v27 = 4 * (*(uint32_t *)(v3[5] + 104) + 4);
    v28 = v3[v27 + 1];
    result = (int)&v3[v27];
    if ( v28 == 0 || (result = (*(uint32_t *)(result + 8) - v28) >> 2) == 0 )
    {
      v29 = 0;
      for ( k = v3 + 17; ; k += 4 )
      {
        if ( *k != 0 )
        {
          result = (k[1] - *k) >> 2;
          if ( result != 0 )
            break;
        }
        if ( ++v29 >= 5 )
          return result;
      }
      return sub_44AB90(v29);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x551500 sub_551500 —— 任务文本联动（429830/472E30/5512D0）
// ------------------------------------------------------------
void /*thiscall*/ sub_551500(uint32_t *this, int a2)
{
  uint32_t *v2; // edi
  bool v4; // zf
  int v5; // ebx
  int *v6; // [esp+8h] [ebp-8h] BYREF
  int v7; // [esp+Ch] [ebp-4h]

  v2 = (uint32_t *)a2;
  if ( a2 != 0 )
  {
    v7 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    if ( v7 != 0 )
    {
      v4 = *v2 == 27;
      *(this + 80) = *v2;
      if ( !v4
        || (v5 = dword_8F8540, a2 = 355, *sub_472E30((int **)(dword_8F8540 + 48), &v6, &a2) == *(int **)(v5 + 52)) )
      {
        *(this + 81) = 2;
      }
      else
      {
        *(this + 81) = 3;
      }
      sub_5512D0(this, (int)&v2[4 * *(uint32_t *)(v7 + 44) + 58]);
    }
  }
}



// ------------------------------------------------------------
// 0x5515A0 sub_5515A0 —— 任务文本辅助（77 行）
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_5515A0(const char *a1, unsigned int a2)
{
  unsigned int result; // eax
  char v3; // cl
  int v4; // ecx
  signed int v5; // ecx

  if ( strlen(a1) <= a2 )
    return strlen(a1);
  for ( result = 0; ; result = v5 )
  {
    v3 = a1[result];
    if ( v3 < 0
      && (v3 == -127
       || v3 == -126
       || v3 == -125
       || v3 == -124
       || v3 == -121
       || v3 == -120
       || v3 == -119
       || v3 == -118
       || v3 == -117
       || v3 == -116
       || v3 == -115
       || v3 == -114
       || v3 == -113
       || v3 == -112
       || v3 == -111
       || v3 == -110
       || v3 == -109
       || v3 == -108
       || v3 == -107
       || v3 == -106
       || v3 == -105
       || v3 == -104
       || v3 == -103
       || v3 == -102
       || v3 == -101
       || v3 == -100
       || v3 == -99
       || v3 == -98
       || v3 == -97
       || v3 == -32
       || v3 == -31
       || v3 == -30
       || v3 == -29
       || v3 == -28
       || v3 == -27
       || v3 == -26
       || v3 == -25
       || v3 == -24
       || v3 == -23
       || v3 == -22
       || v3 == -19
       || v3 == -18
       || v3 == -6
       || v3 == -5
       || v3 == -4) )
    {
      v4 = 2;
    }
    else
    {
      v4 = 1;
    }
    v5 = result + v4;
    if ( v5 > (int)a2 )
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x551730 sub_551730 —— 任务文本辅助 2（36 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_551730(int this)
{
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 28) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = -1;
  *(uint32_t *)(this + 212) = 0;
  return 0;
}



// ============================================================
// 【分区 4】任务信息窗 CNRDQuestInfoWindow（0x5517A0-0x553130）
// vmt0 构造（164 行）/vmtC 打开/vmt8 Update（LETTER_FADE_IN_01/02 信纸
// 淡入 + WRITE_CHAR_LOOP 打字机）；0x552070 页绘制（322 行）；
// 任务文本装配在 0x552BD0（246 行）。
// ============================================================
// ------------------------------------------------------------
// 0x5517A0 CNRDQuestInfoWindow__vmt10 —— CNRDQuestInfoWindow__vmt10 状态切换槽（432EE0 + 44E850）
// ------------------------------------------------------------
char /*thiscall*/ CNRDQuestInfoWindow__vmt10(int this)
{
  *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 8) + 84) + 180) = -1;
  if ( *(uint8_t *)(this + 28) != 0 )
    sub_432EE0(5);
  return sub_44E850(*(uint32_t **)(this + 8), 38);
}



// ------------------------------------------------------------
// 0x5517D0 sub_5517D0 —— 任务文本初始化（522300/41A5E0/4E9C00/445150）
// ------------------------------------------------------------
int /*stdcall*/ sub_5517D0(void *a1)
{
  int result; // eax
  int v2; // edi
  int v3; // eax
  int *v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // edx
  char v8[60]; // [esp+4h] [ebp-48h] BYREF
  int v9; // [esp+48h] [ebp-4h]

  result = sub_522300(a1, 1, 0, 0, -1, 0);
  v2 = result;
  if ( result != 0 )
  {
    v3 = __RTDynamicCast(result, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
    v4 = (int *)v3;
    if ( v3 != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 172))(v3);
      v6 = sub_41A5E0(v5 + 18);
      sub_4E9C00(dword_8F84B0, 0, 0, v6, 0);
      v7 = *v4;
      v9 = 0;
      (*(void (/*thiscall*/ **)(int *, char *))(v7 + 184))(v4, v8);
      v9 = -1;
      sub_445150(v8);
    }
    return v2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5518A0 sub_5518A0 —— 任务信纸文本动画：LETTER_FADE_IN_02/WRITE_CHAR_LOOP 事件（69C340/69C400/698F90/432EA0/69C360/69C500/69C3A0/69C440/69C680）
// ------------------------------------------------------------
int /*userpurge*/ sub_5518A0@<eax>(int a1@<ecx>, int a2@<ebx>, char a3)
{
  int result; // eax
  const char *v5; // eax
  signed int v6; // eax
  int v7; // ecx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  unsigned int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax

  result = *(uint32_t *)(a1 + 16);
  if ( result != 0 )
  {
    *(uint8_t *)(a1 + 28) = a3;
    sub_69C340(-1);
    sub_69C400(0);
    sub_69C340(-1);
    sub_69C400(0);
    *(uint8_t *)(a1 + 45) = 0;
    *(uint8_t *)(a1 + 46) = 0;
    sub_698F90(a1 + 32, 0, 0);
    v5 = *(const char **)(a1 + 24);
    if ( *(uint8_t *)(a1 + 28) != 0 )
    {
      *(uint32_t *)(a1 + 60) = 0;
      *(uint32_t *)(a1 + 68) = 0;
      v6 = 30 * strlen(v5);
      *(uint32_t *)(a1 + 64) = v6;
      if ( v6 > 8000 )
        v6 = 8000;
      *(uint32_t *)(a1 + 64) = v6;
      if ( v6 < 400 )
        v6 = 400;
      v7 = *(uint32_t *)(a1 + 84);
      *(uint32_t *)(a1 + 64) = v6;
      *(uint8_t *)(v7 + 17) = 0;
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 84) + 32))(*(uint32_t *)(a1 + 84), 0);
      *(uint8_t *)(*(uint32_t *)(a1 + 104) + 17) = 0;
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 104) + 32))(*(uint32_t *)(a1 + 104), 0);
      *(uint8_t *)(*(uint32_t *)(a1 + 116) + 17) = 0;
      *(uint8_t *)(*(uint32_t *)(a1 + 120) + 17) = 0;
      *(uint8_t *)(*(uint32_t *)(a1 + 124) + 17) = 0;
      sub_432EA0("WRITE_CHAR_LOOP", 5, 0, 0);
    }
    else
    {
      sub_69C360(v5, 0);
      *(uint8_t *)(*(uint32_t *)(a1 + 84) + 17) = 1;
      v8 = sub_69C500(*(uint32_t *)(a1 + 88));
      v9 = sub_69C3A0(*(uint32_t *)(a1 + 88));
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(a1 + 84) + 32))(
        *(uint32_t *)(a1 + 84),
        (v8 - v9) & ((v8 - v9 <= 0) - 1),
        a2);
      sub_69C440(-4265479);
      v10 = *(uint32_t *)(a1 + 16);
      v11 = *(uint32_t *)(v10 + 84);
      v12 = v10 + 60;
      if ( v11 < 0x10 )
        v13 = v12 + 4;
      else
        v13 = *(uint32_t *)(v12 + 4);
      sub_69C360(v13, 0);
      *(uint8_t *)(*(uint32_t *)(a1 + 104) + 17) = 1;
      v14 = sub_69C500(*(uint32_t *)(a1 + 108));
      v15 = sub_69C3A0(*(uint32_t *)(a1 + 108));
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 104) + 32))(
        *(uint32_t *)(a1 + 104),
        (v14 - v15) & ((v14 - v15 <= 0) - 1));
      *(uint8_t *)(*(uint32_t *)(a1 + 116) + 17) = 1;
      *(uint8_t *)(*(uint32_t *)(a1 + 120) + 17) = 1;
      *(uint8_t *)(*(uint32_t *)(a1 + 124) + 17) = 1;
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 124) + 16) != 0 )
        sub_432EA0("LETTER_FADE_IN_02", -1, 0, 0);
    }
    sub_69C680(0);
    return sub_69C680(0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x551A60 sub_551A60 —— 任务文本辅助（4999D0，99 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_551A60(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  uint32_t *v3; // edi
  int i; // ebx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  uint32_t *v8; // edi
  int j; // ebx
  void (/*thiscall*/ ***v10)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v11)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v12)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v13)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v14)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v15)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v16)(uint32_t, int); // ecx
  void *v17; // edi
  int (/*thiscall*/ ***v18)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 1) = 0;
  v3 = this + 18;
  for ( i = 2; i != 0; --i )
  {
    if ( *v3 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v3)(*v3, 1);
    *v3++ = 0;
  }
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 20);
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  v6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 21);
  *(this + 20) = 0;
  if ( v6 != nullptr )
    (**v6)(v6, 1);
  v7 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 22);
  *(this + 21) = 0;
  if ( v7 != nullptr )
    (**v7)(v7, 1);
  *(this + 22) = 0;
  v8 = this + 23;
  for ( j = 2; j != 0; --j )
  {
    if ( *v8 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v8)(*v8, 1);
    *v8++ = 0;
  }
  v10 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 25);
  if ( v10 != nullptr )
    (**v10)(v10, 1);
  v11 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 26);
  *(this + 25) = 0;
  if ( v11 != nullptr )
    (**v11)(v11, 1);
  v12 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 27);
  *(this + 26) = 0;
  if ( v12 != nullptr )
    (**v12)(v12, 1);
  v13 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 28);
  *(this + 27) = 0;
  if ( v13 != nullptr )
    (**v13)(v13, 1);
  v14 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 29);
  *(this + 28) = 0;
  if ( v14 != nullptr )
    (**v14)(v14, 1);
  v15 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 30);
  *(this + 29) = 0;
  if ( v15 != nullptr )
    (**v15)(v15, 1);
  v16 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 31);
  *(this + 30) = 0;
  if ( v16 != nullptr )
    (**v16)(v16, 1);
  v17 = (void *)*(this + 53);
  *(this + 31) = 0;
  if ( v17 != nullptr )
  {
    sub_4999D0(v17);
    j__free(v17);
  }
  v18 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 51);
  result = 0;
  *(this + 53) = 0;
  if ( v18 != nullptr )
    result = (**v18)(v18, 1);
  *(this + 51) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x551BD0 CNRDQuestInfoWindow__vmtC —— CNRDQuestInfoWindow__vmtC 打开槽（29 行）
// ------------------------------------------------------------
char /*thiscall*/ CNRDQuestInfoWindow__vmtC(uint32_t *this)
{
  unsigned int v3; // ebx
  int i; // edi
  int v5; // eax
  int v6; // ecx

  if ( *(this + 4) == 0 )
    return 0;
  v3 = 0;
  for ( i = 0; ; i += 52 )
  {
    v5 = *(this + 47);
    if ( v5 == 0 || v3 >= (*(this + 48) - v5) / 52 )
      break;
    v6 = *(uint32_t *)(*(this + 47) + i + 48);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 4))(v6, 1);
    ++v3;
    *(uint32_t *)(i + *(this + 47) + 48) = 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x551C50 sub_551C50 —— 任务窗数据（5517D0 转发）
// ------------------------------------------------------------
int /*thiscall*/ sub_551C50(uint32_t *this)
{
  int v1; // edi
  LONG v2; // ebx
  unsigned int i; // esi
  int v4; // edi

  v1 = *(this + 47);
  v2 = 97;
  for ( i = 0; ; ++i )
  {
    if ( v1 == 0 || i >= (*(this + 48) - v1) / 52 )
      return -1;
    if ( pt.x >= v2 && pt.x < v2 + 34 && pt.y >= 356 && pt.y < 390 )
      break;
    v2 += 38;
  }
  v4 = *(this + 47) + 52 * i;
  if ( *(uint32_t *)(v4 + 48) == 0 )
    *(uint32_t *)(v4 + 48) = sub_5517D0(*(void **)v4);
  return i;
}



// ------------------------------------------------------------
// 0x551CE0 sub_551CE0 —— 任务窗联动（472E30）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_551CE0(int **this, int a2)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  return *sub_472E30(this + 50, &v3, &a2) != *(this + 51);
}



// ------------------------------------------------------------
// 0x551D10 CNRDQuestInfoWindow__vmt0 —— CNRDQuestInfoWindow__vmt0 构造（164 行：47C210 + 418DD0/4F2C10/551C50/44E850/44E8D0/422E70/50EF20/50EB40 + 42B420/491530/43B560/491630）
// ------------------------------------------------------------
char /*thiscall*/ sub_551D10(int this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // edi
  int v16; // ebx
  int v17; // eax
  unsigned int v18; // ecx
  uint32_t *v19; // eax
  int v20; // ecx
  uint32_t *v21; // eax
  const char *v22; // eax
  const char *v23; // eax
  int v24; // eax
  uint8_t v25; // bl
  int v26; // eax
  uint32_t *v28; // [esp-10h] [ebp-118h]
  int v29; // [esp-Ch] [ebp-114h]
  char Buffer[256]; // [esp+4h] [ebp-104h] BYREF
  int v31; // [esp+104h] [ebp-4h]

  v31 = dword_796E50;
  v3 = *(uint32_t *)(this + 16);
  if ( v3 != 0 )
  {
    if ( a2 == *(uint32_t *)(this + 4) )
    {
      v4 = sub_47C210(v3);
      if ( v4 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v4 + 152))(v4, 52, 90, dword_79C0B0);
      v5 = *(uint32_t *)(this + 20);
      if ( v5 != 0 )
      {
        v6 = *(uint32_t *)(v5 + 64);
        if ( v6 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, 54, 122, dword_79C0B0);
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 128);
      v7 = *(uint32_t *)(this + 16);
      v8 = *(uint32_t *)(v7 + 28);
      v9 = v7 + 4;
      if ( v8 < 0x10 )
        v10 = v9 + 4;
      else
        v10 = *(uint32_t *)(v9 + 4);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 83, 96, -1, v10);
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v11 = *(uint32_t *)(this + 200);
      if ( v11 != 0 )
      {
        LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(v11, 83, 354, dword_79C0B0);
      }
      else
      {
        v12 = *(uint32_t *)(this + 188);
        v13 = 100;
        if ( v12 != *(uint32_t *)(this + 192) )
        {
          do
          {
            v14 = sub_418DD0(26);
            if ( v14 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 152))(v14, v13 - 3, 356, dword_79C0B0);
            sub_4F2C10(v13, 359, *(uint32_t *)(v12 + 4), *(uint32_t *)(v12 + 40));
            v3 = *(uint32_t *)(this + 192);
            v12 += 52;
            v13 += 38;
          }
          while ( v12 != v3 );
        }
      }
    }
    else if ( a2 == *(uint32_t *)(this + 204) )
    {
      v3 = sub_551C50(this);
      v15 = v3;
      if ( v3 == -1 )
      {
        if ( dword_795378 == 13 )
          LOBYTE(v3) = sub_44E850(*(uint32_t **)(this + 8), 26);
      }
      else
      {
        v16 = *(uint32_t *)(this + 188);
        v17 = 52 * v3;
        v18 = *(uint32_t *)(v17 + v16);
        v19 = (uint32_t *)(v16 + v17);
        if ( v18 > 1 )
        {
          v3 = v19[12];
          if ( v3 != 0 && dword_9B88D0 != v3 )
          {
            v3 = sub_44E8D0(*(char **)(this + 8), (void *)0x1A, v3, 13);
            if ( v3 != 0 )
              LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v3 + 48))(
                             v3,
                             38 * v15 + 100,
                             359,
                             28,
                             28);
          }
        }
        else
        {
          if ( v15 != *(uint32_t *)(this + 208) )
          {
            *(uint32_t *)(this + 208) = v15;
            v20 = v19[11];
            if ( v20 <= 1 )
            {
              if ( v19[8] < 0x10u )
                v23 = (const char *)(v19 + 3);
              else
                v23 = (const char *)v19[3];
              strcpy(Buffer, v23);
            }
            else
            {
              if ( v19[8] < 0x10u )
                v21 = v19 + 3;
              else
                v21 = (uint32_t *)v19[3];
              v29 = v20;
              v28 = v21;
              v22 = (const char *)sub_422E70(460);
              sprintf(Buffer, v22, v28, v29);
            }
            sub_50EF20(*(uint32_t *)(this + 212), Buffer, 4, -1);
          }
          LOBYTE(v3) = sub_50EB40(38 * v15 + 117, 360, 255);
        }
      }
    }
    else
    {
      v3 = *(uint32_t *)(this + 124);
      if ( a2 == v3 && *(uint8_t *)(v3 + 17) != 0 )
      {
        v24 = sub_699000(this + 32);
        v25 = sub_42B420(0, 255, v24, 400);
        sub_491530(2, 0);
        v26 = sub_418DD0(40);
        sub_43B560(118, 384, v26, 1065353216, 1065353216, 0, (v25 << 24) | 0xFFFFFF, 1333788672, 1333788672);
        LOBYTE(v3) = sub_491630(2);
      }
    }
  }
  return v3;
}


// ------------------------------------------------------------
// 0x552070 sub_552070 —— 任务信息页绘制（322 行：43C250/426BD0/69C780/69C7B0/69CA20/69CA50/43C630 + 69A5F0/69A840 + 69C2D0/69C520/69C440/69C420/69C3E0/69C4C0/69C5D0/69CD70 + 50EAD0/50F1C0）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_552070(int this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  int v4; // ebx
  uint8_t *v5; // edi
  uint8_t *v6; // eax
  uint32_t *v7; // edi
  int v8; // ebx
  uint8_t *v9; // eax
  uint8_t *v10; // eax
  uint8_t *v11; // eax
  uint32_t *v12; // edi
  int v13; // ecx
  int v14; // ebx
  uint8_t *v15; // edi
  uint8_t *v16; // edi
  uint8_t *v17; // edi
  uint32_t *v18; // ecx
  uint8_t *v19; // eax
  uint32_t *v20; // edi
  int v21; // ecx
  uint8_t *v22; // edi
  uint8_t *v23; // edi
  uint32_t *v24; // ecx
  uint8_t *v25; // edi
  uint8_t *v26; // edi
  uint8_t *v27; // eax
  uint8_t *v28; // eax
  uint8_t *v29; // eax
  uint8_t *result; // eax
  uint8_t *v31; // edi
  void *Block; // [esp+10h] [ebp-18h]
  void *Blocka; // [esp+10h] [ebp-18h]
  void *Blockb; // [esp+10h] [ebp-18h]
  void *Blockc; // [esp+10h] [ebp-18h]
  void *Blockd; // [esp+10h] [ebp-18h]
  int v37; // [esp+14h] [ebp-14h]
  int v38; // [esp+14h] [ebp-14h]
  int v39; // [esp+14h] [ebp-14h]
  uint32_t *v40; // [esp+14h] [ebp-14h]
  uint32_t *v41; // [esp+18h] [ebp-10h]
  uint32_t *v42; // [esp+18h] [ebp-10h]
  int v43; // [esp+18h] [ebp-10h]

  *(uint32_t *)(this + 180) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 40);
  v2 = operator new(0x6Cu);
  if ( v2 != nullptr )
    v3 = sub_43C250(v2, *(uint32_t *)(this + 180), 21);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 4) = v3;
  *((uint32_t *)v3 + 7) = *((uint32_t *)v3 + 7);
  *((uint32_t *)v3 + 8) = 353;
  *(uint32_t *)(*(uint32_t *)(this + 4) + 68) = this;
  v4 = 4;
  v41 = (uint32_t *)(this + 72);
  do
  {
    v5 = operator new(0x84u);
    if ( v5 != nullptr )
    {
      v37 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v5);
      *(uint32_t *)v5 = &nengine::CNButton::`vftable';
      sub_69C780((int)v5);
      sub_69C7B0((int)v5, v37, v4, v4, v4 + 1, v4, 0, 0);
    }
    else
    {
      v5 = nullptr;
    }
    *v41 = v5;
    v4 += 2;
    ++v41;
  }
  while ( v4 < 8 );
  v6 = operator new(0x88u);
  v7 = v6;
  if ( v6 != nullptr )
  {
    v8 = *(uint32_t *)(this + 180);
    sub_426BD0(v6);
    *v7 = &nengine::CNSlider::`vftable';
    sub_69CA20((int)v7);
    sub_69CA50((int)v7, v8, 37, 39);
    *v7 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v7 = nullptr;
  }
  *(uint32_t *)(this + 80) = v7;
  v9 = operator new(0x74u);
  if ( v9 != nullptr )
    v10 = sub_43C630(v9, *(uint32_t *)(this + 72), *(uint32_t *)(this + 76), *(uint32_t *)(this + 80));
  else
    v10 = nullptr;
  *(uint32_t *)(this + 84) = v10;
  sub_69A5F0(v10, 256, 55);
  sub_69A840(*(uint32_t **)(this + 4), *(uint32_t *)(this + 84));
  v11 = operator new(0x6Cu);
  v12 = v11;
  if ( v11 != nullptr )
  {
    sub_426BD0(v11);
    *v12 = &nengine::CNTextBox::`vftable';
    sub_69C2D0(v12);
    sub_69C520((int)v12, 150, 2048);
    v13 = (int)v12;
  }
  else
  {
    v13 = 0;
  }
  *(uint32_t *)(this + 88) = v13;
  sub_69C440(v13, -4265479);
  sub_69C420(*(uint32_t *)(this + 88), 6);
  sub_69C3E0(*(uint32_t *)(this + 88), 8);
  sub_69C4C0(*(uint32_t **)(this + 88), dword_99FCCC);
  sub_69A5F0(*(uint32_t **)(this + 88), 95, 56);
  sub_69A840(*(uint32_t **)(this + 4), *(uint32_t *)(this + 88));
  v14 = 4;
  v42 = (uint32_t *)(this + 92);
  do
  {
    v15 = operator new(0x84u);
    if ( v15 != nullptr )
    {
      v38 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v15);
      *(uint32_t *)v15 = &nengine::CNButton::`vftable';
      sub_69C780((int)v15);
      sub_69C7B0((int)v15, v38, v14, v14, v14 + 1, v14, 0, 0);
    }
    else
    {
      v15 = nullptr;
    }
    *v42 = v15;
    v14 += 2;
    ++v42;
  }
  while ( v14 < 8 );
  v16 = operator new(0x88u);
  if ( v16 != nullptr )
  {
    v39 = *(uint32_t *)(this + 180);
    sub_426BD0(v16);
    *(uint32_t *)v16 = &nengine::CNSlider::`vftable';
    sub_69CA20((int)v16);
    sub_69CA50((int)v16, v39, 38, 39);
    *(uint32_t *)v16 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v16 = nullptr;
  }
  *(uint32_t *)(this + 100) = v16;
  v17 = operator new(0x74u);
  if ( v17 != nullptr )
  {
    Block = *(void **)(this + 92);
    v40 = *(uint32_t **)(this + 100);
    v43 = *(uint32_t *)(this + 96);
    sub_426BD0(v17);
    *(uint32_t *)v17 = &nengine::CNScroll::`vftable';
    sub_69C5D0(v17);
    *(uint32_t *)v17 = &nengine::CNVScroll::`vftable';
    sub_69C5D0(v17);
    sub_69CD70((int)v17, (int)Block, v43, v40);
    v18 = v17;
  }
  else
  {
    v18 = nullptr;
  }
  *(uint32_t *)(this + 104) = v18;
  sub_69A5F0(v18, 256, 211);
  sub_69A840(*(uint32_t **)(this + 4), *(uint32_t *)(this + 104));
  v19 = operator new(0x6Cu);
  v20 = v19;
  if ( v19 != nullptr )
  {
    sub_426BD0(v19);
    *v20 = &nengine::CNTextBox::`vftable';
    sub_69C2D0(v20);
    sub_69C520((int)v20, 220, 2048);
    v21 = (int)v20;
  }
  else
  {
    v21 = 0;
  }
  *(uint32_t *)(this + 108) = v21;
  sub_69C420(v21, 6);
  sub_69C3E0(*(uint32_t *)(this + 108), 3);
  sub_69C4C0(*(uint32_t **)(this + 108), dword_99FCCC);
  sub_69A5F0(*(uint32_t **)(this + 108), 27, 231);
  sub_69A840(*(uint32_t **)(this + 4), *(uint32_t *)(this + 108));
  v22 = operator new(0x84u);
  if ( v22 != nullptr )
  {
    Blocka = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
    sub_426BD0(v22);
    *(uint32_t *)v22 = &nengine::CNButton::`vftable';
    sub_69C780((int)v22);
    sub_69C7B0((int)v22, (int)Blocka, 11, 12, 13, 11, 0, 0);
  }
  else
  {
    v22 = nullptr;
  }
  *(uint32_t *)(this + 112) = v22;
  sub_69A5F0(v22, 221, 353);
  sub_69A840(*(uint32_t **)(this + 4), *(uint32_t *)(this + 112));
  v23 = operator new(0x84u);
  if ( v23 != nullptr )
  {
    Blockb = *(void **)(this + 180);
    sub_426BD0(v23);
    *(uint32_t *)v23 = &nengine::CNButton::`vftable';
    sub_69C780((int)v23);
    sub_69C7B0((int)v23, (int)Blockb, 8, 9, 10, 17, 0, 0);
    v24 = v23;
  }
  else
  {
    v24 = nullptr;
  }
  *(uint32_t *)(this + 116) = v24;
  sub_69A5F0(v24, 105, 337);
  sub_69A840(*(uint32_t **)(this + 4), *(uint32_t *)(this + 116));
  v25 = operator new(0x84u);
  if ( v25 != nullptr )
  {
    Blockc = *(void **)(this + 180);
    sub_426BD0(v25);
    *(uint32_t *)v25 = &nengine::CNButton::`vftable';
    sub_69C780((int)v25);
    sub_69C7B0((int)v25, (int)Blockc, 14, 15, 16, 14, 0, 0);
  }
  else
  {
    v25 = nullptr;
  }
  *(uint32_t *)(this + 120) = v25;
  sub_69A5F0(v25, 105, 337);
  sub_69A840(*(uint32_t **)(this + 4), *(uint32_t *)(this + 120));
  v26 = operator new(0x84u);
  if ( v26 != nullptr )
  {
    Blockd = *(void **)(this + 180);
    sub_426BD0(v26);
    *(uint32_t *)v26 = &nengine::CNButton::`vftable';
    sub_69C780((int)v26);
    sub_69C7B0((int)v26, (int)Blockd, 11, 12, 13, 18, 0, 0);
    v27 = v26;
  }
  else
  {
    v27 = nullptr;
  }
  *(uint32_t *)(this + 124) = v27;
  *((uint32_t *)v27 + 17) = this;
  sub_69A5F0(*(uint32_t **)(this + 124), 105, 337);
  sub_69A840(*(uint32_t **)(this + 4), *(uint32_t *)(this + 124));
  sub_69A5F0(*(uint32_t **)(this + 4), 29, 63);
  *(uint8_t *)(this + 128) = 0;
  *(uint8_t *)(this + 129) = 0;
  *(uint8_t *)(this + 130) = 0;
  *(uint8_t *)(this + 131) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 6;
  *(uint32_t *)(this + 148) = 12;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 1600;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 176) = dword_99FCCC;
  *(uint32_t *)(this + 132) = -14931922;
  *(uint32_t *)(this + 156) = 184;
  *(uint32_t *)(this + 140) = 1;
  v28 = operator new(0x68u);
  if ( v28 != nullptr )
    v29 = sub_426BD0(v28);
  else
    v29 = nullptr;
  *(uint32_t *)(this + 204) = v29;
  *((uint32_t *)v29 + 17) = this;
  sub_69A840(*(uint32_t **)(this + 4), *(uint32_t *)(this + 204));
  result = operator new(0x44u);
  v31 = result;
  if ( result != nullptr )
  {
    result[8] = 0;
    *((uint32_t *)result + 1) = &off_6C2B88;
    *((uint32_t *)result + 3) = 0;
    result[16] = 1;
    result[18] = 0;
    result[17] = 0;
    *((uint32_t *)result + 7) = 0;
    *((uint32_t *)result + 6) = 0;
    *((uint32_t *)result + 5) = 0;
    sub_50EAD0(result);
    result = (uint8_t *)sub_50F1C0(nullptr, 132, 1);
    *(uint32_t *)(this + 212) = v31;
  }
  else
  {
    *(uint32_t *)(this + 212) = 0;
  }
  return result;
}


// ------------------------------------------------------------
// 0x552810 sub_552810 —— 打字机辅助（468BA0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_552810(int **this, int a2)
{
  uint32_t *result; // eax

  result = (uint32_t *)sub_468BA0(this + 47, &a2);
  *result = a2;
  return result;
}



// ------------------------------------------------------------
// 0x552830 sub_552830 —— 打字机辅助 2（468BA0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_552830(int **this, int a2)
{
  uint32_t *result; // eax

  result = (uint32_t *)sub_468BA0(this + 50, &a2);
  *result = a2;
  return result;
}



// ------------------------------------------------------------
// 0x552850 CNRDQuestInfoWindow__vmt8 —— CNRDQuestInfoWindow__vmt8 Update（140 行：CLICK_BUTTON2/LETTER_FADE_IN_01/WINDOW_CLOSE + 5518A0 打字机 + 69C6A0/69C680/69C690/69C400 + 552830/552810/5515A0 + 69C340/69C440/69C360 + 47B560/47B9E0/44AB50）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_552850(void *this)
{
  uint8_t *result; // eax
  const char *v3; // eax
  int v4; // edi
  int v5; // eax
  double v6; // st7
  const char *v7; // ebx
  size_t v8; // edi
  int v9; // ebx
  int v10; // eax
  const char *v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  unsigned int v17; // ecx
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  float v24; // [esp+0h] [ebp-1Ch]
  int v25; // [esp+8h] [ebp-14h]
  int v26; // [esp+18h] [ebp-4h]

  if ( *((uint32_t *)this + 4) == 0 )
    return (uint8_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 44))(this);
  if ( *((uint8_t *)this + 28) != 0 )
  {
    v3 = *((const char **)this + 6);
    if ( *((uint32_t *)this + 15) == strlen(v3) )
    {
      v12 = 0;
      if ( sub_699000((int)this + 32) > 200
        && (v13 = sub_699000((int)this + 32), (v12 = (uint64_t)sub_4049C0(0.0, 255.0, v13 - 200, 1000)) == 255) )
      {
        sub_5518A0(0);
        v14 = sub_69C6A0(*((uint32_t **)this + 21));
        sub_69C680(v14);
        v15 = sub_69C690(*((uint32_t *)this + 21));
        sub_69C400(v15);
        v25 = **((uint32_t **)this + 4);
        if ( *(uint8_t *)(*((uint32_t *)this + 31) + 16) != 0 )
          sub_552830(v25);
        else
          sub_552810(v25);
      }
      else if ( v12 != *((uint32_t *)this + 17) )
      {
        sub_69C340(-1);
        sub_69C440(((uint8_t)v12 << 24) | 0xBEE9F9);
        v16 = *((uint32_t *)this + 4);
        v17 = *(uint32_t *)(v16 + 84);
        v18 = v16 + 60;
        if ( v17 < 0x10 )
          sub_69C360(v18 + 4, 0);
        else
          sub_69C360(*(uint32_t *)(v18 + 4), 0);
        *((uint32_t *)this + 17) = v12;
      }
    }
    else
    {
      v26 = strlen(v3);
      v4 = *((uint32_t *)this + 16);
      v5 = sub_699000((int)this + 32);
      v24 = (float)v26;
      v6 = sub_4049C0(0.0, v24, v5, v4);
      v7 = *((const char **)this + 6);
      v8 = sub_5515A0(v7, (uint64_t)v6);
      if ( *((uint32_t *)this + 15) != v8 )
      {
        strncpy(byte_9B8068, v7, v8);
        byte_9B8068[v8] = 0;
        sub_69C340(-1);
        sub_69C360(byte_9B8068, 0);
        v9 = sub_69C500(*((uint32_t *)this + 22));
        v10 = sub_69C3A0(*((uint32_t *)this + 22));
        sub_69C400((v9 - v10) & ((v9 - v10 <= 0) - 1));
        v11 = *((const char **)this + 6);
        *((uint32_t *)this + 15) = v8;
        if ( v8 == strlen(v11) )
        {
          sub_432EE0(5);
          sub_432EA0("LETTER_FADE_IN_01", -1, 0, 0);
          *((uint8_t *)this + 45) = 0;
          *((uint8_t *)this + 46) = 0;
          sub_698F90((int)this + 32, 0, 0);
        }
      }
    }
  }
  else
  {
    v19 = sub_69C690(*((uint32_t *)this + 21));
    sub_69C400(v19);
    v20 = sub_69C690(*((uint32_t *)this + 26));
    sub_69C400(v20);
  }
  v21 = *((uint32_t *)this + 29);
  if ( *(uint8_t *)(v21 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v21 + 12) )
  {
    sub_47B560(**((uint32_t **)this + 4));
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 44))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    sub_432EA0("WINDOW_CLOSE", -1, 0, 0);
  }
  v22 = *((uint32_t *)this + 30);
  if ( *(uint8_t *)(v22 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v22 + 12) )
  {
    sub_44E8D0(*((char **)this + 2), (void *)0x26, *((uint32_t *)this + 4), 0);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v23 = *((uint32_t *)this + 31);
  if ( *(uint8_t *)(v23 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v23 + 12) )
  {
    sub_47B9E0(**((uint32_t **)this + 4));
    if ( *(uint32_t *)(*((uint32_t *)this + 4) + 296) == 1 )
      sub_44AB50(1, 12);
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 44))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    sub_432EA0("WINDOW_CLOSE", -1, 0, 0);
  }
  result = *((uint8_t **)this + 28);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 44))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    return sub_432EA0("WINDOW_CLOSE", -1, 0, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x552BD0 sub_552BD0 —— 任务文本装配（246 行：44AB50/432EE0/44CA70/429830 + 4F33A0/4F2CE0/4F2D60/4F2DF0/4F2DA0 + 459700/45A340/477AF0 奖励文本 + 463F10/551CE0/472E30/56CFE0/5518A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_552BD0(uint32_t *this, int a2)
{
  int result; // eax
  int v3; // esi
  uint32_t *v4; // ebx
  int v5; // edi
  bool v6; // zf
  int v7; // eax
  int v8; // ecx
  unsigned int v9; // eax
  int v10; // eax
  int v11; // esi
  size_t v12; // ebx
  char *v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  uint32_t *v17; // edi
  unsigned int v18; // esi
  int v19; // edi
  int v20; // eax
  uint32_t *v21; // edx
  int v22; // eax
  int v23; // eax
  unsigned int v24; // ecx
  int v25; // eax
  int v26; // eax
  int v27; // eax
  unsigned int v28; // ecx
  int v29; // esi
  unsigned int v30; // ecx
  int v31; // edx
  int v32; // eax
  unsigned int v33; // edi
  int i; // ebx
  int v35; // eax
  char v36; // [esp-4h] [ebp-60h]
  uint8_t *v37; // [esp+Ch] [ebp-50h] BYREF
  uint32_t *v38; // [esp+10h] [ebp-4Ch]
  uint32_t *v39; // [esp+14h] [ebp-48h]
  uint32_t v40[2]; // [esp+18h] [ebp-44h] BYREF
  size_t v41[12]; // [esp+20h] [ebp-3Ch] BYREF
  int v42; // [esp+58h] [ebp-4h]

  result = dword_796E50;
  v3 = a2;
  v4 = this;
  v5 = 0;
  v6 = a2 == 0;
  v41[11] = dword_796E50;
  v38 = this;
  *(this + 4) = a2;
  if ( v6 )
  {
    if ( *(uint32_t *)(*(this + 2) + 104) == 8 )
      return sub_44AB50(0, 12);
    return result;
  }
  sub_432EE0(5);
  sub_44CA70(v4 + 46);
  v4[50] = 0;
  v7 = *(uint32_t *)(v3 + 296);
  if ( v7 != 0 )
  {
    if ( v7 == 1 )
    {
      v15 = sub_429830((uint16_t)word_77F804);
      v4[50] = sub_418DD0((uint32_t *)v4[45], **(uint32_t **)(v3 + 304) + 4 * *(uint32_t *)(v15 + 44) + 45);
    }
  }
  else
  {
    v8 = *(uint32_t *)(v3 + 304);
    if ( v8 != 0 )
      v9 = (*(uint32_t *)(v3 + 308) - v8) >> 2;
    else
      v9 = 0;
    v39 = (uint32_t *)(v9 >> 1);
    if ( v9 >> 1 != 0 )
    {
      while ( 1 )
      {
        v10 = *(uint32_t *)(v3 + 304);
        v11 = *(uint32_t *)(v10 + 8 * v5);
        v12 = *(uint32_t *)(v10 + 8 * v5 + 4);
        sub_459700(v40);
        v42 = 0;
        v40[0] = v11;
        v40[1] = sub_4F33A0(v11);
        v13 = (char *)sub_4F2CE0(v11);
        v37 = v13 + 1;
        sub_4015C0(v41, v13, strlen(v13));
        v41[8] = v12;
        v14 = sub_4F2D60(v11);
        v41[7] = sub_4F2DF0(v14);
        v41[9] = sub_4F2DA0(v11);
        sub_45A340(v40);
        v42 = -1;
        sub_477AF0(v40);
        if ( ++v5 >= (int)v39 )
          break;
        v3 = a2;
      }
      v4 = v38;
    }
  }
  v16 = *(uint32_t *)(dword_8F8540 + 8);
  v17 = *(uint32_t **)(v4[2] + 84);
  v18 = 0;
  v39 = v17;
  LOBYTE(v38) = 0;
  if ( v16 != 0 )
    a2 = (*(uint32_t *)(dword_8F8540 + 12) - v16) / 20;
  else
    a2 = 0;
  if ( a2 > 0 )
  {
    v19 = *(uint32_t *)(dword_8F8540 + 8);
    v37 = nullptr;
    while ( 1 )
    {
      v20 = v19 != 0 && v18 < (*(uint32_t *)(dword_8F8540 + 12) - v19) / 20
          ? *(uint32_t *)&v37[*(uint32_t *)(dword_8F8540 + 8)]
          : 0;
      if ( v20 == v4[4] )
        break;
      ++v18;
      v37 += 20;
      if ( (int)v18 >= a2 )
        goto LABEL_36;
    }
    result = sub_463F10(v18);
    if ( result == -1 )
    {
      v4[4] = 0;
      return result;
    }
    v21 = (uint32_t *)v39[5];
    if ( v21 != nullptr && v39[4] == 1 && *v21 == *(uint32_t *)(v4[4] + 128) && result == 0 )
    {
      *(uint8_t *)(v4[29] + 16) = 0;
      *(uint8_t *)(v4[30] + 16) = 0;
      *(uint8_t *)(v4[31] + 16) = 1;
      if ( (uint8_t)sub_551CE0(*(uint32_t *)v4[4]) == 0 )
        LOBYTE(v38) = 1;
    }
    else
    {
      *(uint8_t *)(v4[29] + 16) = 0;
      *(uint8_t *)(v4[30] + 16) = 1;
      *(uint8_t *)(v4[31] + 16) = 0;
    }
LABEL_36:
    v17 = v39;
  }
  if ( v18 == a2 )
  {
    *(uint8_t *)(v4[29] + 16) = 1;
    *(uint8_t *)(v4[30] + 16) = 0;
    *(uint8_t *)(v4[31] + 16) = 0;
    a2 = *(uint32_t *)v4[4];
    if ( *(uint32_t *)sub_472E30(&v37, &a2) == v17[48] )
      LOBYTE(v38) = 1;
  }
  v22 = v4[31];
  v4[52] = -1;
  if ( *(uint8_t *)(v22 + 16) == 0 )
  {
    v4[5] = sub_56CFE0(*(uint32_t *)(v4[4] + 124));
    v27 = v4[4];
    v28 = *(uint32_t *)(v27 + 56);
    v25 = v27 + 32;
    if ( v28 >= 0x10 )
    {
      v26 = *(uint32_t *)(v25 + 4);
      goto LABEL_46;
    }
LABEL_45:
    v26 = v25 + 4;
    goto LABEL_46;
  }
  v4[5] = sub_56CFE0(*(uint32_t *)(v4[4] + 128));
  v23 = v4[4];
  v24 = *(uint32_t *)(v23 + 112);
  v25 = v23 + 88;
  if ( v24 < 0x10 )
    goto LABEL_45;
  v26 = *(uint32_t *)(v25 + 4);
LABEL_46:
  v36 = (char)v38;
  v4[6] = v26;
  sub_5518A0(v36);
  result = v17[42];
  if ( result != 0 )
    v29 = (v17[43] - result) >> 2;
  else
    v29 = 0;
  v30 = 0;
  a2 = v29;
  if ( v29 > 0 )
  {
    v31 = v17[42];
    while ( 1 )
    {
      result = v31 != 0 && v30 < (v17[43] - v31) >> 2 ? *(uint32_t *)(v17[42] + 4 * v30) : 0;
      v29 = a2;
      if ( result == v4[4] )
        break;
      if ( (int)++v30 >= a2 )
        goto LABEL_59;
    }
    v17[45] = v30;
  }
LABEL_59:
  if ( v30 == v29 )
  {
    v32 = *(uint32_t *)(dword_8F8540 + 8);
    a2 = v32 != 0 ? (*(uint32_t *)(dword_8F8540 + 12) - v32) / 20 : 0;
    result = a2;
    v33 = 0;
    if ( a2 > 0 )
    {
      v38 = (uint32_t *)v4[4];
      for ( i = 0; ; i += 20 )
      {
        v35 = *(uint32_t *)(dword_8F8540 + 8);
        if ( v35 != 0 && v33 < (*(uint32_t *)(dword_8F8540 + 12) - v35) / 20 )
          result = *(uint32_t *)(i + *(uint32_t *)(dword_8F8540 + 8));
        else
          result = 0;
        if ( (uint32_t *)result == v38 )
          break;
        result = a2;
        if ( (int)++v33 >= a2 )
          return result;
      }
      v39[45] = v33 + 1000;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x553040 sub_553040 —— 23 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_553040(uint32_t *this)
{
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 4) = 2;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 40) = 0;
  *(this + 45) = -1;
  *(this + 46) = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x553080 sub_553080 —— 任务数据（56 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_553080(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  uint32_t *v4; // edi
  int i; // ebx
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  uint32_t *v7; // edi
  int j; // ebx
  void (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v10)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  *(this + 1) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(this + 6) = 0;
  v4 = this + 7;
  for ( i = 2; i != 0; --i )
  {
    if ( *v4 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v4)(*v4, 1);
    *v4++ = 0;
  }
  v6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( v6 != nullptr )
    (**v6)(v6, 1);
  *(this + 9) = 0;
  v7 = this + 10;
  for ( j = 2; j != 0; --j )
  {
    if ( *v7 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v7)(*v7, 1);
    *v7++ = 0;
  }
  v9 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  if ( v9 != nullptr )
    (**v9)(v9, 1);
  v10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  result = 0;
  *(this + 12) = 0;
  if ( v10 != nullptr )
    result = (**v10)(v10, 1);
  *(this + 13) = 0;
  return result;
}



// ============================================================
// 【分区 5】任务列表窗 CNRDQuestListWindow（0x553130-0x553B70）
// vmt0 构造（319 行，MOUSE_OVER 悬停标签）；vmt8 Update（CLICK_BUTTON1/
// CLICK_BUTTON2/WINDOW_CLOSE）。
// ============================================================
// ------------------------------------------------------------
// 0x553130 CNRDQuestListWindow__vmtC —— CNRDQuestListWindow__vmtC 打开槽（15 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNRDQuestListWindow__vmtC(uint32_t *this)
{
  bool result; // al

  result = true;
  if ( *(this + 4) == 1 )
    return *(this + 5) != 0;
  return result;
}



// ------------------------------------------------------------
// 0x553150 CNRDQuestListWindow__vmt10 —— CNRDQuestListWindow__vmt10 状态切换槽（44AB50）
// ------------------------------------------------------------
int /*thiscall*/ CNRDQuestListWindow__vmt10(uint32_t *this)
{
  int result; // eax

  *(this + 5) = 0;
  if ( *((uint32_t *)dword_8F8528 + 26) == 8 )
    return sub_44AB50(dword_8F8528, 0, 12);
  return result;
}



// ------------------------------------------------------------
// 0x553170 sub_553170 —— 任务列表数据（69C690，47 行）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_553170(uint32_t *this)
{
  int v2; // ebx
  int i; // edi
  int v4; // eax
  int v5; // edx
  unsigned int result; // eax
  int v7; // esi
  int v8; // edi
  int j; // ecx
  int v10; // eax
  LONG y; // [esp+10h] [ebp-8h]
  LONG x; // [esp+14h] [ebp-4h]

  x = pt.x;
  y = pt.y;
  v2 = 177;
  for ( i = 0; i < 3; ++i )
  {
    v4 = sub_69C690(*(this + 13));
    v5 = *(this + 42);
    result = i + v4;
    if ( v5 == 0 || result >= (*(this + 43) - v5) >> 2 )
      break;
    if ( x >= 345 && x < 570 && y >= v2 && y < v2 + 26 )
      return result;
    v2 += 29;
  }
  v7 = *(uint32_t *)(dword_8F8540 + 8);
  v8 = 308;
  for ( j = 0; ; ++j )
  {
    v10 = v7 != 0 ? (*(uint32_t *)(dword_8F8540 + 12) - v7) / 20 : 0;
    if ( j >= v10 )
      break;
    if ( x >= 345 && x < 584 && y >= v8 && y < v8 + 26 )
      return j + 1000;
    v8 += 29;
  }
  return -1;
}



// ------------------------------------------------------------
// 0x553260 CNRDQuestListWindow__vmt8 —— CNRDQuestListWindow__vmt8 Update（115 行：CLICK_BUTTON1/CLICK_BUTTON2/WINDOW_CLOSE + 69C380/69C400/69C3A0/69C500 + 463ED0/552BD0/44BBA0）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDQuestListWindow__vmt8(uint32_t *this)
{
  uint32_t *v1; // esi
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // edi
  unsigned int v6; // edi
  int v7; // eax
  int v8; // eax
  signed int v9; // eax
  uint32_t *v10; // ecx
  int v11; // eax
  uint8_t *result; // eax
  int v13; // edi
  int v14; // ecx
  unsigned int v15; // ebx
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int v19; // esi
  int v20; // eax
  unsigned int v21; // ecx
  int v22; // eax
  int v23; // eax
  int v25; // [esp+Ch] [ebp-4h]

  v1 = this;
  v2 = *(this + 7);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) && sub_69C380(*(this + 9)) != 0 )
  {
    v3 = sub_69C380(v1[9]);
    sub_69C400(v3 - 1);
  }
  v4 = v1[8];
  if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
  {
    v5 = sub_69C380(v1[9]);
    v6 = sub_69C3A0(v1[9]) + v5;
    if ( v6 < sub_69C500(v1[9]) )
    {
      v7 = sub_69C380(v1[9]);
      sub_69C400(v7 + 1);
    }
  }
  v8 = v1[1];
  if ( *(uint8_t *)(v8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v8 + 12) )
  {
    v9 = sub_553170(v1);
    if ( v9 != -1 && v9 != v1[45] )
    {
      if ( v9 >= 1000 )
      {
        v11 = sub_463ED0((uint32_t *)dword_8F8540, v9 - 1000);
        v10 = *((uint32_t **)dword_8F8528 + 22);
      }
      else
      {
        v10 = *((uint32_t **)dword_8F8528 + 22);
        v11 = *(uint32_t *)(v1[42] + 4 * v9);
      }
      sub_552BD0(v10, v11);
      sub_44BBA0(dword_8F8528, 8, 0);
      sub_432EA0("CLICK_BUTTON1", -1, 0, 0);
    }
  }
  result = (uint8_t *)v1[6];
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    if ( v1[4] == 1 )
    {
      v13 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);
      v14 = *(uint32_t *)(v13 + 8);
      v15 = 0;
      v25 = v14 != 0 ? (*(uint32_t *)(v13 + 12) - v14) >> 2 : 0;
      if ( v25 > 0 )
      {
        while ( 1 )
        {
          v16 = *(uint32_t *)(v13 + 8);
          if ( v16 != 0 && v15 < (*(uint32_t *)(v13 + 12) - v16) >> 2 )
            v17 = *(uint32_t *)(v16 + 4 * v15);
          else
            v17 = 0;
          v18 = __RTDynamicCast(v17, 0, &CNRDObject `RTTI Type Descriptor', &CNRDNpc `RTTI Type Descriptor', 0);
          v19 = v18;
          if ( v18 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 340))(v18) == *(this + 5) )
            break;
          if ( (int)++v15 >= v25 )
            goto LABEL_36;
        }
        v20 = *(this + 5);
        v21 = *(uint32_t *)(v20 + 180);
        v22 = v20 + 156;
        if ( v21 < 0x10 )
          v23 = v22 + 4;
        else
          v23 = *(uint32_t *)(v22 + 4);
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)v19 + 212))(v19, v23, -1, 0, 0);
LABEL_36:
        v1 = this;
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t *))(*v1 + 44))(v1);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    return sub_432EA0("WINDOW_CLOSE", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x553490 CNRDQuestListWindow__vmt0 —— CNRDQuestListWindow__vmt0 构造（319 行：553170 + 432EA0 MOUSE_OVER + 422E70/418DD0/69C690/47C210 + 491530/491630/47B470/463F10/468FC0/4049C0/56CFE0）
// ------------------------------------------------------------
int /*userpurge*/ sub_553490@<eax>(uint32_t *a1@<ecx>, int a2@<esi>, int a3)
{
  int v4; // ecx
  int result; // eax
  int v6; // eax
  int v7; // esi
  int v8; // eax
  unsigned int v9; // ecx
  int v10; // eax
  int v11; // eax
  const char *v12; // eax
  int v13; // esi
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // ebx
  int v18; // eax
  int v19; // ecx
  unsigned int v20; // esi
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  unsigned int v26; // ecx
  int v27; // eax
  int v28; // eax
  int v29; // esi
  int v30; // ecx
  int v31; // eax
  unsigned int v32; // edx
  uint32_t *v33; // ecx
  int v34; // eax
  int v35; // eax
  int v36; // ebx
  int v37; // eax
  bool v38; // cc
  int v39; // ecx
  int v40; // eax
  unsigned int v41; // ebx
  int v42; // esi
  int v43; // eax
  int v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // edx
  double v48; // st7
  int v49; // eax
  int v50; // eax
  int v51; // eax
  int v52; // eax
  int v53; // eax
  int v54; // eax
  int v55; // ecx
  int v56; // eax
  int v57; // eax
  const char *v58; // eax
  int v59; // esi
  uint32_t *v60; // eax
  int v61; // ebx
  int v62; // eax
  int v63; // [esp-Ch] [ebp-ACh]
  int v64; // [esp-Ch] [ebp-ACh]
  int v65; // [esp-Ch] [ebp-ACh]
  uint32_t *v66; // [esp-Ch] [ebp-ACh]
  int v68; // [esp+4h] [ebp-9Ch]
  int v69; // [esp+8h] [ebp-98h]
  int v70; // [esp+Ch] [ebp-94h]
  int v71; // [esp+10h] [ebp-90h]
  int v72; // [esp+14h] [ebp-8Ch]
  int v73; // [esp+14h] [ebp-8Ch]
  uint32_t *v74; // [esp+18h] [ebp-88h]
  char v75[64]; // [esp+1Ch] [ebp-84h] BYREF
  char Buffer[64]; // [esp+5Ch] [ebp-44h] BYREF
  int v77; // [esp+9Ch] [ebp-4h]
  int v78; // [esp+A8h] [ebp+8h]
  unsigned int v79; // [esp+A8h] [ebp+8h]

  v4 = a1[1];
  v77 = dword_796E50;
  result = a3;
  if ( a3 == v4 )
  {
    v6 = sub_553170(a1);
    v7 = v6;
    v70 = v6;
    if ( v6 != a1[46] )
    {
      if ( v6 != -1 )
        sub_432EA0("MOUSE_OVER", -1, 0, 0);
      a1[46] = v7;
    }
    if ( a1[4] == 1 )
    {
      v8 = a1[5];
      v9 = *(uint32_t *)(v8 + 28);
      v10 = v8 + 4;
      if ( v9 < 0x10 )
        v11 = v10 + 4;
      else
        v11 = *(uint32_t *)(v10 + 4);
      v63 = v11;
      v12 = (const char *)sub_422E70(461);
      sprintf(Buffer, v12, v63);
      v13 = 465
          - ((*(int (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, Buffer, a2) + 20)
          / 2;
      v14 = sub_418DD0(22);
      if ( v14 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 152))(v14, v13, 80, dword_79C0B0);
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 14);
      (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v13 + 20,
        82,
        -3742223,
        Buffer);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v15 = a1[5];
      if ( *(uint32_t *)(v15 + 60) != 0 )
      {
        v16 = *(uint32_t *)(v15 + 68);
        if ( v16 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v16 + 152))(v16, 350, 107, dword_79C0B0);
      }
      v17 = 0;
      v78 = 179;
      v72 = 0;
      do
      {
        v18 = sub_69C690(a1[13]);
        v19 = a1[42];
        v20 = v17 + v18;
        if ( v19 == 0 || v20 >= (a1[43] - v19) >> 2 )
          break;
        v21 = 4 * v20;
        v22 = sub_47C210(*(uint32_t *)(v19 + 4 * v20));
        if ( v22 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v22 + 152))(v22, 350, v78, dword_79C0B0);
        v23 = sub_418DD0(42);
        if ( v23 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v23 + 152))(v23, 394, v78, dword_79C0B0);
        if ( a1[45] == v20 || v70 == v20 )
        {
          sub_491530(2, 0);
          v24 = sub_418DD0((a1[45] == v20) + 43);
          if ( v24 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v24 + 152))(v24, 394, v78, dword_79C0B0);
          sub_491630(2);
        }
        v25 = *(uint32_t *)(v21 + a1[42]);
        v26 = *(uint32_t *)(v25 + 28);
        v27 = v25 + 4;
        v28 = v26 < 0x10 ? v27 + 4 : *(uint32_t *)(v27 + 4);
        v29 = 481 - (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v28) / 2;
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
        v30 = a1[42];
        v31 = *(uint32_t *)(v30 + v21);
        v32 = *(uint32_t *)(v31 + 28);
        v33 = (uint32_t *)(v21 + v30);
        v34 = v31 + 4;
        v35 = v32 < 0x10 ? v34 + 4 : *(uint32_t *)(v34 + 4);
        v36 = *(uint32_t *)dword_79C0B0;
        v64 = v35;
        v37 = sub_47B470(*v33);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v36 + 80))(dword_79C0B0, v29, v78 + 6, v37, v64);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v17 = v72 + 1;
        v38 = ++v72 < 3;
        v78 += 29;
      }
      while ( v38 );
    }
    v39 = dword_8F8540;
    v40 = *(uint32_t *)(dword_8F8540 + 8);
    v41 = 0;
    v42 = 310;
    v69 = 310;
    if ( v40 != 0 )
      v73 = (*(uint32_t *)(dword_8F8540 + 12) - v40) / 20;
    else
      v73 = 0;
    v79 = 0;
    if ( v73 > 0 )
    {
      v71 = 0;
      while ( 1 )
      {
        v43 = *(uint32_t *)(v39 + 8);
        if ( v43 != 0 && v41 < (*(uint32_t *)(v39 + 12) - v43) / 20 )
          v74 = *(uint32_t **)(v71 + *(uint32_t *)(v39 + 8));
        else
          v74 = nullptr;
        v44 = sub_463F10(v41);
        v68 = v44;
        if ( v44 != -1 )
          break;
        v45 = *(uint32_t *)(a1[2] + 16);
        if ( *(uint32_t *)(v45 + 568) != v41 || *(int *)(*(uint32_t *)(v45 + 580) + 148) < 5 )
          goto LABEL_49;
LABEL_84:
        ++v41;
        v42 += 29;
        v79 = v41;
        v71 += 20;
        v69 = v42;
        if ( (int)v41 >= v73 )
          return sub_468FC0(2);
        v39 = dword_8F8540;
      }
      if ( v44 > 0 )
      {
        v53 = sub_47C210(v74);
        if ( v53 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v53 + 152))(v53, 350, v42, dword_79C0B0);
      }
      else
      {
LABEL_49:
        v46 = sub_418DD0(31);
        if ( v46 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v46 + 152))(v46, 350, v42, dword_79C0B0);
        v47 = (int)timeGetTime() % 800;
        if ( v47 >= 400 )
          v48 = sub_4049C0(255.0, 0.0, v47 - 400, 400);
        else
          v48 = sub_4049C0(0.0, 255.0, v47, 400);
        v49 = sub_418DD0(32);
        if ( v49 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v49 + 128))(
            v49,
            350,
            v42,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)(uint64_t)v48 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        v41 = v79;
      }
      v50 = sub_418DD0(23);
      if ( v50 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v50 + 152))(v50, 394, v42, dword_79C0B0);
      if ( a1[45] - 1000 == v41 || v70 - 1000 == v41 )
      {
        sub_491530(2, 0);
        v51 = sub_418DD0(25 - (v41 != a1[45] - 1000));
        if ( v51 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v51 + 152))(v51, 394, v42, dword_79C0B0);
        sub_491630(2);
      }
      if ( v68 > 0 )
        v52 = v74[31];
      else
        v52 = v74[32];
      v54 = sub_56CFE0(v52);
      if ( v54 != 0 )
      {
        v55 = *(uint32_t *)(v54 + 68);
        if ( v55 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v55 + 152))(v55, 396, v42 + 2, dword_79C0B0);
      }
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 27);
      if ( v68 > 0 )
      {
        if ( v74[7] < 0x10u )
          v60 = v74 + 2;
        else
          v60 = (uint32_t *)v74[2];
        v61 = *(uint32_t *)dword_79C0B0;
        v66 = v60;
        v62 = sub_47B470(v74);
        (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(v61 + 80))(dword_79C0B0, 409, v42 + 6, v62, v66);
      }
      else
      {
        v56 = sub_56CFE0(v74[32]);
        if ( v56 == 0 )
        {
LABEL_83:
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
          goto LABEL_84;
        }
        if ( *(uint32_t *)(v56 + 28) < 0x10u )
          v57 = v56 + 8;
        else
          v57 = *(uint32_t *)(v56 + 8);
        v65 = v57;
        v58 = (const char *)sub_422E70(462);
        sprintf(v75, v58, v65);
        v59 = v42 + 6;
        (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          408,
          v59,
          -16525825,
          v75);
        (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          409,
          v59,
          -16525825,
          v75);
        v42 = v69;
      }
      v41 = v79;
      goto LABEL_83;
    }
    return sub_468FC0(2);
  }
  return result;
}


// ============================================================
// 【分区 6】任务文本与公告辅助（0x553B70-0x554320）
// 任务页绘制在 0x553B70（184 行）；任务 NPC 文本在 0x5540D0（96 行）。
// ============================================================
// ------------------------------------------------------------
// 0x553B70 sub_553B70 —— 任务页绘制（184 行：43C250/43C410/69A840 + 426BD0/69C780/69C7B0 + 69A5F0/69C2D0/69C520/69C440/69C420/69C3E0/69C4C0/69CA20/69CA50/69C5D0/69CD70）
// ------------------------------------------------------------
int /*thiscall*/ sub_553B70(int this)
{
  int v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int v5; // ebx
  uint8_t *v6; // edi
  uint8_t *v7; // eax
  uint32_t *v8; // edi
  int v9; // ebx
  uint32_t *v10; // ecx
  uint8_t *v11; // edi
  uint8_t *v12; // edi
  uint8_t *v13; // edi
  uint32_t *v14; // ecx
  int result; // eax
  void *Block; // [esp+10h] [ebp-18h]
  int v17; // [esp+14h] [ebp-14h]
  int v18; // [esp+14h] [ebp-14h]
  int v19; // [esp+14h] [ebp-14h]
  int v20; // [esp+14h] [ebp-14h]
  uint32_t *v21; // [esp+18h] [ebp-10h]
  uint32_t *v22; // [esp+18h] [ebp-10h]
  int v23; // [esp+18h] [ebp-10h]

  *(uint32_t *)(this + 160) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 40);
  if ( operator new(0x6Cu) != nullptr )
    v2 = sub_43C250(*(uint32_t *)(this + 160), 19);
  else
    v2 = 0;
  *(uint32_t *)(this + 4) = v2;
  *(uint32_t *)(v2 + 68) = this;
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 11, 12, 13, 11, 0, 0);
  else
    v4 = nullptr;
  *(uint32_t *)(this + 24) = v4;
  sub_69A840(v4);
  v5 = 2;
  v21 = (uint32_t *)(this + 28);
  do
  {
    v6 = operator new(0x84u);
    if ( v6 != nullptr )
    {
      v17 = *(uint32_t *)(this + 160);
      sub_426BD0(v6);
      *(uint32_t *)v6 = &nengine::CNButton::`vftable';
      sub_69C780(v6);
      sub_69C7B0(v17, v5 - 2, v5 - 1, v5, v5 + 1, 0, 0);
    }
    else
    {
      v6 = nullptr;
    }
    *v21 = v6;
    sub_69A840(v6);
    v5 += 4;
    ++v21;
  }
  while ( v5 < 10 );
  sub_69A5F0(*(uint32_t **)(this + 28), 232, 99);
  sub_69A5F0(*(uint32_t **)(this + 32), 247, 98);
  v7 = operator new(0x6Cu);
  v8 = v7;
  v9 = 4;
  if ( v7 != nullptr )
  {
    sub_426BD0(v7);
    *v8 = &nengine::CNTextBox::`vftable';
    sub_69C2D0(v8);
    sub_69C520(195, 2048);
    v10 = v8;
  }
  else
  {
    v10 = nullptr;
  }
  *(uint32_t *)(this + 36) = v10;
  sub_69C440(-3742223);
  sub_69C420(6);
  sub_69C3E0(3);
  sub_69C4C0(dword_99FCCC);
  sub_69A5F0(*(uint32_t **)(this + 36), 57, 46);
  sub_69A840(*(uint32_t *)(this + 36));
  v22 = (uint32_t *)(this + 40);
  do
  {
    v11 = operator new(0x84u);
    if ( v11 != nullptr )
    {
      v18 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v11);
      *(uint32_t *)v11 = &nengine::CNButton::`vftable';
      sub_69C780(v11);
      sub_69C7B0(v18, v9, v9, v9 + 1, v9, 0, 0);
    }
    else
    {
      v11 = nullptr;
    }
    *v22 = v11;
    v9 += 2;
    ++v22;
  }
  while ( v9 < 8 );
  v12 = operator new(0x88u);
  if ( v12 != nullptr )
  {
    v19 = *(uint32_t *)(this + 160);
    sub_426BD0(v12);
    *(uint32_t *)v12 = &nengine::CNSlider::`vftable';
    sub_69CA20(v12);
    sub_69CA50(v19, 45, 39);
    *(uint32_t *)v12 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v12 = nullptr;
  }
  *(uint32_t *)(this + 48) = v12;
  v13 = operator new(0x74u);
  if ( v13 != nullptr )
  {
    Block = *(void **)(this + 40);
    v20 = *(uint32_t *)(this + 48);
    v23 = *(uint32_t *)(this + 44);
    sub_426BD0(v13);
    *(uint32_t *)v13 = &nengine::CNScroll::`vftable';
    sub_69C5D0(v13);
    *(uint32_t *)v13 = &nengine::CNVScroll::`vftable';
    sub_69C5D0(v13);
    sub_69CD70(Block, v23, v20);
    v14 = v13;
  }
  else
  {
    v14 = nullptr;
  }
  *(uint32_t *)(this + 52) = v14;
  sub_69A5F0(v14, 252, 115);
  sub_69A840(*(uint32_t *)(this + 52));
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint8_t *)(this + 56) = 0;
  *(uint8_t *)(this + 57) = 0;
  *(uint8_t *)(this + 58) = 0;
  *(uint8_t *)(this + 59) = 0;
  *(uint32_t *)(this + 76) = 12;
  *(uint32_t *)(this + 84) = 1600;
  *(uint32_t *)(this + 72) = 6;
  *(uint32_t *)(this + 104) = dword_99FCCC;
  *(uint32_t *)(this + 60) = -14537421;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 128) = 12;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint8_t *)(this + 108) = 0;
  *(uint8_t *)(this + 109) = 0;
  *(uint8_t *)(this + 110) = 0;
  *(uint8_t *)(this + 111) = 0;
  *(uint32_t *)(this + 124) = 6;
  *(uint32_t *)(this + 136) = 1600;
  result = dword_99FCCC;
  *(uint32_t *)(this + 156) = dword_99FCCC;
  *(uint32_t *)(this + 136) = 180;
  *(uint32_t *)(this + 120) = 1;
  return result;
}


// ------------------------------------------------------------
// 0x553FB0 sub_553FB0 —— 任务 NPC 查询（47CC80/47CA40）
// ------------------------------------------------------------
void /*thiscall*/ sub_553FB0(int this)
{
  int *v2; // eax
  uint32_t *v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v8; // [esp+10h] [ebp-14h]
  int v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  v2 = *(int **)(this + 20);
  if ( v2 != nullptr )
  {
    v3 = sub_47CC80((int **)dword_8F8540, &v6, *v2);
    v10 = 0;
    sub_47CA40(this + 164, (int)v3);
    v10 = -1;
    if ( Block != nullptr )
      j__free(Block);
    v4 = *(uint32_t *)(this + 168);
    Block = nullptr;
    v8 = 0;
    v9 = 0;
    if ( v4 != 0 && (unsigned int)((*(uint32_t *)(this + 172) - v4) >> 2) > 3 )
    {
      v5 = *(uint32_t *)(this + 168);
      if ( v5 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 52) + 32))(
          *(uint32_t *)(this + 52),
          ((*(uint32_t *)(this + 172) - v5) >> 2) - 3);
      else
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 52) + 32))(*(uint32_t *)(this + 52), -3);
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 52) + 32))(*(uint32_t *)(this + 52), 0);
    }
  }
  else
  {
    if ( *(uint32_t *)(this + 168) != 0 )
      j__free(*(void **)(this + 168));
    *(uint32_t *)(this + 168) = 0;
    *(uint32_t *)(this + 172) = 0;
    *(uint32_t *)(this + 176) = 0;
  }
}



// ------------------------------------------------------------
// 0x5540D0 sub_5540D0 —— 任务 NPC 文本装配（69C730/69A5F0/56CFE0 + 69C340/69C360/69C400/69C500/69C3A0 + 553FB0/41CA60，96 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5540D0(int this, void *Block, int a3)
{
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  unsigned int v9; // ecx
  int v10; // eax
  int v11; // eax
  unsigned int v12; // edi
  uint32_t *v13; // ebx
  uint32_t *v14; // eax
  void *i; // ebx
  int v16; // edi
  uint32_t *v17; // esi
  uint32_t *result; // eax
  void *Blocka; // [esp+14h] [ebp+8h]

  sub_69C730(*(uint32_t *)(this + 160), (Block != (void *)1) + 19);
  v4 = *(uint32_t *)(this + 4);
  *(uint32_t *)(v4 + 28) = *(uint32_t *)(v4 + 28);
  *(uint32_t *)(v4 + 32) = Block != (void *)1 ? 153 : 353;
  sub_69A5F0(*(uint32_t **)(this + 4), 320, Block != (void *)1 ? 263 : 63);
  v5 = *(uint32_t *)(this + 4);
  v6 = *(uint32_t *)(v5 + 24);
  if ( Block == (void *)1 )
    v7 = v6 + 353;
  else
    v7 = v6 + 153;
  sub_69A5F0(*(uint32_t **)(this + 24), *(uint32_t *)(v5 + 20) + 51, v7);
  *(uint8_t *)(*(uint32_t *)(this + 28) + 16) = Block == (void *)1;
  *(uint8_t *)(*(uint32_t *)(this + 32) + 16) = Block == (void *)1;
  *(uint8_t *)(*(uint32_t *)(this + 36) + 16) = Block == (void *)1;
  *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = Block == (void *)1;
  *(uint32_t *)(this + 16) = Block;
  if ( a3 != -1 )
  {
    *(uint32_t *)(this + 20) = sub_56CFE0(a3);
    sub_69C340(-1);
    v8 = *(uint32_t *)(this + 20);
    v9 = *(uint32_t *)(v8 + 228);
    v10 = v8 + 204;
    if ( v9 < 0x10 )
      v11 = v10 + 4;
    else
      v11 = *(uint32_t *)(v10 + 4);
    sub_69C360(v11, 0);
    sub_69C400(0);
    v12 = sub_69C500(*(uint32_t *)(this + 36));
    if ( v12 > sub_69C3A0(*(uint32_t *)(this + 36)) )
    {
      *(uint8_t *)(*(uint32_t *)(this + 28) + 17) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 32) + 17) = 1;
    }
    else
    {
      *(uint8_t *)(*(uint32_t *)(this + 28) + 17) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 32) + 17) = 0;
    }
  }
  sub_553FB0(this);
  *(uint32_t *)(this + 184) = -1;
  v13 = *(uint32_t **)(*(uint32_t *)(this + 192) + 4);
  for ( Blocka = v13; *((uint8_t *)v13 + 21) == 0; Blocka = v13 )
  {
    sub_41CA60((void *)v13[2]);
    v13 = (uint32_t *)*v13;
    j__free(Blocka);
  }
  *(uint32_t *)(*(uint32_t *)(this + 192) + 4) = *(uint32_t *)(this + 192);
  v14 = *(uint32_t **)(this + 192);
  *(uint32_t *)(this + 196) = 0;
  *v14 = v14;
  *(uint32_t *)(*(uint32_t *)(this + 192) + 8) = *(uint32_t *)(this + 192);
  v16 = this + 200;
  v17 = *(uint32_t **)(*(uint32_t *)(this + 204) + 4);
  for ( i = v17; *((uint8_t *)v17 + 21) == 0; i = v17 )
  {
    sub_41CA60((void *)v17[2]);
    v17 = (uint32_t *)*v17;
    j__free(i);
  }
  *(uint32_t *)(*(uint32_t *)(v16 + 4) + 4) = *(uint32_t *)(v16 + 4);
  result = *(uint32_t **)(v16 + 4);
  *(uint32_t *)(v16 + 8) = 0;
  *result = result;
  *(uint32_t *)(*(uint32_t *)(v16 + 4) + 8) = *(uint32_t *)(v16 + 4);
  return result;
}



// ------------------------------------------------------------
// 0x5542C0 sub_5542C0 —— 窗口页数据（18 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5542C0(uint32_t *this)
{
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x5542F0 sub_5542F0 —— 窗口页数据 2（22 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5542F0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ============================================================
// 【分区 7】IRDPopupWindow 弹窗基类（0x554320-0x5544E0）
// vmt18/vmt34/vmt1C = 位置/尺寸/事件统一实现；0x554450=公共清理转发。
// ============================================================
// ------------------------------------------------------------
// 0x554320 IRDPopupWindow__vmt18 —— IRDPopupWindow__vmt18 位置槽（39 行）
// ------------------------------------------------------------
int /*thiscall*/ IRDPopupWindow__vmt18(uint32_t *this, int a2, int a3)
{
  int v3; // esi
  int v4; // edx
  int result; // eax
  int v6; // ecx
  int v7; // ecx

  *(this + 6) = a3;
  *(this + 5) = a2 + 1;
  v3 = *(this + 7);
  v4 = 4 * (3 * (a2 + 1) + 3);
  result = 13 * a3 + 12;
  if ( v3 == 2 )
  {
    v6 = *(this + 2);
    result = 13 * a3 + 18;
    *(uint32_t *)(v6 + 28) = v4 + 6;
    *(uint32_t *)(v6 + 32) = result;
  }
  else
  {
    if ( v3 == 3 )
    {
      v4 += 4;
      result = 13 * a3 + 16;
    }
    v7 = *(this + 2);
    *(uint32_t *)(v7 + 28) = v4;
    *(uint32_t *)(v7 + 32) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x554380 IRDPopupWindow__vmt34 —— IRDPopupWindow__vmt34 尺寸槽（44 行）
// ------------------------------------------------------------
void /*thiscall*/ IRDPopupWindow__vmt34(uint32_t *this, int a2, int a3)
{
  int v3; // edx
  int v4; // eax
  int v5; // esi
  int v6; // edx
  int v7; // ecx
  int v8; // ecx

  if ( a2 != 0 && a3 != 0 )
  {
    v3 = a2 % 12;
    if ( a2 % 12 != 0 )
      v3 = 1;
    *(this + 5) = v3 + a2 / 12;
    *(this + 6) = a3 / 13;
    v4 = *(this + 7);
    v5 = a3 + 12;
    v6 = a2 + 12;
    if ( v4 == 2 )
    {
      v7 = *(this + 2);
      *(uint32_t *)(v7 + 32) = a3 + 18;
      *(uint32_t *)(v7 + 28) = a2 + 18;
    }
    else
    {
      if ( v4 == 3 )
      {
        v6 = a2 + 16;
        v5 = a3 + 16;
      }
      v8 = *(this + 2);
      *(uint32_t *)(v8 + 28) = v6;
      *(uint32_t *)(v8 + 32) = v5;
    }
  }
}



// ------------------------------------------------------------
// 0x554400 IRDPopupWindow__vmt1C —— IRDPopupWindow__vmt1C 事件槽（36 行）
// ------------------------------------------------------------
int /*thiscall*/ IRDPopupWindow__vmt1C(uint32_t *this, int a2)
{
  int v2; // edx
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  v2 = 12 * (*(this + 5) + 1);
  result = 13 * *(this + 6) + 12;
  *(this + 7) = a2;
  if ( a2 == 2 )
  {
    v4 = *(this + 2);
    result += 6;
    *(uint32_t *)(v4 + 28) = v2 + 6;
    *(uint32_t *)(v4 + 32) = result;
  }
  else
  {
    if ( a2 == 3 )
    {
      v2 += 4;
      result += 4;
    }
    v5 = *(this + 2);
    *(uint32_t *)(v5 + 28) = v2;
    *(uint32_t *)(v5 + 32) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x554450 sub_554450 —— 弹窗清理转发（633590 window_party 数据清理）
// ------------------------------------------------------------
void /*thiscall*/ sub_554450(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDYesNoConfirmWindow;
  sub_633590((uint32_t *)this);
  if ( *(uint32_t *)(this + 68) >= 0x10u )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 68) = 15;
  *(uint32_t *)(this + 64) = 0;
  *(uint8_t *)(this + 48) = 0;
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 12) = 0;
}



// ============================================================
// 【分区 8】弹窗 vmt4 析构三件套注册表 A（0x5544E0-0x55A010）
// 每个窗口类一组：vmt4 标量删除析构 → sub_XXXX 数据清理（63xxxx 关闭回调
// → window_party.cpp 对应窗口）。覆盖 YesNo/SkillBuy/ItemSell/Delete/Repair/
// SealRemove/Popup/ResponsePeer/CharacterDelete/Notice/QuestGiveup/Walkout/
// PVPRoom/Option/Party/Friend/Member/Stamina/CashShop 系/Inform/Guild/
// DungeonInfo/MoveToHome/PrivateStoreBuy/MemberRemove/Upgrade/ItemBox/
// Reseal/WarRoom/Disjoint/Lottery/ItemBuy/DisjointResult/PlayDungeon/
// TradeResult/Compound/Dialogue/QuestReward/ClassChange/Recommend/FriendList/
// SeriasPresent 等约 45 个窗口类。
// ============================================================
// ------------------------------------------------------------
// 0x5544E0 CNRDYesNoConfirmWindow__vmt4 —— CNRDYesNoConfirmWindow__vmt4 标量删除析构（554450 转发）
// ------------------------------------------------------------
void */*thiscall*/ CNRDYesNoConfirmWindow__vmt4(void *Block, char a2)
{
  sub_554450((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x554510 sub_554510 —— 弹窗基件构造（418DD0，144 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_554510(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
  int v8; // edi
  uint32_t *v9; // esi
  uint32_t **v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // edi
  int k; // ebx
  int v25; // eax
  int result; // eax
  int v27; // [esp+Ch] [ebp-Ch]
  int i; // [esp+14h] [ebp-4h]
  int v30; // [esp+14h] [ebp-4h]
  unsigned int v31; // [esp+20h] [ebp+8h]
  int v32; // [esp+24h] [ebp+Ch]
  int j; // [esp+24h] [ebp+Ch]

  v8 = 0;
  v9 = nullptr;
  v31 = 0;
  if ( a5 != 0 )
  {
    if ( a5 == 1 )
    {
      v10 = (uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
      v31 = 134;
      v8 = 6;
    }
    else
    {
      if ( a5 == 2 )
      {
        v11 = *(uint32_t *)(dword_99FCC8 + 20);
        v31 = 26;
        v8 = 9;
      }
      else
      {
        if ( a5 != 3 )
          goto LABEL_11;
        v11 = *(uint32_t *)(dword_99FCC8 + 20);
        v31 = 35;
        v8 = 8;
      }
      v10 = (uint32_t **)(v11 + 116);
    }
  }
  else
  {
    v31 = 0;
    v10 = (uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
    v8 = 6;
  }
  v9 = *v10;
LABEL_11:
  v12 = sub_418DD0(v9, v31);
  if ( v12 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, a1, a2, dword_79C0B0);
  v13 = v8 + a1;
  v27 = v13;
  if ( a3 > 0 )
  {
    for ( i = a3; i != 0; --i )
    {
      v14 = sub_418DD0(v9, v31 + 1);
      if ( v14 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 152))(v14, v13, a2, dword_79C0B0);
      v13 += 12;
    }
  }
  v15 = sub_418DD0(v9, v31 + 2);
  if ( v15 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v15 + 152))(v15, v13, a2, dword_79C0B0);
  v16 = v8 + a2;
  v32 = v8 + a2;
  v30 = 0;
  if ( a4 > 0 )
  {
    do
    {
      v17 = sub_418DD0(v9, v31 + 3);
      if ( v17 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v17 + 152))(v17, a1, v16, dword_79C0B0);
      v18 = v27;
      if ( a3 > 0 )
      {
        for ( j = a3; j != 0; --j )
        {
          v19 = sub_418DD0(v9, v31 + 4);
          if ( v19 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v19 + 152))(v19, v18, v16, dword_79C0B0);
          if ( a5 == 1 && v30 == a7 )
          {
            v20 = sub_418DD0(v9, 0x90u);
            if ( v20 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v20 + 152))(v20, v18, v16 + 7, dword_79C0B0);
          }
          v18 += 12;
        }
      }
      v21 = sub_418DD0(v9, v31 + 5);
      if ( v21 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v21 + 152))(v21, v18, v16, dword_79C0B0);
      v16 += 13;
      ++v30;
    }
    while ( v30 < a4 );
    v32 = v16;
  }
  v22 = sub_418DD0(v9, v31 + 6);
  if ( v22 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v22 + 152))(v22, a1, v16, dword_79C0B0);
  v23 = v27;
  for ( k = 0; k < a3; v23 += 12 )
  {
    if ( a5 != 0 || a6 != k )
      v25 = sub_418DD0(v9, v31 + 7);
    else
      v25 = sub_418DD0(v9, 0xA1u);
    if ( v25 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v25 + 152))(v25, v23, v32, dword_79C0B0);
    ++k;
  }
  result = sub_418DD0(v9, v31 + 8);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(result, v23, v32, dword_79C0B0);
  return result;
}


// ------------------------------------------------------------
// 0x5547D0 sub_5547D0 —— 弹窗事件挂接（426BD0/69DDF0）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5547D0(uint8_t *this, int a2, int a3)
{
  sub_426BD0(this);
  *(uint32_t *)this = &vftbl_nengine__CNWindow;
  sub_69DDF0(this);
  nengine__CNFrame__vmt20(a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x554830 nengine__CNWindow__vmt0 —— nengine__CNWindow__vmt0 基类析构（554860）
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNWindow__vmt0(void *Block, char a2)
{
  sub_554860();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x554860 sub_554860 —— 窗口事件解挂（426C90）
// ------------------------------------------------------------
int /*thiscall*/ sub_554860(void **this)
{
  *this = &vftbl_nengine__CNWindow;
  nengine__CNWindow__vmt8();
  return sub_426C90(this);
}



// ------------------------------------------------------------
// 0x5548B0 sub_5548B0 —— 弹窗关闭回调调用（5547D0，22 行——vmt4 三件套的公共尾）
// ------------------------------------------------------------
int /*thiscall*/ sub_5548B0(uint32_t *this, int a2, int a3)
{
  uint8_t *v4; // eax
  uint8_t *v5; // eax

  v4 = operator new(0x6Cu);
  if ( v4 != nullptr )
    v5 = sub_5547D0(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 37);
  else
    v5 = nullptr;
  *(this + 2) = v5;
  *((uint32_t *)v5 + 17) = this;
  *(this + 4) = a2;
  *(this + 1) = a3;
  return a3;
}



// ------------------------------------------------------------
// 0x554930 IRDPopupWindow__vmt0 —— IRDPopupWindow__vmt0 构造（554510）
// ------------------------------------------------------------
int /*thiscall*/ IRDPopupWindow__vmt0(int *this, int a2)
{
  int result; // eax

  result = a2;
  if ( a2 == *(this + 2) )
    return sub_554510(*(uint32_t *)(a2 + 20), *(uint32_t *)(a2 + 24), *(this + 5), *(this + 6), *(this + 7), *(this + 8), 2);
  return result;
}



// ------------------------------------------------------------
// 0x554970 IRDPopupWindow__vmt2C —— IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 + 69A5F0/69A840）
// ------------------------------------------------------------
int /*thiscall*/ IRDPopupWindow__vmt2C(uint32_t *this, int a2, int a3)
{
  int result; // eax
  uint8_t *v5; // eax
  uint8_t *v6; // eax

  result = *(this + 3);
  if ( result == 0 )
  {
    v5 = operator new(0x6Cu);
    if ( v5 != nullptr )
      v6 = sub_43C330(v5, a2, a3);
    else
      v6 = nullptr;
    *(this + 3) = v6;
    sub_69C4C0(dword_99FCCC);
    sub_69C420(1);
    sub_69A5F0((uint32_t *)*(this + 3), *(uint32_t *)(*(this + 2) + 20) + 18, *(uint32_t *)(*(this + 2) + 24) + 19);
    return sub_69A840(*(this + 3));
  }
  return result;
}



// ------------------------------------------------------------
// 0x554A20 sub_554A20 —— YesNo 关闭回调（5548B0 + 633580/633770）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_554A20(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 17);
  *this = &vftbl_CNRDSkillBuyConfirmWindow;
  sub_633580((int)this);
  sub_633770(this);
  return this;
}



// ------------------------------------------------------------
// 0x554AA0 CNRDSkillBuyConfirmWindow__vmt4 —— CNRDSkillBuyConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDSkillBuyConfirmWindow__vmt4(void *Block, char a2)
{
  sub_554AD0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x554AD0 sub_554AD0 —— 技能购买确认清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_554AD0(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDSkillBuyConfirmWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x554B40 sub_554B40 —— 技能购买关闭回调（5548B0 + 5640C0/563FE0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_554B40(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 20);
  *this = &vftbl_CNRDItemSellConfirmWindow;
  sub_5640C0(this);
  sub_563FE0(this);
  return this;
}



// ------------------------------------------------------------
// 0x554BC0 CNRDItemSellConfirmWindow__vmt4 —— CNRDItemSellConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemSellConfirmWindow__vmt4(void *Block, char a2)
{
  sub_554BF0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x554BF0 sub_554BF0 —— 出售确认清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_554BF0(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDItemSellConfirmWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x554C60 sub_554C60 —— 出售关闭回调（5548B0 + 5640C0/633B20）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_554C60(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 21);
  *this = &vftbl_CNRDItemDeleteConfirmWindow;
  sub_5640C0(this);
  sub_633B20(this);
  return this;
}



// ------------------------------------------------------------
// 0x554CE0 CNRDItemDeleteConfirmWindow__vmt4 —— CNRDItemDeleteConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemDeleteConfirmWindow__vmt4(void *Block, char a2)
{
  sub_554D10();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x554D10 sub_554D10 —— 删除确认清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_554D10(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDItemDeleteConfirmWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x554D80 sub_554D80 —— 删除关闭回调（5548B0 + 5640C0/564520）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_554D80(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 22);
  *this = &vftbl_CNRDItemRepairConfirmWindow;
  sub_5640C0(this);
  sub_564520(this);
  return this;
}



// ------------------------------------------------------------
// 0x554E00 CNRDItemRepairConfirmWindow__vmt4 —— CNRDItemRepairConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemRepairConfirmWindow__vmt4(void *Block, char a2)
{
  sub_554E30();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x554E30 sub_554E30 —— 修理确认清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_554E30(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDItemRepairConfirmWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x554EA0 sub_554EA0 —— 修理关闭回调（5548B0 + 636030/633E30）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_554EA0(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 25);
  *this = &vftbl_CNRDItemSealRemoveConfirmWindow;
  sub_636030(this);
  sub_633E30(this);
  return this;
}



// ------------------------------------------------------------
// 0x554F20 CNRDItemSealRemoveConfirmWindow__vmt4 —— CNRDItemSealRemoveConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemSealRemoveConfirmWindow__vmt4(void *Block, char a2)
{
  sub_554F50();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x554F50 sub_554F50 —— 解封确认清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_554F50(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDItemSealRemoveConfirmWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x554FC0 sub_554FC0 —— 解封关闭回调（5548B0 + 633F10/634000）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_554FC0(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 27);
  *this = &vftbl_CNRDPopupMessageWindow;
  sub_633F10(this);
  sub_634000(this);
  return this;
}



// ------------------------------------------------------------
// 0x555050 CNRDPopupMessageWindow__vmt4 —— CNRDPopupMessageWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPopupMessageWindow__vmt4(void *Block, char a2)
{
  sub_555080();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x555080 sub_555080 —— 消息弹窗清理（63E1E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_555080(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDPopupMessageWindow;
  result = sub_63E1E0(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5550F0 sub_5550F0 —— 消息关闭回调（5548B0 + 634090）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5550F0(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 28);
  *this = &vftbl_CNRDPopupTextBoxOnly;
  nullsub_3();
  sub_634090(this);
  return this;
}



// ------------------------------------------------------------
// 0x555170 CNRDPopupTextBoxOnly__vmt4 —— CNRDPopupTextBoxOnly__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPopupTextBoxOnly__vmt4(void *Block, char a2)
{
  sub_5551A0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5551A0 sub_5551A0 —— 文本弹窗清理（23 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_5551A0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *this = &vftbl_CNRDPopupTextBoxOnly;
  nullsub_3();
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x555210 sub_555210 —— 文本关闭回调（5548B0 + 634130/634360）
// ------------------------------------------------------------
int /*thiscall*/ sub_555210(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 29);
  *(uint32_t *)this = &vftbl_CNRDResponsePeerWindow;
  *(uint8_t *)(this + 64) = 0;
  *(uint32_t *)(this + 60) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 68) = 0;
  *(uint8_t *)(this + 72) = 1;
  *(uint8_t *)(this + 74) = 0;
  *(uint8_t *)(this + 73) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 76) = 0;
  sub_634130((uint32_t *)this);
  sub_634360((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x5552C0 CNRDResponsePeerWindow__vmt4 —— CNRDResponsePeerWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDResponsePeerWindow__vmt4(void *Block, char a2)
{
  sub_5552F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5552F0 sub_5552F0 —— 响应窗清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_5552F0(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDResponsePeerWindow;
  result = sub_633590((uint32_t *)this);
  *(uint32_t *)(this + 60) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 64) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x555370 sub_555370 —— 响应关闭回调（5548B0 + 6349C0/6348E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_555370(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 30);
  *(uint32_t *)this = &vftbl_CNRDCharacterDeleteConfirmWindow;
  *(uint32_t *)(this + 68) = 15;
  *(uint32_t *)(this + 64) = 0;
  *(uint8_t *)(this + 48) = 0;
  sub_6349C0((uint32_t *)this);
  sub_6348E0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x555400 CNRDCharacterDeleteConfirmWindow__vmt4 —— CNRDCharacterDeleteConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDCharacterDeleteConfirmWindow__vmt4(void *Block, char a2)
{
  sub_555430();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x555430 sub_555430 —— 角色删除清理（633590）
// ------------------------------------------------------------
void /*thiscall*/ sub_555430(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDCharacterDeleteConfirmWindow;
  sub_633590((uint32_t *)this);
  if ( *(uint32_t *)(this + 68) >= 0x10u )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 68) = 15;
  *(uint32_t *)(this + 64) = 0;
  *(uint8_t *)(this + 48) = 0;
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x5554C0 sub_5554C0 —— 角色删除关闭回调（5548B0 + 568390/634BB0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5554C0(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 36);
  *this = &vftbl_CNRDNoticeMessageWindow;
  sub_568390(this);
  sub_634BB0(this);
  return this;
}



// ------------------------------------------------------------
// 0x555540 CNRDNoticeMessageWindow__vmt4 —— CNRDNoticeMessageWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDNoticeMessageWindow__vmt4(void *Block, char a2)
{
  sub_555570();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x555570 sub_555570 —— 公告清理（63E1E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_555570(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDNoticeMessageWindow;
  result = sub_63E1E0(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5555E0 sub_5555E0 —— 公告关闭回调（5548B0 + 634C40/634E60）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5555E0(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 38);
  *this = &vftbl_CNRDQuestGiveupConfirmWindow;
  sub_634C40(this);
  sub_634E60(this);
  return this;
}



// ------------------------------------------------------------
// 0x555660 CNRDQuestGiveupConfirmWindow__vmt4 —— CNRDQuestGiveupConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDQuestGiveupConfirmWindow__vmt4(void *Block, char a2)
{
  sub_555690();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x555690 sub_555690 —— 任务放弃清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_555690(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDQuestGiveupConfirmWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x555700 sub_555700 —— 放弃关闭回调（5548B0 + 634F40/635170）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_555700(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 40);
  *this = &vftbl_CNRDWalkoutConfirmWindow;
  sub_634F40(this);
  sub_635170(this);
  return this;
}



// ------------------------------------------------------------
// 0x555780 CNRDWalkoutConfirmWindow__vmt4 —— CNRDWalkoutConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDWalkoutConfirmWindow__vmt4(void *Block, char a2)
{
  sub_5557B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5557B0 sub_5557B0 —— 退场清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_5557B0(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDWalkoutConfirmWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x555820 sub_555820 —— 退场关闭回调（5548B0 + 635250/6358C0）
// ------------------------------------------------------------
int */*thiscall*/ sub_555820(int *this, int a2)
{
  *this = (int)&vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 4);
  *this = (int)&vftbl_CNRDPVPRoomCreateWindow;
  sub_635250(this);
  sub_6358C0(this);
  return this;
}



// ------------------------------------------------------------
// 0x5558A0 CNRDPVPRoomCreateWindow__vmt4 —— CNRDPVPRoomCreateWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPVPRoomCreateWindow__vmt4(void *Block, char a2)
{
  sub_5558D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5558D0 sub_5558D0 —— 房间创建清理（6352A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_5558D0(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDPVPRoomCreateWindow;
  result = sub_6352A0(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x555940 sub_555940 —— 房间创建关闭回调（5548B0 + 636030/635ED0）
// ------------------------------------------------------------
int /*thiscall*/ sub_555940(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 3);
  *(uint32_t *)this = &vftbl_CNRDPVPRoomInfoWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  sub_636030((uint32_t *)this);
  sub_635ED0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x555A00 CNRDPVPRoomInfoWindow__vmt4 —— CNRDPVPRoomInfoWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPVPRoomInfoWindow__vmt4(void *Block, char a2)
{
  sub_555A30();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x555A30 sub_555A30 —— 房间信息清理（63BAD0）
// ------------------------------------------------------------
int /*thiscall*/ sub_555A30(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDPVPRoomInfoWindow;
  sub_63BAD0((uint32_t *)this);
  result = *(uint32_t *)(this + 92);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 92));
    *(uint32_t *)(this + 92) = 0;
  }
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x555AE0 sub_555AE0 —— 房间信息关闭回调（5548B0 + 631A90/631E40）
// ------------------------------------------------------------
int /*thiscall*/ sub_555AE0(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 54);
  *(uint32_t *)this = &vftbl_CNRDPVPChannelListWindow;
  *(uint8_t *)(this + 64) = 0;
  *(uint8_t *)(this + 65) = 0;
  *(uint8_t *)(this + 66) = 0;
  *(uint8_t *)(this + 67) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 6;
  *(uint32_t *)(this + 84) = 12;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 1600;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  sub_631A90((uint32_t *)this);
  sub_631E40(this);
  return this;
}



// ------------------------------------------------------------
// 0x555BA0 CNRDPVPChannelListWindow__vmt4 —— CNRDPVPChannelListWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPVPChannelListWindow__vmt4(void *Block, char a2)
{
  sub_555BD0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x555BD0 sub_555BD0 —— 频道列表清理（631AC0）
// ------------------------------------------------------------
int /*thiscall*/ sub_555BD0(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDPVPChannelListWindow;
  sub_631AC0((uint32_t *)this);
  result = *(uint32_t *)(this + 108);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 108));
    *(uint32_t *)(this + 108) = 0;
  }
  *(uint8_t *)(this + 64) = 0;
  *(uint8_t *)(this + 65) = 0;
  *(uint8_t *)(this + 66) = 0;
  *(uint8_t *)(this + 67) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x555C80 sub_555C80 —— 频道列表关闭回调（5548B0 + 638A70/56DA00）
// ------------------------------------------------------------
int /*thiscall*/ sub_555C80(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 0);
  *(uint32_t *)this = &vftbl_CNRDTutorialWindow;
  *(uint8_t *)(this + 52) = 0;
  *(uint8_t *)(this + 53) = 0;
  *(uint8_t *)(this + 54) = 0;
  *(uint8_t *)(this + 55) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 6;
  *(uint32_t *)(this + 72) = 12;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 1600;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  sub_638A70((uint32_t *)this);
  sub_56DA00(this);
  return this;
}



// ------------------------------------------------------------
// 0x555D40 CNRDTutorialWindow__vmt4 —— CNRDTutorialWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDTutorialWindow__vmt4(void *Block, char a2)
{
  sub_555D70();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x555D70 sub_555D70 —— 教程清理（638A90）
// ------------------------------------------------------------
int /*thiscall*/ sub_555D70(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDTutorialWindow;
  sub_638A90((uint32_t *)this);
  result = *(uint32_t *)(this + 96);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 96));
    *(uint32_t *)(this + 96) = 0;
  }
  *(uint8_t *)(this + 52) = 0;
  *(uint8_t *)(this + 53) = 0;
  *(uint8_t *)(this + 54) = 0;
  *(uint8_t *)(this + 55) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x555E20 sub_555E20 —— 教程关闭回调（5548B0 + 561EA0/562DA0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_555E20(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 43);
  *this = &vftbl_CNRDOptionWindow;
  sub_561EA0(this);
  sub_562DA0(this);
  return this;
}



// ------------------------------------------------------------
// 0x555EA0 CNRDOptionWindow__vmt4 —— CNRDOptionWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDOptionWindow__vmt4(void *Block, char a2)
{
  sub_555ED0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x555ED0 sub_555ED0 —— 设置清理（561F10）
// ------------------------------------------------------------
int /*thiscall*/ sub_555ED0(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDOptionWindow;
  result = sub_561F10();
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x555F40 sub_555F40 —— 设置关闭回调（5548B0 + 636030/636500）
// ------------------------------------------------------------
int /*thiscall*/ sub_555F40(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 6);
  *(uint32_t *)this = &vftbl_CNRDPartyInfoWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint8_t *)(this + 100) = 0;
  *(uint8_t *)(this + 101) = 0;
  *(uint8_t *)(this + 102) = 0;
  *(uint8_t *)(this + 103) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 6;
  *(uint32_t *)(this + 120) = 12;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 1600;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  sub_636030((uint32_t *)this);
  sub_636500((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x556040 CNRDPartyInfoWindow__vmt4 —— CNRDPartyInfoWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPartyInfoWindow__vmt4(void *Block, char a2)
{
  sub_556070();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556070 sub_556070 —— 组队信息清理（63BAD0）
// ------------------------------------------------------------
int /*thiscall*/ sub_556070(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDPartyInfoWindow;
  sub_63BAD0((uint32_t *)this);
  if ( *(uint32_t *)(this + 144) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 144));
    *(uint32_t *)(this + 144) = 0;
  }
  *(uint8_t *)(this + 100) = 0;
  *(uint8_t *)(this + 101) = 0;
  *(uint8_t *)(this + 102) = 0;
  *(uint8_t *)(this + 103) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  result = *(uint32_t *)(this + 92);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 92));
    *(uint32_t *)(this + 92) = 0;
  }
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x556170 sub_556170 —— 组队信息关闭回调（5548B0 + 6366C0/637070）
// ------------------------------------------------------------
int */*thiscall*/ sub_556170(int *this, int a2)
{
  *this = (int)&vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 7);
  *this = (int)&vftbl_CNRDPartyCreateWindow;
  sub_6366C0(this);
  sub_637070(this);
  return this;
}



// ------------------------------------------------------------
// 0x5561F0 CNRDPartyCreateWindow__vmt4 —— CNRDPartyCreateWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPartyCreateWindow__vmt4(void *Block, char a2)
{
  sub_556220();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556220 sub_556220 —— 组队创建清理（636700）
// ------------------------------------------------------------
int /*thiscall*/ sub_556220(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDPartyCreateWindow;
  result = sub_636700(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x556290 sub_556290 —— 组队创建关闭回调（5548B0 + 633F10/6375A0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_556290(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 44);
  *this = &vftbl_CNRDPartyLeaveSuggestWindow;
  sub_633F10(this);
  sub_6375A0(this);
  return this;
}



// ------------------------------------------------------------
// 0x556310 CNRDPartyLeaveSuggestWindow__vmt4 —— CNRDPartyLeaveSuggestWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPartyLeaveSuggestWindow__vmt4(void *Block, char a2)
{
  sub_556340();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556340 sub_556340 —— 退队清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_556340(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDPartyLeaveSuggestWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5563B0 sub_5563B0 —— 退队关闭回调（5548B0 + 637A80/637920）
// ------------------------------------------------------------
int */*thiscall*/ sub_5563B0(int *this, int a2)
{
  *this = (int)&vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 9);
  *this = (int)&vftbl_CNRDFriendAddRemoveWindow;
  sub_637A80(this);
  sub_637920(this);
  return this;
}



// ------------------------------------------------------------
// 0x556430 CNRDFriendAddRemoveWindow__vmt4 —— CNRDFriendAddRemoveWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDFriendAddRemoveWindow__vmt4(void *Block, char a2)
{
  sub_556460();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556460 sub_556460 —— 好友添加清理（637680）
// ------------------------------------------------------------
int /*thiscall*/ sub_556460(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDFriendAddRemoveWindow;
  result = sub_637680(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5564D0 sub_5564D0 —— 好友添加关闭回调（5548B0 + 637A80/637D60）
// ------------------------------------------------------------
int */*thiscall*/ sub_5564D0(int *this, int a2)
{
  *this = (int)&vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 10);
  *this = (int)&vftbl_CNRDMemberAddRemoveWindow;
  sub_637A80(this);
  sub_637D60(this);
  return this;
}



// ------------------------------------------------------------
// 0x556550 CNRDMemberAddRemoveWindow__vmt4 —— CNRDMemberAddRemoveWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDMemberAddRemoveWindow__vmt4(void *Block, char a2)
{
  sub_556580();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556580 sub_556580 —— 成员添加清理（637680）
// ------------------------------------------------------------
int /*thiscall*/ sub_556580(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDMemberAddRemoveWindow;
  result = sub_637680(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5565F0 sub_5565F0 —— 成员添加关闭回调（5548B0 + 639BD0/637F50）
// ------------------------------------------------------------
int /*thiscall*/ sub_5565F0(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 45);
  *(uint32_t *)this = &vftbl_CNRDFriendRemoveConfirmWindow;
  *(uint32_t *)(this + 68) = 15;
  *(uint32_t *)(this + 64) = 0;
  *(uint8_t *)(this + 48) = 0;
  sub_639BD0((uint32_t *)this);
  sub_637F50((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x556680 CNRDFriendRemoveConfirmWindow__vmt4 —— CNRDFriendRemoveConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDFriendRemoveConfirmWindow__vmt4(void *Block, char a2)
{
  sub_5566B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5566B0 sub_5566B0 —— 好友移除清理（633590）
// ------------------------------------------------------------
void /*thiscall*/ sub_5566B0(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDFriendRemoveConfirmWindow;
  sub_633590((uint32_t *)this);
  if ( *(uint32_t *)(this + 68) >= 0x10u )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 68) = 15;
  *(uint32_t *)(this + 64) = 0;
  *(uint8_t *)(this + 48) = 0;
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x556740 sub_556740 —— 好友移除关闭回调（5548B0 + 636030/638520）
// ------------------------------------------------------------
int /*thiscall*/ sub_556740(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 46);
  *(uint32_t *)this = &vftbl_CNRDStaminaRecoverConfirmWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint8_t *)(this + 100) = 0;
  *(uint8_t *)(this + 101) = 0;
  *(uint8_t *)(this + 102) = 0;
  *(uint8_t *)(this + 103) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 6;
  *(uint32_t *)(this + 120) = 12;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 1600;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  sub_636030((uint32_t *)this);
  sub_638520((int *)this);
  return this;
}



// ------------------------------------------------------------
// 0x556840 CNRDStaminaRecoverConfirmWindow__vmt4 —— CNRDStaminaRecoverConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDStaminaRecoverConfirmWindow__vmt4(void *Block, char a2)
{
  sub_556870();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556870 sub_556870 —— 疲劳清理（63BAD0）
// ------------------------------------------------------------
int /*thiscall*/ sub_556870(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDStaminaRecoverConfirmWindow;
  sub_63BAD0((uint32_t *)this);
  if ( *(uint32_t *)(this + 144) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 144));
    *(uint32_t *)(this + 144) = 0;
  }
  *(uint8_t *)(this + 100) = 0;
  *(uint8_t *)(this + 101) = 0;
  *(uint8_t *)(this + 102) = 0;
  *(uint8_t *)(this + 103) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  result = *(uint32_t *)(this + 92);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 92));
    *(uint32_t *)(this + 92) = 0;
  }
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x556970 sub_556970 —— 疲劳关闭回调（5548B0 + 639BD0/6332F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_556970(int this, int a2, int a3)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &vftbl_CNRDYesNoConfirmWindow;
  *(uint32_t *)(this + 68) = 15;
  *(uint32_t *)(this + 64) = 0;
  *(uint8_t *)(this + 48) = 0;
  sub_639BD0((uint32_t *)this);
  sub_6332F0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x556A10 sub_556A10 —— 疲劳清理 2（556970 转发）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_556A10(uint32_t *this, int a2)
{
  sub_556970((int)this, a2, 47);
  *this = &vftbl_CNRDCashShopBuyConfirmWindow;
  return this;
}



// ------------------------------------------------------------
// 0x556A30 CNRDCashShopBuyConfirmWindow__vmt4 —— CNRDCashShopBuyConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDCashShopBuyConfirmWindow__vmt4(void *Block, char a2)
{
  sub_556A60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556A60 sub_556A60 —— 商城购买清理（554450）
// ------------------------------------------------------------
void /*thiscall*/ sub_556A60(int this)
{
  *(uint32_t *)this = &vftbl_CNRDCashShopBuyConfirmWindow;
  sub_554450(this);
}



// ------------------------------------------------------------
// 0x556A70 sub_556A70 —— 商城购买关闭回调（556970 转发）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_556A70(uint32_t *this, int a2)
{
  sub_556970((int)this, a2, 50);
  *this = &vftbl_CNRDCashShopLevelLimitConfirmWindow;
  return this;
}



// ------------------------------------------------------------
// 0x556A90 CNRDCashShopLevelLimitConfirmWindow__vmt4 —— CNRDCashShopLevelLimitConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDCashShopLevelLimitConfirmWindow__vmt4(void *Block, char a2)
{
  sub_556AC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556AC0 sub_556AC0 —— 等级限制清理（554450）
// ------------------------------------------------------------
void /*thiscall*/ sub_556AC0(int this)
{
  *(uint32_t *)this = &vftbl_CNRDCashShopLevelLimitConfirmWindow;
  sub_554450(this);
}



// ------------------------------------------------------------
// 0x556AD0 sub_556AD0 —— 等级限制关闭回调（556970 转发）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_556AD0(uint32_t *this, int a2)
{
  sub_556970((int)this, a2, 69);
  *this = &vftbl_CNRDCashShopNoDoubleEventConfirmWindow;
  return this;
}



// ------------------------------------------------------------
// 0x556AF0 CNRDCashShopNoDoubleEventConfirmWindow__vmt4 —— CNRDCashShopNoDoubleEventConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDCashShopNoDoubleEventConfirmWindow__vmt4(void *Block, char a2)
{
  sub_556B20();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556B20 sub_556B20 —— 无双倍清理（554450）
// ------------------------------------------------------------
void /*thiscall*/ sub_556B20(int this)
{
  *(uint32_t *)this = &vftbl_CNRDCashShopNoDoubleEventConfirmWindow;
  sub_554450(this);
}



// ------------------------------------------------------------
// 0x556B30 sub_556B30 —— 无双倍关闭回调（556970 转发）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_556B30(uint32_t *this, int a2)
{
  sub_556970((int)this, a2, 49);
  *this = &vftbl_CNRDImportantItemUseConfirmWindow;
  return this;
}



// ------------------------------------------------------------
// 0x556B50 CNRDImportantItemUseConfirmWindow__vmt4 —— CNRDImportantItemUseConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDImportantItemUseConfirmWindow__vmt4(void *Block, char a2)
{
  sub_556B80();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556B80 sub_556B80 —— 重要道具清理（554450）
// ------------------------------------------------------------
void /*thiscall*/ sub_556B80(int this)
{
  *(uint32_t *)this = &vftbl_CNRDImportantItemUseConfirmWindow;
  sub_554450(this);
}



// ------------------------------------------------------------
// 0x556B90 sub_556B90 —— 重要道具关闭回调（556970 转发）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_556B90(uint32_t *this, int a2)
{
  sub_556970((int)this, a2, 66);
  *this = &vftbl_CNRDTradeLastConfirmWindow;
  return this;
}



// ------------------------------------------------------------
// 0x556BB0 CNRDTradeLastConfirmWindow__vmt4 —— CNRDTradeLastConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDTradeLastConfirmWindow__vmt4(void *Block, char a2)
{
  sub_556BE0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556BE0 sub_556BE0 —— 交易确认清理（554450）
// ------------------------------------------------------------
void /*thiscall*/ sub_556BE0(int this)
{
  *(uint32_t *)this = &vftbl_CNRDTradeLastConfirmWindow;
  sub_554450(this);
}



// ------------------------------------------------------------
// 0x556BF0 sub_556BF0 —— 交易确认关闭回调（5548B0 + 6386E0/638870）
// ------------------------------------------------------------
int */*thiscall*/ sub_556BF0(int *this, int a2)
{
  *this = (int)&vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 48);
  *this = (int)&vftbl_CNRDInformCashShopWindow;
  sub_6386E0(this);
  sub_638870(this);
  return this;
}



// ------------------------------------------------------------
// 0x556C70 CNRDInformCashShopWindow__vmt4 —— CNRDInformCashShopWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDInformCashShopWindow__vmt4(void *Block, char a2)
{
  sub_556CA0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556CA0 sub_556CA0 —— 商城提示清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_556CA0(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDInformCashShopWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x556D10 sub_556D10 —— 商城提示关闭回调（5548B0 + 638990）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_556D10(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 70);
  *this = &vftbl_CNRDCashShopDoubleEventWindow;
  sub_638990(this);
  return this;
}



// ------------------------------------------------------------
// 0x556D90 CNRDCashShopDoubleEventWindow__vmt4 —— CNRDCashShopDoubleEventWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDCashShopDoubleEventWindow__vmt4(void *Block, char a2)
{
  sub_556DC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556DC0 sub_556DC0 —— 双倍清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_556DC0(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDCashShopDoubleEventWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x556E30 sub_556E30 —— 双倍关闭回调（5548B0 + 638A70/638DF0）
// ------------------------------------------------------------
int /*thiscall*/ sub_556E30(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 52);
  *(uint32_t *)this = &vftbl_CNRDGuildWindow;
  *(uint8_t *)(this + 52) = 0;
  *(uint8_t *)(this + 53) = 0;
  *(uint8_t *)(this + 54) = 0;
  *(uint8_t *)(this + 55) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 6;
  *(uint32_t *)(this + 72) = 12;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 1600;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  sub_638A70((uint32_t *)this);
  sub_638DF0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x556EF0 CNRDGuildWindow__vmt4 —— CNRDGuildWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDGuildWindow__vmt4(void *Block, char a2)
{
  sub_556F20();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x556F20 sub_556F20 —— 公会清理（638A90）
// ------------------------------------------------------------
int /*thiscall*/ sub_556F20(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDGuildWindow;
  sub_638A90((uint32_t *)this);
  result = *(uint32_t *)(this + 96);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 96));
    *(uint32_t *)(this + 96) = 0;
  }
  *(uint8_t *)(this + 52) = 0;
  *(uint8_t *)(this + 53) = 0;
  *(uint8_t *)(this + 54) = 0;
  *(uint8_t *)(this + 55) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x556FD0 sub_556FD0 —— 公会关闭回调（5548B0 + 636030/6392D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_556FD0(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 53);
  *this = &vftbl_CNRDGuildConfirmWindow;
  sub_636030(this);
  sub_6392D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x557050 CNRDGuildConfirmWindow__vmt4 —— CNRDGuildConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDGuildConfirmWindow__vmt4(void *Block, char a2)
{
  sub_557080();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x557080 sub_557080 —— 公会确认清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_557080(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDGuildConfirmWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5570F0 sub_5570F0 —— 公会确认关闭回调（5548B0 + 568390/5686D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5570F0(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 55);
  *this = &vftbl_CNRDDungeonInfoWindow;
  sub_568390(this);
  sub_5686D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x557180 CNRDDungeonInfoWindow__vmt4 —— CNRDDungeonInfoWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDDungeonInfoWindow__vmt4(void *Block, char a2)
{
  sub_5571B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5571B0 sub_5571B0 —— 副本信息清理（5683A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_5571B0(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDDungeonInfoWindow;
  result = sub_5683A0();
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x557220 sub_557220 —— 副本信息关闭回调（5548B0 + 633F10/6394F0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_557220(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 64);
  *this = &vftbl_CNRDMoveToHomeConfirmWindow;
  sub_633F10(this);
  sub_6394F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x5572A0 CNRDMoveToHomeConfirmWindow__vmt4 —— CNRDMoveToHomeConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDMoveToHomeConfirmWindow__vmt4(void *Block, char a2)
{
  sub_5572D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5572D0 sub_5572D0 —— 回城清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_5572D0(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDMoveToHomeConfirmWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x557340 sub_557340 —— 回城关闭回调（5548B0 + 636030/639690）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_557340(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 65);
  *this = &vftbl_CNRDPrivateStoreItemBuyConfirmWindow;
  sub_636030(this);
  sub_639690(this);
  return this;
}



// ------------------------------------------------------------
// 0x5573C0 CNRDPrivateStoreItemBuyConfirmWindow__vmt4 —— CNRDPrivateStoreItemBuyConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPrivateStoreItemBuyConfirmWindow__vmt4(void *Block, char a2)
{
  sub_5573F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5573F0 sub_5573F0 —— 摆摊购买清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_5573F0(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDPrivateStoreItemBuyConfirmWindow;
  result = sub_633590(this);
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x557460 sub_557460 —— 摆摊购买关闭回调（5548B0 + 639BD0/639AE0）
// ------------------------------------------------------------
int /*thiscall*/ sub_557460(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 56);
  *(uint32_t *)this = &vftbl_CNRDMemberRemoveConfirmWindow;
  *(uint32_t *)(this + 68) = 15;
  *(uint32_t *)(this + 64) = 0;
  *(uint8_t *)(this + 48) = 0;
  sub_639BD0((uint32_t *)this);
  sub_639AE0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x5574F0 CNRDMemberRemoveConfirmWindow__vmt4 —— CNRDMemberRemoveConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDMemberRemoveConfirmWindow__vmt4(void *Block, char a2)
{
  sub_557520();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x557520 sub_557520 —— 成员移除清理（633590）
// ------------------------------------------------------------
void /*thiscall*/ sub_557520(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDMemberRemoveConfirmWindow;
  sub_633590((uint32_t *)this);
  if ( *(uint32_t *)(this + 68) >= 0x10u )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 68) = 15;
  *(uint32_t *)(this + 64) = 0;
  *(uint8_t *)(this + 48) = 0;
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x5575B0 sub_5575B0 —— 成员移除关闭回调（5548B0 + 633F10/639F50）
// ------------------------------------------------------------
int /*thiscall*/ sub_5575B0(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 58);
  *(uint32_t *)this = &vftbl_CNRDResponseMemberWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint32_t *)(this + 44) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 56) = 1;
  *(uint8_t *)(this + 58) = 0;
  *(uint8_t *)(this + 57) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 60) = 0;
  sub_633F10(this);
  sub_639F50((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x557660 CNRDResponseMemberWindow__vmt4 —— CNRDResponseMemberWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDResponseMemberWindow__vmt4(void *Block, char a2)
{
  sub_557690();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x557690 sub_557690 —— 成员响应清理（633590）
// ------------------------------------------------------------
int /*thiscall*/ sub_557690(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDResponseMemberWindow;
  result = sub_633590((uint32_t *)this);
  *(uint32_t *)(this + 44) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 48) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x557710 sub_557710 —— 成员响应关闭回调（5548B0 + 63A030/63A520）
// ------------------------------------------------------------
int /*thiscall*/ sub_557710(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 59);
  *(uint32_t *)this = &vftbl_CNRDUpgradeConfirmWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  sub_63A030(this);
  sub_63A520((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x5577D0 CNRDUpgradeConfirmWindow__vmt4 —— CNRDUpgradeConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDUpgradeConfirmWindow__vmt4(void *Block, char a2)
{
  sub_557800();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x557800 sub_557800 —— 强化确认清理（63BAD0）
// ------------------------------------------------------------
int /*thiscall*/ sub_557800(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDUpgradeConfirmWindow;
  sub_63BAD0((uint32_t *)this);
  result = *(uint32_t *)(this + 92);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 92));
    *(uint32_t *)(this + 92) = 0;
  }
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5578B0 sub_5578B0 —— 强化确认关闭回调（5548B0 + 63A6D0/63AAD0）
// ------------------------------------------------------------
int /*thiscall*/ sub_5578B0(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 60);
  *(uint32_t *)this = &vftbl_CNRDUpgradeResultWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  sub_63A6D0(this);
  sub_63AAD0(this);
  return this;
}



// ------------------------------------------------------------
// 0x557970 CNRDUpgradeResultWindow__vmt4 —— CNRDUpgradeResultWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDUpgradeResultWindow__vmt4(void *Block, char a2)
{
  sub_5579A0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5579A0 sub_5579A0 —— 强化结果清理（63A6E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_5579A0(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDUpgradeResultWindow;
  sub_63A6E0((uint32_t *)this);
  result = *(uint32_t *)(this + 92);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 92));
    *(uint32_t *)(this + 92) = 0;
  }
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x557A50 sub_557A50 —— 强化结果关闭回调（5548B0 + 63B070/63B900）
// ------------------------------------------------------------
int /*thiscall*/ sub_557A50(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 14);
  *(uint32_t *)this = &vftbl_CNRDItemBoxWindow;
  *(uint8_t *)(this + 72) = 0;
  *(uint32_t *)(this + 68) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 76) = 0;
  *(uint8_t *)(this + 80) = 1;
  *(uint8_t *)(this + 82) = 0;
  *(uint8_t *)(this + 81) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 84) = 0;
  sub_63B070(this);
  sub_63B900((int *)this);
  return this;
}



// ------------------------------------------------------------
// 0x557B00 CNRDItemBoxWindow__vmt4 —— CNRDItemBoxWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemBoxWindow__vmt4(void *Block, char a2)
{
  sub_557B30();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x557B30 sub_557B30 —— 物品盒清理（63B0A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_557B30(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDItemBoxWindow;
  result = sub_63B0A0((uint32_t *)this);
  *(uint32_t *)(this + 68) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 72) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x557BB0 sub_557BB0 —— 物品盒关闭回调（5548B0 + 63BAB0/63BD30）
// ------------------------------------------------------------
int /*thiscall*/ sub_557BB0(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 57);
  *(uint32_t *)this = &vftbl_CNRDResetOrResealConfirmWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  sub_63BAB0((uint32_t *)this);
  sub_63BD30((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x557C70 CNRDResetOrResealConfirmWindow__vmt4 —— CNRDResetOrResealConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDResetOrResealConfirmWindow__vmt4(void *Block, char a2)
{
  sub_557CA0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x557CA0 sub_557CA0 —— 再封清理（63BAD0）
// ------------------------------------------------------------
int /*thiscall*/ sub_557CA0(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDResetOrResealConfirmWindow;
  sub_63BAD0((uint32_t *)this);
  result = *(uint32_t *)(this + 92);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 92));
    *(uint32_t *)(this + 92) = 0;
  }
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x557D50 sub_557D50 —— 再封关闭回调（5548B0 + 63C0D0/63C780）
// ------------------------------------------------------------
int /*thiscall*/ sub_557D50(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 61);
  *(uint32_t *)this = &vftbl_CNRDWarRoomDifficultListWindow;
  *(uint8_t *)(this + 56) = 0;
  *(uint8_t *)(this + 57) = 0;
  *(uint8_t *)(this + 58) = 0;
  *(uint8_t *)(this + 59) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 6;
  *(uint32_t *)(this + 76) = 12;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 1600;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  sub_63C0D0((uint32_t *)this);
  sub_63C780((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x557E10 CNRDWarRoomDifficultListWindow__vmt4 —— CNRDWarRoomDifficultListWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDWarRoomDifficultListWindow__vmt4(void *Block, char a2)
{
  sub_557E40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x557E40 sub_557E40 —— 难度列表清理（63C0F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_557E40(uint32_t *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDWarRoomDifficultListWindow;
  sub_63C0F0((int)this);
  result = *(this + 25);
  if ( result != 0 )
  {
    result = DeleteObject((HGDIOBJ)*(this + 25));
    *(this + 25) = 0;
  }
  *((uint8_t *)this + 56) = 0;
  *((uint8_t *)this + 57) = 0;
  *((uint8_t *)this + 58) = 0;
  *((uint8_t *)this + 59) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x557EF0 sub_557EF0 —— 难度列表关闭回调（5548B0 + 636030/63CE30）
// ------------------------------------------------------------
int /*thiscall*/ sub_557EF0(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 63);
  *(uint32_t *)this = &vftbl_CNRDWarRoomInfoWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  sub_636030((uint32_t *)this);
  sub_63CE30((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x557FB0 CNRDWarRoomInfoWindow__vmt4 —— CNRDWarRoomInfoWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDWarRoomInfoWindow__vmt4(void *Block, char a2)
{
  sub_557FE0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x557FE0 sub_557FE0 —— 战争房间清理（63BAD0）
// ------------------------------------------------------------
int /*thiscall*/ sub_557FE0(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDWarRoomInfoWindow;
  sub_63BAD0((uint32_t *)this);
  result = *(uint32_t *)(this + 92);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 92));
    *(uint32_t *)(this + 92) = 0;
  }
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x558090 sub_558090 —— 分隔符文本组装（4015C0/401740——信息窗共用）
// ------------------------------------------------------------
void /*noreturn*/ sub_558090()
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
// 0x558100 sub_558100 —— 分解确认关闭回调（5548B0 + 459700/63CFA0/63D1A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_558100(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 23);
  *(uint32_t *)this = &vftbl_CNRDItemDisjointConfirmWindow;
  *(uint8_t *)(this + 56) = 0;
  *(uint8_t *)(this + 57) = 0;
  *(uint8_t *)(this + 58) = 0;
  *(uint8_t *)(this + 59) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 6;
  *(uint32_t *)(this + 76) = 12;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 1600;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  sub_459700((uint32_t *)(this + 108));
  sub_63CFA0(this);
  sub_63D1A0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x5581D0 CNRDItemDisjointConfirmWindow__vmt4 —— CNRDItemDisjointConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemDisjointConfirmWindow__vmt4(void *Block, char a2)
{
  sub_558200();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x558200 sub_558200 —— 分解确认清理（63BAD0/477AF0）
// ------------------------------------------------------------
int /*thiscall*/ sub_558200(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDItemDisjointConfirmWindow;
  sub_63BAD0((uint32_t *)this);
  sub_477AF0(this + 108);
  result = *(uint32_t *)(this + 100);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 100));
    *(uint32_t *)(this + 100) = 0;
  }
  *(uint8_t *)(this + 56) = 0;
  *(uint8_t *)(this + 57) = 0;
  *(uint8_t *)(this + 58) = 0;
  *(uint8_t *)(this + 59) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5582C0 sub_5582C0 —— 24 行小辅助
// ------------------------------------------------------------
void /*thiscall*/ sub_5582C0(int this)
{
  if ( *(uint32_t *)(this + 36) != 0 )
    j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  if ( *(uint32_t *)(this + 20) != 0 )
    j__free(*(void **)(this + 20));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x558320 sub_558320 —— 分解关闭回调 2（5548B0 + 459700/63D400/63D7F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_558320(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 35);
  *(uint32_t *)this = &vftbl_CNRDLotteryItemWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  sub_459700((uint32_t *)(this + 100));
  *(uint8_t *)(this + 164) = 0;
  *(uint32_t *)(this + 160) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 168) = 0;
  *(uint8_t *)(this + 172) = 1;
  *(uint8_t *)(this + 174) = 0;
  *(uint8_t *)(this + 173) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 176) = 0;
  sub_63D400(this);
  sub_63D7F0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x558420 CNRDLotteryItemWindow__vmt4 —— CNRDLotteryItemWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDLotteryItemWindow__vmt4(void *Block, char a2)
{
  sub_558450();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x558450 sub_558450 —— 赌博清理（633590/477AF0）
// ------------------------------------------------------------
int /*thiscall*/ sub_558450(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDLotteryItemWindow;
  sub_633590((uint32_t *)this);
  *(uint32_t *)(this + 160) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 164) = 0;
  sub_477AF0(this + 100);
  result = *(uint32_t *)(this + 92);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 92));
    *(uint32_t *)(this + 92) = 0;
  }
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x558520 sub_558520 —— 赌博关闭回调（558090 转发）
// ------------------------------------------------------------
char /*thiscall*/ sub_558520(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x1FFFFFFF )
    sub_558090();
  v4 = (char *)operator new(8 * a2);
  *(this + 3) = &v4[8 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x558580 sub_558580 —— 赌博关闭回调 2（5548B0 + 5633F0/563860）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_558580(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  *(this + 1) = 71;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  sub_5548B0(this, a2, 19);
  *this = &vftbl_CNRDItemBuyConfirmWindow;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  sub_5633F0(this);
  sub_563860(this);
  return this;
}



// ------------------------------------------------------------
// 0x558610 CNRDItemBuyConfirmWindow__vmt4 —— CNRDItemBuyConfirmWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemBuyConfirmWindow__vmt4(void *Block, char a2)
{
  sub_558640();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x558640 sub_558640 —— 购买确认清理（633590）
// ------------------------------------------------------------
void /*thiscall*/ sub_558640(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDItemBuyConfirmWindow;
  sub_633590((uint32_t *)this);
  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x5586D0 sub_5586D0 —— 购买关闭回调（5548B0 + 63E7E0/63DC50）
// ------------------------------------------------------------
int /*thiscall*/ sub_5586D0(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 24);
  *(uint32_t *)this = &vftbl_CNRDItemDisjointResultWindow;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 6;
  *(uint32_t *)(this + 80) = 12;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 1600;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  sub_63E7E0((uint32_t *)this);
  sub_63DC50((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x5587A0 CNRDItemDisjointResultWindow__vmt4 —— CNRDItemDisjointResultWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemDisjointResultWindow__vmt4(void *Block, char a2)
{
  sub_5587D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5587D0 sub_5587D0 —— 分解结果清理（63DA90/44CA70）
// ------------------------------------------------------------
int /*thiscall*/ sub_5587D0(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDItemDisjointResultWindow;
  sub_63DA90((uint32_t *)this);
  sub_44CA70((int *)(this + 112));
  result = *(uint32_t *)(this + 104);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 104));
    *(uint32_t *)(this + 104) = 0;
  }
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x558890 sub_558890 —— 分解结果关闭回调（5548B0 + 633F10/63E400）
// ------------------------------------------------------------
int /*thiscall*/ sub_558890(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 31);
  *(uint32_t *)this = &vftbl_CNRDPlayDungeonResultWindow;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 6;
  *(uint32_t *)(this + 80) = 12;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 1600;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  sub_633F10(this);
  sub_63E400((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x558960 CNRDPlayDungeonResultWindow__vmt4 —— CNRDPlayDungeonResultWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPlayDungeonResultWindow__vmt4(void *Block, char a2)
{
  sub_558990();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x558990 sub_558990 —— 副本结算清理（63E1E0/44CA70）
// ------------------------------------------------------------
int /*thiscall*/ sub_558990(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDPlayDungeonResultWindow;
  sub_63E1E0((uint32_t *)this);
  if ( *(uint32_t *)(this + 104) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 104));
    *(uint32_t *)(this + 104) = 0;
  }
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  result = sub_44CA70((int *)(this + 44));
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x558A50 sub_558A50 —— 副本结算关闭回调（5548B0 + 63E7E0/63EA50）
// ------------------------------------------------------------
int /*thiscall*/ sub_558A50(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 32);
  *(uint32_t *)this = &vftbl_CNRDItemTradeResultWindow;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 6;
  *(uint32_t *)(this + 80) = 12;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 1600;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  sub_63E7E0((uint32_t *)this);
  sub_63EA50((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x558B20 CNRDItemTradeResultWindow__vmt4 —— CNRDItemTradeResultWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemTradeResultWindow__vmt4(void *Block, char a2)
{
  sub_558B50();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x558B50 sub_558B50 —— 交易结果清理（63DA90/44CA70）
// ------------------------------------------------------------
int /*thiscall*/ sub_558B50(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDItemTradeResultWindow;
  sub_63DA90((uint32_t *)this);
  sub_44CA70((int *)(this + 112));
  result = *(uint32_t *)(this + 104);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 104));
    *(uint32_t *)(this + 104) = 0;
  }
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x558C10 sub_558C10 —— 合成数据（4F5090）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_558C10(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  sub_4F5090();
  return this;
}



// ------------------------------------------------------------
// 0x558C60 sub_558C60 —— 合成关闭回调（5548B0 + 636030/63F1E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_558C60(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 34);
  *(uint32_t *)this = &vftbl_CNRDCompoundResultWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  sub_636030((uint32_t *)this);
  sub_63F1E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x558D30 CNRDCompoundResultWindow__vmt4 —— CNRDCompoundResultWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDCompoundResultWindow__vmt4(void *Block, char a2)
{
  sub_558D60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x558D60 sub_558D60 —— 合成结果清理（63E1E0/44CA70）
// ------------------------------------------------------------
int /*thiscall*/ sub_558D60(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDCompoundResultWindow;
  sub_63E1E0((uint32_t *)this);
  sub_44CA70((int *)(this + 100));
  result = *(uint32_t *)(this + 92);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 92));
    *(uint32_t *)(this + 92) = 0;
  }
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x558E20 sub_558E20 —— 对话关闭回调（5548B0 + 605E80/606340）
// ------------------------------------------------------------
int /*thiscall*/ sub_558E20(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 37);
  *(uint32_t *)this = &vftbl_CNRDDialogueWindow;
  *(uint8_t *)(this + 68) = 0;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  *(uint8_t *)(this + 71) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 6;
  *(uint32_t *)(this + 88) = 12;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 1600;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 152) = 15;
  *(uint32_t *)(this + 148) = 0;
  *(uint8_t *)(this + 132) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  sub_605E80(this);
  sub_606340((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x558F20 CNRDDialogueWindow__vmt4 —— CNRDDialogueWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDDialogueWindow__vmt4(void *Block, char a2)
{
  sub_558F50();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x558F50 sub_558F50 —— 对话清理（605EB0）
// ------------------------------------------------------------
int /*thiscall*/ sub_558F50(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDDialogueWindow;
  sub_605EB0((uint32_t *)this);
  if ( *(uint32_t *)(this + 176) != 0 )
    j__free(*(void **)(this + 176));
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  if ( *(uint32_t *)(this + 160) != 0 )
    j__free(*(void **)(this + 160));
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  if ( *(uint32_t *)(this + 152) >= 0x10u )
    j__free(*(void **)(this + 132));
  *(uint32_t *)(this + 152) = 15;
  *(uint32_t *)(this + 148) = 0;
  *(uint8_t *)(this + 132) = 0;
  result = *(uint32_t *)(this + 112);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 112));
    *(uint32_t *)(this + 112) = 0;
  }
  *(uint8_t *)(this + 68) = 0;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  *(uint8_t *)(this + 71) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x559080 sub_559080 —— 任务奖励关闭回调（5548B0 + 633F10/63F660）
// ------------------------------------------------------------
int /*thiscall*/ sub_559080(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 39);
  *(uint32_t *)this = &vftbl_CNRDQuestRewardWindow;
  *(uint8_t *)(this + 44) = 0;
  *(uint8_t *)(this + 45) = 0;
  *(uint8_t *)(this + 46) = 0;
  *(uint8_t *)(this + 47) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 6;
  *(uint32_t *)(this + 64) = 12;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 1600;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  sub_633F10(this);
  sub_63F660(this);
  return this;
}



// ------------------------------------------------------------
// 0x559150 CNRDQuestRewardWindow__vmt4 —— CNRDQuestRewardWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDQuestRewardWindow__vmt4(void *Block, char a2)
{
  sub_559180();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x559180 sub_559180 —— 任务奖励清理（63E1E0/44CA70）
// ------------------------------------------------------------
int /*thiscall*/ sub_559180(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDQuestRewardWindow;
  sub_63E1E0((uint32_t *)this);
  sub_44CA70((int *)(this + 96));
  result = *(uint32_t *)(this + 88);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 88));
    *(uint32_t *)(this + 88) = 0;
  }
  *(uint8_t *)(this + 44) = 0;
  *(uint8_t *)(this + 45) = 0;
  *(uint8_t *)(this + 46) = 0;
  *(uint8_t *)(this + 47) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x559240 sub_559240 —— 任务奖励关闭回调 2（5548B0 + 636030/640250）
// ------------------------------------------------------------
int /*thiscall*/ sub_559240(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 41);
  *(uint32_t *)this = &vftbl_CNRDClassChangeWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 80) = 0;
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
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  sub_636030((uint32_t *)this);
  sub_640250(this);
  return this;
}



// ------------------------------------------------------------
// 0x559320 CNRDClassChangeWindow__vmt4 —— CNRDClassChangeWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDClassChangeWindow__vmt4(void *Block, char a2)
{
  sub_559350();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x559350 sub_559350 —— 转职清理（63E1E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_559350(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDClassChangeWindow;
  sub_63E1E0((uint32_t *)this);
  if ( *(uint32_t *)(this + 136) != 0 )
    j__free(*(void **)(this + 136));
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  if ( *(uint32_t *)(this + 120) != 0 )
    j__free(*(void **)(this + 120));
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  if ( *(uint32_t *)(this + 104) != 0 )
    j__free(*(void **)(this + 104));
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  result = *(uint32_t *)(this + 92);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 92));
    *(uint32_t *)(this + 92) = 0;
  }
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x559460 sub_559460 —— 推荐用户关闭回调（5548B0 + 63E7E0/632AA0）
// ------------------------------------------------------------
int /*thiscall*/ sub_559460(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 1);
  *(uint32_t *)this = &vftbl_CNRDPartyRecommendUserWindow;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 6;
  *(uint32_t *)(this + 80) = 12;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 1600;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint8_t *)(this + 112) = 0;
  *(uint8_t *)(this + 113) = 0;
  *(uint8_t *)(this + 114) = 0;
  *(uint8_t *)(this + 115) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 6;
  *(uint32_t *)(this + 132) = 12;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 1600;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  sub_63E7E0((uint32_t *)this);
  sub_632AA0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x559580 CNRDPartyRecommendUserWindow__vmt4 —— CNRDPartyRecommendUserWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPartyRecommendUserWindow__vmt4(void *Block, char a2)
{
  sub_5595B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5595B0 sub_5595B0 —— 推荐用户清理（632630）
// ------------------------------------------------------------
int /*thiscall*/ sub_5595B0(int this)
{
  void *v2; // eax
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDPartyRecommendUserWindow;
  sub_632630((uint32_t *)this);
  if ( *(uint32_t *)(this + 168) != 0 )
    j__free(*(void **)(this + 168));
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  v2 = *(void **)(this + 156);
  if ( v2 != nullptr )
  {
    DeleteObject(v2);
    *(uint32_t *)(this + 156) = 0;
  }
  *(uint8_t *)(this + 112) = 0;
  *(uint8_t *)(this + 113) = 0;
  *(uint8_t *)(this + 114) = 0;
  *(uint8_t *)(this + 115) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  result = *(uint32_t *)(this + 104);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 104));
    *(uint32_t *)(this + 104) = 0;
  }
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5596E0 sub_5596E0 —— PVP 邀请关闭回调（5548B0 + 640A10/640D10）
// ------------------------------------------------------------
int /*thiscall*/ sub_5596E0(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 42);
  *(uint32_t *)this = &vftbl_CNRDPVPWarRoomInviteWindow;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint8_t *)(this + 132) = 0;
  *(uint8_t *)(this + 133) = 0;
  *(uint8_t *)(this + 134) = 0;
  *(uint8_t *)(this + 135) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 6;
  *(uint32_t *)(this + 152) = 12;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 1600;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  sub_640A10(this);
  sub_640D10(this);
  return this;
}



// ------------------------------------------------------------
// 0x5597E0 CNRDPVPWarRoomInviteWindow__vmt4 —— CNRDPVPWarRoomInviteWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPVPWarRoomInviteWindow__vmt4(void *Block, char a2)
{
  sub_559810();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x559810 sub_559810 —— PVP 邀请清理（640990）
// ------------------------------------------------------------
void /*thiscall*/ sub_559810(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDPVPWarRoomInviteWindow;
  sub_640990((uint32_t *)this);
  if ( *(uint32_t *)(this + 176) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 176));
    *(uint32_t *)(this + 176) = 0;
  }
  *(uint8_t *)(this + 132) = 0;
  *(uint8_t *)(this + 133) = 0;
  *(uint8_t *)(this + 134) = 0;
  *(uint8_t *)(this + 135) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  if ( *(uint32_t *)(this + 116) != 0 )
    j__free(*(void **)(this + 116));
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  if ( *(uint32_t *)(this + 100) != 0 )
    j__free(*(void **)(this + 100));
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x559920 sub_559920 —— 组队列表关闭回调（5548B0 + 6305E0/630F80）
// ------------------------------------------------------------
int /*thiscall*/ sub_559920(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 5);
  *(uint32_t *)this = &vftbl_CNRDPartyListWindow;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint8_t *)(this + 96) = 0;
  *(uint8_t *)(this + 97) = 0;
  *(uint8_t *)(this + 98) = 0;
  *(uint8_t *)(this + 99) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 6;
  *(uint32_t *)(this + 116) = 12;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 1600;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint8_t *)(this + 148) = 0;
  *(uint8_t *)(this + 149) = 0;
  *(uint8_t *)(this + 150) = 0;
  *(uint8_t *)(this + 151) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 6;
  *(uint32_t *)(this + 168) = 12;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 1600;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  sub_6305E0((uint32_t *)this);
  sub_630F80((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x559A50 CNRDPartyListWindow__vmt4 —— CNRDPartyListWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPartyListWindow__vmt4(void *Block, char a2)
{
  sub_559A80();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x559A80 sub_559A80 —— 组队列表清理（630610）
// ------------------------------------------------------------
void /*thiscall*/ sub_559A80(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDPartyListWindow;
  sub_630610((uint32_t *)this);
  if ( *(uint32_t *)(this + 192) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 192));
    *(uint32_t *)(this + 192) = 0;
  }
  *(uint8_t *)(this + 148) = 0;
  *(uint8_t *)(this + 149) = 0;
  *(uint8_t *)(this + 150) = 0;
  *(uint8_t *)(this + 151) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  if ( *(uint32_t *)(this + 140) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 140));
    *(uint32_t *)(this + 140) = 0;
  }
  *(uint8_t *)(this + 96) = 0;
  *(uint8_t *)(this + 97) = 0;
  *(uint8_t *)(this + 98) = 0;
  *(uint8_t *)(this + 99) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  if ( *(uint32_t *)(this + 68) != 0 )
    j__free(*(void **)(this + 68));
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x559BD0 sub_559BD0 —— 好友列表关闭回调（5548B0 + 6414D0/6417E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_559BD0(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 8);
  *(uint32_t *)this = &vftbl_CNRDFriendListWindow;
  *(uint8_t *)(this + 68) = 0;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  *(uint8_t *)(this + 71) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 6;
  *(uint32_t *)(this + 88) = 12;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 1600;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint8_t *)(this + 120) = 0;
  *(uint8_t *)(this + 121) = 0;
  *(uint8_t *)(this + 122) = 0;
  *(uint8_t *)(this + 123) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 6;
  *(uint32_t *)(this + 140) = 12;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 1600;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  sub_6414D0((uint32_t *)this);
  sub_6417E0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x559CF0 CNRDFriendListWindow__vmt4 —— CNRDFriendListWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDFriendListWindow__vmt4(void *Block, char a2)
{
  sub_559D20();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x559D20 sub_559D20 —— 好友列表清理（6414F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_559D20(int this)
{
  void *v2; // eax
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDFriendListWindow;
  sub_6414F0((uint32_t *)this);
  if ( *(uint32_t *)(this + 180) != 0 )
    j__free(*(void **)(this + 180));
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  v2 = *(void **)(this + 164);
  if ( v2 != nullptr )
  {
    DeleteObject(v2);
    *(uint32_t *)(this + 164) = 0;
  }
  *(uint8_t *)(this + 120) = 0;
  *(uint8_t *)(this + 121) = 0;
  *(uint8_t *)(this + 122) = 0;
  *(uint8_t *)(this + 123) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  result = *(uint32_t *)(this + 112);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 112));
    *(uint32_t *)(this + 112) = 0;
  }
  *(uint8_t *)(this + 68) = 0;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  *(uint8_t *)(this + 71) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x559E50 sub_559E50 —— 赠品列表关闭回调（5548B0 + 63E7E0/4D42A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_559E50(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 68);
  *(uint32_t *)this = &vftbl_CNRDSeriasPresentListWindow;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 6;
  *(uint32_t *)(this + 80) = 12;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 1600;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  sub_63E7E0((uint32_t *)this);
  sub_4D42A0(this);
  return this;
}



// ------------------------------------------------------------
// 0x559F20 CNRDSeriasPresentListWindow__vmt4 —— CNRDSeriasPresentListWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDSeriasPresentListWindow__vmt4(void *Block, char a2)
{
  sub_559F50();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x559F50 sub_559F50 —— 赠品清理（63DA90/44CA70）
// ------------------------------------------------------------
int /*thiscall*/ sub_559F50(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDSeriasPresentListWindow;
  sub_63DA90((uint32_t *)this);
  sub_44CA70((int *)(this + 112));
  result = *(uint32_t *)(this + 104);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 104));
    *(uint32_t *)(this + 104) = 0;
  }
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ============================================================
// 【分区 9】弹窗析构配套与关闭回调装配表（0x55A010-0x55C0F0）
// 关闭事件槽 0x55A040；各独立窗口 vmt4 在 0x55A0D0-0x55AEF0
// vmt4（WarRoomList/SkillInfo/ItemInfo/CompoundItem/PVPRoomList）；
// 集中装配表 0x55B070（408 行）= 全部弹窗关闭回调（初始化时调用）。
// ============================================================
// ------------------------------------------------------------
// 0x55A010 sub_55A010 —— 信息窗文本（5014C0）
// ------------------------------------------------------------
void /*stdcall*/ sub_55A010(char *a1, char *a2)
{
  char *i; // esi

  for ( i = a1; i != a2; i += 40 )
    sub_5014C0(i);
}



// ------------------------------------------------------------
// 0x55A040 IRDPopupWindow__vmt20 —— IRDPopupWindow__vmt20 关闭事件槽（44E3E0）
// ------------------------------------------------------------
unsigned int /*thiscall*/ IRDPopupWindow__vmt20(uint32_t **this)
{
  return sub_44E3E0(*(this + 4), (int)this);
}



// ------------------------------------------------------------
// 0x55A050 sub_55A050 —— 信息窗文本 2（5014C0）
// ------------------------------------------------------------
int /*thiscall*/ sub_55A050(int this)
{
  char *v2; // esi
  int result; // eax
  char *i; // edi

  v2 = *(char **)(this + 4);
  result = 0;
  if ( v2 != nullptr )
  {
    for ( i = *(char **)(this + 8); v2 != i; v2 += 40 )
      sub_5014C0(v2);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x55A090 sub_55A090 —— 合成窗文本（442C50）
// ------------------------------------------------------------
int /*thiscall*/ sub_55A090(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 44 )
      sub_442C50(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x55A0D0 sub_55A0D0 —— 战争房间列表关闭回调（5548B0 + 49ED30/62E400/62E0A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_55A0D0(int this, int a2)
{
  int v3; // eax

  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 62);
  *(uint32_t *)this = &vftbl_CNRDWarRoomListWindow;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 6;
  *(uint32_t *)(this + 80) = 12;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 1600;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint8_t *)(this + 112) = 0;
  *(uint8_t *)(this + 113) = 0;
  *(uint8_t *)(this + 114) = 0;
  *(uint8_t *)(this + 115) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 6;
  *(uint32_t *)(this + 132) = 12;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 1600;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  v3 = sub_49ED30(this + 188);
  *(uint32_t *)(this + 192) = v3;
  *(uint8_t *)(v3 + 173) = 1;
  *(uint32_t *)(*(uint32_t *)(this + 192) + 4) = *(uint32_t *)(this + 192);
  **(uint32_t **)(this + 192) = *(uint32_t *)(this + 192);
  *(uint32_t *)(*(uint32_t *)(this + 192) + 8) = *(uint32_t *)(this + 192);
  *(uint32_t *)(this + 196) = 0;
  *(uint8_t *)(this + 204) = 0;
  *(uint32_t *)(this + 200) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 208) = 0;
  *(uint8_t *)(this + 212) = 1;
  *(uint8_t *)(this + 214) = 0;
  *(uint8_t *)(this + 213) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 216) = 0;
  sub_62E400((uint32_t *)this);
  sub_62E0A0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x55A250 CNRDWarRoomListWindow__vmt4 —— CNRDWarRoomListWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDWarRoomListWindow__vmt4(void *Block, char a2)
{
  sub_55A280();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x55A280 sub_55A280 —— 战争房间清理（62DED0/49F750，86 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_55A280(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int v5; // [esp-8h] [ebp-28h]
  int *v6; // [esp-4h] [ebp-24h]
  uint8_t v7[4]; // [esp+Ch] [ebp-14h] BYREF
  int v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+1Ch] [ebp-4h]

  v8 = this;
  *(uint32_t *)this = &vftbl_CNRDWarRoomListWindow;
  v9 = 5;
  sub_62DED0((uint32_t *)this);
  *(uint32_t *)(this + 200) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 204) = 0;
  v6 = *(int **)(this + 192);
  v5 = *v6;
  LOBYTE(v9) = 3;
  sub_49F750(v7, v5, v6);
  j__free(*(void **)(this + 192));
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  if ( *(uint32_t *)(this + 168) != 0 )
    j__free(*(void **)(this + 168));
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  if ( *(uint32_t *)(this + 156) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 156));
    *(uint32_t *)(this + 156) = 0;
  }
  *(uint8_t *)(this + 112) = 0;
  *(uint8_t *)(this + 113) = 0;
  *(uint8_t *)(this + 114) = 0;
  *(uint8_t *)(this + 115) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  result = *(uint32_t *)(this + 104);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 104));
    *(uint32_t *)(this + 104) = 0;
  }
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  v9 = -1;
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x55A3F0 sub_55A3F0 —— 技能信息文本转发（55A050）
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_55A3F0(int this)
{
  return sub_55A050(this);
}



// ------------------------------------------------------------
// 0x55A410 sub_55A410 —— 技能信息关闭回调（5548B0 + 5702F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_55A410(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 18);
  *(uint32_t *)this = &vftbl_CNRDSkillInfoWindow;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 6;
  *(uint32_t *)(this + 80) = 12;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 1600;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint8_t *)(this + 112) = 0;
  *(uint8_t *)(this + 113) = 0;
  *(uint8_t *)(this + 114) = 0;
  *(uint8_t *)(this + 115) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 6;
  *(uint32_t *)(this + 132) = 12;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 1600;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint8_t *)(this + 164) = 0;
  *(uint8_t *)(this + 165) = 0;
  *(uint8_t *)(this + 166) = 0;
  *(uint8_t *)(this + 167) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 6;
  *(uint32_t *)(this + 184) = 12;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 1600;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  nullsub_3();
  sub_5702F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x55A570 CNRDSkillInfoWindow__vmt4 —— CNRDSkillInfoWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDSkillInfoWindow__vmt4(void *Block, char a2)
{
  sub_55A5A0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x55A5A0 sub_55A5A0 —— 技能信息清理（55A050）
// ------------------------------------------------------------
int /*thiscall*/ sub_55A5A0(HGDIOBJ *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDSkillInfoWindow;
  nullsub_3();
  if ( *(this + 52) != nullptr )
  {
    DeleteObject(*(this + 52));
    *(this + 52) = nullptr;
  }
  *((uint8_t *)this + 164) = 0;
  *((uint8_t *)this + 165) = 0;
  *((uint8_t *)this + 166) = 0;
  *((uint8_t *)this + 167) = 0;
  *(this + 44) = nullptr;
  *(this + 45) = nullptr;
  *(this + 46) = nullptr;
  *(this + 47) = nullptr;
  *(this + 48) = nullptr;
  *(this + 49) = nullptr;
  *(this + 50) = nullptr;
  *(this + 51) = nullptr;
  *(this + 52) = nullptr;
  *(this + 53) = nullptr;
  if ( *(this + 39) != nullptr )
  {
    DeleteObject(*(this + 39));
    *(this + 39) = nullptr;
  }
  *((uint8_t *)this + 112) = 0;
  *((uint8_t *)this + 113) = 0;
  *((uint8_t *)this + 114) = 0;
  *((uint8_t *)this + 115) = 0;
  *(this + 31) = nullptr;
  *(this + 32) = nullptr;
  *(this + 33) = nullptr;
  *(this + 34) = nullptr;
  *(this + 35) = nullptr;
  *(this + 36) = nullptr;
  *(this + 37) = nullptr;
  *(this + 38) = nullptr;
  *(this + 39) = nullptr;
  *(this + 40) = nullptr;
  if ( *(this + 26) != nullptr )
  {
    DeleteObject(*(this + 26));
    *(this + 26) = nullptr;
  }
  *((uint8_t *)this + 60) = 0;
  *((uint8_t *)this + 61) = 0;
  *((uint8_t *)this + 62) = 0;
  *((uint8_t *)this + 63) = 0;
  *(this + 18) = nullptr;
  *(this + 19) = nullptr;
  *(this + 20) = nullptr;
  *(this + 21) = nullptr;
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *(this + 24) = nullptr;
  *(this + 25) = nullptr;
  *(this + 26) = nullptr;
  *(this + 27) = nullptr;
  result = sub_55A050((int)(this + 11));
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = nullptr;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x55A720 sub_55A720 —— 物品信息关闭回调（5548B0 + 572040）
// ------------------------------------------------------------
int /*thiscall*/ sub_55A720(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 26);
  *(uint32_t *)this = &vftbl_CNRDItemInfoWindow;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint8_t *)(this + 52) = 0;
  *(uint8_t *)(this + 53) = 0;
  *(uint8_t *)(this + 54) = 0;
  *(uint8_t *)(this + 55) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 6;
  *(uint32_t *)(this + 72) = 12;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 1600;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 104) = 0;
  *(uint8_t *)(this + 105) = 0;
  *(uint8_t *)(this + 106) = 0;
  *(uint8_t *)(this + 107) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 6;
  *(uint32_t *)(this + 124) = 12;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 1600;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint8_t *)(this + 156) = 0;
  *(uint8_t *)(this + 157) = 0;
  *(uint8_t *)(this + 158) = 0;
  *(uint8_t *)(this + 159) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 6;
  *(uint32_t *)(this + 176) = 12;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 1600;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint8_t *)(this + 208) = 0;
  *(uint8_t *)(this + 209) = 0;
  *(uint8_t *)(this + 210) = 0;
  *(uint8_t *)(this + 211) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 6;
  *(uint32_t *)(this + 228) = 12;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 1600;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 252) = 0;
  *(uint32_t *)(this + 256) = 0;
  nullsub_3();
  sub_572040(this);
  return this;
}



// ------------------------------------------------------------
// 0x55A8E0 CNRDItemInfoWindow__vmt4 —— CNRDItemInfoWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemInfoWindow__vmt4(void *Block, char a2)
{
  sub_55A910();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x55A910 sub_55A910 —— 物品信息清理（55A050）
// ------------------------------------------------------------
int /*thiscall*/ sub_55A910(HGDIOBJ *this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  *this = &vftbl_CNRDItemInfoWindow;
  nullsub_3();
  if ( *(this + 63) != nullptr )
  {
    DeleteObject(*(this + 63));
    *(this + 63) = nullptr;
  }
  *((uint8_t *)this + 208) = 0;
  *((uint8_t *)this + 209) = 0;
  *((uint8_t *)this + 210) = 0;
  *((uint8_t *)this + 211) = 0;
  *(this + 55) = nullptr;
  *(this + 56) = nullptr;
  *(this + 57) = nullptr;
  *(this + 58) = nullptr;
  *(this + 59) = nullptr;
  *(this + 60) = nullptr;
  *(this + 61) = nullptr;
  *(this + 62) = nullptr;
  *(this + 63) = nullptr;
  *(this + 64) = nullptr;
  if ( *(this + 50) != nullptr )
  {
    DeleteObject(*(this + 50));
    *(this + 50) = nullptr;
  }
  *((uint8_t *)this + 156) = 0;
  *((uint8_t *)this + 157) = 0;
  *((uint8_t *)this + 158) = 0;
  *((uint8_t *)this + 159) = 0;
  *(this + 42) = nullptr;
  *(this + 43) = nullptr;
  *(this + 44) = nullptr;
  *(this + 45) = nullptr;
  *(this + 46) = nullptr;
  *(this + 47) = nullptr;
  *(this + 48) = nullptr;
  *(this + 49) = nullptr;
  *(this + 50) = nullptr;
  *(this + 51) = nullptr;
  if ( *(this + 37) != nullptr )
  {
    DeleteObject(*(this + 37));
    *(this + 37) = nullptr;
  }
  *((uint8_t *)this + 104) = 0;
  *((uint8_t *)this + 105) = 0;
  *((uint8_t *)this + 106) = 0;
  *((uint8_t *)this + 107) = 0;
  *(this + 29) = nullptr;
  *(this + 30) = nullptr;
  *(this + 31) = nullptr;
  *(this + 32) = nullptr;
  *(this + 33) = nullptr;
  *(this + 34) = nullptr;
  *(this + 35) = nullptr;
  *(this + 36) = nullptr;
  *(this + 37) = nullptr;
  *(this + 38) = nullptr;
  if ( *(this + 24) != nullptr )
  {
    DeleteObject(*(this + 24));
    *(this + 24) = nullptr;
  }
  *((uint8_t *)this + 52) = 0;
  *((uint8_t *)this + 53) = 0;
  *((uint8_t *)this + 54) = 0;
  *((uint8_t *)this + 55) = 0;
  *(this + 16) = nullptr;
  *(this + 17) = nullptr;
  *(this + 18) = nullptr;
  *(this + 19) = nullptr;
  *(this + 20) = nullptr;
  *(this + 21) = nullptr;
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *(this + 24) = nullptr;
  *(this + 25) = nullptr;
  result = sub_55A050((int)(this + 9));
  v3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = nullptr;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x55AAF0 sub_55AAF0 —— 合成窗关闭回调（5548B0 + 558C10/62ED00/62F700）
// ------------------------------------------------------------
int /*thiscall*/ sub_55AAF0(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 33);
  *(uint32_t *)this = &vftbl_CNRDCompoundItemWindow;
  sub_558C10((uint32_t *)(this + 64));
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint8_t *)(this + 148) = 0;
  *(uint8_t *)(this + 149) = 0;
  *(uint8_t *)(this + 150) = 0;
  *(uint8_t *)(this + 151) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 6;
  *(uint32_t *)(this + 168) = 12;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 1600;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  sub_62ED00((uint32_t *)this);
  sub_62F700((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x55AC00 CNRDCompoundItemWindow__vmt4 —— CNRDCompoundItemWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDCompoundItemWindow__vmt4(void *Block, char a2)
{
  sub_55AC30();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x55AC30 sub_55AC30 —— 合成窗清理（62ED40/55A090/5582C0）
// ------------------------------------------------------------
void /*thiscall*/ sub_55AC30(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDCompoundItemWindow;
  sub_62ED40((uint32_t *)this);
  if ( *(uint32_t *)(this + 192) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 192));
    *(uint32_t *)(this + 192) = 0;
  }
  *(uint8_t *)(this + 148) = 0;
  *(uint8_t *)(this + 149) = 0;
  *(uint8_t *)(this + 150) = 0;
  *(uint8_t *)(this + 151) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  sub_55A090((int *)(this + 132));
  sub_55A090((int *)(this + 116));
  sub_5582C0(this + 64);
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x55AD30 sub_55AD30 —— PVP 房间列表关闭回调（5548B0 + 433A80/6428A0/642420）
// ------------------------------------------------------------
int /*thiscall*/ sub_55AD30(int this, int a2)
{
  uint32_t *v3; // eax

  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  *(uint32_t *)(this + 4) = 71;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_5548B0((uint32_t *)this, a2, 2);
  *(uint32_t *)this = &vftbl_CNRDPVPRoomListWindow;
  *(uint8_t *)(this + 68) = 0;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  *(uint8_t *)(this + 71) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 6;
  *(uint32_t *)(this + 88) = 12;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 1600;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint8_t *)(this + 120) = 0;
  *(uint8_t *)(this + 121) = 0;
  *(uint8_t *)(this + 122) = 0;
  *(uint8_t *)(this + 123) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 6;
  *(uint32_t *)(this + 140) = 12;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 1600;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  v3 = sub_433A80();
  *(uint32_t *)(this + 204) = v3;
  *((uint8_t *)v3 + 137) = 1;
  *(uint32_t *)(*(uint32_t *)(this + 204) + 4) = *(uint32_t *)(this + 204);
  **(uint32_t **)(this + 204) = *(uint32_t *)(this + 204);
  *(uint32_t *)(*(uint32_t *)(this + 204) + 8) = *(uint32_t *)(this + 204);
  *(uint32_t *)(this + 208) = 0;
  *(uint8_t *)(this + 216) = 0;
  *(uint32_t *)(this + 212) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 220) = 0;
  *(uint8_t *)(this + 224) = 1;
  *(uint8_t *)(this + 226) = 0;
  *(uint8_t *)(this + 225) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 228) = 0;
  sub_6428A0(this);
  sub_642420(this);
  return this;
}



// ------------------------------------------------------------
// 0x55AEC0 CNRDPVPRoomListWindow__vmt4 —— CNRDPVPRoomListWindow__vmt4 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNRDPVPRoomListWindow__vmt4(void *Block, char a2)
{
  sub_55AEF0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x55AEF0 sub_55AEF0 —— PVP 房间列表清理（6421A0/438820）
// ------------------------------------------------------------
int /*thiscall*/ sub_55AEF0(int this)
{
  int result; // eax
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int v5; // [esp-8h] [ebp-28h]
  int *v6; // [esp-4h] [ebp-24h]
  int v7[2]; // [esp+Ch] [ebp-14h] BYREF
  int v8; // [esp+1Ch] [ebp-4h]

  v7[1] = this;
  *(uint32_t *)this = &vftbl_CNRDPVPRoomListWindow;
  v8 = 5;
  sub_6421A0((uint32_t *)this);
  *(uint32_t *)(this + 212) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 216) = 0;
  v6 = *(int **)(this + 204);
  v5 = *v6;
  LOBYTE(v8) = 3;
  sub_438820((int **)(this + 200), v7, v5, (int)v6);
  j__free(*(void **)(this + 204));
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  if ( *(uint32_t *)(this + 176) != 0 )
    j__free(*(void **)(this + 176));
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  if ( *(uint32_t *)(this + 164) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 164));
    *(uint32_t *)(this + 164) = 0;
  }
  *(uint8_t *)(this + 120) = 0;
  *(uint8_t *)(this + 121) = 0;
  *(uint8_t *)(this + 122) = 0;
  *(uint8_t *)(this + 123) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  result = *(uint32_t *)(this + 112);
  if ( result != 0 )
  {
    result = DeleteObject(*(HGDIOBJ *)(this + 112));
    *(uint32_t *)(this + 112) = 0;
  }
  *(uint8_t *)(this + 68) = 0;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  *(uint8_t *)(this + 71) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  v8 = -1;
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  if ( v3 != nullptr )
    result = (**v3)(v3, 1);
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
  *(uint32_t *)(this + 8) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x55B070 sub_55B070 —— 全部弹窗关闭回调集中装配表（408 行：依次调用 24 组 5548B0 系关闭回调登记——YesNo/技能/出售/删除/修理/解封/消息/文本/角色删除/公告/放弃/退场/房间创建/房间信息/频道/教程/设置/组队信息/创建/退队/好友/成员/疲劳/双倍等）
// ------------------------------------------------------------
int /*cdecl*/ sub_55B070(void *Block, int a2)
{
  if ( Block == (void *)1 )
  {
    if ( operator new(0xB4u) != nullptr )
      return sub_559460(a2);
    return 0;
  }
  if ( Block == (void *)2 )
  {
    if ( operator new(0xF0u) != nullptr )
      return sub_55AD30(a2);
    return 0;
  }
  if ( Block == (void *)3 )
  {
    if ( operator new(0x64u) != nullptr )
      return sub_555940(a2);
    return 0;
  }
  if ( Block == (void *)4 )
  {
    if ( operator new(0x78u) != nullptr )
      return sub_555820(a2);
    return 0;
  }
  if ( Block == (void *)5 )
  {
    if ( operator new(0xC8u) != nullptr )
      return sub_559920(a2);
    return 0;
  }
  if ( Block == (void *)6 )
  {
    if ( operator new(0x98u) != nullptr )
      return sub_555F40(a2);
    return 0;
  }
  if ( Block == (void *)7 )
  {
    if ( operator new(0x64u) != nullptr )
      return sub_556170(a2);
    return 0;
  }
  if ( Block == (void *)8 )
  {
    if ( operator new(0xC0u) != nullptr )
      return sub_559BD0(a2);
    return 0;
  }
  if ( Block == (void *)9 )
  {
    if ( operator new(0x38u) != nullptr )
      return sub_5563B0(a2);
    return 0;
  }
  if ( Block == (void *)10 )
  {
    if ( operator new(0x38u) != nullptr )
      return sub_5564D0(a2);
    return 0;
  }
  if ( Block == (void *)11 )
  {
    if ( operator new(0x100u) != nullptr )
      return sub_644890(a2);
    return 0;
  }
  if ( Block == (void *)17 )
  {
    if ( operator new(0x34u) != nullptr )
      return sub_554A20(a2);
    return 0;
  }
  if ( Block == (void *)18 )
  {
    if ( operator new(0xD8u) != nullptr )
      return sub_55A410(a2);
    return 0;
  }
  if ( Block == (void *)19 )
  {
    if ( operator new(0x4Cu) != nullptr )
      return sub_558580(a2);
    return 0;
  }
  if ( Block == (void *)20 )
  {
    if ( operator new(0x34u) != nullptr )
      return sub_554B40(a2);
    return 0;
  }
  if ( Block == (void *)21 )
  {
    if ( operator new(0x34u) != nullptr )
      return sub_554C60(a2);
    return 0;
  }
  if ( Block == (void *)22 )
  {
    if ( operator new(0x34u) != nullptr )
      return sub_554D80(a2);
    return 0;
  }
  if ( Block == (void *)23 )
  {
    if ( operator new(0xA0u) != nullptr )
      return sub_558100(a2);
    return 0;
  }
  if ( Block == (void *)24 )
  {
    if ( operator new(0x80u) != nullptr )
      return sub_5586D0(a2);
    return 0;
  }
  if ( Block == (void *)25 )
  {
    if ( operator new(0x30u) != nullptr )
      return sub_554EA0(a2);
    return 0;
  }
  if ( Block == (void *)26 )
  {
    if ( operator new(0x118u) != nullptr )
      return sub_55A720(a2);
    return 0;
  }
  if ( Block == (void *)27 )
  {
    if ( operator new(0x2Cu) != nullptr )
      return sub_554FC0(a2);
    return 0;
  }
  if ( Block == (void *)28 )
  {
    if ( operator new(0x24u) != nullptr )
      return sub_5550F0(a2);
    return 0;
  }
  if ( Block == (void *)29 )
  {
    if ( operator new(0x58u) != nullptr )
      return sub_555210(a2);
    return 0;
  }
  if ( Block == (void *)30 )
  {
    if ( operator new(0x4Cu) != nullptr )
      return sub_555370(a2);
    return 0;
  }
  if ( Block == (void *)31 )
  {
    if ( operator new(0x70u) != nullptr )
      return sub_558890(a2);
    return 0;
  }
  if ( Block == (void *)32 )
  {
    if ( operator new(0x84u) != nullptr )
      return sub_558A50(a2);
    return 0;
  }
  if ( Block == (void *)33 )
  {
    if ( operator new(0xDCu) != nullptr )
      return sub_55AAF0(a2);
    return 0;
  }
  if ( Block == (void *)34 )
  {
    if ( operator new(0x74u) != nullptr )
      return sub_558C60(a2);
    return 0;
  }
  if ( Block == (void *)35 )
  {
    if ( operator new(0xC0u) != nullptr )
      return sub_558320(a2);
    return 0;
  }
  if ( Block == (void *)36 )
  {
    if ( operator new(0x28u) != nullptr )
      return sub_5554C0(a2);
    return 0;
  }
  if ( Block == (void *)37 )
  {
    if ( operator new(0xC4u) != nullptr )
      return sub_558E20(a2);
    return 0;
  }
  if ( Block == (void *)38 )
  {
    if ( operator new(0x30u) != nullptr )
      return sub_5555E0(a2);
    return 0;
  }
  if ( Block == (void *)39 )
  {
    if ( operator new(0x70u) != nullptr )
      return sub_559080(a2);
    return 0;
  }
  if ( Block == (void *)40 )
  {
    if ( operator new(0x30u) != nullptr )
      return sub_555700(a2);
    return 0;
  }
  if ( Block == (void *)41 )
  {
    if ( operator new(0x94u) != nullptr )
      return sub_559240(a2);
    return 0;
  }
  if ( Block == (void *)42 )
  {
    if ( operator new(0xB8u) != nullptr )
      return sub_5596E0(a2);
    return 0;
  }
  if ( Block == nullptr )
  {
    if ( operator new(0x6Cu) != nullptr )
      return sub_555C80(a2);
    return 0;
  }
  if ( Block == (void *)43 )
  {
    if ( operator new(0x94u) != nullptr )
      return sub_555E20(a2);
    return 0;
  }
  if ( Block == (void *)44 )
  {
    if ( operator new(0x2Cu) != nullptr )
      return sub_556290(a2);
    return 0;
  }
  if ( Block == (void *)45 )
  {
    if ( operator new(0x48u) != nullptr )
      return sub_5565F0(a2);
    return 0;
  }
  if ( Block == (void *)46 )
  {
    if ( operator new(0x98u) != nullptr )
      return sub_556740(a2);
    return 0;
  }
  if ( Block == (void *)47 )
  {
    if ( operator new(0x54u) != nullptr )
      return sub_556A10(a2);
    return 0;
  }
  if ( Block == (void *)48 )
  {
    if ( operator new(0x48u) != nullptr )
      return sub_556BF0(a2);
    return 0;
  }
  if ( Block == (void *)13 )
  {
    if ( operator new(0x34u) != nullptr )
      return sub_525360(a2);
    return 0;
  }
  if ( Block == (void *)15 )
  {
    if ( operator new(0x38u) != nullptr )
      return sub_50E650(a2);
  }
  else if ( Block == (void *)16 )
  {
    if ( operator new(0x38u) != nullptr )
      return sub_50E650(a2);
  }
  else if ( Block == (void *)49 )
  {
    if ( operator new(0x5Cu) != nullptr )
      return sub_556B30(a2);
  }
  else if ( Block == (void *)50 )
  {
    if ( operator new(0x50u) != nullptr )
      return sub_556A70(a2);
  }
  else if ( Block == (void *)51 )
  {
    if ( operator new(0x48u) != nullptr )
      return sub_643EF0(a2);
  }
  else if ( Block == (void *)52 )
  {
    if ( operator new(0x6Cu) != nullptr )
      return sub_556E30(a2);
  }
  else if ( Block == (void *)53 )
  {
    if ( operator new(0x30u) != nullptr )
      return sub_556FD0(a2);
  }
  else if ( Block == (void *)12 )
  {
    if ( operator new(0x15Cu) != nullptr )
      return sub_56F2B0(a2);
  }
  else if ( Block == (void *)54 )
  {
    if ( operator new(0x80u) != nullptr )
      return sub_555AE0(a2);
  }
  else if ( Block == (void *)55 )
  {
    if ( operator new(0x34u) != nullptr )
      return sub_5570F0(a2);
  }
  else if ( Block == (void *)56 )
  {
    if ( operator new(0x48u) != nullptr )
      return sub_557460(a2);
  }
  else if ( Block == (void *)58 )
  {
    if ( operator new(0x48u) != nullptr )
      return sub_5575B0(a2);
  }
  else if ( Block == (void *)59 )
  {
    if ( operator new(0x6Cu) != nullptr )
      return sub_557710(a2);
  }
  else if ( Block == (void *)60 )
  {
    if ( operator new(0x68u) != nullptr )
      return sub_5578B0(a2);
  }
  else if ( Block == (void *)14 )
  {
    if ( operator new(0x60u) != nullptr )
      return sub_557A50(a2);
  }
  else if ( Block == (void *)57 )
  {
    if ( operator new(0x70u) != nullptr )
      return sub_557BB0(a2);
  }
  else if ( Block == (void *)67 )
  {
    if ( operator new(0x2Cu) != nullptr )
      return sub_643910(a2);
  }
  else if ( Block == (void *)61 )
  {
    if ( operator new(0x70u) != nullptr )
      return sub_557D50(a2);
  }
  else if ( Block == (void *)62 )
  {
    if ( operator new(0xE8u) != nullptr )
      return sub_55A0D0(a2);
  }
  else if ( Block == (void *)63 )
  {
    if ( operator new(0x64u) != nullptr )
      return sub_557EF0(a2);
  }
  else if ( Block == (void *)64 )
  {
    if ( operator new(0x2Cu) != nullptr )
      return sub_557220(a2);
  }
  else if ( Block == (void *)65 )
  {
    if ( operator new(0x38u) != nullptr )
      return sub_557340(a2);
  }
  else if ( Block == (void *)66 )
  {
    if ( operator new(0x50u) != nullptr )
      return sub_556B90(a2);
  }
  else if ( Block == (void *)68 )
  {
    if ( operator new(0x80u) != nullptr )
      return sub_559E50(a2);
  }
  else if ( Block == (void *)69 )
  {
    if ( operator new(0x58u) != nullptr )
      return sub_556AD0(a2);
  }
  else if ( Block == (void *)70 && operator new(0x2Cu) != nullptr )
  {
    return sub_556D10(a2);
  }
  return 0;
}


// ============================================================
// 【分区 10】商城数据辅助（0x55C0F0-0x55CB60）
// 商城对象基件在 0x55C2B0（418DD0/422E70/4938F0/491D00）；装配在 0x55C500
// （4F33A0/4F2C10）；事件链在 0x55C860（126 行 44E850/44E8D0）。
// ============================================================
// ------------------------------------------------------------
// 0x55C0F0 unknown_libname_6 —— unknown_libname_6（库函数桩，13 行）
// ------------------------------------------------------------
// Microsoft VisualC 2-14/net runtime
void /*thiscall*/ unknown_libname_6(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
}



// ------------------------------------------------------------
// 0x55C100 sub_55C100 —— 商城辅助（25 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_55C100(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*this;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  *this = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *(this + 1) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  *(this + 2) = 0;
}



// ------------------------------------------------------------
// 0x55C140 sub_55C140 —— 商城辅助 2（13 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_55C140(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x55C150 sub_55C150 —— 商城辅助 3（30 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_55C150(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*this;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  *this = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  *(this + 1) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x55C1A0 sub_55C1A0 —— 商城辅助 4（66 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_55C1A0(int this)
{
  *(uint32_t *)(this + 44) = 4;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 596) = 0;
  *(uint32_t *)(this + 600) = 0;
  memset((void *)(this + 7324), 0, 0x50u);
  *(uint32_t *)(this + 7416) = 0;
  *(uint32_t *)(this + 7420) = 0;
  *(uint32_t *)(this + 7424) = 0;
  *(uint32_t *)(this + 7428) = 0;
  *(uint32_t *)(this + 7432) = 0;
  *(uint32_t *)(this + 7436) = 0;
  *(uint32_t *)(this + 7440) = 0;
  *(uint32_t *)(this + 7444) = 0;
  *(uint32_t *)(this + 7448) = 0;
  *(uint32_t *)(this + 7452) = 0;
  *(uint32_t *)(this + 7456) = 0;
  *(uint32_t *)(this + 7460) = 0;
  *(uint32_t *)(this + 7464) = 0;
  *(uint32_t *)(this + 7468) = 0;
  *(uint32_t *)(this + 7472) = 0;
  *(uint32_t *)(this + 7476) = 0;
  *(uint32_t *)(this + 7480) = 0;
  *(uint32_t *)(this + 7484) = 0;
  *(uint32_t *)(this + 7488) = 0;
  *(uint32_t *)(this + 7492) = 0;
  *(uint32_t *)(this + 7496) = 0;
  memset((void *)(this + 348), 0, 0x80u);
  *(uint32_t *)(this + 572) = 0;
  *(uint32_t *)(this + 576) = 0;
  *(uint32_t *)(this + 580) = 0;
  *(uint32_t *)(this + 584) = 0;
  *(uint32_t *)(this + 588) = 0;
  *(uint32_t *)(this + 592) = 0;
  *(uint32_t *)(this + 492) = 0;
  *(uint32_t *)(this + 496) = 0;
  *(uint32_t *)(this + 500) = 0;
  *(uint32_t *)(this + 504) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 9956) = 0;
  *(uint32_t *)(this + 9960) = 0;
  *(uint32_t *)(this + 9964) = 0;
  *(uint32_t *)(this + 9968) = 0;
  *(uint32_t *)(this + 9972) = 0;
  *(uint32_t *)(this + 9976) = 0;
  *(uint32_t *)(this + 9980) = 0;
  *(uint32_t *)(this + 9984) = 0;
  *(uint32_t *)(this + 9988) = 0;
  *(uint32_t *)(this + 9952) = 0;
  *(uint32_t *)(this + 340) = 0;
  *(uint32_t *)(this + 10108) = 0;
  *(uint32_t *)(this + 10112) = 0;
  *(uint8_t *)(this + 10128) = 0;
  *(uint32_t *)(this + 10120) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x55C2B0 sub_55C2B0 —— 商城对象基件（418DD0/422E70/4938F0/491D00，96 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_55C2B0(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // edi
  char *v6; // eax
  int result; // eax
  int v8; // ecx
  int *v9; // eax
  int v10; // edi
  int v11; // [esp+8h] [ebp-108h]
  char Buffer[256]; // [esp+Ch] [ebp-104h] BYREF
  int v13; // [esp+10Ch] [ebp-4h]

  v13 = dword_796E50;
  v2 = sub_418DD0(0);
  if ( v2 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v2 + 128))(
      v2,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      -1,
      1333788672,
      1333788672);
  v3 = *(uint32_t *)(this + 44);
  v4 = *(uint32_t *)(this + 8 * v3 + 7440);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v4 + 128))(
      v4,
      *(uint32_t *)(*(uint32_t *)(this + 4 * v3 + 7420) + 20),
      *(uint32_t *)(*(uint32_t *)(this + 4 * v3 + 7420) + 24),
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      -1,
      1333788672,
      1333788672);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 168);
  v5 = *(uint32_t *)dword_79C0B0;
  v6 = sub_422E70(*(uint32_t *)(this + 44) + 1610);
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v5 + 80))(dword_79C0B0, 153, 50, -2171168, v6);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  if ( *(uint32_t *)(this + 44) != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 64);
    sprintf(
      Buffer,
      "%2d/%-2d",
      *(uint32_t *)(this + 4 * *(uint32_t *)(this + 44) + 476) + 1,
      *(uint32_t *)(this + 4 * *(uint32_t *)(this + 44) + 492) + 1);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 186, 443, -1, Buffer);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  }
  else
  {
    result = *(uint32_t *)(this + 9956);
    if ( result != 0 )
    {
      v8 = dword_77F6DC;
      dword_77F6DC = 1065353216;
      v11 = v8;
      v9 = (int *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 9956) + 344))(*(uint32_t *)(this + 9956));
      sub_4938F0(*v9);
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 9956) + 344))(*(uint32_t *)(this + 9956));
      sub_491D00(dword_79C0B0, 513, 200, 0.0);
      dword_77F6DC = v11;
      v10 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 9952) + 1032))(*(uint32_t *)(this + 9952));
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 64);
      sprintf(
        Buffer,
        "%2d/%-2d",
        *(uint32_t *)(this + 4 * (*(uint32_t *)(this + 7588) + 8 * v10) + 7592) + 1,
        *(uint32_t *)(this + 4 * (*(uint32_t *)(this + 7588) + 8 * v10) + 7720) + 1);
      (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        186,
        443,
        -1,
        Buffer);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x55C500 sub_55C500 —— 商城装配件（4F33A0/4F2C10/418DD0，110 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_55C500(int this, int a2)
{
  int v3; // ecx
  int v4; // esi
  uint32_t *j; // edx
  uint32_t *v6; // eax
  int v7; // eax
  uint32_t *v8; // ecx
  int v9; // edi
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // [esp-4h] [ebp-1Ch]
  int v17; // [esp-4h] [ebp-1Ch]
  int v18; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]
  int *v20; // [esp+14h] [ebp-4h]

  v3 = *(uint32_t *)(this + 44);
  v4 = 0;
  if ( v3 == 0 )
  {
    v20 = (int *)(this + 7324);
    v8 = (uint32_t *)(this + 680);
    for ( i = this + 680; ; i += 84 )
    {
      v9 = *v20;
      if ( a2 == *v20 && *(uint8_t *)(v9 + 17) != 0 )
      {
        if ( *v8 != 0 )
        {
          v17 = *(v8 - 14);
          v15 = sub_4F33A0(*(v8 - 16));
          sub_4F2C10(*(&dword_795248 + 2 * v4), dword_79524C[2 * v4], v15, v17);
          return;
        }
        v10 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 9952) + 792))(
                *(uint32_t *)(this + 9952),
                dword_725D50[v4]);
        if ( v10 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, int))(*(uint32_t *)v10 + 8))(
            v10,
            *(&dword_795248 + 2 * v4),
            dword_79524C[2 * v4],
            0,
            1);
          v11 = *(uint32_t *)(this + 9908);
          if ( v11 != 0 )
            (*(void (/*stdcall*/ **)(uint32_t, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v11 + 128))(
              *(&dword_795248 + 2 * v4),
              dword_79524C[2 * v4],
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              -1929379841,
              1333788672,
              1333788672);
        }
        else
        {
          v12 = *(uint32_t *)(v9 + 24);
          v13 = *(uint32_t *)(v9 + 20);
          v18 = v12;
          v14 = sub_418DD0(dword_725D50[v4] + 19);
          if ( v14 != 0 )
            (*(void (/*stdcall*/ **)(int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
              v13,
              v18,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              -1929379841,
              1333788672,
              1333788672);
        }
      }
      ++v4;
      v8 = (uint32_t *)(i + 84);
      ++v20;
      if ( v4 >= 20 )
        return;
    }
  }
  for ( j = (uint32_t *)(this + 7324); ; ++j )
  {
    if ( a2 == *j )
    {
      v6 = (uint32_t *)(this + 84 * (v4 + 20 * v3));
      if ( v6[170] != 0 )
        break;
    }
    if ( ++v4 >= 20 )
      return;
  }
  v16 = v6[156];
  v7 = sub_4F33A0(v6[154]);
  sub_4F2C10(*(&dword_795248 + 2 * v4), dword_79524C[2 * v4], v7, v16);
}



// ------------------------------------------------------------
// 0x55C6E0 sub_55C6E0 —— 商城联动（4872A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_55C6E0(uint32_t *this)
{
  int result; // eax
  int v2; // ecx

  result = *(this + 13);
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE38 == *(uint32_t *)(result + 12) )
  {
    result = *(this + 86);
    if ( result != -1 )
    {
      v2 = *(this + 11);
      if ( v2 == 0 || v2 == 2 )
        return sub_4872A0(result);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x55C730 sub_55C730 —— 商城文本（24 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_55C730(uint32_t *this)
{
  int result; // eax
  uint32_t *i; // edx

  result = 0;
  for ( i = this + 420 * *(this + 11) + 170; *i == 0; i += 21 )
  {
    if ( ++result >= 20 )
    {
      *(uint8_t *)(*(this + 1870) + 17) = 0;
      return result;
    }
  }
  result = *(this + 1870);
  *(uint8_t *)(result + 17) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x55C770 sub_55C770 —— 商城文本 2（522300/41A5E0/4E9C00/445150）
// ------------------------------------------------------------
int /*stdcall*/ sub_55C770(void *a1)
{
  int result; // eax
  int v2; // edi
  int v3; // eax
  int *v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // edx
  char v8[60]; // [esp+4h] [ebp-48h] BYREF
  int v9; // [esp+48h] [ebp-4h]

  result = sub_522300(a1, 1, 0, 0, -1, 0);
  v2 = result;
  if ( result != 0 )
  {
    v3 = __RTDynamicCast(result, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
    v4 = (int *)v3;
    if ( v3 != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 172))(v3);
      v6 = sub_41A5E0(v5 + 18);
      sub_4E9C00(dword_8F84B0, 0, 0, v6, 0);
      v7 = *v4;
      v9 = 0;
      (*(void (/*thiscall*/ **)(int *, char *))(v7 + 184))(v4, v8);
      v9 = -1;
      sub_445150(v8);
    }
    return v2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x55C840 sub_55C840 —— 商城参数（423200/423380）
// ------------------------------------------------------------
int sub_55C840()
{
  sub_423200(dword_8F7B08, 66);
  return sub_423380(dword_8F7B08);
}



// ------------------------------------------------------------
// 0x55C860 sub_55C860 —— 商城事件链（126 行：44E850/44E8D0 状态机）
// ------------------------------------------------------------
char /*thiscall*/ sub_55C860(int this)
{
  LONG x; // ebx
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // ecx
  uint32_t *i; // edx
  LONG v8; // edx
  LONG v9; // edx
  int v10; // esi
  int v11; // ebx
  LONG v12; // ecx
  LONG v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v17; // [esp+Ch] [ebp-Ch]
  uint32_t *v18; // [esp+10h] [ebp-8h]
  LONG y; // [esp+14h] [ebp-4h]

  x = pt.x;
  y = pt.y;
  v3 = *(uint32_t *)(*(uint32_t *)(this + 4) + 2504);
  v4 = 0;
  v17 = 5;
  if ( v3 == 1 || v3 == 2 || *(uint32_t *)(this + 10108) != 0 )
  {
LABEL_31:
    LOBYTE(v4) = dword_9B88D0;
    if ( dword_9B88D0 != 0 )
      LOBYTE(v4) = sub_44E850(*(uint32_t **)(this + 4), 26);
    return v4;
  }
  if ( *(uint32_t *)(this + 340) != 0 )
  {
    v4 = *(uint32_t *)(this + 340);
    v5 = 2 * *(uint32_t *)(this + 344);
    x = dword_725BC0[v5];
    y = dword_725BC4[v5];
    v17 = 2;
  }
  v6 = 0;
  if ( v4 == 0 )
  {
    for ( i = (uint32_t *)(this + 572); ; i = v18 + 1 )
    {
      v18 = i;
      if ( v6 >= 6 )
        break;
      if ( *i != 0 )
      {
        v8 = dword_795214[2 * v6];
        if ( pt.x >= v8 && pt.x <= v8 + 28 )
        {
          v9 = dword_795218[2 * v6];
          if ( pt.y >= v9 && pt.y <= v9 + 28 )
          {
            x = dword_795214[2 * v6];
            v4 = *(uint32_t *)(*(uint32_t *)(this + 4 * v6 + 572) + 76);
            y = dword_795218[2 * v6];
            break;
          }
        }
      }
      ++v6;
    }
  }
  v10 = 0;
  if ( v4 == 0 )
  {
    v11 = this + 7324;
    while ( v10 < 20 )
    {
      if ( *(uint8_t *)(*(uint32_t *)v11 + 17) != 0 )
      {
        v12 = *(&dword_795248 + 2 * v10);
        if ( pt.x >= v12 && pt.x <= v12 + 28 )
        {
          v13 = dword_79524C[2 * v10];
          if ( pt.y >= v13 && pt.y <= v13 + 28 )
          {
            v14 = *(uint32_t *)(this + 44);
            if ( v14 != 0 )
            {
              v15 = 84 * (v10 + 20 * v14);
              if ( *(uint32_t *)(v15 + this + 680) != 0 )
                v4 = *(uint32_t *)(v15 + this + 680);
            }
            else
            {
              v4 = *(uint32_t *)(84 * v10 + this + 680);
              if ( v4 == 0 )
              {
                v4 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 9952) + 792))(
                       *(uint32_t *)(this + 9952),
                       dword_725D50[v10]);
                v17 = 2;
              }
            }
            x = *(&dword_795248 + 2 * v10);
            y = dword_79524C[2 * v10];
            if ( v4 != 0 )
              goto LABEL_33;
            goto LABEL_31;
          }
        }
      }
      ++v10;
      v11 += 4;
    }
    goto LABEL_31;
  }
LABEL_33:
  if ( dword_9B88D0 != v4 )
  {
    v4 = sub_44E8D0(*(char **)(this + 4), (void *)0x1A, v4, v17);
    if ( v4 != 0 )
      LOBYTE(v4) = (*(int (/*thiscall*/ **)(int, LONG, LONG, int, int))(*(uint32_t *)v4 + 48))(v4, x, y, 28, 28);
  }
  return v4;
}


// ------------------------------------------------------------
// 0x55CA50 sub_55CA50 —— 商城控件定位（69A5F0 + 44E850）
// ------------------------------------------------------------
char /*thiscall*/ sub_55CA50(int this, char a2, int a3)
{
  char result; // al
  int v5; // edi
  int v6; // ebx

  result = a2;
  *(uint8_t *)(*(uint32_t *)(this + 7404) + 16) = a2;
  *(uint8_t *)(*(uint32_t *)(this + 7408) + 16) = a2;
  if ( a2 == 0 )
    goto LABEL_7;
  v5 = (uint64_t)((double)dword_725CB0[2 * a3] + 22.4);
  v6 = (uint64_t)((double)dword_725CB4[2 * a3] + 22.4);
  if ( v5 + 100 > 640 )
    v5 = 540;
  sub_69A5F0(*(uint32_t **)(this + 7404), v5, v6);
  sub_69A5F0(*(uint32_t **)(this + 7408), v5, v6 + 21);
  result = dword_9B88D0;
  if ( dword_9B88D0 != 0 )
  {
    if ( dword_795378 == 5 )
    {
      result = sub_44E850(*(uint32_t **)(this + 4), 26);
LABEL_7:
      *(uint32_t *)(this + 7412) = a3;
      return result;
    }
    *(uint32_t *)(this + 7412) = a3;
    return a3;
  }
  else
  {
    *(uint32_t *)(this + 7412) = a3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x55CB10 sub_55CB10 —— 商城状态（44E8D0）
// ------------------------------------------------------------
int /*thiscall*/ sub_55CB10(void *this, int a2, int a3)
{
  uint32_t v4[2]; // [esp+0h] [ebp-8h] BYREF

  v4[1] = this;
  v4[0] = a2;
  return sub_44E8D0((char *)dword_8F8528, (void *)0x33, (int)v4, a3);
}



// ============================================================
// 【分区 11】商城核心辅助与 CNRDCashShop 主类（0x55CB60-0x55E7F0）
// 商城公共入口 0x55CCB0（全文件被引最多的商城辅助）；面板绘制 0x55D6E0/0x55DA50
// =商城面板绘制（cashshopdoubleevent.img）；0x55E700=CNRDCashShop__vmt0
// 主构造（55C2B0/55D6E0/55DA50/55C500/55D3C0/55E320 装配链）。
// ============================================================
// ------------------------------------------------------------
// 0x55CB60 sub_55CB60 —— 商城取串（422E70，54 行）
// ------------------------------------------------------------
char */*stdcall*/ sub_55CB60(int a1)
{
  char *result; // eax

  switch ( a1 )
  {
    case 1:
      result = sub_422E70(264);
      break;
    case 4:
      result = sub_422E70(255);
      break;
    case 10:
      result = sub_422E70(256);
      break;
    case 11:
      result = sub_422E70(258);
      break;
    case 12:
      result = sub_422E70(257);
      break;
    case 13:
      result = sub_422E70(259);
      break;
    case 17:
      result = sub_422E70(260);
      break;
    case 19:
      result = sub_422E70(261);
      break;
    case 20:
      result = sub_422E70(253);
      break;
    case 21:
      result = sub_422E70(254);
      break;
    case 23:
      result = sub_422E70(262);
      break;
    case 25:
      result = sub_422E70(263);
      break;
    default:
      result = sub_422E70(265);
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x55CCB0 sub_55CCB0 —— 商城公共入口辅助（19 行——0x55/0x64 两区块商城函数共同调用）
// ------------------------------------------------------------
int /*stdcall*/ sub_55CCB0(int a1)
{
  if ( a1 != 0
    && (**(int (/*thiscall*/ ***)(int))a1)(a1) == 2
    && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 172))(a1) <= 7 )
  {
    return a1;
  }
  else
  {
    return 0;
  }
}



// ------------------------------------------------------------
// 0x55CCF0 sub_55CCF0 —— 商城辅助 5（30 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_55CCF0(char *this, uint32_t *a2)
{
  int v2; // ebx
  int v5; // edi
  char *v6; // eax

  v2 = a2[19];
  if ( v2 == 0
    || (**(int (/*thiscall*/ ***)(uint32_t))v2)(a2[19]) != 2
    || *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 172))(v2) > 7 )
  {
    return 0;
  }
  v5 = 0;
  while ( dword_725D50[v5] != *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 172))(v2) )
  {
    if ( ++v5 >= 20 )
      return 0;
  }
  v6 = this + 84 * v5 + 604;
  qmemcpy(v6, a2, 0x54u);
  v6[80] = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x55CD70 sub_55CD70 —— 商城辅助 6（21 行）
// ------------------------------------------------------------
int /*stdcall*/ sub_55CD70(int a1)
{
  int v1; // eax
  int v2; // ecx
  int result; // eax

  *(uint32_t *)(a1 + 40) = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 76) + 16))(*(uint32_t *)(a1 + 76))
                                   + 40);
  v1 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 76) + 16))(*(uint32_t *)(a1 + 76));
  v2 = *(uint32_t *)(a1 + 76);
  *(uint32_t *)(a1 + 32) = *(uint32_t *)(v1 + 36);
  result = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 16))(v2) + 44);
  *(uint32_t *)(a1 + 36) = result;
  return result;
}



// ------------------------------------------------------------
// 0x55CDB0 sub_55CDB0 —— 商城辅助 7（24 行）
// ------------------------------------------------------------
int */*thiscall*/ sub_55CDB0(uint32_t **this, uint32_t *a2)
{
  int *result; // eax
  int v5; // edi
  int v6; // eax
  int v7; // [esp+14h] [ebp+8h]

  result = (int *)(*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 172))(a2);
  v5 = *result;
  if ( *result <= 7 )
  {
    *(this + v5 + 2490) = a2;
    v7 = **(this + 2489);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 16))(a2);
    return (int *)(*(int (/*thiscall*/ **)(uint32_t, int, uint32_t))(v7 + 352))(*(this + 2489), v5, *(uint32_t *)(v6 + 4));
  }
  return result;
}



// ------------------------------------------------------------
// 0x55CE00 sub_55CE00 —— 商城辅助 8（429830）
// ------------------------------------------------------------
void /*thiscall*/ sub_55CE00(uint32_t **this, int a2)
{
  int v3; // eax

  if ( a2 <= 7
    && sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0
    && *(this + a2 + 2490) != nullptr )
  {
    *(this + a2 + 2490) = nullptr;
    v3 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t))(**(this + 2489) + 352))(
      *(this + 2489),
      a2,
      *(uint32_t *)(v3 + 4 * a2 + 72));
  }
}



// ------------------------------------------------------------
// 0x55CE70 sub_55CE70 —— 商城辅助 9（28 行）
// ------------------------------------------------------------
int /*stdcall*/ sub_55CE70(int a1)
{
  int result; // eax
  uint32_t *v2; // edx
  int v3; // ecx

  result = 0;
LABEL_2:
  v2 = &dword_725C50;
  while ( 1 )
  {
    v3 = 2 * (*v2 + 8 * result);
    if ( a1 >= dword_725DF0[v3] && a1 <= dword_725DF4[v3] )
      return result;
    if ( (int)++v2 >= (int)dword_725C70 )
    {
      if ( ++result < 4 )
        goto LABEL_2;
      return (a1 > 38999) - 2;
    }
  }
}



// ------------------------------------------------------------
// 0x55CED0 sub_55CED0 —— 商城辅助 10（31 行）
// ------------------------------------------------------------
int /*stdcall*/ sub_55CED0(int a1)
{
  int v1; // esi
  int *v2; // edx
  int result; // eax
  int v4; // ecx

  v1 = 0;
LABEL_2:
  v2 = &dword_725C50;
  while ( 1 )
  {
    result = *v2;
    v4 = 2 * (v1 + *v2);
    if ( a1 >= dword_725DF0[v4] && a1 <= dword_725DF4[v4] )
      return result;
    if ( (int)++v2 >= (int)dword_725C70 )
    {
      v1 += 8;
      if ( v1 < 32 )
        goto LABEL_2;
      return -1;
    }
  }
}



// ------------------------------------------------------------
// 0x55CF20 sub_55CF20 —— 商城格子绘制（69C690 + 491530/491630，50 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_55CF20(uint32_t *this)
{
  int i; // edi
  int result; // eax
  int v4; // esi
  int v5; // ecx

  for ( i = 0; i < 12; ++i )
  {
    result = i + 12 * sub_69C690(*(this + 84));
    if ( result < 105 && result < *((uint32_t *)dword_8F8534 + 2) )
    {
      v4 = *(uint32_t *)(*((uint32_t *)dword_8F8534 + 3) + 4 * result);
      if ( v4 != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)v4 + 8))(
                   v4,
                   dword_725BC0[2 * i],
                   dword_725BC4[2 * i],
                   0,
                   1);
        if ( *(this + 85) == v4 )
        {
          sub_491530(2, 0);
          v5 = *(this + 2478);
          if ( v5 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v5 + 128))(
              v5,
              dword_725BC0[2 * i],
              dword_725BC4[2 * i],
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              -1,
              1333788672,
              1333788672);
          result = sub_491630(2);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x55CFF0 sub_55CFF0 —— 商城格子绘制 2（69C690 + 491530/491630，72 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_55CFF0(uint32_t *this)
{
  int i; // edi
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int result; // eax
  int v7; // esi
  int v8; // ecx

  for ( i = 0; i < 12; ++i )
  {
    v3 = *(this + 2529);
    v4 = 0;
    if ( v3 != 0 )
    {
      v5 = v3 - 1;
      if ( v5 != 0 )
      {
        if ( v5 == 1 )
          v4 = 73;
      }
      else
      {
        v4 = 41;
      }
    }
    else
    {
      v4 = 9;
    }
    result = i + v4 + 12 * sub_69C690(*(this + 84));
    if ( result - v4 < 32 && result < *((uint32_t *)dword_8F852C + 2) )
    {
      v7 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * result);
      if ( v7 != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)v7 + 8))(
                   v7,
                   dword_725BC0[2 * i],
                   dword_725BC4[2 * i],
                   0,
                   1);
        if ( *(this + 85) == v7 )
        {
          sub_491530(2, 0);
          v8 = *(this + 2478);
          if ( v8 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v8 + 128))(
              v8,
              dword_725BC0[2 * i],
              dword_725BC4[2 * i],
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              -1,
              1333788672,
              1333788672);
          result = sub_491630(2);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x55D0F0 sub_55D0F0 —— 商城翻页（69C690 + 44A980 数组，80 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_55D0F0(uint32_t *this, int *a2)
{
  LONG x; // esi
  LONG y; // ecx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // esi
  int v12; // eax
  int v13; // eax
  POINT v15; // 0:^10.8

  x = pt.x;
  y = pt.y;
  v15 = pt;
  v5 = 0;
  while ( 1 )
  {
    v6 = dword_725BC0[2 * v5];
    if ( x < v6 )
      goto LABEL_18;
    if ( x > v6 + 28 )
      goto LABEL_18;
    v7 = dword_725BC4[2 * v5];
    if ( y < v7 || y > v7 + 28 )
      goto LABEL_18;
    v8 = v5 + 12 * sub_69C690(*(this + 84));
    v9 = *(this + 11);
    if ( v9 == 0 )
      break;
    if ( v9 == 2 )
    {
      v10 = *(this + 2529);
      v11 = 0;
      if ( v10 != 0 )
      {
        v12 = v10 - 1;
        if ( v12 != 0 )
        {
          if ( v12 == 1 )
            v11 = 73;
        }
        else
        {
          v11 = 41;
        }
      }
      else
      {
        v11 = 9;
      }
      v13 = v5 + v11 + 12 * sub_69C690(*(this + 84));
      if ( v13 - v11 < 32 )
      {
        if ( a2 != nullptr )
          *a2 = v13;
        return sub_44A980(dword_8F852C, v13);
      }
      x = v15.x;
    }
LABEL_18:
    if ( ++v5 >= 12 )
      return 0;
    y = v15.y;
  }
  if ( v8 >= 105 )
    goto LABEL_18;
  if ( a2 != nullptr )
    *a2 = v8;
  return sub_44A980(dword_8F8534, v8);
}



// ------------------------------------------------------------
// 0x55D210 sub_55D210 —— 商城确认参数（49BE70/422E70/43BEE0 + 423200/423290/423380，40 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_55D210(int this)
{
  char result; // al
  uint32_t *v3; // esi
  char *v4; // eax
  int v5; // [esp+4h] [ebp-8h] BYREF
  char v6[4]; // [esp+8h] [ebp-4h] BYREF

  result = *(uint8_t *)(this + 7584);
  if ( result == 0 )
  {
    if ( (uint8_t)sub_49BE70(*((uint32_t *)dword_8F8528 + 605)) != 0 )
    {
      v3 = *((uint32_t **)dword_8F8528 + 7);
      v4 = sub_422E70(3015);
      return sub_43BEE0(v3, (int)v4, -6567706, 0, -1);
    }
    else
    {
      sub_423200(dword_8F7B08, 67);
      v6[0] = 1;
      sub_423290(dword_8F7B08, (int)v6, 1);
      v6[0] = *(uint8_t *)(this + 10040);
      sub_423290(dword_8F7B08, (int)v6, 1);
      v5 = *(uint16_t *)(this + 10050);
      sub_423290(dword_8F7B08, (int)&v5, 2);
      v5 = *(uint32_t *)(this + 10024);
      sub_423290(dword_8F7B08, (int)&v5, 4);
      result = sub_423380(dword_8F7B08);
      *(uint8_t *)(this + 7584) = 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x55D300 sub_55D300 —— 商城确认状态（422E70/44E8D0）
// ------------------------------------------------------------
int /*thiscall*/ sub_55D300(char **this)
{
  char *v2; // eax

  v2 = sub_422E70(275);
  return sub_44E8D0(*(this + 1), (void *)0x1B, (int)v2, 0);
}



// ------------------------------------------------------------
// 0x55D320 sub_55D320 —— 商城数据（50D910）
// ------------------------------------------------------------
int sub_55D320()
{
  int v0; // eax
  int v1; // eax

  v0 = sub_50D910();
  if ( v0 == 0 )
    return 5;
  v1 = v0 - 1;
  if ( v1 == 0 )
    return 6;
  if ( v1 == 1 )
    return 7;
  return -1;
}



// ------------------------------------------------------------
// 0x55D350 sub_55D350 —— 商城数据 2（50D910）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_55D350(uint32_t *a1)
{
  int v1; // eax
  int v2; // eax
  bool v3; // zf
  uint32_t *result; // eax

  v1 = sub_50D910();
  if ( v1 != 0 )
  {
    v2 = v1 - 1;
    if ( v2 == 0 )
    {
      *a1 = 110001;
      a1[1] = 110004;
      a1[2] = 110005;
      return a1;
    }
    v3 = v2 == 1;
    result = a1;
    a1[1] = 110002;
    *a1 = 110001;
    if ( v3 )
    {
      a1[2] = 110006;
      return result;
    }
  }
  else
  {
    result = a1;
    *a1 = 110001;
    a1[1] = 110002;
  }
  result[2] = 110003;
  return result;
}



// ------------------------------------------------------------
// 0x55D3C0 sub_55D3C0 —— 商城主绘制（491530/491630 批次，173 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_55D3C0(int *this, int a2)
{
  int v3; // edx
  int *v4; // esi
  int result; // eax
  int *v6; // ecx
  int v7; // edx
  int v8; // esi
  int v9; // ecx
  int *v10; // edx
  int v11; // esi
  int v12; // esi
  BOOL v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx

  v3 = 0;
  v4 = this + 1855;
  do
  {
    result = *v4;
    if ( a2 == *v4
      && *(uint8_t *)(result + 16) != 0
      && *(uint8_t *)(result + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(result + 12)
       || dword_79BE34 == *(uint32_t *)(result + 12)
       || dword_79BE38 == *(uint32_t *)(result + 12)) )
    {
      v13 = *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12);
      v14 = *(this + 2 * v3 + v13 + 1860);
      if ( v14 == 0 )
        return result;
      return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
               v14,
               *(uint32_t *)(result + 20),
               *(uint32_t *)(result + 24),
               dword_79C0B0,
               1065353216,
               1065353216,
               0,
               -1,
               1333788672,
               1333788672);
    }
    ++v3;
    ++v4;
  }
  while ( v3 < 5 );
  v6 = (int *)*(this + 149);
  v7 = 0;
  while ( 2 )
  {
    v8 = *v6;
    if ( a2 == *v6
      && *(uint8_t *)(v8 + 16) != 0
      && *(uint8_t *)(v8 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(v8 + 12)
       || dword_79BE34 == *(uint32_t *)(v8 + 12)
       || dword_79BE38 == *(uint32_t *)(v8 + 12)) )
    {
      sub_491530(2, 0);
      v15 = *(this + 150);
      if ( v15 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v15 + 128))(
          v15,
          *(uint32_t *)(v8 + 20),
          *(uint32_t *)(v8 + 24),
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          -1,
          1333788672,
          1333788672);
      return sub_491630(2);
    }
    ++v7;
    v6 += 3;
    if ( v7 < 6 )
      continue;
    break;
  }
  if ( *(uint8_t *)(*(this + 1851) + 16) != 0 )
  {
LABEL_27:
    result = *(this + 2474);
    if ( a2 != result )
      return result;
    if ( *(uint8_t *)(result + 16) == 0 )
      return result;
    if ( *(uint8_t *)(result + 17) == 0 )
      return result;
    v12 = *(uint32_t *)(result + 12);
    if ( dword_79BE3C != v12 && dword_79BE34 != v12 && dword_79BE38 != v12 )
      return result;
    result = *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12);
    v14 = *(this + result + 2475);
    if ( v14 == 0 )
      return result;
    result = *(this + 2474);
    return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
             v14,
             *(uint32_t *)(result + 20),
             *(uint32_t *)(result + 24),
             dword_79C0B0,
             1065353216,
             1065353216,
             0,
             -1,
             1333788672,
             1333788672);
  }
  v9 = 0;
  v10 = this + 1831;
  while ( 1 )
  {
    v11 = *v10;
    if ( a2 == *v10
      && *(uint8_t *)(v11 + 16) != 0
      && *(uint8_t *)(v11 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(v11 + 12)
       || dword_79BE34 == *(uint32_t *)(v11 + 12)
       || dword_79BE38 == *(uint32_t *)(v11 + 12))
      && *(this + 420 * *(this + 11) + 21 * v9 + 170) != 0 )
    {
      break;
    }
    ++v9;
    ++v10;
    if ( v9 >= 20 )
      goto LABEL_27;
  }
  result = *(this + 11);
  if ( result == 0 )
  {
    sub_491530(2, 0);
    v17 = *(this + 2478);
    if ( v17 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v17 + 128))(
        v17,
        *(uint32_t *)(v11 + 20) + 4,
        *(uint32_t *)(v11 + 24) + 4,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    return sub_491630(2);
  }
  v16 = *(this + 1854);
  if ( v16 != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v16 + 128))(
             v16,
             *(uint32_t *)(v11 + 20) + 4,
             *(uint32_t *)(v11 + 24) + 4,
             dword_79C0B0,
             1065353216,
             1065353216,
             0,
             -1,
             1333788672,
             1333788672);
  return result;
}


// ------------------------------------------------------------
// 0x55D6E0 sub_55D6E0 —— 商城面板绘制（418DD0/55CFF0/55CF20/422E70/69A110/699000/4049C0/491530/491630，158 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_55D6E0(int this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  const char *v7; // eax
  const char *v8; // eax
  const char *v9; // eax
  int v10; // eax
  int v11; // eax
  uint64_t v12; // rax
  uint8_t v13; // bl
  int v14; // eax
  int v15; // eax
  uint64_t v16; // rax
  uint8_t v17; // bl
  int v18; // eax
  int v20; // [esp-10h] [ebp-118h]
  int v21; // [esp-10h] [ebp-118h]
  int v22; // [esp-10h] [ebp-118h]
  char Buffer[256]; // [esp+4h] [ebp-104h] BYREF
  int v24; // [esp+104h] [ebp-4h]

  v2 = *(uint32_t *)(this + 44);
  v24 = dword_796E50;
  v3 = 1;
  if ( v2 == 0 )
    v3 = 12;
  v4 = sub_418DD0(v3);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v4 + 128))(
      v4,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      -1,
      1333788672,
      1333788672);
  v5 = *(uint32_t *)(this + 9952);
  if ( v5 != 0 )
  {
    v6 = *(uint32_t *)(this + 44);
    if ( v6 != 0 )
    {
      if ( v6 == 2 )
        sub_55CFF0((uint32_t *)this);
    }
    else
    {
      sub_55CF20((uint32_t *)this);
    }
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);
    v20 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8));
    v7 = (const char *)sub_422E70(246);
    sprintf(Buffer, v7, v20);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      480 - *(uint32_t *)(this + 144),
      363,
      -1,
      Buffer);
    v21 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));
    v8 = (const char *)sub_422E70(247);
    sprintf(Buffer, v8, v21);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      609 - *(uint32_t *)(this + 144),
      363,
      -1,
      Buffer);
    v22 = dword_8F7C0C;
    v9 = (const char *)sub_422E70(248);
    sprintf(Buffer, v9, v22);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      590 - *(uint32_t *)(this + 144),
      389,
      -1,
      Buffer);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      589 - *(uint32_t *)(this + 144),
      389,
      -1,
      Buffer);
    v10 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(
            *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4),
            -1);
    sub_69A110(442, 389, v10, this + 116);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    if ( *(uint8_t *)(this + 7540) != 0 )
    {
      v11 = sub_699000(this + 7528);
      v12 = (uint64_t)sub_4049C0(0.0, 510.0, v11, 600);
      v13 = v12;
      if ( (int)v12 > 255 )
      {
        if ( (uint32_t)v12 == 510 )
          *(uint8_t *)(this + 7540) = 0;
        v13 = -2 - v12;
      }
      sub_491530(2, 0);
      v14 = sub_418DD0(7);
      if ( v14 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
          v14,
          410,
          385,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (v13 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_491630(2);
    }
    LOBYTE(v5) = *(uint8_t *)(this + 7568);
    if ( (uint8_t)v5 != 0 )
    {
      v15 = sub_699000(this + 7556);
      v16 = (uint64_t)sub_4049C0(0.0, 510.0, v15, 600);
      v17 = v16;
      if ( (int)v16 > 255 )
      {
        if ( (uint32_t)v16 == 510 )
          *(uint8_t *)(this + 7568) = 0;
        v17 = -2 - v16;
      }
      sub_491530(2, 0);
      v18 = sub_418DD0(13);
      if ( v18 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v18 + 128))(
          v18,
          490,
          385,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (v17 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      LOBYTE(v5) = sub_491630(2);
    }
  }
  return v5;
}


// ------------------------------------------------------------
// 0x55DA50 sub_55DA50 —— 双倍活动面板：加载 interface/cashshop/cashshopdoubleevent.img（667620/4F33A0/4F2C10/418DD0/69A110/422E70，322 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_55DA50(int this, int a2)
{
  int v3; // eax
  int *i; // edx
  int v5; // esi
  uint32_t *v6; // ebx
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // ebx
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // ecx
  const CHAR *v19; // eax
  const char *v20; // eax
  int v21; // ebx
  int v22; // eax
  const char *v23; // eax
  BOOL v24; // ebx
  int v25; // eax
  int v26; // esi
  int v27; // eax
  int v28; // ebx
  int v29; // edx
  int v30; // esi
  int v32; // [esp-18h] [ebp-150h]
  const CHAR *v33; // [esp-4h] [ebp-13Ch]
  int v34; // [esp-4h] [ebp-13Ch]
  int v35; // [esp+Ch] [ebp-12Ch]
  int v36; // [esp+10h] [ebp-128h]
  int *v37; // [esp+14h] [ebp-124h]
  int v38; // [esp+18h] [ebp-120h]
  int v39; // [esp+1Ch] [ebp-11Ch]
  int v40; // [esp+1Ch] [ebp-11Ch]
  int v41; // [esp+20h] [ebp-118h]
  int Value; // [esp+24h] [ebp-114h]
  int v43; // [esp+28h] [ebp-110h]
  int v44; // [esp+2Ch] [ebp-10Ch]
  int v45; // [esp+30h] [ebp-108h]
  int *v46; // [esp+30h] [ebp-108h]
  char Buffer[256]; // [esp+34h] [ebp-104h] BYREF
  int v48; // [esp+134h] [ebp-4h]
  int v49; // [esp+140h] [ebp+8h]
  int v50; // [esp+140h] [ebp+8h]
  int v51; // [esp+140h] [ebp+8h]
  int v52; // [esp+140h] [ebp+8h]
  int v53; // [esp+140h] [ebp+8h]
  int v54; // [esp+140h] [ebp+8h]
  char v55; // [esp+143h] [ebp+Bh]

  v48 = dword_796E50;
  v3 = 0;
  v45 = 0;
  for ( i = (int *)(this + 572); *i != 0; ++i )
  {
    v5 = *(uint32_t *)(v3 + *(uint32_t *)(this + 596));
    v6 = (uint32_t *)*i;
    v38 = *(uint32_t *)(*i + 76);
    v41 = *i;
    if ( a2 == v5 && v38 != 0 )
    {
      v36 = v6[8];
      v55 = 1;
      v44 = -15920333;
      v39 = v6[9];
      v35 = v6[10];
      Value = sub_667620();
      v43 = v6[5];
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 9952) + 672))(
                        *(uint32_t *)(this + 9952),
                        3) < Value )
      {
        v55 = 0;
        v44 = -14803286;
      }
      v37 = (int *)(8 * v45 + 7950872);
      v46 = (int *)(8 * v45 + 7950868);
      v7 = sub_4F33A0(v6[3]);
      sub_4F2C10(*v46, *v37, v7, v43);
      if ( v55 == 0 && dword_9B0C5C != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)dword_9B0C5C + 128))(
          dword_9B0C5C,
          *v46,
          *v37,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          1308622847,
          1333788672,
          1333788672);
      if ( Value > 1 )
      {
        v8 = *(uint32_t *)(v5 + 24);
        v49 = *(uint32_t *)(v5 + 20);
        v9 = sub_418DD0(10);
        if ( v9 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
            v9,
            v49 + 10,
            v8 + 64,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
        sub_69A110(*(uint32_t *)(v5 + 20) + 27, *(uint32_t *)(v5 + 24) + 66, Value, -1);
      }
      if ( v36 > 0 )
      {
        v10 = *(uint32_t *)(v5 + 24);
        v50 = *(uint32_t *)(v5 + 20);
        v11 = sub_418DD0(5);
        if ( v11 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v11 + 128))(
            v11,
            v50 + 51,
            v10 + 45,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( v39 > 0 )
      {
        v12 = *(uint32_t *)(v5 + 24);
        v51 = *(uint32_t *)(v5 + 20);
        v13 = sub_418DD0(6);
        if ( v13 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
            v13,
            v51 + 71,
            v12 + 45,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v38 + 108))(v38);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 220);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        *v46 - 4,
        *(uint32_t *)(v5 + 24) + 5,
        v44,
        v14);
      v32 = v14;
      v15 = v44;
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        *v46 - 3,
        *(uint32_t *)(v5 + 24) + 5,
        v44,
        v32);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 272);
      v16 = *(uint32_t *)(this + 44);
      if ( v16 != 0 )
      {
        v17 = v16 - 1;
        if ( v17 != 0 )
        {
          if ( v17 == 1 )
          {
            if ( *(uint32_t *)(v41 + 72) < 0x10u )
              v18 = v41 + 52;
            else
              v18 = *(uint32_t *)(v41 + 52);
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
              dword_79C0B0,
              *(uint32_t *)(v5 + 20) - *(uint32_t *)(this + 144) + 169,
              *(uint32_t *)(v5 + 24) + 27,
              v44,
              v18);
          }
        }
        else
        {
          if ( v43 <= 1 )
            v19 = szPassword;
          else
            v19 = (const CHAR *)sub_422E70(251);
          v33 = v19;
          v20 = (const char *)sub_422E70(250);
          sprintf(Buffer, v20, v43, v33);
          (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            *(uint32_t *)(v5 + 20) - *(uint32_t *)(this + 144) + 169,
            *(uint32_t *)(v5 + 24) + 27,
            v44,
            Buffer);
        }
      }
      else
      {
        v21 = *(uint32_t *)dword_79C0B0;
        v52 = *(uint32_t *)(v5 + 24);
        v40 = *(uint32_t *)(v5 + 20);
        v22 = sub_422E70(249);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v21 + 80))(
          dword_79C0B0,
          v40 - *(uint32_t *)(this + 144) + 169,
          v52 + 27,
          v44,
          v22);
        v15 = v44;
      }
      if ( v35 > 0 )
      {
        v34 = v35;
        v23 = (const char *)sub_422E70(252);
        goto LABEL_38;
      }
      if ( v36 > 0 )
      {
        v34 = v36;
        v23 = (const char *)sub_422E70(180);
LABEL_38:
        sprintf(Buffer, v23, v34);
        (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          *(uint32_t *)(v5 + 20) - *(uint32_t *)(this + 144) + 169,
          *(uint32_t *)(v5 + 24) + 45,
          v15,
          Buffer);
      }
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      LOBYTE(v3) = *(uint8_t *)(v41 + 24);
      if ( (uint8_t)v3 == 0 )
        return v3;
      v24 = GetTickCount() % 0x578 < 0x2BC;
      if ( *(uint8_t *)(v41 + 24) == 1 )
      {
        v28 = v24 + 27;
      }
      else
      {
        if ( *(uint8_t *)(v41 + 24) != 2 )
        {
          LOBYTE(v3) = *(uint8_t *)(v41 + 24) - 22;
          if ( *(uint8_t *)(v41 + 24) == 22 )
          {
            v25 = *(uint32_t *)(v5 + 24);
            v26 = *(uint32_t *)(v5 + 20);
            v53 = v25;
            v27 = sub_418DD0(v24 + 39);
            if ( v27 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v27 + 128))(
                v27,
                v26 - 1,
                v53 - 1,
                dword_79C0B0,
                1065353216,
                1065353216,
                0,
                -1,
                1333788672,
                1333788672);
            (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
              dword_8F84B8,
              "interface/cashshop/cashshopdoubleevent.img");
            v3 = sub_418DD0(v24 + 3);
            if ( v3 != 0 )
              LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v3 + 128))(
                             v3,
                             *v46 + 30,
                             *v37 + 14,
                             dword_79C0B0,
                             1065353216,
                             1065353216,
                             0,
                             -1,
                             1333788672,
                             1333788672);
          }
          return v3;
        }
        v28 = v24 + 39;
      }
      v29 = *(uint32_t *)(v5 + 24);
      v30 = *(uint32_t *)(v5 + 20);
      v54 = v29;
      v3 = sub_418DD0(v28);
      if ( v3 != 0 )
        LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v3 + 128))(
                       v3,
                       v30 - 1,
                       v54 - 1,
                       dword_79C0B0,
                       1065353216,
                       1065353216,
                       0,
                       -1,
                       1333788672,
                       1333788672);
      return v3;
    }
    v3 += 12;
    ++v45;
    if ( v3 >= 72 )
      return v3;
  }
  return v3;
}


// ------------------------------------------------------------
// 0x55E050 sub_55E050 —— 商城状态切换（44ABE0）
// ------------------------------------------------------------
int /*fastcall*/ sub_55E050(uint32_t *a1)
{
  int *v1; // ebx
  int v2; // edi
  int *v3; // esi
  int result; // eax
  int v5; // edi
  int v6; // edi
  int *i; // esi
  uint32_t *v8; // ecx
  uint32_t *v9; // ecx
  uint32_t *v10; // ecx
  uint32_t *v11; // [esp+Ch] [ebp-4h]

  v1 = (int *)a1[149];
  v11 = a1;
  v2 = 0;
  v3 = v1;
  do
  {
    result = *v3;
    if ( *(uint8_t *)(*v3 + 17) != 0 )
    {
      if ( dword_79BE3C == *(uint32_t *)(result + 12) || dword_79BE34 == *(uint32_t *)(result + 12) )
      {
        a1 = v11;
LABEL_21:
        v9 = (uint32_t *)a1[1];
        if ( v9[626] != 12 )
          return sub_44ABE0(v9, 12);
        return result;
      }
      a1 = v11;
      if ( dword_79BE38 == *(uint32_t *)(result + 12) )
        goto LABEL_21;
    }
    ++v2;
    v3 += 3;
  }
  while ( v2 < 6 );
  result = a1[1870];
  if ( *(uint8_t *)(result + 17) == 0
    || (v5 = *(uint32_t *)(result + 12), dword_79BE3C != v5) && dword_79BE34 != v5 && dword_79BE38 != v5 )
  {
    v6 = 0;
    for ( i = v1 + 2; ; i += 3 )
    {
      result = *i;
      if ( *(uint8_t *)(*i + 17) != 0
        && (dword_79BE3C == *(uint32_t *)(result + 12)
         || dword_79BE34 == *(uint32_t *)(result + 12)
         || dword_79BE38 == *(uint32_t *)(result + 12)) )
      {
        break;
      }
      if ( ++v6 >= 6 )
      {
        v8 = (uint32_t *)a1[1];
        result = v8[626];
        if ( result != 0 )
          return sub_44ABE0(v8, 0);
        return result;
      }
    }
  }
  v10 = (uint32_t *)a1[1];
  if ( v10[626] != 13 )
    return sub_44ABE0(v10, 13);
  return result;
}



// ------------------------------------------------------------
// 0x55E190 sub_55E190 —— 商城确认（6477B0 + 422E70/44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ sub_55E190(int this, uint32_t *a2)
{
  int v3; // edi
  uint32_t *v4; // ebx
  char *v5; // eax
  char result; // al

  v3 = a2[19];
  v4 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 9952) + 672))(*(uint32_t *)(this + 9952), 3);
  if ( *v4 >= CNRDParticleCreater__vmt30(v3) )
  {
    result = sub_6477B0(*(uint32_t *)(this + 8), a2, 0);
    *(uint8_t *)(*(uint32_t *)(this + 7404) + 16) = 0;
    *(uint8_t *)(*(uint32_t *)(this + 7408) + 16) = 0;
    *(uint32_t *)(this + 7412) = -1;
  }
  else
  {
    v5 = sub_422E70(1250);
    return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)v5, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x55E210 sub_55E210 —— 商城确认 2（6477B0 + 422E70/44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ sub_55E210(int this, int a2)
{
  int v3; // edi
  uint32_t *v4; // ebx
  char result; // al
  char *v7; // eax
  int v8; // [esp+Ch] [ebp-8h]
  int v9; // [esp+10h] [ebp-4h]
  int *i; // [esp+1Ch] [ebp+8h]

  v8 = this + 1680 * a2;
  v9 = 0;
  for ( i = (int *)(v8 + 680); ; i += 21 )
  {
    v3 = *i;
    if ( *i != 0 )
    {
      v4 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 9952) + 672))(
                       *(uint32_t *)(this + 9952),
                       3);
      if ( *v4 < CNRDParticleCreater__vmt30(v3) )
        break;
    }
    if ( ++v9 >= 20 )
    {
      result = sub_6477B0(*(uint32_t *)(this + 8), (uint32_t *)(v8 + 604), 1);
      *(uint8_t *)(*(uint32_t *)(this + 7404) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 7408) + 16) = 0;
      *(uint32_t *)(this + 7412) = -1;
      return result;
    }
  }
  v7 = sub_422E70(1250);
  return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)v7, 0);
}



// ------------------------------------------------------------
// 0x55E2D0 sub_55E2D0 —— 商城参数串（423200/423380/698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_55E2D0(int this)
{
  int v2; // eax

  LOBYTE(v2) = *(uint8_t *)(this + 7584);
  if ( (uint8_t)v2 == 0 )
  {
    sub_423200(dword_8F7B08, 68);
    sub_423380(dword_8F7B08);
    *(uint8_t *)(this + 7584) = 1;
    *(uint8_t *)(this + 7513) = 0;
    *(uint8_t *)(this + 7514) = 0;
    sub_698F90(this + 7500, 0, 0);
    v2 = *(uint32_t *)(this + 7488);
    *(uint8_t *)(v2 + 17) = 0;
  }
  return v2;
}



// ------------------------------------------------------------
// 0x55E320 sub_55E320 —— 商城主装配（422E70/4649B0/43BCB0，148 行）
// ------------------------------------------------------------
int */*thiscall*/ sub_55E320(uint32_t *this, int a2)
{
  uint32_t *v2; // ebx
  int v3; // eax
  int v4; // esi
  unsigned int v5; // esi
  int v6; // edi
  int v7; // ebx
  const char *v8; // eax
  int v9; // edi
  int v10; // esi
  int *result; // eax
  int v12; // esi
  int v13; // esi
  int v14; // edi
  int v15; // esi
  const char *v16; // eax
  int *v17; // esi
  int *v18; // edi
  int v19; // eax
  const char *v20; // eax
  int v21; // eax
  int v22; // esi
  int v23; // ecx
  int v24; // eax
  int v25; // edx
  int v26; // ecx
  int v27; // edi
  int v28; // ebx
  int v29; // esi
  const char *v30; // eax
  int v31; // [esp-14h] [ebp-2Ch]
  int v33; // [esp+10h] [ebp-8h]
  int *v34; // [esp+14h] [ebp-4h]
  int *v35; // [esp+14h] [ebp-4h]

  v2 = this;
  v3 = *(this + 1872);
  if ( a2 == v3 && *(uint8_t *)(v3 + 17) != 0 )
  {
    v4 = *(uint32_t *)(v3 + 12);
    if ( dword_79BE3C == v4 || dword_79BE34 == v4 || dword_79BE38 == v4 )
    {
      v31 = 269;
LABEL_7:
      v5 = *(uint32_t *)(v3 + 28);
      v6 = *(uint32_t *)(v3 + 24);
      v7 = *(uint32_t *)(v3 + 20);
      v8 = (const char *)sub_422E70(v31);
      v9 = v6 - 5;
      v10 = v7 + (v5 >> 1);
      return (int *)sub_4649B0(v10, v9, -1, -16777216, 2, v8, 0, 0, 1600, 0);
    }
  }
  v3 = *(this + 2474);
  if ( a2 == v3 && *(uint8_t *)(v3 + 17) != 0 )
  {
    v12 = *(uint32_t *)(v3 + 12);
    if ( dword_79BE3C == v12 || dword_79BE34 == v12 || dword_79BE38 == v12 )
    {
      v31 = 270;
      goto LABEL_7;
    }
  }
  v13 = *(this + 1871);
  if ( a2 == v13 && (uint8_t)sub_43BCB0(*(this + 1871)) != 0 )
  {
    v14 = *(uint32_t *)(v13 + 24);
    v10 = *(uint32_t *)(v13 + 20);
    v8 = (const char *)sub_422E70(271);
    v9 = v14 - 5;
    return (int *)sub_4649B0(v10, v9, -1, -16777216, 2, v8, 0, 0, 1600, 0);
  }
  if ( v2[11] == 0 )
  {
    if ( v2[85] != 0 )
    {
      if ( a2 == v2[2528] )
      {
        v15 = 2 * v2[86];
        v16 = (const char *)sub_422E70(272);
        sub_4649B0(dword_725BC0[v15] - 38, dword_725BC4[v15] + 25, -1, -16777216, 2, v16, 0, 0, 1600, 0);
      }
    }
    else
    {
      v17 = &dword_725CB0;
      v18 = &dword_725D50;
      v34 = v2 + 1831;
      do
      {
        v19 = *v34;
        if ( a2 == *v34
          && *(uint8_t *)(v19 + 17) != 0
          && dword_79BE3C == *(uint32_t *)(v19 + 12)
          && v2[2488] != 0
          && (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)v2[2488] + 792))(v2[2488], *v18) != 0 )
        {
          v20 = (const char *)sub_422E70(273);
          sub_4649B0(*v17 - 38, v17[1] + 25, -1, -16777216, 2, v20, 0, 0, 1600, 0);
        }
        ++v18;
        v17 += 2;
        ++v34;
      }
      while ( (int)v18 < (int)&dword_725DA0 );
    }
  }
  result = &dword_725C50;
  v35 = &dword_725C50;
  do
  {
    v21 = *result;
    v22 = v2[v21 + 2480];
    v33 = v21;
    if ( a2 == v22 && *(uint8_t *)(v22 + 16) != 0 && *(uint8_t *)(v22 + 17) != 0 )
    {
      if ( dword_79BE3C == *(uint32_t *)(v22 + 12)
        || (v23 = *(uint32_t *)(v22 + 12), dword_79BE34 == v23)
        || dword_79BE38 == v23 )
      {
        v24 = v2[2488];
        if ( v24 != 0 )
        {
          v25 = (v33 + 8 * *(uint32_t *)(*(int (**)(void))(*(uint32_t *)v24 + 1032))()) << 6;
          v26 = *(uint32_t *)((char *)v2 + v25 + 7868);
          v27 = *(uint32_t *)(v22 + 28) >> 1;
          if ( v26 == 0 || (*(uint32_t *)((char *)v2 + v25 + 7872) - v26) >> 2 == 0 )
          {
            v28 = *(uint32_t *)(v22 + 24);
            v29 = *(uint32_t *)(v22 + 20);
            v30 = (const char *)sub_422E70(274);
            sub_4649B0(v27 + v29, v28, -1, -16777216, 2, v30, 0, 0, 1600, 0);
            v2 = this;
          }
        }
      }
    }
    result = ++v35;
  }
  while ( (int)v35 < (int)dword_725C70 );
  return result;
}


// ------------------------------------------------------------
// 0x55E650 sub_55E650 —— 商城数据 3（30 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_55E650(uint32_t *this, const void *a2)
{
  int v2; // edi
  int v3; // edx
  int i; // eax
  int v5; // esi

  v2 = *(this + 11);
  v3 = 0;
  for ( i = (int)(this + 420 * v2 + 151); ; i += 84 )
  {
    if ( i != 0 )
    {
      v5 = *(uint32_t *)(i + 12);
      if ( v5 >= 4 && v5 <= 7 )
        break;
    }
    if ( ++v3 >= 20 )
      return 0;
  }
  qmemcpy(this + 420 * v2 + 21 * v3 + 151, a2, 0x54u);
  *((uint8_t *)this + 1680 * v2 + 84 * v3 + 684) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x55E6C0 sub_55E6C0 —— 商城数据 4（25 行）
// ------------------------------------------------------------
uint8_t */*cdecl*/ sub_55E6C0(uint8_t *a1, uint8_t *a2, uint8_t *a3)
{
  uint8_t *result; // eax
  int v4; // edx

  result = a3;
  if ( a1 != a2 )
  {
    v4 = a1 - a3;
    do
    {
      qmemcpy(result, &result[v4], 0x54u);
      result[80] = 0;
      result += 84;
    }
    while ( &result[v4] != a2 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x55E700 CNRDCashShop__vmt0 —— CNRDCashShop__vmt0 主构造（55C2B0/55D6E0/55DA50/55C500/55D3C0/55E320/418DD0/43B560 装配链）
// ------------------------------------------------------------
char /*thiscall*/ CNRDCashShop__vmt0(int *this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // esi

  if ( a2 == *(this + 13) )
  {
    sub_55C2B0((int)this);
    LOBYTE(v3) = sub_55D6E0((int)this);
  }
  else
  {
    sub_55DA50((int)this, a2);
    sub_55C500((int)this, a2);
    sub_55D3C0(this, a2);
    sub_55E320(this, a2);
    v3 = *(this + 1872);
    if ( a2 == v3 && *(uint8_t *)(v3 + 17) == 1 )
    {
      if ( timeGetTime() % 0x578 <= 0x2BC && byte_9B887C == 0 )
      {
        v4 = *(this + 1872);
        v5 = *(uint32_t *)(v4 + 24);
        v6 = *(uint32_t *)(v4 + 20);
        v7 = sub_418DD0(36);
        sub_43B560((void *)dword_79C0B0, v6, v5, v7, 1065353216, 1065353216, 0, -1, 1333788672, 1333788672);
      }
      v8 = *(this + 1872);
      LOBYTE(v3) = *(uint8_t *)(v8 + 17);
      if ( (uint8_t)v3 != 0 && dword_79BE34 == *(uint32_t *)(v8 + 12) )
      {
        LOBYTE(v3) = byte_9B887C;
        if ( byte_9B887C == 0 )
          byte_9B887C = 1;
      }
    }
  }
  return v3;
}



// ============================================================
// 【分区 12】商城购买流程（0x55E7F0-0x5603E0）
// 商品列表刷新链 0x55F810/55FB40/55FC80/55FDB0；礼赠流程 0x5601C0；
// SERA_SHOP 赛丽亚商店事件 0x560610；商品选择 Update 0x5607D0（217 行）。
// ============================================================
// ------------------------------------------------------------
// 0x55E7F0 sub_55E7F0 —— 商城状态（10 行）
// ------------------------------------------------------------
int /*stdcall*/ sub_55E7F0(void *Src, int a2, void *a3)
{
  return (int)memcpy_0(a3, Src, 4 * ((a2 - (int)Src) >> 2)) + 4 * ((a2 - (int)Src) >> 2);
}



// ------------------------------------------------------------
// 0x55E820 sub_55E820 —— 商城条目（26 行）
// ------------------------------------------------------------
unsigned int /*stdcall*/ sub_55E820(int a1)
{
  int v1; // ecx
  unsigned int i; // edx
  unsigned int result; // eax

  v1 = dword_9B8870;
  for ( i = 0; v1 != 0; ++i )
  {
    result = ((int)dword_9B8874 - v1) >> 2;
    if ( i >= result )
      break;
    if ( *(uint32_t *)(v1 + 4 * i) == a1 )
    {
      *(uint32_t *)(v1 + 4 * i) = -1;
      v1 = dword_9B8870;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x55E860 sub_55E860 —— 商城条目 2（19 行）
// ------------------------------------------------------------
char /*stdcall*/ sub_55E860(int a1)
{
  unsigned int i; // edx

  if ( a1 == 0 )
    return 0;
  for ( i = 0; dword_9B8870 != 0 && i < ((int)dword_9B8874 - dword_9B8870) >> 2; ++i )
  {
    if ( *(uint32_t *)(dword_9B8870 + 4 * i) == a1 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x55E8B0 sub_55E8B0 —— 商城条目 3（24 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_55E8B0(uint32_t *this, int a2, int a3)
{
  unsigned int v3; // esi
  int v4; // ebx
  int v6; // [esp+Ch] [ebp-4h]

  v3 = 0;
  v4 = *(this + 4 * a2 + 128);
  v6 = 0;
  while ( v4 != 0 && v3 < (*(this + 4 * a2 + 129) - v4) / 84 )
  {
    if ( *(uint32_t *)(v6 + *(this + 4 * a2 + 128)) == a3 )
      return *(this + 4 * a2 + 128) + 84 * v3;
    ++v3;
    v6 += 84;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x55E940 sub_55E940 —— 商品列表刷新（55E860/55D350/55D320，84 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_55E940(int this, int *a2)
{
  bool v3; // bl
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  char v9; // bl
  int v10; // eax
  int v11; // esi
  int v12; // eax
  int v13; // [esp+Ch] [ebp-Ch] BYREF
  int v14; // [esp+10h] [ebp-8h]
  int v15; // [esp+14h] [ebp-4h]

  v3 = true;
  if ( sub_55E860(a2[2]) == 1 )
    return 0;
  v4 = *(uint32_t *)(this + 44);
  if ( v4 == 0 )
  {
    v12 = *(uint32_t *)(dword_8F7A24 + 244);
    if ( v12 != 0 )
    {
      if ( v12 != 2 || *((uint8_t *)a2 + 44) != 0xF4 )
        return v3;
      return 0;
    }
    if ( *((uint8_t *)a2 + 44) != 0xF1 )
      return v3;
    return 0;
  }
  if ( v4 != 2 )
    return v3;
  v5 = a2[3];
  if ( v5 >= 4 && v5 <= 7 )
  {
    v14 = 0;
    v15 = 0;
    v13 = -1;
    sub_55D350(&v13);
    v6 = *a2;
    if ( *a2 != v13 && v6 != v14 )
      v3 = v6 == v15;
    v7 = sub_55D320();
    if ( v7 != -1 && a2[3] >= v7 )
      return v3;
    return 0;
  }
  if ( *a2 != 110013 )
    return v3;
  v9 = 0;
  v10 = 0;
  while ( v10 >= *((uint32_t *)dword_8F8534 + 2) || *(uint32_t *)(*((uint32_t *)dword_8F8534 + 3) + 4 * v10) == 0 )
  {
    if ( ++v10 >= 105 )
      goto LABEL_20;
  }
  v9 = 1;
LABEL_20:
  if ( *(uint32_t *)(this + 9952) != 0 )
  {
    if ( v9 == 0 )
    {
      v11 = 0;
      while ( (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 9952) + 792))(*(uint32_t *)(this + 9952), v11) == 0 )
      {
        if ( ++v11 >= 8 )
          return 0;
      }
    }
  }
  else if ( v9 == 0 )
  {
    return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x55EA90 sub_55EA90 —— 礼赠数据（6454C0）
// ------------------------------------------------------------
void /*thiscall*/ sub_55EA90(int this)
{
  *(uint32_t *)this = &vftbl_CNRDCashShopBuyWindow;
  sub_6454C0((uint32_t *)this);
  *(uint32_t *)(this + 2328) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 2332) = 0;
  `eh vector destructor iterator'((void *)(this + 340), 0x54u, 20, sub_44C2A0);
  if ( *(uint32_t *)(this + 332) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 332));
    *(uint32_t *)(this + 332) = 0;
  }
  *(uint8_t *)(this + 288) = 0;
  *(uint8_t *)(this + 289) = 0;
  *(uint8_t *)(this + 290) = 0;
  *(uint8_t *)(this + 291) = 0;
  *(uint32_t *)(this + 300) = 0;
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;
  *(uint32_t *)(this + 328) = 0;
  *(uint32_t *)(this + 332) = 0;
  *(uint32_t *)(this + 336) = 0;
  if ( *(uint32_t *)(this + 280) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 280));
    *(uint32_t *)(this + 280) = 0;
  }
  *(uint8_t *)(this + 236) = 0;
  *(uint8_t *)(this + 237) = 0;
  *(uint8_t *)(this + 238) = 0;
  *(uint8_t *)(this + 239) = 0;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 252) = 0;
  *(uint32_t *)(this + 256) = 0;
  *(uint32_t *)(this + 260) = 0;
  *(uint32_t *)(this + 264) = 0;
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;
  *(uint32_t *)(this + 280) = 0;
  *(uint32_t *)(this + 284) = 0;
  if ( *(uint32_t *)(this + 228) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 228));
    *(uint32_t *)(this + 228) = 0;
  }
  *(uint8_t *)(this + 184) = 0;
  *(uint8_t *)(this + 185) = 0;
  *(uint8_t *)(this + 186) = 0;
  *(uint8_t *)(this + 187) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 228) = 0;
  *(uint32_t *)(this + 232) = 0;
  if ( *(uint32_t *)(this + 176) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 176));
    *(uint32_t *)(this + 176) = 0;
  }
  *(uint8_t *)(this + 132) = 0;
  *(uint8_t *)(this + 133) = 0;
  *(uint8_t *)(this + 134) = 0;
  *(uint8_t *)(this + 135) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  `eh vector destructor iterator'((void *)(this + 52), 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_55C150);
}



// ------------------------------------------------------------
// 0x55ECC0 sub_55ECC0 —— 礼赠条目（55CE70/55CED0）
// ------------------------------------------------------------
int /*thiscall*/ sub_55ECC0(char *this, int a2, int a3, int a4)
{
  int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // ebx
  unsigned int i; // edx
  uint32_t *v11; // eax
  int v12; // edi
  int v13; // ecx
  int v14; // eax
  int v15; // esi
  int v16; // eax
  int v17; // ecx
  int v19; // [esp+1Ch] [ebp+10h]

  v5 = sub_55CE70(a2);
  v6 = 4 * (sub_55CED0(a2) + 8 * v5);
  v7 = 16 * (v6 + a4);
  v8 = *(uint32_t *)(this + v7 + 7852);
  v9 = (int)(this + v7 + 7848);
  v19 = (int)(this + 16 * a3 + 16 * v6 + 7848);
  for ( i = 0; ; ++i )
  {
    if ( v8 == 0 || i >= (*(uint32_t *)(v9 + 8) - v8) >> 2 )
      return 0;
    v11 = *(uint32_t **)(4 * i + v8);
    if ( v11[3] == a2 && *v11 != -1 && **(uint32_t **)(4 * i + *(uint32_t *)(v19 + 4)) != -1 )
      break;
  }
  v12 = 4 * i;
  v13 = *(uint32_t *)(4 * i + v8);
  v14 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v19 + 4) + 4 * i) + 76);
  *(uint32_t *)(v13 + 76) = v14;
  if ( v14 != 0 )
    *(uint8_t *)(v13 + 80) = 0;
  v15 = *(uint32_t *)(*(uint32_t *)(v9 + 4) + 4 * i);
  *(uint32_t *)(v15 + 40) = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v15 + 76) + 16))(*(uint32_t *)(v15 + 76))
                                    + 40);
  v16 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v15 + 76) + 16))(*(uint32_t *)(v15 + 76));
  v17 = *(uint32_t *)(v15 + 76);
  *(uint32_t *)(v15 + 32) = *(uint32_t *)(v16 + 36);
  *(uint32_t *)(v15 + 36) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 16))(v17) + 44);
  return *(uint32_t *)(v12 + *(uint32_t *)(v9 + 4));
}



// ------------------------------------------------------------
// 0x55EDC0 sub_55EDC0 —— 礼赠列表刷新（55EA90，126 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_55EDC0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  char *v3; // eax
  char *v4; // edi
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  uint32_t *v10; // edi
  int i; // ebx
  uint32_t *v12; // edi
  int j; // ebx
  uint32_t *v14; // edi
  int k; // ebx
  void *v16; // edi
  uint32_t *v17; // edi
  int m; // ebx
  void (/*thiscall*/ ***v19)(uint32_t, int); // ecx
  int *v20; // edi
  int v21; // ebx
  void (/*thiscall*/ ***v22)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v23)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v24)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v25)(uint32_t, int); // ecx

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (char *)*(this + 149);
  *(this + 13) = 0;
  if ( v3 != nullptr )
  {
    v4 = v3 - 4;
    `eh vector destructor iterator'(v3, 0xCu, *((uint32_t *)v3 - 1), sub_55C100);
    j_j__free(v4);
  }
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  v6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 81);
  *(this + 12) = 0;
  if ( v6 != nullptr )
    (**v6)(v6, 1);
  v7 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 82);
  *(this + 81) = 0;
  if ( v7 != nullptr )
    (**v7)(v7, 1);
  v8 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 83);
  *(this + 82) = 0;
  if ( v8 != nullptr )
    (**v8)(v8, 1);
  v9 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 84);
  *(this + 83) = 0;
  if ( v9 != nullptr )
    (**v9)(v9, 1);
  *(this + 84) = 0;
  v10 = this + 1831;
  for ( i = 20; i != 0; --i )
  {
    if ( *v10 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v10)(*v10, 1);
    *v10++ = 0;
  }
  v12 = this + 1870;
  for ( j = 5; j != 0; --j )
  {
    if ( *v12 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v12)(*v12, 1);
    *v12++ = 0;
  }
  v14 = this + 1855;
  for ( k = 5; k != 0; --k )
  {
    if ( *v14 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v14)(*v14, 1);
    *v14++ = 0;
  }
  v16 = (void *)*(this + 2);
  if ( v16 != nullptr )
  {
    sub_55EA90(*(this + 2));
    j__free(v16);
  }
  *(this + 2) = 0;
  v17 = this + 1851;
  for ( m = 2; m != 0; --m )
  {
    if ( *v17 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v17)(*v17, 1);
    *v17++ = 0;
  }
  v19 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2479);
  if ( v19 != nullptr )
    (**v19)(v19, 1);
  *(this + 2479) = 0;
  v20 = &dword_725C50;
  do
  {
    v21 = *v20;
    v22 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + *v20 + 2480);
    if ( v22 != nullptr )
      (**v22)(v22, 1);
    ++v20;
    *(this + v21 + 2480) = 0;
  }
  while ( (int)v20 < (int)dword_725C70 );
  v23 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2474);
  if ( v23 != nullptr )
    (**v23)(v23, 1);
  v24 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2489);
  *(this + 2474) = 0;
  if ( v24 != nullptr )
    (**v24)(v24, 1);
  v25 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2528);
  *(this + 2489) = 0;
  if ( v25 != nullptr )
    (**v25)(v25, 1);
  *(this + 2528) = 0;
}


// ------------------------------------------------------------
// 0x55EFB0 sub_55EFB0 —— 礼赠文本（4015C0/429830）
// ------------------------------------------------------------
int */*thiscall*/ sub_55EFB0(uint32_t *this)
{
  uint32_t *v2; // ecx
  uint32_t *v3; // esi
  int j; // edi
  int *v5; // eax
  int v6; // edx
  int v7; // eax
  uint32_t *v8; // ecx
  int *result; // eax
  int v10; // edi
  int v11; // eax
  uint32_t *v12; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]
  int *v14; // [esp+10h] [ebp-4h]

  v2 = this + 119;
  *v2 = 0;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 0;
  v12 = this;
  memset(this + 1898, 0, 0x80u);
  v3 = this + 153;
  for ( i = 4; i != 0; --i )
  {
    for ( j = 20; j != 0; --j )
    {
      *(v3 - 2) = -1;
      *(v3 - 1) = -1;
      *v3 = 0;
      v3[1] = -1;
      *((uint8_t *)v3 + 8) = -1;
      v3[3] = 0;
      *((uint8_t *)v3 + 16) = 0;
      *((uint16_t *)v3 + 9) = 0;
      v3[5] = 0;
      v3[6] = 0;
      v3[7] = 0;
      v3[8] = 0;
      *((uint8_t *)v3 + 36) = -1;
      sub_4015C0((void *)szPassword, 0);
      v3[17] = 0;
      v3 += 21;
    }
  }
  v12[1853] = -1;
  v5 = &dword_725C50;
  do
  {
    v6 = v12[*v5++ + 2480];
    *(uint8_t *)(v6 + 132) = 0;
  }
  while ( (int)v5 < (int)dword_725C70 );
  v12[1897] = 0;
  *(uint8_t *)(v12[2480] + 132) = 1;
  *(uint8_t *)(v12[1851] + 16) = 0;
  *(uint8_t *)(v12[1852] + 16) = 0;
  v12[1853] = -1;
  v7 = 0;
  v8 = &v12[420 * v12[11] + 170];
  while ( *v8 == 0 )
  {
    ++v7;
    v8 += 21;
    if ( v7 >= 20 )
    {
      *(uint8_t *)(v12[1870] + 17) = 0;
      goto LABEL_11;
    }
  }
  *(uint8_t *)(v12[1870] + 17) = 1;
LABEL_11:
  result = &dword_725C50;
  v14 = &dword_725C50;
  do
  {
    v10 = *result;
    if ( *result <= 7 && sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0 && v12[v10 + 2490] != 0 )
    {
      v12[v10 + 2490] = 0;
      v11 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t))(*(uint32_t *)v12[2489] + 352))(
        v12[2489],
        v10,
        *(uint32_t *)(v11 + 4 * v10 + 72));
    }
    result = ++v14;
  }
  while ( (int)v14 < (int)dword_725C70 );
  v12[2529] = 1;
  v12[2531] = -1;
  return result;
}



// ------------------------------------------------------------
// 0x55F160 sub_55F160 —— 礼赠参数（55CE00/4015C0）
// ------------------------------------------------------------
int /*thiscall*/ sub_55F160(int this, int a2)
{
  int v3; // esi
  int v4; // ecx
  int *v5; // eax
  int result; // eax
  uint32_t *j; // ecx
  int i; // [esp+Ch] [ebp-4h]

  v3 = 1680 * a2 + this + 612;
  for ( i = 20; i != 0; --i )
  {
    if ( a2 == 0 )
    {
      v4 = *(uint32_t *)(v3 + 68);
      if ( v4 != 0 )
      {
        v5 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 172))(v4);
        sub_55CE00((uint32_t **)this, *v5);
      }
    }
    *(uint32_t *)(v3 - 8) = -1;
    *(uint32_t *)(v3 - 4) = -1;
    *(uint32_t *)v3 = 0;
    *(uint32_t *)(v3 + 4) = -1;
    *(uint8_t *)(v3 + 8) = -1;
    *(uint32_t *)(v3 + 12) = 0;
    *(uint8_t *)(v3 + 16) = 0;
    *(uint16_t *)(v3 + 18) = 0;
    *(uint32_t *)(v3 + 20) = 0;
    *(uint32_t *)(v3 + 24) = 0;
    *(uint32_t *)(v3 + 28) = 0;
    *(uint32_t *)(v3 + 32) = 0;
    *(uint8_t *)(v3 + 36) = -1;
    sub_4015C0((void *)szPassword, 0);
    *(uint32_t *)(v3 + 68) = 0;
    v3 += 84;
  }
  result = 0;
  for ( j = (uint32_t *)(1680 * *(uint32_t *)(this + 44) + this + 680); *j == 0; j += 21 )
  {
    if ( ++result >= 20 )
    {
      result = *(uint32_t *)(this + 7480);
      *(uint8_t *)(result + 17) = 0;
      return result;
    }
  }
  *(uint8_t *)(*(uint32_t *)(this + 7480) + 17) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x55F240 sub_55F240 —— 礼赠执行（55CE00/44C9C0/55C730/4015C0，88 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_55F240(int this, int a2, int a3)
{
  int v4; // esi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  uint8_t *v8; // eax
  bool v9; // zf
  int v10; // esi
  int v11; // ecx
  uint32_t *i; // eax
  int v14; // esi
  int v15; // ecx
  int *v16; // eax
  int v17; // [esp+14h] [ebp+8h]

  *(uint8_t *)(*(uint32_t *)(this + 7404) + 16) = 0;
  v4 = a3;
  *(uint8_t *)(*(uint32_t *)(this + 7408) + 16) = 0;
  *(uint32_t *)(this + 7412) = a2;
  if ( a3 == 0 )
  {
    v14 = 84 * a2 + this;
    v15 = *(uint32_t *)(v14 + 680);
    if ( v15 != 0 )
    {
      v16 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 172))(v15);
      sub_55CE00((uint32_t **)this, *v16);
      sub_44C9C0((uint32_t *)(v14 + 604));
      sub_55C730((uint32_t *)this);
      return 1;
    }
    return 0;
  }
  v5 = 84 * (a2 + 20 * a3);
  v6 = *(uint32_t *)(v5 + this + 680);
  v7 = this + v5;
  if ( v6 == 0 )
    return 0;
  if ( a2 < 19 )
  {
    v8 = (uint8_t *)(v7 + 604);
    v17 = 19 - a2;
    do
    {
      qmemcpy(v8, v8 + 84, 0x54u);
      v9 = v17 == 1;
      v8[80] = 0;
      v8 += 84;
      --v17;
    }
    while ( !v9 );
    v4 = a3;
  }
  v10 = 1680 * v4 + this + 2200;
  *(uint32_t *)v10 = -1;
  *(uint32_t *)(v10 + 4) = -1;
  *(uint32_t *)(v10 + 8) = 0;
  *(uint32_t *)(v10 + 12) = -1;
  *(uint8_t *)(v10 + 16) = -1;
  *(uint32_t *)(v10 + 20) = 0;
  *(uint8_t *)(v10 + 24) = 0;
  *(uint16_t *)(v10 + 26) = 0;
  *(uint32_t *)(v10 + 28) = 0;
  *(uint32_t *)(v10 + 32) = 0;
  *(uint32_t *)(v10 + 36) = 0;
  *(uint32_t *)(v10 + 40) = 0;
  *(uint8_t *)(v10 + 44) = -1;
  sub_4015C0((void *)szPassword, 0);
  *(uint32_t *)(v10 + 76) = 0;
  v11 = 0;
  for ( i = (uint32_t *)(1680 * *(uint32_t *)(this + 44) + this + 680); *i == 0; i += 21 )
  {
    if ( ++v11 >= 20 )
    {
      *(uint8_t *)(*(uint32_t *)(this + 7480) + 17) = 0;
      return 1;
    }
  }
  *(uint8_t *)(*(uint32_t *)(this + 7480) + 17) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x55F3A0 sub_55F3A0 —— 礼赠校验（44C9C0/55CED0/4015C0）
// ------------------------------------------------------------
char /*thiscall*/ sub_55F3A0(uint32_t *this, uint32_t *a2)
{
  int v2; // ebx
  int v4; // ecx
  int v5; // ecx
  uint32_t *i; // eax
  int v8; // edi
  int v9; // ebx
  int v10; // esi
  int v11; // [esp+Ch] [ebp-4h]
  int *j; // [esp+18h] [ebp+8h]

  v2 = a2[2];
  if ( v2 <= 0 )
    return 0;
  v4 = a2[1];
  if ( v4 != 0 )
  {
    if ( v4 > 0 && v4 <= 2 )
    {
      v5 = 0;
      for ( i = this + 420 * *(this + 11) + 153; *(i - 2) != *a2 && *i != v2; i += 21 )
      {
        if ( ++v5 >= 20 )
          return 0;
      }
      sub_44C9C0(this + 420 * *(this + 11) + 21 * v5 + 151);
      return 1;
    }
    return 0;
  }
  v8 = 0;
  v11 = a2[3];
  for ( j = this + 420 * *(this + 11) + 154; ; j += 21 )
  {
    v9 = sub_55CED0(v11);
    if ( sub_55CED0(*j) == v9 )
      break;
    if ( ++v8 >= 20 )
      return 0;
  }
  v10 = (int)(this + 420 * *(this + 11) + 21 * v8 + 151);
  *(uint32_t *)v10 = -1;
  *(uint32_t *)(v10 + 4) = -1;
  *(uint32_t *)(v10 + 8) = 0;
  *(uint32_t *)(v10 + 12) = -1;
  *(uint8_t *)(v10 + 16) = -1;
  *(uint32_t *)(v10 + 20) = 0;
  *(uint8_t *)(v10 + 24) = 0;
  *(uint16_t *)(v10 + 26) = 0;
  *(uint32_t *)(v10 + 28) = 0;
  *(uint32_t *)(v10 + 32) = 0;
  *(uint32_t *)(v10 + 36) = 0;
  *(uint32_t *)(v10 + 40) = 0;
  *(uint8_t *)(v10 + 44) = -1;
  sub_4015C0((void *)szPassword, 0);
  *(uint32_t *)(v10 + 76) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x55F4D0 sub_55F4D0 —— 购买页联动（645410/647BF0）
// ------------------------------------------------------------
char */*thiscall*/ sub_55F4D0(char *this, int a2, int a3)
{
  *(uint32_t *)this = &vftbl_CNRDCashShopBuyWindow;
  `eh vector constructor iterator'(
    this + 52,
    0x10u,
    4,
    (void (/*thiscall*/ *)(void *))sub_55C140,
    (void (/*thiscall*/ *)(void *))sub_55C150);
  *(this + 132) = 0;
  *(this + 133) = 0;
  *(this + 134) = 0;
  *(this + 135) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 6;
  *((uint32_t *)this + 38) = 12;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 40) = 1600;
  *((uint32_t *)this + 41) = 0;
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 43) = 0;
  *((uint32_t *)this + 44) = 0;
  *((uint32_t *)this + 45) = 0;
  *(this + 184) = 0;
  *(this + 185) = 0;
  *(this + 186) = 0;
  *(this + 187) = 0;
  *((uint32_t *)this + 49) = 0;
  *((uint32_t *)this + 50) = 6;
  *((uint32_t *)this + 51) = 12;
  *((uint32_t *)this + 52) = 0;
  *((uint32_t *)this + 53) = 1600;
  *((uint32_t *)this + 54) = 0;
  *((uint32_t *)this + 55) = 0;
  *((uint32_t *)this + 56) = 0;
  *((uint32_t *)this + 57) = 0;
  *((uint32_t *)this + 58) = 0;
  *(this + 236) = 0;
  *(this + 237) = 0;
  *(this + 238) = 0;
  *(this + 239) = 0;
  *((uint32_t *)this + 62) = 0;
  *((uint32_t *)this + 63) = 6;
  *((uint32_t *)this + 64) = 12;
  *((uint32_t *)this + 65) = 0;
  *((uint32_t *)this + 66) = 1600;
  *((uint32_t *)this + 67) = 0;
  *((uint32_t *)this + 68) = 0;
  *((uint32_t *)this + 69) = 0;
  *((uint32_t *)this + 70) = 0;
  *((uint32_t *)this + 71) = 0;
  *(this + 288) = 0;
  *(this + 289) = 0;
  *(this + 290) = 0;
  *(this + 291) = 0;
  *((uint32_t *)this + 75) = 0;
  *((uint32_t *)this + 76) = 6;
  *((uint32_t *)this + 77) = 12;
  *((uint32_t *)this + 78) = 0;
  *((uint32_t *)this + 79) = 1600;
  *((uint32_t *)this + 80) = 0;
  *((uint32_t *)this + 81) = 0;
  *((uint32_t *)this + 82) = 0;
  *((uint32_t *)this + 83) = 0;
  *((uint32_t *)this + 84) = 0;
  `eh vector constructor iterator'(this + 340, 0x54u, 20, (void (/*thiscall*/ *)(void *))sub_44CF30, sub_44C2A0);
  *(this + 2332) = 0;
  *((uint32_t *)this + 582) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 584) = 0;
  *(this + 2340) = 1;
  *(this + 2342) = 0;
  *(this + 2341) = 0;
  *((uint32_t *)this + 588) = 0;
  *((uint32_t *)this + 587) = 0;
  *((uint32_t *)this + 586) = 0;
  sub_645410((int)this);
  sub_647BF0((int)this);
  *((uint32_t *)this + 1) = a3;
  *((uint32_t *)this + 2) = a2;
  return this;
}



// ------------------------------------------------------------
// 0x55F700 sub_55F700 —— 礼赠收尾（55F3A0/55CCF0/55CDB0/55E650）
// ------------------------------------------------------------
char /*thiscall*/ sub_55F700(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  int v5; // eax
  uint32_t *i; // ecx
  uint8_t *v8; // eax

  sub_55F3A0(this, (uint32_t *)a2);
  if ( a3 == 0 )
  {
    if ( sub_55CCF0((char *)this, (uint32_t *)a2) != 0 )
      sub_55CDB0((uint32_t **)this, *(uint32_t **)(a2 + 76));
  }
  else if ( a3 != 2 || a2 == 0 || (v4 = *(uint32_t *)(a2 + 12)) < 4 || v4 > 7 || sub_55E650(this, (const void *)a2) == 0 )
  {
    v5 = 0;
    for ( i = this + 420 * a3 + 170; *i != 0; i += 21 )
    {
      if ( ++v5 >= 20 )
        return 0;
    }
    v8 = this + 420 * a3 + 21 * v5 + 151;
    qmemcpy(v8, (const void *)a2, 0x54u);
    v8[80] = 0;
    return 1;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x55F7B0 sub_55F7B0 —— 全局窗口获取（430C80）
// ------------------------------------------------------------
unsigned int /*stdcall*/ sub_55F7B0(int a1)
{
  char *v1; // esi

  v1 = (char *)dword_9B8874;
  if ( dword_9B8870 == 0
    || ((int)dword_9B8874 - dword_9B8870) >> 2 >= (unsigned int)((dword_9B8878 - dword_9B8870) >> 2) )
  {
    return sub_430C80((int)&unk_9B886C, (int)dword_9B8874, 1u, &a1);
  }
  *(uint32_t *)dword_9B8874 = a1;
  dword_9B8874 = v1 + 4;
  return (unsigned int)(v1 + 4);
}



// ------------------------------------------------------------
// 0x55F810 sub_55F810 —— 商品列表刷新 A（55CED0/55CE70/55E940/565EE0，148 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_55F810(int this)
{
  int v2; // edi
  int k; // ebx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // ebx
  int v9; // edi
  int v10; // ebx
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  unsigned int v15; // ebx
  int *v16; // eax
  bool v17; // zf
  int m; // ecx
  int v19; // ebx
  int v20; // eax
  int v21; // edi
  int v22; // eax
  int v23; // ebx
  int v24; // edx
  int v25; // edi
  int v26; // ebx
  int v27; // edx
  int v28; // edi
  int v29; // ebx
  int v30; // edx
  int v31; // edi
  int result; // eax
  int v33; // [esp+Ch] [ebp-14h] BYREF
  int v34; // [esp+10h] [ebp-10h]
  int v35; // [esp+14h] [ebp-Ch]
  int i; // [esp+18h] [ebp-8h]
  int j; // [esp+1Ch] [ebp-4h]

  *(uint8_t *)(this + 10128) = 0;
  v2 = this + 7852;
  for ( i = 4; i != 0; --i )
  {
    for ( j = 8; j != 0; --j )
    {
      for ( k = 4; k != 0; --k )
      {
        if ( *(uint32_t *)v2 != 0 )
          j__free(*(void **)v2);
        *(uint32_t *)v2 = 0;
        *(uint32_t *)(v2 + 4) = 0;
        *(uint32_t *)(v2 + 8) = 0;
        v2 += 16;
      }
    }
  }
  v4 = *(uint32_t *)(this + 512);
  if ( v4 != 0 )
    v4 = (*(uint32_t *)(this + 516) - v4) / 84;
  v5 = v4 - 1;
  if ( v4 - 1 >= 0 )
  {
    v6 = 84 * v5;
    j = 84 * v5;
    i = v5 + 1;
    while ( 1 )
    {
      v7 = *(uint32_t *)(this + 512);
      v8 = *(uint32_t *)(v7 + v6 + 12);
      v9 = v7 + v6;
      v34 = *(int16_t *)(v7 + v6 + 26);
      v35 = sub_55CED0(v8);
      v10 = sub_55CE70(v8);
      if ( (uint8_t)sub_55E940(v9) != 0 )
      {
        v11 = j + *(uint32_t *)(this + 512);
        v12 = 16 * (v34 + 4 * (v35 + 8 * v10));
        v13 = *(uint32_t *)(v12 + this + 7852);
        v14 = v12 + this + 7848;
        v33 = v11;
        v15 = v13 != 0 ? (*(uint32_t *)(v14 + 8) - v13) >> 2 : 0;
        if ( v13 != 0 && v15 < (*(uint32_t *)(v14 + 12) - v13) >> 2 )
        {
          v16 = *(int **)(v14 + 8);
          *v16 = v11;
          *(uint32_t *)(v14 + 8) = v16 + 1;
        }
        else
        {
          sub_565EE0(*(void **)(v14 + 8), 1, (int)&v33);
        }
        if ( *(uint8_t *)(*(uint32_t *)(this + 512) + j + 24) == 22 )
          *(uint8_t *)(this + 10128) = 1;
      }
      v17 = i == 1;
      j -= 84;
      --i;
      if ( v17 )
        break;
      v6 = j;
    }
  }
  for ( m = 0; m < 32; m += 8 )
  {
    j = (int)&unk_725C54;
    do
    {
      v19 = *(uint32_t *)(j - 4);
      v20 = (m + v19) << 6;
      v21 = *(uint32_t *)(v20 + this + 7868);
      v22 = v20 + this + 7864;
      if ( v21 != 0 && (*(uint32_t *)(v22 + 8) - v21) >> 2 != 0 )
        *(uint32_t *)(this + 4 * (m + v19 + 1930)) = (((*(uint32_t *)(v22 + 8) - v21) >> 2) - 1) / 6u;
      else
        *(uint32_t *)(this + 4 * (m + v19 + 1930)) = 0;
      v23 = *(uint32_t *)j;
      v24 = (m + *(uint32_t *)j) << 6;
      v25 = *(uint32_t *)(v24 + this + 7868);
      if ( v25 != 0 && (*(uint32_t *)(v24 + this + 7872) - v25) >> 2 != 0 )
        *(uint32_t *)(this + 4 * (m + v23 + 1930)) = (((*(uint32_t *)(v24 + this + 7872) - v25) >> 2) - 1) / 6u;
      else
        *(uint32_t *)(this + 4 * (m + v23 + 1930)) = 0;
      v26 = *(uint32_t *)(j + 4);
      v27 = (m + v26) << 6;
      v28 = *(uint32_t *)(v27 + this + 7868);
      if ( v28 != 0 && (*(uint32_t *)(v27 + this + 7872) - v28) >> 2 != 0 )
        *(uint32_t *)(this + 4 * (m + v26 + 1930)) = (((*(uint32_t *)(v27 + this + 7872) - v28) >> 2) - 1) / 6u;
      else
        *(uint32_t *)(this + 4 * (m + v26 + 1930)) = 0;
      v29 = *(uint32_t *)(j + 8);
      v30 = (m + v29) << 6;
      v31 = *(uint32_t *)(v30 + this + 7868);
      if ( v31 != 0 && (*(uint32_t *)(v30 + this + 7872) - v31) >> 2 != 0 )
        *(uint32_t *)(this + 4 * (m + v29 + 1930)) = (((*(uint32_t *)(v30 + this + 7872) - v31) >> 2) - 1) / 6u;
      else
        *(uint32_t *)(this + 4 * (m + v29 + 1930)) = 0;
      result = j + 16;
      j += 16;
    }
    while ( j < (int)dword_725C74 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x55FB40 sub_55FB40 —— 商品列表刷新 B（55E940/565EE0）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_55FB40(int this)
{
  int v2; // esi
  unsigned int result; // eax
  int v4; // edi
  int v5; // ecx
  unsigned int v6; // edx
  int *v7; // eax
  int v8; // ecx
  unsigned int v9; // esi
  int v10; // [esp+Ch] [ebp-Ch] BYREF
  unsigned int v11; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  v2 = this + 9992;
  if ( *(uint32_t *)(this + 9996) != 0 )
    j__free(*(void **)(this + 9996));
  *(uint32_t *)(v2 + 4) = 0;
  *(uint32_t *)(v2 + 8) = 0;
  *(uint32_t *)(v2 + 12) = 0;
  v11 = 0;
  for ( i = 0; ; i += 84 )
  {
    result = *(uint32_t *)(this + 528);
    if ( result == 0 )
      break;
    result = (int)(*(uint32_t *)(this + 532) - result) / 84;
    if ( v11 >= result )
      break;
    if ( sub_55E940(this, (int *)(i + *(uint32_t *)(this + 528))) != 0 )
    {
      v4 = i + *(uint32_t *)(this + 528);
      v5 = *(uint32_t *)(v2 + 4);
      v10 = v4;
      if ( v5 != 0 )
        v6 = (*(uint32_t *)(v2 + 8) - v5) >> 2;
      else
        v6 = 0;
      if ( v5 != 0 && v6 < (*(uint32_t *)(v2 + 12) - v5) >> 2 )
      {
        v7 = *(int **)(v2 + 8);
        *v7 = v4;
        *(uint32_t *)(v2 + 8) = v7 + 1;
      }
      else
      {
        sub_565EE0(*(void **)(v2 + 8), 1, (int)&v10);
      }
    }
    ++v11;
  }
  v8 = *(uint32_t *)(v2 + 4);
  if ( v8 != 0 && (result = (*(uint32_t *)(v2 + 8) - v8) >> 2) != 0 )
  {
    v9 = ((*(uint32_t *)(v2 + 8) - v8) >> 2) - 1;
    *(uint32_t *)(this + 496) = v9 / 6;
    return -1431655765 * v9;
  }
  else
  {
    *(uint8_t *)(*(uint32_t *)(this + 7424) + 17) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x55FC80 sub_55FC80 —— 商品列表刷新 C（55E940/565EE0）
// ------------------------------------------------------------
int /*thiscall*/ sub_55FC80(uint32_t *this)
{
  uint32_t *v1; // edi
  void *v2; // eax
  uint32_t *v3; // esi
  int v4; // eax
  int v5; // eax
  int result; // eax
  int v7; // ebx
  int v8; // ecx
  int v9; // edi
  unsigned int v10; // edx
  int *v11; // eax
  int v12; // ecx
  unsigned int v13; // esi
  int v14; // [esp+Ch] [ebp-Ch] BYREF
  int v15; // [esp+10h] [ebp-8h]
  uint32_t *v16; // [esp+14h] [ebp-4h]

  v1 = this;
  v2 = (void *)*(this + 2503);
  v3 = this + 2502;
  v16 = this;
  if ( v2 != nullptr )
    j__free(v2);
  v3[1] = 0;
  v3[2] = 0;
  v3[3] = 0;
  v4 = v1[136];
  if ( v4 != 0 )
    v5 = (v1[137] - v4) / 84;
  else
    v5 = 0;
  result = v5 - 1;
  if ( result >= 0 )
  {
    v7 = 84 * result;
    v15 = result + 1;
    do
    {
      if ( sub_55E940((int)v1, (int *)(v7 + v1[136])) != 0 )
      {
        v8 = v3[1];
        v9 = v7 + v1[136];
        v14 = v9;
        if ( v8 != 0 )
          v10 = (v3[2] - v8) >> 2;
        else
          v10 = 0;
        if ( v8 != 0 && v10 < (v3[3] - v8) >> 2 )
        {
          v11 = (int *)v3[2];
          *v11 = v9;
          v3[2] = v11 + 1;
        }
        else
        {
          sub_565EE0((void *)v3[2], 1, (int)&v14);
        }
        v1 = v16;
      }
      v7 -= 84;
      result = --v15;
    }
    while ( v15 != 0 );
  }
  v12 = v3[1];
  if ( v12 != 0 && (result = (v3[2] - v12) >> 2) != 0 )
  {
    v13 = ((v3[2] - v12) >> 2) - 1;
    v1[125] = v13 / 6;
    return -1431655765 * v13;
  }
  else
  {
    *(uint8_t *)(v1[1857] + 17) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x55FDB0 sub_55FDB0 —— 商品列表刷新总入口（55FB40/55FC80/55F810/55C770/55CD70，181 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_55FDB0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // ebx
  int v5; // ecx
  int v6; // edi
  int v7; // edi
  unsigned int v8; // edx
  int v9; // ebx
  int v10; // ecx
  int v11; // edi
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  char *v15; // ecx
  int (/*thiscall*/ ***v16)(uint32_t); // eax
  int (/*thiscall*/ ***v17)(uint32_t); // ebx
  int v18; // eax
  int v19; // [esp+4h] [ebp-14h]
  int v20; // [esp+8h] [ebp-10h]
  int v21; // [esp+Ch] [ebp-Ch]
  unsigned int v22; // [esp+10h] [ebp-8h]
  int v23; // [esp+14h] [ebp-4h]
  uint32_t *v24; // [esp+20h] [ebp+8h]

  result = *(this + 2488);
  if ( result == 0 )
    return result;
  v4 = *(this + 11);
  v20 = v4;
  v5 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 1032))(result);
  result = a2;
  v19 = v5;
  if ( a2 == -1 )
  {
    if ( v4 != 0 )
    {
      result = *(this + v4 + 119);
      if ( result > 0 )
      {
        v6 = result - 1;
        *(this + v4 + 119) = result - 1;
LABEL_19:
        v7 = 6 * v6;
        if ( v4 != 0 )
        {
          if ( v4 == 1 )
          {
            sub_55FB40(this);
          }
          else if ( v4 == 2 )
          {
            sub_55FC80(this);
          }
        }
        else
        {
          sub_55F810(this);
        }
        v8 = v7;
        v9 = 4 * v7;
        v21 = 0;
        v22 = v7;
        v23 = 4 * v7;
        v24 = this + 143;
        while ( 1 )
        {
          if ( v20 != 0 )
          {
            if ( v20 == 1 )
            {
              v12 = *(this + 2499);
              if ( v12 == 0 || v8 >= (*(this + 2500) - v12) >> 2 )
                goto LABEL_46;
              v11 = *(uint32_t *)(v12 + v9);
            }
            else
            {
              if ( v20 != 2 )
                goto LABEL_46;
              v10 = *(this + 2503);
              if ( v10 == 0 || v8 >= (*(this + 2504) - v10) >> 2 )
                goto LABEL_46;
              v11 = *(uint32_t *)(v10 + v9);
            }
          }
          else
          {
            v13 = (*(this + 1897) + 8 * v19) << 6;
            v14 = *(uint32_t *)((char *)this + v13 + 7868);
            v15 = (char *)this + v13;
            if ( v14 == 0 || v22 >= (*((uint32_t *)v15 + 1968) - v14) >> 2 )
              goto LABEL_46;
            v11 = *(uint32_t *)(*((uint32_t *)v15 + 1967) + v9);
          }
          if ( v11 != 0 )
          {
            if ( *(uint32_t *)(v11 + 76) == 0 )
            {
              v16 = (int (/*thiscall*/ ***)(uint32_t))sub_55C770(*(void **)(v11 + 12));
              v17 = v16;
              *(uint32_t *)(v11 + 76) = v16;
              if ( v16 != nullptr )
              {
                *(uint8_t *)(v11 + 80) = 1;
                if ( (**v16)(v16) == 2 && *(int *)(*v17)[43](v17) <= 7 )
                  sub_55CD70(v11);
              }
              v9 = v23;
            }
            v18 = v21;
            *v24 = v11;
            *(uint8_t *)(*(uint32_t *)(v21 + *(this + 149)) + 16) = 1;
            goto LABEL_47;
          }
LABEL_46:
          v18 = v21;
          *v24 = 0;
          *(uint8_t *)(*(uint32_t *)(v21 + *(this + 149)) + 16) = 0;
LABEL_47:
          ++v24;
          v9 += 4;
          result = v18 + 12;
          v8 = v22 + 1;
          v23 = v9;
          ++v22;
          v21 = result;
          if ( result >= 72 )
            return result;
        }
      }
      return result;
    }
    result = 8 * v5;
    if ( (int)*(this + 8 * v5 + *(this + 1897) + 1898) <= 0 )
      return result;
    --*(this + result + *(this + 1897) + 1898);
LABEL_18:
    v6 = *(this + result + *(this + 1897) + 1898);
    goto LABEL_19;
  }
  if ( a2 != 1 )
  {
    if ( v4 != 0 )
    {
      v6 = *(this + v4 + 119);
      if ( v6 <= *(this + v4 + 123) )
        goto LABEL_19;
      return result;
    }
    result = 8 * v5;
    if ( *(this + 8 * v5 + *(this + 1897) + 1898) > *(this + 8 * v5 + *(this + 1897) + 1930) )
      return result;
    goto LABEL_18;
  }
  if ( v4 != 0 )
  {
    result = *(this + v4 + 119);
    if ( result < *(this + v4 + 123) )
    {
      v6 = result + 1;
      *(this + v4 + 119) = result + 1;
      goto LABEL_19;
    }
  }
  else
  {
    result = 8 * v5;
    if ( *(this + 8 * v5 + *(this + 1897) + 1898) < *(this + 8 * v5 + *(this + 1897) + 1930) )
    {
      v6 = ++*(this + result + *(this + 1897) + 1898);
      goto LABEL_19;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x5600A0 sub_5600A0 —— 商品选中刷新（55FDB0）
// ------------------------------------------------------------
int /*thiscall*/ sub_5600A0(int this)
{
  int v2; // eax
  uint32_t *v3; // ecx
  int v4; // eax
  int v5; // eax
  int result; // eax

  sub_55FDB0((int *)this, 0);
  v2 = 0;
  v3 = (uint32_t *)(1680 * *(uint32_t *)(this + 44) + this + 680);
  while ( *v3 == 0 )
  {
    ++v2;
    v3 += 21;
    if ( v2 >= 20 )
    {
      *(uint8_t *)(*(uint32_t *)(this + 7480) + 17) = 0;
      goto LABEL_5;
    }
  }
  *(uint8_t *)(*(uint32_t *)(this + 7480) + 17) = 1;
LABEL_5:
  *(uint8_t *)(*(uint32_t *)(this + 7404) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 7408) + 16) = 0;
  v4 = *(uint32_t *)(this + 44);
  *(uint32_t *)(this + 7412) = -1;
  if ( v4 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 336) + 32))(*(uint32_t *)(this + 336), 8);
  v5 = v4 - 1;
  if ( v5 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 336) + 32))(*(uint32_t *)(this + 336), 0);
  result = v5 - 1;
  if ( result == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 336) + 32))(*(uint32_t *)(this + 336), 2);
  return result;
}



// ------------------------------------------------------------
// 0x560140 sub_560140 —— 商品列表显示（698F90/55FDB0/44BBA0）
// ------------------------------------------------------------
char /*thiscall*/ sub_560140(int this, char a2, int a3)
{
  char result; // al

  result = a2;
  if ( a2 != 0 )
  {
    if ( a3 != 0 )
    {
      if ( a3 == 1 )
      {
        *(uint8_t *)(this + 7540) = 1;
        *(uint8_t *)(this + 7541) = 0;
        *(uint8_t *)(this + 7542) = 0;
        result = sub_698F90(this + 7528, 0, 0);
        *(uint8_t *)(this + 7584) = 0;
        return result;
      }
      result = a3 - 2;
      if ( a3 == 2 )
      {
        result = sub_55FDB0((int *)this, 0);
        *(uint8_t *)(this + 7584) = 0;
        return result;
      }
    }
    else
    {
      sub_55FDB0((int *)this, 0);
      result = sub_44BBA0(*(uint32_t **)(this + 4), 1, 1u);
    }
  }
  *(uint8_t *)(this + 7584) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5601C0 sub_5601C0 —— 礼赠流程主函数（55E8B0/44E8D0/44E850/55CB60/4015C0/63EF60/55F7B0，60 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_5601C0(int this, char a2, int a3, int a4, int a5)
{
  int v6; // eax
  int v7; // eax
  uint32_t *v8; // ecx
  int v9; // edi
  char *v10; // eax
  int v11; // edi
  void *Block[5]; // [esp+10h] [ebp-28h] BYREF
  unsigned int v13; // [esp+24h] [ebp-14h]
  int v14; // [esp+28h] [ebp-10h]
  int v15; // [esp+34h] [ebp-4h]

  v14 = dword_796E50;
  if ( sub_55E8B0((uint32_t *)this, a3, a4) != 0 )
  {
    if ( *(uint32_t *)(this + 10108) == 0 )
    {
      v6 = sub_44E8D0(*(char **)(this + 4), (void *)0x20, this, 0xFFFF);
      v7 = __RTDynamicCast(
             v6,
             0,
             &IRDPopupWindow `RTTI Type Descriptor',
             &CNRDItemTradeResultWindow `RTTI Type Descriptor',
             0);
      v8 = *(uint32_t **)(this + 4);
      *(uint32_t *)(this + 10108) = v7;
      sub_44E850(v8, 27);
    }
    v9 = sub_55E8B0((uint32_t *)this, a3, a4);
    v13 = 15;
    Block[4] = nullptr;
    LOBYTE(Block[0]) = 0;
    v10 = sub_55CB60(a5);
    sub_4015C0(v10, strlen(v10));
    v15 = 0;
    if ( v9 != 0 )
    {
      if ( a2 != 0 )
      {
        sub_63EF60(*(uint32_t **)(this + 10108), *(int **)(v9 + 76), 1, nullptr);
        v11 = *(uint32_t *)(v9 + 8);
        if ( v11 > 0 )
          sub_55F7B0(v11);
      }
      else
      {
        sub_63EF60(*(uint32_t **)(this + 10108), *(int **)(v9 + 76), 0, (const char *)Block);
      }
    }
    if ( v13 >= 0x10 )
      j__free(Block[0]);
  }
}



// ------------------------------------------------------------
// 0x560310 sub_560310 —— 商城分页（44C2A0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_560310(char **this, uint32_t *a2, uint8_t *a3)
{
  char *v4; // edi
  char *v5; // esi

  sub_55E6C0(a3 + 84, *(this + 2), a3);
  v4 = *(this + 2);
  v5 = v4 - 84;
  do
  {
    sub_44C2A0(v5);
    v5 += 84;
  }
  while ( v5 != v4 );
  *(this + 2) -= 84;
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x560360 sub_560360 —— 商城分页 2（560310）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_560360(int this)
{
  int v1; // edx
  int v2; // eax
  int v3; // eax
  char **v5; // [esp+Ch] [ebp-4h] BYREF

  v1 = *(uint32_t *)(this + 528);
  v5 = (char **)(this + 524);
  if ( v1 != 0 )
    v2 = (*(uint32_t *)(this + 532) - v1) / 84;
  else
    v2 = 0;
  v3 = 84 * (v2 - 1);
  qmemcpy((void *)(this + 10024), (const void *)(v3 + *(uint32_t *)(this + 528)), 0x54u);
  *(uint8_t *)(this + 10104) = 0;
  dword_795210 = *(uint32_t *)(this + 10056);
  return sub_560310(v5, &v5, (uint8_t *)(v3 + *(uint32_t *)(this + 528)));
}



// ------------------------------------------------------------
// 0x5603E0 sub_5603E0 —— 商城对象更新（46C180/42B0F0/4939E0/41CBF0）
// ------------------------------------------------------------
int /*thiscall*/ sub_5603E0(uint32_t *this, int a2)
{
  int *v3; // ebx
  int v4; // esi
  int v5; // eax
  void *v6; // eax
  int v7; // eax
  int *v8; // eax
  uint8_t v10[144]; // [esp+10h] [ebp-A0h] BYREF
  int v11; // [esp+A0h] [ebp-10h]
  int v12; // [esp+ACh] [ebp-4h]

  v11 = dword_796E50;
  sub_46C180((int)v10, a2);
  v12 = 0;
  v3 = &dword_725C50;
  do
  {
    v5 = *(this + *v3 + 2490);
    if ( v5 != 0 )
    {
      v4 = *v3;
      *(uint32_t *)&v10[4 * v4 + 56] = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)v5 + 16))() + 4);
    }
    ++v3;
  }
  while ( (int)v3 < (int)dword_725C70 );
  if ( *(this + 2489) == 0 )
  {
    v6 = operator new(0x294u);
    LOBYTE(v12) = 1;
    if ( v6 != nullptr )
      v7 = sub_42B0F0((int)v6);
    else
      v7 = 0;
    LOBYTE(v12) = 0;
    *(this + 2489) = v7;
  }
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2489) + 348))(*(this + 2489), v10);
  v8 = (int *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2489) + 344))(*(this + 2489));
  sub_4939E0(*v8, 0);
  v12 = -1;
  return sub_41CBF0(v10);
}



// ------------------------------------------------------------
// 0x5604F0 sub_5604F0 —— 商品选择应用（429830 + 5603E0）
// ------------------------------------------------------------
int */*thiscall*/ sub_5604F0(int *this, char a2)
{
  int v3; // eax
  uint32_t *v4; // ecx
  int *result; // eax
  int v6; // edi
  bool v7; // dl
  int i; // ecx
  int v9; // esi

  if ( sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0 )
  {
    v3 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    sub_5603E0(this, v3 + 16);
  }
  *(uint8_t *)(*(this + 2483) + 16) = a2;
  *(uint8_t *)(*(this + 2484) + 16) = a2;
  *(uint8_t *)(*(this + 2481) + 16) = a2;
  *(uint8_t *)(*(this + 2480) + 16) = a2;
  *(uint8_t *)(*(this + 2482) + 16) = a2;
  *(uint8_t *)(*(this + 2486) + 16) = a2;
  *(uint8_t *)(*(this + 2487) + 16) = a2;
  *(uint8_t *)(*(this + 2485) + 16) = a2;
  *(uint8_t *)(*(this + 2474) + 16) = a2;
  if ( a2 != 0 )
  {
    v4 = this + 1832;
    result = (int *)&unk_725D54;
    do
    {
      *(uint8_t *)(*(v4 - 1) + 17) = *(result - 1) != -1;
      *(uint8_t *)(*v4 + 17) = *result != -1;
      *(uint8_t *)(v4[1] + 17) = result[1] != -1;
      *(uint8_t *)(v4[2] + 17) = result[2] != -1;
      v6 = v4[3];
      v7 = result[3] != -1;
      result += 5;
      v4 += 5;
      *(uint8_t *)(v6 + 17) = v7;
    }
    while ( (int)result < (int)dword_725DA4 );
  }
  else
  {
    result = this + 1831;
    for ( i = 20; i != 0; --i )
    {
      v9 = *result++;
      *(uint8_t *)(v9 + 17) = 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x560610 sub_560610 —— SERA_SHOP 赛丽亚商店事件（698F90/55FDB0/5604F0/432EA0/44E8D0/65FA00/461170/461190/55EFB0/645CA0/44E850/44ABE0）
// ------------------------------------------------------------
char /*thiscall*/ sub_560610(int this, int a2)
{
  char result; // al
  int v5; // eax
  bool v6; // zf
  LONG RecursionCount; // eax
  int v8; // [esp+Ch] [ebp+8h]

  result = *(uint8_t *)(this + 7584);
  if ( result == 0 )
  {
    while ( 1 )
    {
      v5 = *(uint32_t *)(this + 12);
      *(uint32_t *)(this + 12) = a2;
      v8 = v5;
      *(uint8_t *)(this + 29) = 0;
      *(uint8_t *)(this + 30) = 0;
      result = sub_698F90(this + 16, 0, 0);
      if ( a2 == 0 )
        break;
      if ( a2 != 1 )
        return result;
      v6 = dword_8F7C04 == 0;
      *(uint32_t *)(this + 9952) = dword_8F7C04;
      if ( !v6 )
      {
        sub_55FDB0((int *)this, 0);
        *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 1;
        if ( *(uint32_t *)(this + 44) == 0 )
          sub_5604F0((int *)this, 1);
        sub_432EA0("SERA_SHOP", -1, 0, 0);
        result = *(uint8_t *)(this + 10128);
        if ( result != 0 )
        {
          result = byte_9B887D;
          if ( byte_9B887D == 0 )
          {
            result = sub_44E8D0(*(char **)(this + 4), (void *)0x46, 0, 0);
            byte_9B887D = 1;
          }
        }
        return result;
      }
      result = *(uint8_t *)(this + 7584);
      a2 = 0;
      if ( result != 0 )
        return result;
    }
    if ( v8 == 1 )
    {
      RecursionCount = lpCriticalSection[107].RecursionCount;
      if ( RecursionCount != 0 )
        sub_65FA00(lpCriticalSection, RecursionCount, 0, 0, 0, 0, 0, 0);
      if ( *(uint32_t *)(this + 10124) != -1 )
      {
        sub_461170(*((uint8_t **)dword_8F8528 + 4), 1);
        sub_461190(*((uint32_t *)dword_8F8528 + 4));
      }
    }
    sub_55EFB0((uint32_t *)this);
    *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 0;
    sub_645CA0(*(uint32_t **)(this + 8));
    sub_44E850(*(uint32_t **)(this + 4), 26);
    return sub_44ABE0(*(uint32_t **)(this + 4), 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x560780 sub_560780 —— 角色选择事件 SELECT_CHARACTER（5604F0/5600A0/432EA0）
// ------------------------------------------------------------
void */*thiscall*/ sub_560780(int *this, void *a2)
{
  void *result; // eax

  result = (void *)*(this + 11);
  if ( result != a2 )
  {
    if ( result == nullptr )
      sub_5604F0(this, 0);
    *(this + 11) = (int)a2;
    if ( a2 == nullptr )
      sub_5604F0(this, 1);
    sub_5600A0((int)this);
    return sub_432EA0("SELECT_CHARACTER", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5607D0 sub_5607D0 —— 商品选择 Update（217 行：COMMAND_SELECT/SCROLL_ARROW/SELECT_CHARACTER 事件 + 55FDB0/55E210/55E2D0/55C840/43B500/560780/560610/55E190/55F240/55F160/55F700/55C730/43B520/55CA50/44A980/486820）
// ------------------------------------------------------------
int /*thiscall*/ sub_5607D0(uint32_t *this)
{
  int v2; // eax
  int result; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // ebx
  uint32_t *v11; // edi
  int v12; // ecx
  int v13; // ebx
  uint32_t *v14; // edi
  int v15; // edi
  uint32_t *v16; // ebx
  int v17; // eax
  int v18; // ecx
  int *v19; // ecx
  int v20; // edi
  int v21; // edi
  int v22; // esi
  int v23; // ecx
  int v24; // edx
  int v25; // ecx
  int v26; // [esp+4h] [ebp-4h]
  uint32_t *v27; // [esp+4h] [ebp-4h]
  uint32_t *v28; // [esp+4h] [ebp-4h]

  v2 = *(this + 1873);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    sub_432EA0("SCROLL_ARROW", -1, 0, 0);
    return sub_55FDB0(-1);
  }
  v4 = *(this + 1874);
  if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
  {
    sub_432EA0("SCROLL_ARROW", -1, 0, 0);
    return sub_55FDB0(1);
  }
  v5 = *(this + 1870);
  if ( *(uint8_t *)(v5 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v5 + 12) )
  {
    sub_432EA0("COMMAND_SELECT", -1, 0, 0);
    return sub_55E210(*(this + 11));
  }
  v6 = *(this + 1872);
  if ( *(uint8_t *)(v6 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v6 + 12) )
  {
    sub_432EA0("COMMAND_SELECT", -1, 0, 0);
    return sub_55E2D0(this);
  }
  v7 = *(this + 1871);
  if ( *(uint8_t *)(v7 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v7 + 12) )
    return sub_55C840(this);
  if ( (uint8_t)sub_43B500(*(this + 1855)) != 0 && *(this + 11) != 0 )
    return sub_560780(0);
  if ( (uint8_t)sub_43B500(*(this + 1856)) != 0 && *(this + 11) != 1 )
    return sub_560780(1);
  if ( (uint8_t)sub_43B500(*(this + 1857)) != 0 && *(this + 11) != 2 )
    return sub_560780(2);
  if ( (uint8_t)sub_43B500(*(this + 1858)) != 0 && *(this + 11) != 3 )
    return sub_560780(3);
  if ( (uint8_t)sub_43B500(*(this + 1859)) != 0 )
  {
    sub_432EA0("SELECT_CHARACTER", -1, 0, 0);
    return sub_560610(0);
  }
  if ( (uint8_t)sub_43B500(*(this + 1851)) != 0 )
  {
    v8 = 84 * (*(this + 1853) + 20 * *(this + 11));
    v9 = *(uint32_t *)((char *)this + v8 + 680);
    result = (int)this + v8;
    if ( v9 != 0 )
      result = sub_55E190(result + 604);
    *(uint8_t *)(*(this + 1851) + 16) = 0;
    *(uint8_t *)(*(this + 1852) + 16) = 0;
    *(this + 1853) = -1;
    return result;
  }
  if ( (uint8_t)sub_43B500(*(this + 1852)) != 0 )
  {
    sub_55F240(*(this + 1853), *(this + 11));
    *(uint8_t *)(*(this + 1851) + 16) = 0;
    result = *(this + 1852);
    *(uint8_t *)(result + 16) = 0;
    *(this + 1853) = -1;
    return result;
  }
  if ( (uint8_t)sub_43B500(*(this + 2474)) != 0 )
    return sub_55F160(0);
  v26 = *(this + 11);
  v10 = 0;
  v11 = this + 143;
  do
  {
    v12 = *(uint32_t *)(v10 + *(this + 149));
    if ( *(uint8_t *)(v12 + 16) != 0
      && (uint8_t)sub_43B500(v12) != 0
      && *v11 != 0
      && (uint8_t)sub_55F700(*v11, v26) == 1 )
    {
      return sub_55C730(this);
    }
    v10 += 12;
    ++v11;
  }
  while ( v10 < 72 );
  v13 = 0;
  v27 = this + 143;
  v14 = (uint32_t *)(*(this + 149) + 8);
  do
  {
    if ( *(uint8_t *)(*v14 + 16) != 0 && (uint8_t)sub_43B500(*v14) != 0 && *v27 != 0 )
    {
      sub_55E190(*(this + v13 + 143));
      return (int)sub_432EA0("COMMAND_SELECT", -1, 0, 0);
    }
    ++v13;
    v14 += 3;
    ++v27;
  }
  while ( v13 < 6 );
  v15 = 0;
  v16 = this + 1831;
  v28 = this + 170;
  while ( 1 )
  {
    v17 = *(this + 11);
    v18 = *v16;
    if ( v17 != 0 )
    {
      if ( *(uint8_t *)(v18 + 16) != 0 && *(this + 420 * v17 + 21 * v15 + 170) != 0 )
      {
        if ( (uint8_t)sub_43B520() != 0 )
          return sub_55F240(v15, *(this + 11));
        if ( (uint8_t)sub_43B500(*v16) != 0 )
          return sub_55CA50(1, v15);
      }
      goto LABEL_64;
    }
    if ( *(uint8_t *)(v18 + 16) != 0 )
    {
      if ( *v28 != 0 )
      {
        if ( (uint8_t)sub_43B520() != 0 )
          return sub_55F240(v15, 0);
        if ( (uint8_t)sub_43B500(*v16) != 0 )
          return sub_55CA50(1, v15);
        goto LABEL_64;
      }
      if ( (uint8_t)sub_43B520() != 0 )
        break;
    }
LABEL_64:
    ++v15;
    ++v16;
    v28 += 21;
    if ( v15 >= 20 )
    {
      v19 = &dword_725C50;
      while ( 1 )
      {
        v20 = *v19;
        result = *(this + *v19 + 2480);
        if ( *(uint8_t *)(result + 16) != 0 && *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
          break;
        if ( (int)++v19 >= (int)dword_725C70 )
          return result;
      }
      result = (int)sub_432EA0("SELECT_CHARACTER", -1, 0, 0);
      v23 = *(this + 2488);
      if ( v23 != 0 )
      {
        v24 = (v20 + 8 * *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v23 + 1032))(v23)) << 6;
        v25 = *(uint32_t *)((char *)this + v24 + 7868);
        if ( v25 != 0 && (*(uint32_t *)((char *)this + v24 + 7872) - v25) >> 2 != 0 )
        {
          *(this + 1897) = v20;
          sub_55FDB0(0);
          memset(this + 1898, 0, 0x80u);
          return 0;
        }
        else
        {
          result = *(this + 1897);
          *(uint8_t *)(*(this + result + 2480) + 132) = 1;
          *(uint8_t *)(*(this + v20 + 2480) + 132) = 0;
        }
      }
      return result;
    }
  }
  v21 = dword_725D50[v15];
  result = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2488) + 792))(*(this + 2488), v21);
  if ( result != 0 )
  {
    v22 = 0;
    while ( 1 )
    {
      result = sub_44A980(v22);
      if ( result == 0 )
        break;
      if ( ++v22 >= 105 )
        return result;
    }
    return sub_486820(v22, v21, 1);
  }
  return result;
}


// ============================================================
// 【分区 13】新版商城主逻辑（0x560D10-0x561FF0）
// 主窗口 0x560D10（778 行·本文件最大）=NewCashShop：装载 Etc/NewCashShop.etc
// （4FB180 配置解析 + 69CE10/69CF50/69CF80/69CFB0 控件组 + 560360/55F810/
// 55FB40/55FC80/55F4D0 刷新链 + 560610/5604F0/5600A0 商店联动）；
// SELECT_CHARACTER 角色选择事件贯穿。
// ============================================================
// ------------------------------------------------------------
// 0x560D10 sub_560D10 —— 新版商城主窗口逻辑（778 行·本文件最大）：装载 Etc/NewCashShop.etc 配置 + 426BD0/423B30/43C410/43C4D0/43C630 绘制 + 69A5F0/69A840 + 69C780/69C7B0 + 418DD0 + 69CE10/69CF50/69CF80/69CFB0 控件组 + 4FB180 解析 + 560360/55F810/55FB40/55FC80/55F4D0/698F90/560610/5604F0/5600A0 联动
// ------------------------------------------------------------
// SELECT_CHARACTER 事件贯穿本函数；NewCashShop.etc 即"新版商城"布局配置。
void */*thiscall*/ sub_560D10(int this)
{
  void *v2; // eax
  int v3; // eax
  int v4; // eax
  uint32_t *v5; // eax
  void *v6; // eax
  int v7; // eax
  int v8; // eax
  uint32_t *v9; // edi
  int v10; // eax
  int v11; // edi
  void *v12; // ecx
  void *v13; // eax
  void *v14; // eax
  void *v15; // ecx
  void *v16; // eax
  void *v17; // eax
  void *v18; // ecx
  void *v19; // eax
  uint32_t *v20; // eax
  uint32_t *v21; // edi
  uint32_t *v22; // eax
  char *v23; // edi
  bool v24; // cc
  int *v25; // edi
  void *v26; // eax
  void *v27; // ecx
  void *v28; // eax
  void *v29; // eax
  void *v30; // ecx
  int *v31; // edx
  int *v32; // ecx
  uint32_t *v33; // edi
  void *v34; // eax
  void *v35; // ecx
  void *v36; // eax
  int v37; // edx
  int v38; // eax
  int v39; // edx
  int v40; // eax
  char *v41; // ecx
  int *v42; // edx
  uint32_t *v43; // edi
  uint32_t *v44; // edi
  uint32_t *v45; // eax
  uint32_t *v46; // edi
  uint32_t *v47; // eax
  uint32_t *v48; // edi
  uint32_t *v49; // eax
  uint32_t *v50; // edi
  char *v51; // eax
  uint32_t *v52; // eax
  uint32_t *v53; // edi
  uint32_t *v54; // eax
  void *v55; // eax
  int v56; // eax
  int v57; // eax
  int v58; // eax
  int v59; // eax
  int v60; // eax
  int v61; // eax
  int v62; // eax
  int v63; // eax
  int v64; // eax
  int v65; // eax
  int v66; // eax
  int v67; // eax
  int v68; // eax
  int v69; // eax
  void *result; // eax
  int v71; // [esp-8h] [ebp-A8h]
  int v72; // [esp-8h] [ebp-A8h]
  int v73; // [esp-8h] [ebp-A8h]
  int v74; // [esp-8h] [ebp-A8h]
  int v75; // [esp-8h] [ebp-A8h]
  int v76; // [esp-4h] [ebp-A4h]
  int v77; // [esp+8h] [ebp-98h]
  int v78; // [esp+Ch] [ebp-94h]
  uint32_t v79[8]; // [esp+10h] [ebp-90h] BYREF
  int v80; // [esp+30h] [ebp-70h]
  int v81; // [esp+34h] [ebp-6Ch]
  int v82; // [esp+38h] [ebp-68h] BYREF
  int v83; // [esp+3Ch] [ebp-64h]
  int v84; // [esp+40h] [ebp-60h]
  int v85; // [esp+44h] [ebp-5Ch]
  int v86; // [esp+48h] [ebp-58h]
  int v87; // [esp+4Ch] [ebp-54h]
  int v88; // [esp+50h] [ebp-50h]
  int v89; // [esp+54h] [ebp-4Ch]
  int v90; // [esp+58h] [ebp-48h]
  int v91; // [esp+5Ch] [ebp-44h]
  int v92; // [esp+60h] [ebp-40h]
  int v93; // [esp+64h] [ebp-3Ch]
  int v94; // [esp+68h] [ebp-38h]
  int v95; // [esp+6Ch] [ebp-34h]
  int v96; // [esp+70h] [ebp-30h]
  int v97; // [esp+74h] [ebp-2Ch]
  int v98; // [esp+78h] [ebp-28h]
  int v99; // [esp+7Ch] [ebp-24h]
  uint32_t *v100; // [esp+80h] [ebp-20h]
  int *v101; // [esp+84h] [ebp-1Ch]
  void *Block; // [esp+88h] [ebp-18h]
  void *v103; // [esp+8Ch] [ebp-14h]
  void *v104; // [esp+90h] [ebp-10h]
  int v105; // [esp+9Ch] [ebp-4h]

  *(uint32_t *)(this + 56) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 156);
  *(uint32_t *)(this + 60) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 160);
  v2 = operator new(0x68u);
  Block = v2;
  v105 = 0;
  if ( v2 != nullptr )
    v3 = sub_426BD0(v2);
  else
    v3 = 0;
  *(uint32_t *)(this + 52) = v3;
  *(uint32_t *)(v3 + 28) = 640;
  *(uint32_t *)(v3 + 32) = 480;
  *(uint32_t *)(*(uint32_t *)(this + 52) + 68) = this;
  Block = operator new(0x2Cu);
  v105 = 1;
  if ( Block != nullptr )
    v4 = sub_423B30(dword_79C0B0, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 16), 25, 4);
  else
    v4 = 0;
  *(uint32_t *)(this + 48) = v4;
  *(uint8_t *)(v4 + 24) = 1;
  *(uint8_t *)(this + 64) = 0;
  *(uint8_t *)(this + 65) = 0;
  *(uint8_t *)(this + 66) = 0;
  *(uint8_t *)(this + 67) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 80) = 6;
  *(uint32_t *)(this + 92) = 1600;
  *(uint32_t *)(this + 84) = 12;
  *(uint32_t *)(this + 112) = dword_99FCCC;
  *(uint32_t *)(this + 92) = 165;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 68) = -16777216;
  *(uint8_t *)(this + 116) = 0;
  *(uint8_t *)(this + 117) = 0;
  *(uint8_t *)(this + 118) = 0;
  *(uint8_t *)(this + 119) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 6;
  *(uint32_t *)(this + 136) = 12;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 1600;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 164) = dword_99FCCC;
  *(uint32_t *)(this + 144) = 165;
  *(uint32_t *)(this + 128) = 2;
  *(uint32_t *)(this + 120) = -16777216;
  *(uint8_t *)(this + 168) = 0;
  *(uint8_t *)(this + 169) = 0;
  *(uint8_t *)(this + 170) = 0;
  *(uint8_t *)(this + 171) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 6;
  *(uint32_t *)(this + 188) = 12;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 1600;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 216) = dword_99FCCC;
  *(uint32_t *)(this + 196) = 160;
  *(uint32_t *)(this + 180) = 0;
  *(uint8_t *)(this + 220) = 0;
  *(uint8_t *)(this + 221) = 0;
  *(uint8_t *)(this + 222) = 0;
  *(uint8_t *)(this + 223) = 0;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 6;
  *(uint32_t *)(this + 240) = 12;
  *(uint32_t *)(this + 244) = 0;
  *(uint32_t *)(this + 248) = 1600;
  *(uint32_t *)(this + 252) = 0;
  *(uint32_t *)(this + 256) = 0;
  *(uint32_t *)(this + 260) = 0;
  *(uint32_t *)(this + 264) = 0;
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 268) = dword_99FCCC;
  *(uint32_t *)(this + 248) = 165;
  *(uint32_t *)(this + 232) = 1;
  *(uint32_t *)(this + 224) = -16777216;
  *(uint8_t *)(this + 272) = 0;
  *(uint8_t *)(this + 273) = 0;
  *(uint8_t *)(this + 274) = 0;
  *(uint8_t *)(this + 275) = 0;
  *(uint32_t *)(this + 284) = 0;
  *(uint32_t *)(this + 288) = 6;
  *(uint32_t *)(this + 292) = 12;
  *(uint32_t *)(this + 296) = 0;
  *(uint32_t *)(this + 300) = 1600;
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 320) = dword_99FCCC;
  *(uint32_t *)(this + 300) = 165;
  *(uint32_t *)(this + 284) = 2;
  *(uint32_t *)(this + 276) = -16777216;
  v5 = operator new(0x4Cu);
  Block = v5;
  v105 = 2;
  if ( v5 != nullptr )
  {
    *v5 = 6;
    v103 = v5 + 1;
    `eh vector constructor iterator'(v5 + 1, 0xCu, 6, unknown_libname_6, sub_55C100);
    v6 = v103;
  }
  else
  {
    v6 = nullptr;
  }
  *(uint32_t *)(this + 596) = v6;
  Block = operator new(0x84u);
  v105 = 3;
  if ( Block != nullptr )
    v7 = sub_43C410(*(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 4, 4, 5, 4, 0, 0);
  else
    v7 = 0;
  *(uint32_t *)(this + 324) = v7;
  Block = operator new(0x84u);
  v105 = 4;
  if ( Block != nullptr )
    v8 = sub_43C410(*(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 6, 6, 7, 6, 0, 0);
  else
    v8 = 0;
  *(uint32_t *)(this + 328) = v8;
  v9 = operator new(0x88u);
  Block = v9;
  v105 = 5;
  if ( v9 != nullptr )
  {
    sub_43C4D0(*(uint32_t *)(this + 56), 9, 11);
    *v9 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v9 = nullptr;
  }
  *(uint32_t *)(this + 332) = v9;
  Block = operator new(0x74u);
  v105 = 6;
  if ( Block != nullptr )
    v10 = sub_43C630(*(uint32_t *)(this + 324), *(uint32_t *)(this + 328), *(uint32_t *)(this + 332));
  else
    v10 = 0;
  v105 = -1;
  *(uint32_t *)(this + 336) = v10;
  sub_69A5F0(604, 280);
  sub_69A840(*(uint32_t *)(this + 336));
  v11 = 0;
  v101 = (int *)&unk_725C20;
  do
  {
    v104 = operator new(0x84u);
    v105 = 7;
    if ( v104 != nullptr )
    {
      v103 = *(void **)(this + 56);
      sub_426BD0(v104);
      v12 = v104;
      LOBYTE(v105) = 8;
      *(uint32_t *)v104 = &nengine::CNButton::`vftable';
      sub_69C780(v12);
      sub_69C7B0(v103, 3, 3, 3, 3, 0, 0);
      v13 = v104;
    }
    else
    {
      v13 = nullptr;
    }
    *(uint32_t *)(v11 + *(uint32_t *)(this + 596)) = v13;
    v71 = *(uint32_t *)(v11 + *(uint32_t *)(this + 596));
    v105 = -1;
    sub_69A840(v71);
    *(uint32_t *)(*(uint32_t *)(v11 + *(uint32_t *)(this + 596)) + 68) = this;
    sub_69A5F0(*v101, v101[1]);
    *(uint8_t *)(*(uint32_t *)(v11 + *(uint32_t *)(this + 596)) + 16) = 0;
    v14 = operator new(0x84u);
    v104 = v14;
    v105 = 9;
    if ( v14 != nullptr )
    {
      v103 = *(void **)(this + 60);
      sub_426BD0(v14);
      v15 = v104;
      LOBYTE(v105) = 10;
      *(uint32_t *)v104 = &nengine::CNButton::`vftable';
      sub_69C780(v15);
      sub_69C7B0(v103, 41, 41, 41, 41, 0, 0);
      v16 = v104;
    }
    else
    {
      v16 = nullptr;
    }
    *(uint32_t *)(v11 + *(uint32_t *)(this + 596) + 4) = v16;
    v72 = *(uint32_t *)(v11 + *(uint32_t *)(this + 596) + 4);
    v105 = -1;
    sub_69A840(v72);
    sub_69A5F0(*v101 + 49, v101[1] + 63);
    *(uint8_t *)(*(uint32_t *)(v11 + *(uint32_t *)(this + 596) + 4) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(v11 + *(uint32_t *)(this + 596) + 4) + 17) = 0;
    v17 = operator new(0x84u);
    v104 = v17;
    v105 = 11;
    if ( v17 != nullptr )
    {
      v103 = *(void **)(this + 60);
      sub_426BD0(v17);
      v18 = v104;
      LOBYTE(v105) = 12;
      *(uint32_t *)v104 = &nengine::CNButton::`vftable';
      sub_69C780(v18);
      sub_69C7B0(v103, 42, 43, 44, 45, 0, 0);
      v19 = v104;
    }
    else
    {
      v19 = nullptr;
    }
    *(uint32_t *)(v11 + *(uint32_t *)(this + 596) + 8) = v19;
    v73 = *(uint32_t *)(v11 + *(uint32_t *)(this + 596) + 8);
    v105 = -1;
    sub_69A840(v73);
    sub_69A5F0(*v101 + 112, v101[1] + 63);
    *(uint8_t *)(*(uint32_t *)(v11 + *(uint32_t *)(this + 596) + 8) + 16) = 1;
    v11 += 12;
    v101 += 2;
  }
  while ( (int)v101 < (int)&dword_725C50 );
  *(uint32_t *)(this + 600) = sub_418DD0(4);
  v104 = &dword_725CB0;
  v103 = (void *)(this + 7324);
  do
  {
    v20 = operator new(0x84u);
    v21 = v20;
    Block = v20;
    v105 = 13;
    if ( v20 != nullptr )
    {
      v100 = *(uint32_t **)(this + 56);
      sub_426BD0(v20);
      LOBYTE(v105) = 14;
      *v21 = &nengine::CNButton::`vftable';
      sub_69C780(v21);
      sub_69C7B0(v100, 2, 2, 2, -1, 0, 0);
      v22 = v21;
    }
    else
    {
      v22 = nullptr;
    }
    v23 = (char *)v103;
    *(uint32_t *)v103 = v22;
    v105 = -1;
    sub_69A840(v22);
    *(uint32_t *)(*(uint32_t *)v23 + 68) = this;
    sub_69A5F0(*(uint32_t *)v104, *((uint32_t *)v104 + 1));
    *(uint8_t *)(*(uint32_t *)v23 + 16) = 1;
    v24 = (int)((char *)v104 + 8) < (int)&dword_725D50;
    v103 = v23 + 4;
    v104 = (char *)v104 + 8;
  }
  while ( v24 );
  *(uint32_t *)(this + 7416) = sub_418DD0(8);
  v85 = 34;
  v86 = 34;
  v87 = -1;
  v95 = -1;
  v99 = -1;
  v80 = 30;
  v81 = 31;
  v82 = 32;
  v83 = 68;
  v84 = 33;
  v88 = 35;
  v89 = 36;
  v90 = 37;
  v91 = 87;
  v92 = 46;
  v93 = 47;
  v94 = 48;
  v96 = 49;
  v97 = 50;
  v98 = 51;
  v100 = &unk_725DC8;
  v25 = &v82;
  v101 = (int *)(this + 7480);
  do
  {
    if ( v25[1] == -1 )
    {
      v29 = operator new(0x84u);
      v104 = v29;
      v105 = 17;
      if ( v29 != nullptr )
      {
        v103 = *(void **)(this + 60);
        sub_426BD0(v29);
        v30 = v104;
        LOBYTE(v105) = 18;
        *(uint32_t *)v104 = &nengine::CNButton::`vftable';
        sub_69C780(v30);
        sub_69C7B0(v103, *(v25 - 2), *(v25 - 1), *v25, -1, 0, 0);
        v28 = v104;
        goto LABEL_45;
      }
    }
    else
    {
      v26 = operator new(0x84u);
      v104 = v26;
      v105 = 15;
      if ( v26 != nullptr )
      {
        v103 = *(void **)(this + 60);
        sub_426BD0(v26);
        v27 = v104;
        LOBYTE(v105) = 16;
        *(uint32_t *)v104 = &nengine::CNButton::`vftable';
        sub_69C780(v27);
        sub_69C7B0(v103, *(v25 - 2), *(v25 - 1), *v25, v25[1], 0, 0);
        v28 = v104;
        goto LABEL_45;
      }
    }
    v28 = nullptr;
LABEL_45:
    v31 = v101;
    *v101 = (int)v28;
    v74 = *v31;
    v105 = -1;
    sub_69A840(v74);
    *(uint32_t *)(*v101 + 68) = this;
    sub_69A5F0(*v100, v100[1]);
    v32 = v101;
    *(uint8_t *)(*v101 + 16) = 1;
    v25 += 4;
    v24 = (int)(v100 + 2) < (int)&dword_725DF0;
    v101 = v32 + 1;
    v100 += 2;
  }
  while ( v24 );
  v77 = 0;
  v78 = 1;
  v79[0] = 3;
  v79[1] = 5;
  v79[2] = 2;
  v79[3] = 4;
  v79[4] = 6;
  v79[5] = 7;
  v79[6] = 9;
  v79[7] = 11;
  v80 = 8;
  v81 = 10;
  v82 = 12;
  v83 = 13;
  v84 = 15;
  v85 = 17;
  v86 = 14;
  v87 = 16;
  v88 = 18;
  v89 = 19;
  v90 = 21;
  v91 = 23;
  v92 = 20;
  v93 = 22;
  v94 = 24;
  v95 = 25;
  v96 = 27;
  v97 = 29;
  v98 = 26;
  v99 = 28;
  v100 = &unk_725DA0;
  v33 = v79;
  v103 = (void *)(this + 7444);
  v101 = (int *)(this + 7420);
  do
  {
    v34 = operator new(0x84u);
    v104 = v34;
    v105 = 19;
    if ( v34 != nullptr )
    {
      Block = *(void **)(this + 60);
      sub_426BD0(v34);
      v35 = v104;
      LOBYTE(v105) = 20;
      *(uint32_t *)v104 = &nengine::CNButton::`vftable';
      sub_69C780(v35);
      sub_69C7B0(Block, *(v33 - 2), *(v33 - 1), *v33, v33[1], 0, 0);
      v36 = v104;
    }
    else
    {
      v36 = nullptr;
    }
    *v101 = (int)v36;
    v105 = -1;
    sub_69A840(v36);
    *(uint32_t *)(*v101 + 68) = this;
    sub_69A5F0(*v100, v100[1]);
    v37 = v33[2];
    *(uint8_t *)(*v101 + 16) = 1;
    v38 = sub_418DD0(v37);
    v39 = v33[3];
    *((uint32_t *)v103 - 1) = v38;
    v40 = sub_418DD0(v39);
    v41 = (char *)v103;
    v42 = v101;
    *(uint32_t *)v103 = v40;
    v33 += 6;
    v24 = (int)(v100 + 2) < (int)&unk_725DC8;
    v101 = v42 + 1;
    v100 += 2;
    v103 = v41 + 8;
  }
  while ( v24 );
  v43 = operator new(0x84u);
  v103 = v43;
  v105 = 21;
  if ( v43 != nullptr )
  {
    Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
    sub_426BD0(v43);
    LOBYTE(v105) = 22;
    *v43 = &nengine::CNButton::`vftable';
    sub_69C780(v43);
    sub_69C7B0(Block, 175, 176, 177, -1, 0, 0);
  }
  else
  {
    v43 = nullptr;
  }
  v105 = -1;
  *(uint32_t *)(this + 7404) = v43;
  sub_69A840(v43);
  sub_69A5F0(0, 0);
  *(uint8_t *)(*(uint32_t *)(this + 7404) + 16) = 0;
  v44 = operator new(0x84u);
  v103 = v44;
  v105 = 23;
  if ( v44 != nullptr )
  {
    Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
    sub_426BD0(v44);
    LOBYTE(v105) = 24;
    *v44 = &nengine::CNButton::`vftable';
    sub_69C780(v44);
    sub_69C7B0(Block, 178, 179, 180, -1, 0, 0);
  }
  else
  {
    v44 = nullptr;
  }
  v105 = -1;
  *(uint32_t *)(this + 7408) = v44;
  sub_69A840(v44);
  sub_69A5F0(0, 0);
  *(uint8_t *)(*(uint32_t *)(this + 7408) + 16) = 0;
  v45 = operator new(0x70u);
  v46 = v45;
  Block = v45;
  v105 = 25;
  if ( v45 != nullptr )
  {
    sub_426BD0(v45);
    LOBYTE(v105) = 26;
    *v46 = &nengine::CNRadioButton::`vftable';
    sub_69CE10(v46);
    sub_69CF50(0);
  }
  else
  {
    v46 = nullptr;
  }
  v105 = -1;
  *(uint32_t *)(this + 9916) = v46;
  sub_69A840(v46);
  v103 = &dword_725C50;
  do
  {
    v100 = *(uint32_t **)v103;
    v47 = operator new(0x88u);
    v48 = v47;
    v104 = v47;
    v105 = 27;
    if ( v47 != nullptr )
    {
      Block = *(void **)(this + 60);
      sub_426BD0(v47);
      LOBYTE(v105) = 28;
      *v48 = &nengine::CNButton::`vftable';
      sub_69C780(v48);
      LOBYTE(v105) = 29;
      *v48 = &nengine::CNCheckBox::`vftable';
      sub_69CF80(v48);
      sub_69CFB0(
        Block,
        2 * (uint32_t)v100 + 52,
        2 * (uint32_t)v100 + 52,
        2 * (uint32_t)v100 + 53,
        2 * (uint32_t)v100 + 52,
        0,
        0);
      v49 = v48;
    }
    else
    {
      v49 = nullptr;
    }
    v50 = v100;
    *(uint32_t *)(this + 4 * (uint32_t)v100 + 9920) = v49;
    v105 = -1;
    sub_69A840(v49);
    sub_69A5F0(dword_725C70[2 * (uint32_t)v50], dword_725C74[2 * (uint32_t)v50]);
    *(uint8_t *)(*(uint32_t *)(this + 4 * (uint32_t)v50 + 9920) + 16) = 0;
    v51 = (char *)v103 + 4;
    v24 = (int)((char *)v103 + 4) < (int)dword_725C70;
    *(uint32_t *)(*(uint32_t *)(this + 4 * (uint32_t)v50 + 9920) + 68) = this;
    v103 = v51;
  }
  while ( v24 );
  v52 = operator new(0x84u);
  v53 = v52;
  v103 = v52;
  v105 = 30;
  if ( v52 != nullptr )
  {
    Block = *(void **)(this + 60);
    sub_426BD0(v52);
    LOBYTE(v105) = 31;
    *v53 = &nengine::CNButton::`vftable';
    sub_69C780(v53);
    sub_69C7B0(Block, 77, 77, 79, -1, 0, 0);
    v54 = v53;
  }
  else
  {
    v54 = nullptr;
  }
  v105 = -1;
  *(uint32_t *)(this + 9896) = v54;
  sub_69A840(v54);
  sub_69A5F0(582, 210);
  *(uint8_t *)(*(uint32_t *)(this + 9896) + 16) = 0;
  *(uint32_t *)(*(uint32_t *)(this + 9896) + 68) = this;
  *(uint32_t *)(this + 9900) = sub_418DD0(78);
  *(uint32_t *)(this + 9904) = sub_418DD0(80);
  *(uint32_t *)(this + 9908) = sub_418DD0(14);
  *(uint32_t *)(this + 9912) = sub_418DD0(15);
  v55 = operator new(0x68u);
  Block = v55;
  v105 = 32;
  if ( v55 != nullptr )
    v56 = sub_426BD0(v55);
  else
    v56 = 0;
  *(uint32_t *)(this + 10112) = v56;
  *(uint32_t *)(v56 + 68) = this;
  v75 = *(uint32_t *)(this + 10112);
  v105 = -1;
  sub_69A840(v75);
  sub_4FB180("Etc/NewCashShop.etc", this + 508);
  sub_560360(this);
  v57 = *(uint32_t *)(this + 512);
  if ( v57 != 0 && (v103 = (void *)((*(uint32_t *)(this + 516) - v57) / 84)) != nullptr )
  {
    v58 = *(uint32_t *)(this + 512);
    if ( v58 != 0 )
      v59 = (*(uint32_t *)(this + 516) - v58) / 84;
    else
      v59 = 0;
    *(uint32_t *)(this + 492) = (v59 - 1) / 6u;
  }
  else
  {
    *(uint8_t *)(*(uint32_t *)(this + 7420) + 17) = 0;
  }
  v60 = *(uint32_t *)(this + 528);
  if ( v60 != 0 && (v103 = (void *)((*(uint32_t *)(this + 532) - v60) / 84)) != nullptr )
  {
    v61 = *(uint32_t *)(this + 528);
    if ( v61 != 0 )
      v62 = (*(uint32_t *)(this + 532) - v61) / 84;
    else
      v62 = 0;
    *(uint32_t *)(this + 496) = (v62 - 1) / 6u;
  }
  else
  {
    *(uint8_t *)(*(uint32_t *)(this + 7424) + 17) = 0;
  }
  v63 = *(uint32_t *)(this + 544);
  if ( v63 != 0 && (v103 = (void *)((*(uint32_t *)(this + 548) - v63) / 84)) != nullptr )
  {
    v64 = *(uint32_t *)(this + 544);
    if ( v64 != 0 )
      v65 = (*(uint32_t *)(this + 548) - v64) / 84;
    else
      v65 = 0;
    *(uint32_t *)(this + 500) = (v65 - 1) / 6u;
  }
  else
  {
    *(uint8_t *)(*(uint32_t *)(this + 7428) + 17) = 0;
  }
  v66 = *(uint32_t *)(this + 560);
  if ( v66 != 0 && (v103 = (void *)((*(uint32_t *)(this + 564) - v66) / 84)) != nullptr )
  {
    v67 = *(uint32_t *)(this + 560);
    if ( v67 != 0 )
      v68 = (*(uint32_t *)(this + 564) - v67) / 84;
    else
      v68 = 0;
    *(uint32_t *)(this + 504) = (v68 - 1) / 6u;
  }
  else
  {
    *(uint8_t *)(*(uint32_t *)(this + 7432) + 17) = 0;
  }
  sub_55F810(this);
  sub_55FB40(this);
  sub_55FC80(this);
  Block = operator new(0x934u);
  v105 = 33;
  if ( Block != nullptr )
    v69 = sub_55F4D0(this, *(uint32_t *)(this + 4));
  else
    v69 = 0;
  *(uint32_t *)(this + 8) = v69;
  v76 = *(uint32_t *)(v69 + 12);
  v105 = -1;
  sub_69A840(v76);
  *(uint8_t *)(this + 7513) = 0;
  *(uint8_t *)(this + 7514) = 0;
  sub_698F90(0, 0);
  *(uint8_t *)(this + 7540) = 0;
  *(uint8_t *)(this + 7568) = 0;
  *(uint8_t *)(this + 7584) = 0;
  sub_560610(0);
  result = *(void **)(this + 44);
  if ( result != (void *)2 )
  {
    if ( result == nullptr )
      sub_5604F0(0);
    *(uint32_t *)(this + 44) = 2;
    sub_5600A0(this);
    return sub_432EA0("SELECT_CHARACTER", -1, 0, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x561E10 sub_561E10 —— 商城窗口刷新汇总（55D0F0/55E050/5607D0/55C6E0/55C860/699000）
// ------------------------------------------------------------
int /*thiscall*/ sub_561E10(int this)
{
  int result; // eax

  result = *(uint32_t *)(this + 52);
  if ( *(uint8_t *)(result + 16) != 0 )
  {
    *(uint32_t *)(this + 340) = sub_55D0F0((uint32_t *)this, (int *)(this + 344));
    if ( *(uint8_t *)(this + 7584) == 0 )
    {
      sub_55E050((uint32_t *)this);
      sub_5607D0((int *)this);
      sub_55C6E0((uint32_t *)this);
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8) + 4))(*(uint32_t *)(this + 8));
      if ( *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 8) + 12) + 16) == 0
        && *(uint8_t *)(*(uint32_t *)(this + 7404) + 16) == 0 )
      {
        sub_55C860(this);
      }
    }
    result = sub_699000(this + 7500);
    if ( result > 5000 )
    {
      result = *(uint32_t *)(this + 7488);
      *(uint8_t *)(result + 17) = 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x561EA0 sub_561EA0 —— 设置窗数据（38 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_561EA0(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 33) = 0;
  *(this + 34) = 2;
  *(this + 35) = -1;
  *(this + 36) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x561F10 sub_561F10 —— 设置清理（68 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_561F10(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  uint32_t *v4; // esi
  int i; // ebx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  uint32_t *v7; // esi
  int j; // ebx
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  uint32_t *v10; // esi
  int k; // ebx
  uint32_t *v12; // esi
  int m; // ebx
  int (/*thiscall*/ ***v14)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 9) = 0;
  v4 = this + 10;
  for ( i = 6; i != 0; --i )
  {
    if ( *v4 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v4)(*v4, 1);
    *v4++ = 0;
  }
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 16);
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  *(this + 16) = 0;
  v7 = this + 17;
  for ( j = 5; j != 0; --j )
  {
    if ( *v7 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v7)(*v7, 1);
    *v7++ = 0;
  }
  v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 22);
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  *(this + 22) = 0;
  v10 = this + 23;
  for ( k = 3; k != 0; --k )
  {
    if ( *v10 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v10)(*v10, 1);
    *v10++ = 0;
  }
  v12 = this + 26;
  for ( m = 2; m != 0; --m )
  {
    if ( *v12 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v12)(*v12, 1);
    *v12++ = 0;
  }
  v14 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 28);
  if ( v14 != nullptr )
    result = (**v14)(v14, 1);
  *(this + 28) = 0;
  return result;
}



// ============================================================
// 【分区 14】设置窗 CNRDOptionWindow（0x561FF0-0x562DA0）
// vmtC 打开（POP_UP 事件）、vmt8 Update（251 行：48B740/48B7C0 滑条 +
// 48F5A0/48F500/48FCA0/48FC30 视频/音频项）、vmt0 构造；
// 分辨率/刷新率切换在 0x5621D0/0x5621F0（65D990/65D8F0）。
// ============================================================
// ------------------------------------------------------------
// 0x561FF0 sub_561FF0 —— 设置窗定位（69A5F0 + 48B740/69CE50）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_561FF0(uint32_t *this, uint32_t *a2)
{
  uint32_t *result; // eax
  int v4; // eax
  int v5; // eax

  result = (uint32_t *)*(this + 34);
  if ( result != a2 )
  {
    *(uint8_t *)(*(this + 9) + 16) = a2 == nullptr;
    result = (uint32_t *)*(this + 16);
    *((uint8_t *)result + 16) = a2 == (uint32_t *)1;
    if ( a2 != nullptr )
    {
      if ( a2 == (uint32_t *)1 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 19, 27);
        sub_69A5F0((uint32_t *)*(this + 2), 200, 27);
        v4 = sub_48B740(7);
        sub_69CE50(v4);
        v5 = sub_48B740(8);
        result = (uint32_t *)sub_69CE50(v5);
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 12, 17);
      result = sub_69A5F0((uint32_t *)*(this + 2), 243, 122);
    }
    *(this + 34) = a2;
    *(this + 35) = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5620A0 CNRDOptionWindow__vmt10 —— CNRDOptionWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDOptionWindow__vmt10()
{
  dword_9B8880 = 0;
}



// ------------------------------------------------------------
// 0x5620B0 sub_5620B0 —— 设置滑条初始化（41C590/42B510）
// ------------------------------------------------------------
int /*thiscall*/ sub_5620B0(int *this, int a2)
{
  int v3; // eax
  int result; // eax

  if ( a2 == 3 )
  {
    v3 = *(this + 14);
    goto LABEL_3;
  }
  if ( a2 == 4 )
  {
    if ( dword_99FEC0 != 0 )
    {
      *(uint8_t *)(*(this + 14) + 17) = 1;
      goto LABEL_4;
    }
    v3 = *(this + 14);
LABEL_3:
    *(uint8_t *)(v3 + 17) = 1;
LABEL_4:
    *(uint8_t *)(*(this + 15) + 17) = 0;
    goto LABEL_5;
  }
  *(uint8_t *)(*(this + 14) + 17) = (uint8_t)sub_41C590(dword_8F7A24) == 1;
  *(uint8_t *)(*(this + 15) + 17) = 1;
  if ( a2 == 1 )
  {
    result = sub_41C590(dword_8F7A24);
    if ( (uint8_t)result == 1 )
    {
      *(uint8_t *)(*(this + 12) + 17) = 0;
    }
    else
    {
      result = *(this + 12);
      *(uint8_t *)(result + 17) = 1;
    }
    *(uint8_t *)(*(this + 13) + 17) = 1;
    return result;
  }
LABEL_5:
  *(uint8_t *)(*(this + 12) + 17) = 0;
  result = *(this + 13);
  *(uint8_t *)(result + 17) = 0;
  if ( a2 == 6 )
  {
    *(uint8_t *)(*(this + 14) + 17) = (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 724))(dword_8F7C04) == 1
                                 || !sub_42B510(*(uint32_t **)(dword_8F7A24 + 40));
    result = *(this + 15);
    *(uint8_t *)(result + 17) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5621D0 sub_5621D0 —— 分辨率切换（65D990）
// ------------------------------------------------------------
int /*cdecl*/ sub_5621D0(int a1)
{
  int v1; // eax

  v1 = a1;
  if ( a1 == 50 )
    v1 = 0;
  dword_79530C = v1;
  return sub_65D990(v1);
}



// ------------------------------------------------------------
// 0x5621F0 sub_5621F0 —— 刷新率切换（65D8F0）
// ------------------------------------------------------------
int /*cdecl*/ sub_5621F0(int a1)
{
  int v1; // eax

  v1 = a1;
  if ( a1 == 50 )
    v1 = 0;
  dword_795310 = v1;
  return sub_65D8F0(v1);
}



// ------------------------------------------------------------
// 0x562210 sub_562210 —— 设置项应用（CLICK_BUTTON2 + 48B740/69CE50/432EA0 + 41C590/423200/423380 + 41D520/46ED90 + 48F5A0/48F500/48FCA0/48FC30/41C860，98 行）
// ------------------------------------------------------------
void */*thiscall*/ sub_562210(uint32_t *this, void *a2)
{
  void *result; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax

  result = a2;
  if ( *(uint8_t *)(*(this + (uint32_t)a2 + 10) + 17) != 0 )
  {
    if ( a2 != nullptr )
    {
      if ( a2 == (void *)1 )
      {
        if ( *(this + 34) != 1 )
        {
          *(uint8_t *)(*(this + 9) + 16) = 0;
          *(uint8_t *)(*(this + 16) + 16) = 1;
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 19, 27);
          sub_69A5F0((uint32_t *)*(this + 2), 200, 27);
          v4 = sub_48B740(7);
          sub_69CE50(v4);
          v5 = sub_48B740(8);
          sub_69CE50(v5);
          *(this + 34) = 1;
          *(this + 35) = -1;
        }
        return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
      if ( a2 == (void *)2 )
      {
        if ( dword_8F7C04 == 0 || (uint8_t)sub_41C590(dword_8F7A24) != 0 )
          return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        sub_423200(dword_8F7B08, 7);
        sub_423380(dword_8F7B08);
        goto LABEL_26;
      }
      if ( a2 == (void *)3 )
      {
        if ( dword_8F7C04 != 0 )
        {
          sub_41D520(dword_8F7A24);
          goto LABEL_26;
        }
        return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
      if ( a2 == (void *)4 )
      {
        switch ( *(uint32_t *)(dword_8F7A24 + 12) )
        {
          case 1:
            if ( (uint8_t)sub_41C590(dword_8F7A24) != 1 )
              goto LABEL_26;
            sub_46ED90(*(int **)(dword_8F7A24 + 36));
            sub_41D520(dword_8F7A24);
            (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
            break;
          case 3:
            sub_423200(dword_8F7B08, 45);
            sub_423380(dword_8F7B08);
            (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
            break;
          case 4:
            if ( sub_48F5A0() == -1 )
              goto LABEL_26;
            v6 = sub_48F5A0();
            sub_48F500(v6, 254);
            (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
            break;
          case 6:
            if ( sub_48FCA0() != -1 )
            {
              v7 = sub_48FCA0();
              sub_48FC30(v7, 255);
            }
            goto LABEL_26;
          default:
            goto LABEL_26;
        }
        return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
      if ( a2 != (void *)5 )
        return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      sub_41C860(dword_8F7A24);
    }
LABEL_26:
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x562430 CNRDOptionWindow__vmtC —— CNRDOptionWindow__vmtC 打开槽：POP_UP 事件（561FF0/5620B0/432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDOptionWindow__vmtC(int *this, int a2, uint32_t *a3)
{
  sub_561FF0(this, a3);
  sub_5620B0(this, *(uint32_t *)(dword_8F7A24 + 12));
  dword_9B8880 = (int)this;
  *(this + 36) = 0;
  sub_432EA0("POP_UP", -1, 0, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x562480 CNRDOptionWindow__vmt0 —— CNRDOptionWindow__vmt0 构造（164 行：554930/418DD0/48B740/4049C0/488670/43BCB0）
// ------------------------------------------------------------
int /*thiscall*/ sub_562480(int this, int a2)
{
  int v2; // edi
  int v4; // ebx
  int v5; // edi
  int result; // eax
  int v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // eax
  int v16; // edi
  uint32_t *v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // edi
  uint32_t *v21; // eax
  int v22; // eax
  uint32_t *v23; // ebx
  int v24; // ecx
  int v25; // [esp+Ch] [ebp-8h]
  int v26; // [esp+10h] [ebp-4h]
  int v27; // [esp+10h] [ebp-4h]
  int v28; // [esp+1Ch] [ebp+8h]

  v2 = a2;
  sub_554930(a2);
  if ( a2 == *(uint32_t *)(this + 36) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    result = sub_418DD0(*(uint32_t **)(this + 132), 0x12u);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(
               result,
               v4 + 28,
               v5 - 14,
               dword_79C0B0);
    return result;
  }
  if ( a2 == *(uint32_t *)(this + 64) )
  {
    v7 = *(uint32_t *)(a2 + 20);
    v8 = *(uint32_t *)(a2 + 24);
    v26 = v7;
    v28 = v8;
    v9 = sub_418DD0(*(uint32_t **)(this + 132), 0x21u);
    if ( v9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, v7 + 71, v8 - 14, dword_79C0B0);
    v10 = sub_418DD0(*(uint32_t **)(this + 132), 0x15u);
    if ( v10 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, v7 + 15, v8 + 32, dword_79C0B0);
    v11 = 0;
    while ( 1 )
    {
      if ( v11 != 0 )
      {
        switch ( v11 )
        {
          case 1:
            v12 = sub_48B740((const CHAR *)dword_8F8544, 2);
            break;
          case 2:
            goto LABEL_20;
          case 3:
            v12 = sub_48B740((const CHAR *)dword_8F8544, 3);
            break;
          case 4:
            v12 = sub_48B740((const CHAR *)dword_8F8544, 4);
            break;
          default:
            goto LABEL_23;
        }
      }
      else
      {
        v12 = sub_48B740((const CHAR *)dword_8F8544, 1);
      }
      if ( v12 != 0 )
      {
LABEL_20:
        v13 = *(uint32_t *)(this + 4 * v11 + 68);
        v14 = *(uint32_t *)(v13 + 24);
        v25 = *(uint32_t *)(v13 + 20);
        v15 = sub_418DD0(*(uint32_t **)(this + 132), 0x16u);
        if ( v15 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v15 + 152))(v15, v25 + 2, v14 - 3, dword_79C0B0);
        v7 = v26;
      }
LABEL_23:
      if ( ++v11 >= 5 )
      {
        v16 = (uint64_t)sub_4049C0(0.0, 130.0, dword_79530C - 50, 50);
        v17 = (uint32_t *)dword_79C0B0;
        *(uint32_t *)(dword_79C0B0 + 48) = 0;
        v17[13] = 0;
        v17[14] = v16 + v7 + 84;
        v17[15] = 480;
        v18 = sub_418DD0(*(uint32_t **)(this + 132), 0x14u);
        if ( v18 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v18 + 152))(v18, v7 + 77, v28 + 169, dword_79C0B0);
        sub_488670((uint32_t *)dword_79C0B0);
        v19 = sub_418DD0(*(uint32_t **)(this + 132), 0x17u);
        if ( v19 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v19 + 152))(
            v19,
            v16 + v7 + 79,
            v28 + 166,
            dword_79C0B0);
        v20 = (uint64_t)sub_4049C0(0.0, 130.0, dword_795310 - 50, 50);
        v21 = (uint32_t *)dword_79C0B0;
        *(uint32_t *)(dword_79C0B0 + 48) = 0;
        v21[13] = 0;
        v21[14] = v20 + v7 + 84;
        v21[15] = 480;
        v22 = sub_418DD0(*(uint32_t **)(this + 132), 0x14u);
        if ( v22 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v22 + 152))(v22, v7 + 77, v28 + 202, dword_79C0B0);
        sub_488670((uint32_t *)dword_79C0B0);
        result = sub_418DD0(*(uint32_t **)(this + 132), 0x17u);
        if ( result != 0 )
          return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(
                   result,
                   v20 + v7 + 79,
                   v28 + 199,
                   dword_79C0B0);
        return result;
      }
    }
  }
  result = 0;
  v27 = 0;
  v23 = (uint32_t *)(this + 40);
  do
  {
    if ( v2 == *v23 && *(uint32_t *)(this + 144) == result && (uint8_t)sub_43BCB0(*v23) == 0 )
    {
      v24 = *(uint32_t *)(*v23 + 112);
      if ( v24 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v24 + 152))(
          v24,
          *(uint32_t *)(*v23 + 20),
          *(uint32_t *)(*v23 + 24),
          dword_79C0B0);
        v2 = a2;
      }
    }
    result = v27 + 1;
    ++v23;
    ++v27;
  }
  while ( v27 < 6 );
  return result;
}


// ------------------------------------------------------------
// 0x562790 sub_562790 —— 设置滑条绘制（415660/69A5F0/432EA0/562210——CLICK_BUTTON2/MOUSE_OVER）
// ------------------------------------------------------------
char /*thiscall*/ sub_562790(int this)
{
  int v1; // eax
  bool v3; // sf
  int v4; // eax
  char v5; // cl
  int v6; // eax
  int v7; // eax
  char v8; // cl

  LOBYTE(v1) = dword_79C0A0;
  if ( *(uint32_t *)(dword_79C0A0 + 32) == 0 )
    return v1;
  v1 = *(uint32_t *)(this + 136);
  if ( v1 == 1 )
  {
    if ( sub_415660(8, &unk_9B8888) != 0 || (LOBYTE(v1) = sub_415660(13, &unk_9B8887), (uint8_t)v1 != 0) )
    {
      if ( *(uint32_t *)(this + 136) != 0 )
      {
        *(uint8_t *)(*(uint32_t *)(this + 36) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(this + 64) + 16) = 0;
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 24))(this, 12, 17);
        sub_69A5F0(*(uint32_t **)(this + 8), 243, 122);
        *(uint32_t *)(this + 136) = 0;
        *(uint32_t *)(this + 140) = -1;
      }
      LOBYTE(v1) = (uint8_t)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
    return v1;
  }
  if ( v1 != 0 )
    return v1;
  if ( sub_415660(38, &unk_9B8886) != 0 )
  {
    v3 = --*(uint32_t *)(this + 144) < 0;
    if ( v3 )
      *(uint32_t *)(this + 144) = 5;
    do
    {
      while ( 1 )
      {
        v4 = *(uint32_t *)(this + 144);
        v5 = *(uint8_t *)(*(uint32_t *)(this + 4 * v4 + 40) + 17);
        if ( v5 != 0 )
          break;
        *(uint32_t *)(this + 144) = v4 - 1;
      }
    }
    while ( v5 != 1 );
LABEL_15:
    LOBYTE(v1) = (uint8_t)sub_432EA0("MOUSE_OVER", -1, 0, 0);
    return v1;
  }
  if ( sub_415660(40, &unk_9B8885) != 0 )
  {
    v6 = *(uint32_t *)(this + 144) + 1;
    v3 = *(uint32_t *)(this + 144) - 5 < 0;
    *(uint32_t *)(this + 144) = v6;
    if ( v3 == __OFSUB__(v6, 6) )
      *(uint32_t *)(this + 144) = 0;
    do
    {
      while ( 1 )
      {
        v7 = *(uint32_t *)(this + 144);
        v8 = *(uint8_t *)(*(uint32_t *)(this + 4 * v7 + 40) + 17);
        if ( v8 != 0 )
          break;
        *(uint32_t *)(this + 144) = v7 + 1;
      }
    }
    while ( v8 != 1 );
    goto LABEL_15;
  }
  LOBYTE(v1) = sub_415660(13, &unk_9B8884);
  if ( (uint8_t)v1 != 0 )
    LOBYTE(v1) = (uint8_t)sub_562210((uint32_t *)this, *(void **)(this + 144));
  return v1;
}



// ------------------------------------------------------------
// 0x562930 CNRDOptionWindow__vmt8 —— CNRDOptionWindow__vmt8 Update（251 行：69A650/562790/562210 + 48B740/48B7C0/432EA0 + 69A4D0/4049C0/69A5F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_562930(int *this)
{
  int *v1; // ebx
  int result; // eax
  int v3; // edx
  int v4; // esi
  int *i; // edi
  int v6; // edx
  int v7; // esi
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // esi
  uint32_t *v12; // edi
  int v13; // eax
  int v14; // esi
  uint32_t *v15; // edi
  int v16; // eax
  int v17; // edi
  int *v18; // esi
  int v19; // eax
  uint64_t v20; // rax
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int v24; // edi
  int v25; // [esp-4h] [ebp-18h]
  int v26; // [esp-4h] [ebp-18h]
  int v27; // [esp-4h] [ebp-18h]
  int v28; // [esp-4h] [ebp-18h]
  int v30; // [esp+10h] [ebp-4h]

  v1 = this;
  sub_69A650(*(this + 2));
  sub_562790(v1);
  result = v1[34];
  v30 = -1;
  if ( result == 0 )
  {
    v3 = dword_79BE34;
    v4 = 0;
    for ( i = v1 + 10; ; ++i )
    {
      if ( *(uint8_t *)(*i + 17) != 0 && v3 == *(uint32_t *)(*i + 12) )
      {
        sub_562210(v4);
        v3 = dword_79BE34;
      }
      result = *i;
      if ( *(uint8_t *)(*i + 17) != 0 )
      {
        v1 = this;
        if ( dword_79BE3C == *(uint32_t *)(result + 12)
          || v3 == *(uint32_t *)(result + 12)
          || dword_79BE38 == *(uint32_t *)(result + 12) )
        {
          break;
        }
      }
      if ( ++v4 >= 6 )
      {
        v1[35] = -1;
        return -1;
      }
    }
    v30 = v4;
LABEL_13:
    if ( v30 == -1 )
    {
      v1[35] = -1;
      return result;
    }
    goto LABEL_14;
  }
  if ( result != 1 )
  {
    v1[35] = -1;
    return result;
  }
  v6 = dword_79BE34;
  v7 = 0;
  while ( 1 )
  {
    v8 = v1[v7 + 17];
    if ( *(uint8_t *)(v8 + 17) != 0 && v6 == *(uint32_t *)(v8 + 12) )
    {
      if ( v7 != 0 )
      {
        switch ( v7 )
        {
          case 1:
            v26 = 1 - sub_48B740(2);
            sub_48B7C0(2, v26);
            break;
          case 2:
LABEL_89:
            break;
          case 3:
            v27 = 1 - sub_48B740(3);
            sub_48B7C0(3, v27);
            break;
          case 4:
            v28 = 1 - sub_48B740(4);
            sub_48B7C0(4, v28);
            break;
          default:
            goto LABEL_89;
        }
      }
      else
      {
        v25 = 1 - sub_48B740(1);
        sub_48B7C0(1, v25);
      }
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      v6 = dword_79BE34;
    }
    v9 = v1[v7 + 17];
    if ( *(uint8_t *)(v9 + 17) != 0 )
    {
      if ( dword_79BE3C == *(uint32_t *)(v9 + 12) )
        break;
      v10 = *(uint32_t *)(v9 + 12);
      if ( v6 == v10 || dword_79BE38 == v10 )
        break;
    }
    if ( ++v7 >= 5 )
      goto LABEL_38;
  }
  v30 = v7 + 6;
LABEL_38:
  v11 = 0;
  v12 = v1 + 23;
  while ( 1 )
  {
    if ( *(uint8_t *)(*v12 + 17) != 0 && v6 == *(uint32_t *)(*v12 + 12) )
    {
      sub_48B7C0(7, v11);
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      v6 = dword_79BE34;
    }
    v13 = *v12;
    if ( *(uint8_t *)(*v12 + 17) != 0 )
    {
      v1 = this;
      if ( dword_79BE3C == *(uint32_t *)(v13 + 12) || v6 == *(uint32_t *)(v13 + 12) || dword_79BE38 == *(uint32_t *)(v13 + 12) )
        break;
    }
    ++v11;
    ++v12;
    if ( v11 >= 3 )
      goto LABEL_49;
  }
  v30 = v11 + 11;
LABEL_49:
  v14 = 0;
  v15 = v1 + 30;
  while ( 1 )
  {
    if ( *(uint8_t *)(*v15 + 17) != 0 && v6 == *(uint32_t *)(*v15 + 12) )
    {
      sub_48B7C0(8, v14);
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      v6 = dword_79BE34;
    }
    v16 = *v15;
    if ( *(uint8_t *)(*v15 + 17) != 0 )
    {
      v1 = this;
      if ( dword_79BE3C == *(uint32_t *)(v16 + 12) || v6 == *(uint32_t *)(v16 + 12) || dword_79BE38 == *(uint32_t *)(v16 + 12) )
        break;
    }
    ++v14;
    ++v15;
    if ( v14 >= 3 )
      goto LABEL_60;
  }
  v30 = v14 + 11;
LABEL_60:
  v17 = 0;
  v18 = v1 + 26;
  while ( 1 )
  {
    if ( sub_69A4D0(*v18) != 0 )
    {
      v19 = pt.x - *(uint32_t *)(v1[2] + 20);
      if ( v19 >= 84 )
      {
        if ( v19 < 214 )
          v20 = (uint64_t)sub_4049C0(50.0, 100.0, v19 - 84, 130);
        else
          LODWORD(v20) = 100;
      }
      else
      {
        LODWORD(v20) = 50;
      }
      sub_48B7C0((v17 != 0) + 9, v20);
    }
    v21 = *v18;
    v22 = dword_79BE34;
    if ( *(uint8_t *)(*v18 + 17) != 0 )
    {
      v1 = this;
      if ( dword_79BE3C == *(uint32_t *)(v21 + 12)
        || dword_79BE34 == *(uint32_t *)(v21 + 12)
        || dword_79BE38 == *(uint32_t *)(v21 + 12) )
      {
        break;
      }
    }
    ++v17;
    ++v18;
    if ( v17 >= 2 )
      goto LABEL_75;
  }
  v30 = v17 + 14;
LABEL_75:
  v23 = v1[28];
  if ( *(uint8_t *)(v23 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v23 + 12) )
  {
    if ( v1[34] != 0 )
    {
      *(uint8_t *)(v1[9] + 16) = 1;
      *(uint8_t *)(v1[16] + 16) = 0;
      (*(void (/*thiscall*/ **)(int *, int, int))(*v1 + 24))(v1, 12, 17);
      sub_69A5F0((uint32_t *)v1[2], 243, 122);
      v1[34] = 0;
      v1[35] = -1;
    }
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v22 = dword_79BE34;
  }
  result = v1[28];
  if ( *(uint8_t *)(result + 17) == 0 )
    goto LABEL_13;
  v24 = *(uint32_t *)(result + 12);
  if ( dword_79BE3C != v24 && v22 != v24 && dword_79BE38 != v24 )
    goto LABEL_13;
  v30 = 16;
LABEL_14:
  if ( v30 != v1[35] )
    result = (int)sub_432EA0("MOUSE_OVER", -1, 0, 0);
  v1[35] = v30;
  return result;
}


// ============================================================
// 【分区 15】修理/买卖确认窗（0x562DA0-0x564600）
// 修理窗绘制在 0x562DA0（250 行）；CNRDItemBuyConfirmWindow（vmtC/vmt14、
// 5634F0 购买执行）、CNRDItemSellConfirmWindow（vmtC/vmt14）、
// CNRDItemRepairConfirmWindow（vmtC/vmt14）。
// ============================================================
// ------------------------------------------------------------
// 0x562DA0 sub_562DA0 —— 修理窗绘制（250 行：426BD0/69A840/43C410/69A5F0 + 69CE10/69CF50/69C780/69CF80/69CFB0/69C7B0）
// ------------------------------------------------------------
int /*thiscall*/ sub_562DA0(int this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // edi
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  uint32_t *v14; // eax
  uint32_t *v15; // eax
  uint32_t *v16; // eax
  int i; // ebx
  uint8_t *v18; // eax
  uint8_t *v19; // eax
  uint32_t *v20; // edi
  int j; // ebx
  uint8_t *v22; // eax
  uint8_t *v23; // eax
  uint8_t *v24; // eax
  uint32_t *v25; // edi
  int v26; // ebx
  uint8_t *v27; // eax
  uint32_t *v28; // edi
  uint8_t *v29; // eax
  uint32_t *v30; // edi
  int v31; // ebx
  uint8_t *v32; // eax
  uint32_t *v33; // edi
  uint32_t *v34; // edi
  int k; // ebx
  uint8_t *v36; // eax
  uint8_t *v37; // eax
  uint8_t *v38; // eax
  uint32_t *v39; // edi
  int v40; // ebx
  void *Block; // [esp+10h] [ebp-14h]
  void *Blocka; // [esp+10h] [ebp-14h]
  uint32_t *v44; // [esp+14h] [ebp-10h]
  uint32_t *v45; // [esp+14h] [ebp-10h]

  *(uint32_t *)(this + 132) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 72);
  v2 = operator new(0x68u);
  if ( v2 != nullptr )
    v3 = sub_426BD0(v2);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 36) = v3;
  *((uint32_t *)v3 + 17) = this;
  sub_69A840(*(uint32_t *)(this + 36));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(this + 132), 0, 13, 8, 0, 0, 0);
  else
    v5 = nullptr;
  v6 = (uint32_t *)(this + 40);
  *(uint32_t *)(this + 40) = v5;
  v7 = operator new(0x84u);
  if ( v7 != nullptr )
    v8 = sub_43C410(v7, *(uint32_t *)(this + 132), 1, 14, 9, 1, 0, 0);
  else
    v8 = nullptr;
  *(uint32_t *)(this + 44) = v8;
  v9 = operator new(0x84u);
  if ( v9 != nullptr )
    v10 = sub_43C410(v9, *(uint32_t *)(this + 132), 2, 15, 10, 5, 0, 0);
  else
    v10 = nullptr;
  *(uint32_t *)(this + 48) = v10;
  v11 = operator new(0x84u);
  if ( v11 != nullptr )
    v12 = sub_43C410(v11, *(uint32_t *)(this + 132), 34, 35, 36, 37, 0, 0);
  else
    v12 = nullptr;
  *(uint32_t *)(this + 52) = v12;
  v13 = operator new(0x84u);
  if ( v13 != nullptr )
    v14 = sub_43C410(v13, *(uint32_t *)(this + 132), 3, 16, 11, 6, 0, 0);
  else
    v14 = nullptr;
  *(uint32_t *)(this + 56) = v14;
  v15 = operator new(0x84u);
  if ( v15 != nullptr )
    v16 = sub_43C410(v15, *(uint32_t *)(this + 132), 4, 17, 12, 7, 0, 0);
  else
    v16 = nullptr;
  *(uint32_t *)(this + 60) = v16;
  for ( i = 27; i < 219; i += 32 )
  {
    sub_69A5F0((uint32_t *)*v6, 19, i);
    *(uint32_t *)(*v6 + 68) = this;
    sub_69A840(*v6++);
  }
  v18 = operator new(0x68u);
  if ( v18 != nullptr )
    v19 = sub_426BD0(v18);
  else
    v19 = nullptr;
  *(uint32_t *)(this + 64) = v19;
  *((uint32_t *)v19 + 17) = this;
  sub_69A840(*(uint32_t *)(this + 64));
  v20 = (uint32_t *)(this + 68);
  for ( j = 5; j != 0; --j )
  {
    v22 = operator new(0x68u);
    if ( v22 != nullptr )
      v23 = sub_426BD0(v22);
    else
      v23 = nullptr;
    *v20 = v23;
    *((uint32_t *)v23 + 7) = 19;
    *((uint32_t *)v23 + 8) = 19;
    sub_69A840(*v20++);
  }
  sub_69A5F0(*(uint32_t **)(this + 68), 203, 35);
  sub_69A5F0(*(uint32_t **)(this + 72), 203, 68);
  sub_69A5F0(*(uint32_t **)(this + 76), 203, 101);
  sub_69A5F0(*(uint32_t **)(this + 80), 203, 233);
  sub_69A5F0(*(uint32_t **)(this + 84), 203, 266);
  v24 = operator new(0x70u);
  v25 = v24;
  if ( v24 != nullptr )
  {
    sub_426BD0(v24);
    *v25 = &nengine::CNRadioButton::`vftable';
    sub_69CE10(v25);
    sub_69CF50(0);
  }
  else
  {
    v25 = nullptr;
  }
  *(uint32_t *)(this + 88) = v25;
  sub_69A840(v25);
  v26 = 25;
  v44 = (uint32_t *)(this + 92);
  do
  {
    v27 = operator new(0x88u);
    v28 = v27;
    if ( v27 != nullptr )
    {
      Block = *(void **)(this + 132);
      sub_426BD0(v27);
      *v28 = &nengine::CNButton::`vftable';
      sub_69C780(v28);
      *v28 = &nengine::CNCheckBox::`vftable';
      sub_69CF80(v28);
      sub_69CFB0(Block, v26 - 1, v26, v26 + 1, -1, 0, 0);
    }
    else
    {
      v28 = nullptr;
    }
    *v44 = v28;
    sub_69A840(v28);
    v26 += 3;
    ++v44;
  }
  while ( v26 < 34 );
  sub_69A5F0(*(uint32_t **)(this + 92), 119, 132);
  sub_69A5F0(*(uint32_t **)(this + 96), 155, 132);
  sub_69A5F0(*(uint32_t **)(this + 100), 192, 132);
  v29 = operator new(0x70u);
  v30 = v29;
  if ( v29 != nullptr )
  {
    sub_426BD0(v29);
    *v30 = &nengine::CNRadioButton::`vftable';
    sub_69CE10(v30);
    sub_69CF50(0);
  }
  else
  {
    v30 = nullptr;
  }
  *(uint32_t *)(this + 116) = v30;
  sub_69A840(v30);
  v31 = 25;
  v45 = (uint32_t *)(this + 120);
  do
  {
    v32 = operator new(0x88u);
    v33 = v32;
    if ( v32 != nullptr )
    {
      Blocka = *(void **)(this + 132);
      sub_426BD0(v32);
      *v33 = &nengine::CNButton::`vftable';
      sub_69C780(v33);
      *v33 = &nengine::CNCheckBox::`vftable';
      sub_69CF80(v33);
      sub_69CFB0(Blocka, v31 - 1, v31, v31 + 1, -1, 0, 0);
    }
    else
    {
      v33 = nullptr;
    }
    *v45 = v33;
    sub_69A840(v33);
    v31 += 3;
    ++v45;
  }
  while ( v31 < 34 );
  sub_69A5F0(*(uint32_t **)(this + 120), 119, 299);
  sub_69A5F0(*(uint32_t **)(this + 124), 155, 299);
  sub_69A5F0(*(uint32_t **)(this + 128), 192, 299);
  v34 = (uint32_t *)(this + 104);
  for ( k = 2; k != 0; --k )
  {
    v36 = operator new(0x68u);
    if ( v36 != nullptr )
      v37 = sub_426BD0(v36);
    else
      v37 = nullptr;
    *v34 = v37;
    *((uint32_t *)v37 + 7) = 150;
    *((uint32_t *)v37 + 8) = 25;
    sub_69A840(*v34++);
  }
  sub_69A5F0(*(uint32_t **)(this + 104), 74, 161);
  sub_69A5F0(*(uint32_t **)(this + 108), 74, 194);
  v38 = operator new(0x84u);
  v39 = v38;
  if ( v38 != nullptr )
  {
    v40 = *(uint32_t *)(this + 132);
    sub_426BD0(v38);
    *v39 = &nengine::CNButton::`vftable';
    sub_69C780(v39);
    sub_69C7B0(v40, 19, 19, 19, -1, 0, 0);
  }
  else
  {
    v39 = nullptr;
  }
  *(uint32_t *)(this + 112) = v39;
  sub_69A5F0(v39, 64, 336);
  return sub_69A840(*(uint32_t *)(this + 112));
}


// ------------------------------------------------------------
// 0x5633F0 sub_5633F0 —— 修理窗数据（16 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5633F0(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x563410 sub_563410 —— 确认参数（423200/423290/423380）
// ------------------------------------------------------------
int /*cdecl*/ sub_563410(int a1, int a2)
{
  sub_423200(dword_8F7B08, 21);
  sub_423290(dword_8F7B08, (int)&a1, 2);
  a1 = a2;
  sub_423290(dword_8F7B08, (int)&a1, 4);
  return sub_423380(dword_8F7B08);
}



// ------------------------------------------------------------
// 0x563460 sub_563460 —— 确认参数 2（423200/423290/423380）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_563460(uint32_t *a1)
{
  uint32_t *result; // eax
  uint32_t *v2; // edi
  int v3; // esi
  int v4; // ebx
  int v5; // esi
  int v6; // [esp+4h] [ebp-4h] BYREF

  result = a1;
  v2 = (uint32_t *)a1[1];
  if ( v2 != (uint32_t *)a1[2] )
  {
    do
    {
      v3 = *v2;
      v4 = v2[1];
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*v2 + 20))(*v2, 1) == 0 )
        v4 = dword_8F84B0;
      v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 16))(v3) + 4);
      sub_423200(dword_8F7B08, 21);
      v6 = v5;
      sub_423290(dword_8F7B08, (int)&v6, 2);
      v6 = v4;
      sub_423290(dword_8F7B08, (int)&v6, 4);
      sub_423380(dword_8F7B08);
      result = (uint32_t *)a1[2];
      v2 += 2;
    }
    while ( v2 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x5634F0 sub_5634F0 —— 购买执行（48FCA0/48FD70 + 422E70/4F36B0/44E8D0/484FA0，142 行）
// ------------------------------------------------------------
char /*cdecl*/ sub_5634F0(int a1, char a2)
{
  int v2; // ebx
  int *v3; // edi
  uint32_t *v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // esi
  int v10; // eax
  int v11; // esi
  int v12; // esi
  const char *v13; // eax
  int v15; // edi
  int v16; // ebx
  int v17; // esi
  int v18; // eax
  const char *p_Block; // eax
  const char *v20; // edx
  unsigned int v21; // eax
  char *v22; // edi
  char v23; // cl
  const char *v24; // ecx
  unsigned int v25; // eax
  const char *v26; // esi
  char *v27; // edi
  char v28; // cl
  double v29; // [esp+0h] [ebp-150h]
  int v30; // [esp+14h] [ebp-13Ch]
  int v31; // [esp+18h] [ebp-138h]
  int v32; // [esp+1Ch] [ebp-134h]
  int i; // [esp+20h] [ebp-130h]
  char Buffer[127]; // [esp+24h] [ebp-12Ch] BYREF
  char v35; // [esp+A3h] [ebp-ADh] BYREF
  char v36[128]; // [esp+A4h] [ebp-ACh] BYREF
  uint8_t v37[4]; // [esp+124h] [ebp-2Ch] BYREF
  void *Block; // [esp+128h] [ebp-28h] BYREF
  unsigned int v39; // [esp+13Ch] [ebp-14h]
  int v40; // [esp+140h] [ebp-10h]
  int v41; // [esp+14Ch] [ebp-4h]
  int v42; // [esp+158h] [ebp+8h]
  uint32_t *v43; // [esp+158h] [ebp+8h]

  v40 = dword_796E50;
  v2 = 0;
  v3 = *(int **)(a1 + 4);
  v30 = 0;
  v31 = 0;
  v32 = 0;
  for ( i = 0; v3 != *(int **)(a1 + 8); v3 += 2 )
  {
    v4 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)*v3 + 16))(*v3);
    v5 = v3[1];
    v2 += v5 * v4[9];
    v30 += v5 * v4[11];
    v31 += v5 * v4[10];
    v32 += v5 * v4[13];
    v6 = __RTDynamicCast(*v3, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
    if ( v6 == 0 || *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 172))(v6) >= 8 )
      i += v4[14];
  }
  v7 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) - v2;
  v8 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8))
     - v30;
  v9 = dword_8F7C0C - v31;
  v42 = 0;
  if ( dword_99FF08 != 0 )
  {
    v43 = (uint32_t *)dword_99FF08;
    v10 = sub_48FCA0();
    v42 = sub_48FD70(v43, v10) - v32;
  }
  if ( v7 < 0 || v8 < 0 || v9 < 0 || v42 < 0 )
  {
    if ( a2 != 0 )
    {
      strcpy(v36, (const char *)sub_422E70(952));
      if ( v7 >= 0 )
        v15 = 0;
      else
        v15 = -v7;
      if ( v8 >= 0 )
        v16 = 0;
      else
        v16 = -v8;
      if ( v9 >= 0 )
        v17 = 0;
      else
        v17 = -v9;
      if ( v42 >= 0 )
        v18 = 0;
      else
        v18 = -v42;
      sub_4F36B0(v37, v15, v16, v17, v18);
      p_Block = (const char *)Block;
      v41 = 0;
      if ( v39 < 0x10 )
        p_Block = (const char *)&Block;
      v20 = p_Block;
      v21 = strlen(p_Block) + 1;
      v22 = &v35;
      do
        v23 = *++v22;
      while ( v23 != 0 );
      qmemcpy(v22, v20, v21);
      v24 = (const char *)sub_422E70(953);
      v25 = strlen(v24) + 1;
      v26 = v24;
      v27 = &v35;
      do
        v28 = *++v27;
      while ( v28 != 0 );
      qmemcpy(v27, v26, v25);
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v36, 0);
      if ( v39 >= 0x10 )
        j__free(Block);
    }
  }
  else
  {
    if ( i <= 0 )
      return 1;
    v11 = *((uint32_t *)dword_8F852C + 1);
    if ( i <= sub_484FA0() - v11 )
      return 1;
    if ( a2 != 0 )
    {
      v12 = *((uint32_t *)dword_8F852C + 1);
      v29 = (double)(i + v12 - sub_484FA0()) * 0.001;
      v13 = (const char *)sub_422E70(954);
      sprintf(Buffer, v13, v29);
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);
    }
  }
  return 0;
}


// ------------------------------------------------------------
// 0x563820 CNRDItemBuyConfirmWindow__vmt14 —— CNRDItemBuyConfirmWindow__vmt14 确认动作（5634F0 购买 + 563460 参数 + 44ABE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemBuyConfirmWindow__vmt14(uint32_t **this)
{
  uint32_t *v2; // edi

  v2 = this + 11;
  if ( sub_5634F0((int)(this + 11), 1) != 0 )
    sub_563460(v2);
  if ( byte_9B8889 != 0 )
    sub_44ABE0(*(this + 4), 4);
  ((void (/*thiscall*/ *)(uint32_t **))(*this)[8])(this);
  return 1;
}



// ------------------------------------------------------------
// 0x563860 sub_563860 —— 修理窗关闭清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_563860(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 15, 16, 17, 15, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  sub_69A840(v3);
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);
  else
    v5 = nullptr;
  *(this + 10) = v5;
  return sub_69A840(v5);
}



// ------------------------------------------------------------
// 0x563940 sub_563940 —— CNRDItemBuyConfirmWindow__vmtC 文案装配（44E340 + 422E70/4F36B0 + 69C340 系，161 行）
// ------------------------------------------------------------
void /*userpurge*/ sub_563940(int *a1@<ecx>, int a2@<edi>, int a3, const char *a4)
{
  int v5; // esi
  uint32_t *v6; // ecx
  uint32_t *v7; // eax
  char *v8; // edi
  char v9; // cl
  int *v10; // esi
  int v11; // edi
  const char *v12; // eax
  int v13; // edx
  char *v14; // eax
  unsigned int v15; // eax
  char *v16; // edi
  char v17; // cl
  char *v18; // esi
  unsigned int v19; // eax
  char *v20; // edi
  char v21; // cl
  int v22; // edx
  char *v23; // edi
  char *v24; // esi
  char v25; // cl
  int v26; // eax
  const char *p_Block; // eax
  const char *v28; // edx
  unsigned int v29; // eax
  char *v30; // edi
  char v31; // cl
  char *v32; // esi
  unsigned int v33; // eax
  char *v34; // edi
  char v35; // cl
  int v36; // esi
  uint32_t *v37; // ecx
  int v38; // esi
  int v39; // edi
  const char *v40; // [esp-8h] [ebp-344h]
  int v41; // [esp+8h] [ebp-334h] BYREF
  const char *v42; // [esp+Ch] [ebp-330h]
  char Buffer[255]; // [esp+10h] [ebp-32Ch] BYREF
  char v44; // [esp+10Fh] [ebp-22Dh] BYREF
  uint8_t v45[512]; // [esp+110h] [ebp-22Ch] BYREF
  uint8_t v46[4]; // [esp+310h] [ebp-2Ch] BYREF
  void *Block; // [esp+314h] [ebp-28h] BYREF
  unsigned int v48; // [esp+328h] [ebp-14h]
  int v49; // [esp+32Ch] [ebp-10h]
  int v50; // [esp+338h] [ebp-4h]
  uint32_t *v51; // [esp+344h] [ebp+8h]

  v49 = dword_796E50;
  if ( a3 != 0 && a4 != nullptr )
  {
    v41 = a3;
    v42 = a4;
    sub_44E340(&v41);
    a1[15] += (uint32_t)a4 * *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 16))(a3, a2) + 36);
    a1[16] += (uint32_t)a4 * *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 16))(a3) + 44);
    a1[17] += (uint32_t)a4 * *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 16))(a3) + 40);
    v5 = (uint32_t)a4 * *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 16))(a3) + 52) + a1[18];
    memset(v45, 0, sizeof(v45));
    v6 = (uint32_t *)a1[13];
    v7 = (uint32_t *)a1[12];
    a1[18] = v5;
    v51 = v7;
    if ( v7 != v6 )
    {
      while ( 1 )
      {
        if ( v7 != (uint32_t *)a1[12] )
        {
          v8 = &v44;
          do
            v9 = *++v8;
          while ( v9 != 0 );
          strcpy(v8, ", ");
        }
        v10 = (int *)*v7;
        v11 = v7[1];
        v12 = (const char *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v7 + 108))(*v7);
        v13 = *v10;
        v42 = v12;
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v13 + 20))(v10, 2) != 0 && v11 == 1 )
        {
          sprintf(Buffer, "%s", v42);
        }
        else
        {
          v40 = v42;
          v14 = sub_422E70(949);
          sprintf(Buffer, v14, v40, v11);
        }
        v15 = strlen(Buffer) + 1;
        v16 = &v44;
        do
          v17 = *++v16;
        while ( v17 != 0 );
        qmemcpy(v16, Buffer, v15);
        v51 += 2;
        if ( v51 == (uint32_t *)a1[13] )
          break;
        v7 = v51;
      }
    }
    v18 = sub_422E70(950);
    v19 = strlen(v18) + 1;
    v20 = &v44;
    do
      v21 = *++v20;
    while ( v21 != 0 );
    v22 = a1[17];
    qmemcpy(v20, v18, 4 * (v19 >> 2));
    v24 = &v18[4 * (v19 >> 2)];
    v23 = &v20[4 * (v19 >> 2)];
    v25 = v19;
    v26 = a1[16];
    qmemcpy(v23, v24, v25 & 3);
    sub_4F36B0((int)v46, a1[15], v26, v22, a1[18]);
    p_Block = (const char *)Block;
    v50 = 0;
    if ( v48 < 0x10 )
      p_Block = (const char *)&Block;
    v28 = p_Block;
    v29 = strlen(p_Block) + 1;
    v30 = &v44;
    do
      v31 = *++v30;
    while ( v31 != 0 );
    qmemcpy(v30, v28, v29);
    v32 = sub_422E70(951);
    v33 = strlen(v32) + 1;
    v34 = &v44;
    do
      v35 = *++v34;
    while ( v35 != 0 );
    qmemcpy(v34, v32, v33);
    sub_69C340((uint8_t *)a1[3], -1);
    sub_69C440(a1[3], -1);
    sub_69C360((uint8_t *)a1[3], (int)v45, 0);
    v36 = *a1;
    sub_69C500(a1[3]);
    (*(void (/*thiscall*/ **)(int *, int))(v36 + 24))(a1, 14);
    v37 = (uint32_t *)a1[2];
    v38 = 640 - v37[7];
    if ( ((pt.x - 55) & ((pt.x - 55 <= 0) - 1)) < v38 )
      v38 = (pt.x - 55) & ((pt.x - 55 <= 0) - 1);
    v39 = 480 - v37[8];
    if ( (pt.y - v37[8] + 31 <= 0 ? 0 : pt.y - v37[8] + 31) < v39 )
      v39 = pt.y - v37[8] + 31 <= 0 ? 0 : pt.y - v37[8] + 31;
    sub_69A5F0(v37, v38, v39);
    sub_69A5F0((uint32_t *)a1[9], v38 + 29, *(uint32_t *)(a1[2] + 32) + v39 - 43);
    sub_69A5F0((uint32_t *)a1[10], v38 + 98, *(uint32_t *)(a1[2] + 32) + v39 - 43);
    if ( v48 >= 0x10 )
      j__free(Block);
  }
}


// ------------------------------------------------------------
// 0x563CB0 CNRDItemBuyConfirmWindow__vmtC —— CNRDItemBuyConfirmWindow__vmtC 打开转发（563940）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemBuyConfirmWindow__vmtC(int this, int a2, const char *a3)
{
  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  if ( a2 != 0 )
    sub_563940((int *)this, 0, a2, a3);
  return 1;
}



// ------------------------------------------------------------
// 0x563D00 CNRDItemSellConfirmWindow__vmtC —— CNRDItemSellConfirmWindow__vmtC 文案装配（422E70 + 69C340/69C440/69C360/69C500/69A5F0）
// ------------------------------------------------------------
char /*userpurge*/ CNRDItemSellConfirmWindow__vmtC@<al>(int *a1@<ecx>, int a2@<ebx>, int a3@<edi>, int a4, int a5)
{
  int v7; // edi
  int v8; // ebx
  char *v9; // eax
  char *v10; // eax
  int v11; // edi
  int v12; // eax
  uint32_t *v13; // ecx
  int v14; // ebx
  int v15; // [esp-8h] [ebp-90h]
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int v17; // [esp+84h] [ebp-4h]
  int v18; // [esp+90h] [ebp+8h]

  v17 = dword_796E50;
  a1[11] = a4;
  a1[12] = a5;
  if ( a4 == 0 )
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a4 + 20))(a4, 2) != 0 )
    a1[12] = 1;
  v7 = a1[12] * (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1[11] + 96))(a1[11], a3, a2);
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[11] + 108))(a1[11]);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[11] + 20))(a1[11], 2) != 0 )
  {
    v9 = sub_422E70(1110);
    sprintf(Buffer, v9, v8, v7);
  }
  else
  {
    v15 = a1[12];
    v10 = sub_422E70(1111);
    sprintf(Buffer, v10, v8, v15, v7);
  }
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(Buffer, 0);
  v11 = *a1;
  v12 = sub_69C500(a1[3]);
  (*(void (/*thiscall*/ **)(int *, int, int))(v11 + 24))(a1, 14, v12 + 5);
  v13 = (uint32_t *)a1[2];
  v18 = pt.x - 55 <= 0 ? 0 : pt.x - 55;
  if ( v18 >= 640 - v13[7] )
    v18 = 640 - v13[7];
  v14 = pt.y - v13[8] + 31 <= 0 ? 0 : pt.y - v13[8] + 31;
  if ( v14 >= 480 - v13[8] )
    v14 = 480 - v13[8];
  sub_69A5F0(v13, v18, v14);
  sub_69A5F0((uint32_t *)a1[9], v18 + 29, *(uint32_t *)(a1[2] + 32) + v14 - 43);
  sub_69A5F0((uint32_t *)a1[10], v18 + 98, *(uint32_t *)(a1[2] + 32) + v14 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x563E90 sub_563E90 —— 出售执行（422E70/44E8D0 + 423200/423290/423380，76 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_563E90(int a1, int a2, char *a3)
{
  int result; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edi
  char v7; // bl
  int v8; // esi
  int v9; // edi
  char *v10; // eax
  unsigned int v11; // eax
  int v12; // edi

  result = a2;
  if ( a2 > 0 )
  {
    v4 = *((uint32_t *)dword_8F852C + 2);
    v5 = 0;
    if ( v4 <= 0 )
      goto LABEL_7;
    while ( 1 )
    {
      v6 = a1;
      if ( *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v5) == a1 )
        break;
      if ( ++v5 >= v4 )
        goto LABEL_7;
    }
    v7 = 0;
    v8 = v5;
    if ( v5 == -1 )
    {
LABEL_7:
      v9 = dword_8F7C04;
      v8 = 0;
      while ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 792))(v9, v8) != a1 )
      {
        if ( ++v8 >= 18 )
          goto LABEL_12;
      }
      v7 = 3;
      if ( v8 == -1 )
      {
LABEL_12:
        v10 = sub_422E70(1112);
        return sub_44E8D0(a3, (void *)0x1B, (int)v10, 0);
      }
      v6 = a1;
    }
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 44))(v6);
    v12 = a2;
    if ( v11 >= a2 )
    {
      sub_423200(dword_8F7B08, 24);
      HIBYTE(a2) = v7;
      sub_423290(dword_8F7B08, (int)&a2 + 3, 1);
      a2 = v8;
      sub_423290(dword_8F7B08, (int)&a2, 2);
      a2 = v12;
      sub_423290(dword_8F7B08, (int)&a2, 2);
      return sub_423380(dword_8F7B08);
    }
    else
    {
      v10 = sub_422E70(1113);
      return sub_44E8D0(a3, (void *)0x1B, (int)v10, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x563FA0 CNRDItemSellConfirmWindow__vmt14 —— CNRDItemSellConfirmWindow__vmt14 确认动作（563E90 出售 + 44ABE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemSellConfirmWindow__vmt14(void *this)
{
  sub_563E90(*((uint32_t *)this + 11), *((uint32_t *)this + 12), *((char **)this + 4));
  if ( byte_9B888A != 0 )
    sub_44ABE0(*((uint32_t **)this + 4), 5);
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x563FE0 sub_563FE0 —— 出售窗关闭清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_563FE0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 18, 19, 20, 18, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  sub_69A840(v3);
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);
  else
    v5 = nullptr;
  *(this + 10) = v5;
  return sub_69A840(v5);
}



// ------------------------------------------------------------
// 0x5640C0 sub_5640C0 —— 14 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_5640C0(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5640D0 sub_5640D0 —— 修理费计算（41A5E0，79 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_5640D0(uint32_t *a1)
{
  int v1; // ecx
  int v2; // ebx
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // eax
  int v9; // ebx
  int v10; // esi
  int v11; // eax
  int v12; // edi
  int v13; // eax
  int i; // [esp+Ch] [ebp-Ch]
  int v16; // [esp+Ch] [ebp-Ch]
  int v17; // [esp+10h] [ebp-8h]
  int v18; // [esp+14h] [ebp-4h]

  v1 = dword_8F7C04;
  v2 = 0;
  v17 = 0;
  v18 = 0;
  for ( i = dword_8F7C04; ; v1 = i )
  {
    v3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v1 + 792))(v1, v2);
    v4 = v3;
    if ( v3 != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 188))(v3);
      v6 = sub_41A5E0(v5 + 32);
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 172))(v4);
      if ( v6 < sub_41A5E0(v7 + 18) )
      {
        ++v17;
        v18 += (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 180))(v4);
      }
    }
    if ( ++v2 >= 18 )
      break;
  }
  v8 = dword_8F852C;
  v9 = 0;
  v16 = *((uint32_t *)dword_8F852C + 2);
  if ( v16 > 0 )
  {
    while ( 1 )
    {
      if ( v9 < v8[2] )
      {
        v10 = *(uint32_t *)(v8[3] + 4 * v9);
        if ( v10 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 20))(v10, 2) != 0 )
        {
          v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 188))(v10);
          v12 = sub_41A5E0(v11 + 32);
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 172))(v10);
          if ( v12 < sub_41A5E0(v13 + 18) )
          {
            ++v17;
            v18 += (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 180))(v10);
          }
        }
      }
      if ( ++v9 >= v16 )
        break;
      v8 = dword_8F852C;
    }
  }
  if ( a1 != nullptr )
    *a1 = v17;
  return v18;
}



// ------------------------------------------------------------
// 0x5641E0 sub_5641E0 —— 修理执行（484ED0/422E70/44E8D0 + 423200/423290/423380，56 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_5641E0(int a1, char *a2)
{
  int v2; // ebx
  int v4; // esi
  char v5; // bl
  int v6; // edi
  char *v7; // eax

  v2 = a1;
  if ( a1 != 0 )
  {
    v4 = sub_484ED0(a1);
    if ( v4 == -1 )
    {
      v6 = dword_8F7C04;
      v4 = 0;
      while ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 792))(v6, v4) != v2 )
      {
        if ( ++v4 >= 18 )
          goto LABEL_11;
      }
      v5 = 3;
      if ( v4 != -1 )
        goto LABEL_5;
LABEL_11:
      v7 = sub_422E70(1106);
      return sub_44E8D0(a2, (void *)0x1B, (int)v7, 0);
    }
    else
    {
      v5 = 0;
LABEL_5:
      sub_423200(dword_8F7B08, 25);
      HIBYTE(a1) = v5;
      sub_423290(dword_8F7B08, (int)&a1 + 3, 1);
      a1 = v4;
      sub_423290(dword_8F7B08, (int)&a1, 2);
      return sub_423380(dword_8F7B08);
    }
  }
  else
  {
    sub_423200(dword_8F7B08, 25);
    HIBYTE(a1) = 0;
    sub_423290(dword_8F7B08, (int)&a1 + 3, 1);
    a1 = 0xFFFF;
    sub_423290(dword_8F7B08, (int)&a1, 2);
    return sub_423380(dword_8F7B08);
  }
}



// ------------------------------------------------------------
// 0x5642E0 CNRDItemRepairConfirmWindow__vmt14 —— CNRDItemRepairConfirmWindow__vmt14 确认动作（5641E0 修理 + 422E70/44E8D0/44ABE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemRepairConfirmWindow__vmt14(void *this)
{
  char *v2; // eax
  int v4; // [esp-4h] [ebp-4Ch]
  char Buffer[64]; // [esp+4h] [ebp-44h] BYREF
  int v6; // [esp+44h] [ebp-4h]

  v6 = dword_796E50;
  if ( *((uint32_t *)this + 12) <= (unsigned int)(*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) )
  {
    sub_5641E0(*((uint32_t *)this + 11), *((char **)this + 4));
  }
  else
  {
    v4 = *((uint32_t *)this + 12)
       - (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));
    v2 = sub_422E70(1107);
    sprintf(Buffer, v2, v4);
    sub_44E8D0(*((char **)this + 4), (void *)0x1B, (int)Buffer, 0);
  }
  if ( byte_9B888B != 0 )
    sub_44ABE0(*((uint32_t **)this + 4), 6);
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x564380 CNRDItemRepairConfirmWindow__vmtC —— CNRDItemRepairConfirmWindow__vmtC 文案装配（41A5E0/422E70/5640D0 修理费 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemRepairConfirmWindow__vmtC(int *this, int a2, int a3)
{
  int v3; // edi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  char *v12; // eax
  int v13; // edi
  int v14; // eax
  uint32_t *v15; // ecx
  int v16; // ebx
  int v17; // edi
  int v18; // [esp-8h] [ebp-94h]
  char Buffer[128]; // [esp+8h] [ebp-84h] BYREF
  int v20; // [esp+88h] [ebp-4h]

  v3 = a2;
  v20 = dword_796E50;
  if ( a2 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 20))(a2, 2) == 0 )
    return 0;
  *(this + 11) = v3;
  if ( v3 != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 188))(v3);
    v6 = sub_41A5E0(v5 + 32);
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 11) + 172))(*(this + 11));
    if ( v6 >= sub_41A5E0(v7 + 18) )
      return 0;
  }
  v9 = *(this + 11);
  if ( v9 != 0 )
  {
    v10 = *(this + 11);
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 180))(v10);
    v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 108))(v10, v11);
    v12 = sub_422E70(1104);
  }
  else
  {
    a2 = 0;
    *(this + 12) = sub_5640D0(&a2);
    v18 = a2;
    v12 = sub_422E70(1105);
  }
  sprintf(Buffer, v12, v18);
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(Buffer, 0);
  v13 = *this;
  v14 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(int *, int, int))(v13 + 24))(this, 14, v14 + 5);
  v15 = (uint32_t *)*(this + 2);
  v16 = pt.x - 55 <= 0 ? 0 : pt.x - 55;
  if ( v16 >= 640 - v15[7] )
    v16 = 640 - v15[7];
  v17 = 480 - v15[8];
  if ( (pt.y - v15[8] + 31 <= 0 ? 0 : pt.y - v15[8] + 31) < v17 )
    v17 = pt.y - v15[8] + 31 <= 0 ? 0 : pt.y - v15[8] + 31;
  sub_69A5F0(v15, v16, v17);
  sub_69A5F0((uint32_t *)*(this + 9), v16 + 29, *(uint32_t *)(*(this + 2) + 32) + v17 - 43);
  sub_69A5F0((uint32_t *)*(this + 10), v16 + 98, *(uint32_t *)(*(this + 2) + 32) + v17 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x564520 sub_564520 —— 修理窗关闭清理 2（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_564520(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  sub_69A840(v3);
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);
  else
    v5 = nullptr;
  *(this + 10) = v5;
  return sub_69A840(v5);
}



// ============================================================
// 【分区 16】道具商店窗 CNRDItemShopWindow（0x564600-0x5654D0）
// vmt8 Update（166 行：DISSOLVE_ITEM 分解事件 + 5515A0/484ED0）；
// vmtC 打开（44BBA0/69C400）；vmt1C 刷新（44F190/44F580/44F2E0 格子系）。
// ============================================================
// ------------------------------------------------------------
// 0x564600 sub_564600 —— 道具商店数据（69C690）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_564600(uint32_t *this, int a2)
{
  return (*(this + 4) != 2 ? 198 : 186) + 32 * ((a2 - 7 * sub_69C690(*(this + 14))) / 7u);
}



// ------------------------------------------------------------
// 0x564650 sub_564650 —— 道具商店数据 2（33 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_564650(uint32_t *this)
{
  *(this + 4) = 1;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 20) = -1;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 27) = 0;
  *(this + 45) = 0;
  *(this + 46) = 0;
  *(this + 47) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5646B0 CNRDItemShopWindow__vmtC —— CNRDItemShopWindow__vmtC 打开槽（44BBA0 显示 + 69C400）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemShopWindow__vmtC(uint32_t **this)
{
  sub_44BBA0(*(this + 2), 0, 0);
  sub_69C400(0);
  return 1;
}



// ------------------------------------------------------------
// 0x5646D0 sub_5646D0 —— 道具商店数据 3（12 行）
// ------------------------------------------------------------
bool /*thiscall*/ sub_5646D0(uint32_t *this)
{
  if ( *(this + 4) != 2 )
    return false;
  return pt.x >= 57 && pt.y >= 314 && pt.x < 293 && pt.y < 406;
}



// ------------------------------------------------------------
// 0x564710 sub_564710 —— 商店格子查询（69C690，37 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_564710(uint32_t *this)
{
  int v2; // esi
  int v3; // ebx
  signed int v4; // esi
  signed int v5; // ecx
  int v7; // [esp+Ch] [ebp-10h]
  LONG y; // [esp+10h] [ebp-Ch]
  LONG x; // [esp+14h] [ebp-8h]
  int v10; // [esp+18h] [ebp-4h]

  x = pt.x;
  y = pt.y;
  v10 = 0;
  v2 = 7 * (*(this + 4) != 2 ? 6 : 3);
  v7 = v2;
  v3 = 7 * sub_69C690(*(this + 14));
  if ( v2 <= 0 )
    return -1;
  while ( 1 )
  {
    v4 = 2 * (*(this + 4) == 2) + 56 + 32 * ((v3 - 7 * sub_69C690(*(this + 14))) % 7u);
    v5 = (*(this + 4) != 2 ? 198 : 186) + 32 * ((v3 - 7 * sub_69C690(*(this + 14))) / 7u);
    if ( x >= v4 && x < v4 + 28 && y >= v5 && y < v5 + 28 )
      break;
    ++v3;
    if ( ++v10 >= v7 )
      return -1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x564810 CNRDItemShopWindow__vmt10 —— CNRDItemShopWindow__vmt10 状态切换槽（44ABE0/44E850/540960/698F90/432EE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemShopWindow__vmt10(int this)
{
  uint32_t *v2; // ecx
  int v3; // eax
  uint32_t *v4; // ecx
  int v5; // eax
  char result; // al

  v2 = *(uint32_t **)(this + 8);
  v3 = v2[626];
  if ( v3 == 4 || v3 == 5 || v3 == 6 || v3 == 7 )
    sub_44ABE0(v2, 0);
  sub_44E850(*(uint32_t **)(this + 8), 19);
  sub_44E850(*(uint32_t **)(this + 8), 20);
  sub_44E850(*(uint32_t **)(this + 8), 22);
  if ( dword_9B88D0 != 0 && dword_795378 == 4 )
    sub_44E850(*(uint32_t **)(this + 8), 26);
  v4 = *(uint32_t **)(*(uint32_t *)(this + 8) + 116);
  v5 = v4[10];
  if ( v5 == 2 || v5 == 3 )
    sub_540960(v4);
  *(uint32_t *)(this + 108) = 0;
  *(uint8_t *)(this + 125) = 0;
  *(uint8_t *)(this + 126) = 0;
  sub_698F90(this + 112, 0, 0);
  result = *(uint8_t *)(*(uint32_t *)(this + 40) + 17);
  if ( result == 0 )
    return sub_432EE0(5);
  return result;
}



// ------------------------------------------------------------
// 0x5648C0 sub_5648C0 —— 商店文本（23 行）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_5648C0(int a1, int a2, int a3, uint32_t *a4, char a5)
{
  uint32_t *result; // eax

  result = operator new(0x18u);
  if ( result != nullptr )
  {
    *result = a1;
    result[2] = a3;
    result[1] = a2;
    result[3] = *a4;
    result[4] = a4[1];
    *((uint8_t *)result + 20) = a5;
    *((uint8_t *)result + 21) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x564900 CNRDItemShopWindow__vmt8 —— CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTTON2/DISSOLVE_ITEM 分解事件 + 69C690/69C400/432EA0 + 5515A0/69C340/69C360/69C500/69C3A0/69C6A0/69C680 + 44ABE0/44F400/564710/564600/44E8D0/44E850/484ED0/422E70/486E00）
// ------------------------------------------------------------
int /*thiscall*/ sub_564900(int this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // edi
  int i; // ebx
  int v6; // edi
  int v7; // eax
  uint64_t v8; // rax
  size_t v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // ebx
  const char *v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // ecx
  int v22; // edi
  unsigned int v23; // ebx
  int v24; // ecx
  unsigned int v25; // edi
  int v26; // ebx
  int v27; // eax
  int result; // eax
  int v29; // eax
  int v30; // eax
  float v31; // [esp+0h] [ebp-420h]
  int v32; // [esp+18h] [ebp-408h]
  int v33; // [esp+18h] [ebp-408h]
  char Destination[1024]; // [esp+1Ch] [ebp-404h] BYREF
  int v35; // [esp+41Ch] [ebp-4h]

  v2 = *(uint32_t *)(this + 40);
  v35 = dword_796E50;
  if ( *(uint8_t *)(v2 + 17) != 0 )
  {
    v3 = sub_69C690(v2);
    sub_69C400(v3);
    v4 = this + 28;
    for ( i = 2; i != 0; --i )
    {
      if ( *(uint8_t *)(*(uint32_t *)v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(*(uint32_t *)v4 + 12) )
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      v4 += 4;
    }
  }
  else
  {
    v32 = strlen(*(const char **)(this + 180));
    v6 = *(uint32_t *)(this + 188);
    v7 = sub_699000(this + 152);
    v31 = (float)v32;
    v8 = (uint64_t)sub_4049C0(0.0, v31, v7, v6);
    v9 = sub_5515A0(*(uint32_t *)(this + 180), v8);
    if ( *(uint32_t *)(this + 184) != v9 )
    {
      strncpy(Destination, *(const char **)(this + 180), v9);
      Destination[v9] = 0;
      sub_69C340(-1);
      sub_69C360(Destination, 0);
      v10 = sub_69C500(*(uint32_t *)(this + 24));
      v11 = sub_69C3A0(*(uint32_t *)(this + 24));
      v12 = v10 - v11 <= 0 ? 0 : v10 - v11;
      sub_69C400(v12);
      v13 = *(const char **)(this + 180);
      *(uint32_t *)(this + 184) = v9;
      if ( v9 == strlen(v13) )
      {
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 40) + 32))(*(uint32_t *)(this + 40), v12);
        v14 = sub_69C6A0(*(uint32_t **)(this + 40));
        sub_69C680(v14);
        *(uint8_t *)(*(uint32_t *)(this + 40) + 17) = 1;
        sub_432EE0(5);
      }
    }
  }
  v15 = *(uint32_t *)(this + 60);
  if ( *(uint8_t *)(v15 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v15 + 12) )
  {
    sub_44ABE0(5);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v16 = *(uint32_t *)(this + 64);
  if ( *(uint8_t *)(v16 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v16 + 12) )
  {
    sub_44ABE0(4);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v17 = *(uint32_t *)(this + 68);
  if ( *(uint8_t *)(v17 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v17 + 12) )
  {
    sub_44ABE0(6);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v18 = *(uint32_t *)(this + 72);
  if ( *(uint8_t *)(v18 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v18 + 12) )
  {
    sub_44F400(0, 1);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v19 = *(uint32_t *)(this + 76);
  if ( *(uint8_t *)(v19 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v19 + 12) )
  {
    sub_44ABE0(7);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v20 = *(uint32_t *)(*(uint32_t *)(this + 8) + 2504);
  if ( v20 != 1
    && v20 != 2
    && *(uint8_t *)((v21 = *(uint32_t *)(this + 4)) + 17) != 0
    && ((v22 = *(uint32_t *)(v21 + 12), dword_79BE3C == v22) || dword_79BE34 == v22 || dword_79BE38 == v22)
    && (v23 = sub_564710(this)) != -1
    && ((v24 = *(uint32_t *)(this + 96)) == 0 || v23 >= (*(uint32_t *)(this + 100) - v24) >> 2
      ? (v33 = 0)
      : (v33 = *(uint32_t *)(v24 + 4 * v23)),
        v25 = 2 * (*(uint32_t *)(this + 16) == 2) + 56 + 32 * ((v23 - 7 * sub_69C690(*(uint32_t *)(this + 56))) % 7),
        v26 = sub_564600(v23),
        v33 != 0) )
  {
    if ( dword_9B88D0 != v33 || dword_795378 != 4 )
    {
      v27 = sub_44E8D0(*(char **)(this + 8), (void *)0x1A, v33, 4);
      if ( v27 != 0 )
        (*(void (/*thiscall*/ **)(int, unsigned int, int, int, int))(*(uint32_t *)v27 + 48))(v27, v25, v26, 28, 28);
    }
  }
  else if ( dword_9B88D0 != 0 && dword_795378 == 4 )
  {
    sub_44E850(*(uint32_t **)(this + 8), 26);
  }
  result = *(uint32_t *)(this + 108);
  if ( result != 0 )
  {
    result = sub_699000(this + 112);
    if ( result >= 3000 )
    {
      v29 = sub_484ED0(*(uint32_t *)(this + 108));
      if ( v29 == -1 )
      {
        v30 = sub_422E70(417);
        result = sub_44E8D0(*(char **)(this + 8), (void *)0x1B, v30, 0);
        *(uint32_t *)(this + 108) = 0;
      }
      else
      {
        result = sub_486E00(v29);
        if ( (uint8_t)result != 0 )
        {
          *(uint32_t *)(this + 108) = 0;
          return (int)sub_432EA0("DISSOLVE_ITEM", -1, 0, 0);
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x564D30 CNRDItemShopWindow__vmt0 —— CNRDItemShopWindow__vmt0 构造（140 行：69C690/564710/4F2E40/699000/418DD0/491530/491630）
// ------------------------------------------------------------
char /*thiscall*/ sub_564D30(int *this, int a2)
{
  int v2; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // ebx
  int v7; // edi
  int **v8; // eax
  int *v9; // ebx
  int v10; // eax
  int v11; // ebx
  unsigned int v12; // edi
  int v13; // eax
  bool v14; // cc
  int v15; // edi
  int v16; // ebx
  int v17; // edi
  int v18; // eax
  int v19; // ecx
  int v20; // ecx
  int v21; // eax
  signed int v22; // edi
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v28; // [esp+4h] [ebp-14h]
  int *v29; // [esp+8h] [ebp-10h]
  int v30; // [esp+Ch] [ebp-Ch]
  int v31; // [esp+10h] [ebp-8h]
  int v32; // [esp+14h] [ebp-4h]

  LOBYTE(v2) = a2;
  if ( a2 == *(this + 1) )
  {
    v4 = *(this + 22);
    if ( v4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v4 + 152))(
        v4,
        *(uint32_t *)(a2 + 20) + 28,
        *(uint32_t *)(a2 + 24) + 25,
        dword_79C0B0);
    v5 = *(this + 24);
    v6 = 7 * (*(this + 4) != 2 ? 6 : 3);
    v28 = v6;
    if ( v5 != 0 )
      v31 = (*(this + 25) - v5) >> 2;
    else
      v31 = 0;
    v30 = 0;
    v7 = 7 * sub_69C690(*(this + 14));
    v32 = v7;
    if ( v6 > 0 )
    {
      do
      {
        if ( v7 >= v31 )
          break;
        v8 = (int **)(*(this + 24) + 4 * v7);
        if ( *v8 != nullptr )
        {
          v9 = *v8;
          v29 = *v8;
          v10 = sub_69C690(*(this + 14));
          v11 = *v9;
          v12 = 2 * (*(this + 4) == 2) + 56 + 32 * ((v7 - 7 * v10) % 7u);
          v13 = sub_69C690(*(this + 14));
          (*(void (/*thiscall*/ **)(int *, unsigned int, unsigned int, int, uint32_t))(v11 + 8))(
            v29,
            v12,
            (*(this + 4) != 2 ? 198 : 186) + 32 * ((v32 - 7 * v13) / 7u),
            1,
            0);
          v6 = v28;
          v7 = v32;
        }
        ++v7;
        v14 = ++v30 < v6;
        v32 = v7;
      }
      while ( v14 );
    }
    LOBYTE(v2) = *(uint8_t *)(a2 + 17);
    if ( (uint8_t)v2 != 0 )
    {
      v15 = *(uint32_t *)(a2 + 12);
      if ( dword_79BE3C == v15 || dword_79BE34 == v15 || (LOBYTE(v2) = dword_79BE38, dword_79BE38 == v15) )
      {
        v2 = sub_564710(this);
        v16 = v2;
        if ( v2 != -1 )
        {
          v17 = 2 * (*(this + 4) == 2) + 56 + 32 * ((v2 - 7 * sub_69C690(*(this + 14))) % 7u);
          v18 = sub_69C690(*(this + 14));
          LOBYTE(v2) = sub_4F2E40(v17, (*(this + 4) != 2 ? 198 : 186) + 32 * ((v16 - 7 * v18) / 7u));
        }
      }
    }
    if ( *(this + 4) == 2 )
    {
      v19 = (int)(this + 28);
      if ( *(this + 27) != 0 )
      {
        v20 = sub_699000(v19);
        v21 = 1374389535;
      }
      else
      {
        v20 = sub_699000(v19);
        v21 = 458129845;
      }
      v22 = ((int)((uint64_t)(v20 * (int64_t)v21) >> 32) >> 5)
          + ((unsigned int)((uint64_t)(v20 * (int64_t)v21) >> 32) >> 31);
      v23 = sub_418DD0(v22 % 3 + 15);
      if ( v23 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v23 + 152))(v23, 122, 342, dword_79C0B0);
      v24 = sub_418DD0(v22 % 3 + 12);
      if ( v24 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v24 + 152))(v24, 112, 375, dword_79C0B0);
      v2 = *(this + 27);
      if ( v2 != 0 )
      {
        v25 = sub_418DD0(v22 % 6 + 6);
        if ( v25 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v25 + 152))(v25, 63, 320, dword_79C0B0);
        sub_491530(2, 0);
        v26 = sub_418DD0(v22 % 2 + 4);
        if ( v26 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v26 + 152))(v26, 100, 316, dword_79C0B0);
        LOBYTE(v2) = sub_491630(2);
      }
    }
  }
  return v2;
}


// ------------------------------------------------------------
// 0x565050 CNRDItemShopWindow__vmt1C —— CNRDItemShopWindow__vmt1C 刷新槽（564710 + 44F190/5646D0/422E70/44E8D0/44A980/44F580/44F2E0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemShopWindow__vmt1C(int *this)
{
  int v2; // eax
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  char *v9; // eax
  char v10; // al
  unsigned int v11; // eax
  int v12; // edx

  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0 || dword_79BE34 != *(uint32_t *)(v2 + 12) )
    return 0;
  v4 = (uint32_t *)*(this + 2);
  v5 = v4[626];
  if ( v5 == 4 || v5 == 0 )
  {
    v11 = sub_564710(this);
    if ( v11 != -1 )
    {
      v12 = *(this + 24);
      if ( v12 != 0 && v11 < (*(this + 25) - v12) >> 2 && *(uint32_t *)(v12 + 4 * v11) != 0 )
      {
        sub_44F190(*(this + 2), v11, 1);
        return 1;
      }
    }
  }
  else if ( v5 == 2 )
  {
    v6 = v4[627];
    if ( v6 == 2 )
    {
      v7 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v4[629]);
      v8 = v7;
      if ( v7 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7) + 4) == v4[628] )
      {
        if ( sub_5646D0(this) )
        {
          v9 = sub_422E70(418);
          sub_44E8D0((char *)*(this + 2), (void *)0x1B, (int)v9, 0);
          return 1;
        }
        v10 = *(uint8_t *)(*(this + 15) + 17);
        goto LABEL_20;
      }
    }
    else if ( v6 == 3 || v6 == 4 )
    {
      v8 = sub_44A980(dword_8F852C, v4[629]);
      if ( v8 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 16))(v8) + 4) == v4[628] )
      {
        if ( sub_5646D0(this) )
        {
          sub_44F580(*(this + 2), v8, 1);
          return 1;
        }
        v10 = *(uint8_t *)(*(this + 15) + 17);
LABEL_20:
        if ( v10 != 0 )
        {
          sub_44F2E0(*(this + 2), v8, 1);
          return 1;
        }
        return 1;
      }
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5651C0 sub_5651C0 —— 商店文本辅助（69C730/69A5F0/69CB10）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5651C0(int this, uint32_t *a2)
{
  uint32_t *result; // eax

  result = a2;
  if ( a2 != *(uint32_t **)(this + 16) )
  {
    *(uint32_t *)(this + 16) = a2;
    if ( a2 != nullptr )
    {
      if ( a2 == (uint32_t *)1 )
      {
        sub_69C730(*(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 28), 0);
        sub_69A5F0(
          *(uint32_t **)(this + 60),
          *(uint32_t *)(*(uint32_t *)(this + 4) + 20) + 55,
          *(uint32_t *)(*(uint32_t *)(this + 4) + 24) + 333);
        sub_69A5F0(
          *(uint32_t **)(this + 64),
          *(uint32_t *)(*(uint32_t *)(this + 4) + 20) + 97,
          *(uint32_t *)(*(uint32_t *)(this + 4) + 24) + 333);
        *(uint8_t *)(*(uint32_t *)(this + 68) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(this + 72) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 0;
      }
      else if ( a2 == (uint32_t *)2 )
      {
        sub_69C730(*(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 36), 0);
        sub_69A5F0(
          *(uint32_t **)(this + 60),
          *(uint32_t *)(*(uint32_t *)(this + 4) + 20) + 107,
          *(uint32_t *)(*(uint32_t *)(this + 4) + 24) + 224);
        sub_69A5F0(
          *(uint32_t **)(this + 64),
          *(uint32_t *)(*(uint32_t *)(this + 4) + 20) + 149,
          *(uint32_t *)(*(uint32_t *)(this + 4) + 24) + 224);
        *(uint8_t *)(*(uint32_t *)(this + 68) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(this + 72) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 1;
      }
    }
    else
    {
      sub_69C730(*(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 32), 0);
      sub_69A5F0(
        *(uint32_t **)(this + 60),
        *(uint32_t *)(*(uint32_t *)(this + 4) + 20) + 99,
        *(uint32_t *)(*(uint32_t *)(this + 4) + 24) + 332);
      sub_69A5F0(
        *(uint32_t **)(this + 64),
        *(uint32_t *)(*(uint32_t *)(this + 4) + 20) + 141,
        *(uint32_t *)(*(uint32_t *)(this + 4) + 24) + 332);
      *(uint8_t *)(*(uint32_t *)(this + 68) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 72) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 0;
    }
    if ( *(uint32_t *)(this + 16) == 2 )
    {
      sub_69CB10(*(uint32_t *)(this + 20), 18, 19);
      sub_69A5F0(
        *(uint32_t **)(this + 56),
        *(uint32_t *)(*(uint32_t *)(this + 4) + 20) + 254,
        *(uint32_t *)(*(uint32_t *)(this + 4) + 24) + 120);
      return sub_69A5F0(
               *(uint32_t **)(this + 48),
               *(uint32_t *)(*(uint32_t *)(this + 56) + 20),
               *(uint32_t *)(*(uint32_t *)(this + 56) + 24) + 83);
    }
    else
    {
      sub_69CB10(*(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 32), 13, 8);
      sub_69A5F0(
        *(uint32_t **)(this + 56),
        *(uint32_t *)(*(uint32_t *)(this + 4) + 20) + 252,
        *(uint32_t *)(*(uint32_t *)(this + 4) + 24) + 132);
      return sub_69A5F0(
               *(uint32_t **)(this + 48),
               *(uint32_t *)(*(uint32_t *)(this + 56) + 20),
               *(uint32_t *)(*(uint32_t *)(this + 56) + 24) + 179);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5653D0 sub_5653D0 —— 商店格子（4CE8A0）
// ------------------------------------------------------------
int /*usercall*/ sub_5653D0@<eax>(int a1@<ecx>, int a2@<edi>, int a3@<esi>)
{
  int result; // eax
  unsigned int v4; // ebx
  int v5; // edi
  int v6; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // esi
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v17; // [esp+4h] [ebp-8h]
  int v18; // [esp+8h] [ebp-4h]

  result = sub_4CE8A0(*(uint32_t *)(a1 + 80));
  v4 = 0;
  v17 = result;
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    v5 = *(uint32_t *)(result + 104);
    if ( v5 != 0 )
    {
      v6 = *(uint32_t *)(v5 + 8);
      if ( v6 != 0 )
      {
        result = (*(uint32_t *)(v5 + 12) - v6) >> 2;
        v18 = result;
      }
      else
      {
        v18 = 0;
      }
      if ( v18 > 0 )
      {
        while ( 1 )
        {
          v7 = *(uint32_t *)(v5 + 8);
          if ( v7 != 0 && v4 < (*(uint32_t *)(v5 + 12) - v7) >> 2 )
            v8 = *(uint32_t *)(v7 + 4 * v4);
          else
            v8 = 0;
          v9 = __RTDynamicCast(v8, 0, &CNRDObject `RTTI Type Descriptor', &CNRDNpc `RTTI Type Descriptor', 0);
          v10 = v9;
          if ( v9 != 0 && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 340))(v9) == *(uint32_t *)(v17 + 8) )
            break;
          result = v18;
          if ( (int)++v4 >= v18 )
            return result;
        }
        v11 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v10 + 340))(v10, a3, a2);
        v12 = *(uint32_t *)(v11 + 180);
        v13 = v11 + 156;
        if ( v12 < 0x10 )
          v14 = v13 + 4;
        else
          v14 = *(uint32_t *)(v13 + 4);
        return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v10 + 212))(v10, v14, -1);
      }
    }
  }
  return result;
}



// ============================================================
// 【分区 17】道具商店辅助与商品橱窗（0x5654D0-0x567760）
// 商品页绘制在 0x5654D0（268 行）；文本打字机在 0x566110（WRITE_CHAR_LOOP）；
// CNRDItemProductWindow 商品橱窗（vmtC/vmt8/vmt1C/vmt0/vmt10）。
// ============================================================
// ------------------------------------------------------------
// 0x5654D0 sub_5654D0 —— 商品页绘制（268 行：43C250/43C330 + 69C440/69C420/69C3E0/69C4C0 + 69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630 + 69C5D0/69CD70/698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_5654D0(int *this)
{
  uint32_t *v1; // eax
  int v3; // edi
  uint8_t *v4; // eax
  uint8_t *v5; // eax
  int v6; // eax
  int v7; // ebx
  uint8_t *v8; // edi
  uint8_t *v9; // eax
  uint32_t *v10; // edi
  uint8_t *v11; // eax
  uint8_t *v12; // eax
  int v13; // ebx
  uint8_t *v14; // edi
  uint8_t *v15; // eax
  uint32_t *v16; // edi
  uint8_t *v17; // edi
  uint32_t *v18; // ebx
  uint32_t *v19; // ecx
  uint8_t *v20; // eax
  uint32_t *v21; // edi
  uint32_t *v22; // ecx
  uint8_t *v23; // eax
  uint32_t *v24; // edi
  uint32_t *v25; // ecx
  uint8_t *v26; // eax
  uint32_t *v27; // edi
  uint32_t *v28; // ecx
  uint8_t *v29; // eax
  uint32_t *v30; // edi
  uint32_t *v31; // ecx
  uint8_t *v32; // eax
  uint32_t *v33; // edi
  int v34; // ebx
  uint32_t *v35; // ecx
  void *Block; // [esp+10h] [ebp-1Ch]
  void *Blocka; // [esp+10h] [ebp-1Ch]
  void *Blockb; // [esp+10h] [ebp-1Ch]
  int v40; // [esp+14h] [ebp-18h]
  uint32_t *v41; // [esp+18h] [ebp-14h]
  uint32_t *v42; // [esp+18h] [ebp-14h]
  int v43; // [esp+18h] [ebp-14h]
  int v44; // [esp+1Ch] [ebp-10h]

  v1 = *(uint32_t **)(dword_99FCC8 + 20);
  v3 = v1[7];
  v40 = v3;
  v44 = v1[8];
  *(this + 5) = v1[9];
  v4 = operator new(0x6Cu);
  if ( v4 != nullptr )
    v5 = sub_43C250(v4, v3, 0);
  else
    v5 = nullptr;
  *(this + 1) = (int)v5;
  *((uint32_t *)v5 + 7) = *((uint32_t *)v5 + 7);
  *((uint32_t *)v5 + 8) = 353;
  *(uint32_t *)(*(this + 1) + 68) = this;
  if ( operator new(0x6Cu) != nullptr )
    v6 = sub_43C330(130, 2048);
  else
    v6 = 0;
  *(this + 6) = v6;
  sub_69C440(v6, -4265479);
  sub_69C420(*(this + 6), 2);
  sub_69C3E0(*(this + 6), 5);
  sub_69C4C0((uint32_t *)*(this + 6), dword_99FCCC);
  sub_69A5F0((uint32_t *)*(this + 6), 110, 31);
  sub_69A840((uint32_t *)*(this + 1), *(this + 6));
  v7 = 4;
  v41 = this + 7;
  do
  {
    v8 = operator new(0x84u);
    if ( v8 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v8);
      *(uint32_t *)v8 = &nengine::CNButton::`vftable';
      sub_69C780((int)v8);
      sub_69C7B0((int)v8, (int)Block, v7, v7, v7 + 1, v7, 0, 0);
    }
    else
    {
      v8 = nullptr;
    }
    *v41 = v8;
    v7 += 2;
    ++v41;
  }
  while ( v7 < 8 );
  v9 = operator new(0x88u);
  v10 = v9;
  if ( v9 != nullptr )
  {
    sub_426BD0(v9);
    *v10 = &nengine::CNSlider::`vftable';
    sub_69CA20((int)v10);
    sub_69CA50((int)v10, v44, 7, 8);
    *v10 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v10 = nullptr;
  }
  *(this + 9) = (int)v10;
  v11 = operator new(0x74u);
  if ( v11 != nullptr )
    v12 = sub_43C630(v11, *(this + 7), *(this + 8), *(this + 9));
  else
    v12 = nullptr;
  *(this + 10) = (int)v12;
  sub_69A5F0(v12, 249, 27);
  sub_69A840((uint32_t *)*(this + 1), *(this + 10));
  v13 = 4;
  v42 = this + 11;
  do
  {
    v14 = operator new(0x84u);
    if ( v14 != nullptr )
    {
      Blocka = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v14);
      *(uint32_t *)v14 = &nengine::CNButton::`vftable';
      sub_69C780((int)v14);
      sub_69C7B0((int)v14, (int)Blocka, v13, v13, v13 + 1, v13, 0, 0);
    }
    else
    {
      v14 = nullptr;
    }
    *v42 = v14;
    v13 += 2;
    ++v42;
  }
  while ( v13 < 8 );
  v15 = operator new(0x88u);
  v16 = v15;
  if ( v15 != nullptr )
  {
    sub_426BD0(v15);
    *v16 = &nengine::CNSlider::`vftable';
    sub_69CA20((int)v16);
    sub_69CA50((int)v16, v44, 13, 8);
    *v16 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v16 = nullptr;
  }
  *(this + 13) = (int)v16;
  v17 = operator new(0x74u);
  if ( v17 != nullptr )
  {
    v18 = (uint32_t *)*(this + 13);
    Blockb = (void *)*(this + 12);
    v43 = *(this + 11);
    sub_426BD0(v17);
    *(uint32_t *)v17 = &nengine::CNScroll::`vftable';
    sub_69C5D0(v17);
    *(uint32_t *)v17 = &nengine::CNVScroll::`vftable';
    sub_69C5D0(v17);
    sub_69CD70((int)v17, v43, (int)Blockb, v18);
    v19 = v17;
  }
  else
  {
    v19 = nullptr;
  }
  *(this + 14) = (int)v19;
  sub_69A5F0(v19, 252, 132);
  sub_69A840((uint32_t *)*(this + 1), *(this + 14));
  v20 = operator new(0x84u);
  v21 = v20;
  if ( v20 != nullptr )
  {
    sub_426BD0(v20);
    *v21 = &nengine::CNButton::`vftable';
    sub_69C780((int)v21);
    sub_69C7B0((int)v21, v44, 1, 2, 3, 14, 0, 0);
    v22 = v21;
  }
  else
  {
    v22 = nullptr;
  }
  *(this + 15) = (int)v22;
  sub_69A5F0(v22, 55, 333);
  sub_69A840((uint32_t *)*(this + 1), *(this + 15));
  v23 = operator new(0x84u);
  v24 = v23;
  if ( v23 != nullptr )
  {
    sub_426BD0(v23);
    *v24 = &nengine::CNButton::`vftable';
    sub_69C780((int)v24);
    sub_69C7B0((int)v24, v44, 4, 5, 6, 4, 0, 0);
    v25 = v24;
  }
  else
  {
    v25 = nullptr;
  }
  *(this + 16) = (int)v25;
  sub_69A5F0(v25, 97, 333);
  sub_69A840((uint32_t *)*(this + 1), *(this + 16));
  v26 = operator new(0x84u);
  v27 = v26;
  if ( v26 != nullptr )
  {
    sub_426BD0(v26);
    *v27 = &nengine::CNButton::`vftable';
    sub_69C780((int)v27);
    sub_69C7B0((int)v27, v40, 1, 2, 3, 1, 0, 0);
    v28 = v27;
  }
  else
  {
    v28 = nullptr;
  }
  *(this + 17) = (int)v28;
  sub_69A5F0(v28, 139, 333);
  sub_69A840((uint32_t *)*(this + 1), *(this + 17));
  v29 = operator new(0x84u);
  v30 = v29;
  if ( v29 != nullptr )
  {
    sub_426BD0(v29);
    *v30 = &nengine::CNButton::`vftable';
    sub_69C780((int)v30);
    sub_69C7B0((int)v30, v40, 4, 5, 6, 4, 0, 0);
    v31 = v30;
  }
  else
  {
    v31 = nullptr;
  }
  *(this + 18) = (int)v31;
  sub_69A5F0(v31, 181, 333);
  sub_69A840((uint32_t *)*(this + 1), *(this + 18));
  v32 = operator new(0x84u);
  v33 = v32;
  if ( v32 != nullptr )
  {
    v34 = *(this + 5);
    sub_426BD0(v32);
    *v33 = &nengine::CNButton::`vftable';
    sub_69C780((int)v33);
    sub_69C7B0((int)v33, v34, 1, 2, 3, 1, 0, 0);
    v35 = v33;
  }
  else
  {
    v35 = nullptr;
  }
  *(this + 19) = (int)v35;
  sub_69A5F0(v35, 197, 345);
  *(uint8_t *)(*(this + 19) + 16) = 0;
  sub_69A840((uint32_t *)*(this + 1), *(this + 19));
  sub_69A5F0((uint32_t *)*(this + 1), 29, 63);
  return sub_698F90((int)(this + 28), 0, 0);
}


// ------------------------------------------------------------
// 0x565AD0 sub_565AD0 —— 商品数据（121 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_565AD0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  uint32_t *v4; // esi
  int i; // ebx
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  uint32_t *v8; // esi
  int j; // ebx
  void (/*thiscall*/ ***v10)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v11)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v12)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v13)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v14)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v15)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v16)(uint32_t, int); // ecx
  int *k; // eax
  int *v18; // esi
  int v19; // ecx
  int **v20; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  *(this + 1) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(this + 6) = 0;
  v4 = this + 7;
  for ( i = 2; i != 0; --i )
  {
    if ( *v4 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v4)(*v4, 1);
    *v4++ = 0;
  }
  v6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( v6 != nullptr )
    (**v6)(v6, 1);
  v7 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 9) = 0;
  if ( v7 != nullptr )
    (**v7)(v7, 1);
  *(this + 10) = 0;
  v8 = this + 11;
  for ( j = 2; j != 0; --j )
  {
    if ( *v8 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v8)(*v8, 1);
    *v8++ = 0;
  }
  v10 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  if ( v10 != nullptr )
    (**v10)(v10, 1);
  v11 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( v11 != nullptr )
    (**v11)(v11, 1);
  v12 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  *(this + 14) = 0;
  if ( v12 != nullptr )
    (**v12)(v12, 1);
  v13 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 16);
  *(this + 15) = 0;
  if ( v13 != nullptr )
    (**v13)(v13, 1);
  v14 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 17);
  *(this + 16) = 0;
  if ( v14 != nullptr )
    (**v14)(v14, 1);
  v15 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 18);
  *(this + 17) = 0;
  if ( v15 != nullptr )
    (**v15)(v15, 1);
  v16 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 19);
  *(this + 18) = 0;
  if ( v16 != nullptr )
    (**v16)(v16, 1);
  k = (int *)*(this + 36);
  *(this + 19) = 0;
  v18 = (int *)*k;
  if ( (int *)*k != k )
  {
    do
    {
      v19 = v18[4];
      if ( v19 != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v19 + 4))(v19, 1);
      LOBYTE(k) = *((uint8_t *)v18 + 21);
      v18[4] = 0;
      if ( (uint8_t)k == 0 )
      {
        v20 = (int **)v18[2];
        if ( *((uint8_t *)v20 + 21) != 0 )
        {
          for ( k = (int *)v18[1]; *((uint8_t *)k + 21) == 0; k = (int *)k[1] )
          {
            if ( v18 != (int *)k[2] )
              break;
            v18 = k;
          }
          v18 = k;
        }
        else
        {
          v18 = (int *)v18[2];
          for ( k = *v20; *((uint8_t *)k + 21) == 0; k = (int *)*k )
            v18 = k;
        }
      }
    }
    while ( v18 != (int *)*(this + 36) );
  }
  return (char)k;
}


// ------------------------------------------------------------
// 0x565C70 sub_565C70 —— 商品标题文本（4015C0/401740/5648C0/433130/4296E0，113 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_565C70(int *this, uint32_t *a2, char a3, uint32_t *a4, uint32_t *a5)
{
  uint32_t *v6; // ecx
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int *v10; // eax
  int v11; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  void **pExceptionObject; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v17[20]; // [esp+34h] [ebp-28h] BYREF
  int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]
  uint32_t *v21; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0x1FFFFFFE )
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
  v6 = sub_5648C0(*(this + 1), (int)a4, *(this + 1), a5, 0);
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
  v10 = v6 + 1;
  v11 = (int)v6;
  if ( *(uint8_t *)(v6[1] + 20) == 0 )
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
            sub_433130(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 20) = 0;
          sub_4296E0(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_4296E0(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 20) = 0;
        sub_433130(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
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
// 0x565E20 sub_565E20 —— 商品标题收尾（565C70 + 4A3B30）
// ------------------------------------------------------------
int /*thiscall*/ sub_565E20(int *this, int a2, uint32_t *a3)
{
  uint32_t *v3; // ebx
  uint32_t *v5; // esi
  int *v6; // eax
  bool v7; // cl
  int v8; // edx
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
      v10 = *sub_565C70(this, &a3, 1, v5, v3);
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
    v12 = *sub_565C70(this, &a3, v13, v5, v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x565EE0 sub_565EE0 —— 商城/任务共用文本辅助（44CAB0 + 55E7F0/5DAF70/49A9D0/523700，112 行）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_565EE0(int this, int Src, unsigned int a3, int *a4)
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
      sub_44CAB0(this);
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
// 0x5660C0 sub_5660C0 —— 文本辅助转发（565EE0）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5660C0(int *this, int *a2)
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
    return sub_565EE0((int)this, *(this + 2), 1u, a2);
  v4 = (int *)*(this + 2);
  *v4 = *a2;
  result = (unsigned int)(v4 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x566110 sub_566110 —— 商品/任务文本打字机：WRITE_CHAR_LOOP 事件（69C340/698F90/432EE0/432EA0 + 4CE8A0/5651C0/56CFE0/565EE0/472E30/522300/41A5E0/4E9C00/445150/5660C0/565E20 + 69C680/69C500/69C3A0/69C690/69C400/44ABE0，207 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_566110(int this, int ArgList)
{
  int result; // eax
  uint32_t *v4; // edi
  const char *v5; // eax
  signed int v6; // eax
  void *v7; // eax
  int v8; // ecx
  void *v9; // edi
  int v10; // edx
  unsigned int v11; // ecx
  uint32_t *v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // edi
  int v19; // edx
  int v20; // eax
  int v21; // eax
  int v22; // edx
  int v23; // ecx
  int v24; // eax
  int v25; // edi
  int v26; // eax
  int v27; // ebx
  int v28; // eax
  int v29; // ebx
  int v30; // eax
  int v31; // eax
  uint32_t v32[15]; // [esp+8h] [ebp-A4h] BYREF
  uint32_t v33[15]; // [esp+44h] [ebp-68h] BYREF
  uint32_t v34[2]; // [esp+80h] [ebp-2Ch] BYREF
  int v35; // [esp+88h] [ebp-24h] BYREF
  char v36[4]; // [esp+8Ch] [ebp-20h] BYREF
  int v37; // [esp+90h] [ebp-1Ch] BYREF
  uint32_t *v38; // [esp+94h] [ebp-18h]
  int v39; // [esp+98h] [ebp-14h]
  int v40; // [esp+9Ch] [ebp-10h] BYREF
  int v41; // [esp+A8h] [ebp-4h]
  int ArgLista; // [esp+B4h] [ebp+8h]

  sub_69C340(-1);
  *(uint32_t *)(this + 184) = 0;
  *(uint8_t *)(this + 165) = 0;
  *(uint8_t *)(this + 166) = 0;
  sub_698F90(this + 152, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 40) + 32))(*(uint32_t *)(this + 40), 0);
  *(uint8_t *)(*(uint32_t *)(this + 40) + 17) = 0;
  sub_432EE0(5);
  sub_432EA0("WRITE_CHAR_LOOP", 5, 0, 0);
  result = *(uint32_t *)(this + 80);
  if ( result != ArgList || *(uint32_t *)(this + 84) != dword_8F84B0 )
  {
    *(uint32_t *)(this + 80) = ArgList;
    *(uint32_t *)(this + 84) = dword_8F84B0;
    v4 = (uint32_t *)sub_4CE8A0((uint32_t *)dword_8F84E8, ArgList);
    v38 = v4;
    if ( v4 != nullptr )
    {
      sub_5651C0(v4[1]);
      *(uint32_t *)(this + 88) = *(uint32_t *)(sub_56CFE0(v4[2]) + 60);
      if ( v4[10] < 0x10u )
        v5 = (const char *)(v4 + 5);
      else
        v5 = (const char *)v4[5];
      *(uint32_t *)(this + 180) = v5;
      v6 = 50 * strlen(v5);
      *(uint32_t *)(this + 188) = v6;
      if ( v6 > 3000 )
        v6 = 3000;
      *(uint32_t *)(this + 188) = v6;
      if ( v6 < 500 )
        v6 = 500;
      *(uint32_t *)(this + 188) = v6;
      v7 = *(void **)(this + 96);
      if ( v7 != nullptr )
        j__free(v7);
      *(uint32_t *)(this + 96) = 0;
      *(uint32_t *)(this + 100) = 0;
      *(uint32_t *)(this + 104) = 0;
      v8 = v4[12];
      if ( v8 != 0 )
        v39 = (v4[13] - v8) >> 2;
      else
        v39 = 0;
      ArgLista = 0;
      if ( v39 > 0 )
      {
        while ( 1 )
        {
          v9 = *(void **)(v4[12] + 4 * ArgLista);
          v40 = (int)v9;
          if ( v9 == (void *)-1 )
          {
            v10 = *(uint32_t *)(this + 96);
            v40 = 0;
            v11 = v10 != 0 ? (*(uint32_t *)(this + 100) - v10) >> 2 : 0;
            if ( v10 != 0 && v11 < (*(uint32_t *)(this + 104) - v10) >> 2 )
            {
              v12 = *(uint32_t **)(this + 100);
              *v12 = 0;
              *(uint32_t *)(this + 100) = v12 + 1;
            }
            else
            {
              sub_565EE0(*(void **)(this + 100), 1, (int)&v40);
            }
          }
          else
          {
            sub_472E30(&v35, &v40);
            if ( v35 == *(uint32_t *)(this + 144) )
            {
              v13 = sub_522300(v9, 1, 0, 0, -1, 0);
              v14 = v13;
              v37 = v13;
              if ( v13 != 0 )
              {
                if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 20))(v13, 2) != 0 )
                {
                  v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 172))(v14);
                  v16 = sub_41A5E0(v15 + 18);
                  sub_4E9C00(v33, dword_8F84B0, 0, 0, v16, 0);
                  v17 = *(uint32_t *)v14;
                  v41 = 0;
                  (*(void (/*thiscall*/ **)(int, uint32_t *))(v17 + 184))(v14, v33);
                  v41 = -1;
                  sub_445150(v33);
                }
                sub_5660C0(&v37);
                v34[0] = v40;
                v34[1] = v14;
                sub_565E20(v36, v34);
              }
            }
            else
            {
              v18 = *(uint32_t *)(v35 + 16);
              v19 = *(uint32_t *)v18;
              v37 = v18;
              if ( (*(uint8_t (/*thiscall*/ **)(int, int))(v19 + 20))(v18, 2) != 0
                && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 188))(v18) != dword_8F84B0 )
              {
                v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 172))(v18);
                v21 = sub_41A5E0(v20 + 18);
                sub_4E9C00(v32, dword_8F84B0, 0, 0, v21, 0);
                v22 = *(uint32_t *)v18;
                v41 = 1;
                (*(void (/*thiscall*/ **)(int, uint32_t *))(v22 + 184))(v18, v32);
                v41 = -1;
                sub_445150(v32);
              }
              sub_5660C0(&v37);
            }
          }
          if ( ++ArgLista >= v39 )
            break;
          v4 = v38;
        }
      }
      v23 = *(uint32_t *)(this + 96);
      if ( v23 != 0 )
        v24 = (*(uint32_t *)(this + 100) - v23) >> 2;
      else
        v24 = 0;
      v25 = *(uint32_t *)(this + 16) != 2 ? 6 : 3;
      if ( (v24 - 1) / 7 - v25 + 1 <= 0 )
      {
        v28 = 0;
      }
      else
      {
        v26 = *(uint32_t *)(this + 96);
        if ( v26 != 0 )
          v27 = (*(uint32_t *)(this + 100) - v26) >> 2;
        else
          v27 = 0;
        v28 = (v27 - 1) / 7 - v25 + 1;
      }
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), v28);
      sub_69C680(0);
      *(uint32_t *)(this + 108) = 0;
      *(uint8_t *)(this + 125) = 0;
      *(uint8_t *)(this + 126) = 0;
      sub_698F90(this + 112, 0, 0);
      v29 = sub_69C500(*(uint32_t *)(this + 24));
      v30 = sub_69C3A0(*(uint32_t *)(this + 24));
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 40) + 32))(*(uint32_t *)(this + 40), v29 - v30);
      v31 = sub_69C690(*(uint32_t *)(this + 40));
      sub_69C400(v31);
      *(uint8_t *)(*(uint32_t *)(this + 60) + 17) = *((uint8_t *)v38 + 12) == 0;
      return sub_44ABE0(0);
    }
    else
    {
      return off_77F3FC("ITEM SHOP LOAD FAIL! FILENAME[%d]", ArgList);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x566570 sub_566570 —— 商品橱窗数据（32 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_566570(uint32_t *this)
{
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 15) = 0;
  *(this + 12) = 0;
  *(this + 16) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 20) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 55) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5665C0 sub_5665C0 —— 商品橱窗数据 2（33 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5665C0(uint32_t *this)
{
  int v1; // edi
  int v2; // esi
  int v3; // ecx
  LONG v4; // ecx
  int v5; // edx

  v1 = *(this + 1);
  v2 = 0;
  while ( 1 )
  {
    v3 = *(uint32_t *)(v1 + 20);
    v4 = v2 % 2 != 0 ? v3 + 137 : v3 + 24;
    v5 = 39 * (v2 / 2);
    if ( pt.x >= v4
      && pt.x < v4 + 112
      && pt.y >= v5 + *(uint32_t *)(v1 + 24) + 157
      && pt.y < v5 + *(uint32_t *)(v1 + 24) + 193 )
    {
      break;
    }
    if ( ++v2 >= 8 )
      return -1;
  }
  return v2;
}



// ------------------------------------------------------------
// 0x566640 CNRDItemProductWindow__vmtC —— CNRDItemProductWindow__vmtC 打开槽（69C680/69C400）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemProductWindow__vmtC(int this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax

  v2 = 16 * *(uint32_t *)(*(uint32_t *)(this + 20) + 104) + this + 140;
  v3 = *(uint32_t *)(16 * *(uint32_t *)(*(uint32_t *)(this + 20) + 104) + this + 144);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(v2 + 8) - v3) >> 2;
  else
    v4 = 0;
  (*(void (/*thiscall*/ **)(uint32_t, unsigned int))(**(uint32_t **)(this + 72) + 32))(
    *(uint32_t *)(this + 72),
    (((unsigned int)(v4 - 1) >> 1) - 3) & (((unsigned int)(v4 - 1) >> 1 <= 3) - 1));
  sub_69C680(0);
  sub_69C400(0);
  return 1;
}



// ------------------------------------------------------------
// 0x5666A0 CNRDItemProductWindow__vmt8 —— CNRDItemProductWindow__vmt8 Update（120 行：CLICK_BUTTON2/WINDOW_CLOSE + 69C690/69C400/432EA0 + 5515A0/69C340/69C360/69C3A0/69C500/69C6A0/69C680/432EE0/44ABE0）
// ------------------------------------------------------------
int /*thiscall*/ sub_5666A0(char *this)
{
  int v2; // ecx
  int v3; // eax
  char *v4; // edi
  int i; // ebx
  int v6; // edi
  int v7; // eax
  uint64_t v8; // rax
  size_t v9; // edi
  uint8_t *v10; // ecx
  int v11; // ebx
  int v12; // eax
  int v13; // ebx
  const char *v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  uint32_t *v18; // edi
  int v19; // eax
  bool v20; // zf
  int result; // eax
  float v22; // [esp+0h] [ebp-424h]
  char *v23; // [esp+18h] [ebp-40Ch]
  int v24; // [esp+1Ch] [ebp-408h]
  int v25; // [esp+1Ch] [ebp-408h]
  char Destination[1024]; // [esp+20h] [ebp-404h] BYREF
  int v27; // [esp+420h] [ebp-4h]

  v2 = *((uint32_t *)this + 14);
  v27 = dword_796E50;
  if ( *(uint8_t *)(v2 + 17) != 0 )
  {
    v3 = sub_69C690((uint32_t *)v2);
    sub_69C400(*((uint32_t *)this + 20), v3);
    v4 = this + 44;
    for ( i = 2; i != 0; --i )
    {
      if ( *(uint8_t *)(*(uint32_t *)v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(*(uint32_t *)v4 + 12) )
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      v4 += 4;
    }
  }
  else
  {
    v24 = strlen(*((const char **)this + 28));
    v6 = *((uint32_t *)this + 30);
    v7 = sub_699000((int)(this + 84));
    v22 = (float)v24;
    v8 = (uint64_t)sub_4049C0(0.0, v22, v7, v6);
    v9 = sub_5515A0(*((uint32_t *)this + 28), v8);
    if ( *((uint32_t *)this + 29) != v9 )
    {
      strncpy(Destination, *((const char **)this + 28), v9);
      v10 = *((uint8_t **)this + 20);
      Destination[v9] = 0;
      sub_69C340(v10, -1);
      sub_69C360(*((uint8_t **)this + 20), (int)Destination, 0);
      v11 = sub_69C3A0(*((uint32_t *)this + 20));
      v12 = sub_69C500(*((uint32_t *)this + 20));
      v13 = (v12 - v11) & ((v12 - v11 <= 0) - 1);
      sub_69C400(*((uint32_t *)this + 20), v13);
      v14 = *((const char **)this + 28);
      *((uint32_t *)this + 29) = v9;
      if ( v9 == strlen(v14) )
      {
        (*(void (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)this + 14) + 32))(*((uint32_t *)this + 14), v13);
        v15 = sub_69C6A0(*((uint32_t *)this + 14));
        sub_69C680(v15);
        *(uint8_t *)(*((uint32_t *)this + 14) + 17) = 1;
        sub_432EE0(5);
      }
    }
  }
  v16 = *((uint32_t *)this + 31);
  if ( *(uint8_t *)(v16 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v16 + 12) )
  {
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 44))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    sub_432EA0("WINDOW_CLOSE", -1, 0, 0);
  }
  v17 = *((uint32_t *)this + 19);
  if ( *(uint8_t *)(v17 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v17 + 12) )
  {
    if ( *(uint32_t *)(*((uint32_t *)this + 2) + 2504) == 19 )
      sub_44ABE0(0);
    else
      sub_44ABE0(19);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v23 = this + 24;
  v18 = this + 144;
  v25 = 5;
  do
  {
    if ( *(uint8_t *)(*(uint32_t *)v23 + 17) != 0 && dword_79BE34 == *(uint32_t *)(*(uint32_t *)v23 + 12) )
    {
      if ( *v18 != 0 )
        v19 = (v18[1] - *v18) >> 2;
      else
        v19 = 0;
      (*(void (/*thiscall*/ **)(uint32_t, unsigned int))(**((uint32_t **)this + 18) + 32))(
        *((uint32_t *)this + 18),
        (((unsigned int)(v19 - 1) >> 1) - 3) & (((unsigned int)(v19 - 1) >> 1 <= 3) - 1));
      sub_69C680(0);
    }
    v18 += 4;
    result = v25 - 1;
    v20 = v25 == 1;
    v23 += 4;
    --v25;
  }
  while ( !v20 );
  return result;
}


// ------------------------------------------------------------
// 0x566920 CNRDItemProductWindow__vmt1C —— CNRDItemProductWindow__vmt1C 刷新槽（5665C0/69C690/44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemProductWindow__vmt1C(uint32_t *this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // edi
  unsigned int v5; // edx
  int v6; // ecx
  int v7; // eax

  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0 )
    return 0;
  if ( dword_79BE34 != *(uint32_t *)(v2 + 12) )
    return 0;
  v3 = sub_5665C0(this);
  if ( v3 == -1 )
    return 0;
  v4 = *(uint32_t *)(*(this + 5) + 104);
  v5 = v3 + 2 * sub_69C690(*(this + 18));
  v6 = *(this + 4 * v4 + 36);
  if ( v6 == 0 )
    return 0;
  if ( v5 >= (*(this + 4 * v4 + 37) - v6) >> 2 )
    return 0;
  v7 = *(uint32_t *)(*(this + 4 * v4 + 36) + 4 * v5);
  if ( v7 == 0 )
    return 0;
  sub_44E8D0((char *)dword_8F8528, (void *)0x21, v7, 1);
  return 1;
}



// ------------------------------------------------------------
// 0x5669B0 CNRDItemProductWindow__vmt0 —— CNRDItemProductWindow__vmt0 构造（69C690/404B30）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemProductWindow__vmt0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // ebx
  int v11; // edi
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // edx
  bool v16; // cc
  uint8_t v17[204800]; // [esp+4h] [ebp-32010h] BYREF
  int v18; // [esp+32004h] [ebp-10h]
  int v19; // [esp+32008h] [ebp-Ch]
  int v20; // [esp+3200Ch] [ebp-8h]
  uint32_t *v21; // [esp+32010h] [ebp-4h]
  int v22; // [esp+3201Ch] [ebp+8h]

  result = a2;
  if ( a2 == *(this + 1) )
  {
    v4 = *(this + 55);
    if ( v4 != 0 )
    {
      v5 = *(uint32_t *)(v4 + 60);
      if ( v5 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, 57, 88, dword_79C0B0);
    }
    v6 = 16 * *(uint32_t *)(*(this + 5) + 104);
    v7 = *(uint32_t *)((char *)this + v6 + 144);
    v8 = (int)this + v6 + 140;
    if ( v7 != 0 )
      v19 = (*(uint32_t *)(v8 + 8) - v7) >> 2;
    else
      v19 = 0;
    v9 = *(this + 18);
    v20 = 0;
    result = sub_69C690(v9);
    v10 = 2 * result;
    v22 = 2 * result;
    do
    {
      if ( v10 >= v19 )
        break;
      v21 = this + 4 * *(uint32_t *)(*(this + 5) + 104) + 36;
      if ( *(uint32_t *)(4 * v10 + *v21) != 0 )
      {
        if ( (v10 - 2 * sub_69C690(*(this + 18))) % 2 != 0 )
          v11 = *(uint32_t *)(*(this + 1) + 20) + 137;
        else
          v11 = *(uint32_t *)(*(this + 1) + 20) + 24;
        v12 = v11 + 5;
        v13 = 39 * ((v10 - 2 * sub_69C690(*(this + 18))) / 2) + *(uint32_t *)(*(this + 1) + 24) + 162;
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t))(**(uint32_t **)(4 * v22 + *v21) + 8))(
          *(uint32_t *)(4 * v22 + *v21),
          v12,
          v13,
          1,
          0);
        v21 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(4 * v22 + *v21) + 108))(*(uint32_t *)(4 * v22 + *v21));
        v14 = sub_404B30(v17, v21, this + 56);
        v15 = *(uint32_t *)dword_79C0B0;
        v18 = v14;
        (*(void (/*thiscall*/ **)(int, uint32_t *))(v15 + 72))(dword_79C0B0, this + 56);
        (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v12 + 35,
          v13 + (v18 > 1 ? 0 : 7),
          -1,
          v21);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v10 = v22;
      }
      result = v20 + 1;
      ++v10;
      v16 = ++v20 < 8;
      v22 = v10;
    }
    while ( v16 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x566B80 sub_566B80 —— 商品橱窗数据 3（66 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_566B80(uint32_t **this)
{
  int result; // eax
  int v2; // edi
  unsigned int v3; // ebx
  int v4; // ecx
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v14; // [esp+Ch] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  v2 = *(uint32_t *)(result + 104);
  v3 = 0;
  if ( v2 != 0 )
  {
    v4 = *(uint32_t *)(v2 + 8);
    if ( v4 != 0 )
    {
      result = (*(uint32_t *)(v2 + 12) - v4) >> 2;
      v14 = result;
    }
    else
    {
      v14 = 0;
    }
    if ( v14 > 0 )
    {
      while ( 1 )
      {
        v5 = *(uint32_t *)(v2 + 8);
        if ( v5 != 0 && v3 < (*(uint32_t *)(v2 + 12) - v5) >> 2 )
          v6 = *(uint32_t *)(v5 + 4 * v3);
        else
          v6 = 0;
        v7 = __RTDynamicCast(v6, 0, &CNRDObject `RTTI Type Descriptor', &CNRDNpc `RTTI Type Descriptor', 0);
        v8 = v7;
        if ( v7 != 0 && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 340))(v7) == **(this + 55) )
          break;
        result = v14;
        if ( (int)++v3 >= v14 )
          return result;
      }
      v9 = (int)*(this + 55);
      v10 = *(uint32_t *)(v9 + 180);
      v11 = v9 + 156;
      if ( v10 < 0x10 )
        v12 = v11 + 4;
      else
        v12 = *(uint32_t *)(v11 + 4);
      return (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)v8 + 212))(v8, v12, -1, 0, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x566C60 sub_566C60 —— 商品橱窗页绘制（279 行：43C250/46F7A0/46F880 + 69A840/69A5F0/69CE50 + 426BD0/69C780/69C7B0/69CA20/69CA50/69C5D0/69CD70/69C2D0/69C520/69C440/69C420/69C3E0/69C4C0）
// ------------------------------------------------------------
int /*thiscall*/ sub_566C60(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ebx
  uint32_t **v5; // edi
  uint32_t *v6; // eax
  int v7; // eax
  int v8; // ebx
  uint8_t *v9; // edi
  uint8_t *v10; // eax
  uint32_t *v11; // edi
  int v12; // ebx
  uint8_t *v13; // edi
  int v14; // ebx
  uint32_t *v15; // ecx
  int v16; // ebx
  uint8_t *v17; // edi
  uint8_t *v18; // eax
  uint32_t *v19; // edi
  uint8_t *v20; // eax
  uint32_t *v21; // edi
  int v22; // ebx
  uint32_t *v23; // ecx
  uint8_t *v24; // edi
  uint32_t *v25; // ecx
  uint8_t *v26; // eax
  uint32_t *v27; // edi
  uint8_t *v28; // edi
  uint32_t *v29; // ecx
  int result; // eax
  void *Block; // [esp+10h] [ebp-14h]
  void *Blocka; // [esp+10h] [ebp-14h]
  void *Blockb; // [esp+10h] [ebp-14h]
  void *Blockc; // [esp+10h] [ebp-14h]
  void *Blockd; // [esp+10h] [ebp-14h]
  void *Blocke; // [esp+10h] [ebp-14h]
  void *Blockf; // [esp+10h] [ebp-14h]
  int v38; // [esp+14h] [ebp-10h]
  uint32_t *v39; // [esp+14h] [ebp-10h]
  int v40; // [esp+14h] [ebp-10h]
  uint32_t *v41; // [esp+14h] [ebp-10h]
  int v42; // [esp+14h] [ebp-10h]

  *(uint32_t *)(this + 16) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 200);
  if ( operator new(0x6Cu) != nullptr )
    v2 = sub_43C250(*(uint32_t *)(this + 16), 0);
  else
    v2 = 0;
  *(uint32_t *)(this + 4) = v2;
  *(uint32_t *)(v2 + 28) = *(uint32_t *)(v2 + 28);
  *(uint32_t *)(v2 + 32) = 353;
  *(uint32_t *)(*(uint32_t *)(this + 4) + 68) = this;
  if ( operator new(0x70u) != nullptr )
    v3 = sub_46F7A0(0);
  else
    v3 = 0;
  *(uint32_t *)(this + 20) = v3;
  v38 = 16;
  v4 = 2;
  v5 = (uint32_t **)(this + 24);
  do
  {
    if ( operator new(0x88u) != nullptr )
      v6 = (uint32_t *)sub_46F880(*(uint32_t *)(this + 16), v4, v4, v4 - 1, -1, 0, 0);
    else
      v6 = nullptr;
    *v5 = v6;
    sub_69A840(v6);
    sub_69A5F0(*v5, v38, 128);
    v7 = (*v5)[7] + v38;
    v4 += 2;
    ++v5;
    v38 = v7;
  }
  while ( v4 < 12 );
  sub_69CE50(0);
  sub_69A840(*(uint32_t *)(this + 20));
  v8 = 4;
  v39 = (uint32_t *)(this + 44);
  do
  {
    v9 = operator new(0x84u);
    if ( v9 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v9);
      *(uint32_t *)v9 = &nengine::CNButton::`vftable';
      sub_69C780(v9);
      sub_69C7B0(Block, v8, v8, v8 + 1, v8, 0, 0);
    }
    else
    {
      v9 = nullptr;
    }
    *v39 = v9;
    v8 += 2;
    ++v39;
  }
  while ( v8 < 8 );
  v10 = operator new(0x88u);
  v11 = v10;
  if ( v10 != nullptr )
  {
    v12 = *(uint32_t *)(this + 16);
    sub_426BD0(v10);
    *v11 = &nengine::CNSlider::`vftable';
    sub_69CA20(v11);
    sub_69CA50(v12, 14, 20);
    *v11 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v11 = nullptr;
  }
  *(uint32_t *)(this + 52) = v11;
  v13 = operator new(0x74u);
  if ( v13 != nullptr )
  {
    v14 = *(uint32_t *)(this + 52);
    Blocka = *(void **)(this + 48);
    v40 = *(uint32_t *)(this + 44);
    sub_426BD0(v13);
    *(uint32_t *)v13 = &nengine::CNScroll::`vftable';
    sub_69C5D0(v13);
    *(uint32_t *)v13 = &nengine::CNVScroll::`vftable';
    sub_69C5D0(v13);
    sub_69CD70(v40, Blocka, v14);
    v15 = v13;
  }
  else
  {
    v15 = nullptr;
  }
  *(uint32_t *)(this + 56) = v15;
  sub_69A5F0(v15, 249, 27);
  sub_69A840(*(uint32_t *)(this + 56));
  v16 = 4;
  v41 = (uint32_t *)(this + 60);
  do
  {
    v17 = operator new(0x84u);
    if ( v17 != nullptr )
    {
      Blockb = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v17);
      *(uint32_t *)v17 = &nengine::CNButton::`vftable';
      sub_69C780(v17);
      sub_69C7B0(Blockb, v16, v16, v16 + 1, v16, 0, 0);
    }
    else
    {
      v17 = nullptr;
    }
    *v41 = v17;
    v16 += 2;
    ++v41;
  }
  while ( v16 < 8 );
  v18 = operator new(0x88u);
  v19 = v18;
  if ( v18 != nullptr )
  {
    Blockc = *(void **)(this + 16);
    sub_426BD0(v18);
    *v19 = &nengine::CNSlider::`vftable';
    sub_69CA20(v19);
    sub_69CA50(Blockc, 15, 20);
    *v19 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v19 = nullptr;
  }
  *(uint32_t *)(this + 68) = v19;
  v20 = operator new(0x74u);
  v21 = v20;
  if ( v20 != nullptr )
  {
    v22 = *(uint32_t *)(this + 68);
    Blockd = *(void **)(this + 64);
    v42 = *(uint32_t *)(this + 60);
    sub_426BD0(v20);
    *v21 = &nengine::CNScroll::`vftable';
    sub_69C5D0(v21);
    *v21 = &nengine::CNVScroll::`vftable';
    sub_69C5D0(v21);
    sub_69CD70(v42, Blockd, v22);
    v23 = v21;
  }
  else
  {
    v23 = nullptr;
  }
  *(uint32_t *)(this + 72) = v23;
  sub_69A5F0(v23, 255, 162);
  sub_69A840(*(uint32_t *)(this + 72));
  v24 = operator new(0x84u);
  if ( v24 != nullptr )
  {
    Blocke = *(void **)(this + 16);
    sub_426BD0(v24);
    *(uint32_t *)v24 = &nengine::CNButton::`vftable';
    sub_69C780(v24);
    sub_69C7B0(Blocke, 11, 12, 13, 11, 0, 0);
    v25 = v24;
  }
  else
  {
    v25 = nullptr;
  }
  *(uint32_t *)(this + 76) = v25;
  sub_69A5F0(v25, 112, 326);
  sub_69A840(*(uint32_t *)(this + 76));
  v26 = operator new(0x6Cu);
  v27 = v26;
  if ( v26 != nullptr )
  {
    sub_426BD0(v26);
    *v27 = &nengine::CNTextBox::`vftable';
    sub_69C2D0(v27);
    sub_69C520(130, 2048);
  }
  else
  {
    v27 = nullptr;
  }
  *(uint32_t *)(this + 80) = v27;
  sub_69C440(-4265479);
  sub_69C420(2);
  sub_69C3E0(5);
  sub_69C4C0(dword_99FCCC);
  sub_69A5F0(*(uint32_t **)(this + 80), 110, 31);
  sub_69A840(*(uint32_t *)(this + 80));
  v28 = operator new(0x84u);
  if ( v28 != nullptr )
  {
    Blockf = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
    sub_426BD0(v28);
    *(uint32_t *)v28 = &nengine::CNButton::`vftable';
    sub_69C780(v28);
    sub_69C7B0(Blockf, 11, 12, 13, 11, 0, 0);
    v29 = v28;
  }
  else
  {
    v29 = nullptr;
  }
  *(uint32_t *)(this + 124) = v29;
  sub_69A5F0(v29, 221, 353);
  sub_69A840(*(uint32_t *)(this + 124));
  sub_69A5F0(*(uint32_t **)(this + 4), 29, 63);
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 256) = 0;
  *(uint32_t *)(this + 260) = 0;
  *(uint32_t *)(this + 264) = 0;
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint8_t *)(this + 224) = 0;
  *(uint8_t *)(this + 225) = 0;
  *(uint8_t *)(this + 226) = 0;
  *(uint8_t *)(this + 227) = 0;
  *(uint32_t *)(this + 240) = 6;
  *(uint32_t *)(this + 244) = 12;
  *(uint32_t *)(this + 252) = 1600;
  result = dword_99FCCC;
  *(uint32_t *)(this + 260) = 0;
  *(uint32_t *)(this + 272) = result;
  *(uint32_t *)(this + 228) = -16777216;
  *(uint32_t *)(this + 252) = 68;
  *(uint32_t *)(this + 256) = 2;
  return result;
}


// ------------------------------------------------------------
// 0x5672B0 sub_5672B0 —— 商品橱窗数据 4（120 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_5672B0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  uint32_t *v4; // esi
  int i; // edi
  void (/*thiscall*/ ****v6)(uint32_t, int); // esi
  int j; // edi
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  bool v10; // zf
  void (/*thiscall*/ ***v11)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v12)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v13)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v14)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v15)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v16)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v17)(uint32_t, int); // ecx
  int *k; // eax
  int *v19; // esi
  int v20; // ecx
  int **v21; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 1) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(this + 5) = 0;
  v4 = this + 6;
  for ( i = 5; i != 0; --i )
  {
    if ( *v4 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v4)(*v4, 1);
    *v4++ = 0;
  }
  v6 = (void (/*thiscall*/ ****)(uint32_t, int))(this + 15);
  for ( j = 2; j != 0; --j )
  {
    v8 = *(v6 - 4);
    if ( v8 != nullptr )
      (**v8)(v8, 1);
    v9 = *v6;
    v10 = *v6 == nullptr;
    *(v6 - 4) = nullptr;
    if ( !v10 )
      (**v9)(v9, 1);
    *v6++ = nullptr;
  }
  v11 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  if ( v11 != nullptr )
    (**v11)(v11, 1);
  v12 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( v12 != nullptr )
    (**v12)(v12, 1);
  v13 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 17);
  *(this + 14) = 0;
  if ( v13 != nullptr )
    (**v13)(v13, 1);
  v14 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 18);
  *(this + 17) = 0;
  if ( v14 != nullptr )
    (**v14)(v14, 1);
  v15 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 19);
  *(this + 18) = 0;
  if ( v15 != nullptr )
    (**v15)(v15, 1);
  v16 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 20);
  *(this + 19) = 0;
  if ( v16 != nullptr )
    (**v16)(v16, 1);
  v17 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 31);
  *(this + 20) = 0;
  if ( v17 != nullptr )
    (**v17)(v17, 1);
  k = (int *)*(this + 33);
  *(this + 31) = 0;
  v19 = (int *)*k;
  if ( (int *)*k != k )
  {
    do
    {
      v20 = v19[4];
      if ( v20 != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v20 + 4))(v20, 1);
      LOBYTE(k) = *((uint8_t *)v19 + 21);
      v19[4] = 0;
      if ( (uint8_t)k == 0 )
      {
        v21 = (int **)v19[2];
        if ( *((uint8_t *)v21 + 21) != 0 )
        {
          for ( k = (int *)v19[1]; *((uint8_t *)k + 21) == 0; k = (int *)k[1] )
          {
            if ( v19 != (int *)k[2] )
              break;
            v19 = k;
          }
          v19 = k;
        }
        else
        {
          v19 = (int *)v19[2];
          for ( k = *v21; *((uint8_t *)k + 21) == 0; k = (int *)*k )
            v19 = k;
        }
      }
    }
    while ( v19 != (int *)*(this + 33) );
  }
  return (char)k;
}


// ------------------------------------------------------------
// 0x567430 CNRDItemProductWindow__vmt10 —— CNRDItemProductWindow__vmt10 状态切换槽（44ABE0/44E850/566B80/432EE0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemProductWindow__vmt10(int this)
{
  uint32_t *v2; // ecx
  int result; // eax

  v2 = *(uint32_t **)(this + 8);
  if ( v2[626] == 19 )
    sub_44ABE0(v2, 0);
  sub_44E850(*(uint32_t **)(this + 8), 33);
  sub_566B80((uint32_t **)this);
  result = *(uint32_t *)(this + 56);
  if ( *(uint8_t *)(result + 17) == 0 )
    return sub_432EE0(5);
  return result;
}



// ------------------------------------------------------------
// 0x567470 sub_567470 —— 商品橱窗文本打字机：WRITE_CHAR_LOOP（69C340/698F90/432EE0/432EA0 + 4CE8A0/56CFE0/472E30/522300/565EE0/565E20 + 69C3A0/69C500/69C690/69C400，182 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_567470(uint32_t *this, int ArgList)
{
  uint32_t *v2; // ebx
  uint8_t *v3; // ecx
  int v4; // eax
  int v5; // esi
  const char *v7; // eax
  signed int v8; // eax
  void **v9; // edi
  int i; // esi
  int v11; // ecx
  int v12; // eax
  int *v13; // esi
  void *v14; // edi
  int v15; // edx
  bool v16; // zf
  unsigned int v17; // ecx
  uint32_t *v18; // eax
  int v19; // ebx
  int v20; // eax
  unsigned int v21; // edx
  int *v22; // eax
  int v23; // ecx
  int v24; // edi
  unsigned int v25; // edx
  int *v26; // eax
  int v27; // esi
  int v28; // eax
  int v29; // eax
  uint32_t v30[2]; // [esp+Ch] [ebp-24h] BYREF
  int v31; // [esp+14h] [ebp-1Ch] BYREF
  char v32[4]; // [esp+18h] [ebp-18h] BYREF
  int v33; // [esp+1Ch] [ebp-14h] BYREF
  int v34; // [esp+20h] [ebp-10h]
  uint32_t *v35; // [esp+24h] [ebp-Ch]
  int v36; // [esp+28h] [ebp-8h]
  int v37; // [esp+2Ch] [ebp-4h]
  int ArgLista; // [esp+38h] [ebp+8h]

  v2 = this;
  v3 = (uint8_t *)*(this + 20);
  v35 = v2;
  sub_69C340(v3, -1);
  v2[29] = 0;
  *((uint8_t *)v2 + 97) = 0;
  *((uint8_t *)v2 + 98) = 0;
  sub_698F90((int)(v2 + 21), 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)v2[14] + 32))(v2[14], 0);
  *(uint8_t *)(v2[14] + 17) = 0;
  sub_432EE0(5);
  sub_432EA0("WRITE_CHAR_LOOP", 5, 0, 0);
  v4 = sub_4CE8A0(ArgList);
  v5 = v4;
  v36 = v4;
  if ( v4 == 0 )
    return off_77F3FC("ITEM SHOP LOAD FAIL! FILENAME[%d]", ArgList);
  v2[55] = sub_56CFE0(*(uint32_t *)(v4 + 8));
  if ( *(uint32_t *)(v5 + 40) < 0x10u )
    v7 = (const char *)(v5 + 20);
  else
    v7 = *(const char **)(v5 + 20);
  v2[28] = v7;
  v8 = 50 * strlen(v7);
  v2[30] = v8;
  if ( v8 > 3000 )
    v8 = 3000;
  v2[30] = v8;
  if ( v8 < 500 )
    v8 = 500;
  v2[30] = v8;
  v9 = (void **)(v2 + 36);
  for ( i = 5; i != 0; --i )
  {
    if ( *v9 != nullptr )
      j__free(*v9);
    *v9 = nullptr;
    v9[1] = nullptr;
    v9[2] = nullptr;
    v9 += 4;
  }
  v11 = *(uint32_t *)(v36 + 48);
  if ( v11 != 0 )
    v37 = (*(uint32_t *)(v36 + 52) - v11) >> 2;
  else
    v37 = 0;
  v12 = 0;
  ArgLista = 0;
  v34 = 0;
  if ( v37 > 0 )
  {
    v13 = v2 + 36;
    do
    {
      v33 = *(uint32_t *)(*(uint32_t *)(v36 + 48) + 4 * v12);
      v14 = (void *)v33;
      if ( v33 == -1 )
      {
        v15 = *v13;
        v16 = *v13 == 0;
        v33 = 0;
        if ( v16 )
          v17 = 0;
        else
          v17 = (v13[1] - v15) >> 2;
        if ( v15 == 0 || v17 >= (v13[2] - v15) >> 2 )
          goto LABEL_44;
        v18 = (uint32_t *)v13[1];
        *v18 = 0;
        v13[1] = (int)(v18 + 1);
      }
      else
      {
        if ( v33 == -2 )
        {
          if ( ArgLista < 4 )
          {
            ++ArgLista;
            v13 += 4;
          }
          goto LABEL_45;
        }
        sub_472E30(&v31, &v33);
        if ( v31 == v2[33] )
        {
          v19 = sub_522300(v14, 1, 0, -1, 0, 1);
          v20 = *v13;
          v16 = *v13 == 0;
          v33 = v19;
          if ( v16 )
            v21 = 0;
          else
            v21 = (v13[1] - v20) >> 2;
          if ( v20 != 0 && v21 < (v13[2] - v20) >> 2 )
          {
            v22 = (int *)v13[1];
            *v22 = v19;
            v13[1] = (int)(v22 + 1);
          }
          else
          {
            sub_565EE0((void *)v13[1], 1, (int)&v33);
          }
          v30[0] = v14;
          v30[1] = v19;
          sub_565E20(v32, v30);
          v2 = v35;
          goto LABEL_45;
        }
        v23 = *v13;
        v16 = *v13 == 0;
        v24 = *(uint32_t *)(v31 + 16);
        v33 = v24;
        if ( v16 )
          v25 = 0;
        else
          v25 = (v13[1] - v23) >> 2;
        if ( v23 == 0 || v25 >= (v13[2] - v23) >> 2 )
        {
LABEL_44:
          sub_565EE0((void *)v13[1], 1, (int)&v33);
          goto LABEL_45;
        }
        v26 = (int *)v13[1];
        *v26 = v24;
        v13[1] = (int)(v26 + 1);
      }
LABEL_45:
      v12 = ++v34;
    }
    while ( v34 < v37 );
  }
  v27 = sub_69C3A0(v2[20]);
  v28 = sub_69C500(v2[20]);
  (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)v2[14] + 32))(v2[14], v28 - v27);
  v29 = sub_69C690((uint32_t *)v2[14]);
  return sub_69C400(v2[20], v29);
}


// ============================================================
// 【分区 18】NPC 对象 CNRDNpc（0x567760-0x5683A0）
// 头顶任务标记绘制在 0x5677B0：资源 Common/Etc/NpcQuest.img（41C590/42B420）；
// vmt158/vmt144/vmt14C=交互与标记槽；0x567C10/0x567F40=对话/商店联动。
// ============================================================
// ------------------------------------------------------------
// 0x567760 sub_567760 —— 13 行小辅助
// ------------------------------------------------------------
void /*thiscall*/ sub_567760(int this)
{
  *(uint32_t *)(this + 96) = 34;
  *(uint32_t *)(this + 292) = 7;
  *(uint8_t *)(this + 296) = 0;
  *(uint32_t *)(this + 288) = -1;
}



// ------------------------------------------------------------
// 0x567790 CNRDNpc__vmtC —— CNRDNpc__vmtC 打开槽（15 行）
// ------------------------------------------------------------
int /*thiscall*/ CNRDNpc__vmtC(int this)
{
  int result; // eax

  result = CNRDObject__vmtC((void *)this);
  *(uint32_t *)(this + 292) = 7;
  *(uint8_t *)(this + 296) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5677B0 sub_5677B0 —— NPC 头顶任务标记绘制：资源 Common/Etc/NpcQuest.img（41C590/42B420/491530/418DD0/491630，95 行）
// ------------------------------------------------------------
void /*cdecl*/ sub_5677B0(int a1, int a2, int a3, char a4)
{
  int v4; // esi
  DWORD Time; // eax
  uint8_t v6; // al
  int v7; // eax
  int v8; // eax
  uint8_t v9; // [esp+4h] [ebp-8h]
  uint8_t v10; // [esp+8h] [ebp-4h]

  if ( a3 != 7 && (uint8_t)sub_41C590(dword_8F7A24) != 1 )
  {
    if ( dword_9B888C == 0 )
      dword_9B888C = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                       dword_8F84B8,
                       "Common/Etc/NpcQuest.img");
    v4 = 0;
    if ( a3 != 0 )
    {
      switch ( a3 )
      {
        case 1:
          v4 = 6;
          break;
        case 2:
          v4 = 0;
          break;
        case 3:
          v4 = 10;
          break;
        case 4:
          v4 = 2;
          break;
        case 5:
          v4 = 12;
          break;
        case 6:
          v4 = 14;
          break;
        default:
          break;
      }
    }
    else
    {
      v4 = 8;
    }
    Time = timeGetTime();
    if ( a4 != 0 )
    {
      v6 = sub_42B420(255, 0, Time, 400);
      v10 = v6;
    }
    else
    {
      v6 = sub_42B420(255, 130, Time, 400);
      v10 = -1;
    }
    v9 = v6;
    sub_491530(2, 0);
    v7 = sub_418DD0(v4);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
        v7,
        a1 - 30,
        a2 - 30,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v9 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491630(2);
    v8 = sub_418DD0(v4 + 1);
    if ( v8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v8 + 128))(
        v8,
        a1 - 30,
        a2 - 30,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v10 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
  }
}



// ------------------------------------------------------------
// 0x567950 CNRDNpc__vmt158 —— CNRDNpc__vmt158 交互槽（45E490/45E4D0/525CE0）
// ------------------------------------------------------------
bool /*thiscall*/ CNRDNpc__vmt158(uint32_t *this, int a2, int a3)
{
  uint32_t *v4; // edi
  int v6; // eax
  int v7; // eax
  uint32_t *v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // ebx
  int **v12; // eax
  int v13; // [esp-10h] [ebp-18h]
  int v14; // [esp-Ch] [ebp-14h]
  int v15; // [esp-8h] [ebp-10h]

  v4 = (uint32_t *)*(this + 29);
  if ( v4 == nullptr )
    return false;
  v15 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 8);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v7 = sub_45E490(v4, v6, v15);
  v8 = (uint32_t *)*(this + 29);
  v9 = v7;
  v14 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 8);
  v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v11 = sub_45E4D0(v8, v10, v13, v14, 1.0);
  if ( a2 < v9 - 100 || a2 >= v9 + 100 )
    return false;
  v12 = (int **)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this);
  if ( sub_525CE0(v12, 7) )
  {
    if ( a3 < v11 - 100 )
      return false;
  }
  else if ( a3 < v11 - 200 )
  {
    return false;
  }
  return a3 < v11 + 10;
}



// ------------------------------------------------------------
// 0x567A10 CNRDNpc__vmt144 —— CNRDNpc__vmt144 绘制槽（5677B0 标记 + 418DD0/472E30/50D8F0，107 行）
// ------------------------------------------------------------
void /*userpurge*/ CNRDNpc__vmt144(int *a1@<ecx>, int a2@<edi>, int a3, int a4, int a5, int a6)
{
  int v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // esi
  int v15; // eax
  int v16; // eax
  int v17; // esi
  int v18; // ebx
  int v19; // eax
  int v20; // eax
  unsigned int v21; // ecx
  int v22; // eax
  int v23; // eax
  int v24; // ebx
  int v25; // eax
  unsigned int v26; // ecx
  int v27; // eax
  int v28; // eax

  if ( (uint8_t)a3 != 0 )
  {
    v7 = a4;
    v8 = a5;
    nullsub_2(a3, a4, a5, a6);
    sub_5677B0(v7, v8 - a1[40] - 40, a1[73], *((uint8_t *)a1 + 296));
    v9 = *((uint32_t *)dword_8F8528 + 12);
    if ( *(int **)(v9 + 8) == a1 )
    {
      if ( *(uint32_t *)(v9 + 12) != 0 )
      {
        v11 = sub_418DD0(73);
        if ( v11 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(
            v11,
            v7 + 10,
            v8 - a1[40] - 10,
            dword_79C0B0);
      }
      else
      {
        v10 = sub_418DD0(74);
        if ( v10 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(
            v10,
            v7 - 33,
            v8 - a1[40] - 10,
            dword_79C0B0);
      }
    }
    (*(void (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_77F8FC, a2);
    v12 = *a1;
    a6 = v8 - a1[40] - 16;
    a5 = 7;
    v13 = (*(int (/*thiscall*/ **)(int *))(v12 + 340))(a1);
    if ( *sub_472E30((int **)(v13 + 192), (int **)&a4, &a5) == *(int **)(v13 + 196) )
    {
      v20 = (*(int (/*thiscall*/ **)(int *))(*a1 + 340))(a1);
      v21 = *(uint32_t *)(v20 + 56);
      v22 = v20 + 32;
      if ( v21 < 0x10 )
        v23 = v22 + 4;
      else
        v23 = *(uint32_t *)(v22 + 4);
      v24 = v7 - (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v23) / 2;
      v25 = (*(int (/*thiscall*/ **)(int *))(*a1 + 340))(a1);
      v26 = *(uint32_t *)(v25 + 56);
      v27 = v25 + 32;
      if ( v26 < 0x10 )
        v28 = v27 + 4;
      else
        v28 = *(uint32_t *)(v27 + 4);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v24,
        a6,
        -6567706,
        v28);
    }
    else
    {
      v14 = *(uint32_t *)dword_99FCCC;
      v15 = sub_50D8F0();
      v16 = (*(int (/*thiscall*/ **)(int, int))(v14 + 16))(dword_99FCCC, v15);
      v17 = *(uint32_t *)dword_79C0B0;
      v18 = v7 - v16 / 2;
      v19 = sub_50D8F0();
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(v17 + 80))(dword_79C0B0, v18, a6, -6567706, v19);
    }
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  }
  else
  {
    nullsub_2(0, a4, a5, a6);
  }
}



// ------------------------------------------------------------
// 0x567C10 sub_567C10 —— NPC 对话联动（47CC80/429830/472E30/524330/522EB0/463F10，178 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_567C10(uint32_t *this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // ebx
  unsigned int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  char v10; // al
  char *v11; // edi
  char *v12; // edx
  char *v13; // eax
  char v14; // al
  char *v15; // eax
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  char v21; // al
  void *v22; // ecx
  int v23; // eax
  int v24; // edi
  uint32_t *v25; // eax
  int v26; // edi
  int v27; // ebx
  uint32_t *v28; // eax
  char v29[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  char *v31; // [esp+14h] [ebp-1Ch]
  char v32[4]; // [esp+1Ch] [ebp-14h] BYREF
  uint32_t v33[4]; // [esp+20h] [ebp-10h] BYREF

  *(this + 73) = 7;
  *((uint8_t *)this + 296) = 0;
  v2 = dword_8F8540;
  v3 = *(uint32_t *)(dword_8F8540 + 8);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(dword_8F8540 + 12) - v3) / 20;
  else
    v4 = 0;
  v5 = 0;
  if ( v4 <= 0 )
  {
LABEL_20:
    sub_47CC80(v29, *(this + 71));
    v11 = (char *)Block;
    v12 = v31;
    v33[3] = 0;
    v13 = (char *)Block;
    if ( Block != v31 )
    {
      while ( *(uint8_t *)(*(uint32_t *)v13 + 120) == 0 || *(uint8_t *)(*(uint32_t *)v13 + 320) == 0 && *(this + 73) != 7 )
      {
        v13 += 4;
        if ( v13 == v31 )
          goto LABEL_27;
      }
      *(this + 73) = 1;
      v14 = *(uint8_t *)(*(uint32_t *)v13 + 320);
      *((uint8_t *)this + 296) = v14;
      if ( v14 != 0 )
        goto LABEL_38;
    }
LABEL_27:
    v15 = v11;
    if ( v11 != v12 )
    {
      while ( *(uint32_t *)(*(uint32_t *)v15 + 116) != 2 || *(uint8_t *)(*(uint32_t *)v15 + 320) == 0 && *(this + 73) != 7 )
      {
        v15 += 4;
        if ( v15 == v12 )
          goto LABEL_32;
      }
      *(this + 73) = 2;
      v21 = *(uint8_t *)(*(uint32_t *)v15 + 320);
      *((uint8_t *)this + 296) = v21;
      if ( v21 != 0 )
      {
LABEL_38:
        if ( v11 != nullptr )
          j__free(v11);
        return;
      }
    }
LABEL_32:
    if ( *(this + 73) == 7 )
    {
      v16 = sub_429830((uint16_t)word_77F804);
      if ( v16 != 0 )
      {
        v17 = *(uint32_t *)(v16 + 44);
        v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this);
        v17 *= 16;
        v19 = *(uint32_t *)(v18 + v17 + 236);
        v20 = v18 + v17 + 232;
        if ( v19 != 0 && (*(uint32_t *)(v20 + 8) - v19) >> 2 != 0 )
        {
          *(this + 73) = 3;
          goto LABEL_50;
        }
      }
      v22 = Block;
      if ( Block != nullptr && (v31 - (uint8_t *)Block) >> 2 != 0 )
      {
        *(this + 73) = 4;
        *((uint8_t *)this + 296) = 0;
        j__free(v22);
        return;
      }
    }
    v23 = *this;
    v33[0] = 8;
    v24 = (*(int (/*thiscall*/ **)(uint32_t *))(v23 + 340))(this);
    if ( *(uint32_t *)sub_472E30(v32, v33) != *(uint32_t *)(v24 + 196) )
    {
      v25 = (uint32_t *)sub_524330();
      if ( sub_522EB0(v25) != 0 )
      {
        *(this + 73) = 5;
        *((uint8_t *)this + 296) = 0;
      }
      if ( *(uint32_t *)(sub_524330() + 4) != 0 )
      {
        *(this + 73) = 5;
        *((uint8_t *)this + 296) = 0;
      }
      v26 = *(uint32_t *)(sub_524330() + 4);
      v27 = *(uint32_t *)(sub_524330() + 8);
      v28 = (uint32_t *)sub_524330();
      if ( v26 + v27 + sub_522EB0(v28) > 20 )
      {
        *(this + 73) = 6;
LABEL_50:
        *((uint8_t *)this + 296) = 0;
      }
    }
    if ( Block != nullptr )
      j__free(Block);
    return;
  }
  v33[0] = 0;
  while ( 1 )
  {
    v6 = *(uint32_t *)(v2 + 8);
    if ( v6 != 0 && v5 < (*(uint32_t *)(v2 + 12) - v6) / 20 )
      v7 = *(uint32_t *)(v33[0] + *(uint32_t *)(v2 + 8));
    else
      v7 = 0;
    if ( *(uint32_t *)(v7 + 128) == *(this + 71) )
    {
      if ( sub_463F10(v5) == 0 )
        break;
      v2 = dword_8F8540;
    }
    ++v5;
    v33[0] += 20;
    if ( (int)v5 >= v4 )
      goto LABEL_20;
  }
  *(this + 73) = 0;
  v8 = *(uint32_t *)(dword_8F8540 + 8);
  if ( v8 != 0 && v5 < (*(uint32_t *)(dword_8F8540 + 12) - v8) / 20 )
    v9 = *(uint32_t *)(*(uint32_t *)(dword_8F8540 + 8) + 20 * v5);
  else
    v9 = 0;
  v10 = *(uint8_t *)(v9 + 320);
  *((uint8_t *)this + 296) = v10;
  if ( v10 == 0 )
    goto LABEL_20;
}


// ------------------------------------------------------------
// 0x567F40 sub_567F40 —— NPC 商店/任务联动（546840 引导 + 472E30/44E8D0/522E20/47CC80/5E5260/461730/463ED0/463F10/5540D0/44BBA0/552BD0/526BF0，126 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_567F40(int *this, char a2)
{
  uint32_t *v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // esi
  int v7; // edx
  int v8; // esi
  int v9; // eax
  int v10; // edi
  int v11; // esi
  int *v12; // eax
  void **v13; // ecx
  int *v14; // eax
  char v15[4]; // [esp+8h] [ebp-28h] BYREF
  int *v16; // [esp+Ch] [ebp-24h]
  int *v17; // [esp+10h] [ebp-20h]
  char v18[4]; // [esp+18h] [ebp-18h] BYREF
  int *v19; // [esp+1Ch] [ebp-14h]
  int *v20; // [esp+20h] [ebp-10h]
  char v21[4]; // [esp+28h] [ebp-8h] BYREF
  int v22; // [esp+2Ch] [ebp-4h] BYREF
  int v23; // [esp+38h] [ebp+8h]

  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 340))(this);
  if ( (uint8_t)sub_546840(*v3) == 0
    && (*(uint32_t *)(dword_8F7A24 + 12) != 7
     || (v4 = *(this + 72)) == -1
     || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) == v4) )
  {
    v5 = *this;
    v22 = 7;
    v6 = (*(int (/*thiscall*/ **)(int *))(v5 + 340))(this);
    if ( *(uint32_t *)sub_472E30(v21, &v22) != *(uint32_t *)(v6 + 196) )
    {
      sub_44E8D0((char *)dword_8F8528, (void *)0xF, 0, 0);
      return;
    }
    v7 = *this;
    v22 = 8;
    v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 340))(this);
    if ( *(uint32_t *)sub_472E30(v21, &v22) != *(uint32_t *)(v8 + 196) )
    {
      sub_522E20();
      return;
    }
    if ( *((uint8_t *)this + 296) != 0 )
    {
      v9 = *(this + 73);
      v10 = 0;
      if ( v9 != 0 )
      {
        if ( v9 == 1 )
        {
          sub_47CC80(v18, *(this + 71));
          v12 = v19;
          if ( v19 != v20 )
          {
            while ( *(uint8_t *)(*v12 + 320) == 0 || *(uint8_t *)(*v12 + 120) == 0 )
            {
              if ( ++v12 == v20 )
              {
                v13 = (void **)v18;
                goto LABEL_33;
              }
            }
            v10 = *v12;
          }
          v13 = (void **)v18;
        }
        else
        {
          if ( v9 != 2 )
            return;
          sub_47CC80(v15, *(this + 71));
          v14 = v16;
          if ( v16 != v17 )
          {
            while ( *(uint8_t *)(*v14 + 320) == 0 || *(uint32_t *)(*v14 + 116) != 2 )
            {
              if ( ++v14 == v17 )
                goto LABEL_32;
            }
            v10 = *v14;
          }
LABEL_32:
          v13 = (void **)v15;
        }
LABEL_33:
        sub_5E5260(v13);
      }
      else
      {
        v11 = 0;
        v23 = sub_461730(dword_8F8540);
        if ( v23 <= 0 )
          return;
        while ( 1 )
        {
          v10 = sub_463ED0(v11);
          if ( *(uint8_t *)(v10 + 320) != 0 && *(uint32_t *)(v10 + 128) == *(this + 71) && sub_463F10(v11) == 0 )
            break;
          if ( ++v11 >= v23 )
            return;
        }
      }
      if ( v10 != 0 )
      {
        sub_5540D0((void *)1, *(this + 71));
        sub_44BBA0(7, 0);
        sub_552BD0(*((uint32_t **)dword_8F8528 + 22), v10);
        sub_44BBA0(8, 0);
        *(uint8_t *)(v10 + 320) = 0;
      }
    }
    else
    {
      sub_526BF0(this, a2);
    }
  }
}


// ------------------------------------------------------------
// 0x5681C0 CNRDNpc__vmt14C —— CNRDNpc__vmt14C 表现槽（567C10 + 472E30/50D910/493400/4939E0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDNpc__vmt14C(int *this)
{
  int v2; // edx
  int v3; // edi
  int **v4; // eax
  int v5; // eax
  int *v7; // [esp+4h] [ebp-8h] BYREF
  int v8; // [esp+8h] [ebp-4h] BYREF

  nullsub_3();
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
    sub_567C10(this);
  v2 = *this;
  v8 = 7;
  v3 = (*(int (/*thiscall*/ **)(int *))(v2 + 340))(this);
  v4 = sub_472E30((int **)(v3 + 192), &v7, &v8);
  if ( *v4 != *(int **)(v3 + 196) )
  {
    v5 = sub_50D910();
    sub_493400(*(this + 34), v5);
    LOBYTE(v4) = sub_4939E0(*(this + 34), 1);
  }
  return (char)v4;
}



// ------------------------------------------------------------
// 0x568240 sub_568240 —— 对话数据（40BF00/42FCB0/431920）
// ------------------------------------------------------------
int /*thiscall*/ sub_568240(int this)
{
  int v2; // esi
  int v3; // eax
  const char *v4; // esi

  v2 = this + 72;
  if ( sub_40BF00((std::_String_base *)(this + 72), 0, *(uint32_t *)(this + 92), szPassword, 0) == 0 )
    return 0;
  v3 = sub_42FCB0(228);
  if ( v3 == 0 )
    return 0;
  if ( *(uint32_t *)(v2 + 24) < 0x10u )
    v4 = (const char *)(v2 + 4);
  else
    v4 = *(const char **)(v2 + 4);
  if ( *(uint32_t *)(this + 332) < 0x10u )
    return sub_431920(v3, (const char *)(this + 312), v4, 1);
  else
    return sub_431920(v3, *(const char **)(this + 312), v4, 1);
}



// ------------------------------------------------------------
// 0x568310 sub_568310 —— 对话表现（56CFE0/568240/4924C0/4918E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_568310(int *this, int ArgList)
{
  int v3; // eax
  int v4; // edi
  int result; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax

  *(this + 71) = ArgList;
  v3 = sub_56CFE0(ArgList);
  v4 = v3;
  if ( v3 == 0 )
    return off_77F3FC("NPC CREATE FAIL! INDEX %d", ArgList);
  v6 = *this;
  v7 = sub_568240(v3);
  (*(void (/*thiscall*/ **)(int *, int))(v6 + 92))(this, v7);
  if ( *(this + 34) != 0 )
  {
    v8 = sub_4924C0(0);
    *(this + 40) = sub_4918E0(v8, 2);
  }
  result = *(uint32_t *)(v4 + 188);
  *(this + 72) = result;
  return result;
}



// ============================================================
// 【分区 19】副本信息窗 CNRDDungeonInfoWindow（0x5683A0-0x569020）
// vmtC 打开（476B60 副本数据 + 69C340 系）；vmt30/vmt0/vmt10。
// ============================================================
// ------------------------------------------------------------
// 0x5683A0 sub_5683A0 —— 副本信息数据（17 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5683A0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 10) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5683C0 CNRDDungeonInfoWindow__vmt10 —— CNRDDungeonInfoWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDDungeonInfoWindow__vmt10()
{
  dword_795314 = -1;
}



// ------------------------------------------------------------
// 0x5683D0 CNRDDungeonInfoWindow__vmt30 —— CNRDDungeonInfoWindow__vmt30 槽（69A5F0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDDungeonInfoWindow__vmt30(void *this, int a2, int a3, int a4, int a5)
{
  int v6; // edi
  int v7; // ebx
  uint32_t *v8; // eax

  v6 = a2 - ((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 56))(this) - a4) / 2;
  v7 = a3 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 60))(this);
  if ( v6 < 0 )
    v6 = 0;
  if ( v6 + (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 56))(this) > 640 )
    v6 = 640 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 56))(this);
  if ( v7 < 0 )
  {
    v7 = a3 + a5;
    if ( a3 + a5 + (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 60))(this) > 480 )
      v7 = 0;
  }
  v8 = (uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 36))(this);
  return sub_69A5F0(v8, v6, v7);
}



// ------------------------------------------------------------
// 0x568460 CNRDDungeonInfoWindow__vmt0 —— CNRDDungeonInfoWindow__vmt0 构造（554510/418DD0/69A110/699FC0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDDungeonInfoWindow__vmt0(int *this, int a2)
{
  int result; // eax
  int v4; // eax
  int v5; // ebx
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // [esp-10h] [ebp-1Ch]
  int v12; // [esp+4h] [ebp-8h]
  int v13; // [esp+14h] [ebp+8h]

  result = a2;
  if ( a2 == *(this + 2) )
  {
    sub_554510(*(uint32_t *)(a2 + 20), *(uint32_t *)(a2 + 24), *(this + 5), *(this + 6), *(this + 7), *(this + 8), -1);
    v4 = *(this + 2);
    v5 = *(uint32_t *)(v4 + 20);
    v6 = *(uint32_t *)(v4 + 24) - 14;
    v7 = sub_418DD0(0);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v5, v6, dword_79C0B0);
    v12 = v6 + 24;
    sub_69A110(v5 + 150, v6 + 24, *(this + 11), -1);
    v13 = sub_418DD0(11);
    v8 = sub_699FC0(*(this + 11));
    if ( v13 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v13 + 152))(v13, v8 + v5 + 150, v6 + 28, dword_79C0B0);
    v9 = *(uint32_t *)(sub_418DD0(11) + 20);
    v11 = *(this + 12);
    v10 = sub_699FC0(*(this + 11));
    return sub_69A110(v9 + v10 + v5 + 150, v12, v11, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x568570 CNRDDungeonInfoWindow__vmtC —— CNRDDungeonInfoWindow__vmtC 打开槽（476B60 副本数据 + 69C340 系 + 4F2CE0/422E70）
// ------------------------------------------------------------
char /*thiscall*/ CNRDDungeonInfoWindow__vmtC(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  uint32_t *v5; // eax
  int v6; // ecx
  char *v7; // eax
  char *v8; // eax
  uint32_t *v9; // eax
  unsigned int v10; // ecx
  char *v11; // eax
  char *v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // esi
  int v17; // [esp-8h] [ebp-114h]
  int v18; // [esp-4h] [ebp-110h]
  char Buffer[256]; // [esp+8h] [ebp-104h] BYREF
  int v20; // [esp+108h] [ebp-4h]

  v20 = dword_796E50;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 1);
  dword_795314 = a3;
  v4 = *((uint32_t *)sub_476B60(a3) + 28);
  if ( v4 > 2 )
  {
    if ( v4 > 4 )
      *(this + 11) = v4 - 2;
    else
      *(this + 11) = v4 - 1;
  }
  else
  {
    *(this + 11) = v4;
  }
  *(this + 12) = v4 + 1;
  sub_69C340(-1);
  v5 = sub_476B60(dword_795314);
  v6 = v5[24];
  v7 = (char *)(v5 + 24);
  if ( v6 != 0xFFFF )
  {
    v18 = *((uint32_t *)v7 + 1);
    if ( v7[8] != 0 )
    {
      v17 = sub_4F2CE0(v6);
      v8 = sub_422E70(2101);
    }
    else
    {
      v17 = sub_4F2CE0(v6);
      v8 = sub_422E70(2102);
    }
    sprintf(Buffer, v8, v17, v18);
    sub_69C440(-16711681);
    sub_69C360(Buffer, 0);
    sub_69C360(" ", 0);
  }
  sub_69C440(-1);
  v9 = sub_476B60(dword_795314);
  v10 = v9[14];
  v11 = (char *)(v9 + 8);
  if ( v10 < 0x10 )
    v12 = v11 + 4;
  else
    v12 = *((char **)v11 + 1);
  sub_69C360(v12, 0);
  v13 = *this;
  v14 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v13 + 24))(this, 20, v14 + 2);
  v15 = *(this + 2);
  *(uint32_t *)(v15 + 28) = 0;
  *(uint32_t *)(v15 + 32) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x5686D0 sub_5686D0 —— 副本信息页绘制（69A5F0/69C460/69C480/423B30）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5686D0(int *this)
{
  int v2; // edx
  uint8_t *v3; // eax
  uint8_t *result; // eax

  v2 = *this;
  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 192);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(240, 2048);
  sub_69A5F0((uint32_t *)*(this + 3), 6, 32);
  sub_69C460(1);
  sub_69C480(-16777216);
  v3 = operator new(0x2Cu);
  if ( v3 != nullptr )
    result = sub_423B30(v3, dword_79C0B0, *(this + 9), 0, 2);
  else
    result = nullptr;
  *(this + 10) = (int)result;
  result[24] = 0;
  return result;
}



// ------------------------------------------------------------
// 0x568780 sub_568780 —— 频道数据（47 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_568780(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 153) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 153) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 153) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 153) == 0 );
        if ( *(uint8_t *)(result + 153) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 153) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x568800 sub_568800 —— 频道数据 2（27 行）
// ------------------------------------------------------------
int */*thiscall*/ sub_568800(uint32_t *this, uint32_t *a2)
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);
  v3 = (int *)result[1];
  while ( *((uint8_t *)v3 + 153) == 0 )
  {
    if ( v3[3] >= *a2 )
    {
      result = v3;
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x568840 sub_568840 —— 频道数据 3（47 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_568840(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 29) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 29) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 29) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 29) == 0 );
        if ( *(uint8_t *)(result + 29) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 29) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5688A0 sub_5688A0 —— 频道数据 4（47 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5688A0(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 85) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 85) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 85) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 85) == 0 );
        if ( *(uint8_t *)(result + 85) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 85) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x568900 sub_568900 —— 频道数据 5（21 行）
// ------------------------------------------------------------
uint32_t *sub_568900()
{
  uint32_t *result; // eax

  result = operator new(0x9Cu);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 152) = 1;
  *((uint8_t *)result + 153) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x568940 sub_568940 —— 频道条目（36 行）
// ------------------------------------------------------------
int **/*thiscall*/ sub_568940(int **this, int **a2, uint32_t *a3)
{
  int *v3; // edx
  int *v4; // eax

  v3 = *(this + 1);
  v4 = (int *)v3[1];
  while ( *((uint8_t *)v4 + 29) == 0 )
  {
    if ( v4[3] >= *a3 )
    {
      v3 = v4;
      v4 = (int *)*v4;
    }
    else
    {
      v4 = (int *)v4[2];
    }
  }
  if ( v3 == *(this + 1) || *a3 < v3[3] )
  {
    *a2 = *(this + 1);
    return a2;
  }
  else
  {
    *a2 = v3;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x5689B0 sub_5689B0 —— 频道条目 2（72 行）
// ------------------------------------------------------------
int */*thiscall*/ sub_5689B0(int **this, int a2)
{
  int *v2; // ecx
  int *v3; // eax
  unsigned int v4; // edx
  unsigned int v5; // esi
  const char **v6; // ecx
  const char *v7; // edi
  unsigned int v8; // ebx
  int v9; // ecx
  const char *v10; // esi
  int v11; // edx
  bool v12; // sf
  unsigned int v14; // [esp+0h] [ebp-Ch]
  const char **i; // [esp+4h] [ebp-8h]
  int *v16; // [esp+8h] [ebp-4h]
  unsigned int v17; // [esp+14h] [ebp+8h]

  v2 = *(this + 1);
  v3 = (int *)v2[1];
  v16 = v2;
  if ( *((uint8_t *)v3 + 85) == 0 )
  {
    v4 = *(uint32_t *)(a2 + 24);
    v5 = *(uint32_t *)(a2 + 20);
    v6 = (const char **)(a2 + 4);
    v17 = v5;
    v14 = v4;
    for ( i = v6; ; v6 = i )
    {
      if ( v14 < 0x10 )
        v7 = (const char *)v6;
      else
        v7 = *v6;
      v8 = v3[8];
      if ( v8 == 0 )
        goto LABEL_14;
      v9 = v3[8];
      if ( v8 >= v5 )
        v9 = v5;
      v10 = (unsigned int)v3[9] < 0x10 ? (const char *)(v3 + 4) : (const char *)v3[4];
      v11 = memcmp(v10, v7, v9);
      v12 = v11 < 0;
      v5 = v17;
      if ( v11 == 0 )
      {
LABEL_14:
        if ( v8 < v5 )
          goto LABEL_17;
        v12 = false;
      }
      if ( v12 )
      {
LABEL_17:
        v3 = (int *)v3[2];
        goto LABEL_19;
      }
      v16 = v3;
      v3 = (int *)*v3;
LABEL_19:
      if ( *((uint8_t *)v3 + 85) != 0 )
        return v16;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x568A70 sub_568A70 —— 频道条目组装（568940/568800）
// ------------------------------------------------------------
int */*thiscall*/ sub_568A70(int **this, int *a2, int *a3)
{
  int **v4; // eax
  int *v5; // edi
  int v6; // ebx
  int *v7; // eax
  int *v8; // esi
  int **v9; // eax
  int *v10; // eax
  int *v12; // [esp+8h] [ebp-4h] BYREF

  a2 = (int *)(uint8_t)a2;
  v4 = sub_568940(this + 3, &v12, &a2);
  v5 = *v4;
  if ( *v4 == *(this + 4) )
    return nullptr;
  v6 = (int)a3;
  a2 = a3;
  v7 = sub_568800(v5 + 4, &a2);
  v8 = (int *)v5[5];
  a2 = v7;
  if ( v7 == v8 || v6 < v7[3] )
  {
    a3 = v8;
    v9 = &a3;
  }
  else
  {
    v9 = &a2;
  }
  v10 = *v9;
  if ( v10 == (int *)v5[5] )
    return nullptr;
  else
    return v10 + 4;
}



// ------------------------------------------------------------
// 0x568AF0 sub_568AF0 —— 频道条目 3（5689B0/40BF00）
// ------------------------------------------------------------
int **/*thiscall*/ sub_568AF0(int **this, int **a2, unsigned int *a3)
{
  int *v5; // eax
  unsigned int v6; // ecx
  const char *v7; // eax
  int *v9; // [esp+18h] [ebp+Ch]

  v5 = sub_5689B0(this, (int)a3);
  v9 = v5;
  if ( v5 == *(this + 1)
    || ((v6 = v5[8], (unsigned int)v5[9] < 0x10) ? (v7 = (const char *)(v5 + 4)) : (v7 = (const char *)v5[4]),
        sub_40BF00((std::_String_base *)a3, 0, a3[5], v7, v6) < 0) )
  {
    *a2 = *(this + 1);
    return a2;
  }
  else
  {
    *a2 = v9;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x568B60 sub_568B60 —— 频道字符串（4014D0）
// ------------------------------------------------------------
int /*thiscall*/ sub_568B60(int this, int a2)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((std::_String_base *)this, a2, 0, -1);
  *(uint32_t *)(this + 28) = *(uint32_t *)(a2 + 28);
  *(uint32_t *)(this + 56) = 15;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 36) = 0;
  sub_4014D0((std::_String_base *)(this + 32), a2 + 32, 0, -1);
  *(uint32_t *)(this + 84) = 15;
  *(uint32_t *)(this + 80) = 0;
  *(uint8_t *)(this + 64) = 0;
  sub_4014D0((std::_String_base *)(this + 60), a2 + 60, 0, -1);
  *(uint32_t *)(this + 88) = *(uint32_t *)(a2 + 88);
  *(uint8_t *)(this + 92) = *(uint8_t *)(a2 + 92);
  qmemcpy((void *)(this + 96), (const void *)(a2 + 96), 0x28u);
  return this;
}



// ------------------------------------------------------------
// 0x568C20 sub_568C20 —— 频道字符串 2（4014D0）
// ------------------------------------------------------------
int /*thiscall*/ sub_568C20(int this, int a2)
{
  sub_4014D0((std::_String_base *)this, a2, 0, -1);
  *(uint32_t *)(this + 28) = *(uint32_t *)(a2 + 28);
  sub_4014D0((std::_String_base *)(this + 32), a2 + 32, 0, -1);
  sub_4014D0((std::_String_base *)(this + 60), a2 + 60, 0, -1);
  *(uint32_t *)(this + 88) = *(uint32_t *)(a2 + 88);
  *(uint8_t *)(this + 92) = *(uint8_t *)(a2 + 92);
  *(uint32_t *)(this + 96) = *(uint32_t *)(a2 + 96);
  *(uint32_t *)(this + 100) = *(uint32_t *)(a2 + 100);
  *(uint32_t *)(this + 104) = *(uint32_t *)(a2 + 104);
  *(uint32_t *)(this + 108) = *(uint32_t *)(a2 + 108);
  *(uint32_t *)(this + 112) = *(uint32_t *)(a2 + 112);
  *(uint32_t *)(this + 116) = *(uint32_t *)(a2 + 116);
  *(uint32_t *)(this + 120) = *(uint32_t *)(a2 + 120);
  *(uint32_t *)(this + 124) = *(uint32_t *)(a2 + 124);
  *(uint32_t *)(this + 128) = *(uint32_t *)(a2 + 128);
  *(uint32_t *)(this + 132) = *(uint32_t *)(a2 + 132);
  return this;
}



// ------------------------------------------------------------
// 0x568CC0 sub_568CC0 —— 频道字符串 3（568B60）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_568CC0(int a1, int a2, int a3, uint32_t *a4, char a5)
{
  uint32_t *v5; // eax
  uint32_t *v6; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  v5 = operator new(0x9Cu);
  v6 = v5;
  v8[4] = v5;
  v8[8] = (void *)1;
  v8[3] = v5;
  if ( v5 != nullptr )
  {
    *v5 = a1;
    v5[1] = a2;
    v5[2] = a3;
    v5[3] = *a4;
    sub_568B60((int)(v5 + 4), (int)(a4 + 1));
    *((uint8_t *)v6 + 152) = a5;
    *((uint8_t *)v6 + 153) = 0;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x568D70 sub_568D70 —— 频道字符串 4（4014D0/435020）
// ------------------------------------------------------------
int /*thiscall*/ sub_568D70(int this, int a2)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((std::_String_base *)this, a2, 0, -1);
  sub_435020((uint32_t *)(this + 28), (uint32_t *)(a2 + 28));
  return this;
}



// ------------------------------------------------------------
// 0x568DE0 sub_568DE0 —— 频道列表装配（4015C0/401740/568CC0/46ECF0/46E740，113 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_568DE0(int *this, uint32_t *a2, char a3, uint32_t *a4, uint32_t *a5)
{
  uint32_t *v6; // ecx
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int *v10; // eax
  int v11; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  void **pExceptionObject; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v17[20]; // [esp+34h] [ebp-28h] BYREF
  int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]
  uint32_t *v21; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0x1D41D40 )
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
  v6 = sub_568CC0(*(this + 1), (int)a4, *(this + 1), a5, 0);
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
  v10 = v6 + 1;
  v11 = (int)v6;
  if ( *(uint8_t *)(v6[1] + 152) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 152) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_46ECF0(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 152) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 152) = 0;
          sub_46E740(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 152) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_46E740(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 152) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 152) = 0;
        sub_46ECF0(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 152) = 1;
      *(uint8_t *)(v14 + 152) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 152) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 152) != 0 )
      {
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 152) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x568FB0 sub_568FB0 —— 频道文本（4014D0/568D70）
// ------------------------------------------------------------
int /*thiscall*/ sub_568FB0(int this, int a2)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((std::_String_base *)this, a2, 0, -1);
  sub_568D70(this + 28, a2 + 28);
  return this;
}



// ============================================================
// 【分区 20】频道信息与选择（0x569020-0x56A670）
// 主装载 0x569F40（311 行）=importChannelScript 装载 Etc/channel_info.etc：
// 442A10/443430/4423D0/442480 .etc 解析 + 46F440/46F490/472520/46F6E0/
// 46E3F0 系频道数据 + 日志 "importChannelScript - can't find
// channel_info.etc"；0x56CFE0=频道选择主入口（191 行）。
// ============================================================
// ------------------------------------------------------------
// 0x569020 sub_569020 —— 频道文本 2（4014D0/568D70）
// ------------------------------------------------------------
int /*thiscall*/ sub_569020(int this, int a2, int a3)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((std::_String_base *)this, a2, 0, -1);
  sub_568D70(this + 28, a3);
  return this;
}



// ------------------------------------------------------------
// 0x569090 sub_569090 —— 频道列表装配 2（568DE0/568780）
// ------------------------------------------------------------
int /*thiscall*/ sub_569090(int *this, int a2, uint32_t *a3)
{
  uint32_t *v3; // ebx
  uint32_t *v5; // esi
  int *v6; // eax
  bool v7; // cl
  int v8; // edx
  uint32_t *v9; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  v3 = a3;
  v5 = (uint32_t *)*(this + 1);
  v6 = (int *)v5[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 153) == 0 )
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
    while ( *((uint8_t *)v6 + 153) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_568DE0(this, &a3, 1, v5, v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_568780(&a3);
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
    v12 = *sub_568DE0(this, &a3, v13, v5, v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x569150 sub_569150 —— 频道条目 4（568CC0）
// ------------------------------------------------------------
void */*thiscall*/ sub_569150(void **this, int *a2, int a3)
{
  char v3; // al
  uint32_t *v4; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);
  v3 = *((uint8_t *)a2 + 153);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    v4 = sub_568CC0((int)*(this + 1), a3, (int)*(this + 1), a2 + 3, *((uint8_t *)a2 + 152));
    if ( *((uint8_t *)Block + 153) != 0 )
      Block = v4;
    v6 = *a2;
    v10 = 0;
    *v4 = sub_569150(v6, v4);
    v4[2] = sub_569150(a2[2], v4);
  }
  return Block;
}



// ------------------------------------------------------------
// 0x569210 sub_569210 —— 频道列表装配 3（568DE0/568780/46E7B0/569090）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_569210(int this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v6; // eax
  uint32_t *v7; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_568DE0((int *)this, a2, 1, *(uint32_t **)(this + 4), a4);
    return a2;
  }
  v6 = *(uint32_t **)(this + 4);
  v7 = a4;
  if ( a3 == (uint32_t *)*v6 )
  {
    if ( *a4 < a3[3] )
    {
      sub_568DE0((int *)this, a2, 1, a3, a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( a3 == v6 )
  {
    v8 = (uint32_t *)v6[2];
    if ( v8[3] < *a4 )
    {
      sub_568DE0((int *)this, a2, 0, v8, a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( *a4 >= a3[3] || (a4 = a3, sub_568780(&a4), a4[3] >= *v7) )
  {
    if ( a3[3] >= *v7 || (a4 = a3, sub_46E7B0((int *)&a4), a4 != *(uint32_t **)(this + 4)) && *v7 >= a4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_569090((int *)this, (int)v10, v7);
      *a2 = v9;
      return a2;
    }
    if ( *(uint8_t *)(a3[2] + 153) != 0 )
      sub_568DE0((int *)this, a2, 0, a3, v7);
    else
      sub_568DE0((int *)this, a2, 1, a4, v7);
    return a2;
  }
  else
  {
    if ( *(uint8_t *)(a4[2] + 153) != 0 )
      sub_568DE0((int *)this, a2, 0, a4, v7);
    else
      sub_568DE0((int *)this, a2, 1, a3, v7);
    return a2;
  }
}



// ------------------------------------------------------------
// 0x569370 sub_569370 —— 频道条目 5（569150）
// ------------------------------------------------------------
int */*thiscall*/ sub_569370(int this, int a2)
{
  int v3; // edi
  int **v4; // edx
  int *result; // eax
  int *v6; // ecx
  int v7; // esi
  int **v8; // ecx

  v3 = *(uint32_t *)(this + 4);
  *(uint32_t *)(v3 + 4) = sub_569150((void **)this, *(int **)(*(uint32_t *)(a2 + 4) + 4), v3);
  *(uint32_t *)(this + 8) = *(uint32_t *)(a2 + 8);
  v4 = *(int ***)(this + 4);
  result = v4[1];
  if ( *((uint8_t *)result + 153) != 0 )
  {
    *v4 = (int *)v4;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);
  }
  else
  {
    v6 = (int *)*result;
    if ( *(uint8_t *)(*result + 153) == 0 )
    {
      do
      {
        result = v6;
        v6 = (int *)*v6;
      }
      while ( *((uint8_t *)v6 + 153) == 0 );
    }
    *v4 = result;
    v7 = *(uint32_t *)(this + 4);
    v8 = *(int ***)(v7 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 153) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(v7 + 8) = v8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x569400 sub_569400 —— 频道文本 3（568FB0）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_569400(int a1, int a2, int a3, int a4, char a5)
{
  uint32_t *v5; // eax
  uint32_t *v6; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  v5 = operator new(0x58u);
  v6 = v5;
  v8[4] = v5;
  v8[8] = (void *)1;
  v8[3] = v5;
  if ( v5 != nullptr )
  {
    *v5 = a1;
    v5[1] = a2;
    v5[2] = a3;
    sub_568FB0((int)(v5 + 3), a4);
    *((uint8_t *)v6 + 84) = a5;
    *((uint8_t *)v6 + 85) = 0;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x5694A0 sub_5694A0 —— 频道汇总件（568800/568B60/569210/46F490）
// ------------------------------------------------------------
int */*thiscall*/ sub_5694A0(uint32_t *this, int *a2)
{
  int *v2; // ebx
  int *v4; // edi
  int v5; // esi
  int v7; // [esp+Ch] [ebp-120h] BYREF
  uint8_t v8[136]; // [esp+10h] [ebp-11Ch] BYREF
  uint8_t v9[20]; // [esp+98h] [ebp-94h] BYREF
  int v10; // [esp+ACh] [ebp-80h]
  int v11; // [esp+B0h] [ebp-7Ch]
  int v12; // [esp+B4h] [ebp-78h]
  char v13; // [esp+BCh] [ebp-70h]
  int v14; // [esp+CCh] [ebp-60h]
  int v15; // [esp+D0h] [ebp-5Ch]
  char v16; // [esp+D8h] [ebp-54h]
  int v17; // [esp+E8h] [ebp-44h]
  int v18; // [esp+ECh] [ebp-40h]
  int v19; // [esp+F0h] [ebp-3Ch]
  char v20; // [esp+F4h] [ebp-38h]
  int v21; // [esp+128h] [ebp-4h]

  v2 = a2;
  v4 = sub_568800(this, a2);
  if ( v4 != (int *)*(this + 1) && *v2 >= v4[3] )
    return v4 + 4;
  v11 = 15;
  v10 = 0;
  v9[4] = 0;
  v15 = 15;
  v14 = 0;
  v13 = 0;
  v18 = 15;
  v17 = 0;
  v16 = 0;
  v12 = 0;
  v19 = 0;
  v20 = 0;
  v7 = *v2;
  v21 = 0;
  sub_568B60((int)v8, (int)v9);
  LOBYTE(v21) = 1;
  v5 = *sub_569210((int)this, &a2, v4, &v7);
  sub_46F490((int)v8);
  sub_46F490((int)v9);
  return (int *)(v5 + 16);
}



// ------------------------------------------------------------
// 0x569590 sub_569590 —— 频道负载装配（4015C0/401740/569400/46E3F0/46E490，113 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_569590(int *this, uint32_t *a2, char a3, uint32_t *a4, int a5)
{
  uint32_t *v6; // ecx
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int *v10; // eax
  int v11; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  void **pExceptionObject; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v17[20]; // [esp+34h] [ebp-28h] BYREF
  int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]
  uint32_t *v21; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0x38E38E2 )
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
  v6 = sub_569400(*(this + 1), (int)a4, *(this + 1), a5, 0);
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
  v10 = v6 + 1;
  v11 = (int)v6;
  if ( *(uint8_t *)(v6[1] + 84) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 84) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_46E3F0(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 84) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 84) = 0;
          sub_46E490(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 84) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_46E490(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 84) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 84) = 0;
        sub_46E3F0(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 84) = 1;
      *(uint8_t *)(v14 + 84) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 84) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 84) != 0 )
      {
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 84) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x569740 sub_569740 —— 频道条目 6（568900/569370）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_569740(uint32_t *this, int a2)
{
  uint32_t *v3; // eax
  uint32_t v5[8]; // [esp+0h] [ebp-20h] BYREF

  v5[4] = v5;
  v5[3] = this;
  v3 = sub_568900();
  *(this + 1) = v3;
  *((uint8_t *)v3 + 153) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  v5[7] = 0;
  sub_569370((int)this, a2);
  return this;
}



// ------------------------------------------------------------
// 0x5697D0 sub_5697D0 —— 频道人数/负载装配（569590/5688A0/40BF00，102 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5697D0(int *this, int a2, uint32_t *a3)
{
  int v3; // ebx
  uint32_t *v4; // esi
  char v5; // al
  uint32_t *v6; // edi
  unsigned int i; // esi
  unsigned int v8; // ecx
  const char *v9; // eax
  unsigned int v10; // edx
  const char *v11; // esi
  int v12; // eax
  bool v13; // sf
  unsigned int v14; // esi
  int v15; // eax
  uint32_t *v16; // ebx
  const char *v18; // eax
  uint32_t *v19; // [esp+Ch] [ebp-14h]
  int *v20; // [esp+18h] [ebp-8h]
  char v21; // [esp+1Ch] [ebp-4h]

  v3 = *(uint32_t *)(*(this + 1) + 4);
  v4 = (uint32_t *)*(this + 1);
  v5 = 1;
  v6 = a3;
  v20 = this;
  v21 = 1;
  if ( *(uint8_t *)(v3 + 85) == 0 )
  {
    for ( i = a3[5]; ; i = a3[5] )
    {
      v8 = *(uint32_t *)(v3 + 32);
      v19 = (uint32_t *)v3;
      if ( *(uint32_t *)(v3 + 36) < 0x10u )
        v9 = (const char *)(v3 + 16);
      else
        v9 = *(const char **)(v3 + 16);
      v10 = a3[5];
      if ( i < v10 )
        v10 = i;
      if ( v10 == 0 )
        goto LABEL_16;
      if ( v10 < v8 )
        v8 = v10;
      v11 = v6[6] < 0x10u ? (const char *)(v6 + 1) : (const char *)v6[1];
      v12 = memcmp(v11, v9, v8);
      v13 = v12 < 0;
      v6 = a3;
      if ( v12 == 0 )
      {
LABEL_16:
        v14 = *(uint32_t *)(v3 + 32);
        if ( v10 >= v14 )
          v15 = v10 != v14;
        else
          v15 = -1;
        v13 = v15 < 0;
      }
      v5 = v13;
      v21 = v13;
      v3 = v13 ? *(uint32_t *)v3 : *(uint32_t *)(v3 + 8);
      if ( *(uint8_t *)(v3 + 85) != 0 )
        break;
    }
    v4 = v19;
    this = v20;
  }
  v16 = v4;
  a3 = v4;
  if ( v5 != 0 )
  {
    if ( v4 == *(uint32_t **)*(this + 1) )
    {
      *(uint32_t *)a2 = *sub_569590(this, &a3, 1, v4, (int)v6);
      *(uint8_t *)(a2 + 4) = 1;
      return a2;
    }
    sub_5688A0(&a3);
    v16 = a3;
  }
  if ( v6[6] < 0x10u )
    v18 = (const char *)(v6 + 1);
  else
    v18 = (const char *)v6[1];
  if ( sub_40BF00((std::_String_base *)(v16 + 3), 0, v16[8], v18, v6[5]) >= 0 )
  {
    *(uint32_t *)a2 = v16;
    *(uint8_t *)(a2 + 4) = 0;
  }
  else
  {
    *(uint32_t *)a2 = *sub_569590(v20, &a3, v21, v4, (int)v6);
    *(uint8_t *)(a2 + 4) = 1;
  }
  return a2;
}



// ------------------------------------------------------------
// 0x569930 sub_569930 —— 频道负载装配 2（569590/40C160/5688A0/46E5F0/5697D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_569930(int this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_569590((int *)this, a2, 1, *(uint32_t **)(this + 4), (int)a4);
    return a2;
  }
  v6 = *(uint32_t **)(this + 4);
  v7 = a4;
  if ( a3 == (uint32_t *)*v6 )
  {
    if ( (uint8_t)sub_40C160(a4, a3 + 3) != 0 )
    {
      sub_569590((int *)this, a2, 1, a3, (int)v7);
      return a2;
    }
    goto LABEL_23;
  }
  if ( a3 == v6 )
  {
    if ( (uint8_t)sub_40C160(v6[2] + 12, a4) != 0 )
    {
      sub_569590((int *)this, a2, 0, *(uint32_t **)(*(uint32_t *)(this + 4) + 8), (int)v7);
      return a2;
    }
    goto LABEL_23;
  }
  if ( (uint8_t)sub_40C160(a4, a3 + 3) != 0 )
  {
    a4 = a3;
    sub_5688A0(&a4);
    if ( (uint8_t)sub_40C160(a4 + 3, v7) != 0 )
    {
      if ( *(uint8_t *)(a4[2] + 85) != 0 )
        sub_569590((int *)this, a2, 0, a4, (int)v7);
      else
        sub_569590((int *)this, a2, 1, a3, (int)v7);
      return a2;
    }
  }
  if ( (uint8_t)sub_40C160(a3 + 3, v7) == 0 )
    goto LABEL_23;
  a4 = a3;
  sub_46E5F0((int *)&a4);
  v8 = a4;
  if ( a4 != *(uint32_t **)(this + 4) )
  {
    if ( (uint8_t)sub_40C160(v7, a4 + 3) != 0 )
    {
      v8 = a4;
      goto LABEL_19;
    }
LABEL_23:
    v9 = *(uint32_t *)sub_5697D0((int *)this, (int)v10, v7);
    *a2 = v9;
    return a2;
  }
LABEL_19:
  if ( *(uint8_t *)(a3[2] + 85) != 0 )
    sub_569590((int *)this, a2, 0, a3, (int)v7);
  else
    sub_569590((int *)this, a2, 1, v8, (int)v7);
  return a2;
}



// ------------------------------------------------------------
// 0x569AD0 sub_569AD0 —— 频道条目 7（5689B0/40BF00/569020/569930/46F6E0）
// ------------------------------------------------------------
int */*thiscall*/ sub_569AD0(int this, int a2)
{
  unsigned int *v2; // ebx
  int *v4; // esi
  const char *v5; // eax
  uint32_t *v6; // eax
  uint8_t v8[72]; // [esp+Ch] [ebp-80h] BYREF
  uint8_t v9[4]; // [esp+54h] [ebp-38h] BYREF
  void *v10; // [esp+58h] [ebp-34h]
  int v11; // [esp+68h] [ebp-24h]
  unsigned int v12; // [esp+6Ch] [ebp-20h]
  void *Block; // [esp+74h] [ebp-18h]
  int v14; // [esp+78h] [ebp-14h]
  int v15; // [esp+7Ch] [ebp-10h]
  int v16; // [esp+88h] [ebp-4h]

  v2 = (unsigned int *)a2;
  v4 = sub_5689B0((int **)this, a2);
  if ( v4 == *(int **)(this + 4)
    || ((unsigned int)v4[9] < 0x10 ? (v5 = (const char *)(v4 + 4)) : (v5 = (const char *)v4[4]),
        sub_40BF00((std::_String_base *)v2, 0, v2[5], v5, v4[8]) < 0) )
  {
    v12 = 15;
    v11 = 0;
    LOBYTE(v10) = 0;
    Block = nullptr;
    v14 = 0;
    v15 = 0;
    v16 = 1;
    v6 = (uint32_t *)sub_569020((int)v8, (int)v2, (int)v9);
    LOBYTE(v16) = 2;
    v4 = (int *)*sub_569930(this, &a2, v4, v6);
    sub_46F6E0((int)v8);
    if ( Block != nullptr )
      j__free(Block);
    if ( v12 >= 0x10 )
      j__free(v10);
  }
  return v4 + 10;
}



// ------------------------------------------------------------
// 0x569BB0 sub_569BB0 —— 频道入口件（569740/472460）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_569BB0(uint32_t *a1, int a2, int ***a3, int ***Block)
{
  *a1 = a2;
  sub_569740(a1 + 1, (int)&a3);
  sub_472460(&a3, (int ***)&a2, *Block, (int **)Block);
  j__free(Block);
  return a1;
}



// ------------------------------------------------------------
// 0x569C30 sub_569C30 —— 频道入口件 2（569740）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_569C30(int a1, int a2, int a3, uint32_t *a4, char a5)
{
  uint32_t *v5; // eax
  uint32_t *v6; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  v5 = operator new(0x20u);
  v6 = v5;
  v8[4] = v5;
  v8[8] = (void *)1;
  v8[3] = v5;
  if ( v5 != nullptr )
  {
    *v5 = a1;
    v5[1] = a2;
    v5[2] = a3;
    v5[3] = *a4;
    sub_569740(v5 + 4, (int)(a4 + 1));
    *((uint8_t *)v6 + 28) = a5;
    *((uint8_t *)v6 + 29) = 0;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x569CD0 sub_569CD0 —— 频道人数装配（4015C0/401740/569C30/46E4F0/46E590，113 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_569CD0(int *this, uint32_t *a2, char a3, uint32_t *a4, uint32_t *a5)
{
  uint32_t *v6; // ecx
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int *v10; // eax
  int v11; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  void **pExceptionObject; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v17[20]; // [esp+34h] [ebp-28h] BYREF
  int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]
  uint32_t *v21; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0xFFFFFFE )
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
  v6 = sub_569C30(*(this + 1), (int)a4, *(this + 1), a5, 0);
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
  v10 = v6 + 1;
  v11 = (int)v6;
  if ( *(uint8_t *)(v6[1] + 28) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 28) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_46E4F0(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 28) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 28) = 0;
          sub_46E590(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 28) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_46E590(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 28) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 28) = 0;
        sub_46E4F0(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 28) = 1;
      *(uint8_t *)(v14 + 28) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 28) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 28) != 0 )
      {
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 28) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x569E80 sub_569E80 —— 频道汇总件 2（569CD0/568840）
// ------------------------------------------------------------
int /*thiscall*/ sub_569E80(int *this, int a2, uint32_t *a3)
{
  uint32_t *v3; // ebx
  uint32_t *v5; // esi
  int *v6; // eax
  bool v7; // cl
  int v8; // edx
  uint32_t *v9; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  v3 = a3;
  v5 = (uint32_t *)*(this + 1);
  v6 = (int *)v5[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 29) == 0 )
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
    while ( *((uint8_t *)v6 + 29) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_569CD0(this, &a3, 1, v5, v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_568840(&a3);
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
    v12 = *sub_569CD0(this, &a3, v13, v5, v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x569F40 sub_569F40 —— importChannelScript 主装载（311 行）：读取 Etc/channel_info.etc（442A10/443430/4423D0/442480 .etc 解析 + 40BF00 + 430C80 + 569AD0/4014D0/4ED3F0/568900/472520/46F490/569740/569BB0/569E80/472460/568800/423340/568AF0/568C20/501490）；找不到时日志 "importChannelScript - can't find channel_info.etc"
// ------------------------------------------------------------
// channel_info.etc 内含 [dungeon]/[server] 段（背景字符串证据），本函数即频道表初始化。
char /*cdecl*/ sub_569F40(int a1)
{
  int v1; // edi
  char *v2; // esi
  std::_String_base *v3; // esi
  int v4; // edi
  int v5; // esi
  void **v6; // eax
  void **v7; // eax
  int v8; // eax
  int v9; // esi
  int *v10; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  void *v17[10]; // [esp-1Ch] [ebp-174h] BYREF
  uint8_t v18[8]; // [esp+Ch] [ebp-14Ch] BYREF
  uint8_t v19[4]; // [esp+14h] [ebp-144h] BYREF
  uint8_t v20[4]; // [esp+18h] [ebp-140h] BYREF
  int v21; // [esp+1Ch] [ebp-13Ch] BYREF
  void *v22; // [esp+24h] [ebp-134h]
  int v23; // [esp+28h] [ebp-130h]
  void *v24; // [esp+2Ch] [ebp-12Ch] BYREF
  int v25; // [esp+30h] [ebp-128h] BYREF
  void *v26; // [esp+38h] [ebp-120h]
  int v27; // [esp+3Ch] [ebp-11Ch]
  uint8_t v28[4]; // [esp+40h] [ebp-118h] BYREF
  void **v29; // [esp+44h] [ebp-114h] BYREF
  int i; // [esp+48h] [ebp-110h] BYREF
  uint8_t v31[4]; // [esp+4Ch] [ebp-10Ch] BYREF
  void *v32; // [esp+50h] [ebp-108h]
  int v33; // [esp+54h] [ebp-104h]
  char v34; // [esp+5Ah] [ebp-FEh] BYREF
  char v35; // [esp+5Bh] [ebp-FDh] BYREF
  uint8_t v36[20]; // [esp+5Ch] [ebp-FCh] BYREF
  int v37; // [esp+70h] [ebp-E8h]
  int v38; // [esp+74h] [ebp-E4h]
  int v39; // [esp+78h] [ebp-E0h]
  uint32_t v40[7]; // [esp+7Ch] [ebp-DCh] BYREF
  uint8_t v41[20]; // [esp+98h] [ebp-C0h] BYREF
  int v42; // [esp+ACh] [ebp-ACh]
  int v43; // [esp+B0h] [ebp-A8h]
  int v44; // [esp+B4h] [ebp-A4h]
  char v45; // [esp+B8h] [ebp-A0h]
  float v46[10]; // [esp+BCh] [ebp-9Ch]
  uint8_t v47[20]; // [esp+E4h] [ebp-74h] BYREF
  int v48; // [esp+F8h] [ebp-60h]
  int v49; // [esp+FCh] [ebp-5Ch]
  uint8_t v50[4]; // [esp+100h] [ebp-58h] BYREF
  int v51; // [esp+104h] [ebp-54h]
  void *Src; // [esp+108h] [ebp-50h]
  int v53; // [esp+10Ch] [ebp-4Ch]
  uint8_t v54[4]; // [esp+110h] [ebp-48h] BYREF
  void *v55; // [esp+114h] [ebp-44h]
  int v56; // [esp+124h] [ebp-34h]
  unsigned int v57; // [esp+128h] [ebp-30h]
  void *v58[8]; // [esp+12Ch] [ebp-2Ch] BYREF
  int v59; // [esp+154h] [ebp-4h]

  v58[7] = (void *)dword_796E50;
  v58[6] = (void *)15;
  v58[5] = nullptr;
  LOBYTE(v58[1]) = 0;
  v59 = 0;
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"Etc/channel_info.etc") == 0 )
  {
    off_77F3FC("importChannelScript - can't find channel_info.etc");
    return 0;
  }
  if ( (uint8_t)sub_443430(v58) == 0 )
    goto LABEL_56;
  while ( 1 )
  {
    if ( sub_40BF00((std::_String_base *)v58, 0, (unsigned int)v58[5], "[dungeon]", 9u) == 0 )
    {
      v57 = 15;
      v56 = 0;
      LOBYTE(v55) = 0;
      v49 = 15;
      v48 = 0;
      v47[4] = 0;
      v51 = 0;
      Src = nullptr;
      v53 = 0;
      v17[6] = v54;
      LOBYTE(v59) = 3;
      if ( sub_443370() == 0 )
      {
        sub_46F440(v47);
        if ( v57 < 0x10 )
          goto LABEL_56;
        goto LABEL_41;
      }
      v17[6] = v47;
      if ( sub_443370() != 0 )
      {
        v1 = sub_4423D0(&v34);
        for ( i = v1; v34 != 0; i = v1 )
        {
          v2 = (char *)Src;
          if ( v51 != 0 && ((int)Src - v51) >> 2 < (unsigned int)((v53 - v51) >> 2) )
          {
            *(uint32_t *)Src = v1;
            Src = v2 + 4;
          }
          else
          {
            sub_430C80(Src, 1, (int)&i);
          }
          v1 = sub_4423D0(&v34);
        }
        v3 = (std::_String_base *)sub_569AD0(v54);
        sub_4014D0(v3, v47, 0, -1);
        sub_4ED3F0((int)v3 + 28, (int)v50);
        sub_46F440(v47);
        LOBYTE(v59) = 0;
        if ( v57 >= 0x10 )
          j__free(v55);
        v57 = 15;
        v56 = 0;
        LOBYTE(v55) = 0;
        goto LABEL_38;
      }
      sub_46F440(v47);
      if ( v57 >= 0x10 )
LABEL_41:
        j__free(v55);
LABEL_56:
      if ( v58[6] >= (void *)0x10 )
        j__free(v58[1]);
      return 1;
    }
    if ( sub_40BF00((std::_String_base *)v58, 0, (unsigned int)v58[5], "[server]", 8u) != 0 )
    {
      qmemcpy(v17, v58, 28);
      off_77F3FC("importChannelScript - invalid type. %s is not acceptable");
      goto LABEL_56;
    }
    v32 = (void *)sub_568900(v31);
    *((uint8_t *)v32 + 153) = 1;
    *((uint32_t *)v32 + 1) = v32;
    *(uint32_t *)v32 = v32;
    *((uint32_t *)v32 + 2) = v32;
    v33 = 0;
    LOBYTE(v59) = 4;
    v4 = sub_4423D0(&v35);
    if ( v35 == 0 )
    {
      LOBYTE(v59) = 0;
      sub_472520(v31);
      goto LABEL_56;
    }
LABEL_18:
    v38 = 15;
    v37 = 0;
    v36[4] = 0;
    v40[6] = 15;
    v40[5] = 0;
    LOBYTE(v40[1]) = 0;
    v43 = 15;
    v42 = 0;
    v41[4] = 0;
    v39 = 0;
    v44 = 0;
    v45 = 0;
    LOBYTE(v59) = 5;
    v5 = sub_4423D0(&v35);
    i = v5;
    if ( v35 != 0 )
      break;
    LOBYTE(v59) = 4;
    sub_46F490(v36);
    v29 = &v17[4];
    sub_569740(v31);
    v10 = (int *)sub_569BB0((int)&v21, v4, (char)v17[4], v17[5]);
    v11 = *v10;
    LOBYTE(v59) = 6;
    v25 = v11;
    sub_569740(v10 + 1);
    LOBYTE(v59) = 7;
    sub_569E80(v18, &v25);
    v12 = *(uint32_t *)v26;
    LOBYTE(v59) = 6;
    sub_472460(&i, v12, v26);
    j__free(v26);
    v26 = nullptr;
    v27 = 0;
    v13 = *(uint32_t *)v22;
    LOBYTE(v59) = 4;
    sub_472460(v20, v13, v22);
    j__free(v22);
    v14 = *(uint32_t *)v32;
    v22 = nullptr;
    v23 = 0;
    LOBYTE(v59) = 0;
    sub_472460(v28, v14, v32);
    j__free(v32);
    v32 = nullptr;
    v33 = 0;
LABEL_38:
    if ( (uint8_t)sub_443430(v58) == 0 )
      goto LABEL_56;
  }
  v6 = (void **)sub_568800(&i);
  v29 = v6;
  if ( v6 == v32 || v5 < (int)v6[3] )
  {
    v24 = v32;
    v7 = &v24;
  }
  else
  {
    v7 = (void **)&v29;
  }
  if ( *v7 == v32 )
  {
    v17[6] = v36;
    if ( sub_443370() != 0 )
    {
      v39 = sub_4423D0(&v35);
      if ( v39 > 4 )
        v39 = 4;
      if ( v35 != 0 )
      {
        v17[6] = v40;
        if ( sub_443370() != 0 )
        {
          if ( (uint8_t)sub_423340(v40, "[none]") != 0 )
          {
            v8 = *(uint32_t *)sub_568AF0(v19, v40);
            if ( v8 != *(uint32_t *)(a1 + 4) )
            {
              v44 = v8 + 68;
              sub_4014D0((std::_String_base *)v41, v8 + 40, 0, -1);
              goto LABEL_32;
            }
            qmemcpy(v17, v40, 28);
            off_77F3FC("importChannelScript - invalid dungeon classification. %s does not exist");
          }
          else
          {
LABEL_32:
            v45 = sub_4423D0(&v35);
            if ( v35 != 0 )
            {
              v9 = 0;
              while ( 1 )
              {
                v46[v9] = sub_442480(&v35);
                if ( v35 == 0 )
                  break;
                if ( ++v9 >= 10 )
                {
                  v17[6] = v36;
                  sub_5694A0(&i);
                  sub_568C20(v17[6]);
                  sub_46F490(v36);
                  goto LABEL_18;
                }
              }
              off_77F3FC("importChannelScript - invalid level GridPercent(%d). (required Float)", v9);
            }
            else
            {
              off_77F3FC("importChannelScript - invalid dungeon bonus rate. (required INT)");
            }
          }
        }
        else
        {
          off_77F3FC("importChannelScript - invalid dungeon classification (requires STR)");
        }
      }
      else
      {
        off_77F3FC("importChannelScript - invalid channel type (requires INT)");
      }
    }
    else
    {
      off_77F3FC("importChannelScript - invalid channel name (requires STR)");
    }
    sub_46F490(v36);
    LOBYTE(v59) = 0;
    sub_472520(v31);
    sub_501490(v58);
    return 0;
  }
  else
  {
    off_77F3FC("importChannelScript - invalid channel number. %d already exists", v5);
    sub_46F490(v36);
    v15 = *(uint32_t *)v32;
    LOBYTE(v59) = 0;
    sub_472460(v28, v15, v32);
    j__free(v32);
    v32 = nullptr;
    v33 = 0;
    if ( v58[6] < (void *)0x10 )
      return 0;
    j__free(v58[1]);
    return 0;
  }
}


// ============================================================
// 【分区 21】频道数据处理（0x56A670-0x56CFE0）
// 频道表插入/遍历 0x56A8A0/0x56A900/0x56AA00（668C69/668C72 池标记）；
// 角色/负载列表装配 0x56B230/0x56B8D0（52E300/433130/4296E0、4FD800-4FDA00）；
// 频道信息汇总 0x56C660（220 行）。
// ============================================================
// ------------------------------------------------------------
// 0x56A670 unknown_libname_7 —— unknown_libname_7（库函数桩，12 行）
// ------------------------------------------------------------
// Microsoft VisualC 2-14/net runtime
int /*thiscall*/ unknown_libname_7(uint32_t *this, int a2)
{
  *(this + 1) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x56A680 sub_56A680 —— 频道对象辅助（429830）
// ------------------------------------------------------------
int /*thiscall*/ sub_56A680(uint16_t *this, int a2)
{
  if ( a2 == 0xFFFF )
    return 0;
  else
    return sub_429830((uint32_t *)dword_8F8500, *(this + 2 * a2 + 20));
}



// ------------------------------------------------------------
// 0x56A6B0 sub_56A6B0 —— 频道对象辅助 2（429830）
// ------------------------------------------------------------
int /*thiscall*/ sub_56A6B0(uint32_t *this, int a2, int a3)
{
  int result; // eax

  result = *(this + a2 + 10);
  if ( result != a3 )
  {
    if ( result != 0xFFFF )
    {
      result = sub_429830((uint32_t *)dword_8F8500, *((uint16_t *)this + 2 * a2 + 20));
      if ( result != 0 )
        *(uint32_t *)(result + 184) = 0;
    }
    *(this + a2 + 10) = a3;
    if ( a3 != 0xFFFF )
    {
      result = sub_429830((uint32_t *)dword_8F8500, (uint16_t)a3);
      if ( result != 0 )
        *(uint32_t *)(result + 184) = this;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x56A720 sub_56A720 —— 组队列表联动（55 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_56A720(uint32_t *this)
{
  int result; // eax

  result = *(this + 10) != 0xFFFF;
  if ( *(this + 11) != 0xFFFF )
    ++result;
  if ( *(this + 12) != 0xFFFF )
    ++result;
  if ( *(this + 13) != 0xFFFF )
    ++result;
  return result;
}



// ------------------------------------------------------------
// 0x56A750 ??Bid@locale@std@@QAEIXZ —— std::locale::Bid（MSVC 修饰名 ??Bid@locale@std@@QAEIXZ）——RTTI 命名
// ------------------------------------------------------------
int /*thiscall*/ std::locale::id::operator unsigned int(void *this)
{
  uint8_t v3[4]; // [esp+4h] [ebp-4h] BYREF

  if ( *(uint32_t *)this == 0 )
  {
    std::_Lockit::_Lockit((std::_Lockit *)v3, 0);
    if ( *(uint32_t *)this == 0 )
      *(uint32_t *)this = ++dword_9D2258;
    std::_Lockit::~_Lockit((std::_Lockit *)v3);
  }
  return *(uint32_t *)this;
}



// ------------------------------------------------------------
// 0x56A790 ?_Incref@facet@locale@std@@QAEXXZ —— std::locale::facet::_Incref（修饰名 ?_Incref@facet@locale@std@@QAEXXZ）——引用计数递增
// ------------------------------------------------------------
void /*thiscall*/ std::locale::facet::_Incref(std::locale::facet *this)
{
  int v2; // eax
  uint8_t v3[4]; // [esp+4h] [ebp-4h] BYREF

  std::_Lockit::_Lockit((std::_Lockit *)v3, 0);
  v2 = *((uint32_t *)this + 1);
  if ( v2 != -1 )
    *((uint32_t *)this + 1) = v2 + 1;
  std::_Lockit::~_Lockit((std::_Lockit *)v3);
}



// ------------------------------------------------------------
// 0x56A7C0 sub_56A7C0 —— 频道辅助（39 行）
// ------------------------------------------------------------
int /*fastcall*/ sub_56A7C0(int a1)
{
  int v2; // eax
  int v3; // esi
  uint8_t v5[4]; // [esp+4h] [ebp-4h] BYREF

  std::_Lockit::_Lockit((std::_Lockit *)v5, 0);
  v2 = *(uint32_t *)(a1 + 4);
  if ( v2 != 0 && v2 != -1 )
    *(uint32_t *)(a1 + 4) = v2 - 1;
  v3 = *(uint32_t *)(a1 + 4) != 0 ? 0 : a1;
  std::_Lockit::~_Lockit((std::_Lockit *)v5);
  return v3;
}



// ------------------------------------------------------------
// 0x56A810 ??1locale@std@@QAE@XZ —— std::locale::~locale（修饰名 ??1locale@std@@QAE@XZ）——析构
// ------------------------------------------------------------
void /*thiscall*/ std::locale::~locale(std::locale *this)
{
  int v1; // ecx
  void (/*thiscall*/ ***v2)(uint32_t, int); // eax

  v1 = *(uint32_t *)this;
  if ( v1 != 0 )
  {
    v2 = (void (/*thiscall*/ ***)(uint32_t, int))sub_56A7C0(v1);
    if ( v2 != nullptr )
      (**v2)(v2, 1);
  }
}



// ------------------------------------------------------------
// 0x56A830 sub_56A830 —— 频道辅助 2（13 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_56A830(uint32_t *Block, char a2)
{
  *Block = &std::locale::facet::`vftable';
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x56A860 sub_56A860 —— 频道辅助 3（22 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_56A860(uint32_t **this, uint32_t *a2)
{
  int v2; // esi
  uint32_t *v3; // edi
  int v4; // eax

  v2 = **(this + 9);
  v3 = a2;
  *a2 = v2;
  std::_Lockit::_Lockit((std::_Lockit *)&a2, 0);
  v4 = *(uint32_t *)(v2 + 4);
  if ( v4 != -1 )
    *(uint32_t *)(v2 + 4) = v4 + 1;
  std::_Lockit::~_Lockit((std::_Lockit *)&a2);
  return v3;
}



// ------------------------------------------------------------
// 0x56A8A0 sub_56A8A0 —— 频道表节点申请（668C69 池标记）
// ------------------------------------------------------------
char */*thiscall*/ sub_56A8A0(char *this)
{
  char *v2; // eax
  int v3; // edi
  std::ios_base *v4; // ecx
  int v5; // eax

  v2 = this + *(uint32_t *)(*(uint32_t *)this + 4);
  v3 = 0;
  if ( (v2[8] & 6) == 0 && (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)v2 + 10) + 44))(*((uint32_t *)v2 + 10)) == -1 )
    v3 = 4;
  v4 = (std::ios_base *)(this + *(uint32_t *)(*(uint32_t *)this + 4));
  if ( v3 != 0 )
  {
    v5 = v3 | *((uint32_t *)v4 + 2);
    if ( *((uint32_t *)v4 + 10) == 0 )
      v5 |= 4u;
    std::ios_base::clear(v4, v5, false);
  }
  return this;
}



// ------------------------------------------------------------
// 0x56A900 sub_56A900 —— 频道表遍历（668C72 + 56A8A0）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_56A900(uint8_t *this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  char *v7; // eax

  *(uint32_t *)this = a2;
  v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)a2 + 4) + a2 + 40);
  if ( v3 != 0 )
    sub_668C69(v3 + 4);
  v4 = *(uint32_t *)(*(uint32_t *)a2 + 4);
  v5 = *(uint32_t *)(v4 + a2 + 8);
  v6 = a2 + v4;
  if ( v5 == 0 )
  {
    v7 = *(char **)(v6 + 44);
    if ( v7 != nullptr )
      sub_56A8A0(v7);
  }
  *(this + 4) = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)a2 + 4) + a2 + 8) == 0;
  return this;
}



// ------------------------------------------------------------
// 0x56A990 sub_56A990 —— 频道表节点释放（56A8A0/668C72）
// ------------------------------------------------------------
int /*thiscall*/ sub_56A990(char **this)
{
  int result; // eax

  if ( !__uncaught_exception() && ((*this)[*(uint32_t *)(*(uint32_t *)*this + 4) + 16] & 2) != 0 )
    sub_56A8A0(*this);
  result = *(uint32_t *)&(*this)[*(uint32_t *)(*(uint32_t *)*this + 4) + 40];
  if ( result != 0 )
    return sub_668C72(result + 4, this);
  return result;
}



// ------------------------------------------------------------
// 0x56AA00 sub_56AA00 —— 频道表批量填充（56A900/668C72，173 行）
// ------------------------------------------------------------
int */*cdecl*/ sub_56AA00(int *a1, const char *a2)
{
  int v2; // ebx
  signed int v3; // edi
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  uint32_t *v10; // edx
  uint32_t *v11; // ecx
  uint8_t *v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // eax
  int v16; // ecx
  uint32_t *v17; // edx
  uint32_t *v18; // ecx
  uint8_t *v19; // edx
  int v20; // edx
  std::ios_base *v21; // ecx
  int v22; // eax
  int v23; // ebx
  int v24; // eax
  int v25; // edi
  std::ios_base *v26; // ecx
  int v27; // eax
  int v28; // eax
  int v30; // [esp+0h] [ebp-2Ch] BYREF
  int v31; // [esp+Ch] [ebp-20h]
  char v32; // [esp+10h] [ebp-1Ch]
  int v33; // [esp+14h] [ebp-18h]
  int v34; // [esp+18h] [ebp-14h]
  int *v35; // [esp+1Ch] [ebp-10h]
  int v36; // [esp+28h] [ebp-4h]

  v2 = 0;
  v35 = &v30;
  v34 = 0;
  v3 = strlen(a2);
  v4 = *(int *)((char *)a1 + *(uint32_t *)(*a1 + 4) + 24);
  if ( v4 > 0 && v4 > v3 )
    v2 = v4 - v3;
  v33 = v2;
  sub_56A900(a1);
  v36 = 0;
  if ( v32 == 0 )
  {
    v5 = 4;
    goto LABEL_29;
  }
  v6 = *(int *)((char *)a1 + *(uint32_t *)(*a1 + 4) + 16) & 0x1C0;
  LOBYTE(v36) = 1;
  if ( v6 == 64 )
  {
LABEL_16:
    v13 = *(int *)((char *)a1 + *(uint32_t *)(*a1 + 4) + 40);
    if ( (*(int (/*thiscall*/ **)(int, const char *, signed int))(*(uint32_t *)v13 + 28))(v13, a2, v3) == v3 )
    {
      while ( v2 > 0 )
      {
        v14 = *(uint32_t *)(*a1 + 4);
        LOBYTE(v15) = *((uint8_t *)a1 + v14 + 48);
        v16 = *(int *)((char *)a1 + v14 + 40);
        v17 = *(uint32_t **)(v16 + 36);
        if ( *v17 != 0 && *v17 < (unsigned int)(*v17 + **(uint32_t **)(v16 + 52)) )
        {
          --**(uint32_t **)(v16 + 52);
          v18 = *(uint32_t **)(v16 + 36);
          v19 = (uint8_t *)(*v18)++;
          *v19 = v15;
          v15 = (uint8_t)v15;
        }
        else
        {
          v15 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v16 + 4))(v16, (uint8_t)v15);
        }
        if ( v15 == -1 )
        {
          v20 = *a1;
          v34 |= 4u;
          *(int *)((char *)a1 + *(uint32_t *)(v20 + 4) + 24) = 0;
          goto LABEL_28;
        }
        --v2;
      }
    }
    else
    {
      v34 = 4;
    }
    goto LABEL_18;
  }
  while ( v2 > 0 )
  {
    v7 = *(uint32_t *)(*a1 + 4);
    LOBYTE(v8) = *((uint8_t *)a1 + v7 + 48);
    v9 = *(int *)((char *)a1 + v7 + 40);
    v10 = *(uint32_t **)(v9 + 36);
    if ( *v10 != 0 )
    {
      if ( *v10 < (unsigned int)(*v10 + **(uint32_t **)(v9 + 52)) )
      {
        --**(uint32_t **)(v9 + 52);
        v11 = *(uint32_t **)(v9 + 36);
        v12 = (uint8_t *)(*v11)++;
        v2 = v33;
        *v12 = v8;
        v8 = (uint8_t)v8;
        goto LABEL_13;
      }
      v2 = v33;
    }
    v8 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v9 + 4))(v9, (uint8_t)v8);
LABEL_13:
    if ( v8 == -1 )
    {
      v34 |= 4u;
      break;
    }
    v33 = --v2;
  }
  if ( v34 == 0 )
    goto LABEL_16;
LABEL_18:
  *(int *)((char *)a1 + *(uint32_t *)(*a1 + 4) + 24) = 0;
LABEL_28:
  v5 = v34;
LABEL_29:
  v21 = (std::ios_base *)((char *)a1 + *(uint32_t *)(*a1 + 4));
  v36 = 0;
  if ( v5 != 0 )
  {
    v22 = v5 | *((uint32_t *)v21 + 2);
    if ( *((uint32_t *)v21 + 10) == 0 )
      LOBYTE(v22) = v22 | 4;
    std::ios_base::clear(v21, v22, false);
  }
  v36 = 3;
  if ( !__uncaught_exception() )
  {
    v23 = v31;
    v24 = *(uint32_t *)(*(uint32_t *)v31 + 4) + v31;
    if ( (*(uint8_t *)(v24 + 16) & 2) != 0 )
    {
      v25 = 0;
      if ( (*(uint8_t *)(v24 + 8) & 6) == 0
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v24 + 40) + 44))(*(uint32_t *)(v24 + 40)) == -1 )
      {
        v25 = 4;
      }
      v26 = (std::ios_base *)(v23 + *(uint32_t *)(*(uint32_t *)v23 + 4));
      if ( v25 != 0 )
      {
        v27 = v25 | *((uint32_t *)v26 + 2);
        if ( *((uint32_t *)v26 + 10) == 0 )
          LOBYTE(v27) = v27 | 4;
        std::ios_base::clear(v26, v27, false);
      }
    }
  }
  v28 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)v31 + 4) + v31 + 40);
  v36 = -1;
  if ( v28 != 0 )
    sub_668C72(v28 + 4);
  return a1;
}


// ------------------------------------------------------------
// 0x56AC80 sub_56AC80 —— 频道表查询（56A900/56A990）
// ------------------------------------------------------------
char */*thiscall*/ sub_56AC80(char *this, uint8_t a2)
{
  int v3; // edi
  int v4; // ecx
  uint32_t *v5; // edx
  bool v6; // zf
  uint32_t *v7; // ecx
  uint8_t *v8; // eax
  int v9; // eax
  std::ios_base *v10; // ecx
  int v11; // eax
  int v13; // [esp+0h] [ebp-2Ch] BYREF
  char *v14; // [esp+Ch] [ebp-20h] BYREF
  char v15; // [esp+10h] [ebp-1Ch]
  int v16; // [esp+14h] [ebp-18h]
  char *v17; // [esp+18h] [ebp-14h]
  int *v18; // [esp+1Ch] [ebp-10h]
  int v19; // [esp+28h] [ebp-4h]

  v18 = &v13;
  v3 = 0;
  v17 = this;
  v16 = 0;
  sub_56A900(&v14, (int)this);
  v19 = 0;
  if ( v15 != 0 )
  {
    v4 = *(uint32_t *)(this + *(uint32_t *)(*(uint32_t *)this + 4) + 40);
    v5 = *(uint32_t **)(v4 + 36);
    v6 = *v5 == 0;
    LOBYTE(v19) = 1;
    if ( v6 || *v5 >= (unsigned int)(*v5 + **(uint32_t **)(v4 + 52)) )
    {
      v9 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v4 + 4))(v4, a2);
    }
    else
    {
      --**(uint32_t **)(v4 + 52);
      v7 = *(uint32_t **)(v4 + 36);
      v8 = (uint8_t *)(*v7)++;
      *v8 = a2;
      v9 = a2;
    }
    if ( v9 == -1 )
      v3 = 4;
  }
  else
  {
    v3 = 4;
  }
  v10 = (std::ios_base *)(this + *(uint32_t *)(*(uint32_t *)this + 4));
  v19 = 0;
  if ( v3 != 0 )
  {
    v11 = v3 | *((uint32_t *)v10 + 2);
    if ( *((uint32_t *)v10 + 10) == 0 )
      v11 |= 4u;
    std::ios_base::clear(v10, v11, false);
  }
  v19 = -1;
  sub_56A990(&v14);
  return this;
}



// ------------------------------------------------------------
// 0x56ADA0 sub_56ADA0 —— 频道表重建（56AA00/56AC80/56A8A0）
// ------------------------------------------------------------
WORD sub_56ADA0()
{
  char *v0; // eax
  WORD result; // ax
  char *v2; // esi
  struct WSAData WSAData; // [esp+0h] [ebp-194h] BYREF
  int v4; // [esp+190h] [ebp-4h]

  v4 = dword_796E50;
  if ( WSAStartup(0x202u, &WSAData) != 0 )
  {
    v0 = (char *)sub_56AA00((int)&dword_9D2320, "Could not load winsock");
    goto LABEL_5;
  }
  result = WSAData.wVersion;
  if ( WSAData.wVersion != 514 )
  {
    WSACleanup();
    v0 = (char *)sub_56AA00((int)&dword_9D2320, "Bad winsock verion");
LABEL_5:
    v2 = v0;
    sub_56AC80(v0, 0xAu);
    sub_56A8A0(v2);
    exit(1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x56AE20 sub_56AE20 —— 频道显示数据（16 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_56AE20(int a1)
{
  int result; // eax
  int i; // ecx

  result = a1;
  for ( i = *(uint32_t *)(a1 + 8); *(uint8_t *)(i + 353) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x56AE50 sub_56AE50 —— 频道显示数据 2（24 行）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_56AE50(uint32_t *a1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = a1;
  v2 = (int *)*a1;
  if ( *(uint8_t *)(*a1 + 353) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 353) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x56AE80 sub_56AE80 —— 频道显示数据 3（42 行）
// ------------------------------------------------------------
int */*thiscall*/ sub_56AE80(int *this)
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 353) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 353) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 353) == 0; result = (int *)result[1] )
      {
        if ( *this != result[2] )
          break;
        *this = (int)result;
      }
      *this = (int)result;
    }
    else
    {
      result = (int *)*v2;
      if ( *(uint8_t *)(*v2 + 353) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 353) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x56AEE0 sub_56AEE0 —— 频道显示数据 4（27 行）
// ------------------------------------------------------------
int */*thiscall*/ sub_56AEE0(uint32_t *this, uint32_t *a2)
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);
  v3 = (int *)result[1];
  while ( *((uint8_t *)v3 + 353) == 0 )
  {
    if ( v3[3] >= *a2 )
    {
      result = v3;
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x56AF20 sub_56AF20 —— 频道显示数据 5（36 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_56AF20(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  int v3; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(a2 + 8);
  *(uint32_t *)(a2 + 8) = *result;
  if ( *(uint8_t *)(*result + 353) == 0 )
    *(uint32_t *)(*result + 4) = a2;
  result[1] = *(uint32_t *)(a2 + 4);
  v3 = *(this + 1);
  if ( a2 == *(uint32_t *)(v3 + 4) )
  {
    *(uint32_t *)(v3 + 4) = result;
    *result = a2;
    *(uint32_t *)(a2 + 4) = result;
  }
  else
  {
    v4 = *(uint32_t **)(a2 + 4);
    if ( a2 == *v4 )
      *v4 = result;
    else
      v4[2] = result;
    *result = a2;
    *(uint32_t *)(a2 + 4) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x56AF80 sub_56AF80 —— 频道显示数据 6（38 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_56AF80(uint32_t *this, uint32_t *a2)
{
  int result; // eax
  int v3; // esi
  int v4; // ecx
  uint32_t *v5; // ecx

  result = *a2;
  *a2 = *(uint32_t *)(*a2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 353) == 0 )
    *(uint32_t *)(v3 + 4) = a2;
  *(uint32_t *)(result + 4) = a2[1];
  v4 = *(this + 1);
  if ( a2 == *(uint32_t **)(v4 + 4) )
  {
    *(uint32_t *)(v4 + 4) = result;
    *(uint32_t *)(result + 8) = a2;
    a2[1] = result;
  }
  else
  {
    v5 = (uint32_t *)a2[1];
    if ( a2 == (uint32_t *)v5[2] )
      v5[2] = result;
    else
      *v5 = result;
    *(uint32_t *)(result + 8) = a2;
    a2[1] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x56AFF0 sub_56AFF0 —— 频道显示数据 7（47 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_56AFF0(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 353) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 353) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 353) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 353) == 0 );
        if ( *(uint8_t *)(result + 353) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 353) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x56B070 sub_56B070 —— 频道条目 8（21 行）
// ------------------------------------------------------------
uint32_t *sub_56B070()
{
  uint32_t *result; // eax

  result = operator new(0x68u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 100) = 1;
  *((uint8_t *)result + 101) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x56B0B0 sub_56B0B0 —— 频道条目 9（21 行）
// ------------------------------------------------------------
uint32_t *sub_56B0B0()
{
  uint32_t *result; // eax

  result = operator new(0x164u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 352) = 1;
  *((uint8_t *)result + 353) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x56B0F0 sub_56B0F0 —— 频道名取串（5648C0）
// ------------------------------------------------------------
void */*thiscall*/ sub_56B0F0(void **this, int *a2, int a3)
{
  char v3; // al
  uint32_t *v4; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);
  v3 = *((uint8_t *)a2 + 21);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    v4 = sub_5648C0((int)*(this + 1), a3, (int)*(this + 1), a2 + 3, *((uint8_t *)a2 + 20));
    if ( *((uint8_t *)Block + 21) != 0 )
      Block = v4;
    v6 = *a2;
    v10 = 0;
    *v4 = sub_56B0F0(v6, v4);
    v4[2] = sub_56B0F0(a2[2], v4);
  }
  return Block;
}



// ------------------------------------------------------------
// 0x56B1A0 sub_56B1A0 —— 频道名收尾（56B0F0）
// ------------------------------------------------------------
int */*thiscall*/ sub_56B1A0(int this, int a2)
{
  int v3; // edi
  int **v4; // edx
  int *result; // eax
  int *v6; // ecx
  int v7; // esi
  int **v8; // ecx

  v3 = *(uint32_t *)(this + 4);
  *(uint32_t *)(v3 + 4) = sub_56B0F0((void **)this, *(int **)(*(uint32_t *)(a2 + 4) + 4), v3);
  *(uint32_t *)(this + 8) = *(uint32_t *)(a2 + 8);
  v4 = *(int ***)(this + 4);
  result = v4[1];
  if ( *((uint8_t *)result + 21) != 0 )
  {
    *v4 = (int *)v4;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);
  }
  else
  {
    v6 = (int *)*result;
    if ( *(uint8_t *)(*result + 21) == 0 )
    {
      do
      {
        result = v6;
        v6 = (int *)*v6;
      }
      while ( *((uint8_t *)v6 + 21) == 0 );
    }
    *v4 = result;
    v7 = *(uint32_t *)(this + 4);
    v8 = *(int ***)(v7 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 21) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(v7 + 8) = v8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x56B230 sub_56B230 —— 频道角色列表装配（4015C0/401740/41C5E0/52E300/542490/433130/4296E0，219 行）
// ------------------------------------------------------------
int ***/*thiscall*/ sub_56B230(uint32_t *this, int ***a2, int **a3)
{
  int **v3; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *v7; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *v15; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  size_t v20; // [esp+34h] [ebp-34h] BYREF
  char v21; // [esp+38h] [ebp-30h]
  int v22; // [esp+48h] [ebp-20h]
  int v23; // [esp+4Ch] [ebp-1Ch]
  int v24; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v26; // [esp+58h] [ebp-10h]
  int v27; // [esp+64h] [ebp-4h]

  v26 = this;
  if ( *((uint8_t *)a3 + 21) != 0 )
  {
    v23 = 15;
    v22 = 0;
    v21 = 0;
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);
    v27 = 0;
    sub_401740(pExceptionObject, &v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_41C5E0((int *)&a3);
  if ( *((uint8_t *)*v3 + 21) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    v7 = v26;
    v8 = v26[1];
    if ( *(int ***)(v8 + 4) == v3 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == v3 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)v7[1] == v3 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);
        v7 = v26;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v24 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v24 + 8) = sub_542490(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 21) != 0 )
  {
    v4 = *v3;
    goto LABEL_8;
  }
  v5 = (int *)a3;
  v4 = a3[2];
  if ( a3 == v3 )
    goto LABEL_8;
  (*v3)[1] = (int)a3;
  *v5 = (int)*v3;
  if ( v5 == v3[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)v3[2];
    v3[2][1] = (int)v5;
  }
  v12 = v26[1];
  if ( *(int ***)(v12 + 4) == v3 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)v3[1];
    if ( *v13 == (int *)v3 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)v3[1];
  v14 = *((uint8_t *)v5 + 20);
  *((uint8_t *)v5 + 20) = *((uint8_t *)v3 + 20);
  *((uint8_t *)v3 + 20) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )
  {
    v15 = v26;
    if ( v4 != *(int **)(v26[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 20) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_433130(v6);
            v16 = (uint32_t *)v6[2];
            v15 = v26;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 20) != 1 || *(uint8_t *)(v16[2] + 20) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 20) == 1 )
            {
              *(uint8_t *)(*v16 + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_4296E0(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(v16[2] + 20) = 1;
            sub_433130(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_4296E0(v6);
            v16 = (uint32_t *)*v6;
            v15 = v26;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 20) != 1 || *(uint8_t *)(*v16 + 20) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 20) == 1 )
            {
              *(uint8_t *)(v16[2] + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_433130(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(*v16 + 20) = 1;
            sub_4296E0(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 20) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 20) = 1;
  }
  j__free(Block);
  v17 = v26[2];
  if ( v17 != 0 )
    v26[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x56B4F0 sub_56B4F0 —— 频道负载请求（42A9A0/55E7F0/5DAF70/6511B0/497E70）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_56B4F0(int this, char *Src, int a3, int a4, int a5)
{
  int v6; // edx
  unsigned int v7; // ecx
  unsigned int result; // eax
  int v9; // edi
  int v10; // edi
  unsigned int v11; // eax
  int v12; // edi
  int v13; // eax
  char *v14; // ebx
  size_t v15; // edi
  char *v16; // eax
  void *v17; // eax
  int v18; // ecx
  int v19; // eax
  unsigned int v20; // edi
  int v21; // ebx
  int v23; // ebx
  const void *v24; // [esp-Ch] [ebp-34h]
  int v25; // [esp-Ch] [ebp-34h]
  int v26; // [esp+0h] [ebp-28h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v28; // [esp+10h] [ebp-18h]
  unsigned int v29; // [esp+14h] [ebp-14h]
  int *v30; // [esp+18h] [ebp-10h]
  int v31; // [esp+24h] [ebp-4h]
  int Srca; // [esp+30h] [ebp+8h]
  void *Srcb; // [esp+30h] [ebp+8h]

  v6 = *(uint32_t *)(this + 4);
  v7 = (a4 - a3) >> 2;
  v30 = &v26;
  v29 = v7;
  if ( v6 != 0 )
    result = (*(uint32_t *)(this + 12) - v6) >> 2;
  else
    result = 0;
  if ( v7 != 0 )
  {
    if ( v6 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v6) >> 2;
    else
      v9 = 0;
    if ( 0x3FFFFFFF - v9 < v7 )
      sub_42A9A0(this);
    if ( v6 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v6) >> 2;
    else
      v10 = 0;
    if ( result >= v7 + v10 )
    {
      v21 = *(uint32_t *)(this + 8);
      if ( (v21 - (int)Src) >> 2 >= v7 )
      {
        Srcb = (void *)(v21 - 4 * v7);
        *(uint32_t *)(this + 8) = sub_55E7F0(Srcb, v21, *(void **)(this + 8));
        sub_5DAF70(Src, (int)Srcb, v21);
        return sub_6511B0(a3, a4, Src);
      }
      else
      {
        Srca = 4 * v7;
        sub_55E7F0(Src, v21, &Src[4 * v7]);
        v23 = a3 + 4 * ((*(uint32_t *)(this + 8) - (int)Src) >> 2);
        v25 = *(uint32_t *)(this + 8);
        v31 = 2;
        sub_497E70(v23, a4, v25);
        *(uint32_t *)(this + 8) += Srca;
        return sub_6511B0(a3, v23, Src);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v11 = (result >> 1) + result;
      else
        v11 = 0;
      if ( v6 != 0 )
        v12 = (*(uint32_t *)(this + 8) - v6) >> 2;
      else
        v12 = 0;
      if ( v11 < v7 + v12 )
      {
        if ( v6 != 0 )
          v13 = (*(uint32_t *)(this + 8) - v6) >> 2;
        else
          v13 = 0;
        v11 = v7 + v13;
      }
      v28 = 4 * v11;
      v14 = (char *)operator new(4 * v11);
      v15 = 4 * ((int)&Src[-*(uint32_t *)(this + 4)] >> 2);
      v24 = *(const void **)(this + 4);
      Block = v14;
      v31 = 0;
      v16 = (char *)memcpy_0(v14, v24, v15);
      v17 = (void *)sub_497E70(a3, a4, &v16[v15]);
      memcpy_0(v17, Src, 4 * ((*(uint32_t *)(this + 8) - (int)Src) >> 2));
      v18 = *(uint32_t *)(this + 4);
      if ( v18 != 0 )
        v19 = (*(uint32_t *)(this + 8) - v18) >> 2;
      else
        v19 = 0;
      v20 = v19 + v29;
      if ( v18 != 0 )
        j__free(*(void **)(this + 4));
      result = (unsigned int)&v14[v28];
      *(uint32_t *)(this + 12) = &v14[v28];
      *(uint32_t *)(this + 8) = &v14[4 * v20];
      *(uint32_t *)(this + 4) = v14;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x56B740 sub_56B740 —— 频道角色列表入口（4FD9C0/56B230）
// ------------------------------------------------------------
int */*thiscall*/ sub_56B740(int **this, int *a2, int a3, int a4)
{
  int v4; // ebx
  int v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int v10; // ecx
  int v11; // eax
  int j; // eax
  int i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(uint32_t *)v7 && a4 == v7 )
  {
    sub_4FD9C0(*(void **)(v7 + 4));
    (*(this + 1))[1] = (int)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int)*(this + 1);
    *a2 = **(this + 1);
    return a2;
  }
  else
  {
    if ( a3 != a4 )
    {
      do
      {
        v10 = v5;
        if ( *(uint8_t *)(v5 + 21) == 0 )
        {
          v11 = *(uint32_t *)(v5 + 8);
          if ( *(uint8_t *)(v11 + 21) != 0 )
          {
            for ( i = *(uint32_t *)(v5 + 4); *(uint8_t *)(i + 21) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( v5 != *(uint32_t *)(i + 8) )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = *(uint32_t *)(v5 + 8);
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 21) == 0; j = *(uint32_t *)j )
              v5 = j;
          }
        }
        sub_56B230(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x56B800 sub_56B800 —— 转发 56B740
// ------------------------------------------------------------
int /*thiscall*/ sub_56B800(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_56B740((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x56B840 sub_56B840 —— 频道条目 10（433AC0/56B1A0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_56B840(uint32_t *this, int a2)
{
  uint32_t *v3; // eax
  uint32_t v5[8]; // [esp+0h] [ebp-20h] BYREF

  v5[4] = v5;
  v5[3] = this;
  v3 = sub_433AC0();
  *(this + 1) = v3;
  *((uint8_t *)v3 + 21) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  v5[7] = 0;
  sub_56B1A0((int)this, a2);
  return this;
}



// ------------------------------------------------------------
// 0x56B8D0 sub_56B8D0 —— 频道负载列表装配（4015C0/401740 + 4FD8A0/4FD820/4FD800/4FD900/4FD960/4FDA00，219 行）
// ------------------------------------------------------------
int ***/*thiscall*/ sub_56B8D0(uint32_t *this, int ***a2, int **a3)
{
  int **v3; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *v7; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *v15; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v20[20]; // [esp+34h] [ebp-34h] BYREF
  int v21; // [esp+48h] [ebp-20h]
  int v22; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v25; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  v25 = this;
  if ( *((uint8_t *)a3 + 101) != 0 )
  {
    v22 = 15;
    v21 = 0;
    v20[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);
    v26 = 0;
    sub_401740(v20);
    pExceptionObject = &std::out_of_range::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_4FD8A0(&a3);
  if ( *((uint8_t *)*v3 + 101) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 101) == 0 )
      v4[1] = (int)v6;
    v7 = v25;
    v8 = v25[1];
    if ( *(int ***)(v8 + 4) == v3 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == v3 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)v7[1] == v3 )
    {
      if ( *((uint8_t *)v4 + 101) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_4FD820(v4);
        v7 = v25;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 101) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_4FD800(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 101) != 0 )
  {
    v4 = *v3;
    goto LABEL_8;
  }
  v5 = (int *)a3;
  v4 = a3[2];
  if ( a3 == v3 )
    goto LABEL_8;
  (*v3)[1] = (int)a3;
  *v5 = (int)*v3;
  if ( v5 == v3[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 101) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)v3[2];
    v3[2][1] = (int)v5;
  }
  v12 = v25[1];
  if ( *(int ***)(v12 + 4) == v3 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)v3[1];
    if ( *v13 == (int *)v3 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)v3[1];
  v14 = *((uint8_t *)v5 + 100);
  *((uint8_t *)v5 + 100) = *((uint8_t *)v3 + 100);
  *((uint8_t *)v3 + 100) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 100) == 1 )
  {
    v15 = v25;
    if ( v4 != *(int **)(v25[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 100) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 100) == 0 )
          {
            *((uint8_t *)v16 + 100) = 1;
            *((uint8_t *)v6 + 100) = 0;
            sub_4FD900(v6);
            v16 = (uint32_t *)v6[2];
            v15 = v25;
          }
          if ( *((uint8_t *)v16 + 101) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 100) != 1 || *(uint8_t *)(v16[2] + 100) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 100) == 1 )
            {
              *(uint8_t *)(*v16 + 100) = 1;
              *((uint8_t *)v16 + 100) = 0;
              sub_4FD960(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 100) = *((uint8_t *)v6 + 100);
            *((uint8_t *)v6 + 100) = 1;
            *(uint8_t *)(v16[2] + 100) = 1;
            sub_4FD900(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 100) == 0 )
          {
            *((uint8_t *)v16 + 100) = 1;
            *((uint8_t *)v6 + 100) = 0;
            sub_4FD960(v6);
            v16 = (uint32_t *)*v6;
            v15 = v25;
          }
          if ( *((uint8_t *)v16 + 101) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 100) != 1 || *(uint8_t *)(*v16 + 100) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 100) == 1 )
            {
              *(uint8_t *)(v16[2] + 100) = 1;
              *((uint8_t *)v16 + 100) = 0;
              sub_4FD900(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 100) = *((uint8_t *)v6 + 100);
            *((uint8_t *)v6 + 100) = 1;
            *(uint8_t *)(*v16 + 100) = 1;
            sub_4FD960(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 100) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 100) = 1;
  }
  sub_4FDA00((char *)Block + 16);
  j__free(Block);
  v17 = v25[2];
  if ( v17 != 0 )
    v25[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x56BBA0 sub_56BBA0 —— 频道负载列表入口（4FDE50/56B8D0）
// ------------------------------------------------------------
int **/*thiscall*/ sub_56BBA0(int ***this, int **a2, int *a3, int *a4)
{
  int *v4; // ebx
  int *v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(int **)v7 && a4 == (int *)v7 )
  {
    sub_4FDE50(*(void **)(v7 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int *)*(this + 1);
    *a2 = **(this + 1);
    return a2;
  }
  else
  {
    if ( a3 != a4 )
    {
      do
      {
        v10 = (int **)v5;
        if ( *((uint8_t *)v5 + 101) == 0 )
        {
          v11 = (int **)v5[2];
          if ( *((uint8_t *)v11 + 101) != 0 )
          {
            for ( i = (int *)v5[1]; *((uint8_t *)i + 101) == 0; i = (int *)i[1] )
            {
              if ( v5 != (int *)i[2] )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = (int *)v5[2];
            for ( j = *v11; *((uint8_t *)j + 101) == 0; j = (int *)*j )
              v5 = j;
          }
        }
        sub_56B8D0(this, (int ***)&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x56BC60 sub_56BC60 —— 转发 56BBA0
// ------------------------------------------------------------
int /*thiscall*/ sub_56BC60(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_56BBA0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x56BCA0 sub_56BCA0 —— 频道负载文本（4015C0/4FD9C0/4FDE50）
// ------------------------------------------------------------
int /*thiscall*/ sub_56BCA0(uint32_t *this)
{
  char *v2; // edi
  int i; // ebx
  uint32_t *v4; // ebx
  uint32_t *v5; // eax
  char *v6; // edi
  uint32_t *v7; // eax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-4h]
  int Blocka; // [esp+Ch] [ebp-4h]

  *this = 0;
  sub_4015C0((void *)szPassword, 0);
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0;
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  v2 = (char *)(this + 32);
  for ( i = 2; i != 0; --i )
  {
    sub_4015C0((void *)szPassword, 0);
    v2 += 28;
  }
  *((uint8_t *)this + 184) = 1;
  v4 = *(uint32_t **)(*(this + 49) + 4);
  for ( Block = v4; *((uint8_t *)v4 + 21) == 0; Block = v4 )
  {
    sub_4FD9C0((void *)v4[2]);
    v4 = (uint32_t *)*v4;
    j__free(Block);
  }
  *(uint32_t *)(*(this + 49) + 4) = *(this + 49);
  v5 = (uint32_t *)*(this + 49);
  *(this + 50) = 0;
  *v5 = v5;
  *(uint32_t *)(*(this + 49) + 8) = *(this + 49);
  sub_4015C0((void *)szPassword, 0);
  v6 = (char *)(this + 59);
  for ( Blocka = 4; Blocka != 0; --Blocka )
  {
    if ( *(uint32_t *)v6 != 0 )
      j__free(*(void **)v6);
    *(uint32_t *)v6 = 0;
    *((uint32_t *)v6 + 1) = 0;
    *((uint32_t *)v6 + 2) = 0;
    v6 += 16;
  }
  sub_4FDE50(*(void **)(*(this + 75) + 4));
  *(uint32_t *)(*(this + 75) + 4) = *(this + 75);
  v7 = (uint32_t *)*(this + 75);
  *(this + 76) = 0;
  *v7 = v7;
  *(uint32_t *)(*(this + 75) + 8) = *(this + 75);
  result = sub_4015C0((void *)szPassword, 0);
  *(this + 47) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x56BDF0 sub_56BDF0 —— 频道负载联动（56BBA0/56B740）
// ------------------------------------------------------------
void /*thiscall*/ sub_56BDF0(int this)
{
  bool v2; // cf
  int v3; // [esp-8h] [ebp-28h]
  int *v4; // [esp-4h] [ebp-24h]
  uint8_t v5[4]; // [esp+Ch] [ebp-14h] BYREF
  int v6; // [esp+10h] [ebp-10h]
  int v7; // [esp+1Ch] [ebp-4h]

  v6 = this;
  v2 = *(uint32_t *)(this + 332) < 0x10u;
  v7 = 7;
  if ( !v2 )
    j__free(*(void **)(this + 312));
  *(uint32_t *)(this + 332) = 15;
  *(uint32_t *)(this + 328) = 0;
  *(uint8_t *)(this + 312) = 0;
  sub_56BBA0(v5, **(uint32_t **)(this + 300), *(uint32_t *)(this + 300));
  j__free(*(void **)(this + 300));
  *(uint32_t *)(this + 300) = 0;
  *(uint32_t *)(this + 304) = 0;
  LOBYTE(v7) = 6;
  `eh vector destructor iterator'((void *)(this + 232), 0x10u, 4, sub_5E5260);
  if ( *(uint32_t *)(this + 228) >= 0x10u )
    j__free(*(void **)(this + 208));
  *(uint32_t *)(this + 228) = 15;
  *(uint32_t *)(this + 224) = 0;
  *(uint8_t *)(this + 208) = 0;
  v4 = *(int **)(this + 196);
  v3 = *v4;
  LOBYTE(v7) = 4;
  sub_56B740(v5, v3, v4);
  j__free(*(void **)(this + 196));
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  LOBYTE(v7) = 3;
  `eh vector destructor iterator'((void *)(this + 128), 0x1Cu, 2, sub_501490);
  if ( *(uint32_t *)(this + 124) >= 0x10u )
    j__free(*(void **)(this + 104));
  *(uint32_t *)(this + 124) = 15;
  *(uint32_t *)(this + 120) = 0;
  *(uint8_t *)(this + 104) = 0;
  if ( *(uint32_t *)(this + 96) >= 0x10u )
    j__free(*(void **)(this + 76));
  *(uint32_t *)(this + 96) = 15;
  *(uint32_t *)(this + 92) = 0;
  *(uint8_t *)(this + 76) = 0;
  if ( *(uint32_t *)(this + 56) >= 0x10u )
    j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 56) = 15;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 36) = 0;
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 15;
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x56BFA0 sub_56BFA0 —— 频道负载联动 2（56BBA0/56B740）
// ------------------------------------------------------------
void /*thiscall*/ sub_56BFA0(int this)
{
  bool v2; // cf
  int v3; // [esp-8h] [ebp-28h]
  int *v4; // [esp-4h] [ebp-24h]
  int *v5[2]; // [esp+Ch] [ebp-14h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  v5[1] = (int *)this;
  v2 = *(uint32_t *)(this + 432) < 0x10u;
  v6 = 10;
  if ( !v2 )
    j__free(*(void **)(this + 412));
  *(uint32_t *)(this + 432) = 15;
  *(uint32_t *)(this + 428) = 0;
  *(uint8_t *)(this + 412) = 0;
  sub_56BBA0((int ***)(this + 396), v5, **(int ***)(this + 400), *(int **)(this + 400));
  j__free(*(void **)(this + 400));
  *(uint32_t *)(this + 400) = 0;
  *(uint32_t *)(this + 404) = 0;
  LOBYTE(v6) = 9;
  `eh vector destructor iterator'((void *)(this + 316), 0x10u, 5, (void (/*thiscall*/ *)(void *))sub_5E5260);
  if ( *(uint32_t *)(this + 312) >= 0x10u )
    j__free(*(void **)(this + 292));
  *(uint32_t *)(this + 312) = 15;
  *(uint32_t *)(this + 308) = 0;
  *(uint8_t *)(this + 292) = 0;
  v4 = *(int **)(this + 280);
  v3 = *v4;
  LOBYTE(v6) = 7;
  sub_56B740((int **)(this + 276), (int *)v5, v3, (int)v4);
  j__free(*(void **)(this + 280));
  *(uint32_t *)(this + 280) = 0;
  *(uint32_t *)(this + 284) = 0;
  LOBYTE(v6) = 6;
  `eh vector destructor iterator'((void *)(this + 212), 0x1Cu, 2, sub_501490);
  if ( *(uint32_t *)(this + 208) >= 0x10u )
    j__free(*(void **)(this + 188));
  *(uint32_t *)(this + 208) = 15;
  *(uint32_t *)(this + 204) = 0;
  *(uint8_t *)(this + 188) = 0;
  if ( *(uint32_t *)(this + 180) >= 0x10u )
    j__free(*(void **)(this + 160));
  *(uint32_t *)(this + 180) = 15;
  *(uint32_t *)(this + 176) = 0;
  *(uint8_t *)(this + 160) = 0;
  if ( *(uint32_t *)(this + 148) >= 0x10u )
    j__free(*(void **)(this + 128));
  *(uint32_t *)(this + 148) = 15;
  *(uint32_t *)(this + 144) = 0;
  *(uint8_t *)(this + 128) = 0;
  if ( *(uint32_t *)(this + 116) >= 0x10u )
    j__free(*(void **)(this + 96));
  *(uint32_t *)(this + 116) = 15;
  *(uint32_t *)(this + 112) = 0;
  *(uint8_t *)(this + 96) = 0;
  if ( *(uint32_t *)(this + 84) >= 0x10u )
    j__free(*(void **)(this + 64));
  *(uint32_t *)(this + 84) = 15;
  *(uint32_t *)(this + 80) = 0;
  *(uint8_t *)(this + 64) = 0;
  if ( *(uint32_t *)(this + 56) >= 0x10u )
    j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 56) = 15;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 36) = 0;
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 15;
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x56C1F0 sub_56C1F0 —— 频道条目 11（433AC0/56B070/56BCA0）
// ------------------------------------------------------------
int /*thiscall*/ sub_56C1F0(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax

  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 56) = 15;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 36) = 0;
  *(uint32_t *)(this + 96) = 15;
  *(uint32_t *)(this + 92) = 0;
  *(uint8_t *)(this + 76) = 0;
  *(uint32_t *)(this + 124) = 15;
  *(uint32_t *)(this + 120) = 0;
  *(uint8_t *)(this + 104) = 0;
  `eh vector constructor iterator'((void *)(this + 128), 0x1Cu, 2, sub_40C120, sub_501490);
  v2 = sub_433AC0();
  *(uint32_t *)(this + 196) = v2;
  *((uint8_t *)v2 + 21) = 1;
  *(uint32_t *)(*(uint32_t *)(this + 196) + 4) = *(uint32_t *)(this + 196);
  **(uint32_t **)(this + 196) = *(uint32_t *)(this + 196);
  *(uint32_t *)(*(uint32_t *)(this + 196) + 8) = *(uint32_t *)(this + 196);
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 228) = 15;
  *(uint32_t *)(this + 224) = 0;
  *(uint8_t *)(this + 208) = 0;
  `eh vector constructor iterator'((void *)(this + 232), 0x10u, 4, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  v3 = sub_56B070();
  *(uint32_t *)(this + 300) = v3;
  *((uint8_t *)v3 + 101) = 1;
  *(uint32_t *)(*(uint32_t *)(this + 300) + 4) = *(uint32_t *)(this + 300);
  **(uint32_t **)(this + 300) = *(uint32_t *)(this + 300);
  *(uint32_t *)(*(uint32_t *)(this + 300) + 8) = *(uint32_t *)(this + 300);
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 332) = 15;
  *(uint32_t *)(this + 328) = 0;
  *(uint8_t *)(this + 312) = 0;
  sub_56BCA0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x56C320 sub_56C320 —— 频道条目 12（433AC0/56B070/4FE0B0）
// ------------------------------------------------------------
int /*thiscall*/ sub_56C320(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax

  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 56) = 15;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 36) = 0;
  *(uint32_t *)(this + 84) = 15;
  *(uint32_t *)(this + 80) = 0;
  *(uint8_t *)(this + 64) = 0;
  *(uint32_t *)(this + 116) = 15;
  *(uint32_t *)(this + 112) = 0;
  *(uint8_t *)(this + 96) = 0;
  *(uint32_t *)(this + 148) = 15;
  *(uint32_t *)(this + 144) = 0;
  *(uint8_t *)(this + 128) = 0;
  *(uint32_t *)(this + 180) = 15;
  *(uint32_t *)(this + 176) = 0;
  *(uint8_t *)(this + 160) = 0;
  *(uint32_t *)(this + 208) = 15;
  *(uint32_t *)(this + 204) = 0;
  *(uint8_t *)(this + 188) = 0;
  `eh vector constructor iterator'((void *)(this + 212), 0x1Cu, 2, sub_40C120, sub_501490);
  v2 = sub_433AC0();
  *(uint32_t *)(this + 280) = v2;
  *((uint8_t *)v2 + 21) = 1;
  *(uint32_t *)(*(uint32_t *)(this + 280) + 4) = *(uint32_t *)(this + 280);
  **(uint32_t **)(this + 280) = *(uint32_t *)(this + 280);
  *(uint32_t *)(*(uint32_t *)(this + 280) + 8) = *(uint32_t *)(this + 280);
  *(uint32_t *)(this + 284) = 0;
  *(uint32_t *)(this + 312) = 15;
  *(uint32_t *)(this + 308) = 0;
  *(uint8_t *)(this + 292) = 0;
  `eh vector constructor iterator'((void *)(this + 316), 0x10u, 5, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  v3 = sub_56B070();
  *(uint32_t *)(this + 400) = v3;
  *((uint8_t *)v3 + 101) = 1;
  *(uint32_t *)(*(uint32_t *)(this + 400) + 4) = *(uint32_t *)(this + 400);
  **(uint32_t **)(this + 400) = *(uint32_t *)(this + 400);
  *(uint32_t *)(*(uint32_t *)(this + 400) + 8) = *(uint32_t *)(this + 400);
  *(uint32_t *)(this + 404) = 0;
  *(uint32_t *)(this + 432) = 15;
  *(uint32_t *)(this + 428) = 0;
  *(uint8_t *)(this + 412) = 0;
  sub_4FE0B0(this);
  return this;
}



// ------------------------------------------------------------
// 0x56C490 sub_56C490 —— 频道负载查询（4FE240）
// ------------------------------------------------------------
void */*thiscall*/ sub_56C490(void **this, int *a2, int a3)
{
  char v3; // al
  uint32_t *v4; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);
  v3 = *((uint8_t *)a2 + 101);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    v4 = (uint32_t *)sub_4FE240(*(this + 1), a3, *(this + 1), a2 + 3, *((uint8_t *)a2 + 100));
    if ( *((uint8_t *)Block + 101) != 0 )
      Block = v4;
    v6 = *a2;
    v10 = 0;
    *v4 = sub_56C490(v6, v4);
    v4[2] = sub_56C490(a2[2], v4);
  }
  return Block;
}



// ------------------------------------------------------------
// 0x56C540 sub_56C540 —— 频道负载查询 2（56C490）
// ------------------------------------------------------------
int */*thiscall*/ sub_56C540(int this, int a2)
{
  int v3; // edi
  int **v4; // edx
  int *result; // eax
  int *v6; // ecx
  int v7; // esi
  int **v8; // ecx

  v3 = *(uint32_t *)(this + 4);
  *(uint32_t *)(v3 + 4) = sub_56C490((void **)this, *(int **)(*(uint32_t *)(a2 + 4) + 4), v3);
  *(uint32_t *)(this + 8) = *(uint32_t *)(a2 + 8);
  v4 = *(int ***)(this + 4);
  result = v4[1];
  if ( *((uint8_t *)result + 101) != 0 )
  {
    *v4 = (int *)v4;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);
  }
  else
  {
    v6 = (int *)*result;
    if ( *(uint8_t *)(*result + 101) == 0 )
    {
      do
      {
        result = v6;
        v6 = (int *)*v6;
      }
      while ( *((uint8_t *)v6 + 101) == 0 );
    }
    *v4 = result;
    v7 = *(uint32_t *)(this + 4);
    v8 = *(int ***)(v7 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 101) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(v7 + 8) = v8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x56C5D0 sub_56C5D0 —— 频道负载联动 3（56B070/56C540）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_56C5D0(uint32_t *this, int a2)
{
  uint32_t *v3; // eax
  uint32_t v5[8]; // [esp+0h] [ebp-20h] BYREF

  v5[4] = v5;
  v5[3] = this;
  v3 = sub_56B070();
  *(this + 1) = v3;
  *((uint8_t *)v3 + 101) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  v5[7] = 0;
  sub_56C540((int)this, a2);
  return this;
}



// ------------------------------------------------------------
// 0x56C660 sub_56C660 —— 频道信息汇总（220 行：4015C0/401740 + 56AE80/56AE50/56AE20/56AF20/56AF80/56BDF0）
// ------------------------------------------------------------
int ***/*thiscall*/ sub_56C660(uint32_t *this, int ***a2, int **a3)
{
  int **v3; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *v7; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *v15; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  size_t v20; // [esp+34h] [ebp-34h] BYREF
  char v21; // [esp+38h] [ebp-30h]
  int v22; // [esp+48h] [ebp-20h]
  int v23; // [esp+4Ch] [ebp-1Ch]
  int v24; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v26; // [esp+58h] [ebp-10h]
  int v27; // [esp+64h] [ebp-4h]

  v26 = this;
  if ( *((uint8_t *)a3 + 353) != 0 )
  {
    v23 = 15;
    v22 = 0;
    v21 = 0;
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);
    v27 = 0;
    sub_401740(pExceptionObject, &v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_56AE80(&a3);
  if ( *((uint8_t *)*v3 + 353) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 353) == 0 )
      v4[1] = (int)v6;
    v7 = v26;
    v8 = v26[1];
    if ( *(int ***)(v8 + 4) == v3 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == v3 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)v7[1] == v3 )
    {
      if ( *((uint8_t *)v4 + 353) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_56AE50(v4);
        v7 = v26;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v24 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 353) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v24 + 8) = sub_56AE20(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 353) != 0 )
  {
    v4 = *v3;
    goto LABEL_8;
  }
  v5 = (int *)a3;
  v4 = a3[2];
  if ( a3 == v3 )
    goto LABEL_8;
  (*v3)[1] = (int)a3;
  *v5 = (int)*v3;
  if ( v5 == v3[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 353) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)v3[2];
    v3[2][1] = (int)v5;
  }
  v12 = v26[1];
  if ( *(int ***)(v12 + 4) == v3 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)v3[1];
    if ( *v13 == (int *)v3 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)v3[1];
  v14 = *((uint8_t *)v5 + 352);
  *((uint8_t *)v5 + 352) = *((uint8_t *)v3 + 352);
  *((uint8_t *)v3 + 352) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 352) == 1 )
  {
    v15 = v26;
    if ( v4 != *(int **)(v26[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 352) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 352) == 0 )
          {
            *((uint8_t *)v16 + 352) = 1;
            *((uint8_t *)v6 + 352) = 0;
            sub_56AF20(v6);
            v16 = (uint32_t *)v6[2];
            v15 = v26;
          }
          if ( *((uint8_t *)v16 + 353) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 352) != 1 || *(uint8_t *)(v16[2] + 352) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 352) == 1 )
            {
              *(uint8_t *)(*v16 + 352) = 1;
              *((uint8_t *)v16 + 352) = 0;
              sub_56AF80(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 352) = *((uint8_t *)v6 + 352);
            *((uint8_t *)v6 + 352) = 1;
            *(uint8_t *)(v16[2] + 352) = 1;
            sub_56AF20(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 352) == 0 )
          {
            *((uint8_t *)v16 + 352) = 1;
            *((uint8_t *)v6 + 352) = 0;
            sub_56AF80(v6);
            v16 = (uint32_t *)*v6;
            v15 = v26;
          }
          if ( *((uint8_t *)v16 + 353) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 352) != 1 || *(uint8_t *)(*v16 + 352) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 352) == 1 )
            {
              *(uint8_t *)(v16[2] + 352) = 1;
              *((uint8_t *)v16 + 352) = 0;
              sub_56AF20(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 352) = *((uint8_t *)v6 + 352);
            *((uint8_t *)v6 + 352) = 1;
            *(uint8_t *)(*v16 + 352) = 1;
            sub_56AF80(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 352) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 352) = 1;
  }
  sub_56BDF0((int)Block + 16);
  j__free(Block);
  v17 = v26[2];
  if ( v17 != 0 )
    v26[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x56C9C0 sub_56C9C0 —— 频道清理（56C1E0）
// ------------------------------------------------------------
char /*stdcall*/ sub_56C9C0(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 353);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_56C9C0(i[2]);
    i = (void **)*i;
    sub_56C1E0(v1);
    j__free(v1);
    result = *((uint8_t *)i + 353);
  }
  return result;
}



// ------------------------------------------------------------
// 0x56CA10 sub_56CA10 —— 频道汇总件（4014D0/56B840/56C5D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_56CA10(uint32_t *this, int a2)
{
  char *v3; // ecx

  v3 = (char *)(this + 1);
  *this = *(uint32_t *)a2;
  *((uint32_t *)v3 + 6) = 15;
  *((uint32_t *)v3 + 5) = 0;
  v3[4] = 0;
  sub_4014D0((std::_String_base *)v3, a2 + 4, 0, -1);
  *(this + 14) = 15;
  *(this + 13) = 0;
  *((uint8_t *)this + 36) = 0;
  sub_4014D0((std::_String_base *)(this + 8), a2 + 32, 0, -1);
  *(this + 15) = *(uint32_t *)(a2 + 60);
  *(this + 16) = *(uint32_t *)(a2 + 64);
  *(this + 17) = *(uint32_t *)(a2 + 68);
  *(this + 24) = 15;
  *(this + 23) = 0;
  *((uint8_t *)this + 76) = 0;
  sub_4014D0((std::_String_base *)(this + 18), a2 + 72, 0, -1);
  *(this + 31) = 15;
  *(this + 30) = 0;
  *((uint8_t *)this + 104) = 0;
  sub_4014D0((std::_String_base *)(this + 25), a2 + 100, 0, -1);
  `eh vector copy constructor iterator'(
    this + 32,
    (void *)(a2 + 128),
    0x1Cu,
    2,
    (void (/*thiscall*/ *)(void *, void *))sub_401690,
    sub_501490);
  *((uint8_t *)this + 184) = *(uint8_t *)(a2 + 184);
  *(this + 47) = *(uint32_t *)(a2 + 188);
  sub_56B840(this + 48, a2 + 192);
  *(this + 57) = 15;
  *(this + 56) = 0;
  *((uint8_t *)this + 208) = 0;
  sub_4014D0((std::_String_base *)(this + 51), a2 + 204, 0, -1);
  `eh vector copy constructor iterator'(
    this + 58,
    (void *)(a2 + 232),
    0x10u,
    4,
    (void (/*thiscall*/ *)(void *, void *))sub_435020,
    (void (/*thiscall*/ *)(void *))sub_5E5260);
  sub_56C5D0(this + 74, a2 + 296);
  *(this + 83) = 15;
  *(this + 82) = 0;
  *((uint8_t *)this + 312) = 0;
  sub_4014D0((std::_String_base *)(this + 77), a2 + 308, 0, -1);
  return this;
}



// ------------------------------------------------------------
// 0x56CBB0 sub_56CBB0 —— 频道汇总件 2（56C9C0/56AE80/56C660）
// ------------------------------------------------------------
int */*thiscall*/ sub_56CBB0(int **this, int *a2, int a3, int a4)
{
  int v4; // ebx
  int v6; // eax
  int v7; // ecx
  uint32_t *v8; // eax
  int v10; // edi

  v4 = a4;
  v6 = (int)*(this + 1);
  v7 = a3;
  if ( a3 == *(uint32_t *)v6 && a4 == v6 )
  {
    sub_56C9C0(*(void ***)(v6 + 4));
    (*(this + 1))[1] = (int)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int)*(this + 1);
    *a2 = **(this + 1);
    return a2;
  }
  else
  {
    if ( a3 != a4 )
    {
      do
      {
        v10 = v7;
        sub_56AE80(&a3);
        sub_56C660(this, &a4, v10);
        v7 = a3;
      }
      while ( a3 != v4 );
    }
    *a2 = v7;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x56CC30 sub_56CC30 —— 频道汇总件 3（56CA10）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_56CC30(int a1, int a2, int a3, uint32_t *a4, char a5)
{
  uint32_t *v5; // eax
  uint32_t *v6; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  v5 = operator new(0x164u);
  v6 = v5;
  v8[4] = v5;
  v8[8] = (void *)1;
  v8[3] = v5;
  if ( v5 != nullptr )
  {
    *v5 = a1;
    v5[1] = a2;
    v5[2] = a3;
    v5[3] = *a4;
    sub_56CA10(v5 + 4, (int)(a4 + 1));
    *((uint8_t *)v6 + 352) = a5;
    *((uint8_t *)v6 + 353) = 0;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x56CCE0 sub_56CCE0 —— 频道选择装配（4015C0/401740/56CC30/56AF20/56AF80，113 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_56CCE0(int *this, uint32_t *a2, char a3, uint32_t *a4, uint32_t *a5)
{
  uint32_t *v6; // ecx
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int *v10; // eax
  int v11; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  void **pExceptionObject; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v17[20]; // [esp+34h] [ebp-28h] BYREF
  int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]
  uint32_t *v21; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0xC0C0BF )
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
  v6 = sub_56CC30(*(this + 1), (int)a4, *(this + 1), a5, 0);
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
  v10 = v6 + 1;
  v11 = (int)v6;
  if ( *(uint8_t *)(v6[1] + 352) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 352) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_56AF20(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 352) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 352) = 0;
          sub_56AF80(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 352) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_56AF80(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 352) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 352) = 0;
        sub_56AF20(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 352) = 1;
      *(uint8_t *)(v14 + 352) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 352) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 352) != 0 )
      {
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 352) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x56CEF0 sub_56CEF0 —— 频道条目 13（56B0B0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_56CEF0(uint32_t *this)
{
  uint32_t *v2; // eax

  v2 = sub_56B0B0();
  *(this + 1) = v2;
  *((uint8_t *)v2 + 353) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x56CF20 sub_56CF20 —— 频道选择装配 2（56CCE0/56AFF0）
// ------------------------------------------------------------
int /*thiscall*/ sub_56CF20(int *this, int a2, uint32_t *a3)
{
  uint32_t *v3; // ebx
  uint32_t *v5; // esi
  int *v6; // eax
  bool v7; // cl
  int v8; // edx
  uint32_t *v9; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  v3 = a3;
  v5 = (uint32_t *)*(this + 1);
  v6 = (int *)v5[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 353) == 0 )
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
    while ( *((uint8_t *)v6 + 353) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_56CCE0(this, &a3, 1, v5, v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_56AFF0(&a3);
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
    v12 = *sub_56CCE0(this, &a3, v13, v5, v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x56CFE0 sub_56CFE0 —— 频道选择主入口（191 行：56AEE0/56C1F0/56C320/442D00/56BFA0/56BDF0/4FE770/4014D0/423340/418DD0/56B740/56B1A0/4ED3F0/56B4F0/56BBA0/56C540/56CA10/56CF20）
// ------------------------------------------------------------
int /*cdecl*/ sub_56CFE0(int a1)
{
  int v1; // eax
  int v2; // edi
  int *v3; // eax
  int v4; // esi
  const char *v5; // esi
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  int i; // esi
  int v11; // ebx
  int j; // esi
  int v13; // esi
  int v14; // eax
  int v15; // edx
  int *v16; // eax
  int v17; // [esp-4h] [ebp-484h]
  int v18; // [esp-4h] [ebp-484h]
  int v19; // [esp-4h] [ebp-484h]
  int v20; // [esp+Ch] [ebp-474h] BYREF
  char v21[336]; // [esp+10h] [ebp-470h] BYREF
  char v22[4]; // [esp+160h] [ebp-320h] BYREF
  int v23; // [esp+164h] [ebp-31Ch] BYREF
  int v24; // [esp+168h] [ebp-318h] BYREF
  int v25; // [esp+16Ch] [ebp-314h] BYREF
  char v26[28]; // [esp+170h] [ebp-310h] BYREF
  char v27[28]; // [esp+18Ch] [ebp-2F4h] BYREF
  int v28; // [esp+1A8h] [ebp-2D8h]
  int v29; // [esp+1ACh] [ebp-2D4h]
  int v30; // [esp+1B0h] [ebp-2D0h]
  char v31[28]; // [esp+1B4h] [ebp-2CCh] BYREF
  uint8_t v32[88]; // [esp+1D0h] [ebp-2B0h] BYREF
  int v33; // [esp+228h] [ebp-258h]
  uint32_t *v34; // [esp+230h] [ebp-250h]
  uint8_t v35[36]; // [esp+238h] [ebp-248h] BYREF
  void *Src[14]; // [esp+25Ch] [ebp-224h]
  uint32_t *v37; // [esp+298h] [ebp-1E8h]
  char v38[28]; // [esp+2A0h] [ebp-1E0h] BYREF
  int v39; // [esp+2BCh] [ebp-1C4h] BYREF
  char v40[28]; // [esp+2C0h] [ebp-1C0h] BYREF
  char v41[28]; // [esp+2DCh] [ebp-1A4h] BYREF
  char v42[4]; // [esp+2F8h] [ebp-188h] BYREF
  uint32_t v43[7]; // [esp+2FCh] [ebp-184h] BYREF
  char v44[4]; // [esp+318h] [ebp-168h] BYREF
  uint32_t v45[7]; // [esp+31Ch] [ebp-164h] BYREF
  char v46[4]; // [esp+338h] [ebp-148h] BYREF
  uint32_t v47[7]; // [esp+33Ch] [ebp-144h] BYREF
  char v48[28]; // [esp+358h] [ebp-128h] BYREF
  uint8_t v49[88]; // [esp+374h] [ebp-10Ch] BYREF
  int v50; // [esp+3CCh] [ebp-B4h]
  char v51[12]; // [esp+3D0h] [ebp-B0h] BYREF
  uint8_t v52[96]; // [esp+3DCh] [ebp-A4h] BYREF
  int v53; // [esp+43Ch] [ebp-44h]
  int v54; // [esp+440h] [ebp-40h]
  char v55[12]; // [esp+448h] [ebp-38h] BYREF
  char v56[28]; // [esp+454h] [ebp-2Ch] BYREF
  int v57; // [esp+470h] [ebp-10h]
  int v58; // [esp+47Ch] [ebp-4h]

  v57 = dword_796E50;
  v1 = sub_56AEE0(&a1);
  v2 = a1;
  v24 = v1;
  if ( v1 == dword_9B88B4 || a1 < *(uint32_t *)(v1 + 12) )
  {
    v23 = dword_9B88B4;
    v3 = &v23;
  }
  else
  {
    v3 = &v24;
  }
  v4 = *v3;
  if ( *v3 == dword_9B88B4 )
  {
    sub_56C1F0(&v25);
    v58 = 0;
    sub_56C320(&v39);
    LOBYTE(v58) = 1;
    v23 = v2;
    sub_442D00(&v24, &v23);
    if ( v24 == dword_9B6F9C
      || (*(uint32_t *)(v24 + 40) < 0x10u ? (v5 = (const char *)(v24 + 20)) : (v5 = *(const char **)(v24 + 20)),
          v5 == nullptr) )
    {
      off_77F3FC("NPC LOAD FAIL! INDEX %d", v2);
LABEL_14:
      LOBYTE(v58) = 0;
      sub_56BFA0(&v39);
      v58 = -1;
      sub_56BDF0((int)&v25);
      return 0;
    }
    if ( sub_4FE770((int)&v39, v5) == 0 )
    {
      off_77F3FC("NPC LOAD FAIL! FILENAME[%s]", v5);
      goto LABEL_14;
    }
    v25 = v39;
    sub_4014D0((std::_String_base *)v26, v40, 0, -1);
    sub_4014D0((std::_String_base *)v27, v41, 0, -1);
    if ( (uint8_t)sub_423340(v42, szPassword) != 0 )
    {
      v7 = (uint32_t *)v43[0];
      if ( v43[5] < 0x10u )
        v7 = v43;
      v17 = v43[6];
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v7);
      v28 = sub_418DD0(v17);
    }
    if ( (uint8_t)sub_423340(v44, szPassword) != 0 )
    {
      v8 = (uint32_t *)v45[0];
      if ( v45[5] < 0x10u )
        v8 = v45;
      v18 = v45[6];
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v8);
      v29 = sub_418DD0(v18);
    }
    if ( (uint8_t)sub_423340(v46, szPassword) != 0 )
    {
      v9 = (uint32_t *)v47[0];
      if ( v47[5] < 0x10u )
        v9 = v47;
      v19 = v47[6];
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v9);
      v30 = sub_418DD0(v19);
    }
    sub_4014D0((std::_String_base *)v31, v48, 0, -1);
    sub_4014D0((std::_String_base *)v32, v49, 0, -1);
    for ( i = 0; i < 56; i += 28 )
      sub_4014D0((std::_String_base *)&v32[i + 28], &v49[i + 28], 0, -1);
    v32[84] = v49[84];
    sub_56B740(&v23, *v34, v34);
    sub_56B1A0(v51);
    sub_4014D0((std::_String_base *)v35, v52, 0, -1);
    v11 = v23;
    for ( j = 0; j < 16; j += 4 )
    {
      sub_4ED3F0((int)&v35[j * 4 + 28], (int)&v52[j * 4 + 28]);
      sub_56B4F0((int)&v35[j * 4 + 28], (char *)Src[j], v53, v54, v11);
    }
    sub_56BBA0(&v23, *v37, v37);
    sub_56C540(v55);
    sub_4014D0((std::_String_base *)v38, v56, 0, -1);
    v13 = a1;
    v33 = v50;
    v20 = a1;
    sub_56CA10(&v25);
    LOBYTE(v58) = 2;
    sub_56CF20(v22, &v20);
    LOBYTE(v58) = 1;
    sub_56BDF0((int)v21);
    v14 = *(uint32_t *)(dword_9B88B4 + 4);
    v15 = dword_9B88B4;
    while ( *(uint8_t *)(v14 + 353) == 0 )
    {
      if ( *(uint32_t *)(v14 + 12) >= v13 )
      {
        v15 = v14;
        v14 = *(uint32_t *)v14;
      }
      else
      {
        v14 = *(uint32_t *)(v14 + 8);
      }
    }
    v23 = v15;
    if ( v15 == dword_9B88B4 || v13 < *(uint32_t *)(v15 + 12) )
    {
      v24 = dword_9B88B4;
      v16 = &v24;
    }
    else
    {
      v16 = &v23;
    }
    v4 = *v16;
    LOBYTE(v58) = 0;
    sub_56BFA0(&v39);
    v58 = -1;
    sub_56BDF0((int)&v25);
  }
  return v4 + 16;
}


// ============================================================
// 【分区 22】教程窗 CNRDTutorialWindow（0x56D430-0x56DB90）
// vmtC 打开（POP_UP 事件 + 56D4B0 文案）、vmt14 关闭（5461C0 复用）、
// vmt8 Update（CLICK_BUTTON2）。
// ============================================================
// ------------------------------------------------------------
// 0x56D430 CNRDTutorialWindow__vmt8 —— CNRDTutorialWindow__vmt8 Update（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDTutorialWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 10);
  v3 = dword_79BE34;
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12)
    || *(uint8_t *)((v4 = *(this + 11)) + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 20))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v3 = dword_79BE34;
  }
  result = (uint8_t *)*(this + 9);
  if ( result[17] != 0 && v3 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x56D4B0 sub_56D4B0 —— 教程文案装配（69C340/69A5F0/422E70/69C360/69C500）
// ------------------------------------------------------------
bool /*thiscall*/ sub_56D4B0(uint32_t *this, unsigned int a2)
{
  int v3; // eax
  int v4; // ebx
  char *v5; // eax
  int v6; // eax
  int v7; // eax
  uint32_t *v8; // ecx
  int v9; // ebx
  bool result; // al
  int v11; // [esp+Ch] [ebp-4h]

  v3 = *(this + 2);
  v4 = *(uint32_t *)(v3 + 20);
  v11 = *(uint32_t *)(v3 + 24);
  sub_69C340(-1);
  if ( a2 != 0 )
  {
    if ( a2 == 1 )
    {
      sub_69A5F0((uint32_t *)*(this + 3), v4 + 36, v11 + 132);
      v5 = sub_422E70(1169);
    }
    else
    {
      sub_69A5F0((uint32_t *)*(this + 3), v4 + 17, v11 + 58);
      switch ( a2 )
      {
        case 2u:
          v5 = sub_422E70(1170);
          break;
        case 3u:
          v5 = sub_422E70(1171);
          break;
        case 4u:
          v5 = sub_422E70(1172);
          break;
        case 5u:
          v5 = sub_422E70(1173);
          break;
        case 6u:
          v5 = sub_422E70(1174);
          break;
        default:
          goto LABEL_16;
      }
    }
  }
  else
  {
    sub_69A5F0((uint32_t *)*(this + 3), v4 + 52, v11 + 58);
    v5 = sub_422E70(1168);
  }
  sub_69C360(v5, 0);
LABEL_16:
  v6 = sub_69C500(*(this + 3)) + 8;
  if ( a2 == 1 )
    v6 += 6;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 17, v6);
  if ( a2 < 2 )
  {
    *(uint8_t *)(*(this + 9) + 16) = 1;
    *(uint8_t *)(*(this + 10) + 16) = 1;
    *(uint8_t *)(*(this + 11) + 16) = 0;
    sub_69A5F0((uint32_t *)*(this + 9), v4 + 50, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);
    v7 = *(uint32_t *)(*(this + 2) + 32) + v11 - 43;
    v8 = (uint32_t *)*(this + 10);
    v9 = v4 + 113;
  }
  else
  {
    *(uint8_t *)(*(this + 9) + 16) = 0;
    *(uint8_t *)(*(this + 10) + 16) = 0;
    *(uint8_t *)(*(this + 11) + 16) = 1;
    v7 = *(uint32_t *)(*(this + 2) + 32) + v11 - 43;
    v8 = (uint32_t *)*(this + 11);
    v9 = v4 + 82;
  }
  sub_69A5F0(v8, v9, v7);
  result = a2 == 6;
  byte_9B88BC = a2 == 2;
  byte_9B88BD = a2 == 5;
  byte_9B88BE = a2 == 6;
  *(this + 26) = a2;
  if ( a2 == 5 )
    *(this + 8) = 4;
  else
    *(this + 8) = a2 != 6 ? -1 : 8;
  return result;
}



// ------------------------------------------------------------
// 0x56D670 CNRDTutorialWindow__vmt10 —— CNRDTutorialWindow__vmt10 状态切换槽（13 行）
// ------------------------------------------------------------
char CNRDTutorialWindow__vmt10()
{
  byte_9B88BC = 0;
  byte_9B88BD = 0;
  byte_9B88BE = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x56D690 CNRDTutorialWindow__vmtC —— CNRDTutorialWindow__vmtC 打开槽：POP_UP 事件（56D4B0/69A5F0/432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDTutorialWindow__vmtC(uint32_t *this, int a2, unsigned int a3)
{
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // esi

  sub_56D4B0(this, a3);
  v4 = *(this + 26);
  if ( v4 == 5 )
  {
    v5 = 11;
    v6 = 192;
  }
  else if ( v4 == 6 )
  {
    v5 = 212;
    v6 = 199;
  }
  else
  {
    v7 = *(this + 2);
    v5 = (640 - *(uint32_t *)(v7 + 28)) / 2;
    v6 = (480 - *(uint32_t *)(v7 + 32)) / 2;
  }
  sub_69A5F0((uint32_t *)*(this + 2), v5, v6);
  sub_432EA0("POP_UP", -1, 0, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x56D710 CNRDTutorialWindow__vmt0 —— CNRDTutorialWindow__vmt0 构造（418DD0/422E70）
// ------------------------------------------------------------
int /*thiscall*/ CNRDTutorialWindow__vmt0(int *this, int a2)
{
  int result; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  char *v8; // eax
  DWORD Time; // eax
  int v10; // [esp+8h] [ebp-4h]

  result = IRDPopupWindow__vmt0(this, a2);
  if ( a2 == *(this + 2) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    v6 = sub_418DD0(90);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
        v6,
        v4 + 6,
        v5 + 6,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        872415231,
        1333788672,
        1333788672);
    v7 = sub_418DD0(158);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v4 + 7, v5 + 7, dword_79C0B0);
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 13);
    v10 = *(uint32_t *)dword_79C0B0;
    v8 = sub_422E70(1167);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v10 + 80))(dword_79C0B0, v4, v5 + 17, -1190552, v8);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    if ( *(this + 26) == 1 )
    {
      Time = timeGetTime();
      result = sub_418DD0((((458129845LL * Time) & 0x2000000000LL) != 0) + 159);
      if ( result != 0 )
        return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(
                 result,
                 v4 + 36,
                 v5 + 58,
                 dword_79C0B0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x56D840 CNRDTutorialWindow__vmt14 —— CNRDTutorialWindow__vmt14 关闭槽（69C340/69A5F0/422E70/69C360/69C500 + 5461C0 复位）
// ------------------------------------------------------------
char /*thiscall*/ CNRDTutorialWindow__vmt14(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edi
  int v5; // ebx
  char *v6; // eax
  int v7; // eax
  int v9; // eax
  int v10; // edi
  int v11; // ebx
  char *v12; // eax
  int v13; // eax

  v2 = *(this + 26);
  switch ( v2 )
  {
    case 0:
      v3 = *(this + 2);
      v4 = *(uint32_t *)(v3 + 20);
      v5 = *(uint32_t *)(v3 + 24);
      sub_69C340(-1);
      sub_69A5F0((uint32_t *)*(this + 3), v4 + 36, v5 + 132);
      v6 = sub_422E70(1169);
      sub_69C360(v6, 0);
      v7 = sub_69C500(*(this + 3));
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 17, v7 + 14);
      *(uint8_t *)(*(this + 9) + 16) = 1;
      *(uint8_t *)(*(this + 10) + 16) = 1;
      *(uint8_t *)(*(this + 11) + 16) = 0;
      sub_69A5F0((uint32_t *)*(this + 9), v4 + 50, *(uint32_t *)(*(this + 2) + 32) + v5 - 43);
      sub_69A5F0((uint32_t *)*(this + 10), v4 + 113, *(uint32_t *)(*(this + 2) + 32) + v5 - 43);
      byte_9B88BC = 0;
      byte_9B88BD = 0;
      byte_9B88BE = 0;
      *(this + 8) = -1;
      *(this + 26) = 1;
      return 1;
    case 1:
      v9 = *(this + 2);
      v10 = *(uint32_t *)(v9 + 20);
      v11 = *(uint32_t *)(v9 + 24);
      sub_69C340(-1);
      sub_69A5F0((uint32_t *)*(this + 3), v10 + 17, v11 + 58);
      v12 = sub_422E70(1170);
      sub_69C360(v12, 0);
      v13 = sub_69C500(*(this + 3));
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 17, v13 + 8);
      *(uint8_t *)(*(this + 9) + 16) = 0;
      *(uint8_t *)(*(this + 10) + 16) = 0;
      *(uint8_t *)(*(this + 11) + 16) = 1;
      sub_69A5F0((uint32_t *)*(this + 11), v10 + 82, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);
      byte_9B88BC = 1;
      byte_9B88BD = 0;
      byte_9B88BE = 0;
      *(this + 8) = -1;
      *(this + 26) = 2;
      return 1;
    case 2:
      sub_5461C0(*(uint32_t **)(*(this + 4) + 44), 8);
LABEL_11:
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
      return 1;
    case 4:
      sub_5461C0(*(uint32_t **)(*(this + 4) + 44), 10);
      goto LABEL_11;
    case 3:
      sub_5461C0(*(uint32_t **)(*(this + 4) + 44), 9);
      goto LABEL_11;
    default:
      break;
  }
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x56DA00 sub_56DA00 —— 教程关闭回调（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_56DA00(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  int v8; // eax

  *(this + 12) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(this + 12), 152, 153, 154, 152, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  sub_69A840(v3);
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 12), 149, 150, 151, 149, 0, 0);
  else
    v5 = nullptr;
  *(this + 10) = v5;
  sub_69A840(v5);
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(this + 12), 9, 10, 11, 9, 0, 0);
  else
    v7 = nullptr;
  *(this + 11) = v7;
  sub_69A840(v7);
  *((uint8_t *)this + 52) = 0;
  *((uint8_t *)this + 53) = 0;
  *((uint8_t *)this + 54) = 0;
  *((uint8_t *)this + 55) = 0;
  *(this + 16) = 0;
  *(this + 17) = 6;
  *(this + 18) = 12;
  *(this + 19) = 0;
  *(this + 20) = 1600;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  v8 = *this;
  *(this + 25) = dword_99FCCC;
  *(this + 20) = 216;
  *(this + 16) = 1;
  *(this + 14) = -16777216;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v8 + 44))(this, 182, 2048);
}



// ============================================================
// 【分区 23】社区窗 CNRDCommunityWindow（0x56DB90-0x56FB50+）
// 社区面板 0x56DDA0（478EA0/478F40 好友/公会数据）；vmt8 Update（56E1E0/
// 56E360 双页签：479240/42B340/526BF0 私聊 + 527A60）；0x56F460/0x56F660=
// 好友/公会列表重建（479110/479240/430C80）；0x56FB50=社区窗 vmt0 构造
// （291 行：429900/4BF0F0/4BE300/4BE1D0 + 43BCB0）。
// ============================================================
// ------------------------------------------------------------
// 0x56DB90 sub_56DB90 —— 社区数据（42 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_56DB90(uint32_t *this)
{
  uint32_t *v2; // esi
  int i; // ebx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  int result; // eax

  v2 = this + 52;
  for ( i = 2; i != 0; --i )
  {
    if ( *v2 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v2)(*v2, 1);
    *v2++ = 0;
  }
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 54);
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 55);
  *(this + 54) = 0;
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  v6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 56);
  *(this + 55) = 0;
  if ( v6 != nullptr )
    (**v6)(v6, 1);
  v7 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 57);
  result = 0;
  *(this + 56) = 0;
  if ( v7 != nullptr )
    result = (**v7)(v7, 1);
  *(this + 57) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x56DC30 sub_56DC30 —— 社区数据 2（37 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_56DC30(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  uint32_t *v3; // esi
  int i; // ebx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 10) = 0;
  v3 = this + 62;
  for ( i = 2; i != 0; --i )
  {
    if ( *v3 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v3)(*v3, 1);
    *v3++ = 0;
  }
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 64);
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 65);
  result = 0;
  *(this + 64) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  *(this + 65) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x56DCB0 sub_56DCB0 —— 社区数据 3（57 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_56DCB0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  uint32_t *v6; // edi
  int i; // ebx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v10)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 73);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 74);
  *(this + 73) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 75);
  *(this + 74) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 76);
  *(this + 75) = 0;
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  *(this + 76) = 0;
  v6 = this + 77;
  for ( i = 2; i != 0; --i )
  {
    if ( *v6 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v6)(*v6, 1);
    *v6++ = 0;
  }
  v8 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 79);
  if ( v8 != nullptr )
    (**v8)(v8, 1);
  v9 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 81);
  *(this + 79) = 0;
  if ( v9 != nullptr )
    (**v9)(v9, 1);
  v10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 80);
  result = 0;
  *(this + 81) = 0;
  if ( v10 != nullptr )
    result = (**v10)(v10, 1);
  *(this + 80) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x56DDA0 sub_56DDA0 —— 社区面板（429830 + 478EA0/478F40 好友/公会数据）
// ------------------------------------------------------------
void /*thiscall*/ sub_56DDA0(uint32_t *this, int a2)
{
  int v2; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax

  v2 = a2;
  if ( a2 >= 3 )
    return;
  v4 = sub_429830((uint16_t)word_77F804);
  if ( a2 == 1 && v4 != 0 )
    v2 = *(uint32_t *)(v4 + 120) != 0;
  v5 = *(this + 11);
  if ( v2 == v5 )
  {
    if ( v5 == 1 )
    {
      sub_478EA0(0);
    }
    else if ( v5 == 2 )
    {
      sub_478F40(0);
    }
    return;
  }
  if ( v2 == 2 )
    return;
  if ( v5 != 0 )
  {
    v6 = v5 - 1;
    if ( v6 != 0 )
    {
      if ( v6 != 1 )
        goto LABEL_18;
      *(uint8_t *)(*(this + 73) + 16) = 0;
      *(uint8_t *)(*(this + 74) + 16) = 0;
      *(uint8_t *)(*(this + 75) + 16) = 0;
      *(uint8_t *)(*(this + 76) + 16) = 0;
      *(uint8_t *)(*(this + 77) + 16) = 0;
      *(uint8_t *)(*(this + 78) + 16) = 0;
      *(uint8_t *)(*(this + 79) + 16) = 0;
      *(uint8_t *)(*(this + 80) + 16) = 0;
      v7 = *(this + 81);
    }
    else
    {
      *(uint8_t *)(*(this + 62) + 16) = 0;
      *(uint8_t *)(*(this + 63) + 16) = 0;
      *(uint8_t *)(*(this + 64) + 16) = 0;
      v7 = *(this + 65);
    }
  }
  else
  {
    *(uint8_t *)(*(this + 52) + 16) = 0;
    *(uint8_t *)(*(this + 53) + 16) = 0;
    *(uint8_t *)(*(this + 54) + 16) = 0;
    *(uint8_t *)(*(this + 55) + 16) = 0;
    *(uint8_t *)(*(this + 56) + 16) = 0;
    v7 = *(this + 57);
  }
  *(uint8_t *)(v7 + 16) = 0;
LABEL_18:
  if ( v2 != 0 )
  {
    if ( v2 == 1 )
    {
      *(uint8_t *)(*(this + 62) + 16) = 1;
      *(uint8_t *)(*(this + 63) + 16) = 1;
      *(uint8_t *)(*(this + 64) + 16) = 1;
      *(uint8_t *)(*(this + 65) + 16) = 1;
      if ( *(this + 66) == 2 )
        *(this + 66) = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 21);
      sub_478EA0(0);
      *(this + 11) = v2;
    }
  }
  else
  {
    *(uint8_t *)(*(this + 52) + 16) = 1;
    *(uint8_t *)(*(this + 53) + 16) = 1;
    *(uint8_t *)(*(this + 54) + 16) = 1;
    *(uint8_t *)(*(this + 55) + 16) = 1;
    *(uint8_t *)(*(this + 56) + 16) = 1;
    *(uint8_t *)(*(this + 57) + 16) = 1;
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 19);
    *(this + 11) = 0;
  }
}



// ------------------------------------------------------------
// 0x56E000 sub_56E000 —— 社区页部件（418DD0/69A110）
// ------------------------------------------------------------
void /*stdcall*/ sub_56E000(int a1, int a2, int a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax

  if ( a3 != 0 )
  {
    v3 = *(uint32_t *)(a3 + 48);
    if ( v3 != 0 )
    {
      if ( *(uint32_t *)(v3 + 68) != 0 )
        v4 = sub_418DD0(154);
      else
        v4 = sub_418DD0(*(uint32_t *)(v3 + 184) != 0 ? 158 : 155);
      goto LABEL_11;
    }
    if ( *(int *)(a3 + 40) < 0 )
    {
      v4 = sub_418DD0(269);
LABEL_11:
      if ( v4 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v4 + 152))(v4, a1, a2, dword_79C0B0);
      return;
    }
    v5 = sub_418DD0(269);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, a1, a2, dword_79C0B0);
    sub_69A110(a1 + 3, a2 + 7, *(uint32_t *)(a3 + 40), -1);
  }
}



// ------------------------------------------------------------
// 0x56E0D0 CNRDCommunityWindow__vmtC —— CNRDCommunityWindow__vmtC 打开槽（69A5F0 + 56DDA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDCommunityWindow__vmtC(int this, int a2, int a3)
{
  dword_9B88C0 = this;
  sub_69A5F0(*(uint32_t **)(this + 8), 192, 55);
  if ( *(int *)(this + 44) >= 3 )
    sub_56DDA0((uint32_t *)this, 0);
  else
    sub_56DDA0((uint32_t *)this, *(uint32_t *)(this + 44));
  return 1;
}



// ------------------------------------------------------------
// 0x56E120 sub_56E120 —— 好友页数据（25 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_56E120(uint32_t *this)
{
  int v1; // eax
  int v2; // edx
  int v3; // ecx
  int result; // eax
  LONG i; // ecx

  v1 = *(this + 2);
  v2 = *(uint32_t *)(v1 + 20) + 11;
  v3 = *(uint32_t *)(v1 + 24) + 71;
  result = 0;
  for ( i = v3 + 17; pt.x < v2 - 3 || pt.x >= v2 + 226 || pt.y < i - 18 || pt.y >= i; i += 18 )
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x56E180 sub_56E180 —— 公会页数据（25 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_56E180(uint32_t *this)
{
  int v1; // eax
  int v2; // edx
  int v3; // ecx
  int result; // eax
  LONG i; // ecx

  v1 = *(this + 2);
  v2 = *(uint32_t *)(v1 + 20) + 11;
  v3 = *(uint32_t *)(v1 + 24) + 100;
  result = 0;
  for ( i = v3 + 17; pt.x < v2 - 3 || pt.x >= v2 + 226 || pt.y < i - 18 || pt.y >= i; i += 18 )
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x56E1E0 sub_56E1E0 —— 社区好友页 Update（CLICK_BUTTON2 + 56E120/69C690/479240/42B340/526BF0/527A60/432EA0/44E8D0）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_56E1E0(int this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // eax
  unsigned int v5; // edi
  int v6; // eax
  uint32_t *v7; // eax
  int v8; // ecx
  int v9; // edi
  int *v10; // eax
  void *v11; // eax
  int v12; // edi
  int i; // ebx
  int v14; // eax
  uint8_t *result; // eax

  v2 = *(uint32_t *)(this + 8);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    v3 = sub_56E120((uint32_t *)this);
    if ( v3 != -1 )
    {
      v4 = *(uint32_t *)(this + 236);
      v5 = v4 != 0 ? (*(uint32_t *)(this + 240) - v4) >> 2 : 0;
      if ( v3 + sub_69C690(*(uint32_t *)(this + 220)) < v5 )
      {
        v6 = sub_69C690(*(uint32_t *)(this + 220));
        v7 = (uint32_t *)sub_479240((uint32_t *)dword_8F8510, *(uint32_t *)(*(uint32_t *)(this + 236) + 4 * (v3 + v6)));
        v8 = v7[12];
        if ( v8 != 0 )
        {
          v9 = *(uint32_t *)(*(uint32_t *)(this + 16) + 48);
          v10 = (int *)sub_42B340(v8);
          sub_526BF0(v9, v10, 1);
        }
        else
        {
          if ( v7[6] < 0x10u )
            v11 = v7 + 1;
          else
            v11 = (void *)v7[1];
          sub_527A60(*(int ***)(*(uint32_t *)(this + 16) + 48), v11);
        }
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
    }
  }
  v12 = this + 208;
  for ( i = 2; i != 0; --i )
  {
    if ( *(uint8_t *)(*(uint32_t *)v12 + 17) != 0 && dword_79BE34 == *(uint32_t *)(*(uint32_t *)v12 + 12) )
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v12 += 4;
  }
  v14 = *(uint32_t *)(this + 224);
  if ( *(uint8_t *)(v14 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v14 + 12) )
  {
    sub_44E8D0(*(char **)(this + 16), (void *)9, 0, 0);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = *(uint8_t **)(this + 228);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    sub_44E8D0(*(char **)(this + 16), (void *)9, 0, 1);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x56E360 sub_56E360 —— 社区公会页 Update（CLICK_BUTTON2 + 56E180/69C690/479240/42B340/526BF0/527A60/432EA0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_56E360(uint32_t *this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // ecx
  const RECT *v5; // esi
  int v6; // ebx
  int v7; // eax
  unsigned int v8; // esi
  int v9; // eax
  uint32_t *v10; // eax
  int v11; // ecx
  int v12; // esi
  int *v13; // eax
  void *v14; // eax
  uint32_t *v15; // edi
  int i; // esi
  uint32_t *result; // eax
  int v18; // [esp+Ch] [ebp-8h]
  int v19; // [esp+10h] [ebp-4h]

  v2 = *(this + 2);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    v3 = pt.x - *(uint32_t *)(v2 + 20);
    v4 = pt.y - *(uint32_t *)(v2 + 24);
    v18 = v4;
    v19 = 0;
    v5 = &rc;
    while ( !PtInRect(v5, (POINT)__PAIR64__(v4, v3)) )
    {
      ++v5;
      ++v19;
      if ( (int)v5 >= (int)&stru_726304 )
        goto LABEL_9;
      v4 = v18;
    }
    *(this + 66) = v19;
LABEL_9:
    v6 = sub_56E180(this);
    if ( v6 != -1 )
    {
      v7 = *(this + 68);
      v8 = v7 != 0 ? (*(this + 69) - v7) >> 2 : 0;
      if ( v6 + sub_69C690(*(this + 65)) < v8 )
      {
        v9 = sub_69C690(*(this + 65));
        v10 = (uint32_t *)sub_479240((uint32_t *)dword_8F8514, *(uint32_t *)(*(this + 68) + 4 * (v6 + v9)));
        v11 = v10[12];
        if ( v11 != 0 )
        {
          v12 = *(uint32_t *)(*(this + 4) + 48);
          v13 = (int *)sub_42B340(v11);
          sub_526BF0(v12, v13, 1);
        }
        else
        {
          if ( v10[6] < 0x10u )
            v14 = v10 + 1;
          else
            v14 = (void *)v10[1];
          sub_527A60(*(int ***)(*(this + 4) + 48), v14);
        }
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
    }
  }
  v15 = this + 62;
  for ( i = 2; i != 0; --i )
  {
    result = (uint32_t *)*v15;
    if ( *(uint8_t *)(*v15 + 17) != 0 && dword_79BE34 == result[3] )
      result = sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    ++v15;
  }
  return result;
}



// ------------------------------------------------------------
// 0x56E4D0 sub_56E4D0 —— 社区关闭清理（56DB90/56DC30/56DCB0/5542F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_56E4D0(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNRDCommunityWindow;
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 40);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 204);
  *(uint32_t *)(this + 40) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 204) = 0;
  sub_56DB90((uint32_t *)this);
  sub_56DC30((uint32_t *)this);
  sub_56DCB0((uint32_t *)this);
  if ( *(uint32_t *)(this + 336) != 0 )
    j__free(*(void **)(this + 336));
  *(uint32_t *)(this + 336) = 0;
  *(uint32_t *)(this + 340) = 0;
  *(uint32_t *)(this + 344) = 0;
  if ( *(uint32_t *)(this + 272) != 0 )
    j__free(*(void **)(this + 272));
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;
  *(uint32_t *)(this + 280) = 0;
  if ( *(uint32_t *)(this + 236) != 0 )
    j__free(*(void **)(this + 236));
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  if ( *(uint32_t *)(this + 196) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 196));
    *(uint32_t *)(this + 196) = 0;
  }
  *(uint8_t *)(this + 152) = 0;
  *(uint8_t *)(this + 153) = 0;
  *(uint8_t *)(this + 154) = 0;
  *(uint8_t *)(this + 155) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  if ( *(uint32_t *)(this + 144) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 144));
    *(uint32_t *)(this + 144) = 0;
  }
  *(uint8_t *)(this + 100) = 0;
  *(uint8_t *)(this + 101) = 0;
  *(uint8_t *)(this + 102) = 0;
  *(uint8_t *)(this + 103) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  if ( *(uint32_t *)(this + 92) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 92));
    *(uint32_t *)(this + 92) = 0;
  }
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  return sub_5542F0((uint32_t *)this);
}



// ------------------------------------------------------------
// 0x56E6D0 CNRDCommunityWindow__vmt8 —— CNRDCommunityWindow__vmt8 Update（CLICK_BUTTON2 + 56DDA0/56E360/56E1E0 双页签分发）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDCommunityWindow__vmt8(uint32_t *this)
{
  uint32_t *v1; // esi
  int v2; // eax
  uint8_t *result; // eax
  int v4; // eax
  int v5; // edi
  int v6; // ebx
  const RECT *v7; // esi
  int v8; // eax
  int v10; // [esp+8h] [ebp-4h]

  v1 = this;
  sub_69A650(*(this + 2));
  v2 = v1[10];
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*v1 + 32))(v1);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  else
  {
    v4 = v1[2];
    if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
    {
      v5 = pt.x - *(uint32_t *)(v4 + 20);
      v6 = pt.y - *(uint32_t *)(v4 + 24);
      v10 = 0;
      v7 = &stru_7262B4;
      while ( !PtInRect(v7, (POINT)__PAIR64__(v6, v5)) )
      {
        ++v7;
        ++v10;
        if ( (int)v7 >= (int)&rc )
          goto LABEL_11;
      }
      sub_56DDA0(this, v10);
LABEL_11:
      v1 = this;
    }
    v8 = v1[11];
    if ( v8 != 0 )
    {
      result = (uint8_t *)(v8 - 1);
      if ( result == nullptr )
        return sub_56E360(v1);
    }
    else
    {
      return sub_56E1E0((int)v1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x56E7B0 CNRDCommunityWindow__vmt4 —— CNRDCommunityWindow__vmt4 析构（转发 56E4D0 关闭清理）
// ------------------------------------------------------------
void */*thiscall*/ CNRDCommunityWindow__vmt4(void *Block, char a2)
{
  sub_56E4D0((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x56E7E0 sub_56E7E0 —— CNRDCommunityWindow__vmt4 析构主体（426BD0/69C780/69CA20/43C630/69A5F0/69A840，114 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_56E7E0(uint32_t *this)
{
  int v2; // edi
  uint8_t *v3; // ebx
  uint8_t *v4; // eax
  uint8_t *v5; // edi
  int v6; // ebx
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  uint8_t *v9; // eax
  uint32_t *v10; // edi
  int v11; // ebx
  uint32_t *v12; // ecx
  uint8_t *v13; // eax
  uint32_t *v14; // edi
  int v15; // ebx
  uint32_t *v16; // ecx
  int v18; // [esp+10h] [ebp-14h]
  uint32_t *v19; // [esp+14h] [ebp-10h]

  v2 = 4;
  v19 = this + 52;
  do
  {
    v3 = operator new(0x84u);
    if ( v3 != nullptr )
    {
      v18 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v3);
      *(uint32_t *)v3 = &vftbl_nengine__CNButton;
      sub_69C780(v3);
      nengine__CNButton__vmt20(v18, v2, v2, v2 + 1, v2, 0, 0);
    }
    else
    {
      v3 = nullptr;
    }
    *v19 = v3;
    v2 += 2;
    v3[16] = 0;
    ++v19;
  }
  while ( v2 < 8 );
  v4 = operator new(0x88u);
  v5 = v4;
  if ( v4 != nullptr )
  {
    v6 = *(this + 9);
    sub_426BD0(v4);
    *(uint32_t *)v5 = &vftbl_nengine__CNSlider;
    sub_69CA20(v5);
    nengine__CNSlider__vmt20(v6, 218, 86);
    *(uint32_t *)v5 = &vftbl_nengine__CNVSlider;
  }
  else
  {
    v5 = nullptr;
  }
  *(this + 54) = v5;
  v5[16] = 0;
  v7 = operator new(0x74u);
  if ( v7 != nullptr )
    v8 = sub_43C630(v7, *(this + 52), *(this + 53), *(this + 54));
  else
    v8 = nullptr;
  *(this + 55) = v8;
  sub_69A5F0(v8, 239, 71);
  *(uint8_t *)(*(this + 55) + 16) = 0;
  sub_69A840(*(this + 55));
  v9 = operator new(0x84u);
  v10 = v9;
  if ( v9 != nullptr )
  {
    v11 = *(this + 9);
    sub_426BD0(v9);
    *v10 = &vftbl_nengine__CNButton;
    sub_69C780(v10);
    nengine__CNButton__vmt20(v11, 144, 145, 146, 144, 0, 0);
    v12 = v10;
  }
  else
  {
    v12 = nullptr;
  }
  *(this + 56) = v12;
  sub_69A5F0(v12, 54, 231);
  *(uint8_t *)(*(this + 56) + 16) = 0;
  sub_69A840(*(this + 56));
  v13 = operator new(0x84u);
  v14 = v13;
  if ( v13 != nullptr )
  {
    v15 = *(this + 9);
    sub_426BD0(v13);
    *v14 = &vftbl_nengine__CNButton;
    sub_69C780(v14);
    nengine__CNButton__vmt20(v15, 147, 148, 149, 147, 0, 0);
    v16 = v14;
  }
  else
  {
    v16 = nullptr;
  }
  *(this + 57) = v16;
  sub_69A5F0(v16, 136, 231);
  *(uint8_t *)(*(this + 57) + 16) = 0;
  return sub_69A840(*(this + 57));
}



// ------------------------------------------------------------
// 0x56EA90 sub_56EA90 —— 社区页绘制 2（426BD0/69C780/69CA20/43C630/69A5F0/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_56EA90(uint32_t *this)
{
  int v2; // esi
  uint8_t *v3; // edi
  uint8_t *v4; // eax
  uint8_t *v5; // esi
  int v6; // edi
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  int v10; // [esp+10h] [ebp-14h]
  uint32_t *v11; // [esp+14h] [ebp-10h]

  v2 = 4;
  v11 = this + 62;
  do
  {
    v3 = operator new(0x84u);
    if ( v3 != nullptr )
    {
      v10 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v3);
      *(uint32_t *)v3 = &vftbl_nengine__CNButton;
      sub_69C780(v3);
      nengine__CNButton__vmt20(v10, v2, v2, v2 + 1, v2, 0, 0);
    }
    else
    {
      v3 = nullptr;
    }
    *v11 = v3;
    v2 += 2;
    *(uint8_t *)(*(this + 57) + 16) = 0;
    ++v11;
  }
  while ( v2 < 8 );
  v4 = operator new(0x88u);
  v5 = v4;
  if ( v4 != nullptr )
  {
    v6 = *(this + 9);
    sub_426BD0(v4);
    *(uint32_t *)v5 = &vftbl_nengine__CNSlider;
    sub_69CA20(v5);
    nengine__CNSlider__vmt20(v6, 218, 86);
    *(uint32_t *)v5 = &vftbl_nengine__CNVSlider;
  }
  else
  {
    v5 = nullptr;
  }
  *(this + 64) = v5;
  v5[16] = 0;
  v7 = operator new(0x74u);
  if ( v7 != nullptr )
    v8 = sub_43C630(v7, *(this + 62), *(this + 63), *(this + 64));
  else
    v8 = nullptr;
  *(this + 65) = v8;
  sub_69A5F0(v8, 239, 100);
  *(uint8_t *)(*(this + 65) + 16) = 0;
  return sub_69A840(*(this + 65));
}



// ------------------------------------------------------------
// 0x56EC20 sub_56EC20 —— 社区页绘制 3（134 行：43C410/69A5F0/69A840/43C330 + 69C440/69C460/69C480/69C420/69C3E0/69C4C0/69C340/69C400/422E70/69C360 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630/69C500）
// ------------------------------------------------------------
int /*thiscall*/ sub_56EC20(int *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // edi
  uint8_t *v13; // ebx
  uint8_t *v14; // eax
  uint8_t *v15; // edi
  int v16; // ebx
  uint32_t *v17; // eax
  int v18; // edi
  int v19; // eax
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v22; // [esp+14h] [ebp-10h]

  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(this + 9), 168, 169, 170, 168, 0, 0);
  else
    v3 = nullptr;
  *(this + 73) = (int)v3;
  sub_69A5F0(v3, 50, 334);
  *(uint8_t *)(*(this + 73) + 16) = 0;
  sub_69A840(*(this + 73));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 9), 171, 172, 173, 171, 0, 0);
  else
    v5 = nullptr;
  *(this + 74) = (int)v5;
  sub_69A5F0(v5, 132, 334);
  *(uint8_t *)(*(this + 74) + 16) = 0;
  sub_69A840(*(this + 74));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(this + 9), 186, 187, 188, 186, 0, 0);
  else
    v7 = nullptr;
  *(this + 75) = (int)v7;
  sub_69A5F0(v7, 220, 334);
  *(uint8_t *)(*(this + 75) + 16) = 0;
  sub_69A840(*(this + 75));
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
    v9 = sub_43C410(v8, *(this + 9), 176, 177, 178, 176, 0, 0);
  else
    v9 = nullptr;
  *(this + 76) = (int)v9;
  sub_69A5F0(v9, 220, 334);
  *(uint8_t *)(*(this + 76) + 16) = 0;
  sub_69A840(*(this + 76));
  if ( operator new(0x6Cu) != nullptr )
    v10 = sub_43C330(220, 2048);
  else
    v10 = 0;
  *(this + 81) = v10;
  sub_69C440(-5512193);
  sub_69C460(1);
  sub_69C480(-12189696);
  sub_69C420(1);
  sub_69C3E0(19);
  sub_69C4C0(dword_99FCCC);
  sub_69A5F0((uint32_t *)*(this + 81), 13, 73);
  sub_69C340(-1);
  sub_69C400(0);
  v11 = sub_422E70(1525);
  sub_69C360(v11, 0);
  *(uint8_t *)(*(this + 81) + 16) = 0;
  sub_69A840(*(this + 81));
  v12 = 4;
  v22 = this + 77;
  do
  {
    v13 = operator new(0x84u);
    if ( v13 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v13);
      *(uint32_t *)v13 = &nengine::CNButton::`vftable';
      sub_69C780(v13);
      sub_69C7B0(Block, v12, v12, v12 + 1, v12, 0, 0);
    }
    else
    {
      v13 = nullptr;
    }
    *v22 = v13;
    v12 += 2;
    v13[16] = 0;
    ++v22;
  }
  while ( v12 < 8 );
  v14 = operator new(0x88u);
  v15 = v14;
  if ( v14 != nullptr )
  {
    v16 = *(this + 9);
    sub_426BD0(v14);
    *(uint32_t *)v15 = &nengine::CNSlider::`vftable';
    sub_69CA20(v15);
    sub_69CA50(v16, 181, 86);
    *(uint32_t *)v15 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v15 = nullptr;
  }
  *(this + 79) = (int)v15;
  v15[16] = 0;
  if ( operator new(0x74u) != nullptr )
    v17 = (uint32_t *)sub_43C630(*(this + 77), *(this + 78), *(this + 79));
  else
    v17 = nullptr;
  *(this + 80) = (int)v17;
  sub_69A5F0(v17, 237, 68);
  *(uint8_t *)(*(this + 80) + 16) = 0;
  v18 = *(uint32_t *)*(this + 80);
  v19 = sub_69C500(*(this + 81));
  (*(void (/*thiscall*/ **)(uint32_t, int))(v18 + 32))(*(this + 80), v19 - 19);
  return sub_69A840(*(this + 80));
}


// ------------------------------------------------------------
// 0x56F090 sub_56F090 —— 社区页绘制总入口（43C410/69A5F0/69A840/423B30 + 56E7E0/56EA90/56EC20）
// ------------------------------------------------------------
int /*thiscall*/ sub_56F090(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint8_t *v4; // eax
  uint8_t *v5; // eax

  *(uint32_t *)(this + 36) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(this + 36), 23, 24, 25, 23, 0, 0);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 40) = v3;
  sub_69A5F0(v3, 230, 11);
  sub_69A840(*(uint32_t *)(this + 40));
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 96) = dword_99FCCC;
  *(uint8_t *)(this + 50) = 1;
  *(uint32_t *)(this + 52) = -16777216;
  *(uint32_t *)(this + 116) = 6;
  *(uint8_t *)(this + 100) = 0;
  *(uint8_t *)(this + 101) = 0;
  *(uint8_t *)(this + 102) = 0;
  *(uint8_t *)(this + 103) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 120) = 12;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 1600;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 148) = dword_99FCCC;
  *(uint32_t *)(this + 104) = -16777216;
  *(uint32_t *)(this + 128) = 144;
  *(uint8_t *)(this + 102) = 1;
  *(uint32_t *)(this + 112) = 1;
  *(uint32_t *)(this + 132) = 1;
  *(uint8_t *)(this + 152) = 0;
  *(uint8_t *)(this + 153) = 0;
  *(uint8_t *)(this + 154) = 0;
  *(uint8_t *)(this + 155) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 6;
  *(uint32_t *)(this + 172) = 12;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 1600;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 200) = dword_99FCCC;
  *(uint32_t *)(this + 156) = -16777216;
  *(uint32_t *)(this + 164) = 1;
  *(uint32_t *)(this + 184) = 1;
  *(uint8_t *)(this + 154) = 1;
  v4 = operator new(0x2Cu);
  if ( v4 != nullptr )
    v5 = sub_423B30(v4, dword_79C0B0, *(uint32_t *)(this + 36), 258, 2);
  else
    v5 = nullptr;
  *(uint32_t *)(this + 204) = v5;
  sub_56E7E0((uint32_t *)this);
  sub_56EA90((uint32_t *)this);
  sub_56EC20((int *)this);
  return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 28))(this, 2);
}



// ------------------------------------------------------------
// 0x56F2B0 sub_56F2B0 —— 社区页部件（5542C0/5548B0/422E70/56F090）
// ------------------------------------------------------------
int /*thiscall*/ sub_56F2B0(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  sub_5542C0((uint32_t *)this);
  sub_5548B0((uint32_t *)this, a2, 12);
  *(uint32_t *)this = &vftbl_CNRDCommunityWindow;
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint8_t *)(this + 100) = 0;
  *(uint8_t *)(this + 101) = 0;
  *(uint8_t *)(this + 102) = 0;
  *(uint8_t *)(this + 103) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 6;
  *(uint32_t *)(this + 120) = 12;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 1600;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint8_t *)(this + 152) = 0;
  *(uint8_t *)(this + 153) = 0;
  *(uint8_t *)(this + 154) = 0;
  *(uint8_t *)(this + 155) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 6;
  *(uint32_t *)(this + 172) = 12;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 1600;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;
  *(uint32_t *)(this + 280) = 0;
  *(uint32_t *)(this + 336) = 0;
  *(uint32_t *)(this + 340) = 0;
  *(uint32_t *)(this + 344) = 0;
  if ( dword_9B88C4[0] == 0 )
  {
    dword_9B88C4[0] = (int)sub_422E70(921);
    dword_9B88C8[0] = (int)sub_422E70(922);
  }
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 3;
  *(uint32_t *)(this + 264) = 2;
  *(uint32_t *)(this + 328) = 2;
  sub_56F090(this);
  return this;
}



// ------------------------------------------------------------
// 0x56F460 sub_56F460 —— 好友列表重建（479110/479240/430C80，148 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_56F460(int this)
{
  int result; // eax
  void *v2; // eax
  int v3; // esi
  int v4; // eax
  int v5; // edi
  int v6; // edx
  unsigned int v7; // ecx
  int *v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edx
  unsigned int v12; // ecx
  int *v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // edx
  unsigned int v17; // ecx
  int *v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // esi
  int v24; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h] BYREF

  result = dword_8F8510;
  if ( dword_8F8510 != 0 )
  {
    v2 = *(void **)(this + 236);
    v3 = this + 232;
    if ( v2 != nullptr )
      j__free(v2);
    *(uint32_t *)(v3 + 4) = 0;
    *(uint32_t *)(v3 + 8) = 0;
    *(uint32_t *)(v3 + 12) = 0;
    v4 = sub_479110(dword_8F8510);
    v5 = 0;
    v24 = v4;
    for ( i = 0; v5 < v24; i = v5 )
    {
      if ( *(uint32_t *)(sub_479240(v5) + 48) != 0 )
      {
        v6 = *(uint32_t *)(v3 + 4);
        if ( v6 != 0 )
          v7 = (*(uint32_t *)(v3 + 8) - v6) >> 2;
        else
          v7 = 0;
        if ( v6 != 0 && v7 < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
        {
          v8 = *(int **)(v3 + 8);
          *v8 = v5;
          *(uint32_t *)(v3 + 8) = v8 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v3 + 8), 1, (int)&i);
        }
      }
      v4 = v24;
      ++v5;
    }
    v9 = 0;
    i = 0;
    if ( v4 > 0 )
    {
      do
      {
        v10 = sub_479240(v9);
        if ( *(int *)(v10 + 40) >= 0 && *(uint32_t *)(v10 + 48) == 0 )
        {
          v11 = *(uint32_t *)(v3 + 4);
          if ( v11 != 0 )
            v12 = (*(uint32_t *)(v3 + 8) - v11) >> 2;
          else
            v12 = 0;
          if ( v11 != 0 && v12 < (*(uint32_t *)(v3 + 12) - v11) >> 2 )
          {
            v13 = *(int **)(v3 + 8);
            *v13 = v9;
            *(uint32_t *)(v3 + 8) = v13 + 1;
          }
          else
          {
            sub_430C80(*(void **)(v3 + 8), 1, (int)&i);
          }
        }
        v4 = v24;
        i = ++v9;
      }
      while ( v9 < v24 );
    }
    v14 = 0;
    i = 0;
    if ( v4 > 0 )
    {
      do
      {
        v15 = sub_479240(v14);
        if ( *(int *)(v15 + 40) < 0 && *(uint32_t *)(v15 + 48) == 0 )
        {
          v16 = *(uint32_t *)(v3 + 4);
          if ( v16 != 0 )
            v17 = (*(uint32_t *)(v3 + 8) - v16) >> 2;
          else
            v17 = 0;
          if ( v16 != 0 && v17 < (*(uint32_t *)(v3 + 12) - v16) >> 2 )
          {
            v18 = *(int **)(v3 + 8);
            *v18 = v14;
            *(uint32_t *)(v3 + 8) = v18 + 1;
          }
          else
          {
            sub_430C80(*(void **)(v3 + 8), 1, (int)&i);
          }
        }
        i = ++v14;
      }
      while ( v14 < v24 );
    }
    v19 = *(uint32_t *)(v3 + 4);
    if ( v19 != 0 )
      v20 = (*(uint32_t *)(v3 + 8) - v19) >> 2;
    else
      v20 = 0;
    if ( v20 - 8 >= 0 )
    {
      v21 = *(uint32_t *)(v3 + 4);
      if ( v21 != 0 )
        v22 = (*(uint32_t *)(v3 + 8) - v21) >> 2;
      else
        v22 = 0;
      return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 220) + 32))(*(uint32_t *)(this + 220), v22 - 8);
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 220) + 32))(*(uint32_t *)(this + 220), 0);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x56F660 sub_56F660 —— 公会列表重建（479110/479240/430C80，158 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_56F660(int this)
{
  void *v1; // eax
  int v2; // esi
  int v3; // edx
  int v4; // edi
  int v5; // edx
  unsigned int v6; // ecx
  int *v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // edx
  unsigned int v13; // ecx
  int *v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // edx
  unsigned int v20; // ecx
  int *v21; // eax
  int v22; // ecx
  int v23; // eax
  int v25; // eax
  int v26; // esi
  int v28; // [esp+8h] [ebp-8h]
  int v29; // [esp+Ch] [ebp-4h] BYREF

  v1 = *(void **)(this + 272);
  v2 = this + 268;
  if ( v1 != nullptr )
    j__free(v1);
  *(uint32_t *)(v2 + 4) = 0;
  *(uint32_t *)(v2 + 8) = 0;
  *(uint32_t *)(v2 + 12) = 0;
  v3 = sub_479110(dword_8F8514);
  v4 = 0;
  v28 = v3;
  v29 = 0;
  if ( v3 > 0 )
  {
    do
    {
      if ( *(uint32_t *)(sub_479240(v4) + 48) != 0 )
      {
        v5 = *(uint32_t *)(v2 + 4);
        if ( v5 != 0 )
          v6 = (*(uint32_t *)(v2 + 8) - v5) >> 2;
        else
          v6 = 0;
        if ( v5 != 0 && v6 < (*(uint32_t *)(v2 + 12) - v5) >> 2 )
        {
          v7 = *(int **)(v2 + 8);
          *v7 = v4;
          *(uint32_t *)(v2 + 8) = v7 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v2 + 8), 1, (int)&v29);
        }
      }
      v29 = ++v4;
    }
    while ( v4 < v28 );
    v3 = v28;
  }
  v8 = *(uint32_t *)(v2 + 4);
  if ( v8 != 0 )
    v9 = (*(uint32_t *)(v2 + 8) - v8) >> 2;
  else
    v9 = 0;
  v10 = 0;
  *(uint32_t *)(this + 284) = v9;
  v29 = 0;
  if ( v3 > 0 )
  {
    do
    {
      v11 = sub_479240(v10);
      if ( *(int *)(v11 + 40) >= 0 && *(uint32_t *)(v11 + 48) == 0 )
      {
        v12 = *(uint32_t *)(v2 + 4);
        if ( v12 != 0 )
          v13 = (*(uint32_t *)(v2 + 8) - v12) >> 2;
        else
          v13 = 0;
        if ( v12 != 0 && v13 < (*(uint32_t *)(v2 + 12) - v12) >> 2 )
        {
          v14 = *(int **)(v2 + 8);
          *v14 = v10;
          *(uint32_t *)(v2 + 8) = v14 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v2 + 8), 1, (int)&v29);
        }
      }
      v29 = ++v10;
    }
    while ( v10 < v28 );
    v3 = v28;
  }
  v15 = *(uint32_t *)(v2 + 4);
  if ( v15 != 0 )
    v16 = (*(uint32_t *)(v2 + 8) - v15) >> 2;
  else
    v16 = 0;
  v17 = 0;
  *(uint32_t *)(this + 288) = v16;
  v29 = 0;
  if ( v3 > 0 )
  {
    do
    {
      v18 = sub_479240(v17);
      if ( *(int *)(v18 + 40) < 0 && *(uint32_t *)(v18 + 48) == 0 )
      {
        v19 = *(uint32_t *)(v2 + 4);
        if ( v19 != 0 )
          v20 = (*(uint32_t *)(v2 + 8) - v19) >> 2;
        else
          v20 = 0;
        if ( v19 != 0 && v20 < (*(uint32_t *)(v2 + 12) - v19) >> 2 )
        {
          v21 = *(int **)(v2 + 8);
          *v21 = v17;
          *(uint32_t *)(v2 + 8) = v21 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v2 + 8), 1, (int)&v29);
        }
      }
      v29 = ++v17;
    }
    while ( v17 < v28 );
  }
  v22 = *(uint32_t *)(v2 + 4);
  if ( v22 != 0 )
    v23 = (*(uint32_t *)(v2 + 8) - v22) >> 2;
  else
    v23 = 0;
  if ( v23 - 8 < 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 260) + 32))(*(uint32_t *)(this + 260), 0);
  v25 = *(uint32_t *)(v2 + 4);
  if ( v25 != 0 )
    v26 = (*(uint32_t *)(v2 + 8) - v25) >> 2;
  else
    v26 = 0;
  return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 260) + 32))(*(uint32_t *)(this + 260), v26 - 8);
}


// ------------------------------------------------------------
// 0x56F890 sub_56F890 —— 社区好友页装配（56F460/418DD0/69C690/56E120/479240/42B340/4B0EC0/56E000/491530/491630）
// ------------------------------------------------------------
int /*thiscall*/ sub_56F890(uint32_t *this, int a2)
{
  int v3; // ebx
  int v4; // esi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // ecx
  unsigned int v9; // esi
  int v10; // eax
  int v11; // ecx
  uint32_t *v12; // esi
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  uint32_t *v16; // ecx
  int v17; // eax
  int v18; // eax
  int result; // eax
  bool v20; // cc
  int v21; // [esp+Ch] [ebp-18h]
  int v22; // [esp+10h] [ebp-14h]
  int v23; // [esp+14h] [ebp-10h]
  int v24; // [esp+18h] [ebp-Ch]
  int v25; // [esp+1Ch] [ebp-8h]
  int v26; // [esp+20h] [ebp-4h]
  int v27; // [esp+2Ch] [ebp+8h]

  sub_56F460();
  v3 = *(uint32_t *)(a2 + 20);
  v4 = *(uint32_t *)(a2 + 24);
  v5 = sub_418DD0(150);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, v3 + 7, v4 + 65, dword_79C0B0);
  v6 = v3 + 11;
  v22 = v6;
  v27 = v4 + 71;
  v7 = sub_69C690(*(this + 55));
  v8 = *(this + 2);
  v9 = v7;
  v23 = v7;
  if ( *(uint8_t *)(v8 + 17) != 0
    && (dword_79BE3C == *(uint32_t *)(v8 + 12)
     || dword_79BE34 == *(uint32_t *)(v8 + 12)
     || dword_79BE38 == *(uint32_t *)(v8 + 12)) )
  {
    v24 = sub_56E120(this);
  }
  else
  {
    v24 = -1;
  }
  v25 = 0;
  v26 = v27 + 3;
  do
  {
    v10 = sub_418DD0(94);
    if ( v10 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, v6, v27, dword_79C0B0);
    v11 = *(this + 59);
    if ( v11 != 0 && v9 < (*(this + 60) - v11) >> 2 )
    {
      v12 = (uint32_t *)sub_479240(*(uint32_t *)(*(this + 59) + 4 * v9));
      v13 = v12[12];
      if ( v13 != 0 )
      {
        v14 = sub_42B340(v13);
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)v14 + 384))(v14, v6, v27, 16, 16, 1065353216);
      }
      else
      {
        v15 = sub_418DD0(108);
        if ( v15 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v15 + 152))(v15, v6, v27, dword_79C0B0);
      }
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);
      (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v6 + 23,
        v26,
        v12[12] != 0 ? -4928551 : -8947849,
        "Lv.%d",
        v12[7]);
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, this + 25);
      if ( v12[6] < 0x10u )
        v16 = v12 + 1;
      else
        v16 = (uint32_t *)v12[1];
      (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v6 + 17,
        v26,
        v12[12] != 0 ? -4928551 : -8947849,
        v16);
      v21 = *(uint32_t *)dword_79C0B0;
      v17 = sub_4B0EC0(v12[8], v12[9]);
      v6 = v22;
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(v21 + 80))(
        dword_79C0B0,
        v22 + 96,
        v26,
        v12[12] != 0 ? -8005942 : -9934744,
        v17);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      sub_56E000(v22 + 212, v26 - 2, v12);
      if ( v25 == v24 )
      {
        sub_491530(2, 0);
        v18 = sub_418DD0(22);
        if ( v18 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v18 + 152))(v18, v22 - 3, v26 - 4, dword_79C0B0);
        sub_491630(2);
      }
    }
    v27 += 19;
    result = v25 + 1;
    v9 = v23 + 1;
    v20 = ++v25 < 8;
    ++v23;
    v26 += 19;
  }
  while ( v20 );
  return result;
}


// ------------------------------------------------------------
// 0x56FB50 sub_56FB50 —— CNRDCommunityWindow 社区窗构造（291 行：429830/429900/4BF0F0/56F660/418DD0/40FC80/4BE300/422E70/4BE1D0/69C690/43BCB0/56E180/479240/42B340/4B0EC0/56E000/491530/491630/4649B0/56DDA0）
// ------------------------------------------------------------
void /*thiscall*/ sub_56FB50(uint32_t *this, int a2)
{
  int v2; // ebx
  int v3; // edi
  void *v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // edx
  int v14; // edi
  int v15; // ebx
  int v16; // eax
  int v17; // edx
  int v18; // edi
  int v19; // eax
  uint8_t v20; // al
  int v21; // ecx
  int v22; // eax
  int v23; // ecx
  unsigned int v24; // edi
  int v25; // ebx
  int v26; // eax
  int v27; // ecx
  uint32_t *v28; // edi
  int v29; // ecx
  int v30; // eax
  int v31; // eax
  uint32_t *v32; // ecx
  int v33; // edx
  int v34; // eax
  int v35; // eax
  bool v36; // cc
  LONG x; // esi
  LONG y; // edi
  uint8_t v39; // bl
  int v40; // eax
  const char *v41; // eax
  int v42; // [esp-8h] [ebp-248h]
  int v43; // [esp-8h] [ebp-248h]
  int v44; // [esp-8h] [ebp-248h]
  int v45; // [esp-4h] [ebp-244h]
  int v46; // [esp-4h] [ebp-244h]
  int v47; // [esp-4h] [ebp-244h]
  int v48; // [esp-4h] [ebp-244h]
  RECT rc; // [esp+Ch] [ebp-234h] BYREF
  int v50; // [esp+1Ch] [ebp-224h]
  int v51; // [esp+20h] [ebp-220h]
  int v52; // [esp+24h] [ebp-21Ch]
  int v53; // [esp+28h] [ebp-218h]
  int v54; // [esp+2Ch] [ebp-214h]
  int v55; // [esp+30h] [ebp-210h]
  int v56; // [esp+34h] [ebp-20Ch]
  int v57; // [esp+38h] [ebp-208h]
  char Buffer[512]; // [esp+3Ch] [ebp-204h] BYREF
  int v59; // [esp+23Ch] [ebp-4h]
  int v60; // [esp+248h] [ebp+8h]

  v59 = dword_796E50;
  v2 = *(uint32_t *)(a2 + 24);
  v3 = *(uint32_t *)(a2 + 20);
  v60 = v3;
  v51 = v2;
  if ( sub_429830((uint16_t)word_77F804) != 0 )
  {
    v5 = (void *)sub_429900(dword_8F8500);
    if ( v5 != nullptr )
    {
      v56 = sub_4BF0F0(v5);
      sub_56F660((int)this);
      v6 = sub_418DD0(214);
      if ( v6 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v3 + 7, v2 + 65, dword_79C0B0);
      v7 = *(this + 66);
      if ( v7 != 0 )
      {
        if ( v7 == 1 )
        {
          v9 = sub_418DD0(215);
          sub_40FC80(v3 + 141, v2 + 65, v9);
        }
      }
      else
      {
        v8 = sub_418DD0(216);
        if ( v8 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, v3 + 141, v2 + 65, dword_79C0B0);
      }
      v10 = sub_4BE300(v56);
      if ( v10 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, v3 + 11, v2 + 72, dword_79C0B0);
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 38);
      *(this + 41) = 0;
      if ( *(uint32_t *)(dword_8F8514 + 44) < 0x10u )
        v11 = dword_8F8514 + 24;
      else
        v11 = *(uint32_t *)(dword_8F8514 + 24);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v3 + 34,
        v2 + 73,
        -5512193,
        v11);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v12 = sub_418DD0(217);
      if ( v12 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, v3 + 7, v2 + 256, dword_79C0B0);
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 38);
      v13 = *(this + 71);
      v45 = *(this + 72);
      *(this + 45) = 147;
      *(this + 41) = 1;
      v14 = *(uint32_t *)dword_79C0B0;
      v42 = v13;
      v15 = v2 + 263;
      v16 = sub_422E70(923);
      (*(void (/*cdecl*/ **)(int, int, int, int, int, int, int))(v14 + 80))(
        dword_79C0B0,
        v60 + 103,
        v15,
        -4928551,
        v16,
        v42,
        v45);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 38);
      v17 = *(this + 71);
      v46 = *(this + 72);
      *(this + 41) = 0;
      v18 = *(uint32_t *)dword_79C0B0;
      v43 = v17;
      v19 = sub_422E70(924);
      (*(void (/*cdecl*/ **)(int, int, int, int, int, int, int))(v18 + 80))(
        dword_79C0B0,
        v60 + 22,
        v15,
        -4928551,
        v19,
        v43,
        v46);
      if ( (uint8_t)sub_4BE1D0(v56) != 0xFF )
      {
        v55 = *(uint32_t *)dword_79C0B0;
        v20 = sub_4BE1D0(v56);
        (*(void (**)(int, int, int, int, const char *, ...))(v55 + 80))(
          dword_79C0B0,
          v60 + 72,
          v15,
          -701185,
          "%d",
          v20 + 1);
      }
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v21 = *(this + 65);
      v57 = v51 + 100;
      v22 = sub_69C690(v21);
      v23 = *(this + 2);
      v24 = v22;
      v53 = v22;
      if ( (uint8_t)sub_43BCB0(v23) == 1 )
        v52 = sub_56E180(this);
      else
        v52 = -1;
      v25 = v51 + 103;
      v54 = 0;
      v55 = v51 + 103;
      do
      {
        v26 = sub_418DD0(94);
        if ( v26 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v26 + 152))(v26, v60 + 12, v57, dword_79C0B0);
        v27 = *(this + 68);
        if ( v27 != 0 && v24 < (*(this + 69) - v27) >> 2 )
        {
          v28 = (uint32_t *)sub_479240(*(uint32_t *)(*(this + 68) + 4 * v24));
          v29 = v28[12];
          if ( v29 != 0 )
          {
            v30 = sub_42B340(v29);
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)v30 + 384))(
              v30,
              v60 + 12,
              v57,
              16,
              16,
              1065353216);
          }
          else
          {
            v31 = sub_418DD0(108);
            if ( v31 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v31 + 152))(v31, v60 + 12, v57, dword_79C0B0);
          }
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);
          (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v60 + 35,
            v25,
            v28[12] != 0 ? -4928551 : -8947849,
            "Lv.%d",
            v28[7]);
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, this + 25);
          if ( v28[6] < 0x10u )
            v32 = v28 + 1;
          else
            v32 = (uint32_t *)v28[1];
          (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v60 + 29,
            v25,
            v28[12] != 0 ? -4928551 : -8947849,
            v32);
          if ( *(this + 66) == 0 )
          {
            v33 = v28[8];
            v47 = v28[9];
            v50 = *(uint32_t *)dword_79C0B0;
            v34 = sub_4B0EC0(v33, v47);
            v25 = v55;
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(v50 + 80))(
              dword_79C0B0,
              v60 + 108,
              v55,
              v28[12] != 0 ? -8005942 : -9934744,
              v34);
          }
          if ( *(this + 66) == 1 )
            (*(void (/*cdecl*/ **)(int, int, int, unsigned int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
              dword_79C0B0,
              v60 + 108,
              v25,
              v28[12] != 0 ? (unsigned int)&loc_5C1D6C + 2 - 9934744 : -9934744,
              v28 + 13);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
          sub_56E000(v60 + 224, v25 - 2, v28);
          if ( v54 == v52 )
          {
            sub_491530(2, 0);
            v35 = sub_418DD0(22);
            if ( v35 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v35 + 152))(v35, v60 + 9, v25 - 4, dword_79C0B0);
            sub_491630(2);
          }
        }
        v24 = v53 + 1;
        v25 += 19;
        v36 = ++v54 < 8;
        ++v53;
        v57 += 19;
        v55 = v25;
      }
      while ( v36 );
      if ( (uint8_t)sub_4BE1D0(v56) != 0xFF )
      {
        x = pt.x;
        y = pt.y;
        v39 = sub_4BE1D0(v56);
        rc.left = v60 + 7;
        rc.top = v51 + 256;
        rc.right = v60 + 98;
        rc.bottom = v51 + 281;
        if ( PtInRect(&rc, (POINT)__PAIR64__(y, x)) )
        {
          if ( v39 == 1 )
          {
            sprintf(Buffer, "%s\n", (const char *)dword_9B88C8[0]);
          }
          else
          {
            v40 = v39;
            v48 = dword_9B88C8[v40];
            v44 = dword_9B88C4[v40];
            v41 = (const char *)sub_422E70(925);
            sprintf(Buffer, v41, v44, v48);
          }
          sub_4649B0(rc.left + (rc.right - rc.left) / 2, rc.top - 2, -1, -16777216, 2, Buffer, 0, 0, 1600, 1);
        }
      }
    }
    else
    {
      sub_56DDA0(this, 0);
    }
  }
}

