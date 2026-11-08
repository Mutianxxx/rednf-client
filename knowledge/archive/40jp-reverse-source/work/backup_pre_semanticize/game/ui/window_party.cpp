// ============================================================
// 【40JP逆向源代码工程】ui/window_party.cpp
// 模块: 0x63 区块 —— CNRD 窗口族虚方法实现层（组队/PVP/公会/确认弹窗/结果窗）
// 来源: work/dump_skills.txt  区块: 0x630000-0x640000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 266
// ------------------------------------------------------------
// ★ 本文件是 IRDWindow 派生窗口类的 vtable 覆写实现集中地，与
//   cashshop.cpp 中的 vmt4 析构三件套一一配对。槽位语义（以
//   CNRDYesNoConfirmWindow/CNRDPartyRecommendUserWindow 实读定案）：
//     vmt0 = 构造/主虚表装配（418DD0 取控件、491530/491630 绘制批次）
//     vmt4 = 标量删除析构（cashshop.cpp 侧）
//     vmt8 = 逐帧 Update：悬停判定（+17 激活标志 && dword_79BE34==控件 X
//            ——鼠标坐标全局），按下触发 vt+56(确认)/vt+60(取消)/vt+32(关闭)
//            并播 CLICK_BUTTON2
//     vmtC = 打开/刷新（69A5F0 定位、44BBA0=WINDOW_SHOW、列表重建）
//     vmt10 = 页签/状态切换（44AB50）
//     vmt14 = 关闭/ESC 路径（vt+56 + vt+32）
//     vmt38/vmt3C = 确认/取消动作（商城购买、交易、成员响应等）
//   事件音：CLICK_BUTTON2=按钮、WINDOW_CLOSE=关窗、TAB_SELECT=页签、
//   POP_UP=弹窗开、422E70=字符串表取串。
// ------------------------------------------------------------
// 内容分区：合成窗/组队列表/PVP 频道与房间/好友与社区/各类确认弹窗/
//   强化与分解/赌博/副本与交易结果/任务奖励/转职/物品盒/战争房间。
//   关键标签：RECIPE_OPEN、GET_SKILL、QUEST_ABANDON、POP_UP、
//   EQUIP_BROKEN/STRENGTHEN_SUCCESS/FAIL/ZERO（强化结果 0x63AC20）、
//   GAMBLE_OPEN_LOOP/GAMBLE_RESULT_COMMON/GOOD（赌博 0x63D940）、
//   DISSOLVE_ITEM（分解 0x63DED0）、REWARD_OPEN2（副本结算 0x63E6B0）；
//   资源：interface/cashshop/cashshopdoubleevent.img（0x6387C0）、
//   etc/reseal.etc（再封 0x63B900）。
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】合成窗口 CNRDCompoundItemWindow（0x630060-0x630690）
// vmtC 打开主函数（245 行）含 RECIPE_OPEN 配方打开事件；0x630060=
// 合成条目辅助（62FFF0/62FBB0）。
// ============================================================
// ------------------------------------------------------------
// 0x630060 sub_630060 —— 合成条目辅助（62FFF0 + 62FBB0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_630060(int this, int *a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  uint32_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 44;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 44 )
    return sub_62FFF0((int *)this, &a2, *(char **)(this + 8), a2);
  v5 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_62FBB0(v5, 1, a2);
  *(uint32_t *)(this + 8) = v5 + 44;
  return result;
}



// ------------------------------------------------------------
// 0x6300F0 CNRDCompoundItemWindow__vmtC —— CNRDCompoundItemWindow__vmtC 打开主函数（245 行：69C340 系文本 + 4F6390/62FA00 配方 + RECIPE_OPEN 事件 + 630060 条目）
// ------------------------------------------------------------
char /*thiscall*/ sub_6300F0(uint8_t *this, uint32_t *a2, int a3)
{
  uint8_t *v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  uint32_t *v11; // ebx
  int v12; // eax
  int v13; // edi
  void *v14; // eax
  int v15; // ecx
  unsigned int v16; // eax
  uint32_t *v18; // eax
  int v19; // ebx
  int v20; // ecx
  int v21; // eax
  bool v22; // cc
  int i; // edi
  int v24; // eax
  void *v25; // eax
  int v26; // eax
  int v27; // ecx
  int v28; // eax
  int v29; // edx
  unsigned int v30; // eax
  int v31; // edx
  int v32; // ecx
  uint32_t *v33; // ecx
  int v34; // ebx
  int v35; // edi
  int v36; // ecx
  int v37; // eax
  int v38; // ecx
  int v39; // eax
  bool v40; // zf
  int v41; // eax
  uint8_t *v42; // [esp+Ch] [ebp-48h]
  uint32_t *v43; // [esp+10h] [ebp-44h]
  int v44; // [esp+14h] [ebp-40h]
  uint32_t *v45; // [esp+14h] [ebp-40h]
  int v46; // [esp+18h] [ebp-3Ch] BYREF
  void *Block; // [esp+20h] [ebp-34h]
  unsigned int v48; // [esp+34h] [ebp-20h]
  int v49; // [esp+38h] [ebp-1Ch]
  int v50; // [esp+3Ch] [ebp-18h]
  int v51; // [esp+40h] [ebp-14h]
  int v52; // [esp+44h] [ebp-10h]
  int v53; // [esp+50h] [ebp-4h]
  char v54; // [esp+5Fh] [ebp+Bh]
  bool v55; // [esp+63h] [ebp+Fh]

  v52 = dword_796E50;
  v4 = __RTDynamicCast(a2, 0, &IRDItem `RTTI Type Descriptor', &CNRecipeStackable `RTTI Type Descriptor', 0);
  v42 = v4;
  *(this + 200) = a3 == 1;
  if ( v4 == nullptr )
    return 0;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 108))(a2);
  v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v5);
  if ( v6 >= 126 )
    v6 = 126;
  *((uint32_t *)this + 14) = 114 - (v6 + 35) / 2;
  sub_69C340(-1);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 108))(a2);
  sub_69C360(v7, 0);
  *((uint32_t *)this + 12) = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 16))(a2) + 4);
  v8 = *((uint32_t *)v4 + 41);
  *((uint32_t *)this + 13) = v8;
  if ( v8 == 4 )
    return 0;
  v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 16))(a2);
  sub_4F6390((uint32_t *)this + 16, v9 + 88);
  sub_62FA00(&v46);
  v53 = 0;
  sub_55A090(this + 116);
  sub_55A090(this + 132);
  v10 = sub_4F33A0(**((uint32_t **)this + 21));
  v11 = *((uint32_t **)this + 25);
  *((uint32_t *)this + 15) = v10;
  v54 = 1;
  if ( v11 != *((uint32_t **)this + 26) )
  {
    while ( 1 )
    {
      v12 = sub_47DC90(*v11);
      v13 = v12;
      if ( v12 == 0 )
        break;
      v50 = v11[1];
      v49 = sub_41A5E0(v12 + 510);
      v14 = (void *)sub_41ACF0(v13 + 20);
      sub_4015C0(v14, strlen((const char *)v14));
      v46 = *(uint32_t *)(v13 + 4 * (v49 < v50) + 380);
      v51 = v49 < v50 ? -15132207 : -16723573;
      sub_630060(&v46);
      if ( v49 < v50 )
        v54 = 0;
      v11 += 2;
      if ( v11 == *((uint32_t **)this + 26) )
        goto LABEL_10;
    }
    if ( v48 >= 0x10 )
    {
      j__free(Block);
      return 0;
    }
    return 0;
  }
LABEL_10:
  v15 = *((uint32_t *)this + 17);
  if ( v15 != 0 )
    v16 = (*((uint32_t *)this + 18) - v15) >> 3;
  else
    v16 = 0;
  v55 = v16 > 6;
  v44 = dword_8F7C04;
  if ( dword_8F7C04 == 0 )
  {
    if ( v48 >= 0x10 )
      j__free(Block);
    return 0;
  }
  v18 = *((uint32_t **)this + 17);
  v43 = v18;
  if ( v18 != *((uint32_t **)this + 18) )
  {
    while ( 1 )
    {
      v19 = *v18;
      v50 = v18[1];
      v20 = sub_484E00(v19);
      v21 = v50;
      v22 = v20 <= v50;
      v49 = v20;
      if ( v20 < v50 )
      {
        for ( i = 0; i < 18; ++i )
        {
          v24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v44 + 792))(v44, i);
          if ( v24 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v24 + 16))(v24) + 4) == v19 )
            ++v49;
        }
        v21 = v50;
        v22 = v49 <= v50;
      }
      if ( !v22 )
        v49 = v21;
      v25 = (void *)sub_4F2CE0(v19);
      sub_4015C0(v25, strlen((const char *)v25));
      v46 = sub_4F33A0(v19);
      if ( v49 < v50 )
      {
        v51 = -15132207;
      }
      else
      {
        v26 = sub_4F2D60(v19);
        v51 = sub_4F2DF0(v26);
      }
      sub_630060(&v46);
      if ( v49 < v50 )
        v54 = 0;
      v43 += 2;
      if ( v43 == *((uint32_t **)this + 18) )
        break;
      v18 = v43;
    }
  }
  v27 = *((uint32_t *)this + 25);
  if ( v27 != 0 )
    v28 = (*((uint32_t *)this + 26) - v27) >> 3;
  else
    v28 = 0;
  v29 = *((uint32_t *)this + 17);
  v30 = 3 * (((unsigned int)(v28 + 1) >> 1) + 4);
  if ( v55 )
  {
    if ( v29 != 0 && (unsigned int)((*((uint32_t *)this + 18) - v29) >> 3) >= 6 )
    {
      v30 += 18;
    }
    else
    {
      v31 = *((uint32_t *)this + 17);
      if ( v31 != 0 )
        v30 += ((*((uint32_t *)this + 18) - v31) >> 3) + 2 * ((*((uint32_t *)this + 18) - v31) >> 3);
    }
  }
  else
  {
    if ( v29 != 0 )
      v32 = (*((uint32_t *)this + 18) - v29) >> 3;
    else
      v32 = 0;
    v30 += v32 + 2 * v32;
  }
  (*(void (/*thiscall*/ **)(uint8_t *, int, unsigned int))(*(uint32_t *)this + 24))(this, 18, v30);
  v33 = *((uint32_t **)this + 2);
  v34 = (480 - v33[8]) / 2;
  v35 = (640 - v33[7]) / 2;
  sub_69A5F0(v33, v35, v34);
  sub_69A5F0(*((uint32_t **)this + 9), v35 + 115, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v34 - 37);
  sub_69A5F0(*((uint32_t **)this + 10), v35 + 7, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v34 - 37);
  if ( v55 )
  {
    v36 = *((uint32_t *)this + 17);
    if ( v36 != 0 )
      v37 = (*((uint32_t *)this + 18) - v36) >> 3;
    else
      v37 = 0;
    (*(void (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)this + 54) + 32))(*((uint32_t *)this + 54), v37 - 6);
    *(uint8_t *)(*((uint32_t *)this + 54) + 16) = 1;
    v38 = *((uint32_t *)this + 25);
    if ( v38 != 0 )
      v39 = (*((uint32_t *)this + 26) - v38) >> 3;
    else
      v39 = 0;
    sub_69A5F0(*((uint32_t **)this + 54), v35 + 205, 39 * ((unsigned int)(v39 + 1) >> 1) + v34 + 124);
  }
  else
  {
    *(uint8_t *)(*((uint32_t *)this + 54) + 16) = 0;
  }
  v45 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3);
  if ( *v45 < sub_667620(v42) )
    v54 = 0;
  v40 = sub_69C500(*((uint32_t *)this + 3)) == 1;
  v41 = v34 + 27;
  if ( !v40 )
    v41 = v34 + 20;
  sub_69A5F0(*((uint32_t **)this + 3), *((uint32_t *)this + 14) + v35 + 35, v41);
  *(uint8_t *)(*((uint32_t *)this + 9) + 17) = v54;
  sub_432EA0("RECIPE_OPEN", -1, 0, 0);
  if ( v48 >= 0x10 )
    j__free(Block);
  return 1;
}


// ------------------------------------------------------------
// 0x6305E0 sub_6305E0 —— 合成窗辅助（21 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6305E0(uint32_t *this)
{
  *(this + 9) = 2;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  return 0;
}



// ============================================================
// 【分区 2】组队列表窗口 CNRDPartyListWindow（0x630610-0x631FF0）
// vmt0 构造（353 行：6306A0/636190 列表件 + 456390/4569F0 组队查询）；
// vmt8 Update（CLICK_BUTTON2）、vmtC 打开（6312F0 列表重建 251 行）。
// ============================================================
// ------------------------------------------------------------
// 0x630610 sub_630610 —— 组队列表数据准备（47 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_630610(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 11) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  *(this + 12) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  v7 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  *(this + 14) = 0;
  if ( v7 != nullptr )
    result = (**v7)(v7, 1);
  v8 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 22);
  *(this + 15) = 0;
  if ( v8 != nullptr )
    result = (**v8)(v8, 1);
  v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 23);
  *(this + 22) = 0;
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  *(this + 23) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x630690 CNRDPartyListWindow__vmt10 —— CNRDPartyListWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDPartyListWindow__vmt10()
{
  dword_9B9458 = 0;
}



// ------------------------------------------------------------
// 0x6306A0 sub_6306A0 —— 组队列表构建（57 行：456480/456390 组队查询 + 69C980）
// ------------------------------------------------------------
int /*thiscall*/ sub_6306A0(int *this)
{
  int result; // eax
  int v2; // ecx
  LONG v3; // edx
  LONG v4; // ecx
  LONG j; // esi
  int v6; // ecx
  int v7; // edx
  LONG v8; // ecx
  LONG v9; // edx
  LONG i; // esi

  result = *(this + 9);
  if ( result != 0 )
  {
    if ( result == 1 )
    {
      v6 = *(this + 2);
      v7 = *(uint32_t *)(v6 + 20);
      v8 = *(uint32_t *)(v6 + 24) + 66;
      v9 = v7 + 14;
      result = 0;
      for ( i = v8 + 16; pt.x < v9 || pt.x >= v9 + 230 || pt.y < v8 || pt.y >= i; i += 21 )
      {
        ++result;
        v8 += 21;
        if ( result >= 4 )
          return -1;
      }
    }
    else
    {
      return -1;
    }
  }
  else
  {
    v2 = *(this + 2);
    v3 = *(uint32_t *)(v2 + 20) + 8;
    v4 = *(uint32_t *)(v2 + 24) + 34;
    for ( j = v4 + 20; pt.x < v3 || pt.x >= v3 + 242 || pt.y < v4 || pt.y >= j; j += 24 )
    {
      ++result;
      v4 += 24;
      if ( result >= 7 )
        return -1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x630750 sub_630750 —— 组队列表页绘制（456480/429830/456390/69C980，25 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_630750(uint32_t *this)
{
  uint32_t *v2; // edi
  int v3; // edi

  if ( *(this + 9) == 1 )
  {
    v2 = (uint32_t *)dword_8F850C;
    if ( sub_456480((uint32_t *)dword_8F850C) == -1 )
      v3 = 0;
    else
      v3 = v2[sub_456480(v2) + 4];
    *(uint8_t *)(*(this + 22) + 17) = v3 == sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    if ( sub_456390((char *)dword_8F850C, 0) > 1 )
      sub_69C980(*(this + 10), 119, 120, 121, 122, 0, 0);
    else
      sub_69C980(*(this + 10), 116, 117, 118, 116, 0, 0);
  }
}



// ------------------------------------------------------------
// 0x6307E0 sub_6307E0 —— 组队创建提交辅助（17 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6307E0(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 2);
  if ( v1 != 0 )
    return dword_9B8890[(v1 - 1) % 6];
  if ( *(this + 9) < 0x10u )
    return (int)(this + 4);
  return *(this + 4);
}



// ------------------------------------------------------------
// 0x630810 CNRDPartyListWindow__vmt0 —— CNRDPartyListWindow__vmt0 构造（353 行：554930 + 6306A0/636190 列表 + 456390/4569F0 + 56A720）
// ------------------------------------------------------------
char /*userpurge*/ sub_630810@<al>(uint32_t *a1@<ecx>, uint32_t *a2@<esi>, int a3)
{
  int v4; // eax
  int v5; // esi
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  unsigned int v9; // ebx
  int v10; // eax
  int v11; // ecx
  uint32_t *v12; // eax
  uint32_t *v13; // esi
  int v14; // eax
  int v15; // edx
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  bool v19; // cc
  int v20; // ecx
  int v21; // esi
  uint32_t *v22; // edi
  int v23; // eax
  int v24; // eax
  uint32_t *v25; // ebx
  int v26; // eax
  int v27; // edx
  int v28; // ebx
  int v29; // esi
  int v30; // eax
  uint32_t *v31; // eax
  uint32_t *v32; // esi
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // eax
  uint32_t *v37; // ecx
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // eax
  int v42; // ecx
  int v43; // esi
  int v44; // ebx
  unsigned int v45; // esi
  int v46; // eax
  int v47; // eax
  int v49; // [esp-18h] [ebp-40h]
  int v51; // [esp+8h] [ebp-20h]
  int v52; // [esp+8h] [ebp-20h]
  int v53; // [esp+Ch] [ebp-1Ch]
  int v54; // [esp+10h] [ebp-18h]
  int v55; // [esp+10h] [ebp-18h]
  int v56; // [esp+14h] [ebp-14h]
  unsigned int v57; // [esp+18h] [ebp-10h]
  uint32_t *v58; // [esp+18h] [ebp-10h]
  int v59; // [esp+1Ch] [ebp-Ch]
  int v60; // [esp+20h] [ebp-8h]
  int v61; // [esp+20h] [ebp-8h]
  int v62; // [esp+24h] [ebp-4h]
  int v63; // [esp+24h] [ebp-4h]
  int v64; // [esp+30h] [ebp+8h]
  int v65; // [esp+30h] [ebp+8h]
  int v66; // [esp+30h] [ebp+8h]

  LOBYTE(v4) = sub_554930(a3);
  if ( a3 == a1[2] )
  {
    v5 = *(uint32_t *)(a3 + 20);
    v6 = *(uint32_t *)(a3 + 24);
    v64 = v5;
    v56 = v6;
    v7 = sub_418DD0(109);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v5 + 6, v6 + 6, dword_79C0B0);
    if ( a1[9] != 0 )
    {
      v23 = sub_418DD0(123);
      if ( v23 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v23 + 152))(v23, v5 + 100, v6 + 12, dword_79C0B0);
      v24 = sub_418DD0(132);
      if ( v24 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v24 + 152))(v24, v5 + 8, v6 + 35, dword_79C0B0);
      v4 = sub_429830((uint16_t)word_77F804);
      v25 = *(uint32_t **)(v4 + 184);
      v58 = v25;
      if ( v25 != nullptr )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 37);
        v26 = v25[2];
        if ( v26 != 0 )
        {
          v27 = dword_9B8890[(v26 - 1) % 6];
        }
        else if ( v25[9] < 0x10u )
        {
          v27 = (int)(v25 + 4);
        }
        else
        {
          v27 = v25[4];
        }
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v5 + 29,
          v56 + 42,
          -804984,
          v27);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v28 = v5 + 14;
        v29 = v56 + 66;
        v61 = v56 + 66;
        if ( (uint8_t)sub_43BCB0(a1[2]) != 0 )
          v55 = sub_6306A0(a1);
        else
          v55 = -1;
        v63 = 0;
        v65 = v56 + 69;
        while ( 1 )
        {
          v30 = sub_418DD0(45);
          if ( v30 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v30 + 152))(v30, v28, v29, dword_79C0B0);
          v31 = (uint32_t *)sub_636190(v58, v63);
          v32 = v31;
          if ( v31 != nullptr )
          {
            v33 = sub_42B340(v31);
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t *))(*(uint32_t *)v33 + 384))(
              v33,
              v28,
              v61,
              16,
              16,
              1065353216,
              a2);
            if ( v63 == v58[14] )
            {
              v34 = sub_418DD0(106);
              if ( v34 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v34 + 152))(v34, v28 - 1, v65 - 4, dword_79C0B0);
            }
            else
            {
              v35 = sub_418DD0(107);
              if ( v35 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v35 + 152))(v35, v28, v61, dword_79C0B0);
            }
            a2 = a1 + 24;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);
            v36 = sub_41A5E0((unsigned int)v32 + 53);
            (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
              dword_79C0B0,
              v28 + 31,
              v65,
              -4732715,
              "Lv.%d",
              v36);
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, a1 + 37);
            if ( v32[10] < 0x10u )
              v37 = v32 + 5;
            else
              v37 = (uint32_t *)v32[5];
            (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
              dword_79C0B0,
              v28 + 17,
              v65,
              -4732715,
              v37);
            v52 = *(uint32_t *)dword_79C0B0;
            v38 = sub_4B0EC0(v32[11], v32[12]);
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(v52 + 80))(dword_79C0B0, v28 + 102, v65, -8005942, v38);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
            if ( v63 == v55 )
            {
              sub_491530(2, 0);
              v39 = sub_418DD0(46);
              if ( v39 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v39 + 152))(v39, v28 - 6, v65 - 5, dword_79C0B0);
              sub_491630(2);
            }
          }
          else if ( v63 >= v58[15] )
          {
            v40 = sub_418DD0(108);
            if ( v40 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v40 + 152))(v40, v28, v61, dword_79C0B0);
            v41 = sub_418DD0(122);
            if ( v41 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v41 + 152))(v41, v28 + 28, v65 - 2, dword_79C0B0);
          }
          v19 = ++v63 < 4;
          v61 += 21;
          v65 += 21;
          if ( !v19 )
            break;
          v29 = v61;
        }
        v42 = a1[22];
        if ( *(uint8_t *)(v42 + 17) != 0 )
        {
          v43 = *(uint32_t *)(v42 + 12);
          if ( dword_79BE3C == v43 || dword_79BE34 == v43 || dword_79BE38 == v43 )
          {
            v22 = (uint32_t *)a1[22];
            v49 = 1128;
            goto LABEL_75;
          }
        }
        LOBYTE(v4) = sub_43BCB0(a1[23]);
        if ( (uint8_t)v4 != 0 )
        {
          if ( (int)sub_456390(0) > 1 )
            v47 = sub_422E70(1130);
          else
            v47 = sub_422E70(1129);
          LOBYTE(v4) = sub_4649B0(
                         *(uint32_t *)(a1[23] + 20) + (*(uint32_t *)(a1[23] + 28) >> 1),
                         *(uint32_t *)(a1[23] + 24),
                         -1,
                         -16777216,
                         2,
                         v47,
                         0,
                         0,
                         1600,
                         0);
        }
      }
    }
    else
    {
      v8 = sub_418DD0(124);
      if ( v8 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, v5 + 107, v6 + 12, dword_79C0B0);
      v60 = v6 + 34;
      v9 = 7 * a1[20];
      v57 = v9;
      if ( (uint8_t)sub_43BCB0(a1[2]) != 0 )
        v54 = sub_6306A0(a1);
      else
        v54 = -1;
      v59 = 0;
      v62 = v60 + 5;
      do
      {
        v10 = sub_418DD0(21);
        if ( v10 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 128))(
            v10,
            v5 + 8,
            v60,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1929379841,
            1333788672,
            1333788672);
        v11 = a1[17];
        if ( v11 != 0 && v9 < (a1[18] - v11) >> 2 )
        {
          v12 = (uint32_t *)sub_4569F0(*(uint32_t *)(a1[17] + 4 * v9));
          v13 = v12;
          if ( v12 != nullptr )
          {
            sub_69A110(v64 + 13, v62 - 1, v12[1], -1);
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 37);
            v14 = v13[2];
            if ( v14 != 0 )
            {
              v15 = dword_9B8890[(v14 - 1) % 6];
            }
            else if ( v13[9] < 0x10u )
            {
              v15 = (int)(v13 + 4);
            }
            else
            {
              v15 = v13[4];
            }
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
              dword_79C0B0,
              v64 + 34,
              v62,
              -4928551,
              v15);
            v16 = v13[15];
            v53 = v16 - sub_56A720(v13);
            v51 = *(uint32_t *)dword_79C0B0;
            v17 = sub_56A720(v13);
            (*(void (/*cdecl*/ **)(int, int, int, void *, const char *, int))(v51 + 80))(
              dword_79C0B0,
              v64 + 134,
              v62,
              v53 <= 0 ? (void *)-13220865 : (char *)&loc_4F92CB - 13220865,
              "%d/%d",
              v17);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
            if ( v59 == v54 || v13[1] == dword_795D40 )
            {
              sub_491530(2, 0);
              v18 = sub_418DD0(46);
              if ( v18 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v18 + 152))(v18, v64 + 8, v60, dword_79C0B0);
              sub_491630(2);
            }
            v9 = v57;
          }
          v5 = v64;
        }
        v60 += 24;
        ++v9;
        v19 = ++v59 < 7;
        v57 = v9;
        v62 += 24;
      }
      while ( v19 );
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 37);
      (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v5 + 29,
        v56 + 207,
        -3750202,
        "%d/%d",
        a1[20] + 1,
        a1[21] + 1);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v20 = a1[12];
      LOBYTE(v4) = *(uint8_t *)(v20 + 17);
      if ( (uint8_t)v4 != 0 )
      {
        v21 = *(uint32_t *)(v20 + 12);
        if ( dword_79BE3C == v21 || dword_79BE34 == v21 || (LOBYTE(v4) = dword_79BE38, dword_79BE38 == v21) )
        {
          v22 = (uint32_t *)a1[12];
          v49 = 1127;
LABEL_75:
          v44 = v22[6];
          v45 = v22[7];
          v66 = v22[5];
          v46 = sub_422E70(v49);
          LOBYTE(v4) = sub_4649B0(v66 + (v45 >> 1), v44, -1, -16777216, 2, v46, 0, 0, 1600, 0);
        }
      }
    }
  }
  return v4;
}


// ------------------------------------------------------------
// 0x630F80 sub_630F80 —— 组队成员条目绘制（43C410/69A5F0/69A840 + 423B30，121 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_630F80(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint8_t *v10; // eax
  uint8_t *v11; // eax
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  uint32_t *v14; // eax
  uint32_t *v15; // eax
  int v16; // ecx
  int v17; // edx

  *(this + 10) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(this + 10), 23, 24, 25, 23, 0, 0);
  else
    v3 = nullptr;
  *(this + 11) = v3;
  sub_69A5F0(v3, 230, 11);
  sub_69A840((uint32_t *)*(this + 2), *(this + 11));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 10), 110, 111, 112, 110, 0, 0);
  else
    v5 = nullptr;
  *(this + 12) = v5;
  sub_69A5F0(v5, 91, 226);
  sub_69A840((uint32_t *)*(this + 2), *(this + 12));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(this + 10), 76, 77, 78, 76, 0, 0);
  else
    v7 = nullptr;
  *(this + 13) = v7;
  sub_69A5F0(v7, 100, 206);
  sub_69A840((uint32_t *)*(this + 2), *(this + 13));
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
    v9 = sub_43C410(v8, *(this + 10), 79, 80, 81, 79, 0, 0);
  else
    v9 = nullptr;
  *(this + 14) = v9;
  sub_69A5F0(v9, 146, 206);
  sub_69A840((uint32_t *)*(this + 2), *(this + 14));
  v10 = operator new(0x2Cu);
  if ( v10 != nullptr )
    v11 = sub_423B30(v10, dword_79C0B0, *(this + 10), 51, 3);
  else
    v11 = nullptr;
  *(this + 15) = v11;
  v11[24] = 1;
  v12 = operator new(0x84u);
  if ( v12 != nullptr )
    v13 = sub_43C410(v12, *(this + 10), 113, 114, 115, 125, 0, 0);
  else
    v13 = nullptr;
  *(this + 22) = v13;
  sub_69A5F0(v13, 49, 161);
  sub_69A840((uint32_t *)*(this + 2), *(this + 22));
  v14 = operator new(0x84u);
  if ( v14 != nullptr )
    v15 = sub_43C410(v14, *(this + 10), 119, 120, 121, 119, 0, 0);
  else
    v15 = nullptr;
  *(this + 23) = v15;
  sub_69A5F0(v15, 133, 161);
  sub_69A840((uint32_t *)*(this + 2), *(this + 23));
  *((uint8_t *)this + 96) = 0;
  *((uint8_t *)this + 97) = 0;
  *((uint8_t *)this + 98) = 0;
  *((uint8_t *)this + 99) = 0;
  *(this + 27) = 0;
  *(this + 28) = 6;
  *(this + 30) = 0;
  *(this + 32) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 36) = 0;
  *(this + 29) = 12;
  *(this + 31) = 1600;
  *(this + 36) = dword_99FCCC;
  *((uint8_t *)this + 98) = 1;
  *(this + 25) = -16777216;
  *(this + 44) = 1600;
  *((uint8_t *)this + 148) = 0;
  *((uint8_t *)this + 149) = 0;
  *((uint8_t *)this + 150) = 0;
  *((uint8_t *)this + 151) = 0;
  *(this + 40) = 0;
  *(this + 41) = 6;
  *(this + 42) = 12;
  *(this + 43) = 0;
  *(this + 45) = 0;
  *(this + 46) = 0;
  *(this + 47) = 0;
  *(this + 48) = 0;
  *(this + 49) = 0;
  v16 = dword_99FCCC;
  v17 = *this;
  *(this + 38) = -16777216;
  *(this + 49) = v16;
  *(this + 44) = 200;
  *(this + 40) = 1;
  *(this + 45) = 1;
  *((uint8_t *)this + 150) = 1;
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(v17 + 28))(this, 2);
}


// ------------------------------------------------------------
// 0x6312F0 sub_6312F0 —— 组队列表重建（251 行：4A2CF0 + 56A720/56A680 成员 + 52DAA0/468240/430C80 候选）
// ------------------------------------------------------------
void /*thiscall*/ sub_6312F0(uint32_t *this)
{
  uint32_t *v1; // esi
  int v2; // eax
  unsigned int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // esi
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // esi
  int v13; // edi
  char *v14; // ebx
  int v15; // eax
  int v16; // eax
  uint32_t *v17; // ecx
  uint32_t *v18; // esi
  signed int i; // eax
  int v20; // ecx
  int v21; // edi
  void *v22; // eax
  uint32_t *v23; // esi
  uint32_t **v24; // eax
  uint32_t *v25; // edi
  int v26; // ecx
  unsigned int v27; // edx
  uint32_t *v28; // eax
  uint32_t *j; // edi
  int v30; // ecx
  unsigned int v31; // edx
  uint32_t *v32; // eax
  int v33; // ecx
  int v34; // eax
  int v35; // eax
  int v36; // esi
  int v37; // eax
  uint32_t *v38; // ecx
  bool v39; // cc
  uint32_t *v40; // edi
  uint32_t *v41; // eax
  bool v42; // zf
  uint32_t *v43; // esi
  uint32_t *v44; // edi
  uint32_t *v45; // eax
  uint32_t *v46; // esi
  char v47[4]; // [esp+8h] [ebp-40h] BYREF
  void *v48; // [esp+Ch] [ebp-3Ch]
  int v49; // [esp+10h] [ebp-38h]
  char v50[4]; // [esp+14h] [ebp-34h] BYREF
  void *Block; // [esp+18h] [ebp-30h]
  int v52; // [esp+1Ch] [ebp-2Ch]
  uint32_t v53[2]; // [esp+20h] [ebp-28h] BYREF
  int v54; // [esp+28h] [ebp-20h]
  uint32_t *v55; // [esp+2Ch] [ebp-1Ch]
  int v56; // [esp+30h] [ebp-18h]
  int v57; // [esp+34h] [ebp-14h]
  unsigned int v58; // [esp+38h] [ebp-10h]
  int v59; // [esp+44h] [ebp-4h]

  v1 = this;
  v2 = *(this + 9);
  v3 = 0;
  v55 = this;
  if ( v2 == 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0 )
  {
    v56 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);
    v4 = v56;
    if ( v56 != 0 )
    {
      v48 = (void *)sub_4A2CF0(v47);
      v49 = 0;
      v59 = 0;
      Block = (void *)sub_4A2CF0(v50);
      v52 = 0;
      LOBYTE(v59) = 1;
      v5 = sub_429830((uint16_t)word_77F804);
      v54 = sub_41A5E0(v5 + 53);
      v6 = *(uint32_t *)(v4 + 8);
      if ( v6 != 0 )
        v57 = (*(uint32_t *)(v4 + 12) - v6) >> 2;
      else
        v57 = 0;
      v58 = 0;
      if ( v57 > 0 )
      {
        do
        {
          v7 = *(uint32_t *)(v4 + 8);
          if ( v7 != 0 && v3 < (*(uint32_t *)(v4 + 12) - v7) >> 2 )
            v8 = *(uint32_t *)(v7 + 4 * v3);
          else
            v8 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 40))(v8, 18) != 0 )
          {
            v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 52))(v8);
            v10 = sub_429830(v9);
            if ( v10 != 0 )
            {
              v11 = *(uint32_t *)(v10 + 184);
              if ( v11 != 0 )
              {
                v12 = *(uint32_t *)(v10 + 184);
                v13 = *(uint32_t *)(v11 + 4);
                v14 = v47;
                if ( *(uint32_t *)(v12 + 60) - sub_56A720(v11) <= 0 )
                  v14 = v50;
                v15 = sub_56A680(*(uint32_t *)(v12 + 56));
                v16 = sub_41A5E0(v15 + 53);
                v17 = *((uint32_t **)v14 + 1);
                v18 = (uint32_t *)*v17;
                for ( i = abs32(v16 - v54); v18 != v17; v18 = (uint32_t *)*v18 )
                {
                  if ( v18[2] > i )
                    break;
                  if ( v18[3] == v13 )
                    goto LABEL_22;
                }
                v20 = v18[1];
                v53[0] = i;
                v53[1] = v13;
                v21 = sub_52DAA0(v18, v20, v53);
                sub_468240(1);
                v18[1] = v21;
                **(uint32_t **)(v21 + 4) = v21;
LABEL_22:
                v4 = v56;
                v3 = v58;
              }
            }
          }
          v58 = ++v3;
        }
        while ( (int)v3 < v57 );
        v1 = v55;
      }
      v22 = (void *)v1[17];
      v23 = v1 + 16;
      if ( v22 != nullptr )
        j__free(v22);
      v24 = (uint32_t **)v48;
      v23[1] = 0;
      v23[2] = 0;
      v23[3] = 0;
      v25 = *v24;
      if ( *v24 != v24 )
      {
        do
        {
          v26 = v23[1];
          if ( v26 != 0 )
            v27 = (v23[2] - v26) >> 2;
          else
            v27 = 0;
          if ( v26 != 0 && v27 < (v23[3] - v26) >> 2 )
          {
            v28 = (uint32_t *)v23[2];
            *v28 = v25[3];
            v23[2] = v28 + 1;
          }
          else
          {
            sub_430C80((void *)v23[2], 1, (int)(v25 + 3));
          }
          v25 = (uint32_t *)*v25;
        }
        while ( v25 != v48 );
      }
      for ( j = *(uint32_t **)Block; j != Block; j = (uint32_t *)*j )
      {
        v30 = v23[1];
        if ( v30 != 0 )
          v31 = (v23[2] - v30) >> 2;
        else
          v31 = 0;
        if ( v30 != 0 && v31 < (v23[3] - v30) >> 2 )
        {
          v32 = (uint32_t *)v23[2];
          *v32 = j[3];
          v23[2] = v32 + 1;
        }
        else
        {
          sub_430C80((void *)v23[2], 1, (int)(j + 3));
        }
      }
      v33 = v23[1];
      if ( v33 != 0 )
        v34 = (v23[2] - v33) >> 2;
      else
        v34 = 0;
      if ( (v34 - 1) / 7 <= 0 )
      {
        v37 = 0;
      }
      else
      {
        v35 = v23[1];
        if ( v35 != 0 )
          v36 = (v23[2] - v35) >> 2;
        else
          v36 = 0;
        v37 = (v36 - 1) / 7;
      }
      v38 = v55;
      v39 = v55[20] <= v37;
      v55[21] = v37;
      if ( !v39 )
        v38[20] = v37;
      v40 = Block;
      v41 = *(uint32_t **)Block;
      v42 = *(uint32_t *)Block == (uint32_t)Block;
      *(uint32_t *)Block = Block;
      v40[1] = v40;
      if ( !v42 )
      {
        do
        {
          v43 = (uint32_t *)*v41;
          j__free(v41);
          v41 = v43;
        }
        while ( v43 != v40 );
      }
      j__free(v40);
      v44 = v48;
      v45 = *(uint32_t **)v48;
      v42 = *(uint32_t *)v48 == (uint32_t)v48;
      *(uint32_t *)v48 = v48;
      v44[1] = v44;
      if ( !v42 )
      {
        do
        {
          v46 = (uint32_t *)*v45;
          j__free(v45);
          v45 = v46;
        }
        while ( v46 != v44 );
      }
      j__free(v44);
    }
  }
}


// ------------------------------------------------------------
// 0x631630 sub_631630 —— 组队列表刷新入口（630750 绘制 + 6312F0 重建）
// ------------------------------------------------------------
char /*thiscall*/ sub_631630(uint32_t *this, int a2)
{
  int v3; // eax

  v3 = *(this + 9);
  if ( v3 != a2 )
  {
    *(this + 9) = a2;
    if ( a2 != 0 )
    {
      if ( a2 == 1 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 14);
        sub_630750(this);
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 19);
      sub_6312F0(this);
    }
    *(uint8_t *)(*(this + 12) + 16) = a2 == 0;
    *(uint8_t *)(*(this + 13) + 16) = a2 == 0;
    *(uint8_t *)(*(this + 14) + 16) = a2 == 0;
    *(uint8_t *)(*(this + 22) + 16) = a2 == 1;
    *(uint8_t *)(*(this + 23) + 16) = a2 == 1;
    LOBYTE(v3) = a2 == 1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x6316A0 CNRDPartyListWindow__vmt8 —— CNRDPartyListWindow__vmt8 Update（137 行：CLICK_BUTTON2 + 423B10/526BF0 加入 + 6312F0 重建）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_6316A0(void *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // edx
  unsigned int v6; // ecx
  unsigned int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // eax
  int v16; // edi
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  uint8_t *result; // eax

  sub_69A650(*((uint32_t *)this + 2));
  v2 = *((uint32_t *)this + 9);
  if ( v2 != 0 )
  {
    if ( v2 == 1 )
    {
      v13 = *((uint32_t *)this + 2);
      if ( *(uint8_t *)(v13 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v13 + 12) )
      {
        v14 = *(uint32_t *)(v13 + 20);
        if ( pt.x >= v14 + 8 && pt.x < v14 + 250 )
        {
          v15 = *(uint32_t *)(v13 + 24);
          if ( pt.y >= v15 + 35 && pt.y < v15 + 59 )
          {
            v16 = sub_429830((uint16_t)word_77F804);
            if ( sub_423B10(dword_8F850C) == v16 )
            {
              sub_44E8D0(*((char **)this + 4), (void *)7, 0, 0);
              sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
            }
          }
        }
        v17 = sub_6306A0(this);
        if ( v17 != -1 )
        {
          v18 = sub_429830((uint16_t)word_77F804);
          v19 = sub_636190(*(uint32_t *)(v18 + 184), v17);
          if ( v19 != 0 )
          {
            v20 = sub_42B340(v19);
            sub_526BF0(v20, 1);
            sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
          }
        }
      }
      v21 = *((uint32_t *)this + 22);
      if ( *(uint8_t *)(v21 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v21 + 12) )
      {
        sub_44E8D0(*((char **)this + 4), (void *)7, 0, 0);
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
      v22 = *((uint32_t *)this + 23);
      if ( *(uint8_t *)(v22 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v22 + 12) )
      {
        sub_423200(dword_8F7B08, 13);
        sub_423380(dword_8F7B08);
        goto LABEL_39;
      }
    }
  }
  else
  {
    v3 = *((uint32_t *)this + 2);
    if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
    {
      v4 = sub_6306A0(this);
      if ( v4 != -1 )
      {
        v5 = *((uint32_t *)this + 17);
        v6 = v5 != 0 ? (*((uint32_t *)this + 18) - v5) >> 2 : 0;
        v7 = 7 * *((uint32_t *)this + 20) + v4;
        if ( v7 < v6 )
        {
          sub_44E8D0(*((char **)this + 4), (void *)6, 0, *(uint32_t *)(*((uint32_t *)this + 17) + 4 * v7));
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        }
      }
    }
    v8 = *((uint32_t *)this + 12);
    if ( *(uint8_t *)(v8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v8 + 12) )
    {
      sub_44E8D0(*((char **)this + 4), (void *)7, 0, 0);
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
    v9 = *((uint32_t *)this + 13);
    if ( *(uint8_t *)(v9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v9 + 12) )
    {
      v10 = *((uint32_t *)this + 20);
      if ( v10 > 0 )
      {
        *((uint32_t *)this + 20) = v10 - 1;
        sub_6312F0(this);
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
    }
    v11 = *((uint32_t *)this + 14);
    if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )
    {
      v12 = *((uint32_t *)this + 20);
      if ( v12 < *((uint32_t *)this + 21) )
      {
        *((uint32_t *)this + 20) = v12 + 1;
        sub_6312F0(this);
LABEL_39:
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
    }
  }
  result = *((uint8_t **)this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x631980 CNRDPartyListWindow__vmtC —— CNRDPartyListWindow__vmtC 打开槽（429830 + 69A5F0 + 630750/6312F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyListWindow__vmtC(int this, int a2, int a3)
{
  int v5; // ecx
  int v6; // eax
  int v7; // edx
  int v8; // edx

  if ( sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) == 0 )
    return 0;
  dword_9B9458 = this;
  sub_69A5F0(*(uint32_t **)(this + 8), 192, 55);
  v5 = *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184);
  v6 = *(uint32_t *)(this + 36);
  if ( v5 != 0 )
  {
    if ( v6 == 1 )
      sub_630750((uint32_t *)this);
    if ( *(uint32_t *)(this + 36) != 1 )
    {
      v7 = *(uint32_t *)this;
      *(uint32_t *)(this + 36) = 1;
      (*(void (/*thiscall*/ **)(int, int, int))(v7 + 24))(this, 20, 14);
      sub_630750((uint32_t *)this);
      *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 56) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 88) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 92) + 16) = 1;
      return 1;
    }
  }
  else
  {
    if ( v6 == 0 )
      sub_6312F0((uint32_t *)this);
    if ( *(uint32_t *)(this + 36) != 0 )
    {
      v8 = *(uint32_t *)this;
      *(uint32_t *)(this + 36) = 0;
      (*(void (/*thiscall*/ **)(int, int, int))(v8 + 24))(this, 20, 19);
      sub_6312F0((uint32_t *)this);
      *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 56) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 88) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 92) + 16) = 0;
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x631A90 sub_631A90 —— PVP 频道数据（19 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_631A90(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x631AC0 sub_631AC0 —— PVP 频道列表构建（26 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_631AC0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  uint32_t *v4; // esi
  int i; // edi

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 10) = 0;
  v4 = this + 11;
  for ( i = 5; i != 0; --i )
  {
    if ( *v4 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v4)(*v4, 1);
    *v4++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x631B10 sub_631B10 —— PVP 频道条目（23 行）
// ------------------------------------------------------------
int /*stdcall*/ sub_631B10(int a1, int a2)
{
  int v2; // ecx
  int v3; // eax

  v2 = a2;
  if ( a2 < 1 )
    v2 = 1;
  v3 = 100 * a1 / v2;
  if ( v3 <= 25 )
    return 243;
  if ( v3 <= 50 )
    return 242;
  if ( v3 > 75 )
    return v3 > 100 ? 274 : 240;
  return 241;
}



// ------------------------------------------------------------
// 0x631B70 sub_631B70 —— PVP 频道辅助（11 行）
// ------------------------------------------------------------
bool sub_631B70()
{
  return dword_8F7C04 != 0
      && *(int *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) >= 10;
}



// ------------------------------------------------------------
// 0x631B90 sub_631B90 —— PVP 频道页绘制（69C980/69A5F0，95 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_631B90(uint32_t *this)
{
  int v2; // ecx
  int result; // eax
  int v4; // esi
  int v5; // eax
  int v6; // ebx
  uint32_t **v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // [esp+8h] [ebp-10h]
  int v11; // [esp+Ch] [ebp-Ch]
  unsigned int v12; // [esp+10h] [ebp-8h]
  uint32_t *v13; // [esp+14h] [ebp-4h]

  v2 = 140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 740;
  result = *(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 744);
  v4 = 0;
  v13 = this;
  v11 = v2;
  if ( result != 0 )
  {
    result = (*(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 748)
            - result)
           / 104;
    if ( result != 0 )
    {
      v5 = *(this + 2);
      v6 = *(uint32_t *)(v5 + 24) + 37;
      v10 = *(uint32_t *)(v5 + 20) + 14;
      v12 = 0;
      v7 = (uint32_t **)(this + 11);
      do
      {
        v8 = *(uint32_t *)(v2 + 4);
        if ( v8 != 0 && v12 < (*(uint32_t *)(v11 + 8) - v8) / 104 )
        {
          sub_69C980(
            v13[9],
            dword_73DE70[4 * *(char *)(v4 + v8 + 100)],
            dword_73DE74[4 * *(char *)(v4 + v8 + 100)],
            dword_73DE78[4 * *(char *)(v4 + v8 + 100)],
            dword_73DE78[4 * *(char *)(v4 + v8 + 100)],
            0,
            0);
          sub_69A5F0(*v7, v10, v6);
          v6 += 52;
          *((uint8_t *)*v7 + 16) = 1;
        }
        else
        {
          *((uint8_t *)*v7 + 16) = 0;
        }
        v2 = v11;
        v4 += 104;
        ++v7;
        ++v12;
      }
      while ( v4 < 520 );
      v9 = *(uint32_t *)(v11 + 4);
      if ( v9 != 0 )
        v9 = (*(uint32_t *)(v11 + 8) - v9) / 104;
      switch ( v9 )
      {
        case 0:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*v13 + 24))(v13, 20, 7);
          return (*(int (/*thiscall*/ **)(uint32_t *, int))(*v13 + 28))(v13, 2);
        case 1:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*v13 + 24))(v13, 20, 7);
          goto LABEL_18;
        case 2:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*v13 + 24))(v13, 20, 10);
          return (*(int (/*thiscall*/ **)(uint32_t *, int))(*v13 + 28))(v13, 2);
        case 3:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*v13 + 24))(v13, 20, 14);
          goto LABEL_18;
        case 4:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*v13 + 24))(v13, 20, 18);
          return (*(int (/*thiscall*/ **)(uint32_t *, int))(*v13 + 28))(v13, 2);
        default:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*v13 + 24))(v13, 20, 22);
LABEL_18:
          result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v13 + 28))(v13, 2);
          break;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x631D70 sub_631D70 —— PVP 频道辅助（429830）
// ------------------------------------------------------------
bool /*stdcall*/ sub_631D70(int a1)
{
  int v1; // eax
  int v2; // ecx
  int v3; // edi
  int v4; // eax

  v1 = *(uint32_t *)(dword_8F7A24 + 36);
  v2 = 140 * *(uint32_t *)(v1 + 12);
  v3 = v2 + v1 + 740;
  v4 = *(uint32_t *)(v2 + v1 + 744);
  if ( v4 == 0 || (*(uint32_t *)(v3 + 8) - v4) / 104 == 0 )
    return false;
  return sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0
      && *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 116) >= *(char *)(104 * a1 + *(uint32_t *)(v3 + 4) + 98)
      && *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 116) <= *(char *)(*(uint32_t *)(v3 + 4) + 104 * a1 + 99);
}



// ------------------------------------------------------------
// 0x631E40 sub_631E40 —— PVP 频道页绘制 2（43C410/69A5F0/69A840 + 426BD0/69C780，74 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_631E40(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // ebx
  uint8_t *v5; // edi
  bool v6; // zf
  void *Block; // [esp+10h] [ebp-18h]
  int v9; // [esp+14h] [ebp-14h]
  int v10; // [esp+18h] [ebp-10h]

  *(uint32_t *)(this + 36) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(this + 36), 23, 24, 25, 23, 0, 0);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 40) = v3;
  sub_69A5F0(v3, 230, 11);
  sub_69A840(*(uint32_t *)(this + 40));
  v10 = 37;
  v4 = (uint32_t *)(this + 44);
  v9 = 5;
  do
  {
    v5 = operator new(0x84u);
    if ( v5 != nullptr )
    {
      Block = *(void **)(this + 36);
      sub_426BD0(v5);
      *(uint32_t *)v5 = &vftbl_nengine__CNButton;
      sub_69C780(v5);
      nengine__CNButton__vmt20(Block, 223, 223, 223, 223, 0, 0);
    }
    else
    {
      v5 = nullptr;
    }
    *v4 = v5;
    sub_69A5F0(v5, 14, v10);
    *(uint32_t *)(*v4 + 68) = this;
    sub_69A840(*v4++);
    v6 = v9 == 1;
    v10 += 52;
    --v9;
  }
  while ( !v6 );
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
  *(uint32_t *)(this + 112) = dword_99FCCC;
  *(uint32_t *)(this + 68) = -16777216;
  *(uint32_t *)(this + 92) = 200;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 96) = 1;
  return 0;
}



// ============================================================
// 【分区 3】PVP 频道列表 CNRDPVPChannelListWindow（0x631FF0-0x632630）
// vmt0 构造（171 行）、vmt8 Update（46E350/471CC0 频道进入）。
// ============================================================
// ------------------------------------------------------------
// 0x631FF0 CNRDPVPChannelListWindow__vmt0 —— CNRDPVPChannelListWindow__vmt0 构造（171 行：554930 + 631B10/631D70/631B70 + 42A210）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_631FF0(int this, int a2)
{
  int v4; // edi
  int v5; // eax
  int v6; // edi
  unsigned int result; // eax
  char *v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  char v13; // al
  const CHAR *v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  int v18; // ebx
  int v19; // eax
  int v20; // eax
  int v21; // ecx
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int v25; // esi
  int v26; // edi
  int v27; // esi
  int v28; // ebx
  int v29; // eax
  const CHAR *v30; // [esp-4h] [ebp-1Ch]
  char *v31; // [esp+Ch] [ebp-Ch]
  int v32; // [esp+10h] [ebp-8h]
  int v33; // [esp+14h] [ebp-4h]
  int v34; // [esp+14h] [ebp-4h]
  int v35; // [esp+14h] [ebp-4h]
  int v36; // [esp+20h] [ebp+8h]
  int v37; // [esp+20h] [ebp+8h]
  int v38; // [esp+20h] [ebp+8h]
  int v39; // [esp+20h] [ebp+8h]
  int v40; // [esp+20h] [ebp+8h]
  int v41; // [esp+20h] [ebp+8h]

  sub_554930(a2);
  if ( a2 == *(uint32_t *)(this + 8) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v36 = *(uint32_t *)(a2 + 24);
    v5 = sub_418DD0(20);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, v4 + 6, v36 + 6, dword_79C0B0);
  }
  v6 = 0;
  result = this + 44;
  while ( *(uint32_t *)result == 0 || *(uint32_t *)result != a2 )
  {
    ++v6;
    result += 4;
    if ( v6 >= 5 )
      return result;
  }
  if ( *(uint8_t *)(this + 124) != 0 )
  {
    result = *(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 744);
    if ( result != 0 )
    {
      result = (int)(*(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12)
                               + *(uint32_t *)(dword_8F7A24 + 36)
                               + 748)
                   - result)
             / 104;
      if ( v6 < result )
      {
        v8 = (char *)(*(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12)
                                + *(uint32_t *)(dword_8F7A24 + 36)
                                + 744)
                    + 104 * v6);
        v31 = v8;
        if ( (uint8_t)sub_43BCB0(*(uint32_t *)(this + 4 * v6 + 44)) != 0 )
        {
          sub_491530(2, 0);
          v9 = *(uint32_t *)(this + 4 * v6 + 44);
          v37 = *(uint32_t *)(v9 + 24);
          v33 = *(uint32_t *)(v9 + 20);
          v10 = sub_418DD0(235);
          if ( v10 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, v33, v37, dword_79C0B0);
          sub_491630(2);
        }
        v11 = *(uint32_t *)(this + 4 * v6 + 44);
        v38 = *(uint32_t *)(v11 + 24);
        v34 = *(uint32_t *)(v11 + 20);
        v12 = sub_418DD0(dword_73DE7C[4 * v8[100]]);
        if ( v12 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, v34 + 50, v38 + 15, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 64);
        v13 = v8[99];
        if ( v13 == -1 )
          v14 = szPassword;
        else
          v14 = (const CHAR *)sub_42A210(v13);
        v15 = *(uint32_t *)(this + 4 * v6 + 44);
        v30 = v14;
        v39 = *(uint32_t *)(v15 + 24);
        v35 = *(uint32_t *)(v15 + 20);
        v32 = *(uint32_t *)dword_79C0B0;
        v16 = sub_42A210(v8[98]);
        (*(void (**)(int, int, int, int, const char *, ...))(v32 + 80))(
          dword_79C0B0,
          v35 + 122,
          v39 + 21,
          -1,
          "(%s ~ %s)",
          v16,
          v30);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v17 = *(uint32_t *)(this + 4 * v6 + 44);
        v18 = *(uint32_t *)(v17 + 24);
        v40 = *(uint32_t *)(v17 + 20);
        v19 = sub_631B10(*((uint32_t *)v31 + 15), *((uint32_t *)v31 + 14));
        v20 = sub_418DD0(v19);
        if ( v20 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v20 + 152))(v20, v40 + 193, v18 + 15, dword_79C0B0);
        if ( (uint8_t)sub_631D70(v6) != 1
          || dword_8F7C04 == 0
          || *(int *)(result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3)) < 10 )
        {
          result = *(uint32_t *)(this + 4 * v6 + 44);
          if ( pt.x >= *(uint32_t *)(result + 20)
            && pt.x <= *(uint32_t *)(result + 20) + *(uint32_t *)(*(uint32_t *)(result + 116) + 20)
            && pt.y >= *(uint32_t *)(result + 24)
            && pt.y <= *(uint32_t *)(result + 24) + *(uint32_t *)(*(uint32_t *)(result + 116) + 24) )
          {
            v21 = *(uint32_t *)(result + 116);
            v22 = *(uint32_t *)(result + 20) + (*(uint32_t *)(v21 + 20) >> 1);
            v41 = (*(uint32_t *)(v21 + 24) >> 1) + *(uint32_t *)(result + 24) + 10;
            if ( (uint8_t)sub_631B70(this) != 0 )
            {
              result = sub_631D70(v6);
              if ( (uint8_t)result == 0 )
              {
                v24 = sub_422E70(1247);
                return sub_4649B0(v22, v41, -1, -16777216, 2, v24, 0, 0, 1600, 0);
              }
            }
            else
            {
              v23 = sub_422E70(1248);
              return sub_4649B0(v22, v41, -1, -16777216, 2, v23, 0, 0, 1600, 0);
            }
          }
        }
      }
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 64);
    v25 = *(uint32_t *)(this + 4 * v6 + 44);
    v26 = *(uint32_t *)(v25 + 24);
    v27 = *(uint32_t *)(v25 + 20);
    v28 = *(uint32_t *)dword_79C0B0;
    v29 = sub_422E70(1242);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v28 + 80))(dword_79C0B0, v27 + 67, v26 + 16, -1, v29);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x6323B0 sub_6323B0 —— PVP 频道点击（46EAA0 进入 + 41D520 + CLICK_BUTTON2）
// ------------------------------------------------------------
unsigned int /*stdcall*/ sub_6323B0(unsigned int a1)
{
  unsigned int result; // eax
  int v2; // esi

  result = 140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 740;
  v2 = *(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 744);
  if ( v2 != 0 )
  {
    result = (*(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 748)
            - v2)
           / 104;
    if ( result > a1 )
    {
      if ( 104 * a1 + 64 + strlen((const char *)(v2 + 104 * a1 + 64)) + 1 != 104 * a1 + 65
        && sub_631D70(a1)
        && dword_8F7C04 != 0
        && *(int *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) >= 10 )
      {
        sub_46EAA0(*(uint32_t **)(dword_8F7A24 + 36), *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12), 4, a1);
        sub_41D520(dword_8F7A24);
      }
      return (unsigned int)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x632470 sub_632470 —— PVP 频道刷新（631D70 + 631B10，54 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_632470(int *this, char a2)
{
  int v2; // eax
  int v3; // ebx
  int v4; // esi
  int *v5; // edi
  int v7; // [esp+8h] [ebp-8h]

  v2 = *(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 744);
  v7 = 140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 740;
  if ( v2 != 0 )
  {
    v2 = (*(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 748) - v2)
       / 104;
    if ( v2 != 0 )
    {
      v3 = 0;
      v4 = 0;
      v5 = this + 11;
      do
      {
        v2 = *v5;
        if ( *v5 != 0 )
        {
          *(uint8_t *)(v2 + 17) = a2;
          if ( a2 == 1 )
          {
            LOBYTE(v2) = sub_631D70(v3);
            if ( (uint8_t)v2 == 0
              || dword_8F7C04 == 0
              || *(int *)(v2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3)) < 10
              || (v2 = sub_631B10(
                         *(uint32_t *)(v4 + *(uint32_t *)(v7 + 4) + 60),
                         *(uint32_t *)(v4 + *(uint32_t *)(v7 + 4) + 56))) == 274 )
            {
              *(uint8_t *)(*v5 + 17) = 0;
            }
          }
        }
        v4 += 104;
        ++v3;
        ++v5;
      }
      while ( v4 < 520 );
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x632540 CNRDPVPChannelListWindow__vmt8 —— CNRDPVPChannelListWindow__vmt8 Update（48 行：CLICK_BUTTON2 + 46E350/632470/6323B0/471CC0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPVPChannelListWindow__vmt8(int this)
{
  int v2; // eax
  signed int v3; // edi
  int *v4; // ebx
  int v5; // eax

  sub_69A650(*(uint32_t *)(this + 8));
  v2 = *(uint32_t *)(this + 40);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  if ( *(uint8_t *)(this + 124) != 0 )
    goto LABEL_8;
  if ( sub_46E350() )
  {
    sub_632470((int *)this, 1);
    *(uint8_t *)(this + 124) = 1;
  }
  if ( *(uint8_t *)(this + 124) != 0 )
  {
LABEL_8:
    v3 = 0;
    v4 = (int *)(this + 44);
    do
    {
      v5 = *v4;
      if ( *v4 != 0 && *(uint8_t *)(v5 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v5 + 12) )
        LOBYTE(v5) = sub_6323B0(v3);
      ++v3;
      ++v4;
    }
    while ( v3 < 5 );
  }
  else
  {
    LOBYTE(v5) = sub_471CC0(*(uint32_t *)(dword_8F7A24 + 36));
  }
  return v5;
}



// ------------------------------------------------------------
// 0x6325F0 CNRDPVPChannelListWindow__vmtC —— CNRDPVPChannelListWindow__vmtC 打开槽（69A5F0 + 631B90/632470 + 46F3E0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPVPChannelListWindow__vmtC(int this, int a2, int a3)
{
  sub_69A5F0(*(uint32_t **)(this + 8), 192, 55);
  sub_631B90((uint32_t *)this);
  dword_9B945C = this;
  *(uint8_t *)(this + 124) = 0;
  sub_632470((int *)this, 0);
  sub_46F3E0(*(uint32_t *)(dword_8F7A24 + 36));
  return 1;
}



// ============================================================
// 【分区 4】推荐组队用户 CNRDPartyRecommendUserWindow（0x632630-0x632FE0）
// vmtC 打开（287 行 641120 系：52DAA0/468240/430C80 候选列表）；
// vmt8 Update（CLICK_BUTTON2 + 526BF0 邀请）。
// ============================================================
// ------------------------------------------------------------
// 0x632630 sub_632630 —— 推荐用户数据（37 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_632630(uint32_t *this)
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
  v3 = this + 11;
  for ( i = 2; i != 0; --i )
  {
    if ( *v3 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v3)(*v3, 1);
    *v3++ = 0;
  }
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  result = 0;
  *(this + 13) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  *(this + 14) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6326A0 CNRDPartyRecommendUserWindow__vmt10 —— CNRDPartyRecommendUserWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDPartyRecommendUserWindow__vmt10()
{
  dword_9B9460 = 0;
}



// ------------------------------------------------------------
// 0x6326B0 sub_6326B0 —— 推荐用户选中处理（27 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6326B0(uint32_t *this)
{
  int v1; // eax
  LONG v2; // ecx
  LONG v3; // edx
  int result; // eax
  LONG i; // esi

  v1 = *(this + 2);
  v2 = *(uint32_t *)(v1 + 24) + 35;
  v3 = *(uint32_t *)(v1 + 20) + 8;
  result = 0;
  for ( i = v2 + 18; pt.x < v3 || pt.x >= v3 + 229 || pt.y < v2 || pt.y >= i; i += 18 )
  {
    ++result;
    v2 += 18;
    if ( result >= 5 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x632710 CNRDPartyRecommendUserWindow__vmt8 —— CNRDPartyRecommendUserWindow__vmt8 Update（54 行：CLICK_BUTTON2 + 69C690 + 526BF0 邀请）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDPartyRecommendUserWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ebx
  int v5; // eax
  unsigned int v6; // edi
  int v7; // eax
  int v8; // eax
  uint32_t *v9; // esi
  int i; // edi
  uint32_t *result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 10);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v3 = *(this + 2);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    v4 = sub_6326B0(this);
    if ( v4 != -1 )
    {
      v5 = *(this + 42);
      v6 = v5 != 0 ? (*(this + 43) - v5) >> 2 : 0;
      if ( v4 + sub_69C690(*(this + 14)) < v6 )
      {
        v7 = sub_69C690(*(this + 14));
        v8 = sub_429830((uint32_t *)dword_8F8500, *(uint16_t *)(*(this + 42) + 4 * (v4 + v7)));
        if ( v8 != 0 )
          sub_526BF0(*(uint32_t *)(*(this + 4) + 48), *(int **)(v8 + 192), 1);
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
    }
  }
  v9 = this + 11;
  for ( i = 2; i != 0; --i )
  {
    result = (uint32_t *)*v9;
    if ( *(uint8_t *)(*v9 + 17) != 0 && dword_79BE34 == result[3] )
      result = sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    ++v9;
  }
  return result;
}



// ------------------------------------------------------------
// 0x632830 CNRDPartyRecommendUserWindow__vmt0 —— CNRDPartyRecommendUserWindow__vmt0 构造（132 行：554930 + 69C690/6326B0/42B340）
// ------------------------------------------------------------
char /*thiscall*/ sub_632830(uint32_t *this, int a2)
{
  unsigned int v3; // eax
  int v4; // esi
  int v5; // ebx
  int v6; // eax
  int v7; // ebx
  int v8; // ecx
  unsigned int v9; // esi
  int v10; // ebx
  int v11; // ecx
  uint32_t *v12; // eax
  uint32_t *v13; // esi
  int v14; // eax
  int v15; // eax
  uint32_t *v16; // ecx
  int v17; // eax
  int v18; // eax
  bool v19; // cc
  int v21; // [esp+8h] [ebp-14h]
  int v22; // [esp+8h] [ebp-14h]
  int v23; // [esp+Ch] [ebp-10h]
  int v24; // [esp+10h] [ebp-Ch]
  unsigned int v25; // [esp+14h] [ebp-8h]
  int v26; // [esp+18h] [ebp-4h]
  int v27; // [esp+24h] [ebp+8h]

  LOBYTE(v3) = sub_554930(a2);
  if ( a2 == *(this + 2) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    v6 = sub_418DD0(19);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4 + 6, v5 + 6, dword_79C0B0);
    v7 = v5 + 35;
    v27 = v4 + 8;
    v24 = v7;
    v3 = sub_69C690(*(this + 14));
    v8 = *(this + 2);
    v9 = v3;
    LOBYTE(v3) = *(uint8_t *)(v8 + 17);
    v25 = v9;
    if ( (uint8_t)v3 != 0
      && (dword_79BE3C == *(uint32_t *)(v8 + 12)
       || dword_79BE34 == *(uint32_t *)(v8 + 12)
       || (LOBYTE(v3) = dword_79BE38, dword_79BE38 == *(uint32_t *)(v8 + 12))) )
    {
      v3 = sub_6326B0(this);
      v23 = v3;
      v26 = 0;
      v10 = v7 + 4;
    }
    else
    {
      v23 = -1;
      v26 = 0;
      v10 = v7 + 4;
    }
    while ( 1 )
    {
      v11 = *(this + 42);
      if ( v11 == 0 )
        break;
      v3 = (*(this + 43) - v11) >> 2;
      if ( v9 >= v3 )
        break;
      v12 = (uint32_t *)sub_429830(*(uint16_t *)(v11 + 4 * v9));
      v13 = v12;
      if ( v12 != nullptr )
      {
        v21 = sub_42B340(v12);
        v14 = sub_418DD0(94);
        if ( v14 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 152))(v14, v27 + 1, v10 - 3, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)v21 + 384))(
          v21,
          v27 + 1,
          v10 - 3,
          16,
          16,
          1065353216);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 15);
        v15 = sub_41A5E0((unsigned int)v13 + 53);
        (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v27 + 27,
          v10,
          -4928551,
          "Lv.%d",
          v15);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, this + 28);
        if ( v13[10] < 0x10u )
          v16 = v13 + 5;
        else
          v16 = (uint32_t *)v13[5];
        (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v27 + 23,
          v10,
          -4928551,
          v16);
        v22 = *(uint32_t *)dword_79C0B0;
        v17 = sub_4B0EC0(v13[11], v13[12]);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v22 + 80))(dword_79C0B0, v27 + 104, v10, -8005942, v17);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        if ( v26 == v23 )
        {
          sub_491530(2, 0);
          v18 = sub_418DD0(22);
          if ( v18 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v18 + 152))(v18, v27, v24, dword_79C0B0);
          sub_491630(2);
        }
      }
      LOBYTE(v3) = v26 + 1;
      v10 += 18;
      v19 = ++v26 < 5;
      ++v25;
      v24 += 18;
      if ( !v19 )
        break;
      v9 = v25;
    }
  }
  return v3;
}


// ------------------------------------------------------------
// 0x632AA0 sub_632AA0 —— 推荐用户页绘制（117 行：43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630）
// ------------------------------------------------------------
int /*thiscall*/ sub_632AA0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint8_t *v4; // edi
  uint8_t *v5; // eax
  uint32_t *v6; // edi
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // ecx
  int v10; // edx
  void *Block; // [esp+10h] [ebp-18h]
  void *Blocka; // [esp+10h] [ebp-18h]
  uint32_t *v14; // [esp+14h] [ebp-14h]
  int v15; // [esp+18h] [ebp-10h]

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(this + 9), 23, 24, 25, 23, 0, 0);
  else
    v3 = nullptr;
  *(this + 10) = v3;
  sub_69A5F0(v3, 230, 11);
  sub_69A840(*(this + 10));
  v15 = 4;
  v14 = this + 11;
  do
  {
    v4 = operator new(0x84u);
    if ( v4 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v4);
      *(uint32_t *)v4 = &nengine::CNButton::`vftable';
      sub_69C780(v4);
      sub_69C7B0(Block, v15, v15, v15 + 1, v15, 0, 0);
    }
    else
    {
      v4 = nullptr;
    }
    *v14++ = v4;
    v15 += 2;
  }
  while ( v15 < 8 );
  v5 = operator new(0x88u);
  v6 = v5;
  if ( v5 != nullptr )
  {
    Blocka = (void *)*(this + 9);
    sub_426BD0(v5);
    *v6 = &nengine::CNSlider::`vftable';
    sub_69CA20(v6);
    sub_69CA50(Blocka, 87, 86);
    *v6 = &nengine::CNVSlider::`vftable';
    v7 = v6;
  }
  else
  {
    v7 = nullptr;
  }
  *(this + 13) = v7;
  if ( operator new(0x74u) != nullptr )
    v8 = (uint32_t *)sub_43C630(*(this + 11), *(this + 12), *(this + 13));
  else
    v8 = nullptr;
  *(this + 14) = v8;
  sub_69A5F0(v8, 239, 35);
  sub_69A840(*(this + 14));
  *((uint8_t *)this + 60) = 0;
  *((uint8_t *)this + 61) = 0;
  *((uint8_t *)this + 62) = 0;
  *((uint8_t *)this + 63) = 0;
  *(this + 18) = 0;
  *(this + 21) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 20) = 12;
  *(this + 22) = 1600;
  *(this + 19) = 6;
  *(this + 27) = dword_99FCCC;
  *((uint8_t *)this + 62) = 1;
  *(this + 16) = -16777216;
  *(this + 35) = 1600;
  *((uint8_t *)this + 112) = 0;
  *((uint8_t *)this + 113) = 0;
  *((uint8_t *)this + 114) = 0;
  *((uint8_t *)this + 115) = 0;
  *(this + 31) = 0;
  *(this + 32) = 6;
  *(this + 33) = 12;
  *(this + 34) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  *(this + 39) = 0;
  *(this + 40) = 0;
  v9 = dword_99FCCC;
  v10 = *this;
  *(this + 29) = -16777216;
  *(this + 40) = v9;
  *(this + 35) = 144;
  *(this + 31) = 1;
  *(this + 36) = 1;
  *((uint8_t *)this + 114) = 1;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v10 + 24))(this, 20, 9);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 2);
}


// ------------------------------------------------------------
// 0x632D40 sub_632D40 —— 推荐用户列表重建（178 行：4A2CF0 + 52DAA0/468240/430C80）
// ------------------------------------------------------------
void /*thiscall*/ sub_632D40(uint32_t *this)
{
  void *v1; // eax
  uint32_t *v2; // ebx
  int v3; // esi
  int v4; // edi
  int v5; // ecx
  int v6; // eax
  uint32_t **v7; // eax
  unsigned int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // eax
  uint32_t *i; // esi
  int v15; // ecx
  int v16; // edx
  int v17; // edi
  uint32_t *v18; // esi
  int v19; // ecx
  unsigned int v20; // edx
  uint32_t *v21; // eax
  int v22; // ecx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // ebx
  uint32_t *v27; // esi
  uint32_t *v28; // eax
  bool v29; // zf
  uint32_t *v30; // edi
  uint8_t v31[4]; // [esp+8h] [ebp-38h] BYREF
  void *Block; // [esp+Ch] [ebp-34h]
  int v33; // [esp+10h] [ebp-30h]
  uint32_t v34[2]; // [esp+14h] [ebp-2Ch] BYREF
  uint32_t *v35; // [esp+1Ch] [ebp-24h]
  int v36; // [esp+20h] [ebp-20h]
  int v37; // [esp+24h] [ebp-1Ch]
  int v38; // [esp+28h] [ebp-18h]
  int v39; // [esp+2Ch] [ebp-14h]
  unsigned int v40; // [esp+30h] [ebp-10h]
  int v41; // [esp+3Ch] [ebp-4h]

  v1 = (void *)*(this + 42);
  v2 = this + 41;
  v3 = 0;
  v35 = this;
  if ( v1 != nullptr )
    j__free(v1);
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 0;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0 )
  {
    v38 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);
    v4 = v38;
    if ( v38 != 0 )
    {
      v5 = *(uint32_t *)(v38 + 8);
      v39 = v5 != 0 ? (*(uint32_t *)(v38 + 12) - v5) >> 2 : 0;
      v6 = sub_429830((uint16_t)word_77F804);
      v36 = v6;
      if ( v6 != 0 )
      {
        v37 = sub_41A5E0(v6 + 53);
        v7 = (uint32_t **)sub_4A2CF0(v31);
        Block = v7;
        v33 = 0;
        v8 = 0;
        v41 = 0;
        v40 = 0;
        if ( v39 > 0 )
        {
          while ( 1 )
          {
            v9 = *(uint32_t *)(v4 + 8);
            if ( v9 != 0 && v8 < (*(uint32_t *)(v4 + 12) - v9) >> 2 )
              v3 = *(uint32_t *)(v9 + 4 * v8);
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 40))(v3, 18) != 0 )
            {
              v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 52))(v3);
              v11 = sub_429830(v10);
              v12 = sub_41A5E0(v11 + 53);
              v13 = abs32(v37 - v12);
              if ( v11 != v36 && *(uint32_t *)(v11 + 184) == 0 && v13 <= 5 )
              {
                for ( i = *(uint32_t **)Block; i != Block; i = (uint32_t *)*i )
                {
                  if ( i[2] >= v13 )
                    break;
                }
                v15 = i[1];
                v16 = *(uint16_t *)(v11 + 4);
                v34[0] = v13;
                v34[1] = v16;
                v17 = sub_52DAA0(i, v15, v34);
                sub_468240(1);
                i[1] = v17;
                **(uint32_t **)(v17 + 4) = v17;
              }
              v4 = v38;
            }
            if ( (int)++v40 >= v39 )
              break;
            v8 = v40;
            v3 = 0;
          }
          v7 = (uint32_t **)Block;
        }
        v18 = *v7;
        if ( *v7 != v7 )
        {
          do
          {
            v19 = v2[1];
            if ( v19 != 0 )
              v20 = (v2[2] - v19) >> 2;
            else
              v20 = 0;
            if ( v19 != 0 && v20 < (v2[3] - v19) >> 2 )
            {
              v21 = (uint32_t *)v2[2];
              *v21 = v18[3];
              v2[2] = v21 + 1;
            }
            else
            {
              sub_430C80((void *)v2[2], 1, (int)(v18 + 3));
            }
            v18 = (uint32_t *)*v18;
          }
          while ( v18 != Block );
        }
        v22 = v2[1];
        if ( v22 != 0 )
          v23 = (v2[2] - v22) >> 2;
        else
          v23 = 0;
        if ( v23 - 5 >= 0 )
        {
          v25 = v2[1];
          if ( v25 != 0 )
            v26 = (v2[2] - v25) >> 2;
          else
            v26 = 0;
          v24 = v26 - 5;
        }
        else
        {
          v24 = 0;
        }
        (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)v35[14] + 32))(v35[14], v24);
        v27 = Block;
        v28 = *(uint32_t **)Block;
        v29 = *(uint32_t *)Block == (uint32_t)Block;
        *(uint32_t *)Block = Block;
        v27[1] = v27;
        if ( !v29 )
        {
          do
          {
            v30 = (uint32_t *)*v28;
            j__free(v28);
            v28 = v30;
          }
          while ( v30 != v27 );
        }
        j__free(v27);
      }
    }
  }
}


// ------------------------------------------------------------
// 0x632FB0 CNRDPartyRecommendUserWindow__vmtC —— CNRDPartyRecommendUserWindow__vmtC 打开槽（登记 dword_9B9460 + 69A5F0 + 69C680 + 632D40）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyRecommendUserWindow__vmtC(int this, int a2, int a3)
{
  dword_9B9460 = this;
  sub_69A5F0(*(uint32_t **)(this + 8), 192, 55);
  sub_69C680(0);
  sub_632D40((uint32_t *)this);
  return 1;
}



// ============================================================
// 【分区 5】确认弹窗动作槽家族（0x632FE0-0x633580）
// YesNo 确认窗 vmt8/vmt14（悬停+确认取消）；CNRDCashShopBuyConfirm/
// NoDoubleEvent/ImportantItemUse/TradeLast/StaminaRecover 等的
// vmt38=确认动作、vmt3C=取消动作、vmt40=文案装配（645CC0 商城下单）。
// ============================================================
// ------------------------------------------------------------
// 0x632FE0 CNRDYesNoConfirmWindow__vmt8 —— CNRDYesNoConfirmWindow__vmt8 Update：双按钮悬停（+17 标志 && dword_79BE34==X）→vt+56 确认/vt+60 取消 + vt+32 关闭 + CLICK_BUTTON2
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDYesNoConfirmWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 9);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 56))(this);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = (uint8_t *)*(this + 10);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 60))(this);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x633060 CNRDYesNoConfirmWindow__vmt14 —— CNRDYesNoConfirmWindow__vmt14 关闭槽：vt+56 + vt+32
// ------------------------------------------------------------
char /*thiscall*/ CNRDYesNoConfirmWindow__vmt14(void *this)
{
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 56))(this);
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x633080 CNRDCashShopBuyConfirmWindow__vmt38 —— CNRDCashShopBuyConfirmWindow__vmt38 确认动作：645CC0 商城下单 + 清 +2052 标志
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopBuyConfirmWindow__vmt38(uint32_t *this)
{
  int result; // eax

  sub_645CC0(*(this + 20));
  result = *(this + 20);
  *(uint8_t *)(result + 2052) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6330A0 CNRDCashShopBuyConfirmWindow__vmt3C —— CNRDCashShopBuyConfirmWindow__vmt3C 取消动作：清 +2052 标志
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopBuyConfirmWindow__vmt3C(uint32_t *this)
{
  int result; // eax

  result = *(this + 20);
  *(uint8_t *)(result + 2052) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6330B0 CNRDCashShopNoDoubleEventConfirmWindow__vmt38 —— CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认动作：+84 标志时 44E8D0 下单 + vt+32 关闭
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopNoDoubleEventConfirmWindow__vmt38(uint32_t *this)
{
  if ( *((uint8_t *)this + 84) != 0 )
    sub_44E8D0((char *)dword_8F8528, (void *)0x2F, *(this + 20), 0);
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
}



// ------------------------------------------------------------
// 0x6330E0 CNRDCashShopNoDoubleEventConfirmWindow__vmt3C —— CNRDCashShopNoDoubleEventConfirmWindow__vmt3C 取消动作：645CA0
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopNoDoubleEventConfirmWindow__vmt3C(uint32_t *this)
{
  return sub_645CA0(*(this + 20));
}



// ------------------------------------------------------------
// 0x6330F0 CNRDImportantItemUseConfirmWindow__vmt38 —— CNRDImportantItemUseConfirmWindow__vmt38 确认动作：484E80 + 602C00 重要道具使用
// ------------------------------------------------------------
int /*thiscall*/ CNRDImportantItemUseConfirmWindow__vmt38(int this)
{
  int result; // eax
  int v3; // ecx
  int v4; // edi

  result = *(uint32_t *)(this + 88);
  if ( result < *((uint32_t *)dword_8F852C + 2) )
  {
    v3 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * result);
    if ( v3 != 0 && *(uint32_t *)(this + 80) == v3 )
    {
      v4 = *(uint32_t *)(this + 84);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 16))(v3);
      if ( v4 == *(uint32_t *)(result + 4) )
      {
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 32))(*(uint32_t *)(this + 80));
        result = sub_484E80(v4);
        if ( result == *(uint32_t *)(this + 88) )
          return sub_602C00(*(uint32_t **)(this + 80), *(uint32_t *)(this + 88));
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x633150 CNRDTradeLastConfirmWindow__vmt38 —— CNRDTradeLastConfirmWindow__vmt38 确认动作（423200 系参数 + 422E70/44E8D0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDTradeLastConfirmWindow__vmt38(void *this)
{
  char *v1; // eax
  void *v3; // [esp+0h] [ebp-4h] BYREF

  v3 = this;
  sub_423200(dword_8F7B08, 26);
  LOBYTE(v3) = 3;
  sub_423290(dword_8F7B08, (int)&v3, 1);
  sub_423380(dword_8F7B08);
  v1 = sub_422E70(2006);
  return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v1, 0);
}



// ------------------------------------------------------------
// 0x6331B0 CNRDTradeLastConfirmWindow__vmt3C —— CNRDTradeLastConfirmWindow__vmt3C 取消动作（423200 系参数）
// ------------------------------------------------------------
int /*thiscall*/ CNRDTradeLastConfirmWindow__vmt3C(void *this)
{
  void *v2; // [esp+0h] [ebp-4h] BYREF

  v2 = this;
  sub_423200(dword_8F7B08, 26);
  LOBYTE(v2) = 4;
  sub_423290(dword_8F7B08, (int)&v2, 1);
  return sub_423380(dword_8F7B08);
}



// ------------------------------------------------------------
// 0x6331F0 CNRDYesNoConfirmWindow__vmtC —— CNRDYesNoConfirmWindow__vmtC 文案装配（69C340/69C440/69C360/69C500 文本链 + 406DF0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDYesNoConfirmWindow__vmtC(char *this, int a2, int a3)
{
  int v4; // edx
  char *v5; // eax
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // ecx
  int v9; // ebx
  int v10; // edi

  v4 = *(uint32_t *)this;
  *((uint32_t *)this + 19) = a3;
  *((uint32_t *)this + 18) = a2;
  (*(void (/*thiscall*/ **)(char *, int, int))(v4 + 64))(this, a2, a3);
  sub_69C340(-1);
  sub_69C440(-1);
  if ( *((uint32_t *)this + 17) < 0x10u )
    v5 = this + 48;
  else
    v5 = *((char **)this + 12);
  sub_69C360(v5, 0);
  v6 = *(uint32_t *)this;
  v7 = sub_69C500(*((uint32_t *)this + 3));
  (*(void (/*thiscall*/ **)(char *, int, int))(v6 + 24))(this, 14, v7 + 5);
  v8 = *((uint32_t **)this + 2);
  v9 = (480 - v8[8]) / 2;
  v10 = (640 - v8[7]) / 2;
  sub_69A5F0(v8, v10, v9);
  sub_69A5F0(*((uint32_t **)this + 9), v10 + 29, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v9 - 43);
  sub_69A5F0(*((uint32_t **)this + 10), v10 + 98, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v9 - 43);
  sub_406DF0(*(uint32_t *)(*((uint32_t *)this + 9) + 20) + (*(uint32_t *)(*((uint32_t *)this + 9) + 28) >> 1), pt.y);
  sub_406DF0(pt.x, *(uint32_t *)(*((uint32_t *)this + 9) + 24) + (*(uint32_t *)(*((uint32_t *)this + 9) + 32) >> 1));
  return 1;
}



// ------------------------------------------------------------
// 0x6332F0 sub_6332F0 —— 弹窗关闭清理（43C410 + 69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_6332F0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 21, 22, 23, 21, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  sub_69A840(v3);
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 24, 25, 26, 24, 0, 0);
  else
    v5 = nullptr;
  *(this + 10) = v5;
  return sub_69A840(v5);
}



// ------------------------------------------------------------
// 0x6333D0 CNRDCashShopBuyConfirmWindow__vmt40 —— CNRDCashShopBuyConfirmWindow__vmt40 文案槽（422E70 取串 + 4015C0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopBuyConfirmWindow__vmt40(uint32_t *this, int a2, int a3)
{
  char *v3; // eax

  *(this + 20) = a2;
  *(uint8_t *)(a2 + 2052) = 1;
  v3 = sub_422E70(881);
  return sub_4015C0(v3, strlen(v3));
}



// ------------------------------------------------------------
// 0x633410 CNRDCashShopNoDoubleEventConfirmWindow__vmt40 —— CNRDCashShopNoDoubleEventConfirmWindow__vmt40 文案槽（422E70/4015C0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopNoDoubleEventConfirmWindow__vmt40(int this, int a2, int a3)
{
  char *v4; // eax

  *(uint32_t *)(this + 80) = a2;
  v4 = sub_422E70(3011);
  sub_4015C0(v4, strlen(v4));
  *(uint8_t *)(this + 84) = a3 == 0;
  return a3;
}



// ------------------------------------------------------------
// 0x633460 CNRDImportantItemUseConfirmWindow__vmt40 —— CNRDImportantItemUseConfirmWindow__vmt40 文案槽（422E70/4015C0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDImportantItemUseConfirmWindow__vmt40(uint32_t *this, int *a2, int a3)
{
  int v4; // ecx
  int v5; // eax
  int v6; // edx
  char *v7; // eax
  int v9; // [esp-4h] [ebp-10Ch]
  char Buffer[256]; // [esp+4h] [ebp-104h] BYREF
  int v11; // [esp+104h] [ebp-4h]

  v4 = *a2;
  v11 = dword_796E50;
  v5 = a2[1];
  v6 = a2[2];
  *(this + 20) = v4;
  *(this + 21) = v5;
  *(this + 22) = v6;
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 108))(v4);
  v7 = sub_422E70(882);
  sprintf(Buffer, v7, v9);
  return sub_4015C0(Buffer, strlen(Buffer));
}



// ------------------------------------------------------------
// 0x6334E0 CNRDCashShopLevelLimitConfirmWindow__vmt40 —— CNRDCashShopLevelLimitConfirmWindow__vmt40 文案槽（422E70/4015C0）
// ------------------------------------------------------------
int /*stdcall*/ CNRDCashShopLevelLimitConfirmWindow__vmt40(int a1, int a2)
{
  char *v2; // eax
  char Buffer[512]; // [esp+4h] [ebp-204h] BYREF
  int v5; // [esp+204h] [ebp-4h]

  v5 = dword_796E50;
  v2 = sub_422E70(883);
  sprintf(Buffer, v2, a2);
  return sub_4015C0(Buffer, strlen(Buffer));
}



// ------------------------------------------------------------
// 0x633550 CNRDTradeLastConfirmWindow__vmt40 —— CNRDTradeLastConfirmWindow__vmt40 文案槽（422E70/4015C0）
// ------------------------------------------------------------
int /*stdcall*/ CNRDTradeLastConfirmWindow__vmt40(int a1, int a2)
{
  char *v2; // eax

  v2 = sub_422E70(2005);
  return sub_4015C0(v2, strlen(v2));
}



// ------------------------------------------------------------
// 0x633580 sub_633580 —— 14 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_633580(int this)
{
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint8_t *)(this + 48) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x633590 sub_633590 —— 弹窗数据清理（422E70 系——被 cashshop.cpp 各 vmt4 调用）
// ------------------------------------------------------------
int /*thiscall*/ sub_633590(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 9) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 10) = 0;
  return result;
}



// ============================================================
// 【分区 6】技能购买确认 CNRDSkillBuyConfirmWindow（0x6335C0-0x633770）
// vmtC 文案装配（47EB10 技能查询）、vmt14 关闭（GET_SKILL 学技事件）。
// ============================================================
// ------------------------------------------------------------
// 0x6335C0 CNRDSkillBuyConfirmWindow__vmtC —— CNRDSkillBuyConfirmWindow__vmtC 文案装配（69C340 系 + 47EB10 技能查询 + 550470/5013F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillBuyConfirmWindow__vmtC(uint32_t *this, int a2, int a3)
{
  int v5; // edi
  int v6; // eax
  char *v7; // eax
  int v8; // edi
  int v9; // eax
  uint32_t *v10; // ecx
  int v11; // ebx
  int v12; // edi
  int v13; // [esp-10h] [ebp-218h]
  char Buffer[512]; // [esp+4h] [ebp-204h] BYREF
  int v15; // [esp+204h] [ebp-4h]

  v15 = dword_796E50;
  *(this + 11) = a2;
  if ( a2 == 0 )
    return 0;
  *((uint8_t *)this + 48) = a3 != 0;
  sub_69C340(-1);
  sub_69C440(-1);
  v5 = sub_47EB10((uint32_t *)*(this + 11));
  if ( (uint8_t)sub_550470(*(uint32_t *)(*(this + 4) + 68)) != 0 )
  {
    v6 = *(this + 11);
    if ( *(uint8_t *)(v6 + 480) != 0 )
      v5 = sub_5013F0(v5, *(uint32_t *)(v6 + 488));
  }
  v13 = sub_41ACF0(*(this + 11) + 20);
  v7 = sub_422E70(1143);
  sprintf(Buffer, v7, v13, v5);
  sub_69C360(Buffer, 0);
  v8 = *this;
  v9 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v8 + 24))(this, 14, v9 + 5);
  v10 = (uint32_t *)*(this + 2);
  v11 = pt.x - 55 <= 0 ? 0 : pt.x - 55;
  if ( v11 >= 640 - v10[7] )
    v11 = 640 - v10[7];
  v12 = 480 - v10[8];
  if ( (pt.y - v10[8] + 31 <= 0 ? 0 : pt.y - v10[8] + 31) < v12 )
    v12 = pt.y - v10[8] + 31 <= 0 ? 0 : pt.y - v10[8] + 31;
  sub_69A5F0(v10, v11, v12);
  sub_69A5F0((uint32_t *)*(this + 9), v11 + 29, *(uint32_t *)(*(this + 2) + 32) + v12 - 43);
  sub_69A5F0((uint32_t *)*(this + 10), v11 + 98, *(uint32_t *)(*(this + 2) + 32) + v12 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x633730 CNRDSkillBuyConfirmWindow__vmt14 —— CNRDSkillBuyConfirmWindow__vmt14 关闭槽：GET_SKILL 学技事件（47F890/432EA0）+ 44ABE0
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillBuyConfirmWindow__vmt14(uint32_t **this)
{
  sub_47F890(*(this + 11));
  sub_432EA0("GET_SKILL", -1, 0, 0);
  if ( *((uint8_t *)this + 48) != 0 )
    sub_44ABE0(*(this + 4), 3);
  ((void (/*thiscall*/ *)(uint32_t **))(*this)[8])(this);
  return 1;
}



// ============================================================
// 【分区 7】物品删除确认 CNRDItemDeleteConfirmWindow（0x633770-0x633C00）
// vmtC 文案（69C340 系文本链）、vmt14 删除执行（484ED0/486070）。
// ============================================================
// ------------------------------------------------------------
// 0x633770 sub_633770 —— 删除确认清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_633770(uint32_t *this)
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
// 0x633850 CNRDItemDeleteConfirmWindow__vmtC —— CNRDItemDeleteConfirmWindow__vmtC 文案装配（422E70 + 69C340 系）
// ------------------------------------------------------------
char /*userpurge*/ CNRDItemDeleteConfirmWindow__vmtC@<al>(int *a1@<ecx>, int a2@<ebx>, int a3@<edi>, int a4, int a5)
{
  int v7; // edi
  char *v8; // eax
  char *v9; // eax
  char *v10; // eax
  int v11; // edi
  int v12; // eax
  uint32_t *v13; // ecx
  int v14; // ebx
  int v15; // [esp-4h] [ebp-8Ch]
  int v16; // [esp-4h] [ebp-8Ch]
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int v18; // [esp+84h] [ebp-4h]
  int v19; // [esp+90h] [ebp+8h]

  v18 = dword_796E50;
  a1[11] = a4;
  a1[12] = a5;
  if ( a4 == 0 )
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a4 + 20))(a4, 2) != 0 )
    a1[12] = 1;
  v7 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1[11] + 108))(a1[11], a3, a2);
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[11] + 16))(a1[11]) + 4) != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[11] + 20))(a1[11], 2) != 0 )
    {
      v9 = sub_422E70(956);
      sprintf(Buffer, v9, v7);
    }
    else
    {
      v16 = a1[12];
      v10 = sub_422E70(957);
      sprintf(Buffer, v10, v7, v16);
    }
  }
  else
  {
    v15 = a1[12];
    v8 = sub_422E70(955);
    sprintf(Buffer, v8, v15);
  }
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(Buffer, 0);
  v11 = *a1;
  v12 = sub_69C500(a1[3]);
  (*(void (/*thiscall*/ **)(int *, int, int))(v11 + 24))(a1, 14, v12 + 5);
  v13 = (uint32_t *)a1[2];
  v19 = pt.x - 125 <= 0 ? 0 : pt.x - 125;
  if ( v19 >= 640 - v13[7] )
    v19 = 640 - v13[7];
  v14 = pt.y - v13[8] + 31 <= 0 ? 0 : pt.y - v13[8] + 31;
  if ( v14 >= 480 - v13[8] )
    v14 = 480 - v13[8];
  sub_69A5F0(v13, v19, v14);
  sub_69A5F0((uint32_t *)a1[9], v19 + 29, *(uint32_t *)(a1[2] + 32) + v14 - 43);
  sub_69A5F0((uint32_t *)a1[10], v19 + 98, *(uint32_t *)(a1[2] + 32) + v14 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x633A00 CNRDItemDeleteConfirmWindow__vmt14 —— CNRDItemDeleteConfirmWindow__vmt14 删除执行（484ED0/422E70/44E8D0/432F00/486070）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemDeleteConfirmWindow__vmt14(void *this)
{
  int v2; // esi
  int v3; // ebx
  char *v4; // eax
  int v5; // ebx

  v2 = sub_484ED0(*((uint32_t *)this + 11));
  if ( v2 == -1 )
  {
    v2 = sub_484ED0(*((uint32_t *)this + 11));
    if ( v2 == -1 )
    {
      v2 = sub_484ED0(*((uint32_t *)this + 11));
      if ( v2 == -1 )
      {
        v5 = dword_8F7C04;
        v2 = 0;
        while ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 792))(v5, v2) != *((uint32_t *)this + 11) )
        {
          if ( ++v2 >= 18 )
            goto LABEL_14;
        }
        v3 = 3;
        if ( v2 != -1 )
          goto LABEL_3;
LABEL_14:
        v4 = sub_422E70(958);
        goto LABEL_15;
      }
      v3 = 2;
    }
    else
    {
      v3 = 1;
    }
  }
  else
  {
    v3 = 0;
  }
LABEL_3:
  if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 11) + 44))(*((uint32_t *)this + 11)) < *((uint32_t *)this + 12) )
  {
    v4 = sub_422E70(959);
LABEL_15:
    sub_44E8D0(*((char **)this + 4), (void *)0x1B, (int)v4, 0);
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
    return 1;
  }
  if ( v3 == 3 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F7C04 + 1092))(dword_8F7C04, v2, 1);
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
    return 1;
  }
  else
  {
    if ( sub_432F00(v3) != nullptr )
      sub_486070(v2, *((uint32_t *)this + 12), 1);
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
    return 1;
  }
}



// ------------------------------------------------------------
// 0x633B20 sub_633B20 —— 删除确认清理 2（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_633B20(uint32_t *this)
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
// 【分区 8】物品购买确认 CNRDItemBuyConfirmWindow（0x633C00-0x633C70）
// ============================================================
// ------------------------------------------------------------
// 0x633C00 CNRDItemBuyConfirmWindow__vmt8 —— CNRDItemBuyConfirmWindow__vmt8 Update：悬停 + CLICK_BUTTON2
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemBuyConfirmWindow__vmt8(int *this)
{
  int v2; // eax
  int result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 9);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 20))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = *(this + 10);
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  }
  return result;
}



// ============================================================
// 【分区 9】解封确认 CNRDItemSealRemoveConfirmWindow（0x633C70-0x633F20）
// vmt14 执行解封（484ED0/486820）。
// ============================================================
// ------------------------------------------------------------
// 0x633C70 CNRDItemSealRemoveConfirmWindow__vmtC —— CNRDItemSealRemoveConfirmWindow__vmtC 文案装配（422E70 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemSealRemoveConfirmWindow__vmtC(int *this, int a2, int a3)
{
  int v4; // eax
  char *v6; // eax
  int v7; // edi
  int v8; // eax
  uint32_t *v9; // ecx
  int v10; // ebx
  int v11; // edi
  int v12; // [esp-Ch] [ebp-114h]
  char Buffer[256]; // [esp+4h] [ebp-104h] BYREF
  int v14; // [esp+104h] [ebp-4h]

  v14 = dword_796E50;
  v4 = __RTDynamicCast(a2, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
  *(this + 11) = v4;
  if ( v4 == 0 )
    return 0;
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 108))(v4);
  v6 = sub_422E70(1108);
  sprintf(Buffer, v6, v12);
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(Buffer, 0);
  v7 = *this;
  v8 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(int *, int, int))(v7 + 24))(this, 14, v8 + 5);
  v9 = (uint32_t *)*(this + 2);
  v10 = pt.x - 55 <= 0 ? 0 : pt.x - 55;
  if ( v10 >= 640 - v9[7] )
    v10 = 640 - v9[7];
  v11 = 480 - v9[8];
  if ( (pt.y - v9[8] + 31 <= 0 ? 0 : pt.y - v9[8] + 31) < v11 )
    v11 = pt.y - v9[8] + 31 <= 0 ? 0 : pt.y - v9[8] + 31;
  sub_69A5F0(v9, v10, v11);
  sub_69A5F0((uint32_t *)*(this + 9), v10 + 29, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);
  sub_69A5F0((uint32_t *)*(this + 10), v10 + 98, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x633DB0 CNRDItemSealRemoveConfirmWindow__vmt14 —— CNRDItemSealRemoveConfirmWindow__vmt14 解封执行（484ED0/486820）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemSealRemoveConfirmWindow__vmt14(void *this)
{
  int v2; // edi
  char *v3; // eax
  char v4; // bl
  uint32_t *v5; // eax

  v2 = sub_484ED0(*((uint32_t *)this + 11));
  if ( v2 == -1 )
  {
    v3 = sub_422E70(1109);
    sub_44E8D0(*((char **)this + 4), (void *)0x1B, (int)v3, 0);
  }
  v4 = *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 11) + 16))(*((uint32_t *)this + 11)) + 32);
  *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 11) + 16))(*((uint32_t *)this + 11)) + 32) = 0;
  v5 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 11) + 172))(*((uint32_t *)this + 11));
  sub_486820(v2, *v5, 1);
  *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 11) + 16))(*((uint32_t *)this + 11)) + 32) = v4;
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x633E30 sub_633E30 —— 解封确认清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_633E30(uint32_t *this)
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
// 【分区 10】通用弹窗（0x633F20-0x634150）
// CNRDPopupMessageWindow/CNRDPopupTextBoxOnly：vmtC 文案装配、
// vmt8/vmt10 输入与关闭。
// ============================================================
// ------------------------------------------------------------
// 0x633F20 CNRDPopupMessageWindow__vmtC —— CNRDPopupMessageWindow__vmtC 文案装配（541AE0 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPopupMessageWindow__vmtC(int *this, int a2, int a3)
{
  int v5; // edi
  int v6; // eax
  uint32_t *v7; // ecx
  int v8; // ebx
  int v9; // edi

  if ( a2 == 0 )
    return 0;
  *(this + 10) = a3;
  if ( a3 != 0 && *((uint32_t *)dword_8F8528 + 626) == 17 )
    sub_541AE0();
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(a2, 0);
  v5 = *this;
  v6 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(int *, int, int))(v5 + 24))(this, 14, v6 + 5);
  v7 = (uint32_t *)*(this + 2);
  v8 = (480 - v7[8]) / 2;
  v9 = (640 - v7[7]) / 2;
  sub_69A5F0(v7, v9, v8);
  sub_69A5F0(
    (uint32_t *)*(this + 9),
    v9 + ((unsigned int)(*(uint32_t *)(*(this + 2) + 28) - *(uint32_t *)(*(this + 9) + 28)) >> 1),
    *(uint32_t *)(*(this + 2) + 32) + v8 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x633FE0 CNRDPopupMessageWindow__vmt10 —— CNRDPopupMessageWindow__vmt10 输入槽（41C860/41D520）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPopupMessageWindow__vmt10(uint32_t *this)
{
  int result; // eax

  if ( *(this + 10) == 1 )
    return sub_41C860(dword_8F7A24);
  result = *(this + 10) - 2;
  if ( *(this + 10) == 2 )
    return sub_41D520(dword_8F7A24);
  return result;
}



// ------------------------------------------------------------
// 0x634000 sub_634000 —— 弹窗清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_634000(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  return sub_69A840(v3);
}



// ------------------------------------------------------------
// 0x634090 sub_634090 —— 弹窗数据（10 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_634090(void *this)
{
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 44))(this, 144, 2048);
}



// ------------------------------------------------------------
// 0x6340A0 CNRDPopupTextBoxOnly__vmt8 —— CNRDPopupTextBoxOnly__vmt8 Update（69A650 显示）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPopupTextBoxOnly__vmt8(uint32_t *this)
{
  return sub_69A650(*(this + 2));
}



// ------------------------------------------------------------
// 0x6340B0 CNRDPopupTextBoxOnly__vmtC —— CNRDPopupTextBoxOnly__vmtC 文案装配（69C340 系 + 69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPopupTextBoxOnly__vmtC(int *this, int a2, int a3)
{
  int v5; // edi
  int v6; // eax

  if ( a2 == 0 )
    return 0;
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(a2, 0);
  v5 = *this;
  v6 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(int *, int, int))(v5 + 24))(this, 14, v6 + 2);
  sub_69A5F0(
    (uint32_t *)*(this + 2),
    (640 - *(uint32_t *)(*(this + 2) + 28)) / 2,
    (480 - *(uint32_t *)(*(this + 2) + 32)) / 2);
  return 1;
}



// ------------------------------------------------------------
// 0x634130 sub_634130 —— 弹窗数据 2（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_634130(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0xFFFF;
  *(this + 12) = 0;
  *(this + 13) = 0;
  return 0;
}



// ============================================================
// 【分区 11】邀请响应窗 CNRDResponsePeerWindow（0x634150-0x6347E0）
// vmtC 打开（209 行，POP_UP 事件：好友/组队邀请）；vmt38=接受动作
// （456690/42EAF0 组队加入）；vmt8 Update（CLICK_BUTTON2）。
// ============================================================
// ------------------------------------------------------------
// 0x634150 CNRDResponsePeerWindow__vmt38 —— CNRDResponsePeerWindow__vmt38 接受动作：429830 + 456690/484FA0/42EAF0 组队/好友接受
// ------------------------------------------------------------
int /*thiscall*/ CNRDResponsePeerWindow__vmt38(uint16_t *this)
{
  char *v2; // eax
  int v4; // eax
  int v5; // edi
  int v6; // ebx
  int v7; // [esp+4h] [ebp-8h] BYREF
  char v8[4]; // [esp+8h] [ebp-4h] BYREF

  if ( sub_429830((uint32_t *)dword_8F8500, *(this + 22)) == 0 )
  {
    v2 = sub_422E70(1142);
    sub_44E8D0(*((char **)this + 4), (void *)0x1B, (int)v2, 0);
    return (*(int (/*thiscall*/ **)(uint16_t *))(*(uint32_t *)this + 32))(this);
  }
  v4 = *((uint32_t *)this + 12);
  if ( v4 != 1 || *((uint32_t *)dword_8F8528 + 26) != 2 )
  {
    if ( v4 == 0 )
    {
      sub_456690(*((uint32_t *)this + 11));
      return (*(int (/*thiscall*/ **)(uint16_t *))(*(uint32_t *)this + 32))(this);
    }
    v5 = 0;
    if ( v4 == 1 )
    {
      v6 = *((uint32_t *)dword_8F852C + 1);
      v5 = sub_484FA0() - v6;
    }
    if ( *((uint32_t *)this + 12) != 3 || sub_42EAF0(*(uint32_t **)(dword_8F7A24 + 40), *((uint32_t *)this + 14)) != 0 )
    {
      sub_423200(dword_8F7B08, 11);
      v7 = *(this + 22);
      sub_423290(dword_8F7B08, (int)&v7, 2);
      v8[0] = *((uint8_t *)this + 48);
      sub_423290(dword_8F7B08, (int)v8, 1);
      v7 = v5;
      sub_423290(dword_8F7B08, (int)&v7, 4);
      sub_423380(dword_8F7B08);
    }
  }
  return (*(int (/*thiscall*/ **)(uint16_t *))(*(uint32_t *)this + 32))(this);
}



// ------------------------------------------------------------
// 0x634270 CNRDResponsePeerWindow__vmt8 —— CNRDResponsePeerWindow__vmt8 Update（CLICK_BUTTON2 + 699000 输入）
// ------------------------------------------------------------
int /*thiscall*/ CNRDResponsePeerWindow__vmt8(int *this)
{
  int v2; // edi
  int v3; // eax
  int result; // eax

  sub_69A650(*(this + 2));
  if ( sub_429830((uint32_t *)dword_8F8500, *((uint16_t *)this + 22)) == 0 )
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  v2 = *(this + 21);
  if ( sub_699000((int)(this + 15)) >= v2 )
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  v3 = *(this + 9);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 56))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = *(this + 10);
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x634310 CNRDResponsePeerWindow__vmt0 —— CNRDResponsePeerWindow__vmt0 构造（24 行）
// ------------------------------------------------------------
int /*thiscall*/ CNRDResponsePeerWindow__vmt0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // ecx

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 2) && *(this + 12) == 2 )
  {
    v4 = *(this + 13);
    if ( v4 != 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v4 + 152))(
               v4,
               *(uint32_t *)(a2 + 20) + 18,
               *(uint32_t *)(a2 + 24) + 16,
               dword_79C0B0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x634360 sub_634360 —— 响应窗清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_634360(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 21, 22, 23, 21, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  sub_69A840(v3);
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 24, 25, 26, 24, 0, 0);
  else
    v5 = nullptr;
  *(this + 10) = v5;
  return sub_69A840(v5);
}



// ------------------------------------------------------------
// 0x634440 CNRDResponsePeerWindow__vmtC —— CNRDResponsePeerWindow__vmtC 打开槽（209 行：POP_UP 事件 + 48B740/49EFE0/42A410/4332F0 邀请数据 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ sub_634440(uint32_t *this, int a2, int *a3)
{
  uint32_t *v3; // ebx
  int *v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  unsigned int v10; // eax
  uint32_t *v11; // edi
  int v12; // eax
  const char *v13; // eax
  uint32_t *v14; // edi
  int v15; // eax
  uint32_t *v16; // ebx
  const char *v17; // eax
  int *v18; // eax
  int v19; // edx
  bool v20; // zf
  int v21; // eax
  uint32_t *v22; // ecx
  uint32_t *v23; // edi
  int v24; // eax
  int v25; // eax
  uint32_t *v26; // ecx
  const char *v27; // eax
  int v28; // edx
  uint32_t *v29; // ebx
  const char *v30; // eax
  int v31; // edi
  int v32; // eax
  uint32_t *v33; // ecx
  int v34; // ebx
  int v35; // edi
  int v36; // [esp-10h] [ebp-A0h]
  uint32_t *v37; // [esp-Ch] [ebp-9Ch]
  uint32_t *v38; // [esp-Ch] [ebp-9Ch]
  int v39; // [esp-8h] [ebp-98h]
  int v40; // [esp-8h] [ebp-98h]
  int v41; // [esp-8h] [ebp-98h]
  int v42; // [esp+8h] [ebp-88h] BYREF
  char Buffer[128]; // [esp+Ch] [ebp-84h] BYREF
  int v44; // [esp+8Ch] [ebp-4h]

  v3 = (uint32_t *)a2;
  v44 = dword_796E50;
  if ( a2 == 0 )
    return 0;
  *(this + 11) = *(uint16_t *)(a2 + 4);
  v6 = a3;
  v7 = *(this + 11);
  *(this + 12) = a3;
  *(this + 14) = -1;
  if ( v7 == (uint16_t)word_77F804 || *(uint32_t *)(dword_8F7A24 + 12) != 1 )
    return 0;
  if ( v6 != nullptr )
  {
    if ( v6 == (int *)2 )
    {
      if ( sub_48B740(4) == 1 )
        return 0;
    }
    else if ( v6 == (int *)3 && sub_48B740(5) == 1 )
    {
      return 0;
    }
  }
  else if ( sub_48B740(3) == 1 )
  {
    return 0;
  }
  v8 = *(this + 12);
  if ( v8 == 0 )
  {
    v9 = *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184);
    v10 = v3[10];
    if ( v9 != 0 )
    {
      if ( v10 < 0x10 )
        v11 = v3 + 5;
      else
        v11 = (uint32_t *)v3[5];
      v12 = sub_41A5E0((unsigned int)v3 + 53);
      v39 = v3[45];
      v37 = v11;
      v36 = v12;
      v13 = (const char *)sub_422E70(1138);
    }
    else
    {
      if ( v10 < 0x10 )
        v14 = v3 + 5;
      else
        v14 = (uint32_t *)v3[5];
      v15 = sub_41A5E0((unsigned int)v3 + 53);
      v39 = v3[45];
      v37 = v14;
      v36 = v15;
      v13 = (const char *)sub_422E70(1139);
    }
    sprintf(Buffer, v13, v36, v37, v39);
    goto LABEL_53;
  }
  if ( v8 != 1 )
  {
    if ( v8 != 2 )
    {
      if ( v8 == 3 )
      {
        v28 = *(this + 11);
        v42 = 0;
        a2 = -1;
        if ( (uint8_t)sub_49EFE0(v28, &v42, &a2, this + 14) == 0 )
          return 0;
        sub_432EA0("POP_UP", -1, 0, 0);
        if ( v3[10] < 0x10u )
          v29 = v3 + 5;
        else
          v29 = (uint32_t *)v3[5];
        v41 = sub_48FE30(v42);
        v30 = (const char *)sub_422E70(2032);
        sprintf(Buffer, v30, v29, v41);
      }
      goto LABEL_53;
    }
    v18 = *(int **)(dword_8F8504 + 8);
    v19 = *v18;
    v20 = *v18 == (uint32_t)v18;
    a3 = v18;
    a2 = v19;
    if ( !v20 )
    {
      while ( 2 )
      {
        v21 = 0;
        v22 = (uint32_t *)(v19 + 56);
        while ( *v22 != *(this + 11) )
        {
          ++v21;
          ++v22;
          if ( v21 >= 8 )
            goto LABEL_36;
        }
        v23 = (uint32_t *)(v19 + 16);
        if ( v19 != -16 )
        {
          sub_432EA0("POP_UP", -1, 0, 0);
          v24 = v23[19];
          if ( v24 != 0 )
          {
            v25 = dword_99FEC4[v24];
          }
          else if ( v23[26] < 0x10u )
          {
            v25 = (int)(v23 + 21);
          }
          else
          {
            v25 = v23[21];
          }
          if ( v3[10] < 0x10u )
            v26 = v3 + 5;
          else
            v26 = (uint32_t *)v3[5];
          v40 = v25;
          v38 = v26;
          v27 = (const char *)sub_422E70(1141);
          sprintf(Buffer, v27, v38, v40);
          *(this + 13) = sub_42A410(v3);
          goto LABEL_53;
        }
LABEL_36:
        sub_4332F0(&a2);
        v19 = a2;
        if ( (int *)a2 != a3 )
          continue;
        break;
      }
    }
    return 0;
  }
  if ( v3[10] < 0x10u )
    v16 = v3 + 5;
  else
    v16 = (uint32_t *)v3[5];
  v17 = (const char *)sub_422E70(1140);
  sprintf(Buffer, v17, v16);
LABEL_53:
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(Buffer, 0);
  v31 = *this;
  v32 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v31 + 24))(this, 14, v32 + 5);
  v33 = (uint32_t *)*(this + 2);
  v34 = 415 - v33[8];
  v35 = 631 - v33[7];
  sub_69A5F0(v33, v35, v34);
  sub_69A5F0((uint32_t *)*(this + 9), v35 + 29, *(uint32_t *)(*(this + 2) + 32) + v34 - 43);
  sub_69A5F0((uint32_t *)*(this + 10), v35 + 98, *(uint32_t *)(*(this + 2) + 32) + v34 - 43);
  *((uint8_t *)this + 73) = 0;
  *((uint8_t *)this + 74) = 0;
  sub_698F90((int)(this + 15), 10000, 0);
  return 1;
}


// ============================================================
// 【分区 12】角色删除确认 CNRDCharacterDeleteConfirmWindow（0x6347E0-0x634BB0）
// vmt8 确认（40BF00 角色删除 + 41C100 二次输入校验）。
// ============================================================
// ------------------------------------------------------------
// 0x6347E0 CNRDCharacterDeleteConfirmWindow__vmt8 —— CNRDCharacterDeleteConfirmWindow__vmt8 确认：40BF00 角色删除 + 423200 系 + 41C100 二次输入校验 + CLICK_BUTTON2
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDCharacterDeleteConfirmWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  unsigned int *v3; // ecx
  const char *v4; // eax
  uint32_t *v5; // eax
  uint8_t *result; // eax
  uint8_t v7[4]; // [esp+4h] [ebp-4h] BYREF

  sub_69A650(*(this + 2));
  v2 = *(this + 9);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    if ( *(this + 17) < 0x10u )
      v4 = (const char *)(this + 12);
    else
      v4 = (const char *)*(this + 12);
    v3 = (unsigned int *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 16) + 80) + 144 * *(this + 18));
    if ( sub_40BF00((std::_String_base *)v3, 0, v3[5], v4, *(this + 16)) == 0 )
    {
      sub_423200(dword_8F7B08, 6);
      v7[0] = *((uint8_t *)this + 72);
      sub_423290(dword_8F7B08, (int)v7, 1);
      if ( *(this + 17) < 0x10u )
        v5 = this + 12;
      else
        v5 = (uint32_t *)*(this + 12);
      sub_41C100(v5);
      sub_423380(dword_8F7B08);
    }
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = (uint8_t *)*(this + 10);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6348E0 sub_6348E0 —— 角色删除清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_6348E0(uint32_t *this)
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



// ------------------------------------------------------------
// 0x6349C0 sub_6349C0 —— 公告数据（4015C0）
// ------------------------------------------------------------
int /*thiscall*/ sub_6349C0(uint32_t *this)
{
  int result; // eax

  *(this + 9) = 0;
  *(this + 10) = 0;
  result = sub_4015C0((void *)szPassword, 0);
  *(this + 18) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x6349F0 CNRDCharacterDeleteConfirmWindow__vmtC —— CNRDCharacterDeleteConfirmWindow__vmtC 文案装配（4015C0 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDCharacterDeleteConfirmWindow__vmtC(char *this, void *Src, int a3)
{
  char *v4; // edi
  char *v5; // eax
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // ecx
  int v9; // ebx
  int v10; // edi

  sub_4015C0(Src, strlen((const char *)Src));
  *((uint32_t *)this + 18) = a3;
  sub_69C340(-1);
  sub_69C440(-1);
  if ( *((uint32_t *)this + 17) < 0x10u )
    v4 = this + 48;
  else
    v4 = *((char **)this + 12);
  sub_69C360(v4, 0);
  v5 = sub_422E70(917);
  sub_69C360(v5, 0);
  v6 = *(uint32_t *)this;
  v7 = sub_69C500(*((uint32_t *)this + 3));
  (*(void (/*thiscall*/ **)(char *, int, int))(v6 + 24))(this, 14, v7 + 5);
  v8 = *((uint32_t **)this + 2);
  v9 = pt.x - 125 <= 0 ? 0 : pt.x - 125;
  if ( v9 >= 640 - v8[7] )
    v9 = 640 - v8[7];
  v10 = 480 - v8[8];
  if ( (pt.y - v8[8] + 31 <= 0 ? 0 : pt.y - v8[8] + 31) < v10 )
    v10 = pt.y - v8[8] + 31 <= 0 ? 0 : pt.y - v8[8] + 31;
  sub_69A5F0(v8, v9, v10);
  sub_69A5F0(*((uint32_t **)this + 9), v9 + 29, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v10 - 43);
  sub_69A5F0(*((uint32_t **)this + 10), v9 + 98, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v10 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x634B10 CNRDNoticeMessageWindow__vmtC —— CNRDNoticeMessageWindow__vmtC 公告装配（69C340 系 + 69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDNoticeMessageWindow__vmtC(int *this, int a2, int a3)
{
  int v5; // edi
  int v6; // eax
  uint32_t *v7; // ecx
  int v8; // ebx
  int v9; // edi

  if ( a2 == 0 )
    return 0;
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(a2, 0);
  v5 = *this;
  v6 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(int *, int, int))(v5 + 24))(this, 26, v6 + 5);
  v7 = (uint32_t *)*(this + 2);
  v8 = (480 - v7[8]) / 2;
  v9 = (640 - v7[7]) / 2;
  sub_69A5F0(v7, v9, v8);
  sub_69A5F0(
    (uint32_t *)*(this + 9),
    v9 + ((unsigned int)(*(uint32_t *)(*(this + 2) + 28) - *(uint32_t *)(*(this + 9) + 28)) >> 1),
    *(uint32_t *)(*(this + 2) + 32) + v8 - 43);
  return 1;
}



// ============================================================
// 【分区 13】公告与任务放弃（0x634BB0-0x634F40）
// CNRDNoticeMessageWindow 公告弹窗；CNRDQuestGiveupConfirmWindow
// 任务放弃：vmt14 发 QUEST_ABANDON 事件（47C080/47B820）。
// ============================================================
// ------------------------------------------------------------
// 0x634BB0 sub_634BB0 —— 公告清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_634BB0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 288, 2048);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  return sub_69A840(v3);
}



// ------------------------------------------------------------
// 0x634C40 sub_634C40 —— 任务放弃数据（13 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_634C40(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x634C50 CNRDQuestGiveupConfirmWindow__vmt8 —— CNRDQuestGiveupConfirmWindow__vmt8 确认放弃（47C080 + CLICK_BUTTON2）
// ------------------------------------------------------------
int /*thiscall*/ CNRDQuestGiveupConfirmWindow__vmt8(int *this)
{
  int result; // eax
  int v3; // eax

  sub_69A650(*(this + 2));
  if ( sub_47C080((uint32_t *)dword_8F8540, *(this + 11)) == 0 )
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  v3 = *(this + 9);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 20))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = *(this + 10);
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x634CE0 CNRDQuestGiveupConfirmWindow__vmt14 —— CNRDQuestGiveupConfirmWindow__vmt14 放弃执行：QUEST_ABANDON 事件（47C080/47B820/432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDQuestGiveupConfirmWindow__vmt14(int *this)
{
  if ( sub_47C080((uint32_t *)dword_8F8540, *(this + 11)) != 0 )
    sub_47B820((uint32_t *)dword_8F8540, *(this + 11));
  (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
  sub_432EA0("QUEST_ABANDON", -1, 0, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x634D30 CNRDQuestGiveupConfirmWindow__vmtC —— CNRDQuestGiveupConfirmWindow__vmtC 文案装配（422E70 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDQuestGiveupConfirmWindow__vmtC(int *this, int *a2, int a3)
{
  uint32_t *v5; // eax
  char *v6; // eax
  int v7; // edi
  int v8; // eax
  uint32_t *v9; // ecx
  int v10; // ebx
  int v11; // edi
  uint32_t *v12; // [esp-Ch] [ebp-94h]
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int v14; // [esp+84h] [ebp-4h]

  v14 = dword_796E50;
  if ( a2 == nullptr )
    return 0;
  *(this + 11) = *a2;
  if ( (unsigned int)a2[7] < 0x10 )
    v5 = a2 + 2;
  else
    v5 = (uint32_t *)a2[2];
  v12 = v5;
  v6 = sub_422E70(1136);
  sprintf(Buffer, v6, v12);
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(Buffer, 0);
  v7 = *this;
  v8 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(int *, int, int))(v7 + 24))(this, 14, v8 + 5);
  v9 = (uint32_t *)*(this + 2);
  v10 = pt.x - 125 <= 0 ? 0 : pt.x - 125;
  if ( v10 >= 640 - v9[7] )
    v10 = 640 - v9[7];
  v11 = 480 - v9[8];
  if ( (pt.y - v9[8] + 31 <= 0 ? 0 : pt.y - v9[8] + 31) < v11 )
    v11 = pt.y - v9[8] + 31 <= 0 ? 0 : pt.y - v9[8] + 31;
  sub_69A5F0(v9, v10, v11);
  sub_69A5F0((uint32_t *)*(this + 9), v10 + 29, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);
  sub_69A5F0((uint32_t *)*(this + 10), v10 + 98, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x634E60 sub_634E60 —— 任务放弃清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_634E60(uint32_t *this)
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
// 【分区 14】退出副本确认 CNRDWalkoutConfirmWindow（0x634F40-0x635250）
// vmt14 执行退场（48F500）。
// ============================================================
// ------------------------------------------------------------
// 0x634F40 sub_634F40 —— 退场数据（13 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_634F40(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0xFFFF;
  return 0;
}



// ------------------------------------------------------------
// 0x634F50 CNRDWalkoutConfirmWindow__vmt8 —— CNRDWalkoutConfirmWindow__vmt8 确认退场（429830 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDWalkoutConfirmWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  if ( *(this + 11) != 0xFFFF && sub_429830((uint32_t *)dword_8F8500, *((uint16_t *)this + 22)) == 0 )
    *(this + 11) = 0xFFFF;
  v2 = *(this + 9);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 20))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = (uint8_t *)*(this + 10);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x634FF0 CNRDWalkoutConfirmWindow__vmt14 —— CNRDWalkoutConfirmWindow__vmt14 退场执行（48F500）
// ------------------------------------------------------------
char /*thiscall*/ CNRDWalkoutConfirmWindow__vmt14(uint32_t *this)
{
  int v2; // edx
  int v3; // eax
  uint32_t *i; // ecx

  if ( dword_99FEC0 != 0 )
  {
    v2 = *(this + 11);
    if ( v2 != 0xFFFF )
    {
      v3 = 0;
      for ( i = (uint32_t *)(dword_99FEC0 + 40); *i != v2; ++i )
      {
        if ( ++v3 >= 8 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
          return 1;
        }
      }
      sub_48F500(v3, 254);
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x635050 CNRDWalkoutConfirmWindow__vmtC —— CNRDWalkoutConfirmWindow__vmtC 文案装配（429830 + 422E70 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDWalkoutConfirmWindow__vmtC(int *this, int a2, int a3)
{
  int v4; // eax
  int v6; // eax
  char *v7; // eax
  int v8; // edi
  int v9; // eax
  uint32_t *v10; // ecx
  int v11; // ebx
  int v12; // edi
  int v13; // [esp-Ch] [ebp-94h]
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int v15; // [esp+84h] [ebp-4h]

  v15 = dword_796E50;
  *(this + 11) = a3;
  v4 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)a3);
  if ( v4 == 0 )
    return 0;
  if ( *(uint32_t *)(v4 + 40) < 0x10u )
    v6 = v4 + 20;
  else
    v6 = *(uint32_t *)(v4 + 20);
  v13 = v6;
  v7 = sub_422E70(1175);
  sprintf(Buffer, v7, v13);
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(Buffer, 0);
  v8 = *this;
  v9 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(int *, int, int))(v8 + 24))(this, 14, v9 + 5);
  v10 = (uint32_t *)*(this + 2);
  v11 = (480 - v10[8]) / 2;
  v12 = (640 - v10[7]) / 2;
  sub_69A5F0(v10, v12, v11);
  sub_69A5F0((uint32_t *)*(this + 9), v12 + 29, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);
  sub_69A5F0((uint32_t *)*(this + 10), v12 + 98, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x635170 sub_635170 —— 退场清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_635170(uint32_t *this)
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
// 【分区 15】PVP 房间创建/信息（0x635250-0x636030）
// CNRDPVPRoomCreateWindow：vmt8 Update（144 行，522500/540870 数量控件
// + 423200 系参数）；CNRDPVPRoomInfoWindow：vmt8 进入房间（487420/48F6C0）。
// ============================================================
// ------------------------------------------------------------
// 0x635250 sub_635250 —— PVP 房间数据（29 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_635250(uint32_t *this)
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
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  return this + 14;
}



// ------------------------------------------------------------
// 0x6352A0 sub_6352A0 —— PVP 房间数据 2（41 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6352A0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  uint32_t *v7; // esi
  int i; // edi

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 11) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  *(this + 12) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  *(this + 13) = 0;
  v7 = this + 14;
  for ( i = 16; i != 0; --i )
  {
    if ( *v7 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v7)(*v7, 1);
    *v7++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x635310 CNRDPVPRoomCreateWindow__vmt8 —— CNRDPVPRoomCreateWindow__vmt8 Update（144 行：522500 房名 + 540870 数量 + 69B740/69BCC0 输入 + 4BF300）
// ------------------------------------------------------------
int /*thiscall*/ sub_635310(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  char v9; // cl
  int v10; // eax
  const char *v11; // eax
  int v12; // ebx
  int v13; // eax
  const char *v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int *v18; // eax
  bool v19; // dl
  int i; // ecx
  int v21; // esi
  int v22; // eax
  uint32_t *v23; // ecx
  int v24; // esi
  const char *v25; // ebx
  int *v26; // eax
  int j; // ecx
  int v28; // edx
  unsigned int v29; // [esp+4h] [ebp-8h] BYREF
  uint8_t v30[4]; // [esp+8h] [ebp-4h] BYREF

  if ( dword_9B9534 == 0 )
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  sub_69A650(*(this + 2));
  v3 = *(this + 2);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    dword_79BE4C = *(uint32_t *)(*(this + 10) + 12);
    dword_79BE54 = dword_79BE4C;
    v4 = *(this + 2);
    v5 = *(uint32_t *)(v4 + 20);
    v6 = *(uint32_t *)(v4 + 24);
    if ( pt.x >= v5 + 43 && pt.x < v5 + 193 && pt.y >= v6 + 36 && pt.y < v6 + 52 && sub_522500(*(this + 10)) != 0 )
      sub_540870(szPassword);
  }
  v7 = *(this + 11);
  if ( *(uint8_t *)(v7 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v7 + 12)
    || (v8 = *(this + 10), v9 = *(uint8_t *)(v8 + 116), *(uint8_t *)(v8 + 116) = 0, v9 != 0) )
  {
    v29 = strlen((const char *)sub_69B740(*(this + 10)));
    if ( v29 != 0 )
    {
      v11 = (const char *)sub_69B740(*(this + 10));
      if ( strstr(v11, "%") == nullptr )
      {
        v12 = 0;
        v29 = 0;
        while ( 1 )
        {
          v13 = strcmp((const char *)sub_69B740(*(this + 10)), (const char *)dword_99FEC8[v12++]);
          if ( v13 == 0 )
            break;
          if ( v12 >= 16 )
          {
            v12 = v29;
            break;
          }
        }
        sub_423200(dword_8F7B08, 53);
        v30[0] = v12;
        sub_423290(v30, 1);
        if ( v12 == 0 )
        {
          v14 = (const char *)sub_69B740(*(this + 10));
          sub_41C100(v14);
        }
        v29 = 0;
        sub_423290(&v29, 2);
        sub_423380(dword_8F7B08);
        (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
        goto LABEL_26;
      }
      v10 = sub_422E70(1135);
    }
    else
    {
      v10 = sub_422E70(1134);
    }
    sub_44E8D0((char *)*(this + 4), (void *)0x1B, v10, 0);
  }
LABEL_26:
  v15 = *(this + 11);
  if ( *(uint8_t *)(v15 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v15 + 12) )
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  v16 = *(this + 13);
  if ( *(uint8_t *)(v16 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v16 + 12) )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v17 = *(this + 12);
  if ( *(uint8_t *)(v17 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v17 + 12) )
  {
    v18 = this + 14;
    v19 = *(uint8_t *)(*(this + 14) + 16) == 0;
    for ( i = 16; i != 0; --i )
    {
      v21 = *v18++;
      *(uint8_t *)(v21 + 16) = v19;
    }
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v22 = 0;
  v23 = this + 14;
  while ( *(uint8_t *)(*v23 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*v23 + 12) )
  {
    ++v22;
    ++v23;
    if ( v22 >= 16 )
      goto LABEL_45;
  }
  v24 = *(this + 10);
  v25 = (const char *)dword_99FEC8[v22];
  sub_69BCC0(v24);
  sub_402AE0(v24 + 180, v25);
  v26 = this + 14;
  for ( j = 16; j != 0; --j )
  {
    v28 = *v26++;
    *(uint8_t *)(v28 + 16) = 0;
  }
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
LABEL_45:
  sub_4BF300(dword_8F8558, 0, 0);
  result = *(this + 4);
  *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(result + 28) + 136) + 17) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x635630 CNRDPVPRoomCreateWindow__vmtC —— CNRDPVPRoomCreateWindow__vmtC 打开槽（69A5F0 + 43B920 + 69BCC0/402AE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPVPRoomCreateWindow__vmtC(int *this, int a2, int a3)
{
  int v4; // ecx
  unsigned int v5; // edi
  int v6; // edx
  int v7; // ecx
  uint32_t *v8; // edi
  unsigned int v9; // eax
  unsigned int v10; // edx
  int v11; // ebx
  int *v12; // eax
  int i; // ecx
  int v14; // edx

  v4 = *(this + 2);
  v5 = *(uint32_t *)(v4 + 28);
  v6 = pt.y - (*(uint32_t *)(v4 + 32) >> 1);
  if ( ((int)(pt.x - (v5 >> 1)) <= 0 ? 0 : pt.x - (v5 >> 1)) >= 640 - v5 )
    v7 = 640 - *(uint32_t *)(*(this + 2) + 28);
  else
    v7 = (int)(pt.x - (v5 >> 1)) <= 0 ? 0 : pt.x - (v5 >> 1);
  v8 = (uint32_t *)*(this + 2);
  v9 = 480 - v8[8];
  v10 = v6 <= 0 ? 0 : v6;
  if ( v10 < v9 )
    v9 = v10;
  sub_69A5F0(v8, v7, v9);
  sub_43B920(*(uint32_t *)(*(this + 4) + 28), 0);
  v11 = dword_99FEC8[rand() % 16];
  sub_69BCC0(*(this + 10));
  sub_402AE0(v11);
  dword_79BE4C = *(uint32_t *)(*(this + 10) + 12);
  dword_79BE54 = dword_79BE4C;
  v12 = this + 14;
  for ( i = 16; i != 0; --i )
  {
    v14 = *v12++;
    *(uint8_t *)(v14 + 16) = 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x635710 CNRDPVPRoomCreateWindow__vmt10 —— CNRDPVPRoomCreateWindow__vmt10 状态切换槽（22 行）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPVPRoomCreateWindow__vmt10(uint32_t *this)
{
  int v2; // eax
  int result; // eax

  v2 = *(uint32_t *)(*(this + 4) + 28);
  if ( *(uint8_t *)(v2 + 256) == 0 )
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v2 + 124) + 12);
    dword_79BE54 = dword_79BE4C;
  }
  CNCommandChecker__vmt40(0, 1);
  result = *(uint32_t *)(*(this + 4) + 28);
  *(uint8_t *)(*(uint32_t *)(result + 136) + 17) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x635760 CNRDPVPRoomCreateWindow__vmt0 —— CNRDPVPRoomCreateWindow__vmt0 构造（418DD0 + 491530/491630，66 行）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPVPRoomCreateWindow__vmt0(uint32_t *this, int a2)
{
  int v3; // edi
  int v4; // esi
  int v5; // eax
  int v6; // eax
  uint32_t *v7; // eax
  int v8; // edi
  int v9; // edi
  int v10; // esi
  int v11; // eax

  IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 2) )
  {
    v3 = *(uint32_t *)(a2 + 20);
    v4 = *(uint32_t *)(a2 + 24);
    v5 = sub_418DD0(104);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, v3 + 8, v4 + 8, dword_79C0B0);
    v6 = sub_418DD0(141);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v3 + 73, v4 + 13, dword_79C0B0);
    v7 = (uint32_t *)sub_418DD0(100);
    if ( v7 != nullptr )
      LOBYTE(v7) = (*(char (/*thiscall*/ **)(uint32_t *, int, int, int))(*v7 + 152))(v7, v3 + 8, v4 + 35, dword_79C0B0);
  }
  else
  {
    v8 = 0;
    v7 = this + 14;
    while ( a2 != *v7 )
    {
      ++v8;
      ++v7;
      if ( v8 >= 16 )
        return (char)v7;
    }
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      *(uint32_t *)(a2 + 20) + 4,
      *(uint32_t *)(a2 + 24) + 4,
      -1,
      dword_99FEC8[v8]);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    LOBYTE(v7) = *(uint8_t *)(a2 + 17);
    if ( (uint8_t)v7 != 0 && dword_79BE3C == *(uint32_t *)(a2 + 12) )
    {
      sub_491530(2, 0);
      v9 = *(uint32_t *)(a2 + 24);
      v10 = *(uint32_t *)(a2 + 20);
      v11 = sub_418DD0(96);
      if ( v11 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(v11, v10, v9, dword_79C0B0);
      LOBYTE(v7) = sub_491630(2);
    }
  }
  return (char)v7;
}



// ------------------------------------------------------------
// 0x6358C0 sub_6358C0 —— PVP 房间页绘制（43C060/69A5F0/69A840/43C410 + 426BD0/69C6B0，82 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6358C0(int *this)
{
  void *v2; // eax
  int v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // ebx
  uint32_t *v11; // edi
  void *Block; // [esp+10h] [ebp-14h]
  int v14; // [esp+14h] [ebp-10h]

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0xE4u);
  if ( v2 != nullptr )
    v3 = sub_43C060((int)v2, 19, 155);
  else
    v3 = 0;
  *(this + 10) = v3;
  dword_9D3BD8 = dword_99FCCC;
  sub_69A5F0((uint32_t *)*(this + 10), 46, 39);
  sub_69A840(*(this + 10));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 9), 65, 66, 67, 65, 0, 0);
  else
    v5 = nullptr;
  *(this + 11) = (int)v5;
  sub_69A5F0(v5, 83, 58);
  sub_69A840(*(this + 11));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(this + 9), 91, 92, 93, 91, 0, 0);
  else
    v7 = nullptr;
  *(this + 12) = (int)v7;
  sub_69A5F0(v7, 195, 37);
  sub_69A840(*(this + 12));
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
    v9 = sub_43C410(v8, *(this + 9), 23, 24, 25, 23, 0, 0);
  else
    v9 = nullptr;
  *(this + 13) = (int)v9;
  sub_69A5F0(v9, 195, 11);
  sub_69A840(*(this + 13));
  v14 = 52;
  v10 = this + 14;
  do
  {
    v11 = operator new(0x6Cu);
    if ( v11 != nullptr )
    {
      Block = (void *)*(this + 9);
      sub_426BD0(v11);
      *v11 = &vftbl_nengine__CNFrame;
      sub_69C6B0(v11);
      nengine__CNFrame__vmt20(Block, 95);
    }
    else
    {
      v11 = nullptr;
    }
    *v10 = v11;
    v11[17] = this;
    sub_69A5F0((uint32_t *)*v10, 42, v14);
    sub_69A840(*v10++);
    v14 += 18;
  }
  while ( v14 < 340 );
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 17, 6);
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 28))(this, 3);
}



// ------------------------------------------------------------
// 0x635B00 CNRDPVPRoomInfoWindow__vmtC —— CNRDPVPRoomInfoWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPVPRoomInfoWindow__vmtC(uint32_t **this, int a2, int a3)
{
  dword_795D3C = a3;
  sub_69A5F0(*(this + 2), (640 - (*(this + 2))[7]) / 2, (480 - (*(this + 2))[8]) / 2);
  return 1;
}



// ------------------------------------------------------------
// 0x635B40 CNRDPVPRoomInfoWindow__vmt10 —— CNRDPVPRoomInfoWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDPVPRoomInfoWindow__vmt10()
{
  dword_795D3C = -1;
}



// ------------------------------------------------------------
// 0x635B50 CNRDPVPRoomInfoWindow__vmt8 —— CNRDPVPRoomInfoWindow__vmt8 Update（CLICK_BUTTON2 + 487420/48F6C0 进入房间 + 423200 系）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDPVPRoomInfoWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // [esp+4h] [ebp-4h] BYREF

  if ( dword_795D3C == -1 )
    return (uint8_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
  sub_69A650(*(this + 2));
  v3 = *(this + 10);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v4 = sub_487420(dword_795D3C);
  *(uint8_t *)(*(this + 11) + 17) = v4 != 0 && *(uint32_t *)(v4 + 72) != 2 && sub_48F6C0(v4) != 0;
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    sub_423200(dword_8F7B08, 54);
    v5 = dword_795D3C;
    sub_423290(dword_8F7B08, (int)&v5, 2);
    sub_423380(dword_8F7B08);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x635C40 CNRDPVPRoomInfoWindow__vmt0 —— CNRDPVPRoomInfoWindow__vmt0 构造（125 行：554930 + 487420/48F690/42B340/452580 + 40FC80/42A430/42A410）
// ------------------------------------------------------------
int /*userpurge*/ sub_635C40@<eax>(int a1@<ecx>, int a2@<esi>, int a3)
{
  int result; // eax
  int v5; // esi
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // eax
  int v16; // esi
  int v17; // eax
  int v18; // eax
  int v19; // esi
  int v20; // eax
  int v21; // eax
  int v22; // ebx
  bool v23; // cc
  int *v25; // [esp+Ch] [ebp-Ch]
  int v26; // [esp+10h] [ebp-8h]
  int v28; // [esp+20h] [ebp+8h]

  result = sub_554930(a3);
  if ( a3 == *(uint32_t *)(a1 + 8) )
  {
    v5 = *(uint32_t *)(a3 + 20);
    v6 = *(uint32_t *)(a3 + 24);
    v7 = sub_418DD0(103);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v5 + 8, v6 + 8, dword_79C0B0);
    v8 = sub_418DD0(101);
    if ( v8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, v5 + 47, v6 + 12, dword_79C0B0);
    result = sub_487420(dword_795D3C);
    if ( result != 0 )
    {
      v9 = v5 + 9;
      v10 = v6 + 34;
      v28 = v9;
      v26 = 0;
      v25 = (int *)(result + 8);
      do
      {
        v11 = sub_418DD0(45);
        if ( v11 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(v11, v9, v10, dword_79C0B0);
        if ( *v25 == 254 )
        {
          v12 = sub_418DD0(48);
          if ( v12 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, v9, v10, dword_79C0B0);
        }
        else if ( *v25 != 255 )
        {
          v13 = sub_48F690(v26);
          v14 = v13;
          if ( v13 != 0 )
          {
            v15 = sub_42B340(v13);
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, int))(*(uint32_t *)v15 + 384))(
              v15,
              v9,
              v10,
              16,
              16,
              1065353216,
              a2);
            v16 = *v25;
            if ( *v25 < 1 || v16 > 3 || (uint8_t)sub_452580(v26) != 0 )
            {
              v19 = v28;
            }
            else
            {
              sub_491530(2, 0);
              v17 = sub_418DD0(v16 + 88);
              sub_40FC80(v28, v10, v17);
              v18 = sub_418DD0(v16 + 96);
              v19 = v28;
              sub_40FC80(v28 + 18, v10, v18);
              sub_491630(2);
            }
            sub_491530(2, 0);
            v20 = sub_42A430(v14);
            if ( v20 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v20 + 152))(v20, v19 + 20, v10, dword_79C0B0);
            sub_491630(2);
            v21 = sub_42A410(v14);
            if ( v21 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v21 + 152))(v21, v19 + 20, v10, dword_79C0B0);
            a2 = a1 + 48;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);
            if ( *(uint32_t *)(v14 + 40) < 0x10u )
              v22 = v14 + 20;
            else
              v22 = *(uint32_t *)(v14 + 20);
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
              dword_79C0B0,
              v19 + 30,
              v10 + 3,
              -1,
              v22);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
            v9 = v28;
          }
        }
        result = v26 + 1;
        v10 += 17;
        v23 = ++v26 < 8;
        ++v25;
      }
      while ( v23 );
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x635ED0 sub_635ED0 —— PVP 房间信息清理（43C410/69A5F0/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_635ED0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  int v6; // edx

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(this + 9), 23, 24, 25, 23, 0, 0);
  else
    v3 = nullptr;
  *(this + 10) = v3;
  sub_69A5F0(v3, 136, 11);
  sub_69A840(*(this + 10));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 9), 62, 63, 64, 99, 0, 0);
  else
    v5 = nullptr;
  *(this + 11) = v5;
  sub_69A5F0(v5, 36, 174);
  sub_69A840(*(this + 11));
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;
  *(this + 16) = 6;
  *(this + 17) = 12;
  *(this + 18) = 0;
  *(this + 19) = 1600;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  v6 = *this;
  *(this + 24) = dword_99FCCC;
  *(this + 13) = -16777216;
  *(this + 19) = 144;
  *(this + 15) = 1;
  *(this + 20) = 1;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v6 + 24))(this, 12, 15);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 3);
}



// ============================================================
// 【分区 16】组队信息/创建（0x636030-0x637070）
// CNRDPartyInfoWindow vmt8 Update（4569F0/56A720 成员刷新）；
// CNRDPartyCreateWindow：vmtC 打开、vmt0 构造、vmt8 Update（242 行，
// 545510 队名输入 + 69AC60/69AC70/464740/40BE20 创建提交）。
// ============================================================
// ------------------------------------------------------------
// 0x636030 sub_636030 —— 组队信息数据（13 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_636030(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x636040 CNRDPartyInfoWindow__vmt8 —— CNRDPartyInfoWindow__vmt8 Update（CLICK_BUTTON2 + 4569F0/56A720/4564A0 成员操作）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDPartyInfoWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // edi

  if ( (uint8_t)sub_545510(3) == 0 || dword_795D40 == -1 )
    return (uint8_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
  sub_69A650(*(this + 2));
  v3 = *(this + 10);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v4 = sub_4569F0((uint32_t *)dword_8F850C, dword_795D40);
  v5 = v4;
  *(uint8_t *)(*(this + 11) + 17) = v4 != 0
                               && *(uint32_t *)(v4 + 60) - sub_56A720(v4) > 0
                               && *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) == 0;
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    sub_4564A0(*(uint32_t *)(v5 + 4 * *(uint32_t *)(v5 + 56) + 40));
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x636140 CNRDPartyInfoWindow__vmtC —— CNRDPartyInfoWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyInfoWindow__vmtC(uint32_t **this, int a2, int a3)
{
  dword_795D40 = a3;
  sub_69A5F0(*(this + 2), (640 - (*(this + 2))[7]) / 2, (480 - (*(this + 2))[8]) / 2);
  return 1;
}



// ------------------------------------------------------------
// 0x636180 CNRDPartyInfoWindow__vmt10 —— CNRDPartyInfoWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDPartyInfoWindow__vmt10()
{
  dword_795D40 = -1;
}



// ------------------------------------------------------------
// 0x636190 sub_636190 —— 组队成员数据（56A680，27 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_636190(int a1, int a2)
{
  int v2; // esi
  int v3; // eax
  uint32_t *i; // edx

  v2 = 0;
  v3 = 0;
  for ( i = (uint32_t *)(a1 + 40); *i == 0xFFFF; ++i )
  {
LABEL_5:
    if ( ++v3 >= 4 )
      return 0;
  }
  if ( v2 != a2 )
  {
    ++v2;
    goto LABEL_5;
  }
  return sub_56A680(v3);
}



// ------------------------------------------------------------
// 0x6361D0 CNRDPartyInfoWindow__vmt0 —— CNRDPartyInfoWindow__vmt0 构造（175 行：554930 + 4569F0/56A680/42B340/456480 + 422E70）
// ------------------------------------------------------------
char /*userpurge*/ sub_6361D0@<al>(int a1@<ecx>, int a2@<edi>, int a3)
{
  int v4; // eax
  int v5; // edi
  int v6; // esi
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // edi
  int v12; // esi
  int v13; // eax
  uint32_t *v14; // ecx
  uint32_t *v15; // esi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  uint32_t *v21; // ecx
  int v22; // eax
  int v23; // eax
  int v24; // eax
  bool v25; // cc
  int v26; // ecx
  int v27; // esi
  uint32_t *v28; // eax
  int v29; // edi
  int v30; // ebx
  unsigned int v31; // esi
  int v32; // eax
  int v35; // [esp+8h] [ebp-10h]
  int v36; // [esp+Ch] [ebp-Ch]
  int v37; // [esp+10h] [ebp-8h]
  int v38; // [esp+14h] [ebp-4h]
  int v39; // [esp+20h] [ebp+8h]

  LOBYTE(v4) = sub_554930(a3);
  if ( a3 != *(uint32_t *)(a1 + 8) )
    return v4;
  v5 = *(uint32_t *)(a3 + 20);
  v6 = *(uint32_t *)(a3 + 24);
  v7 = sub_418DD0(104);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v5 + 8, v6 + 8, dword_79C0B0);
  v8 = sub_418DD0(140);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, v5 + 79, v6 + 12, dword_79C0B0);
  v4 = sub_4569F0(dword_795D40);
  v9 = v4;
  v36 = v4;
  if ( v4 == 0 )
    return v4;
  v10 = 0;
  v11 = v5 + 9;
  v38 = v6 + 33;
  v37 = 0;
  v39 = v6 + 36;
  while ( 2 )
  {
    v12 = 0;
    v13 = 0;
    v14 = (uint32_t *)(v9 + 40);
    while ( *v14 == 0xFFFF )
    {
LABEL_13:
      ++v13;
      ++v14;
      if ( v13 >= 4 )
      {
        v15 = nullptr;
        goto LABEL_15;
      }
    }
    if ( v12 != v10 )
    {
      ++v12;
      goto LABEL_13;
    }
    v15 = (uint32_t *)sub_56A680(v13);
LABEL_15:
    v16 = sub_418DD0(45);
    if ( v16 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v16 + 152))(v16, v11, v38, dword_79C0B0);
    if ( v15 != nullptr )
    {
      v17 = sub_42B340(v15);
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, int))(*(uint32_t *)v17 + 384))(
        v17,
        v11,
        v38,
        16,
        16,
        1065353216,
        a2);
      if ( v37 == sub_456480(dword_8F850C) )
      {
        v18 = sub_418DD0(106);
        if ( v18 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v18 + 152))(v18, v11 - 1, v39 - 4, dword_79C0B0);
      }
      else
      {
        v19 = sub_418DD0(107);
        if ( v19 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v19 + 152))(v19, v11, v38, dword_79C0B0);
      }
      a2 = a1 + 48;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);
      v20 = sub_41A5E0((unsigned int)v15 + 53);
      (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v11 + 26,
        v39,
        -4732715,
        "Lv.%d",
        v20);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, a1 + 100);
      if ( v15[10] < 0x10u )
        v21 = v15 + 5;
      else
        v21 = (uint32_t *)v15[5];
      (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v11 - 3,
        v39,
        -4732715,
        v21);
      v35 = *(uint32_t *)dword_79C0B0;
      v22 = sub_4B0EC0(v15[11], v15[12]);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(v35 + 80))(dword_79C0B0, v11 + 73, v39, -8005942, v22);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    }
    else if ( v37 >= *(uint32_t *)(v36 + 60) )
    {
      v23 = sub_418DD0(108);
      if ( v23 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v23 + 152))(v23, v11, v38, dword_79C0B0);
      v24 = sub_418DD0(130);
      if ( v24 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v24 + 152))(v24, v11 + 24, v39 - 2, dword_79C0B0);
    }
    v25 = ++v37 < 4;
    v38 += 20;
    v39 += 20;
    if ( v25 )
    {
      v10 = v37;
      v9 = v36;
      continue;
    }
    break;
  }
  v26 = *(uint32_t *)(a1 + 44);
  LOBYTE(v4) = *(uint8_t *)(v26 + 17);
  if ( (uint8_t)v4 != 0 )
  {
    v27 = *(uint32_t *)(v26 + 12);
    if ( dword_79BE3C == v27 || dword_79BE34 == v27 || (LOBYTE(v4) = dword_79BE38, dword_79BE38 == v27) )
    {
      v28 = *(uint32_t **)(a1 + 44);
      v29 = v28[6];
      v30 = v28[5];
      v31 = v28[7];
      v32 = sub_422E70(1125);
      LOBYTE(v4) = sub_4649B0(v30 + (v31 >> 1), v29, -1, -16777216, 2, v32, 0, 0, 1600, 0);
    }
  }
  return v4;
}


// ------------------------------------------------------------
// 0x636500 sub_636500 —— 组队信息页绘制（43C410/69A5F0/69A840，70 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_636500(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  int v6; // edx

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(this + 9), 23, 24, 25, 23, 0, 0);
  else
    v3 = nullptr;
  *(this + 10) = v3;
  sub_69A5F0(v3, 195, 11);
  sub_69A840(*(this + 10));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 9), 126, 127, 128, 129, 0, 0);
  else
    v5 = nullptr;
  *(this + 11) = v5;
  sub_69A5F0(v5, 66, 111);
  sub_69A840(*(this + 11));
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;
  *(this + 16) = 6;
  *(this + 18) = 0;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 17) = 12;
  *(this + 19) = 1600;
  *(this + 24) = dword_99FCCC;
  *(this + 13) = -16777216;
  *(this + 32) = 1600;
  *((uint8_t *)this + 100) = 0;
  *((uint8_t *)this + 101) = 0;
  *((uint8_t *)this + 102) = 0;
  *((uint8_t *)this + 103) = 0;
  *(this + 28) = 0;
  *(this + 29) = 6;
  *(this + 30) = 12;
  *(this + 31) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  v6 = *this;
  *(this + 37) = dword_99FCCC;
  *(this + 26) = -16777216;
  *(this + 32) = 200;
  *(this + 28) = 1;
  *(this + 33) = 1;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v6 + 24))(this, 17, 10);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 3);
}



// ------------------------------------------------------------
// 0x6366C0 sub_6366C0 —— 组队创建数据（26 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6366C0(uint32_t *this)
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
  return 0;
}



// ------------------------------------------------------------
// 0x636700 sub_636700 —— 组队创建数据 2（55 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_636700(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  uint32_t *v7; // edi
  int i; // ebx
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  uint32_t *v10; // esi
  int j; // edi

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 11) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  *(this + 12) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  *(this + 13) = 0;
  v7 = this + 14;
  for ( i = 3; i != 0; --i )
  {
    if ( *v7 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v7)(*v7, 1);
    *v7++ = 0;
  }
  v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 17);
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  *(this + 17) = 0;
  v10 = this + 18;
  for ( j = 6; j != 0; --j )
  {
    if ( *v10 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v10)(*v10, 1);
    *v10++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6367A0 CNRDPartyCreateWindow__vmtC —— CNRDPartyCreateWindow__vmtC 打开槽（69A5F0 + 429830 + 69BCC0/402AE0 + 43B920）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyCreateWindow__vmtC(uint32_t *this, int a2, int a3)
{
  uint32_t *v4; // edi
  unsigned int v5; // ecx
  unsigned int v6; // eax
  unsigned int v7; // ecx
  int v9; // [esp+Ch] [ebp-4h]

  v4 = (uint32_t *)*(this + 2);
  v5 = v4[7];
  v6 = (int)(pt.x - (v5 >> 1)) <= 0 ? 0 : pt.x - (v5 >> 1);
  if ( v6 >= 640 - v5 )
    v6 = 640 - v5;
  v7 = 480 - v4[8];
  if ( (pt.y - (v4[8] >> 1) <= 0 ? 0 : pt.y - (v4[8] >> 1)) < v7 )
    v7 = pt.y - (v4[8] >> 1) <= 0 ? 0 : pt.y - (v4[8] >> 1);
  sub_69A5F0(v4, v6, v7);
  if ( *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) != 0 )
  {
    sub_69BCC0(*(this + 10));
    *(this + 24) = *(uint32_t *)(*(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) + 60);
  }
  else
  {
    v9 = dword_9B8890[rand() % 6];
    sub_69BCC0(*(this + 10));
    sub_402AE0(v9);
    *(this + 24) = 4;
  }
  sub_43B920(*(uint32_t *)(*(this + 4) + 28), 0);
  dword_79BE4C = *(uint32_t *)(*(this + 10) + 12);
  dword_79BE54 = dword_79BE4C;
  *(uint8_t *)(*(this + 18) + 16) = 0;
  *(uint8_t *)(*(this + 19) + 16) = 0;
  *(uint8_t *)(*(this + 20) + 16) = 0;
  *(uint8_t *)(*(this + 21) + 16) = 0;
  *(uint8_t *)(*(this + 22) + 16) = 0;
  *(uint8_t *)(*(this + 23) + 16) = 0;
  *(uint8_t *)(*(this + 14) + 16) = 0;
  *(uint8_t *)(*(this + 15) + 16) = 0;
  *(uint8_t *)(*(this + 16) + 16) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x6368F0 CNRDPartyCreateWindow__vmt0 —— CNRDPartyCreateWindow__vmt0 构造（418DD0 + 429830 + 491530/491630，110 行）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyCreateWindow__vmt0(uint32_t *this, int a2)
{
  int v3; // edi
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  uint32_t *v8; // eax
  int v9; // edi
  uint32_t *v10; // eax
  int v11; // edi
  int v12; // edi
  int v13; // esi
  int v14; // eax
  int v16; // [esp-4h] [ebp-10h]

  IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 2) )
  {
    v3 = *(uint32_t *)(a2 + 20);
    v4 = *(uint32_t *)(a2 + 24);
    v5 = sub_418DD0(136);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, v3 + 8, v4 + 8, dword_79C0B0);
    if ( *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) != 0 )
      v6 = sub_418DD0(142);
    else
      v6 = sub_418DD0(139);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v3 + 101, v4 + 13, dword_79C0B0);
    v7 = sub_418DD0(133);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v3 + 8, v4 + 35, dword_79C0B0);
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
    (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v3 + 54,
      v4 + 62,
      -1,
      "%d",
      *(this + 24));
    LOBYTE(v8) = (*(char (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  }
  else
  {
    v9 = 0;
    v10 = this + 18;
    do
    {
      if ( a2 == *v10 )
      {
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          *(uint32_t *)(a2 + 20) + 4,
          *(uint32_t *)(a2 + 24) + 4,
          -1,
          dword_9B8890[v9]);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        LOBYTE(v8) = *(uint8_t *)(a2 + 17);
        if ( (uint8_t)v8 == 0 || dword_79BE3C != *(uint32_t *)(a2 + 12) )
          return (char)v8;
        sub_491530(2, 0);
        v16 = 137;
        goto LABEL_25;
      }
      ++v9;
      ++v10;
    }
    while ( v9 < 6 );
    v11 = 0;
    v8 = this + 14;
    while ( a2 != *v8 )
    {
      ++v11;
      ++v8;
      if ( v11 >= 3 )
        return (char)v8;
    }
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
    (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      *(uint32_t *)(a2 + 20) + 12,
      *(uint32_t *)(a2 + 24) + 4,
      -1,
      "%d",
      v11 + 2);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    LOBYTE(v8) = *(uint8_t *)(a2 + 17);
    if ( (uint8_t)v8 != 0 && dword_79BE3C == *(uint32_t *)(a2 + 12) )
    {
      sub_491530(2, 0);
      v16 = 138;
LABEL_25:
      v12 = *(uint32_t *)(a2 + 24);
      v13 = *(uint32_t *)(a2 + 20);
      v14 = sub_418DD0(v16);
      if ( v14 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 152))(v14, v13, v12, dword_79C0B0);
      LOBYTE(v8) = sub_491630(2);
    }
  }
  return (char)v8;
}



// ------------------------------------------------------------
// 0x636B30 CNRDPartyCreateWindow__vmt8 —— CNRDPartyCreateWindow__vmt8 Update（242 行：545510 队名输入 + 522500/540870 + 69AC60/69AC70/464740/40BE20 创建提交 + 48B740/48B7C0）
// ------------------------------------------------------------
int /*thiscall*/ sub_636B30(char *this)
{
  int result; // eax
  DWORD v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  const char *v11; // ebx
  uint32_t *v12; // edi
  int v13; // edx
  int v14; // eax
  int v15; // eax
  uint32_t *v16; // ebx
  int v17; // edi
  uint32_t *v18; // ecx
  int v19; // eax
  const char *v20; // edx
  uint32_t *v21; // edi
  int v22; // eax
  int v23; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  bool v27; // zf
  int v28; // eax
  char *v29; // ecx
  int v30; // eax
  bool v31; // al
  int v32; // eax
  char *v33; // ecx
  int v34; // edi
  const char *v35; // ebx
  uint32_t *v36; // [esp+8h] [ebp-10h]
  int v37; // [esp+8h] [ebp-10h]
  int v38; // [esp+Ch] [ebp-Ch]
  char *Str; // [esp+10h] [ebp-8h]
  char v40[4]; // [esp+14h] [ebp-4h] BYREF

  if ( (uint8_t)sub_545510(3) == 0 )
    return (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 32))(this);
  sub_69A650(*((uint32_t *)this + 2));
  v4 = *((uint32_t *)this + 2);
  if ( *(uint8_t *)(v4 + 17) != 0 )
  {
    v3 = dword_79BE34;
    if ( dword_79BE34 == *(uint32_t *)(v4 + 12) )
    {
      dword_79BE4C = *(uint32_t *)(*((uint32_t *)this + 10) + 12);
      dword_79BE54 = dword_79BE4C;
      v5 = *((uint32_t *)this + 2);
      v6 = *(uint32_t *)(v5 + 20);
      v7 = *(uint32_t *)(v5 + 24);
      if ( pt.x >= v6 + 43
        && pt.x < v6 + 219
        && pt.y >= v7 + 36
        && pt.y < v7 + 52
        && sub_522500(*((uint32_t *)this + 10)) != 0 )
      {
        sub_540870(szPassword);
      }
      if ( (uint8_t)sub_69AC60(*((uint32_t *)this + 10)) != 0 )
      {
        v8 = sub_69AC70(*((uint32_t *)this + 10));
        sub_464740(v6 + 15, v7 - 150, v8 + 10, 11, 0, 0);
      }
    }
  }
  v9 = *((uint32_t *)this + 11);
  if ( *(uint8_t *)(v9 + 17) != 0 && (v3 = dword_79BE34, dword_79BE34 == *(uint32_t *)(v9 + 12))
    || (v10 = *((uint32_t *)this + 10), LOBYTE(v3) = *(uint8_t *)(v10 + 116), *(uint8_t *)(v10 + 116) = 0, (uint8_t)v3 != 0) )
  {
    sub_40BE20(v3, "\n CNRDPartyCreateWindow Enter");
    v11 = (const char *)sub_69B740(*((uint32_t *)this + 10));
    Str = (char *)v11;
    v38 = 0;
    v12 = *(uint32_t **)(sub_429830((uint16_t)word_77F804) + 184);
    v36 = v12;
    if ( v12 != nullptr && strlen(v11) == 0 )
    {
      v11 = (const char *)sub_6307E0(v12);
      Str = (char *)v11;
    }
    v13 = 0;
    while ( 1 )
    {
      v14 = strcmp(v11, (const char *)dword_9B8890[v13++]);
      if ( v14 == 0 )
        break;
      if ( v13 >= 6 )
        goto LABEL_25;
      v11 = Str;
    }
    v38 = v13;
LABEL_25:
    if ( strlen(Str) == 0 )
    {
      v15 = sub_422E70(1121);
LABEL_27:
      sub_44E8D0(*((char **)this + 4), (void *)0x1B, v15, 0);
      goto LABEL_47;
    }
    if ( strstr(Str, "%") != nullptr )
    {
      v15 = sub_422E70(1122);
      goto LABEL_27;
    }
    v16 = v36;
    if ( v36 != nullptr )
    {
      v17 = *((uint32_t *)this + 24);
      v18 = v36;
      v37 = v17;
      if ( v17 < sub_56A720(v18) )
      {
        v15 = sub_422E70(1123);
        goto LABEL_27;
      }
      v19 = v16[2];
      if ( v19 != 0 )
      {
        v20 = (const char *)dword_9B8890[(v19 - 1) % 6];
      }
      else if ( v16[9] < 0x10u )
      {
        v20 = (const char *)(v16 + 4);
      }
      else
      {
        v20 = (const char *)v16[4];
      }
      if ( strcmp(v20, Str) == 0 && v16[15] == v37 )
      {
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 32))(this);
        goto LABEL_47;
      }
    }
    sub_423200(dword_8F7B08, 12);
    v40[0] = v38;
    sub_423290(v40, 1);
    if ( v38 == 0 )
      sub_41C100(Str);
    v40[0] = *(this + 96);
    sub_423290(v40, 1);
    sub_423380(dword_8F7B08);
    if ( v16 == nullptr && sub_48B740((const CHAR *)dword_8F8544, 3) == 1 )
    {
      v21 = *(uint32_t **)(*((uint32_t *)this + 4) + 28);
      v22 = sub_422E70(1124);
      sub_43BEE0(v21, v22, -6567706, 0, -1);
      sub_48B7C0((const CHAR *)dword_8F8544, 3, 0);
    }
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 32))(this);
  }
LABEL_47:
  v23 = *((uint32_t *)this + 11);
  v24 = dword_79BE34;
  if ( *(uint8_t *)(v23 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v23 + 12) )
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v24 = dword_79BE34;
  }
  v25 = *((uint32_t *)this + 12);
  if ( *(uint8_t *)(v25 + 17) != 0 && v24 == *(uint32_t *)(v25 + 12) )
  {
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v24 = dword_79BE34;
  }
  v26 = *((uint32_t *)this + 13);
  if ( *(uint8_t *)(v26 + 17) != 0 && v24 == *(uint32_t *)(v26 + 12) )
  {
    v27 = *(uint8_t *)(*((uint32_t *)this + 14) + 16) == 0;
    *(uint8_t *)(*((uint32_t *)this + 14) + 16) = v27;
    *(uint8_t *)(*((uint32_t *)this + 15) + 16) = v27;
    *(uint8_t *)(*((uint32_t *)this + 16) + 16) = v27;
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v24 = dword_79BE34;
  }
  v28 = 0;
  v29 = this + 56;
  while ( *(uint8_t *)(*(uint32_t *)v29 + 17) == 0 || v24 != *(uint32_t *)(*(uint32_t *)v29 + 12) )
  {
    ++v28;
    v29 += 4;
    if ( v28 >= 3 )
      goto LABEL_62;
  }
  *((uint32_t *)this + 24) = v28 + 2;
  *(uint8_t *)(*((uint32_t *)this + 14) + 16) = 0;
  *(uint8_t *)(*((uint32_t *)this + 15) + 16) = 0;
  *(uint8_t *)(*((uint32_t *)this + 16) + 16) = 0;
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  v24 = dword_79BE34;
LABEL_62:
  v30 = *((uint32_t *)this + 17);
  if ( *(uint8_t *)(v30 + 17) != 0 && v24 == *(uint32_t *)(v30 + 12) )
  {
    v31 = *(uint8_t *)(*((uint32_t *)this + 18) + 16) == 0;
    *(uint8_t *)(*((uint32_t *)this + 18) + 16) = v31;
    *(uint8_t *)(*((uint32_t *)this + 19) + 16) = v31;
    *(uint8_t *)(*((uint32_t *)this + 20) + 16) = v31;
    *(uint8_t *)(*((uint32_t *)this + 21) + 16) = v31;
    *(uint8_t *)(*((uint32_t *)this + 22) + 16) = v31;
    *(uint8_t *)(*((uint32_t *)this + 23) + 16) = v31;
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v24 = dword_79BE34;
  }
  v32 = 0;
  v33 = this + 72;
  while ( *(uint8_t *)(*(uint32_t *)v33 + 17) == 0 || v24 != *(uint32_t *)(*(uint32_t *)v33 + 12) )
  {
    ++v32;
    v33 += 4;
    if ( v32 >= 6 )
      goto LABEL_71;
  }
  v34 = *((uint32_t *)this + 10);
  v35 = (const char *)dword_9B8890[v32];
  sub_69BCC0(v34);
  sub_402AE0(v34 + 180, v35);
  *(uint8_t *)(*((uint32_t *)this + 18) + 16) = 0;
  *(uint8_t *)(*((uint32_t *)this + 19) + 16) = 0;
  *(uint8_t *)(*((uint32_t *)this + 20) + 16) = 0;
  *(uint8_t *)(*((uint32_t *)this + 21) + 16) = 0;
  *(uint8_t *)(*((uint32_t *)this + 22) + 16) = 0;
  *(uint8_t *)(*((uint32_t *)this + 23) + 16) = 0;
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
LABEL_71:
  sub_4BF300(dword_8F8558, 0, 0);
  result = *((uint32_t *)this + 4);
  *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(result + 28) + 136) + 17) = 0;
  return result;
}


// ============================================================
// 【分区 17】退队建议窗 CNRDPartyLeaveSuggestWindow（0x637070-0x637680）
// ============================================================
// ------------------------------------------------------------
// 0x637070 sub_637070 —— 组队创建页绘制（133 行：43C060/69A5F0/69A840/43C410 + 426BD0/69C6B0/69C6C0/69C780/69C7B0）
// ------------------------------------------------------------
int /*thiscall*/ sub_637070(int *this)
{
  void *v2; // eax
  int v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  int *v10; // ebx
  uint32_t *v11; // edi
  uint8_t *v12; // eax
  uint32_t *v13; // edi
  int v14; // ebx
  uint32_t *v15; // ecx
  int *v16; // ebx
  uint8_t *v17; // eax
  uint32_t *v18; // edi
  void *Block; // [esp+10h] [ebp-14h]
  void *Blocka; // [esp+10h] [ebp-14h]
  int v22; // [esp+14h] [ebp-10h]
  int v23; // [esp+14h] [ebp-10h]

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0xE4u);
  if ( v2 != nullptr )
    v3 = sub_43C060((int)v2, 31, 180);
  else
    v3 = 0;
  *(this + 10) = v3;
  dword_9D3BD8 = dword_99FCCC;
  sub_69A5F0((uint32_t *)*(this + 10), 46, 39);
  sub_69A840((uint32_t *)*(this + 2), *(this + 10));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 9), 65, 66, 67, 65, 0, 0);
  else
    v5 = nullptr;
  *(this + 11) = (int)v5;
  sub_69A5F0(v5, 95, 84);
  sub_69A840((uint32_t *)*(this + 2), *(this + 11));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(this + 9), 23, 24, 25, 23, 0, 0);
  else
    v7 = nullptr;
  *(this + 12) = (int)v7;
  sub_69A5F0(v7, 219, 11);
  sub_69A840((uint32_t *)*(this + 2), *(this + 12));
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
    v9 = sub_43C410(v8, *(this + 9), 91, 92, 93, 91, 0, 0);
  else
    v9 = nullptr;
  *(this + 13) = (int)v9;
  sub_69A5F0(v9, 71, 60);
  sub_69A840((uint32_t *)*(this + 2), *(this + 13));
  v22 = 75;
  v10 = this + 14;
  do
  {
    v11 = operator new(0x6Cu);
    if ( v11 != nullptr )
    {
      Block = (void *)*(this + 9);
      sub_426BD0(v11);
      *v11 = &nengine::CNFrame::`vftable';
      sub_69C6B0(v11);
      sub_69C6C0((int)v11, (int)Block, 135);
    }
    else
    {
      v11 = nullptr;
    }
    *v10 = (int)v11;
    v11[17] = this;
    sub_69A5F0((uint32_t *)*v10, 42, v22);
    sub_69A840((uint32_t *)*(this + 2), *v10++);
    v22 += 18;
  }
  while ( v22 < 129 );
  v12 = operator new(0x84u);
  v13 = v12;
  if ( v12 != nullptr )
  {
    v14 = *(this + 9);
    sub_426BD0(v12);
    *v13 = &nengine::CNButton::`vftable';
    sub_69C780((int)v13);
    sub_69C7B0((int)v13, v14, 91, 92, 93, 91, 0, 0);
    v15 = v13;
  }
  else
  {
    v15 = nullptr;
  }
  *(this + 17) = (int)v15;
  sub_69A5F0(v15, 221, 37);
  sub_69A840((uint32_t *)*(this + 2), *(this + 17));
  v23 = 52;
  v16 = this + 18;
  do
  {
    v17 = operator new(0x6Cu);
    v18 = v17;
    if ( v17 != nullptr )
    {
      Blocka = (void *)*(this + 9);
      sub_426BD0(v17);
      *v18 = &nengine::CNFrame::`vftable';
      sub_69C6B0(v18);
      sub_69C6C0((int)v18, (int)Blocka, 134);
    }
    else
    {
      v18 = nullptr;
    }
    *v16 = (int)v18;
    v18[17] = this;
    sub_69A5F0((uint32_t *)*v16, 42, v23);
    sub_69A840((uint32_t *)*(this + 2), *v16++);
    v23 += 18;
  }
  while ( v23 < 160 );
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 19, 8);
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 28))(this, 3);
}


// ------------------------------------------------------------
// 0x6373B0 CNRDPartyLeaveSuggestWindow__vmt8 —— CNRDPartyLeaveSuggestWindow__vmt8 确认退队（456390 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDPartyLeaveSuggestWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  if ( sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) == 0
    || *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) == 0
    || sub_456390((char *)dword_8F850C, 0) != 1 )
  {
    return (uint8_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
  }
  v2 = *(this + 9);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = (uint8_t *)*(this + 10);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    sub_423200(dword_8F7B08, 13);
    sub_423380(dword_8F7B08);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x637490 CNRDPartyLeaveSuggestWindow__vmtC —— CNRDPartyLeaveSuggestWindow__vmtC 文案装配（429830 + 422E70 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyLeaveSuggestWindow__vmtC(int *this, int a2, int a3)
{
  int v4; // eax
  unsigned int v5; // ecx
  int v6; // eax
  int v7; // eax
  char *v8; // eax
  int v9; // edi
  int v10; // eax
  uint32_t *v11; // ecx
  int v12; // ebx
  int v13; // edi
  int v15; // [esp-4h] [ebp-94h]
  char Buffer[128]; // [esp+Ch] [ebp-84h] BYREF
  int v17; // [esp+8Ch] [ebp-4h]

  v17 = dword_796E50;
  v4 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  v5 = *(uint32_t *)(v4 + 40);
  v6 = v4 + 16;
  if ( v5 < 0x10 )
    v7 = v6 + 4;
  else
    v7 = *(uint32_t *)(v6 + 4);
  v15 = v7;
  v8 = sub_422E70(1126);
  sprintf(Buffer, v8, v15);
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(Buffer, 0);
  v9 = *this;
  v10 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(int *, int, int))(v9 + 24))(this, 14, v10 + 5);
  v11 = (uint32_t *)*(this + 2);
  v12 = (480 - v11[8]) / 2;
  v13 = (640 - v11[7]) / 2;
  sub_69A5F0(v11, v13, v12);
  sub_69A5F0((uint32_t *)*(this + 9), v13 + 29, *(uint32_t *)(*(this + 2) + 32) + v12 - 43);
  sub_69A5F0((uint32_t *)*(this + 10), v13 + 98, *(uint32_t *)(*(this + 2) + 32) + v12 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x6375A0 sub_6375A0 —— 退队清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_6375A0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 21, 22, 23, 21, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  sub_69A840(v3);
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 24, 25, 26, 24, 0, 0);
  else
    v5 = nullptr;
  *(this + 10) = v5;
  return sub_69A840(v5);
}



// ============================================================
// 【分区 18】好友/队员增删窗族（0x637680-0x6381B0）
// CNRDFriendAddRemoveWindow / CNRDMemberAddRemoveWindow /
// CNRDFriendRemoveConfirmWindow：vmt8 Update（545510 名字输入 + 提交）。
// ============================================================
// ------------------------------------------------------------
// 0x637680 sub_637680 —— 好友添加数据（27 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_637680(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 11) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  *(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6376C0 CNRDFriendAddRemoveWindow__vmt8 —— CNRDFriendAddRemoveWindow__vmt8 提交（545510 名字输入 + 69AC60/69AC70/464740 + 44E8D0 + CLICK_BUTTON2）
// ------------------------------------------------------------
int /*thiscall*/ CNRDFriendAddRemoveWindow__vmt8(void *this)
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  char v10; // cl
  char *v11; // eax
  int v12; // ecx
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax

  if ( (uint8_t)sub_545510(4) == 0 )
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
  sub_69A650(*((uint32_t *)this + 2));
  v3 = *((uint32_t *)this + 2);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    dword_79BE4C = *(uint32_t *)(*((uint32_t *)this + 10) + 12);
    dword_79BE54 = dword_79BE4C;
    v4 = *((uint32_t *)this + 2);
    v5 = *(uint32_t *)(v4 + 20);
    v6 = *(uint32_t *)(v4 + 24);
    if ( (uint8_t)sub_69AC60(*((uint32_t *)this + 10)) != 0 )
    {
      v7 = sub_69AC70(*((uint32_t *)this + 10));
      sub_464740(v5 + 15, v6 - 150, v7 + 10, 11, 0, 0);
    }
  }
  v8 = *((uint32_t *)this + 12);
  if ( *(uint8_t *)(v8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v8 + 12)
    || (v9 = *((uint32_t *)this + 10), v10 = *(uint8_t *)(v9 + 116), *(uint8_t *)(v9 + 116) = 0, v10 != 0) )
  {
    if ( strlen((const char *)sub_69B740(*((uint32_t *)this + 10))) != 0 )
    {
      v12 = *((uint32_t *)this + 10);
      if ( *((uint32_t *)this + 13) != 0 )
      {
        v15 = sub_69B740(v12);
        sub_44E8D0(*((char **)this + 4), (void *)0x2D, v15, 0);
      }
      else
      {
        v13 = *(uint32_t *)dword_8F8510;
        v14 = sub_69B740(v12);
        (*(void (/*thiscall*/ **)(int, int))(v13 + 4))(dword_8F8510, v14);
      }
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
    }
    else
    {
      v11 = sub_422E70(936);
      sub_44E8D0(*((char **)this + 4), (void *)0x1B, (int)v11, 0);
    }
  }
  v16 = *((uint32_t *)this + 12);
  if ( *(uint8_t *)(v16 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v16 + 12) )
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  v17 = *((uint32_t *)this + 11);
  if ( *(uint8_t *)(v17 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v17 + 12) )
  {
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  CNCommandChecker__vmt40(0, 0);
  result = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)this + 4) + 28) + 136);
  *(uint8_t *)(result + 17) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x637870 CNRDFriendAddRemoveWindow__vmt0 —— CNRDFriendAddRemoveWindow__vmt0 构造（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDFriendAddRemoveWindow__vmt0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // eax

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 2) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    v6 = sub_418DD0(156);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4 + 8, v5 + 8, dword_79C0B0);
    v7 = sub_418DD0(153 - (*(this + 13) != 0));
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v4 + 64, v5 + 13, dword_79C0B0);
    result = sub_418DD0(157);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(
               result,
               v4 + 8,
               v5 + 36,
               dword_79C0B0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x637920 sub_637920 —— 好友窗页绘制（43C060/69A5F0/69A840/43C410，44 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_637920(int *this)
{
  void *v2; // eax
  int v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0xE4u);
  if ( v2 != nullptr )
    v3 = sub_43C060((int)v2, 12, 112);
  else
    v3 = 0;
  *(this + 10) = v3;
  dword_9D3BD8 = dword_99FCCC;
  sub_69A5F0((uint32_t *)*(this + 10), 49, 40);
  sub_69A840(*(this + 10));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 9), 23, 24, 25, 23, 0, 0);
  else
    v5 = nullptr;
  *(this + 11) = (int)v5;
  sub_69A5F0(v5, 147, 11);
  sub_69A840(*(this + 11));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(this + 9), 65, 66, 67, 65, 0, 0);
  else
    v7 = nullptr;
  *(this + 12) = (int)v7;
  sub_69A5F0(v7, 59, 60);
  sub_69A840(*(this + 12));
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 13, 6);
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 28))(this, 3);
}



// ------------------------------------------------------------
// 0x637A80 sub_637A80 —— 好友/成员窗数据（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_637A80(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x637AA0 CNRDMemberAddRemoveWindow__vmt8 —— CNRDMemberAddRemoveWindow__vmt8 提交（545510 名字输入 + 69B740 + 44E8D0 + CLICK_BUTTON2）
// ------------------------------------------------------------
int /*thiscall*/ CNRDMemberAddRemoveWindow__vmt8(void *this)
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  char v6; // cl
  char *v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax

  if ( (uint8_t)sub_545510(4) == 0 )
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
  sub_69A650(*((uint32_t *)this + 2));
  v3 = *((uint32_t *)this + 2);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    dword_79BE4C = *(uint32_t *)(*((uint32_t *)this + 10) + 12);
    dword_79BE54 = dword_79BE4C;
  }
  v4 = *((uint32_t *)this + 12);
  if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12)
    || (v5 = *((uint32_t *)this + 10), v6 = *(uint8_t *)(v5 + 116), *(uint8_t *)(v5 + 116) = 0, v6 != 0) )
  {
    if ( strlen((const char *)sub_69B740(*((uint32_t *)this + 10))) != 0 )
    {
      if ( *((uint32_t *)this + 13) != 0 )
      {
        v10 = sub_69B740(*((uint32_t *)this + 10));
        sub_44E8D0(*((char **)this + 4), (void *)0x38, v10, 0);
      }
      else
      {
        v8 = *(uint32_t *)dword_8F8518;
        v9 = sub_69B740(*((uint32_t *)this + 10));
        (*(void (/*thiscall*/ **)(int, int))(v8 + 4))(dword_8F8518, v9);
      }
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
    }
    else
    {
      v7 = sub_422E70(1120);
      sub_44E8D0(*((char **)this + 4), (void *)0x1B, (int)v7, 0);
    }
  }
  v11 = *((uint32_t *)this + 12);
  if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  v12 = *((uint32_t *)this + 11);
  if ( *(uint8_t *)(v12 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v12 + 12) )
  {
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  CNCommandChecker__vmt40(0, 0);
  result = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)this + 4) + 28) + 136);
  *(uint8_t *)(result + 17) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x637C10 CNRDFriendAddRemoveWindow__vmtC —— CNRDFriendAddRemoveWindow__vmtC 打开槽（69A5F0 + 43B920 + 69BCC0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDFriendAddRemoveWindow__vmtC(uint32_t *this, int a2, int a3)
{
  uint32_t *v4; // edi
  unsigned int v5; // ecx
  unsigned int v6; // eax
  unsigned int v7; // ecx

  *(this + 13) = a3;
  v4 = (uint32_t *)*(this + 2);
  v5 = v4[7];
  v6 = (int)(pt.x - (v5 >> 1)) <= 0 ? 0 : pt.x - (v5 >> 1);
  if ( v6 >= 640 - v5 )
    v6 = 640 - v5;
  v7 = 480 - v4[8];
  if ( (pt.y - (v4[8] >> 1) <= 0 ? 0 : pt.y - (v4[8] >> 1)) < v7 )
    v7 = pt.y - (v4[8] >> 1) <= 0 ? 0 : pt.y - (v4[8] >> 1);
  sub_69A5F0(v4, v6, v7);
  sub_43B920(*(uint32_t *)(*(this + 4) + 28), 0);
  sub_69BCC0(*(this + 10));
  dword_79BE4C = *(uint32_t *)(*(this + 10) + 12);
  dword_79BE54 = dword_79BE4C;
  return 1;
}



// ------------------------------------------------------------
// 0x637CB0 CNRDMemberAddRemoveWindow__vmt0 —— CNRDMemberAddRemoveWindow__vmt0 构造（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDMemberAddRemoveWindow__vmt0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // eax

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 2) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    v6 = sub_418DD0(156);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4 + 8, v5 + 8, dword_79C0B0);
    v7 = sub_418DD0(175 - (*(this + 13) != 0));
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v4 + 64, v5 + 13, dword_79C0B0);
    result = sub_418DD0(157);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(
               result,
               v4 + 8,
               v5 + 36,
               dword_79C0B0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x637D60 sub_637D60 —— 成员窗页绘制（43C060/69A5F0/69A840/43C410，44 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_637D60(int *this)
{
  void *v2; // eax
  int v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0xE4u);
  if ( v2 != nullptr )
    v3 = sub_43C060((int)v2, 12, 112);
  else
    v3 = 0;
  *(this + 10) = v3;
  dword_9D3BD8 = dword_99FCCC;
  sub_69A5F0((uint32_t *)*(this + 10), 49, 40);
  sub_69A840(*(this + 10));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 9), 23, 24, 25, 23, 0, 0);
  else
    v5 = nullptr;
  *(this + 11) = (int)v5;
  sub_69A5F0(v5, 147, 11);
  sub_69A840(*(this + 11));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(this + 9), 65, 66, 67, 65, 0, 0);
  else
    v7 = nullptr;
  *(this + 12) = (int)v7;
  sub_69A5F0(v7, 59, 60);
  sub_69A840(*(this + 12));
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 13, 6);
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 28))(this, 3);
}



// ------------------------------------------------------------
// 0x637EC0 CNRDFriendRemoveConfirmWindow__vmt8 —— CNRDFriendRemoveConfirmWindow__vmt8 确认移除（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDFriendRemoveConfirmWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 9);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    if ( *(this + 17) < 0x10u )
      v3 = this + 12;
    else
      v3 = (uint32_t *)*(this + 12);
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F8510 + 8))(dword_8F8510, v3);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = (uint8_t *)*(this + 10);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x637F50 sub_637F50 —— 好友移除清理（69C3C0 + 43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_637F50(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);
  sub_69C3C0(1);
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



// ------------------------------------------------------------
// 0x638040 CNRDFriendRemoveConfirmWindow__vmtC —— CNRDFriendRemoveConfirmWindow__vmtC 文案装配（479290 好友查询 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDFriendRemoveConfirmWindow__vmtC(char *this, void *Src, int a3)
{
  const char *v4; // eax
  char *v5; // eax
  char *v7; // edi
  char *v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // edi
  uint32_t *v14; // ecx
  int v15; // ebx

  sub_4015C0(Src, strlen((const char *)Src));
  if ( *((uint32_t *)this + 17) < 0x10u )
    v4 = this + 48;
  else
    v4 = *((const char **)this + 12);
  if ( sub_479290((uint32_t *)dword_8F8510, v4) == -1 )
  {
    v5 = sub_422E70(937);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v5, 0);
    return 0;
  }
  else
  {
    sub_69C340(-1);
    sub_69C440(-1);
    if ( *((uint32_t *)this + 17) < 0x10u )
      v7 = this + 48;
    else
      v7 = *((char **)this + 12);
    sub_69C360(v7, 0);
    v8 = sub_422E70(938);
    sub_69C360(v8, 0);
    v9 = *(uint32_t *)this;
    v10 = sub_69C500(*((uint32_t *)this + 3));
    (*(void (/*thiscall*/ **)(char *, int, int))(v9 + 24))(this, 14, v10 + 5);
    v11 = *((uint32_t *)this + 2);
    v12 = pt.y - *(uint32_t *)(v11 + 32) + 31;
    if ( (pt.x - 125 <= 0 ? 0 : pt.x - 125) >= 640 - *(uint32_t *)(v11 + 28) )
      v13 = 640 - *(uint32_t *)(*((uint32_t *)this + 2) + 28);
    else
      v13 = pt.x - 125 <= 0 ? 0 : pt.x - 125;
    v14 = *((uint32_t **)this + 2);
    v15 = v12 <= 0 ? 0 : v12;
    if ( v15 >= 480 - v14[8] )
      v15 = 480 - v14[8];
    sub_69A5F0(v14, v13, v15);
    sub_69A5F0(*((uint32_t **)this + 9), v13 + 29, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v15 - 43);
    sub_69A5F0(*((uint32_t **)this + 10), v13 + 98, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v15 - 43);
    return 1;
  }
}



// ============================================================
// 【分区 19】疲劳恢复确认 CNRDStaminaRecoverConfirmWindow（0x6381B0-0x6386E0）
// ============================================================
// ------------------------------------------------------------
// 0x6381B0 CNRDStaminaRecoverConfirmWindow__vmt8 —— CNRDStaminaRecoverConfirmWindow__vmt8 确认恢复（423200/423380 参数 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDStaminaRecoverConfirmWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax
  int v3; // eax

  sub_69A650(*(this + 2));
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1064))(dword_8F7C04) == 100 )
    return (uint8_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
  v3 = *(this + 10);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    sub_423200(dword_8F7B08, 9);
    sub_423380(dword_8F7B08);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x638250 CNRDStaminaRecoverConfirmWindow__vmtC —— CNRDStaminaRecoverConfirmWindow__vmtC 文案装配（422E70/44E8D0 + 69A5F0 + 69C340/69C360）
// ------------------------------------------------------------
char /*thiscall*/ CNRDStaminaRecoverConfirmWindow__vmtC(uint32_t **this, int a2, int a3)
{
  char *v4; // eax
  char *v6; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1064))(dword_8F7C04) == 100 )
  {
    v4 = sub_422E70(1156);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v4, 0);
    return 0;
  }
  else
  {
    sub_69A5F0(*(this + 2), (640 - (*(this + 2))[7]) / 2, (480 - (*(this + 2))[8]) / 2);
    sub_69C340(-1);
    v6 = sub_422E70(1157);
    sub_69C360(v6, 0);
    return 1;
  }
}



// ------------------------------------------------------------
// 0x6382E0 sub_6382E0 —— 疲劳清理（29 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6382E0(uint32_t *this, int a2, int a3)
{
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edx

  v3 = *(this + 54);
  if ( v3 != 0 )
    v4 = (*(this + 55) - v3) >> 2;
  else
    v4 = 0;
  v5 = a2;
  if ( v4 < a2 )
  {
    v6 = *(this + 54);
    if ( v6 != 0 )
      v5 = (*(this + 55) - v6) >> 2;
    else
      v5 = 0;
  }
  return *(uint32_t *)(*(this + 54) + 4 * v5 - 4) * (100 - a3) / 90;
}



// ------------------------------------------------------------
// 0x638350 CNRDStaminaRecoverConfirmWindow__vmt0 —— CNRDStaminaRecoverConfirmWindow__vmt0 构造（65 行：418DD0/422E70/429830/41A5E0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDStaminaRecoverConfirmWindow__vmt0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ebx
  char *v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // ebx
  int v16; // esi
  int v17; // eax
  char *v18; // eax
  int v19; // [esp-8h] [ebp-10h]
  int v20; // [esp+10h] [ebp+8h]

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 2) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    v20 = v5;
    v6 = sub_418DD0(172);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4 + 8, v5 + 13, dword_79C0B0);
    v7 = sub_418DD0(171);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v4 + 36, v5 + 19, dword_79C0B0);
    v8 = sub_418DD0(173);
    if ( v8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, v4 + 11, v5 + 47, dword_79C0B0);
    v9 = sub_418DD0(174);
    if ( v9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, v4 + 21, v5 + 158, dword_79C0B0);
    v10 = sub_418DD0(175);
    if ( v10 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, v4 + 11, v5 + 199, dword_79C0B0);
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);
    v11 = *(uint32_t *)dword_79C0B0;
    v12 = sub_422E70(1158);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v11 + 80))(dword_79C0B0, v4 + 67, v20 + 154, -1, v12);
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, this + 25);
    v13 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    v14 = sub_41A5E0(v13 + 53);
    v15 = *(uint32_t *)dword_79C0B0;
    v16 = v14;
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1064))(dword_8F7C04);
    v19 = sub_6382E0(byte_8F85E0, v16, v17);
    v18 = sub_422E70(1159);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *, int))(v15 + 80))(dword_79C0B0, v4, v20 + 205, -1, v18, v19);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x638520 sub_638520 —— 疲劳窗页绘制（69A5F0 + 69C440 + 43C410/69A840，73 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_638520(int *this)
{
  int v2; // edx
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  int result; // eax

  v2 = *this;
  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(116, 2048);
  sub_69A5F0((uint32_t *)*(this + 3), 88, 66);
  sub_69C440(-1);
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 18, 20);
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, *(this + 9), 21, 22, 23, 21, 0, 0);
  else
    v4 = nullptr;
  *(this + 10) = (int)v4;
  sub_69A5F0(v4, 57, 232);
  sub_69A840(*(this + 10));
  v5 = operator new(0x84u);
  if ( v5 != nullptr )
    v6 = sub_43C410(v5, *(this + 9), 24, 25, 26, 24, 0, 0);
  else
    v6 = nullptr;
  *(this + 11) = (int)v6;
  sub_69A5F0(v6, 118, 232);
  sub_69A840(*(this + 11));
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;
  *(this + 18) = 0;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 17) = 12;
  *(this + 19) = 1600;
  *(this + 16) = 6;
  *(this + 24) = dword_99FCCC;
  *(this + 19) = 150;
  *((uint8_t *)this + 100) = 0;
  *((uint8_t *)this + 101) = 0;
  *((uint8_t *)this + 102) = 0;
  *((uint8_t *)this + 103) = 0;
  *(this + 28) = 0;
  *(this + 30) = 12;
  *(this + 31) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 29) = 6;
  *(this + 32) = 1600;
  result = dword_99FCCC;
  *(this + 37) = dword_99FCCC;
  *(this + 28) = 2;
  *(this + 32) = 207;
  return result;
}



// ============================================================
// 【分区 20】商城提示窗（0x6386E0-0x638AD0）
// CNRDInformCashShopWindow 提示、CNRDCashShopDoubleEventWindow 双倍活动
// （vmt0 加载 interface/cashshop/cashshopdoubleevent.img）。
// ============================================================
// ------------------------------------------------------------
// 0x6386E0 sub_6386E0 —— 商城提示数据（13 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6386E0(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 13) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6386F0 CNRDInformCashShopWindow__vmtC —— CNRDInformCashShopWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDInformCashShopWindow__vmtC(int this, int a2, int a3)
{
  sub_69A5F0(*(uint32_t **)(this + 8), 122, 14);
  *(uint32_t *)(this + 52) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x638710 CNRDCashShopDoubleEventWindow__vmtC —— CNRDCashShopDoubleEventWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDCashShopDoubleEventWindow__vmtC(uint32_t **this, int a2, int a3)
{
  sub_69A5F0(*(this + 2), 74, 55);
  ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[6])(this, 40, 28);
  return 1;
}



// ------------------------------------------------------------
// 0x638730 CNRDInformCashShopWindow__vmt8 —— CNRDInformCashShopWindow__vmt8 Update（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDInformCashShopWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  result = (uint8_t *)*(this + 10);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x638770 CNRDInformCashShopWindow__vmt0 —— CNRDInformCashShopWindow__vmt0 构造（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDInformCashShopWindow__vmt0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // ebx
  int v5; // esi

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 9) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    result = sub_418DD0(0);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(
               result,
               v4 - 120,
               v5 - 15,
               dword_79C0B0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6387C0 CNRDCashShopDoubleEventWindow__vmt0 —— CNRDCashShopDoubleEventWindow__vmt0 构造：加载 interface/cashshop/cashshopdoubleevent.img（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopDoubleEventWindow__vmt0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // eax

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 9) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
      dword_8F84B8,
      "interface/cashshop/cashshopdoubleevent.img");
    v6 = sub_418DD0(0);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4 + 19, v5 + 25, dword_79C0B0);
    if ( GetTickCount() % 0x578 >= 0x2BC )
      result = sub_418DD0(2);
    else
      result = sub_418DD0(1);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(
               result,
               v4 + 44,
               v5 + 181,
               dword_79C0B0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x638870 sub_638870 —— 商城提示页绘制（426BD0/69A840/43C410/69A5F0，41 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_638870(int *this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  int v6; // edx
  int result; // eax

  v2 = operator new(0x68u);
  if ( v2 != nullptr )
    v3 = sub_426BD0(v2);
  else
    v3 = nullptr;
  *(this + 9) = (int)v3;
  *((uint32_t *)v3 + 17) = this;
  sub_69A840(*(this + 9));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v5 = nullptr;
  *(this + 10) = (int)v5;
  sub_69A5F0(v5, 169, 402);
  sub_69A840(*(this + 10));
  *(this + 11) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 168);
  v6 = *this;
  *(this + 12) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 132);
  result = (*(int (/*thiscall*/ **)(int *, int, int))(v6 + 24))(this, 32, 33);
  *(this + 14) = 150;
  *(this + 15) = 240;
  *(this + 16) = -60;
  *(this + 17) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x638990 sub_638990 —— 商城提示页绘制 2（426BD0/69A840/43C410/69A5F0，31 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_638990(uint32_t *this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  *(this + 9) = 0;
  v2 = operator new(0x68u);
  if ( v2 != nullptr )
    v3 = sub_426BD0(v2);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  *((uint32_t *)v3 + 17) = this;
  sub_69A840(*(this + 9));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v5 = nullptr;
  *(this + 10) = v5;
  sub_69A5F0(v5, 215, 336);
  return sub_69A840(*(this + 10));
}



// ------------------------------------------------------------
// 0x638A70 sub_638A70 —— 商城提示数据（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_638A70(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 26) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x638A90 sub_638A90 —— 商城提示数据 2（27 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_638A90(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 9) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  *(this + 11) = 0;
  return result;
}



// ============================================================
// 【分区 21】公会窗与回城确认（0x638AD0-0x6395D0）
// CNRDGuildWindow（vmtC POP_UP 事件）、CNRDGuildConfirmWindow（vmt8 111 行
// 确认流程）、CNRDMoveToHomeConfirmWindow 回城确认（vmt14 转发 541F10）。
// ============================================================
// ------------------------------------------------------------
// 0x638AD0 CNRDGuildWindow__vmt8 —— CNRDGuildWindow__vmt8 Update（423200/423380 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDGuildWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 9);
  v3 = dword_79BE34;
  if ( *(uint8_t *)(v2 + 17) == 0 || dword_79BE34 != *(uint32_t *)(v2 + 12) )
  {
    v4 = *(this + 11);
    if ( *(uint8_t *)(v4 + 17) == 0 || dword_79BE34 != *(uint32_t *)(v4 + 12) )
      goto LABEL_11;
  }
  v5 = *(this + 26);
  if ( v5 == 0 )
  {
    sub_423200(dword_8F7B08, 71);
LABEL_9:
    sub_423380(dword_8F7B08);
    goto LABEL_10;
  }
  if ( v5 == 2 )
  {
    sub_423200(dword_8F7B08, 76);
    goto LABEL_9;
  }
LABEL_10:
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  v3 = dword_79BE34;
LABEL_11:
  result = (uint8_t *)*(this + 10);
  if ( result[17] != 0 && v3 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x638B80 sub_638B80 —— 公会窗文案装配（69C340 系 + 422E70，57 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_638B80(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // ebx
  int v5; // edi
  char *v6; // eax
  int v7; // eax
  uint32_t *result; // eax

  v3 = *(this + 2);
  v4 = *(uint32_t *)(v3 + 20);
  v5 = *(uint32_t *)(v3 + 24);
  sub_69C340(-1);
  sub_69A5F0((uint32_t *)*(this + 3), v4 + 17, v5 + 58);
  switch ( a2 )
  {
    case 0:
      v6 = sub_422E70(946);
LABEL_7:
      sub_69C360(v6, 0);
      break;
    case 1:
      v6 = sub_422E70(947);
      goto LABEL_7;
    case 2:
      v6 = sub_422E70(948);
      goto LABEL_7;
    default:
      break;
  }
  v7 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 17, v7 + 8);
  if ( a2 == 0 || a2 == 2 )
  {
    *(uint8_t *)(*(this + 9) + 16) = 1;
    *(uint8_t *)(*(this + 10) + 16) = 1;
    *(uint8_t *)(*(this + 11) + 16) = 0;
    sub_69A5F0((uint32_t *)*(this + 9), v4 + 50, *(uint32_t *)(*(this + 2) + 32) + v5 - 43);
    result = sub_69A5F0((uint32_t *)*(this + 10), v4 + 113, *(uint32_t *)(*(this + 2) + 32) + v5 - 43);
    *(this + 26) = a2;
  }
  else
  {
    *(uint8_t *)(*(this + 9) + 16) = 0;
    *(uint8_t *)(*(this + 10) + 16) = 0;
    *(uint8_t *)(*(this + 11) + 16) = 1;
    result = sub_69A5F0((uint32_t *)*(this + 11), v4 + 82, *(uint32_t *)(*(this + 2) + 32) + v5 - 43);
    *(this + 26) = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x638CA0 CNRDGuildWindow__vmtC —— CNRDGuildWindow__vmtC 打开槽：POP_UP 事件（638B80 + 69A5F0 + 432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDGuildWindow__vmtC(int this, int a2, int a3)
{
  sub_638B80((uint32_t *)this, a3);
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) / 2,
    (480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) / 2);
  sub_432EA0("POP_UP", -1, 0, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x638D00 CNRDGuildWindow__vmt0 —— CNRDGuildWindow__vmt0 构造（418DD0 + 422E70）
// ------------------------------------------------------------
int /*thiscall*/ CNRDGuildWindow__vmt0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // esi
  int v5; // edi
  int v6; // eax
  int v7; // eax
  char *v8; // eax

  result = IRDPopupWindow__vmt0(a2);
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
    v7 = sub_418DD0(199);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v4 + 7, v5 + 7, dword_79C0B0);
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 13);
    if ( *(this + 26) == 2 )
      v8 = sub_422E70(944);
    else
      v8 = sub_422E70(945);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v4,
      v5 + 17,
      -1190552,
      v8);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x638DF0 sub_638DF0 —— 公会清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_638DF0(uint32_t *this)
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
    v3 = sub_43C410(v2, *(this + 12), 21, 22, 23, 21, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  sub_69A840(v3);
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 12), 24, 25, 26, 24, 0, 0);
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



// ------------------------------------------------------------
// 0x638F70 CNRDGuildConfirmWindow__vmt8 —— CNRDGuildConfirmWindow__vmt8 确认流程（111 行：69A650 + CLICK_BUTTON2）
// ------------------------------------------------------------
HRESULT /*thiscall*/ CNRDGuildConfirmWindow__vmt8(uint32_t *this)
{
  int v2; // ecx
  int v3; // eax
  const wchar_t *v4; // ecx
  HWND DesktopWindow; // eax
  HRESULT result; // eax
  OLECHAR *v7; // edi
  OLECHAR *v8; // esi
  int16_t v9; // [esp+4h] [ebp-248h] BYREF
  int v10; // [esp+6h] [ebp-246h]
  int v11; // [esp+Ah] [ebp-242h]
  int v12; // [esp+Eh] [ebp-23Eh]
  int16_t v13; // [esp+12h] [ebp-23Ah]
  int16_t v14; // [esp+14h] [ebp-238h] BYREF
  int v15; // [esp+16h] [ebp-236h]
  int v16; // [esp+1Ah] [ebp-232h]
  int v17; // [esp+1Eh] [ebp-22Eh]
  int16_t v18; // [esp+22h] [ebp-22Ah]
  VARIANTARG pvarg; // [esp+24h] [ebp-228h] BYREF
  int16_t v20; // [esp+34h] [ebp-218h] BYREF
  int v21; // [esp+36h] [ebp-216h]
  int64_t v22; // [esp+3Ah] [ebp-212h]
  int16_t v23; // [esp+42h] [ebp-20Ah]
  LPVOID ppv; // [esp+44h] [ebp-208h] BYREF
  wchar_t Buffer[256]; // [esp+48h] [ebp-204h] BYREF
  int v26; // [esp+248h] [ebp-4h]

  v2 = *(this + 2);
  v26 = dword_796E50;
  sub_69A650(v2);
  v3 = *(this + 9);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    v15 = 0;
    v10 = 0;
    v16 = 0;
    v11 = 0;
    v17 = 0;
    v12 = 0;
    v18 = 0;
    v13 = 0;
    v4 = (const wchar_t *)*(this + 11);
    v21 = 0;
    v22 = 0;
    ppv = nullptr;
    v14 = 0;
    v9 = 0;
    memset(&pvarg, 0, sizeof(pvarg));
    v20 = 0;
    v23 = 0;
    swprintf(Buffer, (const size_t)&off_73DF80, v4);
    DesktopWindow = GetDesktopWindow();
    SetForegroundWindow(DesktopWindow);
    result = CoInitialize(nullptr);
    if ( result >= 0 )
    {
      if ( CoCreateInstance(&stru_743300, nullptr, 5u, &stru_743330, &ppv) >= 0 )
      {
        v7 = SysAllocString(Buffer);
        if ( v7 != nullptr )
        {
          v8 = SysAllocString(&psz);
          if ( v8 != nullptr )
          {
            v20 = 8;
            *(uint32_t *)((char *)&v22 + 2) = v8;
            (*(void (/*stdcall*/ **)(LPVOID, OLECHAR *, int16_t *, int16_t *, VARIANTARG *, int16_t *))(*(uint32_t *)ppv + 44))(
              ppv,
              v7,
              &v14,
              &v9,
              &pvarg,
              &v20);
            (*(void (/*stdcall*/ **)(LPVOID, int))(*(uint32_t *)ppv + 104))(ppv, 990);
            (*(void (/*stdcall*/ **)(LPVOID, int))(*(uint32_t *)ppv + 112))(ppv, 570);
            (*(void (/*stdcall*/ **)(LPVOID, uint32_t))(*(uint32_t *)ppv + 196))(ppv, 0);
            (*(void (/*stdcall*/ **)(LPVOID, uint32_t))(*(uint32_t *)ppv + 188))(ppv, 0);
            (*(void (/*stdcall*/ **)(LPVOID, uint32_t))(*(uint32_t *)ppv + 172))(ppv, 0);
            (*(void (/*stdcall*/ **)(LPVOID, uint32_t))(*(uint32_t *)ppv + 280))(ppv, 0);
            (*(void (/*stdcall*/ **)(LPVOID, int))(*(uint32_t *)ppv + 164))(ppv, -1);
          }
          SysFreeString(v7);
          if ( v8 != nullptr )
            SysFreeString(v8);
        }
      }
      VariantClear(&pvarg);
      if ( ppv != nullptr )
        (*(void (/*stdcall*/ **)(LPVOID))(*(uint32_t *)ppv + 8))(ppv);
      CoUninitialize();
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    }
  }
  else
  {
    result = *(this + 10);
    if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
    {
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6391F0 CNRDGuildConfirmWindow__vmtC —— CNRDGuildConfirmWindow__vmtC 文案装配（69C340 系 + 69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDGuildConfirmWindow__vmtC(int *this, int a2, int a3)
{
  int v4; // edi
  int v5; // eax
  uint32_t *v6; // ecx
  int v7; // ebx
  int v8; // edi

  *(this + 11) = a3;
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(a2, 0);
  v4 = *this;
  v5 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(int *, int, int))(v4 + 24))(this, 14, v5 + 5);
  v6 = (uint32_t *)*(this + 2);
  v7 = pt.x - 55 <= 0 ? 0 : pt.x - 55;
  if ( v7 >= 640 - v6[7] )
    v7 = 640 - v6[7];
  v8 = 480 - v6[8];
  if ( (pt.y - v6[8] + 31 <= 0 ? 0 : pt.y - v6[8] + 31) < v8 )
    v8 = pt.y - v6[8] + 31 <= 0 ? 0 : pt.y - v6[8] + 31;
  sub_69A5F0(v6, v7, v8);
  sub_69A5F0((uint32_t *)*(this + 9), v7 + 29, *(uint32_t *)(*(this + 2) + 32) + v8 - 43);
  sub_69A5F0((uint32_t *)*(this + 10), v7 + 98, *(uint32_t *)(*(this + 2) + 32) + v8 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x6392D0 sub_6392D0 —— 公会确认清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_6392D0(uint32_t *this)
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



// ------------------------------------------------------------
// 0x6393B0 CNRDMoveToHomeConfirmWindow__vmt8 —— CNRDMoveToHomeConfirmWindow__vmt8 确认回城（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDMoveToHomeConfirmWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 9);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 20))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = (uint8_t *)*(this + 10);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x639420 CNRDMoveToHomeConfirmWindow__vmtC —— CNRDMoveToHomeConfirmWindow__vmtC 文案装配（69C340 系 + 69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDMoveToHomeConfirmWindow__vmtC(int *this, int a2, int a3)
{
  int v4; // edi
  int v5; // eax
  uint32_t *v6; // ecx
  int v7; // ebx
  int v8; // edi

  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(a2, 0);
  v4 = *this;
  v5 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(int *, int, int))(v4 + 24))(this, 14, v5 + 5);
  v6 = (uint32_t *)*(this + 2);
  v7 = (480 - v6[8]) / 2;
  v8 = (640 - v6[7]) / 2;
  sub_69A5F0(v6, v8, v7);
  sub_69A5F0((uint32_t *)*(this + 9), v8 + 29, *(uint32_t *)(*(this + 2) + 32) + v7 - 43);
  sub_69A5F0((uint32_t *)*(this + 10), v8 + 98, *(uint32_t *)(*(this + 2) + 32) + v7 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x6394D0 CNRDMoveToHomeConfirmWindow__vmt14 —— CNRDMoveToHomeConfirmWindow__vmt14 关闭槽（转发 541F10 trade_shop 参数写入）
// ------------------------------------------------------------
char /*thiscall*/ CNRDMoveToHomeConfirmWindow__vmt14(void *this)
{
  sub_541F10();
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x6394F0 sub_6394F0 —— 回城清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_6394F0(uint32_t *this)
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
// 【分区 22】摆摊购买确认与成员移除（0x6395D0-0x63A030）
// CNRDPrivateStoreItemBuyConfirmWindow（vmtC 115 行，541A30/541B20 摊位
// 条目 + 4F36B0 下单）；CNRDMemberRemoveConfirmWindow/CNRDResponseMemberWindow
// （vmt38/3C=接受/拒绝成员动作）。
// ============================================================
// ------------------------------------------------------------
// 0x6395D0 CNRDPrivateStoreItemBuyConfirmWindow__vmt14 —— CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买（541A30/541B20 摊位条目 + 422E70/44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreItemBuyConfirmWindow__vmt14(int *this)
{
  int v2; // esi
  int v3; // eax
  int v4; // eax
  int *v5; // esi
  int v6; // ebx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  char *v11; // eax
  int v12; // [esp+8h] [ebp-4h]

  v2 = *(this + 13);
  v3 = sub_541A30();
  v4 = sub_541B20(v3);
  if ( v2 < *(uint32_t *)(v4 + 8) )
  {
    v5 = *(int **)(*(uint32_t *)(v4 + 12) + 4 * v2);
    if ( v5 != nullptr && (*(int (/*thiscall*/ **)(int *))(*v5 + 44))(v5) >= (unsigned int)*(this + 12) )
    {
      v6 = *v5;
      v12 = 1;
      v7 = (*(int (/*thiscall*/ **)(int *))(*v5 + 16))(v5);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, uint32_t))(v6 + 60))(v5, *(uint32_t *)(v7 + 4)) != 0 )
      {
        v8 = *(this + 12);
      }
      else
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v5 + 20))(v5, 2) == 0 )
        {
LABEL_9:
          v9 = sub_541A30();
          (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v9 + 80))(v9, *(this + 13), v12);
          (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
          return 1;
        }
        v8 = *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 188))(v5);
      }
      v12 = v8;
      goto LABEL_9;
    }
  }
  v11 = sub_422E70(1353);
  sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v11, 0);
  (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x639690 sub_639690 —— 摆摊购买清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_639690(uint32_t *this)
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
// 0x639770 CNRDPrivateStoreItemBuyConfirmWindow__vmtC —— CNRDPrivateStoreItemBuyConfirmWindow__vmtC 文案装配（115 行：541A30/541B20 + 4F36B0 下单 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreItemBuyConfirmWindow__vmtC(unsigned int *this, unsigned int **a2, unsigned int a3)
{
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int64_t v7; // rcx
  int v8; // edi
  unsigned int v9; // ecx
  char *v10; // eax
  char *v11; // eax
  int v12; // eax
  char *v13; // eax
  char *v14; // eax
  char *v15; // eax
  void **v16; // eax
  unsigned int v17; // edi
  int v18; // eax
  uint32_t *v19; // ecx
  int v20; // ebx
  int v21; // edi
  unsigned int v23; // [esp-8h] [ebp-15Ch]
  int v24; // [esp-8h] [ebp-15Ch]
  int v25; // [esp-4h] [ebp-158h]
  char Buffer[256]; // [esp+Ch] [ebp-148h] BYREF
  uint8_t v27[4]; // [esp+10Ch] [ebp-48h] BYREF
  void *Block; // [esp+110h] [ebp-44h]
  int v29; // [esp+120h] [ebp-34h]
  unsigned int v30; // [esp+124h] [ebp-30h]
  uint8_t v31[4]; // [esp+128h] [ebp-2Ch] BYREF
  void *v32[5]; // [esp+12Ch] [ebp-28h] BYREF
  unsigned int v33; // [esp+140h] [ebp-14h]
  int v34; // [esp+144h] [ebp-10h]
  int v35; // [esp+150h] [ebp-4h]

  v34 = dword_796E50;
  *(this + 13) = **a2;
  v7 = *a2[1];
  *(this + 12) = v7;
  *(this + 11) = a3;
  v33 = 15;
  v32[4] = nullptr;
  LOBYTE(v32[0]) = 0;
  sub_4015C0((void *)szPassword, 0);
  v4 = *(this + 13);
  v35 = HIDWORD(v7);
  v5 = sub_541A30();
  v6 = sub_541B20(v5);
  if ( v4 >= *(uint32_t *)(v6 + 8) )
    return 0;
  v8 = *(uint32_t *)(*(uint32_t *)(v6 + 12) + 4 * v4);
  if ( v8 == HIDWORD(v7) )
    return 0;
  v9 = *(this + 12);
  v23 = *(this + 11);
  if ( !is_mul_ok(v9, v23) || v9 * v23 > 0x7FFFFFFF )
  {
    v10 = sub_422E70(1354);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v10, 0);
    return 0;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 20))(v8, 2) != 0 && *(this + 12) == 1 )
  {
    v11 = (char *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 108))(v8);
  }
  else
  {
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 108))(v8);
    v25 = *(this + 12);
    v24 = v12;
    v13 = sub_422E70(949);
    sprintf(Buffer, v13, v24, v25);
    v11 = Buffer;
  }
  sub_4022F0((std::_String_base *)v31, v11, strlen(v11));
  v14 = sub_422E70(950);
  sub_4022F0((std::_String_base *)v31, v14, strlen(v14));
  sub_4F36B0(v27, *(this + 11) * *(this + 12), 0, 0, 0);
  LOBYTE(v35) = 1;
  sub_4021F0((std::_String_base *)v31, v27, 0, -1);
  v15 = sub_422E70(951);
  sub_4022F0((std::_String_base *)v31, v15, strlen(v15));
  sub_69C340(-1);
  sub_69C440(-1);
  v16 = (void **)v32[0];
  if ( v33 < 0x10 )
    v16 = v32;
  sub_69C360(v16, 0);
  v17 = *this;
  v18 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(unsigned int *, int, int))(v17 + 24))(this, 14, v18 + 5);
  v19 = (uint32_t *)*(this + 2);
  v20 = pt.x - 55 <= 0 ? 0 : pt.x - 55;
  if ( v20 >= 640 - v19[7] )
    v20 = 640 - v19[7];
  v21 = 480 - v19[8];
  if ( (pt.y - v19[8] + 31 <= 0 ? 0 : pt.y - v19[8] + 31) < v21 )
    v21 = pt.y - v19[8] + 31 <= 0 ? 0 : pt.y - v19[8] + 31;
  sub_69A5F0(v19, v20, v21);
  sub_69A5F0((uint32_t *)*(this + 9), v20 + 29, *(uint32_t *)(*(this + 2) + 32) + v21 - 43);
  sub_69A5F0((uint32_t *)*(this + 10), v20 + 98, *(uint32_t *)(*(this + 2) + 32) + v21 - 43);
  if ( v30 >= 0x10 )
    j__free(Block);
  v30 = 15;
  v29 = 0;
  LOBYTE(Block) = 0;
  if ( v33 >= 0x10 )
    j__free(v32[0]);
  return 1;
}



// ------------------------------------------------------------
// 0x639A50 CNRDMemberRemoveConfirmWindow__vmt8 —— CNRDMemberRemoveConfirmWindow__vmt8 确认移除（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDMemberRemoveConfirmWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 9);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    if ( *(this + 17) < 0x10u )
      v3 = this + 12;
    else
      v3 = (uint32_t *)*(this + 12);
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F8518 + 8))(dword_8F8518, v3);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = (uint8_t *)*(this + 10);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x639AE0 sub_639AE0 —— 成员移除清理（69C3C0 + 43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_639AE0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);
  sub_69C3C0(1);
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



// ------------------------------------------------------------
// 0x639BD0 sub_639BD0 —— 成员移除数据（4015C0）
// ------------------------------------------------------------
int /*thiscall*/ sub_639BD0(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  return sub_4015C0((void *)szPassword, 0);
}



// ------------------------------------------------------------
// 0x639BF0 CNRDMemberRemoveConfirmWindow__vmtC —— CNRDMemberRemoveConfirmWindow__vmtC 文案装配（69C340 系 + 422E70）
// ------------------------------------------------------------
char /*thiscall*/ CNRDMemberRemoveConfirmWindow__vmtC(char *this, void *Src, int a3)
{
  char *v4; // edi
  char *v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // edi
  uint32_t *v11; // ecx
  int v12; // ebx

  sub_4015C0(Src, strlen((const char *)Src));
  sub_69C340(-1);
  sub_69C440(-1);
  if ( *((uint32_t *)this + 17) < 0x10u )
    v4 = this + 48;
  else
    v4 = *((char **)this + 12);
  sub_69C360(v4, 0);
  v5 = sub_422E70(1500);
  sub_69C360(v5, 0);
  v6 = *(uint32_t *)this;
  v7 = sub_69C500(*((uint32_t *)this + 3));
  (*(void (/*thiscall*/ **)(char *, int, int))(v6 + 24))(this, 14, v7 + 5);
  v8 = *((uint32_t *)this + 2);
  v9 = pt.y - *(uint32_t *)(v8 + 32) + 31;
  if ( (pt.x - 125 <= 0 ? 0 : pt.x - 125) >= 640 - *(uint32_t *)(v8 + 28) )
    v10 = 640 - *(uint32_t *)(*((uint32_t *)this + 2) + 28);
  else
    v10 = pt.x - 125 <= 0 ? 0 : pt.x - 125;
  v11 = *((uint32_t **)this + 2);
  v12 = v9 <= 0 ? 0 : v9;
  if ( v12 >= 480 - v11[8] )
    v12 = 480 - v11[8];
  sub_69A5F0(v11, v10, v12);
  sub_69A5F0(*((uint32_t **)this + 9), v10 + 29, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v12 - 43);
  sub_69A5F0(*((uint32_t **)this + 10), v10 + 98, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v12 - 43);
  return 1;
}



// ------------------------------------------------------------
// 0x639D20 CNRDResponseMemberWindow__vmtC —— CNRDResponseMemberWindow__vmtC 文案装配（69C340 系 + 698F90）
// ------------------------------------------------------------
char /*thiscall*/ CNRDResponseMemberWindow__vmtC(uint32_t *this, int a2, int a3)
{
  char *v5; // eax
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // ecx
  unsigned int v9; // ebx
  unsigned int v10; // edi
  char Buffer[256]; // [esp+4h] [ebp-104h] BYREF
  int v12; // [esp+104h] [ebp-4h]

  v12 = dword_796E50;
  if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
    return 0;
  v5 = sub_422E70(1512);
  sprintf(Buffer, v5, a3, a2);
  sub_69C340(-1);
  sub_69C440(-1);
  sub_69C360(Buffer, 0);
  v6 = *this;
  v7 = sub_69C500(*(this + 3));
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v6 + 24))(this, 14, v7 + 5);
  v8 = (uint32_t *)*(this + 2);
  v9 = (unsigned int)(480 - v8[8]) >> 1;
  v10 = (unsigned int)(640 - v8[7]) >> 1;
  sub_69A5F0(v8, v10, v9);
  sub_69A5F0((uint32_t *)*(this + 9), v10 + 29, *(uint32_t *)(*(this + 2) + 32) + v9 - 43);
  sub_69A5F0((uint32_t *)*(this + 10), v10 + 98, *(uint32_t *)(*(this + 2) + 32) + v9 - 43);
  *((uint8_t *)this + 57) = 0;
  *((uint8_t *)this + 58) = 0;
  sub_698F90((int)(this + 11), 5000, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x639E30 CNRDResponseMemberWindow__vmt38 —— CNRDResponseMemberWindow__vmt38 接受成员动作（423200 系参数）
// ------------------------------------------------------------
int /*thiscall*/ CNRDResponseMemberWindow__vmt38(void *this)
{
  void *v2; // [esp+0h] [ebp-4h] BYREF

  v2 = this;
  sub_423200(dword_8F7B08, 80);
  LOBYTE(v2) = 1;
  sub_423290(dword_8F7B08, (int)&v2, 1);
  return sub_423380(dword_8F7B08);
}



// ------------------------------------------------------------
// 0x639E70 CNRDResponseMemberWindow__vmt3C —— CNRDResponseMemberWindow__vmt3C 拒绝成员动作（423200 系参数）
// ------------------------------------------------------------
int /*thiscall*/ CNRDResponseMemberWindow__vmt3C(void *this)
{
  void *v2; // [esp+0h] [ebp-4h] BYREF

  v2 = this;
  sub_423200(dword_8F7B08, 80);
  LOBYTE(v2) = 2;
  sub_423290(dword_8F7B08, (int)&v2, 1);
  return sub_423380(dword_8F7B08);
}



// ------------------------------------------------------------
// 0x639EB0 CNRDResponseMemberWindow__vmt8 —— CNRDResponseMemberWindow__vmt8 Update（CLICK_BUTTON2 + 699000）
// ------------------------------------------------------------
int /*thiscall*/ CNRDResponseMemberWindow__vmt8(int *this)
{
  int v2; // edi
  int result; // eax
  int v4; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 17);
  if ( sub_699000((int)(this + 11)) < v2 )
  {
    v4 = *(this + 9);
    if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
    {
      (*(void (/*thiscall*/ **)(int *))(*this + 56))(this);
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
    }
    else
    {
      result = *(this + 10);
      if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
      {
        (*(void (/*thiscall*/ **)(int *))(*this + 60))(this);
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
      }
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 60))(this);
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x639F50 sub_639F50 —— 成员响应清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_639F50(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 21, 22, 23, 21, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  sub_69A840(v3);
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 24, 25, 26, 24, 0, 0);
  else
    v5 = nullptr;
  *(this + 10) = v5;
  return sub_69A840(v5);
}



// ============================================================
// 【分区 23】强化确认/结果窗（0x63A030-0x63B070）
// CNRDUpgradeConfirmWindow（vmt8 确认：54D470 工具窗联动）；
// CNRDUpgradeResultWindow vmtC（0x63AC20）播放强化结果事件：
// EQUIP_BROKEN/STRENGTHEN_SUCCESS/STRENGTHEN_FAIL/STRENGTHEN_ZERO
// （54D0C0 工具窗动画切换复用）。
// ============================================================
// ------------------------------------------------------------
// 0x63A030 sub_63A030 —— 强化确认数据（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63A030(int this)
{
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint8_t *)(this + 104) = 0;
  *(uint32_t *)(this + 100) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x63A050 CNRDUpgradeConfirmWindow__vmt8 —— CNRDUpgradeConfirmWindow__vmt8 确认强化（484ED0/422E70/44E8D0 + 54D470 工具窗联动 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDUpgradeConfirmWindow__vmt8(int *this)
{
  int v2; // eax
  int v3; // eax
  char *v4; // eax
  char *v5; // eax
  int v6; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 10);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    v3 = sub_484ED0(*(this + 25));
    if ( *(uint32_t *)(*(this + 4) + 104) == 10 )
    {
      if ( v3 == -1 )
      {
        v5 = sub_422E70(1658);
        sub_44E8D0((char *)*(this + 4), (void *)0x1B, (int)v5, 0);
        (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
      }
      else
      {
        sub_54D470(*(this + 25));
      }
    }
    else
    {
      v4 = sub_422E70(1657);
      sub_44E8D0((char *)*(this + 4), (void *)0x1B, (int)v4, 0);
      (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
    }
    v6 = *this;
    *(this + 25) = 0;
    (*(void (/*thiscall*/ **)(int *))(v6 + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63A140 CNRDUpgradeConfirmWindow__vmt0 —— CNRDUpgradeConfirmWindow__vmt0 构造（165 行：554930 + 484ED0/40FC80 + 4F9F40/43B560 + 4F33A0/4F2CE0/4F2D60/4F2DF0）
// ------------------------------------------------------------
void */*thiscall*/ sub_63A140(uint32_t *this, int a2)
{
  void *result; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // ebx
  int *v10; // ecx
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int *v15; // ecx
  int v16; // edx
  int *v17; // eax
  int v18; // ebx
  int v19; // eax
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int v24; // edx
  const char *v25; // eax
  int v26; // eax
  int v27; // eax
  const char *v28; // eax
  int v29; // esi
  int v30; // eax
  int v31; // eax
  int v32; // [esp-8h] [ebp-8Ch]
  int v33; // [esp-8h] [ebp-8Ch]
  int v34; // [esp-4h] [ebp-88h]
  int v35; // [esp-4h] [ebp-88h]
  uint32_t v36[7]; // [esp+Ch] [ebp-78h] BYREF
  char v37; // [esp+28h] [ebp-5Ch]
  int v38; // [esp+2Ch] [ebp-58h]
  int v39; // [esp+30h] [ebp-54h]
  int v40; // [esp+34h] [ebp-50h]
  int v41; // [esp+38h] [ebp-4Ch]
  uint32_t *v42; // [esp+3Ch] [ebp-48h]
  char Buffer[64]; // [esp+40h] [ebp-44h] BYREF
  int v44; // [esp+80h] [ebp-4h]
  int v45; // [esp+8Ch] [ebp+8h]
  int v46; // [esp+8Ch] [ebp+8h]

  v44 = dword_796E50;
  memset(v36, 0, 12);
  v36[6] = 0;
  v37 = 0;
  v38 = 0;
  v39 = 0;
  v40 = 0;
  result = (void *)sub_554930(a2);
  if ( a2 == *(this + 2) )
  {
    result = dword_8F8528;
    if ( *((uint32_t *)dword_8F8528 + 26) == 10 )
    {
      if ( *(this + 25) != 0 )
      {
        v4 = *(uint32_t *)(a2 + 20);
        v5 = *(uint32_t *)(a2 + 24);
        v45 = v4;
        v6 = sub_418DD0(90);
        if ( v6 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
            v6,
            v4 + 12,
            v5 + 9,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            872415231,
            1333788672,
            1333788672);
        if ( sub_484ED0(*(this + 25)) == -1 )
        {
          v7 = *this;
          *(this + 25) = 0;
          return (void *)(*(int (/*thiscall*/ **)(uint32_t *))(v7 + 32))(this);
        }
        else
        {
          if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 16))(*(this + 25)) + 68) != 0 )
          {
            v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 16))(*(this + 25));
            sub_40FC80(v4 + 13, v5 + 10, *(uint32_t *)(v8 + 68));
          }
          v9 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 108))(*(this + 25));
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);
          v10 = (int *)*(this + 25);
          v11 = *v10;
          v42 = *(uint32_t **)dword_79C0B0;
          v12 = (*(int (/*thiscall*/ **)(int *, int))(v11 + 24))(v10, v9);
          v41 = v45 + 43;
          ((void (/*cdecl*/ *)(int, int, int, int))v42[20])(dword_79C0B0, v45 + 43, v5 + 20, v12);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
          v13 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 188))(*(this + 25));
          v14 = sub_41A5E0(v13 + 4);
          v15 = (int *)*(this + 25);
          v16 = *v15;
          v42 = (uint32_t *)v14;
          v17 = (int *)(*(int (/*thiscall*/ **)(int *))(v16 + 172))(v15);
          v18 = *(this + 25);
          v32 = *v17;
          v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 16))(v18);
          v20 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v18 + 16))(v18, *(uint8_t *)(v19 + 24));
          result = (void *)sub_4F9F40(v36, *(uint8_t *)(v20 + 84), v42, v32, this + 12);
          if ( (uint8_t)result != 0 )
          {
            v21 = v45 + 12;
            v22 = sub_418DD0(90);
            sub_43B560(v45 + 12, v5 + 87, v22, 1065353216, 1065353216, 0, 872415231, 1333788672, 1333788672);
            v46 = v45 + 13;
            v23 = sub_418DD0(203);
            sub_40FC80(v46, v5 + 88, v23);
            v24 = *(uint32_t *)dword_79C0B0;
            v42 = this + 12;
            (*(void (/*thiscall*/ **)(int, uint32_t *))(v24 + 72))(dword_79C0B0, this + 12);
            v34 = v40;
            v25 = (const char *)sub_422E70(180);
            sprintf(Buffer, v25, v34);
            (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
              dword_79C0B0,
              v41,
              v5 + 98,
              -1,
              Buffer);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
            v26 = sub_418DD0(90);
            sub_43B560(v21, v5 + 126, v26, 1065353216, 1065353216, 0, 872415231, 1333788672, 1333788672);
            if ( sub_4F33A0(v38) != 0 )
            {
              v27 = sub_4F33A0(v38);
              sub_40FC80(v46, v5 + 127, v27);
            }
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v42);
            v35 = v39;
            v33 = sub_4F2CE0(v38);
            v28 = (const char *)sub_422E70(1655);
            sprintf(Buffer, v28, v33, v35);
            v29 = *(uint32_t *)dword_79C0B0;
            v30 = sub_4F2D60(v38);
            v31 = sub_4F2DF0(v30);
            (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v29 + 80))(dword_79C0B0, v41, v5 + 137, v31, Buffer);
            return (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
          }
        }
      }
    }
    else
    {
      return (void *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x63A4C0 CNRDUpgradeConfirmWindow__vmtC —— CNRDUpgradeConfirmWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDUpgradeConfirmWindow__vmtC(int this, int a2, int a3)
{
  *(uint32_t *)(this + 100) = a2;
  *(uint8_t *)(this + 104) = a3 == 1;
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (unsigned int)(640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) >> 1,
    (unsigned int)(480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) >> 1);
  return 1;
}



// ------------------------------------------------------------
// 0x63A500 CNRDUpgradeConfirmWindow__vmt10 —— CNRDUpgradeConfirmWindow__vmt10 状态切换槽（44ABE0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDUpgradeConfirmWindow__vmt10(uint8_t *this)
{
  int result; // eax

  if ( *(this + 104) == 1 )
    return sub_44ABE0(dword_8F8528, 18);
  return result;
}



// ------------------------------------------------------------
// 0x63A520 sub_63A520 —— 强化确认页绘制（69C3C0/69A5F0/69C340/69C440 + 422E70 + 43C410/69A840，63 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63A520(uint32_t *this)
{
  int v2; // edx
  char *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  int v8; // edx

  v2 = *this;
  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(192, 2048);
  sub_69C3C0(1);
  sub_69A5F0((uint32_t *)*(this + 3), 18, 51);
  sub_69C340(-1);
  sub_69C440(-1);
  v3 = sub_422E70(1650);
  sub_69C360(v3, 0);
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 9), 9, 10, 11, 9, 0, 0);
  else
    v5 = nullptr;
  *(this + 10) = v5;
  sub_69A5F0(v5, 56, 167);
  sub_69A840(*(this + 10));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(this + 9), 12, 13, 14, 12, 0, 0);
  else
    v7 = nullptr;
  *(this + 11) = v7;
  sub_69A5F0(v7, 119, 167);
  sub_69A840(*(this + 11));
  sub_69A5F0((uint32_t *)*(this + 2), 61, 242);
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;
  *(this + 16) = 6;
  *(this + 17) = 12;
  *(this + 18) = 0;
  *(this + 19) = 1600;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  v8 = *this;
  *(this + 24) = dword_99FCCC;
  *(this + 19) = 173;
  *(this + 15) = 1;
  *(this + 13) = -16777216;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v8 + 24))(this, 18, 15);
}



// ------------------------------------------------------------
// 0x63A6D0 sub_63A6D0 —— 强化结果清理（13 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63A6D0(int this)
{
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint8_t *)(this + 36) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x63A6E0 sub_63A6E0 —— 强化结果数据（17 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63A6E0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 11) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x63A700 CNRDUpgradeResultWindow__vmt8 —— CNRDUpgradeResultWindow__vmt8 Update（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDUpgradeResultWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63A740 sub_63A740 —— 强化结果页绘制（69A5F0，31 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_63A740(uint32_t *this)
{
  int v2; // edi
  int v3; // eax

  if ( *((uint8_t *)this + 36) == 3 )
  {
    if ( dword_9B9468 != nullptr )
      v2 = (dword_9B946C - (int)dword_9B9468) >> 3;
    else
      v2 = 0;
    v3 = *this;
    *(this + 25) = 0;
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v3 + 24))(this, 18, 3 * v2 + 5);
    return sub_69A5F0(
             (uint32_t *)*(this + 11),
             *(uint32_t *)(*(this + 2) + 20) + 88,
             *(uint32_t *)(*(this + 2) + 24) + 39 * (v2 + 1));
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 18, 8);
    return sub_69A5F0((uint32_t *)*(this + 11), *(uint32_t *)(*(this + 2) + 20) + 88, *(uint32_t *)(*(this + 2) + 24) + 78);
  }
}



// ------------------------------------------------------------
// 0x63A7C0 sub_63A7C0 —— 强化结果公共件（30 行）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_63A7C0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *v4; // edx

  result = a2;
  if ( a2 != nullptr )
  {
    v4 = a2;
    result = a1;
    do
    {
      if ( result != nullptr )
      {
        *result = *a3;
        result[1] = a3[1];
      }
      result += 2;
      v4 = (uint32_t *)((char *)v4 - 1);
    }
    while ( v4 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x63A7F0 CNRDUpgradeResultWindow__vmt0 —— CNRDUpgradeResultWindow__vmt0 构造（144 行：554930 + 63A740 + 4F33A0/4F2CE0/4F2D60/4F2DF0 + 484ED0/40FC80）
// ------------------------------------------------------------
void */*userpurge*/ sub_63A7F0@<eax>(int *a1@<ecx>, int a2@<edi>, int a3)
{
  void *result; // eax
  char v5; // al
  int v6; // edi
  int v7; // ebx
  unsigned int v8; // eax
  bool v9; // zf
  int v10; // eax
  unsigned int v11; // ecx
  int i; // ebx
  int v13; // edi
  int v14; // eax
  int v15; // eax
  const char *v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // edi
  int v23; // eax
  int v24; // eax
  int v25; // [esp-Ch] [ebp-68h]
  int v27; // [esp+Ch] [ebp-50h]
  int v28; // [esp+10h] [ebp-4Ch]
  int v29; // [esp+10h] [ebp-4Ch]
  int v30; // [esp+14h] [ebp-48h]
  char Buffer[64]; // [esp+18h] [ebp-44h] BYREF
  int v32; // [esp+58h] [ebp-4h]
  int v33; // [esp+64h] [ebp+8h]

  v32 = dword_796E50;
  sub_554930(a3);
  result = (void *)sub_63A740(a1);
  if ( a3 == a1[2] )
  {
    v5 = *((uint8_t *)a1 + 36);
    v6 = *(uint32_t *)(a3 + 20);
    v7 = *(uint32_t *)(a3 + 24);
    v33 = v6;
    if ( v5 != 0 )
    {
      if ( v5 == 1 || (v9 = v5 == 2, v8 = 214, v9) )
        v8 = 213;
    }
    else
    {
      v8 = 212;
    }
    v10 = sub_418DD0((uint32_t *)a1[10], v8);
    if ( v10 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(
        v10,
        v6 + dword_73DFFC[*((uint8_t *)a1 + 36)],
        v7 + 13,
        dword_79C0B0);
    if ( *((uint8_t *)a1 + 36) == 3 )
    {
      v11 = 0;
      v30 = 0;
      for ( i = v7 + 38; ; i += 39 )
      {
        result = dword_9B9468;
        if ( dword_9B9468 == nullptr || v11 >= (dword_9B946C - (int)dword_9B9468) >> 3 )
          break;
        v13 = *((uint32_t *)dword_9B9468 + 2 * v11);
        v27 = *((uint32_t *)dword_9B9468 + 2 * v11 + 1);
        v14 = sub_418DD0((uint32_t *)a1[10], 0x5Au);
        if ( v14 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
            v14,
            v33 + 12,
            i - 1,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            872415231,
            1333788672,
            1333788672);
        if ( sub_4F33A0(v13) != 0 )
        {
          v15 = sub_4F33A0(v13);
          if ( v15 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v15 + 152))(v15, v33 + 13, i, dword_79C0B0);
        }
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 12);
        v25 = sub_4F2CE0(v13);
        v16 = (const char *)sub_422E70(1655);
        sprintf(Buffer, v16, v25, v27);
        v28 = *(uint32_t *)dword_79C0B0;
        v17 = sub_4F2D60(v13);
        v18 = sub_4F2DF0(v17);
        (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v28 + 80))(dword_79C0B0, v33 + 43, i + 10, v18, Buffer);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v11 = ++v30;
      }
    }
    else
    {
      v19 = sub_418DD0((uint32_t *)a1[10], 0x5Au);
      if ( v19 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v19 + 128))(
          v19,
          v6 + 12,
          v7 + 37,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          872415231,
          1333788672,
          1333788672);
      if ( sub_484ED0((int *)dword_8F852C, a1[25]) == -1 )
      {
        v20 = *a1;
        a1[25] = 0;
        return (void *)(*(int (/*thiscall*/ **)(int *))(v20 + 32))(a1);
      }
      else
      {
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[25] + 16))(a1[25], a2) + 68) != 0 )
        {
          v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[25] + 16))(a1[25]);
          sub_40FC80((void *)dword_79C0B0, v6 + 13, v7 + 38, *(uint32_t *)(v21 + 68));
        }
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 12);
        v22 = *(uint32_t *)dword_79C0B0;
        v29 = a1[25];
        v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v29 + 108))(v29);
        v24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v29 + 24))(v29, v23);
        (*(void (/*cdecl*/ **)(int, int, int, int))(v22 + 80))(dword_79C0B0, v33 + 43, v7 + 48, v24);
        return (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x63AAD0 sub_63AAD0 —— 强化结果清理 2（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_63AAD0(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  int result; // eax

  *(uint32_t *)(this + 40) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(this + 40), 9, 10, 11, 9, 0, 0);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 44) = v3;
  result = sub_69A840(v3);
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
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 96) = dword_99FCCC;
  *(uint32_t *)(this + 76) = 175;
  *(uint32_t *)(this + 60) = 1;
  *(uint32_t *)(this + 52) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x63ABB0 sub_63ABB0 —— 强化结果文本（4015C0/401740）
// ------------------------------------------------------------
void /*noreturn*/ sub_63ABB0()
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
// 0x63AC20 CNRDUpgradeResultWindow__vmtC —— CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_SUCCESS/STRENGTHEN_FAIL/STRENGTHEN_ZERO/EQUIP_BROKEN 事件（432EA0 + 54D0C0 工具窗动画 + 484ED0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDUpgradeResultWindow__vmtC(int this, int a2, char a3)
{
  char v5; // al
  char *v6; // eax
  int v7; // eax

  *(uint8_t *)(this + 36) = a3;
  if ( a3 == 3 )
  {
    *(uint32_t *)(this + 100) = 0;
  }
  else
  {
    if ( a2 == 0 )
      return 0;
    *(uint32_t *)(this + 100) = a2;
    if ( dword_9B9468 != nullptr )
      j__free(dword_9B9468);
    dword_9B9468 = nullptr;
    dword_9B946C = 0;
    dword_9B9470 = 0;
  }
  sub_63A740((uint32_t *)this);
  v5 = *(uint8_t *)(this + 36);
  if ( v5 == 0 )
  {
    sub_432EA0("STRENGTHEN_SUCCESS", -1, 0, 0);
    v6 = sub_422E70(1669);
LABEL_17:
    sub_54D0C0(v6);
    goto LABEL_18;
  }
  if ( v5 != 1 && v5 != 2 )
  {
    sub_432EA0("EQUIP_BROKEN", -1, 0, 0);
    v6 = sub_422E70(1672);
    goto LABEL_17;
  }
  if ( sub_484ED0(*(uint32_t *)(this + 100)) != -1 )
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 100) + 188))(*(uint32_t *)(this + 100));
    if ( sub_41A5E0(v7 + 4) != 0 )
    {
      sub_432EA0("STRENGTHEN_FAIL", -1, 0, 0);
      v6 = sub_422E70(1670);
    }
    else
    {
      sub_432EA0("STRENGTHEN_ZERO", -1, 0, 0);
      v6 = sub_422E70(1671);
    }
    goto LABEL_17;
  }
LABEL_18:
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (unsigned int)(640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) >> 1,
    (unsigned int)(480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) >> 1);
  return 1;
}



// ------------------------------------------------------------
// 0x63AD80 sub_63AD80 —— 强化结果动画辅助（44BD30/5E51F0/41FEB0/44BD00 + 63A7C0，122 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_63AD80(int this, int a2, unsigned int a3, int a4)
{
  void *v4; // edx
  int v6; // ecx
  unsigned int v7; // eax
  int v9; // edx
  int v10; // edx
  unsigned int v11; // eax
  int v12; // edx
  int v13; // eax
  char *v14; // edi
  int v15; // ecx
  int v16; // eax
  unsigned int v17; // ebx
  int v18; // eax
  bool v20; // cf
  int v21; // ecx
  int v22; // ebx
  int v23; // ebx
  int v24; // [esp-18h] [ebp-40h]
  int v25; // [esp-Ch] [ebp-34h]
  unsigned int v26; // [esp-8h] [ebp-30h]
  int v27; // [esp+0h] [ebp-28h] BYREF
  void *v28[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v29; // [esp+24h] [ebp-4h]
  int v30; // [esp+30h] [ebp+8h]
  int v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int v33; // [esp+38h] [ebp+10h]

  v4 = *(void **)(a4 + 4);
  v28[0] = *(void **)a4;
  v6 = *(uint32_t *)(this + 4);
  v28[3] = &v27;
  v28[1] = v4;
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(this + 12) - v6) >> 3;
  else
    v7 = 0;
  if ( a3 != 0 )
  {
    if ( v6 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v9 = 0;
    if ( 0x1FFFFFFF - v9 < a3 )
      sub_63ABB0(this);
    if ( v6 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v10 = 0;
    if ( v7 >= a3 + v10 )
    {
      v18 = *(uint32_t *)(this + 8);
      v20 = (v18 - a2) >> 3 < a3;
      v21 = 8 * a3;
      v30 = 8 * a3;
      v33 = v18;
      if ( v20 )
      {
        sub_44BD30(a2, v18, a2 + v21);
        v26 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 3);
        v25 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(v25, v26, v28);
        v22 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v22;
        sub_41FEB0(a2, v22 - v30, v28);
      }
      else
      {
        v23 = v18 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(v18 - v21, v18, v18);
        sub_44BD00(a2, v23, v33);
        sub_41FEB0(a2, a2 + v30, v28);
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (v7 >> 1) >= v7 )
        v11 = (v7 >> 1) + v7;
      else
        v11 = 0;
      if ( v6 != 0 )
        v12 = (*(uint32_t *)(this + 8) - v6) >> 3;
      else
        v12 = 0;
      if ( v11 < a3 + v12 )
      {
        if ( v6 != 0 )
          v13 = (*(uint32_t *)(this + 8) - v6) >> 3;
        else
          v13 = 0;
        v11 = a3 + v13;
      }
      v31 = 8 * v11;
      v14 = (char *)operator new(8 * v11);
      v24 = *(uint32_t *)(this + 4);
      v28[2] = v14;
      v29 = 0;
      v32 = sub_44BD30(v24, a2, v14);
      sub_63A7C0(v32, a3, v28);
      sub_44BD30(a2, *(uint32_t *)(this + 8), v32 + 8 * a3);
      v15 = *(uint32_t *)(this + 4);
      if ( v15 != 0 )
        v16 = (*(uint32_t *)(this + 8) - v15) >> 3;
      else
        v16 = 0;
      v17 = v16 + a3;
      if ( v15 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v14[v31];
      *(uint32_t *)(this + 8) = &v14[8 * v17];
      *(uint32_t *)(this + 4) = v14;
    }
  }
}


// ------------------------------------------------------------
// 0x63AFD0 sub_63AFD0 —— 强化结果动画中层（63A7C0 + 63AD80）
// ------------------------------------------------------------
void /*thiscall*/ sub_63AFD0(int this, uint32_t *a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  uint32_t *v5; // edi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) >> 3 )
  {
    v5 = *(uint32_t **)(this + 8);
    sub_63A7C0(v5, (uint32_t *)1, a2);
    *(uint32_t *)(this + 8) = v5 + 2;
  }
  else
  {
    sub_63AD80(this, *(char **)(this + 8), 1u, (int)a2);
  }
}



// ------------------------------------------------------------
// 0x63B040 sub_63B040 —— 强化结果动画转发（63AFD0）
// ------------------------------------------------------------
void /*cdecl*/ sub_63B040(int a1, int a2)
{
  uint32_t v2[2]; // [esp+0h] [ebp-8h] BYREF

  v2[1] = a2;
  v2[0] = a1;
  sub_63AFD0((int)&unk_9B9464, v2);
}



// ============================================================
// 【分区 24】物品盒/金库 CNRDItemBoxWindow（0x63B070-0x63B900）
// vmt8 Update（111 行：486F40 格子 + 69A500）、vmtC 打开（44AB50/44BBA0）。
// ============================================================
// ------------------------------------------------------------
// 0x63B070 sub_63B070 —— 物品盒数据（20 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63B070(int this)
{
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 81) = 0;
  *(uint8_t *)(this + 82) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x63B0A0 sub_63B0A0 —— 物品盒数据 2（27 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63B0A0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  *(this + 14) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 16);
  *(this + 15) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  *(this + 16) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x63B0E0 sub_63B0E0 —— 物品盒数据 3（17 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_63B0E0(uint32_t *this)
{
  int v1; // edx

  v1 = *(this + 14);
  *(this + 13) = 1;
  *(uint8_t *)(v1 + 17) = 0;
  *(uint8_t *)(*(this + 15) + 17) = 0;
  *(uint8_t *)(*(this + 16) + 17) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x63B100 sub_63B100 —— 物品盒数据 4（17 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_63B100(uint32_t *this)
{
  int v1; // edx

  v1 = *(this + 14);
  *(this + 13) = 0;
  *(uint8_t *)(v1 + 17) = 1;
  *(uint8_t *)(*(this + 15) + 17) = 1;
  *(uint8_t *)(*(this + 16) + 17) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x63B120 CNRDItemBoxWindow__vmt38 —— CNRDItemBoxWindow__vmt38 确认动作槽（422E70/44E8D0 + 41A5E0，78 行）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemBoxWindow__vmt38(uint32_t *this)
{
  uint32_t *v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // esi
  char *v7; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax

  v2 = (uint32_t *)*(this + 4);
  if ( v2[626] != 2 )
    return 0;
  v3 = v2[627];
  if ( v3 != 3 && v3 != 4 )
    return 0;
  v4 = v2[629];
  if ( v4 >= *((uint32_t *)dword_8F852C + 2) )
    return 0;
  v5 = *((uint32_t *)dword_8F852C + 3);
  v6 = *(uint32_t *)(v5 + 4 * v4);
  if ( v6 == 0
    || *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v6 + 16))(*(uint32_t *)(v5 + 4 * v4)) + 4) != v2[628] )
  {
    return 0;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 20))(v6, 2) == 0 )
  {
    v7 = sub_422E70(1690);
LABEL_9:
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v7, 0);
    return 0;
  }
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 188))(v6);
  v10 = sub_41A5E0(v9 + 32);
  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 172))(v6);
  if ( v10 != sub_41A5E0(v11 + 18) )
  {
    v7 = sub_422E70(1691);
    goto LABEL_9;
  }
  if ( *(this + 9) == 1 )
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 16))(v6) + 32) == 1 )
    {
      v7 = sub_422E70(1694);
      goto LABEL_9;
    }
    if ( *(this + 9) == 1 )
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 16))(v6) + 28) != 3 )
      {
        v7 = sub_422E70(1697);
        goto LABEL_9;
      }
      if ( *(this + 9) == 1 )
      {
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 188))(v6);
        if ( sub_41A5E0(v12 + 46) >= 7 )
        {
          v7 = sub_422E70(1696);
          goto LABEL_9;
        }
      }
    }
  }
  *(this + 12) = v6;
  return 1;
}



// ------------------------------------------------------------
// 0x63B260 CNRDItemBoxWindow__vmt10 —— CNRDItemBoxWindow__vmt10 状态切换槽（44E850）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemBoxWindow__vmt10(uint32_t **this)
{
  char result; // al

  result = dword_9B88D0;
  if ( dword_9B88D0 != 0 && dword_795378 == 8 )
    return sub_44E850(*(this + 4), 26);
  return result;
}



// ------------------------------------------------------------
// 0x63B280 sub_63B280 —— 物品盒条目操作（53 行：484ED0/484E80/44E8D0/41A5E0/4F8F40）
// ------------------------------------------------------------
int /*thiscall*/ sub_63B280(int this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // ebx
  char *v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // eax
  unsigned int v11; // edi
  int v12; // ecx
  char v14; // [esp-8h] [ebp-14h]
  char v15; // [esp-4h] [ebp-10h]

  v2 = sub_484ED0(*(uint32_t *)(this + 48));
  v3 = *(uint32_t *)(this + 36);
  if ( v3 != 0 )
    v4 = v3 != 1 ? 0 : 0xE;
  else
    v4 = 15;
  v5 = sub_484E80(v4);
  v6 = v5;
  if ( v2 < 0 )
  {
    v7 = sub_422E70(1695);
LABEL_14:
    sub_44E8D0(*(char **)(this + 16), (void *)0x1B, (int)v7, 0);
    return 0;
  }
  if ( v5 < 0
    || *(uint32_t *)(this + 36) == 1
    && ((v8 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 48) + 188))(*(uint32_t *)(this + 48)),
         v15 = sub_41A5E0(v8 + 46),
         v9 = *(uint32_t *)(this + 48),
         v14 = *(uint8_t *)((*(int (**)(void))(*(uint32_t *)v9 + 16))() + 24),
         v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 16))(v9),
         ((v11 = sub_4F8F40(*(uint8_t *)(v10 + 84), v14, v15)) & 0x80000000) != 0)
     || (v6 >= *((uint32_t *)dword_8F852C + 2) ? (v12 = 0) : (v12 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v6)),
         (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 44))(v12) < v11)) )
  {
    v7 = sub_422E70(1661);
    goto LABEL_14;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x63B360 sub_63B360 —— 物品盒条目操作 2（63B280 + 698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_63B360(char **this)
{
  char *v2; // eax
  char result; // al

  if ( *(this + 10) != nullptr )
  {
    v2 = sub_422E70(1656);
    return sub_44E8D0(*(this + 4), (void *)0x1B, (int)v2, 0);
  }
  else if ( sub_63B280((int)this) == 1 )
  {
    *((uint8_t *)this + 81) = 0;
    *((uint8_t *)this + 82) = 0;
    result = sub_698F90((int)(this + 17), 0, 0);
    *(this + 10) = (char *)1;
  }
  else
  {
    return (*((int (/*thiscall*/ **)(char **))*this + 8))(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63B3C0 sub_63B3C0 —— 物品盒数据 5（32 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63B3C0(uint32_t *this)
{
  int result; // eax
  int v2; // eax

  result = *(this + 9);
  if ( result != 0 )
  {
    if ( result == 1 )
    {
      result = *(this + 14);
      *(uint8_t *)(result + 17) = 1;
    }
  }
  else
  {
    v2 = *(this + 14);
    *(this + 10) = 0;
    *(this + 13) = 0;
    *(uint8_t *)(v2 + 17) = 1;
    result = *(this + 15);
    *(uint8_t *)(result + 17) = 1;
    *(uint8_t *)(*(this + 16) + 17) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x63B400 sub_63B400 —— 物品盒数据 6（20 行）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_63B400(uint32_t *this)
{
  int v1; // eax
  int v2; // ecx
  RECT rc; // [esp+4h] [ebp-10h] BYREF

  v1 = *(this + 2);
  v2 = *(uint32_t *)(v1 + 24);
  rc.left = *(uint32_t *)(v1 + 20) + 42;
  rc.right = rc.left + 55;
  rc.top = v2 + 40;
  rc.bottom = v2 + 95;
  return PtInRect(&rc, pt);
}



// ------------------------------------------------------------
// 0x63B450 CNRDItemBoxWindow__vmtC —— CNRDItemBoxWindow__vmtC 打开槽（44AB50/44BBA0 页切换显示）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemBoxWindow__vmtC(int this, int a2, int a3)
{
  int v4; // edx
  int result; // eax
  int v6; // edx

  sub_44AB50(*(uint32_t **)(this + 16), 0, 12);
  sub_44BBA0(*(uint32_t **)(this + 16), 0, 0);
  *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 16) + 56) + 56) = 0;
  v4 = *(uint32_t *)(this + 60);
  result = 1;
  if ( a3 != 0 )
  {
    *(uint8_t *)(v4 + 16) = 0;
    *(uint8_t *)(*(uint32_t *)(this + 64) + 16) = 1;
    *(uint32_t *)(this + 36) = 1;
  }
  else
  {
    *(uint8_t *)(v4 + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(this + 64) + 16) = 0;
    *(uint32_t *)(this + 36) = 0;
  }
  v6 = *(uint32_t *)(this + 56);
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(v6 + 17) = 1;
  *(uint8_t *)(*(uint32_t *)(this + 60) + 17) = 1;
  *(uint8_t *)(*(uint32_t *)(this + 64) + 17) = 1;
  *(uint32_t *)(this + 48) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x63B4D0 CNRDItemBoxWindow__vmt8 —— CNRDItemBoxWindow__vmt8 Update（111 行：CLICK_BUTTON2 + 486F40 格子 + 69A500 + 63B400）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemBoxWindow__vmt8(int this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  char *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  BOOL v13; // eax
  int v14; // ecx
  int v15; // eax

  v2 = *(uint32_t *)(this + 56);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  if ( *(uint32_t *)(this + 40) == 1 && (unsigned int)sub_699000(this + 68) >= 0x3E8 )
  {
    if ( sub_63B280(this) == 1 )
    {
      v3 = sub_484ED0(*(uint32_t *)(this + 48));
      v4 = *(uint32_t *)(this + 36);
      if ( v4 != 0 )
        v5 = v4 != 1 ? 0 : 0xE;
      else
        v5 = 15;
      v6 = sub_484E80(v5);
      if ( (uint8_t)sub_486F40(v3, v6) == 0 )
      {
        v7 = sub_422E70(1659);
        sub_44E8D0(*(char **)(this + 16), (void *)0x1B, (int)v7, 0);
      }
      *(uint32_t *)(this + 40) = 2;
    }
    else
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 32))(this);
    }
  }
  if ( *(uint32_t *)(this + 52) != 0 )
    goto LABEL_37;
  v8 = *(uint32_t *)(this + 60);
  if ( *(uint8_t *)(v8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v8 + 12)
    || *(uint8_t *)((v9 = *(uint32_t *)(this + 64)) + 17) != 0 && dword_79BE34 == *(uint32_t *)(v9 + 12) )
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v10 = *(uint32_t *)(this + 48);
    if ( v10 != 0 )
    {
      v11 = *(uint32_t *)(this + 36);
      if ( v11 != 0 )
        v12 = v11 != 1 ? 0 : 0xE;
      else
        v12 = 15;
      sub_44E8D0(*(char **)(this + 16), (void *)0x39, v10, v12);
    }
  }
  v13 = sub_63B400((uint32_t *)this);
  v14 = *(uint32_t *)(this + 8);
  if ( v13 )
  {
    if ( (uint8_t)sub_69A500(v14) == 1 && *(uint32_t *)(*(uint32_t *)(this + 16) + 2504) == 2 )
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 56))(this);
  }
  else if ( (uint8_t)sub_69A500(v14) == 1 )
  {
    v15 = *(uint32_t *)(this + 48);
    if ( v15 == 0 )
      return v15;
    *(uint32_t *)(this + 48) = 0;
  }
  v15 = *(uint32_t *)(this + 48);
  if ( v15 == 0 )
    return v15;
  if ( !sub_63B400((uint32_t *)this) )
  {
LABEL_37:
    LOBYTE(v15) = dword_9B88D0;
    if ( dword_9B88D0 != 0 && dword_795378 == 8 )
      LOBYTE(v15) = sub_44E850(*(uint32_t **)(this + 16), 26);
  }
  else
  {
    v15 = *(uint32_t *)(this + 48);
    if ( dword_9B88D0 != v15 || dword_795378 != 8 )
    {
      v15 = sub_44E8D0(*(char **)(this + 16), (void *)0x1A, v15, 8);
      if ( v15 != 0 )
        LOBYTE(v15) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v15 + 48))(
                        v15,
                        *(uint32_t *)(*(uint32_t *)(this + 8) + 20) + 57,
                        *(uint32_t *)(*(uint32_t *)(this + 8) + 24) + 55,
                        28,
                        28);
    }
  }
  return v15;
}



// ------------------------------------------------------------
// 0x63B6D0 CNRDItemBoxWindow__vmt0 —— CNRDItemBoxWindow__vmt0 构造（106 行：418DD0/484ED0/4F33A0/63B400/4F2E40/4F2E80）
// ------------------------------------------------------------
void /*thiscall*/ CNRDItemBoxWindow__vmt0(int *this, int a2)
{
  int v2; // ebx
  int v3; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // edx
  int v11; // esi
  unsigned int v12; // edx
  uint8_t v13; // bl
  int v14; // eax
  int v15; // eax
  int v16; // [esp+14h] [ebp+8h]

  v2 = *(uint32_t *)(a2 + 24);
  v3 = *(uint32_t *)(a2 + 20);
  v16 = v2;
  v5 = sub_418DD0(44 - (*(this + 9) != 0));
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, v3, v2, dword_79C0B0);
  if ( *(this + 12) != 0 )
  {
    if ( (int)sub_484ED0(*(this + 12)) < 0 )
    {
      v10 = *this;
      *(this + 12) = 0;
      (*(void (/*thiscall*/ **)(int *))(v10 + 32))(this);
      return;
    }
    v6 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 12) + 16))(*(this + 12));
    v7 = sub_4F33A0(*(uint32_t *)(v6 + 4));
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v3 + 57, v2 + 55, dword_79C0B0);
  }
  if ( *(this + 13) == 0 && sub_63B400(this) )
    sub_4F2E40(v3 + 57, v2 + 55);
  v8 = sub_699000((int)(this + 17));
  v9 = *(this + 9);
  if ( v9 != 0 )
  {
    if ( v9 != 1 )
      return;
    v11 = *(this + 10);
    if ( v11 == 1 )
    {
      v12 = 255 * v8 / 0x3E8;
      if ( v12 <= 0xFF )
      {
        v13 = 255 * v8 / 0x3E8;
        if ( (uint8_t)v12 == 0 )
          return;
      }
      else
      {
        v13 = -1;
      }
    }
    else
    {
      if ( v11 != 2 )
        return;
      v13 = -1;
    }
    v14 = sub_418DD0(119);
    if ( v14 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
        v14,
        v3 + 57,
        v16 + 55,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v13 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491530(2, 0);
    v15 = sub_418DD0(118);
    if ( v15 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v15 + 128))(
        v15,
        v3 + 58,
        v16 + 56,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v13 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491630(2);
  }
  else if ( *(this + 10) == 1 )
  {
    sub_4F2E80(v3 + 56, v2 + 54, 1, -(int)(uint64_t)(double)(v8 >> 1));
  }
}



// ============================================================
// 【分区 25】重置/再封确认 CNRDResetOrResealConfirmWindow（0x63B900-0x63C170）
// 资源 etc/reseal.etc 由 0x63B900 装载（4FAA40）；vmt8 确认（63B360 + 63B100）。
// ============================================================
// ------------------------------------------------------------
// 0x63B900 sub_63B900 —— 装载资源 etc/reseal.etc（4FAA40）+ 69A5F0/69A840 定位——再封确认窗用
// ------------------------------------------------------------
int /*thiscall*/ sub_63B900(int *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  int v8; // edx
  int result; // eax

  *(this + 11) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 36);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(this + 11), 48, 49, 50, 48, 0, 0);
  else
    v3 = nullptr;
  *(this + 14) = (int)v3;
  sub_69A5F0(v3, 112, 14);
  sub_69A840(*(this + 14));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(this + 11), 51, 52, 53, 51, 0, 0);
  else
    v5 = nullptr;
  *(this + 15) = (int)v5;
  sub_69A5F0(v5, 46, 95);
  sub_69A840(*(this + 15));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(this + 11), 45, 46, 47, 45, 0, 0);
  else
    v7 = nullptr;
  *(this + 16) = (int)v7;
  sub_69A5F0(v7, 49, 103);
  sub_69A840(*(this + 16));
  *(uint8_t *)(*(this + 15) + 16) = 1;
  *(uint8_t *)(*(this + 16) + 16) = 0;
  v8 = *this;
  *(this + 9) = 0;
  (*(void (/*thiscall*/ **)(int *, int))(v8 + 28))(this, 1);
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 10, 10);
  sub_69A5F0((uint32_t *)*(this + 2), 142, 201);
  if ( dword_9B9478 == 0 )
    return sub_4FAA40("etc/reseal.etc", &unk_9B9474);
  result = (dword_9B947C - dword_9B9478) >> 2;
  if ( result == 0 )
    return sub_4FAA40("etc/reseal.etc", &unk_9B9474);
  return result;
}



// ------------------------------------------------------------
// 0x63BAB0 sub_63BAB0 —— 再封数据 2（16 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63BAB0(uint32_t *this)
{
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 9) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x63BAD0 sub_63BAD0 —— 再封数据 3（22 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63BAD0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 11) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x63BB00 CNRDResetOrResealConfirmWindow__vmt0 —— CNRDResetOrResealConfirmWindow__vmt0 构造（101 行：418DD0/484ED0/4F33A0/4F2CE0/422E70/4F2D60/4F2DF0）
// ------------------------------------------------------------
int /*userpurge*/ CNRDResetOrResealConfirmWindow__vmt0@<eax>(int *a1@<ecx>, int a2@<ebx>, int a3)
{
  int result; // eax
  int v5; // ebx
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  char *v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // [esp-Ch] [ebp-5Ch]
  int v19; // [esp-8h] [ebp-58h]
  int v21; // [esp+8h] [ebp-48h]
  char Buffer[64]; // [esp+Ch] [ebp-44h] BYREF
  int v23; // [esp+4Ch] [ebp-4h]
  int v24; // [esp+58h] [ebp+8h]
  int v25; // [esp+58h] [ebp+8h]

  v23 = dword_796E50;
  result = IRDPopupWindow__vmt0(a3);
  if ( a3 == a1[2] )
  {
    v5 = *(uint32_t *)(a3 + 20);
    v6 = *(uint32_t *)(a3 + 24);
    v24 = v5;
    v7 = sub_418DD0(90);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
        v7,
        v5 + 12,
        v6 + 9,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        872415231,
        1333788672,
        1333788672);
    if ( sub_484ED0(a1[25]) == -1 )
    {
      v8 = *a1;
      a1[25] = 0;
      return (*(int (/*thiscall*/ **)(int *))(v8 + 32))(a1);
    }
    else
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[25] + 16))(a1[25], a2) + 68) != 0 )
      {
        v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[25] + 16))(a1[25]) + 68);
        if ( v9 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, v5 + 13, v6 + 10, dword_79C0B0);
      }
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[25] + 108))(a1[25]);
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 12);
      v21 = *(uint32_t *)dword_79C0B0;
      v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[25] + 24))(a1[25], v10);
      v12 = v24 + 43;
      (*(void (/*cdecl*/ **)(int, int, int, int))(v21 + 80))(dword_79C0B0, v24 + 43, v6 + 20, v11);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v13 = sub_418DD0(90);
      if ( v13 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
          v13,
          v24 + 12,
          v6 + 87,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          872415231,
          1333788672,
          1333788672);
      v14 = sub_4F33A0(a1[26]);
      if ( v14 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 152))(v14, v24 + 13, v6 + 88, dword_79C0B0);
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 12);
      v19 = a1[27];
      v18 = sub_4F2CE0(a1[26]);
      v15 = sub_422E70(1655);
      sprintf(Buffer, v15, v18, v19);
      v25 = *(uint32_t *)dword_79C0B0;
      v16 = sub_4F2D60(a1[26]);
      v17 = sub_4F2DF0(v16);
      (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v25 + 80))(dword_79C0B0, v12, v6 + 98, v17, Buffer);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63BD30 sub_63BD30 —— 再封页绘制（69C3C0/69A5F0/69C440 + 43C410/69A840，58 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63BD30(uint32_t *this)
{
  int v2; // edx
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  int v7; // edx

  v2 = *this;
  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(192, 2048);
  sub_69C3C0(1);
  sub_69A5F0((uint32_t *)*(this + 3), 18, 51);
  sub_69C440(-1);
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, *(this + 9), 9, 10, 11, 9, 0, 0);
  else
    v4 = nullptr;
  *(this + 10) = v4;
  sub_69A5F0(v4, 56, 130);
  sub_69A840(*(this + 10));
  v5 = operator new(0x84u);
  if ( v5 != nullptr )
    v6 = sub_43C410(v5, *(this + 9), 12, 13, 14, 12, 0, 0);
  else
    v6 = nullptr;
  *(this + 11) = v6;
  sub_69A5F0(v6, 119, 130);
  sub_69A840(*(this + 11));
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;
  *(this + 16) = 6;
  *(this + 17) = 12;
  *(this + 18) = 0;
  *(this + 19) = 1600;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  v7 = *this;
  *(this + 24) = dword_99FCCC;
  *(this + 19) = 175;
  *(this + 15) = 1;
  *(this + 13) = -16777216;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v7 + 24))(this, 18, 12);
}



// ------------------------------------------------------------
// 0x63BEB0 CNRDResetOrResealConfirmWindow__vmt8 —— CNRDResetOrResealConfirmWindow__vmt8 确认（63B360 + 63B100 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDResetOrResealConfirmWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  int v3; // ecx
  char ***v4; // edx
  int v5; // ecx
  uint8_t *result; // eax
  int v7; // ecx
  uint32_t **v8; // edx
  int v9; // ecx

  sub_69A650(*(this + 2));
  v2 = *(this + 10);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    v3 = *(this + 4);
    v4 = *(char ****)(v3 + 360);
    v5 = v3 + 356;
    if ( v4 != nullptr && (*(uint32_t *)(v5 + 8) - (int)v4) >> 2 != 0 )
      sub_63B360(*v4);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    v7 = *(this + 4);
    v8 = *(uint32_t ***)(v7 + 360);
    v9 = v7 + 356;
    if ( v8 != nullptr && (*(uint32_t *)(v9 + 8) - (int)v8) >> 2 != 0 )
      sub_63B100(*v8);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63BF80 CNRDResetOrResealConfirmWindow__vmtC —— CNRDResetOrResealConfirmWindow__vmtC 文案装配（69C340 + 422E70 + 4F8F40 + 63B0E0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDResetOrResealConfirmWindow__vmtC(uint32_t *this, int a2, int a3)
{
  char *v4; // eax
  int v5; // eax
  char v6; // al
  int v7; // edi
  int v8; // eax
  char *v9; // eax
  uint32_t *v10; // edi
  int v11; // eax
  int v12; // ecx
  int v13; // ecx
  uint32_t **v14; // edx
  int v15; // ecx
  char v17; // [esp-8h] [ebp-10h]
  char v18; // [esp-4h] [ebp-Ch]

  *(this + 25) = a2;
  *(this + 26) = a3;
  if ( a3 == 14 )
  {
    sub_69C340(-1);
    v4 = sub_422E70(1692);
    sub_69C360(v4, 0);
    v5 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 188))(*(this + 25));
    v6 = sub_41A5E0(v5 + 46);
    v7 = *(this + 25);
    v18 = v6;
    v17 = *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7) + 24);
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7);
    *(this + 27) = sub_4F8F40(*(uint8_t *)(v8 + 84), v17, v18);
  }
  else
  {
    sub_69C340(-1);
    if ( a3 == 15 )
    {
      v9 = sub_422E70(1693);
      sub_69C360(v9, 0);
      *(this + 27) = 1;
    }
    else
    {
      sub_69C360("ERROR!!", 0);
    }
  }
  v10 = (uint32_t *)*(this + 2);
  v11 = 640 - v10[7];
  if ( ((pt.x - 85) & ((pt.x - 85 <= 0) - 1)) < v11 )
    v11 = (pt.x - 85) & ((pt.x - 85 <= 0) - 1);
  v12 = 480 - v10[8];
  if ( ((pt.y - 145) & ((pt.y - 145 <= 0) - 1)) < v12 )
    v12 = (pt.y - 145) & ((pt.y - 145 <= 0) - 1);
  sub_69A5F0(v10, v11, v12);
  v13 = *(this + 4);
  v14 = *(uint32_t ***)(v13 + 360);
  v15 = v13 + 356;
  if ( v14 != nullptr && (*(uint32_t *)(v15 + 8) - (int)v14) >> 2 != 0 )
    sub_63B0E0(*v14);
  return 1;
}



// ------------------------------------------------------------
// 0x63C0D0 sub_63C0D0 —— 再封收尾（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63C0D0(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 27) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x63C0F0 sub_63C0F0 —— 战争房间数据（33 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_63C0F0(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int i; // edi
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  void *v6; // [esp-8h] [ebp-Ch]

  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 44);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v6 = *(void **)(this + 52);
  *(uint32_t *)(this + 44) = 0;
  j_j__free(v6);
  for ( i = 0; i < *(uint32_t *)(this + 108); ++i )
  {
    v4 = *(void (/*thiscall*/ ****)(uint32_t, int))(*(uint32_t *)(this + 48) + 4 * i);
    if ( v4 != nullptr )
      (**v4)(v4, 1);
    *(uint32_t *)(*(uint32_t *)(this + 48) + 4 * i) = 0;
  }
  j_j__free(*(void **)(this + 48));
  v5 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 40);
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  *(uint32_t *)(this + 40) = 0;
}



// ============================================================
// 【分区 26】战争房间难度/信息窗（0x63C170-0x63CE30）
// CNRDWarRoomDifficultListWindow（vmt0 193 行 + 难度选择 42EAF0/5403D0）；
// CNRDWarRoomInfoWindow（vmt8 进入战争房间 49EDC0/4902A0）。
// ============================================================
// ------------------------------------------------------------
// 0x63C170 CNRDWarRoomDifficultListWindow__vmt10 —— CNRDWarRoomDifficultListWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDWarRoomDifficultListWindow__vmt10()
{
  dword_9B94AC = 0;
}



// ------------------------------------------------------------
// 0x63C180 sub_63C180 —— 战争房间难度选择（42EAF0 + 5403D0 + CLICK_BUTTON2）
// ------------------------------------------------------------
char /*thiscall*/ sub_63C180(uint32_t *this, int a2)
{
  char result; // al

  result = sub_42EAF0(*(uint32_t **)(dword_8F7A24 + 40), a2);
  if ( result == 1 )
  {
    if ( *(uint32_t *)(*(uint32_t *)(*(this + 4) + 2532) + 28) == 1 )
      sub_5403D0(0);
    sub_5403D0(1);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return (uint8_t)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63C1E0 CNRDWarRoomDifficultListWindow__vmt8 —— CNRDWarRoomDifficultListWindow__vmt8 Update（69A650 + 63C180 + CLICK_BUTTON2）
// ------------------------------------------------------------
int /*thiscall*/ CNRDWarRoomDifficultListWindow__vmt8(int *this)
{
  int v2; // eax
  int result; // eax
  int i; // edi
  int v5; // eax

  sub_69A650(*(this + 2));
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
  v2 = *(this + 11);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = *(this + 27);
  for ( i = 0; i < result; ++i )
  {
    v5 = *(uint32_t *)(*(this + 12) + 4 * i);
    if ( v5 != 0 && *(uint8_t *)(v5 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v5 + 12) )
      sub_63C180(this, i);
    result = *(this + 27);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63C270 CNRDWarRoomDifficultListWindow__vmt0 —— CNRDWarRoomDifficultListWindow__vmt0 构造（193 行：554930 + 69A110/699FC0/49EF60/49EEE0 + 422E70）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_63C270(int *this, int Value)
{
  uint32_t *result; // eax
  int v5; // edi
  int v6; // ecx
  int v7; // edi
  int v8; // ecx
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // ebx
  int v19; // eax
  int v20; // ebx
  int v21; // ebx
  int v22; // eax
  int v23; // ebx
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  int v27; // ebx
  int v28; // eax
  int v29; // ecx
  uint32_t *v30; // edi
  int v31; // eax
  int v32; // esi
  int v33; // esi
  int v34; // ecx
  int v35; // edi
  int v36; // ecx
  int v37; // eax
  int v38; // [esp-4h] [ebp-1Ch]
  int v39; // [esp+Ch] [ebp-Ch]
  int v40; // [esp+Ch] [ebp-Ch]
  int v41; // [esp+Ch] [ebp-Ch]
  int v42; // [esp+Ch] [ebp-Ch]
  int v43; // [esp+10h] [ebp-8h]
  int v44; // [esp+10h] [ebp-8h]
  int v45; // [esp+14h] [ebp-4h]
  int Valuea; // [esp+20h] [ebp+8h]
  int Valueb; // [esp+20h] [ebp+8h]
  int Valuec; // [esp+20h] [ebp+8h]
  int Valued; // [esp+20h] [ebp+8h]
  int Valuee; // [esp+20h] [ebp+8h]
  int Valuef; // [esp+20h] [ebp+8h]

  result = (uint32_t *)sub_554930(Value);
  if ( Value == *(this + 2) )
  {
    v5 = *(uint32_t *)(Value + 24);
    Valuea = *(uint32_t *)(Value + 20);
    result = (uint32_t *)sub_418DD0(0);
    if ( result != nullptr )
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*result + 152))(
                           result,
                           Valuea + 6,
                           v5 + 6,
                           dword_79C0B0);
  }
  v6 = *(this + 27);
  v7 = 0;
  if ( v6 > 0 )
  {
    result = (uint32_t *)*(this + 12);
    while ( *result != Value )
    {
      ++v7;
      ++result;
      if ( v7 >= v6 )
        return result;
    }
    v8 = *(uint32_t *)(*(this + 12) + 4 * v7);
    if ( *(uint8_t *)(v8 + 17) != 0 )
    {
      v9 = *(uint32_t *)(v8 + 12);
      if ( dword_79BE3C == v9 || dword_79BE34 == v9 || dword_79BE38 == v9 )
      {
        sub_491530(2, 0);
        v10 = *(uint32_t *)(*(this + 12) + 4 * v7);
        v11 = *(uint32_t *)(v10 + 24);
        Valueb = *(uint32_t *)(v10 + 20);
        v12 = sub_418DD0(15);
        if ( v12 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, Valueb, v11, dword_79C0B0);
        sub_491630(2);
      }
    }
    v13 = *(uint32_t *)(*(this + 12) + 4 * v7);
    Valuec = *((int16_t *)dword_8F7C48 + 10 * v7);
    v45 = *((int16_t *)dword_8F7C48 + 10 * v7 + 1);
    v43 = *(uint32_t *)(v13 + 24);
    v39 = *(uint32_t *)(v13 + 20);
    v14 = sub_418DD0(6);
    if ( v14 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 152))(v14, v39 + 6, v43 + 15, dword_79C0B0);
    v15 = *(uint32_t *)(*(this + 12) + 4 * v7);
    v40 = *(uint32_t *)(v15 + 24);
    v44 = *(uint32_t *)(v15 + 20);
    v16 = sub_418DD0(v7 + 7);
    if ( v16 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v16 + 152))(v16, v44 + 28, v40 + 15, dword_79C0B0);
    v17 = *(uint32_t *)(*(this + 12) + 4 * v7);
    v18 = *(uint32_t *)(v17 + 20) + 99;
    v41 = *(uint32_t *)(v17 + 24);
    v19 = sub_418DD0(28);
    if ( v19 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v19 + 152))(v19, v18, v41 + 17, dword_79C0B0);
    v20 = *(uint32_t *)(sub_418DD0(28) + 20) + v18;
    sub_69A110(v20, *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v7) + 24) + 17, Valuec, -1);
    v21 = sub_699FC0(Valuec) + v20;
    Valued = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v7) + 24);
    v22 = sub_418DD0(29);
    if ( v22 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v22 + 152))(v22, v21, Valued + 20, dword_79C0B0);
    v23 = *(uint32_t *)(sub_418DD0(29) + 20) + v21;
    sub_69A110(v23, *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v7) + 24) + 17, v45, -1);
    v24 = sub_699FC0(v45) + v23;
    Valuee = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v7) + 24);
    v25 = sub_418DD0(30);
    if ( v25 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v25 + 152))(v25, v24, Valuee + 17, dword_79C0B0);
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 14);
    v26 = *(uint32_t *)(*(this + 12) + 4 * v7);
    v27 = *(uint32_t *)dword_79C0B0;
    Valuef = *(uint32_t *)(v26 + 24);
    v42 = *(uint32_t *)(v26 + 20);
    v38 = sub_49EF60(v7);
    v28 = sub_49EEE0(v7);
    (*(void (**)(int, int, int, int, const char *, ...))(v27 + 80))(
      dword_79C0B0,
      v42 + 188,
      Valuef + 18,
      -1,
      "(%d/%d)",
      v28,
      v38);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    result = (uint32_t *)*(this + 13);
    v29 = result[v7];
    if ( v29 != 0 )
    {
      result = (uint32_t *)pt.x;
      if ( pt.x >= *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v7) + 20) )
      {
        result = *(uint32_t **)(*(this + 12) + 4 * v7);
        if ( pt.x <= result[5] + *(uint32_t *)(result[29] + 20) && pt.y >= result[6] )
        {
          result = *(uint32_t **)(*(this + 12) + 4 * v7);
          if ( pt.y <= result[6] + *(uint32_t *)(result[29] + 24) )
          {
            v30 = *(uint32_t **)(*(this + 12) + 4 * v7);
            v31 = v30[29];
            v32 = *(uint32_t *)(v31 + 20) >> 1;
            result = (uint32_t *)(*(uint32_t *)(v31 + 24) >> 1);
            v33 = v30[5] + v32;
            v34 = v29 - 1;
            v35 = (int)result + v30[6] + 10;
            if ( v34 != 0 )
            {
              v36 = v34 - 1;
              if ( v36 != 0 )
              {
                if ( v36 != 1 )
                  return result;
                v37 = sub_422E70(1802);
              }
              else
              {
                v37 = sub_422E70(1801);
              }
            }
            else
            {
              v37 = sub_422E70(1800);
            }
            return (uint32_t *)sub_4649B0(v33, v35, -1, -16777216, 2, v37, 0, 0, 1600, 0);
          }
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x63C660 sub_63C660 —— 难度列表辅助（49EE90）
// ------------------------------------------------------------
int /*thiscall*/ sub_63C660(int *this, char a2)
{
  int result; // eax
  int v4; // esi
  int v5; // edx
  int v6; // eax
  int v7; // ebx
  int v8; // ebx
  int v9; // [esp+8h] [ebp-8h]
  const char *future_error_what; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  result = *(this + 27);
  v4 = 0;
  if ( result > 0 )
  {
    v5 = 0;
    for ( i = 0; ; i += 20 )
    {
      v6 = *(uint32_t *)(*(this + 12) + 4 * v4);
      if ( v6 == 0 )
        goto LABEL_14;
      *(uint8_t *)(v6 + 17) = a2;
      v7 = *(int16_t *)((char *)dword_8F7C48 + v5);
      v9 = *(int16_t *)((char *)dword_8F7C48 + v5 + 2);
      if ( a2 != 1 )
        goto LABEL_14;
      if ( sub_49EE90(v4) == 0 )
        break;
      if ( dword_8F7C04 != 0
        && *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) >= v7
        && *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) <= v9 )
      {
        v8 = **((uint32_t **)dword_8F852C + 3);
        future_error_what = std::_Get_future_error_what(v4 + dword_77F888);
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 44))(v8) < (unsigned int)future_error_what )
        {
          *(uint32_t *)(*(this + 13) + 4 * v4) = 3;
          goto LABEL_13;
        }
      }
      else
      {
        *(uint32_t *)(*(this + 13) + 4 * v4) = 1;
        *(uint8_t *)(*(uint32_t *)(*(this + 12) + 4 * v4) + 17) = 0;
      }
LABEL_14:
      result = *(this + 27);
      ++v4;
      v5 = i + 20;
      if ( v4 >= result )
        return result;
    }
    *(uint32_t *)(*(this + 13) + 4 * v4) = 2;
LABEL_13:
    *(uint8_t *)(*(uint32_t *)(*(this + 12) + 4 * v4) + 17) = 0;
    goto LABEL_14;
  }
  return result;
}



// ------------------------------------------------------------
// 0x63C780 sub_63C780 —— 战争房间页绘制（426BD0/69C780/69C7B0/69A5F0/69A840 + 699E20/699E40，147 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63C780(uint32_t *this)
{
  int v1; // eax
  void *v3; // eax
  void *v4; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // eax
  uint8_t *v8; // ebx
  uint32_t *v9; // ecx
  uint8_t *v10; // eax
  uint32_t *v11; // ebx
  uint8_t *v12; // eax
  uint8_t *v13; // ebx
  int v14; // edi
  int v15; // eax
  size_t v17; // [esp-8h] [ebp-2Ch]
  void *Block; // [esp+Ch] [ebp-18h]
  void *Blocka; // [esp+Ch] [ebp-18h]
  int v20; // [esp+10h] [ebp-14h]
  int v21; // [esp+10h] [ebp-14h]
  int v22; // [esp+14h] [ebp-10h]

  v1 = *(uint32_t *)(dword_8F8508 + 8);
  *(this + 27) = v1;
  v3 = operator new(4 * v1);
  v17 = 4 * *(this + 27);
  *(this + 12) = v3;
  v4 = operator new(v17);
  v5 = *(this + 27);
  *(this + 13) = v4;
  v6 = 0;
  v7 = 0;
  if ( v5 > 0 )
  {
    do
      *(uint32_t *)(*(this + 13) + 4 * v7++) = 0;
    while ( v7 < *(this + 27) );
  }
  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 196);
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
  {
    v20 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
    sub_426BD0(v8);
    *(uint32_t *)v8 = &nengine::CNButton::`vftable';
    sub_69C780(v8);
    sub_69C7B0(v20, 23, 24, 25, 23, 0, 0);
    v9 = v8;
  }
  else
  {
    v9 = nullptr;
  }
  *(this + 11) = v9;
  sub_69A5F0(v9, 230, 11);
  sub_69A840(*(this + 11));
  v21 = 37;
  if ( (int)*(this + 27) > 0 )
  {
    v22 = 18;
    do
    {
      v10 = operator new(0x84u);
      v11 = v10;
      if ( v10 != nullptr )
      {
        Block = (void *)*(this + 9);
        sub_426BD0(v10);
        *v11 = &nengine::CNButton::`vftable';
        sub_69C780(v11);
        sub_69C7B0(Block, v22 - 1, v22, v22, v22 - 2, 0, 0);
      }
      else
      {
        v11 = nullptr;
      }
      *(uint32_t *)(*(this + 12) + 4 * v6) = v11;
      sub_69A5F0(*(uint32_t **)(*(this + 12) + 4 * v6), 14, v21);
      *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v6) + 68) = this;
      sub_69A840(*(uint32_t *)(*(this + 12) + 4 * v6++));
      v21 += 52;
      v22 += 3;
    }
    while ( v6 < *(this + 27) );
    v6 = 0;
  }
  *((uint8_t *)this + 56) = 0;
  *((uint8_t *)this + 57) = 0;
  *((uint8_t *)this + 58) = 0;
  *((uint8_t *)this + 59) = 0;
  *(this + 17) = 0;
  *(this + 18) = 6;
  *(this + 19) = 12;
  *(this + 20) = 0;
  *(this + 21) = 1600;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 26) = dword_99FCCC;
  *((uint8_t *)this + 58) = 1;
  *(this + 15) = -16777216;
  *(this + 21) = 200;
  *(this + 17) = 0;
  *(this + 22) = 1;
  v12 = operator new(0x2Cu);
  v13 = v12;
  if ( v12 != nullptr )
  {
    v14 = *(this + 9);
    Blocka = (void *)dword_79C0B0;
    v12[4] = 0;
    *(uint32_t *)v12 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v12);
    sub_699E40(Blocka, v14, 30, 2);
    v6 = (int)v13;
  }
  v15 = *(this + 27);
  *(this + 10) = v6;
  switch ( v15 )
  {
    case 0:
    case 1:
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 7);
      break;
    case 2:
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 10);
      break;
    case 3:
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 14);
      break;
    case 4:
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 18);
      break;
    default:
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 22);
      break;
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 2);
}


// ------------------------------------------------------------
// 0x63CA70 CNRDWarRoomDifficultListWindow__vmtC —— CNRDWarRoomDifficultListWindow__vmtC 打开槽（69A5F0 + 63C660）
// ------------------------------------------------------------
char /*thiscall*/ CNRDWarRoomDifficultListWindow__vmtC(int this, int a2, int a3)
{
  int i; // eax

  sub_69A5F0(*(uint32_t **)(this + 8), 192, 55);
  dword_9B94AC = this;
  for ( i = 0; i < *(uint32_t *)(this + 108); ++i )
    *(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i) = 0;
  sub_63C660((int *)this, 1);
  return 1;
}



// ------------------------------------------------------------
// 0x63CAC0 CNRDWarRoomInfoWindow__vmt8 —— CNRDWarRoomInfoWindow__vmt8 Update（49EDC0/48FBB0/48FBF0/4902A0 进入战争房间 + 423200 系 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDWarRoomInfoWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // [esp+4h] [ebp-4h] BYREF

  if ( dword_795D44 == -1 )
    return (uint8_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
  sub_69A650(*(this + 2));
  v3 = *(this + 10);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v4 = sub_49EDC0(dword_795D44, -1);
  v5 = v4;
  *(uint8_t *)(*(this + 11) + 17) = v4 != 0
                               && sub_48FBB0(v4) != 8
                               && sub_48FBF0(v5) != 0
                               && (uint8_t)sub_4902A0(v5) == 0;
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    sub_423200(dword_8F7B08, 93);
    v6 = dword_795D44;
    sub_423290(dword_8F7B08, (int)&v6, 2);
    sub_423380(dword_8F7B08);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63CBD0 CNRDWarRoomInfoWindow__vmtC —— CNRDWarRoomInfoWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDWarRoomInfoWindow__vmtC(uint32_t **this, int a2, int a3)
{
  dword_795D44 = a3;
  sub_69A5F0(*(this + 2), (640 - (*(this + 2))[7]) / 2, (480 - (*(this + 2))[8]) / 2);
  return 1;
}



// ------------------------------------------------------------
// 0x63CC10 CNRDWarRoomInfoWindow__vmt10 —— CNRDWarRoomInfoWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDWarRoomInfoWindow__vmt10()
{
  dword_795D44 = -1;
}



// ------------------------------------------------------------
// 0x63CC20 CNRDWarRoomInfoWindow__vmt0 —— CNRDWarRoomInfoWindow__vmt0 构造（102 行：418DD0/49EDC0/578E80/42B340 + 491530/491630）
// ------------------------------------------------------------
int */*userpurge*/ CNRDWarRoomInfoWindow__vmt0@<eax>(int a1@<ecx>, int a2@<esi>, int a3)
{
  int *result; // eax
  int v5; // esi
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // edi
  int v11; // ebx
  int v12; // eax
  int v13; // esi
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  int v18; // [esp+Ch] [ebp-Ch]
  int *v19; // [esp+10h] [ebp-8h]
  int v21; // [esp+20h] [ebp+8h]

  result = (int *)IRDPopupWindow__vmt0(a3);
  if ( a3 == *(uint32_t *)(a1 + 8) )
  {
    v5 = *(uint32_t *)(a3 + 20);
    v6 = *(uint32_t *)(a3 + 24);
    v7 = sub_418DD0(103);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v5 + 8, v6 + 8, dword_79C0B0);
    v8 = sub_418DD0(5);
    if ( v8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, v5 + 47, v6 + 12, dword_79C0B0);
    result = (int *)sub_49EDC0(dword_795D44, -1);
    if ( result != nullptr )
    {
      v21 = v5 + 9;
      v9 = 0;
      v10 = v6 + 34;
      v18 = 0;
      v19 = result + 2;
      do
      {
        result = (int *)sub_418DD0(45);
        if ( result != nullptr )
          result = (int *)(*(int (/*thiscall*/ **)(int *, int, int, int))(*result + 152))(result, v21, v10, dword_79C0B0);
        if ( *v19 != 255 )
        {
          result = (int *)sub_578E80(v9);
          v11 = (int)result;
          if ( result != nullptr )
          {
            v12 = sub_42B340((int)result);
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, int))(*(uint32_t *)v12 + 384))(
              v12,
              v21,
              v10,
              16,
              16,
              1065353216,
              a2);
            v13 = *v19;
            if ( (*v19 == 1 || v13 == 2) && v13 != 4 && v13 != 3 )
            {
              sub_491530(2, 0);
              v14 = sub_418DD0(v13 + 88);
              if ( v14 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 152))(v14, v21, v10, dword_79C0B0);
              v15 = sub_418DD0(v13 + 96);
              if ( v15 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v15 + 152))(v15, v21 + 18, v10, dword_79C0B0);
              sub_491630(2);
            }
            a2 = a1 + 48;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);
            if ( *(uint32_t *)(v11 + 40) < 0x10u )
              v16 = v11 + 20;
            else
              v16 = *(uint32_t *)(v11 + 20);
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
              dword_79C0B0,
              v21 + 5,
              v10 + 3,
              -1,
              v16);
            result = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
            v9 = v18;
          }
        }
        ++v9;
        v10 += 17;
        v18 = v9;
        ++v19;
      }
      while ( v9 < 8 );
    }
  }
  return result;
}



// ============================================================
// 【分区 27】物品分解确认 CNRDItemDisjointConfirmWindow（0x63CE30-0x63D420）
// vmt14 执行分解（484ED0 + 54D470 工具窗联动）。
// ============================================================
// ------------------------------------------------------------
// 0x63CE30 sub_63CE30 —— 战争房间清理（43C410/69A5F0/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_63CE30(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  int v6; // edx

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(this + 9), 23, 24, 25, 23, 0, 0);
  else
    v3 = nullptr;
  *(this + 10) = v3;
  sub_69A5F0(v3, 136, 11);
  sub_69A840(*(this + 10));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 196), 2, 3, 4, 2, 0, 0);
  else
    v5 = nullptr;
  *(this + 11) = v5;
  sub_69A5F0(v5, 36, 174);
  sub_69A840(*(this + 11));
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;
  *(this + 16) = 6;
  *(this + 17) = 12;
  *(this + 18) = 0;
  *(this + 19) = 1600;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  v6 = *this;
  *(this + 24) = dword_99FCCC;
  *(this + 13) = -16777216;
  *(this + 19) = 144;
  *(this + 15) = 1;
  *(this + 20) = 1;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v6 + 24))(this, 12, 15);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 3);
}



// ------------------------------------------------------------
// 0x63CFA0 sub_63CFA0 —— 分解数据（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63CFA0(int this)
{
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint8_t *)(this + 52) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x63CFC0 CNRDItemDisjointConfirmWindow__vmt8 —— CNRDItemDisjointConfirmWindow__vmt8 确认分解（CLICK_BUTTON2）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemDisjointConfirmWindow__vmt8(int *this)
{
  int v2; // eax
  int result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 10);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 20))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = *(this + 11);
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63D030 CNRDItemDisjointConfirmWindow__vmt14 —— CNRDItemDisjointConfirmWindow__vmt14 分解执行（484ED0 + 54D470 工具窗联动 + 44ABE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemDisjointConfirmWindow__vmt14(char **this)
{
  char *v2; // eax

  if ( *((uint32_t *)*(this + 4) + 26) != 10 )
  {
    v2 = sub_422E70(1657);
LABEL_5:
    sub_44E8D0(*(this + 4), (void *)0x1B, (int)v2, 0);
    (*((void (/*thiscall*/ **)(char **))*this + 8))(this);
    return 1;
  }
  if ( sub_484ED0(*(this + 12)) == -1 )
  {
    v2 = sub_422E70(962);
    goto LABEL_5;
  }
  sub_54D470(*(this + 12));
  if ( *((uint8_t *)this + 52) != 0 )
    sub_44ABE0(*(this + 4), 7);
  (*((void (/*thiscall*/ **)(char **))*this + 8))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x63D0B0 CNRDItemDisjointConfirmWindow__vmt0 —— CNRDItemDisjointConfirmWindow__vmt0 构造（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemDisjointConfirmWindow__vmt0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // ecx
  uint32_t *v8; // ecx

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 2) )
  {
    if ( *((uint32_t *)dword_8F8528 + 26) == 10 )
    {
      v4 = *(uint32_t *)(a2 + 20);
      v5 = *(uint32_t *)(a2 + 24);
      v6 = sub_418DD0(90);
      if ( v6 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
          v6,
          v4 + 12,
          v5 + 9,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          872415231,
          1333788672,
          1333788672);
      v7 = *(this + 28);
      if ( v7 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v4 + 13, v5 + 10, dword_79C0B0);
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 14);
      if ( *(this + 35) < 0x10u )
        v8 = this + 30;
      else
        v8 = (uint32_t *)*(this + 30);
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v4 + 18,
        v5 + 20,
        *(this + 36),
        v8);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63D1A0 sub_63D1A0 —— 分解页绘制（69C3C0/69A5F0 + 43C410/69A840，57 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63D1A0(uint32_t *this)
{
  int v2; // edx
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  int result; // eax

  v2 = *this;
  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(192, 2048);
  sub_69C3C0(1);
  sub_69A5F0((uint32_t *)*(this + 3), 18, 51);
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, *(this + 9), 9, 10, 11, 9, 0, 0);
  else
    v4 = nullptr;
  *(this + 10) = v4;
  sub_69A5F0(v4, 48, 78);
  sub_69A840(*(this + 10));
  v5 = operator new(0x84u);
  if ( v5 != nullptr )
    v6 = sub_43C410(v5, *(this + 9), 12, 13, 14, 12, 0, 0);
  else
    v6 = nullptr;
  *(this + 11) = v6;
  sub_69A5F0(v6, 127, 78);
  sub_69A840(*(this + 11));
  *((uint8_t *)this + 56) = 0;
  *((uint8_t *)this + 57) = 0;
  *((uint8_t *)this + 58) = 0;
  *((uint8_t *)this + 59) = 0;
  *(this + 17) = 0;
  *(this + 20) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 18) = 6;
  *(this + 19) = 12;
  *(this + 21) = 1600;
  result = dword_99FCCC;
  *(this + 26) = dword_99FCCC;
  *(this + 21) = 192;
  *(this + 17) = 1;
  *(this + 15) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x63D300 CNRDItemDisjointConfirmWindow__vmtC —— CNRDItemDisjointConfirmWindow__vmtC 文案装配（4015C0 + 69C340/69C440/422E70/69C360）
// ------------------------------------------------------------
char /*userpurge*/ CNRDItemDisjointConfirmWindow__vmtC@<al>(int a1@<ecx>, int a2@<edi>, int a3, int a4)
{
  int v6; // eax
  int v7; // ecx
  void *v8; // eax
  char *v9; // eax
  uint32_t *v10; // esi
  int v11; // eax
  int v12; // edx

  *(uint32_t *)(a1 + 48) = a3;
  *(uint8_t *)(a1 + 52) = a4 != 0;
  if ( a3 == 0 )
    return 0;
  v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 16))(a3, a2);
  v7 = *(uint32_t *)(a1 + 48);
  *(uint32_t *)(a1 + 112) = *(uint32_t *)(v6 + 68);
  v8 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 108))(v7);
  sub_4015C0(v8, strlen((const char *)v8));
  *(uint32_t *)(a1 + 144) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 48) + 24))(*(uint32_t *)(a1 + 48));
  sub_69C340(-1);
  sub_69C440(-1);
  v9 = sub_422E70(960);
  sub_69C360(v9, 0);
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 24))(a1, 18, 8);
  v10 = *(uint32_t **)(a1 + 8);
  v11 = 640 - v10[7];
  if ( ((pt.x - 74) & ((pt.x - 74 <= 0) - 1)) < v11 )
    v11 = (pt.x - 74) & ((pt.x - 74 <= 0) - 1);
  v12 = 480 - v10[8];
  if ( (pt.y - 89 <= 0 ? 0 : pt.y - 89) < v12 )
    v12 = pt.y - 89 <= 0 ? 0 : pt.y - 89;
  sub_69A5F0(v10, v11, v12);
  return 1;
}



// ------------------------------------------------------------
// 0x63D400 sub_63D400 —— 分解数据 2（16 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63D400(int this)
{
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint8_t *)(this + 188) = 0;
  return 0;
}



// ============================================================
// 【分区 28】赌博/抽奖窗 CNRDLotteryItemWindow（0x63D420-0x63DB00）
// vmtC（0x63D940）播 GAMBLE_OPEN_LOOP 开启循环与 GAMBLE_RESULT_COMMON/
// GAMBLE_RESULT_GOOD 结果事件。
// ============================================================
// ------------------------------------------------------------
// 0x63D420 CNRDLotteryItemWindow__vmt10 —— CNRDLotteryItemWindow__vmt10 状态切换槽（432EE0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDLotteryItemWindow__vmt10(int *this)
{
  int result; // eax

  result = *(this + 38);
  if ( result == 0 )
    return sub_432EE0(4);
  return result;
}



// ------------------------------------------------------------
// 0x63D440 CNRDLotteryItemWindow__vmt8 —— CNRDLotteryItemWindow__vmt8 Update（484E80/423200 系 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDLotteryItemWindow__vmt8(int *this)
{
  int v2; // edi
  int v3; // edi
  int v4; // eax
  uint32_t *result; // eax
  int v6; // [esp+4h] [ebp-4h] BYREF

  sub_69A650(*(this + 2));
  if ( *(this + 38) == 0 && *((uint8_t *)this + 188) == 0 )
  {
    v2 = *(this + 46);
    if ( sub_699000((int)(this + 40)) >= v2 )
    {
      v3 = sub_484E80(*(this + 39));
      if ( v3 == -1 )
      {
        (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
      }
      else
      {
        sub_423200(dword_8F7B08, 29);
        v6 = v3;
        sub_423290(dword_8F7B08, (int)&v6, 2);
        sub_423380(dword_8F7B08);
      }
      *((uint8_t *)this + 188) = 1;
    }
  }
  v4 = *(this + 9);
  if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12)
    || *((uint8_t *)(result = (uint32_t *)*(this + 10)) + 17) != 0 && dword_79BE34 == result[3] )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63D510 CNRDLotteryItemWindow__vmt0 —— CNRDLotteryItemWindow__vmt0 构造（131 行：554930 + 699000/4049C0/488670）
// ------------------------------------------------------------
int /*thiscall*/ sub_63D510(int *this, int a2)
{
  int result; // eax
  int v4; // edi
  int v5; // ecx
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  uint64_t v15; // rax
  uint32_t *v16; // ecx
  int v17; // eax
  uint32_t *v18; // ecx
  char *v19; // [esp-Ch] [ebp-1Ch]
  int v20; // [esp+Ch] [ebp-4h]
  int v21; // [esp+Ch] [ebp-4h]
  int v22; // [esp+18h] [ebp+8h]
  int v23; // [esp+18h] [ebp+8h]

  result = sub_554930(a2);
  if ( a2 == *(this + 2) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v22 = *(uint32_t *)(a2 + 24);
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);
    v5 = *(this + 39);
    if ( *(this + 38) != 0 )
    {
      v6 = 1119;
      if ( v5 == 1086 )
      {
        v6 = 2011;
      }
      else if ( v5 == 7039 )
      {
        v6 = 2014;
      }
    }
    else
    {
      v6 = 1118;
      if ( v5 == 1086 )
      {
        v6 = 2010;
      }
      else if ( v5 == 7039 )
      {
        v6 = 2013;
      }
    }
    v20 = *(uint32_t *)dword_79C0B0;
    v19 = sub_422E70(v6);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v20 + 80))(dword_79C0B0, v4 + 6, v22 + 20, -1, v19);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    v7 = v22 + 49;
    v23 = v22 + 49;
    v8 = sub_418DD0(90);
    if ( v8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v8 + 128))(
        v8,
        v4 + 18,
        v7,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        872415231,
        1333788672,
        1333788672);
    if ( *(this + 26) != 0 )
    {
      v9 = v4 + 19;
      v21 = v23 + 1;
      if ( *(this + 38) == 0 )
      {
        v10 = sub_699000((int)(this + 40));
        srand(v10 / 30);
        v9 = v9 + rand() % 2 - 1;
        v21 = v23 + rand() % 2;
      }
      v11 = *(this + 26);
      if ( v11 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(v11, v9, v21, dword_79C0B0);
      v7 = v23;
    }
    if ( *(this + 38) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);
      if ( (unsigned int)*(this + 33) < 0x10 )
        v18 = this + 28;
      else
        v18 = (uint32_t *)*(this + 28);
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v4 + 6,
        v7 + 10,
        *(this + 34),
        v18);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    }
    else
    {
      v12 = sub_418DD0(104);
      if ( v12 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, v4 + 53, v7 + 10, dword_79C0B0);
      v13 = *(this + 46);
      v14 = sub_699000((int)(this + 40));
      v15 = (uint64_t)sub_4049C0(0.0, 161.0, v14, v13);
      v16 = (uint32_t *)dword_79C0B0;
      *(uint32_t *)(dword_79C0B0 + 48) = 0;
      v16[13] = 0;
      v16[14] = v15 + v4 + 54;
      v16[15] = 480;
      v17 = sub_418DD0(105);
      if ( v17 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v17 + 152))(v17, v4 + 54, v23 + 11, dword_79C0B0);
      return sub_488670(dword_79C0B0);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x63D7F0 sub_63D7F0 —— 赌博页绘制（43C410/69A5F0/69A840，59 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63D7F0(uint32_t *this)
{
  int v2; // edx
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int v5; // edx
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  int v8; // edx
  int result; // eax

  v2 = *this;
  *(this + 11) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 24))(19, 9);
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, *(this + 11), 9, 10, 11, 9, 0, 0);
  else
    v4 = nullptr;
  v5 = *(this + 2);
  *(this + 9) = v4;
  sub_69A5F0(v4, 94, *(uint32_t *)(v5 + 32) - 37);
  sub_69A840(*(this + 9));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(this + 11), 12, 13, 14, 12, 0, 0);
  else
    v7 = nullptr;
  v8 = *(this + 2);
  *(this + 10) = v7;
  sub_69A5F0(v7, 94, *(uint32_t *)(v8 + 32) - 37);
  sub_69A840(*(this + 10));
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;
  *(this + 18) = 0;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 16) = 6;
  *(this + 17) = 12;
  *(this + 19) = 1600;
  result = dword_99FCCC;
  *(this + 24) = dword_99FCCC;
  *(this + 19) = 228;
  *(this + 15) = 1;
  *(this + 13) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x63D940 CNRDLotteryItemWindow__vmtC —— CNRDLotteryItemWindow__vmtC 播放赌博动画：GAMBLE_OPEN_LOOP 开启循环 + GAMBLE_RESULT_COMMON/GAMBLE_RESULT_GOOD 结果事件（69A5F0/698F90/432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDLotteryItemWindow__vmtC(int this, int a2, int a3)
{
  void *v5; // eax
  int v6; // eax

  if ( a2 == 0 )
    return 0;
  *(uint32_t *)(this + 152) = a3;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2) + 4) == 0 )
    return 0;
  *(uint32_t *)(this + 104) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2) + 68);
  *(uint32_t *)(this + 136) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 24))(a2);
  v5 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 108))(a2);
  sub_4015C0(v5, strlen((const char *)v5));
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) / 2,
    (480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) / 2);
  *(uint8_t *)(*(uint32_t *)(this + 36) + 16) = *(uint32_t *)(this + 152) == 1;
  *(uint8_t *)(*(uint32_t *)(this + 40) + 16) = *(uint32_t *)(this + 152) == 0;
  v6 = *(uint32_t *)(this + 152);
  if ( v6 == 0 )
  {
    *(uint32_t *)(this + 156) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2) + 4);
    *(uint8_t *)(this + 173) = 0;
    *(uint8_t *)(this + 174) = 0;
    sub_698F90(this + 160, 4000, 0);
    *(uint8_t *)(this + 188) = 0;
    sub_432EA0("GAMBLE_OPEN_LOOP", 4, 0, 0);
    return 1;
  }
  if ( v6 == 1 )
  {
    if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2) + 84) >= 2 )
    {
      sub_432EA0("GAMBLE_RESULT_GOOD", -1, 0, 0);
      return 1;
    }
    sub_432EA0("GAMBLE_RESULT_COMMON", -1, 0, 0);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x63DA90 sub_63DA90 —— 结果窗公共清理（37 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63DA90(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  uint32_t *v3; // esi
  int i; // ebx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 9) = 0;
  v3 = this + 10;
  for ( i = 2; i != 0; --i )
  {
    if ( *v3 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v3)(*v3, 1);
    *v3++ = 0;
  }
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  result = 0;
  *(this + 12) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  *(this + 13) = 0;
  return result;
}



// ============================================================
// 【分区 29】分解结果窗 CNRDItemDisjointResultWindow（0x63DB00-0x63DF50）
// vmtC 播 DISSOLVE_ITEM 分解完成事件（44CA70 收尾）。
// ============================================================
// ------------------------------------------------------------
// 0x63DB00 CNRDItemDisjointResultWindow__vmt0 —— CNRDItemDisjointResultWindow__vmt0 构造（69C690 + 418DD0）
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDItemDisjointResultWindow__vmt0(unsigned int *this, int a2)
{
  unsigned int result; // eax
  int v4; // ebx
  int v5; // edi
  unsigned int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // ecx
  uint32_t *v10; // eax
  uint32_t *v11; // edx
  int v12; // [esp+8h] [ebp-8h]
  int v13; // [esp+Ch] [ebp-4h]
  int v14; // [esp+18h] [ebp+8h]

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 2) )
  {
    v4 = 0;
    v13 = *(uint32_t *)(a2 + 20);
    v12 = 0;
    v14 = *(uint32_t *)(a2 + 24) + 59;
    do
    {
      v5 = sub_69C690(*(this + 13));
      result = *(this + 29);
      v6 = v4 + v5;
      if ( result != 0 )
      {
        result = (int)(*(this + 30) - result) / 52;
        if ( result > v6 )
        {
          v7 = sub_418DD0(90);
          if ( v7 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
              v7,
              v13 + 11,
              v14 - 10,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              872415231,
              1333788672,
              1333788672);
          v8 = 52 * v6;
          v9 = *(uint32_t *)(*(this + 29) + v8 + 4);
          if ( v9 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, v13 + 12, v14 - 9, dword_79C0B0);
          (*(void (/*thiscall*/ **)(int, unsigned int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 15);
          v10 = (uint32_t *)(*(this + 29) + v8);
          if ( v10[8] < 0x10u )
            v11 = v10 + 3;
          else
            v11 = (uint32_t *)v10[3];
          (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v13 + 6,
            v14,
            v10[9],
            v11);
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
          v4 = v12;
        }
      }
      v12 = ++v4;
      v14 += 39;
    }
    while ( v4 < 3 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x63DC50 sub_63DC50 —— 分解结果页绘制（69A5F0/69C460/69C480/69C440 + 43C410/69A840 + 426BD0/69C780/69CA20/43C630，105 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63DC50(uint32_t *this)
{
  int v2; // edx
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int v5; // ebx
  uint8_t *v6; // edi
  uint8_t *v7; // eax
  uint32_t *v8; // edi
  int v9; // ebx
  uint8_t *v10; // eax
  uint8_t *v11; // eax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-14h]
  uint32_t *v14; // [esp+10h] [ebp-10h]

  v2 = *this;
  *(this + 14) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(228, 2048);
  sub_69A5F0((uint32_t *)*(this + 3), 44, 20);
  sub_69C460(1);
  sub_69C480(-16777216);
  sub_69C440(-1);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 19, 15);
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v4 = nullptr;
  *(this + 9) = v4;
  sub_69A5F0(v4, 94, 169);
  sub_69A840(*(this + 9));
  v5 = 4;
  v14 = this + 10;
  do
  {
    v6 = operator new(0x84u);
    if ( v6 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v6);
      *(uint32_t *)v6 = &vftbl_nengine__CNButton;
      sub_69C780(v6);
      nengine__CNButton__vmt20(Block, v5, v5, v5 + 1, v5, 0, 0);
    }
    else
    {
      v6 = nullptr;
    }
    *v14 = v6;
    v5 += 2;
    ++v14;
  }
  while ( v5 < 8 );
  v7 = operator new(0x88u);
  v8 = v7;
  if ( v7 != nullptr )
  {
    v9 = *(this + 14);
    sub_426BD0(v7);
    *v8 = &vftbl_nengine__CNSlider;
    sub_69CA20(v8);
    nengine__CNSlider__vmt20(v9, 87, 88);
    *v8 = &vftbl_nengine__CNVSlider;
  }
  else
  {
    v8 = nullptr;
  }
  *(this + 12) = v8;
  v10 = operator new(0x74u);
  if ( v10 != nullptr )
    v11 = sub_43C630(v10, *(this + 10), *(this + 11), *(this + 12));
  else
    v11 = nullptr;
  *(this + 13) = v11;
  sub_69A5F0(v11, 218, 49);
  sub_69A840(*(this + 13));
  *(this + 18) = 0;
  *(this + 21) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *((uint8_t *)this + 60) = 0;
  *((uint8_t *)this + 61) = 0;
  *((uint8_t *)this + 62) = 0;
  *((uint8_t *)this + 63) = 0;
  *(this + 19) = 6;
  *(this + 20) = 12;
  *(this + 22) = 1600;
  result = dword_99FCCC;
  *(this + 27) = dword_99FCCC;
  *(this + 22) = 228;
  *(this + 18) = 1;
  *(this + 16) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x63DED0 CNRDItemDisjointResultWindow__vmtC —— CNRDItemDisjointResultWindow__vmtC 播放 DISSOLVE_ITEM 分解完成事件（44CA70 收尾 + 432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemDisjointResultWindow__vmtC(int this, int a2, int a3)
{
  char *v4; // eax

  sub_69C340(-1);
  v4 = sub_422E70(963);
  sub_69C360(v4, 0);
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) / 2,
    (480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) / 2);
  sub_44CA70((int *)(this + 112));
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 52) + 32))(*(uint32_t *)(this + 52), 0);
  sub_432EA0("DISSOLVE_ITEM", -1, 0, 0);
  return 1;
}



// ============================================================
// 【分区 30】奖励文本辅助（0x63DF50-0x63E200）
// 459700/45A340/477AF0 = 结算奖励文本拼装（被副本/交易/合成结果窗共用）。
// ============================================================
// ------------------------------------------------------------
// 0x63DF50 sub_63DF50 —— 奖励文本缓冲（4014D0）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_63DF50(uint32_t *a1, uint32_t *a2, uint32_t *a3)
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
    v4[1] = v3[1];
    sub_4014D0((std::_String_base *)(v4 + 2), v3 + 2, 0, -1);
    v4[9] = v3[9];
    v4[10] = v3[10];
    v4[11] = v3[11];
    v4[12] = v3[12];
    v3 += 13;
    v4 += 13;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x63DFB0 sub_63DFB0 —— 奖励文本拼装（459700/4014D0/63DF50 + 477AF0 + 45A340，112 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_63DFB0(uint32_t *this, int *a2, int a3)
{
  uint32_t *v4; // edi
  int *v5; // esi
  int *v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // edi
  int v11; // esi
  int v12; // eax
  char *v13; // eax
  void *v14; // eax
  int v15; // eax
  int v16; // [esp-4h] [ebp-D8h]
  char Buffer[128]; // [esp+10h] [ebp-C4h] BYREF
  int v19; // [esp+90h] [ebp-44h] BYREF
  int v20; // [esp+94h] [ebp-40h]
  uint8_t v21[28]; // [esp+98h] [ebp-3Ch] BYREF
  int v22; // [esp+B4h] [ebp-20h]
  int v23; // [esp+B8h] [ebp-1Ch]
  int v24; // [esp+BCh] [ebp-18h]
  int v25; // [esp+C0h] [ebp-14h]
  int v26; // [esp+C4h] [ebp-10h]
  int v27; // [esp+D0h] [ebp-4h]
  int v28; // [esp+DCh] [ebp+8h]

  v4 = this;
  v26 = dword_796E50;
  v28 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*a2 + 16))(a2) + 4);
  sub_459700(&v19);
  v5 = (int *)v4[29];
  v6 = (int *)v4[30];
  v27 = 0;
  if ( v5 != v6 )
  {
    while ( *v5 != v28 )
    {
      v5 += 13;
      if ( v5 == v6 )
        goto LABEL_6;
    }
    v19 = *v5;
    v20 = v5[1];
    sub_4014D0((std::_String_base *)v21, v5 + 2, 0, -1);
    v22 = v5[9];
    v23 = v5[10];
    v24 = v5[11];
    v25 = v5[12];
    v23 += a3;
  }
LABEL_6:
  if ( v5 == (int *)v4[30] )
  {
    v7 = *a2;
    v19 = v28;
    v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 16))(a2);
    v9 = *a2;
    v20 = *(uint32_t *)(v8 + 68);
    v22 = (*(int (/*thiscall*/ **)(int *))(v9 + 24))(a2);
    v23 = a3;
  }
  else
  {
    sub_63DF50(v5 + 13, (uint32_t *)v4[30], v5);
    v10 = v4[30];
    v11 = v10 - 52;
    do
    {
      sub_477AF0(v11);
      v11 += 52;
    }
    while ( v11 != v10 );
    *(this + 30) -= 52;
    v4 = this;
  }
  if ( v28 != 0 )
  {
    v14 = (void *)(*(int (/*thiscall*/ **)(int *))(*a2 + 108))(a2);
    if ( v23 <= 1 )
    {
      sub_4015C0(v14, strlen((const char *)v14));
    }
    else
    {
      sprintf(Buffer, "%s x%d", (const char *)v14, v23);
      sub_4015C0(Buffer, strlen(Buffer));
    }
  }
  else
  {
    v12 = sub_418DD0(10);
    v16 = v23;
    v20 = v12;
    v13 = sub_422E70(964);
    sprintf(Buffer, v13, v16);
    sub_4015C0(Buffer, strlen(Buffer));
  }
  sub_45A340((int)(v4 + 28), &v19);
  v15 = v4[29];
  if ( v15 != 0 )
    v15 = (v4[30] - v15) / 52;
  (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)v4[13] + 32))(v4[13], v15 - 3 <= 0 ? 0 : v15 - 3);
  v27 = -1;
  sub_477AF0((int)&v19);
}



// ------------------------------------------------------------
// 0x63E1E0 sub_63E1E0 —— 结果窗文案复位（17 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63E1E0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 9) = 0;
  return result;
}



// ============================================================
// 【分区 31】副本结算窗 CNRDPlayDungeonResultWindow（0x63E200-0x63E800）
// vmt38/3C=翻页动作（69C440 文本链 + 40BEA0 经验结算）；
// vmtC 播 REWARD_OPEN2 奖励面板事件（44CA70）。
// ============================================================
// ------------------------------------------------------------
// 0x63E200 CNRDPlayDungeonResultWindow__vmt0 —— CNRDPlayDungeonResultWindow__vmt0 构造（418DD0）
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDPlayDungeonResultWindow__vmt0(unsigned int *this, int a2)
{
  unsigned int result; // eax
  int v4; // ebx
  int v5; // eax
  int i; // esi
  int v7; // eax
  int v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // edx
  int v11; // [esp+Ch] [ebp-8h]
  unsigned int v12; // [esp+10h] [ebp-4h]
  int v13; // [esp+1Ch] [ebp+8h]

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 2) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = 0;
    v11 = v4;
    v12 = 0;
    for ( i = *(uint32_t *)(a2 + 24) + 58; ; i += 39 )
    {
      v13 = v5;
      result = *(this + 12);
      if ( result == 0 )
        break;
      result = (int)(*(this + 13) - result) / 52;
      if ( v12 >= result )
        break;
      v7 = sub_418DD0(90);
      if ( v7 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
          v7,
          v4 + 12,
          i - 9,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          872415231,
          1333788672,
          1333788672);
      v8 = *(uint32_t *)(v13 + *(this + 12) + 4);
      if ( v8 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, v4 + 13, i - 8, dword_79C0B0);
      (*(void (/*thiscall*/ **)(int, unsigned int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 15);
      v9 = (uint32_t *)(*(this + 12) + v13);
      if ( v9[8] < 0x10u )
        v10 = v9 + 3;
      else
        v10 = (uint32_t *)v9[3];
      v4 = v11;
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v11 + 20,
        i,
        v9[9],
        v10);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      ++v12;
      v5 = v13 + 52;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63E340 CNRDPlayDungeonResultWindow__vmt3C —— CNRDPlayDungeonResultWindow__vmt3C 翻页动作（69C440/69C340/69C360 + 418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPlayDungeonResultWindow__vmt3C(int *this, int a2)
{
  int v3; // eax
  char *v4; // eax
  int v5; // ebx
  int v6; // eax
  char *v8; // [esp-8h] [ebp-98h]
  int v9; // [esp-4h] [ebp-94h]
  char Buffer[128]; // [esp+Ch] [ebp-84h] BYREF
  int v11; // [esp+8Ch] [ebp-4h]

  v11 = dword_796E50;
  if ( *(uint32_t *)(a2 + 28) < 0x10u )
    v3 = a2 + 8;
  else
    v3 = *(uint32_t *)(a2 + 8);
  v9 = v3;
  v4 = sub_422E70(1131);
  sprintf(Buffer, v4, v9);
  sub_69C440(-5395027);
  sub_69C340(-1);
  sub_69C360(Buffer, 0);
  v5 = *this;
  v8 = sub_422E70(1132);
  v6 = sub_418DD0(57);
  return (*(int (/*thiscall*/ **)(int *, int, char *, int))(v5 + 64))(this, v6, v8, -13421569);
}



// ------------------------------------------------------------
// 0x63E400 sub_63E400 —— 副本结算页绘制（69A5F0/69C3C0/69C460/69C480 + 43C410/69A840，47 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63E400(uint32_t *this)
{
  int v2; // edx
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int result; // eax

  v2 = *this;
  *(this + 10) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(216, 2048);
  sub_69A5F0((uint32_t *)*(this + 3), 6, 19);
  sub_69C3C0(1);
  sub_69C460(1);
  sub_69C480(-16777216);
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v4 = nullptr;
  *(this + 9) = v4;
  result = sub_69A840(v4);
  *((uint8_t *)this + 60) = 0;
  *((uint8_t *)this + 61) = 0;
  *((uint8_t *)this + 62) = 0;
  *((uint8_t *)this + 63) = 0;
  *(this + 18) = 0;
  *(this + 21) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 19) = 6;
  *(this + 20) = 12;
  *(this + 22) = 1600;
  *(this + 27) = dword_99FCCC;
  *(this + 22) = 216;
  *(this + 18) = 1;
  *(this + 16) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x63E520 CNRDPlayDungeonResultWindow__vmt38 —— CNRDPlayDungeonResultWindow__vmt38 翻页动作（69C440/69C340/422E70/69C360 + 4CE8A0/40BEA0 经验结算）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPlayDungeonResultWindow__vmt38(int *this, uint32_t *a2, int i)
{
  char *v4; // eax
  bool v5; // cf
  const char *v6; // eax
  int v7; // esi
  int v8; // eax
  const char *v9; // eax
  const char *v10; // esi
  unsigned int v11; // eax
  char *v12; // edi
  char v13; // cl
  int v14; // edx
  int result; // eax
  uint32_t *v16; // esi
  int v17; // eax
  uint32_t *v18; // esi
  int v19; // [esp+8h] [ebp-88h] BYREF
  char Buffer[128]; // [esp+Ch] [ebp-84h] BYREF
  int v21; // [esp+8Ch] [ebp-4h]

  v21 = dword_796E50;
  sub_69C440(-1);
  sub_69C340(-1);
  v4 = sub_422E70(1133);
  sub_69C360(v4, 0);
  v5 = a2[7] < 0x10u;
  v19 = 0;
  if ( v5 )
    v6 = (const char *)(a2 + 2);
  else
    v6 = (const char *)a2[2];
  sprintf(Buffer, "%s - ", v6);
  v7 = i;
  switch ( i )
  {
    case 1:
      v8 = sub_418DD0(146);
      break;
    case 2:
      v8 = sub_418DD0(147);
      break;
    case 3:
      v8 = sub_418DD0(148);
      break;
    default:
      goto LABEL_11;
  }
  v19 = v8;
LABEL_11:
  switch ( v7 )
  {
    case 1:
      v9 = "EXPERT'S ROAD";
      break;
    case 2:
      v9 = "MASTER'S ROAD";
      break;
    case 3:
      v9 = "KING'S ROAD";
      break;
    default:
      v9 = szPassword;
      break;
  }
  v10 = v9;
  v11 = strlen(v9) + 1;
  v12 = (char *)&v19 + 3;
  do
    v13 = *++v12;
  while ( v13 != 0 );
  v14 = *this;
  qmemcpy(v12, v10, v11);
  result = (*(int (/*thiscall*/ **)(int *, int, char *, int))(v14 + 64))(this, v19, Buffer, -1);
  if ( i == 1 )
  {
    result = *(uint32_t *)dword_9B6D7C;
    for ( i = *(uint32_t *)dword_9B6D7C; i != dword_9B6D7C; result = i )
    {
      v16 = (uint32_t *)sub_4CE8A0(*(uint32_t *)(result + 12));
      if ( v16[23] == *a2 )
      {
        v17 = sub_418DD0(123);
        if ( v16[7] < 0x10u )
          v18 = v16 + 2;
        else
          v18 = (uint32_t *)v16[2];
        (*(void (/*thiscall*/ **)(int *, int, uint32_t *, int))(*this + 64))(this, v17, v18, -1);
      }
      sub_40BEA0(&i);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63E6B0 CNRDPlayDungeonResultWindow__vmtC —— CNRDPlayDungeonResultWindow__vmtC 播 REWARD_OPEN2 奖励面板事件（44CA70 + 432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPlayDungeonResultWindow__vmtC(int *this, int a2, int a3)
{
  sub_44CA70(this + 11);
  sub_432EA0("REWARD_OPEN2", -1, 0, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x63E6D0 CNRDPlayDungeonResultWindow__vmt40 —— CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/4015C0/45A340 + 69A5F0/477AF0）
// ------------------------------------------------------------
void /*thiscall*/ CNRDPlayDungeonResultWindow__vmt40(int *this, int a2, void *Src, int a4)
{
  int v5; // eax
  uint32_t *v6; // ecx
  int v7; // ebx
  int v8; // edi
  uint32_t v9[14]; // [esp+Ch] [ebp-44h] BYREF
  int v10; // [esp+4Ch] [ebp-4h]

  v9[13] = dword_796E50;
  sub_459700(v9);
  v9[1] = a2;
  v10 = 0;
  sub_4015C0(Src, strlen((const char *)Src));
  v9[9] = a4;
  sub_45A340((int)(this + 11), v9);
  v5 = *(this + 12);
  if ( v5 != 0 )
    v5 = (*(this + 13) - v5) / 52;
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 18, 3 * v5 + 6);
  v6 = (uint32_t *)*(this + 2);
  v7 = (480 - v6[8]) / 2;
  v8 = (640 - v6[7]) / 2;
  sub_69A5F0(v6, v8, v7);
  sub_69A5F0((uint32_t *)*(this + 9), v8 + 88, *(uint32_t *)(*(this + 2) + 32) + v7 - 37);
  v10 = -1;
  sub_477AF0((int)v9);
}



// ------------------------------------------------------------
// 0x63E7E0 sub_63E7E0 —— 副本结算数据（16 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63E7E0(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  return 0;
}



// ============================================================
// 【分区 32】交易结果窗 CNRDItemTradeResultWindow（0x63E800-0x63F020）
// vmtC 收尾（44CA70）。
// ============================================================
// ------------------------------------------------------------
// 0x63E800 CNRDItemTradeResultWindow__vmt8 —— CNRDItemTradeResultWindow__vmt8 Update（429830 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDItemTradeResultWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  if ( *(this + 32) != 0xFFFF && sub_429830((uint32_t *)dword_8F8500, *((uint16_t *)this + 64)) == 0 )
    *(this + 32) = 0xFFFF;
  result = (uint8_t *)*(this + 9);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63E870 CNRDItemTradeResultWindow__vmt10 —— CNRDItemTradeResultWindow__vmt10 状态切换槽（17 行）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemTradeResultWindow__vmt10(uint32_t *this)
{
  int result; // eax

  if ( *(this + 32) == 0xFFFF )
  {
    result = *(this + 4);
    *(uint32_t *)(*(uint32_t *)(result + 2444) + 10108) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x63E890 CNRDItemTradeResultWindow__vmt0 —— CNRDItemTradeResultWindow__vmt0 构造（103 行：418DD0/429830/42B340/69C690）
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDItemTradeResultWindow__vmt0(int this, int a2)
{
  unsigned int result; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // ebx
  int v10; // edi
  unsigned int v11; // edi
  int v12; // eax
  int v13; // edi
  int v14; // ecx
  uint32_t *v15; // eax
  uint32_t *v16; // edx
  int v17; // [esp+8h] [ebp-8h]
  int v18; // [esp+Ch] [ebp-4h]
  int v19; // [esp+18h] [ebp+8h]

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(uint32_t *)(this + 8) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    v18 = v4;
    if ( *(uint32_t *)(this + 128) != 0xFFFF )
    {
      v6 = sub_418DD0(89);
      if ( v6 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4 + 15, v5 + 11, dword_79C0B0);
      v7 = sub_429830((uint32_t *)dword_8F8500, *(uint16_t *)(this + 128));
      if ( v7 != 0 )
      {
        v8 = sub_42B340(v7);
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)v8 + 384))(
          v8,
          v4 + 16,
          v5 + 12,
          24,
          24,
          1065353216);
      }
    }
    v9 = 0;
    v17 = 0;
    v19 = v5 + 59;
    do
    {
      v10 = sub_69C690(*(uint32_t *)(this + 52));
      result = *(uint32_t *)(this + 116);
      v11 = v9 + v10;
      if ( result != 0 )
      {
        result = (int)(*(uint32_t *)(this + 120) - result) / 52;
        if ( result > v11 )
        {
          v12 = sub_418DD0(90);
          if ( v12 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v12 + 128))(
              v12,
              v18 + 11,
              v19 - 10,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              872415231,
              1333788672,
              1333788672);
          v13 = 52 * v11;
          v14 = *(uint32_t *)(v13 + *(uint32_t *)(this + 116) + 4);
          if ( v14 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 152))(v14, v18 + 12, v19 - 9, dword_79C0B0);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 60);
          v15 = (uint32_t *)(v13 + *(uint32_t *)(this + 116));
          if ( v15[8] < 0x10u )
            v16 = v15 + 3;
          else
            v16 = (uint32_t *)v15[3];
          (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v18 + 6,
            v19,
            v15[9],
            v16);
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
          v9 = v17;
        }
      }
      v17 = ++v9;
      v19 += 39;
    }
    while ( v9 < 3 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x63EA50 sub_63EA50 —— 交易结果页绘制（69A5F0/69C460/69C480/69C440 + 43C410/69A840 + 426BD0/69C780/69CA20/43C630，105 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63EA50(uint32_t *this)
{
  int v2; // edx
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int v5; // ebx
  uint8_t *v6; // edi
  uint8_t *v7; // eax
  uint32_t *v8; // edi
  int v9; // ebx
  uint8_t *v10; // eax
  uint8_t *v11; // eax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-14h]
  uint32_t *v14; // [esp+10h] [ebp-10h]

  v2 = *this;
  *(this + 14) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(228, 2048);
  sub_69A5F0((uint32_t *)*(this + 3), 44, 20);
  sub_69C460(1);
  sub_69C480(-16777216);
  sub_69C440(-1);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 19, 15);
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v4 = nullptr;
  *(this + 9) = v4;
  sub_69A5F0(v4, 94, 169);
  sub_69A840(*(this + 9));
  v5 = 4;
  v14 = this + 10;
  do
  {
    v6 = operator new(0x84u);
    if ( v6 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v6);
      *(uint32_t *)v6 = &vftbl_nengine__CNButton;
      sub_69C780(v6);
      nengine__CNButton__vmt20(Block, v5, v5, v5 + 1, v5, 0, 0);
    }
    else
    {
      v6 = nullptr;
    }
    *v14 = v6;
    v5 += 2;
    ++v14;
  }
  while ( v5 < 8 );
  v7 = operator new(0x88u);
  v8 = v7;
  if ( v7 != nullptr )
  {
    v9 = *(this + 14);
    sub_426BD0(v7);
    *v8 = &vftbl_nengine__CNSlider;
    sub_69CA20(v8);
    nengine__CNSlider__vmt20(v9, 87, 88);
    *v8 = &vftbl_nengine__CNVSlider;
  }
  else
  {
    v8 = nullptr;
  }
  *(this + 12) = v8;
  v10 = operator new(0x74u);
  if ( v10 != nullptr )
    v11 = sub_43C630(v10, *(this + 10), *(this + 11), *(this + 12));
  else
    v11 = nullptr;
  *(this + 13) = v11;
  sub_69A5F0(v11, 218, 49);
  sub_69A840(*(this + 13));
  *(this + 18) = 0;
  *(this + 21) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *((uint8_t *)this + 60) = 0;
  *((uint8_t *)this + 61) = 0;
  *((uint8_t *)this + 62) = 0;
  *((uint8_t *)this + 63) = 0;
  *(this + 19) = 6;
  *(this + 20) = 12;
  *(this + 22) = 1600;
  result = dword_99FCCC;
  *(this + 27) = dword_99FCCC;
  *(this + 22) = 228;
  *(this + 18) = 1;
  *(this + 16) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x63ECD0 CNRDItemTradeResultWindow__vmtC —— CNRDItemTradeResultWindow__vmtC 收尾（429830 + 69C340/69C360 + 44CA70）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemTradeResultWindow__vmtC(int this, int a2, int a3)
{
  int v4; // eax
  int v6; // eax
  char *v7; // [esp-8h] [ebp-90h]
  char *v8; // [esp-8h] [ebp-90h]
  int v9; // [esp-4h] [ebp-8Ch]
  int v10; // [esp-4h] [ebp-8Ch]
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int v12; // [esp+84h] [ebp-4h]

  v12 = dword_796E50;
  *(uint32_t *)(this + 128) = a3;
  if ( a3 == 0xFFFF )
  {
    v7 = sub_422E70(1114);
    sprintf(Buffer, v7, v9);
  }
  else
  {
    v4 = sub_429830((uint32_t *)dword_8F8500, *(uint16_t *)(this + 128));
    if ( v4 == 0 )
      return 0;
    if ( *(uint32_t *)(v4 + 40) < 0x10u )
      v6 = v4 + 20;
    else
      v6 = *(uint32_t *)(v4 + 20);
    v10 = v6;
    v8 = sub_422E70(1115);
    sprintf(Buffer, v8, v10);
  }
  sub_69C340(-1);
  sub_69C360(Buffer, 0);
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) / 2,
    (480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) / 2);
  sub_44CA70((int *)(this + 112));
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 52) + 32))(*(uint32_t *)(this + 52), 0);
  return 1;
}



// ------------------------------------------------------------
// 0x63EDD0 sub_63EDD0 —— 交易结果文本（459700/4015C0/422E70/45A340/477AF0，69 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_63EDD0(int this, int *a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  char *v9; // eax
  void *v10; // eax
  int v11; // eax
  int v12; // [esp-4h] [ebp-D0h]
  char Buffer[128]; // [esp+8h] [ebp-C4h] BYREF
  int v14; // [esp+88h] [ebp-44h] BYREF
  int v15; // [esp+8Ch] [ebp-40h]
  int v16; // [esp+ACh] [ebp-20h]
  int v17; // [esp+B0h] [ebp-1Ch]
  int v18; // [esp+BCh] [ebp-10h]
  int v19; // [esp+C8h] [ebp-4h]

  v18 = dword_796E50;
  sub_459700(&v14);
  v3 = *a2;
  v19 = 0;
  v4 = (*(int (/*thiscall*/ **)(int *))(v3 + 16))(a2);
  v5 = *a2;
  v15 = *(uint32_t *)(v4 + 68);
  v16 = (*(int (/*thiscall*/ **)(int *))(v5 + 24))(a2);
  v6 = (*(int (/*thiscall*/ **)(int *))(*a2 + 44))(a2);
  v7 = *a2;
  v17 = v6;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v7 + 16))(a2) + 4) != 0 )
  {
    v10 = (void *)(*(int (/*thiscall*/ **)(int *))(*a2 + 108))(a2);
    if ( v17 <= 1 )
    {
      sub_4015C0(v10, strlen((const char *)v10));
    }
    else
    {
      sprintf(Buffer, "%s x%d", (const char *)v10, v17);
      sub_4015C0(Buffer, strlen(Buffer));
    }
  }
  else
  {
    v8 = sub_418DD0(10);
    v12 = v17;
    v15 = v8;
    v9 = sub_422E70(1116);
    sprintf(Buffer, v9, v12);
    sub_4015C0(Buffer, strlen(Buffer));
  }
  sub_45A340(this + 112, &v14);
  v11 = *(uint32_t *)(this + 116);
  if ( v11 != 0 )
    v11 = (*(uint32_t *)(this + 120) - v11) / 52;
  (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 52) + 32))(
    *(uint32_t *)(this + 52),
    v11 - 3 <= 0 ? 0 : v11 - 3);
  v19 = -1;
  sub_477AF0((int)&v14);
}



// ------------------------------------------------------------
// 0x63EF60 sub_63EF60 —— 交易结果文本 2（63EDD0 + 4015C0）
// ------------------------------------------------------------
char /*thiscall*/ sub_63EF60(uint32_t *this, int *a2, char a3, const char *a4)
{
  int v5; // eax
  int v6; // esi
  char result; // al
  int v8; // ecx
  int v9; // esi
  const char *v10; // ebx
  char *v11; // eax
  char Buffer[512]; // [esp+8h] [ebp-204h] BYREF
  int v13; // [esp+208h] [ebp-4h]

  v13 = dword_796E50;
  v5 = *(this + 29);
  if ( v5 != 0 )
    v6 = (*(this + 30) - v5) / 52;
  else
    v6 = 0;
  sub_63EDD0((int)this, a2);
  result = a3;
  if ( a3 == 0 )
  {
    v8 = *(this + 29);
    v9 = 52 * v6;
    if ( *(uint32_t *)(v8 + v9 + 32) < 0x10u )
      v10 = (const char *)(v8 + v9 + 12);
    else
      v10 = *(const char **)(v8 + v9 + 12);
    v11 = sub_422E70(1117);
    sprintf(Buffer, "%s %s%s", v10, v11, a4);
    return sub_4015C0(Buffer, strlen(Buffer));
  }
  return result;
}



// ============================================================
// 【分区 33】合成结果窗 CNRDCompoundResultWindow（0x63F020-0x63F4C0）
// ============================================================
// ------------------------------------------------------------
// 0x63F020 CNRDCompoundResultWindow__vmt0 —— CNRDCompoundResultWindow__vmt0 构造（418DD0/422E70）
// ------------------------------------------------------------
int /*thiscall*/ CNRDCompoundResultWindow__vmt0(int *this, int a2)
{
  int result; // eax
  int v4; // ebx
  int v5; // esi
  int v6; // eax
  char *v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // ecx
  uint32_t *v11; // eax
  uint32_t *v12; // edx
  bool v13; // zf
  int v14; // [esp+Ch] [ebp-8h]
  int v15; // [esp+10h] [ebp-4h]
  int v16; // [esp+10h] [ebp-4h]
  int v17; // [esp+1Ch] [ebp+8h]

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 2) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    v14 = v4;
    v6 = sub_418DD0(dword_795D48 + 12);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4 + 13, v5 + 16, dword_79C0B0);
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);
    v15 = *(uint32_t *)dword_79C0B0;
    v7 = sub_422E70(934);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v15 + 80))(dword_79C0B0, v4 + 6, v5 + 27, -1, v7);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    result = *(this + 26);
    if ( result != 0 )
      result = (*(this + 27) - result) / 52;
    if ( result > 0 )
    {
      v17 = 0;
      v8 = v5 + 72;
      v16 = result;
      do
      {
        v9 = sub_418DD0(90);
        if ( v9 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
            v9,
            v4 + 18,
            v8 - 10,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            872415231,
            1333788672,
            1333788672);
        v10 = *(uint32_t *)(v17 + *(this + 26) + 4);
        if ( v10 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, v4 + 19, v8 - 9, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);
        v11 = (uint32_t *)(v17 + *(this + 26));
        if ( v11[8] < 0x10u )
          v12 = v11 + 3;
        else
          v12 = (uint32_t *)v11[3];
        v4 = v14;
        (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v14 + 6,
          v8,
          v11[9],
          v12);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v8 += 39;
        result = v16 - 1;
        v13 = v16 == 1;
        v17 += 52;
        --v16;
      }
      while ( !v13 );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63F1E0 sub_63F1E0 —— 合成结果清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_63F1E0(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  int result; // eax

  *(uint32_t *)(this + 40) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  *(uint32_t *)(this + 44) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 96);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 36) = v3;
  sub_69A840(v3);
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
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 76) = 1600;
  result = dword_99FCCC;
  *(uint32_t *)(this + 96) = dword_99FCCC;
  *(uint32_t *)(this + 76) = 228;
  *(uint32_t *)(this + 60) = 1;
  *(uint32_t *)(this + 52) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x63F2D0 CNRDCompoundResultWindow__vmtC —— CNRDCompoundResultWindow__vmtC 收尾（44CA70）
// ------------------------------------------------------------
char /*thiscall*/ CNRDCompoundResultWindow__vmtC(int *this, int a2, int a3)
{
  if ( dword_795D48 == 4 )
    return 0;
  sub_44CA70(this + 25);
  return 1;
}



// ------------------------------------------------------------
// 0x63F2F0 sub_63F2F0 —— 合成结果文本（459700/4015C0/422E70/45A340/69A5F0/477AF0，75 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_63F2F0(int *this, int *a2, int a3)
{
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  char *v10; // eax
  void *v11; // eax
  int v12; // eax
  uint32_t *v13; // ecx
  int v14; // edi
  int v15; // esi
  int v16; // [esp-4h] [ebp-D4h]
  char Buffer[128]; // [esp+Ch] [ebp-C4h] BYREF
  int v18; // [esp+8Ch] [ebp-44h] BYREF
  int v19; // [esp+90h] [ebp-40h]
  int v20; // [esp+B0h] [ebp-20h]
  int v21; // [esp+B4h] [ebp-1Ch]
  int v22; // [esp+C0h] [ebp-10h]
  int v23; // [esp+CCh] [ebp-4h]

  v22 = dword_796E50;
  sub_459700(&v18);
  v4 = *a2;
  v23 = 0;
  v5 = (*(int (/*thiscall*/ **)(int *))(v4 + 16))(a2);
  v6 = *a2;
  v19 = *(uint32_t *)(v5 + 68);
  v7 = (*(int (/*thiscall*/ **)(int *))(v6 + 24))(a2);
  v8 = *a2;
  v20 = v7;
  v21 = a3;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v8 + 16))(a2) + 4) != 0 )
  {
    v11 = (void *)(*(int (/*thiscall*/ **)(int *))(*a2 + 108))(a2);
    if ( v21 <= 1 )
    {
      sub_4015C0(v11, strlen((const char *)v11));
    }
    else
    {
      sprintf(Buffer, "%s x%d", (const char *)v11, v21);
      sub_4015C0(Buffer, strlen(Buffer));
    }
  }
  else
  {
    v9 = sub_418DD0(10);
    v16 = v21;
    v19 = v9;
    v10 = sub_422E70(935);
    sprintf(Buffer, v10, v16);
    sub_4015C0(Buffer, strlen(Buffer));
  }
  sub_45A340((int)(this + 25), &v18);
  v12 = *(this + 26);
  if ( v12 != 0 )
    v12 = (*(this + 27) - v12) / 52;
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 19, 3 * v12 + 7);
  v13 = (uint32_t *)*(this + 2);
  v14 = (480 - v13[8]) / 2;
  v15 = (640 - v13[7]) / 2;
  sub_69A5F0(v13, v15, v14);
  sub_69A5F0((uint32_t *)*(this + 9), v15 + 94, *(uint32_t *)(*(this + 2) + 32) + v14 - 37);
  v23 = -1;
  sub_477AF0((int)&v18);
}



// ============================================================
// 【分区 34】Sera 赠品列表/任务奖励/转职（0x63F4C0-0x63FBC0+）
// CNRDSeriasPresentListWindow（商城赠品）、CNRDQuestRewardWindow（vmtC
// 44CA70 收尾）、CNRDClassChangeWindow 转职（vmt0 322 行；其 vmtC 续作
// 在 aura_create.cpp 0x6405E0，含 "CHARACTER CREATE FAIL" 错误日志）。
// ============================================================
// ------------------------------------------------------------
// 0x63F4C0 CNRDSeriasPresentListWindow__vmt8 —— CNRDSeriasPresentListWindow__vmt8 Update（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDSeriasPresentListWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  result = (uint8_t *)*(this + 9);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63F500 CNRDQuestRewardWindow__vmt0 —— CNRDQuestRewardWindow__vmt0 构造（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDQuestRewardWindow__vmt0(uint32_t *this, int a2)
{
  uint32_t *v2; // ebx
  int result; // eax
  int v4; // edi
  int v5; // esi
  int v6; // eax
  int v7; // edi
  int v8; // esi
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // eax
  int v14; // edx
  int v16; // [esp+Ch] [ebp-4h]
  int v17; // [esp+18h] [ebp+8h]

  v2 = this;
  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == v2[2] )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    v17 = v4;
    v6 = sub_418DD0(124);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4 + 13, v5 + 16, dword_79C0B0);
    result = v2[25];
    if ( result != 0 )
      result = (v2[26] - result) / 52;
    if ( result > 0 )
    {
      v7 = 0;
      v8 = v5 + 72;
      v16 = result;
      while ( 1 )
      {
        v9 = sub_418DD0(90);
        if ( v9 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
            v9,
            v17 + 18,
            v8 - 10,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            872415231,
            1333788672,
            1333788672);
        v10 = *(uint32_t *)(v2[25] + v7 + 4);
        if ( v10 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, v17 + 19, v8 - 9, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v2 + 11);
        v11 = v2[25];
        v12 = *(uint32_t *)(v11 + v7 + 32);
        v13 = v7 + v11;
        v14 = v12 < 0x10 ? v13 + 12 : *(uint32_t *)(v13 + 12);
        (*(void (/*cdecl*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v17 + 6,
          v8,
          *(uint32_t *)(v13 + 36),
          v14);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v8 += 39;
        v7 += 52;
        result = --v16;
        if ( v16 == 0 )
          break;
        v2 = this;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63F660 sub_63F660 —— 任务奖励清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_63F660(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  int result; // eax

  *(uint32_t *)(this + 40) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 36) = v3;
  result = sub_69A840(v3);
  *(uint8_t *)(this + 44) = 0;
  *(uint8_t *)(this + 45) = 0;
  *(uint8_t *)(this + 46) = 0;
  *(uint8_t *)(this + 47) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 60) = 6;
  *(uint32_t *)(this + 64) = 12;
  *(uint32_t *)(this + 72) = 1600;
  *(uint32_t *)(this + 92) = dword_99FCCC;
  *(uint32_t *)(this + 72) = 228;
  *(uint32_t *)(this + 56) = 1;
  *(uint32_t *)(this + 48) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x63F740 CNRDQuestRewardWindow__vmtC —— CNRDQuestRewardWindow__vmtC 收尾（44CA70 + 69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDQuestRewardWindow__vmtC(int *this, int a2, int a3)
{
  int v5; // eax
  uint32_t *v6; // ecx
  int v7; // ebx
  int v8; // edi

  if ( a2 == 0 )
    return 0;
  sub_44CA70(this + 24);
  v5 = *(this + 25);
  if ( v5 != 0 )
    v5 = (*(this + 26) - v5) / 52;
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 19, 3 * v5 + 7);
  v6 = (uint32_t *)*(this + 2);
  v7 = (480 - v6[8]) / 2;
  v8 = (640 - v6[7]) / 2;
  sub_69A5F0(v6, v8, v7);
  sub_69A5F0((uint32_t *)*(this + 9), v8 + 94, *(uint32_t *)(*(this + 2) + 32) + v7 - 37);
  return 1;
}



// ------------------------------------------------------------
// 0x63F7E0 sub_63F7E0 —— 任务奖励文本（459700/4015C0/422E70/45A340/69A5F0/477AF0，75 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_63F7E0(int *this, int *a2, int a3)
{
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  char *v10; // eax
  void *v11; // eax
  int v12; // eax
  uint32_t *v13; // ecx
  int v14; // edi
  int v15; // esi
  int v16; // [esp-4h] [ebp-D4h]
  char Buffer[128]; // [esp+Ch] [ebp-C4h] BYREF
  int v18; // [esp+8Ch] [ebp-44h] BYREF
  int v19; // [esp+90h] [ebp-40h]
  int v20; // [esp+B0h] [ebp-20h]
  int v21; // [esp+B4h] [ebp-1Ch]
  int v22; // [esp+C0h] [ebp-10h]
  int v23; // [esp+CCh] [ebp-4h]

  v22 = dword_796E50;
  sub_459700(&v18);
  v4 = *a2;
  v23 = 0;
  v5 = (*(int (/*thiscall*/ **)(int *))(v4 + 16))(a2);
  v6 = *a2;
  v19 = *(uint32_t *)(v5 + 68);
  v7 = (*(int (/*thiscall*/ **)(int *))(v6 + 24))(a2);
  v8 = *a2;
  v20 = v7;
  v21 = a3;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v8 + 16))(a2) + 4) != 0 )
  {
    v11 = (void *)(*(int (/*thiscall*/ **)(int *))(*a2 + 108))(a2);
    if ( v21 <= 1 )
    {
      sub_4015C0(v11, strlen((const char *)v11));
    }
    else
    {
      sprintf(Buffer, "%s x%d", (const char *)v11, v21);
      sub_4015C0(Buffer, strlen(Buffer));
    }
  }
  else
  {
    v9 = sub_418DD0(10);
    v16 = v21;
    v19 = v9;
    v10 = sub_422E70(1137);
    sprintf(Buffer, v10, v16);
    sub_4015C0(Buffer, strlen(Buffer));
  }
  sub_45A340((int)(this + 24), &v18);
  v12 = *(this + 25);
  if ( v12 != 0 )
    v12 = (*(this + 26) - v12) / 52;
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 19, 3 * v12 + 7);
  v13 = (uint32_t *)*(this + 2);
  v14 = (480 - v13[8]) / 2;
  v15 = (640 - v13[7]) / 2;
  sub_69A5F0(v13, v15, v14);
  sub_69A5F0((uint32_t *)*(this + 9), v15 + 94, *(uint32_t *)(*(this + 2) + 32) + v14 - 37);
  v23 = -1;
  sub_477AF0((int)&v18);
}



// ------------------------------------------------------------
// 0x63F9B0 CNRDClassChangeWindow__vmt8 —— CNRDClassChangeWindow__vmt8 Update（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDClassChangeWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  result = (uint8_t *)*(this + 9);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 20))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x63F9F0 sub_63F9F0 —— 转职窗数据（41ACF0 粒子挂载，93 行）
// ------------------------------------------------------------
char */*stdcall*/ sub_63F9F0(int a1)
{
  char *result; // eax
  int i; // esi
  char v3; // cl
  int v4; // ecx
  int v5; // ecx
  char *v6; // edx
  char v7; // cl

  result = (char *)sub_41ACF0(a1 + 20);
  if ( strlen(result) > 0xE )
  {
    for ( i = 0; ; i = v5 )
    {
      v3 = result[i];
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
      v5 = i + v4;
      if ( v5 > 12 )
        break;
    }
    v6 = (char *)(byte_9B94B0 - result);
    do
    {
      v7 = *result;
      result[(uint32_t)v6] = *result;
      ++result;
    }
    while ( v7 != 0 );
    byte_9B94B0[i] = 0;
    strcat(byte_9B94B0, "..");
    return byte_9B94B0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x63FBC0 CNRDClassChangeWindow__vmt0 —— CNRDClassChangeWindow__vmt0 构造（322 行：554930 + 47DF50 + 63F9F0 + 422E70）
// ------------------------------------------------------------
int /*userpurge*/ sub_63FBC0@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>, int a3)
{
  int result; // eax
  int v5; // ebx
  int v6; // edi
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // ecx
  int v14; // edi
  int v15; // eax
  int v16; // edi
  signed int v17; // edi
  int v18; // eax
  bool v19; // zf
  int v20; // eax
  int v21; // eax
  int v22; // edi
  int v23; // eax
  int v24; // eax
  int v25; // ecx
  unsigned int v26; // edi
  int v27; // ebx
  int v28; // eax
  int v29; // ecx
  int v30; // eax
  unsigned int v31; // edi
  int v32; // eax
  int v33; // edi
  int v34; // eax
  int v35; // ecx
  unsigned int v36; // edi
  int v37; // ecx
  int v38; // ebx
  int v39; // eax
  int v40; // ecx
  int v41; // eax
  int v42; // ecx
  int v43; // edx
  int v44; // eax
  unsigned int v45; // edi
  int v46; // eax
  int v47; // edi
  int v48; // eax
  int v49; // ecx
  unsigned int v50; // edi
  int v51; // ecx
  int v52; // ebx
  int v53; // eax
  int v55; // [esp+8h] [ebp-14h]
  unsigned int v56; // [esp+8h] [ebp-14h]
  unsigned int v57; // [esp+Ch] [ebp-10h]
  int v58; // [esp+10h] [ebp-Ch]
  int v59; // [esp+10h] [ebp-Ch]
  int v60; // [esp+10h] [ebp-Ch]
  int v61; // [esp+14h] [ebp-8h]
  int v62; // [esp+18h] [ebp-4h]
  int v63; // [esp+24h] [ebp+8h]
  int i; // [esp+24h] [ebp+8h]
  int j; // [esp+24h] [ebp+8h]
  int v66; // [esp+24h] [ebp+8h]

  result = sub_554930(a3);
  if ( a3 == a1[2] )
  {
    v5 = *(uint32_t *)(a3 + 20);
    v6 = *(uint32_t *)(a3 + 24);
    v61 = v5;
    v62 = v6;
    v7 = sub_418DD0(0);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v5 + 6, v6 + 6, dword_79C0B0);
    v8 = a1[11];
    if ( v8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, v5 + 43, v6 + 45, dword_79C0B0);
    v9 = sub_418DD0(2);
    if ( v9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
        v9,
        v5 + 8,
        v6 + 90,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        1694498815,
        1333788672,
        1333788672);
    v10 = a1[26];
    if ( v10 != 0 )
      v11 = (a1[27] - v10) >> 3;
    else
      v11 = 0;
    v12 = a1[30];
    if ( v12 != 0 )
      v13 = (a1[31] - v12) >> 2;
    else
      v13 = 0;
    v14 = a1[34];
    if ( v14 != 0 )
      v15 = (a1[35] - v14) >> 2;
    else
      v15 = 0;
    if ( a1[34] != 0 )
      v16 = (a1[35] - a1[34]) >> 2;
    else
      v16 = 0;
    v17 = (v15 != 0) + ((unsigned int)(v11 + 1) >> 1) + ((unsigned int)(v13 + 1) >> 1) + ((unsigned int)(v16 + 1) >> 1);
    if ( v17 > 0 )
    {
      v63 = v62 + 123;
      v58 = v17;
      do
      {
        v18 = sub_418DD0(3);
        if ( v18 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v18 + 128))(
            v18,
            v5 + 8,
            v63,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            1694498815,
            1333788672,
            1333788672);
        v19 = v58 == 1;
        v63 += 39;
        --v58;
      }
      while ( !v19 );
    }
    v20 = sub_418DD0(4);
    if ( v20 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v20 + 128))(
        v20,
        v5 + 8,
        39 * v17 + v62 + 123,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        1694498815,
        1333788672,
        1333788672);
    v21 = sub_418DD0(1);
    if ( v21 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v21 + 128))(
        v21,
        v5 + 12,
        v62 + 94,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        603979775,
        1333788672,
        1333788672);
    (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 12, a2);
    v22 = *(uint32_t *)dword_79C0B0;
    v23 = sub_422E70(918);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v22 + 80))(dword_79C0B0, v5 + 24, v62 + 97, -6833455, v23);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    v24 = a1[26];
    if ( v24 != 0 )
      v25 = (a1[27] - v24) >> 3;
    else
      v25 = 0;
    v26 = 0;
    for ( i = v25; (int)v26 < i; ++v26 )
    {
      v55 = 126 * (v26 % 2) + v5 + 12;
      sub_47DF50(v55, 39 * (v26 / 2) + v62 + 94 + 29, *(uint32_t *)(8 * v26 + a1[26] + 4), 0, 1, 0, 0);
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 12);
      v27 = *(uint32_t *)dword_79C0B0;
      v28 = sub_63F9F0(*(uint32_t *)(a1[26] + 8 * v26));
      (*(void (/*cdecl*/ **)(int, int, unsigned int, int, int))(v27 + 80))(
        dword_79C0B0,
        v55 + 37,
        39 * (v26 / 2) + v62 + 94 + 38,
        -1,
        v28);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v5 = v61;
    }
    v29 = a1[26];
    if ( v29 != 0 )
      v30 = (a1[27] - v29) >> 3;
    else
      v30 = 0;
    v31 = 39 * ((unsigned int)(v30 + 1) >> 1) + v62 + 133;
    v59 = v31;
    v32 = sub_418DD0(1);
    if ( v32 != 0 )
      (*(void (/*thiscall*/ **)(int, int, unsigned int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v32 + 128))(
        v32,
        v5 + 12,
        v31,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        603979775,
        1333788672,
        1333788672);
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 12);
    v33 = *(uint32_t *)dword_79C0B0;
    v34 = sub_422E70(919);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v33 + 80))(dword_79C0B0, v5 + 24, v59 + 3, -6833455, v34);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    result = a1[30];
    if ( result != 0 )
      v35 = (a1[31] - result) >> 2;
    else
      v35 = 0;
    v36 = 0;
    for ( j = v35; (int)v36 < j; ++v36 )
    {
      v56 = 126 * (v36 % 2) + v5 + 12;
      v37 = *(uint32_t *)(*(uint32_t *)(4 * v36 + a1[30]) + 380);
      if ( v37 != 0 )
        (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, int))(*(uint32_t *)v37 + 152))(
          v37,
          v56,
          39 * (v36 / 2) + v59 + 29,
          dword_79C0B0);
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 12);
      v38 = *(uint32_t *)dword_79C0B0;
      v39 = sub_63F9F0(*(uint32_t *)(a1[30] + 4 * v36));
      (*(void (/*cdecl*/ **)(int, unsigned int, unsigned int, int, int))(v38 + 80))(
        dword_79C0B0,
        v56 + 37,
        39 * (v36 / 2) + v59 + 38,
        -1,
        v39);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      result = j;
      v5 = v61;
    }
    v40 = a1[34];
    if ( v40 != 0 )
    {
      result = (a1[35] - v40) >> 2;
      if ( result != 0 )
      {
        v41 = a1[26];
        if ( v41 != 0 )
          v42 = (a1[27] - v41) >> 3;
        else
          v42 = 0;
        v43 = a1[30];
        if ( v43 != 0 )
          v44 = (a1[31] - v43) >> 2;
        else
          v44 = 0;
        v45 = 39 * (((unsigned int)(v42 + 1) >> 1) + ((unsigned int)(v44 + 1) >> 1)) + v62 + 172;
        v60 = v45;
        v46 = sub_418DD0(1);
        if ( v46 != 0 )
          (*(void (/*thiscall*/ **)(int, int, unsigned int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v46 + 128))(
            v46,
            v5 + 12,
            v45,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            603979775,
            1333788672,
            1333788672);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 12);
        v47 = *(uint32_t *)dword_79C0B0;
        v48 = sub_422E70(920);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v47 + 80))(dword_79C0B0, v5 + 24, v60 + 3, -6833455, v48);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        result = a1[34];
        if ( result != 0 )
          v49 = (a1[35] - result) >> 2;
        else
          v49 = 0;
        v50 = 0;
        v66 = v49;
        if ( v49 > 0 )
        {
          while ( 1 )
          {
            v57 = 126 * (v50 % 2) + v5 + 12;
            v51 = *(uint32_t *)(*(uint32_t *)(4 * v50 + a1[34]) + 380);
            if ( v51 != 0 )
              (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, int))(*(uint32_t *)v51 + 152))(
                v51,
                v57,
                39 * (v50 / 2) + v60 + 29,
                dword_79C0B0);
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 12);
            v52 = *(uint32_t *)dword_79C0B0;
            v53 = sub_63F9F0(*(uint32_t *)(a1[34] + 4 * v50));
            (*(void (/*cdecl*/ **)(int, unsigned int, unsigned int, int, int))(v52 + 80))(
              dword_79C0B0,
              v57 + 37,
              39 * (v50 / 2) + v60 + 38,
              -1,
              v53);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
            result = v66;
            if ( (int)++v50 >= v66 )
              break;
            v5 = v61;
          }
        }
      }
    }
  }
  return result;
}

