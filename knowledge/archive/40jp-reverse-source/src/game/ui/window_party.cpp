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
uint32_t */*thiscall*/ sub_630060(int this, int *pDwArg2)  // 函数: 合成条目辅助（62FFF0 + 62FBB0）
{
  int pVecEnd_9; // edi
  unsigned int fld_8; // ecx
  int fld_82; // edi
  uint32_t *result; // eax

  pVecEnd_9 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( pVecEnd_9 != 0 )  // 若 fld_4 != 0
    fld_8 = (*(uint32_t *)(this + 8) - pVecEnd_9) / 44;
  else
    fld_8 = 0;
  if ( pVecEnd_9 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - pVecEnd_9) / 44 )  // 若 pVecEnd_9 == 0 || pVecCap_4 >= (*(uint32_t *)(this + 12) - pVecEnd_9) / 44
    return sub_62FFF0((int *)this, &pDwArg2, *(char **)(this + 8), pDwArg2);  // 调 合成表插入并回传位置
  fld_82 = *(uint32_t *)(this + 8);  // fld_82 = this+8
  result = (uint32_t *)sub_62FBB0(fld_82, 1, pDwArg2);  // 调 合成表元素重复填充
  *(uint32_t *)(this + 8) = fld_82 + 44;  // this+8 = fld_82 + 44
  return result;
}



// ------------------------------------------------------------
// 0x6300F0 CNRDCompoundItemWindow__vmtC —— CNRDCompoundItemWindow__vmtC 打开主函数（245 行：69C340 系文本 + 4F6390/62FA00 配方 + RECIPE_OPEN 事件 + 630060 条目）
// ------------------------------------------------------------
char /*thiscall*/ sub_6300F0(uint8_t *this, uint32_t *pArg2, int nArg3)  // 【CNRDCompoundItemWindow__vmtC】
{
  uint8_t *v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int pThis_15; // eax
  uint32_t *pThis_19; // ebx
  int v12; // eax
  int v13; // edi
  void *v14; // eax
  int pThis_11; // ecx
  unsigned int pThis_12; // eax
  uint32_t *pThis_112; // eax
  int v19; // ebx
  int v20; // ecx
  int v21; // eax
  bool v22; // cc
  int i; // edi
  int pObj; // eax
  void *v25; // eax
  int v26; // eax
  int pThis_192; // ecx
  int pThis_1A; // eax
  int pThis_113; // edx
  unsigned int v30; // eax
  int pThis_114; // edx
  int pThis_122; // ecx
  uint32_t *pThis_2; // ecx
  int v34; // ebx
  int v35; // edi
  int pThis_115; // ecx
  int pThis_123; // eax
  int pThis_193; // ecx
  int pThis_1A2; // eax
  bool pThis_3; // zf
  int v41; // eax
  uint8_t *v42; // [esp+Ch] [ebp-48h]
  uint32_t *pThis_1122; // [esp+10h] [ebp-44h]
  int pObj2; // [esp+14h] [ebp-40h]
  uint32_t *v45; // [esp+14h] [ebp-40h]
  int v46; // [esp+18h] [ebp-3Ch] BYREF
  void *Block; // [esp+20h] [ebp-34h]
  unsigned int v48; // [esp+34h] [ebp-20h]
  int v49; // [esp+38h] [ebp-1Ch]
  int v50; // [esp+3Ch] [ebp-18h]
  int v51; // [esp+40h] [ebp-14h]
  int dword_796E502; // [esp+44h] [ebp-10h]
  int v53; // [esp+50h] [ebp-4h]
  char v54; // [esp+5Fh] [ebp+Bh]
  bool v55; // [esp+63h] [ebp+Fh]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  v4 = __RTDynamicCast(pArg2, 0, &IRDItem `RTTI Type Descriptor', &CNRecipeStackable `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
  v42 = v4;
  *(this + 200) = nArg3 == 1;  // this+800 = nArg3 == 1
  if ( v4 == nullptr )  // 若 v4 为空
    return 0;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 108))(pArg2);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
  v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v5);  // 调用虚函数（虚表槽 +16）
  if ( v6 >= 126 )  // 若 v6 >= 126
    v6 = 126;
  *((uint32_t *)this + 14) = 114 - (v6 + 35) / 2;  // this+56 = 114 - (v6 + 35) / 2
  sub_69C340(-1);  // 调 sub_69C340
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 108))(pArg2);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
  sub_69C360(v7, 0);  // 调 sub_69C360
  *((uint32_t *)this + 12) = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 16))(pArg2) + 4);  // 调用虚函数（虚表槽 +16）
  v8 = *((uint32_t *)v4 + 41);
  *((uint32_t *)this + 13) = v8;  // this+52 = bAuraState
  if ( v8 == 4 )  // 若 v8 == 4
    return 0;
  v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 16))(pArg2);  // 调用虚函数（虚表槽 +16）
  sub_4F6390((uint32_t *)this + 16, v9 + 88);  // 调 强化结果三段 8 字节对表填充（+4/+20/+36）
  sub_62FA00(&v46);  // 调 合成表元素构造
  v53 = 0;
  sub_55A090(this + 116);  // 调 合成窗文本（442C50）
  sub_55A090(this + 132);  // 调 合成窗文本（442C50）
  pThis_15 = sub_4F33A0(**((uint32_t **)this + 21));  // 调 sub_4F33A0
  pThis_19 = *((uint32_t **)this + 25);
  *((uint32_t *)this + 15) = pThis_15;  // this+60 = pThis_15
  v54 = 1;
  if ( pThis_19 != *((uint32_t **)this + 26) )  // 若 pThis_19 != *((uint32_t **)this + 26)
  {
    while ( 1 )  // 无限循环
    {
      v12 = sub_47DC90(*pThis_19);  // 调 sub_47DC90
      v13 = v12;
      if ( v12 == 0 )  // 若 v12 == 0
        break;
      v50 = pThis_19[1];
      v49 = sub_41A5E0(v12 + 510);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      v14 = (void *)sub_41ACF0(v13 + 20);  // 调 驻留串句柄 → 字符串指针
      sub_4015C0(v14, strlen((const char *)v14));  // 【std::string构造赋值】
      v46 = *(uint32_t *)(v13 + 4 * (v49 < v50) + 380);
      v51 = v49 < v50 ? -15132207 : -16723573;
      sub_630060(&v46);  // 调 合成条目辅助（62FFF0 + 62FBB0）
      if ( v49 < v50 )  // 若 v49 < v50
        v54 = 0;
      pThis_19 += 2;
      if ( pThis_19 == *((uint32_t **)this + 26) )  // 若 pThis_19 == *((uint32_t **)this + 26)
        goto LABEL_10;  // 跳转 LABEL_10
    }
    if ( v48 >= 0x10 )  // 若 v48 >= 0x10
    {
      j__free(Block);  // 调 堆释放
      return 0;
    }
    return 0;
  }
LABEL_10:
  pThis_11 = *((uint32_t *)this + 17);
  if ( pThis_11 != 0 )  // 若 pThis_11 != 0
    pThis_12 = (*((uint32_t *)this + 18) - pThis_11) >> 3;
  else
    pThis_12 = 0;
  v55 = pThis_12 > 6;
  pObj2 = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
  if ( dword_8F7C04 == 0 )  // dword_8F7C04 = 本地玩家对象
  {
    if ( v48 >= 0x10 )  // 若 v48 >= 0x10
      j__free(Block);  // 调 堆释放
    return 0;
  }
  pThis_112 = *((uint32_t **)this + 17);
  pThis_1122 = pThis_112;
  if ( pThis_112 != *((uint32_t **)this + 18) )  // 若 pThis_112 != *((uint32_t **)this + 18)
  {
    while ( 1 )  // 无限循环
    {
      v19 = *pThis_112;
      v50 = pThis_112[1];
      v20 = sub_484E00(v19);  // 调 按类型查找并取数值（虚表 +16/+4 匹配）
      v21 = v50;
      v22 = v20 <= v50;
      v49 = v20;
      if ( v20 < v50 )  // 若 v20 < v50
      {
        for ( i = 0; i < 18; ++i )  // 循环：i = 0; i < 18; ++i
        {
          pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 792))(pObj2, i);  // 调用虚函数（虚表槽 +792）
          if ( pObj != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 4) == v19 )  // 调用虚函数（虚表槽 +16）
            ++v49;  // 自增v49
        }
        v21 = v50;
        v22 = v49 <= v50;
      }
      if ( !v22 )  // 若 !v22
        v49 = v21;
      v25 = (void *)sub_4F2CE0(v19);
      sub_4015C0(v25, strlen((const char *)v25));  // 【std::string构造赋值】
      v46 = sub_4F33A0(v19);  // 调 sub_4F33A0
      if ( v49 < v50 )  // 若 v49 < v50
      {
        v51 = -15132207;
      }
      else
      {
        v26 = sub_4F2D60(v19);  // 调 sub_4F2D60
        v51 = sub_4F2DF0(v26);  // 调 sub_4F2DF0
      }
      sub_630060(&v46);  // 调 合成条目辅助（62FFF0 + 62FBB0）
      if ( v49 < v50 )  // 若 v49 < v50
        v54 = 0;
      pThis_1122 += 2;
      if ( pThis_1122 == *((uint32_t **)this + 18) )  // 若 pThis_1122 == *((uint32_t **)this + 18)
        break;
      pThis_112 = pThis_1122;
    }
  }
  pThis_192 = *((uint32_t *)this + 25);
  if ( pThis_192 != 0 )  // 若 pThis_192 != 0
    pThis_1A = (*((uint32_t *)this + 26) - pThis_192) >> 3;
  else
    pThis_1A = 0;
  pThis_113 = *((uint32_t *)this + 17);
  v30 = 3 * (((unsigned int)(pThis_1A + 1) >> 1) + 4);
  if ( v55 )  // 若 v55
  {
    if ( pThis_113 != 0 && (unsigned int)((*((uint32_t *)this + 18) - pThis_113) >> 3) >= 6 )  // 若 pThis_113 != 0 && (unsigned int)((*((uint32_t *)this + 18) - p..
    {
      v30 += 18;
    }
    else
    {
      pThis_114 = *((uint32_t *)this + 17);
      if ( pThis_114 != 0 )  // 若 pThis_114 != 0
        v30 += ((*((uint32_t *)this + 18) - pThis_114) >> 3) + 2 * ((*((uint32_t *)this + 18) - pThis_114) >> 3);
    }
  }
  else
  {
    if ( pThis_113 != 0 )  // 若 pThis_113 != 0
      pThis_122 = (*((uint32_t *)this + 18) - pThis_113) >> 3;
    else
      pThis_122 = 0;
    v30 += pThis_122 + 2 * pThis_122;
  }
  (*(void (/*thiscall*/ **)(uint8_t *, int, unsigned int))(*(uint32_t *)this + 24))(this, 18, v30);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  pThis_2 = *((uint32_t **)this + 2);
  v34 = (480 - pThis_2[8]) / 2;
  v35 = (640 - pThis_2[7]) / 2;
  sub_69A5F0(pThis_2, v35, v34);  // 调 sub_69A5F0
  sub_69A5F0(*((uint32_t **)this + 9), v35 + 115, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v34 - 37);  // this+8 = 技能槽记录首字
  sub_69A5F0(*((uint32_t **)this + 10), v35 + 7, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v34 - 37);  // this+8 = 技能槽记录首字
  if ( v55 )  // 若 v55
  {
    pThis_115 = *((uint32_t *)this + 17);
    if ( pThis_115 != 0 )  // 若 pThis_115 != 0
      pThis_123 = (*((uint32_t *)this + 18) - pThis_115) >> 3;
    else
      pThis_123 = 0;
    (*(void (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)this + 54) + 32))(*((uint32_t *)this + 54), pThis_123 - 6);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    *(uint8_t *)(*((uint32_t *)this + 54) + 16) = 1;
    pThis_193 = *((uint32_t *)this + 25);
    if ( pThis_193 != 0 )  // 若 pThis_193 != 0
      pThis_1A2 = (*((uint32_t *)this + 26) - pThis_193) >> 3;
    else
      pThis_1A2 = 0;
    sub_69A5F0(*((uint32_t **)this + 54), v35 + 205, 39 * ((unsigned int)(pThis_1A2 + 1) >> 1) + v34 + 124);  // 调 sub_69A5F0
  }
  else
  {
    *(uint8_t *)(*((uint32_t *)this + 54) + 16) = 0;
  }
  v45 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  if ( *v45 < sub_667620(v42) )  // 调 取 +8 字段（getter）
    v54 = 0;
  pThis_3 = sub_69C500(*((uint32_t *)this + 3)) == 1;  // this+12 = 技能槽记录次字
  v41 = v34 + 27;
  if ( !pThis_3 )  // 若 !pThis_3
    v41 = v34 + 20;
  sub_69A5F0(*((uint32_t **)this + 3), *((uint32_t *)this + 14) + v35 + 35, v41);  // 调 sub_69A5F0
  *(uint8_t *)(*((uint32_t *)this + 9) + 17) = v54;  // this+36 = 状态字
  sub_432EA0("RECIPE_OPEN", -1, 0, 0);  // 调 音效播放包装（非空判定）
  if ( v48 >= 0x10 )  // 若 v48 >= 0x10
    j__free(Block);  // 调 堆释放
  return 1;
}


// ------------------------------------------------------------
// 0x6305E0 sub_6305E0 —— 合成窗辅助（21 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6305E0(uint32_t *this)  // 函数: 合成窗辅助（21 行）
{
  *(this + 9) = 2;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = bAuraState
  *(this + 14) = 0;  // this+56 = 0
  *(this + 15) = 0;  // this+60 = 0
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
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
int /*thiscall*/ sub_630610(uint32_t *this)  // 函数: 组队列表数据准备（47 行）
{
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e14)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e15)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e22)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e23)(uint32_t, int); // ecx

  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    result = (**fld_e11)(fld_e11, 1);
  fld_e12 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 11) = 0;  // this+44 = 0
  if ( fld_e12 != nullptr )  // 若 fld_e12 非空
    result = (**fld_e12)(fld_e12, 1);
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);  // this+52 = bAuraState
  *(this + 12) = 0;  // this+48 = 0
  if ( fld_e13 != nullptr )  // 若 fld_e13 非空
    result = (**fld_e13)(fld_e13, 1);
  fld_e14 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;  // this+52 = bAuraState
  if ( fld_e14 != nullptr )  // 若 fld_e14 非空
    result = (**fld_e14)(fld_e14, 1);
  fld_e15 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  *(this + 14) = 0;  // this+56 = 0
  if ( fld_e15 != nullptr )  // 若 fld_e15 非空
    result = (**fld_e15)(fld_e15, 1);
  fld_e22 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 22);  // this+88 = pFxObjB
  *(this + 15) = 0;  // this+60 = 0
  if ( fld_e22 != nullptr )  // 若 fld_e22 非空
    result = (**fld_e22)(fld_e22, 1);
  fld_e23 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 23);  // this+92 = pFxObjC
  *(this + 22) = 0;  // this+88 = pFxObjB
  if ( fld_e23 != nullptr )  // 若 fld_e23 非空
    result = (**fld_e23)(fld_e23, 1);
  *(this + 23) = 0;  // this+92 = pFxObjC
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
int /*thiscall*/ sub_6306A0(int *this)  // 函数: 组队列表构建（57 行：456480/456390 组队查询 + 69C980）
{
  int result; // eax
  int fld_e22; // ecx
  LONG v3; // edx
  LONG v4; // ecx
  LONG j; // esi
  int fld_e2; // ecx
  int v7; // edx
  LONG v8; // ecx
  LONG v9; // edx
  LONG i; // esi

  result = *(this + 9);  // this+36 = 状态字
  if ( result != 0 )  // 若 result != 0
  {
    if ( result == 1 )  // 若 result == 1
    {
      fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
      v7 = *(uint32_t *)(fld_e2 + 20);  // v7 = fld_e2+20
      v8 = *(uint32_t *)(fld_e2 + 24) + 66;
      v9 = v7 + 14;
      result = 0;
      for ( i = v8 + 16; pt.x < v9 || pt.x >= v9 + 230 || pt.y < v8 || pt.y >= i; i += 21 )  // 循环：i = v8 + 16; pt.x < v9 || pt.x >= v9 + 230 || pt.y < v8 || p
      {
        ++result;  // 自增result
        v8 += 21;
        if ( result >= 4 )  // 若 result >= 4
          return -1;  // 返回 -1（0xFFFFFFFF）
      }
    }
    else
    {
      return -1;  // 返回 -1（0xFFFFFFFF）
    }
  }
  else
  {
    fld_e22 = *(this + 2);  // this+8 = 技能槽记录首字
    v3 = *(uint32_t *)(fld_e22 + 20) + 8;
    v4 = *(uint32_t *)(fld_e22 + 24) + 34;
    for ( j = v4 + 20; pt.x < v3 || pt.x >= v3 + 242 || pt.y < v4 || pt.y >= j; j += 24 )  // 循环：j = v4 + 20; pt.x < v3 || pt.x >= v3 + 242 || pt.y < v4 || p
    {
      ++result;  // 自增result
      v4 += 24;
      if ( result >= 7 )  // 若 result >= 7
        return -1;  // 返回 -1（0xFFFFFFFF）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x630750 sub_630750 —— 组队列表页绘制（456480/429830/456390/69C980，25 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_630750(uint32_t *this)  // 函数: 组队列表页绘制（456480/429830/456390/69C980，25 行）
{
  uint32_t *v2; // edi
  int v3; // edi

  if ( *(this + 9) == 1 )  // this+36 = 状态字
  {
    v2 = (uint32_t *)dword_8F850C;
    if ( sub_456480((uint32_t *)dword_8F850C) == -1 )  // 若 sub_456480((uint32_t *)dword_8F850C) == -1
      v3 = 0;
    else
      v3 = v2[sub_456480(v2) + 4];
    *(uint8_t *)(*(this + 22) + 17) = v3 == sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // 调 表按键查找（uint16）
    if ( sub_456390((char *)dword_8F850C, 0) > 1 )  // 若 sub_456390((char *)dword_8F850C, 0) > 1
      sub_69C980(*(this + 10), 119, 120, 121, 122, 0, 0);  // this+40 = 状态子标志
    else
      sub_69C980(*(this + 10), 116, 117, 118, 116, 0, 0);  // this+40 = 状态子标志
  }
}



// ------------------------------------------------------------
// 0x6307E0 sub_6307E0 —— 组队创建提交辅助（17 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6307E0(uint32_t *this)  // 函数: 组队创建提交辅助（17 行）
{
  int fld_e2; // eax

  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  if ( fld_e2 != 0 )  // 若 fld_e2 != 0
    return dword_9B8890[(fld_e2 - 1) % 6];
  if ( *(this + 9) < 0x10u )  // this+36 = 状态字
    return (int)(this + 4);
  return *(this + 4);
}



// ------------------------------------------------------------
// 0x630810 CNRDPartyListWindow__vmt0 —— CNRDPartyListWindow__vmt0 构造（353 行：554930 + 6306A0/636190 列表 + 456390/4569F0 + 56A720）
// ------------------------------------------------------------
char /*userpurge*/ sub_630810@<al>(uint32_t *pArg1@<ecx>, uint32_t *uArg2@<esi>, int pArg3)  // 函数: CNRDPartyListWindow__vmt0 构造（353 行：554930 + 6306A0/636190 列表 + 456390/4569F0 + 56A720）
{
  int v4; // eax
  int v5; // esi
  int v6; // ebx
  int pObj4; // eax
  int pObj6; // eax
  unsigned int v9; // ebx
  int pObj8; // eax
  int v11; // ecx
  uint32_t *v12; // eax
  uint32_t *v13; // esi
  int v14; // eax
  int v15; // edx
  int v16; // ebx
  int v17; // eax
  int pObj11; // eax
  bool v19; // cc
  int v20; // ecx
  int v21; // esi
  uint32_t *v22; // edi
  int pObj10; // eax
  int pObj5; // eax
  uint32_t *v25; // ebx
  int v26; // eax
  int v27; // edx
  int v28; // ebx
  int v29; // esi
  int pObj7; // eax
  uint32_t *v31; // eax
  uint32_t *v32; // esi
  int pObj2; // eax
  int pObj; // eax
  int pObj3; // eax
  int v36; // eax
  uint32_t *v37; // ecx
  int v38; // eax
  int pObj12; // eax
  int pObj9; // eax
  int pObj13; // eax
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

  LOBYTE(v4) = sub_554930(pArg3);  // 【IRDPopupWindow__vmt0】
  if ( pArg3 == pArg1[2] )  // 若 pArg3 == pArg1[2]
  {
    v5 = *(uint32_t *)(pArg3 + 20);  // v5 = pArg3+20
    v6 = *(uint32_t *)(pArg3 + 24);  // v6 = pArg3+24
    v64 = v5;
    v56 = v6;
    pObj4 = sub_418DD0(109);  // 调 sub_418DD0
    if ( pObj4 != 0 )  // 若 pObj4 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v5 + 6, v6 + 6, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    if ( pArg1[9] != 0 )  // 若 pArg1[9] != 0
    {
      pObj10 = sub_418DD0(123);  // 调 sub_418DD0
      if ( pObj10 != 0 )  // 若 pObj10 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj10 + 152))(pObj10, v5 + 100, v6 + 12, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      pObj5 = sub_418DD0(132);  // 调 sub_418DD0
      if ( pObj5 != 0 )  // 若 pObj5 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v5 + 8, v6 + 35, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      v4 = sub_429830((uint16_t)word_77F804);  // 调 表按键查找（uint16）
      v25 = *(uint32_t **)(v4 + 184);
      v58 = v25;
      if ( v25 != nullptr )  // 若 v25 非空
      {
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 37);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
        v26 = v25[2];
        if ( v26 != 0 )  // 若 v26 != 0
        {
          v27 = dword_9B8890[(v26 - 1) % 6];
        }
        else if ( v25[9] < 0x10u )  // 否则若 v25[9] < 0x10u
        {
          v27 = (int)(v25 + 4);
        }
        else
        {
          v27 = v25[4];
        }
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          v5 + 29,
          v56 + 42,
          -804984,
          v27);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
        v28 = v5 + 14;
        v29 = v56 + 66;
        v61 = v56 + 66;
        if ( (uint8_t)sub_43BCB0(pArg1[2]) != 0 )  // 调 焦点窗口判定（三选）
          v55 = sub_6306A0(pArg1);  // 调 组队列表构建（57 行：456480/456390 组队查询 + 69C980）
        else
          v55 = -1;
        v63 = 0;
        v65 = v56 + 69;
        while ( 1 )  // 无限循环
        {
          pObj7 = sub_418DD0(45);  // 调 sub_418DD0
          if ( pObj7 != 0 )  // 若 pObj7 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v28, v29, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          v31 = (uint32_t *)sub_636190(v58, v63);  // 调 组队成员数据（56A680，27 行）
          v32 = v31;
          if ( v31 != nullptr )  // 若 v31 非空
          {
            pObj2 = sub_42B340(v31);  // 调 虚拟角色惰性创建（0x294 字节）
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t *))(*(uint32_t *)pObj2 + 384))(  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
              pObj2,
              v28,
              v61,
              16,
              16,
              1065353216,
              uArg2);
            if ( v63 == v58[14] )  // 若 v63 == v58[14]
            {
              pObj = sub_418DD0(106);  // 调 sub_418DD0
              if ( pObj != 0 )  // 若 pObj != 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v28 - 1, v65 - 4, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            }
            else
            {
              pObj3 = sub_418DD0(107);  // 调 sub_418DD0
              if ( pObj3 != 0 )  // 若 pObj3 != 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v28, v61, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            }
            uArg2 = pArg1 + 24;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
            v36 = sub_41A5E0((unsigned int)v32 + 53);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
            (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              v28 + 31,
              v65,
              -4732715,
              "Lv.%d",
              v36);
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, pArg1 + 37);  // 调用虚函数（虚表槽 +68）【推断: 观察者组件懒创建（0x10 字节）】
            if ( v32[10] < 0x10u )  // 若 v32[10] < 0x10u
              v37 = v32 + 5;
            else
              v37 = (uint32_t *)v32[5];
            (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              v28 + 17,
              v65,
              -4732715,
              v37);
            v52 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
            v38 = sub_4B0EC0(v32[11], v32[12]);  // 调 表记录字符串取值（28 字节/条）
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(v52 + 80))(dword_79C0B0, v28 + 102, v65, -8005942, v38);  // 调用虚函数（虚表槽 +80）
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
            if ( v63 == v55 )  // 若 v63 == v55
            {
              sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
              pObj12 = sub_418DD0(46);  // 调 sub_418DD0
              if ( pObj12 != 0 )  // 若 pObj12 != 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj12 + 152))(pObj12, v28 - 6, v65 - 5, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
            }
          }
          else if ( v63 >= v58[15] )  // 否则若 v63 >= v58[15]
          {
            pObj9 = sub_418DD0(108);  // 调 sub_418DD0
            if ( pObj9 != 0 )  // 若 pObj9 != 0
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj9 + 152))(pObj9, v28, v61, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            pObj13 = sub_418DD0(122);  // 调 sub_418DD0
            if ( pObj13 != 0 )  // 若 pObj13 != 0
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj13 + 152))(pObj13, v28 + 28, v65 - 2, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          }
          v19 = ++v63 < 4;
          v61 += 21;
          v65 += 21;
          if ( !v19 )  // 若 !v19
            break;
          v29 = v61;
        }
        v42 = pArg1[22];
        if ( *(uint8_t *)(v42 + 17) != 0 )  // 若 *(uint8_t *)(v42 + 17) != 0
        {
          v43 = *(uint32_t *)(v42 + 12);  // v43 = v42+12
          if ( dword_79BE3C == v43 || dword_79BE34 == v43 || dword_79BE38 == v43 )  // 若 dword_79BE3C == v43 || dword_79BE34 == v43 || dword_79BE38 == ..
          {
            v22 = (uint32_t *)pArg1[22];
            v49 = 1128;
            goto LABEL_75;  // 跳转 LABEL_75
          }
        }
        LOBYTE(v4) = sub_43BCB0(pArg1[23]);  // 调 焦点窗口判定（三选）
        if ( (uint8_t)v4 != 0 )  // 若 (uint8_t)v4 != 0
        {
          if ( (int)sub_456390(0) > 1 )  // 若 (int)sub_456390(0) > 1
            v47 = sub_422E70(1130);  // 调 sub_422E70
          else
            v47 = sub_422E70(1129);  // 调 sub_422E70
          LOBYTE(v4) = sub_4649B0(  // 调 带框文本上屏（静态一次性初始化）
                         *(uint32_t *)(pArg1[23] + 20) + (*(uint32_t *)(pArg1[23] + 28) >> 1),
                         *(uint32_t *)(pArg1[23] + 24),
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
      pObj6 = sub_418DD0(124);  // 调 sub_418DD0
      if ( pObj6 != 0 )  // 若 pObj6 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v5 + 107, v6 + 12, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      v60 = v6 + 34;
      v9 = 7 * pArg1[20];
      v57 = v9;
      if ( (uint8_t)sub_43BCB0(pArg1[2]) != 0 )  // 调 焦点窗口判定（三选）
        v54 = sub_6306A0(pArg1);  // 调 组队列表构建（57 行：456480/456390 组队查询 + 69C980）
      else
        v54 = -1;
      v59 = 0;
      v62 = v60 + 5;
      do
      {
        pObj8 = sub_418DD0(21);  // 调 sub_418DD0
        if ( pObj8 != 0 )  // 若 pObj8 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj8 + 128))(  // 调用虚函数（虚表槽 +128）
            pObj8,
            v5 + 8,
            v60,
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            1065353216,
            1065353216,
            0,
            -1929379841,
            1333788672,
            1333788672);
        v11 = pArg1[17];
        if ( v11 != 0 && v9 < (pArg1[18] - v11) >> 2 )  // 若 v11 != 0 && v9 < (pArg1[18] - v11) >> 2
        {
          v12 = (uint32_t *)sub_4569F0(*(uint32_t *)(pArg1[17] + 4 * v9));  // 调 队员槽查询
          v13 = v12;
          if ( v12 != nullptr )  // 若 v12 非空
          {
            sub_69A110(v64 + 13, v62 - 1, v12[1], -1);  // 调 sub_69A110
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 37);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
            v14 = v13[2];
            if ( v14 != 0 )  // 若 v14 != 0
            {
              v15 = dword_9B8890[(v14 - 1) % 6];
            }
            else if ( v13[9] < 0x10u )  // 否则若 v13[9] < 0x10u
            {
              v15 = (int)(v13 + 4);
            }
            else
            {
              v15 = v13[4];
            }
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              v64 + 34,
              v62,
              -4928551,
              v15);
            v16 = v13[15];
            v53 = v16 - sub_56A720(v13);  // 调 组队列表联动（55 行）
            v51 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
            v17 = sub_56A720(v13);  // 调 组队列表联动（55 行）
            (*(void (/*cdecl*/ **)(int, int, int, void *, const char *, int))(v51 + 80))(  // 调用虚函数（虚表槽 +80）
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              v64 + 134,
              v62,
              v53 <= 0 ? (void *)-13220865 : (char *)&loc_4F92CB - 13220865,
              "%d/%d",
              v17);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
            if ( v59 == v54 || v13[1] == dword_795D40 )  // 若 v59 == v54 || v13[1] == dword_795D40
            {
              sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
              pObj11 = sub_418DD0(46);  // 调 sub_418DD0
              if ( pObj11 != 0 )  // 若 pObj11 != 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj11 + 152))(pObj11, v64 + 8, v60, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
            }
            v9 = v57;
          }
          v5 = v64;
        }
        v60 += 24;
        ++v9;  // 自增v9
        v19 = ++v59 < 7;
        v57 = v9;
        v62 += 24;
      }
      while ( v19 );  // 当 v19 循环
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 37);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
      (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        v5 + 29,
        v56 + 207,
        -3750202,
        "%d/%d",
        pArg1[20] + 1,
        pArg1[21] + 1);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
      v20 = pArg1[12];
      LOBYTE(v4) = *(uint8_t *)(v20 + 17);  // 调 取 16 位值低 8 位
      if ( (uint8_t)v4 != 0 )  // 若 (uint8_t)v4 != 0
      {
        v21 = *(uint32_t *)(v20 + 12);  // v21 = v20+12
        if ( dword_79BE3C == v21 || dword_79BE34 == v21 || (LOBYTE(v4) = dword_79BE38, dword_79BE38 == v21) )  // 调 取 16 位值低 8 位
        {
          v22 = (uint32_t *)pArg1[12];
          v49 = 1127;
LABEL_75:
          v44 = v22[6];
          v45 = v22[7];
          v66 = v22[5];
          v46 = sub_422E70(v49);  // 调 sub_422E70
          LOBYTE(v4) = sub_4649B0(v66 + (v45 >> 1), v44, -1, -16777216, 2, v46, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
        }
      }
    }
  }
  return v4;
}


// ------------------------------------------------------------
// 0x630F80 sub_630F80 —— 组队成员条目绘制（43C410/69A5F0/69A840 + 423B30，121 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_630F80(uint32_t *this)  // 函数: 组队成员条目绘制（43C410/69A5F0/69A840 + 423B30，121 行）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e10; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e102; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_e103; // eax
  uint32_t *pMem4; // eax
  uint32_t *fld_e104; // eax
  uint8_t *pMem5; // eax
  uint8_t *fld_e105; // eax
  uint32_t *pMem6; // eax
  uint32_t *fld_e106; // eax
  uint32_t *pMem7; // eax
  uint32_t *fld_e107; // eax
  int dword_99FCCC2; // ecx
  int v17; // edx

  *(this + 10) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+40 = 状态子标志
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e10 = sub_43C410(pMem, *(this + 10), 23, 24, 25, 23, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e10 = nullptr;  // fld_e10 = nullptr 空指针
  *(this + 11) = fld_e10;  // this+44 = fld_e10
  sub_69A5F0(fld_e10, 230, 11);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 11));  // this+8 = 技能槽记录首字
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e102 = sub_43C410(pMem2, *(this + 10), 110, 111, 112, 110, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e102 = nullptr;  // fld_e102 = nullptr 空指针
  *(this + 12) = fld_e102;  // this+48 = fld_e102
  sub_69A5F0(fld_e102, 91, 226);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 12));  // this+8 = 技能槽记录首字
  pMem3 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    fld_e103 = sub_43C410(pMem3, *(this + 10), 76, 77, 78, 76, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e103 = nullptr;  // fld_e103 = nullptr 空指针
  *(this + 13) = fld_e103;  // this+52 = bAuraState
  sub_69A5F0(fld_e103, 100, 206);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 13));  // this+8 = 技能槽记录首字
  pMem4 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    fld_e104 = sub_43C410(pMem4, *(this + 10), 79, 80, 81, 79, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e104 = nullptr;  // fld_e104 = nullptr 空指针
  *(this + 14) = fld_e104;  // this+56 = fld_e104
  sub_69A5F0(fld_e104, 146, 206);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 14));  // this+8 = 技能槽记录首字
  pMem5 = operator new(0x2Cu);  // operator new 分配 44 字节
  if ( pMem5 != nullptr )  // 若 pMem5 非空
    fld_e105 = sub_423B30(pMem5, dword_79C0B0, *(this + 10), 51, 3);  // 调 CNNumberSet 构造
  else
    fld_e105 = nullptr;  // fld_e105 = nullptr 空指针
  *(this + 15) = fld_e105;  // this+60 = fld_e105
  fld_e105[24] = 1;
  pMem6 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem6 != nullptr )  // 若 pMem6 非空
    fld_e106 = sub_43C410(pMem6, *(this + 10), 113, 114, 115, 125, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e106 = nullptr;  // fld_e106 = nullptr 空指针
  *(this + 22) = fld_e106;  // this+88 = pFxObjB
  sub_69A5F0(fld_e106, 49, 161);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 22));  // this+8 = 技能槽记录首字
  pMem7 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem7 != nullptr )  // 若 pMem7 非空
    fld_e107 = sub_43C410(pMem7, *(this + 10), 119, 120, 121, 119, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e107 = nullptr;  // fld_e107 = nullptr 空指针
  *(this + 23) = fld_e107;  // this+92 = pFxObjC
  sub_69A5F0(fld_e107, 133, 161);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 23));  // this+8 = 技能槽记录首字
  *((uint8_t *)this + 96) = 0;
  *((uint8_t *)this + 97) = 0;
  *((uint8_t *)this + 98) = 0;
  *((uint8_t *)this + 99) = 0;
  *(this + 27) = 0;  // this+108 = 0
  *(this + 28) = 6;  // this+112 = pHostComp
  *(this + 30) = 0;  // this+120 = 动画对象指针
  *(this + 32) = 0;  // this+128 = 0
  *(this + 33) = 0;  // this+132 = 0
  *(this + 34) = 0;  // this+136 = 0
  *(this + 35) = 0;  // this+140 = 0
  *(this + 36) = 0;  // this+144 = pFrameList144
  *(this + 29) = 12;  // this+116 = 12
  *(this + 31) = 1600;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
  *(this + 36) = dword_99FCCC;  // this+144 = pFrameList144
  *((uint8_t *)this + 98) = 1;
  *(this + 25) = -16777216;  // this+100 = -16777216
  *(this + 44) = 1600;  // this+176 = 1600
  *((uint8_t *)this + 148) = 0;
  *((uint8_t *)this + 149) = 0;
  *((uint8_t *)this + 150) = 0;
  *((uint8_t *)this + 151) = 0;
  *(this + 40) = 0;  // this+160 = 0
  *(this + 41) = 6;  // this+164 = 6
  *(this + 42) = 12;  // this+168 = 12
  *(this + 43) = 0;  // this+172 = 0
  *(this + 45) = 0;  // this+180 = 0
  *(this + 46) = 0;  // this+184 = 0
  *(this + 47) = 0;  // this+188 = 0
  *(this + 48) = 0;  // this+192 = 0
  *(this + 49) = 0;  // this+196 = 0
  dword_99FCCC2 = dword_99FCCC;
  v17 = *this;
  *(this + 38) = -16777216;  // this+152 = -16777216
  *(this + 49) = dword_99FCCC2;  // this+196 = dword_99FCCC2
  *(this + 44) = 200;  // this+176 = 200
  *(this + 40) = 1;  // this+160 = 1
  *(this + 45) = 1;  // this+180 = 1
  *((uint8_t *)this + 150) = 1;
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(v17 + 28))(this, 2);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
}


// ------------------------------------------------------------
// 0x6312F0 sub_6312F0 —— 组队列表重建（251 行：4A2CF0 + 56A720/56A680 成员 + 52DAA0/468240/430C80 候选）
// ------------------------------------------------------------
void /*thiscall*/ sub_6312F0(uint32_t *this)  // 函数: 组队列表重建（251 行：4A2CF0 + 56A720/56A680 成员 + 52DAA0/468240/430C80 …
{
  uint32_t *pThis; // esi
  int fld_e9; // eax
  unsigned int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int pObj; // esi
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
  uint32_t *pThis22; // ecx
  bool v39; // cc
  uint32_t *Block2; // edi
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
  uint32_t *pThis2; // [esp+2Ch] [ebp-1Ch]
  int v56; // [esp+30h] [ebp-18h]
  int v57; // [esp+34h] [ebp-14h]
  unsigned int v58; // [esp+38h] [ebp-10h]
  int v59; // [esp+44h] [ebp-4h]

  pThis = this;
  fld_e9 = *(this + 9);  // this+36 = 状态字
  v3 = 0;
  pThis2 = this;
  if ( fld_e9 == 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  {
    v56 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v4 = v56;
    if ( v56 != 0 )  // 若 v56 != 0
    {
      v48 = (void *)sub_4A2CF0(v47);
      v49 = 0;
      v59 = 0;
      Block = (void *)sub_4A2CF0(v50);
      v52 = 0;
      LOBYTE(v59) = 1;  // 调 取 16 位值低 8 位
      v5 = sub_429830((uint16_t)word_77F804);  // 调 表按键查找（uint16）
      v54 = sub_41A5E0(v5 + 53);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      v6 = *(uint32_t *)(v4 + 8);  // v6 = v4+8
      if ( v6 != 0 )  // 若 v6 != 0
        v57 = (*(uint32_t *)(v4 + 12) - v6) >> 2;
      else
        v57 = 0;
      v58 = 0;
      if ( v57 > 0 )  // 若 v57 > 0
      {
        do
        {
          v7 = *(uint32_t *)(v4 + 8);  // v7 = v4+8
          if ( v7 != 0 && v3 < (*(uint32_t *)(v4 + 12) - v7) >> 2 )  // 若 v7 != 0 && v3 < (*(uint32_t *)(v4 + 12) - v7) >> 2
            pObj = *(uint32_t *)(v7 + 4 * v3);
          else
            pObj = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 18) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
          {
            v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调用虚函数（虚表槽 +52）
            v10 = sub_429830(v9);  // 调 表按键查找（uint16）
            if ( v10 != 0 )  // 若 v10 != 0
            {
              v11 = *(uint32_t *)(v10 + 184);  // v11 = v10+184
              if ( v11 != 0 )  // 若 v11 != 0
              {
                v12 = *(uint32_t *)(v10 + 184);  // v12 = v10+184
                v13 = *(uint32_t *)(v11 + 4);  // v13 = v11+4
                v14 = v47;
                if ( *(uint32_t *)(v12 + 60) - sub_56A720(v11) <= 0 )  // 调 组队列表联动（55 行）
                  v14 = v50;
                v15 = sub_56A680(*(uint32_t *)(v12 + 56));  // 调 频道对象辅助（429830）
                v16 = sub_41A5E0(v15 + 53);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
                v17 = *((uint32_t **)v14 + 1);
                v18 = (uint32_t *)*v17;
                for ( i = abs32(v16 - v54); v18 != v17; v18 = (uint32_t *)*v18 )  // 循环：i = abs32(v16 - v54); v18 != v17; v18 = (uint32_t *)*v18
                {
                  if ( v18[2] > i )  // 若 v18[2] > i
                    break;
                  if ( v18[3] == v13 )  // 若 v18[3] == v13
                    goto LABEL_22;  // 跳转 LABEL_22
                }
                v20 = v18[1];
                v53[0] = i;
                v53[1] = v13;
                v21 = sub_52DAA0(v18, v20, v53);  // 调 sub_52DAA0
                sub_468240(1);  // 调 list 元素数预留（溢出抛错）
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
        while ( (int)v3 < v57 );  // 当 (int)v3 < v57 循环
        pThis = pThis2;
      }
      v22 = (void *)pThis[17];
      v23 = pThis + 16;
      if ( v22 != nullptr )  // 若 v22 非空
        j__free(v22);  // 调 堆释放
      v24 = (uint32_t **)v48;
      v23[1] = 0;
      v23[2] = 0;
      v23[3] = 0;
      v25 = *v24;
      if ( *v24 != v24 )  // 若 *v24 != v24
      {
        do
        {
          v26 = v23[1];
          if ( v26 != 0 )  // 若 v26 != 0
            v27 = (v23[2] - v26) >> 2;
          else
            v27 = 0;
          if ( v26 != 0 && v27 < (v23[3] - v26) >> 2 )  // 若 v26 != 0 && v27 < (v23[3] - v26) >> 2
          {
            v28 = (uint32_t *)v23[2];
            *v28 = v25[3];  // *v28 写入 v25[3]
            v23[2] = v28 + 1;  // v23[2] 写入 v28 + 1
          }
          else
          {
            sub_430C80((void *)v23[2], 1, (int)(v25 + 3));  // 调 uint32 vector 区间插入（同值填充）
          }
          v25 = (uint32_t *)*v25;
        }
        while ( v25 != v48 );  // 当 v25 != v48 循环
      }
      for ( j = *(uint32_t **)Block; j != Block; j = (uint32_t *)*j )  // 循环：j = *(uint32_t **)Block; j != Block; j = (uint32_t *)*j
      {
        v30 = v23[1];
        if ( v30 != 0 )  // 若 v30 != 0
          v31 = (v23[2] - v30) >> 2;
        else
          v31 = 0;
        if ( v30 != 0 && v31 < (v23[3] - v30) >> 2 )  // 若 v30 != 0 && v31 < (v23[3] - v30) >> 2
        {
          v32 = (uint32_t *)v23[2];
          *v32 = j[3];  // *v32 写入 j[3]
          v23[2] = v32 + 1;  // v23[2] 写入 v32 + 1
        }
        else
        {
          sub_430C80((void *)v23[2], 1, (int)(j + 3));  // 调 uint32 vector 区间插入（同值填充）
        }
      }
      v33 = v23[1];
      if ( v33 != 0 )  // 若 v33 != 0
        v34 = (v23[2] - v33) >> 2;
      else
        v34 = 0;
      if ( (v34 - 1) / 7 <= 0 )  // 若 (v34 - 1) / 7 <= 0
      {
        v37 = 0;
      }
      else
      {
        v35 = v23[1];
        if ( v35 != 0 )  // 若 v35 != 0
          v36 = (v23[2] - v35) >> 2;
        else
          v36 = 0;
        v37 = (v36 - 1) / 7;
      }
      pThis22 = pThis2;
      v39 = pThis2[20] <= v37;
      pThis2[21] = v37;
      if ( !v39 )  // 若 !v39
        pThis22[20] = v37;
      Block2 = Block;
      v41 = *(uint32_t **)Block;
      v42 = *(uint32_t *)Block == (uint32_t)Block;
      *(uint32_t *)Block = Block;
      Block2[1] = Block2;
      if ( !v42 )  // 若 !v42
      {
        do
        {
          v43 = (uint32_t *)*v41;
          j__free(v41);  // 调 堆释放
          v41 = v43;
        }
        while ( v43 != Block2 );  // 当 v43 != Block2 循环
      }
      j__free(Block2);  // 调 堆释放
      v44 = v48;
      v45 = *(uint32_t **)v48;
      v42 = *(uint32_t *)v48 == (uint32_t)v48;
      *(uint32_t *)v48 = v48;
      v44[1] = v44;
      if ( !v42 )  // 若 !v42
      {
        do
        {
          v46 = (uint32_t *)*v45;
          j__free(v45);  // 调 堆释放
          v45 = v46;
        }
        while ( v46 != v44 );  // 当 v46 != v44 循环
      }
      j__free(v44);  // 调 堆释放
    }
  }
}


// ------------------------------------------------------------
// 0x631630 sub_631630 —— 组队列表刷新入口（630750 绘制 + 6312F0 重建）
// ------------------------------------------------------------
char /*thiscall*/ sub_631630(uint32_t *this, int nArg2)  // 函数: 组队列表刷新入口（630750 绘制 + 6312F0 重建）
{
  int fld_e9; // eax

  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( fld_e9 != nArg2 )  // 若 fld_e9 != nArg2
  {
    *(this + 9) = nArg2;  // this+36 = 状态字
    if ( nArg2 != 0 )  // 若 nArg2 != 0
    {
      if ( nArg2 == 1 )  // 若 nArg2 == 1
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 14);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
        sub_630750(this);  // 调 组队列表页绘制（456480/429830/456390/69C980，25 行）
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 19);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
      sub_6312F0(this);  // 调 组队列表重建（251 行：4A2CF0 + 56A720/56A680 成员 + 52DAA0/468240/430C80 …
    }
    *(uint8_t *)(*(this + 12) + 16) = nArg2 == 0;
    *(uint8_t *)(*(this + 13) + 16) = nArg2 == 0;  // this+52 = bAuraState
    *(uint8_t *)(*(this + 14) + 16) = nArg2 == 0;
    *(uint8_t *)(*(this + 22) + 16) = nArg2 == 1;  // this+88 = pFxObjB
    *(uint8_t *)(*(this + 23) + 16) = nArg2 == 1;  // this+92 = pFxObjC
    LOBYTE(fld_e9) = nArg2 == 1;  // 调 取 16 位值低 8 位
  }
  return fld_e9;
}



// ------------------------------------------------------------
// 0x6316A0 CNRDPartyListWindow__vmt8 —— CNRDPartyListWindow__vmt8 Update（137 行：CLICK_BUTTON2 + 423B10/526BF0 加入 + 6312F0 重建）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_6316A0(void *this)  // 【CNRDPartyListWindow__vmt8】
{
  int pThis_9; // eax
  int pThis_22; // eax
  int v4; // eax
  int pThis_11; // edx
  unsigned int pThis_12; // ecx
  unsigned int pThis_14; // eax
  int pThis_C; // eax
  int pThis_D; // eax
  int pThis_142; // eax
  int pThis_E; // eax
  int pThis_143; // eax
  int pThis_2; // eax
  int v14; // edx
  int v15; // eax
  int v16; // edi
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int pThis_16; // eax
  int pThis_17; // eax
  uint8_t *result; // eax

  sub_69A650(*((uint32_t *)this + 2));  // this+8 = 技能槽记录首字
  pThis_9 = *((uint32_t *)this + 9);  // this+36 = 状态字
  if ( pThis_9 != 0 )  // 若 pThis_9 != 0
  {
    if ( pThis_9 == 1 )  // 若 pThis_9 == 1
    {
      pThis_2 = *((uint32_t *)this + 2);  // this+8 = 技能槽记录首字
      if ( *(uint8_t *)(pThis_2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_2 + 12) )  // 若 *(uint8_t *)(pThis_2 + 17) != 0 && dword_79BE34 == *(uint32_t ..
      {
        v14 = *(uint32_t *)(pThis_2 + 20);  // v14 = pThis_2+20
        if ( pt.x >= v14 + 8 && pt.x < v14 + 250 )  // 若 pt.x >= v14 + 8 && pt.x < v14 + 250
        {
          v15 = *(uint32_t *)(pThis_2 + 24);  // v15 = pThis_2+24
          if ( pt.y >= v15 + 35 && pt.y < v15 + 59 )  // 若 pt.y >= v15 + 35 && pt.y < v15 + 59
          {
            v16 = sub_429830((uint16_t)word_77F804);  // 调 表按键查找（uint16）
            if ( sub_423B10(dword_8F850C) == v16 )  // 调 本机槽元素取用
            {
              sub_44E8D0(*((char **)this + 4), (void *)7, 0, 0);  // 调 对象池借出（按池号取可用对象）
              sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
            }
          }
        }
        v17 = sub_6306A0(this);  // 调 组队列表构建（57 行：456480/456390 组队查询 + 69C980）
        if ( v17 != -1 )  // 若 v17 != -1
        {
          v18 = sub_429830((uint16_t)word_77F804);  // 调 表按键查找（uint16）
          v19 = sub_636190(*(uint32_t *)(v18 + 184), v17);  // 调 组队成员数据（56A680，27 行）
          if ( v19 != 0 )  // 若 v19 != 0
          {
            v20 = sub_42B340(v19);  // 调 虚拟角色惰性创建（0x294 字节）
            sub_526BF0(v20, 1);  // 调 sub_526BF0
            sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
          }
        }
      }
      pThis_16 = *((uint32_t *)this + 22);  // this+88 = pFxObjB
      if ( *(uint8_t *)(pThis_16 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_16 + 12) )  // 若 *(uint8_t *)(pThis_16 + 17) != 0 && dword_79BE34 == *(uint32_t..
      {
        sub_44E8D0(*((char **)this + 4), (void *)7, 0, 0);  // 调 对象池借出（按池号取可用对象）
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
      }
      pThis_17 = *((uint32_t *)this + 23);  // this+92 = pFxObjC
      if ( *(uint8_t *)(pThis_17 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_17 + 12) )  // 若 *(uint8_t *)(pThis_17 + 17) != 0 && dword_79BE34 == *(uint32_t..
      {
        sub_423200(dword_8F7B08, 13);  // 【发送网络包API】
        sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
        goto LABEL_39;  // 跳转 LABEL_39
      }
    }
  }
  else
  {
    pThis_22 = *((uint32_t *)this + 2);  // this+8 = 技能槽记录首字
    if ( *(uint8_t *)(pThis_22 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_22 + 12) )  // 若 *(uint8_t *)(pThis_22 + 17) != 0 && dword_79BE34 == *(uint32_t..
    {
      v4 = sub_6306A0(this);  // 调 组队列表构建（57 行：456480/456390 组队查询 + 69C980）
      if ( v4 != -1 )  // 若 v4 != -1
      {
        pThis_11 = *((uint32_t *)this + 17);
        pThis_12 = pThis_11 != 0 ? (*((uint32_t *)this + 18) - pThis_11) >> 2 : 0;
        pThis_14 = 7 * *((uint32_t *)this + 20) + v4;  // this+80 = nAuraStage
        if ( pThis_14 < pThis_12 )  // 若 pThis_14 < pThis_12
        {
          sub_44E8D0(*((char **)this + 4), (void *)6, 0, *(uint32_t *)(*((uint32_t *)this + 17) + 4 * pThis_14));  // 调 对象池借出（按池号取可用对象）
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
        }
      }
    }
    pThis_C = *((uint32_t *)this + 12);
    if ( *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_C + 12) )  // 若 *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE34 == *(uint32_t ..
    {
      sub_44E8D0(*((char **)this + 4), (void *)7, 0, 0);  // 调 对象池借出（按池号取可用对象）
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    }
    pThis_D = *((uint32_t *)this + 13);  // this+52 = bAuraState
    if ( *(uint8_t *)(pThis_D + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_D + 12) )  // 若 *(uint8_t *)(pThis_D + 17) != 0 && dword_79BE34 == *(uint32_t ..
    {
      pThis_142 = *((uint32_t *)this + 20);  // this+80 = nAuraStage
      if ( pThis_142 > 0 )  // 若 pThis_142 > 0
      {
        *((uint32_t *)this + 20) = pThis_142 - 1;  // this+80 = nAuraStage
        sub_6312F0(this);  // 调 组队列表重建（251 行：4A2CF0 + 56A720/56A680 成员 + 52DAA0/468240/430C80 …
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
      }
    }
    pThis_E = *((uint32_t *)this + 14);
    if ( *(uint8_t *)(pThis_E + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_E + 12) )  // 若 *(uint8_t *)(pThis_E + 17) != 0 && dword_79BE34 == *(uint32_t ..
    {
      pThis_143 = *((uint32_t *)this + 20);  // this+80 = nAuraStage
      if ( pThis_143 < *((uint32_t *)this + 21) )  // this+84 = pFxObjA
      {
        *((uint32_t *)this + 20) = pThis_143 + 1;  // this+80 = nAuraStage
        sub_6312F0(this);  // 调 组队列表重建（251 行：4A2CF0 + 56A720/56A680 成员 + 52DAA0/468240/430C80 …
LABEL_39:
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
      }
    }
  }
  result = *((uint8_t **)this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}


// ------------------------------------------------------------
// 0x631980 CNRDPartyListWindow__vmtC —— CNRDPartyListWindow__vmtC 打开槽（429830 + 69A5F0 + 630750/6312F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyListWindow__vmtC(int this, int nArg2, int nArg3)  // 函数: CNRDPartyListWindow__vmtC 打开槽（429830 + 69A5F0 + 630750/6312F0）
{
  int v5; // ecx
  int nListMode; // eax  | +0x0024 → 列表模式（CNRDPartyListWindow；va=00631980）
  int v7; // edx
  int v8; // edx

  if ( sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) == 0 )  // 调 表按键查找（uint16）
    return 0;
  dword_9B9458 = this;
  sub_69A5F0(*(uint32_t **)(this + 8), 192, 55);  // 调 sub_69A5F0
  v5 = *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184);  // 调 表按键查找（uint16）
  nListMode = *(uint32_t *)(this + 36);  // this+144 = pFrameList144
  if ( v5 != 0 )  // 若 v5 != 0
  {
    if ( nListMode == 1 )  // 若 fld_24 == 1
      sub_630750((uint32_t *)this);  // 调 组队列表页绘制（456480/429830/456390/69C980，25 行）
    if ( *(uint32_t *)(this + 36) != 1 )  // this+144 = pFrameList144
    {
      v7 = *(uint32_t *)this;  // v7 = this
      *(uint32_t *)(this + 36) = 1;  // this+144 = pFrameList144
      (*(void (/*thiscall*/ **)(int, int, int))(v7 + 24))(this, 20, 14);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
      sub_630750((uint32_t *)this);  // 调 组队列表页绘制（456480/429830/456390/69C980，25 行）
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
    if ( nListMode == 0 )  // 若 fld_24 == 0
      sub_6312F0((uint32_t *)this);  // 调 组队列表重建（251 行：4A2CF0 + 56A720/56A680 成员 + 52DAA0/468240/430C80 …
    if ( *(uint32_t *)(this + 36) != 0 )  // this+144 = pFrameList144
    {
      v8 = *(uint32_t *)this;  // v8 = this
      *(uint32_t *)(this + 36) = 0;  // this+144 = pFrameList144
      (*(void (/*thiscall*/ **)(int, int, int))(v8 + 24))(this, 20, 19);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
      sub_6312F0((uint32_t *)this);  // 调 组队列表重建（251 行：4A2CF0 + 56A720/56A680 成员 + 52DAA0/468240/430C80 …
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
int /*thiscall*/ sub_631A90(uint32_t *this)  // 函数: PVP 频道数据（19 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = bAuraState
  *(this + 14) = 0;  // this+56 = 0
  *(this + 15) = 0;  // this+60 = 0
  *(this + 29) = 0;  // this+116 = 0
  *(this + 30) = 0;  // this+120 = 动画对象指针
  return 0;
}



// ------------------------------------------------------------
// 0x631AC0 sub_631AC0 —— PVP 频道列表构建（26 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_631AC0(uint32_t *this)  // 函数: PVP 频道列表构建（26 行）
{
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  int result; // eax
  uint32_t *pThis_B; // esi
  int i; // edi

  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);  // this+40 = 状态子标志
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    result = (**fld_e10)(fld_e10, 1);
  *(this + 10) = 0;  // this+40 = 状态子标志
  pThis_B = this + 11;
  for ( i = 5; i != 0; --i )  // 循环：i = 5; i != 0; --i
  {
    if ( *pThis_B != 0 )  // 若 *pThis_B != 0
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_B)(*pThis_B, 1);
    *pThis_B++ = 0;  // *pThis_B++ 写入 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x631B10 sub_631B10 —— PVP 频道条目（23 行）
// ------------------------------------------------------------
int /*stdcall*/ sub_631B10(int nArg1, int nArg2)  // 函数: PVP 频道条目（23 行）
{
  int nArg22; // ecx
  int v3; // eax

  nArg22 = nArg2;
  if ( nArg2 < 1 )  // 若 nArg2 < 1
    nArg22 = 1;
  v3 = 100 * nArg1 / nArg22;
  if ( v3 <= 25 )  // 若 v3 <= 25
    return 243;
  if ( v3 <= 50 )  // 若 v3 <= 50
    return 242;
  if ( v3 > 75 )  // 若 v3 > 75
    return v3 > 100 ? 274 : 240;
  return 241;
}



// ------------------------------------------------------------
// 0x631B70 sub_631B70 —— PVP 频道辅助（11 行）
// ------------------------------------------------------------
bool sub_631B70()  // 函数: PVP 频道辅助（11 行）
{
  return dword_8F7C04 != 0  // dword_8F7C04 = 本地玩家对象
      && *(int *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) >= 10;  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
}



// ------------------------------------------------------------
// 0x631B90 sub_631B90 —— PVP 频道页绘制（69C980/69A5F0，95 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_631B90(uint32_t *this)  // 函数: PVP 频道页绘制（69C980/69A5F0，95 行）
{
  int v2; // ecx
  int result; // eax
  int v4; // esi
  int fld_e2; // eax
  int v6; // ebx
  uint32_t **pThis_B; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // [esp+8h] [ebp-10h]
  int v11; // [esp+Ch] [ebp-Ch]
  unsigned int v12; // [esp+10h] [ebp-8h]
  uint32_t *pThis; // [esp+14h] [ebp-4h]

  v2 = 140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 740;  // dword_8F7A24 = 当前场景状态对象
  result = *(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 744);  // dword_8F7A24 = 当前场景状态对象
  v4 = 0;
  pThis = this;
  v11 = v2;
  if ( result != 0 )  // 若 result != 0
  {
    result = (*(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 748)  // dword_8F7A24 = 当前场景状态对象
            - result)
           / 104;
    if ( result != 0 )  // 若 result != 0
    {
      fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
      v6 = *(uint32_t *)(fld_e2 + 24) + 37;
      v10 = *(uint32_t *)(fld_e2 + 20) + 14;
      v12 = 0;
      pThis_B = (uint32_t **)(this + 11);
      do
      {
        v8 = *(uint32_t *)(v2 + 4);  // v8 = v2+4
        if ( v8 != 0 && v12 < (*(uint32_t *)(v11 + 8) - v8) / 104 )  // 若 v8 != 0 && v12 < (*(uint32_t *)(v11 + 8) - v8) / 104
        {
          sub_69C980(
            pThis[9],
            dword_73DE70[4 * *(char *)(v4 + v8 + 100)],
            dword_73DE74[4 * *(char *)(v4 + v8 + 100)],
            dword_73DE78[4 * *(char *)(v4 + v8 + 100)],
            dword_73DE78[4 * *(char *)(v4 + v8 + 100)],
            0,
            0);
          sub_69A5F0(*pThis_B, v10, v6);  // 调 sub_69A5F0
          v6 += 52;
          *((uint8_t *)*pThis_B + 16) = 1;
        }
        else
        {
          *((uint8_t *)*pThis_B + 16) = 0;
        }
        v2 = v11;
        v4 += 104;
        ++pThis_B;  // 自增pThis_B
        ++v12;  // 自增v12
      }
      while ( v4 < 520 );  // 当 v4 < 520 循环
      v9 = *(uint32_t *)(v11 + 4);  // v9 = v11+4
      if ( v9 != 0 )  // 若 v9 != 0
        v9 = (*(uint32_t *)(v11 + 8) - v9) / 104;
      switch ( v9 )  // 分支：按 v9 分派
      {
        case 0:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pThis + 24))(pThis, 20, 7);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
          return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pThis + 28))(pThis, 2);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
        case 1:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pThis + 24))(pThis, 20, 7);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
          goto LABEL_18;  // 跳转 LABEL_18
        case 2:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pThis + 24))(pThis, 20, 10);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
          return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pThis + 28))(pThis, 2);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
        case 3:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pThis + 24))(pThis, 20, 14);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
          goto LABEL_18;  // 跳转 LABEL_18
        case 4:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pThis + 24))(pThis, 20, 18);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
          return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pThis + 28))(pThis, 2);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
        default:
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pThis + 24))(pThis, 20, 22);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
LABEL_18:
          result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pThis + 28))(pThis, 2);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
          break;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x631D70 sub_631D70 —— PVP 频道辅助（429830）
// ------------------------------------------------------------
bool /*stdcall*/ sub_631D70(int nArg1)  // 函数: PVP 频道辅助（429830）
{
  int v1; // eax
  int v2; // ecx
  int v3; // edi
  int v4; // eax

  v1 = *(uint32_t *)(dword_8F7A24 + 36);  // dword_8F7A24 = 当前场景状态对象
  v2 = 140 * *(uint32_t *)(v1 + 12);
  v3 = v2 + v1 + 740;
  v4 = *(uint32_t *)(v2 + v1 + 744);
  if ( v4 == 0 || (*(uint32_t *)(v3 + 8) - v4) / 104 == 0 )  // 若 v4 == 0 || (*(uint32_t *)(v3 + 8) - v4) / 104 == 0
    return false;
  return sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0  // 调 表按键查找（uint16）
      && *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 116) >= *(char *)(104 * nArg1 + *(uint32_t *)(v3 + 4) + 98)  // 调 表按键查找（uint16）
      && *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 116) <= *(char *)(*(uint32_t *)(v3 + 4) + 104 * nArg1 + 99);  // 调 表按键查找（uint16）
}



// ------------------------------------------------------------
// 0x631E40 sub_631E40 —— PVP 频道页绘制 2（43C410/69A5F0/69A840 + 426BD0/69C780，74 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_631E40(int this)  // 函数: PVP 频道页绘制 2（43C410/69A5F0/69A840 + 426BD0/69C780，74 行）
{
  uint32_t *pMem; // eax
  uint32_t *fld_24; // eax
  uint32_t *pThis_2C; // ebx
  uint8_t *pMem2; // edi
  bool v6; // zf
  void *Block; // [esp+10h] [ebp-18h]
  int v9; // [esp+14h] [ebp-14h]
  int v10; // [esp+18h] [ebp-10h]

  *(uint32_t *)(this + 36) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+144 = pFrameList144
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_24 = sub_43C410(pMem, *(uint32_t *)(this + 36), 23, 24, 25, 23, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_24 = nullptr;  // fld_24 = nullptr 空指针
  *(uint32_t *)(this + 40) = fld_24;  // this+40 = fld_24
  sub_69A5F0(fld_24, 230, 11);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 40));  // 调 sub_69A840
  v10 = 37;
  pThis_2C = (uint32_t *)(this + 44);
  v9 = 5;
  do
  {
    pMem2 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem2 != nullptr )  // 若 pMem2 非空
    {
      Block = *(void **)(this + 36);  // this+144 = pFrameList144
      sub_426BD0(pMem2);  // 调 nengine::IControl 构造
      *(uint32_t *)pMem2 = &vftbl_nengine__CNButton;
      sub_69C780(pMem2);  // 调 sub_69C780
      nengine__CNButton__vmt20(Block, 223, 223, 223, 223, 0, 0);
    }
    else
    {
      pMem2 = nullptr;  // pMem2 = nullptr 空指针
    }
    *pThis_2C = pMem2;  // *pThis_2C 写入 pMem2
    sub_69A5F0(pMem2, 14, v10);  // 调 sub_69A5F0
    *(uint32_t *)(*pThis_2C + 68) = this;
    sub_69A840(*pThis_2C++);  // 调 sub_69A840
    v6 = v9 == 1;
    v10 += 52;
    --v9;  // 自减v9
  }
  while ( !v6 );  // 当 !v6 循环
  *(uint8_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  *(uint8_t *)(this + 65) = 0;  // this+260 = 基类四元组 dword 槽 4
  *(uint8_t *)(this + 66) = 0;  // this+66 = 0
  *(uint8_t *)(this + 67) = 0;  // this+67 = 0
  *(uint32_t *)(this + 76) = 0;  // this+76 = 0
  *(uint32_t *)(this + 80) = 6;  // this+80 = 6
  *(uint32_t *)(this + 84) = 12;  // this+84 = 12
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 92) = 1600;  // this+92 = 1600
  *(uint32_t *)(this + 96) = 0;  // this+384 = 动画件名 SSO 容量判据
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  *(uint32_t *)(this + 104) = 0;  // this+104 = 0
  *(uint32_t *)(this + 108) = 0;  // this+108 = 0
  *(uint32_t *)(this + 112) = 0;  // this+112 = 0
  *(uint32_t *)(this + 112) = dword_99FCCC;  // this+112 = dword_99FCCC
  *(uint32_t *)(this + 68) = -16777216;  // this+68 = -16777216
  *(uint32_t *)(this + 92) = 200;  // this+92 = 200
  *(uint32_t *)(this + 76) = 0;  // this+76 = 0
  *(uint32_t *)(this + 96) = 1;  // this+384 = 动画件名 SSO 容量判据
  return 0;
}



// ============================================================
// 【分区 3】PVP 频道列表 CNRDPVPChannelListWindow（0x631FF0-0x632630）
// vmt0 构造（171 行）、vmt8 Update（46E350/471CC0 频道进入）。
// ============================================================
// ------------------------------------------------------------
// 0x631FF0 CNRDPVPChannelListWindow__vmt0 —— CNRDPVPChannelListWindow__vmt0 构造（171 行：554930 + 631B10/631D70/631B70 + 42A210）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_631FF0(int this, int pArg2)  // 【CNRDPVPChannelListWindow__vmt0】
{
  int v4; // edi
  int pObj3; // eax
  int v6; // edi
  unsigned int result; // eax
  char *v8; // ebx
  int pThis_4; // eax
  int pObj; // eax
  int pThis_42; // eax
  int pObj2; // eax
  char v13; // al
  const CHAR *v14; // eax
  int pThis_43; // ecx
  int v16; // eax
  int pThis_44; // eax
  int v18; // ebx
  int v19; // eax
  int pObj4; // eax
  int v21; // ecx
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int pThis_45; // esi
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

  sub_554930(pArg2);  // 【IRDPopupWindow__vmt0】
  if ( pArg2 == *(uint32_t *)(this + 8) )  // 若 pArg2 == *(uint32_t *)(this + 8)
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v36 = *(uint32_t *)(pArg2 + 24);  // v36 = pArg2+24
    pObj3 = sub_418DD0(20);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v4 + 6, v36 + 6, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  }
  v6 = 0;
  result = this + 44;
  while ( *(uint32_t *)result == 0 || *(uint32_t *)result != pArg2 )  // 当 *(uint32_t *)result == 0 || *(uint32_t *)result != pArg2 循环
  {
    ++v6;  // 自增v6
    result += 4;
    if ( v6 >= 5 )  // 若 v6 >= 5
      return result;
  }
  if ( *(uint8_t *)(this + 124) != 0 )  // 若 *(uint8_t *)(this + 124) != 0
  {
    result = *(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 744);  // dword_8F7A24 = 当前场景状态对象
    if ( result != 0 )  // 若 result != 0
    {
      result = (int)(*(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12)  // dword_8F7A24 = 当前场景状态对象
                               + *(uint32_t *)(dword_8F7A24 + 36)  // dword_8F7A24 = 当前场景状态对象
                               + 748)
                   - result)
             / 104;
      if ( v6 < result )  // 若 v6 < result
      {
        v8 = (char *)(*(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12)  // dword_8F7A24 = 当前场景状态对象
                                + *(uint32_t *)(dword_8F7A24 + 36)  // dword_8F7A24 = 当前场景状态对象
                                + 744)
                    + 104 * v6);
        v31 = v8;
        if ( (uint8_t)sub_43BCB0(*(uint32_t *)(this + 4 * v6 + 44)) != 0 )  // 调 焦点窗口判定（三选）
        {
          sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          pThis_4 = *(uint32_t *)(this + 4 * v6 + 44);
          v37 = *(uint32_t *)(pThis_4 + 24);  // v37 = pThis_4+24
          v33 = *(uint32_t *)(pThis_4 + 20);  // v33 = pThis_4+20
          pObj = sub_418DD0(235);  // 调 sub_418DD0
          if ( pObj != 0 )  // 若 pObj != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v33, v37, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
        }
        pThis_42 = *(uint32_t *)(this + 4 * v6 + 44);
        v38 = *(uint32_t *)(pThis_42 + 24);  // v38 = pThis_42+24
        v34 = *(uint32_t *)(pThis_42 + 20);  // v34 = pThis_42+20
        pObj2 = sub_418DD0(dword_73DE7C[4 * v8[100]]);  // 调 sub_418DD0
        if ( pObj2 != 0 )  // 若 pObj2 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v34 + 50, v38 + 15, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 64);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
        v13 = v8[99];
        if ( v13 == -1 )  // 若 v13 == -1
          v14 = szPassword;
        else
          v14 = (const CHAR *)sub_42A210(v13);  // 调 串 id 偏移取串（+1207）
        pThis_43 = *(uint32_t *)(this + 4 * v6 + 44);
        v30 = v14;
        v39 = *(uint32_t *)(pThis_43 + 24);  // v39 = pThis_43+24
        v35 = *(uint32_t *)(pThis_43 + 20);  // v35 = pThis_43+20
        v32 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
        v16 = sub_42A210(v8[98]);  // 调 串 id 偏移取串（+1207）
        (*(void (**)(int, int, int, int, const char *, ...))(v32 + 80))(  // 调用虚函数（虚表槽 +80）
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          v35 + 122,
          v39 + 21,
          -1,
          "(%s ~ %s)",
          v16,
          v30);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
        pThis_44 = *(uint32_t *)(this + 4 * v6 + 44);
        v18 = *(uint32_t *)(pThis_44 + 24);  // v18 = pThis_44+24
        v40 = *(uint32_t *)(pThis_44 + 20);  // v40 = pThis_44+20
        v19 = sub_631B10(*((uint32_t *)v31 + 15), *((uint32_t *)v31 + 14));  // 调 PVP 频道条目（23 行）
        pObj4 = sub_418DD0(v19);  // 调 sub_418DD0
        if ( pObj4 != 0 )  // 若 pObj4 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v40 + 193, v18 + 15, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        if ( (uint8_t)sub_631D70(v6) != 1  // 调 PVP 频道辅助（429830）
          || dword_8F7C04 == 0  // dword_8F7C04 = 本地玩家对象
          || *(int *)(result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3)) < 10 )  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
        {
          result = *(uint32_t *)(this + 4 * v6 + 44);
          if ( pt.x >= *(uint32_t *)(result + 20)  // 若 pt.x >= *(uint32_t *)(result + 20
            && pt.x <= *(uint32_t *)(result + 20) + *(uint32_t *)(*(uint32_t *)(result + 116) + 20)
            && pt.y >= *(uint32_t *)(result + 24)
            && pt.y <= *(uint32_t *)(result + 24) + *(uint32_t *)(*(uint32_t *)(result + 116) + 24) )
          {
            v21 = *(uint32_t *)(result + 116);  // v21 = result+116
            v22 = *(uint32_t *)(result + 20) + (*(uint32_t *)(v21 + 20) >> 1);
            v41 = (*(uint32_t *)(v21 + 24) >> 1) + *(uint32_t *)(result + 24) + 10;
            if ( (uint8_t)sub_631B70(this) != 0 )  // 调 PVP 频道辅助（11 行）
            {
              result = sub_631D70(v6);  // 调 PVP 频道辅助（429830）
              if ( (uint8_t)result == 0 )  // 若 (uint8_t)result == 0
              {
                v24 = sub_422E70(1247);  // 调 sub_422E70
                return sub_4649B0(v22, v41, -1, -16777216, 2, v24, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
              }
            }
            else
            {
              v23 = sub_422E70(1248);  // 调 sub_422E70
              return sub_4649B0(v22, v41, -1, -16777216, 2, v23, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
            }
          }
        }
      }
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 64);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    pThis_45 = *(uint32_t *)(this + 4 * v6 + 44);
    v26 = *(uint32_t *)(pThis_45 + 24);  // v26 = pThis_45+24
    v27 = *(uint32_t *)(pThis_45 + 20);  // v27 = pThis_45+20
    v28 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    v29 = sub_422E70(1242);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v28 + 80))(dword_79C0B0, v27 + 67, v26 + 16, -1, v29);  // 调用虚函数（虚表槽 +80）
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  }
  return result;
}


// ------------------------------------------------------------
// 0x6323B0 sub_6323B0 —— PVP 频道点击（46EAA0 进入 + 41D520 + CLICK_BUTTON2）
// ------------------------------------------------------------
unsigned int /*stdcall*/ sub_6323B0(unsigned int pArg1)  // 函数: PVP 频道点击（46EAA0 进入 + 41D520 + CLICK_BUTTON2）
{
  unsigned int result; // eax
  int v2; // esi

  result = 140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 740;  // dword_8F7A24 = 当前场景状态对象
  v2 = *(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 744);  // dword_8F7A24 = 当前场景状态对象
  if ( v2 != 0 )  // 若 v2 != 0
  {
    result = (*(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 748)  // dword_8F7A24 = 当前场景状态对象
            - v2)
           / 104;
    if ( result > pArg1 )  // 若 result > pArg1
    {
      if ( 104 * pArg1 + 64 + strlen((const char *)(v2 + 104 * pArg1 + 64)) + 1 != 104 * pArg1 + 65  // 调 返回字符串长度（逐字节扫描）
        && sub_631D70(pArg1)  // 调 PVP 频道辅助（429830）
        && dword_8F7C04 != 0  // dword_8F7C04 = 本地玩家对象
        && *(int *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) >= 10 )  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      {
        sub_46EAA0(*(uint32_t **)(dword_8F7A24 + 36), *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12), 4, pArg1);  // dword_8F7A24 = 当前场景状态对象
        sub_41D520(dword_8F7A24);  // 调 切换到模块 5 的切换流程
      }
      return (unsigned int)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x632470 sub_632470 —— PVP 频道刷新（631D70 + 631B10，54 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_632470(int *this, char pszArg2)  // 函数: PVP 频道刷新（631D70 + 631B10，54 行）
{
  int v2; // eax
  int v3; // ebx
  int v4; // esi
  int *pThis_B; // edi
  int v7; // [esp+8h] [ebp-8h]

  v2 = *(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 744);  // dword_8F7A24 = 当前场景状态对象
  v7 = 140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 740;  // dword_8F7A24 = 当前场景状态对象
  if ( v2 != 0 )  // 若 v2 != 0
  {
    v2 = (*(uint32_t *)(140 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12) + *(uint32_t *)(dword_8F7A24 + 36) + 748) - v2)  // dword_8F7A24 = 当前场景状态对象
       / 104;
    if ( v2 != 0 )  // 若 v2 != 0
    {
      v3 = 0;
      v4 = 0;
      pThis_B = this + 11;
      do
      {
        v2 = *pThis_B;
        if ( *pThis_B != 0 )  // 若 *pThis_B != 0
        {
          *(uint8_t *)(v2 + 17) = pszArg2;  // v2+17 = pszArg2
          if ( pszArg2 == 1 )  // 若 pszArg2 == 1
          {
            LOBYTE(v2) = sub_631D70(v3);  // 调 PVP 频道辅助（429830）
            if ( (uint8_t)v2 == 0
              || dword_8F7C04 == 0  // dword_8F7C04 = 本地玩家对象
              || *(int *)(v2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3)) < 10  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
              || (v2 = sub_631B10(  // 调 PVP 频道条目（23 行）
                         *(uint32_t *)(v4 + *(uint32_t *)(v7 + 4) + 60),
                         *(uint32_t *)(v4 + *(uint32_t *)(v7 + 4) + 56))) == 274 )
            {
              *(uint8_t *)(*pThis_B + 17) = 0;
            }
          }
        }
        v4 += 104;
        ++v3;  // 自增v3
        ++pThis_B;  // 自增pThis_B
      }
      while ( v4 < 520 );  // 当 v4 < 520 循环
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x632540 CNRDPVPChannelListWindow__vmt8 —— CNRDPVPChannelListWindow__vmt8 Update（48 行：CLICK_BUTTON2 + 46E350/632470/6323B0/471CC0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPVPChannelListWindow__vmt8(int this)  // 函数: CNRDPVPChannelListWindow__vmt8 Update（48 行：CLICK_BUTTON2 + 46E350/632470/6323B0/471CC0）
{
  int pBtnClose; // eax  | +0x0028 → 关闭/返回按钮（CNRDPVPChannelListWindow；va=00632540）
  signed int v3; // edi
  int *pThis_2C; // ebx
  int v5; // eax

  sub_69A650(*(uint32_t *)(this + 8));  // 调 sub_69A650
  pBtnClose = *(uint32_t *)(this + 40);  // fld_28 = this+40
  if ( *(uint8_t *)(pBtnClose + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnClose + 12) )  // 若 *(uint8_t *)(fld_28 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  if ( *(uint8_t *)(this + 124) != 0 )  // 若 *(uint8_t *)(this + 124) != 0
    goto LABEL_8;  // 跳转 LABEL_8
  if ( sub_46E350() )  // 调 HTTP 频道列表线程空闲判定
  {
    sub_632470((int *)this, 1);  // 调 PVP 频道刷新（631D70 + 631B10，54 行）
    *(uint8_t *)(this + 124) = 1;  // this+124 = 1
  }
  if ( *(uint8_t *)(this + 124) != 0 )  // 若 *(uint8_t *)(this + 124) != 0
  {
LABEL_8:
    v3 = 0;
    pThis_2C = (int *)(this + 44);
    do
    {
      v5 = *pThis_2C;
      if ( *pThis_2C != 0 && *(uint8_t *)(v5 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v5 + 12) )  // 若 *pThis_2C != 0 && *(uint8_t *)(v5 + 17) != 0 && dword_79BE34 =..
        LOBYTE(v5) = sub_6323B0(v3);  // 调 PVP 频道点击（46EAA0 进入 + 41D520 + CLICK_BUTTON2）
      ++v3;  // 自增v3
      ++pThis_2C;  // 自增pThis_2C
    }
    while ( v3 < 5 );  // 当 v3 < 5 循环
  }
  else
  {
    LOBYTE(v5) = sub_471CC0(*(uint32_t *)(dword_8F7A24 + 36));  // 调 取 16 位值低 8 位
  }
  return v5;
}



// ------------------------------------------------------------
// 0x6325F0 CNRDPVPChannelListWindow__vmtC —— CNRDPVPChannelListWindow__vmtC 打开槽（69A5F0 + 631B90/632470 + 46F3E0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPVPChannelListWindow__vmtC(int this, int nArg2, int nArg3)  // 函数: CNRDPVPChannelListWindow__vmtC 打开槽（69A5F0 + 631B90/632470 + 46F3E0）
{
  sub_69A5F0(*(uint32_t **)(this + 8), 192, 55);  // 调 sub_69A5F0
  sub_631B90((uint32_t *)this);  // 调 PVP 频道页绘制（69C980/69A5F0，95 行）
  dword_9B945C = this;
  *(uint8_t *)(this + 124) = 0;  // this+124 = 0
  sub_632470((int *)this, 0);  // 调 PVP 频道刷新（631D70 + 631B10，54 行）
  sub_46F3E0(*(uint32_t *)(dword_8F7A24 + 36));  // 调 频道列表手动刷新（5000ms 节流）
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
int /*thiscall*/ sub_632630(uint32_t *this)  // 函数: 推荐用户数据（37 行）
{
  void (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  uint32_t *pThis_B; // esi
  int i; // ebx
  void (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e14)(uint32_t, int); // ecx
  int result; // eax

  fld_e10 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);  // this+40 = 状态子标志
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    (**fld_e10)(fld_e10, 1);
  *(this + 10) = 0;  // this+40 = 状态子标志
  pThis_B = this + 11;
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    if ( *pThis_B != 0 )  // 若 *pThis_B != 0
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_B)(*pThis_B, 1);
    *pThis_B++ = 0;  // *pThis_B++ 写入 0
  }
  fld_e13 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 13);  // this+52 = bAuraState
  if ( fld_e13 != nullptr )  // 若 fld_e13 非空
    (**fld_e13)(fld_e13, 1);
  fld_e14 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  result = 0;
  *(this + 13) = 0;  // this+52 = bAuraState
  if ( fld_e14 != nullptr )  // 若 fld_e14 非空
    result = (**fld_e14)(fld_e14, 1);
  *(this + 14) = 0;  // this+56 = 0
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
int /*thiscall*/ sub_6326B0(uint32_t *this)  // 函数: 推荐用户选中处理（27 行）
{
  int fld_e2; // eax
  LONG v2; // ecx
  LONG v3; // edx
  int result; // eax
  LONG i; // esi

  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  v2 = *(uint32_t *)(fld_e2 + 24) + 35;
  v3 = *(uint32_t *)(fld_e2 + 20) + 8;
  result = 0;
  for ( i = v2 + 18; pt.x < v3 || pt.x >= v3 + 229 || pt.y < v2 || pt.y >= i; i += 18 )  // 循环：i = v2 + 18; pt.x < v3 || pt.x >= v3 + 229 || pt.y < v2 || p
  {
    ++result;  // 自增result
    v2 += 18;
    if ( result >= 5 )  // 若 result >= 5
      return -1;  // 返回 -1（0xFFFFFFFF）
  }
  return result;
}



// ------------------------------------------------------------
// 0x632710 CNRDPartyRecommendUserWindow__vmt8 —— CNRDPartyRecommendUserWindow__vmt8 Update（54 行：CLICK_BUTTON2 + 69C690 + 526BF0 邀请）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDPartyRecommendUserWindow__vmt8(uint32_t *this)
{
  int fld_e10; // eax
  int fld_e2; // eax
  int v4; // ebx
  int fld_e42; // eax
  unsigned int fld_e43; // edi
  int fld_e14; // eax
  int fld_e422; // eax
  uint32_t *pThis_B; // esi
  int i; // edi
  uint32_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e10 = *(this + 10);  // this+40 = 状态子标志
  if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )  // 若 *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  if ( *(uint8_t *)(fld_e2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e2 + 12) )  // 若 *(uint8_t *)(fld_e2 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    v4 = sub_6326B0(this);  // 调 推荐用户选中处理（27 行）
    if ( v4 != -1 )  // 若 v4 != -1
    {
      fld_e42 = *(this + 42);  // fld_e42 = this+42
      fld_e43 = fld_e42 != 0 ? (*(this + 43) - fld_e42) >> 2 : 0;
      if ( v4 + sub_69C690(*(this + 14)) < fld_e43 )  // 调 取设备对象 +112 字段（类型或句柄）
      {
        fld_e14 = sub_69C690(*(this + 14));  // 调 取设备对象 +112 字段（类型或句柄）
        fld_e422 = sub_429830((uint32_t *)dword_8F8500, *(uint16_t *)(*(this + 42) + 4 * (v4 + fld_e14)));  // 调 表按键查找（uint16）
        if ( fld_e422 != 0 )  // 若 fld_e422 != 0
          sub_526BF0(*(uint32_t *)(*(this + 4) + 48), *(int **)(fld_e422 + 192), 1);  // 调 sub_526BF0
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
      }
    }
  }
  pThis_B = this + 11;
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    result = (uint32_t *)*pThis_B;
    if ( *(uint8_t *)(*pThis_B + 17) != 0 && dword_79BE34 == result[3] )  // 若 *(uint8_t *)(*pThis_B + 17) != 0 && dword_79BE34 == result[3]
      result = sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    ++pThis_B;  // 自增pThis_B
  }
  return result;
}



// ------------------------------------------------------------
// 0x632830 CNRDPartyRecommendUserWindow__vmt0 —— CNRDPartyRecommendUserWindow__vmt0 构造（132 行：554930 + 69C690/6326B0/42B340）
// ------------------------------------------------------------
char /*thiscall*/ sub_632830(uint32_t *this, int pArg2)  // 【CNRDPartyRecommendUserWindow__vmt0】
{
  unsigned int fld_e14; // eax
  int v4; // esi
  int v5; // ebx
  int pObj2; // eax
  int v7; // ebx
  int fld_e2; // ecx
  unsigned int fld_e142; // esi
  int v10; // ebx
  int fld_e42; // ecx
  uint32_t *v12; // eax
  uint32_t *v13; // esi
  int pObj4; // eax
  int v15; // eax
  uint32_t *v16; // ecx
  int v17; // eax
  int pObj3; // eax
  bool v19; // cc
  int pObj; // [esp+8h] [ebp-14h]
  int v22; // [esp+8h] [ebp-14h]
  int fld_e143; // [esp+Ch] [ebp-10h]
  int v24; // [esp+10h] [ebp-Ch]
  unsigned int fld_e1422; // [esp+14h] [ebp-8h]
  int v26; // [esp+18h] [ebp-4h]
  int v27; // [esp+24h] [ebp+8h]

  LOBYTE(fld_e14) = sub_554930(pArg2);  // 【IRDPopupWindow__vmt0】
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
    pObj2 = sub_418DD0(19);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v4 + 6, v5 + 6, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v7 = v5 + 35;
    v27 = v4 + 8;
    v24 = v7;
    fld_e14 = sub_69C690(*(this + 14));  // 调 取设备对象 +112 字段（类型或句柄）
    fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
    fld_e142 = fld_e14;
    LOBYTE(fld_e14) = *(uint8_t *)(fld_e2 + 17);  // 调 取 16 位值低 8 位
    fld_e1422 = fld_e142;
    if ( (uint8_t)fld_e14 != 0
      && (dword_79BE3C == *(uint32_t *)(fld_e2 + 12)
       || dword_79BE34 == *(uint32_t *)(fld_e2 + 12)
       || (LOBYTE(fld_e14) = dword_79BE38, dword_79BE38 == *(uint32_t *)(fld_e2 + 12))) )  // 调 取 16 位值低 8 位
    {
      fld_e14 = sub_6326B0(this);  // 调 推荐用户选中处理（27 行）
      fld_e143 = fld_e14;
      v26 = 0;
      v10 = v7 + 4;
    }
    else
    {
      fld_e143 = -1;
      v26 = 0;
      v10 = v7 + 4;
    }
    while ( 1 )  // 无限循环
    {
      fld_e42 = *(this + 42);  // fld_e42 = this+42
      if ( fld_e42 == 0 )  // 若 fld_e42 == 0
        break;
      fld_e14 = (*(this + 43) - fld_e42) >> 2;
      if ( fld_e142 >= fld_e14 )  // 若 fld_e142 >= fld_e14
        break;
      v12 = (uint32_t *)sub_429830(*(uint16_t *)(fld_e42 + 4 * fld_e142));  // 调 表按键查找（uint16）
      v13 = v12;
      if ( v12 != nullptr )  // 若 v12 非空
      {
        pObj = sub_42B340(v12);  // 调 虚拟角色惰性创建（0x294 字节）
        pObj4 = sub_418DD0(94);  // 调 sub_418DD0
        if ( pObj4 != 0 )  // 若 pObj4 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v27 + 1, v10 - 3, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj + 384))(  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
          pObj,
          v27 + 1,
          v10 - 3,
          16,
          16,
          1065353216);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 15);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
        v15 = sub_41A5E0((unsigned int)v13 + 53);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          v27 + 27,
          v10,
          -4928551,
          "Lv.%d",
          v15);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, this + 28);  // 调用虚函数（虚表槽 +68）【推断: 观察者组件懒创建（0x10 字节）】
        if ( v13[10] < 0x10u )  // 若 v13[10] < 0x10u
          v16 = v13 + 5;
        else
          v16 = (uint32_t *)v13[5];
        (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          v27 + 23,
          v10,
          -4928551,
          v16);
        v22 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
        v17 = sub_4B0EC0(v13[11], v13[12]);  // 调 表记录字符串取值（28 字节/条）
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v22 + 80))(dword_79C0B0, v27 + 104, v10, -8005942, v17);  // 调用虚函数（虚表槽 +80）
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
        if ( v26 == fld_e143 )  // 若 v26 == fld_e143
        {
          sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          pObj3 = sub_418DD0(22);  // 调 sub_418DD0
          if ( pObj3 != 0 )  // 若 pObj3 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v27, v24, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
        }
      }
      LOBYTE(fld_e14) = v26 + 1;  // 调 取 16 位值低 8 位
      v10 += 18;
      v19 = ++v26 < 5;
      ++fld_e1422;  // 自增fld_e1422
      v24 += 18;
      if ( !v19 )  // 若 !v19
        break;
      fld_e142 = fld_e1422;
    }
  }
  return fld_e14;
}


// ------------------------------------------------------------
// 0x632AA0 sub_632AA0 —— 推荐用户页绘制（117 行：43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630）
// ------------------------------------------------------------
int /*thiscall*/ sub_632AA0(uint32_t *this)  // 函数: 推荐用户页绘制（117 行：43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA…
{
  uint32_t *pMem; // eax
  uint32_t *fld_e9; // eax
  uint8_t *pMem2; // edi
  uint8_t *pMem3; // eax
  uint32_t *pMem32; // edi
  uint32_t *pMem322; // eax
  uint32_t *fld_e11; // eax
  int dword_99FCCC2; // ecx
  int v10; // edx
  void *Block; // [esp+10h] [ebp-18h]
  void *Blocka; // [esp+10h] [ebp-18h]
  uint32_t *pThis_B; // [esp+14h] [ebp-14h]
  int v15; // [esp+18h] [ebp-10h]

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+36 = 状态字
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e9 = sub_43C410(pMem, *(this + 9), 23, 24, 25, 23, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 10) = fld_e9;  // this+40 = 状态子标志
  sub_69A5F0(fld_e9, 230, 11);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  v15 = 4;
  pThis_B = this + 11;
  do
  {
    pMem2 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem2 != nullptr )  // 若 pMem2 非空
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(pMem2);  // 调 nengine::IControl 构造
      *(uint32_t *)pMem2 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(v4);  // 调 sub_69C780
      sub_69C7B0(Block, v15, v15, v15 + 1, v15, 0, 0);  // 调 sub_69C7B0
    }
    else
    {
      v4 = nullptr;  // v4 = nullptr 空指针
    }
    *v14++ = v4;  // *v14++ 写入 v4
    v15 += 2;
  }
  while ( v15 < 8 );  // 当 v15 < 8 循环
  v5 = operator new(0x88u);  // operator new 分配 136 字节
  v6 = v5;
  if ( v5 != nullptr )  // 若 v5 非空
  {
    Blocka = (void *)*(this + 9);  // this+36 = 状态字
    sub_426BD0(v5);  // 调 nengine::IControl 构造
    *v6 = &nengine::CNSlider::`vftable';  // vftable 复位
    sub_69CA20(pMem32);  // 调 sub_69CA20
    sub_69CA50(Blocka, 87, 86);  // 调 sub_69CA50
    *pMem32 = &nengine::CNVSlider::`vftable';  // vftable 复位
    pMem322 = pMem32;
  }
  else
  {
    pMem322 = nullptr;  // pMem322 = nullptr 空指针
  }
  *(this + 13) = pMem322;  // this+52 = bAuraState
  if ( operator new(0x74u) != nullptr )  // operator new 分配 116 字节
    fld_e11 = (uint32_t *)sub_43C630(*(this + 11), *(this + 12), *(this + 13));  // 调 nengine::CNVScroll 构造
  else
    fld_e11 = nullptr;  // fld_e11 = nullptr 空指针
  *(this + 14) = fld_e11;  // this+56 = fld_e11
  sub_69A5F0(fld_e11, 239, 35);  // 调 sub_69A5F0
  sub_69A840(*(this + 14));  // 调 sub_69A840
  *((uint8_t *)this + 60) = 0;
  *((uint8_t *)this + 61) = 0;
  *((uint8_t *)this + 62) = 0;
  *((uint8_t *)this + 63) = 0;
  *(this + 18) = 0;  // this+72 = 0
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 25) = 0;  // this+100 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 27) = 0;  // this+108 = 0
  *(this + 20) = 12;  // this+80 = nAuraStage
  *(this + 22) = 1600;  // this+88 = pFxObjB
  *(this + 19) = 6;  // this+76 = 6
  *(this + 27) = dword_99FCCC;  // this+108 = dword_99FCCC
  *((uint8_t *)this + 62) = 1;
  *(this + 16) = -16777216;  // this+64 = -16777216
  *(this + 35) = 1600;  // this+140 = 1600
  *((uint8_t *)this + 112) = 0;  // this+112 = pHostComp
  *((uint8_t *)this + 113) = 0;
  *((uint8_t *)this + 114) = 0;
  *((uint8_t *)this + 115) = 0;
  *(this + 31) = 0;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
  *(this + 32) = 6;  // this+128 = 6
  *(this + 33) = 12;  // this+132 = 12
  *(this + 34) = 0;  // this+136 = 0
  *(this + 36) = 0;  // this+144 = pFrameList144
  *(this + 37) = 0;  // this+148 = 0
  *(this + 38) = 0;  // this+152 = 0
  *(this + 39) = 0;  // this+156 = 0
  *(this + 40) = 0;  // this+160 = 0
  dword_99FCCC2 = dword_99FCCC;
  v10 = *this;
  *(this + 29) = -16777216;  // this+116 = -16777216
  *(this + 40) = dword_99FCCC2;  // this+160 = dword_99FCCC2
  *(this + 35) = 144;  // this+140 = 144
  *(this + 31) = 1;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
  *(this + 36) = 1;  // this+144 = pFrameList144
  *((uint8_t *)this + 114) = 1;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v10 + 24))(this, 20, 9);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 2);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
}


// ------------------------------------------------------------
// 0x632D40 sub_632D40 —— 推荐用户列表重建（178 行：4A2CF0 + 52DAA0/468240/430C80）
// ------------------------------------------------------------
void /*thiscall*/ sub_632D40(uint32_t *this)  // 函数: 推荐用户列表重建（178 行：4A2CF0 + 52DAA0/468240/430C80）
{
  void *fld_e42; // eax
  uint32_t *pThis_29; // ebx
  int pObj; // esi
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
  uint32_t *Block2; // esi
  uint32_t *v28; // eax
  bool v29; // zf
  uint32_t *v30; // edi
  uint8_t v31[4]; // [esp+8h] [ebp-38h] BYREF
  void *Block; // [esp+Ch] [ebp-34h]
  int v33; // [esp+10h] [ebp-30h]
  uint32_t v34[2]; // [esp+14h] [ebp-2Ch] BYREF
  uint32_t *pThis; // [esp+1Ch] [ebp-24h]
  int v36; // [esp+20h] [ebp-20h]
  int v37; // [esp+24h] [ebp-1Ch]
  int v38; // [esp+28h] [ebp-18h]
  int v39; // [esp+2Ch] [ebp-14h]
  unsigned int v40; // [esp+30h] [ebp-10h]
  int v41; // [esp+3Ch] [ebp-4h]

  fld_e42 = (void *)*(this + 42);
  pThis_29 = this + 41;
  pObj = 0;
  pThis = this;
  if ( fld_e42 != nullptr )  // 若 fld_e42 非空
    j__free(fld_e42);  // 调 堆释放
  pThis_29[1] = 0;
  pThis_29[2] = 0;
  pThis_29[3] = 0;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  {
    v38 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v4 = v38;
    if ( v38 != 0 )  // 若 v38 != 0
    {
      v5 = *(uint32_t *)(v38 + 8);  // v5 = v38+8
      v39 = v5 != 0 ? (*(uint32_t *)(v38 + 12) - v5) >> 2 : 0;
      v6 = sub_429830((uint16_t)word_77F804);  // 调 表按键查找（uint16）
      v36 = v6;
      if ( v6 != 0 )  // 若 v6 != 0
      {
        v37 = sub_41A5E0(v6 + 53);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        v7 = (uint32_t **)sub_4A2CF0(v31);
        Block = v7;
        v33 = 0;
        v8 = 0;
        v41 = 0;
        v40 = 0;
        if ( v39 > 0 )  // 若 v39 > 0
        {
          while ( 1 )  // 无限循环
          {
            v9 = *(uint32_t *)(v4 + 8);  // v9 = v4+8
            if ( v9 != 0 && v8 < (*(uint32_t *)(v4 + 12) - v9) >> 2 )  // 若 v9 != 0 && v8 < (*(uint32_t *)(v4 + 12) - v9) >> 2
              pObj = *(uint32_t *)(v9 + 4 * v8);
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 18) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
            {
              v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调用虚函数（虚表槽 +52）
              v11 = sub_429830(v10);  // 调 表按键查找（uint16）
              v12 = sub_41A5E0(v11 + 53);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
              v13 = abs32(v37 - v12);
              if ( v11 != v36 && *(uint32_t *)(v11 + 184) == 0 && v13 <= 5 )  // 若 v11 != v36 && *(uint32_t *)(v11 + 184) == 0 && v13 <= 5
              {
                for ( i = *(uint32_t **)Block; i != Block; i = (uint32_t *)*i )  // 循环：i = *(uint32_t **)Block; i != Block; i = (uint32_t *)*i
                {
                  if ( i[2] >= v13 )  // 若 i[2] >= v13
                    break;
                }
                v15 = i[1];
                v16 = *(uint16_t *)(v11 + 4);  // v16 = v11+4
                v34[0] = v13;
                v34[1] = v16;
                v17 = sub_52DAA0(i, v15, v34);  // 调 sub_52DAA0
                sub_468240(1);  // 调 list 元素数预留（溢出抛错）
                i[1] = v17;
                **(uint32_t **)(v17 + 4) = v17;
              }
              v4 = v38;
            }
            if ( (int)++v40 >= v39 )  // 若 (int)++v40 >= v39
              break;
            v8 = v40;
            pObj = 0;
          }
          v7 = (uint32_t **)Block;
        }
        v18 = *v7;
        if ( *v7 != v7 )  // 若 *v7 != v7
        {
          do
          {
            v19 = pThis_29[1];
            if ( v19 != 0 )  // 若 v19 != 0
              v20 = (pThis_29[2] - v19) >> 2;
            else
              v20 = 0;
            if ( v19 != 0 && v20 < (pThis_29[3] - v19) >> 2 )  // 若 v19 != 0 && v20 < (pThis_29[3] - v19) >> 2
            {
              v21 = (uint32_t *)pThis_29[2];
              *v21 = v18[3];  // *v21 写入 v18[3]
              pThis_29[2] = v21 + 1;  // pThis_29[2] 写入 v21 + 1
            }
            else
            {
              sub_430C80((void *)pThis_29[2], 1, (int)(v18 + 3));  // 调 uint32 vector 区间插入（同值填充）
            }
            v18 = (uint32_t *)*v18;
          }
          while ( v18 != Block );  // 当 v18 != Block 循环
        }
        v22 = pThis_29[1];
        if ( v22 != 0 )  // 若 v22 != 0
          v23 = (pThis_29[2] - v22) >> 2;
        else
          v23 = 0;
        if ( v23 - 5 >= 0 )  // 若 v23 - 5 >= 0
        {
          v25 = pThis_29[1];
          if ( v25 != 0 )  // 若 v25 != 0
            v26 = (pThis_29[2] - v25) >> 2;
          else
            v26 = 0;
          v24 = v26 - 5;
        }
        else
        {
          v24 = 0;
        }
        (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pThis[14] + 32))(pThis[14], v24);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
        Block2 = Block;
        v28 = *(uint32_t **)Block;
        v29 = *(uint32_t *)Block == (uint32_t)Block;
        *(uint32_t *)Block = Block;
        Block2[1] = Block2;
        if ( !v29 )  // 若 !v29
        {
          do
          {
            v30 = (uint32_t *)*v28;
            j__free(v28);  // 调 堆释放
            v28 = v30;
          }
          while ( v30 != Block2 );  // 当 v30 != Block2 循环
        }
        j__free(Block2);  // 调 堆释放
      }
    }
  }
}


// ------------------------------------------------------------
// 0x632FB0 CNRDPartyRecommendUserWindow__vmtC —— CNRDPartyRecommendUserWindow__vmtC 打开槽（登记 dword_9B9460 + 69A5F0 + 69C680 + 632D40）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyRecommendUserWindow__vmtC(int this, int nArg2, int nArg3)  // 函数: CNRDPartyRecommendUserWindow__vmtC 打开槽（登记 dword_9B9460 + 69A5F0 + 69C680 + 632D40）
{
  dword_9B9460 = this;
  sub_69A5F0(*(uint32_t **)(this + 8), 192, 55);  // 调 sub_69A5F0
  sub_69C680(0);  // 调 sub_69C680
  sub_632D40((uint32_t *)this);  // 调 推荐用户列表重建（178 行：4A2CF0 + 52DAA0/468240/430C80）
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
  int fld_e9; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 56))(this);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = (uint8_t *)*(this + 10);  // this+40 = 状态子标志
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 60))(this);  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x633060 CNRDYesNoConfirmWindow__vmt14 —— CNRDYesNoConfirmWindow__vmt14 关闭槽：vt+56 + vt+32
// ------------------------------------------------------------
char /*thiscall*/ CNRDYesNoConfirmWindow__vmt14(void *this)  // 函数: CNRDYesNoConfirmWindow__vmt14 关闭槽：vt+56 + vt+32
{
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 56))(this);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  return 1;
}



// ------------------------------------------------------------
// 0x633080 CNRDCashShopBuyConfirmWindow__vmt38 —— CNRDCashShopBuyConfirmWindow__vmt38 确认动作：645CC0 商城下单 + 清 +2052 标志
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopBuyConfirmWindow__vmt38(uint32_t *this)  // 函数: CNRDCashShopBuyConfirmWindow__vmt38 确认动作：645CC0 商城下单 + 清 +2052 标志
{
  int result; // eax

  sub_645CC0(*(this + 20));  // 调 商城下单确认（423200 系参数 + 55F160/55D300/55CB40，45 行——被确认窗 vmt38 调用）
  result = *(this + 20);  // this+80 = nAuraStage
  *(uint8_t *)(result + 2052) = 0;  // result+2052 = 0
  return result;
}



// ------------------------------------------------------------
// 0x6330A0 CNRDCashShopBuyConfirmWindow__vmt3C —— CNRDCashShopBuyConfirmWindow__vmt3C 取消动作：清 +2052 标志
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopBuyConfirmWindow__vmt3C(uint32_t *this)  // 函数: CNRDCashShopBuyConfirmWindow__vmt3C 取消动作：清 +2052 标志
{
  int result; // eax

  result = *(this + 20);  // this+80 = nAuraStage
  *(uint8_t *)(result + 2052) = 0;  // result+2052 = 0
  return result;
}



// ------------------------------------------------------------
// 0x6330B0 CNRDCashShopNoDoubleEventConfirmWindow__vmt38 —— CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认动作：+84 标志时 44E8D0 下单 + vt+32 关闭
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopNoDoubleEventConfirmWindow__vmt38(uint32_t *this)  // 函数: CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认动作：+84 标志时 44E8D0 下单 + vt+32 关闭
{
  if ( *((uint8_t *)this + 84) != 0 )  // this+84 = pFxObjA
    sub_44E8D0((char *)dword_8F8528, (void *)0x2F, *(this + 20), 0);  // 调 对象池借出（按池号取可用对象）
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
}



// ------------------------------------------------------------
// 0x6330E0 CNRDCashShopNoDoubleEventConfirmWindow__vmt3C —— CNRDCashShopNoDoubleEventConfirmWindow__vmt3C 取消动作：645CA0
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopNoDoubleEventConfirmWindow__vmt3C(uint32_t *this)  // 函数: CNRDCashShopNoDoubleEventConfirmWindow__vmt3C 取消动作：645CA0
{
  return sub_645CA0(*(this + 20));  // 调 商城取消（12 行）
}



// ------------------------------------------------------------
// 0x6330F0 CNRDImportantItemUseConfirmWindow__vmt38 —— CNRDImportantItemUseConfirmWindow__vmt38 确认动作：484E80 + 602C00 重要道具使用
// ------------------------------------------------------------
int /*thiscall*/ CNRDImportantItemUseConfirmWindow__vmt38(int this)  // 函数: CNRDImportantItemUseConfirmWindow__vmt38 确认动作：484E80 + 602C00 重要道具使用
{
  int result; // eax
  int pObj; // ecx
  int nItemId; // edi  | +0x0054 → 道具 id（0x6330F0: fld_54=*(this+84)；与 vt+16()+4 比对）（CNRDImportantItemUseConfirmWindow；va=006330F0）

  result = *(uint32_t *)(this + 88);  // result = this+88
  if ( result < *((uint32_t *)dword_8F852C + 2) )  // dword_8F852C = UI 管理器全局
  {
    pObj = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * result);  // dword_8F852C = UI 管理器全局
    if ( pObj != 0 && *(uint32_t *)(this + 80) == pObj )  // 若 pObj != 0 && *(uint32_t *)(this + 80) == pObj
    {
      nItemId = *(uint32_t *)(this + 84);  // fld_54 = this+84
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 调用虚函数（虚表槽 +16）
      if ( nItemId == *(uint32_t *)(result + 4) )  // 若 fld_54 == *(uint32_t *)(result + 4)
      {
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 32))(*(uint32_t *)(this + 80));  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
        result = sub_484E80(nItemId);  // 调 按类型查找下标（同一匹配规则，未命中 -1）
        if ( result == *(uint32_t *)(this + 88) )  // 若 result == *(uint32_t *)(this + 88)
          return sub_602C00(*(uint32_t **)(this + 80), *(uint32_t *)(this + 88));  // 调 基类激活转发
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x633150 CNRDTradeLastConfirmWindow__vmt38 —— CNRDTradeLastConfirmWindow__vmt38 确认动作（423200 系参数 + 422E70/44E8D0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDTradeLastConfirmWindow__vmt38(void *this)  // 函数: CNRDTradeLastConfirmWindow__vmt38 确认动作（423200 系参数 + 422E70/44E8D0）
{
  char *v1; // eax
  void *pThis; // [esp+0h] [ebp-4h] BYREF

  pThis = this;
  sub_423200(dword_8F7B08, 26);  // 【发送网络包API】
  LOBYTE(pThis) = 3;  // 调 取 16 位值低 8 位
  sub_423290(dword_8F7B08, (int)&pThis, 1);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
  sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
  v1 = sub_422E70(2006);  // 调 sub_422E70
  return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v1, 0);  // 调 对象池借出（按池号取可用对象）
}



// ------------------------------------------------------------
// 0x6331B0 CNRDTradeLastConfirmWindow__vmt3C —— CNRDTradeLastConfirmWindow__vmt3C 取消动作（423200 系参数）
// ------------------------------------------------------------
int /*thiscall*/ CNRDTradeLastConfirmWindow__vmt3C(void *this)  // 函数: CNRDTradeLastConfirmWindow__vmt3C 取消动作（423200 系参数）
{
  void *pThis; // [esp+0h] [ebp-4h] BYREF

  pThis = this;
  sub_423200(dword_8F7B08, 26);  // 【发送网络包API】
  LOBYTE(pThis) = 4;  // 调 取 16 位值低 8 位
  sub_423290(dword_8F7B08, (int)&pThis, 1);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
  return sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
}



// ------------------------------------------------------------
// 0x6331F0 CNRDYesNoConfirmWindow__vmtC —— CNRDYesNoConfirmWindow__vmtC 文案装配（69C340/69C440/69C360/69C500 文本链 + 406DF0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDYesNoConfirmWindow__vmtC(char *this, int nArg2, int nArg3)  // 函数: CNRDYesNoConfirmWindow__vmtC 文案装配（69C340/69C440/69C360/69C500 文本链 + 406DF0）
{
  int v4; // edx
  char *pThis_30; // eax
  int v6; // edi
  int pThis_3; // eax
  uint32_t *pThis_2; // ecx
  int v9; // ebx
  int v10; // edi

  v4 = *(uint32_t *)this;  // v4 = this
  *((uint32_t *)this + 19) = nArg3;  // this+76 = nArg3
  *((uint32_t *)this + 18) = nArg2;  // this+72 = nArg2
  (*(void (/*thiscall*/ **)(char *, int, int))(v4 + 64))(this, nArg2, nArg3);  // 调用虚函数（虚表槽 +64）【推断: 取观察者容器（懒创建 0x44 字节 sb_499960(thi…】
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  if ( *((uint32_t *)this + 17) < 0x10u )  // 若 *((uint32_t *)this + 17) < 0x10u
    pThis_30 = this + 48;
  else
    pThis_30 = *((char **)this + 12);
  sub_69C360(pThis_30, 0);  // 调 sub_69C360
  v6 = *(uint32_t *)this;  // v6 = this
  pThis_3 = sub_69C500(*((uint32_t *)this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(char *, int, int))(v6 + 24))(this, 14, pThis_3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  pThis_2 = *((uint32_t **)this + 2);
  v9 = (480 - pThis_2[8]) / 2;
  v10 = (640 - pThis_2[7]) / 2;
  sub_69A5F0(pThis_2, v10, v9);  // 调 sub_69A5F0
  sub_69A5F0(*((uint32_t **)this + 9), v10 + 29, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v9 - 43);  // this+8 = 技能槽记录首字
  sub_69A5F0(*((uint32_t **)this + 10), v10 + 98, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v9 - 43);  // this+8 = 技能槽记录首字
  sub_406DF0(*(uint32_t *)(*((uint32_t *)this + 9) + 20) + (*(uint32_t *)(*((uint32_t *)this + 9) + 28) >> 1), pt.y);  // 调 光标位置设置（ClientToScreen 换算 + SetCursorPos，同步回写全局 pt）
  sub_406DF0(pt.x, *(uint32_t *)(*((uint32_t *)this + 9) + 24) + (*(uint32_t *)(*((uint32_t *)this + 9) + 32) >> 1));  // 调 光标位置设置（ClientToScreen 换算 + SetCursorPos，同步回写全局 pt）
  return 1;
}



// ------------------------------------------------------------
// 0x6332F0 sub_6332F0 —— 弹窗关闭清理（43C410 + 69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_6332F0(uint32_t *this)  // 函数: 弹窗关闭清理（43C410 + 69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 21, 22, 23, 21, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 24, 25, 26, 24, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ------------------------------------------------------------
// 0x6333D0 CNRDCashShopBuyConfirmWindow__vmt40 —— CNRDCashShopBuyConfirmWindow__vmt40 文案槽（422E70 取串 + 4015C0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopBuyConfirmWindow__vmt40(uint32_t *this, int pArg2, int nArg3)  // 函数: CNRDCashShopBuyConfirmWindow__vmt40 文案槽（422E70 取串 + 4015C0）
{
  char *psz; // eax

  *(this + 20) = pArg2;  // this+80 = nAuraStage
  *(uint8_t *)(pArg2 + 2052) = 1;  // pArg2+2052 = 1
  psz = sub_422E70(881);  // 调 sub_422E70
  return sub_4015C0(psz, strlen(psz));  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x633410 CNRDCashShopNoDoubleEventConfirmWindow__vmt40 —— CNRDCashShopNoDoubleEventConfirmWindow__vmt40 文案槽（422E70/4015C0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopNoDoubleEventConfirmWindow__vmt40(int this, int nArg2, int nArg3)  // 函数: CNRDCashShopNoDoubleEventConfirmWindow__vmt40 文案槽（422E70/4015C0）
{
  char *psz; // eax

  *(uint32_t *)(this + 80) = nArg2;  // this+80 = nArg2
  psz = sub_422E70(3011);  // 调 sub_422E70
  sub_4015C0(psz, strlen(psz));  // 【std::string构造赋值】
  *(uint8_t *)(this + 84) = nArg3 == 0;  // this+84 = nArg3 == 0
  return nArg3;
}



// ------------------------------------------------------------
// 0x633460 CNRDImportantItemUseConfirmWindow__vmt40 —— CNRDImportantItemUseConfirmWindow__vmt40 文案槽（422E70/4015C0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDImportantItemUseConfirmWindow__vmt40(uint32_t *this, int *pDwArg2, int nArg3)  // 函数: CNRDImportantItemUseConfirmWindow__vmt40 文案槽（422E70/4015C0）
{
  int pObj; // ecx
  int v5; // eax
  int v6; // edx
  char *v7; // eax
  int v9; // [esp-4h] [ebp-10Ch]
  char Buffer[256]; // [esp+4h] [ebp-104h] BYREF
  int dword_796E502; // [esp+104h] [ebp-4h]

  pObj = *pDwArg2;
  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  v5 = pDwArg2[1];
  v6 = pDwArg2[2];
  *(this + 20) = pObj;  // this+80 = nAuraStage
  *(this + 21) = v5;  // this+84 = pFxObjA
  *(this + 22) = v6;  // this+88 = pFxObjB
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 108))(pObj);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
  v7 = sub_422E70(882);  // 调 sub_422E70
  sprintf(Buffer, v7, v9);  // 调 格式化到缓冲
  return sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x6334E0 CNRDCashShopLevelLimitConfirmWindow__vmt40 —— CNRDCashShopLevelLimitConfirmWindow__vmt40 文案槽（422E70/4015C0）
// ------------------------------------------------------------
int /*stdcall*/ CNRDCashShopLevelLimitConfirmWindow__vmt40(int nArg1, int nArg2)  // 函数: CNRDCashShopLevelLimitConfirmWindow__vmt40 文案槽（422E70/4015C0）
{
  char *v2; // eax
  char Buffer[512]; // [esp+4h] [ebp-204h] BYREF
  int dword_796E502; // [esp+204h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  v2 = sub_422E70(883);  // 调 sub_422E70
  sprintf(Buffer, v2, nArg2);  // 调 格式化到缓冲
  return sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x633550 CNRDTradeLastConfirmWindow__vmt40 —— CNRDTradeLastConfirmWindow__vmt40 文案槽（422E70/4015C0）
// ------------------------------------------------------------
int /*stdcall*/ CNRDTradeLastConfirmWindow__vmt40(int nArg1, int nArg2)  // 函数: CNRDTradeLastConfirmWindow__vmt40 文案槽（422E70/4015C0）
{
  char *psz; // eax

  psz = sub_422E70(2005);  // 调 sub_422E70
  return sub_4015C0(psz, strlen(psz));  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x633580 sub_633580 —— 14 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_633580(int this)  // 函数: 14 行小辅助
{
  *(uint32_t *)(this + 36) = 0;  // this+144 = pFrameList144
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  *(uint8_t *)(this + 48) = 0;  // this+48 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x633590 sub_633590 —— 弹窗数据清理（422E70 系——被 cashshop.cpp 各 vmt4 调用）
// ------------------------------------------------------------
int /*thiscall*/ sub_633590(uint32_t *this)  // 函数: 弹窗数据清理（422E70 系——被 cashshop.cpp 各 vmt4 调用）
{
  int (/*thiscall*/ ***fld_e9)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx

  fld_e9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);  // this+36 = 状态字
  if ( fld_e9 != nullptr )  // 若 fld_e9 非空
    result = (**fld_e9)(fld_e9, 1);
  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);  // this+40 = 状态子标志
  *(this + 9) = 0;  // this+36 = 状态字
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    result = (**fld_e10)(fld_e10, 1);
  *(this + 10) = 0;  // this+40 = 状态子标志
  return result;
}



// ============================================================
// 【分区 6】技能购买确认 CNRDSkillBuyConfirmWindow（0x6335C0-0x633770）
// vmtC 文案装配（47EB10 技能查询）、vmt14 关闭（GET_SKILL 学技事件）。
// ============================================================
// ------------------------------------------------------------
// 0x6335C0 CNRDSkillBuyConfirmWindow__vmtC —— CNRDSkillBuyConfirmWindow__vmtC 文案装配（69C340 系 + 47EB10 技能查询 + 550470/5013F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillBuyConfirmWindow__vmtC(uint32_t *this, int nArg2, int nArg3)  // 函数: CNRDSkillBuyConfirmWindow__vmtC 文案装配（69C340 系 + 47EB10 技能查询 + 550470/5013F0）
{
  int fld_e11; // edi
  int fld_e112; // eax
  char *v7; // eax
  int v8; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
  int v11; // ebx
  int v12; // edi
  int fld_e113; // [esp-10h] [ebp-218h]
  char Buffer[512]; // [esp+4h] [ebp-204h] BYREF
  int dword_796E502; // [esp+204h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  *(this + 11) = nArg2;  // this+44 = nArg2
  if ( nArg2 == 0 )  // 若 nArg2 == 0
    return 0;
  *((uint8_t *)this + 48) = nArg3 != 0;
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  fld_e11 = sub_47EB10((uint32_t *)*(this + 11));  // 调 sub_47EB10
  if ( (uint8_t)sub_550470(*(uint32_t *)(*(this + 4) + 68)) != 0 )  // 调 判定 dword_9B88CC==3（购买上下文查询）
  {
    fld_e112 = *(this + 11);  // fld_e112 = this+11
    if ( *(uint8_t *)(fld_e112 + 480) != 0 )  // 若 *(uint8_t *)(fld_e112 + 480) != 0
      fld_e11 = sub_5013F0(fld_e11, *(uint32_t *)(fld_e112 + 488));  // 调 sub_5013F0
  }
  fld_e113 = sub_41ACF0(*(this + 11) + 20);  // 调 驻留串句柄 → 字符串指针
  v7 = sub_422E70(1143);  // 调 sub_422E70
  sprintf(Buffer, v7, fld_e113, fld_e11);  // 调 格式化到缓冲
  sub_69C360(Buffer, 0);  // 调 sub_69C360
  v8 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v8 + 24))(this, 14, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v11 = pt.x - 55 <= 0 ? 0 : pt.x - 55;
  if ( v11 >= 640 - fld_e2[7] )  // 若 v11 >= 640 - fld_e2[7]
    v11 = 640 - fld_e2[7];
  v12 = 480 - fld_e2[8];
  if ( (pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31) < v12 )  // 若 (pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31) < v12
    v12 = pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31;
  sub_69A5F0(fld_e2, v11, v12);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v11 + 29, *(uint32_t *)(*(this + 2) + 32) + v12 - 43);  // this+36 = 状态字
  sub_69A5F0((uint32_t *)*(this + 10), v11 + 98, *(uint32_t *)(*(this + 2) + 32) + v12 - 43);  // this+40 = 状态子标志
  return 1;
}



// ------------------------------------------------------------
// 0x633730 CNRDSkillBuyConfirmWindow__vmt14 —— CNRDSkillBuyConfirmWindow__vmt14 关闭槽：GET_SKILL 学技事件（47F890/432EA0）+ 44ABE0
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillBuyConfirmWindow__vmt14(uint32_t **this)  // 函数: CNRDSkillBuyConfirmWindow__vmt14 关闭槽：GET_SKILL 学技事件（47F890/432EA0）+ 44ABE0
{
  sub_47F890(*(this + 11));  // 调 sub_47F890
  sub_432EA0("GET_SKILL", -1, 0, 0);  // 调 音效播放包装（非空判定）
  if ( *((uint8_t *)this + 48) != 0 )  // 若 *((uint8_t *)this + 48) != 0
    sub_44ABE0(*(this + 4), 3);  // 调 选中索引 setter
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
int /*thiscall*/ sub_633770(uint32_t *this)  // 函数: 删除确认清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 15, 16, 17, 15, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ------------------------------------------------------------
// 0x633850 CNRDItemDeleteConfirmWindow__vmtC —— CNRDItemDeleteConfirmWindow__vmtC 文案装配（422E70 + 69C340 系）
// ------------------------------------------------------------
char /*userpurge*/ CNRDItemDeleteConfirmWindow__vmtC@<al>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4, int nArg5)  // 函数: CNRDItemDeleteConfirmWindow__vmtC 文案装配（422E70 + 69C340 系）
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
  int dword_796E502; // [esp+84h] [ebp-4h]
  int v19; // [esp+90h] [ebp+8h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  pDwArg1[11] = nArg4;
  pDwArg1[12] = nArg5;
  if ( nArg4 == 0 )  // 若 nArg4 == 0
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg4 + 20))(nArg4, 2) != 0 )  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
    pDwArg1[12] = 1;
  v7 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pDwArg1[11] + 108))(pDwArg1[11], nArg3, nArg2);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[11] + 16))(pDwArg1[11]) + 4) != 0 )  // 调用虚函数（虚表槽 +16）
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[11] + 20))(pDwArg1[11], 2) != 0 )  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
    {
      v9 = sub_422E70(956);  // 调 sub_422E70
      sprintf(Buffer, v9, v7);  // 调 格式化到缓冲
    }
    else
    {
      v16 = pDwArg1[12];
      v10 = sub_422E70(957);  // 调 sub_422E70
      sprintf(Buffer, v10, v7, v16);  // 调 格式化到缓冲
    }
  }
  else
  {
    v15 = pDwArg1[12];
    v8 = sub_422E70(955);  // 调 sub_422E70
    sprintf(Buffer, v8, v15);  // 调 格式化到缓冲
  }
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(Buffer, 0);  // 调 sub_69C360
  v11 = *pDwArg1;
  v12 = sub_69C500(pDwArg1[3]);  // 调 sub_69C500
  (*(void (/*thiscall*/ **)(int *, int, int))(v11 + 24))(pDwArg1, 14, v12 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  v13 = (uint32_t *)pDwArg1[2];
  v19 = pt.x - 125 <= 0 ? 0 : pt.x - 125;
  if ( v19 >= 640 - v13[7] )  // 若 v19 >= 640 - v13[7]
    v19 = 640 - v13[7];
  v14 = pt.y - v13[8] + 31 <= 0 ? 0 : pt.y - v13[8] + 31;
  if ( v14 >= 480 - v13[8] )  // 若 v14 >= 480 - v13[8]
    v14 = 480 - v13[8];
  sub_69A5F0(v13, v19, v14);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)pDwArg1[9], v19 + 29, *(uint32_t *)(pDwArg1[2] + 32) + v14 - 43);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)pDwArg1[10], v19 + 98, *(uint32_t *)(pDwArg1[2] + 32) + v14 - 43);  // 调 sub_69A5F0
  return 1;
}



// ------------------------------------------------------------
// 0x633A00 CNRDItemDeleteConfirmWindow__vmt14 —— CNRDItemDeleteConfirmWindow__vmt14 删除执行（484ED0/422E70/44E8D0/432F00/486070）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemDeleteConfirmWindow__vmt14(void *this)  // 函数: CNRDItemDeleteConfirmWindow__vmt14 删除执行（484ED0/422E70/44E8D0/432F00/486070）
{
  int pThis_B; // esi
  int v3; // ebx
  char *v4; // eax
  int pObj; // ebx

  pThis_B = sub_484ED0(*((uint32_t *)this + 11));  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
  if ( pThis_B == -1 )  // 若 pThis_B == -1
  {
    pThis_B = sub_484ED0(*((uint32_t *)this + 11));  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
    if ( pThis_B == -1 )  // 若 pThis_B == -1
    {
      pThis_B = sub_484ED0(*((uint32_t *)this + 11));  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
      if ( pThis_B == -1 )  // 若 pThis_B == -1
      {
        pObj = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
        pThis_B = 0;
        while ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 792))(pObj, pThis_B) != *((uint32_t *)this + 11) )  // 调用虚函数（虚表槽 +792）
        {
          if ( ++pThis_B >= 18 )  // 若 ++pThis_B >= 18
            goto LABEL_14;  // 跳转 LABEL_14
        }
        v3 = 3;
        if ( pThis_B != -1 )  // 若 pThis_B != -1
          goto LABEL_3;  // 跳转 LABEL_3
LABEL_14:
        v4 = sub_422E70(958);  // 调 sub_422E70
        goto LABEL_15;  // 跳转 LABEL_15
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
  if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 11) + 44))(*((uint32_t *)this + 11)) < *((uint32_t *)this + 12) )  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  {
    v4 = sub_422E70(959);  // 调 sub_422E70
LABEL_15:
    sub_44E8D0(*((char **)this + 4), (void *)0x1B, (int)v4, 0);  // 调 对象池借出（按池号取可用对象）
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return 1;
  }
  if ( v3 == 3 )  // 若 v3 == 3
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F7C04 + 1092))(dword_8F7C04, pThis_B, 1);  // 调用虚函数（虚表槽 +1092）
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return 1;
  }
  else
  {
    if ( sub_432F00(v3) != nullptr )  // 调 按类型取全局列表对象
      sub_486070(pThis_B, *((uint32_t *)this + 12), 1);  // 调 请求 op 18：单槽技能值设置
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return 1;
  }
}



// ------------------------------------------------------------
// 0x633B20 sub_633B20 —— 删除确认清理 2（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_633B20(uint32_t *this)  // 函数: 删除确认清理 2（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ============================================================
// 【分区 8】物品购买确认 CNRDItemBuyConfirmWindow（0x633C00-0x633C70）
// ============================================================
// ------------------------------------------------------------
// 0x633C00 CNRDItemBuyConfirmWindow__vmt8 —— CNRDItemBuyConfirmWindow__vmt8 Update：悬停 + CLICK_BUTTON2
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemBuyConfirmWindow__vmt8(int *this)  // 函数: CNRDItemBuyConfirmWindow__vmt8 Update：悬停 + CLICK_BUTTON2
{
  int fld_e9; // eax
  int result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 20))(this);  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = *(this + 10);  // this+40 = 状态子标志
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 若 *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
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
char /*thiscall*/ CNRDItemSealRemoveConfirmWindow__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDItemSealRemoveConfirmWindow__vmtC 文案装配（422E70 + 69C340 系）
{
  int pObj; // eax
  char *v6; // eax
  int v7; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
  int v10; // ebx
  int v11; // edi
  int v12; // [esp-Ch] [ebp-114h]
  char Buffer[256]; // [esp+4h] [ebp-104h] BYREF
  int dword_796E502; // [esp+104h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  pObj = __RTDynamicCast(nArg2, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
  *(this + 11) = pObj;  // this+44 = pObj
  if ( pObj == 0 )  // 若 pObj == 0
    return 0;
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 108))(pObj);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
  v6 = sub_422E70(1108);  // 调 sub_422E70
  sprintf(Buffer, v6, v12);  // 调 格式化到缓冲
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(Buffer, 0);  // 调 sub_69C360
  v7 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(int *, int, int))(v7 + 24))(this, 14, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v10 = pt.x - 55 <= 0 ? 0 : pt.x - 55;
  if ( v10 >= 640 - fld_e2[7] )  // 若 v10 >= 640 - fld_e2[7]
    v10 = 640 - fld_e2[7];
  v11 = 480 - fld_e2[8];
  if ( (pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31) < v11 )  // 若 (pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31) < v11
    v11 = pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31;
  sub_69A5F0(fld_e2, v10, v11);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v10 + 29, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);  // this+36 = 状态字
  sub_69A5F0((uint32_t *)*(this + 10), v10 + 98, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);  // this+40 = 状态子标志
  return 1;
}



// ------------------------------------------------------------
// 0x633DB0 CNRDItemSealRemoveConfirmWindow__vmt14 —— CNRDItemSealRemoveConfirmWindow__vmt14 解封执行（484ED0/486820）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemSealRemoveConfirmWindow__vmt14(void *this)  // 函数: CNRDItemSealRemoveConfirmWindow__vmt14 解封执行（484ED0/486820）
{
  int pThis_B; // edi
  char *v3; // eax
  char pThis_B2; // bl
  uint32_t *pThis_B3; // eax

  pThis_B = sub_484ED0(*((uint32_t *)this + 11));  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
  if ( pThis_B == -1 )  // 若 pThis_B == -1
  {
    v3 = sub_422E70(1109);  // 调 sub_422E70
    sub_44E8D0(*((char **)this + 4), (void *)0x1B, (int)v3, 0);  // 调 对象池借出（按池号取可用对象）
  }
  pThis_B2 = *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 11) + 16))(*((uint32_t *)this + 11)) + 32);  // 调用虚函数（虚表槽 +16）
  *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 11) + 16))(*((uint32_t *)this + 11)) + 32) = 0;  // 调用虚函数（虚表槽 +16）
  pThis_B3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 11) + 172))(*((uint32_t *)this + 11));  // 调用虚函数（虚表槽 +172）【推断: 朝目标方向按比例取点: p = this + (target −…】
  sub_486820(pThis_B, *pThis_B3, 1);  // 调 施放拒绝提示（ALERT_1 音效 + sub_485510）
  *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 11) + 16))(*((uint32_t *)this + 11)) + 32) = pThis_B2;  // 调用虚函数（虚表槽 +16）
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  return 1;
}



// ------------------------------------------------------------
// 0x633E30 sub_633E30 —— 解封确认清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_633E30(uint32_t *this)  // 函数: 解封确认清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ============================================================
// 【分区 10】通用弹窗（0x633F20-0x634150）
// CNRDPopupMessageWindow/CNRDPopupTextBoxOnly：vmtC 文案装配、
// vmt8/vmt10 输入与关闭。
// ============================================================
// ------------------------------------------------------------
// 0x633F20 CNRDPopupMessageWindow__vmtC —— CNRDPopupMessageWindow__vmtC 文案装配（541AE0 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPopupMessageWindow__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDPopupMessageWindow__vmtC 文案装配（541AE0 + 69C340 系）
{
  int v5; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
  int v8; // ebx
  int v9; // edi

  if ( nArg2 == 0 )  // 若 nArg2 == 0
    return 0;
  *(this + 10) = nArg3;  // this+40 = 状态子标志
  if ( nArg3 != 0 && *((uint32_t *)dword_8F8528 + 626) == 17 )  // dword_8F8528 = 主管理器
    sub_541AE0();  // 调 sub_541AE0
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(nArg2, 0);  // 调 sub_69C360
  v5 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(int *, int, int))(v5 + 24))(this, 14, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v8 = (480 - fld_e2[8]) / 2;
  v9 = (640 - fld_e2[7]) / 2;
  sub_69A5F0(fld_e2, v9, v8);  // 调 sub_69A5F0
  sub_69A5F0(
    (uint32_t *)*(this + 9),  // this+36 = 状态字
    v9 + ((unsigned int)(*(uint32_t *)(*(this + 2) + 28) - *(uint32_t *)(*(this + 9) + 28)) >> 1),  // this+8 = 技能槽记录首字
    *(uint32_t *)(*(this + 2) + 32) + v8 - 43);  // this+8 = 技能槽记录首字
  return 1;
}



// ------------------------------------------------------------
// 0x633FE0 CNRDPopupMessageWindow__vmt10 —— CNRDPopupMessageWindow__vmt10 输入槽（41C860/41D520）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPopupMessageWindow__vmt10(uint32_t *this)  // 函数: CNRDPopupMessageWindow__vmt10 输入槽（41C860/41D520）
{
  int result; // eax

  if ( *(this + 10) == 1 )  // this+40 = 状态子标志
    return sub_41C860(dword_8F7A24);  // 调 断线/超时退出判定（重试上限 5）
  result = *(this + 10) - 2;  // this+40 = 状态子标志
  if ( *(this + 10) == 2 )  // this+40 = 状态子标志
    return sub_41D520(dword_8F7A24);  // 调 切换到模块 5 的切换流程
  return result;
}



// ------------------------------------------------------------
// 0x634000 sub_634000 —— 弹窗清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_634000(uint32_t *this)  // 函数: 弹窗清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  return sub_69A840(v3);  // 调 sub_69A840
}



// ------------------------------------------------------------
// 0x634090 sub_634090 —— 弹窗数据（10 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_634090(void *this)  // 函数: 弹窗数据（10 行）
{
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
}



// ------------------------------------------------------------
// 0x6340A0 CNRDPopupTextBoxOnly__vmt8 —— CNRDPopupTextBoxOnly__vmt8 Update（69A650 显示）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPopupTextBoxOnly__vmt8(uint32_t *this)  // 函数: CNRDPopupTextBoxOnly__vmt8 Update（69A650 显示）
{
  return sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
}



// ------------------------------------------------------------
// 0x6340B0 CNRDPopupTextBoxOnly__vmtC —— CNRDPopupTextBoxOnly__vmtC 文案装配（69C340 系 + 69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPopupTextBoxOnly__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDPopupTextBoxOnly__vmtC 文案装配（69C340 系 + 69A5F0）
{
  int v5; // edi
  int fld_e3; // eax

  if ( nArg2 == 0 )  // 若 nArg2 == 0
    return 0;
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(nArg2, 0);  // 调 sub_69C360
  v5 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(int *, int, int))(v5 + 24))(this, 14, fld_e3 + 2);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  sub_69A5F0(
    (uint32_t *)*(this + 2),  // this+8 = 技能槽记录首字
    (640 - *(uint32_t *)(*(this + 2) + 28)) / 2,  // this+8 = 技能槽记录首字
    (480 - *(uint32_t *)(*(this + 2) + 32)) / 2);  // this+8 = 技能槽记录首字
  return 1;
}



// ------------------------------------------------------------
// 0x634130 sub_634130 —— 弹窗数据 2（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_634130(uint32_t *this)  // 函数: 弹窗数据 2（15 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = 0xFFFF;  // 常量 0xFFFF（= 0xFFFF）
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = bAuraState
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
int /*thiscall*/ CNRDResponsePeerWindow__vmt38(uint16_t *this)  // 函数: CNRDResponsePeerWindow__vmt38 接受动作：429830 + 456690/484FA0/42EAF0 组队/好友接受
{
  char *v2; // eax
  int pThis_C; // eax
  int v5; // edi
  int v6; // ebx
  int fld_e22; // [esp+4h] [ebp-8h] BYREF
  char v8[4]; // [esp+8h] [ebp-4h] BYREF

  if ( sub_429830((uint32_t *)dword_8F8500, *(this + 22)) == 0 )  // 调 表按键查找（uint16）
  {
    v2 = sub_422E70(1142);  // 调 sub_422E70
    sub_44E8D0(*((char **)this + 4), (void *)0x1B, (int)v2, 0);  // 调 对象池借出（按池号取可用对象）
    return (*(int (/*thiscall*/ **)(uint16_t *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  }
  pThis_C = *((uint32_t *)this + 12);
  if ( pThis_C != 1 || *((uint32_t *)dword_8F8528 + 26) != 2 )  // dword_8F8528 = 主管理器
  {
    if ( pThis_C == 0 )  // 若 pThis_C == 0
    {
      sub_456690(*((uint32_t *)this + 11));  // 调 组队申请发送
      return (*(int (/*thiscall*/ **)(uint16_t *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
    v5 = 0;
    if ( pThis_C == 1 )  // 若 pThis_C == 1
    {
      v6 = *((uint32_t *)dword_8F852C + 1);  // dword_8F852C = UI 管理器全局
      v5 = sub_484FA0() - v6;  // 调 全局时间系数计算（+732 与 +746 相乘）
    }
    if ( *((uint32_t *)this + 12) != 3 || sub_42EAF0(*(uint32_t **)(dword_8F7A24 + 40), *((uint32_t *)this + 14)) != 0 )  // 调 场景与难度选择
    {
      sub_423200(dword_8F7B08, 11);  // 【发送网络包API】
      fld_e22 = *(this + 22);  // this+88 = pFxObjB
      sub_423290(dword_8F7B08, (int)&fld_e22, 2);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
      v8[0] = *((uint8_t *)this + 48);  // v8[0] 写入 *((uint8_t *)this + 48)
      sub_423290(dword_8F7B08, (int)v8, 1);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
      fld_e22 = v5;
      sub_423290(dword_8F7B08, (int)&fld_e22, 4);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
      sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    }
  }
  return (*(int (/*thiscall*/ **)(uint16_t *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
}



// ------------------------------------------------------------
// 0x634270 CNRDResponsePeerWindow__vmt8 —— CNRDResponsePeerWindow__vmt8 Update（CLICK_BUTTON2 + 699000 输入）
// ------------------------------------------------------------
int /*thiscall*/ CNRDResponsePeerWindow__vmt8(int *this)  // 函数: CNRDResponsePeerWindow__vmt8 Update（CLICK_BUTTON2 + 699000 输入）
{
  int fld_e21; // edi
  int fld_e9; // eax
  int result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  if ( sub_429830((uint32_t *)dword_8F8500, *((uint16_t *)this + 22)) == 0 )  // 调 表按键查找（uint16）
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  fld_e21 = *(this + 21);  // this+84 = pFxObjA
  if ( sub_699000((int)(this + 15)) >= fld_e21 )  // 【clock_now(clk)】
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 56))(this);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = *(this + 10);  // this+40 = 状态子标志
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 若 *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  }
  return result;
}



// ------------------------------------------------------------
// 0x634310 CNRDResponsePeerWindow__vmt0 —— CNRDResponsePeerWindow__vmt0 构造（24 行）
// ------------------------------------------------------------
int /*thiscall*/ CNRDResponsePeerWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDResponsePeerWindow__vmt0 构造（24 行）
{
  int result; // eax
  int fld_e13; // ecx

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 2) && *(this + 12) == 2 )  // this+8 = 技能槽记录首字
  {
    fld_e13 = *(this + 13);  // this+52 = bAuraState
    if ( fld_e13 != 0 )  // 若 fld_e13 != 0
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e13 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
               fld_e13,
               *(uint32_t *)(pArg2 + 20) + 18,
               *(uint32_t *)(pArg2 + 24) + 16,
               dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
  }
  return result;
}



// ------------------------------------------------------------
// 0x634360 sub_634360 —— 响应窗清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_634360(uint32_t *this)  // 函数: 响应窗清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 21, 22, 23, 21, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 24, 25, 26, 24, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ------------------------------------------------------------
// 0x634440 CNRDResponsePeerWindow__vmtC —— CNRDResponsePeerWindow__vmtC 打开槽（209 行：POP_UP 事件 + 48B740/49EFE0/42A410/4332F0 邀请数据 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ sub_634440(uint32_t *this, int pArg2, int *pDwArg3)  // 【CNRDResponsePeerWindow__vmtC】
{
  uint32_t *v3; // ebx
  int *pDwArg32; // eax
  int fld_e11; // edx
  int fld_e12; // eax
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
  int pArg22; // edx
  bool v20; // zf
  int v21; // eax
  uint32_t *v22; // ecx
  uint32_t *v23; // edi
  int v24; // eax
  int v25; // eax
  uint32_t *v26; // ecx
  const char *v27; // eax
  int fld_e112; // edx
  uint32_t *v29; // ebx
  const char *v30; // eax
  int v31; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
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
  int dword_796E502; // [esp+8Ch] [ebp-4h]

  v3 = (uint32_t *)pArg2;
  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  if ( pArg2 == 0 )  // 若 pArg2 == 0
    return 0;
  *(this + 11) = *(uint16_t *)(pArg2 + 4);  // this+44 = *(uint16_t *)(pArg2 + 4)
  pDwArg32 = pDwArg3;
  fld_e11 = *(this + 11);  // fld_e11 = this+11
  *(this + 12) = pDwArg3;  // this+48 = pDwArg3
  *(this + 14) = -1;  // this+56 = -1
  if ( fld_e11 == (uint16_t)word_77F804 || *(uint32_t *)(dword_8F7A24 + 12) != 1 )  // dword_8F7A24 = 当前场景状态对象
    return 0;
  if ( pDwArg32 != nullptr )  // 若 pDwArg32 非空
  {
    if ( pDwArg32 == (int *)2 )  // 若 pDwArg32 == (int *)2
    {
      if ( sub_48B740(4) == 1 )  // 调 调试配置项读取并夹取上下限
        return 0;
    }
    else if ( pDwArg32 == (int *)3 && sub_48B740(5) == 1 )  // 调 调试配置项读取并夹取上下限
    {
      return 0;
    }
  }
  else if ( sub_48B740(3) == 1 )  // 调 调试配置项读取并夹取上下限
  {
    return 0;
  }
  fld_e12 = *(this + 12);  // fld_e12 = this+12
  if ( fld_e12 == 0 )  // 若 fld_e12 == 0
  {
    v9 = *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184);  // 调 表按键查找（uint16）
    v10 = v3[10];
    if ( v9 != 0 )  // 若 v9 != 0
    {
      if ( v10 < 0x10 )  // 若 v10 < 0x10
        v11 = v3 + 5;
      else
        v11 = (uint32_t *)v3[5];
      v12 = sub_41A5E0((unsigned int)v3 + 53);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      v39 = v3[45];
      v37 = v11;
      v36 = v12;
      v13 = (const char *)sub_422E70(1138);
    }
    else
    {
      if ( v10 < 0x10 )  // 若 v10 < 0x10
        v14 = v3 + 5;
      else
        v14 = (uint32_t *)v3[5];
      v15 = sub_41A5E0((unsigned int)v3 + 53);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      v39 = v3[45];
      v37 = v14;
      v36 = v15;
      v13 = (const char *)sub_422E70(1139);
    }
    sprintf(Buffer, v13, v36, v37, v39);  // 调 格式化到缓冲
    goto LABEL_53;  // 跳转 LABEL_53
  }
  if ( fld_e12 != 1 )  // 若 fld_e12 != 1
  {
    if ( fld_e12 != 2 )  // 若 fld_e12 != 2
    {
      if ( fld_e12 == 3 )  // 若 fld_e12 == 3
      {
        fld_e112 = *(this + 11);  // fld_e112 = this+11
        v42 = 0;
        pArg2 = -1;
        if ( (uint8_t)sub_49EFE0(fld_e112, &v42, &pArg2, this + 14) == 0 )  // 调 槽表按键搜索（·sub_48FB60 按 +4 int16 键；回填载荷/键/槽号）
          return 0;
        sub_432EA0("POP_UP", -1, 0, 0);  // 调 音效播放包装（非空判定）
        if ( v3[10] < 0x10u )  // 若 v3[10] < 0x10u
          v29 = v3 + 5;
        else
          v29 = (uint32_t *)v3[5];
        v41 = sub_48FE30(v42);  // 调 组装显示串（串表名 + 表项串 #编号）
        v30 = (const char *)sub_422E70(2032);
        sprintf(Buffer, v30, v29, v41);  // 调 格式化到缓冲
      }
      goto LABEL_53;  // 跳转 LABEL_53
    }
    v18 = *(int **)(dword_8F8504 + 8);
    pArg22 = *v18;
    v20 = *v18 == (uint32_t)v18;
    pDwArg3 = v18;
    pArg2 = pArg22;
    if ( !v20 )  // 若 !v20
    {
      while ( 2 )  // 当 2 循环
      {
        v21 = 0;
        v22 = (uint32_t *)(pArg22 + 56);
        while ( *v22 != *(this + 11) )  // 当 *v22 != *(this + 11) 循环
        {
          ++v21;  // 自增v21
          ++v22;  // 自增v22
          if ( v21 >= 8 )  // 若 v21 >= 8
            goto LABEL_36;  // 跳转 LABEL_36
        }
        v23 = (uint32_t *)(pArg22 + 16);
        if ( pArg22 != -16 )  // 若 pArg22 != -16
        {
          sub_432EA0("POP_UP", -1, 0, 0);  // 调 音效播放包装（非空判定）
          v24 = v23[19];
          if ( v24 != 0 )  // 若 v24 != 0
          {
            v25 = dword_99FEC4[v24];
          }
          else if ( v23[26] < 0x10u )  // 否则若 v23[26] < 0x10u
          {
            v25 = (int)(v23 + 21);
          }
          else
          {
            v25 = v23[21];
          }
          if ( v3[10] < 0x10u )  // 若 v3[10] < 0x10u
            v26 = v3 + 5;
          else
            v26 = (uint32_t *)v3[5];
          v40 = v25;
          v38 = v26;
          v27 = (const char *)sub_422E70(1141);
          sprintf(Buffer, v27, v38, v40);  // 调 格式化到缓冲
          *(this + 13) = sub_42A410(v3);  // 调 图标句柄取用（+116 槽）
          goto LABEL_53;  // 跳转 LABEL_53
        }
LABEL_36:
        sub_4332F0(&pArg2);  // 调 红黑树迭代器自增（后继）
        pArg22 = pArg2;
        if ( (int *)pArg2 != pDwArg3 )  // 若 (int *)pArg2 != pDwArg3
          continue;
        break;
      }
    }
    return 0;
  }
  if ( v3[10] < 0x10u )  // 若 v3[10] < 0x10u
    v16 = v3 + 5;
  else
    v16 = (uint32_t *)v3[5];
  v17 = (const char *)sub_422E70(1140);
  sprintf(Buffer, v17, v16);  // 调 格式化到缓冲
LABEL_53:
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(Buffer, 0);  // 调 sub_69C360
  v31 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v31 + 24))(this, 14, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v34 = 415 - fld_e2[8];
  v35 = 631 - fld_e2[7];
  sub_69A5F0(fld_e2, v35, v34);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v35 + 29, *(uint32_t *)(*(this + 2) + 32) + v34 - 43);  // this+36 = 状态字
  sub_69A5F0((uint32_t *)*(this + 10), v35 + 98, *(uint32_t *)(*(this + 2) + 32) + v34 - 43);  // this+40 = 状态子标志
  *((uint8_t *)this + 73) = 0;  // this+73 = szDigitalName
  *((uint8_t *)this + 74) = 0;
  sub_698F90((int)(this + 15), 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
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
  int fld_e9; // eax
  unsigned int *fld_e18; // ecx
  const char *pThis_C; // eax
  uint32_t *pThis_C2; // eax
  uint8_t *result; // eax
  uint8_t v7[4]; // [esp+4h] [ebp-4h] BYREF

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    if ( *(this + 17) < 0x10u )  // 若 *(this + 17) < 0x10u
      pThis_C = (const char *)(this + 12);
    else
      pThis_C = (const char *)*(this + 12);
    fld_e18 = (unsigned int *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 16) + 80) + 144 * *(this + 18));  // dword_8F7A24 = 当前场景状态对象
    if ( sub_40BF00((std::_String_base *)fld_e18, 0, fld_e18[5], pThis_C, *(this + 16)) == 0 )  // 调 std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      sub_423200(dword_8F7B08, 6);  // 【发送网络包API】
      v7[0] = *((uint8_t *)this + 72);  // v7[0] 写入 *((uint8_t *)this + 72)
      sub_423290(dword_8F7B08, (int)v7, 1);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
      if ( *(this + 17) < 0x10u )  // 若 *(this + 17) < 0x10u
        pThis_C2 = this + 12;
      else
        pThis_C2 = (uint32_t *)*(this + 12);
      sub_41C100(pThis_C2);  // 调 写字符串到发送缓冲（4B 长度 + 内容）
      sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    }
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = (uint8_t *)*(this + 10);  // this+40 = 状态子标志
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x6348E0 sub_6348E0 —— 角色删除清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_6348E0(uint32_t *this)  // 函数: 角色删除清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ------------------------------------------------------------
// 0x6349C0 sub_6349C0 —— 公告数据（4015C0）
// ------------------------------------------------------------
int /*thiscall*/ sub_6349C0(uint32_t *this)  // 函数: 公告数据（4015C0）
{
  int result; // eax

  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  result = sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 18) = -1;  // this+72 = -1
  return result;
}



// ------------------------------------------------------------
// 0x6349F0 CNRDCharacterDeleteConfirmWindow__vmtC —— CNRDCharacterDeleteConfirmWindow__vmtC 文案装配（4015C0 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDCharacterDeleteConfirmWindow__vmtC(char *this, void *Src, int nArg3)  // 函数: CNRDCharacterDeleteConfirmWindow__vmtC 文案装配（4015C0 + 69C340 系）
{
  char *pThis_30; // edi
  char *v5; // eax
  int v6; // edi
  int pThis_3; // eax
  uint32_t *pThis_2; // ecx
  int v9; // ebx
  int v10; // edi

  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  *((uint32_t *)this + 18) = nArg3;  // this+72 = nArg3
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  if ( *((uint32_t *)this + 17) < 0x10u )  // 若 *((uint32_t *)this + 17) < 0x10u
    pThis_30 = this + 48;
  else
    pThis_30 = *((char **)this + 12);
  sub_69C360(pThis_30, 0);  // 调 sub_69C360
  v5 = sub_422E70(917);  // 调 sub_422E70
  sub_69C360(v5, 0);  // 调 sub_69C360
  v6 = *(uint32_t *)this;  // v6 = this
  pThis_3 = sub_69C500(*((uint32_t *)this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(char *, int, int))(v6 + 24))(this, 14, pThis_3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  pThis_2 = *((uint32_t **)this + 2);
  v9 = pt.x - 125 <= 0 ? 0 : pt.x - 125;
  if ( v9 >= 640 - pThis_2[7] )  // 若 v9 >= 640 - pThis_2[7]
    v9 = 640 - pThis_2[7];
  v10 = 480 - pThis_2[8];
  if ( (pt.y - pThis_2[8] + 31 <= 0 ? 0 : pt.y - pThis_2[8] + 31) < v10 )  // 若 (pt.y - pThis_2[8] + 31 <= 0 ? 0 : pt.y - pThis_2[8] + 31) < v10
    v10 = pt.y - pThis_2[8] + 31 <= 0 ? 0 : pt.y - pThis_2[8] + 31;
  sub_69A5F0(pThis_2, v9, v10);  // 调 sub_69A5F0
  sub_69A5F0(*((uint32_t **)this + 9), v9 + 29, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v10 - 43);  // this+8 = 技能槽记录首字
  sub_69A5F0(*((uint32_t **)this + 10), v9 + 98, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v10 - 43);  // this+8 = 技能槽记录首字
  return 1;
}



// ------------------------------------------------------------
// 0x634B10 CNRDNoticeMessageWindow__vmtC —— CNRDNoticeMessageWindow__vmtC 公告装配（69C340 系 + 69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDNoticeMessageWindow__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDNoticeMessageWindow__vmtC 公告装配（69C340 系 + 69A5F0）
{
  int v5; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
  int v8; // ebx
  int v9; // edi

  if ( nArg2 == 0 )  // 若 nArg2 == 0
    return 0;
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(nArg2, 0);  // 调 sub_69C360
  v5 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(int *, int, int))(v5 + 24))(this, 26, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v8 = (480 - fld_e2[8]) / 2;
  v9 = (640 - fld_e2[7]) / 2;
  sub_69A5F0(fld_e2, v9, v8);  // 调 sub_69A5F0
  sub_69A5F0(
    (uint32_t *)*(this + 9),  // this+36 = 状态字
    v9 + ((unsigned int)(*(uint32_t *)(*(this + 2) + 28) - *(uint32_t *)(*(this + 9) + 28)) >> 1),  // this+8 = 技能槽记录首字
    *(uint32_t *)(*(this + 2) + 32) + v8 - 43);  // this+8 = 技能槽记录首字
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
int /*thiscall*/ sub_634BB0(uint32_t *this)  // 函数: 公告清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 288, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  return sub_69A840(v3);  // 调 sub_69A840
}



// ------------------------------------------------------------
// 0x634C40 sub_634C40 —— 任务放弃数据（13 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_634C40(uint32_t *this)  // 函数: 任务放弃数据（13 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = -1;  // this+44 = -1
  return 0;
}



// ------------------------------------------------------------
// 0x634C50 CNRDQuestGiveupConfirmWindow__vmt8 —— CNRDQuestGiveupConfirmWindow__vmt8 确认放弃（47C080 + CLICK_BUTTON2）
// ------------------------------------------------------------
int /*thiscall*/ CNRDQuestGiveupConfirmWindow__vmt8(int *this)  // 函数: CNRDQuestGiveupConfirmWindow__vmt8 确认放弃（47C080 + CLICK_BUTTON2）
{
  int result; // eax
  int fld_e9; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  if ( sub_47C080((uint32_t *)dword_8F8540, *(this + 11)) == 0 )  // dword_8F8540 = 技能/条目全局链
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 20))(this);  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = *(this + 10);  // this+40 = 状态子标志
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 若 *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  }
  return result;
}



// ------------------------------------------------------------
// 0x634CE0 CNRDQuestGiveupConfirmWindow__vmt14 —— CNRDQuestGiveupConfirmWindow__vmt14 放弃执行：QUEST_ABANDON 事件（47C080/47B820/432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDQuestGiveupConfirmWindow__vmt14(int *this)  // 函数: CNRDQuestGiveupConfirmWindow__vmt14 放弃执行：QUEST_ABANDON 事件（47C080/47B820/432EA0）
{
  if ( sub_47C080((uint32_t *)dword_8F8540, *(this + 11)) != 0 )  // dword_8F8540 = 技能/条目全局链
    sub_47B820((uint32_t *)dword_8F8540, *(this + 11));  // dword_8F8540 = 技能/条目全局链
  (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  sub_432EA0("QUEST_ABANDON", -1, 0, 0);  // 调 音效播放包装（非空判定）
  return 1;
}



// ------------------------------------------------------------
// 0x634D30 CNRDQuestGiveupConfirmWindow__vmtC —— CNRDQuestGiveupConfirmWindow__vmtC 文案装配（422E70 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDQuestGiveupConfirmWindow__vmtC(int *this, int *pDwArg2, int nArg3)  // 函数: CNRDQuestGiveupConfirmWindow__vmtC 文案装配（422E70 + 69C340 系）
{
  uint32_t *v5; // eax
  char *v6; // eax
  int v7; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
  int v10; // ebx
  int v11; // edi
  uint32_t *v12; // [esp-Ch] [ebp-94h]
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int dword_796E502; // [esp+84h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  if ( pDwArg2 == nullptr )  // 若 pDwArg2 为空
    return 0;
  *(this + 11) = *pDwArg2;  // this+44 = *pDwArg2
  if ( (unsigned int)pDwArg2[7] < 0x10 )  // 若 (unsigned int)pDwArg2[7] < 0x10
    v5 = pDwArg2 + 2;
  else
    v5 = (uint32_t *)pDwArg2[2];
  v12 = v5;
  v6 = sub_422E70(1136);  // 调 sub_422E70
  sprintf(Buffer, v6, v12);  // 调 格式化到缓冲
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(Buffer, 0);  // 调 sub_69C360
  v7 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(int *, int, int))(v7 + 24))(this, 14, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v10 = pt.x - 125 <= 0 ? 0 : pt.x - 125;
  if ( v10 >= 640 - fld_e2[7] )  // 若 v10 >= 640 - fld_e2[7]
    v10 = 640 - fld_e2[7];
  v11 = 480 - fld_e2[8];
  if ( (pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31) < v11 )  // 若 (pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31) < v11
    v11 = pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31;
  sub_69A5F0(fld_e2, v10, v11);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v10 + 29, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);  // this+36 = 状态字
  sub_69A5F0((uint32_t *)*(this + 10), v10 + 98, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);  // this+40 = 状态子标志
  return 1;
}



// ------------------------------------------------------------
// 0x634E60 sub_634E60 —— 任务放弃清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_634E60(uint32_t *this)  // 函数: 任务放弃清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ============================================================
// 【分区 14】退出副本确认 CNRDWalkoutConfirmWindow（0x634F40-0x635250）
// vmt14 执行退场（48F500）。
// ============================================================
// ------------------------------------------------------------
// 0x634F40 sub_634F40 —— 退场数据（13 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_634F40(uint32_t *this)  // 函数: 退场数据（13 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = 0xFFFF;  // 常量 0xFFFF（= 0xFFFF）
  return 0;
}



// ------------------------------------------------------------
// 0x634F50 CNRDWalkoutConfirmWindow__vmt8 —— CNRDWalkoutConfirmWindow__vmt8 确认退场（429830 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDWalkoutConfirmWindow__vmt8(uint32_t *this)
{
  int fld_e9; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  if ( *(this + 11) != 0xFFFF && sub_429830((uint32_t *)dword_8F8500, *((uint16_t *)this + 22)) == 0 )  // 调 表按键查找（uint16）
    *(this + 11) = 0xFFFF;  // 常量 0xFFFF（= 0xFFFF）
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 20))(this);  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = (uint8_t *)*(this + 10);  // this+40 = 状态子标志
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x634FF0 CNRDWalkoutConfirmWindow__vmt14 —— CNRDWalkoutConfirmWindow__vmt14 退场执行（48F500）
// ------------------------------------------------------------
char /*thiscall*/ CNRDWalkoutConfirmWindow__vmt14(uint32_t *this)  // 函数: CNRDWalkoutConfirmWindow__vmt14 退场执行（48F500）
{
  int fld_e11; // edx
  int v3; // eax
  uint32_t *i; // ecx

  if ( dword_99FEC0 != 0 )  // 若 dword_99FEC0 != 0
  {
    fld_e11 = *(this + 11);  // fld_e11 = this+11
    if ( fld_e11 != 0xFFFF )  // 若 fld_e11 != 0xFFFF
    {
      v3 = 0;
      for ( i = (uint32_t *)(dword_99FEC0 + 40); *i != fld_e11; ++i )  // 循环：i = (uint32_t *)(dword_99FEC0 + 40); *i != fld_e11; ++i
      {
        if ( ++v3 >= 8 )  // 若 ++v3 >= 8
        {
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
          return 1;
        }
      }
      sub_48F500(v3, 254);  // 调 座位状态上报发包（op 55）
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x635050 CNRDWalkoutConfirmWindow__vmtC —— CNRDWalkoutConfirmWindow__vmtC 文案装配（429830 + 422E70 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDWalkoutConfirmWindow__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDWalkoutConfirmWindow__vmtC 文案装配（429830 + 422E70 + 69C340 系）
{
  int v4; // eax
  int v6; // eax
  char *v7; // eax
  int v8; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
  int v11; // ebx
  int v12; // edi
  int v13; // [esp-Ch] [ebp-94h]
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int dword_796E502; // [esp+84h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  *(this + 11) = nArg3;  // this+44 = nArg3
  v4 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)nArg3);  // 调 表按键查找（uint16）
  if ( v4 == 0 )  // 若 v4 == 0
    return 0;
  if ( *(uint32_t *)(v4 + 40) < 0x10u )  // 若 *(uint32_t *)(v4 + 40) < 0x10u
    v6 = v4 + 20;
  else
    v6 = *(uint32_t *)(v4 + 20);  // v6 = v4+20
  v13 = v6;
  v7 = sub_422E70(1175);  // 调 sub_422E70
  sprintf(Buffer, v7, v13);  // 调 格式化到缓冲
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(Buffer, 0);  // 调 sub_69C360
  v8 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(int *, int, int))(v8 + 24))(this, 14, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v11 = (480 - fld_e2[8]) / 2;
  v12 = (640 - fld_e2[7]) / 2;
  sub_69A5F0(fld_e2, v12, v11);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v12 + 29, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);  // this+36 = 状态字
  sub_69A5F0((uint32_t *)*(this + 10), v12 + 98, *(uint32_t *)(*(this + 2) + 32) + v11 - 43);  // this+40 = 状态子标志
  return 1;
}



// ------------------------------------------------------------
// 0x635170 sub_635170 —— 退场清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_635170(uint32_t *this)  // 函数: 退场清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ============================================================
// 【分区 15】PVP 房间创建/信息（0x635250-0x636030）
// CNRDPVPRoomCreateWindow：vmt8 Update（144 行，522500/540870 数量控件
// + 423200 系参数）；CNRDPVPRoomInfoWindow：vmt8 进入房间（487420/48F6C0）。
// ============================================================
// ------------------------------------------------------------
// 0x635250 sub_635250 —— PVP 房间数据（29 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_635250(uint32_t *this)  // 函数: PVP 房间数据（29 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = bAuraState
  *(this + 14) = 0;  // this+56 = 0
  *(this + 15) = 0;  // this+60 = 0
  *(this + 16) = 0;  // this+64 = 0
  *(this + 17) = 0;  // this+68 = 0
  *(this + 18) = 0;  // this+72 = 0
  *(this + 19) = 0;  // this+76 = 0
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 25) = 0;  // this+100 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 27) = 0;  // this+108 = 0
  *(this + 28) = 0;  // this+112 = pHostComp
  *(this + 29) = 0;  // this+116 = 0
  return this + 14;
}



// ------------------------------------------------------------
// 0x6352A0 sub_6352A0 —— PVP 房间数据 2（41 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6352A0(uint32_t *this)  // 函数: PVP 房间数据 2（41 行）
{
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  uint32_t *pThis_E; // esi
  int i; // edi

  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);  // this+40 = 状态子标志
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    result = (**fld_e10)(fld_e10, 1);
  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;  // this+40 = 状态子标志
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    result = (**fld_e11)(fld_e11, 1);
  fld_e12 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 11) = 0;  // this+44 = 0
  if ( fld_e12 != nullptr )  // 若 fld_e12 非空
    result = (**fld_e12)(fld_e12, 1);
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);  // this+52 = bAuraState
  *(this + 12) = 0;  // this+48 = 0
  if ( fld_e13 != nullptr )  // 若 fld_e13 非空
    result = (**fld_e13)(fld_e13, 1);
  *(this + 13) = 0;  // this+52 = bAuraState
  pThis_E = this + 14;
  for ( i = 16; i != 0; --i )  // 循环：i = 16; i != 0; --i
  {
    if ( *pThis_E != 0 )  // 若 *pThis_E != 0
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_E)(*pThis_E, 1);
    *pThis_E++ = 0;  // *pThis_E++ 写入 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x635310 CNRDPVPRoomCreateWindow__vmt8 —— CNRDPVPRoomCreateWindow__vmt8 Update（144 行：522500 房名 + 540870 数量 + 69B740/69BCC0 输入 + 4BF300）
// ------------------------------------------------------------
int /*thiscall*/ sub_635310(int *this)  // 【CNRDPVPRoomCreateWindow__vmt8】
{
  int result; // eax
  int fld_e2; // eax
  int fld_e22; // eax
  int v5; // edx
  int v6; // eax
  int fld_e11; // eax
  int fld_e10; // eax
  char v9; // cl
  int v10; // eax
  const char *fld_e102; // eax
  int nLen2; // ebx
  int nCmp; // eax
  const char *fld_e103; // eax
  int fld_e112; // eax
  int fld_e13; // eax
  int fld_e12; // eax
  int *pThis_E; // eax
  bool fld_e14; // dl
  int i; // ecx
  int v21; // esi
  int v22; // eax
  uint32_t *pThis_E2; // ecx
  int fld_e104; // esi
  const char *v25; // ebx
  int *pThis_E3; // eax
  int j; // ecx
  int v28; // edx
  unsigned int nLen; // [esp+4h] [ebp-8h] BYREF
  uint8_t v30[4]; // [esp+8h] [ebp-4h] BYREF

  if ( dword_9B9534 == 0 )  // 若 dword_9B9534 == 0
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  if ( *(uint8_t *)(fld_e2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e2 + 12) )  // 若 *(uint8_t *)(fld_e2 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    dword_79BE4C = *(uint32_t *)(*(this + 10) + 12);  // this+40 = 状态子标志
    dword_79BE54 = dword_79BE4C;
    fld_e22 = *(this + 2);  // this+8 = 技能槽记录首字
    v5 = *(uint32_t *)(fld_e22 + 20);  // v5 = fld_e22+20
    v6 = *(uint32_t *)(fld_e22 + 24);  // v6 = fld_e22+24
    if ( pt.x >= v5 + 43 && pt.x < v5 + 193 && pt.y >= v6 + 36 && pt.y < v6 + 52 && sub_522500(*(this + 10)) != 0 )  // this+40 = 状态子标志
      sub_540870(szPassword);  // 调 数量窗口打开（69BCC0/402AE0 控件显示）
  }
  fld_e11 = *(this + 11);  // fld_e11 = this+11
  if ( *(uint8_t *)(fld_e11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e11 + 12)  // 若 *(uint8_t *)(fld_e11 + 17) != 0 && dword_79BE34 == *(uint32_t ..
    || (fld_e10 = *(this + 10), v9 = *(uint8_t *)(fld_e10 + 116), *(uint8_t *)(fld_e10 + 116) = 0, v9 != 0) )  // this+40 = 状态子标志
  {
    nLen = strlen((const char *)sub_69B740(*(this + 10)));  // 调 返回字符串长度（逐字节扫描）
    if ( nLen != 0 )  // 若 nLen != 0
    {
      fld_e102 = (const char *)sub_69B740(*(this + 10));  // this+40 = 状态子标志
      if ( strstr(fld_e102, "%") == nullptr )  // 调 查子串
      {
        nLen2 = 0;
        nLen = 0;
        while ( 1 )  // 无限循环
        {
          nCmp = strcmp((const char *)sub_69B740(*(this + 10)), (const char *)dword_99FEC8[nLen2++]);  // this+40 = 状态子标志
          if ( nCmp == 0 )  // 若 nCmp == 0
            break;
          if ( nLen2 >= 16 )  // 若 nLen2 >= 16
          {
            nLen2 = nLen;
            break;
          }
        }
        sub_423200(dword_8F7B08, 53);  // 【发送网络包API】
        v30[0] = nLen2;
        sub_423290(v30, 1);  // 调 sub_423290
        if ( nLen2 == 0 )  // 若 nLen2 == 0
        {
          fld_e103 = (const char *)sub_69B740(*(this + 10));  // this+40 = 状态子标志
          sub_41C100(fld_e103);  // 调 写字符串到发送缓冲（4B 长度 + 内容）
        }
        nLen = 0;
        sub_423290(&nLen, 2);  // 调 sub_423290
        sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
        (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
        goto LABEL_26;  // 跳转 LABEL_26
      }
      v10 = sub_422E70(1135);  // 调 sub_422E70
    }
    else
    {
      v10 = sub_422E70(1134);  // 调 sub_422E70
    }
    sub_44E8D0((char *)*(this + 4), (void *)0x1B, v10, 0);  // 调 对象池借出（按池号取可用对象）
  }
LABEL_26:
  fld_e112 = *(this + 11);  // fld_e112 = this+11
  if ( *(uint8_t *)(fld_e112 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e112 + 12) )  // 若 *(uint8_t *)(fld_e112 + 17) != 0 && dword_79BE34 == *(uint32_t..
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  fld_e13 = *(this + 13);  // this+52 = bAuraState
  if ( *(uint8_t *)(fld_e13 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e13 + 12) )  // 若 *(uint8_t *)(fld_e13 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  fld_e12 = *(this + 12);  // fld_e12 = this+12
  if ( *(uint8_t *)(fld_e12 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e12 + 12) )  // 若 *(uint8_t *)(fld_e12 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    pThis_E = this + 14;
    fld_e14 = *(uint8_t *)(*(this + 14) + 16) == 0;
    for ( i = 16; i != 0; --i )  // 循环：i = 16; i != 0; --i
    {
      v21 = *pThis_E++;  // 取 *pThis_E 后自增
      *(uint8_t *)(v21 + 16) = fld_e14;  // v21+16 = fld_e14
    }
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  v22 = 0;
  pThis_E2 = this + 14;
  while ( *(uint8_t *)(*pThis_E2 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*pThis_E2 + 12) )  // 当 *(uint8_t *)(*pThis_E2 + 17) == 0 || dword_79BE34 != *(uint32_.. 循环
  {
    ++v22;  // 自增v22
    ++pThis_E2;  // 自增pThis_E2
    if ( v22 >= 16 )  // 若 v22 >= 16
      goto LABEL_45;  // 跳转 LABEL_45
  }
  fld_e104 = *(this + 10);  // this+40 = 状态子标志
  v25 = (const char *)dword_99FEC8[v22];
  sub_69BCC0(fld_e104);  // 调 sub_69BCC0
  sub_402AE0(fld_e104 + 180, v25);  // 调 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
  pThis_E3 = this + 14;
  for ( j = 16; j != 0; --j )  // 循环：j = 16; j != 0; --j
  {
    v28 = *pThis_E3++;  // 取 *pThis_E3 后自增
    *(uint8_t *)(v28 + 16) = 0;  // v28+16 = 0
  }
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
LABEL_45:
  sub_4BF300(dword_8F8558, 0, 0);  // 调 槽写侧（+64 + 索引）
  result = *(this + 4);  // result = this+4
  *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(result + 28) + 136) + 17) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x635630 CNRDPVPRoomCreateWindow__vmtC —— CNRDPVPRoomCreateWindow__vmtC 打开槽（69A5F0 + 43B920 + 69BCC0/402AE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPVPRoomCreateWindow__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDPVPRoomCreateWindow__vmtC 打开槽（69A5F0 + 43B920 + 69BCC0/402AE0）
{
  int fld_e2; // ecx
  unsigned int v5; // edi
  int v6; // edx
  int fld_e22; // ecx
  uint32_t *fld_e23; // edi
  unsigned int v9; // eax
  unsigned int v10; // edx
  int nRand; // ebx
  int *pThis_E; // eax
  int i; // ecx
  int v14; // edx

  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  v5 = *(uint32_t *)(fld_e2 + 28);  // v5 = fld_e2+28
  v6 = pt.y - (*(uint32_t *)(fld_e2 + 32) >> 1);
  if ( ((int)(pt.x - (v5 >> 1)) <= 0 ? 0 : pt.x - (v5 >> 1)) >= 640 - v5 )  // 若 ((int)(pt.x - (v5 >> 1)) <= 0 ? 0 : pt.x - (v5 >> 1)) >= 640 -..
    fld_e22 = 640 - *(uint32_t *)(*(this + 2) + 28);  // this+8 = 技能槽记录首字
  else
    fld_e22 = (int)(pt.x - (v5 >> 1)) <= 0 ? 0 : pt.x - (v5 >> 1);
  fld_e23 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v9 = 480 - fld_e23[8];
  v10 = v6 <= 0 ? 0 : v6;
  if ( v10 < v9 )  // 若 v10 < v9
    v9 = v10;
  sub_69A5F0(fld_e23, fld_e22, v9);  // 调 sub_69A5F0
  sub_43B920(*(uint32_t *)(*(this + 4) + 28), 0);  // 调 输入面板开关
  nRand = dword_99FEC8[rand() % 16];  // 调 以 16 位种子状态递推并返回 15 位结果
  sub_69BCC0(*(this + 10));  // this+40 = 状态子标志
  sub_402AE0(nRand);  // 调 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
  dword_79BE4C = *(uint32_t *)(*(this + 10) + 12);  // this+40 = 状态子标志
  dword_79BE54 = dword_79BE4C;
  pThis_E = this + 14;
  for ( i = 16; i != 0; --i )  // 循环：i = 16; i != 0; --i
  {
    v14 = *pThis_E++;  // 取 *pThis_E 后自增
    *(uint8_t *)(v14 + 16) = 0;  // v14+16 = 0
  }
  return 1;
}



// ------------------------------------------------------------
// 0x635710 CNRDPVPRoomCreateWindow__vmt10 —— CNRDPVPRoomCreateWindow__vmt10 状态切换槽（22 行）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPVPRoomCreateWindow__vmt10(uint32_t *this)  // 函数: CNRDPVPRoomCreateWindow__vmt10 状态切换槽（22 行）
{
  int fld_e4; // eax
  int result; // eax

  fld_e4 = *(uint32_t *)(*(this + 4) + 28);
  if ( *(uint8_t *)(fld_e4 + 256) == 0 )  // 若 *(uint8_t *)(fld_e4 + 256) == 0
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(fld_e4 + 124) + 12);
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
char /*thiscall*/ CNRDPVPRoomCreateWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDPVPRoomCreateWindow__vmt0 构造（418DD0 + 491530/491630，66 行）
{
  int v3; // edi
  int v4; // esi
  int pObj; // eax
  int pObj3; // eax
  uint32_t *pThis_E; // eax
  int v8; // edi
  int v9; // edi
  int v10; // esi
  int pObj2; // eax

  IRDPopupWindow__vmt0(pArg2);  // 调 IRDPopupWindow__vmt0 构造
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v3 = *(uint32_t *)(pArg2 + 20);  // v3 = pArg2+20
    v4 = *(uint32_t *)(pArg2 + 24);  // v4 = pArg2+24
    pObj = sub_418DD0(104);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v3 + 8, v4 + 8, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj3 = sub_418DD0(141);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v3 + 73, v4 + 13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pThis_E = (uint32_t *)sub_418DD0(100);
    if ( pThis_E != nullptr )  // 若 pThis_E 非空
      LOBYTE(pThis_E) = (*(char (/*thiscall*/ **)(uint32_t *, int, int, int))(*pThis_E + 152))(pThis_E, v3 + 8, v4 + 35, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  }
  else
  {
    v8 = 0;
    pThis_E = this + 14;
    while ( pArg2 != *pThis_E )  // 当 pArg2 != *pThis_E 循环
    {
      ++v8;  // 自增v8
      ++pThis_E;  // 自增pThis_E
      if ( v8 >= 16 )  // 若 v8 >= 16
        return (char)pThis_E;
    }
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      *(uint32_t *)(pArg2 + 20) + 4,
      *(uint32_t *)(pArg2 + 24) + 4,
      -1,
      dword_99FEC8[v8]);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    LOBYTE(pThis_E) = *(uint8_t *)(pArg2 + 17);  // 调 取 16 位值低 8 位
    if ( (uint8_t)pThis_E != 0 && dword_79BE3C == *(uint32_t *)(pArg2 + 12) )  // 若 (uint8_t)pThis_E != 0 && dword_79BE3C == *(uint32_t *)(pArg2 +..
    {
      sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      v9 = *(uint32_t *)(pArg2 + 24);  // v9 = pArg2+24
      v10 = *(uint32_t *)(pArg2 + 20);  // v10 = pArg2+20
      pObj2 = sub_418DD0(96);  // 调 sub_418DD0
      if ( pObj2 != 0 )  // 若 pObj2 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v10, v9, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      LOBYTE(pThis_E) = sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
    }
  }
  return (char)pThis_E;
}



// ------------------------------------------------------------
// 0x6358C0 sub_6358C0 —— PVP 房间页绘制（43C060/69A5F0/69A840/43C410 + 426BD0/69C6B0，82 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6358C0(int *this)  // 函数: PVP 房间页绘制（43C060/69A5F0/69A840/43C410 + 426BD0/69C6B0，82 行）
{
  void *pMem; // eax
  int v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_e92; // eax
  uint32_t *pMem4; // eax
  uint32_t *fld_e93; // eax
  uint32_t *pThis_E; // ebx
  uint32_t *pMem5; // edi
  void *Block; // [esp+10h] [ebp-14h]
  int v14; // [esp+14h] [ebp-10h]

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+36 = 状态字
  pMem = operator new(0xE4u);  // operator new 分配 228 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C060((int)pMem, 19, 155);  // 调 nengine::CNEdit 构造
  else
    v3 = 0;
  *(this + 10) = v3;  // this+40 = 状态子标志
  dword_9D3BD8 = dword_99FCCC;
  sub_69A5F0((uint32_t *)*(this + 10), 46, 39);  // this+40 = 状态子标志
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e9 = sub_43C410(pMem2, *(this + 9), 65, 66, 67, 65, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 11) = (int)fld_e9;  // this+44 = (int)fld_e9
  sub_69A5F0(fld_e9, 83, 58);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  pMem3 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    fld_e92 = sub_43C410(pMem3, *(this + 9), 91, 92, 93, 91, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e92 = nullptr;  // fld_e92 = nullptr 空指针
  *(this + 12) = (int)fld_e92;  // this+48 = (int)fld_e92
  sub_69A5F0(fld_e92, 195, 37);  // 调 sub_69A5F0
  sub_69A840(*(this + 12));  // 调 sub_69A840
  pMem4 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    fld_e93 = sub_43C410(pMem4, *(this + 9), 23, 24, 25, 23, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e93 = nullptr;  // fld_e93 = nullptr 空指针
  *(this + 13) = (int)fld_e93;  // this+52 = bAuraState
  sub_69A5F0(fld_e93, 195, 11);  // 调 sub_69A5F0
  sub_69A840(*(this + 13));  // this+52 = bAuraState
  v14 = 52;
  pThis_E = this + 14;
  do
  {
    pMem5 = operator new(0x6Cu);  // operator new 分配 108 字节
    if ( pMem5 != nullptr )  // 若 pMem5 非空
    {
      Block = (void *)*(this + 9);  // this+36 = 状态字
      sub_426BD0(pMem5);  // 调 nengine::IControl 构造
      *pMem5 = &vftbl_nengine__CNFrame;  // *pMem5 写入 &vftbl_nengine__CNFrame
      sub_69C6B0(pMem5);  // 调 sub_69C6B0
      nengine__CNFrame__vmt20(Block, 95);
    }
    else
    {
      pMem5 = nullptr;  // pMem5 = nullptr 空指针
    }
    *pThis_E = pMem5;  // *pThis_E 写入 pMem5
    pMem5[17] = this;
    sub_69A5F0((uint32_t *)*pThis_E, 42, v14);  // 调 sub_69A5F0
    sub_69A840(*pThis_E++);  // 调 sub_69A840
    v14 += 18;
  }
  while ( v14 < 340 );  // 当 v14 < 340 循环
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 17, 6);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 28))(this, 3);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
}



// ------------------------------------------------------------
// 0x635B00 CNRDPVPRoomInfoWindow__vmtC —— CNRDPVPRoomInfoWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPVPRoomInfoWindow__vmtC(uint32_t **this, int nArg2, int nArg3)  // 函数: CNRDPVPRoomInfoWindow__vmtC 打开槽（69A5F0）
{
  dword_795D3C = nArg3;
  sub_69A5F0(*(this + 2), (640 - (*(this + 2))[7]) / 2, (480 - (*(this + 2))[8]) / 2);  // this+8 = 技能槽记录首字
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
  int fld_e10; // eax
  int v4; // eax
  int dword_795D3C2; // [esp+4h] [ebp-4h] BYREF

  if ( dword_795D3C == -1 )  // 若 dword_795D3C == -1
    return (uint8_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e10 = *(this + 10);  // this+40 = 状态子标志
  if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )  // 若 *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  v4 = sub_487420(dword_795D3C);  // 调 按键取节点载荷（未命中返回 0）
  *(uint8_t *)(*(this + 11) + 17) = v4 != 0 && *(uint32_t *)(v4 + 72) != 2 && sub_48F6C0(v4) != 0;  // 调 未装载槽计数
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    sub_423200(dword_8F7B08, 54);  // 【发送网络包API】
    dword_795D3C2 = dword_795D3C;
    sub_423290(dword_8F7B08, (int)&dword_795D3C2, 2);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x635C40 CNRDPVPRoomInfoWindow__vmt0 —— CNRDPVPRoomInfoWindow__vmt0 构造（125 行：554930 + 487420/48F690/42B340/452580 + 40FC80/42A430/42A410）
// ------------------------------------------------------------
int /*userpurge*/ sub_635C40@<eax>(int pArg1@<ecx>, int nArg2@<esi>, int pArg3)  // 函数: CNRDPVPRoomInfoWindow__vmt0 构造（125 行：554930 + 487420/48F690/42B340/452580 + 40FC80/42A430/42A410）
{
  int result; // eax
  int v5; // esi
  int v6; // edi
  int pObj; // eax
  int pObj3; // eax
  int v9; // esi
  int v10; // edi
  int pObj6; // eax
  int pObj4; // eax
  int v13; // eax
  int v14; // ebx
  int pObj5; // eax
  int v16; // esi
  int v17; // eax
  int v18; // eax
  int v19; // esi
  int pObj7; // eax
  int pObj2; // eax
  int v22; // ebx
  bool v23; // cc
  int *v25; // [esp+Ch] [ebp-Ch]
  int v26; // [esp+10h] [ebp-8h]
  int v28; // [esp+20h] [ebp+8h]

  result = sub_554930(pArg3);  // 【IRDPopupWindow__vmt0】
  if ( pArg3 == *(uint32_t *)(pArg1 + 8) )  // 若 pArg3 == *(uint32_t *)(pArg1 + 8)
  {
    v5 = *(uint32_t *)(pArg3 + 20);  // v5 = pArg3+20
    v6 = *(uint32_t *)(pArg3 + 24);  // v6 = pArg3+24
    pObj = sub_418DD0(103);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v5 + 8, v6 + 8, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj3 = sub_418DD0(101);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v5 + 47, v6 + 12, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    result = sub_487420(dword_795D3C);  // 调 按键取节点载荷（未命中返回 0）
    if ( result != 0 )  // 若 result != 0
    {
      v9 = v5 + 9;
      v10 = v6 + 34;
      v28 = v9;
      v26 = 0;
      v25 = (int *)(result + 8);
      do
      {
        pObj6 = sub_418DD0(45);  // 调 sub_418DD0
        if ( pObj6 != 0 )  // 若 pObj6 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v9, v10, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        if ( *v25 == 254 )  // 若 *v25 == 254
        {
          pObj4 = sub_418DD0(48);  // 调 sub_418DD0
          if ( pObj4 != 0 )  // 若 pObj4 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v9, v10, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        }
        else if ( *v25 != 255 )  // 否则若 *v25 != 255
        {
          v13 = sub_48F690(v26);  // 调 槽 id 解析·第二组（偏移 +10）
          v14 = v13;
          if ( v13 != 0 )  // 若 v13 != 0
          {
            pObj5 = sub_42B340(v13);  // 调 虚拟角色惰性创建（0x294 字节）
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, int))(*(uint32_t *)pObj5 + 384))(  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
              pObj5,
              v9,
              v10,
              16,
              16,
              1065353216,
              nArg2);
            v16 = *v25;
            if ( *v25 < 1 || v16 > 3 || (uint8_t)sub_452580(v26) != 0 )  // 调 槽位类别查询（表值 4/3 判定）
            {
              v19 = v28;
            }
            else
            {
              sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
              v17 = sub_418DD0(v16 + 88);  // 调 sub_418DD0
              sub_40FC80(v28, v10, v17);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
              v18 = sub_418DD0(v16 + 96);  // 调 sub_418DD0
              v19 = v28;
              sub_40FC80(v28 + 18, v10, v18);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
              sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
            }
            sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
            pObj7 = sub_42A430(v14);  // 调 同构 ·0x42A410
            if ( pObj7 != 0 )  // 若 pObj7 != 0
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v19 + 20, v10, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
            pObj2 = sub_42A410(v14);  // 调 图标句柄取用（+116 槽）
            if ( pObj2 != 0 )  // 若 pObj2 != 0
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v19 + 20, v10, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            nArg2 = pArg1 + 48;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
            if ( *(uint32_t *)(v14 + 40) < 0x10u )  // 若 *(uint32_t *)(v14 + 40) < 0x10u
              v22 = v14 + 20;
            else
              v22 = *(uint32_t *)(v14 + 20);  // v22 = v14+20
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              v19 + 30,
              v10 + 3,
              -1,
              v22);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
            v9 = v28;
          }
        }
        result = v26 + 1;
        v10 += 17;
        v23 = ++v26 < 8;
        ++v25;  // 自增v25
      }
      while ( v23 );  // 当 v23 循环
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x635ED0 sub_635ED0 —— PVP 房间信息清理（43C410/69A5F0/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_635ED0(uint32_t *this)  // 函数: PVP 房间信息清理（43C410/69A5F0/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e92; // eax
  int v6; // edx

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+36 = 状态字
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e9 = sub_43C410(pMem, *(this + 9), 23, 24, 25, 23, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 10) = fld_e9;  // this+40 = 状态子标志
  sub_69A5F0(fld_e9, 136, 11);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e92 = sub_43C410(pMem2, *(this + 9), 62, 63, 64, 99, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e92 = nullptr;  // fld_e92 = nullptr 空指针
  *(this + 11) = fld_e92;  // this+44 = fld_e92
  sub_69A5F0(fld_e92, 36, 174);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;  // this+60 = 0
  *(this + 16) = 6;  // this+64 = 6
  *(this + 17) = 12;  // this+68 = 12
  *(this + 18) = 0;  // this+72 = 0
  *(this + 19) = 1600;  // this+76 = 1600
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  v6 = *this;
  *(this + 24) = dword_99FCCC;  // this+96 = dword_99FCCC
  *(this + 13) = -16777216;  // this+52 = bAuraState
  *(this + 19) = 144;  // this+76 = 144
  *(this + 15) = 1;  // this+60 = 1
  *(this + 20) = 1;  // this+80 = nAuraStage
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v6 + 24))(this, 12, 15);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 3);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
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
int /*thiscall*/ sub_636030(uint32_t *this)  // 函数: 组队信息数据（13 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = 0;  // this+44 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x636040 CNRDPartyInfoWindow__vmt8 —— CNRDPartyInfoWindow__vmt8 Update（CLICK_BUTTON2 + 4569F0/56A720/4564A0 成员操作）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDPartyInfoWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax
  int fld_e10; // eax
  int v4; // eax
  int v5; // edi

  if ( (uint8_t)sub_545510(3) == 0 || dword_795D40 == -1 )  // 调 输入框取值（25 行——社区/摆摊/组队窗口共用的文本框读取）
    return (uint8_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e10 = *(this + 10);  // this+40 = 状态子标志
  if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )  // 若 *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  v4 = sub_4569F0((uint32_t *)dword_8F850C, dword_795D40);  // 调 队员槽查询
  v5 = v4;
  *(uint8_t *)(*(this + 11) + 17) = v4 != 0
                               && *(uint32_t *)(v4 + 60) - sub_56A720(v4) > 0  // 调 组队列表联动（55 行）
                               && *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) == 0;  // 调 表按键查找（uint16）
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    sub_4564A0(*(uint32_t *)(v5 + 4 * *(uint32_t *)(v5 + 56) + 40));  // 调 组队邀请发送
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x636140 CNRDPartyInfoWindow__vmtC —— CNRDPartyInfoWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyInfoWindow__vmtC(uint32_t **this, int nArg2, int nArg3)  // 函数: CNRDPartyInfoWindow__vmtC 打开槽（69A5F0）
{
  dword_795D40 = nArg3;
  sub_69A5F0(*(this + 2), (640 - (*(this + 2))[7]) / 2, (480 - (*(this + 2))[8]) / 2);  // this+8 = 技能槽记录首字
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
int /*cdecl*/ sub_636190(int pArg1, int nArg2)  // 函数: 组队成员数据（56A680，27 行）
{
  int v2; // esi
  int v3; // eax
  uint32_t *i; // edx

  v2 = 0;
  v3 = 0;
  for ( i = (uint32_t *)(pArg1 + 40); *i == 0xFFFF; ++i )  // 常量 0xFFFF（= 0xFFFF）
  {
LABEL_5:
    if ( ++v3 >= 4 )  // 若 ++v3 >= 4
      return 0;
  }
  if ( v2 != nArg2 )  // 若 v2 != nArg2
  {
    ++v2;  // 自增v2
    goto LABEL_5;  // 跳转 LABEL_5
  }
  return sub_56A680(v3);  // 调 频道对象辅助（429830）
}



// ------------------------------------------------------------
// 0x6361D0 CNRDPartyInfoWindow__vmt0 —— CNRDPartyInfoWindow__vmt0 构造（175 行：554930 + 4569F0/56A680/42B340/456480 + 422E70）
// ------------------------------------------------------------
char /*userpurge*/ sub_6361D0@<al>(int pArg1@<ecx>, int nArg2@<edi>, int pArg3)  // 函数: CNRDPartyInfoWindow__vmt0 构造（175 行：554930 + 4569F0/56A680/42B340/456480 + 422E70）
{
  int v4; // eax
  int v5; // edi
  int v6; // esi
  int pObj2; // eax
  int pObj4; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // edi
  int v12; // esi
  int v13; // eax
  uint32_t *v14; // ecx
  uint32_t *v15; // esi
  int pObj7; // eax
  int pObj; // eax
  int pObj6; // eax
  int pObj8; // eax
  int v20; // eax
  uint32_t *v21; // ecx
  int v22; // eax
  int pObj5; // eax
  int pObj3; // eax
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

  LOBYTE(v4) = sub_554930(pArg3);  // 【IRDPopupWindow__vmt0】
  if ( pArg3 != *(uint32_t *)(pArg1 + 8) )  // 若 pArg3 != *(uint32_t *)(pArg1 + 8)
    return v4;
  v5 = *(uint32_t *)(pArg3 + 20);  // v5 = pArg3+20
  v6 = *(uint32_t *)(pArg3 + 24);  // v6 = pArg3+24
  pObj2 = sub_418DD0(104);  // 调 sub_418DD0
  if ( pObj2 != 0 )  // 若 pObj2 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v5 + 8, v6 + 8, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  pObj4 = sub_418DD0(140);  // 调 sub_418DD0
  if ( pObj4 != 0 )  // 若 pObj4 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v5 + 79, v6 + 12, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  v4 = sub_4569F0(dword_795D40);  // 调 队员槽查询
  v9 = v4;
  v36 = v4;
  if ( v4 == 0 )  // 若 v4 == 0
    return v4;
  v10 = 0;
  v11 = v5 + 9;
  v38 = v6 + 33;
  v37 = 0;
  v39 = v6 + 36;
  while ( 2 )  // 当 2 循环
  {
    v12 = 0;
    v13 = 0;
    v14 = (uint32_t *)(v9 + 40);
    while ( *v14 == 0xFFFF )  // 当 *v14 == 0xFFFF 循环
    {
LABEL_13:
      ++v13;  // 自增v13
      ++v14;  // 自增v14
      if ( v13 >= 4 )  // 若 v13 >= 4
      {
        v15 = nullptr;  // v15 = nullptr 空指针
        goto LABEL_15;  // 跳转 LABEL_15
      }
    }
    if ( v12 != v10 )  // 若 v12 != v10
    {
      ++v12;  // 自增v12
      goto LABEL_13;  // 跳转 LABEL_13
    }
    v15 = (uint32_t *)sub_56A680(v13);  // 调 频道对象辅助（429830）
LABEL_15:
    pObj7 = sub_418DD0(45);  // 调 sub_418DD0
    if ( pObj7 != 0 )  // 若 pObj7 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v11, v38, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    if ( v15 != nullptr )  // 若 v15 非空
    {
      pObj = sub_42B340(v15);  // 调 虚拟角色惰性创建（0x294 字节）
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, int))(*(uint32_t *)pObj + 384))(  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        pObj,
        v11,
        v38,
        16,
        16,
        1065353216,
        nArg2);
      if ( v37 == sub_456480(dword_8F850C) )  // 若 v37 == sub_456480(dword_8F850C)
      {
        pObj6 = sub_418DD0(106);  // 调 sub_418DD0
        if ( pObj6 != 0 )  // 若 pObj6 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v11 - 1, v39 - 4, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      }
      else
      {
        pObj8 = sub_418DD0(107);  // 调 sub_418DD0
        if ( pObj8 != 0 )  // 若 pObj8 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, v11, v38, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      }
      nArg2 = pArg1 + 48;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
      v20 = sub_41A5E0((unsigned int)v15 + 53);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        v11 + 26,
        v39,
        -4732715,
        "Lv.%d",
        v20);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, pArg1 + 100);  // 调用虚函数（虚表槽 +68）【推断: 观察者组件懒创建（0x10 字节）】
      if ( v15[10] < 0x10u )  // 若 v15[10] < 0x10u
        v21 = v15 + 5;
      else
        v21 = (uint32_t *)v15[5];
      (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        v11 - 3,
        v39,
        -4732715,
        v21);
      v35 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      v22 = sub_4B0EC0(v15[11], v15[12]);  // 调 表记录字符串取值（28 字节/条）
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(v35 + 80))(dword_79C0B0, v11 + 73, v39, -8005942, v22);  // 调用虚函数（虚表槽 +80）
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    }
    else if ( v37 >= *(uint32_t *)(v36 + 60) )  // 否则若 v37 >= *(uint32_t *)(v36 + 60)
    {
      pObj5 = sub_418DD0(108);  // 调 sub_418DD0
      if ( pObj5 != 0 )  // 若 pObj5 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v11, v38, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      pObj3 = sub_418DD0(130);  // 调 sub_418DD0
      if ( pObj3 != 0 )  // 若 pObj3 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v11 + 24, v39 - 2, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    }
    v25 = ++v37 < 4;
    v38 += 20;
    v39 += 20;
    if ( v25 )  // 若 v25
    {
      v10 = v37;
      v9 = v36;
      continue;
    }
    break;
  }
  v26 = *(uint32_t *)(pArg1 + 44);  // v26 = pArg1+44
  LOBYTE(v4) = *(uint8_t *)(v26 + 17);  // 调 取 16 位值低 8 位
  if ( (uint8_t)v4 != 0 )  // 若 (uint8_t)v4 != 0
  {
    v27 = *(uint32_t *)(v26 + 12);  // v27 = v26+12
    if ( dword_79BE3C == v27 || dword_79BE34 == v27 || (LOBYTE(v4) = dword_79BE38, dword_79BE38 == v27) )  // 调 取 16 位值低 8 位
    {
      v28 = *(uint32_t **)(pArg1 + 44);
      v29 = v28[6];
      v30 = v28[5];
      v31 = v28[7];
      v32 = sub_422E70(1125);  // 调 sub_422E70
      LOBYTE(v4) = sub_4649B0(v30 + (v31 >> 1), v29, -1, -16777216, 2, v32, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
    }
  }
  return v4;
}


// ------------------------------------------------------------
// 0x636500 sub_636500 —— 组队信息页绘制（43C410/69A5F0/69A840，70 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_636500(uint32_t *this)  // 函数: 组队信息页绘制（43C410/69A5F0/69A840，70 行）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e92; // eax
  int v6; // edx

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+36 = 状态字
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e9 = sub_43C410(pMem, *(this + 9), 23, 24, 25, 23, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 10) = fld_e9;  // this+40 = 状态子标志
  sub_69A5F0(fld_e9, 195, 11);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e92 = sub_43C410(pMem2, *(this + 9), 126, 127, 128, 129, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e92 = nullptr;  // fld_e92 = nullptr 空指针
  *(this + 11) = fld_e92;  // this+44 = fld_e92
  sub_69A5F0(fld_e92, 66, 111);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;  // this+60 = 0
  *(this + 16) = 6;  // this+64 = 6
  *(this + 18) = 0;  // this+72 = 0
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 17) = 12;  // this+68 = 12
  *(this + 19) = 1600;  // this+76 = 1600
  *(this + 24) = dword_99FCCC;  // this+96 = dword_99FCCC
  *(this + 13) = -16777216;  // this+52 = bAuraState
  *(this + 32) = 1600;  // this+128 = 1600
  *((uint8_t *)this + 100) = 0;
  *((uint8_t *)this + 101) = 0;
  *((uint8_t *)this + 102) = 0;
  *((uint8_t *)this + 103) = 0;
  *(this + 28) = 0;  // this+112 = pHostComp
  *(this + 29) = 6;  // this+116 = 6
  *(this + 30) = 12;  // this+120 = 动画对象指针
  *(this + 31) = 0;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
  *(this + 33) = 0;  // this+132 = 0
  *(this + 34) = 0;  // this+136 = 0
  *(this + 35) = 0;  // this+140 = 0
  *(this + 36) = 0;  // this+144 = pFrameList144
  *(this + 37) = 0;  // this+148 = 0
  v6 = *this;
  *(this + 37) = dword_99FCCC;  // this+148 = dword_99FCCC
  *(this + 26) = -16777216;  // this+104 = -16777216
  *(this + 32) = 200;  // this+128 = 200
  *(this + 28) = 1;  // this+112 = pHostComp
  *(this + 33) = 1;  // this+132 = 1
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v6 + 24))(this, 17, 10);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 3);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
}



// ------------------------------------------------------------
// 0x6366C0 sub_6366C0 —— 组队创建数据（26 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6366C0(uint32_t *this)  // 函数: 组队创建数据（26 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = bAuraState
  *(this + 14) = 0;  // this+56 = 0
  *(this + 15) = 0;  // this+60 = 0
  *(this + 16) = 0;  // this+64 = 0
  *(this + 17) = 0;  // this+68 = 0
  *(this + 18) = 0;  // this+72 = 0
  *(this + 19) = 0;  // this+76 = 0
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x636700 sub_636700 —— 组队创建数据 2（55 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_636700(uint32_t *this)  // 函数: 组队创建数据 2（55 行）
{
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  uint32_t *pThis_E; // edi
  int i; // ebx
  int (/*thiscall*/ ***fld_e17)(uint32_t, int); // ecx
  uint32_t *pThis_12; // esi
  int j; // edi

  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);  // this+40 = 状态子标志
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    result = (**fld_e10)(fld_e10, 1);
  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;  // this+40 = 状态子标志
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    result = (**fld_e11)(fld_e11, 1);
  fld_e12 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 11) = 0;  // this+44 = 0
  if ( fld_e12 != nullptr )  // 若 fld_e12 非空
    result = (**fld_e12)(fld_e12, 1);
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);  // this+52 = bAuraState
  *(this + 12) = 0;  // this+48 = 0
  if ( fld_e13 != nullptr )  // 若 fld_e13 非空
    result = (**fld_e13)(fld_e13, 1);
  *(this + 13) = 0;  // this+52 = bAuraState
  pThis_E = this + 14;
  for ( i = 3; i != 0; --i )  // 循环：i = 3; i != 0; --i
  {
    if ( *pThis_E != 0 )  // 若 *pThis_E != 0
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_E)(*pThis_E, 1);
    *pThis_E++ = 0;  // *pThis_E++ 写入 0
  }
  fld_e17 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 17);
  if ( fld_e17 != nullptr )  // 若 fld_e17 非空
    result = (**fld_e17)(fld_e17, 1);
  *(this + 17) = 0;  // this+68 = 0
  pThis_12 = this + 18;
  for ( j = 6; j != 0; --j )  // 循环：j = 6; j != 0; --j
  {
    if ( *pThis_12 != 0 )  // 若 *pThis_12 != 0
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_12)(*pThis_12, 1);
    *pThis_12++ = 0;  // *pThis_12++ 写入 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x6367A0 CNRDPartyCreateWindow__vmtC —— CNRDPartyCreateWindow__vmtC 打开槽（69A5F0 + 429830 + 69BCC0/402AE0 + 43B920）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyCreateWindow__vmtC(uint32_t *this, int nArg2, int nArg3)  // 函数: CNRDPartyCreateWindow__vmtC 打开槽（69A5F0 + 429830 + 69BCC0/402AE0 + 43B920）
{
  uint32_t *fld_e2; // edi
  unsigned int v5; // ecx
  unsigned int v6; // eax
  unsigned int v7; // ecx
  int nRand; // [esp+Ch] [ebp-4h]

  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v5 = fld_e2[7];
  v6 = (int)(pt.x - (v5 >> 1)) <= 0 ? 0 : pt.x - (v5 >> 1);
  if ( v6 >= 640 - v5 )  // 若 v6 >= 640 - v5
    v6 = 640 - v5;
  v7 = 480 - fld_e2[8];
  if ( (pt.y - (fld_e2[8] >> 1) <= 0 ? 0 : pt.y - (fld_e2[8] >> 1)) < v7 )  // 若 (pt.y - (fld_e2[8] >> 1) <= 0 ? 0 : pt.y - (fld_e2[8] >> 1)) <..
    v7 = pt.y - (fld_e2[8] >> 1) <= 0 ? 0 : pt.y - (fld_e2[8] >> 1);
  sub_69A5F0(fld_e2, v6, v7);  // 调 sub_69A5F0
  if ( *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) != 0 )  // 调 表按键查找（uint16）
  {
    sub_69BCC0(*(this + 10));  // this+40 = 状态子标志
    *(this + 24) = *(uint32_t *)(*(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) + 60);  // 调 表按键查找（uint16）
  }
  else
  {
    nRand = dword_9B8890[rand() % 6];  // 调 以 16 位种子状态递推并返回 15 位结果
    sub_69BCC0(*(this + 10));  // this+40 = 状态子标志
    sub_402AE0(nRand);  // 调 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
    *(this + 24) = 4;  // this+96 = 4
  }
  sub_43B920(*(uint32_t *)(*(this + 4) + 28), 0);  // 调 输入面板开关
  dword_79BE4C = *(uint32_t *)(*(this + 10) + 12);  // this+40 = 状态子标志
  dword_79BE54 = dword_79BE4C;
  *(uint8_t *)(*(this + 18) + 16) = 0;
  *(uint8_t *)(*(this + 19) + 16) = 0;
  *(uint8_t *)(*(this + 20) + 16) = 0;  // this+80 = nAuraStage
  *(uint8_t *)(*(this + 21) + 16) = 0;  // this+84 = pFxObjA
  *(uint8_t *)(*(this + 22) + 16) = 0;  // this+88 = pFxObjB
  *(uint8_t *)(*(this + 23) + 16) = 0;  // this+92 = pFxObjC
  *(uint8_t *)(*(this + 14) + 16) = 0;
  *(uint8_t *)(*(this + 15) + 16) = 0;
  *(uint8_t *)(*(this + 16) + 16) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x6368F0 CNRDPartyCreateWindow__vmt0 —— CNRDPartyCreateWindow__vmt0 构造（418DD0 + 429830 + 491530/491630，110 行）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyCreateWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDPartyCreateWindow__vmt0 构造（418DD0 + 429830 + 491530/491630，110 行）
{
  int v3; // edi
  int v4; // esi
  int pObj; // eax
  int pObj3; // eax
  int pObj4; // eax
  uint32_t *pThis_E; // eax
  int v9; // edi
  uint32_t *pThis_12; // eax
  int v11; // edi
  int v12; // edi
  int v13; // esi
  int pObj2; // eax
  int v16; // [esp-4h] [ebp-10h]

  IRDPopupWindow__vmt0(pArg2);  // 调 IRDPopupWindow__vmt0 构造
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v3 = *(uint32_t *)(pArg2 + 20);  // v3 = pArg2+20
    v4 = *(uint32_t *)(pArg2 + 24);  // v4 = pArg2+24
    pObj = sub_418DD0(136);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v3 + 8, v4 + 8, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    if ( *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) != 0 )  // 调 表按键查找（uint16）
      pObj3 = sub_418DD0(142);  // 调 sub_418DD0
    else
      pObj3 = sub_418DD0(139);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v3 + 101, v4 + 13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj4 = sub_418DD0(133);  // 调 sub_418DD0
    if ( pObj4 != 0 )  // 若 pObj4 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v3 + 8, v4 + 35, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      v3 + 54,
      v4 + 62,
      -1,
      "%d",
      *(this + 24));
    LOBYTE(pThis_E) = (*(char (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  }
  else
  {
    v9 = 0;
    pThis_12 = this + 18;
    do
    {
      if ( pArg2 == *pThis_12 )  // 若 pArg2 == *pThis_12
      {
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          *(uint32_t *)(pArg2 + 20) + 4,
          *(uint32_t *)(pArg2 + 24) + 4,
          -1,
          dword_9B8890[v9]);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
        LOBYTE(pThis_E) = *(uint8_t *)(pArg2 + 17);  // 调 取 16 位值低 8 位
        if ( (uint8_t)pThis_E == 0 || dword_79BE3C != *(uint32_t *)(pArg2 + 12) )  // 若 (uint8_t)pThis_E == 0 || dword_79BE3C != *(uint32_t *)(pArg2 +..
          return (char)pThis_E;
        sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
        v16 = 137;
        goto LABEL_25;  // 跳转 LABEL_25
      }
      ++v9;  // 自增v9
      ++pThis_12;  // 自增pThis_12
    }
    while ( v9 < 6 );  // 当 v9 < 6 循环
    v11 = 0;
    pThis_E = this + 14;
    while ( pArg2 != *pThis_E )  // 当 pArg2 != *pThis_E 循环
    {
      ++v11;  // 自增v11
      ++pThis_E;  // 自增pThis_E
      if ( v11 >= 3 )  // 若 v11 >= 3
        return (char)pThis_E;
    }
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      *(uint32_t *)(pArg2 + 20) + 12,
      *(uint32_t *)(pArg2 + 24) + 4,
      -1,
      "%d",
      v11 + 2);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    LOBYTE(pThis_E) = *(uint8_t *)(pArg2 + 17);  // 调 取 16 位值低 8 位
    if ( (uint8_t)pThis_E != 0 && dword_79BE3C == *(uint32_t *)(pArg2 + 12) )  // 若 (uint8_t)pThis_E != 0 && dword_79BE3C == *(uint32_t *)(pArg2 +..
    {
      sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      v16 = 138;
LABEL_25:
      v12 = *(uint32_t *)(pArg2 + 24);  // v12 = pArg2+24
      v13 = *(uint32_t *)(pArg2 + 20);  // v13 = pArg2+20
      pObj2 = sub_418DD0(v16);  // 调 sub_418DD0
      if ( pObj2 != 0 )  // 若 pObj2 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v13, v12, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      LOBYTE(pThis_E) = sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
    }
  }
  return (char)pThis_E;
}



// ------------------------------------------------------------
// 0x636B30 CNRDPartyCreateWindow__vmt8 —— CNRDPartyCreateWindow__vmt8 Update（242 行：545510 队名输入 + 522500/540870 + 69AC60/69AC70/464740/40BE20 创建提交 + 48B740/48B7C0）
// ------------------------------------------------------------
int /*thiscall*/ sub_636B30(char *this)  // 【CNRDPartyCreateWindow__vmt8】
{
  int result; // eax
  DWORD pThis_A2; // ecx
  int pThis_2; // eax
  int pThis_22; // eax
  int v6; // edi
  int v7; // ebx
  int pThis_A; // eax
  int pThis_B; // eax
  int v10; // eax
  const char *pThis_A3; // ebx
  uint32_t *v12; // edi
  int v13; // edx
  int nCmp; // eax
  int v15; // eax
  uint32_t *v16; // ebx
  int pThis_18; // edi
  uint32_t *v18; // ecx
  int v19; // eax
  const char *psz; // edx
  uint32_t *pThis_4; // edi
  int v22; // eax
  int pThis_B2; // eax
  int dword_79BE342; // ebx
  int pThis_C; // eax
  int pThis_D; // eax
  bool pThis_E; // zf
  int v28; // eax
  char *pThis_38; // ecx
  int pThis_11; // eax
  bool pThis_12; // al
  int v32; // eax
  char *pThis_48; // ecx
  int pThis_A4; // edi
  const char *v35; // ebx
  uint32_t *v36; // [esp+8h] [ebp-10h]
  int pThis_182; // [esp+8h] [ebp-10h]
  int v38; // [esp+Ch] [ebp-Ch]
  char *Str; // [esp+10h] [ebp-8h]
  char v40[4]; // [esp+14h] [ebp-4h] BYREF

  if ( (uint8_t)sub_545510(3) == 0 )  // 调 输入框取值（25 行——社区/摆摊/组队窗口共用的文本框读取）
    return (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  sub_69A650(*((uint32_t *)this + 2));  // this+8 = 技能槽记录首字
  pThis_2 = *((uint32_t *)this + 2);  // this+8 = 技能槽记录首字
  if ( *(uint8_t *)(pThis_2 + 17) != 0 )  // 若 *(uint8_t *)(pThis_2 + 17) != 0
  {
    pThis_A2 = dword_79BE34;
    if ( dword_79BE34 == *(uint32_t *)(pThis_2 + 12) )  // 若 dword_79BE34 == *(uint32_t *)(pThis_2 + 12)
    {
      dword_79BE4C = *(uint32_t *)(*((uint32_t *)this + 10) + 12);  // this+40 = 状态子标志
      dword_79BE54 = dword_79BE4C;
      pThis_22 = *((uint32_t *)this + 2);  // this+8 = 技能槽记录首字
      v6 = *(uint32_t *)(pThis_22 + 20);  // v6 = pThis_22+20
      v7 = *(uint32_t *)(pThis_22 + 24);  // v7 = pThis_22+24
      if ( pt.x >= v6 + 43
        && pt.x < v6 + 219
        && pt.y >= v7 + 36
        && pt.y < v7 + 52
        && sub_522500(*((uint32_t *)this + 10)) != 0 )  // this+40 = 状态子标志
      {
        sub_540870(szPassword);  // 调 数量窗口打开（69BCC0/402AE0 控件显示）
      }
      if ( (uint8_t)sub_69AC60(*((uint32_t *)this + 10)) != 0 )  // this+40 = 状态子标志
      {
        pThis_A = sub_69AC70(*((uint32_t *)this + 10));  // this+40 = 状态子标志
        sub_464740(v6 + 15, v7 - 150, pThis_A + 10, 11, 0, 0);  // 调 九宫格面板框绘制
      }
    }
  }
  pThis_B = *((uint32_t *)this + 11);
  if ( *(uint8_t *)(pThis_B + 17) != 0 && (pThis_A2 = dword_79BE34, dword_79BE34 == *(uint32_t *)(pThis_B + 12))  // 若 *(uint8_t *)(pThis_B + 17) != 0 && (pThis_A2 = dword_79BE34, d..
    || (v10 = *((uint32_t *)this + 10), LOBYTE(pThis_A2) = *(uint8_t *)(v10 + 116), *(uint8_t *)(v10 + 116) = 0, (uint8_t)pThis_A2 != 0) )  // this+40 = 状态子标志
  {
    sub_40BE20(pThis_A2, "\n CNRDPartyCreateWindow Enter");  // 日志/输出串: CNRDPartyCreateWindow Enter
    pThis_A3 = (const char *)sub_69B740(*((uint32_t *)this + 10));  // this+40 = 状态子标志
    Str = (char *)pThis_A3;
    v38 = 0;
    v12 = *(uint32_t **)(sub_429830((uint16_t)word_77F804) + 184);  // 调 表按键查找（uint16）
    v36 = v12;
    if ( v12 != nullptr && strlen(pThis_A3) == 0 )  // 调 返回字符串长度（逐字节扫描）
    {
      pThis_A3 = (const char *)sub_6307E0(v12);  // 调 组队创建提交辅助（17 行）
      Str = (char *)pThis_A3;
    }
    v13 = 0;
    while ( 1 )  // 无限循环
    {
      nCmp = strcmp(pThis_A3, (const char *)dword_9B8890[v13++]);  // 调 串比较
      if ( nCmp == 0 )  // 若 nCmp == 0
        break;
      if ( v13 >= 6 )  // 若 v13 >= 6
        goto LABEL_25;  // 跳转 LABEL_25
      pThis_A3 = Str;
    }
    v38 = v13;
LABEL_25:
    if ( strlen(Str) == 0 )  // 调 返回字符串长度（逐字节扫描）
    {
      v15 = sub_422E70(1121);  // 调 sub_422E70
LABEL_27:
      sub_44E8D0(*((char **)this + 4), (void *)0x1B, v15, 0);  // 调 对象池借出（按池号取可用对象）
      goto LABEL_47;  // 跳转 LABEL_47
    }
    if ( strstr(Str, "%") != nullptr )  // 调 查子串
    {
      v15 = sub_422E70(1122);  // 调 sub_422E70
      goto LABEL_27;  // 跳转 LABEL_27
    }
    v16 = v36;
    if ( v36 != nullptr )  // 若 v36 非空
    {
      pThis_18 = *((uint32_t *)this + 24);
      v18 = v36;
      pThis_182 = pThis_18;
      if ( pThis_18 < sub_56A720(v18) )  // 调 组队列表联动（55 行）
      {
        v15 = sub_422E70(1123);  // 调 sub_422E70
        goto LABEL_27;  // 跳转 LABEL_27
      }
      v19 = v16[2];
      if ( v19 != 0 )  // 若 v19 != 0
      {
        psz = (const char *)dword_9B8890[(v19 - 1) % 6];
      }
      else if ( v16[9] < 0x10u )  // 否则若 v16[9] < 0x10u
      {
        psz = (const char *)(v16 + 4);
      }
      else
      {
        psz = (const char *)v16[4];
      }
      if ( strcmp(psz, Str) == 0 && v16[15] == pThis_182 )  // 调 串比较
      {
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
        goto LABEL_47;  // 跳转 LABEL_47
      }
    }
    sub_423200(dword_8F7B08, 12);  // 【发送网络包API】
    v40[0] = v38;
    sub_423290(v40, 1);  // 调 sub_423290
    if ( v38 == 0 )  // 若 v38 == 0
      sub_41C100(Str);  // 调 写字符串到发送缓冲（4B 长度 + 内容）
    v40[0] = *(this + 96);  // this+384 = 动画件名 SSO 容量判据
    sub_423290(v40, 1);  // 调 sub_423290
    sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    if ( v16 == nullptr && sub_48B740((const CHAR *)dword_8F8544, 3) == 1 )  // 调 调试配置项读取并夹取上下限
    {
      pThis_4 = *(uint32_t **)(*((uint32_t *)this + 4) + 28);
      v22 = sub_422E70(1124);  // 调 sub_422E70
      sub_43BEE0(pThis_4, v22, -6567706, 0, -1);  // 调 sub_43BEE0
      sub_48B7C0((const CHAR *)dword_8F8544, 3, 0);  // 调 调试配置项写入并刷新（·sub_48B830 联动）
    }
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  }
LABEL_47:
  pThis_B2 = *((uint32_t *)this + 11);
  dword_79BE342 = dword_79BE34;
  if ( *(uint8_t *)(pThis_B2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_B2 + 12) )  // 若 *(uint8_t *)(pThis_B2 + 17) != 0 && dword_79BE34 == *(uint32_t..
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    dword_79BE342 = dword_79BE34;
  }
  pThis_C = *((uint32_t *)this + 12);
  if ( *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE342 == *(uint32_t *)(pThis_C + 12) )  // 若 *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE342 == *(uint32_t..
  {
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    dword_79BE342 = dword_79BE34;
  }
  pThis_D = *((uint32_t *)this + 13);  // this+52 = bAuraState
  if ( *(uint8_t *)(pThis_D + 17) != 0 && dword_79BE342 == *(uint32_t *)(pThis_D + 12) )  // 若 *(uint8_t *)(pThis_D + 17) != 0 && dword_79BE342 == *(uint32_t..
  {
    pThis_E = *(uint8_t *)(*((uint32_t *)this + 14) + 16) == 0;
    *(uint8_t *)(*((uint32_t *)this + 14) + 16) = pThis_E;
    *(uint8_t *)(*((uint32_t *)this + 15) + 16) = pThis_E;
    *(uint8_t *)(*((uint32_t *)this + 16) + 16) = pThis_E;
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    dword_79BE342 = dword_79BE34;
  }
  v28 = 0;
  pThis_38 = this + 56;
  while ( *(uint8_t *)(*(uint32_t *)pThis_38 + 17) == 0 || dword_79BE342 != *(uint32_t *)(*(uint32_t *)pThis_38 + 12) )  // 当 *(uint8_t *)(*(uint32_t *)pThis_38 + 17) == 0 || dword_79BE342.. 循环
  {
    ++v28;  // 自增v28
    pThis_38 += 4;
    if ( v28 >= 3 )  // 若 v28 >= 3
      goto LABEL_62;  // 跳转 LABEL_62
  }
  *((uint32_t *)this + 24) = v28 + 2;  // this+96 = v28 + 2
  *(uint8_t *)(*((uint32_t *)this + 14) + 16) = 0;
  *(uint8_t *)(*((uint32_t *)this + 15) + 16) = 0;
  *(uint8_t *)(*((uint32_t *)this + 16) + 16) = 0;
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  dword_79BE342 = dword_79BE34;
LABEL_62:
  pThis_11 = *((uint32_t *)this + 17);
  if ( *(uint8_t *)(pThis_11 + 17) != 0 && dword_79BE342 == *(uint32_t *)(pThis_11 + 12) )  // 若 *(uint8_t *)(pThis_11 + 17) != 0 && dword_79BE342 == *(uint32_..
  {
    pThis_12 = *(uint8_t *)(*((uint32_t *)this + 18) + 16) == 0;
    *(uint8_t *)(*((uint32_t *)this + 18) + 16) = pThis_12;
    *(uint8_t *)(*((uint32_t *)this + 19) + 16) = pThis_12;
    *(uint8_t *)(*((uint32_t *)this + 20) + 16) = pThis_12;  // this+80 = nAuraStage
    *(uint8_t *)(*((uint32_t *)this + 21) + 16) = pThis_12;  // this+84 = pFxObjA
    *(uint8_t *)(*((uint32_t *)this + 22) + 16) = pThis_12;  // this+88 = pFxObjB
    *(uint8_t *)(*((uint32_t *)this + 23) + 16) = pThis_12;  // this+92 = pFxObjC
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    dword_79BE342 = dword_79BE34;
  }
  v32 = 0;
  pThis_48 = this + 72;
  while ( *(uint8_t *)(*(uint32_t *)pThis_48 + 17) == 0 || dword_79BE342 != *(uint32_t *)(*(uint32_t *)pThis_48 + 12) )  // 当 *(uint8_t *)(*(uint32_t *)pThis_48 + 17) == 0 || dword_79BE342.. 循环
  {
    ++v32;  // 自增v32
    pThis_48 += 4;
    if ( v32 >= 6 )  // 若 v32 >= 6
      goto LABEL_71;  // 跳转 LABEL_71
  }
  pThis_A4 = *((uint32_t *)this + 10);  // this+40 = 状态子标志
  v35 = (const char *)dword_9B8890[v32];
  sub_69BCC0(pThis_A4);  // 调 sub_69BCC0
  sub_402AE0(pThis_A4 + 180, v35);  // 调 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
  *(uint8_t *)(*((uint32_t *)this + 18) + 16) = 0;
  *(uint8_t *)(*((uint32_t *)this + 19) + 16) = 0;
  *(uint8_t *)(*((uint32_t *)this + 20) + 16) = 0;  // this+80 = nAuraStage
  *(uint8_t *)(*((uint32_t *)this + 21) + 16) = 0;  // this+84 = pFxObjA
  *(uint8_t *)(*((uint32_t *)this + 22) + 16) = 0;  // this+88 = pFxObjB
  *(uint8_t *)(*((uint32_t *)this + 23) + 16) = 0;  // this+92 = pFxObjC
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
LABEL_71:
  sub_4BF300(dword_8F8558, 0, 0);  // 调 槽写侧（+64 + 索引）
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
int /*thiscall*/ sub_637070(int *this)  // 函数: 组队创建页绘制（133 行：43C060/69A5F0/69A840/43C410 + 426BD0/69C6B0/69C6…
{
  void *pMem; // eax
  int v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_e92; // eax
  uint32_t *pMem4; // eax
  uint32_t *fld_e93; // eax
  int *pThis_E; // ebx
  uint32_t *pMem5; // edi
  uint8_t *pMem6; // eax
  uint32_t *pMem62; // edi
  int fld_e94; // ebx
  uint32_t *pMem622; // ecx
  int *pThis_12; // ebx
  uint8_t *pMem7; // eax
  uint32_t *pMem72; // edi
  void *Block; // [esp+10h] [ebp-14h]
  void *Blocka; // [esp+10h] [ebp-14h]
  int v22; // [esp+14h] [ebp-10h]
  int v23; // [esp+14h] [ebp-10h]

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+36 = 状态字
  pMem = operator new(0xE4u);  // operator new 分配 228 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C060((int)pMem, 31, 180);  // 调 nengine::CNEdit 构造
  else
    v3 = 0;
  *(this + 10) = v3;  // this+40 = 状态子标志
  dword_9D3BD8 = dword_99FCCC;
  sub_69A5F0((uint32_t *)*(this + 10), 46, 39);  // this+40 = 状态子标志
  sub_69A840((uint32_t *)*(this + 2), *(this + 10));  // this+8 = 技能槽记录首字
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e9 = sub_43C410(pMem2, *(this + 9), 65, 66, 67, 65, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 11) = (int)fld_e9;  // this+44 = (int)fld_e9
  sub_69A5F0(fld_e9, 95, 84);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 11));  // this+8 = 技能槽记录首字
  pMem3 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    fld_e92 = sub_43C410(pMem3, *(this + 9), 23, 24, 25, 23, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e92 = nullptr;  // fld_e92 = nullptr 空指针
  *(this + 12) = (int)fld_e92;  // this+48 = (int)fld_e92
  sub_69A5F0(fld_e92, 219, 11);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 12));  // this+8 = 技能槽记录首字
  pMem4 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    fld_e93 = sub_43C410(pMem4, *(this + 9), 91, 92, 93, 91, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e93 = nullptr;  // fld_e93 = nullptr 空指针
  *(this + 13) = (int)fld_e93;  // this+52 = bAuraState
  sub_69A5F0(fld_e93, 71, 60);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 13));  // this+8 = 技能槽记录首字
  v22 = 75;
  pThis_E = this + 14;
  do
  {
    pMem5 = operator new(0x6Cu);  // operator new 分配 108 字节
    if ( pMem5 != nullptr )  // 若 pMem5 非空
    {
      Block = (void *)*(this + 9);  // this+36 = 状态字
      sub_426BD0(pMem5);  // 调 nengine::IControl 构造
      *pMem5 = &nengine::CNFrame::`vftable';  // vftable 复位
      sub_69C6B0(v11);  // 调 sub_69C6B0
      sub_69C6C0((int)v11, (int)Block, 135);  // 调 sub_69C6C0
    }
    else
    {
      v11 = nullptr;  // v11 = nullptr 空指针
    }
    *v10 = (int)v11;  // *v10 写入 (int)v11
    v11[17] = this;
    sub_69A5F0((uint32_t *)*v10, 42, v22);  // 调 sub_69A5F0
    sub_69A840((uint32_t *)*(this + 2), *v10++);  // this+8 = 技能槽记录首字
    v22 += 18;
  }
  while ( v22 < 129 );  // 当 v22 < 129 循环
  v12 = operator new(0x84u);  // operator new 分配 132 字节
  v13 = v12;
  if ( v12 != nullptr )  // 若 v12 非空
  {
    v14 = *(this + 9);  // this+36 = 状态字
    sub_426BD0(v12);  // 调 nengine::IControl 构造
    *v13 = &nengine::CNButton::`vftable';  // vftable 复位
    sub_69C780((int)pMem62);  // 调 sub_69C780
    sub_69C7B0((int)pMem62, fld_e94, 91, 92, 93, 91, 0, 0);  // 调 sub_69C7B0
    pMem622 = pMem62;
  }
  else
  {
    pMem622 = nullptr;  // pMem622 = nullptr 空指针
  }
  *(this + 17) = (int)pMem622;  // this+68 = (int)pMem622
  sub_69A5F0(pMem622, 221, 37);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 17));  // this+8 = 技能槽记录首字
  v23 = 52;
  pThis_12 = this + 18;
  do
  {
    pMem7 = operator new(0x6Cu);  // operator new 分配 108 字节
    pMem72 = pMem7;
    if ( pMem7 != nullptr )  // 若 pMem7 非空
    {
      Blocka = (void *)*(this + 9);  // this+36 = 状态字
      sub_426BD0(pMem7);  // 调 nengine::IControl 构造
      *pMem72 = &nengine::CNFrame::`vftable';  // vftable 复位
      sub_69C6B0(pMem72);  // 调 sub_69C6B0
      sub_69C6C0((int)pMem72, (int)Blocka, 134);  // 调 sub_69C6C0
    }
    else
    {
      pMem72 = nullptr;  // pMem72 = nullptr 空指针
    }
    *pThis_12 = (int)pMem72;  // *pThis_12 写入 (int)pMem72
    pMem72[17] = this;
    sub_69A5F0((uint32_t *)*pThis_12, 42, v23);  // 调 sub_69A5F0
    sub_69A840((uint32_t *)*(this + 2), *pThis_12++);  // this+8 = 技能槽记录首字
    v23 += 18;
  }
  while ( v23 < 160 );  // 当 v23 < 160 循环
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 19, 8);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 28))(this, 3);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
}


// ------------------------------------------------------------
// 0x6373B0 CNRDPartyLeaveSuggestWindow__vmt8 —— CNRDPartyLeaveSuggestWindow__vmt8 确认退队（456390 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDPartyLeaveSuggestWindow__vmt8(uint32_t *this)
{
  int fld_e9; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  if ( sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) == 0  // 调 表按键查找（uint16）
    || *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) == 0  // 调 表按键查找（uint16）
    || sub_456390((char *)dword_8F850C, 0) != 1 )
  {
    return (uint8_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  }
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = (uint8_t *)*(this + 10);  // this+40 = 状态子标志
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    sub_423200(dword_8F7B08, 13);  // 【发送网络包API】
    sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x637490 CNRDPartyLeaveSuggestWindow__vmtC —— CNRDPartyLeaveSuggestWindow__vmtC 文案装配（429830 + 422E70 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPartyLeaveSuggestWindow__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDPartyLeaveSuggestWindow__vmtC 文案装配（429830 + 422E70 + 69C340 系）
{
  int v4; // eax
  unsigned int v5; // ecx
  int v6; // eax
  int v7; // eax
  char *v8; // eax
  int v9; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
  int v12; // ebx
  int v13; // edi
  int v15; // [esp-4h] [ebp-94h]
  char Buffer[128]; // [esp+Ch] [ebp-84h] BYREF
  int dword_796E502; // [esp+8Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  v4 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // 调 表按键查找（uint16）
  v5 = *(uint32_t *)(v4 + 40);  // v5 = v4+40
  v6 = v4 + 16;
  if ( v5 < 0x10 )  // 若 v5 < 0x10
    v7 = v6 + 4;
  else
    v7 = *(uint32_t *)(v6 + 4);  // v7 = v6+4
  v15 = v7;
  v8 = sub_422E70(1126);  // 调 sub_422E70
  sprintf(Buffer, v8, v15);  // 调 格式化到缓冲
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(Buffer, 0);  // 调 sub_69C360
  v9 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(int *, int, int))(v9 + 24))(this, 14, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v12 = (480 - fld_e2[8]) / 2;
  v13 = (640 - fld_e2[7]) / 2;
  sub_69A5F0(fld_e2, v13, v12);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v13 + 29, *(uint32_t *)(*(this + 2) + 32) + v12 - 43);  // this+36 = 状态字
  sub_69A5F0((uint32_t *)*(this + 10), v13 + 98, *(uint32_t *)(*(this + 2) + 32) + v12 - 43);  // this+40 = 状态子标志
  return 1;
}



// ------------------------------------------------------------
// 0x6375A0 sub_6375A0 —— 退队清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_6375A0(uint32_t *this)  // 函数: 退队清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 21, 22, 23, 21, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 24, 25, 26, 24, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ============================================================
// 【分区 18】好友/队员增删窗族（0x637680-0x6381B0）
// CNRDFriendAddRemoveWindow / CNRDMemberAddRemoveWindow /
// CNRDFriendRemoveConfirmWindow：vmt8 Update（545510 名字输入 + 提交）。
// ============================================================
// ------------------------------------------------------------
// 0x637680 sub_637680 —— 好友添加数据（27 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_637680(uint32_t *this)  // 函数: 好友添加数据（27 行）
{
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx

  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);  // this+40 = 状态子标志
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    result = (**fld_e10)(fld_e10, 1);
  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;  // this+40 = 状态子标志
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    result = (**fld_e11)(fld_e11, 1);
  fld_e12 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 11) = 0;  // this+44 = 0
  if ( fld_e12 != nullptr )  // 若 fld_e12 非空
    result = (**fld_e12)(fld_e12, 1);
  *(this + 12) = 0;  // this+48 = 0
  return result;
}



// ------------------------------------------------------------
// 0x6376C0 CNRDFriendAddRemoveWindow__vmt8 —— CNRDFriendAddRemoveWindow__vmt8 提交（545510 名字输入 + 69AC60/69AC70/464740 + 44E8D0 + CLICK_BUTTON2）
// ------------------------------------------------------------
int /*thiscall*/ CNRDFriendAddRemoveWindow__vmt8(void *this)  // 函数: CNRDFriendAddRemoveWindow__vmt8 提交（545510 名字输入 + 69AC60/69AC70/464740 + 44E8D0 + CLICK_BUTTON2）
{
  int result; // eax
  int pThis_2; // eax
  int pThis_22; // eax
  int v5; // edi
  int v6; // ebx
  int pThis_A; // eax
  int pThis_C; // eax
  int pThis_A2; // eax
  char v10; // cl
  char *v11; // eax
  int pThis_A3; // ecx
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int pThis_C2; // eax
  int pThis_B; // eax

  if ( (uint8_t)sub_545510(4) == 0 )  // 调 输入框取值（25 行——社区/摆摊/组队窗口共用的文本框读取）
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  sub_69A650(*((uint32_t *)this + 2));  // this+8 = 技能槽记录首字
  pThis_2 = *((uint32_t *)this + 2);  // this+8 = 技能槽记录首字
  if ( *(uint8_t *)(pThis_2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_2 + 12) )  // 若 *(uint8_t *)(pThis_2 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    dword_79BE4C = *(uint32_t *)(*((uint32_t *)this + 10) + 12);  // this+40 = 状态子标志
    dword_79BE54 = dword_79BE4C;
    pThis_22 = *((uint32_t *)this + 2);  // this+8 = 技能槽记录首字
    v5 = *(uint32_t *)(pThis_22 + 20);  // v5 = pThis_22+20
    v6 = *(uint32_t *)(pThis_22 + 24);  // v6 = pThis_22+24
    if ( (uint8_t)sub_69AC60(*((uint32_t *)this + 10)) != 0 )  // this+40 = 状态子标志
    {
      pThis_A = sub_69AC70(*((uint32_t *)this + 10));  // this+40 = 状态子标志
      sub_464740(v5 + 15, v6 - 150, pThis_A + 10, 11, 0, 0);  // 调 九宫格面板框绘制
    }
  }
  pThis_C = *((uint32_t *)this + 12);
  if ( *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_C + 12)  // 若 *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE34 == *(uint32_t ..
    || (pThis_A2 = *((uint32_t *)this + 10), v10 = *(uint8_t *)(pThis_A2 + 116), *(uint8_t *)(pThis_A2 + 116) = 0, v10 != 0) )  // this+40 = 状态子标志
  {
    if ( strlen((const char *)sub_69B740(*((uint32_t *)this + 10))) != 0 )  // 调 返回字符串长度（逐字节扫描）
    {
      pThis_A3 = *((uint32_t *)this + 10);  // this+40 = 状态子标志
      if ( *((uint32_t *)this + 13) != 0 )  // this+52 = bAuraState
      {
        v15 = sub_69B740(pThis_A3);  // 调 sub_69B740
        sub_44E8D0(*((char **)this + 4), (void *)0x2D, v15, 0);  // 调 对象池借出（按池号取可用对象）
      }
      else
      {
        v13 = *(uint32_t *)dword_8F8510;
        v14 = sub_69B740(pThis_A3);  // 调 sub_69B740
        (*(void (/*thiscall*/ **)(int, int))(v13 + 4))(dword_8F8510, v14);  // 调用虚函数（虚表槽 +4）
      }
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
    else
    {
      v11 = sub_422E70(936);  // 调 sub_422E70
      sub_44E8D0(*((char **)this + 4), (void *)0x1B, (int)v11, 0);  // 调 对象池借出（按池号取可用对象）
    }
  }
  pThis_C2 = *((uint32_t *)this + 12);
  if ( *(uint8_t *)(pThis_C2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_C2 + 12) )  // 若 *(uint8_t *)(pThis_C2 + 17) != 0 && dword_79BE34 == *(uint32_t..
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  pThis_B = *((uint32_t *)this + 11);
  if ( *(uint8_t *)(pThis_B + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_B + 12) )  // 若 *(uint8_t *)(pThis_B + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  CNCommandChecker__vmt40(0, 0);
  result = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)this + 4) + 28) + 136);
  *(uint8_t *)(result + 17) = 0;  // result+17 = 0
  return result;
}



// ------------------------------------------------------------
// 0x637870 CNRDFriendAddRemoveWindow__vmt0 —— CNRDFriendAddRemoveWindow__vmt0 构造（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDFriendAddRemoveWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDFriendAddRemoveWindow__vmt0 构造（418DD0）
{
  int result; // eax
  int v4; // ebx
  int v5; // edi
  int pObj; // eax
  int fld_e13; // eax

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
    pObj = sub_418DD0(156);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v4 + 8, v5 + 8, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    fld_e13 = sub_418DD0(153 - (*(this + 13) != 0));  // this+52 = bAuraState
    if ( fld_e13 != 0 )  // 若 fld_e13 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e13 + 152))(fld_e13, v4 + 64, v5 + 13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    result = sub_418DD0(157);  // 调 sub_418DD0
    if ( result != 0 )  // 若 result != 0
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
               result,
               v4 + 8,
               v5 + 36,
               dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
  }
  return result;
}



// ------------------------------------------------------------
// 0x637920 sub_637920 —— 好友窗页绘制（43C060/69A5F0/69A840/43C410，44 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_637920(int *this)  // 函数: 好友窗页绘制（43C060/69A5F0/69A840/43C410，44 行）
{
  void *pMem; // eax
  int v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_e92; // eax

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+36 = 状态字
  pMem = operator new(0xE4u);  // operator new 分配 228 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C060((int)pMem, 12, 112);  // 调 nengine::CNEdit 构造
  else
    v3 = 0;
  *(this + 10) = v3;  // this+40 = 状态子标志
  dword_9D3BD8 = dword_99FCCC;
  sub_69A5F0((uint32_t *)*(this + 10), 49, 40);  // this+40 = 状态子标志
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e9 = sub_43C410(pMem2, *(this + 9), 23, 24, 25, 23, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 11) = (int)fld_e9;  // this+44 = (int)fld_e9
  sub_69A5F0(fld_e9, 147, 11);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  pMem3 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    fld_e92 = sub_43C410(pMem3, *(this + 9), 65, 66, 67, 65, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e92 = nullptr;  // fld_e92 = nullptr 空指针
  *(this + 12) = (int)fld_e92;  // this+48 = (int)fld_e92
  sub_69A5F0(fld_e92, 59, 60);  // 调 sub_69A5F0
  sub_69A840(*(this + 12));  // 调 sub_69A840
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 13, 6);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 28))(this, 3);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
}



// ------------------------------------------------------------
// 0x637A80 sub_637A80 —— 好友/成员窗数据（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_637A80(uint32_t *this)  // 函数: 好友/成员窗数据（15 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = bAuraState
  return 0;
}



// ------------------------------------------------------------
// 0x637AA0 CNRDMemberAddRemoveWindow__vmt8 —— CNRDMemberAddRemoveWindow__vmt8 提交（545510 名字输入 + 69B740 + 44E8D0 + CLICK_BUTTON2）
// ------------------------------------------------------------
int /*thiscall*/ CNRDMemberAddRemoveWindow__vmt8(void *this)  // 函数: CNRDMemberAddRemoveWindow__vmt8 提交（545510 名字输入 + 69B740 + 44E8D0 + CLICK_BUTTON2）
{
  int result; // eax
  int pThis_2; // eax
  int pThis_C; // eax
  int pThis_A; // eax
  char v6; // cl
  char *v7; // eax
  int v8; // edi
  int pThis_A3; // eax
  int pThis_A2; // eax
  int pThis_C2; // eax
  int pThis_B; // eax

  if ( (uint8_t)sub_545510(4) == 0 )  // 调 输入框取值（25 行——社区/摆摊/组队窗口共用的文本框读取）
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  sub_69A650(*((uint32_t *)this + 2));  // this+8 = 技能槽记录首字
  pThis_2 = *((uint32_t *)this + 2);  // this+8 = 技能槽记录首字
  if ( *(uint8_t *)(pThis_2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_2 + 12) )  // 若 *(uint8_t *)(pThis_2 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    dword_79BE4C = *(uint32_t *)(*((uint32_t *)this + 10) + 12);  // this+40 = 状态子标志
    dword_79BE54 = dword_79BE4C;
  }
  pThis_C = *((uint32_t *)this + 12);
  if ( *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_C + 12)  // 若 *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE34 == *(uint32_t ..
    || (pThis_A = *((uint32_t *)this + 10), v6 = *(uint8_t *)(pThis_A + 116), *(uint8_t *)(pThis_A + 116) = 0, v6 != 0) )  // this+40 = 状态子标志
  {
    if ( strlen((const char *)sub_69B740(*((uint32_t *)this + 10))) != 0 )  // 调 返回字符串长度（逐字节扫描）
    {
      if ( *((uint32_t *)this + 13) != 0 )  // this+52 = bAuraState
      {
        pThis_A2 = sub_69B740(*((uint32_t *)this + 10));  // this+40 = 状态子标志
        sub_44E8D0(*((char **)this + 4), (void *)0x38, pThis_A2, 0);  // 调 对象池借出（按池号取可用对象）
      }
      else
      {
        v8 = *(uint32_t *)dword_8F8518;
        pThis_A3 = sub_69B740(*((uint32_t *)this + 10));  // this+40 = 状态子标志
        (*(void (/*thiscall*/ **)(int, int))(v8 + 4))(dword_8F8518, pThis_A3);  // 调用虚函数（虚表槽 +4）
      }
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
    else
    {
      v7 = sub_422E70(1120);  // 调 sub_422E70
      sub_44E8D0(*((char **)this + 4), (void *)0x1B, (int)v7, 0);  // 调 对象池借出（按池号取可用对象）
    }
  }
  pThis_C2 = *((uint32_t *)this + 12);
  if ( *(uint8_t *)(pThis_C2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_C2 + 12) )  // 若 *(uint8_t *)(pThis_C2 + 17) != 0 && dword_79BE34 == *(uint32_t..
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  pThis_B = *((uint32_t *)this + 11);
  if ( *(uint8_t *)(pThis_B + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_B + 12) )  // 若 *(uint8_t *)(pThis_B + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  CNCommandChecker__vmt40(0, 0);
  result = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)this + 4) + 28) + 136);
  *(uint8_t *)(result + 17) = 0;  // result+17 = 0
  return result;
}



// ------------------------------------------------------------
// 0x637C10 CNRDFriendAddRemoveWindow__vmtC —— CNRDFriendAddRemoveWindow__vmtC 打开槽（69A5F0 + 43B920 + 69BCC0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDFriendAddRemoveWindow__vmtC(uint32_t *this, int nArg2, int nArg3)  // 函数: CNRDFriendAddRemoveWindow__vmtC 打开槽（69A5F0 + 43B920 + 69BCC0）
{
  uint32_t *fld_e2; // edi
  unsigned int v5; // ecx
  unsigned int v6; // eax
  unsigned int v7; // ecx

  *(this + 13) = nArg3;  // this+52 = bAuraState
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v5 = fld_e2[7];
  v6 = (int)(pt.x - (v5 >> 1)) <= 0 ? 0 : pt.x - (v5 >> 1);
  if ( v6 >= 640 - v5 )  // 若 v6 >= 640 - v5
    v6 = 640 - v5;
  v7 = 480 - fld_e2[8];
  if ( (pt.y - (fld_e2[8] >> 1) <= 0 ? 0 : pt.y - (fld_e2[8] >> 1)) < v7 )  // 若 (pt.y - (fld_e2[8] >> 1) <= 0 ? 0 : pt.y - (fld_e2[8] >> 1)) <..
    v7 = pt.y - (fld_e2[8] >> 1) <= 0 ? 0 : pt.y - (fld_e2[8] >> 1);
  sub_69A5F0(fld_e2, v6, v7);  // 调 sub_69A5F0
  sub_43B920(*(uint32_t *)(*(this + 4) + 28), 0);  // 调 输入面板开关
  sub_69BCC0(*(this + 10));  // this+40 = 状态子标志
  dword_79BE4C = *(uint32_t *)(*(this + 10) + 12);  // this+40 = 状态子标志
  dword_79BE54 = dword_79BE4C;
  return 1;
}



// ------------------------------------------------------------
// 0x637CB0 CNRDMemberAddRemoveWindow__vmt0 —— CNRDMemberAddRemoveWindow__vmt0 构造（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDMemberAddRemoveWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDMemberAddRemoveWindow__vmt0 构造（418DD0）
{
  int result; // eax
  int v4; // ebx
  int v5; // edi
  int pObj; // eax
  int fld_e13; // eax

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
    pObj = sub_418DD0(156);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v4 + 8, v5 + 8, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    fld_e13 = sub_418DD0(175 - (*(this + 13) != 0));  // this+52 = bAuraState
    if ( fld_e13 != 0 )  // 若 fld_e13 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e13 + 152))(fld_e13, v4 + 64, v5 + 13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    result = sub_418DD0(157);  // 调 sub_418DD0
    if ( result != 0 )  // 若 result != 0
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
               result,
               v4 + 8,
               v5 + 36,
               dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
  }
  return result;
}



// ------------------------------------------------------------
// 0x637D60 sub_637D60 —— 成员窗页绘制（43C060/69A5F0/69A840/43C410，44 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_637D60(int *this)  // 函数: 成员窗页绘制（43C060/69A5F0/69A840/43C410，44 行）
{
  void *pMem; // eax
  int v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_e92; // eax

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+36 = 状态字
  pMem = operator new(0xE4u);  // operator new 分配 228 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C060((int)pMem, 12, 112);  // 调 nengine::CNEdit 构造
  else
    v3 = 0;
  *(this + 10) = v3;  // this+40 = 状态子标志
  dword_9D3BD8 = dword_99FCCC;
  sub_69A5F0((uint32_t *)*(this + 10), 49, 40);  // this+40 = 状态子标志
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e9 = sub_43C410(pMem2, *(this + 9), 23, 24, 25, 23, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 11) = (int)fld_e9;  // this+44 = (int)fld_e9
  sub_69A5F0(fld_e9, 147, 11);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  pMem3 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    fld_e92 = sub_43C410(pMem3, *(this + 9), 65, 66, 67, 65, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e92 = nullptr;  // fld_e92 = nullptr 空指针
  *(this + 12) = (int)fld_e92;  // this+48 = (int)fld_e92
  sub_69A5F0(fld_e92, 59, 60);  // 调 sub_69A5F0
  sub_69A840(*(this + 12));  // 调 sub_69A840
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 13, 6);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 28))(this, 3);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
}



// ------------------------------------------------------------
// 0x637EC0 CNRDFriendRemoveConfirmWindow__vmt8 —— CNRDFriendRemoveConfirmWindow__vmt8 确认移除（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDFriendRemoveConfirmWindow__vmt8(uint32_t *this)
{
  int fld_e9; // eax
  uint32_t *pThis_C; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    if ( *(this + 17) < 0x10u )  // 若 *(this + 17) < 0x10u
      pThis_C = this + 12;
    else
      pThis_C = (uint32_t *)*(this + 12);
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F8510 + 8))(dword_8F8510, pThis_C);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = (uint8_t *)*(this + 10);  // this+40 = 状态子标志
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x637F50 sub_637F50 —— 好友移除清理（69C3C0 + 43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_637F50(uint32_t *this)  // 函数: 好友移除清理（69C3C0 + 43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  sub_69C3C0(1);  // 调 sub_69C3C0
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ------------------------------------------------------------
// 0x638040 CNRDFriendRemoveConfirmWindow__vmtC —— CNRDFriendRemoveConfirmWindow__vmtC 文案装配（479290 好友查询 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDFriendRemoveConfirmWindow__vmtC(char *this, void *Src, int nArg3)  // 函数: CNRDFriendRemoveConfirmWindow__vmtC 文案装配（479290 好友查询 + 69C340 系）
{
  const char *pThis_30; // eax
  char *v5; // eax
  char *pThis_302; // edi
  char *v8; // eax
  int v9; // edi
  int pThis_3; // eax
  int pThis_2; // edi
  int v12; // eax
  int pThis_22; // edi
  uint32_t *pThis_23; // ecx
  int v15; // ebx

  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  if ( *((uint32_t *)this + 17) < 0x10u )  // 若 *((uint32_t *)this + 17) < 0x10u
    pThis_30 = this + 48;
  else
    pThis_30 = *((const char **)this + 12);
  if ( sub_479290((uint32_t *)dword_8F8510, pThis_30) == -1 )  // 若 sub_479290((uint32_t *)dword_8F8510, pThis_30) == -1
  {
    v5 = sub_422E70(937);  // 调 sub_422E70
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v5, 0);  // 调 对象池借出（按池号取可用对象）
    return 0;
  }
  else
  {
    sub_69C340(-1);  // 调 sub_69C340
    sub_69C440(-1);  // 调 sub_69C440
    if ( *((uint32_t *)this + 17) < 0x10u )  // 若 *((uint32_t *)this + 17) < 0x10u
      pThis_302 = this + 48;
    else
      pThis_302 = *((char **)this + 12);
    sub_69C360(pThis_302, 0);  // 调 sub_69C360
    v8 = sub_422E70(938);  // 调 sub_422E70
    sub_69C360(v8, 0);  // 调 sub_69C360
    v9 = *(uint32_t *)this;  // v9 = this
    pThis_3 = sub_69C500(*((uint32_t *)this + 3));  // this+12 = 技能槽记录次字
    (*(void (/*thiscall*/ **)(char *, int, int))(v9 + 24))(this, 14, pThis_3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
    pThis_2 = *((uint32_t *)this + 2);  // this+8 = 技能槽记录首字
    v12 = pt.y - *(uint32_t *)(pThis_2 + 32) + 31;
    if ( (pt.x - 125 <= 0 ? 0 : pt.x - 125) >= 640 - *(uint32_t *)(pThis_2 + 28) )  // 若 (pt.x - 125 <= 0 ? 0 : pt.x - 125) >= 640 - *(uint32_t *)(pThi..
      pThis_22 = 640 - *(uint32_t *)(*((uint32_t *)this + 2) + 28);  // this+8 = 技能槽记录首字
    else
      pThis_22 = pt.x - 125 <= 0 ? 0 : pt.x - 125;
    pThis_23 = *((uint32_t **)this + 2);
    v15 = v12 <= 0 ? 0 : v12;
    if ( v15 >= 480 - pThis_23[8] )  // 若 v15 >= 480 - pThis_23[8]
      v15 = 480 - pThis_23[8];
    sub_69A5F0(pThis_23, pThis_22, v15);  // 调 sub_69A5F0
    sub_69A5F0(*((uint32_t **)this + 9), pThis_22 + 29, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v15 - 43);  // this+8 = 技能槽记录首字
    sub_69A5F0(*((uint32_t **)this + 10), pThis_22 + 98, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v15 - 43);  // this+8 = 技能槽记录首字
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
  int fld_e10; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1064))(dword_8F7C04) == 100 )  // 调用虚函数（虚表槽 +1064）
    return (uint8_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  fld_e10 = *(this + 10);  // this+40 = 状态子标志
  if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )  // 若 *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    sub_423200(dword_8F7B08, 9);  // 【发送网络包API】
    sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x638250 CNRDStaminaRecoverConfirmWindow__vmtC —— CNRDStaminaRecoverConfirmWindow__vmtC 文案装配（422E70/44E8D0 + 69A5F0 + 69C340/69C360）
// ------------------------------------------------------------
char /*thiscall*/ CNRDStaminaRecoverConfirmWindow__vmtC(uint32_t **this, int nArg2, int nArg3)  // 函数: CNRDStaminaRecoverConfirmWindow__vmtC 文案装配（422E70/44E8D0 + 69A5F0 + 69C340/69C360）
{
  char *v4; // eax
  char *v6; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1064))(dword_8F7C04) == 100 )  // 调用虚函数（虚表槽 +1064）
  {
    v4 = sub_422E70(1156);  // 调 sub_422E70
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v4, 0);  // 调 对象池借出（按池号取可用对象）
    return 0;
  }
  else
  {
    sub_69A5F0(*(this + 2), (640 - (*(this + 2))[7]) / 2, (480 - (*(this + 2))[8]) / 2);  // this+8 = 技能槽记录首字
    sub_69C340(-1);  // 调 sub_69C340
    v6 = sub_422E70(1157);  // 调 sub_422E70
    sub_69C360(v6, 0);  // 调 sub_69C360
    return 1;
  }
}



// ------------------------------------------------------------
// 0x6382E0 sub_6382E0 —— 疲劳清理（29 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6382E0(uint32_t *this, int nArg2, int pArg3)  // 函数: 疲劳清理（29 行）
{
  int fld_e54; // eax
  int fld_e55; // edx
  int fld_e552; // eax
  int fld_e542; // edx

  fld_e54 = *(this + 54);  // fld_e54 = this+54
  if ( fld_e54 != 0 )  // 若 fld_e54 != 0
    fld_e55 = (*(this + 55) - fld_e54) >> 2;
  else
    fld_e55 = 0;
  fld_e552 = nArg2;
  if ( fld_e55 < nArg2 )  // 若 fld_e55 < nArg2
  {
    fld_e542 = *(this + 54);  // fld_e542 = this+54
    if ( fld_e542 != 0 )  // 若 fld_e542 != 0
      fld_e552 = (*(this + 55) - fld_e542) >> 2;
    else
      fld_e552 = 0;
  }
  return *(uint32_t *)(*(this + 54) + 4 * fld_e552 - 4) * (100 - pArg3) / 90;
}



// ------------------------------------------------------------
// 0x638350 CNRDStaminaRecoverConfirmWindow__vmt0 —— CNRDStaminaRecoverConfirmWindow__vmt0 构造（65 行：418DD0/422E70/429830/41A5E0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDStaminaRecoverConfirmWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDStaminaRecoverConfirmWindow__vmt0 构造（65 行：418DD0/422E70/429830/41A5E0）
{
  int result; // eax
  int v4; // edi
  int v5; // ebx
  int pObj4; // eax
  int pObj5; // eax
  int pObj2; // eax
  int pObj; // eax
  int pObj3; // eax
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

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
    v20 = v5;
    pObj4 = sub_418DD0(172);  // 调 sub_418DD0
    if ( pObj4 != 0 )  // 若 pObj4 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v4 + 8, v5 + 13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj5 = sub_418DD0(171);  // 调 sub_418DD0
    if ( pObj5 != 0 )  // 若 pObj5 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v4 + 36, v5 + 19, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj2 = sub_418DD0(173);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v4 + 11, v5 + 47, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj = sub_418DD0(174);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v4 + 21, v5 + 158, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj3 = sub_418DD0(175);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v4 + 11, v5 + 199, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    v11 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    v12 = sub_422E70(1158);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v11 + 80))(dword_79C0B0, v4 + 67, v20 + 154, -1, v12);  // 调用虚函数（虚表槽 +80）
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, this + 25);  // 调用虚函数（虚表槽 +68）【推断: 观察者组件懒创建（0x10 字节）】
    v13 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // 调 表按键查找（uint16）
    v14 = sub_41A5E0(v13 + 53);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    v15 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    v16 = v14;
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1064))(dword_8F7C04);  // 调用虚函数（虚表槽 +1064）
    v19 = sub_6382E0(byte_8F85E0, v16, v17);  // 调 疲劳清理（29 行）
    v18 = sub_422E70(1159);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, char *, int))(v15 + 80))(dword_79C0B0, v4, v20 + 205, -1, v18, v19);  // 调用虚函数（虚表槽 +80）
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  }
  return result;
}



// ------------------------------------------------------------
// 0x638520 sub_638520 —— 疲劳窗页绘制（69A5F0 + 69C440 + 43C410/69A840，73 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_638520(int *this)  // 函数: 疲劳窗页绘制（69A5F0 + 69C440 + 43C410/69A840，73 行）
{
  int v2; // edx
  uint32_t *pMem; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e92; // eax
  int result; // eax

  v2 = *this;
  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+36 = 状态字
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(116, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  sub_69A5F0((uint32_t *)*(this + 3), 88, 66);  // this+12 = 技能槽记录次字
  sub_69C440(-1);  // 调 sub_69C440
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 18, 20);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e9 = sub_43C410(pMem, *(this + 9), 21, 22, 23, 21, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 10) = (int)fld_e9;  // this+40 = 状态子标志
  sub_69A5F0(fld_e9, 57, 232);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e92 = sub_43C410(pMem2, *(this + 9), 24, 25, 26, 24, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e92 = nullptr;  // fld_e92 = nullptr 空指针
  *(this + 11) = (int)fld_e92;  // this+44 = (int)fld_e92
  sub_69A5F0(fld_e92, 118, 232);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;  // this+60 = 0
  *(this + 18) = 0;  // this+72 = 0
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 17) = 12;  // this+68 = 12
  *(this + 19) = 1600;  // this+76 = 1600
  *(this + 16) = 6;  // this+64 = 6
  *(this + 24) = dword_99FCCC;  // this+96 = dword_99FCCC
  *(this + 19) = 150;  // this+76 = 150
  *((uint8_t *)this + 100) = 0;
  *((uint8_t *)this + 101) = 0;
  *((uint8_t *)this + 102) = 0;
  *((uint8_t *)this + 103) = 0;
  *(this + 28) = 0;  // this+112 = pHostComp
  *(this + 30) = 12;  // this+120 = 动画对象指针
  *(this + 31) = 0;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
  *(this + 33) = 0;  // this+132 = 0
  *(this + 34) = 0;  // this+136 = 0
  *(this + 35) = 0;  // this+140 = 0
  *(this + 36) = 0;  // this+144 = pFrameList144
  *(this + 37) = 0;  // this+148 = 0
  *(this + 29) = 6;  // this+116 = 6
  *(this + 32) = 1600;  // this+128 = 1600
  result = dword_99FCCC;
  *(this + 37) = dword_99FCCC;  // this+148 = dword_99FCCC
  *(this + 28) = 2;  // this+112 = pHostComp
  *(this + 32) = 207;  // this+128 = 207
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
int /*thiscall*/ sub_6386E0(uint32_t *this)  // 函数: 商城提示数据（13 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 13) = 0;  // this+52 = bAuraState
  return 0;
}



// ------------------------------------------------------------
// 0x6386F0 CNRDInformCashShopWindow__vmtC —— CNRDInformCashShopWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDInformCashShopWindow__vmtC(int this, int nArg2, int nArg3)  // 函数: CNRDInformCashShopWindow__vmtC 打开槽（69A5F0）
{
  sub_69A5F0(*(uint32_t **)(this + 8), 122, 14);  // 调 sub_69A5F0
  *(uint32_t *)(this + 52) = 0;  // this+52 = 0
  return 1;
}



// ------------------------------------------------------------
// 0x638710 CNRDCashShopDoubleEventWindow__vmtC —— CNRDCashShopDoubleEventWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDCashShopDoubleEventWindow__vmtC(uint32_t **this, int nArg2, int nArg3)  // 函数: CNRDCashShopDoubleEventWindow__vmtC 打开槽（69A5F0）
{
  sub_69A5F0(*(this + 2), 74, 55);  // this+8 = 技能槽记录首字
  ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[6])(this, 40, 28);
  return 1;
}



// ------------------------------------------------------------
// 0x638730 CNRDInformCashShopWindow__vmt8 —— CNRDInformCashShopWindow__vmt8 Update（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDInformCashShopWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  result = (uint8_t *)*(this + 10);  // this+40 = 状态子标志
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x638770 CNRDInformCashShopWindow__vmt0 —— CNRDInformCashShopWindow__vmt0 构造（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDInformCashShopWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDInformCashShopWindow__vmt0 构造（418DD0）
{
  int result; // eax
  int v4; // ebx
  int v5; // esi

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 9) )  // this+36 = 状态字
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
    result = sub_418DD0(0);  // 调 sub_418DD0
    if ( result != 0 )  // 若 result != 0
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
               result,
               v4 - 120,
               v5 - 15,
               dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
  }
  return result;
}



// ------------------------------------------------------------
// 0x6387C0 CNRDCashShopDoubleEventWindow__vmt0 —— CNRDCashShopDoubleEventWindow__vmt0 构造：加载 interface/cashshop/cashshopdoubleevent.img（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopDoubleEventWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDCashShopDoubleEventWindow__vmt0 构造：加载 interface/cashshop/cashshopdoubleevent.img（418DD0）
{
  int result; // eax
  int v4; // edi
  int v5; // ebx
  int pObj; // eax

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 9) )  // this+36 = 状态字
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
    (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
      dword_8F84B8,
      "interface/cashshop/cashshopdoubleevent.img");
    pObj = sub_418DD0(0);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v4 + 19, v5 + 25, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    if ( GetTickCount() % 0x578 >= 0x2BC )  // 调 取系统运行毫秒数
      result = sub_418DD0(2);  // 调 sub_418DD0
    else
      result = sub_418DD0(1);  // 调 sub_418DD0
    if ( result != 0 )  // 若 result != 0
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
               result,
               v4 + 44,
               v5 + 181,
               dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
  }
  return result;
}



// ------------------------------------------------------------
// 0x638870 sub_638870 —— 商城提示页绘制（426BD0/69A840/43C410/69A5F0，41 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_638870(int *this)  // 函数: 商城提示页绘制（426BD0/69A840/43C410/69A5F0，41 行）
{
  uint8_t *pMem; // eax
  uint8_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax
  int v6; // edx
  int result; // eax

  pMem = operator new(0x68u);  // operator new 分配 104 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_426BD0(pMem);  // 调 nengine::IControl 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = (int)v3;  // this+36 = 状态字
  *((uint32_t *)v3 + 17) = this;
  sub_69A840(*(this + 9));  // this+36 = 状态字
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = (int)v5;  // this+40 = 状态子标志
  sub_69A5F0(v5, 169, 402);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  *(this + 11) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 168);  // this+44 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  v6 = *this;
  *(this + 12) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 132);  // this+48 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  result = (*(int (/*thiscall*/ **)(int *, int, int))(v6 + 24))(this, 32, 33);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  *(this + 14) = 150;  // this+56 = 150
  *(this + 15) = 240;  // this+60 = 240
  *(this + 16) = -60;  // this+64 = -60
  *(this + 17) = 0;  // this+68 = 0
  return result;
}



// ------------------------------------------------------------
// 0x638990 sub_638990 —— 商城提示页绘制 2（426BD0/69A840/43C410/69A5F0，31 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_638990(uint32_t *this)  // 函数: 商城提示页绘制 2（426BD0/69A840/43C410/69A5F0，31 行）
{
  uint8_t *pMem; // eax
  uint8_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  *(this + 9) = 0;  // this+36 = 状态字
  pMem = operator new(0x68u);  // operator new 分配 104 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_426BD0(pMem);  // 调 nengine::IControl 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  *((uint32_t *)v3 + 17) = this;
  sub_69A840(*(this + 9));  // this+36 = 状态字
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  sub_69A5F0(v5, 215, 336);  // 调 sub_69A5F0
  return sub_69A840(*(this + 10));  // this+40 = 状态子标志
}



// ------------------------------------------------------------
// 0x638A70 sub_638A70 —— 商城提示数据（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_638A70(uint32_t *this)  // 函数: 商城提示数据（15 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 26) = 0;  // this+104 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x638A90 sub_638A90 —— 商城提示数据 2（27 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_638A90(uint32_t *this)  // 函数: 商城提示数据 2（27 行）
{
  int (/*thiscall*/ ***fld_e9)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx

  fld_e9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);  // this+36 = 状态字
  if ( fld_e9 != nullptr )  // 若 fld_e9 非空
    result = (**fld_e9)(fld_e9, 1);
  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);  // this+40 = 状态子标志
  *(this + 9) = 0;  // this+36 = 状态字
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    result = (**fld_e10)(fld_e10, 1);
  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;  // this+40 = 状态子标志
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    result = (**fld_e11)(fld_e11, 1);
  *(this + 11) = 0;  // this+44 = 0
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
  int fld_e9; // eax
  int dword_79BE342; // ecx
  int fld_e11; // eax
  int fld_e26; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e9 = *(this + 9);  // this+36 = 状态字
  dword_79BE342 = dword_79BE34;
  if ( *(uint8_t *)(fld_e9 + 17) == 0 || dword_79BE34 != *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) == 0 || dword_79BE34 != *(uint32_t *..
  {
    fld_e11 = *(this + 11);  // fld_e11 = this+11
    if ( *(uint8_t *)(fld_e11 + 17) == 0 || dword_79BE34 != *(uint32_t *)(fld_e11 + 12) )  // 若 *(uint8_t *)(fld_e11 + 17) == 0 || dword_79BE34 != *(uint32_t ..
      goto LABEL_11;  // 跳转 LABEL_11
  }
  fld_e26 = *(this + 26);  // fld_e26 = this+26
  if ( fld_e26 == 0 )  // 若 fld_e26 == 0
  {
    sub_423200(dword_8F7B08, 71);  // 【发送网络包API】
LABEL_9:
    sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    goto LABEL_10;  // 跳转 LABEL_10
  }
  if ( fld_e26 == 2 )  // 若 fld_e26 == 2
  {
    sub_423200(dword_8F7B08, 76);  // 【发送网络包API】
    goto LABEL_9;  // 跳转 LABEL_9
  }
LABEL_10:
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  dword_79BE342 = dword_79BE34;
LABEL_11:
  result = (uint8_t *)*(this + 10);  // this+40 = 状态子标志
  if ( result[17] != 0 && dword_79BE342 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE342 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x638B80 sub_638B80 —— 公会窗文案装配（69C340 系 + 422E70，57 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_638B80(uint32_t *this, int nArg2)  // 函数: 公会窗文案装配（69C340 系 + 422E70，57 行）
{
  int fld_e2; // eax
  int v4; // ebx
  int v5; // edi
  char *v6; // eax
  int fld_e3; // eax
  uint32_t *result; // eax

  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  v4 = *(uint32_t *)(fld_e2 + 20);  // v4 = fld_e2+20
  v5 = *(uint32_t *)(fld_e2 + 24);  // v5 = fld_e2+24
  sub_69C340(-1);  // 调 sub_69C340
  sub_69A5F0((uint32_t *)*(this + 3), v4 + 17, v5 + 58);  // this+12 = 技能槽记录次字
  switch ( nArg2 )  // 分支：按 nArg2 分派
  {
    case 0:
      v6 = sub_422E70(946);  // 调 sub_422E70
LABEL_7:
      sub_69C360(v6, 0);  // 调 sub_69C360
      break;
    case 1:
      v6 = sub_422E70(947);  // 调 sub_422E70
      goto LABEL_7;  // 跳转 LABEL_7
    case 2:
      v6 = sub_422E70(948);  // 调 sub_422E70
      goto LABEL_7;  // 跳转 LABEL_7
    default:
      break;
  }
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 17, fld_e3 + 8);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  if ( nArg2 == 0 || nArg2 == 2 )  // 若 nArg2 == 0 || nArg2 == 2
  {
    *(uint8_t *)(*(this + 9) + 16) = 1;  // this+36 = 状态字
    *(uint8_t *)(*(this + 10) + 16) = 1;  // this+40 = 状态子标志
    *(uint8_t *)(*(this + 11) + 16) = 0;
    sub_69A5F0((uint32_t *)*(this + 9), v4 + 50, *(uint32_t *)(*(this + 2) + 32) + v5 - 43);  // this+36 = 状态字
    result = sub_69A5F0((uint32_t *)*(this + 10), v4 + 113, *(uint32_t *)(*(this + 2) + 32) + v5 - 43);  // this+40 = 状态子标志
    *(this + 26) = nArg2;  // this+104 = nArg2
  }
  else
  {
    *(uint8_t *)(*(this + 9) + 16) = 0;  // this+36 = 状态字
    *(uint8_t *)(*(this + 10) + 16) = 0;  // this+40 = 状态子标志
    *(uint8_t *)(*(this + 11) + 16) = 1;
    result = sub_69A5F0((uint32_t *)*(this + 11), v4 + 82, *(uint32_t *)(*(this + 2) + 32) + v5 - 43);  // this+8 = 技能槽记录首字
    *(this + 26) = nArg2;  // this+104 = nArg2
  }
  return result;
}



// ------------------------------------------------------------
// 0x638CA0 CNRDGuildWindow__vmtC —— CNRDGuildWindow__vmtC 打开槽：POP_UP 事件（638B80 + 69A5F0 + 432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDGuildWindow__vmtC(int this, int nArg2, int nArg3)  // 函数: CNRDGuildWindow__vmtC 打开槽：POP_UP 事件（638B80 + 69A5F0 + 432EA0）
{
  sub_638B80((uint32_t *)this, nArg3);  // 调 公会窗文案装配（69C340 系 + 422E70，57 行）
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) / 2,
    (480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) / 2);
  sub_432EA0("POP_UP", -1, 0, 0);  // 调 音效播放包装（非空判定）
  return 1;
}



// ------------------------------------------------------------
// 0x638D00 CNRDGuildWindow__vmt0 —— CNRDGuildWindow__vmt0 构造（418DD0 + 422E70）
// ------------------------------------------------------------
int /*thiscall*/ CNRDGuildWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDGuildWindow__vmt0 构造（418DD0 + 422E70）
{
  int result; // eax
  int v4; // esi
  int v5; // edi
  int pObj; // eax
  int pObj2; // eax
  char *v8; // eax

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
    pObj = sub_418DD0(90);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
        pObj,
        v4 + 6,
        v5 + 6,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,
        1065353216,
        0,
        872415231,
        1333788672,
        1333788672);
    pObj2 = sub_418DD0(199);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v4 + 7, v5 + 7, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 13);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    if ( *(this + 26) == 2 )  // 若 *(this + 26) == 2
      v8 = sub_422E70(944);  // 调 sub_422E70
    else
      v8 = sub_422E70(945);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      v4,
      v5 + 17,
      -1190552,
      v8);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  }
  return result;
}



// ------------------------------------------------------------
// 0x638DF0 sub_638DF0 —— 公会清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_638DF0(uint32_t *this)  // 函数: 公会清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e12; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e122; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_e123; // eax
  int v8; // eax

  *(this + 12) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+48 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e12 = sub_43C410(pMem, *(this + 12), 21, 22, 23, 21, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e12 = nullptr;  // fld_e12 = nullptr 空指针
  *(this + 9) = fld_e12;  // this+36 = 状态字
  sub_69A840(fld_e12);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e122 = sub_43C410(pMem2, *(this + 12), 24, 25, 26, 24, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e122 = nullptr;  // fld_e122 = nullptr 空指针
  *(this + 10) = fld_e122;  // this+40 = 状态子标志
  sub_69A840(fld_e122);  // 调 sub_69A840
  pMem3 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    fld_e123 = sub_43C410(pMem3, *(this + 12), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e123 = nullptr;  // fld_e123 = nullptr 空指针
  *(this + 11) = fld_e123;  // this+44 = fld_e123
  sub_69A840(fld_e123);  // 调 sub_69A840
  *((uint8_t *)this + 52) = 0;  // this+52 = bAuraState
  *((uint8_t *)this + 53) = 0;
  *((uint8_t *)this + 54) = 0;
  *((uint8_t *)this + 55) = 0;
  *(this + 16) = 0;  // this+64 = 0
  *(this + 17) = 6;  // this+68 = 6
  *(this + 18) = 12;  // this+72 = 12
  *(this + 19) = 0;  // this+76 = 0
  *(this + 20) = 1600;  // this+80 = nAuraStage
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 25) = 0;  // this+100 = 0
  v8 = *this;
  *(this + 25) = dword_99FCCC;  // this+100 = dword_99FCCC
  *(this + 20) = 216;  // this+80 = nAuraStage
  *(this + 16) = 1;  // this+64 = 1
  *(this + 14) = -16777216;  // this+56 = -16777216
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v8 + 44))(this, 182, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
}



// ------------------------------------------------------------
// 0x638F70 CNRDGuildConfirmWindow__vmt8 —— CNRDGuildConfirmWindow__vmt8 确认流程（111 行：69A650 + CLICK_BUTTON2）
// ------------------------------------------------------------
HRESULT /*thiscall*/ CNRDGuildConfirmWindow__vmt8(uint32_t *this)  // 函数: CNRDGuildConfirmWindow__vmt8 确认流程（111 行：69A650 + CLICK_BUTTON2）
{
  int fld_e2; // ecx
  int fld_e9; // eax
  const wchar_t *fld_e11; // ecx
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
  int dword_796E502; // [esp+248h] [ebp-4h]

  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  sub_69A650(fld_e2);  // 调 sub_69A650
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    v15 = 0;
    v10 = 0;
    v16 = 0;
    v11 = 0;
    v17 = 0;
    v12 = 0;
    v18 = 0;
    v13 = 0;
    fld_e11 = (const wchar_t *)*(this + 11);
    v21 = 0;
    v22 = 0;
    ppv = nullptr;  // ppv = nullptr 空指针
    v14 = 0;
    v9 = 0;
    memset(&pvarg, 0, sizeof(pvarg));  // 调 内存按字节填充
    v20 = 0;
    v23 = 0;
    swprintf(Buffer, (const size_t)&off_73DF80, fld_e11);
    DesktopWindow = GetDesktopWindow();
    SetForegroundWindow(DesktopWindow);  // 调 置前台窗口
    result = CoInitialize(nullptr);  // 调 初始化 COM
    if ( result >= 0 )  // 若 result >= 0
    {
      if ( CoCreateInstance(&stru_743300, nullptr, 5u, &stru_743330, &ppv) >= 0 )  // 调 创建 COM 组件实例
      {
        v7 = SysAllocString(Buffer);  // 调 分配 BSTR
        if ( v7 != nullptr )  // 若 v7 非空
        {
          v8 = SysAllocString(&psz);  // 调 分配 BSTR
          if ( v8 != nullptr )  // 若 v8 非空
          {
            v20 = 8;
            *(uint32_t *)((char *)&v22 + 2) = v8;
            (*(void (/*stdcall*/ **)(LPVOID, OLECHAR *, int16_t *, int16_t *, VARIANTARG *, int16_t *))(*(uint32_t *)ppv + 44))(  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
              ppv,
              v7,
              &v14,
              &v9,
              &pvarg,
              &v20);
            (*(void (/*stdcall*/ **)(LPVOID, int))(*(uint32_t *)ppv + 104))(ppv, 990);  // 调用虚函数（虚表槽 +104）【推断: 观察者数组元素访问（越界返回 0）】
            (*(void (/*stdcall*/ **)(LPVOID, int))(*(uint32_t *)ppv + 112))(ppv, 570);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
            (*(void (/*stdcall*/ **)(LPVOID, uint32_t))(*(uint32_t *)ppv + 196))(ppv, 0);  // 调用虚函数（虚表槽 +196）
            (*(void (/*stdcall*/ **)(LPVOID, uint32_t))(*(uint32_t *)ppv + 188))(ppv, 0);  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
            (*(void (/*stdcall*/ **)(LPVOID, uint32_t))(*(uint32_t *)ppv + 172))(ppv, 0);  // 调用虚函数（虚表槽 +172）【推断: 朝目标方向按比例取点: p = this + (target −…】
            (*(void (/*stdcall*/ **)(LPVOID, uint32_t))(*(uint32_t *)ppv + 280))(ppv, 0);  // 调用虚函数（虚表槽 +280）
            (*(void (/*stdcall*/ **)(LPVOID, int))(*(uint32_t *)ppv + 164))(ppv, -1);  // 调用虚函数（虚表槽 +164）【推断: ★ 与目标朝向角度（atan2 角度制；3D 俯视判定）】
          }
          SysFreeString(v7);  // 调 释放 BSTR
          if ( v8 != nullptr )  // 若 v8 非空
            SysFreeString(v8);  // 调 释放 BSTR
        }
      }
      VariantClear(&pvarg);  // 调 清空 VARIANT
      if ( ppv != nullptr )  // 若 ppv 非空
        (*(void (/*stdcall*/ **)(LPVOID))(*(uint32_t *)ppv + 8))(ppv);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
      CoUninitialize();  // 调 反初始化 COM
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
  }
  else
  {
    result = *(this + 10);  // this+40 = 状态子标志
    if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 若 *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *..
    {
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6391F0 CNRDGuildConfirmWindow__vmtC —— CNRDGuildConfirmWindow__vmtC 文案装配（69C340 系 + 69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDGuildConfirmWindow__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDGuildConfirmWindow__vmtC 文案装配（69C340 系 + 69A5F0）
{
  int v4; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
  int v7; // ebx
  int v8; // edi

  *(this + 11) = nArg3;  // this+44 = nArg3
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(nArg2, 0);  // 调 sub_69C360
  v4 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(int *, int, int))(v4 + 24))(this, 14, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v7 = pt.x - 55 <= 0 ? 0 : pt.x - 55;
  if ( v7 >= 640 - fld_e2[7] )  // 若 v7 >= 640 - fld_e2[7]
    v7 = 640 - fld_e2[7];
  v8 = 480 - fld_e2[8];
  if ( (pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31) < v8 )  // 若 (pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31) < v8
    v8 = pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31;
  sub_69A5F0(fld_e2, v7, v8);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v7 + 29, *(uint32_t *)(*(this + 2) + 32) + v8 - 43);  // this+36 = 状态字
  sub_69A5F0((uint32_t *)*(this + 10), v7 + 98, *(uint32_t *)(*(this + 2) + 32) + v8 - 43);  // this+40 = 状态子标志
  return 1;
}



// ------------------------------------------------------------
// 0x6392D0 sub_6392D0 —— 公会确认清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_6392D0(uint32_t *this)  // 函数: 公会确认清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ------------------------------------------------------------
// 0x6393B0 CNRDMoveToHomeConfirmWindow__vmt8 —— CNRDMoveToHomeConfirmWindow__vmt8 确认回城（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDMoveToHomeConfirmWindow__vmt8(uint32_t *this)
{
  int fld_e9; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 20))(this);  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = (uint8_t *)*(this + 10);  // this+40 = 状态子标志
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x639420 CNRDMoveToHomeConfirmWindow__vmtC —— CNRDMoveToHomeConfirmWindow__vmtC 文案装配（69C340 系 + 69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDMoveToHomeConfirmWindow__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDMoveToHomeConfirmWindow__vmtC 文案装配（69C340 系 + 69A5F0）
{
  int v4; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
  int v7; // ebx
  int v8; // edi

  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(nArg2, 0);  // 调 sub_69C360
  v4 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(int *, int, int))(v4 + 24))(this, 14, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v7 = (480 - fld_e2[8]) / 2;
  v8 = (640 - fld_e2[7]) / 2;
  sub_69A5F0(fld_e2, v8, v7);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v8 + 29, *(uint32_t *)(*(this + 2) + 32) + v7 - 43);  // this+36 = 状态字
  sub_69A5F0((uint32_t *)*(this + 10), v8 + 98, *(uint32_t *)(*(this + 2) + 32) + v7 - 43);  // this+40 = 状态子标志
  return 1;
}



// ------------------------------------------------------------
// 0x6394D0 CNRDMoveToHomeConfirmWindow__vmt14 —— CNRDMoveToHomeConfirmWindow__vmt14 关闭槽（转发 541F10 trade_shop 参数写入）
// ------------------------------------------------------------
char /*thiscall*/ CNRDMoveToHomeConfirmWindow__vmt14(void *this)  // 函数: CNRDMoveToHomeConfirmWindow__vmt14 关闭槽（转发 541F10 trade_shop 参数写入）
{
  sub_541F10();  // 调 上架参数写入 3（423200/423380 + 44ABF0）
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  return 1;
}



// ------------------------------------------------------------
// 0x6394F0 sub_6394F0 —— 回城清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_6394F0(uint32_t *this)  // 函数: 回城清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
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
char /*thiscall*/ CNRDPrivateStoreItemBuyConfirmWindow__vmt14(int *this)  // 函数: CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买（541A30/541B20 摊位条目 + 422E70/44E8D0）
{
  int fld_e13; // esi
  int v3; // eax
  int v4; // eax
  int *v5; // esi
  int v6; // ebx
  int v7; // eax
  int fld_e12; // ecx
  int pObj; // eax
  char *v11; // eax
  int fld_e122; // [esp+8h] [ebp-4h]

  fld_e13 = *(this + 13);  // this+52 = bAuraState
  v3 = sub_541A30();  // 调 摊位条目名取串（10 行）
  v4 = sub_541B20(v3);  // 调 sub_541B20
  if ( fld_e13 < *(uint32_t *)(v4 + 8) )  // 若 fld_e13 < *(uint32_t *)(v4 + 8)
  {
    v5 = *(int **)(*(uint32_t *)(v4 + 12) + 4 * fld_e13);
    if ( v5 != nullptr && (*(int (/*thiscall*/ **)(int *))(*v5 + 44))(v5) >= (unsigned int)*(this + 12) )  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
    {
      v6 = *v5;
      fld_e122 = 1;
      v7 = (*(int (/*thiscall*/ **)(int *))(*v5 + 16))(v5);  // 调用虚函数（虚表槽 +16）
      if ( (*(uint8_t (/*thiscall*/ **)(int *, uint32_t))(v6 + 60))(v5, *(uint32_t *)(v7 + 4)) != 0 )  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
      {
        fld_e12 = *(this + 12);  // fld_e12 = this+12
      }
      else
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v5 + 20))(v5, 2) == 0 )  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
        {
LABEL_9:
          pObj = sub_541A30();  // 调 摊位条目名取串（10 行）
          (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 80))(pObj, *(this + 13), fld_e122);  // this+52 = bAuraState
          (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
          return 1;
        }
        fld_e12 = *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 188))(v5);  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
      }
      fld_e122 = fld_e12;
      goto LABEL_9;  // 跳转 LABEL_9
    }
  }
  v11 = sub_422E70(1353);  // 调 sub_422E70
  sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v11, 0);  // 调 对象池借出（按池号取可用对象）
  (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  return 1;
}



// ------------------------------------------------------------
// 0x639690 sub_639690 —— 摆摊购买清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_639690(uint32_t *this)  // 函数: 摆摊购买清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 15, 16, 17, 15, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ------------------------------------------------------------
// 0x639770 CNRDPrivateStoreItemBuyConfirmWindow__vmtC —— CNRDPrivateStoreItemBuyConfirmWindow__vmtC 文案装配（115 行：541A30/541B20 + 4F36B0 下单 + 69C340 系）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreItemBuyConfirmWindow__vmtC(unsigned int *this, unsigned int **pDwArg2, unsigned int uArg3)  // 函数: CNRDPrivateStoreItemBuyConfirmWindow__vmtC 文案装配（115 行：541A30/541B20 + 4F36B0 下单 + 69C340 系）
{
  int fld_e13; // edi
  int v5; // eax
  int v6; // eax
  int64_t v7; // rcx
  int pObj; // edi
  unsigned int fld_e12; // ecx
  char *v10; // eax
  char *psz3; // eax
  int v12; // eax
  char *v13; // eax
  char *psz; // eax
  char *psz2; // eax
  void **v16; // eax
  unsigned int v17; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
  int v20; // ebx
  int v21; // edi
  unsigned int fld_e11; // [esp-8h] [ebp-15Ch]
  int v24; // [esp-8h] [ebp-15Ch]
  int fld_e122; // [esp-4h] [ebp-158h]
  char Buffer[256]; // [esp+Ch] [ebp-148h] BYREF
  uint8_t v27[4]; // [esp+10Ch] [ebp-48h] BYREF
  void *Block; // [esp+110h] [ebp-44h]
  int v29; // [esp+120h] [ebp-34h]
  unsigned int v30; // [esp+124h] [ebp-30h]
  uint8_t v31[4]; // [esp+128h] [ebp-2Ch] BYREF
  void *v32[5]; // [esp+12Ch] [ebp-28h] BYREF
  unsigned int v33; // [esp+140h] [ebp-14h]
  int dword_796E502; // [esp+144h] [ebp-10h]
  int v35; // [esp+150h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  *(this + 13) = **pDwArg2;  // this+52 = bAuraState
  v7 = *pDwArg2[1];
  *(this + 12) = v7;  // this+48 = v7
  *(this + 11) = uArg3;  // this+44 = uArg3
  v33 = 15;
  v32[4] = nullptr;  // v32[4] = nullptr 空指针
  LOBYTE(v32[0]) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  fld_e13 = *(this + 13);  // this+52 = bAuraState
  v35 = HIDWORD(v7);  // 调 取 64 位值高 32 位
  v5 = sub_541A30();  // 调 摊位条目名取串（10 行）
  v6 = sub_541B20(v5);  // 调 sub_541B20
  if ( fld_e13 >= *(uint32_t *)(v6 + 8) )  // 若 fld_e13 >= *(uint32_t *)(v6 + 8)
    return 0;
  pObj = *(uint32_t *)(*(uint32_t *)(v6 + 12) + 4 * fld_e13);
  if ( pObj == HIDWORD(v7) )  // 调 取 64 位值高 32 位
    return 0;
  fld_e12 = *(this + 12);  // fld_e12 = this+12
  fld_e11 = *(this + 11);  // fld_e11 = this+11
  if ( !is_mul_ok(fld_e12, fld_e11) || fld_e12 * fld_e11 > 0x7FFFFFFF )  // 若 !is_mul_ok(fld_e12, fld_e11) || fld_e12 * fld_e11 > 0x7FFFFFFF
  {
    v10 = sub_422E70(1354);  // 调 sub_422E70
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v10, 0);  // 调 对象池借出（按池号取可用对象）
    return 0;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 20))(pObj, 2) != 0 && *(this + 12) == 1 )  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
  {
    psz3 = (char *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 108))(pObj);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
  }
  else
  {
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 108))(pObj);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
    fld_e122 = *(this + 12);  // fld_e122 = this+12
    v24 = v12;
    v13 = sub_422E70(949);  // 调 sub_422E70
    sprintf(Buffer, v13, v24, fld_e122);  // 调 格式化到缓冲
    psz3 = Buffer;
  }
  sub_4022F0((std::_String_base *)v31, psz3, strlen(psz3));  // 调 std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
  psz = sub_422E70(950);  // 调 sub_422E70
  sub_4022F0((std::_String_base *)v31, psz, strlen(psz));  // 调 std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
  sub_4F36B0(v27, *(this + 11) * *(this + 12), 0, 0, 0);  // 调 sub_4F36B0
  LOBYTE(v35) = 1;  // 调 取 16 位值低 8 位
  sub_4021F0((std::_String_base *)v31, v27, 0, -1);  // 调 std::string::append(str, pos, n) 模板实例（含自引用重叠路径）
  psz2 = sub_422E70(951);  // 调 sub_422E70
  sub_4022F0((std::_String_base *)v31, psz2, strlen(psz2));  // 调 std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  v16 = (void **)v32[0];
  if ( v33 < 0x10 )  // 若 v33 < 0x10
    v16 = v32;
  sub_69C360(v16, 0);  // 调 sub_69C360
  v17 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(unsigned int *, int, int))(v17 + 24))(this, 14, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v20 = pt.x - 55 <= 0 ? 0 : pt.x - 55;
  if ( v20 >= 640 - fld_e2[7] )  // 若 v20 >= 640 - fld_e2[7]
    v20 = 640 - fld_e2[7];
  v21 = 480 - fld_e2[8];
  if ( (pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31) < v21 )  // 若 (pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31) < v21
    v21 = pt.y - fld_e2[8] + 31 <= 0 ? 0 : pt.y - fld_e2[8] + 31;
  sub_69A5F0(fld_e2, v20, v21);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v20 + 29, *(uint32_t *)(*(this + 2) + 32) + v21 - 43);  // this+36 = 状态字
  sub_69A5F0((uint32_t *)*(this + 10), v20 + 98, *(uint32_t *)(*(this + 2) + 32) + v21 - 43);  // this+40 = 状态子标志
  if ( v30 >= 0x10 )  // 若 v30 >= 0x10
    j__free(Block);  // 调 堆释放
  v30 = 15;
  v29 = 0;
  LOBYTE(Block) = 0;  // 调 取 16 位值低 8 位
  if ( v33 >= 0x10 )  // 若 v33 >= 0x10
    j__free(v32[0]);  // 调 堆释放
  return 1;
}



// ------------------------------------------------------------
// 0x639A50 CNRDMemberRemoveConfirmWindow__vmt8 —— CNRDMemberRemoveConfirmWindow__vmt8 确认移除（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDMemberRemoveConfirmWindow__vmt8(uint32_t *this)
{
  int fld_e9; // eax
  uint32_t *pThis_C; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    if ( *(this + 17) < 0x10u )  // 若 *(this + 17) < 0x10u
      pThis_C = this + 12;
    else
      pThis_C = (uint32_t *)*(this + 12);
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F8518 + 8))(dword_8F8518, pThis_C);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = (uint8_t *)*(this + 10);  // this+40 = 状态子标志
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x639AE0 sub_639AE0 —— 成员移除清理（69C3C0 + 43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_639AE0(uint32_t *this)  // 函数: 成员移除清理（69C3C0 + 43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  sub_69C3C0(1);  // 调 sub_69C3C0
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
}



// ------------------------------------------------------------
// 0x639BD0 sub_639BD0 —— 成员移除数据（4015C0）
// ------------------------------------------------------------
int /*thiscall*/ sub_639BD0(uint32_t *this)  // 函数: 成员移除数据（4015C0）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  return sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x639BF0 CNRDMemberRemoveConfirmWindow__vmtC —— CNRDMemberRemoveConfirmWindow__vmtC 文案装配（69C340 系 + 422E70）
// ------------------------------------------------------------
char /*thiscall*/ CNRDMemberRemoveConfirmWindow__vmtC(char *this, void *Src, int nArg3)  // 函数: CNRDMemberRemoveConfirmWindow__vmtC 文案装配（69C340 系 + 422E70）
{
  char *pThis_30; // edi
  char *v5; // eax
  int v6; // edi
  int pThis_3; // eax
  int pThis_2; // edi
  int v9; // eax
  int pThis_22; // edi
  uint32_t *pThis_23; // ecx
  int v12; // ebx

  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  if ( *((uint32_t *)this + 17) < 0x10u )  // 若 *((uint32_t *)this + 17) < 0x10u
    pThis_30 = this + 48;
  else
    pThis_30 = *((char **)this + 12);
  sub_69C360(pThis_30, 0);  // 调 sub_69C360
  v5 = sub_422E70(1500);  // 调 sub_422E70
  sub_69C360(v5, 0);  // 调 sub_69C360
  v6 = *(uint32_t *)this;  // v6 = this
  pThis_3 = sub_69C500(*((uint32_t *)this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(char *, int, int))(v6 + 24))(this, 14, pThis_3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  pThis_2 = *((uint32_t *)this + 2);  // this+8 = 技能槽记录首字
  v9 = pt.y - *(uint32_t *)(pThis_2 + 32) + 31;
  if ( (pt.x - 125 <= 0 ? 0 : pt.x - 125) >= 640 - *(uint32_t *)(pThis_2 + 28) )  // 若 (pt.x - 125 <= 0 ? 0 : pt.x - 125) >= 640 - *(uint32_t *)(pThi..
    pThis_22 = 640 - *(uint32_t *)(*((uint32_t *)this + 2) + 28);  // this+8 = 技能槽记录首字
  else
    pThis_22 = pt.x - 125 <= 0 ? 0 : pt.x - 125;
  pThis_23 = *((uint32_t **)this + 2);
  v12 = v9 <= 0 ? 0 : v9;
  if ( v12 >= 480 - pThis_23[8] )  // 若 v12 >= 480 - pThis_23[8]
    v12 = 480 - pThis_23[8];
  sub_69A5F0(pThis_23, pThis_22, v12);  // 调 sub_69A5F0
  sub_69A5F0(*((uint32_t **)this + 9), pThis_22 + 29, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v12 - 43);  // this+8 = 技能槽记录首字
  sub_69A5F0(*((uint32_t **)this + 10), pThis_22 + 98, *(uint32_t *)(*((uint32_t *)this + 2) + 32) + v12 - 43);  // this+8 = 技能槽记录首字
  return 1;
}



// ------------------------------------------------------------
// 0x639D20 CNRDResponseMemberWindow__vmtC —— CNRDResponseMemberWindow__vmtC 文案装配（69C340 系 + 698F90）
// ------------------------------------------------------------
char /*thiscall*/ CNRDResponseMemberWindow__vmtC(uint32_t *this, int nArg2, int nArg3)  // 函数: CNRDResponseMemberWindow__vmtC 文案装配（69C340 系 + 698F90）
{
  char *v5; // eax
  int v6; // edi
  int fld_e3; // eax
  uint32_t *fld_e2; // ecx
  unsigned int v9; // ebx
  unsigned int v10; // edi
  char Buffer[256]; // [esp+4h] [ebp-104h] BYREF
  int dword_796E502; // [esp+104h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )  // dword_8F7A24 = 当前场景状态对象
    return 0;
  v5 = sub_422E70(1512);  // 调 sub_422E70
  sprintf(Buffer, v5, nArg3, nArg2);  // 调 格式化到缓冲
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C360(Buffer, 0);  // 调 sub_69C360
  v6 = *this;
  fld_e3 = sub_69C500(*(this + 3));  // this+12 = 技能槽记录次字
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v6 + 24))(this, 14, fld_e3 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v9 = (unsigned int)(480 - fld_e2[8]) >> 1;
  v10 = (unsigned int)(640 - fld_e2[7]) >> 1;
  sub_69A5F0(fld_e2, v10, v9);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v10 + 29, *(uint32_t *)(*(this + 2) + 32) + v9 - 43);  // this+36 = 状态字
  sub_69A5F0((uint32_t *)*(this + 10), v10 + 98, *(uint32_t *)(*(this + 2) + 32) + v9 - 43);  // this+40 = 状态子标志
  *((uint8_t *)this + 57) = 0;
  *((uint8_t *)this + 58) = 0;
  sub_698F90((int)(this + 11), 5000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  return 1;
}



// ------------------------------------------------------------
// 0x639E30 CNRDResponseMemberWindow__vmt38 —— CNRDResponseMemberWindow__vmt38 接受成员动作（423200 系参数）
// ------------------------------------------------------------
int /*thiscall*/ CNRDResponseMemberWindow__vmt38(void *this)  // 函数: CNRDResponseMemberWindow__vmt38 接受成员动作（423200 系参数）
{
  void *pThis; // [esp+0h] [ebp-4h] BYREF

  pThis = this;
  sub_423200(dword_8F7B08, 80);  // 【发送网络包API】
  LOBYTE(pThis) = 1;  // 调 取 16 位值低 8 位
  sub_423290(dword_8F7B08, (int)&pThis, 1);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
  return sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
}



// ------------------------------------------------------------
// 0x639E70 CNRDResponseMemberWindow__vmt3C —— CNRDResponseMemberWindow__vmt3C 拒绝成员动作（423200 系参数）
// ------------------------------------------------------------
int /*thiscall*/ CNRDResponseMemberWindow__vmt3C(void *this)  // 函数: CNRDResponseMemberWindow__vmt3C 拒绝成员动作（423200 系参数）
{
  void *pThis; // [esp+0h] [ebp-4h] BYREF

  pThis = this;
  sub_423200(dword_8F7B08, 80);  // 【发送网络包API】
  LOBYTE(pThis) = 2;  // 调 取 16 位值低 8 位
  sub_423290(dword_8F7B08, (int)&pThis, 1);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
  return sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
}



// ------------------------------------------------------------
// 0x639EB0 CNRDResponseMemberWindow__vmt8 —— CNRDResponseMemberWindow__vmt8 Update（CLICK_BUTTON2 + 699000）
// ------------------------------------------------------------
int /*thiscall*/ CNRDResponseMemberWindow__vmt8(int *this)  // 函数: CNRDResponseMemberWindow__vmt8 Update（CLICK_BUTTON2 + 699000）
{
  int fld_e17; // edi
  int result; // eax
  int fld_e9; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e17 = *(this + 17);  // fld_e17 = this+17
  if ( sub_699000((int)(this + 11)) < fld_e17 )  // 【clock_now(clk)】
  {
    fld_e9 = *(this + 9);  // this+36 = 状态字
    if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
    {
      (*(void (/*thiscall*/ **)(int *))(*this + 56))(this);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
      return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
    else
    {
      result = *(this + 10);  // this+40 = 状态子标志
      if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 若 *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *..
      {
        (*(void (/*thiscall*/ **)(int *))(*this + 60))(this);  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
        return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
      }
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 60))(this);  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  }
  return result;
}



// ------------------------------------------------------------
// 0x639F50 sub_639F50 —— 成员响应清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_639F50(uint32_t *this)  // 函数: 成员响应清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 144, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 21, 22, 23, 21, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = 状态字
  sub_69A840(v3);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 24, 25, 26, 24, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 10) = v5;  // this+40 = 状态子标志
  return sub_69A840(v5);  // 调 sub_69A840
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
int /*thiscall*/ sub_63A030(int this)  // 函数: 强化确认数据（15 行）
{
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  *(uint32_t *)(this + 36) = 0;  // this+144 = pFrameList144
  *(uint8_t *)(this + 104) = 0;  // this+104 = 0
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x63A050 CNRDUpgradeConfirmWindow__vmt8 —— CNRDUpgradeConfirmWindow__vmt8 确认强化（484ED0/422E70/44E8D0 + 54D470 工具窗联动 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDUpgradeConfirmWindow__vmt8(int *this)
{
  int fld_e10; // eax
  int pUpgradeItem; // eax  | +0x0064 → 待强化物品（0x63A4C0: *(this+100)=nArg2；63A520 装配）（CNRDUpgradeConfirmWindow；va=0063A4C0）
  char *v4; // eax
  char *v5; // eax
  int v6; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e10 = *(this + 10);  // this+40 = 状态子标志
  if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )  // 若 *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    pUpgradeItem = sub_484ED0(*(this + 25));  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
    if ( *(uint32_t *)(*(this + 4) + 104) == 10 )  // 若 *(uint32_t *)(*(this + 4) + 104) == 10
    {
      if ( pUpgradeItem == -1 )  // 若 fld_e25 == -1
      {
        v5 = sub_422E70(1658);  // 调 sub_422E70
        sub_44E8D0((char *)*(this + 4), (void *)0x1B, (int)v5, 0);  // 调 对象池借出（按池号取可用对象）
        (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
      }
      else
      {
        sub_54D470(*(this + 25));  // 调 sub_54D470
      }
    }
    else
    {
      v4 = sub_422E70(1657);  // 调 sub_422E70
      sub_44E8D0((char *)*(this + 4), (void *)0x1B, (int)v4, 0);  // 调 对象池借出（按池号取可用对象）
      (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
    v6 = *this;
    *(this + 25) = 0;  // this+100 = 0
    (*(void (/*thiscall*/ **)(int *))(v6 + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x63A140 CNRDUpgradeConfirmWindow__vmt0 —— CNRDUpgradeConfirmWindow__vmt0 构造（165 行：554930 + 484ED0/40FC80 + 4F9F40/43B560 + 4F33A0/4F2CE0/4F2D60/4F2DF0）
// ------------------------------------------------------------
void */*thiscall*/ sub_63A140(uint32_t *this, int pArg2)  // 【CNRDUpgradeConfirmWindow__vmt0】
{
  void *result; // eax
  int v4; // ebx
  int v5; // edi
  int pObj; // eax
  int v7; // eax
  int pUpgradeItem; // eax  | +0x0064 → 待强化物品（0x63A4C0: *(this+100)=nArg2；63A520 装配）（CNRDUpgradeConfirmWindow；va=0063A4C0）
  int pUpgradeItem_; // ebx  | +0x0064 → 待强化物品（0x63A4C0: *(this+100)=nArg2；63A520 装配）（CNRDUpgradeConfirmWindow；va=0063A4C0）
  int *fld_e253; // ecx
  int v11; // edx
  int v12; // eax
  int pUpgradeItem_2; // eax  | +0x0064 → 待强化物品（0x63A4C0: *(this+100)=nArg2；63A520 装配）（CNRDUpgradeConfirmWindow；va=0063A4C0）
  int v14; // eax
  int *fld_e255; // ecx
  int v16; // edx
  int *v17; // eax
  int pUpgradeItem_3; // ebx  | +0x0064 → 待强化物品（0x63A4C0: *(this+100)=nArg2；63A520 装配）（CNRDUpgradeConfirmWindow；va=0063A4C0）
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
  uint32_t pBuf[7]; // [esp+Ch] [ebp-78h] BYREF
  char v37; // [esp+28h] [ebp-5Ch]
  int v38; // [esp+2Ch] [ebp-58h]
  int v39; // [esp+30h] [ebp-54h]
  int v40; // [esp+34h] [ebp-50h]
  int v41; // [esp+38h] [ebp-4Ch]
  uint32_t *pThis_C; // [esp+3Ch] [ebp-48h]
  char Buffer[64]; // [esp+40h] [ebp-44h] BYREF
  int dword_796E502; // [esp+80h] [ebp-4h]
  int v45; // [esp+8Ch] [ebp+8h]
  int v46; // [esp+8Ch] [ebp+8h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  memset(pBuf, 0, 12);  // 调 内存按字节填充
  pBuf[6] = 0;
  v37 = 0;
  v38 = 0;
  v39 = 0;
  v40 = 0;
  result = (void *)sub_554930(pArg2);  // 【IRDPopupWindow__vmt0】
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    result = dword_8F8528;  // dword_8F8528 = 主管理器
    if ( *((uint32_t *)dword_8F8528 + 26) == 10 )  // dword_8F8528 = 主管理器
    {
      if ( *(this + 25) != 0 )  // 若 *(this + 25) != 0
      {
        v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
        v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
        v45 = v4;
        pObj = sub_418DD0(90);  // 调 sub_418DD0
        if ( pObj != 0 )  // 若 pObj != 0
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
            pObj,
            v4 + 12,
            v5 + 9,
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            1065353216,
            1065353216,
            0,
            872415231,
            1333788672,
            1333788672);
        if ( sub_484ED0(*(this + 25)) == -1 )  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
        {
          v7 = *this;
          *(this + 25) = 0;  // this+100 = 0
          return (void *)(*(int (/*thiscall*/ **)(uint32_t *))(v7 + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
        }
        else
        {
          if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 16))(*(this + 25)) + 68) != 0 )  // 调用虚函数（虚表槽 +16）
          {
            pUpgradeItem = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 16))(*(this + 25));  // 调用虚函数（虚表槽 +16）
            sub_40FC80(v4 + 13, v5 + 10, *(uint32_t *)(pUpgradeItem + 68));  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
          }
          pUpgradeItem_ = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 108))(*(this + 25));  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
          fld_e253 = (int *)*(this + 25);
          v11 = *fld_e253;
          pThis_C = *(uint32_t **)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
          v12 = (*(int (/*thiscall*/ **)(int *, int))(v11 + 24))(fld_e253, pUpgradeItem_);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
          v41 = v45 + 43;
          ((void (/*cdecl*/ *)(int, int, int, int))pThis_C[20])(dword_79C0B0, v45 + 43, v5 + 20, v12);  // dword_79C0B0 = 文本/图像绘制对象
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
          pUpgradeItem_2 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 188))(*(this + 25));  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
          v14 = sub_41A5E0(pUpgradeItem_2 + 4);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
          fld_e255 = (int *)*(this + 25);
          v16 = *fld_e255;
          pThis_C = (uint32_t *)v14;
          v17 = (int *)(*(int (/*thiscall*/ **)(int *))(v16 + 172))(fld_e255);  // 调用虚函数（虚表槽 +172）【推断: 朝目标方向按比例取点: p = this + (target −…】
          pUpgradeItem_3 = *(this + 25);  // fld_e256 = this+25
          v32 = *v17;
          v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pUpgradeItem_3 + 16))(pUpgradeItem_3);  // 调用虚函数（虚表槽 +16）
          v20 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pUpgradeItem_3 + 16))(pUpgradeItem_3, *(uint8_t *)(v19 + 24));  // 调用虚函数（虚表槽 +16）
          result = (void *)sub_4F9F40(pBuf, *(uint8_t *)(v20 + 84), pThis_C, v32, this + 12);  // 调 强化数值重算（44B 行 × 三层浮点系数）【推断】
          if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
          {
            v21 = v45 + 12;
            v22 = sub_418DD0(90);  // 调 sub_418DD0
            sub_43B560(v45 + 12, v5 + 87, v22, 1065353216, 1065353216, 0, 872415231, 1333788672, 1333788672);  // 调 绘制转发（vt+128）
            v46 = v45 + 13;
            v23 = sub_418DD0(203);  // 调 sub_418DD0
            sub_40FC80(v46, v5 + 88, v23);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
            v24 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
            pThis_C = this + 12;
            (*(void (/*thiscall*/ **)(int, uint32_t *))(v24 + 72))(dword_79C0B0, this + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
            v34 = v40;
            v25 = (const char *)sub_422E70(180);
            sprintf(Buffer, v25, v34);  // 调 格式化到缓冲
            (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              v41,
              v5 + 98,
              -1,
              Buffer);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
            v26 = sub_418DD0(90);  // 调 sub_418DD0
            sub_43B560(v21, v5 + 126, v26, 1065353216, 1065353216, 0, 872415231, 1333788672, 1333788672);  // 调 绘制转发（vt+128）
            if ( sub_4F33A0(v38) != 0 )  // 若 sub_4F33A0(v38) != 0
            {
              v27 = sub_4F33A0(v38);  // 调 sub_4F33A0
              sub_40FC80(v46, v5 + 127, v27);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
            }
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pThis_C);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
            v35 = v39;
            v33 = sub_4F2CE0(v38);  // 调 sub_4F2CE0
            v28 = (const char *)sub_422E70(1655);
            sprintf(Buffer, v28, v33, v35);  // 调 格式化到缓冲
            v29 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
            v30 = sub_4F2D60(v38);  // 调 sub_4F2D60
            v31 = sub_4F2DF0(v30);  // 调 sub_4F2DF0
            (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v29 + 80))(dword_79C0B0, v41, v5 + 137, v31, Buffer);  // 调用虚函数（虚表槽 +80）
            return (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
          }
        }
      }
    }
    else
    {
      return (void *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x63A4C0 CNRDUpgradeConfirmWindow__vmtC —— CNRDUpgradeConfirmWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDUpgradeConfirmWindow__vmtC(int this, int nArg2, int nArg3)  // 函数: CNRDUpgradeConfirmWindow__vmtC 打开槽（69A5F0）
{
  *(uint32_t *)(this + 100) = nArg2;  // this+100 = nArg2
  *(uint8_t *)(this + 104) = nArg3 == 1;  // this+104 = nArg3 == 1
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (unsigned int)(640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) >> 1,
    (unsigned int)(480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) >> 1);
  return 1;
}



// ------------------------------------------------------------
// 0x63A500 CNRDUpgradeConfirmWindow__vmt10 —— CNRDUpgradeConfirmWindow__vmt10 状态切换槽（44ABE0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDUpgradeConfirmWindow__vmt10(uint8_t *this)  // 函数: CNRDUpgradeConfirmWindow__vmt10 状态切换槽（44ABE0）
{
  int result; // eax

  if ( *(this + 104) == 1 )  // 若 *(this + 104) == 1
    return sub_44ABE0(dword_8F8528, 18);  // 调 选中索引 setter
  return result;
}



// ------------------------------------------------------------
// 0x63A520 sub_63A520 —— 强化确认页绘制（69C3C0/69A5F0/69C340/69C440 + 422E70 + 43C410/69A840，63 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63A520(uint32_t *this)  // 函数: 强化确认页绘制（69C3C0/69A5F0/69C340/69C440 + 422E70 + 43C410/69A840，6…
{
  int v2; // edx
  char *v3; // eax
  uint32_t *pMem; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e92; // eax
  int v8; // edx

  v2 = *this;
  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+36 = 状态字
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(192, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  sub_69C3C0(1);  // 调 sub_69C3C0
  sub_69A5F0((uint32_t *)*(this + 3), 18, 51);  // this+12 = 技能槽记录次字
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  v3 = sub_422E70(1650);  // 调 sub_422E70
  sub_69C360(v3, 0);  // 调 sub_69C360
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e9 = sub_43C410(pMem, *(this + 9), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 10) = fld_e9;  // this+40 = 状态子标志
  sub_69A5F0(fld_e9, 56, 167);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e92 = sub_43C410(pMem2, *(this + 9), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e92 = nullptr;  // fld_e92 = nullptr 空指针
  *(this + 11) = fld_e92;  // this+44 = fld_e92
  sub_69A5F0(fld_e92, 119, 167);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  sub_69A5F0((uint32_t *)*(this + 2), 61, 242);  // this+8 = 技能槽记录首字
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;  // this+60 = 0
  *(this + 16) = 6;  // this+64 = 6
  *(this + 17) = 12;  // this+68 = 12
  *(this + 18) = 0;  // this+72 = 0
  *(this + 19) = 1600;  // this+76 = 1600
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  v8 = *this;
  *(this + 24) = dword_99FCCC;  // this+96 = dword_99FCCC
  *(this + 19) = 173;  // this+76 = 173
  *(this + 15) = 1;  // this+60 = 1
  *(this + 13) = -16777216;  // this+52 = bAuraState
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v8 + 24))(this, 18, 15);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
}



// ------------------------------------------------------------
// 0x63A6D0 sub_63A6D0 —— 强化结果清理（13 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63A6D0(int this)  // 函数: 强化结果清理（13 行）
{
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint8_t *)(this + 36) = 0;  // this+144 = pFrameList144
  return 0;
}



// ------------------------------------------------------------
// 0x63A6E0 sub_63A6E0 —— 强化结果数据（17 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63A6E0(uint32_t *this)  // 函数: 强化结果数据（17 行）
{
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int result; // eax

  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    result = (**fld_e11)(fld_e11, 1);
  *(this + 11) = 0;  // this+44 = 0
  return result;
}



// ------------------------------------------------------------
// 0x63A700 CNRDUpgradeResultWindow__vmt8 —— CNRDUpgradeResultWindow__vmt8 Update（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDUpgradeResultWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x63A740 sub_63A740 —— 强化结果页绘制（69A5F0，31 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_63A740(uint32_t *this)  // 函数: 强化结果页绘制（69A5F0，31 行）
{
  int v2; // edi
  int v3; // eax

  if ( *((uint8_t *)this + 36) == 3 )  // this+36 = 状态字
  {
    if ( dword_9B9468 != nullptr )  // 若 dword_9B9468 非空
      v2 = (dword_9B946C - (int)dword_9B9468) >> 3;
    else
      v2 = 0;
    v3 = *this;
    *(this + 25) = 0;  // this+100 = 0
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v3 + 24))(this, 18, 3 * v2 + 5);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
    return sub_69A5F0(
             (uint32_t *)*(this + 11),
             *(uint32_t *)(*(this + 2) + 20) + 88,  // this+8 = 技能槽记录首字
             *(uint32_t *)(*(this + 2) + 24) + 39 * (v2 + 1));  // this+8 = 技能槽记录首字
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 18, 8);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
    return sub_69A5F0((uint32_t *)*(this + 11), *(uint32_t *)(*(this + 2) + 20) + 88, *(uint32_t *)(*(this + 2) + 24) + 78);  // this+8 = 技能槽记录首字
  }
}



// ------------------------------------------------------------
// 0x63A7C0 sub_63A7C0 —— 强化结果公共件（30 行）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_63A7C0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // 函数: 强化结果公共件（30 行）
{
  uint32_t *result; // eax
  uint32_t *uArg22; // edx

  result = uArg2;
  if ( uArg2 != nullptr )  // 若 uArg2 非空
  {
    uArg22 = uArg2;
    result = uArg1;
    do
    {
      if ( result != nullptr )  // 若 result 非空
      {
        *result = *pArg3;  // *result 写入 *pArg3
        result[1] = pArg3[1];  // result[1] 写入 pArg3[1]
      }
      result += 2;
      uArg22 = (uint32_t *)((char *)uArg22 - 1);
    }
    while ( uArg22 != nullptr );  // 当 uArg22 非空 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x63A7F0 CNRDUpgradeResultWindow__vmt0 —— CNRDUpgradeResultWindow__vmt0 构造（144 行：554930 + 63A740 + 4F33A0/4F2CE0/4F2D60/4F2DF0 + 484ED0/40FC80）
// ------------------------------------------------------------
void */*userpurge*/ sub_63A7F0@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>, int pArg3)
{
  void *result; // eax
  char v5; // al
  int v6; // edi
  int v7; // ebx
  unsigned int v8; // eax
  bool v9; // zf
  int pObj; // eax
  unsigned int v11; // ecx
  int i; // ebx
  int v13; // edi
  int pObj3; // eax
  int pObj4; // eax
  const char *v16; // eax
  int v17; // eax
  int v18; // eax
  int pObj5; // eax
  int v20; // eax
  int v21; // eax
  int v22; // edi
  int v23; // eax
  int v24; // eax
  int v25; // [esp-Ch] [ebp-68h]
  int v27; // [esp+Ch] [ebp-50h]
  int v28; // [esp+10h] [ebp-4Ch]
  int pObj2; // [esp+10h] [ebp-4Ch]
  int v30; // [esp+14h] [ebp-48h]
  char Buffer[64]; // [esp+18h] [ebp-44h] BYREF
  int dword_796E502; // [esp+58h] [ebp-4h]
  int v33; // [esp+64h] [ebp+8h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  sub_554930(pArg3);  // 【IRDPopupWindow__vmt0】
  result = (void *)sub_63A740(pDwArg1);  // 调 强化结果页绘制（69A5F0，31 行）
  if ( pArg3 == pDwArg1[2] )  // 若 pArg3 == pDwArg1[2]
  {
    v5 = *((uint8_t *)pDwArg1 + 36);
    v6 = *(uint32_t *)(pArg3 + 20);  // v6 = pArg3+20
    v7 = *(uint32_t *)(pArg3 + 24);  // v7 = pArg3+24
    v33 = v6;
    if ( v5 != 0 )  // 若 v5 != 0
    {
      if ( v5 == 1 || (v9 = v5 == 2, v8 = 214, v9) )  // 若 v5 == 1 || (v9 = v5 == 2, v8 = 214, v9)
        v8 = 213;
    }
    else
    {
      v8 = 212;
    }
    pObj = sub_418DD0((uint32_t *)pDwArg1[10], v8);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        pObj,
        v6 + dword_73DFFC[*((uint8_t *)pDwArg1 + 36)],
        v7 + 13,
        dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
    if ( *((uint8_t *)pDwArg1 + 36) == 3 )  // 若 *((uint8_t *)pDwArg1 + 36) == 3
    {
      v11 = 0;
      v30 = 0;
      for ( i = v7 + 38; ; i += 39 )  // 循环：i = v7 + 38; ; i += 39
      {
        result = dword_9B9468;
        if ( dword_9B9468 == nullptr || v11 >= (dword_9B946C - (int)dword_9B9468) >> 3 )  // 若 dword_9B9468 == nullptr || v11 >= (dword_9B946C - (int)dword_9..
          break;
        v13 = *((uint32_t *)dword_9B9468 + 2 * v11);
        v27 = *((uint32_t *)dword_9B9468 + 2 * v11 + 1);
        pObj3 = sub_418DD0((uint32_t *)pDwArg1[10], 0x5Au);  // 调 sub_418DD0
        if ( pObj3 != 0 )  // 若 pObj3 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 调用虚函数（虚表槽 +128）
            pObj3,
            v33 + 12,
            i - 1,
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            1065353216,
            1065353216,
            0,
            872415231,
            1333788672,
            1333788672);
        if ( sub_4F33A0(v13) != 0 )  // 若 sub_4F33A0(v13) != 0
        {
          pObj4 = sub_4F33A0(v13);  // 调 sub_4F33A0
          if ( pObj4 != 0 )  // 若 pObj4 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v33 + 13, i, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        }
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pDwArg1 + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
        v25 = sub_4F2CE0(v13);  // 调 sub_4F2CE0
        v16 = (const char *)sub_422E70(1655);
        sprintf(Buffer, v16, v25, v27);  // 调 格式化到缓冲
        v28 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
        v17 = sub_4F2D60(v13);  // 调 sub_4F2D60
        v18 = sub_4F2DF0(v17);  // 调 sub_4F2DF0
        (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v28 + 80))(dword_79C0B0, v33 + 43, i + 10, v18, Buffer);  // 调用虚函数（虚表槽 +80）
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
        v11 = ++v30;
      }
    }
    else
    {
      pObj5 = sub_418DD0((uint32_t *)pDwArg1[10], 0x5Au);  // 调 sub_418DD0
      if ( pObj5 != 0 )  // 若 pObj5 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(  // 调用虚函数（虚表槽 +128）
          pObj5,
          v6 + 12,
          v7 + 37,
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          1065353216,
          1065353216,
          0,
          872415231,
          1333788672,
          1333788672);
      if ( sub_484ED0((int *)dword_8F852C, pDwArg1[25]) == -1 )  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
      {
        v20 = *pDwArg1;
        pDwArg1[25] = 0;
        return (void *)(*(int (/*thiscall*/ **)(int *))(v20 + 32))(pDwArg1);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
      }
      else
      {
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[25] + 16))(pDwArg1[25], nArg2) + 68) != 0 )  // 调用虚函数（虚表槽 +16）
        {
          v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[25] + 16))(pDwArg1[25]);  // 调用虚函数（虚表槽 +16）
          sub_40FC80((void *)dword_79C0B0, v6 + 13, v7 + 38, *(uint32_t *)(v21 + 68));  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
        }
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pDwArg1 + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
        v22 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
        pObj2 = pDwArg1[25];
        v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 108))(pObj2);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
        v24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 24))(pObj2, v23);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
        (*(void (/*cdecl*/ **)(int, int, int, int))(v22 + 80))(dword_79C0B0, v33 + 43, v7 + 48, v24);  // 调用虚函数（虚表槽 +80）
        return (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x63AAD0 sub_63AAD0 —— 强化结果清理 2（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_63AAD0(int this)  // 函数: 强化结果清理 2（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *fld_28; // eax
  int result; // eax

  *(uint32_t *)(this + 40) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+40 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_28 = sub_43C410(pMem, *(uint32_t *)(this + 40), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_28 = nullptr;  // fld_28 = nullptr 空指针
  *(uint32_t *)(this + 44) = fld_28;  // this+44 = fld_28
  result = sub_69A840(fld_28);  // 调 sub_69A840
  *(uint8_t *)(this + 48) = 0;  // this+48 = 0
  *(uint8_t *)(this + 49) = 0;  // this+49 = 0
  *(uint8_t *)(this + 50) = 0;  // this+50 = 0
  *(uint8_t *)(this + 51) = 0;  // this+51 = 0
  *(uint32_t *)(this + 60) = 0;  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint32_t *)(this + 80) = 0;  // this+80 = 0
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 96) = 0;  // this+384 = 动画件名 SSO 容量判据
  *(uint32_t *)(this + 64) = 6;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 68) = 12;  // this+68 = 12
  *(uint32_t *)(this + 76) = 1600;  // this+76 = 1600
  *(uint32_t *)(this + 96) = dword_99FCCC;  // this+384 = 动画件名 SSO 容量判据
  *(uint32_t *)(this + 76) = 175;  // this+76 = 175
  *(uint32_t *)(this + 60) = 1;  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 52) = -16777216;  // this+52 = -16777216
  return result;
}



// ------------------------------------------------------------
// 0x63ABB0 sub_63ABB0 —— 强化结果文本（4015C0/401740）
// ------------------------------------------------------------
void /*noreturn*/ sub_63ABB0()  // 函数: 强化结果文本（4015C0/401740）
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
  sub_401740(v1);  // 调 std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消…
  pExceptionObject = &std::length_error::`vftable';  // vftable 复位
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x63AC20 CNRDUpgradeResultWindow__vmtC —— CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_SUCCESS/STRENGTHEN_FAIL/STRENGTHEN_ZERO/EQUIP_BROKEN 事件（432EA0 + 54D0C0 工具窗动画 + 484ED0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDUpgradeResultWindow__vmtC(int this, int nArg2, char pszArg3)  // 函数: CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_SUCCESS/STRENGTHEN_FAIL/STRENGTHEN_ZERO/EQUIP_BROKEN 事件（432EA0 + 54D0C0 工具窗动画 + 484ED0）
{
  char bResultCode; // al  | +0x0024 → 强化结果码（CNRDUpgradeResultWindow；va=0063AC20）
  char *v6; // eax
  int pResultItem; // eax  | +0x0064 → 结果物品（CNRDUpgradeResultWindow；va=0063AC20）

  *(uint8_t *)(this + 36) = pszArg3;  // this+144 = pFrameList144
  if ( pszArg3 == 3 )  // 若 pszArg3 == 3
  {
    *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  }
  else
  {
    if ( nArg2 == 0 )  // 若 nArg2 == 0
      return 0;
    *(uint32_t *)(this + 100) = nArg2;  // this+100 = nArg2
    if ( dword_9B9468 != nullptr )  // 若 dword_9B9468 非空
      j__free(dword_9B9468);  // 调 堆释放
    dword_9B9468 = nullptr;  // dword_9B9468 = nullptr 空指针
    dword_9B946C = 0;
    dword_9B9470 = 0;
  }
  sub_63A740((uint32_t *)this);  // 调 强化结果页绘制（69A5F0，31 行）
  bResultCode = *(uint8_t *)(this + 36);  // this+144 = pFrameList144
  if ( bResultCode == 0 )  // 若 fld_24 == 0
  {
    sub_432EA0("STRENGTHEN_SUCCESS", -1, 0, 0);  // 调 音效播放包装（非空判定）
    v6 = sub_422E70(1669);  // 调 sub_422E70
LABEL_17:
    sub_54D0C0(v6);  // 调 工具窗动画切换（69C340/69C360/69C500）——强化结果窗 0x63AC20 复用
    goto LABEL_18;  // 跳转 LABEL_18
  }
  if ( bResultCode != 1 && bResultCode != 2 )  // 若 fld_24 != 1 && fld_24 != 2
  {
    sub_432EA0("EQUIP_BROKEN", -1, 0, 0);  // 调 音效播放包装（非空判定）
    v6 = sub_422E70(1672);  // 调 sub_422E70
    goto LABEL_17;  // 跳转 LABEL_17
  }
  if ( sub_484ED0(*(uint32_t *)(this + 100)) != -1 )  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
  {
    pResultItem = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 100) + 188))(*(uint32_t *)(this + 100));  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
    if ( sub_41A5E0(pResultItem + 4) != 0 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    {
      sub_432EA0("STRENGTHEN_FAIL", -1, 0, 0);  // 调 音效播放包装（非空判定）
      v6 = sub_422E70(1670);  // 调 sub_422E70
    }
    else
    {
      sub_432EA0("STRENGTHEN_ZERO", -1, 0, 0);  // 调 音效播放包装（非空判定）
      v6 = sub_422E70(1671);  // 调 sub_422E70
    }
    goto LABEL_17;  // 跳转 LABEL_17
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
void /*thiscall*/ sub_63AD80(int this, int nArg2, unsigned int uArg3, int pArg4)  // 函数: 强化结果动画辅助（44BD30/5E51F0/41FEB0/44BD00 + 63A7C0，122 行）
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
  v28[0] = *(void **)pArg4;  // v28[0] 写入 *(void **)pArg4
  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;
  else
    fld_C = 0;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
    else
      fld_8 = 0;
    if ( 0x1FFFFFFF - fld_8 < uArg3 )  // 若 0x1FFFFFFF - fld_8 < uArg3
      sub_63ABB0(this);  // 调 强化结果文本（4015C0/401740）
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )  // 若 fld_C >= uArg3 + fld_82
    {
      fld_83 = *(uint32_t *)(this + 8);  // fld_83 = this+8
      v20 = (fld_83 - nArg2) >> 3 < uArg3;
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;
      if ( v20 )  // 若 v20
      {
        sub_44BD30(nArg2, fld_83, nArg2 + v21);  // 调 8 字节元素正向拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 3);
        fld_85 = *(uint32_t *)(this + 8);  // fld_85 = this+8
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);  // 调 sub_5E51F0
        fld_86 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;  // this+8 = fld_86
        sub_41FEB0(nArg2, fld_86 - v30, v28);  // 调 8B 元素区间拷贝
      }
      else
      {
        v23 = fld_83 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);  // 调 8 字节元素正向拷贝
        sub_44BD00(nArg2, v23, fld_832);  // 调 8 字节元素反向拷贝
        sub_41FEB0(nArg2, nArg2 + v30, v28);  // 调 8B 元素区间拷贝
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )  // 若 0x1FFFFFFF - (fld_C >> 1) >= fld_C
        v11 = (fld_C >> 1) + fld_C;
      else
        v11 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 != 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
      else
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )  // 若 v11 < uArg3 + fld_87
      {
        if ( fld_4 != 0 )  // 若 fld_4 != 0
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
        else
          fld_88 = 0;
        v11 = uArg3 + fld_88;
      }
      v31 = 8 * v11;
      pMem = (char *)operator new(8 * v11);
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = this+4
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, nArg2, pMem);  // 调 8 字节元素正向拷贝
      sub_63A7C0(v32, uArg3, v28);  // 调 强化结果公共件（30 行）
      sub_44BD30(nArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);  // 调 8 字节元素正向拷贝
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = this+4
      if ( fld_43 != 0 )  // 若 fld_43 != 0
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;
      else
        fld_89 = 0;
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )  // 若 fld_43 != 0
        j__free(*(void **)(this + 4));  // 调 堆释放
      *(uint32_t *)(this + 12) = &pMem[v31];  // this+12 = &pMem[v31]
      *(uint32_t *)(this + 8) = &pMem[8 * v17];  // this+8 = &pMem[8 * v17]
      *(uint32_t *)(this + 4) = pMem;  // this+4 = pMem
    }
  }
}


// ------------------------------------------------------------
// 0x63AFD0 sub_63AFD0 —— 强化结果动画中层（63A7C0 + 63AD80）
// ------------------------------------------------------------
void /*thiscall*/ sub_63AFD0(int this, uint32_t *uArg2)  // 函数: 强化结果动画中层（63A7C0 + 63AD80）
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
  else
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 3 )  // 若 fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 3
  {
    fld_82 = *(uint32_t **)(this + 8);
    sub_63A7C0(fld_82, (uint32_t *)1, uArg2);  // 调 强化结果公共件（30 行）
    *(uint32_t *)(this + 8) = fld_82 + 2;  // this+8 = fld_82 + 2
  }
  else
  {
    sub_63AD80(this, *(char **)(this + 8), 1u, (int)uArg2);  // 调 强化结果动画辅助（44BD30/5E51F0/41FEB0/44BD00 + 63A7C0，122 行）
  }
}



// ------------------------------------------------------------
// 0x63B040 sub_63B040 —— 强化结果动画转发（63AFD0）
// ------------------------------------------------------------
void /*cdecl*/ sub_63B040(int nArg1, int nArg2)  // 函数: 强化结果动画转发（63AFD0）
{
  uint32_t v2[2]; // [esp+0h] [ebp-8h] BYREF

  v2[1] = nArg2;
  v2[0] = nArg1;
  sub_63AFD0((int)&unk_9B9464, v2);  // 调 强化结果动画中层（63A7C0 + 63AD80）
}



// ============================================================
// 【分区 24】物品盒/金库 CNRDItemBoxWindow（0x63B070-0x63B900）
// vmt8 Update（111 行：486F40 格子 + 69A500）、vmtC 打开（44AB50/44BBA0）。
// ============================================================
// ------------------------------------------------------------
// 0x63B070 sub_63B070 —— 物品盒数据（20 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63B070(int this)  // 函数: 物品盒数据（20 行）
{
  *(uint32_t *)(this + 36) = 0;  // this+144 = pFrameList144
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  *(uint32_t *)(this + 56) = 0;  // this+56 = 0
  *(uint32_t *)(this + 60) = 0;  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 52) = 0;  // this+52 = 0
  *(uint8_t *)(this + 81) = 0;  // this+324 = 购买上下文 id（0x550480: dword
  *(uint8_t *)(this + 82) = 0;  // this+82 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x63B0A0 sub_63B0A0 —— 物品盒数据 2（27 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63B0A0(uint32_t *this)  // 函数: 物品盒数据 2（27 行）
{
  int (/*thiscall*/ ***fld_e14)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e15)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e16)(uint32_t, int); // ecx

  fld_e14 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  if ( fld_e14 != nullptr )  // 若 fld_e14 非空
    result = (**fld_e14)(fld_e14, 1);
  fld_e15 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  *(this + 14) = 0;  // this+56 = 0
  if ( fld_e15 != nullptr )  // 若 fld_e15 非空
    result = (**fld_e15)(fld_e15, 1);
  fld_e16 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 16);
  *(this + 15) = 0;  // this+60 = 0
  if ( fld_e16 != nullptr )  // 若 fld_e16 非空
    result = (**fld_e16)(fld_e16, 1);
  *(this + 16) = 0;  // this+64 = 0
  return result;
}



// ------------------------------------------------------------
// 0x63B0E0 sub_63B0E0 —— 物品盒数据 3（17 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_63B0E0(uint32_t *this)  // 函数: 物品盒数据 3（17 行）
{
  int fld_e14; // edx

  fld_e14 = *(this + 14);  // fld_e14 = this+14
  *(this + 13) = 1;  // this+52 = bAuraState
  *(uint8_t *)(fld_e14 + 17) = 0;  // fld_e14+17 = 0
  *(uint8_t *)(*(this + 15) + 17) = 0;
  *(uint8_t *)(*(this + 16) + 17) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x63B100 sub_63B100 —— 物品盒数据 4（17 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_63B100(uint32_t *this)  // 函数: 物品盒数据 4（17 行）
{
  int fld_e14; // edx

  fld_e14 = *(this + 14);  // fld_e14 = this+14
  *(this + 13) = 0;  // this+52 = bAuraState
  *(uint8_t *)(fld_e14 + 17) = 1;  // fld_e14+17 = 1
  *(uint8_t *)(*(this + 15) + 17) = 1;
  *(uint8_t *)(*(this + 16) + 17) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x63B120 CNRDItemBoxWindow__vmt38 —— CNRDItemBoxWindow__vmt38 确认动作槽（422E70/44E8D0 + 41A5E0，78 行）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemBoxWindow__vmt38(uint32_t *this)  // 函数: CNRDItemBoxWindow__vmt38 确认动作槽（422E70/44E8D0 + 41A5E0，78 行）
{
  uint32_t *fld_e4; // edi
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int pObj; // esi
  char *v7; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax

  fld_e4 = (uint32_t *)*(this + 4);
  if ( fld_e4[626] != 2 )  // 若 fld_e4[626] != 2
    return 0;
  v3 = fld_e4[627];
  if ( v3 != 3 && v3 != 4 )  // 若 v3 != 3 && v3 != 4
    return 0;
  v4 = fld_e4[629];
  if ( v4 >= *((uint32_t *)dword_8F852C + 2) )  // dword_8F852C = UI 管理器全局
    return 0;
  v5 = *((uint32_t *)dword_8F852C + 3);  // dword_8F852C = UI 管理器全局
  pObj = *(uint32_t *)(v5 + 4 * v4);
  if ( pObj == 0
    || *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj + 16))(*(uint32_t *)(v5 + 4 * v4)) + 4) != fld_e4[628] )  // 调用虚函数（虚表槽 +16）
  {
    return 0;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 20))(pObj, 2) == 0 )  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
  {
    v7 = sub_422E70(1690);  // 调 sub_422E70
LABEL_9:
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v7, 0);  // 调 对象池借出（按池号取可用对象）
    return 0;
  }
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 188))(pObj);  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
  v10 = sub_41A5E0(v9 + 32);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj);  // 调用虚函数（虚表槽 +172）【推断: 朝目标方向按比例取点: p = this + (target −…】
  if ( v10 != sub_41A5E0(v11 + 18) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v7 = sub_422E70(1691);  // 调 sub_422E70
    goto LABEL_9;  // 跳转 LABEL_9
  }
  if ( *(this + 9) == 1 )  // this+36 = 状态字
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 32) == 1 )  // 调用虚函数（虚表槽 +16）
    {
      v7 = sub_422E70(1694);  // 调 sub_422E70
      goto LABEL_9;  // 跳转 LABEL_9
    }
    if ( *(this + 9) == 1 )  // this+36 = 状态字
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 28) != 3 )  // 调用虚函数（虚表槽 +16）
      {
        v7 = sub_422E70(1697);  // 调 sub_422E70
        goto LABEL_9;  // 跳转 LABEL_9
      }
      if ( *(this + 9) == 1 )  // this+36 = 状态字
      {
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 188))(pObj);  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
        if ( sub_41A5E0(v12 + 46) >= 7 )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        {
          v7 = sub_422E70(1696);  // 调 sub_422E70
          goto LABEL_9;  // 跳转 LABEL_9
        }
      }
    }
  }
  *(this + 12) = pObj;  // this+48 = pObj
  return 1;
}



// ------------------------------------------------------------
// 0x63B260 CNRDItemBoxWindow__vmt10 —— CNRDItemBoxWindow__vmt10 状态切换槽（44E850）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemBoxWindow__vmt10(uint32_t **this)  // 函数: CNRDItemBoxWindow__vmt10 状态切换槽（44E850）
{
  char result; // al

  result = dword_9B88D0;
  if ( dword_9B88D0 != 0 && dword_795378 == 8 )  // 若 dword_9B88D0 != 0 && dword_795378 == 8
    return sub_44E850(*(this + 4), 26);  // 调 按池号批量回收活动对象
  return result;
}



// ------------------------------------------------------------
// 0x63B280 sub_63B280 —— 物品盒条目操作（53 行：484ED0/484E80/44E8D0/41A5E0/4F8F40）
// ------------------------------------------------------------
int /*thiscall*/ sub_63B280(int this)  // 函数: 物品盒条目操作（53 行：484ED0/484E80/44E8D0/41A5E0/4F8F40）
{
  int fld_30; // edi
  int fld_24; // eax
  int v4; // eax
  int v5; // eax
  int v6; // ebx
  char *v7; // eax
  int fld_302; // eax
  int pObj2; // edi
  int v10; // eax
  unsigned int v11; // edi
  int pObj; // ecx
  char v14; // [esp-8h] [ebp-14h]
  char v15; // [esp-4h] [ebp-10h]

  fld_30 = sub_484ED0(*(uint32_t *)(this + 48));  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
  fld_24 = *(uint32_t *)(this + 36);  // this+144 = pFrameList144
  if ( fld_24 != 0 )  // 若 fld_24 != 0
    v4 = fld_24 != 1 ? 0 : 0xE;
  else
    v4 = 15;
  v5 = sub_484E80(v4);  // 调 按类型查找下标（同一匹配规则，未命中 -1）
  v6 = v5;
  if ( fld_30 < 0 )  // 若 fld_30 < 0
  {
    v7 = sub_422E70(1695);  // 调 sub_422E70
LABEL_14:
    sub_44E8D0(*(char **)(this + 16), (void *)0x1B, (int)v7, 0);  // 调 对象池借出（按池号取可用对象）
    return 0;
  }
  if ( v5 < 0
    || *(uint32_t *)(this + 36) == 1  // this+144 = pFrameList144
    && ((fld_302 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 48) + 188))(*(uint32_t *)(this + 48)),  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
         v15 = sub_41A5E0(fld_302 + 46),  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
         pObj2 = *(uint32_t *)(this + 48),
         v14 = *(uint8_t *)((*(int (**)(void))(*(uint32_t *)pObj2 + 16))() + 24),  // 调用虚函数（虚表槽 +16）
         v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2),  // 调用虚函数（虚表槽 +16）
         ((v11 = sub_4F8F40(*(uint8_t *)(v10 + 84), v14, v15)) & 0x80000000) != 0)  // 调 等级分段查表（1..99 × 5 档系数）【推断】
     || (v6 >= *((uint32_t *)dword_8F852C + 2) ? (pObj = 0) : (pObj = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v6)),  // dword_8F852C = UI 管理器全局
         (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj) < v11)) )  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  {
    v7 = sub_422E70(1661);  // 调 sub_422E70
    goto LABEL_14;  // 跳转 LABEL_14
  }
  return 1;
}



// ------------------------------------------------------------
// 0x63B360 sub_63B360 —— 物品盒条目操作 2（63B280 + 698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_63B360(char **this)  // 函数: 物品盒条目操作 2（63B280 + 698F90）
{
  char *v2; // eax
  char result; // al

  if ( *(this + 10) != nullptr )  // 若 *(this + 10) != nullptr
  {
    v2 = sub_422E70(1656);  // 调 sub_422E70
    return sub_44E8D0(*(this + 4), (void *)0x1B, (int)v2, 0);  // 调 对象池借出（按池号取可用对象）
  }
  else if ( sub_63B280((int)this) == 1 )  // 调 物品盒条目操作（53 行：484ED0/484E80/44E8D0/41A5E0/4F8F40）
  {
    *((uint8_t *)this + 81) = 0;
    *((uint8_t *)this + 82) = 0;
    result = sub_698F90((int)(this + 17), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(this + 10) = (char *)1;  // this+40 = 状态子标志
  }
  else
  {
    return (*((int (/*thiscall*/ **)(char **))*this + 8))(this);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
  }
  return result;
}



// ------------------------------------------------------------
// 0x63B3C0 sub_63B3C0 —— 物品盒数据 5（32 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63B3C0(uint32_t *this)  // 函数: 物品盒数据 5（32 行）
{
  int result; // eax
  int fld_e14; // eax

  result = *(this + 9);  // this+36 = 状态字
  if ( result != 0 )  // 若 result != 0
  {
    if ( result == 1 )  // 若 result == 1
    {
      result = *(this + 14);  // result = this+14
      *(uint8_t *)(result + 17) = 1;  // result+17 = 1
    }
  }
  else
  {
    fld_e14 = *(this + 14);  // fld_e14 = this+14
    *(this + 10) = 0;  // this+40 = 状态子标志
    *(this + 13) = 0;  // this+52 = bAuraState
    *(uint8_t *)(fld_e14 + 17) = 1;  // fld_e14+17 = 1
    result = *(this + 15);  // result = this+15
    *(uint8_t *)(result + 17) = 1;  // result+17 = 1
    *(uint8_t *)(*(this + 16) + 17) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x63B400 sub_63B400 —— 物品盒数据 6（20 行）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_63B400(uint32_t *this)  // 函数: 物品盒数据 6（20 行）
{
  int fld_e2; // eax
  int v2; // ecx
  RECT rc; // [esp+4h] [ebp-10h] BYREF

  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  v2 = *(uint32_t *)(fld_e2 + 24);  // v2 = fld_e2+24
  rc.left = *(uint32_t *)(fld_e2 + 20) + 42;
  rc.right = rc.left + 55;
  rc.top = v2 + 40;
  rc.bottom = v2 + 95;
  return PtInRect(&rc, pt);
}



// ------------------------------------------------------------
// 0x63B450 CNRDItemBoxWindow__vmtC —— CNRDItemBoxWindow__vmtC 打开槽（44AB50/44BBA0 页切换显示）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemBoxWindow__vmtC(int this, int nArg2, int nArg3)  // 函数: CNRDItemBoxWindow__vmtC 打开槽（44AB50/44BBA0 页切换显示）
{
  int pBtnConfirm; // edx  | +0x003C → 确认按钮（CNRDItemBoxWindow；va=0063B4D0）
  int result; // eax
  int pBtnAction; // edx  | +0x0038 → 主操作按钮（CNRDItemBoxWindow；va=0063B4D0）

  sub_44AB50(*(uint32_t **)(this + 16), 0, 12);  // 调 页签切换
  sub_44BBA0(*(uint32_t **)(this + 16), 0, 0);  // 调 窗口显示切换（WINDOW_SHOW 音效）
  *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 16) + 56) + 56) = 0;
  pBtnConfirm = *(uint32_t *)(this + 60);  // this+240 = 基类时刻同步参数 B
  result = 1;
  if ( nArg3 != 0 )  // 若 nArg3 != 0
  {
    *(uint8_t *)(pBtnConfirm + 16) = 0;  // fld_3C+16 = 0
    *(uint8_t *)(*(uint32_t *)(this + 64) + 16) = 1;  // this+256 = 基类四元组字节槽 3
    *(uint32_t *)(this + 36) = 1;  // this+144 = pFrameList144
  }
  else
  {
    *(uint8_t *)(pBtnConfirm + 16) = 1;  // fld_3C+16 = 1
    *(uint8_t *)(*(uint32_t *)(this + 64) + 16) = 0;  // this+256 = 基类四元组字节槽 3
    *(uint32_t *)(this + 36) = 0;  // this+144 = pFrameList144
  }
  pBtnAction = *(uint32_t *)(this + 56);  // fld_38 = this+56
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint32_t *)(this + 52) = 0;  // this+52 = 0
  *(uint8_t *)(pBtnAction + 17) = 1;  // fld_38+17 = 1
  *(uint8_t *)(*(uint32_t *)(this + 60) + 17) = 1;  // this+240 = 基类时刻同步参数 B
  *(uint8_t *)(*(uint32_t *)(this + 64) + 17) = 1;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  return result;
}



// ------------------------------------------------------------
// 0x63B4D0 CNRDItemBoxWindow__vmt8 —— CNRDItemBoxWindow__vmt8 Update（111 行：CLICK_BUTTON2 + 486F40 格子 + 69A500 + 63B400）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemBoxWindow__vmt8(int this)  // 函数: CNRDItemBoxWindow__vmt8 Update（111 行：CLICK_BUTTON2 + 486F40 格子 + 69A500 + 63B400）
{
  int pBtnAction; // eax  | +0x0038 → 主操作按钮（CNRDItemBoxWindow；va=0063B4D0）
  int nSubState; // edi  | +0x0030 → 子状态/校验结果（0x63B4D0: 由 63B280 返回 1 置 2；非 1 则直接关窗）（CNRDItemBoxWindow；va=0063B4D0）
  int nSelItemSlot; // eax  | +0x0024 → 选中物品槽 id（0x63B4D0: fld_24=*(this+36)；0→帧 15、1→帧 0xE 换算图标）（CNRDItemBoxWindow；va=0063B4D0）
  int v5; // eax
  int v6; // eax
  char *v7; // eax
  int pBtnConfirm; // eax  | +0x003C → 确认按钮（CNRDItemBoxWindow；va=0063B4D0）
  int pBtnCancel; // eax  | +0x0040 → 取消按钮（CNRDItemBoxWindow；va=0063B4D0）
  int nSubState_; // ecx  | +0x0030 → 子状态/校验结果（0x63B4D0: 由 63B280 返回 1 置 2；非 1 则直接关窗）（CNRDItemBoxWindow；va=0063B4D0）
  int nSelItemSlot_; // eax  | +0x0024 → 选中物品槽 id（0x63B4D0: fld_24=*(this+36)；0→帧 15、1→帧 0xE 换算图标）（CNRDItemBoxWindow；va=0063B4D0）
  int v12; // eax
  BOOL v13; // eax
  int pHostCtrl; // ecx  | +0x0008 → 宿主控件（CNRDItemBoxWindow；va=0063B4D0）
  int fld_303; // eax

  pBtnAction = *(uint32_t *)(this + 56);  // fld_38 = this+56
  if ( *(uint8_t *)(pBtnAction + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnAction + 12) )  // 若 *(uint8_t *)(fld_38 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  if ( *(uint32_t *)(this + 40) == 1 && (unsigned int)sub_699000(this + 68) >= 0x3E8 )  // 【clock_now(clk)】
  {
    if ( sub_63B280(this) == 1 )  // 调 物品盒条目操作（53 行：484ED0/484E80/44E8D0/41A5E0/4F8F40）
    {
      nSubState = sub_484ED0(*(uint32_t *)(this + 48));  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
      nSelItemSlot = *(uint32_t *)(this + 36);  // this+144 = pFrameList144
      if ( nSelItemSlot != 0 )  // 若 fld_24 != 0
        v5 = nSelItemSlot != 1 ? 0 : 0xE;
      else
        v5 = 15;
      v6 = sub_484E80(v5);  // 调 按类型查找下标（同一匹配规则，未命中 -1）
      if ( (uint8_t)sub_486F40(nSubState, v6) == 0 )  // 调 请求 op 84
      {
        v7 = sub_422E70(1659);  // 调 sub_422E70
        sub_44E8D0(*(char **)(this + 16), (void *)0x1B, (int)v7, 0);  // 调 对象池借出（按池号取可用对象）
      }
      *(uint32_t *)(this + 40) = 2;  // this+40 = 2
    }
    else
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
  }
  if ( *(uint32_t *)(this + 52) != 0 )  // 若 *(uint32_t *)(this + 52) != 0
    goto LABEL_37;  // 跳转 LABEL_37
  pBtnConfirm = *(uint32_t *)(this + 60);  // this+240 = 基类时刻同步参数 B
  if ( *(uint8_t *)(pBtnConfirm + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnConfirm + 12)  // 若 *(uint8_t *)(fld_3C + 17) != 0 && dword_79BE34 == *(uint32_t *..
    || *(uint8_t *)((pBtnCancel = *(uint32_t *)(this + 64)) + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnCancel + 12) )  // this+256 = 基类四元组字节槽 3
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    nSubState_ = *(uint32_t *)(this + 48);  // fld_302 = this+48
    if ( nSubState_ != 0 )  // 若 fld_302 != 0
    {
      nSelItemSlot_ = *(uint32_t *)(this + 36);  // this+144 = pFrameList144
      if ( nSelItemSlot_ != 0 )  // 若 fld_242 != 0
        v12 = nSelItemSlot_ != 1 ? 0 : 0xE;
      else
        v12 = 15;
      sub_44E8D0(*(char **)(this + 16), (void *)0x39, nSubState_, v12);  // 调 对象池借出（按池号取可用对象）
    }
  }
  v13 = sub_63B400((uint32_t *)this);  // 调 物品盒数据 6（20 行）
  pHostCtrl = *(uint32_t *)(this + 8);  // fld_8 = this+8
  if ( v13 )  // 若 v13
  {
    if ( (uint8_t)sub_69A500(pHostCtrl) == 1 && *(uint32_t *)(*(uint32_t *)(this + 16) + 2504) == 2 )  // 若 (uint8_t)sub_69A500(fld_8) == 1 && *(uint32_t *)(*(uint32_t *)..
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 56))(this);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
  }
  else if ( (uint8_t)sub_69A500(pHostCtrl) == 1 )  // 否则若 (uint8_t)sub_69A500(fld_8) == 1
  {
    fld_303 = *(uint32_t *)(this + 48);  // fld_303 = this+48
    if ( fld_303 == 0 )  // 若 fld_303 == 0
      return fld_303;
    *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  }
  fld_303 = *(uint32_t *)(this + 48);  // fld_303 = this+48
  if ( fld_303 == 0 )  // 若 fld_303 == 0
    return fld_303;
  if ( !sub_63B400((uint32_t *)this) )  // 调 物品盒数据 6（20 行）
  {
LABEL_37:
    LOBYTE(fld_303) = dword_9B88D0;  // 调 取 16 位值低 8 位
    if ( dword_9B88D0 != 0 && dword_795378 == 8 )  // 若 dword_9B88D0 != 0 && dword_795378 == 8
      LOBYTE(fld_303) = sub_44E850(*(uint32_t **)(this + 16), 26);  // 调 按池号批量回收活动对象
  }
  else
  {
    fld_303 = *(uint32_t *)(this + 48);  // fld_303 = this+48
    if ( dword_9B88D0 != fld_303 || dword_795378 != 8 )  // 若 dword_9B88D0 != fld_303 || dword_795378 != 8
    {
      fld_303 = sub_44E8D0(*(char **)(this + 16), (void *)0x1A, fld_303, 8);  // 调 对象池借出（按池号取可用对象）
      if ( fld_303 != 0 )  // 若 fld_303 != 0
        LOBYTE(fld_303) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)fld_303 + 48))(  // 调用虚函数（虚表槽 +48）
                        fld_303,
                        *(uint32_t *)(*(uint32_t *)(this + 8) + 20) + 57,
                        *(uint32_t *)(*(uint32_t *)(this + 8) + 24) + 55,
                        28,
                        28);
    }
  }
  return fld_303;
}



// ------------------------------------------------------------
// 0x63B6D0 CNRDItemBoxWindow__vmt0 —— CNRDItemBoxWindow__vmt0 构造（106 行：418DD0/484ED0/4F33A0/63B400/4F2E40/4F2E80）
// ------------------------------------------------------------
void /*thiscall*/ CNRDItemBoxWindow__vmt0(int *this, int pArg2)  // 函数: CNRDItemBoxWindow__vmt0 构造（106 行：418DD0/484ED0/4F33A0/63B400/4F2E40/4F2E80）
{
  int v2; // ebx
  int v3; // edi
  int nSelItemSlot; // eax  | +0x0024 → 选中物品槽 id（0x63B4D0: fld_24=*(this+36)；0→帧 15、1→帧 0xE 换算图标）（CNRDItemBoxWindow；va=0063B4D0）
  int nSubState; // eax  | +0x0030 → 子状态/校验结果（0x63B4D0: 由 63B280 返回 1 置 2；非 1 则直接关窗）（CNRDItemBoxWindow；va=0063B4D0）
  int pObj3; // eax
  unsigned int pThis_11; // ecx
  int nSelItemSlot_; // eax  | +0x0024 → 选中物品槽 id（0x63B4D0: fld_24=*(this+36)；0→帧 15、1→帧 0xE 换算图标）（CNRDItemBoxWindow；va=0063B4D0）
  int v10; // edx
  int uActive; // esi  | +0x0028 → 激活标志（CNRDItemBoxWindow；va=0063B4D0）
  unsigned int v12; // edx
  uint8_t v13; // bl
  int pObj; // eax
  int pObj2; // eax
  int v16; // [esp+14h] [ebp+8h]

  v2 = *(uint32_t *)(pArg2 + 24);  // v2 = pArg2+24
  v3 = *(uint32_t *)(pArg2 + 20);  // v3 = pArg2+20
  v16 = v2;
  nSelItemSlot = sub_418DD0(44 - (*(this + 9) != 0));  // this+36 = 状态字
  if ( nSelItemSlot != 0 )  // 若 fld_e9 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)nSelItemSlot + 152))(nSelItemSlot, v3, v2, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  if ( *(this + 12) != 0 )  // 若 *(this + 12) != 0
  {
    if ( (int)sub_484ED0(*(this + 12)) < 0 )  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
    {
      v10 = *this;
      *(this + 12) = 0;  // this+48 = 0
      (*(void (/*thiscall*/ **)(int *))(v10 + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
      return;
    }
    nSubState = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 12) + 16))(*(this + 12));  // 调用虚函数（虚表槽 +16）
    pObj3 = sub_4F33A0(*(uint32_t *)(nSubState + 4));  // 调 sub_4F33A0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v3 + 57, v2 + 55, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  }
  if ( *(this + 13) == 0 && sub_63B400(this) )  // 调 物品盒数据 6（20 行）
    sub_4F2E40(v3 + 57, v2 + 55);  // 调 sub_4F2E40
  pThis_11 = sub_699000((int)(this + 17));  // 【clock_now(clk)】
  nSelItemSlot_ = *(this + 9);  // this+36 = 状态字
  if ( nSelItemSlot_ != 0 )  // 若 fld_e92 != 0
  {
    if ( nSelItemSlot_ != 1 )  // 若 fld_e92 != 1
      return;
    uActive = *(this + 10);  // this+40 = 状态子标志
    if ( uActive == 1 )  // 若 fld_e10 == 1
    {
      v12 = 255 * pThis_11 / 0x3E8;
      if ( v12 <= 0xFF )  // 若 v12 <= 0xFF
      {
        v13 = 255 * pThis_11 / 0x3E8;
        if ( (uint8_t)v12 == 0 )  // 若 (uint8_t)v12 == 0
          return;
      }
      else
      {
        v13 = -1;
      }
    }
    else
    {
      if ( uActive != 2 )  // 若 fld_e10 != 2
        return;
      v13 = -1;
    }
    pObj = sub_418DD0(119);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
        pObj,
        v3 + 57,
        v16 + 55,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,
        1065353216,
        0,
        (v13 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    pObj2 = sub_418DD0(118);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调用虚函数（虚表槽 +128）
        pObj2,
        v3 + 58,
        v16 + 56,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,
        1065353216,
        0,
        (v13 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
  }
  else if ( *(this + 10) == 1 )  // this+40 = 状态子标志
  {
    sub_4F2E80(v3 + 56, v2 + 54, 1, -(int)(uint64_t)(double)(pThis_11 >> 1));  // 调 sub_4F2E80
  }
}



// ============================================================
// 【分区 25】重置/再封确认 CNRDResetOrResealConfirmWindow（0x63B900-0x63C170）
// 资源 etc/reseal.etc 由 0x63B900 装载（4FAA40）；vmt8 确认（63B360 + 63B100）。
// ============================================================
// ------------------------------------------------------------
// 0x63B900 sub_63B900 —— 装载资源 etc/reseal.etc（4FAA40）+ 69A5F0/69A840 定位——再封确认窗用
// ------------------------------------------------------------
int /*thiscall*/ sub_63B900(int *this)  // 函数: 装载资源 etc/reseal.etc（4FAA40）+ 69A5F0/69A840 定位——再封确认窗用
{
  uint32_t *pMem; // eax
  uint32_t *fld_e11; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e112; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_e113; // eax
  int v8; // edx
  int result; // eax

  *(this + 11) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 36);  // this+44 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e11 = sub_43C410(pMem, *(this + 11), 48, 49, 50, 48, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e11 = nullptr;  // fld_e11 = nullptr 空指针
  *(this + 14) = (int)fld_e11;  // this+56 = (int)fld_e11
  sub_69A5F0(fld_e11, 112, 14);  // 调 sub_69A5F0
  sub_69A840(*(this + 14));  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e112 = sub_43C410(pMem2, *(this + 11), 51, 52, 53, 51, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e112 = nullptr;  // fld_e112 = nullptr 空指针
  *(this + 15) = (int)fld_e112;  // this+60 = (int)fld_e112
  sub_69A5F0(fld_e112, 46, 95);  // 调 sub_69A5F0
  sub_69A840(*(this + 15));  // 调 sub_69A840
  pMem3 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    fld_e113 = sub_43C410(pMem3, *(this + 11), 45, 46, 47, 45, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e113 = nullptr;  // fld_e113 = nullptr 空指针
  *(this + 16) = (int)fld_e113;  // this+64 = (int)fld_e113
  sub_69A5F0(fld_e113, 49, 103);  // 调 sub_69A5F0
  sub_69A840(*(this + 16));  // 调 sub_69A840
  *(uint8_t *)(*(this + 15) + 16) = 1;
  *(uint8_t *)(*(this + 16) + 16) = 0;
  v8 = *this;
  *(this + 9) = 0;  // this+36 = 状态字
  (*(void (/*thiscall*/ **)(int *, int))(v8 + 28))(this, 1);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 10, 10);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  sub_69A5F0((uint32_t *)*(this + 2), 142, 201);  // this+8 = 技能槽记录首字
  if ( dword_9B9478 == 0 )  // 若 dword_9B9478 == 0
    return sub_4FAA40("etc/reseal.etc", &unk_9B9474);  // 调 封印(解封)概率表解析器（importResealTable）
  result = (dword_9B947C - dword_9B9478) >> 2;
  if ( result == 0 )  // 若 result == 0
    return sub_4FAA40("etc/reseal.etc", &unk_9B9474);  // 调 封印(解封)概率表解析器（importResealTable）
  return result;
}



// ------------------------------------------------------------
// 0x63BAB0 sub_63BAB0 —— 再封数据 2（16 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63BAB0(uint32_t *this)  // 函数: 再封数据 2（16 行）
{
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = 0;  // this+44 = 0
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 25) = 0;  // this+100 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 27) = 0;  // this+108 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x63BAD0 sub_63BAD0 —— 再封数据 3（22 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63BAD0(uint32_t *this)  // 函数: 再封数据 3（22 行）
{
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx

  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);  // this+40 = 状态子标志
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    result = (**fld_e10)(fld_e10, 1);
  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;  // this+40 = 状态子标志
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    result = (**fld_e11)(fld_e11, 1);
  *(this + 11) = 0;  // this+44 = 0
  return result;
}



// ------------------------------------------------------------
// 0x63BB00 CNRDResetOrResealConfirmWindow__vmt0 —— CNRDResetOrResealConfirmWindow__vmt0 构造（101 行：418DD0/484ED0/4F33A0/4F2CE0/422E70/4F2D60/4F2DF0）
// ------------------------------------------------------------
int /*userpurge*/ CNRDResetOrResealConfirmWindow__vmt0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int pArg3)  // 函数: CNRDResetOrResealConfirmWindow__vmt0 构造（101 行：418DD0/484ED0/4F33A0/4F2CE0/422E70/4F2D60/4F2DF0）
{
  int result; // eax
  int v5; // ebx
  int v6; // edi
  int pObj2; // eax
  int v8; // eax
  int pObj; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // ebx
  int pObj3; // eax
  int pObj4; // eax
  char *v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // [esp-Ch] [ebp-5Ch]
  int v19; // [esp-8h] [ebp-58h]
  int v21; // [esp+8h] [ebp-48h]
  char Buffer[64]; // [esp+Ch] [ebp-44h] BYREF
  int dword_796E502; // [esp+4Ch] [ebp-4h]
  int v24; // [esp+58h] [ebp+8h]
  int v25; // [esp+58h] [ebp+8h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  result = IRDPopupWindow__vmt0(pArg3);
  if ( pArg3 == pDwArg1[2] )  // 若 pArg3 == pDwArg1[2]
  {
    v5 = *(uint32_t *)(pArg3 + 20);  // v5 = pArg3+20
    v6 = *(uint32_t *)(pArg3 + 24);  // v6 = pArg3+24
    v24 = v5;
    pObj2 = sub_418DD0(90);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调用虚函数（虚表槽 +128）
        pObj2,
        v5 + 12,
        v6 + 9,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,
        1065353216,
        0,
        872415231,
        1333788672,
        1333788672);
    if ( sub_484ED0(pDwArg1[25]) == -1 )  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
    {
      v8 = *pDwArg1;
      pDwArg1[25] = 0;
      return (*(int (/*thiscall*/ **)(int *))(v8 + 32))(pDwArg1);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
    else
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[25] + 16))(pDwArg1[25], nArg2) + 68) != 0 )  // 调用虚函数（虚表槽 +16）
      {
        pObj = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[25] + 16))(pDwArg1[25]) + 68);  // 调用虚函数（虚表槽 +16）
        if ( pObj != 0 )  // 若 pObj != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v5 + 13, v6 + 10, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      }
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[25] + 108))(pDwArg1[25]);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pDwArg1 + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
      v21 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[25] + 24))(pDwArg1[25], v10);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
      v12 = v24 + 43;
      (*(void (/*cdecl*/ **)(int, int, int, int))(v21 + 80))(dword_79C0B0, v24 + 43, v6 + 20, v11);  // 调用虚函数（虚表槽 +80）
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
      pObj3 = sub_418DD0(90);  // 调 sub_418DD0
      if ( pObj3 != 0 )  // 若 pObj3 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 调用虚函数（虚表槽 +128）
          pObj3,
          v24 + 12,
          v6 + 87,
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          1065353216,
          1065353216,
          0,
          872415231,
          1333788672,
          1333788672);
      pObj4 = sub_4F33A0(pDwArg1[26]);  // 调 sub_4F33A0
      if ( pObj4 != 0 )  // 若 pObj4 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v24 + 13, v6 + 88, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pDwArg1 + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
      v19 = pDwArg1[27];
      v18 = sub_4F2CE0(pDwArg1[26]);  // 调 sub_4F2CE0
      v15 = sub_422E70(1655);  // 调 sub_422E70
      sprintf(Buffer, v15, v18, v19);  // 调 格式化到缓冲
      v25 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      v16 = sub_4F2D60(pDwArg1[26]);  // 调 sub_4F2D60
      v17 = sub_4F2DF0(v16);  // 调 sub_4F2DF0
      (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v25 + 80))(dword_79C0B0, v12, v6 + 98, v17, Buffer);  // 调用虚函数（虚表槽 +80）
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63BD30 sub_63BD30 —— 再封页绘制（69C3C0/69A5F0/69C440 + 43C410/69A840，58 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63BD30(uint32_t *this)  // 函数: 再封页绘制（69C3C0/69A5F0/69C440 + 43C410/69A840，58 行）
{
  int v2; // edx
  uint32_t *pMem; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e92; // eax
  int v7; // edx

  v2 = *this;
  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+36 = 状态字
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(192, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  sub_69C3C0(1);  // 调 sub_69C3C0
  sub_69A5F0((uint32_t *)*(this + 3), 18, 51);  // this+12 = 技能槽记录次字
  sub_69C440(-1);  // 调 sub_69C440
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e9 = sub_43C410(pMem, *(this + 9), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 10) = fld_e9;  // this+40 = 状态子标志
  sub_69A5F0(fld_e9, 56, 130);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e92 = sub_43C410(pMem2, *(this + 9), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e92 = nullptr;  // fld_e92 = nullptr 空指针
  *(this + 11) = fld_e92;  // this+44 = fld_e92
  sub_69A5F0(fld_e92, 119, 130);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;  // this+60 = 0
  *(this + 16) = 6;  // this+64 = 6
  *(this + 17) = 12;  // this+68 = 12
  *(this + 18) = 0;  // this+72 = 0
  *(this + 19) = 1600;  // this+76 = 1600
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  v7 = *this;
  *(this + 24) = dword_99FCCC;  // this+96 = dword_99FCCC
  *(this + 19) = 175;  // this+76 = 175
  *(this + 15) = 1;  // this+60 = 1
  *(this + 13) = -16777216;  // this+52 = bAuraState
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v7 + 24))(this, 18, 12);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
}



// ------------------------------------------------------------
// 0x63BEB0 CNRDResetOrResealConfirmWindow__vmt8 —— CNRDResetOrResealConfirmWindow__vmt8 确认（63B360 + 63B100 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDResetOrResealConfirmWindow__vmt8(uint32_t *this)
{
  int fld_e10; // eax
  int fld_e4; // ecx
  char ***v4; // edx
  int v5; // ecx
  uint8_t *result; // eax
  int fld_e42; // ecx
  uint32_t **v8; // edx
  int v9; // ecx

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e10 = *(this + 10);  // this+40 = 状态子标志
  if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )  // 若 *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    fld_e4 = *(this + 4);  // fld_e4 = this+4
    v4 = *(char ****)(fld_e4 + 360);
    v5 = fld_e4 + 356;
    if ( v4 != nullptr && (*(uint32_t *)(v5 + 8) - (int)v4) >> 2 != 0 )  // 若 v4 != nullptr && (*(uint32_t *)(v5 + 8) - (int)v4) >> 2 != 0
      sub_63B360(*v4);  // 调 物品盒条目操作 2（63B280 + 698F90）
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    fld_e42 = *(this + 4);  // fld_e42 = this+4
    v8 = *(uint32_t ***)(fld_e42 + 360);
    v9 = fld_e42 + 356;
    if ( v8 != nullptr && (*(uint32_t *)(v9 + 8) - (int)v8) >> 2 != 0 )  // 若 v8 != nullptr && (*(uint32_t *)(v9 + 8) - (int)v8) >> 2 != 0
      sub_63B100(*v8);  // 调 物品盒数据 4（17 行）
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x63BF80 CNRDResetOrResealConfirmWindow__vmtC —— CNRDResetOrResealConfirmWindow__vmtC 文案装配（69C340 + 422E70 + 4F8F40 + 63B0E0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDResetOrResealConfirmWindow__vmtC(uint32_t *this, int nArg2, int nArg3)  // 函数: CNRDResetOrResealConfirmWindow__vmtC 文案装配（69C340 + 422E70 + 4F8F40 + 63B0E0）
{
  char *v4; // eax
  int fld_e25; // eax
  char v6; // al
  int fld_e252; // edi
  int v8; // eax
  char *v9; // eax
  uint32_t *fld_e2; // edi
  int v11; // eax
  int v12; // ecx
  int fld_e4; // ecx
  uint32_t **v14; // edx
  int v15; // ecx
  char v17; // [esp-8h] [ebp-10h]
  char v18; // [esp-4h] [ebp-Ch]

  *(this + 25) = nArg2;  // this+100 = nArg2
  *(this + 26) = nArg3;  // this+104 = nArg3
  if ( nArg3 == 14 )  // 若 nArg3 == 14
  {
    sub_69C340(-1);  // 调 sub_69C340
    v4 = sub_422E70(1692);  // 调 sub_422E70
    sub_69C360(v4, 0);  // 调 sub_69C360
    fld_e25 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 188))(*(this + 25));  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
    v6 = sub_41A5E0(fld_e25 + 46);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    fld_e252 = *(this + 25);  // fld_e252 = this+25
    v18 = v6;
    v17 = *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e252 + 16))(fld_e252) + 24);  // 调用虚函数（虚表槽 +16）
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e252 + 16))(fld_e252);  // 调用虚函数（虚表槽 +16）
    *(this + 27) = sub_4F8F40(*(uint8_t *)(v8 + 84), v17, v18);  // 调 等级分段查表（1..99 × 5 档系数）【推断】
  }
  else
  {
    sub_69C340(-1);  // 调 sub_69C340
    if ( nArg3 == 15 )  // 若 nArg3 == 15
    {
      v9 = sub_422E70(1693);  // 调 sub_422E70
      sub_69C360(v9, 0);  // 调 sub_69C360
      *(this + 27) = 1;  // this+108 = 1
    }
    else
    {
      sub_69C360("ERROR!!", 0);  // 调 sub_69C360
    }
  }
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v11 = 640 - fld_e2[7];
  if ( ((pt.x - 85) & ((pt.x - 85 <= 0) - 1)) < v11 )  // 若 ((pt.x - 85) & ((pt.x - 85 <= 0) - 1)) < v11
    v11 = (pt.x - 85) & ((pt.x - 85 <= 0) - 1);
  v12 = 480 - fld_e2[8];
  if ( ((pt.y - 145) & ((pt.y - 145 <= 0) - 1)) < v12 )  // 若 ((pt.y - 145) & ((pt.y - 145 <= 0) - 1)) < v12
    v12 = (pt.y - 145) & ((pt.y - 145 <= 0) - 1);
  sub_69A5F0(fld_e2, v11, v12);  // 调 sub_69A5F0
  fld_e4 = *(this + 4);  // fld_e4 = this+4
  v14 = *(uint32_t ***)(fld_e4 + 360);
  v15 = fld_e4 + 356;
  if ( v14 != nullptr && (*(uint32_t *)(v15 + 8) - (int)v14) >> 2 != 0 )  // 若 v14 != nullptr && (*(uint32_t *)(v15 + 8) - (int)v14) >> 2 != 0
    sub_63B0E0(*v14);  // 调 物品盒数据 3（17 行）
  return 1;
}



// ------------------------------------------------------------
// 0x63C0D0 sub_63C0D0 —— 再封收尾（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63C0D0(uint32_t *this)  // 函数: 再封收尾（15 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = bAuraState
  *(this + 27) = 0;  // this+108 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x63C0F0 sub_63C0F0 —— 战争房间数据（33 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_63C0F0(int this)  // 函数: 战争房间数据（33 行）
{
  void (/*thiscall*/ ***pThis_2C)(uint32_t, int); // ecx
  int i; // edi
  void (/*thiscall*/ ***fld_30)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_28)(uint32_t, int); // ecx
  void *fld_34; // [esp-8h] [ebp-Ch]

  pThis_2C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 44);
  if ( pThis_2C != nullptr )  // 若 pThis_2C 非空
    (**pThis_2C)(pThis_2C, 1);
  fld_34 = *(void **)(this + 52);
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  j_j__free(fld_34);  // 调 j__free
  for ( i = 0; i < *(uint32_t *)(this + 108); ++i )  // 循环：i = 0; i < *(uint32_t *)(this + 108); ++i
  {
    fld_30 = *(void (/*thiscall*/ ****)(uint32_t, int))(*(uint32_t *)(this + 48) + 4 * i);
    if ( fld_30 != nullptr )  // 若 fld_30 非空
      (**fld_30)(fld_30, 1);
    *(uint32_t *)(*(uint32_t *)(this + 48) + 4 * i) = 0;
  }
  j_j__free(*(void **)(this + 48));  // 调 j__free
  pThis_28 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 40);
  if ( pThis_28 != nullptr )  // 若 pThis_28 非空
    (**pThis_28)(pThis_28, 1);
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
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
char /*thiscall*/ sub_63C180(uint32_t *this, int nArg2)  // 函数: 战争房间难度选择（42EAF0 + 5403D0 + CLICK_BUTTON2）
{
  char result; // al

  result = sub_42EAF0(*(uint32_t **)(dword_8F7A24 + 40), nArg2);  // 调 场景与难度选择
  if ( result == 1 )  // 若 result == 1
  {
    if ( *(uint32_t *)(*(uint32_t *)(*(this + 4) + 2532) + 28) == 1 )  // 若 *(uint32_t *)(*(uint32_t *)(*(this + 4) + 2532) + 28) == 1
      sub_5403D0(0);  // 调 对象状态切换（44E850）——区域选择联动
    sub_5403D0(1);  // 调 对象状态切换（44E850）——区域选择联动
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return (uint8_t)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x63C1E0 CNRDWarRoomDifficultListWindow__vmt8 —— CNRDWarRoomDifficultListWindow__vmt8 Update（69A650 + 63C180 + CLICK_BUTTON2）
// ------------------------------------------------------------
int /*thiscall*/ CNRDWarRoomDifficultListWindow__vmt8(int *this)  // 函数: CNRDWarRoomDifficultListWindow__vmt8 Update（69A650 + 63C180 + CLICK_BUTTON2）
{
  int fld_e11; // eax
  int result; // eax
  int i; // edi
  int fld_e12; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // dword_8F8538 = 技能施放请求对象
    (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  fld_e11 = *(this + 11);  // fld_e11 = this+11
  if ( *(uint8_t *)(fld_e11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e11 + 12) )  // 若 *(uint8_t *)(fld_e11 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = *(this + 27);  // result = this+27
  for ( i = 0; i < result; ++i )  // 循环：i = 0; i < result; ++i
  {
    fld_e12 = *(uint32_t *)(*(this + 12) + 4 * i);
    if ( fld_e12 != 0 && *(uint8_t *)(fld_e12 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e12 + 12) )  // 若 fld_e12 != 0 && *(uint8_t *)(fld_e12 + 17) != 0 && dword_79BE3..
      sub_63C180(this, i);  // 调 战争房间难度选择（42EAF0 + 5403D0 + CLICK_BUTTON2）
    result = *(this + 27);  // result = this+27
  }
  return result;
}



// ------------------------------------------------------------
// 0x63C270 CNRDWarRoomDifficultListWindow__vmt0 —— CNRDWarRoomDifficultListWindow__vmt0 构造（193 行：554930 + 69A110/699FC0/49EF60/49EEE0 + 422E70）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_63C270(int *this, int Value)  // 【CNRDWarRoomDifficultListWindow__vmt0】
{
  uint32_t *result; // eax
  int v5; // edi
  int nItemCount; // ecx  | +0x006C → 条目数（0x63CA70: *(this+108) 清零循环上界）（CNRDWarRoomDifficultListWindow；va=0063CA70）
  int v7; // edi
  int fld_e12; // ecx
  int v9; // ebx
  int fld_e122; // eax
  int v11; // ebx
  int pObj; // eax
  int fld_e123; // eax
  int pObj3; // eax
  int fld_e124; // eax
  int pObj5; // eax
  int fld_e125; // eax
  int v18; // ebx
  int pObj6; // eax
  int v20; // ebx
  int v21; // ebx
  int pObj2; // eax
  int v23; // ebx
  int v24; // ebx
  int pObj4; // eax
  int fld_e126; // eax
  int v27; // ebx
  int v28; // eax
  int v29; // ecx
  uint32_t *fld_e127; // edi
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

  result = (uint32_t *)sub_554930(Value);  // 【IRDPopupWindow__vmt0】
  if ( Value == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v5 = *(uint32_t *)(Value + 24);  // v5 = Value+24
    Valuea = *(uint32_t *)(Value + 20);  // Valuea = Value+20
    result = (uint32_t *)sub_418DD0(0);
    if ( result != nullptr )  // 若 result 非空
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*result + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                           result,
                           Valuea + 6,
                           v5 + 6,
                           dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
  }
  nItemCount = *(this + 27);  // fld_e27 = this+27
  v7 = 0;
  if ( nItemCount > 0 )  // 若 fld_e27 > 0
  {
    result = (uint32_t *)*(this + 12);
    while ( *result != Value )  // 当 *result != Value 循环
    {
      ++v7;  // 自增v7
      ++result;  // 自增result
      if ( v7 >= nItemCount )  // 若 v7 >= fld_e27
        return result;
    }
    fld_e12 = *(uint32_t *)(*(this + 12) + 4 * v7);
    if ( *(uint8_t *)(fld_e12 + 17) != 0 )  // 若 *(uint8_t *)(fld_e12 + 17) != 0
    {
      v9 = *(uint32_t *)(fld_e12 + 12);  // v9 = fld_e12+12
      if ( dword_79BE3C == v9 || dword_79BE34 == v9 || dword_79BE38 == v9 )  // 若 dword_79BE3C == v9 || dword_79BE34 == v9 || dword_79BE38 == v9
      {
        sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
        fld_e122 = *(uint32_t *)(*(this + 12) + 4 * v7);
        v11 = *(uint32_t *)(fld_e122 + 24);  // v11 = fld_e122+24
        Valueb = *(uint32_t *)(fld_e122 + 20);  // Valueb = fld_e122+20
        pObj = sub_418DD0(15);  // 调 sub_418DD0
        if ( pObj != 0 )  // 若 pObj != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, Valueb, v11, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
      }
    }
    fld_e123 = *(uint32_t *)(*(this + 12) + 4 * v7);
    Valuec = *((int16_t *)dword_8F7C48 + 10 * v7);
    v45 = *((int16_t *)dword_8F7C48 + 10 * v7 + 1);
    v43 = *(uint32_t *)(fld_e123 + 24);  // v43 = fld_e123+24
    v39 = *(uint32_t *)(fld_e123 + 20);  // v39 = fld_e123+20
    pObj3 = sub_418DD0(6);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v39 + 6, v43 + 15, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    fld_e124 = *(uint32_t *)(*(this + 12) + 4 * v7);
    v40 = *(uint32_t *)(fld_e124 + 24);  // v40 = fld_e124+24
    v44 = *(uint32_t *)(fld_e124 + 20);  // v44 = fld_e124+20
    pObj5 = sub_418DD0(v7 + 7);  // 调 sub_418DD0
    if ( pObj5 != 0 )  // 若 pObj5 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v44 + 28, v40 + 15, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    fld_e125 = *(uint32_t *)(*(this + 12) + 4 * v7);
    v18 = *(uint32_t *)(fld_e125 + 20) + 99;
    v41 = *(uint32_t *)(fld_e125 + 24);  // v41 = fld_e125+24
    pObj6 = sub_418DD0(28);  // 调 sub_418DD0
    if ( pObj6 != 0 )  // 若 pObj6 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v18, v41 + 17, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v20 = *(uint32_t *)(sub_418DD0(28) + 20) + v18;
    sub_69A110(v20, *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v7) + 24) + 17, Valuec, -1);  // 调 sub_69A110
    v21 = sub_699FC0(Valuec) + v20;
    Valued = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v7) + 24);
    pObj2 = sub_418DD0(29);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v21, Valued + 20, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v23 = *(uint32_t *)(sub_418DD0(29) + 20) + v21;
    sub_69A110(v23, *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v7) + 24) + 17, v45, -1);  // 调 sub_69A110
    v24 = sub_699FC0(v45) + v23;
    Valuee = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v7) + 24);
    pObj4 = sub_418DD0(30);  // 调 sub_418DD0
    if ( pObj4 != 0 )  // 若 pObj4 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v24, Valuee + 17, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 14);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    fld_e126 = *(uint32_t *)(*(this + 12) + 4 * v7);
    v27 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    Valuef = *(uint32_t *)(fld_e126 + 24);  // Valuef = fld_e126+24
    v42 = *(uint32_t *)(fld_e126 + 20);  // v42 = fld_e126+20
    v38 = sub_49EF60(v7);  // 调 槽表遍历求和（·sub_48F4C0 计非 254 字段数）
    v28 = sub_49EEE0(v7);  // 调 槽表遍历求和（·sub_48FBB0 累加非 0xFFFF 字段数）
    (*(void (**)(int, int, int, int, const char *, ...))(v27 + 80))(  // 调用虚函数（虚表槽 +80）
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      v42 + 188,
      Valuef + 18,
      -1,
      "(%d/%d)",
      v28,
      v38);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    result = (uint32_t *)*(this + 13);  // this+52 = bAuraState
    v29 = result[v7];
    if ( v29 != 0 )  // 若 v29 != 0
    {
      result = (uint32_t *)pt.x;
      if ( pt.x >= *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v7) + 20) )  // 若 pt.x >= *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v7) + 20)
      {
        result = *(uint32_t **)(*(this + 12) + 4 * v7);
        if ( pt.x <= result[5] + *(uint32_t *)(result[29] + 20) && pt.y >= result[6] )  // 若 pt.x <= result[5] + *(uint32_t *)(result[29] + 20) && pt.y >= ..
        {
          result = *(uint32_t **)(*(this + 12) + 4 * v7);
          if ( pt.y <= result[6] + *(uint32_t *)(result[29] + 24) )  // 若 pt.y <= result[6] + *(uint32_t *)(result[29] + 24)
          {
            fld_e127 = *(uint32_t **)(*(this + 12) + 4 * v7);
            v31 = fld_e127[29];
            v32 = *(uint32_t *)(v31 + 20) >> 1;
            result = (uint32_t *)(*(uint32_t *)(v31 + 24) >> 1);
            v33 = fld_e127[5] + v32;
            v34 = v29 - 1;
            v35 = (int)result + fld_e127[6] + 10;
            if ( v34 != 0 )  // 若 v34 != 0
            {
              v36 = v34 - 1;
              if ( v36 != 0 )  // 若 v36 != 0
              {
                if ( v36 != 1 )  // 若 v36 != 1
                  return result;
                v37 = sub_422E70(1802);  // 调 sub_422E70
              }
              else
              {
                v37 = sub_422E70(1801);  // 调 sub_422E70
              }
            }
            else
            {
              v37 = sub_422E70(1800);  // 调 sub_422E70
            }
            return (uint32_t *)sub_4649B0(v33, v35, -1, -16777216, 2, v37, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
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
int /*thiscall*/ sub_63C660(int *this, char pszArg2)  // 函数: 难度列表辅助（49EE90）
{
  int result; // eax
  int v4; // esi
  int v5; // edx
  int fld_e12; // eax
  int v7; // ebx
  int pObj; // ebx
  int v9; // [esp+8h] [ebp-8h]
  const char *future_error_what; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  result = *(this + 27);  // result = this+27
  v4 = 0;
  if ( result > 0 )  // 若 result > 0
  {
    v5 = 0;
    for ( i = 0; ; i += 20 )  // 循环：i = 0; ; i += 20
    {
      fld_e12 = *(uint32_t *)(*(this + 12) + 4 * v4);
      if ( fld_e12 == 0 )  // 若 fld_e12 == 0
        goto LABEL_14;  // 跳转 LABEL_14
      *(uint8_t *)(fld_e12 + 17) = pszArg2;  // fld_e12+17 = pszArg2
      v7 = *(int16_t *)((char *)dword_8F7C48 + v5);
      v9 = *(int16_t *)((char *)dword_8F7C48 + v5 + 2);
      if ( pszArg2 != 1 )  // 若 pszArg2 != 1
        goto LABEL_14;  // 跳转 LABEL_14
      if ( sub_49EE90(v4) == 0 )  // 调 槽表遍历计数（·sub_48FD50 为真的条目数）
        break;
      if ( dword_8F7C04 != 0  // dword_8F7C04 = 本地玩家对象
        && *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) >= v7  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
        && *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) <= v9 )  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      {
        pObj = **((uint32_t **)dword_8F852C + 3);  // dword_8F852C = UI 管理器全局
        future_error_what = std::_Get_future_error_what(v4 + dword_77F888);
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj) < (unsigned int)future_error_what )  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
        {
          *(uint32_t *)(*(this + 13) + 4 * v4) = 3;  // this+52 = bAuraState
          goto LABEL_13;  // 跳转 LABEL_13
        }
      }
      else
      {
        *(uint32_t *)(*(this + 13) + 4 * v4) = 1;  // this+52 = bAuraState
        *(uint8_t *)(*(uint32_t *)(*(this + 12) + 4 * v4) + 17) = 0;
      }
LABEL_14:
      result = *(this + 27);  // result = this+27
      ++v4;  // 自增v4
      v5 = i + 20;
      if ( v4 >= result )  // 若 v4 >= result
        return result;
    }
    *(uint32_t *)(*(this + 13) + 4 * v4) = 2;  // this+52 = bAuraState
LABEL_13:
    *(uint8_t *)(*(uint32_t *)(*(this + 12) + 4 * v4) + 17) = 0;
    goto LABEL_14;  // 跳转 LABEL_14
  }
  return result;
}



// ------------------------------------------------------------
// 0x63C780 sub_63C780 —— 战争房间页绘制（426BD0/69C780/69C7B0/69A5F0/69A840 + 699E20/699E40，147 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63C780(uint32_t *this)  // 函数: 战争房间页绘制（426BD0/69C780/69C7B0/69A5F0/69A840 + 699E20/699E40，147…
{
  int v1; // eax
  void *pMem; // eax
  void *pMem2; // eax
  int fld_e272; // ecx
  int v6; // edi
  int v7; // eax
  uint8_t *pMem3; // ebx
  uint32_t *pMem32; // ecx
  uint8_t *pMem4; // eax
  uint32_t *pMem42; // ebx
  uint8_t *pMem5; // eax
  uint8_t *pMem52; // ebx
  int fld_e9; // edi
  int fld_e273; // eax
  size_t fld_e27; // [esp-8h] [ebp-2Ch]
  void *Block; // [esp+Ch] [ebp-18h]
  void *Blocka; // [esp+Ch] [ebp-18h]
  int v20; // [esp+10h] [ebp-14h]
  int v21; // [esp+10h] [ebp-14h]
  int v22; // [esp+14h] [ebp-10h]

  v1 = *(uint32_t *)(dword_8F8508 + 8);  // v1 = dword_8F8508+8
  *(this + 27) = v1;  // this+108 = v1
  pMem = operator new(4 * v1);
  fld_e27 = 4 * *(this + 27);
  *(this + 12) = pMem;  // this+48 = pMem
  pMem2 = operator new(fld_e27);
  fld_e272 = *(this + 27);  // fld_e272 = this+27
  *(this + 13) = pMem2;  // this+52 = bAuraState
  v6 = 0;
  v7 = 0;
  if ( fld_e272 > 0 )  // 若 fld_e272 > 0
  {
    do
      *(uint32_t *)(*(this + 13) + 4 * v7++) = 0;  // this+52 = bAuraState
    while ( v7 < *(this + 27) );  // 当 v7 < *(this + 27) 循环
  }
  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 196);  // this+36 = 状态字
  pMem3 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem3 != nullptr )  // 若 pMem3 非空
  {
    v20 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
    sub_426BD0(pMem3);  // 调 nengine::IControl 构造
    *(uint32_t *)pMem3 = &nengine::CNButton::`vftable';  // vftable 复位
    sub_69C780(v8);  // 调 sub_69C780
    sub_69C7B0(v20, 23, 24, 25, 23, 0, 0);  // 调 sub_69C7B0
    v9 = v8;
  }
  else
  {
    v9 = nullptr;  // v9 = nullptr 空指针
  }
  *(this + 11) = v9;  // this+44 = v9
  sub_69A5F0(v9, 230, 11);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  v21 = 37;
  if ( (int)*(this + 27) > 0 )  // 若 (int)*(this + 27) > 0
  {
    v22 = 18;
    do
    {
      v10 = operator new(0x84u);  // operator new 分配 132 字节
      v11 = v10;
      if ( v10 != nullptr )  // 若 v10 非空
      {
        Block = (void *)*(this + 9);  // this+36 = 状态字
        sub_426BD0(v10);  // 调 nengine::IControl 构造
        *v11 = &nengine::CNButton::`vftable';  // vftable 复位
        sub_69C780(pMem42);  // 调 sub_69C780
        sub_69C7B0(Block, v22 - 1, v22, v22, v22 - 2, 0, 0);  // 调 sub_69C7B0
      }
      else
      {
        pMem42 = nullptr;  // pMem42 = nullptr 空指针
      }
      *(uint32_t *)(*(this + 12) + 4 * v6) = pMem42;
      sub_69A5F0(*(uint32_t **)(*(this + 12) + 4 * v6), 14, v21);  // 调 sub_69A5F0
      *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * v6) + 68) = this;
      sub_69A840(*(uint32_t *)(*(this + 12) + 4 * v6++));  // 调 sub_69A840
      v21 += 52;
      v22 += 3;
    }
    while ( v6 < *(this + 27) );  // 当 v6 < *(this + 27) 循环
    v6 = 0;
  }
  *((uint8_t *)this + 56) = 0;
  *((uint8_t *)this + 57) = 0;
  *((uint8_t *)this + 58) = 0;
  *((uint8_t *)this + 59) = 0;
  *(this + 17) = 0;  // this+68 = 0
  *(this + 18) = 6;  // this+72 = 6
  *(this + 19) = 12;  // this+76 = 12
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 21) = 1600;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 25) = 0;  // this+100 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 26) = dword_99FCCC;  // this+104 = dword_99FCCC
  *((uint8_t *)this + 58) = 1;
  *(this + 15) = -16777216;  // this+60 = -16777216
  *(this + 21) = 200;  // this+84 = pFxObjA
  *(this + 17) = 0;  // this+68 = 0
  *(this + 22) = 1;  // this+88 = pFxObjB
  pMem5 = operator new(0x2Cu);  // operator new 分配 44 字节
  pMem52 = pMem5;
  if ( pMem5 != nullptr )  // 若 pMem5 非空
  {
    fld_e9 = *(this + 9);  // this+36 = 状态字
    Blocka = (void *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    pMem5[4] = 0;
    *(uint32_t *)pMem5 = &nengine::CNNumberSet::`vftable';  // vftable 复位
    sub_699E20(pMem5);  // 调 sub_699E20
    sub_699E40(Blocka, fld_e9, 30, 2);  // 调 sub_699E40
    v6 = (int)pMem52;
  }
  fld_e273 = *(this + 27);  // fld_e273 = this+27
  *(this + 10) = v6;  // this+40 = 状态子标志
  switch ( fld_e273 )  // 分支：按 fld_e273 分派
  {
    case 0:
    case 1:
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 7);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
      break;
    case 2:
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 10);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
      break;
    case 3:
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 14);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
      break;
    case 4:
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 18);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
      break;
    default:
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 22);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
      break;
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 2);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
}


// ------------------------------------------------------------
// 0x63CA70 CNRDWarRoomDifficultListWindow__vmtC —— CNRDWarRoomDifficultListWindow__vmtC 打开槽（69A5F0 + 63C660）
// ------------------------------------------------------------
char /*thiscall*/ CNRDWarRoomDifficultListWindow__vmtC(int this, int nArg2, int nArg3)  // 函数: CNRDWarRoomDifficultListWindow__vmtC 打开槽（69A5F0 + 63C660）
{
  int i; // eax

  sub_69A5F0(*(uint32_t **)(this + 8), 192, 55);  // 调 sub_69A5F0
  dword_9B94AC = this;
  for ( i = 0; i < *(uint32_t *)(this + 108); ++i )  // 循环：i = 0; i < *(uint32_t *)(this + 108); ++i
    *(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i) = 0;
  sub_63C660((int *)this, 1);  // 调 难度列表辅助（49EE90）
  return 1;
}



// ------------------------------------------------------------
// 0x63CAC0 CNRDWarRoomInfoWindow__vmt8 —— CNRDWarRoomInfoWindow__vmt8 Update（49EDC0/48FBB0/48FBF0/4902A0 进入战争房间 + 423200 系 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDWarRoomInfoWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax
  int fld_e10; // eax
  int v4; // eax
  int v5; // edi
  int dword_795D442; // [esp+4h] [ebp-4h] BYREF

  if ( dword_795D44 == -1 )  // 若 dword_795D44 == -1
    return (uint8_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e10 = *(this + 10);  // this+40 = 状态子标志
  if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )  // 若 *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  v4 = sub_49EDC0(dword_795D44, -1);  // 调 红黑树多槽查表（槽内 lower_bound，命中返回条目 +16）
  v5 = v4;
  *(uint8_t *)(*(this + 11) + 17) = v4 != 0
                               && sub_48FBB0(v4) != 8  // 调 槽表计数（+40..+68 中不等于 0xFFFF 的字段数）
                               && sub_48FBF0(v5) != 0  // 调 槽表计数（+8..+36 中等于 255 的字段数）
                               && (uint8_t)sub_4902A0(v5) == 0;  // 调 动画播放态判定（帧态 2/3/4 为进行中，-1 视为起始）
  result = (uint8_t *)*(this + 11);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    sub_423200(dword_8F7B08, 93);  // 【发送网络包API】
    dword_795D442 = dword_795D44;
    sub_423290(dword_8F7B08, (int)&dword_795D442, 2);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x63CBD0 CNRDWarRoomInfoWindow__vmtC —— CNRDWarRoomInfoWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDWarRoomInfoWindow__vmtC(uint32_t **this, int nArg2, int nArg3)  // 函数: CNRDWarRoomInfoWindow__vmtC 打开槽（69A5F0）
{
  dword_795D44 = nArg3;
  sub_69A5F0(*(this + 2), (640 - (*(this + 2))[7]) / 2, (480 - (*(this + 2))[8]) / 2);  // this+8 = 技能槽记录首字
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
int */*userpurge*/ CNRDWarRoomInfoWindow__vmt0@<eax>(int pArg1@<ecx>, int nArg2@<esi>, int pArg3)
{
  int *result; // eax
  int v5; // esi
  int v6; // edi
  int pObj5; // eax
  int pObj2; // eax
  int v9; // esi
  int v10; // edi
  int v11; // ebx
  int pObj; // eax
  int v13; // esi
  int pObj3; // eax
  int pObj4; // eax
  int v16; // ebx
  int v18; // [esp+Ch] [ebp-Ch]
  int *v19; // [esp+10h] [ebp-8h]
  int v21; // [esp+20h] [ebp+8h]

  result = (int *)IRDPopupWindow__vmt0(pArg3);
  if ( pArg3 == *(uint32_t *)(pArg1 + 8) )  // 若 pArg3 == *(uint32_t *)(pArg1 + 8)
  {
    v5 = *(uint32_t *)(pArg3 + 20);  // v5 = pArg3+20
    v6 = *(uint32_t *)(pArg3 + 24);  // v6 = pArg3+24
    pObj5 = sub_418DD0(103);  // 调 sub_418DD0
    if ( pObj5 != 0 )  // 若 pObj5 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v5 + 8, v6 + 8, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj2 = sub_418DD0(5);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v5 + 47, v6 + 12, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    result = (int *)sub_49EDC0(dword_795D44, -1);  // 调 红黑树多槽查表（槽内 lower_bound，命中返回条目 +16）
    if ( result != nullptr )  // 若 result 非空
    {
      v21 = v5 + 9;
      v9 = 0;
      v10 = v6 + 34;
      v18 = 0;
      v19 = result + 2;
      do
      {
        result = (int *)sub_418DD0(45);
        if ( result != nullptr )  // 若 result 非空
          result = (int *)(*(int (/*thiscall*/ **)(int *, int, int, int))(*result + 152))(result, v21, v10, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        if ( *v19 != 255 )  // 若 *v19 != 255
        {
          result = (int *)sub_578E80(v9);
          v11 = (int)result;
          if ( result != nullptr )  // 若 result 非空
          {
            pObj = sub_42B340((int)result);  // 调 虚拟角色惰性创建（0x294 字节）
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, int))(*(uint32_t *)pObj + 384))(  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
              pObj,
              v21,
              v10,
              16,
              16,
              1065353216,
              nArg2);
            v13 = *v19;
            if ( (*v19 == 1 || v13 == 2) && v13 != 4 && v13 != 3 )  // 若 (*v19 == 1 || v13 == 2) && v13 != 4 && v13 != 3
            {
              sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
              pObj3 = sub_418DD0(v13 + 88);  // 调 sub_418DD0
              if ( pObj3 != 0 )  // 若 pObj3 != 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v21, v10, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              pObj4 = sub_418DD0(v13 + 96);  // 调 sub_418DD0
              if ( pObj4 != 0 )  // 若 pObj4 != 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v21 + 18, v10, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
            }
            nArg2 = pArg1 + 48;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
            if ( *(uint32_t *)(v11 + 40) < 0x10u )  // 若 *(uint32_t *)(v11 + 40) < 0x10u
              v16 = v11 + 20;
            else
              v16 = *(uint32_t *)(v11 + 20);  // v16 = v11+20
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              v21 + 5,
              v10 + 3,
              -1,
              v16);
            result = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
            v9 = v18;
          }
        }
        ++v9;  // 自增v9
        v10 += 17;
        v18 = v9;
        ++v19;  // 自增v19
      }
      while ( v9 < 8 );  // 当 v9 < 8 循环
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
int /*thiscall*/ sub_63CE30(uint32_t *this)  // 函数: 战争房间清理（43C410/69A5F0/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax
  int v6; // edx

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+36 = 状态字
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e9 = sub_43C410(pMem, *(this + 9), 23, 24, 25, 23, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 10) = fld_e9;  // this+40 = 状态子标志
  sub_69A5F0(fld_e9, 136, 11);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 196), 2, 3, 4, 2, 0, 0);  // 调 nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 11) = v5;  // this+44 = v5
  sub_69A5F0(v5, 36, 174);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;  // this+60 = 0
  *(this + 16) = 6;  // this+64 = 6
  *(this + 17) = 12;  // this+68 = 12
  *(this + 18) = 0;  // this+72 = 0
  *(this + 19) = 1600;  // this+76 = 1600
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  v6 = *this;
  *(this + 24) = dword_99FCCC;  // this+96 = dword_99FCCC
  *(this + 13) = -16777216;  // this+52 = bAuraState
  *(this + 19) = 144;  // this+76 = 144
  *(this + 15) = 1;  // this+60 = 1
  *(this + 20) = 1;  // this+80 = nAuraStage
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v6 + 24))(this, 12, 15);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 3);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
}



// ------------------------------------------------------------
// 0x63CFA0 sub_63CFA0 —— 分解数据（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63CFA0(int this)  // 函数: 分解数据（15 行）
{
  *(uint32_t *)(this + 36) = 0;  // this+144 = pFrameList144
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  *(uint8_t *)(this + 52) = 0;  // this+52 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x63CFC0 CNRDItemDisjointConfirmWindow__vmt8 —— CNRDItemDisjointConfirmWindow__vmt8 确认分解（CLICK_BUTTON2）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemDisjointConfirmWindow__vmt8(int *this)  // 函数: CNRDItemDisjointConfirmWindow__vmt8 确认分解（CLICK_BUTTON2）
{
  int fld_e10; // eax
  int result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  fld_e10 = *(this + 10);  // this+40 = 状态子标志
  if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )  // 若 *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 20))(this);  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = *(this + 11);  // result = this+11
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 若 *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  }
  return result;
}



// ------------------------------------------------------------
// 0x63D030 CNRDItemDisjointConfirmWindow__vmt14 —— CNRDItemDisjointConfirmWindow__vmt14 分解执行（484ED0 + 54D470 工具窗联动 + 44ABE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemDisjointConfirmWindow__vmt14(char **this)  // 函数: CNRDItemDisjointConfirmWindow__vmt14 分解执行（484ED0 + 54D470 工具窗联动 + 44ABE0）
{
  char *v2; // eax

  if ( *((uint32_t *)*(this + 4) + 26) != 10 )  // 若 *((uint32_t *)*(this + 4) + 26) != 10
  {
    v2 = sub_422E70(1657);  // 调 sub_422E70
LABEL_5:
    sub_44E8D0(*(this + 4), (void *)0x1B, (int)v2, 0);  // 调 对象池借出（按池号取可用对象）
    (*((void (/*thiscall*/ **)(char **))*this + 8))(this);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
    return 1;
  }
  if ( sub_484ED0(*(this + 12)) == -1 )  // 调 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
  {
    v2 = sub_422E70(962);  // 调 sub_422E70
    goto LABEL_5;  // 跳转 LABEL_5
  }
  sub_54D470(*(this + 12));  // 调 sub_54D470
  if ( *((uint8_t *)this + 52) != 0 )  // this+52 = bAuraState
    sub_44ABE0(*(this + 4), 7);  // 调 选中索引 setter
  (*((void (/*thiscall*/ **)(char **))*this + 8))(this);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
  return 1;
}



// ------------------------------------------------------------
// 0x63D0B0 CNRDItemDisjointConfirmWindow__vmt0 —— CNRDItemDisjointConfirmWindow__vmt0 构造（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemDisjointConfirmWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDItemDisjointConfirmWindow__vmt0 构造（418DD0）
{
  int result; // eax
  int v4; // edi
  int v5; // ebx
  int pObj; // eax
  int fld_e28; // ecx
  uint32_t *pThis_1E; // ecx

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    if ( *((uint32_t *)dword_8F8528 + 26) == 10 )  // dword_8F8528 = 主管理器
    {
      v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
      v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
      pObj = sub_418DD0(90);  // 调 sub_418DD0
      if ( pObj != 0 )  // 若 pObj != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
          pObj,
          v4 + 12,
          v5 + 9,
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          1065353216,
          1065353216,
          0,
          872415231,
          1333788672,
          1333788672);
      fld_e28 = *(this + 28);  // this+112 = pHostComp
      if ( fld_e28 != 0 )  // 若 fld_e28 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e28 + 152))(fld_e28, v4 + 13, v5 + 10, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 14);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
      if ( *(this + 35) < 0x10u )  // 若 *(this + 35) < 0x10u
        pThis_1E = this + 30;
      else
        pThis_1E = (uint32_t *)*(this + 30);  // this+120 = 动画对象指针
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        v4 + 18,
        v5 + 20,
        *(this + 36),  // this+144 = pFrameList144
        pThis_1E);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63D1A0 sub_63D1A0 —— 分解页绘制（69C3C0/69A5F0 + 43C410/69A840，57 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63D1A0(uint32_t *this)  // 函数: 分解页绘制（69C3C0/69A5F0 + 43C410/69A840，57 行）
{
  int v2; // edx
  uint32_t *pMem; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e92; // eax
  int result; // eax

  v2 = *this;
  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+36 = 状态字
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(192, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  sub_69C3C0(1);  // 调 sub_69C3C0
  sub_69A5F0((uint32_t *)*(this + 3), 18, 51);  // this+12 = 技能槽记录次字
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e9 = sub_43C410(pMem, *(this + 9), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 10) = fld_e9;  // this+40 = 状态子标志
  sub_69A5F0(fld_e9, 48, 78);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e92 = sub_43C410(pMem2, *(this + 9), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e92 = nullptr;  // fld_e92 = nullptr 空指针
  *(this + 11) = fld_e92;  // this+44 = fld_e92
  sub_69A5F0(fld_e92, 127, 78);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  *((uint8_t *)this + 56) = 0;
  *((uint8_t *)this + 57) = 0;
  *((uint8_t *)this + 58) = 0;
  *((uint8_t *)this + 59) = 0;
  *(this + 17) = 0;  // this+68 = 0
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 25) = 0;  // this+100 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 18) = 6;  // this+72 = 6
  *(this + 19) = 12;  // this+76 = 12
  *(this + 21) = 1600;  // this+84 = pFxObjA
  result = dword_99FCCC;
  *(this + 26) = dword_99FCCC;  // this+104 = dword_99FCCC
  *(this + 21) = 192;  // this+84 = pFxObjA
  *(this + 17) = 1;  // this+68 = 1
  *(this + 15) = -16777216;  // this+60 = -16777216
  return result;
}



// ------------------------------------------------------------
// 0x63D300 CNRDItemDisjointConfirmWindow__vmtC —— CNRDItemDisjointConfirmWindow__vmtC 文案装配（4015C0 + 69C340/69C440/422E70/69C360）
// ------------------------------------------------------------
char /*userpurge*/ CNRDItemDisjointConfirmWindow__vmtC@<al>(int pArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4)  // 函数: CNRDItemDisjointConfirmWindow__vmtC 文案装配（4015C0 + 69C340/69C440/422E70/69C360）
{
  int v6; // eax
  int pObj; // ecx
  void *v8; // eax
  char *v9; // eax
  uint32_t *v10; // esi
  int v11; // eax
  int v12; // edx

  *(uint32_t *)(pArg1 + 48) = nArg3;  // pArg1+48 = nArg3
  *(uint8_t *)(pArg1 + 52) = nArg4 != 0;  // pArg1+52 = nArg4 != 0
  if ( nArg3 == 0 )  // 若 nArg3 == 0
    return 0;
  v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 16))(nArg3, nArg2);  // 调用虚函数（虚表槽 +16）
  pObj = *(uint32_t *)(pArg1 + 48);  // pObj = pArg1+48
  *(uint32_t *)(pArg1 + 112) = *(uint32_t *)(v6 + 68);  // pArg1+112 = *(uint32_t *)(v6 + 68)
  v8 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 108))(pObj);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
  sub_4015C0(v8, strlen((const char *)v8));  // 【std::string构造赋值】
  *(uint32_t *)(pArg1 + 144) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 48) + 24))(*(uint32_t *)(pArg1 + 48));  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C440(-1);  // 调 sub_69C440
  v9 = sub_422E70(960);  // 调 sub_422E70
  sub_69C360(v9, 0);  // 调 sub_69C360
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 24))(pArg1, 18, 8);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  v10 = *(uint32_t **)(pArg1 + 8);
  v11 = 640 - v10[7];
  if ( ((pt.x - 74) & ((pt.x - 74 <= 0) - 1)) < v11 )  // 若 ((pt.x - 74) & ((pt.x - 74 <= 0) - 1)) < v11
    v11 = (pt.x - 74) & ((pt.x - 74 <= 0) - 1);
  v12 = 480 - v10[8];
  if ( (pt.y - 89 <= 0 ? 0 : pt.y - 89) < v12 )  // 若 (pt.y - 89 <= 0 ? 0 : pt.y - 89) < v12
    v12 = pt.y - 89 <= 0 ? 0 : pt.y - 89;
  sub_69A5F0(v10, v11, v12);  // 调 sub_69A5F0
  return 1;
}



// ------------------------------------------------------------
// 0x63D400 sub_63D400 —— 分解数据 2（16 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63D400(int this)  // 函数: 分解数据 2（16 行）
{
  *(uint32_t *)(this + 36) = 0;  // this+144 = pFrameList144
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  *(uint32_t *)(this + 152) = 0;  // this+152 = 0
  *(uint32_t *)(this + 156) = 0;  // this+156 = 0
  *(uint8_t *)(this + 188) = 0;  // this+188 = 0
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
int /*thiscall*/ CNRDLotteryItemWindow__vmt10(int *this)  // 函数: CNRDLotteryItemWindow__vmt10 状态切换槽（432EE0）
{
  int result; // eax

  result = *(this + 38);  // result = this+38
  if ( result == 0 )  // 若 result == 0
    return sub_432EE0(4);  // 调 音效 TAG 查询包装
  return result;
}



// ------------------------------------------------------------
// 0x63D440 CNRDLotteryItemWindow__vmt8 —— CNRDLotteryItemWindow__vmt8 Update（484E80/423200 系 + CLICK_BUTTON2）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDLotteryItemWindow__vmt8(int *this)
{
  int fld_e46; // edi
  int fld_e39; // edi  | +0x009C → ★ 物品 id B（0x63D940: *(this+156) = *(nArg2 vt+16() + 4)）（CNRDLotteryItemWindow；va=0063D940）
  int fld_e9; // eax  | +0x0024 → ★ 页签按钮 A（0x63D940: 其 +16 = (*(this+152) == 1)）（CNRDLotteryItemWindow；va=0063D940）
  uint32_t *result; // eax
  int fld_e392; // [esp+4h] [ebp-4h] BYREF

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  if ( *(this + 38) == 0 && *((uint8_t *)this + 188) == 0 )  // 若 *(this + 38) == 0 && *((uint8_t *)this + 188) == 0
  {
    fld_e46 = *(this + 46);  // fld_e46 = this+46
    if ( sub_699000((int)(this + 40)) >= fld_e46 )  // 【clock_now(clk)】
    {
      fld_e39 = sub_484E80(*(this + 39));  // 调 按类型查找下标（同一匹配规则，未命中 -1）
      if ( fld_e39 == -1 )  // 若 fld_e39 == -1
      {
        (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
      }
      else
      {
        sub_423200(dword_8F7B08, 29);  // 【发送网络包API】
        fld_e392 = fld_e39;
        sub_423290(dword_8F7B08, (int)&fld_e392, 2);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
        sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
      }
      *((uint8_t *)this + 188) = 1;
    }
  }
  fld_e9 = *(this + 9);  // this+36 = 状态字
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12)  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *..
    || *((uint8_t *)(result = (uint32_t *)*(this + 10)) + 17) != 0 && dword_79BE34 == result[3] )  // this+40 = 状态子标志
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x63D510 CNRDLotteryItemWindow__vmt0 —— CNRDLotteryItemWindow__vmt0 构造（131 行：554930 + 699000/4049C0/488670）
// ------------------------------------------------------------
int /*thiscall*/ sub_63D510(int *this, int pArg2)  // 【CNRDLotteryItemWindow__vmt0】
{
  int result; // eax
  int v4; // edi
  int fld_e39; // ecx  | +0x009C → ★ 物品 id B（0x63D940: *(this+156) = *(nArg2 vt+16() + 4)）（CNRDLotteryItemWindow；va=0063D940）
  int v6; // eax
  int v7; // ebx
  int pObj2; // eax
  int nRand; // ebx
  int pThis_28; // eax
  int fld_e26; // ecx  | +0x0068 → ★ 物品 id A（CNRDLotteryItemWindow；va=0063D940）
  int pObj3; // eax
  int fld_e46; // ebx
  int pThis_282; // eax
  uint64_t v15; // rax
  uint32_t *v16; // ecx
  int pObj; // eax
  uint32_t *pThis_1C; // ecx
  char *v19; // [esp-Ch] [ebp-1Ch]
  int v20; // [esp+Ch] [ebp-4h]
  int nRand2; // [esp+Ch] [ebp-4h]
  int v22; // [esp+18h] [ebp+8h]
  int v23; // [esp+18h] [ebp+8h]

  result = sub_554930(pArg2);  // 【IRDPopupWindow__vmt0】
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v22 = *(uint32_t *)(pArg2 + 24);  // v22 = pArg2+24
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    fld_e39 = *(this + 39);  // fld_e39 = this+39
    if ( *(this + 38) != 0 )  // 若 *(this + 38) != 0
    {
      v6 = 1119;
      if ( fld_e39 == 1086 )  // 若 fld_e39 == 1086
      {
        v6 = 2011;
      }
      else if ( fld_e39 == 7039 )  // 否则若 fld_e39 == 7039
      {
        v6 = 2014;
      }
    }
    else
    {
      v6 = 1118;
      if ( fld_e39 == 1086 )  // 若 fld_e39 == 1086
      {
        v6 = 2010;
      }
      else if ( fld_e39 == 7039 )  // 否则若 fld_e39 == 7039
      {
        v6 = 2013;
      }
    }
    v20 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    v19 = sub_422E70(v6);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v20 + 80))(dword_79C0B0, v4 + 6, v22 + 20, -1, v19);  // 调用虚函数（虚表槽 +80）
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    v7 = v22 + 49;
    v23 = v22 + 49;
    pObj2 = sub_418DD0(90);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调用虚函数（虚表槽 +128）
        pObj2,
        v4 + 18,
        v7,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,
        1065353216,
        0,
        872415231,
        1333788672,
        1333788672);
    if ( *(this + 26) != 0 )  // 若 *(this + 26) != 0
    {
      nRand = v4 + 19;
      nRand2 = v23 + 1;
      if ( *(this + 38) == 0 )  // 若 *(this + 38) == 0
      {
        pThis_28 = sub_699000((int)(this + 40));  // 【clock_now(clk)】
        srand(pThis_28 / 30);  // 调 设置随机种子
        nRand = nRand + rand() % 2 - 1;  // 调 以 16 位种子状态递推并返回 15 位结果
        nRand2 = v23 + rand() % 2;  // 调 以 16 位种子状态递推并返回 15 位结果
      }
      fld_e26 = *(this + 26);  // fld_e26 = this+26
      if ( fld_e26 != 0 )  // 若 fld_e26 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e26 + 152))(fld_e26, nRand, nRand2, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      v7 = v23;
    }
    if ( *(this + 38) != 0 )  // 若 *(this + 38) != 0
    {
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
      if ( (unsigned int)*(this + 33) < 0x10 )  // 若 (unsigned int)*(this + 33) < 0x10
        pThis_1C = this + 28;
      else
        pThis_1C = (uint32_t *)*(this + 28);  // this+112 = pHostComp
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        v4 + 6,
        v7 + 10,
        *(this + 34),
        pThis_1C);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    }
    else
    {
      pObj3 = sub_418DD0(104);  // 调 sub_418DD0
      if ( pObj3 != 0 )  // 若 pObj3 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v4 + 53, v7 + 10, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      fld_e46 = *(this + 46);  // fld_e46 = this+46
      pThis_282 = sub_699000((int)(this + 40));  // 【clock_now(clk)】
      v15 = (uint64_t)sub_4049C0(0.0, 161.0, pThis_282, fld_e46);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v16 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
      v16[13] = 0;
      v16[14] = v15 + v4 + 54;  // v16[14] 写入 v15 + v4 + 54
      v16[15] = 480;
      pObj = sub_418DD0(105);  // 调 sub_418DD0
      if ( pObj != 0 )  // 若 pObj != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v4 + 54, v23 + 11, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      return sub_488670(dword_79C0B0);  // 调 视口重置 640x480
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x63D7F0 sub_63D7F0 —— 赌博页绘制（43C410/69A5F0/69A840，59 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63D7F0(uint32_t *this)  // 函数: 赌博页绘制（43C410/69A5F0/69A840，59 行）
{
  int v2; // edx
  uint32_t *pMem; // eax
  uint32_t *fld_e11; // eax
  int fld_e2; // edx
  uint32_t *pMem2; // eax
  uint32_t *fld_e112; // eax
  int fld_e22; // edx
  int result; // eax

  v2 = *this;
  *(this + 11) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+44 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  (*(void (/*stdcall*/ **)(int, int))(v2 + 24))(19, 9);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e11 = sub_43C410(pMem, *(this + 11), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e11 = nullptr;  // fld_e11 = nullptr 空指针
  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  *(this + 9) = fld_e11;  // this+36 = 状态字
  sub_69A5F0(fld_e11, 94, *(uint32_t *)(fld_e2 + 32) - 37);  // 调 sub_69A5F0
  sub_69A840(*(this + 9));  // this+36 = 状态字
  pMem2 = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e112 = sub_43C410(pMem2, *(this + 11), 12, 13, 14, 12, 0, 0);  // 调 nengine::CNButton 构造
  else
    fld_e112 = nullptr;  // fld_e112 = nullptr 空指针
  fld_e22 = *(this + 2);  // this+8 = 技能槽记录首字
  *(this + 10) = fld_e112;  // this+40 = 状态子标志
  sub_69A5F0(fld_e112, 94, *(uint32_t *)(fld_e22 + 32) - 37);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // this+40 = 状态子标志
  *((uint8_t *)this + 48) = 0;
  *((uint8_t *)this + 49) = 0;
  *((uint8_t *)this + 50) = 0;
  *((uint8_t *)this + 51) = 0;
  *(this + 15) = 0;  // this+60 = 0
  *(this + 18) = 0;  // this+72 = 0
  *(this + 20) = 0;  // this+80 = nAuraStage
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 22) = 0;  // this+88 = pFxObjB
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 16) = 6;  // this+64 = 6
  *(this + 17) = 12;  // this+68 = 12
  *(this + 19) = 1600;  // this+76 = 1600
  result = dword_99FCCC;
  *(this + 24) = dword_99FCCC;  // this+96 = dword_99FCCC
  *(this + 19) = 228;  // this+76 = 228
  *(this + 15) = 1;  // this+60 = 1
  *(this + 13) = -16777216;  // this+52 = bAuraState
  return result;
}



// ------------------------------------------------------------
// 0x63D940 CNRDLotteryItemWindow__vmtC —— CNRDLotteryItemWindow__vmtC 播放赌博动画：GAMBLE_OPEN_LOOP 开启循环 + GAMBLE_RESULT_COMMON/GAMBLE_RESULT_GOOD 结果事件（69A5F0/698F90/432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDLotteryItemWindow__vmtC(int this, int nArg2, int nArg3)  // 函数: CNRDLotteryItemWindow__vmtC 播放赌博动画：GAMBLE_OPEN_LOOP 开启循环 + GAMBLE_RESULT_COMMON/GAMBLE_RESULT_GOOD 结果事件（69A5F0/698F90/432EA0）
{
  void *v5; // eax
  int fld_98; // eax  | +0x0098 → ★ 页签选择值（0x63D940: = nArg3；1→A 可见、0→B 可见，两按钮互斥驱动）（CNRDLotteryItemWindow；va=0063D940）

  if ( nArg2 == 0 )  // 若 nArg2 == 0
    return 0;
  *(uint32_t *)(this + 152) = nArg3;  // this+152 = nArg3
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2) + 4) == 0 )  // 调用虚函数（虚表槽 +16）
    return 0;
  *(uint32_t *)(this + 104) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2) + 68);  // 调用虚函数（虚表槽 +16）
  *(uint32_t *)(this + 136) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 24))(nArg2);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  v5 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 108))(nArg2);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
  sub_4015C0(v5, strlen((const char *)v5));  // 【std::string构造赋值】
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) / 2,
    (480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) / 2);
  *(uint8_t *)(*(uint32_t *)(this + 36) + 16) = *(uint32_t *)(this + 152) == 1;  // this+144 = pFrameList144
  *(uint8_t *)(*(uint32_t *)(this + 40) + 16) = *(uint32_t *)(this + 152) == 0;
  fld_98 = *(uint32_t *)(this + 152);  // fld_98 = this+152
  if ( fld_98 == 0 )  // 若 fld_98 == 0
  {
    *(uint32_t *)(this + 156) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2) + 4);  // 调用虚函数（虚表槽 +16）
    *(uint8_t *)(this + 173) = 0;  // this+692 = 表现/名字快照[3]
    *(uint8_t *)(this + 174) = 0;  // this+696 = 表现/名字快照[4]
    sub_698F90(this + 160, 4000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(uint8_t *)(this + 188) = 0;  // this+188 = 0
    sub_432EA0("GAMBLE_OPEN_LOOP", 4, 0, 0);  // 调 音效播放包装（非空判定）
    return 1;
  }
  if ( fld_98 == 1 )  // 若 fld_98 == 1
  {
    if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2) + 84) >= 2 )  // 调用虚函数（虚表槽 +16）
    {
      sub_432EA0("GAMBLE_RESULT_GOOD", -1, 0, 0);  // 调 音效播放包装（非空判定）
      return 1;
    }
    sub_432EA0("GAMBLE_RESULT_COMMON", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return 1;
}



// ------------------------------------------------------------
// 0x63DA90 sub_63DA90 —— 结果窗公共清理（37 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63DA90(uint32_t *this)  // 函数: 结果窗公共清理（37 行）
{
  void (/*thiscall*/ ***fld_e9)(uint32_t, int); // ecx
  uint32_t *pThis_A; // esi
  int i; // ebx
  void (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  int result; // eax

  fld_e9 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);  // this+36 = 状态字
  if ( fld_e9 != nullptr )  // 若 fld_e9 非空
    (**fld_e9)(fld_e9, 1);
  *(this + 9) = 0;  // this+36 = 状态字
  pThis_A = this + 10;
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    if ( *pThis_A != 0 )  // 若 *pThis_A != 0
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_A)(*pThis_A, 1);
    *pThis_A++ = 0;  // *pThis_A++ 写入 0
  }
  fld_e12 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  if ( fld_e12 != nullptr )  // 若 fld_e12 非空
    (**fld_e12)(fld_e12, 1);
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);  // this+52 = bAuraState
  result = 0;
  *(this + 12) = 0;  // this+48 = 0
  if ( fld_e13 != nullptr )  // 若 fld_e13 非空
    result = (**fld_e13)(fld_e13, 1);
  *(this + 13) = 0;  // this+52 = bAuraState
  return result;
}



// ============================================================
// 【分区 29】分解结果窗 CNRDItemDisjointResultWindow（0x63DB00-0x63DF50）
// vmtC 播 DISSOLVE_ITEM 分解完成事件（44CA70 收尾）。
// ============================================================
// ------------------------------------------------------------
// 0x63DB00 CNRDItemDisjointResultWindow__vmt0 —— CNRDItemDisjointResultWindow__vmt0 构造（69C690 + 418DD0）
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDItemDisjointResultWindow__vmt0(unsigned int *this, int pArg2)  // 函数: CNRDItemDisjointResultWindow__vmt0 构造（69C690 + 418DD0）
{
  unsigned int result; // eax
  int v4; // ebx
  int pResultListCtrl; // edi  | +0x0034 → 结果列表控件（0x63DED0: *(this+52) 经其 vt+32(0) 复位滚动）（CNRDItemDisjointResultWindow；va=0063DED0）
  unsigned int v6; // edi
  int pObj; // eax
  int v8; // edi
  int fld_e29; // ecx
  uint32_t *fld_e292; // eax
  uint32_t *v11; // edx
  int v12; // [esp+8h] [ebp-8h]
  int v13; // [esp+Ch] [ebp-4h]
  int v14; // [esp+18h] [ebp+8h]

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v4 = 0;
    v13 = *(uint32_t *)(pArg2 + 20);  // v13 = pArg2+20
    v12 = 0;
    v14 = *(uint32_t *)(pArg2 + 24) + 59;
    do
    {
      pResultListCtrl = sub_69C690(*(this + 13));  // 调 取设备对象 +112 字段（类型或句柄）
      result = *(this + 29);  // result = this+29
      v6 = v4 + pResultListCtrl;
      if ( result != 0 )  // 若 result != 0
      {
        result = (int)(*(this + 30) - result) / 52;  // this+120 = 动画对象指针
        if ( result > v6 )  // 若 result > v6
        {
          pObj = sub_418DD0(90);  // 调 sub_418DD0
          if ( pObj != 0 )  // 若 pObj != 0
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
              pObj,
              v13 + 11,
              v14 - 10,
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              1065353216,
              1065353216,
              0,
              872415231,
              1333788672,
              1333788672);
          v8 = 52 * v6;
          fld_e29 = *(uint32_t *)(*(this + 29) + v8 + 4);
          if ( fld_e29 != 0 )  // 若 fld_e29 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e29 + 152))(fld_e29, v13 + 12, v14 - 9, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          (*(void (/*thiscall*/ **)(int, unsigned int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 15);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
          fld_e292 = (uint32_t *)(*(this + 29) + v8);
          if ( fld_e292[8] < 0x10u )  // 若 fld_e292[8] < 0x10u
            v11 = fld_e292 + 3;
          else
            v11 = (uint32_t *)fld_e292[3];
          (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            v13 + 6,
            v14,
            fld_e292[9],
            v11);
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
          v4 = v12;
        }
      }
      v12 = ++v4;
      v14 += 39;
    }
    while ( v4 < 3 );  // 当 v4 < 3 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x63DC50 sub_63DC50 —— 分解结果页绘制（69A5F0/69C460/69C480/69C440 + 43C410/69A840 + 426BD0/69C780/69CA20/43C630，105 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63DC50(uint32_t *this)  // 函数: 分解结果页绘制（69A5F0/69C460/69C480/69C440 + 43C410/69A840 + 426BD0/6…
{
  int v2; // edx
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  int v5; // ebx
  uint8_t *pMem2; // edi
  uint8_t *pMem3; // eax
  uint32_t *pMem32; // edi
  int fld_e14; // ebx
  uint8_t *pMem4; // eax
  uint8_t *fld_e10; // eax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-14h]
  uint32_t *pThis_A; // [esp+10h] [ebp-10h]

  v2 = *this;
  *(this + 14) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+56 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(228, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  sub_69A5F0((uint32_t *)*(this + 3), 44, 20);  // this+12 = 技能槽记录次字
  sub_69C460(1);  // 调 sub_69C460
  sub_69C480(-16777216);  // 调 sub_69C480
  sub_69C440(-1);  // 调 sub_69C440
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 19, 15);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v4 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v4 = nullptr;  // v4 = nullptr 空指针
  *(this + 9) = v4;  // this+36 = 状态字
  sub_69A5F0(v4, 94, 169);  // 调 sub_69A5F0
  sub_69A840(*(this + 9));  // this+36 = 状态字
  v5 = 4;
  pThis_A = this + 10;
  do
  {
    pMem2 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem2 != nullptr )  // 若 pMem2 非空
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(pMem2);  // 调 nengine::IControl 构造
      *(uint32_t *)pMem2 = &vftbl_nengine__CNButton;
      sub_69C780(pMem2);  // 调 sub_69C780
      nengine__CNButton__vmt20(Block, v5, v5, v5 + 1, v5, 0, 0);
    }
    else
    {
      pMem2 = nullptr;  // pMem2 = nullptr 空指针
    }
    *pThis_A = pMem2;  // *pThis_A 写入 pMem2
    v5 += 2;
    ++pThis_A;  // 自增pThis_A
  }
  while ( v5 < 8 );  // 当 v5 < 8 循环
  pMem3 = operator new(0x88u);  // operator new 分配 136 字节
  pMem32 = pMem3;
  if ( pMem3 != nullptr )  // 若 pMem3 非空
  {
    fld_e14 = *(this + 14);  // fld_e14 = this+14
    sub_426BD0(pMem3);  // 调 nengine::IControl 构造
    *pMem32 = &vftbl_nengine__CNSlider;  // *pMem32 写入 &vftbl_nengine__CNSlider
    sub_69CA20(pMem32);  // 调 sub_69CA20
    nengine__CNSlider__vmt20(fld_e14, 87, 88);
    *pMem32 = &vftbl_nengine__CNVSlider;  // *pMem32 写入 &vftbl_nengine__CNVSlider
  }
  else
  {
    pMem32 = nullptr;  // pMem32 = nullptr 空指针
  }
  *(this + 12) = pMem32;  // this+48 = pMem32
  pMem4 = operator new(0x74u);  // operator new 分配 116 字节
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    fld_e10 = sub_43C630(pMem4, *(this + 10), *(this + 11), *(this + 12));  // 调 nengine::CNVScroll 构造
  else
    fld_e10 = nullptr;  // fld_e10 = nullptr 空指针
  *(this + 13) = fld_e10;  // this+52 = bAuraState
  sub_69A5F0(fld_e10, 218, 49);  // 调 sub_69A5F0
  sub_69A840(*(this + 13));  // this+52 = bAuraState
  *(this + 18) = 0;  // this+72 = 0
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 25) = 0;  // this+100 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 27) = 0;  // this+108 = 0
  *((uint8_t *)this + 60) = 0;
  *((uint8_t *)this + 61) = 0;
  *((uint8_t *)this + 62) = 0;
  *((uint8_t *)this + 63) = 0;
  *(this + 19) = 6;  // this+76 = 6
  *(this + 20) = 12;  // this+80 = nAuraStage
  *(this + 22) = 1600;  // this+88 = pFxObjB
  result = dword_99FCCC;
  *(this + 27) = dword_99FCCC;  // this+108 = dword_99FCCC
  *(this + 22) = 228;  // this+88 = pFxObjB
  *(this + 18) = 1;  // this+72 = 1
  *(this + 16) = -16777216;  // this+64 = -16777216
  return result;
}



// ------------------------------------------------------------
// 0x63DED0 CNRDItemDisjointResultWindow__vmtC —— CNRDItemDisjointResultWindow__vmtC 播放 DISSOLVE_ITEM 分解完成事件（44CA70 收尾 + 432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemDisjointResultWindow__vmtC(int this, int nArg2, int nArg3)  // 函数: CNRDItemDisjointResultWindow__vmtC 播放 DISSOLVE_ITEM 分解完成事件（44CA70 收尾 + 432EA0）
{
  char *v4; // eax

  sub_69C340(-1);  // 调 sub_69C340
  v4 = sub_422E70(963);  // 调 sub_422E70
  sub_69C360(v4, 0);  // 调 sub_69C360
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) / 2,
    (480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) / 2);
  sub_44CA70((int *)(this + 112));  // 调 52 字节记录数组析构释放
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 52) + 32))(*(uint32_t *)(this + 52), 0);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  sub_432EA0("DISSOLVE_ITEM", -1, 0, 0);  // 调 音效播放包装（非空判定）
  return 1;
}



// ============================================================
// 【分区 30】奖励文本辅助（0x63DF50-0x63E200）
// 459700/45A340/477AF0 = 结算奖励文本拼装（被副本/交易/合成结果窗共用）。
// ============================================================
// ------------------------------------------------------------
// 0x63DF50 sub_63DF50 —— 奖励文本缓冲（4014D0）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_63DF50(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 函数: 奖励文本缓冲（4014D0）
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
    uArg32[1] = uArg12[1];  // uArg32[1] 写入 uArg12[1]
    sub_4014D0((std::_String_base *)(uArg32 + 2), uArg12 + 2, 0, -1);  // 调 std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    uArg32[9] = uArg12[9];  // uArg32[9] 写入 uArg12[9]
    uArg32[10] = uArg12[10];  // uArg32[10] 写入 uArg12[10]
    uArg32[11] = uArg12[11];  // uArg32[11] 写入 uArg12[11]
    uArg32[12] = uArg12[12];  // uArg32[12] 写入 uArg12[12]
    uArg12 += 13;
    uArg32 += 13;
  }
  while ( uArg12 != uArg2 );  // 当 uArg12 != uArg2 循环
  return uArg32;
}



// ------------------------------------------------------------
// 0x63DFB0 sub_63DFB0 —— 奖励文本拼装（459700/4014D0/63DF50 + 477AF0 + 45A340，112 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_63DFB0(uint32_t *this, int *pDwArg2, int nArg3)  // 函数: 奖励文本拼装（459700/4014D0/63DF50 + 477AF0 + 45A340，112 行）
{
  uint32_t *pThis; // edi
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
  int nArg322; // [esp-4h] [ebp-D8h]
  char Buffer[128]; // [esp+10h] [ebp-C4h] BYREF
  int v19; // [esp+90h] [ebp-44h] BYREF
  int v20; // [esp+94h] [ebp-40h]
  uint8_t v21[28]; // [esp+98h] [ebp-3Ch] BYREF
  int v22; // [esp+B4h] [ebp-20h]
  int nArg32; // [esp+B8h] [ebp-1Ch]
  int v24; // [esp+BCh] [ebp-18h]
  int v25; // [esp+C0h] [ebp-14h]
  int dword_796E502; // [esp+C4h] [ebp-10h]
  int v27; // [esp+D0h] [ebp-4h]
  int v28; // [esp+DCh] [ebp+8h]

  pThis = this;
  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  v28 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 16))(pDwArg2) + 4);  // 调用虚函数（虚表槽 +16）
  sub_459700(&v19);  // 调 52 字节元素默认初始化
  v5 = (int *)pThis[29];
  v6 = (int *)pThis[30];
  v27 = 0;
  if ( v5 != v6 )  // 若 v5 != v6
  {
    while ( *v5 != v28 )  // 当 *v5 != v28 循环
    {
      v5 += 13;
      if ( v5 == v6 )  // 若 v5 == v6
        goto LABEL_6;  // 跳转 LABEL_6
    }
    v19 = *v5;
    v20 = v5[1];
    sub_4014D0((std::_String_base *)v21, v5 + 2, 0, -1);  // 调 std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    v22 = v5[9];
    nArg32 = v5[10];
    v24 = v5[11];
    v25 = v5[12];
    nArg32 += nArg3;  // nArg32 累加 nArg3
  }
LABEL_6:
  if ( v5 == (int *)pThis[30] )  // 若 v5 == (int *)pThis[30]
  {
    v7 = *pDwArg2;
    v19 = v28;
    v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 16))(pDwArg2);  // 调用虚函数（虚表槽 +16）
    v9 = *pDwArg2;
    v20 = *(uint32_t *)(v8 + 68);  // v20 = v8+68
    v22 = (*(int (/*thiscall*/ **)(int *))(v9 + 24))(pDwArg2);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
    nArg32 = nArg3;
  }
  else
  {
    sub_63DF50(v5 + 13, (uint32_t *)pThis[30], v5);  // 调 奖励文本缓冲（4014D0）
    v10 = pThis[30];
    v11 = v10 - 52;
    do
    {
      sub_477AF0(v11);  // 调 sub_477AF0
      v11 += 52;
    }
    while ( v11 != v10 );  // 当 v11 != v10 循环
    *(this + 30) -= 52;  // this+120 = 动画对象指针
    pThis = this;
  }
  if ( v28 != 0 )  // 若 v28 != 0
  {
    v14 = (void *)(*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 108))(pDwArg2);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
    if ( nArg32 <= 1 )  // 若 nArg32 <= 1
    {
      sub_4015C0(v14, strlen((const char *)v14));  // 【std::string构造赋值】
    }
    else
    {
      sprintf(Buffer, "%s x%d", (const char *)v14, nArg32);  // 调 格式化到缓冲
      sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
    }
  }
  else
  {
    v12 = sub_418DD0(10);  // 调 sub_418DD0
    nArg322 = nArg32;
    v20 = v12;
    v13 = sub_422E70(964);  // 调 sub_422E70
    sprintf(Buffer, v13, nArg322);  // 调 格式化到缓冲
    sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
  }
  sub_45A340((int)(pThis + 28), &v19);  // 调 52 字节向量尾插
  v15 = pThis[29];
  if ( v15 != 0 )  // 若 v15 != 0
    v15 = (pThis[30] - v15) / 52;
  (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pThis[13] + 32))(pThis[13], v15 - 3 <= 0 ? 0 : v15 - 3);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  v27 = -1;
  sub_477AF0((int)&v19);  // 调 sub_477AF0
}



// ------------------------------------------------------------
// 0x63E1E0 sub_63E1E0 —— 结果窗文案复位（17 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63E1E0(uint32_t *this)  // 函数: 结果窗文案复位（17 行）
{
  int (/*thiscall*/ ***fld_e9)(uint32_t, int); // ecx
  int result; // eax

  fld_e9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);  // this+36 = 状态字
  if ( fld_e9 != nullptr )  // 若 fld_e9 非空
    result = (**fld_e9)(fld_e9, 1);
  *(this + 9) = 0;  // this+36 = 状态字
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
unsigned int /*thiscall*/ CNRDPlayDungeonResultWindow__vmt0(unsigned int *this, int pArg2)  // 函数: CNRDPlayDungeonResultWindow__vmt0 构造（418DD0）
{
  unsigned int result; // eax
  int v4; // ebx
  int v5; // eax
  int i; // esi
  int pObj; // eax
  int fld_e12; // eax
  uint32_t *fld_e122; // eax
  uint32_t *v10; // edx
  int v11; // [esp+Ch] [ebp-8h]
  unsigned int v12; // [esp+10h] [ebp-4h]
  int v13; // [esp+1Ch] [ebp+8h]

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = 0;
    v11 = v4;
    v12 = 0;
    for ( i = *(uint32_t *)(pArg2 + 24) + 58; ; i += 39 )  // 循环：i = *(uint32_t *)(pArg2 + 24) + 58; ; i += 39
    {
      v13 = v5;
      result = *(this + 12);  // result = this+12
      if ( result == 0 )  // 若 result == 0
        break;
      result = (int)(*(this + 13) - result) / 52;  // this+52 = bAuraState
      if ( v12 >= result )  // 若 v12 >= result
        break;
      pObj = sub_418DD0(90);  // 调 sub_418DD0
      if ( pObj != 0 )  // 若 pObj != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
          pObj,
          v4 + 12,
          i - 9,
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          1065353216,
          1065353216,
          0,
          872415231,
          1333788672,
          1333788672);
      fld_e12 = *(uint32_t *)(v13 + *(this + 12) + 4);
      if ( fld_e12 != 0 )  // 若 fld_e12 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e12 + 152))(fld_e12, v4 + 13, i - 8, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      (*(void (/*thiscall*/ **)(int, unsigned int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 15);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
      fld_e122 = (uint32_t *)(*(this + 12) + v13);
      if ( fld_e122[8] < 0x10u )  // 若 fld_e122[8] < 0x10u
        v10 = fld_e122 + 3;
      else
        v10 = (uint32_t *)fld_e122[3];
      v4 = v11;
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        v11 + 20,
        i,
        fld_e122[9],
        v10);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
      ++v12;  // 自增v12
      v5 = v13 + 52;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63E340 CNRDPlayDungeonResultWindow__vmt3C —— CNRDPlayDungeonResultWindow__vmt3C 翻页动作（69C440/69C340/69C360 + 418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPlayDungeonResultWindow__vmt3C(int *this, int pArg2)  // 函数: CNRDPlayDungeonResultWindow__vmt3C 翻页动作（69C440/69C340/69C360 + 418DD0）
{
  int v3; // eax
  char *v4; // eax
  int v5; // ebx
  int v6; // eax
  char *v8; // [esp-8h] [ebp-98h]
  int v9; // [esp-4h] [ebp-94h]
  char Buffer[128]; // [esp+Ch] [ebp-84h] BYREF
  int dword_796E502; // [esp+8Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  if ( *(uint32_t *)(pArg2 + 28) < 0x10u )  // 若 *(uint32_t *)(pArg2 + 28) < 0x10u
    v3 = pArg2 + 8;
  else
    v3 = *(uint32_t *)(pArg2 + 8);  // v3 = pArg2+8
  v9 = v3;
  v4 = sub_422E70(1131);  // 调 sub_422E70
  sprintf(Buffer, v4, v9);  // 调 格式化到缓冲
  sub_69C440(-5395027);  // 调 sub_69C440
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C360(Buffer, 0);  // 调 sub_69C360
  v5 = *this;
  v8 = sub_422E70(1132);  // 调 sub_422E70
  v6 = sub_418DD0(57);  // 调 sub_418DD0
  return (*(int (/*thiscall*/ **)(int *, int, char *, int))(v5 + 64))(this, v6, v8, -13421569);  // 调用虚函数（虚表槽 +64）【推断: 取观察者容器（懒创建 0x44 字节 sb_499960(thi…】
}



// ------------------------------------------------------------
// 0x63E400 sub_63E400 —— 副本结算页绘制（69A5F0/69C3C0/69C460/69C480 + 43C410/69A840，47 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63E400(uint32_t *this)  // 函数: 副本结算页绘制（69A5F0/69C3C0/69C460/69C480 + 43C410/69A840，47 行）
{
  int v2; // edx
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  int result; // eax

  v2 = *this;
  *(this + 10) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+40 = 状态子标志
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(216, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  sub_69A5F0((uint32_t *)*(this + 3), 6, 19);  // this+12 = 技能槽记录次字
  sub_69C3C0(1);  // 调 sub_69C3C0
  sub_69C460(1);  // 调 sub_69C460
  sub_69C480(-16777216);  // 调 sub_69C480
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v4 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v4 = nullptr;  // v4 = nullptr 空指针
  *(this + 9) = v4;  // this+36 = 状态字
  result = sub_69A840(v4);  // 调 sub_69A840
  *((uint8_t *)this + 60) = 0;
  *((uint8_t *)this + 61) = 0;
  *((uint8_t *)this + 62) = 0;
  *((uint8_t *)this + 63) = 0;
  *(this + 18) = 0;  // this+72 = 0
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 25) = 0;  // this+100 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 27) = 0;  // this+108 = 0
  *(this + 19) = 6;  // this+76 = 6
  *(this + 20) = 12;  // this+80 = nAuraStage
  *(this + 22) = 1600;  // this+88 = pFxObjB
  *(this + 27) = dword_99FCCC;  // this+108 = dword_99FCCC
  *(this + 22) = 216;  // this+88 = pFxObjB
  *(this + 18) = 1;  // this+72 = 1
  *(this + 16) = -16777216;  // this+64 = -16777216
  return result;
}



// ------------------------------------------------------------
// 0x63E520 CNRDPlayDungeonResultWindow__vmt38 —— CNRDPlayDungeonResultWindow__vmt38 翻页动作（69C440/69C340/422E70/69C360 + 4CE8A0/40BEA0 经验结算）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPlayDungeonResultWindow__vmt38(int *this, uint32_t *pArg2, int i)  // 函数: CNRDPlayDungeonResultWindow__vmt38 翻页动作（69C440/69C340/422E70/69C360 + 4CE8A0/40BEA0 经验结算）
{
  char *v4; // eax
  bool v5; // cf
  const char *v6; // eax
  int v7; // esi
  int v8; // eax
  const char *psz; // eax
  const char *psz2; // esi
  unsigned int nLen; // eax
  char *v12; // edi
  char v13; // cl
  int v14; // edx
  int result; // eax
  uint32_t *v16; // esi
  int v17; // eax
  uint32_t *v18; // esi
  int v19; // [esp+8h] [ebp-88h] BYREF
  char Buffer[128]; // [esp+Ch] [ebp-84h] BYREF
  int dword_796E502; // [esp+8Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  sub_69C440(-1);  // 调 sub_69C440
  sub_69C340(-1);  // 调 sub_69C340
  v4 = sub_422E70(1133);  // 调 sub_422E70
  sub_69C360(v4, 0);  // 调 sub_69C360
  v5 = pArg2[7] < 0x10u;
  v19 = 0;
  if ( v5 )  // 若 v5
    v6 = (const char *)(pArg2 + 2);
  else
    v6 = (const char *)pArg2[2];
  sprintf(Buffer, "%s - ", v6);  // 调 格式化到缓冲
  v7 = i;
  switch ( i )  // 分支：按 i 分派
  {
    case 1:
      v8 = sub_418DD0(146);  // 调 sub_418DD0
      break;
    case 2:
      v8 = sub_418DD0(147);  // 调 sub_418DD0
      break;
    case 3:
      v8 = sub_418DD0(148);  // 调 sub_418DD0
      break;
    default:
      goto LABEL_11;  // 跳转 LABEL_11
  }
  v19 = v8;
LABEL_11:
  switch ( v7 )  // 分支：按 v7 分派
  {
    case 1:
      psz = "EXPERT'S ROAD";
      break;
    case 2:
      psz = "MASTER'S ROAD";
      break;
    case 3:
      psz = "KING'S ROAD";
      break;
    default:
      psz = szPassword;
      break;
  }
  psz2 = psz;
  nLen = strlen(psz) + 1;  // 调 返回字符串长度（逐字节扫描）
  v12 = (char *)&v19 + 3;
  do
    v13 = *++v12;
  while ( v13 != 0 );  // 当 v13 != 0 循环
  v14 = *this;
  qmemcpy(v12, psz2, nLen);  // 调 内存块拷贝(内联展开)
  result = (*(int (/*thiscall*/ **)(int *, int, char *, int))(v14 + 64))(this, v19, Buffer, -1);  // 调用虚函数（虚表槽 +64）【推断: 取观察者容器（懒创建 0x44 字节 sb_499960(thi…】
  if ( i == 1 )  // 若 i == 1
  {
    result = *(uint32_t *)dword_9B6D7C;
    for ( i = *(uint32_t *)dword_9B6D7C; i != dword_9B6D7C; result = i )  // 循环：i = *(uint32_t *)dword_9B6D7C; i != dword_9B6D7C; result = i
    {
      v16 = (uint32_t *)sub_4CE8A0(*(uint32_t *)(result + 12));
      if ( v16[23] == *pArg2 )  // 若 v16[23] == *pArg2
      {
        v17 = sub_418DD0(123);  // 调 sub_418DD0
        if ( v16[7] < 0x10u )  // 若 v16[7] < 0x10u
          v18 = v16 + 2;
        else
          v18 = (uint32_t *)v16[2];
        (*(void (/*thiscall*/ **)(int *, int, uint32_t *, int))(*this + 64))(this, v17, v18, -1);  // 调用虚函数（虚表槽 +64）【推断: 取观察者容器（懒创建 0x44 字节 sb_499960(thi…】
      }
      sub_40BEA0(&i);  // 调 红黑树迭代器自增（后继；哨兵位 +45）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63E6B0 CNRDPlayDungeonResultWindow__vmtC —— CNRDPlayDungeonResultWindow__vmtC 播 REWARD_OPEN2 奖励面板事件（44CA70 + 432EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPlayDungeonResultWindow__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDPlayDungeonResultWindow__vmtC 播 REWARD_OPEN2 奖励面板事件（44CA70 + 432EA0）
{
  sub_44CA70(this + 11);  // 调 52 字节记录数组析构释放
  sub_432EA0("REWARD_OPEN2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  return 1;
}



// ------------------------------------------------------------
// 0x63E6D0 CNRDPlayDungeonResultWindow__vmt40 —— CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/4015C0/45A340 + 69A5F0/477AF0）
// ------------------------------------------------------------
void /*thiscall*/ CNRDPlayDungeonResultWindow__vmt40(int *this, int nArg2, void *Src, int nArg4)  // 函数: CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/4015C0/45A340 + 69A5F0/477AF0）
{
  int fld_e12; // eax
  uint32_t *fld_e2; // ecx
  int v7; // ebx
  int v8; // edi
  uint32_t v9[14]; // [esp+Ch] [ebp-44h] BYREF
  int v10; // [esp+4Ch] [ebp-4h]

  v9[13] = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  sub_459700(v9);  // 调 52 字节元素默认初始化
  v9[1] = nArg2;
  v10 = 0;
  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  v9[9] = nArg4;
  sub_45A340((int)(this + 11), v9);  // 调 52 字节向量尾插
  fld_e12 = *(this + 12);  // fld_e12 = this+12
  if ( fld_e12 != 0 )  // 若 fld_e12 != 0
    fld_e12 = (*(this + 13) - fld_e12) / 52;  // this+52 = bAuraState
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 18, 3 * fld_e12 + 6);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v7 = (480 - fld_e2[8]) / 2;
  v8 = (640 - fld_e2[7]) / 2;
  sub_69A5F0(fld_e2, v8, v7);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v8 + 88, *(uint32_t *)(*(this + 2) + 32) + v7 - 37);  // this+36 = 状态字
  v10 = -1;
  sub_477AF0((int)v9);  // 调 sub_477AF0
}



// ------------------------------------------------------------
// 0x63E7E0 sub_63E7E0 —— 副本结算数据（16 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63E7E0(uint32_t *this)  // 函数: 副本结算数据（16 行）
{
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = bAuraState
  *(this + 14) = 0;  // this+56 = 0
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

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  if ( *(this + 32) != 0xFFFF && sub_429830((uint32_t *)dword_8F8500, *((uint16_t *)this + 64)) == 0 )  // 调 表按键查找（uint16）
    *(this + 32) = 0xFFFF;  // 常量 0xFFFF（= 0xFFFF）
  result = (uint8_t *)*(this + 9);  // this+36 = 状态字
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x63E870 CNRDItemTradeResultWindow__vmt10 —— CNRDItemTradeResultWindow__vmt10 状态切换槽（17 行）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemTradeResultWindow__vmt10(uint32_t *this)  // 函数: CNRDItemTradeResultWindow__vmt10 状态切换槽（17 行）
{
  int result; // eax

  if ( *(this + 32) == 0xFFFF )  // 若 *(this + 32) == 0xFFFF
  {
    result = *(this + 4);  // result = this+4
    *(uint32_t *)(*(uint32_t *)(result + 2444) + 10108) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x63E890 CNRDItemTradeResultWindow__vmt0 —— CNRDItemTradeResultWindow__vmt0 构造（103 行：418DD0/429830/42B340/69C690）
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDItemTradeResultWindow__vmt0(int this, int pArg2)  // 函数: CNRDItemTradeResultWindow__vmt0 构造（103 行：418DD0/429830/42B340/69C690）
{
  unsigned int result; // eax
  int v4; // ebx
  int v5; // edi
  int pObj3; // eax
  int nFailReasonId; // eax  | +0x0080 → 失败原因 id（CNRDItemTradeResultWindow；va=0063E890）
  int pObj2; // eax
  int v9; // ebx
  int pListCtrl; // edi  | +0x0034 → 列表控件（0x63E890: sub_69C690(*(this+52)) 取滚动偏移；行高 39px）（CNRDItemTradeResultWindow；va=0063E890）
  unsigned int v11; // edi
  int pObj; // eax
  int v13; // edi
  int pEntryVecBegin; // ecx  | +0x0074 → 结果条目向量 begin（0x63E890: result=*(this+116)；元素 52 字节）（CNRDItemTradeResultWindow；va=0063E890）
  uint32_t *fld_742; // eax
  uint32_t *v16; // edx
  int v17; // [esp+8h] [ebp-8h]
  int v18; // [esp+Ch] [ebp-4h]
  int v19; // [esp+18h] [ebp+8h]

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(uint32_t *)(this + 8) )  // 若 pArg2 == *(uint32_t *)(this + 8)
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
    v18 = v4;
    if ( *(uint32_t *)(this + 128) != 0xFFFF )  // 若 *(uint32_t *)(this + 128) != 0xFFFF
    {
      pObj3 = sub_418DD0(89);  // 调 sub_418DD0
      if ( pObj3 != 0 )  // 若 pObj3 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v4 + 15, v5 + 11, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      nFailReasonId = sub_429830((uint32_t *)dword_8F8500, *(uint16_t *)(this + 128));  // 调 表按键查找（uint16）
      if ( nFailReasonId != 0 )  // 若 fld_80 != 0
      {
        pObj2 = sub_42B340(nFailReasonId);  // 调 虚拟角色惰性创建（0x294 字节）
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj2 + 384))(  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
          pObj2,
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
      pListCtrl = sub_69C690(*(uint32_t *)(this + 52));  // 调 取设备对象 +112 字段（类型或句柄）
      result = *(uint32_t *)(this + 116);  // result = this+116
      v11 = v9 + pListCtrl;
      if ( result != 0 )  // 若 result != 0
      {
        result = (int)(*(uint32_t *)(this + 120) - result) / 52;
        if ( result > v11 )  // 若 result > v11
        {
          pObj = sub_418DD0(90);  // 调 sub_418DD0
          if ( pObj != 0 )  // 若 pObj != 0
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
              pObj,
              v18 + 11,
              v19 - 10,
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              1065353216,
              1065353216,
              0,
              872415231,
              1333788672,
              1333788672);
          v13 = 52 * v11;
          pEntryVecBegin = *(uint32_t *)(v13 + *(uint32_t *)(this + 116) + 4);
          if ( pEntryVecBegin != 0 )  // 若 fld_74 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pEntryVecBegin + 152))(pEntryVecBegin, v18 + 12, v19 - 9, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 60);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
          fld_742 = (uint32_t *)(v13 + *(uint32_t *)(this + 116));
          if ( fld_742[8] < 0x10u )  // 若 fld_742[8] < 0x10u
            v16 = fld_742 + 3;
          else
            v16 = (uint32_t *)fld_742[3];
          (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            v18 + 6,
            v19,
            fld_742[9],
            v16);
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
          v9 = v17;
        }
      }
      v17 = ++v9;
      v19 += 39;
    }
    while ( v9 < 3 );  // 当 v9 < 3 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x63EA50 sub_63EA50 —— 交易结果页绘制（69A5F0/69C460/69C480/69C440 + 43C410/69A840 + 426BD0/69C780/69CA20/43C630，105 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_63EA50(uint32_t *this)  // 函数: 交易结果页绘制（69A5F0/69C460/69C480/69C440 + 43C410/69A840 + 426BD0/6…
{
  int v2; // edx
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  int v5; // ebx
  uint8_t *pMem2; // edi
  uint8_t *pMem3; // eax
  uint32_t *pMem32; // edi
  int fld_e14; // ebx
  uint8_t *pMem4; // eax
  uint8_t *fld_e10; // eax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-14h]
  uint32_t *pThis_A; // [esp+10h] [ebp-10h]

  v2 = *this;
  *(this + 14) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+56 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(228, 2048);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  sub_69A5F0((uint32_t *)*(this + 3), 44, 20);  // this+12 = 技能槽记录次字
  sub_69C460(1);  // 调 sub_69C460
  sub_69C480(-16777216);  // 调 sub_69C480
  sub_69C440(-1);  // 调 sub_69C440
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 19, 15);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v4 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v4 = nullptr;  // v4 = nullptr 空指针
  *(this + 9) = v4;  // this+36 = 状态字
  sub_69A5F0(v4, 94, 169);  // 调 sub_69A5F0
  sub_69A840(*(this + 9));  // this+36 = 状态字
  v5 = 4;
  pThis_A = this + 10;
  do
  {
    pMem2 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem2 != nullptr )  // 若 pMem2 非空
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(pMem2);  // 调 nengine::IControl 构造
      *(uint32_t *)pMem2 = &vftbl_nengine__CNButton;
      sub_69C780(pMem2);  // 调 sub_69C780
      nengine__CNButton__vmt20(Block, v5, v5, v5 + 1, v5, 0, 0);
    }
    else
    {
      pMem2 = nullptr;  // pMem2 = nullptr 空指针
    }
    *pThis_A = pMem2;  // *pThis_A 写入 pMem2
    v5 += 2;
    ++pThis_A;  // 自增pThis_A
  }
  while ( v5 < 8 );  // 当 v5 < 8 循环
  pMem3 = operator new(0x88u);  // operator new 分配 136 字节
  pMem32 = pMem3;
  if ( pMem3 != nullptr )  // 若 pMem3 非空
  {
    fld_e14 = *(this + 14);  // fld_e14 = this+14
    sub_426BD0(pMem3);  // 调 nengine::IControl 构造
    *pMem32 = &vftbl_nengine__CNSlider;  // *pMem32 写入 &vftbl_nengine__CNSlider
    sub_69CA20(pMem32);  // 调 sub_69CA20
    nengine__CNSlider__vmt20(fld_e14, 87, 88);
    *pMem32 = &vftbl_nengine__CNVSlider;  // *pMem32 写入 &vftbl_nengine__CNVSlider
  }
  else
  {
    pMem32 = nullptr;  // pMem32 = nullptr 空指针
  }
  *(this + 12) = pMem32;  // this+48 = pMem32
  pMem4 = operator new(0x74u);  // operator new 分配 116 字节
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    fld_e10 = sub_43C630(pMem4, *(this + 10), *(this + 11), *(this + 12));  // 调 nengine::CNVScroll 构造
  else
    fld_e10 = nullptr;  // fld_e10 = nullptr 空指针
  *(this + 13) = fld_e10;  // this+52 = bAuraState
  sub_69A5F0(fld_e10, 218, 49);  // 调 sub_69A5F0
  sub_69A840(*(this + 13));  // this+52 = bAuraState
  *(this + 18) = 0;  // this+72 = 0
  *(this + 21) = 0;  // this+84 = pFxObjA
  *(this + 23) = 0;  // this+92 = pFxObjC
  *(this + 24) = 0;  // this+96 = 0
  *(this + 25) = 0;  // this+100 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 27) = 0;  // this+108 = 0
  *((uint8_t *)this + 60) = 0;
  *((uint8_t *)this + 61) = 0;
  *((uint8_t *)this + 62) = 0;
  *((uint8_t *)this + 63) = 0;
  *(this + 19) = 6;  // this+76 = 6
  *(this + 20) = 12;  // this+80 = nAuraStage
  *(this + 22) = 1600;  // this+88 = pFxObjB
  result = dword_99FCCC;
  *(this + 27) = dword_99FCCC;  // this+108 = dword_99FCCC
  *(this + 22) = 228;  // this+88 = pFxObjB
  *(this + 18) = 1;  // this+72 = 1
  *(this + 16) = -16777216;  // this+64 = -16777216
  return result;
}



// ------------------------------------------------------------
// 0x63ECD0 CNRDItemTradeResultWindow__vmtC —— CNRDItemTradeResultWindow__vmtC 收尾（429830 + 69C340/69C360 + 44CA70）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemTradeResultWindow__vmtC(int this, int nArg2, int nArg3)  // 函数: CNRDItemTradeResultWindow__vmtC 收尾（429830 + 69C340/69C360 + 44CA70）
{
  int nFailReasonId; // eax  | +0x0080 → 失败原因 id（CNRDItemTradeResultWindow；va=0063E890）
  int v6; // eax
  char *v7; // [esp-8h] [ebp-90h]
  char *v8; // [esp-8h] [ebp-90h]
  int v9; // [esp-4h] [ebp-8Ch]
  int v10; // [esp-4h] [ebp-8Ch]
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int dword_796E502; // [esp+84h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  *(uint32_t *)(this + 128) = nArg3;  // this+128 = nArg3
  if ( nArg3 == 0xFFFF )  // 若 nArg3 == 0xFFFF
  {
    v7 = sub_422E70(1114);  // 调 sub_422E70
    sprintf(Buffer, v7, v9);  // 调 格式化到缓冲
  }
  else
  {
    nFailReasonId = sub_429830((uint32_t *)dword_8F8500, *(uint16_t *)(this + 128));  // 调 表按键查找（uint16）
    if ( nFailReasonId == 0 )  // 若 fld_80 == 0
      return 0;
    if ( *(uint32_t *)(nFailReasonId + 40) < 0x10u )  // 若 *(uint32_t *)(fld_80 + 40) < 0x10u
      v6 = nFailReasonId + 20;
    else
      v6 = *(uint32_t *)(nFailReasonId + 20);  // v6 = fld_80+20
    v10 = v6;
    v8 = sub_422E70(1115);  // 调 sub_422E70
    sprintf(Buffer, v8, v10);  // 调 格式化到缓冲
  }
  sub_69C340(-1);  // 调 sub_69C340
  sub_69C360(Buffer, 0);  // 调 sub_69C360
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) / 2,
    (480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) / 2);
  sub_44CA70((int *)(this + 112));  // 调 52 字节记录数组析构释放
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 52) + 32))(*(uint32_t *)(this + 52), 0);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
  return 1;
}



// ------------------------------------------------------------
// 0x63EDD0 sub_63EDD0 —— 交易结果文本（459700/4015C0/422E70/45A340/477AF0，69 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_63EDD0(int this, int *pDwArg2)  // 函数: 交易结果文本（459700/4015C0/422E70/45A340/477AF0，69 行）
{
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  char *v9; // eax
  void *v10; // eax
  int fld_74; // eax
  int v12; // [esp-4h] [ebp-D0h]
  char Buffer[128]; // [esp+8h] [ebp-C4h] BYREF
  int v14; // [esp+88h] [ebp-44h] BYREF
  int v15; // [esp+8Ch] [ebp-40h]
  int v16; // [esp+ACh] [ebp-20h]
  int v17; // [esp+B0h] [ebp-1Ch]
  int dword_796E502; // [esp+BCh] [ebp-10h]
  int v19; // [esp+C8h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  sub_459700(&v14);  // 调 52 字节元素默认初始化
  v3 = *pDwArg2;
  v19 = 0;
  v4 = (*(int (/*thiscall*/ **)(int *))(v3 + 16))(pDwArg2);  // 调用虚函数（虚表槽 +16）
  v5 = *pDwArg2;
  v15 = *(uint32_t *)(v4 + 68);  // v15 = v4+68
  v16 = (*(int (/*thiscall*/ **)(int *))(v5 + 24))(pDwArg2);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  v6 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 44))(pDwArg2);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
  v7 = *pDwArg2;
  v17 = v6;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v7 + 16))(pDwArg2) + 4) != 0 )  // 调用虚函数（虚表槽 +16）
  {
    v10 = (void *)(*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 108))(pDwArg2);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
    if ( v17 <= 1 )  // 若 v17 <= 1
    {
      sub_4015C0(v10, strlen((const char *)v10));  // 【std::string构造赋值】
    }
    else
    {
      sprintf(Buffer, "%s x%d", (const char *)v10, v17);  // 调 格式化到缓冲
      sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
    }
  }
  else
  {
    v8 = sub_418DD0(10);  // 调 sub_418DD0
    v12 = v17;
    v15 = v8;
    v9 = sub_422E70(1116);  // 调 sub_422E70
    sprintf(Buffer, v9, v12);  // 调 格式化到缓冲
    sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
  }
  sub_45A340(this + 112, &v14);  // 调 52 字节向量尾插
  fld_74 = *(uint32_t *)(this + 116);  // fld_74 = this+116
  if ( fld_74 != 0 )  // 若 fld_74 != 0
    fld_74 = (*(uint32_t *)(this + 120) - fld_74) / 52;
  (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 52) + 32))(  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    *(uint32_t *)(this + 52),
    fld_74 - 3 <= 0 ? 0 : fld_74 - 3);
  v19 = -1;
  sub_477AF0((int)&v14);  // 调 sub_477AF0
}



// ------------------------------------------------------------
// 0x63EF60 sub_63EF60 —— 交易结果文本 2（63EDD0 + 4015C0）
// ------------------------------------------------------------
char /*thiscall*/ sub_63EF60(uint32_t *this, int *pDwArg2, char pszArg3, const char *pArg4)  // 函数: 交易结果文本 2（63EDD0 + 4015C0）
{
  int fld_e29; // eax
  int fld_e30; // esi
  char result; // al
  int fld_e292; // ecx
  int v9; // esi
  const char *v10; // ebx
  char *v11; // eax
  char Buffer[512]; // [esp+8h] [ebp-204h] BYREF
  int dword_796E502; // [esp+208h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  fld_e29 = *(this + 29);  // fld_e29 = this+29
  if ( fld_e29 != 0 )  // 若 fld_e29 != 0
    fld_e30 = (*(this + 30) - fld_e29) / 52;  // this+120 = 动画对象指针
  else
    fld_e30 = 0;
  sub_63EDD0((int)this, pDwArg2);  // 调 交易结果文本（459700/4015C0/422E70/45A340/477AF0，69 行）
  result = pszArg3;
  if ( pszArg3 == 0 )  // 若 pszArg3 == 0
  {
    fld_e292 = *(this + 29);  // fld_e292 = this+29
    v9 = 52 * fld_e30;
    if ( *(uint32_t *)(fld_e292 + v9 + 32) < 0x10u )  // 若 *(uint32_t *)(fld_e292 + v9 + 32) < 0x10u
      v10 = (const char *)(fld_e292 + v9 + 12);
    else
      v10 = *(const char **)(fld_e292 + v9 + 12);
    v11 = sub_422E70(1117);  // 调 sub_422E70
    sprintf(Buffer, "%s %s%s", v10, v11, pArg4);  // 调 格式化到缓冲
    return sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
  }
  return result;
}



// ============================================================
// 【分区 33】合成结果窗 CNRDCompoundResultWindow（0x63F020-0x63F4C0）
// ============================================================
// ------------------------------------------------------------
// 0x63F020 CNRDCompoundResultWindow__vmt0 —— CNRDCompoundResultWindow__vmt0 构造（418DD0/422E70）
// ------------------------------------------------------------
int /*thiscall*/ CNRDCompoundResultWindow__vmt0(int *this, int pArg2)  // 函数: CNRDCompoundResultWindow__vmt0 构造（418DD0/422E70）
{
  int result; // eax
  int v4; // ebx
  int v5; // esi
  int pObj2; // eax
  char *v7; // eax
  int v8; // esi
  int pObj; // eax
  int fld_e26; // ecx
  uint32_t *fld_e262; // eax
  uint32_t *v12; // edx
  bool v13; // zf
  int v14; // [esp+Ch] [ebp-8h]
  int v15; // [esp+10h] [ebp-4h]
  int v16; // [esp+10h] [ebp-4h]
  int v17; // [esp+1Ch] [ebp+8h]

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 2) )  // this+8 = 技能槽记录首字
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
    v14 = v4;
    pObj2 = sub_418DD0(dword_795D48 + 12);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v4 + 13, v5 + 16, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    v15 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    v7 = sub_422E70(934);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v15 + 80))(dword_79C0B0, v4 + 6, v5 + 27, -1, v7);  // 调用虚函数（虚表槽 +80）
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    result = *(this + 26);  // result = this+26
    if ( result != 0 )  // 若 result != 0
      result = (*(this + 27) - result) / 52;
    if ( result > 0 )  // 若 result > 0
    {
      v17 = 0;
      v8 = v5 + 72;
      v16 = result;
      do
      {
        pObj = sub_418DD0(90);  // 调 sub_418DD0
        if ( pObj != 0 )  // 若 pObj != 0
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
            pObj,
            v4 + 18,
            v8 - 10,
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            1065353216,
            1065353216,
            0,
            872415231,
            1333788672,
            1333788672);
        fld_e26 = *(uint32_t *)(v17 + *(this + 26) + 4);
        if ( fld_e26 != 0 )  // 若 fld_e26 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e26 + 152))(fld_e26, v4 + 19, v8 - 9, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
        fld_e262 = (uint32_t *)(v17 + *(this + 26));
        if ( fld_e262[8] < 0x10u )  // 若 fld_e262[8] < 0x10u
          v12 = fld_e262 + 3;
        else
          v12 = (uint32_t *)fld_e262[3];
        v4 = v14;
        (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          v14 + 6,
          v8,
          fld_e262[9],
          v12);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
        v8 += 39;
        result = v16 - 1;
        v13 = v16 == 1;
        v17 += 52;
        --v16;  // 自减v16
      }
      while ( !v13 );  // 当 !v13 循环
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63F1E0 sub_63F1E0 —— 合成结果清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_63F1E0(int this)  // 函数: 合成结果清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  int result; // eax

  *(uint32_t *)(this + 40) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+40 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  *(uint32_t *)(this + 44) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 96);  // this+44 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(uint32_t *)(this + 36) = v3;  // this+144 = pFrameList144
  sub_69A840(v3);  // 调 sub_69A840
  *(uint8_t *)(this + 48) = 0;  // this+48 = 0
  *(uint8_t *)(this + 49) = 0;  // this+49 = 0
  *(uint8_t *)(this + 50) = 0;  // this+50 = 0
  *(uint8_t *)(this + 51) = 0;  // this+51 = 0
  *(uint32_t *)(this + 60) = 0;  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint32_t *)(this + 80) = 0;  // this+80 = 0
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 96) = 0;  // this+384 = 动画件名 SSO 容量判据
  *(uint32_t *)(this + 64) = 6;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 68) = 12;  // this+68 = 12
  *(uint32_t *)(this + 76) = 1600;  // this+76 = 1600
  result = dword_99FCCC;
  *(uint32_t *)(this + 96) = dword_99FCCC;  // this+384 = 动画件名 SSO 容量判据
  *(uint32_t *)(this + 76) = 228;  // this+76 = 228
  *(uint32_t *)(this + 60) = 1;  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 52) = -16777216;  // this+52 = -16777216
  return result;
}



// ------------------------------------------------------------
// 0x63F2D0 CNRDCompoundResultWindow__vmtC —— CNRDCompoundResultWindow__vmtC 收尾（44CA70）
// ------------------------------------------------------------
char /*thiscall*/ CNRDCompoundResultWindow__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDCompoundResultWindow__vmtC 收尾（44CA70）
{
  if ( dword_795D48 == 4 )  // 若 dword_795D48 == 4
    return 0;
  sub_44CA70(this + 25);  // 调 52 字节记录数组析构释放
  return 1;
}



// ------------------------------------------------------------
// 0x63F2F0 sub_63F2F0 —— 合成结果文本（459700/4015C0/422E70/45A340/69A5F0/477AF0，75 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_63F2F0(int *this, int *pDwArg2, int nArg3)  // 函数: 合成结果文本（459700/4015C0/422E70/45A340/69A5F0/477AF0，75 行）
{
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  char *v10; // eax
  void *v11; // eax
  int fld_e26; // eax
  uint32_t *fld_e2; // ecx
  int v14; // edi
  int v15; // esi
  int nArg322; // [esp-4h] [ebp-D4h]
  char Buffer[128]; // [esp+Ch] [ebp-C4h] BYREF
  int v18; // [esp+8Ch] [ebp-44h] BYREF
  int v19; // [esp+90h] [ebp-40h]
  int v20; // [esp+B0h] [ebp-20h]
  int nArg32; // [esp+B4h] [ebp-1Ch]
  int dword_796E502; // [esp+C0h] [ebp-10h]
  int v23; // [esp+CCh] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  sub_459700(&v18);  // 调 52 字节元素默认初始化
  v4 = *pDwArg2;
  v23 = 0;
  v5 = (*(int (/*thiscall*/ **)(int *))(v4 + 16))(pDwArg2);  // 调用虚函数（虚表槽 +16）
  v6 = *pDwArg2;
  v19 = *(uint32_t *)(v5 + 68);  // v19 = v5+68
  v7 = (*(int (/*thiscall*/ **)(int *))(v6 + 24))(pDwArg2);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  v8 = *pDwArg2;
  v20 = v7;
  nArg32 = nArg3;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v8 + 16))(pDwArg2) + 4) != 0 )  // 调用虚函数（虚表槽 +16）
  {
    v11 = (void *)(*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 108))(pDwArg2);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
    if ( nArg32 <= 1 )  // 若 nArg32 <= 1
    {
      sub_4015C0(v11, strlen((const char *)v11));  // 【std::string构造赋值】
    }
    else
    {
      sprintf(Buffer, "%s x%d", (const char *)v11, nArg32);  // 调 格式化到缓冲
      sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
    }
  }
  else
  {
    v9 = sub_418DD0(10);  // 调 sub_418DD0
    nArg322 = nArg32;
    v19 = v9;
    v10 = sub_422E70(935);  // 调 sub_422E70
    sprintf(Buffer, v10, nArg322);  // 调 格式化到缓冲
    sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
  }
  sub_45A340((int)(this + 25), &v18);  // 调 52 字节向量尾插
  fld_e26 = *(this + 26);  // fld_e26 = this+26
  if ( fld_e26 != 0 )  // 若 fld_e26 != 0
    fld_e26 = (*(this + 27) - fld_e26) / 52;
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 19, 3 * fld_e26 + 7);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v14 = (480 - fld_e2[8]) / 2;
  v15 = (640 - fld_e2[7]) / 2;
  sub_69A5F0(fld_e2, v15, v14);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v15 + 94, *(uint32_t *)(*(this + 2) + 32) + v14 - 37);  // this+36 = 状态字
  v23 = -1;
  sub_477AF0((int)&v18);  // 调 sub_477AF0
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

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  result = (uint8_t *)*(this + 9);  // this+36 = 状态字
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 调用虚函数（虚表槽 +32）【推断: 设置坐标三元组 (this+100..112)】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x63F500 CNRDQuestRewardWindow__vmt0 —— CNRDQuestRewardWindow__vmt0 构造（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDQuestRewardWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDQuestRewardWindow__vmt0 构造（418DD0）
{
  uint32_t *pThis; // ebx
  int result; // eax
  int v4; // edi
  int v5; // esi
  int pObj3; // eax
  int v7; // edi
  int v8; // esi
  int pObj; // eax
  int pObj2; // ecx
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // eax
  int v14; // edx
  int v16; // [esp+Ch] [ebp-4h]
  int v17; // [esp+18h] [ebp+8h]

  pThis = this;
  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == pThis[2] )  // 若 pArg2 == pThis[2]
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
    v17 = v4;
    pObj3 = sub_418DD0(124);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v4 + 13, v5 + 16, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    result = pThis[25];
    if ( result != 0 )  // 若 result != 0
      result = (pThis[26] - result) / 52;
    if ( result > 0 )  // 若 result > 0
    {
      v7 = 0;
      v8 = v5 + 72;
      v16 = result;
      while ( 1 )  // 无限循环
      {
        pObj = sub_418DD0(90);  // 调 sub_418DD0
        if ( pObj != 0 )  // 若 pObj != 0
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
            pObj,
            v17 + 18,
            v8 - 10,
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            1065353216,
            1065353216,
            0,
            872415231,
            1333788672,
            1333788672);
        pObj2 = *(uint32_t *)(pThis[25] + v7 + 4);
        if ( pObj2 != 0 )  // 若 pObj2 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v17 + 19, v8 - 9, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pThis + 11);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
        v11 = pThis[25];
        v12 = *(uint32_t *)(v11 + v7 + 32);
        v13 = v7 + v11;
        v14 = v12 < 0x10 ? v13 + 12 : *(uint32_t *)(v13 + 12);
        (*(void (/*cdecl*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          v17 + 6,
          v8,
          *(uint32_t *)(v13 + 36),
          v14);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
        v8 += 39;
        v7 += 52;
        result = --v16;
        if ( v16 == 0 )  // 若 v16 == 0
          break;
        pThis = this;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x63F660 sub_63F660 —— 任务奖励清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_63F660(int this)  // 函数: 任务奖励清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  int result; // eax

  *(uint32_t *)(this + 40) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+40 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x84u);  // operator new 分配 132 字节
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(uint32_t *)(this + 36) = v3;  // this+144 = pFrameList144
  result = sub_69A840(v3);  // 调 sub_69A840
  *(uint8_t *)(this + 44) = 0;  // this+44 = 0
  *(uint8_t *)(this + 45) = 0;  // this+45 = 0
  *(uint8_t *)(this + 46) = 0;  // this+46 = 0
  *(uint8_t *)(this + 47) = 0;  // this+47 = 0
  *(uint32_t *)(this + 56) = 0;  // this+56 = 0
  *(uint32_t *)(this + 68) = 0;  // this+68 = 0
  *(uint32_t *)(this + 76) = 0;  // this+76 = 0
  *(uint32_t *)(this + 80) = 0;  // this+80 = 0
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 60) = 6;  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 64) = 12;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 72) = 1600;  // this+72 = 1600
  *(uint32_t *)(this + 92) = dword_99FCCC;  // this+92 = dword_99FCCC
  *(uint32_t *)(this + 72) = 228;  // this+72 = 228
  *(uint32_t *)(this + 56) = 1;  // this+56 = 1
  *(uint32_t *)(this + 48) = -16777216;  // this+48 = -16777216
  return result;
}



// ------------------------------------------------------------
// 0x63F740 CNRDQuestRewardWindow__vmtC —— CNRDQuestRewardWindow__vmtC 收尾（44CA70 + 69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDQuestRewardWindow__vmtC(int *this, int nArg2, int nArg3)  // 函数: CNRDQuestRewardWindow__vmtC 收尾（44CA70 + 69A5F0）
{
  int fld_e25; // eax
  uint32_t *fld_e2; // ecx
  int v7; // ebx
  int v8; // edi

  if ( nArg2 == 0 )  // 若 nArg2 == 0
    return 0;
  sub_44CA70(this + 24);  // 调 52 字节记录数组析构释放
  fld_e25 = *(this + 25);  // fld_e25 = this+25
  if ( fld_e25 != 0 )  // 若 fld_e25 != 0
    fld_e25 = (*(this + 26) - fld_e25) / 52;
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 19, 3 * fld_e25 + 7);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v7 = (480 - fld_e2[8]) / 2;
  v8 = (640 - fld_e2[7]) / 2;
  sub_69A5F0(fld_e2, v8, v7);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v8 + 94, *(uint32_t *)(*(this + 2) + 32) + v7 - 37);  // this+36 = 状态字
  return 1;
}



// ------------------------------------------------------------
// 0x63F7E0 sub_63F7E0 —— 任务奖励文本（459700/4015C0/422E70/45A340/69A5F0/477AF0，75 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_63F7E0(int *this, int *pDwArg2, int nArg3)  // 函数: 任务奖励文本（459700/4015C0/422E70/45A340/69A5F0/477AF0，75 行）
{
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  char *v10; // eax
  void *v11; // eax
  int fld_e25; // eax
  uint32_t *fld_e2; // ecx
  int v14; // edi
  int v15; // esi
  int nArg322; // [esp-4h] [ebp-D4h]
  char Buffer[128]; // [esp+Ch] [ebp-C4h] BYREF
  int v18; // [esp+8Ch] [ebp-44h] BYREF
  int v19; // [esp+90h] [ebp-40h]
  int v20; // [esp+B0h] [ebp-20h]
  int nArg32; // [esp+B4h] [ebp-1Ch]
  int dword_796E502; // [esp+C0h] [ebp-10h]
  int v23; // [esp+CCh] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  sub_459700(&v18);  // 调 52 字节元素默认初始化
  v4 = *pDwArg2;
  v23 = 0;
  v5 = (*(int (/*thiscall*/ **)(int *))(v4 + 16))(pDwArg2);  // 调用虚函数（虚表槽 +16）
  v6 = *pDwArg2;
  v19 = *(uint32_t *)(v5 + 68);  // v19 = v5+68
  v7 = (*(int (/*thiscall*/ **)(int *))(v6 + 24))(pDwArg2);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  v8 = *pDwArg2;
  v20 = v7;
  nArg32 = nArg3;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v8 + 16))(pDwArg2) + 4) != 0 )  // 调用虚函数（虚表槽 +16）
  {
    v11 = (void *)(*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 108))(pDwArg2);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
    if ( nArg32 <= 1 )  // 若 nArg32 <= 1
    {
      sub_4015C0(v11, strlen((const char *)v11));  // 【std::string构造赋值】
    }
    else
    {
      sprintf(Buffer, "%s x%d", (const char *)v11, nArg32);  // 调 格式化到缓冲
      sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
    }
  }
  else
  {
    v9 = sub_418DD0(10);  // 调 sub_418DD0
    nArg322 = nArg32;
    v19 = v9;
    v10 = sub_422E70(1137);  // 调 sub_422E70
    sprintf(Buffer, v10, nArg322);  // 调 格式化到缓冲
    sub_4015C0(Buffer, strlen(Buffer));  // 【std::string构造赋值】
  }
  sub_45A340((int)(this + 24), &v18);  // 调 52 字节向量尾插
  fld_e25 = *(this + 25);  // fld_e25 = this+25
  if ( fld_e25 != 0 )  // 若 fld_e25 != 0
    fld_e25 = (*(this + 26) - fld_e25) / 52;
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 24))(this, 19, 3 * fld_e25 + 7);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
  fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
  v14 = (480 - fld_e2[8]) / 2;
  v15 = (640 - fld_e2[7]) / 2;
  sub_69A5F0(fld_e2, v15, v14);  // 调 sub_69A5F0
  sub_69A5F0((uint32_t *)*(this + 9), v15 + 94, *(uint32_t *)(*(this + 2) + 32) + v14 - 37);  // this+36 = 状态字
  v23 = -1;
  sub_477AF0((int)&v18);  // 调 sub_477AF0
}



// ------------------------------------------------------------
// 0x63F9B0 CNRDClassChangeWindow__vmt8 —— CNRDClassChangeWindow__vmt8 Update（CLICK_BUTTON2）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDClassChangeWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // this+8 = 技能槽记录首字
  result = (uint8_t *)*(this + 9);  // this+36 = 状态字
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 20))(this);  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}



// ------------------------------------------------------------
// 0x63F9F0 sub_63F9F0 —— 转职窗数据（41ACF0 粒子挂载，93 行）
// ------------------------------------------------------------
char */*stdcall*/ sub_63F9F0(int pArg1)  // 函数: 转职窗数据（41ACF0 粒子挂载，93 行）
{
  char *result; // eax
  int i; // esi
  char v3; // cl
  int v4; // ecx
  int v5; // ecx
  char *v6; // edx
  char v7; // cl

  result = (char *)sub_41ACF0(pArg1 + 20);  // 调 驻留串句柄 → 字符串指针
  if ( strlen(result) > 0xE )  // 调 返回字符串长度（逐字节扫描）
  {
    for ( i = 0; ; i = v5 )  // 循环：i = 0; ; i = v5
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
      if ( v5 > 12 )  // 若 v5 > 12
        break;
    }
    v6 = (char *)(byte_9B94B0 - result);
    do
    {
      v7 = *result;
      result[(uint32_t)v6] = *result;  // result[(uint32_t)v6] 写入 *result
      ++result;  // 自增result
    }
    while ( v7 != 0 );  // 当 v7 != 0 循环
    byte_9B94B0[i] = 0;
    strcat(byte_9B94B0, "..");  // 调 串拼接
    return byte_9B94B0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x63FBC0 CNRDClassChangeWindow__vmt0 —— CNRDClassChangeWindow__vmt0 构造（322 行：554930 + 47DF50 + 63F9F0 + 422E70）
// ------------------------------------------------------------
int /*userpurge*/ sub_63FBC0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int pArg3)  // 函数: CNRDClassChangeWindow__vmt0 构造（322 行：554930 + 47DF50 + 63F9F0 + 422E70）
{
  int result; // eax
  int v5; // ebx
  int v6; // edi
  int pObj3; // eax
  int pObj6; // ecx
  int pObj; // eax
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // ecx
  int v14; // edi
  int v15; // eax
  int v16; // edi
  signed int v17; // edi
  int pObj8; // eax
  bool v19; // zf
  int pObj10; // eax
  int pObj4; // eax
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
  int pObj2; // eax
  int v33; // edi
  int v34; // eax
  int v35; // ecx
  unsigned int v36; // edi
  int pObj5; // ecx
  int v38; // ebx
  int v39; // eax
  int v40; // ecx
  int v41; // eax
  int v42; // ecx
  int v43; // edx
  int v44; // eax
  unsigned int v45; // edi
  int pObj9; // eax
  int v47; // edi
  int v48; // eax
  int v49; // ecx
  unsigned int v50; // edi
  int pObj7; // ecx
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

  result = sub_554930(pArg3);  // 【IRDPopupWindow__vmt0】
  if ( pArg3 == pArg1[2] )  // 若 pArg3 == pArg1[2]
  {
    v5 = *(uint32_t *)(pArg3 + 20);  // v5 = pArg3+20
    v6 = *(uint32_t *)(pArg3 + 24);  // v6 = pArg3+24
    v61 = v5;
    v62 = v6;
    pObj3 = sub_418DD0(0);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v5 + 6, v6 + 6, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj6 = pArg1[11];
    if ( pObj6 != 0 )  // 若 pObj6 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v5 + 43, v6 + 45, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj = sub_418DD0(2);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
        pObj,
        v5 + 8,
        v6 + 90,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,
        1065353216,
        0,
        1694498815,
        1333788672,
        1333788672);
    v10 = pArg1[26];
    if ( v10 != 0 )  // 若 v10 != 0
      v11 = (pArg1[27] - v10) >> 3;
    else
      v11 = 0;
    v12 = pArg1[30];
    if ( v12 != 0 )  // 若 v12 != 0
      v13 = (pArg1[31] - v12) >> 2;
    else
      v13 = 0;
    v14 = pArg1[34];
    if ( v14 != 0 )  // 若 v14 != 0
      v15 = (pArg1[35] - v14) >> 2;
    else
      v15 = 0;
    if ( pArg1[34] != 0 )  // 若 pArg1[34] != 0
      v16 = (pArg1[35] - pArg1[34]) >> 2;
    else
      v16 = 0;
    v17 = (v15 != 0) + ((unsigned int)(v11 + 1) >> 1) + ((unsigned int)(v13 + 1) >> 1) + ((unsigned int)(v16 + 1) >> 1);
    if ( v17 > 0 )  // 若 v17 > 0
    {
      v63 = v62 + 123;
      v58 = v17;
      do
      {
        pObj8 = sub_418DD0(3);  // 调 sub_418DD0
        if ( pObj8 != 0 )  // 若 pObj8 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj8 + 128))(  // 调用虚函数（虚表槽 +128）
            pObj8,
            v5 + 8,
            v63,
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            1065353216,
            1065353216,
            0,
            1694498815,
            1333788672,
            1333788672);
        v19 = v58 == 1;
        v63 += 39;
        --v58;  // 自减v58
      }
      while ( !v19 );  // 当 !v19 循环
    }
    pObj10 = sub_418DD0(4);  // 调 sub_418DD0
    if ( pObj10 != 0 )  // 若 pObj10 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj10 + 128))(  // 调用虚函数（虚表槽 +128）
        pObj10,
        v5 + 8,
        39 * v17 + v62 + 123,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,
        1065353216,
        0,
        1694498815,
        1333788672,
        1333788672);
    pObj4 = sub_418DD0(1);  // 调 sub_418DD0
    if ( pObj4 != 0 )  // 若 pObj4 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 调用虚函数（虚表槽 +128）
        pObj4,
        v5 + 12,
        v62 + 94,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,
        1065353216,
        0,
        603979775,
        1333788672,
        1333788672);
    (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 12, nArg2);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    v22 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    v23 = sub_422E70(918);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v22 + 80))(dword_79C0B0, v5 + 24, v62 + 97, -6833455, v23);  // 调用虚函数（虚表槽 +80）
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    v24 = pArg1[26];
    if ( v24 != 0 )  // 若 v24 != 0
      v25 = (pArg1[27] - v24) >> 3;
    else
      v25 = 0;
    v26 = 0;
    for ( i = v25; (int)v26 < i; ++v26 )  // 循环：i = v25; (int)v26 < i; ++v26
    {
      v55 = 126 * (v26 % 2) + v5 + 12;
      sub_47DF50(v55, 39 * (v26 / 2) + v62 + 94 + 29, *(uint32_t *)(8 * v26 + pArg1[26] + 4), 0, 1, 0, 0);  // 调 sub_47DF50
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
      v27 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      v28 = sub_63F9F0(*(uint32_t *)(pArg1[26] + 8 * v26));  // 调 转职窗数据（41ACF0 粒子挂载，93 行）
      (*(void (/*cdecl*/ **)(int, int, unsigned int, int, int))(v27 + 80))(  // 调用虚函数（虚表槽 +80）
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        v55 + 37,
        39 * (v26 / 2) + v62 + 94 + 38,
        -1,
        v28);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
      v5 = v61;
    }
    v29 = pArg1[26];
    if ( v29 != 0 )  // 若 v29 != 0
      v30 = (pArg1[27] - v29) >> 3;
    else
      v30 = 0;
    v31 = 39 * ((unsigned int)(v30 + 1) >> 1) + v62 + 133;
    v59 = v31;
    pObj2 = sub_418DD0(1);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, unsigned int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调用虚函数（虚表槽 +128）
        pObj2,
        v5 + 12,
        v31,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,
        1065353216,
        0,
        603979775,
        1333788672,
        1333788672);
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    v33 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    v34 = sub_422E70(919);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v33 + 80))(dword_79C0B0, v5 + 24, v59 + 3, -6833455, v34);  // 调用虚函数（虚表槽 +80）
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    result = pArg1[30];
    if ( result != 0 )  // 若 result != 0
      v35 = (pArg1[31] - result) >> 2;
    else
      v35 = 0;
    v36 = 0;
    for ( j = v35; (int)v36 < j; ++v36 )  // 循环：j = v35; (int)v36 < j; ++v36
    {
      v56 = 126 * (v36 % 2) + v5 + 12;
      pObj5 = *(uint32_t *)(*(uint32_t *)(4 * v36 + pArg1[30]) + 380);
      if ( pObj5 != 0 )  // 若 pObj5 != 0
        (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, int))(*(uint32_t *)pObj5 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          pObj5,
          v56,
          39 * (v36 / 2) + v59 + 29,
          dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
      v38 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      v39 = sub_63F9F0(*(uint32_t *)(pArg1[30] + 4 * v36));  // 调 转职窗数据（41ACF0 粒子挂载，93 行）
      (*(void (/*cdecl*/ **)(int, unsigned int, unsigned int, int, int))(v38 + 80))(  // 调用虚函数（虚表槽 +80）
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        v56 + 37,
        39 * (v36 / 2) + v59 + 38,
        -1,
        v39);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
      result = j;
      v5 = v61;
    }
    v40 = pArg1[34];
    if ( v40 != 0 )  // 若 v40 != 0
    {
      result = (pArg1[35] - v40) >> 2;
      if ( result != 0 )  // 若 result != 0
      {
        v41 = pArg1[26];
        if ( v41 != 0 )  // 若 v41 != 0
          v42 = (pArg1[27] - v41) >> 3;
        else
          v42 = 0;
        v43 = pArg1[30];
        if ( v43 != 0 )  // 若 v43 != 0
          v44 = (pArg1[31] - v43) >> 2;
        else
          v44 = 0;
        v45 = 39 * (((unsigned int)(v42 + 1) >> 1) + ((unsigned int)(v44 + 1) >> 1)) + v62 + 172;
        v60 = v45;
        pObj9 = sub_418DD0(1);  // 调 sub_418DD0
        if ( pObj9 != 0 )  // 若 pObj9 != 0
          (*(void (/*thiscall*/ **)(int, int, unsigned int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj9 + 128))(  // 调用虚函数（虚表槽 +128）
            pObj9,
            v5 + 12,
            v45,
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            1065353216,
            1065353216,
            0,
            603979775,
            1333788672,
            1333788672);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
        v47 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
        v48 = sub_422E70(920);  // 调 sub_422E70
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v47 + 80))(dword_79C0B0, v5 + 24, v60 + 3, -6833455, v48);  // 调用虚函数（虚表槽 +80）
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
        result = pArg1[34];
        if ( result != 0 )  // 若 result != 0
          v49 = (pArg1[35] - result) >> 2;
        else
          v49 = 0;
        v50 = 0;
        v66 = v49;
        if ( v49 > 0 )  // 若 v49 > 0
        {
          while ( 1 )  // 无限循环
          {
            v57 = 126 * (v50 % 2) + v5 + 12;
            pObj7 = *(uint32_t *)(*(uint32_t *)(4 * v50 + pArg1[34]) + 380);
            if ( pObj7 != 0 )  // 若 pObj7 != 0
              (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, int))(*(uint32_t *)pObj7 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                pObj7,
                v57,
                39 * (v50 / 2) + v60 + 29,
                dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 12);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
            v52 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
            v53 = sub_63F9F0(*(uint32_t *)(pArg1[34] + 4 * v50));  // 调 转职窗数据（41ACF0 粒子挂载，93 行）
            (*(void (/*cdecl*/ **)(int, unsigned int, unsigned int, int, int))(v52 + 80))(  // 调用虚函数（虚表槽 +80）
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              v57 + 37,
              39 * (v50 / 2) + v60 + 38,
              -1,
              v53);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
            result = v66;
            if ( (int)++v50 >= v66 )  // 若 (int)++v50 >= v66
              break;
            v5 = v61;
          }
        }
      }
    }
  }
  return result;
}

